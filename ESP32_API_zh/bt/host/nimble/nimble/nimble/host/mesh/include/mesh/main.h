/** @file
 *  @brief 蓝牙网格配置文件API。
 */

/*
 * 版权所有（c）2017 Intel Corporation
 *
 * SPDX许可证标识符：Apache-2.0
 */
#ifndef __BT_MESH_MAIN_H
#define __BT_MESH_MAIN_H

/**
 * @brief 蓝牙网格配置
 * @defgroup bt_mesh_prov蓝牙网格配置
 * @ingroup bt_网格@{
 */

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
	BT_MESH_NO_OUTPUT       = 0,
	BT_MESH_BLINK           = BIT(0),
	BT_MESH_BEEP            = BIT(1),
	BT_MESH_VIBRATE         = BIT(2),
	BT_MESH_DISPLAY_NUMBER  = BIT(3),
	BT_MESH_DISPLAY_STRING  = BIT(4),
} bt_mesh_output_action_t;

typedef enum {
	BT_MESH_NO_INPUT      = 0,
	BT_MESH_PUSH          = BIT(0),
	BT_MESH_TWIST         = BIT(1),
	BT_MESH_ENTER_NUMBER  = BIT(2),
	BT_MESH_ENTER_STRING  = BIT(3),
} bt_mesh_input_action_t;

typedef enum {
	BT_MESH_PROV_ADV   = BIT(0),
	BT_MESH_PROV_GATT  = BIT(1),
} bt_mesh_prov_bearer_t;

typedef enum {
	BT_MESH_PROV_OOB_OTHER     = BIT(0),
	BT_MESH_PROV_OOB_URI       = BIT(1),
	BT_MESH_PROV_OOB_2D_CODE   = BIT(2),
	BT_MESH_PROV_OOB_BAR_CODE  = BIT(3),
	BT_MESH_PROV_OOB_NFC       = BIT(4),
	BT_MESH_PROV_OOB_NUMBER    = BIT(5),
	BT_MESH_PROV_OOB_STRING    = BIT(6),
	/* 保留7-10*/
	BT_MESH_PROV_OOB_ON_BOX    = BIT(11),
	BT_MESH_PROV_OOB_IN_BOX    = BIT(12),
	BT_MESH_PROV_OOB_ON_PAPER  = BIT(13),
	BT_MESH_PROV_OOB_IN_MANUAL = BIT(14),
	BT_MESH_PROV_OOB_ON_DEV    = BIT(15),
} bt_mesh_prov_oob_info_t;

/**配置属性和功能。*/
struct bt_mesh_prov {
	/**广告未设置时使用的UUID*/
	const u8_t *uuid;

	/** 可选URI。这将与未设置的信标分开发布，但是未设置的灯塔将包含其哈希值，因此两者可以由设置者关联。
	 */
	const char *uri;

	/**带外信息字段。*/
	bt_mesh_prov_oob_info_t oob_info;

	/**静态OOB值*/
	const u8_t *static_val;
	/**静态OOB值长度*/
	u8_t        static_val_len;

	/**支持的输出OOB的最大大小*/
	u8_t        output_size;
	/**支持的输出OOB操作*/
	u16_t       output_actions;

	/* 支持的最大输入OOB大小*/
	u8_t        input_size;
	/**支持的输入OOB操作*/
	u16_t       input_actions;

	/** @brief 请求输出数字。
	 *
	 *  此回调通知应用程序应该使用给定的操作输出给定的数字。
	 *
	 *  @param act 用于输出数字的操作。
	 *  @param num 要输出的编号。
	 *
	 *  @return 成功归零，否则为负错误代码
	 */
	int         (*output_number)(bt_mesh_output_action_t act, u32_t num);

	/** @brief 请求输出字符串。
	 *
	 *  此回调通知应用程序它应该向用户显示给定的字符串。
	 *
	 *  @param str 要显示的字符串。
	 *
	 *  @return 成功归零，否则为负错误代码
	 */
	int         (*output_string)(const char *str);

	/** @brief 请求输入。
	 *
	 *  此回调通知应用程序，它应该使用给定的操作请求用户输入。请求的输入将是字符串或数字，因此，一旦从用户获取数据，应用程序就需要调用bt_mesh_input_string（）或bt_mesh_input_number（）函数。
	 *
	 *  @param act 输入数据的动作。
	 *  @param num 输入数据的最大大小。
	 *
	 *  @return 成功归零，否则为负错误代码
	 */
	int         (*input)(bt_mesh_input_action_t act, u8_t size);

	/** @brief 另一台设备完成了OOB输入。
	 *
	 * 此回调通知应用程序，当另一方完成OOB输入时，它应该停止显示其输出OOB值。
	 */
	void 	    (*input_complete)(void);

