/**
 * \文件pkcs12.h
 *
 * \简短的PKCS#12个人信息交换语法
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
#ifndef MBEDTLS_PKCS12_H
#define MBEDTLS_PKCS12_H

#if !defined(MBEDTLS_CONFIG_FILE)
#include "mbedtls/config.h"
#else
#include MBEDTLS_CONFIG_FILE
#endif

#include "mbedtls/md.h"
#include "mbedtls/cipher.h"
#include "mbedtls/asn1.h"

#include <stddef.h>

#define MBEDTLS_ERR_PKCS12_BAD_INPUT_DATA                 -0x1F80  /**<功能输入参数错误。*/
#define MBEDTLS_ERR_PKCS12_FEATURE_UNAVAILABLE            -0x1F00  /**<功能不可用，例如不支持的加密方案。*/
#define MBEDTLS_ERR_PKCS12_PBE_INVALID_FORMAT             -0x1E80  /**<PBE ASN。1数据不符合预期。*/
#define MBEDTLS_ERR_PKCS12_PASSWORD_MISMATCH              -0x1E00  /**<给定的私钥密码不允许正确解密。*/

#define MBEDTLS_PKCS12_DERIVE_KEY       1   /**<加密/解密密钥*/
#define MBEDTLS_PKCS12_DERIVE_IV        2   /**<初始化向量*/
#define MBEDTLS_PKCS12_DERIVE_MAC_KEY   3   /**<完整性/MAC密钥*/

#define MBEDTLS_PKCS12_PBE_DECRYPT      0
#define MBEDTLS_PKCS12_PBE_ENCRYPT      1

#ifdef __cplusplus
extern "C" {
#endif

#if defined(MBEDTLS_ASN1_PARSE_C)

/**
 * \pbeWithSHAAnd128BitRC4的简短PKCS12基于密码的功能（加密/解密）
 *
 * \param pbe_params包含pkcs-12PbeParams结构的ASN1缓冲区\param模式MBEDTLS_PKCS12_pbe_ENCRYPT或MBEDTLS_PKCS12_pbe_DECRYPT \param pwd使用的密码（如果未使用密码，则可能为NULL）\param密码长度（可能为0）\param输入输入数据\param len数据长度\param输出缓冲区
 *
 * \如果成功，则返回0，或返回MBEDTLS_ERROR_XXX代码
 */
int mbedtls_pkcs12_pbe_sha1_rc4_128( mbedtls_asn1_buf *pbe_params, int mode,
                             const unsigned char *pwd,  size_t pwdlen,
                             const unsigned char *input, size_t len,
                             unsigned char *output );

/**
 * \基于密码和基于mbedtls_md的PBE的简短PKCS12基于密码的功能（加密/解密）
 *
 * \param pbe_params包含pkcs-12PbeParams结构的ASN1缓冲区\param模式MBEDTLS_PKCS12_pbe_ENCRYPT或MBEDTLS_PKCS12_BBE_DECRYPT \param cipher_type所用密码\param md_type所使用的MBEDTLS_md \param pwd所用密码（如果未使用密码，则可能为NULL）\param密码长度（可能为0）\param输入输入数据\param len数据长度\param输出输出缓冲器
 *
 * \如果成功，则返回0，或返回MBEDTLS_ERROR_XXX代码
 */
int mbedtls_pkcs12_pbe( mbedtls_asn1_buf *pbe_params, int mode,
                mbedtls_cipher_type_t cipher_type, mbedtls_md_type_t md_type,
                const unsigned char *pwd,  size_t pwdlen,
                const unsigned char *input, size_t len,
                unsigned char *output );

#endif /* MBEDTLS_ASN1_PARSE_C */

/**
 * \brief PKCS#12派生函数使用密码和salt生成用于特定“目的”的伪随机位。
 *
 *                   根据给定的id，此函数可以生成加密/解密密钥、初始化向量或完整性密钥。
 *
 * \param data buffer用于存储派生数据，其长度为\param datalen length to fill \param pwd password to use（如果未使用密码，则可能为NULL）\param密码的长度（可能为0）\pram salt salt buffer to use \param saltlen length of the salt \param mbedtls_md mbedtls-md type to use during the derivation \param id id which description the purpose（可以是MBEDTLS_PKCS12_DERIVE_KEY、MBEDTLS_PKCS12_DERIVE_IV或MBEDTLS_PKCS12DERIVE_MAC_KEY）\param迭代次数
 *
 * \如果成功，则返回0，或MD、BIGNUM类型错误。
 */
int mbedtls_pkcs12_derivation( unsigned char *data, size_t datalen,
                       const unsigned char *pwd, size_t pwdlen,
                       const unsigned char *salt, size_t saltlen,
                       mbedtls_md_type_t mbedtls_md, int id, int iterations );

#ifdef __cplusplus
}
#endif

#endif /* pkcs12.小时*/

