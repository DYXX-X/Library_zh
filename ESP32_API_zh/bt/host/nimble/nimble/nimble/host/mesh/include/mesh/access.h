/** @file
 *  @brief 蓝牙网格接入层API。
 */

/*
 * 版权所有（c）2017 Intel Corporation
 *
 * SPDX许可证标识符：Apache-2.0
 */
#ifndef __BT_MESH_ACCESS_H
#define __BT_MESH_ACCESS_H

/**
 * @brief 蓝牙网格接入层
 * @defgroup bt_mesh_access蓝牙网格访问层
 * @ingroup bt_网格@{
 */

#ifdef __cplusplus
extern "C" {
#endif

#define BT_MESH_ADDR_UNASSIGNED   0x0000
#define BT_MESH_ADDR_ALL_NODES    0xffff
#define BT_MESH_ADDR_PROXIES      0xfffc
#define BT_MESH_ADDR_FRIENDS      0xfffd
#define BT_MESH_ADDR_RELAYS       0xfffe

#define BT_MESH_KEY_UNUSED        0xffff
#define BT_MESH_KEY_DEV           0xfffe
#define BT_MESH_KEY_DEV_LOCAL     BT_MESH_KEY_DEV
#define BT_MESH_KEY_DEV_REMOTE    0xfffd
#define BT_MESH_KEY_DEV_ANY       0xfffc

#define BT_MESH_IS_DEV_KEY(key) (key == BT_MESH_KEY_DEV_LOCAL || \
				 key == BT_MESH_KEY_DEV_REMOTE)

/** 用于在数组中定义网格元素的助手。
 *
 *  如果元素没有SIG或Vendor模型，则可以改用帮助宏BT_MESH_MODEL_NONE。
 *
 *  @param _loc       位置描述符。
 *  @param _mods      模型阵列。
 *  @param _vnd_mods  供应商模型阵列。
 */
#define BT_MESH_ELEM(_loc, _mods, _vnd_mods)        \
{                                                   \
	.loc              = (_loc),                 \
	.model_count      = ARRAY_SIZE(_mods),      \
	.models           = (_mods),                \
	.vnd_model_count  = ARRAY_SIZE(_vnd_mods),  \
	.vnd_models       = (_vnd_mods),            \
}

/**描述网格元素的抽象*/
struct bt_mesh_elem {
	/* 单播地址。在配置期间在运行时设置。*/
	u16_t addr;

	/* 位置描述符（GATT蓝牙命名空间描述符）*/
	const u16_t loc;

	const u8_t model_count;
	const u8_t vnd_model_count;

	struct bt_mesh_model * const models;
	struct bt_mesh_model * const vnd_models;
};

/* 基础模型*/
#define BT_MESH_MODEL_ID_CFG_SRV                   0x0000
#define BT_MESH_MODEL_ID_CFG_CLI                   0x0001
#define BT_MESH_MODEL_ID_HEALTH_SRV                0x0002
#define BT_MESH_MODEL_ID_HEALTH_CLI                0x0003

