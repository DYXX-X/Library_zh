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
#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include "soc/soc_caps.h"
#include "soc/rmt_struct.h"

/**
 * @brief RMT驱动程序的HAL上下文类型
 *
 */
typedef struct {
    rmt_dev_t *regs;     /*!< RMT寄存器基址*/
    rmt_mem_t *mem;      /*!< RMT内存基地址*/
} rmt_hal_context_t;

#define RMT_MEM_OWNER_SW (0) /*!< RMT内存所有权属于软件方*/
#define RMT_MEM_OWNER_HW (1) /*!< RMT内存所有权属于硬件方*/

/**
 * @brief 初始化RMT HAL驱动程序
 *
 * @param hal: RMT HAL上下文
 */
void rmt_hal_init(rmt_hal_context_t *hal);

/**
 * @brief 重置RMT TX信道
 *
 * @param hal: RMT HAL上下文
 * @param channel: RMT通道编号
 */
void rmt_hal_tx_channel_reset(rmt_hal_context_t *hal, uint32_t channel);

/**
 * @brief 重置RMT TX信道
 *
 * @param hal: RMT HAL上下文
 * @param channel: RMT通道编号
 */
void rmt_hal_rx_channel_reset(rmt_hal_context_t *hal, uint32_t channel);

/**
 * @brief 设置RMT信道的计数器时钟
 *
 * @param hal: RMT HAL上下文
 * @param channel: RMT通道编号
 * @param base_clk_hz: RMT内部信道的基本时钟（计数器时钟将从中分频）
 * @param counter_clk_hz: 目标计数器时钟
 */
void rmt_hal_tx_set_channel_clock(rmt_hal_context_t *hal, uint32_t channel, uint32_t base_clk_hz, uint32_t counter_clk_hz);

/**
 * @brief 设置RMT信道的载波时钟
 *
 * @param hal: RMT HAL上下文
 * @param channel: RMT通道编号
 * @param base_clk_hz: RMT载波生成的基本时钟（载波时钟将从中分频）
 * @param carrier_clk_hz: 目标载波时钟
 * @param carrier_clk_duty: 载波时钟占空比
 */
void rmt_hal_set_carrier_clock(rmt_hal_context_t *hal, uint32_t channel, uint32_t base_clk_hz, uint32_t carrier_clk_hz, float carrier_clk_duty);

/**
 * @brief 设置RMT接收信道的滤波器阈值
 *
 * @param hal: RMT HAL上下文
 * @param channel: RMT通道编号
 * @param base_clk_hz: RMT接收滤波器的基准时钟
 * @param thres_us: RMT接收滤波器的阈值，以美国为单位
 */
void rmt_hal_set_rx_filter_thres(rmt_hal_context_t *hal, uint32_t channel, uint32_t base_clk_hz, uint32_t thres_us);

/**
 * @brief 设置RMT接收信道的空闲阈值
 *
 * @param hal: RMT HAL上下文
 * @param channel: RMT通道编号
 * @param base_clk_hz: RMT接收信道的基本时钟
 * @param thres_us: RMT接收信道的空闲阈值
 */
void rmt_hal_set_rx_idle_thres(rmt_hal_context_t *hal, uint32_t channel, uint32_t base_clk_hz, uint32_t thres_us);

/**
 * @brief 从RMT信道接收帧
 *
 * @param hal: RMT HAL上下文
 * @param channel: RMT通道编号
 * @param buf: 用于存储接收到的RMT帧的缓冲器
 * @return 收到的项目数
 */
uint32_t rmt_hal_receive(rmt_hal_context_t *hal, uint32_t channel, rmt_item32_t *buf);

#ifdef __cplusplus
}
#endif

