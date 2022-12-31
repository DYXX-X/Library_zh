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

// SIGMADELTA的HAL层。
// hal层中没有参数检查，因此调用者必须确保参数的正确性。

#pragma once

#include "soc/sigmadelta_periph.h"
#include "hal/sigmadelta_types.h"
#include "hal/sigmadelta_ll.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * 驾驶员和HAL应维护的上下文
 */

typedef struct {
    gpio_sd_dev_t *dev;
} sigmadelta_hal_context_t;

/**
 * @brief 设置Sigma delta通道占空比。
 *
 * @param hal HAL层的上下文
 * @param channel Sigma-delta通道编号
 * @param duty 一个通道的Sigma-delta占空比，值范围为-128至127，建议范围为-90~90。在此范围内，波形更像随机波形。
 */
#define sigmadelta_hal_set_duty(hal, channel, duty) sigmadelta_ll_set_duty((hal)->dev, channel, duty)

/**
 * @brief 设置Sigma-delta通道的时钟预缩放值。
 *
 * @param hal HAL层的上下文
 * @param channel Sigma-delta通道编号
 * @param prescale 源时钟分频器，范围从0到255
 */
#define sigmadelta_hal_set_prescale(hal, channel, prescale) sigmadelta_ll_set_prescale((hal)->dev, channel, prescale)

/**
 * @brief 初始化SIGMADELTA hal并将SIGMADELTA设置为默认配置。在调用其他hal层函数之前，应先调用此函数
 *
 * @param hal HAL层的上下文
 * @param sigmadelta_num uart端口号，最大端口号为（SIGMADELTA_NUM_max-1）
 */
void sigmadelta_hal_init(sigmadelta_hal_context_t *hal, int sigmadelta_num);

#ifdef __cplusplus
}
#endif

