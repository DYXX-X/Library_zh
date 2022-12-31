/*
 * SPDX文件版权文本：2017-2021浓缩咖啡系统（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */

#ifndef _ESP_BLE_MESH_LOW_POWER_API_H_
#define _ESP_BLE_MESH_LOW_POWER_API_H_

#include "esp_ble_mesh_defs.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief       启用BLE Mesh设备LPN功能。
 *
 * @note        此API支持LPN功能。呼叫后，将发送正确的好友请求。
 *
 * @return      成功时返回ESP_OK，否则返回错误代码。
 *
 */
esp_err_t esp_ble_mesh_lpn_enable(void);

/**
 * @brief       禁用BLE Mesh设备LPN功能。
 *
 * @param[in]   force: 当禁用LPN功能时，使用此标志指示是直接清除相应的信息，还是仅发送好友清除以禁用它（如果已经建立了友谊）。
 *
 * @return      成功时返回ESP_OK，否则返回错误代码。
 *
 */
esp_err_t esp_ble_mesh_lpn_disable(bool force);

/**
 * @brief       LPN尝试轮询来自朋友节点的消息。
 *
 * @note        朋友轮询消息由低功率节点发送，以请求朋友节点发送其为低功率节点存储的消息。用户可以调用此API手动发送朋友投票消息。如果未调用此API，则低功耗节点的底层将在轮询超时计时器到期之前发送朋友轮询。如果接收到相应的好友更新并且MD设置为0，这意味着没有低功率节点的消息，那么低功率节点将停止扫描。
 *
 * @return      成功时返回ESP_OK，否则返回错误代码。
 *
 */
esp_err_t esp_ble_mesh_lpn_poll(void);

#ifdef __cplusplus
}
#endif

#endif /* _ESP_BLE_MESH_LOW_POWER_API_H_ */

