// 版权所有2015-2016 Espressif Systems（上海）私人有限公司
//
// 根据Apache许可证2.0版（“许可证”）获得许可；
// 除非符合许可证，否则不得使用此文件。
// 您可以在以下地址获取许可证副本：

//     http://www.apache.org/licenses/LICENSE-2.0
//
// 除非适用法律要求或书面同意，软件
// 根据许可证分发的内容是按“原样”分发的，
// 无任何明示或暗示的保证或条件。
// 有关管理权限和
// 许可证下的限制。

#ifndef _SSL_X509_H_
#define _SSL_X509_H_

#ifdef __cplusplus
 extern "C" {
#endif

#include "ssl_types.h"
#include "ssl_stack.h"

DEFINE_STACK_OF(X509_NAME)

/**
 * @brief 根据输入X509认证创建X509认证对象
 *
 * @param ix -输入X509认证点
 *
 * @return 新X509认证对象点
 */
X509* __X509_new(X509 *ix);

/**
 * @brief 创建X509证书对象
 *
 * @param none
 *
 * @return X509认证对象点
 */
X509* X509_new(void);

/**
 * @brief 将字符认证上下文加载到系统上下文中。如果'*cert'指向证书，则将证书加载到其中。或创建新的X509认证对象
 *
 * @param cert   -一点指向X509认证
 * @param buffer -指向认证上下文存储点的点
 * @param length -认证字节
 *
 * @return X509认证对象点
 */
X509* d2i_X509(X509 **cert, const unsigned char *buffer, long len);

/**
 * @brief 释放X509认证对象
 *
 * @param x -X509认证对象点
 *
 * @return 没有一个
 */
void X509_free(X509 *x);

/**
 * @brief 设置SSL上下文客户端CA证书
 *
 * @param ctx -SSL上下文点
 * @param x   -X509认证点
 *
 * @return 结果0:失败1:OK
 */
int SSL_CTX_add_client_CA(SSL_CTX *ctx, X509 *x);

/**
 * @brief 将CA客户端证书添加到SSL中
 *
 * @param ssl -SSL点
 * @param x   -X509认证点
 *
 * @return 结果0:失败1:OK
 */
int SSL_add_client_CA(SSL *ssl, X509 *x);

/**
 * @brief 将证书加载到SSL中
 *
 * @param ssl -SSL点
 * @param len -数据字节
 * @param d   -数据点
 *
 * @return 结果0:失败1:OK
 *
 */
int SSL_use_certificate_ASN1(SSL *ssl, int len, const unsigned char *d);


/**
 * @brief 设置SSL上下文客户端CA证书
 *
 * @param store -指向X509_STORE的指针
 * @param x     -指向X509认证点的指针
 *
 * @return 结果0:失败1:OK
 */
int X509_STORE_add_cert(X509_STORE *store, X509 *x);

/**
 * @brief 将字符认证上下文加载到系统上下文中。
 *
 * 如果“*cert”指向证书，则将证书加载到其中，或创建新的X509证书对象。
 *
 * @param bp     -指向BIO的指针
 * @param buffer -指向认证上下文存储器的指针
 * @param cb     -指向回调的指针，该回调查询用于加密PEM结构的密码短语
 * @param u      -指向应用程序传递给回调的任意数据的指针
 *
 * @return X509认证对象点
 */
X509 * PEM_read_bio_X509(BIO *bp, X509 **x, pem_password_cb cb, void *u);

/**
 * @brief 将字符认证上下文加载到系统上下文中。
 *
 * 当前实现直接调用PEM_read_bio_X509
 *
 * @param bp     -指向BIO的指针
 * @param buffer -指向认证上下文存储器的指针
 * @param cb     -指向回调的指针（未实现）
 * @param u      -指向任意数据的指针（未实现）
 *
 * @return X509认证对象点
 */
X509 *PEM_read_bio_X509_AUX(BIO *bp, X509 **cert, pem_password_cb *cb, void *u);


#ifdef __cplusplus
}
#endif

#endif

