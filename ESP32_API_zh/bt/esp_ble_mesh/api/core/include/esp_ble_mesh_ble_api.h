/*
 * SPDX文件版权文本：2017-2021浓缩咖啡系统（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */

#ifndef _ESP_BLE_MESH_BLE_API_H_
#define _ESP_BLE_MESH_BLE_API_H_

#include "esp_ble_mesh_defs.h"

#ifdef __cplusplus
extern "C" {
#endif

/**此枚举值是BLE操作的事件*/
typedef enum {
    ESP_BLE_MESH_START_BLE_ADVERTISING_COMP_EVT, /*!< 启动BLE广告完成事件*/
    ESP_BLE_MESH_STOP_BLE_ADVERTISING_COMP_EVT,  /*!< 停止BLE广告完成事件*/
    ESP_BLE_MESH_START_BLE_SCANNING_COMP_EVT,    /*!< 启动BLE扫描完成事件*/
    ESP_BLE_MESH_STOP_BLE_SCANNING_COMP_EVT,     /*!< 停止BLE扫描完成事件*/
    ESP_BLE_MESH_SCAN_BLE_ADVERTISING_PKT_EVT,   /*!< 扫描BLE广告包事件*/
    ESP_BLE_MESH_BLE_EVT_MAX,
} esp_ble_mesh_ble_cb_event_t;

/**BLE操作回调参数*/
typedef union {
    /**
     * @brief ESP_BLE_MESH_START_BLE_ADVERTISING_COMP_EVT
     */
    struct {
        int err_code;             /*!< 指示启动BLE广告的结果*/
        uint8_t index;            /*!< BLE广告索引*/
    } start_ble_advertising_comp; /*!< ESP_BLE_MESH_START_BLE_ADVERTISING_COMP_EVT的事件参数*/
    /**
     * @brief ESP_BLE_MESH_STOP_BLE_ADVERTISING_COMP_EVT
     */
    struct {
        int err_code;            /*!< 指示停止BLE广告的结果*/
        uint8_t index;           /*!< BLE广告索引*/
    } stop_ble_advertising_comp; /*!< ESP_BLE_MESH_STOP_BLE_ADVERTISING_COMP_EVT的事件参数*/
    /**
     * @brief ESP_BLE_MESH_START_BLE_SCANNING_COMP_EVT
     */
    struct {
        int err_code;      /*!< 指示启动BLE扫描的结果*/
    } start_ble_scan_comp; /*!< ESP_BLE_MESH_START_BLE_SCANNING_COMP_EVT的事件参数*/
    /**
     * @brief ESP_BLE_MESH_STOP_BLE_SCANNING_COMP_EVT
     */
    struct {
        int err_code;     /*!< 指示停止BLE扫描的结果*/
    } stop_ble_scan_comp; /*!< ESP_BLE_MESH_STOP_BLE_SCANNING_COMP_EVT的事件参数*/
    /**
     * @brief ESP_BLE_MESH_SCAN_BLE_ADVERTISING_PKT_EVT
     */
    struct {
        uint8_t  addr[6];   /*!< 设备地址*/
        uint8_t  addr_type; /*!< 设备地址类型*/
        uint8_t  adv_type;  /*!< 广告数据类型*/
        uint8_t *data;      /*!< 广告数据*/
        uint16_t length;    /*!< 广告数据长度*/
        int8_t   rssi;      /*!< 广告包的RSSI*/
    } scan_ble_adv_pkt;     /*!< ESP_BLE_MESH_SCAN_BLE_ADVERTISING_PKT_EVT的事件参数*/
} esp_ble_mesh_ble_cb_param_t;

/**
 * @brief   BLE扫描回调函数类型
 *
 * @param   event: BLE扫描回调事件类型
 * @param   param: BLE扫描回调参数
 */
typedef void (* esp_ble_mesh_ble_cb_t)(esp_ble_mesh_ble_cb_event_t event,
                                       esp_ble_mesh_ble_cb_param_t *param);

/**
 * @brief       注册BLE扫描回调。
 *
 * @param[in]   callback: 指向BLE扫描回调函数的指针。
 *
 * @return      成功时返回ESP_OK，否则返回错误代码。
 *
 */
esp_err_t esp_ble_mesh_register_ble_callback(esp_ble_mesh_ble_cb_t callback);

/**无限发送BLE广告包计数*/
#define ESP_BLE_MESH_BLE_ADV_INFINITE   0xFFFF

/*!< 此枚举值是BLE广告包的优先级*/
typedef enum {
    ESP_BLE_MESH_BLE_ADV_PRIO_LOW,
    ESP_BLE_MESH_BLE_ADV_PRIO_HIGH,
} esp_ble_mesh_ble_adv_priority_t;

/**BLE广告参数的上下文。*/
typedef struct {
    uint16_t interval;               /*!< BLE广告间隔*/
    uint8_t  adv_type;               /*!< BLE广告类型*/
    uint8_t  own_addr_type;          /*!< 自己的地址类型*/
    uint8_t  peer_addr_type;         /*!< 对等地址类型*/
    uint8_t  peer_addr[BD_ADDR_LEN]; /*!< 对等地址*/
    uint16_t duration;               /*!< 持续时间为毫秒*/
    uint16_t period;                 /*!< 周期（毫秒）*/
    uint16_t count;                  /*!< 广告持续时间数*/
    uint8_t  priority:2;             /*!< BLE广告包的优先级*/
} esp_ble_mesh_ble_adv_param_t;

/**BLE广告数据的上下文。*/
typedef struct {
    uint8_t adv_data_len;      /*!< 广告数据长度*/
    uint8_t adv_data[31];      /*!< 广告数据*/
    uint8_t scan_rsp_data_len; /*!< 扫描响应数据长度*/
    uint8_t scan_rsp_data[31]; /*!< 扫描响应数据*/
} esp_ble_mesh_ble_adv_data_t;

/**
 * @brief         调用此函数以在BLE Mesh同时工作时使用相应的数据和参数启动BLE广告。
 *
 * @note          1.当调用此函数时，BLE广告包将被发布到网格堆栈中的BLE网格adv队列并等待发送。2.在BLE广告参数中，“持续时间”是指每次发送BLE广告包所用的时间，不得小于广告间隔。当数据包成功发送时，如果“计数”大于0，则它将在“周期”时间后再次发送到adv队列。“计数”表示数据包首次成功发送后将发送多长时间。如果“计数”设置为0xFFFF，这意味着数据包将无限发送。3.“优先级”是指BLE广告包与BLE Mesh包相比的优先级。目前提供了两个选项（即低/高）。如果“优先级”较高，BLE广告包将张贴在adv队列的前面。否则，它将被张贴到adv队列的后面。
 *
 * @param[in]     param: 指向BLE广告参数的指针
 * @param[in]     data:  指向BLE广告数据和扫描响应数据的指针
 *
 * @return        成功时返回ESP_OK，否则返回错误代码。
 *
 */
esp_err_t esp_ble_mesh_start_ble_advertising(const esp_ble_mesh_ble_adv_param_t *param,
                                             const esp_ble_mesh_ble_adv_data_t *data);

/**
 * @brief         调用此函数以停止具有相应索引的BLE广告。
 *
 * @param[in]     index: BLE广告索引
 *
 * @return        成功时返回ESP_OK，否则返回错误代码。
 *
 */
esp_err_t esp_ble_mesh_stop_ble_advertising(uint8_t index);

/**BLE扫描参数的上下文。*/
typedef struct {
    uint32_t duration; /*!< 用于扫描正常BLE广告包的持续时间*/
} esp_ble_mesh_ble_scan_param_t;

/**
 * @brief         调用此函数以开始扫描正常的BLE广告包，并将这些包通知给应用层。
 *
 * @param[in]     param: 指向BLE扫描参数的指针
 *
 * @return        成功时返回ESP_OK，否则返回错误代码。
 *
 */
esp_err_t esp_ble_mesh_start_ble_scanning(esp_ble_mesh_ble_scan_param_t *param);

/**
 * @brief         调用此函数以停止向应用层通知正常BLE广告包。
 *
 * @return        成功时返回ESP_OK，否则返回错误代码。
 *
 */
esp_err_t esp_ble_mesh_stop_ble_scanning(void);

#ifdef __cplusplus
}
#endif

#endif /* _ESP_BLE_MESH_BLE_API_H_ */

