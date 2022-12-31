/**
 * \文件aes_alt.h
 *
 * \简单AES分组密码
 *
 *  版权所有（C）2006-2015，ARM Limited，保留所有权利SPDX许可证标识符：Apache-2.0
 *
 *  根据Apache许可证2.0版（“许可证”）获得许可；除非符合许可证，否则不得使用此文件。您可以在以下地址获取许可证副本：
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 *  除非适用法律要求或书面同意，否则根据许可证分发的软件是按“原样”分发的，无任何明示或暗示的担保或条件。有关许可证下权限和限制的具体语言，请参阅许可证。
 *
 *
 */
#ifndef AES_ALT_H
#define AES_ALT_H

#ifdef __cplusplus
extern "C" {
#endif

#if defined(MBEDTLS_AES_ALT)
#include "aes/esp_aes.h"

typedef esp_aes_context mbedtls_aes_context;

#define mbedtls_aes_init            esp_aes_init
#define mbedtls_aes_free            esp_aes_free
#define mbedtls_aes_setkey_enc      esp_aes_setkey
#define mbedtls_aes_setkey_dec      esp_aes_setkey
#define mbedtls_aes_crypt_ecb       esp_aes_crypt_ecb
#if defined(MBEDTLS_CIPHER_MODE_CBC)
#define mbedtls_aes_crypt_cbc       esp_aes_crypt_cbc
#endif
#if defined(MBEDTLS_CIPHER_MODE_CFB)
#define mbedtls_aes_crypt_cfb128    esp_aes_crypt_cfb128
#define mbedtls_aes_crypt_cfb8      esp_aes_crypt_cfb8
#endif
#if defined(MBEDTLS_CIPHER_MODE_CTR)
#define mbedtls_aes_crypt_ctr       esp_aes_crypt_ctr
#endif
#if defined(MBEDTLS_CIPHER_MODE_OFB)
#define mbedtls_aes_crypt_ofb       esp_aes_crypt_ofb
#endif
#if defined(MBEDTLS_CIPHER_MODE_XTS)
typedef esp_aes_xts_context mbedtls_aes_xts_context;
#define mbedtls_aes_xts_init            esp_aes_xts_init
#define mbedtls_aes_xts_free            esp_aes_xts_free
#define mbedtls_aes_xts_setkey_enc      esp_aes_xts_setkey_enc
#define mbedtls_aes_xts_setkey_dec      esp_aes_xts_setkey_dec
#define mbedtls_aes_crypt_xts       esp_aes_crypt_xts
#endif
#define mbedtls_internal_aes_encrypt         esp_internal_aes_encrypt
#define mbedtls_internal_aes_decrypt         esp_internal_aes_decrypt
#endif /* MBEDTLS_AES_ALT */

#ifdef __cplusplus
}
#endif

#endif

