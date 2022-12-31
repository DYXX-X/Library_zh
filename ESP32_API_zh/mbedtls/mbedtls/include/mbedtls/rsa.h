/**
 * \文件rsa.h
 *
 * \这个文件为RSA公钥密码系统提供了一个API。
 *
 * RSA公钥密码系统在《公钥密码标准（PKCS）#1 v1.5：RSA加密</em>》和《公钥密码规范（PKCS）#1 v2.1:RSA加密规范</em>中定义。
 *
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
#ifndef MBEDTLS_RSA_H
#define MBEDTLS_RSA_H

#if !defined(MBEDTLS_CONFIG_FILE)
#include "mbedtls/config.h"
#else
#include MBEDTLS_CONFIG_FILE
#endif

#include "mbedtls/bignum.h"
#include "mbedtls/md.h"

#if defined(MBEDTLS_THREADING_C)
#include "mbedtls/threading.h"
#endif

/*
 * RSA错误代码
 */
/**函数的输入参数错误。*/
#define MBEDTLS_ERR_RSA_BAD_INPUT_DATA                    -0x4080
/**输入数据包含无效填充并被拒绝。*/
#define MBEDTLS_ERR_RSA_INVALID_PADDING                   -0x4100
/**在生成密钥期间出现问题。*/
#define MBEDTLS_ERR_RSA_KEY_GEN_FAILED                    -0x4180
/**密钥未能通过库的有效性检查。*/
#define MBEDTLS_ERR_RSA_KEY_CHECK_FAILED                  -0x4200
/**公钥操作失败。*/
#define MBEDTLS_ERR_RSA_PUBLIC_FAILED                     -0x4280
/**私钥操作失败。*/
#define MBEDTLS_ERR_RSA_PRIVATE_FAILED                    -0x4300
/**PKCS#1验证失败。*/
#define MBEDTLS_ERR_RSA_VERIFY_FAILED                     -0x4380
/**用于解密的输出缓冲区不够大。*/
#define MBEDTLS_ERR_RSA_OUTPUT_TOO_LARGE                  -0x4400
/**随机生成器无法生成非零。*/
#define MBEDTLS_ERR_RSA_RNG_FAILED                        -0x4480

/* MBEDTLS_ERROR_RSA_UNSUPPORTED_OPERATION已弃用，不应使用。
 */
/**例如，由于安全违规或缺少功能，该实现不提供所请求的操作。*/
#define MBEDTLS_ERR_RSA_UNSUPPORTED_OPERATION             -0x4500

/* MBEDTLS_ERROR_RSA_HW_ACCEL_FAILED已弃用，不应使用。*/
/**RSA硬件加速器失败。*/
#define MBEDTLS_ERR_RSA_HW_ACCEL_FAILED                   -0x4580

/*
 * RSA常数
 */
#define MBEDTLS_RSA_PUBLIC      0 /**<请求私钥操作。*/
#define MBEDTLS_RSA_PRIVATE     1 /**<请求公钥操作。*/

#define MBEDTLS_RSA_PKCS_V15    0 /**<使用PKCS#1 v1.5编码。*/
#define MBEDTLS_RSA_PKCS_V21    1 /**<使用PKCS#1 v2.1编码。*/

#define MBEDTLS_RSA_SIGN        1 /**<RSA签名操作的标识符。*/
#define MBEDTLS_RSA_CRYPT       2 /**<RSA加密和解密操作的标识符。*/

#define MBEDTLS_RSA_SALT_LEN_ANY    -1

/*
 * 即使编译了RSA模块，也可以使用上述常量，例如用于PK层中的替代（PKCS#11）RSA实现。
 */

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(MBEDTLS_RSA_ALT)
// 定期实施
//

/**
 * \RSA上下文结构简介。
 *
 * \注意：不推荐直接操纵此结构的成员。所有操作都应该通过公共接口函数完成。
 */
typedef struct mbedtls_rsa_context
{
    int ver;                    /*!<  保留用于内部目的。不要在应用程序代码中设置此字段。其含义可能会在未经通知的情况下发生变化。*/
    size_t len;                 /*!<  \p N的大小（以字节为单位）。*/

    mbedtls_mpi N;              /*!<  公共模数。*/
    mbedtls_mpi E;              /*!<  公众指数。*/

    mbedtls_mpi D;              /*!<  私人指数。*/
    mbedtls_mpi P;              /*!<  第一个主要因素。*/
    mbedtls_mpi Q;              /*!<  第二个主要因素。*/

    mbedtls_mpi DP;             /*!<  <代码>D%（P-1）</code>。*/
    mbedtls_mpi DQ;             /*!<  <code>D%（Q-1）</code>。*/
    mbedtls_mpi QP;             /*!<  <代码>1/（Q%P）</code>。*/

    mbedtls_mpi RN;             /*!<  缓存<code>R^2 mod N</code>。*/

    mbedtls_mpi RP;             /*!<  缓存<code>R^2 mod P</code>。*/
    mbedtls_mpi RQ;             /*!<  缓存<code>R^2 mod Q</code>。*/

    mbedtls_mpi Vi;             /*!<  缓存的致盲值。*/
    mbedtls_mpi Vf;             /*!<  缓存的非盲值。*/

    int padding;                /*!< 选择填充模式：#MBEDTLS_RSA_PKCS_V15用于1.5填充，#MBEDTLS_RSA_PKCS_V21用于OAEP或PSS。*/
    int hash_id;                /*!< mbedtls_md_type_t类型的哈希标识符，在md.h中指定，用于EME-OAEP和EMSA-PSS编码中使用的MGF掩码生成函数。*/
#if defined(MBEDTLS_THREADING_C)
    /* 不变量：互斥体在iff ver！=时初始化0*/
    mbedtls_threading_mutex_t mutex;    /*!<  线程安全互斥锁。*/
#endif
}
mbedtls_rsa_context;

#else  /* MBEDTLS_RSA_ALT */
#include "rsa_alt.h"
#endif /* MBEDTLS_RSA_ALT */

/**
 * \brief此函数初始化RSA上下文。
 *
 * \注意：将RSAES-OAEP加密方案和RSASSA-PSS签名方案的填充设置为#MBEDTLS_RSA_PKCS_V21。
 *
 * \注意：使用#MBEDTLS_RSA_PKCS_V15填充时，将忽略\p hash_id参数。
 *
 * \注意：填充模式的选择对于私钥操作是严格执行的，因为混合填充模式可能存在安全问题。对于公钥操作，它是一个默认值，可以通过调用特定的\c rsa_saes_xxx或\c rses_sa_xxx函数来覆盖该值。
 *
 * \注意：\p hash_id中选择的哈希始终用于OEAP加密。对于PSS签名，它始终用于生成签名，但可以被覆盖以验证签名。如果设置为#MBEDTLS_MD_NONE，则始终覆盖它。
 *
 * \param ctx要初始化的RSA上下文。此值不能为空。\param padding要使用的填充模式。这必须是#MBEDTLS_RSA_PKCS_V15或#MBEDRLS_RSA_PKCS_V21。\param hash_id如果padding为#MBEDLLS_RSA_PSA_PKCS_V21，则为：：MBEDTLS_md_type_t类型的哈希标识符。否则不使用。
 */
void mbedtls_rsa_init( mbedtls_rsa_context *ctx,
                       int padding,
                       int hash_id );

