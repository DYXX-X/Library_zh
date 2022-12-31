/**
 * \文件psa/crypto_sizes.h
 *
 * \简短的PSA加密模块：Mbed TLS缓冲区大小宏
 *
 * \注意：此文件可能不直接包含。应用程序必须包括psa/crypto.h。
 *
 * 此文件包含用于计算缓冲区大小的宏的定义。这些宏的签名和语义是标准化的，但定义不是，因为它们取决于可用的算法，在某些情况下，取决于缓冲区大小的允许公差。
 *
 * 在应用程序和加密模块之间具有隔离的实现中，实现者应注意确保向应用程序公开的定义与模块实现的内容相匹配。
 *
 * 计算其值不依赖于实现的大小的宏是crypto.h。
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

#ifndef PSA_CRYPTO_SIZES_H
#define PSA_CRYPTO_SIZES_H

/* 包括Mbed TLS配置文件，即Mbed TLS在其每个头文件中执行的方式。*/
#if !defined(MBEDTLS_CONFIG_FILE)
#include "mbedtls/config.h"
#else
#include MBEDTLS_CONFIG_FILE
#endif

#define PSA_BITS_TO_BYTES(bits) (((bits) + 7) / 8)
#define PSA_BYTES_TO_BITS(bytes) ((bytes) * 8)

#define PSA_ROUND_UP_TO_MULTIPLE(block_size, length) \
    (((length) + (block_size) - 1) / (block_size) * (block_size))

/** psa_hash_finish（）输出的大小，以字节为单位。
 *
 * 这也是psa_hash_verify（）期望的哈希大小。
 *
 * \param alg哈希算法（\c PSA_alg_XXX值，使得#PSA_alg_IS_hash（\p alg）为真）或HMAC算法（#PSA_LG_HMAC（\c hash_alg），其中\c hash_alg是哈希算法）。
 *
 * \return指定哈希算法的哈希大小。如果无法识别哈希算法，则返回0。
 */
#define PSA_HASH_LENGTH(alg)                                        \
    (                                                               \
        PSA_ALG_HMAC_GET_HASH(alg) == PSA_ALG_MD2 ? 16 :            \
        PSA_ALG_HMAC_GET_HASH(alg) == PSA_ALG_MD4 ? 16 :            \
        PSA_ALG_HMAC_GET_HASH(alg) == PSA_ALG_MD5 ? 16 :            \
        PSA_ALG_HMAC_GET_HASH(alg) == PSA_ALG_RIPEMD160 ? 20 :      \
        PSA_ALG_HMAC_GET_HASH(alg) == PSA_ALG_SHA_1 ? 20 :          \
        PSA_ALG_HMAC_GET_HASH(alg) == PSA_ALG_SHA_224 ? 28 :        \
        PSA_ALG_HMAC_GET_HASH(alg) == PSA_ALG_SHA_256 ? 32 :        \
        PSA_ALG_HMAC_GET_HASH(alg) == PSA_ALG_SHA_384 ? 48 :        \
        PSA_ALG_HMAC_GET_HASH(alg) == PSA_ALG_SHA_512 ? 64 :        \
        PSA_ALG_HMAC_GET_HASH(alg) == PSA_ALG_SHA_512_224 ? 28 :    \
        PSA_ALG_HMAC_GET_HASH(alg) == PSA_ALG_SHA_512_256 ? 32 :    \
        PSA_ALG_HMAC_GET_HASH(alg) == PSA_ALG_SHA3_224 ? 28 :       \
        PSA_ALG_HMAC_GET_HASH(alg) == PSA_ALG_SHA3_256 ? 32 :       \
        PSA_ALG_HMAC_GET_HASH(alg) == PSA_ALG_SHA3_384 ? 48 :       \
        PSA_ALG_HMAC_GET_HASH(alg) == PSA_ALG_SHA3_512 ? 64 :       \
        0)

/** 哈希算法的输入块大小，以字节为单位。
 *
 * 哈希算法以块为单位处理其输入数据。哈希操作将保留所有部分块，直到它们有足够的输入来填充该块或直到操作完成。这会影响psa_hash_suspend（）的输出。
 *
 * \param alg哈希算法（\c PSA_alg_XXX值，使得PSA_alg_IS_hash（\p alg）为真）。
 *
 * \return指定哈希算法的块大小（字节）。如果无法识别哈希算法，则返回0。实现可以返回0或其识别但不支持的哈希算法的正确大小。
 */
#define PSA_HASH_BLOCK_LENGTH(alg)                                  \
    (                                                               \
        PSA_ALG_HMAC_GET_HASH(alg) == PSA_ALG_MD2 ? 16 :            \
        PSA_ALG_HMAC_GET_HASH(alg) == PSA_ALG_MD4 ? 64 :            \
        PSA_ALG_HMAC_GET_HASH(alg) == PSA_ALG_MD5 ? 64 :            \
        PSA_ALG_HMAC_GET_HASH(alg) == PSA_ALG_RIPEMD160 ? 64 :      \
        PSA_ALG_HMAC_GET_HASH(alg) == PSA_ALG_SHA_1 ? 64 :          \
        PSA_ALG_HMAC_GET_HASH(alg) == PSA_ALG_SHA_224 ? 64 :        \
        PSA_ALG_HMAC_GET_HASH(alg) == PSA_ALG_SHA_256 ? 64 :        \
        PSA_ALG_HMAC_GET_HASH(alg) == PSA_ALG_SHA_384 ? 128 :       \
        PSA_ALG_HMAC_GET_HASH(alg) == PSA_ALG_SHA_512 ? 128 :       \
        PSA_ALG_HMAC_GET_HASH(alg) == PSA_ALG_SHA_512_224 ? 128 :   \
        PSA_ALG_HMAC_GET_HASH(alg) == PSA_ALG_SHA_512_256 ? 128 :   \
        PSA_ALG_HMAC_GET_HASH(alg) == PSA_ALG_SHA3_224 ? 144 :      \
        PSA_ALG_HMAC_GET_HASH(alg) == PSA_ALG_SHA3_256 ? 136 :      \
        PSA_ALG_HMAC_GET_HASH(alg) == PSA_ALG_SHA3_384 ? 104 :      \
        PSA_ALG_HMAC_GET_HASH(alg) == PSA_ALG_SHA3_512 ? 72 :       \
        0)

/** \定义PSA_HAH_MAX_SIZE
 *
 * 哈希的最大大小。
 *
 * 此宏扩展为编译时常量整数。此值是哈希的最大大小（以字节为单位）。
 */
/* 注：对于HMAC-SHA-3，HMAC-SHA3-226的块大小为144字节，HMAC-SHA3-256为136字节，SHA3-384为104字节，HMAC SHA3-512为72字节。*/
#if defined(PSA_WANT_ALG_SHA_512) || defined(PSA_WANT_ALG_SHA_384)
#define PSA_HASH_MAX_SIZE 64
#define PSA_HMAC_MAX_HASH_BLOCK_SIZE 128
#else
#define PSA_HASH_MAX_SIZE 32
#define PSA_HMAC_MAX_HASH_BLOCK_SIZE 64
#endif

