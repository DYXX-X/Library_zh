/**
 * \文件psa_util.h
 *
 * \PSA Crypto库使用的简短实用函数。
 *
 * \警告此函数不是公共API的一部分，可能随时更改。
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

#ifndef MBEDTLS_PSA_UTIL_H
#define MBEDTLS_PSA_UTIL_H

#if !defined(MBEDTLS_CONFIG_FILE)
#include "mbedtls/config.h"
#else
#include MBEDTLS_CONFIG_FILE
#endif

#if defined(MBEDTLS_USE_PSA_CRYPTO)

#include "psa/crypto.h"

#include "mbedtls/ecp.h"
#include "mbedtls/md.h"
#include "mbedtls/pk.h"
#include "mbedtls/oid.h"

#include <string.h>

/* 对称加密的翻译。*/

static inline psa_key_type_t mbedtls_psa_translate_cipher_type(
    mbedtls_cipher_type_t cipher )
{
    switch( cipher )
    {
        case MBEDTLS_CIPHER_AES_128_CCM:
        case MBEDTLS_CIPHER_AES_192_CCM:
        case MBEDTLS_CIPHER_AES_256_CCM:
        case MBEDTLS_CIPHER_AES_128_GCM:
        case MBEDTLS_CIPHER_AES_192_GCM:
        case MBEDTLS_CIPHER_AES_256_GCM:
        case MBEDTLS_CIPHER_AES_128_CBC:
        case MBEDTLS_CIPHER_AES_192_CBC:
        case MBEDTLS_CIPHER_AES_256_CBC:
        case MBEDTLS_CIPHER_AES_128_ECB:
        case MBEDTLS_CIPHER_AES_192_ECB:
        case MBEDTLS_CIPHER_AES_256_ECB:
            return( PSA_KEY_TYPE_AES );

        /* PSA尚未支持ARIA。*/
        /* case MBEDTLS_CIPHER_ARIA_128_CCM:case MBEDLS_CIPHER_ARIA_192_CCM:case MBEDTLS_CIPHER_ARIA_256_CCM:ccase MBEDTL_CIPHER-ARIA_128_GCM:case EMBEDLS_CIP HER_ARIA_1 92_GCM:caseMBEDTLs_CHIHER_ARIA_2 56_GCM:ccase EMBEDTLS_CHIHER_ARIA_128_CBC:case MBEDTLS-CIPHER_ARIA_292_CBC:caseMBETLS_CIPHER_ARIA_156_CBC:cese返回（PSA_KEY_TYPE_ARIA）；*/

        default:
            return( 0 );
    }
}

static inline psa_algorithm_t mbedtls_psa_translate_cipher_mode(
    mbedtls_cipher_mode_t mode, size_t taglen )
{
    switch( mode )
    {
        case MBEDTLS_MODE_ECB:
            return( PSA_ALG_ECB_NO_PADDING );
        case MBEDTLS_MODE_GCM:
            return( PSA_ALG_AEAD_WITH_SHORTENED_TAG( PSA_ALG_GCM, taglen ) );
        case MBEDTLS_MODE_CCM:
            return( PSA_ALG_AEAD_WITH_SHORTENED_TAG( PSA_ALG_CCM, taglen ) );
        case MBEDTLS_MODE_CBC:
            if( taglen == 0 )
                return( PSA_ALG_CBC_NO_PADDING );
            else
                return( 0 );
        default:
            return( 0 );
    }
}

static inline psa_key_usage_t mbedtls_psa_translate_cipher_operation(
    mbedtls_operation_t op )
{
    switch( op )
    {
        case MBEDTLS_ENCRYPT:
            return( PSA_KEY_USAGE_ENCRYPT );
        case MBEDTLS_DECRYPT:
            return( PSA_KEY_USAGE_DECRYPT );
        default:
            return( 0 );
    }
}

/* 哈希的翻译。*/

