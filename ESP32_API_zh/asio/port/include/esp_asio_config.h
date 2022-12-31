/*
 * SPDX文件版权文本：2018-2021浓缩咖啡系统（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */
#ifndef _ESP_ASIO_CONFIG_H_
#define _ESP_ASIO_CONFIG_H_

//
// 仅当在menuconfig中启用异常时才启用异常
//
# include <sdkconfig.h>
# ifndef CONFIG_COMPILER_CXX_EXCEPTIONS
#  define ASIO_NO_EXCEPTIONS
# endif   // CONFIG_COMPILER_CXX_EXCEPTIONS

# ifndef CONFIG_COMPILER_RTTI
#  define ASIO_NO_TYPEID
# endif   // CONFIG_COMPILER_RTTI

//
// 在构建ASIO时，取消OpenSSL弃用警告
//
#define ESP_OPENSSL_SUPPRESS_LEGACY_WARNING

//
// LWIP兼容性inet和地址宏/函数
//
# define LWIP_COMPAT_SOCKET_INET 1
# define LWIP_COMPAT_SOCKET_ADDR 1

//
// 特定ASIO功能标志
//
# define ASIO_DISABLE_SERIAL_PORT
# define ASIO_SEPARATE_COMPILATION
# define ASIO_STANDALONE
# define ASIO_HAS_PTHREADS

# ifdef CONFIG_ASIO_USE_ESP_OPENSSL
#  define ASIO_USE_ESP_OPENSSL
#  define OPENSSL_NO_ENGINE
# elif CONFIG_ASIO_USE_ESP_WOLFSSL
#  define ASIO_USE_WOLFSSL
# endif   // CONFIG_ASIO_USE_ESP_OPENSSL

#endif // _ESP_ASIO_CONFIG_H_

