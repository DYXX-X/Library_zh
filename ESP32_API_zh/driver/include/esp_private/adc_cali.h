/*
 * SPDX文件版权文本：2020-2021浓缩咖啡系统（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */

// 用于校准的内部标头，不在应用程序中使用

#include "sdkconfig.h"
#include "esp_err.h"
#include "hal/adc_hal.h"

#ifdef __cplusplus
extern "C" {
#endif

#if !CONFIG_IDF_TARGET_ESP32

/**
 * @brief 校准ADC的偏移。（基于预先存储的efuse或实际校准）
 *
 * @param adc_n 要校准的ADC单元
 * @param channel 如果真的进行校准，目标通道
 * @param atten 要使用的衰减
 * @return 始终ESP_OK
 */
extern esp_err_t adc_cal_offset(adc_ll_num_t adc_n, adc_channel_t channel, adc_atten_t atten);

#endif

#ifdef __cplusplus
}
#endif

