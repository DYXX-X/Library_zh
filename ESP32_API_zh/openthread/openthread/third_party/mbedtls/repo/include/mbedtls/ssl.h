/**
 * \文件ssl.h
 *
 * \简短的SSL/TLS功能。
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
#ifndef MBEDTLS_SSL_H
#define MBEDTLS_SSL_H

#if !defined(MBEDTLS_CONFIG_FILE)
#include "mbedtls/config.h"
#else
#include MBEDTLS_CONFIG_FILE
#endif

#include "mbedtls/bignum.h"
#include "mbedtls/ecp.h"

#include "mbedtls/ssl_ciphersuites.h"

#if defined(MBEDTLS_X509_CRT_PARSE_C)
#include "mbedtls/x509_crt.h"
#include "mbedtls/x509_crl.h"
#endif

#if defined(MBEDTLS_DHM_C)
#include "mbedtls/dhm.h"
#endif

/* 为MBEDTLS_ECDSA_C添加保护，以确保由于ssl_srv中也存在保护，因此不会出现编译错误。c和ssl_cli.c在功能上存在差距，MBEDTLS_ECDSA_c需要访问ecdh_ctx结构，这似乎不正确。
 */
#if defined(MBEDTLS_ECDH_C) || defined(MBEDTLS_ECDSA_C)
#include "mbedtls/ecdh.h"
#endif

#if defined(MBEDTLS_ZLIB_SUPPORT)

#if defined(MBEDTLS_DEPRECATED_WARNING)
#warning "Record compression support via MBEDTLS_ZLIB_SUPPORT is deprecated and will be removed in the next major revision of the library"
#endif

#if defined(MBEDTLS_DEPRECATED_REMOVED)
#error "Record compression support via MBEDTLS_ZLIB_SUPPORT is deprecated and cannot be used if MBEDTLS_DEPRECATED_REMOVED is set"
#endif

#include "zlib.h"
#endif

#if defined(MBEDTLS_HAVE_TIME)
#include "mbedtls/platform_time.h"
#endif

#if defined(MBEDTLS_USE_PSA_CRYPTO)
#include "psa/crypto.h"
#endif /* MBEDTLS_USE_PSA_CRYPTO */

/*
 * SSL错误代码
 */
#define MBEDTLS_ERR_SSL_FEATURE_UNAVAILABLE               -0x7080  /**<请求的功能不可用。*/
#define MBEDTLS_ERR_SSL_BAD_INPUT_DATA                    -0x7100  /**<功能输入参数错误。*/
#define MBEDTLS_ERR_SSL_INVALID_MAC                       -0x7180  /**<消息MAC验证失败。*/
#define MBEDTLS_ERR_SSL_INVALID_RECORD                    -0x7200  /**<收到无效的SSL记录。*/
#define MBEDTLS_ERR_SSL_CONN_EOF                          -0x7280  /**<连接指示EOF。*/
#define MBEDTLS_ERR_SSL_UNKNOWN_CIPHER                    -0x7300  /**<收到未知密码。*/
#define MBEDTLS_ERR_SSL_NO_CIPHER_CHOSEN                  -0x7380  /**<服务器与客户端没有共同的密码套件。*/
#define MBEDTLS_ERR_SSL_NO_RNG                            -0x7400  /**<未向SSL模块提供RNG。*/
#define MBEDTLS_ERR_SSL_NO_CLIENT_CERTIFICATE             -0x7480  /**<没有从客户端接收到客户端认证，但身份验证模式需要。*/
#define MBEDTLS_ERR_SSL_CERTIFICATE_TOO_LARGE             -0x7500  /**<我们自己的证书太大，无法发送SSL消息。*/
#define MBEDTLS_ERR_SSL_CERTIFICATE_REQUIRED              -0x7580  /**<未设置自己的证书，但服务器需要该证书。*/
#define MBEDTLS_ERR_SSL_PRIVATE_KEY_REQUIRED              -0x7600  /**<未设置自己的私钥或预共享密钥，但需要。*/
#define MBEDTLS_ERR_SSL_CA_CHAIN_REQUIRED                 -0x7680  /**<未设置CA链，但需要操作。*/
#define MBEDTLS_ERR_SSL_UNEXPECTED_MESSAGE                -0x7700  /**<从我们的同行处收到意外消息。*/
#define MBEDTLS_ERR_SSL_FATAL_ALERT_MESSAGE               -0x7780  /**<从我们的同行收到致命警报消息。*/
#define MBEDTLS_ERR_SSL_PEER_VERIFY_FAILED                -0x7800  /**<我们的同行验证失败。*/
#define MBEDTLS_ERR_SSL_PEER_CLOSE_NOTIFY                 -0x7880  /**<对等方通知我们连接将关闭。*/
#define MBEDTLS_ERR_SSL_BAD_HS_CLIENT_HELLO               -0x7900  /**<ClientHello握手消息处理失败。*/
#define MBEDTLS_ERR_SSL_BAD_HS_SERVER_HELLO               -0x7980  /**<处理ServerHello握手消息失败。*/
#define MBEDTLS_ERR_SSL_BAD_HS_CERTIFICATE                -0x7A00  /**<证书握手消息处理失败。*/
#define MBEDTLS_ERR_SSL_BAD_HS_CERTIFICATE_REQUEST        -0x7A80  /**<处理CertificateRequest握手消息失败。*/
#define MBEDTLS_ERR_SSL_BAD_HS_SERVER_KEY_EXCHANGE        -0x7B00  /**<ServerKeyExchange握手消息处理失败。*/
#define MBEDTLS_ERR_SSL_BAD_HS_SERVER_HELLO_DONE          -0x7B80  /**<ServerHelloDone握手消息处理失败。*/
#define MBEDTLS_ERR_SSL_BAD_HS_CLIENT_KEY_EXCHANGE        -0x7C00  /**<ClientKeyExchange握手消息处理失败。*/
#define MBEDTLS_ERR_SSL_BAD_HS_CLIENT_KEY_EXCHANGE_RP     -0x7C80  /**<在DHM/ECDH Read Public中处理ClientKeyExchange握手消息失败。*/
#define MBEDTLS_ERR_SSL_BAD_HS_CLIENT_KEY_EXCHANGE_CS     -0x7D00  /**<在DHM/ECDH Calculate Secret中处理ClientKeyExchange握手消息失败。*/
#define MBEDTLS_ERR_SSL_BAD_HS_CERTIFICATE_VERIFY         -0x7D80  /**<处理CertificateVerify握手消息失败。*/
#define MBEDTLS_ERR_SSL_BAD_HS_CHANGE_CIPHER_SPEC         -0x7E00  /**<ChangeCipherSpec握手消息处理失败。*/
#define MBEDTLS_ERR_SSL_BAD_HS_FINISHED                   -0x7E80  /**<处理完成握手消息失败。*/
#define MBEDTLS_ERR_SSL_ALLOC_FAILED                      -0x7F00  /**<内存分配失败*/
#define MBEDTLS_ERR_SSL_HW_ACCEL_FAILED                   -0x7F80  /**<硬件加速功能返回错误*/
#define MBEDTLS_ERR_SSL_HW_ACCEL_FALLTHROUGH              -0x6F80  /**<硬件加速功能已跳过/仅保留数据*/
#define MBEDTLS_ERR_SSL_COMPRESSION_FAILED                -0x6F00  /**<压缩/解压缩处理失败*/
#define MBEDTLS_ERR_SSL_BAD_HS_PROTOCOL_VERSION           -0x6E80  /**<握手协议不在最小/最大范围内*/
#define MBEDTLS_ERR_SSL_BAD_HS_NEW_SESSION_TICKET         -0x6E00  /**<NewSessionTicket握手消息处理失败。*/
#define MBEDTLS_ERR_SSL_SESSION_TICKET_EXPIRED            -0x6D80  /**<会话票证已过期。*/
#define MBEDTLS_ERR_SSL_PK_TYPE_MISMATCH                  -0x6D00  /**<公钥类型不匹配（例如，要求交换RSA密钥并提供EC密钥）*/
#define MBEDTLS_ERR_SSL_UNKNOWN_IDENTITY                  -0x6C80  /**<收到未知身份（如PSK身份）*/
#define MBEDTLS_ERR_SSL_INTERNAL_ERROR                    -0x6C00  /**<内部错误（例如，低级模块中的意外故障）*/
#define MBEDTLS_ERR_SSL_COUNTER_WRAPPING                  -0x6B80  /**<计数器会换行（例如，交换的消息太多）。*/
#define MBEDTLS_ERR_SSL_WAITING_SERVER_HELLO_RENEGO       -0x6B00  /**<重新协商时ServerHello出现意外消息。*/
#define MBEDTLS_ERR_SSL_HELLO_VERIFY_REQUIRED             -0x6A80  /**<DTLS客户端必须重试hello验证*/
#define MBEDTLS_ERR_SSL_BUFFER_TOO_SMALL                  -0x6A00  /**<缓冲区太小，无法接收或写入消息*/
#define MBEDTLS_ERR_SSL_NO_USABLE_CIPHERSUITE             -0x6980  /**<所有常见的密码套件都不可用（例如，没有合适的证书，请参阅调试消息）。*/
#define MBEDTLS_ERR_SSL_WANT_READ                         -0x6900  /**<基础传输上当前没有可用的请求类型的数据。*/
#define MBEDTLS_ERR_SSL_WANT_WRITE                        -0x6880  /**<连接需要写调用。*/
#define MBEDTLS_ERR_SSL_TIMEOUT                           -0x6800  /**<操作超时。*/
#define MBEDTLS_ERR_SSL_CLIENT_RECONNECT                  -0x6780  /**<客户端从同一端口启动了重新连接。*/
#define MBEDTLS_ERR_SSL_UNEXPECTED_RECORD                 -0x6700  /**<记录标题看起来有效，但不是预期的。*/
#define MBEDTLS_ERR_SSL_NON_FATAL                         -0x6680  /**<收到的警报消息表示非致命错误。*/
#define MBEDTLS_ERR_SSL_INVALID_VERIFY_HASH               -0x6600  /**<无法设置用于验证CertificateVerify的哈希*/
#define MBEDTLS_ERR_SSL_CONTINUE_PROCESSING               -0x6580  /**<应进行进一步消息处理的仅内部消息信令*/
#define MBEDTLS_ERR_SSL_ASYNC_IN_PROGRESS                 -0x6500  /**<异步操作尚未完成。*/
#define MBEDTLS_ERR_SSL_EARLY_MESSAGE                     -0x6480  /**<仅内部消息，表示消息提前到达。*/
#define MBEDTLS_ERR_SSL_UNEXPECTED_CID                    -0x6000  /**<接收到具有意外CID的加密DTLS帧。*/
#define MBEDTLS_ERR_SSL_VERSION_MISMATCH                  -0x5F00  /**<由于意外的版本或配置，操作失败。*/
#define MBEDTLS_ERR_SSL_CRYPTO_IN_PROGRESS                -0x7000  /**<正在进行加密操作。请稍后再试。*/
#define MBEDTLS_ERR_SSL_BAD_CONFIG                        -0x5E80  /**<SSL配置中的值无效*/

/*
 * 各种常数
 */
#define MBEDTLS_SSL_MAJOR_VERSION_3             3
#define MBEDTLS_SSL_MINOR_VERSION_0             0   /*!< SSL v3.0*/
#define MBEDTLS_SSL_MINOR_VERSION_1             1   /*!< TLS v1.0*/
#define MBEDTLS_SSL_MINOR_VERSION_2             2   /*!< TLS 1.1版*/
#define MBEDTLS_SSL_MINOR_VERSION_3             3   /*!< TLS 1.2版*/
#define MBEDTLS_SSL_MINOR_VERSION_4             4   /*!< TLS v1.3（实验）*/

#define MBEDTLS_SSL_TRANSPORT_STREAM            0   /*!< TLS      */
#define MBEDTLS_SSL_TRANSPORT_DATAGRAM          1   /*!< DTLS     */

#define MBEDTLS_SSL_MAX_HOST_NAME_LEN           255 /*!< RFC 1035中定义的最大主机名*/
#define MBEDTLS_SSL_MAX_ALPN_NAME_LEN           255 /*!< RFC 7301 alpn ext.中协议名称的最大字节数*/

#define MBEDTLS_SSL_MAX_ALPN_LIST_LEN           65535 /*!< RFC 7301 alpn ext.中列表的最大大小（字节）*/

/* RFC 6066第4节，另请参阅ssl_tls中的mfl_code_to_length。c NONE必须为零，以便memset（）ing结构为零*/
#define MBEDTLS_SSL_MAX_FRAG_LEN_NONE           0   /*!< 不要使用此扩展*/
#define MBEDTLS_SSL_MAX_FRAG_LEN_512            1   /*!< 最大片段长度2^9*/
#define MBEDTLS_SSL_MAX_FRAG_LEN_1024           2   /*!< 最大片段长度2^10*/
#define MBEDTLS_SSL_MAX_FRAG_LEN_2048           3   /*!< 最大片段长度2^11*/
#define MBEDTLS_SSL_MAX_FRAG_LEN_4096           4   /*!< 最大片段长度2^12*/
#define MBEDTLS_SSL_MAX_FRAG_LEN_INVALID        5   /*!< 第一个无效值*/

#define MBEDTLS_SSL_IS_CLIENT                   0
#define MBEDTLS_SSL_IS_SERVER                   1

#define MBEDTLS_SSL_IS_NOT_FALLBACK             0
#define MBEDTLS_SSL_IS_FALLBACK                 1

#define MBEDTLS_SSL_EXTENDED_MS_DISABLED        0
#define MBEDTLS_SSL_EXTENDED_MS_ENABLED         1

#define MBEDTLS_SSL_CID_DISABLED                0
#define MBEDTLS_SSL_CID_ENABLED                 1

#define MBEDTLS_SSL_ETM_DISABLED                0
#define MBEDTLS_SSL_ETM_ENABLED                 1

#define MBEDTLS_SSL_COMPRESS_NULL               0
#define MBEDTLS_SSL_COMPRESS_DEFLATE            1

#define MBEDTLS_SSL_VERIFY_NONE                 0
#define MBEDTLS_SSL_VERIFY_OPTIONAL             1
#define MBEDTLS_SSL_VERIFY_REQUIRED             2
#define MBEDTLS_SSL_VERIFY_UNSET                3 /* 仅用于sni_authmode*/

#define MBEDTLS_SSL_LEGACY_RENEGOTIATION        0
#define MBEDTLS_SSL_SECURE_RENEGOTIATION        1

#define MBEDTLS_SSL_RENEGOTIATION_DISABLED      0
#define MBEDTLS_SSL_RENEGOTIATION_ENABLED       1

#define MBEDTLS_SSL_ANTI_REPLAY_DISABLED        0
#define MBEDTLS_SSL_ANTI_REPLAY_ENABLED         1

#define MBEDTLS_SSL_RENEGOTIATION_NOT_ENFORCED  -1
#define MBEDTLS_SSL_RENEGO_MAX_RECORDS_DEFAULT  16

#define MBEDTLS_SSL_LEGACY_NO_RENEGOTIATION     0
#define MBEDTLS_SSL_LEGACY_ALLOW_RENEGOTIATION  1
#define MBEDTLS_SSL_LEGACY_BREAK_HANDSHAKE      2

#define MBEDTLS_SSL_TRUNC_HMAC_DISABLED         0
#define MBEDTLS_SSL_TRUNC_HMAC_ENABLED          1
#define MBEDTLS_SSL_TRUNCATED_HMAC_LEN          10  /* 80位，rfc 6066第7节*/

#define MBEDTLS_SSL_SESSION_TICKETS_DISABLED     0
#define MBEDTLS_SSL_SESSION_TICKETS_ENABLED      1

#define MBEDTLS_SSL_CBC_RECORD_SPLITTING_DISABLED    0
#define MBEDTLS_SSL_CBC_RECORD_SPLITTING_ENABLED     1

#define MBEDTLS_SSL_ARC4_ENABLED                0
#define MBEDTLS_SSL_ARC4_DISABLED               1

#define MBEDTLS_SSL_PRESET_DEFAULT              0
#define MBEDTLS_SSL_PRESET_SUITEB               2

#define MBEDTLS_SSL_CERT_REQ_CA_LIST_ENABLED       1
#define MBEDTLS_SSL_CERT_REQ_CA_LIST_DISABLED      0

#define MBEDTLS_SSL_DTLS_SRTP_MKI_UNSUPPORTED    0
#define MBEDTLS_SSL_DTLS_SRTP_MKI_SUPPORTED      1

/*
 * DTLS重传计时器值的默认范围，以毫秒为单位。RFC 6347 4.2.4.1规定从1秒到60秒。
 */
#define MBEDTLS_SSL_DTLS_TIMEOUT_DFL_MIN    1000
#define MBEDTLS_SSL_DTLS_TIMEOUT_DFL_MAX   60000

/**
 * \name SECTION:模块设置
 *
 * 您可以为此模块设置的配置选项在本节中。在配置中更改它们。h或在编译器命令行上定义它们\{
 */

#if !defined(MBEDTLS_SSL_DEFAULT_TICKET_LIFETIME)
#define MBEDTLS_SSL_DEFAULT_TICKET_LIFETIME     86400 /**<会话票证的生存期（如果启用）*/
#endif

/*
 * 最大片段长度（字节）决定两个内部I/O缓冲区的大小。
 *
 * 注意：RFC定义了SSL/TLS消息的默认大小。如果您更改此处的值，其他客户端/服务器可能无法再与您通信。只有当您控制连接的两侧并在两侧减少连接时，或者如果您使用的是“最大片段长度”扩展，并且您知道所有对等方也在使用它，才可以更改此值！
 */
#if !defined(MBEDTLS_SSL_MAX_CONTENT_LEN)
#define MBEDTLS_SSL_MAX_CONTENT_LEN         16384   /**<输入/输出缓冲区的大小*/
#endif

#if !defined(MBEDTLS_SSL_IN_CONTENT_LEN)
#define MBEDTLS_SSL_IN_CONTENT_LEN MBEDTLS_SSL_MAX_CONTENT_LEN
#endif

#if !defined(MBEDTLS_SSL_OUT_CONTENT_LEN)
#define MBEDTLS_SSL_OUT_CONTENT_LEN MBEDTLS_SSL_MAX_CONTENT_LEN
#endif

/*
 * 用于DTLS握手消息重组和未来消息缓冲的最大堆分配字节数。
 */
#if !defined(MBEDTLS_SSL_DTLS_MAX_BUFFERING)
#define MBEDTLS_SSL_DTLS_MAX_BUFFERING 32768
#endif

/*
 * 传入和传出消息的最大CID长度。
 */
#if !defined(MBEDTLS_SSL_CID_IN_LEN_MAX)
#define MBEDTLS_SSL_CID_IN_LEN_MAX          32
#endif

#if !defined(MBEDTLS_SSL_CID_OUT_LEN_MAX)
#define MBEDTLS_SSL_CID_OUT_LEN_MAX         32
#endif

#if !defined(MBEDTLS_SSL_CID_PADDING_GRANULARITY)
#define MBEDTLS_SSL_CID_PADDING_GRANULARITY 16
#endif

#if !defined(MBEDTLS_SSL_TLS1_3_PADDING_GRANULARITY)
#define MBEDTLS_SSL_TLS1_3_PADDING_GRANULARITY 1
#endif

/* \}name SECTION:模块设置*/

/*
 * 安全重新协商的验证数据长度
 */
#if defined(MBEDTLS_SSL_PROTO_SSL3)
#define MBEDTLS_SSL_VERIFY_DATA_MAX_LEN 36
#else
#define MBEDTLS_SSL_VERIFY_DATA_MAX_LEN 12
#endif

/*
 * 信令密码组值（SCSV）
 */
#define MBEDTLS_SSL_EMPTY_RENEGOTIATION_INFO    0xFF   /**<重新协商信息文本*/
#define MBEDTLS_SSL_FALLBACK_SCSV_VALUE         0x5600 /**<RFC 7507第2节*/

/*
 * 支持的签名和哈希算法（适用于TLS 1.2）RFC 5246第7.4.1.4.1节
 */
#define MBEDTLS_SSL_HASH_NONE                0
#define MBEDTLS_SSL_HASH_MD5                 1
#define MBEDTLS_SSL_HASH_SHA1                2
#define MBEDTLS_SSL_HASH_SHA224              3
#define MBEDTLS_SSL_HASH_SHA256              4
#define MBEDTLS_SSL_HASH_SHA384              5
#define MBEDTLS_SSL_HASH_SHA512              6

#define MBEDTLS_SSL_SIG_ANON                 0
#define MBEDTLS_SSL_SIG_RSA                  1
#define MBEDTLS_SSL_SIG_ECDSA                3

/*
 * 客户端证书类型RFC 5246第7.4.4节和RFC 4492第5.5节
 */
#define MBEDTLS_SSL_CERT_TYPE_RSA_SIGN       1
#define MBEDTLS_SSL_CERT_TYPE_ECDSA_SIGN    64

/*
 * 消息、警报和握手类型
 */
#define MBEDTLS_SSL_MSG_CHANGE_CIPHER_SPEC     20
#define MBEDTLS_SSL_MSG_ALERT                  21
#define MBEDTLS_SSL_MSG_HANDSHAKE              22
#define MBEDTLS_SSL_MSG_APPLICATION_DATA       23
#define MBEDTLS_SSL_MSG_CID                    25

#define MBEDTLS_SSL_ALERT_LEVEL_WARNING         1
#define MBEDTLS_SSL_ALERT_LEVEL_FATAL           2

#define MBEDTLS_SSL_ALERT_MSG_CLOSE_NOTIFY           0  /* 0x00位*/
#define MBEDTLS_SSL_ALERT_MSG_UNEXPECTED_MESSAGE    10  /* 0x0A*/
#define MBEDTLS_SSL_ALERT_MSG_BAD_RECORD_MAC        20  /* 0x14像素*/
#define MBEDTLS_SSL_ALERT_MSG_DECRYPTION_FAILED     21  /* 0x15像素*/
#define MBEDTLS_SSL_ALERT_MSG_RECORD_OVERFLOW       22  /* 0x16像素*/
#define MBEDTLS_SSL_ALERT_MSG_DECOMPRESSION_FAILURE 30  /* 0x1E像素*/
#define MBEDTLS_SSL_ALERT_MSG_HANDSHAKE_FAILURE     40  /* 第28位*/
#define MBEDTLS_SSL_ALERT_MSG_NO_CERT               41  /* 第29页*/
#define MBEDTLS_SSL_ALERT_MSG_BAD_CERT              42  /* 0倍2A*/
#define MBEDTLS_SSL_ALERT_MSG_UNSUPPORTED_CERT      43  /* 0x2B倍*/
#define MBEDTLS_SSL_ALERT_MSG_CERT_REVOKED          44  /* 0x2摄氏度*/
#define MBEDTLS_SSL_ALERT_MSG_CERT_EXPIRED          45  /* 0x2D*/
#define MBEDTLS_SSL_ALERT_MSG_CERT_UNKNOWN          46  /* 0x2E*/
#define MBEDTLS_SSL_ALERT_MSG_ILLEGAL_PARAMETER     47  /* 0x2层*/
#define MBEDTLS_SSL_ALERT_MSG_UNKNOWN_CA            48  /* 0x30*/
#define MBEDTLS_SSL_ALERT_MSG_ACCESS_DENIED         49  /* 0x31个*/
#define MBEDTLS_SSL_ALERT_MSG_DECODE_ERROR          50  /* 0x32个*/
#define MBEDTLS_SSL_ALERT_MSG_DECRYPT_ERROR         51  /* 0x33个*/
#define MBEDTLS_SSL_ALERT_MSG_EXPORT_RESTRICTION    60  /* 0x3C级*/
#define MBEDTLS_SSL_ALERT_MSG_PROTOCOL_VERSION      70  /* 0时46分*/
#define MBEDTLS_SSL_ALERT_MSG_INSUFFICIENT_SECURITY 71  /* 第47页*/
#define MBEDTLS_SSL_ALERT_MSG_INTERNAL_ERROR        80  /* 50倍*/
#define MBEDTLS_SSL_ALERT_MSG_INAPROPRIATE_FALLBACK 86  /* 0时56分*/
#define MBEDTLS_SSL_ALERT_MSG_USER_CANCELED         90  /* 0x5安培*/
#define MBEDTLS_SSL_ALERT_MSG_NO_RENEGOTIATION     100  /* 0x64位*/
#define MBEDTLS_SSL_ALERT_MSG_UNSUPPORTED_EXT      110  /* 0x6E*/
#define MBEDTLS_SSL_ALERT_MSG_UNRECOGNIZED_NAME    112  /* 0倍70*/
#define MBEDTLS_SSL_ALERT_MSG_UNKNOWN_PSK_IDENTITY 115  /* 0秒73*/
#define MBEDTLS_SSL_ALERT_MSG_NO_APPLICATION_PROTOCOL 120 /* 0秒78*/

