/*
 * 根据一个或多个贡献者许可协议向Apache Software Foundation（ASF）许可。有关版权所有权的更多信息，请参阅随本作品分发的通知文件。ASF根据Apache许可证2.0版（“许可证”）向您许可此文件；除非符合许可证，否则不得使用此文件。您可以在以下地址获取许可证副本：
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 * 除非适用法律要求或书面同意，否则根据许可证分发的软件是按“原样”分发的，无任何明示或暗示的担保或条件。有关许可证下权限和限制的具体语言，请参阅许可证。
 */

#ifndef H_BLE_MONITOR_PRIV_
#define H_BLE_MONITOR_PRIV_

#ifdef __cplusplus
extern "C" {
#endif

#define BLE_MONITOR_OPCODE_NEW_INDEX    0
#define BLE_MONITOR_OPCODE_DEL_INDEX    1
#define BLE_MONITOR_OPCODE_COMMAND_PKT  2
#define BLE_MONITOR_OPCODE_EVENT_PKT    3
#define BLE_MONITOR_OPCODE_ACL_TX_PKT   4
#define BLE_MONITOR_OPCODE_ACL_RX_PKT   5
#define BLE_MONITOR_OPCODE_SCO_TX_PKT   6
#define BLE_MONITOR_OPCODE_SCO_RX_PKT   7
#define BLE_MONITOR_OPCODE_OPEN_INDEX   8
#define BLE_MONITOR_OPCODE_CLOSE_INDEX  9
#define BLE_MONITOR_OPCODE_INDEX_INFO   10
#define BLE_MONITOR_OPCODE_VENDOR_DIAG  11
#define BLE_MONITOR_OPCODE_SYSTEM_NOTE  12
#define BLE_MONITOR_OPCODE_USER_LOGGING 13

#define BLE_MONITOR_EXTHDR_COMMAND_DROPS    1
#define BLE_MONITOR_EXTHDR_EVENT_DROPS      2
#define BLE_MONITOR_EXTHDR_ACL_RX_DROPS     3
#define BLE_MONITOR_EXTHDR_ACL_TX_DROPS     4
#define BLE_MONITOR_EXTHDR_SCO_RX_DROPS     5
#define BLE_MONITOR_EXTHDR_SCO_TX_DROPS     6
#define BLE_MONITOR_EXTHDR_OTHER_DROPS      7
#define BLE_MONITOR_EXTHDR_TS32             8

struct ble_monitor_hdr {
    uint16_t  data_len;
    uint16_t  opcode;
    uint8_t   flags;
    uint8_t   hdr_len;
} __attribute__((packed));

struct ble_monitor_drops_hdr {
    uint8_t type_cmd;
    uint8_t cmd;
    uint8_t type_evt;
    uint8_t evt;
    uint8_t type_acl_tx;
    uint8_t acl_tx;
    uint8_t type_acl_rx;
    uint8_t acl_rx;
    uint8_t type_other;
    uint8_t other;
} __attribute__((packed));

struct ble_monitor_ts_hdr {
    uint8_t   type;
    uint32_t  ts32;
} __attribute__((packed));

struct ble_monitor_new_index {
    uint8_t  type;
    uint8_t  bus;
    uint8_t  bdaddr[6];
    char     name[8];
} __attribute__((packed));

struct ble_monitor_user_logging {
    uint8_t  priority;
    uint8_t  ident_len;
} __attribute__((packed));

int ble_monitor_init(void);

int ble_monitor_send(uint16_t opcode, const void *data, size_t len);

int ble_monitor_send_om(uint16_t opcode, const struct os_mbuf *om);

int ble_monitor_new_index(uint8_t bus, uint8_t *addr, const char *name);

#ifdef __cplusplus
}
#endif

#endif

