/*
 * SPDX文件版权文本：2015-2021浓缩咖啡系统（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */

/*----------------------------------------------------------------------------------
              此文件包含不推荐的ADC API
-----------------------------------------------------------------------------------*/

#pragma once
#include "esp_err.h"
#include "hal/adc_types.h"
#include "driver/adc_types_deprecated.h"

#ifdef __cplusplus
extern "C" {
#endif


#if CONFIG_IDF_TARGET_ESP32S2
/*---------------------------------------------------------------
                    ESP32S2弃用的ADC API
---------------------------------------------------------------*/
/**
 * @brief 配置ADC模块仲裁器。仲裁器是为了提高ADC2的使用效率，在控制权被高优先级抢走后，低优先级控制器将读取无效的ADC2数据，数据的有效性可以通过数据中的标志位来判断。
 *
 * @note 只有ADC2支持仲裁器。
 * @note 默认优先级：Wi-Fi>RTC>Digital；
 * @note 在正常使用中，不需要调用此接口来配置仲裁器。
 *
 * @param adc_unit ADC单元。
 * @param config 请参阅“adc_arbiter_t”。
 *
 * @return
 *      -ESP_OK成功
 *      -ESP_ERR_NOT_SUPPORTED ADC单元不支持仲裁器。
 */
esp_err_t adc_arbiter_config(adc_unit_t adc_unit, adc_arbiter_t *config) __attribute__((deprecated));

/**
 * @brief 通过位掩码启用adc数字控制器的中断。
 *
 * @param adc_unit ADC单元。
 * @param intr_mask 中断位掩码。请参见`adc_digi_intr_t``。
 *
 * @return
 *      -ESP_OK成功
 */
esp_err_t adc_digi_intr_enable(adc_unit_t adc_unit, adc_digi_intr_t intr_mask) __attribute__((deprecated));

/**
 * @brief 通过位掩码禁用adc数字控制器中断。
 *
 * @param adc_unit ADC单元。
 * @param intr_mask 中断位掩码。请参见`adc_digi_intr_t``。
 *
 * @return
 *      -ESP_OK成功
 */
esp_err_t adc_digi_intr_disable(adc_unit_t adc_unit, adc_digi_intr_t intr_mask) __attribute__((deprecated));

/**
 * @brief 通过位掩码清除adc数字控制器的中断。
 *
 * @param adc_unit ADC单元。
 * @param intr_mask 中断位掩码。请参见`adc_digi_intr_t``。
 *
 * @return
 *      -ESP_OK成功
 */
esp_err_t adc_digi_intr_clear(adc_unit_t adc_unit, adc_digi_intr_t intr_mask) __attribute__((deprecated));

/**
 * @brief 获取adc数字控制器的中断状态掩码。
 *
 * @param adc_unit ADC单元。
 * @return
 *     -intr中断位掩码，请参见`adc_digi_intr_t``。
 */
uint32_t adc_digi_intr_get_status(adc_unit_t adc_unit) __attribute__((deprecated));

/**
 * @brief 注册ADC中断处理程序，该处理程序是ISR。处理程序将连接到运行此函数的同一CPU内核。
 *
 * @param fn 中断处理程序函数。
 * @param arg 处理程序函数的参数
 * @param intr_alloc_flags 用于分配中断的标志。一个或多个（ORred）ESP_INTR_FLAG_值。请参见esp_intr_alloc。h了解更多信息。
 *
 * @return
 *     -ESP_OK成功
 *     -ESP_ERR_NOT_FOUND找不到与标志匹配的中断。
 *     -ESP_ERR_INVALID_ARG函数指针错误。
 */
esp_err_t adc_digi_isr_register(void (*fn)(void *), void *arg, int intr_alloc_flags) __attribute__((deprecated));

/**
 * @brief 取消注册ADC中断处理程序，该处理程序是ISR。
 *
 * @return
 *     -ESP_OK成功
 *     -ESP_ERR_INVALID_ARG处理程序错误。
 *     -未注册ESP_FAIL ISR。
 */
esp_err_t adc_digi_isr_deregister(void) __attribute__((deprecated));
#endif  // #如果配置IDF_TARGET_ESP32S2


#if CONFIG_IDF_TARGET_ESP32 || CONFIG_IDF_TARGET_ESP32S2
/*---------------------------------------------------------------
            ESP32、ESP32S2弃用的ADC API
---------------------------------------------------------------*/
/**
 * @brief ADC数字控制器初始化。
 * @return
 *      -ESP_OK成功
 */
esp_err_t adc_digi_init(void) __attribute__((deprecated));

/**
 * @brief ADC数字控制器去初始化。
 * @return
 *      -ESP_OK成功
 */
esp_err_t adc_digi_deinit(void) __attribute__((deprecated));
#endif  //#如果CONFIG_IDF_TARGET_ESP32 | | CONFIG_IDF _TARGET_ESP32S2


#if CONFIG_IDF_TARGET_ESP32 || CONFIG_IDF_TARGET_ESP32S2 || CONFIG_IDF_TARGET_ESP32C3
/*---------------------------------------------------------------
            ESP32、ESP32S2、ESP32C3弃用的ADC API
---------------------------------------------------------------*/
/**
 * @brief 设置数字控制器。
 *
 * @param config 指向数字控制器参数的指针。请参阅`adc_digi_config_t``。
 *
 * @return
 *      -ESP_ERR_INVALID_STATE驱动程序状态无效。
 *      -ESP_ERR_INVALID_ARG如果参数组合无效。
 *      -ESP_OK成功
 */
esp_err_t adc_digi_controller_config(const adc_digi_config_t *config) __attribute__((deprecated));

/**
 * @brief 初始化ADC焊盘
 * @param adc_unit ADC单元索引
 * @param channel ADC通道索引
 * @return
 *     -ESP_OK成功
 *     -ESP_ERR_INVALID_ARG参数错误
 */
esp_err_t adc_gpio_init(adc_unit_t adc_unit, adc_channel_t channel) __attribute__((deprecated));;
#endif //#如果CONFIG_IDF_TARGET_ESP32 | | CONFIG_IDF _TARGET_ESP32S2 | | CONFIG _IDF_TERGET_ESP32C3


#ifdef __cplusplus
}
#endif

