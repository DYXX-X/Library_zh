/**
 * \文件ecdsa.h
 *
 * \brief此文件包含ECDSA定义和函数。
 *
 * 椭圆曲线数字签名算法（ECDSA）定义在有效密码组（SECG）标准：SEC1椭圆曲线密码</em>中。用于TLS的ECDSA的使用在<em>RFC-4492:Elliptic Curve Cryptography（ECC）Cipher Suites for Transport Layer Security（TLS）</em>中定义。
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

#ifndef MBEDTLS_ECDSA_H
#define MBEDTLS_ECDSA_H

#if !defined(MBEDTLS_CONFIG_FILE)
#include "mbedtls/config.h"
#else
#include MBEDTLS_CONFIG_FILE
#endif

#include "mbedtls/ecp.h"
#include "mbedtls/md.h"

/**
 * \给定曲线比特大小的简短最大ECDSA签名大小
 *
 * \param bits曲线大小（位）\return最大签名大小（字节）
 *
 * \注意：如果此宏的参数为1，则返回编译时间常数。它可以多次评估其论点。
 */
/*
 *     Ecdsa Sig值：：=序列｛r整数，s整数｝
 *
 * 对于r和s中的每一个，值（V）可以包括额外的初始“0”位。
 */
#define MBEDTLS_ECDSA_MAX_SIG_LEN( bits )                               \
    ( /*T、 序列L*/ ( ( bits ) >= 61 * 8 ? 3 : 2 ) +              \
      /*T、 r，s的长度*/        2 * ( ( ( bits ) >= 127 * 8 ? 3 : 2 ) +     \
      /*r的V，s*/                ( ( bits ) + 8 ) / 8 ) )

/**ECDSA签名的最大大小（字节）。*/
#define MBEDTLS_ECDSA_MAX_LEN  MBEDTLS_ECDSA_MAX_SIG_LEN( MBEDTLS_ECP_MAX_BITS )

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \简要ECDSA上下文结构。
 *
 * \警告：不支持在同一ECDSA上下文上同时执行多个操作；这种类型的对象不应在多个线程之间共享。
 */
typedef mbedtls_ecp_keypair mbedtls_ecdsa_context;

#if defined(MBEDTLS_ECP_RESTARTABLE)

/**
 * \ecdsa_verify（）的简短内部重新启动上下文
 *
 * \注意：不透明结构，在ecdsa.c中定义
 */
typedef struct mbedtls_ecdsa_restart_ver mbedtls_ecdsa_restart_ver_ctx;

/**
 * \ecdsa_sign（）的简短内部重新启动上下文
 *
 * \注意：不透明结构，在ecdsa.c中定义
 */
typedef struct mbedtls_ecdsa_restart_sig mbedtls_ecdsa_restart_sig_ctx;

#if defined(MBEDTLS_ECDSA_DETERMINISTIC)
/**
 * \ecdsa_sign_det（）的简短内部重新启动上下文
 *
 * \注意：不透明结构，在ecdsa.c中定义
 */
typedef struct mbedtls_ecdsa_restart_det mbedtls_ecdsa_restart_det_ctx;
#endif

/**
 * \恢复ECDSA运行的简要概述
 */
typedef struct
{
    mbedtls_ecp_restart_ctx ecp;        /*!<  ECP重启和共享管理信息的基本上下文*/
    mbedtls_ecdsa_restart_ver_ctx *ver; /*!<  ecdsa_verify（）子上下文*/
    mbedtls_ecdsa_restart_sig_ctx *sig; /*!<  ecdsa_sign（）子上下文*/
#if defined(MBEDTLS_ECDSA_DETERMINISTIC)
    mbedtls_ecdsa_restart_det_ctx *det; /*!<  ecdsa_sign_det（）子上下文*/
#endif
} mbedtls_ecdsa_restart_ctx;

#else /* MBEDTLS_ECP_RESTARTABLE */

/* 现在我们可以声明一个指向它的函数*/
typedef void mbedtls_ecdsa_restart_ctx;

#endif /* MBEDTLS_ECP_RESTARTABLE */

/**
 * \brief此函数检查给定组是否可用于ECDSA。
 *
 * \param gid要检查的ECP组ID。
 *
 * \如果可以使用组，则返回\c 1，否则返回\c 0
 */
