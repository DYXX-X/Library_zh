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

typedef enum {
    MCPWM_TIMER_DIRECTION_UP,   /*!< 计数方向：增加*/
    MCPWM_TIMER_DIRECTION_DOWN, /*!< 计数方向：减少*/
} mcpwm_timer_direction_t;

typedef enum {
    MCPWM_TIMER_EVENT_ZERO, /*!< MCPWM计时器计数为零*/
    MCPWM_TIMER_EVENT_PEAK, /*!< MCPWM计时器计数达到峰值*/
} mcpwm_timer_event_t;

typedef enum {
    MCPWM_TIMER_COUNT_MODE_PAUSE,   /*!< MCPWM计时器已暂停*/
    MCPWM_TIMER_COUNT_MODE_UP,      /*!< MCPWM计时器计数*/
    MCPWM_TIMER_COUNT_MODE_DOWN,    /*!< MCPWM定时器倒计时*/
    MCPWM_TIMER_COUNT_MODE_UP_DOWN, /*!< MCPWM定时器上下计数*/
} mcpwm_timer_count_mode_t;

typedef enum {
    MCPWM_TIMER_STOP_AT_ZERO,       /*!< MCPWM计时器在归零时停止*/
    MCPWM_TIMER_STOP_AT_PEAK,       /*!< 计数到峰值时，MCPWM计时器停止*/
    MCPWM_TIMER_START_NO_STOP,      /*!< MCPWM计时器开始计时*/
    MCPWM_TIMER_START_STOP_AT_ZERO, /*!< MCPWM计时器开始计数并在归零时停止*/
    MCPWM_TIMER_START_STOP_AT_PEAK, /*!< MCPWM计时器开始计数，计数到峰值时停止*/
} mcpwm_timer_execute_cmd_t;

typedef enum {
    MCPWM_GEN_ACTION_KEEP,   /*!< 发电机动作：保持相同水平*/
    MCPWM_GEN_ACTION_LOW,    /*!< 发电机动作：强制至低电平*/
    MCPWM_GEN_ACTION_HIGH,   /*!< 发电机动作：强制至高电平*/
    MCPWM_GEN_ACTION_TOGGLE, /*!< 生成器操作：切换级别*/
} mcpwm_generator_action_t;

typedef enum {
    MCPWM_TRIP_TYPE_CBC, /*!< CBC跳闸类型，逐个周期关闭操作员*/
    MCPWM_TRIP_TYPE_OST, /*!< OST跳闸类型，一次性关闭操作员*/
} mcpwm_trip_type_t;

