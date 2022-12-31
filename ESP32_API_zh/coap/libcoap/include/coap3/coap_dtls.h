/*
 * coap_dtls。h——libcoap的（数据报）传输层支持
 *
 * Copyright (C) 2016 Olaf Bergmann <bergmann@tzi.org> 版权所有（C）2017 Jean-Claude Michelou<jcm@spinetix.com>
 *
 * SPDX许可证标识符：BSD-2-Clause
 *
 * 此文件是CoAP库libcoap的一部分。请参阅README了解使用条款。
 */

#ifndef COAP_DTLS_H_
#define COAP_DTLS_H_

#include "coap_time.h"
#include "str.h"

/**
 * @defgroup dtls dtls支持与dtls库接口的API函数@{
 */

typedef struct coap_dtls_pki_t coap_dtls_pki_t;

#ifndef COAP_DTLS_HINT_LENGTH
#define COAP_DTLS_HINT_LENGTH 128
#endif
#ifndef COAP_DTLS_MAX_PSK_IDENTITY
#define COAP_DTLS_MAX_PSK_IDENTITY 64
#endif
#ifndef COAP_DTLS_MAX_PSK
#define COAP_DTLS_MAX_PSK 64
#endif

typedef enum coap_dtls_role_t {
  COAP_DTLS_ROLE_CLIENT, /**<为客户端调用的内部函数*/
  COAP_DTLS_ROLE_SERVER  /**<为服务器调用的内部函数*/
} coap_dtls_role_t;

#define COAP_DTLS_RPK_CERT_CN "RPK"

/**
 * 检查DTLS是否可用。
 *
 * @return @如果启用了对DTLS的支持，则为c 1，否则为@c 0。
 */
int coap_dtls_is_supported(void);

/**
 * 检查TLS是否可用。
 *
 * @return @如果启用TLS支持，则为c 1，否则为@c 0。
 */
int coap_tls_is_supported(void);

typedef enum coap_tls_library_t {
  COAP_TLS_LIBRARY_NOTLS = 0, /**<无DTLS库*/
  COAP_TLS_LIBRARY_TINYDTLS,  /**<使用TinyDTLS库*/
  COAP_TLS_LIBRARY_OPENSSL,   /**<使用OpenSSL库*/
  COAP_TLS_LIBRARY_GNUTLS,    /**<使用GnuTLS库*/
  COAP_TLS_LIBRARY_MBEDTLS,   /**<使用Mbed TLS库*/
} coap_tls_library_t;

/**
 * 用于返回底层（D）TLS库信息的结构。
 */
typedef struct coap_tls_version_t {
  uint64_t version; /**<（D）TLS运行库版本*/
  coap_tls_library_t type; /**<库类型。COAP_TLS_LIBRARY_*之一*/
  uint64_t built_version; /**<（D）TLS根据库版本构建*/
} coap_tls_version_t;

/**
 * 确定基础（D）TLS库的类型和版本。
 *
 * @return 库libcoap的版本和类型是根据编译的。
 */
coap_tls_version_t *coap_get_tls_library_version(void);

/**
 * 可由coap_context_set_pki（）设置的其他安全设置处理程序。在libcoap完成TLS级别的验证检查时调用，但应用程序需要执行一些额外的检查/更改/更新。
 *
 * @param tls_session 安全会话定义-例如OpenSSL的SSL*。如果服务器回调，则为NULL。这将取决于底层TLS库-请参阅coap_get_TLS_library_version（）
 * @param setup_data 包含最初传递到coap_context_set_pki（）或coap_new_client_session_pki（）中的设置数据的结构。
 *
 * @return @c 1如果成功，否则@c 0。
 */
typedef int (*coap_dtls_security_setup_t)(void* tls_session,
                                          coap_dtls_pki_t *setup_data);

