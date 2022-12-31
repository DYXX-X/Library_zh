// 版权所有2020 Espressif Systems（上海）私人有限公司
//
// 根据Apache许可证2.0版（“许可证”）获得许可；
// 除非符合许可证，否则不得使用此文件。
// 您可以在以下地址获取许可证副本：

//     http://www.apache.org/licenses/LICENSE-2.0
//
// 除非适用法律要求或书面同意，软件
// 根据许可证分发的内容是按“原样”分发的，
// 无任何明示或暗示的保证或条件。
// 有关管理权限和
// 许可证下的限制。

#ifndef _LWIP_DEFAULT_HOOKS_H_
#define _LWIP_DEFAULT_HOOKS_H_
#include "lwip/ip_addr.h"
#include "lwip/arch.h"
#include "lwip/err.h"

#ifdef ESP_IDF_LWIP_HOOK_FILENAME
#include ESP_IDF_LWIP_HOOK_FILENAME
#endif

#ifdef __cplusplus
extern "C" {
#endif

#ifdef CONFIG_LWIP_HOOK_TCP_ISN_DEFAULT
void lwip_init_tcp_isn(u32_t boot_time, const u8_t *secret_16_bytes);
#endif
#if defined(CONFIG_LWIP_HOOK_TCP_ISN_CUSTOM) || defined(CONFIG_LWIP_HOOK_TCP_ISN_DEFAULT)
u32_t lwip_hook_tcp_isn(const ip_addr_t *local_ip, u16_t local_port,
                        const ip_addr_t *remote_ip, u16_t remote_port);
#define LWIP_HOOK_TCP_ISN lwip_hook_tcp_isn
#endif /* CONFIG_LWIP_HOOK_TCP_ISN... */

#if defined(CONFIG_LWIP_HOOK_IP6_ROUTE_CUSTOM) || defined(CONFIG_LWIP_HOOK_IP6_ROUTE_DEFAULT)
struct netif *
lwip_hook_ip6_route(const ip6_addr_t *src, const ip6_addr_t *dest);

#define LWIP_HOOK_IP6_ROUTE lwip_hook_ip6_route
#endif /* CONFIG_LWIP_HOOK_IP6_ROUTE... */

#if defined(CONFIG_LWIP_HOOK_ND6_GET_GW_CUSTOM) || defined(CONFIG_LWIP_HOOK_ND6_GET_GW_DEFAULT)
const ip6_addr_t *lwip_hook_nd6_get_gw(struct netif *netif, const ip6_addr_t *dest);

#define LWIP_HOOK_ND6_GET_GW lwip_hook_nd6_get_gw
#endif /* CONFIG_LWIP_HOOK_ND6_GET_GATEWAY... */

#if defined(CONFIG_LWIP_HOOK_NETCONN_EXT_RESOLVE_CUSTOM) || defined(CONFIG_LWIP_HOOK_NETCONN_EXT_RESOLVE_DEFAULT)
int lwip_hook_netconn_external_resolve(const char *name, ip_addr_t *addr, u8_t addrtype, err_t *err);

#define LWIP_HOOK_NETCONN_EXTERNAL_RESOLVE lwip_hook_netconn_external_resolve
#endif /* CONFIG_LWIP_HOOK_NETCONN_EXTERNAL_RESOLVE... */

#ifdef __cplusplus
}
#endif

#endif /* _LWIP_DEFAULT_HOOKS_H_ */

