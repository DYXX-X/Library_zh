/*  蓝牙网格*/

/*
 * SPDX文件版权文本：2017 Intel Corporation SPDX FileContributor:2018-2021 Espressif Systems（Shanghai）CO LTD
 *
 * SPDX许可证标识符：Apache-2.0
 */

#ifndef _ADV_H_
#define _ADV_H_

#include "mesh_access.h"
#include "mesh_bearer_adapt.h"

#ifdef __cplusplus
extern "C" {
#endif

/* 单个数据类型的最大广告数据负载*/
#define BLE_MESH_ADV_DATA_SIZE 29

/* 用户数据是指向结构bt_mesh_adv的指针（4字节）*/
#define BLE_MESH_ADV_USER_DATA_SIZE 4

#define BLE_MESH_ADV(buf) (*(struct bt_mesh_adv **)net_buf_user_data(buf))

typedef struct bt_mesh_msg {
    bool  relay;        /* 标志指示数据包是否为中继数据包*/
    void *arg;          /* 指向结构net_buf的指针*/
    uint16_t src;       /* 中继数据包的源地址*/
    uint16_t dst;       /* 中继数据包的目标地址*/
    uint32_t timestamp; /* 中继数据包发布到队列时记录的时间戳*/
} bt_mesh_msg_t;

enum bt_mesh_adv_type {
    BLE_MESH_ADV_PROV,
    BLE_MESH_ADV_DATA,
    BLE_MESH_ADV_BEACON,
    BLE_MESH_ADV_URI,
    BLE_MESH_ADV_BLE,
};

struct bt_mesh_adv {
    const struct bt_mesh_send_cb *cb;
    void *cb_data;

    uint8_t type:3,
            busy:1;
    uint8_t xmit;
};

typedef struct bt_mesh_adv *(*bt_mesh_adv_alloc_t)(int id);

/* xmit_count：重传次数，即0==1次传输*/
struct net_buf *bt_mesh_adv_create(enum bt_mesh_adv_type type, uint8_t xmit,
                                   int32_t timeout);

typedef enum {
    BLE_MESH_BUF_REF_EQUAL,
    BLE_MESH_BUF_REF_SMALL,
    BLE_MESH_BUF_REF_MAX,
} bt_mesh_buf_ref_flag_t;

void bt_mesh_adv_buf_ref_debug(const char *func, struct net_buf *buf,
                               uint8_t ref_cmp, bt_mesh_buf_ref_flag_t flag);

struct net_buf *bt_mesh_adv_create_from_pool(struct net_buf_pool *pool,
                                             bt_mesh_adv_alloc_t get_id,
                                             enum bt_mesh_adv_type type,
                                             uint8_t xmit, int32_t timeout);

void bt_mesh_unref_buf_from_pool(struct net_buf_pool *pool);

void bt_mesh_adv_send(struct net_buf *buf, const struct bt_mesh_send_cb *cb,
                      void *cb_data);

struct net_buf *bt_mesh_relay_adv_create(enum bt_mesh_adv_type type, uint8_t xmit,
                                         int32_t timeout);

void bt_mesh_relay_adv_send(struct net_buf *buf, const struct bt_mesh_send_cb *cb,
                            void *cb_data, uint16_t src, uint16_t dst);

uint16_t bt_mesh_get_stored_relay_count(void);

void bt_mesh_adv_update(void);

void bt_mesh_adv_init(void);
void bt_mesh_adv_deinit(void);

#if CONFIG_BLE_MESH_SUPPORT_BLE_ADV
int bt_mesh_start_ble_advertising(const struct bt_mesh_ble_adv_param *param,
                                  const struct bt_mesh_ble_adv_data *data, uint8_t *index);

int bt_mesh_stop_ble_advertising(uint8_t index);
#endif /* CONFIG_BLE_MESH_SUPPORT_BLE_ADV */

#ifdef __cplusplus
}
#endif

#endif /* _ADV_H_ */

