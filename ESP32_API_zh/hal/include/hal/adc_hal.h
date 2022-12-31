/*
 * SPDX文件版权文本：2021浓缩咖啡系统（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */

#pragma once

#include "esp_err.h"
#include "soc/soc_caps.h"
#include "hal/dma_types.h"
#include "hal/adc_types.h"
#include "hal/adc_ll.h"
#include "esp_err.h"

#if SOC_GDMA_SUPPORTED
#include "soc/gdma_struct.h"
#include "hal/gdma_ll.h"
#endif

#if CONFIG_IDF_TARGET_ESP32S2
//ADC在ESP32S2上使用SPI3 DMA
#include "hal/spi_ll.h"
#endif

#if CONFIG_IDF_TARGET_ESP32
//ADC在ESP32上使用I2S0 DMA
#include "hal/i2s_ll.h"
#endif

#if SOC_GDMA_SUPPORTED
#define ADC_HAL_DMA_INTR_MASK                           GDMA_LL_EVENT_RX_SUC_EOF
#elif CONFIG_IDF_TARGET_ESP32S2
#define ADC_HAL_DMA_INTR_MASK                           SPI_LL_INTR_IN_SUC_EOF
#else //CONFIG_IDF_TARGET_ESP32
#define ADC_HAL_DMA_INTR_MASK                           BIT(9)
#endif

//对于ADC模块，每个转换包含4个字节
#define ADC_HAL_DATA_LEN_PER_CONV 4

typedef enum adc_hal_work_mode_t {
    ADC_HAL_ULP_MODE,
    ADC_HAL_SINGLE_READ_MODE,
    ADC_HAL_CONTINUOUS_READ_MODE,
    ADC_HAL_PWDET_MODE
} adc_hal_work_mode_t;

/**
 * @brief DMA描述符状态的枚举
 */
typedef enum adc_hal_dma_desc_status_t {
    ADC_HAL_DMA_DESC_VALID   = 0,            ///<此DMA描述符已由硬件写入
    ADC_HAL_DMA_DESC_WAITING = 1,            ///<此DMA描述符尚未由硬件写入
    ADC_HAL_DMA_DESC_NULL    = 2             ///<此DMA描述符为空
} adc_hal_dma_desc_status_t;

/**
 * @brief HAL的配置
 */
typedef struct adc_hal_config_t {
    void                *dev;               ///<DMA外围地址
    uint32_t            desc_max_num;       ///<链接一次的描述符数
    uint32_t            dma_chan;           ///<要使用的DMA通道
    uint32_t            eof_num;            ///<2 in_suc_eof中断之间的字节数
} adc_hal_config_t;

/**
 * @brief HAL的背景
 */
typedef struct adc_hal_context_t {
    /**<这需要首先由驱动程序层分配*/
    dma_descriptor_t    *rx_desc;           ///<DMA描述符

    /**<这些将由hal层自身分配*/
    dma_descriptor_t    desc_dummy_head;    ///<启动`cur_desc_ptr``的伪DMA描述符
    dma_descriptor_t    *cur_desc_ptr;      ///<指向当前描述符的指针

    /**<这些需要通过“adc_hal_config_t”通过驱动程序层进行配置*/
    void                *dev;               ///<DMA地址
    uint32_t            desc_max_num;       ///<链接一次的描述符数
    uint32_t            dma_chan;           ///<要使用的DMA通道
    uint32_t            eof_num;            ///<2 in_suc_eof中断之间的单词
} adc_hal_context_t;

typedef struct adc_hal_digi_ctrlr_cfg_t {
    bool                        conv_limit_en;      //1： 当达到“convlimitnum”时，adc转换将停止。0：不会停止。注意：esp32应始终设置为1。
    uint32_t                    conv_limit_num;     //请参见`conv_limit_en`
    uint32_t                    adc_pattern_len;    //总模式项目编号，包括ADC1和ADC2
    adc_digi_pattern_config_t   *adc_pattern;       //图案项目
    uint32_t                    sample_freq_hz;     //ADC采样频率
    adc_digi_convert_mode_t     conv_mode;          //控制器工作模式
    uint32_t                    bit_width;          //输出数据宽度
} adc_hal_digi_ctrlr_cfg_t;


/*---------------------------------------------------------------
                    常用设置
---------------------------------------------------------------*/
/**
 * 设置ADC模块电源管理。
 *
 * @prarm 管理设置ADC电源状态。
 */
#define adc_hal_set_power_manage(manage) adc_ll_set_power_manage(manage)

void adc_hal_set_controller(adc_ll_num_t unit, adc_hal_work_mode_t work_mode);

#if SOC_ADC_ARBITER_SUPPORTED
//ESP32上没有ADC2控制器仲裁器
/**
 * 配置ADC2模块仲裁器。仲裁器是为了提高ADC2的使用效率，在控制权被高优先级抢走后，低优先级控制器将读取无效的ADC2数据，数据的有效性可以通过数据中的标志位来判断。
 *
 * @note 只有ADC2支持仲裁器。
 * @note 仲裁器的工作时钟为APB_CLK。当APB_CLK时钟低于8MHz时，仲裁器必须处于屏蔽模式。
 * @note 默认优先级：Wi-Fi>RTC>Digital；
 *
 * @param config 请参阅`adc_arbiter_t`。
 */
