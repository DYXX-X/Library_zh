/*
 * SPDX文件版权文本：2015-2021浓缩咖啡系统（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */

#ifndef _ESP_NETIF_TYPES_H_
#define _ESP_NETIF_TYPES_H_

#include <stdbool.h>
#include <stdint.h>
#include "esp_event_base.h"
#include "esp_err.h"
#include "esp_netif_ip_addr.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 基于ESP-NETIF的错误定义
 */
#define ESP_ERR_ESP_NETIF_BASE                  0x5000
#define ESP_ERR_ESP_NETIF_INVALID_PARAMS        ESP_ERR_ESP_NETIF_BASE + 0x01
#define ESP_ERR_ESP_NETIF_IF_NOT_READY          ESP_ERR_ESP_NETIF_BASE + 0x02
#define ESP_ERR_ESP_NETIF_DHCPC_START_FAILED    ESP_ERR_ESP_NETIF_BASE + 0x03
#define ESP_ERR_ESP_NETIF_DHCP_ALREADY_STARTED  ESP_ERR_ESP_NETIF_BASE + 0x04
#define ESP_ERR_ESP_NETIF_DHCP_ALREADY_STOPPED  ESP_ERR_ESP_NETIF_BASE + 0x05
#define ESP_ERR_ESP_NETIF_NO_MEM                ESP_ERR_ESP_NETIF_BASE + 0x06
#define ESP_ERR_ESP_NETIF_DHCP_NOT_STOPPED      ESP_ERR_ESP_NETIF_BASE + 0x07
#define ESP_ERR_ESP_NETIF_DRIVER_ATTACH_FAILED   ESP_ERR_ESP_NETIF_BASE + 0x08
#define ESP_ERR_ESP_NETIF_INIT_FAILED           ESP_ERR_ESP_NETIF_BASE + 0x09
#define ESP_ERR_ESP_NETIF_DNS_NOT_CONFIGURED    ESP_ERR_ESP_NETIF_BASE + 0x0A
#define ESP_ERR_ESP_NETIF_MLD6_FAILED           ESP_ERR_ESP_NETIF_BASE + 0x0B
#define ESP_ERR_ESP_NETIF_IP6_ADDR_FAILED       ESP_ERR_ESP_NETIF_BASE + 0x0C


/** @brief esp_netif_object服务器的类型*/
struct esp_netif_obj;

typedef struct esp_netif_obj esp_netif_t;


/** @brief DNS服务器类型*/
typedef enum {
    ESP_NETIF_DNS_MAIN= 0,       /**<DNS主服务器地址*/
    ESP_NETIF_DNS_BACKUP,        /**<DNS备份服务器地址（仅限Wi-Fi STA和以太网）*/
    ESP_NETIF_DNS_FALLBACK,      /**<DNS回退服务器地址（仅限Wi-Fi STA和以太网）*/
    ESP_NETIF_DNS_MAX
} esp_netif_dns_type_t;

/** @brief DNS服务器信息*/
typedef struct {
    esp_ip_addr_t ip; /**<DNS服务器的IPV4地址*/
} esp_netif_dns_info_t;

/** @brief DHCP客户端或DHCP服务器的状态*/
typedef enum {
    ESP_NETIF_DHCP_INIT = 0,    /**<DHCP客户端/服务器处于初始状态（尚未启动）*/
    ESP_NETIF_DHCP_STARTED,     /**<DHCP客户端/服务器已启动*/
    ESP_NETIF_DHCP_STOPPED,     /**<DHCP客户端/服务器已停止*/
    ESP_NETIF_DHCP_STATUS_MAX
} esp_netif_dhcp_status_t;


/** @brief DHCP客户端或DHCP服务器选项功能的模式*/
typedef enum{
    ESP_NETIF_OP_START = 0,
    ESP_NETIF_OP_SET,           /**<设置选项*/
    ESP_NETIF_OP_GET,           /**<获取选项*/
    ESP_NETIF_OP_MAX
} esp_netif_dhcp_option_mode_t;

