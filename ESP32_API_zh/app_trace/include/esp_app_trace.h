/*
 * SPDX文件版权文本：2017-2021浓缩咖啡系统（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */
#ifndef ESP_APP_TRACE_H_
#define ESP_APP_TRACE_H_

#include <stdarg.h>
#include "esp_err.h"
#include "esp_app_trace_util.h" // ESP_APPTRACE_TMO_INFINITE

#ifdef __cplusplus
extern "C" {
#endif

/**
 * 应用程序跟踪数据目标位。
 */
typedef enum {
    ESP_APPTRACE_DEST_JTAG = 1,                         ///<JTAG目的地
    ESP_APPTRACE_DEST_TRAX = ESP_APPTRACE_DEST_JTAG, 	///<xxx_TRAX名称已过时，请使用更常见的xxx_JTAG
    ESP_APPTRACE_DEST_UART0,	                        ///<UART0目的地
    ESP_APPTRACE_DEST_MAX = ESP_APPTRACE_DEST_UART0,
    ESP_APPTRACE_DEST_NUM
} esp_apptrace_dest_t;

/**
 * @brief  初始化应用程序跟踪模块。
 *
 * @note   应在任何esp_apptrace_xxx调用之前调用。
 *
 * @return 成功时ESP_OK，否则请参见ESP_err_t
 */
esp_err_t esp_apptrace_init(void);

/**
 * @brief 配置向下缓冲区。
 *        @note 需要在使用esp_apptrace_buffer_get和esp_apptrack_write启动任何数据传输之前调用。此功能不通过锁保护内部数据。
 *
 * @param buf 用于下行通道（主机到目标）数据的缓冲区地址。
 * @param size 缓冲区的大小。
 */
void esp_apptrace_down_buffer_config(uint8_t *buf, uint32_t size);

/**
 * @brief 为跟踪数据分配缓冲区。缓冲区中的数据准备好发送后，必须调用esp_apptrace_buffer_put来指示它。
 *
 * @param dest 表示发送数据的硬件接口。
 * @param size 要写入跟踪缓冲区的数据大小。
 * @param tmo  操作超时（在我们中）。使用ESP_APPTRACE_TMO_INFINITE无限期等待。
 *
 * @return 成功时为非NULL，否则为NULL。
 */
uint8_t *esp_apptrace_buffer_get(esp_apptrace_dest_t dest, uint32_t size, uint32_t tmo);

/**
 * @brief 指示缓冲区中的数据已准备好发送。此函数是的对应函数，必须在其前面加esp_apptrace_buffer_get。
 *
 * @param dest 表示发送数据的硬件接口。应与esp_apptrace_buffer_get调用中的相同参数相同。
 * @param ptr  要释放的跟踪缓冲区的地址。应该是调用esp_apptrace_buffer_get返回的值。
 * @param tmo  操作超时（在我们中）。使用ESP_APPTRACE_TMO_INFINITE无限期等待。
 *
 * @return 成功时ESP_OK，否则请参见ESP_err_t
 */
esp_err_t esp_apptrace_buffer_put(esp_apptrace_dest_t dest, uint8_t *ptr, uint32_t tmo);

/**
 * @brief  将数据写入跟踪缓冲区。
 *
 * @param dest 表示发送数据的硬件接口。
 * @param data 要写入跟踪缓冲区的数据地址。
 * @param size 要写入跟踪缓冲区的数据大小。
 * @param tmo  操作超时（在我们中）。使用ESP_APPTRACE_TMO_INFINITE无限期等待。
 *
 * @return 成功时ESP_OK，否则请参见ESP_err_t
 */
esp_err_t esp_apptrace_write(esp_apptrace_dest_t dest, const void *data, uint32_t size, uint32_t tmo);

/**
 * @brief 类似vprintf的功能，通过指定的硬件接口向主机发送日志消息。
 *
 * @param dest 表示发送数据的硬件接口。
 * @param tmo  操作超时（在我们中）。使用ESP_APPTRACE_TMO_INFINITE无限期等待。
 * @param fmt  格式字符串的地址。
 * @param ap   参数列表。
 *
 * @return 写入的字节数。
 */
int esp_apptrace_vprintf_to(esp_apptrace_dest_t dest, uint32_t tmo, const char *fmt, va_list ap);

/**
 * @brief 类似vprintf的函数，用于向主机发送日志消息。
 *
 * @param fmt  格式字符串的地址。
 * @param ap   参数列表。
 *
 * @return 写入的字节数。
 */
int esp_apptrace_vprintf(const char *fmt, va_list ap);

/**
 * @brief 将跟踪缓冲区中的剩余数据刷新到主机。
 *
 * @param dest 指示要刷新数据的硬件接口。
 * @param tmo  操作超时（在我们中）。使用ESP_APPTRACE_TMO_INFINITE无限期等待。
 *
 * @return 成功时ESP_OK，否则请参见ESP_err_t
 */
esp_err_t esp_apptrace_flush(esp_apptrace_dest_t dest, uint32_t tmo);

/**
 * @brief 将跟踪缓冲区中的剩余数据刷新到主机，而不锁定内部数据。这是esp_apptrace_flush的特殊版本，应该从panic处理程序调用。
 *
 * @param dest   指示要刷新数据的硬件接口。
 * @param min_sz 刷新数据的阈值。如果当前填充级别高于此值，则将刷新数据。仅限TRAX目的地。
 * @param tmo    操作超时（在我们中）。使用ESP_APPTRACE_TMO_INFINITE无限期等待。
 *
 * @return 成功时ESP_OK，否则请参见ESP_err_t
 */
esp_err_t esp_apptrace_flush_nolock(esp_apptrace_dest_t dest, uint32_t min_sz, uint32_t tmo);

/**
 * @brief 从跟踪缓冲区读取主机数据。
 *
 * @param dest 表示读取数据的硬件接口。
 * @param data 从跟踪缓冲区中放入数据的缓冲区地址。
 * @param size 指向存储读取数据大小的指针。在调用此函数之前，指向的内存必须保存请求的数据大小
 * @param tmo  操作超时（在我们中）。使用ESP_APPTRACE_TMO_INFINITE无限期等待。
 *
 * @return 成功时ESP_OK，否则请参见ESP_err_t
 */
esp_err_t esp_apptrace_read(esp_apptrace_dest_t dest, void *data, uint32_t *size, uint32_t tmo);

/**
 * @brief 检索传入数据缓冲区（如果有）。处理缓冲区中的数据后，必须调用esp_apptrace_down_buffer_put来指示它。
 *
 * @param dest 表示接收数据的硬件接口。
 * @param size 用于存储下行缓冲区中可用数据大小的地址。必须使用请求的值初始化。
 * @param tmo  操作超时（在我们中）。使用ESP_APPTRACE_TMO_INFINITE无限期等待。
 *
 * @return 成功时为非NULL，否则为NULL。
 */
uint8_t *esp_apptrace_down_buffer_get(esp_apptrace_dest_t dest, uint32_t *size, uint32_t tmo);

/**
 * @brief 指示已处理下行缓冲区中的数据。此函数是esp_apptrace_down_buffer_get的对应函数，必须在其前面。
 *
 * @param dest 表示接收数据的硬件接口。应与esp_apptrace_down_buffer_get调用中的相同参数相同。
 * @param ptr  要释放的跟踪缓冲区的地址。应该是调用esp_apptrace_down_buffer_get返回的值。
 * @param tmo  操作超时（在我们中）。使用ESP_APPTRACE_TMO_INFINITE无限期等待。
 *
 * @return 成功时ESP_OK，否则请参见ESP_err_t
 */
esp_err_t esp_apptrace_down_buffer_put(esp_apptrace_dest_t dest, uint8_t *ptr, uint32_t tmo);

/**
 * @brief 检查主机是否已连接。
 *
 * @param dest 指示要使用的硬件接口。
 *
 * @return 如果主机已连接，则为true，否则为false
 */
bool esp_apptrace_host_is_connected(esp_apptrace_dest_t dest);

/**
 * @brief 在主机上打开文件。除了第一个参数外，此函数与“fopen”具有相同的语义。
 *
 * @param dest 指示要使用的硬件接口。
 * @param path 文件路径。
 * @param mode 模式字符串。有关详细信息，请参阅fopen。
 *
 * @return 成功时为非零文件句柄，否则为0
 */
void *esp_apptrace_fopen(esp_apptrace_dest_t dest, const char *path, const char *mode);

/**
 * @brief 关闭主机上的文件。除第一个参数外，此函数与“fclose”具有相同的语义。
 *
 * @param dest   指示要使用的硬件接口。
 * @param stream esp_apptrace_fopen返回的文件句柄。
 *
 * @return 成功时为零，否则为非零。有关详细信息，请参见fclose。
 */
int esp_apptrace_fclose(esp_apptrace_dest_t dest, void *stream);

/**
 * @brief 写入主机上的文件。除了第一个参数外，此函数与“fwrite”具有相同的语义。
 *
 * @param dest   指示要使用的硬件接口。
 * @param ptr 要写入的数据地址。
 * @param size 项目的大小。
 * @param nmemb  要写入的项目数。
 * @param stream esp_apptrace_fopen返回的文件句柄。
 *
 * @return 写入项目的数量。有关详细信息，请参阅fwrite。
 */
size_t esp_apptrace_fwrite(esp_apptrace_dest_t dest, const void *ptr, size_t size, size_t nmemb, void *stream);

/**
 * @brief 读取主机上的文件。除了第一个参数外，此函数与“fread”具有相同的语义。
 *
 * @param dest   指示要使用的硬件接口。
 * @param ptr 存储读取数据的地址。
 * @param size 项目的大小。
 * @param nmemb  要读取的项目数。
 * @param stream esp_apptrace_fopen返回的文件句柄。
 *
 * @return 读取的项目数。有关详细信息，请参阅fread。
 */
size_t esp_apptrace_fread(esp_apptrace_dest_t dest, void *ptr, size_t size, size_t nmemb, void *stream);

/**
 * @brief 在主机上的文件中设置位置指示器。除了第一个参数外，此函数与“fseek”具有相同的语义。
 *
 * @param dest   指示要使用的硬件接口。
 * @param stream esp_apptrace_fopen返回的文件句柄。
 * @param offset 抵消有关详细信息，请参阅fseek。
 * @param whence 文件中的位置。有关详细信息，请参阅fseek。
 *
 * @return 成功时为零，否则为非零。有关详细信息，请参阅fseek。
 */
int esp_apptrace_fseek(esp_apptrace_dest_t dest, void *stream, long offset, int whence);

/**
 * @brief 获取主机上文件的当前位置指示器。除了第一个参数外，此函数与“ftell”具有相同的语义。
 *
 * @param dest   指示要使用的硬件接口。
 * @param stream esp_apptrace_fopen返回的文件句柄。
 *
 * @return 文件中的当前位置。有关详细信息，请参阅ftell。
 */
int esp_apptrace_ftell(esp_apptrace_dest_t dest, void *stream);

/**
 * @brief 向主机指示所有文件操作都已完成。应在完成所有文件操作后调用此函数，并向主机指示它可以执行清理操作（关闭打开的文件等）。
 *
 * @param dest   指示要使用的硬件接口。
 *
 * @return 成功时ESP_OK，否则请参见ESP_err_t
 */
int esp_apptrace_fstop(esp_apptrace_dest_t dest);

/**
 * @brief 触发gcov信息转储。此函数在转储数据之前等待主机连接到目标。
 */
void esp_gcov_dump(void);

#ifdef __cplusplus
}
#endif

#endif

