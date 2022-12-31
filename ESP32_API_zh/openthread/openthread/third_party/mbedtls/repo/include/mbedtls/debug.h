/**
 * \文件debug.h
 *
 * \用于控制和提供库的调试输出的简短函数。
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
#ifndef MBEDTLS_DEBUG_H
#define MBEDTLS_DEBUG_H

#if !defined(MBEDTLS_CONFIG_FILE)
#include "mbedtls/config.h"
#else
#include MBEDTLS_CONFIG_FILE
#endif

#include "mbedtls/ssl.h"

#if defined(MBEDTLS_ECP_C)
#include "mbedtls/ecp.h"
#endif

#if defined(MBEDTLS_DEBUG_C)

#define MBEDTLS_DEBUG_STRIP_PARENS( ... )   __VA_ARGS__

#define MBEDTLS_SSL_DEBUG_MSG( level, args )                    \
    mbedtls_debug_print_msg( ssl, level, __FILE__, __LINE__,    \
                             MBEDTLS_DEBUG_STRIP_PARENS args )

#define MBEDTLS_SSL_DEBUG_RET( level, text, ret )                \
    mbedtls_debug_print_ret( ssl, level, __FILE__, __LINE__, text, ret )

#define MBEDTLS_SSL_DEBUG_BUF( level, text, buf, len )           \
    mbedtls_debug_print_buf( ssl, level, __FILE__, __LINE__, text, buf, len )

#if defined(MBEDTLS_BIGNUM_C)
#define MBEDTLS_SSL_DEBUG_MPI( level, text, X )                  \
    mbedtls_debug_print_mpi( ssl, level, __FILE__, __LINE__, text, X )
#endif

#if defined(MBEDTLS_ECP_C)
#define MBEDTLS_SSL_DEBUG_ECP( level, text, X )                  \
    mbedtls_debug_print_ecp( ssl, level, __FILE__, __LINE__, text, X )
#endif

#if defined(MBEDTLS_X509_CRT_PARSE_C)
#define MBEDTLS_SSL_DEBUG_CRT( level, text, crt )                \
    mbedtls_debug_print_crt( ssl, level, __FILE__, __LINE__, text, crt )
#endif

#if defined(MBEDTLS_ECDH_C)
#define MBEDTLS_SSL_DEBUG_ECDH( level, ecdh, attr )               \
    mbedtls_debug_printf_ecdh( ssl, level, __FILE__, __LINE__, ecdh, attr )
#endif

#else /* MBEDTLS_DEBUG_C */

#define MBEDTLS_SSL_DEBUG_MSG( level, args )            do { } while( 0 )
#define MBEDTLS_SSL_DEBUG_RET( level, text, ret )       do { } while( 0 )
#define MBEDTLS_SSL_DEBUG_BUF( level, text, buf, len )  do { } while( 0 )
#define MBEDTLS_SSL_DEBUG_MPI( level, text, X )         do { } while( 0 )
#define MBEDTLS_SSL_DEBUG_ECP( level, text, X )         do { } while( 0 )
#define MBEDTLS_SSL_DEBUG_CRT( level, text, crt )       do { } while( 0 )
#define MBEDTLS_SSL_DEBUG_ECDH( level, ecdh, attr )     do { } while( 0 )

#endif /* MBEDTLS_DEBUG_C */

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \brief设置阈值错误级别以全局处理所有调试输出。级别超过阈值的调试消息将被丢弃。（默认值：0=无调试）
 *
 * \param threshold要筛选的消息的保留级别。较高级别的消息将被丢弃。
 *                          -调试级别
 *                              -0无调试
 *                              -1错误
 *                              -2状态更改
 *                              -3信息
 *                              -4详细信息
 */
void mbedtls_debug_set_threshold( int threshold );

/**
 * \brief将消息打印到调试输出。此函数始终通过MBEDTLS_SL_DEBUG_MSG（）宏使用，该宏提供SSL上下文、文件和行号参数。
 *
 * \param ssl ssl上下文\param调试消息的错误级别\param文件文件消息出现在\param行号中消息出现在@param格式格式说明符、printf格式\param…格式说明符使用的变量中
 *
 * \注意：此功能仅供库内部使用。
 */
void mbedtls_debug_print_msg( const mbedtls_ssl_context *ssl, int level,
                              const char *file, int line,
                              const char *format, ... );

