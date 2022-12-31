/*
 *  SSL测试程序的通用代码
 *
 *  版权所有The Mbed TLS Contributors SPDX许可证标识符：Apache-2.0
 *
 *  根据Apache许可证2.0版（“许可证”）获得许可；除非符合许可证，否则不得使用此文件。您可以在以下地址获取许可证副本：
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 *  除非适用法律要求或书面同意，否则根据许可证分发的软件是按“原样”分发的，无任何明示或暗示的担保或条件。有关许可证下权限和限制的具体语言，请参阅许可证。
 */

#ifndef MBEDTLS_PROGRAMS_SSL_SSL_TEST_LIB_H
#define MBEDTLS_PROGRAMS_SSL_SSL_TEST_LIB_H

#if !defined(MBEDTLS_CONFIG_FILE)
#include "mbedtls/config.h"
#else
#include MBEDTLS_CONFIG_FILE
#endif

#if defined(MBEDTLS_PLATFORM_C)
#include "mbedtls/platform.h"
#else
#include <stdio.h>
#include <stdlib.h>
#define mbedtls_calloc     calloc
#define mbedtls_free       free
#define mbedtls_time       time
#define mbedtls_time_t     time_t
#define mbedtls_printf     printf
#define mbedtls_fprintf    fprintf
#define mbedtls_snprintf   snprintf
#define mbedtls_exit            exit
#define MBEDTLS_EXIT_SUCCESS    EXIT_SUCCESS
#define MBEDTLS_EXIT_FAILURE    EXIT_FAILURE
#endif

#undef HAVE_RNG
#if defined(MBEDTLS_PSA_CRYPTO_EXTERNAL_RNG) &&         \
    ( defined(MBEDTLS_USE_PSA_CRYPTO) ||                \
      defined(MBEDTLS_TEST_USE_PSA_CRYPTO_RNG) )
#define HAVE_RNG
#elif defined(MBEDTLS_ENTROPY_C) && defined(MBEDTLS_CTR_DRBG_C)
#define HAVE_RNG
#elif defined(MBEDTLS_ENTROPY_C) && defined(MBEDTLS_HMAC_DRBG_C) &&     \
    ( defined(MBEDTLS_SHA256_C) || defined(MBEDTLS_SHA512_C) )
#define HAVE_RNG
#endif

#if !defined(MBEDTLS_NET_C) ||                              \
    !defined(MBEDTLS_SSL_TLS_C) ||                          \
    defined(MBEDTLS_PSA_CRYPTO_KEY_ID_ENCODES_OWNER)
#define MBEDTLS_SSL_TEST_IMPOSSIBLE                             \
    "MBEDTLS_NET_C and/or "                                     \
    "MBEDTLS_SSL_TLS_C not defined, "                           \
    "and/or MBEDTLS_PSA_CRYPTO_KEY_ID_ENCODES_OWNER defined.\n"
#elif !defined(HAVE_RNG)
#define MBEDTLS_SSL_TEST_IMPOSSIBLE             \
    "No random generator is available.\n"
#else
#undef MBEDTLS_SSL_TEST_IMPOSSIBLE

#undef HAVE_RNG

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mbedtls/net_sockets.h"
#include "mbedtls/ssl.h"
#include "mbedtls/entropy.h"
#include "mbedtls/ctr_drbg.h"
#include "mbedtls/hmac_drbg.h"
#include "mbedtls/certs.h"
#include "mbedtls/x509.h"
#include "mbedtls/error.h"
#include "mbedtls/debug.h"
#include "mbedtls/timing.h"
#include "mbedtls/base64.h"

#if defined(MBEDTLS_USE_PSA_CRYPTO) || defined(MBEDTLS_TEST_USE_PSA_CRYPTO_RNG)
#include "psa/crypto.h"
#include "mbedtls/psa_util.h"
#endif

#if defined(MBEDTLS_MEMORY_BUFFER_ALLOC_C)
#include "mbedtls/memory_buffer_alloc.h"
#endif

#include <test/helpers.h>

#include "../test/query_config.h"

#if defined(MBEDTLS_SSL_EXPORT_KEYS)

typedef struct eap_tls_keys
{
    unsigned char master_secret[48];
    unsigned char randbytes[64];
    mbedtls_tls_prf_types tls_prf_type;
} eap_tls_keys;

#if defined( MBEDTLS_SSL_DTLS_SRTP )

/* 支持的SRTP模式最多需要：
 * -密钥16字节（AES-128）
 * -14字节SALT一个用于发送方，一个用于接收方上下文
 */
#define MBEDTLS_TLS_SRTP_MAX_KEY_MATERIAL_LENGTH    60

typedef struct dtls_srtp_keys
{
    unsigned char master_secret[48];
    unsigned char randbytes[64];
    mbedtls_tls_prf_types tls_prf_type;
} dtls_srtp_keys;

#endif /* MBEDTLS_SSL_DTLS_SRTP */

#endif /* MBEDTLS_SSL_EXPORT_KEYS */

typedef struct
{
    mbedtls_ssl_context *ssl;
    mbedtls_net_context *net;
} io_ctx_t;

void my_debug( void *ctx, int level,
               const char *file, int line,
               const char *str );

mbedtls_time_t dummy_constant_time( mbedtls_time_t* time );

