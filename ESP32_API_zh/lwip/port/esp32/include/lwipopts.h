/*
 * SPDX文件版权所有文本：2001-2003瑞典计算机科学研究所
 *
 * SPDX许可证标识符：BSD-3-条款
 *
 * SPDX文件撰稿人：2015-2021浓缩咖啡系统（上海）有限公司
 */

#ifndef __LWIPOPTS_H__
#define __LWIPOPTS_H__

#include <stdlib.h>
#include <unistd.h>
#include <sys/fcntl.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/select.h>
#include "esp_task.h"
#include "esp_system.h"
#include "sdkconfig.h"
#include "netif/dhcp_state.h"
#include "sntp/sntp_get_set_time.h"

/* 启用所有仅限Espressif选项*/

/*
   -----------------------------------------------
   ----------平台特定锁定----------
   -----------------------------------------------
*/
/**
 * SYS_LIGHTWEIGHT_PROT==1：如果您希望在缓冲区分配、释放和内存分配和释放过程中对某些关键区域进行任务间保护。
 */
#define SYS_LIGHTWEIGHT_PROT        1

/**
 * MEMCPY：如果手头有比C库中包含的实现更快的实现，请重写此选项
 */
#define MEMCPY(dst,src,len)             memcpy(dst,src,len)

/**
 * SMEMCPY:小心忽略这个！如果长度在编译时已知并且很小，一些编译器（例如gcc）可以内联对memcpy（）的调用。
 */
#define SMEMCPY(dst,src,len)            memcpy(dst,src,len)

#define LWIP_RAND       esp_random

/*
   ------------------------------------
   ----------内存选项----------
   ------------------------------------
*/
/**
 * MEM_LIBC_MALLOC==1：使用C库提供的MALLOC/free/realloc，而不是lwip内部分配器。如果您已经使用它，可以保存代码大小。
 */
#define MEM_LIBC_MALLOC        1

/**
* MEMP_MEM_MALLOC==1：使用MEM_MALLOC/MEM_free而不是lwip池分配器。特别适用于MEM_LIBC_MALLOC，但要小心处理中断的执行速度和使用情况！
*/
#define MEMP_MEM_MALLOC                 1

/**
 * MEM_ALIGNMENT：应设置为CPU 4字节对齐方式->#define MEM_ALIGNMENT 4 2字节对齐方式->#define MEM_ALIGNENT 2
 */
#define MEM_ALIGNMENT           4

/*
   ------------------------------------------------
   ----------内部内存池大小----------
   ------------------------------------------------
*/

/**
 * MEMP_NUM_NETCONN：结构NETCONN的数量。（仅当使用顺序API（如API_lib.c）时才需要）
 */
#define MEMP_NUM_NETCONN                CONFIG_LWIP_MAX_SOCKETS

/**
 * MEMP_NUM_RAW_PCB：原始连接PCB的数量（需要LWIP_RAW选项）
 */
#define MEMP_NUM_RAW_PCB                CONFIG_LWIP_MAX_RAW_PCBS

/**
 * MEMP_NUM_TCP_PCB：同时活动的TCP连接数。（需要LWIP_TCP选项）
 */
#define MEMP_NUM_TCP_PCB                CONFIG_LWIP_MAX_ACTIVE_TCP

/**
 * MEMP_NUM_TCP_PCB_LISTEN：侦听TCP连接的数量。（需要LWIP_TCP选项）
 */
#define MEMP_NUM_TCP_PCB_LISTEN         CONFIG_LWIP_MAX_LISTENING_TCP

/**
 * MEMP_NUM_UDP_PCB：UDP协议控制块的数量。每个活动UDP“连接”一个。（需要LWIP_UDP选项）
 */
#define MEMP_NUM_UDP_PCB                CONFIG_LWIP_MAX_UDP_PCBS

/*
   --------------------------------
   ----------ARP选项-------
   --------------------------------
*/
/**
 * ARP_QUEUEING==1：在硬件地址解析期间，多个传出数据包被排队。默认情况下，每个IP地址只排队最近的数据包。这对于大多数协议来说已经足够了，并且主要减少了TCP连接启动时间。如果您知道应用程序在一行中向不在ARP缓存中的IP地址发送了多个数据包，请将此值设置为1。
 */
#define ARP_QUEUEING                    1

/*
   --------------------------------
   ----------IP选项----------
   --------------------------------
*/
/**
 * IP_REASSEMBLY==1：重新组装传入的分段IP4数据包。注意，此选项不影响传出数据包大小，可通过IP_FRAG控制。
 */
#define IP_REASSEMBLY                   CONFIG_LWIP_IP4_REASSEMBLY

/**
 * LWIP_IPV6_REASS==1：重新组装碎片化的传入IP6数据包。请注意，此选项不影响传出数据包大小，可通过LWIP_IPV6_FRAG控制。
 */
#define LWIP_IPV6_REASS                 CONFIG_LWIP_IP6_REASSEMBLY

/**
 * IP_FRAG==1：如果传出IP4数据包的大小超过MTU，则将其分段。请注意，此选项不影响传入数据包大小，可以通过IP_REASSEMBLY控制。
 */
