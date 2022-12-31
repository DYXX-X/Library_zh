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
 * @brief WIFI模块要求使用ADC2。
 *
 * 禁止其他任务在“ADC2_wifi_acquire”和“ADC2_wifi_release”之间使用ADC2。WIFI模块可能需要等待很短时间才能完成电流转换（如果存在）。
 *
 * @return
 *      -ESP_OK成功
 *      -ESP_ERR_TIMEOUT保留供将来使用。目前，该功能将等待成功。
 */
esp_err_t adc2_wifi_acquire(void);


/**
 * @brief 当WIFI不工作时，WIFI模块允许其他任务使用ADC2。
 *
 * 禁止其他任务在“ADC2_wifi_acquire”和“ADC2_wifi_release”之间使用ADC2。调用此函数以释放WIFI对ADC2的占用。
 *
 * @return 始终返回ESP_OK。
 */
esp_err_t adc2_wifi_release(void);

#if CONFIG_IDF_TARGET_ESP32S2 || CONFIG_IDF_TARGET_ESP32C3 || CONFIG_IDF_TARGET_ESP32H2
/**
 * @brief 此API帮助链接ADC2校准构造函数。
 *
 * @note  这是一个私有函数，不要在用户代码中调用`adc2_cal_include`。
 */
void adc2_cal_include(void);
#else
/**
 * @brief 这个芯片没有校准。
 *
 * @note  这是一个私有函数，不要在用户代码中调用`adc2_cal_include`。
 */
#define adc2_cal_include()
#endif //CONFIG_IDF_TARGET_*

#ifdef __cplusplus
}
#endif

