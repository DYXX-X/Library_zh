/**
 * \文件x509.h
 *
 * \简短的X.509通用定义和结构
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
#ifndef MBEDTLS_X509_H
#define MBEDTLS_X509_H

#if !defined(MBEDTLS_CONFIG_FILE)
#include "mbedtls/config.h"
#else
#include MBEDTLS_CONFIG_FILE
#endif

#include "mbedtls/asn1.h"
#include "mbedtls/pk.h"

#if defined(MBEDTLS_RSA_C)
#include "mbedtls/rsa.h"
#endif

/**
 * \添加组x509_模块\{
 */

#if !defined(MBEDTLS_X509_MAX_INTERMEDIATE_CA)
/**
 * 验证链中中间CA的最大数量。即链的最大长度，不包括最终实体证书和受信任的根证书。
 *
 * 将此值设置为较低值，以防止对手使您浪费资源验证过长的证书链。
 */
#define MBEDTLS_X509_MAX_INTERMEDIATE_CA   8
#endif

/**
 * \name X509错误代码\{
 */
#define MBEDTLS_ERR_X509_FEATURE_UNAVAILABLE              -0x2080  /**<不可用功能，例如RSA哈希/加密组合。*/
#define MBEDTLS_ERR_X509_UNKNOWN_OID                      -0x2100  /**<请求的OID未知。*/
#define MBEDTLS_ERR_X509_INVALID_FORMAT                   -0x2180  /**<CRT/CRL/CSR格式无效，例如需要不同的类型。*/
#define MBEDTLS_ERR_X509_INVALID_VERSION                  -0x2200  /**<CRT/CRL/CSR版本元素无效。*/
#define MBEDTLS_ERR_X509_INVALID_SERIAL                   -0x2280  /**<序列标记或值无效。*/
#define MBEDTLS_ERR_X509_INVALID_ALG                      -0x2300  /**<算法标记或值无效。*/
#define MBEDTLS_ERR_X509_INVALID_NAME                     -0x2380  /**<名称标记或值无效。*/
#define MBEDTLS_ERR_X509_INVALID_DATE                     -0x2400  /**<日期标记或值无效。*/
#define MBEDTLS_ERR_X509_INVALID_SIGNATURE                -0x2480  /**<签名标记或值无效。*/
#define MBEDTLS_ERR_X509_INVALID_EXTENSIONS               -0x2500  /**<扩展标记或值无效。*/
#define MBEDTLS_ERR_X509_UNKNOWN_VERSION                  -0x2580  /**<CRT/CRL/CSR的版本号不受支持。*/
#define MBEDTLS_ERR_X509_UNKNOWN_SIG_ALG                  -0x2600  /**<不支持签名算法（oid）。*/
#define MBEDTLS_ERR_X509_SIG_MISMATCH                     -0x2680  /**<签名算法不匹配。（请参见\c:：mbedtls_x509_crt sig_oid）*/
#define MBEDTLS_ERR_X509_CERT_VERIFY_FAILED               -0x2700  /**<证书验证失败，例如CRL、CA或签名检查失败。*/
#define MBEDTLS_ERR_X509_CERT_UNKNOWN_FORMAT              -0x2780  /**<格式未识别为DER或PEM。*/
#define MBEDTLS_ERR_X509_BAD_INPUT_DATA                   -0x2800  /**<输入无效。*/
#define MBEDTLS_ERR_X509_ALLOC_FAILED                     -0x2880  /**<内存分配失败。*/
#define MBEDTLS_ERR_X509_FILE_IO_ERROR                    -0x2900  /**<读取/写入文件失败。*/
#define MBEDTLS_ERR_X509_BUFFER_TOO_SMALL                 -0x2980  /**<目标缓冲区太小。*/
#define MBEDTLS_ERR_X509_FATAL_ERROR                      -0x3000  /**<发生致命错误，例如链太长或vrfy回调失败。*/
/* \}名称*/

/**
 * \名称X509验证代码\{
 */
