/**
 * \文件md5_alt.h
 *
 * \简单的MD5分组密码
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
#ifndef MD5_ALT_H
#define MD5_ALT_H

#ifdef __cplusplus
extern "C" {
#endif

#if defined(MBEDTLS_MD5_ALT)
#include "md/esp_md.h"

#define mbedtls_md5_init                        esp_md5_init
#define mbedtls_md5_update                      esp_md5_update
#define mbedtls_md5_finish                      esp_md5_finish
#define mbedtls_md5_starts_ret                  esp_md5_init_ret
#define mbedtls_md5_update_ret                  esp_md5_update_ret
#define mbedtls_md5_finish_ret                  esp_md5_finish_ret

#define mbedtls_md5_free                        esp_md5_free
#define mbedtls_md5_clone                       esp_md5_clone
#define mbedtls_internal_md5_process            esp_md5_process

#endif /* MBEDTLS_MD5_ALT */

#ifdef __cplusplus
}
#endif

#endif

