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

#pragma once

#include "soc/soc_caps.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
* @brief RMT通道ID
*
*/
typedef enum {
    RMT_CHANNEL_0,  /*!< RMT通道编号0*/
    RMT_CHANNEL_1,  /*!< RMT通道编号1*/
    RMT_CHANNEL_2,  /*!< RMT通道编号2*/
    RMT_CHANNEL_3,  /*!< RMT通道编号3*/
#if SOC_RMT_CHANNELS_PER_GROUP > 4
    RMT_CHANNEL_4,  /*!< RMT通道编号4*/
    RMT_CHANNEL_5,  /*!< RMT通道编号5*/
    RMT_CHANNEL_6,  /*!< RMT通道编号6*/
    RMT_CHANNEL_7,  /*!< RMT通道编号7*/
#endif
    RMT_CHANNEL_MAX /*!< RMT通道数量*/
} rmt_channel_t;

/**
 * @brief RMT内部内存所有者
 *
 */
typedef enum {
    RMT_MEM_OWNER_TX, /*!< RMT RX模式，RMT发射机拥有存储块*/
    RMT_MEM_OWNER_RX, /*!< RMT RX模式，RMT接收机拥有内存块*/
    RMT_MEM_OWNER_MAX,
} rmt_mem_owner_t;

/**
 * @brief RMT信道的时钟源
 *
 */
typedef enum {
#if SOC_RMT_SUPPORT_REF_TICK
    RMT_BASECLK_REF = 0, /*!< RMT源时钟默认为REF_TICK，1MHz*/
#endif
    RMT_BASECLK_APB = 1, /*!< RMT源时钟默认为APB CLK，80Mhz*/
#if SOC_RMT_SUPPORT_XTAL
    RMT_BASECLK_XTAL = 3, /*!< RMT源时钟为XTAL时钟，默认为40Mhz*/
#endif
    RMT_BASECLK_MAX,
} rmt_source_clk_t;

/**
 * @brief RMT数据模式
 *
 * @note 我们强烈建议使用MEM模式而不是FIFO模式，因为FIFO模式中会有一些错误。
 *
 */
typedef enum {
    RMT_DATA_MODE_FIFO, /*<! FIFO模式下的RMT内存访问*/
    RMT_DATA_MODE_MEM,  /*<! 内存模式下的RMT内存访问*/
    RMT_DATA_MODE_MAX,
} rmt_data_mode_t;

/**
 * @brief RMT信道工作模式（TX或RX）
 *
 */
typedef enum {
    RMT_MODE_TX, /*!< RMT TX模式*/
    RMT_MODE_RX, /*!< RMT RX模式*/
    RMT_MODE_MAX
} rmt_mode_t;

/**
 * @brief RMT闲置水平
 *
 */
typedef enum {
    RMT_IDLE_LEVEL_LOW,  /*!< RMT TX空闲电平：低电平*/
    RMT_IDLE_LEVEL_HIGH, /*!< RMT TX空闲电平：高电平*/
    RMT_IDLE_LEVEL_MAX,
} rmt_idle_level_t;

/**
 * @brief RMT载波电平
 *
 */
typedef enum {
    RMT_CARRIER_LEVEL_LOW,  /*!< RMT载波调制为低电平输出*/
    RMT_CARRIER_LEVEL_HIGH, /*!< RMT载波被调制用于高电平输出*/
    RMT_CARRIER_LEVEL_MAX
} rmt_carrier_level_t;

/**
 * @brief RMT通道状态
 *
 */
typedef enum {
    RMT_CHANNEL_UNINIT, /*!< RMT通道未初始化*/
    RMT_CHANNEL_IDLE,   /*!< RMT信道状态空闲*/
    RMT_CHANNEL_BUSY,   /*!< RMT信道状态忙*/
} rmt_channel_status_t;

/**
* @brief RMT通道状态数据结构
*/
typedef struct {
    rmt_channel_status_t status[RMT_CHANNEL_MAX]; /*!< 存储每个通道的当前状态*/
} rmt_channel_status_result_t;

#ifdef __cplusplus
}
#endif

