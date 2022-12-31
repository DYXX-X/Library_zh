/**
 * \文件密码.h
 *
 * \这个文件包含一个抽象接口，用于库提供的密码原语。它为所有可用的密码操作提供了一个通用接口。
 *
 * \作者Adrian de Jong<dejong@fox-it.com>
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

#ifndef MBEDTLS_CIPHER_H
#define MBEDTLS_CIPHER_H

#if !defined(MBEDTLS_CONFIG_FILE)
#include "mbedtls/config.h"
#else
#include MBEDTLS_CONFIG_FILE
#endif

#include <stddef.h>
#include "mbedtls/platform_util.h"

#if defined(MBEDTLS_GCM_C) || defined(MBEDTLS_CCM_C) || defined(MBEDTLS_CHACHAPOLY_C)
#define MBEDTLS_CIPHER_MODE_AEAD
#endif

#if defined(MBEDTLS_CIPHER_MODE_CBC)
#define MBEDTLS_CIPHER_MODE_WITH_PADDING
#endif

#if defined(MBEDTLS_ARC4_C) || defined(MBEDTLS_CIPHER_NULL_CIPHER) || \
    defined(MBEDTLS_CHACHA20_C)
#define MBEDTLS_CIPHER_MODE_STREAM
#endif

#if ( defined(__ARMCC_VERSION) || defined(_MSC_VER) ) && \
    !defined(inline) && !defined(__cplusplus)
#define inline __inline
#endif

#define MBEDTLS_ERR_CIPHER_FEATURE_UNAVAILABLE  -0x6080  /**<所选功能不可用。*/
#define MBEDTLS_ERR_CIPHER_BAD_INPUT_DATA       -0x6100  /**<输入参数错误。*/
#define MBEDTLS_ERR_CIPHER_ALLOC_FAILED         -0x6180  /**<分配内存失败。*/
#define MBEDTLS_ERR_CIPHER_INVALID_PADDING      -0x6200  /**<输入数据包含无效填充并被拒绝。*/
#define MBEDTLS_ERR_CIPHER_FULL_BLOCK_EXPECTED  -0x6280  /**<解密块需要完整的块。*/
#define MBEDTLS_ERR_CIPHER_AUTH_FAILED          -0x6300  /**<身份验证失败（对于AEAD模式）。*/
#define MBEDTLS_ERR_CIPHER_INVALID_CONTEXT      -0x6380  /**<上下文无效。例如，因为它被释放了。*/

/* MBEDTLS_ERROR_CIPHER_HW_ACCEL_FAILED已弃用，不应使用。*/
#define MBEDTLS_ERR_CIPHER_HW_ACCEL_FAILED      -0x6400  /**<密码硬件加速器失败。*/

#define MBEDTLS_CIPHER_VARIABLE_IV_LEN     0x01    /**<密码接受可变长度的IV。*/
#define MBEDTLS_CIPHER_VARIABLE_KEY_LEN    0x02    /**<密码接受可变长度的密钥。*/

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \brief支持的密码类型。
 *
 * \警告RC4和DES被认为是弱密码，它们的使用构成了安全风险。Arm建议改用更强的密码。
 */
typedef enum {
    MBEDTLS_CIPHER_ID_NONE = 0,  /**<标记密码ID列表末尾的占位符。*/
    MBEDTLS_CIPHER_ID_NULL,      /**<身份密码，被视为流密码。*/
    MBEDTLS_CIPHER_ID_AES,       /**<AES密码。*/
    MBEDTLS_CIPHER_ID_DES,       /**<DES密码。*/
    MBEDTLS_CIPHER_ID_3DES,      /**<三重DES密码。*/
    MBEDTLS_CIPHER_ID_CAMELLIA,  /**<山茶花密码。*/
    MBEDTLS_CIPHER_ID_BLOWFISH,  /**<Blowfish密码。*/
    MBEDTLS_CIPHER_ID_ARC4,      /**<RC4密码。*/
    MBEDTLS_CIPHER_ID_ARIA,      /**<阿里亚密码。*/
    MBEDTLS_CIPHER_ID_CHACHA20,  /**<ChaCha20密码。*/
} mbedtls_cipher_id_t;

/**
 * \brief支持{密码类型，密码模式}对。
 *
 * \警告RC4和DES被认为是弱密码，它们的使用构成了安全风险。Arm建议改用更强的密码。
 */
