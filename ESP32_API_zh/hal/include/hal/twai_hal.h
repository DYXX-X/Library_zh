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

#include <stddef.h>
#include <stdbool.h>
#include "sdkconfig.h"
#include "hal/twai_types.h"
#include "hal/twai_ll.h"

/* -------------------------定义和Typedefs---------------------------*/

#define TWAI_HAL_SET_BITS(var, flag)            ((var) |= (flag))
#define TWAI_HAL_CLEAR_BITS(var, flag)          ((var) &= ~(flag))

//HAL状态标志
#define TWAI_HAL_STATE_FLAG_RUNNING             (1 << 0)    //控制器处于激活状态（未处于重置模式）
#define TWAI_HAL_STATE_FLAG_RECOVERING          (1 << 1)    //公交车正在恢复
#define TWAI_HAL_STATE_FLAG_ERR_WARN            (1 << 2)    //TEC或REC>=错误警告限值
#define TWAI_HAL_STATE_FLAG_ERR_PASSIVE         (1 << 3)    //TEC或REC>=128
#define TWAI_HAL_STATE_FLAG_BUS_OFF             (1 << 4)    //由于TEC>=256，总线关闭
#define TWAI_HAL_STATE_FLAG_TX_BUFF_OCCUPIED    (1 << 5)    //传输缓冲区被占用
#if defined(CONFIG_TWAI_ERRATA_FIX_RX_FRAME_INVALID) || defined(CONFIG_TWAI_ERRATA_FIX_RX_FIFO_CORRUPT)
#define TWAI_HAL_STATE_FLAG_TX_NEED_RETRY       (1 << 7)    //由于错误的解决方案，TX需要重新启动
#endif

//中断事件
#define TWAI_HAL_EVENT_BUS_OFF                  (1 << 0)
#define TWAI_HAL_EVENT_BUS_RECOV_CPLT           (1 << 1)
#define TWAI_HAL_EVENT_BUS_RECOV_PROGRESS       (1 << 2)
#define TWAI_HAL_EVENT_ABOVE_EWL                (1 << 3)
#define TWAI_HAL_EVENT_BELOW_EWL                (1 << 4)
#define TWAI_HAL_EVENT_ERROR_PASSIVE            (1 << 5)
#define TWAI_HAL_EVENT_ERROR_ACTIVE             (1 << 6)
#define TWAI_HAL_EVENT_BUS_ERR                  (1 << 7)
#define TWAI_HAL_EVENT_ARB_LOST                 (1 << 8)
#define TWAI_HAL_EVENT_RX_BUFF_FRAME            (1 << 9)
#define TWAI_HAL_EVENT_TX_BUFF_FREE             (1 << 10)
#if defined(CONFIG_TWAI_ERRATA_FIX_RX_FRAME_INVALID) || defined(CONFIG_TWAI_ERRATA_FIX_RX_FIFO_CORRUPT)
#define TWAI_HAL_EVENT_NEED_PERIPH_RESET        (1 << 11)
#endif

typedef twai_ll_frame_buffer_t twai_hal_frame_t;

typedef struct {
    twai_dev_t *dev;
    uint32_t state_flags;
#if defined(CONFIG_TWAI_ERRATA_FIX_RX_FRAME_INVALID) || defined(CONFIG_TWAI_ERRATA_FIX_RX_FIFO_CORRUPT)
    twai_hal_frame_t tx_frame_save;
    twai_ll_reg_save_t reg_save;
    uint8_t rx_msg_cnt_save;
#endif
} twai_hal_context_t;

/* ----------------------------初始化和配置---------------------------*/

/**
 * @brief 初始化TWAI外围设备和HAL上下文
 *
 * 设置HAL上下文，将TWAI外设置于重置模式，然后使用默认值设置一些寄存器。
 *
 * @param hal_ctx HAL层的上下文
 * @return 如果成功初始化，则为True，否则为false。
 */
bool twai_hal_init(twai_hal_context_t *hal_ctx);

/**
 * @brief 取消TWAI外围设备和HAL上下文的初始化
 *
 * 清除任何未处理的中断并取消设置HAL上下文
 *
 * @param hal_ctx HAL层的上下文
 */
void twai_hal_deinit(twai_hal_context_t *hal_ctx);

/**
 * @brief 配置TWAI外围设备
 *
 * @param hal_ctx HAL层的上下文
 * @param t_config 指向定时配置结构的指针
 * @param f_config 指向筛选器配置结构的指针
 * @param intr_mask 要启用的中断掩码
 * @param clkout_divider CLKOUT的时钟分频器值。设置为-1以禁用CLKOUT
 */
void twai_hal_configure(twai_hal_context_t *hal_ctx, const twai_timing_config_t *t_config, const twai_filter_config_t *f_config, uint32_t intr_mask, uint32_t clkout_divider);

/* --------------------------------行动------------------------------*/

/**
 * @brief 启动TWAI外围设备
 *
 * 通过配置TWAI外设的操作模式，然后退出重置模式，启动TWAI外设，以便TWAI外设可以参与总线活动。
 *
 * @param hal_ctx HAL层的上下文
 * @param mode 操作模式
 */