/** @brief DHCP客户端或DHCP服务器支持的选项*/
typedef enum{
    ESP_NETIF_SUBNET_MASK                   = 1,    /**<网络掩码*/
    ESP_NETIF_DOMAIN_NAME_SERVER            = 6,    /**<域名服务器*/
    ESP_NETIF_ROUTER_SOLICITATION_ADDRESS   = 32,   /**<请求路由器地址*/
    ESP_NETIF_REQUESTED_IP_ADDRESS          = 50,   /**<请求特定IP地址*/
    ESP_NETIF_IP_ADDRESS_LEASE_TIME         = 51,   /**<请求IP地址租用时间*/
    ESP_NETIF_IP_REQUEST_RETRY_TIME         = 52,   /**<请求IP地址重试计数器*/
    ESP_NETIF_VENDOR_CLASS_IDENTIFIER       = 60,   /**<DHCP客户端的供应商类标识符*/
    ESP_NETIF_VENDOR_SPECIFIC_INFO          = 43,   /**<DHCP服务器的供应商特定信息*/
} esp_netif_dhcp_option_id_t;

/**IP事件声明*/
typedef enum {
    IP_EVENT_STA_GOT_IP,               /*!< 站点从连接的AP获得IP*/
    IP_EVENT_STA_LOST_IP,              /*!< 站点丢失IP，IP重置为0*/
    IP_EVENT_AP_STAIPASSIGNED,         /*!< 软AP为连接的站点分配IP*/
    IP_EVENT_GOT_IP6,                  /*!< 首选站或ap或以太网接口v6IP地址*/
    IP_EVENT_ETH_GOT_IP,               /*!< 以太网从连接的AP获取IP*/
    IP_EVENT_ETH_LOST_IP,              /*!< 以太网丢失IP，IP重置为0*/
    IP_EVENT_PPP_GOT_IP,               /*!< PPP接口获得IP*/
    IP_EVENT_PPP_LOST_IP,              /*!< PPP接口丢失IP*/
} ip_event_t;

/** @brief IP事件基础声明*/
ESP_EVENT_DECLARE_BASE(IP_EVENT);

/**IP_Event_STA_GOT_IP、IP_Event_ETH_GOT_IP事件的事件结构*/

typedef struct {
    esp_ip4_addr_t ip;      /**<接口IPV4地址*/
    esp_ip4_addr_t netmask; /**<接口IPV4网络掩码*/
    esp_ip4_addr_t gw;      /**<接口IPV4网关地址*/
} esp_netif_ip_info_t;

/** @brief IPV6 IP地址信息
 */
typedef struct {
    esp_ip6_addr_t ip; /**<接口IPV6地址*/
} esp_netif_ip6_info_t;

typedef struct {
    int if_index;                    /*!< 接收事件的接口索引（留给遗留编译）*/
    esp_netif_t *esp_netif;          /*!< 指向相应esp netif对象的指针*/
    esp_netif_ip_info_t ip_info;     /*!< IP地址、网络掩码、网关IP地址*/
    bool ip_changed;                 /*!< 分配的IP是否已更改*/
} ip_event_got_ip_t;

/**IP_Event_GOT_IP6事件的事件结构*/
typedef struct {
    int if_index;                    /*!< 接收事件的接口索引（留给遗留编译）*/
    esp_netif_t *esp_netif;          /*!< 指向相应esp netif对象的指针*/
    esp_netif_ip6_info_t ip6_info;   /*!< 接口的IPv6地址*/
    int ip_index;                    /*!< IPv6地址索引*/
} ip_event_got_ip6_t;

/**ADD_IP6事件的事件结构*/
typedef struct {
    esp_ip6_addr_t addr;            /*!< 要添加到接口的地址*/
    bool preferred;                 /*!< 地址的默认首选项*/
} ip_event_add_ip6_t;