void adc_hal_arbiter_config(adc_arbiter_t *config);
#endif  //#如果SOC_ADC_ARBITER_SUPPORTED

/*---------------------------------------------------------------
                    PWDET（功率检测）控制器设置
---------------------------------------------------------------*/
/**
 * 为PWDET控制器设置adc cct。
 *
 * @note PA功率监视器的电容器调谐。cct设置为与PHY相同的值。
 * @prarm cct范围：0~7。
 */
#define adc_hal_pwdet_set_cct(cct) adc_ll_pwdet_set_cct(cct)

/**
 * 获取PWDET控制器的adc cct。
 *
 * @note PA功率监视器的电容器调谐。cct设置为与PHY相同的值。
 * @return cct范围：0~7。
 */
#define adc_hal_pwdet_get_cct() adc_ll_pwdet_get_cct()

/**
 *  启用/禁用ADC2通道之一的ADCn内部参考电压输出。
 *
 *  此函数将ADCn的内部参考电压路由到ADC2的一个通道。然后，可以手动测量该参考电压以进行校准。
 *
 *  @note  ESP32仅支持ADC2内部参考电压的输出。
 *  @param[in]  adc ADC单元选择
 *  @param[in]  channel ADC2通道编号
 *  @param[in]  en 启用/禁用参考电压输出
 */
#define adc_hal_vref_output(adc, channel, en) adc_ll_vref_output(adc, channel, en)

/*---------------------------------------------------------------
                    数字控制器设置
---------------------------------------------------------------*/
/**
 * ADC模块初始化。
 */
void adc_hal_init(void);

/**
 * 数字控制器去初始化。
 *
 * @param hal HAL的背景
 */
void adc_hal_digi_deinit(adc_hal_context_t *hal);

/**
 * @brief 初始化hal上下文
 *
 * @param hal    HAL的背景
 * @param config HAL的配置
 */
void adc_hal_context_config(adc_hal_context_t *hal, const adc_hal_config_t *config);

/**
 * @brief 初始化硬件
 *
 * @param hal HAL的背景
 */
void adc_hal_digi_init(adc_hal_context_t *hal);

/**
 * 设置数字控制器。
 *
 * @param hal    HAL的背景
 * @param cfg    指向数字控制器参数的指针。
 */
void adc_hal_digi_controller_config(adc_hal_context_t *hal, const adc_hal_digi_ctrlr_cfg_t *cfg);

/**
 * @brief 开始转换
 *
 * @param hal HAL的背景
 * @param data_buf 指向数据缓冲区的指针，长度应为`adc_hal_context_t中`desc_max_num``和`eof_num```的倍数``
 */
void adc_hal_digi_start(adc_hal_context_t *hal, uint8_t *data_buf);

#if !SOC_GDMA_SUPPORTED
/**
 * @brief 获取硬件已完成处理的DMA描述符。
 *
 * @param hal HAL的背景
 *
 * @return DMA描述符地址
 */
intptr_t adc_hal_get_desc_addr(adc_hal_context_t *hal);

/**
 * @brief 检查硬件中断事件
 *
 * @param hal HAL的背景
 * @param mask 事件掩码
 *
 * @return True：事件已触发。False：事件尚未触发。
 */
bool adc_hal_check_event(adc_hal_context_t *hal, uint32_t mask);
#endif

/**
 * @brief 获取ADC读数结果
 *
 * @param      hal           HAL的背景
 * @param      eof_desc_addr 硬件完成的最后一个描述符。应该从DMA获取
 * @param[out] cur_desc      具有ADC读取结果的描述符（从第一个到最后一个（“eof_desc_addr”））
 *
 * @return                   请参见``adc_hal_dma_desc_status_t``
 */
adc_hal_dma_desc_status_t adc_hal_get_reading_result(adc_hal_context_t *hal, const intptr_t eof_desc_addr, dma_descriptor_t **cur_desc);

/**
 * @brief 清除中断
 *
 * @param hal  HAL的背景
 * @param mask 中断屏蔽
 */
void adc_hal_digi_clr_intr(adc_hal_context_t *hal, uint32_t mask);

/**
 * @brief 启用中断
 *
 * @param hal  HAL的背景
 * @param mask 中断屏蔽
 */
void adc_hal_digi_dis_intr(adc_hal_context_t *hal, uint32_t mask);

/**
 * @brief 停止转换
 *
 * @param hal HAL的背景
 */
void adc_hal_digi_stop(adc_hal_context_t *hal);


