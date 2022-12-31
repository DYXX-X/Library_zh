/**
 * \文件ssl_internal.h
 *
 * \SSL模块共享的简短内部功能
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
#ifndef MBEDTLS_SSL_INTERNAL_H
#define MBEDTLS_SSL_INTERNAL_H

#if !defined(MBEDTLS_CONFIG_FILE)
#include "mbedtls/config.h"
#else
#include MBEDTLS_CONFIG_FILE
#endif

#include "mbedtls/ssl.h"
#include "mbedtls/cipher.h"

#if defined(MBEDTLS_USE_PSA_CRYPTO)
#include "psa/crypto.h"
#endif

#if defined(MBEDTLS_MD5_C)
#include "mbedtls/md5.h"
#endif

#if defined(MBEDTLS_SHA1_C)
#include "mbedtls/sha1.h"
#endif

#if defined(MBEDTLS_SHA256_C)
#include "mbedtls/sha256.h"
#endif

#if defined(MBEDTLS_SHA512_C)
#include "mbedtls/sha512.h"
#endif

#if defined(MBEDTLS_KEY_EXCHANGE_ECJPAKE_ENABLED)
#include "mbedtls/ecjpake.h"
#endif

#if defined(MBEDTLS_USE_PSA_CRYPTO)
#include "psa/crypto.h"
#include "mbedtls/psa_util.h"
#endif /* MBEDTLS_USE_PSA_CRYPTO */

#if ( defined(__ARMCC_VERSION) || defined(_MSC_VER) ) && \
    !defined(inline) && !defined(__cplusplus)
#define inline __inline
#endif

/* 确定最低支持版本*/
#define MBEDTLS_SSL_MIN_MAJOR_VERSION           MBEDTLS_SSL_MAJOR_VERSION_3

#if defined(MBEDTLS_SSL_PROTO_SSL3)
#define MBEDTLS_SSL_MIN_MINOR_VERSION           MBEDTLS_SSL_MINOR_VERSION_0
#else
#if defined(MBEDTLS_SSL_PROTO_TLS1)
#define MBEDTLS_SSL_MIN_MINOR_VERSION           MBEDTLS_SSL_MINOR_VERSION_1
#else
#if defined(MBEDTLS_SSL_PROTO_TLS1_1)
#define MBEDTLS_SSL_MIN_MINOR_VERSION           MBEDTLS_SSL_MINOR_VERSION_2
#else
#if defined(MBEDTLS_SSL_PROTO_TLS1_2)
#define MBEDTLS_SSL_MIN_MINOR_VERSION           MBEDTLS_SSL_MINOR_VERSION_3
#endif /* MBEDTLS_SSL_PROTO_TLS1_2 */
#endif /* MBEDTLS_SSL_PROTO_TLS1_1 */
#endif /* MBEDTLS_SSL_PROTO_TLS1   */
#endif /* MBEDTLS_SSL_PROTO_SSL3   */

#define MBEDTLS_SSL_MIN_VALID_MINOR_VERSION MBEDTLS_SSL_MINOR_VERSION_1
#define MBEDTLS_SSL_MIN_VALID_MAJOR_VERSION MBEDTLS_SSL_MAJOR_VERSION_3

/* 确定支持的最大版本*/
#define MBEDTLS_SSL_MAX_MAJOR_VERSION           MBEDTLS_SSL_MAJOR_VERSION_3

#if defined(MBEDTLS_SSL_PROTO_TLS1_2)
#define MBEDTLS_SSL_MAX_MINOR_VERSION           MBEDTLS_SSL_MINOR_VERSION_3
#else
#if defined(MBEDTLS_SSL_PROTO_TLS1_1)
#define MBEDTLS_SSL_MAX_MINOR_VERSION           MBEDTLS_SSL_MINOR_VERSION_2
#else
#if defined(MBEDTLS_SSL_PROTO_TLS1)
#define MBEDTLS_SSL_MAX_MINOR_VERSION           MBEDTLS_SSL_MINOR_VERSION_1
#else
#if defined(MBEDTLS_SSL_PROTO_SSL3)
#define MBEDTLS_SSL_MAX_MINOR_VERSION           MBEDTLS_SSL_MINOR_VERSION_0
#endif /* MBEDTLS_SSL_PROTO_SSL3   */
#endif /* MBEDTLS_SSL_PROTO_TLS1   */
#endif /* MBEDTLS_SSL_PROTO_TLS1_1 */
#endif /* MBEDTLS_SSL_PROTO_TLS1_2 */

/* 可重启ECC的速记*/
#if defined(MBEDTLS_ECP_RESTARTABLE) && \
    defined(MBEDTLS_SSL_CLI_C) && \
    defined(MBEDTLS_SSL_PROTO_TLS1_2) && \
    defined(MBEDTLS_KEY_EXCHANGE_ECDHE_ECDSA_ENABLED)
#define MBEDTLS_SSL_ECP_RESTARTABLE_ENABLED
#endif

#define MBEDTLS_SSL_INITIAL_HANDSHAKE           0
#define MBEDTLS_SSL_RENEGOTIATION_IN_PROGRESS   1   /* 正在进行中*/
#define MBEDTLS_SSL_RENEGOTIATION_DONE          2   /* 完成或中止*/
#define MBEDTLS_SSL_RENEGOTIATION_PENDING       3   /* 请求（仅限服务器）*/

/*
 * DTLS重传状态，参见RFC 6347 4.2.4
 *
 * 对于初始发送，SENDING状态在PREPARING中合并，但对于重新发送则不同。
 *
 * 注意：服务器的初始状态是错误的，但无论如何都不会使用。
 */
#define MBEDTLS_SSL_RETRANS_PREPARING       0
#define MBEDTLS_SSL_RETRANS_SENDING         1
#define MBEDTLS_SSL_RETRANS_WAITING         2
#define MBEDTLS_SSL_RETRANS_FINISHED        3

/*
 * 允许额外的字节用于记录、身份验证和加密开销：计数器（8）+标头（5）+IV（16）+MAC（16-48）+填充（0-256），如果启用，允许最大1024个压缩扩展。
 */
#if defined(MBEDTLS_ZLIB_SUPPORT)
#define MBEDTLS_SSL_COMPRESSION_ADD          1024
#else
#define MBEDTLS_SSL_COMPRESSION_ADD             0
#endif

/* 此宏确定是否支持CBC。*/
#if defined(MBEDTLS_CIPHER_MODE_CBC) &&                               \
    ( defined(MBEDTLS_AES_C)      ||                                  \
      defined(MBEDTLS_CAMELLIA_C) ||                                  \
      defined(MBEDTLS_ARIA_C)     ||                                  \
      defined(MBEDTLS_DES_C) )
#define MBEDTLS_SSL_SOME_SUITES_USE_CBC
#endif

/* 此宏确定是否支持TLS 1.0-1.2中使用的CBC构造（与SSLv3中使用的非常不同的CBC结构相反）。*/
#if defined(MBEDTLS_SSL_SOME_SUITES_USE_CBC) && \
    ( defined(MBEDTLS_SSL_PROTO_TLS1) ||        \
      defined(MBEDTLS_SSL_PROTO_TLS1_1) ||      \
      defined(MBEDTLS_SSL_PROTO_TLS1_2) )
#define MBEDTLS_SSL_SOME_SUITES_USE_TLS_CBC
#endif

#if defined(MBEDTLS_ARC4_C) || defined(MBEDTLS_CIPHER_NULL_CIPHER) ||   \
    defined(MBEDTLS_SSL_SOME_SUITES_USE_CBC)
#define MBEDTLS_SSL_SOME_MODES_USE_MAC
#endif

