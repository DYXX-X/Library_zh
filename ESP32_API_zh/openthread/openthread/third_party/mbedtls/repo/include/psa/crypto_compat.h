/**
 * \psa/crypto_compat.h文件
 *
 * \PSA密码模块简介：向后兼容别名
 *
 * 此标头声明宏和函数的可选名称。新应用程序代码不应使用这些名称。这些名称可能会在未来版本的Mbed Crypto中删除。
 *
 * \注意：此文件可能不直接包含。应用程序必须包括psa/crypto.h。
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

#ifndef PSA_CRYPTO_COMPAT_H
#define PSA_CRYPTO_COMPAT_H

#ifdef __cplusplus
extern "C" {
#endif

/*
 * 要暂时支持无开放API和psa_open_key（），请将psa_key_handle_t定义为等于mbedtls_svc_key_id_t。不要将该类型及其实用程序宏和函数标记为已弃用。这将在后续阶段完成。
 */
typedef mbedtls_svc_key_id_t psa_key_handle_t;

#define PSA_KEY_HANDLE_INIT MBEDTLS_SVC_KEY_ID_INIT

/** 检查句柄是否为空。
 *
 * \param句柄句柄
 *
 * \如果句柄为空，则返回非零，否则返回零。
 */
static inline int psa_key_handle_is_null( psa_key_handle_t handle )
{
    return( mbedtls_svc_key_id_is_null( handle ) );
}

#if !defined(MBEDTLS_DEPRECATED_REMOVED)

/*
 * 声明弃用值的机制
 */
#if defined(MBEDTLS_DEPRECATED_WARNING) && !defined(MBEDTLS_PSA_DEPRECATED)
#define MBEDTLS_PSA_DEPRECATED __attribute__((deprecated))
#else
#define MBEDTLS_PSA_DEPRECATED
#endif

typedef MBEDTLS_PSA_DEPRECATED size_t mbedtls_deprecated_size_t;
typedef MBEDTLS_PSA_DEPRECATED psa_status_t mbedtls_deprecated_psa_status_t;
typedef MBEDTLS_PSA_DEPRECATED psa_key_usage_t mbedtls_deprecated_psa_key_usage_t;
typedef MBEDTLS_PSA_DEPRECATED psa_ecc_family_t mbedtls_deprecated_psa_ecc_family_t;
typedef MBEDTLS_PSA_DEPRECATED psa_dh_family_t mbedtls_deprecated_psa_dh_family_t;
typedef MBEDTLS_PSA_DEPRECATED psa_ecc_family_t psa_ecc_curve_t;
typedef MBEDTLS_PSA_DEPRECATED psa_dh_family_t psa_dh_group_t;
typedef MBEDTLS_PSA_DEPRECATED psa_algorithm_t mbedtls_deprecated_psa_algorithm_t;

#define PSA_KEY_TYPE_GET_CURVE PSA_KEY_TYPE_ECC_GET_FAMILY
#define PSA_KEY_TYPE_GET_GROUP PSA_KEY_TYPE_DH_GET_FAMILY

