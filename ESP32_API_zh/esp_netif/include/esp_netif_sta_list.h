// 版权所有2019 Espressif Systems（上海）私人有限公司
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

#ifndef _ESP_NETIF_STA_LIST_H_
#define _ESP_NETIF_STA_LIST_H_

#include "esp_netif_types.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 站点列表信息元素
 */
typedef struct {
    uint8_t mac[6]; /**<站点MAC地址*/
    esp_ip4_addr_t ip;  /**<站点分配的IP地址*/
} esp_netif_sta_info_t;

/**
 * @brief 车站列表结构
 */
typedef struct {
    esp_netif_sta_info_t sta[ESP_WIFI_MAX_CONN_NUM]; /**<连接的站点*/
    int num; /**<连接的站点数量*/
} esp_netif_sta_list_t;

/**
 * @defgroup ESP_NETIF_STA_LIST ESP-NETIF STA列表api
 * @brief Wi-Fi AP接口站点列表
 *
 */

/** @addtogroup ESP_NETIF_STA_LIST @{
 */

/**
 * @brief  获取连接到Wi-Fi AP接口的站点的IP信息
 *
 * @param[in]   wifi_sta_list Wi-Fi站点信息列表，从esp_wifi_ap_get_sta_list（）返回
 * @param[out]  netif_sta_list IP层站点信息列表，对应于wifi_sta_list中提供的MAC地址
 *
 * @return
 *         - ESP_OK
 *         - ESP_ERR_ESP_NETIF_NO_MEM
 *         - ESP_ERR_ESP_NETIF_INVALID_PARAMS
 */
esp_err_t esp_netif_get_sta_list(const wifi_sta_list_t *wifi_sta_list, esp_netif_sta_list_t *netif_sta_list);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif //_ESP_NETIF_STA_LIST_H_

