/*
 * 根据一个或多个贡献者许可协议向Apache Software Foundation（ASF）许可。有关版权所有权的更多信息，请参阅随本作品分发的通知文件。ASF根据Apache许可证2.0版（“许可证”）向您许可此文件；除非符合许可证，否则不得使用此文件。您可以在以下地址获取许可证副本：
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 * 除非适用法律要求或书面同意，否则根据许可证分发的软件是按“原样”分发的，无任何明示或暗示的担保或条件。有关许可证下权限和限制的具体语言，请参阅许可证。
 */

#ifndef H_BLE_LL_
#define H_BLE_LL_

#include "stats/stats.h"
#include "os/os_cputime.h"
#include "nimble/nimble_opt.h"
#include "nimble/nimble_npl.h"
#include "controller/ble_phy.h"

#ifdef MYNEWT
#include "controller/ble_ll_ctrl.h"
#include "hal/hal_system.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

#if MYNEWT_VAL(OS_CPUTIME_FREQ) != 32768
#error 32.768kHz clock required
#endif

#if defined(MYNEWT) && MYNEWT_VAL(BLE_LL_VND_EVENT_ON_ASSERT)
#ifdef NDEBUG
#define BLE_LL_ASSERT(cond) (void(0))
#else
#define BLE_LL_ASSERT(cond) \
    if (!(cond)) { \
        if (hal_debugger_connected()) { \
            assert(0);\
        } else {\
            ble_ll_hci_ev_send_vendor_err(__FILE__, __LINE__); \
            while(1) {}\
        }\
    }
#endif
#else
#define BLE_LL_ASSERT(cond) assert(cond)
#endif

#if MYNEWT_VAL(BLE_LL_CFG_FEAT_LE_2M_PHY) || MYNEWT_VAL(BLE_LL_CFG_FEAT_LE_CODED_PHY)
#define BLE_LL_BT5_PHY_SUPPORTED    (1)
#else
#define BLE_LL_BT5_PHY_SUPPORTED    (0)
#endif

/* 控制器版本。*/
#define BLE_LL_SUB_VERS_NR      (0x0000)

/* 根据规范，定时抖动为+/-16 usecs*/
#define BLE_LL_JITTER_USECS         (16)

/* 数据包队列标头定义*/
STAILQ_HEAD(ble_ll_pkt_q, os_mbuf_pkthdr);

/*
 * 全局链接层数据对象。每个控制器只有一个链路层数据对象，尽管链路层状态机可能有许多实例在运行。
 */
struct ble_ll_obj
{
    /* 支持的功能*/
    uint64_t ll_supp_features;

    /* 当前链接层状态*/
    uint8_t ll_state;

    /* 支持的ACL数据包数*/
    uint8_t ll_num_acl_pkts;

    /* ACL数据包大小*/
    uint16_t ll_acl_pkt_size;

    /* 首选PHY*/
    uint8_t ll_pref_tx_phys;
    uint8_t ll_pref_rx_phys;

    /* 任务事件队列*/
    struct ble_npl_eventq ll_evq;

    /* 等待响应计时器*/
    struct hal_timer ll_wfr_timer;

    /* 数据包接收队列（和事件）。保存从PHY接收的数据包*/
    struct ble_npl_event ll_rx_pkt_ev;
    struct ble_ll_pkt_q ll_rx_pkt_q;

    /* 数据包传输队列*/
    struct ble_npl_event ll_tx_pkt_ev;
    struct ble_ll_pkt_q ll_tx_pkt_q;

    /* 数据缓冲区溢出事件*/
    struct ble_npl_event ll_dbuf_overflow_ev;

    /* 完成的数据包数事件*/
    struct ble_npl_event ll_comp_pkt_ev;

    /* 硬件错误标注*/
    struct ble_npl_callout ll_hw_err_timer;
};
extern struct ble_ll_obj g_ble_ll_data;

