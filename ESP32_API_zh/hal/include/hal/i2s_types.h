/*
 * SPDX文件版权所有文本：2020-2022 Espressif Systems（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */

#pragma once

#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>
#include "soc/soc_caps.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 每个样本的I2S比特宽度。
 *
 */
typedef enum {
    I2S_BITS_PER_SAMPLE_8BIT    = 8,            /*!< 数据位宽：8*/
    I2S_BITS_PER_SAMPLE_16BIT   = 16,           /*!< 数据位宽：16*/
    I2S_BITS_PER_SAMPLE_24BIT   = 24,           /*!< 数据位宽：24*/
    I2S_BITS_PER_SAMPLE_32BIT   = 32,           /*!< 数据位宽：32*/
} i2s_bits_per_sample_t;

/**
 * @brief 每个通道的I2S比特宽度。
 *
 */
typedef enum {
    I2S_BITS_PER_CHAN_DEFAULT        = (0),      /*!< 通道位宽等于数据位宽*/
    I2S_BITS_PER_CHAN_8BIT           = (8),      /*!< 通道位宽：8*/
    I2S_BITS_PER_CHAN_16BIT          = (16),     /*!< 通道位宽：16*/
    I2S_BITS_PER_CHAN_24BIT          = (24),     /*!< 通道位宽：24*/
    I2S_BITS_PER_CHAN_32BIT          = (32),     /*!< 通道位宽：32*/
} i2s_bits_per_chan_t;

/**
 * @brief I2S通道。
 *
 */
typedef enum {
    I2S_CHANNEL_MONO        = 1,  /*!< I2S通道（单声道），一个通道激活。在此模式下，您只需发送一个信道数据，但fifo将自动复制其他未激活信道的相同数据，然后两个信道将发送相同数据。*/
    I2S_CHANNEL_STEREO      = 2,  /*!< I2S通道（立体声）、两个（或更多）通道激活。在此模式下，这些信道将传输不同的数据。*/
#if SOC_I2S_SUPPORTS_TDM
    // 激活通道的位图。
    // TDM模式下有16个信道。
    // 对于TX模块，只有激活信道发送音频数据，未激活信道发送常量（可配置），如果设置了“skip_msk”，则将被跳过。
    // 对于RX模块，仅接收激活通道中的音频数据，未激活通道中数据将被忽略。
    // 激活信道的位图不能超过最大启用信道数（即0x10000<<total_chan_num）。
    // e、 g:active_chan_mask=（I2S_TDM_active_CH0|I2S_TDM_OCTIVE_CH3），此处active_chan_number为2，total_chan_num不应小于4。
    I2S_TDM_ACTIVE_CH0  = (0x1 << 16),               /*!< I2S通道0已激活*/
    I2S_TDM_ACTIVE_CH1  = (0x1 << 17),               /*!< I2S通道1已激活*/
    I2S_TDM_ACTIVE_CH2  = (0x1 << 18),               /*!< I2S通道2已激活*/
    I2S_TDM_ACTIVE_CH3  = (0x1 << 19),               /*!< I2S通道3已激活*/
    I2S_TDM_ACTIVE_CH4  = (0x1 << 20),               /*!< I2S通道4已激活*/
    I2S_TDM_ACTIVE_CH5  = (0x1 << 21),               /*!< I2S通道5已激活*/
    I2S_TDM_ACTIVE_CH6  = (0x1 << 22),               /*!< I2S通道6已激活*/
    I2S_TDM_ACTIVE_CH7  = (0x1 << 23),               /*!< I2S通道7已激活*/
    I2S_TDM_ACTIVE_CH8  = (0x1 << 24),               /*!< I2S通道8已激活*/
    I2S_TDM_ACTIVE_CH9  = (0x1 << 25),               /*!< I2S通道9已激活*/
    I2S_TDM_ACTIVE_CH10 = (0x1 << 26),              /*!< I2S通道10已激活*/
    I2S_TDM_ACTIVE_CH11 = (0x1 << 27),              /*!< I2S通道11已激活*/
    I2S_TDM_ACTIVE_CH12 = (0x1 << 28),              /*!< I2S通道12已激活*/
    I2S_TDM_ACTIVE_CH13 = (0x1 << 29),              /*!< I2S通道13已激活*/
    I2S_TDM_ACTIVE_CH14 = (0x1 << 30),              /*!< I2S通道14已激活*/
    I2S_TDM_ACTIVE_CH15 = (0x1 << 31),              /*!< I2S通道15已激活*/
#endif
} i2s_channel_t;