/** \定义PSA_MAC_MAX_SIZE
 *
 * MAC的最大大小。
 *
 * 此宏扩展为编译时常量整数。此值是MAC的最大大小（以字节为单位）。
 */
/* 在此实现中，所有非HMAC MAC的最大大小都小于PSA_HAH_MAX_size的最小可能值。*/
/* 注意，截断MAC算法的编码将此值限制为64字节。
 */
#define PSA_MAC_MAX_SIZE PSA_HASH_MAX_SIZE

/** AEAD算法的标记长度，以字节为单位。
 *
 * 此宏可用于分配足够大小的缓冲区，以存储psa_aead_finish（）中的标记输出。
 *
 * 另请参见#PSA_EAD_TAG_MAX_SIZE。
 *
 * \param key_type AEAD密钥的类型。\param key_bits AEAD密钥的大小（以位为单位）。\param alg AEAD算法（\c PSA_alg_XXX值，使得#PSA_alg_IS_AEAD（\p alg）为真）。
 *
 * \return指定算法和密钥的标记长度。如果AEAD算法没有可与其他密文区分的已识别标记，则返回0。如果无法识别密钥类型或AEAD算法，或参数不兼容，则返回1。
 */
#define PSA_AEAD_TAG_LENGTH(key_type, key_bits, alg)                        \
    (PSA_AEAD_NONCE_LENGTH(key_type, alg) != 0 ?                            \
     PSA_ALG_AEAD_GET_TAG_LENGTH(alg) :                                     \
     ((void) (key_bits), 0))

/** 所有支持的AEAD算法的最大标记大小（字节）。
 *
 * 另请参见#PSA_EAD_TAG_LENGTH（\p key_type，\p key_bits，\p alg）。
 */
#define PSA_AEAD_TAG_MAX_SIZE       16

/* 此实现中RSA密钥的最大大小（以位为单位）。这是一个特定于供应商的宏。
 *
 * Mbed TLS对RSA密钥的大小没有硬性限制：任何参数符合bignum的密钥都可以接受。然而，大的键会导致大的内存使用和长的计算时间。与此文件和crypto.h中反映库配置方式的其他辅助宏不同，此宏定义了库的配置方式。此实现拒绝导入或生成大小大于此处定义的值的RSA密钥。
 *
 * 请注意，一个实现可以为不同的操作设置不同的大小限制，并且不需要接受该限制内的所有密钥大小。*/
#define PSA_VENDOR_RSA_MAX_KEY_BITS 4096

/* 此实现中ECC密钥的最大大小，以位为单位。这是一个特定于供应商的宏。*/
#if defined(MBEDTLS_ECP_DP_SECP521R1_ENABLED)
#define PSA_VENDOR_ECC_MAX_CURVE_BITS 521
#elif defined(MBEDTLS_ECP_DP_BP512R1_ENABLED)
#define PSA_VENDOR_ECC_MAX_CURVE_BITS 512
#elif defined(MBEDTLS_ECP_DP_CURVE448_ENABLED)
#define PSA_VENDOR_ECC_MAX_CURVE_BITS 448
#elif defined(MBEDTLS_ECP_DP_SECP384R1_ENABLED)
#define PSA_VENDOR_ECC_MAX_CURVE_BITS 384
#elif defined(MBEDTLS_ECP_DP_BP384R1_ENABLED)
#define PSA_VENDOR_ECC_MAX_CURVE_BITS 384
#elif defined(MBEDTLS_ECP_DP_SECP256R1_ENABLED)
#define PSA_VENDOR_ECC_MAX_CURVE_BITS 256
#elif defined(MBEDTLS_ECP_DP_SECP256K1_ENABLED)
#define PSA_VENDOR_ECC_MAX_CURVE_BITS 256
#elif defined(MBEDTLS_ECP_DP_BP256R1_ENABLED)
#define PSA_VENDOR_ECC_MAX_CURVE_BITS 256
#elif defined(MBEDTLS_ECP_DP_CURVE25519_ENABLED)
#define PSA_VENDOR_ECC_MAX_CURVE_BITS 255
#elif defined(MBEDTLS_ECP_DP_SECP224R1_ENABLED)
#define PSA_VENDOR_ECC_MAX_CURVE_BITS 224
#elif defined(MBEDTLS_ECP_DP_SECP224K1_ENABLED)
#define PSA_VENDOR_ECC_MAX_CURVE_BITS 224
#elif defined(MBEDTLS_ECP_DP_SECP192R1_ENABLED)
#define PSA_VENDOR_ECC_MAX_CURVE_BITS 192
#elif defined(MBEDTLS_ECP_DP_SECP192K1_ENABLED)
#define PSA_VENDOR_ECC_MAX_CURVE_BITS 192
#else
#define PSA_VENDOR_ECC_MAX_CURVE_BITS 0
#endif

/** 此宏返回TLS-1.2 PSK到MS密钥派生的PSK支持的最大长度（#PSA_ALG_TLS12_PSK_to_MS（\c hash_ALG））。
 *
 * 支持的最大长度不取决于所选的哈希算法。
 *
 * 引用RFC 4279第5.3节：支持这些密码套件的TLS实现必须支持长度高达128个八位字节的任意PSK标识，以及长度高达64个八位比特的任意PSKs。建议支持更长的身份和密钥。
 *
 * 因此，任何实现都不应为#PSA_TLS12_PSK_TO_MS_PSK_MAX_SIZE定义小于64的值。
 */
#define PSA_TLS12_PSK_TO_MS_PSK_MAX_SIZE 128

/**分组密码的最大大小。*/
#define PSA_BLOCK_CIPHER_BLOCK_MAX_SIZE 16

/** psa_mac_sign_finish（）输出的大小，以字节为单位。
 *
 * 这也是psa_MAC_verify_finish（）期望的MAC大小。
 *
 * \警告此宏可能会多次或零次计算其参数，因此不应传递包含副作用的参数。
 *
 * \param key_type MAC密钥的类型。\param key_bits MAC密钥的大小（以位为单位）。\param alg MAC算法（\c PSA_alg_XXX值使得#PSA_alg_IS_MAC（\p alg）为真）。
 *
 * \return具有指定密钥参数的指定算法的MAC大小。\如果MAC算法未被识别，则返回0。\return 0或实现识别但不支持的MAC算法的正确大小。\如果密钥参数与算法不一致，则返回未指定。
 */
#define PSA_MAC_LENGTH(key_type, key_bits, alg)                                   \
    ((alg) & PSA_ALG_MAC_TRUNCATION_MASK ? PSA_MAC_TRUNCATED_LENGTH(alg) :        \
     PSA_ALG_IS_HMAC(alg) ? PSA_HASH_LENGTH(PSA_ALG_HMAC_GET_HASH(alg)) :         \
     PSA_ALG_IS_BLOCK_CIPHER_MAC(alg) ? PSA_BLOCK_CIPHER_BLOCK_LENGTH(key_type) : \
     ((void)(key_type), (void)(key_bits), 0))

