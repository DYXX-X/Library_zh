/**
 * @file 用于为MIB2实现netifs和statics的SNMP支持API
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
 * 作者：Dirk Ziegelmeier<dziegel@gmx.de>
 *
 */
#ifndef LWIP_HDR_SNMP_H
#define LWIP_HDR_SNMP_H

#include "lwip/opt.h"
#include "lwip/ip_addr.h"

#ifdef __cplusplus
extern "C" {
#endif

struct udp_pcb;
struct netif;

/**
 * @defgroup netif_mib2 mib2统计
 * @ingroup netif语言
 */

/* MIB2统计功能*/
#if MIB2_STATS  /* 如果未配置为在lwipots中使用，请不要构建。小时*/
/**
 * @ingroup netif_mib2
 * @see RFC1213，“MIB-II，6.定义”
 */
enum snmp_ifType {
  snmp_ifType_other=1,                /* 无以下内容*/
  snmp_ifType_regular1822,
  snmp_ifType_hdh1822,
  snmp_ifType_ddn_x25,
  snmp_ifType_rfc877_x25,
  snmp_ifType_ethernet_csmacd,
  snmp_ifType_iso88023_csmacd,
  snmp_ifType_iso88024_tokenBus,
  snmp_ifType_iso88025_tokenRing,
  snmp_ifType_iso88026_man,
  snmp_ifType_starLan,
  snmp_ifType_proteon_10Mbit,
  snmp_ifType_proteon_80Mbit,
  snmp_ifType_hyperchannel,
  snmp_ifType_fddi,
  snmp_ifType_lapb,
  snmp_ifType_sdlc,
  snmp_ifType_ds1,                    /* T-1 */
  snmp_ifType_e1,                     /* T-1的欧洲等价物*/
  snmp_ifType_basicISDN,
  snmp_ifType_primaryISDN,            /* 专有序列号*/
  snmp_ifType_propPointToPointSerial,
  snmp_ifType_ppp,
  snmp_ifType_softwareLoopback,
  snmp_ifType_eon,                    /* IP上的CLNP[11]*/
  snmp_ifType_ethernet_3Mbit,
  snmp_ifType_nsip,                   /* IP上的XNS*/
  snmp_ifType_slip,                   /* 通用SLIP*/
  snmp_ifType_ultra,                  /* ULTRA技术*/
  snmp_ifType_ds3,                    /* T-3 */
  snmp_ifType_sip,                    /* SMDS */
  snmp_ifType_frame_relay
};

/**此宏的精度为~49天，因为sys_now返回u32_t\#如果你想要490天，就定义你自己。*/
#ifndef MIB2_COPY_SYSUPTIME_TO
#define MIB2_COPY_SYSUPTIME_TO(ptrToVal) (*(ptrToVal) = (sys_now() / 10))
#endif

/**
 * @ingroup netif_mib2 SNMP mib2统计信息的增量统计信息成员（结构stats_mib2_netif_ctrs）
 */
#define MIB2_STATS_NETIF_INC(n, x)      do { ++(n)->mib2_counters.x; } while(0)
/**
 * @ingroup netif_mib2向SNMP mib2统计信息（结构stats_mib2_netif_ctrs）的统计信息成员添加值
 */
#define MIB2_STATS_NETIF_ADD(n, x, val) do { (n)->mib2_counters.x += (val); } while(0)

/**
 * @ingroup netif_mib2初始化netif中的mib2统计计数器
 * @param netif Netif初始化
 * @param type enum@ref snmp_ifType之一
 * @param speed 此处的链接速度（单位：位/秒）
 */
#define MIB2_INIT_NETIF(netif, type, speed) do { \
  (netif)->link_type = (type);  \
  (netif)->link_speed = (speed);\
  (netif)->ts = 0;              \
  (netif)->mib2_counters.ifinoctets = 0;      \
  (netif)->mib2_counters.ifinucastpkts = 0;   \
  (netif)->mib2_counters.ifinnucastpkts = 0;  \
  (netif)->mib2_counters.ifindiscards = 0;    \
  (netif)->mib2_counters.ifinerrors = 0;    \
  (netif)->mib2_counters.ifinunknownprotos = 0;    \
  (netif)->mib2_counters.ifoutoctets = 0;     \
  (netif)->mib2_counters.ifoutucastpkts = 0;  \
  (netif)->mib2_counters.ifoutnucastpkts = 0; \
  (netif)->mib2_counters.ifoutdiscards = 0; \
  (netif)->mib2_counters.ifouterrors = 0; } while(0)
