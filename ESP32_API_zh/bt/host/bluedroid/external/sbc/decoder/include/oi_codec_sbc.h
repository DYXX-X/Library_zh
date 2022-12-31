/******************************************************************************
 * 版权所有（C）2014 Android开源项目版权所有2003-2004 Open Interface North America，Inc.保留所有权利。
 *
 *  根据Apache许可证2.0版（“许可证”）获得许可；除非符合许可证，否则不得使用此文件。您可以在以下地址获取许可证副本：
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 *  除非适用法律要求或书面同意，否则根据许可证分发的软件是按“原样”分发的，无任何明示或暗示的担保或条件。有关许可证下权限和限制的具体语言，请参阅许可证。
 *
 ******************************************************************************/

/**********************************************************************************
  $版本：#1$
***********************************************************************************/

#ifndef _OI_CODEC_SBC_CORE_H
#define _OI_CODEC_SBC_CORE_H

#ifdef __cplusplus
extern "C" {
#endif

/**
@文件编解码器函数、数据类型和宏的声明。

@内部组代码库
*/

/**
@添加组代码库
@{
*/

/* 编解码器的非BM3用户必须包括oi_codec_sbc_bm3defs。h，否则这些include将失败，因为BM3 SDK不在include路径中*/
#ifndef _OI_CODEC_SBC_BM3DEFS_H
#include "oi_stddefs.h"
#include "oi_status.h"
#endif

#include <stdint.h>

#define SBC_MAX_CHANNELS 2
#define SBC_MAX_BANDS 8
#define SBC_MAX_BLOCKS 16
#define SBC_MIN_BITPOOL 2   /**<用于编码流的比特分配池的最小大小*/
#define SBC_MAX_BITPOOL 250 /**<用于编码流的位分配池的最大大小*/
#define SBC_MAX_ONE_CHANNEL_BPS 320000
#define SBC_MAX_TWO_CHANNEL_BPS 512000


#define SBC_WBS_BITRATE 62000
#define SBC_WBS_BITPOOL 27
#define SBC_WBS_NROF_BLOCKS 16
#define SBC_WBS_FRAME_LEN 62
#define SBC_WBS_SAMPLES_PER_FRAME 128


#define SBC_HEADER_LEN 4
#define SBC_MAX_FRAME_LEN (SBC_HEADER_LEN + \
                             ((SBC_MAX_BANDS * SBC_MAX_CHANNELS / 2) + \
                              (SBC_MAX_BANDS + SBC_MAX_BLOCKS * SBC_MAX_BITPOOL + 7)/8))
#define SBC_MAX_SAMPLES_PER_FRAME   (SBC_MAX_BANDS * SBC_MAX_BLOCKS)

#define SBC_MAX_SCALEFACTOR_BYTES ((4*(SBC_MAX_CHANNELS * SBC_MAX_BANDS) + 7)/8)

#define OI_SBC_SYNCWORD 0x9c
#define OI_SBC_ENHANCED_SYNCWORD 0x9d
#define OI_mSBC_SYNCWORD 0xad

#define OI_SBC_MODE_STD      0
#define OI_SBC_MODE_MSBC     1

/**@name采样频率*/
/**@{*/
#define SBC_FREQ_16000 0 /**<采样频率为16 kHz。OI_CODEC_SBC_EncoderConfigure（）的@a频率参数的一个可能值*/
#define SBC_FREQ_32000 1 /**<采样频率为32 kHz。OI_CODEC_SBC_EncoderConfigure（）的@a频率参数的一个可能值*/
#define SBC_FREQ_44100 2 /**<采样频率为44.1 kHz。OI_CODEC_SBC_EncoderConfigure（）的@a频率参数的一个可能值*/
#define SBC_FREQ_48000 3 /**<采样频率为48 kHz。OI_CODEC_SBC_EncoderConfigure（）的@a频率参数的一个可能值*/
/**@}*/

