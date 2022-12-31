/**
 * @file netif API（从TCPIP线程使用）
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
#ifndef LWIP_HDR_NETIF_H
#define LWIP_HDR_NETIF_H

#include "lwip/opt.h"

#define ENABLE_LOOPBACK (LWIP_NETIF_LOOPBACK || LWIP_HAVE_LOOPIF)

#include "lwip/err.h"

#include "lwip/ip_addr.h"

#include "lwip/def.h"
#include "lwip/pbuf.h"
#include "lwip/stats.h"

#ifdef __cplusplus
extern "C" {
#endif

/* 在整个文件中，IP地址的字节顺序应与IP_PCB中的相同。*/

/**必须是所用所有类型接口上所有已用硬件地址长度的最大值。这通常不需要更改。*/
#ifndef NETIF_MAX_HWADDR_LEN
#define NETIF_MAX_HWADDR_LEN 6U
#endif

/** 在API中可以识别netif的完全构造的netif名称的大小。由2个字符、3个（最大）数字和1\0组成
 */
#define NETIF_NAMESIZE 6

/**
 * @defgroup netif_flags标志
 * @ingroup netif语言@{
 */

/** 网络接口是否“打开”。这是一个软件标志，用于控制此网络接口是否已启用并处理流量。在使用此netif之前，它必须由启动代码设置（也适用于dhcp/autoip）。
 */
#define NETIF_FLAG_UP           0x01U
/**如果设置，netif具有广播功能。由netif驱动程序在其init函数中设置。*/
#define NETIF_FLAG_BROADCAST    0x02U
/**如果设置，则接口具有活动链接（由网络接口驱动程序设置）。由netif驱动程序在其init函数中设置（如果当时链接已启动），或者在链接启动后的稍后时间设置（如果硬件支持链接检测）。*/
#define NETIF_FLAG_LINK_UP      0x04U
/**如果设置，netif是使用ARP的以太网设备。由netif驱动程序在其init函数中设置。用于检查输入数据包类型和DHCP的使用。*/
#define NETIF_FLAG_ETHARP       0x08U
/** 如果设置，netif是以太网设备。如果仅用于PPPoE，它可能不使用ARP或TCP/IP。
 */
#define NETIF_FLAG_ETHERNET     0x10U
/**如果设置，netif具有IGMP功能。由netif驱动程序在其init函数中设置。*/
#define NETIF_FLAG_IGMP         0x20U
/**如果设置，netif具有MLD6功能。由netif驱动程序在其init函数中设置。*/
#define NETIF_FLAG_MLD6         0x40U

#if ESP_GRATUITOUS_ARP
/**如果设置，netif将定期发送免费ARP*/
#define NETIF_FLAG_GARP         0x80U
#endif

/**
 * @}
 */

enum lwip_internal_netif_client_data_index
{
#if LWIP_IPV4
#if LWIP_DHCP
   LWIP_NETIF_CLIENT_DATA_INDEX_DHCP,
#endif
#if LWIP_AUTOIP
   LWIP_NETIF_CLIENT_DATA_INDEX_AUTOIP,
#endif
#if LWIP_IGMP
   LWIP_NETIF_CLIENT_DATA_INDEX_IGMP,
#endif
#endif /* LWIP_IPV4 */
#if LWIP_IPV6
#if LWIP_IPV6_DHCP6
   LWIP_NETIF_CLIENT_DATA_INDEX_DHCP6,
#endif
#if LWIP_IPV6_MLD
   LWIP_NETIF_CLIENT_DATA_INDEX_MLD6,
#endif
#endif /* LWIP_IPV6 */
   LWIP_NETIF_CLIENT_DATA_INDEX_MAX
};

