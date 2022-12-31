/**
 * \文件ssl_scookie.h
 *
 * \简短的DTLS cookie回调实现
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
#ifndef MBEDTLS_SSL_COOKIE_H
#define MBEDTLS_SSL_COOKIE_H

#if !defined(MBEDTLS_CONFIG_FILE)
#include "mbedtls/config.h"
#else
#include MBEDTLS_CONFIG_FILE
#endif

#include "mbedtls/ssl.h"

#if defined(MBEDTLS_THREADING_C)
#include "mbedtls/threading.h"
#endif

/**
 * \name SECTION:模块设置
 *
 * 您可以为此模块设置的配置选项在本节中。在配置中更改它们。h或在编译器命令行上定义它们\{
 */
#ifndef MBEDTLS_SSL_COOKIE_TIMEOUT
#define MBEDTLS_SSL_COOKIE_TIMEOUT     60 /**＜DTLS cookie的默认过期延迟，如果是HAVE_TIME，则以秒为单位，或者以发出的cookie数量为单位*/
#endif

/* \}name SECTION:模块设置*/

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \默认cookie函数的简短上下文。
 */
typedef struct mbedtls_ssl_cookie_ctx
{
    mbedtls_md_context_t    hmac_ctx;   /*!< HMAC部分的上下文*/
#if !defined(MBEDTLS_HAVE_TIME)
    unsigned long   serial;     /*!< 到期序列号*/
#endif
    unsigned long   timeout;    /*!< 超时延迟，如果是HAVE_TIME，则以秒为单位，或以发出的票证数为单位*/

#if defined(MBEDTLS_THREADING_C)
    mbedtls_threading_mutex_t mutex;
#endif
} mbedtls_ssl_cookie_ctx;

/**
 * \brief初始化cookie上下文
 */
void mbedtls_ssl_cookie_init( mbedtls_ssl_cookie_ctx *ctx );

/**
 * \简要设置cookie上下文（生成密钥）
 */
int mbedtls_ssl_cookie_setup( mbedtls_ssl_cookie_ctx *ctx,
                      int (*f_rng)(void *, unsigned char *, size_t),
                      void *p_rng );

/**
 * \brief设置COOKIE的过期延迟（默认MBEDTLS_SL_COOKIE_TIMEOUT）
 *
 * \param ctx Cookie上下文\param delay延迟，如果是HAVE_TIME，则以秒为单位，或同时发出的Cookie数量。0禁用过期（不推荐）
 */
void mbedtls_ssl_cookie_set_timeout( mbedtls_ssl_cookie_ctx *ctx, unsigned long delay );

/**
 * \简短的免费cookie上下文
 */
void mbedtls_ssl_cookie_free( mbedtls_ssl_cookie_ctx *ctx );

/**
 * \brief生成cookie，请参见\c mbedtls_ssl_cookie_write_t
 */
mbedtls_ssl_cookie_write_t mbedtls_ssl_cookie_write;

/**
 * \简要验证cookie，请参见\c mbedtls_ssl_cookie_write_t
 */
mbedtls_ssl_cookie_check_t mbedtls_ssl_cookie_check;

#ifdef __cplusplus
}
#endif

#endif /* ssl_ cookie.h*/

