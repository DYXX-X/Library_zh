/****************************************************************************
** 版权所有（C）2017 Intel Corporation
**
** 特此免费授予获得本软件和相关文档文件（“软件”）副本的任何人无限制地处理软件的权利，包括但不限于使用、复制、修改、合并、发布、分发、再许可和/或销售软件副本的权利，并允许向其提供软件的人这样做，符合以下条件：
**
** 上述版权声明和本许可声明应包含在软件的所有副本或主要部分中。
**
** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
**
****************************************************************************/

#ifndef CBORINTERNAL_P_H
#define CBORINTERNAL_P_H

#include "compilersupport_p.h"

#ifndef CBOR_NO_FLOATING_POINT
#  include <float.h>
#  include <math.h>
#else
#  ifndef CBOR_NO_HALF_FLOAT_TYPE
#    define CBOR_NO_HALF_FLOAT_TYPE     1
#  endif
#endif

#ifndef CBOR_NO_HALF_FLOAT_TYPE
#  if defined(__F16C__) || defined(__AVX2__)
#    include <immintrin.h>
static inline unsigned short encode_half(float val)
{
    __m128i m = _mm_cvtps_ph(_mm_set_ss(val), _MM_FROUND_CUR_DIRECTION);
    return _mm_extract_epi16(m, 0);
}
static inline float decode_half(unsigned short half)
{
    __m128i m = _mm_cvtsi32_si128(half);
    return _mm_cvtss_f32(_mm_cvtph_ps(m));
}
#  else
/* float-to-fp16转换的软件实现*/
static inline unsigned short encode_half(double val)
{
    uint64_t v;
    int sign, exp, mant;
    memcpy(&v, &val, sizeof(v));
    sign = v >> 63 << 15;
    exp = (v >> 52) & 0x7ff;
    mant = v << 12 >> 12 >> (53-11);    /* 只保留尾数的11个最高有效位*/
    exp -= 1023;
    if (exp == 1024) {
        /* 无限或NaN*/
        exp = 16;
        mant >>= 1;
    } else if (exp >= 16) {
        /* 溢出，作为最大数*/
        exp = 15;
        mant = 1023;
    } else if (exp >= -14) {
        /* 正则正态*/
    } else if (exp >= -24) {
        /* 低于正常值*/
        mant |= 1024;
        mant >>= -(exp + 14);
        exp = -15;
    } else {
        /* 下溢，归零*/
        return 0;
    }

    /* 此处安全强制执行，因为上面的位操作保证不会溢出*/
    return (unsigned short)(sign | ((exp + 15) << 10) | mant);
}

/* 该函数是从RFC 7049附录D中复制和改编的*/
static inline double decode_half(unsigned short half)
{
    int exp = (half >> 10) & 0x1f;
    int mant = half & 0x3ff;
    double val;
    if (exp == 0) val = ldexp(mant, -24);
    else if (exp != 31) val = ldexp(mant + 1024, exp - 25);
    else val = mant == 0 ? INFINITY : NAN;
    return half & 0x8000 ? -val : val;
}
#  endif
#endif /* CBOR_NO_HALF_FLOAT_TYPE */

#ifndef CBOR_INTERNAL_API
#  define CBOR_INTERNAL_API
#endif

#ifndef CBOR_PARSER_MAX_RECURSIONS
#  define CBOR_PARSER_MAX_RECURSIONS 1024
#endif

/*
 * CBOR主要类型在描述符字节的高3位编码请参见http://tools.ietf.org/html/rfc7049#section-2.1
 */
typedef enum CborMajorTypes {
    UnsignedIntegerType = 0U,
    NegativeIntegerType = 1U,
    ByteStringType = 2U,
    TextStringType = 3U,
    ArrayType = 4U,
    MapType = 5U,           /* a、 k.a.对象*/
    TagType = 6U,
    SimpleTypesType = 7U
} CborMajorTypes;

/*
 * 当主类型为7时，在描述符字节的低8位中编码CBOR简单和浮点类型。
 */
typedef enum CborSimpleTypes {
    FalseValue              = 20,
    TrueValue               = 21,
    NullValue               = 22,
    UndefinedValue          = 23,
    SimpleTypeInNextByte    = 24,   /* 不是很简单的类型*/
    HalfPrecisionFloat      = 25,   /* 同上*/
    SinglePrecisionFloat    = 26,   /* 同上*/
    DoublePrecisionFloat    = 27,   /* 同上*/
    Break                   = 31
} CborSimpleTypes;

enum {
    SmallValueBitLength     = 5U,
    SmallValueMask          = (1U << SmallValueBitLength) - 1,      /* 31 */
    Value8Bit               = 24U,
    Value16Bit              = 25U,
    Value32Bit              = 26U,
    Value64Bit              = 27U,
    IndefiniteLength        = 31U,

    MajorTypeShift          = SmallValueBitLength,
    MajorTypeMask           = (int) (~0U << MajorTypeShift),

    BreakByte               = (unsigned)Break | (SimpleTypesType << MajorTypeShift)
};

CBOR_INTERNAL_API CborError CBOR_INTERNAL_API_CC _cbor_value_extract_number(const uint8_t **ptr, const uint8_t *end, uint64_t *len);
CBOR_INTERNAL_API CborError CBOR_INTERNAL_API_CC _cbor_value_prepare_string_iteration(CborValue *it);
CBOR_INTERNAL_API CborError CBOR_INTERNAL_API_CC _cbor_value_get_string_chunk(const CborValue *value, const void **bufferptr,
                                                                              size_t *len, CborValue *next);


#endif /* CBORINTERNAL_P_H */

