// 版权所有2015-2019 Espressif Systems（上海）私人有限公司
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

// 定时器组寄存器操作的LL层。
// 注意，该层中的大多数寄存器操作都是非原子操作。

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>
#include "hal/misc.h"
#include "soc/timer_periph.h"
#include "soc/timer_group_struct.h"
#include "hal/timer_types.h"
#include "hal/assert.h"

_Static_assert(TIMER_INTR_T0 == TIMG_T0_INT_CLR, "Add mapping to LL interrupt handling, since it's no longer naturally compatible with the timer_intr_t");
_Static_assert(TIMER_INTR_T1 == TIMG_T1_INT_CLR, "Add mapping to LL interrupt handling, since it's no longer naturally compatible with the timer_intr_t");
_Static_assert(TIMER_INTR_WDT == TIMG_WDT_INT_CLR, "Add mapping to LL interrupt handling, since it's no longer naturally compatible with the timer_intr_t");

// 获取计时器组实例并给出组编号
#define TIMER_LL_GET_HW(num) ((num == 0) ? (&TIMERG0) : (&TIMERG1))

/**
 * @brief 设置定时器时钟预缩放值
 *
 * @param hw 外围寄存器的起始地址。
 * @param timer_num 计时器编号
 * @param divider 预缩放值（0无效）
 *
 * @return 没有一个
 */
static inline void timer_ll_set_divider(timg_dev_t *hw, timer_idx_t timer_num, uint32_t divider)
{
    HAL_ASSERT(divider >= 2 && divider <= 65536);
    if (divider >= 65536) {
        divider = 0;
    }
    int timer_en = hw->hw_timer[timer_num].config.tx_en;
    hw->hw_timer[timer_num].config.tx_en = 0;
    HAL_FORCE_MODIFY_U32_REG_FIELD(hw->hw_timer[timer_num].config, tx_divider, divider);
    hw->hw_timer[timer_num].config.tx_en = timer_en;
}

/**
 * @brief 获取计时器时钟预缩放值
 *
 * @param hw 外围寄存器的起始地址。
 * @param timer_num 计时器编号
 * @param divider 接受预缩放值的指针
 *
 * @return 没有一个
 */
static inline void timer_ll_get_divider(timg_dev_t *hw, timer_idx_t timer_num, uint32_t *divider)
{
    uint32_t d = HAL_FORCE_READ_U32_REG_FIELD(hw->hw_timer[timer_num].config, tx_divider);
    if (d == 0) {
        d = 65536;
    } else if (d == 1) {
        d = 2;
    }
    *divider = d;
}

/**
 * @brief 将计数器值加载到时基计数器
 *
 * @param hw 外围寄存器的起始地址。
 * @param timer_num 计时器编号
 * @param load_val 计数器值
 *
 * @return 没有一个
 */
static inline void timer_ll_set_counter_value(timg_dev_t *hw, timer_idx_t timer_num, uint64_t load_val)
{
    hw->hw_timer[timer_num].loadhi.tx_load_hi = (uint32_t) (load_val >> 32);
    hw->hw_timer[timer_num].loadlo.tx_load_lo = (uint32_t) load_val;
    hw->hw_timer[timer_num].load.tx_load = 1;
}

/**
 * @brief 从时基计数器获取计数器值
 *
 * @param hw 外围寄存器的起始地址。
 * @param timer_num 计时器编号
 * @param timer_val 用于接受计数器值的指针
 *
 * @return 没有一个
 */
FORCE_INLINE_ATTR void timer_ll_get_counter_value(timg_dev_t *hw, timer_idx_t timer_num, uint64_t *timer_val)
{
    hw->hw_timer[timer_num].update.tx_update = 1;
    while (hw->hw_timer[timer_num].update.tx_update) {}
    *timer_val = ((uint64_t) hw->hw_timer[timer_num].hi.tx_hi << 32) | (hw->hw_timer[timer_num].lo.tx_lo);
}

/**
 * @brief 设置计数器模式，包括递增模式和递减模式。
 *
 * @param hw 外围寄存器的起始地址。
 * @param timer_num 计时器编号
 * @param increase_en 真至递增模式，快至递减模式
 *
 * @return 没有一个
 */
static inline void timer_ll_set_counter_increase(timg_dev_t *hw, timer_idx_t timer_num, bool increase_en)
{
    hw->hw_timer[timer_num].config.tx_increase = increase_en;
}

/**
 * @brief 获取计数器模式，包括递增模式和递减模式。
 *
 * @param hw 外围寄存器的起始地址。
 * @param timer_num 计时器编号
 *
 * @return
 *     -真增量模式
 *     -假减量模式
 */
static inline bool timer_ll_get_counter_increase(timg_dev_t *hw, timer_idx_t timer_num)
{
    return hw->hw_timer[timer_num].config.tx_increase;
}

