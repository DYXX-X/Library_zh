/** 执行PSA关键对象的代码，即验证它看起来格式良好，并且可以执行它应该执行的操作。
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

#ifndef PSA_EXERCISE_KEY_H
#define PSA_EXERCISE_KEY_H

#include "test/helpers.h"
#include "test/psa_crypto_helpers.h"

#include <psa/crypto.h>

/** \定义KNOWN_SUPPORTED_HASH_ALG
 *
 * 已知支持的哈希算法。
 *
 * 这在一些烟雾测试中使用。
 */
#if defined(PSA_WANT_ALG_MD2)
#define KNOWN_SUPPORTED_HASH_ALG PSA_ALG_MD2
#elif defined(PSA_WANT_ALG_MD4)
#define KNOWN_SUPPORTED_HASH_ALG PSA_ALG_MD4
#elif defined(PSA_WANT_ALG_MD5)
#define KNOWN_SUPPORTED_HASH_ALG PSA_ALG_MD5
/* MBEDTLS_RIPEMD160_C被省略。这对于exercise_signature_key（）是必要的，因为Mbed TLS在RSA PKCS#1v1.5签名中不支持RIPEMD160。仅RIPEMD160配置无论如何都不可信。*/
#elif defined(PSA_WANT_ALG_SHA_1)
#define KNOWN_SUPPORTED_HASH_ALG PSA_ALG_SHA_1
#elif defined(PSA_WANT_ALG_SHA_256)
#define KNOWN_SUPPORTED_HASH_ALG PSA_ALG_SHA_256
#elif defined(PSA_WANT_ALG_SHA_384)
#define KNOWN_SUPPORTED_HASH_ALG PSA_ALG_SHA_384
#elif defined(PSA_WANT_ALG_SHA_512)
#define KNOWN_SUPPORTED_HASH_ALG PSA_ALG_SHA_512
#elif defined(PSA_WANT_ALG_SHA3_256)
#define KNOWN_SUPPORTED_HASH_ALG PSA_ALG_SHA3_256
#else
#undef KNOWN_SUPPORTED_HASH_ALG
#endif

/** \定义KNOWN_MBEDTLS_SUPPORTED_HASH_ALG
 *
 * 已知Mbed TLS API支持的哈希算法。
 *
 * 这在一些烟雾测试中使用，其中哈希算法被用作另一种算法（如签名算法）的一部分，并且哈希是通过Mbed TLS哈希API而不是PSA API完成的。
 */
#if defined(MBEDTLS_MD2_C)
#define KNOWN_MBEDTLS_SUPPORTED_HASH_ALG PSA_ALG_MD2
#elif defined(MBEDTLS_MD4_C)
#define KNOWN_MBEDTLS_SUPPORTED_HASH_ALG PSA_ALG_MD4
#elif defined(MBEDTLS_MD5_C)
#define KNOWN_MBEDTLS_SUPPORTED_HASH_ALG PSA_ALG_MD5
/* MBEDTLS_RIPEMD160_C被省略。这对于exercise_signature_key（）是必要的，因为Mbed TLS在RSA PKCS#1v1.5签名中不支持RIPEMD160。仅RIPEMD160配置无论如何都不可信。*/
#elif defined(MBEDTLS_SHA1_C)
#define KNOWN_MBEDTLS_SUPPORTED_HASH_ALG PSA_ALG_SHA_1
#elif defined(MBEDTLS_SHA256_C)
#define KNOWN_MBEDTLS_SUPPORTED_HASH_ALG PSA_ALG_SHA_256
#elif defined(MBEDTLS_SHA512_C)
#define KNOWN_MBEDTLS_SUPPORTED_HASH_ALG PSA_ALG_SHA_512
#else
#undef KNOWN_MBEDLTS_SUPPORTED_HASH_ALG
#endif

/** \定义KNOWN_SUPPORTED_BLOCK_CIPHER
 *
 * 已知支持的分组密码。
 *
 * 为了简单起见，请使用16字节块的分组密码。
 */
