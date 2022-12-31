/**
 * \文件宏.h
 *
 * \brief此文件包含用于测试的通用宏。
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

#ifndef TEST_MACROS_H
#define TEST_MACROS_H

#if !defined(MBEDTLS_CONFIG_FILE)
#include "mbedtls/config.h"
#else
#include MBEDTLS_CONFIG_FILE
#endif

#include <stdlib.h>

#if defined(MBEDTLS_PLATFORM_C)
#include "mbedtls/platform.h"
#else
#include <stdio.h>
#define mbedtls_fprintf    fprintf
#define mbedtls_snprintf   snprintf
#define mbedtls_calloc     calloc
#define mbedtls_free       free
#define mbedtls_exit       exit
#define mbedtls_time       time
#define mbedtls_time_t     time_t
#define MBEDTLS_EXIT_SUCCESS EXIT_SUCCESS
#define MBEDTLS_EXIT_FAILURE EXIT_FAILURE
#endif

#if defined(MBEDTLS_MEMORY_BUFFER_ALLOC_C)
#include "mbedtls/memory_buffer_alloc.h"
#endif

#define TEST_HELPER_ASSERT(a) if( !( a ) )                          \
{                                                                   \
    mbedtls_fprintf( stderr, "Assertion Failed at %s:%d - %s\n",    \
                             __FILE__, __LINE__, #a );              \
    mbedtls_exit( 1 );                                              \
}

#if defined(__GNUC__)
/* 测试arg和&（arg）[0]是否具有相同的类型。如果arg是一个数组，则这是正确的，但如果它是一个指针，则不是。*/
#define IS_ARRAY_NOT_POINTER( arg )                                     \
    ( ! __builtin_types_compatible_p( __typeof__( arg ),                \
                                      __typeof__( &( arg )[0] ) ) )
#else
/* 在我们不知道如何实现此检查的平台上，忽略它。哦，不随身携带的支票总比什么都没有好。*/
#define IS_ARRAY_NOT_POINTER( arg ) 1
#endif

/* 值为0的编译时常数。如果“const_expr”不是具有非零值的编译时常量，则导致编译时错误。*/
#define STATIC_ASSERT_EXPR( const_expr )                                \
    ( 0 && sizeof( struct { unsigned int STATIC_ASSERT : 1 - 2 * ! ( const_expr ); } ) )
/* 返回标量值“value”（可能已升级）。如果“value”是，则这是一个编译时常数。“condition”必须是编译时常量。如果“condition”为false，请安排导致编译时错误。*/
#define STATIC_ASSERT_THEN_RETURN( condition, value )   \
    ( STATIC_ASSERT_EXPR( condition ) ? 0 : ( value ) )

#define ARRAY_LENGTH_UNSAFE( array )            \
    ( sizeof( array ) / sizeof( *( array ) ) )
/** 返回静态数组或堆栈数组的元素数。
 *
 * \param array数组（非指针）类型的值。
 *
 * \return数组的元素数。
 */
#define ARRAY_LENGTH( array )                                           \
    ( STATIC_ASSERT_THEN_RETURN( IS_ARRAY_NOT_POINTER( array ),         \
                                 ARRAY_LENGTH_UNSAFE( array ) ) )

/** 返回两个值中的较小值。
 *
 * \param x没有副作用的整数值表达式。\param y没有副作用的整数值表达式。
 *
 * \return \p x和\p y中的较小值。
 */
#define MIN( x, y ) ( ( x ) < ( y ) ? ( x ) : ( y ) )

/** 返回两个值中的较大值。
 *
 * \param x没有副作用的整数值表达式。\param y没有副作用的整数值表达式。
 *
 * \return \p x和\p y中的较大值。
 */
#define MAX( x, y ) ( ( x ) > ( y ) ? ( x ) : ( y ) )

/*
 * 32位整数操作宏（大端）
 */
#ifndef GET_UINT32_BE
#define GET_UINT32_BE(n,b,i)                            \
{                                                       \
    (n) = ( (uint32_t) (b)[(i)    ] << 24 )             \
        | ( (uint32_t) (b)[(i) + 1] << 16 )             \
        | ( (uint32_t) (b)[(i) + 2] <<  8 )             \
        | ( (uint32_t) (b)[(i) + 3]       );            \
}
#endif

#ifndef PUT_UINT32_BE
#define PUT_UINT32_BE(n,b,i)                            \
{                                                       \
    (b)[(i)    ] = (unsigned char) ( (n) >> 24 );       \
    (b)[(i) + 1] = (unsigned char) ( (n) >> 16 );       \
    (b)[(i) + 2] = (unsigned char) ( (n) >>  8 );       \
    (b)[(i) + 3] = (unsigned char) ( (n)       );       \
}
#endif

#endif /* TEST_MACROS_H */

