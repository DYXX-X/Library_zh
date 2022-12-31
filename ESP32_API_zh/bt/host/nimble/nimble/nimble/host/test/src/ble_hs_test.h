/*
 * 根据一个或多个贡献者许可协议向Apache Software Foundation（ASF）许可。有关版权所有权的更多信息，请参阅随本作品分发的通知文件。ASF根据Apache许可证2.0版（“许可证”）向您许可此文件；除非符合许可证，否则不得使用此文件。您可以在以下地址获取许可证副本：
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 * 除非适用法律要求或书面同意，否则根据许可证分发的软件是按“原样”分发的，无任何明示或暗示的担保或条件。有关许可证下权限和限制的具体语言，请参阅许可证。
 */

#ifndef H_BLE_HS_TEST_
#define H_BLE_HS_TEST_

#include "testutil/testutil.h"

TEST_SUITE_DECL(ble_att_clt_suite);
TEST_SUITE_DECL(ble_att_svr_suite);
TEST_SUITE_DECL(ble_gap_test_suite_adv);
TEST_SUITE_DECL(ble_gap_test_suite_conn_cancel);
TEST_SUITE_DECL(ble_gap_test_suite_conn_find);
TEST_SUITE_DECL(ble_gap_test_suite_conn_gen);
TEST_SUITE_DECL(ble_gap_test_suite_conn_terminate);
TEST_SUITE_DECL(ble_gap_test_suite_disc);
TEST_SUITE_DECL(ble_gap_test_suite_mtu);
TEST_SUITE_DECL(ble_gap_test_suite_set_cb);
TEST_SUITE_DECL(ble_gap_test_suite_stop_adv);
TEST_SUITE_DECL(ble_gap_test_suite_timeout);
TEST_SUITE_DECL(ble_gap_test_suite_update_conn);
TEST_SUITE_DECL(ble_gap_test_suite_wl);
TEST_SUITE_DECL(ble_gatt_conn_suite);
TEST_SUITE_DECL(ble_gatt_disc_c_test_suite);
TEST_SUITE_DECL(ble_gatt_disc_d_test_suite);
TEST_SUITE_DECL(ble_gatt_disc_s_test_suite);
TEST_SUITE_DECL(ble_gatt_find_s_test_suite);
TEST_SUITE_DECL(ble_gatt_read_test_suite);
TEST_SUITE_DECL(ble_gatt_write_test_suite);
TEST_SUITE_DECL(ble_gatts_notify_suite);
TEST_SUITE_DECL(ble_gatts_read_test_suite);
TEST_SUITE_DECL(ble_gatts_reg_suite);
TEST_SUITE_DECL(ble_hs_adv_test_suite);
TEST_SUITE_DECL(ble_hs_conn_suite);
TEST_SUITE_DECL(ble_hs_hci_suite);
TEST_SUITE_DECL(ble_hs_id_test_suite_auto);
TEST_SUITE_DECL(ble_hs_pvcy_test_suite_irk);
TEST_SUITE_DECL(ble_l2cap_test_suite);
TEST_SUITE_DECL(ble_os_test_suite);
TEST_SUITE_DECL(ble_sm_gen_test_suite);
TEST_SUITE_DECL(ble_sm_lgcy_test_suite);
TEST_SUITE_DECL(ble_sm_sc_test_suite);
TEST_SUITE_DECL(ble_store_suite);
TEST_SUITE_DECL(ble_uuid_test_suite);

#endif