#define IP_FRAG                         CONFIG_LWIP_IP4_FRAG

/**
 * LWIP_IPV6_FRAG==1：如果传出的IP6数据包的大小超过MTU，则将其分段。请注意，此选项不影响传入数据包大小，可以通过IP_REASSEMBLY控制。
 */
#define LWIP_IPV6_FRAG                  CONFIG_LWIP_IP6_FRAG

/**
 * IP_REASS_MAXAGE：碎片化IP数据包等待所有碎片到达的最长时间（以IP_TMR_INTERVAL的倍数表示，通常为秒）。如果此时不是所有碎片都到达，则丢弃整个数据包。
 */
#define IP_REASS_MAXAGE                 3

/**
 * IP_REASS_MAX_PBUFS：等待重新组装的pbuf的最大总数。由于接收到的PBUF已入队，请确保配置PBUF_POOL_SIZE>IP_REASS_MAX_pbufs，以便堆栈仍然能够接收数据包，即使已入队进行重组的碎片数量达到最大！
 */
#define IP_REASS_MAX_PBUFS              10

/**
 * IP_FORWARD==1：允许跨网络接口转发IP数据包。如果要在只有一个网络接口的设备上运行lwIP，请将其定义为0。
 */
#define IP_FORWARD                      CONFIG_LWIP_IP_FORWARD

/**
 * IP_NAPT==1:启用IPv4网络地址和端口转换。注意，需要在系统配置中启用CONFIG_LWIP_IP_FORWARD和CONFIG_LDAP_L2_TO_L3_COPY选项，NAPT才能在ESP平台上工作
 */
#define IP_NAPT                         CONFIG_LWIP_IPV4_NAPT

/*
   ----------------------------------
   ----------ICMP选项----------
   ----------------------------------
*/
#define LWIP_ICMP  CONFIG_LWIP_ICMP

#define LWIP_BROADCAST_PING CONFIG_LWIP_BROADCAST_PING

#define LWIP_MULTICAST_PING CONFIG_LWIP_MULTICAST_PING

/*
   ---------------------------------
   ----------RAW选项----------
   ---------------------------------
*/
/**
 * LWIP_RAW==1：使应用程序层能够挂接到IP层本身。
 */
#define LWIP_RAW                        1

/*
   ----------------------------------
   ----------DHCP选项----------
   ----------------------------------
*/
/**
 * LWIP_DHCP==1：启用DHCP模块。
 */
#define LWIP_DHCP                       1

#define DHCP_MAXRTX                     0

/**
 * DHCP_DOES_ARP_CHECK==1：对提供的地址执行ARP检查。
 */
#define DHCP_DOES_ARP_CHECK             CONFIG_LWIP_DHCP_DOES_ARP_CHECK

/**
 * LWIP_DHCP_DISABLE_CLIENT_ID==1:不向DHCP数据包添加选项61（客户端ID）
 */
#define ESP_DHCP_DISABLE_CLIENT_ID      CONFIG_LWIP_DHCP_DISABLE_CLIENT_ID

/**
 * CONFIG_LWIP_DDHCP_RESTORE_LAST_IP==1:从DHCP服务器获得的最后一个有效IP地址在重置/通电后恢复。
 */
#if CONFIG_LWIP_DHCP_RESTORE_LAST_IP

#define LWIP_DHCP_IP_ADDR_RESTORE()     dhcp_ip_addr_restore(netif)
#define LWIP_DHCP_IP_ADDR_STORE()       dhcp_ip_addr_store(netif)
#define LWIP_DHCP_IP_ADDR_ERASE(esp_netif)       dhcp_ip_addr_erase(esp_netif)

#endif

/**
 * CONFIG_LWIP_DDHCP_OPTIONS_LEN：传出DHCP选项消息的总长度。如果您有许多选项，并且选项值太长，可以根据您的要求配置长度
 */
#define DHCP_OPTIONS_LEN                CONFIG_LWIP_DHCP_OPTIONS_LEN

/**
 * LWIP_DHCP_DISABLE_VENDOR_CLASS_ID==1：不向DHCP数据包添加选项60（供应商类别标识符）
 */
#define ESP_DHCP_DISABLE_VENDOR_CLASS_IDENTIFIER       CONFIG_LWIP_DHCP_DISABLE_VENDOR_CLASS_ID

/*
   ------------------------------------
   ----------AUTOIP选项----------
   ------------------------------------
*/
#ifdef CONFIG_LWIP_AUTOIP
#define LWIP_AUTOIP                     1

/**
* LWIP_DHCP_AUTOIP_COP==1：允许同时在同一接口上启用DHCP和AUTOIP。
*/
#define LWIP_DHCP_AUTOIP_COOP           1

/**
* LWIP_DHCP_AUTOIP_COP_TRIES：设置为在返回AUTOIP之前应发送的DHCP DISCOVER探测数。这可以设置为低至1，以快速获得AutoIP地址，但当DHCP覆盖AutoIP时，您应该准备好处理更改的IP地址。
*/
#define LWIP_DHCP_AUTOIP_COOP_TRIES     CONFIG_LWIP_AUTOIP_TRIES

#define LWIP_AUTOIP_MAX_CONFLICTS CONFIG_LWIP_AUTOIP_MAX_CONFLICTS

