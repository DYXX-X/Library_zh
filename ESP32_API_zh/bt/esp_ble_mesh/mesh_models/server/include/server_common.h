/*
 * SPDX文件版权文本：2017-2021浓缩咖啡系统（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */

#ifndef _SERVER_COMMON_H_
#define _SERVER_COMMON_H_

#include <string.h>
#include <stdint.h>
#include "mesh_access.h"

#ifdef __cplusplus
extern "C" {
#endif

#define BLE_MESH_SERVER_RSP_MAX_LEN         384

#define BLE_MESH_SERVER_TRANS_MIC_SIZE      4

#define BLE_MESH_CHECK_SEND_STATUS(_func) do {                      \
        int __status = (_func);                                     \
        if (__status) {                                             \
            BT_ERR("%s, Send failed, err %d", __func__, __status);  \
        }                                                           \
    } while(0);

#define BLE_MESH_STATE_OFF                      0x00
#define BLE_MESH_STATE_ON                       0x01
#define BLE_MESH_STATE_RESTORE                  0x02

/* 以下4个值符合网格模型规范*/
#define BLE_MESH_LIGHTNESS_MIN                  0x0001
#define BLE_MESH_LIGHTNESS_MAX                  0xFFFF
#define BLE_MESH_TEMPERATURE_MIN                0x0320
#define BLE_MESH_TEMPERATURE_MAX                0x4E20
#define BLE_MESH_TEMPERATURE_UNKNOWN            0xFFFF

/* 参考网格模型规范7.2*/
#define BLE_MESH_RANGE_UPDATE_SUCCESS           0x00
#define BLE_MESH_CANNOT_SET_RANGE_MIN           0x01
#define BLE_MESH_CANNOT_SET_RANGE_MAX           0x02

#define BLE_MESH_UNKNOWN_REMAIN_TIME            0x3F
#define BLE_MESH_DEVICE_SPECIFIC_RESOLUTION     10

enum {
    BLE_MESH_TRANS_TIMER_START,  /* 已启动适当的过渡计时器*/
    BLE_MESH_TRANS_FLAG_MAX,
};

struct bt_mesh_state_transition {
    bool just_started;

    uint8_t  trans_time;
    uint8_t  remain_time;
    uint8_t  delay;
    uint32_t quo_tt;
    uint32_t counter;
    uint32_t total_duration;
    int64_t  start_timestamp;

    BLE_MESH_ATOMIC_DEFINE(flag, BLE_MESH_TRANS_FLAG_MAX);
    struct k_delayed_work timer;
};

struct bt_mesh_last_msg_info {
    uint8_t  tid;
    uint16_t src;
    uint16_t dst;
    int64_t  timestamp;
};

#define BLE_MESH_SERVER_RSP_BY_APP  0
#define BLE_MESH_SERVER_AUTO_RSP    1

struct bt_mesh_server_rsp_ctrl {
    /**
     * @brief BLE Mesh服务器响应选项1。如果get_auto_rsp设置为BLE_Mesh_Server_rsp_BY_APP，则客户端获取消息的响应需要由应用程序回复；2.如果get_auto_rsp设置为BLE_MESH_SERVER_auto_rsp，则客户端获取消息的响应将由服务器模型回复；3.如果set_auto_rsp设置为BLE_MESH_SERVER_rsp_BY_APP，则客户端设置消息的响应需要由应用程序回复；4.如果set_auto_rsp设置为BLE_MESH_SERVER_auto_rsp，则服务器模型将回复客户端设置消息的响应；5.如果status_auto_rsp设置为BLE_MESH_SERVER_rsp_BY_APP，则应用程序需要回复服务器状态消息的响应；6.如果status_auto_rsp设置为BLE_MESH_SERVER_auto_rsp，则服务器模型将回复服务器状态消息的响应；
     */
    uint8_t get_auto_rsp : 1, /* 客户端获取消息的响应*/
            set_auto_rsp : 1, /* 客户端集消息的响应*/
            status_auto_rsp : 1; /* 服务器状态消息的响应*/
};

uint8_t bt_mesh_get_default_trans_time(struct bt_mesh_model *model);

int bt_mesh_get_light_lc_trans_time(struct bt_mesh_model *model, uint8_t *trans_time);

int bt_mesh_server_get_optional(struct bt_mesh_model *model,
                                struct bt_mesh_msg_ctx *ctx,
                                struct net_buf_simple *buf,
                                uint8_t *trans_time, uint8_t *delay,
                                bool *optional);

void bt_mesh_server_alloc_ctx(struct k_work *work);
void bt_mesh_server_free_ctx(struct k_work *work);

bool bt_mesh_is_server_recv_last_msg(struct bt_mesh_last_msg_info *last,
                                     uint8_t tid, uint16_t src, uint16_t dst, int64_t *now);

void bt_mesh_server_update_last_msg(struct bt_mesh_last_msg_info *last,
                                    uint8_t tid, uint16_t src, uint16_t dst, int64_t *now);

struct net_buf_simple *bt_mesh_server_get_pub_msg(struct bt_mesh_model *model, uint16_t msg_len);

#ifdef __cplusplus
}
#endif

#endif /* _SERVER_COMMON_H_ */

