/*
 * SPDX文件版权文本：2015-2021浓缩咖啡系统（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */

#pragma once
#include <stdint.h>
#include "sdkconfig.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @file 睡眠_注意力.h
 *
 * 此文件包含轻雨夹模式下与内存保留相关的函数的声明。
 */

#if SOC_PM_SUPPORT_CPU_PD

/**
 * @brief 是否允许关闭cpu电源域。
 *
 * 在轻睡眠模式下，只有当系统能够为cpu保留提供足够的内存时，cpu电源域才能关闭。
 */
bool cpu_domain_pd_allowed(void);

#endif

#if SOC_PM_SUPPORT_CPU_PD || SOC_PM_SUPPORT_TAGMEM_PD

/**
 * @brief 启用某些模块的内存保留。
 *
 * 在轻睡眠模式下，在系统进入睡眠状态之前，启用CPU和I/O缓存标签内存等模块的内存保留。
 */
void sleep_enable_memory_retention(void);

/**
 * @brief 禁用某些模块的内存保留。
 *
 * 在轻睡眠模式下，在系统退出睡眠后，禁用模块的内存保留，如CPU和I/O缓存标签内存。
 */
void sleep_disable_memory_retention(void);

#endif // SOC_PM_SUPPORT_CPU_PD || SOC_PM_SUPPORT_TAGMEM_PD

#ifdef __cplusplus
}
#endif

