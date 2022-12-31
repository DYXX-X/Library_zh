/*
 * 根据一个或多个贡献者许可协议向Apache Software Foundation（ASF）许可。有关版权所有权的更多信息，请参阅随本作品分发的通知文件。ASF根据Apache许可证2.0版（“许可证”）向您许可此文件；除非符合许可证，否则不得使用此文件。您可以在以下地址获取许可证副本：
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 * 除非适用法律要求或书面同意，否则根据许可证分发的软件是按“原样”分发的，无任何明示或暗示的担保或条件。有关许可证下权限和限制的具体语言，请参阅许可证。
 */

#ifndef H_BLE_L2CAP_SIG_
#define H_BLE_L2CAP_SIG_

#include "syscfg/syscfg.h"

#ifdef __cplusplus
extern "C" {
#endif

#define BLE_L2CAP_SIG_MTU           100  /* 这是我们自己的默认值。*/

#define BLE_L2CAP_SIG_HDR_SZ                4
struct ble_l2cap_sig_hdr {
    uint8_t op;
    uint8_t identifier;
    uint16_t length;
    uint8_t data[0];
} __attribute__((packed));

#define BLE_L2CAP_SIG_REJECT_MIN_SZ         2
struct ble_l2cap_sig_reject {
    uint16_t reason;
    uint8_t data[0];
} __attribute__((packed));

#define BLE_L2CAP_SIG_UPDATE_REQ_SZ         8
struct ble_l2cap_sig_update_req {
    uint16_t itvl_min;
    uint16_t itvl_max;
    uint16_t slave_latency;
    uint16_t timeout_multiplier;
} __attribute__((packed));

#define BLE_L2CAP_SIG_UPDATE_RSP_SZ         2
struct ble_l2cap_sig_update_rsp {
    uint16_t result;
} __attribute__((packed));

#define BLE_L2CAP_SIG_UPDATE_RSP_RESULT_ACCEPT  0x0000
#define BLE_L2CAP_SIG_UPDATE_RSP_RESULT_REJECT  0x0001

struct ble_l2cap_sig_le_con_req {
    uint16_t psm;
    uint16_t scid;
    uint16_t mtu;
    uint16_t mps;
    uint16_t credits;
} __attribute__((packed));

struct ble_l2cap_sig_le_con_rsp {
    uint16_t dcid;
    uint16_t mtu;
    uint16_t mps;
    uint16_t credits;
    uint16_t result;
} __attribute__((packed));

struct ble_l2cap_sig_credit_base_connect_req {
    uint16_t psm;
    uint16_t mtu;
    uint16_t mps;
    uint16_t credits;
    uint16_t scids[0];
} __attribute__((packed));

struct ble_l2cap_sig_credit_base_connect_rsp {
    uint16_t mtu;
    uint16_t mps;
    uint16_t credits;
    uint16_t result;
    uint16_t dcids[0];
} __attribute__((packed));

struct ble_l2cap_sig_credit_base_reconfig_req {
    uint16_t mtu;
    uint16_t mps;
    uint16_t dcids[0];
} __attribute__((packed));

struct ble_l2cap_sig_credit_base_reconfig_rsp {
    uint16_t result;
} __attribute__((packed));

struct ble_l2cap_sig_disc_req {
    uint16_t dcid;
    uint16_t scid;
} __attribute__((packed));

struct ble_l2cap_sig_disc_rsp {
    uint16_t dcid;
    uint16_t scid;
} __attribute__((packed));

struct ble_l2cap_sig_le_credits {
    uint16_t scid;
    uint16_t credits;
} __attribute__((packed));

void ble_l2cap_sig_hdr_parse(void *payload, uint16_t len,
                             struct ble_l2cap_sig_hdr *hdr);
int ble_l2cap_sig_reject_tx(uint16_t conn_handle,
                            uint8_t id, uint16_t reason,
                            void *data, int data_len);
int ble_l2cap_sig_reject_invalid_cid_tx(uint16_t conn_handle, uint8_t id,
                                        uint16_t src_cid, uint16_t dst_cid);
int ble_l2cap_sig_tx(uint16_t conn_handle, struct os_mbuf *txom);
void *ble_l2cap_sig_cmd_get(uint8_t opcode, uint8_t id, uint16_t len,
                            struct os_mbuf **txom);
#if MYNEWT_VAL(BLE_L2CAP_COC_MAX_NUM) != 0
int ble_l2cap_sig_coc_connect(uint16_t conn_handle, uint16_t psm, uint16_t mtu,
                              struct os_mbuf *sdu_rx,
                              ble_l2cap_event_fn *cb, void *cb_arg);
int ble_l2cap_sig_disconnect(struct ble_l2cap_chan *chan);
int ble_l2cap_sig_le_credits(uint16_t conn_handle, uint16_t scid,
                             uint16_t credits);
#else
static inline int
ble_l2cap_sig_coc_connect(uint16_t conn_handle, uint16_t psm, uint16_t mtu,
                          struct os_mbuf *sdu_rx,
                          ble_l2cap_event_fn *cb, void *cb_arg)
{
    return BLE_HS_ENOTSUP;
}

static inline int
ble_l2cap_sig_disconnect(struct ble_l2cap_chan *chan)
{
    return BLE_HS_ENOTSUP;
}
#endif

#if MYNEWT_VAL(BLE_L2CAP_ENHANCED_COC)
int ble_l2cap_sig_ecoc_connect(uint16_t conn_handle,
                                       uint16_t psm, uint16_t mtu,
                                       uint8_t num, struct os_mbuf *sdu_rx[],
                                       ble_l2cap_event_fn *cb, void *cb_arg);
int ble_l2cap_sig_coc_reconfig(uint16_t conn_handle, struct ble_l2cap_chan *chans[],
                               uint8_t num, uint16_t new_mtu);
#else
static inline int
ble_l2cap_sig_ecoc_connect(uint16_t conn_handle,
                           uint16_t psm, uint16_t mtu,
                           uint8_t num, struct os_mbuf *sdu_rx[],
                           ble_l2cap_event_fn *cb, void *cb_arg)
{
    return BLE_HS_ENOTSUP;
}
static inline int
ble_l2cap_sig_coc_reconfig(uint16_t conn_handle, struct ble_l2cap_chan *chans[],
                           uint8_t num, uint16_t new_mtu)
{
    return BLE_HS_ENOTSUP;
}
#endif

void ble_l2cap_sig_conn_broken(uint16_t conn_handle, int reason);
int32_t ble_l2cap_sig_timer(void);
struct ble_l2cap_chan *ble_l2cap_sig_create_chan(uint16_t conn_handle);
int ble_l2cap_sig_init(void);

#ifdef __cplusplus
}
#endif

#endif