/**IP_Event_AP_STAIPASSIGNED事件的事件结构*/
typedef struct {
    esp_ip4_addr_t ip; /*!< 分配给工作站的IP地址*/
} ip_event_ap_staipassigned_t;




typedef enum esp_netif_flags {
    ESP_NETIF_DHCP_CLIENT = 1 << 0,
    ESP_NETIF_DHCP_SERVER = 1 << 1,
    ESP_NETIF_FLAG_AUTOUP = 1 << 2,
    ESP_NETIF_FLAG_GARP   = 1 << 3,
    ESP_NETIF_FLAG_EVENT_IP_MODIFIED = 1 << 4,
    ESP_NETIF_FLAG_IS_PPP = 1 << 5,
    ESP_NETIF_FLAG_IS_SLIP = 1 << 6,
} esp_netif_flags_t;

typedef enum esp_netif_ip_event_type {
    ESP_NETIF_IP_EVENT_GOT_IP = 1,
    ESP_NETIF_IP_EVENT_LOST_IP = 2,
} esp_netif_ip_event_type_t;


//
//    ESP-NETIF接口配置：
//      1） 常规（行为）配置（esp_netif_configt）
//      2） （外围设备）驱动程序特定配置（esp_netif_driver_ifconfig_t）
//      3） 网络堆栈特定配置（esp_netif_net_stack_ifconfig_t）--无公开可用
//

typedef struct esp_netif_inherent_config {
    esp_netif_flags_t flags;         /*!< 定义esp netif行为的标志*/
    uint8_t mac[6];                  /*!< 此接口的初始mac地址*/
    const esp_netif_ip_info_t* ip_info;    /*!< 此接口的初始ip地址*/
    uint32_t get_ip_event;           /*!< 接口获取IP时要引发的事件id*/
    uint32_t lost_ip_event;          /*!< 接口丢失IP时要引发的事件id*/
    const char * if_key;             /*!< 接口的字符串标识符*/
    const char * if_desc;            /*!< 界面的文本描述*/
    int route_prio;                  /*!< 如果（如果其他netif已启动），此接口的数字优先级将成为默认路由。route_prio的值越高，表示优先级越高*/
} esp_netif_inherent_config_t;

typedef struct esp_netif_config esp_netif_config_t;

/**
 * @brief  IO驱动程序手柄类型
 */
typedef void * esp_netif_iodriver_handle;

typedef struct esp_netif_driver_base_s {
    esp_err_t (*post_attach)(esp_netif_t *netif, esp_netif_iodriver_handle h);
    esp_netif_t *netif;
} esp_netif_driver_base_t;

/**
 * @brief  特定IO驱动程序配置
 */
struct esp_netif_driver_ifconfig {
    esp_netif_iodriver_handle handle;
    esp_err_t (*transmit)(void *h, void *buffer, size_t len);
    esp_err_t (*transmit_wrap)(void *h, void *buffer, size_t len, void *netstack_buffer);
    void (*driver_free_rx_buffer)(void *h, void* buffer);
};

typedef struct esp_netif_driver_ifconfig esp_netif_driver_ifconfig_t;

/**
 * @brief  特定L3网络堆栈配置
 */

typedef struct esp_netif_netstack_config esp_netif_netstack_config_t;

/**
 * @brief  通用esp_netif配置
 */
struct esp_netif_config {
    const esp_netif_inherent_config_t *base;
    const esp_netif_driver_ifconfig_t *driver;
    const esp_netif_netstack_config_t *stack;
};

/**
 * @brief  ESP-NETIF接收函数类型
 */
typedef esp_err_t (*esp_netif_receive_t)(esp_netif_t *esp_netif, void *buffer, size_t len, void *eb);

#ifdef __cplusplus
}
#endif

#endif // _ESP_NETIF_TYPES_H_

