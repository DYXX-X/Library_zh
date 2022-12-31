/**
 * \文件check_crypto_config.h
 *
 * \PSA配置选项的简短一致性检查
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

/*
 * 建议在crypto_config中包含此文件。h，以便及早发现依赖性问题。
 */

#ifndef MBEDTLS_CHECK_CRYPTO_CONFIG_H
#define MBEDTLS_CHECK_CRYPTO_CONFIG_H

#if defined(PSA_WANT_ALG_CCM) && \
    !( defined(PSA_WANT_KEY_TYPE_AES) || \
       defined(PSA_WANT_KEY_TYPE_CAMELLIA) )
#error "PSA_WANT_ALG_CCM defined, but not all prerequisites"
#endif

#if defined(PSA_WANT_ALG_CMAC) && \
    !( defined(PSA_WANT_KEY_TYPE_AES) || \
       defined(PSA_WANT_KEY_TYPE_CAMELLIA) || \
       defined(PSA_WANT_KEY_TYPE_DES) )
#error "PSA_WANT_ALG_CMAC defined, but not all prerequisites"
#endif

#if defined(PSA_WANT_ALG_DETERMINISTIC_ECDSA) && \
    !( defined(PSA_WANT_KEY_TYPE_ECC_KEY_PAIR) || \
       defined(PSA_WANT_KEY_TYPE_ECC_PUBLIC_KEY) )
#error "PSA_WANT_ALG_DETERMINISTIC_ECDSA defined, but not all prerequisites"
#endif

#if defined(PSA_WANT_ALG_ECDSA) && \
    !( defined(PSA_WANT_KEY_TYPE_ECC_KEY_PAIR) || \
       defined(PSA_WANT_KEY_TYPE_ECC_PUBLIC_KEY) )
#error "PSA_WANT_ALG_ECDSA defined, but not all prerequisites"
#endif

#if defined(PSA_WANT_ALG_GCM) && \
    !( defined(PSA_WANT_KEY_TYPE_AES) || \
       defined(PSA_WANT_KEY_TYPE_CAMELLIA) )
#error "PSA_WANT_ALG_GCM defined, but not all prerequisites"
#endif

#if defined(PSA_WANT_ALG_RSA_PKCS1V15_CRYPT) && \
    !( defined(PSA_WANT_KEY_TYPE_RSA_KEY_PAIR) || \
       defined(PSA_WANT_KEY_TYPE_RSA_PUBLIC_KEY) )
#error "PSA_WANT_ALG_RSA_PKCS1V15_CRYPT defined, but not all prerequisites"
#endif

#if defined(PSA_WANT_ALG_RSA_PKCS1V15_SIGN) && \
    !( defined(PSA_WANT_KEY_TYPE_RSA_KEY_PAIR) || \
       defined(PSA_WANT_KEY_TYPE_RSA_PUBLIC_KEY) )
#error "PSA_WANT_ALG_RSA_PKCS1V15_SIGN defined, but not all prerequisites"
#endif

#if defined(PSA_WANT_ALG_RSA_OAEP) && \
    !( defined(PSA_WANT_KEY_TYPE_RSA_KEY_PAIR) || \
       defined(PSA_WANT_KEY_TYPE_RSA_PUBLIC_KEY) )
#error "PSA_WANT_ALG_RSA_OAEP defined, but not all prerequisites"
#endif

#if defined(PSA_WANT_ALG_RSA_PSS) && \
    !( defined(PSA_WANT_KEY_TYPE_RSA_KEY_PAIR) || \
       defined(PSA_WANT_KEY_TYPE_RSA_PUBLIC_KEY) )
#error "PSA_WANT_ALG_RSA_PSS defined, but not all prerequisites"
#endif

#if defined(PSA_WANT_KEY_TYPE_ECC_KEY_PAIR) && \
    !defined(PSA_WANT_KEY_TYPE_ECC_PUBLIC_KEY)
#error "PSA_WANT_KEY_TYPE_ECC_KEY_PAIR defined, but not all prerequisites"
#endif

#endif /* MBEDTLS_CHECK_CRYPTO_CONFIG_H */