int mbedtls_ecdsa_can_do( mbedtls_ecp_group_id gid );

/**
 * \brief此函数计算先前散列消息的ECDSA签名。
 *
 * \注意：通常首选在mbedtls_ecdsa_sign_det（）中实现的确定性版本。
 *
 * \注意：如果消息哈希的比特长度大于组顺序的比特长度，则哈希将被截断，如<em>高效加密组标准（SECG）：SEC1椭圆曲线加密</em>第4.1.3节步骤5中所定义。
 *
 * \见ecp.h
 *
 * \param grp要使用的椭圆曲线的上下文。必须对其进行初始化并设置组参数，例如通过mbedtls_ecp_group_load（）。\param r存储签名的第一部分的MPI上下文。必须对其进行初始化。\param s用于存储签名的第二部分的MPI上下文。必须对其进行初始化。\param d私有签名密钥。必须对其进行初始化。\param buf要签名的内容。这通常是要签名的原始数据的哈希。这必须是一个可读缓冲区，长度为\n blen Bytes。如果布尔值为零，则可能为空。\param blen \p buf的长度（以字节为单位）。\param f_rng rng函数。此值不能为空。\param p_rng要传递给\p f_rng的rng上下文。如果\p f_rng不需要上下文参数，则该值可能为\c NULL。
 *
 * \成功时返回\c 0。\失败时返回\c MBEDTLS_error_ECP_XXX或\c MBEDTLS_MPI_XXX错误代码。
 */
int mbedtls_ecdsa_sign( mbedtls_ecp_group *grp, mbedtls_mpi *r, mbedtls_mpi *s,
                const mbedtls_mpi *d, const unsigned char *buf, size_t blen,
                int (*f_rng)(void *, unsigned char *, size_t), void *p_rng );

#if defined(MBEDTLS_ECDSA_DETERMINISTIC)
#if ! defined(MBEDTLS_DEPRECATED_REMOVED)
#if defined(MBEDTLS_DEPRECATED_WARNING)
#define MBEDTLS_DEPRECATED    __attribute__((deprecated))
#else
#define MBEDTLS_DEPRECATED
#endif
/**
 * \brief此函数计算先前散列消息（确定性版本）的ECDSA签名。
 *
 *                  有关更多信息，请参见RFC-6979：数字签名算法（DSA）和椭圆曲线数字签名算法的确定用法</em>。
 *
 * \注意：如果消息哈希的比特长度大于组顺序的比特长度，则哈希将被截断，如<em>高效加密组标准（SECG）：SEC1椭圆曲线加密</em>第4.1.3节步骤5中所定义。
 *
 * \警告由于对于同一密钥和消息，内部RNG的输出总是相同的，这限制了致盲的效率，并通过侧信道泄漏信息。对于安全行为，请改用mbedtls_ecdsa_sign_det_ext（）。
 *
 *                  （最佳情况下，致盲是一个随机值，每次执行都不同。在这种情况下，从攻击者的角度来看，致盲仍然是随机的，但每次执行都是一样的。这意味着，这种致盲不会阻止攻击者通过组合多个测量痕迹来恢复机密，但可能会阻止一些利用机密数据之间关系的攻击。）
 *
 * \见ecp.h
 *
 * \param grp要使用的椭圆曲线的上下文。必须对其进行初始化并设置组参数，例如通过mbedtls_ecp_group_load（）。\param r存储签名的第一部分的MPI上下文。必须对其进行初始化。\param s用于存储签名的第二部分的MPI上下文。必须对其进行初始化。\param d私有签名密钥。例如，必须通过mbedtls_ecp_gen_privkey（）对其进行初始化和设置。\param buf要签名的哈希内容。这必须是一个可读缓冲区，长度为\n blen Bytes。如果布尔值为零，则可能为空。\param blen \p buf的长度（以字节为单位）。\param md_alg用于哈希原始数据的哈希算法。
 *
 * \成功时返回\c 0。\失败时返回\c MBEDTLS_error_ECP_XXX或\c MBEDTLS_MPI_XXX错误代码。
 */
int mbedtls_ecdsa_sign_det( mbedtls_ecp_group *grp, mbedtls_mpi *r,
                            mbedtls_mpi *s, const mbedtls_mpi *d,
                            const unsigned char *buf, size_t blen,
                            mbedtls_md_type_t md_alg ) MBEDTLS_DEPRECATED;