typedef enum {
    MBEDTLS_CIPHER_NONE = 0,             /**<标记密码对列表末尾的占位符。*/
    MBEDTLS_CIPHER_NULL,                 /**<身份流密码。*/
    MBEDTLS_CIPHER_AES_128_ECB,          /**＜AES密码，128位ECB模式。*/
    MBEDTLS_CIPHER_AES_192_ECB,          /**<192位ECB模式的AES密码。*/
    MBEDTLS_CIPHER_AES_256_ECB,          /**＜AES密码，256位ECB模式。*/
    MBEDTLS_CIPHER_AES_128_CBC,          /**＜AES密码，128位CBC模式。*/
    MBEDTLS_CIPHER_AES_192_CBC,          /**<192位CBC模式的AES密码。*/
    MBEDTLS_CIPHER_AES_256_CBC,          /**＜AES密码，256位CBC模式。*/
    MBEDTLS_CIPHER_AES_128_CFB128,       /**＜AES密码，128位CFB128模式。*/
    MBEDTLS_CIPHER_AES_192_CFB128,       /**<192位CFB128模式的AES密码。*/
    MBEDTLS_CIPHER_AES_256_CFB128,       /**＜AES密码，256位CFB128模式。*/
    MBEDTLS_CIPHER_AES_128_CTR,          /**＜AES密码，128位CTR模式。*/
    MBEDTLS_CIPHER_AES_192_CTR,          /**＜AES密码，192位CTR模式。*/
    MBEDTLS_CIPHER_AES_256_CTR,          /**＜AES密码，256位CTR模式。*/
    MBEDTLS_CIPHER_AES_128_GCM,          /**＜AES密码，128位GCM模式。*/
    MBEDTLS_CIPHER_AES_192_GCM,          /**＜AES密码，192位GCM模式。*/
    MBEDTLS_CIPHER_AES_256_GCM,          /**＜AES密码，256位GCM模式。*/
    MBEDTLS_CIPHER_CAMELLIA_128_ECB,     /**＜128位ECB模式的Camellia密码。*/
    MBEDTLS_CIPHER_CAMELLIA_192_ECB,     /**＜Camellia密码，192位ECB模式。*/
    MBEDTLS_CIPHER_CAMELLIA_256_ECB,     /**＜Camellia密码，256位ECB模式。*/
    MBEDTLS_CIPHER_CAMELLIA_128_CBC,     /**＜Camellia密码，128位CBC模式。*/
    MBEDTLS_CIPHER_CAMELLIA_192_CBC,     /**<具有192位CBC模式的Camellia密码。*/
    MBEDTLS_CIPHER_CAMELLIA_256_CBC,     /**<具有256位CBC模式的Camellia密码。*/
    MBEDTLS_CIPHER_CAMELLIA_128_CFB128,  /**＜Camellia密码，128位CFB128模式。*/
    MBEDTLS_CIPHER_CAMELLIA_192_CFB128,  /**＜Camellia密码，192位CFB128模式。*/
    MBEDTLS_CIPHER_CAMELLIA_256_CFB128,  /**＜Camellia密码，256位CFB128模式。*/
    MBEDTLS_CIPHER_CAMELLIA_128_CTR,     /**<具有128位CTR模式的Camellia密码。*/
    MBEDTLS_CIPHER_CAMELLIA_192_CTR,     /**<具有192位CTR模式的Camellia密码。*/
    MBEDTLS_CIPHER_CAMELLIA_256_CTR,     /**<具有256位CTR模式的Camellia密码。*/
    MBEDTLS_CIPHER_CAMELLIA_128_GCM,     /**<具有128位GCM模式的Camellia密码。*/
    MBEDTLS_CIPHER_CAMELLIA_192_GCM,     /**<具有192位GCM模式的Camellia密码。*/
    MBEDTLS_CIPHER_CAMELLIA_256_GCM,     /**<具有256位GCM模式的Camellia密码。*/
    MBEDTLS_CIPHER_DES_ECB,              /**<带ECB模式的DES密码。*/
    MBEDTLS_CIPHER_DES_CBC,              /**<具有CBC模式的DES密码。*/
    MBEDTLS_CIPHER_DES_EDE_ECB,          /**<采用EDE ECB模式的DES密码。*/
    MBEDTLS_CIPHER_DES_EDE_CBC,          /**<DES密码与EDE CBC模式。*/
    MBEDTLS_CIPHER_DES_EDE3_ECB,         /**<DES密码，EDE3 ECB模式。*/
    MBEDTLS_CIPHER_DES_EDE3_CBC,         /**<DES密码，EDE3 CBC模式。*/
    MBEDTLS_CIPHER_BLOWFISH_ECB,         /**<带ECB模式的Blowfish密码。*/
    MBEDTLS_CIPHER_BLOWFISH_CBC,         /**<CBC模式下的Blowfish密码。*/
    MBEDTLS_CIPHER_BLOWFISH_CFB64,       /**<CFB64模式的Blowfish密码。*/
    MBEDTLS_CIPHER_BLOWFISH_CTR,         /**<带CTR模式的Blowfish密码。*/
    MBEDTLS_CIPHER_ARC4_128,             /**<RC4密码，128位模式。*/
    MBEDTLS_CIPHER_AES_128_CCM,          /**＜AES密码，128位CCM模式。*/
    MBEDTLS_CIPHER_AES_192_CCM,          /**<AES密码，192位CCM模式。*/
    MBEDTLS_CIPHER_AES_256_CCM,          /**<具有256位CCM模式的AES密码。*/
    MBEDTLS_CIPHER_CAMELLIA_128_CCM,     /**<具有128位CCM模式的Camellia密码。*/
    MBEDTLS_CIPHER_CAMELLIA_192_CCM,     /**<具有192位CCM模式的Camellia密码。*/
    MBEDTLS_CIPHER_CAMELLIA_256_CCM,     /**<具有256位CCM模式的Camellia密码。*/
    MBEDTLS_CIPHER_ARIA_128_ECB,         /**<带128位密钥和ECB模式的Aria密码。*/
    MBEDTLS_CIPHER_ARIA_192_ECB,         /**<带有192位密钥和ECB模式的Aria密码。*/
    MBEDTLS_CIPHER_ARIA_256_ECB,         /**<带有256位密钥和ECB模式的Aria密码。*/
    MBEDTLS_CIPHER_ARIA_128_CBC,         /**＜Aria密码，128位密钥和CBC模式。*/
    MBEDTLS_CIPHER_ARIA_192_CBC,         /**<带有192位密钥和CBC模式的Aria密码。*/
    MBEDTLS_CIPHER_ARIA_256_CBC,         /**<带有256位密钥和CBC模式的Aria密码。*/
    MBEDTLS_CIPHER_ARIA_128_CFB128,      /**<带128位密钥和CFB-128模式的Aria密码。*/
    MBEDTLS_CIPHER_ARIA_192_CFB128,      /**<带有192位密钥和CFB-128模式的Aria密码。*/
    MBEDTLS_CIPHER_ARIA_256_CFB128,      /**<带有256位密钥和CFB-128模式的Aria密码。*/
    MBEDTLS_CIPHER_ARIA_128_CTR,         /**<带128位密钥和CTR模式的Aria密码。*/
    MBEDTLS_CIPHER_ARIA_192_CTR,         /**<带有192位密钥和CTR模式的Aria密码。*/
    MBEDTLS_CIPHER_ARIA_256_CTR,         /**<带有256位密钥和CTR模式的Aria密码。*/
    MBEDTLS_CIPHER_ARIA_128_GCM,         /**＜Aria密码，128位密钥和GCM模式。*/
    MBEDTLS_CIPHER_ARIA_192_GCM,         /**<带有192位密钥和GCM模式的Aria密码。*/
    MBEDTLS_CIPHER_ARIA_256_GCM,         /**<带有256位密钥和GCM模式的Aria密码。*/
    MBEDTLS_CIPHER_ARIA_128_CCM,         /**<带128位密钥和CCM模式的Aria密码。*/
    MBEDTLS_CIPHER_ARIA_192_CCM,         /**<带有192位密钥和CCM模式的Aria密码。*/
    MBEDTLS_CIPHER_ARIA_256_CCM,         /**<带有256位密钥和CCM模式的Aria密码。*/
    MBEDTLS_CIPHER_AES_128_OFB,          /**OFB模式下的AES 128位密码。*/
    MBEDTLS_CIPHER_AES_192_OFB,          /**OFB模式下的AES 192位密码。*/
    MBEDTLS_CIPHER_AES_256_OFB,          /**OFB模式下的AES 256位密码。*/
    MBEDTLS_CIPHER_AES_128_XTS,          /**XTS块模式下的AES 128位密码。*/
    MBEDTLS_CIPHER_AES_256_XTS,          /**XTS块模式下的AES 256位密码。*/
    MBEDTLS_CIPHER_CHACHA20,             /**<ChaCha20流密码。*/
    MBEDTLS_CIPHER_CHACHA20_POLY1305,    /**<ChaCha20-Poly1305 AEAD密码。*/
    MBEDTLS_CIPHER_AES_128_KW,           /**<AES密码，128位NIST KW模式。*/
    MBEDTLS_CIPHER_AES_192_KW,           /**<AES密码，192位NIST KW模式。*/
    MBEDTLS_CIPHER_AES_256_KW,           /**<AES密码，采用256位NIST KW模式。*/
    MBEDTLS_CIPHER_AES_128_KWP,          /**＜AES密码，128位NIST KWP模式。*/
    MBEDTLS_CIPHER_AES_192_KWP,          /**<192位NIST KWP模式的AES密码。*/
    MBEDTLS_CIPHER_AES_256_KWP,          /**<AES密码，采用256位NIST KWP模式。*/
} mbedtls_cipher_type_t;