#if LWIP_CHECKSUM_CTRL_PER_NETIF
#define NETIF_CHECKSUM_GEN_IP       0x0001
#define NETIF_CHECKSUM_GEN_UDP      0x0002
#define NETIF_CHECKSUM_GEN_TCP      0x0004
#define NETIF_CHECKSUM_GEN_ICMP     0x0008
#define NETIF_CHECKSUM_GEN_ICMP6    0x0010
#define NETIF_CHECKSUM_CHECK_IP     0x0100
#define NETIF_CHECKSUM_CHECK_UDP    0x0200
#define NETIF_CHECKSUM_CHECK_TCP    0x0400
#define NETIF_CHECKSUM_CHECK_ICMP   0x0800
#define NETIF_CHECKSUM_CHECK_ICMP6  0x1000
#define NETIF_CHECKSUM_ENABLE_ALL   0xFFFF
#define NETIF_CHECKSUM_DISABLE_ALL  0x0000
#endif /* LWIP_CHECKSUM_CTRL_PER_NETIF */

struct netif;

/**MAC筛选器操作，这些操作将传递给netif的igmp_MAC_Filter或mld_MAC_filt回调函数。*/
enum netif_mac_filter_action {
  /**删除筛选器条目*/
  NETIF_DEL_MAC_FILTER = 0,
  /**添加筛选器条目*/
  NETIF_ADD_MAC_FILTER = 1
};

/** netif init函数的函数原型。在此函数中设置标志和输出/链接输出回调函数。
 *
 * @param netif 要初始化的netif
 */
typedef err_t (*netif_init_fn)(struct netif *netif);
/** netif->输入函数的函数原型。此函数保存为netif结构中的“input”回调函数。收到数据包后调用它。
 *
 * @param p 收到的数据包，复制到pbuf中
 * @param inp 接收数据包的netif
 * @return 如果数据包已处理，则返回ERR_OK！=ERR_OK是未处理的数据包，在这种情况下，调用者必须释放pbuf
 */
typedef err_t (*netif_input_fn)(struct pbuf *p, struct netif *inp);

#if LWIP_IPV4
/** netif->输出函数的函数原型。当应发送数据包时由lwIP调用。对于以太网netif，将其设置为“etharp_output”并设置为“linkoutput”。
 *
 * @param netif 应发送数据包的netif
 * @param p 要发送的数据包（p->有效负载指向IP报头）
 * @param ipaddr 数据包应发送到的IP地址
 */
typedef err_t (*netif_output_fn)(struct netif *netif, struct pbuf *p,
       const ip4_addr_t *ipaddr);
#endif /* LWIP_IPV4*/

#if LWIP_IPV6
/** netif->output_ip6函数的函数原型。当应发送数据包时由lwIP调用。对于以太网netif，将其设置为“ethip6_output”并设置为“linkoutput”。
 *
 * @param netif 应发送数据包的netif
 * @param p 要发送的数据包（p->有效负载指向IP报头）
 * @param ipaddr 数据包应发送到的IPv6地址
 */
typedef err_t (*netif_output_ip6_fn)(struct netif *netif, struct pbuf *p,
       const ip6_addr_t *ipaddr);
#endif /* LWIP_IPV6 */

/** netif->linkoutput函数的函数原型。仅用于以太网网络。当发送数据包时，ARP会调用此函数。
 *
 * @param netif 应发送数据包的netif
 * @param p 要发送的数据包（原始以太网数据包）
 */
typedef err_t (*netif_linkoutput_fn)(struct netif *netif, struct pbuf *p);
/**netif状态或链接回调函数的函数原型。*/
typedef void (*netif_status_callback_fn)(struct netif *netif);
#if LWIP_IPV4 && LWIP_IGMP
/**netif igmp_mac_filter函数的函数原型*/
typedef err_t (*netif_igmp_mac_filter_fn)(struct netif *netif,
       const ip4_addr_t *group, enum netif_mac_filter_action action);
#endif /* LWIP_IPV4 && LWIP_IGMP */
#if LWIP_IPV6 && LWIP_IPV6_MLD
/**netif mld_mac_filter函数的函数原型*/
typedef err_t (*netif_mld_mac_filter_fn)(struct netif *netif,
       const ip6_addr_t *group, enum netif_mac_filter_action action);
#endif /* LWIP_IPV6 && LWIP_IPV6_MLD */

