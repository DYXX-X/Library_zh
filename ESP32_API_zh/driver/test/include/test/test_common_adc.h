/*
 * SPDX文件版权文本：2015-2021浓缩咖啡系统（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */

#pragma once

#include "driver/adc.h"

/**@{*/
/**
 * 通过连接内部上拉和下拉，将ADC通道输入连接到中间（1.4V）。
 *
 * `tie_middle`：1.4v`tie_high`：3.3v`tie_low `:0v；
 *
 * @param adc_unit_t ADC单元。
 * @param adc_channel_t ADC通道。
 */
void adc_fake_tie_middle(adc_unit_t adc_unit, adc_channel_t channel);
void adc_fake_tie_high(adc_unit_t adc_unit, adc_channel_t channel);
void adc_fake_tie_low(adc_unit_t adc_unit, adc_channel_t channel);
void adc_io_normal(adc_unit_t adc_unit, adc_channel_t channel);
/**@}*/

