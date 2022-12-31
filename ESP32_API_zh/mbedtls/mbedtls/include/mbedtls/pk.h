/**
 * \文件pk.h
 *
 * \简短的公钥抽象层
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

#ifndef MBEDTLS_PK_H
#define MBEDTLS_PK_H

#if !defined(MBEDTLS_CONFIG_FILE)
#include "mbedtls/config.h"
#else
#include MBEDTLS_CONFIG_FILE
#endif

#include "mbedtls/md.h"

#if defined(MBEDTLS_RSA_C)
#include "mbedtls/rsa.h"
#endif

#if defined(MBEDTLS_ECP_C)
#include "mbedtls/ecp.h"
#endif

#if defined(MBEDTLS_ECDSA_C)
#include "mbedtls/ecdsa.h"
#endif

#if defined(MBEDTLS_USE_PSA_CRYPTO)
#include "psa/crypto.h"
#endif

#if ( defined(__ARMCC_VERSION) || defined(_MSC_VER) ) && \
    !defined(inline) && !defined(__cplusplus)
#define inline __inline
#endif

/**内存分配失败。*/
#define MBEDTLS_ERR_PK_ALLOC_FAILED        -0x3F80
/**类型不匹配，例如尝试使用ECDSA密钥加密*/
#define MBEDTLS_ERR_PK_TYPE_MISMATCH       -0x3F00
/**函数的输入参数错误。*/
#define MBEDTLS_ERR_PK_BAD_INPUT_DATA      -0x3E80
/**读取/写入文件失败。*/
#define MBEDTLS_ERR_PK_FILE_IO_ERROR       -0x3E00
/**不支持的密钥版本*/
#define MBEDTLS_ERR_PK_KEY_INVALID_VERSION -0x3D80
/**无效的键标记或值。*/
#define MBEDTLS_ERR_PK_KEY_INVALID_FORMAT  -0x3D00
/**不支持密钥算法（仅支持RSA和EC）。*/
#define MBEDTLS_ERR_PK_UNKNOWN_PK_ALG      -0x3C80
/**私钥密码不能为空。*/
#define MBEDTLS_ERR_PK_PASSWORD_REQUIRED   -0x3C00
/**给定的私钥密码不允许正确解密。*/
#define MBEDTLS_ERR_PK_PASSWORD_MISMATCH   -0x3B80
/**公钥标记或值无效（仅支持RSA和EC）。*/
#define MBEDTLS_ERR_PK_INVALID_PUBKEY      -0x3B00
/**算法标记或值无效。*/
#define MBEDTLS_ERR_PK_INVALID_ALG         -0x3A80
/**不支持椭圆曲线（仅支持NIST曲线）。*/
#define MBEDTLS_ERR_PK_UNKNOWN_NAMED_CURVE -0x3A00
/**不可用的功能，例如RSA密钥禁用了RSA。*/
#define MBEDTLS_ERR_PK_FEATURE_UNAVAILABLE -0x3980
/**缓冲区包含一个有效签名，后面跟着更多数据。*/
#define MBEDTLS_ERR_PK_SIG_LEN_MISMATCH    -0x3900

/* MBEDTLS_ERROR_PK_HW_ACCEL_FAILED已弃用，不应使用。*/
/**PK硬件加速器失败。*/
#define MBEDTLS_ERR_PK_HW_ACCEL_FAILED     -0x3880

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \简要公钥类型
 */
typedef enum {
    MBEDTLS_PK_NONE=0,
    MBEDTLS_PK_RSA,
    MBEDTLS_PK_ECKEY,
    MBEDTLS_PK_ECKEY_DH,
    MBEDTLS_PK_ECDSA,
    MBEDTLS_PK_RSA_ALT,
    MBEDTLS_PK_RSASSA_PSS,
    MBEDTLS_PK_OPAQUE,
} mbedtls_pk_type_t;

/**
 * \RSASSA-PSS签名验证的简短选项。请参见\c mbedtls_rsa_rsassa_pss_verify_ext（）
 */
typedef struct mbedtls_pk_rsassa_pss_options
{
    mbedtls_md_type_t mgf1_hash_id;
    int expected_salt_len;

} mbedtls_pk_rsassa_pss_options;

/**
 * \brief mbedtls_pk_sign（）生成的签名的最大大小。
 */