static inline psa_algorithm_t mbedtls_psa_translate_md( mbedtls_md_type_t md_alg )
{
    switch( md_alg )
    {
#if defined(MBEDTLS_MD2_C)
    case MBEDTLS_MD_MD2:
        return( PSA_ALG_MD2 );
#endif
#if defined(MBEDTLS_MD4_C)
    case MBEDTLS_MD_MD4:
        return( PSA_ALG_MD4 );
#endif
#if defined(MBEDTLS_MD5_C)
    case MBEDTLS_MD_MD5:
        return( PSA_ALG_MD5 );
#endif
#if defined(MBEDTLS_SHA1_C)
    case MBEDTLS_MD_SHA1:
        return( PSA_ALG_SHA_1 );
#endif
#if defined(MBEDTLS_SHA256_C)
    case MBEDTLS_MD_SHA224:
        return( PSA_ALG_SHA_224 );
    case MBEDTLS_MD_SHA256:
        return( PSA_ALG_SHA_256 );
#endif
#if defined(MBEDTLS_SHA512_C)
    case MBEDTLS_MD_SHA384:
        return( PSA_ALG_SHA_384 );
    case MBEDTLS_MD_SHA512:
        return( PSA_ALG_SHA_512 );
#endif
#if defined(MBEDTLS_RIPEMD160_C)
    case MBEDTLS_MD_RIPEMD160:
        return( PSA_ALG_RIPEMD160 );
#endif
    case MBEDTLS_MD_NONE:
        return( 0 );
    default:
        return( 0 );
    }
}

/* ECC翻译。*/

static inline int mbedtls_psa_get_ecc_oid_from_id(
    psa_ecc_family_t curve, size_t bits,
    char const **oid, size_t *oid_len )
{
    switch( curve )
    {
        case PSA_ECC_FAMILY_SECP_R1:
            switch( bits )
            {
#if defined(MBEDTLS_ECP_DP_SECP192R1_ENABLED)
                case 192:
                    *oid = MBEDTLS_OID_EC_GRP_SECP192R1;
                    *oid_len = MBEDTLS_OID_SIZE( MBEDTLS_OID_EC_GRP_SECP192R1 );
                    return( 0 );
#endif /* MBEDTLS_ECP_DP_SECP192R1_ENABLED */
#if defined(MBEDTLS_ECP_DP_SECP224R1_ENABLED)
                case 224:
                    *oid = MBEDTLS_OID_EC_GRP_SECP224R1;
                    *oid_len = MBEDTLS_OID_SIZE( MBEDTLS_OID_EC_GRP_SECP224R1 );
                    return( 0 );
#endif /* MBEDTLS_ECP_DP_SECP224R1_ENABLED */
#if defined(MBEDTLS_ECP_DP_SECP256R1_ENABLED)
                case 256:
                    *oid = MBEDTLS_OID_EC_GRP_SECP256R1;
                    *oid_len = MBEDTLS_OID_SIZE( MBEDTLS_OID_EC_GRP_SECP256R1 );
                    return( 0 );
#endif /* MBEDTLS_ECP_DP_SECP256R1_ENABLED */
#if defined(MBEDTLS_ECP_DP_SECP384R1_ENABLED)
                case 384:
                    *oid = MBEDTLS_OID_EC_GRP_SECP384R1;
                    *oid_len = MBEDTLS_OID_SIZE( MBEDTLS_OID_EC_GRP_SECP384R1 );
                    return( 0 );
#endif /* MBEDTLS_ECP_DP_SECP384R1_ENABLED */
#if defined(MBEDTLS_ECP_DP_SECP521R1_ENABLED)
                case 521:
                    *oid = MBEDTLS_OID_EC_GRP_SECP521R1;
                    *oid_len = MBEDTLS_OID_SIZE( MBEDTLS_OID_EC_GRP_SECP521R1 );
                    return( 0 );
#endif /* MBEDTLS_ECP_DP_SECP521R1_ENABLED */
            }
            break;
        case PSA_ECC_FAMILY_SECP_K1:
            switch( bits )
            {
#if defined(MBEDTLS_ECP_DP_SECP192K1_ENABLED)
                case 192:
                    *oid = MBEDTLS_OID_EC_GRP_SECP192K1;
                    *oid_len = MBEDTLS_OID_SIZE( MBEDTLS_OID_EC_GRP_SECP192K1 );
                    return( 0 );
#endif /* MBEDTLS_ECP_DP_SECP192K1_ENABLED */
#if defined(MBEDTLS_ECP_DP_SECP224K1_ENABLED)
                case 224:
                    *oid = MBEDTLS_OID_EC_GRP_SECP224K1;
                    *oid_len = MBEDTLS_OID_SIZE( MBEDTLS_OID_EC_GRP_SECP224K1 );
                    return( 0 );
#endif /* MBEDTLS_ECP_DP_SECP224K1_ENABLED */
#if defined(MBEDTLS_ECP_DP_SECP256K1_ENABLED)
                case 256:
                    *oid = MBEDTLS_OID_EC_GRP_SECP256K1;
                    *oid_len = MBEDTLS_OID_SIZE( MBEDTLS_OID_EC_GRP_SECP256K1 );
                    return( 0 );
#endif /* MBEDTLS_ECP_DP_SECP256K1_ENABLED */
            }
            break;
        case PSA_ECC_FAMILY_BRAINPOOL_P_R1:
            switch( bits )
            {
#if defined(MBEDTLS_ECP_DP_BP256R1_ENABLED)
                case 256:
                    *oid = MBEDTLS_OID_EC_GRP_BP256R1;
                    *oid_len = MBEDTLS_OID_SIZE( MBEDTLS_OID_EC_GRP_BP256R1 );
                    return( 0 );
#endif /* MBEDTLS_ECP_DP_BP256R1_ENABLED */
#if defined(MBEDTLS_ECP_DP_BP384R1_ENABLED)
                case 384:
                    *oid = MBEDTLS_OID_EC_GRP_BP384R1;
                    *oid_len = MBEDTLS_OID_SIZE( MBEDTLS_OID_EC_GRP_BP384R1 );
                    return( 0 );
#endif /* MBEDTLS_ECP_DP_BP384R1_ENABLED */
#if defined(MBEDTLS_ECP_DP_BP512R1_ENABLED)
                case 512:
                    *oid = MBEDTLS_OID_EC_GRP_BP512R1;
                    *oid_len = MBEDTLS_OID_SIZE( MBEDTLS_OID_EC_GRP_BP512R1 );
                    return( 0 );
#endif /* MBEDTLS_ECP_DP_BP512R1_ENABLED */
            }
            break;
    }
    (void) oid;
    (void) oid_len;
    return( -1 );
}

