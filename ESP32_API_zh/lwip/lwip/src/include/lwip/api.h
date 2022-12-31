/**
 * @file netconn API（从非TCPIP线程使用）
 */

/*
 * 版权所有（c）2001-2004瑞典计算机科学研究所。保留所有权利。
 *
 * 在满足以下条件的情况下，允许以源代码和二进制形式重新分发和使用，无论是否进行修改：
 *
 * 1.源代码的重新分发必须保留上述版权声明、本条件列表和以下免责声明。2.二进制形式的再发行必须在随发行提供的文档和/或其他材料中复制上述版权声明、本条件列表和以下免责声明。3.未经事先书面许可，不得使用作者的姓名为本软件衍生的产品背书或推广。
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * 此文件是lwIP TCP/IP堆栈的一部分。
 *
 * 作者：Adam Dunkels<adam@sics.se>
 *
 */
#ifndef LWIP_HDR_API_H
#define LWIP_HDR_API_H

#include "lwip/opt.h"

#if LWIP_NETCONN || LWIP_SOCKET /* 如果未配置为在lwipots中使用，请不要构建。小时*/
/* 注意：当套接字被启用时，Netconn API总是可用的-套接字是在套接字之上实现的*/

#include "lwip/arch.h"
#include "lwip/netbuf.h"
#include "lwip/sys.h"
#include "lwip/ip_addr.h"
#include "lwip/err.h"

