/**
 * \文件ripemd160.h
 *
 * \RIPE MD-160消息摘要
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
#ifndef MBEDTLS_RIPEMD160_H
#define MBEDTLS_RIPEMD160_H

#if !defined(MBEDTLS_CONFIG_FILE)
#include "mbedtls/config.h"
#else
#include MBEDTLS_CONFIG_FILE
#endif

#include <stddef.h>
#include <stdint.h>

/* MBEDTLS_ERROR_RIPEMD160_HW_ACCEL_FAILED已弃用，不应使用。
 */
/**RIPEMD160硬件加速器故障*/
#define MBEDTLS_ERR_RIPEMD160_HW_ACCEL_FAILED             -0x0031

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(MBEDTLS_RIPEMD160_ALT)
// 定期实施
//

/**
 * \RIPEMD-160上下文结构简介
 */
typedef struct mbedtls_ripemd160_context
{
    uint32_t total[2];          /*!< 处理的字节数*/
    uint32_t state[5];          /*!< 中间消化状态*/
    unsigned char buffer[64];   /*!< 正在处理的数据块*/
}
mbedtls_ripemd160_context;

#else  /* MBEDTLS_RIPEMD160_ALT */
#include "ripemd160_alt.h"
#endif /* MBEDTLS_RIPEMD160_ALT */

/**
 * \简要初始化RIPEMD-160上下文
 *
 * \param ctx要初始化的RIPEMD-160上下文
 */
void mbedtls_ripemd160_init( mbedtls_ripemd160_context *ctx );

/**
 * \简要清除RIPEMD-160上下文
 *
 * \param ctx要清除的RIPEMD-160上下文
 */
void mbedtls_ripemd160_free( mbedtls_ripemd160_context *ctx );

/**
 * \RIPEMD-160上下文的简要克隆（状态）
 *
 * \param dst目标上下文\param src要克隆的上下文
 */
void mbedtls_ripemd160_clone( mbedtls_ripemd160_context *dst,
                        const mbedtls_ripemd160_context *src );

/**
 * \RIPEMD-160上下文设置简介
 *
 * \要初始化的param ctx上下文
 *
 * \如果成功，则返回0
 */
int mbedtls_ripemd160_starts_ret( mbedtls_ripemd160_context *ctx );

/**
 * \RIPEMD-160过程缓冲区简介
 *
 * \param ctx RIPEMD-160上下文\param保存数据的输入缓冲区\param输入数据的长度
 *
 * \如果成功，则返回0
 */
int mbedtls_ripemd160_update_ret( mbedtls_ripemd160_context *ctx,
                                  const unsigned char *input,
                                  size_t ilen );

/**
 * \RIPEMD-160最终摘要简介
 *
 * \param ctx RIPEMD-160上下文\param输出RIPEMD160校验和结果
 *
 * \如果成功，则返回0
 */
int mbedtls_ripemd160_finish_ret( mbedtls_ripemd160_context *ctx,
                                  unsigned char output[20] );

/**
 * \RIPEMD-160过程数据块（仅供内部使用）
 *
 * \param ctx RIPEMD-160上下文\param保存一个数据块的数据缓冲区
 *
 * \如果成功，则返回0
 */
int mbedtls_internal_ripemd160_process( mbedtls_ripemd160_context *ctx,
                                        const unsigned char data[64] );

#if !defined(MBEDTLS_DEPRECATED_REMOVED)
#if defined(MBEDTLS_DEPRECATED_WARNING)
#define MBEDTLS_DEPRECATED      __attribute__((deprecated))
#else
#define MBEDTLS_DEPRECATED
#endif
/**
 * \RIPEMD-160上下文设置简介
 *
 * \已弃用在2.7.0中被mbedtls_ripemd160_starts_ret（）取代
 *
 * \要初始化的param ctx上下文
 */
MBEDTLS_DEPRECATED void mbedtls_ripemd160_starts(
                                            mbedtls_ripemd160_context *ctx );

/**
 * \RIPEMD-160过程缓冲区简介
 *
 * \已弃用在2.7.0中被mbedtls_ripemd160_update_ret（）取代
 *
 * \param ctx RIPEMD-160上下文\param保存数据的输入缓冲区\param输入数据的长度
 */
MBEDTLS_DEPRECATED void mbedtls_ripemd160_update(
                                                mbedtls_ripemd160_context *ctx,
                                                const unsigned char *input,
                                                size_t ilen );

/**
 * \RIPEMD-160最终摘要简介
 *
 * \已弃用在2.7.0中被mbedtls_ripemd160_finish_ret（）取代
 *
 * \param ctx RIPEMD-160上下文\param输出RIPEMD160校验和结果
 */
MBEDTLS_DEPRECATED void mbedtls_ripemd160_finish(
                                                mbedtls_ripemd160_context *ctx,
                                                unsigned char output[20] );

/**
 * \RIPEMD-160过程数据块（仅供内部使用）
 *
 * \已弃用在2.7.0中被mbedtls_internal_tripemd160_process（）取代
 *
 * \param ctx RIPEMD-160上下文\param保存一个数据块的数据缓冲区
 */
MBEDTLS_DEPRECATED void mbedtls_ripemd160_process(
                                            mbedtls_ripemd160_context *ctx,
                                            const unsigned char data[64] );

#undef MBEDTLS_DEPRECATED
#endif /* !MBEDTLS_DEPRECATED_REMOVED */

/**
 * \简短输出=RIPEMD-160（输入缓冲区）
 *
 * \param保存数据的输入缓冲区\param输入数据的长度\param输出RIPEMD-160校验和结果
 *
 * \如果成功，则返回0
 */
int mbedtls_ripemd160_ret( const unsigned char *input,
                           size_t ilen,
                           unsigned char output[20] );

#if !defined(MBEDTLS_DEPRECATED_REMOVED)
#if defined(MBEDTLS_DEPRECATED_WARNING)
#define MBEDTLS_DEPRECATED      __attribute__((deprecated))
#else
#define MBEDTLS_DEPRECATED
#endif
/**
 * \简短输出=RIPEMD-160（输入缓冲区）
 *
 * \已弃用2.7.0中的mbedtls_ripemd160_ret（）取代
 *
 * \param保存数据的输入缓冲区\param输入数据的长度\param输出RIPEMD-160校验和结果
 */
MBEDTLS_DEPRECATED void mbedtls_ripemd160( const unsigned char *input,
                                           size_t ilen,
                                           unsigned char output[20] );

#undef MBEDTLS_DEPRECATED
#endif /* !MBEDTLS_DEPRECATED_REMOVED */

#if defined(MBEDTLS_SELF_TEST)

/**
 * \简要检查程序
 *
 * \如果成功，则返回0；如果测试失败，则返回1
 */
int mbedtls_ripemd160_self_test( int verbose );

#endif /* MBEDTLS_SELF_TEST */

#ifdef __cplusplus
}
#endif

#endif /* mbedtls_ripemd160.h*/

