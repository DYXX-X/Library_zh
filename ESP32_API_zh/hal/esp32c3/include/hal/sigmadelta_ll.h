// 版权所有2020 Espressif Systems（上海）私人有限公司
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
 * 注意：hal不是公共api，不要在应用程序代码中使用。请参阅自述文件。soc/include/hal/readme.md中的md
 ******************************************************************************/

// ESP32 SIGMADELTA寄存器操作的LL层

#pragma once

#include <stdbool.h>
#include "hal/misc.h"
#include "soc/sigmadelta_periph.h"
#include "soc/gpio_sd_struct.h"
#include "hal/sigmadelta_types.h"

#ifdef __cplusplus
extern "C" {
#endif

// 使用SIGMADELTA num获取SIGMADELTA硬件实例
#define SIGMADELTA_LL_GET_HW(num) (((num) == 0) ? (&SIGMADELTA) : NULL)

/**
 * @brief 设置Sigma delta启用
 *
 * @param hw 外围SIGMADELTA硬件实例地址。
 * @param en Sigma delta启用值
 */
static inline void sigmadelta_ll_set_en(gpio_sd_dev_t *hw, bool en)
{
    hw->misc.function_clk_en = en;
}

/**
 * @brief 设置Sigma delta通道占空比。
 *
 * @param hw 外围SIGMADELTA硬件实例地址。
 * @param channel Sigma-delta通道编号
 * @param duty 一个通道的Sigma-delta占空比，值范围为-128至127，建议范围为-90~90。在此范围内，波形更像随机波形。
 */
static inline void sigmadelta_ll_set_duty(gpio_sd_dev_t *hw, sigmadelta_channel_t channel, int8_t duty)
{
    HAL_FORCE_MODIFY_U32_REG_FIELD(hw->channel[channel], duty, (uint32_t)duty);
}

/**
 * @brief 设置Sigma-delta通道的时钟预缩放值。
 *
 * @param hw 外围SIGMADELTA硬件实例地址。
 * @param channel Sigma-delta通道编号
 * @param val 源时钟分频器，范围从0到255
 */
static inline void sigmadelta_ll_set_prescale(gpio_sd_dev_t *hw, sigmadelta_channel_t channel, uint8_t prescale)
{
    HAL_FORCE_MODIFY_U32_REG_FIELD(hw->channel[channel], prescale, prescale);
}

#ifdef __cplusplus
}
#endif