#ifdef __cplusplus
extern "C" {
#endif

/* 在整个文件中，IP地址和端口号的字节顺序与相应的pcb中的字节顺序相同。
 */

/* netconn_write（u8_t）的标志*/
#define NETCONN_NOFLAG      0x00
#define NETCONN_NOCOPY      0x00 /* 仅用于源代码兼容性*/
#define NETCONN_COPY        0x01
#define NETCONN_MORE        0x02
#define NETCONN_DONTBLOCK   0x04
#define NETCONN_NOAUTORCVD  0x08 /* 阻止netconn_recv_data_tcp（）更新tcp窗口-必须通过netconn_tcp_recfd（）手动完成*/
#define NETCONN_NOFIN       0x10 /* 上层已经接收到数据，将FIN留在队列中，直到再次调用*/

/* 结构netconn的标志。标志（u8_t）*/
/**此netconn出现错误，不再阻止recvmbox/acceptmbox*/
#define NETCONN_FLAG_MBOXCLOSED               0x01
/**这个netconn应该避免阻塞吗？*/
#define NETCONN_FLAG_NON_BLOCKING             0x02
/**上一次连接操作是否为非阻塞操作？*/
#define NETCONN_FLAG_IN_NONBLOCKING_CONNECT   0x04
#if LWIP_NETCONN_FULLDUPLEX
  /**此netconn的mbox正在解除分配，不要再使用它*/
#define NETCONN_FLAG_MBOXINVALID              0x08
#endif /* LWIP_NETCONN_FULLDUPLEX */
/**如果之前拒绝了非阻塞写入，则poll_tcp需要检查netconn是否可再次写入*/
#define NETCONN_FLAG_CHECK_WRITESPACE         0x10
#if LWIP_IPV6
/**如果设置了此标志，则netconn上只允许IPv6通信。根据RFC#3493，该功能默认为OFF，允许默认使用双堆栈。*/
#define NETCONN_FLAG_IPV6_V6ONLY              0x20
#endif /* LWIP_IPV6 */
#if LWIP_NETBUF_RECVINFO
/**将记录此netconn的接收数据包信息*/
#define NETCONN_FLAG_PKTINFO                  0x40
#endif /* LWIP_NETBUF_RECVINFO */
/**已收到FIN，但尚未传递给应用程序*/
#define NETCONN_FIN_RX_PENDING                0x80

/* 通过同一代码处理多个netconn_type的帮助程序*/
#define NETCONNTYPE_GROUP(t)         ((t)&0xF0)
#define NETCONNTYPE_DATAGRAM(t)      ((t)&0xE0)
#if LWIP_IPV6
#define NETCONN_TYPE_IPV6            0x08
#define NETCONNTYPE_ISIPV6(t)        (((t)&NETCONN_TYPE_IPV6) != 0)
#define NETCONNTYPE_ISUDPLITE(t)     (((t)&0xF3) == NETCONN_UDPLITE)
#define NETCONNTYPE_ISUDPNOCHKSUM(t) (((t)&0xF3) == NETCONN_UDPNOCHKSUM)
#else /* LWIP_IPV6 */
#define NETCONNTYPE_ISIPV6(t)        (0)
#define NETCONNTYPE_ISUDPLITE(t)     ((t) == NETCONN_UDPLITE)
#define NETCONNTYPE_ISUDPNOCHKSUM(t) ((t) == NETCONN_UDPNOCHKSUM)
#endif /* LWIP_IPV6 */

/** @ingroup netconn_common协议族和netconn的类型
 */
enum netconn_type {
  NETCONN_INVALID     = 0,
  /**TCP IPv4*/
  NETCONN_TCP         = 0x10,
#if LWIP_IPV6
  /**TCP IPv6*/
  NETCONN_TCP_IPV6    = NETCONN_TCP | NETCONN_TYPE_IPV6 /* 0x18像素*/,
#endif /* LWIP_IPV6 */
  /**UDP IPv4*/
  NETCONN_UDP         = 0x20,
  /**UDP IPv4精简版*/
  NETCONN_UDPLITE     = 0x21,
  /**UDP IPv4无校验和*/
  NETCONN_UDPNOCHKSUM = 0x22,

#if LWIP_IPV6
  /**UDP IPv6（默认情况下为双堆栈，除非仅调用@ref netconn_set_IPv6）*/
  NETCONN_UDP_IPV6         = NETCONN_UDP | NETCONN_TYPE_IPV6 /* 第28位*/,
  /**UDP IPv6 lite（默认情况下为双堆栈，除非仅调用@ref netconn_set_IPv6）*/
  NETCONN_UDPLITE_IPV6     = NETCONN_UDPLITE | NETCONN_TYPE_IPV6 /* 第29页*/,
  /**UDP IPv6无校验和（默认情况下为双堆栈，除非仅调用@ref netconn_set_IPv6）*/
  NETCONN_UDPNOCHKSUM_IPV6 = NETCONN_UDPNOCHKSUM | NETCONN_TYPE_IPV6 /* 0x2a倍*/,
#endif /* LWIP_IPV6 */

  /**原始连接IPv4*/
  NETCONN_RAW         = 0x40
#if LWIP_IPV6
  /**原始连接IPv6（默认情况下为双堆栈，除非仅调用@ref netconn_set_IPv6）*/
  , NETCONN_RAW_IPV6    = NETCONN_RAW | NETCONN_TYPE_IPV6 /* 0x48秒*/
#endif /* LWIP_IPV6 */
};

/**netconn的当前状态。非TCP NETCONN始终处于NETCONN_NONE状态！*/
enum netconn_state {
  NETCONN_NONE,
  NETCONN_WRITE,
  NETCONN_LISTEN,
  NETCONN_CONNECT,
  NETCONN_CLOSE
};

/** 用于通知回调函数有关更改的信息
 * 
 * 事件说明：
 * 
 * 在netconn实现中，有三种方法可以阻止客户端：
 * 
 * -accept mbox（sys_arch_mbox_fetch（&conn->acceptmbox，&accept_ptr，0）；在netconn_accept（）中）
 * -接收mbox（sys_arch_mbox_fetch（&conn->recvmbox，&buf，0）；在netconn_recv_data（）中）
 * -发送队列已满（sys_arch_sem_wait（LWIP_API_MSG_sem（MSG），0）；在lwip_netconn_do_write（）中）
 * 
 * 这些事件必须被视为表示这些mbox/信号量状态的事件。对于非阻塞连接，您需要事先知道对netconn函数调用的调用是否会阻塞，这些事件告诉您这一点。
 * 
 * RCVPLUS事件表示：再次执行可能阻塞的呼叫是安全的。它们在套接字中计数-accept mbox的三个RCVPLUS事件意味着您可以安全地调用netconn_accept 3次而不会被阻止。接收mbox也是一样的。
 * 
 * RCVMINUS事件表示：对可能阻塞的函数的调用“已确认”。套接字实现使计数器递减。
 * 
 * 对于TX，不需要计数，它只是一个标志。SENDPLUS意味着你可以发送一些东西。SENDPLUS发生在将足够的数据传递给对等方以便再次调用netconn_send（）时。当对netconn_send（）的下一次调用将被阻塞时，将发生SENDMINUS事件。
 */
enum netconn_evt {
  NETCONN_EVT_RCVPLUS,
  NETCONN_EVT_RCVMINUS,
  NETCONN_EVT_SENDPLUS,
  NETCONN_EVT_SENDMINUS,
  NETCONN_EVT_ERROR
};

#if LWIP_IGMP || (LWIP_IPV6 && LWIP_IPV6_MLD)
/**用于netconn_join_leave_group（）*/
enum netconn_igmp {
  NETCONN_JOIN,
  NETCONN_LEAVE
};
#endif /* LWIP_IGMP || (LWIP_IPV6 && LWIP_IPV6_MLD) */

#if LWIP_DNS
/* 用于netconn_gethostbyname_addrtype（），它们应该与DNS中定义的DNS_addrtype相匹配。小时*/
#define NETCONN_DNS_DEFAULT   NETCONN_DNS_IPV4_IPV6
#define NETCONN_DNS_IPV4      0
#define NETCONN_DNS_IPV6      1
#define NETCONN_DNS_IPV4_IPV6 2 /* 首先尝试解析IPv4，如果IPv4失败，则尝试IPv6*/
#define NETCONN_DNS_IPV6_IPV4 3 /* 首先尝试解析IPv6，如果IPv6失败，则尝试IPv4*/
#endif /* LWIP_DNS */

/* 转发声明一些结构以避免包含其标头*/
struct ip_pcb;
struct tcp_pcb;
struct udp_pcb;
struct raw_pcb;
struct netconn;
struct api_msg;

/**通知netconn事件的回调原型*/
typedef void (* netconn_callback)(struct netconn *, enum netconn_evt, u16_t len);

/**netconn描述符*/
struct netconn {
  /**netconn的类型（TCP、UDP或RAW）*/
  enum netconn_type type;
  /**netconn的当前状态*/
  enum netconn_state state;
  /**lwIP内部协议控制块*/
  union {
    struct ip_pcb  *ip;
    struct tcp_pcb *tcp;
    struct udp_pcb *udp;
    struct raw_pcb *raw;
  } pcb;
  /**此netconn的最后一个异步未报告错误*/
  err_t pending_err;
#if !LWIP_NETCONN_SEM_PER_THREAD
  /**用于在核心上下文中同步执行函数的sem*/
  sys_sem_t op_completed;
#endif
  /**mbox，其中存储接收到的数据包，直到它们被netconn应用程序线程获取（可能会变得很大）*/
  sys_mbox_t recvmbox;
#if LWIP_TCP
  /**mbox，其中存储新连接，直到由应用程序线程处理*/
  sys_mbox_t acceptmbox;
#if ESP_THREAD_PROTECTION
  bool write_protection;
#endif /* ESP_THREAD_PROTECTION */
#endif /* LWIP_TCP */
#if LWIP_NETCONN_FULLDUPLEX
  /**等待mbox的线程数。这是在线程等待时关闭时解除阻止所有线程所必需的。*/
  int mbox_threads_waiting;
#endif
  /**仅用于套接字层*/
#if LWIP_SOCKET
  int socket;
#endif /* LWIP_SOCKET */
#if LWIP_SO_SNDTIMEO
  /**等待发送数据的超时（这意味着在内部缓冲区中排队发送数据）（以毫秒为单位）*/
  s32_t send_timeout;
#endif /* LWIP_SO_RCVTIMEO */
#if LWIP_SO_RCVTIMEO
  /**等待接收新数据（或连接到达以侦听netconn）的超时（毫秒）*/
  u32_t recv_timeout;
#endif /* LWIP_SO_RCVTIMEO */
#if LWIP_SO_RCVBUF
  /**recvmbox中未用于TCP的最大排队字节数：请改为调整TCP_WND！*/
  int recv_bufsize;
  /**recvmbox中当前要接收的字节数，针对recv_bufsize进行测试，以限制recvmbox上UDP和RAW的字节数（用于FIONREAD）*/
  int recv_avail;
#endif /* LWIP_SO_RCVBUF */
#if LWIP_SO_LINGER
   /**值＜0表示延迟被禁用，值＞0表示延迟秒数*/
  s16_t linger;
#endif /* LWIP_SO_LINGER */
  /**保存更多netconn内部状态的标志，请参阅netconn_FLAG_*定义*/
  u8_t flags;
#if LWIP_TCP
  /**TCP：当传递到netconn_write的数据不适合发送缓冲区时，这将临时存储消息。在连接和关闭时也使用。*/
  struct api_msg *current_msg;
#endif /* LWIP_TCP */
  /**通知此netconn事件的回调函数*/
  netconn_callback callback;
};

/** This vector type is passed to @ref netconn_write_vectors_partly一次发送多个缓冲区。注意：此类型必须直接映射结构iovec，因为一个被强制转换为另一个！
 */
struct netvector {
  /**指向包含要发送的数据的应用程序缓冲区的指针*/
  const void *ptr;
  /**要发送的应用程序数据的大小*/
  size_t len;
};

/**注册网络连接事件*/
#define API_EVENT(c,e,l) if (c->callback) {         \
                           (*c->callback)(c, e, l); \
                         }

