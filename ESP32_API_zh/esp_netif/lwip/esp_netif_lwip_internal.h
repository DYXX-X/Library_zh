// 版权所有2015-2018 Espressif Systems（上海）私人有限公司
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

#pragma once

#include "esp_netif.h"
#include "esp_netif_ppp.h"
#include "esp_netif_slip.h"
#include "lwip/netif.h"

#ifdef CONFIG_ESP_NETIF_TCPIP_LWIP

struct esp_netif_netstack_lwip_vanilla_config {
    err_t (*init_fn)(struct netif*);
    void (*input_fn)(void *netif, void *buffer, size_t len, void *eb);
};

struct esp_netif_netstack_lwip_ppp_config {
    void (*input_fn)(void *netif, void *buffer, size_t len, void *eb);
    esp_netif_ppp_config_t ppp_events;
};

struct esp_netif_netstack_lwip_slip_config {
    err_t (*init_fn)(struct netif*);
    void (*input_fn)(void *netif, void *buffer, size_t len, void *eb);
    esp_netif_slip_config_t slip_config;
};

// LWIP netif特定网络堆栈配置
struct esp_netif_netstack_config {
    union {
        struct esp_netif_netstack_lwip_vanilla_config lwip;
        struct esp_netif_netstack_lwip_ppp_config lwip_ppp;
    };
};

struct esp_netif_api_msg_s;

typedef int (*esp_netif_api_fn)(struct esp_netif_api_msg_s *msg);

typedef struct esp_netif_api_msg_s {
    int type;  /**<第一个字段必须为int*/
    int ret;
    esp_netif_api_fn api_fn;
    esp_netif_t *esp_netif;
    void    *data;
} esp_netif_api_msg_t;


typedef struct esp_netif_dns_param_s {
    esp_netif_dns_type_t dns_type;
    esp_netif_dns_info_t *dns_info;
} esp_netif_dns_param_t;

typedef struct esp_netif_ip_lost_timer_s {
    bool timer_running;
} esp_netif_ip_lost_timer_t;

/**
 * @brief 检查netif是否为特定P2P类型
 */
#if CONFIG_PPP_SUPPORT || CONFIG_LWIP_SLIP_SUPPORT
#define _IS_NETIF_POINT2POINT_TYPE(netif, type) (netif->related_data && netif->related_data->is_point2point && netif->related_data->netif_type == type)
#else
#define _IS_NETIF_POINT2POINT_TYPE(netif, type) false
#endif

/**
 * @brief 需要相关数据时的其他netif类型
 */
enum netif_types {
    COMMON_LWIP_NETIF,
    PPP_LWIP_NETIF,
    SLIP_LWIP_NETIF
};

/**
 * @brief 与esp netif相关的数据（一些特殊类型netif的附加数据（通常用于点对点网络类型，如PPP或SLIP）
 */
typedef struct netif_related_data {
    bool is_point2point;
    enum netif_types netif_type;
} netif_related_data_t;

/**
 * @brief 带有接口相关信息的主esp netif容器
 */
struct esp_netif_obj {
    // 默认接口地址
    uint8_t mac[NETIF_MAX_HWADDR_LEN];
    esp_netif_ip_info_t* ip_info;
    esp_netif_ip_info_t* ip_info_old;

    // lwip netif相关
    struct netif *lwip_netif;
    err_t (*lwip_init_fn)(struct netif*);
    void (*lwip_input_fn)(void *input_netif_handle, void *buffer, size_t len, void *eb);
    void * netif_handle;    // netif impl上下文（香草lwip netif或pppcb）
    netif_related_data_t *related_data; // 保存特定netifs的附加数据

    // io驱动程序相关
    void* driver_handle;
    esp_err_t (*driver_transmit)(void *h, void *buffer, size_t len);
    esp_err_t (*driver_transmit_wrap)(void *h, void *buffer, size_t len, void *pbuf);
    void (*driver_free_rx_buffer)(void *h, void* buffer);

    // dhcp相关
    esp_netif_dhcp_status_t dhcpc_status;
    esp_netif_dhcp_status_t dhcps_status;
    bool timer_running;

    // 事件翻译
    ip_event_t get_ip_event;
    ip_event_t lost_ip_event;

    // 其他标志、类型、键、优先级
    esp_netif_flags_t flags;
    char * hostname;
    char * if_key;
    char * if_desc;
    int route_prio;
};

#endif /* CONFIG_ESP_NETIF_TCPIP_LWIP */