/* 网格模型规范中的模型*/
#define BT_MESH_MODEL_ID_GEN_ONOFF_SRV             0x1000
#define BT_MESH_MODEL_ID_GEN_ONOFF_CLI             0x1001
#define BT_MESH_MODEL_ID_GEN_LEVEL_SRV             0x1002
#define BT_MESH_MODEL_ID_GEN_LEVEL_CLI             0x1003
#define BT_MESH_MODEL_ID_GEN_DEF_TRANS_TIME_SRV    0x1004
#define BT_MESH_MODEL_ID_GEN_DEF_TRANS_TIME_CLI    0x1005
#define BT_MESH_MODEL_ID_GEN_POWER_ONOFF_SRV       0x1006
#define BT_MESH_MODEL_ID_GEN_POWER_ONOFF_SETUP_SRV 0x1007
#define BT_MESH_MODEL_ID_GEN_POWER_ONOFF_CLI       0x1008
#define BT_MESH_MODEL_ID_GEN_POWER_LEVEL_SRV       0x1009
#define BT_MESH_MODEL_ID_GEN_POWER_LEVEL_SETUP_SRV 0x100a
#define BT_MESH_MODEL_ID_GEN_POWER_LEVEL_CLI       0x100b
#define BT_MESH_MODEL_ID_GEN_BATTERY_SRV           0x100c
#define BT_MESH_MODEL_ID_GEN_BATTERY_CLI           0x100d
#define BT_MESH_MODEL_ID_GEN_LOCATION_SRV          0x100e
#define BT_MESH_MODEL_ID_GEN_LOCATION_SETUPSRV     0x100f
#define BT_MESH_MODEL_ID_GEN_LOCATION_CLI          0x1010
#define BT_MESH_MODEL_ID_GEN_ADMIN_PROP_SRV        0x1011
#define BT_MESH_MODEL_ID_GEN_MANUFACTURER_PROP_SRV 0x1012
#define BT_MESH_MODEL_ID_GEN_USER_PROP_SRV         0x1013
#define BT_MESH_MODEL_ID_GEN_CLIENT_PROP_SRV       0x1014
#define BT_MESH_MODEL_ID_GEN_PROP_CLI              0x1015
#define BT_MESH_MODEL_ID_SENSOR_SRV                0x1100
#define BT_MESH_MODEL_ID_SENSOR_SETUP_SRV          0x1101
#define BT_MESH_MODEL_ID_SENSOR_CLI                0x1102
#define BT_MESH_MODEL_ID_TIME_SRV                  0x1200
#define BT_MESH_MODEL_ID_TIME_SETUP_SRV            0x1201
#define BT_MESH_MODEL_ID_TIME_CLI                  0x1202
#define BT_MESH_MODEL_ID_SCENE_SRV                 0x1203
#define BT_MESH_MODEL_ID_SCENE_SETUP_SRV           0x1204
#define BT_MESH_MODEL_ID_SCENE_CLI                 0x1205
#define BT_MESH_MODEL_ID_SCHEDULER_SRV             0x1206
#define BT_MESH_MODEL_ID_SCHEDULER_SETUP_SRV       0x1207
#define BT_MESH_MODEL_ID_SCHEDULER_CLI             0x1208
#define BT_MESH_MODEL_ID_LIGHT_LIGHTNESS_SRV       0x1300
#define BT_MESH_MODEL_ID_LIGHT_LIGHTNESS_SETUP_SRV 0x1301
#define BT_MESH_MODEL_ID_LIGHT_LIGHTNESS_CLI       0x1302
#define BT_MESH_MODEL_ID_LIGHT_CTL_SRV             0x1303
#define BT_MESH_MODEL_ID_LIGHT_CTL_SETUP_SRV       0x1304
#define BT_MESH_MODEL_ID_LIGHT_CTL_CLI             0x1305
#define BT_MESH_MODEL_ID_LIGHT_CTL_TEMP_SRV        0x1306
#define BT_MESH_MODEL_ID_LIGHT_HSL_SRV             0x1307
#define BT_MESH_MODEL_ID_LIGHT_HSL_SETUP_SRV       0x1308
#define BT_MESH_MODEL_ID_LIGHT_HSL_CLI             0x1309
#define BT_MESH_MODEL_ID_LIGHT_HSL_HUE_SRV         0x130a
#define BT_MESH_MODEL_ID_LIGHT_HSL_SAT_SRV         0x130b
#define BT_MESH_MODEL_ID_LIGHT_XYL_SRV             0x130c
#define BT_MESH_MODEL_ID_LIGHT_XYL_SETUP_SRV       0x130d
#define BT_MESH_MODEL_ID_LIGHT_XYL_CLI             0x130e
#define BT_MESH_MODEL_ID_LIGHT_LC_SRV              0x130f
#define BT_MESH_MODEL_ID_LIGHT_LC_SETUPSRV         0x1310
#define BT_MESH_MODEL_ID_LIGHT_LC_CLI              0x1311