/* 链接层统计信息*/
STATS_SECT_START(ble_ll_stats)
    STATS_SECT_ENTRY(hci_cmds)
    STATS_SECT_ENTRY(hci_cmd_errs)
    STATS_SECT_ENTRY(hci_events_sent)
    STATS_SECT_ENTRY(bad_ll_state)
    STATS_SECT_ENTRY(bad_acl_hdr)
    STATS_SECT_ENTRY(no_bufs)
    STATS_SECT_ENTRY(rx_adv_pdu_crc_ok)
    STATS_SECT_ENTRY(rx_adv_pdu_crc_err)
    STATS_SECT_ENTRY(rx_adv_bytes_crc_ok)
    STATS_SECT_ENTRY(rx_adv_bytes_crc_err)
    STATS_SECT_ENTRY(rx_data_pdu_crc_ok)
    STATS_SECT_ENTRY(rx_data_pdu_crc_err)
    STATS_SECT_ENTRY(rx_data_bytes_crc_ok)
    STATS_SECT_ENTRY(rx_data_bytes_crc_err)
    STATS_SECT_ENTRY(rx_adv_malformed_pkts)
    STATS_SECT_ENTRY(rx_adv_ind)
    STATS_SECT_ENTRY(rx_adv_direct_ind)
    STATS_SECT_ENTRY(rx_adv_nonconn_ind)
    STATS_SECT_ENTRY(rx_adv_ext_ind)
    STATS_SECT_ENTRY(rx_scan_reqs)
    STATS_SECT_ENTRY(rx_scan_rsps)
    STATS_SECT_ENTRY(rx_connect_reqs)
    STATS_SECT_ENTRY(rx_scan_ind)
    STATS_SECT_ENTRY(rx_aux_connect_rsp)
    STATS_SECT_ENTRY(adv_txg)
    STATS_SECT_ENTRY(adv_late_starts)
    STATS_SECT_ENTRY(adv_resched_pdu_fail)
    STATS_SECT_ENTRY(adv_drop_event)
    STATS_SECT_ENTRY(sched_state_conn_errs)
    STATS_SECT_ENTRY(sched_state_adv_errs)
    STATS_SECT_ENTRY(scan_starts)
    STATS_SECT_ENTRY(scan_stops)
    STATS_SECT_ENTRY(scan_req_txf)
    STATS_SECT_ENTRY(scan_req_txg)
    STATS_SECT_ENTRY(scan_rsp_txg)
    STATS_SECT_ENTRY(aux_missed_adv)
    STATS_SECT_ENTRY(aux_scheduled)
    STATS_SECT_ENTRY(aux_received)
    STATS_SECT_ENTRY(aux_fired_for_read)
    STATS_SECT_ENTRY(aux_allocated)
    STATS_SECT_ENTRY(aux_freed)
    STATS_SECT_ENTRY(aux_sched_cb)
    STATS_SECT_ENTRY(aux_conn_req_tx)
    STATS_SECT_ENTRY(aux_conn_rsp_tx)
    STATS_SECT_ENTRY(aux_conn_rsp_err)
    STATS_SECT_ENTRY(aux_scan_req_tx)
    STATS_SECT_ENTRY(aux_scan_rsp_err)
    STATS_SECT_ENTRY(aux_chain_cnt)
    STATS_SECT_ENTRY(aux_chain_err)
    STATS_SECT_ENTRY(aux_scan_drop)
    STATS_SECT_ENTRY(adv_evt_dropped)
    STATS_SECT_ENTRY(scan_timer_stopped)
    STATS_SECT_ENTRY(scan_timer_restarted)
    STATS_SECT_ENTRY(periodic_adv_drop_event)
    STATS_SECT_ENTRY(periodic_chain_drop_event)
    STATS_SECT_ENTRY(sync_event_failed)
    STATS_SECT_ENTRY(sync_received)
    STATS_SECT_ENTRY(sync_chain_failed)
    STATS_SECT_ENTRY(sync_missed_err)
    STATS_SECT_ENTRY(sync_crc_err)
    STATS_SECT_ENTRY(sync_rx_buf_err)
    STATS_SECT_ENTRY(sync_scheduled)
    STATS_SECT_ENTRY(sched_state_sync_errs)
    STATS_SECT_ENTRY(sched_invalid_pdu)