#undef MBEDTLS_DEPRECATED
#endif /* MBEDTLS_DEPRECATED_REMOVED */

/**
 * \brief此函数计算先前散列消息（确定性版本）的ECDSA签名。
 *
 *                  有关更多信息，请参见RFC-6979：数字签名算法（DSA）和椭圆曲线数字签名算法的确定用法</em>。
 *
 * \注意：如果消息哈希的比特长度大于组顺序的比特长度，则哈希将被截断，如<em>高效加密组标准（SECG）：SEC1椭圆曲线加密</em>第4.1.3节步骤5中所定义。
 *
 * \见ecp.h
 *
 * \param grp要使用的椭圆曲线的上下文。必须对其进行初始化并设置组参数，例如通过mbedtls_ecp_group_load（）。\param r存储签名的第一部分的MPI上下文。必须对其进行初始化。\param s用于存储签名的第二部分的MPI上下文。必须对其进行初始化。\param d私有签名密钥。例如，必须通过mbedtls_ecp_gen_privkey（）对其进行初始化和设置。\param buf要签名的哈希内容。这必须是一个可读缓冲区，长度为\n blen Bytes。如果布尔值为零，则可能为空。\param blen \p buf的长度（以字节为单位）。\param md_alg用于哈希原始数据的哈希算法。\param f_rng_widd用于致盲的rng函数。此值不能为空。\param p_rng_blind要传递给\p f_rng的rng上下文。如果\p f_rng不需要上下文参数，则该值可能为\c NULL。
 *
 * \成功时返回\c 0。\失败时返回\c MBEDTLS_error_ECP_XXX或\c MBEDTLS_MPI_XXX错误代码。
 */
int mbedtls_ecdsa_sign_det_ext( mbedtls_ecp_group *grp, mbedtls_mpi *r,
                            mbedtls_mpi *s, const mbedtls_mpi *d,
                            const unsigned char *buf, size_t blen,
                            mbedtls_md_type_t md_alg,
                            int (*f_rng_blind)(void *, unsigned char *, size_t),
                            void *p_rng_blind );
#endif /* MBEDTLS_ECDSA_DETERMINISTIC */

/**
 * \brief此函数验证先前散列消息的ECDSA签名。
 *
 * \注意：如果消息哈希的比特长度大于组顺序的比特长度，则哈希被截断，如<em>高效密码组标准（SECG）：SEC1椭圆曲线密码</em>第4.1.4节步骤3中所定义。
 *
 * \见ecp.h
 *
 * \param grp要使用的ECP组。必须对其进行初始化并设置组参数，例如通过mbedtls_ecp_group_load（）。\param buf签名的哈希内容。这必须是一个可读缓冲区，长度为\n blen Bytes。如果布尔值为零，则可能为空。\param blen \p buf的长度（以字节为单位）。\param Q用于验证的公钥。必须对其进行初始化和设置。\param r签名的第一个整数。必须对其进行初始化。\param s签名的第二个整数。必须对其进行初始化。
 *
 * \成功时返回\c 0。\如果签名无效，则返回#MBEDTLS_ERROR_ECP_BAD_INPUT_DATA。\由于任何其他原因失败时，返回\c MBEDTLS_error_ECP_XXX或\c MBEDTLS_MPI_XXX错误代码。
 */
int mbedtls_ecdsa_verify( mbedtls_ecp_group *grp,
                          const unsigned char *buf, size_t blen,
                          const mbedtls_ecp_point *Q, const mbedtls_mpi *r,
                          const mbedtls_mpi *s);

