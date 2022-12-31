/*
 * SPDX文件版权文本：2020-2021浓缩咖啡系统（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */

#ifndef _ESP_ASIO_OPENSSL_STUBS_H
#define _ESP_ASIO_OPENSSL_STUBS_H

/**
 * @note 此标头包含未实现的openssl API，并且仅作为存根提供，或者不提供任何操作，以编译ASIO库，并将其作为ESP平台上的嵌入式应用程序与大多数实际用例一起使用
 */

#if defined(ASIO_USE_WOLFSSL)

#include "wolfssl/ssl.h"
// esp-wolfssl默认禁用文件系统，但ASIO需要ssl文件系统函数来编译
//  -所以我们可以将wolfSSL配置为使用文件系统
//  -或者使用默认的wolfSSL并声明文件系统函数--首选选项，无论何时
//    文件系统函数是从应用程序代码中使用的（如果文件系统中有私钥，则可能会影响安全性）
//    编译失败，出现链接错误。

#if defined(NO_FILESYSTEM)
// 标准esp WolfSSL配置中未包含的WolfSSL方法必须在此处定义
// 作为函数存根，ASIO会编译，但如果使用这些函数，则会出现链接错误。

#ifdef __cplusplus
extern "C" {
#endif

typedef struct WOLFSSL_CTX      WOLFSSL_CTX;

void wolfSSL_CTX_set_verify_depth(WOLFSSL_CTX *ctx,int depth);
int SSL_CTX_load_verify_locations(WOLFSSL_CTX*, const char*, const char*);
int SSL_CTX_use_certificate_file(WOLFSSL_CTX*, const char*, int);
int SSL_CTX_use_certificate_chain_file(WOLFSSL_CTX*, const char*);
int SSL_CTX_use_PrivateKey_file(WOLFSSL_CTX*, const char*, int);
int SSL_CTX_use_RSAPrivateKey_file(WOLFSSL_CTX*, const char*, int);

#if defined(__cplusplus)
} /* 外部C*/
#endif

#endif // NO_FILESYSTEM

#elif defined(ASIO_USE_ESP_OPENSSL)

#include "internal/ssl_x509.h"
#include "internal/ssl_pkey.h"
#include "mbedtls/pem.h"
#include <stdint.h>


#ifdef __cplusplus
extern "C" {
#endif


// 最适用的OpenSSL版本wrtt ASIO用法
#define OPENSSL_VERSION_NUMBER 0x10100001L
// 不支持SSLv2方法
// OpenSSL端口支持：TLS_ANY、TLS_1、TLS_1_1、TLS_1_2、SSL_3
#define OPENSSL_NO_SSL2
#define SSL2_VERSION 0x0002

#define SSL_R_SHORT_READ 219
#define SSL_OP_ALL 0
#define SSL_OP_SINGLE_DH_USE 0
#define SSL_OP_NO_COMPRESSION 0
// 翻译ASIO使用的mbedTLS PEM解析错误
#define PEM_R_NO_START_LINE -MBEDTLS_ERR_PEM_NO_HEADER_FOOTER_PRESENT

#define SSL_OP_NO_SSLv2					0x01000000L
#define SSL_OP_NO_SSLv3					0x02000000L
#define SSL_OP_NO_TLSv1					0x04000000L

#define X509_FILETYPE_PEM	1
#define X509_FILETYPE_ASN1	2
#define SSL_FILETYPE_ASN1	X509_FILETYPE_ASN1
#define SSL_FILETYPE_PEM	X509_FILETYPE_PEM

#define NID_subject_alt_name 85


#define GEN_DNS		2
#define GEN_IPADD	7
#define V_ASN1_OCTET_STRING		4
#define V_ASN1_IA5STRING		22
#define NID_commonName 13

#define SSL_CTX_get_app_data(ctx) ((void*)SSL_CTX_get_ex_data(ctx, 0))

/**
* @brief 释放DH对象--未实现
*
* 当前实现调用SSL_ASSERT
*
* @param r DH对象
*/
void DH_free(DH *r);

/**
 * @brief 释放GENERAL_NAMES--未实现
 *
 * 当前实现调用SSL_ASSERT
 *
 * @param r GENERAL_NAMES对象
 */
void GENERAL_NAMES_free(GENERAL_NAMES * gens);

/**
 * @brief 从X509返回主题名称--未实现
 *
 * 当前实现调用SSL_ASSERT
 *
 * @param r X509对象
 */
X509_NAME *X509_get_subject_name(X509 *a);

/**
 * @brief API仅作为声明证明
 *
 */
int	X509_STORE_CTX_get_error_depth(X509_STORE_CTX *ctx);

/**
 * @brief API仅作为声明证明
 *
 */
int X509_NAME_get_index_by_NID(X509_NAME *name, int nid, int lastpos);

/**
 * @brief API仅作为声明证明
 *
 */
X509_NAME_ENTRY *X509_NAME_get_entry(X509_NAME *name, int loc);

/**
 * @brief API仅作为声明证明
 *
 */
ASN1_STRING *X509_NAME_ENTRY_get_data(X509_NAME_ENTRY *ne);

/**
 * @brief API仅作为声明证明
 *
 */
void *X509_get_ext_d2i(X509 *x, int nid, int *crit, int *idx);

/**
 * @brief API仅作为声明证明
 *
 */
X509 *	X509_STORE_CTX_get_current_cert(X509_STORE_CTX *ctx);

/**
 * @brief 从生物对象读取DH参数--未实现
 *
 * 当前实现调用SSL_ASSERT
 */
DH *PEM_read_bio_DHparams(BIO *bp, DH **x, pem_password_cb *cb, void *u);

/**
 * @brief API仅作为声明证明
 *
 */
void *	X509_STORE_CTX_get_ex_data(X509_STORE_CTX *ctx,int idx);

/**
 * @brief 将DH参数设置为ssl ctx--未实现
 *
 * 当前实现调用SSL_ASSERT
 */
int SSL_CTX_set_tmp_dh(SSL_CTX *ctx, const DH *dh);

/**
 * @brief API仅作为声明证明
 *
 */
void SSL_CTX_set_default_passwd_cb_userdata(SSL_CTX *ctx, void *data);

/**
 * @brief API仅作为声明证明
 *
 */
void SSL_CTX_set_default_passwd_cb(SSL_CTX *ctx, pem_password_cb *cb);

/**
 * @brief 清除与ctx的当前证书关联的任何现有链。
 *
 */
int SSL_CTX_clear_chain_certs(SSL_CTX *ctx);

#if defined(__cplusplus)
} /* 外部C*/
#endif

#endif /* ASIO_USE_ESP_OPENSSL, ASIO_USE_WOLFSSL */
#endif /* _ESP_ASIO_OPENSSL_STUBS_H */

