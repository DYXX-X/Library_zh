/*
 * mbedtls_psa_external_get_random（）的不安全但独立的实现。仅用于测试！
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

#ifndef FAKE_EXTERNAL_RNG_FOR_TEST_H
#define FAKE_EXTERNAL_RNG_FOR_TEST_H

#if !defined(MBEDTLS_CONFIG_FILE)
#include "mbedtls/config.h"
#else
#include MBEDTLS_CONFIG_FILE
#endif

#if defined(MBEDTLS_PSA_CRYPTO_EXTERNAL_RNG)
/** 启用mbedtls_psa_external_get_random（）的不安全实现。
 *
 * 默认情况下，mbedtls_psa_external_get_random（）的不安全实现被禁用。
 *
 * 当启用MBEDTLS_PSA_CRYPTO_EXTERNAL_RNG并且测试助手链接到程序中时，您必须在运行任何使用PSA子系统生成随机数据的代码之前启用该功能（包括内部随机生成，例如当随机生成通过PSA路由时的盲视）。
 *
 * 无论PSA子系统的状态如何，您都可以随时启用和禁用它。您可以暂时禁用它来模拟耗尽的熵源。
 */
void mbedtls_test_enable_insecure_external_rng( void );

/** 禁用mbedtls_psa_external_get_random（）的不安全实现。
 *
 * 请参见mbedtls_test_enable_insecure_external_rng（）。
 */
void mbedtls_test_disable_insecure_external_rng( void );
#endif /* MBEDTLS_PSA_CRYPTO_EXTERNAL_RNG */

#endif /* FAKE_EXTERNAL_RNG_FOR_TEST_H */