/* 我们需要将MBEDTLS_PK_SIGNURE_MAX_SIZE设置为支持的签名类型中的最大签名大小。通过从0开始，然后逐渐增加到足以支持每个签名机制的大小来实现。
 *
 * 例如，如果启用了MBEDTLS_CDH_C（这允许包含pk模块），但既没有MBEDTLS_CDSA_C也没有MBEDLLS_RSA_C，也没有任何不透明的签名机制（PSA或RSA_ALT），则结果值可以为0。
 */
#define MBEDTLS_PK_SIGNATURE_MAX_SIZE 0

#if ( defined(MBEDTLS_RSA_C) || defined(MBEDTLS_PK_RSA_ALT_SUPPORT) ) && \
    MBEDTLS_MPI_MAX_SIZE > MBEDTLS_PK_SIGNATURE_MAX_SIZE
/* 对于RSA，签名可以是bignum模块允许的最大值。对于RSA_ALT，签名大小不一定与bignum模块的功能相关，但在没有任何特定设置的情况下，我们使用它（pk_wrap中的RSA\ALT_sign_wrap将进行检查）。*/
#undef MBEDTLS_PK_SIGNATURE_MAX_SIZE
#define MBEDTLS_PK_SIGNATURE_MAX_SIZE MBEDTLS_MPI_MAX_SIZE
#endif

#if defined(MBEDTLS_ECDSA_C) &&                                 \
    MBEDTLS_ECDSA_MAX_LEN > MBEDTLS_PK_SIGNATURE_MAX_SIZE
/* 对于ECDSA，ECDSA模块导出最大签名大小的常量。*/
#undef MBEDTLS_PK_SIGNATURE_MAX_SIZE
#define MBEDTLS_PK_SIGNATURE_MAX_SIZE MBEDTLS_ECDSA_MAX_LEN
#endif

#if defined(MBEDTLS_USE_PSA_CRYPTO)
#if PSA_SIGNATURE_MAX_SIZE > MBEDTLS_PK_SIGNATURE_MAX_SIZE
/* PSA_SIGNATURE_MAX_SIZE是通过PSA表示中的PSA API生成的签名的最大大小。*/
#undef MBEDTLS_PK_SIGNATURE_MAX_SIZE
#define MBEDTLS_PK_SIGNATURE_MAX_SIZE PSA_SIGNATURE_MAX_SIZE
#endif

#if PSA_VENDOR_ECDSA_SIGNATURE_MAX_SIZE + 11 > MBEDTLS_PK_SIGNATURE_MAX_SIZE
/* 对于ECDSA签名，Mbed TLS表示不同：PSA使用r和s的原始连接，而Mbed TLS使用ASN。1表示（两个整数的序列）。增加ASN的开销。1： 对于INTEGER和SEQUENCE的类型、长度（由最多2个字节表示）和可能的前导零，最多为（1+2）+2（1+2+1）。*/
#undef MBEDTLS_PK_SIGNATURE_MAX_SIZE
#define MBEDTLS_PK_SIGNATURE_MAX_SIZE ( PSA_VENDOR_ECDSA_SIGNATURE_MAX_SIZE + 11 )
#endif
#endif /* 已定义（MBEDTLS_USE_PSA_CRYPTO）*/

/**
 * \与调试模块接口的简要类型
 */
typedef enum
{
    MBEDTLS_PK_DEBUG_NONE = 0,
    MBEDTLS_PK_DEBUG_MPI,
    MBEDTLS_PK_DEBUG_ECP,
} mbedtls_pk_debug_type;

/**
 * \要发送到调试模块的简要项
 */
typedef struct mbedtls_pk_debug_item
{
    mbedtls_pk_debug_type type;
    const char *name;
    void *value;
} mbedtls_pk_debug_item;

/**发送用于调试的最大项目数，加1*/
#define MBEDTLS_PK_DEBUG_MAX_ITEMS 3

/**
 * \简要公钥信息和操作
 */
typedef struct mbedtls_pk_info_t mbedtls_pk_info_t;

/**
 * \简短公钥容器
 */
typedef struct mbedtls_pk_context
{
    const mbedtls_pk_info_t *   pk_info; /**<公钥信息*/
    void *                      pk_ctx;  /**<基础公钥上下文*/
} mbedtls_pk_context;

#if defined(MBEDTLS_ECDSA_C) && defined(MBEDTLS_ECP_RESTARTABLE)
/**
 * \恢复操作的简要上下文
 */
typedef struct
{
    const mbedtls_pk_info_t *   pk_info; /**<公钥信息*/
    void *                      rs_ctx;  /**<基础重新启动上下文*/
} mbedtls_pk_restart_ctx;
#else /* MBEDTLS_ECDSA_C && MBEDTLS_ECP_RESTARTABLE */
/* 现在我们可以声明一个指向它的函数*/
typedef void mbedtls_pk_restart_ctx;
#endif /* MBEDTLS_ECDSA_C && MBEDTLS_ECP_RESTARTABLE */