#define MBEDTLS_PSA_MAX_EC_PUBKEY_LENGTH 1

#if defined(MBEDTLS_ECP_DP_SECP192R1_ENABLED)
#if MBEDTLS_PSA_MAX_EC_PUBKEY_LENGTH < ( 2 * ( ( 192 + 7 ) / 8 ) + 1 )
#undef MBEDTLS_PSA_MAX_EC_PUBKEY_LENGTH
#define MBEDTLS_PSA_MAX_EC_PUBKEY_LENGTH ( 2 * ( ( 192 + 7 ) / 8 ) + 1 )
#endif
#endif /* MBEDTLS_ECP_DP_SECP192R1_ENABLED */

#if defined(MBEDTLS_ECP_DP_SECP224R1_ENABLED)
#if MBEDTLS_PSA_MAX_EC_PUBKEY_LENGTH < ( 2 * ( ( 224 + 7 ) / 8 ) + 1 )
#undef MBEDTLS_PSA_MAX_EC_PUBKEY_LENGTH
#define MBEDTLS_PSA_MAX_EC_PUBKEY_LENGTH ( 2 * ( ( 224 + 7 ) / 8 ) + 1 )
#endif
#endif /* MBEDTLS_ECP_DP_SECP224R1_ENABLED */

#if defined(MBEDTLS_ECP_DP_SECP256R1_ENABLED)
#if MBEDTLS_PSA_MAX_EC_PUBKEY_LENGTH < ( 2 * ( ( 256 + 7 ) / 8 ) + 1 )
#undef MBEDTLS_PSA_MAX_EC_PUBKEY_LENGTH
#define MBEDTLS_PSA_MAX_EC_PUBKEY_LENGTH ( 2 * ( ( 256 + 7 ) / 8 ) + 1 )
#endif
#endif /* MBEDTLS_ECP_DP_SECP256R1_ENABLED */