/**@名称通道模式*/
/**@{*/
#define SBC_MONO 0         /**<编码信道的模式为单声道。OI_CODEC_SBC_EncoderConfigure（）的@a模式参数的一个可能值*/
#define SBC_DUAL_CHANNEL 1 /**<编码信道的模式为双信道。OI_CODEC_SBC_EncoderConfigure（）的@a模式参数的一个可能值*/
#define SBC_STEREO 2       /**<编码频道的模式为立体声。OI_CODEC_SBC_EncoderConfigure（）的@a模式参数的一个可能值*/
#define SBC_JOINT_STEREO 3 /**<编码频道的模式为联合立体声。OI_CODEC_SBC_EncoderConfigure（）的@a模式参数的一个可能值*/
/**@}*/

/**@名称子带*/
/**@{*/
#define SBC_SUBBANDS_4  0 /**<编码流具有4个子带。OI_CODEC_SBC_EncoderConfigure（）的@a子带参数的一个可能值*/
#define SBC_SUBBANDS_8  1 /**<编码流具有8个子带。OI_CODEC_SBC_EncoderConfigure（）的@a子带参数的一个可能值*/
/**@}*/

/**@name块长度*/
/**@{*/
#define SBC_BLOCKS_4    0 /**<使用4个块的块大小来编码流。OI_CODEC_SBC_EncoderConfigure（）的@a块参数的一个可能值*/
#define SBC_BLOCKS_8    1 /**<8个块的块大小用于对流进行编码。OI_CODEC_SBC_EncoderConfigure（）的@A块参数的一个可能值*/
#define SBC_BLOCKS_12   2 /**<使用12个块的块大小来编码流。OI_CODEC_SBC_EncoderConfigure（）的@a块参数的一个可能值*/
#define SBC_BLOCKS_16   3 /**<使用16个块的块大小来编码流。OI_CODEC_SBC_EncoderConfigure（）的@a块参数的一个可能值*/
/**@}*/

/**@name位分配方法*/
/**@{*/
#define SBC_LOUDNESS 0    /**<位分配方法。OI_CODEC_SBC_EncoderConfigure（）的@a响度参数的一个可能值*/
#define SBC_SNR 1         /**<位分配方法。OI_CODEC_SBC_EncoderConfigure（）的@a响度参数的一个可能值*/
/**@}*/

/**
@}

@添加组代码_内部
@{
*/

typedef OI_INT16 SBC_BUFFER_T;


/**内部使用。*/
typedef struct {
    OI_UINT16 frequency;    /**<采样频率。输入参数。*/
    OI_UINT8 freqIndex;

    OI_UINT8 nrof_blocks;   /**<用于编码流的块大小。输入参数。*/
    OI_UINT8 blocks;


    OI_UINT8 nrof_subbands; /**<编码流的子带数。输入参数。*/
    OI_UINT8 subbands;

    OI_UINT8 mode;          /**<编码频道的模式。输入参数。*/
    OI_UINT8 nrof_channels; /**<编码流的通道数。*/

    OI_UINT8 alloc;         /**<位分配方法。输入参数。*/
    OI_UINT8 bitpool;       /**<用于编码流的比特分配池的大小。输入参数。*/
    OI_UINT8 crc;           /**<用于错误检测的奇偶校验字节。*/
    OI_UINT8 join;          /**<是否使用了联合立体声。*/
    OI_UINT8 enhanced;
    OI_UINT8 min_bitpool;   /**<此值仅在编码时使用。SBC_MAX_BITPOOL（如果不允许使用可变位池），否则为位分配器将使用的最小位池大小。*/

    OI_UINT8 cachedInfo;    /**<关于上一帧的信息*/
} OI_CODEC_SBC_FRAME_INFO;