/** psa_aead_encrypt（）输出的最大大小，以字节为单位。
 *
 * 如果密文缓冲区的大小至少如此大，则可以保证psa_aead_encrypt（）不会因缓冲区大小不足而失败。根据算法，密文的实际大小可能更小。
 *
 * 另请参阅#PSA_EAD_ENCRYPT_OUTPUT_MAX_SIZE（\p明文长度）。
 *
 * \警告此宏可能会多次或零次计算其参数，因此不应传递包含副作用的参数。
 *
 * \param key_type与算法\p alg兼容的对称密钥类型。\param alg AEAD算法（\c PSA_alg_XXX值，使得#PSA_alg_IS_AEAD（\p alg）为真）。\param plaintext_length明文的大小（字节）。
 *
 * \return指定算法的AEAD密文大小。如果无法识别密钥类型或AEAD算法，或者参数不兼容，则返回0。
 */
#define PSA_AEAD_ENCRYPT_OUTPUT_SIZE(key_type, alg, plaintext_length) \
    (PSA_AEAD_NONCE_LENGTH(key_type, alg) != 0 ?                      \
     (plaintext_length) + PSA_ALG_AEAD_GET_TAG_LENGTH(alg) :          \
     0)

/** 对于任何支持的密钥类型和aead算法，psa_aeaad_encrypt（）的输出缓冲区大小足够。
 *
 * 如果密文缓冲区的大小至少如此大，则可以保证psa_aead_encrypt（）不会因缓冲区大小不足而失败。
 *
 * \注意：如果该宏的参数是编译时常数，则该宏返回编译时常数。
 *
 * 另请参见#PSA_EAD_ENCRYPT_OUTPUT_SIZE（\p key_type，\p alg，\p明文_length）。
 *
 * \param plaintext_length明文的大小（字节）。
 *
 * \为任何支持的密钥类型和AEAD算法返回足够的输出缓冲区大小。
 *
 */
#define PSA_AEAD_ENCRYPT_OUTPUT_MAX_SIZE(plaintext_length)          \
    ((plaintext_length) + PSA_AEAD_TAG_MAX_SIZE)


/** psa_aeaad_decrypt（）输出的最大大小，以字节为单位。
 *
 * 如果明文缓冲区的大小至少如此大，则可以保证psa_aead_decrypt（）不会因缓冲区大小不足而失败。根据算法，明文的实际大小可能更小。
 *
 * 另请参阅#PSA_EAD_DECRYPT_OUTPUT_MAX_SIZE（\p密文长度）。
 *
 * \警告此宏可能会多次或零次计算其参数，因此不应传递包含副作用的参数。
 *
 * \param key_type与算法\p alg兼容的对称密钥类型。\param alg AEAD算法（\c PSA_alg_XXX值，使得#PSA_alg_IS_AEAD（\p alg）为真）。\param ciphertext_length明文的大小（字节）。
 *
 * \return指定算法的AEAD密文大小。如果无法识别密钥类型或AEAD算法，或者参数不兼容，则返回0。
 */
#define PSA_AEAD_DECRYPT_OUTPUT_SIZE(key_type, alg, ciphertext_length) \
    (PSA_AEAD_NONCE_LENGTH(key_type, alg) != 0 &&                      \
         (ciphertext_length) > PSA_ALG_AEAD_GET_TAG_LENGTH(alg) ?      \
         (ciphertext_length) - PSA_ALG_AEAD_GET_TAG_LENGTH(alg) :      \
     0)

/** 对于任何支持的密钥类型和aead算法，psa_aeaad_decrypt（）的足够输出缓冲区大小。
 *
 * 如果明文缓冲区的大小至少如此大，则可以保证psa_aead_decrypt（）不会因缓冲区大小不足而失败。
 *
 * \注意：如果该宏的参数是编译时常数，则该宏返回编译时常数。
 *
 * 另请参阅#PSA_EAD_DECRYPT_OUTPUT_SIZE（\p key_type，\p alg，\p密文_length）。
 *
 * \param ciphertext_length密文的大小（字节）。
 *
 * \为任何支持的密钥类型和AEAD算法返回足够的输出缓冲区大小。
 *
 */
#define PSA_AEAD_DECRYPT_OUTPUT_MAX_SIZE(ciphertext_length)     \
     (ciphertext_length)

/** AEAD算法的默认随机数大小，以字节为单位。
 *
 * 此宏可用于分配足够大小的缓冲区，以存储#psa_aead_generate_nnonce（）的nonce输出。
 *
 * 另请参见#PSA_EAD_NONCE_MAX_SIZE。
 *
 * \注意：这不是#psa_aead_set_nnonce（）、#psa\uaead_encrypt（）或#psa_ead_decrypt（）的输入所支持的nonce的最大大小，只是#psa\aead_generate_nonce（）生成的默认大小。
 *
 * \警告此宏可能会多次或零次计算其参数，因此不应传递包含副作用的参数。
 *
 * \param key_type与算法\p alg兼容的对称密钥类型。
 *
 * \param alg AEAD算法（\c PSA_alg_XXX值，使得#PSA_alg_IS_AEAD（\p alg）为真）。
 *
 * \return指定密钥类型和算法的默认随机数大小。如果无法识别密钥类型或AEAD算法，或者参数不兼容，则返回0。
 */
#define PSA_AEAD_NONCE_LENGTH(key_type, alg) \
    (PSA_BLOCK_CIPHER_BLOCK_LENGTH(key_type) == 16 ? \
          MBEDTLS_PSA_ALG_AEAD_EQUAL(alg, PSA_ALG_CCM) ? 13 : \
          MBEDTLS_PSA_ALG_AEAD_EQUAL(alg, PSA_ALG_GCM) ? 12 : \
          0 : \
     (key_type) == PSA_KEY_TYPE_CHACHA20 && \
          MBEDTLS_PSA_ALG_AEAD_EQUAL(alg, PSA_ALG_CHACHA20_POLY1305) ? 12 : \
     0)

/** 所有支持的密钥类型对和AEAD算法中的最大默认随机数大小（以字节为单位）。
 *
 * 这等于或大于#PSA_EAD_NONCE_LENGTH（）可能返回的任何值。
 *
 * \注意：这不是#psa_aead_set_nnonce（）、#psa\uaead_encrypt（）或#psa_ead_decrypt（）的输入所支持的nonce的最大大小，只是#psa\aead_generate_nnonce）可能生成的最大大小。
 */
#define PSA_AEAD_NONCE_MAX_SIZE 13

/** psa_aead_update（）的输出缓冲区大小足够。
 *
 * 如果输出缓冲区的大小至少如此大，则可以保证psa_aead_update（）不会因缓冲区大小不足而失败。在任何给定的调用中，输出的实际大小都可能更小。
 *
 * 另请参阅#PSA_EAD_UPDATE_OUTPUT_MAX_SIZE（\p input_length）。
 *
 * \警告此宏可能会多次或零次计算其参数，因此不应传递包含副作用的参数。
 *
 * \param key_type与算法\p alg兼容的对称密钥类型。\param alg AEAD算法（\c PSA_alg_XXX值，使得#PSA_alg_IS_AEAD（\p alg）为真）。\param input_length输入的大小（字节）。
 *
 * \返回指定算法的足够输出缓冲区大小。如果无法识别密钥类型或AEAD算法，或者参数不兼容，则返回0。
 */