#if defined(MBEDTLS_RSA_C)
/**
 * 快速访问PK上下文中的RSA上下文。
 *
 * \警告在使用此函数之前，必须确保PK上下文实际上包含RSA上下文！
 */
static inline mbedtls_rsa_context *mbedtls_pk_rsa( const mbedtls_pk_context pk )
{
    return( (mbedtls_rsa_context *) (pk).pk_ctx );
}
#endif /* MBEDTLS_RSA_C */

#if defined(MBEDTLS_ECP_C)
/**
 * 快速访问PK上下文中的EC上下文。
 *
 * \警告在使用此函数之前，必须确保PK上下文实际上包含EC上下文！
 */
static inline mbedtls_ecp_keypair *mbedtls_pk_ec( const mbedtls_pk_context pk )
{
    return( (mbedtls_ecp_keypair *) (pk).pk_ctx );
}
#endif /* MBEDTLS_ECP_C */

#if defined(MBEDTLS_PK_RSA_ALT_SUPPORT)
/**
 * \RSA alt抽象的简要类型
 */
typedef int (*mbedtls_pk_rsa_alt_decrypt_func)( void *ctx, int mode, size_t *olen,
                    const unsigned char *input, unsigned char *output,
                    size_t output_max_len );
typedef int (*mbedtls_pk_rsa_alt_sign_func)( void *ctx,
                    int (*f_rng)(void *, unsigned char *, size_t), void *p_rng,
                    int mode, mbedtls_md_type_t md_alg, unsigned int hashlen,
                    const unsigned char *hash, unsigned char *sig );
typedef size_t (*mbedtls_pk_rsa_alt_key_len_func)( void *ctx );
#endif /* MBEDTLS_PK_RSA_ALT_SUPPORT */

/**
 * \与给定PK类型相关的简短返回信息
 *
 * \param pk_type要搜索的pk类型。
 *
 * \返回与该类型关联的PK信息，如果找不到，则返回NULL。
 */
const mbedtls_pk_info_t *mbedtls_pk_info_from_type( mbedtls_pk_type_t pk_type );

/**
 * \brief初始化#mbedtls_pk_context（作为NONE）。
 *
 * \param ctx要初始化的上下文。此值不能为空。
 */
void mbedtls_pk_init( mbedtls_pk_context *ctx );

/**
 * \brief释放#mbedtls_pk_context的组件。
 *
 * \param ctx要清除的上下文。它必须已初始化。如果该值为空，则此函数不执行任何操作。
 *
 * \注意：对于已使用mbedtls_pk_setup_opaque（）设置的上下文，这不会释放底层PSA密钥，如果要销毁该密钥，仍需要单独调用PSA_destroy_key（）。
 */
void mbedtls_pk_free( mbedtls_pk_context *ctx );

#if defined(MBEDTLS_ECDSA_C) && defined(MBEDTLS_ECP_RESTARTABLE)
/**
 * \brief初始化重新启动上下文
 *
 * \param ctx要初始化的上下文。此值不能为空。
 */
void mbedtls_pk_restart_init( mbedtls_pk_restart_ctx *ctx );

/**
 * \brief释放重新启动上下文的组件
 *
 * \param ctx要清除的上下文。它必须已初始化。如果该值为空，则此函数不执行任何操作。
 */
void mbedtls_pk_restart_free( mbedtls_pk_restart_ctx *ctx );
#endif /* MBEDTLS_ECDSA_C && MBEDTLS_ECP_RESTARTABLE */

/**
 * \brief使用给定的信息初始化PK上下文，并分配特定于类型的PK子上下文。
 *
 * \param ctx要初始化的上下文。它必须尚未设置（类型#MBEDTLS_PK_NONE）。\param info要使用的信息
 *
 * \成功时返回0，无效输入时返回MBEDTLS_ERROR_PK_BAD_INPUT_DATA，分配失败时返回MBEDTLS_ERR_PK_ALLOC_FAILED。
 *
 * \注意：对于包含RSA alt密钥的上下文，请改用\c mbedtls_pk_setup_RSA_alt（）。
 */
int mbedtls_pk_setup( mbedtls_pk_context *ctx, const mbedtls_pk_info_t *info );

