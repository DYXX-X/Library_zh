/** @file
 *  @brief 蓝牙网格配置服务器模型API。
 */

/*
 * 版权所有（c）2017 Intel Corporation
 *
 * SPDX许可证标识符：Apache-2.0
 */
#ifndef __BT_MESH_CFG_SRV_H
#define __BT_MESH_CFG_SRV_H

/**
 * @brief 蓝牙网格
 * @defgroup bt_mesh_cfg_srv蓝牙网格配置服务器型号
 * @ingroup bt_网格@{
 */

#ifdef __cplusplus
extern "C" {
#endif

/**网格配置服务器模型上下文*/
struct bt_mesh_cfg_srv {
	struct bt_mesh_model *model;

	u8_t net_transmit;         /* 网络传输状态*/
	u8_t relay;                /* 继电器模式状态*/
	u8_t relay_retransmit;     /* 继电器重新传输状态*/
	u8_t beacon;               /* 安全网络信标状态*/
	u8_t gatt_proxy;           /* GATT代理国*/
	u8_t frnd;                 /* 好友状态*/
	u8_t default_ttl;          /* 默认TTL*/

	/* 心跳发布*/
	struct bt_mesh_hb_pub {
		struct k_delayed_work timer;

		u16_t dst;
		u16_t count;
		u8_t  period;
		u8_t  ttl;
		u16_t feat;
		u16_t net_idx;
	} hb_pub;

	/* 心跳订阅*/
	struct bt_mesh_hb_sub {
		s64_t  expiry;

		u16_t src;
		u16_t dst;
		u16_t count;
		u8_t  min_hops;
		u8_t  max_hops;

		/* 可选订阅跟踪功能*/
		void (*func)(u8_t hops, u16_t feat);
	} hb_sub;
};

extern const struct bt_mesh_model_op bt_mesh_cfg_srv_op[];
extern const struct bt_mesh_model_cb bt_mesh_cfg_srv_cb;

#define BT_MESH_MODEL_CFG_SRV(srv_data)                                        \
	BT_MESH_MODEL_CB(BT_MESH_MODEL_ID_CFG_SRV, bt_mesh_cfg_srv_op, NULL,   \
			 srv_data, &bt_mesh_cfg_srv_cb)

#ifdef __cplusplus
}
#endif

/**
 * @}
 */

#endif /* __BT_MESH_CFG_SRV_H */

