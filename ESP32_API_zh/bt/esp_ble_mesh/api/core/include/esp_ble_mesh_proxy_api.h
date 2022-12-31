/*
 * SPDX文件版权文本：2017-2021浓缩咖啡系统（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */

#ifndef _ESP_BLE_MESH_PROXY_API_H_
#define _ESP_BLE_MESH_PROXY_API_H_

#include "esp_ble_mesh_defs.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief   使用节点标识启用广告。
 *
 * @note    此API要求启用GATT代理支持。一旦被调用，每个子网将在接下来的60秒内使用节点标识开始广告，60秒后将广告网络ID。在正常情况下，BLE Mesh代理节点标识和网络ID广告将在设备配置后由BLE Mesh堆栈自动启用。
 *
 * @return  成功时返回ESP_OK，否则返回错误代码。
 *
 */
esp_err_t esp_ble_mesh_proxy_identity_enable(void);

/**
 * @brief   启用BLE Mesh GATT代理服务。
 *
 * @return  成功时返回ESP_OK，否则返回错误代码。
 *
 */
esp_err_t esp_ble_mesh_proxy_gatt_enable(void);

/**
 * @brief   断开BLE Mesh GATT代理连接（如果有），并禁用BLE Mesh GATT代理服务。
 *
 * @return  成功时返回ESP_OK，否则返回错误代码。
 *
 */
esp_err_t esp_ble_mesh_proxy_gatt_disable(void);

/**
 * @brief        代理客户端创建与代理服务器的连接。
 *
 * @param[in]    addr:      代理服务器的设备地址。
 * @param[in]    addr_type: 设备地址类型（公共或静态随机）。
 * @param[in]    net_idx:   与网状代理广告包中的网络ID相关的NetKey索引。
 *
 * @return       成功时返回ESP_OK，否则返回错误代码。
 *
 */
esp_err_t esp_ble_mesh_proxy_client_connect(esp_ble_mesh_bd_addr_t addr,
                                            esp_ble_mesh_addr_type_t addr_type,
                                            uint16_t net_idx);

/**
 * @brief        代理客户端终止与代理服务器的连接。
 *
 * @param[in]    conn_handle: 代理连接句柄。
 *
 * @return       成功时返回ESP_OK，否则返回错误代码。
 *
 */
esp_err_t esp_ble_mesh_proxy_client_disconnect(uint8_t conn_handle);

/**
 * @brief        代理客户端设置代理服务器的筛选器类型。
 *
 * @param[in]    conn_handle: 代理连接句柄。
 * @param[in]    net_idx:     对应的NetKey索引。
 * @param[in]    filter_type: 白名单或黑名单。
 *
 * @return       成功时返回ESP_OK，否则返回错误代码。
 *
 */
esp_err_t esp_ble_mesh_proxy_client_set_filter_type(uint8_t conn_handle, uint16_t net_idx,
                                                    esp_ble_mesh_proxy_filter_type_t filter_type);

/**
 * @brief        代理客户端将地址添加到代理服务器筛选器列表中。
 *
 * @param[in]    conn_handle: 代理连接句柄。
 * @param[in]    net_idx:     对应的NetKey索引。
 * @param[in]    addr:        指向筛选器地址的指针。
 * @param[in]    addr_num:    筛选器地址的编号。
 *
 * @return       成功时返回ESP_OK，否则返回错误代码。
 *
 */
esp_err_t esp_ble_mesh_proxy_client_add_filter_addr(uint8_t conn_handle, uint16_t net_idx,
                                                    uint16_t *addr, uint16_t addr_num);

/**
 * @brief        代理客户端从代理服务器筛选器列表中删除地址。
 *
 * @param[in]    conn_handle: 代理连接句柄。
 * @param[in]    net_idx:     对应的NetKey索引。
 * @param[in]    addr:        指向筛选器地址的指针。
 * @param[in]    addr_num:    筛选器地址的编号。
 *
 * @return       成功时返回ESP_OK，否则返回错误代码。
 *
 */
esp_err_t esp_ble_mesh_proxy_client_remove_filter_addr(uint8_t conn_handle, uint16_t net_idx,
                                                       uint16_t *addr, uint16_t addr_num);

#ifdef __cplusplus
}
#endif

#endif /* _ESP_BLE_MESH_PROXY_API_H_ */

