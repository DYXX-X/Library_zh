/**
 * \文件config-ccm-psk-tls1_2.h
 *
 * \具有PSK和AES-CCM密码套件的TLS 1.2的简要最低配置
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
 * 具有PSK和AES-CCM密码套件的TLS 1.2的最低配置区别特征：
 * -没有bignum，没有PK，没有X509
 * -完全现代化和安全（前提是预共享密钥具有高熵）
 * -CCM-8的记录开销非常低
 * -针对低RAM使用率进行了优化
 *
 * 请参阅自述文件。txt获取使用说明。
 */
#ifndef MBEDTLS_CONFIG_H
#define MBEDTLS_CONFIG_H

/* 系统支持*/
//#define MBEDTLS_HAVE_TIME /* 可选用于Hello消息*/
/* 与此配置无关的其他MBEDTLS_HAVE_XXX标志*/

/* mbed TLS功能支持*/
#define MBEDTLS_KEY_EXCHANGE_PSK_ENABLED
#define MBEDTLS_SSL_PROTO_TLS1_2

/* mbed TLS模块*/
#define MBEDTLS_AES_C
#define MBEDTLS_CCM_C
#define MBEDTLS_CIPHER_C
#define MBEDTLS_CTR_DRBG_C
#define MBEDTLS_ENTROPY_C
#define MBEDTLS_MD_C
#define MBEDTLS_NET_C
#define MBEDTLS_SHA256_C
#define MBEDTLS_SSL_CLI_C
#define MBEDTLS_SSL_SRV_C
#define MBEDTLS_SSL_TLS_C

/* 以ROM为代价节省RAM*/
#define MBEDTLS_AES_ROM_TABLES

/* 通过调整以满足您的确切需求，节省一些RAM*/
#define MBEDTLS_PSK_MAX_LEN    16 /* 128位密钥通常就足够了*/

/*
 * 您应该将其调整为所使用的源的确切数量：默认为“platform_entropy_poll”源，但可能需要添加其他源。熵测试套件的最小值为2。
 */
#define MBEDTLS_ENTROPY_MAX_SOURCES 2

/*
 * 只使用CCM_8密码套件，并通过指定自己的密码套件列表来保存ROM和几个字节的RAM
 */
#define MBEDTLS_SSL_CIPHERSUITES                        \
        MBEDTLS_TLS_PSK_WITH_AES_256_CCM_8,             \
        MBEDTLS_TLS_PSK_WITH_AES_128_CCM_8

/*
 * 以牺牲互操作性为代价节省RAM：只有当您控制连接的两端时才能这样做！（请参阅“mbedtls/ssl.h”中的注释。）此处的最佳大小取决于记录的典型大小。
 */
#define MBEDTLS_SSL_MAX_CONTENT_LEN             1024

#include "mbedtls/check_config.h"

#endif /* MBEDTLS_CONFIG_H */