/**
 * 可以通过coap_context_set_pki（）设置的CN验证回调。在libcoap完成TLS级别的验证检查时调用，但应用程序需要检查CN是否被允许。CN是证书中的SubjectAltName，如果不存在，则是主题名称的最左侧通用名称（CN）组件。注意：如果使用RPK，则公钥不包含CN，但COAP_DTLS_RPK_CERT_CN的内容将显示给@p CN参数。
 *
 * @param cn  根据证书确定的CN
 * @param asn1_public_cert  ASN。1个DER编码的X.509证书
 * @param asn1_length  ASN。1长度
 * @param coap_session  与证书更新关联的CoAP会话
 * @param depth  证书链的深度。如果为0，则为客户端证书，否则为CA
 * @param validated  TLS层在1
 * @param arg  与在setup_data->cn_call_back_arg中传递到coap_context_set_pki（）中的相同
 *
 * @return @c 1如果被接受，否则@c 0如果被拒绝。
 */
typedef int (*coap_dtls_cn_callback_t)(const char *cn,
             const uint8_t *asn1_public_cert,
             size_t asn1_length,
             coap_session_t *coap_session,
             unsigned int depth,
             int validated,
             void *arg);

/**
 * 用于确定提供的PKI ASN的枚举。1（DER）私钥格式。
 */
typedef enum coap_asn1_privatekey_type_t {
  COAP_ASN1_PKEY_NONE,     /**< NONE */
  COAP_ASN1_PKEY_RSA,      /**<RSA类型*/
  COAP_ASN1_PKEY_RSA2,     /**<RSA2型*/
  COAP_ASN1_PKEY_DSA,      /**<DSA类型*/
  COAP_ASN1_PKEY_DSA1,     /**<DSA1类型*/
  COAP_ASN1_PKEY_DSA2,     /**<DSA2类型*/
  COAP_ASN1_PKEY_DSA3,     /**<DSA3类型*/
  COAP_ASN1_PKEY_DSA4,     /**<DSA4类型*/
  COAP_ASN1_PKEY_DH,       /**<DH类型*/
  COAP_ASN1_PKEY_DHX,      /**<DHX型*/
  COAP_ASN1_PKEY_EC,       /**<EC型*/
  COAP_ASN1_PKEY_HMAC,     /**<HMAC类型*/
  COAP_ASN1_PKEY_CMAC,     /**<CMAC类型*/
  COAP_ASN1_PKEY_TLS1_PRF, /**<TLS1_PRF类型*/
  COAP_ASN1_PKEY_HKDF      /**<HKDF类型*/
} coap_asn1_privatekey_type_t;

/**
 * 用于确定PKI密钥格式的枚举。
 */
typedef enum coap_pki_key_t {
  COAP_PKI_KEY_PEM = 0,        /**<PKI密钥类型为PEM文件*/
  COAP_PKI_KEY_ASN1,           /**<PKI密钥类型为ASN。1（DER）缓冲器*/
  COAP_PKI_KEY_PEM_BUF,        /**<PKI密钥类型为PEM缓冲区*/
  COAP_PKI_KEY_PKCS11,         /**<PKI密钥类型为PKCS11（DER）*/
} coap_pki_key_t;

/**
 * 保存PKI PEM定义的结构。
 */
typedef struct coap_pki_key_pem_t {
  const char *ca_file;       /**<PEM格式的通用CA的文件位置*/
  const char *public_cert;   /**<公共证书的文件位置*/
  const char *private_key;   /**<PEM格式的私钥文件位置*/
} coap_pki_key_pem_t;

/**
 * 保存PKI PEM缓冲区定义的结构。证书和私钥数据必须采用PEM格式。
 *
 * 注意：出于性能原因（为了保存潜在的缓冲区副本），证书和密钥应该是以NULL结尾的字符串，并且长度包括此NULL终止符。不过，不要求使用NULL终止符，长度必须反映实际数据大小。
 */
typedef struct coap_pki_key_pem_buf_t {
  const uint8_t *ca_cert;     /**<PEM缓冲区通用CA证书*/
  const uint8_t *public_cert; /**<PEM缓冲区公钥，或公钥（如果是RPK）*/
  const uint8_t *private_key; /**<PEM buffer私钥如果RPK和'EC Private Key'，则可以用于public_cert和Private_Key*/
  size_t ca_cert_len;         /**<PEM缓冲区CA证书长度*/
  size_t public_cert_len;     /**<PEM缓冲区公共证书长度*/
  size_t private_key_len;     /**<PEM缓冲区私钥长度*/
} coap_pki_key_pem_buf_t;