#if defined(MBEDTLS_ECP_DP_SECP384R1_ENABLED)
#if MBEDTLS_PSA_MAX_EC_PUBKEY_LENGTH < ( 2 * ( ( 384 + 7 ) / 8 ) + 1 )
#undef MBEDTLS_PSA_MAX_EC_PUBKEY_LENGTH
#define MBEDTLS_PSA_MAX_EC_PUBKEY_LENGTH ( 2 * ( ( 384 + 7 ) / 8 ) + 1 )
#endif
#endif /* MBEDTLS_ECP_DP_SECP384R1_ENABLED */

#if defined(MBEDTLS_ECP_DP_SECP521R1_ENABLED)
#if MBEDTLS_PSA_MAX_EC_PUBKEY_LENGTH < ( 2 * ( ( 521 + 7 ) / 8 ) + 1 )
#undef MBEDTLS_PSA_MAX_EC_PUBKEY_LENGTH
#define MBEDTLS_PSA_MAX_EC_PUBKEY_LENGTH ( 2 * ( ( 521 + 7 ) / 8 ) + 1 )
#endif
#endif /* MBEDTLS_ECP_DP_SECP521R1_ENABLED */

#if defined(MBEDTLS_ECP_DP_SECP192K1_ENABLED)
#if MBEDTLS_PSA_MAX_EC_PUBKEY_LENGTH < ( 2 * ( ( 192 + 7 ) / 8 ) + 1 )
#undef MBEDTLS_PSA_MAX_EC_PUBKEY_LENGTH
#define MBEDTLS_PSA_MAX_EC_PUBKEY_LENGTH ( 2 * ( ( 192 + 7 ) / 8 ) + 1 )
#endif
#endif /* MBEDTLS_ECP_DP_SECP192K1_ENABLED */

#if defined(MBEDTLS_ECP_DP_SECP224K1_ENABLED)
#if MBEDTLS_PSA_MAX_EC_PUBKEY_LENGTH < ( 2 * ( ( 224 + 7 ) / 8 ) + 1 )
#undef MBEDTLS_PSA_MAX_EC_PUBKEY_LENGTH
#define MBEDTLS_PSA_MAX_EC_PUBKEY_LENGTH ( 2 * ( ( 224 + 7 ) / 8 ) + 1 )
#endif
#endif /* MBEDTLS_ECP_DP_SECP224K1_ENABLED */

#if defined(MBEDTLS_ECP_DP_SECP256K1_ENABLED)
#if MBEDTLS_PSA_MAX_EC_PUBKEY_LENGTH < ( 2 * ( ( 256 + 7 ) / 8 ) + 1 )
#undef MBEDTLS_PSA_MAX_EC_PUBKEY_LENGTH
#define MBEDTLS_PSA_MAX_EC_PUBKEY_LENGTH ( 2 * ( ( 256 + 7 ) / 8 ) + 1 )
#endif
#endif /* MBEDTLS_ECP_DP_SECP256K1_ENABLED */

#if defined(MBEDTLS_ECP_DP_BP256R1_ENABLED)
#if MBEDTLS_PSA_MAX_EC_PUBKEY_LENGTH < ( 2 * ( ( 256 + 7 ) / 8 ) + 1 )
#undef MBEDTLS_PSA_MAX_EC_PUBKEY_LENGTH
#define MBEDTLS_PSA_MAX_EC_PUBKEY_LENGTH ( 2 * ( ( 256 + 7 ) / 8 ) + 1 )
#endif
#endif /* MBEDTLS_ECP_DP_BP256R1_ENABLED */

#if defined(MBEDTLS_ECP_DP_BP384R1_ENABLED)
#if MBEDTLS_PSA_MAX_EC_PUBKEY_LENGTH < ( 2 * ( ( 384 + 7 ) / 8 ) + 1 )
#undef MBEDTLS_PSA_MAX_EC_PUBKEY_LENGTH
#define MBEDTLS_PSA_MAX_EC_PUBKEY_LENGTH ( 2 * ( ( 384 + 7 ) / 8 ) + 1 )
#endif
#endif /* MBEDTLS_ECP_DP_BP384R1_ENABLED */