/**内部使用。*/
typedef struct {
    const OI_CHAR *codecInfo;
    OI_CODEC_SBC_FRAME_INFO frameInfo;
    OI_INT8 scale_factor[SBC_MAX_CHANNELS * SBC_MAX_BANDS];
    OI_UINT32 frameCount;
    OI_INT32 *subdata;

    SBC_BUFFER_T *filterBuffer[SBC_MAX_CHANNELS];
    OI_INT32 filterBufferLen;
    OI_UINT filterBufferOffset;

    union {
        OI_UINT8 uint8[SBC_MAX_CHANNELS * SBC_MAX_BANDS];
        OI_UINT32 uint32[SBC_MAX_CHANNELS * SBC_MAX_BANDS / 4];
    } bits;
    OI_UINT8 maxBitneed;    /**<运行最大位需求*/
    OI_BYTE formatByte;
    OI_UINT8 pcmStride;
    OI_UINT8 maxChannels;
} OI_CODEC_SBC_COMMON_CONTEXT;


/*
 * 较小的值以增加CPU使用为代价减少RAM使用。建议值在27..50范围内，超过50时，CPU使用率会降低。
 */
#define SBC_CODEC_MIN_FILTER_BUFFERS 16
#define SBC_CODEC_FAST_FILTER_BUFFERS 27

/* 扩展到所需的OI_UINT32数量，以确保有足够的内存来使用numBuffers缓冲区对numChannels通道的流进行编码或解码。示例：OI_UINT32解码器数据[CODEC_DATA_WORDS（SBC_MAX_CHANNELS，SBC_DECODER_FAST_SYNTHESIS_BUFFERS）]；
 * */
#define CODEC_DATA_WORDS(numChannels, numBuffers) \
    ((\
        (sizeof(OI_INT32) * SBC_MAX_BLOCKS * numChannels * SBC_MAX_BANDS) \
         + (sizeof(SBC_BUFFER_T) * SBC_MAX_CHANNELS * SBC_MAX_BANDS * numBuffers) \
         + (sizeof (OI_UINT32) - 1) \
    ) / sizeof(OI_UINT32))

/**解码函数的不透明参数；维护解码器上下文。*/
typedef struct {
    OI_CODEC_SBC_COMMON_CONTEXT common;
    OI_UINT8 limitFrameFormat;              /* 布尔值，由OI_CODEC_SBC_DecoderLimit（）设置*/
    OI_UINT8 restrictSubbands;
    OI_UINT8 enhancedEnabled;
    OI_UINT8 bufferedBlocks;
    OI_UINT8 sbc_mode;                      /* OI_SBC_MODE_STD或OI_SBC_MODE_MSBC*/
} OI_CODEC_SBC_DECODER_CONTEXT;

typedef struct {
    OI_UINT32 data[CODEC_DATA_WORDS(1, SBC_CODEC_FAST_FILTER_BUFFERS)];
} OI_CODEC_SBC_CODEC_DATA_MONO;

typedef struct {
    OI_UINT32 data[CODEC_DATA_WORDS(2, SBC_CODEC_FAST_FILTER_BUFFERS)];
} OI_CODEC_SBC_CODEC_DATA_STEREO;

/**
@}

@添加组代码库
@{
*/

/**
 * 此功能重置解码器。在更改流时，或者如果以下流参数发生更改，则必须重置上下文：子带数、立体声模式或频率。
 *
 * @param context   指向要重置的解码器上下文结构的指针。
 *
 * @param enhanced  如果为true，则启用增强的SBC操作。如果启用，则编解码器将识别用于解码增强SBC流的替代同步字。除非已知流是由增强型编码器生成的，或者如果同步丢失，则很有可能解码故障，否则不应启用增强功能。
 */
OI_STATUS OI_CODEC_SBC_DecoderReset(OI_CODEC_SBC_DECODER_CONTEXT *context,
                                    OI_UINT32 *decoderData,
                                    OI_UINT32 decoderDataBytes,
                                    OI_UINT8 maxChannels,
                                    OI_UINT8 pcmStride,
                                    OI_BOOL enhanced,
                                    OI_BOOL msbc_enable);

