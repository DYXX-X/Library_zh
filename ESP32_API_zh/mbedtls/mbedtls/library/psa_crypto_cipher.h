/*
 *  PSA密码驱动程序入口点
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

#ifndef PSA_CRYPTO_CIPHER_H
#define PSA_CRYPTO_CIPHER_H

#include <mbedtls/cipher.h>
#include <psa/crypto.h>

/** 在给定加密算法PSA标识符以及要与加密算法一起使用的密钥的PSA类型和大小的情况下，获取Mbed TLS加密信息。
 *
 * \param alg PSA密码算法标识符\param key_type PSA密钥类型\param key _bits密钥的大小（以位为单位）\param[out]cipher_id Mbed TLS密码算法标识符
 *
 * \return密码算法的Mbed TLS密码信息。\c如果不支持PSA密码算法，则为NULL。
 */
const mbedtls_cipher_info_t *mbedtls_cipher_info_from_psa(
    psa_algorithm_t alg, psa_key_type_t key_type, size_t key_bits,
    mbedtls_cipher_id_t *cipher_id );

/**
 * \brief设置多部分对称加密操作的密钥。
 *
 * \注意：此函数的签名是PSA驱动程序cipher_encrypt_setup入口点的签名。此函数充当透明驱动程序的PSA驱动程序接口规范中定义的cipher_encrypt_setup入口点。
 *
 * \param[in，out]operation要设置的操作对象。它已根据#psa_cher_operation_t文档进行初始化，但尚未使用。\param[in]attributes用于操作的键的属性。\param[in]key_buffer包含密钥上下文的缓冲区。\param[in]key_buffer_size \p key_buffer缓冲区的大小（字节）。\param[in]alg要计算的密码算法（\c PSA_alg_XXX值，使得#PSA_alg_IS_cipher（\p alg）为真）。
 *
 * \retval#PSA_SUCCESS\retval#PSTA_ERROR_NOT_SUPPORTED\retval#PSA_ERROR_INSUFFIE_MEMORY\retval#PSA_ERROR_CORRUPTION_DETECTED
 */
psa_status_t mbedtls_psa_cipher_encrypt_setup(
    mbedtls_psa_cipher_operation_t *operation,
    const psa_key_attributes_t *attributes,
    const uint8_t *key_buffer, size_t key_buffer_size,
    psa_algorithm_t alg );

/**
 * \brief设置多部分对称解密操作的密钥。
 *
 * \注意：此函数的签名是PSA驱动程序cipher_decrypt_setup入口点的签名。此函数充当透明驱动程序的PSA驱动程序接口规范中定义的cipher_decrypt_setup入口点。
 *
 * \param[in，out]operation要设置的操作对象。它已根据#psa_cher_operation_t文档进行初始化，但尚未使用。\param[in]attributes用于操作的键的属性。\param[in]key_buffer包含密钥上下文的缓冲区。\param[in]key_buffer_size \p key_buffer缓冲区的大小（字节）。\param[in]alg要计算的密码算法（\c PSA_alg_XXX值，使得#PSA_alg_IS_cipher（\p alg）为真）。
 *
 * \retval#PSA_SUCCESS\retval#PSTA_ERROR_NOT_SUPPORTED\retval#PSA_ERROR_INSUFFIE_MEMORY\retval#PSA_ERROR_CORRUPTION_DETECTED
 */
psa_status_t mbedtls_psa_cipher_decrypt_setup(
    mbedtls_psa_cipher_operation_t *operation,
    const psa_key_attributes_t *attributes,
    const uint8_t *key_buffer, size_t key_buffer_size,
    psa_algorithm_t alg );

