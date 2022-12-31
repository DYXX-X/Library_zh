/**
 * \xtea.h文件
 *
 * \简短XTEA分组密码（32位）
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
#ifndef MBEDTLS_XTEA_H
#define MBEDTLS_XTEA_H

#if !defined(MBEDTLS_CONFIG_FILE)
#include "mbedtls/config.h"
#else
#include MBEDTLS_CONFIG_FILE
#endif

#include <stddef.h>
#include <stdint.h>

#define MBEDTLS_XTEA_ENCRYPT     1
#define MBEDTLS_XTEA_DECRYPT     0

/**数据输入的长度无效。*/
#define MBEDTLS_ERR_XTEA_INVALID_INPUT_LENGTH             -0x0028

/* MBEDTLS_ERROR_XTEA_HW_ACCEL_FAILED已弃用，不应使用。*/
/**XTEA硬件加速器失败。*/
#define MBEDTLS_ERR_XTEA_HW_ACCEL_FAILED                  -0x0029

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(MBEDTLS_XTEA_ALT)
// 定期实施
//

/**
 * \简要的XTEA上下文结构
 */
typedef struct mbedtls_xtea_context
{
    uint32_t k[4];       /*!< 钥匙*/
}
mbedtls_xtea_context;

#else  /* MBEDTLS_XTEA_ALT */
#include "xtea_alt.h"
#endif /* MBEDTLS_XTEA_ALT */

/**
 * \brief初始化XTEA上下文
 *
 * \param ctx要初始化的XTEA上下文
 */
void mbedtls_xtea_init( mbedtls_xtea_context *ctx );

/**
 * \简要清除XTEA上下文
 *
 * \param ctx要清除的XTEA上下文
 */
void mbedtls_xtea_free( mbedtls_xtea_context *ctx );

/**
 * \简要XTEA密钥计划
 *
 * \param ctx要初始化的XTEA上下文\param密钥
 */
void mbedtls_xtea_setup( mbedtls_xtea_context *ctx, const unsigned char key[16] );

/**
 * \简短的XTEA密码函数
 *
 * \param ctx XTEA上下文\param模式MBEDTLS_XTEA_ENCRYPT或MBEDTLS_XTEA_DECRYPT \param输入8字节输入块\param输出8字节输出块
 *
 * \如果成功，则返回0
 */
int mbedtls_xtea_crypt_ecb( mbedtls_xtea_context *ctx,
                    int mode,
                    const unsigned char input[8],
                    unsigned char output[8] );

#if defined(MBEDTLS_CIPHER_MODE_CBC)
/**
 * \简短的XTEA CBC密码函数
 *
 * \param ctx XTEA上下文\param mode MBEDTLS_XTEA_ENCRYPT或MBEDTLS_XTEA_DECRYPT \param length输入长度，8的倍数\param iv CBC模式的初始化向量\param输入输入块\param输出输出块
 *
 * \如果成功，则返回0；如果长度为%8！=0
 */
int mbedtls_xtea_crypt_cbc( mbedtls_xtea_context *ctx,
                    int mode,
                    size_t length,
                    unsigned char iv[8],
                    const unsigned char *input,
                    unsigned char *output);
#endif /* MBEDTLS_CIPHER_MODE_CBC */

#if defined(MBEDTLS_SELF_TEST)

/**
 * \简要检查程序
 *
 * \如果成功，则返回0；如果测试失败，则返回1
 */
int mbedtls_xtea_self_test( int verbose );

#endif /* MBEDTLS_SELF_TEST */

#ifdef __cplusplus
}
#endif

#endif /* xtea.h公司*/

