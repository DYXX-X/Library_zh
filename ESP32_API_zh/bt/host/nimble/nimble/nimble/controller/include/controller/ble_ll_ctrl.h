/*
 * 根据一个或多个贡献者许可协议向Apache Software Foundation（ASF）许可。有关版权所有权的更多信息，请参阅随本作品分发的通知文件。ASF根据Apache许可证2.0版（“许可证”）向您许可此文件；除非符合许可证，否则不得使用此文件。您可以在以下地址获取许可证副本：
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 * 除非适用法律要求或书面同意，否则根据许可证分发的软件是按“原样”分发的，无任何明示或暗示的担保或条件。有关许可证下权限和限制的具体语言，请参阅许可证。
 */

#ifndef H_BLE_LL_CTRL_
#define H_BLE_LL_CTRL_

#ifdef __cplusplus
extern "C" {
#endif

/*
 * LL控制程序。该“枚举”不在规范中；它用于确定连接中当前正在运行的LL控制程序以及可能挂起的LL控制过程。
 */
#define BLE_LL_CTRL_PROC_CONN_UPDATE    (0)
#define BLE_LL_CTRL_PROC_CHAN_MAP_UPD   (1)
#define BLE_LL_CTRL_PROC_ENCRYPT        (2)
#define BLE_LL_CTRL_PROC_FEATURE_XCHG   (3)
#define BLE_LL_CTRL_PROC_VERSION_XCHG   (4)
#define BLE_LL_CTRL_PROC_TERMINATE      (5)
#define BLE_LL_CTRL_PROC_CONN_PARAM_REQ (6)
#define BLE_LL_CTRL_PROC_LE_PING        (7)
#define BLE_LL_CTRL_PROC_DATA_LEN_UPD   (8)
#define BLE_LL_CTRL_PROC_PHY_UPDATE     (9)
#define BLE_LL_CTRL_PROC_NUM            (10)
#define BLE_LL_CTRL_PROC_IDLE           (255)

/* 检查特定控制程序是否正在运行*/
#define IS_PENDING_CTRL_PROC(sm, proc)  (sm->pending_ctrl_procs & (1 << proc))
#define CLR_PENDING_CTRL_PROC(sm, proc) (sm->pending_ctrl_procs &= ~(1 << proc))

/* LL控制程序超时*/
#define BLE_LL_CTRL_PROC_TIMEOUT_MS     (40000) /* 太太*/

/*
 * LL CTRL PDU格式
 *  ->操作码（1字节）
 *  ->数据（0-26字节）
 */
#define BLE_LL_CTRL_CONN_UPDATE_IND     (0)
#define BLE_LL_CTRL_CHANNEL_MAP_REQ     (1)
#define BLE_LL_CTRL_TERMINATE_IND       (2)
#define BLE_LL_CTRL_ENC_REQ             (3)
#define BLE_LL_CTRL_ENC_RSP             (4)
#define BLE_LL_CTRL_START_ENC_REQ       (5)
#define BLE_LL_CTRL_START_ENC_RSP       (6)
#define BLE_LL_CTRL_UNKNOWN_RSP         (7)
#define BLE_LL_CTRL_FEATURE_REQ         (8)
#define BLE_LL_CTRL_FEATURE_RSP         (9)
#define BLE_LL_CTRL_PAUSE_ENC_REQ       (10)
#define BLE_LL_CTRL_PAUSE_ENC_RSP       (11)
#define BLE_LL_CTRL_VERSION_IND         (12)
#define BLE_LL_CTRL_REJECT_IND          (13)
#define BLE_LL_CTRL_SLAVE_FEATURE_REQ   (14)
#define BLE_LL_CTRL_CONN_PARM_REQ       (15)
#define BLE_LL_CTRL_CONN_PARM_RSP       (16)
#define BLE_LL_CTRL_REJECT_IND_EXT      (17)
#define BLE_LL_CTRL_PING_REQ            (18)
#define BLE_LL_CTRL_PING_RSP            (19)
#define BLE_LL_CTRL_LENGTH_REQ          (20)
#define BLE_LL_CTRL_LENGTH_RSP          (21)
#define BLE_LL_CTRL_PHY_REQ             (22)
#define BLE_LL_CTRL_PHY_RSP             (23)
#define BLE_LL_CTRL_PHY_UPDATE_IND      (24)
#define BLE_LL_CTRL_MIN_USED_CHAN_IND   (25)
#define BLE_LL_CTRL_CTE_REQ             (26)
#define BLE_LL_CTRL_CTE_RSP             (27)
#define BLE_LL_CTRL_PERIODIC_SYNC_IND   (28)
#define BLE_LL_CTRL_CLOCK_ACCURACY_REQ  (29)
#define BLE_LL_CTRL_CLOCK_ACCURACY_RSP  (30)

/* 最大操作码值*/
#define BLE_LL_CTRL_OPCODES             (BLE_LL_CTRL_CLOCK_ACCURACY_RSP + 1)

extern const uint8_t g_ble_ll_ctrl_pkt_lengths[BLE_LL_CTRL_OPCODES];

/* 最大LL控制PDU大小*/
#if MYNEWT_VAL(BLE_LL_CFG_FEAT_LL_PERIODIC_ADV_SYNC_TRANSFER)
#define BLE_LL_CTRL_MAX_PDU_LEN         (35)
#else
#define BLE_LL_CTRL_MAX_PDU_LEN         (27)
#endif

/* LL控制连接更新请求*/
struct ble_ll_conn_upd_req
{
    uint8_t winsize;
    uint16_t winoffset;
    uint16_t interval;
    uint16_t latency;
    uint16_t timeout;
    uint16_t instant;
};
#define BLE_LL_CTRL_CONN_UPD_REQ_LEN        (11)

/* LL控制信道映射请求*/
struct ble_ll_chan_map_req
{
    uint8_t chmap[5];
    uint16_t instant;
};
#define BLE_LL_CTRL_CHAN_MAP_LEN            (7)

/*
 * LL控制终止ind
 *  ->错误代码（1字节）
 */
#define BLE_LL_CTRL_TERMINATE_IND_LEN      (1)

/* LL控制要求*/
struct ble_ll_enc_req
{
    uint8_t rand[8];
    uint16_t ediv;
    uint8_t skdm[8];
    uint32_t ivm;
};

#define BLE_LL_CTRL_ENC_REQ_LEN             (22)

/* LL控制外壳*/
struct ble_ll_enc_rsp
{
    uint8_t skds[8];
    uint32_t ivs;
};

#define BLE_LL_CTRL_ENC_RSP_LEN             (12)

/* LL控制启动/暂停enc请求和响应*/
#define BLE_LL_CTRL_START_ENC_REQ_LEN       (0)
#define BLE_LL_CTRL_START_ENC_RSP_LEN       (0)
#define BLE_LL_CTRL_PAUSE_ENC_REQ_LEN       (0)
#define BLE_LL_CTRL_PAUSE_ENC_RSP_LEN       (0)

/*
 * LL控制未知响应
 *  ->1字节，包含未知或不受支持的操作码。
 */
#define BLE_LL_CTRL_UNK_RSP_LEN             (1)

/*
 * LL控制特性req和LL控制特性rsp
 *  ->包含设备支持的功能的8字节数据。
 */
#define BLE_LL_CTRL_FEATURE_LEN             (8)

/*
 * LL控制版本ind
 *  ->version（1字节）：包含蓝牙控制器规范的版本号。
 *  ->comp_id（2字节）包含控制器制造商的公司标识符。
 *  ->sub_ver_num：包含蓝牙控制器的实现或修订的唯一值。
 */
struct ble_ll_version_ind
{
    uint8_t ble_ctrlr_ver;
    uint16_t company_id;
    uint16_t sub_ver_num;
};

#define BLE_LL_CTRL_VERSION_IND_LEN         (5)

/*
 * LL控制拒绝ind
 *  ->错误代码（1字节）：包含请求被拒绝的原因。
 */
#define BLE_LL_CTRL_REJ_IND_LEN             (1)

/*
 * LL控制从属功能要求
 *  ->包含设备支持的功能的8字节数据。
 */
#define BLE_LL_CTRL_SLAVE_FEATURE_REQ_LEN   (8)

/* LL控制连接参数req和连接参数rsp*/
struct ble_ll_conn_params
{
    uint16_t interval_min;
    uint16_t interval_max;
    uint16_t latency;
    uint16_t timeout;
    uint8_t pref_periodicity;
    uint16_t ref_conn_event_cnt;
    uint16_t offset0;
    uint16_t offset1;
    uint16_t offset2;
    uint16_t offset3;
    uint16_t offset4;
    uint16_t offset5;
};

#define BLE_LL_CTRL_CONN_PARAMS_LEN     (23)

/* LL控制拒绝文本*/
struct ble_ll_reject_ind_ext
{
    uint8_t reject_opcode;
    uint8_t err_code;
};

#define BLE_LL_CTRL_REJECT_IND_EXT_LEN  (2)

/* LL控制ping req和ping rsp（不包含数据）*/
#define BLE_LL_CTRL_PING_LEN            (0)

/*
 * LL控制长度req和长度rsp
 *  ->max_rx_bytes（2字节）：定义connMaxRxOctets。范围27至251
 *  ->max_rx_time（2字节）：定义connMaxRxTime。范围328至2120 usecs。
 *  ->max_tx_bytes（2字节）：定义connMaxTxOctets。范围27至251
 *  ->max_tx_time（2字节）：定义connMaxTxTime。范围328至2120 usecs。
 */
struct ble_ll_len_req
{
    uint16_t max_rx_bytes;
    uint16_t max_rx_time;
    uint16_t max_tx_bytes;
    uint16_t max_tx_time;
};

#define BLE_LL_CTRL_LENGTH_REQ_LEN      (8)

/* PHY请求/响应*/
#define BLE_LL_CTRL_PHY_REQ_LEN         (2)
#define BLE_LL_CTRL_PHY_RSP_LEN         (2)
#define BLE_LL_CTRL_PHY_UPD_IND_LEN     (4)

/* 最小使用通道数*/
#define BLE_LL_CTRL_MIN_USED_CHAN_LEN   (2)

/* CTE REQ */
#define BLE_LL_CTRL_CTE_REQ_LEN         (1)

/* CTE RSP（不含数据）*/
#define BLE_LL_CTRL_CTE_RSP_LEN     (0)

/* 定期同步传输IND*/
#define BLE_LL_CTRL_PERIODIC_SYNC_IND_LEN   (34)

/* 时钟精度请求/响应*/
#define BLE_LL_CTRL_CLOCK_ACCURACY_REQ_LEN  (1)
#define BLE_LL_CTRL_CLOCK_ACCURACY_RSP_LEN  (1)

/* API */
struct ble_ll_conn_sm;
void ble_ll_ctrl_proc_start(struct ble_ll_conn_sm *connsm, int ctrl_proc);
void ble_ll_ctrl_proc_stop(struct ble_ll_conn_sm *connsm, int ctrl_proc);
int ble_ll_ctrl_rx_pdu(struct ble_ll_conn_sm *connsm, struct os_mbuf *om);
void ble_ll_ctrl_chk_proc_start(struct ble_ll_conn_sm *connsm);
void ble_ll_ctrl_terminate_start(struct ble_ll_conn_sm *connsm);
int ble_ll_ctrl_is_terminate_ind(uint8_t hdr, uint8_t opcode);
uint8_t ble_ll_ctrl_conn_param_reply(struct ble_ll_conn_sm *connsm,
                                     uint8_t *rsp,
                                     struct ble_ll_conn_params *req);
int ble_ll_ctrl_reject_ind_send(struct ble_ll_conn_sm *connsm,
                                uint8_t rej_opcode, uint8_t err);
int ble_ll_ctrl_start_enc_send(struct ble_ll_conn_sm *connsm);
int ble_ll_ctrl_enc_allowed_pdu_rx(struct os_mbuf *rxpdu);
int ble_ll_ctrl_enc_allowed_pdu_tx(struct os_mbuf_pkthdr *pkthdr);
int ble_ll_ctrl_tx_done(struct os_mbuf *txpdu, struct ble_ll_conn_sm *connsm);
int ble_ll_ctrl_is_start_enc_rsp(struct os_mbuf *txpdu);

void ble_ll_hci_ev_datalen_chg(struct ble_ll_conn_sm *connsm);
void ble_ll_hci_ev_rem_conn_parm_req(struct ble_ll_conn_sm *connsm,
                                     struct ble_ll_conn_params *cp);
void ble_ll_hci_ev_conn_update(struct ble_ll_conn_sm *connsm, uint8_t status);
void ble_ll_hci_ev_rd_rem_used_feat(struct ble_ll_conn_sm *connsm,
                                      uint8_t status);
void ble_ll_hci_ev_rd_rem_ver(struct ble_ll_conn_sm *connsm, uint8_t status);
void ble_ll_hci_ev_encrypt_chg(struct ble_ll_conn_sm *connsm, uint8_t status);
int ble_ll_hci_ev_ltk_req(struct ble_ll_conn_sm *connsm);
int ble_ll_hci_ev_hw_err(uint8_t hw_err);
void ble_ll_hci_ev_databuf_overflow(void);
void ble_ll_hci_ev_le_csa(struct ble_ll_conn_sm *connsm);
void ble_ll_hci_ev_send_scan_req_recv(uint8_t adv_handle, const uint8_t *peer,
                                      uint8_t peer_addr_type);
void ble_ll_hci_ev_send_scan_timeout(void);
void ble_ll_hci_ev_send_adv_set_terminated(uint8_t status, uint8_t adv_handle,
                                           uint16_t conn_handle, uint8_t events);
int ble_ll_hci_ev_phy_update(struct ble_ll_conn_sm *connsm, uint8_t status);
void ble_ll_calc_session_key(struct ble_ll_conn_sm *connsm);
void ble_ll_ctrl_phy_update_proc_complete(struct ble_ll_conn_sm *connsm);
void ble_ll_ctrl_initiate_dle(struct ble_ll_conn_sm *connsm);
void ble_ll_hci_ev_send_vendor_err(const char *file, uint32_t line);

uint8_t ble_ll_ctrl_phy_tx_transition_get(uint8_t phy_mask);
uint8_t ble_ll_ctrl_phy_from_phy_mask(uint8_t phy_mask);

#ifdef __cplusplus
}
#endif

#endif /* H_BLE_LL_CTRL_ */

