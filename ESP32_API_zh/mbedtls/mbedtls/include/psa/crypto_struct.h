/**
 * \psa/crypto_struct.h文件
 *
 * \简短的PSA加密模块：Mbed TLS结构化类型实现
 *
 * \注意：此文件可能不直接包含。应用程序必须包括psa/crypto.h。
 *
 * 此文件包含一些具有特定于实现的定义的数据结构的定义。
 *
 * 在应用程序和加密模块之间具有隔离的实现中，预期前端和后端将具有此文件的不同版本。
 *
 * <h3>关于多部分操作结构的设计注意事项</h3>
 *
 * 对于不支持驱动程序委派的多部分操作，每个多部分操作结构都包含一个“psa_algorithm_t alg”字段，该字段指示该结构用于哪个特定算法。当结构不使用时，“alg”为0。大多数结构由一个由“alg’区分的并集组成。
 *
 * 对于支持驱动程序委派的多部分操作，每个多部分操作结构都包含一个“unsigned int id”字段，指示分配给哪个驱动程序执行该操作。当结构未使用时，“id”为0。该结构还包含一个驱动程序上下文，该上下文是能够处理多部分操作类型的所有驱动程序的上下文的联合。
 *
 * 注意，当“alg”或“id”为0时，其他字段的内容未定义。特别是，不能保证新初始化的结构都为零：我们将结构初始化为类似于“｛0，0｝”，这只保证初始化联合的第一个成员；GCC和Clang将整个结构初始化为0（在编写时），但MSVC和CompCert没有。
 *
 * 在Mbed Crypto中，多部分操作结构独立于密钥。这允许Mbed Crypto在销毁密钥槽时释放密钥对象。如果在设置函数返回后，多部分操作需要记住密钥，则操作结构需要包含密钥的副本。
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

#ifndef PSA_CRYPTO_STRUCT_H
#define PSA_CRYPTO_STRUCT_H

#ifdef __cplusplus
extern "C" {
#endif

/* 包括Mbed TLS配置文件，即Mbed TLS在其每个头文件中执行的方式。*/
#if !defined(MBEDTLS_CONFIG_FILE)
#include "mbedtls/config.h"
#else
#include MBEDTLS_CONFIG_FILE
#endif

#include "mbedtls/cmac.h"
#include "mbedtls/gcm.h"

/* 包括原始算法的编译驱动程序的上下文定义。*/
#include "psa/crypto_driver_contexts_primitives.h"

struct psa_hash_operation_s
{
    /**唯一ID，指示分配给哪个驱动程序执行操作。由于驱动程序上下文是特定于驱动程序的，因此不支持在操作中途交换驱动程序。ID值在psa_driver_wrappers.h中自动生成。ID值为零表示上下文无效或未分配给任何驱动程序（即驱动程序上下文未激活，正在使用）。*/
    unsigned int id;
    psa_driver_hash_context_t ctx;
};

#define PSA_HASH_OPERATION_INIT {0, {0}}
static inline struct psa_hash_operation_s psa_hash_operation_init( void )
{
    const struct psa_hash_operation_s v = PSA_HASH_OPERATION_INIT;
    return( v );
}

struct psa_cipher_operation_s
{
    /**唯一ID，指示分配给哪个驱动程序执行操作。由于驱动程序上下文是特定于驱动程序的，因此不支持在操作中途交换驱动程序。ID值在psa_crypto_driver_wrappers中自动生成。h ID值为零表示上下文无效或未分配给任何驱动程序（即，没有驱动程序上下文是活动的）。*/
    unsigned int id;

    unsigned int iv_required : 1;
    unsigned int iv_set : 1;

    uint8_t default_iv_length;

    psa_driver_cipher_context_t ctx;
};

#define PSA_CIPHER_OPERATION_INIT {0, 0, 0, 0, {0}}
static inline struct psa_cipher_operation_s psa_cipher_operation_init( void )
{
    const struct psa_cipher_operation_s v = PSA_CIPHER_OPERATION_INIT;
    return( v );
}

/* 包括复合算法的编译驱动程序的上下文定义。*/
#include "psa/crypto_driver_contexts_composites.h"

