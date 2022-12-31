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

#ifndef _SSL_TYPES_H_
#define _SSL_TYPES_H_

#ifdef __cplusplus
 extern "C" {
#endif

#include "ssl_code.h"
#include <stddef.h>
#include <stdint.h>

typedef void SSL_CIPHER;

typedef void X509_STORE_CTX;
typedef void X509_STORE;

typedef void RSA;

typedef void STACK;

typedef void DH;

#define ossl_inline inline

#define SSL_METHOD_CALL(f, s, ...)        s->method->func->ssl_##f(s, ##__VA_ARGS__)
#define X509_METHOD_CALL(f, x, ...)       x->method->x509_##f(x, ##__VA_ARGS__)
#define EVP_PKEY_METHOD_CALL(f, k, ...)   k->method->pkey_##f(k, ##__VA_ARGS__)

typedef int (*OPENSSL_sk_compfunc)(const void *, const void *);
typedef int (*openssl_verify_callback)(int, X509_STORE_CTX *);
struct stack_st;
typedef struct stack_st OPENSSL_STACK;

struct ssl_method_st;
typedef struct ssl_method_st SSL_METHOD;

struct ssl_method_func_st;
typedef struct ssl_method_func_st SSL_METHOD_FUNC;

struct record_layer_st;
typedef struct record_layer_st RECORD_LAYER;

struct ossl_statem_st;
typedef struct ossl_statem_st OSSL_STATEM;

struct ssl_session_st;
typedef struct ssl_session_st SSL_SESSION;

struct ssl_ctx_st;
typedef struct ssl_ctx_st SSL_CTX;

struct ssl_st;
typedef struct ssl_st SSL;

struct cert_st;
typedef struct cert_st CERT;

struct x509_st;
typedef struct x509_st X509;

struct X509_VERIFY_PARAM_st;
typedef struct X509_VERIFY_PARAM_st X509_VERIFY_PARAM;

struct evp_pkey_st;
typedef struct evp_pkey_st EVP_PKEY;

struct x509_method_st;
typedef struct x509_method_st X509_METHOD;

struct pkey_method_st;
typedef struct pkey_method_st PKEY_METHOD;

struct ssl_alpn_st;
typedef struct ssl_alpn_st SSL_ALPN;

struct bio_st;
typedef struct bio_st BIO;

struct stack_st {

    char **data;

    int num_alloc;

    OPENSSL_sk_compfunc c;
};

struct evp_pkey_st {

    void *pkey_pm;

    const PKEY_METHOD *method;

    int ref_counter;
};

struct x509_st {

    /* X509认证平台专用点*/
    void *x509_pm;

    const X509_METHOD *method;

    int ref_counter;
};

struct cert_st {

    int sec_level;

    X509 *x509;

    EVP_PKEY *pkey;

};

struct ossl_statem_st {

    MSG_FLOW_STATE state;

    int hand_state;
};

struct record_layer_st {

    int rstate;

    int read_ahead;
};

struct ssl_session_st {

    long timeout;

    long time;

    X509 *peer;
};

struct X509_VERIFY_PARAM_st {

    int depth;

};

struct bio_st {

    unsigned char * data;
    int dlen;
    BIO* peer;
    size_t offset;
    size_t roffset;
    size_t size;
    size_t flags;
    size_t type;

};

typedef enum { ALPN_INIT, ALPN_ENABLE, ALPN_DISABLE, ALPN_ERROR } ALPN_STATUS;
struct ssl_alpn_st {
     ALPN_STATUS alpn_status;
     /* 这是动态分配的*/
     char *alpn_string;
     /* 这只指向字符串中的成员*/
#define ALPN_LIST_MAX 10
     const char *alpn_list[ALPN_LIST_MAX];
};

typedef int pem_password_cb(char *buf, int size, int rwflag, void *userdata);


struct ssl_ctx_st
{
    int version;

    int references;

    unsigned long options;

    SSL_ALPN ssl_alpn;

    const SSL_METHOD *method;

    CERT *cert;

    X509 *client_CA;

    int verify_mode;

    int (*default_verify_callback) (int ok, X509_STORE_CTX *ctx);

    long session_timeout;

    int read_ahead;

    int read_buffer_len;

    X509_VERIFY_PARAM param;

    void *default_passwd_callback_userdata;

    pem_password_cb *default_passwd_callback;

    struct stack_st_X509 *extra_certs;

    int max_version;
    int min_version;

};

struct ssl_st
{
    /* 协议版本（SSL3.0、TLS1.0等之一）*/
    int version;

    unsigned long options;

    /* 关闭（0x01：已发送，0x02：已接收）*/
    int shutdown;

    CERT *cert;

    X509 *client_CA;

    SSL_CTX  *ctx;

    const SSL_METHOD *method;

    RECORD_LAYER rlayer;

    /* 我们在哪里*/
    OSSL_STATEM statem;

    SSL_SESSION *session;

    int verify_mode;

    int (*verify_callback) (int ok, X509_STORE_CTX *ctx);

    int rwstate;

    long verify_result;

    X509_VERIFY_PARAM param;

    uint32_t mode;

    void (*info_callback) (const SSL *ssl, int type, int val);

    /* SSL低级系统拱点*/
    void *ssl_pm;
    void *bio;
};

struct ssl_method_st {
    /* 协议版本（SSL3.0、TLS1.0等之一）*/
    int version;

    /* SSL模式（客户端（0），服务器（1），未知（-1））*/
    int endpoint;

    const SSL_METHOD_FUNC *func;
};

struct ssl_method_func_st {

    int (*ssl_new)(SSL *ssl);

    void (*ssl_free)(SSL *ssl);

    int (*ssl_handshake)(SSL *ssl);

    int (*ssl_shutdown)(SSL *ssl);

    int (*ssl_clear)(SSL *ssl);

    int (*ssl_read)(SSL *ssl, void *buffer, int len);

    int (*ssl_send)(SSL *ssl, const void *buffer, int len);

    int (*ssl_pending)(const SSL *ssl);

    void (*ssl_set_fd)(SSL *ssl, int fd, int mode);

    void (*ssl_set_hostname)(SSL *ssl, const char *hostname);

    int (*ssl_get_fd)(const SSL *ssl, int mode);

    void (*ssl_set_bufflen)(SSL *ssl, int len);

    long (*ssl_get_verify_result)(const SSL *ssl);

    OSSL_HANDSHAKE_STATE (*ssl_get_state)(const SSL *ssl);
};

struct x509_method_st {

    int (*x509_new)(X509 *x, X509 *m_x);

    void (*x509_free)(X509 *x);

    int (*x509_load)(X509 *x, const unsigned char *buf, int len);

    int (*x509_show_info)(X509 *x);
};

struct pkey_method_st {

    int (*pkey_new)(EVP_PKEY *pkey, EVP_PKEY *m_pkey);

    void (*pkey_free)(EVP_PKEY *pkey);

    int (*pkey_load)(EVP_PKEY *pkey, const unsigned char *buf, int len);
};

struct bio_method_st {

    unsigned type;

    unsigned size;
};


typedef int (*next_proto_cb)(SSL *ssl, unsigned char **out,
                             unsigned char *outlen, const unsigned char *in,
                             unsigned int inlen, void *arg);

#ifdef __cplusplus
}
#endif

#endif

