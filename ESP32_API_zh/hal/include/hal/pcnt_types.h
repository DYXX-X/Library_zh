// 版权所有2015-2021 Espressif Systems（Shanghai）PTE LTD
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

/**
 * @brief 控制级PCNT通道动作
 *
 */
typedef enum {
    PCNT_CHANNEL_LEVEL_ACTION_KEEP,    /*!< 保持当前计数模式*/
    PCNT_CHANNEL_LEVEL_ACTION_INVERSE, /*!< 反转电流计数模式（增加->减少，减少->增加）*/
    PCNT_CHANNEL_LEVEL_ACTION_HOLD,    /*!< 保持当前计数值*/
} pcnt_channel_level_action_t;

/**
 * @brief 信号边缘上的PCNT通道动作
 *
 */
typedef enum {
    PCNT_CHANNEL_EDGE_ACTION_HOLD,     /*!< 保持当前计数值*/
    PCNT_CHANNEL_EDGE_ACTION_INCREASE, /*!< 增加计数值*/
    PCNT_CHANNEL_EDGE_ACTION_DECREASE, /*!< 减少计数值*/
} pcnt_channel_edge_action_t;

/**
 * @brief PCNT单位计数器值符号
 *
 */
typedef enum {
    PCNT_UNIT_COUNT_SIGN_ZERO_POS, /*!< 正值为零*/
    PCNT_UNIT_COUNT_SIGN_ZERO_NEG, /*!< 负值归零*/
    PCNT_UNIT_COUNT_SIGN_NEG,      /*!< 计数器值负值*/
    PCNT_UNIT_COUNT_SIGN_POS,      /*!< 计数器值正值*/
} pcnt_unit_count_sign_t;

#ifdef __cplusplus
}
#endif

