/**
 * \文件x509_crt.h
 *
 * \简短的X.509证书解析和编写
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
#ifndef MBEDTLS_X509_CRT_H
#define MBEDTLS_X509_CRT_H

#if !defined(MBEDTLS_CONFIG_FILE)
#include "mbedtls/config.h"
#else
#include MBEDTLS_CONFIG_FILE
#endif

#include "mbedtls/x509.h"
#include "mbedtls/x509_crl.h"
#include "mbedtls/bignum.h"

/**
 * \添加组x509_模块\{
 */

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \解析和写入X.509证书的结构和函数\{
 */

/**
 * X.509证书的容器。证书可能被链接。
 */
typedef struct mbedtls_x509_crt
{
    int own_buffer;                     /**<指示\c raw是否由结构拥有*。*/
    mbedtls_x509_buf raw;               /**<原始证书数据（DER）。*/
    mbedtls_x509_buf tbs;               /**<原始证书主体（DER）。要签名的部分。*/

    int version;                /**<X.509版本。（1=v1，2=v2，3=v3）*/
    mbedtls_x509_buf serial;            /**<由特定CA颁发的证书的唯一id。*/
    mbedtls_x509_buf sig_oid;           /**<签名算法，例如sha1RSA*/

    mbedtls_x509_buf issuer_raw;        /**<原始发行人数据（DER）。用于快速比较。*/
    mbedtls_x509_buf subject_raw;       /**<原始受试者数据（DER）。用于快速比较。*/

    mbedtls_x509_name issuer;           /**<解析的颁发者数据（命名的信息对象）。*/
    mbedtls_x509_name subject;          /**<解析的主题数据（命名的信息对象）。*/

    mbedtls_x509_time valid_from;       /**<证书有效期的开始时间。*/
    mbedtls_x509_time valid_to;         /**<证书有效期结束时间。*/

    mbedtls_x509_buf pk_raw;
    mbedtls_pk_context pk;              /**<公钥上下文的容器。*/

    mbedtls_x509_buf issuer_id;         /**<可选X.509 v2/v3颁发者唯一标识符。*/
    mbedtls_x509_buf subject_id;        /**<可选X.509 v2/v3主题唯一标识符。*/
    mbedtls_x509_buf v3_ext;            /**<可选X.509 v3扩展。*/
    mbedtls_x509_sequence subject_alt_names;    /**<主题替代名称扩展的原始条目的可选列表（当前仅列出dNSName和OtherName）。*/

    mbedtls_x509_sequence certificate_policies; /**<证书策略的可选列表（仅打印和强制执行任何策略，但仍列出其余策略）。*/

    int ext_types;              /**<包含检测到和解析的扩展名的位字符串*/
    int ca_istrue;              /**<可选基本约束扩展值：如果此证书属于CA，则为1，否则为0。*/
    int max_pathlen;            /**<可选基本约束扩展值：根证书的最大路径长度。路径长度比RFC 5280“表示”高1，因此1+*/

    unsigned int key_usage;     /**<可选密钥用法扩展值：参见x509.h中的值*/

    mbedtls_x509_sequence ext_key_usage; /**<扩展密钥用法OID的可选列表。*/

    unsigned char ns_cert_type; /**<可选Netscape证书类型扩展值：请参见x509.h中的值*/

    mbedtls_x509_buf sig;               /**<签名：使用私钥签名的tbs部分的哈希。*/
    mbedtls_md_type_t sig_md;           /**<签名算法的MD算法的内部表示，例如MBEDTLS_MD_SHA256*/
    mbedtls_pk_type_t sig_pk;           /**<签名算法的公钥算法的内部表示，例如MBEDTLS_PK_RSA*/
    void *sig_opts;             /**<要传递给mbedtls_pk_verify_ext（）的签名选项，例如RSASSA-PSS*/

    struct mbedtls_x509_crt *next;     /**<CA链中的下一个证书。*/
}
mbedtls_x509_crt;

/**
 * 根据RFC 5280第4.2.1.6节：OtherName:：=SEQUENCE｛type id OBJECT IDENTIFIER，value[0]EXPLICIT ANY DEFINED BY type id｝
 */
typedef struct mbedtls_x509_san_other_name
{
    /**
     * type_id是RFC 5280中定义的OID。若要检查类型id的值，应使用带有已知OID MBEDTLS_x509_buf的\p MBEDTLS_OID_CMP。
     */
    mbedtls_x509_buf type_id;                   /**<类型id。*/
    union
    {
        /**
         * 来自RFC 4108第5节：硬件模块名称：：=序列｛hwType OBJECT IDENTIFIER，hwSerialNum八位字节字符串｝
         */
        struct
        {
            mbedtls_x509_buf oid;               /**<对象标识符。*/
            mbedtls_x509_buf val;               /**<命名值。*/
        }
        hardware_module_name;
    }
    value;
}
mbedtls_x509_san_other_name;

/**
 * 根据类型，用于保存已解析的Subject Alternative Name的结构
 */
typedef struct mbedtls_x509_subject_alternative_name
{
    int type;                              /**<SAN类型，MBEDTLS_X509_SAN_XXX的值。*/
    union {
        mbedtls_x509_san_other_name other_name; /**＜otherName支持的类型。*/
        mbedtls_x509_buf   unstructured_name; /**<未构造类型的缓冲区。当前仅支持dnsName*/
    }
    san; /**<支持的SAN类型的联合*/
}
mbedtls_x509_subject_alternative_name;

/**
 * 来自算法/曲线标识符（pk，md，ecp）的构建标志由于0总是XXX_NONE，因此忽略它。
 */
#define MBEDTLS_X509_ID_FLAG( id )   ( 1 << ( (id) - 1 ) )

/**
 * 证书验证的安全配置文件。
 *
 * 所有列表都是位字段，由MBEDTLS_X509_ID_FLAG（）中的“或”标志构建。
 */
typedef struct mbedtls_x509_crt_profile
{
    uint32_t allowed_mds;       /**<签名的MD*/
    uint32_t allowed_pks;       /**<签名的PK代数*/
    uint32_t allowed_curves;    /**<ECDSA的椭圆曲线*/
    uint32_t rsa_min_bitlen;    /**<RSA密钥的最小大小*/
}
mbedtls_x509_crt_profile;

#define MBEDTLS_X509_CRT_VERSION_1              0
#define MBEDTLS_X509_CRT_VERSION_2              1
#define MBEDTLS_X509_CRT_VERSION_3              2

#define MBEDTLS_X509_RFC5280_MAX_SERIAL_LEN 32
#define MBEDTLS_X509_RFC5280_UTC_TIME_LEN   15

#if !defined( MBEDTLS_X509_MAX_FILE_PATH_LEN )
#define MBEDTLS_X509_MAX_FILE_PATH_LEN 512
#endif

/**
 * 用于编写证书的容器（CRT）
 */
typedef struct mbedtls_x509write_cert
{
    int version;
    mbedtls_mpi serial;
    mbedtls_pk_context *subject_key;
    mbedtls_pk_context *issuer_key;
    mbedtls_asn1_named_data *subject;
    mbedtls_asn1_named_data *issuer;
    mbedtls_md_type_t md_alg;
    char not_before[MBEDTLS_X509_RFC5280_UTC_TIME_LEN + 1];
    char not_after[MBEDTLS_X509_RFC5280_UTC_TIME_LEN + 1];
    mbedtls_asn1_named_data *extensions;
}
mbedtls_x509write_cert;

/**
 * 验证链中的项目：证书及其标志
 */
typedef struct {
    mbedtls_x509_crt *crt;
    uint32_t flags;
} mbedtls_x509_crt_verify_chain_item;

/**
 * 验证链的最大大小：最终实体+中间实体+可信根
 */
#define MBEDTLS_X509_MAX_VERIFY_CHAIN_SIZE  ( MBEDTLS_X509_MAX_INTERMEDIATE_CA + 2 )

/**
 * 验证链由\c mbedtls_crt_verify_chain（）构建
 */
typedef struct
{
    mbedtls_x509_crt_verify_chain_item items[MBEDTLS_X509_MAX_VERIFY_CHAIN_SIZE];
    unsigned len;

#if defined(MBEDTLS_X509_TRUSTED_CERTIFICATE_CALLBACK)
    /* 它存储从用于CRT验证的CA回调获得的潜在可信签名者列表（如果配置）。我们必须在某处跟踪它，因为回调将其所有权传递给调用者。*/
    mbedtls_x509_crt *trust_ca_cb_result;
#endif /* MBEDTLS_X509_TRUSTED_CERTIFICATE_CALLBACK */
} mbedtls_x509_crt_verify_chain;

#if defined(MBEDTLS_ECDSA_C) && defined(MBEDTLS_ECP_RESTARTABLE)

/**
 * \恢复X.509验证操作的简短上下文
 */
typedef struct
{
    /* 用于check_signature（）*/
    mbedtls_pk_restart_ctx pk;

    /* 对于find_parent_in（）*/
    mbedtls_x509_crt *parent; /* 正在进行非空iff parent_in*/
    mbedtls_x509_crt *fallback_parent;
    int fallback_signature_is_good;

    /* 对于find_parent（）*/
    int parent_is_trusted; /* -如果find_parent未进行，则为1*/

    /* 用于verify_chain（）*/
    enum {
        x509_crt_rs_none,
        x509_crt_rs_find_parent,
    } in_progress;  /* 如果没有操作正在进行，则无*/
    int self_cnt;
    mbedtls_x509_crt_verify_chain ver_chain;

} mbedtls_x509_crt_restart_ctx;

#else /* MBEDTLS_ECDSA_C && MBEDTLS_ECP_RESTARTABLE */

/* 现在我们可以声明一个指向它的函数*/
typedef void mbedtls_x509_crt_restart_ctx;

#endif /* MBEDTLS_ECDSA_C && MBEDTLS_ECP_RESTARTABLE */

#if defined(MBEDTLS_X509_CRT_PARSE_C)
/**
 * 默认安全配置文件。应在安全性和与当前部署的兼容性之间提供良好的平衡。
 */
extern const mbedtls_x509_crt_profile mbedtls_x509_crt_profile_default;

/**
 * 应为下一个默认配置文件。建议用于新部署。目前的目标是128位安全级别，RSA-2048除外。
 */
extern const mbedtls_x509_crt_profile mbedtls_x509_crt_profile_next;

/**
 * NSA Suite B简介。
 */
extern const mbedtls_x509_crt_profile mbedtls_x509_crt_profile_suiteb;

/**
 * \简要分析单个DER格式的证书，并将其添加到所提供的链接列表的末尾。
 *
 * \param chain指向要附加到的CRT链起点的指针。在分析链中的第一个CRT时，该指针应指向通过mbedtls_x509_CRT_init（）初始化的：：mbedtls-x509_CRT的实例。\param buf保存DER编码证书的缓冲区。\param buflen \p buf的大小（以字节为单位）。
 *
 * \注意：此函数生成CRT缓冲区的内部副本。特别是，此调用返回后，\p buf可能会被销毁或重用。为了避免复制CRT缓冲区（以更严格的生存期约束为代价），请改用mbedtls_x509_CRT_parse_der_nocopy（）。
 *
 * \如果成功，返回\c 0。\失败时返回负错误代码。
 */
int mbedtls_x509_crt_parse_der( mbedtls_x509_crt *chain,
                                const unsigned char *buf,
                                size_t buflen );

/**
 * \brief证书扩展回调的类型。
 *
 *                 当mbedtls_x509_crt_parse_der_with_ext_cb（）例程遇到不支持的扩展或包含任何不支持的证书策略的“证书策略”扩展时，该类型的回调将传递给该例程并由其使用。如果需要，库的未来版本可能会在其他情况下调用回调。
 *
 * \param p_ctx传递给回调的不透明上下文。\param crt正在解析的证书。\param oid扩展的oid。\param critical扩展是否关键。\param p指向扩展值（八位字节字符串的内容）开头的指针。\param end扩展值的结尾。
 *
 * \注意：如果回调无法解析或不支持扩展，则回调必须失败并返回负错误代码。当回调无法解析关键扩展mbedtls_x509_crt_parse_der_with_ext_cb（）时，也会失败。当回调无法解析非关键扩展mbedtls_x509_crt_parse_der_with_ext_cb（）时，只需跳过扩展并继续解析。
 *
 * \成功时返回\c 0。\失败时返回负错误代码。
 */
typedef int (*mbedtls_x509_crt_ext_cb_t)( void *p_ctx,
                                          mbedtls_x509_crt const *crt,
                                          mbedtls_x509_buf const *oid,
                                          int critical,
                                          const unsigned char *p,
                                          const unsigned char *end );

/**
 * \简要分析单个DER格式的证书，并将其添加到所提供的链接列表的末尾。
 *
 * \param chain指向要附加到的CRT链起点的指针。在分析链中的第一个CRT时，该指针应指向通过mbedtls_x509_CRT_init（）初始化的：：mbedtls-x509_CRT的实例。\param buf保存DER编码证书的缓冲区。\param buflen \p buf的大小（以字节为单位）。\param make_copy当不为零时，此函数生成CRT缓冲区的内部副本。特别是，此调用返回后，\p buf可能会被销毁或重用。当为零时，此函数通过获取CRT缓冲区的临时所有权来避免复制CRT缓冲区，直到CRT被销毁（如mbedtls_x509_CRT_parse_der_nocopy（））\param cb为每个不受支持的证书扩展调用的回调。\param p_ctx传递给回调的不透明上下文。
 *
 * \注意：此调用在功能上等同于mbedtls_x509_crt_parse_der（）和/或mbedtls-x509_crt.parse_der_nocopy（），但它使用每个不受支持的证书扩展名调用回调，如果它包含任何不受支持证书策略，则还调用“证书策略”扩展名。如果回调不知道如何处理这样的扩展，它必须返回一个负错误代码。当回调无法解析关键扩展mbedtls_x509_crt_parse_der_with_ext_cb（）时，也会失败。当回调无法解析非关键扩展mbedtls_x509_crt_parse_der_with_ext_cb（）时，只需跳过扩展并继续解析。如果需要，库的未来版本可能会在其他情况下调用回调。
 *
 * \如果成功，返回\c 0。\失败时返回负错误代码。
 */
int mbedtls_x509_crt_parse_der_with_ext_cb( mbedtls_x509_crt *chain,
                                            const unsigned char *buf,
                                            size_t buflen,
                                            int make_copy,
                                            mbedtls_x509_crt_ext_cb_t cb,
                                            void *p_ctx );

/**
 * \简要分析单个DER格式的证书，并将其添加到所提供的链接列表的末尾。这是mbedtls_x509_crt_parse_der（）的一个变体，它在crt被销毁之前暂时拥有crt缓冲区的所有权。
 *
 * \param chain指向要附加到的CRT链起点的指针。在分析链中的第一个CRT时，该指针应指向通过mbedtls_x509_CRT_init（）初始化的：：mbedtls-x509_CRT的实例。\param buf保存要使用的DER编码证书的可读缓冲区的地址。成功后，必须保留此缓冲区，并且不能在CRT链的提升时间内更改，也就是说，直到通过调用mbedtls_x509_CRT_free（）销毁链。\param buflen \p buf的大小（以字节为单位）。
 *
 * \注意：此调用在功能上等同于mbedtls_x509_crt_parse_der（），但它避免了以更强的生存期约束为代价创建输入缓冲区的副本。这在不能容忍CRT复制的受限环境中非常有用。
 *
 * \如果成功，返回\c 0。\失败时返回负错误代码。
 */
int mbedtls_x509_crt_parse_der_nocopy( mbedtls_x509_crt *chain,
                                       const unsigned char *buf,
                                       size_t buflen );

/**
 * \简要分析一个DER编码的证书或一个或多个级联的PEM编码的证书，并将它们添加到链接列表中。
 *
 *                 对于PEM编码中的CRT，该函数允许解析：如果至少可以解析一个证书，则该函数返回解析失败的证书数（因此，如果所有证书都解析成功，则为0）。如果无法解析证书，则函数返回解析过程中遇到的第一个（否定）错误。
 *
 *                 PEM编码的证书可以与其他数据交织，例如其内容的人类可读描述，只要证书包含在PEM特定的“-{BEGIN/END}CERTIFICATE-----”分隔符中。
 *
 * \param chain要向其中添加已解析证书的链。\param buf以PEM或DER格式保存证书数据的缓冲区。对于PEM编码中的证书，这可能是多个证书的串联；对于DER编码，缓冲区必须正好包含一个证书。\param buflen缓冲区的大小，包括PEM编码数据的终止空字节。
 *
 * \如果成功解析了所有证书，则返回\c 0。\return如果解析部分成功，则无法解析的证书数（正数）（见上文）。\否则返回负X509或PEM错误代码。
 *
 */
int mbedtls_x509_crt_parse( mbedtls_x509_crt *chain, const unsigned char *buf, size_t buflen );

#if defined(MBEDTLS_FS_IO)
/**
 * \brief加载一个或多个证书并将其添加到链接列表中。允许分析。如果可以解析某些证书，则结果是遇到的失败证书数。如果没有正确完成，则返回第一个错误。
 *
 * \param chain指向要从中读取证书的链的开头\param路径文件名
 *
 * \如果成功解析了所有证书，则返回0；如果部分成功，则返回正数；或者返回特定的X509或PEM错误代码
 */
int mbedtls_x509_crt_parse_file( mbedtls_x509_crt *chain, const char *path );

/**
 * \brief从路径加载一个或多个证书文件，并将它们添加到链接列表中。允许分析。如果可以解析某些证书，则结果是遇到的失败证书数。如果没有正确完成，则返回第一个错误。
 *
 * \param chain指向要从中读取证书文件的链的开头\param path目录/文件夹
 *
 * \如果成功解析了所有证书，则返回0；如果部分成功，则返回正数；或者返回特定的X509或PEM错误代码
 */
int mbedtls_x509_crt_parse_path( mbedtls_x509_crt *chain, const char *path );

#endif /* MBEDTLS_FS_IO */
/**
 * \brief此函数解析SubjectAlternativeNames扩展中的项。
 *
 * \param san_buf保存主题备选名称的原始数据项的缓冲区。\param san要填充的目标结构，其中包含在\p san_raw中编码的主题替代名称的解析表示。
 *
 * \注意：仅支持RFC 4180中定义的hardware_module_name类型的“dnsName”和“otherName”。
 *
 * \注意：此函数应在主题替换名称的单个原始数据上调用。例如，在成功解析证书之后，必须迭代\pcrt->subject_alt_names序列中的每个项，并将其传递给此函数。
 *
 * \警告目标结构包含指向已解析证书的原始数据的指针，其生存期受证书生存期的限制。
 *
 * \成功时返回\c 0 \return#MBEDTLS_ERROR_X509_FEATURE_NAVAILABLE（对于不支持的SAN类型）。\返回任何其他失败的另一个负值。
 */
int mbedtls_x509_parse_subject_alt_name( const mbedtls_x509_buf *san_buf,
                                         mbedtls_x509_subject_alternative_name *san );
/**
 * \brief返回有关证书的信息字符串。
 *
 * \param buf要写入的缓冲区\param size缓冲区的最大大小\param prefix A行前缀\param crt要表示的X509证书
 *
 * \return所写字符串的长度（不包括终止的nul字节）或负错误代码。
 */
int mbedtls_x509_crt_info( char *buf, size_t size, const char *prefix,
                   const mbedtls_x509_crt *crt );

/**
 * \brief返回有关证书验证状态的信息字符串。
 *
 * \param buf要写入的缓冲区\param size缓冲区的最大大小\param prefix A行前缀\param flags mbedtls_x509_crt_verify（）创建的验证标志
 *
 * \return所写字符串的长度（不包括终止的nul字节）或负错误代码。
 */
int mbedtls_x509_crt_verify_info( char *buf, size_t size, const char *prefix,
                          uint32_t flags );

/**
 * \brief验证证书链。
 *
 *                 验证回调是用户提供的回调，可以清除/修改/添加证书的标志。如果设置了，将为链中的每个证书调用验证回调（从信任ca到呈现的crt）。回调的参数是：（void参数、mbedtls_x509_crt crt、int certificate_depth、int标志）。标志表示该特定证书的当前标志，以及从底部开始的证书深度（对等证书深度=0）。
 *
 *                 从回调返回后留下的所有标志也会返回到应用程序。对于除致命错误之外的任何情况（包括无效证书），函数都应返回0，因为非零返回代码会立即中止验证过程。对于致命错误，应使用特定的错误代码（不同于此时不应返回的MBEDTLS_error_X509_CERT_VERIFY_FAILED），或者如果没有更好的代码可用，则可以使用MBEDTLS_error_X509-ATAL_error。
 *
 * \注意：如果验证失败，可以使用\c mbedtls_x509_crt_verify_info（）显示结果
 *
 * \注意：与默认安全配置文件的\c mbedtls_x509_crt_verify_with_profile（）相同。
 *
 * \注意：您有责任为所有受信任的CA提供最新的CRL。如果没有为用于签署证书的CA提供CRL，则会自动跳过CRL验证，即不设置任何标志。
 *
 * \注意：\ctrust_ca列表可以包含两种类型的证书：（1）受信任的根ca的证书，这样链接到这些ca的证书将被信任；（2）要信任的自签名最终实体证书（对于您知道的特定对等方）-在这种情况下，自签名证书不需要设置ca位。
 *
 * \param crt要验证的证书链。\param trust_ca受信任ca的列表。\param ca_crl受信任ca的crl列表。\param cn预期的通用名称。这将被检查为存在于证书的subjectAltNames扩展中，如果没有此扩展，则作为其Subject名称中的CN组件。当前仅支持DNS名称。如果不需要验证CN，则此值可能为空。\param flags存储验证结果的地址。如果验证无法完成，则标志值设置为（uint32_t）-1。\param f_vrfy要使用的验证回调。有关详细信息，请参阅mbedtls_x509_crt_verify（）的文档。\param p_vrfy要传递给\p f_vrfy的上下文。
 *
 * \如果链对于传递的CN、CA、CRL和安全配置文件有效，则返回\c 0。\如果证书链验证失败，返回#MBEDTLS_ERROR_X509_CERT_VERIFY_FAILED。在这种情况下，\c标志将设置一个或多个\c MBEDTLS_X509_BADCERT_XXX或\c MBEDTLS_X509_BADC RL_XXX标志。\在验证过程中遇到致命错误时，返回另一个负错误代码。
 */
int mbedtls_x509_crt_verify( mbedtls_x509_crt *crt,
                     mbedtls_x509_crt *trust_ca,
                     mbedtls_x509_crl *ca_crl,
                     const char *cn, uint32_t *flags,
                     int (*f_vrfy)(void *, mbedtls_x509_crt *, int, uint32_t *),
                     void *p_vrfy );

/**
 * \brief根据可配置的安全配置文件验证证书链。
 *
 * \注意：与\c mbedtls_x509_crt_verify（）相同，但具有明确的安全配置文件。
 *
 * \注意：对密钥的限制（RSA最小大小、ECDSA允许的曲线）适用于所有证书：受信任的根证书、中间CA（如果有）和最终实体证书。
 *
 * \param crt要验证的证书链。\param trust_ca受信任ca的列表。\param ca_crl受信任ca的crl列表。\param profile用于验证的安全配置文件。\param cn预期的通用名称。如果不需要验证CN，则此值可能为空。\param flags存储验证结果的地址。如果验证无法完成，则标志值设置为（uint32_t）-1。\param f_vrfy要使用的验证回调。有关详细信息，请参阅mbedtls_x509_crt_verify（）的文档。\param p_vrfy要传递给\p f_vrfy的上下文。
 *
 * \如果链对于传递的CN、CA、CRL和安全配置文件有效，则返回\c 0。\如果证书链验证失败，返回#MBEDTLS_ERROR_X509_CERT_VERIFY_FAILED。在这种情况下，\c标志将设置一个或多个\c MBEDTLS_X509_BADCERT_XXX或\c MBEDTLS_X509_BADC RL_XXX标志。\在验证过程中遇到致命错误时，返回另一个负错误代码。
 */
int mbedtls_x509_crt_verify_with_profile( mbedtls_x509_crt *crt,
                     mbedtls_x509_crt *trust_ca,
                     mbedtls_x509_crl *ca_crl,
                     const mbedtls_x509_crt_profile *profile,
                     const char *cn, uint32_t *flags,
                     int (*f_vrfy)(void *, mbedtls_x509_crt *, int, uint32_t *),
                     void *p_vrfy );

/**
 * \\c mbedtls_crt_verify_with_profile（）的简短可重启版本
 *
 * \注意：执行与\c mbedtls_crt_verify_with_profile（）相同的作业，但可以提前返回并根据\c mbedt ls_ecp_set_max_ops（）设置的限制重新启动，以减少阻塞。
 *
 * \param crt要验证的证书链。\param trust_ca受信任ca的列表。\param ca_crl受信任ca的crl列表。\param profile用于验证的安全配置文件。\param cn预期的通用名称。如果不需要验证CN，则此值可能为空。\param flags存储验证结果的地址。如果验证无法完成，则标志值设置为（uint32_t）-1。\param f_vrfy要使用的验证回调。有关详细信息，请参阅mbedtls_x509_crt_verify（）的文档。\param p_vrfy要传递给\p f_vrfy的上下文。\param rs_ctx要使用的重新启动上下文。这可以设置为\c NULL以禁用可重新启动的ECC。
 *
 * \return请参见\c mbedtls_crt_verify_with_profile（），或者如果已达到最大操作数，请参见\return#mbedtls_ERROR_ECP_IN_PROGRESS：请参见\cmbedtls_ECP_set_max_ops（）。
 */
int mbedtls_x509_crt_verify_restartable( mbedtls_x509_crt *crt,
                     mbedtls_x509_crt *trust_ca,
                     mbedtls_x509_crl *ca_crl,
                     const mbedtls_x509_crt_profile *profile,
                     const char *cn, uint32_t *flags,
                     int (*f_vrfy)(void *, mbedtls_x509_crt *, int, uint32_t *),
                     void *p_vrfy,
                     mbedtls_x509_crt_restart_ctx *rs_ctx );

/**
 * \brief受信任证书回调的类型。
 *
 *                      当查找给定证书的可信签名者时，此类型的回调传递给CRT验证例程mbedtls_x509_CRT_verify_with_ca_cb（）并由其使用。
 *
 *                      成功后，回调将返回一个可信证书列表，这些证书将被视为输入证书的潜在签名者。
 *
 * \param p_ctx传递给回调的不透明上下文。\param child要搜索潜在签名者的证书。这将指向可读的证书。\param candidate_cas存储生成的候选签名者链接列表中第一个条目的地址的地址。这不会是空的。
 *
 * \注意：回调只能在出现致命错误时返回非零值。相反，如果对潜在签名者的搜索在没有单个候选项的情况下完成，则回调必须返回\c 0并将\c candidate_cas设置为\c NULL。
 *
 * \成功时返回\c 0。在本例中，\c*candidate_cas指向：：mbedtls_x509_crt的实例的堆分配链接列表，该列表的所有权将传递给调用者。\失败时返回负错误代码。
 */
typedef int (*mbedtls_x509_crt_ca_cb_t)( void *p_ctx,
                                         mbedtls_x509_crt const *child,
                                         mbedtls_x509_crt **candidate_cas );

#if defined(MBEDTLS_X509_TRUSTED_CERTIFICATE_CALLBACK)
/**
 * \\c mbedtls_x509_crt_verify_with_profile（）的简短版本，该版本使用回调获取受信任CA证书列表。
 *
 * \param crt要验证的证书链。\param f_ca_cb用于查询给定子证书的潜在签名者的回调。有关详细信息，请参阅：：mbedtls_x509_crt_ca_cb_t的文档。\param p_ca_cb要传递给\p f_ca_cb的不透明上下文。\param profile验证的安全配置文件。\param cn预期的通用名称。如果不需要验证CN，则此值可能为空。\param flags存储验证结果的地址。如果验证无法完成，则标志值设置为（uint32_t）-1。\param f_vrfy要使用的验证回调。有关详细信息，请参阅mbedtls_x509_crt_verify（）的文档。\param p_vrfy要传递给\p f_vrfy的上下文。
 *
 * \return请参见\c mbedtls_crt_verify_with_profile（）。
 */
int mbedtls_x509_crt_verify_with_ca_cb( mbedtls_x509_crt *crt,
                     mbedtls_x509_crt_ca_cb_t f_ca_cb,
                     void *p_ca_cb,
                     const mbedtls_x509_crt_profile *profile,
                     const char *cn, uint32_t *flags,
                     int (*f_vrfy)(void *, mbedtls_x509_crt *, int, uint32_t *),
                     void *p_vrfy );

#endif /* MBEDTLS_X509_TRUSTED_CERTIFICATE_CALLBACK */

#if defined(MBEDTLS_X509_CHECK_KEY_USAGE)
/**
 * \brief根据keyUsage扩展检查证书的用法。
 *
 * \param crt使用的叶证书。\param用法预期用途（例如使用证书执行RSA密钥交换之前的MBEDTLS_X509_KU_KEY_ENCIPHERMENT）。
 *
 * \注意：除了decisionOnly和encyperOnly之外，在用法参数中设置的位意味着必须在证书中设置该位。对于仅解密和仅加密，这意味着可以设置该位。
 *
 * \如果keyUsage扩展名存在但与用法参数不匹配，则返回0表示允许使用证书，MBEDTLS_ERROR_X509_BAD_INPUT_DATA。
 *
 * \注意：您只应在叶证书上调用此函数，在（中间）CA上，keyUsage扩展由\c mbedtls_x509_crt_verify（）自动检查。
 */
int mbedtls_x509_crt_check_key_usage( const mbedtls_x509_crt *crt,
                                      unsigned int usage );
#endif /* MBEDTLS_X509_CHECK_KEY_USAGE) */

#if defined(MBEDTLS_X509_CHECK_EXTENDED_KEY_USAGE)
/**
 * \brief对照extendedKeyUsage检查证书的用法。
 *
 * \param crt使用的叶证书。\param usage_oid预期用途（例如MBEDTLS_oid_SERVER_AUTH或MBEDTLS_oid_CLIENT_AUTH）。\param usage_len usage_oid的长度（例如由MBEDTLS_oid_SIZE（）给出）。
 *
 * \如果允许使用证书，则返回0；如果不允许，则返回MBEDTLS_ERROR_X509_BAD_INPUT_DATA。
 *
 * \注：通常只有叶证书才有意义。
 */
int mbedtls_x509_crt_check_extended_key_usage( const mbedtls_x509_crt *crt,
                                               const char *usage_oid,
                                               size_t usage_len );
#endif /* MBEDTLS_X509_CHECK_EXTENDED_KEY_USAGE */

#if defined(MBEDTLS_X509_CRL_PARSE_C)
/**
 * \brief验证证书吊销状态
 *
 * \param crt要验证的证书\param crl要验证的crl
 *
 * \如果证书被吊销，则返回1，否则返回0
 *
 */
int mbedtls_x509_crt_is_revoked( const mbedtls_x509_crt *crt, const mbedtls_x509_crl *crl );
#endif /* MBEDTLS_X509_CRL_PARSE_C */

/**
 * \brief初始化证书（链）
 *
 * \param crt要初始化的证书链
 */
void mbedtls_x509_crt_init( mbedtls_x509_crt *crt );

/**
 * \brief取消分配所有证书数据
 *
 * \param crt证书链释放
 */
void mbedtls_x509_crt_free( mbedtls_x509_crt *crt );

#if defined(MBEDTLS_ECDSA_C) && defined(MBEDTLS_ECP_RESTARTABLE)
/**
 * \brief初始化重新启动上下文
 */
void mbedtls_x509_crt_restart_init( mbedtls_x509_crt_restart_ctx *ctx );

/**
 * \brief释放重新启动上下文的组件
 */
void mbedtls_x509_crt_restart_free( mbedtls_x509_crt_restart_ctx *ctx );
#endif /* MBEDTLS_ECDSA_C && MBEDTLS_ECP_RESTARTABLE */
#endif /* MBEDTLS_X509_CRT_PARSE_C */

/* \}名称*/
/* \}添加组x509_模块*/

#if defined(MBEDTLS_X509_CRT_WRITE_C)
/**
 * \brief初始化CRT写入上下文
 *
 * \param ctx要初始化的CRT上下文
 */
void mbedtls_x509write_crt_init( mbedtls_x509write_cert *ctx );

/**
 * \brief设置证书默认版本：MBEDTLS_X509_CRT_VERSION_3
 *
 * \param ctx要使用的CRT上下文\param要设置的版本（MBEDTLS_X509_CRT_version_1、MBEDTLS_X509_CERT_version_2或MBEDTL_X509_CRT _version_3）
 */
void mbedtls_x509write_crt_set_version( mbedtls_x509write_cert *ctx, int version );

/**
 * \brief设置证书的序列号。
 *
 * \param ctx要使用的CRT上下文\param要设置的序列号
 *
 * \如果成功，则返回0
 */
int mbedtls_x509write_crt_set_serial( mbedtls_x509write_cert *ctx, const mbedtls_mpi *serial );

/**
 * \brief设置证书时间戳的有效期应为UTC时区的字符串格式，即“YYYYMMDDhhmmss”，例如2013年12月31日23:59:59的“20131231235959”
 *
 * \param ctx要使用的CRT上下文\param not_before-not_before-tstamp \param not_after not_after timestamp
 *
 * \如果时间戳解析成功，则返回0，或者返回特定的错误代码
 */
int mbedtls_x509write_crt_set_validity( mbedtls_x509write_cert *ctx, const char *not_before,
                                const char *not_after );

/**
 * \brief设置证书颁发者名称颁发者名称应包含以逗号分隔的OID类型和值列表：例如“C=UK，O=ARM，CN=mbed TLS CA”
 *
 * \param ctx要使用的CRT上下文\param issuer_name要设置的颁发者名称
 *
 * \如果成功解析了颁发者名称，则返回0，或者返回特定的错误代码
 */
int mbedtls_x509write_crt_set_issuer_name( mbedtls_x509write_cert *ctx,
                                   const char *issuer_name );

/**
 * \brief设置证书使用者名称使用者名称应包含以逗号分隔的OID类型和值列表：例如“C=UK，O=ARM，CN=mbed TLS Server 1”
 *
 * \param ctx要使用的CRT上下文\param subject_name要设置的主题名称
 *
 * \如果主题名称解析成功，则返回0，或者返回特定的错误代码
 */
int mbedtls_x509write_crt_set_subject_name( mbedtls_x509write_cert *ctx,
                                    const char *subject_name );

/**
 * \brief设置证书的主题公钥
 *
 * \param ctx CRT上下文以使用\param key公钥包含
 */
void mbedtls_x509write_crt_set_subject_key( mbedtls_x509write_cert *ctx, mbedtls_pk_context *key );

/**
 * \brief设置用于签名证书的颁发者密钥
 *
 * \param ctx要使用的CRT上下文\param key私钥进行签名
 */
void mbedtls_x509write_crt_set_issuer_key( mbedtls_x509write_cert *ctx, mbedtls_pk_context *key );

/**
 * \brief设置用于签名的MD算法（例如MBEDTLS_MD_SHA1）
 *
 * \param ctx要使用的CRT上下文\param md_alg要使用的md算法
 */
void mbedtls_x509write_crt_set_md_alg( mbedtls_x509write_cert *ctx, mbedtls_md_type_t md_alg );

/**
 * \在CRT中添加或替换扩展的简短通用函数
 *
 * \param ctx CRT上下文，如果扩展是关键的（根据RFC的定义），则使用扩展名的oid oid \param oid_len长度\param critical \param value of the extension OCET STRING \param val_len length of the value data
 *
 * \如果成功，则返回0，或者返回MBEDTLS_ERROR_X509_ALLOC_FAILED
 */
int mbedtls_x509write_crt_set_extension( mbedtls_x509write_cert *ctx,
                                 const char *oid, size_t oid_len,
                                 int critical,
                                 const unsigned char *val, size_t val_len );

/**
 * \brief为CRT设置basicConstraints扩展
 *
 * \param ctx要使用的CRT上下文\param is_ca这是ca证书吗\param max_pathlen此证书下面的证书链的最大长度（仅适用于ca证书，-1受限制）
 *
 * \如果成功，则返回0，或者返回MBEDTLS_ERROR_X509_ALLOC_FAILED
 */
int mbedtls_x509write_crt_set_basic_constraints( mbedtls_x509write_cert *ctx,
                                         int is_ca, int max_pathlen );

#if defined(MBEDTLS_SHA1_C)
/**
 * \brief设置CRT的subjectKeyIdentifier扩展名需要之前调用过mbedtls_x509write_CRT_Set_subject_key（）
 *
 * \param ctx要使用的CRT上下文
 *
 * \如果成功，则返回0，或者返回MBEDTLS_ERROR_X509_ALLOC_FAILED
 */
int mbedtls_x509write_crt_set_subject_key_identifier( mbedtls_x509write_cert *ctx );

/**
 * \brief为CRT设置authorityKeyIdentifier扩展要求之前已调用mbedtls_x509write_CRT_Set_issuer_key（）
 *
 * \param ctx要使用的CRT上下文
 *
 * \如果成功，则返回0，或者返回MBEDTLS_ERROR_X509_ALLOC_FAILED
 */
int mbedtls_x509write_crt_set_authority_key_identifier( mbedtls_x509write_cert *ctx );
#endif /* MBEDTLS_SHA1_C */

/**
 * \brief设置密钥使用扩展标志（例如MBEDTLS_X509_KU_DIGITAL_SIGNATURE|MBEDTLS_X509_KU_Key_CERT_SIGN）
 *
 * \param ctx要使用的CRT上下文\param key_usage要设置的密钥使用标志
 *
 * \如果成功，则返回0，或MBEDTLS_ERROR_X509_ALLOC_FAILED
 */
int mbedtls_x509write_crt_set_key_usage( mbedtls_x509write_cert *ctx,
                                         unsigned int key_usage );

/**
 * \brief设置Netscape证书类型标志（例如MBEDTLS_X509_NS_Cert_Type_SSL_CLIENT | MBEDTLS_X509_NS_Cert_Type-EMAIL）
 *
 * \param ctx要使用的CRT上下文\param ns_cert_type要设置的Netscape证书类型标志
 *
 * \如果成功，则返回0，或MBEDTLS_ERROR_X509_ALLOC_FAILED
 */
int mbedtls_x509write_crt_set_ns_cert_type( mbedtls_x509write_cert *ctx,
                                    unsigned char ns_cert_type );

/**
 * \brief释放CRT写入上下文的内容
 *
 * \param ctx要释放的CRT上下文
 */
void mbedtls_x509write_crt_free( mbedtls_x509write_cert *ctx );

/**
 * \brief将构建的证书写入X509 DER结构注意：数据写入缓冲区的末尾！使用返回值确定应该从何处开始使用缓冲区
 *
 * \param ctx证书要注销\param buf缓冲区要写入\param缓冲区大小\param f_rng rng函数（有关签名，请参阅注释）\param p_rng rng参数
 *
 * \如果成功，返回写入的数据长度，或返回特定的错误代码
 *
 * \如果RSA被用于签名并且签名被离线，则注释f_rng可以是NULL（否则f_rng是针对定时攻击的对策所需要的）。ECDSA签名始终需要非NULL f_rng。
 */
int mbedtls_x509write_crt_der( mbedtls_x509write_cert *ctx, unsigned char *buf, size_t size,
                       int (*f_rng)(void *, unsigned char *, size_t),
                       void *p_rng );

#if defined(MBEDTLS_PEM_WRITE_C)
/**
 * \brief将构建的证书写入X509 PEM字符串
 *
 * \param ctx证书要注销\param buf缓冲区要写入\param缓冲区大小\param f_rng rng函数（有关签名，请参阅注释）\param p_rng rng参数
 *
 * \如果成功，则返回0，或返回特定的错误代码
 *
 * \如果RSA被用于签名并且签名被离线，则注释f_rng可以是NULL（否则f_rng是针对定时攻击的对策所需要的）。ECDSA签名始终需要非NULL f_rng。
 */
int mbedtls_x509write_crt_pem( mbedtls_x509write_cert *ctx, unsigned char *buf, size_t size,
                       int (*f_rng)(void *, unsigned char *, size_t),
                       void *p_rng );
#endif /* MBEDTLS_PEM_WRITE_C */
#endif /* MBEDTLS_X509_CRT_WRITE_C */

#ifdef __cplusplus
}
#endif

#endif /* mbedtls_x509_crt.h文件*/