STATS_SECT_END
extern STATS_SECT_DECL(ble_ll_stats) ble_ll_stats;

/* 州*/
#define BLE_LL_STATE_STANDBY        (0)
#define BLE_LL_STATE_ADV            (1)
#define BLE_LL_STATE_SCANNING       (2)
#define BLE_LL_STATE_INITIATING     (3)
#define BLE_LL_STATE_CONNECTION     (4)
#define BLE_LL_STATE_DTM            (5)
#define BLE_LL_STATE_SYNC           (6)

/* LL功能*/
#define BLE_LL_FEAT_LE_ENCRYPTION    (0x0000000001)
#define BLE_LL_FEAT_CONN_PARM_REQ    (0x0000000002)
#define BLE_LL_FEAT_EXTENDED_REJ     (0x0000000004)
#define BLE_LL_FEAT_SLAVE_INIT       (0x0000000008)
#define BLE_LL_FEAT_LE_PING          (0x0000000010)
#define BLE_LL_FEAT_DATA_LEN_EXT     (0x0000000020)
#define BLE_LL_FEAT_LL_PRIVACY       (0x0000000040)
#define BLE_LL_FEAT_EXT_SCAN_FILT    (0x0000000080)
#define BLE_LL_FEAT_LE_2M_PHY        (0x0000000100)
#define BLE_LL_FEAT_STABLE_MOD_ID_TX (0x0000000200)
#define BLE_LL_FEAT_STABLE_MOD_ID_RX (0x0000000400)
#define BLE_LL_FEAT_LE_CODED_PHY     (0x0000000800)
#define BLE_LL_FEAT_EXT_ADV          (0x0000001000)
#define BLE_LL_FEAT_PERIODIC_ADV     (0x0000002000)
#define BLE_LL_FEAT_CSA2             (0x0000004000)
#define BLE_LL_FEAT_LE_POWER_CLASS_1 (0x0000008000)
#define BLE_LL_FEAT_MIN_USED_CHAN    (0x0000010000)
#define BLE_LL_FEAT_CTE_REQ          (0x0000020000)
#define BLE_LL_FEAT_CTE_RSP          (0x0000040000)
#define BLE_LL_FEAT_CTE_TX           (0x0000080000)
#define BLE_LL_FEAT_CTE_RX           (0x0000100000)
#define BLE_LL_FEAT_CTE_AOD          (0x0000200000)
#define BLE_LL_FEAT_CTE_AOA          (0x0000400000)
#define BLE_LL_FEAT_CTE_RECV         (0x0000800000)
#define BLE_LL_FEAT_SYNC_TRANS_SEND  (0x0001000000)
#define BLE_LL_FEAT_SYNC_TRANS_RECV  (0x0002000000)
#define BLE_LL_FEAT_SCA_UPDATE       (0x0004000000)
#define BLE_LL_FEAT_REM_PKEY         (0x0008000000)
#define BLE_LL_FEAT_CIS_MASTER       (0x0010000000)
#define BLE_LL_FEAT_CIS_SLAVE        (0x0020000000)
#define BLE_LL_FEAT_ISO_BROADCASTER  (0x0040000000)
#define BLE_LL_FEAT_SYNC_RECV        (0x0080000000)
#define BLE_LL_FEAT_ISO_HOST_SUPPORT (0x0100000000)
#define BLE_LL_FEAT_POWER_CTRL_REQ   (0x0200000000)
#define BLE_LL_FEAT_POWER_CHANGE_IND (0x0400000000)
#define BLE_LL_FEAT_PATH_LOSS_MON    (0x0800000000)

/* 这是初始掩码，所以若功能交换不会发生，但主机将希望使用此过程，我们将尝试。如果不成功，将清除特征位。查看以上LL功能以了解允许的功能
 */
