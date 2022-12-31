/*
 * SPDX文件版权文本：2015-2021浓缩咖啡系统（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */

#pragma once

#include <stdint.h>
#include <stdbool.h>
#include "esp_err.h"
#include "sdkconfig.h"
#include "driver/gpio.h"
#include "hal/adc_types.h"

#ifdef __cplusplus
extern "C" {
#endif

#if CONFIG_IDF_TARGET_ESP32
/****“adc1_channel_t”将被弃用，合并为“adc_channel_t”********/
typedef enum {
    ADC1_CHANNEL_0 = 0, /*!< ADC1通道0为GPIO36*/
    ADC1_CHANNEL_1,     /*!< ADC1通道1为GPIO37*/
    ADC1_CHANNEL_2,     /*!< ADC1通道2为GPIO38*/
    ADC1_CHANNEL_3,     /*!< ADC1通道3为GPIO39*/
    ADC1_CHANNEL_4,     /*!< ADC1通道4为GPIO32*/
    ADC1_CHANNEL_5,     /*!< ADC1通道5为GPIO33*/
    ADC1_CHANNEL_6,     /*!< ADC1通道6为GPIO34*/
    ADC1_CHANNEL_7,     /*!< ADC1通道7为GPIO35*/
    ADC1_CHANNEL_MAX,
} adc1_channel_t;
#elif CONFIG_IDF_TARGET_ESP32S2 || CONFIG_IDF_TARGET_ESP32S3 // TODO ESP32-S3通道错误IDF-1776
/****“adc1_channel_t”将被弃用，合并为“adc_channel_t”********/
typedef enum {
    ADC1_CHANNEL_0 = 0, /*!< ADC1通道0为GPIO1*/
    ADC1_CHANNEL_1,     /*!< ADC1通道1为GPIO2*/
    ADC1_CHANNEL_2,     /*!< ADC1通道2为GPIO3*/
    ADC1_CHANNEL_3,     /*!< ADC1通道3为GPIO4*/
    ADC1_CHANNEL_4,     /*!< ADC1通道4为GPIO5*/
    ADC1_CHANNEL_5,     /*!< ADC1通道5为GPIO6*/
    ADC1_CHANNEL_6,     /*!< ADC1通道6为GPIO7*/
    ADC1_CHANNEL_7,     /*!< ADC1通道7为GPIO8*/
    ADC1_CHANNEL_8,     /*!< ADC1通道8为GPIO9*/
    ADC1_CHANNEL_9,     /*!< ADC1通道9为GPIO10*/
    ADC1_CHANNEL_MAX,
} adc1_channel_t;
#elif CONFIG_IDF_TARGET_ESP32C3 || CONFIG_IDF_TARGET_ESP32H2
/****“adc1_channel_t”将被弃用，合并为“adc_channel_t”********/
typedef enum {
    ADC1_CHANNEL_0 = 0, /*!< ADC1通道0为GPIO0*/
    ADC1_CHANNEL_1,     /*!< ADC1通道1为GPIO1*/
    ADC1_CHANNEL_2,     /*!< ADC1通道2为GPIO2*/
    ADC1_CHANNEL_3,     /*!< ADC1通道3为GPIO3*/
    ADC1_CHANNEL_4,     /*!< ADC1通道4为GPIO4*/
    ADC1_CHANNEL_MAX,
} adc1_channel_t;
#endif // CONFIG_IDF_TARGET_*

#if CONFIG_IDF_TARGET_ESP32 || CONFIG_IDF_TARGET_ESP32S2 || CONFIG_IDF_TARGET_ESP32S3 // TODO ESP32-S3通道错误IDF-1776
/****“adc2_channel_t”将被弃用，合并为“adc_channel_t”********/
typedef enum {
    ADC2_CHANNEL_0 = 0, /*!< ADC2通道0为GPIO4（ESP32）、GPIO11（ESP32-S2）*/
    ADC2_CHANNEL_1,     /*!< ADC2信道1为GPIO0（ESP32）、GPIO12（ESP32-S2）*/
    ADC2_CHANNEL_2,     /*!< ADC2通道2为GPIO2（ESP32）、GPIO13（ESP32-S2）*/
    ADC2_CHANNEL_3,     /*!< ADC2信道3为GPIO15（ESP32）、GPIO14（ESP32-S2）*/
    ADC2_CHANNEL_4,     /*!< ADC2信道4为GPIO13（ESP32）、GPIO15（ESP32-S2）*/
    ADC2_CHANNEL_5,     /*!< ADC2通道5为GPIO12（ESP32）、GPIO16（ESP32-S2）*/
    ADC2_CHANNEL_6,     /*!< ADC2信道6为GPIO14（ESP32）、GPIO17（ESP32-S2）*/
    ADC2_CHANNEL_7,     /*!< ADC2通道7为GPIO27（ESP32）、GPIO18（ESP32-S2）*/
    ADC2_CHANNEL_8,     /*!< ADC2通道8为GPIO25（ESP32）、GPIO19（ESP32-S2）*/
    ADC2_CHANNEL_9,     /*!< ADC2通道9为GPIO26（ESP32）、GPIO20（ESP32-S2）*/
    ADC2_CHANNEL_MAX,
} adc2_channel_t;
#elif CONFIG_IDF_TARGET_ESP32C3 || CONFIG_IDF_TARGET_ESP32H2
/****“adc2_channel_t”将被弃用，合并为“adc_channel_t”********/
typedef enum {
    ADC2_CHANNEL_0 = 0, /*!< ADC2通道0为GPIO5*/
    ADC2_CHANNEL_MAX,
} adc2_channel_t;
#endif


/**
 * @brief ADC rtc控制器衰减选项。
 *
 * @note  此定义仅用于向后兼容
 */
#define ADC_ATTEN_0db   ADC_ATTEN_DB_0
#define ADC_ATTEN_2_5db ADC_ATTEN_DB_2_5
#define ADC_ATTEN_6db   ADC_ATTEN_DB_6
#define ADC_ATTEN_11db  ADC_ATTEN_DB_11

/**
 * 当前版本ADC的默认（最大）位宽。还可以通过SOC_caps.h中定义的“SOC_ADC_MAX_bitwidth”获取最大位宽。
 */
#define ADC_WIDTH_BIT_DEFAULT   (ADC_WIDTH_MAX-1)

//此定义仅用于向后兼容
#define ADC_WIDTH_9Bit  ADC_WIDTH_BIT_9
#define ADC_WIDTH_10Bit ADC_WIDTH_BIT_10
#define ADC_WIDTH_11Bit ADC_WIDTH_BIT_11
#define ADC_WIDTH_12Bit ADC_WIDTH_BIT_12

/**
 * @brief ADC数字控制器编码选项。
 *
 * @deprecated ESP32-S2不使用I2S DMA。改为调用``adc_digi_output_format_t``。
 */
typedef enum {
    ADC_ENCODE_12BIT,        /*!< ADC到DMA数据格式，[15:12]-通道[11:0]-12位ADC数据*/
    ADC_ENCODE_11BIT,        /*!< ADC到DMA数据格式，[15]-单元，[14:11]-通道[10:0]-11位ADC数据*/
    ADC_ENCODE_MAX,
} adc_i2s_encode_t;

/*---------------------------------------------------------------
                    常用设置
---------------------------------------------------------------*/

/**
 * @brief 启用ADC电源
 * @deprecated 请改用adc_power_acquire和adc_power_release。
 */
void adc_power_on(void) __attribute__((deprecated));

/**
 * @brief 关闭SAR ADC
 * @deprecated 请改用adc_power_acquire和adc_power_release。此功能将强制关闭ADC的电源。不推荐使用此功能，因为强制关闭ADC电源可能会中断使用ADC的其他组件的操作。
 */
void adc_power_off(void) __attribute__((deprecated));

/**
 * @brief 增加ADC模块的使用计数器。当计数器大于0时，ADC将保持通电状态。使用ADC后调用ADC_power_release。
 */
void adc_power_acquire(void);

/**
 * @brief 减少ADC模块的使用计数器。当计数器大于0时，ADC将保持通电状态。使用ADC后调用此函数。
 */
void adc_power_release(void);

/*---------------------------------------------------------------
                    ADC单读设置
---------------------------------------------------------------*/
/**
 * @brief 获取特定ADC1通道的GPIO编号。
 *
 * @param channel 获取GPIO编号的通道
 * @param gpio_num 保存GPIO编号的输出缓冲区
 *
 * @return
 *   -ESP_OK（如果成功）
 *   -如果通道无效，则为ESP_ERR_INVALID_ARG
 */
esp_err_t adc1_pad_get_io_num(adc1_channel_t channel, gpio_num_t *gpio_num);

/**
 * @brief 设置ADC1上特定信道的衰减，并配置其相关的GPIO引脚多路复用器。
 *
 * 默认ADC电压用于衰减0 dB，并在下表中列出。通过设置更高的衰减，可以读取更高的电压。
 *
 * 由于ADC特性，在下表所示的“建议范围”内可获得最准确的结果。
 *
 *     +----------+-------------+-----------------+| |衰减|建议范围| | SoC |（dB）|（mV）|+===============+============+=====+|||0|100~950||+----------------+----------------+||2.5|100~1250||ESP32+----------------+||6|150~1750 ||+-------------+||11|150~2450 |+---------------+---------------+| |0|0~750 ||+---------------+----------------+||2.5 |0~1050 ||ESP32-S2+---------------+-------------------+||6 |0~1300 ||+------------+----------------+||11 |0~2500 |+----------+-------------+-----------------+
 *
 * 为了获得最大精度，请使用ADC校准API并在这些推荐范围内测量电压。
 *
 * @note 对于任何给定的通道，必须在第一次为该通道调用`adc1_get_raw（）``之前调用该函数。
 *
 * @note 可以多次调用此函数以同时配置多个ADC通道。您只能在配置频道后调用``adc1_get_raw（）``。
 *
 * @param channel 要配置的ADC1通道
 * @param atten  衰减水平
 *
 * @return
 *     -ESP_OK成功
 *     -ESP_ERR_INVALID_ARG参数错误
 */
esp_err_t adc1_config_channel_atten(adc1_channel_t channel, adc_atten_t atten);

/**
 * @brief 配置ADC1捕获宽度，同时启用ADC1的输出反转。该配置适用于ADC1的所有通道
 * @param width_bit ADC1的位捕获宽度
 *
 * @return
 *     -ESP_OK成功
 *     -ESP_ERR_INVALID_ARG参数错误
 */
esp_err_t adc1_config_width(adc_bits_width_t width_bit);

/**
 * @brief 从单个通道读取ADC1读数。
 * @note ESP32：当SARADC1、SARADC2、HALL传感器和AMP传感器的电源开关打开时，GPIO36和GPIO39的输入将被下拉约80ns。当为任何这些外设启用电源时，忽略GPIO36和GPIO39的输入。有关此问题的说明，请参阅“ECO_and_Workarounds_for_Bugs_in_ESP32”的3.11节。作为解决方法，在应用程序中调用adc_power_acquire（）。这将导致更高的功耗（约1mA），但将消除GPIO36和GPIO39上的故障。
 *
 * @note 在第一次调用此函数之前调用``adc1_config_width（）``。
 *
 * @note 对于任何给定的通道，必须在第一次调用此函数之前调用adc1_config_channel_atten（通道）。配置新通道不会阻止读取先前配置的通道。
 *
 * @param  channel 要读取的ADC1通道
 *
 * @return
 *     --1：参数错误
 *     -其他：ADC1通道读数。
 */
int adc1_get_raw(adc1_channel_t channel);

#if CONFIG_IDF_TARGET_ESP32 || CONFIG_IDF_TARGET_ESP32S2 || CONFIG_IDF_TARGET_ESP32S3
//TODO IDF-3610，用合适的盖子替换
/**
 * @brief 设置ADC数据反转
 * @param adc_unit ADC单元索引
 * @param inv_en 是否启用数据反转
 * @return
 *     -ESP_OK成功
 *     -ESP_ERR_INVALID_ARG参数错误
 */
esp_err_t adc_set_data_inv(adc_unit_t adc_unit, bool inv_en);

/**
 * @brief 设置ADC源时钟
 * @param clk_div ADC时钟分频器，ADC时钟与APB时钟分频
 * @return
 *     -ESP_OK成功
 */
esp_err_t adc_set_clk_div(uint8_t clk_div);

/**
 * @brief 配置ADC捕获宽度。
 *
 * @param adc_unit ADC单元索引
 * @param width_bit ADC单元的位捕获宽度。
 *
 * @return
 *     -ESP_OK成功
 *     -ESP_ERR_INVALID_ARG参数错误
 */
esp_err_t adc_set_data_width(adc_unit_t adc_unit, adc_bits_width_t width_bit);

/**
 * @brief 配置ADC1以供ULP使用
 *
 * 此功能将ADC1重新配置为由ULP控制。可以使用``adc1_get_raw（）``函数恢复此函数的效果。
 *
 * 注意，在ULP使用adc1之前，需要调用adc1_config_channel_atten、`adc1_conconfig_width（）``函数来配置adc1信道。
 */
void adc1_ulp_enable(void);
#endif  //#如果CONFIG_IDF_TARGET_ESP32 | | CONFIG_IDF _TARGET_ESP32S2 | | CONFIG _IDF_TERGET_ESP32S3

/**
 * @brief 获取特定ADC2通道的GPIO编号。
 *
 * @param channel 获取GPIO编号的通道
 *
 * @param gpio_num 保存GPIO编号的输出缓冲区
 *
 * @return
 *   -ESP_OK（如果成功）
 *   -如果通道无效，则为ESP_ERR_INVALID_ARG
 */
esp_err_t adc2_pad_get_io_num(adc2_channel_t channel, gpio_num_t *gpio_num);

/**
 * @brief 配置ADC2信道，包括设置衰减。
 *
 * 默认ADC电压用于衰减0 dB，并在下表中列出。通过设置更高的衰减，可以读取更高的电压。
 *
 * 由于ADC特性，在下表所示的“建议范围”内可获得最准确的结果。
 *
 *     +----------+-------------+-----------------+| |衰减|建议范围| | SoC |（dB）|（mV）|+===============+============+=====+|||0|100~950||+----------------+----------------+||2.5|100~1250||ESP32+----------------+||6|150~1750 ||+-------------+||11|150~2450 |+---------------+---------------+| |0|0~750 ||+---------------+----------------+||2.5 |0~1050 ||ESP32-S2+---------------+-------------------+||6 |0~1300 ||+------------+----------------+||11 |0~2500 |+----------+-------------+-----------------+
 *
 * 为了获得最大精度，请使用ADC校准API并在这些推荐范围内测量电压。
 *
 * @note 该功能还配置输入GPIO引脚多路复用器，将其连接到ADC2信道。必须在为此通道调用``adc2_get_raw（）``之前调用它。
 *
 * @note 对于任何给定的通道，必须在第一次为该通道调用`adc2_get_raw（）``之前调用该函数。
 *
 * @param channel 要配置的ADC2通道
 * @param atten  衰减水平
 *
 * @return
 *     -ESP_OK成功
 *     -ESP_ERR_INVALID_ARG参数错误
 */
esp_err_t adc2_config_channel_atten(adc2_channel_t channel, adc_atten_t atten);

/**
 * @brief 在单个通道上读取ADC2读数
 *
 * @note ESP32：当SARADC1、SARADC2、HALL传感器和AMP传感器的电源开关打开时，GPIO36和GPIO39的输入将被下拉约80ns。当为任何这些外设启用电源时，忽略GPIO36和GPIO39的输入。有关此问题的说明，请参阅“ECO_and_Workarounds_for_Bugs_in_ESP32”的3.11节。作为解决方法，在应用程序中调用adc_power_acquire（）。这将导致更高的功耗（约1mA），但将消除GPIO36和GPIO39上的故障。
 *
 *
 * @note ESP32:对于给定的通道，必须在第一次调用此函数之前调用``adc2_config_channel_atten（）``。如果通过`esp_wifi_start（）``启动Wi-Fi，则此函数将始终失败，并显示``esp_ERR_TIMEOUT``。
 *
 * @note ESP32-S2:ADC2支持硬件仲裁器。仲裁器是为了提高ADC2的使用效率。在控制权被高优先级抢走之后，低优先级控制器将读取无效的ADC2数据。默认优先级：Wi-Fi>RTC>Digital；
 *
 * @param channel 要读取的ADC2通道
 * @param width_bit ADC2的位捕获宽度
 * @param raw_out 保存输出数据的变量。
 *
 * @return
 *     -ESP_OK（如果成功）
 *     -其他控制器正在使用ESP_ERR_TIMEOUT ADC2，请求超时。
 *     -ESP_ERR_INVALID_STATE控制器状态无效。请重试。
 */
esp_err_t adc2_get_raw(adc2_channel_t channel, adc_bits_width_t width_bit, int *raw_out);

/**
 *  @brief 将ADC1或ADC2的参考电压输出到“ADC2_channe_t”的IO。
 *
 *  此函数将ADCn的内部参考电压路由到ADC2的一个通道。然后，可以手动测量该参考电压以进行校准。
 *
 *  @note  ESP32仅支持ADC2内部参考电压的输出。
 *  @param[in]  adc_unit ADC单元索引
 *  @param[in]  gpio     GPIO编号（仅支持ADC2的通道IO）
 *
 *  @return
 *                  -ESP_OK:v_ref成功路由到所选GPIO
 *                  -ESP_ERR_INVALID_ARG：不支持的GPIO
 */
esp_err_t adc_vref_to_gpio(adc_unit_t adc_unit, gpio_num_t gpio);

/**
 *  @brief 将ADC2参考电压输出到“ADC2_channe_t”的IO。
 *
 *  此函数将ADCn的内部参考电压路由到ADC2的一个通道。然后，可以手动测量该参考电压以进行校准。
 *
 *  @deprecated 请改用``adc_vref_to_gpio``。
 *
 *  @param[in]  gpio    GPIO编号（支持ADC2的通道）
 *
 *  @return
 *                  -ESP_OK:v_ref成功路由到所选GPIO
 *                  -ESP_ERR_INVALID_ARG：不支持的GPIO
 */
esp_err_t adc2_vref_to_gpio(gpio_num_t gpio) __attribute__((deprecated));

/*---------------------------------------------------------------
                    DMA设置
---------------------------------------------------------------*/
/**
 * @brief 数字ADC DMA读取最大超时值，如果操作系统支持，它可能会使“ADC_digi_read_bytes”块永远停止
 */
#define ADC_MAX_DELAY UINT32_MAX

/**
 * @brief ADC DMA驱动程序配置
 */
typedef struct adc_digi_init_config_s {
    uint32_t max_store_buf_size;    ///<驱动程序在处理转换数据之前可以存储的转换数据的最大长度。
    uint32_t conv_num_each_intr;    ///<可在1个中断中转换的数据字节数。
    uint32_t adc1_chan_mask;        ///<要初始化的ADC1的频道列表。
    uint32_t adc2_chan_mask;        ///<要初始化的ADC2的频道列表。
} adc_digi_init_config_t;

/**
 * @brief ADC数字控制器设置
 */
typedef struct {
    bool conv_limit_en;                      ///<限制ADC转换时间。完成“conv_limit_num”次转换后，转换停止
    uint32_t conv_limit_num;                 ///<设置ADC转换触发器数量的上限。范围：1~255。
    uint32_t pattern_num;                    ///<将使用的ADC通道数
    adc_digi_pattern_config_t *adc_pattern;    ///<将使用的每个ADC通道的配置列表
    uint32_t sample_freq_hz;  /*!< 预期ADC采样频率（Hz）。范围：611Hz~83333Hz Fs=Fd/间隔/2 Fs：采样频率；Fd：数字控制器频率，不大于5M以获得更好的性能间隔：2个测量触发信号之间的间隔，最小间隔不应小于ADC测量周期，最大间隔不应大于4095*/
    adc_digi_convert_mode_t conv_mode;      ///<ADC DMA转换模式，请参见“ADC_digi_convert_mode_t”。
    adc_digi_output_format_t format;        ///<ADC DMA转换输出格式，请参见“ADC_digi_output_format_t”。
} adc_digi_configuration_t;

/**
 * @brief 初始化数字ADC。
 *
 * @param init_config 指向数字ADC初始化配置的指针。请参阅`adc_digi_init_config_t`。
 *
 * @return
 *         -ESP_ERR_INVALID_ARG如果参数组合无效。
 *         -ESP_ERR_NOT_FOUND未找到具有指定标志的空闲中断
 *         -ESP_ERR_NO_MEM如果内存不足
 *         -ESP_OK成功
 */
esp_err_t adc_digi_initialize(const adc_digi_init_config_t *init_config);

/**
 * @brief 通过DMA从数字ADC读取字节。
 *
 * @param[out] buf                 要从ADC读取的缓冲区。
 * @param[in]  length_max          从ADC读取的数据的预期长度。
 * @param[out] out_length          通过此API从ADC读取的数据的实际长度。
 * @param[in]  timeout_ms          通过此API等待数据的时间（毫秒）。
 *
 * @return
 *         -ESP_ERR_INVALID_STATE驱动程序状态无效。通常这意味着ADC采样速率比任务处理速率快。
 *         -ESP_ERR_TIMEOUT操作超时
 *         -ESP_OK成功
 */
esp_err_t adc_digi_read_bytes(uint8_t *buf, uint32_t length_max, uint32_t *out_length, uint32_t timeout_ms);

/**
 * @brief 启动数字ADC和DMA外围设备。之后，硬件开始工作。
 *
 * @return
 *         -ESP_ERR_INVALID_STATE驱动程序状态无效。
 *         -ESP_OK成功
 */
esp_err_t adc_digi_start(void);

/**
 * @brief 停止数字ADC和DMA外围设备。之后，硬件停止工作。
 *
 * @return
 *         -ESP_ERR_INVALID_STATE驱动程序状态无效。
 *         -ESP_OK成功
 */
esp_err_t adc_digi_stop(void);

/**
 * @brief 取消初始化数字ADC。
 *
 * @return
 *         -ESP_ERR_INVALID_STATE驱动程序状态无效。
 *         -ESP_OK成功
 */
esp_err_t adc_digi_deinitialize(void);

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
esp_err_t adc_digi_controller_configure(const adc_digi_configuration_t *config);


#if CONFIG_IDF_TARGET_ESP32S2 || CONFIG_IDF_TARGET_ESP32C3
//TODO IDF-3610
/**
 * @brief 重置adc数字控制器滤波器。
 *
 * @param idx 筛选器索引。
 *
 * @return
 *      -ESP_OK成功
 */
esp_err_t adc_digi_filter_reset(adc_digi_filter_idx_t idx);

/**
 * @brief 设置adc数字控制器滤波器配置。
 *
 * @note 对于ESP32S2，滤波器IDX0/IDX1只能用于同时对ADC1/ADC2单元的所有启用信道进行滤波。
 *
 * @param idx 筛选器索引。
 * @param config 请参见`adc_digi_filter_t``。
 *
 * @return
 *      -ESP_OK成功
 */
esp_err_t adc_digi_filter_set_config(adc_digi_filter_idx_t idx, adc_digi_filter_t *config);

/**
 * @brief 获取adc数字控制器滤波器配置。
 *
 * @note 对于ESP32S2，滤波器IDX0/IDX1只能用于同时对ADC1/ADC2单元的所有启用信道进行滤波。
 *
 * @param idx 筛选器索引。
 * @param config 请参见`adc_digi_filter_t``。
 *
 * @return
 *      -ESP_OK成功
 */
esp_err_t adc_digi_filter_get_config(adc_digi_filter_idx_t idx, adc_digi_filter_t *config);

/**
 * @brief 启用/禁用adc数字控制器滤波器。对ADC数据进行滤波，以获得更高采样率的平滑数据。
 *
 * @note 对于ESP32S2，滤波器IDX0/IDX1只能用于同时对ADC1/ADC2单元的所有启用信道进行滤波。
 *
 * @param idx 筛选器索引。
 * @param enable 启用/禁用过滤器。
 *
 * @return
 *      -ESP_OK成功
 */
esp_err_t adc_digi_filter_enable(adc_digi_filter_idx_t idx, bool enable);

/**
 * @brief 配置adc数字控制器的监视器。
 *
 * @note 对于ESP32S2，监视器将同时监视每个ADC单元的所有启用通道数据。
 *
 * @param idx 监控索引。
 * @param config 请参见`adc_digi_monitor_t``。
 *
 * @return
 *      -ESP_OK成功
 */
esp_err_t adc_digi_monitor_set_config(adc_digi_monitor_idx_t idx, adc_digi_monitor_t *config);

/**
 * @brief 启用/禁用adc数字控制器的监视器。
 *
 * @note 对于ESP32S2，监视器将同时监视每个ADC单元的所有启用通道数据。
 *
 * @param idx 监控索引。
 * @param enable True或false启用监视器。
 *
 * @return
 *      -ESP_OK成功
 */
esp_err_t adc_digi_monitor_enable(adc_digi_monitor_idx_t idx, bool enable);
#endif  //#如果CONFIG_IDF_TARGET_ESP2S2 | | CONFIG_IDF _TARGET_ESP2C3

#if CONFIG_IDF_TARGET_ESP32
//TODO IDF-3610
/**
 * @brief 读取霍尔传感器
 *
 * @note 当SARADC1、SARADC2、HALL传感器和AMP传感器的电源开关打开时，GPIO36和GPIO39的输入将被下拉约80ns。当为任何这些外设启用电源时，忽略GPIO36和GPIO39的输入。有关此问题的说明，请参阅“ECO_and_Workarounds_for_Bugs_in_ESP32”的3.11节。
 *
 * @note 霍尔传感器使用ADC1的通道0和3。请勿将这些通道配置为用作ADC通道。
 *
 * @note 在调用hall_sensor_read（）之前，必须通过调用ADC1_config_width（）来启用ADC1模块。ADC1应配置为12位读数，因为霍尔传感器读数为低值，不涵盖ADC的整个范围。
 *
 * @return 霍尔传感器读数。
 */
int hall_sensor_read(void);

/*---------------------------------------------------------------
                    不推荐TODO:IDF-3610
---------------------------------------------------------------*/
/**
 * @brief 设置I2S数据源
 * @param src I2S DMA数据源，I2S DMA可以从数字信号或ADC获得数据。
 * @return
 *     -ESP_OK成功
 */
esp_err_t adc_set_i2s_data_source(adc_i2s_source_t src);

/**
 * @brief 初始化I2S ADC模式
 * @param adc_unit ADC单元索引
 * @param channel ADC通道索引
 * @return
 *     -ESP_OK成功
 *     -ESP_ERR_INVALID_ARG参数错误
 */
esp_err_t adc_i2s_mode_init(adc_unit_t adc_unit, adc_channel_t channel);
#endif

#ifdef __cplusplus
}
#endif

