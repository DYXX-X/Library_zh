/*
 * SPDX文件版权文本：2020-2021浓缩咖啡系统（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */

#pragma once

#include <stdint.h>
#include <stdbool.h>

#include "esp_err.h"

#include "soc/soc_caps.h"
#include "hal/cpu_types.h"
#include "hal/cpu_ll.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * 返回当前执行此代码的核心的ID。
 *
 * @return 核心id[0..SOC_CPU_CORES_NUM-1]
 */
#define cpu_hal_get_core_id()           cpu_ll_get_core_id()

/**
 * 获取堆栈指针的当前值。
 *
 * @return 当前堆栈指针
 */
#define cpu_hal_get_sp()                cpu_ll_get_sp()

/**
 * 获取每个处理器时钟周期递增的内部计数器的当前值。
 *
 * @return 循环计数；如果不支持，则返回0
 */
#define cpu_hal_get_cycle_count()       cpu_ll_get_cycle_count()

/**
 * 将给定值设置到每个处理器时钟周期递增的内部计数器中。
 */
#define cpu_hal_set_cycle_count(val)       cpu_ll_set_cycle_count(val)

/**
 * 检查CPU是否连接了某种形式的调试器。
 *
 * @return 附加了true调试器
 * @return false没有附加调试器/不支持调试器
 */
#define cpu_hal_is_debugger_attached()  cpu_ll_is_debugger_attached()

/**
 * 初始化硬件环路状态。
 */
#define cpu_hal_init_hwloop()           cpu_ll_init_hwloop()

/**
 * 触发对调试器的调用。
 */
#define cpu_hal_break()                 cpu_ll_break()

/**
 * 等待中断。
 */
#define cpu_hal_waiti()                 cpu_ll_waiti()

/**
 * 触发系统调用。
 */
#define cpu_hal_syscall(sys_nr, arg1, arg2, arg3, arg4, ret_errno)                 cpu_ll_syscall(sys_nr, arg1, arg2, arg3, arg4, ret_errno)

#if SOC_CPU_BREAKPOINTS_NUM > 0

/**
 * 在指令地址设置并启用断点。
 *
 * @note 用相同的断点ID覆盖先前设置的断点。
 *
 * @param id 要设置的断点[0..SOC_CPU_BREAKPOINTS_NUM-1]
 * @param addr 设置断点的地址
 */
void cpu_hal_set_breakpoint(int id, const void* addr);

/**
 * 清除并禁用断点。
 *
 * @param id 要清除的断点[0..SOC_CPU_BREAKPOINTS_NUM-1]
 */
void cpu_hal_clear_breakpoint(int id);

#endif // SOC_CPU_BREAKPOINTS_NUM > 0

#if SOC_CPU_WATCHPOINTS_NUM > 0

/**
 * 设置并启用观察点，指定内存范围和触发操作。
 *
 * @param id 要设置的观察点[0..SOC_CPU_WATCHPOINTS_NUM-1]
 * @param addr 起始地址
 * @param size 从起始地址到监视的字节数
 * @param trigger 对触发监视点的指定内存范围的操作（读、写、读/写）
 */
void cpu_hal_set_watchpoint(int id, const void* addr, size_t size, watchpoint_trigger_t trigger);

/**
 * 清除并禁用观察点。
 *
 * @param id 要清除的观察点[0..SOC_CPU_WATCHPOINTS_NUM-1]
 */
void cpu_hal_clear_watchpoint(int id);

#endif // SOC_CPU_WATCHPOINTS_NUM > 0

/**
 * 设置异常向量表基地址。
 *
 * @param base 将异常向量表移动到的地址
 */
void cpu_hal_set_vecbase(const void* base);

#ifdef __cplusplus
}
#endif

