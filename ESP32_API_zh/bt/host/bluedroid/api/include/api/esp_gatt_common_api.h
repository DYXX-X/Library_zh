// 版权所有2015-2017 Espressif Systems（上海）私人有限公司
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

#ifndef __ESP_GATT_COMMON_API_H__
#define __ESP_GATT_COMMON_API_H__

#include <stdint.h>
#include <stdbool.h>

#include "esp_err.h"
#include "esp_bt_defs.h"

#ifdef __cplusplus
extern "C" {
#endif

// GATT中使用的最大传输单位
#define ESP_GATT_DEF_BLE_MTU_SIZE   23   /* 与堆栈/gat_api.h中的GATT_DEF_BLE_MTU_SIZE相关*/

// GATT允许的最大传输单位
#define ESP_GATT_MAX_MTU_SIZE       517  /* 与堆栈/gat_api.h中的GATT_MAX_MTU_SIZE相关*/

/**
 * @brief           调用此函数以设置本地MTU，在BLE连接之前调用此函数。
 *
 * @param[in]       mtu: MTU的大小。
 *
 * @return
 *                  -ESP_OK：成功
 *                  -其他：失败
 *
 */
extern esp_err_t esp_ble_gatt_set_local_mtu (uint16_t mtu);

#if (BLE_INCLUDED == TRUE)
extern uint16_t esp_ble_get_sendable_packets_num (void);
extern uint16_t esp_ble_get_cur_sendable_packets_num (uint16_t connid);
#endif

#ifdef __cplusplus
}
#endif

#endif /* __ESP_GATT_COMMON_API_H__ */

