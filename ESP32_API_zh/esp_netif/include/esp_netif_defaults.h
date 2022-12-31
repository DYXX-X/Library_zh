/*
 * SPDX文件版权文本：2015-2021浓缩咖啡系统（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */

#ifndef _ESP_NETIF_DEFAULTS_H
#define _ESP_NETIF_DEFAULTS_H

#include "esp_compiler.h"

#ifdef __cplusplus
extern "C" {
#endif

//
// 宏将主配置与netif、堆栈和驱动程序中的部分配置组装在一起
//

#define ESP_NETIF_INHERENT_DEFAULT_WIFI_STA() \
    {   \
        .flags = (esp_netif_flags_t)(ESP_NETIF_DHCP_CLIENT | ESP_NETIF_FLAG_GARP | ESP_NETIF_FLAG_EVENT_IP_MODIFIED), \
        ESP_COMPILER_DESIGNATED_INIT_AGGREGATE_TYPE_EMPTY(mac) \
        ESP_COMPILER_DESIGNATED_INIT_AGGREGATE_TYPE_EMPTY(ip_info) \
        .get_ip_event = IP_EVENT_STA_GOT_IP, \
        .lost_ip_event = IP_EVENT_STA_LOST_IP, \
        .if_key = "WIFI_STA_DEF", \
        .if_desc = "sta", \
        .route_prio = 100 \
     }  \

#ifdef CONFIG_ESP_WIFI_SOFTAP_SUPPORT
#define ESP_NETIF_INHERENT_DEFAULT_WIFI_AP() \
    {   \
        .flags = (esp_netif_flags_t)(ESP_NETIF_DHCP_SERVER | ESP_NETIF_FLAG_AUTOUP), \
        ESP_COMPILER_DESIGNATED_INIT_AGGREGATE_TYPE_EMPTY(mac) \
        .ip_info = &_g_esp_netif_soft_ap_ip, \
        .get_ip_event = 0, \
        .lost_ip_event = 0, \
        .if_key = "WIFI_AP_DEF", \
        .if_desc = "ap", \
        .route_prio = 10 \
    };
#endif

#define ESP_NETIF_INHERENT_DEFAULT_ETH() \
    {   \
        .flags = (esp_netif_flags_t)(ESP_NETIF_DHCP_CLIENT | ESP_NETIF_FLAG_GARP | ESP_NETIF_FLAG_EVENT_IP_MODIFIED), \
        ESP_COMPILER_DESIGNATED_INIT_AGGREGATE_TYPE_EMPTY(mac) \
        ESP_COMPILER_DESIGNATED_INIT_AGGREGATE_TYPE_EMPTY(ip_info) \
        .get_ip_event = IP_EVENT_ETH_GOT_IP, \
        .lost_ip_event = IP_EVENT_ETH_LOST_IP, \
        .if_key = "ETH_DEF", \
        .if_desc = "eth", \
        .route_prio = 50 \
    };

#define ESP_NETIF_INHERENT_DEFAULT_PPP() \
    {   \
        .flags = ESP_NETIF_FLAG_IS_PPP, \
        ESP_COMPILER_DESIGNATED_INIT_AGGREGATE_TYPE_EMPTY(mac) \
        ESP_COMPILER_DESIGNATED_INIT_AGGREGATE_TYPE_EMPTY(ip_info) \
        .get_ip_event = IP_EVENT_PPP_GOT_IP,    \
        .lost_ip_event = IP_EVENT_PPP_LOST_IP,  \
        .if_key = "PPP_DEF",    \
        .if_desc = "ppp",   \
        .route_prio = 20   \
};

#define ESP_NETIF_INHERENT_DEFAULT_OPENTHREAD() \
    {   \
        .flags = 0, \
        ESP_COMPILER_DESIGNATED_INIT_AGGREGATE_TYPE_EMPTY(mac) \
        ESP_COMPILER_DESIGNATED_INIT_AGGREGATE_TYPE_EMPTY(ip_info) \
        .get_ip_event = 0,    \
        .lost_ip_event = 0,   \
        .if_key = "OT_DEF",  \
        .if_desc = "openthread",    \
        .route_prio = 15      \
};

#define ESP_NETIF_INHERENT_DEFAULT_SLIP() \
    {   \
        .flags = ESP_NETIF_FLAG_IS_SLIP, \
        ESP_COMPILER_DESIGNATED_INIT_AGGREGATE_TYPE_EMPTY(mac) \
        ESP_COMPILER_DESIGNATED_INIT_AGGREGATE_TYPE_EMPTY(ip_info) \
        .get_ip_event = 0,    \
        .lost_ip_event = 0,   \
        .if_key = "SLP_DEF",  \
        .if_desc = "slip",    \
        .route_prio = 16      \
};


/**
 * @brief  以太网接口的默认配置参考
 */
#define ESP_NETIF_DEFAULT_ETH()                  \
    {                                            \
        .base = ESP_NETIF_BASE_DEFAULT_ETH,      \
        .driver = NULL,                          \
        .stack = ESP_NETIF_NETSTACK_DEFAULT_ETH, \
    }

#ifdef CONFIG_ESP_WIFI_SOFTAP_SUPPORT
/**
 * @brief  WIFI AP的默认配置参考
 */
#define ESP_NETIF_DEFAULT_WIFI_AP()                  \
    {                                                \
        .base = ESP_NETIF_BASE_DEFAULT_WIFI_AP,      \
        .driver = NULL,                              \
        .stack = ESP_NETIF_NETSTACK_DEFAULT_WIFI_AP, \
    }
#endif

/**
* @brief  WIFI STA的默认配置参考
*/
#define ESP_NETIF_DEFAULT_WIFI_STA()                  \
    {                                                 \
        .base = ESP_NETIF_BASE_DEFAULT_WIFI_STA,      \
        .driver = NULL,                               \
        .stack = ESP_NETIF_NETSTACK_DEFAULT_WIFI_STA, \
    }

/**
* @brief  PPP客户端的默认配置参考
*/
#define ESP_NETIF_DEFAULT_PPP()                       \
    {                                                 \
        .base = ESP_NETIF_BASE_DEFAULT_PPP,           \
        .driver = NULL,                               \
        .stack = ESP_NETIF_NETSTACK_DEFAULT_PPP,      \
    }

/**
* @brief  SLIP客户端的默认配置参考
*/
#define ESP_NETIF_DEFAULT_SLIP()                       \
    {                                                  \
        .base = ESP_NETIF_BASE_DEFAULT_SLIP,           \
        .driver = NULL,                                \
        .stack = ESP_NETIF_NETSTACK_DEFAULT_SLIP,      \
    }


/**
 * @brief  WIFI STA的默认基本配置（特别是netif固有）
 */
#define ESP_NETIF_BASE_DEFAULT_WIFI_STA        &_g_esp_netif_inherent_sta_config

#ifdef CONFIG_ESP_WIFI_SOFTAP_SUPPORT
/**
 * @brief  WIFI AP的默认基本配置（特别是netif固有）
 */
#define ESP_NETIF_BASE_DEFAULT_WIFI_AP         &_g_esp_netif_inherent_ap_config
#endif

/**
 * @brief  以太网接口的默认基本配置（特别是netif固有）
 */
#define ESP_NETIF_BASE_DEFAULT_ETH             &_g_esp_netif_inherent_eth_config

/**
 * @brief  ppp接口的默认基本配置（特别是netif固有）
 */
#define ESP_NETIF_BASE_DEFAULT_PPP             &_g_esp_netif_inherent_ppp_config

/**
 * @brief  滑动接口的默认基本配置（特别是netif固有）
 */
#define ESP_NETIF_BASE_DEFAULT_SLIP             &_g_esp_netif_inherent_slip_config


#define ESP_NETIF_NETSTACK_DEFAULT_ETH          _g_esp_netif_netstack_default_eth
#define ESP_NETIF_NETSTACK_DEFAULT_WIFI_STA     _g_esp_netif_netstack_default_wifi_sta
#ifdef CONFIG_ESP_WIFI_SOFTAP_SUPPORT
#define ESP_NETIF_NETSTACK_DEFAULT_WIFI_AP      _g_esp_netif_netstack_default_wifi_ap
#endif
#define ESP_NETIF_NETSTACK_DEFAULT_PPP          _g_esp_netif_netstack_default_ppp
#define ESP_NETIF_NETSTACK_DEFAULT_SLIP         _g_esp_netif_netstack_default_slip
#define ESP_NETIF_NETSTACK_DEFAULT_OPENTHREAD   _g_esp_netif_netstack_default_openthread

//
// 包括默认网络堆栈配置
//  -网络堆栈配置在特定网络堆栈中提供
//      用户API不可见的实现
//  -此处仅作为不透明指针引用
//
extern const esp_netif_netstack_config_t *_g_esp_netif_netstack_default_eth;
extern const esp_netif_netstack_config_t *_g_esp_netif_netstack_default_wifi_sta;
#ifdef CONFIG_ESP_WIFI_SOFTAP_SUPPORT
extern const esp_netif_netstack_config_t *_g_esp_netif_netstack_default_wifi_ap;
#endif
extern const esp_netif_netstack_config_t *_g_esp_netif_netstack_default_ppp;
extern const esp_netif_netstack_config_t *_g_esp_netif_netstack_default_slip;

//
// 包括esp netif固有的默认通用配置
//  -这些固有配置在esp_netif_defaults中定义。c并描述
//    常见接口的常见行为模式，如STA、AP、ETH、PPP
//
extern const esp_netif_inherent_config_t _g_esp_netif_inherent_sta_config;
#ifdef CONFIG_ESP_WIFI_SOFTAP_SUPPORT
extern const esp_netif_inherent_config_t _g_esp_netif_inherent_ap_config;
#endif
extern const esp_netif_inherent_config_t _g_esp_netif_inherent_eth_config;
extern const esp_netif_inherent_config_t _g_esp_netif_inherent_ppp_config;
extern const esp_netif_inherent_config_t _g_esp_netif_inherent_slip_config;

#ifdef CONFIG_ESP_WIFI_SOFTAP_SUPPORT
extern const esp_netif_ip_info_t _g_esp_netif_soft_ap_ip;
#endif

#if CONFIG_OPENTHREAD_ENABLED
/**
* @brief  SLIP客户端的默认配置参考
*/
#define ESP_NETIF_DEFAULT_OPENTHREAD()                  \
    {                                                   \
        .base = ESP_NETIF_BASE_DEFAULT_OPENTHREAD,      \
        .driver = NULL,                                 \
        .stack = ESP_NETIF_NETSTACK_DEFAULT_OPENTHREAD, \
    }

/**
 * @brief  openthread接口的默认基本配置（esp-nitif固有）
 */
#define ESP_NETIF_BASE_DEFAULT_OPENTHREAD       &_g_esp_netif_inherent_openthread_config

extern const esp_netif_netstack_config_t *_g_esp_netif_netstack_default_openthread;
extern const esp_netif_inherent_config_t _g_esp_netif_inherent_openthread_config;

#endif // CONFIG_OPENTHREAD_ENABLED

#ifdef __cplusplus
}
#endif

#endif //_ESP_NETIF_DEFAULTS_H