/**
 * @brief 设置计数器状态，启用或禁用计数器。
 *
 * @param hw 外围寄存器的起始地址。
 * @param timer_num 计时器编号
 * @param counter_en True表示启用计数器，false表示禁用计数器
 *
 * @return 没有一个
 */
FORCE_INLINE_ATTR void timer_ll_set_counter_enable(timg_dev_t *hw, timer_idx_t timer_num, bool counter_en)
{
    hw->hw_timer[timer_num].config.tx_en = counter_en;
}

/**
 * @brief 获取计数器状态。
 *
 * @param hw 外围寄存器的起始地址。
 * @param timer_num 计时器编号
 *
 * @return
 *     -true启用计数器
 *     -false禁用圆锥
 */
static inline bool timer_ll_get_counter_enable(timg_dev_t *hw, timer_idx_t timer_num)
{
    return hw->hw_timer[timer_num].config.tx_en;
}

/**
 * @brief 设置自动重新加载模式。
 *
 * @param hw 外围寄存器的起始地址。
 * @param timer_num 计时器编号
 * @param auto_reload_en True表示启用自动重新加载模式，flase表示禁用自动重新加载方式
 *
 * @return 没有一个
 */
static inline void timer_ll_set_auto_reload(timg_dev_t *hw, timer_idx_t timer_num, bool auto_reload_en)
{
    hw->hw_timer[timer_num].config.tx_autoreload = auto_reload_en;
}

/**
 * @brief 获取自动重新加载模式。
 *
 * @param hw 外围寄存器的起始地址。
 * @param timer_num 计时器编号
 *
 * @return
 *     -true启用自动重新加载模式
 *     -false禁用自动重新加载模式
 */
FORCE_INLINE_ATTR bool timer_ll_get_auto_reload(timg_dev_t *hw, timer_idx_t timer_num)
{
    return hw->hw_timer[timer_num].config.tx_autoreload;
}

/**
 * @brief 设置计数器值以触发警报。
 *
 * @param hw 外围寄存器的起始地址。
 * @param timer_num 计时器编号
 * @param alarm_value 触发报警的计数器值
 *
 * @return 没有一个
 */
FORCE_INLINE_ATTR void timer_ll_set_alarm_value(timg_dev_t *hw, timer_idx_t timer_num, uint64_t alarm_value)
{
    hw->hw_timer[timer_num].alarmhi.tx_alarm_hi = (uint32_t) (alarm_value >> 32);
    hw->hw_timer[timer_num].alarmlo.tx_alarm_lo = (uint32_t) alarm_value;
}

/**
 * @brief 获取触发警报的计数器值。
 *
 * @param hw 外围寄存器的起始地址。
 * @param timer_num 计时器编号
 * @param alarm_value 接受计数器值以触发报警的指针
 *
 * @return 没有一个
 */
static inline void timer_ll_get_alarm_value(timg_dev_t *hw, timer_idx_t timer_num, uint64_t *alarm_value)
{
    *alarm_value = ((uint64_t) hw->hw_timer[timer_num].alarmhi.tx_alarm_hi << 32) | (hw->hw_timer[timer_num].alarmlo.tx_alarm_lo);
}

/**
 * @brief 设置报警状态，启用或禁用报警。
 *
 * @param hw 外围寄存器的起始地址。
 * @param timer_num 计时器编号
 * @param alarm_en True表示启用报警，false表示禁用报警
 *
 * @return 没有一个
 */
FORCE_INLINE_ATTR void timer_ll_set_alarm_enable(timg_dev_t *hw, timer_idx_t timer_num, bool alarm_en)
{
    hw->hw_timer[timer_num].config.tx_alarm_en = alarm_en;
}

/**
 * @brief 获取报警状态。
 *
 * @param hw 外围寄存器的起始地址。
 * @param timer_num 计时器编号
 *
 * @return
 *     -真启用报警
 *     -假禁用报警
 */
static inline bool timer_ll_get_alarm_enable(timg_dev_t *hw, timer_idx_t timer_num)
{
    return hw->hw_timer[timer_num].config.tx_alarm_en;
}

/**
 * @brief 启用计时器中断。
 *
 * @param hw 外围寄存器的起始地址。
 * @param timer_num 计时器编号
 *
 * @return 没有一个
 */
FORCE_INLINE_ATTR void timer_ll_intr_enable(timg_dev_t *hw, timer_idx_t timer_num)
{
    hw->int_ena_timers.val |= BIT(timer_num);
    hw->hw_timer[timer_num].config.tx_level_int_en = 1;
}

/**
 * @brief 禁用计时器中断。
 *
 * @param hw 外围寄存器的起始地址。
 * @param timer_num 计时器编号
 *
 * @return 没有一个
 */
