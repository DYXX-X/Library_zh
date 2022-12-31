/** \文件psa_crypto_random_inmpl.h
 *
 * \简短的PSA加密随机生成器实现抽象。
 *
 * 此处的定义需要与include/mbedtls/psa_util.h中的声明保持一致。此文件包含一些冗余声明，以增加编译器在一个文件更改而不更新另一个文件时检测到不一致的可能性，但并非所有潜在的不一致都可以强制执行，因此，请确保检查include/mbedtls/psautil中的公共声明和契约。h如果修改此文件。
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

#ifndef PSA_CRYPTO_RANDOM_IMPL_H
#define PSA_CRYPTO_RANDOM_IMPL_H

#include <mbedtls/psa_util.h>

#if defined(MBEDTLS_PSA_CRYPTO_EXTERNAL_RNG)

#include <string.h>
#include <mbedtls/entropy.h> // 仅适用于错误代码
#include <psa/crypto.h>

typedef mbedtls_psa_external_random_context_t mbedtls_psa_random_context_t;

/* psa_generate_random（）周围的平凡包装。*/
int mbedtls_psa_get_random( void *p_rng,
                            unsigned char *output,
                            size_t output_size );

/* PSA RNG API不需要任何外部维护状态。*/
#define MBEDTLS_PSA_RANDOM_STATE NULL

#else /* MBEDTLS_PSA_CRYPTO_EXTERNAL_RNG */

/* 根据配置和可用性选择DRBG*/
#if defined(MBEDTLS_PSA_HMAC_DRBG_MD_TYPE)

#include "mbedtls/hmac_drbg.h"

#elif defined(MBEDTLS_CTR_DRBG_C)

#include "mbedtls/ctr_drbg.h"

#elif defined(MBEDTLS_HMAC_DRBG_C)

#include "mbedtls/hmac_drbg.h"
#if defined(MBEDTLS_SHA512_C) && defined(MBEDTLS_SHA256_C)
#include <limits.h>
#if SIZE_MAX > 0xffffffff
/* 看起来像64位系统，所以更喜欢SHA-512。*/
#define MBEDTLS_PSA_HMAC_DRBG_MD_TYPE MBEDTLS_MD_SHA512
#else
/* 看起来像32位系统，所以更喜欢SHA-256。*/
#define MBEDTLS_PSA_HMAC_DRBG_MD_TYPE MBEDTLS_MD_SHA256
#endif
#elif defined(MBEDTLS_SHA512_C)
#define MBEDTLS_PSA_HMAC_DRBG_MD_TYPE MBEDTLS_MD_SHA512
#elif defined(MBEDTLS_SHA256_C)
#define MBEDTLS_PSA_HMAC_DRBG_MD_TYPE MBEDTLS_MD_SHA256
#else
#error "No hash algorithm available for HMAC_DBRG."
#endif

#else
#error "No DRBG module available for the psa_crypto module."
#endif

#include "mbedtls/entropy.h"

/** 初始化PSA DRBG。
 *
 * \param p_rng指向Mbed TLS DRBG状态的指针。
 */
static inline void mbedtls_psa_drbg_init( mbedtls_psa_drbg_context_t *p_rng )
{
#if defined(MBEDTLS_CTR_DRBG_C)
    mbedtls_ctr_drbg_init( p_rng );
#elif defined(MBEDTLS_HMAC_DRBG_C)
    mbedtls_hmac_drbg_init( p_rng );
#endif
}

/** 取消PSA DRBG的初始化。
 *
 * \param p_rng指向Mbed TLS DRBG状态的指针。
 */
static inline void mbedtls_psa_drbg_free( mbedtls_psa_drbg_context_t *p_rng )
{
#if defined(MBEDTLS_CTR_DRBG_C)
    mbedtls_ctr_drbg_free( p_rng );
#elif defined(MBEDTLS_HMAC_DRBG_C)
    mbedtls_hmac_drbg_free( p_rng );
#endif
}

