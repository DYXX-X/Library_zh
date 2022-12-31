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

#ifndef LWIP_HDR_ND6_H
#define LWIP_HDR_ND6_H

#include "lwip/opt.h"

#if LWIP_IPV6  /* 如果未配置为在lwipots中使用，请不要构建。小时*/

#include "lwip/ip6_addr.h"
#include "lwip/err.h"

#ifdef __cplusplus
extern "C" {
#endif

/**1秒周期*/
#define ND6_TMR_INTERVAL 1000

/**路由器请求以4秒的间隔发送（见RFC 4861，ch.6.3.7）*/
#ifndef ND6_RTR_SOLICITATION_INTERVAL
#define ND6_RTR_SOLICITATION_INTERVAL  4000
#endif

struct pbuf;
struct netif;

void nd6_tmr(void);
void nd6_input(struct pbuf *p, struct netif *inp);
void nd6_clear_destination_cache(void);
struct netif *nd6_find_route(const ip6_addr_t *ip6addr);
err_t nd6_get_next_hop_addr_or_queue(struct netif *netif, struct pbuf *q, const ip6_addr_t *ip6addr, const u8_t **hwaddrp);
u16_t nd6_get_destination_mtu(const ip6_addr_t *ip6addr, struct netif *netif);
#if LWIP_ND6_TCP_REACHABILITY_HINTS
void nd6_reachability_hint(const ip6_addr_t *ip6addr);
#endif /* LWIP_ND6_TCP_REACHABILITY_HINTS */
void nd6_cleanup_netif(struct netif *netif);
#if LWIP_IPV6_MLD
void nd6_adjust_mld_membership(struct netif *netif, s8_t addr_idx, u8_t new_state);
#endif /* LWIP_IPV6_MLD */
void nd6_restart_netif(struct netif *netif);

#if ESP_IPV6
/**当ipv6地址状态优先时设置nd6回调*/
void nd6_set_cb(struct netif *netif, void (*cb)(struct netif *netif, u8_t ip_index));
#endif

#ifdef __cplusplus
}
#endif

#endif /* LWIP_IPV6 */

#endif /* LWIP_HDR_ND6_H */