#define BLE_LL_CONN_INITIAL_FEATURES    (0x00000022)
#define BLE_LL_CONN_CLEAR_FEATURE(connsm, feature)   (connsm->conn_features &= ~(feature))

/* 主机可以控制的所有功能*/
#define BLE_LL_HOST_CONTROLLED_FEATURES (BLE_LL_FEAT_ISO_HOST_SUPPORT)

/* LL定时*/
#define BLE_LL_IFS                  (150)       /* 用途*/
#define BLE_LL_MAFS                 (300)       /* 用途*/

/*
 * BLE LL设备地址。注意，数组的元素0是LSB，并且首先通过空中发送。字节5是MSB，是最后一个通过空中发送的字节。
 */
#define BLE_DEV_ADDR_LEN            (6)     /* 字节*/

struct ble_dev_addr
{
    uint8_t u8[BLE_DEV_ADDR_LEN];
};

#define BLE_IS_DEV_ADDR_STATIC(addr)        ((addr->u8[5] & 0xc0) == 0xc0)
#define BLE_IS_DEV_ADDR_RESOLVABLE(addr)    ((addr->u8[5] & 0xc0) == 0x40)
#define BLE_IS_DEV_ADDR_UNRESOLVABLE(addr)  ((addr->u8[5] & 0xc0) == 0x00)

/*
 * LL数据包格式
 *
 *  ->前导码（1/2字节）
 *  ->访问地址（4字节）
 *  ->PDU（2至257个八位字节）
 *  ->CRC（3字节）
 */
#define BLE_LL_PREAMBLE_LEN     (1)
#define BLE_LL_ACC_ADDR_LEN     (4)
#define BLE_LL_CRC_LEN          (3)
#define BLE_LL_PDU_HDR_LEN      (2)
#define BLE_LL_MAX_PAYLOAD_LEN  (255)
#define BLE_LL_MIN_PDU_LEN      (BLE_LL_PDU_HDR_LEN)
#define BLE_LL_MAX_PDU_LEN      ((BLE_LL_PDU_HDR_LEN) + (BLE_LL_MAX_PAYLOAD_LEN))
#define BLE_LL_CRCINIT_ADV      (0x555555)

/* 广告频道的访问地址*/
#define BLE_ACCESS_ADDR_ADV             (0x8E89BED6)

/*
 * 广告PDU格式：
 * ->2字节标头
 *      ->LSB包含pdu类型、txadd和rxadd位。
 *      ->MSB包含长度（6位）。长度是有效载荷的长度。不包括标头长度本身。
 * ->有效载荷（最大37字节）
 */
#define BLE_ADV_PDU_HDR_TYPE_MASK           (0x0F)
#define BLE_ADV_PDU_HDR_CHSEL_MASK          (0x20)
#define BLE_ADV_PDU_HDR_TXADD_MASK          (0x40)
#define BLE_ADV_PDU_HDR_RXADD_MASK          (0x80)

/* 广告频道PDU类型*/
#define BLE_ADV_PDU_TYPE_ADV_IND            (0)
#define BLE_ADV_PDU_TYPE_ADV_DIRECT_IND     (1)
#define BLE_ADV_PDU_TYPE_ADV_NONCONN_IND    (2)
#define BLE_ADV_PDU_TYPE_SCAN_REQ           (3)
#define BLE_ADV_PDU_TYPE_SCAN_RSP           (4)
#define BLE_ADV_PDU_TYPE_CONNECT_IND        (5)
#define BLE_ADV_PDU_TYPE_ADV_SCAN_IND       (6)
#define BLE_ADV_PDU_TYPE_ADV_EXT_IND        (7)
#define BLE_ADV_PDU_TYPE_AUX_ADV_IND        BLE_ADV_PDU_TYPE_ADV_EXT_IND
#define BLE_ADV_PDU_TYPE_AUX_SCAN_RSP       BLE_ADV_PDU_TYPE_ADV_EXT_IND
#define BLE_ADV_PDU_TYPE_AUX_SYNC_IND       BLE_ADV_PDU_TYPE_ADV_EXT_IND
#define BLE_ADV_PDU_TYPE_AUX_CHAIN_IND      BLE_ADV_PDU_TYPE_ADV_EXT_IND
#define BLE_ADV_PDU_TYPE_AUX_CONNECT_REQ    BLE_ADV_PDU_TYPE_CONNECT_IND
#define BLE_ADV_PDU_TYPE_AUX_SCAN_REQ       BLE_ADV_PDU_TYPE_SCAN_REQ
#define BLE_ADV_PDU_TYPE_AUX_CONNECT_RSP    (8)

