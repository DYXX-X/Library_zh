/*
 * SPDX文件版权文本：2015-2021浓缩咖啡系统（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */

#pragma once
#include "esp_err.h"
#include "hal/adc_types.h"

#ifdef __cplusplus
extern "C" {
#endif

#if CONFIG_IDF_TARGET_ESP32
/*---------------------------------------------------------------
                    ESP32不推荐的类型
---------------------------------------------------------------*/
/**
 * @brief ADC数字控制器（DMA模式）转换规则设置。
 */
typedef struct {
    union {
        struct {
            uint8_t atten:     2;   /*!< ADC采样电压衰减配置。衰减的修改会影响测量范围。0：测量范围0-800mV，1：测量范围0~1100mV，2：测量范围0-1350mV，3：测量范围0-2600mV。*/
            uint8_t bit_width: 2;   /*!< ADC分辨率。
-0:9位；
-1:10位；
-2:11位；-3： 12位。*/
            int8_t channel:   4;   /*!< ADC通道索引。*/
        };
        uint8_t val;                /*!<原始数据值*/
    };
} adc_digi_pattern_table_t __attribute__((deprecated));

/**
  * 解释“conv_limit_num”、“dma_eof_num”与dma输出数量之间的关系：
  *
  *     +---------------------+--------+--------+--------+| conv_mode | single | both | alter |+-------------------------+---------+--------+|触发测量时间|1|1|1|+-------------------------+--------+----------+--------+-------+|conv_limit_num |+1 |+1 |+1||dma_eof_num |+1|+2|+1|| dma输出（字节）|+2|+4|+2|+---------------------+--------+--------+--------+
  */
typedef struct {
    bool conv_limit_en;                      /*!<启用限制ADC转换时间的功能。如果ADC转换触发计数的数量等于“limit_num”，则停止转换。*/
    uint32_t conv_limit_num;                 /*!<设置ADC转换触发器数量的上限。范围：1~255。*/
    uint32_t adc1_pattern_len;               /*!<数字控制器的模式表长度。范围：0~16（0：不更改模式表设置）。定义每个SAR ADC的转换规则的模式表。每个表有16个项目，其中存储了信道选择、分辨率和衰减。当转换开始时，控制器从模式表中逐个读取转换规则。对于每个控制器，扫描序列在重复之前具有最多16个不同的规则。*/
    uint32_t adc2_pattern_len;               /*!<参考``adc1_pattern_len``*/
    adc_digi_pattern_table_t *adc1_pattern;  /*!<指向数字控制器模式表的指针。“adc1_pattern_len”定义的表大小。*/
    adc_digi_pattern_table_t *adc2_pattern;  /*!<请参阅`adc1_pattern`*/
    adc_digi_convert_mode_t conv_mode;       /*!<数字控制器的ADC转换模式。请参见`adc_digi_convert_mode_t``。*/
    adc_digi_output_format_t format;         /*!<数字控制器的ADC输出数据格式。请参见`adc_digi_output_format_t``。*/
} adc_digi_config_t __attribute__((deprecated));
#endif  //#如果配置IDF_TARGET_ESP32


#if CONFIG_IDF_TARGET_ESP32S2
/*---------------------------------------------------------------
                    ESP32S2不推荐的类型
---------------------------------------------------------------*/
/**
 * @brief ADC数字控制器（DMA模式）转换规则设置。
 */
typedef struct {
    union {
        struct {
            uint8_t atten:     2;   /*!< ADC采样电压衰减配置。衰减的修改会影响测量范围。0：测量范围0-800mV，1：测量范围0~1100mV，2：测量范围0-1350mV，3：测量范围0-2600mV。*/
            uint8_t reserved:  2;   /*!< 保留0*/
            uint8_t channel:   4;   /*!< ADC通道索引。*/
        };
        uint8_t val;                /*!<原始数据值*/
    };
} adc_digi_pattern_table_t __attribute__((deprecated));

/**
  * @brief ADC数字控制器（DMA模式）配置参数。
  *
  * 示例设置：使用ADC1通道0测量电压时，采样率要求为1 kHz：
  *
  *     +---------------------+--------+--------+--------+|采样率|1kHz |1kHz |1KHz|+-------------------------+---------+--------+|conv_mode|single|both|alter||adc1_pattern_len|1|1||dig_clk。使用锁相环|0|0|0 |dig_clk。div_num|99|99|99 | |数字时钟。div_b|0|0|0 ||dig_clk。div_a|0|0|||interval |400|400|200|+-------------------------+--------+---------+--------+|`trigger_meas_freq`|1kHz |1kHz |2kHz|+---------------------+--------+--------+--------+
  *
  * 解释“conv_limit_num”、“dma_eof_num”与dma输出数量之间的关系：
  *
  *     +---------------------+--------+--------+--------+| conv_mode | single | both | alter |+-------------------------+---------+--------+|触发测量时间|1|1|1|+-------------------------+--------+----------+--------+-------+|conv_limit_num |+1 |+1 |+1||dma_eof_num |+1|+2|+1|| dma输出（字节）|+2|+4|+2|+---------------------+--------+--------+--------+
  */
typedef struct {
    bool conv_limit_en;                      /*!<启用限制ADC转换时间的功能。如果ADC转换触发计数的数量等于“limit_num”，则停止转换。*/
    uint32_t conv_limit_num;                 /*!<设置ADC转换触发器数量的上限。范围：1~255。*/
    uint32_t adc1_pattern_len;               /*!<数字控制器的模式表长度。范围：0~16（0：不更改模式表设置）。定义每个SAR ADC的转换规则的模式表。每个表有16个项目，其中存储了信道选择、分辨率和衰减。当转换开始时，控制器从模式表中逐个读取转换规则。对于每个控制器，扫描序列在重复之前具有最多16个不同的规则。*/
    uint32_t adc2_pattern_len;               /*!<参考``adc1_pattern_len``*/
    adc_digi_pattern_table_t *adc1_pattern;  /*!<指向数字控制器模式表的指针。“adc1_pattern_len”定义的表大小。*/
    adc_digi_pattern_table_t *adc2_pattern;  /*!<请参阅`adc1_pattern`*/
    adc_digi_convert_mode_t conv_mode;       /*!<数字控制器的ADC转换模式。请参见`adc_digi_convert_mode_t``。*/
    adc_digi_output_format_t format;         /*!<数字控制器的ADC输出数据格式。请参见`adc_digi_output_format_t``。*/
    uint32_t interval;                       /*!<数字控制器触发测量的间隔时钟周期数。单位是分频时钟。范围：40 ~ 4095。表达式：`trigger_meas_freq`=`controller_clk`/2/interval。请参阅`adc_digi_clk_t`。注：每个通道的采样率也与转换模式（参见“adc_digi_convert_mode_t”）和模式表设置有关。*/
    adc_digi_clk_t dig_clk;                  /*!<ADC数字控制器时钟分频器设置。请参阅`adc_digi_clk_t`。注：DAC数字控制器的时钟使用ADC数字控制器时钟分频器。*/
    uint32_t dma_eof_num;                    /*!<adc数字控制器的DMA数量。如果测量次数达到“dma_eof_num”，则在dma中生成“dma_in_suc_eof”信号。注意：DMA链接缓冲区中的转换数据将是两个字节的倍数。*/
} adc_digi_config_t __attribute__((deprecated));

/**
 * @brief ADC数字控制器（DMA模式）中断类型选项。
 */
typedef enum {
    ADC_DIGI_INTR_MASK_MONITOR = 0x1,
    ADC_DIGI_INTR_MASK_MEAS_DONE = 0x2,
    ADC_DIGI_INTR_MASK_ALL = 0x3,
} adc_digi_intr_t __attribute__((deprecated));
FLAG_ATTR(adc_digi_intr_t)
#endif  //#如果配置IDF_TARGET_ESP32S2


#if CONFIG_IDF_TARGET_ESP32C3
/*---------------------------------------------------------------
                    ESP32C3弃用类型
---------------------------------------------------------------*/
/**
 * @brief ADC数字控制器（DMA模式）转换规则设置。
 */
typedef struct {
    union {
        struct {
            uint8_t atten:     2;   /*!< ADC采样电压衰减配置。衰减的修改会影响测量范围。0：测量范围0-800mV，1：测量范围0~1100mV，2：测量范围0-1350mV，3：测量范围0-2600mV。*/
            uint8_t channel:   3;   /*!< ADC通道索引。*/
            uint8_t unit:      1;   /*!< ADC单元索引。*/
            uint8_t reserved:  2;   /*!< 保留0*/
        };
        uint8_t val;                /*!<原始数据值*/
    };
} adc_digi_pattern_table_t __attribute__((deprecated));

typedef struct {
    bool conv_limit_en;                      /*!<启用限制ADC转换时间的功能。如果ADC转换触发计数的数量等于“limit_num”，则停止转换。*/
    uint32_t conv_limit_num;                 /*!<设置ADC转换触发器数量的上限。范围：1~255。*/
    uint32_t adc_pattern_len;                /*!<数字控制器的模式表长度。范围：0~7（0：不更改模式表设置）。定义每个SAR ADC的转换规则的模式表。每个表有7项，其中存储了信道选择、分辨率和衰减。当转换开始时，控制器从模式表中逐个读取转换规则。对于每个控制器，扫描序列在重复之前具有最多16个不同的规则。*/
    adc_digi_pattern_table_t *adc_pattern;   /*!<指向数字控制器模式表的指针。“adc_pattern_len”定义的表大小。*/
    uint32_t sample_freq_hz;  /*!< 预期ADC采样频率（Hz）。范围：611Hz~83333Hz Fs=Fd/间隔/2 Fs：采样频率；Fd：数字控制器频率，不大于5M以获得更好的性能间隔：2个测量触发信号之间的间隔，最小间隔不应小于ADC测量周期，最大间隔不应大于4095*/
} adc_digi_config_t __attribute__((deprecated));
#endif  //#如果配置IDF_TARGET_ESP32C3


#ifdef __cplusplus
}
#endif

