// 版权所有2015-2019 Espressif Systems（上海）私人有限公司
//
// 根据Apache许可证2.0版（“许可证”）获得许可；
// 除非符合许可证，否则不得使用此文件。
// 您可以在以下地址获取许可证副本：

//     http://www.apache.org/licenses/LICENSE-2.0
//
// 除非适用法律要求或书面同意，软件
// 根据许可证分发的内容是按“原样”分发的，
// 无任何明示或暗示的保证或条件。
// 有关管理权限和
// 许可证下的限制。
#ifndef ESP_CORE_DUMP_PRIV_H_
#define ESP_CORE_DUMP_PRIV_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "esp_err.h"
#include "esp_attr.h"
#include "esp_log.h"
#include "esp_rom_sys.h"
#include "sdkconfig.h"
#include "esp_private/panic_internal.h"
#include "core_dump_checksum.h"

#define ESP_COREDUMP_LOG( level, format, ... )  if (LOG_LOCAL_LEVEL >= level)   { esp_rom_printf(DRAM_STR(format), esp_log_early_timestamp(), (const char *)TAG, ##__VA_ARGS__); }
#define ESP_COREDUMP_LOGE( format, ... )  ESP_COREDUMP_LOG(ESP_LOG_ERROR, LOG_FORMAT(E, format), ##__VA_ARGS__)
#define ESP_COREDUMP_LOGW( format, ... )  ESP_COREDUMP_LOG(ESP_LOG_WARN, LOG_FORMAT(W, format), ##__VA_ARGS__)
#define ESP_COREDUMP_LOGI( format, ... )  ESP_COREDUMP_LOG(ESP_LOG_INFO, LOG_FORMAT(I, format), ##__VA_ARGS__)
#define ESP_COREDUMP_LOGD( format, ... )  ESP_COREDUMP_LOG(ESP_LOG_DEBUG, LOG_FORMAT(D, format), ##__VA_ARGS__)
#define ESP_COREDUMP_LOGV( format, ... )  ESP_COREDUMP_LOG(ESP_LOG_VERBOSE, LOG_FORMAT(V, format), ##__VA_ARGS__)

/**
 * @brief 要在发布上下文中验证的断言。无法静音。
 */
#define ESP_COREDUMP_ASSERT( condition ) if(!(condition)){ abort(); } else { }

/**
 * @brief 要在调试上下文中验证的断言。可以静音。
 */
#define ESP_COREDUMP_DEBUG_ASSERT( condition ) assert(condition)

/**
 * @brief 仅当内核转储未写入UART时，才应启用日志记录。
 */
#if CONFIG_ESP_COREDUMP_ENABLE_TO_FLASH
#define ESP_COREDUMP_LOG_PROCESS( format, ... )  ESP_COREDUMP_LOGD(format, ##__VA_ARGS__)
#else
#define ESP_COREDUMP_LOG_PROCESS( format, ... )  do{/*(__VA_ARGS__);*/}while(0)
#endif

#define COREDUMP_MAX_TASK_STACK_SIZE        (64*1024)

/**
 * @brief 以下定义的宏用于创建版本编号。然后在核心转储标头中使用此数字。
 *
 * @note COREDUMP_VERSION_CHIP在端口标头中定义。
 */
#define COREDUMP_VERSION_MAKE(_maj_, _min_) ( \
                                                (((COREDUMP_VERSION_CHIP)&0xFFFF) << 16) | \
                                                (((_maj_)&0xFF) << 8) | \
                                                (((_min_)&0xFF) << 0) \
                                            )
#define COREDUMP_VERSION_BIN                0
#define COREDUMP_VERSION_ELF                1

/* 旧bin coredumps（IDF v4.1之前）的版本设置为1*/
#define COREDUMP_VERSION_BIN_LEGACY         COREDUMP_VERSION_MAKE(COREDUMP_VERSION_BIN, 1) // ->0x0001号
#define COREDUMP_VERSION_BIN_CURRENT        COREDUMP_VERSION_MAKE(COREDUMP_VERSION_BIN, 2) // ->0x0002年
#define COREDUMP_VERSION_ELF_CRC32          COREDUMP_VERSION_MAKE(COREDUMP_VERSION_ELF, 0) // ->0x0100
#define COREDUMP_VERSION_ELF_SHA256         COREDUMP_VERSION_MAKE(COREDUMP_VERSION_ELF, 1) // ->0x0101
#define COREDUMP_CURR_TASK_MARKER           0xDEADBEEF
#define COREDUMP_CURR_TASK_NOT_FOUND        -1