#if defined(MBEDTLS_USE_PSA_CRYPTO)
/**
 * \brief初始化PK上下文以包装PSA密钥。
 *
 * \注意：对于包装（可能是不透明的）PSA密钥的上下文，此函数将取代mbedtls_pk_setup（），而不是直接存储和操作密钥材料。
 *
 * \param ctx要初始化的上下文。它必须为空（类型NONE）。\param key要换行的PSA密钥，它必须包含一个ECC密钥对（请参阅下面的注释）。
 *
 * \注意：只要包装PK上下文在使用，包装密钥就必须保持有效，即至少在调用此函数的点和在此上下文上调用mbedtls_PK_free（）的点之间。然后可以独立使用或销毁包装的密钥。
 *
 * \注意：此功能当前仅适用于ECC密钥对（即，包含私钥材料的ECC密钥）。稍后可能会添加对其他密钥类型的支持。
 *
 * \成功时返回\c 0。\在无效输入上返回#MBEDTLS_ERROR_PK_BAD_INPUT_DATA（上下文已使用，密钥标识符无效）。\如果密钥不是ECC密钥对，则返回#MBEDTLS_ERROR_PK_FEATURE_NAVAILABLE。\分配失败时返回#MBEDTLS_ERROR_PK_ALLOC_FAILED。
 */
int mbedtls_pk_setup_opaque( mbedtls_pk_context *ctx,
                             const psa_key_id_t key );
#endif /* MBEDTLS_USE_PSA_CRYPTO */

#if defined(MBEDTLS_PK_RSA_ALT_SUPPORT)
/**
 * \brief初始化RSA alt上下文
 *
 * \param ctx要初始化的上下文。它必须尚未设置（类型#MBEDTLS_PK_NONE）。\param key RSA密钥指针\param decrypt_func解密函数\param sign_func签名函数/param key_len_func返回密钥长度（字节）的函数
 *
 * \如果上下文尚未初始化为RSA_ALT，则返回0。
 *
 * \注意：此函数替换RSA-alt\c mbedtls_pk_setup（）。
 */
int mbedtls_pk_setup_rsa_alt( mbedtls_pk_context *ctx, void * key,
                         mbedtls_pk_rsa_alt_decrypt_func decrypt_func,
                         mbedtls_pk_rsa_alt_sign_func sign_func,
                         mbedtls_pk_rsa_alt_key_len_func key_len_func );
#endif /* MBEDTLS_PK_RSA_ALT_SUPPORT */

/**
 * \brief获取基础密钥的位大小
 *
 * \param ctx要查询的上下文。它必须已初始化。
 *
 * \return密钥大小（以位为单位），或出错时返回0
 */
size_t mbedtls_pk_get_bitlen( const mbedtls_pk_context *ctx );

/**
 * \brief获取基础密钥的字节长度
 *
 * \param ctx要查询的上下文。它必须已初始化。
 *
 * \return密钥长度（以字节为单位），错误时为0
 */
static inline size_t mbedtls_pk_get_len( const mbedtls_pk_context *ctx )
{
    return( ( mbedtls_pk_get_bitlen( ctx ) + 7 ) / 8 );
}

/**
 * \brief告诉上下文是否可以执行类型给定的操作
 *
 * \param ctx要查询的上下文。它必须已初始化。\param type所需的类型。
 *
 * \如果上下文可以对给定类型执行操作，则返回1。\如果上下文无法对给定类型执行操作，则返回0。对于已初始化但未设置的上下文，或已使用mbedtls_pk_free（）清除的上下文，情况总是如此。
 */
int mbedtls_pk_can_do( const mbedtls_pk_context *ctx, mbedtls_pk_type_t type );

/**
 * \简短验证签名（包括相关的填充）。
 *
 * \param ctx要使用的PK上下文。它一定已经设置好了。\param md_alg使用的哈希算法（请参阅注释）\param要签名的消息的哈希\param Hash_len Hash长度或0（请参阅备注）\pram sig要验证的签名\param sig_len签名长度
 *
 * \成功时返回0（签名有效），#MBEDTLS_error_PK_SIG_LEN_MISMATCH（如果SIG中有有效签名，但其长度小于\p siglen）或特定错误代码。
 *
 * \注意：对于RSA密钥，默认填充类型为PKCS#1 v1.5。请使用\c mbedtls_pk_verify_ext（mbedtls_pk_RASSA_PSS，…）验证RSASSA_PSS签名。
 *
 * \注意：如果hash_len为0，则使用与md_alg关联的长度，如果无效，则返回错误。
 *
 * \注意，只有当hash_len！=0
 */