struct psa_mac_operation_s
{
    /**唯一ID，指示分配给哪个驱动程序执行操作。由于驱动程序上下文是特定于驱动程序的，因此不支持在操作中途交换驱动程序。ID值在psa_driver_wrappers中自动生成。h ID值为零表示上下文无效或未分配给任何驱动程序（即，没有驱动程序上下文是活动的）。*/
    unsigned int id;
    uint8_t mac_size;
    unsigned int is_sign : 1;
    psa_driver_mac_context_t ctx;
};

#define PSA_MAC_OPERATION_INIT {0, 0, 0, {0}}
static inline struct psa_mac_operation_s psa_mac_operation_init( void )
{
    const struct psa_mac_operation_s v = PSA_MAC_OPERATION_INIT;
    return( v );
}

struct psa_aead_operation_s
{
    psa_algorithm_t alg;
    unsigned int key_set : 1;
    unsigned int iv_set : 1;
    uint8_t iv_size;
    uint8_t block_size;
    union
    {
        unsigned dummy; /* 允许更容易地初始化联合。*/
        mbedtls_cipher_context_t cipher;
    } ctx;
};

#define PSA_AEAD_OPERATION_INIT {0, 0, 0, 0, 0, {0}}
static inline struct psa_aead_operation_s psa_aead_operation_init( void )
{
    const struct psa_aead_operation_s v = PSA_AEAD_OPERATION_INIT;
    return( v );
}

#if defined(MBEDTLS_PSA_BUILTIN_ALG_HKDF)
typedef struct
{
    uint8_t *info;
    size_t info_length;
#if PSA_HASH_MAX_SIZE > 0xff
#error "PSA_HASH_MAX_SIZE does not fit in uint8_t"
#endif
    uint8_t offset_in_block;
    uint8_t block_number;
    unsigned int state : 2;
    unsigned int info_set : 1;
    uint8_t output_block[PSA_HASH_MAX_SIZE];
    uint8_t prk[PSA_HASH_MAX_SIZE];
    struct psa_mac_operation_s hmac;
} psa_hkdf_key_derivation_t;
#endif /* MBEDTLS_PSA_BUILTIN_ALG_HKDF */

#if defined(MBEDTLS_PSA_BUILTIN_ALG_TLS12_PRF) || \
    defined(MBEDTLS_PSA_BUILTIN_ALG_TLS12_PSK_TO_MS)
typedef enum
{
    PSA_TLS12_PRF_STATE_INIT,       /* 未提供输入*/
    PSA_TLS12_PRF_STATE_SEED_SET,   /* 种子已设定*/
    PSA_TLS12_PRF_STATE_KEY_SET,    /* 密钥已设置*/
    PSA_TLS12_PRF_STATE_LABEL_SET,  /* 标签已设置*/
    PSA_TLS12_PRF_STATE_OUTPUT      /* 输出已启动*/
} psa_tls12_prf_key_derivation_state_t;

typedef struct psa_tls12_prf_key_derivation_s
{
#if PSA_HASH_MAX_SIZE > 0xff
#error "PSA_HASH_MAX_SIZE does not fit in uint8_t"
#endif

    /* 指示用户尚未读取当前HMAC块中的字节数。*/
    uint8_t left_in_block;

    /* 块的从1开始的编号。*/
    uint8_t block_number;

    psa_tls12_prf_key_derivation_state_t state;

    uint8_t *secret;
    size_t secret_length;
    uint8_t *seed;
    size_t seed_length;
    uint8_t *label;
    size_t label_length;

    uint8_t Ai[PSA_HASH_MAX_SIZE];

    /* `HMAC_hash（prk，A（i）+种子）”，在RFC 5246第。5.*/
    uint8_t output_block[PSA_HASH_MAX_SIZE];
} psa_tls12_prf_key_derivation_t;
#endif /* MBEDTLS_PSA_BUILTIN_ALG_TLS12_PRF) || MBEDTLS_PSA_BUILTIN_ALG_TLS12_PSK_TO_MS */

struct psa_key_derivation_s
{
    psa_algorithm_t alg;
    unsigned int can_output_key : 1;
    size_t capacity;
    union
    {
        /* 即使没有支持的算法，也要使联合为非空。*/
        uint8_t dummy;
#if defined(MBEDTLS_PSA_BUILTIN_ALG_HKDF)
        psa_hkdf_key_derivation_t hkdf;
#endif
#if defined(MBEDTLS_PSA_BUILTIN_ALG_TLS12_PRF) || \
    defined(MBEDTLS_PSA_BUILTIN_ALG_TLS12_PSK_TO_MS)
        psa_tls12_prf_key_derivation_t tls12_prf;
#endif
    } ctx;
};

