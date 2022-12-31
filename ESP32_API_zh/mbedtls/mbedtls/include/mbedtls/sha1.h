/**
 * \文件sha1.h
 *
 * \brief此文件包含SHA-1定义和函数。
 *
 * 安全哈希算法1（SHA-1）加密哈希函数在FIPS 180-4：安全哈希标准（SHS）</em>中定义。
 *
 * \警告SHA-1被认为是弱消息摘要，其使用构成安全风险。我们建议考虑使用更强的消息摘要。
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
#ifndef MBEDTLS_SHA1_H
#define MBEDTLS_SHA1_H

#if !defined(MBEDTLS_CONFIG_FILE)
#include "mbedtls/config.h"
#else
#include MBEDTLS_CONFIG_FILE
#endif

#include <stddef.h>
#include <stdint.h>

/* MBEDTLS_ERROR_SHA1_HW_ACCEL_FAILED已弃用，不应使用。*/
/**SHA-1硬件加速器失败*/
#define MBEDTLS_ERR_SHA1_HW_ACCEL_FAILED                  -0x0035
/**SHA-1输入数据格式不正确。*/
#define MBEDTLS_ERR_SHA1_BAD_INPUT_DATA                   -0x0073

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(MBEDTLS_SHA1_ALT)
// 定期实施
//

/**
 * \SHA-1上下文结构简介。
 *
 * \警告SHA-1被认为是弱消息摘要，其使用构成安全风险。我们建议考虑使用更强的消息摘要。
 *
 */
typedef struct mbedtls_sha1_context
{
    uint32_t total[2];          /*!< 已处理的字节数。*/
    uint32_t state[5];          /*!< 中间摘要状态。*/
    unsigned char buffer[64];   /*!< 正在处理的数据块。*/
}
mbedtls_sha1_context;

#else  /* MBEDTLS_SHA1_ALT */
#include "sha1_alt.h"
#endif /* MBEDTLS_SHA1_ALT */

/**
 * \brief此函数初始化SHA-1上下文。
 *
 * \警告SHA-1被认为是弱消息摘要，其使用构成安全风险。我们建议考虑使用更强的消息摘要。
 *
 * \param ctx要初始化的SHA-1上下文。此值不能为空。
 *
 */
void mbedtls_sha1_init( mbedtls_sha1_context *ctx );

/**
 * \brief此函数清除SHA-1上下文。
 *
 * \警告SHA-1被认为是弱消息摘要，其使用构成安全风险。我们建议考虑使用更强的消息摘要。
 *
 * \param ctx要清除的SHA-1上下文。这可能是空的，在这种情况下，此函数不执行任何操作。如果不是空，则必须指向已初始化的SHA-1上下文。
 *
 */
void mbedtls_sha1_free( mbedtls_sha1_context *ctx );

/**
 * \brief此函数克隆SHA-1上下文的状态。
 *
 * \警告SHA-1被认为是弱消息摘要，其使用构成安全风险。我们建议考虑使用更强的消息摘要。
 *
 * \param dst要克隆到的SHA-1上下文。必须对其进行初始化。\param src要从中克隆的SHA-1上下文。必须对其进行初始化。
 *
 */
void mbedtls_sha1_clone( mbedtls_sha1_context *dst,
                         const mbedtls_sha1_context *src );

/**
 * \brief此函数启动SHA-1校验和计算。
 *
 * \警告SHA-1被认为是弱消息摘要，其使用构成安全风险。我们建议考虑使用更强的消息摘要。
 *
 * \param ctx要初始化的SHA-1上下文。必须对其进行初始化。
 *
 * \成功时返回\c 0。\失败时返回负错误代码。
 *
 */
int mbedtls_sha1_starts_ret( mbedtls_sha1_context *ctx );

/**
 * \brief此函数将输入缓冲区送入正在进行的SHA-1校验和计算中。
 *
 * \警告SHA-1被认为是弱消息摘要，其使用构成安全风险。我们建议考虑使用更强的消息摘要。
 *
 * \param ctx SHA-1上下文。必须对其进行初始化并启动哈希操作。\param input保存输入数据的缓冲区。这必须是长度为\pilen Bytes的可读缓冲区。\param ilen输入数据的长度，以字节为单位。
 *
 * \成功时返回\c 0。\失败时返回负错误代码。
 */
int mbedtls_sha1_update_ret( mbedtls_sha1_context *ctx,
                             const unsigned char *input,
                             size_t ilen );

/**
 * \brief此函数完成SHA-1操作，并将结果写入输出缓冲区。
 *
 * \警告SHA-1被认为是弱消息摘要，其使用构成安全风险。我们建议考虑使用更强的消息摘要。
 *
 * \param ctx要使用的SHA-1上下文。必须对其进行初始化并启动哈希操作。\param output SHA-1校验和结果。这必须是长度为\c 20字节的可写缓冲区。
 *
 * \成功时返回\c 0。\失败时返回负错误代码。
 */
int mbedtls_sha1_finish_ret( mbedtls_sha1_context *ctx,
                             unsigned char output[20] );

/**
 * \简短的SHA-1过程数据块（仅供内部使用）。
 *
 * \警告SHA-1被认为是弱消息摘要，其使用构成安全风险。我们建议考虑使用更强的消息摘要。
 *
 * \param ctx要使用的SHA-1上下文。必须对其进行初始化。\param data正在处理的数据块。这必须是长度为\c 64字节的可读缓冲区。
 *
 * \成功时返回\c 0。\失败时返回负错误代码。
 *
 */
int mbedtls_internal_sha1_process( mbedtls_sha1_context *ctx,
                                   const unsigned char data[64] );

