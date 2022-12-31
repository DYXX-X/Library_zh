/*
 *  PSA AEAD驾驶员入口点
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

#ifndef PSA_CRYPTO_AEAD_H
#define PSA_CRYPTO_AEAD_H

#include <psa/crypto.h>

/**
 * \brief处理经过身份验证的加密操作。
 *
 * \注意：此函数的签名是PSA驱动程序aead_encrypt入口点的签名。此函数充当透明驱动程序的PSA驱动程序接口规范中定义的aead_encrypt入口点。
 *
 * \param[in]attributes用于操作的键的属性。\param[in]key_buffer包含密钥上下文的缓冲区。\param key_buffer_size \p key_bbuffer缓冲区的大小（以字节为单位）。\param alg要计算的AEAD算法。\param[in]要使用的nonce或IV。\param nonce_length nonce缓冲区的大小（字节）。这必须适用于所选算法。默认的随机数大小为PSA_EAD_nonce_LENGTH（key_type，alg），其中key_type是密钥的类型。\param[in]additional_data将进行身份验证但未加密的其他数据。\param additional_data_length additional_data的大小（字节）。\param[in]明文将被验证和加密的数据。\param plaintext_length以字节为单位的明文大小。\param[out]密文已验证和加密数据的输出缓冲区。附加数据不是此输出的一部分。对于加密数据和认证标签被定义为单独输出的算法，认证标签被附加到加密数据。\param ciphertext_size密文缓冲区的大小（字节）。这必须适用于所选算法和密钥：
 *                                -一个足够的输出大小是PSA_EAD_ENCRYPT_output_size（key_type，alg，明文_length），其中key_type是密钥的类型。
 *                                -PSA_EAD_ENCRYPT_OUTPUT_MAX_SIZE（明文长度）计算为任何支持的AEAD加密的最大密文大小。\param[out]ciphertext_length成功时，密文缓冲区中输出的大小。
 *
 * \retval#PSA_SUCCESS成功。\不支持retval#PSA_ERROR_NOT_SUPPORTED\p alg。\retval#PSA_ERROR_INSUFFIE_MEMORY\retval#PSA错误_BUFFER_TOO_SMALL密文大小太小。\retval#PSA_ERROR_CORRUPTION_DETECTED
 */
psa_status_t mbedtls_psa_aead_encrypt(
    const psa_key_attributes_t *attributes,
    const uint8_t *key_buffer, size_t key_buffer_size,
    psa_algorithm_t alg,
    const uint8_t *nonce, size_t nonce_length,
    const uint8_t *additional_data, size_t additional_data_length,
    const uint8_t *plaintext, size_t plaintext_length,
    uint8_t *ciphertext, size_t ciphertext_size, size_t *ciphertext_length );

/**
 * \brief处理经过身份验证的解密操作。
 *
 * \注意：此函数的签名是PSA驱动程序aead_decrypt入口点的签名。此函数充当透明驱动程序的PSA驱动程序接口规范中定义的aead_decrypt入口点。
 *
 * \param[in]attributes用于操作的键的属性。\param[in]key_buffer包含密钥上下文的缓冲区。\param key_buffer_size \p key_bbuffer缓冲区的大小（以字节为单位）。\param alg要计算的AEAD算法。\param[in]要使用的nonce或IV。\param nonce_length nonce缓冲区的大小（字节）。这必须适用于所选算法。默认的随机数大小为PSA_EAD_nonce_LENGTH（key_type，alg），其中key_type是密钥的类型。\param[in]additional_data已验证但未加密的其他数据。\param additional_data_length additional_data的大小（字节）。\param[in]密文已验证和加密的数据。对于加密数据和认证标签被定义为单独输入的算法，缓冲区包含加密数据，随后是认证标签。\param ciphertext_length密文的大小（字节）。\param[out]明文解密数据的输出缓冲区。\param plaintext_size明文缓冲区的大小（字节）。这必须适用于所选算法和密钥：
 *                                -一个足够的输出大小是PSA_EAD_DECRYPT_output_size（key_type，alg，密文_length），其中key_type是密钥的类型。
 *                                -PSA_EAD_DECRYPT_OUTPUT_MAX_SIZE（密文长度）计算为任何支持的AEAD解密的最大明文大小。\param[out]plaintext_length成功时，明文缓冲区中输出的大小。
 *
 * \retval#PSA_SUCCESS成功。\retval#PSA_ERROR_INVALID_SIGNATURE密码不可信。\不支持retval#PSA_ERROR_NOT_SUPPORTED\p alg。\retval#PSA_ERROR_INSUFFIE_MEMORY\retval#PSA错误_BUFFER_TOO_SMALL明文大小太小。\retval#PSA_ERROR_CORRUPTION_DETECTED
 */
psa_status_t mbedtls_psa_aead_decrypt(
    const psa_key_attributes_t *attributes,
    const uint8_t *key_buffer, size_t key_buffer_size,
    psa_algorithm_t alg,
    const uint8_t *nonce, size_t nonce_length,
    const uint8_t *additional_data, size_t additional_data_length,
    const uint8_t *ciphertext, size_t ciphertext_length,
    uint8_t *plaintext, size_t plaintext_size, size_t *plaintext_length );

#endif /* PSA_CRYPTO_AEAD */

