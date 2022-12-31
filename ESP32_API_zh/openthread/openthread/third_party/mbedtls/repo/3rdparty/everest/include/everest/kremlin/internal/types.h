/* 版权所有（c）INRIA和Microsoft Corporation。保留所有权利。根据Apache 2.0许可证许可。*/

#ifndef KRML_TYPES_H
#define KRML_TYPES_H

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

/* 类型要么是抽象的，意味着必须在C中实现，要么是模型，意味着它们在编译时被替换为手写的C类型（在这种情况下，它们被标记为noextract）。*/

typedef uint64_t FStar_UInt64_t, FStar_UInt64_t_;
typedef int64_t FStar_Int64_t, FStar_Int64_t_;
typedef uint32_t FStar_UInt32_t, FStar_UInt32_t_;
typedef int32_t FStar_Int32_t, FStar_Int32_t_;
typedef uint16_t FStar_UInt16_t, FStar_UInt16_t_;
typedef int16_t FStar_Int16_t, FStar_Int16_t_;
typedef uint8_t FStar_UInt8_t, FStar_UInt8_t_;
typedef int8_t FStar_Int8_t, FStar_Int8_t_;

/* 仅在构建Kremlib时有用，因为它位于FStar.Int.Cast的依赖关系图中。*/
typedef uint64_t FStar_UInt63_t, FStar_UInt63_t_;
typedef int64_t FStar_Int63_t, FStar_Int63_t_;

typedef double FStar_Float_float;
typedef uint32_t FStar_Char_char;
typedef FILE *FStar_IO_fd_read, *FStar_IO_fd_write;

typedef void *FStar_Dyn_dyn;

typedef const char *C_String_t, *C_String_t_;

typedef int exit_code;
typedef FILE *channel;

typedef unsigned long long TestLib_cycles;

typedef uint64_t FStar_Date_dateTime, FStar_Date_timeSpan;

/* uint128类型是一种特殊情况，因为我们提供了它的几种实现，这取决于编译器以及用户是否想要验证的实现。*/
#if !defined(KRML_VERIFIED_UINT128) && defined(_MSC_VER) && defined(_M_X64)
#  include <emmintrin.h>
typedef __m128i FStar_UInt128_uint128;
#elif !defined(KRML_VERIFIED_UINT128) && !defined(_MSC_VER)
typedef unsigned __int128 FStar_UInt128_uint128;
#else
typedef struct FStar_UInt128_uint128_s {
  uint64_t low;
  uint64_t high;
} FStar_UInt128_uint128;
#endif

typedef FStar_UInt128_uint128 FStar_UInt128_t, FStar_UInt128_t_, uint128_t;

#endif