/*---------------------------------------------------------------
                    ADC单读
---------------------------------------------------------------*/
#if SOC_ADC_RTC_CTRL_SUPPORTED
/**
 * 设置ADCn上特定信道的衰减。
 *
 * @note 对于任何给定的通道，必须在第一次转换之前调用此函数。
 *
 * 默认ADC满量程电压为1.1V。要读取更高的电压（高达引脚最大电压，通常为3.3V），需要为该ADC通道设置>0dB的信号衰减。
 *
 * 当VDD_A为3.3V时：
 *
 * -0dB衰减（ADC_ATTEN_DB_0）给出满量程电压1.1V
 * -2.5dB衰减（ADC_ATTEN_DB_2O_5）给出满量程电压1.5V
 * -6dB衰减（ADC_ATTEN_DB_6）给出满量程电压2.2V
 * -11dB衰减（ADC_ATTEN_DB_11）给出全刻度电压3.9V（见下文注释）
 *
 * @note 满刻度电压是对应于最大读数的电压（取决于ADC1配置的位宽，该值为：12位为4095，11位为2047，10位为1023，9位为511）
 *
 * @note 在11dB衰减时，最大电压受VDD_A限制，而不是满量程电压。
 *
 * 由于ADC特性，在以下近似电压范围内可获得最准确的结果：
 *
 * -0dB衰减（ADC_ATTEN_DB_0）介于100和950mV之间
 * -100和1250mV之间的2.5dB衰减（ADC_ATTEN_DB_2O_5）
 * -150至1750mV之间的6dB衰减（ADC_ATTEN_DB_6）
 * -150至2450mV之间的11dB衰减（ADC_ATTEN_DB_11）
 *
 * 为了获得最大精度，请使用ADC校准API并在这些推荐范围内测量电压。
 *
 * @param adc_n   ADC单元。
 * @param channel ADCn信道号。
 * @param atten   ADC衰减。参见``adc_atten_t``
 */
#define adc_hal_set_atten(adc_n, channel, atten) adc_ll_set_atten(adc_n, channel, atten)

#else // #如果！支持SOC_ADC.RTC_CTRL_
/**
 * 将ADC的衰减设置为单次读取
 *
 * @note 所有ADC单元和通道将共享设置。因此，请保存衰减并通过在驱动程序中再次调用此API来重置它们
 *
 * @param adc_n    未使用，请留在此处以获得芯片版本兼容性
 * @param channel  未使用，请留在此处以获得芯片版本兼容性
 * @param atten    ADC衰减。参见``adc_atten_t``
 */
#define adc_hal_set_atten(adc_n, channel, atten) adc_ll_onetime_set_atten(atten)
#endif  //#如果SOC_ADC_RTC_CTRL_SUPPORTED

/**
 * 启动ADC转换并获取转换后的值。
 *
 * @note 等待转换完成可能会被阻塞。
 *
 * @param      adc_n   ADC单元。
 * @param      channel ADC通道编号。
 * @param[out] out_raw ADC转换结果
 *
 * @return
 *      -ESP_OK：该值有效。
 *      -ESP_ERR_INVALID_STATE:值无效。
 */
esp_err_t adc_hal_convert(adc_ll_num_t adc_n, int channel, int *out_raw);

/*---------------------------------------------------------------
                    ADC校准设置
---------------------------------------------------------------*/
#if SOC_ADC_CALIBRATION_V1_SUPPORTED

/**
 * @brief 初始化校准块的默认参数。
 *
 * @param adc_n ADC索引编号
 */
void adc_hal_calibration_init(adc_ll_num_t adc_n);

/**
 * 将校准结果（初始数据）设置为ADC。
 *
 * @note  不同的ADC单元和不同的衰减选项使用不同的校准数据（初始数据）。
 *
 * @param adc_n ADC索引编号。
 * @param param 要配置的校准参数
 */
void adc_hal_set_calibration_param(adc_ll_num_t adc_n, uint32_t param);

/**
 * 使用内部连接校准ADC。
 *
 * @note  不同的ADC单元和不同的衰减选项使用不同的校准数据（初始数据）。
 *
 * @param adc_n ADC索引编号。
 * @param channel adc通道编号。
 * @param atten 通道的衰减
 * @param internal_gnd true：从IO端口断开连接，并使用内部GND作为校准电压。false：使用IO外部电压作为校准电压。
 *
 * @return
 *      -ADC的校准结果（初始数据），使用“ADC_hal_set_calibration_param”进行设置。
 */
uint32_t adc_hal_self_calibration(adc_ll_num_t adc_n, adc_channel_t channel, adc_atten_t atten, bool internal_gnd);

#endif //SOC_ADC_CALIBRATION_V1_SUPPORTED


/*---------------------------------------------------------------
                    RTC控制器设置
---------------------------------------------------------------*/
/**
 * 设置RTC控制器的adc输出数据格式。
 *
 * @prarm adc_n adc单元。
 * @prarm bits输出数据位宽选项。
 */
#define adc_hal_rtc_set_output_format(adc_n, bits) adc_ll_rtc_set_output_format(adc_n, bits)

/**
 * ADC模块输出数据是否反转。
 *
 * @prarm adc_n adc单元。
 */
#define adc_hal_rtc_output_invert(adc_n, inv_en) adc_ll_rtc_output_invert(adc_n, inv_en)