/* 提醒：更新库/x509_crt中的x509_crt_verify_strings[]。c*/
#define MBEDTLS_X509_BADCERT_EXPIRED             0x01  /**<证书有效期已过期。*/
#define MBEDTLS_X509_BADCERT_REVOKED             0x02  /**<证书已被吊销（位于CRL上）。*/
#define MBEDTLS_X509_BADCERT_CN_MISMATCH         0x04  /**<证书公用名称（CN）与预期的CN不匹配。*/
#define MBEDTLS_X509_BADCERT_NOT_TRUSTED         0x08  /**<证书未由受信任的CA正确签名。*/
#define MBEDTLS_X509_BADCRL_NOT_TRUSTED          0x10  /**<CRL未由受信任的CA正确签名。*/
#define MBEDTLS_X509_BADCRL_EXPIRED              0x20  /**<CRL已过期。*/
#define MBEDTLS_X509_BADCERT_MISSING             0x40  /**<缺少证书。*/
#define MBEDTLS_X509_BADCERT_SKIP_VERIFY         0x80  /**<已跳过证书验证。*/
#define MBEDTLS_X509_BADCERT_OTHER             0x0100  /**<其他原因（可通过验证回调使用）*/
#define MBEDTLS_X509_BADCERT_FUTURE            0x0200  /**<证书有效期将从未来开始。*/
#define MBEDTLS_X509_BADCRL_FUTURE             0x0400  /**<CRL来自未来*/
#define MBEDTLS_X509_BADCERT_KEY_USAGE         0x0800  /**<Usage与keyUsage扩展名不匹配。*/
#define MBEDTLS_X509_BADCERT_EXT_KEY_USAGE     0x1000  /**<Usage与extendedKeyUsage扩展不匹配。*/
#define MBEDTLS_X509_BADCERT_NS_CERT_TYPE      0x2000  /**<用法与nsCertType扩展不匹配。*/
#define MBEDTLS_X509_BADCERT_BAD_MD            0x4000  /**<证书使用不可接受的哈希签名。*/
#define MBEDTLS_X509_BADCERT_BAD_PK            0x8000  /**<证书上签署了不可接受的PK alg（如RSA vs ECDSA）。*/
#define MBEDTLS_X509_BADCERT_BAD_KEY         0x010000  /**<证书使用不可接受的密钥签名（例如，曲线不好，RSA太短）。*/
#define MBEDTLS_X509_BADCRL_BAD_MD           0x020000  /**<CRL使用不可接受的哈希签名。*/
#define MBEDTLS_X509_BADCRL_BAD_PK           0x040000  /**<CRL使用不可接受的PK alg签名（例如RSA vs ECDSA）。*/
#define MBEDTLS_X509_BADCRL_BAD_KEY          0x080000  /**<CRL使用不可接受的密钥签名（例如，错误的曲线、RSA太短）。*/

/* \}名称*/
/* \}添加组x509_模块*/

/*
 * 十、 509 v3主题替代名称类型。otherName[0]otherName，rfc822Name[1]IA5String，dNSName[2]IA5String，x400Address[3]ORAddress，directoryName[4]Name，ediPartyName[5]ediPartyName，uniformResourceIdentifier[6]IA5String，iPAddress[7]OCET STRING，registeredID[8]OBJECT IDENTIFIER
 */
#define MBEDTLS_X509_SAN_OTHER_NAME                      0
#define MBEDTLS_X509_SAN_RFC822_NAME                     1
#define MBEDTLS_X509_SAN_DNS_NAME                        2
#define MBEDTLS_X509_SAN_X400_ADDRESS_NAME               3
#define MBEDTLS_X509_SAN_DIRECTORY_NAME                  4
#define MBEDTLS_X509_SAN_EDI_PARTY_NAME                  5
#define MBEDTLS_X509_SAN_UNIFORM_RESOURCE_IDENTIFIER     6
#define MBEDTLS_X509_SAN_IP_ADDRESS                      7
#define MBEDTLS_X509_SAN_REGISTERED_ID                   8

