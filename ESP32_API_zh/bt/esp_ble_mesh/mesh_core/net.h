/*  蓝牙网格*/

/*
 * SPDX文件版权文本：2017 Intel Corporation SPDX FileContributor:2018-2021 Espressif Systems（Shanghai）CO LTD
 *
 * SPDX许可证标识符：Apache-2.0
 */

#ifndef _NET_H_
#define _NET_H_

#include "mesh_access.h"

#ifdef __cplusplus
extern "C" {
#endif

#define BLE_MESH_NET_FLAG_KR       BIT(0)
#define BLE_MESH_NET_FLAG_IVU      BIT(1)

#define BLE_MESH_KR_NORMAL         0x00
#define BLE_MESH_KR_PHASE_1        0x01
#define BLE_MESH_KR_PHASE_2        0x02
#define BLE_MESH_KR_PHASE_3        0x03

#define BLE_MESH_IV_UPDATE(flags)   ((flags >> 1) & 0x01)
#define BLE_MESH_KEY_REFRESH(flags) (flags & 0x01)

/* 更新IVU持续时间间隔多少小时*/
#define BLE_MESH_IVU_MIN_HOURS      96
#define BLE_MESH_IVU_HOURS          (BLE_MESH_IVU_MIN_HOURS / CONFIG_BLE_MESH_IVU_DIVIDER)
#define BLE_MESH_IVU_TIMEOUT        K_HOURS(BLE_MESH_IVU_HOURS)

struct bt_mesh_app_key {
    uint16_t net_idx;
    uint16_t app_idx;
    bool     updated;
    struct bt_mesh_app_keys {
        uint8_t id;
        uint8_t val[16];
    } keys[2];
};

struct bt_mesh_subnet {
    uint32_t beacon_sent;       /* 上次发送的信标的时间戳*/
    uint8_t  beacons_last;      /* 上一个观测窗口期间的信标数量。*/
    uint8_t  beacons_cur;       /* 当前正在进行的窗口期间观察到的信标数量。*/

    uint8_t  beacon_cache[21];  /* 缓存的上次验证的信标*/

    uint16_t net_idx;           /* 网络密钥索引*/

    bool     kr_flag;           /* 关键点刷新标志*/
    uint8_t  kr_phase;          /* 密钥刷新阶段*/

    uint8_t  node_id;           /* 节点标识状态*/
    uint32_t node_id_start;     /* 节点标识开始时间戳*/

    uint8_t  auth[8];           /* 信标验证值*/

    struct bt_mesh_subnet_keys {
        uint8_t net[16];        /* 网络密钥*/
        uint8_t nid;            /* NID */
        uint8_t enc[16];        /* 加密密钥*/
        uint8_t net_id[8];      /* 网络ID*/
#if defined(CONFIG_BLE_MESH_GATT_PROXY_SERVER)
        uint8_t identity[16];   /* 身份密钥*/
#endif
        uint8_t privacy[16];    /* 隐私密钥*/
        uint8_t beacon[16];     /* 信标键*/
    } keys[2];
};

struct bt_mesh_rpl {
    uint16_t src;
    bool     old_iv;
#if defined(CONFIG_BLE_MESH_SETTINGS)
    bool     store;
#endif
    uint32_t seq;
};

#if defined(CONFIG_BLE_MESH_FRIEND)
#define FRIEND_SEG_RX           CONFIG_BLE_MESH_FRIEND_SEG_RX
#define FRIEND_SUB_LIST_SIZE    CONFIG_BLE_MESH_FRIEND_SUB_LIST_SIZE
#else
#define FRIEND_SEG_RX           0
#define FRIEND_SUB_LIST_SIZE    0
#endif

struct bt_mesh_friend {
    uint16_t lpn;
    uint8_t  recv_delay;
    uint8_t  fsn:1,
             send_last:1,
             pending_req:1,
             sec_update:1,
             pending_buf:1,
             valid:1,
             established:1;
    int32_t  poll_to;
    uint8_t  num_elem;
    uint16_t lpn_counter;
    uint16_t counter;

    uint16_t net_idx;

    uint16_t sub_list[FRIEND_SUB_LIST_SIZE];

    struct k_delayed_work timer;

    struct bt_mesh_friend_seg {
        sys_slist_t queue;

        /* 队列中的目标段数，即不一定是当前段数。这用于计算朋友队列可用空间。
         */
        uint8_t seg_count;
    } seg[FRIEND_SEG_RX];

    struct net_buf *last;

    sys_slist_t queue;
    uint32_t    queue_size;

    /* 好友清除程序*/
    struct {
        uint32_t start;               /* 清除程序开始*/
        uint16_t frnd;                /* 上一位朋友的地址*/
        uint16_t repeat_sec;          /* 重复超时（秒）*/
        struct k_delayed_work timer;  /* 重复计时器*/
    } clear;
};

#if defined(CONFIG_BLE_MESH_LOW_POWER)
#define LPN_GROUPS CONFIG_BLE_MESH_LPN_GROUPS
#else
#define LPN_GROUPS 0
#endif

/* 低功耗节点状态*/
struct bt_mesh_lpn {
    enum __packed {
        BLE_MESH_LPN_DISABLED,     /* LPN功能已禁用*/
        BLE_MESH_LPN_CLEAR,        /* 正在清除*/
        BLE_MESH_LPN_TIMER,        /* 等待自动计时器到期*/
        BLE_MESH_LPN_ENABLED,      /* 已启用LPN，但没有朋友*/
        BLE_MESH_LPN_REQ_WAIT,     /* 在扫描优惠之前等待*/
        BLE_MESH_LPN_WAIT_OFFER,   /* 已发送好友请求*/
        BLE_MESH_LPN_ESTABLISHED,  /* 建立友谊*/
        BLE_MESH_LPN_RECV_DELAY,   /* 轮询已发送，等待ReceiveDelay*/
        BLE_MESH_LPN_WAIT_UPDATE,  /* 正在等待更新或消息*/
        BLE_MESH_LPN_OFFER_RECV,   /* 收到好友邀请*/
    } state;

    /* 交易号（用于订阅列表）*/
    uint8_t xact_next;
    uint8_t xact_pending;
    uint8_t sent_req;

    /* 我们是LPN时朋友的地址。如果我们还没有朋友，则未分配。
     */
    uint16_t frnd;

    /* 朋友提供的价值*/
    uint8_t  recv_win;

    uint8_t  req_attempts;     /* 请求尝试次数*/

    int32_t  poll_timeout;

    uint8_t  groups_changed: 1, /* 好友订阅列表需要更新*/
             pending_poll: 1,   /* 订阅后发送的投票*/
             disable: 1,        /* 清除后禁用LPN*/
             fsn: 1,            /* 好友序列号*/
             established: 1,    /* 建立友谊*/
             clear_success: 1;  /* 收到好友清除确认*/

    /* 好友队列大小*/
    uint8_t  queue_size;

    /* LPN计数器*/
    uint16_t counter;

    /* 此LPN的前朋友*/
    uint16_t old_friend;

    /* 上次广告数据包报告的持续时间*/
    uint16_t adv_duration;

    /* 下一个LPN相关动作计时器*/
    struct k_delayed_work timer;

    /* 订阅的组*/
    uint16_t groups[LPN_GROUPS];

    /* 用于跟踪朋友知道哪些组的位字段*/
    BLE_MESH_ATOMIC_DEFINE(added, LPN_GROUPS);
    BLE_MESH_ATOMIC_DEFINE(pending, LPN_GROUPS);
    BLE_MESH_ATOMIC_DEFINE(to_remove, LPN_GROUPS);
};

/* bt_mesh_net中。旗帜*/
enum {
    BLE_MESH_NODE,            /* 设备是一个节点*/
    BLE_MESH_PROVISIONER,     /* 设备是配置器*/
    BLE_MESH_VALID,           /* 我们已配置*/
    BLE_MESH_VALID_PROV,      /* 配置程序已启用*/
    BLE_MESH_SUSPENDED,       /* 网络暂时挂起*/
    BLE_MESH_IVU_IN_PROGRESS, /* IV正在更新*/
    BLE_MESH_IVU_INITIATOR,   /* 四、我们发起的更新*/
    BLE_MESH_IVU_TEST,        /* 四、更新测试模式*/
    BLE_MESH_IVU_PENDING,     /* SDU正在阻止更新*/

    /* 挂起的存储操作，必须位于前32个标志内*/
    BLE_MESH_RPL_PENDING,
    BLE_MESH_KEYS_PENDING,
    BLE_MESH_NET_PENDING,
    BLE_MESH_IV_PENDING,
    BLE_MESH_SEQ_PENDING,
    BLE_MESH_HB_PUB_PENDING,
    BLE_MESH_CFG_PENDING,
    BLE_MESH_MOD_PENDING,
    BLE_MESH_VA_PENDING,

    /* 不要触摸-故意最后*/
    BLE_MESH_FLAG_COUNT,
};

struct bt_mesh_net {
    uint32_t iv_index; /* 当前IV索引*/
    uint32_t seq;      /* 下一个输出序列号（24位）*/

    BLE_MESH_ATOMIC_DEFINE(flags, BLE_MESH_FLAG_COUNT);

    /* 本地网络接口*/
    struct k_work local_work;
    sys_slist_t local_queue;

#if defined(CONFIG_BLE_MESH_FRIEND)
    /* 好友状态，对于我们所属的每个LPN来说都是独一无二的*/
    struct bt_mesh_friend frnd[CONFIG_BLE_MESH_FRIEND_LPN_COUNT];
#endif

#if defined(CONFIG_BLE_MESH_LOW_POWER)
    struct bt_mesh_lpn lpn;  /* 低功耗节点状态*/
#endif

    /* 当前IV更新状态的小时数*/
    uint8_t ivu_duration;

    /* 跟踪当前IV更新状态持续时间的计时器*/
    struct k_delayed_work ivu_timer;

    uint8_t dev_key[16];

    struct bt_mesh_app_key app_keys[CONFIG_BLE_MESH_APP_KEY_COUNT];

    struct bt_mesh_subnet sub[CONFIG_BLE_MESH_SUBNET_COUNT];

    struct bt_mesh_rpl rpl[CONFIG_BLE_MESH_CRPL];

#if defined(CONFIG_BLE_MESH_PROVISIONER)
    /* 设置器存储的应用程序密钥*/
    struct bt_mesh_app_key *p_app_keys[CONFIG_BLE_MESH_PROVISIONER_APP_KEY_COUNT];
    /* 可以分配下一个app_idx*/
    uint16_t p_app_idx_next;

    /* 配置程序存储的网络密钥*/
    struct bt_mesh_subnet *p_sub[CONFIG_BLE_MESH_PROVISIONER_SUBNET_COUNT];
    /* 可以分配下一个net_idx*/
    uint16_t p_net_idx_next;
#endif
};

/* 网络接口*/
enum bt_mesh_net_if {
    BLE_MESH_NET_IF_ADV,
    BLE_MESH_NET_IF_LOCAL,
    BLE_MESH_NET_IF_PROXY,
    BLE_MESH_NET_IF_PROXY_CFG,
};

/* 解码网络/传输数据的上下文*/
struct bt_mesh_net_rx {
    struct bt_mesh_subnet *sub;
    struct bt_mesh_msg_ctx ctx;
    uint32_t seq;            /* 序列号*/
    uint8_t  old_iv:1,       /* 使用iv_index-1*/
             new_key:1,      /* 数据已使用更新的密钥加密*/
             friend_cred:1,  /* 数据已使用好友信用进行加密*/
             ctl:1,          /* 网络控制*/
             net_if:2,       /* 网络接口*/
             local_match:1,  /* 匹配本地元素*/
             friend_match:1; /* 匹配了我们是朋友的LPN*/
    uint16_t msg_cache_idx;  /* 邮件缓存中的条目索引*/
};

/* 网络/传输数据的编码上下文*/
struct bt_mesh_net_tx {
    struct bt_mesh_subnet *sub;
    struct bt_mesh_msg_ctx *ctx;
    uint16_t src;
    uint8_t  xmit;
    uint8_t  friend_cred:1,
             aszmic:1,
             aid: 6;
};

extern struct bt_mesh_net bt_mesh;

#define BLE_MESH_NET_IVI_TX (bt_mesh.iv_index - \
                             bt_mesh_atomic_test_bit(bt_mesh.flags, \
                             BLE_MESH_IVU_IN_PROGRESS))
