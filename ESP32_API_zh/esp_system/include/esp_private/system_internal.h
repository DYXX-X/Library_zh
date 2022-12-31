// 版权所有2018 Espressif Systems（上海）私人有限公司
//
// 根据Apache许可证2.0版（“许可证”）获得许可；
// 除非符合许可证，否则不得使用此文件。
// 您可以在以下地址获取许可证副本：
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// 除非适用法律要求或书面同意，软件
// 根据许可证分发的内容是按“原样”分发的，
// 无任何明示或暗示的保证或条件。
// 有关管理权限和
// 许可证下的限制。

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "esp_system.h"

#define MWDT0_TICK_PRESCALER    40000
#define MWDT0_TICKS_PER_US      500
#define MWDT1_TICK_PRESCALER    40000
#define MWDT1_TICKS_PER_US      500

/**
 * @brief  重新启动PRO和APP CPU的内部功能。
 *
 * @note 不应从FreeRTOS应用程序调用此函数。请改用esp_restart。
 *
 * 这是esp_restart调用的内部函数。它由紧急处理程序和断电检测器中断直接调用。
 */
void esp_restart_noos(void) __attribute__ ((noreturn));

/**
 * @brief 与esp_restart_noos类似，但重置所有数字外设。
 */
void esp_restart_noos_dig(void) __attribute__ ((noreturn));

/**
 * @brief  设置重置原因提示的内部函数
 *
 * 当执行软件重置时，使用提示来区分不同的重置原因。
 *
 * 提示存储在RTC存储寄存器RTC_RESET_CAUSE_REG中。
 *
 * @param hint  实际重置原因所需的esp_reset_reason_t值
 */
void esp_reset_reason_set_hint(esp_reset_reason_t hint);

/**
 * @brief  获取重置提示值的内部函数
 * @return  -使用esp_Reset_reason_set_hint函数重置先前存储在RTC_Reset_CAUSE_REG中的提示值
 *          -如果RTC_RESET_CAUSE_REG中的值无效，则为ESP_RST_UNKNOWN
 */
esp_reset_reason_t esp_reset_reason_get_hint(void);

/**
 * @brief 获取启动后的时间（以微秒为单位）
 *
 * @returns 自g_startup_time起的时间；无论使用什么基础计时器，系统时间提供程序都应该固定定义。
 */
int64_t esp_system_get_time(void);

/**
 * @brief 获取“esp_system_Get_time”返回的时间分辨率。
 *
 * @returns 以纳秒为单位的分辨率
 */
uint32_t esp_system_get_time_resolution(void);

#ifdef __cplusplus
}
#endif

