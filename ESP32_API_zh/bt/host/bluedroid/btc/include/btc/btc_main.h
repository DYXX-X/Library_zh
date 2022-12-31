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

#ifndef __BTC_BT_MAIN_H__
#define __BTC_BT_MAIN_H__

#include "osi/future.h"
#include "stack/bt_types.h"
#include "bta/bta_api.h"
#include "btc/btc_main.h"
#include "btc/btc_task.h"

typedef enum {
    BTC_MAIN_ACT_INIT = 0,
    BTC_MAIN_ACT_DEINIT,
    BTC_MAIN_ACT_ENABLE,
    BTC_MAIN_ACT_DISABLE,
} btc_main_act_t;

typedef enum {
    BTC_MAIN_INIT_FUTURE = 0,
    BTC_MAIN_DEINIT_FUTURE,
    BTC_MAIN_ENABLE_FUTURE,
    BTC_MAIN_DISABLE_FUTURE,
    BTC_MAIN_FUTURE_NUM,
} btc_main_future_type_t;

future_t **btc_main_get_future_p(btc_main_future_type_t type);

#if 0
typedef union {
    struct btc_main_init_args {
        future_t *future;
    } init;
    struct btc_main_deinit_args {
        future_t *future;
    } deinit;
    struct btc_main_init_args {
        future_t *future;
    } enable;
    struct btc_main_init_args {
        future_t *future;
    } disable;
} btc_main_args_t;

bt_status_t btc_enable_bluetooth(future_t *future);
void btc_disable_bluetooth(future_t *future);
bt_status_t btc_init_bluetooth(future_t *future);
void btc_deinit_bluetooth(future_t *future);
#endif

void btc_main_call_handler(btc_msg_t *msg);
#endif /* __BTC_BT_MAIN_H__ */

