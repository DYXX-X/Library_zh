/**
 * \文件ssl_cache.h
 *
 * \简短的SSL会话缓存实现
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
#ifndef MBEDTLS_SSL_CACHE_H
#define MBEDTLS_SSL_CACHE_H

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

#if !defined(MBEDTLS_SSL_CACHE_DEFAULT_TIMEOUT)
#define MBEDTLS_SSL_CACHE_DEFAULT_TIMEOUT       86400   /*!< 1天*/
#endif

#if !defined(MBEDTLS_SSL_CACHE_DEFAULT_MAX_ENTRIES)
#define MBEDTLS_SSL_CACHE_DEFAULT_MAX_ENTRIES      50   /*!< 缓存中的最大条目数*/
#endif

/* \}name SECTION:模块设置*/

#ifdef __cplusplus
extern "C" {
#endif

typedef struct mbedtls_ssl_cache_context mbedtls_ssl_cache_context;
typedef struct mbedtls_ssl_cache_entry mbedtls_ssl_cache_entry;

/**
 * \brief此结构用于存储缓存条目
 */
struct mbedtls_ssl_cache_entry
{
#if defined(MBEDTLS_HAVE_TIME)
    mbedtls_time_t timestamp;           /*!< 条目时间戳*/
#endif
    mbedtls_ssl_session session;        /*!< 进入会话*/
#if defined(MBEDTLS_X509_CRT_PARSE_C) && \
    defined(MBEDTLS_SSL_KEEP_PEER_CERTIFICATE)
    mbedtls_x509_buf peer_cert;         /*!< 入口对等证书*/
#endif
    mbedtls_ssl_cache_entry *next;      /*!< 链式指针*/
};

/**
 * \简短缓存上下文
 */
struct mbedtls_ssl_cache_context
{
    mbedtls_ssl_cache_entry *chain;     /*!< 链条的起点*/
    int timeout;                /*!< 缓存条目超时*/
    int max_entries;            /*!< 最大条目数*/
#if defined(MBEDTLS_THREADING_C)
    mbedtls_threading_mutex_t mutex;    /*!< 互斥锁*/
#endif
};

/**
 * \brief初始化SSL缓存上下文
 *
 * \param缓存SSL缓存上下文
 */
void mbedtls_ssl_cache_init( mbedtls_ssl_cache_context *cache );

/**
 * \简短的缓存获取回调实现（如果启用了MBEDTLS_THREADING_C，则线程安全）
 *
 * \param data SSL缓存上下文\param要检索条目的会话会话
 */
int mbedtls_ssl_cache_get( void *data, mbedtls_ssl_session *session );

/**
 * \简短的缓存集回调实现（如果启用了MBEDTLS_THREADING_C，则线程安全）
 *
 * \param data SSL缓存上下文\param要存储条目的会话会话
 */
int mbedtls_ssl_cache_set( void *data, const mbedtls_ssl_session *session );

#if defined(MBEDTLS_HAVE_TIME)
/**
 * \brief设置缓存超时（默认值：MBEDTLS_SL_cache_Default_timeout（1天））
 *
 *                 超时为0表示没有超时。
 *
 * \param缓存SSL缓存上下文\param超时缓存条目超时（秒）
 */
void mbedtls_ssl_cache_set_timeout( mbedtls_ssl_cache_context *cache, int timeout );
#endif /* MBEDTLS_HAVE_TIME */

/**
 * \brief设置缓存项的最大数量（默认值：MBEDTLS_SL_cache_Default_MAX_entries（50））
 *
 * \param缓存SSL缓存上下文\param最大缓存条目最大值
 */
void mbedtls_ssl_cache_set_max_entries( mbedtls_ssl_cache_context *cache, int max );

/**
 * \brief释放缓存上下文中的引用项并清除内存
 *
 * \param缓存SSL缓存上下文
 */
void mbedtls_ssl_cache_free( mbedtls_ssl_cache_context *cache );

#ifdef __cplusplus
}
#endif

#endif /* ssl_cache.h*/