/**消息发送上下文。*/
struct bt_mesh_msg_ctx {
	/**要发送消息的子网的NetKey索引。*/
	u16_t net_idx;

	/**用于加密消息的AppKey索引。*/
	u16_t app_idx;

	/**远程地址。*/
	u16_t addr;

	/**接收消息的目标地址。不用于发送。*/
	u16_t recv_dst;

	/**接收分组的RSSI。不用于发送。*/
	s8_t  recv_rssi;

	/**收到TTL值。不用于发送。*/
	u8_t  recv_ttl;

	/**使用段确认强制可靠发送*/
	bool  send_rel;

	/**TTL或BT_MESH_TTL_DEFAULT（默认TTL）。*/
	u8_t  send_ttl;
};

struct bt_mesh_model_op {
	/* 使用BT_MESH_MODEL_OP_*宏编码的OpCode*/
	const u32_t  opcode;

	/* 所需的最小消息长度*/
	const size_t min_len;

	/* 操作码的消息处理程序*/
	void (*const func)(struct bt_mesh_model *model,
			   struct bt_mesh_msg_ctx *ctx,
			   struct os_mbuf *buf);
};

#define BT_MESH_MODEL_OP_1(b0) (b0)
#define BT_MESH_MODEL_OP_2(b0, b1) (((b0) << 8) | (b1))
#define BT_MESH_MODEL_OP_3(b0, cid) ((((b0) << 16) | 0xc00000) | (cid))

#define BT_MESH_MODEL_OP_END { 0, 0, NULL }
#define BT_MESH_MODEL_NO_OPS ((struct bt_mesh_model_op []) \
			      { BT_MESH_MODEL_OP_END })

/**定义空模型数组的助手*/
#define BT_MESH_MODEL_NONE ((struct bt_mesh_model []){})

/**短网眼MIC的长度。*/
#define BT_MESH_MIC_SHORT 4
/**长网眼MIC的长度。*/
#define BT_MESH_MIC_LONG 8

/** @def BT_MESH_MODEL_OP_LEN
 *
 * @brief 帮助程序确定操作码的长度。
 *
 * @param _op 操作码。
 */
#define BT_MESH_MODEL_OP_LEN(_op) ((_op) <= 0xff ? 1 : (_op) <= 0xffff ? 2 : 3)

/** @def BT_MESH_MODEL_BUF_LEN
 *
 * @brief 模型消息缓冲区长度的帮助程序。
 *
 * 返回Mesh模型消息缓冲区的长度，包括操作码长度和短MIC。
 *
 * @param _op 消息的操作码。
 * @param _payload_len 模型有效载荷的长度。
 */
#define BT_MESH_MODEL_BUF_LEN(_op, _payload_len)                               \
	(BT_MESH_MODEL_OP_LEN(_op) + (_payload_len) + BT_MESH_MIC_SHORT)

/** @def BT_MESH_MODEL_BUF_LEN_LONG_MIC
 *
 * @brief 模型消息缓冲区长度的帮助程序。
 *
 * 返回Mesh模型消息缓冲区的长度，包括操作码长度和长MIC。
 *
 * @param _op 消息的操作码。
 * @param _payload_len 模型有效载荷的长度。
 */
#define BT_MESH_MODEL_BUF_LEN_LONG_MIC(_op, _payload_len)                      \
	(BT_MESH_MODEL_OP_LEN(_op) + (_payload_len) + BT_MESH_MIC_LONG)

/** @def BT_MESH_MODEL_BUF_DEFINE
 *
 * @brief 使用@ref NET_BUF_SIMPLE定义网格模型消息缓冲区。
 *
 * @param _op 消息的操作码。
 * @param _payload_len 模型消息负载的长度。
 */
