/**
 * @file 测试.h
 * @brief 蓝牙测试的内部API。
 */

/*
 * 版权所有（c）2017 Intel Corporation
 *
 * SPDX许可证标识符：Apache-2.0
 */

#include "mesh/glue.h"
#include "mesh/access.h"

void bt_test_mesh_model_bound(u16_t addr, struct bt_mesh_model *model,
			      u16_t key_idx);
void bt_test_mesh_model_unbound(u16_t addr, struct bt_mesh_model *model,
				u16_t key_idx);
void bt_test_mesh_prov_invalid_bearer(u8_t opcode);
void bt_test_mesh_net_recv(u8_t ttl, u8_t ctl, u16_t src, u16_t dst,
			   const void *payload, size_t payload_len);
void bt_test_mesh_trans_incomp_timer_exp(void);
void bt_test_print_credentials(void);