/**
 * \brief此函数将一组核心参数导入到RSA上下文中。
 *
 * \注意：如果参数不同时存在，则可以为连续导入多次调用此函数。
 *
 *                 对该函数的任何调用序列之后都应调用mbedtls_rsa_complete（），该函数将检查并完成提供的信息，以备使用的公钥或私钥rsa密钥。
 *
 * \注意：请参阅mbedtls_rsa_complete（）以获取有关设置专用或公共rsa密钥所需参数的更多信息。
 *
 * \注意：导入的参数是复制的，不需要在设置的RSA上下文的生命周期内保留。
 *
 * \param ctx用于存储参数的初始化RSA上下文。\param N RSA模数。这可能是空的。\param P N的第一个素因子。这可能是空的。\param Q N的第二个素数。这可能是空。\param D私有指数。这可能是空的。\param E公共指数。这可能是空的。
 *
 * \成功时返回\c 0。\失败时返回非零错误代码。
 */
int mbedtls_rsa_import( mbedtls_rsa_context *ctx,
                        const mbedtls_mpi *N,
                        const mbedtls_mpi *P, const mbedtls_mpi *Q,
                        const mbedtls_mpi *D, const mbedtls_mpi *E );

/**
 * \brief此函数将原始大端二进制格式的核心RSA参数导入到RSA上下文中。
 *
 * \注意：如果参数不同时存在，则可以为连续导入多次调用此函数。
 *
 *                 对该函数的任何调用序列之后都应该调用mbedtls_rsa_complete（），它检查并完成提供的信息，以备使用的公钥或私钥rsa密钥。
 *
 * \注意：请参阅mbedtls_rsa_complete（）以获取有关设置专用或公共rsa密钥所需参数的更多信息。
 *
 * \注意：导入的参数是复制的，不需要在设置的RSA上下文的生命周期内保留。
 *
 * \param ctx用于存储参数的初始化RSA上下文。\param N RSA模数。这可能是空的。\param N_len N的字节长度；如果\p N==NULL，则忽略它。\param P N的第一个素因子。这可能是空的。\param P_len P的字节长度；如果\p p==NULL，则忽略它。\param Q N的第二个素数。这可能是空。\param Q_len Q的字节长度；如果\p Q==NULL，则忽略它。\param D私有指数。这可能是空的。\param D_len D的字节长度；如果\p D==NULL，则忽略该值。\param E公共指数。这可能是空的。\param E_len E的字节长度；如果\p E==NULL，则忽略该值。
 *
 * \成功时返回\c 0。\失败时返回非零错误代码。
 */
int mbedtls_rsa_import_raw( mbedtls_rsa_context *ctx,
                            unsigned char const *N, size_t N_len,
                            unsigned char const *P, size_t P_len,
                            unsigned char const *Q, size_t Q_len,
                            unsigned char const *D, size_t D_len,
                            unsigned char const *E, size_t E_len );

/**
 * \brief此函数从一组导入的核心参数中完成RSA上下文。
 *
 *                 要设置RSA公钥，必须精确地导入\p N和\p E。
 *
 *                 要设置RSA私钥，必须提供足够的信息才能导出其他参数。
 *
 *                 默认实现支持以下内容：＜ul＞＜li＞从\p N、\p D、\p E导出\p p、\p Q。
 *
 *                 如果此函数成功运行，它保证RSA上下文可以用于RSA操作，而不会出现故障或崩溃的风险。
 *
 * \警告此函数不需要对导入的参数执行一致性检查。特别是，实现不需要的参数可能会被默默丢弃并保持未选中状态。要检查密钥材料的一致性，请参见mbedtls_rsa_check_privkey（）。
 *
 * \param ctx保存导入参数的初始化RSA上下文。
 *
 * \成功时返回\c 0。\如果尝试的派生失败，则返回#MBEDTLS_ERROR_RSA_BAD_INPUT_DATA。
 *
 */
int mbedtls_rsa_complete( mbedtls_rsa_context *ctx );

/**
 * \brief此函数导出RSA密钥的核心参数。
 *
 *                 如果此函数成功运行，则由\p N、\p p、\p Q、\p D和\p E指向的非NULL缓冲区将被完全写入，并以零字节开头填充其他未使用的空间。
 *
 *                 返回#MBEDTLS_ERROR_PLATFORM_FEATURE_UNSUPPORTED的可能原因：＜ul＞＜li＞正在使用另一种RSA实现，它将密钥存储在外部，并且不能或不应该将其导出到RAM中</li><li>软件或硬件实施可能不支持某种扣除。例如，\p p、\p Q来自\p N、\p D和\p E，如果前者不是实现的一部分。</li></ul>
 *
 *                 如果函数由于不受支持的操作而失败，则RSA上下文将保持完整并保持可用。
 *
 * \param ctx初始化的RSA上下文。\param N保存RSA模数的MPI。如果不需要导出此字段，则该值可能为空。\param P保存N的第一个素因子的MPI。如果不需要导出此字段，则此值可能为空。\param Q保存N的第二个素数的MPI。如果不需要导出此字段，则此值可能为空。\param D保存私有指数的MPI。如果不需要导出此字段，则该值可能为空。\param E保存公共指数的MPI。如果不需要导出此字段，则该值可能为空。
 *
 * \成功时返回\c 0。\如果由于缺少功能或安全策略而无法导出请求的参数，则返回#MBEDTLS_ERROR_PLATFORM_FEATURE_UNSUPPORTED。\return任何其他失败时的非零返回代码。
 *
 */
int mbedtls_rsa_export( const mbedtls_rsa_context *ctx,
                        mbedtls_mpi *N, mbedtls_mpi *P, mbedtls_mpi *Q,
                        mbedtls_mpi *D, mbedtls_mpi *E );

/**
 * \brief此函数以原始大端二进制格式导出RSA密钥的核心参数。
 *
 *                 如果此函数成功运行，则由\p N、\p p、\p Q、\p D和\p E指向的非NULL缓冲区将被完全写入，并以零字节开头填充其他未使用的空间。
 *
 *                 返回#MBEDTLS_ERROR_PLATFORM_FEATURE_UNSUPPORTED的可能原因：＜ul＞＜li＞正在使用另一种RSA实现，它将密钥存储在外部，并且不能或不应该将其导出到RAM中</li><li>软件或硬件实施可能不支持某种扣除。例如，\p p、\p Q来自\p N、\p D和\p E，如果前者不是实现的一部分</li></ul>如果函数由于不受支持的操作而失败，则RSA上下文保持完整并保持可用。
 *
 * \注意：如果相应的缓冲区指针为NULL，则忽略长度参数。
 *
 * \param ctx初始化的RSA上下文。\param N存储RSA模数的Byte数组，如果不需要导出此字段，则为空。\param N_len模数缓冲区的大小。\param P用于保存\P N的第一个素数的Byte数组，如果不需要导出此字段，则为空。\param P_len第一个素数的缓冲区大小。\param Q用于保存第二个素数\p N的Byte数组，如果不需要导出此字段，则为空。\param Q_len第二个素数的缓冲区大小。\param D保存私有指数的Byte数组，如果不需要导出此字段，则为空。\param D_len专用指数的缓冲区大小。\param E保存公共指数的Byte数组，如果不需要导出此字段，则为空。\param E_len公共指数的缓冲区大小。
 *
 * \成功时返回\c 0。\如果由于缺少功能或安全策略而无法导出请求的参数，则返回#MBEDTLS_ERROR_PLATFORM_FEATURE_UNSUPPORTED。\return任何其他失败时的非零返回代码。
 */