#define BT_MESH_MODEL_BUF(_op, _payload_len)                      \
	NET_BUF_SIMPLE(BT_MESH_MODEL_BUF_LEN(_op, (_payload_len)))

/** @def BT_MESH_MODEL_CB
 *
 * @brief 具有回调函数的合成数据SIG模型条目。
 *
 * @param _id 型号ID。
 * @param _op 模型操作码处理程序数组。
 * @param _pub 模型发布参数。
 * @param _user_data 模型的用户数据。
 * @param _cb 回调结构，或NULL以保持无回调。
 */
#define BT_MESH_MODEL_CB(_id, _op, _pub, _user_data, _cb)                    \
{                                                                            \
	.id = (_id),                                                         \
	.op = _op,                                                           \
	.keys = { [0 ... (CONFIG_BT_MESH_MODEL_KEY_COUNT - 1)] =             \
			BT_MESH_KEY_UNUSED },                                \
	.pub = _pub,                                                         \
	.groups = { [0 ... (CONFIG_BT_MESH_MODEL_GROUP_COUNT - 1)] =         \
			BT_MESH_ADDR_UNASSIGNED },                           \
	.user_data = _user_data,                                             \
	.cb = _cb,                                                           \
}

/** @def BT_MESH_MODEL_VND_CB
 *
 * @brief 具有回调函数的合成数据供应商模型条目。
 *
 * @param _company 公司ID。
 * @param _id 型号ID。
 * @param _op 模型操作码处理程序数组。
 * @param _pub 模型发布参数。
 * @param _user_data 模型的用户数据。
 * @param _cb 回调结构，或NULL以保持无回调。
 */
#define BT_MESH_MODEL_VND_CB(_company, _id, _op, _pub, _user_data, _cb)      \
{                                                                            \
	.vnd.company = (_company),                                           \
	.vnd.id = (_id),                                                     \
	.op = _op,                                                           \
	.pub = _pub,                                                         \
	.keys = { [0 ... (CONFIG_BT_MESH_MODEL_KEY_COUNT - 1)] =             \
			BT_MESH_KEY_UNUSED },                                \
	.groups = { [0 ... (CONFIG_BT_MESH_MODEL_GROUP_COUNT - 1)] =         \
			BT_MESH_ADDR_UNASSIGNED },                           \
	.user_data = _user_data,                                             \
	.cb = _cb,                                                           \
}


/** @def BT_MESH_MODEL
 *
 * @brief 合成数据SIG模型条目。
 *
 * @param _id 型号ID。
 * @param _op 模型操作码处理程序数组。
 * @param _pub 模型发布参数。
 * @param _user_data 模型的用户数据。
 */
#define BT_MESH_MODEL(_id, _op, _pub, _user_data)                              \
	BT_MESH_MODEL_CB(_id, _op, _pub, _user_data, NULL)

/** @def BT_MESH_MODEL_VND
 *
 * @brief 组成数据供应商模型条目。
 *
 * @param _company 公司ID。
 * @param _id 型号ID。
 * @param _op 模型操作码处理程序数组。
 * @param _pub 模型发布参数。
 * @param _user_data 模型的用户数据。
 */
#define BT_MESH_MODEL_VND(_company, _id, _op, _pub, _user_data)                \
	BT_MESH_MODEL_VND_CB(_company, _id, _op, _pub, _user_data, NULL)

/** @def BT_MESH_TRANSMIT
 *
 *  @brief 编码传输计数和间隔步长。
 *
 *  @param count   重传次数（排除第一次传输）。
 *  @param int_ms  间隔步数（毫秒）。必须大于0、小于或等于320以及10的倍数。
 *
 *  @return 可以用于例如配置模型数据的默认值的网格传输值。
 */
#define BT_MESH_TRANSMIT(count, int_ms) ((count) | (((int_ms / 10) - 1) << 3))

