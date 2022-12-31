/*
 * SPDX文件版权文本：2015-2021浓缩咖啡系统（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */

#if !defined(ESP_OPENSSL_SUPPRESS_LEGACY_WARNING)
#warning "OpenSSL component will be removed from ESP-IDF in v5.0, please use esp_tls instead"
#endif

#ifndef _SSL_H_
#define _SSL_H_

#ifdef __cplusplus
 extern "C" {
#endif

#include "internal/ssl_x509.h"
#include "internal/ssl_pkey.h"
#include "openssl/bio.h"
#include "openssl/err.h"

/*
{
*/

#define SSL_CB_ALERT 0x4000

#define X509_CHECK_FLAG_ALWAYS_CHECK_SUBJECT		(1 << 0)
#define X509_CHECK_FLAG_NO_WILDCARDS			(1 << 1)
#define X509_CHECK_FLAG_NO_PARTIAL_WILDCARDS		(1 << 2)
#define X509_CHECK_FLAG_MULTI_LABEL_WILDCARDS		(1 << 3)
#define X509_CHECK_FLAG_SINGLE_LABEL_SUBDOMAINS		(1 << 4)

/**
 * @brief 创建SSL上下文
 *
 * @param method -SSL上下文方法点
 *
 * @return 上下文点
 */
SSL_CTX* SSL_CTX_new(const SSL_METHOD *method);

/**
 * @brief 释放SSL上下文
 *
 * @param method -SSL上下文点
 *
 * @return 没有一个
 */
void SSL_CTX_free(SSL_CTX *ctx);

/**
 * @brief 创建SSL
 *
 * @param ctx -SSL上下文点
 *
 * @return SSL点
 */
SSL* SSL_new(SSL_CTX *ctx);

/**
 * @brief 释放SSL
 *
 * @param ssl -SSL点
 *
 * @return 没有一个
 */
void SSL_free(SSL *ssl);

/**
 * @brief 连接到远程SSL服务器
 *
 * @param ssl -SSL点
 *
 * @return 结果1：正常
 *    -1：失败
 */
int SSL_connect(SSL *ssl);

/**
 * @brief 接受远程连接
 *
 * @param ssl -SSL点
 *
 * @return 结果1：正常
 *    -1：失败
 */
int SSL_accept(SSL *ssl);

/**
 * @brief 从远程读取数据
 *
 * @param ssl    -已连接的SSL点
 * @param buffer -接收数据缓冲点
 * @param len    -接收数据长度
 *
 * @return result>0:OK，并返回接收到的数据字节=0:连接已关闭<0:错误捕获
 */
int SSL_read(SSL *ssl, void *buffer, int len);

/**
 * @brief 将数据发送到远程
 *
 * @param ssl    -已连接的SSL点
 * @param buffer -发送数据缓冲点
 * @param len    -发送数据长度
 *
 * @return result>0:OK，返回发送的数据字节=0：连接已关闭<0:错误捕获
 */
int SSL_write(SSL *ssl, const void *buffer, int len);

/**
 * @brief 获取SSL证书的验证结果
 *
 * @param ssl -SSL点
 *
 * @return 验证的结果
 */
long SSL_get_verify_result(const SSL *ssl);

/**
 * @brief 关闭连接
 *
 * @param ssl -SSL点
 *
 * @return 结果1:OK 0:关闭未完成
 *    -1：错误捕获
 */
int SSL_shutdown(SSL *ssl);

/**
 * @brief 将套接字文件描述绑定到SSL
 *
 * @param ssl -SSL点
 * @param fd  -套筒手柄
 *
 * @return 结果1:OK 0:失败
 */
int SSL_set_fd(SSL *ssl, int fd);

/**
 * @brief 设置SNI的主机名
 *
 * @param ssl -SSL上下文点
 * @param hostname  -指向主机名的指针
 *
 * @return 结果1:OK 0:失败
 */
int SSL_set_tlsext_host_name(SSL* ssl, const char *hostname);

/**
 * @brief 这些函数将私钥加载到SSL_CTX或SSL对象中
 *
 * @param ctx  -SSL上下文点
 * @param pkey -私钥对象点
 *
 * @return 结果1:OK 0:失败
 */
int SSL_CTX_use_PrivateKey(SSL_CTX *ctx, EVP_PKEY *pkey);

/**
 * @brief 这些函数将证书加载到SSL_CTX或SSL对象中
 *
 * @param ctx  -SSL上下文点
 * @param pkey -认证对象点
 *
 * @return 结果1:OK 0:失败
 */
int SSL_CTX_use_certificate(SSL_CTX *ctx, X509 *x);

/**
 * @brief 创建目标SSL上下文客户端方法
 *
 * @param none
 *
 * @return SSLV2.3版本SSL上下文客户端方法
 */
const SSL_METHOD* SSLv23_client_method(void);

/**
 * @brief 创建目标SSL上下文客户端方法
 *
 * @param none
 *
 * @return TLSV1.0版本SSL上下文客户端方法
 */
const SSL_METHOD* TLSv1_client_method(void);

/**
 * @brief 创建目标SSL上下文客户端方法
 *
 * @param none
 *
 * @return SSLV1.0版本SSL上下文客户端方法
 */
const SSL_METHOD* SSLv3_client_method(void);

/**
 * @brief 创建目标SSL上下文客户端方法
 *
 * @param none
 *
 * @return TLSV1.1版本SSL上下文客户端方法
 */
const SSL_METHOD* TLSv1_1_client_method(void);

/**
 * @brief 创建目标SSL上下文客户端方法
 *
 * @param none
 *
 * @return TLSV1.2版本SSL上下文客户端方法
 */
const SSL_METHOD* TLSv1_2_client_method(void);

/**
 * @brief 创建目标SSL上下文服务器方法
 *
 * @param none
 *
 * @return TLS任意版本SSL上下文客户端方法
 */
const SSL_METHOD* TLS_client_method(void);

/**
 * @brief 创建目标SSL上下文服务器方法
 *
 * @param none
 *
 * @return SSLV2.3版本SSL上下文服务器方法
 */
const SSL_METHOD* SSLv23_server_method(void);

/**
 * @brief 创建目标SSL上下文服务器方法
 *
 * @param none
 *
 * @return TLSV1.1版本SSL上下文服务器方法
 */
const SSL_METHOD* TLSv1_1_server_method(void);

/**
 * @brief 创建目标SSL上下文服务器方法
 *
 * @param none
 *
 * @return TLSV1.2版本SSL上下文服务器方法
 */
const SSL_METHOD* TLSv1_2_server_method(void);

/**
 * @brief 创建目标SSL上下文服务器方法
 *
 * @param none
 *
 * @return TLSV1.0版本SSL上下文服务器方法
 */
const SSL_METHOD* TLSv1_server_method(void);

/**
 * @brief 创建目标SSL上下文服务器方法
 *
 * @param none
 *
 * @return SSLV3.0版本SSL上下文服务器方法
 */
const SSL_METHOD* SSLv3_server_method(void);

/**
 * @brief 创建目标SSL上下文服务器方法
 *
 * @param none
 *
 * @return TLS任意版本SSL上下文服务器方法
 */
const SSL_METHOD* TLS_server_method(void);

/**
 * @brief 创建目标SSL上下文方法
 *
 * @return TLS任意版本SSL上下文方法
 */
const SSL_METHOD* TLS_method(void);

/**
 * @brief 创建目标SSL上下文方法
 *
 * @return TLS1.2版本SSL上下文方法
 */
const SSL_METHOD* TLSv1_2_method(void);

/**
 * @brief 创建目标SSL上下文方法
 *
 * @return TLS1.1版本SSL上下文方法
 */
const SSL_METHOD* TLSv1_1_method(void);

/**
 * @brief 创建目标SSL上下文方法
 *
 * @return TLS1.0版本SSL上下文方法
 */
const SSL_METHOD* TLSv1_method(void);

/**
 * @brief 创建目标SSL上下文方法
 *
 * @return SSLV3.0版本SSL上下文方法
 */
const SSL_METHOD* SSLv3_method(void);

/**
 * @brief 创建目标SSL上下文方法
 *
 * @param none
 *
 * @return SSLV2.3版本SSL上下文方法
 */
const SSL_METHOD* SSLv23_method(void);

/**
 * @brief 为定义的上下文设置最低协议版本
 *
 * @param ctx SSL上下文
 *
 * @return 1表示成功
 */
int SSL_CTX_set_min_proto_version(SSL_CTX *ctx, int version);

/**
 * @brief 为定义的上下文设置最大协议版本
 *
 * @param ctx SSL上下文
 *
 * @return 1表示成功
 */
int SSL_CTX_set_max_proto_version(SSL_CTX *ctx, int version);

/**
 * @brief 设置SSL上下文ALPN select回调函数
 *
 * @param ctx -SSL上下文点
 * @param cb  -ALPN选择回调函数
 * @param arg -ALPN选择回调函数入口专用数据点
 *
 * @return 没有一个
 */
void SSL_CTX_set_alpn_select_cb(SSL_CTX *ctx,
                                int (*cb) (SSL *ssl,
                                           const unsigned char **out,
                                           unsigned char *outlen,
                                           const unsigned char *in,
                                           unsigned int inlen,
                                           void *arg),
                                void *arg);


/**
 * @brief 设置SSL上下文ALPN选择协议
 *
 * @param ctx        -SSL上下文点
 * @param protos     -ALPN协议名称
 * @param protos_len -ALPN协议名称字节
 *
 * @return 结果0:正常1:失败
 */
int SSL_CTX_set_alpn_protos(SSL_CTX *ctx, const unsigned char *protos, unsigned int protos_len);

/**
 * @brief 设置SSL上下文下一个ALPN选择回调函数
 *
 * @param ctx -SSL上下文点
 * @param cb  -ALPN选择回调函数
 * @param arg -ALPN选择回调函数入口专用数据点
 *
 * @return 没有一个
 */
void SSL_CTX_set_next_proto_select_cb(SSL_CTX *ctx,
                                      int (*cb) (SSL *ssl,
                                                 unsigned char **out,
                                                 unsigned char *outlen,
                                                 const unsigned char *in,
                                                 unsigned int inlen,
                                                 void *arg),
                                      void *arg);

/**
 * @brief 初始化SSL库
 *
 * @param none
 *
 * @return 没有一个
 */
void SSL_library_init(void);

/**
 * @brief 生成表示错误代码e的可读字符串，并将其存储到“ret”点存储器中
 *
 * @param e   -错误代码
 * @param ret -存储字符串的内存点
 *
 * @return 结果字符串点
 */
char *ERR_error_string(unsigned long e, char *ret);

/**
 * @brief 添加SSL上下文选项
 *
 * @param ctx -SSL上下文点
 * @param opt -新的SSL上下文选项
 *
 * @return SSL上下文选项
 */
unsigned long SSL_CTX_set_options(SSL_CTX *ctx, unsigned long opt);

/**
 * @brief 添加SSL上下文模式
 *
 * @param ctx -SSL上下文点
 * @param mod -新的SSL上下文模式
 *
 * @return 结果1:OK 0:失败
 */
int SSL_CTX_set_mode(SSL_CTX *ctx, int mod);

/*
}
*/

/**
 * @brief 执行SSL握手
 *
 * @param ssl -SSL点
 *
 * @return 结果1:OK 0:失败
 *    -1：错误捕获
 */
int SSL_do_handshake(SSL *ssl);

/**
 * @brief 获取SSL当前版本
 *
 * @param ssl -SSL点
 *
 * @return 版本字符串
 */
const char *SSL_get_version(const SSL *ssl);

/**
 * @brief 设置SSL上下文版本
 *
 * @param ctx  -SSL上下文点
 * @param meth -SSL方法点
 *
 * @return 结果1:OK 0:失败
 */
int SSL_CTX_set_ssl_version(SSL_CTX *ctx, const SSL_METHOD *meth);

/**
 * @brief 获取要读取的字节数
 *
 * @param ssl  -SSL点
 *
 * @return 字节数
 */
int SSL_pending(const SSL *ssl);

/**
 * @brief 检查SSL是否不需要任何内容
 *
 * @param ssl -SSL点
 *
 * @return 结果0:假1:真
 */
int SSL_want_nothing(const SSL *ssl);

/**
 * @brief 检查SSL是否要读取
 *
 * @param ssl -SSL点
 *
 * @return 结果0:假1:真
 */
int SSL_want_read(const SSL *ssl);

/**
 * @brief 检查SSL是否要写入
 *
 * @param ssl -SSL点
 *
 * @return 结果0:假1:真
 */
int SSL_want_write(const SSL *ssl);

/**
 * @brief 获取SSL上下文当前方法
 *
 * @param ctx -SSL上下文点
 *
 * @return SSL上下文当前方法
 */
const SSL_METHOD *SSL_CTX_get_ssl_method(SSL_CTX *ctx);

/**
 * @brief 获取SSL当前方法
 *
 * @param ssl -SSL点
 *
 * @return SSL当前方法
 */
const SSL_METHOD *SSL_get_ssl_method(SSL *ssl);

/**
 * @brief 设置SSL方法
 *
 * @param ssl  -SSL点
 * @param meth -SSL方法点
 *
 * @return 结果1:OK 0:失败
 */
int SSL_set_ssl_method(SSL *ssl, const SSL_METHOD *method);

/**
 * @brief 将CA客户端证书添加到SSL中
 *
 * @param ssl -SSL点
 * @param x   -CA认证点
 *
 * @return 结果1:OK 0:失败
 */
int SSL_add_client_CA(SSL *ssl, X509 *x);

/**
 * @brief 将CA客户端证书添加到SSL上下文中
 *
 * @param ctx -SSL上下文点
 * @param x   -CA认证点
 *
 * @return 结果1:OK 0:失败
 */
int SSL_CTX_add_client_CA(SSL_CTX *ctx, X509 *x);

/**
 * @brief 设置SSL CA证书列表
 *
 * @param ssl       -SSL点
 * @param name_list -CA认证列表
 *
 * @return 没有一个
 */
void SSL_set_client_CA_list(SSL *ssl, STACK_OF(X509_NAME) *name_list);

/**
 * @brief 设置SSL上下文CA证书列表
 *
 * @param ctx       -SSL上下文点
 * @param name_list -CA认证列表
 *
 * @return 没有一个
 */
void SSL_CTX_set_client_CA_list(SSL_CTX *ctx, STACK_OF(X509_NAME) *name_list);

/**
 * @briefget SSL CA证书列表
 *
 * @param ssl -SSL点
 *
 * @return CA认证列表
 */
STACK_OF(X509_NAME) *SSL_get_client_CA_list(const SSL *ssl);

/**
 * @brief 获取SSL上下文CA证书列表
 *
 * @param ctx -SSL上下文点
 *
 * @return CA认证列表
 */
STACK_OF(X509_NAME) *SSL_CTX_get_client_CA_list(const SSL_CTX *ctx);

/**
 * @brief 获取SSL认证点
 *
 * @param ssl -SSL点
 *
 * @return SSL认证点
 */
X509 *SSL_get_certificate(const SSL *ssl);

/**
 * @brief 获取SSL私钥点
 *
 * @param ssl -SSL点
 *
 * @return SSL私钥点
 */
EVP_PKEY *SSL_get_privatekey(const SSL *ssl);

/**
 * @brief 设置SSL信息回调函数
 *
 * @param ssl -SSL点
 * @param cb  -信息回调函数
 *
 * @return 没有一个
 */
void SSL_set_info_callback(SSL *ssl, void (*cb) (const SSL *ssl, int type, int val));

/**
 * @brief 获取SSL状态
 *
 * @param ssl -SSL点
 *
 * @return SSL状态
 */
OSSL_HANDSHAKE_STATE SSL_get_state(const SSL *ssl);

/**
 * @brief 设置SSL上下文读取缓冲区长度
 *
 * @param ctx -SSL上下文点
 * @param len -读取缓冲区长度
 *
 * @return 没有一个
 */
void SSL_CTX_set_default_read_buffer_len(SSL_CTX *ctx, size_t len);

/**
 * @brief 设置SSL读取缓冲区长度
 *
 * @param ssl -SSL点
 * @param len -读取缓冲区长度
 *
 * @return 没有一个
 */
void SSL_set_default_read_buffer_len(SSL *ssl, size_t len);

/**
 * @brief 设置SSL安全级别
 *
 * @param ssl   -SSL点
 * @param level -安全级别
 *
 * @return 没有一个
 */
void SSL_set_security_level(SSL *ssl, int level);

/**
 * @brief 获取SSL安全级别
 *
 * @param ssl -SSL点
 *
 * @return 安全级别
 */
int SSL_get_security_level(const SSL *ssl);

/**
 * @brief 获取SSL上下文的SSL验证模式
 *
 * @param ctx -SSL上下文点
 *
 * @return 验证模式
 */
int SSL_CTX_get_verify_mode(const SSL_CTX *ctx);

/**
 * @brief 获取SSL上下文的SSL验证深度
 *
 * @param ctx -SSL上下文点
 *
 * @return 验证深度
 */
int SSL_CTX_get_verify_depth(const SSL_CTX *ctx);

/**
 * @brief 设置SSL上下文的SSL上下文验证
 *
 * @param ctx             -SSL上下文点
 * @param mode            -验证模式
 * @param verify_callback -验证回调函数
 *
 * @return 没有一个
 */
void SSL_CTX_set_verify(SSL_CTX *ctx, int mode, int (*verify_callback)(int, X509_STORE_CTX *));

/**
 * @brief 设置SSL上下文的SSL验证
 *
 * @param ctx             -SSL点
 * @param mode            -验证模式
 * @param verify_callback -验证回调函数
 *
 * @return 没有一个
 */
void SSL_set_verify(SSL *s, int mode, int (*verify_callback)(int, X509_STORE_CTX *));

/**
 * @brief 设置SSL上下文的SSL验证深度
 *
 * @param ctx   -SSL上下文点
 * @param depth -验证深度
 *
 * @return 没有一个
 */
void SSL_CTX_set_verify_depth(SSL_CTX *ctx, int depth);

/**
 * @brief 认证验证回调函数
 *
 * @param preverify_ok -验证结果
 * @param x509_ctx     -X509认证点
 *
 * @return 验证结果
 */
int verify_callback(int preverify_ok, X509_STORE_CTX *x509_ctx);

/**
 * @brief 设置会话超时时间
 *
 * @param ctx -SSL上下文点
 * @param t   -新会话超时时间
 *
 * @return 旧会话超时时间
 */
long SSL_CTX_set_timeout(SSL_CTX *ctx, long t);

/**
 * @brief 获取会话超时时间
 *
 * @param ctx -SSL上下文点
 *
 * @return 当前会话超时时间
 */
long SSL_CTX_get_timeout(const SSL_CTX *ctx);

/**
 * @brief 通过列表字符串设置SSL上下文密码
 *
 * @param ctx -SSL上下文点
 * @param str -密码控制器列表字符串
 *
 * @return 结果1:OK 0:失败
 */
int SSL_CTX_set_cipher_list(SSL_CTX *ctx, const char *str);

/**
 * @brief 通过列表字符串设置SSL密码
 *
 * @param ssl -SSL点
 * @param str -密码控制器列表字符串
 *
 * @return 结果1:OK 0:失败
 */
int SSL_set_cipher_list(SSL *ssl, const char *str);

/**
 * @brief 获取SSL密码列表字符串
 *
 * @param ssl -SSL点
 *
 * @return 密码控制器列表字符串
 */
const char *SSL_get_cipher_list(const SSL *ssl, int n);

/**
 * @brief 获取SSL密码
 *
 * @param ssl -SSL点
 *
 * @return 电流密码
 */
const SSL_CIPHER *SSL_get_current_cipher(const SSL *ssl);

/**
 * @brief 获取SSL密码字符串
 *
 * @param ssl -SSL点
 *
 * @return 密码字符串
 */
const char *SSL_get_cipher(const SSL *ssl);

/**
 * @brief 获取SSL上下文对象X509认证存储
 *
 * @param ctx -SSL上下文点
 *
 * @return x509认证存储
 */
X509_STORE *SSL_CTX_get_cert_store(const SSL_CTX *ctx);

/**
 * @brief 设置SSL上下文对象X509证书存储
 *
 * @param ctx   -SSL上下文点
 * @param store -X509认证商店
 *
 * @return 没有一个
 */
void SSL_CTX_set_cert_store(SSL_CTX *ctx, X509_STORE *store);

/**
 * @brief 获取SSL特定语句
 *
 * @param ssl -SSL点
 *
 * @return 特定陈述
 */
int SSL_want(const SSL *ssl);

/**
 * @brief 检查SSL是否为SSL_X509_LOOKUP状态
 *
 * @param ssl -SSL点
 *
 * @return 结果1:OK 0:失败
 */
int SSL_want_x509_lookup(const SSL *ssl);

/**
 * @brief 重置SSL
 *
 * @param ssl -SSL点
 *
 * @return 结果1:OK 0:失败
 */
int SSL_clear(SSL *ssl);

/**
 * @brief 获取SSL的套接字句柄
 *
 * @param ssl -SSL点
 *
 * @return result>=0:yes，返回套接字句柄<0:错误捕获
 */
int SSL_get_fd(const SSL *ssl);

/**
 * @brief 获取SSL的只读套接字句柄
 *
 * @param ssl -SSL点
 *
 * @return result>=0:yes，返回套接字句柄<0:错误捕获
 */
int SSL_get_rfd(const SSL *ssl);

/**
 * @brief 获取SSL的只读套接字句柄
 *
 * @param ssl -SSL点
 *
 * @return result>=0:yes，返回套接字句柄<0:错误捕获
 */
int SSL_get_wfd(const SSL *ssl);

/**
 * @brief 如果我们可以读取尽可能多的数据，请设置SSL
 *
 * @param ssl -SSL点
 * @param yes -启用该功能
 *
 * @return 没有一个
 */
void SSL_set_read_ahead(SSL *s, int yes);

/**
 * @brief 如果我们可以读取尽可能多的数据，请设置SSL上下文
 *
 * @param ctx -SSL上下文点
 * @param yes -启用函数
 *
 * @return 没有一个
 */
void SSL_CTX_set_read_ahead(SSL_CTX *ctx, int yes);

/**
 * @brief 如果我们可以读取尽可能多的数据，则获取SSL先行信号
 *
 * @param ssl -SSL点
 *
 * @return SSL上下文提前信号
 */
int SSL_get_read_ahead(const SSL *ssl);

/**
 * @brief 如果我们可以读取尽可能多的数据，则获取SSL上下文提前信号
 *
 * @param ctx -SSL上下文点
 *
 * @return SSL上下文提前信号
 */
long SSL_CTX_get_read_ahead(SSL_CTX *ctx);

/**
 * @brief 检查是否可以读取某些数据
 *
 * @param ssl -SSL点
 *
 * @return 1：有字节要读取0：无数据
 */
int SSL_has_pending(const SSL *ssl);

/**
 * @brief 将X509证书加载到SSL上下文中
 *
 * @param ctx -SSL上下文点
 * @param x   -X509认证点
 *
 * @return 结果1:OK 0:失败
 */
int SSL_CTX_use_certificate(SSL_CTX *ctx, X509 *x);//将证书x加载到ctx中

/**
 * @brief 将ASN1证书加载到SSL上下文中
 *
 * @param ctx -SSL上下文点
 * @param len -认证长度
 * @param d   -数据点
 *
 * @return 结果1:OK 0:失败
 */
int SSL_CTX_use_certificate_ASN1(SSL_CTX *ctx, int len, const unsigned char *d);

/**
 * @brief 将证书文件加载到SSL上下文中
 *
 * @param ctx  -SSL上下文点
 * @param file -证书文件名
 * @param type -认证编码类型
 *
 * @return 结果1:OK 0:失败
 */
int SSL_CTX_use_certificate_file(SSL_CTX *ctx, const char *file, int type);

/**
 * @brief 将证书链文件加载到SSL上下文中
 *
 * @param ctx  -SSL上下文点
 * @param file -证书链文件名
 *
 * @return 结果1:OK 0:失败
 */
int SSL_CTX_use_certificate_chain_file(SSL_CTX *ctx, const char *file);


/**
 * @brief 将ASN1私钥加载到SSL上下文中
 *
 * @param ctx -SSL上下文点
 * @param d   -数据点
 * @param len -私钥长度
 *
 * @return 结果1:OK 0:失败
 */
int SSL_CTX_use_PrivateKey_ASN1(int pk, SSL_CTX *ctx, const unsigned char *d,  long len);//将存储在内存位置d（长度len）的pk类型的私钥添加到ctx

/**
 * @brief 将私钥文件加载到SSL上下文中
 *
 * @param ctx  -SSL上下文点
 * @param file -私钥文件名
 * @param type -私钥编码类型
 *
 * @return 结果1:OK 0:失败
 */
int SSL_CTX_use_PrivateKey_file(SSL_CTX *ctx, const char *file, int type);

/**
 * @brief 将RSA私钥加载到SSL上下文中
 *
 * @param ctx -SSL上下文点
 * @param x   -RSA私钥
 *
 * @return 结果1:OK 0:失败
 */
int SSL_CTX_use_RSAPrivateKey(SSL_CTX *ctx, RSA *rsa);

/**
 * @brief 将RSA ASN1私钥加载到SSL上下文中
 *
 * @param ctx -SSL上下文点
 * @param d   -数据点
 * @param len -RSA私钥长度
 *
 * @return 结果1:OK 0:失败
 */
int SSL_CTX_use_RSAPrivateKey_ASN1(SSL_CTX *ctx, const unsigned char *d, long len);

/**
 * @brief 将RSA私钥文件加载到SSL上下文中
 *
 * @param ctx  -SSL上下文点
 * @param file -RSA私钥文件名
 * @param type -私钥编码类型
 *
 * @return 结果1:OK 0:失败
 */
int SSL_CTX_use_RSAPrivateKey_file(SSL_CTX *ctx, const char *file, int type);


/**
 * @brief 检查私钥和证书是否匹配
 *
 * @param ctx  -SSL上下文点
 *
 * @return 结果1:OK 0:失败
 */
int SSL_CTX_check_private_key(const SSL_CTX *ctx);

/**
 * @brief 设置SSL上下文服务器信息
 *
 * @param ctx               -SSL上下文点
 * @param serverinfo        -服务器信息字符串
 * @param serverinfo_length -服务器信息长度
 *
 * @return 结果1:OK 0:失败
 */
int SSL_CTX_use_serverinfo(SSL_CTX *ctx, const unsigned char *serverinfo, size_t serverinfo_length);

/**
 * @brief 将SSL上下文服务器信息文件加载到SSL上下文中
 *
 * @param ctx  -SSL上下文点
 * @param file -服务器信息文件
 *
 * @return 结果1:OK 0:失败
 */
int SSL_CTX_use_serverinfo_file(SSL_CTX *ctx, const char *file);

/**
 * @brief SSL选择下一个函数
 *
 * @param out        -输出数据点
 * @param outlen     -输出数据长度
 * @param in         -输入数据
 * @param inlen      -输入数据长度
 * @param client     -客户端数据点
 * @param client_len -客户端数据长度
 *
 * @return NPN状态OPENSSL_NPN_UNSUPPORTED：不支持OPENSSL/NPN_NEGOTIATED：协商OPENSSL-NPN_NO_OVERLAP:无重叠
 */
int SSL_select_next_proto(unsigned char **out, unsigned char *outlen,
                          const unsigned char *in, unsigned int inlen,
                          const unsigned char *client, unsigned int client_len);

/**
 * @brief 将额外的证书链加载到SSL上下文中
 *
 * @param ctx  -SSL上下文点
 * @param x509 -X509认证
 *
 * @return 结果1:OK 0:失败
 */
long SSL_CTX_add_extra_chain_cert(SSL_CTX *ctx, X509 *);

/**
 * @brief 控制SSL上下文
 *
 * @param ctx  -SSL上下文点
 * @param cmd  -命令
 * @param larg -参数长度
 * @param parg -参数点
 *
 * @return 结果1:OK 0:失败
 */
long SSL_CTX_ctrl(SSL_CTX *ctx, int cmd, long larg, char *parg);

/**
 * @brief 获取SSL上下文密码
 *
 * @param ctx -SSL上下文点
 *
 * @return SSL上下文密码
 */
STACK *SSL_CTX_get_ciphers(const SSL_CTX *ctx);

/**
 * @brief 检查SSL上下文是否可以读取尽可能多的数据
 *
 * @param ctx -SSL上下文点
 *
 * @return 结果1:OK 0:失败
 */
long SSL_CTX_get_default_read_ahead(SSL_CTX *ctx);

/**
 * @brief 获取SSL上下文额外数据
 *
 * @param ctx -SSL上下文点
 * @param idx -索引
 *
 * @return 数据点
 */
char *SSL_CTX_get_ex_data(const SSL_CTX *ctx, int idx);

/**
 * @brief 获取SSL上下文安静关闭选项
 *
 * @param ctx -SSL上下文点
 *
 * @return 安静关机选项
 */
int SSL_CTX_get_quiet_shutdown(const SSL_CTX *ctx);

/**
 * @brief 加载SSL上下文CA文件
 *
 * @param ctx    -SSL上下文点
 * @param CAfile -CA认证文件
 * @param CApath -CA证书文件路径
 *
 * @return 结果1:OK 0:失败
 */
int SSL_CTX_load_verify_locations(SSL_CTX *ctx, const char *CAfile, const char *CApath);

/**
 * @brief 按“1”添加SSL上下文引用计数
 *
 * @param ctx -SSL上下文点
 *
 * @return 结果1:OK 0:失败
 */
int SSL_CTX_up_ref(SSL_CTX *ctx);

/**
 * @brief 设置SSL上下文应用程序专用数据
 *
 * @param ctx -SSL上下文点
 * @param arg -私有数据
 *
 * @return 结果1:OK 0:失败
 */
int SSL_CTX_set_app_data(SSL_CTX *ctx, void *arg);

/**
 * @brief 设置SSL上下文客户端认证回调函数
 *
 * @param ctx -SSL上下文点
 * @param cb  -回调函数
 *
 * @return 没有一个
 */
void SSL_CTX_set_client_cert_cb(SSL_CTX *ctx, int (*cb)(SSL *ssl, X509 **x509, EVP_PKEY **pkey));

/**
 * @brief 如果我们可以读取尽可能多的数据，请设置SSL上下文
 *
 * @param ctx -SSL上下文点
 * @param m   -启用功能
 *
 * @return 没有一个
 */
void SSL_CTX_set_default_read_ahead(SSL_CTX *ctx, int m);

/**
 * @brief 设置SSL上下文默认验证路径
 *
 * @param ctx -SSL上下文点
 *
 * @return 结果1:OK 0:失败
 */
int SSL_CTX_set_default_verify_paths(SSL_CTX *ctx);

/**
 * @brief 设置SSL上下文默认验证目录
 *
 * @param ctx -SSL上下文点
 *
 * @return 结果1:OK 0:失败
 */
int SSL_CTX_set_default_verify_dir(SSL_CTX *ctx);

/**
 * @brief 设置SSL上下文默认验证文件
 *
 * @param ctx -SSL上下文点
 *
 * @return 结果1:OK 0:失败
 */
int SSL_CTX_set_default_verify_file(SSL_CTX *ctx);

/**
 * @brief 设置SSL上下文额外数据
 *
 * @param ctx -SSL上下文点
 * @param idx -数据索引
 * @param arg -数据点
 *
 * @return 结果1:OK 0:失败
 */
int SSL_CTX_set_ex_data(SSL_CTX *s, int idx, char *arg);

/**
 * @brief 清除“op”的SSL上下文选项位
 *
 * @param ctx -SSL上下文点
 * @param op  -期权
 *
 * @return SSL上下文选项
 */
unsigned long SSL_CTX_clear_options(SSL_CTX *ctx, unsigned long op);

/**
 * @brief 获取SSL上下文选项
 *
 * @param ctx -SSL上下文点
 * @param op  -期权
 *
 * @return SSL上下文选项
 */
unsigned long SSL_CTX_get_options(SSL_CTX *ctx);

/**
 * @brief 设置SSL上下文安静关闭模式
 *
 * @param ctx  -SSL上下文点
 * @param mode -模式
 *
 * @return 没有一个
 */
void SSL_CTX_set_quiet_shutdown(SSL_CTX *ctx, int mode);

/**
 * @brief 获取SSL上下文X509证书
 *
 * @param ctx -SSL上下文点
 *
 * @return X509认证
 */
X509 *SSL_CTX_get0_certificate(const SSL_CTX *ctx);

/**
 * @brief 获取SSL上下文私钥
 *
 * @param ctx -SSL上下文点
 *
 * @return 私钥
 */
EVP_PKEY *SSL_CTX_get0_privatekey(const SSL_CTX *ctx);

/**
 * @brief 设置SSL上下文PSK标识提示
 *
 * @param ctx  -SSL上下文点
 * @param hint -PSK标识提示
 *
 * @return 结果1:OK 0:失败
 */
int SSL_CTX_use_psk_identity_hint(SSL_CTX *ctx, const char *hint);

/**
 * @brief 设置SSL上下文PSK服务器回调函数
 *
 * @param ctx      -SSL上下文点
 * @param callback -回调函数
 *
 * @return 没有一个
 */
void SSL_CTX_set_psk_server_callback(SSL_CTX *ctx,
                                     unsigned int (*callback)(SSL *ssl,
                                                              const char *identity,
                                                              unsigned char *psk,
                                                              int max_psk_len));
/**
 * @brief 获取警报描述字符串
 *
 * @param value -警报值
 *
 * @return 警报描述字符串
 */
const char *SSL_alert_desc_string(int value);

/**
 * @brief 获取警报描述长字符串
 *
 * @param value -警报值
 *
 * @return 警报描述长字符串
 */
const char *SSL_alert_desc_string_long(int value);

/**
 * @brief 获取警报类型字符串
 *
 * @param value -警报值
 *
 * @return 警报类型字符串
 */
const char *SSL_alert_type_string(int value);

/**
 * @brief 获取警报类型长字符串
 *
 * @param value -警报值
 *
 * @return 警报类型长字符串
 */
const char *SSL_alert_type_string_long(int value);

/**
 * @brief 获取SSL的SSL上下文
 *
 * @param ssl -SSL点
 *
 * @return SSL上下文
 */
SSL_CTX *SSL_get_SSL_CTX(const SSL *ssl);

/**
 * @brief 获取SSL应用程序数据
 *
 * @param ssl -SSL点
 *
 * @return 应用程序数据
 */
void *SSL_get_app_data(SSL *ssl);

/**
 * @brief 获取SSL错误代码
 *
 * @param ssl       -SSL点
 * @param ret_code  -SSL返回代码
 *
 * @return SSL错误号
 */
int SSL_get_error(const SSL *ssl, int ret_code);

/**
 * @brief 获取SSL密码位
 *
 * @param ssl -SSL点
 * @param alg_bits -算法位
 *
 * @return 强力钻头
 */
int SSL_get_cipher_bits(const SSL *ssl, int *alg_bits);

/**
 * @brief 获取SSL密码名称
 *
 * @param ssl -SSL点
 *
 * @return SSL密码名称
 */
char *SSL_get_cipher_name(const SSL *ssl);

/**
 * @brief 获取SSL密码版本
 *
 * @param ssl -SSL点
 *
 * @return SSL密码版本
 */
char *SSL_get_cipher_version(const SSL *ssl);

/**
 * @brief 获取SSL额外数据
 *
 * @param ssl -SSL点
 * @param idx -数据索引
 *
 * @return 额外数据
 */
char *SSL_get_ex_data(const SSL *ssl, int idx);

/**
 * @brief 获取SSL额外数据X509存储上下文的索引
 *
 * @param none
 *
 * @return 数据索引
 */
int SSL_get_ex_data_X509_STORE_CTX_idx(void);

/**
 * @brief 获取同行认证链
 *
 * @param ssl -SSL点
 *
 * @return 认证链
 */
STACK *SSL_get_peer_cert_chain(const SSL *ssl);

/**
 * @brief 获得同行认证
 *
 * @param ssl -SSL点
 *
 * @return 证明
 */
X509 *SSL_get_peer_certificate(const SSL *ssl);

/**
 * @brief 获取SSL安静关闭模式
 *
 * @param ssl -SSL点
 *
 * @return 安静关机模式
 */
int SSL_get_quiet_shutdown(const SSL *ssl);

/**
 * @brief 获取SSL只读IO句柄
 *
 * @param ssl -SSL点
 *
 * @return IO手柄
 */
BIO *SSL_get_rbio(const SSL *ssl);

/**
 * @brief 获取SSL共享密码
 *
 * @param ssl -SSL点
 * @param buf -存储密码的缓冲区
 * @param len -缓冲透镜
 *
 * @return 共享密码
 */
char *SSL_get_shared_ciphers(const SSL *ssl, char *buf, int len);

/**
 * @brief 获取SSL关闭模式
 *
 * @param ssl -SSL点
 *
 * @return 关机模式
 */
int SSL_get_shutdown(const SSL *ssl);

/**
 * @brief 获取SSL会话时间
 *
 * @param ssl -SSL点
 *
 * @return 会话时间
 */
long SSL_get_time(const SSL *ssl);

/**
 * @brief 获取SSL会话超时时间
 *
 * @param ssl -SSL点
 *
 * @return 会话超时时间
 */
long SSL_get_timeout(const SSL *ssl);

/**
 * @brief 获取SSL验证模式
 *
 * @param ssl -SSL点
 *
 * @return 验证模式
 */
int SSL_get_verify_mode(const SSL *ssl);

/**
 * @brief 获取SSL验证参数
 *
 * @param ssl -SSL点
 *
 * @return 验证参数
 */
X509_VERIFY_PARAM *SSL_get0_param(SSL *ssl);

/**
 * @brief 设置对等证书CN应具有的预期主机名
 *
 * @param param -验证SSL_get0_param（）中的参数
 *
 * @param name -预期的主机名
 *
 * @param namelen -主机名的长度，如果NUL终止，则为0
 *
 * @return 验证参数
 */
int X509_VERIFY_PARAM_set1_host(X509_VERIFY_PARAM *param,
                                const char *name, size_t namelen);

/**
 * @brief 设置X509主机验证操作的参数
 *
 * @param param -验证SSL_get0_param（）中的参数
 *
 * @param flags -X509_CHECK_FLAG_…要设置的参数的位字段
 *
 * @return 1表示成功，0表示失败
 */
int X509_VERIFY_PARAM_set_hostflags(X509_VERIFY_PARAM *param,
                    unsigned long flags);

/**
 * @brief 清除X509主机验证操作的参数
 *
 * @param param -验证SSL_get0_param（）中的参数
 *
 * @param flags -X509_CHECK_FLAG_…要清除的参数的位字段
 *
 * @return 1表示成功，0表示失败
 */
int X509_VERIFY_PARAM_clear_hostflags(X509_VERIFY_PARAM *param,
                      unsigned long flags);

/**
 * @brief 获取SSL仅写IO句柄
 *
 * @param ssl -SSL点
 *
 * @return IO手柄
 */
BIO *SSL_get_wbio(const SSL *ssl);

/**
 * @brief 加载SSL客户端CA证书文件
 *
 * @param file -文件名
 *
 * @return 认证加载对象
 */
STACK *SSL_load_client_CA_file(const char *file);

/**
 * @brief 通过“1”添加SSL引用
 *
 * @param ssl -SSL点
 *
 * @return 结果1:OK 0:失败
 */
int SSL_up_ref(SSL *ssl);

/**
 * @brief 读取数据并将其放入buf，但不清除SSL低级存储
 *
 * @param ssl -SSL点
 * @param buf -存储缓冲点
 * @param num -数据字节
 *
 * @return result>0:OK，返回read-bytes=0:connect已关闭<0:错误捕获
 */
int SSL_peek(SSL *ssl, void *buf, int num);

/**
 * @brief 使SSL重新协商
 *
 * @param ssl -SSL点
 *
 * @return 结果1:OK 0:失败
 */
int SSL_renegotiate(SSL *ssl);

/**
 * @brief 获取SSL正在读取的状态字符串
 *
 * @param ssl -SSL点
 *
 * @return 状态字符串
 */
const char *SSL_rstate_string(SSL *ssl);

/**
 * @brief 获取SSL正在读取的语句长字符串
 *
 * @param ssl -SSL点
 *
 * @return 语句长字符串
 */
const char *SSL_rstate_string_long(SSL *ssl);

/**
 * @brief 设置SSL接受语句
 *
 * @param ssl -SSL点
 *
 * @return 没有一个
 */
void SSL_set_accept_state(SSL *ssl);

/**
 * @brief 设置SSL应用程序数据
 *
 * @param ssl -SSL点
 * @param arg -SSL应用程序数据点
 *
 * @return 没有一个
 */
void SSL_set_app_data(SSL *ssl, void *arg);

/**
 * @brief 设置SSL BIO
 *
 * @param ssl  -SSL点
 * @param rbio -只读IO
 * @param wbio -仅写IO
 *
 * @return 没有一个
 */
void SSL_set_bio(SSL *ssl, BIO *rbio, BIO *wbio);

/**
 * @brief 清除SSL选项
 *
 * @param ssl -SSL点
 * @param op  -清除选项
 *
 * @return SSL选项
 */
unsigned long SSL_clear_options(SSL *ssl, unsigned long op);

/**
 * @brief 获取SSL选项
 *
 * @param ssl -SSL点
 *
 * @return SSL选项
 */
unsigned long SSL_get_options(SSL *ssl);

/**
 * @brief 清除SSL选项
 *
 * @param ssl -SSL点
 * @param op  -设置选项
 *
 * @return SSL选项
 */
unsigned long SSL_set_options(SSL *ssl, unsigned long op);

/**
 * @brief 设置SSL安静关闭模式
 *
 * @param ssl  -SSL点
 * @param mode -安静关机模式
 *
 * @return 没有一个
 */
void SSL_set_quiet_shutdown(SSL *ssl, int mode);

/**
 * @brief 设置SSL关闭模式
 *
 * @param ssl  -SSL点
 * @param mode -关机模式
 *
 * @return 没有一个
 */
void SSL_set_shutdown(SSL *ssl, int mode);

/**
 * @brief 设置SSL会话时间
 *
 * @param ssl -SSL点
 * @param t   -会话时间
 *
 * @return 会话时间
 */
void SSL_set_time(SSL *ssl, long t);

/**
 * @brief 设置SSL会话超时时间
 *
 * @param ssl -SSL点
 * @param t   -会话超时时间
 *
 * @return 会话超时时间
 */
void SSL_set_timeout(SSL *ssl, long t);

/**
 * @brief 获取SSL语句字符串
 *
 * @param ssl -SSL点
 *
 * @return SSL语句字符串
 */
const char *SSL_state_string(const SSL *ssl);

/**
 * @brief 获取SSL语句长字符串
 *
 * @param ssl -SSL点
 *
 * @return SSL语句长字符串
 */
char *SSL_state_string_long(const SSL *ssl);

/**
 * @brief 获取SSL重新协商计数
 *
 * @param ssl -SSL点
 *
 * @return 重新协商计数
 */
long SSL_total_renegotiations(SSL *ssl);

/**
 * @brief 获取SSL版本
 *
 * @param ssl -SSL点
 *
 * @return SSL版本
 */
int SSL_version(const SSL *ssl);

/**
 * @brief 设置SSL PSK标识提示
 *
 * @param ssl  -SSL点
 * @param hint -身份提示
 *
 * @return 结果1:OK 0:失败
 */
int SSL_use_psk_identity_hint(SSL *ssl, const char *hint);

/**
 * @brief 获取SSL PSK标识提示
 *
 * @param ssl -SSL点
 *
 * @return 身份提示
 */
const char *SSL_get_psk_identity_hint(SSL *ssl);

/**
 * @brief 获取SSL PSK标识
 *
 * @param ssl -SSL点
 *
 * @return 身份
 */
const char *SSL_get_psk_identity(SSL *ssl);

/**
 * @brief 设置SSL的SSL验证深度
 *
 * @param ssl -SSL上下文
 * @param depth -要验证的深度级别
 *
 */
void SSL_set_verify_depth(SSL *ssl, int depth);

/**
 * @brief 获取默认验证回调
 *
 * @param ctx             -SSL上下文
 * @return verify_callback-验证回调函数
 *
 */
openssl_verify_callback SSL_CTX_get_verify_callback(const SSL_CTX *ctx);

/**
 * @brief 获取默认验证回调
 *
 * @param ctx             -SSL上下文
 * @return verify_callback-验证回调函数
 *
 */
openssl_verify_callback SSL_get_verify_callback(const SSL *s);

/**
 * @brief 释放RSA对象
 *
 * 当前实现直接调用EVP_PKEY free
 *
 * @param r RSA对象
 *
 */
void RSA_free(RSA *r);

/**
 * @brief 设置SSL模式，部分实现
 *
 * @param ssl SSL上下文
 *
 * @return 添加模式后的新模式位掩码
 */
uint32_t SSL_set_mode(SSL *ssl, uint32_t mode);

#ifdef __cplusplus
}
#endif

#endif