#define LWIP_AUTOIP_RATE_LIMIT_INTERVAL CONFIG_LWIP_AUTOIP_RATE_LIMIT_INTERVAL

#endif /* CONFIG_LWIP_AUTOIP */

/*
   ----------------------------------
   ----------SNMP选项----------
   ----------------------------------
*/
/*
   ----------------------------------
   ----------IGMP选项----------
   ----------------------------------
*/
/**
 * LWIP_IGMP==1：打开IGMP模块。
 */
#define LWIP_IGMP                       1

/*
   ----------------------------------
   ----------DNS选项-----------
   ----------------------------------
*/
/**
 * LWIP_DNS==1:打开DNS模块。UDP必须可用于DNS传输。
 */
#define LWIP_DNS                        1

#define DNS_MAX_SERVERS                 3
#define DNS_FALLBACK_SERVER_INDEX        (DNS_MAX_SERVERS - 1)

/*
   ---------------------------------
   ----------UDP选项----------
   ---------------------------------
*/
/*
   ---------------------------------
   ----------TCP选项----------
   ---------------------------------
*/


/**
 * TCP_QUEUE_OOSEQ==1:TCP将对无序到达的段进行排队。如果设备内存不足，则定义为0。
 */
#define TCP_QUEUE_OOSEQ                 CONFIG_LWIP_TCP_QUEUE_OOSEQ

/**
 * LWIP_TCP_SACK_OUT==1:TCP将支持发送选择性确认（SACK）。
 */
#define LWIP_TCP_SACK_OUT               CONFIG_LWIP_TCP_SACK_OUT

/**
 * ESP_TCP_KEEP_CONNECTION_WHEN_IP_CHANGES==1：当IP发生更改时，保持TCP连接：192.168.0.2->0.0.0.0->192.168.0.2或192.168.0.2->.0.0.0
 */

#define ESP_TCP_KEEP_CONNECTION_WHEN_IP_CHANGES  CONFIG_LWIP_TCP_KEEP_CONNECTION_WHEN_IP_CHANGES
/*
 *     LWIP_EVENT_API==1：用户定义LWIP_tcp_EVENT（）以接收系统中发生的所有事件（接受、发送等）。LWIP_CALLBACK_API==1：直接为事件调用PCB回调函数。这是默认设置。
*/
#define TCP_MSS                         CONFIG_LWIP_TCP_MSS

/**
 * TCP_TMR_INVAL:TCP计时器间隔
 */
#define TCP_TMR_INTERVAL                CONFIG_LWIP_TCP_TMR_INTERVAL

/**
 * TCP_MSL：最大段生存时间（毫秒）
 */
#define TCP_MSL                         CONFIG_LWIP_TCP_MSL

/**
 * TCP_MAXRTX：数据段的最大重传次数。
 */
#define TCP_MAXRTX                      CONFIG_LWIP_TCP_MAXRTX

/**
 * TCP_SYNMAXRTX：SYN段的最大重传次数。
 */
#define TCP_SYNMAXRTX                   CONFIG_LWIP_TCP_SYNMAXRTX

/**
 * TCP_LISTEN_BACKLOG：为TCP侦听pcb启用BACKLOG选项。
 */
#define TCP_LISTEN_BACKLOG              1


/**
 * TCP_OVERSIZE：TCP_write可以提前分配的最大字节数
 */
#ifdef CONFIG_LWIP_TCP_OVERSIZE_MSS
#define TCP_OVERSIZE                    TCP_MSS
#endif
#ifdef CONFIG_LWIP_TCP_OVERSIZE_QUARTER_MSS
#define TCP_OVERSIZE                    (TCP_MSS/4)
#endif
#ifdef CONFIG_LWIP_TCP_OVERSIZE_DISABLE
#define TCP_OVERSIZE                    0
#endif
#ifndef TCP_OVERSIZE
#error "One of CONFIG_TCP_OVERSIZE_xxx options should be set by sdkconfig"
#endif

/**
 * LWIP_WND_SCALE和TCP_RCV_SCALE：将LWIP_WND _SCALE设置为1以启用窗口缩放。将TCP_RCV_SCALE设置为所需的缩放因子（移位计数在[0..14]范围内）。当启用LWIP_WND_SCALE但TCP_RCV_SCALE为0时，我们可以使用大的发送窗口，而只有小的接收窗口。
 */
#ifdef CONFIG_LWIP_WND_SCALE
#define LWIP_WND_SCALE                  1
#define TCP_RCV_SCALE                   CONFIG_LWIP_TCP_RCV_SCALE
#endif

/**
 * LWIP_TCP_RTO_TIME：TCP实时。默认值为3秒。
 */
#define LWIP_TCP_RTO_TIME             CONFIG_LWIP_TCP_RTO_TIME

/*
   ----------------------------------
   ----------Pbuf选项----------
   ----------------------------------
*/

/*
   ------------------------------------------------
   ----------网络接口选项----------
   ------------------------------------------------
*/

/**
 * LWIP_NETIF_HOSTNAME==1：将DHCP_OPTION_HOSTNNAME与NETIF的主机名字段一起使用。
 */
