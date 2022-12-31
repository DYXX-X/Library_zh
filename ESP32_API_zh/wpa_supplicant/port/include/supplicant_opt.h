// 版权所有2019 Espressif Systems（上海）私人有限公司
//
// 根据Apache许可证2.0版（“许可证”）获得许可；
// 除非符合许可证，否则不得使用此文件。
// 您可以在以下地址获取许可证副本：

//     http://www.apache.org/licenses/LICENSE-2.0
//
// 除非适用法律要求或书面同意，软件
// 根据许可证分发的内容是按“原样”分发的，
// 无任何明示或暗示的保证或条件。
// 有关管理权限和
// 许可证下的限制。

#ifndef _SUPPLICANT_OPT_H
#define _SUPPLICANT_OPT_H

#include "sdkconfig.h"

#if CONFIG_WPA_MBEDTLS_CRYPTO
#define USE_MBEDTLS_CRYPTO 1
#else
#define CONFIG_TLS_INTERNAL_CLIENT
#define CONFIG_CRYPTO_INTERNAL
#define CONFIG_TLSV12
#endif

#if CONFIG_WPA_DEBUG_PRINT
#define DEBUG_PRINT
#endif

#if CONFIG_WPA_11KV_SUPPORT
#define ROAMING_SUPPORT 1
#endif

#if CONFIG_WPA_SCAN_CACHE
#define SCAN_CACHE_SUPPORTED
#endif

#endif /* _SUPPLICANT_OPT_H */

