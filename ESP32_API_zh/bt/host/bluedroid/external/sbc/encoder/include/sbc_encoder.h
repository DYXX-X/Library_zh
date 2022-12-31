/******************************************************************************
 * 版权所有（C）1999-2012 Broadcom Corporation
 *
 *  根据Apache许可证2.0版（“许可证”）获得许可；除非符合许可证，否则不得使用此文件。您可以在以下地址获取许可证副本：
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 *  除非适用法律要求或书面同意，否则根据许可证分发的软件是按“原样”分发的，无任何明示或暗示的担保或条件。有关许可证下权限和限制的具体语言，请参阅许可证。
 *
 ******************************************************************************/

/******************************************************************************
 * 此文件包含编码器使用的常量和结构。
 *
 ******************************************************************************/

#ifndef SBC_ENCODER_H
#define SBC_ENCODER_H

#define ENCODER_VERSION "0025"

#ifdef BUILDCFG
#include "common/bt_target.h"
#endif

/*DEFINES*/
#ifndef FALSE
#define FALSE 0
#endif

#ifndef TRUE
#define TRUE (!FALSE)
#endif

#define SBC_MAX_NUM_OF_SUBBANDS 8
#define SBC_MAX_NUM_OF_CHANNELS 2
#define SBC_MAX_NUM_OF_BLOCKS   16

#define SBC_LOUDNESS    0
#define SBC_SNR 1

#define SUB_BANDS_8 8
#define SUB_BANDS_4 4

#define SBC_sf16000 0
#define SBC_sf32000 1
#define SBC_sf44100 2
#define SBC_sf48000 3

#define SBC_MONO    0
#define SBC_DUAL    1
#define SBC_STEREO  2
#define SBC_JOINT_STEREO    3

#define SBC_BLOCK_0 4
#define SBC_BLOCK_1 8
#define SBC_BLOCK_2 12
#define SBC_BLOCK_3 16

#define SBC_NULL    0

#define SBC_MODE_STD      0
#define SBC_MODE_MSBC     1

#define SBC_SYNC_WORD_STD        (0x9C)
#define SBC_SYNC_WORD_MSBC       (0xAD)

#ifndef SBC_MAX_NUM_FRAME
#define SBC_MAX_NUM_FRAME 1
#endif

#ifndef SBC_DSP_OPT
#define SBC_DSP_OPT FALSE
#endif

/* 将SBC_USE_ARM_PRAGMA设置为TRUE以使用“#PRAGMA ARM section zidata”*/
#ifndef SBC_USE_ARM_PRAGMA
#define SBC_USE_ARM_PRAGMA FALSE
#endif

/* 如果目标是ARM，则将SBC_ARM_ASM_OPT设置为TRUE*/
/* 这将用内联汇编代码替换所有32位和64位多位*/
#ifndef SBC_ARM_ASM_OPT
#define SBC_ARM_ASM_OPT FALSE
#endif

/* green-hill编译器选项->用于区分内联汇编代码的语法*/
#ifndef SBC_GHS_COMPILER
#define SBC_GHS_COMPILER FALSE
#endif

/* ARM编译器选项->用于区分内联汇编代码的语法*/
#ifndef SBC_ARM_COMPILER
#define SBC_ARM_COMPILER TRUE
#endif

/* 如果目标是ARM，则将SBC_IPAQ_OPT设置为TRUE*/
/* 32位和64位多路复用将使用SINT64（通常为__int64）强制执行，如果支持，通常会提供最佳性能*/
#ifndef SBC_IPAQ_OPT
#define SBC_IPAQ_OPT TRUE
#endif

/* 仅限调试：将SBC_IS_64_MULT_IN_WINDOW_ACCU设置为TRUE以在窗口中使用64位乘法*/
/* ->不建议为相同的恢复提供更多MIPS。*/
#ifndef SBC_IS_64_MULT_IN_WINDOW_ACCU
#define SBC_IS_64_MULT_IN_WINDOW_ACCU  FALSE
#endif /*SBC_IS_64_MULT_IN_WINDOW_ACCU */

/* 将SBC_IS_64_MULT_IN_IDCT设置为TRUE，以在矩阵化DCT中使用64位乘法*/
/* ->更好的音频质量需要更多的MIPS。与SIG实用程序的比较显示RMS除以10*/
/* 警告：仅当SBC_FAST_DCT设置为TRUE时才适用*/
#ifndef SBC_IS_64_MULT_IN_IDCT
#define SBC_IS_64_MULT_IN_IDCT  FALSE
#endif /*SBC_IS_64_MULT_IN_IDCT */