#define LWIP_NETIF_HOSTNAME             1

/**
 * LWIP_NETIF_TX_SINGLE_BUF：如果设置为1，LWIP将尝试将所有要发送的数据放入一个PBUF中。这是为了与不支持分散聚集的启用DMA的MAC兼容。请注意，在传输之前，这可能涉及CPU内存，如果没有此标志，则不需要此内存！只有在需要时才使用此选项！
 *
 * @todo: TCP和IP碎片不适用于此，但：
 */
#define LWIP_NETIF_TX_SINGLE_PBUF             1

/**
 * LWIP_NETIF_API==1：在LWIP中启用标准POSIX API。
 */
#define LWIP_NETIF_API                      CONFIG_LWIP_NETIF_API

#define LWIP_NETIF_STATUS_CALLBACK      CONFIG_LWIP_NETIF_STATUS_CALLBACK

/*
   ------------------------------------
   ----------LOOPIF选项----------
   ------------------------------------
*/
#ifdef CONFIG_LWIP_NETIF_LOOPBACK
/**
 * LWIP_NETIF_LOPBACK==1：支持发送目标IP地址等于NETIF IP地址的数据包，并将其循环到堆栈中。
 */
#define LWIP_NETIF_LOOPBACK             1

/**
 * LWIP_LOOPBACK_MAX_PBUFS：每个netif的环回发送队列中pbuf的最大数量（0=禁用）
 */
#define LWIP_LOOPBACK_MAX_PBUFS         CONFIG_LWIP_LOOPBACK_MAX_PBUFS
#endif

/*
   ------------------------------------
   ----------SLIPIF选项----------
   ------------------------------------
*/

#ifdef CONFIG_LWIP_SLIP_SUPPORT

/**
 * 启用来自ISR功能的SLIP接收并禁用Rx线程
 *
 * 这是lwIP SLIP接口唯一支持的模式，因此
 * -传入的数据包排入pbufs
 * -没有从lwIP创建线程，这意味着应用程序负责从IO驱动程序读取数据并将其提供给slip接口
 */
#define SLIP_RX_FROM_ISR                 1
#define SLIP_USE_RX_THREAD               0

/**
 * PPP_DEBUG：启用PPP调试。
 */
#define SLIP_DEBUG_ON                    CONFIG_LWIP_SLIP_DEBUG_ON

#if SLIP_DEBUG_ON
#define SLIP_DEBUG                       LWIP_DBG_ON
#else
#define SLIP_DEBUG                       LWIP_DBG_OFF
#endif


#endif

/*
   ------------------------------------
   ----------线程选项----------
   ------------------------------------
*/
/**
 * TCPIP_THREAD_NAME:分配给主TCPIP线程的名称。
 */
#define TCPIP_THREAD_NAME              "tiT"

/**
 * TCPIP_THREAD_STACKSIZE:主TCPIP线程使用的堆栈大小。堆栈大小值本身依赖于平台，但在创建线程时会传递给sys_thread_new（）。
 */
#define TCPIP_THREAD_STACKSIZE          ESP_TASK_TCPIP_STACK

/**
 * TCPIP_THREAD_PRIO：分配给主TCPIP线程的优先级。优先级值本身依赖于平台，但在创建线程时会传递给sys_thread_new（）。
 */
#define TCPIP_THREAD_PRIO               ESP_TASK_TCPIP_PRIO

/**
 * TCPIP_MBOX_SIZE:TCPIP线程消息的邮箱大小队列大小值本身取决于平台，但在调用TCPIP_init时传递给sys_MBOX_new（）。
 */
#define TCPIP_MBOX_SIZE                 CONFIG_LWIP_TCPIP_RECVMBOX_SIZE

/**
 * DEFAULT_UDP_RECVMBOX_SIZE:NETCONN_UDP上传入数据包的邮箱大小。队列大小值本身依赖于平台，但在创建recvmbox时会传递给sys_mbox_new（）。
 */
#define DEFAULT_UDP_RECVMBOX_SIZE       CONFIG_LWIP_UDP_RECVMBOX_SIZE

/**
 * DEFAULT_TCP_RECVMBOX_SIZE:NETCONN_TCP上传入数据包的邮箱大小。队列大小值本身依赖于平台，但在创建recvmbox时会传递给sys_mbox_new（）。
 */
#define DEFAULT_TCP_RECVMBOX_SIZE       CONFIG_LWIP_TCP_RECVMBOX_SIZE

/**
 * DEFAULT_ACCEPTMBOX_SIZE：传入连接的邮箱大小。队列大小值本身依赖于平台，但在创建acceptbox时传递给sys_mbox_new（）。
 */
#define DEFAULT_ACCEPTMBOX_SIZE         6

/**
 * DEFAULT_THREAD_STACKSIZE：任何其他lwIP线程使用的堆栈大小。堆栈大小值本身依赖于平台，但在创建线程时会传递给sys_thread_new（）。
 */
#define DEFAULT_THREAD_STACKSIZE        TCPIP_THREAD_STACKSIZE

/**
 * DEFAULT_THREAD_PRIO：分配给任何其他lwIP线程的优先级。优先级值本身依赖于平台，但在创建线程时会传递给sys_thread_new（）。
 */
