/**
 * @file 以太网输出功能-处理输出以太网级流量，实现ARP解析。用于大多数低级netif实现
 */

/*
 * 版权所有（c）2001-2003瑞典计算机科学研究所。版权所有（c）2003-2004 Leon Woestenberg<leon.woestenberg@axon.tv>版权所有（c）2003-2004 Axon Digital Design B.V.，荷兰。保留所有权利。
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

#ifndef LWIP_HDR_NETIF_ETHARP_H
#define LWIP_HDR_NETIF_ETHARP_H

#include "lwip/opt.h"

#if LWIP_ARP || LWIP_ETHERNET /* 如果未配置为在lwipopts.h中使用，则不要构建*/

#include "lwip/pbuf.h"
#include "lwip/ip4_addr.h"
#include "lwip/netif.h"
#include "lwip/ip4.h"
#include "lwip/prot/ethernet.h"

#if LWIP_IPV4 && LWIP_ARP /* 如果未配置为在lwipopts.h中使用，则不要构建*/

#include "lwip/prot/etharp.h"

#ifdef __cplusplus
extern "C" {
#endif

/**1秒周期*/
#define ARP_TMR_INTERVAL 1000

#if ARP_QUEUEING
/** 用于将此处定义的未知地址的传出数据包排队以供memp.h访问的结构
  */
struct etharp_q_entry {
  struct etharp_q_entry *next;
  struct pbuf *p;
};
#endif /* ARP_QUEUEING */

#if ESP_GRATUITOUS_ARP
#ifdef CONFIG_GARP_TMR_INTERVAL
#define GARP_TMR_INTERVAL (CONFIG_GARP_TMR_INTERVAL*1000UL)
#else
#define GARP_TMR_INTERVAL 60000 
#endif

void garp_tmr(void);
#endif

#define etharp_init() /* 兼容性定义，不需要初始化。*/
void etharp_tmr(void);
ssize_t etharp_find_addr(struct netif *netif, const ip4_addr_t *ipaddr,
         struct eth_addr **eth_ret, const ip4_addr_t **ip_ret);
int etharp_get_entry(size_t i, ip4_addr_t **ipaddr, struct netif **netif, struct eth_addr **eth_ret);
err_t etharp_output(struct netif *netif, struct pbuf *q, const ip4_addr_t *ipaddr);
err_t etharp_query(struct netif *netif, const ip4_addr_t *ipaddr, struct pbuf *q);
err_t etharp_request(struct netif *netif, const ip4_addr_t *ipaddr);
/**对于以太网网络接口，我们可能希望发送“免费ARP”；这是一个由节点发送的ARP包，以便自发地使其他节点更新其ARP缓存中的条目。来自RFC 3220“IPv4的IP移动性支持”第4.6节。*/
#define etharp_gratuitous(netif) etharp_request((netif), netif_ip4_addr(netif))
void etharp_cleanup_netif(struct netif *netif);

#if ETHARP_SUPPORT_STATIC_ENTRIES
err_t etharp_add_static_entry(const ip4_addr_t *ipaddr, struct eth_addr *ethaddr);
err_t etharp_remove_static_entry(const ip4_addr_t *ipaddr);
#endif /* ETHARP_SUPPORT_STATIC_ENTRIES */

void etharp_input(struct pbuf *p, struct netif *netif);

#ifdef __cplusplus
}
#endif

#endif /* LWIP_IPV4 && LWIP_ARP */
#endif /* LWIP_ARP || LWIP_ETHERNET */

#endif /* LWIP_HDR_NETIF_ETHARP_H */

