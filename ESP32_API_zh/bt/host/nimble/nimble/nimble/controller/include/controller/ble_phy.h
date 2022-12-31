/*
 * 根据一个或多个贡献者许可协议向Apache Software Foundation（ASF）许可。有关版权所有权的更多信息，请参阅随本作品分发的通知文件。ASF根据Apache许可证2.0版（“许可证”）向您许可此文件；除非符合许可证，否则不得使用此文件。您可以在以下地址获取许可证副本：
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 * 除非适用法律要求或书面同意，否则根据许可证分发的软件是按“原样”分发的，无任何明示或暗示的担保或条件。有关许可证下权限和限制的具体语言，请参阅许可证。
 */

#ifndef H_BLE_PHY_
#define H_BLE_PHY_

#include "nimble/hci_common.h"

#ifdef __cplusplus
extern "C" {
#endif

/* 转发声明*/
struct os_mbuf;

/* 信道/频率定义*/
#define BLE_PHY_NUM_CHANS           (40)
#define BLE_PHY_NUM_DATA_CHANS      (37)
#define BLE_PHY_CHAN0_FREQ_MHZ      (2402)
#define BLE_PHY_DATA_CHAN0_FREQ_MHZ (2404)
#define BLE_PHY_CHAN_SPACING_MHZ    (2)
#define BLE_PHY_NUM_ADV_CHANS       (3)
#define BLE_PHY_ADV_CHAN_START      (37)

/* 权力*/
#define BLE_PHY_MAX_PWR_DBM         (10)

/* 偏离*/
#define BLE_PHY_DEV_KHZ             (185)
#define BLE_PHY_BINARY_ZERO         (-BLE_PHY_DEV)
#define BLE_PHY_BINARY_ONE          (BLE_PHY_DEV)

/* 最大时钟漂移*/
#define BLE_PHY_MAX_DRIFT_PPM       (50)

/* 数据速率*/
#define BLE_PHY_BIT_RATE_BPS        (1000000)

/* 宏*/
#define BLE_IS_ADV_CHAN(chan)       (chan >= BLE_PHY_ADV_CHAN_START)
#define BLE_IS_DATA_CHAN(chan)      (chan < BLE_PHY_ADV_CHAN_START)

/* PHY状态*/
#define BLE_PHY_STATE_IDLE          (0)
#define BLE_PHY_STATE_RX            (1)
#define BLE_PHY_STATE_TX            (2)

/* BLE PHY转换*/
#define BLE_PHY_TRANSITION_NONE     (0)
#define BLE_PHY_TRANSITION_RX_TX    (1)
#define BLE_PHY_TRANSITION_TX_RX    (2)

/* PHY错误代码*/
#define BLE_PHY_ERR_RADIO_STATE     (1)
#define BLE_PHY_ERR_INIT            (2)
#define BLE_PHY_ERR_INV_PARAM       (3)
#define BLE_PHY_ERR_NO_BUFS         (4)
#define BLE_PHY_ERR_TX_LATE         (5)
#define BLE_PHY_ERR_RX_LATE         (6)

/* 最大PDU长度。包括2字节的LL报头和255字节的有效负载。*/
#define BLE_PHY_MAX_PDU_LEN         (257)

/* 等待响应计时器*/
typedef void (*ble_phy_tx_end_func)(void *arg);

/* 初始化PHY*/
int ble_phy_init(void);

/* 重置PHY*/
int ble_phy_reset(void);

/* 设置PHY信道*/
int ble_phy_setchan(uint8_t chan, uint32_t access_addr, uint32_t crcinit);

/* 设置传输开始时间*/
int ble_phy_tx_set_start_time(uint32_t cputime, uint8_t rem_usecs);

/* 设置接收开始时间*/
int ble_phy_rx_set_start_time(uint32_t cputime, uint8_t rem_usecs);

/* 设置传输结束回调和参数*/
void ble_phy_set_txend_cb(ble_phy_tx_end_func txend_cb, void *arg);

typedef uint8_t (*ble_phy_tx_pducb_t)(uint8_t *dptr, void *pducb_arg,
                                      uint8_t *hdr_byte);

/* 将PHY置于传输模式*/
int ble_phy_tx(ble_phy_tx_pducb_t pducb, void *pducb_arg, uint8_t end_trans);

/* 将PHY置于接收模式*/
int ble_phy_rx(void);

/* 将接收到的PHY缓冲区复制到分配的pdu中*/
void ble_phy_rxpdu_copy(uint8_t *dptr, struct os_mbuf *rxpdu);

/* 设置发射功率*/
int ble_phy_txpwr_set(int dbm);

/* 获得范围内允许的最高功率*/
int ble_phy_txpower_round(int dbm);

/* 获取发射功率*/
int ble_phy_txpwr_get(void);

/* 将RX路径功率补偿值设置为整数dB*/
void ble_phy_set_rx_pwr_compensation(int8_t compensation);

/* 禁用PHY*/
void ble_phy_disable(void);

#define BLE_PHY_WFR_ENABLE_RX       (0)
#define BLE_PHY_WFR_ENABLE_TXRX     (1)

void ble_phy_wfr_enable(int txrx, uint8_t tx_phy_mode, uint32_t wfr_usecs);

/* 启动射频时钟*/
void ble_phy_rfclk_enable(void);

/* 停止射频时钟*/
void ble_phy_rfclk_disable(void);

/*
 * 用于在wfr计时器到期或收到帧后重新启动同一频道上的接收。
 */
void ble_phy_restart_rx(void);

/* 获取PHY的当前状态*/
int ble_phy_state_get(void);

/* 获取收发器的当前状态*/
uint8_t ble_phy_xcvr_state_get(void);

/* 如果接收已开始，则返回“true”*/
int ble_phy_rx_started(void);

/*
 * 返回数据信道PDU支持的最大tx/rx PDU负载大小（以字节为单位）（这不适用于广告信道PDU）。注意，数据信道PDU由2字节报头、有效载荷和可选MIC组成。最大有效负载为251字节。
 */
uint8_t ble_phy_max_data_pdu_pyld(void);

/* 获取当前访问地址*/
uint32_t ble_phy_access_addr_get(void);

/* 启用加密*/
void ble_phy_encrypt_enable(uint64_t pkt_counter, uint8_t *iv, uint8_t *key,
                            uint8_t is_master);

/* 禁用加密*/
void ble_phy_encrypt_disable(void);

/* 设置LE加密使用的数据包计数器和目录*/
void ble_phy_encrypt_set_pkt_cntr(uint64_t pkt_counter, int dir);

/* 启用phy解析列表*/
void ble_phy_resolv_list_enable(void);

/* 禁用phy解析列表*/
void ble_phy_resolv_list_disable(void);

/*
 * 1M、2M和编码S＝8的PHY模式值与PHY的对应值相同。这使得“phy”和“phy_mode”之间的转换更容易，这也意味着Coded的默认编码将为S=8，除非明确转换为S=2。
 */
#define BLE_PHY_MODE_CODED_500KBPS  (0)
#define BLE_PHY_MODE_1M             (1)
#define BLE_PHY_MODE_2M             (2)
#define BLE_PHY_MODE_CODED_125KBPS  (3)

/* 不同模式的数量*/
#define BLE_PHY_NUM_MODE            (4)

/* PHY编号（与HCI兼容）*/
#define BLE_PHY_1M                  (BLE_HCI_LE_PHY_1M)
#define BLE_PHY_2M                  (BLE_HCI_LE_PHY_2M)
#define BLE_PHY_CODED               (BLE_HCI_LE_PHY_CODED)

/* PHY位掩码（与HCI兼容）*/
#define BLE_PHY_MASK_1M             (BLE_HCI_LE_PHY_1M_PREF_MASK)
#define BLE_PHY_MASK_2M             (BLE_HCI_LE_PHY_2M_PREF_MASK)
#define BLE_PHY_MASK_CODED          (BLE_HCI_LE_PHY_CODED_PREF_MASK)

#if (MYNEWT_VAL(BLE_LL_CFG_FEAT_LE_2M_PHY) || MYNEWT_VAL(BLE_LL_CFG_FEAT_LE_CODED_PHY))
uint32_t ble_phy_mode_pdu_start_off(int phy);
void ble_phy_mode_set(uint8_t tx_phy_mode, uint8_t rx_phy_mode);
#else
#define ble_phy_mode_pdu_start_off(phy)     (40)

#endif

int ble_phy_get_cur_phy(void);
static inline int ble_ll_phy_to_phy_mode(int phy, int phy_options)
{
    int phy_mode;

    /*
     * “phy”值可以用作“phy_mode”值，除非明确要求进行S=2编码。默认情况下，我们将使用S=2作为编码。
     */
    phy_mode = phy;

#if MYNEWT_VAL(BLE_LL_CFG_FEAT_LE_CODED_PHY)
    if (phy == BLE_PHY_CODED && phy_options == BLE_HCI_LE_PHY_CODED_S2_PREF) {
        phy_mode = BLE_PHY_MODE_CODED_500KBPS;
    }
#endif

    return phy_mode;
}

#if MYNEWT_VAL(BLE_LL_DTM)
void ble_phy_enable_dtm(void);
void ble_phy_disable_dtm(void);
#endif

#ifdef __cplusplus
}
#endif

#endif /* H_BLE_PHY_ */

