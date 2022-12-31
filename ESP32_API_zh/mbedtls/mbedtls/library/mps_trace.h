/*
 *  版权所有The Mbed TLS Contributors SPDX许可证标识符：Apache-2.0
 *
 *  根据Apache许可证2.0版（“许可证”）获得许可；除非符合许可证，否则不得使用此文件。您可以在以下地址获取许可证副本：
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 *  除非适用法律要求或书面同意，否则根据许可证分发的软件是按“原样”分发的，无任何明示或暗示的担保或条件。有关许可证下权限和限制的具体语言，请参阅许可证。
 *
 *  此文件是mbed TLS的一部分(https://tls.mbed.org)
 */

/**
 * \文件mps_trace.h
 *
 * \MPS简要跟踪模块
 */

#ifndef MBEDTLS_MPS_MBEDTLS_MPS_TRACE_H
#define MBEDTLS_MPS_MBEDTLS_MPS_TRACE_H

#include "common.h"
#include "mps_common.h"
#include "mps_trace.h"

#if defined(MBEDTLS_PLATFORM_C)
#include "mbedtls/platform.h"
#else
#include <stdio.h>
#define mbedtls_printf    printf
#define mbedtls_vsnprintf vsnprintf
#endif /* MBEDTLS_PLATFORM_C */

#if defined(MBEDTLS_MPS_ENABLE_TRACE)

/*
 * 对此进行调整，以启用/禁用MPS各层的跟踪输出。
 */

#define MBEDTLS_MPS_TRACE_ENABLE_LAYER_1
#define MBEDTLS_MPS_TRACE_ENABLE_LAYER_2
#define MBEDTLS_MPS_TRACE_ENABLE_LAYER_3
#define MBEDTLS_MPS_TRACE_ENABLE_LAYER_4
#define MBEDTLS_MPS_TRACE_ENABLE_READER
#define MBEDTLS_MPS_TRACE_ENABLE_WRITER

/*
 * 要使用现有的跟踪模块，只需更改上面的MBEDTLS_MPS_trace_ENABLE_XXX，但不要修改此文件的其余部分。
 */

typedef enum
{
    MBEDTLS_MPS_TRACE_TYPE_COMMENT,
    MBEDTLS_MPS_TRACE_TYPE_CALL,
    MBEDTLS_MPS_TRACE_TYPE_ERROR,
    MBEDTLS_MPS_TRACE_TYPE_RETURN
} mbedtls_mps_trace_type;

#define MBEDTLS_MPS_TRACE_BIT_LAYER_1 1
#define MBEDTLS_MPS_TRACE_BIT_LAYER_2 2
#define MBEDTLS_MPS_TRACE_BIT_LAYER_3 3
#define MBEDTLS_MPS_TRACE_BIT_LAYER_4 4
#define MBEDTLS_MPS_TRACE_BIT_WRITER  5
#define MBEDTLS_MPS_TRACE_BIT_READER  6

#if defined(MBEDTLS_MPS_TRACE_ENABLE_LAYER_1)
#define MBEDTLS_MPS_TRACE_MASK_LAYER_1 (1u << MBEDTLS_MPS_TRACE_BIT_LAYER_1 )
#else
#define MBEDTLS_MPS_TRACE_MASK_LAYER_1 0
#endif

#if defined(MBEDTLS_MPS_TRACE_ENABLE_LAYER_2)
#define MBEDTLS_MPS_TRACE_MASK_LAYER_2 (1u << MBEDTLS_MPS_TRACE_BIT_LAYER_2 )
#else
#define MBEDTLS_MPS_TRACE_MASK_LAYER_2 0
#endif

#if defined(MBEDTLS_MPS_TRACE_ENABLE_LAYER_3)
#define MBEDTLS_MPS_TRACE_MASK_LAYER_3 (1u << MBEDTLS_MPS_TRACE_BIT_LAYER_3 )
#else
#define MBEDTLS_MPS_TRACE_MASK_LAYER_3 0
#endif

#if defined(MBEDTLS_MPS_TRACE_ENABLE_LAYER_4)
#define MBEDTLS_MPS_TRACE_MASK_LAYER_4 (1u << MBEDTLS_MPS_TRACE_BIT_LAYER_4 )
#else
#define MBEDTLS_MPS_TRACE_MASK_LAYER_4 0
#endif