/*
 * 十、 509 v3密钥使用扩展标志提醒：添加新标志时更新x509_info_Key_Usage（）。
 */
#define MBEDTLS_X509_KU_DIGITAL_SIGNATURE            (0x80)  /* 位0*/
#define MBEDTLS_X509_KU_NON_REPUDIATION              (0x40)  /* 第1位*/
#define MBEDTLS_X509_KU_KEY_ENCIPHERMENT             (0x20)  /* 第2位*/
#define MBEDTLS_X509_KU_DATA_ENCIPHERMENT            (0x10)  /* 第3位*/
#define MBEDTLS_X509_KU_KEY_AGREEMENT                (0x08)  /* 第4位*/
#define MBEDTLS_X509_KU_KEY_CERT_SIGN                (0x04)  /* 第5位*/
#define MBEDTLS_X509_KU_CRL_SIGN                     (0x02)  /* 第6位*/
#define MBEDTLS_X509_KU_ENCIPHER_ONLY                (0x01)  /* 第7位*/
#define MBEDTLS_X509_KU_DECIPHER_ONLY              (0x8000)  /* 第8位*/

/*
 * Netscape证书类型(http://www.mozilla.org/projects/security/pki/nss/tech-notes/tn3.html)
 */

#define MBEDTLS_X509_NS_CERT_TYPE_SSL_CLIENT         (0x80)  /* 位0*/
#define MBEDTLS_X509_NS_CERT_TYPE_SSL_SERVER         (0x40)  /* 第1位*/
#define MBEDTLS_X509_NS_CERT_TYPE_EMAIL              (0x20)  /* 第2位*/
#define MBEDTLS_X509_NS_CERT_TYPE_OBJECT_SIGNING     (0x10)  /* 第3位*/
#define MBEDTLS_X509_NS_CERT_TYPE_RESERVED           (0x08)  /* 第4位*/
#define MBEDTLS_X509_NS_CERT_TYPE_SSL_CA             (0x04)  /* 第5位*/
#define MBEDTLS_X509_NS_CERT_TYPE_EMAIL_CA           (0x02)  /* 第6位*/
#define MBEDTLS_X509_NS_CERT_TYPE_OBJECT_SIGNING_CA  (0x01)  /* 第7位*/

/*
 * 十、 509扩展类型
 *
 * 注释是指使用证书的状态。写入证书或读取CRL或CSR的状态可能不同。
 *
 * 这些定义在oid中。h为oid。c在数据结构中需要它们。由于这些是之前在这里定义的，所以为了兼容性，我们使用别名。
 */