#if defined(MBEDTLS_SSL_SOME_MODES_USE_MAC)
/* 使用HMAC的密码套件*/
#if defined(MBEDTLS_SHA512_C)
#define MBEDTLS_SSL_MAC_ADD                 48  /* 用于HMAC的SHA-384*/
#elif defined(MBEDTLS_SHA256_C)
#define MBEDTLS_SSL_MAC_ADD                 32  /* SHA-256用于HMAC*/
#else
#define MBEDTLS_SSL_MAC_ADD                 20  /* 用于HMAC的SHA-1*/
#endif
#else /* MBEDTLS_SSL_SOME_MODES_USE_MAC */
/* AEAD密码套件：GCM和CCM使用128位标签*/
#define MBEDTLS_SSL_MAC_ADD                 16
#endif

#if defined(MBEDTLS_CIPHER_MODE_CBC)
#define MBEDTLS_SSL_PADDING_ADD            256
#else
#define MBEDTLS_SSL_PADDING_ADD              0
#endif

#if defined(MBEDTLS_SSL_DTLS_CONNECTION_ID)
#define MBEDTLS_SSL_MAX_CID_EXPANSION      MBEDTLS_SSL_CID_PADDING_GRANULARITY
#else
#define MBEDTLS_SSL_MAX_CID_EXPANSION        0
#endif

#define MBEDTLS_SSL_PAYLOAD_OVERHEAD ( MBEDTLS_SSL_COMPRESSION_ADD +    \
                                       MBEDTLS_MAX_IV_LENGTH +          \
                                       MBEDTLS_SSL_MAC_ADD +            \
                                       MBEDTLS_SSL_PADDING_ADD +        \
                                       MBEDTLS_SSL_MAX_CID_EXPANSION    \
                                       )

#define MBEDTLS_SSL_IN_PAYLOAD_LEN ( MBEDTLS_SSL_PAYLOAD_OVERHEAD + \
                                     ( MBEDTLS_SSL_IN_CONTENT_LEN ) )

#define MBEDTLS_SSL_OUT_PAYLOAD_LEN ( MBEDTLS_SSL_PAYLOAD_OVERHEAD + \
                                      ( MBEDTLS_SSL_OUT_CONTENT_LEN ) )

/* 缓冲握手消息的最大数量。*/
#define MBEDTLS_SSL_MAX_BUFFERED_HS 4

/* 为了RFC 6066 max_fragment_length扩展协商的目的，我们可以公布的最大长度为最大内容长度（如果两个大小不相等，则以较小的为准）
 */
#define MBEDTLS_TLS_EXT_ADV_CONTENT_LEN (                            \
        (MBEDTLS_SSL_IN_CONTENT_LEN > MBEDTLS_SSL_OUT_CONTENT_LEN)   \
        ? ( MBEDTLS_SSL_OUT_CONTENT_LEN )                            \
        : ( MBEDTLS_SSL_IN_CONTENT_LEN )                             \
        )

/* sig哈希算法扩展中列表的最大大小（字节），RFC 5246*/
#define MBEDTLS_SSL_MAX_SIG_HASH_ALG_LIST_LEN  65534

/* 支持的椭圆曲线扩展中列表的最大大小（字节），RFC 4492*/
#define MBEDTLS_SSL_MAX_CURVE_LIST_LEN         65535

/*
 * 检查我们是否遵守标准的消息大小限制
 */

#if MBEDTLS_SSL_MAX_CONTENT_LEN > 16384
#error "Bad configuration - record content too large."
#endif

#if MBEDTLS_SSL_IN_CONTENT_LEN > MBEDTLS_SSL_MAX_CONTENT_LEN
#error "Bad configuration - incoming record content should not be larger than MBEDTLS_SSL_MAX_CONTENT_LEN."
#endif

#if MBEDTLS_SSL_OUT_CONTENT_LEN > MBEDTLS_SSL_MAX_CONTENT_LEN
#error "Bad configuration - outgoing record content should not be larger than MBEDTLS_SSL_MAX_CONTENT_LEN."
#endif

#if MBEDTLS_SSL_IN_PAYLOAD_LEN > MBEDTLS_SSL_MAX_CONTENT_LEN + 2048
#error "Bad configuration - incoming protected record payload too large."
#endif

#if MBEDTLS_SSL_OUT_PAYLOAD_LEN > MBEDTLS_SSL_MAX_CONTENT_LEN + 2048
#error "Bad configuration - outgoing protected record payload too large."
#endif

/* 计算缓冲区大小*/

/* 注意：尽管TLS记录头只有5个字节长，但我们在内部使用8个字节来存储隐式序列号。*/
#define MBEDTLS_SSL_HEADER_LEN 13

#if !defined(MBEDTLS_SSL_DTLS_CONNECTION_ID)
#define MBEDTLS_SSL_IN_BUFFER_LEN  \
    ( ( MBEDTLS_SSL_HEADER_LEN ) + ( MBEDTLS_SSL_IN_PAYLOAD_LEN ) )
#else
#define MBEDTLS_SSL_IN_BUFFER_LEN  \
    ( ( MBEDTLS_SSL_HEADER_LEN ) + ( MBEDTLS_SSL_IN_PAYLOAD_LEN ) \
      + ( MBEDTLS_SSL_CID_IN_LEN_MAX ) )
#endif

#if !defined(MBEDTLS_SSL_DTLS_CONNECTION_ID)
#define MBEDTLS_SSL_OUT_BUFFER_LEN  \
    ( ( MBEDTLS_SSL_HEADER_LEN ) + ( MBEDTLS_SSL_OUT_PAYLOAD_LEN ) )
#else
#define MBEDTLS_SSL_OUT_BUFFER_LEN                               \
    ( ( MBEDTLS_SSL_HEADER_LEN ) + ( MBEDTLS_SSL_OUT_PAYLOAD_LEN )    \
      + ( MBEDTLS_SSL_CID_OUT_LEN_MAX ) )
#endif

#if defined(MBEDTLS_SSL_VARIABLE_BUFFER_LENGTH)
static inline uint32_t mbedtls_ssl_get_output_buflen( const mbedtls_ssl_context *ctx )
{
#if defined (MBEDTLS_SSL_DTLS_CONNECTION_ID)
    return (uint32_t) mbedtls_ssl_get_output_max_frag_len( ctx )
               + MBEDTLS_SSL_HEADER_LEN + MBEDTLS_SSL_PAYLOAD_OVERHEAD
               + MBEDTLS_SSL_CID_OUT_LEN_MAX;
#else
    return (uint32_t) mbedtls_ssl_get_output_max_frag_len( ctx )
               + MBEDTLS_SSL_HEADER_LEN + MBEDTLS_SSL_PAYLOAD_OVERHEAD;
#endif
}

static inline uint32_t mbedtls_ssl_get_input_buflen( const mbedtls_ssl_context *ctx )
{
#if defined (MBEDTLS_SSL_DTLS_CONNECTION_ID)
    return (uint32_t) mbedtls_ssl_get_input_max_frag_len( ctx )
               + MBEDTLS_SSL_HEADER_LEN + MBEDTLS_SSL_PAYLOAD_OVERHEAD
               + MBEDTLS_SSL_CID_IN_LEN_MAX;
#else
    return (uint32_t) mbedtls_ssl_get_input_max_frag_len( ctx )
               + MBEDTLS_SSL_HEADER_LEN + MBEDTLS_SSL_PAYLOAD_OVERHEAD;
#endif
}
#endif

#ifdef MBEDTLS_ZLIB_SUPPORT
/* 压缩缓冲区同时容纳IN和OUT缓冲区，所以大小应大于*/
#define MBEDTLS_SSL_COMPRESS_BUFFER_LEN (                               \
        ( MBEDTLS_SSL_IN_BUFFER_LEN > MBEDTLS_SSL_OUT_BUFFER_LEN )      \
        ? MBEDTLS_SSL_IN_BUFFER_LEN                                     \
        : MBEDTLS_SSL_OUT_BUFFER_LEN                                    \
        )
