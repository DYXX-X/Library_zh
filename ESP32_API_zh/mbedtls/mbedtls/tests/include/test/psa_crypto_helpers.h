/*
 * 使用PSA Crypto API的测试的帮助函数。
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

#ifndef PSA_CRYPTO_HELPERS_H
#define PSA_CRYPTO_HELPERS_H

#include "test/helpers.h"

#if defined(MBEDTLS_PSA_CRYPTO_C)

#include "test/psa_helpers.h"

#include <psa/crypto.h>

#if defined(MBEDTLS_USE_PSA_CRYPTO)
#include "mbedtls/psa_util.h"
#endif

#if defined(MBEDTLS_PSA_CRYPTO_STORAGE_C)

/* #TEST_USES_KEY_ID的内部函数。成功时返回1，失败时返回0。*/
int mbedtls_test_uses_key_id( mbedtls_svc_key_id_t key_id );

/** 销毁用#TEST_USES_KEY_ID记录的持久密钥。
 */
void mbedtls_test_psa_purge_key_storage( void );

/** 清除内存缓存中记录有#TEST_USES_KEY_ID的持久密钥。
 *
 * 如果此时持久键仍然存在，请在调用PSA_DONE（）之前调用此函数。
 */
void mbedtls_test_psa_purge_key_cache( void );

/** \定义TEST_USES_KEY_ID
 *
 * 在可能创建持久密钥之前，在测试函数中调用此宏。使用此机制的测试函数必须在其清理代码中调用mbedtls_Test_psa_purge_key_storage（）。
 *
 * 此宏记录当前测试用例中可能使用的持久密钥标识符。记录的关键标识符将在测试用例结束时清理，即使出现故障。
 *
 * 此宏对易失性键没有影响。因此，在根据测试数据创建易失性或持久性键的测试函数中调用此宏是安全的。
 *
 * 此宏当前对用于存储特定于实现的文件的特殊标识符没有影响。
 *
 * 在同一测试用例中，对同一密钥标识符多次调用此宏无效。
 *
 * 如果没有足够的内存来记录密钥id，此宏可能会使测试用例失败。
 *
 * \param key_id要记录的PSA密钥标识符。
 */
#define TEST_USES_KEY_ID( key_id )                      \
    TEST_ASSERT( mbedtls_test_uses_key_id( key_id ) )

#else /* MBEDTLS_PSA_CRYPTO_STORAGE_C */

#define TEST_USES_KEY_ID( key_id ) ( (void) ( key_id ) )
#define mbedtls_test_psa_purge_key_storage( ) ( (void) 0 )
#define mbedtls_test_psa_purge_key_cache( ) ( (void) 0 )

#endif /* MBEDTLS_PSA_CRYPTO_STORAGE_C */

#define PSA_INIT( ) PSA_ASSERT( psa_crypto_init( ) )

/** 检查PSA子系统中是否有未正确清理的东西。
 *
 * \如果没有泄漏，则返回NULL。\return一个字符串文本，解释哪些内容尚未清理（如果适用）。
 */
const char *mbedtls_test_helper_is_psa_leaking( void );

/** 检查是否没有使用PSA Crypto密钥槽。
 *
 * 如果有任何插槽正在使用，请将当前测试标记为失败并跳转到退出标签。这相当于`TEST_ASSERT（！mbedtls_TEST_helper_is_psa_leaking（））`，但信息更丰富。
 */
#define ASSERT_PSA_PRISTINE( )                                          \
    do                                                                  \
    {                                                                   \
        if( test_fail_if_psa_leaking( __LINE__, __FILE__ ) )            \
            goto exit;                                                  \
    }                                                                   \
    while( 0 )

/** 关闭PSA Crypto子系统并销毁持久密钥。预计会在没有插槽的情况下彻底关闭。
 *
 * 如果某些键槽仍在使用，则将测试用例记录为失败，但继续执行。此宏适用于（并且主要用于）测试函数的清理部分。
 *
 * \注意：在创建持久密钥之前，必须使用#TEST_USES_KEY_ID记录持久密钥。
 */
