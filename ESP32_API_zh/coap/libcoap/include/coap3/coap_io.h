/*
 * coap_io。h—libcoap的默认网络I/O函数
 *
 * 版权所有（C）2012-2013 Olaf Bergmann<bergmann@tzi.org>
 *
 * SPDX许可证标识符：BSD-2-Clause
 *
 * 此文件是CoAP库libcoap的一部分。请参阅README了解使用条款。
 */

#ifndef COAP_IO_H_
#define COAP_IO_H_

#include <sys/types.h>

#include "address.h"

#ifdef RIOT_VERSION
#include "net/gnrc.h"
#endif /* RIOT_VERSION */

#ifndef COAP_RXBUFFER_SIZE
#define COAP_RXBUFFER_SIZE 1472
#endif /* COAP_RXBUFFER_SIZE */

/*
 * 通过使用
 * -DCOAP_MAX_EPOLL_EVENTS=nn（编译时）。
 */
#ifndef COAP_MAX_EPOLL_EVENTS
#define COAP_MAX_EPOLL_EVENTS 10
#endif /* COAP_MAX_EPOLL_EVENTS */

#ifdef _WIN32
typedef SOCKET coap_fd_t;
#define coap_closesocket closesocket
#define COAP_SOCKET_ERROR SOCKET_ERROR
#define COAP_INVALID_SOCKET INVALID_SOCKET
#else
typedef int coap_fd_t;
#define coap_closesocket close
#define COAP_SOCKET_ERROR (-1)
#define COAP_INVALID_SOCKET (-1)
#endif

typedef uint16_t coap_socket_flags_t;

typedef struct coap_addr_tuple_t {
  coap_address_t remote;       /**<远程地址和端口*/
  coap_address_t local;        /**<本地地址和端口*/
} coap_addr_tuple_t;

const char *coap_socket_strerror( void );

/**
 * 检查TCP是否可用。
 *
 * @return @如果启用了对TCP的支持，则为c 1，否则为@c 0。
 */
int coap_tcp_is_supported(void);

typedef enum {
  COAP_NACK_TOO_MANY_RETRIES,
  COAP_NACK_NOT_DELIVERABLE,
  COAP_NACK_RST,
  COAP_NACK_TLS_FAILED,
  COAP_NACK_ICMP_ISSUE
} coap_nack_reason_t;

#endif /* COAP_IO_H_ */