/** @def BT_MESH_TRANSMIT_COUNT
 *
 *  @brief 根据传输值解码传输计数。
 *
 *  @param transmit 编码传输计数和间隔值。
 *
 *  @return 传输计数（实际传输为N+1）。
 */
#define BT_MESH_TRANSMIT_COUNT(transmit) (((transmit) & (u8_t)BIT_MASK(3)))

/** @def BT_MESH_TRANSMIT_INT
 *
 *  @brief 根据传输值解码传输间隔。
 *
 *  @param transmit 编码传输计数和间隔值。
 *
 *  @return 传输间隔（毫秒）。
 */
#define BT_MESH_TRANSMIT_INT(transmit) ((((transmit) >> 3) + 1) * 10)

/** @def BT_MESH_PUB_TRANSMIT
 *
 *  @brief 编码发布重新传输计数和间隔步骤。
 *
 *  @param count   重传次数（排除第一次传输）。
 *  @param int_ms  间隔步数（毫秒）。必须大于0和50的倍数。
 *
 *  @return 可以用于例如配置模型数据的默认值的网格传输值。
 */
#define BT_MESH_PUB_TRANSMIT(count, int_ms) BT_MESH_TRANSMIT(count,           \
							     (int_ms) / 5)

/** @def BT_MESH_PUB_TRANSMIT_COUNT
 *
 *  @brief 从给定值解码Pubhlish重发计数。
 *
 *  @param transmit 编码的发布重新传输计数和间隔值。
 *
 *  @return 重新传输计数（实际传输为N+1）。
 */
#define BT_MESH_PUB_TRANSMIT_COUNT(transmit) BT_MESH_TRANSMIT_COUNT(transmit)

/** @def BT_MESH_PUB_TRANSMIT_INT
 *
 *  @brief 从给定值解码发布重新传输间隔。
 *
 *  @param transmit 编码的发布重新传输计数和间隔值。
 *
 *  @return 传输间隔（毫秒）。
 */
#define BT_MESH_PUB_TRANSMIT_INT(transmit) ((((transmit) >> 3) + 1) * 50)

/**模型发布上下文。*/
struct bt_mesh_model_pub {
	/**上下文所属的模型。由堆栈初始化。*/
	struct bt_mesh_model *mod;

	u16_t addr;         /**<发布地址。*/
	u16_t key;          /**<发布AppKey索引。*/

	u8_t  ttl;          /**<发布生存时间。*/
	u8_t  retransmit;   /**<重新传输计数和间隔步骤。*/
	u8_t  period;       /**<发布期。*/
	u8_t  period_div:4, /**<本期除数。*/
	      cred:1,       /**<友谊证书标志。*/
	      fast_period:1,/**<使用FastPeriodDivisior*/
	      count:3;      /**<剩余重新传输。*/

	u32_t period_start; /**<本期开始。*/

	/** @brief 发布缓冲区，包含发布消息。
	 *
	 *  应用程序应使用有效的net_buf_simple指针初始化，例如借助net_buf_simple（）宏。在调用bt_mesh_model_publish（）API之前或发布的
	 *  @ref bt_mesh_model_pub。已调用更新回调并返回成功。缓冲区必须在函数上下文之外创建，即不能在堆栈上。通过在声明发布上下文时内联创建它，可以最方便地实现这一点：
	 *
	 *      静态结构bt_mesh_model_pub my_pub=｛.msg=NET_BUF_SIMPLE（大小），｝；
	 */
	struct os_mbuf *msg;

	/** @brief 用于更新发布缓冲区的回调。
	 *
	 *  设置为NULL时，假设模型不支持定期发布。当设置为非NULL时，将定期调用回调，并预期更新
	 *  @ref bt_mesh_model_pub。带有有效发布消息的消息。
	 *
	 *  @param mod 发布上下文所属的模型。
	 *
	 *  @return 成功时为零，否则为（负）错误代码。
	 */
	int (*update)(struct bt_mesh_model *mod);