void twai_hal_start(twai_hal_context_t *hal_ctx, twai_mode_t mode);

/**
 * @brief 停止TWAI外围设备
 *
 * 通过进入重置模式停止任何总线活动，然后将操作模式设置为“仅侦听”，使REC冻结，从而停止TWAI外围设备。
 *
 * @param hal_ctx HAL层的上下文
 */
void twai_hal_stop(twai_hal_context_t *hal_ctx);

/**
 * @brief 启动总线恢复
 *
 * @param hal_ctx HAL层的上下文
 */
static inline void twai_hal_start_bus_recovery(twai_hal_context_t *hal_ctx)
{
    TWAI_HAL_SET_BITS(hal_ctx->state_flags, TWAI_HAL_STATE_FLAG_RECOVERING);
    twai_ll_exit_reset_mode(hal_ctx->dev);
}

/**
 * @brief 获取TX错误计数器的值
 *
 * @param hal_ctx HAL层的上下文
 * @return TX错误计数器值
 */
static inline uint32_t twai_hal_get_tec(twai_hal_context_t *hal_ctx)
{
    return twai_ll_get_tec((hal_ctx)->dev);
}

/**
 * @brief 获取RX错误计数器的值
 *
 * @param hal_ctx HAL层的上下文
 * @return RX错误计数器值
 */
static inline uint32_t twai_hal_get_rec(twai_hal_context_t *hal_ctx)
{
    return twai_ll_get_rec((hal_ctx)->dev);
}

/**
 * @brief 获取RX消息计数寄存器
 *
 * @param hal_ctx HAL层的上下文
 * @return RX消息计数
 */
static inline uint32_t twai_hal_get_rx_msg_count(twai_hal_context_t *hal_ctx)
{
    return twai_ll_get_rx_msg_count((hal_ctx)->dev);
}

/**
 * @brief 检查最后传输的帧是否成功
 *
 * @param hal_ctx HAL层的上下文
 * @return 如果成功，则为True
 */
static inline bool twai_hal_check_last_tx_successful(twai_hal_context_t *hal_ctx)
{
    return twai_ll_is_last_tx_successful((hal_ctx)->dev);
}

/**
 * @brief 检查是否设置了某些HAL状态标志
 *
 * HAL将通过一组标志保持控制器状态的记录。这些标志在各种HAL函数调用中自动维护（即设置和重置）。此函数检查当前是否设置了某些标志。
 *
 * @param hal_ctx HAL层的上下文
 * @param check_flags 要检查的标志位掩码
 * @return 如果设置了check_flags中的一个或多个标志，则为True
 */

static inline bool twai_hal_check_state_flags(twai_hal_context_t *hal_ctx, uint32_t check_flags)
{
    return hal_ctx->state_flags & check_flags;
}

/* -----------------------------事件处理---------------------------*/

/**
 * @brief 获取触发中断的事件的位掩码
 *
 * 应在中断开始时调用此函数。此功能将执行以下操作：
 * -读取并清除中断寄存器
 * -计算触发中断的事件
 * -响应低延迟中断事件
 *      -总线关闭：更改为LOM以冻结TEC/REC。勘误表1修复
 *      -恢复完成：进入重置模式
 *      -清除ECC和ALC，以便重新配置其中断
 * -根据发生的中断更新HAL状态标志。
 * -对于ESP32，检查错误情况。如果需要硬件重置，此功能将设置TWAI_HAL_EVENT_NEED_PERIPH_reset事件。
 *
 * @param hal_ctx HAL层的上下文
 * @return 已发生事件的位掩码
 */
uint32_t twai_hal_get_events(twai_hal_context_t *hal_ctx);

/* -------------------------------发送和接收------------------------------*/

/**
 * @brief 设置TWAI帧格式
 *
 * 此函数采用TWAI消息结构（包含ID、DLC、数据和标志），并对其进行格式化以匹配TX帧缓冲区的布局。
 *
 * @param message 指向TWAI消息的指针
 * @param frame 指向空框架结构的指针
 */
static inline void twai_hal_format_frame(const twai_message_t *message, twai_hal_frame_t *frame)
{
    //直接调用ll函数
    twai_ll_format_frame_buffer(message->identifier, message->data_length_code, message->data,
                               message->flags, frame);
}

/**
 * @brief 分析TWAI帧
 *
 * 此函数获取TWAI帧（格式为RX帧缓冲区）并将其解析为TWAI消息（包含ID、DLC、数据和标志）。
 *
 * @param frame 指向框架结构的指针
 * @param message 指向空消息结构的指针
 */
static inline void twai_hal_parse_frame(twai_hal_frame_t *frame, twai_message_t *message)
{
    //直接调用ll函数
    twai_ll_prase_frame_buffer(frame, &message->identifier, &message->data_length_code,
                              message->data, &message->flags);
}

