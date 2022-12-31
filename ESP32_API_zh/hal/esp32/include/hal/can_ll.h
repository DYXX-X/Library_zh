// 版权所有2015-2019 Espressif Systems（上海）私人有限公司
//
// 根据Apache许可证2.0版（“许可证”）获得许可；
// 除非符合许可证，否则不得使用此文件。
// 您可以在以下地址获取许可证副本：

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

// CAN的低层

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#warning hal/can_ll.h is deprecated, please use hal/twai_ll.h instead

#include "hal/twai_ll.h"
#include "hal/can_types.h"
#include "soc/can_periph.h"

/* -------------------------定义和Typedefs---------------------------*/

#define CAN_LL_STATUS_RBS       TWAI_LL_STATUS_RBS
#define CAN_LL_STATUS_DOS       TWAI_LL_STATUS_DOS
#define CAN_LL_STATUS_TBS       TWAI_LL_STATUS_TBS
#define CAN_LL_STATUS_TCS       TWAI_LL_STATUS_TCS
#define CAN_LL_STATUS_RS        TWAI_LL_STATUS_RS
#define CAN_LL_STATUS_TS        TWAI_LL_STATUS_TS
#define CAN_LL_STATUS_ES        TWAI_LL_STATUS_ES
#define CAN_LL_STATUS_BS        TWAI_LL_STATUS_BS

#define CAN_LL_INTR_RI          TWAI_LL_INTR_RI
#define CAN_LL_INTR_TI          TWAI_LL_INTR_TI
#define CAN_LL_INTR_EI          TWAI_LL_INTR_EI
#define CAN_LL_INTR_EPI         TWAI_LL_INTR_EPI
#define CAN_LL_INTR_ALI         TWAI_LL_INTR_ALI
#define CAN_LL_INTR_BEI         TWAI_LL_INTR_BEI

typedef twai_ll_frame_buffer_t can_ll_frame_buffer_t;

/* ----------------------------模式寄存器------------------------------*/

static inline void can_ll_enter_reset_mode(can_dev_t *hw)
{
    twai_ll_enter_reset_mode(hw);
}

static inline void can_ll_exit_reset_mode(can_dev_t *hw)
{
    twai_ll_exit_reset_mode(hw);
}

static inline bool can_ll_is_in_reset_mode(can_dev_t *hw)
{
    return twai_ll_is_in_reset_mode(hw);
}

static inline void can_ll_set_mode(can_dev_t *hw, can_mode_t mode)
{
    twai_ll_set_mode(hw, mode);
}

/* ---------------------------命令寄存器---------------------------*/

static inline void can_ll_set_cmd_tx(can_dev_t *hw)
{
    twai_ll_set_cmd_tx(hw);
}

static inline void can_ll_set_cmd_tx_single_shot(can_dev_t *hw)
{
    twai_ll_set_cmd_tx_single_shot(hw);
}

static inline void can_ll_set_cmd_abort_tx(can_dev_t *hw)
{
    twai_ll_set_cmd_abort_tx(hw);
}

static inline void can_ll_set_cmd_release_rx_buffer(can_dev_t *hw)
{
    twai_ll_set_cmd_release_rx_buffer(hw);
}

static inline void can_ll_set_cmd_clear_data_overrun(can_dev_t *hw)
{
    twai_ll_set_cmd_clear_data_overrun(hw);
}

static inline void can_ll_set_cmd_self_rx_request(can_dev_t *hw)
{
    twai_ll_set_cmd_self_rx_request(hw);
}

static inline void can_ll_set_cmd_self_rx_single_shot(can_dev_t *hw)
{
    twai_ll_set_cmd_self_rx_single_shot(hw);
}

/* ---------------------------状态寄存器------------------------------*/

static inline uint32_t can_ll_get_status(can_dev_t *hw)
{
    return twai_ll_get_status(hw);
}

static inline bool can_ll_is_fifo_overrun(can_dev_t *hw)
{
    return twai_ll_is_fifo_overrun(hw);
}

static inline bool can_ll_is_last_tx_successful(can_dev_t *hw)
{
    return twai_ll_is_last_tx_successful(hw);
}

/* --------------------------中断寄存器-------------------------*/