/* 将SBC_IS_64_MULT_IN_QUANTIZER设置为TRUE以在量化器中使用64位乘法*/
/* 将此标志设置为FALSE会增加5.5和11KHz的哨声噪声，通常人类的听觉无法察觉。*/
#ifndef SBC_IS_64_MULT_IN_QUANTIZER
#define SBC_IS_64_MULT_IN_QUANTIZER  TRUE
#endif /*SBC_IS_64_MULT_IN_IDCT */

/* 仅调试：将此标志设置为FALSE以禁用快速DCT算法*/
#ifndef SBC_FAST_DCT
#define SBC_FAST_DCT  TRUE
#endif /*SBC_FAST_DCT */

/* 如果我们不使用联合立体声模式，标志将保存一些RAM和ROM，以防设置为FALSE*/
#ifndef SBC_JOINT_STE_INCLUDED
#define SBC_JOINT_STE_INCLUDED TRUE
#endif

/* TRUE->应用程序应提供PCM缓冲区，FALSE PCM缓冲区驻留在SBC_ENC_PARAMS中*/
#ifndef SBC_NO_PCM_CPY_OPTION
#define SBC_NO_PCM_CPY_OPTION FALSE
#endif

#define MINIMUM_ENC_VX_BUFFER_SIZE (8*10*2)
#ifndef ENC_VX_BUFFER_SIZE
#define ENC_VX_BUFFER_SIZE (MINIMUM_ENC_VX_BUFFER_SIZE + 64)
/*#定义ENC_VX_BUFFER_SIZE MINIMUM_ENC_VX_BUFER_SIZE+1024*/
#endif

#ifndef SBC_FOR_EMBEDDED_LINUX
#define SBC_FOR_EMBEDDED_LINUX FALSE
#endif

/*用于指数计算的常数*/
#define SBC_BLK (SBC_MAX_NUM_OF_CHANNELS * SBC_MAX_NUM_OF_SUBBANDS)

#include "sbc_types.h"

typedef struct SBC_ENC_PARAMS_TAG {
    SINT16 s16SamplingFreq;                         /* 16k、32k、44.1k或48k*/
    SINT16 s16ChannelMode;                          /* 单、双、应力或关节应力*/
    SINT16 s16NumOfSubBands;                        /* 4或8*/
    SINT16 s16NumOfChannels;
    SINT16 s16NumOfBlocks;                          /* 4、8、12或16*/
    SINT16 s16AllocationMethod;                     /* 响度或SNR*/
    SINT16 s16BitPool;                              /* 16*numOfSb用于单声道和双声道；32*numOfSb用于立体声和联合立体声*/
    UINT16 u16BitRate;
    UINT8  sbc_mode;                                /* SBC_MODE_STD或SBC_MODEM_MSBC*/
    UINT8   u8NumPacketToEncode;                    /* 要编码的sbc帧数。默认值为1*/
#if (SBC_JOINT_STE_INCLUDED == TRUE)
    SINT16 as16Join[SBC_MAX_NUM_OF_SUBBANDS];       /*如果JS为1，否则为0*/
#endif

    SINT16 s16MaxBitNeed;
    SINT16 as16ScaleFactor[SBC_MAX_NUM_OF_CHANNELS * SBC_MAX_NUM_OF_SUBBANDS];

    SINT16 *ps16NextPcmBuffer;
#if (SBC_NO_PCM_CPY_OPTION == TRUE)
    SINT16 *ps16PcmBuffer;
#else
    SINT16 as16PcmBuffer[SBC_MAX_NUM_FRAME * SBC_MAX_NUM_OF_BLOCKS * SBC_MAX_NUM_OF_CHANNELS * SBC_MAX_NUM_OF_SUBBANDS];
#endif

    SINT16  s16ScartchMemForBitAlloc[16];

    SINT32  s32SbBuffer[SBC_MAX_NUM_OF_CHANNELS * SBC_MAX_NUM_OF_SUBBANDS * SBC_MAX_NUM_OF_BLOCKS];

    SINT16 as16Bits[SBC_MAX_NUM_OF_CHANNELS * SBC_MAX_NUM_OF_SUBBANDS];

    UINT8  *pu8Packet;
    UINT8  *pu8NextPacket;
    UINT16 FrameHeader;
    UINT16 u16PacketLength;

} SBC_ENC_PARAMS;

#ifdef __cplusplus
extern "C"
{
#endif
extern void SBC_Encoder(SBC_ENC_PARAMS *strEncParams);
extern void SBC_Encoder_Init(SBC_ENC_PARAMS *strEncParams);
#ifdef __cplusplus
}
#endif
#endif