/** 为对称加密或解密操作设置IV。
 *
 * 此函数设置加密或解密操作的IV（初始化向量）、随机数或初始计数器值。
 *
 * \注：此函数的签名是PSA驱动程序cipher_set_iv入口点的签名。此函数充当透明驱动程序的PSA驱动程序接口规范中定义的cipher_set_iv入口点。
 *
 * \param[in，out]操作活动密码操作。\param[in]iv包含要使用的iv的缓冲区。\param[in]iv_length iv的大小（字节）。内核保证其小于或等于PSA_CIPHER_IV_MAX_SIZE。
 *
 * \retval#PSA_SUCCESS\retval#PSTA_ERROR_INVALID_ARGUMENT所选算法不接受\p iv的大小，或者所选算法未使用iv.\retval#PSA _ERROR_INSUFFIE_MEMORY
 */
psa_status_t mbedtls_psa_cipher_set_iv(
    mbedtls_psa_cipher_operation_t *operation,
    const uint8_t *iv, size_t iv_length );

/** 在活动密码操作中加密或解密消息片段。
 *
 * \注意：此函数的签名是PSA驱动程序cipher_update入口点的签名。此函数充当透明驱动程序的PSA驱动程序接口规范中定义的密码更新入口点。
 *
 * \param[in，out]操作活动密码操作。\param[in]输入缓冲区，包含要加密或解密的消息片段。\param[in]input_length输入缓冲区的大小（字节）。\param[out]输出要写入输出的缓冲区。\param[in]output_size输出缓冲区的大小（字节）。\param[out]output_length成功时，构成返回输出的字节数。
 *
 * \retval#PSA_SUCCESS\retval#PSTA_ERROR_BUFFER_TOO_SMALL输出缓冲区的大小太小。\retval#PSA_ERROR_INSUFFIED_EMORY（返回#PSA_错误_充足_内存）
 */
psa_status_t mbedtls_psa_cipher_update(
    mbedtls_psa_cipher_operation_t *operation,
    const uint8_t *input, size_t input_length,
    uint8_t *output, size_t output_size, size_t *output_length );

/** 在密码操作中完成对消息的加密或解密。
 *
 * \注意：此函数的签名是PSA驱动程序cipher_finish入口点的签名。此函数充当透明驱动程序的PSA驱动程序接口规范中定义的密码完成入口点。
 *
 * \param[in，out]操作活动密码操作。\param[out]输出要写入输出的缓冲区。\param[in]output_size输出缓冲区的大小（字节）。\param[out]output_length成功时，构成返回输出的字节数。
 *
 * \retval#PSA_SUCCESS\retval#PSTA_ERROR_INVALID_ARGUMENT传递给此操作的总输入大小对于此特定算法无效。例如，该算法是基于分组密码的，需要整数个块，但总输入大小不是块大小的倍数。\retval#PSA_ERROR_INVALID_PADDING这是对包含填充的算法的解密操作，并且密文不包含有效填充。\retval#PSA_ERROR_BUFFER_TOO_SMALL输出缓冲区的大小太小。\retval#PSA_ERROR_INSUFFIED_EMORY（返回#PSA_错误_充足_内存）
 */
psa_status_t mbedtls_psa_cipher_finish(
    mbedtls_psa_cipher_operation_t *operation,
    uint8_t *output, size_t output_size, size_t *output_length );

/** 中止密码操作。
 *
 * 中止操作将释放所有相关资源，但操作结构本身除外。中止后，操作对象可以重新用于其他操作。
 *
 * \注意：此函数的签名是PSA驱动程序cipher_abort入口点的签名。此函数充当透明驱动程序的PSA驱动程序接口规范中定义的密码端口入口点。
 *
 * \param[in，out]操作已初始化密码操作。
 *
 * \retval#PSA_SUCCESS
 */
psa_status_t mbedtls_psa_cipher_abort( mbedtls_psa_cipher_operation_t *operation );

