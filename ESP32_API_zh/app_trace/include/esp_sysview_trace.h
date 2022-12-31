/*
 * SPDX文件版权文本：2018-2021浓缩咖啡系统（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */
#ifndef ESP_SYSVIEW_TRACE_H_
#define ESP_SYSVIEW_TRACE_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdarg.h>
#include "esp_err.h"
#include "SEGGER_RTT.h" // SEGGER_RTT_ESP冲洗
#include "esp_app_trace_util.h" // ESP_APPTRACE_TMO_INFINITE

/**
 * @brief 将SystemView跟踪缓冲区中的剩余数据刷新到主机。
 *
 * @param tmo  操作超时（在我们中）。使用ESP_APPTRACE_TMO_INFINITE等待。
 *
 * @return ESP_OK.
 */
static inline esp_err_t esp_sysview_flush(uint32_t tmo)
{
    SEGGER_RTT_ESP_Flush(0, tmo);
    return ESP_OK;
}

/**
 * @brief 类似vprintf的函数，用于向主机发送日志消息。
 *
 * @param format  格式字符串的地址。
 * @param args    参数列表。
 *
 * @return 写入的字节数。
 */
int esp_sysview_vprintf(const char * format, va_list args);

/**
 * @brief  启动SystemView堆跟踪。
 *
 * @param tmo 等待主机连接超时。使用-1可以永远等待。
 *
 * @return 成功时为ESP_OK，如果操作已超时，则为ESP_ERR_TIMEOUT。
 */
esp_err_t esp_sysview_heap_trace_start(uint32_t tmo);

/**
 * @brief  停止SystemView堆跟踪。
 *
 * @return ESP_OK.
 */
esp_err_t esp_sysview_heap_trace_stop(void);

/**
 * @brief 向主机发送堆分配事件。
 *
 * @param addr      分配块的地址。
 * @param size      已分配块的大小。
 * @param callers   指向具有调用堆栈地址的数组的指针。数组大小必须为CONFIG_HEAP_TRACING_STACK_DEPTH。
 */
void esp_sysview_heap_trace_alloc(void *addr, uint32_t size, const void *callers);

/**
 * @brief 向主机发送堆取消分配事件。
 *
 * @param addr      取消分配块的地址。
 * @param callers   指向具有调用堆栈地址的数组的指针。数组大小必须为CONFIG_HEAP_TRACING_STACK_DEPTH。
 */
void esp_sysview_heap_trace_free(void *addr, const void *callers);

#ifdef __cplusplus
}
#endif

#endif //ESP_SYSVIEW_TRACE_H_