int mbedtls_rsa_export_raw( const mbedtls_rsa_context *ctx,
                            unsigned char *N, size_t N_len,
                            unsigned char *P, size_t P_len,
                            unsigned char *Q, size_t Q_len,
                            unsigned char *D, size_t D_len,
                            unsigned char *E, size_t E_len );

/**
 * \brief此函数导出专用RSA密钥的CRT参数。
 *
 * \注意：内部不使用CRT参数的可选RSA实现可以基于mbedtls_RSA_deduce_opt（）实现此函数。
 *
 * \param ctx初始化的RSA上下文。\param DP用于保存D模“P-1”的MPI，如果不需要导出，则为NULL。\param DQ用于保存模数“Q-1”的MPI，如果不需要导出，则为NULL。\param QP用于保存\c Q modulo \c P的模逆的MPI，如果不需要导出，则为空。
 *
 * \成功时返回\c 0。\失败时返回非零错误代码。
 *
 */
int mbedtls_rsa_export_crt( const mbedtls_rsa_context *ctx,
                            mbedtls_mpi *DP, mbedtls_mpi *DQ, mbedtls_mpi *QP );

/**
 * \brief此函数为已初始化的RSA上下文设置填充。有关详细信息，请参见mbedtls_rsa_init（）。
 *
 * \param ctx要配置的初始化RSA上下文。\param padding要使用的填充模式。这必须是#MBEDTLS_RSA_PKCS_V15或#MBEDLLS_RSA_PKCS_V21。\param hash_id#MBEDRLS_RSA_PQCS_V21哈希标识符。
 */
void mbedtls_rsa_set_padding( mbedtls_rsa_context *ctx, int padding,
                              int hash_id );

/**
 * \brief此函数以字节为单位检索RSA模数的长度。
 *
 * \param ctx初始化的RSA上下文。
 *
 * \return RSA模数的长度（以字节为单位）。
 *
 */
size_t mbedtls_rsa_get_len( const mbedtls_rsa_context *ctx );

/**
 * \brief此函数生成RSA密钥对。
 *
 * \注意，要设置rsa上下文，必须在该函数之前调用mbedtls_rsa_init（）。
 *
 * \param ctx用于保存密钥的初始化RSA上下文。\param f_rng用于密钥生成的rng函数。此值不能为空。\param p_rng要传递给\p f_rng的rng上下文。如果\p f_rng不需要上下文，则该值可能为\c NULL。\param nbits公钥的大小（以位为单位）。\param指数要使用的公共指数。例如，\c 65537。这必须是奇数，并且大于\c 1。
 *
 * \成功时返回\c 0。\失败时返回\c MBEDTLS_error_RSA_XXX错误代码。
 */
int mbedtls_rsa_gen_key( mbedtls_rsa_context *ctx,
                         int (*f_rng)(void *, unsigned char *, size_t),
                         void *p_rng,
                         unsigned int nbits, int exponent );

/**
 * \brief此函数检查上下文是否至少包含RSA公钥。
 *
 *                 如果函数成功运行，则可以保证有足够的信息来使用mbedtls_RSA_public（）执行RSA公钥操作。
 *
 * \param ctx要检查的初始化RSA上下文。
 *
 * \成功时返回\c 0。\失败时返回\c MBEDTLS_error_RSA_XXX错误代码。
 *
 */
int mbedtls_rsa_check_pubkey( const mbedtls_rsa_context *ctx );

/**
 * \brief此函数检查上下文是否包含RSA私钥，并执行基本一致性检查。
 *
 * \注意：此函数执行的一致性检查不仅确保可以在给定上下文中成功调用mbedtls_rsa_private（），而且各种参数很可能相互一致，因为mbedtls_rsa_prublic（）和mbedtls.rsa_privaate（）是相反的。
 *
 * \警告：此函数应捕捉意外的错误配置，如参数交换，但它无法对用于设置给定RSA上下文的密钥材料的质量和一致性建立完全信任：＜ul＞＜li＞一致性：导入的与实现无关的参数可能会被默默丢弃。如果删除，则当前函数无法访问它们，因此无法检查它们。请参见mbedtls_rsa_complete（）。例如，如果要检查PKCS1编码的RSA私钥的整个内容的一致性，则应在设置RSA上下文之前使用mbedtls_RSA_validate_params（）。此外，如果实施执行了实证检查，这些检查可以证实但不能保证一致性</li><li>质量：该功能预计不会执行扩展的质量评估，如检查主要因素是否安全。此外，用户有责任确保其RSA参数源的可靠性，这超出了库可以有效检查的范围。</li></ul>
 *
 * \param ctx要检查的初始化RSA上下文。
 *
 * \成功时返回\c 0。\失败时返回\c MBEDTLS_error_RSA_XXX错误代码。
 */
int mbedtls_rsa_check_privkey( const mbedtls_rsa_context *ctx );

/**
 * \brief此函数检查公私RSA密钥对。
 *
 *                 它检查每个上下文，并确保它们匹配。
 *
 * \param pub保存公钥的初始化RSA上下文。\param prv保存私钥的初始化RSA上下文。
 *
 * \成功时返回\c 0。\失败时返回\c MBEDTLS_error_RSA_XXX错误代码。
 */
int mbedtls_rsa_check_pub_priv( const mbedtls_rsa_context *pub,
                                const mbedtls_rsa_context *prv );

/**
 * \brief此函数执行RSA公钥操作。
 *
 * \param ctx要使用的初始化RSA上下文。\param input输入缓冲区。这必须是长度为\c ctx->len Bytes的可读缓冲区。例如，对于2048位RSA模数，\c 256字节。\param output输出缓冲区。这必须是长度为\c ctx->len Bytes的可写缓冲区。例如，对于2048位RSA模数，\c 256字节。
 *
 * \注意：此函数不处理消息填充。
 *
 * \注意：请确保将\p input[0]设置为0或确保input小于\p N。
 *
 * \成功时返回\c 0。\失败时返回\c MBEDTLS_error_RSA_XXX错误代码。
 */
int mbedtls_rsa_public( mbedtls_rsa_context *ctx,
                const unsigned char *input,
                unsigned char *output );

/**
 * \brief此函数执行RSA私钥操作。
 *
 * \注：当且仅当提供PRNG时，使用盲板。
 *
 * \注意：如果使用盲法，指数的基数和指数都将被盲法，从而防止某些侧信道攻击。
 *
 * \警告不推荐在此处提供PRNG，从而防止使用盲板。未来版本的库可能会强制存在PRNG。
 *
 * \param ctx要使用的初始化RSA上下文。\param f_rng用于致盲的rng函数。不鼓励并不推荐在此处传递\c NULL，在这种情况下，将省略盲板。\param p_rng要传递给\p f_rng的rng上下文。如果\p f_rng为\c NULL或\p f.rng不需要上下文，则该值可能为\c空。\param input输入缓冲区。这必须是长度为\c ctx->len Bytes的可读缓冲区。例如，对于2048位RSA模数，\c 256字节。\param output输出缓冲区。这必须是长度为\c ctx->len Bytes的可写缓冲区。例如，对于2048位RSA模数，\c 256字节。
 *
 * \成功时返回\c 0。\失败时返回\c MBEDTLS_error_RSA_XXX错误代码。
 *
 */
