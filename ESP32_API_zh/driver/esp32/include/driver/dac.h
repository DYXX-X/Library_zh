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
 * @brief 启用I2S的DAC输出数据
 *
 * @return
 *     -ESP_OK成功
 */
esp_err_t dac_i2s_enable(void);

/**
 * @brief 禁用I2S的DAC输出数据
 *
 * @return
 *     -ESP_OK成功
 */
esp_err_t dac_i2s_disable(void);

#ifdef __cplusplus
}
#endif