/**
 * 此函数限制解码器将处理的SBC帧的类型。它的使用是可选的。如果使用，则必须在调用OI_CODEC_SBC_DecoderReset（）后调用它。调用后，将拒绝使用不符合子带和增强SBC设置的SBC帧对OI_CODEC_SBC_DecodeFrame（）的任何调用，并返回OI_STATUS_INVALID_PARAMETERS。
 *
 * @param context   指向要限制的解码器上下文结构的指针。
 *
 * @param enhanced  如果为真，则传递到解码器的所有帧必须是增强SBC帧。如果为假，则所有帧必须为标准SBC帧。
 *
 * @param subbands  可以设置为SBC_SUBBANDS_4或SBC_SUBBANDS_8。传递到解码器的所有帧必须使用所请求的子带数进行编码。
 *
 */
OI_STATUS OI_CODEC_SBC_DecoderLimit(OI_CODEC_SBC_DECODER_CONTEXT *context,
                                    OI_BOOL enhanced,
                                    OI_UINT8 subbands);

/**
 * 此函数设置原始解码的解码器参数，其中解码器参数在sbc数据流中不可用。在调用此函数之前，必须调用OI_CODEC_SBC_DecoderReset。
 *
 * @param context        解码器上下文结构。这必须是每次解码帧时必须使用的上下文。
 *
 * @param enhanced       设置为TRUE可实现高通公司专有的质量增强。
 *
 * @param frequency      SBC_FREQ_16000、SBC_FREQ.32000、SBC_FREQ_44100、SBC_FREQ_48000之一
 *
 * @param mode           SBC_MONO、SBC_DUAL_CHANNEL、SBC_STEREO和SBC_JOIN_STEREO之一
 *
 * @param subbands       SBC_SUBBANDS_4、SBC_SUBBANDS_8之一
 *
 * @param blocks         SBC_BLOCKS_4、SBC_BLOCK S_8、SBC_BLACKS_12、SBC_ BLOCKS_16之一
 *
 * @param alloc          SBC_LOUDNESS、SBC_SNR之一
 *
 * @param maxBitpool     此上下文的最大位池大小
 */
OI_STATUS OI_CODEC_SBC_DecoderConfigureRaw(OI_CODEC_SBC_DECODER_CONTEXT *context,
        OI_BOOL enhanced,
        OI_UINT8 frequency,
        OI_UINT8 mode,
        OI_UINT8 subbands,
        OI_UINT8 blocks,
        OI_UINT8 alloc,
        OI_UINT8 maxBitpool);

/**
 * 解码一个SBC帧。该帧没有标头字节。上下文之前必须已通过调用OI_CODEC_SBC_DecoderConfigureRaw（）初始化。
 *
 * @param context       指向解码器上下文结构的指针。每次从同一流解码时必须使用相同的上下文。
 *
 * @param bitpool       此帧的实际位池大小。必须<=调用OI_CODEC_SBC_DecoderConfigureRaw（）时指定的最大比特池，
 *
 * @param frameData     指向要解码的SBC数据的指针的地址。该值将在成功解码后更新为指向下一帧。
 *
 * @param frameBytes    指向包含帧数据可用字节数的UINT32的指针。该值将被更新以反映解码操作后剩余的字节数。
 *
 * @param pcmData       OI_INT16对数组的地址，将用解码的音频数据填充。此地址未更新。
 *
 * @param pcmBytes      指向UINT32输入/输出参数的指针。在输入时，它应该包含可用于pcm数据的字节数。在输出时，它将包含写入的字节数。注意，这与frameBytes的语义不同。
 */
OI_STATUS OI_CODEC_SBC_DecodeRaw(OI_CODEC_SBC_DECODER_CONTEXT *context,
                                 OI_UINT8 bitpool,
                                 const OI_BYTE **frameData,
                                 OI_UINT32 *frameBytes,
                                 OI_INT16 *pcmData,
                                 OI_UINT32 *pcmBytes);

/**
 * 解码一个SBC帧。
 *
 * @param context       指向解码器上下文结构的指针。每次从同一流解码时必须使用相同的上下文。
 *
 * @param frameData     指向要解码的SBC数据的指针的地址。该值将在成功解码后更新为指向下一帧。
 *
 * @param frameBytes    指向包含帧数据可用字节数的UINT32的指针。该值将被更新以反映解码操作后剩余的字节数。
 *
 * @param pcmData       OI_INT16对数组的地址，将用解码的音频数据填充。此地址未更新。
 *
 * @param pcmBytes      指向UINT32输入/输出参数的指针。在输入时，它应该包含可用于pcm数据的字节数。在输出时，它将包含写入的字节数。注意，这与frameBytes的语义不同。
 */
