/**
 * @file IP API
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
#ifndef LWIP_HDR_IP_H
#define LWIP_HDR_IP_H

#include "lwip/opt.h"

#include "lwip/def.h"
#include "lwip/pbuf.h"
#include "lwip/ip_addr.h"
#include "lwip/err.h"
#include "lwip/netif.h"
#include "lwip/ip4.h"
#include "lwip/ip6.h"
#include "lwip/prot/ip.h"

#ifdef __cplusplus
extern "C" {
#endif

/* 这将作为目标地址传递给ip_output_if（而不是ip_output），这意味着已经在pbuf中构造了ip标头。这在TCP重新传输时使用。*/
#define LWIP_IP_HDRINCL  NULL

/**传递到IP的pbuf的引用计数必须为1，因为当数据包向下传递时，其有效负载指针会发生更改*/
#ifndef LWIP_IP_CHECK_PBUF_REF_COUNT_FOR_TX
#define LWIP_IP_CHECK_PBUF_REF_COUNT_FOR_TX(p) LWIP_ASSERT("p->ref == 1", (p)->ref == 1)
#endif

#if LWIP_NETIF_USE_HINTS
#define IP_PCB_NETIFHINT ;struct netif_hint netif_hints
#else /* LWIP_NETIF_USE_HINTS */
#define IP_PCB_NETIFHINT
#endif /* LWIP_NETIF_USE_HINTS */

/**这是所有PCB类型的共同部分。它需要在PCB类型定义的开头。它位于此处，因此可以在一个位置对该公共部件进行更改，而无需更改所有PCB结构。*/
#define IP_PCB                             \
  /* 网络字节顺序的ip地址*/ \
  ip_addr_t local_ip;                      \
  ip_addr_t remote_ip;                     \
  /* 绑定netif索引*/                  \
  u8_t netif_idx;                          \
  /* 套接字选项*/                     \
  u8_t so_options;                         \
  /* 服务类型*/                    \
  u8_t tos;                                \
  /* 生存的时间*/                       \
  u8_t ttl                                 \
  /* 链路层地址解析提示*/ \
  IP_PCB_NETIFHINT

struct ip_pcb {
  /* 所有PCB类型的通用构件*/
  IP_PCB;
};

/*
 * 每个套接字的选项标志。这些与插座中的SO_XXX相同
 */
#define SOF_REUSEADDR     0x04U  /* 允许本地地址重用*/
#define SOF_KEEPALIVE     0x08U  /* 保持连接活动*/
#define SOF_BROADCAST     0x20U  /* 允许发送和接收广播消息（请参阅IP_SOF_broadcast选项）*/

/* 这些标志是继承的（例如，从侦听pcb到连接pcb）：*/
#define SOF_INHERITED   (SOF_REUSEADDR|SOF_KEEPALIVE)

/**此模块的全局变量，保存在结构中，以便使用base+索引进行有效访问。*/
struct ip_globals
{
  /**接受当前回调调用的数据包的接口。*/
  struct netif *current_netif;
  /**接收当前回调调用的数据包的接口。*/
  struct netif *current_input_netif;
#if LWIP_IPV4
  /**当前正在处理的输入数据包的标头。*/
  const struct ip_hdr *current_ip4_header;
#endif /* LWIP_IPV4 */
#if LWIP_IPV6
  /**当前正在处理的输入IPv6数据包的标头。*/
  struct ip6_hdr *current_ip6_header;
#endif /* LWIP_IPV6 */
  /**current_ip4/6_header的总标头长度（即，在此之后，UDP/TCP标头开始）*/
  u16_t current_ip_header_tot_len;
  /**current_header的源IP地址*/
  ip_addr_t current_iphdr_src;
  /**current_header的目标IP地址*/
  ip_addr_t current_iphdr_dest;
};
extern struct ip_globals ip_data;


/**获取接受当前数据包的接口。这可能是也可能不是接收netif，具体取决于netif/网络设置。只能从接收回调（udp_recv、raw_recv、tcp_accept）调用此函数。否则将返回NULL。*/
#define ip_current_netif()      (ip_data.current_netif)
/**获取接收当前数据包的接口。只能从接收回调（udp_recv、raw_recv、tcp_accept）调用此函数。否则将返回NULL。*/
#define ip_current_input_netif() (ip_data.current_input_netif)
/**ip（6）_current_header（）的总报头长度（即，在此之后，UDP/TCP报头开始）*/
#define ip_current_header_tot_len() (ip_data.current_ip_header_tot_len)
/**current_header的源IP地址*/
#define ip_current_src_addr()   (&ip_data.current_iphdr_src)
/**current_header的目标IP地址*/
#define ip_current_dest_addr()  (&ip_data.current_iphdr_dest)

