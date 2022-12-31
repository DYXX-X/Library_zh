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

#pragma once

#include <stdint.h>
#include "soc/soc_caps.h"

#ifdef __cplusplus
extern "C" {
#endif

/*
 * @brief 系统计数器值的结构
 *
 */
typedef struct {
    union {
        struct {
            uint64_t lo : SOC_SYSTIMER_BIT_WIDTH_LO; /*!< 计数器值的低部分*/
            uint64_t hi : SOC_SYSTIMER_BIT_WIDTH_HI; /*!< 计数器值的高部分*/
        };
        uint64_t val; /*!< 计数器值*/
    };
} systimer_counter_value_t;

/**@秒*/
_Static_assert(sizeof(systimer_counter_value_t) == 8, "systimer_counter_value_t should occupy 8 bytes in memory");
/**@结束秒*/

/**
 * @brief 系统报警模式
 *
 */
typedef enum {
    SYSTIMER_ALARM_MODE_ONESHOT, /*!< 系统报警单触发模式*/
    SYSTIMER_ALARM_MODE_PERIOD,  /*!< 系统报警周期模式*/
} systimer_alarm_mode_t;

#ifdef __cplusplus
}
#endif