/**支持的密码模式。*/
typedef enum {
    MBEDTLS_MODE_NONE = 0,               /**<无。*/
    MBEDTLS_MODE_ECB,                    /**<ECB密码模式。*/
    MBEDTLS_MODE_CBC,                    /**<CBC密码模式。*/
    MBEDTLS_MODE_CFB,                    /**<CFB密码模式。*/
    MBEDTLS_MODE_OFB,                    /**<OFB密码模式。*/
    MBEDTLS_MODE_CTR,                    /**<CTR密码模式。*/
    MBEDTLS_MODE_GCM,                    /**<GCM密码模式。*/
    MBEDTLS_MODE_STREAM,                 /**<流密码模式。*/
    MBEDTLS_MODE_CCM,                    /**<CCM密码模式。*/
    MBEDTLS_MODE_XTS,                    /**<XTS密码模式。*/
    MBEDTLS_MODE_CHACHAPOLY,             /**<ChaCha Poly密码模式。*/
    MBEDTLS_MODE_KW,                     /**<SP800-38F KW模式*/
    MBEDTLS_MODE_KWP,                    /**<SP800-38F KWP模式*/
} mbedtls_cipher_mode_t;

/**支持的密码填充类型。*/
typedef enum {
    MBEDTLS_PADDING_PKCS7 = 0,     /**<PKCS7填充（默认）。*/
    MBEDTLS_PADDING_ONE_AND_ZEROS, /**<ISO/IEC 7816-4填充。*/
    MBEDTLS_PADDING_ZEROS_AND_LEN, /**<ANSI X.923填充。*/
    MBEDTLS_PADDING_ZEROS,         /**<零填充（不可逆）。*/
    MBEDTLS_PADDING_NONE,          /**<切勿垫（仅限整块）。*/
} mbedtls_cipher_padding_t;

/**操作类型。*/
typedef enum {
    MBEDTLS_OPERATION_NONE = -1,
    MBEDTLS_DECRYPT = 0,
    MBEDTLS_ENCRYPT,
} mbedtls_operation_t;

enum {
    /**未定义的密钥长度。*/
    MBEDTLS_KEY_LENGTH_NONE = 0,
    /**DES密钥的密钥长度，以位为单位（包括奇偶校验）。*/
    MBEDTLS_KEY_LENGTH_DES  = 64,
    /**双密钥EDE中DES的密钥长度（位），包括奇偶校验。*/
    MBEDTLS_KEY_LENGTH_DES_EDE = 128,
    /**三密钥EDE中DES的密钥长度（以位为单位），包括奇偶校验。*/
    MBEDTLS_KEY_LENGTH_DES_EDE3 = 192,
};

/**任何IV的最大长度（字节）。*/
/* 理想情况下，这应该从密码列表中自动导出。这应该与SSL_internal.h中定义的MBEDTLS_SL_MAX_IV_LENGTH保持同步。*/
#define MBEDTLS_MAX_IV_LENGTH      16

/**任何密码的最大块大小（字节）。*/
/* 理想情况下，这应该从密码列表中自动导出。这应该与SSL_internal.h中定义的MBEDTLS_SL_MAX_BLOCK_LENGTH保持同步。*/
#define MBEDTLS_MAX_BLOCK_LENGTH   16

/**最大密钥长度，以字节为单位。*/
/* 理想情况下，这应该从密码列表中自动导出。目前，只检查是否启用了使用64字节密钥的XTS，否则使用32字节作为最大密钥长度的上限。这应与SSL_internal中定义的MBEDTLS_SL_MAX_BLOCK_LENGTH保持同步。h、 然而，这故意忽略了XTS的情况，因为后者没有在SSL/TLS中使用。*/
#if defined(MBEDTLS_CIPHER_MODE_XTS)
#define MBEDTLS_MAX_KEY_LENGTH     64
#else
#define MBEDTLS_MAX_KEY_LENGTH     32
#endif /* MBEDTLS_CIPHER_MODE_XTS */

/**
 * 基本密码信息（不透明结构）。
 */
typedef struct mbedtls_cipher_base_t mbedtls_cipher_base_t;

/**
 * CMAC上下文（不透明结构）。
 */
typedef struct mbedtls_cmac_context_t mbedtls_cmac_context_t;

/**
 * 密码信息。允许以通用方式调用密码函数。
 */
