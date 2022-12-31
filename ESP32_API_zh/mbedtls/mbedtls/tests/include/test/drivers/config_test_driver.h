/*
 * PSA测试驱动程序库的Mbed TLS配置。它包括：.PSA核心所需的最小模块集。出于特定测试的目的，可能需要额外启用的Mbed TLS配置选项。Mbed TLS库及其测试驱动程序的PSA配置文件。
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

#ifndef MBEDTLS_CONFIG_H
#define MBEDTLS_CONFIG_H

#if defined(_MSC_VER) && !defined(_CRT_SECURE_NO_DEPRECATE)
#define _CRT_SECURE_NO_DEPRECATE 1
#endif

#define MBEDTLS_PSA_CRYPTO_C
#define MBEDTLS_PSA_CRYPTO_CONFIG

/* PSA核心强制性配置选项*/
#define MBEDTLS_CIPHER_C
#define MBEDTLS_AES_C
#define MBEDTLS_SHA256_C
#define MBEDTLS_PSA_BUILTIN_ALG_SHA_256 1
#define MBEDTLS_CTR_DRBG_C
#define MBEDTLS_ENTROPY_C

/*
 * 可能需要为特定测试集的目的额外启用的配置选项。
 */
//#定义MBEDTLS_SHA1_C
//#定义MBEDTLS_SHA512_C
//#定义MBEDTLS_PEM_PARSE_C
//#定义MBEDTLS_BASE 64_C

#include "mbedtls/config_psa.h"
#include "mbedtls/check_config.h"

#endif /* MBEDTLS_CONFIG_H */