#define DEFAULT_THREAD_PRIO             TCPIP_THREAD_PRIO

/**
 * DEFAULT_RAW_RECVMBOX_SIZE:NETCONN_RAW上传入数据包的邮箱大小。队列大小值本身依赖于平台，但在创建recvmbox时会传递给sys_mbox_new（）。
 */
#define DEFAULT_RAW_RECVMBOX_SIZE       6

/*
   ----------------------------------------------
   ----------顺序层选项----------
   ----------------------------------------------
*/
/**
 * LWIP_TCPIP_CORE_LOCKING：（实验！）如果您不是活动的lwIP项目成员，请不要使用它
 */
#define LWIP_TCPIP_CORE_LOCKING         CONFIG_LWIP_TCPIP_CORE_LOCKING

/*
   ------------------------------------
   ----------套接字选项----------
   ------------------------------------
*/
/**
 * LWIP_SO_SNDTIMEO==1：为套接字/网络连接和SO_SNDTIMEO处理启用发送超时。
 */
#define LWIP_SO_SNDTIMEO                1

/**
 * LWIP_SO_RCVTIMEO==1：为套接字/网络连接和SO_RCVTIMEO处理启用接收超时。
 */
#define LWIP_SO_RCVTIMEO                1

/**
 * LWIP_TCP_KEEPALIVE==1：启用TCP_KEEPIDLE、TCP_KEPEINTVL和TCP_KEEP选项处理。请注意，TCP_KEEPIDLE和TCP_KEPEINTVL必须以秒为单位设置。（不需要套接字.c，并且会影响tcp.c）
 */
#define LWIP_TCP_KEEPALIVE              1

/**
 * LWIP_SO_LINGER==1：启用SO_LINGER处理。
 */
#define LWIP_SO_LINGER                  CONFIG_LWIP_SO_LINGER

/**
 * LWIP_SO_RCVBUF==1：启用SO_RCVBUF处理。
 */
#define LWIP_SO_RCVBUF                  CONFIG_LWIP_SO_RCVBUF

/**
 * SO_REUSE==1：启用SO_REUSEADDR选项。此选项通过menuconfig设置。
 */
#define SO_REUSE                        CONFIG_LWIP_SO_REUSE


/**
 * LWIP_DNS_SUPPORT_MDNS_QUERIES==1:在主机名解析中启用MDNS查询。此选项通过menuconfig设置。
 */
#define LWIP_DNS_SUPPORT_MDNS_QUERIES   CONFIG_LWIP_DNS_SUPPORT_MDNS_QUERIES
/**
 * SO_REUSE_RXTOALL==1：如果打开了SO_REUSEADDR，则将传入广播/多播数据包的副本传递给所有本地匹配。警告：如果传递到多个pcb，则为每个数据包添加一个memcpy！
 */
#define SO_REUSE_RXTOALL                CONFIG_LWIP_SO_REUSE_RXTOALL

/**
 * LWIP_NETBUF_RECVINFO==1：启用IP_PKTINFO选项。此选项通过menuconfig设置。
 */
#define LWIP_NETBUF_RECVINFO            CONFIG_LWIP_NETBUF_RECVINFO

/*
   ----------------------------------------
   ----------统计信息选项----------
   ----------------------------------------
*/

/**
 * LWIP_STATS==1:在LWIP_STATS中启用统计信息收集。
 */
#define LWIP_STATS                      CONFIG_LWIP_STATS

#if LWIP_STATS

/**
 * LWIP_STATS_DISPLAY==1：在统计输出函数中编译。
 */
#define LWIP_STATS_DISPLAY              CONFIG_LWIP_STATS
#endif


/*
   ---------------------------------
   ----------PPP选项----------
   ---------------------------------
*/

/**
 * PPP_SUPPORT==1：启用PPP。
 */
#define PPP_SUPPORT                     CONFIG_LWIP_PPP_SUPPORT

#if PPP_SUPPORT

/**
 * PPP_IPV6_SUPPORT==1：为调制解调器和lwIP堆栈之间的本地链路启用IPV6支持。一些调制解调器不支持本地链路中的IPV6寻址，唯一可用的选项是禁用IPV6地址协商。
 */
#define PPP_IPV6_SUPPORT                               CONFIG_LWIP_PPP_ENABLE_IPV6

/**
 * PPP_NOTIFY_PHASE==1：支持PPP通知阶段。
 */
#define PPP_NOTIFY_PHASE                CONFIG_LWIP_PPP_NOTIFY_PHASE_SUPPORT

/**
 * PAP_SUPPORT==1：支持PAP。
 */
#define PAP_SUPPORT                     CONFIG_LWIP_PPP_PAP_SUPPORT

/**
 * CHAP_SUPPORT==1：支持CHAP。
 */
#define CHAP_SUPPORT                    CONFIG_LWIP_PPP_CHAP_SUPPORT

/**
 * MSCHAP_SUPPORT==1：支持MSCHAP。
 */
#define MSCHAP_SUPPORT                  CONFIG_LWIP_PPP_MSCHAP_SUPPORT

/**
 * CCP_SUPPORT==1：支持CCP。
 */
