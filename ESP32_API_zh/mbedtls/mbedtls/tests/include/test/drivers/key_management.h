/*
 * 用于生成和验证密钥的测试驱动程序。
 */
/*  版权所有The Mbed TLS Contributors SPDX许可证标识符：Apache-2.0
 *
 *  根据Apache许可证2.0版（“许可证”）获得许可；除非符合许可证，否则不得使用此文件。您可以在以下地址获取许可证副本：
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 *  除非适用法律要求或书面同意，否则根据许可证分发的软件是按“原样”分发的，无任何明示或暗示的担保或条件。有关许可证下权限和限制的具体语言，请参阅许可证。
 */

#ifndef PSA_CRYPTO_TEST_DRIVERS_KEY_MANAGEMENT_H
#define PSA_CRYPTO_TEST_DRIVERS_KEY_MANAGEMENT_H

#if !defined(MBEDTLS_CONFIG_FILE)
#include "mbedtls/config.h"
#else
#include MBEDTLS_CONFIG_FILE
#endif

#if defined(PSA_CRYPTO_DRIVER_TEST)
#include <psa/crypto_driver_common.h>

#define PSA_CRYPTO_TEST_DRIVER_BUILTIN_AES_KEY_SLOT     0
#define PSA_CRYPTO_TEST_DRIVER_BUILTIN_ECDSA_KEY_SLOT   1

typedef struct {
    /* 如果非空，则在成功时将其复制到输出中。*/
    void *forced_output;
    size_t forced_output_length;
    /* 如果不是PSA_SUCCESS，则返回此错误代码，而不是处理函数调用。*/
    psa_status_t forced_status;
    /* 计算其中一个密钥管理驱动程序函数被调用的次数。*/
    unsigned long hits;
} mbedtls_test_driver_key_management_hooks_t;

#define MBEDTLS_TEST_DRIVER_KEY_MANAGEMENT_INIT { NULL, 0, PSA_SUCCESS, 0 }
static inline mbedtls_test_driver_key_management_hooks_t
    mbedtls_test_driver_key_management_hooks_init( void )
{
    const mbedtls_test_driver_key_management_hooks_t
        v = MBEDTLS_TEST_DRIVER_KEY_MANAGEMENT_INIT;
    return( v );
}

extern mbedtls_test_driver_key_management_hooks_t
    mbedtls_test_driver_key_management_hooks;

psa_status_t mbedtls_test_transparent_init( void );
void mbedtls_test_transparent_free( void );
psa_status_t mbedtls_test_opaque_init( void );
void mbedtls_test_opaque_free( void );

psa_status_t mbedtls_test_transparent_generate_key(
    const psa_key_attributes_t *attributes,
    uint8_t *key, size_t key_size, size_t *key_length );

psa_status_t mbedtls_test_opaque_generate_key(
    const psa_key_attributes_t *attributes,
    uint8_t *key, size_t key_size, size_t *key_length );

psa_status_t mbedtls_test_opaque_export_key(
    const psa_key_attributes_t *attributes,
    const uint8_t *key, size_t key_length,
    uint8_t *data, size_t data_size, size_t *data_length );

psa_status_t mbedtls_test_transparent_export_public_key(
    const psa_key_attributes_t *attributes,
    const uint8_t *key, size_t key_length,
    uint8_t *data, size_t data_size, size_t *data_length );

psa_status_t mbedtls_test_opaque_export_public_key(
    const psa_key_attributes_t *attributes,
    const uint8_t *key, size_t key_length,
    uint8_t *data, size_t data_size, size_t *data_length );

psa_status_t mbedtls_test_transparent_import_key(
    const psa_key_attributes_t *attributes,
    const uint8_t *data,
    size_t data_length,
    uint8_t *key_buffer,
    size_t key_buffer_size,
    size_t *key_buffer_length,
    size_t *bits);

psa_status_t mbedtls_test_opaque_get_builtin_key(
    psa_drv_slot_number_t slot_number,
    psa_key_attributes_t *attributes,
    uint8_t *key_buffer, size_t key_buffer_size, size_t *key_buffer_length );

#endif /* PSA_CRYPTO_DRIVER_TEST */
#endif /* PSA_CRYPTO_TEST_DRIVERS_KEY_MANAGEMENT_H */

