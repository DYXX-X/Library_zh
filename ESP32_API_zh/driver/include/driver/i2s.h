/*
 * SPDX文件版权文本：2015-2021浓缩咖啡系统（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */

#pragma once

#include "esp_types.h"
#include "esp_err.h"
#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"
#include "soc/i2s_periph.h"
#include "soc/rtc_periph.h"
#include "soc/soc_caps.h"
#include "hal/i2s_types.h"
#include "driver/periph_ctrl.h"
#include "esp_intr_alloc.h"

#if SOC_I2S_SUPPORTS_ADC
#include "driver/adc.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

#define I2S_PIN_NO_CHANGE (-1) /*!< 在i2s_pin_config_t中使用不应更改的引脚*/

/**
 * @brief I2S端口号，最大端口号为（I2S_NUM_max-1）。
 */
typedef enum {
    I2S_NUM_0 = 0,                 /*!< I2S端口0*/
#if SOC_I2S_NUM > 1
    I2S_NUM_1 = 1,                 /*!< I2S端口1*/
#endif
    I2S_NUM_MAX,                   /*!< I2S端口最大值*/
} i2s_port_t;

#if SOC_I2S_SUPPORTS_PCM
/**
 * @brief I2S PCM组态
 *
 */
typedef struct {
    i2s_pcm_compress_t  pcm_type;       /*!< I2S PCM a/u-law解压缩或压缩类型*/
} i2s_pcm_cfg_t;
#endif

#if SOC_I2S_SUPPORTS_PDM_TX
/**
 * @brief 默认I2S PDM上采样率配置
 */
#define I2S_PDM_DEFAULT_UPSAMPLE_CONFIG(rate) { \
        .sample_rate = rate,                    \
        .fp = 960,                              \
        .fs = (rate) / 100,                     \
    }

/**
 * @brief I2S PDM上采样率配置
 * @note  TX PDM只能设置为以下两种上采样率配置：1:fp=960，fs=sample_rate/100，在这种情况下，Fpdm=12848000 2:fp=960、fs=480，在这种情形下，Fpdm=128Fpcm=128sample_rate如果PDM接收器不关心PDM串行时钟，建议设置Fpdm=12848000。否则，应应用第二种配置。
 */
typedef struct  {
    int sample_rate;                    /*!< I2S PDM采样率*/
    int fp;                             /*!< I2S PDM TX上采样参数。通常应设置为960*/
    int fs;                             /*!< I2S PDM TX上采样参数。当设置为480时，pdm时钟频率Fpdm=128*sample_rate，当设置为sample_rate/100时，Fpdm将固定为128*48000*/
} i2s_pdm_tx_upsample_cfg_t;
#endif

/**
 * @brief I2S_set_pin的I2S引脚号
 *
 */
typedef struct {
    int mck_io_num;     /*!< MCK输入输出引脚。注意，ESP32仅支持在GPIO0/GPIO1/GPIO3上设置MCK*/
    int bck_io_num;     /*!< BCK输入输出引脚*/
    int ws_io_num;      /*!< WS输入输出引脚*/
    int data_out_num;   /*!< 数据输出引脚*/
    int data_in_num;    /*!< 引脚中的数据*/
} i2s_pin_config_t;

/**
 * @brief I2S驱动程序配置参数
 *
 */
