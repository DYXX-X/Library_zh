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

/*******************************************************************************
 * 注意：hal不是公共api，不要在应用程序代码中使用。请参阅自述文件。在hal/include/hal/readme.md中的md
 ******************************************************************************/

// ESP32 I2S寄存器操作的LL层

#pragma once

#include <stdbool.h>
#include "hal/misc.h"
#include "soc/i2s_periph.h"
#include "soc/i2s_struct.h"
#include "hal/i2s_types.h"

#ifdef __cplusplus
extern "C" {
#endif

// 获取I2S硬件实例，并提供I2S num
#define I2S_LL_GET_HW(num) (((num) == 0) ? (&I2S0) : (((num) == 1) ? (&I2S1) : NULL))

#define I2S_LL_AD_BCK_FACTOR           (2)
#define I2S_LL_PDM_BCK_FACTOR          (64)
#define I2S_LL_BASE_CLK                (2 * APB_CLK_FREQ)

#define I2S_LL_MCLK_DIVIDER_BIT_WIDTH  (6)
#define I2S_LL_MCLK_DIVIDER_MAX        ((1 << I2S_LL_MCLK_DIVIDER_BIT_WIDTH) - 1)

#define I2S_LL_EVENT_TX_EOF       (1 << 12)
#define I2S_LL_BCK_MAX_PRESCALE   (64)

/* I2S时钟配置结构*/
typedef struct {
    uint16_t mclk_div; // I2S模块时钟分频器，Fmclk=Fsclk/（mclk_div+b/a）
    uint16_t a;
    uint16_t b;        // 模块时钟偏差的小数部分，小数为：b/a
} i2s_ll_mclk_div_t;

/**
 * @brief 启用DMA描述符所有者检查
 *
 * @param hw 外围I2S硬件实例地址。
 * @param en 是否启用所有者检查
 */
static inline void i2s_ll_dma_enable_owner_check(i2s_dev_t *hw, bool en)
{
    hw->lc_conf.check_owner = en;
}

/**
 * @brief 启用DMA描述符回写
 *
 * @param hw 外围I2S硬件实例地址。
 * @param en 是否启用回写
 */
static inline void i2s_ll_dma_enable_auto_write_back(i2s_dev_t *hw, bool en)
{
    hw->lc_conf.out_auto_wrback = en;
}

/**
 * @brief I2S DMA在弹出的FIFO数据上生成EOF事件
 *
 * @param hw 外围I2S硬件实例地址。
 * @param en True表示启用，False表示禁用
 */
static inline void i2s_ll_dma_enable_eof_on_fifo_empty(i2s_dev_t *hw, bool en)
{
    hw->lc_conf.out_eof_mode = en;
}

/**
 * @brief I2S模块通用初始化，启用I2S时钟。
 *
 * @param hw 外围I2S硬件实例地址。
 */
static inline void i2s_ll_enable_clock(i2s_dev_t *hw)
{
    if (hw->clkm_conf.clk_en == 0) {
        hw->clkm_conf.clk_en = 1;
        hw->conf2.val = 0;
    }
}

/**
 * @brief I2S模块禁用时钟。
 *
 * @param hw 外围I2S硬件实例地址。
 */
static inline void i2s_ll_disable_clock(i2s_dev_t *hw)
{
    if (hw->clkm_conf.clk_en == 1) {
        hw->clkm_conf.clk_en = 0;
    }
}

/**
 * @brief I2S tx msb右启用
 *
 * @param hw 外围I2S硬件实例地址。
 * @param enable 设置为true以启用tx-msb权限
 */
static inline void i2s_ll_tx_enable_msb_right(i2s_dev_t *hw, bool enable)
{
    hw->conf.tx_msb_right = enable;
}

/**
 * @brief I2S rx msb右启用
 *
 * @param hw 外围I2S硬件实例地址。
 * @param enable 设置为true以启用rx-msb权限
 */
static inline void i2s_ll_rx_enable_msb_right(i2s_dev_t *hw, bool enable)
{
    hw->conf.rx_msb_right = enable;
}

/**
 * @brief I2S tx右通道优先
 *
 * @param hw 外围I2S硬件实例地址。
 * @param enable 设置为true以首先启用发送右通道
 */
static inline void i2s_ll_tx_enable_right_first(i2s_dev_t *hw, bool enable)
{
    hw->conf.tx_right_first = enable;
}

/**
 * @brief I2S rx右通道优先
 *
 * @param hw 外围I2S硬件实例地址。
 * @param enable 设置为true以首先启用接收右通道
 */
static inline void i2s_ll_rx_enable_right_first(i2s_dev_t *hw, bool enable)
{
    hw->conf.rx_right_first = enable;
}

/**
 * @brief I2S tx fifo模块强制启用
 *
 * @param hw 外围I2S硬件实例地址。
 * @param enable 设置为true以启用tx fifo模块
 */
static inline void i2s_ll_tx_force_enable_fifo_mod(i2s_dev_t *hw, bool enable)
{
    hw->fifo_conf.tx_fifo_mod_force_en = enable;
}

/**
 * @brief I2S rx fifo模块强制启用
 *
 * @param hw 外围I2S硬件实例地址。
 * @param enable 设置为true以启用rx fifo模块
 */
static inline void i2s_ll_rx_force_enable_fifo_mod(i2s_dev_t *hw, bool enable)
{
    hw->fifo_conf.rx_fifo_mod_force_en = enable;
}
/**
 * @brief 启用I2S TX从属模式
 *
 * @param hw 外围I2S硬件实例地址。
 * @param slave_en 设置为true以启用从属模式
 */
static inline void i2s_ll_tx_set_slave_mod(i2s_dev_t *hw, bool slave_en)
{
    hw->conf.tx_slave_mod = slave_en;
}

/**
 * @brief 启用I2S RX从属模式
 *
 * @param hw 外围I2S硬件实例地址。
 * @param slave_en 设置为true以启用从属模式
 */
static inline void i2s_ll_rx_set_slave_mod(i2s_dev_t *hw, bool slave_en)
{
    hw->conf.rx_slave_mod = slave_en;
}

/**
 * @brief 重置I2S TX模块
 *
 * @param hw 外围I2S硬件实例地址。
 */
static inline void i2s_ll_tx_reset(i2s_dev_t *hw)
{
    hw->conf.tx_reset = 1;
    hw->conf.tx_reset = 0;
}

/**
 * @brief 重置I2S RX模块
 *
 * @param hw 外围I2S硬件实例地址。
 */
static inline void i2s_ll_rx_reset(i2s_dev_t *hw)
{
    hw->conf.rx_reset = 1;
    hw->conf.rx_reset = 0;
}

/**
 * @brief 重置I2S TX FIFO
 *
 * @param hw 外围I2S硬件实例地址。
 */
static inline void i2s_ll_tx_reset_fifo(i2s_dev_t *hw)
{
    hw->conf.tx_fifo_reset = 1;
    hw->conf.tx_fifo_reset = 0;
}

/**
 * @brief 重置I2S RX FIFO
 *
 * @param hw 外围I2S硬件实例地址。
 */
static inline void i2s_ll_rx_reset_fifo(i2s_dev_t *hw)
{
    hw->conf.rx_fifo_reset = 1;
    hw->conf.rx_fifo_reset = 0;
}

/**
 * @brief 设置TX源时钟
 *
 * @param hw 外围I2S硬件实例地址。
 * @param src I2S源时钟
 */
static inline void i2s_ll_tx_clk_set_src(i2s_dev_t *hw, i2s_clock_src_t src)
{
    //0：禁用APLL时钟，I2S模块将使用PLL_D2_CLK（160M）作为源时钟
    //1： 启用APLL时钟，I2S模块将使用APLL作为源时钟
    hw->clkm_conf.clka_en = (src == I2S_CLK_APLL) ? 1 : 0;
}

/**
 * @brief 设置RX源时钟
 *
 * @param hw 外围I2S硬件实例地址。
 * @param src I2S源时钟
 */
static inline void i2s_ll_rx_clk_set_src(i2s_dev_t *hw, i2s_clock_src_t src)
{
    //0：禁用APLL时钟，I2S模块将使用PLL_D2_CLK（160M）作为源时钟
    //1： 启用APLL时钟，I2S模块将使用APLL作为源时钟
    hw->clkm_conf.clka_en = (src == I2S_CLK_APLL) ? 1 : 0;
}

/**
 * @brief 设置I2S tx bck div num
 *
 * @param hw 外围I2S硬件实例地址。
 * @param val 设置tx-bck div num的值
 */
static inline void i2s_ll_tx_set_bck_div_num(i2s_dev_t *hw, uint32_t val)
{
    hw->sample_rate_conf.tx_bck_div_num = val;
}

/**
 * @brief 配置I2S TX时钟分配器
 *
 * @param hw 外围I2S硬件实例地址。
 * @param set 指向I2S时钟分配器配置参数的指针
 */
static inline void i2s_ll_tx_set_clk(i2s_dev_t *hw, i2s_ll_mclk_div_t *set)
{
    HAL_FORCE_MODIFY_U32_REG_FIELD(hw->clkm_conf, clkm_div_num, set->mclk_div);
    hw->clkm_conf.clkm_div_b = set->b;
    hw->clkm_conf.clkm_div_a = set->a;
}

/**
 * @brief 设置I2S rx bck div num
 *
 * @param hw 外围I2S硬件实例地址。
 * @param val 设置rx-bck div num的值
 */
static inline void i2s_ll_rx_set_bck_div_num(i2s_dev_t *hw, uint32_t val)
{
    hw->sample_rate_conf.rx_bck_div_num = val;
}

/**
 * @brief 配置I2S RX时钟分配器
 *
 * @param hw 外围I2S硬件实例地址。
 * @param set 指向I2S时钟分配器配置参数的指针
 */
static inline void i2s_ll_rx_set_clk(i2s_dev_t *hw, i2s_ll_mclk_div_t *set)
{
    HAL_FORCE_MODIFY_U32_REG_FIELD(hw->clkm_conf, clkm_div_num, set->mclk_div);
    hw->clkm_conf.clkm_div_b = set->b;
    hw->clkm_conf.clkm_div_a = set->a;
}

/**
 * @brief 通过掩码启用中断
 *
 * @param hw 外围I2S硬件实例地址。
 * @param mask 中断事件掩码
 * @param en true表示启用，false表示禁用
 */
static inline void i2s_ll_enable_intr(i2s_dev_t *hw, uint32_t mask, bool en)
{
    if (en) {
        hw->int_ena.val |= mask;
    } else {
        hw->int_ena.val &= ~mask;
    }
}

/**
 * @brief 启用TX中断
 *
 * @param hw 外围I2S硬件实例地址。
 */
static inline void i2s_ll_tx_enable_intr(i2s_dev_t *hw)
{
    hw->int_ena.out_eof = 1;
    hw->int_ena.out_dscr_err = 1;
}

/**
 * @brief 禁用TX中断
 *
 * @param hw 外围I2S硬件实例地址。
 */
static inline void i2s_ll_tx_disable_intr(i2s_dev_t *hw)
{
    hw->int_ena.out_eof = 0;
    hw->int_ena.out_dscr_err = 0;
}

/**
 * @brief 启用RX中断
 *
 * @param hw 外围I2S硬件实例地址。
 */
static inline void i2s_ll_rx_enable_intr(i2s_dev_t *hw)
{
    hw->int_ena.in_suc_eof = 1;
    hw->int_ena.in_dscr_err = 1;
}

/**
 * @brief 禁用RX中断
 *
 * @param hw 外围I2S硬件实例地址。
 */
static inline void i2s_ll_rx_disable_intr(i2s_dev_t *hw)
{
    hw->int_ena.in_suc_eof = 0;
    hw->int_ena.in_dscr_err = 0;
}

/**
 * @brief 获取中断状态寄存器地址
 *
 * @param hw 外围I2S硬件实例地址。
 * @return 中断状态寄存器地址
 */
static inline volatile void *i2s_ll_get_intr_status_reg(i2s_dev_t *hw)
{
    return &hw->int_st;
}

/**
 * @brief 获取I2S中断状态
 *
 * @param hw 外围I2S硬件实例地址。
 * @return
 *        -模块中断状态
 */
static inline uint32_t i2s_ll_get_intr_status(i2s_dev_t *hw)
{
    return hw->int_st.val;
}

/**
 * @brief 清除I2S中断状态
 *
 * @param hw 外围I2S硬件实例地址。
 * @param clr_mask 用于清除中断状态的中断掩码
 */
static inline void i2s_ll_clear_intr_status(i2s_dev_t *hw, uint32_t clr_mask)
{
    hw->int_clr.val = clr_mask;
}

/**
 * @brief 重置dma输出
 *
 * @param hw 外围I2S硬件实例地址。
 */
static inline void i2s_ll_tx_reset_dma(i2s_dev_t *hw)
{
    hw->lc_conf.out_rst = 1;
    hw->lc_conf.out_rst = 0;
}

/**
 * @brief 重置dma in
 *
 * @param hw 外围I2S硬件实例地址。
 */
static inline void i2s_ll_rx_reset_dma(i2s_dev_t *hw)
{
    hw->lc_conf.in_rst = 1;
    hw->lc_conf.in_rst = 0;
}

/**
 * @brief 启动链接
 *
 * @param hw 外围I2S硬件实例地址。
 */
static inline void i2s_ll_start_out_link(i2s_dev_t *hw)
{
    hw->out_link.start = 1;
}

/**
 * @brief 设置I2S输出链接地址
 *
 * @param hw 外围I2S硬件实例地址。
 * @param val 设置链接地址的值
 */
static inline void i2s_ll_set_out_link_addr(i2s_dev_t *hw, uint32_t val)
{
    hw->out_link.addr = val;
}

/**
 * @brief 启动TX模块
 *
 * @param hw 外围I2S硬件实例地址。
 */
static inline void i2s_ll_tx_start(i2s_dev_t *hw)
{
    hw->conf.tx_start = 1;
}

/**
 * @brief 启动RX模块
 *
 * @param hw 外围I2S硬件实例地址。
 */
static inline void i2s_ll_rx_start(i2s_dev_t *hw)
{
    hw->conf.rx_start = 1;
}

/**
 * @brief 配置TX DMA描述符地址并启动TX DMA
 *
 * @param hw 外围I2S硬件实例地址。
 * @param link_addr DMA描述符链接地址。
 */
static inline void i2s_ll_tx_start_link(i2s_dev_t *hw, uint32_t link_addr)
{
    i2s_ll_set_out_link_addr(hw, link_addr);
    i2s_ll_start_out_link(hw);
}

/**
 * @brief 配置RX DMA描述符地址并启动RX DMA
 *
 * @param hw 外围I2S硬件实例地址。
 * @param link_addr DMA描述符链接地址。
 */
static inline void i2s_ll_rx_start_link(i2s_dev_t *hw, uint32_t link_addr)
{
    hw->in_link.addr = link_addr;
    hw->in_link.start = 1;
}

/**
 * @brief 停止TX模块
 *
 * @param hw 外围I2S硬件实例地址。
 */
static inline void i2s_ll_tx_stop(i2s_dev_t *hw)
{
    hw->conf.tx_start = 0;
}

/**
 * @brief 停止RX模块
 *
 * @param hw 外围I2S硬件实例地址。
 */
static inline void i2s_ll_rx_stop(i2s_dev_t *hw)
{
    hw->conf.rx_start = 0;
}

/**
 * @brief 停止链接
 *
 * @param hw 外围I2S硬件实例地址。
 */
static inline void i2s_ll_tx_stop_link(i2s_dev_t *hw)
{
    hw->out_link.stop = 1;
}

/**
 * @brief 在链接中停止
 *
 * @param hw 外围I2S硬件实例地址。
 */
static inline void i2s_ll_rx_stop_link(i2s_dev_t *hw)
{
    hw->in_link.stop = 1;
}

/**
 * @brief 从描述符地址中获取I2S
 *
 * @param hw 外围I2S硬件实例地址。
 * @param eof_addr 用于接受地址外的指针
 */
static inline void i2s_ll_tx_get_eof_des_addr(i2s_dev_t *hw, uint32_t *eof_addr)
{
    *eof_addr = hw->out_eof_des_addr;
}

/**
 * @brief 获取描述符地址中的I2S
 *
 * @param hw 外围I2S硬件实例地址。
 * @param eof_addr eof des地址中接受的指针
 */
static inline void i2s_ll_rx_get_eof_des_addr(i2s_dev_t *hw, uint32_t *eof_addr)
{
    *eof_addr = hw->in_eof_des_addr;
}

/**
 * @brief 配置接收长度以触发in_suc_eof中断
 *
 * @param hw 外围I2S硬件实例地址。
 * @param eof_num 要触发in_suc_eof中断的字节长度
 */
static inline void i2s_ll_rx_set_eof_num(i2s_dev_t *hw, int eof_num)
{
    // 在ESP32上，eof_num以单词计数。
    hw->rx_eof_num = eof_num / 4;
}

/**
 * @brief 设置I2S tx位mod
 *
 * @param hw 外围I2S硬件实例地址。
 * @param val 设置tx位mod的值
 */
static inline void i2s_ll_tx_set_bits_mod(i2s_dev_t *hw, uint32_t val)
{
    hw->sample_rate_conf.tx_bits_mod = val;
}

/**
 * @brief 在ESP32上配置TX通道位和音频数据位，sample_bit应等于data_bit
 *
 * @param hw 外围I2S硬件实例地址。
 * @param chan_bit chan位宽度
 * @param data_bit 音频数据位宽
 */
static inline void i2s_ll_tx_set_sample_bit(i2s_dev_t *hw, uint8_t chan_bit, int data_bit)
{
    hw->fifo_conf.tx_fifo_mod = (chan_bit <= I2S_BITS_PER_SAMPLE_16BIT ? 0 : 2);
    hw->sample_rate_conf.tx_bits_mod = data_bit;
}

/**
 * @brief 配置ESP32上的RX通道位和音频数据位，sample_bit应等于data_bit
 *
 * @param hw 外围I2S硬件实例地址。
 * @param chan_bit chan位宽度
 * @param data_bit 音频数据位宽
 */
static inline void i2s_ll_rx_set_sample_bit(i2s_dev_t *hw, uint8_t chan_bit, int data_bit)
{
    hw->fifo_conf.rx_fifo_mod = (chan_bit <= I2S_BITS_PER_SAMPLE_16BIT ? 0 : 2);
    hw->sample_rate_conf.rx_bits_mod = data_bit;
}

/**
 * @brief 设置当TX FIFO为空时是否继续总线上的I2S信号
 *
 * @param hw 外围I2S硬件实例地址。
 * @param en tx fifo为空时是否停止
 */
static inline void i2s_ll_tx_stop_on_fifo_empty(i2s_dev_t *hw, bool en)
{
    hw->conf1.tx_stop_en = en;
}

/**
 * @brief 设置是否绕过内部PCM模块
 *
 * @param hw 外围I2S硬件实例地址。
 * @param bypass 是否绕过PCM模块
 */
static inline void i2s_ll_tx_bypass_pcm(i2s_dev_t *hw, bool bypass)
{
    hw->conf1.tx_pcm_bypass = bypass;
}

/**
 * @brief 启用I2S DMA
 *
 * @param hw 外围I2S硬件实例地址。
 * @param ena 设置为true以启用DMA
 */
static inline void i2s_ll_enable_dma(i2s_dev_t *hw, bool ena)
{
    hw->fifo_conf.dscr_en = ena;
}

/**
 * @brief 配置TX WS信号宽度
 *
 * @param hw 外围I2S硬件实例地址。
 * @param width BCK循环中的WS宽度
 */
static inline void i2s_ll_tx_set_ws_width(i2s_dev_t *hw, int width)
{
    hw->conf.tx_short_sync = width == 1 ? 1 : 0;
}

/**
 * @brief 配置RX WS信号宽度
 *
 * @param hw 外围I2S硬件实例地址。
 * @param width BCK循环中的WS宽度
 */
static inline void i2s_ll_rx_set_ws_width(i2s_dev_t *hw, int width)
{
    hw->conf.rx_short_sync = width == 1 ? 1 : 0;
}

/**
 * @brief 启用TX MSB移位，数据将在第一个BCK时钟启动
 *
 * @param hw 外围I2S硬件实例地址。
 * @param msb_shift_enable 设置为true以启用MSB移位
 */
static inline void i2s_ll_tx_enable_msb_shift(i2s_dev_t *hw, bool msb_shift_enable)
{
    hw->conf.tx_msb_shift = msb_shift_enable;
}

/**
 * @brief 启用RX MSB移位，数据将在第一个BCK时钟启动
 *
 * @param hw 外围I2S硬件实例地址。
 * @param msb_shift_enable 设置为true以启用MSB移位
 */
static inline void i2s_ll_rx_enable_msb_shift(i2s_dev_t *hw, bool msb_shift_enable)
{
    hw->conf.rx_msb_shift = msb_shift_enable;
}

/**
 * @brief 设置I2S tx chan模式
 *
 * @param hw 外围I2S硬件实例地址。
 * @param val 设置tx-chan模式的值
 */
static inline void i2s_ll_tx_set_chan_mod(i2s_dev_t *hw, uint32_t val)
{
    hw->conf_chan.tx_chan_mod = val;
}

/**
 * @brief 启用TX单声道模式
 *
 * @param hw 外围I2S硬件实例地址。
 * @param mono_ena 设置为true以启用mono-mde。
 */
static inline void i2s_ll_tx_enable_mono_mode(i2s_dev_t *hw, bool mono_ena)
{
    int data_bit = hw->sample_rate_conf.tx_bits_mod;
    hw->fifo_conf.tx_fifo_mod = data_bit <= I2S_BITS_PER_SAMPLE_16BIT ? mono_ena : 2 + mono_ena;
    hw->conf_chan.tx_chan_mod = mono_ena;
}

/**
 * @brief 启用RX单声道模式
 *
 * @param hw 外围I2S硬件实例地址。
 * @param mono_ena 设置为true以启用mono-mde。
 */
static inline void i2s_ll_rx_enable_mono_mode(i2s_dev_t *hw, bool mono_ena)
{
    int data_bit = hw->sample_rate_conf.rx_bits_mod;
    hw->fifo_conf.rx_fifo_mod = data_bit <= I2S_BITS_PER_SAMPLE_16BIT ? mono_ena : 2 + mono_ena;
    hw->conf_chan.rx_chan_mod = mono_ena;
}

/**
 * @brief 启用I2S环回模式
 *
 * @param hw 外围I2S硬件实例地址。
 * @param loopback_en 设置为true以共享tx模块和rx模块的BCK和WS信号。
 */
static inline void i2s_ll_share_bck_ws(i2s_dev_t *hw, bool loopback_en)
{
    hw->conf.sig_loopback = loopback_en;
}



/******************************I2S PDM配置*************************************/
/**
 * @brief 配置RX PDM下采样
 *
 * @param hw 外围I2S硬件实例地址。
 * @param dsr PDM下采样配置参数
 */
static inline void i2s_ll_rx_set_pdm_dsr(i2s_dev_t *hw, i2s_pdm_dsr_t dsr)
{
    hw->pdm_conf.rx_sinc_dsr_16_en = dsr;
}

/**
 * @brief 获取RX PDM下采样配置
 *
 * @param hw 外围I2S硬件实例地址。
 * @param dsr 接受PDM下采样配置的指针
 */
static inline void i2s_ll_rx_get_pdm_dsr(i2s_dev_t *hw, i2s_pdm_dsr_t *dsr)
{
    *dsr = hw->pdm_conf.rx_sinc_dsr_16_en;
}

/**
 * @brief 启用I2S TX PDM模式
 *
 * @param hw 外围I2S硬件实例地址。
 * @param pdm_ena 设置为真以启用TX PDM模式
 */
static inline void i2s_ll_tx_enable_pdm(i2s_dev_t *hw, bool pdm_ena)
{
    hw->pdm_conf.tx_pdm_en = pdm_ena;
    hw->pdm_conf.pcm2pdm_conv_en = pdm_ena;
}

/**
 * @brief 启用I2S RX PDM模式
 *
 * @param hw 外围I2S硬件实例地址。
 * @param pdm_ena 设置为真以启用RX PDM模式
 */
static inline void i2s_ll_rx_enable_pdm(i2s_dev_t *hw, bool pdm_ena)
{
    hw->pdm_conf.rx_pdm_en = pdm_ena;
    hw->pdm_conf.pdm2pcm_conv_en = pdm_ena;
}

/**
 * @brief 设置I2S TX PDM预缩放
 *
 * @param hw 外围I2S硬件实例地址。
 * @param prescale I2S TX PDM预缩放
 */
static inline void i2s_ll_tx_set_pdm_prescale(i2s_dev_t *hw, bool prescale)
{
    HAL_FORCE_MODIFY_U32_REG_FIELD(hw->pdm_conf, tx_prescale, prescale);
}

/**
 * @brief 设置I2S TX PDM高通滤波器缩放
 *
 * @param hw 外围I2S硬件实例地址。
 * @param sig_scale 发送至滤波器之前的I2S TX PDM信号缩放
 */
static inline void i2s_ll_tx_set_pdm_hp_scale(i2s_dev_t *hw, i2s_pdm_sig_scale_t sig_scale)
{
    hw->pdm_conf.tx_hp_in_shift = sig_scale;
}

/**
 * @brief 设置I2S TX PDM低通滤波器缩放
 *
 * @param hw 外围I2S硬件实例地址。
 * @param sig_scale 发送至滤波器之前的I2S TX PDM信号缩放
 */
static inline void i2s_ll_tx_set_pdm_lp_scale(i2s_dev_t *hw, i2s_pdm_sig_scale_t sig_scale)
{
    hw->pdm_conf.tx_lp_in_shift = sig_scale;
}

/**
 * @brief 设置I2S TX PDM sinc滤波器缩放
 *
 * @param hw 外围I2S硬件实例地址。
 * @param sig_scale 发送至滤波器之前的I2S TX PDM信号缩放
 */
static inline void i2s_ll_tx_set_pdm_sinc_scale(i2s_dev_t *hw, i2s_pdm_sig_scale_t sig_scale)
{
    hw->pdm_conf.tx_sinc_in_shift = sig_scale;
}

/**
 * @brief 设置I2S TX PDM sigma delta滤波器缩放
 *
 * @param hw 外围I2S硬件实例地址。
 * @param sig_scale 发送至滤波器之前的I2S TX PDM信号缩放
 */
static inline void i2s_ll_tx_set_pdm_sd_scale(i2s_dev_t *hw, i2s_pdm_sig_scale_t sig_scale)
{
    hw->pdm_conf.tx_sigmadelta_in_shift = sig_scale;
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
    hw->pdm_freq_conf.tx_pdm_fp = fp;
    hw->pdm_freq_conf.tx_pdm_fs = fs;
    hw->pdm_conf.tx_sinc_osr2 = fp / fs;
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
    return hw->pdm_freq_conf.tx_pdm_fp;
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
    return hw->pdm_freq_conf.tx_pdm_fs;
}




/****************************I2S ADC/DAC配置***********************************/
/**
 * @brief 启用I2S LCD模式
 * @note  必须启用LCD模式才能使用内置ADC/DAC
 *
 * @param hw 外围I2S硬件实例地址。
 * @param enable 设置为true以启用LCD模式。
 */
static inline void i2s_ll_enable_lcd(i2s_dev_t *hw, bool enable)
{
    hw->conf2.lcd_en = enable;
}

/**
 * @brief 启用I2S相机模式
 *
 * @param hw 外围I2S硬件实例地址。
 * @param enable 设置为true以启用相机模式。
 */
static inline void i2s_ll_enable_camera(i2s_dev_t *hw, bool enable)
{
    hw->conf2.camera_en = enable;
}

/**
 * @brief 在ADC模式下启用I2S内置
 *
 * @param hw 外围I2S硬件实例地址。
 * @param enable 设置为true以启用内置ADC
 */
static inline void i2s_ll_enable_builtin_adc(i2s_dev_t *hw, bool enable)
{
    hw->conf2.lcd_en = enable;
    hw->conf2.camera_en = 0;
    hw->conf.rx_right_first = 0;
    hw->conf.rx_msb_shift = 0;
    hw->conf.rx_mono = 0;
    hw->conf.rx_short_sync = 0;
    hw->fifo_conf.rx_fifo_mod = enable;
    hw->conf_chan.rx_chan_mod = enable;
}

/**
 * @brief 在DAC模式下启用I2S内置
 *
 * @param hw 外围I2S硬件实例地址。
 *  * @param enable 设置为true以启用内置DAC
 */
static inline void i2s_ll_enable_builtin_dac(i2s_dev_t *hw, bool enable)
{
    hw->conf2.lcd_en = enable;
    hw->conf2.camera_en = 0;
    hw->conf.tx_right_first = enable;
    hw->conf.tx_msb_shift = 0;
    hw->conf.tx_short_sync = 0;
}

#ifdef __cplusplus
}
#endif