/* 对于本规范中定义的所有AEAD模式，可以无延迟地发出输出。然而，硬件可能并不总是能够做到这一点。因此，对于基于块密码的模式，允许实现延迟输出，直到它具有完整的块。*/
#define PSA_AEAD_UPDATE_OUTPUT_SIZE(key_type, alg, input_length)                             \
    (PSA_AEAD_NONCE_LENGTH(key_type, alg) != 0 ?                                             \
         PSA_ALG_IS_AEAD_ON_BLOCK_CIPHER(alg) ?                                              \
         PSA_ROUND_UP_TO_MULTIPLE(PSA_BLOCK_CIPHER_BLOCK_LENGTH(key_type), (input_length)) : \
         (input_length) : \
     0)

/** 对于任何支持的密钥类型和aead算法，psa_aeaad_update（）的输出缓冲区大小足够。
 *
 * 如果输出缓冲区的大小至少如此大，则可以保证psa_aead_update（）不会因缓冲区大小不足而失败。
 *
 * 另请参见#PSA_EAD_UPDATE_OUTPUT_SIZE（\p key_type，\p alg，\p input_length）。
 *
 * \param input_length输入的大小（字节）。
 */
#define PSA_AEAD_UPDATE_OUTPUT_MAX_SIZE(input_length)                           \
    (PSA_ROUND_UP_TO_MULTIPLE(PSA_BLOCK_CIPHER_BLOCK_MAX_SIZE, (input_length)))

/** psa_aead_finish（）的密文缓冲区大小足够。
 *
 * 如果密文缓冲区的大小至少如此大，则可以保证psa_aead_finish（）不会因密文缓冲区大小不足而失败。在任何给定的调用中，输出的实际大小都可能更小。
 *
 * 另请参见#PSA_EAD_FINISH_OUTPUT_MAX_SIZE。
 *
 * \param key_type与算法\p alg兼容的对称密钥类型。\param alg AEAD算法（\c PSA_alg_XXX值，使得#PSA_alg_IS_AEAD（\p alg）为真）。
 *
 * \返回指定算法的足够密文缓冲区大小。如果无法识别密钥类型或AEAD算法，或者参数不兼容，则返回0。
 */
#define PSA_AEAD_FINISH_OUTPUT_SIZE(key_type, alg) \
    (PSA_AEAD_NONCE_LENGTH(key_type, alg) != 0 &&  \
         PSA_ALG_IS_AEAD_ON_BLOCK_CIPHER(alg) ?    \
         PSA_BLOCK_CIPHER_BLOCK_LENGTH(key_type) : \
     0)

/** 对于任何受支持的密钥类型和aead算法，psa_aead_finish（）的密文缓冲区大小足够。
 *
 * 另请参见#PSA_EAD_FINISH_OUTPUT_SIZE（\p key_type，\p alg）。
 */
#define PSA_AEAD_FINISH_OUTPUT_MAX_SIZE     (PSA_BLOCK_CIPHER_BLOCK_MAX_SIZE)

/** psa_aead_verify（）的明文缓冲区大小足够。
 *
 * 如果明文缓冲区的大小至少如此大，则可以保证psa_aead_verify（）不会因明文缓冲区大小不足而失败。在任何给定的调用中，输出的实际大小都可能更小。
 *
 * 另请参见#PSA_EAD_VERIFY_OUTPUT_MAX_SIZE。
 *
 * \param key_type与算法\p alg兼容的对称密钥类型。\param alg AEAD算法（\c PSA_alg_XXX值，使得#PSA_alg_IS_AEAD（\p alg）为真）。
 *
 * \返回指定算法的足够明文缓冲区大小。如果无法识别密钥类型或AEAD算法，或者参数不兼容，则返回0。
 */
#define PSA_AEAD_VERIFY_OUTPUT_SIZE(key_type, alg) \
    (PSA_AEAD_NONCE_LENGTH(key_type, alg) != 0 &&  \
         PSA_ALG_IS_AEAD_ON_BLOCK_CIPHER(alg) ?    \
         PSA_BLOCK_CIPHER_BLOCK_LENGTH(key_type) : \
     0)

/** 对于任何支持的密钥类型和aead算法，psa_aead_verify（）的明文缓冲区大小足够。
 *
 * 另请参见#PSA_EAD_VERIFY_OUTPUT_SIZE（\p key_type，\p alg）。
 */
#define PSA_AEAD_VERIFY_OUTPUT_MAX_SIZE     (PSA_BLOCK_CIPHER_BLOCK_MAX_SIZE)

#define PSA_RSA_MINIMUM_PADDING_SIZE(alg)                         \
    (PSA_ALG_IS_RSA_OAEP(alg) ?                                   \
     2 * PSA_HASH_LENGTH(PSA_ALG_RSA_OAEP_GET_HASH(alg)) + 1 :    \
     11 /*PKCS#1v1.5*/)

/**
 * \给定曲线比特大小的简短ECDSA签名大小
 *
 * \param curve_bits曲线大小（以位为单位）。\return签名大小（字节）。
 *
 * \注意：如果此宏的参数为1，则返回编译时间常数。
 */
#define PSA_ECDSA_SIGNATURE_SIZE(curve_bits)    \
    (PSA_BITS_TO_BYTES(curve_bits) * 2)

/** psa_sign_hash（）的签名缓冲区大小足够。
 *
 * 此宏使用指定类型和大小的密钥以及指定的算法为签名返回足够的缓冲区大小。注意，签名的实际大小可能更小（一些算法产生可变大小的签名）。
 *
 * \警告此函数可能多次或零次调用其参数，因此不应传递包含副作用的参数。
 *
 * \param key_type非对称密钥类型（可以是密钥对类型或公钥类型）。\param key_bits密钥的大小（以位为单位）。\param alg签名算法。
 *
 * \return如果参数有效且受支持，则返回以字节为单位的缓冲区大小，以确保psa_sign_hash（）不会因#psa_ERROR_buffer_TOO_SMALL而失败。如果参数是不受支持的有效组合，则返回可感知大小或0。如果参数无效，则返回值未指定。
 */
#define PSA_SIGN_OUTPUT_SIZE(key_type, key_bits, alg)        \
    (PSA_KEY_TYPE_IS_RSA(key_type) ? ((void)alg, PSA_BITS_TO_BYTES(key_bits)) : \
     PSA_KEY_TYPE_IS_ECC(key_type) ? PSA_ECDSA_SIGNATURE_SIZE(key_bits) : \
     ((void)alg, 0))

#define PSA_VENDOR_ECDSA_SIGNATURE_MAX_SIZE     \
    PSA_ECDSA_SIGNATURE_SIZE(PSA_VENDOR_ECC_MAX_CURVE_BITS)