FORCE_INLINE_ATTR void timer_ll_intr_disable(timg_dev_t *hw, timer_idx_t timer_num)
{
    hw->int_ena_timers.val &= (~BIT(timer_num));
    hw->hw_timer[timer_num].config.tx_level_int_en = 0;
}

/**
 * @brief 禁用计时器中断。
 *
 * @param hw 外围寄存器的起始地址。
 * @param timer_num 计时器编号
 *
 * @return 没有一个
 */
FORCE_INLINE_ATTR void timer_ll_clear_intr_status(timg_dev_t *hw, timer_idx_t timer_num)
{
    hw->int_clr_timers.val |= BIT(timer_num);
}

/**
 * @brief 获取中断状态。
 *
 * @param hw 外围寄存器的起始地址。
 * @param intr_status 中断状态
 *
 * @return 没有一个
 */
FORCE_INLINE_ATTR void timer_ll_get_intr_status(timg_dev_t *hw, uint32_t *intr_status)
{
    *intr_status = hw->int_st_timers.val & 0x03;
}

/**
 * @brief 获取中断原始状态。
 *
 * @param group_num 计时器组编号，0表示TIMERG0，1表示TIMERG1
 * @param intr_raw_status 中断原始状态
 *
 * @return 没有一个
 */
FORCE_INLINE_ATTR void timer_ll_get_intr_raw_status(timer_group_t group_num, uint32_t *intr_raw_status)
{
    timg_dev_t *hw = TIMER_LL_GET_HW(group_num);
    *intr_raw_status = hw->int_raw_timers.val & 0x03;
}

/**
 * @brief 设置电平中断状态，启用或禁用电平中断。
 *
 * @param hw 外围寄存器的起始地址。
 * @param timer_num 计时器编号
 * @param level_int_en True表示启用电平中断，false表示禁用电平中断
 *
 * @return 没有一个
 */
static inline void timer_ll_set_level_int_enable(timg_dev_t *hw, timer_idx_t timer_num, bool level_int_en)
{
    hw->hw_timer[timer_num].config.tx_level_int_en = level_int_en;
}

/**
 * @brief 获取电平中断状态。
 *
 * @param hw 外围寄存器的起始地址。
 * @param timer_num 计时器编号
 *
 * @return
 *     -真使能电平中断
 *     -false禁用级别中断
 */
static inline bool timer_ll_get_level_int_enable(timg_dev_t *hw, timer_idx_t timer_num)
{
    return hw->hw_timer[timer_num].config.tx_level_int_en;
}

/**
 * @brief 设置边缘中断状态，启用或禁用边缘中断。
 *
 * @param hw 外围寄存器的起始地址。
 * @param timer_num 计时器编号
 * @param edge_int_en True表示启用边缘中断，false表示禁用边缘中断
 *
 * @return 没有一个
 */
static inline void timer_ll_set_edge_int_enable(timg_dev_t *hw, timer_idx_t timer_num, bool edge_int_en)
{
    hw->hw_timer[timer_num].config.tx_edge_int_en = edge_int_en;
}

/**
 * @brief 获取边缘中断状态。
 *
 * @param hw 外围寄存器的起始地址。
 * @param timer_num 计时器编号
 *
 * @return
 *     -true启用边缘中断
 *     -false禁用边缘中断
 */
static inline bool timer_ll_get_edge_int_enable(timg_dev_t *hw, timer_idx_t timer_num)
{
    return hw->hw_timer[timer_num].config.tx_edge_int_en;
}

/**
 * @brief 获取中断状态寄存器地址。
 *
 * @param hw 外围寄存器的起始地址。
 *
 * @return uint32_t中断状态寄存器地址
 */
static inline uint32_t timer_ll_get_intr_status_reg(timg_dev_t *hw)
{
    return (uint32_t) & (hw->int_st_timers.val);
}

static inline uint32_t timer_ll_get_intr_mask_bit(timg_dev_t *hw, timer_idx_t timer_num)
{
    return (1U << timer_num);
}

/**
 * @brief 设置时钟源。
 *
 * @param hal HAL层的上下文
 * @param use_xtal_en True表示使用XTAL时钟，flase表示使用APB时钟
 *
 * @return 没有一个
 */
static inline void timer_ll_set_use_xtal(timg_dev_t *hw, timer_idx_t timer_num, bool use_xtal_en)
{
    hw->hw_timer[timer_num].config.tx_use_xtal = use_xtal_en;
}

/**
 * @brief 获取时钟源。
 *
 * @param hal HAL层的上下文
 *
 * @return
 *     -true使用XTAL时钟
 *     -错误使用APB时钟
 */
static inline bool timer_ll_get_use_xtal(timg_dev_t *hw, timer_idx_t timer_num)
{
    return hw->hw_timer[timer_num].config.tx_use_xtal;
}

#ifdef __cplusplus
}
#endif