int mbedtls_rsa_private( mbedtls_rsa_context *ctx,
                 int (*f_rng)(void *, unsigned char *, size_t),
                 void *p_rng,
                 const unsigned char *input,
                 unsigned char *output );

/**
 * \brief此函数添加消息填充，然后执行RSA操作。
 *
 *                 它是使用上下文中的\p模式执行PKCS#1加密操作的通用包装。
 *
 * \不推荐在#MBEDTLS_RSA_PRIVATE模式下调用此函数。库的未来版本可能会删除\p mode参数，并将其隐式设置为#MBEDTLS_RSA_PUBLIC。
 *
 * \注意：RSA的替代实现不需要支持将模式设置为#MBEDTLS_RSA_PRIVATE，而是可以返回#MBEDLLS_ERROR_PLATFORM_FEATURE_UNSUPPORTED。
 *
 * \param ctx要使用的初始化RSA上下文。\param f_rng要使用的rng。对于PKCS#1 v2.1填充编码和PKCS#1 v1.5填充编码，当使用\p模式设置为#MBEDTLS_RSA_PUBLIC时，它是必需的。对于PKCS#1 v1.5填充编码和\p模式设置为#MBEDTLS_RSA_PRIVATE，它用于致盲，在这种情况下应提供；有关详细信息，请参阅mbedtls_rsa_private（）。\param p_rng要传递给\p f_rng的rng上下文。如果\p f_rng为\c NULL或\p f.rng不需要上下文参数，则可能为\c空。\param mode操作模式。必须是#MBEDTLS_RSA_PUBLIC或#MBEDLLS_RSA_PRIVATE（已弃用）。\param ilen明文的长度（以字节为单位）。\param input要加密的输入数据。这必须是大小为\pilen Bytes的可读缓冲区。如果“ilen==0”，则可能为\c NULL。\param output输出缓冲区。这必须是长度为\c ctx->len Bytes的可写缓冲区。例如，对于2048位RSA模数，\c 256字节。
 *
 * \成功时返回\c 0。\失败时返回\c MBEDTLS_error_RSA_XXX错误代码。
 */
int mbedtls_rsa_pkcs1_encrypt( mbedtls_rsa_context *ctx,
                       int (*f_rng)(void *, unsigned char *, size_t),
                       void *p_rng,
                       int mode, size_t ilen,
                       const unsigned char *input,
                       unsigned char *output );

/**
 * \brief此函数执行PKCS#1 v1.5加密操作（RSAES-PKCS1-v1_5-ENCRYPT）。
 *
 * \不推荐在#MBEDTLS_RSA_PRIVATE模式下调用此函数。库的未来版本可能会删除\p mode参数，并将其隐式设置为#MBEDTLS_RSA_PUBLIC。
 *
 * \注意：RSA的替代实现不需要支持将模式设置为#MBEDTLS_RSA_PRIVATE，而是可以返回#MBEDLLS_ERROR_PLATFORM_FEATURE_UNSUPPORTED。
 *
 * \param ctx要使用的初始化RSA上下文。\param f_rng要使用的rng函数。如果\p模式为#MBEDTLS_RSA_PUBLIC，则需要生成填充。如果\p模式为#MBEDTLS_RSA_PRIVATE（不鼓励），则该模式用于致盲，应提供；请参见mbedtls_rsa_private（）。\param p_rng要传递给\p f_rng的rng上下文。如果\p f_rng为\c NULL或\p f.rng不需要上下文参数，则该值可能为\c空。\param mode操作模式。必须是#MBEDTLS_RSA_PUBLIC或#MBEDLLS_RSA_PRIVATE（已弃用）。\param ilen明文的长度（以字节为单位）。\param input要加密的输入数据。这必须是大小为\pilen Bytes的可读缓冲区。如果“ilen==0”，则可能为\c NULL。\param output输出缓冲区。这必须是长度为\c ctx->len Bytes的可写缓冲区。例如，对于2048位RSA模数，\c 256字节。
 *
 * \成功时返回\c 0。\失败时返回\c MBEDTLS_error_RSA_XXX错误代码。
 */
int mbedtls_rsa_rsaes_pkcs1_v15_encrypt( mbedtls_rsa_context *ctx,
                                 int (*f_rng)(void *, unsigned char *, size_t),
                                 void *p_rng,
                                 int mode, size_t ilen,
                                 const unsigned char *input,
                                 unsigned char *output );

/**
 * \brief此函数执行PKCS#1 v2.1 OAEP加密操作（RSAES-OAEP-ENCRYPT）。
 *
 * \注意输出缓冲区必须与ctx->N的大小一样大。例如，如果使用RSA-1024，则为128字节。
 *
 * \不推荐在#MBEDTLS_RSA_PRIVATE模式下调用此函数。库的未来版本可能会删除\p mode参数，并将其隐式设置为#MBEDTLS_RSA_PUBLIC。
 *
 * \注意：RSA的替代实现不需要支持将模式设置为#MBEDTLS_RSA_PRIVATE，而是可以返回#MBEDLLS_ERROR_PLATFORM_FEATURE_UNSUPPORTED。
 *
 * \param ctx要使用的初始化RSA上下文。\param f_rng要使用的rng函数。这是生成填充所需的，必须提供。\param p_rng要传递给\p f_rng的rng上下文。如果\p f_rng不需要上下文参数，则该值可能为\c NULL。\param mode操作模式。必须是#MBEDTLS_RSA_PUBLIC或#MBEDLLS_RSA_PRIVATE（已弃用）。\param label保存要使用的自定义标签的缓冲区。这必须是长度为\p label_len Bytes的可读缓冲区。如果\p label_len为\c 0，则可能为\c NULL。\param label_llen标签的长度（以字节为单位）。\param ilen明文缓冲区输入的长度（字节）。\param input要加密的输入数据。这必须是大小为\pilen Bytes的可读缓冲区。如果“ilen==0”，则可能为\c NULL。\param output输出缓冲区。这必须是长度为\c ctx->len Bytes的可写缓冲区。例如，对于2048位RSA模数，\c 256字节。
 *
 * \成功时返回\c 0。\失败时返回\c MBEDTLS_error_RSA_XXX错误代码。
 */
int mbedtls_rsa_rsaes_oaep_encrypt( mbedtls_rsa_context *ctx,
                            int (*f_rng)(void *, unsigned char *, size_t),
                            void *p_rng,
                            int mode,
                            const unsigned char *label, size_t label_len,
                            size_t ilen,
                            const unsigned char *input,
                            unsigned char *output );