#if defined(MBEDTLS_MPS_TRACE_ENABLE_READER)
#define MBEDTLS_MPS_TRACE_MASK_READER (1u << MBEDTLS_MPS_TRACE_BIT_READER )
#else
#define MBEDTLS_MPS_TRACE_MASK_READER 0
#endif

#if defined(MBEDTLS_MPS_TRACE_ENABLE_WRITER)
#define MBEDTLS_MPS_TRACE_MASK_WRITER (1u << MBEDTLS_MPS_TRACE_BIT_WRITER )
#else
#define MBEDTLS_MPS_TRACE_MASK_WRITER 0
#endif

#define MBEDTLS_MPS_TRACE_MASK ( MBEDTLS_MPS_TRACE_MASK_LAYER_1 |       \
                                 MBEDTLS_MPS_TRACE_MASK_LAYER_2 |       \
                                 MBEDTLS_MPS_TRACE_MASK_LAYER_3 |       \
                                 MBEDTLS_MPS_TRACE_MASK_LAYER_4 |       \
                                 MBEDTLS_MPS_TRACE_MASK_READER  |       \
                                 MBEDTLS_MPS_TRACE_MASK_WRITER )

/* 我们必须避免全局变量，因为E-ACSL会阻塞它们……将所有内容都封装在存根函数中。*/
int  mbedtls_mps_trace_get_depth( void );
void mbedtls_mps_trace_inc_depth( void );
void mbedtls_mps_trace_dec_depth( void );

void mbedtls_mps_trace_color( int id );
void mbedtls_mps_trace_indent( int level, mbedtls_mps_trace_type ty );

void mbedtls_mps_trace_print_msg( int id, int line, const char *format, ... );

#define MBEDTLS_MPS_TRACE( type, ... )                                              \
    do {                                                                            \
        if( ! ( MBEDTLS_MPS_TRACE_MASK & ( 1u << mbedtls_mps_trace_id ) ) )         \
            break;                                                                  \
        mbedtls_mps_trace_indent( mbedtls_mps_trace_get_depth(), type );            \
        mbedtls_mps_trace_color( mbedtls_mps_trace_id );                            \
        mbedtls_mps_trace_print_msg( mbedtls_mps_trace_id, __LINE__, __VA_ARGS__ ); \
        mbedtls_mps_trace_color( 0 );                                               \
    } while( 0 )

#define MBEDTLS_MPS_TRACE_INIT( ... )                                         \
    do {                                                                      \
        if( ! ( MBEDTLS_MPS_TRACE_MASK & ( 1u << mbedtls_mps_trace_id ) ) )   \
            break;                                                            \
        MBEDTLS_MPS_TRACE( MBEDTLS_MPS_TRACE_TYPE_CALL, __VA_ARGS__ );        \
        mbedtls_mps_trace_inc_depth();                                        \
    } while( 0 )

#define MBEDTLS_MPS_TRACE_END( val )                                        \
    do {                                                                    \
        if( ! ( MBEDTLS_MPS_TRACE_MASK & ( 1u << mbedtls_mps_trace_id ) ) ) \
            break;                                                          \
        MBEDTLS_MPS_TRACE( MBEDTLS_MPS_TRACE_TYPE_RETURN, "%d (-%#04x)",    \
               (int) (val), -((unsigned)(val)) );                           \
        mbedtls_mps_trace_dec_depth();                                      \
    } while( 0 )

#define MBEDTLS_MPS_TRACE_RETURN( val )         \
    do {                                        \
        /* 中断尾部递归。*/            \
        int ret__ = val;                        \
        MBEDTLS_MPS_TRACE_END( ret__ );         \
        return( ret__ );                        \
    } while( 0 )

#else /* MBEDTLS_MPS_TRACE */

#define MBEDTLS_MPS_TRACE( type, ... ) do { } while( 0 )
#define MBEDTLS_MPS_TRACE_INIT( ... )  do { } while( 0 )
#define MBEDTLS_MPS_TRACE_END          do { } while( 0 )

#define MBEDTLS_MPS_TRACE_RETURN( val ) return( val );

#endif /* MBEDTLS_MPS_TRACE */

#endif /* MBEDTLS_MPS_MBEDTLS_MPS_TRACE_H */

