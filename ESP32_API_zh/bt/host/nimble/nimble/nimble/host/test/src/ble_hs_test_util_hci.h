/*
 * 根据一个或多个贡献者许可协议向Apache Software Foundation（ASF）许可。有关版权所有权的更多信息，请参阅随本作品分发的通知文件。ASF根据Apache许可证2.0版（“许可证”）向您许可此文件；除非符合许可证，否则不得使用此文件。您可以在以下地址获取许可证副本：
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 * 除非适用法律要求或书面同意，否则根据许可证分发的软件是按“原样”分发的，无任何明示或暗示的担保或条件。有关许可证下权限和限制的具体语言，请参阅许可证。
 */

#ifndef H_BLE_HS_TEST_UTIL_HCI_
#define H_BLE_HS_TEST_UTIL_HCI_

#ifdef __cplusplus
extern "C" {
#endif

/* 将其保留为宏，以便可以用于静态常量初始化*/
#define ble_hs_hci_util_opcode_join(ogf, ocf) (((ogf) << 10) | (ocf))

#define BLE_HS_TEST_UTIL_PHONY_ACK_MAX  64
struct ble_hs_test_util_hci_ack {
    uint16_t opcode;
    uint8_t status;
    uint8_t evt_params[256];
    uint8_t evt_params_len;
};

struct ble_hs_test_util_hci_num_completed_pkts_entry {
    uint16_t handle_id; /* 0表示终止数组中的项。*/
    uint16_t num_pkts;
};

/* $out队列*/
void ble_hs_test_util_hci_out_adj(int count);
void *ble_hs_test_util_hci_out_first(void);
void *ble_hs_test_util_hci_out_last(void);
void ble_hs_test_util_hci_out_enqueue(void *cmd);
void ble_hs_test_util_hci_out_clear(void);
void ble_hs_test_util_hci_acks_clear(void);

/* $构建*/
void ble_hs_test_util_hci_build_cmd_complete(uint8_t *dst, int len,
                                             uint8_t param_len,
                                             uint8_t num_pkts,
                                             uint16_t opcode);
void ble_hs_test_util_hci_build_cmd_status(uint8_t *dst, int len,
                                           uint8_t status, uint8_t num_pkts,
                                           uint16_t opcode);

/* $确认*/
void ble_hs_test_util_hci_ack_set_params(uint16_t opcode, uint8_t status,
                                         void *params, uint8_t params_len);
void ble_hs_test_util_hci_ack_set(uint16_t opcode, uint8_t status);
void ble_hs_test_util_hci_ack_append_params(uint16_t opcode, uint8_t status,
                                            void *params, uint8_t params_len);
void ble_hs_test_util_hci_ack_append(uint16_t opcode, uint8_t status);
void ble_hs_test_util_hci_ack_set_seq(const struct ble_hs_test_util_hci_ack *acks);
void ble_hs_test_util_hci_ack_set_startup(void);
void ble_hs_test_util_hci_ack_set_disc(uint8_t own_addr_type,
                                       int fail_idx, uint8_t fail_status);
void ble_hs_test_util_hci_ack_set_disconnect(uint8_t hci_status);

int ble_hs_test_util_hci_startup_seq_cnt(void);

/* $verify发送*/
void ble_hs_test_util_hci_verify_tx_add_irk(uint8_t addr_type,
                                            const uint8_t *addr,
                                            const uint8_t *peer_irk,
                                            const uint8_t *local_irk);
void ble_hs_test_util_hci_verify_tx_set_priv_mode(uint8_t addr_type,
                                                  const uint8_t *addr,
                                                  uint8_t priv_mode);
void ble_hs_test_util_hci_verify_tx_disconnect(uint16_t handle,
                                               uint8_t reason);
void ble_hs_test_util_hci_verify_tx_create_conn(
    const struct hci_create_conn *exp);
uint8_t *ble_hs_test_util_hci_verify_tx(uint8_t ogf, uint16_t ocf,
                                        uint8_t *out_param_len);

/* $rx美元*/
void ble_hs_test_util_hci_rx_num_completed_pkts_event(
    struct ble_hs_test_util_hci_num_completed_pkts_entry *entries);
void ble_hs_test_util_hci_rx_disconn_complete_event(uint16_t conn_handle,
                                                    uint8_t status, uint8_t reason);
void ble_hs_test_util_hci_rx_conn_cancel_evt(void);

/* $杂项*/
int ble_hs_test_util_hci_misc_exp_status(int cmd_idx, int fail_idx,
                                         uint8_t fail_status);

#ifdef __cplusplus
}
#endif

#endif

