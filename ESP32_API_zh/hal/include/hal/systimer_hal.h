// 版权所有2020 Espressif Systems（上海）私人有限公司
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

#include <stdint.h>
#include <stdbool.h>
#include "soc/soc_caps.h"
#include "soc/systimer_struct.h"
#include "hal/systimer_types.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    systimer_dev_t *dev;
} systimer_hal_context_t;

/**
 * @brief 初始化HAL层中的系统计时器
 */
void systimer_hal_init(systimer_hal_context_t *hal);

/**
 * @brief 启用系统计数器
 */
void systimer_hal_enable_counter(systimer_hal_context_t *hal, uint32_t counter_id);

/**
 * @brief 获取当前计数器值
 */
uint64_t systimer_hal_get_counter_value(systimer_hal_context_t *hal, uint32_t counter_id);

/**
 * @brief 获取当前时间（微秒）
 */
uint64_t systimer_hal_get_time(systimer_hal_context_t *hal, uint32_t counter_id);

/*
 * @brief 设置报警目标值（在单次模式下使用）
 */
void systimer_hal_set_alarm_target(systimer_hal_context_t *hal, uint32_t alarm_id, uint64_t target);

/**
 * @brief 设置报警周期值（用于周期模式）
 */
void systimer_hal_set_alarm_period(systimer_hal_context_t *hal, uint32_t alarm_id, uint32_t period);

/**
 * @brief 获取报警时间
 */
uint64_t systimer_hal_get_alarm_value(systimer_hal_context_t *hal, uint32_t alarm_id);

/**
 * @brief 启用报警中断
 */
void systimer_hal_enable_alarm_int(systimer_hal_context_t *hal, uint32_t alarm_id);

/**
 * @brief 选择报警模式
 */
void systimer_hal_select_alarm_mode(systimer_hal_context_t *hal, uint32_t alarm_id, systimer_alarm_mode_t mode);

/**
 * @brief 当apb时钟改变时更新systimer步骤
 */
void systimer_hal_on_apb_freq_update(systimer_hal_context_t *hal, uint32_t apb_ticks_per_us);

/**
 * @brief 向前或向后移动systimer计数器值
 */
void systimer_hal_counter_value_advance(systimer_hal_context_t *hal, uint32_t counter_id, int64_t time_us);

/**
 * @brief  将报警装置连接到所选计数器
 */
void systimer_hal_connect_alarm_counter(systimer_hal_context_t *hal, uint32_t alarm_id, uint32_t counter_id);

/**
 * @brief  设置当CPU被调试器暂停时计数器是否应停止
 */
void systimer_hal_counter_can_stall_by_cpu(systimer_hal_context_t *hal, uint32_t counter_id, uint32_t cpu_id, bool can);

#if !SOC_SYSTIMER_FIXED_TICKS_US
/**
 * @brief 为不同时钟源上的systimer计数器设置增加步长
 */
void systimer_hal_set_steps_per_tick(systimer_hal_context_t *hal, int clock_source, uint32_t steps);
#endif

#ifdef __cplusplus
}
#endif