/** \定义PSA_SIGNATURE_MAX_SIZE
 *
 * 非对称签名的最大大小。
 *
 * 此宏扩展为编译时常量整数。此值是签名的最大大小（以字节为单位）。
 */
#define PSA_SIGNATURE_MAX_SIZE                               \
    (PSA_BITS_TO_BYTES(PSA_VENDOR_RSA_MAX_KEY_BITS) > PSA_VENDOR_ECDSA_SIGNATURE_MAX_SIZE ? \
     PSA_BITS_TO_BYTES(PSA_VENDOR_RSA_MAX_KEY_BITS) :                   \
     PSA_VENDOR_ECDSA_SIGNATURE_MAX_SIZE)

/** psa_aymmetric_encrypt（）的输出缓冲区大小足够。
 *
 * 此宏为使用指定类型和大小的密钥以及指定的算法生成的密文返回足够的缓冲区大小。注意，根据算法，密文的实际大小可能更小。
 *
 * \警告此函数可能多次或零次调用其参数，因此不应传递包含副作用的参数。
 *
 * \param key_type非对称密钥类型（可以是密钥对类型或公钥类型）。\param key_bits密钥的大小（以位为单位）。\param alg非对称加密算法。
 *
 * \return如果参数有效且受支持，则返回一个以字节为单位的缓冲区大小，以确保psa_asymmetric_encrypt（）不会因#psa_ERROR_buffer_TOO_SMALL而失败。如果参数是不受支持的有效组合，则返回可感知大小或0。如果参数无效，则返回值未指定。
 */
#define PSA_ASYMMETRIC_ENCRYPT_OUTPUT_SIZE(key_type, key_bits, alg)     \
    (PSA_KEY_TYPE_IS_RSA(key_type) ?                                    \
     ((void)alg, PSA_BITS_TO_BYTES(key_bits)) :                         \
     0)

/** 对于任何受支持的非对称加密，psa_nsymmetric_encrypt（）的输出缓冲区大小足够。
 *
 * 另请参阅#PSA_SYMMETRIC_ENCRYPT_OUTPUT_SIZE（\p key_type，\p key_bits，\p alg）。
 */
/* 此宏假定RSA是唯一受支持的非对称加密。*/
#define PSA_ASYMMETRIC_ENCRYPT_OUTPUT_MAX_SIZE          \
    (PSA_BITS_TO_BYTES(PSA_VENDOR_RSA_MAX_KEY_BITS))

/** psa_aymmetric_decrypt（）的输出缓冲区大小足够。
 *
 * 此宏为使用指定类型和大小的密钥以及指定的算法生成的明文返回足够的缓冲区大小。注意，明文的实际大小可能更小，这取决于算法。
 *
 * \警告此函数可能多次或零次调用其参数，因此不应传递包含副作用的参数。
 *
 * \param key_type非对称密钥类型（可以是密钥对类型或公钥类型）。\param key_bits密钥的大小（以位为单位）。\param alg非对称加密算法。
 *
 * \return如果参数有效且受支持，则返回一个以字节为单位的缓冲区大小，以确保psa_naymmetric_decrypt（）不会因#psa_ERROR_buffer_TOO_SMALL而失败。如果参数是不受支持的有效组合，则返回可感知大小或0。如果参数无效，则返回值未指定。
 */
#define PSA_ASYMMETRIC_DECRYPT_OUTPUT_SIZE(key_type, key_bits, alg)     \
    (PSA_KEY_TYPE_IS_RSA(key_type) ?                                    \
     PSA_BITS_TO_BYTES(key_bits) - PSA_RSA_MINIMUM_PADDING_SIZE(alg) :  \
     0)

/** 对于任何受支持的非对称解密，psa_nsymmetric_decrypt（）的足够输出缓冲区大小。
 *
 * 此宏假定RSA是唯一受支持的非对称加密。
 *
 * 另请参阅#PSA_SYMMETRIC_DECRYPT_OUTPUT_SIZE（\p key_type，\p key_bits，\p alg）。
 */
#define PSA_ASYMMETRIC_DECRYPT_OUTPUT_MAX_SIZE          \
    (PSA_BITS_TO_BYTES(PSA_VENDOR_RSA_MAX_KEY_BITS))

/* ASN的最大大小。指定位数的整数的1编码。
 *
 * 此定义假定位<=2^19-9，因此长度字段最多为3字节。编码长度是填充到整数字节的位串长度加上：
 * -1类型字节；
 * -1至3个长度字节；
 * -由于符号位，前导0的0到1字节。
 */
#define PSA_KEY_EXPORT_ASN1_INTEGER_MAX_SIZE(bits)      \
    ((bits) / 8 + 5)

/* RSA公钥的导出编码的最大大小。假设公共指数小于2^32。
 *
 * RSAPublicKey:：=序列｛模整数，--n公共指数整数｝--e
 *
 * -4字节的SEQUENCE开销；
 * -n：整数；
 * -公共指数为7字节。
 */
#define PSA_KEY_EXPORT_RSA_PUBLIC_KEY_MAX_SIZE(key_bits)        \
    (PSA_KEY_EXPORT_ASN1_INTEGER_MAX_SIZE(key_bits) + 11)

/* RSA密钥对的导出编码的最大大小。假设公共指数小于2^32，并且两个素数之间的大小差最多为1位。
 *
 * RSAPrivateKey：：=SEQUENCE｛版本版本，--0模整数，--N位公共指数整数，--32位私有指数整数，--N位素数1整数，--N/2位素数2整数，--N/2位指数1整数，--N/2位指数2整数，--N/2位系数整数，--N-2位｝
 *
 * -4字节的SEQUENCE开销；
 * -3字节版本；
 * -7个半大小的整数加上2个全大小的整数，超过9个半大小整数；
 * -公共指数为7字节。
 */
#define PSA_KEY_EXPORT_RSA_KEY_PAIR_MAX_SIZE(key_bits)   \
    (9 * PSA_KEY_EXPORT_ASN1_INTEGER_MAX_SIZE((key_bits) / 2 + 1) + 14)

/* DSA公钥导出编码的最大大小。
 *
 * SubjectPublicKeyInfo:：=序列｛算法算法标识符，subjectPublicKey位字符串｝--包含DSAPublicKey算法标识符：：=序列{算法对象标识符，参数Dss-Parms｝--3个整数的序列DSAPublicKey:：=整数--公钥，Y
 *
 * -3*4字节的SEQUENCE开销；
 * -1+1+7字节的算法（DSA OID）；
 * -4字节的比特串开销；
 * -3个全尺寸整数（p，g，y）；
 * -对于1个子大小INTEGER（q<=256位），为1+1+32字节。
 */
#define PSA_KEY_EXPORT_DSA_PUBLIC_KEY_MAX_SIZE(key_bits)        \
    (PSA_KEY_EXPORT_ASN1_INTEGER_MAX_SIZE(key_bits) * 3 + 59)

