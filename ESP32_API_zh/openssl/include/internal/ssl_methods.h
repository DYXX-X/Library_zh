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

#ifndef _SSL_METHODS_H_
#define _SSL_METHODS_H_

#include "ssl_types.h"

#ifdef __cplusplus
 extern "C" {
#endif

/**
 * TLS方法功能实现
 */
#define IMPLEMENT_TLS_METHOD_FUNC(func_name, \
                    new, free, \
                    handshake, shutdown, clear, \
                    read, send, pending, \
                    set_fd, set_hostname, get_fd,	\
                    set_bufflen, \
                    get_verify_result, \
                    get_state) \
        static const SSL_METHOD_FUNC func_name LOCAL_ATRR = { \
                new, \
                free, \
                handshake, \
                shutdown, \
                clear, \
                read, \
                send, \
                pending, \
                set_fd, \
		set_hostname, \
                get_fd, \
                set_bufflen, \
                get_verify_result, \
                get_state \
        };

#define IMPLEMENT_TLS_METHOD(ver, mode, fun, func_name) \
    const SSL_METHOD* func_name(void) { \
        static const SSL_METHOD func_name##_data LOCAL_ATRR = { \
                ver, \
                mode, \
                &(fun), \
        }; \
        return &func_name##_data; \
    }

#define IMPLEMENT_SSL_METHOD(ver, mode, fun, func_name) \
    const SSL_METHOD* func_name(void) { \
        static const SSL_METHOD func_name##_data LOCAL_ATRR = { \
                ver, \
                mode, \
                &(fun), \
        }; \
        return &func_name##_data; \
    }

#define IMPLEMENT_X509_METHOD(func_name, \
                new, \
                free, \
                load, \
                show_info) \
    const X509_METHOD* func_name(void) { \
        static const X509_METHOD func_name##_data LOCAL_ATRR = { \
                new, \
                free, \
                load, \
                show_info \
        }; \
        return &func_name##_data; \
    }

#define IMPLEMENT_PKEY_METHOD(func_name, \
                new, \
                free, \
                load) \
    const PKEY_METHOD* func_name(void) { \
        static const PKEY_METHOD func_name##_data LOCAL_ATRR = { \
                new, \
                free, \
                load \
        }; \
        return &func_name##_data; \
    }

/**
 * @brief 获取X509对象方法
 *
 * @param none
 *
 * @return X509对象方法点
 */
const X509_METHOD* X509_method(void);

/**
 * @brief 获取私钥对象方法
 *
 * @param none
 *
 * @return 私钥对象方法点
 */
const PKEY_METHOD* EVP_PKEY_method(void);

#ifdef __cplusplus
}
#endif

#endif