	/** @brief 已收到未设置的信标。
	 *
	 * 此回调通知应用程序已收到未设置的信标。
	 *
	 * @param uuid UUID
	 * @param oob_info OOB信息
	 * @param uri_hash 指向URI哈希值的指针。如果信标中不存在哈希，则为NULL。
	 */
	void        (*unprovisioned_beacon)(u8_t uuid[16],
					    bt_mesh_prov_oob_info_t oob_info,
					    u32_t *uri_hash);

	/** @brief 设置链接已打开。
	 *
	 *  此回调通知应用程序已在给定的供应承载上打开供应链路。
	 *
	 *  @param bearer 提供承载。
	 */
	void        (*link_open)(bt_mesh_prov_bearer_t bearer);

	/** @brief 设置链接已关闭。
	 *
	 *  此回调通知应用程序给定供应承载上的供应链路已关闭。
	 *
	 *  @param bearer 提供承载。
	 */
	void        (*link_close)(bt_mesh_prov_bearer_t bearer);

	/** @brief 设置已完成。
	 *
	 *  此回调通知应用程序配置已成功完成，并且已为本地节点分配了指定的NetKeyIndex和主要元素地址。
	 *
	 *  @param net_idx 设置期间提供的NetKeyIndex。
	 *  @param addr 主要元素地址。
	 */
	void        (*complete)(u16_t net_idx, u16_t addr);

	/** @brief 已将新节点添加到配置数据库。
	 *
	 *  此回调通知应用程序配置已成功完成，并且节点已分配指定的NetKeyIndex和主元素地址。
	 *
	 *  @param net_idx 设置期间提供的NetKeyIndex。
	 *  @param addr 主要元素地址。
	 *  @param num_elem 此节点具有的元素数。
	 */
	void        (*node_added)(u16_t net_idx, u16_t addr, u8_t num_elem);

	/** @brief 节点已重置。
	 *
	 *  此回调通知应用程序本地节点已重置，需要重新配置。节点不会自动通告为未配置，而是需要调用bt_mesh_prov_enable（）API以在一个或多个配置承载上启用未配置的通告。
	 */
	void        (*reset)(void);
};

/** @brief 提供配置输入OOB字符串。
 *
 *  这是在使用bt_mesh_ENDER_STRING作为操作调用bt_mesh_prov输入回调后调用的。
 *
 *  @param str 一串
 *
 *  @return 成功时为零，否则为（负）错误代码。
 */
int bt_mesh_input_string(const char *str);

/** @brief 提供供应输入OOB编号。
 *
 *  这是在使用bt_mesh_ENDER_NUMBER作为操作调用bt_mesh_prov输入回调后调用的。
 *
 *  @param num 数字
 *
 *  @return 成功时为零，否则为（负）错误代码。
 */
int bt_mesh_input_number(u32_t num);

/** @brief 启用特定的资源调配承载
 *
 *  启用一个或多个配置承载。
 *
 *  @param bearers 按位或配置承载。
 *
 *  @return 成功时为零，否则为（负）错误代码。
 */
int bt_mesh_prov_enable(bt_mesh_prov_bearer_t bearers);

/** @brief 禁用特定配置承载
 *
 *  禁用一个或多个配置承载。
 *
 *  @param bearers 按位或配置承载。
 *
 *  @return 成功时为零，否则为（负）错误代码。
 */
int bt_mesh_prov_disable(bt_mesh_prov_bearer_t bearers);

/**
 * @}
 */

/**
 * @brief 蓝牙网格
 * @defgroup bt_mesh蓝牙网格
 * @ingroup 蓝牙@{
 */

/* 主要网络密钥索引*/
#define BT_MESH_NET_PRIMARY                 0x000

#define BT_MESH_RELAY_DISABLED              0x00
#define BT_MESH_RELAY_ENABLED               0x01
#define BT_MESH_RELAY_NOT_SUPPORTED         0x02

#define BT_MESH_BEACON_DISABLED             0x00
#define BT_MESH_BEACON_ENABLED              0x01

#define BT_MESH_GATT_PROXY_DISABLED         0x00
#define BT_MESH_GATT_PROXY_ENABLED          0x01
#define BT_MESH_GATT_PROXY_NOT_SUPPORTED    0x02

#define BT_MESH_FRIEND_DISABLED             0x00
#define BT_MESH_FRIEND_ENABLED              0x01
#define BT_MESH_FRIEND_NOT_SUPPORTED        0x02

#define BT_MESH_NODE_IDENTITY_STOPPED       0x00
#define BT_MESH_NODE_IDENTITY_RUNNING       0x01
#define BT_MESH_NODE_IDENTITY_NOT_SUPPORTED 0x02

/* 特征*/
#define BT_MESH_FEAT_RELAY                  BIT(0)
#define BT_MESH_FEAT_PROXY                  BIT(1)
#define BT_MESH_FEAT_FRIEND                 BIT(2)
#define BT_MESH_FEAT_LOW_POWER              BIT(3)
#define BT_MESH_FEAT_SUPPORTED              (BT_MESH_FEAT_RELAY |   \
					     BT_MESH_FEAT_PROXY |   \
					     BT_MESH_FEAT_FRIEND |  \
					     BT_MESH_FEAT_LOW_POWER)

