/**
 * @file 测试.h
 * @brief 蓝牙测试的内部API。
 */

/*
 * 版权所有（c）2017 Intel Corporation
 *
 * SPDX许可证标识符：Apache-2.0
 */

#ifndef __BT_TESTING_H
#define __BT_TESTING_H

#include "slist.h"
#include "glue.h"
#include "access.h"

/**
 * @brief 蓝牙测试
 * @defgroup bt_test_cb蓝牙测试回调
 * @ingroup 蓝牙@{
 */

#ifdef __cplusplus
extern "C" {
#endif

/** @brief 蓝牙测试回调结构。
 *
 *  用于蓝牙测试的回调结构。允许访问蓝牙堆栈内部，而不是由公共API公开。
 */
struct bt_test_cb {
	void (*mesh_net_recv)(u8_t ttl, u8_t ctl, u16_t src, u16_t dst,
			      const void *payload, size_t payload_len);
	void (*mesh_model_bound)(u16_t addr, struct bt_mesh_model *model,
				 u16_t key_idx);
	void (*mesh_model_unbound)(u16_t addr, struct bt_mesh_model *model,
				   u16_t key_idx);
	void (*mesh_prov_invalid_bearer)(u8_t opcode);
	void (*mesh_trans_incomp_timer_exp)(void);

	sys_snode_t node;
};

/** 注册回调以进行蓝牙测试
 *
 *  @param cb bt_test_cb回调结构
 */
void bt_test_cb_register(struct bt_test_cb *cb);

/** 为蓝牙测试注销回调
 *
 *  @param cb bt_test_cb回调结构
 */
void bt_test_cb_unregister(struct bt_test_cb *cb);

/** 发送好友订阅列表添加消息。
 *
 *  由低功耗节点用于发送好友节点要为其存储消息的组地址。
 *
 *  @param group 组地址
 *
 *  @return 成功时为零，否则为（负）错误代码。
 */
int bt_test_mesh_lpn_group_add(u16_t group);

/** 发送好友订阅列表删除消息。
 *
 *  由低功耗节点用于从朋友节点订阅列表中删除组地址。发送到这些地址的消息将不会由朋友节点存储。
 *
 *  @param groups 组地址
 *  @param groups_count 组地址计数
 *
 *  @return 成功时为零，否则为（负）错误代码。
 */
int bt_test_mesh_lpn_group_remove(u16_t *groups, size_t groups_count);

/** 清除重播保护列表缓存。
 *
 *  @return 成功时为零，否则为（负）错误代码。
 */
int bt_test_mesh_rpl_clear(void);

u8_t mod_bind(struct bt_mesh_model *model, u16_t key_idx);
u8_t mod_unbind(struct bt_mesh_model *model, u16_t key_idx, bool store);
int cmd_mesh_init(int argc, char *argv[]);

int bt_test_shell_init(void);
int bt_test_bind_app_key_to_model(struct bt_mesh_model *model, u16_t key_idx, u16_t id);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __BT_TESTING_H */

