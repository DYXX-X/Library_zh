/*
 * SPDX文件版权文本：2015-2021浓缩咖啡系统（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */

#pragma once

#include <esp_types.h>
#include "soc/soc_caps.h"
#include "soc/sigmadelta_periph.h"
#include "driver/gpio.h"
#include "hal/sigmadelta_types.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 配置Sigma delta通道
 *
 * @param  config Sigma delta通道配置结构的指针
 *
 * @return
 *     -ESP_OK成功
 *     -ESP_ERR_INVALID_STATE sigmadelta驱动程序已初始化
 *     -ESP_ERR_INVALID_ARG参数错误
 */
esp_err_t sigmadelta_config(const sigmadelta_config_t *config);

/**
 * @brief 设置Sigma delta通道占空比。
 *
 *        此功能用于设置Sigma-delta通道占空比。如果在输出引脚和接地之间添加电容器，则平均输出电压将为Vdc=VDDIO/256占空比+VDDIO/2，其中VDDIO为电源电压。
 *
 * @param channel Sigma-delta通道编号
 * @param duty 一个通道的Sigma-delta占空比，值范围为-128至127，建议范围为-90~90。在此范围内，波形更像随机波形。
 *
 * @return
 *     -ESP_OK成功
 *     -ESP_ERR_INVALID_STATE sigmadelta驱动程序尚未初始化
 *     -ESP_ERR_INVALID_ARG参数错误
 */
esp_err_t sigmadelta_set_duty(sigmadelta_channel_t channel, int8_t duty);

/**
 * @brief 设置Sigma-delta通道的时钟预缩放值。源时钟为APP_CLK，80MHz。∑-Δ信道的时钟频率为APP_CLK/pre_scale
 *
 * @param channel Sigma-delta通道编号
 * @param prescale 源时钟分频器，范围从0到255
 *
 * @return
 *     -ESP_OK成功
 *     -ESP_ERR_INVALID_STATE sigmadelta驱动程序尚未初始化
 *     -ESP_ERR_INVALID_ARG参数错误
 */
esp_err_t sigmadelta_set_prescale(sigmadelta_channel_t channel, uint8_t prescale);

/**
 * @brief 设置Sigma-delta信号输出引脚
 *
 * @param channel Sigma-delta通道编号
 * @param gpio_num 输出引脚的GPIO编号。
 *
 * @return
 *     -ESP_OK成功
 *     -ESP_ERR_INVALID_STATE sigmadelta驱动程序尚未初始化
 *     -ESP_ERR_INVALID_ARG参数错误
 */
esp_err_t sigmadelta_set_pin(sigmadelta_channel_t channel, gpio_num_t gpio_num);

#ifdef __cplusplus
}
#endif

