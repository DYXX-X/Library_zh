/*
 * 测试驱动程序的哈希驱动程序入口点。
 */
/*  版权所有The Mbed TLS Contributors SPDX许可证标识符：Apache-2.0
 *
 *  根据Apache许可证2.0版（“许可证”）获得许可；除非符合许可证，否则不得使用此文件。您可以在以下地址获取许可证副本：
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 *  除非适用法律要求或书面同意，否则根据许可证分发的软件是按“原样”分发的，无任何明示或暗示的担保或条件。有关许可证下权限和限制的具体语言，请参阅许可证。
 */

#ifndef PSA_CRYPTO_TEST_DRIVERS_HASH_H
#define PSA_CRYPTO_TEST_DRIVERS_HASH_H

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
    /* 计算调用哈希驱动程序入口点的次数。*/
    unsigned long hits;
    /* 上次哈希驱动程序入口点调用返回的状态。*/
    psa_status_t driver_status;
} mbedtls_test_driver_hash_hooks_t;

#define MBEDTLS_TEST_DRIVER_HASH_INIT { 0, 0, 0 }
static inline mbedtls_test_driver_hash_hooks_t
    mbedtls_test_driver_hash_hooks_init( void )
{
    const mbedtls_test_driver_hash_hooks_t v = MBEDTLS_TEST_DRIVER_HASH_INIT;
    return( v );
}

extern mbedtls_test_driver_hash_hooks_t mbedtls_test_driver_hash_hooks;

psa_status_t mbedtls_test_transparent_hash_compute(
    psa_algorithm_t alg,
    const uint8_t *input, size_t input_length,
    uint8_t *hash, size_t hash_size, size_t *hash_length );

psa_status_t mbedtls_test_transparent_hash_setup(
    mbedtls_transparent_test_driver_hash_operation_t *operation,
    psa_algorithm_t alg );

psa_status_t mbedtls_test_transparent_hash_clone(
    const mbedtls_transparent_test_driver_hash_operation_t *source_operation,
    mbedtls_transparent_test_driver_hash_operation_t *target_operation );

psa_status_t mbedtls_test_transparent_hash_update(
    mbedtls_transparent_test_driver_hash_operation_t *operation,
    const uint8_t *input,
    size_t input_length );

psa_status_t mbedtls_test_transparent_hash_finish(
    mbedtls_transparent_test_driver_hash_operation_t *operation,
    uint8_t *hash,
    size_t hash_size,
    size_t *hash_length );

psa_status_t mbedtls_test_transparent_hash_abort(
    mbedtls_transparent_test_driver_hash_operation_t *operation );

#endif /* PSA_CRYPTO_DRIVER_TEST */
#endif /* PSA_CRYPTO_TEST_DRIVERS_HASH_H */

