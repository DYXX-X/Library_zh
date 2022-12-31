/**
 * \文件sha512.h\brief此文件包含SHA-384和SHA-512定义和函数。
 *
 * 安全哈希算法384和512（SHA-384和SHA-512）加密哈希函数在FIPS 180-4：安全哈希标准（SHS）</em>中定义。
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
#ifndef MBEDTLS_SHA512_H
#define MBEDTLS_SHA512_H

#if !defined(MBEDTLS_CONFIG_FILE)
#include "mbedtls/config.h"
#else
#include MBEDTLS_CONFIG_FILE
#endif

#include <stddef.h>
#include <stdint.h>

/* MBEDTLS_ERROR_SHA512_HW_ACCEL_FAILED已弃用，不应使用。*/
/**SHA-512硬件加速器故障*/
#define MBEDTLS_ERR_SHA512_HW_ACCEL_FAILED                -0x0039
/**SHA-512输入数据格式不正确。*/
#define MBEDTLS_ERR_SHA512_BAD_INPUT_DATA                 -0x0075

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(MBEDTLS_SHA512_ALT)
// 定期实施
//

/**
 * \SHA-512上下文结构简介。
 *
 *                 该结构用于SHA-384和SHA-512校验和计算。在对mbedtls_sha512_starts_ret（）的调用中可以在这两者之间进行选择。
 */
typedef struct mbedtls_sha512_context
{
    uint64_t total[2];          /*!< 已处理的字节数。*/
    uint64_t state[8];          /*!< 中间摘要状态。*/
    unsigned char buffer[128];  /*!< 正在处理的数据块。*/
#if !defined(MBEDTLS_SHA512_NO_SHA384)
    int is384;                  /*!< 确定要使用的函数：0:使用SHA-512或1:使用SHA-384。*/
#endif
}
mbedtls_sha512_context;

#else  /* MBEDTLS_SHA512_ALT */
#include "sha512_alt.h"
#endif /* MBEDTLS_SHA512_ALT */

/**
 * \brief此函数初始化SHA-512上下文。
 *
 * \param ctx要初始化的SHA-512上下文。此值不能为空。
 */
void mbedtls_sha512_init( mbedtls_sha512_context *ctx );

/**
 * \brief此函数清除SHA-512上下文。
 *
 * \param ctx要清除的SHA-512上下文。这可能是空的，在这种情况下，此函数不执行任何操作。如果不是空，则必须指向已初始化的SHA-512上下文。
 */
void mbedtls_sha512_free( mbedtls_sha512_context *ctx );

/**
 * \brief此函数克隆SHA-512上下文的状态。
 *
 * \param dst目标上下文。必须对其进行初始化。\param src要克隆的上下文。必须对其进行初始化。
 */
void mbedtls_sha512_clone( mbedtls_sha512_context *dst,
                           const mbedtls_sha512_context *src );

/**
 * \brief此函数启动SHA-384或SHA-512校验和计算。
 *
 * \param ctx要使用的SHA-512上下文。必须对其进行初始化。\param is384确定要使用的函数。对于SHA-512，该值必须为\c 0，对于SHA-384，该值应为\c 1。
 *
 * \注意：当定义了\c MBEDTLS_SHA512_NO_SHA384时，\p is384必须为\c 0，否则函数将返回#MBEDTLS_ERROR_SHA512_BAD_INPUT_DATA。
 *
 * \成功时返回\c 0。\失败时返回负错误代码。
 */
int mbedtls_sha512_starts_ret( mbedtls_sha512_context *ctx, int is384 );

/**
 * \brief此函数将输入缓冲区送入正在进行的SHA-512校验和计算。
 *
 * \param ctx SHA-512上下文。必须对其进行初始化并启动哈希操作。\param input保存输入数据的缓冲区。这必须是长度为\pilen Bytes的可读缓冲区。\param ilen输入数据的长度（以字节为单位）。
 *
 * \成功时返回\c 0。\失败时返回负错误代码。
 */
int mbedtls_sha512_update_ret( mbedtls_sha512_context *ctx,
                    const unsigned char *input,
                    size_t ilen );

/**
 * \brief此函数完成SHA-512操作，并将结果写入输出缓冲区。
 *
 * \param ctx SHA-512上下文。必须对其进行初始化并启动哈希操作。\param输出SHA-384或SHA-512校验和结果。这必须是长度为\c 64字节的可写缓冲区。
 *
 * \成功时返回\c 0。\失败时返回负错误代码。
 */
int mbedtls_sha512_finish_ret( mbedtls_sha512_context *ctx,
                               unsigned char output[64] );

/**
 * \brief此函数处理正在进行的SHA-512计算中的单个数据块。此功能仅供内部使用。
 *
 * \param ctx SHA-512上下文。必须对其进行初始化。\param data保存一个数据块的缓冲区。这必须是长度为\c 128字节的可读缓冲区。
 *
 * \成功时返回\c 0。\失败时返回负错误代码。
 */
int mbedtls_internal_sha512_process( mbedtls_sha512_context *ctx,
                                     const unsigned char data[128] );
