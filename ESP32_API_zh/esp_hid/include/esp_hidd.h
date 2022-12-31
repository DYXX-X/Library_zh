// 版权所有2017-2019 Espressif Systems（上海）私人有限公司
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

#include "sdkconfig.h"
#include "esp_err.h"
#include "esp_event.h"
#include "esp_hid_common.h"

#ifdef __cplusplus
extern "C" {
#endif

#include "esp_hidd_transport.h"

ESP_EVENT_DECLARE_BASE(ESP_HIDD_EVENTS);        // 声明HID设备的事件库

/**
 * @brief HIDD回调事件枚举
 */
typedef enum {
    ESP_HIDD_ANY_EVENT = ESP_EVENT_ANY_ID,      /*!< HID设备任何事件*/
    ESP_HIDD_START_EVENT = 0,                   /*!< HID设备堆栈已启动*/
    ESP_HIDD_CONNECT_EVENT,                     /*!< HID设备已连接*/
    ESP_HIDD_PROTOCOL_MODE_EVENT,               /*!< HID设备协议模式更改*/
    ESP_HIDD_CONTROL_EVENT,                     /*!< HID设备控制请求*/
    ESP_HIDD_OUTPUT_EVENT,                      /*!< HID设备输出报告事件*/
    ESP_HIDD_FEATURE_EVENT,                     /*!< HID设备功能报告事件*/
    ESP_HIDD_DISCONNECT_EVENT,                  /*!< HID设备已断开连接*/
    ESP_HIDD_STOP_EVENT,                        /*!< HID设备堆栈已停止*/
    ESP_HIDD_MAX_EVENT,                         /*!< HID事件结束标记*/
} esp_hidd_event_t;

/**
 * @brief HIDD结构前向声明
 */
struct esp_hidd_dev_s;
typedef struct esp_hidd_dev_s esp_hidd_dev_t;

/**
 * @brief HIDD回调参数联合
 */
typedef union {
    /**
     * @brief ESP_HIDD_START_EVENT
     * @note 仅用于经典蓝牙。
     */
    struct {
        esp_err_t status;                       /*!< HID设备操作状态*/
    } start;                                    /*!< ESP_HIDD_START_EVENT的HID回调参数*/

    /**
     * @brief ESP_HIDD_STOP_EVENT
     * @note 仅用于经典蓝牙。
     */
    struct {
        esp_err_t status;                       /*!< HID设备操作状态*/
    } stop;                                     /*!< ESP_HIDD_STOP_EVENT的HID回调参数*/

    /**
     * @brief ESP_HIDD_CONNECT_EVENT
     */
    struct {
        esp_hidd_dev_t *dev;                    /*!< HID设备结构*/
        esp_err_t status;                       /*!< HID设备操作状态，仅用于经典蓝牙*/
    } connect;                                  /*!< ESP_HIDD_CONNECT_EVENT的HID回调参数*/

    /**
     * @brief ESP_HIDD_DISCONNECT_EVENT
     */
    struct {
        esp_hidd_dev_t *dev;                    /*!< HID设备结构*/
        int reason;                             /*!< 说明断开的原因*/
        esp_err_t status;                       /*!< HID设备操作状态，仅用于经典蓝牙*/
    } disconnect;                               /*!< ESP_HIDD_DISCONNECT_EVENT的HID回调参数*/

    /**
     * @brief ESP_HIDD_OUTPUT_EVENT
     */
    struct {
        esp_hidd_dev_t *dev;                    /*!< HID设备结构*/
        esp_hid_usage_t usage;                  /*!< HID报告使用情况*/
        uint16_t report_id;                     /*!< HID报告索引*/
        uint16_t length;                        /*!< 数据长度*/
        uint8_t  *data;                         /*!< 指向数据的指针*/
        uint8_t map_index;                      /*!< HID配置报告映射索引*/
    } output;                                   /*!< ESP_HIDD_OUTPUT_EVENT的HID回调参数*/

    /**
     * @brief ESP_HIDD_FEATURE_EVENT
     */
    struct {
        esp_hidd_dev_t *dev;                    /*!< HID设备结构*/
        esp_hid_usage_t usage;                  /*!< HID报告使用情况*/
        uint16_t report_id;                     /*!< HID报告索引*/
        uint16_t length;                        /*!< 数据长度*/
        uint8_t  *data;                         /*!< 指向数据的指针*/
        uint8_t map_index;                      /*!< HID配置报告映射索引*/
        uint8_t trans_type;                     /*!< HID设备功能事务类型，仅用于经典蓝牙*/
        uint8_t report_type;                    /*!< HID设备功能报告类型，仅用于经典蓝牙*/
    } feature;                                  /*!< ESP_HIDD_FEATURE_EVENT的HID回调参数*/

    /**
     * @brief ESP_HIDD_PROTOCOL_MODE_EVENT
     */
    struct {
        esp_hidd_dev_t *dev;                    /*!< HID设备结构*/
        uint8_t protocol_mode;                  /*!< HID协议模式*/
        uint8_t map_index;                      /*!< HID配置报告映射索引*/
    } protocol_mode;                            /*!< ESP_HIDD_PROTOCOL_MODE_EVENT的HID回调参数*/

    /**
     * @brief ESP_HIDD_CONTROL_EVENT
     */
    struct {
        esp_hidd_dev_t *dev;                    /*!< HID设备结构*/
        uint8_t control;                        /*!< HID控制点*/
        uint8_t map_index;                      /*!< HID配置报告映射索引*/
    } control;                                  /*!< ESP_HIDD_CONTROL_EVENT的HID回调参数*/

} esp_hidd_event_data_t;

/**
 * @brief 初始化HID设备
 * @param       config   ：设备的配置
 * @param       transport: 设备将使用的协议（ESP_HID_TRANSPORT_BLE/BT/USB）
 * @param       callback ：生成此设备的事件时调用的函数。可以为NULL，但将错过START事件。
 * @param[out]  dev      ：返回指向设备结构指针的位置
 *
 * @return: 成功时ESP_OK
 */
esp_err_t esp_hidd_dev_init(const esp_hid_device_config_t *config, esp_hid_transport_t transport, esp_event_handler_t callback, esp_hidd_dev_t **dev);

/**
 * @brief Deinit HID设备
 * @param dev ：指向要卸载的设备的指针
 *
 * @return: 成功时ESP_OK
 */
esp_err_t esp_hidd_dev_deinit(esp_hidd_dev_t *dev);

/**
 * @brief 获取HID设备传输
 * @param dev ：指向HID设备的指针
 *
 * @return: 连接设备或ESP_HID_transport_MAX的传输
 */
esp_hid_transport_t esp_hidd_dev_transport_get(esp_hidd_dev_t *dev);

/**
 * @brief 检查HID设备是否已连接
 * @param dev ：指向设备的指针
 *
 * @return: 如果设备已连接，则为true
 */
bool esp_hidd_dev_connected(esp_hidd_dev_t *dev);

/**
 * @brief 设置HID设备报告的电池电量
 * @param dev   ：指向设备的指针
 * @param level ：电池电量（0-100）
 *
 * @return: 成功时ESP_OK
 */
esp_err_t esp_hidd_dev_battery_set(esp_hidd_dev_t *dev, uint8_t level);

/**
 * @brief 向主机发送INPUT报告
 * @param dev       ：指向设备的指针
 * @param map_index ：init config中设备报告映射的索引
 * @param report_id ：HID INPUT报告的id
 * @param data      ：指向要发送的数据的指针
 * @param length    ：要发送的数据长度
 *
 * @return: 成功时ESP_OK
 */
esp_err_t esp_hidd_dev_input_set(esp_hidd_dev_t *dev, size_t map_index, size_t report_id, uint8_t *data, size_t length);

/**
 * @brief 向主机发送FEATURE报告
 * @param dev       ：指向设备的指针
 * @param map_index ：init config中设备报告映射的索引
 * @param report_id ：HID FEATURE报告的id
 * @param data      ：指向要发送的数据的指针
 * @param length    ：要发送的数据长度
 *
 * @return: 成功时ESP_OK
 */
esp_err_t esp_hidd_dev_feature_set(esp_hidd_dev_t *dev, size_t map_index, size_t report_id, uint8_t *data, size_t length);

/**
 * @brief 注册函数以侦听设备事件
 * @param dev       ：指向设备的指针
 * @param callback  ：事件处理程序函数
 * @param event     ：要侦听的事件（ESP_HIDD_ANY_event适用于所有事件）
 *
 * @return: 成功时ESP_OK
 */
esp_err_t esp_hidd_dev_event_handler_register(esp_hidd_dev_t *dev, esp_event_handler_t callback, esp_hidd_event_t event);

/**
 * @brief 注销正在侦听设备事件的函数
 * @param dev       ：指向设备的指针
 * @param callback  ：事件处理程序函数
 * @param event     ：正在侦听的事件（ESP_HIDD_ANY_event适用于所有事件）
 *
 * @return: 成功时ESP_OK
 */
esp_err_t esp_hidd_dev_event_handler_unregister(esp_hidd_dev_t *dev, esp_event_handler_t callback, esp_hidd_event_t event);

#ifdef __cplusplus
}
#endif

