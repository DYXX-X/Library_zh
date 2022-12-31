/*
 *  TLS 1.3密钥计划
 *
 *  版权所有The Mbed TLS Contributors SPDX许可证标识符：Apache-2.0
 *
 *  根据Apache许可证2.0版（“许可证”）获得许可；除非符合许可证，否则不得使用此文件。您可以在以下地址获取许可证副本：
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 *  除非适用法律要求或书面同意，否则根据许可证分发的软件是按“原样”分发的，无任何明示或暗示的担保或条件。有关许可证下权限和限制的具体语言，请参阅许可证。
 */
#if !defined(MBEDTLS_SSL_TLS1_3_KEYS_H)
#define MBEDTLS_SSL_TLS1_3_KEYS_H

/* 这需要在使用点定义MBEDTLS_SL_TLS1_3_LABEL（idx，name，string）。例如，请参见下面mbedtls_ssl_tls1_3_labels_union的定义。*/
#define MBEDTLS_SSL_TLS1_3_LABEL_LIST                               \
    MBEDTLS_SSL_TLS1_3_LABEL( finished    , "finished"     ) \
    MBEDTLS_SSL_TLS1_3_LABEL( resumption  , "resumption"   ) \
    MBEDTLS_SSL_TLS1_3_LABEL( traffic_upd , "traffic upd"  ) \
    MBEDTLS_SSL_TLS1_3_LABEL( exporter    , "exporter"     ) \
    MBEDTLS_SSL_TLS1_3_LABEL( key         , "key"          ) \
    MBEDTLS_SSL_TLS1_3_LABEL( iv          , "iv"           ) \
    MBEDTLS_SSL_TLS1_3_LABEL( c_hs_traffic, "c hs traffic" ) \
    MBEDTLS_SSL_TLS1_3_LABEL( c_ap_traffic, "c ap traffic" ) \
    MBEDTLS_SSL_TLS1_3_LABEL( c_e_traffic , "c e traffic"  ) \
    MBEDTLS_SSL_TLS1_3_LABEL( s_hs_traffic, "s hs traffic" ) \
    MBEDTLS_SSL_TLS1_3_LABEL( s_ap_traffic, "s ap traffic" ) \
    MBEDTLS_SSL_TLS1_3_LABEL( s_e_traffic , "s e traffic"  ) \
    MBEDTLS_SSL_TLS1_3_LABEL( e_exp_master, "e exp master" ) \
    MBEDTLS_SSL_TLS1_3_LABEL( res_master  , "res master"   ) \
    MBEDTLS_SSL_TLS1_3_LABEL( exp_master  , "exp master"   ) \
    MBEDTLS_SSL_TLS1_3_LABEL( ext_binder  , "ext binder"   ) \
    MBEDTLS_SSL_TLS1_3_LABEL( res_binder  , "res binder"   ) \
    MBEDTLS_SSL_TLS1_3_LABEL( derived     , "derived"      )

#define MBEDTLS_SSL_TLS1_3_LABEL( name, string )       \
    const unsigned char name    [ sizeof(string) - 1 ];

union mbedtls_ssl_tls1_3_labels_union
{
    MBEDTLS_SSL_TLS1_3_LABEL_LIST
};
struct mbedtls_ssl_tls1_3_labels_struct
{
    MBEDTLS_SSL_TLS1_3_LABEL_LIST
};
#undef MBEDTLS_SSL_TLS1_3_LABEL

extern const struct mbedtls_ssl_tls1_3_labels_struct mbedtls_ssl_tls1_3_labels;

#define MBEDTLS_SSL_TLS1_3_LBL_WITH_LEN( LABEL )  \
    mbedtls_ssl_tls1_3_labels.LABEL,              \
    sizeof(mbedtls_ssl_tls1_3_labels.LABEL)

#define MBEDTLS_SSL_TLS1_3_KEY_SCHEDULE_MAX_LABEL_LEN  \
    sizeof( union mbedtls_ssl_tls1_3_labels_union )

/* TLS 1.3标准中使用的HKDF上下文的最大长度。由于上下文总是消息转录的散列，因此可以从上面通过最大散列大小来近似。*/
#define MBEDTLS_SSL_TLS1_3_KEY_SCHEDULE_MAX_CONTEXT_LEN  \
    MBEDTLS_MD_MAX_SIZE

/* HKDF扩展标签生成的扩展密钥材料的最大期望长度。
 *
 * 警告：如果需要增加此值，请使用ssl_tls13_keys中的实现ssl_tlsl3_hkdf_encode_label（）。c需要调整，因为它当前假设HKDF密钥扩展从未用于超过255字节的输出。*/
#define MBEDTLS_SSL_TLS1_3_KEY_SCHEDULE_MAX_EXPANSION_LEN 255

/**
 * \brief TLS 1.3标准RFC 8446中的HKDF Expand Label功能。
 *
 * <tt>HKDF扩展标签（机密，标签，上下文，长度）=HKDF扩展（机密，HkdfLabel，长度）</tt>
 *
 * \param hash_alg要使用的哈希算法的标识符。\param secret \c HKDF Expand Label的\c secret参数。这必须是长度为\p slen Bytes的可读缓冲区。\param slen \p secret的长度（以字节为单位）。\param label HKDF Expand label的\c label参数。这必须是长度为\pllen Bytes的可读缓冲区。\param llen \p标签的长度（以字节为单位）。\param ctx HKDF Expand Label的\c Context参数。这必须是长度为\p clen Bytes的可读缓冲区。\param clen \p上下文的长度（以字节为单位）。\param buf保存扩展密钥的目标缓冲区。这必须是长度为\n blen Bytes的可写缓冲区。\param blen所需的扩展密钥大小（字节）。
 *
 * \成功时返回\c 0。\失败时返回负错误代码。
 */

