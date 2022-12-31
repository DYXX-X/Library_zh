/*
 * 根据一个或多个贡献者许可协议向Apache Software Foundation（ASF）许可。有关版权所有权的更多信息，请参阅随本作品分发的通知文件。ASF根据Apache许可证2.0版（“许可证”）向您许可此文件；除非符合许可证，否则不得使用此文件。您可以在以下地址获取许可证副本：
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 * 除非适用法律要求或书面同意，否则根据许可证分发的软件是按“原样”分发的，无任何明示或暗示的担保或条件。有关许可证下权限和限制的具体语言，请参阅许可证。
 */

#ifndef H_BLE_LL_SYNC_
#define H_BLE_LL_SYNC_

#include <stdint.h>

#include "nimble/ble.h"
#include "controller/ble_ll_hci.h"
#include "controller/ble_ll_conn.h"

#ifdef __cplusplus
extern "C" {
#endif

struct ble_ll_sync_sm;

int ble_ll_sync_create(const uint8_t *cmdbuf, uint8_t len);
int ble_ll_sync_cancel(ble_ll_hci_post_cmd_complete_cb *post_cmd_cb);
int ble_ll_sync_terminate(const uint8_t *cmdbuf, uint8_t len);
int ble_ll_sync_list_add(const uint8_t *cmdbuf, uint8_t len);
int ble_ll_sync_list_remove(const uint8_t *cmdbuf, uint8_t len);
int ble_ll_sync_list_clear(void);
int ble_ll_sync_list_size(uint8_t *rspbuf, uint8_t *rsplen);
int ble_ll_sync_receive_enable(const uint8_t *cmdbuf, uint8_t len);
int ble_ll_sync_transfer(const uint8_t *cmdbuf, uint8_t len,
                         uint8_t *rspbuf, uint8_t *rsplen);

void ble_ll_sync_periodic_ind(struct ble_ll_conn_sm *connsm,
                              const uint8_t *sync_ind, bool reports_disabled,
                              uint16_t max_skip, uint32_t sync_timeout);
void ble_ll_sync_transfer_disconnected(struct ble_ll_conn_sm *connsm);

void ble_ll_sync_info_event(const uint8_t *addr, uint8_t addr_type,
                            int rpa_index, uint8_t sid,
                            struct ble_mbuf_hdr *rxhdr,
                            const uint8_t *syncinfo);

int ble_ll_sync_rx_isr_start(uint8_t pdu_type, struct ble_mbuf_hdr *rxhdr);
int ble_ll_sync_rx_isr_end(uint8_t *rxbuf, struct ble_mbuf_hdr *rxhdr);
void ble_ll_sync_rx_pkt_in(struct os_mbuf *rxpdu, struct ble_mbuf_hdr *hdr);
void ble_ll_sync_wfr_timer_exp(void);
void ble_ll_sync_halt(void);
void ble_ll_sync_rmvd_from_sched(struct ble_ll_sync_sm *sm);

uint32_t ble_ll_sync_get_event_end_time(void);

bool ble_ll_sync_enabled(void);

void ble_ll_sync_reset(void);
void ble_ll_sync_init(void);

#ifdef __cplusplus
}
#endif

#endif /* H_BLE_LL_SYNC_ */

