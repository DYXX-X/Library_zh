/*
 * 上下文大小函数的测试驱动程序
 */
/*  版权所有The Mbed TLS Contributors SPDX许可证标识符：Apache-2.0
 *
 *  根据Apache许可证2.0版（“许可证”）获得许可；除非符合许可证，否则不得使用此文件。您可以在以下地址获取许可证副本：
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 *  除非适用法律要求或书面同意，否则根据许可证分发的软件是按“原样”分发的，无任何明示或暗示的担保或条件。有关许可证下权限和限制的具体语言，请参阅许可证。
 */

#ifndef PSA_CRYPTO_TEST_DRIVERS_SIZE_H
#define PSA_CRYPTO_TEST_DRIVERS_SIZE_H

#if !defined(MBEDTLS_CONFIG_FILE)
#include "mbedtls/config.h"
#else
#include MBEDTLS_CONFIG_FILE
#endif

#if defined(PSA_CRYPTO_DRIVER_TEST)
#include <psa/crypto_driver_common.h>

typedef struct {
    unsigned int context;
} test_driver_key_context_t;

/** \定义TEST_DRIVER_KEY_CONTEXT_BASE_SIZE
 *
 * 此宏返回键上下文的基本大小。它是存储在每个键上下文中的驱动程序特定信息的大小。
 */
#define TEST_DRIVER_KEY_CONTEXT_BASE_SIZE          sizeof( test_driver_key_context_t )

/** \定义TEST_DRIVER_KEY_CONTEXT_KEY_PAIR_SIZE
 *
 * 密钥对的每个密钥上下文中包含的字节数。
 *
 * 此对大小适用于ECC 256位私钥/公钥对。基于该值，可以通过从该值中减去以下公钥大小来导出私钥的大小。
 */

#define TEST_DRIVER_KEY_CONTEXT_KEY_PAIR_SIZE      65

/** \定义TEST_DRIVER_KEY_CONTEXT_PUBLIC_KEY_SIZE
 *
 * 公钥的每个密钥上下文中包含的字节数。
 *
 * 对于ECC公钥，它需要257位，因此需要33字节。
 */
#define TEST_DRIVER_KEY_CONTEXT_PUBLIC_KEY_SIZE    33

/** \定义TEST_DRIVER_KEY_CONTEXT_SYMMETRIC_FACTOR
 *
 * 对称密钥的每个密钥上下文都包含此密钥大小的许多倍。
 */
#define TEST_DRIVER_KEY_CONTEXT_SYMMETRIC_FACTOR   0

/** \定义TEST_DRIVER_KEY_CONTEXT_STORE_PUBLIC_KEY
 *
 * 如果这对于密钥对是真的，则密钥上下文包含公钥的空间。如果为false，则不会为公钥添加额外的空间。
 *
 * 对于此实例，将公钥与私钥一起存储。
 */
#define TEST_DRIVER_KEY_CONTEXT_STORE_PUBLIC_KEY   1

/** \定义TEST_DRIVER_KEY_CONTEXT_SIZE_FUNCTION
 *
 * 如果定义了TEST_DRIVER_KEY_CONTEXT_SIZE_FUNCTION，测试驱动程序将提供SIZE_FUNCTION入口点，否则将不提供。
 *
 * 一些不透明的驱动程序需要支持密钥和上下文信息存储的自定义大小。size_function提供了提供定制的能力。
 */
//#定义TEST_DRIVER_KEY_CONTEXT_SIZE_FUNCTION

#ifdef TEST_DRIVER_KEY_CONTEXT_SIZE_FUNCTION
size_t test_size_function(
    const psa_key_type_t key_type,
    const size_t key_bits );
#endif /* TEST_DRIVER_KEY_CONTEXT_SIZE_FUNCTION */

#endif /* PSA_CRYPTO_DRIVER_TEST */
#endif /* PSA_CRYPTO_TEST_DRIVERS_SIZE_H */

