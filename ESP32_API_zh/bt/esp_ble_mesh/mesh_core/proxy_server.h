/*  蓝牙网格*/

/*
 * SPDX文件版权文本：2017 Intel Corporation SPDX FileContributor:2018-2021 Espressif Systems（Shanghai）CO LTD
 *
 * SPDX许可证标识符：Apache-2.0
 */

#ifndef _PROXY_H_
#define _PROXY_H_

#include "net.h"
#include "mesh_bearer_adapt.h"

#ifdef __cplusplus
extern "C" {
#endif

#define BLE_MESH_PROXY_NET_PDU   0x00
#define BLE_MESH_PROXY_BEACON    0x01
#define BLE_MESH_PROXY_CONFIG    0x02
#define BLE_MESH_PROXY_PROV      0x03

#if CONFIG_BLE_MESH_PROXY
/**
 * 设备名称特征：1.对于iOS，当它尝试获取设备名称特征的值时，将使用PDU“按类型读取请求”，相应响应的有效长度为19（23-1-1-2）。2.对于Android，当它尝试获取设备名称特征值时，将使用PDU“读取请求”，相应响应的有效长度为22（23-1）。
 */
#define DEVICE_NAME_SIZE    MIN((BLE_MESH_GATT_DEF_MTU_SIZE - 4), (BLE_MESH_GAP_ADV_MAX_LEN - 2))
#else
/* 对于扫描响应数据，当前最大长度为29（31-1-1）。*/
#define DEVICE_NAME_SIZE    (BLE_MESH_GAP_ADV_MAX_LEN - 2)
#endif

typedef void (*proxy_server_connect_cb_t)(uint8_t conn_handle);
typedef void (*proxy_server_disconnect_cb_t)(uint8_t conn_handle, uint8_t reason);

int bt_mesh_set_device_name(const char *name);

int bt_mesh_proxy_server_send(struct bt_mesh_conn *conn, uint8_t type,
                              struct net_buf_simple *msg);

int bt_mesh_proxy_server_prov_enable(void);
int bt_mesh_proxy_server_prov_disable(bool disconnect);

void bt_mesh_proxy_server_set_conn_cb(proxy_server_connect_cb_t cb);
void bt_mesh_proxy_server_set_disconn_cb(proxy_server_disconnect_cb_t cb);

int bt_mesh_proxy_server_gatt_enable(void);
int bt_mesh_proxy_server_gatt_disable(void);

void bt_mesh_proxy_server_gatt_disconnect(void);

void bt_mesh_proxy_server_beacon_send(struct bt_mesh_subnet *sub);

struct net_buf_simple *bt_mesh_proxy_server_get_buf(void);

int32_t bt_mesh_proxy_server_adv_start(void);
void bt_mesh_proxy_server_adv_stop(void);

void bt_mesh_proxy_server_identity_start(struct bt_mesh_subnet *sub);
void bt_mesh_proxy_server_identity_stop(struct bt_mesh_subnet *sub);

bool bt_mesh_proxy_server_relay(struct net_buf_simple *buf, uint16_t dst);
void bt_mesh_proxy_server_addr_add(struct net_buf_simple *buf, uint16_t addr);

int bt_mesh_proxy_server_init(void);
int bt_mesh_proxy_server_deinit(void);

#ifdef __cplusplus
}
#endif

#endif /* _PROXY_H_ */