#if defined(MBEDTLS_AES_C)
#define KNOWN_SUPPORTED_BLOCK_CIPHER PSA_KEY_TYPE_AES
#elif defined(MBEDTLS_ARIA_C)
#define KNOWN_SUPPORTED_BLOCK_CIPHER PSA_KEY_TYPE_ARIA
#elif defined(MBEDTLS_CAMELLIA_C)
#define KNOWN_SUPPORTED_BLOCK_CIPHER PSA_KEY_TYPE_CAMELLIA
#undef KNOWN_SUPPORTED_BLOCK_CIPHER
#endif

/** \定义KNOWN_SUPPORTED MAC_ALG
 *
 * 已知支持的MAC模式。
 *
 * 它必须是具有#KNOWN_SUPPORTED_HASH_ALG的HMAC或具有#KNON_SUPPORTED_block_cipher的基于分组密码的MAC。
 *
 * 这在一些烟雾测试中使用。
 */
#if defined(KNOWN_SUPPORTED_HASH_ALG) && defined(PSA_WANT_ALG_HMAC)
#define KNOWN_SUPPORTED_MAC_ALG ( PSA_ALG_HMAC( KNOWN_SUPPORTED_HASH_ALG ) )
#define KNOWN_SUPPORTED_MAC_KEY_TYPE PSA_KEY_TYPE_HMAC
#elif defined(KNOWN_SUPPORTED_BLOCK_CIPHER) && defined(MBEDTLS_CMAC_C)
#define KNOWN_SUPPORTED_MAC_ALG PSA_ALG_CMAC
#define KNOWN_SUPPORTED_MAC_KEY_TYPE KNOWN_SUPPORTED_BLOCK_CIPHER
#else
#undef KNOWN_SUPPORTED_MAC_ALG
#undef KNOWN_SUPPORTED_MAC_KEY_TYPE
#endif

/** \定义KNOWN_SUPPORTED_BLOCK_CIPHER_ALG
 *
 * 已知支持的密码算法和密钥类型。
 *
 * 这在一些烟雾测试中使用。
 */
#if defined(KNOWN_SUPPORTED_BLOCK_CIPHER) && defined(MBEDTLS_CIPHER_MODE_CTR)
#define KNOWN_SUPPORTED_BLOCK_CIPHER_ALG PSA_ALG_CTR
#elif defined(KNOWN_SUPPORTED_BLOCK_CIPHER) && defined(MBEDTLS_CIPHER_MODE_CBC)
#define KNOWN_SUPPORTED_BLOCK_CIPHER_ALG PSA_ALG_CBC_NO_PADDING
#elif defined(KNOWN_SUPPORTED_BLOCK_CIPHER) && defined(MBEDTLS_CIPHER_MODE_CFB)
#define KNOWN_SUPPORTED_BLOCK_CIPHER_ALG PSA_ALG_CFB
#elif defined(KNOWN_SUPPORTED_BLOCK_CIPHER) && defined(MBEDTLS_CIPHER_MODE_OFB)
#define KNOWN_SUPPORTED_BLOCK_CIPHER_ALG PSA_ALG_OFB
#else
#undef KNOWN_SUPPORTED_BLOCK_CIPHER_ALG
#endif
#if defined(KNOWN_SUPPORTED_BLOCK_CIPHER_ALG)
#define KNOWN_SUPPORTED_CIPHER_ALG KNOWN_SUPPORTED_BLOCK_CIPHER_ALG
#define KNOWN_SUPPORTED_CIPHER_KEY_TYPE KNOWN_SUPPORTED_BLOCK_CIPHER
#elif defined(MBEDTLS_RC4_C)
#define KNOWN_SUPPORTED_CIPHER_ALG PSA_ALG_RC4
#define KNOWN_SUPPORTED_CIPHER_KEY_TYPE PSA_KEY_TYPE_RC4
#else
#undef KNOWN_SUPPORTED_CIPHER_ALG
#undef KNOWN_SUPPORTED_CIPHER_KEY_TYPE
#endif

