/*
 * SPDX文件版权文本：2015-2021浓缩咖啡系统（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "esp_err.h"


/**
 * @brief I2S dma要求使用ADC1。
 *
 * 禁止其他任务在“ADC1_dma_mode_acquire”和“ADC1_i2s_release”之间使用ADC1。I2S模块可能需要等待很短的时间才能完成电流转换（如果存在）。
 *
 * @return
 *      -ESP_OK成功
 *      -ESP_ERR_TIMEOUT保留供将来使用。目前，该功能将等待成功。
 */
esp_err_t adc1_dma_mode_acquire(void);

/**
 * @brief ADC1声明使用ADC1。
 *
 * 禁止其他任务在“ADC1_rtc_mode_acquire”和“ADC1_i2s_release”之间使用ADC1。ADC1可能必须等待一段时间以完成I2S读取操作。
 *
 * @return
 *      -ESP_OK成功
 *      -ESP_ERR_TIMEOUT保留供将来使用。目前，该功能将等待成功。
 */
esp_err_t adc1_rtc_mode_acquire(void);

/**
 * @brief 以便在I2S不工作时让其他任务使用ADC1。
 *
 * 禁止其他任务在“ADC1_adc/i2s_mode_acquire”和“ADC1_i2s_release”之间使用ADC1。调用此函数以释放ADC1的占用
 *
 * @return 始终返回ESP_OK。
 */
esp_err_t adc1_lock_release(void);

#ifdef __cplusplus
}
#endif