#if defined(MBEDTLS_ECP_DP_BP512R1_ENABLED)
#if MBEDTLS_PSA_MAX_EC_PUBKEY_LENGTH < ( 2 * ( ( 512 + 7 ) / 8 ) + 1 )
#undef MBEDTLS_PSA_MAX_EC_PUBKEY_LENGTH
#define MBEDTLS_PSA_MAX_EC_PUBKEY_LENGTH ( 2 * ( ( 512 + 7 ) / 8 ) + 1 )
#endif
#endif /* MBEDTLS_ECP_DP_BP512R1_ENABLED */


/* PK层的翻译*/

static inline int mbedtls_psa_err_translate_pk( psa_status_t status )
{
    switch( status )
    {
        case PSA_SUCCESS:
            return( 0 );
        case PSA_ERROR_NOT_SUPPORTED:
            return( MBEDTLS_ERR_PK_FEATURE_UNAVAILABLE );
        case PSA_ERROR_INSUFFICIENT_MEMORY:
            return( MBEDTLS_ERR_PK_ALLOC_FAILED );
        case PSA_ERROR_INSUFFICIENT_ENTROPY:
            return( MBEDTLS_ERR_ECP_RANDOM_FAILED );
        case PSA_ERROR_BAD_STATE:
            return( MBEDTLS_ERR_PK_BAD_INPUT_DATA );
        /* 所有其他故障*/
        case PSA_ERROR_COMMUNICATION_FAILURE:
        case PSA_ERROR_HARDWARE_FAILURE:
        case PSA_ERROR_CORRUPTION_DETECTED:
            return( MBEDTLS_ERR_PK_HW_ACCEL_FAILED );
        default: /* 我们返回的结果与“其他故障”相同，但将它们单独列出，以表明我们考虑了哪些故障条件。*/
            return( MBEDTLS_ERR_PK_HW_ACCEL_FAILED );
    }
}

/* ECC翻译*/

/* 此函数将ECC组标识符从https://www.iana.org/assignments/tls-parameters/tls-parameters.xhtml#tls-参数-8转换为PSA ECC组标识符。*/
#if defined(MBEDTLS_ECP_C)
static inline psa_key_type_t mbedtls_psa_parse_tls_ecc_group(
    uint16_t tls_ecc_grp_reg_id, size_t *bits )
{
    const mbedtls_ecp_curve_info *curve_info =
        mbedtls_ecp_curve_info_from_tls_id( tls_ecc_grp_reg_id );
    if( curve_info == NULL )
        return( 0 );
    return( PSA_KEY_TYPE_ECC_KEY_PAIR(
                mbedtls_ecc_group_to_psa( curve_info->grp_id, bits ) ) );
}
#endif /* MBEDTLS_ECP_C */

/* 此函数获取一个缓冲区，该缓冲区保存通过psa_export_public_key（）导出的EC公钥，并将其转换为ECPoint结构，以放入ECDHE交换中的ClientKeyExchange消息中。
 *
 * PSA使用的EC公钥的当前格式和可预见的未来格式都具有包含在导出密钥中的ECPoint结构作为子缓冲区，该函数仅选择该子缓冲区而不是复制。
 */
static inline int mbedtls_psa_tls_psa_ec_to_ecpoint( unsigned char *src,
                                                     size_t srclen,
                                                     unsigned char **dst,
                                                     size_t *dstlen )
{
    *dst = src;
    *dstlen = srclen;
    return( 0 );
}

/* 此函数获取一个保存ECPoint结构的缓冲区（包含在ECDHE交换的TLS ServerKeyExchange消息中），并将其转换为PSA密钥协议API可以理解的格式。
 */
