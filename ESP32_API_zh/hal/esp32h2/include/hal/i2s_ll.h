/*
 * SPDX文件版权文本：2015-2021浓缩咖啡系统（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */

/*******************************************************************************
 * 注意：hal不是公共api，不要在应用程序代码中使用。请参阅自述文件。soc/include/hal/readme.md中的md
 ******************************************************************************/

// ESP32-H2 I2S寄存器操作的LL层

#pragma once
#include <stdbool.h>
#include "hal/misc.h"
#include "soc/i2s_periph.h"
#include "soc/i2s_struct.h"
#include "hal/i2s_types.h"

#ifdef __cplusplus
extern "C" {
#endif

#define I2S_LL_GET_HW(num)             (&I2S0)

#define I2S_LL_TDM_CH_MASK             (0xffff)
#define I2S_LL_PDM_BCK_FACTOR          (64)
#define I2S_LL_BASE_CLK                (2*APB_CLK_FREQ)

#define I2S_LL_MCLK_DIVIDER_BIT_WIDTH  (9)
#define I2S_LL_MCLK_DIVIDER_MAX        ((1 << I2S_LL_MCLK_DIVIDER_BIT_WIDTH) - 1)

/* I2S时钟配置结构*/
typedef struct {
    uint16_t mclk_div; // I2S模块时钟分频器，Fmclk=Fsclk/（mclk_div+b/a）
    uint16_t a;
    uint16_t b;        // 模块时钟偏差的小数部分，小数为：b/a
} i2s_ll_mclk_div_t;

/**
 * @brief I2S模块通用初始化，启用I2S时钟。
 *
 * @param hw 外围I2S硬件实例地址。
 */
static inline void i2s_ll_enable_clock(i2s_dev_t *hw)
{
    hw->tx_clkm_conf.clk_en = 1;
}

/**
 * @brief I2S模块禁用I2S时钟。
 *
 * @param hw 外围I2S硬件实例地址。
 */
static inline void i2s_ll_disable_clock(i2s_dev_t *hw)
{
    hw->tx_clkm_conf.clk_en = 0;
}

/**
 * @brief 启用I2S tx模块时钟
 *
 * @param hw 外围I2S硬件实例地址。
 */
static inline void i2s_ll_tx_enable_clock(i2s_dev_t *hw)
{
    hw->tx_clkm_conf.tx_clk_active = 1;
}

/**
 * @brief 启用I2S rx模块时钟
 *
 * @param hw 外围I2S硬件实例地址。
 */
static inline void i2s_ll_rx_enable_clock(i2s_dev_t *hw)
{
    hw->rx_clkm_conf.rx_clk_active = 1;
}

/**
 * @brief 禁用I2S tx模块时钟
 *
 * @param hw 外围I2S硬件实例地址。
 */
static inline void i2s_ll_tx_disable_clock(i2s_dev_t *hw)
{
    hw->tx_clkm_conf.tx_clk_active = 0;
}

/**
 * @brief 禁用I2S rx模块时钟
 *
 * @param hw 外围I2S硬件实例地址。
 */
static inline void i2s_ll_rx_disable_clock(i2s_dev_t *hw)
{
    hw->rx_clkm_conf.rx_clk_active = 0;
}

/**
 * @brief I2S mclk使用tx模块时钟
 *
 * @param hw 外围I2S硬件实例地址。
 */
static inline void i2s_ll_mclk_use_tx_clk(i2s_dev_t *hw)
{
    hw->rx_clkm_conf.mclk_sel = 0;
}

/**
 * @brief I2S mclk使用rx模块时钟
 *
 * @param hw 外围I2S硬件实例地址。
 */
static inline void i2s_ll_mclk_use_rx_clk(i2s_dev_t *hw)
{
    hw->rx_clkm_conf.mclk_sel = 1;
}

/**
 * @brief 启用I2S TX从属模式
 *
 * @param hw 外围I2S硬件实例地址。
 * @param slave_en 设置为true以启用从属模式
 */
static inline void i2s_ll_tx_set_slave_mod(i2s_dev_t *hw, bool slave_en)
{
    hw->tx_conf.tx_slave_mod = slave_en;
}

/**
 * @brief 启用I2S RX从属模式
 *
 * @param hw 外围I2S硬件实例地址。
 * @param slave_en 设置为true以启用从属模式
 */
static inline void i2s_ll_rx_set_slave_mod(i2s_dev_t *hw, bool slave_en)
{
    hw->rx_conf.rx_slave_mod = slave_en;
}

/**
 * @brief 重置I2S TX模块
 *
 * @param hw 外围I2S硬件实例地址。
 */
static inline void i2s_ll_tx_reset(i2s_dev_t *hw)
{
    hw->tx_conf.tx_reset = 1;
    hw->tx_conf.tx_reset = 0;
}

/**
 * @brief 重置I2S RX模块
 *
 * @param hw 外围I2S硬件实例地址。
 */
static inline void i2s_ll_rx_reset(i2s_dev_t *hw)
{
    hw->rx_conf.rx_reset = 1;
    hw->rx_conf.rx_reset = 0;
}

/**
 * @brief 重置I2S TX FIFO
 *
 * @param hw 外围I2S硬件实例地址。
 */
static inline void i2s_ll_tx_reset_fifo(i2s_dev_t *hw)
{
    hw->tx_conf.tx_fifo_reset = 1;
    hw->tx_conf.tx_fifo_reset = 0;
}

/**
 * @brief 重置I2S RX FIFO
 *
 * @param hw 外围I2S硬件实例地址。
 */
static inline void i2s_ll_rx_reset_fifo(i2s_dev_t *hw)
{
    hw->rx_conf.rx_fifo_reset = 1;
    hw->rx_conf.rx_fifo_reset = 0;
}

/**
 * @brief 设置TX源时钟
 *
 * @param hw 外围I2S硬件实例地址。
 * @param src I2S源时钟。
 */
static inline void i2s_ll_tx_clk_set_src(i2s_dev_t *hw, i2s_clock_src_t src)
{
    hw->tx_clkm_conf.tx_clk_sel = 2;
}

/**
 * @brief 设置RX源时钟
 *
 * @param hw 外围I2S硬件实例地址。
 * @param src I2S源时钟，ESP32-H2仅支持`I2S_CLK_D2CLK`
 */
static inline void i2s_ll_rx_clk_set_src(i2s_dev_t *hw, i2s_clock_src_t src)
{
    hw->rx_clkm_conf.rx_clk_sel = 2;
}

/**
 * @brief 设置I2S tx bck div num
 *
 * @param hw 外围I2S硬件实例地址。
 * @param val 设置tx-bck div num的值
 */
static inline void i2s_ll_tx_set_bck_div_num(i2s_dev_t *hw, uint32_t val)
{
    hw->tx_conf1.tx_bck_div_num = val - 1;
}

/**
 * @brief 配置I2S TX时钟分配器
 *
 * @param hw 外围I2S硬件实例地址。
 * @param set 指向I2S时钟分配器配置参数的指针
 */
static inline void i2s_ll_tx_set_clk(i2s_dev_t *hw, i2s_ll_mclk_div_t *set)
{
    if (set->a == 0 || set->b == 0) {
        hw->tx_clkm_div_conf.tx_clkm_div_x = 0;
        hw->tx_clkm_div_conf.tx_clkm_div_y = 0;
        hw->tx_clkm_div_conf.tx_clkm_div_z = 0;
    } else {
        if (set->b > set->a / 2) {
            hw->tx_clkm_div_conf.tx_clkm_div_x = set->a / (set->a - set->b) - 1;
            hw->tx_clkm_div_conf.tx_clkm_div_y = set->a % (set->a - set->b);
            hw->tx_clkm_div_conf.tx_clkm_div_z = set->a - set->b;
            hw->tx_clkm_div_conf.tx_clkm_div_yn1 = 1;
        } else {
            hw->tx_clkm_div_conf.tx_clkm_div_x = set->a / set->b - 1;
            hw->tx_clkm_div_conf.tx_clkm_div_y = set->a % set->b + 1;
            hw->tx_clkm_div_conf.tx_clkm_div_z = set->b;
            hw->tx_clkm_div_conf.tx_clkm_div_yn1 = 0;
        }
    }
    HAL_FORCE_MODIFY_U32_REG_FIELD(hw->tx_clkm_conf, tx_clkm_div_num, set->mclk_div);
}

/**
 * @brief 设置I2S rx bck div num
 *
 * @param hw 外围I2S硬件实例地址。
 * @param val 设置rx-bck div num的值
 */
static inline void i2s_ll_rx_set_bck_div_num(i2s_dev_t *hw, uint32_t val)
{
    hw->rx_conf1.rx_bck_div_num = val - 1;
}

/**
 * @brief 配置I2S RX时钟分配器
 *
 * @param hw 外围I2S硬件实例地址。
 * @param set 指向I2S时钟分配器配置参数的指针
 */
static inline void i2s_ll_rx_set_clk(i2s_dev_t *hw, i2s_ll_mclk_div_t *set)
{
    if (set->a == 0 || set->b == 0) {
        hw->rx_clkm_div_conf.rx_clkm_div_x = 0;
        hw->rx_clkm_div_conf.rx_clkm_div_y = 0;
        hw->rx_clkm_div_conf.rx_clkm_div_z = 0;
    } else {
        if (set->b > set->a / 2) {
            hw->rx_clkm_div_conf.rx_clkm_div_x = set->a / (set->a - set->b) - 1;
            hw->rx_clkm_div_conf.rx_clkm_div_y = set->a % (set->a - set->b);
            hw->rx_clkm_div_conf.rx_clkm_div_z = set->a - set->b;
            hw->rx_clkm_div_conf.rx_clkm_div_yn1 = 1;
        } else {
            hw->rx_clkm_div_conf.rx_clkm_div_x = set->a / set->b - 1;
            hw->rx_clkm_div_conf.rx_clkm_div_y = set->a % set->b + 1;
            hw->rx_clkm_div_conf.rx_clkm_div_z = set->b;
            hw->rx_clkm_div_conf.rx_clkm_div_yn1 = 0;
        }
    }
    HAL_FORCE_MODIFY_U32_REG_FIELD(hw->rx_clkm_conf, rx_clkm_div_num, set->mclk_div);
}

/**
 * @brief 启动I2S TX
 *
 * @param hw 外围I2S硬件实例地址。
 */
static inline void i2s_ll_tx_start(i2s_dev_t *hw)
{
    hw->tx_conf.tx_update = 0;
    hw->tx_conf.tx_update = 1;
    hw->tx_conf.tx_start = 1;
}

/**
 * @brief 启动I2S RX
 *
 * @param hw 外围I2S硬件实例地址。
 */
static inline void i2s_ll_rx_start(i2s_dev_t *hw)
{
    hw->rx_conf.rx_update = 0;
    hw->rx_conf.rx_update = 1;
    hw->rx_conf.rx_start = 1;
}

/**
 * @brief 停止I2S TX
 *
 * @param hw 外围I2S硬件实例地址。
 */
static inline void i2s_ll_tx_stop(i2s_dev_t *hw)
{
    hw->tx_conf.tx_start = 0;
}

/**
 * @brief 停止I2S RX
 *
 * @param hw 外围I2S硬件实例地址。
 */
static inline void i2s_ll_rx_stop(i2s_dev_t *hw)
{
    hw->rx_conf.rx_start = 0;
}

/**
 * @brief 配置TX WS信号宽度
 *
 * @param hw 外围I2S硬件实例地址。
 * @param width BCK循环中的WS宽度
 */
static inline void i2s_ll_tx_set_ws_width(i2s_dev_t *hw, int width)
{
    hw->tx_conf1.tx_tdm_ws_width = width - 1;
}

/**
 * @brief 配置RX WS信号宽度
 *
 * @param hw 外围I2S硬件实例地址。
 * @param width BCK循环中的WS宽度
 */
static inline void i2s_ll_rx_set_ws_width(i2s_dev_t *hw, int width)
{
    hw->rx_conf1.rx_tdm_ws_width = width - 1;
}

/**
 * @brief 配置接收长度以触发in_suc_eof中断
 *
 * @param hw 外围I2S硬件实例地址。
 * @param eof_num 要触发in_suc_eof中断的字节长度
 */
static inline void i2s_ll_rx_set_eof_num(i2s_dev_t *hw, int eof_num)
{
    hw->rx_eof_num.rx_eof_num = eof_num;
}

/**
 * @brief 配置TX通道位和音频数据位
 *
 * @param hw 外围I2S硬件实例地址。
 * @param chan_bit chan位宽度
 * @param data_bit 音频数据位宽
 */
static inline void i2s_ll_tx_set_sample_bit(i2s_dev_t *hw, uint8_t chan_bit, int data_bit)
{
    hw->tx_conf1.tx_bits_mod = data_bit - 1;
    hw->tx_conf1.tx_tdm_chan_bits = chan_bit - 1;
}

/**
 * @brief 配置RX通道位和音频数据位
 *
 * @param hw 外围I2S硬件实例地址。
 * @param chan_bit chan位宽度
 * @param data_bit 音频数据位宽
 */
static inline void i2s_ll_rx_set_sample_bit(i2s_dev_t *hw, uint8_t chan_bit, int data_bit)
{
    hw->rx_conf1.rx_bits_mod = data_bit - 1;
    hw->rx_conf1.rx_tdm_chan_bits = chan_bit - 1;
}

/**
 * @brief 配置RX half_sample_bit
 *
 * @param hw 外围I2S硬件实例地址。
 * @param half_sample_bits 半采样位宽
 */
static inline void i2s_ll_tx_set_half_sample_bit(i2s_dev_t *hw, int half_sample_bits)
{
    hw->tx_conf1.tx_half_sample_bits = half_sample_bits - 1;
}

/**
 * @brief 配置RX half_sample_bit
 *
 * @param hw 外围I2S硬件实例地址。
 * @param half_sample_bits 半采样位宽
 */
static inline void i2s_ll_rx_set_half_sample_bit(i2s_dev_t *hw, int half_sample_bits)
{
    hw->rx_conf1.rx_half_sample_bits = half_sample_bits - 1;
}

/**
 * @brief 启用TX MSB移位，数据将在第一个BCK时钟启动
 *
 * @param hw 外围I2S硬件实例地址。
 * @param msb_shift_enable 设置为true以启用MSB移位
 */
static inline void i2s_ll_tx_enable_msb_shift(i2s_dev_t *hw, bool msb_shift_enable)
{
    hw->tx_conf1.tx_msb_shift = msb_shift_enable;
}

/**
 * @brief 启用RX MSB移位，数据将在第一个BCK时钟启动
 *
 * @param hw 外围I2S硬件实例地址。
 * @param msb_shift_enable 设置为true以启用MSB移位
 */
static inline void i2s_ll_rx_enable_msb_shift(i2s_dev_t *hw, bool msb_shift_enable)
{
    hw->rx_conf1.rx_msb_shift = msb_shift_enable;
}

/**
 * @brief 配置TX总通道数
 *
 * @param hw 外围I2S硬件实例地址。
 * @param total_num 总通道数
 */
static inline void i2s_ll_tx_set_chan_num(i2s_dev_t *hw, int total_num)
{
    hw->tx_tdm_ctrl.tx_tdm_tot_chan_num = total_num - 1;
}

/**
 * @brief 配置RX总通道数
 *
 * @param hw 外围I2S硬件实例地址。
 * @param total_num 总通道数
 */
static inline void i2s_ll_rx_set_chan_num(i2s_dev_t *hw, int total_num)
{
    hw->rx_tdm_ctrl.rx_tdm_tot_chan_num = total_num - 1;
}

/**
 * @brief 设置活动TX通道的双映射，只有活动通道才能启动音频数据。
 *
 * @param hw 外围I2S硬件实例地址。
 * @param chan_mask tx活动通道的掩码
 */
static inline void i2s_ll_tx_set_active_chan_mask(i2s_dev_t *hw, uint32_t chan_mask)
{
    typeof(hw->tx_tdm_ctrl) tdm_ctrl_reg = hw->tx_tdm_ctrl;
    tdm_ctrl_reg.val &= ~I2S_LL_TDM_CH_MASK;
    tdm_ctrl_reg.val |= chan_mask & I2S_LL_TDM_CH_MASK;
    hw->tx_tdm_ctrl.val = tdm_ctrl_reg.val;
}

/**
 * @brief 设置活动RX通道的双映射，只有活动通道才能接收音频数据。
 *
 * @param hw 外围I2S硬件实例地址。
 * @param chan_mask rx活动通道的掩码
 */
static inline void i2s_ll_rx_set_active_chan_mask(i2s_dev_t *hw, uint32_t chan_mask)
{
    typeof(hw->rx_tdm_ctrl) tdm_ctrl_reg = hw->rx_tdm_ctrl;
    tdm_ctrl_reg.val &= ~I2S_LL_TDM_CH_MASK;
    tdm_ctrl_reg.val |= chan_mask & I2S_LL_TDM_CH_MASK;
    hw->rx_tdm_ctrl.val = tdm_ctrl_reg.val;
}

/**
 * @brief 设置TX WS信号pol电平
 *
 * @param hw 外围I2S硬件实例地址。
 * @param ws_pol_level 接收左通道数据时WS（输出）的引脚电平
 */
static inline void i2s_ll_tx_set_ws_idle_pol(i2s_dev_t *hw, bool ws_pol_level)
{
    hw->tx_conf.tx_ws_idle_pol = ws_pol_level;
}

/**
 * @brief 设置RX WS信号pol电平
 *
 * @param hw 外围I2S硬件实例地址。
 * @param ws_pol_level 接收左通道数据时WS（输入）的引脚电平
 */
static inline void i2s_ll_rx_set_ws_idle_pol(i2s_dev_t *hw, bool ws_pol_level)
{
    hw->rx_conf.rx_ws_idle_pol = ws_pol_level;
}

/**
 * @brief 启用TX PDM模式。
 *
 * @param hw 外围I2S硬件实例地址。
 * @param pdm_enable 设置为真以启用发送PDM模式
 */
static inline void i2s_ll_tx_enable_pdm(i2s_dev_t *hw, bool pdm_enable)
{
    hw->tx_conf.tx_pdm_en = pdm_enable;
    hw->tx_conf.tx_tdm_en = !pdm_enable;
    hw->tx_pcm2pdm_conf.pcm2pdm_conv_en = pdm_enable;
}

/**
 * @brief 设置I2S TX PDM预缩放
 *
 * @param hw 外围I2S硬件实例地址。
 * @param prescale I2S TX PDM预缩放
 */
static inline void i2s_ll_tx_set_pdm_prescale(i2s_dev_t *hw, bool prescale)
{
    HAL_FORCE_MODIFY_U32_REG_FIELD(hw->tx_pcm2pdm_conf, tx_pdm_prescale, prescale);
}

/**
 * @brief 设置I2S TX PDM高通滤波器缩放
 *
 * @param hw 外围I2S硬件实例地址。
 * @param sig_scale 发送至滤波器之前的I2S TX PDM信号缩放
 */
static inline void i2s_ll_tx_set_pdm_hp_scale(i2s_dev_t *hw, i2s_pdm_sig_scale_t sig_scale)
{
    hw->tx_pcm2pdm_conf.tx_pdm_hp_in_shift = sig_scale;
}

/**
 * @brief 设置I2S TX PDM低通滤波器缩放
 *
 * @param hw 外围I2S硬件实例地址。
 * @param sig_scale 发送至滤波器之前的I2S TX PDM信号缩放
 */
static inline void i2s_ll_tx_set_pdm_lp_scale(i2s_dev_t *hw, i2s_pdm_sig_scale_t sig_scale)
{
    hw->tx_pcm2pdm_conf.tx_pdm_lp_in_shift = sig_scale;
}

/**
 * @brief 设置I2S TX PDM sinc滤波器缩放
 *
 * @param hw 外围I2S硬件实例地址。
 * @param sig_scale 发送至滤波器之前的I2S TX PDM信号缩放
 */
static inline void i2s_ll_tx_set_pdm_sinc_scale(i2s_dev_t *hw, i2s_pdm_sig_scale_t sig_scale)
{
    hw->tx_pcm2pdm_conf.tx_pdm_sinc_in_shift = sig_scale;
}

/**
 * @brief 设置I2S TX PDM sigma delta滤波器缩放
 *
 * @param hw 外围I2S硬件实例地址。
 * @param sig_scale 发送至滤波器之前的I2S TX PDM信号缩放
 */
static inline void i2s_ll_tx_set_pdm_sd_scale(i2s_dev_t *hw, i2s_pdm_sig_scale_t sig_scale)
{
    hw->tx_pcm2pdm_conf.tx_pdm_sigmadelta_in_shift = sig_scale;
}

/**
 * @brief 设置I2S TX PDM高通滤波器参数0
 *
 * @param hw 外围I2S硬件实例地址。
 * @param param PDM TX IIR_HP滤波器1级的第四个参数为（504+I2S_TX_IIR_HP_MULT12_0[2:0]）
 */
static inline void i2s_ll_tx_set_pdm_hp_filter_param0(i2s_dev_t *hw, uint32_t param)
{
    hw->tx_pcm2pdm_conf1.tx_iir_hp_mult12_0 = param;
}

/**
 * @brief 设置I2S TX PDM高通滤波器参数5
 *
 * @param hw 外围I2S硬件实例地址。
 * @param param PDM TX IIR_HP滤波器2级的第四个参数为（504+I2S_TX_IIR_HP_MULT125[2:0]）
 */
static inline void i2s_ll_tx_set_pdm_hp_filter_param5(i2s_dev_t *hw, uint32_t param)
{
    hw->tx_pcm2pdm_conf1.tx_iir_hp_mult12_5 = param;
}

/**
 * @brief 启用I2S TX PDM高通滤波器
 *
 * @param hw 外围I2S硬件实例地址。
 * @param enable 设置为true以启用I2S TX PDM高通滤波器，设置为false以绕过它
 */
static inline void i2s_ll_tx_enable_pdm_hp_filter(i2s_dev_t *hw, bool enable)
{
    hw->tx_pcm2pdm_conf.tx_pdm_hp_bypass = !enable;
}

/**
 * @brief 启用I2S TX PDM sigma delta编解码器
 *
 * @param hw 外围I2S硬件实例地址。
 * @param dither I2S TX PDM sigmadelta抖动值
 */
static inline void i2s_ll_tx_enable_pdm_sd_codec(i2s_dev_t *hw, bool enable)
{
    hw->tx_pcm2pdm_conf.tx_pdm_dac_2out_en = enable;
    hw->tx_pcm2pdm_conf.tx_pdm_dac_mode_en = enable;
}

/**
 * @brief 设置I2S TX PDM sigma delta编解码器抖动
 *
 * @param hw 外围I2S硬件实例地址。
 * @param dither I2S TX PDM sigmadelta抖动值
 */
static inline void i2s_ll_tx_set_pdm_sd_dither(i2s_dev_t *hw, uint32_t dither)
{
    hw->tx_pcm2pdm_conf.tx_pdm_sigmadelta_dither = dither;
}

/**
 * @brief 设置I2S TX PDM sigma delta编解码器抖动
 *
 * @param hw 外围I2S硬件实例地址。
 * @param dither2 I2S TX PDM sigmadelta抖动2值
 */
static inline void i2s_ll_tx_set_pdm_sd_dither2(i2s_dev_t *hw, uint32_t dither2)
{
    hw->tx_pcm2pdm_conf.tx_pdm_sigmadelta_dither2 = dither2;
}

/**
 * @brief 配置I2S TX PDM采样率Fpdm=64Fpcmfp/fs
 *
 * @param hw 外围I2S硬件实例地址。
 * @param fp TX PDM过滤器模块组0的fp值。
 * @param fs TX PDM过滤器模块组0的fs值。
 */
static inline void i2s_ll_tx_set_pdm_fpfs(i2s_dev_t *hw, uint32_t fp, uint32_t fs)
{
    hw->tx_pcm2pdm_conf1.tx_pdm_fp = fp;
    hw->tx_pcm2pdm_conf1.tx_pdm_fs = fs;
    hw->tx_pcm2pdm_conf.tx_pdm_sinc_osr2 = fp / fs;
}

/**
 * @brief 获取I2S TX PDM fp配置参数
 *
 * @param hw 外围I2S硬件实例地址。
 * @return
 *        -fp配置参数
 */
static inline uint32_t i2s_ll_tx_get_pdm_fp(i2s_dev_t *hw)
{
    return hw->tx_pcm2pdm_conf1.tx_pdm_fp;
}

/**
 * @brief 获取I2S TX PDM fs配置参数
 *
 * @param hw 外围I2S硬件实例地址。
 * @return
 *        -fs配置参数
 */
static inline uint32_t i2s_ll_tx_get_pdm_fs(i2s_dev_t *hw)
{
    return hw->tx_pcm2pdm_conf1.tx_pdm_fs;
}

/**
 * @brief 启用RX PDM模式。
 *
 * @param hw 外围I2S硬件实例地址。
 * @param pdm_enable 设置为RX启用PDM模式
 */
static inline void i2s_ll_rx_enable_pdm(i2s_dev_t *hw, bool pdm_enable)
{
    hw->rx_conf.rx_pdm_en = pdm_enable;
    hw->rx_conf.rx_tdm_en = !pdm_enable;
}

/**
 * @brief 配置TX a/u-law解压缩或压缩
 *
 * @param hw 外围I2S硬件实例地址。
 * @param pcm_cfg PCM组态参数
 */
static inline void i2s_ll_tx_set_pcm_type(i2s_dev_t *hw, i2s_pcm_compress_t pcm_cfg)
{
    hw->tx_conf.tx_pcm_conf = pcm_cfg;
    hw->tx_conf.tx_pcm_bypass = !pcm_cfg;
}

/**
 * @brief 配置RX a/u-law解压缩或压缩
 *
 * @param hw 外围I2S硬件实例地址。
 * @param pcm_cfg PCM组态参数
 */
static inline void i2s_ll_rx_set_pcm_type(i2s_dev_t *hw, i2s_pcm_compress_t pcm_cfg)
{
    hw->rx_conf.rx_pcm_conf = pcm_cfg;
    hw->rx_conf.rx_pcm_bypass = !pcm_cfg;
}

/**
 * @brief 启用TX音频数据左对齐
 *
 * @param hw 外围I2S硬件实例地址。
 * @param ena 设置为true以启用左对齐
 */
static inline void i2s_ll_tx_enable_left_align(i2s_dev_t *hw, bool ena)
{
    hw->tx_conf.tx_left_align = ena;
}

/**
 * @brief 启用RX音频数据左对齐
 *
 * @param hw 外围I2S硬件实例地址。
 * @param ena 设置为true以启用左对齐
 */
static inline void i2s_ll_rx_enable_left_align(i2s_dev_t *hw, bool ena)
{
    hw->rx_conf.rx_left_align = ena;
}

/**
 * @brief 启用TX大端模式
 *
 * @param hw 外围I2S硬件实例地址。
 * @param ena 设置为true以启用big endian模式
 */
static inline void i2s_ll_rx_enable_big_endian(i2s_dev_t *hw, bool ena)
{
    hw->rx_conf.rx_big_endian = ena;
}

/**
 * @brief 启用RX大端模式
 *
 * @param hw 外围I2S硬件实例地址。
 * @param ena 设置为true以启用big endian模式
 */
static inline void i2s_ll_tx_enable_big_endian(i2s_dev_t *hw, bool ena)
{
    hw->tx_conf.tx_big_endian = ena;
}

/**
 * @brief 配置TX位顺序
 *
 * @param hw 外围I2S硬件实例地址。
 * @param lsb_order_ena 设置为true以启用LSB位顺序
 */
static inline void i2s_ll_tx_set_bit_order(i2s_dev_t *hw, bool lsb_order_ena)
{
    hw->tx_conf.tx_bit_order = lsb_order_ena;
}

/**
 * @brief 配置RX位顺序
 *
 * @param hw 外围I2S硬件实例地址。
 * @param lsb_order_ena 设置为true以启用LSB位顺序
 */
static inline void i2s_ll_rx_set_bit_order(i2s_dev_t *hw, bool lsb_order_ena)
{
    hw->rx_conf.rx_bit_order = lsb_order_ena;
}

/**
 * @brief 配置TX跳过掩码启用
 *
 * @param hw 外围I2S硬件实例地址。
 * @param skip_mask_ena 设置为true可跳过非活动通道。
 */
static inline void i2s_ll_tx_set_skip_mask(i2s_dev_t *hw, bool skip_mask_ena)
{
    hw->tx_tdm_ctrl.tx_tdm_skip_msk_en = skip_mask_ena;
}


/**
 * @brief 配置单个数据
 *
 * @param hw 外围I2S硬件实例地址。
 * @param data 要设置的单个数据
 */
static inline void i2s_ll_set_single_data(i2s_dev_t *hw, uint32_t data)
{
    hw->conf_single_data = data;
}

/**
 * @brief 启用环回模式
 *
 * @param hw 外围I2S硬件实例地址。
 * @param ena 设置为true以共享tx模块和rx模块的BCK和WS信号。
 */
static inline void i2s_ll_share_bck_ws(i2s_dev_t *hw, bool ena)
{
    hw->tx_conf.sig_loopback = ena;
}

/**
 * @brief 设置I2S pdm2pcm对流
 *
 * @param hw 外围I2S硬件实例地址。
 * @param val 设置pdm2pcm conv en的值
 */
static inline void i2s_ll_set_pdm2pcm_conv_en(i2s_dev_t *hw, bool val)
{
    abort(); // TODO ESP32-H2 IDF-2098

}

/**
 * @brief 启用TX单声道模式
 * @note 硬件中的MONO表示只有一个通道获得数据，但另一个通道没有。软件中的MON表示两个通道共享相同的数据。该功能旨在在软件中使用MONO，因此应同时启用“tx_MONO”和“tx_chan_equal”
 *
 * @param hw 外围I2S硬件实例地址。
 * @param mono_ena 设置为true以启用mono-mde。
 */
static inline void i2s_ll_tx_enable_mono_mode(i2s_dev_t *hw, bool mono_ena)
{
    hw->tx_conf.tx_mono = mono_ena;
    hw->tx_conf.tx_chan_equal = mono_ena;
}

/**
 * @brief 启用RX单声道模式
 *
 * @param hw 外围I2S硬件实例地址。
 * @param mono_ena 设置为true以启用mono-mde。
 */
static inline void i2s_ll_rx_enable_mono_mode(i2s_dev_t *hw, bool mono_ena)
{
    hw->rx_conf.rx_mono = mono_ena;
    hw->rx_conf.rx_mono_fst_vld = mono_ena;
}

#ifdef __cplusplus
}
#endif