#define MBEDTLS_SSL_HS_HELLO_REQUEST            0
#define MBEDTLS_SSL_HS_CLIENT_HELLO             1
#define MBEDTLS_SSL_HS_SERVER_HELLO             2
#define MBEDTLS_SSL_HS_HELLO_VERIFY_REQUEST     3
#define MBEDTLS_SSL_HS_NEW_SESSION_TICKET       4
#define MBEDTLS_SSL_HS_CERTIFICATE             11
#define MBEDTLS_SSL_HS_SERVER_KEY_EXCHANGE     12
#define MBEDTLS_SSL_HS_CERTIFICATE_REQUEST     13
#define MBEDTLS_SSL_HS_SERVER_HELLO_DONE       14
#define MBEDTLS_SSL_HS_CERTIFICATE_VERIFY      15
#define MBEDTLS_SSL_HS_CLIENT_KEY_EXCHANGE     16
#define MBEDTLS_SSL_HS_FINISHED                20

/*
 * TLS扩展
 */
#define MBEDTLS_TLS_EXT_SERVERNAME                   0
#define MBEDTLS_TLS_EXT_SERVERNAME_HOSTNAME          0

#define MBEDTLS_TLS_EXT_MAX_FRAGMENT_LENGTH          1

#define MBEDTLS_TLS_EXT_TRUNCATED_HMAC               4

#define MBEDTLS_TLS_EXT_SUPPORTED_ELLIPTIC_CURVES   10
#define MBEDTLS_TLS_EXT_SUPPORTED_POINT_FORMATS     11

#define MBEDTLS_TLS_EXT_SIG_ALG                     13

#define MBEDTLS_TLS_EXT_USE_SRTP                    14

#define MBEDTLS_TLS_EXT_ALPN                        16

#define MBEDTLS_TLS_EXT_ENCRYPT_THEN_MAC            22 /* 0x16像素*/
#define MBEDTLS_TLS_EXT_EXTENDED_MASTER_SECRET  0x0017 /* 23 */

#define MBEDTLS_TLS_EXT_SESSION_TICKET              35

/* 截至draft-ietf-tls-dtls-connection-id-05，CID扩展的值仍然待定(https://tools.ietf.org/html/draft-ietf-tls-dtls-connection-id-05) */
#define MBEDTLS_TLS_EXT_CID                        254 /* TBD */

#define MBEDTLS_TLS_EXT_ECJPAKE_KKPP               256 /* 实验的*/

#define MBEDTLS_TLS_EXT_RENEGOTIATION_INFO      0xFF01

/*
 * 大小定义
 */
#if !defined(MBEDTLS_PSK_MAX_LEN)
#define MBEDTLS_PSK_MAX_LEN            32 /* 256位*/
#endif

/* 仅用于其尺寸的虚拟类型*/
union mbedtls_ssl_premaster_secret
{
#if defined(MBEDTLS_KEY_EXCHANGE_RSA_ENABLED)
    unsigned char _pms_rsa[48];                         /* RFC 5246 8.1.1 */
#endif
#if defined(MBEDTLS_KEY_EXCHANGE_DHE_RSA_ENABLED)
    unsigned char _pms_dhm[MBEDTLS_MPI_MAX_SIZE];      /* RFC 5246 8.1.2 */
#endif
#if defined(MBEDTLS_KEY_EXCHANGE_ECDHE_RSA_ENABLED)    || \
    defined(MBEDTLS_KEY_EXCHANGE_ECDHE_ECDSA_ENABLED)  || \
    defined(MBEDTLS_KEY_EXCHANGE_ECDH_RSA_ENABLED)     || \
    defined(MBEDTLS_KEY_EXCHANGE_ECDH_ECDSA_ENABLED)
    unsigned char _pms_ecdh[MBEDTLS_ECP_MAX_BYTES];    /* RFC 4492 5.10 */
#endif
#if defined(MBEDTLS_KEY_EXCHANGE_PSK_ENABLED)
    unsigned char _pms_psk[4 + 2 * MBEDTLS_PSK_MAX_LEN];       /* RFC 4279 2 */
#endif
#if defined(MBEDTLS_KEY_EXCHANGE_DHE_PSK_ENABLED)
    unsigned char _pms_dhe_psk[4 + MBEDTLS_MPI_MAX_SIZE
                                 + MBEDTLS_PSK_MAX_LEN];       /* RFC 4279 3 */
#endif
#if defined(MBEDTLS_KEY_EXCHANGE_RSA_PSK_ENABLED)
    unsigned char _pms_rsa_psk[52 + MBEDTLS_PSK_MAX_LEN];      /* RFC 4279 4 */
#endif
#if defined(MBEDTLS_KEY_EXCHANGE_ECDHE_PSK_ENABLED)
    unsigned char _pms_ecdhe_psk[4 + MBEDTLS_ECP_MAX_BYTES
                                   + MBEDTLS_PSK_MAX_LEN];     /* RFC 5489 2 */
#endif
#if defined(MBEDTLS_KEY_EXCHANGE_ECJPAKE_ENABLED)
    unsigned char _pms_ecjpake[32];     /* 螺纹规格：SHA-256输出*/
#endif
};

#define MBEDTLS_PREMASTER_SIZE     sizeof( union mbedtls_ssl_premaster_secret )

