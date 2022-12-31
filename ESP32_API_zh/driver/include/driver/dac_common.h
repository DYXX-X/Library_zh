/*
 * SPDX文件版权文本：2015-2021浓缩咖啡系统（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include "esp_err.h"
#include "driver/gpio.h"
#include "hal/dac_types.h"

/**
 * @brief 获取特定DAC通道的GPIO编号。
 *
 * @param channel 获取gpio号码的频道
 * @param gpio_num 保存gpio编号的输出缓冲区
 * @return
 *   -ESP_OK（如果成功）
 */
esp_err_t dac_pad_get_io_num(dac_channel_t channel, gpio_num_t *gpio_num);

/**
 * @brief 设置DAC输出电压。DAC输出为8位。最大值（255）对应于VDD3P3_RTC。
 *
 * @note 调用此函数之前需要配置DAC垫。DAC通道1与GPIO25相连，DAC通道2与GPIO26相连
 * @param channel DAC通道
 * @param dac_value DAC输出值
 *
 * @return
 *     -ESP_OK成功
 */
esp_err_t dac_output_voltage(dac_channel_t channel, uint8_t dac_value);

/**
 * @brief DAC焊盘输出启用
 *
 * @param channel DAC通道
 * @note DAC通道1连接到GPIO25，DAC通道2连接到GPIO26 I2S左通道将映射到DAC通道2 I2S右通道将映射至DAC通道1
 */
esp_err_t dac_output_enable(dac_channel_t channel);

/**
 * @brief DAC焊盘输出禁用
 *
 * @param channel DAC通道
 * @note DAC通道1与GPIO25相连，DAC通道2与GPIO26相连
 * @return
 *     -ESP_OK成功
 */
esp_err_t dac_output_disable(dac_channel_t channel);

/**
 * @brief 启用余弦波发生器输出。
 *
 * @return
 *     -ESP_OK成功
 */
esp_err_t dac_cw_generator_enable(void);

/**
 * @brief 禁用余弦波发生器输出。
 *
 * @return
 *     -ESP_OK成功
 */
esp_err_t dac_cw_generator_disable(void);

/**
 * @brief 在DAC模块中配置余弦波发生器功能。
 *
 * @param cw 配置
 * @return
 *     -ESP_OK成功
 *     -ESP_ERR_INVALID_ARG参数为NULL。
 */
esp_err_t dac_cw_generator_config(dac_cw_config_t *cw);

#ifdef __cplusplus
}
#endif

