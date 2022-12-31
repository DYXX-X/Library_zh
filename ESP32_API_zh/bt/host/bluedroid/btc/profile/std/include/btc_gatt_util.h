// 版权所有2015-2016 Espressif Systems（上海）私人有限公司
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

#ifndef __BTC_GATT_UTIL_H__
#define __BTC_GATT_UTIL_H__

#include "stack/bt_types.h"
#include "bta/bta_gatt_api.h"
#include "esp_bt_defs.h"
#include "esp_gatt_defs.h"
#include "esp_gattc_api.h"

#define BTC_GATT_CREATE_CONN_ID(gatt_if, conn_id)  ((uint16_t) ((((uint8_t)(conn_id)) << 8) | ((uint8_t)(gatt_if))))
#define BTC_GATT_GET_CONN_ID(conn_id)  (((uint16_t)(conn_id)) >> 8)
#define BTC_GATT_GET_GATT_IF(conn_id)  ((uint8_t)(conn_id))

void btc128_to_bta_uuid(tBT_UUID *p_dest, uint8_t *p_src);
void btc_to_bta_uuid(tBT_UUID *p_dest, esp_bt_uuid_t *p_src);
void btc_to_bta_gatt_id(tBTA_GATT_ID *p_dest, esp_gatt_id_t *p_src);
void btc_to_bta_srvc_id(tBTA_GATT_SRVC_ID *p_dest, esp_gatt_srvc_id_t *p_src);
void btc_to_bta_response(tBTA_GATTS_RSP *rsp_struct, esp_gatt_rsp_t *p_rsp);

void bta_to_btc_uuid(esp_bt_uuid_t *p_dest, tBT_UUID *p_src);
void bta_to_btc_gatt_id(esp_gatt_id_t *p_dest, tBTA_GATT_ID *p_src);
void bta_to_btc_srvc_id(esp_gatt_srvc_id_t *p_dest, tBTA_GATT_SRVC_ID *p_src);

uint16_t set_read_value(uint8_t *gattc_if, esp_ble_gattc_cb_param_t *p_dest, tBTA_GATTC_READ *p_src);

#endif /* __BTC_GATT_UTIL_H__*/