int mbedtls_pk_verify( mbedtls_pk_context *ctx, mbedtls_md_type_t md_alg,
               const unsigned char *hash, size_t hash_len,
               const unsigned char *sig, size_t sig_len );

/**
 * \\c mbedtls_pk_verify（）的简短可重启版本
 *
 * \注意：执行与\c mbedtls_pk_verify（）相同的作业，但可以提前返回并根据\c mbedt ls_ecp_set_max_ops（）设置的限制重新启动，以减少ECC操作的阻塞。对于RSA，与\c mbedtls_pk_verify（）相同。
 *
 * \param ctx要使用的PK上下文。它一定已经设置好了。\param md_alg使用的哈希算法（请参阅注释）\param要签名的消息的哈希\param Hash_len Hash length或0（请参阅备注）\param sig要验证的签名\param sig_len签名长度\param rs_ctx重新启动上下文（NULL表示禁用重新启动）
 *
 * \return请参见\c mbedtls_pk_verify（），或者如果已达到最大操作数，请参见\return#mbedtls_ERROR_ECP_IN_PROGRESS：请参见\cmbedtls_ECP_set_max_ops（）。
 */
int mbedtls_pk_verify_restartable( mbedtls_pk_context *ctx,
               mbedtls_md_type_t md_alg,
               const unsigned char *hash, size_t hash_len,
               const unsigned char *sig, size_t sig_len,
               mbedtls_pk_restart_ctx *rs_ctx );

/**
 * \简短验证签名，带选项。（包括根据类型验证填充。）
 *
 * \param type要验证的签名类型（包括可能的填充类型）\param options指向类型特定选项的指针，或NULL\param ctx要使用的PK上下文。它一定已经设置好了。\param md_alg使用的哈希算法（请参阅注释）\param要签名的消息的哈希\param Hash_len Hash长度或0（请参阅备注）\pram sig要验证的签名\param sig_len签名长度
 *
 * \成功时返回0（签名有效），如果PK上下文不能用于此类型的签名，则返回#MBEDTLS_error_PK_TYPE_MISMATCH，如果SIG中存在有效签名，但其长度小于\p siglen，则返回#MBEDTLS_error_PK_SIG_LEN_MISMATCH，或者返回特定的错误代码。
 *
 * \注意：如果hash_len为0，则使用与md_alg关联的长度，如果无效，则返回错误。
 *
 * \注意，只有当hash_len！=0
 *
 * \注意：如果类型为MBEDTLS_PK_RASSA_PSS，则options必须指向MBEDTLS_PK_rasassa_PSS_options结构，否则必须为NULL。
 */
int mbedtls_pk_verify_ext( mbedtls_pk_type_t type, const void *options,
                   mbedtls_pk_context *ctx, mbedtls_md_type_t md_alg,
                   const unsigned char *hash, size_t hash_len,
                   const unsigned char *sig, size_t sig_len );

/**
 * \简短签名，包括相关的填充。
 *
 * \param ctx要使用的PK上下文。它必须是用私钥设置的。\param md_alg使用的哈希算法（请参阅注释）\param要签名的消息的哈希值\param Hash_len哈希长度或0（请参阅备注）\pram sig写入签名的位置。它必须有足够的空间来签名#MBEDTLS_PK_SIGNATURE_MAX_SIZE总是足够的。如果给定密钥类型，缓冲区足够大，则可以使用较小的缓冲区。\param sig_len成功返回时，写入\p sig的字节数。\param f_rng rng函数\param p_rng rng参数
 *
 * \成功时返回0或特定错误代码。
 *
 * \注意：对于RSA密钥，默认填充类型为PKCS#1 v1.5。PK模块中还没有生成RSASSA-PSS签名的接口。
 *
 * \注意：如果hash_len为0，则使用与md_alg关联的长度，如果无效，则返回错误。
 *
 * \注意：对于RSA，如果hash_len！=0。对于ECDSA，md_alg可能永远不是MBEDTLS_md_NONE。
 */
int mbedtls_pk_sign( mbedtls_pk_context *ctx, mbedtls_md_type_t md_alg,
             const unsigned char *hash, size_t hash_len,
             unsigned char *sig, size_t *sig_len,
             int (*f_rng)(void *, unsigned char *, size_t), void *p_rng );

