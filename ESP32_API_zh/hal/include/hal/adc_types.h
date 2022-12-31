/*
 * SPDX文件版权文本：2020-2021浓缩咖啡系统（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */
#pragma once

#include <stdbool.h>
#include <stdint.h>
#include "sdkconfig.h"
#include "soc/soc_caps.h"
#include "esp_attr.h"

/**
 * @brief ADC单元枚举。
 *
 * @note  对于ADC数字控制器（DMA模式），ESP32不支持“ADC_UNIT_2”、“ADC_UNIT_BOTH”、“ADC _UNIT_ALTER”。
 */
typedef enum {
    ADC_UNIT_1 = 1,          /*!< SAR ADC 1. */
    ADC_UNIT_2 = 2,          /*!< SAR ADC 2. */
    ADC_UNIT_BOTH = 3,       /*!< SAR ADC 1和2。*/
    ADC_UNIT_ALTER = 7,      /*!< SAR ADC 1和2替代模式。*/
    ADC_UNIT_MAX,
} adc_unit_t;

/**
 * @brief ADC通道句柄。请参见`adc1_channel_t``、`adc2_channel_t``。
 *
 * @note  对于ESP32 ADC1，不要使用`ADC_CHANNEL_8`、`ADC_HANNEL_9`。请参见`adc1_channel_t``。
 */
typedef enum {
    ADC_CHANNEL_0 = 0, /*!< ADC通道*/
    ADC_CHANNEL_1,     /*!< ADC通道*/
    ADC_CHANNEL_2,     /*!< ADC通道*/
    ADC_CHANNEL_3,     /*!< ADC通道*/
    ADC_CHANNEL_4,     /*!< ADC通道*/
    ADC_CHANNEL_5,     /*!< ADC通道*/
    ADC_CHANNEL_6,     /*!< ADC通道*/
    ADC_CHANNEL_7,     /*!< ADC通道*/
    ADC_CHANNEL_8,     /*!< ADC通道*/
    ADC_CHANNEL_9,     /*!< ADC通道*/
    ADC_CHANNEL_MAX,
} adc_channel_t;

/**
 * @brief ADC衰减参数。不同的参数决定ADC的范围。请参见`adc1_config_channel_atten``。
 */
typedef enum {
    ADC_ATTEN_DB_0   = 0,  /*!<无输入衰减，ADC可测量高达约800 mV。*/
    ADC_ATTEN_DB_2_5 = 1,  /*!<ADC的输入电压将衰减，从而将测量范围扩展约2.5 dB（1.33 x）*/
    ADC_ATTEN_DB_6   = 2,  /*!<ADC的输入电压将衰减，从而将测量范围扩展约6 dB（2 x）*/
    ADC_ATTEN_DB_11  = 3,  /*!<ADC的输入电压将衰减，从而将测量范围扩展约11 dB（3.55 x）*/
    ADC_ATTEN_MAX,
} adc_atten_t;

/**
 * @brief ADC分辨率设置选项。
 * @note  仅在单读模式下使用
 */
typedef enum {
#if CONFIG_IDF_TARGET_ESP32
    ADC_WIDTH_BIT_9  = 0, /*!< ADC捕获宽度为9Bit。*/
    ADC_WIDTH_BIT_10 = 1, /*!< ADC捕获宽度为10Bit。*/
    ADC_WIDTH_BIT_11 = 2, /*!< ADC捕获宽度为11Bit。*/
    ADC_WIDTH_BIT_12 = 3, /*!< ADC捕获宽度为12Bit。*/
#elif SOC_ADC_MAX_BITWIDTH == 12
    ADC_WIDTH_BIT_12 = 3, /*!< ADC捕获宽度为12Bit。*/
#elif SOC_ADC_MAX_BITWIDTH == 13
    ADC_WIDTH_BIT_13 = 4, /*!< ADC捕获宽度为13Bit。*/
#endif
    ADC_WIDTH_MAX,
} adc_bits_width_t;

/**
 * @brief ADC数字控制器（DMA模式）工作模式。
 */
typedef enum {
    ADC_CONV_SINGLE_UNIT_1 = 1,  ///<仅使用ADC1进行转换
    ADC_CONV_SINGLE_UNIT_2 = 2,  ///<仅使用ADC2进行转换
    ADC_CONV_BOTH_UNIT     = 3,  ///<同时使用ADC1和ADC2进行转换
    ADC_CONV_ALTER_UNIT    = 7,  ///<依次使用ADC1和ADC2进行转换。e、 g.ADC1->ADC2->ADC1->ADC 2。。。。。
    ADC_CONV_UNIT_MAX,
} adc_digi_convert_mode_t;

/**
 * @brief ADC数字控制器（DMA模式）输出数据格式选项。
 */