typedef struct {

    i2s_mode_t              mode;                       /*!< I2S工作模式*/
    uint32_t                sample_rate;                /*!< I2S采样率*/
    i2s_bits_per_sample_t   bits_per_sample;            /*!< 一个通道中的I2S采样位*/
    i2s_channel_fmt_t       channel_format;             /*!< I2S信道格式。*/
    i2s_comm_format_t       communication_format;       /*!< I2S通信格式*/
    int                     intr_alloc_flags;           /*!< 用于分配中断的标志。一个或多个（ORred）ESP_INTR_FLAG_*值。请参见esp_intr_alloc。h了解更多信息*/
    int                     dma_buf_count;              /**< 用于接收/传输数据的DMA缓冲区总数。描述符包括一些信息，例如缓冲区地址、下一个描述符的地址和缓冲区长度。由于一个描述符指向一个缓冲区，因此，“dma_desc_num”可以解释为用于存储dma中断数据的dma缓冲区总数。请注意，这些缓冲区位于“2s_read”内部，描述符是在i2s驱动程序内部自动创建的。用户只需要设置缓冲区编号，而长度是从下面描述的参数导出的。
                                                          */
    int                     dma_buf_len;                /**< DMA缓冲区中的帧数。帧表示WS周期中所有信道的数据。real_dma_buf_size=dma_buf_len chan_num bits_per_chan/8。例如，如果立体声模式中的两个通道（即“channel_format”设置为“I2S_channel_FMT_RIGHT_LEFT”）处于活动状态，并且每个通道传输32位（即“bits_per_sample”设置为”I2S_bits_per_chan_32BIT“），则帧的总字节数为“channel-format”“bits_per_sample“=2 32/8=8字节。我们假设当前的“dma_buf_len”为100，那么dma缓冲区的实际长度为8 100=800字节。注意，内部实际DMA缓冲区的长度不应大于4092。
                                                          */
    bool                    use_apll;                   /*!< I2S使用APLL作为主I2S时钟，使其能够获得准确的时钟*/
    bool                    tx_desc_auto_clear;         /*!< 如果存在下溢情况，I2S自动清除tx描述符（有助于避免数据不可用时的噪声）*/
    int                     fixed_mclk;                 /*!< I2S使用固定MCLK输出。如果use_apll=true且fixed_mclk>0，则i2s的时钟输出是固定的，并等于fixed_mclk值。如果设置了fixed_mclk，mclk_multiple将不会生效*/
    i2s_mclk_multiple_t     mclk_multiple;              /*!< I2S主时钟（MCLK）与采样率的倍数*/
    i2s_bits_per_chan_t     bits_per_chan;              /*!< 一个通道中的I2S总位，仅在大于“bits_per_sample”时生效，默认值“0”表示等于“bits_pers_sample*/

#if SOC_I2S_SUPPORTS_TDM
    i2s_channel_t           chan_mask;                  /*!< I2S活动信道位掩码，在“I2S_channel_t”中设置值以启用特定信道，活动信道的位图不能超过（0x1<<total_chan）。*/
    uint32_t                total_chan;                 /*!< I2S通道总数。如果它小于最大的活动频道号，它将自动设置为该号。*/
    bool                    left_align;                 /*!< 设置为启用左对齐*/
    bool                    big_edin;                   /*!< 设置为启用big edin*/
    bool                    bit_order_msb;              /*!< 设置为启用msb顺序*/
    bool                    skip_msk;                   /*!< 设置为启用跳过掩码。如果已启用，则仅发送已启用信道的数据，否则将发送DMA TX缓冲区中存储的所有数据*/
#endif // SOC_I2S_SUPPORTS_TDM

} i2s_driver_config_t;

typedef i2s_driver_config_t i2s_config_t;       // 用于向后兼容
typedef intr_handle_t i2s_isr_handle_t;         // 用于向后兼容

/**
 * @brief I2S事件队列类型
 *
 */
typedef enum {
    I2S_EVENT_DMA_ERROR,
    I2S_EVENT_TX_DONE,     /*!< I2S DMA完成发送1个缓冲区*/
    I2S_EVENT_RX_DONE,     /*!< I2S DMA完成收到1个缓冲区*/
    I2S_EVENT_TX_Q_OVF,    /*!< I2S DMA发送队列溢出*/
    I2S_EVENT_RX_Q_OVF,    /*!< I2S DMA接收队列溢出*/
    I2S_EVENT_MAX,         /*!< I2S事件最大索引*/
} i2s_event_type_t;

/**
 * @brief I2S事件队列中使用的事件结构
 *
 */
typedef struct {
    i2s_event_type_t    type;   /*!< I2S事件类型*/
    size_t              size;   /*!< I2S_data事件的I2S数据大小*/
} i2s_event_t;

/**
 * @brief 设置I2S引脚编号
 *
 * @note I2S外围输出信号可以连接到多个GPIO焊盘。然而，I2S外围输入信号只能连接到一个GPIO焊盘。
 *
 * @param   i2s_num     I2S端口号
 *
 * @param   pin         I2S引脚结构，或NULL设置2通道8位内部DAC引脚配置（GPIO25和GPIO26）
 *
 * 在引脚配置结构内部，为不应更改当前配置的任何引脚设置I2S_pin_NO_CHANGE。
 *
 * @note 如果*pin设置为NULL，则默认情况下，此函数将初始化两个内置DAC通道。如果不想发生这种情况，并且只想初始化其中一个DAC通道，则可以调用i2s_set_DAC_mode。
 *
 * @return
 *     -ESP_OK成功
 *     -ESP_ERR_INVALID_ARG参数错误
 *     -ESP_FAIL IO错误
 */
