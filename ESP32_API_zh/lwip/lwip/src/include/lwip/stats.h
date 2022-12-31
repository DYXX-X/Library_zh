/**
 * @file 统计API（从TCPIP线程使用）
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
#ifndef LWIP_HDR_STATS_H
#define LWIP_HDR_STATS_H

#include "lwip/opt.h"

#include "lwip/mem.h"
#include "lwip/memp.h"

#ifdef __cplusplus
extern "C" {
#endif

#if LWIP_STATS

#ifndef LWIP_STATS_LARGE
#define LWIP_STATS_LARGE 0
#endif

#if LWIP_STATS_LARGE
#define STAT_COUNTER     u32_t
#define STAT_COUNTER_F   U32_F
#else
#define STAT_COUNTER     u16_t
#define STAT_COUNTER_F   U16_F
#endif

/**与协议相关的统计信息*/
struct stats_proto {
  STAT_COUNTER xmit;             /* 传输的数据包。*/
  STAT_COUNTER recv;             /* 收到的数据包。*/
  STAT_COUNTER fw;               /* 转发的数据包。*/
  STAT_COUNTER drop;             /* 丢弃的数据包。*/
  STAT_COUNTER chkerr;           /* 校验和错误。*/
  STAT_COUNTER lenerr;           /* 长度错误无效。*/
  STAT_COUNTER memerr;           /* 内存不足错误。*/
  STAT_COUNTER rterr;            /* 路由错误。*/
  STAT_COUNTER proterr;          /* 协议错误。*/
  STAT_COUNTER opterr;           /* 选项错误。*/
  STAT_COUNTER err;              /* 其他错误。*/
  STAT_COUNTER cachehit;
};

/**IGMP统计信息*/
struct stats_igmp {
  STAT_COUNTER xmit;             /* 传输的数据包。*/
  STAT_COUNTER recv;             /* 收到的数据包。*/
  STAT_COUNTER drop;             /* 丢弃的数据包。*/
  STAT_COUNTER chkerr;           /* 校验和错误。*/
  STAT_COUNTER lenerr;           /* 长度错误无效。*/
  STAT_COUNTER memerr;           /* 内存不足错误。*/
  STAT_COUNTER proterr;          /* 协议错误。*/
  STAT_COUNTER rx_v1;            /* 收到v1帧。*/
  STAT_COUNTER rx_group;         /* 收到特定于组的查询。*/
  STAT_COUNTER rx_general;       /* 收到一般查询。*/
  STAT_COUNTER rx_report;        /* 收到报告。*/
  STAT_COUNTER tx_join;          /* 已发送联接。*/
  STAT_COUNTER tx_leave;         /* 已发送树叶。*/
  STAT_COUNTER tx_report;        /* 已发送报告。*/
};

/**内存统计信息*/
struct stats_mem {
#if defined(LWIP_DEBUG) || LWIP_STATS_DISPLAY
  const char *name;
#endif /* 已定义（LWIP_DEBUG）||LWIP_STATS_DISPLAY*/
  STAT_COUNTER err;
  mem_size_t avail;
  mem_size_t used;
  mem_size_t max;
  STAT_COUNTER illegal;
};

/**系统元素统计信息*/
struct stats_syselem {
  STAT_COUNTER used;
  STAT_COUNTER max;
  STAT_COUNTER err;
};

/**系统统计信息*/
struct stats_sys {
  struct stats_syselem sem;
  struct stats_syselem mutex;
  struct stats_syselem mbox;
};

/**SNMP MIB2统计信息*/
struct stats_mib2 {
  /* IP */
  u32_t ipinhdrerrors;
  u32_t ipinaddrerrors;
  u32_t ipinunknownprotos;
  u32_t ipindiscards;
  u32_t ipindelivers;
  u32_t ipoutrequests;
  u32_t ipoutdiscards;
  u32_t ipoutnoroutes;
  u32_t ipreasmoks;
  u32_t ipreasmfails;
  u32_t ipfragoks;
  u32_t ipfragfails;
  u32_t ipfragcreates;
  u32_t ipreasmreqds;
  u32_t ipforwdatagrams;
  u32_t ipinreceives;

  /* TCP */
  u32_t tcpactiveopens;
  u32_t tcppassiveopens;
  u32_t tcpattemptfails;
  u32_t tcpestabresets;
  u32_t tcpoutsegs;
  u32_t tcpretranssegs;
  u32_t tcpinsegs;
  u32_t tcpinerrs;
  u32_t tcpoutrsts;