#define BLE_MESH_NET_IVI_RX(rx) (bt_mesh.iv_index - (rx)->old_iv)

#define BLE_MESH_NET_HDR_LEN 9

void bt_mesh_msg_cache_clear(uint16_t unicast_addr, uint8_t elem_num);

int bt_mesh_net_keys_create(struct bt_mesh_subnet_keys *keys,
                            const uint8_t key[16]);

int bt_mesh_net_create(uint16_t idx, uint8_t flags, const uint8_t key[16],
                       uint32_t iv_index);

uint8_t bt_mesh_net_flags(struct bt_mesh_subnet *sub);

bool bt_mesh_kr_update(struct bt_mesh_subnet *sub, uint8_t new_kr, bool new_key);

void bt_mesh_net_revoke_keys(struct bt_mesh_subnet *sub);

int bt_mesh_net_beacon_update(struct bt_mesh_subnet *sub);

void bt_mesh_rpl_reset(void);

bool bt_mesh_net_iv_update(uint32_t iv_index, bool iv_update);

void bt_mesh_net_sec_update(struct bt_mesh_subnet *sub);

struct bt_mesh_subnet *bt_mesh_subnet_get(uint16_t net_idx);

struct bt_mesh_subnet *bt_mesh_subnet_find(const uint8_t net_id[8], uint8_t flags,
                                           uint32_t iv_index, const uint8_t auth[8],
                                           bool *new_key);