#if !defined(MBEDTLS_DEPRECATED_REMOVED)
#if defined(MBEDTLS_DEPRECATED_WARNING)
#define MBEDTLS_DEPRECATED      __attribute__((deprecated))
#else
#define MBEDTLS_DEPRECATED
#endif
/**
 * \brief此函数启动SHA-384或SHA-512校验和计算。
 *
 * \已弃用在2.7.0中被mbedtls_sha512_starts_ret（）取代
 *
 * \param ctx要使用的SHA-512上下文。必须对其进行初始化。\param is384确定要使用的函数。对于SHA-512，该值必须为\c 0，对于SHA-384，该值应为\c 1。
 *
 * \注意：当定义了\c MBEDTLS_SHA512_NO_SHA384时，\p is384必须为\c 0，否则函数将无法工作。
 */
MBEDTLS_DEPRECATED void mbedtls_sha512_starts( mbedtls_sha512_context *ctx,
                                               int is384 );

/**
 * \brief此函数将输入缓冲区送入正在进行的SHA-512校验和计算。
 *
 * \已弃用在2.7.0中被mbedtls_sha512_update_ret（）取代。
 *
 * \param ctx SHA-512上下文。必须对其进行初始化并启动哈希操作。\param input保存数据的缓冲区。这必须是长度为\pilen Bytes的可读缓冲区。\param ilen输入数据的长度（以字节为单位）。
 */
MBEDTLS_DEPRECATED void mbedtls_sha512_update( mbedtls_sha512_context *ctx,
                                               const unsigned char *input,
                                               size_t ilen );

/**
 * \brief此函数完成SHA-512操作，并将结果写入输出缓冲区。
 *
 * \已弃用在2.7.0中被mbedtls_sha512_finish_ret（）取代。
 *
 * \param ctx SHA-512上下文。必须对其进行初始化并启动哈希操作。\param输出SHA-384或SHA-512校验和结果。这必须是大小为\c 64字节的可写缓冲区。
 */
MBEDTLS_DEPRECATED void mbedtls_sha512_finish( mbedtls_sha512_context *ctx,
                                               unsigned char output[64] );

/**
 * \brief此函数处理正在进行的SHA-512计算中的单个数据块。此功能仅供内部使用。
 *
 * \已弃用在2.7.0中被mbedtls_internal_sha512_process（）取代。
 *
 * \param ctx SHA-512上下文。必须对其进行初始化。\param data保存一个数据块的缓冲区。这必须是长度为\c 128字节的可读缓冲区。
 */
MBEDTLS_DEPRECATED void mbedtls_sha512_process(
                                            mbedtls_sha512_context *ctx,
                                            const unsigned char data[128] );

#undef MBEDTLS_DEPRECATED
#endif /* !MBEDTLS_DEPRECATED_REMOVED */

/**
 * \brief此函数计算缓冲区的SHA-512或SHA-384校验和。
 *
 *                 该函数分配上下文、执行计算并释放上下文。
 *
 *                 SHA-512结果被计算为输出＝SHA-512（输入缓冲器）。
 *
 * \param input保存输入数据的缓冲区。这必须是长度为\pilen Bytes的可读缓冲区。\param ilen输入数据的长度（以字节为单位）。\param输出SHA-384或SHA-512校验和结果。这必须是长度为\c 64字节的可写缓冲区。\param is384确定要使用的函数。对于SHA-512，该值必须为\c 0，对于SHA-384，该值应为\c 1。
 *
 * \注意：当定义了\c MBEDTLS_SHA512_NO_SHA384时，\p is384必须为\c 0，否则函数将返回#MBEDTLS_ERROR_SHA512_BAD_INPUT_DATA。
 *
 * \成功时返回\c 0。\失败时返回负错误代码。
 */
int mbedtls_sha512_ret( const unsigned char *input,
                        size_t ilen,
                        unsigned char output[64],
                        int is384 );

#if !defined(MBEDTLS_DEPRECATED_REMOVED)
#if defined(MBEDTLS_DEPRECATED_WARNING)
#define MBEDTLS_DEPRECATED      __attribute__((deprecated))
#else
#define MBEDTLS_DEPRECATED
#endif

/**
 * \brief此函数计算缓冲区的SHA-512或SHA-384校验和。
 *
 *                 该函数分配上下文、执行计算并释放上下文。
 *
 *                 SHA-512结果被计算为输出＝SHA-512（输入缓冲器）。
 *
 * \已弃用2.7.0中的mbedtls_sha512_ret（）取代
 *
 * \param input保存数据的缓冲区。这必须是长度为\pilen Bytes的可读缓冲区。\param ilen输入数据的长度（以字节为单位）。\param输出SHA-384或SHA-512校验和结果。这必须是长度为\c 64字节的可写缓冲区。\param is384确定要使用的函数。对于SHA-512，该值必须为\c 0，对于SHA-384，该值应为\c 1。
 *
 * \注意：当定义了\c MBEDTLS_SHA512_NO_SHA384时，\p is384必须为\c 0，否则函数将无法工作。
 */
MBEDTLS_DEPRECATED void mbedtls_sha512( const unsigned char *input,
                                        size_t ilen,
                                        unsigned char output[64],
                                        int is384 );

#undef MBEDTLS_DEPRECATED
#endif /* !MBEDTLS_DEPRECATED_REMOVED */

#if defined(MBEDTLS_SELF_TEST)

 /**
 * \简要介绍SHA-384或SHA-512检查程序。
 *
 * \成功时返回\c 0。\失败时返回\c 1。
 */
int mbedtls_sha512_self_test( int verbose );
#endif /* MBEDTLS_SELF_TEST */

#ifdef __cplusplus
}
#endif

#endif /* mbedtls_sha512.h*/