  /* UDP */
  u32_t udpindatagrams;
  u32_t udpnoports;
  u32_t udpinerrors;
  u32_t udpoutdatagrams;

  /* ICMP */
  u32_t icmpinmsgs;
  u32_t icmpinerrors;
  u32_t icmpindestunreachs;
  u32_t icmpintimeexcds;
  u32_t icmpinparmprobs;
  u32_t icmpinsrcquenchs;
  u32_t icmpinredirects;
  u32_t icmpinechos;
  u32_t icmpinechoreps;
  u32_t icmpintimestamps;
  u32_t icmpintimestampreps;
  u32_t icmpinaddrmasks;
  u32_t icmpinaddrmaskreps;
  u32_t icmpoutmsgs;
  u32_t icmpouterrors;
  u32_t icmpoutdestunreachs;
  u32_t icmpouttimeexcds;
  u32_t icmpoutechos; /* 可由用户应用程序递增（“ping”）*/
  u32_t icmpoutechoreps;
};

/**
 * @ingroup netif_mib2 SNMP mib2接口状态
 */
struct stats_mib2_netif_ctrs {
  /**接口上接收的八位字节总数，包括帧字符*/
  u32_t ifinoctets;
  /**由该子层传递到更高（子）层的数据包的数量，这些数据包未寻址到该子层的多播或广播地址*/
  u32_t ifinucastpkts;
  /**由该子层传送到较高（子）层的数据包的数量，这些数据包被寻址到该子层的多播或广播地址*/
  u32_t ifinnucastpkts;
  /**选择丢弃的入站数据包的数量，即使没有检测到错误，也无法将其传递到更高层协议。丢弃此类数据包的一个可能原因是释放缓冲区空间*/
  u32_t ifindiscards;
  /**对于面向数据包的接口，包含错误的入站数据包的数量，这些错误使其无法交付给更高层的协议。对于面向字符的或固定长度的接口，包含错误的入站传输单元的数量，使其无法交付给更高层的协议。*/
  u32_t ifinerrors;
  /**对于面向数据包的接口，由于未知或不支持的协议而被丢弃的通过接口接收的数据包的数量。对于支持协议复用的面向字符的或固定长度的接口，通过接口接收的传输单元的数量由于未知或不支持的协议而被丢弃。对于任何不支持协议复用的接口，此计数器将始终为0*/
  u32_t ifinunknownprotos;
  /**从接口传输出去的八位字节总数，包括成帧字符。*/
  u32_t ifoutoctets;
  /**高级协议请求传输的、未寻址到此子层的多播或广播地址的数据包总数，包括丢弃或未发送的数据包。*/
  u32_t ifoutucastpkts;
  /**更高级别协议请求传输的数据包总数，这些数据包寻址到此子层的多播或广播地址，包括丢弃或未发送的数据包。*/
  u32_t ifoutnucastpkts;
  /**选择丢弃的出站数据包的数量，即使没有检测到错误以阻止其传输。丢弃这种包的一个可能原因是释放缓冲区空间。*/
  u32_t ifoutdiscards;
  /**对于面向数据包的接口，由于错误而无法传输的出站数据包的数量。对于面向字符或固定长度的接口，由于错误而无法传输的出站传输单元的数量。*/
  u32_t ifouterrors;
};

/**lwIP统计信息容器*/
struct stats_ {
#if LINK_STATS
  /**链接级别*/
  struct stats_proto link;
#endif
#if ETHARP_STATS
  /** ARP */
  struct stats_proto etharp;
#endif
#if IPFRAG_STATS
  /**碎片化*/
  struct stats_proto ip_frag;
#endif
#if IP_STATS
  /** IP */
  struct stats_proto ip;
#endif
#if ICMP_STATS
  /** ICMP */
  struct stats_proto icmp;
#endif
#if IGMP_STATS
  /** IGMP */
  struct stats_igmp igmp;
#endif
#if UDP_STATS
  /** UDP */
  struct stats_proto udp;
#endif
#if TCP_STATS
  /** TCP */
  struct stats_proto tcp;
#endif
#if MEM_STATS
  /**堆*/
  struct stats_mem mem;
#endif
#if MEMP_STATS
  /**内部内存池*/
  struct stats_mem *memp[MEMP_MAX];
#endif
#if SYS_STATS
  /**系统*/
  struct stats_sys sys;
#endif
#if IP6_STATS
  /**IPv6协议*/
  struct stats_proto ip6;
#endif
#if ICMP6_STATS
  /** ICMP6 */
  struct stats_proto icmp6;
#endif
#if IP6_FRAG_STATS
  /**IPv6碎片*/
  struct stats_proto ip6_frag;
#endif
#if MLD6_STATS
  /**多播侦听器发现*/
  struct stats_igmp mld6;
#endif
#if ND6_STATS
  /**邻居发现*/
  struct stats_proto nd6;
#endif
#if MIB2_STATS
  /** SNMP MIB2 */
  struct stats_mib2 mib2;
#endif
};

