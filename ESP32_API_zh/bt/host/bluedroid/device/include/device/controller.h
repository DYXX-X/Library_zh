/******************************************************************************
 * 版权所有（C）2014谷歌公司。
 *
 *  根据Apache许可证2.0版（“许可证”）获得许可；除非符合许可证，否则不得使用此文件。您可以在以下地址获取许可证副本：
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 *  除非适用法律要求或书面同意，否则根据许可证分发的软件是按“原样”分发的，无任何明示或暗示的担保或条件。有关许可证下权限和限制的具体语言，请参阅许可证。
 *
 ******************************************************************************/

#ifndef _CONTROLLER_H_
#define _CONTROLLER_H_

#include <stdbool.h>
#include <stdint.h>

#include "common/bt_target.h"
#include "device/bdaddr.h"
#include "device/device_features.h"
#include "hci/hci_layer.h"
#include "hci/hci_packet_factory.h"
#include "hci/hci_packet_parser.h"

typedef struct controller_t {
    void (*start_up)(void);
    void (*shut_down)(void);
    bool (*get_is_ready)(void);

    const bt_bdaddr_t *(*get_address)(void);
    const bt_version_t *(*get_bt_version)(void);

    const bt_device_features_t *(*get_features_classic)(int index);

    uint8_t (*get_last_features_classic_index)(void);

    const bt_device_features_t *(*get_features_ble)(void);
    const uint8_t *(*get_ble_supported_states)(void);

    bool (*supports_simple_pairing)(void);
    bool (*supports_secure_connections)(void);
    bool (*supports_simultaneous_le_bredr)(void);
    bool (*supports_reading_remote_extended_features)(void);
    bool (*supports_interlaced_inquiry_scan)(void);
    bool (*supports_rssi_with_inquiry_results)(void);
    bool (*supports_extended_inquiry_response)(void);
    bool (*supports_master_slave_role_switch)(void);

    bool (*supports_ble)(void);
    bool (*supports_ble_packet_extension)(void);
    bool (*supports_ble_connection_parameters_request)(void);
    bool (*supports_ble_privacy)(void);

    // 获取控制器的缓存acl数据大小。
    uint16_t (*get_acl_data_size_classic)(void);
    uint16_t (*get_acl_data_size_ble)(void);

    // 获取控制器的缓存acl数据包大小。
    // 这是各自的便利功能
    // acl数据大小+acl标头的大小。
    uint16_t (*get_acl_packet_size_classic)(void);
    uint16_t (*get_acl_packet_size_ble)(void);

    uint16_t (*get_ble_default_data_packet_length)(void);
    uint16_t (*get_ble_default_data_packet_txtime)(void);

    // 获取控制器可以缓冲的acl数据包的数量。
    uint16_t (*get_acl_buffer_count_classic)(void);
    uint8_t (*get_acl_buffer_count_ble)(void);

    uint8_t (*get_ble_white_list_size)(void);

    uint8_t (*get_ble_resolving_list_max_size)(void);
    void (*set_ble_resolving_list_max_size)(int resolving_list_max_size);

#if (BLE_50_FEATURE_SUPPORT == TRUE)
    uint16_t (*ble_get_ext_adv_data_max_len)(void);
#endif // BLE_50_FEATURE_SUPPORT

#if (BTM_SCO_HCI_INCLUDED == TRUE)
    // 获取控制器可以缓冲的sco数据包的数量
    uint8_t (*get_sco_data_size)(void);
    uint8_t (*get_sco_buffer_count)(void);
#endif /* #如果（BTM_SCO_HCI_INCLUDED==真）*/
} controller_t;

const controller_t *controller_get_interface(void);

#endif /*_CONTROLLER_H_*/