#define PSA_DONE( )                                                     \
    do                                                                  \
    {                                                                   \
        test_fail_if_psa_leaking( __LINE__, __FILE__ );                 \
        mbedtls_test_psa_purge_key_storage( );                          \
        mbedtls_psa_crypto_free( );                                     \
    }                                                                   \
    while( 0 )

/** 关闭PSA Crypto子系统，允许持久密钥继续存在。预计会在没有插槽的情况下彻底关闭。
 *
 * 如果某些密钥槽仍在使用，则将测试用例记录为失败，并跳转到“退出”标签。
 */
#define PSA_SESSION_DONE( )                                             \
    do                                                                  \
    {                                                                   \
        mbedtls_test_psa_purge_key_cache( );                            \
        ASSERT_PSA_PRISTINE( );                                         \
        mbedtls_psa_crypto_free( );                                     \
    }                                                                   \
    while( 0 )



#if defined(RECORD_PSA_STATUS_COVERAGE_LOG)
psa_status_t mbedtls_test_record_status( psa_status_t status,
                                         const char *func,
                                         const char *file, int line,
                                         const char *expr );

/** 返回值记录包装宏。
 *
 * 评估\p表达式。将记录其值的行写入日志文件#STATUS_log_file_NAME并返回该值。该行是以冒号分隔的字段列表：表达式的```值：字符串：__FILE__：__line_：表达式```
 *
 * 测试代码没有显式调用此宏，因为这将非常具有侵入性。相反，我们通过定义一堆包装宏来插入源代码，如```#define psa_crypto_init（）RECORD_STATUS（“psa_ccrypto_init”，psa_cCrypto_init）```这些宏定义必须存在于`instrument_RECORD_STATUS中。h`在构建测试套件时。
 *
 * \param string字符串，通常是函数名。\param expr要计算的表达式，通常是名称在\p字符串中的函数的调用。此表达式必须返回#psa_status_t类型的值。\return \p expr的值。
 */