/* 扩展收割台长度（6b）+先进模式（2b）*/
#define BLE_LL_EXT_ADV_HDR_LEN          (1)

#define BLE_LL_EXT_ADV_ADVA_BIT         (0)
#define BLE_LL_EXT_ADV_TARGETA_BIT      (1)
#define BLE_LL_EXT_ADV_CTE_INFO_BIT     (2)
#define BLE_LL_EXT_ADV_DATA_INFO_BIT    (3)
#define BLE_LL_EXT_ADV_AUX_PTR_BIT      (4)
#define BLE_LL_EXT_ADV_SYNC_INFO_BIT    (5)
#define BLE_LL_EXT_ADV_TX_POWER_BIT     (6)

#define BLE_LL_EXT_ADV_FLAGS_SIZE       (1)
#define BLE_LL_EXT_ADV_ADVA_SIZE        (6)
#define BLE_LL_EXT_ADV_TARGETA_SIZE     (6)
#define BLE_LL_EXT_ADV_DATA_INFO_SIZE   (2)
#define BLE_LL_EXT_ADV_AUX_PTR_SIZE     (3)
#define BLE_LL_EXT_ADV_SYNC_INFO_SIZE   (18)
#define BLE_LL_EXT_ADV_TX_POWER_SIZE    (1)

#define BLE_LL_EXT_ADV_MODE_NON_CONN    (0x00)
#define BLE_LL_EXT_ADV_MODE_CONN        (0x01)
#define BLE_LL_EXT_ADV_MODE_SCAN        (0x02)

/* 如果支持信道选择算法#2*/
#define BLE_ADV_PDU_HDR_CHSEL               (0x20)

/*
 * TxAdd和RxAdd位定义。A 0是公共地址；1是随机地址。
 */
#define BLE_ADV_PDU_HDR_TXADD_RAND          (0x40)
#define BLE_ADV_PDU_HDR_RXADD_RAND          (0x80)

/*
 * 数据通道格式
 *
 *  ->标题（2字节）
 *      ->LSB包含llid、nesn、sn和md
 *      ->MSB包含长度（8位）
 *  ->有效载荷（0至251）
 *  ->MIC（0或4字节）
 */
#define BLE_LL_DATA_HDR_LLID_MASK       (0x03)
#define BLE_LL_DATA_HDR_NESN_MASK       (0x04)
#define BLE_LL_DATA_HDR_SN_MASK         (0x08)
#define BLE_LL_DATA_HDR_MD_MASK         (0x10)
#define BLE_LL_DATA_HDR_RSRVD_MASK      (0xE0)
#define BLE_LL_DATA_PDU_MAX_PYLD        (251)
#define BLE_LL_DATA_MIC_LEN             (4)

/* LLID定义*/
#define BLE_LL_LLID_RSRVD               (0)
#define BLE_LL_LLID_DATA_FRAG           (1)
#define BLE_LL_LLID_DATA_START          (2)
#define BLE_LL_LLID_CTRL                (3)

