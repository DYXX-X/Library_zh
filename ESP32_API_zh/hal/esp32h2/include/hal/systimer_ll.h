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
#include "soc/systimer_struct.h"
#include "hal/assert.h"

#define SYSTIMER_LL_COUNTER_CLOCK       (0) // 用于“挂钟”时间的计数器
#define SYSTIMER_LL_COUNTER_OS_TICK     (1) // 用于OS刻度的计数器
#define SYSTIMER_LL_ALARM_OS_TICK_CORE0 (0) // 用于CPU核心0的OS滴答声的警报
#define SYSTIMER_LL_ALARM_CLOCK         (2) // 闹钟用于“挂钟”时间

#define SYSTIMER_LL_TICKS_PER_US        (16) // 16个系统节拍==1us

#ifdef __cplusplus
extern "C" {
#endif

// 所有这些函数都可以从链接到IRAM的ISR或HAL调用。
// 即使没有应用gcc优化，也始终内联这些函数。

/*******************时钟*************************/

__attribute__((always_inline)) static inline void systimer_ll_enable_clock(systimer_dev_t *dev, bool en)
{
    dev->conf.clk_en = en;
}

/*******************计数器*************************/

__attribute__((always_inline)) static inline void systimer_ll_enable_counter(systimer_dev_t *dev, uint32_t counter_id, bool en)
{
    if (en) {
        dev->conf.val |= 1 << (30 - counter_id);
    } else {
        dev->conf.val &= ~(1 << (30 - counter_id));
    }
}

__attribute__((always_inline)) static inline void systimer_ll_counter_can_stall_by_cpu(systimer_dev_t *dev, uint32_t counter_id, uint32_t cpu_id, bool can)
{
    if (can) {
        dev->conf.val |= 1 << ((28 - counter_id * 2) - cpu_id);
    } else {
        dev->conf.val &= ~(1 << ((28 - counter_id * 2) - cpu_id));
    }
}

__attribute__((always_inline)) static inline void systimer_ll_counter_snapshot(systimer_dev_t *dev, uint32_t counter_id)
{
    dev->unit_op[counter_id].timer_unit_update = 1;
}

__attribute__((always_inline)) static inline bool systimer_ll_is_counter_value_valid(systimer_dev_t *dev, uint32_t counter_id)
{
    return dev->unit_op[counter_id].timer_unit_value_valid;
}

__attribute__((always_inline)) static inline void systimer_ll_set_counter_value(systimer_dev_t *dev, uint32_t counter_id, uint64_t value)
{
    dev->unit_load_val[counter_id].hi.timer_unit_load_hi = value >> 32;
    dev->unit_load_val[counter_id].lo.timer_unit_load_lo = value & 0xFFFFFFFF;
}

__attribute__((always_inline)) static inline uint32_t systimer_ll_get_counter_value_low(systimer_dev_t *dev, uint32_t counter_id)
{
    return dev->unit_val[counter_id].lo.timer_unit_value_lo;
}

__attribute__((always_inline)) static inline uint32_t systimer_ll_get_counter_value_high(systimer_dev_t *dev, uint32_t counter_id)
{
    return dev->unit_val[counter_id].hi.timer_unit_value_hi;
}

__attribute__((always_inline)) static inline void systimer_ll_apply_counter_value(systimer_dev_t *dev, uint32_t counter_id)
{
    dev->unit_load[counter_id].val = 0x01;
}

/*******************报警*************************/

__attribute__((always_inline)) static inline void systimer_ll_set_alarm_target(systimer_dev_t *dev, uint32_t alarm_id, uint64_t value)
{
    dev->target_val[alarm_id].hi.timer_target_hi = value >> 32;
    dev->target_val[alarm_id].lo.timer_target_lo = value & 0xFFFFFFFF;
}

__attribute__((always_inline)) static inline uint64_t systimer_ll_get_alarm_target(systimer_dev_t *dev, uint32_t alarm_id)
{
    return ((uint64_t)(dev->target_val[alarm_id].hi.timer_target_hi) << 32) | dev->target_val[alarm_id].lo.timer_target_lo;
}

__attribute__((always_inline)) static inline void systimer_ll_connect_alarm_counter(systimer_dev_t *dev, uint32_t alarm_id, uint32_t counter_id)
{
    dev->target_conf[alarm_id].target_timer_unit_sel = counter_id;
}

__attribute__((always_inline)) static inline void systimer_ll_enable_alarm_oneshot(systimer_dev_t *dev, uint32_t alarm_id)
{
    dev->target_conf[alarm_id].target_period_mode = 0;
}

__attribute__((always_inline)) static inline void systimer_ll_enable_alarm_period(systimer_dev_t *dev, uint32_t alarm_id)
{
    dev->target_conf[alarm_id].target_period_mode = 1;
}

__attribute__((always_inline)) static inline void systimer_ll_set_alarm_period(systimer_dev_t *dev, uint32_t alarm_id, uint32_t period)
{
    HAL_ASSERT(period < (1 << 26));
    dev->target_conf[alarm_id].target_period = period;
}

__attribute__((always_inline)) static inline uint32_t systimer_ll_get_alarm_period(systimer_dev_t *dev, uint32_t alarm_id)
{
    return dev->target_conf[alarm_id].target_period;
}

__attribute__((always_inline)) static inline void systimer_ll_apply_alarm_value(systimer_dev_t *dev, uint32_t alarm_id)
{
    dev->comp_load[alarm_id].val = 0x01;
}

__attribute__((always_inline)) static inline void systimer_ll_enable_alarm(systimer_dev_t *dev, uint32_t alarm_id, bool en)
{
    if (en) {
        dev->conf.val |= 1 << (24 - alarm_id);
    } else {
        dev->conf.val &= ~(1 << (24 - alarm_id));
    }
}

/*******************中断*************************/

__attribute__((always_inline)) static inline void systimer_ll_enable_alarm_int(systimer_dev_t *dev, uint32_t alarm_id, bool en)
{
    if (en) {
        dev->int_ena.val |= 1 << alarm_id;
    } else {
        dev->int_ena.val &= ~(1 << alarm_id);
    }
}

__attribute__((always_inline)) static inline bool systimer_ll_is_alarm_int_fired(systimer_dev_t *dev, uint32_t alarm_id)
{
    return dev->int_st.val & (1 << alarm_id);
}

__attribute__((always_inline)) static inline void systimer_ll_clear_alarm_int(systimer_dev_t *dev, uint32_t alarm_id)
{
    dev->int_clr.val |= 1 << alarm_id;
}

#ifdef __cplusplus
}
#endif