#define MPPE_SUPPORT                    CONFIG_LWIP_PPP_MPPE_SUPPORT

/**
 * PPP_MAXIDLEFLAG：重新发送标志字符之前的最大Xmit空闲时间（毫秒）。TODO:如果PPP_MAXIDLEFLAG>0，并且在PPP_MAXDLEFLAG时间内发送了下一个包，则不会在PPP包的开头添加0x7E，但0x7E终止始终在结尾。这种行为破坏了与GSM（PPPoS）的PPP拨号。PPP包应始终以0x7E开头和结尾。
 */

#define PPP_MAXIDLEFLAG                 0

/**
 * PPP_DEBUG：启用PPP调试。
 */
#define PPP_DEBUG_ON                    CONFIG_LWIP_PPP_DEBUG_ON

#if PPP_DEBUG_ON
#define PPP_DEBUG                       LWIP_DBG_ON
#define PRINTPKT_SUPPORT                1
#define PPP_PROTOCOLNAME                1
#else
#define PPP_DEBUG                       LWIP_DBG_OFF
#endif

#endif  /* PPP SUPPORT */

/*
   ------------------------------------
   ---------LCP回声选项---------
   ------------------------------------
*/
#if CONFIG_LWIP_ENABLE_LCP_ECHO
/**
 * LCP_ECHOINTERVAL：保持活动LCP回波请求之间的间隔（秒），0表示禁用。
 */
#define LCP_ECHOINTERVAL                CONFIG_LWIP_LCP_ECHOINTERVAL

/**
 * LCP_MAXECHOFAILS：指示失败前连续未应答的回显请求数。
 */
#define LCP_MAXECHOFAILS                CONFIG_LWIP_LCP_MAXECHOFAILS
#endif /* CONFIG_LWIP_ENABLE_LCP_ECHO */

/*
   --------------------------------------
   ----------校验和选项----------
   --------------------------------------
*/

/*
   ---------------------------------------
   ----------IPv6选项---------------
   ---------------------------------------
*/
/**
 * LWIP_IPV6==1:启用IPV6
 */
#define LWIP_IPV6                       CONFIG_LWIP_IPV6

/**
 * MEMP_NUM_ND6_QUEUE:MAC解析期间要排队的IPv6数据包的最大数量。
 */
#define MEMP_NUM_ND6_QUEUE              CONFIG_LWIP_IPV6_MEMP_NUM_ND6_QUEUE

/**
 * LWIP_ND6_NUM_NEIGHBORS:IPv6邻居缓存中的条目数
 */
#define LWIP_ND6_NUM_NEIGHBORS          CONFIG_LWIP_IPV6_ND6_NUM_NEIGHBORS

/*
   ---------------------------------------
   ----------挂钩选项---------------
   ---------------------------------------
*/
#ifdef LWIP_HOOK_FILENAME
#warning LWIP_HOOK_FILENAME is used for IDF default hooks. Please use ESP_IDF_LWIP_HOOK_FILENAME to insert additional hook
#endif
#define LWIP_HOOK_FILENAME              "lwip_default_hooks.h"
#define LWIP_HOOK_IP4_ROUTE_SRC         ip4_route_src_hook

/*
   ---------------------------------------
   ----------调试选项----------
   ---------------------------------------
*/
/**
 * ETHARP_DEBUG：在ETHARP.c中启用调试。
 */
#ifdef CONFIG_LWIP_ETHARP_DEBUG
#define ETHARP_DEBUG                     LWIP_DBG_ON
#else
#define ETHARP_DEBUG                     LWIP_DBG_OFF
#endif


/**
 * NETIF_DEBUG：启用NETIF.c中的调试。
 */
#ifdef CONFIG_LWIP_NETIF_DEBUG
#define NETIF_DEBUG                     LWIP_DBG_ON
#else
#define NETIF_DEBUG                     LWIP_DBG_OFF
#endif

/**
 * PBUF_DEBUG：在PBUF.c中启用调试。
 */
#ifdef CONFIG_LWIP_PBUF_DEBUG
#define PBUF_DEBUG                     LWIP_DBG_ON
#else
#define PBUF_DEBUG                     LWIP_DBG_OFF
#endif

/**
 * API_LIB_DEBUG：在API_LIB.c中启用调试。
 */
#ifdef CONFIG_LWIP_API_LIB_DEBUG
#define API_LIB_DEBUG                     LWIP_DBG_ON
#else
#define API_LIB_DEBUG                     LWIP_DBG_OFF
#endif


/**
 * SOCKETS_DEBUG：在SOCKETS.c中启用调试。
 */
#ifdef CONFIG_LWIP_SOCKETS_DEBUG
#define SOCKETS_DEBUG                   LWIP_DBG_ON
#else
#define SOCKETS_DEBUG                   LWIP_DBG_OFF
#endif

/**
 * ICMP_DEBUG：在ICMP.c中启用调试。
 */
#ifdef CONFIG_LWIP_ICMP_DEBUG
#define ICMP_DEBUG                      LWIP_DBG_ON
#else
#define ICMP_DEBUG                      LWIP_DBG_OFF
#endif