/**
 * \brief此函数执行RSA操作，然后删除消息填充。
 *
 *                 它是使用上下文中的\p模式执行PKCS#1解密操作的通用包装器。
 *
 * \注意：输出缓冲区长度\coutput_max_len应与大小\p ctx->len of \p ctx->N一样大（例如，如果使用RSA-1024，则为128字节），以便能够保存任意解密的消息。如果其大小不足以保存所提供的特定密文的解密，则函数将返回\c MBEDTLS_ERROR_RSA_OUTPUT_TOO_large。
 *
 * \不推荐在#MBEDTLS_RSA_PUBLIC模式下调用此函数。库的未来版本可能会删除\p mode参数，并将其隐式设置为#MBEDTLS_RSA_PRIVATE。
 *
 * \注意：RSA的替代实现不需要支持将模式设置为#MBEDTLS_RSA_PUBLIC，而是可以返回#MBEDLLS_ERROR_PLATFORM_FEATURE_UNSUPPORTED。
 *
 * \param ctx要使用的初始化RSA上下文。\param f_rng rng函数。如果\p模式为#MBEDTLS_RSA_PRIVATE，则该模式用于致盲，应提供；有关详细信息，请参阅mbedtls_rsa_private（）。如果\p模式为#MBEDTLS_RSA_PUBLIC，则忽略该模式。\param p_rng要传递给\p f_rng的rng上下文。如果\p f_rng为空或不需要上下文，则可能为空。\param mode操作模式。必须是#MBEDTLS_RSA_PRIVATE或#MBEDLLS_RSA_PUBLIC（已弃用）。\param olen存储明文长度的地址。此值不能为空。\param input密文缓冲区。这必须是长度为\c ctx->len Bytes的可读缓冲区。例如，对于2048位RSA模数，\c 256字节。\param output用于保存明文的缓冲区。这必须是长度为\p output_max_len Bytes的可写缓冲区。\param output_max_len输出缓冲区\p输出的长度（以字节为单位）。
 *
 * \成功时返回\c 0。\失败时返回\c MBEDTLS_error_RSA_XXX错误代码。
 */
int mbedtls_rsa_pkcs1_decrypt( mbedtls_rsa_context *ctx,
                       int (*f_rng)(void *, unsigned char *, size_t),
                       void *p_rng,
                       int mode, size_t *olen,
                       const unsigned char *input,
                       unsigned char *output,
                       size_t output_max_len );

/**
 * \brief此函数执行PKCS#1 v1.5解密操作（RSAES-PKCS1-v1_5-DECRYPT）。
 *
 * \注意：输出缓冲区长度\coutput_max_len应与大小\p ctx->len of \p ctx->N一样大，例如，如果使用RSA-1024，则为128字节，以便能够保存任意解密的消息。如果它不足以保存所提供的特定密文的解密，则函数返回#MBEDTLS_ERROR_RSA_OUTPUT_TOO_large。
 *
 * \不推荐在#MBEDTLS_RSA_PUBLIC模式下调用此函数。库的未来版本可能会删除\p mode参数，并将其隐式设置为#MBEDTLS_RSA_PRIVATE。
 *
 * \注意：RSA的替代实现不需要支持将模式设置为#MBEDTLS_RSA_PUBLIC，而是可以返回#MBEDLLS_ERROR_PLATFORM_FEATURE_UNSUPPORTED。
 *
 * \param ctx要使用的初始化RSA上下文。\param f_rng rng函数。如果\p模式为#MBEDTLS_RSA_PRIVATE，则该模式用于致盲，应提供；有关详细信息，请参阅mbedtls_rsa_private（）。如果\p模式为#MBEDTLS_RSA_PUBLIC，则忽略该模式。\param p_rng要传递给\p f_rng的rng上下文。如果\p f_rng为空或不需要上下文，则可能为空。\param mode操作模式。必须是#MBEDTLS_RSA_PRIVATE或#MBEDLLS_RSA_PUBLIC（已弃用）。\param olen存储明文长度的地址。此值不能为空。\param input密文缓冲区。这必须是长度为\c ctx->len Bytes的可读缓冲区。例如，对于2048位RSA模数，\c 256字节。\param output用于保存明文的缓冲区。这必须是长度为\p output_max_len Bytes的可写缓冲区。\param output_max_len输出缓冲区\p输出的长度（以字节为单位）。
 *
 * \成功时返回\c 0。\失败时返回\c MBEDTLS_error_RSA_XXX错误代码。
 *
 */
int mbedtls_rsa_rsaes_pkcs1_v15_decrypt( mbedtls_rsa_context *ctx,
                                 int (*f_rng)(void *, unsigned char *, size_t),
                                 void *p_rng,
                                 int mode, size_t *olen,
                                 const unsigned char *input,
                                 unsigned char *output,
                                 size_t output_max_len );

/**
 * \brief此函数执行PKCS#1 v2.1 OAEP解密操作（RSAES-OAEP-DECRYPT）。
 *
 * \注意：输出缓冲区长度\coutput_max_len应与大小\p ctx->len of \p ctx->N一样大，例如，如果使用RSA-1024，则为128字节，以便能够保存任意解密的消息。如果它不足以保存所提供的特定密文的解密，则函数返回#MBEDTLS_ERROR_RSA_OUTPUT_TOO_large。
 *
 * \不推荐在#MBEDTLS_RSA_PUBLIC模式下调用此函数。库的未来版本可能会删除\p mode参数，并将其隐式设置为#MBEDTLS_RSA_PRIVATE。
 *
 * \注意：RSA的替代实现不需要支持将模式设置为#MBEDTLS_RSA_PUBLIC，而是可以返回#MBEDLLS_ERROR_PLATFORM_FEATURE_UNSUPPORTED。
 *
 * \param ctx要使用的初始化RSA上下文。\param f_rng rng函数。如果\p模式为#MBEDTLS_RSA_PRIVATE，则该模式用于致盲，应提供；有关详细信息，请参阅mbedtls_rsa_private（）。如果\p模式为#MBEDTLS_RSA_PUBLIC，则忽略该模式。\param p_rng要传递给\p f_rng的rng上下文。如果\p f_rng为空或不需要上下文，则可能为空。\param mode操作模式。必须是#MBEDTLS_RSA_PRIVATE或#MBEDLLS_RSA_PUBLIC（已弃用）。\param label保存要使用的自定义标签的缓冲区。这必须是长度为\p label_len Bytes的可读缓冲区。如果\p label_len为\c 0，则可能为\c NULL。\param label_llen标签的长度（以字节为单位）。\param olen存储明文长度的地址。此值不能为空。\param input密文缓冲区。这必须是长度为\c ctx->len Bytes的可读缓冲区。例如，对于2048位RSA模数，\c 256字节。\param output用于保存明文的缓冲区。这必须是长度为\p output_max_len Bytes的可写缓冲区。\param output_max_len输出缓冲区\p输出的长度（以字节为单位）。
 *
 * \成功时返回\c 0。\失败时返回\c MBEDTLS_error_RSA_XXX错误代码。
 */
int mbedtls_rsa_rsaes_oaep_decrypt( mbedtls_rsa_context *ctx,
                            int (*f_rng)(void *, unsigned char *, size_t),
                            void *p_rng,
                            int mode,
                            const unsigned char *label, size_t label_len,
                            size_t *olen,
                            const unsigned char *input,
                            unsigned char *output,
                            size_t output_max_len );

