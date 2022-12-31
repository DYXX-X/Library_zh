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

/*******************************************************************************
 * 注意ll不是公共api，不要在应用程序代码中使用。请参阅自述文件。在hal/include/hal/readme.md中的md
 ******************************************************************************/

// 触摸传感器的低电平层

#pragma once

#include <stdlib.h>
#include <stdbool.h>
#include "hal/misc.h"
#include "soc/touch_sensor_periph.h"
#include "soc/sens_struct.h"
#include "soc/rtc_io_struct.h"
#include "soc/rtc_cntl_struct.h"
#include "hal/touch_sensor_types.h"


#ifdef __cplusplus
extern "C" {
#endif

//触摸传感器8和9的一些寄存器位不匹配，我们需要交换这些位。
#define TOUCH_LL_BIT_SWAP(data, n, m)   (((data >> n) &  0x1)  == ((data >> m) & 0x1) ? (data) : ((data) ^ ((0x1 <<n) | (0x1 << m))))
#define TOUCH_LL_BITS_SWAP(v)  TOUCH_LL_BIT_SWAP(v, TOUCH_PAD_NUM8, TOUCH_PAD_NUM9)

/**
 * 交换touch8和touch9的数量。
 *
 * @touch_num 触摸通道编号。
 */
static inline touch_pad_t touch_ll_num_wrap(touch_pad_t touch_num)
{
    if (touch_num == TOUCH_PAD_NUM8) {
        return TOUCH_PAD_NUM9;
    } else if (touch_num == TOUCH_PAD_NUM9) {
        return TOUCH_PAD_NUM8;
    }
    return touch_num;
}

/**
 * 设置触摸传感器测量时间。
 *
 * @param meas_time 触摸传感器测量的持续时间。t_meas=meas_time/（8MHz），最大测量时间为0xffff/8M=8.19ms。
 */
static inline void touch_ll_set_meas_time(uint16_t meas_time)
{
    //触摸传感器测量时间=meas_cycle/8Mhz
    HAL_FORCE_MODIFY_U32_REG_FIELD(SENS.sar_touch_ctrl1, touch_meas_delay, meas_time);
    //TOUCH_START和TOUCH_XPD之间的等待周期（8MHz）
    HAL_FORCE_MODIFY_U32_REG_FIELD(SENS.sar_touch_ctrl1, touch_xpd_wait, SOC_TOUCH_PAD_MEASURE_WAIT_MAX);
}

/**
 * 获取触摸传感器测量时间。
 *
 * @param meas_time 接受测量周期计数的指针。
 */
static inline void touch_ll_get_meas_time(uint16_t *meas_time)
{
    *meas_time = HAL_FORCE_READ_U32_REG_FIELD(SENS.sar_touch_ctrl1, touch_meas_delay);
}

/**
 * 设置触摸传感器睡眠时间（测量间隔）。
 *
 * @param sleep_time  每次测量后，触摸传感器将休眠。sleep_cycle决定每次测量之间的间隔。t_sleep=sleep_cycle/（RTC_SLOW_CLK频率）。RTC_SLOW_CLK的近似频率值可使用“RTC_CLK_SLOW_freq_get_hz”函数获得。
 */
static inline void touch_ll_set_sleep_time(uint16_t sleep_time)
{
    //触摸传感器睡眠周期时间=sleep_cycle/RTC_SLOW_CLK（可以是150k或32k，取决于选项）
    HAL_FORCE_MODIFY_U32_REG_FIELD(SENS.sar_touch_ctrl2, touch_sleep_cycles, sleep_time);
}

/**
 * 获取触摸传感器睡眠时间。
 *
 * @param sleep_time 用于接受睡眠周期计数的指针。
 */
static inline void touch_ll_get_sleep_time(uint16_t *sleep_time)
{
    *sleep_time = HAL_FORCE_READ_U32_REG_FIELD(SENS.sar_touch_ctrl2, touch_sleep_cycles);
}

/**
 * 设置通道的触摸传感器高电压阈值。触摸传感器通过对通道进行充电和放电来测量通道电容值。因此，高阈值应该小于电源电压。
 *
 * @param refh 通道的高电压阈值。
 */
static inline void touch_ll_set_voltage_high(touch_high_volt_t refh)
{
    RTCIO.touch_cfg.drefh = refh;
}

/**
 * 获取通道的触摸传感器高电压阈值。触摸传感器通过对通道进行充电和放电来测量通道电容值。因此，高阈值应该小于电源电压。
 *
 * @param refh 通道的高电压阈值。
 */
static inline void touch_ll_get_voltage_high(touch_high_volt_t *refh)
{
    *refh = (touch_high_volt_t)RTCIO.touch_cfg.drefh;
}

/**
 * 设置触摸传感器放电的低电压阈值。触摸传感器通过对通道进行充电和放电来测量通道电容值。
 *
 * @param refl 放电的低电压阈值。
 */
static inline void touch_ll_set_voltage_low(touch_low_volt_t refl)
{
    RTCIO.touch_cfg.drefl = refl;
}

/**
 * 获取触摸传感器低电压放电阈值。触摸传感器通过对通道进行充电和放电来测量通道电容值。
 *
 * @param refl 放电的低电压阈值。
 */
static inline void touch_ll_get_voltage_low(touch_low_volt_t *refl)
{
    *refl = (touch_low_volt_t)RTCIO.touch_cfg.drefl;
}

/**
 * 设置触摸传感器的高电压衰减通道。实际充电阈值是高电压阈值减去衰减值。触摸传感器通过对通道进行充电和放电来测量通道电容值。因此，高阈值应该小于电源电压。
 *
 * @param refh 通道的高电压阈值。
 */
static inline void touch_ll_set_voltage_attenuation(touch_volt_atten_t atten)
{
    RTCIO.touch_cfg.drange = atten;
}

/**
 * 获取触摸传感器的高电压衰减通道。实际充电阈值是高电压阈值减去衰减值。触摸传感器通过对通道进行充电和放电来测量通道电容值。因此，高阈值应该小于电源电压。
 *
 * @param refh 通道的高电压阈值。
 */
static inline void touch_ll_get_voltage_attenuation(touch_volt_atten_t *atten)
{
    *atten = (touch_volt_atten_t)RTCIO.touch_cfg.drange;
}

/**
 * 为每个极板设置触摸传感器充电/放电速度（电流）。如果斜率为0，计数器将始终为零。如果斜率为1，则充电和放电将缓慢。测量时间变长。如果斜率设置为最大值7，则充电和放电将很快。测量时间变短。
 *
 * @note 充电和放电电流越高，触摸通道的抗扰度越高，但会增加系统功耗。
 * @param touch_num 触摸板索引。
 * @param slope 触摸板充电/放电速度（电流）。
 */
static inline void touch_ll_set_slope(touch_pad_t touch_num, touch_cnt_slope_t slope)
{
    RTCIO.touch_pad[touch_num].dac = slope;
}

/**
 * 获取每个极板的触摸传感器充电/放电速度（电流）。如果斜率为0，计数器将始终为零。如果斜率为1，则充电和放电将缓慢。测量时间变长。如果斜率设置为最大值7，则充电和放电将很快。测量时间变短。
 *
 * @param touch_num 触摸板索引。
 * @param slope 触摸板充电/放电速度（电流）。
 */
static inline void touch_ll_get_slope(touch_pad_t touch_num, touch_cnt_slope_t *slope)
{
    *slope = (touch_cnt_slope_t)RTCIO.touch_pad[touch_num].dac;
}

/**
 * 为每次测量设置触摸通道的初始电压状态。
 *
 * @param touch_num 触摸板索引。
 * @param opt 初始电压状态。
 */
static inline void touch_ll_set_tie_option(touch_pad_t touch_num, touch_tie_opt_t opt)
{
    touch_pad_t touch_pad_wrap = touch_ll_num_wrap(touch_num);
    RTCIO.touch_pad[touch_pad_wrap].tie_opt = opt;
}

/**
 * 获取每次测量的触摸通道的初始电压状态。
 *
 * @param touch_num 触摸板索引。
 * @param opt 初始电压状态。
 */
static inline void touch_ll_get_tie_option(touch_pad_t touch_num, touch_tie_opt_t *opt)
{
    touch_pad_t touch_pad_wrap = touch_ll_num_wrap(touch_num);
    *opt = (touch_tie_opt_t)RTCIO.touch_pad[touch_pad_wrap].tie_opt;
}

/**
 * 设置触摸传感器FSM模式。测量动作可以由硬件计时器以及软件指令触发。
 *
 * @param mode FSM模式。
 */
static inline void touch_ll_set_fsm_mode(touch_fsm_mode_t mode)
{
    SENS.sar_touch_ctrl2.touch_start_fsm_en = 1;
    SENS.sar_touch_ctrl2.touch_start_en = 0;
    SENS.sar_touch_ctrl2.touch_start_force = mode;
}

/**
 * 获取触摸传感器FSM模式。测量动作可以由硬件计时器以及软件指令触发。
 *
 * @param mode FSM模式。
 */
static inline void touch_ll_get_fsm_mode(touch_fsm_mode_t *mode)
{
    *mode = (touch_fsm_mode_t)SENS.sar_touch_ctrl2.touch_start_force;
}

/**
 * 启动触摸传感器FSM计时器。测量动作可以由硬件计时器以及软件指令触发。
 *
 * @param mode FSM模式。
 */
static inline void touch_ll_start_fsm(void)
{
    RTCCNTL.state0.touch_slp_timer_en = 1;
}

/**
 * 停止触摸传感器FSM计时器。测量动作可以由硬件计时器以及软件指令触发。
 *
 * @param mode FSM模式。
 */
static inline void touch_ll_stop_fsm(void)
{
    RTCCNTL.state0.touch_slp_timer_en = 0;
}

/**
 * 触发触摸传感器测量，仅支持FSM的SW模式。
 */
static inline void touch_ll_start_sw_meas(void)
{
    SENS.sar_touch_ctrl2.touch_start_en = 0;
    SENS.sar_touch_ctrl2.touch_start_en = 1;
}

/**
 * 设置触摸传感器中断阈值。
 *
 * @note 请参阅“touch_pad_set_trigger_mode”以了解如何设置触发模式。
 * @param touch_num 触摸板索引。
 * @param threshold 触摸板计数阈值。
 */
static inline void touch_ll_set_threshold(touch_pad_t touch_num, uint16_t threshold)
{
    touch_pad_t tp_wrap = touch_ll_num_wrap(touch_num);
    if (tp_wrap & 0x1) {
        HAL_FORCE_MODIFY_U32_REG_FIELD(SENS.touch_thresh[tp_wrap / 2], l_thresh, threshold);
    } else {
        HAL_FORCE_MODIFY_U32_REG_FIELD(SENS.touch_thresh[tp_wrap / 2], h_thresh, threshold);
    }
}

/**
 * 获取触摸传感器中断阈值。
 *
 * @param touch_num 触摸板索引。
 * @param threshold 接受阈值的指针。
 */
static inline void touch_ll_get_threshold(touch_pad_t touch_num, uint16_t *threshold)
{
    touch_pad_t tp_wrap = touch_ll_num_wrap(touch_num);
    if (threshold) {
        *threshold = (tp_wrap & 0x1 ) ?
            HAL_FORCE_READ_U32_REG_FIELD(SENS.touch_thresh[tp_wrap / 2], l_thresh) :
            HAL_FORCE_READ_U32_REG_FIELD(SENS.touch_thresh[tp_wrap / 2], h_thresh);
    }
}

/**
 * 设置触摸传感器中断触发模式。当触摸值小于阈值或触摸值大于阈值时，可以触发中断。
 *
 * @param mode 触摸传感器中断触发模式。
 */
static inline void touch_ll_set_trigger_mode(touch_trigger_mode_t mode)
{
    SENS.sar_touch_ctrl1.touch_out_sel = mode;
}

/**
 * 获取触摸传感器中断触发模式。当触摸值小于阈值或触摸值大于阈值时，可以触发中断。
 *
 * @param mode 触摸传感器中断触发模式。
 */
static inline void touch_ll_get_trigger_mode(touch_trigger_mode_t *mode)
{
    *mode = (touch_trigger_mode_t)SENS.sar_touch_ctrl1.touch_out_sel;
}

/**
 * 设置触摸传感器中断触发源。有两组触摸信号。Set1和set2可以被映射到多个触摸信号。如果至少有一个触摸信号被“触摸”，将触发任一组。可以将中断配置为在触发set1时生成，或者仅在触发两个集合时生成。
 *
 * @param src 触摸传感器中断触发源。
 */
static inline void touch_ll_set_trigger_source(touch_trigger_src_t src)
{
    SENS.sar_touch_ctrl1.touch_out_1en = src;
}

/**
 * 获取触摸传感器中断触发源。
 *
 * @param src 用于接受触摸传感器中断触发源的指针。
 */
static inline void touch_ll_get_trigger_source(touch_trigger_src_t *src)
{
    *src = (touch_trigger_src_t)SENS.sar_touch_ctrl1.touch_out_1en;
}

/**
 * 启用触摸传感器通道。将触摸通道注册到触摸传感器测量组中。触摸传感器的工作模式是同时测量。此函数将根据给定的位掩码设置测量位。
 *
 * @note  如果设置此掩码，则应首先停止FSM计时器。
 * @note  在扫描图中的触摸传感器，应首先取消GPIO功能。
 * @param enable_mask 触摸传感器扫描组的位掩码。e、 g.TOUCH_PAD_NUM1->位（1）
 * @return
 *      -成功时ESP_OK
 */
static inline void touch_ll_set_channel_mask(uint16_t enable_mask)
{
    SENS.sar_touch_enable.touch_pad_worken |= TOUCH_LL_BITS_SWAP(enable_mask);
}

/**
 * 获取触摸传感器通道掩码。
 *
 * @param enable_mask 触摸传感器扫描组的位掩码。e、 g.TOUCH_PAD_NUM1->位（1）
 */
static inline void touch_ll_get_channel_mask(uint16_t *enable_mask)
{
    *enable_mask = TOUCH_LL_BITS_SWAP(SENS.sar_touch_enable.touch_pad_worken);
}

/**
 * 通过位掩码禁用触摸传感器通道。
 *
 * @param enable_mask 触摸传感器扫描组的位掩码。e、 g.TOUCH_PAD_NUM1->位（1）
 */
static inline void touch_ll_clear_channel_mask(uint16_t disable_mask)
{
    SENS.sar_touch_enable.touch_pad_worken &= TOUCH_LL_BITS_SWAP(~disable_mask);
}

/**
 * 设置触摸传感器组掩码。触摸板模块有两组信号，只有当该组中至少一个触摸板被“触摸”时，才会触发“触摸”信号。此函数将根据给定的位掩码设置寄存器位。
 *
 * @param set1_mask 触摸传感器信号组1的位掩码，为10位值
 * @param set2_mask 触摸传感器信号组2的位掩码，为10位值
 */
static inline void touch_ll_set_group_mask(uint16_t group1_mask, uint16_t group2_mask)
{
    SENS.sar_touch_enable.touch_pad_outen1 |= TOUCH_LL_BITS_SWAP(group1_mask);
    SENS.sar_touch_enable.touch_pad_outen2 |= TOUCH_LL_BITS_SWAP(group2_mask);
}

/**
 * 获取触摸传感器组掩码。
 *
 * @param set1_mask 用于接受触摸传感器信号组1的位掩码的指针，它是一个10位值
 * @param set2_mask 用于接受触摸传感器信号组2的位掩码的指针，它是一个10位值
 */
static inline void touch_ll_get_group_mask(uint16_t *group1_mask, uint16_t *group2_mask)
{
    *group1_mask = TOUCH_LL_BITS_SWAP(SENS.sar_touch_enable.touch_pad_outen1);
    *group2_mask = TOUCH_LL_BITS_SWAP(SENS.sar_touch_enable.touch_pad_outen2);
}

/**
 * 清除触摸传感器组掩码。
 *
 * @param set1_mask 用于接受触摸传感器信号组1的位掩码的指针，它是一个10位值
 * @param set2_mask 用于接受触摸传感器信号组2的位掩码的指针，它是一个10位值
 */
static inline void touch_ll_clear_group_mask(uint16_t group1_mask, uint16_t group2_mask)
{
    SENS.sar_touch_enable.touch_pad_outen1 &= TOUCH_LL_BITS_SWAP(~group1_mask);
    SENS.sar_touch_enable.touch_pad_outen2 &= TOUCH_LL_BITS_SWAP(~group2_mask);
}

/**
 * 获取触摸传感器状态，通常用于ISR中，以确定哪些焊盘被“触摸”。
 *
 * @param status_mask 触摸传感器状态。e、 g.触摸1触发状态为“status_mask&（BIT1）”。
 */
static inline void touch_ll_read_trigger_status_mask(uint32_t *status_mask)
{
    *status_mask = TOUCH_LL_BITS_SWAP(SENS.sar_touch_ctrl2.touch_meas_en);
}

/**
 * 清除所有触摸传感器状态。
 */
static inline void touch_ll_clear_trigger_status_mask(void)
{
    SENS.sar_touch_ctrl2.touch_meas_en_clr = 1;
}

/**
 * 启用触摸板中断。
 */
static inline void touch_ll_intr_enable(void)
{
    RTCCNTL.int_ena.rtc_touch = 1;
}

/**
 * 禁用触摸板中断。
 */
static inline void touch_ll_intr_disable(void)
{
    RTCCNTL.int_ena.rtc_touch = 0;
}

/**
 * 清除触摸板中断。
 */
static inline void touch_ll_intr_clear(void)
{
    RTCCNTL.int_clr.rtc_touch = 1;
}

/**
 * 从寄存器中获取触摸传感器原始数据（触摸传感器计数器值）。没有障碍。
 *
 * @param touch_num 触摸板索引。
 * @return 用于接受触摸传感器值的touch_value指针。
 */
static inline uint32_t touch_ll_read_raw_data(touch_pad_t touch_num)
{
    touch_pad_t tp_wrap = touch_ll_num_wrap(touch_num);
    return ((tp_wrap & 0x1) ? HAL_FORCE_READ_U32_REG_FIELD(SENS.touch_meas[tp_wrap / 2], l_val) :
                              HAL_FORCE_READ_U32_REG_FIELD(SENS.touch_meas[tp_wrap / 2], h_val));
}

/**
 * 获取触摸传感器测量状态。没有障碍。
 *
 * @return
 *      -如果触摸传感器测量完成。
 */
static inline bool touch_ll_meas_is_done(void)
{
    return (bool)SENS.sar_touch_ctrl2.touch_meas_done;
}

#ifdef __cplusplus
}
#endif

