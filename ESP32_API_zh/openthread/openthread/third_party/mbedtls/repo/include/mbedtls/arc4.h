/**
 * \文件arc4.h
 *
 * \ARCFOUR流密码简介
 *
 * \警告ARC4被认为是弱密码，其使用构成安全风险。我们建议改用更强的密码。
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
#ifndef MBEDTLS_ARC4_H
#define MBEDTLS_ARC4_H

#if !defined(MBEDTLS_CONFIG_FILE)
#include "mbedtls/config.h"
#else
#include MBEDTLS_CONFIG_FILE
#endif

#include <stddef.h>

/* MBEDTLS_ERROR_ARC4_HW_ACCEL_FAILED已弃用，不应使用。*/
#define MBEDTLS_ERR_ARC4_HW_ACCEL_FAILED                  -0x0019  /**<ARC4硬件加速器失败。*/

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(MBEDTLS_ARC4_ALT)
// 定期实施
//

/**
 * \ARC4上下文结构简介
 *
 * \警告ARC4被认为是弱密码，其使用构成安全风险。我们建议改用更强的密码。
 *
 */
typedef struct mbedtls_arc4_context
{
    int x;                      /*!< 排列指数*/
    int y;                      /*!< 排列指数*/
    unsigned char m[256];       /*!< 排列表*/
}
mbedtls_arc4_context;

#else  /* MBEDTLS_ARC4_ALT */
#include "arc4_alt.h"
#endif /* MBEDTLS_ARC4_ALT */

/**
 * \简要初始化ARC4上下文
 *
 * \要初始化的param ctx ARC4上下文
 *
 * \警告ARC4被认为是弱密码，其使用构成安全风险。我们建议改用更强的密码。
 *
 */
void mbedtls_arc4_init( mbedtls_arc4_context *ctx );

/**
 * \简要清除ARC4上下文
 *
 * \要清除的param ctx ARC4上下文
 *
 * \警告ARC4被认为是弱密码，其使用构成安全风险。我们建议改用更强的密码。
 *
 */
void mbedtls_arc4_free( mbedtls_arc4_context *ctx );

/**
 * \ARC4关键计划简介
 *
 * \param ctx要设置的ARC4上下文\param key密钥\param keylen密钥长度，以字节为单位
 *
 * \警告ARC4被认为是弱密码，其使用构成安全风险。我们建议改用更强的密码。
 *
 */
void mbedtls_arc4_setup( mbedtls_arc4_context *ctx, const unsigned char *key,
                 unsigned int keylen );

/**
 * \简短的ARC4密码函数
 *
 * \param ctx ARC4 context\param输入数据的长度\param保存输入数据的输入缓冲区\param输出数据的输出缓冲区
 *
 * \如果成功，则返回0
 *
 * \警告ARC4被认为是弱密码，其使用构成安全风险。我们建议改用更强的密码。
 *
 */
int mbedtls_arc4_crypt( mbedtls_arc4_context *ctx, size_t length, const unsigned char *input,
                unsigned char *output );

#if defined(MBEDTLS_SELF_TEST)

/**
 * \简要检查程序
 *
 * \如果成功，则返回0；如果测试失败，则返回1
 *
 * \警告ARC4被认为是弱密码，其使用构成安全风险。我们建议改用更强的密码。
 *
 */
int mbedtls_arc4_self_test( int verbose );

#endif /* MBEDTLS_SELF_TEST */

#ifdef __cplusplus
}
#endif

#endif /* 弧4.h*/

