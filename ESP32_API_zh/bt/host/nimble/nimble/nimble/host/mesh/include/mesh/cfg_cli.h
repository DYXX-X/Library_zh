/** @file
 *  @brief 蓝牙网格配置客户端模型API。
 */

/*
 * 版权所有（c）2017 Intel Corporation
 *
 * SPDX许可证标识符：Apache-2.0
 */
#ifndef __BT_MESH_CFG_CLI_H
#define __BT_MESH_CFG_CLI_H

/**
 * @brief 蓝牙网格
 * @defgroup bt_mesh_cfg_cli蓝牙网格配置客户端模型
 * @ingroup bt_网格@{
 */

#ifdef __cplusplus
extern "C" {
#endif

/**网格配置客户端模型上下文*/
struct bt_mesh_cfg_cli {
	struct bt_mesh_model *model;

	struct k_sem          op_sync;
	u32_t                 op_pending;
	void                 *op_param;
};

extern const struct bt_mesh_model_op bt_mesh_cfg_cli_op[];
extern const struct bt_mesh_model_cb bt_mesh_cfg_cli_cb;

#define BT_MESH_MODEL_CFG_CLI(cli_data)                                        \
	BT_MESH_MODEL_CB(BT_MESH_MODEL_ID_CFG_CLI, bt_mesh_cfg_cli_op, NULL,   \
			 cli_data, &bt_mesh_cfg_cli_cb)

int bt_mesh_cfg_comp_data_get(u16_t net_idx, u16_t addr, u8_t page,
			      u8_t *status, struct os_mbuf *comp);

int bt_mesh_cfg_beacon_get(u16_t net_idx, u16_t addr, u8_t *status);

int bt_mesh_cfg_beacon_set(u16_t net_idx, u16_t addr, u8_t val, u8_t *status);

int bt_mesh_cfg_ttl_get(u16_t net_idx, u16_t addr, u8_t *ttl);

int bt_mesh_cfg_ttl_set(u16_t net_idx, u16_t addr, u8_t val, u8_t *ttl);

int bt_mesh_cfg_friend_get(u16_t net_idx, u16_t addr, u8_t *status);

int bt_mesh_cfg_friend_set(u16_t net_idx, u16_t addr, u8_t val, u8_t *status);

int bt_mesh_cfg_gatt_proxy_get(u16_t net_idx, u16_t addr, u8_t *status);

int bt_mesh_cfg_gatt_proxy_set(u16_t net_idx, u16_t addr, u8_t val,
			       u8_t *status);

int bt_mesh_cfg_relay_get(u16_t net_idx, u16_t addr, u8_t *status,
			  u8_t *transmit);

int bt_mesh_cfg_relay_set(u16_t net_idx, u16_t addr, u8_t new_relay,
			  u8_t new_transmit, u8_t *status, u8_t *transmit);

int bt_mesh_cfg_net_key_add(u16_t net_idx, u16_t addr, u16_t key_net_idx,
			    const u8_t net_key[16], u8_t *status);

int bt_mesh_cfg_app_key_add(u16_t net_idx, u16_t addr, u16_t key_net_idx,
			    u16_t key_app_idx, const u8_t app_key[16],
			    u8_t *status);

int bt_mesh_cfg_mod_app_bind(u16_t net_idx, u16_t addr, u16_t elem_addr,
			     u16_t mod_app_idx, u16_t mod_id, u8_t *status);

int bt_mesh_cfg_mod_app_bind_vnd(u16_t net_idx, u16_t addr, u16_t elem_addr,
				 u16_t mod_app_idx, u16_t mod_id, u16_t cid,
				 u8_t *status);

/** @def BT_MESH_PUB_PERIOD_100MS
 *
 *  @brief 帮助程序宏以100ms为单位对模型发布周期进行编码
 *
 *  @param steps 100ms步数。
 *
 *  @return 可分配给bt_mesh_cfg_mod_pub.period的编码值
 */
#define BT_MESH_PUB_PERIOD_100MS(steps)  ((steps) & BIT_MASK(6))

/** @def BT_MESH_PUB_PERIOD_SEC
 *
 *  @brief 帮助程序宏，用于以1秒为单位对模型发布周期进行编码
 *
 *  @param steps 1秒步数。
 *
 *  @return 可分配给bt_mesh_cfg_mod_pub.period的编码值
 */
#define BT_MESH_PUB_PERIOD_SEC(steps)   (((steps) & BIT_MASK(6)) | (1 << 6))

/** @def BT_MESH_PUB_PERIOD_10SEC
 *
 *  @brief 帮助程序宏以10秒为单位对模型发布周期进行编码
 *
 *  @param steps 10秒步数。
 *
 *  @return 可分配给bt_mesh_cfg_mod_pub.period的编码值
 */
#define BT_MESH_PUB_PERIOD_10SEC(steps) (((steps) & BIT_MASK(6)) | (2 << 6))

/** @def BT_MESH_PUB_PERIOD_10MIN
 *
 *  @brief 帮助程序宏以10分钟为单位对模型发布周期进行编码
 *
 *  @param steps 10分钟步数。
 *
 *  @return 可分配给bt_mesh_cfg_mod_pub.period的编码值
 */
#define BT_MESH_PUB_PERIOD_10MIN(steps) (((steps) & BIT_MASK(6)) | (3 << 6))

struct bt_mesh_cfg_mod_pub {
	u16_t  addr;
	u16_t  app_idx;
	bool   cred_flag;
	u8_t   ttl;
	u8_t   period;
	u8_t   transmit;
};

int bt_mesh_cfg_mod_pub_get(u16_t net_idx, u16_t addr, u16_t elem_addr,
			    u16_t mod_id, struct bt_mesh_cfg_mod_pub *pub,
			    u8_t *status);

int bt_mesh_cfg_mod_pub_get_vnd(u16_t net_idx, u16_t addr, u16_t elem_addr,
				u16_t mod_id, u16_t cid,
				struct bt_mesh_cfg_mod_pub *pub, u8_t *status);

int bt_mesh_cfg_mod_pub_set(u16_t net_idx, u16_t addr, u16_t elem_addr,
			    u16_t mod_id, struct bt_mesh_cfg_mod_pub *pub,
			    u8_t *status);

int bt_mesh_cfg_mod_pub_set_vnd(u16_t net_idx, u16_t addr, u16_t elem_addr,
				u16_t mod_id, u16_t cid,
				struct bt_mesh_cfg_mod_pub *pub, u8_t *status);

int bt_mesh_cfg_mod_sub_add(u16_t net_idx, u16_t addr, u16_t elem_addr,
			    u16_t sub_addr, u16_t mod_id, u8_t *status);

int bt_mesh_cfg_mod_sub_add_vnd(u16_t net_idx, u16_t addr, u16_t elem_addr,
				 u16_t sub_addr, u16_t mod_id, u16_t cid,
				 u8_t *status);

int bt_mesh_cfg_mod_sub_del(u16_t net_idx, u16_t addr, u16_t elem_addr,
			    u16_t sub_addr, u16_t mod_id, u8_t *status);

int bt_mesh_cfg_mod_sub_del_vnd(u16_t net_idx, u16_t addr, u16_t elem_addr,
				 u16_t sub_addr, u16_t mod_id, u16_t cid,
				 u8_t *status);

int bt_mesh_cfg_mod_sub_overwrite(u16_t net_idx, u16_t addr, u16_t elem_addr,
				  u16_t sub_addr, u16_t mod_id, u8_t *status);

int bt_mesh_cfg_mod_sub_overwrite_vnd(u16_t net_idx, u16_t addr,
				      u16_t elem_addr, u16_t sub_addr,
				      u16_t mod_id, u16_t cid, u8_t *status);

int bt_mesh_cfg_mod_sub_va_add(u16_t net_idx, u16_t addr, u16_t elem_addr,
			       const u8_t label[16], u16_t mod_id,
			       u16_t *virt_addr, u8_t *status);

int bt_mesh_cfg_mod_sub_va_add_vnd(u16_t net_idx, u16_t addr, u16_t elem_addr,
				   const u8_t label[16], u16_t mod_id,
				   u16_t cid, u16_t *virt_addr, u8_t *status);

int bt_mesh_cfg_mod_sub_va_del(u16_t net_idx, u16_t addr, u16_t elem_addr,
			       const u8_t label[16], u16_t mod_id,
			       u16_t *virt_addr, u8_t *status);

int bt_mesh_cfg_mod_sub_va_del_vnd(u16_t net_idx, u16_t addr, u16_t elem_addr,
				   const u8_t label[16], u16_t mod_id,
				   u16_t cid, u16_t *virt_addr, u8_t *status);

int bt_mesh_cfg_mod_sub_va_overwrite(u16_t net_idx, u16_t addr,
				     u16_t elem_addr, const u8_t label[16],
				     u16_t mod_id, u16_t *virt_addr,
				     u8_t *status);

int bt_mesh_cfg_mod_sub_va_overwrite_vnd(u16_t net_idx, u16_t addr,
					 u16_t elem_addr, const u8_t label[16],
					 u16_t mod_id, u16_t cid,
					 u16_t *virt_addr, u8_t *status);

struct bt_mesh_cfg_hb_sub {
	u16_t src;
	u16_t dst;
	u8_t  period;
	u8_t  count;
	u8_t  min;
	u8_t  max;
};

int bt_mesh_cfg_hb_sub_set(u16_t net_idx, u16_t addr,
			   struct bt_mesh_cfg_hb_sub *sub, u8_t *status);

int bt_mesh_cfg_hb_sub_get(u16_t net_idx, u16_t addr,
			   struct bt_mesh_cfg_hb_sub *sub, u8_t *status);

struct bt_mesh_cfg_hb_pub {
	u16_t dst;
	u8_t  count;
	u8_t  period;
	u8_t  ttl;
	u16_t feat;
	u16_t net_idx;
};

int bt_mesh_cfg_hb_pub_set(u16_t net_idx, u16_t addr,
			   const struct bt_mesh_cfg_hb_pub *pub, u8_t *status);

int bt_mesh_cfg_hb_pub_get(u16_t net_idx, u16_t addr,
			   struct bt_mesh_cfg_hb_pub *pub, u8_t *status);

s32_t bt_mesh_cfg_cli_timeout_get(void);
void bt_mesh_cfg_cli_timeout_set(s32_t timeout);

#ifdef __cplusplus
}
#endif
/**
 * @}
 */

#endif /* __BT_MESH_CFG_CLI_H */

