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

// UHCI寄存器操作的LL层。
// 注意，该层中的大多数寄存器操作都是非原子操作。


#pragma once
#include <stdio.h>
#include "hal/uhci_types.h"
#include "soc/uhci_struct.h"

#ifdef __cplusplus
extern "C" {
#endif

#define UHCI_LL_GET_HW(num) (((num) == 0) ? (&UHCI0) : (NULL))

typedef enum {
    UHCI_RX_BREAK_CHR_EOF = 0x1,
    UHCI_RX_IDLE_EOF      = 0x2,
    UHCI_RX_LEN_EOF       = 0x4,
    UHCI_RX_EOF_MAX       = 0x7,
} uhci_rxeof_cfg_t;

static inline void uhci_ll_init(uhci_dev_t *hw)
{
    typeof(hw->conf0) conf0_reg;
    hw->conf0.clk_en = 1;
    conf0_reg.val = 0;
    conf0_reg.clk_en = 1;
    hw->conf0.val = conf0_reg.val;
    hw->conf1.val = 0;
}

static inline void uhci_ll_attach_uart_port(uhci_dev_t *hw, int uart_num)
{
    hw->conf0.uart0_ce = (uart_num == 0)? 1: 0;
    hw->conf0.uart1_ce = (uart_num == 1)? 1: 0;
    hw->conf0.uart2_ce = (uart_num == 2)? 1: 0;
}

static inline void uhci_ll_set_seper_chr(uhci_dev_t *hw, uhci_seper_chr_t *seper_char)
{
    if (seper_char->sub_chr_en) {
        typeof(hw->esc_conf0) esc_conf0_reg = hw->esc_conf0;
        esc_conf0_reg.seper_char = seper_char->seper_chr;
        esc_conf0_reg.seper_esc_char0 = seper_char->sub_chr1;
        esc_conf0_reg.seper_esc_char1 = seper_char->sub_chr2;
        hw->esc_conf0.val = esc_conf0_reg.val;
        hw->escape_conf.tx_c0_esc_en = 1;
        hw->escape_conf.rx_c0_esc_en = 1;
    } else {
        hw->escape_conf.tx_c0_esc_en = 0;
        hw->escape_conf.rx_c0_esc_en = 0;
    }
}

static inline void uhci_ll_get_seper_chr(uhci_dev_t *hw, uhci_seper_chr_t *seper_chr)
{
    (void)hw;
    (void)seper_chr;
}

static inline void uhci_ll_set_swflow_ctrl_sub_chr(uhci_dev_t *hw, uhci_swflow_ctrl_sub_chr_t *sub_ctr)
{
    typeof(hw->escape_conf) escape_conf_reg = hw->escape_conf;
    if (sub_ctr->flow_en == 1) {
        typeof(hw->esc_conf2) esc_conf2_reg = hw->esc_conf2;
        typeof(hw->esc_conf3) esc_conf3_reg = hw->esc_conf3;
        esc_conf2_reg.seq1 = sub_ctr->xon_chr;
        esc_conf2_reg.seq1_char0 = sub_ctr->xon_sub1;
        esc_conf2_reg.seq1_char1 = sub_ctr->xon_sub2;
        esc_conf3_reg.seq2 = sub_ctr->xoff_chr;
        esc_conf3_reg.seq2_char0 = sub_ctr->xoff_sub1;
        esc_conf3_reg.seq2_char1 = sub_ctr->xoff_sub2;
        escape_conf_reg.tx_11_esc_en = 1;
        escape_conf_reg.tx_13_esc_en = 1;
        escape_conf_reg.rx_11_esc_en = 1;
        escape_conf_reg.rx_13_esc_en = 1;
        hw->esc_conf2.val = esc_conf2_reg.val;
        hw->esc_conf3.val = esc_conf3_reg.val;
    } else {
        escape_conf_reg.tx_11_esc_en = 0;
        escape_conf_reg.tx_13_esc_en = 0;
        escape_conf_reg.rx_11_esc_en = 0;
        escape_conf_reg.rx_13_esc_en = 0;
    }
    hw->escape_conf.val = escape_conf_reg.val;
}

static inline void uhci_ll_enable_intr(uhci_dev_t *hw, uint32_t intr_mask)
{
    hw->int_ena.val |= intr_mask;
}

static inline void uhci_ll_disable_intr(uhci_dev_t *hw, uint32_t intr_mask)
{
    hw->int_ena.val &= (~intr_mask);
}

static inline void uhci_ll_clear_intr(uhci_dev_t *hw, uint32_t intr_mask)
{
    hw->int_clr.val = intr_mask;
}

static inline uint32_t uhci_ll_get_intr(uhci_dev_t *hw)
{
    return hw->int_st.val;
}


static inline void uhci_ll_set_eof_mode(uhci_dev_t *hw, uint32_t eof_mode)
{
    if (eof_mode & UHCI_RX_BREAK_CHR_EOF) {
        hw->conf0.uart_rx_brk_eof_en = 1;
    }
    if (eof_mode & UHCI_RX_IDLE_EOF) {
        hw->conf0.uart_idle_eof_en = 1;
    }
    if (eof_mode & UHCI_RX_LEN_EOF) {
        hw->conf0.len_eof_en = 1;
    }
}

#ifdef __cplusplus
}
#endif
