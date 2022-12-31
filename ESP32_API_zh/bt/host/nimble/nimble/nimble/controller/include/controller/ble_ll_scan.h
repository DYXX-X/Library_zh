/*
 * 根据一个或多个贡献者许可协议向Apache Software Foundation（ASF）许可。有关版权所有权的更多信息，请参阅随本作品分发的通知文件。ASF根据Apache许可证2.0版（“许可证”）向您许可此文件；除非符合许可证，否则不得使用此文件。您可以在以下地址获取许可证副本：
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 * 除非适用法律要求或书面同意，否则根据许可证分发的软件是按“原样”分发的，无任何明示或暗示的担保或条件。有关许可证下权限和限制的具体语言，请参阅许可证。
 */

#ifndef H_BLE_LL_SCAN_
#define H_BLE_LL_SCAN_

#include "controller/ble_ll_sched.h"
#include "hal/hal_timer.h"
#include "syscfg/syscfg.h"
#include "nimble/nimble_npl.h"

#ifdef __cplusplus
extern "C" {
#endif

/*
 * SCAN_REQ
 *      ->ScanA（6字节）
 *      ->AdvA（6字节）
 *
 *  ScanA是扫描仪公共（TxAdd=0）或随机（TxAdd=1）地址AdvaA是广告商公共（RxAdd=0）和随机（RxAdd=1）地址。
 *
 * LL在扫描状态下发送；由处于广告状态的LL接收。广告地址是此帧的预期收件人。
 */
#define BLE_SCAN_REQ_LEN                (12)

/*
 * SCAN_RSP
 *      ->AdvA（6字节）
 *      ->ScanRspData（0-31字节）
 *
 *  AdvaA是广告商的公共（TxAdd=0）或随机（TxAdd=1）地址。ScanRspData可能包含来自广告商主机的任何数据。
 *
 * LL在广告状态下发送；由处于扫描状态的LL接收。
 */
#define BLE_SCAN_RSP_LEGACY_DATA_MAX_LEN       (31)
#define BLE_SCAN_LEGACY_MAX_PKT_LEN            (37)

#if MYNEWT_VAL(BLE_LL_CFG_FEAT_LL_EXT_ADV)
#define BLE_SCAN_RSP_DATA_MAX_LEN       MYNEWT_VAL(BLE_EXT_ADV_MAX_SIZE)

/* 对于蓝牙5.0，我们需要两个PHY的状态机*/
#define BLE_LL_SCAN_PHY_NUMBER          (2)
#else
#define BLE_LL_SCAN_PHY_NUMBER          (1)
#define BLE_SCAN_RSP_DATA_MAX_LEN       BLE_SCAN_RSP_LEGACY_DATA_MAX_LEN
#endif

#define PHY_UNCODED                    (0)
#define PHY_CODED                      (1)

#define BLE_LL_EXT_ADV_MODE_NON_CONN    (0x00)
#define BLE_LL_EXT_ADV_MODE_CONN        (0x01)
#define BLE_LL_EXT_ADV_MODE_SCAN        (0x02)

/* 所有值都存储为记号*/
struct ble_ll_scan_timing {
    uint32_t interval;
    uint32_t window;
    uint32_t start_time;
};

struct ble_ll_scan_params
{
    uint8_t phy;
    uint8_t own_addr_type;
    uint8_t scan_filt_policy;
    uint8_t configured;
    uint8_t scan_type;
    uint8_t scan_chan;
    struct ble_ll_scan_timing timing;
};

#define BLE_LL_AUX_HAS_ADVA                     0x01
#define BLE_LL_AUX_HAS_TARGETA                  0x02
#define BLE_LL_AUX_HAS_ADI                      0x04
#define BLE_LL_AUX_IS_MATCHED                   0x08
#define BLE_LL_AUX_IS_TARGETA_RESOLVED          0x10

#define BLE_LL_AUX_FLAG_HCI_SENT_ANY            0x02
#define BLE_LL_AUX_FLAG_HCI_SENT_COMPLETED      0x04
#define BLE_LL_AUX_FLAG_HCI_SENT_TRUNCATED      0x08
#define BLE_LL_AUX_FLAG_SCAN_COMPLETE           0x10
#define BLE_LL_AUX_FLAG_SCAN_ERROR              0x20
#define BLE_LL_AUX_FLAG_AUX_ADV_RECEIVED        0x40
#define BLE_LL_AUX_FLAG_AUX_CHAIN_RECEIVED      0x80

struct ble_ll_aux_data {
    uint8_t flags;

    /*
     * 由于aux_data可以从ISR和LL访问，我们有单独的标志副本，以确保ISR在LL使用标志时不会修改标志。ISR更新“flags_ISR”，LL将其添加到“flags_LL”中，然后用于进一步处理，如果计划对给定“aux_data”进行另一次扫描，则允许更新“flags _ISR”。注意，aux_data有效时，不能取消设置标志。
     */
    uint8_t flags_isr;
    uint8_t flags_ll;

    uint8_t ref_cnt;
    uint8_t chan;
    uint8_t aux_phy;
    uint8_t aux_primary_phy;
    uint8_t mode;
    uint8_t scanning;
#if MYNEWT_VAL(BLE_LL_CFG_FEAT_LL_PRIVACY)
    int8_t rpa_index;
#endif
    uint16_t adi;
    uint32_t offset;
    uint8_t offset_units;
    uint8_t adva[6];
    uint8_t adva_type;
    uint8_t targeta[6];
    uint8_t targeta_type;
    uint16_t evt_type;
    struct ble_ll_sched_item sch;
    struct ble_hci_ev *evt;
    struct ble_npl_event ev;
};

struct ble_ll_scan_pdu_data {
    uint8_t hdr_byte;
    /* SCAN_REQ的ScanA和CONNECT_IND的InitA*/
    union {
        uint8_t scana[BLE_DEV_ADDR_LEN];
        uint8_t inita[BLE_DEV_ADDR_LEN];
    };
    uint8_t adva[BLE_DEV_ADDR_LEN];
};

struct ble_ll_scan_sm
{
    uint8_t scan_enabled;
    uint8_t own_addr_type;
    uint8_t scan_filt_dups;
    uint8_t scan_rsp_pending;
    uint8_t scan_rsp_cons_fails;
    uint8_t scan_rsp_cons_ok;
    uint8_t scan_peer_rpa[BLE_DEV_ADDR_LEN];
#if MYNEWT_VAL(BLE_LL_CFG_FEAT_LL_PRIVACY)
    ble_npl_time_t scan_nrpa_timer;
    uint8_t scan_nrpa[BLE_DEV_ADDR_LEN];
#endif
    struct ble_ll_scan_pdu_data pdu_data;

    /* 三十： 我们可以计算每个phy的回退吗？*/
    uint16_t upper_limit;
    uint16_t backoff_count;
    uint32_t scan_win_start_time;
    struct ble_npl_event scan_sched_ev;
    struct hal_timer scan_timer;
    struct ble_npl_event scan_interrupted_ev;

#if MYNEWT_VAL(BLE_LL_CFG_FEAT_LL_EXT_ADV)
    struct hal_timer duration_timer;
    struct hal_timer period_timer;
    uint32_t duration_ticks;
    uint32_t period_ticks;
    uint8_t ext_scanning;
#endif

    uint8_t restart_timer_needed;
    struct ble_ll_aux_data *cur_aux_data;

    struct ble_ll_scan_params *scanp;
    struct ble_ll_scan_params *scanp_next;
    struct ble_ll_scan_params scanp_phys[BLE_LL_SCAN_PHY_NUMBER];
};

/* 扫描类型*/
#define BLE_SCAN_TYPE_PASSIVE   (BLE_HCI_SCAN_TYPE_PASSIVE)
#define BLE_SCAN_TYPE_ACTIVE    (BLE_HCI_SCAN_TYPE_ACTIVE)
#define BLE_SCAN_TYPE_INITIATE  (2)

/*---- HCI ----*/
/* 设置扫描参数*/
int ble_ll_scan_set_scan_params(const uint8_t *cmdbuf, uint8_t len);

/* 打开/关闭扫描*/
int ble_ll_hci_scan_set_enable(const uint8_t *cmdbuf, uint8_t len);
int ble_ll_hci_ext_scan_set_enable(const uint8_t *cmdbuf, uint8_t len);

#if MYNEWT_VAL(BLE_LL_CFG_FEAT_LL_EXT_ADV)
int ble_ll_set_ext_scan_params(const uint8_t *cmdbuf, uint8_t len);
#endif

/*---控制器内部API---*/
/* 初始化扫描仪*/
void ble_ll_scan_init(void);

/* 重置扫描仪*/
void ble_ll_scan_reset(void);

/* 当链路层开始接收PDU并处于扫描状态时调用*/
int ble_ll_scan_rx_isr_start(uint8_t pdu_type, uint16_t *rxflags);

/* 当链路层在扫描时完成接收PDU时调用*/
int ble_ll_scan_rx_isr_end(struct os_mbuf *rxpdu, uint8_t crcok);

/* 处理扫描响应PDU*/
void ble_ll_scan_rx_pkt_in(uint8_t pdu_type, struct os_mbuf *om,
                           struct ble_mbuf_hdr *hdr);

/* 表示白名单是否可以更改的布尔函数*/
int ble_ll_scan_can_chg_whitelist(void);

/* 如果启用扫描，则布尔函数返回true*/
int ble_ll_scan_enabled(void);

/* 如果白名单已启用扫描，则布尔函数返回true*/
int ble_ll_scan_whitelist_enabled(void);

/* 启动时初始化扫描仪*/
struct hci_create_conn;
int ble_ll_scan_initiator_start(struct hci_create_conn *hcc,
                                struct ble_ll_scan_sm **sm);

/* 返回PDU数据的存储（用于SCAN_REQ或CONNECT_IND）*/
struct ble_ll_scan_pdu_data *ble_ll_scan_get_pdu_data(void);

/* 调用以设置最后连接的对等方的可解析专用地址*/
void ble_ll_scan_set_peer_rpa(uint8_t *rpa);

/* 返回上次连接的对等RPA*/
uint8_t *ble_ll_scan_get_peer_rpa(void);

/* 返回扫描仪/启动器使用的本地RPA*/
uint8_t *ble_ll_scan_get_local_rpa(void);

/* 停止扫描状态机*/
void ble_ll_scan_sm_stop(int chk_disable);

/* 继续扫描*/
void ble_ll_scan_chk_resume(void);

/* 在扫描模式下等待响应计时器过期时调用*/
void ble_ll_scan_wfr_timer_exp(void);

/* 扫描可能中断时调用*/
void ble_ll_scan_interrupted(struct ble_ll_scan_sm *scansm);

int ble_ll_scan_adv_decode_addr(uint8_t pdu_type, uint8_t *rxbuf,
                                struct ble_mbuf_hdr *ble_hdr,
                                uint8_t **addr, uint8_t *addr_type,
                                uint8_t **inita, uint8_t *init_addr_type,
                                int *ext_mode);

#if MYNEWT_VAL(BLE_LL_CFG_FEAT_LL_EXT_ADV)
int ble_ll_scan_update_aux_data(struct ble_mbuf_hdr *ble_hdr, uint8_t *rxbuf,
                                bool *adva_present);

/* 启动时初始化扩展扫描仪*/
struct hci_ext_create_conn;
int ble_ll_scan_ext_initiator_start(struct hci_ext_create_conn *hcc,
                                    struct ble_ll_scan_sm **sm);

/* 调用以分析扩展广告*/
struct ble_ll_aux_data *ble_ll_scan_aux_data_ref(struct ble_ll_aux_data *aux_scan);
void ble_ll_scan_aux_data_unref(struct ble_ll_aux_data *aux_scan);
void ble_ll_scan_end_adv_evt(struct ble_ll_aux_data *aux_data);
#endif

/* 调用以停止当前正在运行的扫描*/
void ble_ll_scan_halt(void);

#ifdef __cplusplus
}
#endif

#endif /* H_BLE_LL_SCAN_ */

