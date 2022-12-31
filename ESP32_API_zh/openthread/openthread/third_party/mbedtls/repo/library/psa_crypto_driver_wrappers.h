/*
 *  密码加速器可以提供的功能的函数签名。警告：此文件将在将来自动生成。
 */
/*  版权所有The Mbed TLS Contributors SPDX许可证标识符：Apache-2.0
 *
 *  根据Apache许可证2.0版（“许可证”）获得许可；除非符合许可证，否则不得使用此文件。您可以在以下地址获取许可证副本：
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 *  除非适用法律要求或书面同意，否则根据许可证分发的软件是按“原样”分发的，无任何明示或暗示的担保或条件。有关许可证下权限和限制的具体语言，请参阅许可证。
 */

#ifndef PSA_CRYPTO_DRIVER_WRAPPERS_H
#define PSA_CRYPTO_DRIVER_WRAPPERS_H

#include "psa/crypto.h"
#include "psa/crypto_driver_common.h"

/*
 * 签名函数
 */
psa_status_t psa_driver_wrapper_sign_hash( psa_key_slot_t *slot,
                                           psa_algorithm_t alg,
                                           const uint8_t *hash,
                                           size_t hash_length,
                                           uint8_t *signature,
                                           size_t signature_size,
                                           size_t *signature_length );

psa_status_t psa_driver_wrapper_verify_hash( psa_key_slot_t *slot,
                                             psa_algorithm_t alg,
                                             const uint8_t *hash,
                                             size_t hash_length,
                                             const uint8_t *signature,
                                             size_t signature_length );

/*
 * 钥匙处理功能
 */

psa_status_t psa_driver_wrapper_generate_key( const psa_key_attributes_t *attributes,
                                              psa_key_slot_t *slot );

psa_status_t psa_driver_wrapper_validate_key( const psa_key_attributes_t *attributes,
                                              const uint8_t *data,
                                              size_t data_length,
                                              size_t *bits );

psa_status_t psa_driver_wrapper_export_public_key( const psa_key_slot_t *slot,
                                                   uint8_t *data,
                                                   size_t data_size,
                                                   size_t *data_length );

/*
 * 密码函数
 */
psa_status_t psa_driver_wrapper_cipher_encrypt(
    psa_key_slot_t *slot,
    psa_algorithm_t alg,
    const uint8_t *input,
    size_t input_length,
    uint8_t *output,
    size_t output_size,
    size_t *output_length );

psa_status_t psa_driver_wrapper_cipher_decrypt(
    psa_key_slot_t *slot,
    psa_algorithm_t alg,
    const uint8_t *input,
    size_t input_length,
    uint8_t *output,
    size_t output_size,
    size_t *output_length );

psa_status_t psa_driver_wrapper_cipher_encrypt_setup(
    psa_operation_driver_context_t *operation,
    psa_key_slot_t *slot,
    psa_algorithm_t alg );

psa_status_t psa_driver_wrapper_cipher_decrypt_setup(
    psa_operation_driver_context_t *operation,
    psa_key_slot_t *slot,
    psa_algorithm_t alg );

psa_status_t psa_driver_wrapper_cipher_generate_iv(
    psa_operation_driver_context_t *operation,
    uint8_t *iv,
    size_t iv_size,
    size_t *iv_length );

psa_status_t psa_driver_wrapper_cipher_set_iv(
    psa_operation_driver_context_t *operation,
    const uint8_t *iv,
    size_t iv_length );

psa_status_t psa_driver_wrapper_cipher_update(
    psa_operation_driver_context_t *operation,
    const uint8_t *input,
    size_t input_length,
    uint8_t *output,
    size_t output_size,
    size_t *output_length );

psa_status_t psa_driver_wrapper_cipher_finish(
    psa_operation_driver_context_t *operation,
    uint8_t *output,
    size_t output_size,
    size_t *output_length );

psa_status_t psa_driver_wrapper_cipher_abort(
    psa_operation_driver_context_t *operation );

#endif /* PSA_CRYPTO_DRIVER_WRAPPERS_H */

/* 自动生成文件的结尾。*/

