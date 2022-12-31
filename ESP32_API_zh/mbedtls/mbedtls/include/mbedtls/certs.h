/**
 * \文件证书.h
 *
 * \用于测试的简要样品证书和DHM参数
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
#ifndef MBEDTLS_CERTS_H
#define MBEDTLS_CERTS_H

#if !defined(MBEDTLS_CONFIG_FILE)
#include "mbedtls/config.h"
#else
#include MBEDTLS_CONFIG_FILE
#endif

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

/* 所有PEM编码CA证书的列表，以NULL结尾；如果启用了MBEDTLS_PEM_PARSE_C，则PEM编码，否则DER编码。*/
extern const char * mbedtls_test_cas[];
extern const size_t mbedtls_test_cas_len[];

/* 所有DER编码CA证书的列表，以NULL结尾*/
extern const unsigned char * mbedtls_test_cas_der[];
extern const size_t mbedtls_test_cas_der_len[];

#if defined(MBEDTLS_PEM_PARSE_C)
/* PEM格式的所有CA证书的级联（如果可用）*/
extern const char   mbedtls_test_cas_pem[];
extern const size_t mbedtls_test_cas_pem_len;
#endif /* MBEDTLS_PEM_PARSE_C */

/*
 * CA测试证书
 */

extern const char mbedtls_test_ca_crt_ec_pem[];
extern const char mbedtls_test_ca_key_ec_pem[];
extern const char mbedtls_test_ca_pwd_ec_pem[];
extern const char mbedtls_test_ca_key_rsa_pem[];
extern const char mbedtls_test_ca_pwd_rsa_pem[];
extern const char mbedtls_test_ca_crt_rsa_sha1_pem[];
extern const char mbedtls_test_ca_crt_rsa_sha256_pem[];

extern const unsigned char mbedtls_test_ca_crt_ec_der[];
extern const unsigned char mbedtls_test_ca_key_ec_der[];
extern const unsigned char mbedtls_test_ca_key_rsa_der[];
extern const unsigned char mbedtls_test_ca_crt_rsa_sha1_der[];
extern const unsigned char mbedtls_test_ca_crt_rsa_sha256_der[];

extern const size_t mbedtls_test_ca_crt_ec_pem_len;
extern const size_t mbedtls_test_ca_key_ec_pem_len;
extern const size_t mbedtls_test_ca_pwd_ec_pem_len;
extern const size_t mbedtls_test_ca_key_rsa_pem_len;
extern const size_t mbedtls_test_ca_pwd_rsa_pem_len;
extern const size_t mbedtls_test_ca_crt_rsa_sha1_pem_len;
extern const size_t mbedtls_test_ca_crt_rsa_sha256_pem_len;

extern const size_t mbedtls_test_ca_crt_ec_der_len;
extern const size_t mbedtls_test_ca_key_ec_der_len;
extern const size_t mbedtls_test_ca_pwd_ec_der_len;
extern const size_t mbedtls_test_ca_key_rsa_der_len;
extern const size_t mbedtls_test_ca_pwd_rsa_der_len;
extern const size_t mbedtls_test_ca_crt_rsa_sha1_der_len;
extern const size_t mbedtls_test_ca_crt_rsa_sha256_der_len;

/* PEM和DER编码之间的配置相关调度（如果启用PEM，则为DER）*/

extern const char mbedtls_test_ca_crt_ec[];
extern const char mbedtls_test_ca_key_ec[];
extern const char mbedtls_test_ca_pwd_ec[];
extern const char mbedtls_test_ca_key_rsa[];
extern const char mbedtls_test_ca_pwd_rsa[];
extern const char mbedtls_test_ca_crt_rsa_sha1[];
extern const char mbedtls_test_ca_crt_rsa_sha256[];

extern const size_t mbedtls_test_ca_crt_ec_len;
extern const size_t mbedtls_test_ca_key_ec_len;
extern const size_t mbedtls_test_ca_pwd_ec_len;
extern const size_t mbedtls_test_ca_key_rsa_len;
extern const size_t mbedtls_test_ca_pwd_rsa_len;
extern const size_t mbedtls_test_ca_crt_rsa_sha1_len;
extern const size_t mbedtls_test_ca_crt_rsa_sha256_len;

/* SHA-1和SHA-256之间的配置相关调度（如果启用了SHA-256，则为SHA-1）*/

extern const char mbedtls_test_ca_crt_rsa[];
extern const size_t mbedtls_test_ca_crt_rsa_len;

/* EC和RSA之间依赖于配置的分派（如果启用了RSA，则为RSA，否则为EC）*/

extern const char * mbedtls_test_ca_crt;
extern const char * mbedtls_test_ca_key;
extern const char * mbedtls_test_ca_pwd;
extern const size_t mbedtls_test_ca_crt_len;
extern const size_t mbedtls_test_ca_key_len;
extern const size_t mbedtls_test_ca_pwd_len;

/*
 * 服务器测试证书
 */

extern const char mbedtls_test_srv_crt_ec_pem[];
extern const char mbedtls_test_srv_key_ec_pem[];
extern const char mbedtls_test_srv_pwd_ec_pem[];
extern const char mbedtls_test_srv_key_rsa_pem[];
extern const char mbedtls_test_srv_pwd_rsa_pem[];
extern const char mbedtls_test_srv_crt_rsa_sha1_pem[];
extern const char mbedtls_test_srv_crt_rsa_sha256_pem[];

extern const unsigned char mbedtls_test_srv_crt_ec_der[];
extern const unsigned char mbedtls_test_srv_key_ec_der[];
extern const unsigned char mbedtls_test_srv_key_rsa_der[];
extern const unsigned char mbedtls_test_srv_crt_rsa_sha1_der[];
extern const unsigned char mbedtls_test_srv_crt_rsa_sha256_der[];

