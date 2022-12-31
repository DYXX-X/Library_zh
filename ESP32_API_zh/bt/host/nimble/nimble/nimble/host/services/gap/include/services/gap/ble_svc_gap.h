/*
 * 根据一个或多个贡献者许可协议向Apache Software Foundation（ASF）许可。有关版权所有权的更多信息，请参阅随本作品分发的通知文件。ASF根据Apache许可证2.0版（“许可证”）向您许可此文件；除非符合许可证，否则不得使用此文件。您可以在以下地址获取许可证副本：
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 * 除非适用法律要求或书面同意，否则根据许可证分发的软件是按“原样”分发的，无任何明示或暗示的担保或条件。有关许可证下权限和限制的具体语言，请参阅许可证。
 */

#ifndef H_BLE_SVC_GAP_
#define H_BLE_SVC_GAP_

#include <inttypes.h>

#ifdef __cplusplus
extern "C" {
#endif

#define BLE_SVC_GAP_UUID16                                  0x1800
#define BLE_SVC_GAP_CHR_UUID16_DEVICE_NAME                  0x2a00
#define BLE_SVC_GAP_CHR_UUID16_APPEARANCE                   0x2a01
#define BLE_SVC_GAP_CHR_UUID16_PERIPH_PREF_CONN_PARAMS      0x2a04
#define BLE_SVC_GAP_CHR_UUID16_CENTRAL_ADDRESS_RESOLUTION   0x2aa6

#define BLE_SVC_GAP_APPEARANCE_GEN_UNKNOWN                         0
#define BLE_SVC_GAP_APPEARANCE_GEN_COMPUTER                        128
#define BLE_SVC_GAP_APPEARANCE_CYC_SPEED_AND_CADENCE_SENSOR        1157

typedef void (ble_svc_gap_chr_changed_fn) (uint16_t uuid);

void ble_svc_gap_set_chr_changed_cb(ble_svc_gap_chr_changed_fn *cb);

const char *ble_svc_gap_device_name(void);
int ble_svc_gap_device_name_set(const char *name);
uint16_t ble_svc_gap_device_appearance(void);
int ble_svc_gap_device_appearance_set(uint16_t appearance);

void ble_svc_gap_init(void);

#ifdef __cplusplus
}
#endif

#endif