#define MBEDTLS_X509_EXT_AUTHORITY_KEY_IDENTIFIER MBEDTLS_OID_X509_EXT_AUTHORITY_KEY_IDENTIFIER
#define MBEDTLS_X509_EXT_SUBJECT_KEY_IDENTIFIER   MBEDTLS_OID_X509_EXT_SUBJECT_KEY_IDENTIFIER
#define MBEDTLS_X509_EXT_KEY_USAGE                MBEDTLS_OID_X509_EXT_KEY_USAGE
#define MBEDTLS_X509_EXT_CERTIFICATE_POLICIES     MBEDTLS_OID_X509_EXT_CERTIFICATE_POLICIES
#define MBEDTLS_X509_EXT_POLICY_MAPPINGS          MBEDTLS_OID_X509_EXT_POLICY_MAPPINGS
#define MBEDTLS_X509_EXT_SUBJECT_ALT_NAME         MBEDTLS_OID_X509_EXT_SUBJECT_ALT_NAME         /* 支持（DNS）*/
#define MBEDTLS_X509_EXT_ISSUER_ALT_NAME          MBEDTLS_OID_X509_EXT_ISSUER_ALT_NAME
#define MBEDTLS_X509_EXT_SUBJECT_DIRECTORY_ATTRS  MBEDTLS_OID_X509_EXT_SUBJECT_DIRECTORY_ATTRS
#define MBEDTLS_X509_EXT_BASIC_CONSTRAINTS        MBEDTLS_OID_X509_EXT_BASIC_CONSTRAINTS        /* 支持*/
#define MBEDTLS_X509_EXT_NAME_CONSTRAINTS         MBEDTLS_OID_X509_EXT_NAME_CONSTRAINTS
#define MBEDTLS_X509_EXT_POLICY_CONSTRAINTS       MBEDTLS_OID_X509_EXT_POLICY_CONSTRAINTS
#define MBEDTLS_X509_EXT_EXTENDED_KEY_USAGE       MBEDTLS_OID_X509_EXT_EXTENDED_KEY_USAGE
#define MBEDTLS_X509_EXT_CRL_DISTRIBUTION_POINTS  MBEDTLS_OID_X509_EXT_CRL_DISTRIBUTION_POINTS
#define MBEDTLS_X509_EXT_INIHIBIT_ANYPOLICY       MBEDTLS_OID_X509_EXT_INIHIBIT_ANYPOLICY
#define MBEDTLS_X509_EXT_FRESHEST_CRL             MBEDTLS_OID_X509_EXT_FRESHEST_CRL
#define MBEDTLS_X509_EXT_NS_CERT_TYPE             MBEDTLS_OID_X509_EXT_NS_CERT_TYPE

/*
 * 存储格式标识符公认的格式：PEM和DER
 */
#define MBEDTLS_X509_FORMAT_DER                 1
#define MBEDTLS_X509_FORMAT_PEM                 2