/* 这只会将并集中的第一个字节归零，其余字节未指定。*/
#define PSA_KEY_DERIVATION_OPERATION_INIT {0, 0, 0, {0}}
static inline struct psa_key_derivation_s psa_key_derivation_operation_init( void )
{
    const struct psa_key_derivation_s v = PSA_KEY_DERIVATION_OPERATION_INIT;
    return( v );
}

struct psa_key_policy_s
{
    psa_key_usage_t usage;
    psa_algorithm_t alg;
    psa_algorithm_t alg2;
};
typedef struct psa_key_policy_s psa_key_policy_t;

#define PSA_KEY_POLICY_INIT {0, 0, 0}
static inline struct psa_key_policy_s psa_key_policy_init( void )
{
    const struct psa_key_policy_s v = PSA_KEY_POLICY_INIT;
    return( v );
}

/* 内部用于键大小的类型。公共接口使用size_t，但在内部我们使用较小的类型。*/
typedef uint16_t psa_key_bits_t;
/* 用于表示位大小的类型的最大值。这用于标记无效的密钥大小。*/
#define PSA_KEY_BITS_TOO_LARGE ( (psa_key_bits_t) ( -1 ) )
/* 密钥的最大大小（以位为单位）。当前定义为可以表示的最大值，向下舍入为整数字节。这是一个uncast值，因此可以在预处理器条件中使用。*/
#define PSA_MAX_KEY_BITS 0xfff8

/** 可以存储在关键属性中的标志掩码。
 *
 * 此类型也在内部用于在插槽中存储标志。内部标志在库/psa_crypto_core.h中定义。如果在密钥创建期间和psa_get_key_attributes中正确处理了内部标志，则内部标志的值可能与外部标志的值相同。
 */
typedef uint16_t psa_key_attributes_flag_t;

#define MBEDTLS_PSA_KA_FLAG_HAS_SLOT_NUMBER     \
    ( (psa_key_attributes_flag_t) 0x0001 )

/* 仅在外部使用的关键属性标志掩码。仅用于图书馆内部检查。*/
#define MBEDTLS_PSA_KA_MASK_EXTERNAL_ONLY (      \
        MBEDTLS_PSA_KA_FLAG_HAS_SLOT_NUMBER |    \
        0 )

/* 内部和外部使用的关键属性标志掩码。目前没有。*/
#define MBEDTLS_PSA_KA_MASK_DUAL_USE (          \
        0 )

typedef struct
{
    psa_key_type_t type;
    psa_key_bits_t bits;
    psa_key_lifetime_t lifetime;
    mbedtls_svc_key_id_t id;
    psa_key_policy_t policy;
    psa_key_attributes_flag_t flags;
} psa_core_key_attributes_t;

#define PSA_CORE_KEY_ATTRIBUTES_INIT {PSA_KEY_TYPE_NONE, 0, PSA_KEY_LIFETIME_VOLATILE, MBEDTLS_SVC_KEY_ID_INIT, PSA_KEY_POLICY_INIT, 0}

struct psa_key_attributes_s
{
    psa_core_key_attributes_t core;
#if defined(MBEDTLS_PSA_CRYPTO_SE_C)
    psa_key_slot_number_t slot_number;
#endif /* MBEDTLS_PSA_CRYPTO_SE_C */
    void *domain_parameters;
    size_t domain_parameters_size;
};

#if defined(MBEDTLS_PSA_CRYPTO_SE_C)
#define PSA_KEY_ATTRIBUTES_INIT {PSA_CORE_KEY_ATTRIBUTES_INIT, 0, NULL, 0}
#else
#define PSA_KEY_ATTRIBUTES_INIT {PSA_CORE_KEY_ATTRIBUTES_INIT, NULL, 0}
#endif

static inline struct psa_key_attributes_s psa_key_attributes_init( void )
{
    const struct psa_key_attributes_s v = PSA_KEY_ATTRIBUTES_INIT;
    return( v );
}