typedef enum {
    ADC_DIGI_FORMAT_12BIT __attribute__((deprecated)),  /*!<ADC到DMA数据格式，[15:12]信道，[11:0]-12位ADC数据（“ADC_digi_output_data_t”）。注：用于单转换模式。*/
    ADC_DIGI_FORMAT_11BIT __attribute__((deprecated)),  /*!<ADC到DMA数据格式，[15]-ADC单元，[14:11]-通道，[10:0]-11位ADC数据（“ADC_digi_output_data_t”）。注意：对于多或多转换模式。*/
    ADC_DIGI_FORMAT_MAX   __attribute__((deprecated)),

    ADC_DIGI_OUTPUT_FORMAT_TYPE1,   ///<请参见`adc_digi_output_data_t.type1`
    ADC_DIGI_OUTPUT_FORMAT_TYPE2,   ///<请参见`adc_digi_output_data_t.type2`
} adc_digi_output_format_t;

/**
 * @brief ADC数字控制器模式配置
 */
typedef struct {
    uint8_t atten;      ///<此ADC通道的衰减
    uint8_t channel;    ///<ADC通道
    uint8_t unit;       ///<ADC单元
    uint8_t bit_width;  ///<ADC输出位宽
} adc_digi_pattern_config_t;

/*---------------------------------------------------------------
                    输出格式
---------------------------------------------------------------*/
#if CONFIG_IDF_TARGET_ESP32 || CONFIG_IDF_TARGET_ESP32S2
/**
 * @brief ADC数字控制器（DMA模式）输出数据格式。用于分析采集的ADC（DMA）数据。
 * @note  ESP32:只有“type1”有效。ADC2不支持DMA模式。
 * @note  ESP32-S2:成员“channel”可用于判断ADC数据的有效性，因为仲裁器的角色可能会获得无效的ADC数据。
 */
typedef struct {
    union {
        struct {
            uint16_t data:     12;  /*!<ADC实际输出数据信息。分辨率：12位。*/
            uint16_t channel:   4;  /*!<ADC通道索引信息。*/
        } type1;
        struct {
            uint16_t data:     11;  /*!<ADC实际输出数据信息。分辨率：11位。*/
            uint16_t channel:   4;  /*!<ADC通道索引信息。对于ESP32-S2：如果（信道<ADC_channel_MAX），则数据有效。如果（通道>ADC_channel_MAX），则数据无效。*/
            uint16_t unit:      1;  /*!<ADC单元索引信息。0:ADC1；1： ADC2。*/
        } type2;                    /*!<当配置的输出格式为11bit时`ADC_DIGI_FORMAT_11BIT`*/
        uint16_t val;               /*!<原始数据值*/
    };
} adc_digi_output_data_t;

#elif CONFIG_IDF_TARGET_ESP32C3 || CONFIG_IDF_TARGET_ESP32H2
/**
 * @brief ADC数字控制器（DMA模式）输出数据格式。用于分析采集的ADC（DMA）数据。
 */
typedef struct {
    union {
        struct {
            uint32_t data:          12; /*!<ADC实际输出数据信息。分辨率：12位。*/
            uint32_t reserved12:    1;  /*!<保留12。*/
            uint32_t channel:       3;  /*!<ADC通道索引信息。如果（通道<ADC_channel_MAX），则数据有效。如果（通道>ADC_channel_MAX），则数据无效。*/
            uint32_t unit:          1;  /*!<ADC单元索引信息。0:ADC1；1： ADC2。*/
            uint32_t reserved17_31: 15; /*!<保留17。*/
        } type2;                         /*!<当配置的输出格式为12bit时`ADC_DIGI_FORMAT_11BIT`*/
        uint32_t val;                   /*!<原始数据值*/
    };
} adc_digi_output_data_t;

#elif CONFIG_IDF_TARGET_ESP32S3
/**
 * @brief ADC数字控制器（DMA模式）输出数据格式。用于分析采集的ADC（DMA）数据。
 */
typedef struct {
    union {
        struct {
            uint32_t data:          13; /*!<ADC实际输出数据信息。分辨率：13位。*/
            uint32_t channel:       4;  /*!<ADC通道索引信息。如果（通道<ADC_channel_MAX），则数据有效。如果（通道>ADC_channel_MAX），则数据无效。*/
            uint32_t unit:          1;  /*!<ADC单元索引信息。0:ADC1；1： ADC2。*/
            uint32_t reserved17_31: 14; /*!<保留17。*/
        } type2;                         /*!<当配置的输出格式为12bit时`ADC_DIGI_FORMAT_11BIT`*/
        uint32_t val;                   /*!<原始数据值*/
    };
} adc_digi_output_data_t;
#endif


