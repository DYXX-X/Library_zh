/*
 * 根据一个或多个贡献者许可协议向Apache Software Foundation（ASF）许可。有关版权所有权的更多信息，请参阅随本作品分发的通知文件。ASF根据Apache许可证2.0版（“许可证”）向您许可此文件；除非符合许可证，否则不得使用此文件。您可以在以下地址获取许可证副本：
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 * 除非适用法律要求或书面同意，否则根据许可证分发的软件是按“原样”分发的，无任何明示或暗示的担保或条件。有关许可证下权限和限制的具体语言，请参阅许可证。
 */

#ifndef BLE_TGT_STRESS_GATT_H
#define BLE_TGT_STRESS_GATT_H

#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "host/ble_hs.h"
#include "host/ble_uuid.h"
#include "nimble/ble.h"
#include "modlog/modlog.h"
#include "misc.h"

#ifdef __cplusplus
extern "C" {
#endif

extern uint16_t hrs_hrm_handle;

/* 心率配置*/
#define STRESS_GATT_UUID                     0xC0DE
#define STRESS_GATT_READ_UUID                0xC1DE
#define STRESS_GATT_WRITE_UUID               0xC2DE
#define STRESS_GATT_INDICATE_UUID            0xC3DE
#define STRESS_GATT_NOTIFY_UUID              0xC4DE

int gatt_svr_init(void);

void gatt_svr_register_cb(struct ble_gatt_register_ctxt *ctxt, void *arg);

#ifdef __cplusplus
}
#endif


#endif //BLE_TGT_STRESS_GATT_H

