/**
 * \文件common.h
 *
 * \库中内部使用的简短实用程序宏
 */
/*
 *  版权所有The Mbed TLS Contributors SPDX许可证标识符：Apache-2.0
 *
 *  根据Apache许可证2.0版（“许可证”）获得许可；除非符合许可证，否则不得使用此文件。您可以在以下地址获取许可证副本：
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 *  除非适用法律要求或书面同意，否则根据许可证分发的软件是按“原样”分发的，无任何明示或暗示的担保或条件。有关许可证下权限和限制的具体语言，请参阅许可证。
 */

#ifndef MBEDTLS_LIBRARY_COMMON_H
#define MBEDTLS_LIBRARY_COMMON_H

#if defined(MBEDTLS_CONFIG_FILE)
#include MBEDTLS_CONFIG_FILE
#else
#include "mbedtls/config.h"
#endif

#include <stdint.h>

/** 帮助程序将函数定义为静态，除非在构建侵入性测试时。
 *
 * 如果函数仅在其自身的源文件中使用，并且应声明为“static”以允许编译器优化代码大小，但该函数具有单元测试，请使用“``MBEDTLS_static_TESTABLE int MBEDTLS_foo（…）｛…｝``”来定义它，并在“library/”目录的头中使用“``”（如果定义了（MBEDTL_TEST_HOOKS）int MBEDTLS _foo（.）来声明它#结束符```
 */
#if defined(MBEDTLS_TEST_HOOKS)
#define MBEDTLS_STATIC_TESTABLE
#else
#define MBEDTLS_STATIC_TESTABLE static
#endif

/** 字节读取宏
 *
 * 给定多字节整数\p x，MBEDTLS_byte_n从x中检索第n个字节，其中字节0是最低有效字节。
 */
#define MBEDTLS_BYTE_0( x ) ( (uint8_t) (   ( x )         & 0xff ) )
#define MBEDTLS_BYTE_1( x ) ( (uint8_t) ( ( ( x ) >> 8  ) & 0xff ) )
#define MBEDTLS_BYTE_2( x ) ( (uint8_t) ( ( ( x ) >> 16 ) & 0xff ) )
#define MBEDTLS_BYTE_3( x ) ( (uint8_t) ( ( ( x ) >> 24 ) & 0xff ) )
#define MBEDTLS_BYTE_4( x ) ( (uint8_t) ( ( ( x ) >> 32 ) & 0xff ) )
#define MBEDTLS_BYTE_5( x ) ( (uint8_t) ( ( ( x ) >> 40 ) & 0xff ) )
#define MBEDTLS_BYTE_6( x ) ( (uint8_t) ( ( ( x ) >> 48 ) & 0xff ) )
#define MBEDTLS_BYTE_7( x ) ( (uint8_t) ( ( ( x ) >> 56 ) & 0xff ) )

/**
 * 获取对应于四个字节的无符号32位整数，以大端序（MSB优先）。
 *
 * \param data要从中获取四个字节的内存的基本地址。\param offset从四个字节中的第一个和最高有效字节的基数偏移，以生成32位无符号整数。
 */
#ifndef MBEDTLS_GET_UINT32_BE
#define MBEDTLS_GET_UINT32_BE( data , offset )                  \
    (                                                           \
          ( (uint32_t) ( data )[( offset )    ] << 24 )         \
        | ( (uint32_t) ( data )[( offset ) + 1] << 16 )         \
        | ( (uint32_t) ( data )[( offset ) + 2] <<  8 )         \
        | ( (uint32_t) ( data )[( offset ) + 3]       )         \
    )
#endif

/**
 * 将一个32位无符号整数按大端顺序放入内存。
 *
 * \param n要放入内存的32位无符号整数。\param data存储32位无符号整数的内存的基本地址。\param offset从\p基位置偏移，在该位置放置32位无符号整数的最高有效字节。
 */
#ifndef MBEDTLS_PUT_UINT32_BE
#define MBEDTLS_PUT_UINT32_BE( n, data, offset )                \
{                                                               \
    ( data )[( offset )    ] = MBEDTLS_BYTE_3( n );             \
    ( data )[( offset ) + 1] = MBEDTLS_BYTE_2( n );             \
    ( data )[( offset ) + 2] = MBEDTLS_BYTE_1( n );             \
    ( data )[( offset ) + 3] = MBEDTLS_BYTE_0( n );             \
}
#endif

