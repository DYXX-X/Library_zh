/* MBEDTLS_USER_CONFIG_FILE用于测试。仅用于少数测试配置。
 *
 * 典型用法（注意多个引用级别）：make CFLAGS=“'-DMBEDTLS_USER_CONFIG_FILE=\”../tests/configs/USER CONFIG for test.h\“'”
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

#if defined(PSA_CRYPTO_DRIVER_TEST_ALL)

/* 允许在库中使用测试驱动程序，并构建测试驱动程序的通用部分。*/
#define PSA_CRYPTO_DRIVER_TEST

/* 为测试驱动程序实现的所有加密机制使用加速器驱动程序。*/
#define MBEDTLS_PSA_ACCEL_KEY_TYPE_AES
#define MBEDTLS_PSA_ACCEL_KEY_TYPE_CAMELLIA
#define MBEDTLS_PSA_ACCEL_KEY_TYPE_ECC_KEY_PAIR
#define MBEDTLS_PSA_ACCEL_KEY_TYPE_RSA_KEY_PAIR
#define MBEDTLS_PSA_ACCEL_ALG_CBC_NO_PADDING
#define MBEDTLS_PSA_ACCEL_ALG_CBC_PKCS7
#define MBEDTLS_PSA_ACCEL_ALG_CTR
#define MBEDTLS_PSA_ACCEL_ALG_CFB
#define MBEDTLS_PSA_ACCEL_ALG_ECDSA
#define MBEDTLS_PSA_ACCEL_ALG_DETERMINISTIC_ECDSA
#define MBEDTLS_PSA_ACCEL_ALG_MD2
#define MBEDTLS_PSA_ACCEL_ALG_MD4
#define MBEDTLS_PSA_ACCEL_ALG_MD5
#define MBEDTLS_PSA_ACCEL_ALG_OFB
#define MBEDTLS_PSA_ACCEL_ALG_RIPEMD160
#define MBEDTLS_PSA_ACCEL_ALG_RSA_PKCS1V15_SIGN
#define MBEDTLS_PSA_ACCEL_ALG_RSA_PSS
#define MBEDTLS_PSA_ACCEL_ALG_SHA_1
#define MBEDTLS_PSA_ACCEL_ALG_SHA_224
#define MBEDTLS_PSA_ACCEL_ALG_SHA_256
#define MBEDTLS_PSA_ACCEL_ALG_SHA_384
#define MBEDTLS_PSA_ACCEL_ALG_SHA_512
#define MBEDTLS_PSA_ACCEL_ALG_XTS
#define MBEDTLS_PSA_ACCEL_ALG_CMAC
#define MBEDTLS_PSA_ACCEL_ALG_HMAC

#endif  /* PSA_CRYPTO_DRIVER_TEST_ALL */

