/****************************************************************************
** 版权所有（C）2019 Intel Corporation
**
** 特此免费授予获得本软件和相关文档文件（“软件”）副本的任何人无限制地处理软件的权利，包括但不限于使用、复制、修改、合并、发布、分发、再许可和/或销售软件副本的权利，并允许向其提供软件的人这样做，符合以下条件：
**
** 上述版权声明和本许可声明应包含在软件的所有副本或主要部分中。
**
** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
**
****************************************************************************/

#ifndef CBOR_H
#define CBOR_H

#ifndef assert
#include <assert.h>
#endif
#include <limits.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>

#include "tinycbor-version.h"

#define TINYCBOR_VERSION            ((TINYCBOR_VERSION_MAJOR << 16) | (TINYCBOR_VERSION_MINOR << 8) | TINYCBOR_VERSION_PATCH)

#ifdef __cplusplus
extern "C" {
#else
#include <stdbool.h>
#endif

#ifndef SIZE_MAX
/* 某些系统无法在<stdint中定义SIZE_MAX。h> ，尽管C99需要它……6.3.1.3（有符号和无符号整数）p2中定义了从有符号到无符号的转换，该p2表示：“通过重复添加或减去新类型中可以表示的最大值的一个来转换值，直到该值在新类型的范围内。”因此，通过添加size_MAX+1将-1转换为size_t，这导致SIZE_ MAX。
 */
#  define SIZE_MAX ((size_t)-1)
#endif

#ifndef CBOR_API
#  define CBOR_API
#endif
#ifndef CBOR_PRIVATE_API
#  define CBOR_PRIVATE_API
#endif
#ifndef CBOR_INLINE_API
#  if defined(__cplusplus)
#    define CBOR_INLINE inline
#    define CBOR_INLINE_API inline
#  else
#    define CBOR_INLINE_API static CBOR_INLINE
#    if defined(_MSC_VER)
#      define CBOR_INLINE __inline
#    elif defined(__GNUC__)
#      define CBOR_INLINE __inline__
#    elif defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L
#      define CBOR_INLINE inline
#    else
#      define CBOR_INLINE
#    endif
#  endif
#endif

typedef enum CborType {
    CborIntegerType     = 0x00,
    CborByteStringType  = 0x40,
    CborTextStringType  = 0x60,
    CborArrayType       = 0x80,
    CborMapType         = 0xa0,
    CborTagType         = 0xc0,
    CborSimpleType      = 0xe0,
    CborBooleanType     = 0xf5,
    CborNullType        = 0xf6,
    CborUndefinedType   = 0xf7,
    CborHalfFloatType   = 0xf9,
    CborFloatType       = 0xfa,
    CborDoubleType      = 0xfb,

    CborInvalidType     = 0xff              /* 相当于中断字节，因此永远不会使用*/
} CborType;

typedef uint64_t CborTag;
typedef enum CborKnownTags {
    CborDateTimeStringTag          = 0,
    CborUnixTime_tTag              = 1,
    CborPositiveBignumTag          = 2,
    CborNegativeBignumTag          = 3,
    CborDecimalTag                 = 4,
    CborBigfloatTag                = 5,
    CborCOSE_Encrypt0Tag           = 16,
    CborCOSE_Mac0Tag               = 17,
    CborCOSE_Sign1Tag              = 18,
    CborExpectedBase64urlTag       = 21,
    CborExpectedBase64Tag          = 22,
    CborExpectedBase16Tag          = 23,
    CborEncodedCborTag             = 24,
    CborUrlTag                     = 32,
    CborBase64urlTag               = 33,
    CborBase64Tag                  = 34,
    CborRegularExpressionTag       = 35,
    CborMimeMessageTag             = 36,
    CborCOSE_EncryptTag            = 96,
    CborCOSE_MacTag                = 97,
    CborCOSE_SignTag               = 98,
    CborSignatureTag               = 55799
} CborKnownTags;

/* #定义常量，以便我们可以使用#ifdef进行检查*/
#define CborDateTimeStringTag CborDateTimeStringTag
#define CborUnixTime_tTag CborUnixTime_tTag
#define CborPositiveBignumTag CborPositiveBignumTag
#define CborNegativeBignumTag CborNegativeBignumTag
#define CborDecimalTag CborDecimalTag
#define CborBigfloatTag CborBigfloatTag
#define CborCOSE_Encrypt0Tag CborCOSE_Encrypt0Tag
#define CborCOSE_Mac0Tag CborCOSE_Mac0Tag
#define CborCOSE_Sign1Tag CborCOSE_Sign1Tag
#define CborExpectedBase64urlTag CborExpectedBase64urlTag
#define CborExpectedBase64Tag CborExpectedBase64Tag
#define CborExpectedBase16Tag CborExpectedBase16Tag
#define CborEncodedCborTag CborEncodedCborTag
#define CborUrlTag CborUrlTag
#define CborBase64urlTag CborBase64urlTag
#define CborBase64Tag CborBase64Tag
#define CborRegularExpressionTag CborRegularExpressionTag
#define CborMimeMessageTag CborMimeMessageTag
#define CborCOSE_EncryptTag CborCOSE_EncryptTag
#define CborCOSE_MacTag CborCOSE_MacTag
#define CborCOSE_SignTag CborCOSE_SignTag
#define CborSignatureTag CborSignatureTag

/* 错误API*/

typedef enum CborError {
    CborNoError = 0,

    /* 所有模式中的错误*/
    CborUnknownError,
    CborErrorUnknownLength,         /* 请求数组、映射或字符串中的长度不确定*/
    CborErrorAdvancePastEOF,
    CborErrorIO,

    /* 解析器错误流错误*/
    CborErrorGarbageAtEnd = 256,
    CborErrorUnexpectedEOF,
    CborErrorUnexpectedBreak,
    CborErrorUnknownType,           /* 只能发生在主要类型7中*/
    CborErrorIllegalType,           /* 此处不允许使用类型*/
    CborErrorIllegalNumber,
    CborErrorIllegalSimpleType,     /* 以两个字节编码的小于32的值类型*/

    /* 仅在严格模式解析中出现解析器错误*/
    CborErrorUnknownSimpleType = 512,
    CborErrorUnknownTag,
    CborErrorInappropriateTagForType,
    CborErrorDuplicateObjectKeys,
    CborErrorInvalidUtf8TextString,
    CborErrorExcludedType,
    CborErrorExcludedValue,
    CborErrorImproperValue,
    CborErrorOverlongEncoding,
    CborErrorMapKeyNotString,
    CborErrorMapNotSorted,
    CborErrorMapKeysNotUnique,

    /* 编码器错误*/
    CborErrorTooManyItems = 768,
    CborErrorTooFewItems,

    /* 内部实现错误*/
    CborErrorDataTooLarge = 1024,
    CborErrorNestingTooDeep,
    CborErrorUnsupportedType,

    /* 转换为JSON时出错*/
    CborErrorJsonObjectKeyIsAggregate = 1280,
    CborErrorJsonObjectKeyNotString,
    CborErrorJsonNotImplemented,

    CborErrorOutOfMemory = (int) (~0U / 2 + 1),
    CborErrorInternalError = (int) (~0U / 2)    /* 二进制补码机上的INT_MAX*/
} CborError;

CBOR_API const char *cbor_error_string(CborError error);

/* 编码器API*/
struct CborEncoder
{
    union {
        uint8_t *ptr;
        ptrdiff_t bytes_needed;
    } data;
    const uint8_t *end;
    size_t remaining;
    int flags;
};
typedef struct CborEncoder CborEncoder;

static const size_t CborIndefiniteLength = SIZE_MAX;

CBOR_API void cbor_encoder_init(CborEncoder *encoder, uint8_t *buffer, size_t size, int flags);
CBOR_API CborError cbor_encode_uint(CborEncoder *encoder, uint64_t value);
CBOR_API CborError cbor_encode_int(CborEncoder *encoder, int64_t value);
CBOR_API CborError cbor_encode_negative_int(CborEncoder *encoder, uint64_t absolute_value);
CBOR_API CborError cbor_encode_simple_value(CborEncoder *encoder, uint8_t value);
CBOR_API CborError cbor_encode_tag(CborEncoder *encoder, CborTag tag);
CBOR_API CborError cbor_encode_text_string(CborEncoder *encoder, const char *string, size_t length);
CBOR_INLINE_API CborError cbor_encode_text_stringz(CborEncoder *encoder, const char *string)
{ return cbor_encode_text_string(encoder, string, strlen(string)); }
CBOR_API CborError cbor_encode_byte_string(CborEncoder *encoder, const uint8_t *string, size_t length);
CBOR_API CborError cbor_encode_floating_point(CborEncoder *encoder, CborType fpType, const void *value);

CBOR_INLINE_API CborError cbor_encode_boolean(CborEncoder *encoder, bool value)
{ return cbor_encode_simple_value(encoder, (int)value - 1 + (CborBooleanType & 0x1f)); }
CBOR_INLINE_API CborError cbor_encode_null(CborEncoder *encoder)
{ return cbor_encode_simple_value(encoder, CborNullType & 0x1f); }
CBOR_INLINE_API CborError cbor_encode_undefined(CborEncoder *encoder)
{ return cbor_encode_simple_value(encoder, CborUndefinedType & 0x1f); }

CBOR_INLINE_API CborError cbor_encode_half_float(CborEncoder *encoder, const void *value)
{ return cbor_encode_floating_point(encoder, CborHalfFloatType, value); }
CBOR_INLINE_API CborError cbor_encode_float(CborEncoder *encoder, float value)
{ return cbor_encode_floating_point(encoder, CborFloatType, &value); }
CBOR_INLINE_API CborError cbor_encode_double(CborEncoder *encoder, double value)
{ return cbor_encode_floating_point(encoder, CborDoubleType, &value); }

CBOR_API CborError cbor_encoder_create_array(CborEncoder *encoder, CborEncoder *arrayEncoder, size_t length);
CBOR_API CborError cbor_encoder_create_map(CborEncoder *encoder, CborEncoder *mapEncoder, size_t length);
CBOR_API CborError cbor_encoder_close_container(CborEncoder *encoder, const CborEncoder *containerEncoder);
CBOR_API CborError cbor_encoder_close_container_checked(CborEncoder *encoder, const CborEncoder *containerEncoder);

CBOR_INLINE_API uint8_t *_cbor_encoder_get_buffer_pointer(const CborEncoder *encoder)
{
    return encoder->data.ptr;
}

CBOR_INLINE_API size_t cbor_encoder_get_buffer_size(const CborEncoder *encoder, const uint8_t *buffer)
{
    return (size_t)(encoder->data.ptr - buffer);
}

CBOR_INLINE_API size_t cbor_encoder_get_extra_bytes_needed(const CborEncoder *encoder)
{
    return encoder->end ? 0 : (size_t)encoder->data.bytes_needed;
}

/* 分析器API*/

enum CborParserIteratorFlags
{
    CborIteratorFlag_IntegerValueTooLarge   = 0x01,
    CborIteratorFlag_NegativeInteger        = 0x02,
    CborIteratorFlag_IteratingStringChunks  = 0x02,
    CborIteratorFlag_UnknownLength          = 0x04,
    CborIteratorFlag_ContainerIsMap         = 0x20,
    CborIteratorFlag_NextIsMapKey           = 0x40
};

struct CborParser
{
    const uint8_t *end;
    uint32_t flags;
};
typedef struct CborParser CborParser;

struct CborValue
{
    const CborParser *parser;
    const uint8_t *ptr;
    uint32_t remaining;
    uint16_t extra;
    uint8_t type;
    uint8_t flags;
};
typedef struct CborValue CborValue;

CBOR_API CborError cbor_parser_init(const uint8_t *buffer, size_t size, uint32_t flags, CborParser *parser, CborValue *it);

CBOR_API CborError cbor_value_validate_basic(const CborValue *it);

CBOR_INLINE_API bool cbor_value_at_end(const CborValue *it)
{ return it->remaining == 0; }
CBOR_INLINE_API const uint8_t *cbor_value_get_next_byte(const CborValue *it)
{ return it->ptr; }
CBOR_API CborError cbor_value_advance_fixed(CborValue *it);
CBOR_API CborError cbor_value_advance(CborValue *it);
CBOR_INLINE_API bool cbor_value_is_container(const CborValue *it)
{ return it->type == CborArrayType || it->type == CborMapType; }
CBOR_API CborError cbor_value_enter_container(const CborValue *it, CborValue *recursed);
CBOR_API CborError cbor_value_leave_container(CborValue *it, const CborValue *recursed);

CBOR_PRIVATE_API uint64_t _cbor_value_decode_int64_internal(const CborValue *value);
CBOR_INLINE_API uint64_t _cbor_value_extract_int64_helper(const CborValue *value)
{
    return value->flags & CborIteratorFlag_IntegerValueTooLarge ?
                _cbor_value_decode_int64_internal(value) : value->extra;
}

CBOR_INLINE_API bool cbor_value_is_valid(const CborValue *value)
{ return value && value->type != CborInvalidType; }
CBOR_INLINE_API CborType cbor_value_get_type(const CborValue *value)
{ return (CborType)value->type; }

/* 空的未定义类型（&U）*/
CBOR_INLINE_API bool cbor_value_is_null(const CborValue *value)
{ return value->type == CborNullType; }
CBOR_INLINE_API bool cbor_value_is_undefined(const CborValue *value)
{ return value->type == CborUndefinedType; }

/* 布尔型*/
CBOR_INLINE_API bool cbor_value_is_boolean(const CborValue *value)
{ return value->type == CborBooleanType; }
CBOR_INLINE_API CborError cbor_value_get_boolean(const CborValue *value, bool *result)
{
    assert(cbor_value_is_boolean(value));
    *result = !!value->extra;
    return CborNoError;
}

/* 简单类型*/
CBOR_INLINE_API bool cbor_value_is_simple_type(const CborValue *value)
{ return value->type == CborSimpleType; }
CBOR_INLINE_API CborError cbor_value_get_simple_type(const CborValue *value, uint8_t *result)
{
    assert(cbor_value_is_simple_type(value));
    *result = (uint8_t)value->extra;
    return CborNoError;
}

/* 整数*/
CBOR_INLINE_API bool cbor_value_is_integer(const CborValue *value)
{ return value->type == CborIntegerType; }
CBOR_INLINE_API bool cbor_value_is_unsigned_integer(const CborValue *value)
{ return cbor_value_is_integer(value) && (value->flags & CborIteratorFlag_NegativeInteger) == 0; }
CBOR_INLINE_API bool cbor_value_is_negative_integer(const CborValue *value)
{ return cbor_value_is_integer(value) && (value->flags & CborIteratorFlag_NegativeInteger); }

CBOR_INLINE_API CborError cbor_value_get_raw_integer(const CborValue *value, uint64_t *result)
{
    assert(cbor_value_is_integer(value));
    *result = _cbor_value_extract_int64_helper(value);
    return CborNoError;
}

CBOR_INLINE_API CborError cbor_value_get_uint64(const CborValue *value, uint64_t *result)
{
    assert(cbor_value_is_unsigned_integer(value));
    *result = _cbor_value_extract_int64_helper(value);
    return CborNoError;
}

CBOR_INLINE_API CborError cbor_value_get_int64(const CborValue *value, int64_t *result)
{
    assert(cbor_value_is_integer(value));
    *result = (int64_t) _cbor_value_extract_int64_helper(value);
    if (value->flags & CborIteratorFlag_NegativeInteger)
        *result = -*result - 1;
    return CborNoError;
}

CBOR_INLINE_API CborError cbor_value_get_int(const CborValue *value, int *result)
{
    assert(cbor_value_is_integer(value));
    *result = (int) _cbor_value_extract_int64_helper(value);
    if (value->flags & CborIteratorFlag_NegativeInteger)
        *result = -*result - 1;
    return CborNoError;
}

CBOR_API CborError cbor_value_get_int64_checked(const CborValue *value, int64_t *result);
CBOR_API CborError cbor_value_get_int_checked(const CborValue *value, int *result);

CBOR_INLINE_API bool cbor_value_is_length_known(const CborValue *value)
{ return (value->flags & CborIteratorFlag_UnknownLength) == 0; }

/* 标签*/
CBOR_INLINE_API bool cbor_value_is_tag(const CborValue *value)
{ return value->type == CborTagType; }
CBOR_INLINE_API CborError cbor_value_get_tag(const CborValue *value, CborTag *result)
{
    assert(cbor_value_is_tag(value));
    *result = _cbor_value_extract_int64_helper(value);
    return CborNoError;
}
CBOR_API CborError cbor_value_skip_tag(CborValue *it);

/* 串*/
CBOR_INLINE_API bool cbor_value_is_byte_string(const CborValue *value)
{ return value->type == CborByteStringType; }
CBOR_INLINE_API bool cbor_value_is_text_string(const CborValue *value)
{ return value->type == CborTextStringType; }

CBOR_INLINE_API CborError cbor_value_get_string_length(const CborValue *value, size_t *length)
{
    uint64_t v;
    assert(cbor_value_is_byte_string(value) || cbor_value_is_text_string(value));
    if (!cbor_value_is_length_known(value))
        return CborErrorUnknownLength;
    v = _cbor_value_extract_int64_helper(value);
    *length = (size_t)v;
    if (*length != v)
        return CborErrorDataTooLarge;
    return CborNoError;
}

CBOR_PRIVATE_API CborError _cbor_value_copy_string(const CborValue *value, void *buffer,
                                                   size_t *buflen, CborValue *next);
CBOR_PRIVATE_API CborError _cbor_value_dup_string(const CborValue *value, void **buffer,
                                                  size_t *buflen, CborValue *next);

CBOR_API CborError cbor_value_calculate_string_length(const CborValue *value, size_t *length);

CBOR_INLINE_API CborError cbor_value_copy_text_string(const CborValue *value, char *buffer,
                                                      size_t *buflen, CborValue *next)
{
    assert(cbor_value_is_text_string(value));
    return _cbor_value_copy_string(value, buffer, buflen, next);
}
CBOR_INLINE_API CborError cbor_value_copy_byte_string(const CborValue *value, uint8_t *buffer,
                                                      size_t *buflen, CborValue *next)
{
    assert(cbor_value_is_byte_string(value));
    return _cbor_value_copy_string(value, buffer, buflen, next);
}

CBOR_INLINE_API CborError cbor_value_dup_text_string(const CborValue *value, char **buffer,
                                                     size_t *buflen, CborValue *next)
{
    assert(cbor_value_is_text_string(value));
    return _cbor_value_dup_string(value, (void **)buffer, buflen, next);
}
CBOR_INLINE_API CborError cbor_value_dup_byte_string(const CborValue *value, uint8_t **buffer,
                                                     size_t *buflen, CborValue *next)
{
    assert(cbor_value_is_byte_string(value));
    return _cbor_value_dup_string(value, (void **)buffer, buflen, next);
}

CBOR_API CborError cbor_value_text_string_equals(const CborValue *value, const char *string, bool *result);

/* 地图和阵列*/
CBOR_INLINE_API bool cbor_value_is_array(const CborValue *value)
{ return value->type == CborArrayType; }
CBOR_INLINE_API bool cbor_value_is_map(const CborValue *value)
{ return value->type == CborMapType; }

CBOR_INLINE_API CborError cbor_value_get_array_length(const CborValue *value, size_t *length)
{
    uint64_t v;
    assert(cbor_value_is_array(value));
    if (!cbor_value_is_length_known(value))
        return CborErrorUnknownLength;
    v = _cbor_value_extract_int64_helper(value);
    *length = (size_t)v;
    if (*length != v)
        return CborErrorDataTooLarge;
    return CborNoError;
}

CBOR_INLINE_API CborError cbor_value_get_map_length(const CborValue *value, size_t *length)
{
    uint64_t v;
    assert(cbor_value_is_map(value));
    if (!cbor_value_is_length_known(value))
        return CborErrorUnknownLength;
    v = _cbor_value_extract_int64_helper(value);
    *length = (size_t)v;
    if (*length != v)
        return CborErrorDataTooLarge;
    return CborNoError;
}

CBOR_API CborError cbor_value_map_find_value(const CborValue *map, const char *string, CborValue *element);

/* 浮点*/
CBOR_INLINE_API bool cbor_value_is_half_float(const CborValue *value)
{ return value->type == CborHalfFloatType; }
CBOR_API CborError cbor_value_get_half_float(const CborValue *value, void *result);

CBOR_INLINE_API bool cbor_value_is_float(const CborValue *value)
{ return value->type == CborFloatType; }
CBOR_INLINE_API CborError cbor_value_get_float(const CborValue *value, float *result)
{
    uint32_t data;
    assert(cbor_value_is_float(value));
    assert(value->flags & CborIteratorFlag_IntegerValueTooLarge);
    data = (uint32_t)_cbor_value_decode_int64_internal(value);
    memcpy(result, &data, sizeof(*result));
    return CborNoError;
}

CBOR_INLINE_API bool cbor_value_is_double(const CborValue *value)
{ return value->type == CborDoubleType; }
CBOR_INLINE_API CborError cbor_value_get_double(const CborValue *value, double *result)
{
    uint64_t data;
    assert(cbor_value_is_double(value));
    assert(value->flags & CborIteratorFlag_IntegerValueTooLarge);
    data = _cbor_value_decode_int64_internal(value);
    memcpy(result, &data, sizeof(*result));
    return CborNoError;
}

/* 验证API*/

enum CborValidationFlags {
    /* 位映射：位0-7（8位）：规范格式位8-11（4位）：标准格式和严格模式位12-20（8位位）：严格模式位21-31（10位）：其他
     */

    CborValidateShortestIntegrals           = 0x0001,
    CborValidateShortestFloatingPoint       = 0x0002,
    CborValidateShortestNumbers             = CborValidateShortestIntegrals | CborValidateShortestFloatingPoint,
    CborValidateNoIndeterminateLength       = 0x0100,
    CborValidateMapIsSorted                 = 0x0200 | CborValidateNoIndeterminateLength,

    CborValidateCanonicalFormat             = 0x0fff,

    CborValidateMapKeysAreUnique            = 0x1000 | CborValidateMapIsSorted,
    CborValidateTagUse                      = 0x2000,
    CborValidateUtf8                        = 0x4000,

    CborValidateStrictMode                  = 0xfff00,

    CborValidateMapKeysAreString            = 0x100000,
    CborValidateNoUndefined                 = 0x200000,
    CborValidateNoTags                      = 0x400000,
    CborValidateFiniteFloatingPoint         = 0x800000,
    /* 未使用=0x1000000，*/
    /* 未使用=0x2000000，*/

    CborValidateNoUnknownSimpleTypesSA      = 0x4000000,
    CborValidateNoUnknownSimpleTypes        = 0x8000000 | CborValidateNoUnknownSimpleTypesSA,
    CborValidateNoUnknownTagsSA             = 0x10000000,
    CborValidateNoUnknownTagsSR             = 0x20000000 | CborValidateNoUnknownTagsSA,
    CborValidateNoUnknownTags               = 0x40000000 | CborValidateNoUnknownTagsSR,

    CborValidateCompleteData                = (int)0x80000000,

    CborValidateStrictest                   = (int)~0U,
    CborValidateBasic                       = 0
};

CBOR_API CborError cbor_value_validate(const CborValue *it, uint32_t flags);

/* 人类可读（转储）API*/

enum CborPrettyFlags {
    CborPrettyNumericEncodingIndicators     = 0x01,
    CborPrettyTextualEncodingIndicators     = 0,

    CborPrettyIndicateIndeterminateLength   = 0x02,
    CborPrettyIndicateIndetermineLength     = CborPrettyIndicateIndeterminateLength, /* 已弃用*/
    CborPrettyIndicateOverlongNumbers       = 0x04,

    CborPrettyShowStringFragments           = 0x100,
    CborPrettyMergeStringFragments          = 0,

    CborPrettyDefaultFlags          = CborPrettyIndicateIndeterminateLength
};

typedef CborError (*CborStreamFunction)(void *token, const char *fmt, ...)
#ifdef __GNUC__
    __attribute__((__format__(printf, 2, 3)))
#endif
;

CBOR_API CborError cbor_value_to_pretty_stream(CborStreamFunction streamFunction, void *token, CborValue *value, int flags);

/* 以下API需要托管C实现（使用FILE*）*/
#if !defined(__STDC_HOSTED__) || __STDC_HOSTED__-0 == 1
CBOR_API CborError cbor_value_to_pretty_advance_flags(FILE *out, CborValue *value, int flags);
CBOR_API CborError cbor_value_to_pretty_advance(FILE *out, CborValue *value);
CBOR_INLINE_API CborError cbor_value_to_pretty(FILE *out, const CborValue *value)
{
    CborValue copy = *value;
    return cbor_value_to_pretty_advance_flags(out, &copy, CborPrettyDefaultFlags);
}
#endif /* __STDC_HOSTED_检查*/

#ifdef __cplusplus
}
#endif

#endif /* CBOR_H */