OI_STATUS OI_CODEC_SBC_DecodeFrame(OI_CODEC_SBC_DECODER_CONTEXT *context,
                                   const OI_BYTE **frameData,
                                   OI_UINT32 *frameBytes,
                                   OI_INT16 *pcmData,
                                   OI_UINT32 *pcmBytes);

/**
 * 计算SBC帧的数量，但不解码。未检查CRC，但在计数计算之前找到Sync字。
 *
 * @param frameData     指向SBC数据的指针。
 *
 * @param frameBytes    frameData缓冲区中可用的字节数
 *
 */
OI_UINT8 OI_CODEC_SBC_FrameCount(OI_BYTE  *frameData,
                                 OI_UINT32 frameBytes);

/**
 * 分析SBC帧，但不进行解码。
 *
 * @param context       指向解码器上下文结构的指针。每次从同一流解码时必须使用相同的上下文。
 *
 * @param frameData     指向要解码的SBC数据的指针的地址。该值将在成功解码后更新为指向下一帧。
 *
 * @param frameBytes    指向包含帧数据可用字节数的UINT32的指针。该值将被更新以反映解码操作后剩余的字节数。
 *
 */
OI_STATUS OI_CODEC_SBC_SkipFrame(OI_CODEC_SBC_DECODER_CONTEXT *context,
                                 const OI_BYTE **frameData,
                                 OI_UINT32 *frameBytes);

/* 常用功能*/

/**
  计算框架长度。

  @param frame要计算其长度的帧

  @返回单个编码帧的长度（以字节为单位）
  */
OI_UINT16 OI_CODEC_SBC_CalculateFramelen(OI_CODEC_SBC_FRAME_INFO *frame);


/**
 * 计算适合给定帧长度的最大位池大小。
 *
 * @param frame     要计算其位池大小的帧
 * @param frameLen  适合位池的帧长度
 *
 * @return 适合指定帧长度的最大位池
 */
OI_UINT16 OI_CODEC_SBC_CalculateBitpool(OI_CODEC_SBC_FRAME_INFO *frame,
                                        OI_UINT16 frameLen);

/**
  计算比特率。

  @param frame要计算其比特率的帧

  @假设流参数是恒定的，返回近似的比特率（以比特每秒为单位）
  */
OI_UINT32 OI_CODEC_SBC_CalculateBitrate(OI_CODEC_SBC_FRAME_INFO *frame);

/**
  计算一帧的解码音频数据长度。

  @param frame要计算其音频数据长度的帧

  @单个帧的解码音频数据的返回长度，以字节为单位
  */
OI_UINT16 OI_CODEC_SBC_CalculatePcmBytes(OI_CODEC_SBC_COMMON_CONTEXT *common);

/**
 * 获取编解码器版本文本。
 *
 * @return  指向包含编解码器版本文本的文本字符串的指针
 *
 */
OI_CHAR *OI_CODEC_Version(void);


/**
@}

@添加组代码_内部
@{
*/

extern const OI_CHAR *const OI_CODEC_SBC_FreqText[];
extern const OI_CHAR *const OI_CODEC_SBC_ModeText[];
extern const OI_CHAR *const OI_CODEC_SBC_SubbandsText[];
extern const OI_CHAR *const OI_CODEC_SBC_BlocksText[];
extern const OI_CHAR *const OI_CODEC_SBC_AllocText[];

/**
@}

@添加组代码库
@{
*/

#ifdef OI_DEBUG
void OI_CODEC_SBC_DumpConfig(OI_CODEC_SBC_FRAME_INFO *frameInfo);
#else
#define OI_CODEC_SBC_DumpConfig(f)
#endif

/**
@}
*/

#ifdef __cplusplus
}
#endif


#endif /* _OI_CODEC_SBC_CORE_H */