#define MBEDTLS_X509_MAX_DN_NAME_SIZE         256 /**<DN条目的最大值大小*/

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \添加组x509_模块
 * \{ */

/**
 * \name用于解析X.509证书、CRL和CSR的结构\{
 */

/**
 * 类型长度值结构，允许ASN1使用DER。
 */
typedef mbedtls_asn1_buf mbedtls_x509_buf;

/**
 * ASN1位字符串的容器。
 */
typedef mbedtls_asn1_bitstring mbedtls_x509_bitstring;

/**
 * ASN1命名信息对象的容器。它允许相对可分辨名称（例如cn=localhost、ou=code等）。
 */
typedef mbedtls_asn1_named_data mbedtls_x509_name;

/**
 * ASN序列的容器。1项
 */
typedef mbedtls_asn1_sequence mbedtls_x509_sequence;

/**日期和时间的容器（精度以秒为单位）。*/
typedef struct mbedtls_x509_time
{
    int year, mon, day;         /**<日期。*/
    int hour, min, sec;         /**<时间。*/
}
mbedtls_x509_time;

/**\}name用于解析X.509证书、CRL和CSR的结构*/
/**\｝添加组x509_module*/

/**
 * \brief将证书DN以可打印形式存储到buf中；将写入不超过大小的字符。
 *
 * \param buf要写入的缓冲区\param size缓冲区的最大大小\param dn要表示的X509名称
 *
 * \return所写字符串的长度（不包括终止的nul字节）或负错误代码。
 */
int mbedtls_x509_dn_gets( char *buf, size_t size, const mbedtls_x509_name *dn );

/**
 * \brief将证书序列以可打印形式存储到buf中；将写入不超过大小的字符。
 *
 * \param buf要写入的缓冲区\param size缓冲区的最大大小\param serial要表示的X509系列
 *
 * \return所写字符串的长度（不包括终止的nul字节）或负错误代码。
 */
int mbedtls_x509_serial_gets( char *buf, size_t size, const mbedtls_x509_buf *serial );

/**
 * \brief根据系统时间检查给定的mbedtls_x509_time，并判断它是否已过去。
 *
 * \注意：预期用法为“if（is_past（valid_to））ERROR”。因此，如果出现内部错误，则返回值为1。
 *
 * \mbedtls_x509_time的参数
 *
 * \如果给定时间已过去或发生错误，则返回1，否则返回0。
 */
int mbedtls_x509_time_is_past( const mbedtls_x509_time *to );

/**
 * \brief根据系统时间检查给定的mbedtls_x509_time，并告诉它是否在将来。
 *
 * \注意：预期用途是“if（is_future（valid_from））ERROR”。因此，如果出现内部错误，则返回值为1。
 *
 * \要检查的mbedtls_x509_time中的参数
 *
 * \如果给定时间在将来或发生错误，则返回1，否则返回0。
 */
int mbedtls_x509_time_is_future( const mbedtls_x509_time *from );

#if defined(MBEDTLS_SELF_TEST)

/**
 * \简要检查程序
 *
 * \如果成功，则返回0；如果测试失败，则返回1
 */
int mbedtls_x509_self_test( int verbose );

#endif /* MBEDTLS_SELF_TEST */

/*
 * 内部模块功能。除非你知道，否则你可能不想使用这些。
 */
int mbedtls_x509_get_name( unsigned char **p, const unsigned char *end,
                   mbedtls_x509_name *cur );
int mbedtls_x509_get_alg_null( unsigned char **p, const unsigned char *end,
                       mbedtls_x509_buf *alg );
int mbedtls_x509_get_alg( unsigned char **p, const unsigned char *end,
                  mbedtls_x509_buf *alg, mbedtls_x509_buf *params );
#if defined(MBEDTLS_X509_RSASSA_PSS_SUPPORT)
int mbedtls_x509_get_rsassa_pss_params( const mbedtls_x509_buf *params,
                                mbedtls_md_type_t *md_alg, mbedtls_md_type_t *mgf_md,
                                int *salt_len );
#endif
int mbedtls_x509_get_sig( unsigned char **p, const unsigned char *end, mbedtls_x509_buf *sig );
int mbedtls_x509_get_sig_alg( const mbedtls_x509_buf *sig_oid, const mbedtls_x509_buf *sig_params,
                      mbedtls_md_type_t *md_alg, mbedtls_pk_type_t *pk_alg,
                      void **sig_opts );
int mbedtls_x509_get_time( unsigned char **p, const unsigned char *end,
                   mbedtls_x509_time *t );
int mbedtls_x509_get_serial( unsigned char **p, const unsigned char *end,
                     mbedtls_x509_buf *serial );
int mbedtls_x509_get_ext( unsigned char **p, const unsigned char *end,
                  mbedtls_x509_buf *ext, int tag );
int mbedtls_x509_sig_alg_gets( char *buf, size_t size, const mbedtls_x509_buf *sig_oid,
                       mbedtls_pk_type_t pk_alg, mbedtls_md_type_t md_alg,
                       const void *sig_opts );
int mbedtls_x509_key_size_helper( char *buf, size_t buf_size, const char *name );
int mbedtls_x509_string_to_names( mbedtls_asn1_named_data **head, const char *name );
int mbedtls_x509_set_extension( mbedtls_asn1_named_data **head, const char *oid, size_t oid_len,
                        int critical, const unsigned char *val,
                        size_t val_len );
int mbedtls_x509_write_extensions( unsigned char **p, unsigned char *start,
                           mbedtls_asn1_named_data *first );
int mbedtls_x509_write_names( unsigned char **p, unsigned char *start,
                      mbedtls_asn1_named_data *first );
int mbedtls_x509_write_sig( unsigned char **p, unsigned char *start,
                    const char *oid, size_t oid_len,
                    unsigned char *sig, size_t size );

#define MBEDTLS_X509_SAFE_SNPRINTF                          \
    do {                                                    \
        if( ret < 0 || (size_t) ret >= n )                  \
            return( MBEDTLS_ERR_X509_BUFFER_TOO_SMALL );    \
                                                            \
        n -= (size_t) ret;                                  \
        p += (size_t) ret;                                  \
    } while( 0 )

#ifdef __cplusplus
}
#endif

#endif /* x509.h小时*/