/** 使用对称密码对消息进行加密。
 *
 * \注意：此函数的签名是PSA驱动程序cipher_encrypt入口点的签名。此函数充当透明驱动程序的PSA驱动程序接口规范中定义的加密入口点。
 *
 * \param[in]attributes用于操作的键的属性。\param[in]key_buffer包含密钥上下文的缓冲区。\param[in]key_buffer_size \p key_buffer缓冲区的大小（字节）。\param[in]alg要计算的密码算法（\c PSA_alg_XXX值，使得#PSA_alg_IS_cipher（\p alg）为真）。\param[in]iv包含用于加密的iv的缓冲区。IV由核心生成。\param[in]iv_length iv的大小（以字节为单位）。\param[in]输入缓冲区，包含要加密的消息。\param[in]input_length输入缓冲区的大小（字节）。\param[in，out]输出要写入输出的缓冲区。\param[in]output_size输出缓冲区的大小（字节）。\param[out]output_length成功时，构成返回输出的字节数。由内核初始化为零。
 *
 * \retval#PSA_SUCCESS\retval#PSTA_ERROR_NOT_SUPPORTED\retval#PSA_ERROR_INSUFFIE_MEMORY\retval#1PSA_ERROR_CORRUPTION_DETECTED \retval#2PSA_ERROR_BUFFER_TOO_SMALL输出缓冲区的大小太小。\retval#PSA_ERROR_INVALID_ARGUMENT所选算法不接受大小\p iv_length，或者所选算法未使用iv。传递给此操作的总输入大小对于此特定算法无效。例如，该算法是基于分组密码的，需要整数个块，但总输入大小不是块大小的倍数。\retval#PSA_ERROR_INVALID_PADDING这是对包含填充的算法的解密操作，并且密文不包含有效填充。
 */
psa_status_t mbedtls_psa_cipher_encrypt( const psa_key_attributes_t *attributes,
                                         const uint8_t *key_buffer,
                                         size_t key_buffer_size,
                                         psa_algorithm_t alg,
                                         const uint8_t *iv,
                                         size_t iv_length,
                                         const uint8_t *input,
                                         size_t input_length,
                                         uint8_t *output,
                                         size_t output_size,
                                         size_t *output_length );

/** 使用对称密码解密消息。
 *
 * \注意：此函数的签名是PSA驱动程序cipher_decrypt入口点的签名。此函数充当透明驱动程序的PSA驱动程序接口规范中定义的密文入口点。
 *
 * \param[in]attributes用于操作的键的属性。\param[in]key_buffer包含密钥上下文的缓冲区。\param[in]key_buffer_size \p key_buffer缓冲区的大小（字节）。\param[in]alg要计算的密码算法（\c PSA_alg_XXX值，使得#PSA_alg_IS_cipher（\p alg）为真）。\param[in]输入缓冲区，包含iv和密文。\param[in]input_length输入缓冲区的大小（字节）。\param[out]输出要写入输出的缓冲区。\param[in]output_size输出缓冲区的大小（字节）。\param[out]output_length成功时，构成返回输出的字节数。由内核初始化为零。
 *
 * \retval#PSA_SUCCESS\retval#PSTA_ERROR_NOT_SUPPORTED\retval#PSA_ERROR_INSUFFIE_MEMORY\retval#1PSA_ERROR_CORRUPTION_DETECTED \retval#2PSA_ERROR_BUFFER_TOO_SMALL输出缓冲区的大小太小。\retval#PSA_ERROR_INVALID_ARGUMENT所选算法不接受\p iv的大小，或者所选算法未使用iv。传递给此操作的总输入大小对于此特定算法无效。例如，该算法是基于分组密码的，需要整数个块，但总输入大小不是块大小的倍数。\retval#PSA_ERROR_INVALID_PADDING这是对包含填充的算法的解密操作，并且密文不包含有效填充。
 */
psa_status_t mbedtls_psa_cipher_decrypt( const psa_key_attributes_t *attributes,
                                         const uint8_t *key_buffer,
                                         size_t key_buffer_size,
                                         psa_algorithm_t alg,
                                         const uint8_t *input,
                                         size_t input_length,
                                         uint8_t *output,
                                         size_t output_size,
                                         size_t *output_length );

#endif /* PSA_CRYPTO_CIPHER_H */

