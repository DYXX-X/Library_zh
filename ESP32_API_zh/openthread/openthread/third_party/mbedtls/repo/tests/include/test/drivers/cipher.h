/*
 * 密码功能的测试驱动程序
 */
/*  版权所有The Mbed TLS Contributors SPDX许可证标识符：Apache-2.0
 *
 *  根据Apache许可证2.0版（“许可证”）获得许可；除非符合许可证，否则不得使用此文件。您可以在以下地址获取许可证副本：
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 *  除非适用法律要求或书面同意，否则根据许可证分发的软件是按“原样”分发的，无任何明示或暗示的担保或条件。有关许可证下权限和限制的具体语言，请参阅许可证。
 */

#ifndef PSA_CRYPTO_TEST_DRIVERS_CIPHER_H
#define PSA_CRYPTO_TEST_DRIVERS_CIPHER_H

#if !defined(MBEDTLS_CONFIG_FILE)
#include "mbedtls/config.h"
#else
#include MBEDTLS_CONFIG_FILE
#endif

#if defined(PSA_CRYPTO_DRIVER_TEST)
#include <psa/crypto_driver_common.h>

#include "mbedtls/cipher.h"
typedef struct {
    psa_algorithm_t alg;
    unsigned int key_set : 1;
    unsigned int iv_required : 1;
    unsigned int iv_set : 1;
    uint8_t iv_size;
    uint8_t block_size;
    mbedtls_cipher_context_t cipher;
} test_transparent_cipher_operation_t;

typedef struct{
    unsigned int initialised : 1;
    test_transparent_cipher_operation_t ctx;
} test_opaque_cipher_operation_t;

typedef struct {
    /* 如果非空，则在成功时将其复制到输出中。*/
    void *forced_output;
    size_t forced_output_length;
    /* 如果不是PSA_SUCCESS，则返回此错误代码，而不是处理函数调用。*/
    psa_status_t forced_status;
    /* 计算调用其中一个密码驱动程序函数的次数。*/
    unsigned long hits;
} test_driver_cipher_hooks_t;

#define TEST_DRIVER_CIPHER_INIT { NULL, 0, PSA_SUCCESS, 0 }
static inline test_driver_cipher_hooks_t test_driver_cipher_hooks_init( void )
{
    const test_driver_cipher_hooks_t v = TEST_DRIVER_CIPHER_INIT;
    return( v );
}

extern test_driver_cipher_hooks_t test_driver_cipher_hooks;

psa_status_t test_transparent_cipher_encrypt(
    const psa_key_attributes_t *attributes,
    const uint8_t *key, size_t key_length,
    psa_algorithm_t alg,
    const uint8_t *input, size_t input_length,
    uint8_t *output, size_t output_size, size_t *output_length);

psa_status_t test_transparent_cipher_decrypt(
    const psa_key_attributes_t *attributes,
    const uint8_t *key, size_t key_length,
    psa_algorithm_t alg,
    const uint8_t *input, size_t input_length,
    uint8_t *output, size_t output_size, size_t *output_length);

psa_status_t test_transparent_cipher_encrypt_setup(
    test_transparent_cipher_operation_t *operation,
    const psa_key_attributes_t *attributes,
    const uint8_t *key, size_t key_length,
    psa_algorithm_t alg);

psa_status_t test_transparent_cipher_decrypt_setup(
    test_transparent_cipher_operation_t *operation,
    const psa_key_attributes_t *attributes,
    const uint8_t *key, size_t key_length,
    psa_algorithm_t alg);

psa_status_t test_transparent_cipher_abort(
    test_transparent_cipher_operation_t *operation);

psa_status_t test_transparent_cipher_generate_iv(
    test_transparent_cipher_operation_t *operation,
    uint8_t *iv,
    size_t iv_size,
    size_t *iv_length);

psa_status_t test_transparent_cipher_set_iv(
    test_transparent_cipher_operation_t *operation,
    const uint8_t *iv,
    size_t iv_length);

psa_status_t test_transparent_cipher_update(
    test_transparent_cipher_operation_t *operation,
    const uint8_t *input,
    size_t input_length,
    uint8_t *output,
    size_t output_size,
    size_t *output_length);

psa_status_t test_transparent_cipher_finish(
    test_transparent_cipher_operation_t *operation,
    uint8_t *output,
    size_t output_size,
    size_t *output_length);

/*
 * 不透明版本
 */
psa_status_t test_opaque_cipher_encrypt(
    const psa_key_attributes_t *attributes,
    const uint8_t *key, size_t key_length,
    psa_algorithm_t alg,
    const uint8_t *input, size_t input_length,
    uint8_t *output, size_t output_size, size_t *output_length);

psa_status_t test_opaque_cipher_decrypt(
    const psa_key_attributes_t *attributes,
    const uint8_t *key, size_t key_length,
    psa_algorithm_t alg,
    const uint8_t *input, size_t input_length,
    uint8_t *output, size_t output_size, size_t *output_length);

psa_status_t test_opaque_cipher_encrypt_setup(
    test_opaque_cipher_operation_t *operation,
    const psa_key_attributes_t *attributes,
    const uint8_t *key, size_t key_length,
    psa_algorithm_t alg);

psa_status_t test_opaque_cipher_decrypt_setup(
    test_opaque_cipher_operation_t *operation,
    const psa_key_attributes_t *attributes,
    const uint8_t *key, size_t key_length,
    psa_algorithm_t alg);

psa_status_t test_opaque_cipher_abort(
    test_opaque_cipher_operation_t *operation);

psa_status_t test_opaque_cipher_generate_iv(
    test_opaque_cipher_operation_t *operation,
    uint8_t *iv,
    size_t iv_size,
    size_t *iv_length);

psa_status_t test_opaque_cipher_set_iv(
    test_opaque_cipher_operation_t *operation,
    const uint8_t *iv,
    size_t iv_length);

psa_status_t test_opaque_cipher_update(
    test_opaque_cipher_operation_t *operation,
    const uint8_t *input,
    size_t input_length,
    uint8_t *output,
    size_t output_size,
    size_t *output_length);

psa_status_t test_opaque_cipher_finish(
    test_opaque_cipher_operation_t *operation,
    uint8_t *output,
    size_t output_size,
    size_t *output_length);

#endif /* PSA_CRYPTO_DRIVER_TEST */
#endif /* PSA_CRYPTO_TEST_DRIVERS_CIPHER_H */