/** PSA随机生成器上下文的类型。
 *
 * 随机生成器上下文由熵上下文和DRBG上下文组成。
 */
typedef struct
{
    void (* entropy_init )( mbedtls_entropy_context *ctx );
    void (* entropy_free )( mbedtls_entropy_context *ctx );
    mbedtls_entropy_context entropy;
    mbedtls_psa_drbg_context_t drbg;
} mbedtls_psa_random_context_t;

/* 在include/mbedtls/psa_util中定义。h，以便应用程序代码可以看到它。这里的声明是多余的，但作为一个安全网被包括在内，以便更可能注意到将来意外导致实现偏离接口的更改。*/
/* 不要在MSVC下包含声明，因为它不接受它（“错误C2370:'mbedtls_psa_get_random'：重新定义；不同的存储类”）。用Visual Studio 2013观察到。一个已知的错误显然是：https://stackoverflow.com/questions/8146541/duplicate-external-static-declarations-not-allowed-in-visual-studio
 */
#if !defined(_MSC_VER)
static mbedtls_f_rng_t *const mbedtls_psa_get_random;
#endif

/** mbedtls_psa_get_random（）预期返回的最大字节数。
 */
#if defined(MBEDTLS_CTR_DRBG_C)
#define MBEDTLS_PSA_RANDOM_MAX_REQUEST MBEDTLS_CTR_DRBG_MAX_REQUEST
#elif defined(MBEDTLS_HMAC_DRBG_C)
#define MBEDTLS_PSA_RANDOM_MAX_REQUEST MBEDTLS_HMAC_DRBG_MAX_REQUEST
#endif

/** 指向PSA DRBG状态的指针。
 *
 * 此变量只能通过宏#MBEDTLS_PSA_RANDOM_STATE使用。
 */
/* psa_crypto。c将该变量设置为指向全局PSA加密状态中的DRBG状态的指针。*/
/* 类型“mbedtls_psa_drbg_context_t”在include/mmbedtls/psa_util中定义。h，以便可以在那里声明“mbedtls_psa_random_state”，并对应用程序代码可见。*/
extern mbedtls_psa_drbg_context_t *const mbedtls_psa_random_state;

/** 指向PSA DRBG状态的指针。
 *
 * 此宏扩展为一个表达式，该表达式适合作为\c p_rng参数传递给mbedtls_psa_get_random（）。
 *
 * 此宏存在于启用psa_crypto模块的所有配置中。其扩展取决于配置。
 */
#define MBEDTLS_PSA_RANDOM_STATE mbedtls_psa_random_state

/** 接种PSA DRBG。
 *
 * \param entropy从中读取种子的熵上下文。\param custom个性化字符串。这可以是空的，在这种情况下，无论\p len的值如何，个性化字符串都是空的。\param len个性化字符串的长度。
 *
 * \成功时返回\c 0。\失败时返回Mbed TLS错误代码（\c MBEDTLS_error_xxx）。
 */
static inline int mbedtls_psa_drbg_seed(
    mbedtls_entropy_context *entropy,
    const unsigned char *custom, size_t len )
{
#if defined(MBEDTLS_CTR_DRBG_C)
    return( mbedtls_ctr_drbg_seed( MBEDTLS_PSA_RANDOM_STATE,
                                   mbedtls_entropy_func,
                                   entropy,
                                   custom, len ) );
#elif defined(MBEDTLS_HMAC_DRBG_C)
    const mbedtls_md_info_t *md_info =
        mbedtls_md_info_from_type( MBEDTLS_PSA_HMAC_DRBG_MD_TYPE );
    return( mbedtls_hmac_drbg_seed( MBEDTLS_PSA_RANDOM_STATE,
                                    md_info,
                                    mbedtls_entropy_func,
                                    entropy,
                                    custom, len ) );
#endif
}

#endif /* MBEDTLS_PSA_CRYPTO_EXTERNAL_RNG */

#endif /* PSA_CRYPTO_RANDOM_IMPL_H */