#if LWIP_DHCP || LWIP_AUTOIP || LWIP_IGMP || LWIP_IPV6_MLD || LWIP_IPV6_DHCP6 || (LWIP_NUM_NETIF_CLIENT_DATA > 0)
#if LWIP_NUM_NETIF_CLIENT_DATA > 0
u8_t netif_alloc_client_data_id(void);
#endif
/** @ingroup netif_cd设置客户端数据。从netif_alloc_client_data_ID（）获取ID。
 */
#define netif_set_client_data(netif, id, data) netif_get_client_data(netif, id) = (data)
/** @ingroup netif_cd获取客户端数据。从netif_alloc_client_data_ID（）获取ID。
 */
#define netif_get_client_data(netif, id)       (netif)->client_data[(id)]
#endif

#if (LWIP_IPV4 && LWIP_ARP && (ARP_TABLE_SIZE > 0x7f)) || (LWIP_IPV6 && (LWIP_ND6_NUM_DESTINATIONS > 0x7f))
typedef u16_t netif_addr_idx_t;
#define NETIF_ADDR_IDX_MAX 0x7FFF
#else
typedef u8_t netif_addr_idx_t;
#define NETIF_ADDR_IDX_MAX 0x7F
#endif

#if LWIP_NETIF_HWADDRHINT
#define LWIP_NETIF_USE_HINTS              1
struct netif_hint {
  netif_addr_idx_t addr_hint;
};
#else /* LWIP_NETIF_HWADDRHINT */
#define LWIP_NETIF_USE_HINTS              0
#endif /* LWIP_NETIF_HWADDRHINT */

#if ESP_DHCP
/*刘汉添加DHCP事件处理*/
typedef void (*dhcp_event_fn)(void);
#endif

