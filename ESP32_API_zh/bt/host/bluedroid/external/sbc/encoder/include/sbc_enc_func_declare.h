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
 * 函数声明。
 *
 ******************************************************************************/

#ifndef SBC_FUNCDECLARE_H
#define SBC_FUNCDECLARE_H

/*#包括“sbc_encoder.h”*/
/* 全局数据*/
#if (SBC_IS_64_MULT_IN_WINDOW_ACCU == FALSE)
extern const SINT16 gas32CoeffFor4SBs[];
extern const SINT16 gas32CoeffFor8SBs[];
#else
extern const SINT32 gas32CoeffFor4SBs[];
extern const SINT32 gas32CoeffFor8SBs[];
#endif

/* 全局功能*/

extern void sbc_enc_bit_alloc_mono(SBC_ENC_PARAMS *CodecParams);
extern void sbc_enc_bit_alloc_ste(SBC_ENC_PARAMS *CodecParams);

extern void SbcAnalysisInit (void);

extern void SbcAnalysisFilter4(SBC_ENC_PARAMS *strEncParams);
extern void SbcAnalysisFilter8(SBC_ENC_PARAMS *strEncParams);

extern void SBC_FastIDCT8 (SINT32 *pInVect, SINT32 *pOutVect);
extern void SBC_FastIDCT4 (SINT32 *x0, SINT32 *pOutVect);

extern void EncPacking(SBC_ENC_PARAMS *strEncParams);
extern void EncQuantizer(SBC_ENC_PARAMS *);
#if (SBC_DSP_OPT==TRUE)
SINT32 SBC_Multiply_32_16_Simplified(SINT32 s32In2Temp, SINT32 s32In1Temp);
#endif
#endif