int bt_mesh_net_encode(struct bt_mesh_net_tx *tx, struct net_buf_simple *buf,
                       bool proxy);

int bt_mesh_net_send(struct bt_mesh_net_tx *tx, struct net_buf *buf,
                     const struct bt_mesh_send_cb *cb, void *cb_data);

int bt_mesh_net_resend(struct bt_mesh_subnet *sub, struct net_buf *buf,
                       bool new_key, const struct bt_mesh_send_cb *cb,
                       void *cb_data);

int bt_mesh_net_decode(struct net_buf_simple *data, enum bt_mesh_net_if net_if,
                       struct bt_mesh_net_rx *rx, struct net_buf_simple *buf);

void bt_mesh_net_recv(struct net_buf_simple *data, int8_t rssi,
                      enum bt_mesh_net_if net_if);

bool bt_mesh_primary_subnet_exist(void);

uint32_t bt_mesh_next_seq(void);

void bt_mesh_net_start(void);

void bt_mesh_net_init(void);
void bt_mesh_net_reset(void);
void bt_mesh_net_deinit(void);

void bt_mesh_net_header_parse(struct net_buf_simple *buf,
                              struct bt_mesh_net_rx *rx);

/* 友谊证书管理*/
struct friend_cred {
    uint16_t net_idx;
    uint16_t addr;

    uint16_t lpn_counter;
    uint16_t frnd_counter;

    struct {
        uint8_t nid;         /* NID */
        uint8_t enc[16];     /* 加密密钥*/
        uint8_t privacy[16]; /* 隐私密钥*/
    } cred[2];
};

int friend_cred_get(struct bt_mesh_subnet *sub, uint16_t addr, uint8_t *nid,
                    const uint8_t **enc, const uint8_t **priv);
int friend_cred_set(struct friend_cred *cred, uint8_t idx, const uint8_t net_key[16]);
void friend_cred_refresh(uint16_t net_idx);
int friend_cred_update(struct bt_mesh_subnet *sub);
struct friend_cred *friend_cred_create(struct bt_mesh_subnet *sub, uint16_t addr,
                                       uint16_t lpn_counter, uint16_t frnd_counter);
void friend_cred_clear(struct friend_cred *cred);
int friend_cred_del(uint16_t net_idx, uint16_t addr);

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

#ifdef __cplusplus
}
#endif

#endif /* _NET_H_ */