/**用于所有lwIP网络接口的通用数据结构。设备驱动程序的初始化函数应填写以下字段：hwaddr_len、hwaddr[]、mtu、flags*/
struct netif {
#if !LWIP_SINGLE_NETIF
  /**指向链接列表中下一个的指针*/
  struct netif *next;
#endif

#if LWIP_IPV4
  /**按网络字节顺序配置IP地址*/
  ip_addr_t ip_addr;
  ip_addr_t netmask;
  ip_addr_t gw;
#endif /* LWIP_IPV4 */
#if LWIP_IPV6
  /**此netif的IPv6地址数组。*/
  ip_addr_t ip6_addr[LWIP_IPV6_NUM_ADDRESSES];
  /**每个IPv6地址的状态（暂定、首选等）@请参见ip6_addr。小时*/
  u8_t ip6_addr_state[LWIP_IPV6_NUM_ADDRESSES];
#if LWIP_IPV6_ADDRESS_LIFETIMES
  /**每个IPv6地址的剩余有效和首选生存期（秒）。对于有效的生存期，特殊值IP6_ADDR_LIFE_STATIC（0）表示地址是静态的，没有生存期。*/
  u32_t ip6_addr_valid_life[LWIP_IPV6_NUM_ADDRESSES];
  u32_t ip6_addr_pref_life[LWIP_IPV6_NUM_ADDRESSES];
#endif /* LWIP_IPV6_ADDRESS_LIFETIMES */
#if ESP_LWIP
  void (*ipv6_addr_cb)(struct netif* netif, u8_t ip_idex); /* ipv6地址状态的回调已更改*/
#endif
#endif /* LWIP_IPV6 */
  /**此函数由网络设备驱动程序调用，以将数据包传递到TCP/IP堆栈。*/
  netif_input_fn input;
#if LWIP_IPV4
  /**当IP模块想要在接口上发送数据包时，它会调用此函数。此函数通常首先解析硬件地址，然后发送数据包。对于以太网物理层，这通常是etharp_output（）*/
  netif_output_fn output;
#endif /* LWIP_IPV4 */
  /**当ethernet_output（）想要在接口上发送数据包时，会调用此函数。此函数输出链接媒体上的pbuf。*/
  netif_linkoutput_fn linkoutput;
#if LWIP_IPV6
  /**当IPv6模块想要在接口上发送数据包时，会调用此函数。此函数通常首先解析硬件地址，然后发送数据包。对于以太网物理层，这通常是ethip6_output（）*/
  netif_output_ip6_fn output_ip6;
#endif /* LWIP_IPV6 */
#if LWIP_NETIF_STATUS_CALLBACK
  /** 当netif状态设置为向上或向下时调用此函数
   */
  netif_status_callback_fn status_callback;
#endif /* LWIP_NETIF_STATUS_CALLBACK */
#if LWIP_NETIF_LINK_CALLBACK
  /** 当netif链接设置为向上或向下时调用此函数
   */
  netif_status_callback_fn link_callback;
#endif /* LWIP_NETIF_LINK_CALLBACK */
#if LWIP_NETIF_REMOVE_CALLBACK
  /**删除netif后调用此函数*/
  netif_status_callback_fn remove_callback;
#endif /* LWIP_NETIF_REMOVE_CALLBACK */
  /**该字段可以由设备驱动程序设置，并且可以指向设备的状态信息。*/
  void *state;
#ifdef netif_get_client_data
  void* client_data[LWIP_NETIF_CLIENT_DATA_INDEX_MAX + LWIP_NUM_NETIF_CLIENT_DATA];
#endif

#if ESP_DHCP
  struct udp_pcb *dhcps_pcb;	
  dhcp_event_fn dhcp_event;
#endif

#if LWIP_NETIF_HOSTNAME
  /* 此netif的主机名，NULL是有效值*/
  const char*  hostname;
#endif /* LWIP_NETIF_HOSTNAME */
#if LWIP_CHECKSUM_CTRL_PER_NETIF
  u16_t chksum_flags;
#endif /* LWIP_CHECKSUM_CTRL_PER_NETIF*/
  /**最大传输单位（字节）*/
  u16_t mtu;
#if LWIP_IPV6 && LWIP_ND6_ALLOW_RA_UPDATES
  /**最大传输单位（字节），由RA更新*/
  u16_t mtu6;
#endif /* LWIP_IPV6 && LWIP_ND6_ALLOW_RA_UPDATES */
  /**此接口的链路级硬件地址*/
  u8_t hwaddr[NETIF_MAX_HWADDR_LEN];
  /**hwddr中使用的字节数*/
  u8_t hwaddr_len;
  /**flags（参见@ref netif_flags）*/
  u8_t flags;
  /**描述性缩写*/
  char name[2];
  /**此接口的编号。用于@ref if_api和@ref netifapi_netif以及IPv6区域*/
  u8_t num;
#if LWIP_IPV6_AUTOCONFIG
  /**此netif是否已启用IPv6自动配置*/
  u8_t ip6_autoconfig_enabled;
#endif /* LWIP_IPV6_AUTOCONFIG */
#if LWIP_IPV6_SEND_ROUTER_SOLICIT
  /**仍要发送的路由器请求消息数。*/
  u8_t rs_count;
#endif /* LWIP_IPV6_SEND_ROUTER_SOLICIT */
#if MIB2_STATS
  /**链接类型（来自snmp_mib2.h的“snmp_ifType”枚举）*/
  u8_t link_type;
  /**（估计）链路速度*/
  u32_t link_speed;
  /**上次更改时的时间戳（向上/向下）*/
  u32_t ts;
  /**计数器*/
  struct stats_mib2_netif_ctrs mib2_counters;
#endif /* MIB2_STATS */
#if LWIP_IPV4 && LWIP_IGMP
  /**可以调用此函数来添加或删除以太网MAC的多播过滤器表中的条目。*/
  netif_igmp_mac_filter_fn igmp_mac_filter;
#endif /* LWIP_IPV4 && LWIP_IGMP */
#if LWIP_IPV6 && LWIP_IPV6_MLD
  /**可以调用此函数来添加或删除以太网MAC的IPv6多播过滤器表中的条目。*/
  netif_mld_mac_filter_fn mld_mac_filter;
#endif /* LWIP_IPV6 && LWIP_IPV6_MLD */
#if LWIP_NETIF_USE_HINTS
  struct netif_hint *hints;
#endif /* LWIP_NETIF_USE_HINTS */
#if ENABLE_LOOPBACK
  /* 为我们排队的数据包列表。*/
  struct pbuf *loop_first;
  struct pbuf *loop_last;
#if LWIP_LOOPBACK_MAX_PBUFS
  u16_t loop_cnt_current;
#endif /* LWIP_LOOPBACK_MAX_PBUFS */
#endif /* ENABLE_LOOPBACK */
#if ESP_PBUF
  void (*l2_buffer_free_notify)(struct netif *lwip_netif, void *user_buf); /* 允许LWIP在可以释放L2提供的pbuf时通知驱动程序*/
  ip_addr_t last_ip_addr; /* 存储最后一个非零ip地址*/
#endif
#if ESP_LWIP
#if LWIP_IPV4 && IP_NAPT
  u8_t napt;
#endif
#endif /* ESP_LWIP */
};
#if LWIP_CHECKSUM_CTRL_PER_NETIF
#define NETIF_SET_CHECKSUM_CTRL(netif, chksumflags) do { \
  (netif)->chksum_flags = chksumflags; } while(0)
