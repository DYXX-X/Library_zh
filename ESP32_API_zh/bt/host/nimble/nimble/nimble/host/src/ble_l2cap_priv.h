/*
 * 根据一个或多个贡献者许可协议向Apache Software Foundation（ASF）许可。有关版权所有权的更多信息，请参阅随本作品分发的通知文件。ASF根据Apache许可证2.0版（“许可证”）向您许可此文件；除非符合许可证，否则不得使用此文件。您可以在以下地址获取许可证副本：
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 * 除非适用法律要求或书面同意，否则根据许可证分发的软件是按“原样”分发的，无任何明示或暗示的担保或条件。有关许可证下权限和限制的具体语言，请参阅许可证。
 */

#ifndef H_L2CAP_PRIV_
#define H_L2CAP_PRIV_

#include "ble_l2cap_coc_priv.h"
#include "host/ble_l2cap.h"
#include <inttypes.h>
#include "stats/stats.h"
#include "os/queue.h"
#include "os/os_mbuf.h"
#ifdef __cplusplus
extern "C" {
#endif

struct ble_hs_conn;
struct hci_data_hdr;

STATS_SECT_START(ble_l2cap_stats)
    STATS_SECT_ENTRY(chan_create)
    STATS_SECT_ENTRY(chan_delete)
    STATS_SECT_ENTRY(update_init)
    STATS_SECT_ENTRY(update_rx)
    STATS_SECT_ENTRY(update_fail)
    STATS_SECT_ENTRY(proc_timeout)
    STATS_SECT_ENTRY(sig_tx)
    STATS_SECT_ENTRY(sig_rx)
    STATS_SECT_ENTRY(sm_tx)
    STATS_SECT_ENTRY(sm_rx)
STATS_SECT_END
extern STATS_SECT_DECL(ble_l2cap_stats) ble_l2cap_stats;

extern struct os_mempool ble_l2cap_chan_pool;

/* 这是灵活具体的；发送到黑洞CID的数据包不会引发“无效CID”响应。
 */
#define BLE_L2CAP_CID_BLACK_HOLE    0xffff

#define BLE_L2CAP_HDR_SZ    4

typedef uint8_t ble_l2cap_chan_flags;

typedef int ble_l2cap_rx_fn(struct ble_l2cap_chan *chan);

struct ble_l2cap_chan {
    SLIST_ENTRY(ble_l2cap_chan) next;
    uint16_t conn_handle;
    uint16_t dcid;
    uint16_t scid;

    /* 工会只是为了避免MPS/MTU的混乱。在CoC上下文中，L2CAP MTU是MPS
     */
    union {
        uint16_t my_mtu;
        uint16_t my_coc_mps;
    };

    union {
        uint16_t peer_mtu;
        uint16_t peer_coc_mps;
    };

    ble_l2cap_chan_flags flags;

    struct os_mbuf *rx_buf;
    uint16_t rx_len;        /* 当前重新组装的rx数据包的长度。*/

    ble_l2cap_rx_fn *rx_fn;

#if MYNEWT_VAL(BLE_L2CAP_COC_MAX_NUM) != 0
    uint16_t psm;
    struct ble_l2cap_coc_endpoint coc_rx;
    struct ble_l2cap_coc_endpoint coc_tx;
    uint16_t initial_credits;
    ble_l2cap_event_fn *cb;
    void *cb_arg;
#endif
};

struct ble_l2cap_hdr {
    uint16_t len;
    uint16_t cid;
};

typedef int ble_l2cap_tx_fn(struct ble_hs_conn *conn,
                            struct ble_l2cap_chan *chan);

#define BLE_L2CAP_CHAN_F_TXED_MTU       0x01    /* 我们已经发送了MTU。*/

SLIST_HEAD(ble_l2cap_chan_list, ble_l2cap_chan);

int ble_l2cap_parse_hdr(struct os_mbuf *om, int off,
                        struct ble_l2cap_hdr *l2cap_hdr);
struct os_mbuf *ble_l2cap_prepend_hdr(struct os_mbuf *om, uint16_t cid,
                                      uint16_t len);

struct ble_l2cap_chan *ble_l2cap_chan_alloc(uint16_t conn_handle);
void ble_l2cap_chan_free(struct ble_hs_conn *conn, struct ble_l2cap_chan *chan);

bool ble_l2cap_is_mtu_req_sent(const struct ble_l2cap_chan *chan);

int ble_l2cap_rx(struct ble_hs_conn *conn,
                 struct hci_data_hdr *hci_hdr,
                 struct os_mbuf *om,
                 ble_l2cap_rx_fn **out_rx_cb,
                 int *out_reject_cid);
int ble_l2cap_tx(struct ble_hs_conn *conn, struct ble_l2cap_chan *chan,
                 struct os_mbuf *txom);

void ble_l2cap_remove_rx(struct ble_hs_conn *conn, struct ble_l2cap_chan *chan);

int ble_l2cap_init(void);

/* 当BLE_VERSION>=52时，以下实验API可用*/
int ble_l2cap_enhanced_connect(uint16_t conn_handle,
                               uint16_t psm, uint16_t mtu,
                               uint8_t num, struct os_mbuf *sdu_rx[],
                               ble_l2cap_event_fn *cb, void *cb_arg);
int ble_l2cap_reconfig(struct ble_l2cap_chan *chans[], uint8_t num, uint16_t new_mtu);

#ifdef __cplusplus
}
#endif

#endif