#else /* MIB2_STATS */
#ifndef MIB2_COPY_SYSUPTIME_TO
#define MIB2_COPY_SYSUPTIME_TO(ptrToVal)
#endif
#define MIB2_INIT_NETIF(netif, type, speed)
#define MIB2_STATS_NETIF_INC(n, x)
#define MIB2_STATS_NETIF_ADD(n, x, val)
#endif /* MIB2_STATS */

/* LWIP MIB2回调*/
#if LWIP_MIB2_CALLBACKS /* 如果未配置为在lwipots中使用，请不要构建。小时*/
/* 网络接口*/
void mib2_netif_added(struct netif *ni);
void mib2_netif_removed(struct netif *ni);

#if LWIP_IPV4 && LWIP_ARP
/* ARP（用于atTable和ipNetToMediaTable）*/
void mib2_add_arp_entry(struct netif *ni, ip4_addr_t *ip);
void mib2_remove_arp_entry(struct netif *ni, ip4_addr_t *ip);
#else /* LWIP_IPV4 && LWIP_ARP */
#define mib2_add_arp_entry(ni,ip)
#define mib2_remove_arp_entry(ni,ip)
#endif /* LWIP_IPV4 && LWIP_ARP */

/* IP */
#if LWIP_IPV4
void mib2_add_ip4(struct netif *ni);
void mib2_remove_ip4(struct netif *ni);
void mib2_add_route_ip4(u8_t dflt, struct netif *ni);
void mib2_remove_route_ip4(u8_t dflt, struct netif *ni);
#endif /* LWIP_IPV4 */

/* UDP */
#if LWIP_UDP
void mib2_udp_bind(struct udp_pcb *pcb);
void mib2_udp_unbind(struct udp_pcb *pcb);
#endif /* LWIP_UDP */

#else /* LWIP_MIB2_CALLBACKS */
/* LWIP_MIB2_CALLBACKS支持不可用*/
/* 将所有内容定义为空*/

/* 网络接口*/
#define mib2_netif_added(ni)
#define mib2_netif_removed(ni)

/* ARP */
#define mib2_add_arp_entry(ni,ip)
#define mib2_remove_arp_entry(ni,ip)

/* IP */
#define mib2_add_ip4(ni)
#define mib2_remove_ip4(ni)
#define mib2_add_route_ip4(dflt, ni)
#define mib2_remove_route_ip4(dflt, ni)

/* UDP */
#define mib2_udp_bind(pcb)
#define mib2_udp_unbind(pcb)
#endif /* LWIP_MIB2_CALLBACKS */

/* 仅出于源代码兼容性的原因，可以删除（不在内部使用）*/
#define NETIF_INIT_SNMP                MIB2_INIT_NETIF
#define snmp_add_ifinoctets(ni,value)  MIB2_STATS_NETIF_ADD(ni, ifinoctets, value)
#define snmp_inc_ifinucastpkts(ni)     MIB2_STATS_NETIF_INC(ni, ifinucastpkts)
#define snmp_inc_ifinnucastpkts(ni)    MIB2_STATS_NETIF_INC(ni, ifinnucastpkts)
#define snmp_inc_ifindiscards(ni)      MIB2_STATS_NETIF_INC(ni, ifindiscards)
#define snmp_inc_ifinerrors(ni)        MIB2_STATS_NETIF_INC(ni, ifinerrors)
#define snmp_inc_ifinunknownprotos(ni) MIB2_STATS_NETIF_INC(ni, ifinunknownprotos)
#define snmp_add_ifoutoctets(ni,value) MIB2_STATS_NETIF_ADD(ni, ifoutoctets, value)
#define snmp_inc_ifoutucastpkts(ni)    MIB2_STATS_NETIF_INC(ni, ifoutucastpkts)
#define snmp_inc_ifoutnucastpkts(ni)   MIB2_STATS_NETIF_INC(ni, ifoutnucastpkts)
#define snmp_inc_ifoutdiscards(ni)     MIB2_STATS_NETIF_INC(ni, ifoutdiscards)
#define snmp_inc_ifouterrors(ni)       MIB2_STATS_NETIF_INC(ni, ifouterrors)

#ifdef __cplusplus
}
#endif

#endif /* LWIP_HDR_SNMP_H */

