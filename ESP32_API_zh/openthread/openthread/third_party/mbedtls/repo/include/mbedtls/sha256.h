/**
 * \文件sha256.h
 *
 * \brief此文件包含SHA-224和SHA-256定义和函数。
 *
 * 安全哈希算法224和256（SHA-224和SHA-256）加密哈希函数在FIPS 180-4：安全哈希标准（SHS）</em>中定义。
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
#ifndef MBEDTLS_SHA256_H
#define MBEDTLS_SHA256_H

#if !defined(MBEDTLS_CONFIG_FILE)
#include "mbedtls/config.h"
#else
#include MBEDTLS_CONFIG_FILE
#endif

#include <stddef.h>
#include <stdint.h>

/* MBEDTLS_ERROR_SHA256_HW_ACCEL_FAILED已弃用，不应使用。*/
#define MBEDTLS_ERR_SHA256_HW_ACCEL_FAILED                -0x0037  /**<SHA-256硬件加速器失败*/
#define MBEDTLS_ERR_SHA256_BAD_INPUT_DATA                 -0x0074  /**<SHA-256输入数据格式不正确。*/

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(MBEDTLS_SHA256_ALT)
// 定期实施
//

/**
 * \SHA-256上下文结构简介。
 *
 *                 该结构用于SHA-256和SHA-224校验和计算。在对mbedtls_sha256_starts_ret（）的调用中可以在这两者之间进行选择。
 */
typedef struct mbedtls_sha256_context
{
    uint32_t total[2];          /*!< 已处理的字节数。*/
    uint32_t state[8];          /*!< 中间摘要状态。*/
    unsigned char buffer[64];   /*!< 正在处理的数据块。*/
    int is224;                  /*!< 确定要使用的函数：0:使用SHA-256或1:使用SHA-224。*/
}
mbedtls_sha256_context;

#else  /* MBEDTLS_SHA256_ALT */
#include "sha256_alt.h"
#endif /* MBEDTLS_SHA256_ALT */

/**
 * \brief此函数初始化SHA-256上下文。
 *
 * \param ctx要初始化的SHA-256上下文。此值不能为空。
 */
void mbedtls_sha256_init( mbedtls_sha256_context *ctx );

/**
 * \brief此函数清除SHA-256上下文。
 *
 * \param ctx要清除的SHA-256上下文。这可能是\c NULL，在这种情况下，此函数会立即返回。如果不是空，则必须指向已初始化的SHA-256上下文。
 */
void mbedtls_sha256_free( mbedtls_sha256_context *ctx );

/**
 * \brief此函数克隆SHA-256上下文的状态。
 *
 * \param dst目标上下文。必须对其进行初始化。\param src要克隆的上下文。必须对其进行初始化。
 */
void mbedtls_sha256_clone( mbedtls_sha256_context *dst,
                           const mbedtls_sha256_context *src );

/**
 * \brief此函数启动SHA-224或SHA-256校验和计算。
 *
 * \param ctx要使用的上下文。必须对其进行初始化。\param is224这决定使用哪个函数。对于SHA-256，该值必须为\c 0，对于SHA-224，该值应为\c 1。
 *
 * \成功时返回\c 0。\失败时返回负错误代码。
 */
int mbedtls_sha256_starts_ret( mbedtls_sha256_context *ctx, int is224 );

/**
 * \brief此函数将输入缓冲区送入正在进行的SHA-256校验和计算。
 *
 * \param ctx SHA-256上下文。必须对其进行初始化并启动哈希操作。\param input保存数据的缓冲区。这必须是长度为\pilen Bytes的可读缓冲区。\param ilen输入数据的长度（以字节为单位）。
 *
 * \成功时返回\c 0。\失败时返回负错误代码。
 */
int mbedtls_sha256_update_ret( mbedtls_sha256_context *ctx,
                               const unsigned char *input,
                               size_t ilen );

/**
 * \brief此函数完成SHA-256操作，并将结果写入输出缓冲区。
 *
 * \param ctx SHA-256上下文。必须对其进行初始化并启动哈希操作。\param输出SHA-224或SHA-256校验和结果。这必须是长度为\c 32字节的可写缓冲区。
 *
 * \成功时返回\c 0。\失败时返回负错误代码。
 */
int mbedtls_sha256_finish_ret( mbedtls_sha256_context *ctx,
                               unsigned char output[32] );

/**
 * \brief此函数处理正在进行的SHA-256计算中的单个数据块。此功能仅供内部使用。
 *
 * \param ctx SHA-256上下文。必须对其进行初始化。\param data保存一个数据块的缓冲区。这必须是长度为\c 64字节的可读缓冲区。
 *
 * \成功时返回\c 0。\失败时返回负错误代码。
 */
int mbedtls_internal_sha256_process( mbedtls_sha256_context *ctx,
                                     const unsigned char data[64] );

