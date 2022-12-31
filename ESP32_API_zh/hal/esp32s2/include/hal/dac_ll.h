// 版权所有2019 Espressif Systems（上海）私人有限公司
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

#pragma once

#include <stdlib.h>
#include "hal/misc.h"
#include "soc/dac_periph.h"
#include "hal/dac_types.h"
#include "soc/apb_saradc_struct.h"
#include "soc/sens_struct.h"
#include "soc/rtc_io_struct.h"
#include "soc/apb_saradc_reg.h"

#ifdef __cplusplus
extern "C" {
#endif

/*---------------------------------------------------------------
                    DAC公共设置
---------------------------------------------------------------*/
/**
 * 打开dac模块电源并启动输出电压。
 *
 * @note 通电前，确保DAC PAD设置为RTC PAD和浮动状态。
 * @param channel DAC通道编号。
 */
static inline void dac_ll_power_on(dac_channel_t channel)
{
    SENS.sar_dac_ctrl1.dac_clkgate_en = 1;
    RTCIO.pad_dac[channel].dac_xpd_force = 1;
    RTCIO.pad_dac[channel].xpd_dac = 1;
}

/**
 * 给dac模块通电并停止输出电压。
 *
 * @param channel DAC通道编号。
 */
static inline void dac_ll_power_down(dac_channel_t channel)
{
    RTCIO.pad_dac[channel].dac_xpd_force = 0;
    RTCIO.pad_dac[channel].xpd_dac = 0;
    if (RTCIO.pad_dac[0].xpd_dac == 0 && RTCIO.pad_dac[1].xpd_dac == 0) {
        SENS.sar_dac_ctrl1.dac_clkgate_en = 0;
    }
}

/*---------------------------------------------------------------
                    RTC控制器设置
---------------------------------------------------------------*/
/**
 * 输出电压值（8位）。
 *
 * @param channel DAC通道编号。
 * @param value 输出值。值范围：0~255。对应的电压范围为0v~VDD3P3_RTC。
 */
static inline void dac_ll_update_output_value(dac_channel_t channel, uint8_t value)
{
    if (channel == DAC_CHANNEL_1) {
        SENS.sar_dac_ctrl2.dac_cw_en1 = 0;
        HAL_FORCE_MODIFY_U32_REG_FIELD(RTCIO.pad_dac[channel], dac, value);
    } else if (channel == DAC_CHANNEL_2) {
        SENS.sar_dac_ctrl2.dac_cw_en2 = 0;
        HAL_FORCE_MODIFY_U32_REG_FIELD(RTCIO.pad_dac[channel], dac, value);
    }
}

/**
 * 通过软件重置dac。
 */
static inline void dac_ll_rtc_reset(void)
{
    SENS.sar_dac_ctrl1.dac_reset = 1;
    SENS.sar_dac_ctrl1.dac_reset = 0;
}

/**
 * 启用/禁用ADC1和DAC的同步操作功能。
 *
 * @note  如果启用（默认），ADC RTC控制器采样将导致DAC通道输出电压。
 *
 * @param enable 启用或禁用adc和dac同步功能。
 */
static inline void dac_ll_rtc_sync_by_adc(bool enable)
{
    SENS.sar_amp_ctrl3.sar1_dac_xpd_fsm = enable;
}

/************************************/
/*  DAC余弦波发生器API*/
/************************************/
/**
 * 启用余弦波发生器输出。
 */
static inline void dac_ll_cw_generator_enable(void)
{
    SENS.sar_dac_ctrl1.sw_tone_en = 1;
}

/**
 * 禁用余弦波发生器输出。
 */
static inline void dac_ll_cw_generator_disable(void)
{
    SENS.sar_dac_ctrl1.sw_tone_en = 0;
}

/**
 * 启用DAC通道的余弦波发生器。
 *
 * @param channel DAC通道编号。
 * @param enable
 */
static inline void dac_ll_cw_set_channel(dac_channel_t channel, bool enable)
{
    if (channel == DAC_CHANNEL_1) {
        SENS.sar_dac_ctrl2.dac_cw_en1 = enable;
    } else if (channel == DAC_CHANNEL_2) {
        SENS.sar_dac_ctrl2.dac_cw_en2 = enable;
    }
}

/**
 * 设置余弦波发生器输出的频率。
 *
 * @note 我们知道CLK8M大约是8M，但不知道实际值。因此该频率具有有限的误差。
 * @param freq_hz CW发电机频率。范围：130（130Hz）~ 55000（100KHz）。
 */
static inline void dac_ll_cw_set_freq(uint32_t freq)
{
    uint32_t sw_freq = freq * 0xFFFF / RTC_FAST_CLK_FREQ_APPROX;
    HAL_FORCE_MODIFY_U32_REG_FIELD(SENS.sar_dac_ctrl1, sw_fstep, (sw_freq > 0xFFFF) ? 0xFFFF : sw_freq);
}

/**
 * 设置余弦波发生器输出的振幅。
 *
 * @param channel DAC通道编号。
 * @param scale 振幅的倍数。最大振幅为VDD3P3_RTC。
 */
static inline void dac_ll_cw_set_scale(dac_channel_t channel, dac_cw_scale_t scale)
{
    if (channel == DAC_CHANNEL_1) {
        SENS.sar_dac_ctrl2.dac_scale1 = scale;
    } else if (channel == DAC_CHANNEL_2) {
        SENS.sar_dac_ctrl2.dac_scale2 = scale;
    }
}

/**
 * 设置余弦波发生器输出的相位。
 *
 * @param channel DAC通道编号。
 * @param scale 相位值。
 */
static inline void dac_ll_cw_set_phase(dac_channel_t channel, dac_cw_phase_t phase)
{
    if (channel == DAC_CHANNEL_1) {
        SENS.sar_dac_ctrl2.dac_inv1 = phase;
    } else if (channel == DAC_CHANNEL_2) {
        SENS.sar_dac_ctrl2.dac_inv2 = phase;
    }
}

/**
 * 设置余弦波发生器输出直流分量的电压值。
 *
 * @note 直流偏移设置应在相位设置之后。
 * @note 不合理的设置会导致信号过饱和。
 * @param channel DAC通道编号。
 * @param offset DC值。范围：-128~127。
 */
static inline void dac_ll_cw_set_dc_offset(dac_channel_t channel, int8_t offset)
{
    if (channel == DAC_CHANNEL_1) {
        if (SENS.sar_dac_ctrl2.dac_inv1 == DAC_CW_PHASE_180) {
            offset = 0 - offset;
        }
        HAL_FORCE_MODIFY_U32_REG_FIELD(SENS.sar_dac_ctrl2, dac_dc1, offset ? offset : (-128 - offset));
    } else if (channel == DAC_CHANNEL_2) {
        if (SENS.sar_dac_ctrl2.dac_inv2 == DAC_CW_PHASE_180) {
            offset = 0 - offset;
        }
        HAL_FORCE_MODIFY_U32_REG_FIELD(SENS.sar_dac_ctrl2, dac_dc2, offset ? offset : (-128 - offset));
    }
}

/*---------------------------------------------------------------
                    数字控制器设置
---------------------------------------------------------------*/

/************************************/
/*           DAC DMA API*/
/************************************/

/**
 * 启用/禁用DAC数字控制器时钟信号的反相。
 *
 * @param enable 正确或错误。
 */
static inline void dac_ll_digi_clk_inv(bool enable)
{
    SENS.sar_dac_ctrl1.dac_clk_inv = enable;
}

/**
 * 启用/禁用DAC数字控制器的DAC-DMA模式。
 */
static inline void dac_ll_digi_enable_dma(bool enable)
{
    SENS.sar_dac_ctrl1.dac_dig_force = enable;
    APB_SARADC.apb_dac_ctrl.apb_dac_trans = enable;
}

/**
 * 设置数字控制器触发DAC输出的间隔时钟周期数。表达式：`dac_output_freq`=`controller_clk`/间隔。
 *
 * @note DAC数字控制器的时钟使用ADC数字控制器时钟分频器。
 *
 * @param cycle 触发器输出间隔的时钟周期数。单位是分频时钟。
 */
static inline void dac_ll_digi_set_trigger_interval(uint32_t cycle)
{
    APB_SARADC.apb_dac_ctrl.dac_timer_target = cycle;
}

/**
 * 启用/禁用DAC数字控制器以触发DAC输出。
 *
 * @param enable 正确或错误。
 */
static inline void dac_ll_digi_trigger_output(bool enable)
{
    APB_SARADC.apb_dac_ctrl.dac_timer_en = enable;
}

/**
 * 设置数字控制器的DAC转换模式。
 *
 * @param mode 转换模式选择。请参见``dac_digi_overt_mode_t``。
 */
static inline void dac_ll_digi_set_convert_mode(dac_digi_convert_mode_t mode)
{
    if (mode == DAC_CONV_NORMAL) {
        APB_SARADC.apb_dac_ctrl.apb_dac_alter_mode = 0;
    } else {
        APB_SARADC.apb_dac_ctrl.apb_dac_alter_mode = 1;
    }
}

/**
 * 重置DAC数字控制器的FIFO。
 */
static inline void dac_ll_digi_fifo_reset(void)
{
    APB_SARADC.apb_dac_ctrl.dac_reset_fifo = 1;
    APB_SARADC.apb_dac_ctrl.dac_reset_fifo = 0;
}

/**
 * 重置DAC数字控制器。
 */
static inline void dac_ll_digi_reset(void)
{
    APB_SARADC.apb_dac_ctrl.apb_dac_rst = 1;
    APB_SARADC.apb_dac_ctrl.apb_dac_rst = 0;
}

#ifdef __cplusplus
}
#endif

