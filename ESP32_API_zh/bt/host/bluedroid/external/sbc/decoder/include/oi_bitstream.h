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
#ifndef _OI_BITSTREAM_H
#define _OI_BITSTREAM_H

/**********************************************************************************
  $版本：#1$
***********************************************************************************/


/**
@fileFunction原型和用于操作输入和输出流的宏定义。

@内部组代码_内部
*/

/**
@添加组代码_内部
@{
*/

#include "oi_codec_sbc_private.h"
#include "oi_stddefs.h"

INLINE void OI_BITSTREAM_ReadInit(OI_BITSTREAM *bs, const OI_BYTE *buffer);

INLINE void OI_BITSTREAM_WriteInit(OI_BITSTREAM *bs, OI_BYTE *buffer);

INLINE OI_UINT32 OI_BITSTREAM_ReadUINT(OI_BITSTREAM *bs, OI_UINT bits);

INLINE OI_UINT8 OI_BITSTREAM_ReadUINT4Aligned(OI_BITSTREAM *bs);

INLINE OI_UINT8 OI_BITSTREAM_ReadUINT8Aligned(OI_BITSTREAM *bs);

INLINE void OI_BITSTREAM_WriteUINT(OI_BITSTREAM *bs,
                                   OI_UINT16 value,
                                   OI_UINT bits);

/*
 * 使用位流对齐的知识来优化字节的写入
 */
PRIVATE void OI_BITSTREAM_WriteUINT8Aligned(OI_BITSTREAM *bs,
        OI_UINT8 datum);

/*
 * 使用位流对齐的知识来优化半字节的写入对
 */
PRIVATE void OI_BITSTREAM_Write2xUINT4Aligned(OI_BITSTREAM *bs,
        OI_UINT8 datum1,
        OI_UINT8 datum2);

/** 在内部，比特流在流中向前看。当OI_SBC_ReadScalefactors（）暂时中断抽象时，它需要知道“逻辑”指针在流中的位置。
 */
#define OI_BITSTREAM_GetWritePtr(bs) ((bs)->ptr.w - 3)
#define OI_BITSTREAM_GetReadPtr(bs) ((bs)->ptr.r - 3)

/** 这在这里声明为宏，因为解码器。由于效率原因，c破坏了bitsream封装。
 */
#define OI_BITSTREAM_READUINT(result, bits, ptr, value, bitPtr) \
do { \
    OI_ASSERT((bits) <= 16); \
    OI_ASSERT((bitPtr) < 16); \
    OI_ASSERT((bitPtr) >= 8); \
    \
    result = (value) << (bitPtr); \
    result >>= 32 - (bits); \
    \
    bitPtr += (bits); \
    while (bitPtr >= 16) { \
        value = ((value) << 8) | *ptr++; \
        bitPtr -= 8; \
    } \
    OI_ASSERT((bits == 0) || (result < (1u << (bits)))); \
} while (0)


#define OI_BITSTREAM_WRITEUINT(ptr, value, bitPtr, datum, bits) \
do {\
    bitPtr -= bits;\
    value |= datum << bitPtr;\
    \
    while (bitPtr <= 16) {\
        bitPtr += 8;\
        *ptr++ = (OI_UINT8)(value >> 24);\
        value <<= 8;\
    }\
} while (0)

#define OI_BITSTREAM_WRITEFLUSH(ptr, value, bitPtr) \
do {\
    while (bitPtr < 32) {\
        bitPtr += 8;\
        *ptr++ = (OI_UINT8)(value >> 24);\
        value <<= 8;\
    }\
} while (0)

/**
@}
*/

#endif /* _OI_BITSTREAM_H */

