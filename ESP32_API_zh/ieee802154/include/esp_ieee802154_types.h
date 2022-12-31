// 版权所有2021 Espressif Systems（Shanghai）PTE LTD
//
// 根据Apache许可证2.0版（“许可证”）获得许可；
// 除非符合许可证，否则不得使用此文件。
// 您可以在以下地址获取许可证副本：

//     http://www.apache.org/licenses/LICENSE-2.0
//
// 除非适用法律要求或书面同意，软件
// 根据许可证分发的内容是按“原样”分发的，
// 无任何明示或暗示的保证或条件。
// 有关管理权限和
// 许可证下的限制。

#pragma once

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 无线电状态类型。
 */
typedef enum {
    ESP_IEEE802154_RADIO_DISABLE,   /*!< 收音机未启动*/
    ESP_IEEE802154_RADIO_SLEEP,     /*!< 收音机处于睡眠状态*/
    ESP_IEEE802154_RADIO_RECEIVE,   /*!< 收音机处于接收状态*/
    ESP_IEEE802154_RADIO_TRANSMIT,  /*!< 无线电处于发射状态*/
} esp_ieee802154_state_t;

/**
 * @brief 传输错误类型。
 */
typedef enum {
    ESP_IEEE802154_TX_ERR_NONE,         /*!< 无传输错误*/
    ESP_IEEE802154_TX_ERR_CCA_BUSY,     /*!< 频道正忙*/
    ESP_IEEE802154_TX_ERR_ABORT,        /*!< 传输中止*/
    ESP_IEEE802154_TX_ERR_NO_ACK,       /*!< 超时前未收到确认帧*/
    ESP_IEEE802154_TX_ERR_INVALID_ACK,  /*!< 无效的确认帧*/
    ESP_IEEE802154_TX_ERR_COEXIST,      /*!< 被共存系统拒绝*/
    ESP_IEEE802154_TX_ERR_COEXIST_REJ,  /*!< 传输帧前被共存系统拒绝*/
    ESP_IEEE802154_TX_ERR_COEXIST_ACK,  /*!< 接收ack时被共存系统拒绝*/
} esp_ieee802154_tx_error_t;

/**
 * @brief CCA模式类型。
 */
typedef enum {
    ESP_IEEE802154_CCA_MODE_CARRIER,         /*!< 仅限承运人*/
    ESP_IEEE802154_CCA_MODE_ED,              /*!< 仅能量检测*/
    ESP_IEEE802154_CCA_MODE_CARRIER_OR_ED,   /*!< 载波或能量检测*/
    ESP_IEEE802154_CCA_MODE_CARRIER_AND_ED,  /*!< 载波和能量检测*/
} esp_ieee802154_cca_mode_t;

/**
 * @brief 帧挂起模式类型。
 */
typedef enum {
    ESP_IEEE802154_AUTO_PENDING_DISABLE,   /*!< 在确认数据请求时，帧挂起位始终设置为1*/
    ESP_IEEE802154_AUTO_PENDING_ENABLE,    /*!< 如果src地址匹配，则在ack to Data Request中，帧挂起位设置为1*/
    ESP_IEEE802154_AUTO_PENDING_ENHANCED,  /*!< 在所有ack帧中，如果src地址匹配，则帧挂起位设置为1*/
    ESP_IEEE802154_AUTO_PENDING_ZIGBEE,    /*!< 只有当src地址是短地址并且与表中的数据请求一致时，才会将帧挂起位设置为0*/
} esp_ieee802154_pending_mode_t;

/**
 * @brief 收到15.4帧的信息。
 *
 */
typedef struct {
    bool pending;                /*!< 该帧已与帧挂起集打包*/
    uint8_t channel;             /*!< 频道*/
    int8_t rssi;                 /*!< RSSI */
    uint8_t lqi;                 /*!< LQI */
    uint64_t timestamp;          /*!< 接收帧的SFD字段时的时间戳*/
} esp_ieee802154_frame_info_t;

#ifdef __cplusplus
}
#endif

