// 版权所有2019 Espressif Systems（上海）私人有限公司
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

#include <protocomm.h>
#include <protocomm_ble.h>

#include "wifi_provisioning/manager.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief   管理器可以使用GATT服务器通过BLE传输进行配置的方案
 */
extern const wifi_prov_scheme_t wifi_prov_scheme_ble;

/* 当配置完成后应用程序不需要BT和BLE时，将使用此方案特定的事件处理程序*/
#define WIFI_PROV_SCHEME_BLE_EVENT_HANDLER_FREE_BTDM {    \
    .event_cb  = wifi_prov_scheme_ble_event_cb_free_btdm, \
    .user_data = NULL                                     \
}

/* 当配置完成后应用程序不需要BLE处于活动状态时，将使用此方案特定的事件处理程序*/
#define WIFI_PROV_SCHEME_BLE_EVENT_HANDLER_FREE_BLE {    \
    .event_cb  = wifi_prov_scheme_ble_event_cb_free_ble, \
    .user_data = NULL                                    \
}

/* 当配置完成后应用程序不要求BT处于活动状态时，将使用此方案特定的事件处理程序*/
#define WIFI_PROV_SCHEME_BLE_EVENT_HANDLER_FREE_BT {    \
    .event_cb  = wifi_prov_scheme_ble_event_cb_free_bt, \
    .user_data = NULL                                   \
}

void wifi_prov_scheme_ble_event_cb_free_btdm(void *user_data, wifi_prov_cb_event_t event, void *event_data);
void wifi_prov_scheme_ble_event_cb_free_ble (void *user_data, wifi_prov_cb_event_t event, void *event_data);
void wifi_prov_scheme_ble_event_cb_free_bt  (void *user_data, wifi_prov_cb_event_t event, void *event_data);

/**
 * @brief   设置用于配置的128位GATT服务UUID
 *
 * 此API用于覆盖默认的128位供应服务UUID，即0000ffff-0000-1000-8000-00805f9b34fb。
 *
 * 在开始配置之前，即在调用wifi_prov_mgr_start_provision（）之前，必须调用此命令，否则将使用默认UUID。
 *
 * @note    参数所指向的数据必须至少在开始设置之前有效。启动后，管理器将存储此UUID的内部副本，此数据可以在其后释放或失效。
 *
 * @param[in] uuid128  自定义128位UUID
 *
 * @return
 *  -ESP_OK：成功
 *  -ESP_ERR_INVALID_ARG:空参数
 */
esp_err_t wifi_prov_scheme_ble_set_service_uuid(uint8_t *uuid128);

/**
 * @brief   在扫描响应中设置制造商特定数据
 *
 * 在开始配置之前，即在调用wifi_prov_mgr_start_provision（）之前，必须调用此命令。
 *
 * @note    了解定制制造商数据的长度应在限制范围内，这一点很重要。制造商数据与BLE设备名称一起进入扫描响应。默认情况下，BLE设备名称长度为11个字节，但它可能因应用程序使用情况而异。因此，必须遵守扫描响应数据大小限制，即（mfg_data_len+2）<31-（device_name_length+2）。如果mfg_data长度超过此限制，则长度将被截断。
 *
 * @param[in] mfg_data      自定义制造商数据
 * @param[in] mfg_data_len  制造商数据长度
 *
 * @return
 *  -ESP_OK：成功
 *  -ESP_ERR_INVALID_ARG:空参数
 */
esp_err_t wifi_prov_scheme_ble_set_mfg_data(uint8_t *mfg_data, ssize_t mfg_data_len);

#ifdef __cplusplus
}
#endif