/**包含lwIP内部统计信息的全局变量。将此添加到调试器的监视列表中。*/
extern struct stats_ lwip_stats;

/**初始化统计信息*/
void stats_init(void);

#define STATS_INC(x) ++lwip_stats.x
#define STATS_DEC(x) --lwip_stats.x
#define STATS_INC_USED(x, y, type) do { lwip_stats.x.used = (type)(lwip_stats.x.used + y); \
                                if (lwip_stats.x.max < lwip_stats.x.used) { \
                                    lwip_stats.x.max = lwip_stats.x.used; \
                                } \
                             } while(0)
#define STATS_GET(x) lwip_stats.x
#else /* LWIP_STATS */
#define stats_init()
#define STATS_INC(x)
#define STATS_DEC(x)
#define STATS_INC_USED(x, y, type)
#endif /* LWIP_STATS */

#if TCP_STATS
#define TCP_STATS_INC(x) STATS_INC(x)
#define TCP_STATS_DISPLAY() stats_display_proto(&lwip_stats.tcp, "TCP")
#else
#define TCP_STATS_INC(x)
#define TCP_STATS_DISPLAY()
#endif

#if UDP_STATS
#define UDP_STATS_INC(x) STATS_INC(x)
#define UDP_STATS_DISPLAY() stats_display_proto(&lwip_stats.udp, "UDP")
#else
#define UDP_STATS_INC(x)
#define UDP_STATS_DISPLAY()
#endif

#if ICMP_STATS
#define ICMP_STATS_INC(x) STATS_INC(x)
#define ICMP_STATS_DISPLAY() stats_display_proto(&lwip_stats.icmp, "ICMP")
#else
#define ICMP_STATS_INC(x)
#define ICMP_STATS_DISPLAY()
#endif

#if IGMP_STATS
#define IGMP_STATS_INC(x) STATS_INC(x)
#define IGMP_STATS_DISPLAY() stats_display_igmp(&lwip_stats.igmp, "IGMP")
#else
#define IGMP_STATS_INC(x)
#define IGMP_STATS_DISPLAY()
#endif

#if IP_STATS
#define IP_STATS_INC(x) STATS_INC(x)
#define IP_STATS_DISPLAY() stats_display_proto(&lwip_stats.ip, "IP")
#else
#define IP_STATS_INC(x)
#define IP_STATS_DISPLAY()
#endif

#if IPFRAG_STATS
#define IPFRAG_STATS_INC(x) STATS_INC(x)
#define IPFRAG_STATS_DISPLAY() stats_display_proto(&lwip_stats.ip_frag, "IP_FRAG")
#else
#define IPFRAG_STATS_INC(x)
#define IPFRAG_STATS_DISPLAY()
#endif

#if ETHARP_STATS
#define ETHARP_STATS_INC(x) STATS_INC(x)
#define ETHARP_STATS_DISPLAY() stats_display_proto(&lwip_stats.etharp, "ETHARP")
#else
#define ETHARP_STATS_INC(x)
#define ETHARP_STATS_DISPLAY()
#endif

#if LINK_STATS
#define LINK_STATS_INC(x) STATS_INC(x)
#define LINK_STATS_DISPLAY() stats_display_proto(&lwip_stats.link, "LINK")
#else
#define LINK_STATS_INC(x)
#define LINK_STATS_DISPLAY()
#endif