/**
 * @brief 定义用于写入核心转储的缓存大小的宏。
 */
#define COREDUMP_CACHE_SIZE 32

/**
 * @brief 如果核心转储必须写入加密闪存，我们可以写入的最小数据块长度为16字节。因此，此宏必须是16的倍数。
 */
#if (COREDUMP_CACHE_SIZE % 16) != 0
    #error "Coredump cache size must be a multiple of 16"
#endif


typedef struct _core_dump_write_data_t
{
    uint32_t off; /*!< 正在写入的数据的当前偏移量*/
    uint8_t  cached_data[COREDUMP_CACHE_SIZE]; /*!< 用于写入闪存的缓存*/
    uint8_t  cached_bytes; /*!< 缓存中填充的字节数*/
    core_dump_checksum_ctx* checksum_ctx; /*!< 校验和上下文*/
} core_dump_write_data_t;


/**
 * @brief 下面的类型定义了用于输出核心转储的回调的签名。转储的目标取决于实现。
 */
typedef esp_err_t (*esp_core_dump_write_prepare_t)(core_dump_write_data_t* priv, uint32_t *data_len);
typedef esp_err_t (*esp_core_dump_write_start_t)(core_dump_write_data_t* priv);
typedef esp_err_t (*esp_core_dump_write_end_t)(core_dump_write_data_t* priv);
typedef esp_err_t (*esp_core_dump_flash_write_data_t)(core_dump_write_data_t* priv,
                                                      void * data,
                                                      uint32_t data_len);


/**
 * @brief 堆芯转储发射器控制结构。此结构包含为将核心转储写入目标（UART或闪存）而调用的函数。函数的调用顺序如下：
 * -准备
 * -启动
 * -写入（调用一次或多次）
 * -完
 */
typedef struct _core_dump_write_config_t
{
    esp_core_dump_write_prepare_t    prepare;  /*!< 为健全性检查调用的函数*/
    esp_core_dump_write_start_t      start; /*!< 在数据写入开始时调用的函数*/
    esp_core_dump_flash_write_data_t write; /*!< 调用函数以写入数据块*/
    esp_core_dump_write_end_t        end; /*!< 写入所有数据后调用函数*/
    core_dump_write_data_t*          priv; /*!< 要传递到此结构的每个函数的私有上下文*/
} core_dump_write_config_t;

/**
 * @brief Core dump data header这个头预先处理实际的Core dump数据（ELF或二进制）。*/
typedef struct _core_dump_header_t
{
    uint32_t data_len;  /*!< 数据长度*/
    uint32_t version;   /*!< 核心转储版本*/
    uint32_t tasks_num; /*!< 任务数*/
    uint32_t tcb_sz;    /*!< TCB的大小（字节）*/
    uint32_t mem_segs_num; /*!< 内存段数*/
} core_dump_header_t;

/**
 * @brief 核心转储任务数据头此定义的主要目标是向代码中添加类型。
 */
typedef void* core_dump_task_handle_t;

/**
 * @brief 任务标题
 */
typedef struct _core_dump_task_header_t
{
    core_dump_task_handle_t tcb_addr;    /*!< TCB地址*/
    uint32_t                stack_start; /*!< 堆栈地址的开始*/
    uint32_t                stack_end;   /*!< 堆栈结尾地址*/
} core_dump_task_header_t;

/**
 * @brief 核心转储内存段标头
 */
typedef struct _core_dump_mem_seg_header_t
{
    uint32_t start; /*!< 内存区域起始地址*/
    uint32_t size;  /*!< 内存区域大小*/
} core_dump_mem_seg_header_t;

/**
 * @brief 核心转储闪存初始化功能
 */
void esp_core_dump_flash_init(void);


/**
 * @brief 公共核心转储写入功能
 */
void esp_core_dump_write(panic_info_t *info, core_dump_write_config_t *write_cfg);

#ifdef __cplusplus
}
#endif

#endif