static inline uint32_t can_ll_get_and_clear_intrs(can_dev_t *hw)
{
    return twai_ll_get_and_clear_intrs(hw);
}

/* -----------------------中断启用寄存器-----------------------*/

static inline void can_ll_set_enabled_intrs(can_dev_t *hw, uint32_t intr_mask)
{
    twai_ll_set_enabled_intrs(hw, intr_mask);
}

/* ------------------------总线定时寄存器---------------------------*/

static inline void can_ll_set_bus_timing(can_dev_t *hw, uint32_t brp, uint32_t sjw, uint32_t tseg1, uint32_t tseg2, bool triple_sampling)
{
    twai_ll_set_bus_timing(hw, brp, sjw, tseg1, tseg2, triple_sampling);
}

/* -----------------------------ALC寄存器------------------------------*/

static inline void can_ll_clear_arb_lost_cap(can_dev_t *hw)
{
    twai_ll_clear_arb_lost_cap(hw);
}

/* -----------------------------ECC寄存器------------------------------*/

static inline void can_ll_clear_err_code_cap(can_dev_t *hw)
{
    twai_ll_clear_err_code_cap(hw);
}

/* -----------------------------EWL寄存器------------------------------*/

static inline void can_ll_set_err_warn_lim(can_dev_t *hw, uint32_t ewl)
{
    twai_ll_set_err_warn_lim(hw, ewl);
}

static inline uint32_t can_ll_get_err_warn_lim(can_dev_t *hw)
{
    return twai_ll_get_err_warn_lim(hw);
}

/* ------------------------RX错误计数寄存器-----------------------*/

static inline uint32_t can_ll_get_rec(can_dev_t *hw)
{
    return twai_ll_get_rec(hw);
}

static inline void can_ll_set_rec(can_dev_t *hw, uint32_t rec)
{
    twai_ll_set_rec(hw, rec);
}

/* ------------------------TX错误计数寄存器-----------------------*/

static inline uint32_t can_ll_get_tec(can_dev_t *hw)
{
    return twai_ll_get_tec(hw);
}

static inline void can_ll_set_tec(can_dev_t *hw, uint32_t tec)
{
    twai_ll_set_tec(hw, tec);
}

/* ----------------------接受过滤器寄存器------------------------*/

static inline void can_ll_set_acc_filter(can_dev_t* hw, uint32_t code, uint32_t mask, bool single_filter)
{
    twai_ll_set_acc_filter(hw, code, mask, single_filter);
}

/* -------------------------TX/RX缓冲寄存器---------------------------*/

static inline void can_ll_set_tx_buffer(can_dev_t *hw, can_ll_frame_buffer_t *tx_frame)
{
    twai_ll_set_tx_buffer(hw, tx_frame);
}

static inline void can_ll_get_rx_buffer(can_dev_t *hw, can_ll_frame_buffer_t *rx_frame)
{
    twai_ll_get_rx_buffer(hw, rx_frame);
}

static inline void can_ll_format_frame_buffer(uint32_t id, uint8_t dlc, const uint8_t *data,
                                              uint32_t flags, can_ll_frame_buffer_t *tx_frame)
{
    twai_ll_format_frame_buffer(id, dlc, data, flags, tx_frame);
}

static inline void can_ll_prase_frame_buffer(can_ll_frame_buffer_t *rx_frame, uint32_t *id, uint8_t *dlc,
                                             uint8_t *data, uint32_t *flags)
{
    twai_ll_prase_frame_buffer(rx_frame, id, dlc, data, flags);
}

/* -----------------------RX消息计数寄存器-----------------------*/

static inline uint32_t can_ll_get_rx_msg_count(can_dev_t *hw)
{
    return twai_ll_get_rx_msg_count(hw);
}

/* -------------------------时钟分频器寄存器-------------------------*/

static inline void can_ll_set_clkout(can_dev_t *hw, uint32_t divider)
{
    twai_ll_set_clkout(hw, divider);
}

static inline void can_ll_enable_extended_reg_layout(can_dev_t *hw)
{
    twai_ll_enable_extended_reg_layout(hw);
}

#ifdef __cplusplus
}
#endif

