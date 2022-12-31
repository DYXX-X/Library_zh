/*  蓝牙网格*/

/*
 * SPDX文件版权文本：2017 Intel Corporation SPDX FileContributor:2018-2021 Espressif Systems（Shanghai）CO LTD
 *
 * SPDX许可证标识符：Apache-2.0
 */

#ifndef _BLE_MESH_TEST_H_
#define _BLE_MESH_TEST_H_

#include "mesh_bearer_adapt.h"

#ifdef __cplusplus
extern "C" {
#endif

int bt_mesh_test(void);

struct bt_mesh_device_network_info {
    uint8_t  net_key[16];
    uint16_t net_idx;
    uint8_t  flags;
    uint32_t iv_index;
    uint16_t unicast_addr;
    uint8_t  dev_key[16];
    uint8_t  app_key[16];
    uint16_t app_idx;
    uint16_t group_addr;
};

int bt_mesh_device_auto_enter_network(struct bt_mesh_device_network_info *info);

/* 在尝试更新白名单之前，用户需要确保满足以下条件之一：1.禁用BLE扫描；2.启用BLE扫描，禁用扫描筛选器策略；如果在启用扫描筛选器策略的情况下启用BLE扫描，则用户需要首先停止BLE扫描然后才能更新白名单。
 */
int bt_mesh_test_update_white_list(struct bt_mesh_white_list *wl);

int bt_mesh_test_start_scanning(bool wl_en);

int bt_mesh_test_stop_scanning(void);

#ifdef __cplusplus
}
#endif

#endif /* _BLE_MESH_TEST_H_ */

