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
#ifndef ESP_CORE_DUMP_COMMON_H_
#define ESP_CORE_DUMP_COMMON_H_

#include "freertos/FreeRTOS.h"
#include "soc/cpu.h"
#include "esp_debug_helpers.h"
#include "esp_app_format.h"
#include "esp_core_dump_types.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 现有内存区域的枚举。可以使用以下函数使用这些定义来检索特定区域的起始地址和/或大小。
 */
typedef enum {
    COREDUMP_MEMORY_DRAM,
    COREDUMP_MEMORY_IRAM,
    COREDUMP_MEMORY_RTC,
    COREDUMP_MEMORY_RTC_FAST,
    COREDUMP_MEMORY_MAX,
    COREDUMP_MEMORY_START = COREDUMP_MEMORY_DRAM
} coredump_region_t;

/**
 * @brief 获取当前任务的（FreeRTOS）任务句柄。
 *
 * @return 当前任务的任务句柄。
 */
core_dump_task_handle_t esp_core_dump_get_current_task_handle(void);

/**
 * @brief 获取给定句柄的下一个任务句柄。
 *
 * @param handle 要从中获取下一个句柄的任务句柄。
 *
 * @return 下一个任务句柄。
 */
core_dump_task_handle_t esp_core_dump_get_next_task(core_dump_task_handle_t handle);

/**
 * @brief 从给定句柄获取任务快照。
 *
 * @param handle 从中获取快照的任务句柄。
 * @param task 返回的任务标头。
 * @param interrupted_stack 如果传递的句柄是崩溃的任务，并且在ISR上下文中崩溃，则备份任务堆栈。
 *
 * @return 如果任务失败，则为假，否则为真。
 */
bool esp_core_dump_get_task_snapshot(core_dump_task_handle_t handle,
                                     core_dump_task_header_t *task,
                                     core_dump_mem_seg_header_t *interrupted_stack);

/**
 * @brief 重置任务快照迭代器。
 */
void esp_core_dump_reset_tasks_snapshots_iter(void);


/**
 * @brief 检查作为参数传递的TCB是否正常。
 *
 * @param address 要检查的TCB地址。
 *
 * @return 如果TCB正常，则为true，否则为false。
 */
bool esp_core_dump_tcb_addr_is_sane(uint32_t addr);

/**
 * @brief 获取RAM段的数量。
 *
 * @return RAM段的数量。
 */
uint32_t esp_core_dump_get_user_ram_segments(void);


/**
 * @brief 获取内存区域的起始地址和大小。
 *
 * @param region 要获取有关信息的内存区域。
 * @param start  将填充区域起始地址的指针。不能为NULL。
 *
 * @return 内存区域的大小（以字节为单位）。
 */
int esp_core_dump_get_user_ram_info(coredump_region_t region, uint32_t *start);


/**
 * @brief 检查当前任务是否在ISR中。
 *
 * @return 如果任务在ISR中，则为true，否则为false。
 */
bool esp_core_dump_in_isr_context(void);


/**
 * @brief 获取所有内存区域的大小（DRAM、RTC、RTC_FAST、IRAM）
 *
 * @return 所有内存区域的大小（以字节为单位）。
 */
uint32_t esp_core_dump_get_user_ram_size(void);


/**
 * @brief 获取TCB长度（字节）。
 *
 * @return TCB的长度，以字节为单位。
 */
static inline uint32_t esp_core_dump_get_tcb_len(void)
{
    return (sizeof(StaticTask_t) % sizeof(uint32_t)) ?
           ((sizeof(StaticTask_t) / sizeof(uint32_t) + 1) * sizeof(uint32_t)) :
           sizeof(StaticTask_t);
}

/**
 * @brief 获取给定内存位置的长度（以字节为单位）。此计算中考虑了填充。
 *
 * @param start 时刻位置的起始地址。
 * @param end 内存位置的结束地址。
 *
 * @return 内存位置的大小，sizeof（uint32_t）的倍数。
 */
static inline uint32_t esp_core_dump_get_memory_len(uint32_t start, uint32_t end)
{
    const uint32_t len = end - start;
    // 考虑堆栈填充
    return (len + sizeof(uint32_t) - 1) & ~(sizeof(uint32_t) - 1);
}


#ifdef __cplusplus
}
#endif

#endif