/**
 * \brief此函数计算ECDSA签名并将其写入缓冲区，缓冲区按照<em>RFC-4492:Elliptic Curve Cryptography（ECC）Cipher Suites for Transport Layer Security（TLS）</em>中的定义进行序列化。
 *
 * \警告在多个线程中使用同一上下文不是线程安全的。
 *
 * \注意：如果定义了#MBEDTLS_ECDSA_deterministic，则使用确定性版本。有关更多信息，请参见RFC-6979：数字签名算法（DSA）和椭圆曲线数字签名算法的确定用法</em>。
 *
 * \注意：如果消息哈希的比特长度大于组顺序的比特长度，则哈希将被截断，如<em>高效加密组标准（SECG）：SEC1椭圆曲线加密</em>第4.1.3节步骤5中所定义。
 *
 * \见ecp.h
 *
 * \param ctx要使用的ECDSA上下文。必须对其进行初始化并绑定组和私钥，例如通过mbedtls_ecdsa_genkey（）或mbedtls-ecdsa_from_keypair（）。\param md_alg用于哈希消息的消息摘要。\param hash要签名的消息哈希。这必须是一个可读缓冲区，长度为\n blen Bytes。\param hlen哈希的长度（字节）。\param sig要将签名写入的缓冲区。这必须是一个可写缓冲区，长度至少是所用曲线大小的两倍，加上9。例如，如果使用256位曲线，则为73字节。缓冲区长度#MBEDTLS_ECDSA_MAX_LEN始终是安全的。\param slen存储写入签名的实际长度的地址。不能为\c NULL。\param f_rng rng函数。如果未设置#MBEDTLS_ECDSA_DETERMINISTIC，则该值不能为空。否则，它仅用于致盲，并且可以设置为\c NULL，但这样做是弃用的。\param p_rng要传递给\p f_rng的rng上下文。如果\p f_rng为空或不使用上下文，则可能为空。
 *
 * \成功时返回\c 0。\失败时返回\c MBEDTLS_error_ECP_XXX、\c MBEDTLS_ERR_MPI_XXX或\c MBETTLS_error_ASN1_XXX错误代码。
 */
int mbedtls_ecdsa_write_signature( mbedtls_ecdsa_context *ctx,
                                   mbedtls_md_type_t md_alg,
                           const unsigned char *hash, size_t hlen,
                           unsigned char *sig, size_t *slen,
                           int (*f_rng)(void *, unsigned char *, size_t),
                           void *p_rng );

/**
 * \brief此函数计算ECDSA签名并以可重新启动的方式将其写入缓冲区。
 *
 * \请参见\c mbedtls_ecdsa_write_signature（）
 *
 * \注意：此函数类似于\cmbedtls_ecdsa_write_signature（），但它可以提前返回并根据\cmbedtls _ecp_set_max_ops（）设置的限制重新启动，以减少阻塞。
 *
 * \param ctx要使用的ECDSA上下文。必须对其进行初始化并绑定组和私钥，例如通过mbedtls_ecdsa_genkey（）或mbedtls-ecdsa_from_keypair（）。\param md_alg用于哈希消息的消息摘要。\param hash要签名的消息哈希。这必须是一个可读缓冲区，长度为\n blen Bytes。\param hlen哈希的长度（字节）。\param sig要将签名写入的缓冲区。这必须是一个可写缓冲区，长度至少是所用曲线大小的两倍，加上9。例如，如果使用256位曲线，则为73字节。缓冲区长度#MBEDTLS_ECDSA_MAX_LEN始终是安全的。\param slen存储写入签名的实际长度的地址。不能为\c NULL。\param f_rng rng函数。如果未设置#MBEDTLS_ECDSA_DETERMINISTIC，则该值不能为空。否则，它是未使用的，可以设置为\c NULL。\param p_rng要传递给\p f_rng的rng上下文。如果\p f_rng为空或不使用上下文，则可能为空。\param rs_ctx要使用的重新启动上下文。这可能为空以禁用重新启动。如果不是空，则必须指向初始化的重新启动上下文。
 *
 * \成功时返回\c 0。\如果已达到最大操作数，返回#MBEDTLS_ERROR_ECP_IN_PROGRESS：请参阅\c MBEDTLS_ECP_set_max_ops（）。\失败时返回另一个\c MBEDTLS_error_ECP_XXX、\c MBETTLS_error_MPI_XXX或\c MBEDTLS_ERR_ASN1_XXX错误代码。
 */
int mbedtls_ecdsa_write_signature_restartable( mbedtls_ecdsa_context *ctx,
                           mbedtls_md_type_t md_alg,
                           const unsigned char *hash, size_t hlen,
                           unsigned char *sig, size_t *slen,
                           int (*f_rng)(void *, unsigned char *, size_t),
                           void *p_rng,
                           mbedtls_ecdsa_restart_ctx *rs_ctx );

