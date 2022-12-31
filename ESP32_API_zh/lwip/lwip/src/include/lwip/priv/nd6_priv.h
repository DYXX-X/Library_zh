/**
 * @file
 *
 * IPv6的邻居发现和无状态地址自动配置。旨在符合RFC 4861（邻居发现）和RFC 4862（地址自动配置）。
 */

/*
 * 版权所有（c）2010 Inico Technologies Ltd.保留所有权利。
 *
 * 在满足以下条件的情况下，允许以源代码和二进制形式重新分发和使用，无论是否进行修改：
 *
 * 1.源代码的重新分发必须保留上述版权声明、本条件列表和以下免责声明。2.二进制形式的再发行必须在随发行提供的文档和/或其他材料中复制上述版权声明、本条件列表和以下免责声明。3.未经事先书面许可，不得使用作者的姓名为本软件衍生的产品背书或推广。
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * 此文件是lwIP TCP/IP堆栈的一部分。
 *
 * 作者：Ivan Delamer<delamer@inicotech.com>
 *
 * 请与Ivan Delamer协调变更和请求
 * <delamer@inicotech.com>
 */

#ifndef LWIP_HDR_ND6_PRIV_H
#define LWIP_HDR_ND6_PRIV_H

#include "lwip/opt.h"

#if LWIP_IPV6  /* 如果未配置为在lwipots中使用，请不要构建。小时*/

#include "lwip/pbuf.h"
#include "lwip/ip6_addr.h"
#include "lwip/netif.h"


#ifdef __cplusplus
extern "C" {
#endif

#if LWIP_ND6_QUEUEING
/** 用于将此处定义的未知地址的传出数据包排队以供memp.h访问的结构
  */
struct nd6_q_entry {
  struct nd6_q_entry *next;
  struct pbuf *p;
};
#endif /* LWIP_ND6_QUEUEING */

/**表的结构。*/
struct nd6_neighbor_cache_entry {
  ip6_addr_t next_hop_address;
  struct netif *netif;
  u8_t lladdr[NETIF_MAX_HWADDR_LEN];
  /*u32_t pmtu；*/
#if LWIP_ND6_QUEUEING
  /**指向此条目上挂起的传出数据包队列的指针。*/
  struct nd6_q_entry *q;
#else /* LWIP_ND6_QUEUEING */
  /**指向此条目上单个挂起的传出数据包的指针。*/
  struct pbuf *q;
#endif /* LWIP_ND6_QUEUEING */
  u8_t state;
  u8_t isrouter;
  union {
    u32_t reachable_time; /* 以秒为单位*/
    u32_t delay_time;     /* 记号（ND6_TMR_INTERVAL）*/
    u32_t probes_sent;
    u32_t stale_time;     /* 记号（ND6_TMR_INTERVAL）*/
  } counter;
};

struct nd6_destination_cache_entry {
  ip6_addr_t destination_addr;
  ip6_addr_t next_hop_addr;
  u16_t pmtu;
  u32_t age;
};

struct nd6_prefix_list_entry {
  ip6_addr_t prefix;
  struct netif *netif;
  u32_t invalidation_timer; /* 以秒为单位*/
};

struct nd6_router_list_entry {
  struct nd6_neighbor_cache_entry *neighbor_entry;
  u32_t invalidation_timer; /* 以秒为单位*/
  u8_t flags;
};

enum nd6_neighbor_cache_entry_state {
  ND6_NO_ENTRY = 0,
  ND6_INCOMPLETE,
  ND6_REACHABLE,
  ND6_STALE,
  ND6_DELAY,
  ND6_PROBE
};

#define ND6_HOPLIM 255 /* 最大跳数限制，所有ND数据包都需要*/

#define ND6_2HRS 7200 /* 两小时，以秒数表示*/

/* 路由器表。*/
/* @如何使这些静态？以及可通过API访问的条目？*/
extern struct nd6_neighbor_cache_entry neighbor_cache[];
extern struct nd6_destination_cache_entry destination_cache[];
extern struct nd6_prefix_list_entry prefix_list[];
extern struct nd6_router_list_entry default_router_list[];

/* 默认值，可通过RA消息更新。*/
extern u32_t reachable_time;
extern u32_t retrans_timer;

#ifdef __cplusplus
}
#endif

#endif /* LWIP_IPV6 */

#endif /* LWIP_HDR_ND6_PRIV_H */

