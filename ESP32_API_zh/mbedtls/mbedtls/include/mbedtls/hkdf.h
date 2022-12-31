/**
 * \文件hkdf.h
 *
 * \brief此文件包含HKDF接口。
 *
 *          RFC 5869规定了基于HMAC的提取和扩展密钥派生函数（HKDF）。
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
#ifndef MBEDTLS_HKDF_H
#define MBEDTLS_HKDF_H

#if !defined(MBEDTLS_CONFIG_FILE)
#include "mbedtls/config.h"
#else
#include MBEDTLS_CONFIG_FILE
#endif

#include "mbedtls/md.h"

/**
 *  \名称HKDF错误代码\{
 */
/**函数的输入参数错误。*/
#define MBEDTLS_ERR_HKDF_BAD_INPUT_DATA  -0x5F80
/* \}名称*/

#ifdef __cplusplus
extern "C" {
#endif

/**
 *  \这是基于HMAC的提取和扩展密钥派生函数（HKDF）。
 *
 *  \param md哈希函数；md.size表示哈希函数输出的长度（以字节为单位）。\param salt可选的salt值（非秘密随机值）；如果没有提供salt，则使用md.size长度的全零字符串作为salt。\param salt_len可选盐的长度（以字节为单位）。\param ikm输入键控材料。\param ikm_len \n ikm的长度（以字节为单位）。\param info可选的上下文和特定于应用程序的信息字符串。这可以是零长度字符串。\param info_len信息的长度（以字节为单位）。\param okm okm_len字节的输出密钥材料。\param okm_len输出密钥材料的长度（以字节为单位）。这必须小于或等于255 md.size字节。
 *
 *  \成功时返回0。\当参数无效时，返回#MBEDTLS_ERROR_HKDF_BAD_INPUT_DATA。\return从基础MD层返回的错误的MBEDTLS_error_MD_错误。
 */
int mbedtls_hkdf( const mbedtls_md_info_t *md, const unsigned char *salt,
                  size_t salt_len, const unsigned char *ikm, size_t ikm_len,
                  const unsigned char *info, size_t info_len,
                  unsigned char *okm, size_t okm_len );

/**
 *  \brief获取输入密钥材料，并从中提取一个固定长度的伪随机密钥。
 *
 *  \警告只有在特定环境中研究并建立了该功能的安全性（例如TLS 1.3密钥计划）时，才能使用该功能。对于标准HKDF安全保证，请改用\c mbedtls_HKDF。
 *
 *  \param md哈希函数；md.size表示哈希函数输出的长度（以字节为单位）。\param salt可选的salt值（非秘密随机值）；如果没有提供salt，则使用md.size长度的全零字符串作为salt。\param salt_len可选盐的长度（以字节为单位）。\param ikm输入键控材料。\param ikm_len \n ikm的长度（以字节为单位）。\param[out]prk至少为md.size字节的伪随机密钥。
 *
 *  \成功时返回0。\当参数无效时，返回#MBEDTLS_ERROR_HKDF_BAD_INPUT_DATA。\return从基础MD层返回的错误的MBEDTLS_error_MD_错误。
 */
int mbedtls_hkdf_extract( const mbedtls_md_info_t *md,
                          const unsigned char *salt, size_t salt_len,
                          const unsigned char *ikm, size_t ikm_len,
                          unsigned char *prk );

/**
 *  \brief将提供的prk扩展为几个附加伪随机密钥，这是HKDF的输出。
 *
 *  \警告只有在特定环境中研究并建立了该功能的安全性（例如TLS 1.3密钥计划）时，才能使用该功能。对于标准HKDF安全保证，请改用\c mbedtls_HKDF。
 *
 *  \param md哈希函数；md.size表示哈希函数输出的长度（以字节为单位）。\param prk至少为md.size字节的伪随机密钥。\p prk通常是HKDF提取步骤的输出。\param prk_len \p prk的长度（以字节为单位）。\param info可选的上下文和特定于应用程序的信息字符串。这可以是零长度字符串。\param info_len信息的长度（以字节为单位）。\param okm okm_len字节的输出密钥材料。\param okm_len输出密钥材料的长度（以字节为单位）。这必须小于或等于255 md.size字节。
 *
 *  \成功时返回0。\当参数无效时，返回#MBEDTLS_ERROR_HKDF_BAD_INPUT_DATA。\return从基础MD层返回的错误的MBEDTLS_error_MD_错误。
 */
int mbedtls_hkdf_expand( const mbedtls_md_info_t *md, const unsigned char *prk,
                         size_t prk_len, const unsigned char *info,
                         size_t info_len, unsigned char *okm, size_t okm_len );

#ifdef __cplusplus
}
#endif

#endif /* 香港会计师事务所*/