#endif

/*
 * TLS扩展标志（对于需要传出ServerHello内容的扩展（例如，对于RENEGOTIATION_INFO，由于重新协商标志的状态，服务器已经知道，因此不需要指示符）
 */
#define MBEDTLS_TLS_EXT_SUPPORTED_POINT_FORMATS_PRESENT (1 << 0)
#define MBEDTLS_TLS_EXT_ECJPAKE_KKPP_OK                 (1 << 1)

/**
 * \brief此函数检查缓冲区中的剩余大小是否大于或等于所需空间。
 *
 * \param cur指向缓冲区中当前位置的指针。\param end指向缓冲区末尾的指针。\param需要以字节为单位的所需空间。
 *
 * \如果缓冲区中有可用的空间，则返回零，否则返回非零。
 */
static inline int mbedtls_ssl_chk_buf_ptr( const uint8_t *cur,
                                           const uint8_t *end, size_t need )
{
    return( ( cur > end ) || ( need > (size_t)( end - cur ) ) );
}

/**
 * \brief此宏检查缓冲区中的剩余大小是否大于或等于所需空间。如果不是这样，则返回SSL_BUFFER_TOO_SMALL错误。
 *
 * \param cur指向缓冲区中当前位置的指针。\param end指向缓冲区末尾的指针。\param需要以字节为单位的所需空间。
 *
 */
#define MBEDTLS_SSL_CHK_BUF_PTR( cur, end, need )                        \
    do {                                                                 \
        if( mbedtls_ssl_chk_buf_ptr( ( cur ), ( end ), ( need ) ) != 0 ) \
        {                                                                \
            return( MBEDTLS_ERR_SSL_BUFFER_TOO_SMALL );                  \
        }                                                                \
    } while( 0 )

