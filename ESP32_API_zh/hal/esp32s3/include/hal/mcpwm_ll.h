/*
 * SPDX文件版权文本：2015-2021浓缩咖啡系统（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */

/*******************************************************************************
 * 注意：hal不是公共api，不要在应用程序代码中使用。请参阅自述文件。在hal/include/hal/readme.md中的md
 ******************************************************************************/

// ESP32-S3 MCPWM寄存器操作的LL层

#pragma once

#include <stdbool.h>
#include "hal/misc.h"
#include "soc/soc_caps.h"
#include "soc/mcpwm_struct.h"
#include "hal/mcpwm_types.h"
#include "hal/assert.h"

#ifdef __cplusplus
extern "C" {
#endif

///获取外围寄存器的地址
#define MCPWM_LL_GET_HW(ID) (((ID) == 0) ? &MCPWM0 : &MCPWM1)
#define MCPWM_LL_MAX_CAPTURE_PRESCALE 255
#define MCPWM_LL_MAX_COMPARE_VALUE    65535
#define MCPWM_LL_MAX_DEAD_DELAY       65535
#define MCPWM_LL_MAX_PHASE_VALUE      65535

/*********************组寄存器*******************/

// 设置/获取组时钟：PWM_clk=clk_160M/（预缩放+1）
static inline void mcpwm_ll_group_set_clock_prescale(mcpwm_dev_t *mcpwm, int pre_scale)
{
    // 如果编译器将32位指令（例如s32i）优化为8位指令（如s8i，不允许访问寄存器）
    // 我们自己负责“读-修改-写”过程。
    mcpwm_clk_cfg_reg_t clkcfg = mcpwm->clk_cfg;
    clkcfg.clk_prescale = pre_scale - 1;
    mcpwm->clk_cfg = clkcfg;
}

static inline uint32_t mcpwm_ll_group_get_clock_prescale(mcpwm_dev_t *mcpwm)
{
    mcpwm_clk_cfg_reg_t clkcfg = mcpwm->clk_cfg;
    return clkcfg.clk_prescale + 1;
}

static inline void mcpwm_ll_group_enable_shadow_mode(mcpwm_dev_t *mcpwm)
{
    mcpwm->update_cfg.global_up_en = 1;
    // 应启用MCPWM运算符中活动寄存器的更新
    mcpwm->update_cfg.op0_up_en = 1;
    mcpwm->update_cfg.op1_up_en = 1;
    mcpwm->update_cfg.op2_up_en = 1;
}

static inline void mcpwm_ll_group_flush_shadow(mcpwm_dev_t *mcpwm)
{
    // 切换可以触发MCPWM中所有活动寄存器的强制更新，即shadow->active
    mcpwm->update_cfg.global_force_up = ~mcpwm->update_cfg.global_force_up;
}

/*********************中断寄存器*******************/

static inline uint32_t mcpwm_ll_intr_get_status(mcpwm_dev_t *mcpwm)
{
    return mcpwm->int_st.val;
}

static inline void mcpwm_ll_intr_clear_status(mcpwm_dev_t *mcpwm, uint32_t intr_mask)
{
    mcpwm->int_clr.val = intr_mask;
}

static inline void mcpwm_ll_intr_disable_all(mcpwm_dev_t *mcpwm)
{
    mcpwm->int_ena.val = 0;
}

////////////获取每个事件的中断状态////////////////

static inline uint32_t mcpwm_ll_intr_get_timer_stop_status(mcpwm_dev_t *mcpwm)
{
    return (mcpwm->int_st.val >> 0) & 0x07;
}

static inline uint32_t mcpwm_ll_intr_get_timer_tez_status(mcpwm_dev_t *mcpwm)
{
    return (mcpwm->int_st.val >> 3) & 0x07;
}

static inline uint32_t mcpwm_ll_intr_get_timer_tep_status(mcpwm_dev_t *mcpwm)
{
    return (mcpwm->int_st.val >> 6) & 0x07;
}

static inline uint32_t mcpwm_ll_intr_get_fault_enter_status(mcpwm_dev_t *mcpwm)
{
    return (mcpwm->int_st.val >> 9) & 0x07;
}

static inline uint32_t mcpwm_ll_intr_get_fault_exit_status(mcpwm_dev_t *mcpwm)
{
    return (mcpwm->int_st.val >> 12) & 0x07;
}

static inline uint32_t mcpwm_ll_intr_get_compare_status(mcpwm_dev_t *mcpwm, uint32_t cmp_id)
{
    return (mcpwm->int_st.val >> (15 + cmp_id * 3)) & 0x07;
}

static inline uint32_t mcpwm_ll_intr_get_trip_cbc_status(mcpwm_dev_t *mcpwm)
{
    return (mcpwm->int_st.val >> 21) & 0x07;
}

static inline uint32_t mcpwm_ll_intr_get_trip_ost_status(mcpwm_dev_t *mcpwm)
{
    return (mcpwm->int_st.val >> 24) & 0x07;
}

__attribute__((always_inline))
static inline uint32_t mcpwm_ll_intr_get_capture_status(mcpwm_dev_t *mcpwm)
{
    return (mcpwm->int_st.val >> 27) & 0x07;
}

////////////清除每个事件的中断状态////////////////

static inline void mcpwm_ll_intr_clear_timer_stop_status(mcpwm_dev_t *mcpwm, uint32_t timer_mask)
{
    mcpwm->int_clr.val = (timer_mask & 0x07) << 0;
}

static inline void mcpwm_ll_intr_clear_timer_tez_status(mcpwm_dev_t *mcpwm, uint32_t timer_mask)
{
    mcpwm->int_clr.val = (timer_mask & 0x07) << 3;
}

static inline void mcpwm_ll_intr_clear_timer_tep_status(mcpwm_dev_t *mcpwm, uint32_t timer_mask)
{
    mcpwm->int_clr.val = (timer_mask & 0x07) << 6;
}

static inline void mcpwm_ll_intr_clear_fault_enter_status(mcpwm_dev_t *mcpwm, uint32_t fault_mask)
{
    mcpwm->int_clr.val = (fault_mask & 0x07) << 9;
}

static inline void mcpwm_ll_intr_clear_fault_exit_status(mcpwm_dev_t *mcpwm, uint32_t fault_mask)
{
    mcpwm->int_clr.val = (fault_mask & 0x07) << 12;
}

static inline void mcpwm_ll_intr_clear_compare_status(mcpwm_dev_t *mcpwm, uint32_t operator_mask, uint32_t cmp_id)
{
    mcpwm->int_clr.val = (operator_mask & 0x07) << (15 + cmp_id * 3);
}

static inline void mcpwm_ll_intr_clear_trip_cbc_status(mcpwm_dev_t *mcpwm, uint32_t cbc_mask)
{
    mcpwm->int_clr.val = (cbc_mask & 0x07) << 21;
}

static inline void mcpwm_ll_intr_clear_trip_ost_status(mcpwm_dev_t *mcpwm, uint32_t ost_mask)
{
    mcpwm->int_clr.val = (ost_mask & 0x07) << 24;
}

__attribute__((always_inline))
static inline void mcpwm_ll_intr_clear_capture_status(mcpwm_dev_t *mcpwm, uint32_t capture_mask)
{
    mcpwm->int_clr.val = (capture_mask & 0x07) << 27;
}

////////////为每个事件启用中断////////////////

static inline void mcpwm_ll_intr_enable_timer_stop(mcpwm_dev_t *mcpwm, uint32_t timer_id, bool enable)
{
    if (enable) {
        mcpwm->int_ena.val |= 1 << (timer_id + 0);
    } else {
        mcpwm->int_ena.val &= ~(1 << (timer_id + 0));
    }
}

static inline void mcpwm_ll_intr_enable_timer_tez(mcpwm_dev_t *mcpwm, uint32_t timer_id, bool enable)
{
    if (enable) {
        mcpwm->int_ena.val |= 1 << (timer_id + 3);
    } else {
        mcpwm->int_ena.val &= ~(1 << (timer_id + 3));
    }
}

static inline void mcpwm_ll_intr_enable_timer_tep(mcpwm_dev_t *mcpwm, uint32_t timer_id, bool enable)
{
    if (enable) {
        mcpwm->int_ena.val |= 1 << (timer_id + 6);
    } else {
        mcpwm->int_ena.val &= ~(1 << (timer_id + 6));
    }
}

static inline void mcpwm_ll_intr_enable_fault_enter(mcpwm_dev_t *mcpwm, uint32_t fault_id, bool enable)
{
    if (enable) {
        mcpwm->int_ena.val |= 1 << (9 + fault_id);  // 进入故障中断
    } else {
        mcpwm->int_ena.val &= ~(1 << (9 + fault_id));
    }
}

static inline void mcpwm_ll_intr_enable_fault_exit(mcpwm_dev_t *mcpwm, uint32_t fault_id, bool enable)
{
    if (enable) {
        mcpwm->int_ena.val |= 1 << (12 + fault_id); // 退出故障中断
    } else {
        mcpwm->int_ena.val &= ~(1 << (12 + fault_id));
    }
}

static inline void mcpwm_ll_intr_enable_compare(mcpwm_dev_t *mcpwm, uint32_t operator_id, uint32_t cmp_id, bool enable)
{
    if (enable) {
        mcpwm->int_ena.val |= (1 << (15 + cmp_id * 3 + operator_id));
    } else {
        mcpwm->int_ena.val &= ~(1 << (15 + cmp_id * 3 + operator_id));
    }
}

static inline void mcpwm_ll_intr_enable_trip_cbc(mcpwm_dev_t *mcpwm, uint32_t operator_id, bool enable)
{
    if (enable) {
        mcpwm->int_ena.val |= (1 << (21 + operator_id));
    } else {
        mcpwm->int_ena.val &= ~(1 << (21 + operator_id));
    }
}

static inline void mcpwm_ll_intr_enable_trip_ost(mcpwm_dev_t *mcpwm, uint32_t operator_id, bool enable)
{
    if (enable) {
        mcpwm->int_ena.val |= (1 << (24 + operator_id));
    } else {
        mcpwm->int_ena.val &= ~(1 << (24 + operator_id));
    }
}

static inline void mcpwm_ll_intr_enable_capture(mcpwm_dev_t *mcpwm, uint32_t capture_id, bool enable)
{
    if (enable) {
        mcpwm->int_ena.val |= 1 << (27 + capture_id);
    } else {
        mcpwm->int_ena.val &= ~(1 << (27 + capture_id));
    }
}

/*********************计时器寄存器*******************/

static inline void mcpwm_ll_timer_set_clock_prescale(mcpwm_dev_t *mcpwm, int timer_id, uint32_t prescale)
{
    // 如果编译器将32位指令（例如s32i）优化为8位指令（如s8i，不允许访问寄存器）
    // 我们自己负责“读-修改-写”过程。
    mcpwm_timer_cfg0_reg_t cfg0 = mcpwm->timer[timer_id].timer_cfg0;
    cfg0.timer_prescale = prescale - 1;
    mcpwm->timer[timer_id].timer_cfg0 = cfg0;
}

static inline uint32_t mcpwm_ll_timer_get_clock_prescale(mcpwm_dev_t *mcpwm, int timer_id)
{
    mcpwm_timer_cfg0_reg_t cfg0 = mcpwm->timer[timer_id].timer_cfg0;
    return cfg0.timer_prescale + 1;
}

static inline void mcpwm_ll_timer_set_peak(mcpwm_dev_t *mcpwm, int timer_id, uint32_t peak, bool symmetric)
{
    if (!symmetric) { // 在不对称模式下，周期=[0，峰值1]
        HAL_FORCE_MODIFY_U32_REG_FIELD(mcpwm->timer[timer_id].timer_cfg0, timer_period, peak - 1);
    } else { // 在对称模式下，周期=[0，峰值-1]+[峰值，1]
        HAL_FORCE_MODIFY_U32_REG_FIELD(mcpwm->timer[timer_id].timer_cfg0, timer_period, peak);
    }
}

static inline uint32_t mcpwm_ll_timer_get_peak(mcpwm_dev_t *mcpwm, int timer_id, bool symmetric)
{
    // 不对称模式
    if (!symmetric) {
        return HAL_FORCE_READ_U32_REG_FIELD(mcpwm->timer[timer_id].timer_cfg0, timer_period) + 1;
    }
    // 对称模式
    return HAL_FORCE_READ_U32_REG_FIELD(mcpwm->timer[timer_id].timer_cfg0, timer_period);
}

static inline void mcpwm_ll_timer_update_period_at_once(mcpwm_dev_t *mcpwm, int timer_id)
{
    mcpwm->timer[timer_id].timer_cfg0.timer_period_upmethod  = 0;
}

static inline void mcpwm_ll_timer_enable_update_period_on_tez(mcpwm_dev_t *mcpwm, int timer_id, bool enable)
{
    if (enable) {
        mcpwm->timer[timer_id].timer_cfg0.timer_period_upmethod  |= 0x01;
    } else {
        mcpwm->timer[timer_id].timer_cfg0.timer_period_upmethod  &= ~0x01;
    }
}

static inline void mcpwm_ll_timer_enable_update_period_on_sync(mcpwm_dev_t *mcpwm, int timer_id, bool enable)
{
    if (enable) {
        mcpwm->timer[timer_id].timer_cfg0.timer_period_upmethod |= 0x02;
    } else {
        mcpwm->timer[timer_id].timer_cfg0.timer_period_upmethod &= ~0x02;
    }
}

static inline void mcpwm_ll_timer_set_count_mode(mcpwm_dev_t *mcpwm, int timer_id, mcpwm_timer_count_mode_t mode)
{
    switch (mode) {
    case MCPWM_TIMER_COUNT_MODE_PAUSE:
        mcpwm->timer[timer_id].timer_cfg1.timer_mod = 0;
        break;
    case MCPWM_TIMER_COUNT_MODE_UP:
        mcpwm->timer[timer_id].timer_cfg1.timer_mod = 1;
        break;
    case MCPWM_TIMER_COUNT_MODE_DOWN:
        mcpwm->timer[timer_id].timer_cfg1.timer_mod = 2;
        break;
    case MCPWM_TIMER_COUNT_MODE_UP_DOWN:
        mcpwm->timer[timer_id].timer_cfg1.timer_mod = 3;
        break;
    }
}

static inline mcpwm_timer_count_mode_t mcpwm_ll_timer_get_count_mode(mcpwm_dev_t *mcpwm, int timer_id)
{
    switch (mcpwm->timer[timer_id].timer_cfg1.timer_mod) {
    case 1:
        return MCPWM_TIMER_COUNT_MODE_UP;
    case 2:
        return MCPWM_TIMER_COUNT_MODE_DOWN;
    case 3:
        return MCPWM_TIMER_COUNT_MODE_UP_DOWN;
    case 0:
    default:
        return MCPWM_TIMER_COUNT_MODE_PAUSE;
    }
}

static inline void mcpwm_ll_timer_set_execute_command(mcpwm_dev_t *mcpwm, int timer_id, mcpwm_timer_execute_cmd_t cmd)
{
    switch (cmd) {
    case MCPWM_TIMER_STOP_AT_ZERO:
        mcpwm->timer[timer_id].timer_cfg1.timer_start = 0;
        break;
    case MCPWM_TIMER_STOP_AT_PEAK:
        mcpwm->timer[timer_id].timer_cfg1.timer_start = 1;
        break;
    case MCPWM_TIMER_START_NO_STOP:
        mcpwm->timer[timer_id].timer_cfg1.timer_start = 2;
        break;
    case MCPWM_TIMER_START_STOP_AT_ZERO:
        mcpwm->timer[timer_id].timer_cfg1.timer_start = 3;
        break;
    case MCPWM_TIMER_START_STOP_AT_PEAK:
        mcpwm->timer[timer_id].timer_cfg1.timer_start = 4;
        break;
    }
}

static inline uint32_t mcpwm_ll_timer_get_count_value(mcpwm_dev_t *mcpwm, int timer_id)
{
    // 地位value保存“下一个计数值”，因此需要在此进行额外的舍入以根据计数模式获得当前计数值
    // 计时器已暂停
    if (mcpwm->timer[timer_id].timer_cfg1.timer_mod == 0) {
        return HAL_FORCE_READ_U32_REG_FIELD(mcpwm->timer[timer_id].timer_status, timer_value);
    }
    if (mcpwm->timer[timer_id].timer_status.timer_direction) { // 向下的方向
        return (HAL_FORCE_READ_U32_REG_FIELD(mcpwm->timer[timer_id].timer_status, timer_value) + 1) %
               (HAL_FORCE_READ_U32_REG_FIELD(mcpwm->timer[timer_id].timer_cfg0, timer_period) + 1);
    }
    // 向上方向
    return (HAL_FORCE_READ_U32_REG_FIELD(mcpwm->timer[timer_id].timer_status, timer_value) +
            HAL_FORCE_READ_U32_REG_FIELD(mcpwm->timer[timer_id].timer_cfg0, timer_period)) %
           (HAL_FORCE_READ_U32_REG_FIELD(mcpwm->timer[timer_id].timer_cfg0, timer_period) + 1);
}

static inline mcpwm_timer_direction_t mcpwm_ll_timer_get_count_direction(mcpwm_dev_t *mcpwm, int timer_id)
{
    return mcpwm->timer[timer_id].timer_status.timer_direction ? MCPWM_TIMER_DIRECTION_DOWN : MCPWM_TIMER_DIRECTION_UP;
}

static inline void mcpwm_ll_timer_enable_sync_input(mcpwm_dev_t *mcpwm, int timer_id, bool enable)
{
    mcpwm->timer[timer_id].timer_sync.timer_synci_en = enable;
}

static inline void mcpwm_ll_timer_sync_out_penetrate(mcpwm_dev_t *mcpwm, int timer_id)
{
    // sync_out被选择为sync_in
    mcpwm->timer[timer_id].timer_sync.timer_synco_sel = 0;
}

static inline void mcpwm_ll_timer_sync_out_on_timer_event(mcpwm_dev_t *mcpwm, int timer_id, mcpwm_timer_event_t event)
{
    if (event == MCPWM_TIMER_EVENT_ZERO) {
        mcpwm->timer[timer_id].timer_sync.timer_synco_sel = 1;
    } else if (event == MCPWM_TIMER_EVENT_PEAK) {
        mcpwm->timer[timer_id].timer_sync.timer_synco_sel = 2;
    } else {
        HAL_ASSERT(false && "unknown sync out event");
    }
}

static inline void mcpwm_ll_timer_disable_sync_out(mcpwm_dev_t *mcpwm, int timer_id)
{
    // sync_out将始终为零
    mcpwm->timer[timer_id].timer_sync.timer_synco_sel = 3;
}

static inline void mcpwm_ll_timer_trigger_soft_sync(mcpwm_dev_t *mcpwm, int timer_id)
{
    mcpwm->timer[timer_id].timer_sync.timer_sync_sw = ~mcpwm->timer[timer_id].timer_sync.timer_sync_sw;
}

static inline void mcpwm_ll_timer_set_sync_phase_value(mcpwm_dev_t *mcpwm, int timer_id, uint32_t phase_value)
{
    HAL_FORCE_MODIFY_U32_REG_FIELD(mcpwm->timer[timer_id].timer_sync, timer_phase, phase_value);
}

static inline void mcpwm_ll_timer_set_sync_phase_direction(mcpwm_dev_t *mcpwm, int timer_id, mcpwm_timer_direction_t direction)
{
    mcpwm->timer[timer_id].timer_sync.timer_phase_direction = direction;
}

static inline void mcpwm_ll_timer_set_gpio_synchro(mcpwm_dev_t *mcpwm, int timer, int gpio_sync_id)
{
    mcpwm->timer_synci_cfg.val &= ~(0x07 << (timer * 3));
    mcpwm->timer_synci_cfg.val |= (gpio_sync_id + 4) << (timer * 3);
}

static inline void mcpwm_ll_timer_set_timer_synchro(mcpwm_dev_t *mcpwm, int timer, int timer_sync_id)
{
    mcpwm->timer_synci_cfg.val &= ~(0x07 << (timer * 3));
    mcpwm->timer_synci_cfg.val |= (timer_sync_id + 1) << (timer * 3);
}

static inline void mcpwm_ll_timer_set_soft_synchro(mcpwm_dev_t *mcpwm, int timer)
{
    // 未选择同步输入，但软件同步仍然可以工作
    mcpwm->timer_synci_cfg.val &= ~(0x07 << (timer * 3));
}

static inline void mcpwm_ll_invert_gpio_synchro(mcpwm_dev_t *mcpwm, int sync_id, bool invert)
{
    if (invert) {
        mcpwm->timer_synci_cfg.val |= 1 << (sync_id + 9);
    } else {
        mcpwm->timer_synci_cfg.val &= ~(1 << (sync_id + 9));
    }
}

/*********************操作员寄存器*******************/

static inline void mcpwm_ll_operator_flush_shadow(mcpwm_dev_t *mcpwm, int operator_id)
{
    mcpwm->update_cfg.val ^= (1 << (2 * operator_id + 3));
}

static inline void mcpwm_ll_operator_select_timer(mcpwm_dev_t *mcpwm, int operator_id, int timer_id)
{
    if (operator_id == 0) {
        mcpwm->operator_timersel.operator0_timersel = timer_id;
    } else if (operator_id == 1) {
        mcpwm->operator_timersel.operator1_timersel = timer_id;
    } else {
        mcpwm->operator_timersel.operator2_timersel = timer_id;
    }
}

static inline void mcpwm_ll_operator_update_compare_at_once(mcpwm_dev_t *mcpwm, int operator_id, int compare_id)
{
    mcpwm->operators[operator_id].gen_stmp_cfg.val &= ~(0x0F << (4 * compare_id));
}

static inline void mcpwm_ll_operator_enable_update_compare_on_tez(mcpwm_dev_t *mcpwm, int operator_id, int compare_id, bool enable)
{
    if (enable) {
        mcpwm->operators[operator_id].gen_stmp_cfg.val |= (1 << 0) << (4 * compare_id);
    } else {
        mcpwm->operators[operator_id].gen_stmp_cfg.val &= ~((1 << 0) << (4 * compare_id));
    }
}

static inline void mcpwm_ll_operator_enable_update_compare_on_tep(mcpwm_dev_t *mcpwm, int operator_id, int compare_id, bool enable)
{
    if (enable) {
        mcpwm->operators[operator_id].gen_stmp_cfg.val |= (1 << 1) << (4 * compare_id);
    } else {
        mcpwm->operators[operator_id].gen_stmp_cfg.val &= ~((1 << 1) << (4 * compare_id));
    }
}

static inline void mcpwm_ll_operator_enable_update_compare_on_sync(mcpwm_dev_t *mcpwm, int operator_id, int compare_id, bool enable)
{
    if (enable) {
        mcpwm->operators[operator_id].gen_stmp_cfg.val |= (1 << 2) << (4 * compare_id);
    } else {
        mcpwm->operators[operator_id].gen_stmp_cfg.val &= ~((1 << 2) << (4 * compare_id));
    }
}

static inline void mcpwm_ll_operator_set_compare_value(mcpwm_dev_t *mcpwm, int operator_id, int compare_id, uint32_t compare_value)
{
    HAL_FORCE_MODIFY_U32_REG_FIELD(mcpwm->operators[operator_id].timestamp[compare_id], gen, compare_value);
}

static inline uint32_t mcpwm_ll_operator_get_compare_value(mcpwm_dev_t *mcpwm, int operator_id, int compare_id)
{
    return HAL_FORCE_READ_U32_REG_FIELD(mcpwm->operators[operator_id].timestamp[compare_id], gen);
}

static inline void mcpwm_ll_operator_update_action_at_once(mcpwm_dev_t *mcpwm, int operator_id)
{
    mcpwm->operators[operator_id].gen_cfg0.gen_cfg_upmethod = 0;
}

static inline void mcpwm_ll_operator_enable_update_action_on_tez(mcpwm_dev_t *mcpwm, int operator_id, bool enable)
{
    if (enable) {
        mcpwm->operators[operator_id].gen_cfg0.gen_cfg_upmethod |= 1 << 0;
    } else {
        mcpwm->operators[operator_id].gen_cfg0.gen_cfg_upmethod &= ~(1 << 0);
    }
}

static inline void mcpwm_ll_operator_enable_update_action_on_tep(mcpwm_dev_t *mcpwm, int operator_id, bool enable)
{
    if (enable) {
        mcpwm->operators[operator_id].gen_cfg0.gen_cfg_upmethod |= 1 << 1;
    } else {
        mcpwm->operators[operator_id].gen_cfg0.gen_cfg_upmethod &= ~(1 << 1);
    }
}

static inline void mcpwm_ll_operator_enable_update_action_on_sync(mcpwm_dev_t *mcpwm, int operator_id, bool enable)
{
    if (enable) {
        mcpwm->operators[operator_id].gen_cfg0.gen_cfg_upmethod |= 1 << 2;
    } else {
        mcpwm->operators[operator_id].gen_cfg0.gen_cfg_upmethod &= ~(1 << 2);
    }
}

static inline void mcpwm_ll_operator_set_trigger_gpio_fault(mcpwm_dev_t *mcpwm, int operator_id, int trig_id, int fault_id)
{
    mcpwm->operators[operator_id].gen_cfg0.val &= ~(0x07 << (4 + 3 * trig_id));
    mcpwm->operators[operator_id].gen_cfg0.val |= (fault_id << (4 + 3 * trig_id));
}

static inline void mcpwm_ll_operator_set_trigger_timer_sync(mcpwm_dev_t *mcpwm, int operator_id, int trig_id)
{
    // 此处的计时器不可选择，必须是与操作员连接的计时器
    mcpwm->operators[operator_id].gen_cfg0.val &= ~(0x07 << (4 + 3 * trig_id));
    mcpwm->operators[operator_id].gen_cfg0.val |= (3 << (4 + 3 * trig_id));
}

/*********************发电机寄存器*******************/

static inline void mcpwm_ll_generator_reset_actions(mcpwm_dev_t *mcpwm, int operator_id, int generator_id)
{
    mcpwm->operators[operator_id].generator[generator_id].val = 0;
}

static inline void mcpwm_ll_generator_set_action_on_timer_event(mcpwm_dev_t *mcpwm, int operator_id, int generator_id,
        mcpwm_timer_direction_t direction, mcpwm_timer_event_t event, mcpwm_generator_action_t action)
{
    if (direction == MCPWM_TIMER_DIRECTION_UP) { // utez、utep
        mcpwm->operators[operator_id].generator[generator_id].val &= ~(0x03 << (event * 2));
        mcpwm->operators[operator_id].generator[generator_id].val |= action << (event * 2);
    } else if (direction == MCPWM_TIMER_DIRECTION_DOWN) { // dtez、dtep
        mcpwm->operators[operator_id].generator[generator_id].val &= ~(0x03 << (event * 2 + 12));
        mcpwm->operators[operator_id].generator[generator_id].val |= action << (event * 2 + 12);
    }
}

static inline void mcpwm_ll_generator_set_action_on_compare_event(mcpwm_dev_t *mcpwm, int operator_id, int generator_id,
        mcpwm_timer_direction_t direction, int cmp_id, int action)
{
    if (direction == MCPWM_TIMER_DIRECTION_UP) { // utea、uteb
        mcpwm->operators[operator_id].generator[generator_id].val &= ~(0x03 << (cmp_id * 2 + 4));
        mcpwm->operators[operator_id].generator[generator_id].val |= action << (cmp_id * 2 + 4);
    } else if (direction == MCPWM_TIMER_DIRECTION_DOWN) { // dtea、dteb
        mcpwm->operators[operator_id].generator[generator_id].val &= ~(0x03 << (cmp_id * 2 + 16));
        mcpwm->operators[operator_id].generator[generator_id].val |= action << (cmp_id * 2 + 16);
    }
}

static inline void mcpwm_ll_generator_set_action_on_trigger_event(mcpwm_dev_t *mcpwm, int operator_id, int generator_id,
        mcpwm_timer_direction_t direction, int trig_id, int action)
{
    if (direction == MCPWM_TIMER_DIRECTION_UP) { // ut0，ut1
        mcpwm->operators[operator_id].generator[generator_id].val &= ~(0x03 << (trig_id * 2 + 8));
        mcpwm->operators[operator_id].generator[generator_id].val |= action << (trig_id * 2 + 8);
    } else if (direction == MCPWM_TIMER_DIRECTION_DOWN) { // 分0秒，分1秒
        mcpwm->operators[operator_id].generator[generator_id].val &= ~(0x03 << (trig_id * 2 + 20));
        mcpwm->operators[operator_id].generator[generator_id].val |= action << (trig_id * 2 + 20);
    }
}

static inline void mcpwm_ll_gen_trigger_noncontinue_force_action(mcpwm_dev_t *mcpwm, int operator_id, int generator_id)
{
    if (generator_id == 0) {
        mcpwm->operators[operator_id].gen_force.gen_a_nciforce = ~mcpwm->operators[operator_id].gen_force.gen_a_nciforce;
    } else {
        mcpwm->operators[operator_id].gen_force.gen_b_nciforce = ~mcpwm->operators[operator_id].gen_force.gen_b_nciforce;
    }
}

static inline void mcpwm_ll_gen_disable_continue_force_action(mcpwm_dev_t *mcpwm, int operator_id, int generator_id)
{
    mcpwm->operators[operator_id].gen_force.gen_cntuforce_upmethod = 0; // 立即更新力方法
    if (generator_id == 0) {
        mcpwm->operators[operator_id].gen_force.gen_a_cntuforce_mode = 0;
    } else {
        mcpwm->operators[operator_id].gen_force.gen_b_cntuforce_mode = 0;
    }
}

static inline void mcpwm_ll_gen_disable_noncontinue_force_action(mcpwm_dev_t *mcpwm, int operator_id, int generator_id)
{
    if (generator_id == 0) {
        mcpwm->operators[operator_id].gen_force.gen_a_nciforce_mode = 0;
    } else {
        mcpwm->operators[operator_id].gen_force.gen_b_nciforce_mode = 0;
    }
}

static inline void mcpwm_ll_gen_set_continue_force_level(mcpwm_dev_t *mcpwm, int operator_id, int generator_id, int level)
{
    mcpwm->operators[operator_id].gen_force.gen_cntuforce_upmethod = 0; // 立即更新力方法
    if (generator_id == 0) {
        mcpwm->operators[operator_id].gen_force.gen_a_cntuforce_mode = level + 1;
    } else {
        mcpwm->operators[operator_id].gen_force.gen_b_cntuforce_mode = level + 1;
    }
}

static inline void mcpwm_ll_gen_set_noncontinue_force_level(mcpwm_dev_t *mcpwm, int operator_id, int generator_id, int level)
{
    if (generator_id == 0) {
        mcpwm->operators[operator_id].gen_force.gen_a_nciforce_mode = level + 1;
    } else {
        mcpwm->operators[operator_id].gen_force.gen_b_nciforce_mode = level + 1;
    }
}

/*********************停滞时间寄存器*******************/

static inline void mcpwm_ll_deadtime_resolution_to_timer(mcpwm_dev_t *mcpwm, int operator_id, bool same)
{
    // 是否使停滞时间延迟模块的分辨率与与操作员连接的计时器相同
    mcpwm->operators[operator_id].dt_cfg.dt_clk_sel = same;
}

static inline void mcpwm_ll_deadtime_red_select_generator(mcpwm_dev_t *mcpwm, int operator_id, int generator)
{
    mcpwm->operators[operator_id].dt_cfg.dt_red_insel = generator;
}

static inline void mcpwm_ll_deadtime_fed_select_generator(mcpwm_dev_t *mcpwm, int operator_id, int generator)
{
    mcpwm->operators[operator_id].dt_cfg.dt_fed_insel = generator;
}

static inline void mcpwm_ll_deadtime_bypass_path(mcpwm_dev_t *mcpwm, int operator_id, int path, bool bypass)
{
    if (bypass) {
        mcpwm->operators[operator_id].dt_cfg.val |= 1 << (path + 15);
    } else {
        mcpwm->operators[operator_id].dt_cfg.val &= ~(1 << (path + 15));
    }
}

static inline void mcpwm_ll_deadtime_invert_outpath(mcpwm_dev_t *mcpwm, int operator_id, int path, bool invert)
{
    if (invert) {
        mcpwm->operators[operator_id].dt_cfg.val |= 1 << (path + 13);
    } else {
        mcpwm->operators[operator_id].dt_cfg.val &= ~(1 << (path + 13));
    }
}

static inline void mcpwm_ll_deadtime_swap_out_path(mcpwm_dev_t *mcpwm, int operator_id, int path, bool swap)
{
    if (swap) {
        mcpwm->operators[operator_id].dt_cfg.val |= 1 << (path + 9);
    } else {
        mcpwm->operators[operator_id].dt_cfg.val &= ~(1 << (path + 9));
    }
}

static inline void mcpwm_ll_deadtime_enable_deb(mcpwm_dev_t *mcpwm, int operator_id, bool enable)
{
    mcpwm->operators[operator_id].dt_cfg.dt_deb_mode = enable;
}

static inline uint32_t mcpwm_ll_deadtime_get_switch_topology(mcpwm_dev_t *mcpwm, int operator_id)
{
    return (mcpwm->operators[operator_id].dt_cfg.dt_deb_mode << 8) | (mcpwm->operators[operator_id].dt_cfg.dt_b_outswap << 7) |
           (mcpwm->operators[operator_id].dt_cfg.dt_a_outswap << 6) | (mcpwm->operators[operator_id].dt_cfg.dt_fed_insel << 5) |
           (mcpwm->operators[operator_id].dt_cfg.dt_red_insel << 4) | (mcpwm->operators[operator_id].dt_cfg.dt_fed_outinvert << 3) |
           (mcpwm->operators[operator_id].dt_cfg.dt_red_outinvert << 2) | (mcpwm->operators[operator_id].dt_cfg.dt_a_outbypass << 1) |
           (mcpwm->operators[operator_id].dt_cfg.dt_b_outbypass << 0);
}

static inline void mcpwm_ll_deadtime_set_falling_delay(mcpwm_dev_t *mcpwm, int operator_id, uint32_t fed)
{
    HAL_FORCE_MODIFY_U32_REG_FIELD(mcpwm->operators[operator_id].dt_fed_cfg, dt_fed, fed - 1);
}

static inline uint32_t mcpwm_ll_deadtime_get_falling_delay(mcpwm_dev_t *mcpwm, int operator_id)
{
    return HAL_FORCE_READ_U32_REG_FIELD(mcpwm->operators[operator_id].dt_fed_cfg, dt_fed) + 1;
}

static inline void mcpwm_ll_deadtime_set_rising_delay(mcpwm_dev_t *mcpwm, int operator_id, uint32_t red)
{
    HAL_FORCE_MODIFY_U32_REG_FIELD(mcpwm->operators[operator_id].dt_red_cfg, dt_red, red - 1);
}

static inline uint32_t mcpwm_ll_deadtime_get_rising_delay(mcpwm_dev_t *mcpwm, int operator_id)
{
    return HAL_FORCE_READ_U32_REG_FIELD(mcpwm->operators[operator_id].dt_red_cfg, dt_red) + 1;
}

static inline void mcpwm_ll_deadtime_update_delay_at_once(mcpwm_dev_t *mcpwm, int operator_id)
{
    mcpwm->operators[operator_id].dt_cfg.dt_fed_upmethod = 0;
    mcpwm->operators[operator_id].dt_cfg.dt_red_upmethod = 0;
}

static inline void mcpwm_ll_deadtime_enable_update_delay_on_tez(mcpwm_dev_t *mcpwm, int operator_id, bool enable)
{
    if (enable) {
        mcpwm->operators[operator_id].dt_cfg.dt_fed_upmethod |= 1 << 0;
        mcpwm->operators[operator_id].dt_cfg.dt_red_upmethod |= 1 << 0;
    } else {
        mcpwm->operators[operator_id].dt_cfg.dt_fed_upmethod &= ~(1 << 0);
        mcpwm->operators[operator_id].dt_cfg.dt_red_upmethod &= ~(1 << 0);
    }
}

static inline void mcpwm_ll_deadtime_enable_update_delay_on_tep(mcpwm_dev_t *mcpwm, int operator_id, bool enable)
{
    if (enable) {
        mcpwm->operators[operator_id].dt_cfg.dt_fed_upmethod |= 1 << 1;
        mcpwm->operators[operator_id].dt_cfg.dt_red_upmethod |= 1 << 1;
    } else {
        mcpwm->operators[operator_id].dt_cfg.dt_fed_upmethod &= ~(1 << 1);
        mcpwm->operators[operator_id].dt_cfg.dt_red_upmethod &= ~(1 << 1);
    }
}

static inline void mcpwm_ll_deadtime_enable_update_delay_on_sync(mcpwm_dev_t *mcpwm, int operator_id, bool enable)
{
    if (enable) {
        mcpwm->operators[operator_id].dt_cfg.dt_fed_upmethod |= 1 << 2;
        mcpwm->operators[operator_id].dt_cfg.dt_red_upmethod |= 1 << 2;
    } else {
        mcpwm->operators[operator_id].dt_cfg.dt_fed_upmethod &= ~(1 << 2);
        mcpwm->operators[operator_id].dt_cfg.dt_red_upmethod &= ~(1 << 2);
    }
}

/*********************载波寄存器*******************/

static inline void mcpwm_ll_carrier_enable(mcpwm_dev_t *mcpwm, int operator_id, bool enable)
{
    mcpwm->operators[operator_id].carrier_cfg.carrier_en = enable;
}

static inline void mcpwm_ll_carrier_set_prescale(mcpwm_dev_t *mcpwm, int operator_id, uint8_t prescale)
{
    mcpwm->operators[operator_id].carrier_cfg.carrier_prescale = prescale - 1;
}

static inline uint8_t mcpwm_ll_carrier_get_prescale(mcpwm_dev_t *mcpwm, int operator_id)
{
    return mcpwm->operators[operator_id].carrier_cfg.carrier_prescale + 1;
}

static inline void mcpwm_ll_carrier_set_duty(mcpwm_dev_t *mcpwm, int operator_id, uint8_t carrier_duty)
{
    mcpwm->operators[operator_id].carrier_cfg.carrier_duty = carrier_duty;
}

static inline uint8_t mcpwm_ll_carrier_get_duty(mcpwm_dev_t *mcpwm, int operator_id)
{
    return mcpwm->operators[operator_id].carrier_cfg.carrier_duty;
}

static inline void mcpwm_ll_carrier_out_invert(mcpwm_dev_t *mcpwm, int operator_id, bool invert)
{
    mcpwm->operators[operator_id].carrier_cfg.carrier_out_invert = invert;
}

static inline void mcpwm_ll_carrier_in_invert(mcpwm_dev_t *mcpwm, int operator_id, bool invert)
{
    mcpwm->operators[operator_id].carrier_cfg.carrier_in_invert = invert;
}

static inline void mcpwm_ll_carrier_set_oneshot_width(mcpwm_dev_t *mcpwm, int operator_id, uint8_t pulse_width)
{
    mcpwm->operators[operator_id].carrier_cfg.carrier_oshtwth = pulse_width - 1;
}

static inline uint8_t mcpwm_ll_carrier_get_oneshot_width(mcpwm_dev_t *mcpwm, int operator_id)
{
    return mcpwm->operators[operator_id].carrier_cfg.carrier_oshtwth + 1;
}

/*********************故障检测器寄存器*******************/

static inline void mcpwm_ll_fault_enable_detection(mcpwm_dev_t *mcpwm, int fault_sig, bool enable)
{
    if (enable) {
        mcpwm->fault_detect.val |= 1 << fault_sig;
    } else {
        mcpwm->fault_detect.val &= ~(1 << fault_sig);
    }
}

static inline void mcpwm_ll_fault_set_active_level(mcpwm_dev_t *mcpwm, int fault_sig, bool level)
{
    if (level) {
        mcpwm->fault_detect.val |= 1 << (fault_sig + 3);
    } else {
        mcpwm->fault_detect.val &= ~(1 << (fault_sig + 3));
    }
}

static inline void mcpwm_ll_fault_clear_ost(mcpwm_dev_t *mcpwm, int operator_id)
{
    // posedge可以清除最严重的故障状态
    mcpwm->operators[operator_id].fh_cfg1.fh_clr_ost = 0;
    mcpwm->operators[operator_id].fh_cfg1.fh_clr_ost = 1;
}

static inline void mcpwm_ll_fault_enable_oneshot_mode(mcpwm_dev_t *mcpwm, int operator_id, int fault_sig, bool enable)
{
    mcpwm->operators[operator_id].fh_cfg0.val &= ~(1 << (7 - fault_sig));
    mcpwm->operators[operator_id].fh_cfg0.val |= (enable << (7 - fault_sig));
}

static inline void mcpwm_ll_fault_enable_cbc_mode(mcpwm_dev_t *mcpwm, int operator_id, int fault_sig, bool enable)
{
    mcpwm->operators[operator_id].fh_cfg0.val &= ~(1 << (3 - fault_sig));
    mcpwm->operators[operator_id].fh_cfg0.val |= (enable << (3 - fault_sig));
}

static inline void mcpwm_ll_fault_enable_cbc_refresh_on_tez(mcpwm_dev_t *mcpwm, int operator_id, bool enable)
{
    if (enable) {
        mcpwm->operators[operator_id].fh_cfg1.val |= 1 << 1;
    } else {
        mcpwm->operators[operator_id].fh_cfg1.val &= ~(1 << 1);
    }
}

static inline void mcpwm_ll_fault_enable_cbc_refresh_on_tep(mcpwm_dev_t *mcpwm, int operator_id, bool enable)
{
    if (enable) {
        mcpwm->operators[operator_id].fh_cfg1.val |= 1 << 2;
    } else {
        mcpwm->operators[operator_id].fh_cfg1.val &= ~(1 << 2);
    }
}

static inline void mcpwm_ll_fault_enable_sw_cbc(mcpwm_dev_t *mcpwm, int operator_id, bool enable)
{
    mcpwm->operators[operator_id].fh_cfg0.fh_sw_cbc = enable;
}

static inline void mcpwm_ll_fault_enable_sw_oneshot(mcpwm_dev_t *mcpwm, int operator_id, bool enable)
{
    mcpwm->operators[operator_id].fh_cfg0.fh_sw_ost = enable;
}

static inline void mcpwm_ll_fault_trigger_sw_cbc(mcpwm_dev_t *mcpwm, int operator_id)
{
    mcpwm->operators[operator_id].fh_cfg1.fh_force_cbc = ~mcpwm->operators[operator_id].fh_cfg1.fh_force_cbc;
}

static inline void mcpwm_ll_fault_trigger_sw_ost(mcpwm_dev_t *mcpwm, int operator_id)
{
    mcpwm->operators[operator_id].fh_cfg1.fh_force_ost = ~mcpwm->operators[operator_id].fh_cfg1.fh_force_ost;
}

static inline void mcpwm_ll_generator_set_action_on_trip_event(mcpwm_dev_t *mcpwm, int operator_id, int generator_id,
        mcpwm_timer_direction_t direction, mcpwm_trip_type_t trip, int action)
{
    if (direction == MCPWM_TIMER_DIRECTION_UP) {
        mcpwm->operators[operator_id].fh_cfg0.val &= ~(0x03 << (8 + 8 * generator_id + 4 * trip + 2));
        mcpwm->operators[operator_id].fh_cfg0.val |= action << (8 + 8 * generator_id + 4 * trip + 2);
    } else if (direction == MCPWM_TIMER_DIRECTION_DOWN) {
        mcpwm->operators[operator_id].fh_cfg0.val &= ~(0x03 << (8 + 8 * generator_id + 4 * trip));
        mcpwm->operators[operator_id].fh_cfg0.val |= action << (8 + 8 * generator_id + 4 * trip);
    }
}

static inline bool mcpwm_ll_fault_is_ost_on(mcpwm_dev_t *mcpwm, int op)
{
    return mcpwm->operators[op].fh_status.fh_ost_on;
}

static inline bool mcpwm_ll_fault_is_cbc_on(mcpwm_dev_t *mcpwm, int op)
{
    return mcpwm->operators[op].fh_status.fh_cbc_on;
}

/*********************捕获寄存器*******************/

static inline void mcpwm_ll_capture_enable_timer(mcpwm_dev_t *mcpwm, bool enable)
{
    mcpwm->cap_timer_cfg.cap_timer_en = enable;
}

static inline void mcpwm_ll_capture_enable_channel(mcpwm_dev_t *mcpwm, int channel, bool enable)
{
    mcpwm->cap_chn_cfg[channel].capn_en = enable;
}

static inline void mcpwm_ll_capture_set_sync_phase_value(mcpwm_dev_t *mcpwm, uint32_t phase_value)
{
    mcpwm->cap_timer_phase.cap_timer_phase = phase_value;
}

static inline uint32_t mcpwm_ll_capture_get_sync_phase_value(mcpwm_dev_t *mcpwm)
{
    return mcpwm->cap_timer_phase.cap_timer_phase;
}

static inline void mcpwm_ll_capture_enable_timer_sync(mcpwm_dev_t *mcpwm, bool enable)
{
    mcpwm->cap_timer_cfg.cap_synci_en = enable;
}

static inline void mcpwm_ll_capture_set_internal_timer_synchro(mcpwm_dev_t *mcpwm, int sync_out_timer)
{
    mcpwm->cap_timer_cfg.cap_synci_sel = sync_out_timer + 1;
}

static inline void mcpwm_ll_capture_set_external_synchro(mcpwm_dev_t *mcpwm, int extern_synchro)
{
    mcpwm->cap_timer_cfg.cap_synci_sel = extern_synchro + 4;
}

static inline void mcpwm_ll_capture_trigger_sw_sync(mcpwm_dev_t *mcpwm)
{
    mcpwm->cap_timer_cfg.cap_sync_sw = 1; // 自动清除
}

static inline void mcpwm_ll_capture_enable_posedge(mcpwm_dev_t *mcpwm, int channel, bool enable)
{
    if (enable) {
        mcpwm->cap_chn_cfg[channel].val |= 1 << 2;
    } else {
        mcpwm->cap_chn_cfg[channel].val &= ~(1 << 2);
    }
}

static inline void mcpwm_ll_capture_enable_negedge(mcpwm_dev_t *mcpwm, int channel, bool enable)
{
    if (enable) {
        mcpwm->cap_chn_cfg[channel].val |= 1 << 1;
    } else {
        mcpwm->cap_chn_cfg[channel].val &= ~(1 << 1);
    }
}

static inline void mcpwm_ll_invert_input(mcpwm_dev_t *mcpwm, int channel, bool invert)
{
    mcpwm->cap_chn_cfg[channel].capn_in_invert = invert;
}

static inline void mcpwm_ll_trigger_soft_capture(mcpwm_dev_t *mcpwm, int channel)
{
    mcpwm->cap_chn_cfg[channel].capn_sw = 1; // 自动清除
}

__attribute__((always_inline))
static inline uint32_t mcpwm_ll_capture_get_value(mcpwm_dev_t *mcpwm, int channel)
{
    return mcpwm->cap_chn[channel].capn_value;
}

__attribute__((always_inline))
static inline bool mcpwm_ll_capture_is_negedge(mcpwm_dev_t *mcpwm, int channel)
{
    return mcpwm->cap_status.val & (1 << channel) ? true : false;
}

static inline void mcpwm_ll_capture_set_prescale(mcpwm_dev_t *mcpwm, int channel, uint32_t prescale)
{
    HAL_FORCE_MODIFY_U32_REG_FIELD(mcpwm->cap_chn_cfg[channel], capn_prescale, prescale - 1);
}

static inline uint32_t mcpwm_ll_capture_get_prescale(mcpwm_dev_t *mcpwm, int channel)
{
    return HAL_FORCE_READ_U32_REG_FIELD(mcpwm->cap_chn_cfg[channel], capn_prescale) + 1;
}

#ifdef __cplusplus
}
#endif

