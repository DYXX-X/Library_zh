#pragma once

#include "soc/soc_caps.h"
#include "hal/adc_types.h"
#include "sdkconfig.h"

typedef enum {
    DAC_CHANNEL_1 = 0,    /*!< DAC通道1为GPIO25（ESP32）/GPIO17（ESP32S2）*/
    DAC_CHANNEL_2 = 1,    /*!< DAC通道2为GPIO26（ESP32）/GPIO18（ESP32S2）*/
    DAC_CHANNEL_MAX,
} dac_channel_t;

/**
 * @brief 余弦波发生器振幅的倍数。最大振幅为VDD3P3_RTC。
 */
typedef enum {
    DAC_CW_SCALE_1 = 0x0,   /*!< 1/1.默认值。*/
    DAC_CW_SCALE_2 = 0x1,   /*!< 1/2. */
    DAC_CW_SCALE_4 = 0x2,   /*!< 1/4. */
    DAC_CW_SCALE_8 = 0x3,   /*!< 1/8. */
} dac_cw_scale_t;

/**
 * @brief 设置余弦波发生器输出的相位。
 */
typedef enum {
    DAC_CW_PHASE_0   = 0x2, /*!< 相移+0°*/
    DAC_CW_PHASE_180 = 0x3, /*!< 相移+180°*/
} dac_cw_phase_t;

/**
 * @brief 在DAC模块中配置余弦波发生器功能。
 */
typedef struct {
    dac_channel_t en_ch;    /*!< 启用DAC通道的余弦波发生器。*/
    dac_cw_scale_t scale;   /*!< 设置余弦波发生器输出的振幅。*/
    dac_cw_phase_t phase;   /*!< 设置余弦波发生器输出的相位。*/
    uint32_t freq;          /*!< 设置余弦波发生器输出的频率。范围：130（130Hz）~ 55000（100KHz）。*/
    int8_t offset;          /*!< 设置余弦波发生器输出直流分量的电压值。注意：不合理的设置会导致波形过饱和。范围：-128~127。*/
} dac_cw_config_t;

#if CONFIG_IDF_TARGET_ESP32S2 || CONFIG_IDF_TARGET_ESP32S3

/**
 * @brief DAC数字控制器（DMA模式）工作模式。
 */
typedef enum {
    DAC_CONV_NORMAL,        /*!< DMA缓冲器中的数据同时输出到DAC的使能通道。*/
    DAC_CONV_ALTER,         /*!< DMA缓冲器中的数据交替地输出到DAC的使能通道。*/
    DAC_CONV_MAX
} dac_digi_convert_mode_t;

/**
 * @brief DAC数字控制器（DMA模式）配置参数。
 */
typedef struct {
    dac_digi_convert_mode_t mode;   /*!<DAC数字控制器（DMA模式）工作模式。请参见``dac_digi_overt_mode_t``。*/
    uint32_t interval;          /*!<DAC数字控制器输出电压的间隔时钟周期数。单位是分频时钟。范围：1~4095。表达式：`dac_output_freq`=`controller_clk`/interval。请参阅`adc_digi_clk_t`。注：每个通道的采样率也与转换模式（参见“dac_digi_cover_mode_t”）和模式表设置有关。*/
    adc_digi_clk_t dig_clk;     /*!<DAC数字控制器时钟分频器设置。请参阅`adc_digi_clk_t`。注：DAC数字控制器的时钟使用ADC数字控制器时钟分频器。*/
} dac_digi_config_t;

#endif //CONFIG_IDF_TARGET_ESP32S2