#define IF__NETIF_CHECKSUM_ENABLED(netif, chksumflag) if (((netif) == NULL) || (((netif)->chksum_flags & (chksumflag)) != 0))
#else /* LWIP_CHECKSUM_CTRL_PER_NETIF */
#define NETIF_SET_CHECKSUM_CTRL(netif, chksumflags)
#define IF__NETIF_CHECKSUM_ENABLED(netif, chksumflag)
#endif /* LWIP_CHECKSUM_CTRL_PER_NETIF */

#if LWIP_SINGLE_NETIF
#define NETIF_FOREACH(netif) if (((netif) = netif_default) != NULL)
#else /* LWIP_SINGLE_NETIF */
/**网络接口列表。*/
extern struct netif *netif_list;
#define NETIF_FOREACH(netif) for ((netif) = netif_list; (netif) != NULL; (netif) = (netif)->next)
#endif /* LWIP_SINGLE_NETIF */
/**默认网络接口。*/
extern struct netif *netif_default;

void netif_init(void);

struct netif *netif_add_noaddr(struct netif *netif, void *state, netif_init_fn init, netif_input_fn input);

#if LWIP_IPV4
struct netif *netif_add(struct netif *netif,
                            const ip4_addr_t *ipaddr, const ip4_addr_t *netmask, const ip4_addr_t *gw,
                            void *state, netif_init_fn init, netif_input_fn input);
void netif_set_addr(struct netif *netif, const ip4_addr_t *ipaddr, const ip4_addr_t *netmask,
                    const ip4_addr_t *gw);
#else /* LWIP_IPV4 */
struct netif *netif_add(struct netif *netif, void *state, netif_init_fn init, netif_input_fn input);
#endif /* LWIP_IPV4 */

#if ESP_GRATUITOUS_ARP
void netif_set_garp_flag(struct netif *netif);
#endif

void netif_remove(struct netif * netif);

/* 返回给定名称的网络接口。名称的形式为“et0”，其中前两个字母是netif结构中的“name”字段，数字位于同一结构中的num字段中。*/
struct netif *netif_find(const char *name);

void netif_set_default(struct netif *netif);

#if LWIP_IPV4
void netif_set_ipaddr(struct netif *netif, const ip4_addr_t *ipaddr);
void netif_set_netmask(struct netif *netif, const ip4_addr_t *netmask);
void netif_set_gw(struct netif *netif, const ip4_addr_t *gw);
/**@ingroup netif_ip4*/
#define netif_ip4_addr(netif)    ((const ip4_addr_t*)ip_2_ip4(&((netif)->ip_addr)))
/**@ingroup netif_ip4*/
#define netif_ip4_netmask(netif) ((const ip4_addr_t*)ip_2_ip4(&((netif)->netmask)))
/**@ingroup netif_ip4*/
#define netif_ip4_gw(netif)      ((const ip4_addr_t*)ip_2_ip4(&((netif)->gw)))
/**@ingroup netif_ip4*/
#define netif_ip_addr4(netif)    ((const ip_addr_t*)&((netif)->ip_addr))
/**@ingroup netif_ip4*/
#define netif_ip_netmask4(netif) ((const ip_addr_t*)&((netif)->netmask))
/**@ingroup netif_ip4*/
#define netif_ip_gw4(netif)      ((const ip_addr_t*)&((netif)->gw))
#endif /* LWIP_IPV4 */

