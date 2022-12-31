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
#include "soc/soc_caps.h"
#include "soc/sens_struct.h"
#include "soc/rtc_cntl_struct.h"
#include "soc/rtc_io_struct.h"
#include "hal/touch_sensor_types.h"

#ifdef __cplusplus
extern "C" {
#endif

#define TOUCH_LL_READ_RAW           0x0
#define TOUCH_LL_READ_BENCHMARK      0x2
#define TOUCH_LL_READ_SMOOTH        0x3
#define TOUCH_LL_TIMER_FORCE_DONE   0x3
#define TOUCH_LL_TIMER_DONE         0x0

/**
 * 设置触摸传感器的充电和放电时间。
 *
 * @param meas_timers 触摸通道的每个测量过程中的充电和放电时间。定时器频率为8Mhz。范围：0~0xffff。
 */
static inline void touch_ll_set_meas_times(uint16_t meas_time)
{
    //触摸通道的每个测量过程中的充电和放电时间。
    HAL_FORCE_MODIFY_U32_REG_FIELD(RTCCNTL.touch_ctrl1, touch_meas_num, meas_time);
    //TOUCH_START和TOUCH_XPD之间的等待周期（8MHz）
    HAL_FORCE_MODIFY_U32_REG_FIELD(RTCCNTL.touch_ctrl2, touch_xpd_wait, SOC_TOUCH_PAD_MEASURE_WAIT_MAX); //等待电压稳定
}

/**
 * 获取触摸传感器的充电和放电时间。
 *
 * @param meas_times 用于接受充电和放电次数计数的指针。
 */
static inline void touch_ll_get_measure_times(uint16_t *meas_time)
{
    *meas_time = HAL_FORCE_READ_U32_REG_FIELD(RTCCNTL.touch_ctrl1, touch_meas_num);
}

/**
 * 设置触摸传感器睡眠时间。
 *
 * @param sleep_cycle  每次测量后，触摸传感器将休眠。sleep_cycle决定每次测量之间的间隔。t_sleep=sleep_cycle/（RTC_SLOW_CLK频率）。RTC_SLOW_CLK的近似频率值可以使用RTC_CLK_SLOW_freq_get_hz函数获得。
 */
static inline void touch_ll_set_sleep_time(uint16_t sleep_time)
{
    // 触摸传感器睡眠周期时间=sleep_cycle/RTC_SLOW_CLK（90k）
    HAL_FORCE_MODIFY_U32_REG_FIELD(RTCCNTL.touch_ctrl1, touch_sleep_cycles, sleep_time);
}

/**
 * 获取触摸传感器睡眠时间。
 *
 * @param sleep_cycle  用于接受睡眠周期号的指针。
 */
static inline void touch_ll_get_sleep_time(uint16_t *sleep_time)
{
    *sleep_time = HAL_FORCE_READ_U32_REG_FIELD(RTCCNTL.touch_ctrl1, touch_sleep_cycles);
}

/**
 * 设置通道的触摸传感器高电压阈值。触摸传感器通过对通道进行充电和放电来测量通道电容值。因此，高阈值应该小于电源电压。
 *
 * @param refh 通道的高电压阈值。
 */
static inline void touch_ll_set_voltage_high(touch_high_volt_t refh)
{
    RTCCNTL.touch_ctrl2.touch_drefh = refh;
}

/**
 * 获取通道的触摸传感器高电压阈值。触摸传感器通过对通道进行充电和放电来测量通道电容值。因此，高阈值应该小于电源电压。
 *
 * @param refh 通道的高电压阈值。
 */
static inline void touch_ll_get_voltage_high(touch_high_volt_t *refh)
{
    *refh = (touch_high_volt_t)RTCCNTL.touch_ctrl2.touch_drefh;
}

/**
 * 设置触摸传感器放电的低电压阈值。触摸传感器通过对通道进行充电和放电来测量通道电容值。
 *
 * @param refl 放电的低电压阈值。
 */
static inline void touch_ll_set_voltage_low(touch_low_volt_t refl)
{
    RTCCNTL.touch_ctrl2.touch_drefl = refl;
}

/**
 * 获取触摸传感器低电压放电阈值。触摸传感器通过对通道进行充电和放电来测量通道电容值。
 *
 * @param refl 放电的低电压阈值。
 */
static inline void touch_ll_get_voltage_low(touch_low_volt_t *refl)
{
    *refl = (touch_low_volt_t)RTCCNTL.touch_ctrl2.touch_drefl;
}

/**
 * 设置触摸传感器的高电压衰减通道。实际充电阈值是高电压阈值减去衰减值。触摸传感器通过对通道进行充电和放电来测量通道电容值。因此，高阈值应该小于电源电压。
 *
 * @param refh 通道的高电压阈值。
 */
static inline void touch_ll_set_voltage_attenuation(touch_volt_atten_t atten)
{
    RTCCNTL.touch_ctrl2.touch_drange = atten;
}

/**
 * 获取触摸传感器的高电压衰减通道。实际充电阈值是高电压阈值减去衰减值。触摸传感器通过对通道进行充电和放电来测量通道电容值。因此，高阈值应该小于电源电压。
 *
 * @param refh 通道的高电压阈值。
 */
static inline void touch_ll_get_voltage_attenuation(touch_volt_atten_t *atten)
{
    *atten = (touch_volt_atten_t)RTCCNTL.touch_ctrl2.touch_drange;
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
    RTCIO.touch_pad[touch_num].tie_opt = opt;
}

/**
 * 获取每次测量的触摸通道的初始电压状态。
 *
 * @param touch_num 触摸板索引。
 * @param opt 初始电压状态。
 */
static inline void touch_ll_get_tie_option(touch_pad_t touch_num, touch_tie_opt_t *opt)
{
    *opt = (touch_tie_opt_t)RTCIO.touch_pad[touch_num].tie_opt;
}

/**
 * 设置触摸传感器FSM模式。测量动作可以由硬件计时器以及软件指令触发。
 *
 * @param mode FSM模式。
 */
static inline void touch_ll_set_fsm_mode(touch_fsm_mode_t mode)
{
    RTCCNTL.touch_ctrl2.touch_start_force = mode;
}

/**
 * 获取触摸传感器FSM模式。测量动作可以由硬件计时器以及软件指令触发。
 *
 * @param mode FSM模式。
 */
static inline void touch_ll_get_fsm_mode(touch_fsm_mode_t *mode)
{
    *mode = (touch_fsm_mode_t)RTCCNTL.touch_ctrl2.touch_start_force;
}

/**
 * 启用/禁用触摸传感器的时钟门。
 *
 * @param enable 真/假。
 */
static inline void touch_ll_clkgate(bool enable)
{
    RTCCNTL.touch_ctrl2.touch_clkgate_en = enable; //启用FSM的触摸时钟。或强制启用。
}

/**
 * 获取触摸传感器FSM状态。
 * @return
 *          -true：fsm状态为打开。
 *          -false：fsm状态已关闭。
 */
static inline bool touch_ll_clkgate_get_state(void)
{
    return RTCCNTL.touch_ctrl2.touch_clkgate_en;
}

/**
 * 触摸计时器触发测量并始终等待测量完成。触摸计时器的强制完成确保计时器始终可以获得测量完成信号。
 */
static inline void touch_ll_timer_force_done(void)
{
    RTCCNTL.touch_ctrl2.touch_timer_force_done = TOUCH_LL_TIMER_FORCE_DONE;
    RTCCNTL.touch_ctrl2.touch_timer_force_done = TOUCH_LL_TIMER_DONE;
}

/**
 * 启动触摸传感器FSM计时器。测量动作可以由硬件计时器以及软件指令触发。
 */
static inline void touch_ll_start_fsm(void)
{
    /**
     * 触摸计时器触发测量并始终等待测量完成。触摸计时器的强制完成确保计时器始终可以获得测量完成信号。
     */
    RTCCNTL.touch_ctrl2.touch_timer_force_done = TOUCH_LL_TIMER_FORCE_DONE;
    RTCCNTL.touch_ctrl2.touch_timer_force_done = TOUCH_LL_TIMER_DONE;
    RTCCNTL.touch_ctrl2.touch_slp_timer_en = (RTCCNTL.touch_ctrl2.touch_start_force == TOUCH_FSM_MODE_TIMER ? 1 : 0);
}

/**
 * 停止触摸传感器FSM计时器。测量动作可以由硬件计时器以及软件指令触发。
 */
static inline void touch_ll_stop_fsm(void)
{
    RTCCNTL.touch_ctrl2.touch_start_en = 0; //停止触摸fsm
    RTCCNTL.touch_ctrl2.touch_slp_timer_en = 0;
    RTCCNTL.touch_ctrl2.touch_timer_force_done = TOUCH_LL_TIMER_FORCE_DONE;
    RTCCNTL.touch_ctrl2.touch_timer_force_done = TOUCH_LL_TIMER_DONE;
}

/**
 * 获取触摸传感器FSM计时器状态。
 * @return
 *     -true：启用FSM
 *     -false:FSM已禁用
 */
static inline bool touch_ll_get_fsm_state(void)
{
    return (bool)RTCCNTL.touch_ctrl2.touch_slp_timer_en;
}

/**
 * 触发触摸传感器测量，仅支持FSM的SW模式。
 */
static inline void touch_ll_start_sw_meas(void)
{
    RTCCNTL.touch_ctrl2.touch_start_en = 0;
    RTCCNTL.touch_ctrl2.touch_start_en = 1;
}

/**
 * 设置触摸传感器的触发阈值。阈值确定触摸传感器的灵敏度。阈值是触发状态的原始值减去基准值。
 *
 * @note  如果设置为“TOUCH_PAD_THRESHOLD_MAX”，则不会触发触摸。
 * @param touch_num 触摸板索引
 * @param threshold 触摸传感器的阈值。
 */
static inline void touch_ll_set_threshold(touch_pad_t touch_num, uint32_t threshold)
{
    SENS.touch_thresh[touch_num - 1].thresh = threshold;
}

/**
 * 获取触摸传感器的触发阈值。阈值确定触摸传感器的灵敏度。阈值是触发状态的原始值减去基准值。
 *
 * @param touch_num 触摸板索引。
 * @param threshold 接受阈值的指针。
 */
static inline void touch_ll_get_threshold(touch_pad_t touch_num, uint32_t *threshold)
{
    *threshold = SENS.touch_thresh[touch_num - 1].thresh;
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
    RTCCNTL.touch_scan_ctrl.touch_scan_pad_map  |= (enable_mask & TOUCH_PAD_BIT_MASK_ALL);
    SENS.sar_touch_conf.touch_outen |= (enable_mask & TOUCH_PAD_BIT_MASK_ALL);
}

/**
 * 获取触摸传感器通道掩码。
 *
 * @param enable_mask 触摸传感器扫描组的位掩码。e、 g.TOUCH_PAD_NUM1->位（1）
 */
static inline void touch_ll_get_channel_mask(uint16_t *enable_mask)
{
    *enable_mask = SENS.sar_touch_conf.touch_outen \
                   & RTCCNTL.touch_scan_ctrl.touch_scan_pad_map \
                   & TOUCH_PAD_BIT_MASK_ALL;
}

/**
 * 通过位掩码禁用触摸传感器通道。
 *
 * @param enable_mask 触摸传感器扫描组的位掩码。e、 g.TOUCH_PAD_NUM1->位（1）
 */
static inline void touch_ll_clear_channel_mask(uint16_t disable_mask)
{
    SENS.sar_touch_conf.touch_outen &= ~(disable_mask & TOUCH_PAD_BIT_MASK_ALL);
    RTCCNTL.touch_scan_ctrl.touch_scan_pad_map  &= ~(disable_mask & TOUCH_PAD_BIT_MASK_ALL);
}

/**
 * 获取触摸传感器触发状态，通常用于ISR中，以确定哪些焊盘被“触摸”。
 *
 * @param status_mask 触摸传感器状态。e、 g.触摸1触发状态为“status_mask&（BIT1）”。
 */
static inline void touch_ll_read_trigger_status_mask(uint32_t *status_mask)
{
    *status_mask = SENS.sar_touch_chn_st.touch_pad_active;
}

/**
 * 清除所有触摸传感器状态。
 *
 * @note 通常不需要手动拆卸。
 */
static inline void touch_ll_clear_trigger_status_mask(void)
{
    SENS.sar_touch_conf.touch_status_clr = 1;
}

/**
 * 从寄存器中获取触摸传感器原始数据（触摸传感器计数器值）。没有障碍。
 *
 * @param touch_num 触摸板索引。
 * @return 用于接受触摸传感器值的touch_value指针。
 */
static inline uint32_t IRAM_ATTR touch_ll_read_raw_data(touch_pad_t touch_num)
{
    SENS.sar_touch_conf.touch_data_sel = TOUCH_LL_READ_RAW;
    return SENS.sar_touch_status[touch_num - 1].touch_pad_data;
}

/**
 * 获取触摸传感器测量状态。没有障碍。
 *
 * @return
 *      -如果触摸传感器测量完成。
 */
static inline bool touch_ll_meas_is_done(void)
{
    return (bool)SENS.sar_touch_chn_st.touch_meas_done;
}

/*************************仅限esp32s2*************************/

/**
 * 重置整个触摸模块。
 *
 * @note 在“touch_pad_fsm_stop”之后调用此函数。
 */
static inline void touch_ll_reset(void)
{
    RTCCNTL.touch_ctrl2.touch_reset = 0;
    RTCCNTL.touch_ctrl2.touch_reset = 1;
    RTCCNTL.touch_ctrl2.touch_reset = 0;    // 应设置为0。
}

/**
 * 将触摸通道的连接类型设置为空闲状态。当信道处于测量模式时，其他初始化信道处于空闲模式。触摸通道通常与迹线相邻，因此空闲通道的连接状态影响测试通道的稳定性和灵敏度。“CONN_HIGHZ”（高电阻）设置增加了触摸通道的灵敏度。“CONN_GND”（接地）设置提高了触摸通道的稳定性。
 *
 * @param type  选择空闲通道连接到高电阻状态或接地。
 */
static inline void touch_ll_set_idle_channel_connect(touch_pad_conn_type_t type)
{
    RTCCNTL.touch_scan_ctrl.touch_inactive_connection = type;
}

/**
 * 将触摸通道的连接类型设置为空闲状态。当信道处于测量模式时，其他初始化信道处于空闲模式。触摸通道通常与迹线相邻，因此空闲通道的连接状态影响测试通道的稳定性和灵敏度。“CONN_HIGHZ”（高电阻）设置增加了触摸通道的灵敏度。“CONN_GND”（接地）设置提高了触摸通道的稳定性。
 *
 * @param type  选择空闲通道连接到高电阻状态或接地。
 */
static inline void touch_ll_get_idle_channel_connect(touch_pad_conn_type_t *type)
{
    *type = RTCCNTL.touch_scan_ctrl.touch_inactive_connection;
}

/**
 * 获取当前测量通道。触摸传感器测量为循环扫描模式。
 *
 * @return
 *      -触摸通道编号
 */
static inline touch_pad_t IRAM_ATTR touch_ll_get_current_meas_channel(void)
{
    return (touch_pad_t)(SENS.sar_touch_status0.touch_scan_curr);
}

/**
 * 通过位掩码启用触摸传感器中断。
 *
 * @param type 中断类型
 */
static inline void touch_ll_intr_enable(touch_pad_intr_mask_t int_mask)
{
    if (int_mask & TOUCH_PAD_INTR_MASK_DONE) {
        RTCCNTL.int_ena.rtc_touch_done = 1;
    }
    if (int_mask & TOUCH_PAD_INTR_MASK_ACTIVE) {
        RTCCNTL.int_ena.rtc_touch_active = 1;
    }
    if (int_mask & TOUCH_PAD_INTR_MASK_INACTIVE) {
        RTCCNTL.int_ena.rtc_touch_inactive = 1;
    }
    if (int_mask & TOUCH_PAD_INTR_MASK_SCAN_DONE) {
        RTCCNTL.int_ena.rtc_touch_scan_done = 1;
    }
    if (int_mask & TOUCH_PAD_INTR_MASK_TIMEOUT) {
        RTCCNTL.int_ena.rtc_touch_timeout = 1;
    }
}

/**
 * 通过位掩码禁用触摸传感器中断。
 *
 * @param type 中断类型
 */
static inline void touch_ll_intr_disable(touch_pad_intr_mask_t int_mask)
{
    if (int_mask & TOUCH_PAD_INTR_MASK_DONE) {
        RTCCNTL.int_ena.rtc_touch_done = 0;
    }
    if (int_mask & TOUCH_PAD_INTR_MASK_ACTIVE) {
        RTCCNTL.int_ena.rtc_touch_active = 0;
    }
    if (int_mask & TOUCH_PAD_INTR_MASK_INACTIVE) {
        RTCCNTL.int_ena.rtc_touch_inactive = 0;
    }
    if (int_mask & TOUCH_PAD_INTR_MASK_SCAN_DONE) {
        RTCCNTL.int_ena.rtc_touch_scan_done = 0;
    }
    if (int_mask & TOUCH_PAD_INTR_MASK_TIMEOUT) {
        RTCCNTL.int_ena.rtc_touch_timeout = 0;
    }
}

/**
 * 通过位掩码清除触摸传感器中断。
 *
 * @param int_mask 清除中断的键盘掩码
 */
static inline void touch_ll_intr_clear(touch_pad_intr_mask_t int_mask)
{
    if (int_mask & TOUCH_PAD_INTR_MASK_DONE) {
        RTCCNTL.int_clr.rtc_touch_done = 1;
    }
    if (int_mask & TOUCH_PAD_INTR_MASK_ACTIVE) {
        RTCCNTL.int_clr.rtc_touch_active = 1;
    }
    if (int_mask & TOUCH_PAD_INTR_MASK_INACTIVE) {
        RTCCNTL.int_clr.rtc_touch_inactive = 1;
    }
    if (int_mask & TOUCH_PAD_INTR_MASK_SCAN_DONE) {
        RTCCNTL.int_clr.rtc_touch_scan_done = 1;
    }
    if (int_mask & TOUCH_PAD_INTR_MASK_TIMEOUT) {
        RTCCNTL.int_clr.rtc_touch_timeout = 1;
    }
}

/**
 * 获取触摸传感器中断状态的位掩码。
 *
 * @return 类型中断类型
 */
static inline uint32_t touch_ll_read_intr_status_mask(void)
{
    uint32_t intr_st = RTCCNTL.int_st.val;
    uint32_t intr_msk = 0;

    if (intr_st & RTC_CNTL_TOUCH_DONE_INT_ST_M) {
        intr_msk |= TOUCH_PAD_INTR_MASK_DONE;
    }
    if (intr_st & RTC_CNTL_TOUCH_ACTIVE_INT_ST_M) {
        intr_msk |= TOUCH_PAD_INTR_MASK_ACTIVE;
    }
    if (intr_st & RTC_CNTL_TOUCH_INACTIVE_INT_ST_M) {
        intr_msk |= TOUCH_PAD_INTR_MASK_INACTIVE;
    }
    if (intr_st & RTC_CNTL_TOUCH_SCAN_DONE_INT_ST_M) {
        intr_msk |= TOUCH_PAD_INTR_MASK_SCAN_DONE;
    }
    if (intr_st & RTC_CNTL_TOUCH_TIMEOUT_INT_ST_M) {
        intr_msk |= TOUCH_PAD_INTR_MASK_TIMEOUT;
    }
    return (intr_msk & TOUCH_PAD_INTR_MASK_ALL);
}

/**
 * 启用所有触摸传感器通道测量的超时检查。当触摸通道的触摸读数超过测量阈值时，如果启用：将产生超时中断，并进入下一个通道测量。如果禁用：FSM始终在信道上，直到该信道的测量结束。
 *
 * @note 在启用超时阈值之前，请正确设置超时阈值。
 */
static inline void touch_ll_timeout_enable(void)
{
    RTCCNTL.touch_timeout_ctrl.touch_timeout_en = 1;
}

/**
 * 禁用所有触摸传感器通道测量的超时检查。当触摸通道的触摸读数超过测量阈值时，如果启用：将产生超时中断，并进入下一个通道测量。如果禁用：FSM始终在信道上，直到该信道的测量结束。
 *
 * @note 在启用超时阈值之前，请正确设置超时阈值。
 */
static inline void touch_ll_timeout_disable(void)
{
    RTCCNTL.touch_timeout_ctrl.touch_timeout_en = 0;
}

/**
 * 为所有触摸传感器通道测量设置超时阈值。与触摸读数相比。
 *
 * @param threshold 设置为在一个通道上测量的最大时间。
 */
static inline void touch_ll_timeout_set_threshold(uint32_t threshold)
{
    RTCCNTL.touch_timeout_ctrl.touch_timeout_num = threshold;
}

/**
 * 获取所有触摸传感器通道测量的超时阈值。与触摸读数相比。
 *
 * @param threshold 指向超时阈值。
 */
static inline void touch_ll_timeout_get_threshold(uint32_t *threshold)
{
    *threshold = RTCCNTL.touch_timeout_ctrl.touch_timeout_num;
}

/************************过滤器寄存器设置************************/

/**
 * 获取通过过滤原始数据获得的平滑数据。
 *
 * @param touch_num 触摸板索引
 * @param smooth_data 平滑数据指针
 */
static inline void IRAM_ATTR touch_ll_filter_read_smooth(touch_pad_t touch_num, uint32_t *smooth_data)
{
    SENS.sar_touch_conf.touch_data_sel = TOUCH_LL_READ_SMOOTH;
    *smooth_data = SENS.sar_touch_status[touch_num - 1].touch_pad_data;
}

/**
 * 获取触摸传感器的基准值。
 *
 * @note 初始化后，基准值为第一个测量周期内的最大值。
 * @param touch_num 触摸板索引
 * @param touch_value 接受触摸传感器值的指针
 */
static inline void IRAM_ATTR touch_ll_read_benchmark(touch_pad_t touch_num, uint32_t *benchmark)
{
    SENS.sar_touch_conf.touch_data_sel = TOUCH_LL_READ_BENCHMARK;
    *benchmark = SENS.sar_touch_status[touch_num - 1].touch_pad_data;
}

/**
 * 强制将基准重置为触摸传感器的原始数据。
 *
 * @note 如果调用此API，请确保首先启用时钟门（`touch_ll_clkgate`）。
 * @param touch_num 触摸板索引
 *                  -TOUCH_PAD_MAX重置所有通道的基线。
 */
static inline void touch_ll_reset_benchmark(touch_pad_t touch_num)
{
    /* 清除触摸通道以初始化通道值（基准、raw_data）。
     */
    if (touch_num == TOUCH_PAD_MAX) {
        SENS.sar_touch_chn_st.touch_channel_clr = TOUCH_PAD_BIT_MASK_ALL;
    } else {
        SENS.sar_touch_chn_st.touch_channel_clr = (1U << touch_num);
    }
}

/**
 * 设置过滤器模式。滤波器的输入是触摸读数的原始值，滤波器的输出涉及触摸状态的判断。
 *
 * @param mode 过滤器模式类型。请参阅`touch_filter_mode_t``。
 */
static inline void touch_ll_filter_set_filter_mode(touch_filter_mode_t mode)
{
    RTCCNTL.touch_filter_ctrl.touch_filter_mode = mode;
}

/**
 * 获取过滤器模式。滤波器的输入是触摸读数的原始值，滤波器的输出涉及触摸状态的判断。
 *
 * @param mode 过滤器模式类型。请参阅`touch_filter_mode_t``。
 */
static inline void touch_ll_filter_get_filter_mode(touch_filter_mode_t *mode)
{
    *mode = (touch_filter_mode_t)RTCCNTL.touch_filter_ctrl.touch_filter_mode;
}

/**
 * 设置过滤器模式。滤波器的输入是原始数据，输出是平滑数据。平滑数据用于确定触摸状态。
 *
 * @param mode 过滤器模式类型。请参阅“touch_smooth_mode_t”。
 */
static inline void touch_ll_filter_set_smooth_mode(touch_smooth_mode_t mode)
{
    RTCCNTL.touch_filter_ctrl.touch_smooth_lvl = mode;
}

/**
 * 获取过滤器模式。平滑数据用于确定触摸状态。
 *
 * @param mode 过滤器模式类型。请参阅“touch_smooth_mode_t”。
 */
static inline void touch_ll_filter_get_smooth_mode(touch_smooth_mode_t *mode)
{
    *mode = RTCCNTL.touch_filter_ctrl.touch_smooth_lvl;
}

/**
 * 设置反跳计数，如“n”。如果测量值持续超过阈值“n+1”次，则确定触摸传感器状态改变。
 *
 * @param dbc_cnt 取消跳动计数值。
 */
static inline void touch_ll_filter_set_debounce(uint32_t dbc_cnt)
{
    RTCCNTL.touch_filter_ctrl.touch_debounce = dbc_cnt;
}

/**
 * 获取防抖计数。
 *
 * @param dbc_cnt 取消跳动计数值。
 */
static inline void touch_ll_filter_get_debounce(uint32_t *dbc_cnt)
{
    *dbc_cnt = RTCCNTL.touch_filter_ctrl.touch_debounce;
}

/**
 * 设置噪声阈值系数。更高=抗噪音能力更强。实际噪声应小于（噪声系数触摸阈值）。范围：0~3。系数为0:4/8；1: 3/8; 2: 2/8; 3: 1;
 *
 * @param hys_thr 噪声阈值系数。
 */
static inline void touch_ll_filter_set_noise_thres(uint32_t noise_thr)
{
    RTCCNTL.touch_filter_ctrl.touch_noise_thres = noise_thr;
    RTCCNTL.touch_filter_ctrl.config2 = noise_thr;
    RTCCNTL.touch_filter_ctrl.config1 = 0xF;
    RTCCNTL.touch_filter_ctrl.config3 = 2;
}

/**
 * 获取噪声阈值系数。更高=抗噪音能力更强。实际噪声应小于（噪声系数触摸阈值）。范围：0~3。系数为0:4/8；1: 3/8; 2: 2/8; 3: 1;
 *
 * @param noise_thr 噪声阈值系数。
 */
static inline void touch_ll_filter_get_noise_thres(uint32_t *noise_thr)
{
    *noise_thr = RTCCNTL.touch_filter_ctrl.touch_noise_thres;
}

/**
 * 设置抖动滤波器步长。如果滤波器模式为抖动，应设置抖动的滤波器步长。范围：0~15
 *
 * @param step 数据的步长更改。
 */
static inline void touch_ll_filter_set_jitter_step(uint32_t step)
{
    RTCCNTL.touch_filter_ctrl.touch_jitter_step = step;
}

/**
 * 获取抖动滤波器步长。如果滤波器模式为抖动，应设置抖动的滤波器步长。范围：0~15
 *
 * @param step 数据的步长更改。
 */
static inline void touch_ll_filter_get_jitter_step(uint32_t *step)
{
    *step = RTCCNTL.touch_filter_ctrl.touch_jitter_step;
}

/**
 * 启用触摸传感器过滤器和检测算法。有关检测算法的更多详细信息，请参阅应用程序文档。
 */
static inline void touch_ll_filter_enable(void)
{
    RTCCNTL.touch_filter_ctrl.touch_filter_en = 1;
}

/**
 * 禁用触摸传感器过滤器和检测算法。有关检测算法的更多详细信息，请参阅应用程序文档。
 */
static inline void touch_ll_filter_disable(void)
{
    RTCCNTL.touch_filter_ctrl.touch_filter_en = 0;
}

/************************去噪寄存器设置************************/

/**
 * 启用降噪功能。T0是不具有相应外部GPIO的内部通道。T0将与测量的信道Tn同时工作。最后，Tn的实际测量值是减去T0的低位后的值。此去噪功能可滤除所有信道上引入的干扰，例如电源和外部EMI引入的噪声。
 */
static inline void touch_ll_denoise_enable(void)
{
    RTCCNTL.touch_scan_ctrl.touch_denoise_en = 1;
}

/**
 * 启用降噪功能。T0是不具有相应外部GPIO的内部通道。T0将与测量的信道Tn同时工作。最后，Tn的实际测量值是减去T0的低位后的值。此去噪功能可滤除所有信道上引入的干扰，例如电源和外部EMI引入的噪声。
 */
static inline void touch_ll_denoise_disable(void)
{
    RTCCNTL.touch_scan_ctrl.touch_denoise_en = 0;
}

/**
 * 设置降噪通道的内部参考电容。选择适当的内部参考电容值，使去噪通道的读数最接近被测通道的读数。
 *
 * @param cap_level 电容水平。
 */
static inline void touch_ll_denoise_set_cap_level(touch_pad_denoise_cap_t cap_level)
{
    RTCCNTL.touch_ctrl2.touch_refc = cap_level;
}

/**
 * 获得去噪通道的内部参考电容。选择适当的内部参考电容值，使去噪通道的读数最接近被测通道的读数。
 *
 * @param cap_level 电容水平。
 */
static inline void touch_ll_denoise_get_cap_level(touch_pad_denoise_cap_t *cap_level)
{
    *cap_level = RTCCNTL.touch_ctrl2.touch_refc;
}

/**
 * 设置去噪通道的去噪范围。通过测量去噪信道的噪声幅度来确定。
 *
 * @param grade 去噪通道的去噪范围。
 */
static inline void touch_ll_denoise_set_grade(touch_pad_denoise_grade_t grade)
{
    RTCCNTL.touch_scan_ctrl.touch_denoise_res = grade;
}

/**
 * 设置去噪通道的去噪范围。通过测量去噪信道的噪声幅度来确定。
 *
 * @param grade 去噪通道的去噪范围。
 */
static inline void touch_ll_denoise_get_grade(touch_pad_denoise_grade_t *grade)
{
    *grade = RTCCNTL.touch_scan_ctrl.touch_denoise_res;
}

/**
 * 读取去噪测量值（TOUCH_PAD_NUM0）。
 *
 * @param denoise 去噪值。
 */
static inline void touch_ll_denoise_read_data(uint32_t *data)
{
    *data = SENS.sar_touch_status0.touch_denoise_data;
}

/************************防水寄存器设置************************/

/**
 * 设置保护板的触摸通道使用。
 *
 * @param pad_num 触摸传感器通道编号。
 */
static inline void touch_ll_waterproof_set_guard_pad(touch_pad_t pad_num)
{
    RTCCNTL.touch_scan_ctrl.touch_out_ring = pad_num;
}

/**
 * 获得用于保护垫的触摸通道。
 *
 * @param pad_num 触摸传感器通道编号。
 */
static inline void touch_ll_waterproof_get_guard_pad(touch_pad_t *pad_num)
{
    *pad_num = RTCCNTL.touch_scan_ctrl.touch_out_ring;
}

/**
 * 设置屏蔽通道的最大等效电容。屏蔽通道的等效电容可以从去噪通道的读数中计算出来。
 *
 * @param pad_num 触摸传感器通道编号。
 */
static inline void touch_ll_waterproof_set_sheild_driver(touch_pad_shield_driver_t driver_level)
{
    RTCCNTL.touch_scan_ctrl.touch_bufdrv = driver_level;
}

/**
 * 获取屏蔽通道的最大等效电容。屏蔽通道的等效电容可以从去噪通道的读数中计算出来。
 *
 * @param pad_num 触摸传感器通道编号。
 */
static inline void touch_ll_waterproof_get_sheild_driver(touch_pad_shield_driver_t *driver_level)
{
    *driver_level = RTCCNTL.touch_scan_ctrl.touch_bufdrv;
}

/**
 * 启用防水功能参数。
 *
 * 防水功能包括屏蔽信道（TOUCH_PAD_NUM14）和保护信道。保护垫用于检测覆盖触摸面板的大面积水。屏蔽垫用于屏蔽覆盖触摸面板的水滴的影响。它通常设计为网格，并放置在触摸按钮周围。
 */
static inline void touch_ll_waterproof_enable(void)
{
    RTCCNTL.touch_scan_ctrl.touch_shield_pad_en = 1;
}

/**
 * 禁用防水功能参数。
 */
static inline void touch_ll_waterproof_disable(void)
{
    RTCCNTL.touch_scan_ctrl.touch_shield_pad_en = 0;
}

/************************接近寄存器设置************************/

/**
 * 设置接近板的触摸通道编号。如果禁用接近焊盘，请将该焊盘指向`TOUCH_pad_NUM0`
 *
 * @param prox_pad 三个接近焊盘的阵列。
 */
static inline void touch_ll_proximity_set_channel_num(const touch_pad_t prox_pad[])
{
    SENS.sar_touch_conf.touch_approach_pad0 = prox_pad[0];
    SENS.sar_touch_conf.touch_approach_pad1 = prox_pad[1];
    SENS.sar_touch_conf.touch_approach_pad2 = prox_pad[2];
}

/**
 * 获取接近板的触摸通道编号。如果禁用接近焊盘，请将该焊盘指向`TOUCH_pad_NUM0`
 *
 * @param prox_pad 三个接近焊盘的阵列。
 */
static inline void touch_ll_proximity_get_channel_num(touch_pad_t prox_pad[])
{
    prox_pad[0] = SENS.sar_touch_conf.touch_approach_pad0;
    prox_pad[1] = SENS.sar_touch_conf.touch_approach_pad1;
    prox_pad[2] = SENS.sar_touch_conf.touch_approach_pad2;
}

/**
 * 设置接近板的累计测量时间。
 *
 * @param times 累计测量周期数。
 */
static inline void touch_ll_proximity_set_meas_times(uint32_t times)
{
    HAL_FORCE_MODIFY_U32_REG_FIELD(RTCCNTL.touch_approach, touch_approach_meas_time, times);
}

/**
 * 获取接近板的累计测量时间。
 *
 * @param times 累计测量周期数。
 */
static inline void touch_ll_proximity_get_meas_times(uint32_t *times)
{
    *times = HAL_FORCE_READ_U32_REG_FIELD(RTCCNTL.touch_approach, touch_approach_meas_time);
}

/**
 * 读取接近焊盘的当前累计测量时间。
 *
 * @param times 累计测量周期数。
 */
static inline void touch_ll_proximity_read_meas_cnt(touch_pad_t touch_num, uint32_t *cnt)
{
    if (SENS.sar_touch_conf.touch_approach_pad0 == touch_num) {
        *cnt = HAL_FORCE_READ_U32_REG_FIELD(SENS.sar_touch_appr_status, touch_approach_pad0_cnt);
    } else if (SENS.sar_touch_conf.touch_approach_pad1 == touch_num) {
        *cnt = HAL_FORCE_READ_U32_REG_FIELD(SENS.sar_touch_appr_status, touch_approach_pad1_cnt);
    } else if (SENS.sar_touch_conf.touch_approach_pad2 == touch_num) {
        *cnt = HAL_FORCE_READ_U32_REG_FIELD(SENS.sar_touch_appr_status, touch_approach_pad2_cnt);
    }
}

/**
 * 检查触摸传感器通道是否为接近板。
 *
 * @param touch_num 触摸传感器通道编号。
 */
static inline bool touch_ll_proximity_pad_check(touch_pad_t touch_num)
{
    if ((SENS.sar_touch_conf.touch_approach_pad0 != touch_num)
            && (SENS.sar_touch_conf.touch_approach_pad1 != touch_num)
            && (SENS.sar_touch_conf.touch_approach_pad2 != touch_num)) {
        return false;
    } else {
        return true;
    }
}

/**************睡眠垫设置***********************/

/**
 * 设置睡眠板的触摸通道编号。
 *
 * @note 深度睡眠模式下仅支持一个触摸传感器通道。
 * @param touch_num 触摸传感器通道编号。
 */
static inline void touch_ll_sleep_set_channel_num(touch_pad_t touch_num)
{
    RTCCNTL.touch_slp_thres.touch_slp_pad = touch_num;
}

/**
 * 获取睡眠板的触摸通道编号。
 *
 * @note 深度睡眠模式下仅支持一个触摸传感器通道。
 * @param touch_num 触摸传感器通道编号。
 */
static inline void touch_ll_sleep_get_channel_num(touch_pad_t *touch_num)
{
    *touch_num = RTCCNTL.touch_slp_thres.touch_slp_pad;
}

/**
 * 设置深度睡眠中触摸传感器的触发阈值。阈值确定触摸传感器的灵敏度。阈值是触发状态的原始值减去基准值。
 *
 * @note 通常，睡眠期间的触摸阈值可以使用睡眠之前的阈值参数参数。
 */
static inline void touch_ll_sleep_set_threshold(uint32_t touch_thres)
{
    RTCCNTL.touch_slp_thres.touch_slp_th = touch_thres;
}

/**
 * 获取深度睡眠中触摸传感器的触发阈值。阈值确定触摸传感器的灵敏度。阈值是触发状态的原始值减去基准值。
 *
 * @note 通常，睡眠期间的触摸阈值可以使用睡眠之前的阈值参数参数。
 */
static inline void touch_ll_sleep_get_threshold(uint32_t *touch_thres)
{
    *touch_thres = RTCCNTL.touch_slp_thres.touch_slp_th;
}

/**
 * 启用睡眠垫的接近功能。
 */
static inline void touch_ll_sleep_enable_approach(void)
{
    RTCCNTL.touch_slp_thres.touch_slp_approach_en = 1;
}

/**
 * 禁用睡眠垫的接近功能。
 */
static inline void touch_ll_sleep_disable_approach(void)
{
    RTCCNTL.touch_slp_thres.touch_slp_approach_en = 0;
}

/**
 * 获取睡眠垫的接近功能状态。
 */
static inline bool touch_ll_sleep_get_approach_status(void)
{
    return (bool)RTCCNTL.touch_slp_thres.touch_slp_approach_en;
}

/**
 * 读取睡眠垫触摸传感器的基准。
 *
 * @param benchmark 用于接受触摸传感器基准值的指针。
 */
static inline void touch_ll_sleep_read_benchmark(uint32_t *benchmark)
{
    SENS.sar_touch_conf.touch_data_sel = TOUCH_LL_READ_BENCHMARK;
    *benchmark = SENS.sar_touch_slp_status.touch_slp_data;
}

static inline void touch_ll_sleep_read_smooth(uint32_t *smooth_data)
{
    SENS.sar_touch_conf.touch_data_sel = TOUCH_LL_READ_SMOOTH;
    *smooth_data = SENS.sar_touch_slp_status.touch_slp_data;
}

/* 解决方法：注意：睡眠板原始数据不在“sar_touch_slp_status”中*/
static inline void touch_ll_sleep_read_data(uint32_t *raw_data)
{
    uint32_t touch_num = RTCCNTL.touch_slp_thres.touch_slp_pad;
    SENS.sar_touch_conf.touch_data_sel = TOUCH_LL_READ_RAW;
    *raw_data = SENS.sar_touch_status[touch_num - 1].touch_pad_data;
}

static inline void touch_ll_sleep_reset_benchmark(void)
{
    RTCCNTL.touch_approach.touch_slp_channel_clr = 1;
}

/**
 * 选择触摸传感器dbias以在睡眠模式下省电。
 *
 * @note 如果改变dbias，触摸传感器的读数将改变。用户应确保阈值。
 */
static inline void touch_ll_sleep_low_power(bool is_low_power)
{
    RTCCNTL.touch_ctrl2.touch_dbias = is_low_power;
}

/**
 * 读取睡眠垫触摸传感器的防抖。
 *
 * @param debounce 用于接受触摸传感器反跳值的指针。
 */
static inline void touch_ll_sleep_read_debounce(uint32_t *debounce)
{
    *debounce = SENS.sar_touch_slp_status.touch_slp_debounce;
}

/**
 * 读取睡眠垫触摸传感器的接近计数。
 * @param proximity_cnt 用于接受触摸传感器接近计数值的指针。
 */
static inline void touch_ll_sleep_read_proximity_cnt(uint32_t *approach_cnt)
{
    *approach_cnt = HAL_FORCE_READ_U32_REG_FIELD(SENS.sar_touch_appr_status, touch_slp_approach_cnt);
}

/**
 * 获取导致从深度睡眠中醒来的触摸板。
 *
 * @param pad_num 导致唤醒的触摸板指针。
 */
static inline void touch_ll_get_wakeup_status(touch_pad_t *pad_num)
{
    *pad_num = (touch_pad_t)RTCCNTL.touch_slp_thres.touch_slp_pad;
}

#ifdef __cplusplus
}
#endif