typedef struct mbedtls_cipher_info_t
{
    /** 完整密码标识符。例如，MBEDTLS_CIPHER_AES_256_CBC。
     */
    mbedtls_cipher_type_t type;

    /**密码模式。例如，MBEDTLS_MODE_CBC。*/
    mbedtls_cipher_mode_t mode;

    /** 密码密钥长度，以位为单位。这是可变大小密码的默认长度。包括DES等密码的奇偶校验位。
     */
    unsigned int key_bitlen;

    /**密码的名称。*/
    const char * name;

    /** IV或nonce大小，以字节为单位。对于接受可变IV大小的密码，这是建议的大小。
     */
    unsigned int iv_size;

    /** 由MBEDTLS_CIPHER_VARIABLE_IV_LEN和MBEDTLS_CIPHER_VARIABLE_KEY_LEN组成的位标志，分别指示密码是否支持可变IV或可变密钥大小。
     */
    int flags;

    /**块大小，以字节为单位。*/
    unsigned int block_size;

    /**基本密码信息和函数的结构。*/
    const mbedtls_cipher_base_t *base;

} mbedtls_cipher_info_t;

/**
 * 通用密码上下文。
 */
typedef struct mbedtls_cipher_context_t
{
    /**有关关联密码的信息。*/
    const mbedtls_cipher_info_t *cipher_info;

    /**要使用的密钥长度。*/
    int key_bitlen;

    /** 已为其初始化上下文密钥的操作。
     */
    mbedtls_operation_t operation;

#if defined(MBEDTLS_CIPHER_MODE_WITH_PADDING)
    /** 要使用的填充函数（如果与特定密码模式相关）。
     */
    void (*add_padding)( unsigned char *output, size_t olen, size_t data_len );
    int (*get_padding)( unsigned char *input, size_t ilen, size_t *data_len );
#endif

    /**尚未处理的输入的缓冲区。*/
    unsigned char unprocessed_data[MBEDTLS_MAX_BLOCK_LENGTH];

    /**尚未处理的字节数。*/
    size_t unprocessed_len;

    /**CTR模式的当前IV或NONCE_COUNTER，XTS模式的数据单元（或扇区）编号。*/
    unsigned char iv[MBEDTLS_MAX_IV_LENGTH];

    /**IV大小（字节），用于具有可变长度IV的密码。*/
    size_t iv_size;

    /**特定于密码的上下文。*/
    void *cipher_ctx;

#if defined(MBEDTLS_CMAC_C)
    /**CMAC特定上下文。*/
    mbedtls_cmac_context_t *cmac_ctx;
#endif

#if defined(MBEDTLS_USE_PSA_CRYPTO)
    /** 指示加密操作是由Mbed TLS自己的加密库执行，还是由PSA crypto API的外部实现执行。如果密码上下文是通过mbedtls_cipher_setup（）建立的，则不设置此项，如果密码上下文通过mbedtls _cipher_setup.psa（）创建的，则设置此项。
     */
    unsigned char psa_enabled;
#endif /* MBEDTLS_USE_PSA_CRYPTO */

} mbedtls_cipher_context_t;

/**
 * \brief此函数检索通用密码模块支持的密码列表。
 *
 *        对于返回列表中的任何密码标识符，您都可以通过mbedtls_cipher_info_from_type（）获得相应的通用密码信息结构，然后可以使用该结构通过mbedtls _cipher_setup（）准备密码上下文。
 *
 * \return类型为cipher_type_t的静态分配的密码标识符数组。最后一项为零。
 */
const int *mbedtls_cipher_list( void );

/**
 * \brief此函数检索与给定密码名关联的密码信息结构。
 *
 * \param cipher_name要搜索的密码的名称。此值不能为空。
 *
 * \return与给定的\p cipher_name关联的密码信息结构。\如果找不到相关的密码信息，则返回\c NULL。
 */
const mbedtls_cipher_info_t *mbedtls_cipher_info_from_string( const char *cipher_name );

/**
 * \brief此函数检索与给定密码类型相关的密码信息结构。
 *
 * \param cipher_type要搜索的密码的类型。
 *
 * \return与给定的\p cipher_type关联的密码信息结构。\如果找不到相关的密码信息，则返回\c NULL。
 */
const mbedtls_cipher_info_t *mbedtls_cipher_info_from_type( const mbedtls_cipher_type_t cipher_type );

/**
 * \brief此函数检索与给定密码ID、密钥大小和模式相关的密码信息结构。
 *
 * \param cipher_id要搜索的密码的id。例如，#MBEDTLS_CIPHER_ID_AES。\param key_bitlen密钥的长度（以位为单位）。\param mode密码模式。例如，#MBEDTLS_MODE_CBC。
 *
 * \return与给定的\p cipher_id关联的密码信息结构。\如果找不到相关的密码信息，则返回\c NULL。
 */
const mbedtls_cipher_info_t *mbedtls_cipher_info_from_values( const mbedtls_cipher_id_t cipher_id,
                                              int key_bitlen,
                                              const mbedtls_cipher_mode_t mode );

/**
 * \brief此函数将密文初始化为NONE。
 *
 * \param ctx要初始化的上下文。此值不能为空。
 */
void mbedtls_cipher_init( mbedtls_cipher_context_t *ctx );

/**
 * \brief此函数释放并清除\p ctx的密码特定上下文。释放ctx本身仍然是调用者的责任。
 *
 * \param ctx要释放的上下文。如果该值为空，则函数无效，否则必须指向已初始化的上下文。
 */
void mbedtls_cipher_free( mbedtls_cipher_context_t *ctx );


/**
 * \brief此函数初始化用于给定密码原语的密码上下文。
 *
 * \param ctx要初始化的上下文。必须对其进行初始化。\param cipher_info要使用的密码。
 *
 * \成功时返回\c 0。\参数验证失败时返回#MBEDTLS_ERROR_CIPHER_BAD_INPUT_DATA。\如果密码特定上下文的分配失败，则返回#MBEDTLS_ERROR_CIPHER_ALLOC_FAILED。
 *
 * \internal当前，该函数还清除结构。在未来的版本中，调用者将需要首先在结构上调用mbedtls_cipher_init（）。
 */
int mbedtls_cipher_setup( mbedtls_cipher_context_t *ctx,
                          const mbedtls_cipher_info_t *cipher_info );

#if defined(MBEDTLS_USE_PSA_CRYPTO)
/**
 * \brief此函数初始化密码上下文，以便使用给定的密码原语进行基于PSA的使用。
 *
 * \注：有关PSA的信息，请参阅#MBEDTLS_USE_PSA_CRYPTO。
 *
 * \param ctx要初始化的上下文。不能为\c NULL。\param cipher_info要使用的密码。\param taglen对于AEAD密码，要使用的身份验证标记的字节长度。随后使用mbedtls_cipher_auth_encrypt（）或mbedtls_cipher_auth_decrypt（）必须提供相同的标记长度。对于非AEAD密码，值必须为\c 0。
 *
 * \成功时返回\c 0。\参数验证失败时返回#MBEDTLS_ERROR_CIPHER_BAD_INPUT_DATA。\如果密码特定上下文的分配失败，则返回#MBEDTLS_ERROR_CIPHER_ALLOC_FAILED。
 */