#if defined(MBEDTLS_USE_PSA_CRYPTO)
/* 如果定义了MBEDTLS_TEST_USE_PSA_CRYPTO_RNG，SSL测试程序将使用MBEDTLS_PSA_get_random（）而不是熵+DRBG作为随机生成器。
 *
 * 约束条件如下：
 * -如果没有熵模块，PSA RNG是唯一的选择。
 * -如果没有至少一个DRBG模块，PSA RNG是唯一的选择。
 * -PSA RNG不支持显式播种，因此与测试程序使用的可再现模式不兼容。
 * -为了获得良好的总体测试覆盖率，应至少有一种配置，其中测试程序使用PSA RNG，而PSA RNG本身基于熵+DRBG，以及至少有一个配置，其中即使PSA RNG存在，测试程序也不使用。
 *
 * 满足约束条件的一个简单选择是在启用MBEDTLS_use_PSA_CRYPTO时使用PSA RNG。没有真正的技术原因，在测试程序中选择使用PSA RNG，以及在TLS代码需要加密时选择使用PSA加密必须结合在一起，但这恰好是一个很好的匹配。从应用程序的角度来看，这也是一个很好的匹配：对于TLS（加密和随机生成），PSA是首选的，或者不是。
 */
#define MBEDTLS_TEST_USE_PSA_CRYPTO_RNG
#endif

/** 随机数生成（RNG）的上下文。
 */
typedef struct
{
#if defined(MBEDTLS_TEST_USE_PSA_CRYPTO_RNG)
    unsigned char dummy;
#else /* MBEDTLS_TEST_USE_PSA_CRYPTO_RNG */
    mbedtls_entropy_context entropy;
#if defined(MBEDTLS_CTR_DRBG_C)
    mbedtls_ctr_drbg_context drbg;
#elif defined(MBEDTLS_HMAC_DRBG_C)
    mbedtls_hmac_drbg_context drbg;
#else
#error "No DRBG available"
#endif
#endif /* MBEDTLS_TEST_USE_PSA_CRYPTO_RNG */
} rng_context_t;

/** 初始化RNG。
 *
 * 此函数仅初始化RNG上下文使用的内存。在使用RNG之前，必须使用RNG_seed（）对其进行种子设定。
 */
void rng_init( rng_context_t *rng );

/* 为随机数生成器设置种子。
 *
 * \param rng要使用的rng上下文。它必须已使用rng_init（）初始化。\param reproductive如果为零，则根据熵为RNG种子。如果非零，则使用固定种子，这样程序每次调用时都会产生相同的随机数序列。\param pers以空结尾的字符串。此字符串的不同值会导致RNG为同一种子发出不同的输出。
 *
 * 成功时返回0，错误时返回负值。
 */
int rng_seed( rng_context_t *rng, int reproducible, const char *pers );

/** 取消RNG的初始化。释放任何嵌入资源。
 *
 * \param rng要取消初始化的rng上下文。它必须已使用rng_init（）初始化。
 */
void rng_free( rng_context_t *rng );

/** 生成随机数据。
 *
 * 此函数适合用作Mbed TLS库函数的\cf_rng参数。
 *
 * \param p_rng随机生成器上下文。这必须是指向#rng_context_t结构的指针。\param output要填充的缓冲区。\param output_len缓冲区的长度（字节）。
 *
 * \成功时返回\c 0。\返回错误时的Mbed TLS错误代码。
 */
int rng_get( void *p_rng, unsigned char *output, size_t output_len );

#if defined(MBEDTLS_USE_PSA_CRYPTO) && defined(MBEDTLS_PSA_CRYPTO_EXTERNAL_RNG)
/* PSA外部RNG的测试实施不安全。当启用MBEDTLS_PSA_CRYPTO_EXTERNAL_RNG时，在使用任何使用RNG的PSA加密函数之前，必须调用MBEDTLS_test_enable_insecure_EXTERNAL_RNG（）。*/
#include <test/fake_external_rng_for_test.h>
#endif

#if defined(MBEDTLS_X509_TRUSTED_CERTIFICATE_CALLBACK)
int ca_callback( void *data, mbedtls_x509_crt const *child,
                 mbedtls_x509_crt **candidates );
#endif /* MBEDTLS_X509_TRUSTED_CERTIFICATE_CALLBACK */

/*
 * 测试recv/send函数，确保每次尝试在成功之前至少返回一次WANT_READ/WANT_WRITE
 */
int delayed_recv( void *ctx, unsigned char *buf, size_t len );
int delayed_send( void *ctx, const unsigned char *buf, size_t len );

/*
 * 等待来自基础传输或计时器的事件（在事件驱动IO模式下使用）。
 */
int idle( mbedtls_net_context *fd,
#if defined(MBEDTLS_TIMING_C)
          mbedtls_timing_delay_context *timer,
#endif
          int idle_reason );

#if defined(MBEDTLS_TEST_HOOKS)
/**初始化编译时配置启用的任何测试挂钩，并使TLS测试程序有意义。*/
void test_hooks_init( void );

/** 检查是否有测试挂钩检测到问题。
 *
 * 如果检测到问题，调用程序可以继续运行，但最终应该以错误状态退出。
 *
 * \注意：当实现一个自行检测错误的测试钩子（而不是将错误留给内存清理器报告）时，请确保在检测到问题时或在执行此函数期间将消息打印为标准错误。此函数不指示检测到什么问题，因此打印消息是在调用程序的日志中提供反馈的唯一方法。
 *
 * \如果检测到问题，则返回非零。\c 0，如果未检测到问题。
 */
int test_hooks_failure_detected( void );

/** 释放为测试挂钩分配的所有资源。
 *
 * 在程序结束时调用它，这样资源泄漏分析器就不会抱怨了。
 */
void test_hooks_free( void );

#endif /* !MBEDTLS_TEST_HOOKS */

#endif /* MBEDTLS_SL_TEST_IMPOSSIBLE条件：否则*/
#endif /* MBEDTLS_PROGRAMS_SSL_SSL_TEST_LIB_H */

