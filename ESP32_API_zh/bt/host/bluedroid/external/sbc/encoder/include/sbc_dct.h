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
 * 快速DCT的定义。
 *
 ******************************************************************************/

#ifndef SBC_DCT_H
#define SBC_DCT_H

#if (SBC_ARM_ASM_OPT==TRUE)
#define SBC_MULT_32_16_SIMPLIFIED(s16In2, s32In1, s32OutLow)                    \
{                                                                               \
    __asm                                                                       \
{                                                                               \
    MUL s32OutLow,(SINT32)s16In2, (s32In1>>15)        \
}                                                                               \
}
#else
#if (SBC_DSP_OPT==TRUE)
#define SBC_MULT_32_16_SIMPLIFIED(s16In2, s32In1 , s32OutLow) s32OutLow = SBC_Multiply_32_16_Simplified((SINT32)s16In2,s32In1);
#else
#if (SBC_IPAQ_OPT==TRUE)
/*#定义SBC_MULT_32_16_IMPLIFIED（s16In2，s32In1，s32OutLow）s32OutLow=（SINT32）；*/
#define SBC_MULT_32_16_SIMPLIFIED(s16In2, s32In1 , s32OutLow) s32OutLow=(SINT32)(((SINT64)s16In2*(SINT64)s32In1)>>15);
#if (SBC_IS_64_MULT_IN_IDCT == TRUE)
#define SBC_MULT_32_32(s32In2, s32In1, s32OutLow)                           \
{                                                                           \
    s64Temp = ((SINT64) s32In2) * ((SINT64) s32In1)>>31;            \
    s32OutLow = (SINT32) s64Temp;                                                    \
}
#endif
#else
#define SBC_MULT_32_16_SIMPLIFIED(s16In2, s32In1 , s32OutLow)                   \
{                                                                               \
    s32In1Temp = s32In1;                                                        \
    s32In2Temp = (SINT32)s16In2;                                                \
                                                                                \
    /* 将一个+ve和另一个-ve数相乘*/                             \
    if (s32In1Temp < 0)                                                         \
    {                                                                           \
        s32In1Temp ^= 0xFFFFFFFF;                                               \
        s32In1Temp++;                                                           \
        s32OutLow  = (s32In2Temp * (s32In1Temp >> 16));                         \
        s32OutLow += (( s32In2Temp * (s32In1Temp & 0xFFFF)) >> 16);             \
        s32OutLow ^= 0xFFFFFFFF;                                                \
        s32OutLow++;                                                            \
    }                                                                           \
    else                                                                        \
    {                                                                           \
        s32OutLow  = (s32In2Temp * (s32In1Temp >> 16));                         \
        s32OutLow += (( s32In2Temp * (s32In1Temp & 0xFFFF)) >> 16);             \
    }                                                                           \
    s32OutLow <<= 1;                                                            \
}
#if (SBC_IS_64_MULT_IN_IDCT == TRUE)
#define SBC_MULT_64(s32In1, s32In2, s32OutLow, s32OutHi)  \
{\
        s32OutLow=(SINT32)(((SINT64)s32In1*(SINT64)s32In2)& 0x00000000FFFFFFFF);\
        s32OutHi=(SINT32)(((SINT64)s32In1*(SINT64)s32In2)>>32);\
}
#define SBC_MULT_32_32(s32In2, s32In1, s32OutLow)                           \
{                                                                           \
    s32HiTemp = 0;                                                          \
    SBC_MULT_64(s32In2,s32In1 , s32OutLow, s32HiTemp);                      \
    s32OutLow   = (((s32OutLow>>15)&0x1FFFF) | (s32HiTemp << 17));          \
}
#endif

#endif
#endif
#endif

#endif