esp_err_t i2s_set_pin(i2s_port_t i2s_num, const i2s_pin_config_t *pin);

#if SOC_I2S_SUPPORTS_PDM_RX
/**
 * @brief 设置PDM模式下采样率在PDM RX模式下，硬件中将有2轮下采样过程。在第一次下采样过程中，采样次数可以是16或8。在第二次下采样处理中，采样数量固定为8。因此，PDM RX模式中的时钟频率将相应地为（fpcm 64）或（fpcm 128）。
 * @param i2s_num I2S端口号
 * @param downsample PDM模式的i2s RX下采样率。
 *
 * @note 调用此函数后，它将在内部调用i2s_set_clk以更新时钟频率。请在初始化I2S驱动程序后调用此函数。
 *
 * @return
 *     -ESP_OK成功
 *     -ESP_ERR_INVALID_ARG参数错误
 *     -ESP_ERR_NO_MEM内存不足
 */
esp_err_t i2s_set_pdm_rx_down_sample(i2s_port_t i2s_num, i2s_pdm_dsr_t downsample);
#endif

#if SOC_I2S_SUPPORTS_PDM_TX
/**
 * @brief 设置TX PDM模式上采样率
 * @note  如果在调用“i2s_driver_install”时设置了PDM模式，则默认的PDM TX上采样参数已经设置，如果不需要更改默认配置，则无需再次调用此函数
 *
 * @param i2s_num I2S端口号
 * @param upsample_cfg 设置I2S PDM上采样率配置
 *
 * @return
 *     -ESP_OK成功
 *     -ESP_ERR_INVALID_ARG参数错误
 *     -ESP_ERR_NO_MEM内存不足
 */
esp_err_t i2s_set_pdm_tx_up_sample(i2s_port_t i2s_num, const i2s_pdm_tx_upsample_cfg_t *upsample_cfg);
#endif

/**
 * @brief 安装并启动I2S驱动程序。
 *
 * @param i2s_num         I2S端口号
 *
 * @param i2s_config      I2S配置-请参阅I2S_config_t结构
 *
 * @param queue_size      I2S事件队列大小/深度。
 *
 * @param i2s_queue       I2S事件队列句柄，如果设置为NULL，驱动程序将不使用事件队列。
 *
 * 必须在任何I2S驱动程序读/写操作之前调用此函数。
 *
 * @return
 *     -ESP_OK成功
 *     -ESP_ERR_INVALID_ARG参数错误
 *     -ESP_ERR_NO_MEM内存不足
 *     -ESP_ERR_INVALID_STATE当前I2S端口正在使用中
 */
esp_err_t i2s_driver_install(i2s_port_t i2s_num, const i2s_config_t *i2s_config, int queue_size, void *i2s_queue);

/**
 * @brief 卸载I2S驱动程序。
 *
 * @param i2s_num  I2S端口号
 *
 * @return
 *     -ESP_OK成功
 *     -ESP_ERR_INVALID_ARG参数错误
 *     -ESP_ERR_INVALID_STATE I2S端口已被其他人卸载（例如LCD i80）
 */
esp_err_t i2s_driver_uninstall(i2s_port_t i2s_num);

/**
 * @brief 将数据写入I2S DMA传输缓冲区。
 *
 * @param i2s_num             I2S端口号
 *
 * @param src                 要写入的源地址
 *
 * @param size                数据大小（字节）
 *
 * @param[out] bytes_written  写入的字节数，如果超时，结果将小于传入的大小。
 *
 * @param ticks_to_wait       TX缓冲区等待超时（以RTOS计时为单位）。如果在DMA传输缓冲区中没有可用空间的情况下经过了这么多时间，则函数将返回（请注意，如果数据以碎片形式写入DMA缓冲区，则整个操作可能仍需要比此超时更长的时间。）传递portMAX_DELAY以无超时。
 *
 * @return
 *     -ESP_OK成功
 *     -ESP_ERR_INVALID_ARG参数错误
 */
esp_err_t i2s_write(i2s_port_t i2s_num, const void *src, size_t size, size_t *bytes_written, TickType_t ticks_to_wait);