extern const size_t mbedtls_test_srv_crt_ec_pem_len;
extern const size_t mbedtls_test_srv_key_ec_pem_len;
extern const size_t mbedtls_test_srv_pwd_ec_pem_len;
extern const size_t mbedtls_test_srv_key_rsa_pem_len;
extern const size_t mbedtls_test_srv_pwd_rsa_pem_len;
extern const size_t mbedtls_test_srv_crt_rsa_sha1_pem_len;
extern const size_t mbedtls_test_srv_crt_rsa_sha256_pem_len;

extern const size_t mbedtls_test_srv_crt_ec_der_len;
extern const size_t mbedtls_test_srv_key_ec_der_len;
extern const size_t mbedtls_test_srv_pwd_ec_der_len;
extern const size_t mbedtls_test_srv_key_rsa_der_len;
extern const size_t mbedtls_test_srv_pwd_rsa_der_len;
extern const size_t mbedtls_test_srv_crt_rsa_sha1_der_len;
extern const size_t mbedtls_test_srv_crt_rsa_sha256_der_len;

/* PEM和DER编码之间的配置相关调度（如果启用PEM，则为DER）*/

extern const char mbedtls_test_srv_crt_ec[];
extern const char mbedtls_test_srv_key_ec[];
extern const char mbedtls_test_srv_pwd_ec[];
extern const char mbedtls_test_srv_key_rsa[];
extern const char mbedtls_test_srv_pwd_rsa[];
extern const char mbedtls_test_srv_crt_rsa_sha1[];
extern const char mbedtls_test_srv_crt_rsa_sha256[];

extern const size_t mbedtls_test_srv_crt_ec_len;
extern const size_t mbedtls_test_srv_key_ec_len;
extern const size_t mbedtls_test_srv_pwd_ec_len;
extern const size_t mbedtls_test_srv_key_rsa_len;
extern const size_t mbedtls_test_srv_pwd_rsa_len;
extern const size_t mbedtls_test_srv_crt_rsa_sha1_len;
extern const size_t mbedtls_test_srv_crt_rsa_sha256_len;

/* SHA-1和SHA-256之间的配置相关调度（如果启用了SHA-256，则为SHA-1）*/

extern const char mbedtls_test_srv_crt_rsa[];
extern const size_t mbedtls_test_srv_crt_rsa_len;

/* EC和RSA之间依赖于配置的分派（如果启用了RSA，则为RSA，否则为EC）*/

extern const char * mbedtls_test_srv_crt;
extern const char * mbedtls_test_srv_key;
extern const char * mbedtls_test_srv_pwd;
extern const size_t mbedtls_test_srv_crt_len;
extern const size_t mbedtls_test_srv_key_len;
extern const size_t mbedtls_test_srv_pwd_len;

/*
 * 客户端测试证书
 */

extern const char mbedtls_test_cli_crt_ec_pem[];
extern const char mbedtls_test_cli_key_ec_pem[];
extern const char mbedtls_test_cli_pwd_ec_pem[];
extern const char mbedtls_test_cli_key_rsa_pem[];
extern const char mbedtls_test_cli_pwd_rsa_pem[];
extern const char mbedtls_test_cli_crt_rsa_pem[];

extern const unsigned char mbedtls_test_cli_crt_ec_der[];
extern const unsigned char mbedtls_test_cli_key_ec_der[];
extern const unsigned char mbedtls_test_cli_key_rsa_der[];
extern const unsigned char mbedtls_test_cli_crt_rsa_der[];

extern const size_t mbedtls_test_cli_crt_ec_pem_len;
extern const size_t mbedtls_test_cli_key_ec_pem_len;
extern const size_t mbedtls_test_cli_pwd_ec_pem_len;
extern const size_t mbedtls_test_cli_key_rsa_pem_len;
extern const size_t mbedtls_test_cli_pwd_rsa_pem_len;
extern const size_t mbedtls_test_cli_crt_rsa_pem_len;

extern const size_t mbedtls_test_cli_crt_ec_der_len;
extern const size_t mbedtls_test_cli_key_ec_der_len;
extern const size_t mbedtls_test_cli_key_rsa_der_len;
extern const size_t mbedtls_test_cli_crt_rsa_der_len;

/* PEM和DER编码之间的配置相关调度（如果启用PEM，则为DER）*/

extern const char mbedtls_test_cli_crt_ec[];
extern const char mbedtls_test_cli_key_ec[];
extern const char mbedtls_test_cli_pwd_ec[];
extern const char mbedtls_test_cli_key_rsa[];
extern const char mbedtls_test_cli_pwd_rsa[];
extern const char mbedtls_test_cli_crt_rsa[];

extern const size_t mbedtls_test_cli_crt_ec_len;
extern const size_t mbedtls_test_cli_key_ec_len;
extern const size_t mbedtls_test_cli_pwd_ec_len;
extern const size_t mbedtls_test_cli_key_rsa_len;
extern const size_t mbedtls_test_cli_pwd_rsa_len;
extern const size_t mbedtls_test_cli_crt_rsa_len;

/* EC和RSA之间依赖于配置的分派（如果启用了RSA，则为RSA，否则为EC）*/

extern const char * mbedtls_test_cli_crt;
extern const char * mbedtls_test_cli_key;
extern const char * mbedtls_test_cli_pwd;
extern const size_t mbedtls_test_cli_crt_len;
extern const size_t mbedtls_test_cli_key_len;
extern const size_t mbedtls_test_cli_pwd_len;

#ifdef __cplusplus
}
#endif

#endif /* 证书.h*/

