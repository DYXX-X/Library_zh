/**
 * \文件md2.h
 *
 * \简短的MD2消息摘要算法（哈希函数）
 *
 * \警告MD2被认为是弱消息摘要，其使用构成安全风险。我们建议考虑使用更强的消息摘要。
 */
/*
 *  版权所有The Mbed TLS Contributors SPDX许可证标识符：Apache-2.0
 *
 *  根据Apache许可证2.0版（“许可证”）获得许可；除非符合许可证，否则不得使用此文件。您可以在以下地址获取许可证副本：
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 *  除非适用法律要求或书面同意，否则根据许可证分发的软件是按“原样”分发的，无任何明示或暗示的担保或条件。有关许可证下权限和限制的具体语言，请参阅许可证。
 *
 */
#ifndef MBEDTLS_MD2_H
#define MBEDTLS_MD2_H

#if !defined(MBEDTLS_CONFIG_FILE)
#include "mbedtls/config.h"
#else
#include MBEDTLS_CONFIG_FILE
#endif

#include <stddef.h>

/* MBEDTLS_ERROR_MD2_HW_ACCEL_FAILED已弃用，不应使用。*/
#define MBEDTLS_ERR_MD2_HW_ACCEL_FAILED                   -0x002B  /**<MD2硬件加速器失败*/

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(MBEDTLS_MD2_ALT)
// 定期实施
//

/**
 * \简要的MD2上下文结构
 *
 * \警告MD2被认为是弱消息摘要，其使用构成安全风险。我们建议考虑使用更强的消息摘要。
 *
 */
typedef struct mbedtls_md2_context
{
    unsigned char cksum[16];    /*!< 数据块的校验和*/
    unsigned char state[48];    /*!< 中间消化状态*/
    unsigned char buffer[16];   /*!< 正在处理的数据块*/
    size_t left;                /*!< 缓冲区中的数据量*/
}
mbedtls_md2_context;

#else  /* MBEDTLS_MD2_ALT */
#include "md2_alt.h"
#endif /* MBEDTLS_MD2_ALT */

/**
 * \brief初始化MD2上下文
 *
 * \要初始化的param ctx MD2上下文
 *
 * \警告MD2被认为是弱消息摘要，其使用构成安全风险。我们建议考虑使用更强的消息摘要。
 *
 */
void mbedtls_md2_init( mbedtls_md2_context *ctx );

/**
 * \简要清除MD2上下文
 *
 * \要清除的param ctx MD2上下文
 *
 * \警告MD2被认为是弱消息摘要，其使用构成安全风险。我们建议考虑使用更强的消息摘要。
 *
 */
void mbedtls_md2_free( mbedtls_md2_context *ctx );

/**
 * \简要克隆MD2上下文（的状态）
 *
 * \param dst目标上下文\param src要克隆的上下文
 *
 * \警告MD2被认为是弱消息摘要，其使用构成安全风险。我们建议考虑使用更强的消息摘要。
 *
 */
void mbedtls_md2_clone( mbedtls_md2_context *dst,
                        const mbedtls_md2_context *src );

/**
 * \简短的MD2上下文设置
 *
 * \要初始化的param ctx上下文
 *
 * \如果成功，则返回0
 *
 * \警告MD2被认为是弱消息摘要，其使用构成安全风险。我们建议考虑使用更强的消息摘要。
 *
 */
int mbedtls_md2_starts_ret( mbedtls_md2_context *ctx );

/**
 * \简短的MD2进程缓冲区
 *
 * \param ctx MD2上下文\param保存数据的输入缓冲区\param输入数据的长度
 *
 * \如果成功，则返回0
 *
 * \警告MD2被认为是弱消息摘要，其使用构成安全风险。我们建议考虑使用更强的消息摘要。
 *
 */
int mbedtls_md2_update_ret( mbedtls_md2_context *ctx,
                            const unsigned char *input,
                            size_t ilen );

/**
 * \简要MD2最终摘要
 *
 * \param ctx MD2上下文\param输出MD2校验和结果
 *
 * \如果成功，则返回0
 *
 * \警告MD2被认为是弱消息摘要，其使用构成安全风险。我们建议考虑使用更强的消息摘要。
 *
 */
int mbedtls_md2_finish_ret( mbedtls_md2_context *ctx,
                            unsigned char output[16] );