#ifdef CONFIG_LWIP_ICMP6_DEBUG
#define ICMP6_DEBUG                      LWIP_DBG_ON
#else
#define ICMP6_DEBUG                      LWIP_DBG_OFF
#endif

/**
 * DHCP_DEBUG：在DHCP.c中启用调试。
 */
#ifdef CONFIG_LWIP_DHCP_DEBUG
#define DHCP_DEBUG                      LWIP_DBG_ON
#else
#define DHCP_DEBUG                      LWIP_DBG_OFF
#endif

#ifdef CONFIG_LWIP_DHCP_STATE_DEBUG
#define ESP_DHCP_DEBUG                  LWIP_DBG_ON
#else
#define ESP_DHCP_DEBUG                  LWIP_DBG_OFF
#endif

/**
 * IP_DEBUG：启用IP调试。
 */
#ifdef CONFIG_LWIP_IP_DEBUG
#define IP_DEBUG                        LWIP_DBG_ON
#else
#define IP_DEBUG                        LWIP_DBG_OFF
#endif

/**
 * IP6_DEBUG：启用IP6调试。
 */
#ifdef CONFIG_LWIP_IP6_DEBUG
#define IP6_DEBUG                        LWIP_DBG_ON
#else
#define IP6_DEBUG                        LWIP_DBG_OFF
#endif

/**
 * TCP_DEBUG：启用TCP调试。
 */
#ifdef CONFIG_LWIP_TCP_DEBUG
#define TCP_DEBUG                        LWIP_DBG_ON
#else
#define TCP_DEBUG                        LWIP_DBG_OFF
#endif

/**
 * SNTP_DEBUG：启用SNTP调试。
 */
#ifdef CONFIG_LWIP_SNTP_DEBUG
#define SNTP_DEBUG                       LWIP_DBG_ON
#else
#define SNTP_DEBUG                       LWIP_DBG_OFF
#endif

/**
 * MEMP_DEBUG：在MEMP.c中启用调试。
 */
#define MEMP_DEBUG                      LWIP_DBG_OFF

/**
 * TCP_INPUT_DEBUG：启用TCP_in中的调试。c表示传入调试。
 */
#define TCP_INPUT_DEBUG                 LWIP_DBG_OFF

/**
 * TCP_OUTPUT_DEBUG：在TCP_out中启用调试。c输出函数。
 */
#define TCP_OUTPUT_DEBUG                LWIP_DBG_OFF

/**
 * TCPIP_DEBUG：在TCPIP.c中启用调试。
 */
#define TCPIP_DEBUG                     LWIP_DBG_OFF

/**
 * TCP_OOSEQ_DEBUG：启用tcpin中的调试。c表示OOSEQ。
 */
#define TCP_OOSEQ_DEBUG                 LWIP_DBG_OFF

/**
 * ETHARP_TRUST_IP_MAC==1：传入的IP数据包导致ARP表使用数据包中提供的源MAC和IP地址进行更新。如果您不信任LAN对等端具有正确的地址，或者作为处理欺骗的有限方法，您可能希望禁用此功能。如果禁用，如果对等方不在ARP表中，lwIP将需要发出新的ARP请求，这会增加一点延迟。如果对等方之前请求了我们的地址，那么它就在ARP表中。还要注意，这会减慢每个IP数据包的输入处理速度！
 */
#define ETHARP_TRUST_IP_MAC             CONFIG_LWIP_ETHARP_TRUST_IP_MAC


/**
 * POSIX I/O函数通过VFS层映射到LWIP（参见port/VFS_LWIP.c）
 */
#define LWIP_POSIX_SOCKETS_IO_NAMES     0

/**
 * sys/types中的FD_SETSIZE。h是支持的文件描述符的最大数量，CONFIG_LWIP_MAX_SOCKETS定义套接字的数量；LWIP_SOCKET_OFFSET配置为为套接字使用最大数量的文件描述符。从0到LWIP_SOCKET_OFFSET-1的文件描述符是非套接字描述符，而从LWIP_SSOCKET_OFFSET到FD_SETSIZE的文件描述符则是套接字描述符。
 */
#define LWIP_SOCKET_OFFSET              (FD_SETSIZE - CONFIG_LWIP_MAX_SOCKETS)

#define LWIP_IPV6_FORWARD               CONFIG_LWIP_IPV6_FORWARD

#define LWIP_IPV6_NUM_ADDRESSES         CONFIG_LWIP_IPV6_NUM_ADDRESSES

#define LWIP_ND6_RDNSS_MAX_DNS_SERVERS  CONFIG_LWIP_IPV6_RDNSS_MAX_DNS_SERVERS

#define LWIP_IPV6_DHCP6                 CONFIG_LWIP_IPV6_DHCP6

/* 启用所有仅限Espressif选项*/

