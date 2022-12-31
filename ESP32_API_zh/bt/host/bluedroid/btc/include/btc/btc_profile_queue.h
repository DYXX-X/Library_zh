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

/*******************************************************************************
 * 文件名：btc/btc_profile_queue.h
 *
 *  描述：蓝牙远程设备连接排队
 *
 *******************************************************************************/

#ifndef __BTC_PROFILE_QUEUE_H__
#define __BTC_PROFILE_QUEUE_H__

#include "common/bt_defs.h"
#include "btc/btc_task.h"

typedef enum {
    BTC_PRF_QUE_CONNECT = 0,
    BTC_PRF_QUE_ADVANCE
} btc_prf_que_act_t;

typedef bt_status_t (*btc_connect_cb_t) (bt_bdaddr_t *bda, uint16_t uuid);

typedef struct connect_node_t {
    bt_bdaddr_t bda;
    uint16_t uuid;
    bool busy;
    btc_connect_cb_t connect_cb;
} connect_node_t;

/* btc_prf_que_args_t*/
typedef union {
    // BTC_PRF_QUE_CONNECT
    connect_node_t connect_node;
} btc_prf_que_args_t;

bt_status_t btc_queue_connect(uint16_t uuid, const bt_bdaddr_t *bda, btc_connect_cb_t connect_cb);
void btc_queue_advance(void);
bt_status_t btc_queue_connect_next(void);
void btc_queue_release(void);

void btc_profile_queue_handler(btc_msg_t *msg);
#endif /* __BTC_PROFILE_QUEUE_H__ */