/**
 * \简要MD2过程数据块（仅供内部使用）
 *
 * \param ctx MD2上下文
 *
 * \如果成功，则返回0
 *
 * \警告MD2被认为是弱消息摘要，其使用构成安全风险。我们建议考虑使用更强的消息摘要。
 *
 */
int mbedtls_internal_md2_process( mbedtls_md2_context *ctx );

#if !defined(MBEDTLS_DEPRECATED_REMOVED)
#if defined(MBEDTLS_DEPRECATED_WARNING)
#define MBEDTLS_DEPRECATED      __attribute__((deprecated))
#else
#define MBEDTLS_DEPRECATED
#endif
/**
 * \简短的MD2上下文设置
 *
 * \已弃用在2.7.0中被mbedtls_md2_starts_ret（）取代
 *
 * \要初始化的param ctx上下文
 *
 * \警告MD2被认为是弱消息摘要，其使用构成安全风险。我们建议考虑使用更强的消息摘要。
 *
 */
MBEDTLS_DEPRECATED void mbedtls_md2_starts( mbedtls_md2_context *ctx );

/**
 * \简短的MD2进程缓冲区
 *
 * \已弃用2.7.0中的mbedtls_md2_update_ret（）取代
 *
 * \param ctx MD2上下文\param保存数据的输入缓冲区\param输入数据的长度
 *
 * \警告MD2被认为是弱消息摘要，其使用构成安全风险。我们建议考虑使用更强的消息摘要。
 *
 */
MBEDTLS_DEPRECATED void mbedtls_md2_update( mbedtls_md2_context *ctx,
                                            const unsigned char *input,
                                            size_t ilen );

/**
 * \简要MD2最终摘要
 *
 * \已弃用2.7.0中的mbedtls_md2_finish_ret（）取代
 *
 * \param ctx MD2上下文\param输出MD2校验和结果
 *
 * \警告MD2被认为是弱消息摘要，其使用构成安全风险。我们建议考虑使用更强的消息摘要。
 *
 */
MBEDTLS_DEPRECATED void mbedtls_md2_finish( mbedtls_md2_context *ctx,
                                            unsigned char output[16] );

/**
 * \简要MD2过程数据块（仅供内部使用）
 *
 * \已弃用2.7.0中的mbedtls_internal_md2_process（）取代
 *
 * \param ctx MD2上下文
 *
 * \警告MD2被认为是弱消息摘要，其使用构成安全风险。我们建议考虑使用更强的消息摘要。
 *
 */
MBEDTLS_DEPRECATED void mbedtls_md2_process( mbedtls_md2_context *ctx );

#undef MBEDTLS_DEPRECATED
#endif /* !MBEDTLS_DEPRECATED_REMOVED */

/**
 * \简要输出=MD2（输入缓冲区）
 *
 * \param保存数据的输入缓冲区\param输入数据的长度\param输出MD2校验和结果
 *
 * \警告MD2被认为是弱消息摘要，其使用构成安全风险。我们建议考虑使用更强的消息摘要。
 *
 */
int mbedtls_md2_ret( const unsigned char *input,
                     size_t ilen,
                     unsigned char output[16] );

#if !defined(MBEDTLS_DEPRECATED_REMOVED)
#if defined(MBEDTLS_DEPRECATED_WARNING)
#define MBEDTLS_DEPRECATED      __attribute__((deprecated))
#else
#define MBEDTLS_DEPRECATED
#endif
/**
 * \简要输出=MD2（输入缓冲区）
 *
 * \已弃用2.7.0中的mbedtls_md2_ret（）取代
 *
 * \param保存数据的输入缓冲区\param输入数据的长度\param输出MD2校验和结果
 *
 * \警告MD2被认为是弱消息摘要，其使用构成安全风险。我们建议考虑使用更强的消息摘要。
 *
 */
MBEDTLS_DEPRECATED void mbedtls_md2( const unsigned char *input,
                                     size_t ilen,
                                     unsigned char output[16] );

#undef MBEDTLS_DEPRECATED
#endif /* !MBEDTLS_DEPRECATED_REMOVED */

#if defined(MBEDTLS_SELF_TEST)

/**
 * \简要检查程序
 *
 * \如果成功，则返回0；如果测试失败，则返回1
 *
 * \警告MD2被认为是弱消息摘要，其使用构成安全风险。我们建议考虑使用更强的消息摘要。
 *
 */
int mbedtls_md2_self_test( int verbose );

#endif /* MBEDTLS_SELF_TEST */

#ifdef __cplusplus
}
#endif

#endif /* mbedtls_md2.h文件*/

