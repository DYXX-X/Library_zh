/*
 * 根据一个或多个贡献者许可协议向Apache Software Foundation（ASF）许可。有关版权所有权的更多信息，请参阅随本作品分发的通知文件。ASF根据Apache许可证2.0版（“许可证”）向您许可此文件；除非符合许可证，否则不得使用此文件。您可以在以下地址获取许可证副本：
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 * 除非适用法律要求或书面同意，否则根据许可证分发的软件是按“原样”分发的，无任何明示或暗示的担保或条件。有关许可证下权限和限制的具体语言，请参阅许可证。
 */

#ifndef H_BLE_LL_TEST_PRIV_
#define H_BLE_LL_TEST_PRIV_

#include <stdint.h>
#include <stdbool.h>
#include "nimble/ble.h"

int ble_ll_hci_dtm_tx_test(const uint8_t *cmdbuf, uint8_t len);
int ble_ll_hci_dtm_tx_test_v2(const uint8_t *cmdbuf, uint8_t len);

int ble_ll_hci_dtm_rx_test(const uint8_t *cmdbuf, uint8_t len);
int ble_ll_hci_dtm_rx_test_v2(const uint8_t *cmdbuf, uint8_t len);

int ble_ll_dtm_end_test(uint8_t *rsp, uint8_t *rsplen);

int ble_ll_dtm_rx_isr_start(struct ble_mbuf_hdr *rxhdr, uint32_t aa);
int ble_ll_dtm_rx_isr_end(uint8_t *rxbuf, struct ble_mbuf_hdr *rxhdr);
void ble_ll_dtm_rx_pkt_in(struct os_mbuf *rxpdu, struct ble_mbuf_hdr *hdr);
void ble_ll_dtm_wfr_timer_exp(void);
void ble_ll_dtm_reset(void);
#endif