	/**发布时段计时器。仅用于堆栈内部使用。*/
	struct k_delayed_work timer;
};

/**模型回调函数。*/
struct bt_mesh_model_cb {
	/** @brief 设置绑定到模型的用户数据的值处理程序。
	 *
	 * @sa 设置处理程序：：h_set
	 *
	 * @param model 要设置其持久数据的模型。
	 * @param val 来自后端的数据。
	 *
	 * @return 成功时为0，否则为错误。
	 */
	int (*const settings_set)(struct bt_mesh_model *model, char *val);

	/** @brief 加载所有设置后调用回调。
	 *
	 * 在完全加载设置后调用此处理程序。
	 *
	 * @sa settings_handler:：h_commit
	 *
	 * @param model 此回调所属的模型。
	 *
	 * @return 成功时为0，否则为错误。
	 */
	int (*const settings_commit)(struct bt_mesh_model *model);

	/** @brief 模型初始化回调。
	 *
	 * 在网格初始化期间对每个模型实例调用。
	 *
	 * @param model 要初始化的模型。
	 *
	 * @return 成功时为0，否则为错误。
	 */
	int (*const init)(struct bt_mesh_model *model);

	/** @brief 模型重置回调。
	 *
	 * 重置网格节点时调用。重置时删除所有模型数据，模型应清除其状态。
	 *
	 * @param model 此回调所属的模型。
	 */
	void (*const reset)(struct bt_mesh_model *model);
};

/**描述网格模型实例的抽象*/
struct bt_mesh_model {
	union {
		const u16_t id;
		struct {
			u16_t company;
			u16_t id;
		} vnd;
	};

	/* 内部信息，主要用于持久性存储*/
	u8_t  elem_idx;   /* 属于第N个元素*/
	u8_t  mod_idx;    /* 是元素中的第N个模型*/
	u16_t flags;      /* 内部记账的模型标志*/

	/* 模型出版物*/
	struct bt_mesh_model_pub * const pub;

	/* AppKey列表*/
	u16_t keys[CONFIG_BT_MESH_MODEL_KEY_COUNT];

	/* 订阅列表（组或虚拟地址）*/
	u16_t groups[CONFIG_BT_MESH_MODEL_GROUP_COUNT];

	const struct bt_mesh_model_op * const op;

	/* 模型回调结构。*/
	const struct bt_mesh_model_cb * const cb;

#if MYNEWT_VAL(BLE_MESH_MODEL_EXTENSIONS)
	/* 指向模型扩展树中下一个模型的指针。*/
	struct bt_mesh_model *next;
	/* 指向此模型扩展的第一个模型的指针。*/
	struct bt_mesh_model *extends;
#endif
	/* 特定于型号的用户数据*/
	void *user_data;
};

struct bt_mesh_send_cb {
	void (*start)(u16_t duration, int err, void *cb_data);
	void (*end)(int err, void *cb_data);
};

void bt_mesh_model_msg_init(struct os_mbuf *msg, u32_t opcode);

/**使用配置的默认TTL请求特殊TTL值*/
#define BT_MESH_TTL_DEFAULT 0xff

/**允许的最大TTL值*/
#define BT_MESH_TTL_MAX     0x7f

/**
 * @brief 发送接入层消息。
 *
 * @param model     消息所属的网格（客户端）模型。
 * @param ctx       消息上下文，包括密钥、TTL等。
 * @param msg       接入层有效载荷（要发送的实际消息）。
 * @param cb        可选的“消息已发送”回调。
 * @param cb_data   要传递给回调的用户数据。
 *
 * @return 成功时为0，失败时为（负）错误代码。
 */
int bt_mesh_model_send(struct bt_mesh_model *model,
		       struct bt_mesh_msg_ctx *ctx,
		       struct os_mbuf *msg,
		       const struct bt_mesh_send_cb *cb,
		       void *cb_data);