/* DSA密钥对的导出编码的最大大小。
 *
 * DSAPrivateKey:：=序列｛版本版本，--0主整数，--p次整数，--q生成器整数，--g公共整数，--y专用整数，--x｝
 *
 * -4字节的SEQUENCE开销；
 * -3字节版本；
 * -3个全尺寸整数（p，g，y）；
 * -2*（1+1+32）字节，用于2个子大小的整数（q，x<=256位）。
 */
#define PSA_KEY_EXPORT_DSA_KEY_PAIR_MAX_SIZE(key_bits)   \
    (PSA_KEY_EXPORT_ASN1_INTEGER_MAX_SIZE(key_bits) * 3 + 75)

/* ECC公钥的导出编码的最大大小。
 *
 * ECC公钥的表示是：
 *      -字节0x04；
 *      -“x_P”作为“上限（m/8）”字节字符串，大端；
 *      -“y_P”作为“上限（m/8）”字节字符串，大端；
 *      -其中m是与曲线相关联的比特大小。
 *
 * -1字节+2*点大小。
 */
#define PSA_KEY_EXPORT_ECC_PUBLIC_KEY_MAX_SIZE(key_bits)        \
    (2 * PSA_BITS_TO_BYTES(key_bits) + 1)

/* ECC密钥对的导出编码的最大大小。
 *
 * ECC密钥对由密钥值表示。
 */
#define PSA_KEY_EXPORT_ECC_KEY_PAIR_MAX_SIZE(key_bits)   \
    (PSA_BITS_TO_BYTES(key_bits))

/** 为psa_export_key（）或psa_eexport_public_key（（）提供足够的输出缓冲区大小。
 *
 * 如果此宏的参数是编译时常量，则返回编译时常量。
 *
 * \警告此宏可能会多次或零次计算其参数，因此不应传递包含副作用的参数。
 *
 * 下面的代码说明了如何通过在运行时查询密钥类型和大小来分配足够的内存以导出密钥。\code｛c｝psa_key_attributes_t attributes=psa_key_attributes_INIT；psa_status_t状态；状态=psa_get_key_attributes（键，属性）；如果（状态！=PSA_SUCCESS）handle_error（…）；psa_key_type_t key_type=psa_get_key_type（&attributes）；size_t key_bits=psa_get_key_bits（&attributes）；size_t buffer_size=PSA_EXPORT_KEY_OUTPUT_size（KEY_type，KEY_bits）；psa_reset_key_attributes（&attributes）；uint8_t缓冲区=malloc（缓冲区大小）；如果（缓冲区==NULL）handle_error（…）；size_t缓冲区长度；状态=psa_export_key（密钥、缓冲区、缓冲区大小和缓冲区长度）；如果（状态！=PSA_SUCCESS）handle_error（…）；\结束代码
 *
 * \param key_type支持的密钥类型。\param key_bits密钥的大小（以位为单位）。
 *
 * \return如果参数有效且受支持，则返回一个以字节为单位的缓冲区大小，以确保psa_export_key（）或psa_eexport_public_key（（）不会因#psa_ERROR_buffer_TOO_SMALL而失败。如果参数是不受支持的有效组合，则返回可感知大小或0。如果参数无效，则返回值未指定。
 */
#define PSA_EXPORT_KEY_OUTPUT_SIZE(key_type, key_bits)                                              \
    (PSA_KEY_TYPE_IS_UNSTRUCTURED(key_type) ? PSA_BITS_TO_BYTES(key_bits) :                         \
     (key_type) == PSA_KEY_TYPE_RSA_KEY_PAIR ? PSA_KEY_EXPORT_RSA_KEY_PAIR_MAX_SIZE(key_bits) :     \
     (key_type) == PSA_KEY_TYPE_RSA_PUBLIC_KEY ? PSA_KEY_EXPORT_RSA_PUBLIC_KEY_MAX_SIZE(key_bits) : \
     (key_type) == PSA_KEY_TYPE_DSA_KEY_PAIR ? PSA_KEY_EXPORT_DSA_KEY_PAIR_MAX_SIZE(key_bits) :     \
     (key_type) == PSA_KEY_TYPE_DSA_PUBLIC_KEY ? PSA_KEY_EXPORT_DSA_PUBLIC_KEY_MAX_SIZE(key_bits) : \
     PSA_KEY_TYPE_IS_ECC_KEY_PAIR(key_type) ? PSA_KEY_EXPORT_ECC_KEY_PAIR_MAX_SIZE(key_bits) :      \
     PSA_KEY_TYPE_IS_ECC_PUBLIC_KEY(key_type) ? PSA_KEY_EXPORT_ECC_PUBLIC_KEY_MAX_SIZE(key_bits) :  \
     0)

/** psa_export_public_key（）的输出缓冲区大小足够。
 *
 * 如果此宏的参数是编译时常量，则返回编译时常量。
 *
 * \警告此宏可能会多次或零次计算其参数，因此不应传递包含副作用的参数。
 *
 * 下面的代码说明了如何通过在运行时查询密钥类型和大小来分配足够的内存以导出公钥。\code｛c｝psa_key_attributes_t attributes=psa_key_attributes_INIT；psa_status_t状态；状态=psa_get_key_attributes（键，属性）；如果（状态！=PSA_SUCCESS）handle_error（…）；psa_key_type_t key_type=psa_get_key_type（&attributes）；size_t key_bits=psa_get_key_bits（&attributes）；size_t buffer_size=PSA_EXPORT_PUBLIC_KEY_OUTPUT_size（KEY_type，KEY_bits）；psa_reset_key_attributes（&attributes）；uint8_t缓冲区=malloc（缓冲区大小）；如果（缓冲区==NULL）handle_error（…）；size_t缓冲区长度；状态=psa_export_public_key（密钥、缓冲区、缓冲区大小和缓冲区长度）；如果（状态！=PSA_SUCCESS）handle_error（…）；\结束代码
 *
 * \param key_type公钥或密钥对密钥类型。\param key_bits密钥的大小（以位为单位）。
 *
 * \return如果参数有效且受支持，则返回一个以字节为单位的缓冲区大小，以确保psa_export_public_key（）不会因#psa_ERROR_buffer_TOO_SMALL而失败。如果参数是不受支持的有效组合，则返回可感知大小或0。如果参数无效，则返回值未指定。
 *
 *                      如果参数有效且受支持，则返回与#PSA_EXPORT_KEY_OUTPUT_SIZE（\p#PSA_KEY_TYPE_PUBLIC_KEY_OF_KEY_PAIR（\p KEY_TYPE），\p KEY_bits）相同的结果。
 */
#define PSA_EXPORT_PUBLIC_KEY_OUTPUT_SIZE(key_type, key_bits)                           \
    (PSA_KEY_TYPE_IS_RSA(key_type) ? PSA_KEY_EXPORT_RSA_PUBLIC_KEY_MAX_SIZE(key_bits) : \
     PSA_KEY_TYPE_IS_ECC(key_type) ? PSA_KEY_EXPORT_ECC_PUBLIC_KEY_MAX_SIZE(key_bits) : \
     0)

