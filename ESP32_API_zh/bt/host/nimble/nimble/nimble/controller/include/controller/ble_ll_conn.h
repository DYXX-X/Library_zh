/*
 * 根据一个或多个贡献者许可协议向Apache Software Foundation（ASF）许可。有关版权所有权的更多信息，请参阅随本作品分发的通知文件。ASF根据Apache许可证2.0版（“许可证”）向您许可此文件；除非符合许可证，否则不得使用此文件。您可以在以下地址获取许可证副本：
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 * 除非适用法律要求或书面同意，否则根据许可证分发的软件是按“原样”分发的，无任何明示或暗示的担保或条件。有关许可证下权限和限制的具体语言，请参阅许可证。
 */

#ifndef H_BLE_LL_CONN_
#define H_BLE_LL_CONN_

#include "os/os.h"
#include "nimble/ble.h"
#include "nimble/hci_common.h"
#include "nimble/nimble_npl.h"
#include "controller/ble_ll_sched.h"
#include "controller/ble_ll_ctrl.h"
#include "controller/ble_phy.h"

#ifdef __cplusplus
extern "C" {
#endif

/* 角色*/
#define BLE_LL_CONN_ROLE_NONE           (0)
#define BLE_LL_CONN_ROLE_MASTER         (1)
#define BLE_LL_CONN_ROLE_SLAVE          (2)

/* 连接状态*/
#define BLE_LL_CONN_STATE_IDLE          (0)
#define BLE_LL_CONN_STATE_CREATED       (1)
#define BLE_LL_CONN_STATE_ESTABLISHED   (2)

/* 通道贴图大小*/
#define BLE_LL_CONN_CHMAP_LEN           (5)

/* 源时钟精度的定义*/
#define BLE_MASTER_SCA_251_500_PPM      (0)
#define BLE_MASTER_SCA_151_250_PPM      (1)
#define BLE_MASTER_SCA_101_150_PPM      (2)
#define BLE_MASTER_SCA_76_100_PPM       (3)
#define BLE_MASTER_SCA_51_75_PPM        (4)
#define BLE_MASTER_SCA_31_50_PPM        (5)
#define BLE_MASTER_SCA_21_30_PPM        (6)
#define BLE_MASTER_SCA_0_20_PPM         (7)

/* RSSI未知时的RSSI定义*/
#define BLE_LL_CONN_UNKNOWN_RSSI        (127)

#if MYNEWT_VAL(BLE_LL_CFG_FEAT_LE_ENCRYPTION)
/*
 * 连接的加密状态
 *
 * 注意：对状态进行排序，以便我们可以检查状态是否大于ENCRYPTED。如果是，这意味着开始或暂停加密过程正在运行，我们不应该发送数据pdu。
 */
enum conn_enc_state {
    CONN_ENC_S_UNENCRYPTED = 1,
    CONN_ENC_S_ENCRYPTED,
    CONN_ENC_S_ENC_RSP_WAIT,
    CONN_ENC_S_PAUSE_ENC_RSP_WAIT,
    CONN_ENC_S_PAUSED,
    CONN_ENC_S_START_ENC_REQ_WAIT,
    CONN_ENC_S_START_ENC_RSP_WAIT,
    CONN_ENC_S_LTK_REQ_WAIT,
    CONN_ENC_S_LTK_NEG_REPLY
};

/*
 * 注意，LTK是密钥，SDK是纯文本，会话密钥是加密块的密文部分。
 *
 * 注意：我们故意违反了规范，将发送和接收数据包计数器设置为32位，而不是39位（根据规范）。我们这样做是为了节省代码空间、内存和计算时间。唯一的缺点是，任何发送超过2^32个数据包的加密连接都会出现MIC故障，从而断开连接。
 */
struct ble_ll_conn_enc_data
{
    uint8_t enc_state;
    uint8_t tx_encrypted;
    uint16_t enc_div;
    uint32_t tx_pkt_cntr;
    uint32_t rx_pkt_cntr;
    uint64_t host_rand_num;
    uint8_t iv[8];
    struct ble_encryption_block enc_block;
};
#endif

/* 连接状态机标志。*/
union ble_ll_conn_sm_flags {
    struct {
        uint32_t pkt_rxd:1;
        uint32_t terminate_ind_txd:1;
        uint32_t terminate_ind_rxd:1;
        uint32_t terminate_ind_rxd_acked:1;
        uint32_t allow_slave_latency:1;
        uint32_t slave_set_last_anchor:1;
        uint32_t awaiting_host_reply:1;
        uint32_t terminate_started:1;
        uint32_t conn_update_sched:1;
        uint32_t host_expects_upd_event:1;
        uint32_t version_ind_sent:1;
        uint32_t rxd_version_ind:1;
        uint32_t chanmap_update_scheduled:1;
        uint32_t conn_empty_pdu_txd:1;
        uint32_t last_txd_md:1;
        uint32_t conn_req_txd:1;
        uint32_t send_ltk_req:1;
        uint32_t encrypted:1;
        uint32_t encrypt_chg_sent:1;
        uint32_t le_ping_supp:1;
        uint32_t csa2_supp:1;
        uint32_t host_phy_update: 1;
        uint32_t phy_update_sched: 1;
        uint32_t ctrlr_phy_update: 1;
        uint32_t phy_update_event: 1;
        uint32_t peer_phy_update: 1; /* 三十： 与ctrlr-udpate位组合？*/
        uint32_t aux_conn_req: 1;
        uint32_t rxd_features:1;
        uint32_t pending_hci_rd_features:1;
        uint32_t pending_initiate_dle:1;
    } cfbit;
    uint32_t conn_flags;
} __attribute__((packed));

/**
 * 用于连接内PHY数据的结构。
 *
 * 注意：新的phy是当phy更新过程正在进行并且事件计数器立即命中时，我们将更改为的phy。
 *
 * tx_phy_mode：tx rx-phy_mode的芯片特定物理模式：rx cur_tx_phy的芯片特定的物理模式：表示当前tx_phy的值（不是位掩码！）cur_rx_phy：表示当前rx phy的值（不是位掩码！）new_tx_phy：表示新tx_phy的值（不是位掩码！）new_rx_phy：表示新rx phy的值（不是位掩码！）req_pref_tx_phy:tx phy在phy请求中发送（可能与主机不同）req_pref_rx_phy:rx phy在hy请求中发出（可能与宿主不同）host_pref_tx.phys：主机发送的首选发送phy的位掩码host_pref_rx-phys：主机发送的首选接收phy的位掩码phy_options：编码phy的首选phy选项
 */
struct ble_ll_conn_phy_data
{
    uint32_t tx_phy_mode: 2;
    uint32_t rx_phy_mode: 2;
    uint32_t cur_tx_phy: 2;
    uint32_t cur_rx_phy: 2;
    uint32_t new_tx_phy: 2;
    uint32_t new_rx_phy: 2;
    uint32_t host_pref_tx_phys_mask: 3;
    uint32_t host_pref_rx_phys_mask: 3;
    uint32_t req_pref_tx_phys_mask: 3;
    uint32_t req_pref_rx_phys_mask: 3;
    uint32_t phy_options: 2;
}  __attribute__((packed));

#define CONN_CUR_TX_PHY_MASK(csm)   (1 << ((csm)->phy_data.cur_tx_phy - 1))
#define CONN_CUR_RX_PHY_MASK(csm)   (1 << ((csm)->phy_data.cur_rx_phy - 1))

struct hci_conn_update
{
    uint16_t handle;
    uint16_t conn_itvl_min;
    uint16_t conn_itvl_max;
    uint16_t conn_latency;
    uint16_t supervision_timeout;
    uint16_t min_ce_len;
    uint16_t max_ce_len;
};

struct hci_ext_conn_params
{
    uint16_t scan_itvl;
    uint16_t scan_window;
    uint16_t conn_itvl_min;
    uint16_t conn_itvl_max;
    uint16_t conn_latency;
    uint16_t supervision_timeout;
    uint16_t min_ce_len;
    uint16_t max_ce_len;
};

struct hci_ext_create_conn
{
    uint8_t filter_policy;
    uint8_t own_addr_type;
    uint8_t peer_addr_type;
    uint8_t peer_addr[BLE_DEV_ADDR_LEN];
    uint8_t init_phy_mask;
    struct hci_ext_conn_params params[3];
};

/* 连接状态机*/
struct ble_ll_conn_sm
{
    /* 连接状态机标志*/
    union ble_ll_conn_sm_flags csmflags;

    /* 当前连接句柄、状态和角色*/
    uint16_t conn_handle;
    uint8_t conn_state;
    uint8_t conn_role;          /* 可能是1位*/

    /* RSSI */
    int8_t conn_rssi;

    /* 为了隐私*/
    int8_t rpa_index;

    /* 连接数据长度管理*/
    uint8_t max_tx_octets;
    uint8_t max_rx_octets;
    uint8_t rem_max_tx_octets;
    uint8_t rem_max_rx_octets;
    uint8_t eff_max_tx_octets;
    uint8_t eff_max_rx_octets;
    uint16_t max_tx_time;
    uint16_t max_rx_time;
    uint16_t rem_max_tx_time;
    uint16_t rem_max_rx_time;
    uint16_t eff_max_tx_time;
    uint16_t eff_max_rx_time;
    uint8_t max_tx_octets_phy_mode[BLE_PHY_NUM_MODE];
#if MYNEWT_VAL(BLE_LL_CFG_FEAT_LE_CODED_PHY)
    uint16_t host_req_max_tx_time;
#endif

#if (BLE_LL_BT5_PHY_SUPPORTED == 1)
    struct ble_ll_conn_phy_data phy_data;
    uint16_t phy_instant;
    uint8_t phy_tx_transition;
#endif

    /* 用于计算连接的数据通道索引*/
    uint8_t chanmap[BLE_LL_CONN_CHMAP_LEN];
    uint8_t req_chanmap[BLE_LL_CONN_CHMAP_LEN];
    uint16_t chanmap_instant;
    uint16_t channel_id; /* TODO可以与使用的跃点和最后一个chan联合*/
    uint8_t hop_inc;
    uint8_t data_chan_index;
    uint8_t last_unmapped_chan;
    uint8_t num_used_chans;

#if MYNEWT_VAL(BLE_LL_STRICT_CONN_SCHEDULING)
    uint8_t period_occ_mask;    /* 掩码：时段0=0x01，时段3=0x08*/
#endif

    /* 确认/流量控制*/
    uint8_t tx_seqnum;          /* 注意：可以是1位*/
    uint8_t next_exp_seqnum;    /* 注意：可以是1位*/
    uint8_t cons_rxd_bad_crc;   /* 注意：可以是1位*/
    uint8_t last_rxd_sn;        /* 注意：给定当前代码，不能为1位*/
    uint8_t last_rxd_hdr_byte;  /* 注意：由于我们现在只使用MD位，因此可能会生成1位*/

    /* 连接事件管理*/
    uint8_t reject_reason;
    uint8_t host_reply_opcode;
    uint8_t master_sca;
    uint8_t tx_win_size;
    uint8_t cur_ctrl_proc;
    uint8_t disconnect_reason;
    uint8_t rxd_disconnect_reason;
    uint8_t vers_nr;
    uint8_t conn_features;
    uint8_t remote_features[7];
    uint16_t pending_ctrl_procs;
    uint16_t event_cntr;
    uint16_t completed_pkts;
    uint16_t comp_id;
    uint16_t sub_vers_nr;
    uint16_t auth_pyld_tmo;         /* 可能是“如果”。10毫秒单位*/

    uint32_t access_addr;
    uint32_t crcinit;               /* 仅使用低24位*/
    /* 三十： 我们需要结束时间吗？这不能安排结束时间吗？*/
    uint32_t ce_end_time;   /* 连接事件应结束的cputime*/
    uint32_t terminate_timeout;
    uint32_t last_scheduled;

    /* 连接定时*/
    uint16_t conn_itvl;
    uint16_t slave_latency;
    uint16_t supervision_tmo;
    uint16_t min_ce_len;
    uint16_t max_ce_len;
    uint16_t tx_win_off;
    uint32_t anchor_point;
    uint8_t anchor_point_usecs;     /* 三十： 这是uint8t吗？*/
    uint8_t conn_itvl_usecs;
    uint32_t conn_itvl_ticks;
    uint32_t last_anchor_point;     /* 仅从设备*/
    uint32_t slave_cur_tx_win_usecs;
    uint32_t slave_cur_window_widening;
    uint32_t last_rxd_pdu_cputime;  /* 专用于监控计时器*/

    /*
     * 用于标记身份地址用作InitA
     */
    uint8_t inita_identity_used;

    /* 地址信息*/
    uint8_t own_addr_type;
    uint8_t peer_addr_type;
    uint8_t peer_addr[BLE_DEV_ADDR_LEN];

    /*
     * 三十： 托多。可以节省内存。在LL中有一个事件，并将其放在一个单独的链接列表中。这里只需要列表指针。
     */
    /* 连接结束事件*/
    struct ble_npl_event conn_ev_end;

    /* 数据包传输队列*/
    struct os_mbuf *cur_tx_pdu;
    STAILQ_HEAD(conn_txq_head, os_mbuf_pkthdr) conn_txq;

    /* 活动/空闲连接池的列表项*/
    union {
        SLIST_ENTRY(ble_ll_conn_sm) act_sle;
        STAILQ_ENTRY(ble_ll_conn_sm) free_stqe;
    };

    /* LL控制程序响应计时器*/
    struct ble_npl_callout ctrl_proc_rsp_timer;

    /* 用于调度连接*/
    struct ble_ll_sched_item conn_sch;

#if MYNEWT_VAL(BLE_LL_CFG_FEAT_LE_PING)
    struct ble_npl_callout auth_pyld_timer;
#endif

    /*
     * 三十： 关于控制程序的所有这些结构的说明。首先，所有这些都需要进行ifdef以节省内存。另一个需要考虑的问题是：由于大多数控制程序只能在没有其他程序运行时运行，所以我可以只使用一个结构（联合）吗？我应该从池中分配这些吗？不知道该怎么做。现在，我只是在每个连接中使用一大块内存。
     */
#if MYNEWT_VAL(BLE_LL_CFG_FEAT_LE_ENCRYPTION)
    struct ble_ll_conn_enc_data enc_data;
#endif
    /*
     * 用于连接更新过程。三十： 如果我们想节省空间，可以将其设置为指针并将其malloc。
     */
    struct hci_conn_update conn_param_req;

    /* 用于连接更新过程*/
    struct ble_ll_conn_upd_req conn_update_req;

    /* 三十： 现在，把它们都存起来*/
    struct ble_ll_conn_params conn_cp;

    struct ble_ll_scan_sm *scansm;
#if MYNEWT_VAL(BLE_LL_CFG_FEAT_LL_EXT_ADV)
    struct hci_ext_create_conn initial_params;
#endif

#if MYNEWT_VAL(BLE_LL_CFG_FEAT_LL_PERIODIC_ADV_SYNC_TRANSFER)
    uint8_t  sync_transfer_mode;
    uint16_t sync_transfer_skip;
    uint32_t sync_transfer_sync_timeout;
#endif
};

/* 旗帜*/
#define CONN_F_UPDATE_SCHED(csm)    ((csm)->csmflags.cfbit.conn_update_sched)
#define CONN_F_EMPTY_PDU_TXD(csm)   ((csm)->csmflags.cfbit.conn_empty_pdu_txd)
#define CONN_F_LAST_TXD_MD(csm)     ((csm)->csmflags.cfbit.last_txd_md)
#define CONN_F_CONN_REQ_TXD(csm)    ((csm)->csmflags.cfbit.conn_req_txd)
#define CONN_F_ENCRYPTED(csm)       ((csm)->csmflags.cfbit.encrypted)
#define CONN_F_ENC_CHANGE_SENT(csm) ((csm)->csmflags.cfbit.encrypt_chg_sent)
#define CONN_F_LE_PING_SUPP(csm)    ((csm)->csmflags.cfbit.le_ping_supp)
#define CONN_F_TERMINATE_STARTED(csm) ((csm)->csmflags.cfbit.terminate_started)
#define CONN_F_CSA2_SUPP(csm)       ((csm)->csmflags.cfbit.csa2_supp)
#define CONN_F_HOST_PHY_UPDATE(csm) ((csm)->csmflags.cfbit.host_phy_update)
#define CONN_F_PHY_UPDATE_SCHED(csm) ((csm)->csmflags.cfbit.phy_update_sched)
#define CONN_F_CTRLR_PHY_UPDATE(csm) ((csm)->csmflags.cfbit.ctrlr_phy_update)
#define CONN_F_PHY_UPDATE_EVENT(csm) ((csm)->csmflags.cfbit.phy_update_event)
#define CONN_F_PEER_PHY_UPDATE(csm)  ((csm)->csmflags.cfbit.peer_phy_update)
#define CONN_F_AUX_CONN_REQ(csm)  ((csm)->csmflags.cfbit.aux_conn_req)

/* 角色*/
#define CONN_IS_MASTER(csm)         (csm->conn_role == BLE_LL_CONN_ROLE_MASTER)
#define CONN_IS_SLAVE(csm)          (csm->conn_role == BLE_LL_CONN_ROLE_SLAVE)

/*
 * 给定句柄，返回活动连接状态机（如果句柄不存在，则返回NULL
 *
 */
struct ble_ll_conn_sm *ble_ll_conn_find_active_conn(uint16_t handle);

/* 单元测试所需*/
uint8_t ble_ll_conn_calc_dci(struct ble_ll_conn_sm *conn, uint16_t latency);

/* 用于获取指定连接事件的锚点*/
void ble_ll_conn_get_anchor(struct ble_ll_conn_sm *connsm, uint16_t conn_event,
                            uint32_t *anchor, uint8_t *anchor_usecs);

#ifdef __cplusplus
}
#endif

#endif /* H_BLE_LL_CONN_ */