/**
 * \\c mbedtls_pk_sign（）的简短可重启版本
 *
 * \注意：执行与\c mbedtls_pk_sign（）相同的作业，但可以提前返回并根据\c mbedt ls_ecp_set_max_ops（）设置的限制重新启动，以减少ECC操作的阻塞。对于RSA，与\c mbedtls_pk_sign（）相同。
 *
 * \param ctx要使用的PK上下文。它必须是用私钥设置的。\param md_alg使用的哈希算法（请参见mbedtls_pk_sign（）的注释）\param要签名的消息的哈希值\param Hash_len哈希长度或0（请参阅mbedtls_prk_sign（）的说明）\pram sig写入签名的位置。它必须有足够的空间来签名#MBEDTLS_PK_SIGNATURE_MAX_SIZE总是足够的。如果给定密钥类型，缓冲区足够大，则可以使用较小的缓冲区。\param sig_len成功返回时，写入\p sig的字节数。\param f_rng rng函数\param p_rng rng参数\param rs_ctx重新启动上下文（NULL表示禁用重新启动）
 *
 * \return请参见\c mbedtls_pk_sign（）。\如果已达到最大操作数，返回#MBEDTLS_ERROR_ECP_IN_PROGRESS：请参阅\c MBEDTLS_ECP_set_max_ops（）。
 */
int mbedtls_pk_sign_restartable( mbedtls_pk_context *ctx,
             mbedtls_md_type_t md_alg,
             const unsigned char *hash, size_t hash_len,
             unsigned char *sig, size_t *sig_len,
             int (*f_rng)(void *, unsigned char *, size_t), void *p_rng,
             mbedtls_pk_restart_ctx *rs_ctx );

/**
 * \简短的解密消息（包括相关的填充）。
 *
 * \param ctx要使用的PK上下文。它必须是用私钥设置的。\param input要解密的输入\param ilen输入大小\param output解密的输出\param olen解密的消息长度\param osize输出缓冲区的大小\pram f_rng rng函数\param p_rng rng参数
 *
 * \注意：对于RSA密钥，默认填充类型为PKCS#1 v1.5。
 *
 * \成功时返回0或特定错误代码。
 */
int mbedtls_pk_decrypt( mbedtls_pk_context *ctx,
                const unsigned char *input, size_t ilen,
                unsigned char *output, size_t *olen, size_t osize,
                int (*f_rng)(void *, unsigned char *, size_t), void *p_rng );

/**
 * \简短的加密消息（包括相关的填充）。
 *
 * \param ctx要使用的PK上下文。它一定已经设置好了。\param input要加密的消息\param ilen消息大小\param output加密的输出\param olen加密的输出长度\param osize输出缓冲区的大小\pram f_rng rng函数\param p_rng rng参数
 *
 * \注意：对于RSA密钥，默认填充类型为PKCS#1 v1.5。
 *
 * \成功时返回0或特定错误代码。
 */
int mbedtls_pk_encrypt( mbedtls_pk_context *ctx,
                const unsigned char *input, size_t ilen,
                unsigned char *output, size_t *olen, size_t osize,
                int (*f_rng)(void *, unsigned char *, size_t), void *p_rng );

/**
 * \brief检查公私密钥对是否匹配。
 *
 * \param pub保存公钥的上下文。\param prv保存私钥（和公钥）的上下文。
 *
 * \成功时返回\c 0（已检查密钥并相互匹配）。\如果无法检查密钥，则返回#MBEDTLS_ERROR_PK_FEATURE_NAVAILABLE-在这种情况下，它们可能匹配，也可能不匹配。\如果上下文无效，则返回#MBEDTLS_ERROR_PK_BAD_INPUT_DATA。\如果键不匹配，则返回另一个非零值。
 */
int mbedtls_pk_check_pair( const mbedtls_pk_context *pub, const mbedtls_pk_context *prv );

/**
 * \简要导出调试信息
 *
 * \param ctx要使用的PK上下文。它必须已初始化。\param items写入调试项的位置
 *
 * \成功时返回0或MBEDTLS_ERROR_PK_BAD_INPUT_DATA
 */
int mbedtls_pk_debug( const mbedtls_pk_context *ctx, mbedtls_pk_debug_item *items );

/**
 * \brief访问类型名称
 *
 * \param ctx要使用的PK上下文。它必须已初始化。
 *
 * \成功时返回类型名称，或“无效PK”
 */
const char * mbedtls_pk_get_name( const mbedtls_pk_context *ctx );

/**
 * \brief获取密钥类型
 *
 * \param ctx要使用的PK上下文。它必须已初始化。
 *
 * \return成功时返回类型。\对于尚未设置的上下文，返回#MBEDTLS_PK_NONE。
 */
mbedtls_pk_type_t mbedtls_pk_get_type( const mbedtls_pk_context *ctx );

