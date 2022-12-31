/**
 * @file netif API（从非TCPIP线程使用）
 */

/*
 * 在满足以下条件的情况下，允许以源代码和二进制形式重新分发和使用，无论是否进行修改：
 *
 * 1.源代码的重新分发必须保留上述版权声明、本条件列表和以下免责声明。2.二进制形式的再发行必须在随发行提供的文档和/或其他材料中复制上述版权声明、本条件列表和以下免责声明。3.未经事先书面许可，不得使用作者的姓名为本软件衍生的产品背书或推广。
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * 此文件是lwIP TCP/IP堆栈的一部分。
 *
 */
#ifndef LWIP_HDR_NETIFAPI_H
#define LWIP_HDR_NETIFAPI_H

#include "lwip/opt.h"

#if LWIP_NETIF_API /* 如果未配置为在lwipots中使用，请不要构建。小时*/

#include "lwip/sys.h"
#include "lwip/netif.h"
#include "lwip/dhcp.h"
#include "lwip/autoip.h"
#include "lwip/priv/tcpip_priv.h"
#include "lwip/priv/api_msg.h"
#include "lwip/prot/ethernet.h"

#ifdef __cplusplus
extern "C" {
#endif

/* 应用程序API*/
#if LWIP_ARP && LWIP_IPV4
/* 用于netfiapi_arp_*API*/
enum netifapi_arp_entry {
  NETIFAPI_ARP_PERM /* 永久性条目*/
  /* 可以在此处添加其他条目类型*/
};

/**@ingroup netifapi_arp*/
err_t netifapi_arp_add(const ip4_addr_t *ipaddr, struct eth_addr *ethaddr, enum netifapi_arp_entry type);
/**@ingroup netifapi_arp*/
err_t netifapi_arp_remove(const ip4_addr_t *ipaddr, enum netifapi_arp_entry type);
#endif /* LWIP_ARP && LWIP_IPV4 */

err_t netifapi_netif_add(struct netif *netif,
#if LWIP_IPV4
                         const ip4_addr_t *ipaddr, const ip4_addr_t *netmask, const ip4_addr_t *gw,
#endif /* LWIP_IPV4 */
                         void *state, netif_init_fn init, netif_input_fn input);

#if LWIP_IPV4
err_t netifapi_netif_set_addr(struct netif *netif, const ip4_addr_t *ipaddr,
                              const ip4_addr_t *netmask, const ip4_addr_t *gw);
#endif /* LWIP_IPV4*/

err_t netifapi_netif_common(struct netif *netif, netifapi_void_fn voidfunc,
                            netifapi_errt_fn errtfunc);

/**@ingroup netifapi_netif*/
err_t netifapi_netif_name_to_index(const char *name, u8_t *index);
/**@ingroup netifapi_netif*/
err_t netifapi_netif_index_to_name(u8_t index, char *name);

/** @ingroup netifapi_netif公司
  * @see netif_remove（）
  */
#define netifapi_netif_remove(n)        netifapi_netif_common(n, netif_remove, NULL)
/** @ingroup netifapi_netif公司
  * @see netif_set_up（）
  */
#define netifapi_netif_set_up(n)        netifapi_netif_common(n, netif_set_up, NULL)
/** @ingroup netifapi_netif公司
  * @see netif_set_down（）
  */
#define netifapi_netif_set_down(n)      netifapi_netif_common(n, netif_set_down, NULL)
/** @ingroup netifapi_netif公司
  * @see netif_set_fault（）
  */
#define netifapi_netif_set_default(n)   netifapi_netif_common(n, netif_set_default, NULL)
/** @ingroup netifapi_netif公司
  * @see netif_set_link_up（）
  */
#define netifapi_netif_set_link_up(n)   netifapi_netif_common(n, netif_set_link_up, NULL)
/** @ingroup netifapi_netif公司
  * @see netif_set_link_down（）
  */
#define netifapi_netif_set_link_down(n) netifapi_netif_common(n, netif_set_link_down, NULL)

/**
 * @defgroup netifapi_dhcp4 DHCPv4
 * @ingroup netifapi从非TCPIP线程调用
 */
/** @ingroup netifapi_dhcp4
  * @see dhcp_start（）
  */
#define netifapi_dhcp_start(n)            netifapi_netif_common(n, NULL, dhcp_start)
/**
 * @ingroup netifapi_dhcp4
 * @deprecated 请改用netifapi_dhcp_release_and_stop（）。
 */
#define netifapi_dhcp_stop(n)             netifapi_netif_common(n, dhcp_stop, NULL)
/** @ingroup netifapi_dhcp4
  * @see dhcp_info（）
  */
#define netifapi_dhcp_inform(n)           netifapi_netif_common(n, dhcp_inform, NULL)
/** @ingroup netifapi_dhcp4
  * @see dhcp_renew（）
  */
#define netifapi_dhcp_renew(n)            netifapi_netif_common(n, NULL, dhcp_renew)
/**
 * @ingroup netifapi_dhcp4
 * @deprecated 请改用netifapi_dhcp_release_and_stop（）。
 */
#define netifapi_dhcp_release(n)          netifapi_netif_common(n, NULL, dhcp_release)
/** @ingroup netifapi_dhcp4
  * @see dhcp_release_and_stop（）
  */
#define netifapi_dhcp_release_and_stop(n) netifapi_netif_common(n, dhcp_release_and_stop, NULL)

/**
 * @defgroup netifapi_autoip自动IP
 * @ingroup netifapi从非TCPIP线程调用
 */
/** @ingroup netifapi_自动
  * @see autoip_start（）
  */
#define netifapi_autoip_start(n)      netifapi_netif_common(n, NULL, autoip_start)
/** @ingroup netifapi_自动
  * @see autoip_stop（）
  */
#define netifapi_autoip_stop(n)       netifapi_netif_common(n, NULL, autoip_stop)

#ifdef __cplusplus
}
#endif

#endif /* LWIP_NETIF_API */

#endif /* LWIP_HDR_NETIFAPI_H */