/*
 * CONNECT_REQ
 *      ->InitA（6字节）
 *      ->AdvA（6字节）
 *      ->LLData（22字节）
 *          ->访问地址（4字节）
 *          ->CRC初始化（3字节）
 *          ->WinSize（1字节）
 *          ->WinOffset（2字节）
 *          ->间隔（2字节）
 *          ->延迟（2字节）
 *          ->超时（2字节）
 *          ->通道图（5字节）
 *          ->跃点增量（5位）
 *          ->SCA（3位）
 *
 *  InitA是启动器公共（TxAdd=0）或随机（TxAdd=1）地址。AdvaA是广告客户的公共（RxAdd=0）或随机（RxAdd=1）地址。LLData包含连接请求数据。aa：链路层的访问地址crc_init：用于crc计算的crc初始化值。winsize：传输窗口大小=winsize 1.25毫秒winoffset：传输窗口偏移量=winoffset 1.25毫秒interval：连接间隔=间隔1.25毫秒。latency：连接从属延迟=延迟超时：连接监控超时=超时10毫秒。chanmap：包含指示已使用和未使用数据信道的信道映射。只有1位可用。LSB是信道0。hop_inc：用于跳频的跃点增量。5到16范围内的随机值。
 */
#define BLE_CONNECT_REQ_LEN         (34)
#define BLE_CONNECT_REQ_PDU_LEN     (BLE_CONNECT_REQ_LEN + BLE_LL_PDU_HDR_LEN)

#define BLE_SCAN_REQ_LEN            (12)
#define BLE_SCAN_RSP_MAX_LEN        (37)
#define BLE_SCAN_RSP_MAX_EXT_LEN    (251)

#define BLE_LL_ADDR_SUBTYPE_IDENTITY    (0)
#define BLE_LL_ADDR_SUBTYPE_RPA         (1)
#define BLE_LL_ADDR_SUBTYPE_NRPA        (2)

/*---外部API---*/
/* 初始化链接层*/
void ble_ll_init(void);

/* 重置链接层*/
int ble_ll_reset(void);

int ble_ll_is_valid_public_addr(const uint8_t *addr);

/* 如果地址是有效的随机地址，则“布尔”函数返回true*/
int ble_ll_is_valid_random_addr(const uint8_t *addr);

/*
 * 检查给定的own_addr_type是否适用于给定的随机地址（如果适用）的当前控制器配置
 */
int ble_ll_is_valid_own_addr_type(uint8_t own_addr_type,
                                  const uint8_t *random_addr);

/* 计算有效负载长度为“payload_len”的PDU在PHY“PHY_mode”上传输所需的时间（以微秒为单位）。*/
uint32_t ble_ll_pdu_tx_time_get(uint16_t payload_len, int phy_mode);

/* 计算PHY“PHY_mode”上“usecs”期间可以传输的PDU有效载荷的最大八位字节。*/
uint16_t ble_ll_pdu_max_tx_octets_get(uint32_t usecs, int phy_mode);

/* 这个地址是可解析的私有地址吗？*/
int ble_ll_is_rpa(const uint8_t *addr, uint8_t addr_type);

int ble_ll_addr_subtype(const uint8_t *addr, uint8_t addr_type);

/* 这个地址是身份地址吗？*/
int ble_ll_addr_is_id(uint8_t *addr, uint8_t addr_type);

/* “addr”是我们的设备地址吗addr_type'是公共的（0）或随机的（！=0）*/
int ble_ll_is_our_devaddr(uint8_t *addr, int addr_type);

/* 获取标识地址“addr_type”是公共的（0）或随机的（！=0）*/
uint8_t *ble_ll_get_our_devaddr(uint8_t addr_type);

/**
 * 调用以将数据包放入链路层传输数据包队列。
 *
 * @param txpdu 发送数据包的指针
 */
void ble_ll_acl_data_in(struct os_mbuf *txpkt);

/**
 * 为接收的PDU分配mbuf
 *
 * 该分配的mbuf（如果需要可以被链接）具有足够大的容量以存储给定长度的接收PDU。它不设置mbufs长度，因为在复制数据时，PHY必须这样做。
 *
 * @param len  PDU长度，包括PDU报头，不包括MIC（如果加密）
 *
 * @return mbuf足够大，可以在成功时存储收到的PDU，在失败时存储NULL（oom）
 */
struct os_mbuf *ble_ll_rxpdu_alloc(uint16_t len);

/* 告诉链接层发生了数据缓冲区溢出*/
void ble_ll_data_buffer_overflow(void);

