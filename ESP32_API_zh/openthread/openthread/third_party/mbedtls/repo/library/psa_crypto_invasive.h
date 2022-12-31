/**
 * \文件psa_crypto_invasive.h
 *
 * \PSA密码模块简介：仅用于测试的侵入式接口。
 *
 * 本文件中的接口仅用于测试目的。在带有隔离的集成中，它们不能通过IPC提供给客户端，除非在构建库进行测试时，它们也不能在库集成中提供。
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

#ifndef PSA_CRYPTO_INVASIVE_H
#define PSA_CRYPTO_INVASIVE_H

#if defined(MBEDTLS_CONFIG_FILE)
#include MBEDTLS_CONFIG_FILE
#else
#include "mbedtls/config.h"
#endif

#include "psa/crypto.h"

#include "mbedtls/entropy.h"

/** \brief配置熵源。
 *
 * 此函数只能在调用psa_crypto_init（）之前调用，或者在调用mbedtls_psa_crypto_free（）之后，以及在任何后续调用psa\ycrypto_init（）之前。
 *
 * 此功能仅用于测试目的。它提供的功能对系统集成商也很有用，但系统集成商应该配置熵驱动程序，而不是突破Mbed TLS API。
 *
 * \param entropy_init函数初始化熵上下文并设置所需的熵源。它由psa_crypto_init（）调用。默认情况下，这是mbedtls_entropy_init（）。此函数不能直接报告故障。要指示失败，请将熵上下文设置为mbedtls_entropy_func（）将返回错误的状态。\param entropy_free函数以释放熵上下文和相关资源。它由mbedtls_psa_crypto_free（）调用。默认情况下，这是mbedtls_entropy_free（）。
 *
 * \retval#PSA_SUCCESS成功。\retval#PSA_ERROR_NOT_PERMITTED调用者没有配置熵源的权限。\retval#PSA_ERROR_BAD_STATE库已初始化。
 */
psa_status_t mbedtls_psa_crypto_configure_entropy_sources(
    void (* entropy_init )( mbedtls_entropy_context *ctx ),
    void (* entropy_free )( mbedtls_entropy_context *ctx ) );

#endif /* PSA_CRYPTO_INVASIVE_H */