int mbedtls_cipher_setup_psa( mbedtls_cipher_context_t *ctx,
                              const mbedtls_cipher_info_t *cipher_info,
                              size_t taglen );
#endif /* MBEDTLS_USE_PSA_CRYPTO */

/**
 * \brief此函数返回给定密码的块大小。
 *
 * \param ctx密码的上下文。必须对其进行初始化。
 *
 * \return基础密码的块大小。\如果\p ctx尚未初始化，则返回\c 0。
 */
static inline unsigned int mbedtls_cipher_get_block_size(
    const mbedtls_cipher_context_t *ctx )
{
    MBEDTLS_INTERNAL_VALIDATE_RET( ctx != NULL, 0 );
    if( ctx->cipher_info == NULL )
        return 0;

    return ctx->cipher_info->block_size;
}

/**
 * \brief此函数返回密码的操作模式。例如，MBEDTLS_MODE_CBC。
 *
 * \param ctx密码的上下文。必须对其进行初始化。
 *
 * \return操作模式。\如果ctx尚未初始化，则返回#MBEDTLS_MODE_NONE。
 */
static inline mbedtls_cipher_mode_t mbedtls_cipher_get_cipher_mode(
    const mbedtls_cipher_context_t *ctx )
{
    MBEDTLS_INTERNAL_VALIDATE_RET( ctx != NULL, MBEDTLS_MODE_NONE );
    if( ctx->cipher_info == NULL )
        return MBEDTLS_MODE_NONE;

    return ctx->cipher_info->mode;
}

/**
 * \brief此函数返回密码的IV或nonce的大小（以字节为单位）。
 *
 * \param ctx密码的上下文。必须对其进行初始化。
 *
 * \return如果未设置IV，则返回建议的IV大小。\对于不使用IV或随机数的密码，返回\c 0。\return如果已设置IV，则返回实际大小。
 */
static inline int mbedtls_cipher_get_iv_size(
    const mbedtls_cipher_context_t *ctx )
{
    MBEDTLS_INTERNAL_VALIDATE_RET( ctx != NULL, 0 );
    if( ctx->cipher_info == NULL )
        return 0;

    if( ctx->iv_size != 0 )
        return (int) ctx->iv_size;

    return (int) ctx->cipher_info->iv_size;
}

/**
 * \brief此函数返回给定密码的类型。
 *
 * \param ctx密码的上下文。必须对其进行初始化。
 *
 * \return密码的类型。\如果ctx尚未初始化，则返回#MBEDTLS_CIPHER_NONE。
 */
static inline mbedtls_cipher_type_t mbedtls_cipher_get_type(
    const mbedtls_cipher_context_t *ctx )
{
    MBEDTLS_INTERNAL_VALIDATE_RET(
        ctx != NULL, MBEDTLS_CIPHER_NONE );
    if( ctx->cipher_info == NULL )
        return MBEDTLS_CIPHER_NONE;

    return ctx->cipher_info->type;
}

/**
 * \brief此函数以字符串形式返回给定密码的名称。
 *
 * \param ctx密码的上下文。必须对其进行初始化。
 *
 * \return密码的名称。\如果\p ctx尚未初始化，则返回NULL。
 */
static inline const char *mbedtls_cipher_get_name(
    const mbedtls_cipher_context_t *ctx )
{
    MBEDTLS_INTERNAL_VALIDATE_RET( ctx != NULL, 0 );
    if( ctx->cipher_info == NULL )
        return 0;

    return ctx->cipher_info->name;
}

/**
 * \brief此函数返回密码的密钥长度。
 *
 * \param ctx密码的上下文。必须对其进行初始化。
 *
 * \return密码的密钥长度（以位为单位）。\如果ctx\p尚未初始化，则返回#MBEDTLS_KEY_LENGTH_NONE。
 */
static inline int mbedtls_cipher_get_key_bitlen(
    const mbedtls_cipher_context_t *ctx )
{
    MBEDTLS_INTERNAL_VALIDATE_RET(
        ctx != NULL, MBEDTLS_KEY_LENGTH_NONE );
    if( ctx->cipher_info == NULL )
        return MBEDTLS_KEY_LENGTH_NONE;

    return (int) ctx->cipher_info->key_bitlen;
}

/**
 * \brief此函数返回给定密码的操作。
 *
 * \param ctx密码的上下文。必须对其进行初始化。
 *
 * \return操作类型：#MBEDTLS_ENCRYPT或#MBEDTLS_DESCRYPT。\如果ctx尚未初始化，则返回#MBEDTLS_OPERATION_NONE。
 */
static inline mbedtls_operation_t mbedtls_cipher_get_operation(
    const mbedtls_cipher_context_t *ctx )
{
    MBEDTLS_INTERNAL_VALIDATE_RET(
        ctx != NULL, MBEDTLS_OPERATION_NONE );
    if( ctx->cipher_info == NULL )
        return MBEDTLS_OPERATION_NONE;

    return ctx->operation;
}

/**
 * \brief此函数设置用于给定上下文的键。
 *
 * \param ctx通用密码上下文。这必须初始化并绑定到密码信息结构。\param key要使用的密钥。这必须是至少有\p key_bitlen位的可读缓冲区。\param key_bitlen要使用的密钥长度，以位为单位。\param operation密钥将用于的操作：#MBEDTLS_ENCRYPT或#MBEDRLS_DECRYPT。
 *
 * \成功时返回\c 0。\参数验证失败时返回#MBEDTLS_ERROR_CIPHER_BAD_INPUT_DATA。\return失败时的密码特定错误代码。
 */
int mbedtls_cipher_setkey( mbedtls_cipher_context_t *ctx,
                           const unsigned char *key,
                           int key_bitlen,
                           const mbedtls_operation_t operation );