/**
 * \brief此函数执行专用RSA操作，以使用PKCS#1签署消息摘要。
 *
 *                 它是使用上下文中的\p模式执行PKCS#1签名的通用包装器。
 *
 * \注意\p sig缓冲区必须与\p ctx->N的大小一样大。例如，如果使用RSA-1024，则为128字节。
 *
 * \注意：对于PKCS#1 v2.1编码，有关\p md_alg和\p hash_id的详细信息，请参阅mbedtls_rsa_rsassa_pss_sign（）上的注释。
 *
 * \不推荐在#MBEDTLS_RSA_PUBLIC模式下调用此函数。库的未来版本可能会删除\p mode参数，并将其隐式设置为#MBEDTLS_RSA_PRIVATE。
 *
 * \注意：RSA的替代实现不需要支持将模式设置为#MBEDTLS_RSA_PUBLIC，而是可以返回#MBEDLLS_ERROR_PLATFORM_FEATURE_UNSUPPORTED。
 *
 * \param ctx要使用的初始化RSA上下文。\param f_rng要使用的rng函数。如果填充模式是PKCS#1 v2.1，则必须提供此选项。如果填充模式是PKCS#1 v1.5，而\p模式是#MBEDTLS_RSA_PRIVATE，则它用于致盲，应提供；有关详细信息，请参阅mbedtls_rsa_private（）。否则将忽略它。\param p_rng要传递给\p f_rng的rng上下文。如果\p f_rng为空或不需要上下文参数，则该值可能为空。\param mode操作模式。必须是#MBEDTLS_RSA_PRIVATE或#MBEDLLS_RSA_PUBLIC（已弃用）。\param md_alg用于哈希原始数据的消息摘要算法。使用#MBEDTLS_MD_NONE对原始数据进行签名。\param hashlen消息摘要的长度。只有当\p md_alg为#MBEDTLS_md_NONE时，才使用Ths。\param hash保存消息摘要或原始数据的缓冲区。如果\p md_alg为#MBEDTLS_md_NONE，则这必须是长度为\p hashlen Bytes的可读缓冲区。如果\p md_alg不是#MBEDTLS_md_NONE，则它必须是一个可读缓冲区，其长度必须与\p md_alg对应的哈希大小相同。\param sig保存签名的缓冲区。这必须是长度为\c ctx->len Bytes的可写缓冲区。例如，对于2048位RSA模数，\c 256字节。缓冲区长度#MBEDTLS_MPI_MAX_SIZE始终是安全的。
 *
 * \如果签名操作成功，则返回\c 0。\失败时返回\c MBEDTLS_error_RSA_XXX错误代码。
 */
int mbedtls_rsa_pkcs1_sign( mbedtls_rsa_context *ctx,
                    int (*f_rng)(void *, unsigned char *, size_t),
                    void *p_rng,
                    int mode,
                    mbedtls_md_type_t md_alg,
                    unsigned int hashlen,
                    const unsigned char *hash,
                    unsigned char *sig );

/**
 * \brief此函数执行PKCS#1 v1.5签名操作（RSASSA-PKS1-v1_5-SIGN）。
 *
 * \不推荐在#MBEDTLS_RSA_PUBLIC模式下调用此函数。库的未来版本可能会删除\p mode参数，并将其隐式设置为#MBEDTLS_RSA_PRIVATE。
 *
 * \注意：RSA的替代实现不需要支持将模式设置为#MBEDTLS_RSA_PUBLIC，而是可以返回#MBEDLLS_ERROR_PLATFORM_FEATURE_UNSUPPORTED。
 *
 * \param ctx要使用的初始化RSA上下文。\param f_rng rng函数。如果\p模式为#MBEDTLS_RSA_PRIVATE，则该模式用于致盲，应提供；有关详细信息，请参阅mbedtls_rsa_private（）。如果\p模式为#MBEDTLS_RSA_PUBLIC，则忽略该模式。\param p_rng要传递给\p f_rng的rng上下文。如果\p f_rng为空或不需要上下文参数，则该值可能为空。\param mode操作模式。必须是#MBEDTLS_RSA_PRIVATE或#MBEDLLS_RSA_PUBLIC（已弃用）。\param md_alg用于哈希原始数据的消息摘要算法。使用#MBEDTLS_MD_NONE对原始数据进行签名。\param hashlen消息摘要的长度。只有当\p md_alg为#MBEDTLS_md_NONE时，才使用Ths。\param hash保存消息摘要或原始数据的缓冲区。如果\p md_alg为#MBEDTLS_md_NONE，则这必须是长度为\p hashlen Bytes的可读缓冲区。如果\p md_alg不是#MBEDTLS_md_NONE，则它必须是一个可读缓冲区，其长度必须与\p md_alg对应的哈希大小相同。\param sig保存签名的缓冲区。这必须是长度为\c ctx->len Bytes的可写缓冲区。例如，对于2048位RSA模数，\c 256字节。缓冲区长度#MBEDTLS_MPI_MAX_SIZE始终是安全的。
 *
 * \如果签名操作成功，则返回\c 0。\失败时返回\c MBEDTLS_error_RSA_XXX错误代码。
 */
int mbedtls_rsa_rsassa_pkcs1_v15_sign( mbedtls_rsa_context *ctx,
                               int (*f_rng)(void *, unsigned char *, size_t),
                               void *p_rng,
                               int mode,
                               mbedtls_md_type_t md_alg,
                               unsigned int hashlen,
                               const unsigned char *hash,
                               unsigned char *sig );

/**
 * \brief此函数执行PKCS#1 v2.1 PSS签名操作（RSASSA-PS-SIGN）。
 *
 * \注意：在\p ctx中设置的\chash_id（当调用mbedtls_rsa_init（）或随后调用mbedtls _rsa_set_padding（）时）选择用于编码操作和掩码生成函数（MGF1）的哈希。有关编码操作和掩码生成功能的更多详细信息，请参阅RFC-3447:公钥加密标准（PKCS）#1 v2.1:RSA加密规范</em>。
 *
 * \注意：此函数强制要求提供的salt长度符合FIPS 186-4§5.5（e）和RFC 8017（PKCS#1 v2.2）§9.1.1第3步的要求。限制条件是哈希长度加上salt长度加上2个字节最多只能是密钥长度。如果不满足此约束，则此函数返回#MBEDTLS_ERROR_RSA_BAD_INPUT_DATA。
 *
 * \param ctx要使用的初始化RSA上下文。\param f_rng rng函数。它不能为空。\param p_rng要传递给\p f_rng的rng上下文。如果\p f_rng不需要上下文参数，则该值可能为\c NULL。\param md_alg用于哈希原始数据的消息摘要算法。使用#MBEDTLS_MD_NONE对原始数据进行签名。\param hashlen消息摘要的长度。只有当\p md_alg为#MBEDTLS_md_NONE时，才使用Ths。\param hash保存消息摘要或原始数据的缓冲区。如果\p md_alg为#MBEDTLS_md_NONE，则这必须是长度为\p hashlen Bytes的可读缓冲区。如果\p md_alg不是#MBEDTLS_md_NONE，则它必须是一个可读缓冲区，其长度必须与\p md_alg对应的哈希大小相同。\param saltlen应使用的盐的长度。如果通过#MBEDTLS_RSA_SALT_LEN_ANY，函数将使用最大可能的盐长度，直到哈希长度，这是某些标准（包括FIPS 186-4§5.5）允许的最大值。\param sig保存签名的缓冲区。这必须是长度为\c ctx->len Bytes的可写缓冲区。例如，对于2048位RSA模数，\c 256字节。缓冲区长度#MBEDTLS_MPI_MAX_SIZE始终是安全的。
 *
 * \如果签名操作成功，则返回\c 0。\失败时返回\c MBEDTLS_error_RSA_XXX错误代码。
 */
int mbedtls_rsa_rsassa_pss_sign_ext( mbedtls_rsa_context *ctx,
                         int (*f_rng)(void *, unsigned char *, size_t),
                         void *p_rng,
                         mbedtls_md_type_t md_alg,
                         unsigned int hashlen,
                         const unsigned char *hash,
                         int saltlen,
                         unsigned char *sig );