/**
 * @brief 将数据写入I2S DMA传输缓冲区，同时扩展每个采样的位数。例如，将16位PCM扩展为32位PCM。
 *
 * @param i2s_num             I2S端口号
 *
 * @param src                 要写入的源地址
 *
 * @param size                数据大小（字节）
 *
 * @param src_bits            源音频位
 *
 * @param aim_bits            需要位，不超过32，并且必须大于src_bits
 *
 * @param[out] bytes_written  写入的字节数，如果超时，结果将小于传入的大小。
 *
 * @param ticks_to_wait       TX缓冲区等待超时（以RTOS计时为单位）。如果在DMA传输缓冲区中没有可用空间的情况下经过了这么多时间，则函数将返回（请注意，如果数据以碎片形式写入DMA缓冲区，则整个操作可能仍需要比此超时更长的时间。）传递portMAX_DELAY以无超时。
 *
 * 源缓冲区中数据的格式由I2S配置确定（请参见I2S_config_t）。
 *
 * @return
 *     -ESP_OK成功
 *     -ESP_ERR_INVALID_ARG参数错误
 */
esp_err_t i2s_write_expand(i2s_port_t i2s_num, const void *src, size_t size, size_t src_bits, size_t aim_bits, size_t *bytes_written, TickType_t ticks_to_wait);

/**
 * @brief 从I2S DMA接收缓冲区读取数据
 *
 * @param i2s_num         I2S端口号
 *
 * @param dest            要读入的目标地址
 *
 * @param size            数据大小（字节）
 *
 * @param[out] bytes_read 读取的字节数，如果超时，读取的字节将小于传入的大小。
 *
 * @param ticks_to_wait   RX缓冲区等待超时（RTOS计时）。如果在DMA接收缓冲区中没有字节可用的情况下，经过了这么多的滴答声，则函数将返回（注意，如果从DMA缓冲区中读取数据，则整个操作可能仍需要比此超时更长的时间。）传递portMAX_DELAY以无超时。
 *
 * @note 如果启用了内置ADC模式，我们应该在整个读取过程中调用i2s_ADC_enable和i2s_ADC_disable，以防止数据损坏。
 *
 * @return
 *     -ESP_OK成功
 *     -ESP_ERR_INVALID_ARG参数错误
 */
esp_err_t i2s_read(i2s_port_t i2s_num, void *dest, size_t size, size_t *bytes_read, TickType_t ticks_to_wait);

/**
 * @brief 设置用于I2S RX和TX的采样率。
 *
 * 位时钟速率由采样速率和i2s_config_t配置参数（通道数、bits_per_sample）确定。
 *
 * `bit_clock=速率*（通道数）*bits_per_sample`
 *
 * @param i2s_num  I2S端口号
 *
 * @param rate I2S采样率（例如：8000、44100…）
 *
 * @return
 *     -ESP_OK成功
 *     -ESP_ERR_INVALID_ARG参数错误
 *     -ESP_ERR_NO_MEM内存不足
 */
esp_err_t i2s_set_sample_rates(i2s_port_t i2s_num, uint32_t rate);

/**
 * @brief 停止I2S驱动程序
 *
 * 在调用i2s_driver_uninstall（）之前，无需调用i2s_stop（）。
 *
 * 禁用I2S TX/RX，直到调用I2S_start（）。
 *
 * @param i2s_num  I2S端口号
 *
 * @return
 *     -ESP_OK成功
 *     -ESP_ERR_INVALID_ARG参数错误
 */
esp_err_t i2s_stop(i2s_port_t i2s_num);

/**
 * @brief 启动I2S驱动程序
 *
 * 在i2s_driver_install（）之后不必调用此函数（它是自动启动的），但在i2s_stop（）之后需要调用它。
 *
 *
 * @param i2s_num  I2S端口号
 *
 * @return
 *     -ESP_OK成功
 *     -ESP_ERR_INVALID_ARG参数错误
 */
esp_err_t i2s_start(i2s_port_t i2s_num);

/**
 * @brief 将TX DMA缓冲区的内容归零。
 *
 * 将零字节样本推入TX DMA缓冲区，直到其满。
 *
 * @param i2s_num  I2S端口号
 *
 * @return
 *     -ESP_OK成功
 *     -ESP_ERR_INVALID_ARG参数错误
 */
esp_err_t i2s_zero_dma_buffer(i2s_port_t i2s_num);

