/*
 * 根据一个或多个贡献者许可协议向Apache Software Foundation（ASF）许可。有关版权所有权的更多信息，请参阅随本作品分发的通知文件。ASF根据Apache许可证2.0版（“许可证”）向您许可此文件；除非符合许可证，否则不得使用此文件。您可以在以下地址获取许可证副本：
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 * 除非适用法律要求或书面同意，否则根据许可证分发的软件是按“原样”分发的，无任何明示或暗示的担保或条件。有关许可证下权限和限制的具体语言，请参阅许可证。
 */

#ifndef H_BLE_LL_ADV_
#define H_BLE_LL_ADV_

#include "syscfg/syscfg.h"

#ifdef __cplusplus
extern "C" {
#endif

/*
 * ADV事件计时T_advEvent=advInterval+advDelay
 *
 *      advInterval：增量625 usecs advDelay:RAND[0，10]毫秒
 *
 */
#define BLE_LL_ADV_ITVL                 (625)           /* 用途*/
#define BLE_LL_ADV_ITVL_MIN             (32)            /* 单位*/
#define BLE_LL_ADV_ITVL_MAX             (16384)         /* 单位*/
#define BLE_LL_ADV_ITVL_MS_MIN          (20)            /* 毫秒*/
#define BLE_LL_ADV_ITVL_MS_MAX          (10240)         /* 毫秒*/
#define BLE_LL_ADV_ITVL_SCAN_MIN        (160)           /* 单位*/
#define BLE_LL_ADV_ITVL_SCAN_MS_MIN     (100)           /* 毫秒*/
#define BLE_LL_ADV_ITVL_NONCONN_MS_MIN  (100)           /* 毫秒*/
#define BLE_LL_ADV_DELAY_MS_MIN         (0)             /* 毫秒*/
#define BLE_LL_ADV_DELAY_MS_MAX         (10)            /* 毫秒*/
#define BLE_LL_ADV_PDU_ITVL_LD_MS_MAX   (10)            /* 毫秒*/
#define BLE_LL_ADV_PDU_ITVL_HD_MS_MAX   (3750)          /* 用途*/
#define BLE_LL_ADV_STATE_HD_MAX         (1280)          /* 毫秒*/
#define BLE_LL_ADV_PERIODIC_ITVL        (1250)          /* 用途*/

/* 最大广告数据长度*/
#define BLE_ADV_LEGACY_DATA_MAX_LEN     (31)
#define BLE_ADV_LEGACY_MAX_PKT_LEN      (37)

#if MYNEWT_VAL(BLE_LL_CFG_FEAT_LL_EXT_ADV)
#define BLE_ADV_DATA_MAX_LEN            MYNEWT_VAL(BLE_EXT_ADV_MAX_SIZE)
#else
#define BLE_ADV_DATA_MAX_LEN            BLE_ADV_LEGACY_DATA_MAX_LEN
#endif

/*
 * ADV_IND
 *      ->AdvA（6字节）
 *      ->AdvData（0-31字节）
 *
 *  广告地址（AdvA）是公共地址（TxAdd=0）或随机地址（TxAdd=1）
 */
#define BLE_ADV_IND_MIN_LEN             (6)
#define BLE_ADV_IND_MAX_LEN             (37)

/*
 * ADV_DIRECT_IND
 *      ->AdvA（6字节）
 *      ->InitA（6字节）
 *
 *  AdvA是广告商公共地址（TxAdd=0）或随机地址（TxAdd=1）。
 *
 *  InitA是启动器的公共或随机地址。这是此数据包的地址。
 *
 */
#define BLE_ADV_DIRECT_IND_LEN          (12)

/*
 * ADV_NONCONN_IND
 *      ->AdvA（6字节）
 *      ->AdvData（0-31字节）
 *
 *  广告地址（AdvA）是公共地址（TxAdd=0）或随机地址（TxAdd=1）
 *
 */
#define BLE_ADV_NONCONN_IND_MIN_LEN     (6)
#define BLE_ADV_NONCONN_IND_MAX_LEN     (37)

/*
 * ADV_SCAN_IND
 *      ->AdvA（6字节）
 *      ->AdvData（0-31字节）
 *
 *  广告地址（AdvA）是公共地址（TxAdd=0）或随机地址（TxAdd=1）
 *
 */
#define BLE_ADV_SCAN_IND_MIN_LEN        (6)
#define BLE_ADV_SCAN_IND_MAX_LEN        (37)

/*---- HCI ----*/
struct ble_ll_adv_sm;
struct ble_ll_conn_sm;

/* 启动广告客户*/
int ble_ll_adv_start_req(uint8_t adv_chanmask, uint8_t adv_type,
                         uint8_t *init_addr, uint16_t adv_itvl, void *handle);

/* 开始或停止广告*/
int ble_ll_hci_adv_set_enable(const uint8_t *cmdbuf, uint8_t len);

/* 设置旧广告数据*/
int ble_ll_hci_set_adv_data(const uint8_t *cmdbuf, uint8_t len);

/* 设置扫描响应数据*/
int ble_ll_hci_set_scan_rsp_data(const uint8_t *cmd, uint8_t cmd_len);

/* 设置广告参数*/
int ble_ll_adv_set_adv_params(const uint8_t *cmdbuf, uint8_t len);

/* 读取广告频道功率*/
int ble_ll_adv_read_txpwr(uint8_t *rspbuf, uint8_t *rsplen);

/*----BLE LL使用的API----*/
/* 发送连接完成事件*/
void ble_ll_adv_send_conn_comp_ev(struct ble_ll_conn_sm *connsm,
                                  struct ble_mbuf_hdr *rxhdr);

/* 返回本地可解析的私有地址*/
uint8_t *ble_ll_adv_get_local_rpa(struct ble_ll_adv_sm *advsm);

/* 返回对等方可解析的私有地址*/
uint8_t *ble_ll_adv_get_peer_rpa(struct ble_ll_adv_sm *advsm);

/* 调用以初始化广告功能。*/
void ble_ll_adv_init(void);

/* 当LL等待响应计时器在广告状态下过期时调用*/
void ble_ll_adv_wfr_timer_exp(void);

/* 调用以重置广告客户。*/
void ble_ll_adv_reset(void);

/* 处于广告状态时在rx pdu启动时调用*/
int ble_ll_adv_rx_isr_start(uint8_t pdu_type);

/* 处于广告状态时在rx pdu端调用*/
int ble_ll_adv_rx_isr_end(uint8_t pdu_type, struct os_mbuf *rxpdu, int crcok);

/* 在链路层任务处处理接收的数据包*/
void ble_ll_adv_rx_pkt_in(uint8_t ptype, uint8_t *rxbuf,
                          struct ble_mbuf_hdr *hdr);

/* 表示白名单是否可以更改的布尔函数*/
int ble_ll_adv_can_chg_whitelist(void);

/*
 * 当广告事件已从调度程序中删除而未运行时调用。
 */
void ble_ll_adv_event_rmvd_from_sched(struct ble_ll_adv_sm *advsm);

/*
 * 当周期性事件已从调度程序中删除而未运行时调用。
 */
void ble_ll_adv_periodic_rmvd_from_sched(struct ble_ll_adv_sm *advsm);

/* 调用以停止当前正在运行的广告事件*/
void ble_ll_adv_halt(void);

/* 调用以确定是否启用广告*/
uint8_t ble_ll_adv_enabled(void);

int ble_ll_adv_hci_set_random_addr(const uint8_t *cmdbuf, uint8_t len);
int ble_ll_adv_set_random_addr(const uint8_t *addr, uint8_t instance);
int ble_ll_adv_remove(const uint8_t *addr, uint8_t len);
int ble_ll_adv_clear_all(void);
int ble_ll_adv_ext_set_param(const uint8_t *cmdbuf, uint8_t len,
                             uint8_t *rspbuf, uint8_t *rsplen);
int ble_ll_adv_ext_set_adv_data(const uint8_t *cmdbuf, uint8_t cmdlen);
int ble_ll_adv_ext_set_scan_rsp(const uint8_t *cmdbuf, uint8_t cmdlen);
int ble_ll_adv_ext_set_enable(const uint8_t *cmdbuf, uint8_t len);

int ble_ll_adv_periodic_set_param(const uint8_t *cmdbuf, uint8_t len);
int ble_ll_adv_periodic_set_data(const uint8_t *cmdbuf, uint8_t len);
int ble_ll_adv_periodic_enable(const uint8_t *cmdbuf, uint8_t len);

int ble_ll_adv_periodic_set_info_transfer(const uint8_t *cmdbuf, uint8_t len,
                                          uint8_t *rspbuf, uint8_t *rsplen);

/* 调用以通知有关RPA轮换的adv代码*/
void ble_ll_adv_rpa_timeout(void);

#ifdef __cplusplus
}
#endif

#endif /* H_BLE_LL_ADV_ */