#if defined(MBEDTLS_ECDSA_DETERMINISTIC)
#if ! defined(MBEDTLS_DEPRECATED_REMOVED)
#if defined(MBEDTLS_DEPRECATED_WARNING)
#define MBEDTLS_DEPRECATED    __attribute__((deprecated))
#else
#define MBEDTLS_DEPRECATED
#endif
/**
 * \brief此函数计算ECDSA签名并将其写入缓冲区，缓冲区按照<em>RFC-4492:Elliptic Curve Cryptography（ECC）Cipher Suites for Transport Layer Security（TLS）</em>中的定义进行序列化。
 *
 *                  确定性版本定义在RFC-6979：数字签名算法（DSA）和椭圆曲线数字签名算法的确定性使用</em>中。
 *
 * \警告在多个线程中使用同一上下文不是线程安全的。
 *
 * \注意：如果消息哈希的比特长度大于组顺序的比特长度，则哈希将被截断，如<em>高效加密组标准（SECG）：SEC1椭圆曲线加密</em>第4.1.3节步骤5中所定义。
 *
 * \见ecp.h
 *
 * \已弃用在Mbed TLS 2.0版及更高版本中被mbedtls_ecdsa_write_signature（）取代。
 *
 * \param ctx要使用的ECDSA上下文。必须对其进行初始化并绑定组和私钥，例如通过mbedtls_ecdsa_genkey（）或mbedtls-ecdsa_from_keypair（）。\param hash要签名的消息哈希。这必须是一个可读缓冲区，长度为\n blen Bytes。\param hlen哈希的长度（字节）。\param sig要将签名写入的缓冲区。这必须是一个可写缓冲区，长度至少是所用曲线大小的两倍，加上9。例如，如果使用256位曲线，则为73字节。缓冲区长度#MBEDTLS_ECDSA_MAX_LEN始终是安全的。\param slen存储写入签名的实际长度的地址。不能为\c NULL。\param md_alg用于哈希消息的消息摘要。
 *
 * \成功时返回\c 0。\失败时返回\c MBEDTLS_error_ECP_XXX、\c MBEDTLS_ERR_MPI_XXX或\c MBETTLS_error_ASN1_XXX错误代码。
 */
int mbedtls_ecdsa_write_signature_det( mbedtls_ecdsa_context *ctx,
                               const unsigned char *hash, size_t hlen,
                               unsigned char *sig, size_t *slen,
                               mbedtls_md_type_t md_alg ) MBEDTLS_DEPRECATED;
#undef MBEDTLS_DEPRECATED
#endif /* MBEDTLS_DEPRECATED_REMOVED */
#endif /* MBEDTLS_ECDSA_DETERMINISTIC */

/**
 * \brief此函数读取并验证ECDSA签名。
 *
 * \注意：如果消息哈希的比特长度大于组顺序的比特长度，则哈希被截断，如<em>高效密码组标准（SECG）：SEC1椭圆曲线密码</em>第4.1.4节步骤3中所定义。
 *
 * \见ecp.h
 *
 * \param ctx要使用的ECDSA上下文。必须对其进行初始化并绑定组和公钥。\param hash签名的消息哈希。这必须是长度为\p大小字节的可读缓冲区。\param hlen哈希\p哈希的大小。\param sig要读取和验证的签名。这必须是长度为\p slen Bytes的可读缓冲区。\param slen \p sig的大小（以字节为单位）。
 *
 * \成功时返回\c 0。\如果签名无效，则返回#MBEDTLS_ERROR_ECP_BAD_INPUT_DATA。\如果SIG中有有效签名，但其长度小于siglen，则返回#MBEDTLS_ERROR_ECP_SIG_LEN_MISMATCH。\由于任何其他原因失败时，返回\c MBEDTLS_error_ECP_XXX或\c MBEDTLS_ERR_MPI_XXX错误代码。
 */
int mbedtls_ecdsa_read_signature( mbedtls_ecdsa_context *ctx,
                          const unsigned char *hash, size_t hlen,
                          const unsigned char *sig, size_t slen );

