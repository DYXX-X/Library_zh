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

#ifndef __BTC_GATT_COMMON_H__
#define __BTC_GATT_COMMON_H__

#include "osi/future.h"
#include "stack/bt_types.h"
#include "bta/bta_api.h"
#include "btc/btc_main.h"
#include "btc/btc_task.h"

typedef enum {
    BTC_GATT_ACT_SET_LOCAL_MTU = 0,
} btc_gatt_com_act_t;

/* btc_ble_gattc_args_t*/
typedef union {
    //BTC_GATT_ACT_SET_LOCAL_MTU,
    struct set_mtu_arg {
        uint16_t mtu;
    } set_mtu;
} btc_ble_gatt_com_args_t;

void btc_gatt_com_call_handler(btc_msg_t *msg);
#endif /* __BTC_GATT_COMMON_H__ */

