/*
 * SPDX文件版权文本：2015-2021浓缩咖啡系统（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */

#pragma once
#include <stdint.h>
#include "sdkconfig.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @file 睡眠时间h
 *
 * 此文件包含浅睡眠模式下GPIO相关函数的声明。
 */

#if SOC_GPIO_SUPPORT_SLP_SWITCH && CONFIG_GPIO_ESP32_SUPPORT_SWITCH_SLP_PULL

/**
 * @brief 在唤醒状态下保存GPIO上拉和下拉配置信息
 *
 * 在轻睡眠模式下，GPIO的上拉和下拉电阻器会在系统睡眠时产生泄漏电流。为了降低系统休眠的功耗，需要在系统进入休眠之前保存所有GPIO上拉和下拉电阻器的配置信息，并禁用GPIO的上拉和下拉电阻器。
 */
void gpio_sleep_mode_config_apply(void);

/**
 * @brief 在唤醒状态下恢复GPIO上拉和下拉配置信息
 *
 * 在轻睡眠模式下，系统唤醒后，需要在最后一次睡眠前恢复所有GPIO上拉和下拉配置。
 */
void gpio_sleep_mode_config_unapply(void);

#endif // SOC_GPIO_SUPPORT_SLP_SWITCH && CONFIG_GPIO_ESP32_SUPPORT_SWITCH_SLP_PULL

#ifdef __cplusplus
}
#endif