/**
 * 保存PKI ASN的结构。1（DER）定义。
 */
typedef struct coap_pki_key_asn1_t {
  const uint8_t *ca_cert;     /**<ASN1（DER）通用CA证书*/
  const uint8_t *public_cert; /**<ASN1（DER）公钥，或公钥（如果是RPK）*/
  const uint8_t *private_key; /**<ASN1（DER）私钥*/
  size_t ca_cert_len;         /**<ASN1 CA证书长度*/
  size_t public_cert_len;     /**<ASN1公共证书长度*/
  size_t private_key_len;     /**<ASN1私钥长度*/
  coap_asn1_privatekey_type_t private_key_type; /**<私钥类型*/
} coap_pki_key_asn1_t;

/**
 * 保存PKI PKCS11定义的结构。
 */
typedef struct coap_pki_key_pkcs11_t {
  const char *ca;            /**<pkcs11:通用CA证书的URI*/
  const char *public_cert;   /**<pkcs11:公共证书的URI*/
  const char *private_key;   /**<pkcs11:私钥的URI*/
  const char *user_pin;      /**<User pin to access PKCS11。如果为NULL，则必须在PKCS11:URI中设置pin value=参数作为查询。*/
} coap_pki_key_pkcs11_t;

/**
 * 保存PKI密钥信息的结构。
 */
typedef struct coap_dtls_key_t {
  coap_pki_key_t key_type;          /**<密钥格式类型*/
  union {
    coap_pki_key_pem_t pem;          /**<对于PEM文件密钥*/
    coap_pki_key_pem_buf_t pem_buf;  /**<对于PEM记忆钥匙*/
    coap_pki_key_asn1_t asn1;        /**<对于ASN。1（DER）记忆键*/
    coap_pki_key_pkcs11_t pkcs11;    /**<对于PKCS11密钥*/
  } key;
} coap_dtls_key_t;

/**
 * 可以由coap_context_set_pki（）设置的服务器名称指示（SNI）验证回调。如果以前未看到SNI，则在将证书集发送回客户端之前调用，以便根据请求的SNI使用适当的证书集。
 *
 * @param sni  请求的SNI
 * @param arg  与在setup_data->sni_call_back_arg中传递到coap_context_set_pki（）中的相同
 *
 * @return 要使用的新证书集，如果拒绝SNI，则@c NULL。
 */
typedef coap_dtls_key_t *(*coap_dtls_pki_sni_callback_t)(const char *sni,
             void* arg);


#define COAP_DTLS_PKI_SETUP_VERSION 1 /**<最新PKI安装版本*/

/**
 * 用于定义要使用的PKI设置数据的结构。
 */
struct coap_dtls_pki_t {
  uint8_t version; /**设置为COAP_DTLS_PKI_SETUP_VERSION以支持此版本的结构*/

  /* 在libcoap中启用不同TLS功能的选项*/
  uint8_t verify_peer_cert;        /**如果要验证对等证书，则<1*/
  uint8_t check_common_ca;         /**＜1，如果对等证书由与本地证书相同的CA签名*/
  uint8_t allow_self_signed;       /**＜1，如果允许自签名证书。如果设置了check_common_ca，则忽略*/
  uint8_t allow_expired_certs;     /**如果允许过期证书，则<1*/
  uint8_t cert_chain_validation;   /**<1如果要检查cert_chain_verify_depth*/
  uint8_t cert_chain_verify_depth; /**<建议深度为3*/
  uint8_t check_cert_revocation;   /**如果需要撤销检查，则<1*/
  uint8_t allow_no_crl;            /**<1如果CRL不存在则忽略*/
  uint8_t allow_expired_crl;       /**<1，如果允许过期crl*/
  uint8_t allow_bad_md_hash;      /**如果允许不支持的MD哈希，则<1*/
  uint8_t allow_short_rsa_length; /**如果允许小的RSA密钥大小，则<1*/
  uint8_t is_rpk_not_cert;        /**<1是RPK而不是公共证书。如果设置，PKI密钥格式类型不能为*COAP_PKI_key_PEM*/
  uint8_t reserved[3];             /**<保留-必须设置为0以获得未来兼容性*/
                                   /* 选择的大小为3，以与下一个参数对齐，因此如果新定义的选项，它可以使用一个reservard插槽，因此无需更改COAP_DTLS_PKI_SETUP_VERSION，只需减少保留的[]计数。
                                    */

