/**
 * \文件pkcs5.h
 *
 * \简短的PKCS#5函数
 *
 * \作者Mathias Olsson<mathias@kompetensum.com>
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
#ifndef MBEDTLS_PKCS5_H
#define MBEDTLS_PKCS5_H

#if !defined(MBEDTLS_CONFIG_FILE)
#include "mbedtls/config.h"
#else
#include MBEDTLS_CONFIG_FILE
#endif

#include "mbedtls/asn1.h"
#include "mbedtls/md.h"

#include <stddef.h>
#include <stdint.h>

/**函数的输入参数错误。*/
#define MBEDTLS_ERR_PKCS5_BAD_INPUT_DATA                  -0x2f80
/**意外的ASN.1数据。*/
#define MBEDTLS_ERR_PKCS5_INVALID_FORMAT                  -0x2f00
/**请求的加密或摘要alg不可用。*/
#define MBEDTLS_ERR_PKCS5_FEATURE_UNAVAILABLE             -0x2e80
/**给定的私钥密码不允许正确解密。*/
#define MBEDTLS_ERR_PKCS5_PASSWORD_MISMATCH               -0x2e00

#define MBEDTLS_PKCS5_DECRYPT      0
#define MBEDTLS_PKCS5_ENCRYPT      1

#ifdef __cplusplus
extern "C" {
#endif

#if defined(MBEDTLS_ASN1_PARSE_C)

/**
 * \简短的PKCS#5 PBES2函数
 *
 * \param pbe_params ASN.1算法参数\param模式MBEDTLS_PKS5_DECRYPT或MBEDTLS_PKS5_ENCRYPT \param pwd生成密钥时使用的密码\param密码长度\param要处理的数据数据\param数据长度\pram输出缓冲区
 *
 * \成功时返回0，如果验证失败则返回MBEDTLS_ERROR_XXX代码。
 */
int mbedtls_pkcs5_pbes2( const mbedtls_asn1_buf *pbe_params, int mode,
                 const unsigned char *pwd,  size_t pwdlen,
                 const unsigned char *data, size_t datalen,
                 unsigned char *output );

#endif /* MBEDTLS_ASN1_PARSE_C */

/**
 * \使用HMAC的简短PKCS#5 PBKDF2
 *
 * \param ctx通用HMAC上下文\param password生成密钥时使用的密码\param plen密码长度\param salt生成密钥时要使用的盐\param slen盐长度/param iteration_count迭代计数\param key_Length生成密钥的长度（字节）\param output生成密钥。必须至少与key_length一样大
 *
 * \成功时返回0，如果验证失败则返回MBEDTLS_ERROR_XXX代码。
 */
int mbedtls_pkcs5_pbkdf2_hmac( mbedtls_md_context_t *ctx, const unsigned char *password,
                       size_t plen, const unsigned char *salt, size_t slen,
                       unsigned int iteration_count,
                       uint32_t key_length, unsigned char *output );

#if defined(MBEDTLS_SELF_TEST)

/**
 * \简要检查程序
 *
 * \如果成功，则返回0；如果测试失败，则返回1
 */
int mbedtls_pkcs5_self_test( int verbose );

#endif /* MBEDTLS_SELF_TEST */

#ifdef __cplusplus
}
#endif

#endif /* pkcs5.小时*/