/* 网络连接功能：*/

/**@ingroup netconn_common创建新的netconn连接@param t@ref netconn_type*/
#define netconn_new(t)                  netconn_new_with_proto_and_callback(t, 0, NULL)
#define netconn_new_with_callback(t, c) netconn_new_with_proto_and_callback(t, 0, c)
struct netconn *netconn_new_with_proto_and_callback(enum netconn_type t, u8_t proto,
                                             netconn_callback callback);
err_t   netconn_prepare_delete(struct netconn *conn);
err_t   netconn_delete(struct netconn *conn);
/**获取netconn的类型（作为enum netconn_type）。*/
#define netconn_type(conn) (conn->type)

err_t   netconn_getaddr(struct netconn *conn, ip_addr_t *addr,
                        u16_t *port, u8_t local);
/**@ingroup netconn_common*/
#define netconn_peer(c,i,p) netconn_getaddr(c,i,p,0)
/**@ingroup netconn_common*/
#define netconn_addr(c,i,p) netconn_getaddr(c,i,p,1)

err_t   netconn_bind(struct netconn *conn, const ip_addr_t *addr, u16_t port);
err_t   netconn_bind_if(struct netconn *conn, u8_t if_idx);
err_t   netconn_connect(struct netconn *conn, const ip_addr_t *addr, u16_t port);
err_t   netconn_disconnect (struct netconn *conn);
err_t   netconn_listen_with_backlog(struct netconn *conn, u8_t backlog);
/**@ingroup网络连接_tcp*/
#define netconn_listen(conn) netconn_listen_with_backlog(conn, TCP_DEFAULT_LISTEN_BACKLOG)
err_t   netconn_accept(struct netconn *conn, struct netconn **new_conn);
err_t   netconn_recv(struct netconn *conn, struct netbuf **new_buf);
err_t   netconn_recv_udp_raw_netbuf(struct netconn *conn, struct netbuf **new_buf);
err_t   netconn_recv_udp_raw_netbuf_flags(struct netconn *conn, struct netbuf **new_buf, u8_t apiflags);
err_t   netconn_recv_tcp_pbuf(struct netconn *conn, struct pbuf **new_buf);
err_t   netconn_recv_tcp_pbuf_flags(struct netconn *conn, struct pbuf **new_buf, u8_t apiflags);
err_t   netconn_tcp_recvd(struct netconn *conn, size_t len);
err_t   netconn_sendto(struct netconn *conn, struct netbuf *buf,
                             const ip_addr_t *addr, u16_t port);
