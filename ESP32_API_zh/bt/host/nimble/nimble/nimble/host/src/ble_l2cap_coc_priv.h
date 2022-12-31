/*
 * 根据一个或多个贡献者许可协议向Apache Software Foundation（ASF）许可。有关版权所有权的更多信息，请参阅随本作品分发的通知文件。ASF根据Apache许可证2.0版（“许可证”）向您许可此文件；除非符合许可证，否则不得使用此文件。您可以在以下地址获取许可证副本：
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 * 除非适用法律要求或书面同意，否则根据许可证分发的软件是按“原样”分发的，无任何明示或暗示的担保或条件。有关许可证下权限和限制的具体语言，请参阅许可证。
 */

#ifndef H_L2CAP_COC_PRIV_
#define H_L2CAP_COC_PRIV_

#include <inttypes.h>
#include "syscfg/syscfg.h"
#include "os/queue.h"
#include "os/os_mbuf.h"
#include "host/ble_l2cap.h"
#include "ble_l2cap_sig_priv.h"
#ifdef __cplusplus
extern "C" {
#endif

#define BLE_L2CAP_COC_CID_START                 0x0040
#define BLE_L2CAP_COC_CID_END                   0x007F

struct ble_l2cap_chan;

#define BLE_L2CAP_COC_FLAG_STALLED              0x01

struct ble_l2cap_coc_endpoint {
    struct os_mbuf *sdu;
    uint16_t mtu;
    uint16_t credits;
    uint16_t data_offset;
    uint8_t flags;
};

struct ble_l2cap_coc_srv {
    STAILQ_ENTRY(ble_l2cap_coc_srv) next;
    uint16_t psm;
    uint16_t mtu;
    ble_l2cap_event_fn *cb;
    void *cb_arg;
};

#if MYNEWT_VAL(BLE_L2CAP_COC_MAX_NUM) != 0
int ble_l2cap_coc_init(void);
int ble_l2cap_coc_create_server(uint16_t psm, uint16_t mtu,
                                ble_l2cap_event_fn *cb, void *cb_arg);
int ble_l2cap_coc_create_srv_chan(struct ble_hs_conn *conn, uint16_t psm,
                                  struct ble_l2cap_chan **chan);
struct ble_l2cap_chan * ble_l2cap_coc_chan_alloc(struct ble_hs_conn *conn,
                                                 uint16_t psm, uint16_t mtu,
                                                 struct os_mbuf *sdu_rx,
                                                 ble_l2cap_event_fn *cb,
                                                 void *cb_arg);
void ble_l2cap_coc_cleanup_chan(struct ble_hs_conn *conn, struct ble_l2cap_chan *chan);
void ble_l2cap_coc_le_credits_update(uint16_t conn_handle, uint16_t dcid,
                                    uint16_t credits);
int ble_l2cap_coc_recv_ready(struct ble_l2cap_chan *chan,
                             struct os_mbuf *sdu_rx);
int ble_l2cap_coc_send(struct ble_l2cap_chan *chan, struct os_mbuf *sdu_tx);
void ble_l2cap_coc_set_new_mtu_mps(struct ble_l2cap_chan *chan, uint16_t mtu, uint16_t mps);
#else
static inline int
ble_l2cap_coc_init(void) {
    return 0;
}

static inline int
ble_l2cap_coc_create_server(uint16_t psm, uint16_t mtu,
                            ble_l2cap_event_fn *cb, void *cb_arg) {
    return BLE_HS_ENOTSUP;
}

static inline int
ble_l2cap_coc_recv_ready(struct ble_l2cap_chan *chan,
                         struct os_mbuf *sdu_rx) {
    return BLE_HS_ENOTSUP;
}

static inline void
ble_l2cap_coc_cleanup_chan(struct ble_hs_conn *conn, struct ble_l2cap_chan *chan) {
}

static inline int
ble_l2cap_coc_send(struct ble_l2cap_chan *chan, struct os_mbuf *sdu_tx) {
    return BLE_HS_ENOTSUP;
}
#endif

#ifdef __cplusplus
}
#endif

#endif /* H_L2CAP_COC_PRIV_ */