#define MBEDTLS_DEPRECATED_CONSTANT( type, value )      \
    ( (mbedtls_deprecated_##type) ( value ) )

/*
 * 不推荐的PSA Crypto错误代码定义（PSA CryptoAPI<=1.0 beta2）
 */
#define PSA_ERROR_UNKNOWN_ERROR \
    MBEDTLS_DEPRECATED_CONSTANT( psa_status_t, PSA_ERROR_GENERIC_ERROR )
#define PSA_ERROR_OCCUPIED_SLOT \
    MBEDTLS_DEPRECATED_CONSTANT( psa_status_t, PSA_ERROR_ALREADY_EXISTS )
#define PSA_ERROR_EMPTY_SLOT \
    MBEDTLS_DEPRECATED_CONSTANT( psa_status_t, PSA_ERROR_DOES_NOT_EXIST )
#define PSA_ERROR_INSUFFICIENT_CAPACITY \
    MBEDTLS_DEPRECATED_CONSTANT( psa_status_t, PSA_ERROR_INSUFFICIENT_DATA )
#define PSA_ERROR_TAMPERING_DETECTED \
    MBEDTLS_DEPRECATED_CONSTANT( psa_status_t, PSA_ERROR_CORRUPTION_DETECTED )

/*
 * 不推荐的PSA加密数字编码（PSA加密API<=1.0 beta3）
 */
#define PSA_KEY_USAGE_SIGN \
    MBEDTLS_DEPRECATED_CONSTANT( psa_key_usage_t, PSA_KEY_USAGE_SIGN_HASH )
#define PSA_KEY_USAGE_VERIFY \
    MBEDTLS_DEPRECATED_CONSTANT( psa_key_usage_t, PSA_KEY_USAGE_VERIFY_HASH )

/*
 * 不推荐的PSA Crypto大小计算宏（PSA CryptoAPI<=1.0 beta3）
 */
#define PSA_ASYMMETRIC_SIGNATURE_MAX_SIZE \
    MBEDTLS_DEPRECATED_CONSTANT( size_t, PSA_SIGNATURE_MAX_SIZE )
#define PSA_ASYMMETRIC_SIGN_OUTPUT_SIZE( key_type, key_bits, alg ) \
    MBEDTLS_DEPRECATED_CONSTANT( size_t, PSA_SIGN_OUTPUT_SIZE( key_type, key_bits, alg ) )

/*
 * 弃用的PSA Crypto函数名称（PSA CryptoAPI<=1.0 beta3）
 */
MBEDTLS_PSA_DEPRECATED static inline psa_status_t psa_asymmetric_sign( psa_key_handle_t key,
                            psa_algorithm_t alg,
                            const uint8_t *hash,
                            size_t hash_length,
                            uint8_t *signature,
                            size_t signature_size,
                            size_t *signature_length )
{
    return psa_sign_hash( key, alg, hash, hash_length, signature, signature_size, signature_length );
}

MBEDTLS_PSA_DEPRECATED static inline psa_status_t psa_asymmetric_verify( psa_key_handle_t key,
                              psa_algorithm_t alg,
                              const uint8_t *hash,
                              size_t hash_length,
                              const uint8_t *signature,
                              size_t signature_length )
{
    return psa_verify_hash( key, alg, hash, hash_length, signature, signature_length );
}

/*
 * 大小特定的椭圆曲线族。
 */
#define PSA_ECC_CURVE_SECP160K1 \
    MBEDTLS_DEPRECATED_CONSTANT( psa_ecc_family_t, PSA_ECC_FAMILY_SECP_K1 )
#define PSA_ECC_CURVE_SECP192K1 \
    MBEDTLS_DEPRECATED_CONSTANT( psa_ecc_family_t, PSA_ECC_FAMILY_SECP_K1 )
#define PSA_ECC_CURVE_SECP224K1 \
    MBEDTLS_DEPRECATED_CONSTANT( psa_ecc_family_t, PSA_ECC_FAMILY_SECP_K1 )
#define PSA_ECC_CURVE_SECP256K1 \
    MBEDTLS_DEPRECATED_CONSTANT( psa_ecc_family_t, PSA_ECC_FAMILY_SECP_K1 )
#define PSA_ECC_CURVE_SECP160R1 \
    MBEDTLS_DEPRECATED_CONSTANT( psa_ecc_family_t, PSA_ECC_FAMILY_SECP_R1 )
#define PSA_ECC_CURVE_SECP192R1 \
    MBEDTLS_DEPRECATED_CONSTANT( psa_ecc_family_t, PSA_ECC_FAMILY_SECP_R1 )
#define PSA_ECC_CURVE_SECP224R1 \
    MBEDTLS_DEPRECATED_CONSTANT( psa_ecc_family_t, PSA_ECC_FAMILY_SECP_R1 )
#define PSA_ECC_CURVE_SECP256R1 \
    MBEDTLS_DEPRECATED_CONSTANT( psa_ecc_family_t, PSA_ECC_FAMILY_SECP_R1 )
#define PSA_ECC_CURVE_SECP384R1 \
    MBEDTLS_DEPRECATED_CONSTANT( psa_ecc_family_t, PSA_ECC_FAMILY_SECP_R1 )
#define PSA_ECC_CURVE_SECP521R1 \
    MBEDTLS_DEPRECATED_CONSTANT( psa_ecc_family_t, PSA_ECC_FAMILY_SECP_R1 )
#define PSA_ECC_CURVE_SECP160R2 \
    MBEDTLS_DEPRECATED_CONSTANT( psa_ecc_family_t, PSA_ECC_FAMILY_SECP_R2 )
#define PSA_ECC_CURVE_SECT163K1 \
    MBEDTLS_DEPRECATED_CONSTANT( psa_ecc_family_t, PSA_ECC_FAMILY_SECT_K1 )
#define PSA_ECC_CURVE_SECT233K1 \
    MBEDTLS_DEPRECATED_CONSTANT( psa_ecc_family_t, PSA_ECC_FAMILY_SECT_K1 )
#define PSA_ECC_CURVE_SECT239K1 \
    MBEDTLS_DEPRECATED_CONSTANT( psa_ecc_family_t, PSA_ECC_FAMILY_SECT_K1 )
#define PSA_ECC_CURVE_SECT283K1 \
    MBEDTLS_DEPRECATED_CONSTANT( psa_ecc_family_t, PSA_ECC_FAMILY_SECT_K1 )
#define PSA_ECC_CURVE_SECT409K1 \
    MBEDTLS_DEPRECATED_CONSTANT( psa_ecc_family_t, PSA_ECC_FAMILY_SECT_K1 )
#define PSA_ECC_CURVE_SECT571K1 \
    MBEDTLS_DEPRECATED_CONSTANT( psa_ecc_family_t, PSA_ECC_FAMILY_SECT_K1 )
#define PSA_ECC_CURVE_SECT163R1 \
    MBEDTLS_DEPRECATED_CONSTANT( psa_ecc_family_t, PSA_ECC_FAMILY_SECT_R1 )
#define PSA_ECC_CURVE_SECT193R1 \
    MBEDTLS_DEPRECATED_CONSTANT( psa_ecc_family_t, PSA_ECC_FAMILY_SECT_R1 )
#define PSA_ECC_CURVE_SECT233R1 \
    MBEDTLS_DEPRECATED_CONSTANT( psa_ecc_family_t, PSA_ECC_FAMILY_SECT_R1 )
#define PSA_ECC_CURVE_SECT283R1 \
    MBEDTLS_DEPRECATED_CONSTANT( psa_ecc_family_t, PSA_ECC_FAMILY_SECT_R1 )
#define PSA_ECC_CURVE_SECT409R1 \
    MBEDTLS_DEPRECATED_CONSTANT( psa_ecc_family_t, PSA_ECC_FAMILY_SECT_R1 )
#define PSA_ECC_CURVE_SECT571R1 \
    MBEDTLS_DEPRECATED_CONSTANT( psa_ecc_family_t, PSA_ECC_FAMILY_SECT_R1 )
#define PSA_ECC_CURVE_SECT163R2 \
    MBEDTLS_DEPRECATED_CONSTANT( psa_ecc_family_t, PSA_ECC_FAMILY_SECT_R2 )
#define PSA_ECC_CURVE_SECT193R2 \
    MBEDTLS_DEPRECATED_CONSTANT( psa_ecc_family_t, PSA_ECC_FAMILY_SECT_R2 )
#define PSA_ECC_CURVE_BRAINPOOL_P256R1 \
    MBEDTLS_DEPRECATED_CONSTANT( psa_ecc_family_t, PSA_ECC_FAMILY_BRAINPOOL_P_R1 )
#define PSA_ECC_CURVE_BRAINPOOL_P384R1 \
    MBEDTLS_DEPRECATED_CONSTANT( psa_ecc_family_t, PSA_ECC_FAMILY_BRAINPOOL_P_R1 )
#define PSA_ECC_CURVE_BRAINPOOL_P512R1 \
    MBEDTLS_DEPRECATED_CONSTANT( psa_ecc_family_t, PSA_ECC_FAMILY_BRAINPOOL_P_R1 )
#define PSA_ECC_CURVE_CURVE25519 \
    MBEDTLS_DEPRECATED_CONSTANT( psa_ecc_family_t, PSA_ECC_FAMILY_MONTGOMERY )
#define PSA_ECC_CURVE_CURVE448 \
    MBEDTLS_DEPRECATED_CONSTANT( psa_ecc_family_t, PSA_ECC_FAMILY_MONTGOMERY )

/*
 * 因PSA规范而更改名称的曲线。
 */
#define PSA_ECC_CURVE_SECP_K1 \
    MBEDTLS_DEPRECATED_CONSTANT( psa_ecc_family_t, PSA_ECC_FAMILY_SECP_K1 )
#define PSA_ECC_CURVE_SECP_R1 \
    MBEDTLS_DEPRECATED_CONSTANT( psa_ecc_family_t, PSA_ECC_FAMILY_SECP_R1 )
#define PSA_ECC_CURVE_SECP_R2 \
    MBEDTLS_DEPRECATED_CONSTANT( psa_ecc_family_t, PSA_ECC_FAMILY_SECP_R2 )
#define PSA_ECC_CURVE_SECT_K1 \
    MBEDTLS_DEPRECATED_CONSTANT( psa_ecc_family_t, PSA_ECC_FAMILY_SECT_K1 )
#define PSA_ECC_CURVE_SECT_R1 \
    MBEDTLS_DEPRECATED_CONSTANT( psa_ecc_family_t, PSA_ECC_FAMILY_SECT_R1 )
#define PSA_ECC_CURVE_SECT_R2 \
    MBEDTLS_DEPRECATED_CONSTANT( psa_ecc_family_t, PSA_ECC_FAMILY_SECT_R2 )
#define PSA_ECC_CURVE_BRAINPOOL_P_R1 \
    MBEDTLS_DEPRECATED_CONSTANT( psa_ecc_family_t, PSA_ECC_FAMILY_BRAINPOOL_P_R1 )
#define PSA_ECC_CURVE_MONTGOMERY \
    MBEDTLS_DEPRECATED_CONSTANT( psa_ecc_family_t, PSA_ECC_FAMILY_MONTGOMERY )

/*
 * 有限域Diffie-Hellman族。
 */
#define PSA_DH_GROUP_FFDHE2048 \
    MBEDTLS_DEPRECATED_CONSTANT( psa_dh_family_t, PSA_DH_FAMILY_RFC7919 )
#define PSA_DH_GROUP_FFDHE3072 \
    MBEDTLS_DEPRECATED_CONSTANT( psa_dh_family_t, PSA_DH_FAMILY_RFC7919 )
#define PSA_DH_GROUP_FFDHE4096 \
    MBEDTLS_DEPRECATED_CONSTANT( psa_dh_family_t, PSA_DH_FAMILY_RFC7919 )
#define PSA_DH_GROUP_FFDHE6144 \
    MBEDTLS_DEPRECATED_CONSTANT( psa_dh_family_t, PSA_DH_FAMILY_RFC7919 )
#define PSA_DH_GROUP_FFDHE8192 \
    MBEDTLS_DEPRECATED_CONSTANT( psa_dh_family_t, PSA_DH_FAMILY_RFC7919 )

/*
 * Diffie-Hellman家族因PSA规范而更名。
 */
#define PSA_DH_GROUP_RFC7919 \
    MBEDTLS_DEPRECATED_CONSTANT( psa_dh_family_t, PSA_DH_FAMILY_RFC7919 )
#define PSA_DH_GROUP_CUSTOM \
    MBEDTLS_DEPRECATED_CONSTANT( psa_dh_family_t, PSA_DH_FAMILY_CUSTOM )

/*
 * 不推荐的PSA Crypto流密码算法（PSA CryptoAPI<=1.0 beta3）
 */
#define PSA_ALG_ARC4 \
    MBEDTLS_DEPRECATED_CONSTANT( psa_algorithm_t, PSA_ALG_STREAM_CIPHER )
#define PSA_ALG_CHACHA20 \
    MBEDTLS_DEPRECATED_CONSTANT( psa_algorithm_t, PSA_ALG_STREAM_CIPHER )

#endif /* MBEDTLS_DEPRECATED_REMOVED */

/** 打开现有持久密钥的句柄。
 *
 * 打开持久密钥的句柄。如果密钥是使用非#PSA_key_lifetime_VOLATILE的生存期创建的，则该密钥是持久的。持久密钥始终具有非零密钥标识符，在创建密钥时使用psa_set_key_id（）进行设置。实现可以提供额外的预配置密钥，这些密钥可以使用psa_open_key（）打开。如#psa_key_id_t描述中所述，此类密钥在供应商范围内具有应用程序密钥标识符。
 *
 * 应用程序最终必须使用psa_close_key（）或psa_destry_key（）关闭句柄以释放相关资源。如果应用程序在没有调用其中一个函数的情况下死亡，那么实现应该执行与调用psa_close_key（）等效的操作。
 *
 * 一些实现允许应用程序多次打开同一密钥。如果成功，对psa_open_key（）的每次调用都将返回不同的密钥句柄。
 *
 * \注意：此API不是PSA Cryptography API Release 1.0.0规范的一部分。它是在1.0 Beta 3版本的规范中定义的，但在1.0.0发布版本中被删除。暂时保留此API，以免破坏依赖它的应用程序。它尚未被弃用，但将在不久的将来被弃用。
 *
 * \注意，依赖于多次打开键的应用程序将不能移植到只允许打开单个键手柄的实现中。另请参见：ref:\`key handles\`。
 *
 * \param key键的持久标识符。\param[out]handle成功时，密钥的句柄。
 *
 * \retval#PSA_SUCCESS成功。应用程序现在可以使用“handle”值来访问密钥。\retval#PSA_ERROR_INSUFFIE_MEMORY实现没有足够的资源来打开密钥。这可能是由于达到了打开键的数量、打开键句柄的数量或可用内存的实现限制。\retval#PSA_ERROR_DOES_NOT_EXIST没有具有密钥标识符的持久密钥。\ p id不是有效的持久密钥标识符。\retval#PSA_ERROR_NOT_PERMITTED指定的密钥存在，但应用程序无权访问它。请注意，本规范没有定义创建此类密钥的任何方式，但可以通过特定于实现的方式实现。\retval#PSA_ERROR_COMMUNICATION_FAILURE\retval#PSTA_ERROR_CORRUPTION_DETECTED\retval#PSA_ERROR_STORAGE_FAILURE \retval#PSA_ERROR_BAD_STATE该库以前未由PSA_crypto_init（）初始化。初始化失败是否导致此错误代码取决于实现。
 */
psa_status_t psa_open_key( mbedtls_svc_key_id_t key,
                           psa_key_handle_t *handle );

/** 关闭钥匙手柄。
 *
 * 如果句柄指定了一个易失性密钥，这将销毁密钥材料并释放所有相关资源，就像psa_destry_key（）一样。
 *
 * 如果这是持久密钥的最后一个打开句柄，那么关闭句柄将释放易失性内存中与该密钥相关的所有资源。持久存储中的密钥数据不受影响，稍后可以通过调用psa_open_key（）再次打开。
 *
 * 关闭密钥句柄会使句柄无效，应用程序不能再次使用密钥句柄。
 *
 * \注意：此API不是PSA Cryptography API Release 1.0.0规范的一部分。它是在1.0 Beta 3版本的规范中定义的，但在1.0.0发布版本中被删除。暂时保留此API，以免破坏依赖它的应用程序。它尚未被弃用，但将在不久的将来被弃用。
 *
 * \注意：如果键句柄用于设置活动的：ref:\`multipart operation<multipart operations>\`，则关闭键句柄会导致多部分操作失败。应用程序应保持密钥句柄，直到多部分操作完成。
 *
 * \param handle要关闭的键句柄。如果这是\c 0，则不执行任何操作并返回\c PSA_SUCCESS。
 *
 * \retval#PSA_SUCCESS\p句柄是有效的句柄或\c 0。它现在已关闭。\retval#PSA_ERROR_INVALID_HANDLE\p句柄不是有效的句柄，也不是0。\retval#PSA _ERROR_COMMUNICATION_FAILURE\retval#PSA_ERROR_CORRUPTION_DETECTED \retval＃PSA_ERROR_BAD_STATE该库以前未由PSA_crypto_init（）初始化。初始化失败是否导致此错误代码取决于实现。
 */
psa_status_t psa_close_key(psa_key_handle_t handle);

#ifdef __cplusplus
}
#endif

#endif /* PSA_CRYPTO_COMPAT_H */