/** 设置密钥派生的便利功能。
 *
 * 如果失败，将当前测试用例标记为失败。
 *
 * 输入\p input1和\p input2依次为：
 * -HKDF：盐，信息。
 * -TKS 1.2 PRF，TLS 1.2 PSK至MS：种子，标签。
 *
 * \param operation要使用的操作对象。它必须处于初始化状态。\param key要使用的密钥。\param alg要使用的算法。\param input1要传递的第一个输入。\param input1_length \p input1的长度（以字节为单位）。\param input2要传递的第一个输入。\param input2_length \p input2的长度（以字节为单位）。\param capacity要设置的容量。
 *
 * \成功时返回\c1，失败时返回\c0。
 */
int mbedtls_test_psa_setup_key_derivation_wrap(
    psa_key_derivation_operation_t* operation,
    mbedtls_svc_key_id_t key,
    psa_algorithm_t alg,
    const unsigned char* input1, size_t input1_length,
    const unsigned char* input2, size_t input2_length,
    size_t capacity );

/** 使用给定的密钥对，使用psa\raw_key_agreement（）对其公钥执行密钥协议。
 *
 * 结果被丢弃。此功能的目的是对钥匙进行烟雾测试。
 *
 * 如果失败，将当前测试用例标记为失败。
 *
 * \param alg与\p密钥兼容的密钥协商算法。\param key允许密钥与\p alg一致的密钥。
 *
 * \成功时返回\c1，失败时返回\c0。
 */
psa_status_t mbedtls_test_psa_raw_key_agreement_with_self(
    psa_algorithm_t alg,
    mbedtls_svc_key_id_t key );

/** 使用给定密钥对，使用psa_key_derivation_raw_key（）对其公钥执行密钥协议。
 *
 * 结果被丢弃。此功能的目的是对钥匙进行烟雾测试。
 *
 * 如果失败，将当前测试用例标记为失败。
 *
 * \param操作为与\p密钥兼容的密钥协议算法设置的操作。\param key一个适用于与\p操作的密钥协议的密钥对对象。
 *
 * \成功时返回\c1，失败时返回\c0。
 */
psa_status_t mbedtls_test_psa_key_agreement_with_self(
    psa_key_derivation_operation_t *operation,
    mbedtls_svc_key_id_t key );

/** 对给定的密钥表示执行健全性检查。
 *
 * 如果任何检查失败，则将当前测试用例标记为失败。
 *
 * 检查取决于密钥类型。
 * -所有类型：对照最大大小宏检查导出大小。
 * -DES：奇偶校验位。
 * -RSA：检查ASN。1结构以及整数的大小和奇偶性。
 * -ECC私钥或公钥：精确的表示长度。
 * -蒙哥马利公钥：第一个字节。
 *
 * \param type键类型。\param bits以位为单位的密钥大小。\param exported包含密钥表示的缓冲区。\param exported_length导出的\p的长度（以字节为单位）。
 *
 * \如果所有检查都通过，则返回\c 1，失败时返回\c 0。
 */
int mbedtls_test_psa_exported_key_sanity_check(
    psa_key_type_t type, size_t bits,
    const uint8_t *exported, size_t exported_length );

/** 在钥匙上做烟雾测试。
 *
 * 根据用法，执行alg指示的每个操作之一（解密/加密、签名/验证或派生）。\p用法和\p alg应与密钥上的预期策略相对应。
 *
 * 如果用法允许，导出密钥，并检查输出是否合理。如果\p用法禁止导出，请检查\p psa_export_key是否正确拒绝该尝试。如果密钥不对称，请同时检查\p psa_export_public_key。
 *
 * 如果密钥未通过测试，该函数将调用测试框架的“mbedtls_test_fail”函数并返回false。否则，此函数返回true。因此，应按如下方式使用：``if（！exercise_key（…））goto exit```
 *
 * \param key锻炼的关键。它应该能够执行代数运算。\param usage要假定的用法标志。\param alg要执行的算法。
 *
 * \retval 0钥匙未通过烟雾测试。\retval 1钥匙通过了烟雾测试。
 */
int mbedtls_test_psa_exercise_key( mbedtls_svc_key_id_t key,
                                   psa_key_usage_t usage,
                                   psa_algorithm_t alg );

psa_key_usage_t mbedtls_test_psa_usage_to_exercise( psa_key_type_t type,
                                                    psa_algorithm_t alg );

#endif /* PSA_EXERCISE_KEY_H */