#define netif_set_flags(netif, set_flags)     do { (netif)->flags = (u8_t)((netif)->flags |  (set_flags)); } while(0)
#define netif_clear_flags(netif, clr_flags)   do { (netif)->flags = (u8_t)((netif)->flags & (u8_t)(~(clr_flags) & 0xff)); } while(0)
#define netif_is_flag_set(nefif, flag)        (((netif)->flags & (flag)) != 0)

void netif_set_up(struct netif *netif);
void netif_set_down(struct netif *netif);
/** @ingroup netif询问接口是否启动
 */
#define netif_is_up(netif) (((netif)->flags & NETIF_FLAG_UP) ? (u8_t)1 : (u8_t)0)

#if LWIP_NETIF_STATUS_CALLBACK
void netif_set_status_callback(struct netif *netif, netif_status_callback_fn status_callback);
#endif /* LWIP_NETIF_STATUS_CALLBACK */
#if LWIP_NETIF_REMOVE_CALLBACK
void netif_set_remove_callback(struct netif *netif, netif_status_callback_fn remove_callback);
#endif /* LWIP_NETIF_REMOVE_CALLBACK */

void netif_set_link_up(struct netif *netif);
void netif_set_link_down(struct netif *netif);
/**询问链接是否已打开*/
#define netif_is_link_up(netif) (((netif)->flags & NETIF_FLAG_LINK_UP) ? (u8_t)1 : (u8_t)0)

#if LWIP_NETIF_LINK_CALLBACK
void netif_set_link_callback(struct netif *netif, netif_status_callback_fn link_callback);
#endif /* LWIP_NETIF_LINK_CALLBACK */

#if LWIP_NETIF_HOSTNAME
/**@ingroup netif*/
#define netif_set_hostname(netif, name) do { if((netif) != NULL) { (netif)->hostname = name; }}while(0)
/**@ingroup netif*/
#define netif_get_hostname(netif) (((netif) != NULL) ? ((netif)->hostname) : NULL)
#endif /* LWIP_NETIF_HOSTNAME */

#if LWIP_IGMP
/**@ingroup netif*/
#define netif_set_igmp_mac_filter(netif, function) do { if((netif) != NULL) { (netif)->igmp_mac_filter = function; }}while(0)
#define netif_get_igmp_mac_filter(netif) (((netif) != NULL) ? ((netif)->igmp_mac_filter) : NULL)
#endif /* LWIP_IGMP */

#if LWIP_IPV6 && LWIP_IPV6_MLD
/**@ingroup netif*/
#define netif_set_mld_mac_filter(netif, function) do { if((netif) != NULL) { (netif)->mld_mac_filter = function; }}while(0)
#define netif_get_mld_mac_filter(netif) (((netif) != NULL) ? ((netif)->mld_mac_filter) : NULL)
#define netif_mld_mac_filter(netif, addr, action) do { if((netif) && (netif)->mld_mac_filter) { (netif)->mld_mac_filter((netif), (addr), (action)); }}while(0)
#endif /* LWIP_IPV6 && LWIP_IPV6_MLD */

#if ENABLE_LOOPBACK
err_t netif_loop_output(struct netif *netif, struct pbuf *p);
void netif_poll(struct netif *netif);
#if !LWIP_NETIF_LOOPBACK_MULTITHREADING
void netif_poll_all(void);
#endif /* !LWIP_NETIF_LOOPBACK_MULTITHREADING */
#endif /* ENABLE_LOOPBACK */

err_t netif_input(struct pbuf *p, struct netif *inp);

