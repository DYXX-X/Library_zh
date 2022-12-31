/*
 * SPDX文件版权文本：2017-2021浓缩咖啡系统（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */

#ifndef _ESP_BLE_MESH_COMMON_API_H_
#define _ESP_BLE_MESH_COMMON_API_H_

#include "esp_ble_mesh_defs.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief         初始化BLE Mesh模块。此API初始化配置功能和合成数据信息。
 *
 * @note          调用此API后，设备需要调用esp_ble_mesh_prov_enable（）以再次启用配置功能。
 *
 * @param[in]     prov: 指向设备配置功能的指针。该指针必须在BLE Mesh设备的生命周期内保持有效。
 * @param[in]     comp: 指向设备组成数据信息的指针。该指针必须在BLE Mesh设备的生命周期内保持有效。
 *
 * @return        成功时返回ESP_OK，否则返回错误代码。
 *
 */
esp_err_t esp_ble_mesh_init(esp_ble_mesh_prov_t *prov, esp_ble_mesh_comp_t *comp);

/**
 * @brief         取消初始化BLE Mesh模块。
 *
 * @note          此函数应在esp_ble_mesh_client_model_deinit（）之后调用。
 *
 * @param[in]     param: 指向BLE网格解编参数结构的指针。
 *
 * @return        成功时返回ESP_OK，否则返回错误代码。
 *
 */
esp_err_t esp_ble_mesh_deinit(esp_ble_mesh_deinit_param_t *param);

#ifdef __cplusplus
}
#endif

#endif /* _ESP_BLE_MESH_COMMON_API_H_ */