#if !defined(MBEDTLS_DEPRECATED_REMOVED)
#if defined(MBEDTLS_DEPRECATED_WARNING)
#define MBEDTLS_DEPRECATED      __attribute__((deprecated))
#else
#define MBEDTLS_DEPRECATED
#endif
/**
 * \brief此函数启动SHA-1校验和计算。
 *
 * \警告SHA-1被认为是弱消息摘要，其使用构成安全风险。我们建议考虑使用更强的消息摘要。
 *
 * \已弃用在2.7.0中被mbedtls_sha1_starts_ret（）取代。
 *
 * \param ctx要初始化的SHA-1上下文。必须对其进行初始化。
 *
 */
MBEDTLS_DEPRECATED void mbedtls_sha1_starts( mbedtls_sha1_context *ctx );

/**
 * \brief此函数将输入缓冲区送入正在进行的SHA-1校验和计算中。
 *
 * \警告SHA-1被认为是弱消息摘要，其使用构成安全风险。我们建议考虑使用更强的消息摘要。
 *
 * \已弃用在2.7.0中被mbedtls_sha1_update_ret（）取代。
 *
 * \param ctx SHA-1上下文。必须对其进行初始化并启动哈希操作。\param input保存输入数据的缓冲区。这必须是长度为\pilen Bytes的可读缓冲区。\param ilen输入数据的长度，以字节为单位。
 *
 */
MBEDTLS_DEPRECATED void mbedtls_sha1_update( mbedtls_sha1_context *ctx,
                                             const unsigned char *input,
                                             size_t ilen );

/**
 * \brief此函数完成SHA-1操作，并将结果写入输出缓冲区。
 *
 * \警告SHA-1被认为是弱消息摘要，其使用构成安全风险。我们建议考虑使用更强的消息摘要。
 *
 * \已弃用在2.7.0中被mbedtls_sha1_finish_ret（）取代。
 *
 * \param ctx SHA-1上下文。必须对其进行初始化并启动哈希操作。\param output SHA-1校验和结果。这必须是长度为\c 20字节的可写缓冲区。
 */
MBEDTLS_DEPRECATED void mbedtls_sha1_finish( mbedtls_sha1_context *ctx,
                                             unsigned char output[20] );

/**
 * \简短的SHA-1过程数据块（仅供内部使用）。
 *
 * \警告SHA-1被认为是弱消息摘要，其使用构成安全风险。我们建议考虑使用更强的消息摘要。
 *
 * \已弃用2.7.0中的mbedtls_internal_sha1_process（）取代。
 *
 * \param ctx SHA-1上下文。必须对其进行初始化。\param data正在处理的数据块。这必须是长度为\c 64字节的可读缓冲区。
 *
 */
MBEDTLS_DEPRECATED void mbedtls_sha1_process( mbedtls_sha1_context *ctx,
                                              const unsigned char data[64] );

#undef MBEDTLS_DEPRECATED
#endif /* !MBEDTLS_DEPRECATED_REMOVED */

/**
 * \brief此函数计算缓冲区的SHA-1校验和。
 *
 *                 该函数分配上下文、执行计算并释放上下文。
 *
 *                 SHA-1结果被计算为输出＝SHA-1（输入缓冲器）。
 *
 * \警告SHA-1被认为是弱消息摘要，其使用构成安全风险。我们建议考虑使用更强的消息摘要。
 *
 * \param input保存输入数据的缓冲区。这必须是长度为\pilen Bytes的可读缓冲区。\param ilen输入数据的长度，以字节为单位。\param output SHA-1校验和结果。这必须是长度为\c 20字节的可写缓冲区。
 *
 * \成功时返回\c 0。\失败时返回负错误代码。
 *
 */
int mbedtls_sha1_ret( const unsigned char *input,
                      size_t ilen,
                      unsigned char output[20] );

#if !defined(MBEDTLS_DEPRECATED_REMOVED)
#if defined(MBEDTLS_DEPRECATED_WARNING)
#define MBEDTLS_DEPRECATED      __attribute__((deprecated))
#else
#define MBEDTLS_DEPRECATED
#endif
/**
 * \brief此函数计算缓冲区的SHA-1校验和。
 *
 *                 该函数分配上下文、执行计算并释放上下文。
 *
 *                 SHA-1结果被计算为输出＝SHA-1（输入缓冲器）。
 *
 * \警告SHA-1被认为是弱消息摘要，其使用构成安全风险。我们建议考虑使用更强的消息摘要。
 *
 * \已弃用2.7.0中的mbedtls_sha1_ret（）取代
 *
 * \param input保存输入数据的缓冲区。这必须是长度为\pilen Bytes的可读缓冲区。\param ilen输入数据的长度，以字节为单位。\param output SHA-1校验和结果。这必须是大小为\c 20字节的可写缓冲区。
 *
 */
MBEDTLS_DEPRECATED void mbedtls_sha1( const unsigned char *input,
                                      size_t ilen,
                                      unsigned char output[20] );

#undef MBEDTLS_DEPRECATED
#endif /* !MBEDTLS_DEPRECATED_REMOVED */

#if defined(MBEDTLS_SELF_TEST)

/**
 * \简要介绍SHA-1检查程序。
 *
 * \警告SHA-1被认为是弱消息摘要，其使用构成安全风险。我们建议考虑使用更强的消息摘要。
 *
 * \成功时返回\c 0。\失败时返回\c 1。
 *
 */
int mbedtls_sha1_self_test( int verbose );

#endif /* MBEDTLS_SELF_TEST */

#ifdef __cplusplus
}
#endif

#endif /* mbedtls_sha1.h文件*/