/** 足够的缓冲区大小用于导出任何非对称密钥对。
 *
 * 此宏扩展为编译时常量整数。当调用psa_export_key（）以导出任何非对称密钥对时，无论确切的密钥类型和密钥大小如何，该值都是足够的缓冲区大小。
 *
 * 另请参见#PSA_EXPORT_KEY_OUTPUT_SIZE（\p KEY_type，\p KEY_bits）。
 */
#define PSA_EXPORT_KEY_PAIR_MAX_SIZE                                            \
    (PSA_KEY_EXPORT_RSA_KEY_PAIR_MAX_SIZE(PSA_VENDOR_RSA_MAX_KEY_BITS) >        \
     PSA_KEY_EXPORT_ECC_KEY_PAIR_MAX_SIZE(PSA_VENDOR_ECC_MAX_CURVE_BITS) ?      \
     PSA_KEY_EXPORT_RSA_KEY_PAIR_MAX_SIZE(PSA_VENDOR_RSA_MAX_KEY_BITS) :        \
     PSA_KEY_EXPORT_ECC_KEY_PAIR_MAX_SIZE(PSA_VENDOR_ECC_MAX_CURVE_BITS))

/** 足够的缓冲区大小用于导出任何非对称公钥。
 *
 * 此宏扩展为编译时常量整数。当调用psa_export_key（）或psa\uexport_public_key（（）导出任何非对称公钥时，无论确切的密钥类型和密钥大小如何，该值都是足够的缓冲区大小。
 *
 * 另请参见#PSA_EXPORT_PUBLIC_KEY_OUTPUT_SIZE（\p KEY_type，\p KEY_bits）。
 */
#define PSA_EXPORT_PUBLIC_KEY_MAX_SIZE                                          \
    (PSA_KEY_EXPORT_RSA_PUBLIC_KEY_MAX_SIZE(PSA_VENDOR_RSA_MAX_KEY_BITS) >      \
     PSA_KEY_EXPORT_ECC_PUBLIC_KEY_MAX_SIZE(PSA_VENDOR_ECC_MAX_CURVE_BITS) ?    \
     PSA_KEY_EXPORT_RSA_PUBLIC_KEY_MAX_SIZE(PSA_VENDOR_RSA_MAX_KEY_BITS) :      \
     PSA_KEY_EXPORT_ECC_PUBLIC_KEY_MAX_SIZE(PSA_VENDOR_ECC_MAX_CURVE_BITS))

/** psa\raw_key_agreement（）的输出缓冲区大小足够。
 *
 * 如果此宏的参数是编译时常量，则返回编译时常量。
 *
 * \警告此宏可能会多次或零次计算其参数，因此不应传递包含副作用的参数。
 *
 * 另请参阅#PSA_RAW_KEY_AGREEMENT_OUTPUT_MAX_SIZE。
 *
 * \param key_type支持的密钥类型。\param key_bits密钥的大小（以位为单位）。
 *
 * \return如果参数有效且受支持，则返回一个以字节为单位的缓冲区大小，以确保psa_raw_key_agreement（）不会因#psa_ERROR_buffer_TOO_SMALL而失败。如果参数是不受支持的有效组合，则返回可感知大小或0。如果参数无效，则返回值未指定。
 */
/* PSA中尚不支持FFDH。*/
#define PSA_RAW_KEY_AGREEMENT_OUTPUT_SIZE(key_type, key_bits)   \
    (PSA_KEY_TYPE_IS_ECC_KEY_PAIR(key_type) ?                   \
     PSA_BITS_TO_BYTES(key_bits) :                              \
     0)

/** psa\raw_key_agreement（）输出的最大大小。
 *
 * 此宏扩展为编译时常量整数。该值是任何原始密钥协议算法输出的最大大小（以字节为单位）。
 *
 * 另请参阅#PSA_RAW_KEY_AGREEMENT_OUTPUT_SIZE（\p KEY_type，\p KEY_bits）。
 */
#define PSA_RAW_KEY_AGREEMENT_OUTPUT_MAX_SIZE   \
    (PSA_BITS_TO_BYTES(PSA_VENDOR_ECC_MAX_CURVE_BITS))

/** 密码算法的默认IV大小，以字节为单位。
 *
 * 作为调用#psa_cher_encrypt（）的一部分生成的IV始终是算法的默认IV长度。
 *
 * 当使用多部分密码操作时，此宏可用于分配足够大小的缓冲区，以存储#psa_cher_generate.IV（）的IV输出。
 *
 * 另请参见#PSA_CIPHER_IV_MAX_SIZE。
 *
 * \警告此宏可能会多次或零次计算其参数，因此不应传递包含副作用的参数。
 *
 * \param key_type与算法\p alg兼容的对称密钥类型。
 *
 * \param alg密码算法（\c PSA_alg_XXX值，使得#PSA_alg_IS_cipher（\p alg）为真）。
 *
 * \return指定密钥类型和算法的默认IV大小。如果算法不使用IV，则返回0。如果无法识别密钥类型或密码算法，或者参数不兼容，则返回1。
 */
#define PSA_CIPHER_IV_LENGTH(key_type, alg) \
    (PSA_BLOCK_CIPHER_BLOCK_LENGTH(key_type) > 1 && \
        ((alg) == PSA_ALG_CTR || \
         (alg) == PSA_ALG_CFB || \
         (alg) == PSA_ALG_OFB || \
         (alg) == PSA_ALG_XTS || \
         (alg) == PSA_ALG_CBC_NO_PADDING || \
         (alg) == PSA_ALG_CBC_PKCS7) ? PSA_BLOCK_CIPHER_BLOCK_LENGTH(key_type) : \
     (key_type) == PSA_KEY_TYPE_CHACHA20 && \
         (alg) == PSA_ALG_STREAM_CIPHER ? 12 : \
     0)

/** 所有支持的密码算法的最大IV大小（以字节为单位）。
 *
 * 另请参见#PSA_CIPHER_IV_LENGTH（）。
 */
#define PSA_CIPHER_IV_MAX_SIZE 16

/** psa_cher_encrypt（）输出的最大大小，以字节为单位。
 *
 * 如果输出缓冲区的大小至少如此大，则可以保证psa_cipher_encrypt（）不会因缓冲区大小不足而失败。根据算法，输出的实际大小可能更小。
 *
 * 另请参阅#PSA_CIPHER_ENCRYPT_OUTPUT_MAX_SIZE（\p input_length）。
 *
 * \警告此宏可能会多次或零次计算其参数，因此不应传递包含副作用的参数。
 *
 * \param key_type与算法alg兼容的对称密钥类型。\param alg密码算法（\c PSA_alg_XXX值，使得#PSA_alg_IS_cipher（\p alg）为真）。\param input_length输入的大小（字节）。
 *
 * \返回指定密钥类型和算法的足够输出大小。如果无法识别密钥类型或密码算法，或者参数不兼容，请返回0。
 */