err_t   netconn_send(struct netconn *conn, struct netbuf *buf);
err_t   netconn_write_partly(struct netconn *conn, const void *dataptr, size_t size,
                             u8_t apiflags, size_t *bytes_written);
err_t   netconn_write_vectors_partly(struct netconn *conn, struct netvector *vectors, u16_t vectorcnt,
                                     u8_t apiflags, size_t *bytes_written);
/**@ingroup网络连接_tcp*/
#define netconn_write(conn, dataptr, size, apiflags) \
          netconn_write_partly(conn, dataptr, size, apiflags, NULL)
err_t   netconn_close(struct netconn *conn);
err_t   netconn_shutdown(struct netconn *conn, u8_t shut_rx, u8_t shut_tx);

#if LWIP_IGMP || (LWIP_IPV6 && LWIP_IPV6_MLD)
err_t   netconn_join_leave_group(struct netconn *conn, const ip_addr_t *multiaddr,
                             const ip_addr_t *netif_addr, enum netconn_igmp join_or_leave);
err_t   netconn_join_leave_group_netif(struct netconn *conn, const ip_addr_t *multiaddr,
                             u8_t if_idx, enum netconn_igmp join_or_leave);
#endif /* LWIP_IGMP || (LWIP_IPV6 && LWIP_IPV6_MLD) */
#if LWIP_DNS
#if LWIP_IPV4 && LWIP_IPV6
err_t   netconn_gethostbyname_addrtype(const char *name, ip_addr_t *addr, u8_t dns_addrtype);
#define netconn_gethostbyname(name, addr) netconn_gethostbyname_addrtype(name, addr, NETCONN_DNS_DEFAULT)
#else /* LWIP_IPV4 && LWIP_IPV6 */
err_t   netconn_gethostbyname(const char *name, ip_addr_t *addr);
#define netconn_gethostbyname_addrtype(name, addr, dns_addrtype) netconn_gethostbyname(name, addr)
#endif /* LWIP_IPV4 && LWIP_IPV6 */
#endif /* LWIP_DNS */

