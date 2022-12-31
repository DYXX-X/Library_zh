/*
 * 版权所有（c）2001-2003瑞典计算机科学研究所。保留所有权利。
 * 
 * 在满足以下条件的情况下，允许以源代码和二进制形式重新分发和使用，无论是否进行修改：
 *
 * 1.源代码的重新分发必须保留上述版权声明、本条件列表和以下免责声明。2.二进制形式的再发行必须在随发行提供的文档和/或其他材料中复制上述版权声明、本条件列表和以下免责声明。3.未经事先书面许可，不得使用作者的姓名为本软件衍生的产品背书或推广。
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR IMPLIED  WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF  MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT  SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,  EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT  OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING  IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY  OF SUCH DAMAGE.
 *
 * 此文件是lwIP TCP/IP堆栈的一部分。
 * 
 * 作者：Simon Goldschmidt
 *
 */
#ifndef LWIP_HDR_LWIPOPTS_H
#define LWIP_HDR_LWIPOPTS_H

#define LWIP_TESTMODE                   1

#define LWIP_IPV6                       1

#define LWIP_CHECKSUM_ON_COPY           1
#define TCP_CHECKSUM_ON_COPY_SANITY_CHECK 1
#define TCP_CHECKSUM_ON_COPY_SANITY_CHECK_FAIL(printfmsg) LWIP_ASSERT("TCP_CHECKSUM_ON_COPY_SANITY_CHECK_FAIL", 0)

/* 我们链接到特殊的sys_arch。c（用于基本的非等待API层单元测试）*/
#define NO_SYS                          0
#define SYS_LIGHTWEIGHT_PROT            0
#define LWIP_NETCONN                    !NO_SYS
#define LWIP_SOCKET                     !NO_SYS
#define LWIP_NETCONN_FULLDUPLEX         LWIP_SOCKET
#define LWIP_NETBUF_RECVINFO            1
#define LWIP_HAVE_LOOPIF                1
#define TCPIP_THREAD_TEST

/* 启用DHCP以测试它，禁用UDP校验和以更容易地注入数据包*/
#define LWIP_DHCP                       1

/* 选择的更改最少。tcp单元测试所需的h：*/
#define MEM_SIZE                        16000
#define TCP_SND_QUEUELEN                40
#define MEMP_NUM_TCP_SEG                TCP_SND_QUEUELEN
#define TCP_SND_BUF                     (12 * TCP_MSS)
#define TCP_WND                         (10 * TCP_MSS)
#define LWIP_WND_SCALE                  1
#define TCP_RCV_SCALE                   0
#define PBUF_POOL_SIZE                  400 /* pbuf测试需要~200KByte*/

/* 为MDNS测试启用IGMP和MDNS*/
#define LWIP_IGMP                       1
#define LWIP_MDNS_RESPONDER             1
#define LWIP_NUM_NETIF_CLIENT_DATA      (LWIP_MDNS_RESPONDER)

/* 选择的更改最少。etharp单元测试所需的h：*/
#define ETHARP_SUPPORT_STATIC_ENTRIES   1

#define MEMP_NUM_SYS_TIMEOUT            (LWIP_NUM_SYS_TIMEOUT_INTERNAL + 8)

/* 需要MIB2统计信息来检查IPv4重组结果*/
#define MIB2_STATS                      1

/* netif测试想要测试这一点，因此启用：*/
#define LWIP_NETIF_EXT_STATUS_CALLBACK  1

/* 检查lwip_stats.mem。非法而非主张*/
#define LWIP_MEM_ILLEGAL_FREE(msg)      /* 什么都没有*/

#define SNTP_SERVER_DNS                 0
#define LWIP_COMPAT_SOCKET_INET         0

/* ESP特定配置*/
#define ESP_LWIP                                1
#define ESP_DHCP                                1 
#define ESP_DHCPS_TIMER                         0
#define ESP_STATS_DROP                          0
#define ESP_PBUF                                1
#define ESP_IP4_ROUTE                           1
#define ESP_AUTO_IP                             1
#define ESP_IPV6                                1
#define ESP_SOCKET                              0
#define ESP_PPP                                 1
#define ESP_LWIP_IGMP_TIMERS_ONDEMAND           1
#define ESP_LWIP_MLD6_TIMERS_ONDEMAND           1
#define ESP_GRATUITOUS_ARP                      1
#define ESP_LWIP_SELECT                         1
#define ESP_LWIP_LOCK                           1
#define TCP_OOSEQ_DEBUG                         LWIP_DBG_ON
#define ESP_DHCP_DEBUG                          1
#define ESP_THREAD_PROTECTION                   0
#define ESP_DHCP_DISABLE_CLIENT_ID              0
#define ESP_DHCP_DISABLE_VENDOR_CLASS_IDENTIFIER 0

#ifdef IP_NAPT
#define IP_NAPT_MAX                     16
#undef LWIP_RAND
#define LWIP_RAND() (esp_random())
#include "lwip/arch.h"
u32_t esp_random(void);
#endif /* IP_NAPT */
/* ESP调试选项*/
#ifdef ESP_TEST_DEBUG
#define NAPT_DEBUG                      LWIP_DBG_ON
#define IP_DEBUG                        LWIP_DBG_ON
#define UDP_DEBUG                       LWIP_DBG_ON
#define TCP_DEBUG                       LWIP_DBG_ON
#endif /* ESP_TEST_DEBUG */

#endif /* LWIP_HDR_LWIPOPTS_H */

