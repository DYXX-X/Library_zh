// 版权所有2015-2016 Espressif Systems（上海）私人有限公司
//
// 根据Apache许可证2.0版（“许可证”）获得许可；
// 除非符合许可证，否则不得使用此文件。
// 您可以在以下地址获取许可证副本：

//     http://www.apache.org/licenses/LICENSE-2.0
//
// 除非适用法律要求或书面同意，软件
// 根据许可证分发的内容是按“原样”分发的，
// 无任何明示或暗示的保证或条件。
// 有关管理权限和
// 许可证下的限制。

#ifndef _SSL_DEBUG_H_
#define _SSL_DEBUG_H_

#include "platform/ssl_opt.h"
#include "platform/ssl_port.h"

#ifdef __cplusplus
 extern "C" {
#endif

#ifdef CONFIG_OPENSSL_DEBUG_LEVEL
    #define SSL_DEBUG_LEVEL CONFIG_OPENSSL_DEBUG_LEVEL
#else
    #define SSL_DEBUG_LEVEL 0
#endif

#define SSL_DEBUG_ON  (SSL_DEBUG_LEVEL + 1)
#define SSL_DEBUG_OFF (SSL_DEBUG_LEVEL - 1)

#ifdef CONFIG_OPENSSL_DEBUG
    #ifndef SSL_DEBUG_LOG
        #error "SSL_DEBUG_LOG is not defined"
    #endif

    #ifndef SSL_DEBUG_FL
        #define SSL_DEBUG_FL "\n"
    #endif

    #define SSL_SHOW_LOCATION()                         \
        SSL_DEBUG_LOG("SSL assert : %s %d\n",           \
            __FILE__, __LINE__)

    #define SSL_DEBUG(level, fmt, ...)                  \
    {                                                   \
        if (level > SSL_DEBUG_LEVEL) {                  \
            SSL_DEBUG_LOG(fmt SSL_DEBUG_FL, ##__VA_ARGS__); \
        }                                               \
    }
#else /* CONFIG_OPENSSL_DEBUG */
    #define SSL_SHOW_LOCATION()

    #define SSL_DEBUG(level, fmt, ...)
#endif /* CONFIG_OPENSSL_DEBUG */

/**
 * OpenSSL断言函数
 *
 * 如果选择“CONFIG_OPENSSL_ASSERT_DEBUG”，SSL_ASSERT*将显示错误文件名和行。如果选择“CONFIG_OPENSSL_ASSERT_DEBUG_EXIT”SSL_ASSERT将显示错误文件名和行，然后返回错误代码。如果选择“CONFIG_OPENSSL_ASSERT_DEBUG_BLOCK”，SSL_ASSERT将显示错误文件名和行，然后在此处用“while（1）”进行阻止
 *
 * SSL_ASSERT1可能会返回“-1”，所以函数的返回参数是整数。SSL_ASSERT2可能会返回“NULL”，所以函数的返回参数是一个点。SSL_ASSERT2可能不会返回任何内容，因此函数的返回参数为“void”。
 */
#if defined(CONFIG_OPENSSL_ASSERT_DEBUG)
    #define SSL_ASSERT1(s)                              \
    {                                                   \
        if (!(s)) {                                     \
            SSL_SHOW_LOCATION();                        \
        }                                               \
    }

    #define SSL_ASSERT2(s)                              \
    {                                                   \
        if (!(s)) {                                     \
            SSL_SHOW_LOCATION();                        \
        }                                               \
    }

    #define SSL_ASSERT3(s)                              \
    {                                                   \
        if (!(s)) {                                     \
            SSL_SHOW_LOCATION();                        \
        }                                               \
    }
#elif defined(CONFIG_OPENSSL_ASSERT_EXIT)
    #define SSL_ASSERT1(s)                              \
    {                                                   \
        if (!(s)) {                                     \
            return -1;                                  \
        }                                               \
    }

    #define SSL_ASSERT2(s)                              \
    {                                                   \
        if (!(s)) {                                     \
            return NULL;                                \
        }                                               \
    }

    #define SSL_ASSERT3(s)                              \
    {                                                   \
        if (!(s)) {                                     \
            return ;                                    \
        }                                               \
    }
#elif defined(CONFIG_OPENSSL_ASSERT_DEBUG_EXIT)
    #define SSL_ASSERT1(s)                              \
    {                                                   \
        if (!(s)) {                                     \
            SSL_SHOW_LOCATION();                        \
            return -1;                                  \
        }                                               \
    }

    #define SSL_ASSERT2(s)                              \
    {                                                   \
        if (!(s)) {                                     \
            SSL_SHOW_LOCATION();                        \
            return NULL;                                \
        }                                               \
    }

    #define SSL_ASSERT3(s)                              \
    {                                                   \
        if (!(s)) {                                     \
            SSL_SHOW_LOCATION();                        \
            return ;                                    \
        }                                               \
    }
#elif defined(CONFIG_OPENSSL_ASSERT_DEBUG_BLOCK)
    #define SSL_ASSERT1(s)                              \
    {                                                   \
        if (!(s)) {                                     \
            SSL_SHOW_LOCATION();                        \
            while (1);                                  \
        }                                               \
    }

    #define SSL_ASSERT2(s)                              \
    {                                                   \
        if (!(s)) {                                     \
            SSL_SHOW_LOCATION();                        \
            while (1);                                  \
        }                                               \
    }

    #define SSL_ASSERT3(s)                              \
    {                                                   \
        if (!(s)) {                                     \
            SSL_SHOW_LOCATION();                        \
            while (1);                                  \
        }                                               \
    }
#else
    #define SSL_ASSERT1(s)
    #define SSL_ASSERT2(s)
    #define SSL_ASSERT3(s)
#endif

#define SSL_PLATFORM_DEBUG_LEVEL SSL_DEBUG_OFF
#define SSL_PLATFORM_ERROR_LEVEL SSL_DEBUG_ON

#define SSL_CERT_DEBUG_LEVEL     SSL_DEBUG_OFF
#define SSL_CERT_ERROR_LEVEL     SSL_DEBUG_ON

#define SSL_PKEY_DEBUG_LEVEL     SSL_DEBUG_OFF
#define SSL_PKEY_ERROR_LEVEL     SSL_DEBUG_ON

#define SSL_X509_DEBUG_LEVEL     SSL_DEBUG_OFF
#define SSL_X509_ERROR_LEVEL     SSL_DEBUG_ON

#define SSL_LIB_DEBUG_LEVEL      SSL_DEBUG_OFF
#define SSL_LIB_ERROR_LEVEL      SSL_DEBUG_ON

#define SSL_STACK_DEBUG_LEVEL    SSL_DEBUG_OFF
#define SSL_STACK_ERROR_LEVEL    SSL_DEBUG_ON

#ifdef __cplusplus
 }
#endif

#endif