#define ESP_LWIP                        1
#define ESP_LWIP_ARP                    1
#define ESP_PER_SOC_TCP_WND             0
#define ESP_THREAD_SAFE                 1
#define ESP_THREAD_SAFE_DEBUG           LWIP_DBG_OFF
#define ESP_DHCP                        1
#define ESP_DNS                         1
#define ESP_PERF                        0
#define ESP_RANDOM_TCP_PORT             1
#define ESP_IP4_ATON                    1
#define ESP_LIGHT_SLEEP                 1
#define ESP_L2_TO_L3_COPY               CONFIG_LWIP_L2_TO_L3_COPY
#define LWIP_NETIF_API                  CONFIG_LWIP_NETIF_API
#define ESP_STATS_MEM                   CONFIG_LWIP_STATS
#define ESP_STATS_DROP                  CONFIG_LWIP_STATS
#define ESP_STATS_TCP                   0
#ifdef CONFIG_LWIP_DHCPS
#define ESP_DHCPS                       1
#define ESP_DHCPS_TIMER                 1
#else
#define ESP_DHCPS                       0
#define ESP_DHCPS_TIMER                 0
#endif /* CONFIG_LWIP_DHCPS */
#define ESP_LWIP_LOGI(...)              ESP_LOGI("lwip", __VA_ARGS__)
#define ESP_PING                        1
#define ESP_HAS_SELECT                  1
#define ESP_AUTO_RECV                   1
#define ESP_GRATUITOUS_ARP              CONFIG_LWIP_ESP_GRATUITOUS_ARP
#define ESP_IP4_ROUTE                   1
#define ESP_AUTO_IP                     1
#define ESP_PBUF                        1
#define ESP_PPP                         1
#define ESP_IPV6                        LWIP_IPV6
#define ESP_SOCKET                      1
#define ESP_LWIP_SELECT                 1
#define ESP_LWIP_LOCK                   1
#define ESP_THREAD_PROTECTION           1

#ifdef CONFIG_LWIP_IPV6_AUTOCONFIG
#define ESP_IPV6_AUTOCONFIG             CONFIG_LWIP_IPV6_AUTOCONFIG
#endif

#ifdef ESP_IRAM_ATTR
#undef ESP_IRAM_ATTR
#endif
#define ESP_IRAM_ATTR

#ifdef CONFIG_LWIP_TIMERS_ONDEMAND
#define ESP_LWIP_IGMP_TIMERS_ONDEMAND            1
#define ESP_LWIP_MLD6_TIMERS_ONDEMAND            1
#else
#define ESP_LWIP_IGMP_TIMERS_ONDEMAND            0
#define ESP_LWIP_MLD6_TIMERS_ONDEMAND            0
#endif

#define TCP_SND_BUF                     CONFIG_LWIP_TCP_SND_BUF_DEFAULT
#define TCP_WND                         CONFIG_LWIP_TCP_WND_DEFAULT

/**
 * LWIP_DEBUG：在其他模块中启用LWIP调试。
 */
#ifdef CONFIG_LWIP_DEBUG
#define LWIP_DEBUG                      LWIP_DBG_ON
#else
#undef LWIP_DEBUG
#endif

#define CHECKSUM_CHECK_UDP              CONFIG_LWIP_CHECKSUM_CHECK_UDP
#define CHECKSUM_CHECK_IP               CONFIG_LWIP_CHECKSUM_CHECK_IP
#define CHECKSUM_CHECK_ICMP             CONFIG_LWIP_CHECKSUM_CHECK_ICMP

#define LWIP_NETCONN_FULLDUPLEX         1
#if LWIP_TCPIP_CORE_LOCKING
#define LWIP_NETCONN_SEM_PER_THREAD     0
#else
#define LWIP_NETCONN_SEM_PER_THREAD     1
#endif /* LWIP_TCPIP_CORE_LOCKING */

#define LWIP_DHCP_MAX_NTP_SERVERS       CONFIG_LWIP_DHCP_MAX_NTP_SERVERS
#define LWIP_TIMEVAL_PRIVATE            0

/*
   --------------------------------------
   ------------SNTP选项------------
   --------------------------------------
*/

// 处理的SNTP服务器的最大数量（默认值等于LWIP_DHCP_Max_NTP_servers）
#if defined CONFIG_LWIP_SNTP_MAX_SERVERS
#define SNTP_MAX_SERVERS                CONFIG_LWIP_SNTP_MAX_SERVERS
#endif // CONFIG_LWIP_SNTP_MAX_SERVERS

#ifdef CONFIG_LWIP_DHCP_GET_NTP_SRV
#define LWIP_DHCP_GET_NTP_SRV           CONFIG_LWIP_DHCP_GET_NTP_SRV
#endif // CONFIG_LWIP_DHCP_GET_NTP_SRV

/** 将此值设置为1以支持DNS名称（或IP地址字符串）以设置sntp服务器如果sntp_server_DNS==1:\#define sntp_server_address“pool.ntp.org”，则可以将一个服务器地址/名称定义为默认值
 */
#define SNTP_SERVER_DNS            1

// 它禁用SNTP_UPDATE_DELAY检查，这是在SNTP_set_sync_interval中完成的
#define SNTP_SUPPRESS_DELAY_CHECK

#define SNTP_UPDATE_DELAY                 (sntp_get_sync_interval())
#define SNTP_SET_SYSTEM_TIME_US(sec, us)  (sntp_set_system_time(sec, us))
#define SNTP_GET_SYSTEM_TIME(sec, us)     (sntp_get_system_time(&(sec), &(us)))

#define SOC_SEND_LOG //输出函数

#endif /* __LWIPOPTS_H__ */

