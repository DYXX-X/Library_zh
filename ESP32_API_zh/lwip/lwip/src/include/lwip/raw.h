/**
 * @file 原始API（从TCPIP线程使用）\n另请参见@ref raw_raw
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
#ifndef LWIP_HDR_RAW_H
#define LWIP_HDR_RAW_H

#include "lwip/opt.h"

#if LWIP_RAW /* 如果未配置为在lwipots中使用，请不要构建。小时*/

#include "lwip/pbuf.h"
#include "lwip/def.h"
#include "lwip/ip.h"
#include "lwip/ip_addr.h"
#include "lwip/ip6_addr.h"

#ifdef __cplusplus
extern "C" {
#endif

#define RAW_FLAGS_CONNECTED      0x01U
#define RAW_FLAGS_HDRINCL        0x02U
#define RAW_FLAGS_MULTICAST_LOOP 0x04U

struct raw_pcb;

/** 用于原始pcb接收回调函数的函数原型。
 * @param arg 用户提供的参数（raw_pcb.recv_arg）
 * @param pcb 接收数据的raw_pcb
 * @param p 接收到的数据包缓冲区
 * @param addr 接收数据包的远程IP地址
 * @return 如果数据包被“吃掉”（即删除），则为1；如果数据包存在，则为0。如果返回1，则回调将负责释放不再使用的pbuf。
 */
typedef u8_t (*raw_recv_fn)(void *arg, struct raw_pcb *pcb, struct pbuf *p,
    const ip_addr_t *addr);

/**RAW协议控制块*/
struct raw_pcb {
  /* 所有PCB类型的通用构件*/
  IP_PCB;

  struct raw_pcb *next;

  u8_t protocol;
  u8_t flags;

#if LWIP_MULTICAST_TX_OPTIONS
  /**多播数据包的传出网络接口，按接口索引（如果非零）*/
  u8_t mcast_ifindex;
  /**传出多播数据包的TTL*/
  u8_t mcast_ttl;
#endif /* LWIP_MULTICAST_TX_OPTIONS */

  /**接收回调函数*/
  raw_recv_fn recv;
  /* 用户为recv回调提供的参数*/
  void *recv_arg;
#if LWIP_IPV6
  /* 用于根据RFC3542处理校验和计算的字段。*/
  u16_t chksum_offset;
  u8_t  chksum_reqd;
#endif
};

/* 以下函数是RAW代码的应用层接口。*/
struct raw_pcb * raw_new        (u8_t proto);
struct raw_pcb * raw_new_ip_type(u8_t type, u8_t proto);
void             raw_remove     (struct raw_pcb *pcb);
err_t            raw_bind       (struct raw_pcb *pcb, const ip_addr_t *ipaddr);
void             raw_bind_netif (struct raw_pcb *pcb, const struct netif *netif);
err_t            raw_connect    (struct raw_pcb *pcb, const ip_addr_t *ipaddr);
void             raw_disconnect (struct raw_pcb *pcb);

err_t            raw_sendto     (struct raw_pcb *pcb, struct pbuf *p, const ip_addr_t *ipaddr);
err_t            raw_sendto_if_src(struct raw_pcb *pcb, struct pbuf *p, const ip_addr_t *dst_ip, struct netif *netif, const ip_addr_t *src_ip);
err_t            raw_send       (struct raw_pcb *pcb, struct pbuf *p);

void             raw_recv       (struct raw_pcb *pcb, raw_recv_fn recv, void *recv_arg);

#define          raw_flags(pcb) ((pcb)->flags)
#define          raw_setflags(pcb,f)  ((pcb)->flags = (f))

#define          raw_set_flags(pcb, set_flags)     do { (pcb)->flags = (u8_t)((pcb)->flags |  (set_flags)); } while(0)
#define          raw_clear_flags(pcb, clr_flags)   do { (pcb)->flags = (u8_t)((pcb)->flags & (u8_t)(~(clr_flags) & 0xff)); } while(0)
#define          raw_is_flag_set(pcb, flag)        (((pcb)->flags & (flag)) != 0)

#define raw_init() /* 兼容性定义，不需要初始化。*/

/* 以与较旧的实现兼容*/
#define raw_new_ip6(proto) raw_new_ip_type(IPADDR_TYPE_V6, proto)

#if LWIP_MULTICAST_TX_OPTIONS
#define raw_set_multicast_netif_index(pcb, idx) ((pcb)->mcast_ifindex = (idx))
#define raw_get_multicast_netif_index(pcb)      ((pcb)->mcast_ifindex)
#define raw_set_multicast_ttl(pcb, value)       ((pcb)->mcast_ttl = (value))
#define raw_get_multicast_ttl(pcb)              ((pcb)->mcast_ttl)
#endif /* LWIP_MULTICAST_TX_OPTIONS */

#ifdef __cplusplus
}
#endif

#endif /* LWIP_RAW */

#endif /* LWIP_HDR_RAW_H */