/**
 * 获取对应于四个字节的无符号32位整数，以小端序（LSB优先）。
 *
 * \param data要从中获取四个字节的内存的基本地址。\param offset从四个字节中的第一个和最低有效字节的基数偏移，以生成32位无符号整数。
 */
#ifndef MBEDTLS_GET_UINT32_LE
#define MBEDTLS_GET_UINT32_LE( data, offset )                   \
    (                                                           \
          ( (uint32_t) ( data )[( offset )    ]       )         \
        | ( (uint32_t) ( data )[( offset ) + 1] <<  8 )         \
        | ( (uint32_t) ( data )[( offset ) + 2] << 16 )         \
        | ( (uint32_t) ( data )[( offset ) + 3] << 24 )         \
    )
#endif

/**
 * 将一个32位无符号整数按小端序放入内存。
 *
 * \param n要放入内存的32位无符号整数。\param data存储32位无符号整数的内存的基本地址。\param offset从\p base偏移，在该位置放置32位无符号整数的最低有效字节。
 */
#ifndef MBEDTLS_PUT_UINT32_LE
#define MBEDTLS_PUT_UINT32_LE( n, data, offset )                \
{                                                               \
    ( data )[( offset )    ] = MBEDTLS_BYTE_0( n );             \
    ( data )[( offset ) + 1] = MBEDTLS_BYTE_1( n );             \
    ( data )[( offset ) + 2] = MBEDTLS_BYTE_2( n );             \
    ( data )[( offset ) + 3] = MBEDTLS_BYTE_3( n );             \
}
#endif

/**
 * 获取对应于两个字节的无符号16位整数，以小端序（LSB优先）。
 *
 * \param data要从中获取两个字节的内存的基本地址。\param offset从构建16位无符号整数的两个字节中第一个和最低有效字节的基数偏移。
 */
#ifndef MBEDTLS_GET_UINT16_LE
#define MBEDTLS_GET_UINT16_LE( data, offset )                   \
    (                                                           \
          ( (uint16_t) ( data )[( offset )    ]       )         \
        | ( (uint16_t) ( data )[( offset ) + 1] <<  8 )         \
    )
#endif

/**
 * 将一个16位无符号整数按小端序放入内存。
 *
 * \param n要放入内存的16位无符号整数。\param data存储16位无符号整数的内存的基本地址。\param offset从\p基址偏移，在此位置放置16位无符号整数的最低有效字节。
 */
#ifndef MBEDTLS_PUT_UINT16_LE
#define MBEDTLS_PUT_UINT16_LE( n, data, offset )                \
{                                                               \
    ( data )[( offset )    ] = MBEDTLS_BYTE_0( n );             \
    ( data )[( offset ) + 1] = MBEDTLS_BYTE_1( n );             \
}
#endif

/**
 * 获取对应于两个字节的无符号16位整数，以大端序（MSB优先）。
 *
 * \param data要从中获取两个字节的内存的基本地址。\param offset从两个字节中的第一个和最高有效字节的基数偏移，以生成16位无符号整数。
 */
#ifndef MBEDTLS_GET_UINT16_BE
#define MBEDTLS_GET_UINT16_BE( data, offset )                   \
    (                                                           \
          ( (uint16_t) ( data )[( offset )    ] << 8 )          \
        | ( (uint16_t) ( data )[( offset ) + 1]      )          \
    )
#endif

/**
 * 将一个16位无符号整数按大端顺序放入内存。
 *
 * \param n要放入内存的16位无符号整数。\param data存储16位无符号整数的内存的基本地址。\param offset从\p基址偏移，在此位置放置16位无符号整数的最高有效字节。
 */
#ifndef MBEDTLS_PUT_UINT16_BE
#define MBEDTLS_PUT_UINT16_BE( n, data, offset )                \
{                                                               \
    ( data )[( offset )    ] = MBEDTLS_BYTE_1( n );             \
    ( data )[( offset ) + 1] = MBEDTLS_BYTE_0( n );             \
}
#endif

/**
 * 获取对应于八个字节的无符号64位整数，顺序为大端（MSB优先）。
 *
 * \param data要从中获取八个字节的内存的基本地址。\param offset从8个字节中的第一个和最高有效字节的基数偏移，以生成64位无符号整数。
 */
