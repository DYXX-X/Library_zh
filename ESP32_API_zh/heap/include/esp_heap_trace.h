// 版权所有2015-2016 Espressif Systems（上海）私人有限公司
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
#pragma once

#include "sdkconfig.h"
#include <stdint.h>
#include <esp_err.h>

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(CONFIG_HEAP_TRACING) && !defined(HEAP_TRACE_SRCFILE)
#warning "esp_heap_trace.h is included but heap tracing is disabled in menuconfig, functions are no-ops"
#endif

#ifndef CONFIG_HEAP_TRACING_STACK_DEPTH
#define CONFIG_HEAP_TRACING_STACK_DEPTH 0
#endif

typedef enum {
    HEAP_TRACE_ALL,
    HEAP_TRACE_LEAKS,
} heap_trace_mode_t;

/**
 * @brief 跟踪记录数据类型。存储有关已分配内存区域的信息。
 */
typedef struct {
    uint32_t ccount; ///<分配时CPU的CCOUNT。LSB（位值1）是CPU编号（0或1）。
    void *address;   ///<分配的地址
    size_t size;     ///<分配大小
    void *alloced_by[CONFIG_HEAP_TRACING_STACK_DEPTH]; ///<分配内存的调用方的调用堆栈。
    void *freed_by[CONFIG_HEAP_TRACING_STACK_DEPTH];   ///<释放内存的调用方的调用堆栈（如果未释放，则全部为零。）
} heap_trace_record_t;

/**
 * @brief 在独立模式下初始化堆跟踪。
 *
 * 必须在调用任何其他堆跟踪函数之前调用此函数。
 *
 * 要禁用堆跟踪并允许释放缓冲区，请停止跟踪，然后调用heap_trace_init_standalone（NULL，0）；
 *
 * @param record_buffer 提供用于堆跟踪数据的缓冲区。在启用堆跟踪时必须保持有效，这意味着必须从内部内存而不是PSRAM中分配。
 * @param num_records 堆跟踪缓冲区的大小，以记录结构的数量表示。
 * @return
 *  -ESP_ERR_NOT_SUPPORTED项目在menuconfig中未启用堆跟踪的情况下编译。
 *  -ESP_ERR_INVALID_STATE堆跟踪当前正在进行。
 *  -ESP_OK堆跟踪已成功初始化。
 */
esp_err_t heap_trace_init_standalone(heap_trace_record_t *record_buffer, size_t num_records);

/**
 * @brief 在基于主机的模式下初始化堆跟踪。
 *
 * 必须在调用任何其他堆跟踪函数之前调用此函数。
 *
 * @return
 *  -ESP_ERR_INVALID_STATE堆跟踪当前正在进行。
 *  -ESP_OK堆跟踪已成功初始化。
 */
esp_err_t heap_trace_init_tohost(void);

/**
 * @brief 启动堆跟踪。将跟踪所有堆分配和释放，直到调用heap_trace_stop（）。
 *
 * @note 在调用此函数之前，必须调用heap_trace_init_standalone（）以提供有效的缓冲区。
 *
 * @note 在堆跟踪运行时调用此函数将重置堆跟踪状态并继续跟踪。
 *
 * @param mode 跟踪模式。
 * -HEAP_TRACE_ALL表示跟踪所有堆分配和释放。
 * -HEAP_TRACE_LEAKS表示只跟踪可疑的内存泄漏。（释放内存后，记录将从跟踪缓冲区中删除。）
 * @return
 * -ESP_ERR_NOT_SUPPORTED项目在menuconfig中未启用堆跟踪的情况下编译。
 * -ESP_ERR_INVALID_STATE尚未通过heap_trace_init_standalone（）设置非零长度缓冲区。
 * -ESP_OK跟踪已启动。
 */
esp_err_t heap_trace_start(heap_trace_mode_t mode);

/**
 * @brief 停止堆跟踪。
 *
 * @return
 * -ESP_ERR_NOT_SUPPORTED项目在menuconfig中未启用堆跟踪的情况下编译。
 * -ESP_ERR_INVALID_STATE堆跟踪未进行。
 * -ESP_OK堆跟踪已停止。。
 */
esp_err_t heap_trace_stop(void);

/**
 * @brief 恢复以前停止的堆跟踪。
 *
 * 与heap_trace_start（）不同，此函数不会清除缓冲区中任何预先存在的跟踪记录。
 *
 * 堆跟踪模式与上次调用heap_trace_start（）时相同（如果从未调用heap_race_start（），则为heap_trace_ALL）。
 *
 * @return
 * -ESP_ERR_NOT_SUPPORTED项目在menuconfig中未启用堆跟踪的情况下编译。
 * -ESP_ERR_INVALID_STATE堆跟踪已启动。
 * -ESP_OK堆跟踪已恢复。
 */
esp_err_t heap_trace_resume(void);

/**
 * @brief 返回堆跟踪缓冲区中的记录数
 *
 * 在堆跟踪运行时调用此函数是安全的。
 */
size_t heap_trace_get_count(void);

/**
 * @brief 从堆跟踪缓冲区返回原始记录
 *
 * @note 在堆跟踪运行时调用此函数是安全的，但是在heap_TRACE_LEAK模式下，除非首先停止堆跟踪，否则记录索引可能会跳过条目。
 *
 * @param index 要返回的记录的索引（从零开始）。
 * @param[out] record 记录将复制堆跟踪记录的位置。
 * @return
 * -ESP_ERR_NOT_SUPPORTED项目在menuconfig中未启用堆跟踪的情况下编译。
 * -ESP_ERR_INVALID_STATE堆跟踪未初始化。
 * -ESP_ERR_INVALID_ARG索引超出当前堆跟踪记录计数的范围。
 * -ESP_OK记录成功返回。
 */
esp_err_t heap_trace_get(size_t index, heap_trace_record_t *record);

/**
 * @brief 将堆跟踪记录数据转储到stdout
 *
 * @note 在堆跟踪运行时调用此函数是安全的，但是在heap_TRACE_LEAK模式下，除非首先停止堆跟踪，否则转储可能会跳过条目。
 *
 *
 */
void heap_trace_dump(void);

#ifdef __cplusplus
}
#endif