#ifdef __cplusplus
extern "C" {
#endif

#if defined(MBEDTLS_SSL_PROTO_TLS1_2) && \
    defined(MBEDTLS_KEY_EXCHANGE_WITH_CERT_ENABLED)
/*
 * 对允许的签名哈希算法对的网格进行抽象。
 */
struct mbedtls_ssl_sig_hash_set_t
{
    /* 目前，我们只需要记住每个签名算法一个合适的哈希算法。只要是这种情况-我们不需要通用的查找函数-我们就可以将sig哈希集实现为从签名到哈希算法的映射。*/
    mbedtls_md_type_t rsa;
    mbedtls_md_type_t ecdsa;
};
#endif /* MBEDTLS_SSL_PROTO_TLS1_2 && MBEDTLS_KEY_EXCHANGE_WITH_CERT_ENABLED */

typedef int  mbedtls_ssl_tls_prf_cb( const unsigned char *secret, size_t slen,
                                     const char *label,
                                     const unsigned char *random, size_t rlen,
                                     unsigned char *dstbuf, size_t dlen );

/* 密码h从配置中启用的所有密码导出最大IV、密钥和块长度，而不管这些密码是否在SSL/TLS中实际可用。值得注意的是，XTS在默认配置中启用，并使用64字节密钥，但它不用于SSL/TLS中的记录保护。
 *
 * 为了防止不必要的密钥结构膨胀，我们在这里引入了max-{key，block，IV}宏的SSL特定变体，这意味着只考虑那些可以在SSL/TLS中协商的密码。
 *
 * 由于当前密码中MBEDTLS_MAX_{KEY|BLOCK|IV}_LENGTH的定义。h是真实最大值的粗略过度近似，这里我们满足于复制最大块和IV长度的过度近似，并从最大密钥长度的计算中排除XTS。*/
#define MBEDTLS_SSL_MAX_BLOCK_LENGTH 16
#define MBEDTLS_SSL_MAX_IV_LENGTH    16
#define MBEDTLS_SSL_MAX_KEY_LENGTH   32

/**
 * \brief保存TLS 1.3中用于记录保护的加密材料（密钥和IV）的数据结构。
 */
struct mbedtls_ssl_key_set
{
    /*! 客户端->服务器记录的密钥。*/
    unsigned char client_write_key[ MBEDTLS_SSL_MAX_KEY_LENGTH ];
    /*! 服务器->客户端记录的密钥。*/
    unsigned char server_write_key[ MBEDTLS_SSL_MAX_KEY_LENGTH ];
    /*! 客户端->服务器记录的IV。*/
    unsigned char client_write_iv[ MBEDTLS_SSL_MAX_IV_LENGTH ];
    /*! 服务器->客户端记录的IV。*/
    unsigned char server_write_iv[ MBEDTLS_SSL_MAX_IV_LENGTH ];

    size_t key_len; /*!< client_write_key和server_write_key的长度，以字节为单位。*/
    size_t iv_len;  /*!< client_write_inv和server_write_iniv的长度（以字节为单位）。*/
};
typedef struct mbedtls_ssl_key_set mbedtls_ssl_key_set;

/*
 * 此结构包含仅在握手期间需要的参数。
 */
struct mbedtls_ssl_handshake_params
{
    /*
     * 特定于握手的加密变量
     */

#if defined(MBEDTLS_SSL_PROTO_TLS1_2) && \
    defined(MBEDTLS_KEY_EXCHANGE_WITH_CERT_ENABLED)
    mbedtls_ssl_sig_hash_set_t hash_algs;             /*!<  一组合适的sig哈希对*/
#endif
#if defined(MBEDTLS_DHM_C)
    mbedtls_dhm_context dhm_ctx;                /*!<  DHM密钥交换*/
#endif
/* 为MBEDTLS_ECDSA_C添加保护，以确保由于ssl_srv中也存在保护，因此不会出现编译错误。c和ssl_cli.c在功能上存在差距，MBEDTLS_ECDSA_c需要访问ecdh_ctx结构，这似乎不正确。
 */
#if defined(MBEDTLS_ECDH_C) || defined(MBEDTLS_ECDSA_C)
    mbedtls_ecdh_context ecdh_ctx;              /*!<  ECDH密钥交换*/

#if defined(MBEDTLS_USE_PSA_CRYPTO)
    psa_key_type_t ecdh_psa_type;
    uint16_t ecdh_bits;
    psa_key_id_t ecdh_psa_privkey;
    unsigned char ecdh_psa_peerkey[MBEDTLS_PSA_MAX_EC_PUBKEY_LENGTH];
    size_t ecdh_psa_peerkey_len;
#endif /* MBEDTLS_USE_PSA_CRYPTO */
#endif /* MBEDTLS_ECDH_C || MBEDTLS_ECDSA_C */

#if defined(MBEDTLS_KEY_EXCHANGE_ECJPAKE_ENABLED)
    mbedtls_ecjpake_context ecjpake_ctx;        /*!< EC J-PAKE密钥交换*/
#if defined(MBEDTLS_SSL_CLI_C)
    unsigned char *ecjpake_cache;               /*!< ClientHello ext的缓存*/
    size_t ecjpake_cache_len;                   /*!< 缓存数据的长度*/
#endif
#endif /* MBEDTLS_KEY_EXCHANGE_ECJPAKE_ENABLED */
#if defined(MBEDTLS_ECDH_C) || defined(MBEDTLS_ECDSA_C) || \
    defined(MBEDTLS_KEY_EXCHANGE_ECJPAKE_ENABLED)
    const mbedtls_ecp_curve_info **curves;      /*!<  支持的椭圆曲线*/
#endif
#if defined(MBEDTLS_KEY_EXCHANGE_SOME_PSK_ENABLED)
#if defined(MBEDTLS_USE_PSA_CRYPTO)
    psa_key_id_t psk_opaque;            /*!< 回调中的不透明PSK*/
#endif /* MBEDTLS_USE_PSA_CRYPTO */
    unsigned char *psk;                 /*!<  来自回调的PSK*/
    size_t psk_len;                     /*!<  回调的PSK长度*/
#endif /* MBEDTLS_KEY_EXCHANGE_SOME_PSK_ENABLED */
#if defined(MBEDTLS_X509_CRT_PARSE_C)
    mbedtls_ssl_key_cert *key_cert;     /*!< 所选密钥/证书对（服务器）*/
#if defined(MBEDTLS_SSL_SERVER_NAME_INDICATION)
    int sni_authmode;                   /*!< SNI回调的authmode*/
    mbedtls_ssl_key_cert *sni_key_cert; /*!< SNI的密钥/证书列表*/
    mbedtls_x509_crt *sni_ca_chain;     /*!< 来自SNI回调的受信任CA*/
    mbedtls_x509_crl *sni_ca_crl;       /*!< 来自SNI的可信CA CRL*/
#endif /* MBEDTLS_SSL_SERVER_NAME_INDICATION */
#endif /* MBEDTLS_X509_CRT_PARSE_C */
#if defined(MBEDTLS_SSL_ECP_RESTARTABLE_ENABLED)
    int ecrs_enabled;                   /*!< 握手支持EC重启？*/
    mbedtls_x509_crt_restart_ctx ecrs_ctx;  /*!< 重新启动上下文*/
    enum { /* 这补充了ssl->state与状态内操作的信息*/
        ssl_ecrs_none = 0,              /*!< 还没发生什么事*/
        ssl_ecrs_crt_verify,            /*!< 证书：crt_verify（）*/
        ssl_ecrs_ske_start_processing,  /*!< 服务器密钥交换：pk_verify（）*/
        ssl_ecrs_cke_ecdh_calc_secret,  /*!< ClientKeyExchange:ECDH步骤2*/
        ssl_ecrs_crt_vrfy_sign,         /*!< 证书验证：pk_sign（）*/
    } ecrs_state;                       /*!< 当前（或最后）操作*/
    mbedtls_x509_crt *ecrs_peer_cert;   /*!< 同行的CRT链。*/
    size_t ecrs_n;                      /*!< 保存长度的位置*/
#endif
#if defined(MBEDTLS_X509_CRT_PARSE_C) && \
    !defined(MBEDTLS_SSL_KEEP_PEER_CERTIFICATE)
    mbedtls_pk_context peer_pubkey;     /*!< 来自对等方的公钥。*/
#endif /* MBEDTLS_X509_CRT_PARSE_C && !MBEDTLS_SSL_KEEP_PEER_CERTIFICATE */
#if defined(MBEDTLS_SSL_PROTO_DTLS)
    unsigned int out_msg_seq;           /*!<  传出握手序列号*/
    unsigned int in_msg_seq;            /*!<  传入握手序列号*/

    unsigned char *verify_cookie;       /*!<  Cli:HelloVerifyRequest cookie Srv:未使用*/
    unsigned char verify_cookie_len;    /*!<  Cli:cookie length Srv：发送cookie的标志*/

    uint32_t retransmit_timeout;        /*!<  当前超时值*/
    unsigned char retransmit_state;     /*!<  重新传输状态*/
    mbedtls_ssl_flight_item *flight;    /*!<  当前外出航班*/
    mbedtls_ssl_flight_item *cur_msg;   /*!<  飞行中的当前消息*/
    unsigned char *cur_msg_p;           /*!<  当前消息中的位置*/
    unsigned int in_flight_start_seq;   /*!<  正在接收的航班中的最小消息序列*/
    mbedtls_ssl_transform *alt_transform_out;   /*!<  用于重新发送消息的替代转换*/
    unsigned char alt_out_ctr[8];       /*!<  用于重新发送消息的备用记录历元/计数器*/

#if defined(MBEDTLS_SSL_DTLS_CONNECTION_ID)
    /* 此握手中CID配置的状态。*/

    uint8_t cid_in_use; /*!< 这表明CID扩展的使用是否已协商。可能的值为#MBEDTLS_SL_CID_ENABLED和#MBEDLLS_SL_CID _DISABLED。*/
    unsigned char peer_cid[ MBEDTLS_SSL_CID_OUT_LEN_MAX ]; /*! 同行的CID*/
    uint8_t peer_cid_len;                                  /*!< *\c peer_cid的长度。*/
#endif /* MBEDTLS_SSL_DTLS_CONNECTION_ID */

    struct
    {
        size_t total_bytes_buffered; /*!< 用于消息缓冲的堆分配缓冲区的累积大小。*/

        uint8_t seen_ccs;               /*!< 指示当前航班中是否出现CCS信息。*/

        struct mbedtls_ssl_hs_buffer
        {
            unsigned is_valid      : 1;
            unsigned is_fragmented : 1;
            unsigned is_complete   : 1;
            unsigned char *data;
            size_t data_len;
        } hs[MBEDTLS_SSL_MAX_BUFFERED_HS];

        struct
        {
            unsigned char *data;
            size_t len;
            unsigned epoch;
        } future_record;

    } buffering;

    uint16_t mtu;                       /*!<  握手mtu，用于分割传出消息*/
#endif /* MBEDTLS_SSL_PROTO_DTLS */

    /*
     * 校验和上下文
     */
#if defined(MBEDTLS_SSL_PROTO_SSL3) || defined(MBEDTLS_SSL_PROTO_TLS1) || \
    defined(MBEDTLS_SSL_PROTO_TLS1_1)
       mbedtls_md5_context fin_md5;
      mbedtls_sha1_context fin_sha1;
#endif
#if defined(MBEDTLS_SSL_PROTO_TLS1_2)
#if defined(MBEDTLS_SHA256_C)
#if defined(MBEDTLS_USE_PSA_CRYPTO)
    psa_hash_operation_t fin_sha256_psa;
#else
    mbedtls_sha256_context fin_sha256;
#endif
#endif
#if defined(MBEDTLS_SHA512_C)
#if defined(MBEDTLS_USE_PSA_CRYPTO)
    psa_hash_operation_t fin_sha384_psa;
#else
    mbedtls_sha512_context fin_sha512;
#endif
#endif
#endif /* MBEDTLS_SSL_PROTO_TLS1_2 */

    void (*update_checksum)(mbedtls_ssl_context *, const unsigned char *, size_t);
    void (*calc_verify)(const mbedtls_ssl_context *, unsigned char *, size_t *);
    void (*calc_finished)(mbedtls_ssl_context *, unsigned char *, int);
    mbedtls_ssl_tls_prf_cb *tls_prf;

    mbedtls_ssl_ciphersuite_t const *ciphersuite_info;

    size_t pmslen;                      /*!<  母体前长度*/

    unsigned char randbytes[64];        /*!<  随机字节*/
    unsigned char premaster[MBEDTLS_PREMASTER_SIZE];
                                        /*!<  婚前秘密*/

    int resume;                         /*!<  会话恢复指示器*/
    int max_major_ver;                  /*!< 最大主版本客户端*/
    int max_minor_ver;                  /*!< 最大次要版本客户端*/
    int cli_exts;                       /*!< 客户端扩展存在*/

#if defined(MBEDTLS_SSL_SESSION_TICKETS)
    int new_session_ticket;             /*!< 使用NewSessionTicket？*/
#endif /* MBEDTLS_SSL_SESSION_TICKETS */
#if defined(MBEDTLS_SSL_EXTENDED_MASTER_SECRET)
    int extended_ms;                    /*!< 使用扩展主密钥？*/
#endif

#if defined(MBEDTLS_SSL_ASYNC_PRIVATE)
    unsigned int async_in_progress : 1; /*!< 正在进行异步操作*/
#endif /* MBEDTLS_SSL_ASYNC_PRIVATE */

#if defined(MBEDTLS_SSL_ASYNC_PRIVATE)
    /**异步操作上下文。此字段用于异步操作回调（mbedtls_ssl_config:：f_async_sign_start，mbedtls_ssl_config：：f_aync_decrypt_start，mbedtls _ssl_connfig:：f-async_resume，mbedt尔斯_ssl_conconfig:：f_sync_cancel）。库不在内部使用它。*/
    void *user_async_ctx;
#endif /* MBEDTLS_SSL_ASYNC_PRIVATE */
};

typedef struct mbedtls_ssl_hs_buffer mbedtls_ssl_hs_buffer;

/*
 * 记录上解密/加密转换的表示
 *
 * 记录转换的一般类型如下：
 * -流转换（仅TLS版本<=1.2）添加MAC并将流密码应用于已验证消息的转换。
 * -CBC分组密码转换（[D]TLS版本仅<=1.2）除了加密和身份验证顺序的区别之外，SSL3和TLS 1.0以及TLS 1.1和TLS 1.2中的处理存在根本区别：对于SSL3和TLS1.0，处理记录后的最终IV将用作下一条记录的IV。加密记录中不包含明确的IV。在密钥提取时间提取第一条记录的IV。相反，对于TLS 1.1和1.2，在密钥提取时不生成IV，但每个加密记录都以加密时使用的IV作为前缀。
 * -AEAD转换（[D]TLS版本>=1.2）有两个根本不同的版本，第一个用于TLS 1.2（不包括ChaChaPoly密码套件），第二个用于TLS 1.3和TLS 1.2中的ChaChaPoly密码套件，静态4字节IV和8字节记录序列号，并将该序列号明确地加在加密记录之前。相反，在第二次转换中，IV是通过将在密钥提取时获得的静态IV与8字节记录序列号进行XOR而获得的，而不将后者前置于加密记录。
 *
 * 此外，DTLS 1.2+CID以及TLS 1.3使用内部明文，允许添加灵活的长度填充并隐藏记录的真实内容类型。
 *
 * 除类型和版本外，以下参数也相关：
 * -要使用的对称密码算法。
 * -密码的（静态）加密/解密密钥。
 * -对于流/CBC，要使用的消息摘要类型。
 * -对于流/CBC，摘要的（静态）加密/解密密钥。
 * -对于AEAD转换，放置在加密记录中的显式随机初始化向量的大小（可能为0）。
 * -对于某些转换（当前SSL3和TLS 1.0中的AEAD和CBC），隐式IV可以是静态的（例如AEAD）或动态的（例如CBC）并且（如果存在）以转换相关的方式与显式IV组合（例如TLS 1.2中的附加和TLS 1.3中的异或）。
 * -对于流/CBC，一种确定加密和MAC顺序的标志。
 * -转换的详细信息取决于SSL/TLS版本。
 * -身份验证标签的长度。
 *
 * 注意：除了SSL3和TLS 1.0中的CBC之外，这些参数在多个加密/解密操作中是恒定的。对于CBC，隐式IV需要在每次操作后更新。
 *
 * 下面的结构将此抽象视图细化如下：
 * -转换背后的密码在密码上下文cipher_ctx_{enc/dec}中管理，该上下文必须具有相同的密码类型。这些密码上下文的模式决定了上述意义上的转换类型：例如，如果类型为MBEDTLS_cipher_AES_256_CBC。MBEDTLS_CIPHER_AES_192_GCM，则转换的类型为CBC resp。AEAD。
 * -密码密钥从不显式存储，而是保存在cipher_ctx_{enc/dec}中。
 * -对于流/CBC转换，用于MAC的消息摘要上下文存储在md_ctx_{enc/dec}中。这些上下文不用于AEAD转换。
 * -对于流/CBC转换和版本>SSL3，MAC密钥不显式存储，而是在md_ctx_{enc/dec}中维护。
 * -对于流/CBC转换和版本SSL3，MAC密钥显式存储在MAC_enc、MAC_dec中，并具有20字节的固定大小。这些字段不用于AEAD转换或>=TLS 1.0的转换。
 * -对于使用在转换上下文中维护的隐式IV的转换，其内容存储在IV_{enc/dec}中。
 * -ivlen的值表示IV的长度。对于始终使用0 resp的流/CBC转换，这是多余的。但是对于AEAD密码是需要的，并且在这种情况下可能不同于基础密码的块长度。
 * -字段fixed_vlen仅对于AEAD变换是非零的，并且指示IV的静态部分的长度，该长度在整个通信过程中是恒定的，并且存储在IV_{enc/dec}数组的第一个fixed_vLen字节中。注意：对于SSL3和TLS 1.0中的CBC，字段iv_{enc/dec}仍然存储iv，以便在多个转换中继续使用，因此fixed_vlen==0并不意味着iv_{enc/dec}没有被使用！
 * -minor_ver表示SSL/TLS版本
 * -对于流/CBC转换，maclen表示身份验证标记的长度，而taglen是未使用的，为0。
 * -对于AEAD转换，taglen表示身份验证标记的长度，而maclen是未使用的，为0。
 * -对于CBC转换，encrypt_then_mac决定加密和身份验证的顺序。此字段在其他转换中未使用。
 *
 */
struct mbedtls_ssl_transform
{
    /*
     * 会话特定加密层
     */
    size_t minlen;                      /*!<  最小密文长度*/
    size_t ivlen;                       /*!<  IV长度*/
    size_t fixed_ivlen;                 /*!<  IV固定部分（AEAD）*/
    size_t maclen;                      /*!<  MAC（CBC）长度*/
    size_t taglen;                      /*!<  标签（AEAD）长度*/

    unsigned char iv_enc[16];           /*!<  IV（加密）*/
    unsigned char iv_dec[16];           /*!<  IV（解密）*/

#if defined(MBEDTLS_SSL_SOME_MODES_USE_MAC)

#if defined(MBEDTLS_SSL_PROTO_SSL3)
    /* 仅SSL v3.0 secret需要*/
    unsigned char mac_enc[20];          /*!<  SSL v3.0机密（enc）*/
    unsigned char mac_dec[20];          /*!<  SSL v3.0机密（dec）*/
#endif /* MBEDTLS_SSL_PROTO_SSL3 */

    mbedtls_md_context_t md_ctx_enc;            /*!<  MAC（加密）*/
    mbedtls_md_context_t md_ctx_dec;            /*!<  MAC（解密）*/

#if defined(MBEDTLS_SSL_ENCRYPT_THEN_MAC)
    int encrypt_then_mac;       /*!< EtM激活标志*/
#endif

#endif /* MBEDTLS_SSL_SOME_MODES_USE_MAC */

    mbedtls_cipher_context_t cipher_ctx_enc;    /*!<  加密上下文*/
    mbedtls_cipher_context_t cipher_ctx_dec;    /*!<  解密上下文*/
    int minor_ver;

#if defined(MBEDTLS_SSL_DTLS_CONNECTION_ID)
    uint8_t in_cid_len;
    uint8_t out_cid_len;
    unsigned char in_cid [ MBEDTLS_SSL_CID_OUT_LEN_MAX ];
    unsigned char out_cid[ MBEDTLS_SSL_CID_OUT_LEN_MAX ];
#endif /* MBEDTLS_SSL_DTLS_CONNECTION_ID */

    /*
     * 会话特定压缩层
     */
#if defined(MBEDTLS_ZLIB_SUPPORT)
    z_stream ctx_deflate;               /*!<  压缩上下文*/
    z_stream ctx_inflate;               /*!<  解压缩上下文*/
#endif

#if defined(MBEDTLS_SSL_CONTEXT_SERIALIZATION)
    /* 我们需要Hello随机字节，以便从Master Secret和其他会话信息中重新派生密钥，请参阅ssl_popuple_transform（）*/
    unsigned char randbytes[64]; /*!< 服务器你好。随机+客户端你好。随机的*/
#endif /* MBEDTLS_SSL_CONTEXT_SERIALIZATION */
};

/*
 * 如果转换使用AEAD密码，则返回1，否则返回0。等效地，如果使用单独的MAC，则返回0，否则返回1。
 */
static inline int mbedtls_ssl_transform_uses_aead(
        const mbedtls_ssl_transform *transform )
{
#if defined(MBEDTLS_SSL_SOME_MODES_USE_MAC)
    return( transform->maclen == 0 && transform->taglen != 0 );
#else
    (void) transform;
    return( 1 );
#endif
}

/*
 * 记录帧的内部表示
 *
 * 实例有两种类型：（1）加密的这些始终具有data_offset=0（2）未加密的这些将data_offset设置为记录保护期间的预扩展量。具体而言，这是用于加密的显式IV的固定部分的长度，如果没有使用显式IV（例如，TLS 1.0中的CBC或流密码），则为0。
 *
 * 在未加密情况下使用data_offset的原因是允许将未加密记录就地转换为加密记录。如果不包括偏移量，加密内容将需要在之后移动，以便为固定的IV腾出空间。
 *
 */
#if MBEDTLS_SSL_CID_OUT_LEN_MAX > MBEDTLS_SSL_CID_IN_LEN_MAX
#define MBEDTLS_SSL_CID_LEN_MAX MBEDTLS_SSL_CID_OUT_LEN_MAX
#else
#define MBEDTLS_SSL_CID_LEN_MAX MBEDTLS_SSL_CID_IN_LEN_MAX
#endif

typedef struct
{
    uint8_t ctr[8];         /* 在TLS中：隐式记录序列号。在DTLS中：2字节的历元，后跟6字节的序列号。与uint64_t相反，这是作为原始大端字节数组存储的，因为我们很少需要对此执行算术运算，但出于MAC计算的目的，确实需要将其作为字节数组。*/
    uint8_t type;           /* 记录内容类型。*/
    uint8_t ver[2];         /* 电线上的SSL/TLS版本。使用mbedtls_ssl_read_version（）和mbedtls_ssl_write_version）转换为版本的内部表示形式。保留MAC计算的有线格式。*/

    unsigned char *buf;     /* 包含记录内容的内存缓冲区*/
    size_t buf_len;         /* 缓冲区长度*/
    size_t data_offset;     /* 记录内容的偏移*/
    size_t data_len;        /* 记录内容长度*/

#if defined(MBEDTLS_SSL_DTLS_CONNECTION_ID)
    uint8_t cid_len;        /* CID的长度（如果不存在，则为0）*/
    unsigned char cid[ MBEDTLS_SSL_CID_LEN_MAX ]; /* CID*/
#endif /* MBEDTLS_SSL_DTLS_CONNECTION_ID */
} mbedtls_record;

#if defined(MBEDTLS_X509_CRT_PARSE_C)
/*
 * 证书+私钥对列表
 */
struct mbedtls_ssl_key_cert
{
    mbedtls_x509_crt *cert;                 /*!< 证书*/
    mbedtls_pk_context *key;                /*!< 私钥*/
    mbedtls_ssl_key_cert *next;             /*!< 下一密钥/证书对*/
};
#endif /* MBEDTLS_X509_CRT_PARSE_C */

#if defined(MBEDTLS_SSL_PROTO_DTLS)
/*
 * 保留用于重新发送的握手消息列表
 */
struct mbedtls_ssl_flight_item
{
    unsigned char *p;       /*!< 消息，包括握手标头*/
    size_t len;             /*!< p的长度*/
    unsigned char type;     /*!< 消息类型：握手或CCS*/
    mbedtls_ssl_flight_item *next;  /*!< 下一个握手消息*/
};
#endif /* MBEDTLS_SSL_PROTO_DTLS */

#if defined(MBEDTLS_SSL_PROTO_TLS1_2) && \
    defined(MBEDTLS_KEY_EXCHANGE_WITH_CERT_ENABLED)

/* 在签名哈希集中查找与给定哈希算法匹配的条目。*/
mbedtls_md_type_t mbedtls_ssl_sig_hash_set_find( mbedtls_ssl_sig_hash_set_t *set,
                                                 mbedtls_pk_type_t sig_alg );
/* 将签名哈希对添加到签名哈希集*/
void mbedtls_ssl_sig_hash_set_add( mbedtls_ssl_sig_hash_set_t *set,
                                   mbedtls_pk_type_t sig_alg,
                                   mbedtls_md_type_t md_alg );
/* 每个签名只允许一个哈希算法。*/
void mbedtls_ssl_sig_hash_set_const_hash( mbedtls_ssl_sig_hash_set_t *set,
                                          mbedtls_md_type_t md_alg );

/* 设置空签名哈希集*/
static inline void mbedtls_ssl_sig_hash_set_init( mbedtls_ssl_sig_hash_set_t *set )
{
    mbedtls_ssl_sig_hash_set_const_hash( set, MBEDTLS_MD_NONE );
}

#endif /* MBEDTLS_SSL_PROTO_TLS1_2) && MBEDTLS_KEY_EXCHANGE_WITH_CERT_ENABLED */

/**
 * \brief释放SSL转换上下文中的引用项并清除内存
 *
 * \param转换SSL转换上下文
 */
void mbedtls_ssl_transform_free( mbedtls_ssl_transform *transform );

/**
 * \brief在SSL握手上下文中释放引用项并清除内存
 *
 * \param ssl ssl上下文
 */
void mbedtls_ssl_handshake_free( mbedtls_ssl_context *ssl );

int mbedtls_ssl_handshake_client_step( mbedtls_ssl_context *ssl );
int mbedtls_ssl_handshake_server_step( mbedtls_ssl_context *ssl );
void mbedtls_ssl_handshake_wrapup( mbedtls_ssl_context *ssl );

int mbedtls_ssl_send_fatal_handshake_failure( mbedtls_ssl_context *ssl );

void mbedtls_ssl_reset_checksum( mbedtls_ssl_context *ssl );
int mbedtls_ssl_derive_keys( mbedtls_ssl_context *ssl );

int mbedtls_ssl_handle_message_type( mbedtls_ssl_context *ssl );
int mbedtls_ssl_prepare_handshake_record( mbedtls_ssl_context *ssl );
void mbedtls_ssl_update_handshake_status( mbedtls_ssl_context *ssl );

/**
 * \brief更新记录层
 *
 *              此函数大致将（D）TLS逻辑的实现与安全传输的实现分开。
 *
 * \param ssl要使用的ssl上下文。\param update_hs_digest这指示在发现握手消息时是否应自动更新握手摘要。
 *
 * \返回0或非零错误代码。
 *
 * \注意：这里对所谓的“记录层”进行了澄清，尽可能多的合理定义：
 *
 *              记录层将不受信任的底层传输（流或数据报）作为输入，并将其转换为串行复用的安全传输，概念上提供了以下内容：
 *
 *              （1） 三种基于数据报、内容不可知的握手、警报和CCS消息传输。（2） 应用程序数据的一个基于流或数据报的传输。（3） 用于更改保护内容的基础转换的功能。
 *
 *              此功能的接口如下所示：
 *
 *              a更新[当前由mbedtls_ssl_read_record]实现
 *
 *                检查四个“端口”数据中的哪一个是否处于挂起状态：Nothing、类型（1）的控制数据报或应用程序数据（2）。在任何情况下，数据都存在，内部缓冲区为用户提供对数据的访问以处理数据。类型（1）数据报的消耗在下一次更新时自动完成，使先前数据报的内部缓冲区无效，而应用程序数据（2）的消耗由用户控制。
 *
 *              b读取应用程序数据[当前手动调整ssl->in_offt指针]
 *
 *                如上一段所述，数据的消耗与控制数据报（1）的自动消耗不同，因为应用数据被视为流。
 *
 *              c跟踪应用程序数据的可用性[当前通过减少ssl->in_msglen]
 *
 *                为了提高效率并在DTLS的情况下保留应用数据的数据报语义，记录层提供了检查内部缓冲区中仍有多少应用数据可用的功能。
 *
 *              d更改通信安全的转换。
 *
 *              鉴于记录层在上述意义上的不透明实现，应该可以在其之上实现（D）TLS的逻辑，而不需要了解记录层的内部结构。这例如在所有握手处理函数和应用数据读取函数mbedtls_ssl_read中完成。
 *
 * \注意：上面试图给出记录层的概念图，但当前的实现在某些地方与之不同。例如，我们通过mbedtls_ssl_read_record实现的更新功能会根据当前状态丢弃数据报，而根据上述定义，数据报不属于记录层的责任。
 *
 */
int mbedtls_ssl_read_record( mbedtls_ssl_context *ssl,
                             unsigned update_hs_digest );
int mbedtls_ssl_fetch_input( mbedtls_ssl_context *ssl, size_t nb_want );

int mbedtls_ssl_write_handshake_msg( mbedtls_ssl_context *ssl );
int mbedtls_ssl_write_record( mbedtls_ssl_context *ssl, uint8_t force_flush );
int mbedtls_ssl_flush_output( mbedtls_ssl_context *ssl );

int mbedtls_ssl_parse_certificate( mbedtls_ssl_context *ssl );
int mbedtls_ssl_write_certificate( mbedtls_ssl_context *ssl );

int mbedtls_ssl_parse_change_cipher_spec( mbedtls_ssl_context *ssl );
int mbedtls_ssl_write_change_cipher_spec( mbedtls_ssl_context *ssl );

int mbedtls_ssl_parse_finished( mbedtls_ssl_context *ssl );
int mbedtls_ssl_write_finished( mbedtls_ssl_context *ssl );

void mbedtls_ssl_optimize_checksum( mbedtls_ssl_context *ssl,
                            const mbedtls_ssl_ciphersuite_t *ciphersuite_info );

#if defined(MBEDTLS_KEY_EXCHANGE_SOME_PSK_ENABLED)
int mbedtls_ssl_psk_derive_premaster( mbedtls_ssl_context *ssl, mbedtls_key_exchange_type_t key_ex );

/**
 * 按优先级顺序获取第一个定义的PSK：1.握手PSK由\c mbedtls_ssl_set_hs_PSK（）在PSK回调中设置2.静态PSK由\\c mbedtls_ssl_conf_PSK（（）配置返回代码并更新传递给此函数的对（PSK，PSK长度）
 */
static inline int mbedtls_ssl_get_psk( const mbedtls_ssl_context *ssl,
    const unsigned char **psk, size_t *psk_len )
{
    if( ssl->handshake->psk != NULL && ssl->handshake->psk_len > 0 )
    {
        *psk = ssl->handshake->psk;
        *psk_len = ssl->handshake->psk_len;
    }

    else if( ssl->conf->psk != NULL && ssl->conf->psk_len > 0 )
    {
        *psk = ssl->conf->psk;
        *psk_len = ssl->conf->psk_len;
    }

    else
    {
        *psk = NULL;
        *psk_len = 0;
        return( MBEDTLS_ERR_SSL_PRIVATE_KEY_REQUIRED );
    }

    return( 0 );
}

#if defined(MBEDTLS_USE_PSA_CRYPTO)
/**
 * 按优先级顺序获取第一个定义的不透明PSK：1.握手PSK由\c mbedtls_ssl_set_hs_PSK_opaque（）在PSK回调中设置2.静态PSK由\\c mbedtls_ssl_conf_PSK_opaque（）配置返回不透明PSK
 */
static inline psa_key_id_t mbedtls_ssl_get_opaque_psk(
    const mbedtls_ssl_context *ssl )
{
    if( ! mbedtls_svc_key_id_is_null( ssl->handshake->psk_opaque ) )
        return( ssl->handshake->psk_opaque );

    if( ! mbedtls_svc_key_id_is_null( ssl->conf->psk_opaque ) )
        return( ssl->conf->psk_opaque );

    return( MBEDTLS_SVC_KEY_ID_INIT );
}
#endif /* MBEDTLS_USE_PSA_CRYPTO */

#endif /* MBEDTLS_KEY_EXCHANGE_SOME_PSK_ENABLED */

#if defined(MBEDTLS_PK_C)
unsigned char mbedtls_ssl_sig_from_pk( mbedtls_pk_context *pk );
unsigned char mbedtls_ssl_sig_from_pk_alg( mbedtls_pk_type_t type );
mbedtls_pk_type_t mbedtls_ssl_pk_alg_from_sig( unsigned char sig );
#endif

mbedtls_md_type_t mbedtls_ssl_md_alg_from_hash( unsigned char hash );
unsigned char mbedtls_ssl_hash_from_md_alg( int md );
int mbedtls_ssl_set_calc_verify_md( mbedtls_ssl_context *ssl, int md );

#if defined(MBEDTLS_ECP_C)
int mbedtls_ssl_check_curve( const mbedtls_ssl_context *ssl, mbedtls_ecp_group_id grp_id );
#endif

#if defined(MBEDTLS_KEY_EXCHANGE_WITH_CERT_ENABLED)
int mbedtls_ssl_check_sig_hash( const mbedtls_ssl_context *ssl,
                                mbedtls_md_type_t md );
#endif

#if defined(MBEDTLS_SSL_DTLS_SRTP)
static inline mbedtls_ssl_srtp_profile mbedtls_ssl_check_srtp_profile_value
                                                    ( const uint16_t srtp_profile_value )
{
    switch( srtp_profile_value )
    {
        case MBEDTLS_TLS_SRTP_AES128_CM_HMAC_SHA1_80:
        case MBEDTLS_TLS_SRTP_AES128_CM_HMAC_SHA1_32:
        case MBEDTLS_TLS_SRTP_NULL_HMAC_SHA1_80:
        case MBEDTLS_TLS_SRTP_NULL_HMAC_SHA1_32:
            return srtp_profile_value;
        default: break;
    }
    return( MBEDTLS_TLS_SRTP_UNSET );
}
#endif

#if defined(MBEDTLS_X509_CRT_PARSE_C)
static inline mbedtls_pk_context *mbedtls_ssl_own_key( mbedtls_ssl_context *ssl )
{
    mbedtls_ssl_key_cert *key_cert;

    if( ssl->handshake != NULL && ssl->handshake->key_cert != NULL )
        key_cert = ssl->handshake->key_cert;
    else
        key_cert = ssl->conf->key_cert;

    return( key_cert == NULL ? NULL : key_cert->key );
}

static inline mbedtls_x509_crt *mbedtls_ssl_own_cert( mbedtls_ssl_context *ssl )
{
    mbedtls_ssl_key_cert *key_cert;

    if( ssl->handshake != NULL && ssl->handshake->key_cert != NULL )
        key_cert = ssl->handshake->key_cert;
    else
        key_cert = ssl->conf->key_cert;

    return( key_cert == NULL ? NULL : key_cert->cert );
}

/*
 * 检查证书相关扩展的用法：keyUsage、extendedKeyUsage（更高版本）和nSCertType（更高）。
 *
 * 警告：cert_endpoint是证书的端点（即，当我们检查从他们那里收到的证书时，我们的对等方的端点）！
 *
 * 如果一切正常，则返回0，否则返回-1。
 */
int mbedtls_ssl_check_cert_usage( const mbedtls_x509_crt *cert,
                          const mbedtls_ssl_ciphersuite_t *ciphersuite,
                          int cert_endpoint,
                          uint32_t *flags );
#endif /* MBEDTLS_X509_CRT_PARSE_C */

void mbedtls_ssl_write_version( int major, int minor, int transport,
                        unsigned char ver[2] );
void mbedtls_ssl_read_version( int *major, int *minor, int transport,
                       const unsigned char ver[2] );

static inline size_t mbedtls_ssl_in_hdr_len( const mbedtls_ssl_context *ssl )
{
#if !defined(MBEDTLS_SSL_PROTO_DTLS)
    ((void) ssl);
#endif

#if defined(MBEDTLS_SSL_PROTO_DTLS)
    if( ssl->conf->transport == MBEDTLS_SSL_TRANSPORT_DATAGRAM )
    {
        return( 13 );
    }
    else
#endif /* MBEDTLS_SSL_PROTO_DTLS */
    {
        return( 5 );
    }
}

static inline size_t mbedtls_ssl_out_hdr_len( const mbedtls_ssl_context *ssl )
{
    return( (size_t) ( ssl->out_iv - ssl->out_hdr ) );
}

static inline size_t mbedtls_ssl_hs_hdr_len( const mbedtls_ssl_context *ssl )
{
#if defined(MBEDTLS_SSL_PROTO_DTLS)
    if( ssl->conf->transport == MBEDTLS_SSL_TRANSPORT_DATAGRAM )
        return( 12 );
#else
    ((void) ssl);
#endif
    return( 4 );
}

#if defined(MBEDTLS_SSL_PROTO_DTLS)
void mbedtls_ssl_send_flight_completed( mbedtls_ssl_context *ssl );
void mbedtls_ssl_recv_flight_completed( mbedtls_ssl_context *ssl );
int mbedtls_ssl_resend( mbedtls_ssl_context *ssl );
int mbedtls_ssl_flight_transmit( mbedtls_ssl_context *ssl );
#endif

/* 仅用于测试目的可见*/
#if defined(MBEDTLS_SSL_DTLS_ANTI_REPLAY)
int mbedtls_ssl_dtls_replay_check( mbedtls_ssl_context const *ssl );
void mbedtls_ssl_dtls_replay_update( mbedtls_ssl_context *ssl );
#endif

int mbedtls_ssl_session_copy( mbedtls_ssl_session *dst,
                              const mbedtls_ssl_session *src );

/* 恒定时间缓冲比较*/
static inline int mbedtls_ssl_safer_memcmp( const void *a, const void *b, size_t n )
{
    size_t i;
    volatile const unsigned char *A = (volatile const unsigned char *) a;
    volatile const unsigned char *B = (volatile const unsigned char *) b;
    volatile unsigned char diff = 0;

    for( i = 0; i < n; i++ )
    {
        /* 在计算差异之前按顺序读取易失性数据。这避免了IAR编译器警告：“易失性访问的顺序未定义。”*/
        unsigned char x = A[i], y = B[i];
        diff |= x ^ y;
    }

    return( diff );
}

#if defined(MBEDTLS_SSL_PROTO_SSL3) || defined(MBEDTLS_SSL_PROTO_TLS1) || \
    defined(MBEDTLS_SSL_PROTO_TLS1_1)
int mbedtls_ssl_get_key_exchange_md_ssl_tls( mbedtls_ssl_context *ssl,
                                        unsigned char *output,
                                        unsigned char *data, size_t data_len );
#endif /* MBEDTLS_SSL_PROTO_SSL3 || MBEDTLS_SSL_PROTO_TLS1 || \ MBEDTLS_SSL_PROTO_TLS1_1 */

#if defined(MBEDTLS_SSL_PROTO_TLS1) || defined(MBEDTLS_SSL_PROTO_TLS1_1) || \
    defined(MBEDTLS_SSL_PROTO_TLS1_2)
/* 哈希缓冲区的长度必须至少为MBEDTLS_MD_MAX_SIZE字节。*/
int mbedtls_ssl_get_key_exchange_md_tls1_2( mbedtls_ssl_context *ssl,
                                            unsigned char *hash, size_t *hashlen,
                                            unsigned char *data, size_t data_len,
                                            mbedtls_md_type_t md_alg );
#endif /* MBEDTLS_SSL_PROTO_TLS1 || MBEDTLS_SSL_PROTO_TLS1_1 || \ MBEDTLS_SSL_PROTO_TLS1_2 */

#ifdef __cplusplus
}
#endif

