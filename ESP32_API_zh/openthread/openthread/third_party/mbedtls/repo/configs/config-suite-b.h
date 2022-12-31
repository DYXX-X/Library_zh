/**
 * \文件config-suite-bh
 *
 * \TLS NSA Suite B配置文件的简要最低配置（RFC 6460）
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
 * TLS NSA Suite B配置文件的最低配置（RFC 6460）
 *
 * 区别特征：
 * -无RSA或经典DH，完全基于ECC
 * -针对低RAM使用率进行了优化
 *
 * 可能的改进：
 * -如果128位安全性足够，则禁用secp384r1和SHA-512
 * -使用DER格式的嵌入式证书并禁用PEM_PARSE_C和BASE64_C
 *
 * 请参阅自述文件。txt获取使用说明。
 */

#ifndef MBEDTLS_CONFIG_H
#define MBEDTLS_CONFIG_H

/* 系统支持*/
#define MBEDTLS_HAVE_ASM
#define MBEDTLS_HAVE_TIME

/* mbed TLS功能支持*/
#define MBEDTLS_ECP_DP_SECP256R1_ENABLED
#define MBEDTLS_ECP_DP_SECP384R1_ENABLED
#define MBEDTLS_KEY_EXCHANGE_ECDHE_ECDSA_ENABLED
#define MBEDTLS_SSL_PROTO_TLS1_2

/* mbed TLS模块*/
#define MBEDTLS_AES_C
#define MBEDTLS_ASN1_PARSE_C
#define MBEDTLS_ASN1_WRITE_C
#define MBEDTLS_BIGNUM_C
#define MBEDTLS_CIPHER_C
#define MBEDTLS_CTR_DRBG_C
#define MBEDTLS_ECDH_C
#define MBEDTLS_ECDSA_C
#define MBEDTLS_ECP_C
#define MBEDTLS_ENTROPY_C
#define MBEDTLS_GCM_C
#define MBEDTLS_MD_C
#define MBEDTLS_NET_C
#define MBEDTLS_OID_C
#define MBEDTLS_PK_C
#define MBEDTLS_PK_PARSE_C
#define MBEDTLS_SHA256_C
#define MBEDTLS_SHA512_C
#define MBEDTLS_SSL_CLI_C
#define MBEDTLS_SSL_SRV_C
#define MBEDTLS_SSL_TLS_C
#define MBEDTLS_X509_CRT_PARSE_C
#define MBEDTLS_X509_USE_C

/* 对于测试证书*/
#define MBEDTLS_BASE64_C
#define MBEDTLS_CERTS_C
#define MBEDTLS_PEM_PARSE_C

/* 以ROM为代价节省RAM*/
#define MBEDTLS_AES_ROM_TABLES

/* 根据我们的具体需求进行调整，从而节省RAM*/
#define MBEDTLS_ECP_MAX_BITS   384
#define MBEDTLS_MPI_MAX_SIZE    48 // 384位为48字节

/* 以牺牲速度为代价节省RAM，请参见ecp。小时*/
#define MBEDTLS_ECP_WINDOW_SIZE        2
#define MBEDTLS_ECP_FIXED_POINT_OPTIM  0

/* 以牺牲某些ROM为代价，显著提高速度*/
#define MBEDTLS_ECP_NIST_OPTIM

/*
 * 您应该将其调整为您使用的源的确切数量：默认为“mbedtls_platform_entropy_poll”源，但您可能需要添加其他源。熵测试套件的最小值为2。
 */
#define MBEDTLS_ENTROPY_MAX_SOURCES 2

/* 通过指定我们自己的密码套件列表，节省ROM和几个字节的RAM*/
#define MBEDTLS_SSL_CIPHERSUITES                        \
    MBEDTLS_TLS_ECDHE_ECDSA_WITH_AES_256_GCM_SHA384,    \
    MBEDTLS_TLS_ECDHE_ECDSA_WITH_AES_128_GCM_SHA256

/*
 * 以牺牲互操作性为代价节省RAM：只有当您控制连接的两端时才能这样做！（请参阅“mbedtls/ssl.h”中的注释。）这里的最小大小取决于所使用的证书链以及记录的典型大小。
 */
#define MBEDTLS_SSL_MAX_CONTENT_LEN             1024

#include "mbedtls/check_config.h"

#endif /* MBEDTLS_CONFIG_H */

