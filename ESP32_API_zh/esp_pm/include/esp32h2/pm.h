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
#include <stdbool.h>
#include "esp_err.h"

#include "soc/rtc.h"

#ifdef __cplusplus
extern "C" {
#endif


/**
 * @brief ESP32H2的电源管理配置
 *
 * 将指向此结构的指针作为参数传递给esp_pm_configure函数。
 */
typedef struct {
    int max_freq_mhz;   /*!< 最大CPU频率（MHz）*/
    int min_freq_mhz;   /*!< 在没有锁定时使用的最小CPU频率（MHz）*/
    bool light_sleep_enable;        /*!< 当没有锁时进入浅睡眠*/
} esp_pm_config_esp32h2_t;


#ifdef __cplusplus
}
#endif

