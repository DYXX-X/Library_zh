/*
 * libcoap。h—CoAP堆栈的平台特定头文件
 *
 * 版权所有（C）2015 Carsten Schoenert<c.schoenert@t-online.de>
 *
 * SPDX许可证标识符：BSD-2-Clause
 *
 * 此文件是CoAP库libcoap的一部分。请参阅README了解使用条款。
 */

#ifndef COAP_LIBCOAP_H_
#define COAP_LIBCOAP_H_

/* Contiki、TinyOS、RIOT等非posix嵌入式平台没有posix兼容的头部结构，因此我们必须稍微做一些与平台相关的事情。目前只有Contiki可用，因此我们检查Contiki环境，不包括POSIX相关的网络内容。如果未来还有其他平台，则需要类似的环境。
 *
 * CONTIKI变量在CONTIKI构建环境中！*/

#if defined(_WIN32)
#pragma comment(lib,"Ws2_32.lib")
#include <ws2tcpip.h>
typedef SSIZE_T ssize_t;
typedef USHORT in_port_t;
#elif !defined (CONTIKI)
#include <netinet/in.h>
#include <sys/socket.h>
#endif /* CONTIKI */

#ifndef COAP_STATIC_INLINE
#  if defined(__cplusplus)
#    define COAP_STATIC_INLINE inline
#  else
#    if defined(_MSC_VER)
#      define COAP_STATIC_INLINE static __inline
#    else
#      define COAP_STATIC_INLINE static inline
#    endif
#  endif
#endif
#ifndef COAP_DEPRECATED
#  if defined(_MSC_VER)
#    define COAP_DEPRECATED __declspec(deprecated)
#  else
#    define COAP_DEPRECATED __attribute__ ((deprecated))
#  endif
#endif
#ifndef COAP_UNUSED
#  ifdef __GNUC__
#    define COAP_UNUSED __attribute__((unused))
#  else /* __GNUC__ */
#    define COAP_UNUSED
#  endif /* __GNUC__ */
#endif /* COAP_UNUSED */

void coap_startup(void);

void coap_cleanup(void);

#endif /* COAP_LIBCOAP_H_ */

