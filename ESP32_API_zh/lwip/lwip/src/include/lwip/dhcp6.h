/**
 * @file
 *
 * DHCPv6客户端：根据RFC 3315（有状态DHCPv6）和RFC 3736（无状态DHCPv4）自动配置IPv6地址。
 */

/*
 * 版权所有（c）2018 Simon Goldschmidt保留所有权利。
 *
 * 在满足以下条件的情况下，允许以源代码和二进制形式重新分发和使用，无论是否进行修改：
 *
 * 1.源代码的重新分发必须保留上述版权声明、本条件列表和以下免责声明。2.二进制形式的再发行必须在随发行提供的文档和/或其他材料中复制上述版权声明、本条件列表和以下免责声明。3.未经事先书面许可，不得使用作者的姓名为本软件衍生的产品背书或推广。
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * 此文件是lwIP TCP/IP堆栈的一部分。
 *
 * 作者：Simon Goldschmidt<goldsimon@gmx.de>
 */

#ifndef LWIP_HDR_IP6_DHCP6_H
#define LWIP_HDR_IP6_DHCP6_H

#include "lwip/opt.h"

#if LWIP_IPV6_DHCP6  /* 如果未配置为在lwipots中使用，请不要构建。小时*/

#include "lwip/err.h"
#include "lwip/netif.h"

#ifdef __cplusplus
extern "C" {
#endif

/**应用程序调用dhcp6_tmr（）的周期（毫秒）*/
#define DHCP6_TIMER_MSECS   500

struct dhcp6
{
  /**上次发送请求的事务标识符*/
  u32_t xid;
  /**轨道PCB分配状态*/
  u8_t pcb_allocated;
  /**当前DHCPv6状态机状态*/
  u8_t state;
  /**当前请求的重试次数*/
  u8_t tries;
  /**如果在另一个操作处于活动状态时触发了请求配置，则会跟踪它*/
  u8_t request_config_pending;
  /**#以DHCP6_TIMER_MSECS为周期标记请求超时*/
  u16_t request_timeout;
#if LWIP_IPV6_DHCP6_STATEFUL
  /* @todo：在这里添加更多成员以跟踪有状态的DHCPv6数据，如租赁时间*/
#endif /* LWIP_IPV6_DHCP6_STATEFUL */
};

void dhcp6_set_struct(struct netif *netif, struct dhcp6 *dhcp6);
/**使用dhcp6_set_struct（）删除先前设置为netif的结构dhcp6*/
#define dhcp6_remove_struct(netif) netif_set_client_data(netif, LWIP_NETIF_CLIENT_DATA_INDEX_DHCP6, NULL)
void dhcp6_cleanup(struct netif *netif);

err_t dhcp6_enable_stateful(struct netif *netif);
err_t dhcp6_enable_stateless(struct netif *netif);
void dhcp6_disable(struct netif *netif);

void dhcp6_tmr(void);

void dhcp6_nd6_ra_trigger(struct netif *netif, u8_t managed_addr_config, u8_t other_config);

#if LWIP_DHCP6_GET_NTP_SRV
/**除此之外，必须存在此功能才能将提供的NTP服务器添加到NTP（或SNTP）引擎。请参阅LWIP_DHCP6_MAX_NTP_SERVERS*/
extern void dhcp6_set_ntp_servers(u8_t num_ntp_servers, const ip_addr_t* ntp_server_addrs);
#endif /* LWIP_DHCP6_GET_NTP_SRV */

#define netif_dhcp6_data(netif) ((struct dhcp6*)netif_get_client_data(netif, LWIP_NETIF_CLIENT_DATA_INDEX_DHCP6))

#ifdef __cplusplus
}
#endif

#endif /* LWIP_IPV6_DHCP6 */

#endif /* LWIP_HDR_IP6_DHCP6_H */