/* 告诉链路层发生了硬件错误*/
void ble_ll_hw_error(void);

/*---PHY接口---*/
struct ble_mbuf_hdr;

/* 当数据包启动时由PHY调用*/
int ble_ll_rx_start(uint8_t *rxbuf, uint8_t chan, struct ble_mbuf_hdr *hdr);

/* 当数据包接收结束时由PHY调用*/
int ble_ll_rx_end(uint8_t *rxbuf, struct ble_mbuf_hdr *rxhdr);

/* 使用ble_phy_tx（）将助手回调到tx-mbuf*/
uint8_t ble_ll_tx_mbuf_pducb(uint8_t *dptr, void *pducb_arg, uint8_t *hdr_byte);
uint8_t ble_ll_tx_flat_mbuf_pducb(uint8_t *dptr, void *pducb_arg, uint8_t *hdr_byte);

/*---控制器API---*/
void ble_ll_mbuf_init(struct os_mbuf *m, uint8_t pdulen, uint8_t hdr);

/* 设置链接层状态*/
void ble_ll_state_set(uint8_t ll_state);

/* 获取链接层状态*/
uint8_t ble_ll_state_get(void);

/* 向LL任务发送事件*/
void ble_ll_event_send(struct ble_npl_event *ev);

/* 手动接收pdu至LL任务*/
void ble_ll_rx_pdu_in(struct os_mbuf *rxpdu);

/*
 * 设置公共地址
 *
 * 这可用于从供应商特定的存储中设置控制器公共地址，通常应在hal_bsp_init（）中完成。只能在LL初始化之前，即sysinit阶段之前调用。
 */
int ble_ll_set_public_addr(const uint8_t *addr);

/* 设置随机地址*/
int ble_ll_set_random_addr(const uint8_t *cmdbuf, uint8_t len, bool hci_adv_ext);

/* 等待响应计时器过期回调*/
void ble_ll_wfr_timer_exp(void *arg);

/* 读取链接层支持的功能集*/
uint64_t ble_ll_read_supp_features(void);

/* 设置主机支持的功能*/
int ble_ll_set_host_feat(const uint8_t *cmdbuf, uint8_t len);

/* 读取链接层支持的状态集*/
uint64_t ble_ll_read_supp_states(void);

/* 检查八位字节和时间是否有效。如果无效，则返回0*/
int ble_ll_chk_txrx_octets(uint16_t octets);
int ble_ll_chk_txrx_time(uint16_t time);

/* 随机数*/
int ble_ll_rand_init(void);
void ble_ll_rand_sample(uint8_t rnum);
int ble_ll_rand_data_get(uint8_t *buf, uint8_t len);
void ble_ll_rand_prand_get(uint8_t *prand);
int ble_ll_rand_start(void);

static inline int
ble_ll_get_addr_type(uint8_t txrxflag)
{
    if (txrxflag) {
        return BLE_HCI_ADV_OWN_ADDR_RANDOM;
    }
    return BLE_HCI_ADV_OWN_ADDR_PUBLIC;
}

/* 将usecs转换为记号并向上舍入到最近的记号*/
static inline uint32_t
ble_ll_usecs_to_ticks_round_up(uint32_t usecs)
{
    return os_cputime_usecs_to_ticks(usecs + 30);
}

#if MYNEWT_VAL(BLE_LL_CFG_FEAT_LE_ENCRYPTION)
/* LTK 0x4C68384139F574D836BCF34E9DFB01BF*/
extern const uint8_t g_bletest_LTK[];
extern uint16_t g_bletest_EDIV;
extern uint64_t g_bletest_RAND;
extern uint64_t g_bletest_SKDm;
extern uint64_t g_bletest_SKDs;
extern uint32_t g_bletest_IVm;
extern uint32_t g_bletest_IVs;
#endif

#if MYNEWT_VAL(BLE_LL_DTM)
void ble_ll_dtm_init(void);
#endif

#ifdef __cplusplus
}
#endif

#endif /* H_LL_ */

