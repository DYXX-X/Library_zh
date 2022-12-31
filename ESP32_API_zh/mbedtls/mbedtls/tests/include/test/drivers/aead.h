/*
 * 测试驾驶员AEAD驾驶员入口点。
 */
/*  版权所有The Mbed TLS Contributors SPDX许可证标识符：Apache-2.0
 *
 *  根据Apache许可证2.0版（“许可证”）获得许可；除非符合许可证，否则不得使用此文件。您可以在以下地址获取许可证副本：
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 *  除非适用法律要求或书面同意，否则根据许可证分发的软件是按“原样”分发的，无任何明示或暗示的担保或条件。有关许可证下权限和限制的具体语言，请参阅许可证。
 */

#ifndef PSA_CRYPTO_TEST_DRIVERS_AEAD_H
#define PSA_CRYPTO_TEST_DRIVERS_AEAD_H

#if !defined(MBEDTLS_CONFIG_FILE)
#include "mbedtls/config.h"
#else
#include MBEDTLS_CONFIG_FILE
#endif

#if defined(PSA_CRYPTO_DRIVER_TEST)
#include <psa/crypto_driver_common.h>

typedef struct {
    /* 如果不是PSA_SUCCESS，则返回此错误代码，而不是处理函数调用。*/
    psa_status_t forced_status;
    /* 计算调用AEAD驱动程序函数的次数。*/
    unsigned long hits;
    /* 上次AEAD驱动程序函数调用返回的状态。*/
    psa_status_t driver_status;
} mbedtls_test_driver_aead_hooks_t;

#define MBEDTLS_TEST_DRIVER_AEAD_INIT { 0, 0, 0 }
static inline mbedtls_test_driver_aead_hooks_t
    mbedtls_test_driver_aead_hooks_init( void )
{
    const mbedtls_test_driver_aead_hooks_t v = MBEDTLS_TEST_DRIVER_AEAD_INIT;
    return( v );
}

extern mbedtls_test_driver_aead_hooks_t mbedtls_test_driver_aead_hooks;

psa_status_t mbedtls_test_transparent_aead_encrypt(
    const psa_key_attributes_t *attributes,
    const uint8_t *key_buffer, size_t key_buffer_size,
    psa_algorithm_t alg,
    const uint8_t *nonce, size_t nonce_length,
    const uint8_t *additional_data, size_t additional_data_length,
    const uint8_t *plaintext, size_t plaintext_length,
    uint8_t *ciphertext, size_t ciphertext_size, size_t *ciphertext_length );

psa_status_t mbedtls_test_transparent_aead_decrypt(
    const psa_key_attributes_t *attributes,
    const uint8_t *key_buffer, size_t key_buffer_size,
    psa_algorithm_t alg,
    const uint8_t *nonce, size_t nonce_length,
    const uint8_t *additional_data, size_t additional_data_length,
    const uint8_t *ciphertext, size_t ciphertext_length,
    uint8_t *plaintext, size_t plaintext_size, size_t *plaintext_length );

#endif /* PSA_CRYPTO_DRIVER_TEST */
#endif /* PSA_CRYPTO_TEST_DRIVERS_AEAD_H */

