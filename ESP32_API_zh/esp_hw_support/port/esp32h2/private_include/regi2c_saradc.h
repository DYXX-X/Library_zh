/*
 * SPDX文件版权文本：2019-2021浓缩咖啡系统（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */

#pragma once

/**
 * @file 区域2c_saradc.h
 * @brief 模拟寄存器定义用于校准初始代码，以获得更精确的SAR ADC电压。
 *
 * 此文件列出SAR的寄存器字段，位于内部配置总线上。这些定义通过regi2c_ctrl中定义的宏使用。h、 通过adc_ll.h中的函数。
 */

#define I2C_SAR_ADC            0X69
#define I2C_SAR_ADC_HOSTID     0

#define ADC_SAR1_ENCAL_GND_ADDR 0x7
#define ADC_SAR1_ENCAL_GND_ADDR_MSB 5
#define ADC_SAR1_ENCAL_GND_ADDR_LSB 5

#define ADC_SAR2_ENCAL_GND_ADDR 0x7
#define ADC_SAR2_ENCAL_GND_ADDR_MSB 7
#define ADC_SAR2_ENCAL_GND_ADDR_LSB 7

#define ADC_SAR1_INITIAL_CODE_HIGH_ADDR 0x1
#define ADC_SAR1_INITIAL_CODE_HIGH_ADDR_MSB 0x3
#define ADC_SAR1_INITIAL_CODE_HIGH_ADDR_LSB 0x0

#define ADC_SAR1_INITIAL_CODE_LOW_ADDR  0x0
#define ADC_SAR1_INITIAL_CODE_LOW_ADDR_MSB  0x7
#define ADC_SAR1_INITIAL_CODE_LOW_ADDR_LSB  0x0

#define ADC_SAR2_INITIAL_CODE_HIGH_ADDR 0x4
#define ADC_SAR2_INITIAL_CODE_HIGH_ADDR_MSB 0x3
#define ADC_SAR2_INITIAL_CODE_HIGH_ADDR_LSB 0x0

#define ADC_SAR2_INITIAL_CODE_LOW_ADDR  0x3
#define ADC_SAR2_INITIAL_CODE_LOW_ADDR_MSB  0x7
#define ADC_SAR2_INITIAL_CODE_LOW_ADDR_LSB  0x0

#define ADC_SAR1_DREF_ADDR  0x2
#define ADC_SAR1_DREF_ADDR_MSB  0x6
#define ADC_SAR1_DREF_ADDR_LSB  0x4

#define ADC_SAR2_DREF_ADDR  0x5
#define ADC_SAR2_DREF_ADDR_MSB  0x6
#define ADC_SAR2_DREF_ADDR_LSB  0x4

#define ADC_SAR1_SAMPLE_CYCLE_ADDR 0x2
#define ADC_SAR1_SAMPLE_CYCLE_ADDR_MSB 0x2
#define ADC_SAR1_SAMPLE_CYCLE_ADDR_LSB 0x0

#define ADC_SARADC_DTEST_RTC_ADDR 0x7
#define ADC_SARADC_DTEST_RTC_ADDR_MSB 1
#define ADC_SARADC_DTEST_RTC_ADDR_LSB 0

#define ADC_SARADC_ENT_TSENS_ADDR 0x7
#define ADC_SARADC_ENT_TSENS_ADDR_MSB 2
#define ADC_SARADC_ENT_TSENS_ADDR_LSB 2

#define ADC_SARADC_ENT_RTC_ADDR 0x7
#define ADC_SARADC_ENT_RTC_ADDR_MSB 3
#define ADC_SARADC_ENT_RTC_ADDR_LSB 3

#define ADC_SARADC1_ENCAL_REF_ADDR 0x7
#define ADC_SARADC1_ENCAL_REF_ADDR_MSB 4
#define ADC_SARADC1_ENCAL_REF_ADDR_LSB 4

#define ADC_SARADC2_ENCAL_REF_ADDR 0x7
#define ADC_SARADC2_ENCAL_REF_ADDR_MSB 6
#define ADC_SARADC2_ENCAL_REF_ADDR_LSB 6

#define I2C_SARADC_TSENS_DAC 0x6
#define I2C_SARADC_TSENS_DAC_MSB 3
#define I2C_SARADC_TSENS_DAC_LSB 0

