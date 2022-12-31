/**
 * \文件x509_csr.h
 *
 * \简短的X.509证书签名请求解析和写入
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
#ifndef MBEDTLS_X509_CSR_H
#define MBEDTLS_X509_CSR_H

#if !defined(MBEDTLS_CONFIG_FILE)
#include "mbedtls/config.h"
#else
#include MBEDTLS_CONFIG_FILE
#endif

#include "mbedtls/x509.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \添加组x509_模块
 * \{ */

/**
 * \名称X.509证书签名请求（CSR）的结构和功能\{
 */

/**
 * 证书签名请求（CSR）结构。
 */
typedef struct mbedtls_x509_csr
{
    mbedtls_x509_buf raw;           /**<原始CSR数据（DER）。*/
    mbedtls_x509_buf cri;           /**<原始CertificateRequestInfo主体（DER）。*/

    int version;            /**<CSR版本（1=v1）。*/

    mbedtls_x509_buf  subject_raw;  /**<原始受试者数据（DER）。*/
    mbedtls_x509_name subject;      /**<解析的主题数据（命名的信息对象）。*/

    mbedtls_pk_context pk;          /**<公钥上下文的容器。*/

    mbedtls_x509_buf sig_oid;
    mbedtls_x509_buf sig;
    mbedtls_md_type_t sig_md;       /**<签名算法的MD算法的内部表示，例如MBEDTLS_MD_SHA256*/
    mbedtls_pk_type_t sig_pk;       /**<签名算法的公钥算法的内部表示，例如MBEDTLS_PK_RSA*/
    void *sig_opts;         /**<要传递给mbedtls_pk_verify_ext（）的签名选项，例如RSASSA-PSS*/
}
mbedtls_x509_csr;

/**
 * 用于编写CSR的容器
 */
typedef struct mbedtls_x509write_csr
{
    mbedtls_pk_context *key;
    mbedtls_asn1_named_data *subject;
    mbedtls_md_type_t md_alg;
    mbedtls_asn1_named_data *extensions;
}
mbedtls_x509write_csr;

#if defined(MBEDTLS_X509_CSR_PARSE_C)
/**
 * \brief以DER格式加载证书签名请求（CSR）
 *
 * \注意CSR属性（如果有的话）当前被忽略。
 *
 * \param csr要填充的csr上下文\n保存CRL数据的缓冲区\n缓冲区的缓冲区大小
 *
 * \如果成功，则返回0，或返回特定的X509错误代码
 */
int mbedtls_x509_csr_parse_der( mbedtls_x509_csr *csr,
                        const unsigned char *buf, size_t buflen );

/**
 * \brief加载证书签名请求（CSR）、DER或PEM格式
 *
 * \注释请参见\c mbedtls_x509_csr_parse_der（）的注释
 *
 * \param csr csr上下文以填充保存CRL数据的缓冲区（包括PEM数据的终止空字节）
 *
 * \如果成功，则返回0，或者返回特定的X509或PEM错误代码
 */
int mbedtls_x509_csr_parse( mbedtls_x509_csr *csr, const unsigned char *buf, size_t buflen );

#if defined(MBEDTLS_FS_IO)
/**
 * \brief加载证书签名请求（CSR）
 *
 * \注释请参见\c mbedtls_x509_csr_parse（）的注释
 *
 * \param csr要填充的csr上下文\param要从中读取csr的路径文件名
 *
 * \如果成功，则返回0，或者返回特定的X509或PEM错误代码
 */
int mbedtls_x509_csr_parse_file( mbedtls_x509_csr *csr, const char *path );
#endif /* MBEDTLS_FS_IO */

/**
 * \brief返回有关CSR的信息字符串。
 *
 * \param buf要写入的缓冲区\param size缓冲区的最大大小\param prefix A行前缀\param csr要表示的X509 csr
 *
 * \return所写字符串的长度（不包括终止的nul字节）或负错误代码。
 */
int mbedtls_x509_csr_info( char *buf, size_t size, const char *prefix,
                   const mbedtls_x509_csr *csr );

/**
 * \brief初始化CSR
 *
 * \param csr csr初始化
 */
void mbedtls_x509_csr_init( mbedtls_x509_csr *csr );

/**
 * \brief取消分配所有CSR数据
 *
 * \param csr csr释放
 */
void mbedtls_x509_csr_free( mbedtls_x509_csr *csr );
#endif /* MBEDTLS_X509_CSR_PARSE_C */

/* \}名称*/
/* \}添加组x509_模块*/

#if defined(MBEDTLS_X509_CSR_WRITE_C)
/**
 * \brief初始化CSR上下文
 *
 * \param ctx要初始化的CSR上下文
 */
void mbedtls_x509write_csr_init( mbedtls_x509write_csr *ctx );

/**
 * \brief设置CSR主题名称主题名称应包含以逗号分隔的OID类型和值列表：例如“C=UK，O=ARM，CN=mbed TLS Server 1”
 *
 * \param ctx要使用的CSR上下文\param subject_name要设置的主题名称
 *
 * \如果主题名称解析成功，则返回0，或者返回特定的错误代码
 */
