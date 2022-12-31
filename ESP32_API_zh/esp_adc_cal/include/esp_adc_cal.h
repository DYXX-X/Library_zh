/*
 * SPDX文件版权所有文本：2015-2022 Espressif Systems（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */

#ifndef __ESP_ADC_CAL_H__
#define __ESP_ADC_CAL_H__

#include <stdint.h>
#include "esp_err.h"
#include "driver/adc.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 用于表征的校准值类型
 */
typedef enum {
    ESP_ADC_CAL_VAL_EFUSE_VREF = 0,         /**<基于eFuse中存储的参考电压的特性*/
    ESP_ADC_CAL_VAL_EFUSE_TP = 1,           /**<基于eFuse中存储的两点值的特性*/
    ESP_ADC_CAL_VAL_DEFAULT_VREF = 2,       /**<基于默认参考电压的特性*/
    ESP_ADC_CAL_VAL_EFUSE_TP_FIT = 3,       /**<基于存储在eFuse中的两点值和拟合曲线系数的特性*/
    ESP_ADC_CAL_VAL_MAX,
    ESP_ADC_CAL_VAL_NOT_SUPPORTED = ESP_ADC_CAL_VAL_MAX,
} esp_adc_cal_value_t;

/**
 * @brief 存储ADC特性的结构
 *
 * @note 调用esp_adc_cal_characterize（）初始化结构
 */
typedef struct {
    adc_unit_t adc_num;                     /**<ADC编号*/
    adc_atten_t atten;                      /**<ADC衰减*/
    adc_bits_width_t bit_width;             /**<ADC位宽*/
    uint32_t coeff_a;                       /**<ADC电压曲线的梯度*/
    uint32_t coeff_b;                       /**<ADC电压曲线的偏移*/
    uint32_t vref;                          /**<查找表使用的Vref*/
    const uint32_t *low_curve;              /**<指向查找表的低Vref曲线的指针（如果未使用，则为NULL）*/
    const uint32_t *high_curve;             /**<指向查找表的高Vref曲线的指针（如果未使用，则为NULL）*/
    uint8_t version;                        /**<ADC校准*/
} esp_adc_cal_characteristics_t;

/**
 * @brief 检查ADC校准值是否烧入eFuse
 *
 * 此功能检查ADC参考电压或两点值是否已烧到电流ESP32的eFuse上
 *
 * @param   value_type  校准值类型（ESP_ADC_CAL_VAL_EFUSE_VREF或ESP_ADC-CAL_VAL-EFUSE_TP）
 * @note 在ESP32S2中，仅支持ESP_ADC_CAL_VAL_EFUSE_TP。一些旧的ESP32S2也不支持这一点。在这种情况下，您必须手动校准，可能需要在芯片上执行自己的两点校准。
 *
 * @return
 *      -ESP_OK:eFuse支持校准模式
 *      -ESP_ERR_NOT_SUPPORTED：错误，eFuse值未烧毁
 *      -ESP_ERR_INVALID_ARG：错误，参数无效（ESP_ADC_CAL_VAL_DEFAULT_VREF）
 */
esp_err_t esp_adc_cal_check_efuse(esp_adc_cal_value_t value_type);

/**
 * @brief 在特定衰减下表征ADC
 *
 * 该函数将表征特定衰减下的ADC，并以[y=coeff_a x+coeff_b]的形式生成ADC电压曲线。特征化可以基于两点值、eFuse Vref或默认Vref，校准值将按此顺序排列。
 *
 * @note 对于ESP32，可以使用menuconfig启用/禁用两点值和eFuse Vref校准。对于ESP32s2，仅支持两点值校准和ADC_WIDTH_BIT_13。参数default_vref未使用。
 *
 *
 * @param[in]   adc_num         要表征的ADC（ADC_UNIT_1或ADC_UNIT_2）
 * @param[in]   atten           要表征的衰减
 * @param[in]   bit_width       ADC的位宽配置
 * @param[in]   default_vref    默认ADC参考电压（mV）（仅在ESP32中，在eFuse值不可用时使用）
 * @param[out]  chars           指向用于存储ADC特性的空结构的指针
 *
 * @return
 *      -ESP_ADC_CAL_VAL_EFUSE_VREF：用于表征的EFUSE VREF
 *      -ESP_ADC_CAL_VAL_EFUSE_TP：用于表征的两点值（仅在线性模式下）
 *      -ESP_ADC_CAL_VAL_DEFAULT_VREF：用于表征的默认VREF
 */
esp_adc_cal_value_t esp_adc_cal_characterize(adc_unit_t adc_num,
                                             adc_atten_t atten,
                                             adc_bits_width_t bit_width,
                                             uint32_t default_vref,
                                             esp_adc_cal_characteristics_t *chars);

/**
 * @brief   将ADC读数转换为电压（mV）
 *
 * 此函数根据ADC的特性将ADC读数转换为以mV为单位的电压。
 *
 * @note    在调用此函数之前，必须初始化特征结构（调用esp_adc_cal_characterize（））
 *
 * @param[in]   adc_reading     ADC读数
 * @param[in]   chars           指向包含ADC特征的初始化结构的指针
 *
 * @return      电压（mV）
 */
uint32_t esp_adc_cal_raw_to_voltage(uint32_t adc_reading, const esp_adc_cal_characteristics_t *chars);

/**
 * @brief   读取ADC并将读数转换为mV电压
 *
 * 该功能读取ADC，然后根据提供的特性将原始读数转换为以mV为单位的电压。读取的ADC也由特性决定。
 *
 * @note    在调用此函数之前，必须初始化Characteristics结构（调用esp_adc_cal_characterize（））
 *
 * @param[in]   channel     要读取的ADC通道
 * @param[in]   chars       指向初始化ADC特征结构的指针
 * @param[out]  voltage     存储转换电压的指针
 *
 * @return
 *      -ESP_OK：ADC读取并转换为mV
 *      -ESP_ERR_INVALID_ARG：参数无效导致错误
 *      -ESP_ERR_INVALID_STATE:读取结果无效。尝试再次阅读。
 */
esp_err_t esp_adc_cal_get_voltage(adc_channel_t channel, const esp_adc_cal_characteristics_t *chars, uint32_t *voltage);

#ifdef __cplusplus
}
#endif

#endif /* __ESP_ADC_CAL_H__ */

