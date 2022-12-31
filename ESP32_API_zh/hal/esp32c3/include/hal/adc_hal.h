/*
 * SPDX文件版权文本：2020-2021浓缩咖啡系统（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */

/*******************************************************************************
 * 注意：hal不是公共api，不要在应用程序代码中使用。请参阅自述文件。soc/include/hal/readme.md中的md
 ******************************************************************************/

// ADC的HAL层（esp32s2特定部分）

#pragma once

#include "hal/adc_ll.h"
#include "hal/adc_types.h"

#include_next "hal/adc_hal.h"

#ifdef __cplusplus
extern "C" {
#endif

/*---------------------------------------------------------------
                    数字控制器设置
---------------------------------------------------------------*/
/**
 * 重置adc数字控制器滤波器。
 *
 * @param filter_idx ADC滤波器单元。
 */
#define adc_hal_digi_filter_reset(filter_idx) adc_ll_digi_filter_reset(filter_idx)

/**
 * 设置adc数字控制器滤波器系数。
 *
 * @param filter_idx ADC滤波器单元。
 * @param filter 过滤器配置。表达式：filter_data=（k-1）/k*last_data+new_data/k。设置值：（2、4、8、16、64）。
 */
void adc_hal_digi_filter_set_factor(adc_digi_filter_idx_t filter_idx, adc_digi_filter_t *filter);

/**
 * 获取adc数字控制器滤波器系数。
 *
 * @param filter_idx ADC滤波器单元。
 * @param factor 表达式：filter_data=（k-1）/k*last_data+new_data/k。设置值：（2、4、8、16、64）。
 */
void adc_hal_digi_filter_get_factor(adc_digi_filter_idx_t filter_idx, adc_digi_filter_t *filter);

/**
 * 启用/禁用adc数字控制器滤波器。对ADC数据进行滤波，以获得更高采样率的平滑数据。
 *
 * @note 滤波器将同时过滤每个ADC单元的所有已启用信道数据。
 * @param filter_idx ADC滤波器单元。
 * @param enable 如果为True，则启用筛选器，否则禁用。
 */
void adc_hal_digi_filter_enable(adc_digi_filter_idx_t filter_idx, bool enable);

/**
 * 配置adc数字控制器的监视器。
 *
 * @note 如果不支持频道信息，则不会启用监视器功能。
 * @param mon_idx ADC监视器索引。
 * @param config 请参阅“adc_digi_monitor_t”。
 */
void adc_hal_digi_monitor_config(adc_digi_monitor_idx_t mon_idx, adc_digi_monitor_t *config);

/**
 * 启用/禁用adc数字控制器的监视器。
 *
 * @note 监视器将同时监视每个ADC单元的所有已启用通道数据。
 * @param mon_idx ADC监视器索引。
 * @param enable 如果为True，则启用监视器，否则禁用。
 */
void adc_hal_digi_monitor_enable(adc_digi_monitor_idx_t mon_idx, bool enable);

#ifdef __cplusplus
}
#endif