#if SOC_ADC_ARBITER_SUPPORTED
/*---------------------------------------------------------------
                    仲裁人
---------------------------------------------------------------*/
/**
 * @brief ADC仲裁器工作模式选项。
 *
 * @note ESP32-S2:只有ADC2支持仲裁器。
 */
typedef enum {
    ADC_ARB_MODE_SHIELD,/*!<强制屏蔽仲裁器，选择要工作的最高优先级控制器。*/
    ADC_ARB_MODE_FIX,   /*!<固定优先级开关控制器模式。*/
    ADC_ARB_MODE_LOOP,  /*!<回路优先级开关控制器模式。每个控制器具有相同的优先级，在测量完成后，仲裁器将切换到下一个控制器。*/
} adc_arbiter_mode_t;

/**
 * @brief ADC仲裁器工作模式和优先级设置。
 *
 * @note ESP32-S2:只有ADC2支持仲裁器。
 */
typedef struct {
    adc_arbiter_mode_t mode; /*!<请参阅`adc_arbiter_mode_t``。注意：仅支持ADC2。*/
    uint8_t rtc_pri;        /*!<RTC控制器优先级。范围：0~2。*/
    uint8_t dig_pri;        /*!<数字控制器优先级。范围：0~2。*/
    uint8_t pwdet_pri;      /*!<Wi-Fi控制器优先级。范围：0~2。*/
} adc_arbiter_t;

/**
 * @brief ADC仲裁器默认配置。
 *
 * @note ESP32S2：只有ADC2支持（需要）仲裁器。
 */
#define ADC_ARBITER_CONFIG_DEFAULT() { \
    .mode = ADC_ARB_MODE_FIX, \
    .rtc_pri = 1, \
    .dig_pri = 0, \
    .pwdet_pri = 2, \
}
#endif  //#如果SOC_ADC_ARBITER_SUPPORTED

#if SOC_ADC_FILTER_SUPPORTED
/*---------------------------------------------------------------
                    滤器
---------------------------------------------------------------*/
/**
 * @brief ADC数字控制器（DMA模式）滤波器索引选项。
 *
 * @note  对于ESP32-S2，ADC的滤波器对象是固定的。
 */
typedef enum {
    ADC_DIGI_FILTER_IDX0 = 0, /*!<过滤器索引0。对于ESP32-S2，它只能用于同时过滤ADC1单元的所有启用信道。*/
    ADC_DIGI_FILTER_IDX1,     /*!<滤波器索引1。对于ESP32-S2，它只能用于同时对ADC2单元的所有启用信道进行滤波。*/
    ADC_DIGI_FILTER_IDX_MAX
} adc_digi_filter_idx_t;

/**
 * @brief ADC数字控制器（DMA模式）滤波器类型选项。表达式：filter_data=（k-1）/k last_data+new_data/k。
 */
typedef enum {
#if CONFIG_IDF_TARGET_ESP32C3 || CONFIG_IDF_TARGET_ESP32H2
    ADC_DIGI_FILTER_DIS = -1,  /*!< 禁用筛选器*/
#endif
    ADC_DIGI_FILTER_IIR_2 = 0, /*!<滤波器模式为一阶IIR滤波器。系数为2。*/
    ADC_DIGI_FILTER_IIR_4,     /*!<滤波器模式为一阶IIR滤波器。系数为4。*/
    ADC_DIGI_FILTER_IIR_8,     /*!<滤波器模式为一阶IIR滤波器。系数为8。*/
    ADC_DIGI_FILTER_IIR_16,    /*!<滤波器模式为一阶IIR滤波器。系数为16。*/
    ADC_DIGI_FILTER_IIR_64,    /*!<滤波器模式为一阶IIR滤波器。系数为64。*/
    ADC_DIGI_FILTER_IIR_MAX
} adc_digi_filter_mode_t;

/**
 * @brief ADC数字控制器（DMA模式）滤波器配置。
 *
 * @note  对于ESP32-S2，ADC的滤波器对象是固定的。
 * @note  对于ESP32-S2，过滤器对象始终是所有启用的通道。
 */
typedef struct {
    adc_unit_t adc_unit;        /*!<设置滤波器的adc单元编号。对于ESP32-S2，滤波器IDX0/IDX1只能用于同时对ADC1/ADC2单元的所有启用信道进行滤波。*/
    adc_channel_t channel;      /*!<设置滤波器的adc通道编号。对于ESP32-S2，始终为`ADC_CHANNEL_MAX`*/
    adc_digi_filter_mode_t mode;/*!<设置滤波器的adc滤波器模式。请参见``adc_digi_filter_mode_t``。*/
} adc_digi_filter_t;
#endif  // #如果SOC_ADC_FILTER_SUPPORTED

