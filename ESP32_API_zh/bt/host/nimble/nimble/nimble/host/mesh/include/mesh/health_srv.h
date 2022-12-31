/** @file
 *  @brief Bluetooth Mesh Health Server模型API。
 */

/*
 * 版权所有（c）2017 Intel Corporation
 *
 * SPDX许可证标识符：Apache-2.0
 */
#ifndef __BT_MESH_HEALTH_SRV_H
#define __BT_MESH_HEALTH_SRV_H

/**
 * @brief 网状蓝牙网状健康服务器模型
 * @defgroup bt_mesh_health_srv
 * @ingroup bt_网格@{
 */

#ifdef __cplusplus
extern "C" {
#endif

struct bt_mesh_health_srv_cb {
	/* 获取当前故障*/
	int (*fault_get_cur)(struct bt_mesh_model *model, u8_t *test_id,
			     u16_t *company_id, u8_t *faults,
			     u8_t *fault_count);

	/* 获取已注册的错误*/
	int (*fault_get_reg)(struct bt_mesh_model *model, u16_t company_id,
			     u8_t *test_id, u8_t *faults,
			     u8_t *fault_count);

	/* 清除已登记的故障*/
	int (*fault_clear)(struct bt_mesh_model *model, u16_t company_id);

	/* 运行特定测试*/
	int (*fault_test)(struct bt_mesh_model *model, u8_t test_id,
			  u16_t company_id);

	/* 注意：*/
	void (*attn_on)(struct bt_mesh_model *model);

	/* 注意事项关闭*/
	void (*attn_off)(struct bt_mesh_model *model);
};

/** @def BT_MESH_HEALTH_FAULT_MSG
 *
 *  用于定义健康故障消息的助手。
 *
 *  @param max_faults 元素可能具有的最大故障数。
 *
 *  @return 所需大小的新net_buf_simple。
 */
#define BT_MESH_HEALTH_FAULT_MSG(max_faults) \
	NET_BUF_SIMPLE(1 + 3 + (max_faults))

/**Mesh Health Server模型上下文*/
struct bt_mesh_health_srv {
	struct bt_mesh_model *model;

	/* 可选回调结构*/
	const struct bt_mesh_health_srv_cb *cb;

	/* 注意计时器状态*/
	struct k_delayed_work attn_timer;
};

int bt_mesh_fault_update(struct bt_mesh_elem *elem);

extern const struct bt_mesh_model_op bt_mesh_health_srv_op[];
extern const struct bt_mesh_model_cb bt_mesh_health_srv_cb;

/** @def BT_MESH_MODEL_HEALTH_SRV
 *
 *  定义新的健康服务器模型。注意，对于应用程序希望在其上具有健康服务器模型的每个元素，需要重复此API。每个实例还需要唯一的bt_mesh_health_srv和bt_mesh_model_pub上下文。
 *
 *  @param srv 指向唯一结构bt_mesh_health_srv的指针。
 *  @param pub 指向唯一结构bt_mesh_model_pub的指针。
 *
 *  @return 新的网格模型实例。
 */
#define BT_MESH_MODEL_HEALTH_SRV(srv, pub)                                     \
	BT_MESH_MODEL_CB(BT_MESH_MODEL_ID_HEALTH_SRV, bt_mesh_health_srv_op,   \
			 pub, srv, &bt_mesh_health_srv_cb)

#ifdef __cplusplus
}
#endif

/**
 * @}
 */

#endif /* __BT_MESH_HEALTH_SRV_H */