/**
 * \brief此函数执行PKCS#1 v2.1 PSS签名操作（RSASSA-PS-SIGN）。
 *
 * \注意：在\p ctx中设置的\chash_id（当调用mbedtls_rsa_init（）或随后调用mbedtls _rsa_set_padding（）时）选择用于编码操作和掩码生成函数（MGF1）的哈希。有关编码操作和掩码生成功能的更多详细信息，请参阅RFC-3447:公钥加密标准（PKCS）#1 v2.1:RSA加密规范</em>。
 *
 * \注意：此函数始终使用最大可能的salt大小，直到有效负载哈希的长度。盐大小的选择符合FIPS 186-4§5.5（e）和RFC 8017（PKCS#1 v2.2）§9.1.1第3步。此外，该函数强制执行最小盐大小，即哈希大小减去2字节。如果给定密钥大小，此最小大小太大（salt大小加上哈希大小，加上2个字节，必须不大于密钥大小（以字节为单位）），则此函数返回#MBEDTLS_ERROR_RSA_BAD_INPUT_DATA。
 *
 * \不推荐在#MBEDTLS_RSA_PUBLIC模式下调用此函数。库的未来版本可能会删除\p mode参数，并将其隐式设置为#MBEDTLS_RSA_PRIVATE。
 *
 * \注意：RSA的替代实现不需要支持将模式设置为#MBEDTLS_RSA_PUBLIC，而是可以返回#MBEDLLS_ERROR_PLATFORM_FEATURE_UNSUPPORTED。
 *
 * \param ctx要使用的初始化RSA上下文。\param f_rng rng函数。它不能为空。\param p_rng要传递给\p f_rng的rng上下文。如果\p f_rng不需要上下文参数，则该值可能为\c NULL。\param mode操作模式。必须是#MBEDTLS_RSA_PRIVATE或#MBEDLLS_RSA_PUBLIC（已弃用）。\param md_alg用于哈希原始数据的消息摘要算法。使用#MBEDTLS_MD_NONE对原始数据进行签名。\param hashlen消息摘要的长度。仅当\p md_alg为#MBEDTLS_md_NONE时才使用。\param hash保存消息摘要或原始数据的缓冲区。如果\p md_alg为#MBEDTLS_md_NONE，则这必须是长度为\p hashlen Bytes的可读缓冲区。如果\p md_alg不是#MBEDTLS_md_NONE，则它必须是一个可读缓冲区，其长度必须与\p md_alg对应的哈希大小相同。\param sig保存签名的缓冲区。这必须是长度为\c ctx->len Bytes的可写缓冲区。例如，对于2048位RSA模数，\c 256字节。缓冲区长度#MBEDTLS_MPI_MAX_SIZE始终是安全的。
 *
 * \如果签名操作成功，则返回\c 0。\失败时返回\c MBEDTLS_error_RSA_XXX错误代码。
 */
int mbedtls_rsa_rsassa_pss_sign( mbedtls_rsa_context *ctx,
                         int (*f_rng)(void *, unsigned char *, size_t),
                         void *p_rng,
                         int mode,
                         mbedtls_md_type_t md_alg,
                         unsigned int hashlen,
                         const unsigned char *hash,
                         unsigned char *sig );

/**
 * \brief此函数执行公共RSA操作并检查消息摘要。
 *
 *                 这是使用上下文中的模式执行PKCS#1验证的通用包装。
 *
 * \注意：对于PKCS#1 v2.1编码，请参阅mbedtls_rsa_rsassa_pss_verify（）上关于\p md_alg和\p hash_id的注释。
 *
 * \不推荐在#MBEDTLS_RSA_PRIVATE模式下调用此函数。库的未来版本可能会删除\p mode参数，并将其设置为#MBEDTLS_RSA_PUBLIC。
 *
 * \注意：RSA的替代实现不需要支持将模式设置为#MBEDTLS_RSA_PRIVATE，而是可以返回#MBEDLLS_ERROR_PLATFORM_FEATURE_UNSUPPORTED。
 *
 * \param ctx要使用的初始化RSA公钥上下文。\param f_rng要使用的rng函数。如果\p模式为#MBEDTLS_RSA_PRIVATE，则该模式用于致盲，应提供；有关详细信息，请参阅mbedtls_rsa_private（）。否则，它将被忽略。\param p_rng要传递给\p f_rng的rng上下文。如果\p f_rng为空或不需要上下文，则可能为空。\param mode操作模式。必须是#MBEDTLS_RSA_PUBLIC或#MBEDLLS_RSA_PRIVATE（已弃用）。\param md_alg用于哈希原始数据的消息摘要算法。使用#MBEDTLS_MD_NONE对原始数据进行签名。\param hashlen消息摘要的长度。仅当\p md_alg为#MBEDTLS_md_NONE时才使用。\param hash保存消息摘要或原始数据的缓冲区。如果\p md_alg为#MBEDTLS_md_NONE，则这必须是长度为\p hashlen Bytes的可读缓冲区。如果\p md_alg不是#MBEDTLS_md_NONE，则它必须是一个可读缓冲区，其长度必须与\p md_alg对应的哈希大小相同。\param sig保存签名的缓冲区。这必须是长度为\c ctx->len Bytes的可读缓冲区。例如，对于2048位RSA模数，\c 256字节。
 *
 * \如果验证操作成功，则返回\c 0。\失败时返回\c MBEDTLS_error_RSA_XXX错误代码。
 */
int mbedtls_rsa_pkcs1_verify( mbedtls_rsa_context *ctx,
                      int (*f_rng)(void *, unsigned char *, size_t),
                      void *p_rng,
                      int mode,
                      mbedtls_md_type_t md_alg,
                      unsigned int hashlen,
                      const unsigned char *hash,
                      const unsigned char *sig );

/**
 * \brief此函数执行PKCS#1 v1.5验证操作（RSASSA-PKS1-v1_5-VERIFY）。
 *
 * \不推荐在#MBEDTLS_RSA_PRIVATE模式下调用此函数。库的未来版本可能会删除\p mode参数，并将其设置为#MBEDTLS_RSA_PUBLIC。
 *
 * \注意：RSA的替代实现不需要支持将模式设置为#MBEDTLS_RSA_PRIVATE，而是可以返回#MBEDLLS_ERROR_PLATFORM_FEATURE_UNSUPPORTED。
 *
 * \param ctx要使用的初始化RSA公钥上下文。\param f_rng要使用的rng函数。如果\p模式为#MBEDTLS_RSA_PRIVATE，则该模式用于致盲，应提供；有关详细信息，请参阅mbedtls_rsa_private（）。否则，它将被忽略。\param p_rng要传递给\p f_rng的rng上下文。如果\p f_rng为空或不需要上下文，则可能为空。\param mode操作模式。必须是#MBEDTLS_RSA_PUBLIC或#MBEDLLS_RSA_PRIVATE（已弃用）。\param md_alg用于哈希原始数据的消息摘要算法。使用#MBEDTLS_MD_NONE对原始数据进行签名。\param hashlen消息摘要的长度。仅当\p md_alg为#MBEDTLS_md_NONE时才使用。\param hash保存消息摘要或原始数据的缓冲区。如果\p md_alg为#MBEDTLS_md_NONE，则这必须是长度为\p hashlen Bytes的可读缓冲区。如果\p md_alg不是#MBEDTLS_md_NONE，则它必须是一个可读缓冲区，其长度必须与\p md_alg对应的哈希大小相同。\param sig保存签名的缓冲区。这必须是长度为\c ctx->len Bytes的可读缓冲区。例如，对于2048位RSA模数，\c 256字节。
 *
 * \如果验证操作成功，则返回\c 0。\失败时返回\c MBEDTLS_error_RSA_XXX错误代码。
 */