#if SOC_ADC_MONITOR_SUPPORTED
/*---------------------------------------------------------------
                    班长
---------------------------------------------------------------*/
/**
 * @brief ADC数字控制器（DMA模式）监控索引选项。
 *
 * @note  对于ESP32-S2，ADC的监控对象是固定的。
 */
typedef enum {
    ADC_DIGI_MONITOR_IDX0 = 0, /*!<监视器索引0。对于ESP32-S2，它只能用于同时监视ADC1单元的所有启用信道。*/
    ADC_DIGI_MONITOR_IDX1,     /*!<监视器索引1。对于ESP32-S2，它只能用于同时监视ADC2单元的所有启用信道。*/
    ADC_DIGI_MONITOR_IDX_MAX
} adc_digi_monitor_idx_t;

/**
 * @brief 设置adc数字控制器的监控模式。MONITOR_HIGH：如果ADC_OUT>阈值，则生成监视器中断。MONITOR_LOW：如果ADC_OUT<阈值，则生成监视器中断。
 */
typedef enum {
#if CONFIG_IDF_TARGET_ESP32C3 || CONFIG_IDF_TARGET_ESP32H2
    ADC_DIGI_MONITOR_DIS = 0,  /*!<禁用监视器。*/
    ADC_DIGI_MONITOR_EN,       /*!<如果ADC_OUT<阈值，则生成监视器中断。*/
                               /*!<如果ADC_OUT>阈值，则生成监视器中断。*/
#else
    ADC_DIGI_MONITOR_HIGH = 0,  /*!<如果ADC_OUT>阈值，则生成监视器中断。*/
    ADC_DIGI_MONITOR_LOW,       /*!<如果ADC_OUT<阈值，则生成监视器中断。*/
#endif
    ADC_DIGI_MONITOR_MAX
} adc_digi_monitor_mode_t;

/**
 * @brief ADC数字控制器（DMA模式）监视器配置。
 *
 * @note  对于ESP32-S2，ADC的监控对象是固定的。
 * @note  对于ESP32-S2，监视器对象始终是所有启用的通道。
 */
typedef struct {
    adc_unit_t adc_unit;            /*!<设置监视器的adc单元编号。对于ESP32-S2，监视器IDX0/IDX1只能用于同时监视ADC1/ADC2单元的所有启用信道。*/
    adc_channel_t channel;          /*!<设置监视器的adc通道编号。对于ESP32-S2，始终为`ADC_CHANNEL_MAX`*/
    adc_digi_monitor_mode_t mode;   /*!<设置adc监视器模式。请参见`adc_digi_monitor_mode_t``。*/
#if CONFIG_IDF_TARGET_ESP32C3 || CONFIG_IDF_TARGET_ESP32H2
    uint32_t h_threshold;             /*!<设置adc数字控制器的监控阈值。*/
    uint32_t l_threshold;             /*!<设置adc数字控制器的监控阈值。*/
#else
    uint32_t threshold;             /*!<设置adc数字控制器的监控阈值。*/
#endif
} adc_digi_monitor_t;
#endif  //#如果SOC_ADC_MONITOR_SUPPORTED

/*---------------------------------------------------------------
            不推荐TODO:IDF-3610
---------------------------------------------------------------*/
#ifdef CONFIG_IDF_TARGET_ESP32
/**
 * @brief ESP32 ADC DMA源选择。
 */
#else
/**
 * @brief ESP32 ADC DMA源选择。
 *
 * @deprecated  不适用于ESP32-S2，因为ESP32-S2不使用I2S DMA。
 */
#endif
typedef enum {
    ADC_I2S_DATA_SRC_IO_SIG = 0, /*!< 来自GPIO矩阵信号的I2S数据*/
    ADC_I2S_DATA_SRC_ADC = 1,    /*!< 来自ADC的I2S数据*/
    ADC_I2S_DATA_SRC_MAX,
} adc_i2s_source_t;

#if CONFIG_IDF_TARGET_ESP32S2
/**
 * @brief ADC数字控制器（DMA模式）时钟系统设置。计算公式：controller_clk=（`APLL'或`APB'）/（div_num+div_a/div_b+1）。
 *
 * @note: DAC数字控制器的时钟使用ADC数字控制器时钟分频器。
 */
typedef struct {
    bool use_apll;      /*!<true：使用APLL时钟；false：使用APB时钟。*/
    uint32_t div_num;   /*!<除法系数。范围：0~255。注意：当使用更高频率的时钟（分频系数小于9）时，ADC读数将略有偏移。*/
    uint32_t div_b;     /*!<除法系数。范围：1~63。*/
    uint32_t div_a;     /*!<除法系数。范围：0~63。*/
} adc_digi_clk_t;
#endif

