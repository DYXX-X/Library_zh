/**
 * @file UDP API（从TCPIP线程使用）\n另请参阅@ref UDP_raw
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
#ifndef LWIP_HDR_UDP_H
#define LWIP_HDR_UDP_H

#include "lwip/opt.h"

#if LWIP_UDP /* 如果未配置为在lwipots中使用，请不要构建。小时*/

#include "lwip/pbuf.h"
#include "lwip/netif.h"
#include "lwip/ip_addr.h"
#include "lwip/ip.h"
#include "lwip/ip6_addr.h"
#include "lwip/prot/udp.h"

#ifdef __cplusplus
extern "C" {
#endif

#define UDP_FLAGS_NOCHKSUM       0x01U
#define UDP_FLAGS_UDPLITE        0x02U
#define UDP_FLAGS_CONNECTED      0x04U
#define UDP_FLAGS_MULTICAST_LOOP 0x08U

struct udp_pcb;

/** udp pcb接收回调函数的函数原型addr和port的字节顺序与pcb中的相同。如果不再使用pbuf，回调负责释放pbuf。
 *
 * 注意：注意“addr”可能指向pbuf“p”，因此释放这个pbuf也会使“addr“无效。
 *
 * @param arg 用户提供的参数（udp_pcb.recv_arg）
 * @param pcb 接收数据的udp_pcb
 * @param p 接收到的数据包缓冲区
 * @param addr 接收数据包的远程IP地址
 * @param port 接收数据包的远程端口
 */
typedef void (*udp_recv_fn)(void *arg, struct udp_pcb *pcb, struct pbuf *p,
    const ip_addr_t *addr, u16_t port);

/**UDP协议控制块*/
struct udp_pcb {
/**所有PCB类型的通用构件*/
  IP_PCB;

/* 特定于协议的PCB成员*/

  struct udp_pcb *next;

  u8_t flags;
  /**端口按主机字节顺序排列*/
  u16_t local_port, remote_port;

#if LWIP_MULTICAST_TX_OPTIONS
#if LWIP_IPV4
  /**多播数据包的传出网络接口，按IPv4地址（如果不是“任何”）*/
  ip4_addr_t mcast_ip4;
#endif /* LWIP_IPV4 */
  /**多播数据包的传出网络接口，按接口索引（如果非零）*/
  u8_t mcast_ifindex;
  /**传出多播数据包的TTL*/
  u8_t mcast_ttl;
#endif /* LWIP_MULTICAST_TX_OPTIONS */

#if LWIP_UDPLITE
  /**仅用于UDP_LITE*/
  u16_t chksum_len_rx, chksum_len_tx;
#endif /* LWIP_UDPLITE */

  /**接收回调函数*/
  udp_recv_fn recv;
  /**用户为recv回调提供的参数*/
  void *recv_arg;
};
/* udp_pcbs导出以供外部参考（例如SNMP代理）*/
extern struct udp_pcb *udp_pcbs;

/* 以下函数是UDP代码的应用层接口。*/
struct udp_pcb * udp_new        (void);
struct udp_pcb * udp_new_ip_type(u8_t type);
void             udp_remove     (struct udp_pcb *pcb);
err_t            udp_bind       (struct udp_pcb *pcb, const ip_addr_t *ipaddr,
                                 u16_t port);
void             udp_bind_netif (struct udp_pcb *pcb, const struct netif* netif);
err_t            udp_connect    (struct udp_pcb *pcb, const ip_addr_t *ipaddr,
                                 u16_t port);
void             udp_disconnect (struct udp_pcb *pcb);
void             udp_recv       (struct udp_pcb *pcb, udp_recv_fn recv,
                                 void *recv_arg);
err_t            udp_sendto_if  (struct udp_pcb *pcb, struct pbuf *p,
                                 const ip_addr_t *dst_ip, u16_t dst_port,
                                 struct netif *netif);
err_t            udp_sendto_if_src(struct udp_pcb *pcb, struct pbuf *p,
                                 const ip_addr_t *dst_ip, u16_t dst_port,
                                 struct netif *netif, const ip_addr_t *src_ip);
err_t            udp_sendto     (struct udp_pcb *pcb, struct pbuf *p,
                                 const ip_addr_t *dst_ip, u16_t dst_port);
err_t            udp_send       (struct udp_pcb *pcb, struct pbuf *p);

#if LWIP_CHECKSUM_ON_COPY && CHECKSUM_GEN_UDP
err_t            udp_sendto_if_chksum(struct udp_pcb *pcb, struct pbuf *p,
                                 const ip_addr_t *dst_ip, u16_t dst_port,
                                 struct netif *netif, u8_t have_chksum,
                                 u16_t chksum);
err_t            udp_sendto_chksum(struct udp_pcb *pcb, struct pbuf *p,
                                 const ip_addr_t *dst_ip, u16_t dst_port,
                                 u8_t have_chksum, u16_t chksum);
err_t            udp_send_chksum(struct udp_pcb *pcb, struct pbuf *p,
                                 u8_t have_chksum, u16_t chksum);
err_t            udp_sendto_if_src_chksum(struct udp_pcb *pcb, struct pbuf *p,
                                 const ip_addr_t *dst_ip, u16_t dst_port, struct netif *netif,
                                 u8_t have_chksum, u16_t chksum, const ip_addr_t *src_ip);
#endif /* LWIP_CHECKSUM_ON_COPY && CHECKSUM_GEN_UDP */

#define          udp_flags(pcb) ((pcb)->flags)
#define          udp_setflags(pcb, f)  ((pcb)->flags = (f))

#define          udp_set_flags(pcb, set_flags)     do { (pcb)->flags = (u8_t)((pcb)->flags |  (set_flags)); } while(0)
#define          udp_clear_flags(pcb, clr_flags)   do { (pcb)->flags = (u8_t)((pcb)->flags & (u8_t)(~(clr_flags) & 0xff)); } while(0)
#define          udp_is_flag_set(pcb, flag)        (((pcb)->flags & (flag)) != 0)

/* 以下函数是UDP的下层接口。*/
void             udp_input      (struct pbuf *p, struct netif *inp);

void             udp_init       (void);

/* 以与较旧的实现兼容*/
#define udp_new_ip6() udp_new_ip_type(IPADDR_TYPE_V6)

#if LWIP_MULTICAST_TX_OPTIONS
#if LWIP_IPV4
#define udp_set_multicast_netif_addr(pcb, ip4addr) ip4_addr_copy((pcb)->mcast_ip4, *(ip4addr))
#define udp_get_multicast_netif_addr(pcb)          (&(pcb)->mcast_ip4)
#endif /* LWIP_IPV4 */
#define udp_set_multicast_netif_index(pcb, idx)    ((pcb)->mcast_ifindex = (idx))
#define udp_get_multicast_netif_index(pcb)         ((pcb)->mcast_ifindex)
#define udp_set_multicast_ttl(pcb, value)          ((pcb)->mcast_ttl = (value))
#define udp_get_multicast_ttl(pcb)                 ((pcb)->mcast_ttl)
#endif /* LWIP_MULTICAST_TX_OPTIONS */

#if UDP_DEBUG
void udp_debug_print(struct udp_hdr *udphdr);
#else
#define udp_debug_print(udphdr)
#endif

void udp_netif_ip_addr_changed(const ip_addr_t* old_addr, const ip_addr_t* new_addr);

#ifdef __cplusplus
}
#endif

#endif /* LWIP_UDP */

#endif /* LWIP_HDR_UDP_H */

