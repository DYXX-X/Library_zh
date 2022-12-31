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
 * \文件mps_common.h
 *
 * \MPS使用的常用函数和宏
 */

#ifndef MBEDTLS_MPS_COMMON_H
#define MBEDTLS_MPS_COMMON_H

#include "mps_error.h"

#include <stdio.h>

/**
 * \name SECTION:MPS配置
 *
 * \{
 */

/*! 该标志控制MPS内部组件（读取器、写入器、1-3层）是否在API调用入口处执行预期抽象状态的验证。
 *
 *  上下文：所有MPS API函数都对其运行的上下文施加假设/前提条件。例如，每个结构都有一个状态完整性的概念，该概念由“xxx_init（）”建立，并由对MPS API的任何调用保存，这些调用满足其前提条件，或者成功，或者失败，错误代码被明确记录为不会破坏结构完整性（如WANT_READ和WANT_WRITE）；除了“xxx_init（）”之外，任何函数都将状态完整性作为前提条件（但通常更多）。如果违反了任何前提条件，则函数的行为完全未定义。除了状态完整性之外，所有MPS结构都有一个更精细的抽象状态概念，API对其进行操作。例如，所有层都有一种“abtract read state”概念，表示传入数据是否已传递给用户，例如通过第2层的MPS_l2_read_start（）或第3层的MPS_l3_read（），在传入数据被显式“消耗”之前，再次调用这些读取函数是没有意义的，例如，通过第2层的mps_l2_read_consume（）或第3层的mps_l3_read_consum（）。然而，即使这没有意义，API是否应该在这种无意义的调用中优雅地失败也是一个设计选择，这就是这个选项的意义所在：
 *
 *  该选项确定预期的抽象状态是否是API前提条件的一部分：如果设置了该选项，则抽象状态不是前提条件的组成部分，因此需要由实现进行验证。如果遇到意外的抽象状态，则实现必须正常失败，出现错误#MBEDTLS_error_MPS_OPERATION_unexpected。相反，如果未设置此选项，则预期的抽象状态将包含在相应API调用的前提条件中，如果抽象状态不符合预期，则实现的行为未定义。
 *
 *  例如：如果当前没有打开的传入记录，则启用此选项会导致mps_l2_read_done（）失败；在这种情况下，禁用此功能将导致未定义的行为。
 *
 *  对此进行注释以删除状态验证。
 */
#define MBEDTLS_MPS_STATE_VALIDATION

/*! 此标志启用/禁用MPS内部状态的断言。
 *
 *  断言是当MPS在其API和前提条件的范围内使用时不应触发的健全性检查。
 *
 *  启用此功能可以通过限制潜在错误的范围来提高安全性，但代价是增加代码大小。
 *
 *  注意：到目前为止，对于哪些预期条件值得断言，哪些不值得断言，还没有指导原则。
 *
 *  对此进行注释以禁用断言。
 */
#define MBEDTLS_MPS_ENABLE_ASSERTIONS

/*! 此标志控制是否应启用MPS跟踪。*/
//#定义MBEDTLS_MPS_ENABLE_TRACE

#if defined(MBEDTLS_MPS_STATE_VALIDATION)

#define MBEDTLS_MPS_STATE_VALIDATE_RAW( cond, string )                         \
    do                                                                         \
    {                                                                          \
        if( !(cond) )                                                          \
        {                                                                      \
            MBEDTLS_MPS_TRACE( MBEDTLS_MPS_TRACE_TYPE_ERROR, string );         \
            MBEDTLS_MPS_TRACE_RETURN( MBEDTLS_ERR_MPS_OPERATION_UNEXPECTED );  \
        }                                                                      \
    } while( 0 )

#else /* MBEDTLS_MPS_STATE_VALIDATION */

#define MBEDTLS_MPS_STATE_VALIDATE_RAW( cond, string )           \
    do                                                           \
    {                                                            \
        ( cond );                                                \
    } while( 0 )

#endif /* MBEDTLS_MPS_STATE_VALIDATION */

#if defined(MBEDTLS_MPS_ENABLE_ASSERTIONS)

#define MBEDTLS_MPS_ASSERT_RAW( cond, string )                          \
    do                                                                  \
    {                                                                   \
        if( !(cond) )                                                   \
        {                                                               \
            MBEDTLS_MPS_TRACE( MBEDTLS_MPS_TRACE_TYPE_ERROR, string );  \
            MBEDTLS_MPS_TRACE_RETURN( MBEDTLS_ERR_MPS_INTERNAL_ERROR ); \
        }                                                               \
    } while( 0 )

#else /* MBEDTLS_MPS_ENABLE_ASSERTIONS */

#define MBEDTLS_MPS_ASSERT_RAW( cond, string ) do {} while( 0 )

#endif /* MBEDTLS_MPS_ENABLE_ASSERTIONS */


/* \}name SECTION:MPS配置*/

/**
 * \name SECTION：通用类型
 *
 * MPS中使用的各种常见类型\{
 */

/** \brief MPS结构中使用的缓冲区大小和偏移量的类型。
 *
 *           这是一个无符号整数类型，应该足够大，可以容纳MPS处理的任何缓冲区或消息的长度。
 *
 *           这里选择尽可能小的值的原因是为了减小MPS结构的大小。
 *
 * \警告：在此处使用比：：mbedtls_mps_size_t更窄的类型时必须小心，因为在转换过程中可能会发生截断。
 *
 * \TLS中的警告握手消息大小可能高达2^24~16Mb。如果mbedtls_mps_[opt_]stored_size_t小于该值，则相应地限制最大握手消息。
 *
 * 目前，我们始终使用默认类型size_t，还不支持对：：mbedtls_mps_size_t和：：mbedtls_mps_stored_size_t使用更小的类型或不同的类型。
 *
 */
typedef size_t mbedtls_mps_stored_size_t;
#define MBEDTLS_MPS_STORED_SIZE_MAX  ( (mbedtls_mps_stored_size_t) -1 )

/** \brief MPS API和实现中使用的缓冲区大小和偏移量的类型。
 *
 *         这必须至少与：：mbedtls_stored_size_t一样宽，但如果更适合目标体系结构，则可以选择更大。
 *
 *         例如，在ARM Thumb的测试构建中，使用uint_fast16_t而不是uint16_t将代码大小从1060字节减少到962字节，因此几乎减少了10%。
 */
typedef size_t mbedtls_mps_size_t;
#define MBEDTLS_MPS_SIZE_MAX  ( (mbedtls_mps_size_t) -1 )

#if MBEDTLS_MPS_STORED_SIZE_MAX > MBEDTLS_MPS_SIZE_MAX
#error "Misconfiguration of mbedtls_mps_size_t and mbedtls_mps_stored_size_t."
#endif

/* \}章节：常见类型*/


#endif /* MBEDTLS_MPS_COMMON_H */