/**
 * @brief 将帧复制到TX缓冲区并发送
 *
 * 此功能将格式化的TX帧复制到TX缓冲器中，并通过在命令寄存器中设置正确的传输命令（例如，正常、单次发射、自RX）进行传输。
 *
 * @param hal_ctx HAL层的上下文
 * @param tx_frame 指向包含格式化TX帧的结构的指针
 */
void twai_hal_set_tx_buffer_and_transmit(twai_hal_context_t *hal_ctx, twai_hal_frame_t *tx_frame);

/**
 * @brief 从RX缓冲区复制帧并释放
 *
 * 此函数从RX缓冲区复制一帧，然后释放缓冲区（以便加载RX FIFO中的下一帧）。在以下条件下返回False：
 * -在ESP32S2上，如果RX缓冲区指向超限帧，则返回false
 * -在ESP32上，如果RX缓冲区指向RX FIFO中的第一个超限帧，则返回false
 *
 * @param hal_ctx HAL层的上下文
 * @param rx_frame 指向存储RX帧的结构的指针
 * @return 如果复制并释放了有效帧，则为True。如果超限，则为False。
 */
static inline bool twai_hal_read_rx_buffer_and_clear(twai_hal_context_t *hal_ctx, twai_hal_frame_t *rx_frame)
{
#ifdef SOC_TWAI_SUPPORTS_RX_STATUS
    if (twai_ll_get_status(hal_ctx->dev) & TWAI_LL_STATUS_MS) {
        //释放此特定超限帧的缓冲区
        twai_ll_set_cmd_release_rx_buffer(hal_ctx->dev);
        return false;
    }
#else
    if (twai_ll_get_status(hal_ctx->dev) & TWAI_LL_STATUS_DOS) {
        //无需释放RX缓冲区，因为我们稍后将连续释放所有RX帧
        return false;
    }
#endif
    twai_ll_get_rx_buffer(hal_ctx->dev, rx_frame);
    twai_ll_set_cmd_release_rx_buffer(hal_ctx->dev);
    return true;
}

#ifndef SOC_TWAI_SUPPORTS_RX_STATUS
/**
 * @brief 清除超限帧的RX FIFO
 *
 * 此功能将清除超限帧的RX FIFO。调用此函数后，RX消息计数将返回0。
 *
 * @param hal_ctx HAL层的上下文
 * @return 从RX FIFO清除的超限消息数
 */
static inline uint32_t twai_hal_clear_rx_fifo_overrun(twai_hal_context_t *hal_ctx)
{
    uint32_t msg_cnt = 0;
    //注意：需要继续轮询rx消息计数器，以防在清除时另一条消息到达
    while (twai_ll_get_rx_msg_count(hal_ctx->dev) > 0) {
        twai_ll_set_cmd_release_rx_buffer(hal_ctx->dev);
        msg_cnt++;
    }
    //设置清除数据超限命令以清除数据超限状态位
    twai_ll_set_cmd_clear_data_overrun(hal_ctx->dev);

    return msg_cnt;
}
#endif  //SOC_TWAI_SUPPORTS_RX_STATUS

/* ---------------------------勘误表解决方法---------------------------*/

#if defined(CONFIG_TWAI_ERRATA_FIX_RX_FRAME_INVALID) || defined(CONFIG_TWAI_ERRATA_FIX_RX_FIFO_CORRUPT)
/**
 * @brief 为硬件重置准备外围设备
 *
 * 某些硬件错误将需要重置外围设备。如果twai_hal_get_events（）返回twai_hal_EVENT_NEED_PERIPH_RESET事件，则应调用此函数。重置准备包括以下内容：
 * -检查重置是否会取消TX。如果是，请标记重置后需要重试该消息
 * -保存由于此重置而丢失的RX消息数
 * -进入重置模式以停止任何外围设备接收任何总线活动
 * -存储外围设备的regsiter状态
 *
 * @param hal_ctx HAL层的上下文
 */
void twai_hal_prepare_for_reset(twai_hal_context_t *hal_ctx);

/**
 * @brief 硬件复位后恢复外围设备
 *
 * 应在调用twai_hal_prepare_for_reset（）并执行HW重置后调用此函数。从硬件重置中恢复外围设备包括以下步骤：
 * -恢复以前保存的寄存器状态
 * -退出重置模式以允许接收总线活动
 * -重试被硬件重置取消的任何发送消息
 *
 * @param hal_ctx HAL层的上下文
 */
void twai_hal_recover_from_reset(twai_hal_context_t *hal_ctx);

/**
 * @brief 获取因硬件重置而丢失的RX消息数
 *
 * @note twai_hal_prepare_for_reset（）期间保存的丢失RX消息数
 *
 * @param hal_ctx HAL层的上下文
 * @return uint32_t由于硬件重置而丢失的RX消息数
 */
static inline uint32_t twai_hal_get_reset_lost_rx_cnt(twai_hal_context_t *hal_ctx)
{
    return hal_ctx->rx_msg_cnt_save;
}
#endif  //已定义（CONFIG_TWAI_ERRORTA_FIX_RX_FRAME_INVALID）||已定义（ONFIG_TWAI_ERRORTA_FIX _RX_FIFO_CORRUPT）

#ifdef __cplusplus
}
#endif