#if LWIP_IPV4 && LWIP_IPV6
/**获取当前数据包的IPv4标头。只能从接收回调（udp_recv、raw_recv、tcp_accept）调用此函数。否则将返回NULL。*/
#define ip4_current_header()     ip_data.current_ip4_header
/**获取当前数据包的IPv6标头。只能从接收回调（udp_recv、raw_recv、tcp_accept）调用此函数。否则将返回NULL。*/
#define ip6_current_header()      ((const struct ip6_hdr*)(ip_data.current_ip6_header))
/**如果当前IP输入数据包是IPv6，则返回TRUE；如果是IPv4，则返回FALSE*/
#define ip_current_is_v6()        (ip6_current_header() != NULL)
/**current_header的源IPv6地址*/
#define ip6_current_src_addr()    (ip_2_ip6(&ip_data.current_iphdr_src))
/**current_header的目标IPv6地址*/
#define ip6_current_dest_addr()   (ip_2_ip6(&ip_data.current_iphdr_dest))
/**获取传输层协议*/
#define ip_current_header_proto() (ip_current_is_v6() ? \
                                   IP6H_NEXTH(ip6_current_header()) :\
                                   IPH_PROTO(ip4_current_header()))
/**获取传输层标头*/
#define ip_next_header_ptr()     ((const void*)((ip_current_is_v6() ? \
  (const u8_t*)ip6_current_header() : (const u8_t*)ip4_current_header())  + ip_current_header_tot_len()))

/**current_header的源IP4地址*/
#define ip4_current_src_addr()     (ip_2_ip4(&ip_data.current_iphdr_src))
/**current_header的目标IP4地址*/
#define ip4_current_dest_addr()    (ip_2_ip4(&ip_data.current_iphdr_dest))

#elif LWIP_IPV4 /* LWIP_IPV4 && LWIP_IPV6 */

/**获取当前数据包的IPv4标头。只能从接收回调（udp_recv、raw_recv、tcp_accept）调用此函数。否则将返回NULL。*/
#define ip4_current_header()     ip_data.current_ip4_header
/**仅支持IPv4时始终返回FALSE*/
#define ip_current_is_v6()        0
/**获取传输层协议*/
#define ip_current_header_proto() IPH_PROTO(ip4_current_header())
/**获取传输层标头*/
#define ip_next_header_ptr()     ((const void*)((const u8_t*)ip4_current_header() + ip_current_header_tot_len()))
/**current_header的源IP4地址*/
#define ip4_current_src_addr()     (&ip_data.current_iphdr_src)
/**current_header的目标IP4地址*/
#define ip4_current_dest_addr()    (&ip_data.current_iphdr_dest)

#elif LWIP_IPV6 /* LWIP_IPV4 && LWIP_IPV6 */

/**获取当前数据包的IPv6标头。只能从接收回调（udp_recv、raw_recv、tcp_accept）调用此函数。否则将返回NULL。*/
#define ip6_current_header()      ((const struct ip6_hdr*)(ip_data.current_ip6_header))
/**仅支持IPv6时始终返回TRUE*/
#define ip_current_is_v6()        1
/**获取传输层协议*/
#define ip_current_header_proto() IP6H_NEXTH(ip6_current_header())
/**获取传输层标头*/
#define ip_next_header_ptr()     ((const void*)(((const u8_t*)ip6_current_header()) + ip_current_header_tot_len()))
/**current_header的源IP6地址*/
#define ip6_current_src_addr()    (&ip_data.current_iphdr_src)
/**current_header的目标IP6地址*/
#define ip6_current_dest_addr()   (&ip_data.current_iphdr_dest)

#endif /* LWIP_IPV6 */

/**current_header的联合源地址*/
#define ip_current_src_addr()    (&ip_data.current_iphdr_src)
/**current_header的联合目标地址*/
#define ip_current_dest_addr()   (&ip_data.current_iphdr_dest)

/**获取IP pcb选项（SOF_*标志）*/
#define ip_get_option(pcb, opt)   ((pcb)->so_options & (opt))
/**设置IP pcb选项（SOF_*标志）*/
#define ip_set_option(pcb, opt)   ((pcb)->so_options = (u8_t)((pcb)->so_options | (opt)))
/**重置IP pcb选项（SOF_*标志）*/
#define ip_reset_option(pcb, opt) ((pcb)->so_options = (u8_t)((pcb)->so_options & ~(opt)))

#if LWIP_IPV4 && LWIP_IPV6
/**
 * @ingroup ip输出ip数据包，netif由源地址选择
 */
#define ip_output(p, src, dest, ttl, tos, proto) \
        (IP_IS_V6(dest) ? \
        ip6_output(p, ip_2_ip6(src), ip_2_ip6(dest), ttl, tos, proto) : \
        ip4_output(p, ip_2_ip4(src), ip_2_ip4(dest), ttl, tos, proto))
/**
 * @ingroup ip将ip数据包输出到指定接口
 */
#define ip_output_if(p, src, dest, ttl, tos, proto, netif) \
        (IP_IS_V6(dest) ? \
        ip6_output_if(p, ip_2_ip6(src), ip_2_ip6(dest), ttl, tos, proto, netif) : \
        ip4_output_if(p, ip_2_ip4(src), ip_2_ip4(dest), ttl, tos, proto, netif))