static inline void psa_set_key_id( psa_key_attributes_t *attributes,
                                   mbedtls_svc_key_id_t key )
{
    psa_key_lifetime_t lifetime = attributes->core.lifetime;

    attributes->core.id = key;

    if( PSA_KEY_LIFETIME_IS_VOLATILE( lifetime ) )
    {
        attributes->core.lifetime =
            PSA_KEY_LIFETIME_FROM_PERSISTENCE_AND_LOCATION(
                PSA_KEY_LIFETIME_PERSISTENT,
                PSA_KEY_LIFETIME_GET_LOCATION( lifetime ) );
    }
}

static inline mbedtls_svc_key_id_t psa_get_key_id(
    const psa_key_attributes_t *attributes)
{
    return( attributes->core.id );
}

#ifdef MBEDTLS_PSA_CRYPTO_KEY_ID_ENCODES_OWNER
static inline void mbedtls_set_key_owner_id( psa_key_attributes_t *attributes,
                                             mbedtls_key_owner_id_t owner )
{
    attributes->core.id.owner = owner;
}
#endif

static inline void psa_set_key_lifetime(psa_key_attributes_t *attributes,
                                        psa_key_lifetime_t lifetime)
{
    attributes->core.lifetime = lifetime;
    if( PSA_KEY_LIFETIME_IS_VOLATILE( lifetime ) )
    {
#ifdef MBEDTLS_PSA_CRYPTO_KEY_ID_ENCODES_OWNER
        attributes->core.id.key_id = 0;
#else
        attributes->core.id = 0;
#endif
    }
}

static inline psa_key_lifetime_t psa_get_key_lifetime(
    const psa_key_attributes_t *attributes)
{
    return( attributes->core.lifetime );
}

static inline void psa_extend_key_usage_flags( psa_key_usage_t *usage_flags )
{
    if( *usage_flags & PSA_KEY_USAGE_SIGN_HASH )
        *usage_flags |= PSA_KEY_USAGE_SIGN_MESSAGE;

    if( *usage_flags & PSA_KEY_USAGE_VERIFY_HASH )
        *usage_flags |= PSA_KEY_USAGE_VERIFY_MESSAGE;
}

static inline void psa_set_key_usage_flags(psa_key_attributes_t *attributes,
                                           psa_key_usage_t usage_flags)
{
    psa_extend_key_usage_flags( &usage_flags );
    attributes->core.policy.usage = usage_flags;
}

static inline psa_key_usage_t psa_get_key_usage_flags(
    const psa_key_attributes_t *attributes)
{
    return( attributes->core.policy.usage );
}

static inline void psa_set_key_algorithm(psa_key_attributes_t *attributes,
                                         psa_algorithm_t alg)
{
    attributes->core.policy.alg = alg;
}

static inline psa_algorithm_t psa_get_key_algorithm(
    const psa_key_attributes_t *attributes)
{
    return( attributes->core.policy.alg );
}

/* 此函数在crypto_extra中声明。h、 它在这个头文件之后，但我们需要这里的函数，所以重复声明。*/
psa_status_t psa_set_key_domain_parameters(psa_key_attributes_t *attributes,
                                           psa_key_type_t type,
                                           const uint8_t *data,
                                           size_t data_length);

static inline void psa_set_key_type(psa_key_attributes_t *attributes,
                                    psa_key_type_t type)
{
    if( attributes->domain_parameters == NULL )
    {
        /* 常见情况：快速路径*/
        attributes->core.type = type;
    }
    else
    {
        /* 调用更大的函数来释放旧的域参数。忽略由于需要非默认域参数的类型而可能出现的任何错误，因为此函数无法报告错误。*/
        (void) psa_set_key_domain_parameters( attributes, type, NULL, 0 );
    }
}

static inline psa_key_type_t psa_get_key_type(
    const psa_key_attributes_t *attributes)
{
    return( attributes->core.type );
}

static inline void psa_set_key_bits(psa_key_attributes_t *attributes,
                                    size_t bits)
{
    if( bits > PSA_MAX_KEY_BITS )
        attributes->core.bits = PSA_KEY_BITS_TOO_LARGE;
    else
        attributes->core.bits = (psa_key_bits_t) bits;
}

static inline size_t psa_get_key_bits(
    const psa_key_attributes_t *attributes)
{
    return( attributes->core.bits );
}

#ifdef __cplusplus
}
#endif

#endif /* PSA_CRYPTO_STRUCT_H */

