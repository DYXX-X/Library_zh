/*
 * SPDX文件版权文本：2019-2021浓缩咖啡系统（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */

#pragma once

#include "driver/dac_common.h"

#ifdef __cplusplus
extern "C" {
#endif
/*---------------------------------------------------------------
                    数字控制器设置
---------------------------------------------------------------*/

/**
 * @brief DAC数字控制器初始化。
 * @return
 *     -ESP_OK成功
 */
esp_err_t dac_digi_init(void);

/**
 * @brief DAC数字控制器去初始化。
 * @return
 *     -ESP_OK成功
 */
esp_err_t dac_digi_deinit(void);

/**
 * @brief 设置DAC数字控制器。
 *
 * @param cfg 指向数字控制器参数的指针。请参见`dac_digi_config_t``。
 *
 * @return
 *     -ESP_OK成功
 *     -ESP_ERR_INVALID_ARG参数错误
 */
esp_err_t dac_digi_controller_config(const dac_digi_config_t *cfg);

/**
 * @brief DAC数字控制器启动输出电压。
 * @return
 *     -ESP_OK成功
 */
esp_err_t dac_digi_start(void);

/**
 * @brief DAC数字控制器停止输出电压。
 * @return
 *     -ESP_OK成功
 */
esp_err_t dac_digi_stop(void);

/**
 * @brief 重置DAC数字控制器FIFO。
 * @return
 *     -ESP_OK成功
 */
esp_err_t dac_digi_fifo_reset(void);

/**
 * @brief 重置DAC数字控制器。
 * @return
 *     -ESP_OK成功
 */
esp_err_t dac_digi_reset(void);

#ifdef __cplusplus
}
#endif