#if defined(MBEDTLS_CIPHER_MODE_WITH_PADDING)
/**
 * \brief此函数为使用填充的密码模式设置填充模式。
 *
 *                      默认的传递模式是PKCS7填充。
 *
 * \param ctx通用密码上下文。这必须初始化并绑定到密码信息结构。\param mode填充模式。
 *
 * \成功时返回\c 0。\如果不支持所选填充模式，则返回#MBEDTLS_ERROR_CIPHER_FEATURE_NAVAILABLE。\如果密码模式不支持填充，则返回#MBEDTLS_ERROR_CIPHER_BAD_INPUT_DATA。
 */
int mbedtls_cipher_set_padding_mode( mbedtls_cipher_context_t *ctx,
                                     mbedtls_cipher_padding_t mode );
#endif /* MBEDTLS_CIPHER_MODE_WITH_PADDING */

/**
 * \brief此函数设置初始化向量（IV）或随机数。
 *
 * \注意：有些密码不使用IV或nonce。对于这些密码，此函数无效。
 *
 * \param ctx通用密码上下文。这必须初始化并绑定到密码信息结构。\param iv要使用的iv，或CTR模式密码的NONCE_COUNTER。这必须是至少为\p iv_len字节的可读缓冲区。\param iv_len具有可变大小iv的密码的iv长度。此参数被具有固定大小iv的加密丢弃。
 *
 * \成功时返回\c 0。\参数验证失败时返回#MBEDTLS_ERROR_CIPHER_BAD_INPUT_DATA。
 */
int mbedtls_cipher_set_iv( mbedtls_cipher_context_t *ctx,
                           const unsigned char *iv,
                           size_t iv_len );

/**
 * \brief此函数重置密码状态。
 *
 * \param ctx通用密码上下文。必须对其进行初始化。
 *
 * \成功时返回\c 0。\参数验证失败时返回#MBEDTLS_ERROR_CIPHER_BAD_INPUT_DATA。
 */
int mbedtls_cipher_reset( mbedtls_cipher_context_t *ctx );

#if defined(MBEDTLS_GCM_C) || defined(MBEDTLS_CHACHAPOLY_C)
/**
 * \brief此函数为AEAD密码添加附加数据。当前支持GCM和ChaCha20+Poly1305。这必须在mbedtls_cipher_reset（）之后调用一次。
 *
 * \param ctx通用密码上下文。必须对其进行初始化。\param ad要使用的其他数据。这必须是至少\pad_len字节的可读缓冲区。\param ad_len \p ad的长度（以字节为单位）。
 *
 * \成功时返回\c 0。\返回失败时的特定错误代码。
 */
int mbedtls_cipher_update_ad( mbedtls_cipher_context_t *ctx,
                      const unsigned char *ad, size_t ad_len );
#endif /* MBEDTLS_GCM_C || MBEDTLS_CHACHAPOLY_C */

/**
 * \brief通用密码更新功能。它使用给定的密码上下文进行加密或解密。将尽可能多的块大小的数据块写入输出。任何无法立即写入的数据都会添加到下一个块中，或者在调用mbedtls_cipher_finish（）时刷新。异常：对于MBEDTLS_MODE_ECB，需要一个块大小。例如，AES为16字节。
 *
 * \注意：如果在GCM模式下使用基础密码，则除mbedtls_cipher_finish（）之前的最后一个调用外，对该函数的所有调用都必须具有密码块大小的倍数。
 *
 * \param ctx通用密码上下文。这必须初始化并绑定到密钥。\param input保存输入数据的缓冲区。这必须是一个至少为\pilen字节的可读缓冲区。\param ilen输入数据的长度。\param output输出数据的缓冲区。这必须至少能够容纳“ilen+block_size”。此缓冲区不能与\p输入区相同。\param olen要用实际写入的字节数更新的输出数据的长度。此值不能为空。
 *
 * \成功时返回\c 0。\参数验证失败时返回#MBEDTLS_ERROR_CIPHER_BAD_INPUT_DATA。\return#MBEDTLS_ERROR_CIPHER_FEATURE_NAVAILABLE（在密码不受支持的模式下）。\return失败时的密码特定错误代码。
 */
int mbedtls_cipher_update( mbedtls_cipher_context_t *ctx,
                           const unsigned char *input,
                           size_t ilen, unsigned char *output,
                           size_t *olen );

/**
 * \brief通用密码终结函数。如果数据仍然需要从不完整的块中刷新，则将其中包含的数据填充到最后一个块的大小，并写入\p输出缓冲区。
 *
 * \param ctx通用密码上下文。这必须初始化并绑定到密钥。\param output要将数据写入的缓冲区。该缓冲区必须至少为\p block_size Bytes。\param olen写入输出缓冲区的数据长度。这可能不是空的。
 *
 * \成功时返回\c 0。\参数验证失败时返回#MBEDTLS_ERROR_CIPHER_BAD_INPUT_DATA。\在解密时返回#MBEDTLS_ERROR_CIPHER_FULL_BLOCK_EXPECTED，需要完整的块，但没有收到完整的块。\解密时在无效填充上返回#MBEDTLS_ERROR_CIPHER_INVALID_PADDING。\return失败时的密码特定错误代码。
 */
int mbedtls_cipher_finish( mbedtls_cipher_context_t *ctx,
                   unsigned char *output, size_t *olen );

#if defined(MBEDTLS_GCM_C) || defined(MBEDTLS_CHACHAPOLY_C)
/**
 * \brief此函数为AEAD密码编写标记。当前支持GCM和ChaCha20+Poly1305。这必须在mbedtls_cipher_finish（）之后调用。
 *
 * \param ctx通用密码上下文。它必须被初始化，绑定到密钥，并且刚刚通过mbedtls_cipher_finish（）完成了加密操作，应该为其写入标记。\param tag将标记写入的缓冲区。此缓冲区必须至少为\p tag_len Bytes。\param tag_len要写入的标记的长度。
 *
 * \成功时返回\c 0。\返回失败时的特定错误代码。
 */
int mbedtls_cipher_write_tag( mbedtls_cipher_context_t *ctx,
                      unsigned char *tag, size_t tag_len );

/**
 * \brief此函数检查标签中的AEAD密码。当前支持GCM和ChaCha20+Poly1305。这必须在mbedtls_cipher_finish（）之后调用。
 *
 * \param ctx通用密码上下文。必须对其进行初始化。\param tag保存标记的缓冲区。这必须是至少有\p tag_len字节的可读缓冲区。\param tag_len要检查的标记的长度。
 *
 * \成功时返回\c 0。\返回失败时的特定错误代码。
 */
