// 版权所有2015-2021 Espressif Systems（Shanghai）PTE LTD
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

/*******************************************************************************
 * 注意：hal不是公共api，不要在应用程序代码中使用。请参阅自述文件。在hal/include/hal/readme.md中的md
 ******************************************************************************/

// ESP32-S2 PCNT寄存器操作的LL层

#pragma once

#include <stdlib.h>
#include <stdbool.h>
#include "soc/pcnt_struct.h"
#include "hal/pcnt_types.h"

#ifdef __cplusplus
extern "C" {
#endif

#define PCNT_LL_GET_HW(num) (((num) == 0) ? (&PCNT) : NULL)
#define PCNT_LL_MAX_GLITCH_WIDTH 1023

typedef enum {
    PCNT_LL_EVENT_THRES1,
    PCNT_LL_EVENT_THRES0,
    PCNT_LL_EVENT_LOW_LIMIT,
    PCNT_LL_EVENT_HIGH_LIMIT,
    PCNT_LL_EVENT_ZERO_CROSS,
    PCNT_LL_EVENT_MAX
} pcnt_ll_event_id_t;

#define PCNT_LL_EVENT_MASK ((1 << PCNT_LL_EVENT_MAX) - 1)

/**
 * @brief 设置PCNT通道边缘动作
 *
 * @param hw 外围PCNT硬件实例地址。
 * @param unit PCNT单元编号
 * @param channel PCNT通道编号
 * @param pos_act 检测到正边缘时的反作用
 * @param neg_act 检测负边缘时的反作用
 */
static inline void pcnt_ll_set_edge_action(pcnt_dev_t *hw, uint32_t unit, uint32_t channel, pcnt_channel_edge_action_t pos_act, pcnt_channel_edge_action_t neg_act)
{
    if (channel == 0) {
        hw->conf_unit[unit].conf0.ch0_pos_mode_un = pos_act;
        hw->conf_unit[unit].conf0.ch0_neg_mode_un = neg_act;
    } else {
        hw->conf_unit[unit].conf0.ch1_pos_mode_un = pos_act;
        hw->conf_unit[unit].conf0.ch1_neg_mode_un = neg_act;
    }
}

/**
 * @brief 设置PCNT通道级别操作
 *
 * @param hw 外围PCNT硬件实例地址。
 * @param unit PCNT单元编号
 * @param channel PCNT通道编号
 * @param high_act 控制信号为高电平时的反作用
 * @param low_act 控制信号为低电平时的反作用
 */
static inline void pcnt_ll_set_level_action(pcnt_dev_t *hw, uint32_t unit, uint32_t channel, pcnt_channel_level_action_t high_act, pcnt_channel_level_action_t low_act)
{
    if (channel == 0) {
        hw->conf_unit[unit].conf0.ch0_hctrl_mode_un = high_act;
        hw->conf_unit[unit].conf0.ch0_lctrl_mode_un = low_act;
    } else {
        hw->conf_unit[unit].conf0.ch1_hctrl_mode_un = high_act;
        hw->conf_unit[unit].conf0.ch1_lctrl_mode_un = low_act;
    }
}

/**
 * @brief 获取脉冲计数器值
 *
 * @param hw 外围PCNT硬件实例地址。
 * @param unit  脉冲计数器单元编号
 * @return PCNT计数值（有符号整数）
 */
static inline int pcnt_ll_get_count(pcnt_dev_t *hw, uint32_t unit)
{
    pcnt_un_cnt_reg_t cnt_reg = hw->cnt_unit[unit];
    int16_t value = cnt_reg.pulse_cnt_un;
    return value;
}

/**
 * @brief 暂停PCNT单元的PCNT计数器
 *
 * @param hw 外围PCNT硬件实例地址。
 * @param unit PCNT单元编号
 */
static inline void pcnt_ll_stop_count(pcnt_dev_t *hw, uint32_t unit)
{
    hw->ctrl.val |= 1 << (2 * unit + 1);
}

/**
 * @brief PCNT计数器的恢复计数
 *
 * @param hw 外围PCNT硬件实例地址。
 * @param unit PCNT单元编号，从uint32_t中选择
 */
static inline void pcnt_ll_start_count(pcnt_dev_t *hw, uint32_t unit)
{
    hw->ctrl.val &= ~(1 << (2 * unit + 1));
}

/**
 * @brief 将PCNT计数器值清零
 *
 * @param hw 外围PCNT硬件实例地址。
 * @param  unit PCNT单元编号，从uint32_t中选择
 */
static inline void pcnt_ll_clear_count(pcnt_dev_t *hw, uint32_t unit)
{
    hw->ctrl.val |= 1 << (2 * unit);
    hw->ctrl.val &= ~(1 << (2 * unit));
}

/**
 * @brief 启用PCNT单元的PCNT中断
 * @note  每个PCNT单元有五个监视点事件，它们共享相同的中断位。
 *
 * @param hw 外围PCNT硬件实例地址。
 * @param unit_mask PCNT单位掩码
 * @param enable True表示启用中断，False表示禁用中断
 */
static inline void pcnt_ll_enable_intr(pcnt_dev_t *hw, uint32_t unit_mask, bool enable)
{
    if (enable) {
        hw->int_ena.val |= unit_mask;
    } else {
        hw->int_ena.val &= ~unit_mask;
    }
}

/**
 * @brief 获取PCNT中断状态
 *
 * @param hw 外围PCNT硬件实例地址。
 * @return 中断状态字
 */
__attribute__((always_inline)) static inline uint32_t pcnt_ll_get_intr_status(pcnt_dev_t *hw)
{
    return hw->int_st.val;
}

/**
 * @brief 清除PCNT中断状态
 *
 * @param hw 外围PCNT硬件实例地址。
 * @param status 清除中断状态的值
 */
__attribute__((always_inline)) static inline void pcnt_ll_clear_intr_status(pcnt_dev_t *hw, uint32_t status)
{
    hw->int_clr.val = status;
}

/**
 * @brief 启用PCNT上限事件
 *
 * @param hw 外围PCNT硬件实例地址。
 * @param unit PCNT单元编号
 * @param enable true表示启用，false表示禁用
 */
static inline void pcnt_ll_enable_high_limit_event(pcnt_dev_t *hw, uint32_t unit, bool enable)
{
    hw->conf_unit[unit].conf0.thr_h_lim_en_un = enable;
}

/**
 * @brief 启用PCNT下限事件
 *
 * @param hw 外围PCNT硬件实例地址。
 * @param unit PCNT单元编号
 * @param enable true表示启用，false表示禁用
 */
static inline void pcnt_ll_enable_low_limit_event(pcnt_dev_t *hw, uint32_t unit, bool enable)
{
    hw->conf_unit[unit].conf0.thr_l_lim_en_un = enable;
}

/**
 * @brief 启用PCNT零交叉事件
 *
 * @param hw 外围PCNT硬件实例地址。
 * @param unit PCNT单元编号
 * @param enable true表示启用，false表示禁用
 */
static inline void pcnt_ll_enable_zero_cross_event(pcnt_dev_t *hw, uint32_t unit, bool enable)
{
    hw->conf_unit[unit].conf0.thr_zero_en_un = enable;
}

/**
 * @brief 启用PCNT阈值事件
 *
 * @param hw 外围PCNT硬件实例地址。
 * @param unit PCNT单元编号
 * @param thres 阈值ID
 * @param enable true表示启用，false表示禁用
 */
static inline void pcnt_ll_enable_thres_event(pcnt_dev_t *hw, uint32_t unit, uint32_t thres, bool enable)
{
    if (thres == 0) {
        hw->conf_unit[unit].conf0.thr_thres0_en_un = enable;
    } else {
        hw->conf_unit[unit].conf0.thr_thres1_en_un = enable;
    }
}

/**
 * @brief 禁用所有PCNT阈值事件
 *
 * @param hw 外围PCNT硬件实例地址。
 * @param unit 单位编号
 */
static inline void pcnt_ll_disable_all_events(pcnt_dev_t *hw, uint32_t unit)
{
    hw->conf_unit[unit].conf0.val &= ~(PCNT_LL_EVENT_MASK << 11);
}

/**
 * @brief 设置PCNT上限值
 *
 * @param hw 外围PCNT硬件实例地址。
 * @param unit PCNT单元编号
 * @param value PCNT上限值
 */
static inline void pcnt_ll_set_high_limit_value(pcnt_dev_t *hw, uint32_t unit, int value)
{
    pcnt_un_conf2_reg_t conf2_reg = hw->conf_unit[unit].conf2;
    conf2_reg.cnt_h_lim_un = value;
    hw->conf_unit[unit].conf2 = conf2_reg;
}

/**
 * @brief 设置PCNT下限值
 *
 * @param hw 外围PCNT硬件实例地址。
 * @param unit PCNT单元编号
 * @param value PCNT下限值
 */
static inline void pcnt_ll_set_low_limit_value(pcnt_dev_t *hw, uint32_t unit, int value)
{
    pcnt_un_conf2_reg_t conf2_reg = hw->conf_unit[unit].conf2;
    conf2_reg.cnt_l_lim_un = value;
    hw->conf_unit[unit].conf2 = conf2_reg;
}

/**
 * @brief 设置PCNT阈值
 *
 * @param hw 外围PCNT硬件实例地址。
 * @param unit PCNT单元编号
 * @param thres 阈值ID
 * @param value PCNT阈值
 */
static inline void pcnt_ll_set_thres_value(pcnt_dev_t *hw, uint32_t unit, uint32_t thres, int value)
{
    pcnt_un_conf1_reg_t conf1_reg = hw->conf_unit[unit].conf1;
    if (thres == 0) {
        conf1_reg.cnt_thres0_un = value;
    } else {
        conf1_reg.cnt_thres1_un = value;
    }
    hw->conf_unit[unit].conf1 = conf1_reg;
}

/**
 * @brief 获取PCNT上限值
 *
 * @param hw 外围PCNT硬件实例地址。
 * @param unit PCNT单元编号
 * @return PCNT上限值
 */
static inline int pcnt_ll_get_high_limit_value(pcnt_dev_t *hw, uint32_t unit)
{
    pcnt_un_conf2_reg_t conf2_reg = hw->conf_unit[unit].conf2;
    int16_t value = conf2_reg.cnt_h_lim_un;
    return value;
}

/**
 * @brief 获取PCNT下限值
 *
 * @param hw 外围PCNT硬件实例地址。
 * @param unit PCNT单元编号
 * @return PCNT上限值
 */
static inline int pcnt_ll_get_low_limit_value(pcnt_dev_t *hw, uint32_t unit)
{
    pcnt_un_conf2_reg_t conf2_reg = hw->conf_unit[unit].conf2;
    int16_t value = conf2_reg.cnt_l_lim_un;
    return value;
}

/**
 * @brief 获取PCNT阈值
 *
 * @param hw 外围PCNT硬件实例地址。
 * @param unit PCNT单元编号
 * @param thres 阈值ID
 * @return PCNT阈值
 */
static inline int pcnt_ll_get_thres_value(pcnt_dev_t *hw, uint32_t unit, uint32_t thres)
{
    int16_t value;
    pcnt_un_conf1_reg_t conf1_reg = hw->conf_unit[unit].conf1;
    if (thres == 0) {
        value = conf1_reg.cnt_thres0_un;
    } else {
        value = conf1_reg.cnt_thres1_un;
    }
    return value;
}

/**
 * @brief 获取PCNT单元运行时状态
 *
 * @param hw 外围PCNT硬件实例地址。
 * @param unit PCNT单元编号
 * @return PCNT装置运行时状态
 */
static inline uint32_t pcnt_ll_get_unit_status(pcnt_dev_t *hw, uint32_t unit)
{
    return hw->status_unit[unit].val;
}

/**
 * @brief 获取PCNT计数标志
 *
 * @param hw 外围PCNT硬件实例地址。
 * @param unit PCNT单元编号
 * @return 计数符号
 */
static inline pcnt_unit_count_sign_t pcnt_ll_get_count_sign(pcnt_dev_t *hw, uint32_t unit)
{
    return hw->status_unit[unit].val & 0x03;
}

/**
 * @brief 获取PCNT事件状态
 *
 * @param hw 外围PCNT硬件实例地址。
 * @param unit PCNT单元编号
 * @return 事件状态字
 */
static inline uint32_t pcnt_ll_get_event_status(pcnt_dev_t *hw, uint32_t unit)
{
    return hw->status_unit[unit].val >> 2;
}

/**
 * @brief 设置PCNT故障筛选器阈值
 *
 * @param hw 外围PCNT硬件实例地址。
 * @param unit PCNT单元编号
 * @param filter_val PCNT信号滤波器值，APB_CLK周期中的计数器。启用滤波器时，任何持续时间短于此的脉冲将被忽略。
 */
static inline void pcnt_ll_set_glitch_filter_thres(pcnt_dev_t *hw, uint32_t unit, uint32_t filter_val)
{
    hw->conf_unit[unit].conf0.filter_thres_un = filter_val;
}

/**
 * @brief 获取PCNT故障筛选器阈值
 *
 * @param hw 外围PCNT硬件实例地址。
 * @param unit PCNT单元编号
 * @return 故障滤波器阈值
 */
static inline uint32_t pcnt_ll_get_glitch_filter_thres(pcnt_dev_t *hw, uint32_t unit)
{
    return hw->conf_unit[unit].conf0.filter_thres_un;
}

/**
 * @brief 启用PCNT故障筛选器
 *
 * @param hw 外围PCNT硬件实例地址。
 * @param unit PCNT单元编号
 * @param enable True表示启用筛选器，False表示禁用筛选器
 */
static inline void pcnt_ll_enable_glitch_filter(pcnt_dev_t *hw, uint32_t unit, bool enable)
{
    hw->conf_unit[unit].conf0.filter_en_un = enable;
}

#ifdef __cplusplus
}
#endif

