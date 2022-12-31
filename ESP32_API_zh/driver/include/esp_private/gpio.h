/*
 * SPDX文件版权文本：2015-2021浓缩咖啡系统（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */

#pragma once

#include "sdkconfig.h"
#include <esp_types.h>

#include "soc/soc_caps.h"
#include "driver/gpio.h"

#if SOC_GPIO_SUPPORT_SLP_SWITCH
#if CONFIG_GPIO_ESP32_SUPPORT_SWITCH_SLP_PULL
/**
  * @brief 模拟ESP32S2行为以备份FUN_PU、FUN_PD信息
  *
  * @note 睡觉前需要打电话。
  *
  * @return
  *      -ESP_OK成功
  */
esp_err_t gpio_sleep_pupd_config_apply(gpio_num_t gpio_num);

/**
  * @brief 模拟ESP32S2行为以恢复FUN_PU、FUN_PD信息
  *
  * @note 睡觉后需要打电话。
  *
  * @return
  *      -ESP_OK成功
  */
esp_err_t gpio_sleep_pupd_config_unapply(gpio_num_t gpio_num);
#endif
#endif

