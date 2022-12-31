/*  蓝牙网格*/

/*
 * 版权所有（c）2017 Intel Corporation
 *
 * SPDX许可证标识符：Apache-2.0
 */

#ifndef __NET_H__
#define __NET_H__

#define BT_MESH_NET_FLAG_KR       BIT(0)
#define BT_MESH_NET_FLAG_IVU      BIT(1)

#define BT_MESH_KR_NORMAL         0x00
#define BT_MESH_KR_PHASE_1        0x01
#define BT_MESH_KR_PHASE_2        0x02
#define BT_MESH_KR_PHASE_3        0x03

#define BT_MESH_IV_UPDATE(flags)   ((flags >> 1) & 0x01)
#define BT_MESH_KEY_REFRESH(flags) (flags & 0x01)

#include <stdbool.h>
#include "atomic.h"
#include "mesh/mesh.h"
#include "mesh/glue.h"

/* 更新IVU持续时间间隔多少小时*/
#define BT_MESH_IVU_MIN_HOURS      96
#define BT_MESH_IVU_HOURS          (BT_MESH_IVU_MIN_HOURS /     \
				    CONFIG_BT_MESH_IVU_DIVIDER)
#define BT_MESH_IVU_TIMEOUT        K_HOURS(BT_MESH_IVU_HOURS)

struct bt_mesh_app_key {
	u16_t net_idx;
	u16_t app_idx;
	bool  updated;
	struct bt_mesh_app_keys {
		u8_t id;
		u8_t val[16];
	} keys[2];
};

struct bt_mesh_node {
	u16_t addr;
	u16_t net_idx;
	u8_t  dev_key[16];
	u8_t  num_elem;
};

struct bt_mesh_subnet {
	u32_t beacon_sent;        /* 上次发送的信标的时间戳*/
	u8_t  beacons_last;       /* 上一个观测窗期间的信标数量
				   */
	u8_t  beacons_cur;        /* 当前正在运行的窗口期间观察到的信标数。
				   */

	u8_t  beacon_cache[21];   /* 缓存的上次验证的信标*/

	u16_t net_idx;            /* 网络密钥索引*/

	bool  kr_flag;            /* 关键点刷新标志*/
	u8_t  kr_phase;           /* 密钥刷新阶段*/

	u8_t  node_id;            /* 节点标识状态*/
	u32_t node_id_start;      /* 节点标识开始时间戳*/

	u8_t  auth[8];            /* 信标验证值*/

	struct bt_mesh_subnet_keys {
		u8_t net[16];       /* 网络密钥*/
		u8_t nid;           /* NID */
		u8_t enc[16];       /* 加密密钥*/
		u8_t net_id[8];     /* 网络ID*/
#if (MYNEWT_VAL(BLE_MESH_GATT_PROXY))
		u8_t identity[16];  /* 身份密钥*/
#endif
		u8_t privacy[16];   /* 隐私密钥*/
		u8_t beacon[16];    /* 信标键*/
	} keys[2];
};

struct bt_mesh_rpl {
	u16_t src;
	bool  old_iv;
#if (MYNEWT_VAL(BLE_MESH_SETTINGS))
	bool  store;
#endif
	u32_t seq;
};

#if MYNEWT_VAL(BLE_MESH_FRIEND)
#define FRIEND_SEG_RX MYNEWT_VAL(BLE_MESH_FRIEND_SEG_RX)
#define FRIEND_SUB_LIST_SIZE MYNEWT_VAL(BLE_MESH_FRIEND_SUB_LIST_SIZE)
#else
#define FRIEND_SEG_RX 0
#define FRIEND_SUB_LIST_SIZE 0
#endif

struct bt_mesh_friend {
	u16_t lpn;
	u8_t  recv_delay;
	u8_t  fsn:1,
	      send_last:1,
	      pending_req:1,
	      sec_update:1,
	      pending_buf:1,
	      valid:1,
	      established:1;
	s32_t poll_to;
	u8_t  num_elem;
	u16_t lpn_counter;
	u16_t counter;

