/**
 * \文件x509_crl.h
 *
 * \简短的X.509证书吊销列表分析
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
#ifndef MBEDTLS_X509_CRL_H
#define MBEDTLS_X509_CRL_H

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
 * \name解析CRL的结构和函数\{
 */

/**
 * 证书吊销列表条目。包含CA特定的序列号和吊销日期。
 */
typedef struct mbedtls_x509_crl_entry
{
    mbedtls_x509_buf raw;

    mbedtls_x509_buf serial;

    mbedtls_x509_time revocation_date;

    mbedtls_x509_buf entry_ext;

    struct mbedtls_x509_crl_entry *next;
}
mbedtls_x509_crl_entry;

/**
 * 证书吊销列表结构。每个CRL可能有多个条目。
 */
typedef struct mbedtls_x509_crl
{
    mbedtls_x509_buf raw;           /**<原始证书数据（DER）。*/
    mbedtls_x509_buf tbs;           /**<原始证书主体（DER）。要签名的部分。*/

    int version;            /**<CRL版本（1=v1，2=v2）*/
    mbedtls_x509_buf sig_oid;       /**<CRL签名类型标识符*/

    mbedtls_x509_buf issuer_raw;    /**<原始发行人数据（DER）。*/

    mbedtls_x509_name issuer;       /**<解析的颁发者数据（命名的信息对象）。*/

    mbedtls_x509_time this_update;
    mbedtls_x509_time next_update;

    mbedtls_x509_crl_entry entry;   /**<包含此CA的证书吊销时间的CRL条目。*/

    mbedtls_x509_buf crl_ext;

    mbedtls_x509_buf sig_oid2;
    mbedtls_x509_buf sig;
    mbedtls_md_type_t sig_md;           /**<签名算法的MD算法的内部表示，例如MBEDTLS_MD_SHA256*/
    mbedtls_pk_type_t sig_pk;           /**<签名算法的公钥算法的内部表示，例如MBEDTLS_PK_RSA*/
    void *sig_opts;             /**<要传递给mbedtls_pk_verify_ext（）的签名选项，例如RSASSA-PSS*/

    struct mbedtls_x509_crl *next;
}
mbedtls_x509_crl;

/**
 * \简要分析DER编码的CRL并将其附加到链接列表
 *
 * \param chain指向保存DER格式CRL数据的缓冲区链的起始位置（包括PEM数据的终止空字节）
 *
 * \如果成功，则返回0，或者返回特定的X509或PEM错误代码
 */
int mbedtls_x509_crl_parse_der( mbedtls_x509_crl *chain,
                        const unsigned char *buf, size_t buflen );
/**
 * \简要分析一个或多个CRL并将其附加到链接列表
 *
 * \注：只有使用PEM格式时，才接受多个CRL
 *
 * \param chain指向保存PEM或DER格式CRL数据的缓冲区链的起始位置（包括PEM数据的终止空字节）
 *
 * \如果成功，则返回0，或者返回特定的X509或PEM错误代码
 */
int mbedtls_x509_crl_parse( mbedtls_x509_crl *chain, const unsigned char *buf, size_t buflen );

#if defined(MBEDTLS_FS_IO)
/**
 * \brief加载一个或多个CRL并将其附加到链接列表中
 *
 * \注：只有使用PEM格式时，才接受多个CRL
 *
 * \param chain指向要从中读取CRL的链的开头\param路径文件名（以PEM或DER编码）
 *
 * \如果成功，则返回0，或者返回特定的X509或PEM错误代码
 */
int mbedtls_x509_crl_parse_file( mbedtls_x509_crl *chain, const char *path );
#endif /* MBEDTLS_FS_IO */

/**
 * \brief返回有关CRL的信息字符串。
 *
 * \param buf要写入的缓冲区\param size缓冲区的最大大小\param prefix A行前缀\param crl要表示的X509 crl
 *
 * \return所写字符串的长度（不包括终止的nul字节）或负错误代码。
 */
int mbedtls_x509_crl_info( char *buf, size_t size, const char *prefix,
                   const mbedtls_x509_crl *crl );

/**
 * \brief初始化CRL（链）
 *
 * \param crl要初始化的crl链
 */
void mbedtls_x509_crl_init( mbedtls_x509_crl *crl );

/**
 * \brief取消分配所有CRL数据
 *
 * \param crl crl链释放
 */
void mbedtls_x509_crl_free( mbedtls_x509_crl *crl );

/* \}名称*/
/* \}添加组x509_模块*/

#ifdef __cplusplus
}
#endif

#endif /* mbedtls_x509_crl.h文件*/

