/**
 * @file
 *
 * IPv6的多播侦听器发现。旨在符合RFC 2710。不支持MLDv2。
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

#ifndef LWIP_HDR_MLD6_H
#define LWIP_HDR_MLD6_H

#include "lwip/opt.h"

#if LWIP_IPV6_MLD && LWIP_IPV6  /* 如果未配置为在lwipots中使用，请不要构建。小时*/

#include "lwip/pbuf.h"
#include "lwip/netif.h"

#ifdef __cplusplus
extern "C" {
#endif

/**MLD组*/
struct mld_group {
  /**下一个链接*/
  struct mld_group *next;
  /**多播地址*/
  ip6_addr_t         group_address;
  /**表示我们是最后一个报告的人*/
  u8_t               last_reporter_flag;
  /**组的当前状态*/
  u8_t               group_state;
  /**报告计时器*/
  u16_t              timer;
  /**同时使用计数器*/
  u8_t               use;
};

#define MLD6_TMR_INTERVAL              100 /* 毫秒*/

err_t  mld6_stop(struct netif *netif);
void   mld6_report_groups(struct netif *netif);
void   mld6_tmr(void);
struct mld_group *mld6_lookfor_group(struct netif *ifp, const ip6_addr_t *addr);
void   mld6_input(struct pbuf *p, struct netif *inp);
err_t  mld6_joingroup(const ip6_addr_t *srcaddr, const ip6_addr_t *groupaddr);
err_t  mld6_joingroup_netif(struct netif *netif, const ip6_addr_t *groupaddr);
err_t  mld6_leavegroup(const ip6_addr_t *srcaddr, const ip6_addr_t *groupaddr);
err_t  mld6_leavegroup_netif(struct netif *netif, const ip6_addr_t *groupaddr);

/** @ingroup mld6获取netif的mld6组的列表头。注意：allnodes组IP不在列表中，因为必须始终接收到它才能进行正确的IPv6操作。
 * @see @参考netif_set_mld_mac_filter（）
 */
#define netif_mld6_data(netif) ((struct mld_group *)netif_get_client_data(netif, LWIP_NETIF_CLIENT_DATA_INDEX_MLD6))

#ifdef __cplusplus
}
#endif

#endif /* LWIP_IPV6_MLD && LWIP_IPV6 */

#endif /* LWIP_HDR_MLD6_H */