  /** CN检查回调函数。如果不为NULL，则在TLS连接已通过上述配置的TLS选项时调用，以便应用程序验证CN是否有效。
   */
  coap_dtls_cn_callback_t validate_cn_call_back;
  void *cn_call_back_arg;  /**<传入CN回调函数*/

  /** SNI检查回调函数。
   * If not @p NULL，如果以前未看到SNI，则在将证书集发送回客户端之前调用，以便根据请求的SNI使用适当的证书集。
   */
  coap_dtls_pki_sni_callback_t validate_sni_call_back;
  void *sni_call_back_arg;  /**<传入sni回调函数*/

  /** 当libcoap在TLS级别执行了标准的、定义的验证检查时，
   * If not @p NULL，从TLS客户端Hello连接设置中调用。
   */
  coap_dtls_security_setup_t additional_tls_setup_call_back;

  char* client_sni;    /**<如果不是NULL，则在客户端TLS设置中使用SNI。由客户端应用程序拥有，并且在调用coap_new_client_session_pki（）期间必须保持有效*/

  coap_dtls_key_t pki_key;  /**<PKI密钥定义*/
};

/**
 * 保存客户端PSK信息的结构。
 */
typedef struct coap_dtls_cpsk_info_t {
  coap_bin_const_t identity;
  coap_bin_const_t key;
} coap_dtls_cpsk_info_t;

/**
 * 可由coap_new_client_session_psk2（）设置的标识提示验证回调。当libcoap在TLS级别执行了验证检查时调用，但应用程序需要检查是否允许Identity Hint，因此需要为（D）TLS会话的Identity Hint使用适当的PSK信息。注意：（D）TLS1.3中不支持Identity Hint。
 *
 * @param hint  服务器提供了身份提示
 * @param coap_session  与标识提示关联的CoAP会话
 * @param arg  与在setup_data->ih_call_back_arg中传递到coap_new_client_session_psk2（）中的相同
 *
 * @return 出现错误时，新建coap_dtls_cpsk_info_t对象或@c NULL。
 */
typedef const coap_dtls_cpsk_info_t *(*coap_dtls_ih_callback_t)(
                                      coap_str_const_t *hint,
                                      coap_session_t *coap_session,
                                      void *arg);

#define COAP_DTLS_CPSK_SETUP_VERSION 1 /**<最新的CPSK安装版本*/

/**
 * 用于定义要使用的客户端PSK设置数据的结构。
 */
typedef struct coap_dtls_cpsk_t {
  uint8_t version; /**设置为COAP_DTLS_CPSK_SETUP_VERSION以支持此版本的结构*/

  /* 在libcoap中启用不同TLS功能的选项*/
  uint8_t reserved[7];             /**<保留-必须设置为0以获得未来兼容性*/
                                   /* 选择的大小为7，以与下一个参数对齐，因此如果新定义的选项，它可以使用一个reservard插槽，因此无需更改COAP_DTLS_CSK_SETUP_VERSION，只需减少保留的[]计数。
                                    */

  /** 标识提示检查回调函数。如果不是NULL，则在服务器提供标识提示（TLS1.2或更早版本）时调用。然后可以返回要使用的适当标识和预共享密钥。
   */
  coap_dtls_ih_callback_t validate_ih_call_back;
  void *ih_call_back_arg;  /**<传入Identity Hint回调函数*/

  char* client_sni;    /**<如果不是NULL，则在客户端TLS设置中使用SNI。由客户端应用程序拥有，并且在调用coap_new_client_session_psk2（）期间必须保持有效。注意：TinyDTLS不支持。*/

  coap_dtls_cpsk_info_t psk_info;  /**<客户端PSK定义*/
} coap_dtls_cpsk_t;

