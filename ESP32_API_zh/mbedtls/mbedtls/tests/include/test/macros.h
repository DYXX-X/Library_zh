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

/**
 * \brief此宏测试作为测试步骤或测试用例中的单个测试传递给它的表达式。
 *
 *          它允许库函数返回值并返回可测试的错误代码。
 *
 *          当启用MBEDTLS_CHECK_PARAMS时，对参数失败回调MBEDTLS_PARAM_FAILED（）的调用将被认为是测试失败。
 *
 *          此宏不适用于负参数验证测试，因为它假设测试步骤不会产生错误。
 *
 *          测试失败意味着：
 *          -将此测试用例标记为失败。
 *          -打印识别故障的消息。
 *          -跳转到\c退出标签。
 *
 *          此宏扩展为指令，而不是表达式。它可能会跳转到\c退出标签。
 *
 * \param TEST要测试的测试表达式。
 */
#define TEST_ASSERT( TEST )                                 \
    do {                                                    \
       if( ! (TEST) )                                       \
       {                                                    \
          mbedtls_test_fail( #TEST, __LINE__, __FILE__ );   \
          goto exit;                                        \
       }                                                    \
    } while( 0 )

/** 对两个整数表达式求值，如果它们的值不同，则测试用例失败。
 *
 * 这两个表达式应该具有相同的正负号，否则如果正负号值为负，则比较就没有意义。
 *
 * \param expr1要计算的整型表达式。\param expr2要计算的另一个整型表达式。
 */
#define TEST_EQUAL( expr1, expr2 )                                      \
    do {                                                                \
        if( ! mbedtls_test_equal( #expr1 " == " #expr2, __LINE__, __FILE__, \
                                  expr1, expr2 ) )                      \
            goto exit;                                                  \
    } while( 0 )

/** 动态分配内存，如果失败，则使测试用例失败。分配的内存将用零填充。
 *
 * 在调用此宏之前，必须将\p指针设置为\c NULL，并将`mbedtls_free（pointer）`放入测试的清理代码中。
 *
 * 如果\p长度为零，则生成的\p指针将为\c NULL。这通常是我们在测试中想要的，因为当缓冲区大小为零时，API函数应该接受空指针。
 *
 * 此宏扩展为指令，而不是表达式。它可能会跳转到\c退出标签。
 *
 * \param pointer将存储已分配缓冲区地址的左值。此表达式可以计算多次。\param length要分配的元素数。此表达式可以计算多次。
 *
 */
#define ASSERT_ALLOC( pointer, length )                           \
    do                                                            \
    {                                                             \
        TEST_ASSERT( ( pointer ) == NULL );                       \
        if( ( length ) != 0 )                                     \
        {                                                         \
            ( pointer ) = mbedtls_calloc( sizeof( *( pointer ) ), \
                                          ( length ) );           \
            TEST_ASSERT( ( pointer ) != NULL );                   \
        }                                                         \
    }                                                             \
    while( 0 )

/** 动态分配内存。如果分配失败，则跳过测试用例。
 *
 * 此宏的行为类似于#ASSERT_ALLOC，只是如果分配失败，它会将测试标记为跳过而不是失败。
 */
#define ASSERT_ALLOC_WEAK( pointer, length )                      \
    do                                                            \
    {                                                             \
        TEST_ASSERT( ( pointer ) == NULL );                       \
        if( ( length ) != 0 )                                     \
        {                                                         \
            ( pointer ) = mbedtls_calloc( sizeof( *( pointer ) ), \
                                          ( length ) );           \
            TEST_ASSUME( ( pointer ) != NULL );                   \
        }                                                         \
    }                                                             \
    while( 0 )

/** 比较两个缓冲区，如果它们不同，则测试用例失败。
 *
 * 此宏扩展为指令，而不是表达式。它可能会跳转到\c退出标签。
 *
 * \param p1指向第一个缓冲区开始的指针。\param size1第一个缓冲区的大小（字节）。此表达式可以计算多次。\param p2指向第二个缓冲区开始的指针。\param size2第二个缓冲区的大小（字节）。此表达式可以计算多次。
 */
#define ASSERT_COMPARE( p1, size1, p2, size2 )                          \
    do                                                                  \
    {                                                                   \
        TEST_ASSERT( ( size1 ) == ( size2 ) );                          \
        if( ( size1 ) != 0 )                                            \
            TEST_ASSERT( memcmp( ( p1 ), ( p2 ), ( size1 ) ) == 0 );    \
    }                                                                   \
    while( 0 )

/**
 * \brief此宏测试传递给它的表达式，如果它的计算结果不为“true”，则跳过正在运行的测试。
 *
 * \param TEST要测试的测试表达式。
 */
#define TEST_ASSUME( TEST )                                 \
    do {                                                    \
        if( ! (TEST) )                                      \
        {                                                   \
            mbedtls_test_skip( #TEST, __LINE__, __FILE__ ); \
            goto exit;                                      \
        }                                                   \
    } while( 0 )

#if defined(MBEDTLS_CHECK_PARAMS) && !defined(MBEDTLS_PARAM_FAILED_ALT)
/**
 * \brief此宏测试作为测试步骤或测试用例中的单个测试传递给它的语句。宏假设测试将失败并将生成错误。
 *
 *          它允许库函数返回一个值，并在返回时测试返回代码以确认返回了给定的错误代码。
 *
 *          当启用MBEDTLS_CHECK_PARAMS时，假设对参数失败回调MBEDTLS_PARAM_FAILED（）的调用表示预期失败，测试将通过。
 *
 *          此宏用于负参数验证测试，其中失败的函数可能返回错误值或调用MBEDTLS_PARAM_FAILED（）来指示错误。
 *
 * \param param_ERROR_VALUE预期的错误代码。
 *
 * \param TEST要测试的测试表达式。
 */
#define TEST_INVALID_PARAM_RET( PARAM_ERR_VALUE, TEST )                 \
    do {                                                                \
        mbedtls_test_param_failed_expect_call( );                       \
        if( ( ( TEST ) != ( PARAM_ERR_VALUE ) ) ||                      \
            ( mbedtls_test_param_failed_check_expected_call( ) != 0 ) ) \
        {                                                               \
            mbedtls_test_fail( #TEST, __LINE__, __FILE__ );             \
            goto exit;                                                  \
        }                                                               \
        mbedtls_test_param_failed_check_expected_call( );               \
   } while( 0 )

/**
 * \brief此宏测试作为测试步骤或测试用例中的单个测试传递给它的语句。宏假设测试将失败并将生成错误。
 *
 *          它假定被测试的库函数不能返回值，并且假定只能通过调用MBEDTLS_PARAM_FAILED（）来指示错误。
 *
 *          当启用MBEDTLS_CHECK_PARAMS时，假设对参数失败回调MBEDTLS_PARAM_FAILED（）的调用表示预期的失败。如果未启用MBEDTLS_CHECK_PARAMS，则无法进行测试。
 *
 *          此宏用于负参数验证测试，其中失败的函数只能通过调用MBEDTLS_PARAM_FAILED（）指示错误来返回错误。
 *
 * \param TEST要测试的测试表达式。
 */
#define TEST_INVALID_PARAM( TEST )                                       \
    do {                                                                 \
        memcpy( jmp_tmp, mbedtls_test_param_failed_get_state_buf( ),     \
                sizeof( jmp_tmp ) );                                     \
        if( setjmp(  mbedtls_test_param_failed_get_state_buf( ) ) == 0 ) \
        {                                                                \
            TEST;                                                        \
            mbedtls_test_fail( #TEST, __LINE__, __FILE__ );              \
            goto exit;                                                   \
        }                                                                \
        mbedtls_test_param_failed_reset_state( );                        \
    } while( 0 )
#endif /* MBEDTLS_CHECK_PARAMS && !MBEDTLS_PARAM_FAILED_ALT */

/**
 * \brief此宏测试作为测试步骤或测试用例中的单个测试传递给它的语句。宏假设测试不会失败。
 *
 *          它假定被测试的库函数不能返回值，并且假定只能通过调用MBEDTLS_PARAM_FAILED（）来指示错误。
 *
 *          当启用MBEDTLS_CHECK_PARAMS时，假设对参数失败回调MBEDTLS_PARAM_FAILED（）的调用表示预期的失败。如果未启用MBEDTLS_CHECK_PARAMS，则无法进行测试。
 *
 *          此宏旨在测试返回void的函数是否接受它们应该接受的所有参数值，例如，当允许为NULL的参数恰好为NULL时，它们不会调用MBEDTLS_PARAM_FAILED（）。
 *
 *          注意：对于返回除void以外的其他值的函数，最好使用TEST_ASSERT（）并检查返回值来检查它们是否接受所有应该接受的参数。
 *
 *          注意：即使禁用了#MBEDTLS_CHECK_PARAMS，此宏也可用，因为即使禁用了此选项，检查函数是否接受所有合法值也是有意义的-只有在这种情况下，测试更多的是函数segfault是否存在，而不是它是否调用MBEDTLS_PARAM_FAILED（）。
 *
 * \param TEST要测试的测试表达式。
 */
#define TEST_VALID_PARAM( TEST )                                    \
    TEST_ASSERT( ( TEST, 1 ) );

#define TEST_HELPER_ASSERT(a) if( !( a ) )                          \
{                                                                   \
    mbedtls_fprintf( stderr, "Assertion Failed at %s:%d - %s\n",    \
                             __FILE__, __LINE__, #a );              \
    mbedtls_exit( 1 );                                              \
}

/** \def ARRAY_LENGTH返回静态数组或堆栈数组的元素数。
 *
 * \param array数组（非指针）类型的值。
 *
 * \return数组的元素数。
 */
/* ARRAY_LENGTH的正确实现，但如果使用指针而不是数组调用，则会无声地给出无意义的结果。*/
#define ARRAY_LENGTH_UNSAFE( array )            \
    ( sizeof( array ) / sizeof( *( array ) ) )

#if defined(__GNUC__)
/* 测试arg和&（arg）[0]是否具有相同的类型。如果arg是一个数组，则这是正确的，但如果它是一个指针，则不是。*/
#define IS_ARRAY_NOT_POINTER( arg )                                     \
    ( ! __builtin_types_compatible_p( __typeof__( arg ),                \
                                      __typeof__( &( arg )[0] ) ) )
/* 值为0的编译时常数。如果“const_expr”不是具有非零值的编译时常量，则导致编译时错误。*/
#define STATIC_ASSERT_EXPR( const_expr )                                \
    ( 0 && sizeof( struct { unsigned int STATIC_ASSERT : 1 - 2 * ! ( const_expr ); } ) )

/* 返回标量值“value”（可能已升级）。如果“value”是，则这是一个编译时常数。“condition”必须是编译时常量。如果“condition”为false，请安排导致编译时错误。*/
#define STATIC_ASSERT_THEN_RETURN( condition, value )   \
    ( STATIC_ASSERT_EXPR( condition ) ? 0 : ( value ) )

#define ARRAY_LENGTH( array )                                           \
    ( STATIC_ASSERT_THEN_RETURN( IS_ARRAY_NOT_POINTER( array ),         \
                                 ARRAY_LENGTH_UNSAFE( array ) ) )

#else
/* 如果我们不确定编译器是否支持我们的非标准技巧，请回到不安全的实现。*/
#define ARRAY_LENGTH( array ) ARRAY_LENGTH_UNSAFE( array )
#endif

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

