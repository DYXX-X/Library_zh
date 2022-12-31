/*
 * coap_io。h—libcoap的默认网络I/O函数
 *
 * 版权所有（C）2012-2013 Olaf Bergmann<bergmann@tzi.org>
 *
 * SPDX许可证标识符：BSD-2-Clause
 *
 * 此文件是CoAP库libcoap的一部分。请参阅README了解使用条款。
 */

#ifndef COAP_IO_INTERNAL_H_
#define COAP_IO_INTERNAL_H_

#include <sys/types.h>

#include "address.h"

#ifdef RIOT_VERSION
#include "net/gnrc.h"
#endif /* RIOT_VERSION */

struct coap_socket_t {
#if defined(WITH_LWIP)
  struct udp_pcb *pcb;
#elif defined(WITH_CONTIKI)
  void *conn;
#else
  coap_fd_t fd;
#endif /* WITH_LWIP */
#if defined(RIOT_VERSION)
  gnrc_pktsnip_t *pkt; /* 指向要处理的接收数据包的指针*/
#endif /* RIOT_VERSION */
  coap_socket_flags_t flags;
  coap_session_t *session; /* 由活动会话的epoll逻辑使用。*/
  coap_endpoint_t *endpoint; /* 由epoll逻辑用于侦听端点。*/
};

/**
 * coap_socket_flags_t值
 */
#define COAP_SOCKET_EMPTY        0x0000  /**<未使用插座*/
#define COAP_SOCKET_NOT_EMPTY    0x0001  /**<套接字不是空的*/
#define COAP_SOCKET_BOUND        0x0002  /**<套接字已绑定*/
#define COAP_SOCKET_CONNECTED    0x0004  /**<插座已连接*/
#define COAP_SOCKET_WANT_READ    0x0010  /**<非阻塞套接字正在等待读取*/
#define COAP_SOCKET_WANT_WRITE   0x0020  /**<非阻塞套接字正在等待写入*/
#define COAP_SOCKET_WANT_ACCEPT  0x0040  /**<非阻塞服务器套接字正在等待接受*/
#define COAP_SOCKET_WANT_CONNECT 0x0080  /**<非阻塞客户端套接字正在等待连接*/
#define COAP_SOCKET_CAN_READ     0x0100  /**<非阻塞套接字现在可以无阻塞地读取*/
#define COAP_SOCKET_CAN_WRITE    0x0200  /**<非阻塞套接字现在可以无阻塞地写入*/
#define COAP_SOCKET_CAN_ACCEPT   0x0400  /**<非阻塞服务器套接字现在可以无阻塞地接受*/
#define COAP_SOCKET_CAN_CONNECT  0x0800  /**<无阻塞客户端套接字现在可以无阻塞地连接*/
#define COAP_SOCKET_MULTICAST    0x1000  /**<套接字用于多播通信*/

coap_endpoint_t *coap_malloc_endpoint( void );
void coap_mfree_endpoint( coap_endpoint_t *ep );

const char *coap_socket_format_errno(int error);

int
coap_socket_connect_udp(coap_socket_t *sock,
                        const coap_address_t *local_if,
                        const coap_address_t *server,
                        int default_port,
                        coap_address_t *local_addr,
                        coap_address_t *remote_addr);

int
coap_socket_bind_udp(coap_socket_t *sock,
                     const coap_address_t *listen_addr,
                     coap_address_t *bound_addr );

void coap_socket_close(coap_socket_t *sock);

ssize_t
coap_socket_send( coap_socket_t *sock, coap_session_t *session,
                  const uint8_t *data, size_t data_len );

ssize_t
coap_socket_write(coap_socket_t *sock, const uint8_t *data, size_t data_len);

ssize_t
coap_socket_read(coap_socket_t *sock, uint8_t *data, size_t data_len);

void
coap_epoll_ctl_mod(coap_socket_t *sock, uint32_t events, const char *func);

#ifdef WITH_LWIP
ssize_t
coap_socket_send_pdu( coap_socket_t *sock, coap_session_t *session,
                      coap_pdu_t *pdu );
#endif

/**
 * 数据传输功能接口。此函数返回已传输的字节数，或错误时返回小于零的值。
 *
 * @param sock             用于发送数据的套接字
 * @param session          未连接套接字的寻址信息，或NULL
 * @param data             要发送的数据。
 * @param datalen          @p数据的实际长度。
 *
 * @return                 成功时写入的字节数，或错误时小于零的值。
 */
ssize_t coap_network_send( coap_socket_t *sock, const coap_session_t *session, const uint8_t *data, size_t datalen );

/**
 * 用于读取数据的功能接口。此函数返回已读取的字节数，或错误时返回小于零的值。如果
 * error, @p *数据包被设置为NULL。
 *
 * @param sock   从中读取数据的套接字
 * @param packet 已接收数据包元数据和有效负载。应预设src和dst。
 *
 * @return       成功时接收的字节数，或错误时小于零的值。
 */
ssize_t coap_network_read( coap_socket_t *sock, coap_packet_t *packet );

#ifndef coap_mcast_interface
# define coap_mcast_interface(Local) 0
#endif

/**
 * 给定一个数据包，将msg和msg_len设置为内存中数据包的地址和长度。
 * */
void coap_packet_get_memmapped(coap_packet_t *packet,
                               unsigned char **address,
                               size_t *length);

#ifdef WITH_LWIP
/**
 * 获取数据包的pbuf。调用者负责释放pbuf。
 */
struct pbuf *coap_packet_extract_pbuf(coap_packet_t *packet);
#endif

#if defined(WITH_LWIP)
/*
 * 这仅包含在coap_io中。h而不是.c，以便可以在lwippools.h中使用sizeof。简单地将传入的pbuf结转为节点。
 *
 * 源地址数据目前通过ip_current_dest_addr&co进行了侧带处理，因为数据包的使用寿命有限。
 */
struct coap_packet_t {
  struct pbuf *pbuf;
  const coap_endpoint_t *local_interface;
  coap_addr_tuple_t addr_info; /**<本地和远程地址*/
  int ifindex;                /**<接口索引*/
//  uint16_t srcport；
};
#else
struct coap_packet_t {
  coap_addr_tuple_t addr_info; /**<本地和远程地址*/
  int ifindex;                /**<接口索引*/
  size_t length;              /**<有效载荷长度*/
  unsigned char payload[COAP_RXBUFFER_SIZE]; /**<有效载荷*/
};
#endif

#endif /* COAP_IO_INTERNAL_H_ */