int mbedtls_rsa_rsassa_pkcs1_v15_verify( mbedtls_rsa_context *ctx,
                                 int (*f_rng)(void *, unsigned char *, size_t),
                                 void *p_rng,
                                 int mode,
                                 mbedtls_md_type_t md_alg,
                                 unsigned int hashlen,
                                 const unsigned char *hash,
                                 const unsigned char *sig );

/**
 * \brief此函数执行PKCS#1 v2.1 PSS验证操作（RSASSA-PS-VERIFY）。
 *
 * \注意：在\p ctx中设置的\chash_id（当调用mbedtls_rsa_init（）或随后调用mbedtls _rsa_set_padding（）时）选择用于编码操作和掩码生成函数（MGF1）的哈希。有关编码操作和掩码生成功能的更多详细信息，请参阅RFC-3447:公钥加密标准（PKCS）#1 v2.1:RSA加密规范</em>。如果ctx中设置的\c hash_id为#MBEDTLS_MD_NONE，则使用\p MD_alg参数。
 *
 * \不推荐在#MBEDTLS_RSA_PRIVATE模式下调用此函数。库的未来版本可能会删除\p mode参数，并将其隐式设置为#MBEDTLS_RSA_PUBLIC。
 *
 * \注意：RSA的替代实现不需要支持将模式设置为#MBEDTLS_RSA_PRIVATE，而是可以返回#MBEDLLS_ERROR_PLATFORM_FEATURE_UNSUPPORTED。
 *
 * \param ctx要使用的初始化RSA公钥上下文。\param f_rng要使用的rng函数。如果\p模式为#MBEDTLS_RSA_PRIVATE，则该模式用于致盲，应提供；有关详细信息，请参阅mbedtls_rsa_private（）。否则，它将被忽略。\param p_rng要传递给\p f_rng的rng上下文。如果\p f_rng为空或不需要上下文，则可能为空。\param mode操作模式。必须是#MBEDTLS_RSA_PUBLIC或#MBEDLLS_RSA_PRIVATE（已弃用）。\param md_alg用于哈希原始数据的消息摘要算法。使用#MBEDTLS_MD_NONE对原始数据进行签名。\param hashlen消息摘要的长度。仅当\p md_alg为#MBEDTLS_md_NONE时才使用。\param hash保存消息摘要或原始数据的缓冲区。如果\p md_alg为#MBEDTLS_md_NONE，则这必须是长度为\p hashlen Bytes的可读缓冲区。如果\p md_alg不是#MBEDTLS_md_NONE，则它必须是一个可读缓冲区，其长度必须与\p md_alg对应的哈希大小相同。\param sig保存签名的缓冲区。这必须是长度为\c ctx->len Bytes的可读缓冲区。例如，对于2048位RSA模数，\c 256字节。
 *
 * \如果验证操作成功，则返回\c 0。\失败时返回\c MBEDTLS_error_RSA_XXX错误代码。
 */
int mbedtls_rsa_rsassa_pss_verify( mbedtls_rsa_context *ctx,
                           int (*f_rng)(void *, unsigned char *, size_t),
                           void *p_rng,
                           int mode,
                           mbedtls_md_type_t md_alg,
                           unsigned int hashlen,
                           const unsigned char *hash,
                           const unsigned char *sig );

/**
 * \brief此函数执行PKCS#1 v2.1 PSS验证操作（RSASSA-PS-VERIFY）。
 *
 * \注意\p sig缓冲区必须与\p ctx->N的大小一样大。例如，如果使用RSA-1024，则为128字节。
 *
 * \注意：在\p ctx中设置的\chash_id（当调用mbedtls_rsa_init（）或之后调用mbedtls _rsa_set_padding（）时）将被忽略。
 *
 * \param ctx要使用的初始化RSA公钥上下文。\param f_rng要使用的rng函数。如果\p模式为#MBEDTLS_RSA_PRIVATE，则该模式用于致盲，应提供；有关详细信息，请参阅mbedtls_rsa_private（）。否则，它将被忽略。\param p_rng要传递给\p f_rng的rng上下文。如果\p f_rng为空或不需要上下文，则可能为空。\param mode操作模式。这必须是#MBEDTLS_RSA_PUBLIC或#MBEDLLS_RSA_PRIVATE。\param md_alg用于哈希原始数据的消息摘要算法。使用#MBEDTLS_MD_NONE对原始数据进行签名。\param hashlen消息摘要的长度。仅当\p md_alg为#MBEDTLS_md_NONE时才使用。\param hash保存消息摘要或原始数据的缓冲区。如果\p md_alg为#MBEDTLS_md_NONE，则这必须是长度为\p hashlen Bytes的可读缓冲区。如果\p md_alg不是#MBEDTLS_md_NONE，则它必须是一个可读缓冲区，其长度必须与\p md_alg对应的哈希大小相同。\param mgf1_hash_id用于验证操作和掩码生成函数（mgf1）的消息摘要算法。有关编码操作和掩码生成功能的更多详细信息，请参阅RFC-3447:公钥加密标准（PKCS）#1 v2.1:RSA加密规范</em>。\param expected_salt_len用于填充的盐的长度。使用#MBEDTLS_RSA_SALT_LEN_ANY接受任何盐长度。\param sig保存签名的缓冲区。这必须是长度为\c ctx->len Bytes的可读缓冲区。例如，对于2048位RSA模数，\c 256字节。
 *
 * \如果验证操作成功，则返回\c 0。\失败时返回\c MBEDTLS_error_RSA_XXX错误代码。
 */
int mbedtls_rsa_rsassa_pss_verify_ext( mbedtls_rsa_context *ctx,
                               int (*f_rng)(void *, unsigned char *, size_t),
                               void *p_rng,
                               int mode,
                               mbedtls_md_type_t md_alg,
                               unsigned int hashlen,
                               const unsigned char *hash,
                               mbedtls_md_type_t mgf1_hash_id,
                               int expected_salt_len,
                               const unsigned char *sig );

/**
 * \brief此函数复制RSA上下文的组件。
 *
 * \param dst目标上下文。必须对其进行初始化。\param src源上下文。必须对其进行初始化。
 *
 * \成功时返回\c 0。\内存分配失败时返回#MBEDTLS_ERROR_MPI_ALLOC_FAILED。
 */
int mbedtls_rsa_copy( mbedtls_rsa_context *dst, const mbedtls_rsa_context *src );

/**
 * \brief此函数释放RSA密钥的组件。
 *
 * \param ctx要释放的RSA上下文。可能为空，在这种情况下，此函数为no-op。如果不是空，则必须指向已初始化的RSA上下文。
 */
void mbedtls_rsa_free( mbedtls_rsa_context *ctx );

#if defined(MBEDTLS_SELF_TEST)

/**
 * \RSA检查程序简介。
 *
 * \成功时返回\c 0。\失败时返回\c 1。
 */
int mbedtls_rsa_self_test( int verbose );

#endif /* MBEDTLS_SELF_TEST */

#ifdef __cplusplus
}
#endif

#endif /* rsa.h格式*/