void mbedtls_ssl_transform_init( mbedtls_ssl_transform *transform );
int mbedtls_ssl_encrypt_buf( mbedtls_ssl_context *ssl,
                             mbedtls_ssl_transform *transform,
                             mbedtls_record *rec,
                             int (*f_rng)(void *, unsigned char *, size_t),
                             void *p_rng );
int mbedtls_ssl_decrypt_buf( mbedtls_ssl_context const *ssl,
                             mbedtls_ssl_transform *transform,
                             mbedtls_record *rec );

/* 记录标题中“epoch”字段的长度*/
static inline size_t mbedtls_ssl_ep_len( const mbedtls_ssl_context *ssl )
{
#if defined(MBEDTLS_SSL_PROTO_DTLS)
    if( ssl->conf->transport == MBEDTLS_SSL_TRANSPORT_DATAGRAM )
        return( 2 );
#else
    ((void) ssl);
#endif
    return( 0 );
}

#if defined(MBEDTLS_SSL_PROTO_DTLS)
int mbedtls_ssl_resend_hello_request( mbedtls_ssl_context *ssl );
#endif /* MBEDTLS_SSL_PROTO_DTLS */

void mbedtls_ssl_set_timer( mbedtls_ssl_context *ssl, uint32_t millisecs );
int mbedtls_ssl_check_timer( mbedtls_ssl_context *ssl );

