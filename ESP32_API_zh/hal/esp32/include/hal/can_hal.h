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
 * 注意：hal不是公共api，不要在应用程序代码中使用。请参阅自述文件。在hal/include/hal/readme.md中的md
 ******************************************************************************/

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#warning hal/can_hal.h is deprecated, please use hal/twai_hal.h instead

#include "hal/twai_hal.h"
#include "hal/can_types.h"

/* -------------------------定义和Typedefs---------------------------*/

//错误激活中断相关
#define CAN_HAL_EVENT_BUS_OFF               TWAI_HAL_EVENT_BUS_OFF
#define CAN_HAL_EVENT_BUS_RECOV_CPLT        TWAI_HAL_EVENT_BUS_RECOV_CPLT
#define CAN_HAL_EVENT_BUS_RECOV_PROGRESS    TWAI_HAL_EVENT_BUS_RECOV_PROGRESS
#define CAN_HAL_EVENT_ABOVE_EWL             TWAI_HAL_EVENT_ABOVE_EWL
#define CAN_HAL_EVENT_BELOW_EWL             TWAI_HAL_EVENT_BELOW_EWL
#define CAN_HAL_EVENT_ERROR_PASSIVE         TWAI_HAL_EVENT_ERROR_PASSIVE
#define CAN_HAL_EVENT_ERROR_ACTIVE          TWAI_HAL_EVENT_ERROR_ACTIVE
#define CAN_HAL_EVENT_BUS_ERR               TWAI_HAL_EVENT_BUS_ERR
#define CAN_HAL_EVENT_ARB_LOST              TWAI_HAL_EVENT_ARB_LOST
#define CAN_HAL_EVENT_RX_BUFF_FRAME         TWAI_HAL_EVENT_RX_BUFF_FRAME
#define CAN_HAL_EVENT_TX_BUFF_FREE          TWAI_HAL_EVENT_TX_BUFF_FREE

typedef twai_hal_context_t can_hal_context_t;

typedef twai_hal_frame_t can_hal_frame_t;

/* ----------------------------初始化和配置---------------------------*/

static inline bool can_hal_init(can_hal_context_t *hal_ctx){
    return twai_hal_init(hal_ctx);
}

static inline void can_hal_deinit(can_hal_context_t *hal_ctx)
{
    twai_hal_deinit(hal_ctx);
}

static inline void can_hal_configure(can_hal_context_t *hal_ctx, const can_timing_config_t *t_config, const can_filter_config_t *f_config, uint32_t intr_mask, uint32_t clkout_divider)
{
    twai_hal_configure(hal_ctx, t_config, f_config, intr_mask, clkout_divider);
}

/* --------------------------------行动------------------------------*/

static inline void can_hal_start(can_hal_context_t *hal_ctx, can_mode_t mode)
{
    twai_hal_start(hal_ctx, mode);
}

static inline void can_hal_stop(can_hal_context_t *hal_ctx)
{
    twai_hal_stop(hal_ctx);
}

static inline void can_hal_start_bus_recovery(can_hal_context_t *hal_ctx)
{
    twai_hal_start_bus_recovery(hal_ctx);
}

static inline uint32_t can_hal_get_tec(can_hal_context_t *hal_ctx)
{
    return twai_hal_get_tec(hal_ctx);
}

static inline uint32_t can_hal_get_rec(can_hal_context_t *hal_ctx)
{
    return twai_hal_get_rec(hal_ctx);
}

static inline uint32_t can_hal_get_rx_msg_count(can_hal_context_t *hal_ctx)
{
    return twai_hal_get_rx_msg_count(hal_ctx);
}

static inline bool can_hal_check_last_tx_successful(can_hal_context_t *hal_ctx)
{
    return twai_hal_check_last_tx_successful(hal_ctx);
}

static inline bool can_hal_check_state_flags(can_hal_context_t *hal_ctx, uint32_t check_flags)
{
    return twai_hal_check_state_flags(hal_ctx, check_flags);
}

/* -----------------------------事件处理---------------------------*/

static inline uint32_t can_hal_decode_interrupt_events(can_hal_context_t *hal_ctx) {
    return twai_hal_decode_interrupt(hal_ctx);
}

/* -------------------------------TX和RX--------------------------------*/

static inline void can_hal_format_frame(const can_message_t *message, can_hal_frame_t *frame)
{
    twai_hal_format_frame(message, frame);
}

static inline void can_hal_parse_frame(can_hal_frame_t *frame, can_message_t *message)
{
    twai_hal_parse_frame(frame, message);
}

static inline void can_hal_set_tx_buffer_and_transmit(can_hal_context_t *hal_ctx, can_hal_frame_t *tx_frame)
{
    twai_hal_set_tx_buffer_and_transmit(hal_ctx, tx_frame);
}

static inline void can_hal_read_rx_buffer_and_clear(can_hal_context_t *hal_ctx, can_hal_frame_t *rx_frame)
{
    twai_hal_read_rx_buffer_and_clear(hal_ctx, rx_frame);
}

#ifdef __cplusplus
}
#endif