/**
 * @brief I2S通信标准格式
 *
 */
typedef enum {
    I2S_COMM_FORMAT_STAND_I2S        = 0X01, /*!< I2S通信I2S Philips标准，第二次BCK数据发布*/
    I2S_COMM_FORMAT_STAND_MSB        = 0X02, /*!< I2S通信MSB校准标准，首次BCK时数据发布*/
    I2S_COMM_FORMAT_STAND_PCM_SHORT  = 0x04, /*!< PCM短标准，也称为DSP模式。同步信号（WS）的周期为1 bck周期。*/
    I2S_COMM_FORMAT_STAND_PCM_LONG   = 0x0C, /*!< PCM Long标准。同步信号（WS）的周期是channel_bit*bck周期。*/
    I2S_COMM_FORMAT_STAND_MAX,               /*!< 标准最大值*/

    //旧的定义将在将来删除。
    I2S_COMM_FORMAT_I2S       __attribute__((deprecated)) = 0x01, /*!< I2S通信格式I2S，对应于`I2S_COMM_format_STAND_I2S`*/
    I2S_COMM_FORMAT_I2S_MSB   __attribute__((deprecated)) = 0x01, /*!< I2S格式MSB，（I2S_COMM_format_I2S | I2S_COMM.format_I2S_MSB）对应于`I2S_COMM-format_STAND_I2S`*/
    I2S_COMM_FORMAT_I2S_LSB   __attribute__((deprecated)) = 0x02, /*!< I2S格式LSB（I2S_COMM_format_I2S | I2S_COMM.format_I2S_LSB）对应于`I2S_COMM-format_STAND_MSB`*/
    I2S_COMM_FORMAT_PCM       __attribute__((deprecated)) = 0x04, /*!< I2S通信格式PCM，对应于`I2S_COMM_format_STAND_PCM_SHORT`*/
    I2S_COMM_FORMAT_PCM_SHORT __attribute__((deprecated)) = 0x04, /*!< PCM短，（I2S_COMM_FORMAT_PMC|I2S_COMM.FORMAT_PCM_Short）对应于`I2S_COMM-FORMAT_STAND_PC_Short`*/
    I2S_COMM_FORMAT_PCM_LONG  __attribute__((deprecated)) = 0x08, /*!< PCM长，（I2S_COMM_FORMAT/PCM|I2S_COMM.FORMAT_PCM_Long）对应于`I2S_COMM-FORMAT_STAND_PCM_Long`*/
} i2s_comm_format_t;

/**
 * @brief I2S信道格式类型
 */
typedef enum {
    I2S_CHANNEL_FMT_RIGHT_LEFT,         /*!< 分离的左右通道*/
    I2S_CHANNEL_FMT_ALL_RIGHT,          /*!< 在两个通道中加载右通道数据*/
    I2S_CHANNEL_FMT_ALL_LEFT,           /*!< 在两个通道中加载左通道数据*/
    I2S_CHANNEL_FMT_ONLY_RIGHT,         /*!< 仅在右通道中加载数据（单声道模式）*/
    I2S_CHANNEL_FMT_ONLY_LEFT,          /*!< 仅在左通道中加载数据（单声道模式）*/
#if SOC_I2S_SUPPORTS_TDM
    // TDM功能提供多个信道
    I2S_CHANNEL_FMT_MULTIPLE,           /*!< 使用了两个以上的通道*/
#endif
}  i2s_channel_fmt_t;

/**
 * @brief I2S模式
 */
typedef enum {
    I2S_MODE_MASTER       = (0x1 << 0),       /*!< 主模式*/
    I2S_MODE_SLAVE        = (0x1 << 1),       /*!< 从属模式*/
    I2S_MODE_TX           = (0x1 << 2),       /*!< TX模式*/
    I2S_MODE_RX           = (0x1 << 3),       /*!< RX模式*/
#if SOC_I2S_SUPPORTS_DAC
    //内置DAC功能仅在ESP32芯片的I2S0上受支持。
    I2S_MODE_DAC_BUILT_IN = (0x1 << 4),       /*!< 将I2S数据输出到内置DAC，无论数据格式是16位还是32位，DAC模块将仅从MSB中取出8位*/
#endif // SOC_I2S_SUPPORTS_DAC
#if SOC_I2S_SUPPORTS_ADC
    I2S_MODE_ADC_BUILT_IN = (0x1 << 5),       /*!< 从内置ADC输入I2S数据，每个数据最多12位宽*/
#endif // SOC_I2S_SUPPORTS_ADC
    // PDM功能仅在I2S0（所有芯片）上受支持。
    I2S_MODE_PDM          = (0x1 << 6),       /*!< I2S PDM模式*/
} i2s_mode_t;

