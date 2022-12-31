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

#ifndef _HCI_PACKET_FACTORY_H_
#define _HCI_PACKET_FACTORY_H_

#include "stack/bt_types.h"
#include "device/event_mask.h"

typedef struct {
    BT_HDR *(*make_reset)(void);
    BT_HDR *(*make_read_buffer_size)(void);
    BT_HDR *(*make_set_c2h_flow_control)(uint8_t enable);
    BT_HDR *(*make_set_adv_report_flow_control)(uint8_t enable, uint16_t num, uint16_t lost_threshold);
    BT_HDR *(*make_host_buffer_size)(uint16_t acl_size, uint8_t sco_size, uint16_t acl_count, uint16_t sco_count);
    BT_HDR *(*make_read_local_version_info)(void);
    BT_HDR *(*make_read_bd_addr)(void);
    BT_HDR *(*make_read_local_supported_commands)(void);
    BT_HDR *(*make_read_local_supported_features)(void);
    BT_HDR *(*make_read_local_extended_features)(uint8_t page_number);
    BT_HDR *(*make_write_simple_pairing_mode)(uint8_t mode);
    BT_HDR *(*make_write_secure_connections_host_support)(uint8_t mode);
    BT_HDR *(*make_set_event_mask)(const bt_event_mask_t *event_mask);
    BT_HDR *(*make_ble_write_host_support)(uint8_t supported_host, uint8_t simultaneous_host);
    BT_HDR *(*make_ble_read_white_list_size)(void);
    BT_HDR *(*make_ble_read_buffer_size)(void);
    BT_HDR *(*make_ble_read_supported_states)(void);
    BT_HDR *(*make_ble_read_local_supported_features)(void);
    BT_HDR *(*make_ble_read_resolving_list_size)(void);
#if (BLE_50_FEATURE_SUPPORT == TRUE)
    BT_HDR *(*make_read_max_adv_data_len)(void);
#endif // #如果（BLE_50_FFEATURE_SUPPORT==真）
    BT_HDR *(*make_ble_read_suggested_default_data_length)(void);
    BT_HDR *(*make_ble_write_suggested_default_data_length)(uint16_t SuggestedMaxTxOctets, uint16_t SuggestedMaxTxTime);
    BT_HDR *(*make_ble_set_event_mask)(const bt_event_mask_t *event_mask);
    BT_HDR *(*make_write_sync_flow_control_enable)(uint8_t enable);
    BT_HDR *(*make_write_default_erroneous_data_report)(uint8_t enable);
} hci_packet_factory_t;

const hci_packet_factory_t *hci_packet_factory_get_interface(void);

#endif /*_HCI_PACKET_FACTORY_H_*/