#if MEM_STATS
#define MEM_STATS_AVAIL(x, y) lwip_stats.mem.x = y
#define MEM_STATS_INC(x) STATS_INC(mem.x)
#define MEM_STATS_INC_USED(x, y) STATS_INC_USED(mem, y, mem_size_t)
#define MEM_STATS_DEC_USED(x, y) lwip_stats.mem.x = (mem_size_t)((lwip_stats.mem.x) - (y))
#define MEM_STATS_DISPLAY() stats_display_mem(&lwip_stats.mem, "HEAP")
#else
#define MEM_STATS_AVAIL(x, y)
#define MEM_STATS_INC(x)
#define MEM_STATS_INC_USED(x, y)
#define MEM_STATS_DEC_USED(x, y)
#define MEM_STATS_DISPLAY()
#endif

 #if MEMP_STATS
#define MEMP_STATS_DEC(x, i) STATS_DEC(memp[i]->x)
#define MEMP_STATS_DISPLAY(i) stats_display_memp(lwip_stats.memp[i], i)
#define MEMP_STATS_GET(x, i) STATS_GET(memp[i]->x)
 #else
#define MEMP_STATS_DEC(x, i)
#define MEMP_STATS_DISPLAY(i)
#define MEMP_STATS_GET(x, i) 0
#endif

#if SYS_STATS
#define SYS_STATS_INC(x) STATS_INC(sys.x)
#define SYS_STATS_DEC(x) STATS_DEC(sys.x)
#define SYS_STATS_INC_USED(x) STATS_INC_USED(sys.x, 1, STAT_COUNTER)
#define SYS_STATS_DISPLAY() stats_display_sys(&lwip_stats.sys)
#else
#define SYS_STATS_INC(x)
#define SYS_STATS_DEC(x)
#define SYS_STATS_INC_USED(x)
#define SYS_STATS_DISPLAY()
#endif

#if IP6_STATS
#define IP6_STATS_INC(x) STATS_INC(x)
#define IP6_STATS_DISPLAY() stats_display_proto(&lwip_stats.ip6, "IPv6")
#else
#define IP6_STATS_INC(x)
#define IP6_STATS_DISPLAY()
#endif

#if ICMP6_STATS
#define ICMP6_STATS_INC(x) STATS_INC(x)
#define ICMP6_STATS_DISPLAY() stats_display_proto(&lwip_stats.icmp6, "ICMPv6")
#else
#define ICMP6_STATS_INC(x)
#define ICMP6_STATS_DISPLAY()
#endif

#if IP6_FRAG_STATS
#define IP6_FRAG_STATS_INC(x) STATS_INC(x)
#define IP6_FRAG_STATS_DISPLAY() stats_display_proto(&lwip_stats.ip6_frag, "IPv6 FRAG")
#else
#define IP6_FRAG_STATS_INC(x)
#define IP6_FRAG_STATS_DISPLAY()
#endif

#if MLD6_STATS
#define MLD6_STATS_INC(x) STATS_INC(x)
#define MLD6_STATS_DISPLAY() stats_display_igmp(&lwip_stats.mld6, "MLDv1")
#else
#define MLD6_STATS_INC(x)
#define MLD6_STATS_DISPLAY()
#endif

#if ND6_STATS
#define ND6_STATS_INC(x) STATS_INC(x)
#define ND6_STATS_DISPLAY() stats_display_proto(&lwip_stats.nd6, "ND")
#else
#define ND6_STATS_INC(x)
#define ND6_STATS_DISPLAY()
#endif

#if MIB2_STATS
#define MIB2_STATS_INC(x) STATS_INC(x)
#else
#define MIB2_STATS_INC(x)
#endif

/* 统计数据的显示*/
#if LWIP_STATS_DISPLAY
void stats_display(void);
void stats_display_proto(struct stats_proto *proto, const char *name);
void stats_display_igmp(struct stats_igmp *igmp, const char *name);
void stats_display_mem(struct stats_mem *mem, const char *name);
void stats_display_memp(struct stats_mem *mem, int index);
void stats_display_sys(struct stats_sys *sys);
#else /* LWIP_STATS_DISPLAY */
#define stats_display()
#define stats_display_proto(proto, name)
#define stats_display_igmp(igmp, name)
#define stats_display_mem(mem, name)
#define stats_display_memp(mem, index)
#define stats_display_sys(sys)
#endif /* LWIP_STATS_DISPLAY */

#ifdef __cplusplus
}
#endif

#endif /* LWIP_HDR_STATS_H */

