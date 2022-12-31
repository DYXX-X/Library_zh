/*
 * 根据一个或多个贡献者许可协议向Apache Software Foundation（ASF）许可。有关版权所有权的更多信息，请参阅随本作品分发的通知文件。ASF根据Apache许可证2.0版（“许可证”）向您许可此文件；除非符合许可证，否则不得使用此文件。您可以在以下地址获取许可证副本：
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 * 除非适用法律要求或书面同意，否则根据许可证分发的软件是按“原样”分发的，无任何明示或暗示的担保或条件。有关许可证下权限和限制的具体语言，请参阅许可证。
 */

#ifndef H_BLE_SM_TEST_UTIL_
#define H_BLE_SM_TEST_UTIL_

#ifdef __cplusplus
extern "C" {
#endif

struct ble_sm_test_passkey_info {
    struct ble_sm_io passkey;
    uint32_t exp_numcmp;
    unsigned io_before_rx:1;
};

struct ble_sm_test_params {
    uint8_t init_addr_type;
    uint8_t init_id_addr[6];
    uint8_t init_rpa[6];
    uint8_t resp_addr_type;
    uint8_t resp_id_addr[6];
    uint8_t resp_rpa[6];
    struct ble_sm_test_passkey_info passkey_info;

    struct ble_sm_sec_req sec_req;
    struct ble_sm_pair_cmd pair_req;
    struct ble_sm_pair_cmd pair_rsp;
    struct ble_sm_pair_confirm confirm_req[20];
    struct ble_sm_pair_confirm confirm_rsp[20];
    struct ble_sm_pair_random random_req[20];
    struct ble_sm_pair_random random_rsp[20];
    struct ble_sm_id_info id_info_req;
    struct ble_sm_id_info id_info_rsp;
    struct ble_sm_id_addr_info id_addr_info_req;
    struct ble_sm_id_addr_info id_addr_info_rsp;
    struct ble_sm_sign_info sign_info_req;
    struct ble_sm_sign_info sign_info_rsp;
    struct ble_sm_pair_fail pair_fail;

    int pair_alg;
    unsigned authenticated:1;

    /***安全连接字段。*/
    uint8_t ltk[16];
    uint8_t our_priv_key[32];
    struct ble_sm_public_key public_key_req;
    struct ble_sm_public_key public_key_rsp;
    struct ble_sm_dhkey_check dhkey_check_req;
    struct ble_sm_dhkey_check dhkey_check_rsp;

    /***传统字段。*/
    uint8_t stk[16];
    struct ble_sm_enc_info enc_info_req;
    struct ble_sm_enc_info enc_info_rsp;
    struct ble_sm_master_id master_id_req;
    struct ble_sm_master_id master_id_rsp;
};

extern int ble_sm_test_gap_event;
extern int ble_sm_test_gap_status;
extern struct ble_gap_sec_state ble_sm_test_sec_state;

extern int ble_sm_test_store_obj_type;
extern union ble_store_key ble_sm_test_store_key;
extern union ble_store_value ble_sm_test_store_value;

void ble_sm_test_util_init(void);
int ble_sm_test_util_conn_cb(struct ble_gap_event *ctxt, void *arg);
void ble_sm_test_util_io_inject(struct ble_sm_test_passkey_info *passkey_info,
                                uint8_t cur_sm_state);
void ble_sm_test_util_io_inject_bad(uint16_t conn_handle,
                                    uint8_t correct_io_act);
void ble_sm_test_util_io_check_pre(
    struct ble_sm_test_passkey_info *passkey_info,
    uint8_t cur_sm_state);
void ble_sm_test_util_io_check_post(
    struct ble_sm_test_passkey_info *passkey_info,
    uint8_t cur_sm_state);
void ble_sm_test_util_rx_sec_req(uint16_t conn_handle,
                                 struct ble_sm_sec_req *cmd,
                                 int exp_status);
void ble_sm_test_util_verify_tx_pair_fail(struct ble_sm_pair_fail *exp_cmd);
void ble_sm_test_util_us_lgcy_good(struct ble_sm_test_params *params);
void ble_sm_test_util_peer_fail_inval(int we_are_master,
                                      uint8_t *init_addr,
                                      uint8_t *resp_addr,
                                      struct ble_sm_pair_cmd *pair_req,
                                      struct ble_sm_pair_fail *pair_fail);
void ble_sm_test_util_peer_lgcy_fail_confirm(
    uint8_t *init_addr,
    uint8_t *resp_addr,
    struct ble_sm_pair_cmd *pair_req,
    struct ble_sm_pair_cmd *pair_rsp,
    struct ble_sm_pair_confirm *confirm_req,
    struct ble_sm_pair_confirm *confirm_rsp,
    struct ble_sm_pair_random *random_req,
    struct ble_sm_pair_random *random_rsp,
    struct ble_sm_pair_fail *fail_rsp);

void ble_sm_test_util_peer_lgcy_good_once(struct ble_sm_test_params *params);
void ble_sm_test_util_peer_lgcy_good(struct ble_sm_test_params *params);
void ble_sm_test_util_peer_bonding_bad(uint16_t ediv, uint64_t rand_num);
void ble_sm_test_util_peer_sc_good(struct ble_sm_test_params *params);
void ble_sm_test_util_us_sc_good(struct ble_sm_test_params *params);
void ble_sm_test_util_us_sc_bad(struct ble_sm_test_params *params);
void ble_sm_test_util_us_fail_inval(struct ble_sm_test_params *params);

#ifdef __cplusplus
}
#endif

#endif

