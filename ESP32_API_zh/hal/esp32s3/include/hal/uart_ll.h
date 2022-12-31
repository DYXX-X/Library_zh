// 版权所有2015-2020 Espressif Systems（上海）私人有限公司
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

// UART寄存器操作的LL层。
// 注意，该层中的大多数寄存器操作都是非原子操作。


#pragma once

#include "hal/misc.h"
#include "hal/uart_types.h"
#include "soc/uart_periph.h"
#include "soc/uart_struct.h"
#include "esp_attr.h"

#ifdef __cplusplus
extern "C" {
#endif

// 默认fifo深度
#define UART_LL_FIFO_DEF_LEN  (SOC_UART_FIFO_LEN)
// 通过提供UART num获取UART硬件实例
#define UART_LL_GET_HW(num) (((num) == 0) ? (&UART0) : (((num) == 1) ? (&UART1) : (&UART2)))

#define UART_LL_MIN_WAKEUP_THRESH (2)
#define UART_LL_INTR_MASK         (0x7ffff) //所有中断掩码

#define UART_LL_FSM_IDLE          (0x0)
#define UART_LL_FSM_TX_WAIT_SEND  (0xf)

// 定义UART中断
typedef enum {
    UART_INTR_RXFIFO_FULL      = (0x1 << 0),
    UART_INTR_TXFIFO_EMPTY     = (0x1 << 1),
    UART_INTR_PARITY_ERR       = (0x1 << 2),
    UART_INTR_FRAM_ERR         = (0x1 << 3),
    UART_INTR_RXFIFO_OVF       = (0x1 << 4),
    UART_INTR_DSR_CHG          = (0x1 << 5),
    UART_INTR_CTS_CHG          = (0x1 << 6),
    UART_INTR_BRK_DET          = (0x1 << 7),
    UART_INTR_RXFIFO_TOUT      = (0x1 << 8),
    UART_INTR_SW_XON           = (0x1 << 9),
    UART_INTR_SW_XOFF          = (0x1 << 10),
    UART_INTR_GLITCH_DET       = (0x1 << 11),
    UART_INTR_TX_BRK_DONE      = (0x1 << 12),
    UART_INTR_TX_BRK_IDLE      = (0x1 << 13),
    UART_INTR_TX_DONE          = (0x1 << 14),
    UART_INTR_RS485_PARITY_ERR = (0x1 << 15),
    UART_INTR_RS485_FRM_ERR    = (0x1 << 16),
    UART_INTR_RS485_CLASH      = (0x1 << 17),
    UART_INTR_CMD_CHAR_DET     = (0x1 << 18),
} uart_intr_t;

/**
 * @brief  配置UART核心重置。
 *
 * @param  hw 外围寄存器的起始地址。
 * @param  core_rst_en True启用核心重置，否则设置为false。
 *
 * @return 没有一个
 */
static inline void uart_ll_set_reset_core(uart_dev_t *hw, bool core_rst_en)
{
    hw->clk_conf.rst_core = core_rst_en;
}

/**
 * @brief  设置UART源时钟。
 *
 * @param  hw 外围寄存器的起始地址。
 * @param  source_clk UART源时钟。源时钟可以是APB时钟、RTC时钟或XTAL时钟。如果源时钟为RTC/XTAL，则当APB发生变化时，UART仍可工作。
 *
 * @return 没有一个
 */
FORCE_INLINE_ATTR void uart_ll_set_sclk(uart_dev_t *hw, uart_sclk_t source_clk)
{
    switch (source_clk) {
        default:
        case UART_SCLK_APB:
            hw->clk_conf.sclk_sel = 1;
            break;
        case UART_SCLK_RTC:
            hw->clk_conf.sclk_sel = 2;
            break;
        case UART_SCLK_XTAL:
            hw->clk_conf.sclk_sel = 3;
            break;
    }
}

/**
 * @brief  获取UART源时钟类型。
 *
 * @param  hw 外围寄存器的起始地址。
 * @param  source_clk 接受UART源时钟类型的指针。
 *
 * @return 没有一个
 */
FORCE_INLINE_ATTR void uart_ll_get_sclk(uart_dev_t *hw, uart_sclk_t *source_clk)
{
    switch (hw->clk_conf.sclk_sel) {
        default:
        case 1:
            *source_clk = UART_SCLK_APB;
            break;
        case 2:
            *source_clk = UART_SCLK_RTC;
            break;
        case 3:
            *source_clk = UART_SCLK_XTAL;
            break;
    }
}

/**
 * @brief  获取UART源时钟频率。
 *
 * @param  hw 外围寄存器的起始地址。
 *
 * @return 电流源时钟频率
 */
FORCE_INLINE_ATTR uint32_t uart_ll_get_sclk_freq(uart_dev_t *hw)
{
    switch (hw->clk_conf.sclk_sel) {
        default:
        case 1:
            return APB_CLK_FREQ;
        case 2:
            return RTC_CLK_FREQ;
        case 3:
            return XTAL_CLK_FREQ;
    }
}

/**
 * @brief  配置波特率。
 *
 * @param  hw 外围寄存器的起始地址。
 * @param  baud 要设置的波特率。
 *
 * @return 没有一个
 */
FORCE_INLINE_ATTR void uart_ll_set_baudrate(uart_dev_t *hw, uint32_t baud)
{
#define DIV_UP(a, b)    (((a) + (b) - 1) / (b))
    uint32_t sclk_freq = uart_ll_get_sclk_freq(hw);
    const uint32_t max_div = BIT(12) - 1;   // UART除法器整数部分只有12位
    int sclk_div = DIV_UP(sclk_freq, max_div * baud);

    uint32_t clk_div = ((sclk_freq) << 4) / (baud * sclk_div);
    // 波特率配置寄存器分为
    // 整数部分和小数部分。
    hw->clkdiv.clkdiv = clk_div >> 4;
    hw->clkdiv.clkdiv_frag = clk_div &  0xf;
    HAL_FORCE_MODIFY_U32_REG_FIELD(hw->clk_conf, sclk_div_num, sclk_div - 1);
#undef DIV_UP
}

/**
 * @brief  获取当前波特率。
 *
 * @param  hw 外围寄存器的起始地址。
 *
 * @return 当前的波特率
 */
FORCE_INLINE_ATTR uint32_t uart_ll_get_baudrate(uart_dev_t *hw)
{
    uint32_t sclk_freq = uart_ll_get_sclk_freq(hw);
    uart_clkdiv_reg_t div_reg = hw->clkdiv;
    return ((sclk_freq << 4)) /
        (((div_reg.clkdiv << 4) | div_reg.clkdiv_frag) * (HAL_FORCE_READ_U32_REG_FIELD(hw->clk_conf, sclk_div_num) + 1));
}

/**
 * @brief  根据给定掩码启用UART中断。
 *
 * @param  hw 外围寄存器的起始地址。
 * @param  mask 需要启用中断位图。
 *
 * @return 没有一个
 */
FORCE_INLINE_ATTR void uart_ll_ena_intr_mask(uart_dev_t *hw, uint32_t mask)
{
    hw->int_ena.val |= mask;
}

/**
 * @brief  根据给定掩码禁用UART中断。
 *
 * @param  hw 外围寄存器的起始地址。
 * @param  mask 需要禁用中断位图。
 *
 * @return 没有一个
 */
FORCE_INLINE_ATTR void uart_ll_disable_intr_mask(uart_dev_t *hw, uint32_t mask)
{
    hw->int_ena.val &= (~mask);
}

/**
 * @brief  获取UART中断状态。
 *
 * @param  hw 外围寄存器的起始地址。
 *
 * @return UART中断状态。
 */
FORCE_INLINE_ATTR uint32_t uart_ll_get_intsts_mask(uart_dev_t *hw)
{
    return hw->int_st.val;
}

/**
 * @brief  根据给定掩码清除UART中断状态。
 *
 * @param  hw 外围寄存器的起始地址。
 * @param  mask 需要清除中断位图。
 *
 * @return 没有一个
 */
FORCE_INLINE_ATTR void uart_ll_clr_intsts_mask(uart_dev_t *hw, uint32_t mask)
{
    hw->int_clr.val = mask;
}

/**
 * @brief  获取已启用中断的状态。
 *
 * @param  hw 外围寄存器的起始地址。
 *
 * @return 中断使能值
 */
FORCE_INLINE_ATTR uint32_t uart_ll_get_intr_ena_status(uart_dev_t *hw)
{
    return hw->int_ena.val;
}

/**
 * @brief  读取UART rxfifo。
 *
 * @param  hw 外围寄存器的起始地址。
 * @param  buf 数据缓冲区。缓冲区大小应大于128字节。
 * @param  rd_len 需要读取数据长度。
 *
 * @return 没有一个
 */
FORCE_INLINE_ATTR void uart_ll_read_rxfifo(uart_dev_t *hw, uint8_t *buf, uint32_t rd_len)
{
    for (int i = 0; i < (int)rd_len; i++) {
        buf[i] = hw->fifo.rxfifo_rd_byte;
    }
}

/**
 * @brief  将字节写入UART txfifo。
 *
 * @param  hw 外围寄存器的起始地址。
 * @param  buf 数据缓冲区。
 * @param  wr_len 数据长度需要写入。
 *
 * @return 没有一个
 */
FORCE_INLINE_ATTR void uart_ll_write_txfifo(uart_dev_t *hw, const uint8_t *buf, uint32_t wr_len)
{
    for (int i = 0; i < (int)wr_len; i++) {
        hw->fifo.rxfifo_rd_byte = buf[i];
    }
}

/**
 * @brief  重置UART hw-rxfifo。
 *
 * @param  hw 外围寄存器的起始地址。
 *
 * @return 没有一个
 */
FORCE_INLINE_ATTR void uart_ll_rxfifo_rst(uart_dev_t *hw)
{
    hw->conf0.rxfifo_rst = 1;
    hw->conf0.rxfifo_rst = 0;
}

/**
 * @brief  重置UART hw txfifo。
 *
 * @param  hw 外围寄存器的起始地址。
 *
 * @return 没有一个
 */
FORCE_INLINE_ATTR void uart_ll_txfifo_rst(uart_dev_t *hw)
{
    hw->conf0.txfifo_rst = 1;
    hw->conf0.txfifo_rst = 0;
}

/**
 * @brief  获取UARTRxfifo中可读数据的长度。
 *
 * @param  hw 外围寄存器的起始地址。
 *
 * @return rxifo中的可读数据长度。
 */
FORCE_INLINE_ATTR uint32_t uart_ll_get_rxfifo_len(uart_dev_t *hw)
{
    return hw->status.rxfifo_cnt;
}

/**
 * @brief  获取UART txfifo的可写数据长度。
 *
 * @param  hw 外围寄存器的起始地址。
 *
 * @return 可以写入txfifo的数据长度。
 */
FORCE_INLINE_ATTR uint32_t uart_ll_get_txfifo_len(uart_dev_t *hw)
{
    return UART_LL_FIFO_DEF_LEN - hw->status.txfifo_cnt;
}

/**
 * @brief  配置UART停止位。
 *
 * @param  hw 外围寄存器的起始地址。
 * @param  stop_bit 要设置的停止位数。
 *
 * @return 没有一个
 */
FORCE_INLINE_ATTR void uart_ll_set_stop_bits(uart_dev_t *hw, uart_stop_bits_t stop_bit)
{
    hw->conf0.stop_bit_num = stop_bit;
}

/**
 * @brief  获取UART停止位的配置。
 *
 * @param  hw 外围寄存器的起始地址。
 * @param  stop_bit 接受停止位配置的指针
 *
 * @return 没有一个
 */
FORCE_INLINE_ATTR void uart_ll_get_stop_bits(uart_dev_t *hw, uart_stop_bits_t *stop_bit)
{
    *stop_bit = hw->conf0.stop_bit_num;
}

/**
 * @brief  配置UART奇偶校验模式。
 *
 * @param  hw 外围寄存器的起始地址。
 * @param  parity_mode 要设置的奇偶校验模式。
 *
 * @return 没有一个
 */
FORCE_INLINE_ATTR void uart_ll_set_parity(uart_dev_t *hw, uart_parity_t parity_mode)
{
    if (parity_mode != UART_PARITY_DISABLE) {
        hw->conf0.parity = parity_mode & 0x1;
    }
    hw->conf0.parity_en = (parity_mode >> 1) & 0x1;
}

/**
 * @brief  获取UART奇偶校验模式配置。
 *
 * @param  hw 外围寄存器的起始地址。
 * @param  parity_mode 用于接受奇偶校验模式配置的指针。
 *
 * @return 没有一个
 */
FORCE_INLINE_ATTR void uart_ll_get_parity(uart_dev_t *hw, uart_parity_t *parity_mode)
{
    if (hw->conf0.parity_en) {
        *parity_mode = 0X2 | hw->conf0.parity;
    } else {
        *parity_mode = UART_PARITY_DISABLE;
    }
}

/**
 * @brief  设置UART rxfifo满阈值。当rxfifo中的数据大于阈值时，它将产生rxfifo_full_int_raw中断。
 *
 * @param  hw 外围寄存器的起始地址。
 * @param  full_thrhd rxfifo的完整阈值`full_thrhd`应小于`UART_LL_FIFO_DEF_LEN`。
 *
 * @return 没有一个
 */
FORCE_INLINE_ATTR void uart_ll_set_rxfifo_full_thr(uart_dev_t *hw, uint16_t full_thrhd)
{
    hw->conf1.rxfifo_full_thrhd = full_thrhd;
}

/**
 * @brief  设置txfifo空阈值。当txfifo中的数据长度小于阈值时，将产生txfifo清空intraw中断。
 *
 * @param  hw 外围寄存器的起始地址。
 * @param  empty_thrhd txfifo的空阈值。
 *
 * @return 没有一个
 */
FORCE_INLINE_ATTR void uart_ll_set_txfifo_empty_thr(uart_dev_t *hw, uint16_t empty_thrhd)
{
    hw->conf1.txfifo_empty_thrhd = empty_thrhd;
}

/**
 * @brief  设置UART rx空闲阈值。当接收机接收一个字节数据所花费的时间超过rxidlethrhd时，它将产生帧结束信号，以便uhci停止接收数据。
 *
 * @param  hw 外围寄存器的起始地址。
 * @param  rx_idle_thr 要设置的rx空闲阈值。
 *
 * @return 没有一个
 */
FORCE_INLINE_ATTR void uart_ll_set_rx_idle_thr(uart_dev_t *hw, uint32_t rx_idle_thr)
{
    hw->idle_conf.rx_idle_thrhd = rx_idle_thr;
}

/**
 * @brief  配置传输之间的持续时间。
 *
 * @param  hw 外围寄存器的起始地址。
 * @param  idle_num 传输之间的持续时间。
 *
 * @return 没有一个
 */
FORCE_INLINE_ATTR void uart_ll_set_tx_idle_num(uart_dev_t *hw, uint32_t idle_num)
{
    hw->idle_conf.tx_idle_num = idle_num;
}

/**
 * @brief  配置传输程序以发送中断字符。
 *
 * @param  hw 外围寄存器的起始地址。
 * @param  break_num 需要发送的中断字符数。
 *
 * @return 没有一个
 */
FORCE_INLINE_ATTR void uart_ll_tx_break(uart_dev_t *hw, uint32_t break_num)
{
    if (break_num > 0) {
        HAL_FORCE_MODIFY_U32_REG_FIELD(hw->txbrk_conf, tx_brk_num, break_num);
        hw->conf0.txd_brk = 1;
    } else {
        hw->conf0.txd_brk = 0;
    }
}
/**
 * @brief  配置UART硬件流量控制。
 *
 * @param  hw 外围寄存器的起始地址。
 * @param  flow_ctrl 硬件流控制配置。
 * @param  rx_thrs 如果rxfifo中的数据长度大于此值，则rx流控制信号将激活。
 *
 * @return 没有一个
 */
FORCE_INLINE_ATTR void uart_ll_set_hw_flow_ctrl(uart_dev_t *hw, uart_hw_flowcontrol_t flow_ctrl, uint32_t rx_thrs)
{
    //只有当设置了UART_HW_FLOWCTRL_RTS时，才会设置rx_thresh值。
    if (flow_ctrl & UART_HW_FLOWCTRL_RTS) {
        hw->mem_conf.rx_flow_thrhd = rx_thrs;
        hw->conf1.rx_flow_en = 1;
    } else {
        hw->conf1.rx_flow_en = 0;
    }
    if (flow_ctrl & UART_HW_FLOWCTRL_CTS) {
        hw->conf0.tx_flow_en = 1;
    } else {
        hw->conf0.tx_flow_en = 0;
    }
}

/**
 * @brief  配置硬件流控制。
 *
 * @param  hw 外围寄存器的起始地址。
 * @param  flow_ctrl 用于接受硬件流控制配置的指针。
 *
 * @return 没有一个
 */
FORCE_INLINE_ATTR void uart_ll_get_hw_flow_ctrl(uart_dev_t *hw, uart_hw_flowcontrol_t *flow_ctrl)
{
    *flow_ctrl = UART_HW_FLOWCTRL_DISABLE;
    if (hw->conf1.rx_flow_en) {
        *flow_ctrl |= UART_HW_FLOWCTRL_RTS;
    }
    if (hw->conf0.tx_flow_en) {
        *flow_ctrl |= UART_HW_FLOWCTRL_CTS;
    }
}

/**
 * @brief  配置软件流控制。
 *
 * @param  hw 外围寄存器的起始地址。
 * @param  flow_ctrl UART软件流控制设置。
 * @param  sw_flow_ctrl_en 设置为true以启用软件流控制，否则设置为false。
 *
 * @return 没有一个
 */
FORCE_INLINE_ATTR void uart_ll_set_sw_flow_ctrl(uart_dev_t *hw, uart_sw_flowctrl_t *flow_ctrl, bool sw_flow_ctrl_en)
{
    if (sw_flow_ctrl_en) {
        hw->flow_conf.xonoff_del = 1;
        hw->flow_conf.sw_flow_con_en = 1;
        hw->swfc_conf1.xon_threshold = flow_ctrl->xon_thrd;
        hw->swfc_conf0.xoff_threshold = flow_ctrl->xoff_thrd;
        HAL_FORCE_MODIFY_U32_REG_FIELD(hw->swfc_conf1, xon_char, flow_ctrl->xon_char);
        HAL_FORCE_MODIFY_U32_REG_FIELD(hw->swfc_conf0, xoff_char, flow_ctrl->xoff_char);
    } else {
        hw->flow_conf.sw_flow_con_en = 0;
        hw->flow_conf.xonoff_del = 0;
    }
}

/**
 * @brief  配置AT cmd字符。当接收机接收到一个连续的AT cmd字符时，它将产生AT_cmd_char_det中断。
 *
 * @param  hw 外围寄存器的起始地址。
 * @param  cmd_char AT cmd字符配置。配置成员为：
 *         -cmd_char AT cmd字符
 *         -char_num收到的AT cmd字符数必须等于或大于此值
 *         -gap_out每个AT cmd字符之间的间隔，当持续时间小于此值时，它不会将此数据作为AT cmd字符串
 *         -pre_idle第一个AT cmd字符之前的空闲时间，当持续时间小于此值时，它不会将之前的数据作为最后一个AT cmd字符
 *         -post_idle最后一个AT cmd字符之后的空闲时间，当持续时间小于此值时，它不会将此数据作为第一个AT cmd字符
 *
 * @return 没有一个
 */
FORCE_INLINE_ATTR void uart_ll_set_at_cmd_char(uart_dev_t *hw, uart_at_cmd_t *cmd_char)
{
    HAL_FORCE_MODIFY_U32_REG_FIELD(hw->at_cmd_char, at_cmd_char, cmd_char->cmd_char);
    HAL_FORCE_MODIFY_U32_REG_FIELD(hw->at_cmd_char, char_num, cmd_char->char_num);
    HAL_FORCE_MODIFY_U32_REG_FIELD(hw->at_cmd_postcnt, post_idle_num, cmd_char->post_idle);
    HAL_FORCE_MODIFY_U32_REG_FIELD(hw->at_cmd_precnt, pre_idle_num, cmd_char->pre_idle);
    HAL_FORCE_MODIFY_U32_REG_FIELD(hw->at_cmd_gaptout, rx_gap_tout, cmd_char->gap_tout);
}

/**
 * @brief  设置UART数据位模式。
 *
 * @param  hw 外围寄存器的起始地址。
 * @param  data_bit 要设置的数据位模式。
 *
 * @return 没有一个
 */
FORCE_INLINE_ATTR void uart_ll_set_data_bit_num(uart_dev_t *hw, uart_word_length_t data_bit)
{
    hw->conf0.bit_num = data_bit;
}

/**
强制INLINE_ATTR无效uart_ll_get_sclk（uart_dev_t*hw，uart_sclk_t*source_clk）
 * @brief  设置rts活动级别。
 *
 * @param  hw 外围寄存器的起始地址。
 * @param  level rts活动级别，0或1。
 *
 * @return 没有一个
 */
FORCE_INLINE_ATTR void uart_ll_set_rts_active_level(uart_dev_t *hw, int level)
{
    hw->conf0.sw_rts = level & 0x1;
}

/**
 * @brief  设置dtr活动级别。
 *
 * @param  hw 外围寄存器的起始地址。
 * @param  level dtr活动级别，0或1。
 *
 * @return 没有一个
 */
FORCE_INLINE_ATTR void uart_ll_set_dtr_active_level(uart_dev_t *hw, int level)
{
    hw->conf0.sw_dtr = level & 0x1;
}

/**
 * @brief  设置UART唤醒阈值。
 *
 * @param  hw 外围寄存器的起始地址。
 * @param  wakeup_thrd 要设置的唤醒阈值。当输入rx边缘变化超过该值时，UART将从浅睡眠模式激活。
 *
 * @return 没有一个
 */
FORCE_INLINE_ATTR void uart_ll_set_wakeup_thrd(uart_dev_t *hw, uint32_t wakeup_thrd)
{
    hw->sleep_conf.active_threshold = wakeup_thrd - UART_LL_MIN_WAKEUP_THRESH;
}

/**
 * @brief  在正常模式下配置UART工作。
 *
 * @param  hw 外围寄存器的起始地址。
 *
 * @return 没有一个
 */
FORCE_INLINE_ATTR void uart_ll_set_mode_normal(uart_dev_t *hw)
{
    hw->rs485_conf.rs485_en = 0;
    hw->rs485_conf.rs485tx_rx_en= 0;
    hw->rs485_conf.rs485rxby_tx_en = 0;
    hw->conf0.irda_en = 0;
}

/**
 * @brief  在rs485_app_ctrl模式下配置UART工作。
 *
 * @param  hw 外围寄存器的起始地址。
 *
 * @return 没有一个
 */
FORCE_INLINE_ATTR void uart_ll_set_mode_rs485_app_ctrl(uart_dev_t *hw)
{
    // 应用软件控制，消除回声
    hw->rs485_conf.rs485rxby_tx_en = 1;
    hw->conf0.irda_en = 0;
    hw->conf0.sw_rts = 0;
    hw->conf0.irda_en = 0;
    hw->rs485_conf.rs485_en = 1;
}

/**
 * @brief  在rs485_half_duplex模式下配置UART工作。
 *
 * @param  hw 外围寄存器的起始地址。
 *
 * @return 没有一个
 */
FORCE_INLINE_ATTR void uart_ll_set_mode_rs485_half_duplex(uart_dev_t *hw)
{
    // 启用接收器，sw_rts=1在rts引脚上生成低电平
    hw->conf0.sw_rts = 1;
    // 必须设置为0才能自动删除回声
    hw->rs485_conf.rs485tx_rx_en = 0;
    // 这是为了避免碰撞
    hw->rs485_conf.rs485rxby_tx_en = 1;
    hw->conf0.irda_en = 0;
    hw->rs485_conf.rs485_en= 1;
}

/**
 * @brief  在碰撞检测模式下配置UART工作。
 *
 * @param  hw 外围寄存器的起始地址。
 *
 * @return 没有一个
 */
FORCE_INLINE_ATTR void uart_ll_set_mode_collision_detect(uart_dev_t *hw)
{
    hw->conf0.irda_en = 0;
    // 发射机输出信号回路回到接收机输入信号
    hw->rs485_conf.rs485tx_rx_en = 1 ;
    // 发射机应在接收机忙时发送数据
    hw->rs485_conf.rs485rxby_tx_en = 1;
    hw->conf0.sw_rts = 0;
    hw->rs485_conf.rs485_en = 1;
}

/**
 * @brief  在irda模式下配置UART工作。
 *
 * @param  hw 外围寄存器的起始地址。
 *
 * @return 没有一个
 */
FORCE_INLINE_ATTR void uart_ll_set_mode_irda(uart_dev_t *hw)
{
    hw->rs485_conf.rs485_en = 0;
    hw->rs485_conf.rs485tx_rx_en = 0;
    hw->rs485_conf.rs485rxby_tx_en = 0;
    hw->conf0.sw_rts = 0;
    hw->conf0.irda_en = 1;
}

/**
 * @brief  设置uart模式。
 *
 * @param  hw 外围寄存器的起始地址。
 * @param  mode 要设置的UART模式。
 *
 * @return 没有一个
 */
FORCE_INLINE_ATTR void uart_ll_set_mode(uart_dev_t *hw, uart_mode_t mode)
{
    switch (mode) {
    default:
    case UART_MODE_UART:
        uart_ll_set_mode_normal(hw);
        break;
    case UART_MODE_RS485_COLLISION_DETECT:
        uart_ll_set_mode_collision_detect(hw);
        break;
    case UART_MODE_RS485_APP_CTRL:
        uart_ll_set_mode_rs485_app_ctrl(hw);
        break;
    case UART_MODE_RS485_HALF_DUPLEX:
        uart_ll_set_mode_rs485_half_duplex(hw);
        break;
    case UART_MODE_IRDA:
        uart_ll_set_mode_irda(hw);
        break;
    }
}

/**
 * @brief  获取UART AT cmd字符配置。
 *
 * @param  hw 外围寄存器的起始地址。
 * @param  cmd_char 用于接受UART AT cmd字符值的指针。
 * @param  char_num 用于接受UART AT cmd字符重复数的指针。
 *
 * @return 没有一个
 */
FORCE_INLINE_ATTR void uart_ll_get_at_cmd_char(uart_dev_t *hw, uint8_t *cmd_char, uint8_t *char_num)
{
    *cmd_char = HAL_FORCE_READ_U32_REG_FIELD(hw->at_cmd_char, at_cmd_char);
    *char_num = HAL_FORCE_READ_U32_REG_FIELD(hw->at_cmd_char, char_num);
}

/**
 * @brief  获取UART唤醒阈值。
 *
 * @param  hw 外围寄存器的起始地址。
 *
 * @return UART唤醒阈值。
 */
FORCE_INLINE_ATTR uint32_t uart_ll_get_wakeup_thrd(uart_dev_t *hw)
{
    return hw->sleep_conf.active_threshold + UART_LL_MIN_WAKEUP_THRESH;
}

/**
 * @brief  获取UART数据位配置。
 *
 * @param  hw 外围寄存器的起始地址。
 * @param  data_bit 接受UART数据位配置的指针。
 *
 * @return 位模式。
 */
FORCE_INLINE_ATTR void uart_ll_get_data_bit_num(uart_dev_t *hw, uart_word_length_t *data_bit)
{
    *data_bit = hw->conf0.bit_num;
}

/**
 * @brief  检查UART发送状态机是否处于IDLE状态。
 *
 * @param  hw 外围寄存器的起始地址。
 *
 * @return 如果状态机处于IDLE状态，则为True，否则返回false。
 */
FORCE_INLINE_ATTR bool uart_ll_is_tx_idle(uart_dev_t *hw)
{
    return ((hw->status.txfifo_cnt == 0) && (hw->fsm_status.st_utx_out == 0));
}

/**
 * @brief  检查UART rts流量控制是否已启用。
 *
 * @param  hw 外围寄存器的起始地址。
 *
 * @return 如果启用了hw-rts流控制，则为True，否则返回false。
 */
FORCE_INLINE_ATTR bool uart_ll_is_hw_rts_en(uart_dev_t *hw)
{
    return hw->conf1.rx_flow_en;
}

/**
 * @brief  检查UART cts流量控制是否启用。
 *
 * @param  hw 外围寄存器的起始地址。
 *
 * @return 如果启用了工作流控制，则为True，否则返回false。
 */
FORCE_INLINE_ATTR bool uart_ll_is_hw_cts_en(uart_dev_t *hw)
{
    return hw->conf0.tx_flow_en;
}

/**
 * @brief 将TX信号回路配置回RX模块，仅用于测试目的
 *
 * @param  hw 外围寄存器的起始地址。
 * @param  loop_back_en 设置ture以启用循环返回功能，否则设置为false。
 *
 * @return 没有一个
 */
FORCE_INLINE_ATTR void uart_ll_set_loop_back(uart_dev_t *hw, bool loop_back_en)
{
    hw->conf0.loopback = loop_back_en;
}

/**
 * @brief  用给定掩码反转UART信号。
 *
 * @param  hw 外围寄存器的起始地址。
 * @param  inv_mask UART信号位图需要反转。使用“uart_signal_inv_t”的OR红色掩码；
 *
 * @return 没有一个
 */
FORCE_INLINE_ATTR void uart_ll_inverse_signal(uart_dev_t *hw, uint32_t inv_mask)
{
    uart_conf0_reg_t conf0_reg = hw->conf0;
    conf0_reg.irda_tx_inv = (inv_mask & UART_SIGNAL_IRDA_TX_INV) ? 1 : 0;
    conf0_reg.irda_rx_inv = (inv_mask & UART_SIGNAL_IRDA_RX_INV) ? 1 : 0;
    conf0_reg.rxd_inv = (inv_mask & UART_SIGNAL_RXD_INV) ? 1 : 0;
    conf0_reg.cts_inv = (inv_mask & UART_SIGNAL_CTS_INV) ? 1 : 0;
    conf0_reg.dsr_inv = (inv_mask & UART_SIGNAL_DSR_INV) ? 1 : 0;
    conf0_reg.txd_inv = (inv_mask & UART_SIGNAL_TXD_INV) ? 1 : 0;
    conf0_reg.rts_inv = (inv_mask & UART_SIGNAL_RTS_INV) ? 1 : 0;
    conf0_reg.dtr_inv = (inv_mask & UART_SIGNAL_DTR_INV) ? 1 : 0;
    hw->conf0.val = conf0_reg.val;
}

/**
 * @brief  配置接收器接收字节的超时值，并启用rx超时功能。
 *
 * @param  hw 外围寄存器的起始地址。
 * @param  tout_thrd 超时值为UART位时间。如果“tout_thrd==0”，则rx超时功能将被禁用。
 *
 * @return 没有一个
 */
FORCE_INLINE_ATTR void uart_ll_set_rx_tout(uart_dev_t *hw, uint16_t tout_thrd)
{
    uint16_t tout_val = tout_thrd;
    if(tout_thrd > 0) {
        hw->mem_conf.rx_tout_thrhd = tout_val;
        hw->conf1.rx_tout_en = 1;
    } else {
        hw->conf1.rx_tout_en = 0;
    }
}

/**
 * @brief  获取接收器接收字节的超时值。
 *
 * @param  hw 外围寄存器的起始地址。
 *
 * @return tout_thr超时阈值。如果禁用超时功能，则返回0。
 */
FORCE_INLINE_ATTR uint16_t uart_ll_get_rx_tout_thr(uart_dev_t *hw)
{
    uint16_t tout_thrd = 0;
    if(hw->conf1.rx_tout_en > 0) {
        tout_thrd = hw->mem_conf.rx_tout_thrhd;
    }
    return tout_thrd;
}

/**
 * @brief  获取UART最大超时阈值。
 *
 * @param  hw 外围寄存器的起始地址。
 *
 * @return 最大超时阈值。
 */
FORCE_INLINE_ATTR uint16_t uart_ll_max_tout_thrd(uart_dev_t *hw)
{
    return UART_RX_TOUT_THRHD_V;
}

/**
 * @brief  配置自动波特率。
 *
 * @param  hw 外围寄存器的起始地址。
 * @param  enable 布尔标记是否应启用自动波特率。
 */
FORCE_INLINE_ATTR void uart_ll_set_autobaud_en(uart_dev_t *hw, bool enable)
{
    hw->conf0.autobaud_en = enable ? 1 : 0;
}

/**
 * @brief  获取RXD边缘计数。
 *
 * @param  hw 外围寄存器的起始地址。
 */
FORCE_INLINE_ATTR uint32_t uart_ll_get_rxd_edge_cnt(uart_dev_t *hw)
{
    return hw->rxd_cnt.rxd_edge_cnt;
}

/**
 * @brief  获取正脉冲最小计数。
 *
 * @param  hw 外围寄存器的起始地址。
 */
FORCE_INLINE_ATTR uint32_t uart_ll_get_pos_pulse_cnt(uart_dev_t *hw)
{
    return hw->pospulse.posedge_min_cnt;
}

/**
 * @brief  获取负脉冲最小计数。
 *
 * @param  hw 外围寄存器的起始地址。
 */
FORCE_INLINE_ATTR uint32_t uart_ll_get_neg_pulse_cnt(uart_dev_t *hw)
{
    return hw->negpulse.negedge_min_cnt;
}

/**
 * @brief  获取高脉冲最小计数。
 *
 * @param  hw 外围寄存器的起始地址。
 */
FORCE_INLINE_ATTR uint32_t uart_ll_get_high_pulse_cnt(uart_dev_t *hw)
{
    return hw->highpulse.highpulse_min_cnt;
}

/**
 * @brief  获取低脉冲最小计数。
 *
 * @param  hw 外围寄存器的起始地址。
 */
FORCE_INLINE_ATTR uint32_t uart_ll_get_low_pulse_cnt(uart_dev_t *hw)
{
    return hw->lowpulse.lowpulse_min_cnt;
}

/**
 * @brief  强制UART xoff。
 *
 * @param  uart_num UART端口号，最大端口号为（UART_NUM_max-1）。
 *
 * @return 没有一个
 */
static inline void uart_ll_force_xoff(uart_port_t uart_num)
{
    REG_CLR_BIT(UART_FLOW_CONF_REG(uart_num), UART_FORCE_XON);
    REG_SET_BIT(UART_FLOW_CONF_REG(uart_num), UART_SW_FLOW_CON_EN | UART_FORCE_XOFF);
}

/**
 * @brief  强制UART xon。
 *
 * @param  uart_num UART端口号，最大端口号为（UART_NUM_max-1）。
 *
 * @return 没有一个
 */
FORCE_INLINE_ATTR void uart_ll_force_xon(uart_port_t uart_num)
{
    REG_CLR_BIT(UART_FLOW_CONF_REG(uart_num), UART_FORCE_XOFF);
    REG_SET_BIT(UART_FLOW_CONF_REG(uart_num), UART_FORCE_XON);
    REG_CLR_BIT(UART_FLOW_CONF_REG(uart_num), UART_SW_FLOW_CON_EN | UART_FORCE_XON);
}

/**
 * @brief  获取UART有限状态机状态。
 *
 * @param  uart_num UART端口号，最大端口号为（UART_NUM_max-1）。
 *
 * @return UART模块FSM状态。
 */
FORCE_INLINE_ATTR uint32_t uart_ll_get_fsm_status(uart_port_t uart_num)
{
    return REG_GET_FIELD(UART_FSM_STATUS_REG(uart_num), UART_ST_UTX_OUT);
}

#ifdef __cplusplus
}
#endif

