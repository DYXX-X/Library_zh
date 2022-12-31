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

#ifndef __BTC_UTIL_H__
#define __BTC_UTIL_H__

#include <stdbool.h>
#include "stack/bt_types.h"
#include "common/bt_defs.h"
#include "esp_bt_defs.h"
#include "esp_hf_defs.h"

/*******************************************************************************
**  常量和宏
********************************************************************************/
#define CASE_RETURN_STR(const) case const: return #const;

/*******************************************************************************
**  回调函数的类型定义
********************************************************************************/
typedef char bdstr_t[18];

#ifdef __cplusplus
extern "C" {
#endif
/*******************************************************************************
**  功能
********************************************************************************/
#if(BTA_AV_INCLUDED == TRUE)
const char *dump_rc_event(UINT8 event);
const char *dump_rc_notification_event_id(UINT8 event_id);
const char *dump_rc_pdu(UINT8 pdu);
#endif

#if(BTA_AG_INCLUDED == TRUE)
const char *dump_hf_conn_state(UINT16 event);
const char *dump_hf_event(UINT16 event);
const char *dump_hf_call_state(esp_hf_call_status_t call_state);
const char* dump_hf_call_setup_state(esp_hf_call_setup_status_t call_setup_state);
#endif

#if(BTA_HD_INCLUDED == TRUE)
const char* dump_hd_event(uint16_t event);
#endif

#if(BTA_HH_INCLUDED == TRUE)
const char* dump_hh_event(uint16_t event);
#endif

UINT32 devclass2uint(DEV_CLASS dev_class);
void uint2devclass(UINT32 dev, DEV_CLASS dev_class);
void uuid128_be_to_esp_uuid(esp_bt_uuid_t *u, uint8_t* uuid128);

void uuid_to_string_legacy(bt_uuid_t *p_uuid, char *str);

esp_bt_status_t btc_hci_to_esp_status(uint8_t hci_status);
esp_bt_status_t btc_btm_status_to_esp_status (uint8_t btm_status);
esp_bt_status_t btc_bta_status_to_esp_status (uint8_t bta_status);

#ifdef __cplusplus
}
#endif

#endif /*  __BTC_UTIL_H__ */