/**
 * \brief将函数的返回值打印到调试输出。此函数始终通过MBEDTLS_SL_DEBUG_RET（）宏使用，该宏提供SSL上下文、文件和行号参数。
 *
 * \param ssl ssl上下文\param调试消息的错误级别\param文件文件错误发生在\param行号错误发生在\param text返回错误的函数的名称\param ret返回代码值
 *
 * \注意：此功能仅供库内部使用。
 */
void mbedtls_debug_print_ret( const mbedtls_ssl_context *ssl, int level,
                      const char *file, int line,
                      const char *text, int ret );

/**
 * \brief将大小为len字节的缓冲区输出到调试输出。此函数始终通过MBEDTLS_SL_DEBUG_BUF（）宏使用，该宏提供SSL上下文、文件和行号参数。
 *
 * \param ssl ssl上下文\param调试消息的错误级别\param文件文件错误发生在\param行号中错误发生在正在转储的缓冲区的名称或标签中。通常，要输出的缓冲区的变量或缓冲区名称\n缓冲区的长度
 *
 * \注意：此功能仅供库内部使用。
 */
void mbedtls_debug_print_buf( const mbedtls_ssl_context *ssl, int level,
                      const char *file, int line, const char *text,
                      const unsigned char *buf, size_t len );

#if defined(MBEDTLS_BIGNUM_C)
/**
 * \brief将MPI变量打印到调试输出。此函数始终通过MBEDTLS_SL_DEBUG_MPI（）宏使用，该宏提供SSL上下文、文件和行号参数。
 *
 * \param ssl ssl上下文\param调试消息的错误级别\param文件文件错误发生在\param行号中错误发生在/param文本中正在输出的MPI的名称或标签中。通常，变量名\param X是MPI变量
 *
 * \注意：此功能仅供库内部使用。
 */
void mbedtls_debug_print_mpi( const mbedtls_ssl_context *ssl, int level,
                      const char *file, int line,
                      const char *text, const mbedtls_mpi *X );
#endif

#if defined(MBEDTLS_ECP_C)
/**
 * \brief将ECP点打印到调试输出。此函数始终通过MBEDTLS_SL_DEBUG_ECP（）宏使用，该宏提供SSL上下文、文件和行号参数。
 *
 * \param ssl ssl上下文\param调试消息的错误级别\param文件文件错误发生在\param行号中错误发生在正在输出的ECP点的名称或标签中。通常变量名\param X ECP点
 *
 * \注意：此功能仅供库内部使用。
 */
void mbedtls_debug_print_ecp( const mbedtls_ssl_context *ssl, int level,
                      const char *file, int line,
                      const char *text, const mbedtls_ecp_point *X );
#endif

#if defined(MBEDTLS_X509_CRT_PARSE_C)
/**
 * \brief将X.509证书结构打印到调试输出。此函数始终通过MBEDTLS_SL_DEBUG_CRT（）宏使用，该宏提供SSL上下文、文件和行号参数。
 *
 * \param ssl ssl上下文\param调试消息的错误级别\param文件文件错误发生在\param行号错误发生在\param文本要输出的证书的名称或标签\param crt X.509证书结构
 *
 * \注意：此功能仅供库内部使用。
 */
void mbedtls_debug_print_crt( const mbedtls_ssl_context *ssl, int level,
                      const char *file, int line,
                      const char *text, const mbedtls_x509_crt *crt );
#endif

#if defined(MBEDTLS_ECDH_C)
typedef enum
{
    MBEDTLS_DEBUG_ECDH_Q,
    MBEDTLS_DEBUG_ECDH_QP,
    MBEDTLS_DEBUG_ECDH_Z,
} mbedtls_debug_ecdh_attr;

/**
 * \brief将SSL上下文中ECDH结构的字段打印到调试输出。此函数始终通过MBEDTLS_SL_DEBUG_ECDH（）宏使用，该宏提供SSL上下文、文件和行号参数。
 *
 * \param ssl ssl上下文\param调试消息的错误级别\param文件文件错误发生在\param行号中错误发生在\param ecdh ecdh上下文中\param attr正在输出的属性的标识符
 *
 * \注意：此功能仅供库内部使用。
 */
void mbedtls_debug_printf_ecdh( const mbedtls_ssl_context *ssl, int level,
                                const char *file, int line,
                                const mbedtls_ecdh_context *ecdh,
                                mbedtls_debug_ecdh_attr attr );
#endif

#ifdef __cplusplus
}
#endif

#endif /* 调试.h*/