#ifdef __cplusplus
extern "C" {
#endif

/*
 * SSL状态机
 */
typedef enum
{
    MBEDTLS_SSL_HELLO_REQUEST,
    MBEDTLS_SSL_CLIENT_HELLO,
    MBEDTLS_SSL_SERVER_HELLO,
    MBEDTLS_SSL_SERVER_CERTIFICATE,
    MBEDTLS_SSL_SERVER_KEY_EXCHANGE,
    MBEDTLS_SSL_CERTIFICATE_REQUEST,
    MBEDTLS_SSL_SERVER_HELLO_DONE,
    MBEDTLS_SSL_CLIENT_CERTIFICATE,
    MBEDTLS_SSL_CLIENT_KEY_EXCHANGE,
    MBEDTLS_SSL_CERTIFICATE_VERIFY,
    MBEDTLS_SSL_CLIENT_CHANGE_CIPHER_SPEC,
    MBEDTLS_SSL_CLIENT_FINISHED,
    MBEDTLS_SSL_SERVER_CHANGE_CIPHER_SPEC,
    MBEDTLS_SSL_SERVER_FINISHED,
    MBEDTLS_SSL_FLUSH_BUFFERS,
    MBEDTLS_SSL_HANDSHAKE_WRAPUP,
    MBEDTLS_SSL_HANDSHAKE_OVER,
    MBEDTLS_SSL_SERVER_NEW_SESSION_TICKET,
    MBEDTLS_SSL_SERVER_HELLO_VERIFY_REQUEST_SENT,
}
mbedtls_ssl_states;

/*
 * tls_prf函数类型。
 */
typedef enum
{
   MBEDTLS_SSL_TLS_PRF_NONE,
   MBEDTLS_SSL_TLS_PRF_SSL3,
   MBEDTLS_SSL_TLS_PRF_TLS1,
   MBEDTLS_SSL_TLS_PRF_SHA384,
   MBEDTLS_SSL_TLS_PRF_SHA256
}
mbedtls_tls_prf_types;
/**
 * \简短回调类型：在网络上发送数据。
 *
 * \注意，回调可以是阻塞的，也可以是非阻塞的。
 *
 * \param ctx发送回调的上下文（通常是文件描述符）\param buf保存要发送数据的缓冲区\param len要发送的数据的长度
 *
 * \return回调必须返回发送的字节数（如果有）或非零错误代码。如果执行非阻塞I/O，当操作将阻塞时，必须返回\c MBEDTLS_ERROR_SSL_WANT_WRITE。
 *
 * \注意：允许回调发送的字节数少于请求的字节数。它必须始终返回实际发送的字节数。
 */
typedef int mbedtls_ssl_send_t( void *ctx,
                                const unsigned char *buf,
                                size_t len );

/**
 * \简短回调类型：从网络接收数据。
 *
 * \注意，回调可以是阻塞的，也可以是非阻塞的。
 *
 * \param ctx接收回调的上下文（通常是文件描述符）\param buf Buffer将接收到的数据写入接收缓冲区的长度
 *
 * \return回调必须返回接收的字节数或非零错误代码。如果执行非阻塞I/O，当操作将阻塞时，必须返回\c MBEDTLS_ERROR_SSL_WANT_READ。
 *
 * \注意，回调接收的字节可能少于缓冲区的长度。它必须始终返回实际接收并写入缓冲区的字节数。
 */
typedef int mbedtls_ssl_recv_t( void *ctx,
                                unsigned char *buf,
                                size_t len );

/**
 * \简短回调类型：从网络接收数据，超时
 *
 * \注意，回调必须阻塞，直到接收到数据，或者超时延迟到期，或者操作被信号中断。
 *
 * \param ctx接收回调的上下文（通常是文件描述符）\param buf将接收数据写入的缓冲区\param len接收缓冲区的长度\param timeout等待数据的最大毫秒数0表示没有超时（可能永远等待）
 *
 * \return回调必须返回接收的字节数，或者返回非零错误代码：如果操作超时，则返回\c MBEDTLS_error_SSL_TIMEOUT；如果被信号中断，则返回\\c MBEDTLS_error_SSL_WANT_READ。
 *
 * \注意，回调接收的字节可能少于缓冲区的长度。它必须始终返回实际接收并写入缓冲区的字节数。
 */
typedef int mbedtls_ssl_recv_timeout_t( void *ctx,
                                        unsigned char *buf,
                                        size_t len,
                                        uint32_t timeout );
/**
 * \简短回调类型：设置一对计时器/延迟以进行监视
 *
 * \param ctx上下文指针\param int_ms中间延迟（毫秒）\param fin_ms最终延迟（毫秒0）取消当前计时器。
 *
 * \注意：此回调必须至少存储关联的\c mbedtls_ssl_get_timer_t回调返回正确信息所需的信息。
 *
 * \注意：如果使用事件驱动的编程风格，则必须在经过最终延迟时生成事件。该事件必须导致使用正确的ssl上下文调用\c mbedtls_ssl_handshake（）。必须小心确保每次最多发生一次此类呼叫。
 *
 * \注意：一次只能运行一个计时器。在计时器运行时调用此函数必须取消它。取消的计时器不能生成任何事件。
 */
typedef void mbedtls_ssl_set_timer_t( void * ctx,
                                      uint32_t int_ms,
                                      uint32_t fin_ms );

/**
 * \简短回调类型：获取计时器/延迟的状态
 *
 * \param ctx上下文指针
 *
 * \return此回调必须返回：
 *                 -如果取消（fin_ms==0），则为1；如果没有延迟通过，则为0；如果只有中间延迟通过，那么为1。
 */
typedef int mbedtls_ssl_get_timer_t( void * ctx );

/* 定义如下*/
typedef struct mbedtls_ssl_session mbedtls_ssl_session;
typedef struct mbedtls_ssl_context mbedtls_ssl_context;
typedef struct mbedtls_ssl_config  mbedtls_ssl_config;

/* 在ssl_internal中定义。小时*/
typedef struct mbedtls_ssl_transform mbedtls_ssl_transform;
typedef struct mbedtls_ssl_handshake_params mbedtls_ssl_handshake_params;
typedef struct mbedtls_ssl_sig_hash_set_t mbedtls_ssl_sig_hash_set_t;
#if defined(MBEDTLS_X509_CRT_PARSE_C)
typedef struct mbedtls_ssl_key_cert mbedtls_ssl_key_cert;
#endif
#if defined(MBEDTLS_SSL_PROTO_DTLS)
typedef struct mbedtls_ssl_flight_item mbedtls_ssl_flight_item;
#endif

#if defined(MBEDTLS_SSL_ASYNC_PRIVATE)
#if defined(MBEDTLS_X509_CRT_PARSE_C)
/**
 * \brief回调类型：启动外部签名操作。
 *
 *                  在SSL握手期间调用此回调，以使用外部处理器启动签名解密操作。参数\p-cert包含公钥；由回调函数决定如何访问相关的私钥。
 *
 *                  此函数通常发送请求或将请求排入队列，而不等待操作完成。这允许握手步骤是非阻塞的。
 *
 *                  参数\p ssl和\p cert保证在整个握手过程中保持有效。另一方面，如果后续处理需要该值，则该函数必须保存\p哈希的内容，因为在该函数返回后，\p哈希缓冲区不再有效。
 *
 *                  此函数可以调用mbedtls_ssl_set_async_operation_data（）来存储操作上下文，以便稍后通过恢复或取消回调进行检索。
 *
 * \注意：对于RSA签名，此函数必须以与mbedtls_RSA_pkcs1_sign（）相同的方式生成与PKCS#1 v1.5一致的输出。在执行私钥操作之前，应用RFC 8017第9.2节“EMSA-PKCS1-v1_5”中描述的填充步骤，如下所示。
 *                  -如果\p md_alg为#MBEDTLS_md_NONE，则应用PKCS#1 v1.5编码，将\p哈希视为要填充的DigestInfo。换句话说，从步骤3开始应用EMSA-PKCS1-v1_5，使用“T=hash”和“tLen=hash_len”。
 *                  -如果`md_alg！=MBEDTLS_MD_NONE`，应用PKCS#1 v1.5编码，将\p哈希视为要编码和填充的哈希。换句话说，从步骤2开始应用EMSA-PKCS1-v1_5，通过在\p md_alg上调用mbedtls_oid_get_oid_by_md（）获得“digitalAlgorithm”。
 *
 * \注意：对于ECDSA签名，输出格式为[RFC 4492第5.4节]中定义的DER编码“ECDSA Sig Value”(https://tools.ietf.org/html/rfc4492#section-5.4).
 *
 * \param ssl ssl连接实例。除了通过mbedtls_ssl_set_async_operation_data（）之外，不应修改它。\param cert包含公钥的证书。在简单的情况下，这是配置ssl连接时传递给mbedtls_ssl_conf_own_cert（）的指针之一。但是，如果使用其他回调，则此属性可能不适用。例如，如果使用mbedtls_ssl_conf_SNI（）注册了SNI回调，则该回调将确定使用的证书。\param md_alg哈希算法。\param hash包含哈希的缓冲区。当函数返回时，此缓冲区不再有效。\param hash_len哈希缓冲区的大小（字节）。
 *
 * \如果操作成功启动，则返回0，并且SSL堆栈应立即调用恢复回调。\return#MBEDTLS_ERROR_SSL_ASYNC_IN_PROGRESS，如果操作已成功启动，则SSL堆栈应立即返回，而不调用恢复回调。\如果外部处理器不支持此密钥，则返回#MBEDTLS_ERROR_SSL_HW_ACCEL_FALLTHROUGH。SSL堆栈将改用私钥对象。\return任何其他错误都表示严重失败，并在调用链上传播。回调应使用\c MBEDTLS_error_PK_xxx错误代码，且<b>不得</b>使用\c EMBEDTLS_ERR_SSL_xxx错误代码，除非此回调的文档中另有说明。
 */
typedef int mbedtls_ssl_async_sign_t( mbedtls_ssl_context *ssl,
                                      mbedtls_x509_crt *cert,
                                      mbedtls_md_type_t md_alg,
                                      const unsigned char *hash,
                                      size_t hash_len );

/**
 * \brief回调类型：启动外部解密操作。
 *
 *                  在SSL握手期间调用此回调，以使用外部处理器启动RSA解密操作。参数\p-cert包含公钥；由回调函数决定如何访问相关的私钥。
 *
 *                  此函数通常发送请求或将请求排入队列，而不等待操作完成。这允许握手步骤是非阻塞的。
 *
 *                  参数\p ssl和\p cert保证在整个握手过程中保持有效。另一方面，如果需要稍后处理该值，则该函数必须保存\p输入的内容，因为在该函数返回后，\p输入缓冲区不再有效。
 *
 *                  此函数可以调用mbedtls_ssl_set_async_operation_data（）来存储操作上下文，以便稍后通过恢复或取消回调进行检索。
 *
 * \警告TLS中使用的RSA解密可能受到Bleichenbacher于1998年首次发现的定时侧信道攻击。这种攻击在实践中可以远程利用。为避免此攻击，必须确保如果回调执行RSA解密，执行并返回结果所需的时间不取决于RSA解密是否成功或报告的填充无效。
 *
 * \param ssl ssl连接实例。除了通过mbedtls_ssl_set_async_operation_data（）之外，不应修改它。\param cert包含公钥的证书。在简单的情况下，这是配置ssl连接时传递给mbedtls_ssl_conf_own_cert（）的指针之一。但是，如果使用其他回调，则此属性可能不适用。例如，如果使用mbedtls_ssl_conf_SNI（）注册了SNI回调，则该回调将确定使用的证书。\param input包含输入密文的缓冲区。当函数返回时，此缓冲区不再有效。\param input_len输入缓冲区的大小（字节）。
 *
 * \如果操作成功启动，则返回0，并且SSL堆栈应立即调用恢复回调。\return#MBEDTLS_ERROR_SSL_ASYNC_IN_PROGRESS，如果操作已成功启动，则SSL堆栈应立即返回，而不调用恢复回调。\如果外部处理器不支持此密钥，则返回#MBEDTLS_ERROR_SSL_HW_ACCEL_FALLTHROUGH。SSL堆栈将改用私钥对象。\return任何其他错误都表示严重失败，并在调用链上传播。回调应使用\c MBEDTLS_error_PK_xxx错误代码，且<b>不得</b>使用\c EMBEDTLS_ERR_SSL_xxx错误代码，除非此回调的文档中另有说明。
 */
typedef int mbedtls_ssl_async_decrypt_t( mbedtls_ssl_context *ssl,
                                         mbedtls_x509_crt *cert,
                                         const unsigned char *input,
                                         size_t input_len );
#endif /* MBEDTLS_X509_CRT_PARSE_C */

/**
 * \简短回调类型：恢复外部操作。
 *
 *                  在SSL握手期间调用此回调以恢复由：：mbedtls_SSL_async_sign_t或：：mbedtls_SSL_async_decrypt_t回调启动的外部操作。
 *
 *                  此函数通常检查挂起请求的状态或使请求队列取得进展，而不等待操作完成。这允许握手步骤是非阻塞的。
 *
 *                  此函数可以调用mbedtls_ssl_get_async_operation_data（）来检索启动回调设置的操作上下文。它可以调用mbedtls_ssl_set_async_operation_data（）来修改此上下文。
 *
 *                  请注意，当此函数返回的状态不是#MBEDTLS_ERROR_SSL_ASYNC_IN_PROGRESS时，它必须释放与操作相关的任何资源。
 *
 * \param ssl ssl连接实例。除了通过mbedtls_ssl_set_async_operation_data（）之外，不应修改它。\param output成功时包含输出（签名或解密数据）的缓冲区。\param output_len成功时，写入\p输出的字节数。\param output_size输出缓冲区的大小（字节）。
 *
 * \如果运算的输出在\p输出缓冲区中可用，则返回0。\如果操作仍在进行，则返回#MBEDTLS_ERROR_SSL_ASYNC_IN_PROGRESS。SSL连接上的后续进度请求将再次调用恢复回调。\return任何其他错误都意味着操作被中止。SSL握手已中止。回调应使用\c MBEDTLS_error_PK_xxx错误代码，且<b>不得</b>使用\c EMBEDTLS_ERR_SSL_xxx错误代码，除非此回调的文档中另有说明。
 */
typedef int mbedtls_ssl_async_resume_t( mbedtls_ssl_context *ssl,
                                        unsigned char *output,
                                        size_t *output_len,
                                        size_t output_size );

/**
 * \简短回调类型：取消外部操作。
 *
 *                  如果在进行异步操作时关闭了SSL连接，则调用此回调。请注意，如果：：mbedtls_ssl_async_resume_t回调已运行并返回了#mbedtls_ERROR_ssl_async_IN_PROGRESS以外的值，则不会调用此回调，因为在这种情况下，异步操作已完成。
 *
 *                  此函数可以调用mbedtls_ssl_get_async_operation_data（）来检索启动回调设置的操作上下文。
 *
 * \param ssl ssl连接实例。不应修改。
 */
typedef void mbedtls_ssl_async_cancel_t( mbedtls_ssl_context *ssl );
#endif /* MBEDTLS_SSL_ASYNC_PRIVATE */

#if defined(MBEDTLS_KEY_EXCHANGE_WITH_CERT_ENABLED) &&        \
    !defined(MBEDTLS_SSL_KEEP_PEER_CERTIFICATE)
#define MBEDTLS_SSL_PEER_CERT_DIGEST_MAX_LEN  48
#if defined(MBEDTLS_SHA256_C)
#define MBEDTLS_SSL_PEER_CERT_DIGEST_DFL_TYPE MBEDTLS_MD_SHA256
#define MBEDTLS_SSL_PEER_CERT_DIGEST_DFL_LEN  32
#elif defined(MBEDTLS_SHA512_C)
#define MBEDTLS_SSL_PEER_CERT_DIGEST_DFL_TYPE MBEDTLS_MD_SHA384
#define MBEDTLS_SSL_PEER_CERT_DIGEST_DFL_LEN  48
#elif defined(MBEDTLS_SHA1_C)
#define MBEDTLS_SSL_PEER_CERT_DIGEST_DFL_TYPE MBEDTLS_MD_SHA1
#define MBEDTLS_SSL_PEER_CERT_DIGEST_DFL_LEN  20
#else
/* 这已经在check_config.h中进行了检查，但请确保。*/
#error "Bad configuration - need SHA-1, SHA-256 or SHA-512 enabled to compute digest of peer CRT."
#endif
#endif /* MBEDTLS_KEY_EXCHANGE_WITH_CERT_ENABLED && !MBEDTLS_SSL_KEEP_PEER_CERTIFICATE */

#if defined(MBEDTLS_SSL_DTLS_SRTP)

#define MBEDTLS_TLS_SRTP_MAX_MKI_LENGTH             255
#define MBEDTLS_TLS_SRTP_MAX_PROFILE_LIST_LENGTH    4
/*
 * 为了代码的可读性，DTLS-SRTP配置文件使用typedef
 *
 * 使用中定义的扩展保护配置文件值（_S）http://www.iana.org/assignments/srtp-protection/srtp-protection.xhtml
 *
 * 提醒：如果展开此列表，则还必须更新mbedtls_ssl_check_srtp_profile_value。
 */
#define MBEDTLS_TLS_SRTP_AES128_CM_HMAC_SHA1_80     ( (uint16_t) 0x0001)
#define MBEDTLS_TLS_SRTP_AES128_CM_HMAC_SHA1_32     ( (uint16_t) 0x0002)
#define MBEDTLS_TLS_SRTP_NULL_HMAC_SHA1_80          ( (uint16_t) 0x0005)
#define MBEDTLS_TLS_SRTP_NULL_HMAC_SHA1_32          ( (uint16_t) 0x0006)
/* 这一个不是由iana定义的，而是为了代码的可读性。*/
#define MBEDTLS_TLS_SRTP_UNSET                      ( (uint16_t) 0x0000)

typedef uint16_t mbedtls_ssl_srtp_profile;

typedef struct mbedtls_dtls_srtp_info_t
{
    /*! 已协商的SRTP配置文件。*/
    mbedtls_ssl_srtp_profile chosen_dtls_srtp_profile;
    /*! mki_value的长度。*/
    uint16_t mki_len;
    /*! 使用的mki_value，最大大小为256字节。*/
    unsigned char mki_value[MBEDTLS_TLS_SRTP_MAX_MKI_LENGTH];
}
mbedtls_dtls_srtp_info;

#endif /* MBEDTLS_SSL_DTLS_SRTP */

/*
 * 此结构用于存储当前会话数据。
 *
 * 注意：更改此定义时，我们需要检查并更新：
 *  -在tests/suites/test_suite_ssl.function:sslpopulate_session（）和ssl_serialize_session_save_load（）中
 *  -在库/ssl_tls.c中：mbedtls_ssl_session_init（）和mbedtls_ssl_session_free（）mbedtls-ssl_sessions_save（）和ssl_session_load（）ssl_session_copy（）
 */
struct mbedtls_ssl_session
{
#if defined(MBEDTLS_HAVE_TIME)
    mbedtls_time_t start;       /*!< 起始时间*/
#endif
    int ciphersuite;            /*!< 选定密码组*/
    int compression;            /*!< 选定的压缩*/
    size_t id_len;              /*!< 会话id长度*/
    unsigned char id[32];       /*!< 会话标识符*/
    unsigned char master[48];   /*!< 主秘密*/

#if defined(MBEDTLS_X509_CRT_PARSE_C)
#if defined(MBEDTLS_SSL_KEEP_PEER_CERTIFICATE)
    mbedtls_x509_crt *peer_cert;       /*!< 对等X.509证书链*/
#else /* MBEDTLS_SSL_KEEP_PEER_CERTIFICATE */
    /*! 对端CRT的摘要。必须保持此状态，以在重新协商期间检测CRT更改，从而减轻三次握手攻击。*/
    unsigned char *peer_cert_digest;
    size_t peer_cert_digest_len;
    mbedtls_md_type_t peer_cert_digest_type;
#endif /* !MBEDTLS_SSL_KEEP_PEER_CERTIFICATE */
#endif /* MBEDTLS_X509_CRT_PARSE_C */
    uint32_t verify_result;          /*!<  验证结果*/

#if defined(MBEDTLS_SSL_SESSION_TICKETS) && defined(MBEDTLS_SSL_CLI_C)
    unsigned char *ticket;      /*!< RFC 5077会话票证*/
    size_t ticket_len;          /*!< 会话票证长度*/
    uint32_t ticket_lifetime;   /*!< 票证生存期提示*/
#endif /* MBEDTLS_SSL_SESSION_TICKETS && MBEDTLS_SSL_CLI_C */

#if defined(MBEDTLS_SSL_MAX_FRAGMENT_LENGTH)
    unsigned char mfl_code;     /*!< 对等方协商的MaxFragmentLength*/
#endif /* MBEDTLS_SSL_MAX_FRAGMENT_LENGTH */

#if defined(MBEDTLS_SSL_TRUNCATED_HMAC)
    int trunc_hmac;             /*!< 截断hmac激活标志*/
#endif /* MBEDTLS_SSL_TRUNCATED_HMAC */

#if defined(MBEDTLS_SSL_ENCRYPT_THEN_MAC)
    int encrypt_then_mac;       /*!< EtM激活标志*/
#endif
};

/**
 * 要在mbedtls_SSL_context结构之间共享的SSL/TLS配置。
 */
struct mbedtls_ssl_config
{
    /* 按大小分组项目（先最大）以最小化填充开销*/

    /*
     * 指针
     */

    const int *ciphersuite_list[4]; /*!< 每个版本允许的密码套件*/

    /**打印调试输出的回调*/
    void (*f_dbg)(void *, int, const char *, int, const char *);
    void *p_dbg;                    /*!< 调试函数的上下文*/

    /**获取（伪）随机数的回调*/
    int  (*f_rng)(void *, unsigned char *, size_t);
    void *p_rng;                    /*!< RNG功能的上下文*/

    /**回调以从缓存中检索会话*/
    int (*f_get_cache)(void *, mbedtls_ssl_session *);
    /**回调以将会话存储到缓存中*/
    int (*f_set_cache)(void *, const mbedtls_ssl_session *);
    void *p_cache;                  /*!< 缓存回调的上下文*/

#if defined(MBEDTLS_SSL_SERVER_NAME_INDICATION)
    /**根据SNI扩展设置证书的回调*/
    int (*f_sni)(void *, mbedtls_ssl_context *, const unsigned char *, size_t);
    void *p_sni;                    /*!< SNI回调的上下文*/
#endif

#if defined(MBEDTLS_X509_CRT_PARSE_C)
    /**回调以自定义X.509证书链验证*/
    int (*f_vrfy)(void *, mbedtls_x509_crt *, int, uint32_t *);
    void *p_vrfy;                   /*!< X.509验证回调的上下文*/
#endif

#if defined(MBEDTLS_KEY_EXCHANGE_SOME_PSK_ENABLED)
    /**从标识检索PSK密钥的回调*/
    int (*f_psk)(void *, mbedtls_ssl_context *, const unsigned char *, size_t);
    void *p_psk;                    /*!< PSK回调上下文*/
#endif

#if defined(MBEDTLS_SSL_DTLS_HELLO_VERIFY) && defined(MBEDTLS_SSL_SRV_C)
    /**回调以创建和编写ClientHello验证的cookie*/
    int (*f_cookie_write)( void *, unsigned char **, unsigned char *,
                           const unsigned char *, size_t );
    /**回调以验证ClientHello cookie的有效性*/
    int (*f_cookie_check)( void *, const unsigned char *, size_t,
                           const unsigned char *, size_t );
    void *p_cookie;                 /*!< cookie回调的上下文*/
#endif

#if defined(MBEDTLS_SSL_SESSION_TICKETS) && defined(MBEDTLS_SSL_SRV_C)
    /**回调以创建和写入会话票证*/
    int (*f_ticket_write)( void *, const mbedtls_ssl_session *,
            unsigned char *, const unsigned char *, size_t *, uint32_t * );
    /**回调以将会话票证解析为会话结构*/
    int (*f_ticket_parse)( void *, mbedtls_ssl_session *, unsigned char *, size_t);
    void *p_ticket;                 /*!< 票证回调的上下文*/
#endif /* MBEDTLS_SSL_SESSION_TICKETS && MBEDTLS_SSL_SRV_C */

#if defined(MBEDTLS_SSL_EXPORT_KEYS)
    /**回调以导出密钥块和主密钥*/
    int (*f_export_keys)( void *, const unsigned char *,
            const unsigned char *, size_t, size_t, size_t );
    /**回调以导出密钥块、主密钥、tls_prf和随机字节。应替换f_export_keys*/
    int (*f_export_keys_ext)( void *, const unsigned char *,
                const unsigned char *, size_t, size_t, size_t,
                const unsigned char[32], const unsigned char[32],
                mbedtls_tls_prf_types );
    void *p_export_keys;            /*!< 密钥导出回调的上下文*/
#endif

#if defined(MBEDTLS_SSL_DTLS_CONNECTION_ID)
    size_t cid_len; /*!< 传入DTLS记录的CID长度。*/
#endif /* MBEDTLS_SSL_DTLS_CONNECTION_ID */

#if defined(MBEDTLS_X509_CRT_PARSE_C)
    const mbedtls_x509_crt_profile *cert_profile; /*!< 验证配置文件*/
    mbedtls_ssl_key_cert *key_cert; /*!< 自己的证书/密钥对*/
    mbedtls_x509_crt *ca_chain;     /*!< 受信任的CA*/
    mbedtls_x509_crl *ca_crl;       /*!< 可信CA CRL*/
#if defined(MBEDTLS_X509_TRUSTED_CERTIFICATE_CALLBACK)
    mbedtls_x509_crt_ca_cb_t f_ca_cb;
    void *p_ca_cb;
#endif /* MBEDTLS_X509_TRUSTED_CERTIFICATE_CALLBACK */
#endif /* MBEDTLS_X509_CRT_PARSE_C */

#if defined(MBEDTLS_SSL_ASYNC_PRIVATE)
#if defined(MBEDTLS_X509_CRT_PARSE_C)
    mbedtls_ssl_async_sign_t *f_async_sign_start; /*!< 启动异步签名操作*/
    mbedtls_ssl_async_decrypt_t *f_async_decrypt_start; /*!< 启动异步解密操作*/
#endif /* MBEDTLS_X509_CRT_PARSE_C */
    mbedtls_ssl_async_resume_t *f_async_resume; /*!< 恢复异步操作*/
    mbedtls_ssl_async_cancel_t *f_async_cancel; /*!< 取消异步操作*/
    void *p_async_config_data; /*!< mbedtls_ssl_conf_async_private_cb（）设置的配置数据。*/
#endif /* MBEDTLS_SSL_ASYNC_PRIVATE */

#if defined(MBEDTLS_KEY_EXCHANGE_WITH_CERT_ENABLED)
    const int *sig_hashes;          /*!< 允许的签名哈希*/
#endif

#if defined(MBEDTLS_ECP_C)
    const mbedtls_ecp_group_id *curve_list; /*!< 允许的曲线*/
#endif

#if defined(MBEDTLS_DHM_C)
    mbedtls_mpi dhm_P;              /*!< DHM的素模量*/
    mbedtls_mpi dhm_G;              /*!< DHM发电机*/
#endif

#if defined(MBEDTLS_KEY_EXCHANGE_SOME_PSK_ENABLED)

#if defined(MBEDTLS_USE_PSA_CRYPTO)
    psa_key_id_t psk_opaque; /*!< PSA钥匙槽保持不透明PSK。此字段只能通过mbedtls_ssl_conf_psk_opaque（）设置。如果未配置PSK或原始PSK，则值为\c 0。
                              */
#endif /* MBEDTLS_USE_PSA_CRYPTO */

    unsigned char *psk;      /*!< 原始预共享密钥。此字段只能通过mbedtls_ssl_conf_psk（）设置。如果未配置PSK或不透明PSK，则值为NULL。*/
    size_t         psk_len;  /*!< 原始预共享密钥的长度。此字段只能通过mbedtls_ssl_conf_psk（）设置。当且仅当*\c psk不是\c NULL时，其值为非零。*/

    unsigned char *psk_identity;    /*!< PSK协商的PSK标识。此字段只能通过mbedtls_ssl_conf_psk（）设置。当且仅当设置了\c psk或\c psk_oopaque时，才会设置此选项。*/
    size_t         psk_identity_len;/*!< PSK标识的长度。此字段只能通过mbedtls_ssl_conf_psk（）设置。当且仅当\c psk不为\c NULL或\c psk_oopaque*不为\c0时，其值为非零。*/
#endif /* MBEDTLS_KEY_EXCHANGE_SOME_PSK_ENABLED */

#if defined(MBEDTLS_SSL_ALPN)
    const char **alpn_list;         /*!< 协议有序列表*/
#endif

#if defined(MBEDTLS_SSL_DTLS_SRTP)
    /*! 支持的srtp配置文件的有序列表*/
    const mbedtls_ssl_srtp_profile *dtls_srtp_profile_list;
    /*! 支持的配置文件数*/
    size_t dtls_srtp_profile_list_len;
#endif /* MBEDTLS_SSL_DTLS_SRTP */

    /*
     * 数字设置（先int后char）
     */

    uint32_t read_timeout;          /*!< mbedtls_ssl_read超时（毫秒）*/

#if defined(MBEDTLS_SSL_PROTO_DTLS)
    uint32_t hs_timeout_min;        /*!< 握手重传超时的初始值（ms）*/
    uint32_t hs_timeout_max;        /*!< 握手重传超时的最大值（毫秒）*/
#endif

#if defined(MBEDTLS_SSL_RENEGOTIATION)
    int renego_max_records;         /*!< 重新谈判的宽限期*/
    unsigned char renego_period[8]; /*!< 触发重新协商的记录计数器的值*/
#endif

#if defined(MBEDTLS_SSL_DTLS_BADMAC_LIMIT)
    unsigned int badmac_limit;      /*!< 具有坏MAC的记录限制*/
#endif

#if defined(MBEDTLS_DHM_C) && defined(MBEDTLS_SSL_CLI_C)
    unsigned int dhm_min_bitlen;    /*!< DHM素数的最小比特长度*/
#endif

    unsigned char max_major_ver;    /*!< 使用的最大主要版本*/
    unsigned char max_minor_ver;    /*!< 使用的最大次要版本*/
    unsigned char min_major_ver;    /*!< 使用的最小主要版本*/
    unsigned char min_minor_ver;    /*!< 使用的最小次要版本*/

    /*
     * 标志（位字段）
     */

    unsigned int endpoint : 1;      /*!< 0:客户端，1:服务器*/
    unsigned int transport : 1;     /*!< 流（TLS）或数据报（DTLS）*/
    unsigned int authmode : 2;      /*!< MBEDTLS_SSL_VERIFY_XXX             */
    /* 即使LEGACY_BREAK_HANDSHAKE禁用了反悔，也需要*/
    unsigned int allow_legacy_renegotiation : 2 ; /*!< MBEDTLS_LEGACY_XXX   */
#if defined(MBEDTLS_ARC4_C)
    unsigned int arc4_disabled : 1; /*!< RC4密码套件黑名单？*/
#endif
#if defined(MBEDTLS_SSL_MAX_FRAGMENT_LENGTH)
    unsigned int mfl_code : 3;      /*!< 期望碎片长度*/
#endif
#if defined(MBEDTLS_SSL_ENCRYPT_THEN_MAC)
    unsigned int encrypt_then_mac : 1 ; /*!< 协商加密然后mac？*/
#endif
#if defined(MBEDTLS_SSL_EXTENDED_MASTER_SECRET)
    unsigned int extended_ms : 1;   /*!< 协商扩展的主秘密？*/
#endif
#if defined(MBEDTLS_SSL_DTLS_ANTI_REPLAY)
    unsigned int anti_replay : 1;   /*!< 检测并防止重放？*/
#endif
#if defined(MBEDTLS_SSL_CBC_RECORD_SPLITTING)
    unsigned int cbc_record_splitting : 1;  /*!< 进行cbc记录拆分*/
#endif
#if defined(MBEDTLS_SSL_RENEGOTIATION)
    unsigned int disable_renegotiation : 1; /*!< 禁用重新协商？*/
#endif
#if defined(MBEDTLS_SSL_TRUNCATED_HMAC)
    unsigned int trunc_hmac : 1;    /*!< 协商截断的hmac？*/
#endif
#if defined(MBEDTLS_SSL_SESSION_TICKETS)
    unsigned int session_tickets : 1;   /*!< 使用会话票证？*/
#endif
#if defined(MBEDTLS_SSL_FALLBACK_SCSV) && defined(MBEDTLS_SSL_CLI_C)
    unsigned int fallback : 1;      /*!< 这是退路吗？*/
#endif
#if defined(MBEDTLS_SSL_SRV_C)
    unsigned int cert_req_ca_list : 1;  /*!< 是否启用在证书请求消息中发送CA列表？*/
#endif
#if defined(MBEDTLS_SSL_DTLS_CONNECTION_ID)
    unsigned int ignore_unexpected_cid : 1; /*!< 确定具有意外CID*的DTLS记录是否应导致失败。*/
#endif /* MBEDTLS_SSL_DTLS_CONNECTION_ID */
#if defined(MBEDTLS_SSL_DTLS_SRTP)
    unsigned int dtls_srtp_mki_support : 1; /* 支持在use_srtp扩展中使用mki_value*/
#endif
};

struct mbedtls_ssl_context
{
    const mbedtls_ssl_config *conf; /*!< 配置信息*/

    /*
     * 混杂的
     */
    int state;                  /*!< SSL握手：当前状态*/
#if defined(MBEDTLS_SSL_RENEGOTIATION)
    int renego_status;          /*!< 初始，正在进行，待定？*/
    int renego_records_seen;    /*!< 如果reteo_max_Records小于0，则记录自reteo请求以来或使用DTLS的请求重传次数*/
#endif /* MBEDTLS_SSL_RENEGOTIATION */

    int major_ver;              /*!< 等于MBEDTLS_SL_MAJOR_VERSION_3*/
    int minor_ver;              /*!< 0（SSL3）或1（TLS1.0）*/

#if defined(MBEDTLS_SSL_DTLS_BADMAC_LIMIT)
    unsigned badmac_seen;       /*!< 接收到MAC错误的记录*/
#endif /* MBEDTLS_SSL_DTLS_BADMAC_LIMIT */

#if defined(MBEDTLS_X509_CRT_PARSE_C)
    /**回调以自定义X.509证书链验证*/
    int (*f_vrfy)(void *, mbedtls_x509_crt *, int, uint32_t *);
    void *p_vrfy;                   /*!< X.509验证回调的上下文*/
#endif

    mbedtls_ssl_send_t *f_send; /*!< 网络发送的回调*/
    mbedtls_ssl_recv_t *f_recv; /*!< 网络接收的回调*/
    mbedtls_ssl_recv_timeout_t *f_recv_timeout;
                                /*!< 网络接收的回调超时*/

    void *p_bio;                /*!< I/O操作的上下文*/

    /*
     * 会话层
     */
    mbedtls_ssl_session *session_in;            /*!<  当前会话数据（in）*/
    mbedtls_ssl_session *session_out;           /*!<  当前会话数据（输出）*/
    mbedtls_ssl_session *session;               /*!<  协商会话数据*/
    mbedtls_ssl_session *session_negotiate;     /*!<  协商中的会话数据*/

    mbedtls_ssl_handshake_params *handshake;    /*!<  仅在握手过程中需要参数*/

    /*
     * 记录层转换
     */
    mbedtls_ssl_transform *transform_in;        /*!<  当前变换参数（in）*/
    mbedtls_ssl_transform *transform_out;       /*!<  当前变换参数（in）*/
    mbedtls_ssl_transform *transform;           /*!<  协商转换参数*/
    mbedtls_ssl_transform *transform_negotiate; /*!<  协商中的转换参数*/

    /*
     * 计时器
     */
    void *p_timer;              /*!< 计时器回调的上下文*/

    mbedtls_ssl_set_timer_t *f_set_timer;       /*!< 设置计时器回调*/
    mbedtls_ssl_get_timer_t *f_get_timer;       /*!< 获取计时器回调*/

    /*
     * 记录层（传入数据）
     */
    unsigned char *in_buf;      /*!< 输入缓冲器*/
    unsigned char *in_ctr;      /*!< 64位传入消息计数器TLS：由我们维护DTLS：从对等方读取*/
    unsigned char *in_hdr;      /*!< 记录头开始*/
#if defined(MBEDTLS_SSL_DTLS_CONNECTION_ID)
    unsigned char *in_cid;      /*!< CID的开始；（结尾用in_len标记）。*/
#endif /* MBEDTLS_SSL_DTLS_CONNECTION_ID */
    unsigned char *in_len;      /*!< 双字节消息长度字段*/
    unsigned char *in_iv;       /*!< ivlen字节IV*/
    unsigned char *in_msg;      /*!< 消息内容（in_iv+ivlen）*/
    unsigned char *in_offt;     /*!< 应用程序数据中的读取偏移量*/

    int in_msgtype;             /*!< 记录标题：消息类型*/
    size_t in_msglen;           /*!< 记录标题：消息长度*/
    size_t in_left;             /*!< 到目前为止读取的数据量*/
#if defined(MBEDTLS_SSL_VARIABLE_BUFFER_LENGTH)
    size_t in_buf_len;          /*!< 输入缓冲区长度*/
#endif
#if defined(MBEDTLS_SSL_PROTO_DTLS)
    uint16_t in_epoch;          /*!< 传入记录的DTLS时期*/
    size_t next_record_offset;  /*!< 数据报中下一条记录的偏移量（如果没有，则等于in_left）*/
#endif /* MBEDTLS_SSL_PROTO_DTLS */
#if defined(MBEDTLS_SSL_DTLS_ANTI_REPLAY)
    uint64_t in_window_top;     /*!< 上次验证的记录seq_num*/
    uint64_t in_window;         /*!< 重放检测的位掩码*/
#endif /* MBEDTLS_SSL_DTLS_ANTI_REPLAY */

    size_t in_hslen;            /*!< 当前握手消息长度，包括握手标头*/
    int nb_zero;                /*!< # 长度为0的加密邮件*/

    int keep_current_message;   /*!< 在下一次调用记录层时丢弃或重用当前消息？*/

#if defined(MBEDTLS_SSL_PROTO_DTLS)
    uint8_t disable_datagram_packing;  /*!< 禁用在单个数据报中打包多个记录*。*/
#endif /* MBEDTLS_SSL_PROTO_DTLS */

    /*
     * 记录层（传出数据）
     */
    unsigned char *out_buf;     /*!< 输出缓冲器*/
    unsigned char *out_ctr;     /*!< 64位传出消息计数器*/
    unsigned char *out_hdr;     /*!< 记录头开始*/
#if defined(MBEDTLS_SSL_DTLS_CONNECTION_ID)
    unsigned char *out_cid;     /*!< CID的开始；（结尾用in_len标记）。*/
#endif /* MBEDTLS_SSL_DTLS_CONNECTION_ID */
    unsigned char *out_len;     /*!< 双字节消息长度字段*/
    unsigned char *out_iv;      /*!< ivlen字节IV*/
    unsigned char *out_msg;     /*!< 消息内容（out_iv+ivlen）*/

    int out_msgtype;            /*!< 记录标题：消息类型*/
    size_t out_msglen;          /*!< 记录标题：消息长度*/
    size_t out_left;            /*!< 尚未写入的数据量*/
#if defined(MBEDTLS_SSL_VARIABLE_BUFFER_LENGTH)
    size_t out_buf_len;         /*!< 输出缓冲区长度*/
#endif

    unsigned char cur_out_ctr[8]; /*!<  传出记录序列号。*/

#if defined(MBEDTLS_SSL_PROTO_DTLS)
    uint16_t mtu;               /*!< 路径mtu，用于分割传出消息*/
#endif /* MBEDTLS_SSL_PROTO_DTLS */

#if defined(MBEDTLS_ZLIB_SUPPORT)
    unsigned char *compress_buf;        /*!<  zlib数据缓冲区*/
#endif /* MBEDTLS_ZLIB_SUPPORT */
#if defined(MBEDTLS_SSL_CBC_RECORD_SPLITTING)
    signed char split_done;     /*!< 当前记录已拆分？*/
#endif /* MBEDTLS_SSL_CBC_RECORD_SPLITTING */

    /*
     * PKI层
     */
    int client_auth;                    /*!<  客户端身份验证标志。*/

    /*
     * 用户设置
     */
#if defined(MBEDTLS_X509_CRT_PARSE_C)
    char *hostname;             /*!< 用于验证的预期对等CN（以及SNI，如果可用）*/
#endif /* MBEDTLS_X509_CRT_PARSE_C */

#if defined(MBEDTLS_SSL_ALPN)
    const char *alpn_chosen;    /*!<  协商协议*/
#endif /* MBEDTLS_SSL_ALPN */

#if defined(MBEDTLS_SSL_DTLS_SRTP)
    /*
     * use_srtp扩展
     */
    mbedtls_dtls_srtp_info dtls_srtp_info;
#endif /* MBEDTLS_SSL_DTLS_SRTP */

    /*
     * DTLS hello验证信息
     */
#if defined(MBEDTLS_SSL_DTLS_HELLO_VERIFY) && defined(MBEDTLS_SSL_SRV_C)
    unsigned char  *cli_id;         /*!<  客户端的传输级别ID*/
    size_t          cli_id_len;     /*!<  cli_id的长度*/
#endif /* MBEDTLS_SSL_DTLS_HELLO_VERIFY && MBEDTLS_SSL_SRV_C */

    /*
     * 安全的重新协商
     */
    /* 需要知道何时在服务器上发送扩展*/
    int secure_renegotiation;           /*!<  同行是否支持传统或安全的重新协商*/
#if defined(MBEDTLS_SSL_RENEGOTIATION)
    size_t verify_data_len;             /*!<  存储的验证数据长度*/
    char own_verify_data[MBEDTLS_SSL_VERIFY_DATA_MAX_LEN]; /*!<  前一次握手验证数据*/
    char peer_verify_data[MBEDTLS_SSL_VERIFY_DATA_MAX_LEN]; /*!<  前一次握手验证数据*/
#endif /* MBEDTLS_SSL_RENEGOTIATION */

#if defined(MBEDTLS_SSL_DTLS_CONNECTION_ID)
    /* 要在后续握手中使用的CID配置。*/

    /*! 由用户选择并应用于所有后续握手的下一个传入CID。如果用户在初始握手之后重新配置了CID，则这可能与当前使用的CID不同。*/
    unsigned char own_cid[ MBEDTLS_SSL_CID_IN_LEN_MAX ];
    uint8_t own_cid_len;   /*!< \cown_cid的长度。*/
    uint8_t negotiate_cid; /*!< 这指示是否应在下一次握手中协商CID扩展。可能的值为#MBEDTLS_SL_CID_ENABLED和#MBEDLLS_SL_CID _DISABLED。*/
#endif /* MBEDTLS_SSL_DTLS_CONNECTION_ID */
};

#if defined(MBEDTLS_SSL_HW_RECORD_ACCEL)

#if !defined(MBEDTLS_DEPRECATED_REMOVED)

#define MBEDTLS_SSL_CHANNEL_OUTBOUND   MBEDTLS_DEPRECATED_NUMERIC_CONSTANT( 0 )
#define MBEDTLS_SSL_CHANNEL_INBOUND    MBEDTLS_DEPRECATED_NUMERIC_CONSTANT( 1 )

#if defined(MBEDTLS_DEPRECATED_WARNING)
#define MBEDTLS_DEPRECATED      __attribute__((deprecated))
#else
#define MBEDTLS_DEPRECATED
#endif /* MBEDTLS_DEPRECATED_WARNING */

MBEDTLS_DEPRECATED extern int (*mbedtls_ssl_hw_record_init)(
                    mbedtls_ssl_context *ssl,
                    const unsigned char *key_enc, const unsigned char *key_dec,
                    size_t keylen,
                    const unsigned char *iv_enc,  const unsigned char *iv_dec,
                    size_t ivlen,
                    const unsigned char *mac_enc, const unsigned char *mac_dec,
                    size_t maclen);
MBEDTLS_DEPRECATED extern int (*mbedtls_ssl_hw_record_activate)(
                                                    mbedtls_ssl_context *ssl,
                                                    int direction );
MBEDTLS_DEPRECATED extern int (*mbedtls_ssl_hw_record_reset)(
                                                    mbedtls_ssl_context *ssl );
MBEDTLS_DEPRECATED extern int (*mbedtls_ssl_hw_record_write)(
                                                    mbedtls_ssl_context *ssl );
MBEDTLS_DEPRECATED extern int (*mbedtls_ssl_hw_record_read)(
                                                    mbedtls_ssl_context *ssl );
MBEDTLS_DEPRECATED extern int (*mbedtls_ssl_hw_record_finish)(
                                                    mbedtls_ssl_context *ssl );

#undef MBEDTLS_DEPRECATED
#endif /* !MBEDTLS_DEPRECATED_REMOVED */

#endif /* MBEDTLS_SSL_HW_RECORD_ACCEL */

/**
 * \brief返回与给定ID关联的密码套件的名称
 *
 * \param ciphersuite_id SSL密码套件id
 *
 * \返回包含密码套件名称的字符串
 */
const char *mbedtls_ssl_get_ciphersuite_name( const int ciphersuite_id );

/**
 * \brief返回与给定名称关联的密码套件的ID
 *
 * \param ciphersuite_name SSL密码套件名称
 *
 * \返回带有密码套件的ID，如果找不到则返回0
 */
int mbedtls_ssl_get_ciphersuite_id( const char *ciphersuite_name );

/**
 * \brief初始化SSL上下文仅使上下文为mbedtls_SSL_setup（）或mbedtls_SSL_free（）做好准备
 *
 * \param ssl ssl上下文
 */
void mbedtls_ssl_init( mbedtls_ssl_context *ssl );

/**
 * \brief设置要使用的SSL上下文
 *
 * \注意：没有创建配置上下文的副本，它可以由许多mbedtls_ssl_context结构共享。
 *
 * \warning会话期间将访问conf结构。只要会话处于活动状态，就不能修改或释放它。
 *
 * \警告此函数必须在每个上下文中调用一次。即使没有活动会话，也不支持再次调用mbedtls_ssl_setup。
 *
 * \param ssl ssl上下文\param conf要使用的ssl配置
 *
 * \如果成功，则返回0；如果内存分配失败，则返回MBEDTLS_ERROR_SSL_ALLOC_FAILED
 */
int mbedtls_ssl_setup( mbedtls_ssl_context *ssl,
                       const mbedtls_ssl_config *conf );

/**
 * \brief重置已初始化的SSL上下文以供重用，同时保留应用程序集变量、函数指针和数据。
 *
 * \param ssl ssl上下文\如果成功，则返回0，或者MBEDTLS_ERROR_ssl_ALLOC_FAILED、MBEDTLS_ERROR_ssl_HW_ACCEL_FAILED或MBEDTL_ERR_ssl_COMPRESSION_FAILED
 */
int mbedtls_ssl_session_reset( mbedtls_ssl_context *ssl );

/**
 * \brief设置当前端点类型
 *
 * \param conf SSL配置\param端点必须是MBEDTLS_SL_IS_CLIENT或MBEDTLS_SL_IS_SERVER
 */
void mbedtls_ssl_conf_endpoint( mbedtls_ssl_config *conf, int endpoint );

/**
 * \brief设置传输类型（TLS或DTLS）。默认值：TLS
 *
 * \注意：对于DTLS，必须提供一个不阻塞的recv回调，或一个处理超时的回调，请参阅\c mbedtls_ssl_set_bio（）。您还需要使用\c mbedtls_ssl_set_timer_cb（）提供计时器回调。
 *
 * \param conf SSL配置\param传输传输类型：用于TLS的MBEDTLS_SL_transport_STREAM，用于DTLS的MBEDTLS _SSL_TRANPORT_DATAGRAM。
 */
void mbedtls_ssl_conf_transport( mbedtls_ssl_config *conf, int transport );

/**
 * \brief设置证书验证模式默认值：服务器上为NONE，客户端上为REQUIRED
 *
 * \param conf SSL配置\param authmode可以是：
 *
 *  MBEDTLS_SL_VERIFY_NONE：未检查对等证书（服务器上的默认值）（客户端上不安全）
 *
 *  MBEDTLS_SL_VERIFY_OPTIONAL：已检查对等证书，但即使验证失败，握手仍将继续；可以在握手完成后调用mbedtls_ssl_get_verify_result（）。
 *
 *  MBEDTLS_SL_VERIFY_REQUIRED：对等方*必须*提供有效证书，如果验证失败，握手将中止。（客户端默认）
 *
 * \注意：在客户端上，建议使用MBEDTLS_SL_VERIFY_REQUIRED模式。使用MBEDTLS_SL_VERIFY_OPTIONAL，用户需要在正确的时间调用MBEDTLS_SSL_get_VERIFY_result（），这可能并不明显，而REQUIRED总是尽快执行验证。例如，在发现“三次握手”攻击之前，REQUIRED就在保护它。
 */
void mbedtls_ssl_conf_authmode( mbedtls_ssl_config *conf, int authmode );

#if defined(MBEDTLS_X509_CRT_PARSE_C)
/**
 * \brief设置验证回调（可选）。
 *
 *                 如果设置，则为对等方的CRT链中的每个证书（包括受信任的根）调用提供的验证回调。有关详细信息，请参阅\c mbedtls_x509_crt_verify（）的文档。
 *
 * \注意：对于每上下文回调和上下文，请改用mbedtls_ssl_set_verify（）。
 *
 * \param conf要使用的SSL配置。\param f_vrfy在CRT验证期间使用的验证回调。\param p_vrfy要传递给回调的不透明上下文。
 */
void mbedtls_ssl_conf_verify( mbedtls_ssl_config *conf,
                     int (*f_vrfy)(void *, mbedtls_x509_crt *, int, uint32_t *),
                     void *p_vrfy );
#endif /* MBEDTLS_X509_CRT_PARSE_C */

/**
 * \brief设置随机数生成器回调
 *
 * \param conf SSL配置\param f_rng rng函数\param p_rng rng参数
 */
void mbedtls_ssl_conf_rng( mbedtls_ssl_config *conf,
                  int (*f_rng)(void *, unsigned char *, size_t),
                  void *p_rng );

/**
 * \brief设置调试回调
 *
 *                 回调具有以下参数：回调的void不透明上下文int调试级别const char文件名int行号const char消息
 *
 * \param conf SSL配置\param f_dbg调试函数\param p_dbg调试参数
 */
void mbedtls_ssl_conf_dbg( mbedtls_ssl_config *conf,
                  void (*f_dbg)(void *, int, const char *, int, const char *),
                  void  *p_dbg );

/**
 * \brief设置写、读和读的基本BIO回调，并超时。
 *
 * \param ssl ssl上下文\param p_bio参数（上下文）由bio回调共享\param f_send write callback \pparam f_recv read callback/param f_recv_timeout阻止超时的读回调。
 *
 * \注意f_recv或f_recv_timeout中的一个可以为NULL，在这种情况下使用另一个。如果两者都为非NULL，则使用f_recv_timeout，并忽略f_recv（如同为NULL一样）。
 *
 * \注意：两个最常见的用例是：
 *                 -非阻塞I/O，f_recv！=NULL，f_recv_timeout==NULL
 *                 -阻塞I/O，f_recv==NULL，f_rev_timeout！=无效的
 *
 * \注意：对于DTLS，您需要提供一个非NULL的f_recv_timeout回调或一个不阻塞的f_rev。
 *
 * \注意：有关回调必须遵循的约定，请参见\c mbedtls_ssl_send_t、\c mbedt ls_ssl_recv_t和\c mbeds ls_ssl-recv_timeout_t的文档。
 *
 * \注意：在某些平台上，net_sockets。c提供了适用于此处的\c mbedtls_net_send（）、\c mbedt ls_net_recv（）和\c mbeds ls_net-recv_timeout（）。
 */
void mbedtls_ssl_set_bio( mbedtls_ssl_context *ssl,
                          void *p_bio,
                          mbedtls_ssl_send_t *f_send,
                          mbedtls_ssl_recv_t *f_recv,
                          mbedtls_ssl_recv_timeout_t *f_recv_timeout );

#if defined(MBEDTLS_SSL_PROTO_DTLS)

#if defined(MBEDTLS_SSL_DTLS_CONNECTION_ID)


/**
 * \brief在下次握手中配置连接ID（CID）扩展的使用。
 *
 *                    参考：draft-ietf-tls-dtls-connection-id-05https://tools.ietf.org/html/draft-ietf-tls-dtls-connection-id-05
 *
 *                    DTLS CID扩展允许通过将显式连接标识符（CID）添加到加密的DTLS记录的头中，将DTLS记录与DTLS连接可靠地关联，以跨越基础传输中的变化（更改的IP和端口元数据）。所需的CID由应用层配置，并在握手期间以新的“ClientHello”/“ServerHello”扩展名进行交换，其中每一方都指示其希望对等方在写入加密消息时使用的CID。一旦记录被加密，CID就会被使用：堆栈丢弃任何传入的记录，这些记录的报头中不包含配置的CID，并将对等方请求的CID添加到传出消息的报头中。
 *
 *                    此API启用或禁用下次握手中CID扩展的使用，并设置用于传入消息的CID值。
 *
 * \param ssl要配置的ssl上下文。必须对其进行初始化。\param enable此值确定是否应使用CID扩展名。可能的值包括：
 *                    -MBEDTLS_SL_CID_ENABLED以启用CID的使用。
 *                    -MBEDTLS_SL_CID_DISABLED（默认）以禁用CID的使用。\param own_cid保存我们希望对等方在向我们发送加密消息时使用的cid的可读缓冲区的地址。如果own_cid_len为0，则该值可能为空。如果enabled设置为MBEDTLS_SL_cid_DISABLED，则该参数不使用。\param own_cid_len \p own_cid的长度。如果enabled设置为MBEDTLS_SL_CID_DISABLED，则此参数未使用。
 *
 * \注意：在配置ssl绑定到的：：mbedtls_ssl_config时，\pown_cid_len的值必须与传递给mbedtls_ssl_conf_cid（）的len参数的值匹配。
 *
 * \注意：此CID配置适用于在SSL上下文\p SSL上执行的后续握手，但不会触发握手。在成功调用此函数后，仍然必须显式调用“mbedtls_ssl_handshake（）”（用于初始握手）或“mbedtls _ssl_regotiate（）”，以运行握手。
 *
 * \注意：此调用不能保证在下次握手中成功协商CID的使用，因为对等方可能不支持它。明确地：
 *                    -在客户端上，通过此调用启用CID意味着下一次握手中的“ClientHello”将包括CID扩展，从而向服务器提供CID的使用。只有当“ServerHello”也包含CID扩展名时，CID扩展名才会实际使用。
 *                    -在服务器上，通过此调用启用CID意味着服务器将在客户端的“ClientHello”中查找CID扩展名，如果存在，则在其“ServerHello”中将CID扩展名回复。
 *
 * \注意：要检查CID的使用是否在后续握手完成后协商，请使用API mbedtls_ssl_get_peer_CID（）。
 *
 * \警告如果在此呼叫中启用了CID扩展名的使用，并且随后的握手协商其使用，则Mbed TLS将默默丢弃CID与own_CID中配置的CID不匹配的每个数据包。用户有责任在将数据报传递给Mbed TLS之前调整底层传输以处理基于CID的多路分解。
 *
 * \成功时返回\c 0。在这种情况下，CID配置适用于下一次握手。\失败时返回负错误代码。
 */
int mbedtls_ssl_set_cid( mbedtls_ssl_context *ssl,
                         int enable,
                         unsigned char const *own_cid,
                         size_t own_cid_len );

/**
 * \brief获取有关在当前连接中使用CID扩展的信息。
 *
 * \param ssl要查询的ssl上下文。\param enabled存储CID扩展是否当前正在使用的地址。如果CID正在使用，则“enabled”设置为MBEDTLS_SL_CID_enabled；否则设置为MBEDTLS_SL_CID_DISABLED。\param peer_cid存储对等方选择的cid的缓冲区地址（如果使用了cid扩展名）。如果不需要对等CID的值，则该值可能为空。如果它不是\c NULL，则\p peer_cid_len不能是\c NULL。\param peer_cid_len存储对等方选择的cid大小的地址（如果使用了cid扩展名）。这也是已写入的\p peer_cid中的字节数。如果不需要对等CID的长度，则该值可能为空。如果它是\c NULL，则\p peer_cid也必须是\c空。
 *
 * \注意：这适用于上次完整握手中协商的CID的状态。如果正在进行握手，此函数将尝试先完成握手。
 *
 * \注意：如果已经交换了CID扩展，但客户端和服务器都选择使用空CID，则此函数将“enabled”设置为#MBEDTLS_SL_CID_DISABLED（这样做的理由是，如果没有使用CID扩展，则产生的通信相同）。
 *
 * \成功时返回\c 0。\失败时返回负错误代码。
 */
int mbedtls_ssl_get_peer_cid( mbedtls_ssl_context *ssl,
                     int *enabled,
                     unsigned char peer_cid[ MBEDTLS_SSL_CID_OUT_LEN_MAX ],
                     size_t *peer_cid_len );

#endif /* MBEDTLS_SSL_DTLS_CONNECTION_ID */

/**
 * \brief设置最大传输单位（MTU）。特殊值：0表示未设置（无限制）。这表示由网络链路和堆栈确定的传输层（通常是UDP）处理的数据报有效载荷的最大大小。实际上，这控制DTLS层使用\c mbedtls_ssl_set_bio（）传递给\c f_send（）回调集的最大数据报大小。
 *
 * \注意：通过减去封装和加密/认证（如果有）的当前开销，数据报大小的限制被转换为记录有效负载的限制。
 *
 * \注意：这可以在连接期间的任何时间点调用，例如，当路径最大传输单元（PMTU）估计值从其他源（例如较低（或较高）协议层）变得可用时。
 *
 * \注意：此设置仅控制我们发送的数据包的大小，而不限制我们愿意接收的数据报的大小。客户端，您可以请求服务器在\c mbedtls_ssl_conf_max_frag_len（）中使用较小的记录。
 *
 * \注意：如果MTU和最大片段长度都已配置（或与对等方协商），则使用记录有效载荷的结果下限（参见第一个注释）。
 *
 * \注意：这只能用于减少发送的数据报（因此记录，请参见第一个注释）的最大大小。它不能用于将记录的最大大小增加到#MBEDTLS_SL_OUT_CONTENT_LEN设置的限制之上。
 *
 * \注意：低于当前记录层扩展的值将在尝试发送数据时导致错误。
 *
 * \注意：在尝试发送数据时，将记录压缩与非零MTU值一起使用将导致错误。
 *
 * \param ssl ssl上下文\param mtu路径mtu的值（字节）
 */
void mbedtls_ssl_set_mtu( mbedtls_ssl_context *ssl, uint16_t mtu );
#endif /* MBEDTLS_SSL_PROTO_DTLS */

#if defined(MBEDTLS_X509_CRT_PARSE_C)
/**
 * \brief设置特定于连接的验证回调（可选）。
 *
 *                 如果设置，则为对等方的CRT链中的每个证书（包括受信任的根）调用提供的验证回调。有关详细信息，请参阅\c mbedtls_x509_crt_verify（）的文档。
 *
 * \注意：此调用类似于mbedtls_ssl_conf_verify（），但将验证回调和上下文绑定到ssl上下文，而不是ssl配置。如果同时使用了mbedtls_ssl_conf_verify（）和mbedtls_ssl_set_verify（），则mbedtls-ssl_set_valid（）优先。
 *
 * \param ssl要使用的ssl上下文。\param f_vrfy在CRT验证期间使用的验证回调。\param p_vrfy要传递给回调的不透明上下文。
 */
void mbedtls_ssl_set_verify( mbedtls_ssl_context *ssl,
                     int (*f_vrfy)(void *, mbedtls_x509_crt *, int, uint32_t *),
                     void *p_vrfy );
#endif /* MBEDTLS_X509_CRT_PARSE_C */

/**
 * \brief设置mbedtls_ssl_read（）的超时时间（默认值：无超时。）
 *
 * \param conf SSL配置上下文\param timeout超时值（毫秒）。使用0表示无超时（默认值）。
 *
 * \注意：对于阻塞I/O，只有在使用\c mbedtls_ssl_set_bio（）设置了非NULL \cf_recv_timeout时，这才有效。对于非阻塞I/O，只有在使用\c mbedtls_ssl_set_timer_cb（）设置了计时器回调时，这才有效。
 *
 * \注意：对于非阻塞I/O，您也可以完全跳过此函数，并在应用程序层处理超时。
 */
void mbedtls_ssl_conf_read_timeout( mbedtls_ssl_config *conf, uint32_t timeout );

#if defined(MBEDTLS_SSL_RECORD_CHECKING)
/**
 * \brief检查缓冲区是否包含以前从未见过的有效且真实的记录。（仅限DTLS）。
 *
 *                 此函数不会更改SSL上下文的用户可见状态。它的唯一目的是提供传入记录合法性的指示。
 *
 *                 例如，在使用DTLS连接ID功能的分布式服务器环境中，这可能很有用，在这种环境中，可能需要在更改对等地址时在服务实例之间传递连接，但只有在确认了传入记录的有效性之后，才会发生此类中断操作。
 *
 * \param ssl要使用的ssl上下文。\param buf保存要检查的记录的缓冲区的地址。这必须是长度为\p buflen Bytes的读/写缓冲区。\param buflen \p buf的长度（以字节为单位）。
 *
 * \注意：此例程仅检查所提供的缓冲区是否以以前从未见过的有效且真实的记录开始，但不检查初始记录之后的潜在数据。特别是，可以传递包含多个记录的DTLS数据报，在这种情况下，只检查第一个记录。
 *
 * \注意：此函数修改输入缓冲区。如果你需要保留原始记录，你必须保留一份副本。
 *
 * \如果记录有效且真实，并且以前从未见过，则返回\c 0。\如果检查成功完成，但发现记录不真实，则返回MBEDTLS_ERROR_SSL_INVALID_MAC。\如果检查成功完成，但发现记录因与真实性检查不同的原因无效，则返回MBEDTLS_ERROR_SSL_INVALID_RECORD。\如果检查成功完成，但发现记录在SSL上下文的状态下是意外的，包括重放的记录，则返回MBEDTLS_ERROR_SSL_UNEXPECTED_RECORD。\返回不同类型失败的另一个负错误代码。在这种情况下，SSL上下文变得不可用，需要在重用之前释放或重置。
 */
int mbedtls_ssl_check_record( mbedtls_ssl_context const *ssl,
                              unsigned char *buf,
                              size_t buflen );
#endif /* MBEDTLS_SSL_RECORD_CHECKING */

/**
 * \brief设置计时器回调（DTLS强制）
 *
 * \param ssl ssl上下文\param p_timer参数（上下文）由计时器回调共享\param f_set_timer设置计时器回调\param f _get_timer获取计时器回调。必须返回：
 *
 * \注意：有关这对回调必须遵循的约定，请参阅\c mbedtls_ssl_set_timer_t和\c mbedt ls_ssl_get_timer_t的文档。
 *
 * \注意：在某些平台上，计时。c提供了适用于此处的\c mbedtls_timing_set_lay（）和\c mbedls_timing_get_delay（），除非使用事件驱动样式。
 *
 * \注意：另请参阅我们知识库中的“DTLS教程”文章。https://tls.mbed.org/kb/how-to/dtls-tutorial
 */
void mbedtls_ssl_set_timer_cb( mbedtls_ssl_context *ssl,
                               void *p_timer,
                               mbedtls_ssl_set_timer_t *f_set_timer,
                               mbedtls_ssl_get_timer_t *f_get_timer );

/**
 * \简短回调类型：生成和写入会话票证
 *
 * \注意：这描述了回调实现应该做什么。这个回调应该为会话生成一个经过加密和验证的票证，并将其写入输出缓冲区。这里，ticket是指RFC 5077的NewSessionTicket结构中不透明的ticket部分。
 *
 * \param p_ticket要写入票证中的回调会话SSL会话的上下文\param start输出缓冲区的开始\param end输出缓冲区结束\param tlen退出时，保存写入的长度\param lifetime退出时，以秒为单位保存票证的生存期
 *
 * \如果成功则返回0，或者返回特定的MBEDTLS_ERROR_XXX代码。
 */
typedef int mbedtls_ssl_ticket_write_t( void *p_ticket,
                                        const mbedtls_ssl_session *session,
                                        unsigned char *start,
                                        const unsigned char *end,
                                        size_t *tlen,
                                        uint32_t *lifetime );

#if defined(MBEDTLS_SSL_EXPORT_KEYS)
/**
 * \简短回调类型：导出密钥块和主密钥
 *
 * \注意这是TLS的某些用途所必需的，例如EAP-TLS（RFC 5216）和线程。键指针是短暂的，因此不能存储。除了作为密钥派生函数的输入之外，主密钥和密钥不应直接使用。
 *
 * \param p_expkey回调上下文\param ms指向主密钥的指针（固定长度：48字节）\param kb指向密钥块的指针，请参阅RFC 5246第6.3节（可变长度：2 maclen+2 keylen+2 ivlen）。\param maclen MAC长度/param keylen密钥长度/param ivlen IV长度
 *
 * \如果成功则返回0，或者返回特定的MBEDTLS_ERROR_XXX代码。
 */
typedef int mbedtls_ssl_export_keys_t( void *p_expkey,
                                const unsigned char *ms,
                                const unsigned char *kb,
                                size_t maclen,
                                size_t keylen,
                                size_t ivlen );

/**
 * \简短回调类型：导出密钥块、主密钥、握手randbyte和用于导出密钥的tls_prf函数。
 *
 * \注意这是TLS的某些用途所必需的，例如EAP-TLS（RFC 5216）和线程。键指针是短暂的，因此不能存储。除了作为密钥派生函数的输入之外，主密钥和密钥不应直接使用。
 *
 * \param p_expkey回调的上下文。\param ms指向主密钥的指针（固定长度：48字节）。\param kb指向密钥块的指针，请参阅RFC 5246第6.3节。（可变长度：2 maclen+2 keylen+2 ivlen）。\param maclen MAC长度。\param keylen密钥长度。\param ivlen IV长度。\param client_random客户端随机字节。\param server_random服务器随机字节。\param tls_prf_type tls_prf枚举类型。
 *
 * \如果成功则返回0，或者返回特定的MBEDTLS_ERROR_XXX代码。
 */
typedef int mbedtls_ssl_export_keys_ext_t( void *p_expkey,
                                           const unsigned char *ms,
                                           const unsigned char *kb,
                                           size_t maclen,
                                           size_t keylen,
                                           size_t ivlen,
                                           const unsigned char client_random[32],
                                           const unsigned char server_random[32],
                                           mbedtls_tls_prf_types tls_prf_type );
#endif /* MBEDTLS_SSL_EXPORT_KEYS */

/**
 * \简短回调类型：解析并加载会话票证
 *
 * \注意：这描述了回调实现应该做什么。此回调应解析由相应的mbedtls_ssl_ticket_write_t函数生成的会话票证，如果票证真实有效，则加载会话。
 *
 * \注意：该实现允许修改输入缓冲区的第一个len字节，例如将其用作解密票据内容的临时区域。
 *
 * \param p_ticket要加载的回调会话SSL会话的上下文\param buf包含票证的缓冲区的开始\param len票证的长度。
 *
 * \如果成功，则返回0；如果不可信，则返回MBEDTLS_ERROR_SSL_INVALIDMACH；如果过期，则返回EMBEDTLS_ERR_SSL_SESSION_TICKET_EXPIRED；如果其他失败，则返回任何其他非零代码。
 */
typedef int mbedtls_ssl_ticket_parse_t( void *p_ticket,
                                        mbedtls_ssl_session *session,
                                        unsigned char *buf,
                                        size_t len );

#if defined(MBEDTLS_SSL_SESSION_TICKETS) && defined(MBEDTLS_SSL_SRV_C)
/**
 * \brief配置SSL会话票证回调（仅限服务器）。（默认值：无。）
 *
 * \注意：在服务器上，通过提供非NULL回调来启用会话票证。
 *
 * \注意：在客户端上，使用\c mbedtls_ssl_conf_session_tickts（）。
 *
 * \param conf SSL配置上下文\param f_tickt_write用于写入票证的回调\param f _tickt_parse用于解析票证的回调\param p_ticket两个回调共享的上下文
 */
void mbedtls_ssl_conf_session_tickets_cb( mbedtls_ssl_config *conf,
        mbedtls_ssl_ticket_write_t *f_ticket_write,
        mbedtls_ssl_ticket_parse_t *f_ticket_parse,
        void *p_ticket );
#endif /* MBEDTLS_SSL_SESSION_TICKETS && MBEDTLS_SSL_SRV_C */

#if defined(MBEDTLS_SSL_EXPORT_KEYS)
/**
 * \brief配置密钥导出回调。（默认值：无。）
 *
 * \注意：请参见\c mbedtls_ssl_export_keys_t。
 *
 * \param conf SSL配置上下文\param f_export_keys用于导出密钥的回调\param p_export_keys回调的上下文
 */
void mbedtls_ssl_conf_export_keys_cb( mbedtls_ssl_config *conf,
        mbedtls_ssl_export_keys_t *f_export_keys,
        void *p_export_keys );

/**
 * \brief配置扩展密钥导出回调。（默认值：无。）
 *
 * \注意：请参见\c mbedtls_ssl_export_keys_ext_t。\警告：在完成（D）TLS握手之前，导出的密钥材料不得用于任何目的
 *
 * \param conf SSL配置上下文\param f_export_keys_ext用于导出密钥的回调\param p_export_keys用于回调的上下文
 */
void mbedtls_ssl_conf_export_keys_ext_cb( mbedtls_ssl_config *conf,
        mbedtls_ssl_export_keys_ext_t *f_export_keys_ext,
        void *p_export_keys );
#endif /* MBEDTLS_SSL_EXPORT_KEYS */

#if defined(MBEDTLS_SSL_ASYNC_PRIVATE)
/**
 * \brief配置异步私钥操作回调。
 *
 * \param conf SSL配置上下文\param f_async_sign回调以启动签名操作。有关详细信息，请参见：：mbedtls_ssl_async_sign_t的描述。如果外部处理器不支持任何签名操作，则可能为空；在这种情况下，将使用与证书相关联的私钥对象。\param f_async_decrypt回调以开始解密操作。有关详细信息，请参见：：mbedtls_ssl_async_decrypt_t的描述。如果外部处理器不支持任何解密操作，则可能为空；在这种情况下，将使用与证书相关联的私钥对象。\param f_async_resume回调以恢复异步操作。有关详细信息，请参阅：：mbedtls_ssl_async_resume_t的描述。除非\p f_async_sign和\p f_sync_decrypt都为空，否则不能为空。\param f_async_cancel回调以取消异步操作。有关详细信息，请参阅：：mbedtls_ssl_async_cancel_t的说明。如果不需要清理，则该值可能为空。\param config_data指向可以使用mbedtls_ssl_conf_get_async_config_data（）检索的配置数据的指针。库存储此值而不取消引用它。
 */
void mbedtls_ssl_conf_async_private_cb( mbedtls_ssl_config *conf,
                                        mbedtls_ssl_async_sign_t *f_async_sign,
                                        mbedtls_ssl_async_decrypt_t *f_async_decrypt,
                                        mbedtls_ssl_async_resume_t *f_async_resume,
                                        mbedtls_ssl_async_cancel_t *f_async_cancel,
                                        void *config_data );

/**
 * \brief检索由mbedtls_ssl_conf_async_private_cb（）设置的配置数据。
 *
 * \param conf SSL配置上下文\return mbedtls_SSL_conf_async_private_cb（）设置的配置数据。
 */
void *mbedtls_ssl_conf_get_async_config_data( const mbedtls_ssl_config *conf );

/**
 * \brief检索异步操作用户上下文。
 *
 * \注意：此函数只能在握手过程中调用。
 *
 * \param ssl要访问的ssl上下文。
 *
 * \return上次在当前握手期间设置的异步操作用户上下文。如果在当前握手期间尚未调用mbedtls_ssl_set_async_operation_data（），则此函数返回\c NULL。
 */
void *mbedtls_ssl_get_async_operation_data( const mbedtls_ssl_context *ssl );

/**
 * \brief检索异步操作用户上下文。
 *
 * \注意：此函数只能在握手过程中调用。
 *
 * \param ssl要访问的ssl上下文。\param ctx异步操作用户上下文的新值。稍后在同一次握手期间调用mbedtls_ssl_get_async_operation_data（）以检索此值。
 */
void mbedtls_ssl_set_async_operation_data( mbedtls_ssl_context *ssl,
                                 void *ctx );
#endif /* MBEDTLS_SSL_ASYNC_PRIVATE */

/**
 * \简短回调类型：生成cookie
 *
 * \param ctx要写入的回调的上下文\param p缓冲区，必须更新为正好指向cookie之后\param end指向输出缓冲区末尾的指针\param info传递到\c mbedtls_ssl_set_Client_transport_ID（）的客户端ID信息\param ilen信息长度（字节）
 *
 * \return成功时回调必须返回0，或返回负错误代码。
 */
typedef int mbedtls_ssl_cookie_write_t( void *ctx,
                                unsigned char **p, unsigned char *end,
                                const unsigned char *info, size_t ilen );

/**
 * \简短回调类型：验证cookie
 *
 * \param ctx回调的上下文\param要验证的cookie cookie \param clen cookie的长度\param info传递到\c mbedtls_ssl_set_Client_transport_ID（）的客户端ID信息\param ilen信息的长度（字节）
 *
 * \return如果cookie有效，则回调必须返回0，或者返回负错误代码。
 */
typedef int mbedtls_ssl_cookie_check_t( void *ctx,
                                const unsigned char *cookie, size_t clen,
                                const unsigned char *info, size_t ilen );

#if defined(MBEDTLS_SSL_DTLS_HELLO_VERIFY) && defined(MBEDTLS_SSL_SRV_C)
/**
 * \注册DTLS cookie的简短回调（仅限服务器。仅限DTLS。）
 *
 *                  默认值：失败的伪回调，以强制您注册工作回调（并初始化其上下文）。
 *
 *                  要禁用HelloVerifyRequest，请注册NULL回调。
 *
 * \警告禁用hello验证允许您的服务器在针对其他主机的DoS攻击中被放大。仅当您知道这在您的特定环境中不可能发生时禁用。
 *
 * \注意：请参阅有关处理mbedtls_ERROR_ssl_HELLO_VERIFY_REQUIRED（启用时第一次握手尝试时预期的）的注释。
 *
 * \注意：这对于处理来自RFC 6347第4.2.8节中描述的相同端口的客户端重新连接也是必要的（当前仅支持带有cookie的变体）。有关详细信息，请参见\c mbedtls_ssl_read（）上的注释。
 *
 * \param conf SSL配置\param f_cookie_write cookie写入回调\param f _cookie_check cookie检查回调\pparam p_cookie两个回调的上下文
 */
void mbedtls_ssl_conf_dtls_cookies( mbedtls_ssl_config *conf,
                           mbedtls_ssl_cookie_write_t *f_cookie_write,
                           mbedtls_ssl_cookie_check_t *f_cookie_check,
                           void *p_cookie );

/**
 * \brief设置客户端的传输级别标识信息。（仅限服务器。仅限DTLS。）
 *
 *                 这通常是IP地址（和端口），但可以是根据底层网络堆栈识别客户端的任何内容。用于具有DTLS的HelloVerifyRequest。这不用于路由实际的数据包。
 *
 * \param ssl ssl上下文\param info标识客户端的传输级别信息（例如IP+端口）\param ilen信息长度（字节）
 *
 * \注意：创建了一个内部副本，因此可以重用信息缓冲区。
 *
 * \如果在客户端上使用，则返回0；如果内存不足，则返回MBEDTLS_ERROR_SSL_BAD_INPUT_DATA。
 */
int mbedtls_ssl_set_client_transport_id( mbedtls_ssl_context *ssl,
                                 const unsigned char *info,
                                 size_t ilen );

#endif /* MBEDTLS_SSL_DTLS_HELLO_VERIFY && MBEDTLS_SSL_SRV_C */

#if defined(MBEDTLS_SSL_DTLS_ANTI_REPLAY)
/**
 * \brief启用或禁用DTLS的防重放保护。（仅DTLS，不影响TLS。）默认值：已启用。
 *
 * \param conf SSL配置\param mode MBEDTLS_SL_ANTI_REPLAY_ENABLED或MBEDTL_SSL_ANTI_REPLAY_DISABLED。
 *
 * \警告禁用这是一种安全风险，除非应用程序协议以安全的方式处理重复的数据包。未经仔细考虑，不应禁用此功能。然而，如果您的应用程序已经检测到重复的数据包，并且需要有关这些数据包的信息来调整其传输策略，那么您需要禁用此功能。
 */
void mbedtls_ssl_conf_dtls_anti_replay( mbedtls_ssl_config *conf, char mode );
#endif /* MBEDTLS_SSL_DTLS_ANTI_REPLAY */

#if defined(MBEDTLS_SSL_DTLS_BADMAC_LIMIT)
/**
 * \brief在终止连接之前，设置具有坏MAC的记录数限制。（仅DTLS，不影响TLS。）默认值：0（已禁用）。
 *
 * \param conf SSL配置\param limit limit，或0以禁用。
 *
 * \注意：如果限制为N，则当看到第N个非真实记录时，连接终止。
 *
 * \注意：带有无效标头的记录不会被计数，只有经过身份验证解密阶段的记录才会被计数。
 *
 * \注意：这是一个与主动攻击者通常相对容易注入UDP数据报这一事实相关的安全权衡。一方面，在这里设置一个较低的限制使得攻击者更容易强行终止连接。另一方面，高限制或无限制可能会使我们浪费资源检查许多伪造数据包的身份验证。
 */
void mbedtls_ssl_conf_dtls_badmac_limit( mbedtls_ssl_config *conf, unsigned limit );
#endif /* MBEDTLS_SSL_DTLS_BADMAC_LIMIT */

#if defined(MBEDTLS_SSL_PROTO_DTLS)

/**
 * \brief允许或不允许在单个数据报中打包多个握手记录。
 *
 * \param ssl要配置的ssl上下文。\param allow_packing这决定是否可以使用数据报打包。值\c 0表示每个记录将在单独的数据报中发送；值\c 1表示，如果空间允许，属于单个航班的多个握手消息（包括CCS）可以打包在单个数据报中。
 *
 * \注意：这在默认情况下是启用的，并且只应在测试时禁用，或者如果数据报打包导致与不支持它的对等端的互操作性问题。
 *
 * \注意：允许数据报打包可以减少网络负载，因为如果多个消息共享同一个数据报，则开销更少。此外，它还提高了握手效率，因为属于单个数据报的消息在传输过程中不会被重新排序，因此未来的消息缓冲或航班重传（如果不使用缓冲）作为处理重新排序的手段不太频繁。
 *
 * \注意应用程序记录不受此选项的影响，当前总是以单独的数据报发送。
 *
 */
void mbedtls_ssl_set_datagram_packing( mbedtls_ssl_context *ssl,
                                       unsigned allow_packing );

/**
 * \brief设置DTLS握手的重传超时值。（仅DTLS，对TLS无影响。）
 *
 * \param conf SSL配置\param min初始超时值（毫秒）。默认值：1000（1秒）。\param max最大超时值（毫秒）。默认值：60000（60秒）。
 *
 * \注意默认值来自RFC 6347第4.2.4.1节。
 *
 * \注意，“min”值通常应略高于预期的对等方往返时间，加上对等方处理消息所需的时间。例如，如果您的RTT大约为600ms，而您的对等方需要最多1秒才能在握手中执行加密操作，那么您应该将“min”设置为略高于1600。“min”的值越低，可能会导致虚假的重新发送，从而浪费网络资源，而“min”值越大，则会增加不可靠网络链路上的总延迟。
 *
 * \注意：网络连接越不可靠，为了实现可靠的握手，最大/最小比率就越大。
 *
 * \注意消息的重传次数最多为log2（ceil（max/min））次。例如，如果min=1s，max=5s，则重新发送计划为：send…1s->重发…2s->重发…4s->重发…5s->放弃并返回超时错误。
 */
void mbedtls_ssl_conf_handshake_timeout( mbedtls_ssl_config *conf, uint32_t min, uint32_t max );
#endif /* MBEDTLS_SSL_PROTO_DTLS */

#if defined(MBEDTLS_SSL_SRV_C)
/**
 * \brief设置会话缓存回调（仅限服务器端）如果未设置，则不会执行会话恢复（除非会话票证也已启用）。
 *
 *                 会话缓存有责任根据超时检查过时条目。有关建议，请参阅RFC 5246。
 *
 *                 警告：连接关闭时，SSL/TLS层会清除session.peer_cert，因此不要缓存指针！将其设置为NULL或制作证书的完整副本。
 *
 *                 在初始握手期间调用一次get回调，以启用会话恢复。get函数具有以下参数：（void parameter，mbedtls_ssl_session session）如果找到有效条目，则应使用缓存的值填充会话对象的master，否则返回0，否则返回1。如果peer_cert在缓存条目中正确存在，也可以设置它。
 *
 *                 在初始握手期间调用set回调一次，以在整个握手完成后恢复会话。set函数具有以下参数：（void参数，const mbedtls_ssl_session会话）。该函数应根据会话结构中的数据创建缓存条目以供将来检索，并应记住，当连接终止时，呈现的mbedtls_ssl_session对象（及其所有引用数据）将被ssl/TLS层清除。建议添加元数据以确定条目将来是否仍然有效。如果缓存成功，则返回0，否则返回1。
 *
 * \param conf SSL配置\param p_cache parmate（上下文）用于两个回调\param f_get_cache会话获取回调\pparam f_set_ache会话设置回调
 */
void mbedtls_ssl_conf_session_cache( mbedtls_ssl_config *conf,
        void *p_cache,
        int (*f_get_cache)(void *, mbedtls_ssl_session *),
        int (*f_set_cache)(void *, const mbedtls_ssl_session *) );
#endif /* MBEDTLS_SSL_SRV_C */

#if defined(MBEDTLS_SSL_CLI_C)
/**
 * \会话的简短请求恢复（仅限客户端）会话数据从呈现的会话结构中复制。
 *
 * \param ssl ssl上下文\param会话会话上下文
 *
 * \如果成功，则返回0；如果内存分配失败，则返回MBEDTLS_ERROR_SSL_ALLOC_FAILED；如果使用的服务器端或参数无效，则返回EMBEDTLS_ERR_SSL_BAD_INPUT_DATA
 *
 * \sa mbedtls_ssl_get_session（）
 */
int mbedtls_ssl_set_session( mbedtls_ssl_context *ssl, const mbedtls_ssl_session *session );
#endif /* MBEDTLS_SSL_CLI_C */

/**
 * \brief将序列化的会话数据加载到会话结构中。在客户端上，这可用于在使用mbedstls_ssl_set_session（）恢复会话之前加载已保存的会话。在服务器上，这可以用于会话缓存或会话票证的替代实现。
 *
 * \警告如果对等证书链与会话关联，则序列化状态将仅包含对等方的最终实体证书和链验证的结果（除非禁用验证），而不包含链的其余部分。
 *
 * \参见mbedtls_ssl_session_save（）\参见mbedtls _ssl_set_session（）
 *
 * \param session要填充的会话结构。它必须已使用mbedtls_ssl_session_It（）初始化，但尚未填充。\param buf保存序列化会话数据的缓冲区。它必须是至少为\p len字节的可读缓冲区。\param len序列化数据的大小（以字节为单位）。
 *
 * \如果成功，返回\c 0。\如果内存分配失败，返回#MBEDTLS_ERROR_SSL_ALLOC_FAILED。\如果输入数据无效，则返回#MBEDTLS_ERROR_SSL_BAD_INPUT_DATA。\如果序列化数据是在不同版本或配置的Mbed TLS中生成的，则返回#MBEDTLS_ERROR_SSL_VERSION_MISMATCH。\返回其他类型错误的另一个负值（例如，嵌入证书中不支持的功能）。
 */
int mbedtls_ssl_session_load( mbedtls_ssl_session *session,
                              const unsigned char *buf,
                              size_t len );

/**
 * \brief将会话结构保存为缓冲区中的序列化数据。在客户端，这可以用于保存会话数据，可能保存在非易失性存储中，以便稍后恢复。在服务器上，这可以用于会话缓存或会话票证的替代实现。
 *
 * \参见mbedtls_ssl_session_load（）\参见mbedtls _ssl_get_session_pointer（）
 *
 * \param session要保存的会话结构。\param buf要将序列化数据写入的缓冲区。它必须是至少\p len字节的可写缓冲区，或者如果\p len为\c 0，则可以是\c NULL。\p buf_len可用于写入\p buf的字节数。\param olen已写入或将写入的数据的字节大小。它必须指向有效的\c size_t。
 *
 * \注意，无论buf_len是否足够大，都会将olen更新为正确的值。这使得可以通过调用此函数来确定所需的大小，其中\p buf设置为\c NULL，\p buf_len设置为\c0。
 *
 * \如果成功，返回\c 0。\如果缓冲区太小，则返回#MBEDTLS_ERROR_SSL_BUFFER_TOO_SMALL。
 */
int mbedtls_ssl_session_save( const mbedtls_ssl_session *session,
                              unsigned char *buf,
                              size_t buf_len,
                              size_t *olen );

/**
 * \brief获取指向当前会话结构的指针，例如对其进行序列化。
 *
 * \警告会话的所有权保留在SSL上下文中，返回的指针只保证在下一个API调用在同一\n SSL上下文上操作之前有效。
 *
 * \请参阅mbedtls_ssl_session_save（）
 *
 * \param ssl ssl上下文。
 *
 * \如果成功，返回指向当前会话的指针。\如果没有活动会话，则返回\c NULL。
 */
const mbedtls_ssl_session *mbedtls_ssl_get_session_pointer( const mbedtls_ssl_context *ssl );

/**
 * \brief设置允许的密码套件列表和首选顺序。列表中的第一位具有最高的偏好。（覆盖所有版本特定列表）
 *
 *                      密码套件数组不会被复制，并且必须在ssl_config的生存期内保持有效。
 *
 *                      注意：除非定义了MBEDTLS_SL_SRV_RESPECT_client_preference，否则服务器使用自己的首选项而不是客户端的首选项！
 *
 * \param conf SSL配置\param ciphersuites 0终止的允许密码套件列表
 */
void mbedtls_ssl_conf_ciphersuites( mbedtls_ssl_config *conf,
                                   const int *ciphersuites );

#if defined(MBEDTLS_SSL_DTLS_CONNECTION_ID)
#define MBEDTLS_SSL_UNEXPECTED_CID_IGNORE 0
#define MBEDTLS_SSL_UNEXPECTED_CID_FAIL   1
/**
 * \brief指定传入加密DTLS记录的连接ID的长度，以及意外CID的行为。
 *
 *                      默认情况下，CID长度设置为\c 0，意外的CID将被忽略。
 *
 * \param conf要修改的SSL配置。\param len使用CID机制加密DTLS记录中CID字段的长度（字节）。此值不得大于#MBEDTLS_SL_CID_OUT_LEN_MAX。\param ignore_other_cids当接收到具有意外CID的记录时，确定堆栈的行为。可能的值包括：
 *                          -#MBEDTLS_SL_UNEXPECTED_CID_IGNORE在这种情况下，记录将被忽略。
 *                          -#MBEDTLS_SL_UNEXPECTED_CID_FAIL在这种情况下，堆栈将失败，并返回特定的错误代码#MBEDLLS_error_SSL_UNEEXPECTED_CID。
 *
 * \注意CID规范允许实现对所有传入连接ID使用公共长度或允许可变长度传入ID。Mbed TLS当前要求共享相同SSL配置的所有连接具有相同的长度；这允许更简单地解析记录头。
 *
 * \成功时返回\c 0。\如果own_cid_len太大，则返回#MBEDTLS_ERROR_SSL_BAD_INPUT_DATA。
 */
int mbedtls_ssl_conf_cid( mbedtls_ssl_config *conf, size_t len,
                          int ignore_other_cids );
#endif /* MBEDTLS_SSL_DTLS_CONNECTION_ID */

/**
 * \brief设置允许的密码套件列表和协议特定版本的首选顺序。（仅在服务器端有用）
 *
 *                      密码套件数组不会被复制，并且必须在ssl_config的生存期内保持有效。
 *
 * \param conf SSL配置\param ciphersuites 0终止的允许密码套件列表\param主要版本号（仅支持MBEDTLS_SL_major_version_3）\param次要版本号（MBEDTL_SSL_minor_VERSON_0、MBEDTLS_SL_MINRO_version_1和MBEDTLS-SL_MINO_version_2、MBEDLLS_SL_MINR_version_3）
 *
 * \注意：对于DTLS，DTLS 1.0使用MBEDTLS_SL_MINOR_VERSION_2，DTLS 1.2使用MBEDLLS_SL_MINIOR_VERSON_3
 */
void mbedtls_ssl_conf_ciphersuites_for_version( mbedtls_ssl_config *conf,
                                       const int *ciphersuites,
                                       int major, int minor );

#if defined(MBEDTLS_X509_CRT_PARSE_C)
/**
 * \brief设置用于验证的X.509安全配置文件
 *
 * \注意：对链中的所有证书都实施了限制。但是，握手中的签名不受此设置的影响，而是受\bmbedtls_ssl_conf_sig_hashes（）的影响。
 *
 * \param conf SSL配置\param profile要使用的配置文件
 */
void mbedtls_ssl_conf_cert_profile( mbedtls_ssl_config *conf,
                                    const mbedtls_x509_crt_profile *profile );

/**
 * \brief设置验证对等证书所需的数据
 *
 * \注释有关参数ca_chain（映射到该函数的trust_ca）和ca_crl的注释，请参见\cmbedtls_x509_crt_verify（）。
 *
 * \param conf SSL配置\param ca_chain可信ca链（表示所有完全可信的顶级ca）\param ca _crl可信ca crl
 */
void mbedtls_ssl_conf_ca_chain( mbedtls_ssl_config *conf,
                               mbedtls_x509_crt *ca_chain,
                               mbedtls_x509_crl *ca_crl );

#if defined(MBEDTLS_X509_TRUSTED_CERTIFICATE_CALLBACK)
/**
 * \brief设置可信证书回调。
 *
 *                 此API允许通过回调注册受信任证书集，而不是通过mbedtls_ssl_conf_ca_chain（）配置的链接列表。
 *
 *                 例如，在使用大量CA的情况下，这是有用的，并且不能容忍在链接列表中维护这些CA的效率低下。当需要频繁修改受信任CA集时，它也很有用。
 *
 *                 有关详细信息，请参阅“mbedtls_x509_crt_ca_cb_t”文档。
 *
 * \param conf要注册回调的SSL配置。\param f_ca_cb验证证书链时要使用的受信任证书回调。\param p_ca_cb要传递给\pf_ca_cb的上下文（例如，对可信ca数据库的引用）。
 *
 * \注意：此API与mbedtls_ssl_conf_ca_chain（）不兼容：对该函数的任何调用都会覆盖之前对mbedtls_ssl_conf.ca_chain（（）或mbedtls-ssl_conf-ca_cb（）的调用所设置的值。
 *
 * \注意：此API与CertificateRequest消息中的CA指示不兼容：绑定到SSL配置的服务器端SSL上下文使用通过mbedtls_SSL_conf_CA_cb（）配置的CA回调，并且需要客户端身份验证，将在相应的CertificateRequest消息发送空CA列表。
 *
 * \注意：此API与mbedtls_ssl_set_hs_ca_chain（）不兼容：如果ssl上下文绑定到使用通过mbedtls_ssl_conf_ca_cb（）配置的ca回调的ssl配置，则对mbedtls-ssl_set_hs _ca_cain（）的调用无效。
 *
 * \注意：此API的使用禁止在X.509 CRT签名验证期间使用可重启ECC（但不影响其他使用）。
 *
 * \警告此API与CRL的使用不兼容。对mbedtls_ssl_conf_ca_cb（）的任何调用都会取消设置通过先前对mbedtls _ssl_conf _ca_chain（）的调用配置的CRL。
 *
 * \警告在多线程环境中，回调\pf_ca_cb必须是线程安全的，用户有责任保证这一点（例如，通过\pp_ca_cb指向的回调上下文中包含的互斥锁）。
 */
void mbedtls_ssl_conf_ca_cb( mbedtls_ssl_config *conf,
                             mbedtls_x509_crt_ca_cb_t f_ca_cb,
                             void *p_ca_cb );
#endif /* MBEDTLS_X509_TRUSTED_CERTIFICATE_CALLBACK */

/**
 * \brief设置自己的证书链和私钥
 *
 * \注意owncert应该从证书链的底部开始按顺序包含。顶级证书（自签名）可以省略。
 *
 * \注意：在服务器上，可以多次调用此函数来提供多个证书/密钥对（例如，一个ECDSA，一个带SHA-256的RSA，一个带有SHA-1的RSA）。将根据客户端的公告功能选择适当的证书。如果有多个证书是足够的，则优先选择通过第一次调用此函数，然后第二次调用等设置的证书。
 *
 * \注意：在客户端上，只有第一次调用具有任何效果。也就是说，只能配置一个客户端证书。服务器在其CertificateRequest消息中的首选项将被忽略，并且无论它是否匹配这些首选项，都将发送我们唯一的证书-然后服务器就可以决定要使用它做什么。
 *
 * \注意：提供的pk_key需要与own_cert中的第一个证书中的公钥匹配，否则使用该证书的所有握手都将失败。您有责任确保：；此函数不会执行任何检查。您可以使用mbedtls_pk_check_pair（）来自己执行此检查，但请注意，对于某些键类型，此函数的计算量可能会很高。
 *
 * \param conf SSL配置\param own_cert自己的公钥链\param pk_key自己的私钥
 *
 * \成功时返回0或MBEDTLS_ERROR_SSL_ALLOC_FAILED
 */
int mbedtls_ssl_conf_own_cert( mbedtls_ssl_config *conf,
                              mbedtls_x509_crt *own_cert,
                              mbedtls_pk_context *pk_key );
#endif /* MBEDTLS_X509_CRT_PARSE_C */

#if defined(MBEDTLS_KEY_EXCHANGE_SOME_PSK_ENABLED)
/**
 * \brief配置要在基于PSK的密码套件中使用的预共享密钥（PSK）和身份。
 *
 * \注意：这主要对客户端有用。服务器通常希望改用\c mbedtls_ssl_conf_psk_cb（）。
 *
 * \注意：在PSK回调中由\c mbedtls_ssl_set_hs_PSK（）设置的PSK优先于此函数配置的PSK。
 *
 * \警告当前，客户端只能注册单个预共享密钥。多次调用此函数或mbedtls_ssl_conf_psk_opaque（）将覆盖以前调用中配置的值。支持在客户端上设置多个PSK，并根据身份提示选择一个PSK不是计划中的功能，但欢迎反馈。
 *
 * \param conf要注册PSK的SSL配置。\param psk指向要使用的预共享密钥的指针。\param psk_len预共享密钥的长度（以字节为单位）。\param psk_identity指向预共享密钥标识的指针。\param psk_identity_len预共享密钥标识的长度（以字节为单位）。
 *
 * \注意：PSK及其标识是内部复制的，因此在SSL配置的整个生命周期内，调用方无需保留PSK及其身份。
 *
 * \如果成功，返回\c 0。\失败时返回\c MBEDTLS_error_SSL_XXX错误代码。
 */
int mbedtls_ssl_conf_psk( mbedtls_ssl_config *conf,
                const unsigned char *psk, size_t psk_len,
                const unsigned char *psk_identity, size_t psk_identity_len );

#if defined(MBEDTLS_USE_PSA_CRYPTO)
/**
 * \brief配置要在基于PSK的密码套件中使用的不透明预共享密钥（PSK）和身份。
 *
 * \注意：这主要对客户端有用。服务器通常希望改用\c mbedtls_ssl_conf_psk_cb（）。
 *
 * \注意：由\c mbedtls_ssl_set_hs_PSK_opaque（）在PSK回调中设置的不透明PSK优先于此函数配置的不透明PSK。
 *
 * \警告当前，客户端只能注册单个预共享密钥。多次调用此函数或mbedtls_ssl_conf_psk（）将覆盖以前调用中配置的值。支持在客户端上设置多个PSK，并根据身份提示选择一个PSK不是计划中的功能，但欢迎反馈。
 *
 * \param conf要注册PSK的SSL配置。\param psk保存psk的密钥槽的标识符。在\p conf被销毁或再次成功调用此函数之前，必须用PSA_ALG_CATEGORY_key_DERIVATION类型的密钥填充密钥槽\p psk，其策略允许其用于握手中应用的密钥派生算法。\param psk_identity指向预共享密钥标识的指针。\param psk_identity_len预共享密钥标识的长度（以字节为单位）。
 *
 * \注意：PSK标识提示是在内部复制的，因此调用方无需在SSL配置的生命周期内保留。
 *
 * \如果成功，返回\c 0。\失败时返回\c MBEDTLS_error_SSL_XXX错误代码。
 */
int mbedtls_ssl_conf_psk_opaque( mbedtls_ssl_config *conf,
                                 psa_key_id_t psk,
                                 const unsigned char *psk_identity,
                                 size_t psk_identity_len );
#endif /* MBEDTLS_USE_PSA_CRYPTO */

/**
 * \brief为当前握手设置预共享密钥（PSK）。
 *
 * \注意：这只应在PSK回调中调用，即传递给\c mbedtls_ssl_conf_PSK_cb（）的函数。
 *
 * \注意：此函数设置的PSK优先于\c mbedtls_ssl_conf_PSK（）配置的PSK。
 *
 * \param ssl要为其配置PSK的ssl上下文。\param psk指向预共享密钥的指针。\param psk_len预共享密钥的长度（以字节为单位）。
 *
 * \如果成功，返回\c 0。\失败时返回\c MBEDTLS_error_SSL_XXX错误代码。
 */
int mbedtls_ssl_set_hs_psk( mbedtls_ssl_context *ssl,
                            const unsigned char *psk, size_t psk_len );

#if defined(MBEDTLS_USE_PSA_CRYPTO)
/**
 * \brief为当前握手设置不透明的预共享密钥（PSK）。
 *
 * \注意：这只应在PSK回调中调用，即传递给\c mbedtls_ssl_conf_PSK_cb（）的函数。
 *
 * \注意：此函数设置的不透明PSK优先于由\c mbedtls_ssl_conf_PSK_opaque（）配置的不透明PSK。
 *
 * \param ssl要为其配置PSK的ssl上下文。\param psk保存psk的密钥槽的标识符。在当前握手的持续时间内，密钥槽必须填充PSA_ALG_CATEGORY_key_DERIVATION类型的密钥，其策略允许其用于握手中应用的密钥派生算法。
  *
 * \如果成功，返回\c 0。\失败时返回\c MBEDTLS_error_SSL_XXX错误代码。
 */
int mbedtls_ssl_set_hs_psk_opaque( mbedtls_ssl_context *ssl,
                                   psa_key_id_t psk );
#endif /* MBEDTLS_USE_PSA_CRYPTO */

/**
 * \brief设置PSK回调（仅限服务器端）。
 *
 *                 如果设置了，则在协商了基于PSK的密码套件的每次握手中调用PSK回调。呼叫者提供所接收的身份，并希望接收实际的PSK数据和长度。
 *
 *                 回调具有以下参数：
 *                 -\c void*：不透明指针\p p_psk。
 *                 -\c mbedtls_ssl_context*：应用操作的ssl上下文。
 *                 -\c const unsigned char*：客户端选择的PSK标识。
 *                 -\c size_t：客户端选择的PSK标识的长度。
 *
 *                 如果找到有效的PSK标识，回调应在ssl上下文上使用\cmbedtls_ssl_set_hs_PSK（）或\cmbedtls _ssl_ses_hs_PSK_opaque（）来设置正确的PSK并返回\c 0。任何其他返回值都将导致PSK标识被拒绝。
 *
 * \注意：动态PSK（即由PSK回调设置）优先于静态PSK（例如由\c mbedtls_ssl_conf_PSK（）或\c mbedt ls_ssl-conf_PSK_opaque（）设置）。这意味着，如果使用此函数设置PSK回调，则不需要使用\c mbedtls_ssl_conf_PSK（）或\c mbedt ls_ssl-conf_PSK_opaque（）设置PSK。
 *
 * \param conf要注册回调的SSL配置。\param f_psk用于根据客户端选择的psk标识选择和设置psk的回调。\param p_psk指向要传递给回调的不透明结构的指针，例如psk存储。
 */
void mbedtls_ssl_conf_psk_cb( mbedtls_ssl_config *conf,
                     int (*f_psk)(void *, mbedtls_ssl_context *, const unsigned char *,
                                  size_t),
                     void *p_psk );
#endif /* MBEDTLS_KEY_EXCHANGE_SOME_PSK_ENABLED */

#if defined(MBEDTLS_DHM_C) && defined(MBEDTLS_SSL_SRV_C)

#if !defined(MBEDTLS_DEPRECATED_REMOVED)

#if defined(MBEDTLS_DEPRECATED_WARNING)
#define MBEDTLS_DEPRECATED    __attribute__((deprecated))
#else
#define MBEDTLS_DEPRECATED
#endif

/**
 * \brief设置Diffie-Hellman公共P和G值，读取为十六进制字符串（仅限服务器端）（默认值：MBEDTLS_DHM_RC3526_MOP_208_[PG]）
 *
 * \param conf SSL配置\param dhm_P Diffie Hellman Merkle模数\param dhm_G Diffie Helman Merkle生成器
 *
 * \已弃用被\c mbedtls_ssl_conf_dh_param_bin取代。
 *
 * \如果成功，则返回0
 */
MBEDTLS_DEPRECATED int mbedtls_ssl_conf_dh_param( mbedtls_ssl_config *conf,
                                                  const char *dhm_P,
                                                  const char *dhm_G );

#endif /* MBEDTLS_DEPRECATED_REMOVED */

/**
 * \brief从大端二进制表示中设置Diffie-Hellman公共P和G值。（默认值：MBEDTLS_DHM_RFC3526_ODP_2048_[PG]_BIN）
 *
 * \param conf SSL配置\param dhm_P大端二进制形式的Diffie Hellman Merkle模数\param P_len dhm模数的长度\param dhm_G大端二进制格式的Diffie-Hellman Merkle生成器\param G_len dhm生成器的长度
 *
 * \如果成功，则返回0
 */
int mbedtls_ssl_conf_dh_param_bin( mbedtls_ssl_config *conf,
                                   const unsigned char *dhm_P, size_t P_len,
                                   const unsigned char *dhm_G,  size_t G_len );

/**
 * \brief设置Diffie-Hellman公共P和G值，从现有上下文读取（仅限服务器端）
 *
 * \param conf SSL配置\param dhm_ctx Diffie Hellman Merkle上下文
 *
 * \如果成功，则返回0
 */
int mbedtls_ssl_conf_dh_param_ctx( mbedtls_ssl_config *conf, mbedtls_dhm_context *dhm_ctx );
#endif /* MBEDTLS_DHM_C已定义（MBEDTL_SSL_SRV_C）*/

#if defined(MBEDTLS_DHM_C) && defined(MBEDTLS_SSL_CLI_C)
/**
 * \brief设置Diffie-Hellman参数的最小长度。（仅客户端。）（默认值：1024位。）
 *
 * \param conf SSL配置\param bitlen DHM prime的最小位长度
 */
void mbedtls_ssl_conf_dhm_min_bitlen( mbedtls_ssl_config *conf,
                                      unsigned int bitlen );
#endif /* MBEDTLS_DHM_C && MBEDTLS_SSL_CLI_C */

#if defined(MBEDTLS_ECP_C)
/**
 * \brief按优先顺序设置允许的曲线。（默认值：所有定义的曲线。）
 *
 *                 在服务器上：这只影响ECDHE曲线的选择；用于ECDH和ECDSA的曲线由可用证书列表确定。
 *
 *                 在客户端：这会影响提供给任何用途的曲线列表。服务器可以覆盖我们的首选顺序。
 *
 *                 双方：限制ECDHE和对等方最终实体证书中接受使用的曲线集。
 *
 * \注意：这对证书链中允许的曲线没有影响，请参见\c mbedtls_ssl_conf_cert_profile（）。但是，对于最终实体证书，只有当此列表和证书配置文件都允许密钥时，才会接受密钥。
 *
 * \注意：此列表应按优先级降序排列（首选曲线优先）。
 *
 * \param conf SSL配置\param curves允许的曲线的有序列表，以MBEDTLS_EP_DP_NONE结尾。
 */
void mbedtls_ssl_conf_curves( mbedtls_ssl_config *conf,
                              const mbedtls_ecp_group_id *curves );
#endif /* MBEDTLS_ECP_C */

#if defined(MBEDTLS_KEY_EXCHANGE_WITH_CERT_ENABLED)
/**
 * \brief为握手期间的签名设置允许的哈希值。（默认值：除MD5之外的所有可用哈希。）
 *
 * \注意：这只影响提供的哈希，并且可以在握手期间用于签名。消息身份验证的哈希和TLS PRF由密码套件控制，请参见\c mbedtls_ssl_conf_cherpseuites（）。用于证书签名的哈希由验证配置文件控制，请参见\c mbedtls_ssl_conf_cert_profile（）。
 *
 * \注意：此列表应按首选项降序排列（首选哈希优先）。
 *
 * \param conf SSL配置\param hashes允许的签名哈希的有序列表，由\c MBEDTLS_MD_NONE终止。
 */
void mbedtls_ssl_conf_sig_hashes( mbedtls_ssl_config *conf,
                                  const int *hashes );
#endif /* MBEDTLS_KEY_EXCHANGE_WITH_CERT_ENABLED */

#if defined(MBEDTLS_X509_CRT_PARSE_C)
/**
 * \brief设置或重置主机名，以对照收到的服务器证书进行检查。如果启用了ServerName TLS扩展，它也会设置该扩展。（仅限客户端）
 *
 * \param ssl ssl上下文\param hostname服务器主机名，可以为NULL以清除主机名

 * \注意最大主机名长度MBEDTLS_SL_MAX_HOST_NAME_LEN。
 *
 * \如果成功，则返回0；如果分配失败，则返回MBEDTLS_ERROR_SSL_ALLOC_FAILED；如果输入主机名过长，则返回EMBEDTLS_ERR_SSL_BAD_INPUT_DATA。
 *
 *                 主机名设置为成功时提供的主机名（NULL时清除）。分配失败时，主机名被清除。如果输入失败时间过长，旧主机名将保持不变。
 */
int mbedtls_ssl_set_hostname( mbedtls_ssl_context *ssl, const char *hostname );
#endif /* MBEDTLS_X509_CRT_PARSE_C */

#if defined(MBEDTLS_SSL_SERVER_NAME_INDICATION)
/**
 * \brief为当前握手设置自己的证书和密钥
 *
 * \注意：与\cmbedtls_ssl_conf_own_cert（）相同，但用于SNI回调。
 *
 * \param ssl ssl上下文\param own_cert自己的公钥链\param pk_key自己的私钥
 *
 * \成功时返回0或MBEDTLS_ERROR_SSL_ALLOC_FAILED
 */
int mbedtls_ssl_set_hs_own_cert( mbedtls_ssl_context *ssl,
                                 mbedtls_x509_crt *own_cert,
                                 mbedtls_pk_context *pk_key );

/**
 * \brief设置验证当前握手的对等证书所需的数据
 *
 * \注意：与\c mbedtls_ssl_conf_ca_chain（）相同，但用于SNI回调。
 *
 * \param ssl ssl上下文\param ca_chain可信ca链（表示所有完全可信的顶级ca）\param ca _crl可信ca crl
 */
void mbedtls_ssl_set_hs_ca_chain( mbedtls_ssl_context *ssl,
                                  mbedtls_x509_crt *ca_chain,
                                  mbedtls_x509_crl *ca_crl );

/**
 * \brief为当前握手设置authmode。
 *
 * \注意：与\c mbedtls_ssl_conf_authmode（）相同，但用于SNI回调。
 *
 * \param ssl ssl上下文\param authmode MBEDTLS_SL_VERIFY_NONE、MBEDTL_ssl_VERIFY_OPTIONAL或MBEDTLS_SL_VERIRY_REQUIRED
 */
void mbedtls_ssl_set_hs_authmode( mbedtls_ssl_context *ssl,
                                  int authmode );

/**
 * \brief设置服务器端ServerName TLS扩展回调（可选，仅限服务器端）。
 *
 *                 如果已设置，则每当服务器在握手期间从客户端接收到ServerName TLS扩展时，就会调用ServerName回调。ServerName回调具有以下参数：（void参数、mbedtls_ssl_context ssl、const unsigned char hostname、size_t len）。如果找到了合适的证书，回调必须设置证书和密钥以与\cmbedtls_ssl_set_hs_own_cert（）一起使用（可以重复调用），并且可以选择使用\cmbedtls _ssl_ses_hs_cachen（）调整CA和关联的CRL，以及使用\c mbedtls_ssl_set_hs _authmode（）调整客户端身份验证模式，然后必须返回0。如果找不到匹配的名称，回调必须设置默认证书，或者返回非零以在此时中止握手。
 *
 * \param conf SSL配置\param f_sni验证函数\param p_sni验证参数
 */
void mbedtls_ssl_conf_sni( mbedtls_ssl_config *conf,
                  int (*f_sni)(void *, mbedtls_ssl_context *, const unsigned char *,
                               size_t),
                  void *p_sni );
#endif /* MBEDTLS_SSL_SERVER_NAME_INDICATION */

#if defined(MBEDTLS_KEY_EXCHANGE_ECJPAKE_ENABLED)
/**
 * \brief为当前握手设置EC J-PAKE密码。
 *
 * \注意：一旦握手完成，或者重置或释放SSL上下文，就会生成内部副本并销毁。
 *
 * \注意：需要已经设置SSL上下文。调用此函数的正确位置在\c mbedtls_ssl_setup（）或\c mbedsls_ssl_reset（）和\c mbedt ls_ssl_handshake（）之间。
 *
 * \param ssl ssl上下文\pram pw EC J-PAKE密码（预共享密钥）\pram pw_len pw长度（字节）
 *
 * \成功时返回0或负错误代码。
 */
int mbedtls_ssl_set_hs_ecjpake_password( mbedtls_ssl_context *ssl,
                                         const unsigned char *pw,
                                         size_t pw_len );
#endif /*MBEDTLS_KEY_EXCHANGE_ECJPAKE_ENABLED */

#if defined(MBEDTLS_SSL_ALPN)
/**
 * \brief设置支持的应用层协议。
 *
 * \param conf SSL配置\param protos指向以NULL结尾的受支持协议列表的指针，以降序排列。指向列表的指针由库记录，以供以后根据需要参考，因此表的生存期必须至少与SSL配置结构的生存期一样长。
 *
 * \成功时返回0，或MBEDTLS_ERROR_SSL_BAD_INPUT_DATA。
 */
int mbedtls_ssl_conf_alpn_protocols( mbedtls_ssl_config *conf, const char **protos );

/**
 * \brief获取协商的应用层协议的名称。握手完成后应调用此函数。
 *
 * \param ssl ssl上下文
 *
 * \返回Protcol名称，如果未协商协议，则返回NULL。
 */
const char *mbedtls_ssl_get_alpn_protocol( const mbedtls_ssl_context *ssl );
#endif /* MBEDTLS_SSL_ALPN */

#if defined(MBEDTLS_SSL_DTLS_SRTP)
#if defined(MBEDTLS_DEBUG_C)
static inline const char *mbedtls_ssl_get_srtp_profile_as_string( mbedtls_ssl_srtp_profile profile )
{
    switch( profile )
    {
        case MBEDTLS_TLS_SRTP_AES128_CM_HMAC_SHA1_80:
            return( "MBEDTLS_TLS_SRTP_AES128_CM_HMAC_SHA1_80" );
        case MBEDTLS_TLS_SRTP_AES128_CM_HMAC_SHA1_32:
            return( "MBEDTLS_TLS_SRTP_AES128_CM_HMAC_SHA1_32" );
        case MBEDTLS_TLS_SRTP_NULL_HMAC_SHA1_80:
            return( "MBEDTLS_TLS_SRTP_NULL_HMAC_SHA1_80" );
        case MBEDTLS_TLS_SRTP_NULL_HMAC_SHA1_32:
            return( "MBEDTLS_TLS_SRTP_NULL_HMAC_SHA1_32" );
        default: break;
    }
    return( "" );
}
#endif /* MBEDTLS_DEBUG_C */
/**
 * \在use_srtp扩展中对mki（主密钥id）值的简要管理支持。MKI是SRTP的可选部分，用于密钥管理和重新键入。有关详细信息，请参阅RFC3711第3.1节。默认值为#MBEDTLS_SL_DTLS_SRTP_MKI_UNSUPPORTED。
 *
 * \param conf管理mki支持的SSL配置。\param support_mki_value启用或禁用mki用法。值为#MBEDTLS_SL_DTLS_SRTP_MKI_SUNSUPPORTED或#MBEDLLS_SL_DTL S_SRTP.MKI_SUPPORTED。
 */
void mbedtls_ssl_conf_srtp_mki_value_supported( mbedtls_ssl_config *conf,
                                                int support_mki_value );

/**
 * \brief设置支持的DTLS-SRTP保护配置文件。
 *
 * \param conf SSL配置\param profiles指向MBEDTLS_TLS_RTP_UNSET终止的受支持的保护配置文件列表的指针，以降序排列。指向列表的指针由库记录，以供以后根据需要参考，因此表的生存期必须至少与SSL配置结构的生存期一样长。列表中包含的元素不能超过MBEDTLS_TLS_STRP_MAX_PROFILE_list_LENGTH（不包括终止的MBEDTL_TLS_SRTP_UNSET）。
 *
 * \成功时返回0 \return#MBEDTLS_ERROR_SSL_BAD_INPUT_DATA（当保护配置文件列表不正确时）。
 */
int mbedtls_ssl_conf_dtls_srtp_protection_profiles
                               ( mbedtls_ssl_config *conf,
                                 const mbedtls_ssl_srtp_profile *profiles );

/**
 * \brief设置当前DTLS-SRTP会话的mki_value。
 *
 * \param ssl要使用的ssl上下文。\param mki_value要设置的mki值。\param mki_len mki值的长度。
 *
 * \注意：此功能仅与客户端相关。服务器在握手期间发现mki值。使用此函数在服务器端设置的mki值将被忽略。
 *
 * \成功时返回0 \return#MBEDTLS_ERROR_SSL_BAD_INPUT_DATA\return#EMBEDTLS_ERR_SSL_FEATURE_NAVAILABLE
 */
int mbedtls_ssl_dtls_srtp_set_mki_value( mbedtls_ssl_context *ssl,
                                         unsigned char *mki_value,
                                         uint16_t mki_len );
/**
 * \brief获取协商的DTLS-SRTP信息：保护配置文件和MKI值。
 *
 * \warning握手完成后必须调用此函数。在握手完成之前，此函数返回的值不能被信任或执行。
 *
 * \param ssl要查询的ssl上下文。\param dtls_srtp_info协商的dtls-srtp信息：
 *                         -正在使用保护配置文件。uint16_t上保护配置文件的iana定义值的直接映射。http://www.iana.org/assignments/srtp-protection/srtp-protection.xhtml#MBEDTLS_TLS_SRTP_UNSET，如果未协商SRTP的使用，或者尚未解析对等方的Hello数据包。
 *                         -mki大小和值（如果大小>0）。
 */
void mbedtls_ssl_get_dtls_srtp_negotiation_result( const mbedtls_ssl_context *ssl,
                                                   mbedtls_dtls_srtp_info *dtls_srtp_info );
#endif /* MBEDTLS_SSL_DTLS_SRTP */

/**
 * \brief设置从客户端发送和/或在服务器端接受的最大支持版本（默认值：MBEDTLS_SL_MAX_MAJOR_version、MBEDTL_SSL_MAX_MINOR_VERSON）
 *
 * \注意：这将忽略更高版本的密码套件。
 *
 * \注意：对于DTLS，DTLS 1.0使用MBEDTLS_SL_MINOR_VERSION_2，DTLS 1.2使用MBEDLLS_SL_MINIOR_VERSON_3
 *
 * \param conf SSL配置\param主要版本号（仅支持MBEDTLS_SL_major_version_3）\param次要版本号（MBEDTL_SSL_minor_VERSON_0、MBEDTLS_SL_MINRO_version_1和MBEDTLS-SL_MINO_version_2、MBEDLLS_SL_MINR_version_3）
 */
void mbedtls_ssl_conf_max_version( mbedtls_ssl_config *conf, int major, int minor );

/**
 * \brief设置接受的最低SSL/TLS协议版本（默认值：TLS 1.0）
 *
 * \注意：忽略SSL_MAX_XXXXX_VERSION和SSL_MIN_XXXXX-VERSION范围之外的输入。
 *
 * \注意应避免MBEDTLS_SL_MINOR_VERSION_0（SSL v3）。
 *
 * \注意：对于DTLS，DTLS 1.0使用MBEDTLS_SL_MINOR_VERSION_2，DTLS 1.2使用MBEDLLS_SL_MINIOR_VERSON_3
 *
 * \param conf SSL配置\param主要版本号（仅支持MBEDTLS_SL_major_version_3）\param次要版本号（MBEDTL_SSL_minor_VERSON_0、MBEDTLS_SL_MINRO_version_1和MBEDTLS-SL_MINO_version_2、MBEDLLS_SL_MINR_version_3）
 */
void mbedtls_ssl_conf_min_version( mbedtls_ssl_config *conf, int major, int minor );

#if defined(MBEDTLS_SSL_FALLBACK_SCSV) && defined(MBEDTLS_SSL_CLI_C)
/**
 * \brief设置回退标志（仅限客户端）。（默认值：MBEDTLS_SL_IS_NOT_FALLBACK）。
 *
 * \注意：准备回退连接时设置为MBEDTLS_SL_IS_FALLBACK，即max_version设置为低于您愿意使用的值的连接。不建议使用这种回退连接，但有时需要与有问题（版本不兼容）的服务器进行互操作。
 *
 * \警告对于非回退连接，不应将其设置为MBEDTLS_SL_IS_FALLACK！这可能会持续一段时间，然后在服务器升级到支持更新的TLS版本时会导致故障。
 *
 * \param conf SSL配置\param回退MBEDTLS_SL_IS_NOT_fallback或MBEDTL_SSL_IS_fallback
 */
void mbedtls_ssl_conf_fallback( mbedtls_ssl_config *conf, char fallback );
#endif /* MBEDTLS_SSL_FALLBACK_SCSV && MBEDTLS_SSL_CLI_C */

#if defined(MBEDTLS_SSL_ENCRYPT_THEN_MAC)
/**
 * \brief启用或禁用先加密后MAC（默认值：MBEDTLS_SL_ETM_ENABLED）
 *
 * \注意：这应该始终启用，这是一种安全改进，不应该导致任何互操作性问题（仅当对等方也支持时使用）。
 *
 * \param conf SSL配置\param etm MBEDTLS_SL_etm_ENABLED或MBEDTL_SSL_etm_DISABLED
 */
void mbedtls_ssl_conf_encrypt_then_mac( mbedtls_ssl_config *conf, char etm );
#endif /* MBEDTLS_SSL_ENCRYPT_THEN_MAC */

#if defined(MBEDTLS_SSL_EXTENDED_MASTER_SECRET)
/**
 * \brief启用或禁用扩展主密钥协商。（默认值：MBEDTLS_SL_EXTENDED_MS_ENABLED）
 *
 * \注意：这应该始终启用，这是对协议的安全修复，不应该导致任何互操作性问题（仅当对等方也支持时使用）。
 *
 * \param conf SSL配置\param ems MBEDTLS_SL_EXTENDED_MS_ENABLED或MBEDTL_SSL_EXTENDED_MS_DISABLED
 */
void mbedtls_ssl_conf_extended_master_secret( mbedtls_ssl_config *conf, char ems );
#endif /* MBEDTLS_SSL_EXTENDED_MASTER_SECRET */

#if defined(MBEDTLS_ARC4_C)
/**
 * \brief禁用或启用对RC4的支持（默认值：MBEDTLS_SL_ARC4_DISABLED）
 *
 * \警告：出于安全原因，RFC 7465禁止在DTLS/TLS中使用RC4。使用风险自负。
 *
 * \注意：此函数已弃用，将在库的未来版本中删除。RC4在编译时默认禁用，需要主动启用才能与旧系统一起使用。
 *
 * \param conf SSL配置\param arc4 MBEDTLS_SL_arc4_ENABLED或MBEDTL_SSL_ARC_4_DISABLED
 */
void mbedtls_ssl_conf_arc4_support( mbedtls_ssl_config *conf, char arc4 );
#endif /* MBEDTLS_ARC4_C */

#if defined(MBEDTLS_SSL_SRV_C)
/**
 * \brief是否在CertificateRequest消息中发送可接受CA的列表。（默认值：do send）
 *
 * \param conf SSL配置\param cert_req_ca\ulist MBEDTLS_SL_cert_req_ca_list_ENABLED或MBEDTL_SSL_cert_ca_list_DISABLED
 */
void mbedtls_ssl_conf_cert_req_ca_list( mbedtls_ssl_config *conf,
                                          char cert_req_ca_list );
#endif /* MBEDTLS_SSL_SRV_C */

#if defined(MBEDTLS_SSL_MAX_FRAGMENT_LENGTH)
/**
 * \brief设置要发出和/或协商的最大片段长度。（典型：#MBEDTLS_SL_IN_CONTENT_LEN和#MBEDLLS_SL_OUT_CONTENT.LEN中较小的一个，通常为“2^14”字节）（服务器：设置要发出的最大片段长度，通常由客户端在握手期间协商）（客户端：设置要发送的最大片段长度，并在握手期间与服务器协商）（默认值：#MBEDTLS_SSL_MAX_FRAG_LEN_ONE）
 *
 * \注意：在客户端，将不使用最大片段长度扩展，除非通过此函数将最大片段长度设置为不同于#MBEDTLS_SL_MAX_FRAG_LEN_NONE的值。
 *
 * \注意：对于TLS，这目前只影响ApplicationData（使用\cmbedtls_ssl_read（）发送），而不影响握手消息。使用DTLS，这会影响ApplicationData和握手。
 *
 * \注意：这设置了记录有效负载的最大长度，不包括将添加到其中的记录开销，请参见\c mbedtls_ssl_get_record_expansion（）。
 *
 * \注意：对于DTLS，还可以为传递到传输层的数据包的总大小设置限制，包括记录开销，请参见\c mbedtls_ssl_set_mtu（）。
 *
 * \param conf SSL配置\param mfl_code最大片段长度的代码（允许值：MBEDTLS_SL_MAX_FRAG_LEN_512、MBEDTL_SSL_MAX-FRAG_LEN_1024、MBEDTLS_SL_MMAX_FRAG_REN_2048、MBEDRLS_SL_MAX _FRAG_LIN_4096）
 *
 * \如果成功，则返回0或MBEDTLS_ERROR_SSL_BAD_INPUT_DATA
 */
int mbedtls_ssl_conf_max_frag_len( mbedtls_ssl_config *conf, unsigned char mfl_code );
#endif /* MBEDTLS_SSL_MAX_FRAGMENT_LENGTH */

#if defined(MBEDTLS_SSL_TRUNCATED_HMAC)
/**
 * \brief激活截断HMAC的协商（默认值：MBEDTLS_SL_TRUNC_HMAC_DISABLED）
 *
 * \param conf SSL配置\param truncate启用或禁用（MBEDTLS_SL_TRUNC_HMAC_ENABLED或MBEDTL_SSL_TRUNC_HMAC_DISABLED）
 */
void mbedtls_ssl_conf_truncated_hmac( mbedtls_ssl_config *conf, int truncate );
#endif /* MBEDTLS_SSL_TRUNCATED_HMAC */

#if defined(MBEDTLS_SSL_CBC_RECORD_SPLITTING)
/**
 * \brief启用/禁用1/n-1记录拆分（默认值：MBEDTLS_SL_CBC_record_splitting_ENABLED）
 *
 * \注意：仅影响SSLv3和TLS 1.0，而不影响更高版本。不影响任何版本的非CBC密码套件。
 *
 * \param conf SSL配置\param拆分MBEDTLS_SL_CBC_RECORD_SPLITTING_ENABLED或MBEDTL_SSL_CBC_RECORD_SPLETTING_DISABLED
 */
void mbedtls_ssl_conf_cbc_record_splitting( mbedtls_ssl_config *conf, char split );
#endif /* MBEDTLS_SSL_CBC_RECORD_SPLITTING */

#if defined(MBEDTLS_SSL_SESSION_TICKETS) && defined(MBEDTLS_SSL_CLI_C)
/**
 * \brief启用/禁用会话票证（仅限客户端）。（默认值：MBEDTLS_SL_SESSION_TICKETS_ENABLED。）
 *
 * \注意：在服务器上，使用\c mbedtls_ssl_conf_session_tickts_cb（）。
 *
 * \param conf SSL配置\param use_tickets启用或禁用（MBEDTLS_SL_SESSION_tickets_ENABLED或MBEDTL_SSL_SESSION_ICKETS_DISABLED）
 */
void mbedtls_ssl_conf_session_tickets( mbedtls_ssl_config *conf, int use_tickets );
#endif /* MBEDTLS_SSL_SESSION_TICKETS && MBEDTLS_SSL_CLI_C */

#if defined(MBEDTLS_SSL_RENEGOTIATION)
/**
 * \brief在对等方启动时启用/禁用对连接的重新协商支持（默认值：MBEDTLS_SL_renegotiation_DISABLED）
 *
 * \警告建议您始终禁用反向旋转，除非您知道自己需要它并且知道自己正在做什么。在过去，有几个问题与重新谈判或对其属性的理解不佳有关。
 *
 * \注意服务器端，启用重新协商也会使服务器容易受到恶意客户端的资源DoS攻击。
 *
 * \param conf SSL配置\param重新协商启用或禁用（MBEDTLS_SL_renegotiation_ENABLED或MBEDTL_SSL_RENE戈TIATION_DISABLED）
 */
void mbedtls_ssl_conf_renegotiation( mbedtls_ssl_config *conf, int renegotiation );
#endif /* MBEDTLS_SSL_RENEGOTIATION */

/**
 * \brief防止或允许旧的重新协商。（默认值：MBEDTLS_SL_LEGACY_NO_RENEGOTIATION）
 *
 *                 MBEDTLS_SL_LEGACY_NO_RENEGOTIATION允许建立连接，即使对等方不支持安全重新协商，但不允许在不安全的情况下进行重新协商。（互操作和安全选项）
 *
 *                 MBEDTLS_SL_LEGACY_ALLOW_RENEGOTIATION允许与未升级的对等方重新协商。允许旧式重新协商使连接容易受到特定中间人攻击。（参见RFC 5746）（最具互操作性和最不安全的选项）
 *
 *                 如果对等方不支持安全重新协商，则MBEDTLS_SL_LEGACY_BREAK_HANDSHAKE将断开连接。导致与不支持完全重新协商的未升级对等体的互操作性问题。（最安全的选项，互操作性问题）
 *
 * \param conf SSL配置\param allow_legacy防止或允许（SSL_NO_legacy_RENEGOTIATION、SSL_allow_legacy_RENEGOTION或MBEDTLS_SL_legacy_BREAK_HANDSHAKE）
 */
void mbedtls_ssl_conf_legacy_renegotiation( mbedtls_ssl_config *conf, int allow_legacy );

#if defined(MBEDTLS_SSL_RENEGOTIATION)
/**
 * \brief强制重新协商请求。（默认值：强制，max_records=16）
 *
 *                 当我们请求重新协商时，对等方可以遵守或忽略该请求。此函数允许我们决定是否在对等方不遵守时通过关闭连接来强制执行重新协商请求。
 *
 *                 然而，当发出请求时，记录可能已经在从对等方传输。为了提高可靠性，我们可以在预期的握手记录之前接受一些记录。
 *
 *                 最佳值高度依赖于特定的使用场景。
 *
 * \注意：对于DTLS和服务器发起的重新协商，每当mbedtls_ssl_read（）超时或接收应用程序数据时，HelloRequest都会重新发送，直到：
 *                 -如果max_records记录大于等于0，则已看到该记录，或
 *                 -已经达到了实际握手期间将发生的重传次数。请记住，如果考虑将max_records设置为非常低的值，则请求可能会丢失几次。
 *
 * \警告在客户端上，宽限期只能发生在mbedtls_ssl_read（）期间，而不是mbedtls_ssl_write（）和mbedtls-ssl_regotiate（），它们的行为总是与max_record为0一样。原因是，如果我们从服务器接收应用程序数据，我们需要一个地方来写入数据，而这只发生在mbedtls_ssl_read（）过程中。
 *
 * \param conf SSL配置\param max_records如果不想强制重新协商，请使用MBEDTLS_SL_RENEGOTIATION_NOT_ENFORCED，或者使用非负值强制重新协商但允许max_record记录的宽限期。
 */
void mbedtls_ssl_conf_renegotiation_enforced( mbedtls_ssl_config *conf, int max_records );

/**
 * \brief为定期重新协商设置记录计数器阈值。（默认值：2^48-1）
 *
 *                 当记录计数器（传出或传入）超过定义的阈值时，将自动触发重新协商。默认值旨在防止在计数器即将达到其最大值时关闭连接（不允许换行）。
 *
 *                 较低的值可用于强制执行诸如“必须使用密码X每N个数据包刷新一次密钥”之类的策略。
 *
 *                 通过将conf->disable_renegotiation设置为MBEDTLS_SL_renegotiation_disabled，可以禁用重新协商周期。
 *
 * \注意：当配置的传输为MBEDTLS_SL_transport_DATAGRAM时，最大重新协商周期为2^48-1，而对于MBEDTLS_SL_TRANPORT_STREAM，最大重新谈判周期为2^ 64-1。
 *
 * \param conf SSL配置\param period阈值：大端64位数字。
 */
void mbedtls_ssl_conf_renegotiation_period( mbedtls_ssl_config *conf,
                                   const unsigned char period[8] );
#endif /* MBEDTLS_SSL_RENEGOTIATION */

/**
 * \brief检查是否有已经从基础传输读取但尚未处理的数据。
 *
 * \param ssl ssl上下文
 *
 * \如果没有挂起，则返回0，否则返回1。
 *
 * \注意：这在目的和行为上与\c mbedtls_ssl_get_bytes_available不同，因为它考虑的是任何类型的未处理数据，而不仅仅是未读的应用程序数据。如果\c mbedtls_ssl_get_bytes返回一个非零值，则此函数也会发出挂起数据的信号，但反之则不成立。例如，在DTLS中，可能有更多的记录等待从当前底层传输的数据报中处理。
 *
 * \注意：如果此函数返回1（数据挂起），这并不意味着后续对\c mbedtls_ssl_read的调用将提供任何数据；e、 例如，未处理的数据可能会变成警报或握手消息。
 *
 * \注意：此函数在以下情况下很有用：如果SSL/TLS模块成功从操作（例如握手或应用程序记录读取）返回，并且您正在等待下一个传入数据，则您不能立即在底层传输上空闲以准备好数据，但您需要先检查此函数的值。原因是所需的数据可能已经被读取，但尚未被处理。相反，如果先前对SSL/TLS模块的调用返回了MBEDTLS_error_SSL_WANT_READ，则无需调用此函数，因为后者的错误代码意味着所有内部数据都已处理。
 *
 */
int mbedtls_ssl_check_pending( const mbedtls_ssl_context *ssl );

/**
 * \brief返回要从当前记录中读取的剩余应用程序数据字节数。
 *
 * \param ssl ssl上下文
 *
 * \return应用程序数据记录读取缓冲区中有多少字节可用。
 *
 * \注意：在数据报传输上工作时，这对于检测当前数据报的边界非常有用，以防mbedtls_ssl_read已将最大数据量写入输入缓冲区。
 *
 */
size_t mbedtls_ssl_get_bytes_avail( const mbedtls_ssl_context *ssl );

/**
 * \brief返回证书验证的结果
 *
 * \param ssl要使用的ssl上下文。
 *
 * \如果证书验证成功，则返回\c 0。\如果结果不可用，则返回\c-1u。例如，如果握手提前中止，或者验证回调返回致命错误，则可能会发生这种情况。\返回\c MBEDTLS_X509_BADCERT_XXX和\c MBEDTLS_X509_BADC RL_XXX失败标志的位组合；参见x509.h。
 */
uint32_t mbedtls_ssl_get_verify_result( const mbedtls_ssl_context *ssl );

/**
 * \brief返回当前密码套件的名称
 *
 * \param ssl ssl上下文
 *
 * \返回包含密码套件名称的字符串
 */
const char *mbedtls_ssl_get_ciphersuite( const mbedtls_ssl_context *ssl );

/**
 * \brief返回当前SSL版本（SSLv3/TLSv1/etc）
 *
 * \param ssl ssl上下文
 *
 * \返回包含SSL版本的字符串
 */
const char *mbedtls_ssl_get_version( const mbedtls_ssl_context *ssl );

/**
 * \brief返回记录层添加的（最大）字节数：头+加密/MAC开销（包括填充）
 *
 * \注意：启用记录压缩时，此函数不可用（始终返回错误）。
 *
 * \param ssl ssl上下文
 *
 * \return当前最大记录扩展（以字节为单位），或者如果启用了压缩，则返回MBEDTLS_ERROR_SSL_FEATURE_NAVAILABLE，这会使扩展变得不可预测
 */
int mbedtls_ssl_get_record_expansion( const mbedtls_ssl_context *ssl );

#if defined(MBEDTLS_SSL_MAX_FRAGMENT_LENGTH)
/**
 * \brief返回输出缓冲区的最大片段长度（有效负载，以字节为单位）。对于客户端，这是配置的值。对于服务器，它是两个值中的最小值-配置值和协商值。
 *
 * \sa mbedtls_ssl_conf_max_frag_len（）\sa mbedtls-ssl_get_max_record_payload（）
 *
 * \param ssl ssl上下文
 *
 * \return输出缓冲区的当前最大片段长度。
 */
size_t mbedtls_ssl_get_output_max_frag_len( const mbedtls_ssl_context *ssl );

/**
 * \brief返回输入缓冲区的最大片段长度（有效负载，以字节为单位）。这是协商的最大片段长度，如果没有，则为MBEDTLS_SL_MAX_CONTENT_LEN。如果它也未定义，则值为2^14。此函数用作其前身\c mbedtls_ssl_get_max_frag_len（）。
 *
 * \sa mbedtls_ssl_conf_max_frag_len（）\sa mbedtls-ssl_get_max_record_payload（）
 *
 * \param ssl ssl上下文
 *
 * \return输出缓冲区的当前最大片段长度。
 */
size_t mbedtls_ssl_get_input_max_frag_len( const mbedtls_ssl_context *ssl );

#if !defined(MBEDTLS_DEPRECATED_REMOVED)

#if defined(MBEDTLS_DEPRECATED_WARNING)
#define MBEDTLS_DEPRECATED    __attribute__((deprecated))
#else
#define MBEDTLS_DEPRECATED
#endif

/**
 * \brief此函数是一种不推荐使用的获取最大片段长度的方法。它是\c mbedtls_ssl_get_output_max_frag_len（）的别名，因为行为相同。有关详细信息，请参见\c mbedtls_ssl_get_output_max_frag_len（）。
 *
 * \sa mbedtls_ssl_get_input_max_frag_len（）\sa mbedtls-ssl_get_output_max_frag_len
 *
 * \param ssl ssl上下文
 *
 * \return输出缓冲区的当前最大片段长度。
 */
MBEDTLS_DEPRECATED size_t mbedtls_ssl_get_max_frag_len(
                                        const mbedtls_ssl_context *ssl );
#endif /* MBEDTLS_DEPRECATED_REMOVED */
#endif /* MBEDTLS_SSL_MAX_FRAGMENT_LENGTH */

/**
 * \brief返回当前最大传出记录负载（字节）。这将考虑到配置。h设置\c MBEDTLS_SL_OUT_CONTENT_LEN，配置和协商的最大片段长度扩展（如果使用），以及DTLS的路径MTU配置和当前记录扩展。
 *
 * \注意：对于DTLS，如果使用较大的长度值调用，\c mbedtls_ssl_write（）将返回错误。使用TLS，\c mbedtls_ssl_write（）将在必要时对输入进行分段，并返回写入的字节数；调用方需要再次调用\cmbedtls_ssl_write（），以便发送剩余的字节（如果有的话）。
 *
 * \注意：启用记录压缩时，此函数不可用（始终返回错误）。
 *
 * \sa mbedtls_ssl_set_mtu（）\sa mbedtls-ssl_get_output_max_frag_len
 *
 * \param ssl ssl上下文
 *
 * \return传出记录的当前最大有效负载或负错误代码。
 */
int mbedtls_ssl_get_max_out_record_payload( const mbedtls_ssl_context *ssl );

#if defined(MBEDTLS_X509_CRT_PARSE_C)
/**
 * \brief从当前连接返回对等证书。
 *
 * \param ssl要使用的ssl上下文。必须对其进行初始化和设置。
 *
 * \return当前对等证书（如果可用）。返回的证书由SSL上下文拥有，仅在下次调用SSL API之前有效。\如果没有可用的对等证书，则返回\c NULL。这可能是因为所选的密码套件不使用CRT（例如，基于PSK的密码套件），或者因为#MBEDTLS_SL_KEEP_PEER_CERTIFICATE已禁用，从而允许堆栈释放对等方的CRT以节省内存。
 *
 * \注意：为了在握手期间一次性检查对等方的证书，请考虑通过mbedtls_ssl_conf_verify（）注册X.509 CRT验证回调，而不是调用此函数。使用mbedtls_ssl_conf_fverify（）也有助于您影响验证过程，例如通过屏蔽预期和可容忍的验证失败。
 *
 * \警告：在进一步调用SSL API（包括mbedtls_SSL_read（）和mbedtls_SSL_write（））后，不能使用此函数返回的指针；这是因为指针可能在重新协商期间发生变化，这对用户来说是透明的。如果要在API调用中使用证书，必须创建一个副本。
 */
const mbedtls_x509_crt *mbedtls_ssl_get_peer_cert( const mbedtls_ssl_context *ssl );
#endif /* MBEDTLS_X509_CRT_PARSE_C */

#if defined(MBEDTLS_SSL_CLI_C)
/**
 * \简要保存会话以便稍后恢复（仅限客户端）会话数据将复制到呈现的会话结构中。
 *
 * \param ssl ssl上下文\param会话会话上下文
 *
 * \如果成功，则返回0；如果内存分配失败，则返回MBEDTLS_ERROR_SSL_ALLOC_FAILED；如果使用的服务器端或参数无效，则返回EMBEDTLS_ERR_SSL_BAD_INPUT_DATA。
 *
 * \注意：只复制服务器证书，而不是整个链，因此您不应通过对证书调用\cmbedtls_x509_crt_verify（）来再次验证证书。相反，您应该在使用\c mbedtls_ssl_set_session（）将会话再次加载到新的ssl上下文中之后，通过调用\c mbedt ls_ssl_get_verify_result（）来使用原始握手中的验证结果。
 *
 * \注意：一旦不再需要会话对象，就应该通过调用\cmbedtls_ssl_session_free（）来释放它。
 *
 * \sa mbedtls_ssl_set_session（）
 */
int mbedtls_ssl_get_session( const mbedtls_ssl_context *ssl, mbedtls_ssl_session *session );
#endif /* MBEDTLS_SSL_CLI_C */

/**
 * \brief执行SSL握手
 *
 * \param ssl ssl上下文
 *
 * \如果成功，返回\c 0。\返回#MBEDTLS_ERROR_SSL_WANT_READ或#MBEDLLS_ERROR_SSL _WANT_WRITE，如果握手不完整，并且等待数据可用于从基础传输中读取或写入-在这种情况下，当基础传输准备好进行操作时，必须再次调用此函数。\如果正在进行异步操作，返回#MBEDTLS_ERROR_SSL_ASYNC_IN_PROGRESS（请参阅MBEDTLS_SSL_conf_ASYNC_private_cb（））-在这种情况下，当操作准备就绪时，必须再次调用此函数。\如果正在进行加密操作，返回#MBEDTLS_ERROR_SSL_CRYPTO_IN_PROGRESS（请参阅MBEDTLS_ecp_set_max_ops（））-在这种情况下，当您完成其他任务时，必须再次调用此函数以完成握手。\返回#MBEDTLS_ERROR_SSL_HELLO_VERIFY_REQUIRED，如果DTLS正在使用，并且客户端尚未显示可访问性-在这种情况下，您必须停止使用上下文（见下文）。\返回另一个SSL错误代码-在这种情况下，您必须停止使用上下文（见下文）。
 *
 * \警告如果此函数返回的内容不是\c 0、#MBEDTLS_ERROR_SSL_WANT_READ、#MBETTLS_ERROR_StSL_WANT_WRITE、#MBEDTLS_ERR_SSL_ASYNC_IN_PROGRESS或#MBETLS_ERR_StSL_CRYPTO_IN_PROGRESSS，则必须停止使用SSL上下文进行读取或写入，并释放它或在其上调用\c MBEDTLS_SSL_session\set（），然后再将其用于新连接；必须关闭当前连接。
 *
 * \注意：如果DTLS正在使用中，那么您可以选择专门处理#MBEDTLS_error_SSL_HELLO_VERIFY_REQUIRED以用于日志记录，因为它是一个预期的返回值，而不是实际的错误，但您仍然需要重置/释放上下文。
 *
 * \注意：关于事件驱动DTLS的备注：如果函数返回#MBEDTLS_ERROR_SSL_WANT_READ，则当前未处理来自底层传输层的数据报，并且在计时器或底层传输发出新事件信号之前，可以安全地空闲。这对于成功的握手是不正确的，在这种情况下，当前正在处理的底层传输的数据报可能包含或可能不包含进一步的DTLS记录。
 */
int mbedtls_ssl_handshake( mbedtls_ssl_context *ssl );

/**
 * \brief执行SSL握手的单个步骤
 *
 * \注意：此函数返回\c 0后，上下文的状态（ssl->state）将处于下一个状态。如果状态为MBEDTLS_SL_HANDSHAKE_OVER，请不要调用此函数。
 *
 * \param ssl ssl上下文
 *
 * \return请参见mbedtls_ssl_handshake（）。
 *
 * \警告如果此函数返回的内容不是\c 0、#MBEDTLS_ERROR_SSL_WANT_READ、#MBETTLS_ERROR_StSL_WANT_WRITE、#MBEDTLS_ERR_SSL_ASYNC_IN_PROGRESS或#MBETLS_ERR_StSL_CRYPTO_IN_PROGRESSS，则必须停止使用SSL上下文进行读取或写入，并释放它或在其上调用\c MBEDTLS_SSL_session\set（），然后再将其用于新连接；必须关闭当前连接。
 */
int mbedtls_ssl_handshake_step( mbedtls_ssl_context *ssl );

#if defined(MBEDTLS_SSL_RENEGOTIATION)
/**
 * \brief在正在运行的连接上启动SSL重新协商。客户：现在就重新协商。服务器：请求重新协商，如果客户机同意，将在下次调用mbedtls_ssl_read（）时执行。
 *
 * \param ssl ssl上下文
 *
 * \如果成功，则返回0，或任何mbedtls_ssl_handshake（）返回值，但#mbedtls_ERROR_ssl_CLIENT_RECONNECT除外，该值在重新协商期间无法发生。
 *
 * \警告如果此函数返回的内容不是\c 0、#MBEDTLS_ERROR_SSL_WANT_READ、#MBETTLS_ERROR_StSL_WANT_WRITE、#MBEDTLS_ERR_SSL_ASYNC_IN_PROGRESS或#MBETLS_ERR_StSL_CRYPTO_IN_PROGRESSS，则必须停止使用SSL上下文进行读取或写入，并释放它或在其上调用\c MBEDTLS_SSL_session\set（），然后再将其用于新连接；必须关闭当前连接。
 *
 */
int mbedtls_ssl_renegotiate( mbedtls_ssl_context *ssl );
#endif /* MBEDTLS_SSL_RENEGOTIATION */

/**
 * \brief最多读取“len”应用程序数据字节
 *
 * \param ssl ssl上下文\param保存数据的缓冲区\param len要读取的最大字节数
 *
 * \return如果成功，读取的字节数（正数）。\return \c 0如果基础传输的读取端在未事先发送CloseNotify的情况下关闭，这可能是由于各种原因（基础堆栈的内部错误、不一致的对等端未发送CloseNotify等）导致的-在这种情况下，必须停止使用上下文（见下文）。\返回#MBEDTLS_ERROR_SSL_PEER_CLOSE_NOTIFY，如果基础传输仍然正常，但对等方已确认不再发送任何内容。\返回#MBEDTLS_ERROR_SSL_WANT_READ或#MBEDLLS_ERROR_SSL _WANT_WRITE，如果握手不完整，并且等待数据可用于从基础传输中读取或写入-在这种情况下，当基础传输准备好进行操作时，必须再次调用此函数。\如果正在进行异步操作，返回#MBEDTLS_ERROR_SSL_ASYNC_IN_PROGRESS（请参阅MBEDTLS_SSL_conf_ASYNC_private_cb（））-在这种情况下，当操作准备就绪时，必须再次调用此函数。\如果正在进行加密操作，返回#MBEDTLS_ERROR_SSL_CRYPTO_IN_PROGRESS（请参阅MBEDTLS_ecp_set_max_ops（））-在这种情况下，当您完成其他任务时，必须再次调用此函数以完成握手。\return#MBEDTLS_ERROR_SSL_CLIENT_RECONNECT，如果我们在DTLS连接的服务器端，并且客户端正在使用相同的源端口启动新连接。请参见下文。\返回另一个SSL错误代码-在这种情况下，您必须停止使用上下文（见下文）。
 *
 * \警告如果此函数返回的值不是正值，#MBEDTLS_ERROR_SSL_WANT_READ、#MBEDLLS_ERROR_SSL _WANT_WRITE、#MBEDTLS_ERR_SSL_ASYNC_IN_PROGRESS、#MBETLS_ERR_StSL_CRYPTO_IN_PROGRESS或#MBEDLS_ERR_STSL_CLIENT_RECONNECT，则必须停止使用SSL上下文进行读取或写入，在重新使用它进行新连接之前，释放它或调用它上的\c mbedtls_ssl_session_set（）；必须关闭当前连接。
 *
 * \注意：当此函数返回#MBEDTLS_ERROR_SSL_CLIENT_RECONNECT（只能发生在服务器端）时，这意味着客户端正在使用同一源端口启动新连接。您可以将其视为连接关闭并等待客户端重新发送ClientHello，或直接使用具有相同上下文的\c mbedtls_ssl_handshake（）继续（因为它已在内部重置）。无论哪种方式，您都必须确保应用程序将其视为新的连接：应用程序状态（如果有的话）应该重置，最重要的是必须再次检查客户端的身份。警告：不再次验证客户端的身份，或者不将新身份传输到应用程序层，将允许绕过身份验证！
 *
 * \注关于事件驱动DTLS的备注：
 *                 -如果函数返回#MBEDTLS_ERROR_SSL_WANT_READ，则当前没有处理来自底层传输层的数据报，并且在计时器或底层传输发出新事件信号之前，可以安全地空闲。
 *                 -即使数据最初在基础传输上可用，此函数也可能返回MBEDTLS_ERROR_SSL_WANT_READ，因为此数据可能仅是重复的消息或重新协商请求。因此，即使在对来自底层传输的传入数据事件作出响应时，也必须做好接收MBEDTLS_ERROR_SSL_WANT_READ的准备。
 *                 -成功后，当前正在处理的底层传输的数据报可能包含进一步的DTLS记录。您应该调用\c mbedtls_ssl_check_pending来检查剩余记录。
 *
 */
int mbedtls_ssl_read( mbedtls_ssl_context *ssl, unsigned char *buf, size_t len );

/**
 * \brief尝试精确写入“len”应用程序数据字节
 *
 * \警告在某些情况下，此函数将执行部分写入。如果返回值为非负值但小于长度，则必须使用更新的参数再次调用该函数：buf+ret，len-ret（如果ret是返回值），直到它返回一个等于最后一个“len”参数的值。
 *
 * \param ssl ssl上下文\param保存数据的缓冲区\param len必须写入多少字节
 *
 * \return如果成功，实际写入的字节数（非负）（可能小于\p len）。\返回#MBEDTLS_ERROR_SSL_WANT_READ或#MBEDLLS_ERROR_SSL _WANT_WRITE，如果握手不完整，并且等待数据可用于从基础传输中读取或写入-在这种情况下，当基础传输准备好进行操作时，必须再次调用此函数。\如果正在进行异步操作，返回#MBEDTLS_ERROR_SSL_ASYNC_IN_PROGRESS（请参阅MBEDTLS_SSL_conf_ASYNC_private_cb（））-在这种情况下，当操作准备就绪时，必须再次调用此函数。\如果正在进行加密操作，返回#MBEDTLS_ERROR_SSL_CRYPTO_IN_PROGRESS（请参阅MBEDTLS_ecp_set_max_ops（））-在这种情况下，当您完成其他任务时，必须再次调用此函数以完成握手。\返回另一个SSL错误代码-在这种情况下，您必须停止使用上下文（见下文）。
 *
 * \警告如果此函数返回非负值以外的值，#MBEDTLS_ERROR_SSL_WANT_READ、#MBEDLLS_ERROR_SSL _WANT_WRITE、#MBEDTLS_ERR_SSL_ASYNC_IN_PROGRESS或#MBEDRLS_ERR_SSL_CRYPTO_IN_PROGRESSS，则必须停止使用SSL上下文进行读取或写入，并释放它或在其上调用\c MBEDTLS_SSL_session _reset（），然后再将其用于新连接；必须关闭当前连接。
 *
 * \注意：当此函数返回#MBEDTLS_ERROR_SSL_WANT_WRITE/READ时，必须稍后使用相同的参数调用它，直到它返回一个大于或等于0的值。当函数返回#EMBEDTLS_ERR_SSL_WANT_WRITE时，输出缓冲区中可能有一些部分数据，但尚未发送。
 *
 * \注意：如果请求的长度大于最大片段长度（内置限制或一组或与对等方协商），则：
 *                 -使用TLS，写入的字节数少于请求的字节数。
 *                 -对于DTLS，返回MBEDTLS_ERROR_SSL_BAD_INPUT_DATA。\c mbedtls_ssl_get_output_max_frag_len（）可用于查询活动的最大片段长度。
 *
 * \注意：尝试写入0字节将导致发送空TLS应用程序记录。
 */
int mbedtls_ssl_write( mbedtls_ssl_context *ssl, const unsigned char *buf, size_t len );

/**
 * \brief发送警报消息
 *
 * \param ssl ssl上下文\param level消息的警报级别（MBEDTLS_SL_alert_level_WARNING或MBEDTL_ssl_ALET_level_FATAL）\param message警报消息（ssl_alert_MSG_）
 *
 * \如果成功，则返回0，或者返回特定的SSL错误代码。
 *
 * \注意：如果此函数返回的值不是0或MBEDTLS_ERROR_SSL_WANT_READ/WRITE，则必须停止使用SSL上下文进行读取或写入，并在重新将其用于新连接之前释放它或调用其上的\c MBEDTLS_SSL_session_set（）；必须关闭当前连接。
 */
int mbedtls_ssl_send_alert_message( mbedtls_ssl_context *ssl,
                            unsigned char level,
                            unsigned char message );
/**
 * \brief通知对等方连接正在关闭
 *
 * \param ssl ssl上下文
 *
 * \如果成功，则返回0，或者返回特定的SSL错误代码。
 *
 * \注意：如果此函数返回的值不是0或MBEDTLS_ERROR_SSL_WANT_READ/WRITE，则必须停止使用SSL上下文进行读取或写入，并在重新将其用于新连接之前释放它或调用其上的\c MBEDTLS_SSL_session_set（）；必须关闭当前连接。
 */
int mbedtls_ssl_close_notify( mbedtls_ssl_context *ssl );

/**
 * \brief释放SSL上下文中的引用项并清除内存
 *
 * \param ssl ssl上下文
 */
void mbedtls_ssl_free( mbedtls_ssl_context *ssl );

#if defined(MBEDTLS_SSL_CONTEXT_SERIALIZATION)
/**
 * \brief将活动连接保存为缓冲区中的序列化数据。这允许释放或重新使用SSL上下文，同时稍后仍以对对等方完全透明的方式获取连接。
 *
 * \请参阅mbedtls_ssl_context_load（）
 *
 * \注意：此功能当前仅在特定条件下可用，有关详细信息，请参阅返回值#MBEDTLS_ERROR_SSL_BAD_INPUT_DATA的文档。
 *
 * \注意：当此函数成功时，它将调用\pssl上的mbedtls_ssl_session_set（），因此该函数不再与已序列化的连接关联。这避免了创建连接状态的副本。然后，您可以为不同的连接重新使用上下文结构，或者对其调用mbedtls_ssl_free（）。有关详细信息，请参阅mbedtls_ssl_session_reset（）的文档。
 *
 * \param ssl要保存的ssl上下文。成功后，它不再与已序列化的连接关联。\param buf要将序列化数据写入的缓冲区。它必须是至少\p buf_len字节的可写缓冲区，或者如果\p buf _len为\c 0，则可以是\c NULL。\p buf-len可用于写入\p buf的字节数。\param olen已写入或将写入的数据的字节大小。它必须指向有效的\c size_t。
 *
 * \注意，无论buf_len是否足够大，都会将olen更新为正确的值。这使得可以通过调用此函数来确定所需的大小，并将\buff设置为\c NULL，将\buf_len设置为\c0。但是，只有当函数返回#MBEDTLS_ERROR_SSL_BUFFER_TOO_SMALL或\c 0时，才能保证\n olen的值正确。如果返回值不同，则\n olen值未定义。
 *
 * \如果成功，返回\c 0。\如果缓冲区太小，则返回#MBEDTLS_ERROR_SSL_BUFFER_TOO_SMALL。\如果重置上下文时内存分配失败，则返回#MBEDTLS_ERROR_SSL_ALLOC_FAILED。\return#MBEDTLS_ERROR_SSL_BAD_INPUT_DATA，如果正在进行握手，或者有待读取或发送的数据，或者连接未将DTLS 1.2与AEAD密码套件一起使用，或者已启用重新协商。
 */
int mbedtls_ssl_context_save( mbedtls_ssl_context *ssl,
                              unsigned char *buf,
                              size_t buf_len,
                              size_t *olen );

/**
 * \brief将序列化连接数据加载到SSL上下文。
 *
 * \请参见mbedtls_ssl_context_save（）
 *
 * \警告同一序列化数据不能加载到多个上下文中。为了确保在成功将序列化数据加载到SSL上下文后，应立即销毁或使加载的序列化数据的所有副本无效。在多个上下文中加载相同的数据将导致严重的安全故障，包括但不限于丢失机密性。
 *
 * \注意：在调用此函数之前，必须以以下两种方式之一准备SSL上下文。第一种方法是获取一个用mbedtls_ssl_init（）初始化的上下文，并使用原始连接中使用的相同：：mbedtls_ssl_config结构对其调用mbedtls-ssl_setup（）。第二种方法是在先前如上所述准备但同时使用的上下文上调用mbedtls_ssl_session\ureset（）。无论哪种方式，都不能使用上下文在调用mbedtls_ssl_setup（）或mbedtls_ssl_session_set（）与调用此函数之间执行握手。但是，您可以在该时间范围内调用其他setter函数，如下面的注释所示。
 *
 * \注意：在成功调用此函数之前或之后，您还需要配置一些特定于连接的回调和设置，然后才能再次使用连接（除非在调用mbedtls_ssl_session_set（）之前已经设置了这些回调和设置并且这些值适用于当前连接）。具体来说，您希望至少调用mbedtls_ssl_set_bio（）和mbedtls_ssl_set_timer_cb（）。不需要调用所有其他SSL setter函数，因为它们只用于握手，或者因为设置已经保存。您可以选择无论如何调用它们，例如，为了在建立新连接和加载已建立的连接的情况下共享代码。
 *
 * \注意：如果您有关于路径MTU的新信息，则需要在调用此函数后调用mbedtls_ssl_set_MTU（），否则此函数将用保存上下文时处于活动状态的值覆盖新配置的值。
 *
 * \注意：当此函数返回错误代码时，它将调用\pssl上的mbedtls_ssl_free（）。在这种情况下，如果要再次使用它，则需要使用通常的序列来准备上下文，首先调用mbedtls_ssl_init（）。
 *
 * \param ssl要填充的ssl上下文结构。必须按照上述说明进行准备。\param buf保存序列化连接数据的缓冲区。它必须是至少为\p len字节的可读缓冲区。\param len序列化数据的大小（以字节为单位）。
 *
 * \如果成功，返回\c 0。\如果内存分配失败，返回#MBEDTLS_ERROR_SSL_ALLOC_FAILED。\如果序列化数据来自不同的Mbed TLS版本或内部版本，则返回#MBEDTLS_ERROR_SSL_VERSION_MISMATCH。\如果输入数据无效，则返回#MBEDTLS_ERROR_SSL_BAD_INPUT_DATA。
 */
int mbedtls_ssl_context_load( mbedtls_ssl_context *ssl,
                              const unsigned char *buf,
                              size_t len );
#endif /* MBEDTLS_SSL_CONTEXT_SERIALIZATION */

/**
 * \brief初始化SSL配置上下文仅使上下文为mbedtls_SSL_config_defaults（）或mbedtls_SSL_config_free（）做好准备。
 *
 * \注意，除非您自己手动设置所有相关字段，否则需要调用mbedtls_ssl_config_defaults（）。
 *
 * \param conf SSL配置上下文
 */
void mbedtls_ssl_config_init( mbedtls_ssl_config *conf );

/**
 * \brief Load reasonable默认SSL配置值。（您需要首先调用mbedtls_ssl_config_init（）。）
 *
 * \param conf SSL配置上下文\param端点MBEDTLS_SL_IS_CLIENT或MBEDTLS_SL_IS_SERVER\param传输MBEDTL_SSL_transport_STREAM（TLS）或MBEDRLS_SL_TRANPORT_DATAGRAM（DTLS）\param预设MBEDTLS-SL_preset_XXX值
 *
 * \注释有关DTLS的注释，请参见\c mbedtls_ssl_conf_transport（）。
 *
 * \如果成功，则返回0；如果内存分配错误，则返回MBEDTLS_error_XXX_ALLOC_FAILED。
 */
int mbedtls_ssl_config_defaults( mbedtls_ssl_config *conf,
                                 int endpoint, int transport, int preset );

/**
 * \brief释放SSL配置上下文
 *
 * \param conf SSL配置上下文
 */
void mbedtls_ssl_config_free( mbedtls_ssl_config *conf );

/**
 * \brief初始化SSL会话结构
 *
 * \param会话SSL会话
 */
void mbedtls_ssl_session_init( mbedtls_ssl_session *session );

/**
 * \brief释放SSL会话中的引用项，包括对等证书和清除内存
 *
 * \注意：即使用于检索会话的SSL上下文仍在使用，也可以释放会话对象。
 *
 * \param会话SSL会话
 */
void mbedtls_ssl_session_free( mbedtls_ssl_session *session );

/**
 * \用于密钥推导的简要TLS-PRF函数。
 *
 * \param prf要使用的tls_prf类型函数类型。\param secret密钥派生函数的密钥。\param slen机密的长度。\param label键派生函数的字符串标签，以空字符结尾。\param随机随机字节。\param rlen随机字节缓冲区的长度。\param dstbuf保存派生密钥的缓冲区。\param dlen输出缓冲区的长度。
 *
 * \成功时返回0。失败时出现SSL特定错误。
 */
int  mbedtls_ssl_tls_prf( const mbedtls_tls_prf_types prf,
                          const unsigned char *secret, size_t slen,
                          const char *label,
                          const unsigned char *random, size_t rlen,
                          unsigned char *dstbuf, size_t dlen );

#ifdef __cplusplus
}
#endif

#endif /* ssl.h*/