	u16_t net_idx;

	u16_t sub_list[FRIEND_SUB_LIST_SIZE];

	struct k_delayed_work timer;

	struct bt_mesh_friend_seg {
		struct net_buf_slist_t queue;

		/* 队列中的目标段数，即不一定是当前段数。这用于计算朋友队列可用空间。
		 */
		u8_t        seg_count;
	} seg[FRIEND_SEG_RX];

	struct os_mbuf *last;

	struct net_buf_slist_t queue;
	u32_t queue_size;

	/* 好友清除程序*/
	struct {
		u32_t start;                  /* 清除程序开始*/
		u16_t frnd;                   /* 上一位朋友的地址*/
		u16_t repeat_sec;             /* 重复超时（秒）*/
		struct k_delayed_work timer;  /* 重复计时器*/
	} clear;
};

#if (MYNEWT_VAL(BLE_MESH_LOW_POWER))
#define LPN_GROUPS CONFIG_BT_MESH_LPN_GROUPS
#else
#define LPN_GROUPS 0
#endif

/* 低功耗节点状态*/
struct bt_mesh_lpn {
	enum __packed {
		BT_MESH_LPN_DISABLED,     /* LPN功能已禁用*/
		BT_MESH_LPN_CLEAR,        /* 正在清除*/
		BT_MESH_LPN_TIMER,        /* 等待自动计时器到期*/
		BT_MESH_LPN_ENABLED,      /* 已启用LPN，但没有朋友*/
		BT_MESH_LPN_REQ_WAIT,     /* 在扫描优惠之前等待*/
		BT_MESH_LPN_WAIT_OFFER,   /* 已发送好友请求*/
		BT_MESH_LPN_ESTABLISHED,  /* 建立友谊*/
		BT_MESH_LPN_RECV_DELAY,   /* 轮询已发送，等待ReceiveDelay*/
		BT_MESH_LPN_WAIT_UPDATE,  /* 正在等待更新或消息*/
	} state;

	/* 交易号（用于订阅列表）*/
	u8_t xact_next;
	u8_t xact_pending;
	u8_t sent_req;

	/* 我们是LPN时朋友的地址。如果我们还没有朋友，则未分配。
	 */
	u16_t frnd;

	/* 朋友提供的价值*/
	u8_t  recv_win;

	u8_t  req_attempts;     /* 请求尝试次数*/

	s32_t poll_timeout;

	u8_t  groups_changed:1, /* 好友订阅列表需要更新*/
	      pending_poll:1,   /* 订阅后发送的投票*/
	      disable:1,        /* 清除后禁用LPN*/
	      fsn:1,            /* 好友序列号*/
	      established:1,    /* 建立友谊*/
	      clear_success:1;  /* 收到好友清除确认*/

	/* 好友队列大小*/
	u8_t  queue_size;

	/* LPN计数器*/
	u16_t counter;

	/* 此LPN的前朋友*/
	u16_t old_friend;

	/* 上次广告数据包报告的持续时间*/
	u16_t adv_duration;

	/* 下一个LPN相关动作计时器*/
	struct k_delayed_work timer;

	/* 订阅的组*/
	u16_t groups[LPN_GROUPS];

	/* 用于跟踪朋友知道哪些组的位字段*/
	ATOMIC_DEFINE(added, LPN_GROUPS);
	ATOMIC_DEFINE(pending, LPN_GROUPS);
	ATOMIC_DEFINE(to_remove, LPN_GROUPS);
};

/* bt_mesh_net中。旗帜*/
enum {
	BT_MESH_VALID,           /* 我们已配置*/
	BT_MESH_SUSPENDED,       /* 网络暂时挂起*/
	BT_MESH_IVU_IN_PROGRESS, /* IV正在更新*/
	BT_MESH_IVU_INITIATOR,   /* 四、我们发起的更新*/
	BT_MESH_IVU_TEST,        /* 四、更新测试模式*/
	BT_MESH_IVU_PENDING,     /* SDU正在阻止更新*/