#if LWIP_IPV6
/**@ingroup netif_ip6*/
#define netif_ip_addr6(netif, i)  ((const ip_addr_t*)(&((netif)->ip6_addr[i])))
/**@ingroup netif_ip6*/
#define netif_ip6_addr(netif, i)  ((const ip6_addr_t*)ip_2_ip6(&((netif)->ip6_addr[i])))
void netif_ip6_addr_set(struct netif *netif, s8_t addr_idx, const ip6_addr_t *addr6);
void netif_ip6_addr_set_parts(struct netif *netif, s8_t addr_idx, u32_t i0, u32_t i1, u32_t i2, u32_t i3);
#define netif_ip6_addr_state(netif, i)  ((netif)->ip6_addr_state[i])
void netif_ip6_addr_set_state(struct netif* netif, s8_t addr_idx, u8_t state);
s8_t netif_get_ip6_addr_match(struct netif *netif, const ip6_addr_t *ip6addr);
void netif_create_ip6_linklocal_address(struct netif *netif, u8_t from_mac_48bit);
err_t netif_add_ip6_address(struct netif *netif, const ip6_addr_t *ip6addr, s8_t *chosen_idx);
#define netif_set_ip6_autoconfig_enabled(netif, action) do { if(netif) { (netif)->ip6_autoconfig_enabled = (action); }}while(0)
#if LWIP_IPV6_ADDRESS_LIFETIMES
#define netif_ip6_addr_valid_life(netif, i)  \
    (((netif) != NULL) ? ((netif)->ip6_addr_valid_life[i]) : IP6_ADDR_LIFE_STATIC)
#define netif_ip6_addr_set_valid_life(netif, i, secs) \
    do { if (netif != NULL) { (netif)->ip6_addr_valid_life[i] = (secs); }} while (0)
#define netif_ip6_addr_pref_life(netif, i)  \
    (((netif) != NULL) ? ((netif)->ip6_addr_pref_life[i]) : IP6_ADDR_LIFE_STATIC)
#define netif_ip6_addr_set_pref_life(netif, i, secs) \
    do { if (netif != NULL) { (netif)->ip6_addr_pref_life[i] = (secs); }} while (0)
#define netif_ip6_addr_isstatic(netif, i)  \
    (netif_ip6_addr_valid_life((netif), (i)) == IP6_ADDR_LIFE_STATIC)
#else /* !LWIP_IPV6_ADDRESS_LIFETIMES */
#define netif_ip6_addr_isstatic(netif, i)  (1) /* 所有地址都是静态的*/
#endif /* !LWIP_IPV6_ADDRESS_LIFETIMES */
#if LWIP_ND6_ALLOW_RA_UPDATES
#define netif_mtu6(netif) ((netif)->mtu6)
#else /* LWIP_ND6_ALLOW_RA_UPDATES */
#define netif_mtu6(netif) ((netif)->mtu)
#endif /* LWIP_ND6_ALLOW_RA_UPDATES */
#endif /* LWIP_IPV6 */

#if LWIP_NETIF_USE_HINTS
#define NETIF_SET_HINTS(netif, netifhint)  (netif)->hints = (netifhint)
#define NETIF_RESET_HINTS(netif)      (netif)->hints = NULL
#else /* LWIP_NETIF_USE_HINTS */
#define NETIF_SET_HINTS(netif, netifhint)
#define NETIF_RESET_HINTS(netif)
#endif /* LWIP_NETIF_USE_HINTS */

u8_t netif_name_to_index(const char *name);
char * netif_index_to_name(u8_t idx, char *name);
struct netif* netif_get_by_index(u8_t idx);

/* 根据RFC 3493第4节，接口索引始终从1开始，num从0开始（内部索引为0..254）*/
#define netif_get_index(netif)      ((u8_t)((netif)->num + 1))
#define NETIF_NO_INDEX              (0)

/**
 * @ingroup netif扩展netif状态回调（NSC）原因标志。未来可能会延长！
 */
typedef u16_t netif_nsc_reason_t;

