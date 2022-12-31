/*
 * SPDX文件版权所有文本：2020-2022 Espressif Systems（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */

#pragma once

#include <stdint.h>
#include "sdkconfig.h"

#ifdef __cplusplus
extern "C" {
#endif

#if CONFIG_IDF_TARGET_ESP32C3 || CONFIG_IDF_TARGET_ESP32S3
#define ESP_ADC_CAL_CURVE_FITTING_SUPPORTED    1

#define COEFF_GROUP_NUM    4
#define TERM_MAX           5
#endif

#if ESP_ADC_CAL_CURVE_FITTING_SUPPORTED
/**
 * 用于曲线拟合校准算法误差的计算参数
 *
 * @note 对于atten0~2，误差=（K0*X^0）+（K1*X^1）+（K2*X^2）；对于atten3，误差=（K0*X^0）+（K1*X^1）+（K2*X^2）+（K3*X^3）+（K4*X^4）；其中X是“v_cali_input”。
 */
typedef struct {
    uint64_t v_cali_input;                                      //计算误差的输入
    uint8_t  term_num;                                          //算法公式的项数
    const uint64_t (*coeff)[COEFF_GROUP_NUM][TERM_MAX][2];      //每个项的系数。有关详细信息，请参见“adc_error_coef_atten”（以及神奇数字2）
    const int32_t  (*sign)[COEFF_GROUP_NUM][TERM_MAX];          //每个术语的符号
} esp_adc_error_calc_param_t;

/**
 * 计算曲线拟合误差
 *
 * @param param   请参见`esp_adc_error_calc_param_t`
 * @param atten   ADC衰减
 */
int32_t esp_adc_cal_get_reading_error(const esp_adc_error_calc_param_t *param, uint8_t atten);

#endif  //#如果ESP_ADC_CAL_CURVE_FITTING_SUPPORTED


#ifdef __cplusplus
}
#endif