/** @brief 初始化网格支持
 *
 *  调用此API后，节点不会自动通告为未配置，而是需要调用bt_mesh_prov_enable（）API以在一个或多个配置承载上启用未配置的通告。
 *
 *  @param own_addr_type 节点地址类型
 *  @param prov 节点配置信息。
 *  @param comp 节点组成。
 *
 *  @return 成功时为零，否则为（负）错误代码。
 */
int bt_mesh_init(u8_t own_addr_type,
		 const struct bt_mesh_prov *prov,
		 const struct bt_mesh_comp *comp);

/** @brief 重置本地网格节点的状态。
 *
 *  重置节点的状态，这意味着需要重新配置它才能再次成为网状网络中的活动节点。
 *
 *  调用此API后，节点不会自动通告为未配置，而是需要调用bt_mesh_prov_enable（）API以在一个或多个配置承载上启用未配置的通告。
 *
 */
void bt_mesh_reset(void);

/** @brief 暂时挂起网格网络。
 *
 *  此API可用于节能目的，但用户应注意，让本地节点长时间挂起可能会导致其与Mesh网络永久断开连接。如果可能的话，应该使用友谊功能，将节点变成低功耗节点。
 *
 *  @return 成功时为0，失败时为（负）错误代码。
 */
int bt_mesh_suspend(void);

/** @brief 恢复挂起的网状网络。
 *
 *  在使用bt_mesh_suspend（）API暂停本地节点后，此API将恢复本地节点。
 *
 *  @return 成功时为0，失败时为（负）错误代码。
 */
int bt_mesh_resume(void);

/** @brief 设置本地网格节点。
 *
 *  应用程序通常不应直接使用此API。唯一的例外是出于测试目的，需要手动配置，而无需实际的外部配置程序。
 *
 *  @param net_key  网络密钥
 *  @param net_idx  网络密钥索引
 *  @param flags    设置标志
 *  @param iv_index IV索引
 *  @param addr     主要元素地址
 *  @param dev_key  设备密钥
 *
 *  @return 成功时为零，否则为（负）错误代码。
 */
int bt_mesh_provision(const u8_t net_key[16], u16_t net_idx,
		      u8_t flags, u32_t iv_index, u16_t addr,
		      const u8_t dev_key[16]);

/** @brief 使用PB-ADV配置网格节点
 *
 * @param uuid    UUID
 * @param net_idx 网络密钥索引
 * @param addr    要分配给远程设备的地址。如果addr为0，则将选择最低可用地址。
 * @param attention_duration 要发送到远程设备的关注持续时间
 *
 * @return 成功时为零，否则为（负）错误代码。
 */
int bt_mesh_provision_adv(const u8_t uuid[16], u16_t net_idx, u16_t addr,
			  u8_t attention_duration);

/** @brief 检查是否已配置本地节点。
 *
 *  此API可用于检查本地节点是否已配置。例如，确定闪存中是否存在存储的网络，即在调用settings_load（）后网络是否已恢复，这可能很有帮助。
 *
 *  @return 如果已配置节点，则为True。否则为False。
 */
bool bt_mesh_is_provisioned(void);

/** @brief 切换IV Update测试模式
 *
 *  只有在Kconfig中启用了IV Update测试模式时，此API才可用。它是通过大多数IV Update资格测试用例所必需的。
 *
 *  @param enable true表示启用IV Update测试模式，false表示禁用。
 */
void bt_mesh_iv_update_test(bool enable);

/** @brief 切换IV更新状态
 *
 *  只有在Kconfig中启用了IV Update测试模式时，此API才可用。它是通过大多数IV Update资格测试用例所必需的。
 *
 *  @return 如果进入IV Update In Progress状态，则为true，否则为false。
 */
bool bt_mesh_iv_update(void);

/** @brief 切换本地设备的低功耗功能
 *
 *  启用或禁用本地设备的低功耗功能。这是一个运行时功能，因为设备可能希望更改此功能，例如，基于插入稳定电源或使用电池电源运行。
 *
 *  @param enable  true表示启用LPN功能，false表示禁用LPN功能。
 *
 *  @return 成功时为零，否则为（负）错误代码。
 */
int bt_mesh_lpn_set(bool enable);

/** @brief 发送朋友投票消息。
 *
 *  向此节点的好友发送好友轮询消息。如果没有建立友谊，函数将返回错误。
 *
 *  @return 成功时为零，否则为（负）错误代码。
 */
int bt_mesh_lpn_poll(void);

/** @brief 注册友谊更改的回调。
 *
 *  注册一个回调，当友谊建立或丢失时将调用该回调。
 *
 *  @param cb 当友谊状态更改时调用的函数。
 */
void bt_mesh_lpn_set_cb(void (*cb)(u16_t friend_addr, bool established));

#ifdef __cplusplus
}
#endif

/**
 * @}
 */

#endif /* __BT_MESH_MAIN_H */