void mbedtls_ssl_reset_in_out_pointers( mbedtls_ssl_context *ssl );
void mbedtls_ssl_update_out_pointers( mbedtls_ssl_context *ssl,
                              mbedtls_ssl_transform *transform );
void mbedtls_ssl_update_in_pointers( mbedtls_ssl_context *ssl );

int mbedtls_ssl_session_reset_int( mbedtls_ssl_context *ssl, int partial );

#if defined(MBEDTLS_SSL_DTLS_ANTI_REPLAY)
void mbedtls_ssl_dtls_replay_reset( mbedtls_ssl_context *ssl );
#endif

void mbedtls_ssl_handshake_wrapup_free_hs_transform( mbedtls_ssl_context *ssl );

#if defined(MBEDTLS_SSL_RENEGOTIATION)
int mbedtls_ssl_start_renegotiation( mbedtls_ssl_context *ssl );
#endif /* MBEDTLS_SSL_RENEGOTIATION */

#if defined(MBEDTLS_SSL_PROTO_DTLS)
size_t mbedtls_ssl_get_current_mtu( const mbedtls_ssl_context *ssl );
void mbedtls_ssl_buffering_free( mbedtls_ssl_context *ssl );
void mbedtls_ssl_flight_free( mbedtls_ssl_flight_item *flight );
#endif /* MBEDTLS_SSL_PROTO_DTLS */

#endif /* ssl_内部.h*/