static inline int mbedtls_psa_tls_ecpoint_to_psa_ec( unsigned char const *src,
                                                     size_t srclen,
                                                     unsigned char *dst,
                                                     size_t dstlen,
                                                     size_t *olen )
{
    if( srclen > dstlen )
        return( MBEDTLS_ERR_ECP_BUFFER_TOO_SMALL );

    memcpy( dst, src, srclen );
    *olen = srclen;
    return( 0 );
}

#endif /* MBEDTLS_USE_PSA_CRYPTO */

/* 使用mbedtls_xxx API向应用程序公开PSA子系统使用的任何RNG。这里的声明和定义需要与库/psa_crypto_random_inmpl.h中的实现保持一致。有关实现文档，请参阅该文件。*/
#if defined(MBEDTLS_PSA_CRYPTO_C)

/* 许多库函数采用的“f_rng”随机生成器函数的类型。
 *
 * 此类型名称不是Mbed TLS稳定API的一部分。它可以在没有警告的情况下重命名或移动。
 */
typedef int mbedtls_f_rng_t( void *p_rng, unsigned char *output, size_t output_size );

#if defined(MBEDTLS_PSA_CRYPTO_EXTERNAL_RNG)

/** PSA子系统的随机发生器功能。
 *
 * 此函数适用于许多“mbedtls_xxx”函数的“f_rng”随机生成器函数参数。使用#MBEDTLS_PSA_RANDOM_STATE获取\p p_rng参数。
 *
 * 此函数的实现取决于库的配置。
 *
 * \注意：根据配置，这可能是一个函数或指向函数的指针。
 *
 * \注意：只有当PSA密码子系统处于活动状态时，才能使用此功能。这意味着在调用此函数之前必须调用psa_crypto_init（），并且在调用mbedtls_psa_crypto_free（）之后不能调用此函数。
 *
 * \param p_rng随机生成器上下文。这必须是#MBEDTLS_PSA_RANDOM_STATE。不支持其他状态。\param output要填充的缓冲区。它必须有空间容纳\c output_size字节。\param output_size要写入\p输出的字节数。如果\p output_size太大，此函数可能会失败。它保证接受Mbed TLS库函数请求的任何输出大小。最大请求大小取决于库配置。
 *
 * \成功时返回\c 0。\错误时返回`MBEDTLS_error_ENTROPY_xxx`、`MBEDLLS_error_PLATFORM_xxx、`MBEDTLS_ERR_CTR_DRBG_xxx`或`MBEDRLS_error_HMAC_DRBG_xxx `。
 */
int mbedtls_psa_get_random( void *p_rng,
                            unsigned char *output,
                            size_t output_size );

/** PSA子系统的随机生成器状态。
 *
 * 此宏扩展到一个表达式，该表达式适合作为许多“mbedtls_xxx”函数的“p_rng”随机生成器状态参数。它必须与随机生成器函数mbedtls_psa_get_random（）结合使用。
 *
 * 此宏的实现取决于库的配置。不要对其性质作出任何假设。
 */
#define MBEDTLS_PSA_RANDOM_STATE NULL

#else /* !已定义（MBEDTLS_PSA_CRYPTO_EXTERNAL_RNG）*/

#if defined(MBEDTLS_CTR_DRBG_C)
#include "mbedtls/ctr_drbg.h"
typedef mbedtls_ctr_drbg_context mbedtls_psa_drbg_context_t;
static mbedtls_f_rng_t *const mbedtls_psa_get_random = mbedtls_ctr_drbg_random;
#elif defined(MBEDTLS_HMAC_DRBG_C)
#include "mbedtls/hmac_drbg.h"
typedef mbedtls_hmac_drbg_context mbedtls_psa_drbg_context_t;
static mbedtls_f_rng_t *const mbedtls_psa_get_random = mbedtls_hmac_drbg_random;
#endif
extern mbedtls_psa_drbg_context_t *const mbedtls_psa_random_state;

#define MBEDTLS_PSA_RANDOM_STATE mbedtls_psa_random_state

#endif /* !已定义（MBEDTLS_PSA_CRYPTO_EXTERNAL_RNG）*/

#endif /* MBEDTLS_PSA_CRYPTO_C */

#endif /* MBEDTLS_PSA_UTIL_H */

