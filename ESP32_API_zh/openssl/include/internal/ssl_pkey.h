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

#ifndef _SSL_PKEY_H_
#define _SSL_PKEY_H_

#ifdef __cplusplus
 extern "C" {
#endif

#include "ssl_types.h"

/**
 * @brief 根据输入的私钥创建私钥对象
 *
 * @param ipk -输入私钥点
 *
 * @return 新私钥对象点
 */
EVP_PKEY* __EVP_PKEY_new(EVP_PKEY *ipk);

/**
 * @brief 创建私钥对象
 *
 * @param none
 *
 * @return 私钥对象点
 */
EVP_PKEY* EVP_PKEY_new(void);

/**
 * @brief 将字符键上下文加载到系统上下文中。如果'*a'指向私钥，则将密钥加载到其中。或创建新的私钥对象
 *
 * @param type   -私钥类型
 * @param a      -指向私钥的点
 * @param pp     -指向关键上下文记忆点的点
 * @param length -密钥字节
 *
 * @return 私钥对象点
 */
EVP_PKEY* d2i_PrivateKey(int type,
                         EVP_PKEY **a,
                         const unsigned char **pp,
                         long length);

/**
 * @brief 解码缓冲器BIO并将其加载到EVP密钥上下文中。如果'*a'指向私钥，则将密钥加载到其中。或创建新的私钥对象
 *
 * @param bp 包含密钥的BIO对象
 * @param a 指向现有EVP_KEY的指针，如果应创建新密钥，则为NULL
 *
 * @return 已创建或更新EVP_PKEY
 */
EVP_PKEY *d2i_PrivateKey_bio(BIO *bp, EVP_PKEY **a);

/**
 * @brief 与d2i_PrivateKey_bio相同
 *
 * @param bp 包含密钥的BIO对象
 * @param a 指向现有EVP_KEY的指针，如果应创建新密钥，则为NULL
 *
 * @return 已创建或更新EVP_PKEY
 */
RSA *d2i_RSAPrivateKey_bio(BIO *bp,RSA **rsa);

/**
 * @brief 从BIO对象加载PEM格式的私钥
 *
 * @param bp 包含密钥的BIO对象
 * @param x  指向现有PKEY或NULL（如果应创建新密钥）的指针
 * @param cb 密码回调（未使用）
 * @param u 用户上下文（未使用）
 *
 * @return 已创建或更新EVP_PKEY
 */
EVP_PKEY *PEM_read_bio_PrivateKey(BIO *bp, EVP_PKEY **x, pem_password_cb *cb, void *u);

/**
 * @brief BIO对象中PEM格式的RSA密钥
 *
 * @param bp 包含密钥的BIO对象
 * @param x  指向现有PKEY或NULL（如果应创建新密钥）的指针
 * @param cb 密码回调（未使用）
 * @param u 用户上下文（未使用）
 *
 * @return 已创建或更新EVP_PKEY
 */

RSA *PEM_read_bio_RSAPrivateKey(BIO *bp, RSA **rsa, pem_password_cb *cb, void *u);

/**
 * @brief 释放私钥对象
 *
 * @param pkey -私钥对象点
 *
 * @return 没有一个
 */
void EVP_PKEY_free(EVP_PKEY *x);

/**
 * @brief 将私钥加载到SSL
 *
 * @param type -私钥类型
 * @param ssl  -SSL点
 * @param len  -数据字节
 * @param d    -数据点
 *
 * @return 结果0:失败1:OK
 */
 int SSL_use_PrivateKey_ASN1(int type, SSL *ssl, const unsigned char *d, long len);


#ifdef __cplusplus
}
#endif

#endif