int mbedtls_cipher_check_tag( mbedtls_cipher_context_t *ctx,
                      const unsigned char *tag, size_t tag_len );
#endif /* MBEDTLS_GCM_C || MBEDTLS_CHACHAPOLY_C */

/**
 * \brief通用的一体化加密/解密功能，适用于除AEAD构造之外的所有密码。
 *
 * \param ctx通用密码上下文。必须对其进行初始化。\param iv要使用的iv，或CTR模式密码的NONCE_COUNTER。这必须是至少为\p iv_len字节的可读缓冲区。\param iv_len具有可变大小iv的密码的iv长度。此参数被具有固定大小iv的加密丢弃。\param input保存输入数据的缓冲区。这必须是一个至少为\pilen字节的可读缓冲区。\param ilen输入数据的长度（以字节为单位）。\param output输出数据的缓冲区。这必须至少能够容纳“ilen+block_size”。此缓冲区不能与\p输入区相同。\param olen要用实际写入的字节数更新的输出数据的长度。此值不能为空。
 *
 * \注意：有些密码不使用IV或nonce。对于这些密码，请使用\p iv=NULL和\p iv_len=0。
 *
 * \成功时返回\c 0。\参数验证失败时返回#MBEDTLS_ERROR_CIPHER_BAD_INPUT_DATA。\在解密时返回#MBEDTLS_ERROR_CIPHER_FULL_BLOCK_EXPECTED，需要完整的块，但没有收到完整的块。\解密时在无效填充上返回#MBEDTLS_ERROR_CIPHER_INVALID_PADDING。\return失败时的密码特定错误代码。
 */
int mbedtls_cipher_crypt( mbedtls_cipher_context_t *ctx,
                  const unsigned char *iv, size_t iv_len,
                  const unsigned char *input, size_t ilen,
                  unsigned char *output, size_t *olen );

#if defined(MBEDTLS_CIPHER_MODE_AEAD)
#if ! defined(MBEDTLS_DEPRECATED_REMOVED)
#if defined(MBEDTLS_DEPRECATED_WARNING)
#define MBEDTLS_DEPRECATED    __attribute__((deprecated))
#else
#define MBEDTLS_DEPRECATED
#endif /* MBEDTLS_DEPRECATED_WARNING */
/**
 * \brief通用认证加密（AEAD）功能。
 *
 * \已弃用被mbedtls_cipher_auth_encrypt_ext（）取代。
 *
 * \注意：此功能仅支持AEAD算法，不支持NIST_KW等密钥包装算法；为此，请参阅mbedtls_cipher_auth_encrypt_ext（）。
 *
 * \param ctx通用密码上下文。必须将其初始化并绑定到与AEAD算法关联的密钥。\param iv要使用的随机数。这必须是一个至少为\p iv_len Bytes的可读缓冲区，并且不能为\c NULL。\param iv_len随机数的长度。这必须满足所使用的AEAD密码所施加的约束。\param ad要验证的附加数据。这必须是一个至少为\p ad_len Bytes的可读缓冲区，并且可以是\c NULL。\p ad_len是\c 0。\p ad _len的长度\p ad \p input保存输入数据的缓冲区。这必须是一个至少为\p ilen Bytes的可读缓冲区，如果\pilen为\c 0，则可能为\c NULL。\param ilen输入数据的长度。\param output输出数据的缓冲区。这必须是一个至少为\pilen Bytes的可写缓冲区，并且不能为空。\param olen这将填充写入输出缓冲区的实际字节数。这必须指向类型为\c size_t的可写对象。\param tag身份验证标记的缓冲区。这必须是至少\p tag_len Bytes的可写缓冲区。关于PSA背景下的限制，请参见以下注释。\param tag_len身份验证标签的所需长度。这必须与所使用的AEAD密码所施加的约束相匹配，尤其不能为\c 0。
 *
 * \注意：如果上下文基于PSA（即，它是用mbedtls_cipher_setup_PSA（）设置的），则需要\c标记==output+ilen。也就是说，标签必须按照RFC 5116的建议附加到密文中。
 *
 * \成功时返回\c 0。\参数验证失败时返回#MBEDTLS_ERROR_CIPHER_BAD_INPUT_DATA。\return失败时的密码特定错误代码。
 */
int mbedtls_cipher_auth_encrypt( mbedtls_cipher_context_t *ctx,
                         const unsigned char *iv, size_t iv_len,
                         const unsigned char *ad, size_t ad_len,
                         const unsigned char *input, size_t ilen,
                         unsigned char *output, size_t *olen,
                         unsigned char *tag, size_t tag_len )
                         MBEDTLS_DEPRECATED;

/**
 * \brief通用认证解密（AEAD）功能。
 *
 * \已弃用被mbedtls_cipher_auth_decrypt_ext（）取代。
 *
 * \注意：此功能仅支持AEAD算法，不支持NIST_KW等密钥包装算法；为此，请参阅mbedtls_cipher_auth_decrypt_ext（）。
 *
 * \注意：如果数据不真实，则输出缓冲区将被清零，以防止使用不真实的明文，从而使该接口更安全。
 *
 * \param ctx通用密码上下文。必须将其初始化并绑定到与AEAD算法关联的密钥。\param iv要使用的随机数。这必须是一个至少为\p iv_len Bytes的可读缓冲区，并且不能为\c NULL。\param iv_len随机数的长度。这必须满足所使用的AEAD密码所施加的约束。\param ad要验证的附加数据。这必须是一个至少为\p ad_len Bytes的可读缓冲区，并且可以是\c NULL。\p ad_len是\c 0。\p ad _len的长度\p ad \p input保存输入数据的缓冲区。这必须是一个至少为\p ilen Bytes的可读缓冲区，如果\pilen为\c 0，则可能为\c NULL。\param ilen输入数据的长度。\param output输出数据的缓冲区。这必须是一个至少为\pilen Bytes的可写缓冲区，并且不能为空。\param olen这将填充写入输出缓冲区的实际字节数。这必须指向类型为\c size_t的可写对象。\param tag身份验证标记的缓冲区。这必须是至少有\p tag_len字节的可读缓冲区。关于PSA背景下的限制，请参见以下注释。\param tag_len身份验证标记的长度。这必须与所使用的AEAD密码所施加的约束相匹配，尤其不能为\c 0。
 *
 * \注意：如果上下文基于PSA（即，它是用mbedtls_cipher_setup_PSA（）设置的），则需要\c tag==input+len。也就是说，标签必须按照RFC 5116的建议附加到密文中。
 *
 * \成功时返回\c 0。\参数验证失败时返回#MBEDTLS_ERROR_CIPHER_BAD_INPUT_DATA。\如果数据不可信，则返回#MBEDTLS_ERROR_CIPHER_AUTH_FAILED。\return失败时的密码特定错误代码。
 */
