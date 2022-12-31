// 版权所有2015-2018 Espressif Systems（上海）私人有限公司
//
// 根据Apache许可证2.0版（“许可证”）获得许可；
// 除非符合许可证，否则不得使用此文件。
// 您可以在以下地址获取许可证副本：
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// 除非适用法律要求或书面同意，软件
// 根据许可证分发的内容是按“原样”分发的，
// 无任何明示或暗示的保证或条件。
// 有关管理权限和
// 许可证下的限制。

#pragma once

#include <stdint.h>
#include <stdbool.h>

#include "esp_err.h"
#include "esp_wifi_types.h"
#include "esp_netif.h"

#ifdef __cplusplus
extern "C" {
#endif

/**系统事件类型枚举*/
typedef enum {
    SYSTEM_EVENT_WIFI_READY = 0,           /*!< ESP32 WiFi就绪*/
    SYSTEM_EVENT_SCAN_DONE,                /*!< ESP32完成扫描AP*/
    SYSTEM_EVENT_STA_START,                /*!< ESP32站启动*/
    SYSTEM_EVENT_STA_STOP,                 /*!< ESP32站点停止*/
    SYSTEM_EVENT_STA_CONNECTED,            /*!< ESP32站连接到AP*/
    SYSTEM_EVENT_STA_DISCONNECTED,         /*!< ESP32站与AP断开连接*/
    SYSTEM_EVENT_STA_AUTHMODE_CHANGE,      /*!< ESP32站点连接的AP的身份验证模式已更改*/
    SYSTEM_EVENT_STA_GOT_IP,               /*!< ESP32电台从连接的AP获得IP*/
    SYSTEM_EVENT_STA_LOST_IP,              /*!< ESP32电台丢失IP，IP重置为0*/
    SYSTEM_EVENT_STA_BSS_RSSI_LOW,         /*!< ESP32站连接的BSS rssi低于阈值*/
    SYSTEM_EVENT_STA_WPS_ER_SUCCESS,       /*!< ESP32电台wps在注册人模式下成功*/
    SYSTEM_EVENT_STA_WPS_ER_FAILED,        /*!< ESP32电台wps在注册人模式下失败*/
    SYSTEM_EVENT_STA_WPS_ER_TIMEOUT,       /*!< 注册人模式下ESP32电台wps超时*/
    SYSTEM_EVENT_STA_WPS_ER_PIN,           /*!< 注册人模式下的ESP32电台wps pin码*/
    SYSTEM_EVENT_STA_WPS_ER_PBC_OVERLAP,   /*!< ESP32站wps在注册人模式下重叠*/
    SYSTEM_EVENT_AP_START,                 /*!< ESP32软AP启动*/
    SYSTEM_EVENT_AP_STOP,                  /*!< ESP32软AP停止*/
    SYSTEM_EVENT_AP_STACONNECTED,          /*!< 连接到ESP32软AP的站点*/
    SYSTEM_EVENT_AP_STADISCONNECTED,       /*!< 与ESP32软AP断开连接的站点*/
    SYSTEM_EVENT_AP_STAIPASSIGNED,         /*!< ESP32软AP为连接的站点分配IP*/
    SYSTEM_EVENT_AP_PROBEREQRECVED,        /*!< 在软AP接口中接收探测请求包*/
    SYSTEM_EVENT_ACTION_TX_STATUS,         /*!< 接收发送的动作帧的状态*/
    SYSTEM_EVENT_ROC_DONE,                 /*!< 指示剩余信道操作状态的完成*/
    SYSTEM_EVENT_STA_BEACON_TIMEOUT,       /*!< ESP32电台信标超时*/
    SYSTEM_EVENT_FTM_REPORT,               /*!< 接收FTM程序报告*/
    SYSTEM_EVENT_GOT_IP6,                  /*!< 首选ESP32站或ap或以太网接口v6IP地址*/
    SYSTEM_EVENT_ETH_START,                /*!< ESP32以太网启动*/
    SYSTEM_EVENT_ETH_STOP,                 /*!< ESP32以太网停止*/
    SYSTEM_EVENT_ETH_CONNECTED,            /*!< ESP32以太网物理链路*/
    SYSTEM_EVENT_ETH_DISCONNECTED,         /*!< ESP32以太网物理链路断开*/
    SYSTEM_EVENT_ETH_GOT_IP,               /*!< ESP32以太网从连接的AP获得IP*/
    SYSTEM_EVENT_ETH_LOST_IP,              /*!< ESP32以太网丢失IP，IP重置为0*/
    SYSTEM_EVENT_MAX                       /*!< 此枚举中的成员数*/
} system_event_id_t;

/* 添加此宏定义以与旧IDF版本兼容*/
#ifndef SYSTEM_EVENT_AP_STA_GOT_IP6
#define SYSTEM_EVENT_AP_STA_GOT_IP6 SYSTEM_EVENT_GOT_IP6
#endif


/**SYSTEM_EVENT_STA_WPS_ER_FAILED事件的参数结构*/
typedef wifi_event_sta_wps_fail_reason_t system_event_sta_wps_fail_reason_t;

/**SYSTEM_EVENT_SCAN_DONE事件的参数结构*/
typedef wifi_event_sta_scan_done_t system_event_sta_scan_done_t;

/**SYSTEM_EVENT_STA_CONNECTED事件的参数结构*/
typedef wifi_event_sta_connected_t system_event_sta_connected_t;

/**SYSTEM_EVENT_STA_DISCONNECTED事件的参数结构*/
typedef wifi_event_sta_disconnected_t system_event_sta_disconnected_t;

/**SYSTEM_EVENT_STA_AUTHMODE_CHANGE事件的参数结构*/
typedef wifi_event_sta_authmode_change_t system_event_sta_authmode_change_t;

/**SYSTEM_EVENT_STA_WPS_ER_PIN事件的参数结构*/
typedef wifi_event_sta_wps_er_pin_t system_event_sta_wps_er_pin_t;

/**SYSTEM_EVENT_STA_WPS_ER_PIN事件的参数结构*/
typedef wifi_event_sta_wps_er_success_t system_event_sta_wps_er_success_t;

/**事件的参数结构*/
typedef wifi_event_ap_staconnected_t system_event_ap_staconnected_t;

/**事件的参数结构*/
typedef wifi_event_ap_stadisconnected_t system_event_ap_stadisconnected_t;

/**事件的参数结构*/
typedef wifi_event_ap_probe_req_rx_t system_event_ap_probe_req_rx_t;

/**SYSTEM_EVENT_FTM_REPORT事件的参数结构*/
typedef wifi_event_ftm_report_t system_event_ftm_report_t;

/**事件的参数结构*/
typedef ip_event_ap_staipassigned_t system_event_ap_staipassigned_t;

/**事件的参数结构*/
typedef ip_event_got_ip_t system_event_sta_got_ip_t;

/**事件的参数结构*/
typedef ip_event_got_ip6_t system_event_got_ip6_t;

/**所有可能的system_event参数结构的并集*/
typedef union {
    system_event_sta_connected_t               connected;          /*!< ESP32站连接到AP*/
    system_event_sta_disconnected_t            disconnected;       /*!< ESP32站与AP断开连接*/
    system_event_sta_scan_done_t               scan_done;          /*!< ESP32站点扫描（AP）已完成*/
    system_event_sta_authmode_change_t         auth_change;        /*!< 连接到的AP ESP32站点的身份验证模式已更改*/
    system_event_sta_got_ip_t                  got_ip;             /*!< ESP32电台获得IP，首次获得IP或IP更改时*/
    system_event_sta_wps_er_pin_t              sta_er_pin;         /*!< 收到ESP32站WPS注册人模式PIN码*/
    system_event_sta_wps_fail_reason_t         sta_er_fail_reason; /*!< 收到ESP32站WPS注册人模式失败原因代码*/
    system_event_sta_wps_er_success_t          sta_er_success;     /*!< ESP32站WPS注册成功*/
    system_event_ap_staconnected_t             sta_connected;      /*!< 连接到ESP32软AP的站点*/
    system_event_ap_stadisconnected_t          sta_disconnected;   /*!< 与ESP32软AP断开连接的站点*/
    system_event_ap_probe_req_rx_t             ap_probereqrecved;  /*!< ESP32软AP接收探测请求包*/
    system_event_ftm_report_t                  ftm_report;         /*!< FTM程序报告*/
    system_event_ap_staipassigned_t            ap_staipassigned;   /**<ESP32软AP为站点分配IP*/
    system_event_got_ip6_t                     got_ip6;            /*!< ESP32站或ap或以太网ipv6地址状态更改为首选*/
} system_event_info_t;

/**事件，作为标记枚举*/
typedef struct {
    system_event_id_t     event_id;      /*!< 事件ID*/
    system_event_info_t   event_info;    /*!< 事件信息*/
} system_event_t;

/**事件处理程序函数类型*/
typedef esp_err_t (*system_event_handler_t)(esp_event_base_t event_base,
                                            int32_t event_id,
                                            void* event_data,
                                            size_t event_data_size,
                                            TickType_t ticks_to_wait);

/**
  * @brief  将事件发送到事件任务
  *
  * @note 此API是遗留事件系统的一部分。新代码应使用esp_event.h中的事件库API
  *
  * 其他任务/模块（如tcpip_adapter）可以调用此API将事件发送到事件任务
  *
  * @param event 要发送的事件
  *
  * @return ESP_OK：成功
  * @return 其他：失败
  */
esp_err_t esp_event_send(system_event_t *event) __attribute__ ((deprecated));

/**
  * @brief  将事件发送到事件任务
  *
  * @note 此API仅由WiFi驱动程序使用。
  *
  * 其他任务/模块（如tcpip_adapter）可以调用此API将事件发送到事件任务
  *
  * @param[in] event_base 标识事件的事件库
  * @param[in] event_id 标识事件的事件id
  * @param[in] event_data 传递给处理程序的特定于事件发生的数据
  * @param[in] event_data_size 事件数据的大小
  * @param[in] ticks_to_wait 完整事件队列上要阻止的标记数
  *
  * @return ESP_OK：成功
  * @return 其他：失败
  */
esp_err_t esp_event_send_internal(esp_event_base_t event_base,
                            int32_t event_id,
                            void* event_data,
                            size_t event_data_size,
                            TickType_t ticks_to_wait);

/**
 * @brief  系统事件的默认事件处理程序
 *
 * @note 此API是遗留事件系统的一部分。新代码应使用esp_event.h中的事件库API
 *
 * 此函数执行系统事件的默认处理。使用esp_event_loop API时，在调用用户提供的回调函数之前会自动调用它。
 *
 * 实现自定义事件循环的应用程序必须在事件处理过程中调用此函数。
 *
 * @param  event   指向要处理的事件的指针
 * @return ESP_OK（如果事件处理成功）
 */
esp_err_t esp_event_process_default(system_event_t *event) __attribute__ ((deprecated));

/**
  * @brief  为以太网接口安装默认事件处理程序
  *
  * @note 此API是遗留事件系统的一部分。新代码应使用esp_event.h中的事件库API
  *
  */
void esp_event_set_default_eth_handlers(void);

/**
  * @brief  为Wi-Fi接口（站点和AP）安装默认事件处理程序
  *
  * @note 此API是遗留事件系统的一部分。新代码应使用esp_event.h中的事件库API
  */
void esp_event_set_default_wifi_handlers(void) __attribute__ ((deprecated));

/**
 * @brief  应用程序指定的事件回调函数
 *
 * @note 此API是遗留事件系统的一部分。新代码应使用esp_event.h中的事件库API
 *
 *
 * @param  ctx    为用户保留
 * @param  event  此文件中定义的事件类型
 *
 * @return
 *    -ESP_OK：成功
 *    -其他：失败
 */
typedef esp_err_t (*system_event_cb_t)(void *ctx, system_event_t *event);

/**
 * @brief  初始化事件循环
 *
 * @note 此API是遗留事件系统的一部分。新代码应使用esp_event.h中的事件库API
 *
 * 创建事件处理程序和任务
 *
 * @param  cb   应用程序指定的事件回调，它可以通过调用esp_event_set_cb进行修改
 * @param  ctx  为用户保留
 *
 * @return
 *    -ESP_OK：成功
 *    -其他：失败
 */
esp_err_t esp_event_loop_init(system_event_cb_t cb, void *ctx) __attribute__ ((deprecated));

/**
 * @brief  设置应用程序指定的事件回调函数
 *
 * @note 此API是遗留事件系统的一部分。新代码应使用esp_event.h中的事件库API
 *
 * @attention 1.如果cb为NULL，则表示应用程序不需要处理。如果cb不为NULL，将在默认事件回调完成后，在收到事件时调用它
 *
 * @param  cb   应用程序回调函数
 * @param  ctx  要传递给回调的参数
 *
 *
 * @return 旧回调
 */
system_event_cb_t esp_event_loop_set_cb(system_event_cb_t cb, void *ctx) __attribute__ ((deprecated));

#ifdef __cplusplus
}
#endif