/**
 * @brief 发送模型发布消息。
 *
 * 在调用此函数之前，用户需要确保模型
 * publication message (@ref bt_mesh_model_pub。msg）包含要发送的有效消息。请注意，此API仅用于非周期发布。对于定期发布，应用程序只需要
 * to make sure that @ref bt_mesh_model_pub。消息包含有效消息
 * whenever the @ref bt_mesh_model_pub。调用update回调。
 *
 * @param model  发布消息的网格（客户端）模型。
 *
 * @return 成功时为0，失败时为（负）错误代码。
 */
int bt_mesh_model_publish(struct bt_mesh_model *model);

/**
 * @brief 获取模型所属的元素。
 *
 * @param mod  网格模型。
 *
 * @return 指向给定模型所属元素的指针。
 */
struct bt_mesh_elem *bt_mesh_model_elem(struct bt_mesh_model *mod);

/** @brief 查找SIG模型。
 *
 * @param elem 要在其中搜索模型的元素。
 * @param id 模型的模型ID。
 *
 * @return 指向与给定参数匹配的Mesh模型的指针，如果给定元素中不存在具有给定ID的SIG模型，则为NULL。
 */
struct bt_mesh_model *bt_mesh_model_find(const struct bt_mesh_elem *elem,
					 u16_t id);

/** @brief 查找供应商模型。
 *
 * @param elem 要在其中搜索模型的元素。
 * @param company 模型的公司ID。
 * @param id 模型的模型ID。
 *
 * @return 指向与给定参数匹配的Mesh模型的指针，如果给定元素中不存在具有给定ID的供应商模型，则为NULL。
 */
struct bt_mesh_model *bt_mesh_model_find_vnd(const struct bt_mesh_elem *elem,
					     u16_t company, u16_t id);

/** @brief 获取模型是否在设备的主要元素中。
 *
 * @param mod 网格模型。
 *
 * @return 如果模型位于主元素上，则为true，否则为false。
 */
static inline bool bt_mesh_model_in_primary(const struct bt_mesh_model *mod)
{
	return (mod->elem_idx == 0);
}

/** @brief 立即将模型的用户数据存储在持久存储中。
 *
 * @param mod 网格模型。
 * @param vnd 这是一个供应商模型。
 * @param data 要存储的模型数据，或NULL可删除任何模型数据。
 * @param data_len 模型数据的长度。
 *
 * @return 成功时为0，失败时为（负）错误代码。
 */
int bt_mesh_model_data_store(struct bt_mesh_model *mod, bool vnd,
			     const void *data, size_t data_len);

/** @brief 让一个模型扩展另一个模型。
 *
 * 可以扩展网格模型以重用其功能，从而形成更复杂的模型。网格模型可以在任何元素中扩展任意数量的模型。扩展也可以是嵌套的，即扩展另一个的模型本身也可以扩展。扩展可能不是周期性的，一个模型只能由另一个模型扩展。
 *
 * 一组相互扩展的模型形成一个模型扩展树。
 *
 * 扩展树中的所有模型都为每个元素共享一个订阅列表。接入层将利用扩展树和元素中所有模型的组合订阅列表，为模型提供扩展订阅列表容量。
 *
 * @param[in] mod 网格模型。
 * @param[in] base_mod 正在扩展的模型。
 *
 * @retval 0已成功扩展base_mod模型。
 * @retval -EALREADY base_mod模型已扩展。
 */
int bt_mesh_model_extend(struct bt_mesh_model *mod,
			 struct bt_mesh_model *base_mod);

/**节点组成*/
struct bt_mesh_comp {
	u16_t cid;
	u16_t pid;
	u16_t vid;

	size_t elem_count;
	struct bt_mesh_elem *elem;
};

#ifdef __cplusplus
}
#endif

/**
 * @}
 */

#endif /* __BT_MESH_ACCESS_H */