#if !defined(MBEDTLS_DEPRECATED_REMOVED)
#if defined(MBEDTLS_DEPRECATED_WARNING)
#define MBEDTLS_DEPRECATED      __attribute__((deprecated))
#else
#define MBEDTLS_DEPRECATED
#endif
/**
 * \brief此函数启动SHA-224或SHA-256校验和计算。
 *
 * \已弃用在2.7.0中被mbedtls_sha256_starts_ret（）取代。
 *
 * \param ctx要使用的上下文。必须对其进行初始化。\param is224确定要使用的函数。对于SHA-256，该值必须为\c 0，对于SHA-224，该值应为\c 1。
 */
MBEDTLS_DEPRECATED void mbedtls_sha256_starts( mbedtls_sha256_context *ctx,
                                               int is224 );

/**
 * \brief此函数将输入缓冲区送入正在进行的SHA-256校验和计算。
 *
 * \已弃用在2.7.0中被mbedtls_sha256_update_ret（）取代。
 *
 * \param ctx要使用的SHA-256上下文。必须对其进行初始化并启动哈希操作。\param input保存数据的缓冲区。这必须是长度为\pilen Bytes的可读缓冲区。\param ilen输入数据的长度（以字节为单位）。
 */
MBEDTLS_DEPRECATED void mbedtls_sha256_update( mbedtls_sha256_context *ctx,
                                               const unsigned char *input,
                                               size_t ilen );

/**
 * \brief此函数完成SHA-256操作，并将结果写入输出缓冲区。
 *
 * \已弃用在2.7.0中被mbedtls_sha256_finish_ret（）取代。
 *
 * \param ctx SHA-256上下文。必须对其进行初始化并启动哈希操作。\param输出SHA-224或SHA-256校验和结果。这必须是长度为\c 32字节的可写缓冲区。
 */
MBEDTLS_DEPRECATED void mbedtls_sha256_finish( mbedtls_sha256_context *ctx,
                                               unsigned char output[32] );

/**
 * \brief此函数处理正在进行的SHA-256计算中的单个数据块。此功能仅供内部使用。
 *
 * \已弃用在2.7.0中被mbedtls_internal_sha256_process（）取代。
 *
 * \param ctx SHA-256上下文。必须对其进行初始化。\param data保存一个数据块的缓冲区。这必须是大小为\c 64字节的可读缓冲区。
 */
MBEDTLS_DEPRECATED void mbedtls_sha256_process( mbedtls_sha256_context *ctx,
                                                const unsigned char data[64] );

#undef MBEDTLS_DEPRECATED
#endif /* !MBEDTLS_DEPRECATED_REMOVED */

/**
 * \brief此函数计算缓冲区的SHA-224或SHA-256校验和。
 *
 *                 该函数分配上下文、执行计算并释放上下文。
 *
 *                 SHA-256结果被计算为输出＝SHA-256（输入缓冲器）。
 *
 * \param input保存数据的缓冲区。这必须是长度为\pilen Bytes的可读缓冲区。\param ilen输入数据的长度（以字节为单位）。\param输出SHA-224或SHA-256校验和结果。这必须是长度为\c 32字节的可写缓冲区。\param is224确定要使用的函数。对于SHA-256，该值必须为\c 0，对于SHA-224，该值应为\c 1。
 */
int mbedtls_sha256_ret( const unsigned char *input,
                        size_t ilen,
                        unsigned char output[32],
                        int is224 );

#if !defined(MBEDTLS_DEPRECATED_REMOVED)
#if defined(MBEDTLS_DEPRECATED_WARNING)
#define MBEDTLS_DEPRECATED      __attribute__((deprecated))
#else
#define MBEDTLS_DEPRECATED
#endif

/**
 * \brief此函数计算缓冲区的SHA-224或SHA-256校验和。
 *
 *                 该函数分配上下文、执行计算并释放上下文。
 *
 *                 SHA-256结果被计算为输出＝SHA-256（输入缓冲器）。
 *
 * \已弃用2.7.0中的mbedtls_sha256_ret（）取代。
 *
 * \param input保存数据的缓冲区。这必须是长度为\pilen Bytes的可读缓冲区。\param ilen输入数据的长度（以字节为单位）。\param输出SHA-224或SHA-256校验和结果。这必须是长度为\c 32字节的可写缓冲区。\param is224确定要使用的函数。对于SHA-256，该值必须为\c 0，对于SHA-224，该值应为\c 1。
 */
MBEDTLS_DEPRECATED void mbedtls_sha256( const unsigned char *input,
                                        size_t ilen,
                                        unsigned char output[32],
                                        int is224 );

#undef MBEDTLS_DEPRECATED
#endif /* !MBEDTLS_DEPRECATED_REMOVED */

#if defined(MBEDTLS_SELF_TEST)

/**
 * \简要介绍SHA-224和SHA-256检查程序。
 *
 * \成功时返回\c 0。\失败时返回\c 1。
 */
int mbedtls_sha256_self_test( int verbose );

#endif /* MBEDTLS_SELF_TEST */

#ifdef __cplusplus
}
#endif

#endif /* mbedtls_sha256.h*/