#if defined(MBEDTLS_PK_PARSE_C)
/**\in组pk_module*/
/**
 * \简要分析PEM或DER格式的私钥
 *
 * \param ctx要填充的PK上下文。它必须已初始化但未设置。\param key要分析的输入缓冲区。缓冲区必须完全包含输入，并且没有额外的尾部材料。对于PEM，缓冲区必须包含以空结尾的字符串。\param keylen \b密钥的大小（以字节为单位）。对于PEM数据，这包括终止的空字节，因此\p keylen必须等于“strlen（key）+1”。\param pwd用于解密的可选密码。如果需要非加密密钥，则传递\c NULL。如果需要加密密钥，则传递一个\p pwdlen字节的字符串；也将接受非加密密钥。不支持空密码。\param pwdlen密码的大小（字节）。如果\p pwd为\c NULL，则忽略。
 *
 * \注意：在输入时，ctx必须为空，要么是用mbedtls_pk_init（）新初始化的，要么是使用mbedtls_prk_free（）重置的。如果需要特定的密钥类型，请使用mbedtls_pk_can_do（）检查结果。
 *
 * \注意：还将检查密钥的正确性。
 *
 * \如果成功，则返回0，或者返回特定的PK或PEM错误代码
 */
int mbedtls_pk_parse_key( mbedtls_pk_context *ctx,
                  const unsigned char *key, size_t keylen,
                  const unsigned char *pwd, size_t pwdlen );

/**\in组pk_module*/
/**
 * \简要分析PEM或DER格式的公钥
 *
 * \param ctx要填充的PK上下文。它必须已初始化但未设置。\param key要分析的输入缓冲区。缓冲区必须完全包含输入，并且没有额外的尾部材料。对于PEM，缓冲区必须包含以空结尾的字符串。\param keylen \b密钥的大小（以字节为单位）。对于PEM数据，这包括终止的空字节，因此\p keylen必须等于“strlen（key）+1”。
 *
 * \注意：在输入时，ctx必须为空，要么是用mbedtls_pk_init（）新初始化的，要么是使用mbedtls_prk_free（）重置的。如果需要特定的密钥类型，请使用mbedtls_pk_can_do（）检查结果。
 *
 * \注意：还将检查密钥的正确性。
 *
 * \如果成功，则返回0，或者返回特定的PK或PEM错误代码
 */
int mbedtls_pk_parse_public_key( mbedtls_pk_context *ctx,
                         const unsigned char *key, size_t keylen );

#if defined(MBEDTLS_FS_IO)
/**\in组pk_module*/
/**
 * \brief加载并解析私钥
 *
 * \param ctx要填充的PK上下文。它必须已初始化但未设置。\param path从中读取私钥的文件名\param password用于解密文件的可选密码。如果需要非加密密钥，则传递\c NULL。如果需要加密密钥，则传递以空结尾的字符串；也将接受非加密密钥。不支持空密码。
 *
 * \注意：在输入时，ctx必须为空，要么是用mbedtls_pk_init（）新初始化的，要么是使用mbedtls_prk_free（）重置的。如果需要特定的密钥类型，请使用mbedtls_pk_can_do（）检查结果。
 *
 * \注意：还将检查密钥的正确性。
 *
 * \如果成功，则返回0，或者返回特定的PK或PEM错误代码
 */
int mbedtls_pk_parse_keyfile( mbedtls_pk_context *ctx,
                      const char *path, const char *password );

/**\in组pk_module*/
/**
 * \brief加载并解析公钥
 *
 * \param ctx要填充的PK上下文。它必须已初始化但未设置。\param读取公钥的路径文件名
 *
 * \注意：在输入时，ctx必须为空，要么是用mbedtls_pk_init（）新初始化的，要么是使用mbedtls_prk_free（）重置的。如果需要特定的密钥类型，请使用mbedtls_pk_can_do（）检查结果。
 *
 * \注意：还将检查密钥的正确性。
 *
 * \如果成功，则返回0，或者返回特定的PK或PEM错误代码
 */
int mbedtls_pk_parse_public_keyfile( mbedtls_pk_context *ctx, const char *path );
#endif /* MBEDTLS_FS_IO */
#endif /* MBEDTLS_PK_PARSE_C */

#if defined(MBEDTLS_PK_WRITE_C)
/**
 * \brief将私钥写入PKCS#1或SEC1DER结构注意：数据写入缓冲区的末尾！使用返回值确定应该从何处开始使用缓冲区
 *
 * \param ctx PK上下文，该上下文必须包含有效的私钥。\要写入的param buf缓冲区\param缓冲区大小
 *
 * \如果成功，返回写入的数据长度，或返回特定的错误代码
 */