#define PSA_CIPHER_ENCRYPT_OUTPUT_SIZE(key_type, alg, input_length)             \
    (alg == PSA_ALG_CBC_PKCS7 ?                                                 \
     (PSA_BLOCK_CIPHER_BLOCK_LENGTH(key_type) != 0 ?                            \
     PSA_ROUND_UP_TO_MULTIPLE(PSA_BLOCK_CIPHER_BLOCK_LENGTH(key_type),          \
                              (input_length) + 1) +                             \
     PSA_CIPHER_IV_LENGTH((key_type), (alg)) : 0) :                             \
     (PSA_ALG_IS_CIPHER(alg) ?                                                  \
      (input_length) + PSA_CIPHER_IV_LENGTH((key_type), (alg)) :                \
     0))

/** 对于任何受支持的密钥类型和密码算法，psa_cher_encrypt（）的输出缓冲区大小都足够。
 *
 * 如果输出缓冲区的大小至少如此大，则可以保证psa_cipher_encrypt（）不会因缓冲区大小不足而失败。
 *
 * 另请参阅#PSA_CIPHER_ENCRYPT_OUTPUT_SIZE（\p key_type，\p alg，\p input_length）。
 *
 * \param input_length输入的大小（字节）。
 *
 */
#define PSA_CIPHER_ENCRYPT_OUTPUT_MAX_SIZE(input_length)                        \
    (PSA_ROUND_UP_TO_MULTIPLE(PSA_BLOCK_CIPHER_BLOCK_MAX_SIZE,                  \
                              (input_length) + 1) +                             \
     PSA_CIPHER_IV_MAX_SIZE)

/** psa_cher_decrypt（）输出的最大大小，以字节为单位。
 *
 * 如果输出缓冲区的大小至少如此大，则可以保证psa_cher_decrypt（）不会因缓冲区大小不足而失败。根据算法，输出的实际大小可能更小。
 *
 * 另请参阅#PSA_CIPHER_DECRYPT_OUTPUT_MAX_SIZE（\p input_length）。
 *
 * \param key_type与算法alg兼容的对称密钥类型。\param alg密码算法（\c PSA_alg_XXX值，使得#PSA_alg_IS_cipher（\p alg）为真）。\param input_length输入的大小（字节）。
 *
 * \返回指定密钥类型和算法的足够输出大小。如果无法识别密钥类型或密码算法，或者参数不兼容，请返回0。
 */
#define PSA_CIPHER_DECRYPT_OUTPUT_SIZE(key_type, alg, input_length)                 \
    (PSA_ALG_IS_CIPHER(alg) &&                                                      \
     ((key_type) & PSA_KEY_TYPE_CATEGORY_MASK) == PSA_KEY_TYPE_CATEGORY_SYMMETRIC ? \
     (input_length) :                                                               \
     0)

/** 对于任何支持的密钥类型和密码算法，psa_cher_decrypt（）的输出缓冲区大小都足够。
 *
 * 如果输出缓冲区的大小至少如此大，则可以保证psa_cher_decrypt（）不会因缓冲区大小不足而失败。
 *
 * 另请参阅#PSA_CIPHER_DECRYPT_OUTPUT_SIZE（\p key_type，\p alg，\p input_length）。
 *
 * \param input_length输入的大小（字节）。
 */
#define PSA_CIPHER_DECRYPT_OUTPUT_MAX_SIZE(input_length)    \
    (input_length)

/** psa_cipher_update（）的输出缓冲区大小足够。
 *
 * 如果输出缓冲区的大小至少如此大，则可以保证psa_cipher_update（）不会因缓冲区大小不足而失败。在任何给定的调用中，输出的实际大小都可能更小。
 *
 * 另请参阅#PSA_CIPHER_UPDATE_OUTPUT_MAX_SIZE（\p input_length）。
 *
 * \param key_type与算法alg兼容的对称密钥类型。\param alg密码算法（PSA_alg_XXX值，使得#PSA_alg_IS_cipher（\p alg）为真）。\param input_length输入的大小（字节）。
 *
 * \返回指定密钥类型和算法的足够输出大小。如果无法识别密钥类型或密码算法，或者参数不兼容，请返回0。
 */
#define PSA_CIPHER_UPDATE_OUTPUT_SIZE(key_type, alg, input_length)              \
    (PSA_ALG_IS_CIPHER(alg) ?                                                   \
    (PSA_BLOCK_CIPHER_BLOCK_LENGTH(key_type) != 0 ?                             \
     (((alg) == PSA_ALG_CBC_PKCS7      ||                                       \
       (alg) == PSA_ALG_CBC_NO_PADDING ||                                       \
       (alg) == PSA_ALG_ECB_NO_PADDING) ?                                       \
      PSA_ROUND_UP_TO_MULTIPLE(PSA_BLOCK_CIPHER_BLOCK_LENGTH(key_type),         \
                                input_length) :                                 \
      (input_length)) : 0) :                                                    \
     0)

/** 对于任何受支持的密钥类型和密码算法，psa_cher_update（）的输出缓冲区大小都足够。
 *
 * 如果输出缓冲区的大小至少如此大，则可以保证psa_cipher_update（）不会因缓冲区大小不足而失败。
 *
 * 另请参见#PSA_CIPHER_UPDATE_OUTPUT_SIZE（\p key_type，\p alg，\p input_length）。
 *
 * \param input_length输入的大小（字节）。
 */
#define PSA_CIPHER_UPDATE_OUTPUT_MAX_SIZE(input_length)     \
    (PSA_ROUND_UP_TO_MULTIPLE(PSA_BLOCK_CIPHER_BLOCK_MAX_SIZE, input_length))

/** psa_cher_finish（）的密文缓冲区大小足够。
 *
 * 如果密文缓冲区的大小至少如此大，则可以保证psa_cher_finish（）不会因密文缓冲区大小不足而失败。在任何给定的调用中，输出的实际大小都可能更小。
 *
 * 另请参见#PSA_CIPHER_FINISH_OUTPUT_MAX_SIZE（）。
 *
 * \param key_type与算法alg兼容的对称密钥类型。\param alg密码算法（PSA_alg_XXX值，使得#PSA_alg_IS_cipher（\p alg）为真）。\返回指定密钥类型和算法的足够输出大小。如果无法识别密钥类型或密码算法，或者参数不兼容，请返回0。
 */
#define PSA_CIPHER_FINISH_OUTPUT_SIZE(key_type, alg)    \
    (PSA_ALG_IS_CIPHER(alg) ?                           \
     (alg == PSA_ALG_CBC_PKCS7 ?                        \
      PSA_BLOCK_CIPHER_BLOCK_LENGTH(key_type) :         \
      0) :                                              \
     0)

/** 对于任何支持的密钥类型和密码算法，psa_cher_finish（）的足够密文缓冲区大小。
 *
 * 另请参见#PSA_CIPHER_FINISH_OUTPUT_SIZE（\p key_type，\p alg）。
 */
#define PSA_CIPHER_FINISH_OUTPUT_MAX_SIZE           \
    (PSA_BLOCK_CIPHER_BLOCK_MAX_SIZE)

#endif /* PSA_CRYPTO_SIZES_H */

