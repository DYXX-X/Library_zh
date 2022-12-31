/*
 * SPDX文件版权文本：2017-2021浓缩咖啡系统（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>
#include "esp_err.h"
#include "sdkconfig.h"

//这是在efuse中烧毁的ADC校准值版本
#define ESP_EFUSE_ADC_CALIB_VER     2

#define RTCCALIB_ESP32S2_ADCCOUNT 2
#define RTCCALIB_ESP32S2_ATTENCOUNT 4

#define RTCCALIB_V1_PARAM_VLOW 0
#define RTCCALIB_V1_PARAM_VHIGH 1
#define RTCCALIB_V2_PARAM_VHIGH 0
#define RTCCALIB_V2_PARAM_VINIT 1

// 这些是标签。直接使用它们或使用esp_efuse_rtc_table_get_tag计算
// 相应的标签。
#define RTCCALIB_V1IDX_A10L 1
#define RTCCALIB_V1IDX_A11L 2
#define RTCCALIB_V1IDX_A12L 3
#define RTCCALIB_V1IDX_A13L 4
#define RTCCALIB_V1IDX_A20L 5
#define RTCCALIB_V1IDX_A21L 6
#define RTCCALIB_V1IDX_A22L 7
#define RTCCALIB_V1IDX_A23L 8
#define RTCCALIB_V1IDX_A10H 9
#define RTCCALIB_V1IDX_A11H 10
#define RTCCALIB_V1IDX_A12H 11
#define RTCCALIB_V1IDX_A13H 12
#define RTCCALIB_V1IDX_A20H 13
#define RTCCALIB_V1IDX_A21H 14
#define RTCCALIB_V1IDX_A22H 15
#define RTCCALIB_V1IDX_A23H 16
#define RTCCALIB_V2IDX_A10H 17
#define RTCCALIB_V2IDX_A11H 18
#define RTCCALIB_V2IDX_A12H 19
#define RTCCALIB_V2IDX_A13H 20
#define RTCCALIB_V2IDX_A20H 21
#define RTCCALIB_V2IDX_A21H 22
#define RTCCALIB_V2IDX_A22H 23
#define RTCCALIB_V2IDX_A23H 24
#define RTCCALIB_V2IDX_A10I 25
#define RTCCALIB_V2IDX_A11I 26
#define RTCCALIB_V2IDX_A12I 27
#define RTCCALIB_V2IDX_A13I 28
#define RTCCALIB_V2IDX_A20I 29
#define RTCCALIB_V2IDX_A21I 30
#define RTCCALIB_V2IDX_A22I 31
#define RTCCALIB_V2IDX_A23I 32
#define RTCCALIB_IDX_TMPSENSOR 33

/**
 * @brief 获取rtc校准版本。
 */
int esp_efuse_rtc_table_read_calib_version(void);

/**
 * @brief Helper函数，用于根据人类可读参数计算标记。标记用于索引efuse中所需的数据。例如，（1，1，3，1）产生标签RTCCALIB_V1IDX_A13H。当adc_num-atten组合具有多个efuse值时，额外参数用于识别。
 * @param adc_channel_num ADC通道的逐字编号。对于通道1，使用1而不是0。
 * @param atten 衰减。使用枚举值。
 * @param version 要为其编制索引的方案的版本。
 * @param extra_params 每个版本的定义不同。
 * */
int esp_efuse_rtc_table_get_tag(int version, int adc_channel_num, int atten, int extra_params);

/**
 * @brief 从efuse获取一个原始值，并执行有符号位分析
 * @param tag 使用esp_efuse_rtc_table_get_tag获得的标记
 *
 * */
int esp_efuse_rtc_table_get_raw_efuse_value(int tag);

/**
 * @brief 从efuse中获取一个原始值，并解析它以获得它表示的原始数字。
 *
 * @param tag 使用esp_efuse_rtc_table_get_tag获得的标记
 * @param use_zero_inputs 在解析数字之前不执行原始值提取，而是像从efuse读取所有零一样继续。
 *
 * */
int esp_efuse_rtc_table_get_parsed_efuse_value(int tag, bool skip_efuse_reading);

#ifdef __cplusplus
}
#endif