int mbedtls_pk_write_key_der( mbedtls_pk_context *ctx, unsigned char *buf, size_t size );

/**
 * \brief将公钥写入SubjectPublicKeyInfo DER结构注意：数据写入缓冲区的末尾！使用返回值确定应该从何处开始使用缓冲区
 *
 * \param ctx PK上下文，该上下文必须包含有效的公钥或私钥。\要写入的param buf缓冲区\param缓冲区大小
 *
 * \如果成功，返回写入的数据长度，或返回特定的错误代码
 */
int mbedtls_pk_write_pubkey_der( mbedtls_pk_context *ctx, unsigned char *buf, size_t size );

#if defined(MBEDTLS_PEM_WRITE_C)
/**
 * \brief将公钥写入PEM字符串
 *
 * \param ctx PK上下文，该上下文必须包含有效的公钥或私钥。\param buf要写入的缓冲区。输出包括终止的空字节。\param size缓冲区的大小（字节）。
 *
 * \如果成功，则返回0，或返回特定的错误代码
 */
int mbedtls_pk_write_pubkey_pem( mbedtls_pk_context *ctx, unsigned char *buf, size_t size );

/**
 * \brief将私钥写入PKCS#1或SEC1 PEM字符串
 *
 * \param ctx PK上下文，该上下文必须包含有效的私钥。\param buf要写入的缓冲区。输出包括终止的空字节。\param size缓冲区的大小（字节）。
 *
 * \如果成功，则返回0，或返回特定的错误代码
 */
int mbedtls_pk_write_key_pem( mbedtls_pk_context *ctx, unsigned char *buf, size_t size );
#endif /* MBEDTLS_PEM_WRITE_C */
#endif /* MBEDTLS_PK_WRITE_C */

/*
 * 警告：低级功能。除非您确定要使用，否则您可能不想使用这些；）
 */

#if defined(MBEDTLS_PK_PARSE_C)
/**
 * \简要分析SubjectPublicKeyInfo DER结构
 *
 * \param p ASN中的位置。1 data\param缓冲区结束\param pk要填充的pk上下文。它必须已初始化但未设置。
 *
 * \如果成功，则返回0，或返回特定PK错误代码
 */
int mbedtls_pk_parse_subpubkey( unsigned char **p, const unsigned char *end,
                        mbedtls_pk_context *pk );
#endif /* MBEDTLS_PK_PARSE_C */

#if defined(MBEDTLS_PK_WRITE_C)
/**
 * \brief编写主题PublicKey给ASN。1数据注意：函数在数据缓冲区中向后工作
 *
 * \param p对当前位置指针的引用\param缓冲区的开始（用于边界检查）\param密钥PK上下文，该上下文必须包含有效的公钥或私钥。
 *
 * \返回写入的长度或负错误代码
 */
int mbedtls_pk_write_pubkey( unsigned char **p, unsigned char *start,
                     const mbedtls_pk_context *key );
#endif /* MBEDTLS_PK_WRITE_C */

/*
 * 内部模块功能。除非你知道，否则你可能不想使用这些。
 */
#if defined(MBEDTLS_FS_IO)
int mbedtls_pk_load_file( const char *path, unsigned char **buf, size_t *n );
#endif

#if defined(MBEDTLS_USE_PSA_CRYPTO)
/**
 * \brief将EC密钥转换为不透明密钥。
 *
 * \警告这是测试的临时实用程序函数。它可能随时更改或删除，恕不另行通知。
 *
 * \注意到目前为止，仅支持ECDSA密钥。使用指定的哈希签名是唯一允许使用该密钥的方法。
 *
 * \param pk输入：要导入到PSA密钥的EC密钥。输出：包装该PSA密钥的PK上下文。\param key输出：PSA密钥标识符。在pk上下文上调用mbedtls_pk_free（）之后，调用方负责对该密钥标识符调用psa_dedestroy_key（）。\param hash_alg允许与该密钥一起使用的哈希算法。
 *
 * \如果成功，返回\c 0。\否则返回Mbed TLS错误代码。
 */
int mbedtls_pk_wrap_as_opaque( mbedtls_pk_context *pk,
                               psa_key_id_t *key,
                               psa_algorithm_t hash_alg );
#endif /* MBEDTLS_USE_PSA_CRYPTO */

#ifdef __cplusplus
}
#endif

#endif /* MBEDTLS_PK_H */