/* 仅用于初始化*/
#define LWIP_NSC_NONE                     0x0000
/**添加netif。参数：NULL。添加netif后调用。*/
#define LWIP_NSC_NETIF_ADDED              0x0001
/**netif被移除。参数：NULL。在删除netif之前调用。*/
#define LWIP_NSC_NETIF_REMOVED            0x0002
/**链接已更改*/
#define LWIP_NSC_LINK_CHANGED             0x0004
/**netif管理状态已更改。\n up被称为netif设置后。\n down被称为netif实际设置之前。*/
#define LWIP_NSC_STATUS_CHANGED           0x0008
/**IPv4地址已更改*/
#define LWIP_NSC_IPV4_ADDRESS_CHANGED     0x0010
/**IPv4网关已更改*/
#define LWIP_NSC_IPV4_GATEWAY_CHANGED     0x0020
/**IPv4网络掩码已更改*/
#define LWIP_NSC_IPV4_NETMASK_CHANGED     0x0040
/**已应用IPv4地址/网关/网络掩码更改后调用*/
#define LWIP_NSC_IPV4_SETTINGS_CHANGED    0x0080
/**已添加IPv6地址*/
#define LWIP_NSC_IPV6_SET                 0x0100
/**IPv6地址状态已更改*/
#define LWIP_NSC_IPV6_ADDR_STATE_CHANGED  0x0200

/** @ingroup netif参数提供给netif_ext_callback_fn。
 */
typedef union
{
  /**LWIP_NSC_LINK_CHANGED回调的参数*/
  struct link_changed_s
  {
    /**1：向上；0：向下*/
    u8_t state;
  } link_changed;
  /**LWIP_NSC_STATUS_CHANGED回调的参数*/
  struct status_changed_s
  {
    /**1：向上；0：向下*/
    u8_t state;
  } status_changed;
  /**LWIP_NSC_IPV4_ADDRESS_CHANGED的参数*/
  struct ipv4_changed_s
  {
    /**旧IPv4地址*/
    const ip_addr_t* old_address;
    const ip_addr_t* old_netmask;
    const ip_addr_t* old_gw;
  } ipv4_changed;
  /**LWIP_NSC_IPV6_SET回调的参数*/
  struct ipv6_set_s
  {
    /**已更改IPv6地址的索引*/
    s8_t addr_index;
    /**旧IPv6地址*/
    const ip_addr_t* old_address;
  } ipv6_set;
  /**LWIP_NSC_IPV6_ADDR_STATE_CHANGED回调的参数*/
  struct ipv6_addr_state_changed_s
  {
    /**受影响IPv6地址的索引*/
    s8_t addr_index;
    /**旧IPv6地址状态*/
    u8_t old_state;
    /**受影响的IPv6地址*/
    const ip_addr_t* address;
  } ipv6_addr_state_changed;
} netif_ext_callback_args_t;

/**
 * @ingroup netif函数用于扩展netif状态回调注意：在解析原因参数时，请记住，将来可能会添加更多原因！
 * @param netif 受变化影响的netif
 * @param reason 变更原因
 * @param args 取决于原因，请参见原因描述
 */
typedef void (*netif_ext_callback_fn)(struct netif* netif, netif_nsc_reason_t reason, const netif_ext_callback_args_t* args);

#if LWIP_NETIF_EXT_STATUS_CALLBACK
struct netif_ext_callback;
typedef struct netif_ext_callback
{
  netif_ext_callback_fn callback_fn;
  struct netif_ext_callback* next;
} netif_ext_callback_t;

#define NETIF_DECLARE_EXT_CALLBACK(name) static netif_ext_callback_t name;
void netif_add_ext_callback(netif_ext_callback_t* callback, netif_ext_callback_fn fn);
void netif_remove_ext_callback(netif_ext_callback_t* callback);
void netif_invoke_ext_callback(struct netif* netif, netif_nsc_reason_t reason, const netif_ext_callback_args_t* args);
#else
#define NETIF_DECLARE_EXT_CALLBACK(name)
#define netif_add_ext_callback(callback, fn)
#define netif_remove_ext_callback(callback)
#define netif_invoke_ext_callback(netif, reason, args)
#endif

#ifdef __cplusplus
}
#endif

#endif /* LWIP_HDR_NETIF_H */