#if SOC_I2S_SUPPORTS_PCM
/**
 * @brief 配置I2S a/u-law解压缩或压缩
 *
 * @note  应在安装i2s驱动程序后调用此函数。仅当i2s“communication_format”设置为“i2s_COMM_format_STAND_PCM_SHORT”或“i2s_COM_format_SESTAND_PCM_LONG”时，此函数才会生效
 *
 * @param i2s_num  I2S端口号
 *
 * @param pcm_cfg  包括模式选择和a/u-law解压缩或压缩配置参数
 *
 * @return
 *     -ESP_OK成功
 *     -ESP_ERR_INVALID_ARG参数错误
 */
esp_err_t i2s_pcm_config(i2s_port_t i2s_num, const i2s_pcm_cfg_t *pcm_cfg);
#endif

/**
 * @brief 设置用于I2S RX和TX的时钟和位宽。
 *
 * 类似于i2s_set_sample_rates（），但也设置位宽。
 *
 * 1.停止i2s；2.计算mclk、bck、bckfactor 3.mallocdma缓冲区；4.启动i2s
 *
 * @param i2s_num  I2S端口号
 *
 * @param rate I2S采样率（例如：8000、44100…）
 *
 * @param bits_cfg I2S位配置，低16位用于一个通道中每个采样的数据位（参见“I2S_bits_per_sample_t”），高16位用于在一个通道（参见“I2S_bits_per_chan_t””）中的总位。高16位=0表示与每个采样的位相同。
 *
 * @param ch I2S信道（I2S_channel_MONO、I2S_CHANDEL_STEREO或TDM模式下的特定信道）
 *
 * @return
 *     -ESP_OK成功
 *     -ESP_ERR_INVALID_ARG参数错误
 *     -ESP_ERR_NO_MEM内存不足
 */
esp_err_t i2s_set_clk(i2s_port_t i2s_num, uint32_t rate, uint32_t bits_cfg, i2s_channel_t ch);

/**
 * @brief 获取特定端口号的时钟设置。
 *
 * @param i2s_num  I2S端口号
 *
 * @return
 *     -i2s驱动器设置的实际时钟
 */
float i2s_get_clk(i2s_port_t i2s_num);

#if SOC_I2S_SUPPORTS_ADC
/**
 * @brief 为I2S DMA设置内置ADC模式，此功能将初始化ADC垫，并设置ADC参数。
 * @note  在此模式下，ADC最大采样率为150KHz。通过`i2s_config_t``设置采样率。
 * @param adc_unit    SAR ADC单元索引
 * @param adc_channel ADC通道索引
 * @return
 *     -ESP_OK成功
 *     -ESP_ERR_INVALID_ARG参数错误
 */
esp_err_t i2s_set_adc_mode(adc_unit_t adc_unit, adc1_channel_t adc_channel);

/**
 * @brief 开始使用I2S内置ADC模式
 * @note 该功能将获取ADC的锁，以防止在I2S外围设备用于进行完全连续的ADC采样期间数据损坏。
 *
 * @param i2s_num i2s端口索引
 * @return
 *     -ESP_OK成功
 *     -ESP_ERR_INVALID_ARG参数错误
 *     -ESP_ERR_INVALID_STATE驱动程序状态错误
 */
esp_err_t i2s_adc_enable(i2s_port_t i2s_num);

/**
 * @brief 停止使用I2S内置ADC模式
 * @param i2s_num i2s端口索引
 * @note 此函数将释放ADC的锁，以便其他任务可以使用ADC。
 * @return
 *     -ESP_OK成功
 *     -ESP_ERR_INVALID_ARG参数错误
 *     -ESP_ERR_INVALID_STATE驱动程序状态错误
 */
esp_err_t i2s_adc_disable(i2s_port_t i2s_num);
#endif // SOC_I2S_SUPPORTS_ADC

#if SOC_I2S_SUPPORTS_DAC
/**
 * @brief 设置I2S dac模式，默认禁用I2S内置dac
 *
 * @param dac_mode DAC模式配置-请参阅i2s_DAC_mode_t
 *
 * @note 内置DAC功能仅在当前ESP32芯片的I2S0上受支持。如果其中一个内置DAC通道被启用，另一个不能同时用作RTC DAC功能。
 *
 * @return
 *     -ESP_OK成功
 *     -ESP_ERR_INVALID_ARG参数错误
 */
esp_err_t i2s_set_dac_mode(i2s_dac_mode_t dac_mode);
#endif //SOC_I2S_SUPPORTS_DAC


#ifdef __cplusplus
}
#endif