/**
 * @ingroup ip将ip数据包输出到指定源地址的接口
 */
#define ip_output_if_src(p, src, dest, ttl, tos, proto, netif) \
        (IP_IS_V6(dest) ? \
        ip6_output_if_src(p, ip_2_ip6(src), ip_2_ip6(dest), ttl, tos, proto, netif) : \
        ip4_output_if_src(p, ip_2_ip4(src), ip_2_ip4(dest), ttl, tos, proto, netif))
/**已包含IP标头的输出IP数据包。*/
#define ip_output_if_hdrincl(p, src, dest, netif) \
        (IP_IS_V6(dest) ? \
        ip6_output_if(p, ip_2_ip6(src), LWIP_IP_HDRINCL, 0, 0, 0, netif) : \
        ip4_output_if(p, ip_2_ip4(src), LWIP_IP_HDRINCL, 0, 0, 0, netif))
/**输出带有netif_int的IP数据包*/
#define ip_output_hinted(p, src, dest, ttl, tos, proto, netif_hint) \
        (IP_IS_V6(dest) ? \
        ip6_output_hinted(p, ip_2_ip6(src), ip_2_ip6(dest), ttl, tos, proto, netif_hint) : \
        ip4_output_hinted(p, ip_2_ip4(src), ip_2_ip4(dest), ttl, tos, proto, netif_hint))
/**
 * @ingroup ip获取netif地址组合。请参见\ref ip6_route和\ref ip4_route
 */
#define ip_route(src, dest) \
        (IP_IS_V6(dest) ? \
        ip6_route(ip_2_ip6(src), ip_2_ip6(dest)) : \
        ip4_route_src(ip_2_ip4(src), ip_2_ip4(dest)))
/**
 * @ingroup ip获取netif for ip。
 */
#define ip_netif_get_local_ip(netif, dest) (IP_IS_V6(dest) ? \
        ip6_netif_get_local_ip(netif, ip_2_ip6(dest)) : \
        ip4_netif_get_local_ip(netif))
#define ip_debug_print(is_ipv6, p) ((is_ipv6) ? ip6_debug_print(p) : ip4_debug_print(p))

err_t ip_input(struct pbuf *p, struct netif *inp);

#elif LWIP_IPV4 /* LWIP_IPV4 && LWIP_IPV6 */

#define ip_output(p, src, dest, ttl, tos, proto) \
        ip4_output(p, src, dest, ttl, tos, proto)
#define ip_output_if(p, src, dest, ttl, tos, proto, netif) \
        ip4_output_if(p, src, dest, ttl, tos, proto, netif)
#define ip_output_if_src(p, src, dest, ttl, tos, proto, netif) \
        ip4_output_if_src(p, src, dest, ttl, tos, proto, netif)
#define ip_output_hinted(p, src, dest, ttl, tos, proto, netif_hint) \
        ip4_output_hinted(p, src, dest, ttl, tos, proto, netif_hint)
#define ip_output_if_hdrincl(p, src, dest, netif) \
        ip4_output_if(p, src, LWIP_IP_HDRINCL, 0, 0, 0, netif)
#define ip_route(src, dest) \
        ip4_route_src(src, dest)
#define ip_netif_get_local_ip(netif, dest) \
        ip4_netif_get_local_ip(netif)
#define ip_debug_print(is_ipv6, p) ip4_debug_print(p)

#define ip_input ip4_input

#elif LWIP_IPV6 /* LWIP_IPV4 && LWIP_IPV6 */

#define ip_output(p, src, dest, ttl, tos, proto) \
        ip6_output(p, src, dest, ttl, tos, proto)
#define ip_output_if(p, src, dest, ttl, tos, proto, netif) \
        ip6_output_if(p, src, dest, ttl, tos, proto, netif)
#define ip_output_if_src(p, src, dest, ttl, tos, proto, netif) \
        ip6_output_if_src(p, src, dest, ttl, tos, proto, netif)
#define ip_output_hinted(p, src, dest, ttl, tos, proto, netif_hint) \
        ip6_output_hinted(p, src, dest, ttl, tos, proto, netif_hint)
#define ip_output_if_hdrincl(p, src, dest, netif) \
        ip6_output_if(p, src, LWIP_IP_HDRINCL, 0, 0, 0, netif)
#define ip_route(src, dest) \
        ip6_route(src, dest)
#define ip_netif_get_local_ip(netif, dest) \
        ip6_netif_get_local_ip(netif, dest)
#define ip_debug_print(is_ipv6, p) ip6_debug_print(p)

#define ip_input ip6_input

#endif /* LWIP_IPV6 */

#define ip_route_get_local_ip(src, dest, netif, ipaddr) do { \
  (netif) = ip_route(src, dest); \
  (ipaddr) = ip_netif_get_local_ip(netif, dest); \
}while(0)

#ifdef __cplusplus
}
#endif

#endif /* LWIP_HDR_IP_H */



