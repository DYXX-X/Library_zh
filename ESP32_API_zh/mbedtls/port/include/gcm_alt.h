/**
 * \文件gcm_alt.h
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
#ifndef GCM_ALT_H
#define GCM_ALT_H

#include "soc/soc_caps.h"

#ifdef __cplusplus
extern "C" {
#endif

#if defined(MBEDTLS_GCM_ALT)

#if SOC_AES_SUPPORT_GCM
#include "aes/esp_aes_gcm.h"


typedef esp_gcm_context mbedtls_gcm_context;

#define mbedtls_gcm_init            esp_aes_gcm_init
#define mbedtls_gcm_free            esp_aes_gcm_free
#define mbedtls_gcm_setkey          esp_aes_gcm_setkey
#define mbedtls_gcm_starts          esp_aes_gcm_starts
#define mbedtls_gcm_update          esp_aes_gcm_update
#define mbedtls_gcm_finish          esp_aes_gcm_finish
#define mbedtls_gcm_auth_decrypt    esp_aes_gcm_auth_decrypt
#define mbedtls_gcm_crypt_and_tag   esp_aes_gcm_crypt_and_tag

#endif // SOC_AES_SUPPORT_GCM

#endif /* MBEDTLS_GCM_ALT */

#ifdef __cplusplus
}
#endif

#endif

