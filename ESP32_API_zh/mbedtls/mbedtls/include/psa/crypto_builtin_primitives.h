/*
 *  通过PSA Crypto驱动程序调度层调用的基于Mbed TLS软件的PSA驱动程序的上下文结构声明。该文件包含那些不依赖于其他算法的算法的上下文结构，即“原始”算法。
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

#ifndef PSA_CRYPTO_BUILTIN_PRIMITIVES_H
#define PSA_CRYPTO_BUILTIN_PRIMITIVES_H

#include <psa/crypto_driver_common.h>

/*
 * 哈希多部分操作定义。
 */

#include "mbedtls/md2.h"
#include "mbedtls/md4.h"
#include "mbedtls/md5.h"
#include "mbedtls/ripemd160.h"
#include "mbedtls/sha1.h"
#include "mbedtls/sha256.h"
#include "mbedtls/sha512.h"

#if defined(MBEDTLS_PSA_BUILTIN_ALG_MD2) || \
    defined(MBEDTLS_PSA_BUILTIN_ALG_MD4) || \
    defined(MBEDTLS_PSA_BUILTIN_ALG_MD5) || \
    defined(MBEDTLS_PSA_BUILTIN_ALG_RIPEMD160) || \
    defined(MBEDTLS_PSA_BUILTIN_ALG_SHA_1) || \
    defined(MBEDTLS_PSA_BUILTIN_ALG_SHA_224) || \
    defined(MBEDTLS_PSA_BUILTIN_ALG_SHA_256) || \
    defined(MBEDTLS_PSA_BUILTIN_ALG_SHA_384) || \
    defined(MBEDTLS_PSA_BUILTIN_ALG_SHA_512)
#define MBEDTLS_PSA_BUILTIN_HASH
#endif

typedef struct
{
    psa_algorithm_t alg;
    union
    {
        unsigned dummy; /* 即使没有支持的算法，也要使联合为非空。*/
#if defined(MBEDTLS_PSA_BUILTIN_ALG_MD2)
        mbedtls_md2_context md2;
#endif
#if defined(MBEDTLS_PSA_BUILTIN_ALG_MD4)
        mbedtls_md4_context md4;
#endif
#if defined(MBEDTLS_PSA_BUILTIN_ALG_MD5)
        mbedtls_md5_context md5;
#endif
#if defined(MBEDTLS_PSA_BUILTIN_ALG_RIPEMD160)
        mbedtls_ripemd160_context ripemd160;
#endif
#if defined(MBEDTLS_PSA_BUILTIN_ALG_SHA_1)
        mbedtls_sha1_context sha1;
#endif
#if defined(MBEDTLS_PSA_BUILTIN_ALG_SHA_256) || \
    defined(MBEDTLS_PSA_BUILTIN_ALG_SHA_224)
        mbedtls_sha256_context sha256;
#endif
#if defined(MBEDTLS_PSA_BUILTIN_ALG_SHA_512) || \
    defined(MBEDTLS_PSA_BUILTIN_ALG_SHA_384)
        mbedtls_sha512_context sha512;
#endif
    } ctx;
} mbedtls_psa_hash_operation_t;

#define MBEDTLS_PSA_HASH_OPERATION_INIT {0, {0}}

/*
 * 密码多部分操作定义。
 */

#include "mbedtls/cipher.h"

#if defined(MBEDTLS_PSA_BUILTIN_ALG_STREAM_CIPHER) || \
    defined(MBEDTLS_PSA_BUILTIN_ALG_CTR) || \
    defined(MBEDTLS_PSA_BUILTIN_ALG_CFB) || \
    defined(MBEDTLS_PSA_BUILTIN_ALG_OFB) || \
    defined(MBEDTLS_PSA_BUILTIN_ALG_XTS) || \
    defined(MBEDTLS_PSA_BUILTIN_ALG_ECB_NO_PADDING) || \
    defined(MBEDTLS_PSA_BUILTIN_ALG_CBC_NO_PADDING) || \
    defined(MBEDTLS_PSA_BUILTIN_ALG_CBC_PKCS7)
#define MBEDTLS_PSA_BUILTIN_CIPHER  1
#endif

typedef struct {
    /* Mbed TLS密码实现的上下文结构。*/
    psa_algorithm_t alg;
    uint8_t iv_length;
    uint8_t block_length;
    union {
        unsigned int dummy;
        mbedtls_cipher_context_t cipher;
    } ctx;
} mbedtls_psa_cipher_operation_t;

#define MBEDTLS_PSA_CIPHER_OPERATION_INIT {0, 0, 0, {0}}

#endif /* PSA_CRYPTO_BUILTIN_PRIMITIVES_H */