err_t   netconn_err(struct netconn *conn);
#define netconn_recv_bufsize(conn)      ((conn)->recv_bufsize)

#define netconn_set_flags(conn, set_flags)     do { (conn)->flags = (u8_t)((conn)->flags |  (set_flags)); } while(0)
#define netconn_clear_flags(conn, clr_flags)   do { (conn)->flags = (u8_t)((conn)->flags & (u8_t)(~(clr_flags) & 0xff)); } while(0)
#define netconn_is_flag_set(conn, flag)        (((conn)->flags & (flag)) != 0)

/**设置netconn调用的阻塞状态（@todo:write/send缺失）*/
#define netconn_set_nonblocking(conn, val)  do { if(val) { \
  netconn_set_flags(conn, NETCONN_FLAG_NON_BLOCKING); \
} else { \
  netconn_clear_flags(conn, NETCONN_FLAG_NON_BLOCKING); }} while(0)
/**获取netconn调用的阻塞状态（@todo:write/send is missing）*/
#define netconn_is_nonblocking(conn)        (((conn)->flags & NETCONN_FLAG_NON_BLOCKING) != 0)

#if LWIP_IPV6
/** @ingroup netconn_common TCP:设置netconn调用的IPv6 ONLY状态（请参阅netconn_FLAG_IPv6_V6ONLY）
 */
#define netconn_set_ipv6only(conn, val)  do { if(val) { \
  netconn_set_flags(conn, NETCONN_FLAG_IPV6_V6ONLY); \
} else { \
  netconn_clear_flags(conn, NETCONN_FLAG_IPV6_V6ONLY); }} while(0)
/** @ingroup netconn_common TCP:获取netconn调用的IPv6 ONLY状态（请参阅netconn_FLAG_IPv6_V6ONLY）
 */
#define netconn_get_ipv6only(conn)        (((conn)->flags & NETCONN_FLAG_IPV6_V6ONLY) != 0)
#endif /* LWIP_IPV6 */

#if LWIP_SO_SNDTIMEO
/**以毫秒为单位设置发送超时*/
#define netconn_set_sendtimeout(conn, timeout)      ((conn)->send_timeout = (timeout))
/**获取以毫秒为单位的发送超时*/
#define netconn_get_sendtimeout(conn)               ((conn)->send_timeout)
#endif /* LWIP_SO_SNDTIMEO */
#if LWIP_SO_RCVTIMEO
/**以毫秒为单位设置接收超时*/
#define netconn_set_recvtimeout(conn, timeout)      ((conn)->recv_timeout = (timeout))
/**获取接收超时（毫秒）*/
#define netconn_get_recvtimeout(conn)               ((conn)->recv_timeout)
#endif /* LWIP_SO_RCVTIMEO */
#if LWIP_SO_RCVBUF
/**以字节为单位设置接收缓冲区*/
#define netconn_set_recvbufsize(conn, recvbufsize)  ((conn)->recv_bufsize = (recvbufsize))
/**获取接收缓冲区（字节）*/
#define netconn_get_recvbufsize(conn)               ((conn)->recv_bufsize)
#endif /* LWIP_SO_RCVBUF*/

#if LWIP_NETCONN_SEM_PER_THREAD
void netconn_thread_init(void);
void netconn_thread_cleanup(void);
#else /* LWIP_NETCONN_SEM_PER_THREAD */
#define netconn_thread_init()
#define netconn_thread_cleanup()
#endif /* LWIP_NETCONN_SEM_PER_THREAD */

#if ESP_THREAD_PROTECTION

#define TCP_WRITE_LOCK(conn)    ((conn)->write_protection = (true))
#define TCP_WRITE_UNLOCK(conn)  ((conn)->write_protection = (false))

#endif /* ESP_THREAD_PROTECTION */

#ifdef __cplusplus
}
#endif

#endif /* LWIP_NETCONN || LWIP_SOCKET */

#endif /* LWIP_HDR_API_H */