#ifndef MBEDTLS_GET_UINT64_BE
#define MBEDTLS_GET_UINT64_BE( data, offset )                   \
    (                                                           \
          ( (uint64_t) ( data )[( offset )    ] << 56 )         \
        | ( (uint64_t) ( data )[( offset ) + 1] << 48 )         \
        | ( (uint64_t) ( data )[( offset ) + 2] << 40 )         \
        | ( (uint64_t) ( data )[( offset ) + 3] << 32 )         \
        | ( (uint64_t) ( data )[( offset ) + 4] << 24 )         \
        | ( (uint64_t) ( data )[( offset ) + 5] << 16 )         \
        | ( (uint64_t) ( data )[( offset ) + 6] <<  8 )         \
        | ( (uint64_t) ( data )[( offset ) + 7]       )         \
    )
#endif

/**
 * 将一个64位无符号整数按大端顺序放入内存。
 *
 * \param n要放入内存的64位无符号整数。\param data存储64位无符号整数的内存的基本地址。\param offset从\p base偏移，在该位置放置64位无符号整数的最高有效字节。
 */
#ifndef MBEDTLS_PUT_UINT64_BE
#define MBEDTLS_PUT_UINT64_BE( n, data, offset )                \
{                                                               \
    ( data )[( offset )    ] = MBEDTLS_BYTE_7( n );             \
    ( data )[( offset ) + 1] = MBEDTLS_BYTE_6( n );             \
    ( data )[( offset ) + 2] = MBEDTLS_BYTE_5( n );             \
    ( data )[( offset ) + 3] = MBEDTLS_BYTE_4( n );             \
    ( data )[( offset ) + 4] = MBEDTLS_BYTE_3( n );             \
    ( data )[( offset ) + 5] = MBEDTLS_BYTE_2( n );             \
    ( data )[( offset ) + 6] = MBEDTLS_BYTE_1( n );             \
    ( data )[( offset ) + 7] = MBEDTLS_BYTE_0( n );             \
}
#endif

/**
 * 获取对应于八个字节的无符号64位整数，以小端序（LSB优先）。
 *
 * \param data要从中获取八个字节的内存的基本地址。\param offset从8个字节中的第一个和最低有效字节的基数偏移，以生成64位无符号整数。
 */
#ifndef MBEDTLS_GET_UINT64_LE
#define MBEDTLS_GET_UINT64_LE( data, offset )                   \
    (                                                           \
          ( (uint64_t) ( data )[( offset ) + 7] << 56 )         \
        | ( (uint64_t) ( data )[( offset ) + 6] << 48 )         \
        | ( (uint64_t) ( data )[( offset ) + 5] << 40 )         \
        | ( (uint64_t) ( data )[( offset ) + 4] << 32 )         \
        | ( (uint64_t) ( data )[( offset ) + 3] << 24 )         \
        | ( (uint64_t) ( data )[( offset ) + 2] << 16 )         \
        | ( (uint64_t) ( data )[( offset ) + 1] <<  8 )         \
        | ( (uint64_t) ( data )[( offset )    ]       )         \
    )
#endif

/**
 * 将一个64位无符号整数按小端序放入内存。
 *
 * \param n要放入内存的64位无符号整数。\param data存储64位无符号整数的内存的基本地址。\param offset从\p base偏移，在该位置放置64位无符号整数的最低有效字节。
 */
#ifndef MBEDTLS_PUT_UINT64_LE
#define MBEDTLS_PUT_UINT64_LE( n, data, offset )                \
{                                                               \
    ( data )[( offset )    ] = MBEDTLS_BYTE_0( n );             \
    ( data )[( offset ) + 1] = MBEDTLS_BYTE_1( n );             \
    ( data )[( offset ) + 2] = MBEDTLS_BYTE_2( n );             \
    ( data )[( offset ) + 3] = MBEDTLS_BYTE_3( n );             \
    ( data )[( offset ) + 4] = MBEDTLS_BYTE_4( n );             \
    ( data )[( offset ) + 5] = MBEDTLS_BYTE_5( n );             \
    ( data )[( offset ) + 6] = MBEDTLS_BYTE_6( n );             \
    ( data )[( offset ) + 7] = MBEDTLS_BYTE_7( n );             \
}
#endif

#endif /* MBEDTLS_LIBRARY_COMMON_H */