	/* 挂起的存储操作，必须位于前32个标志内*/
	BT_MESH_RPL_PENDING,
	BT_MESH_KEYS_PENDING,
	BT_MESH_NET_PENDING,
	BT_MESH_IV_PENDING,
	BT_MESH_SEQ_PENDING,
	BT_MESH_HB_PUB_PENDING,
	BT_MESH_CFG_PENDING,
	BT_MESH_MOD_PENDING,
	BT_MESH_VA_PENDING,
	BT_MESH_NODES_PENDING,

	/* 不要触摸-故意最后*/
	BT_MESH_FLAG_COUNT,
};

struct bt_mesh_net {
	u32_t iv_index; /* 当前IV索引*/
	u32_t seq;      /* 下一个输出序列号（24位）*/

	ATOMIC_DEFINE(flags, BT_MESH_FLAG_COUNT);

	/* 本地网络接口*/
	struct ble_npl_callout local_work;
	struct net_buf_slist_t local_queue;

#if MYNEWT_VAL(BLE_MESH_FRIEND)
	/* 好友状态，对于我们所属的每个LPN来说都是独一无二的*/
	struct bt_mesh_friend frnd[MYNEWT_VAL(BLE_MESH_FRIEND_LPN_COUNT)];
#endif

#if (MYNEWT_VAL(BLE_MESH_LOW_POWER))
	struct bt_mesh_lpn lpn;  /* 低功耗节点状态*/
#endif

	/* 当前IV更新状态的小时数*/
	u8_t  ivu_duration;

	/* 跟踪当前IV更新状态持续时间的计时器*/
	struct k_delayed_work ivu_timer;

	u8_t dev_key[16];

#if MYNEWT_VAL(BLE_MESH_PROVISIONER)
	struct bt_mesh_node nodes[MYNEWT_VAL(BLE_MESH_NODE_COUNT)];
#endif

	struct bt_mesh_app_key app_keys[MYNEWT_VAL(BLE_MESH_APP_KEY_COUNT)];

	struct bt_mesh_subnet sub[MYNEWT_VAL(BLE_MESH_SUBNET_COUNT)];

	struct bt_mesh_rpl rpl[MYNEWT_VAL(BLE_MESH_CRPL)];
};

/* 网络接口*/
enum bt_mesh_net_if {
	BT_MESH_NET_IF_ADV,
	BT_MESH_NET_IF_LOCAL,
	BT_MESH_NET_IF_PROXY,
	BT_MESH_NET_IF_PROXY_CFG,
};

/* 解码网络/传输数据的上下文*/
struct bt_mesh_net_rx {
	struct bt_mesh_subnet *sub;
	struct bt_mesh_msg_ctx ctx;
	u32_t  seq;            /* 序列号*/
	u8_t   old_iv:1,       /* 使用iv_index-1*/
	       new_key:1,      /* 数据已使用更新的密钥加密*/
	       friend_cred:1,  /* 数据已使用好友信用进行加密*/
	       ctl:1,          /* 网络控制*/
	       net_if:2,       /* 网络接口*/
	       local_match:1,  /* 匹配本地元素*/
	       friend_match:1; /* 匹配了我们是朋友的LPN*/
	u16_t  msg_cache_idx;  /* 邮件缓存中的条目索引*/
};

/* 网络/传输数据的编码上下文*/
struct bt_mesh_net_tx {
	struct bt_mesh_subnet *sub;
	struct bt_mesh_msg_ctx *ctx;
	u16_t src;
	u8_t  xmit;
	u8_t  friend_cred:1,
	      aszmic:1,
	      aid:6;
};

extern struct bt_mesh_net bt_mesh;