/**
 * \brief此函数以可重新启动的方式读取并验证ECDSA签名。
 *
 * \请参见\cmbedtls_ecdsa_read_signature（）
 *
 * \注意：此函数类似于\cmbedtls_ecdsa_read_signature（），但它可以提前返回并根据\cmbedtls _ecp_set_max_ops（）设置的限制重新启动，以减少阻塞。
 *
 * \param ctx要使用的ECDSA上下文。必须对其进行初始化并绑定组和公钥。\param hash签名的消息哈希。这必须是长度为\p大小字节的可读缓冲区。\param hlen哈希\p哈希的大小。\param sig要读取和验证的签名。这必须是长度为\p slen Bytes的可读缓冲区。\param slen \p sig的大小（以字节为单位）。\param rs_ctx要使用的重新启动上下文。这可能为空以禁用重新启动。如果不是空，则必须指向初始化的重新启动上下文。
 *
 * \成功时返回\c 0。\如果签名无效，则返回#MBEDTLS_ERROR_ECP_BAD_INPUT_DATA。\如果SIG中有有效签名，但其长度小于siglen，则返回#MBEDTLS_ERROR_ECP_SIG_LEN_MISMATCH。\如果已达到最大操作数，返回#MBEDTLS_ERROR_ECP_IN_PROGRESS：请参阅\c MBEDTLS_ECP_set_max_ops（）。\由于任何其他原因失败时，返回另一个\c MBEDTLS_error_ECP_XXX或\c MBEDTLS_ERR_MPI_XXX错误代码。
 */
int mbedtls_ecdsa_read_signature_restartable( mbedtls_ecdsa_context *ctx,
                          const unsigned char *hash, size_t hlen,
                          const unsigned char *sig, size_t slen,
                          mbedtls_ecdsa_restart_ctx *rs_ctx );

/**
 * \brief此函数在给定曲线上生成ECDSA键对。
 *
 * \见ecp.h
 *
 * \param ctx存储密钥对的ECDSA上下文。必须对其进行初始化。\param gid要使用的椭圆曲线。取决于配置的各种MBEDTLS_ECP_DP_XXX宏之一。\param f_rng要使用的rng函数。此值不能为空。\param p_rng要传递给\p f_rng的rng上下文。如果\p f_rng不需要上下文参数，则该值可能为\c NULL。
 *
 * \成功时返回\c 0。\失败时返回\c MBEDTLS_ERROR_ECP_XXX代码。
 */
int mbedtls_ecdsa_genkey( mbedtls_ecdsa_context *ctx, mbedtls_ecp_group_id gid,
                  int (*f_rng)(void *, unsigned char *, size_t), void *p_rng );

/**
 * \brief此函数从EC密钥对设置ECDSA上下文。
 *
 * \见ecp.h
 *
 * \param ctx要设置的ECDSA上下文。必须对其进行初始化。\param key要使用的EC密钥。必须对其进行初始化，并保存一个私钥对或公钥。在前一种情况下，ECDSA上下文可用于此调用后的签名创建和验证。在后一种情况下，它可以用于签名验证。
 *
 * \成功时返回\c 0。\失败时返回\c MBEDTLS_ERROR_ECP_XXX代码。
 */
int mbedtls_ecdsa_from_keypair( mbedtls_ecdsa_context *ctx,
                                const mbedtls_ecp_keypair *key );

/**
 * \brief此函数初始化ECDSA上下文。
 *
 * \param ctx要初始化的ECDSA上下文。此值不能为空。
 */
void mbedtls_ecdsa_init( mbedtls_ecdsa_context *ctx );

/**
 * \brief此函数释放ECDSA上下文。
 *
 * \param ctx要释放的ECDSA上下文。这可能是空的，在这种情况下，此函数不执行任何操作。如果不是空值，则必须对其进行初始化。
 */
void mbedtls_ecdsa_free( mbedtls_ecdsa_context *ctx );

#if defined(MBEDTLS_ECP_RESTARTABLE)
/**
 * \brief初始化重新启动上下文。
 *
 * \param ctx要初始化的重新启动上下文。此值不能为空。
 */
void mbedtls_ecdsa_restart_init( mbedtls_ecdsa_restart_ctx *ctx );

/**
 * \brief释放重启上下文的组件。
 *
 * \param ctx要释放的重新启动上下文。这可能是空的，在这种情况下，此函数不执行任何操作。如果不是空值，则必须对其进行初始化。
 */
void mbedtls_ecdsa_restart_free( mbedtls_ecdsa_restart_ctx *ctx );
#endif /* MBEDTLS_ECP_RESTARTABLE */

#ifdef __cplusplus
}
#endif

#endif /* 电子海图*/