int mbedtls_x509write_csr_set_subject_name( mbedtls_x509write_csr *ctx,
                                    const char *subject_name );

/**
 * \brief设置CSR的密钥（包括公钥，写入CSR时用于签名的私钥）
 *
 * \param ctx要使用的CSR上下文\param key要包含的Asymetric key
 */
void mbedtls_x509write_csr_set_key( mbedtls_x509write_csr *ctx, mbedtls_pk_context *key );

/**
 * \brief设置用于签名的MD算法（例如MBEDTLS_MD_SHA1）
 *
 * \param ctx要使用的CSR上下文\param md_alg要使用的md算法
 */
void mbedtls_x509write_csr_set_md_alg( mbedtls_x509write_csr *ctx, mbedtls_md_type_t md_alg );

/**
 * \brief设置密钥使用扩展标志（例如MBEDTLS_X509_KU_DIGITAL_SIGNATURE|MBEDTLS_X509_KU_Key_CERT_SIGN）
 *
 * \param ctx要使用的CSR上下文\param key_usage要设置的密钥用法标志
 *
 * \如果成功，则返回0，或MBEDTLS_ERROR_X509_ALLOC_FAILED
 *
 * \注意：密钥用法扩展中的<code>decisibleOnly</code>标志由位8表示（即<code>0x8000</code>），通常不能用无符号字符表示。因此，不能使用此函数设置标志<code>decodeOnly</code>（即#MBEDTLS_X509_KU_DECIPHER_ONLY）。
 */
int mbedtls_x509write_csr_set_key_usage( mbedtls_x509write_csr *ctx, unsigned char key_usage );

/**
 * \brief设置Netscape证书类型标志（例如MBEDTLS_X509_NS_Cert_Type_SSL_CLIENT | MBEDTLS_X509_NS_Cert_Type-EMAIL）
 *
 * \param ctx要使用的CSR上下文\param ns_cert_type要设置的Netscape证书类型标志
 *
 * \如果成功，则返回0，或MBEDTLS_ERROR_X509_ALLOC_FAILED
 */
int mbedtls_x509write_csr_set_ns_cert_type( mbedtls_x509write_csr *ctx,
                                    unsigned char ns_cert_type );

/**
 * \简短的通用函数，用于添加或替换CSR中的扩展
 *
 * \param ctx CSR上下文使用扩展名的oid oid \param oid_len长度\param扩展名的值OCET STRING \param val_len长度数据
 *
 * \如果成功，则返回0，或者返回MBEDTLS_ERROR_X509_ALLOC_FAILED
 */
int mbedtls_x509write_csr_set_extension( mbedtls_x509write_csr *ctx,
                                 const char *oid, size_t oid_len,
                                 const unsigned char *val, size_t val_len );

/**
 * \brief释放CSR上下文的内容
 *
 * \param ctx要释放的CSR上下文
 */
void mbedtls_x509write_csr_free( mbedtls_x509write_csr *ctx );

/**
 * \brief将CSR（证书签名请求）写入DER结构注意：数据写入缓冲区的末尾！使用返回值确定应该从何处开始使用缓冲区
 *
 * \param ctx CSR要写入的内容\param buf buffer要写入的缓冲区大小\param f_rng rng函数（有关签名，请参阅注释）\param p_rng rng参数
 *
 * \如果成功，返回写入的数据长度，或返回特定的错误代码
 *
 * \如果RSA被用于签名并且签名被离线，则注释f_rng可以是NULL（否则f_rng是针对定时攻击的对策所需要的）。ECDSA签名始终需要非NULL f_rng。
 */
int mbedtls_x509write_csr_der( mbedtls_x509write_csr *ctx, unsigned char *buf, size_t size,
                       int (*f_rng)(void *, unsigned char *, size_t),
                       void *p_rng );

#if defined(MBEDTLS_PEM_WRITE_C)
/**
 * \brief将CSR（证书签名请求）写入PEM字符串
 *
 * \param ctx CSR要写入的内容\param buf buffer要写入的缓冲区大小\param f_rng rng函数（有关签名，请参阅注释）\param p_rng rng参数
 *
 * \如果成功，则返回0，或返回特定的错误代码
 *
 * \如果RSA被用于签名并且签名被离线，则注释f_rng可以是NULL（否则f_rng是针对定时攻击的对策所需要的）。ECDSA签名始终需要非NULL f_rng。
 */
int mbedtls_x509write_csr_pem( mbedtls_x509write_csr *ctx, unsigned char *buf, size_t size,
                       int (*f_rng)(void *, unsigned char *, size_t),
                       void *p_rng );
#endif /* MBEDTLS_PEM_WRITE_C */
#endif /* MBEDTLS_X509_CSR_WRITE_C */

#ifdef __cplusplus
}
#endif

#endif /* mbedtls_x509_csr.h文件*/