#define BT_MESH_NET_IVI_TX (bt_mesh.iv_index - \
			    atomic_test_bit(bt_mesh.flags, \
					    BT_MESH_IVU_IN_PROGRESS))
#define BT_MESH_NET_IVI_RX(rx) (bt_mesh.iv_index - (rx)->old_iv)

#define BT_MESH_NET_HDR_LEN 9

int bt_mesh_net_keys_create(struct bt_mesh_subnet_keys *keys,
			    const u8_t key[16]);

int bt_mesh_net_create(u16_t idx, u8_t flags, const u8_t key[16],
		       u32_t iv_index);

u8_t bt_mesh_net_flags(struct bt_mesh_subnet *sub);

bool bt_mesh_kr_update(struct bt_mesh_subnet *sub, u8_t new_kr, bool new_key);

void bt_mesh_net_revoke_keys(struct bt_mesh_subnet *sub);

int bt_mesh_net_beacon_update(struct bt_mesh_subnet *sub);

void bt_mesh_rpl_reset(void);

bool bt_mesh_net_iv_update(u32_t iv_index, bool iv_update);

void bt_mesh_net_sec_update(struct bt_mesh_subnet *sub);

struct bt_mesh_subnet *bt_mesh_subnet_get(u16_t net_idx);

struct bt_mesh_subnet *bt_mesh_subnet_find(const u8_t net_id[8], u8_t flags,
					   u32_t iv_index, const u8_t auth[8],
					   bool *new_key);

int bt_mesh_net_encode(struct bt_mesh_net_tx *tx, struct os_mbuf *buf,
		       bool proxy);

int bt_mesh_net_send(struct bt_mesh_net_tx *tx, struct os_mbuf *buf,
		     const struct bt_mesh_send_cb *cb, void *cb_data);

int bt_mesh_net_resend(struct bt_mesh_subnet *sub, struct os_mbuf *buf,
		       bool new_key, const struct bt_mesh_send_cb *cb,
		       void *cb_data);

int bt_mesh_net_decode(struct os_mbuf *data, enum bt_mesh_net_if net_if,
		       struct bt_mesh_net_rx *rx, struct os_mbuf *buf);

void bt_mesh_net_recv(struct os_mbuf *data, s8_t rssi,
		      enum bt_mesh_net_if net_if);

u32_t bt_mesh_next_seq(void);

void bt_mesh_net_start(void);

void bt_mesh_net_init(void);
void bt_mesh_net_header_parse(struct os_mbuf *buf,
			      struct bt_mesh_net_rx *rx);

/* 友谊证书管理*/
struct friend_cred {
	u16_t net_idx;
	u16_t addr;

	u16_t lpn_counter;
	u16_t frnd_counter;

	struct {
		u8_t nid;         /* NID */
		u8_t enc[16];     /* 加密密钥*/
		u8_t privacy[16]; /* 隐私密钥*/
	} cred[2];
};

int friend_cred_get(struct bt_mesh_subnet *sub, u16_t addr, u8_t *nid,
			    const u8_t **enc, const u8_t **priv);
int friend_cred_set(struct friend_cred *cred, u8_t idx, const u8_t net_key[16]);
void friend_cred_refresh(u16_t net_idx);
int friend_cred_update(struct bt_mesh_subnet *sub);
struct friend_cred *friend_cred_create(struct bt_mesh_subnet *sub, u16_t addr,
				       u16_t lpn_counter, u16_t frnd_counter);
void friend_cred_clear(struct friend_cred *cred);
int friend_cred_del(u16_t net_idx, u16_t addr);

static inline void send_cb_finalize(const struct bt_mesh_send_cb *cb,
				    void *cb_data)
{
	if (!cb) {
		return;
	}

	if (cb->start) {
		cb->start(0, 0, cb_data);
	}

	if (cb->end) {
		cb->end(0, cb_data);
	}
}

#endif

