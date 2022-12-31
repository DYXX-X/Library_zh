/*
 * 根据一个或多个贡献者许可协议向Apache Software Foundation（ASF）许可。有关版权所有权的更多信息，请参阅随本作品分发的通知文件。ASF根据Apache许可证2.0版（“许可证”）向您许可此文件；除非符合许可证，否则不得使用此文件。您可以在以下地址获取许可证副本：
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 * 除非适用法律要求或书面同意，否则根据许可证分发的软件是按“原样”分发的，无任何明示或暗示的担保或条件。有关许可证下权限和限制的具体语言，请参阅许可证。
 */

#ifndef H_BLE_SM_
#define H_BLE_SM_

#include <inttypes.h>
#include "syscfg/syscfg.h"

#ifdef __cplusplus
extern "C" {
#endif

#define BLE_SM_ERR_PASSKEY                      0x01
#define BLE_SM_ERR_OOB                          0x02
#define BLE_SM_ERR_AUTHREQ                      0x03
#define BLE_SM_ERR_CONFIRM_MISMATCH             0x04
#define BLE_SM_ERR_PAIR_NOT_SUPP                0x05
#define BLE_SM_ERR_ENC_KEY_SZ                   0x06
#define BLE_SM_ERR_CMD_NOT_SUPP                 0x07
#define BLE_SM_ERR_UNSPECIFIED                  0x08
#define BLE_SM_ERR_REPEATED                     0x09
#define BLE_SM_ERR_INVAL                        0x0a
#define BLE_SM_ERR_DHKEY                        0x0b
#define BLE_SM_ERR_NUMCMP                       0x0c
#define BLE_SM_ERR_ALREADY                      0x0d
#define BLE_SM_ERR_CROSS_TRANS                  0x0e
#define BLE_SM_ERR_MAX_PLUS_1                   0x0f

#define BLE_SM_PAIR_ALG_JW                      0
#define BLE_SM_PAIR_ALG_PASSKEY                 1
#define BLE_SM_PAIR_ALG_OOB                     2
#define BLE_SM_PAIR_ALG_NUMCMP                  3

#define BLE_SM_PAIR_KEY_DIST_ENC                0x01
#define BLE_SM_PAIR_KEY_DIST_ID                 0x02
#define BLE_SM_PAIR_KEY_DIST_SIGN               0x04
#define BLE_SM_PAIR_KEY_DIST_LINK               0x08
#define BLE_SM_PAIR_KEY_DIST_RESERVED           0xf0

#define BLE_SM_IO_CAP_DISP_ONLY                 0x00
#define BLE_SM_IO_CAP_DISP_YES_NO               0x01
#define BLE_SM_IO_CAP_KEYBOARD_ONLY             0x02
#define BLE_SM_IO_CAP_NO_IO                     0x03
#define BLE_SM_IO_CAP_KEYBOARD_DISP             0x04
#define BLE_SM_IO_CAP_RESERVED                  0x05

#define BLE_SM_PAIR_OOB_NO                      0x00
#define BLE_SM_PAIR_OOB_YES                     0x01
#define BLE_SM_PAIR_OOB_RESERVED                0x02

#define BLE_SM_PAIR_AUTHREQ_BOND                0x01
#define BLE_SM_PAIR_AUTHREQ_MITM                0x04
#define BLE_SM_PAIR_AUTHREQ_SC                  0x08
#define BLE_SM_PAIR_AUTHREQ_KEYPRESS            0x10
#define BLE_SM_PAIR_AUTHREQ_RESERVED            0xe2

#define BLE_SM_PAIR_KEY_SZ_MIN                  7
#define BLE_SM_PAIR_KEY_SZ_MAX                  16

/*
 * 安全管理器要求应用程序执行密钥生成操作。应用程序通过ble_SM_inject_io（）将密钥传递回SM。
 */
#define BLE_SM_IOACT_NONE                       0
#define BLE_SM_IOACT_OOB                        1
#define BLE_SM_IOACT_INPUT                      2
#define BLE_SM_IOACT_DISP                       3
#define BLE_SM_IOACT_NUMCMP                     4
#define BLE_SM_IOACT_OOB_SC                     5
#define BLE_SM_IOACT_MAX_PLUS_ONE               6

struct ble_sm_sc_oob_data {
    /**随机数。*/
    uint8_t r[16];

    /**确认值。*/
    uint8_t c[16];
};

struct ble_sm_io {
    uint8_t action;
    union {
        uint32_t passkey;
        uint8_t  oob[16];
        uint8_t  numcmp_accept;
        struct {
            struct ble_sm_sc_oob_data *local;
            struct ble_sm_sc_oob_data *remote;
        } oob_sc_data;
    };
};

int ble_sm_sc_oob_generate_data(struct ble_sm_sc_oob_data *oob_data);

#if NIMBLE_BLE_SM
int ble_sm_inject_io(uint16_t conn_handle, struct ble_sm_io *pkey);
#else
#define ble_sm_inject_io(conn_handle, pkey) \
    ((void)(conn_handle), BLE_HS_ENOTSUP)
#endif

#ifdef __cplusplus
}
#endif

#endif