/**
 * @brief I2S源时钟
 */
typedef enum {
    I2S_CLK_D2CLK = 0,               /*!< 来自PLL_D2_CLK的时钟（160M）*/
#if SOC_I2S_SUPPORTS_APLL
    I2S_CLK_APLL,                    /*!< 来自APLL的时钟*/
#endif
} i2s_clock_src_t;

/**
 * @brief mclk与采样率的倍数
 */
typedef enum {
    I2S_MCLK_MULTIPLE_DEFAULT   = 0,       /*!< 默认值。mclk=采样率*256*/
    I2S_MCLK_MULTIPLE_128       = 128,     /*!< mclk=采样率*128*/
    I2S_MCLK_MULTIPLE_256       = 256,     /*!< mclk=采样率*256*/
    I2S_MCLK_MULTIPLE_384       = 384,     /*!< mclk=采样率*384*/
} i2s_mclk_multiple_t;

#if SOC_I2S_SUPPORTS_DAC
/**
 * @brief I2S_set_DAC_mode的I2S DAC模式。
 *
 * @note 内置DAC功能仅在当前ESP32芯片的I2S0上受支持。
 */
typedef enum {
    I2S_DAC_CHANNEL_DISABLE  = 0,    /*!< 禁用I2S内置DAC信号*/
    I2S_DAC_CHANNEL_RIGHT_EN = 1,    /*!< 启用I2S内置DAC右通道，映射到GPIO25上的DAC通道1*/
    I2S_DAC_CHANNEL_LEFT_EN  = 2,    /*!< 启用I2S内置DAC左通道，映射到GPIO26上的DAC通道2*/
    I2S_DAC_CHANNEL_BOTH_EN  = 0x3,  /*!< 启用两个I2S内置DAC通道。*/
    I2S_DAC_CHANNEL_MAX      = 0x4,  /*!< I2S内置DAC模式最大索引*/
} i2s_dac_mode_t;
#endif //SOC_I2S_SUPPORTS_DAC

#if SOC_I2S_SUPPORTS_PCM
/**
 * @brief A/U法则解压缩或压缩配置。
 *
 */
typedef enum {
    I2S_PCM_DISABLE = 0,      /*!< 禁用A/U法则解压缩或压缩*/
    I2S_PCM_A_DECOMPRESS,     /*!< A律减压*/
    I2S_PCM_A_COMPRESS,       /*!< A律压缩*/
    I2S_PCM_U_DECOMPRESS,     /*!< U定律减压*/
    I2S_PCM_U_COMPRESS,       /*!< U定律压缩*/
} i2s_pcm_compress_t;
#endif

#if SOC_I2S_SUPPORTS_PDM_RX
/**
 * @brief I2S PDM RX下采样模式
 */
typedef enum {
    I2S_PDM_DSR_8S = 0,  /*!< PDM RX模式的下采样数为8*/
    I2S_PDM_DSR_16S,     /*!< PDM RX模式的下采样数为16*/
    I2S_PDM_DSR_MAX,
} i2s_pdm_dsr_t;
#endif

#if SOC_I2S_SUPPORTS_PDM_TX
typedef enum {
    I2S_PDM_SIG_SCALING_DIV_2 = 0,   /*!< I2S TX PDM信号缩放：/2*/
    I2S_PDM_SIG_SCALING_MUL_1 = 1,   /*!< I2S TX PDM信号缩放：x1*/
    I2S_PDM_SIG_SCALING_MUL_2 = 2,   /*!< I2S TX PDM信号缩放：x2*/
    I2S_PDM_SIG_SCALING_MUL_4 = 3,   /*!< I2S TX PDM信号缩放：x4*/
} i2s_pdm_sig_scale_t;
#endif

#ifdef __cplusplus
}
#endif