/**
 * 保存服务器预共享密钥和标识提示信息的结构。
 */
typedef struct coap_dtls_spsk_info_t {
  coap_bin_const_t hint;
  coap_bin_const_t key;
} coap_dtls_spsk_info_t;


/**
 * 可由coap_context_set_psk2（）设置的身份验证回调。当libcoap在TLS级别完成验证检查时调用，但应用程序需要检查身份是否被允许，并且需要为（D）TLS会话使用适当的预共享密钥。
 *
 * @param identity  客户提供的身份
 * @param coap_session  与标识提示关联的CoAP会话
 * @param arg  在setup_data->id_call_back_arg中传递到coap_context_set_psk2（）的值
 *
 * @return 包含预共享密钥的新coap_bin_const_t对象或
           @c出错时为NULL。注：此信息将复制到内部结构中。
 */
typedef const coap_bin_const_t *(*coap_dtls_id_callback_t)(
                                 coap_bin_const_t *identity,
                                 coap_session_t *coap_session,
                                 void *arg);
/**
 * 可以由coap_context_set_psk2（）设置的PSK SNI回调。当libcoap在TLS级别完成验证检查，并且应用程序需要：-a）检查是否允许SNI b）为（D）TLS会话提供适当的PSK信息时调用。
 *
 * @param sni  客户提供的SNI
 * @param coap_session  与SNI关联的CoAP会话
 * @param arg  与在setup_data->sni_call_back_arg中传递到coap_context_set_psk2（）中的相同
 *
 * @return 出现错误时，新建coap_dtls_spsk_info_t对象或@c NULL。
 */
typedef const coap_dtls_spsk_info_t *(*coap_dtls_psk_sni_callback_t)(
                                 const char *sni,
                                 coap_session_t *coap_session,
                                 void *arg);

#define COAP_DTLS_SPSK_SETUP_VERSION 1 /**<最新SPSK安装版本*/

/**
 * 用于定义要使用的服务器PSK设置数据的结构。
 */
typedef struct coap_dtls_spsk_t {
  uint8_t version; /**设置为COAP_DTLS_PSK_SETUP_VERSION以支持此版本的结构*/

  /* 在libcoap中启用不同TLS功能的选项*/
  uint8_t reserved[7];             /**<保留-必须设置为0以获得未来兼容性*/
                                   /* 选择的大小为7，以与下一个参数对齐，因此如果新定义的选项，它可以使用一个reservard插槽，因此无需更改COAP_DTLS_PSK_SETUP_VERSION，只需减少保留的[]计数。
                                    */

  /** 身份检查回调函数。
   * If not @p 当客户端提供标识时，将调用NULL。然后可以返回要使用的适当的预共享密钥。
   */
  coap_dtls_id_callback_t validate_id_call_back;
  void *id_call_back_arg;  /**<传入Identity回调函数*/

  /** SNI检查回调函数。
   * If not @p NULL，如果之前没有看到SNI并且在将PSK信息发送回客户端之前调用，以便可以基于请求的SNI使用适当的PSK信息。
   */
  coap_dtls_psk_sni_callback_t validate_sni_call_back;
  void *sni_call_back_arg;  /**<传入SNI回调函数*/

  coap_dtls_spsk_info_t psk_info;  /**<服务器PSK定义*/
} coap_dtls_spsk_t;


/** @} */

/**
 * @ingroup logging将（D）TLS日志记录级别设置为指定的@p级别。注意：如果处于指定级别，coap_log_level（）将影响输出。
 *
 * @param level 要使用的日志记录级别-LOG_*
 */
void coap_dtls_set_log_level(int level);

/**
 * @ingroup logging获取当前（D）TLS日志记录。
 *
 * @return 当前日志级别（log_*之一）。
 */
int coap_dtls_get_log_level(void);


#endif /* COAP_DTLS_H */

