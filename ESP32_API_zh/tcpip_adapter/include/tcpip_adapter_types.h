// 版权所有2015-2019 Espressif Systems（上海）私人有限公司
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

#ifndef _TCPIP_ADAPTER_TYPES_H_
#define _TCPIP_ADAPTER_TYPES_H_

#include "lwip/ip_addr.h"
#include "dhcpserver/dhcpserver.h"
#include "esp_netif_sta_list.h"

#ifdef __cplusplus
extern "C" {
#endif

//
// 如果使用了tcpip_adapter接口，则定义兼容类型
//
#define TCPIP_ADAPTER_DHCP_STARTED ESP_NETIF_DHCP_STARTED
#define TCPIP_ADAPTER_DHCP_STOPPED ESP_NETIF_DHCP_STOPPED
#define TCPIP_ADAPTER_DHCP_INIT    ESP_NETIF_DHCP_INIT
#define TCPIP_ADAPTER_OP_SET       ESP_NETIF_OP_SET
#define TCPIP_ADAPTER_OP_GET       ESP_NETIF_OP_GET
#define TCPIP_ADAPTER_DOMAIN_NAME_SERVER             ESP_NETIF_DOMAIN_NAME_SERVER
#define TCPIP_ADAPTER_ROUTER_SOLICITATION_ADDRESS    ESP_NETIF_ROUTER_SOLICITATION_ADDRESS
#define TCPIP_ADAPTER_REQUESTED_IP_ADDRESS           ESP_NETIF_REQUESTED_IP_ADDRESS
#define TCPIP_ADAPTER_IP_ADDRESS_LEASE_TIME          ESP_NETIF_IP_ADDRESS_LEASE_TIME
#define TCPIP_ADAPTER_IP_REQUEST_RETRY_TIME          ESP_NETIF_IP_REQUEST_RETRY_TIME

/** @brief 旧错误代码定义
 *
 */
#define ESP_ERR_TCPIP_ADAPTER_INVALID_PARAMS        ESP_ERR_ESP_NETIF_INVALID_PARAMS
#define ESP_ERR_TCPIP_ADAPTER_IF_NOT_READY          ESP_ERR_ESP_NETIF_IF_NOT_READY
#define ESP_ERR_TCPIP_ADAPTER_DHCPC_START_FAILED    ESP_ERR_ESP_NETIF_DHCPC_START_FAILED
#define ESP_ERR_TCPIP_ADAPTER_DHCP_ALREADY_STARTED  ESP_ERR_ESP_NETIF_DHCP_ALREADY_STARTED
#define ESP_ERR_TCPIP_ADAPTER_DHCP_ALREADY_STOPPED  ESP_ERR_ESP_NETIF_DHCP_ALREADY_STOPPED
#define ESP_ERR_TCPIP_ADAPTER_NO_MEM                ESP_ERR_ESP_NETIF_NO_MEM
#define ESP_ERR_TCPIP_ADAPTER_DHCP_NOT_STOPPED      ESP_ERR_ESP_NETIF_DHCP_NOT_STOPPED

typedef enum {
    TCPIP_ADAPTER_IF_STA = 0,     /**<Wi-Fi STA（站）接口*/
    TCPIP_ADAPTER_IF_AP,          /**<Wi-Fi软AP接口*/
    TCPIP_ADAPTER_IF_ETH,         /**<以太网接口*/
    TCPIP_ADAPTER_IF_TEST,        /**<tcpip堆栈测试接口*/
    TCPIP_ADAPTER_IF_MAX
} tcpip_adapter_if_t;

/** @brief 旧版ip_info类型
 */
typedef struct {
    ip4_addr_t ip;      /**<接口IPV4地址*/
    ip4_addr_t netmask; /**<接口IPV4网络掩码*/
    ip4_addr_t gw;      /**<接口IPV4网关地址*/
} tcpip_adapter_ip_info_t;

/** @brief 传统typedef
 */
typedef esp_netif_dhcp_status_t tcpip_adapter_dhcp_status_t;
typedef dhcps_lease_t tcpip_adapter_dhcps_lease_t;
typedef esp_netif_dhcp_option_mode_t tcpip_adapter_dhcp_option_mode_t;
typedef esp_netif_dhcp_option_id_t tcpip_adapter_dhcp_option_id_t;
typedef esp_netif_dns_type_t tcpip_adapter_dns_type_t;
typedef esp_netif_dns_info_t tcpip_adapter_dns_info_t;
typedef esp_netif_sta_list_t tcpip_adapter_sta_list_t;
typedef esp_netif_sta_info_t tcpip_adapter_sta_info_t;

#ifdef __cplusplus
} // 外部“C”
#endif

#endif // _TCPIP_ADAPTER_TYPES_H_