int mbedtls_cipher_auth_decrypt( mbedtls_cipher_context_t *ctx,
                         const unsigned char *iv, size_t iv_len,
                         const unsigned char *ad, size_t ad_len,
                         const unsigned char *input, size_t ilen,
                         unsigned char *output, size_t *olen,
                         const unsigned char *tag, size_t tag_len )
                         MBEDTLS_DEPRECATED;
#undef MBEDTLS_DEPRECATED
#endif /* MBEDTLS_DEPRECATED_REMOVED */
#endif /* MBEDTLS_CIPHER_MODE_AEAD */

#if defined(MBEDTLS_CIPHER_MODE_AEAD) || defined(MBEDTLS_NIST_KW_C)
/**
 * \brief认证加密（AEAD/NIT_KW）功能。
 *
 * \注意：对于AEAD模式，根据RFC 5116的建议，标记将附加到密文中。（NIST_KW没有单独的标记。）
 *
 * \param ctx通用密码上下文。必须使用AEAD算法或NIST_KW将其初始化并绑定到密钥。\param iv要使用的随机数。这必须是一个至少为\p iv_len Bytes的可读缓冲区，如果\p iv_len为\c 0，则该缓冲区可能为\c NULL。\pram iv_len随机数的长度。对于AEAD密码，这必须满足所用密码所施加的约束。对于NIST_KW，此值必须为\c 0。\param ad要验证的其他数据。这必须是一个至少为\p ad_len Bytes的可读缓冲区，并且可以是\c NULL。\p ad_len是\c 0。\p ad的长度。对于NIST_KW，这必须是\c 0.\p input保存输入数据的缓冲区。这必须是一个至少为\p ilen Bytes的可读缓冲区，如果\pilen为\c 0，则可能为\c NULL。\param ilen输入数据的长度。\param output输出数据的缓冲区。这必须是一个至少为\p output_len Bytes的可写缓冲区，并且不能为\c NULL。\param output_len输出缓冲区的长度（字节）。对于AEAD密码，它必须至少为\pilen+\ptag_len。对于NIST_KW，这必须至少为8位数（如果使用KWP，则四舍五入为8的倍数）；\p ilen+15始终是一个安全值。\param olen这将填充写入输出缓冲区的实际字节数。这必须指向类型为\c size_t的可写对象。\param tag_len身份验证标签的所需长度。对于AEAD密码，这必须与所用密码所施加的约束相匹配，尤其不能为\c 0。对于NIST_KW，这必须为\c。
 *
 * \成功时返回\c 0。\参数验证失败时返回#MBEDTLS_ERROR_CIPHER_BAD_INPUT_DATA。\return失败时的密码特定错误代码。
 */
int mbedtls_cipher_auth_encrypt_ext( mbedtls_cipher_context_t *ctx,
                         const unsigned char *iv, size_t iv_len,
                         const unsigned char *ad, size_t ad_len,
                         const unsigned char *input, size_t ilen,
                         unsigned char *output, size_t output_len,
                         size_t *olen, size_t tag_len );

/**
 * \brief认证加密（AEAD/NIT_KW）功能。
 *
 * \注意：如果数据不真实，则输出缓冲区将被清零，以防止使用不真实的明文，从而使该接口更安全。
 *
 * \注意：对于AEAD模式，必须按照RFC 5116的建议将标记附加到密文中。（NIST_KW没有单独的标记。）
 *
 * \param ctx通用密码上下文。必须使用AEAD算法或NIST_KW将其初始化并绑定到密钥。\param iv要使用的随机数。这必须是一个至少为\p iv_len Bytes的可读缓冲区，如果\p iv_len为\c 0，则该缓冲区可能为\c NULL。\pram iv_len随机数的长度。对于AEAD密码，这必须满足所用密码所施加的约束。对于NIST_KW，此值必须为\c 0。\param ad要验证的其他数据。这必须是一个至少为\p ad_len Bytes的可读缓冲区，并且可以是\c NULL。\p ad_len是\c 0。\p ad的长度。对于NIST_KW，这必须是\c 0.\p input保存输入数据的缓冲区。这必须是一个至少为\p ilen Bytes的可读缓冲区，如果\pilen为\c 0，则可能为\c NULL。\param ilen输入数据的长度。对于AEAD密码，它必须至少为\p tag_len。对于NIST_KW，该值必须至少为\c 8。\param output输出数据的缓冲区。这必须是一个至少为\p output_len Bytes的可写缓冲区，如果\p outut_len为\c 0，则可能为\c NULL。\param output-len输出缓冲区的长度（以字节为单位）。对于AEAD密码，它必须至少为\pilen-\ptag_len。对于NIST_KW，它必须至少为\pilen-8。\param olen这将用写入输出缓冲区的实际字节数填充。这必须指向类型为\c size_t的可写对象。\param tag_len身份验证标记的实际长度。对于AEAD密码，这必须与所用密码所施加的约束相匹配，尤其不能为\c 0。对于NIST_KW，这必须为\c。
 *
 * \成功时返回\c 0。\参数验证失败时返回#MBEDTLS_ERROR_CIPHER_BAD_INPUT_DATA。\如果数据不可信，则返回#MBEDTLS_ERROR_CIPHER_AUTH_FAILED。\return失败时的密码特定错误代码。
 */
int mbedtls_cipher_auth_decrypt_ext( mbedtls_cipher_context_t *ctx,
                         const unsigned char *iv, size_t iv_len,
                         const unsigned char *ad, size_t ad_len,
                         const unsigned char *input, size_t ilen,
                         unsigned char *output, size_t output_len,
                         size_t *olen, size_t tag_len );
#endif /* MBEDTLS_CIPHER_MODE_AEAD || MBEDTLS_NIST_KW_C */
#ifdef __cplusplus
}
#endif

#endif /* MBEDTLS_CIPHER_H */