int mbedtls_ssl_tls1_3_hkdf_expand_label(
                     mbedtls_md_type_t hash_alg,
                     const unsigned char *secret, size_t slen,
                     const unsigned char *label, size_t llen,
                     const unsigned char *ctx, size_t clen,
                     unsigned char *buf, size_t blen );

/**
 * \brief此功能是TLS 1.3密钥计划的一部分。它从客户端/服务器流量秘密中提取实际客户端/服务器通信的密钥和IV。
 *
 * 来自RFC 8446：
 *
 * <tt>[sender]_write_key=HKDF扩展标签（机密，“key”，“”，key_length
 *
 * \param hash_alg用于基于HKDF的密钥扩展的哈希算法的标识符。\param client_secret客户端流量机密。这必须是大小为\p slen Bytes\param server_secret服务器流量机密的可读缓冲区。这必须是一个可读缓冲区，大小为\p slen Bytes\param slen secrets\p client_secret和\p server_secret的长度（以字节为单位）。\param key_len要提取的密钥的所需长度（字节）。\param iv_len要提取的iv的所需长度（字节）。\param keys保存生成的密钥和IV的结构的地址。
 *
 * \成功时返回\c 0。\失败时返回负错误代码。
 */

int mbedtls_ssl_tls1_3_make_traffic_keys(
                     mbedtls_md_type_t hash_alg,
                     const unsigned char *client_secret,
                     const unsigned char *server_secret,
                     size_t slen, size_t key_len, size_t iv_len,
                     mbedtls_ssl_key_set *keys );


#define MBEDTLS_SSL_TLS1_3_CONTEXT_UNHASHED 0
#define MBEDTLS_SSL_TLS1_3_CONTEXT_HASHED   1

/**
 * \brief从TLS 1.3标准RFC 8446中派生Secret函数。
 *
 * <tt>派生秘密（秘密、标签、消息）=HKDF扩展标签（秘密、标记、哈希（消息）、哈希）。长度））</tt>
 *
 * \param hash_alg HKDF应用程序使用的哈希函数的标识符。\param secret \c Derive secret函数的\c secret参数。这必须是长度为\p slen Bytes的可读缓冲区。\param slen \p secret的长度（以字节为单位）。\param label \c Derive Secret函数的\c label参数。这必须是长度为\pllen Bytes的可读缓冲区。\param llen \p标签的长度（以字节为单位）。\param ctx \c Derive Secret函数的\c Messages参数的哈希值，或\c Messages参数本身，具体取决于\p context_already_hashed。\param clen \p哈希的长度。\param ctx_hashed这表示ctx是否包含派生秘密函数应用程序中的消息参数的哈希（值MBEDTLS_SL_TLS1_3_CONTEXT_hashed），或者它是否是消息本身的内容，在这种情况下，函数会处理哈希（值为MBEDTL_SSL_TLS_13_CONTEXT_UNHASHED。\param dstbuf将派生密钥的输出写入的目标缓冲区。这必须是大小为\p buflen Bytes的可写缓冲区。\param buflen \p dstbuf的长度（以字节为单位）。
 *
 * \成功时返回\c 0。\失败时返回负错误代码。
 */
int mbedtls_ssl_tls1_3_derive_secret(
                   mbedtls_md_type_t hash_alg,
                   const unsigned char *secret, size_t slen,
                   const unsigned char *label, size_t llen,
                   const unsigned char *ctx, size_t clen,
                   int ctx_hashed,
                   unsigned char *dstbuf, size_t buflen );

/**
 * \简要计算TLS 1.3密钥计划中的下一个秘密
 *
 * TLS 1.3密钥调度按如下方式进行，以计算握手期间的三个主要秘密：早期数据的早期秘密、所有其他加密握手消息的握手秘密以及所有应用程序流量的主秘密。
 *
 * <tt>0|v PSK->HKDF Extract=早期秘密|v派生秘密（.，“派生”，“”）|v（EC）DHE->HKDF Extract=握手密钥|v派生密钥（.，”派生“，“”
 *
 * 这三个秘密中的每一个都是进一步密钥推导的基础，例如流量密钥和IV的推导；参见例如mbedtls_ssl_tls1_3_make_traffic_keys（）。
 *
 * 该函数实现了秘密演变的一个步骤：
 *
 * <tt>old_secret|v派生密钥（.，“derived”，“”）|v input->HKDF Extract=new_secret</tt>
 *
 * \param hash_alg HKDF应用程序使用的哈希函数的标识符。\param secret_old保存函数项上旧密钥的缓冲区的地址。如果不是空，则必须是可读缓冲区，其大小与\p hash_alg表示的哈希函数的输出大小匹配。如果\c为NULL，则将改用all\c 0数组。\param input保存密钥派生的附加输入的缓冲区的地址（例如，PSK或临时（EC）DH密钥）。如果不是空，则必须是大小为\p input_len Bytes的可读缓冲区。如果\c为NULL，则将改用all\c 0数组。\param input_len输入的长度（字节）。\param secret_new函数退出时保存新秘密的缓冲区的地址。这必须是一个可写缓冲区，其大小与\p hash_alg表示的哈希函数的输出大小匹配。这可能与\p secret_old相同。
 *
 * \成功时返回\c 0。\失败时返回负错误代码。
 */

int mbedtls_ssl_tls1_3_evolve_secret(
                   mbedtls_md_type_t hash_alg,
                   const unsigned char *secret_old,
                   const unsigned char *input, size_t input_len,
                   unsigned char *secret_new );

#endif /* MBEDTLS_SSL_TLS1_3_KEYS_H */

