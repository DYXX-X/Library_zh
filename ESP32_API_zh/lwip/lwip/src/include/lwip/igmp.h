/**
 * @file IGMP API
 */

/*
 * 版权所有（c）2002 CITEL Technologies Ltd.保留所有权利。
 *
 * 在满足以下条件的情况下，允许以源代码和二进制形式重新分发和使用，无论是否进行修改：1.重新分发源代码必须保留上述版权声明、本条件列表和以下免责声明。2.二进制形式的再发行必须在随发行提供的文档和/或其他材料中复制上述版权声明、本条件列表和以下免责声明。3.未经事先书面许可，不得使用CITEL Technologies Ltd的名称或其贡献者的名称来支持或推广源自此软件的产品。
 *
 * THIS SOFTWARE IS PROVIDED BY CITEL TECHNOLOGIES AND CONTRIBUTORS ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL CITEL TECHNOLOGIES OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * 此文件是lwIP TCP/IP堆栈的一部分。瑞典计算机科学研究所和Adam Dunkels被特别授权重新分发此源代码。
*/

#ifndef LWIP_HDR_IGMP_H
#define LWIP_HDR_IGMP_H

#include "lwip/opt.h"
#include "lwip/ip_addr.h"
#include "lwip/netif.h"
#include "lwip/pbuf.h"

#if LWIP_IPV4 && LWIP_IGMP /* 如果未配置为在lwipots中使用，请不要构建。小时*/

#ifdef __cplusplus
extern "C" {
#endif

/* IGMP计时器*/
#define IGMP_TMR_INTERVAL              100 /* 毫秒*/
#define IGMP_V1_DELAYING_MEMBER_TMR   (1000/IGMP_TMR_INTERVAL)
#define IGMP_JOIN_DELAYING_MEMBER_TMR (500 /IGMP_TMR_INTERVAL)

/* 兼容性定义（不用于新代码）*/
#define IGMP_DEL_MAC_FILTER            NETIF_DEL_MAC_FILTER
#define IGMP_ADD_MAC_FILTER            NETIF_ADD_MAC_FILTER

/**
 * igmp组结构-每个接口都有一个组列表，这些组确实应该从接口链接，但如果我们将它们分开，我们不会太影响lwip原始代码
 *
 * 所有系统组地址将有一个组，但这不会运行状态机，因为它用于启动来自所有其他组的报告
 */
struct igmp_group {
  /**下一个链接*/
  struct igmp_group *next;
  /**多播地址*/
  ip4_addr_t         group_address;
  /**表示我们是最后一个报告的人*/
  u8_t               last_reporter_flag;
  /**组的当前状态*/
  u8_t               group_state;
  /**报告计时器，负值为OFF*/
  u16_t              timer;
  /**同时使用计数器*/
  u8_t               use;
};

/*  原型*/
void   igmp_init(void);
err_t  igmp_start(struct netif *netif);
err_t  igmp_stop(struct netif *netif);
void   igmp_report_groups(struct netif *netif);
struct igmp_group *igmp_lookfor_group(struct netif *ifp, const ip4_addr_t *addr);
void   igmp_input(struct pbuf *p, struct netif *inp, const ip4_addr_t *dest);
err_t  igmp_joingroup(const ip4_addr_t *ifaddr, const ip4_addr_t *groupaddr);
err_t  igmp_joingroup_netif(struct netif *netif, const ip4_addr_t *groupaddr);
err_t  igmp_leavegroup(const ip4_addr_t *ifaddr, const ip4_addr_t *groupaddr);
err_t  igmp_leavegroup_netif(struct netif *netif, const ip4_addr_t *groupaddr);
void   igmp_tmr(void);

/** @ingroup igmp获取netif的igmp组的列表头。注意：所有系统组IP作为第一个条目包含在列表中。
 * @see @参考netif_set_igmp_mac_filter（）
 */
#define netif_igmp_data(netif) ((struct igmp_group *)netif_get_client_data(netif, LWIP_NETIF_CLIENT_DATA_INDEX_IGMP))

#ifdef __cplusplus
}
#endif

#endif /* LWIP_IPV4 && LWIP_IGMP */

#endif /* LWIP_HDR_IGMP_H */