#define RECORD_STATUS( string, expr )                                   \
    mbedtls_test_record_status( ( expr ), string, __FILE__, __LINE__, #expr )

#include "instrument_record_status.h"

#endif /* 已定义（RECORD_PSA_STATUS_COVERAGE_LOG）*/

/** 返回扩展密钥使用策略。
 *
 * 在密钥使用策略上执行密钥策略权限扩展总是涉及其他使用策略的权限（如PSA_key_usage_SIGN_HASH涉及PSA_key.usage_SIGNA_MESSGAE）。
 */
psa_key_usage_t mbedtls_test_update_key_usage_flags( psa_key_usage_t usage_flags );

/** 如果给定密钥是192位AES密钥并且AES实现至少部分由加速器或替代实现提供，则跳过测试用例。
 *
 *  当可能涉及AES操作的加密操作返回#PSA_ERROR_NOT_SUPPORTED错误代码时，在测试用例中调用此宏。如果操作涉及192位AES密钥，并且AES实现至少部分由加速器或替代实现提供。
 *
 *  通常存在不支持192位密钥的硬件AES实现。因此，PSA测试用例的目标是，当由替代AES实现执行的具有192位密钥的AES操作返回#PSA_ERROR_not_SUPPORTED错误代码时，不会失败。此宏的目的是促进这一点，并使测试用例代码更具可读性。
 *
 *  \param key_type密钥类型\param key_bits以位数表示的密钥长度。
 */
#if defined(MBEDTLS_AES_ALT) || \
    defined(MBEDTLS_AES_SETKEY_ENC_ALT) || \
    defined(MBEDTLS_PSA_ACCEL_KEY_TYPE_AES)
#define MBEDTLS_TEST_HAVE_ALT_AES 1
#else
#define MBEDTLS_TEST_HAVE_ALT_AES 0
#endif

#define MBEDTLS_TEST_PSA_SKIP_IF_ALT_AES_192( key_type, key_bits )        \
    do                                                                    \
    {                                                                     \
        if( ( MBEDTLS_TEST_HAVE_ALT_AES ) &&                              \
            ( ( key_type ) == PSA_KEY_TYPE_AES ) &&                       \
            ( key_bits == 192 ) )                                         \
        {                                                                 \
            mbedtls_test_skip( "AES-192 not supported", __LINE__, __FILE__ );     \
            goto exit;                                                    \
        }                                                                 \
    }                                                                     \
    while( 0 )

/** 如果随机数长度不同于12字节的GCM操作失败，并且由加速器或替代实现执行，则跳过测试用例。
 *
 *  当可能涉及GCM模式的AEAD加密操作返回#PSA_ERROR_NOT_SUPPORTED错误代码时，在测试用例中调用此宏。如果操作涉及GCM模式、长度不同于12字节的随机数以及GCM模式实现，宏调用将跳过测试用例，并且不会失败。
 *
 *  通常存在不支持不同于12字节的随机数长度的硬件GCM实现，因为支持非12字节随机数需要涉及GHASH函数的额外计算。因此，PSA测试用例旨在在GCM模式下的AEAD操作（随机数长度不同于12字节）由替代GCM实现执行时不失败，并返回#PSA_ERROR_not_SUPPORTED错误代码。此宏的目的是为了便于检查，并使测试用例代码更可读。
 *
 *  \param alg AEAD算法。\param nonce_length以字节数表示的nonce长度。
 */
#if defined(MBEDTLS_GCM_ALT) || \
    defined(MBEDTLS_PSA_ACCEL_ALG_GCM)
#define MBEDTLS_TEST_HAVE_ALT_GCM  1
#else
#define MBEDTLS_TEST_HAVE_ALT_GCM  0
#endif

#define MBEDTLS_TEST_PSA_SKIP_IF_ALT_GCM_NOT_12BYTES_NONCE( alg,           \
                                                            nonce_length ) \
    do                                                                     \
    {                                                                      \
        if( ( MBEDTLS_TEST_HAVE_ALT_GCM ) &&                               \
            ( PSA_ALG_AEAD_WITH_SHORTENED_TAG( ( alg ) , 0 ) ==            \
              PSA_ALG_AEAD_WITH_SHORTENED_TAG( PSA_ALG_GCM, 0 ) ) &&       \
            ( ( nonce_length ) != 12 ) )                                   \
        {                                                                  \
            mbedtls_test_skip( "GCM with non-12-byte IV is not supported", __LINE__, __FILE__ ); \
            goto exit;                                                     \
        }                                                                  \
    }                                                                      \
    while( 0 )

#endif /* MBEDTLS_PSA_CRYPTO_C */

/** \定义USE_PSA_INIT
 *
 * 如果启用了#MBEDTLS_USE_PSA_CRYPTO，则调用此宏初始化PSA子系统，否则不执行任何操作。如果初始化失败，请将测试用例标记为失败，然后跳到\p退出标签。
 */
/** \定义USE_PSA_DONE
 *
 * 如果调用了#USE_PSA_INIT，请在测试用例结束时调用此宏。这与#PSA_DONE类似，但如果禁用#MBEDTLS_USE_PSA_CRYPTO，则它不会执行任何操作。
 */
#if defined(MBEDTLS_USE_PSA_CRYPTO)
#define USE_PSA_INIT( ) PSA_INIT( )
#define USE_PSA_DONE( ) PSA_DONE( )
#else /* MBEDTLS_USE_PSA_CRYPTO */
/* 定义空宏，以便我们可以在前导码中使用它们，并根据MBEDTLS_use_PSA_CRYPTO有条件地使用PSA的每个测试函数的分解。*/
#define USE_PSA_INIT( ) ( (void) 0 )
#define USE_PSA_DONE( ) ( (void) 0 )
#endif /* !MBEDTLS_USE_PSA_CRYPTO */

#endif /* PSA_CRYPTO_HELPERS_H */

