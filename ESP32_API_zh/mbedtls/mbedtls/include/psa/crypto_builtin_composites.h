/*
 *  通过PSA Crypto驱动程序调度层调用的基于Mbed TLS软件的PSA驱动程序的上下文结构声明。该文件包含需要依赖于其他算法的算法的上下文结构，即“复合”算法。
 *
 * \注意：此文件可能不直接包含。应用程序必须包括psa/crypto.h。
 *
 * \注意：此标头及其内容不是Mbed TLS API的一部分，应用程序不能依赖它。其主要目的是定义基于Mbed TLS软件的PSA驱动程序的多部分状态对象。crypt_struct使用这些对象的定义。h定义PSA多部件状态对象的实现定义类型。
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

#ifndef PSA_CRYPTO_BUILTIN_COMPOSITES_H
#define PSA_CRYPTO_BUILTIN_COMPOSITES_H

#include <psa/crypto_driver_common.h>

/*
 * MAC多部分操作定义。
 */
#if defined(MBEDTLS_PSA_BUILTIN_ALG_CMAC) || \
    defined(MBEDTLS_PSA_BUILTIN_ALG_HMAC)
#define MBEDTLS_PSA_BUILTIN_MAC
#endif

#if defined(MBEDTLS_PSA_BUILTIN_ALG_HMAC) || defined(PSA_CRYPTO_DRIVER_TEST)
typedef struct
{
    /**正在使用的HMAC算法*/
    psa_algorithm_t alg;
    /**哈希上下文。*/
    struct psa_hash_operation_s hash_ctx;
    /**上下文的HMAC部分。*/
    uint8_t opad[PSA_HMAC_MAX_HASH_BLOCK_SIZE];
} mbedtls_psa_hmac_operation_t;

#define MBEDTLS_PSA_HMAC_OPERATION_INIT {0, PSA_HASH_OPERATION_INIT, {0}}
#endif /* MBEDTLS_PSA_BUILTIN_ALG_HMAC */

#include "mbedtls/cmac.h"

typedef struct
{
    psa_algorithm_t alg;
    union
    {
        unsigned dummy; /* 即使没有支持的算法，也要使联合为非空。*/
#if defined(MBEDTLS_PSA_BUILTIN_ALG_HMAC) || defined(PSA_CRYPTO_DRIVER_TEST)
        mbedtls_psa_hmac_operation_t hmac;
#endif /* MBEDTLS_PSA_BUILTIN_ALG_HMAC */
#if defined(MBEDTLS_PSA_BUILTIN_ALG_CMAC) || defined(PSA_CRYPTO_DRIVER_TEST)
        mbedtls_cipher_context_t cmac;
#endif /* MBEDTLS_PSA_BUILTIN_ALG_CMAC */
    } ctx;
} mbedtls_psa_mac_operation_t;

#define MBEDTLS_PSA_MAC_OPERATION_INIT {0, {0}}

#endif /* PSA_CRYPTO_BUILTIN_COMPOSITES_H */

