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
#include "esp_log.h"
#include "esp_event.h"
#include "esp_hid_common.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief HIDH结构前向声明
 */
struct esp_hidh_dev_s;
typedef struct esp_hidh_dev_s esp_hidh_dev_t;

ESP_EVENT_DECLARE_BASE(ESP_HIDH_EVENTS);

/**
 * @brief HIDH回调事件枚举
 */
typedef enum {
    ESP_HIDH_ANY_EVENT = ESP_EVENT_ANY_ID,          /*!< HID设备任何事件*/
    ESP_HIDH_OPEN_EVENT = 0,                        /*!< HID设备已打开*/
    ESP_HIDH_BATTERY_EVENT,                         /*!< HID设备电池电量已更改*/
    ESP_HIDH_INPUT_EVENT,                           /*!< 收到HID设备INPUT报告*/
    ESP_HIDH_FEATURE_EVENT,                         /*!< 收到HID设备特征报告*/
    ESP_HIDH_CLOSE_EVENT,                           /*!< HID设备关闭*/
    ESP_HIDH_START_EVENT,                           /*!< HID主机堆栈已启动，仅用于经典蓝牙*/
    ESP_HIDH_STOP_EVENT,                            /*!< HID主机堆栈已停止，仅用于经典蓝牙*/
    ESP_HIDH_MAX_EVENT,                             /*!< HID事件结束标记*/
} esp_hidh_event_t;

/**
 * @brief HIDH回调参数联合
 */
typedef union {
    /**
     * @brief ESP_HIDH_START_EVENT
     * @note 仅用于经典蓝牙。
     */
    struct {
        esp_err_t status;                           /*!< HID主机操作状态*/
    } start;                                         /*!< ESP_HIDH_START_EVENT的HID回调参数*/

    /**
     * @brief ESP_HIDH_STOP_EVENT
     * @note 仅用于经典蓝牙。
     */
    struct {
        esp_err_t status;                           /*!< HID主机操作状态*/
    } stop;                                        /*!< ESP_HIDH_STOP_EVENT的HID回调参数*/

    /**
     * @brief ESP_HIDH_OPEN_EVENT
     */
    struct {
        esp_hidh_dev_t *dev;                        /*!< HID远程蓝牙设备*/
        esp_err_t status;                           /*!< HID主机操作状态，仅用于经典蓝牙*/
    } open;                                         /*!< ESP_HIDH_OPEN_EVENT的HID回调参数*/

    /**
     * @brief ESP_HIDH_CLOSE_EVENT
     */
    struct {
        esp_hidh_dev_t *dev;                        /*!< HID远程蓝牙设备。*/
        int reason;                                 /*!< 连接关闭的原因。仅BLE*/
        esp_err_t status;                           /*!< HID主机操作状态，仅用于经典蓝牙*/
    } close;                                        /*!< ESP_HIDH_CLOSE_EVENT的HID回调参数*/

    /**
     * @brief ESP_HIDH_BATTERY_EVENT
     */
    struct {
        esp_hidh_dev_t *dev;                        /*!< HID远程蓝牙设备*/
        uint8_t level;                              /*!< 电池电量（0-100%）*/
        esp_err_t status;                           /*!< HID主机操作状态*/
    } battery;                                      /*!< ESP_HIDH_BATTERY_EVENT的HID回调参数*/

    /**
     * @brief ESP_HIDH_INPUT_EVENT
     */
    struct {
        esp_hidh_dev_t *dev;                        /*!< HID远程蓝牙设备*/
        esp_hid_usage_t usage;                      /*!< HID报告使用情况*/
        uint16_t report_id;                         /*!< HID报告索引*/
        uint16_t length;                            /*!< HID数据长度*/
        uint8_t *data;                              /*!< 指向HID数据的指针*/
        uint8_t map_index;                          /*!< HID报告映射索引*/
    } input;                                        /*!< ESP_HIDH_INPUT_EVENT的HID回调参数*/

    /**
     * @brief ESP_HIDH_FEATURE_EVENT
     */
    struct {
        esp_hidh_dev_t *dev;                        /*!< HID远程蓝牙设备*/
        esp_hid_usage_t usage;                      /*!< HID报告使用情况*/
        uint16_t report_id;                         /*!< HID报告索引*/
        uint16_t length;                            /*!< HID数据长度*/
        uint8_t *data;                              /*!< 指向HID数据的指针*/
        uint8_t map_index;                          /*!< HID报告映射索引*/
        esp_err_t status;                           /*!< HID主机操作状态，仅用于经典蓝牙*/
        esp_hid_trans_type_t trans_type;            /*!< HID主机功能事务类型，仅用于经典蓝牙*/
    } feature;                                      /*!< ESP_HIDH_FEATURE_EVENT的HID回调参数*/

} esp_hidh_event_data_t;

typedef struct {
    esp_event_handler_t callback;
    uint16_t event_stack_size;
    void *callback_arg;
} esp_hidh_config_t;

/**
 * @brief 初始化HID主机组件
 * @param config           ：指向esp_hidh_config_t结构的指针
 *
 * @return: 成功时ESP_OK
 */
esp_err_t esp_hidh_init(const esp_hidh_config_t *config);

/**
 * @brief 取消初始化HID主机组件
 *
 * @return: 成功时ESP_OK
 */
esp_err_t esp_hidh_deinit(void);

/**
 * @brief 关闭HID设备
 * @param dev ：指向设备的指针
 *
 * @return: 成功时ESP_OK
 */
esp_err_t esp_hidh_dev_close(esp_hidh_dev_t *dev);

/**
 * @brief 释放HID设备内存在处理ESP_HIDH_CLOSE_EVENT时必须调用此函数。只有这样，用于设备的所有内存才会被释放。
 * @param dev ：指向设备的指针
 *
 * @return: 成功时ESP_OK
 */
esp_err_t esp_hidh_dev_free(esp_hidh_dev_t *dev);

/**
 * @brief 检查设备是否仍然存在。
 * @param dev ：指向设备的指针
 *
 * @return: 如果存在，则为true
 */
bool esp_hidh_dev_exists(esp_hidh_dev_t *dev);

/**
 * @brief 向设备发送OUTPUT报告
 * @param dev       ：指向设备的指针
 * @param map_index ：设备报告映射的索引
 * @param report_id ：HID OUTPUT报告的id
 * @param data      ：指向要发送的数据的指针
 * @param length    ：要发送的数据长度
 *
 * @return: 成功时ESP_OK
 */
esp_err_t esp_hidh_dev_output_set(esp_hidh_dev_t *dev, size_t map_index, size_t report_id, uint8_t *data, size_t length);

/**
 * @brief 向设备发送特征报告
 * @param dev       ：指向设备的指针
 * @param map_index ：设备报告映射的索引
 * @param report_id ：HID FEATURE报告的id
 * @param data      ：指向要发送的数据的指针
 * @param length    ：要发送的数据长度
 *
 * @return: 成功时ESP_OK
 */
esp_err_t esp_hidh_dev_feature_set(esp_hidh_dev_t *dev, size_t map_index, size_t report_id, uint8_t *data, size_t length);

/**
 * @brief 从设备获取FEATURE报告值
 * @param dev       ：指向设备的指针
 * @param map_index ：设备报告映射的索引
 * @param report_id ：HID FEATURE报告的id
 * @param max_len   ：将保存数据的缓冲区大小
 * @param data      ：指向数据缓冲区的指针
 * @param length    ：指向将设置为接收字节数的值的指针
 *
 * @return: 成功时ESP_OK
 */
esp_err_t esp_hidh_dev_feature_get(esp_hidh_dev_t *dev, size_t map_index, size_t report_id, size_t max_len, uint8_t *data, size_t *length);

/**
 * @brief Set_Report命令。
 * @note 目前，此功能仅用于经典蓝牙。
 *
 * @param dev           ：指向设备的指针
 * @param map_index     ：设备报告映射的索引
 * @param report_id     ：HID FEATURE报告的id
 * @param report_type   ：报告类型，在`esp_hid_common.h中定义`
 * @param data          ：指向要发送的数据的指针
 * @param length        ：要发送的数据长度
 *
 * @return: 成功时ESP_OK
 */
esp_err_t esp_hidh_dev_set_report(esp_hidh_dev_t *dev, size_t map_index, size_t report_id, int report_type,
                                  uint8_t *data, size_t length);

/**
 * @brief Get_Report命令。
 * @note 目前，此功能仅用于经典蓝牙。
 *
 * @param dev           ：指向设备的指针
 * @param map_index     ：设备报告映射的索引
 * @param report_id     ：HID FEATURE报告的id
 * @param report_type   ：报告类型，在`esp_hid_common.h中定义`
 * @param max_len       ：将保存数据的缓冲区大小
 *
 * @return: 成功时ESP_OK
 */
esp_err_t esp_hidh_dev_get_report(esp_hidh_dev_t *dev, size_t map_index, size_t report_id, int report_type,
                                  size_t max_len);

/**
 * @brief Get_Idle命令。
 * @note 目前，此功能仅用于经典蓝牙。
 *
 * @param dev               ：指向设备的指针
 *
 * @return: 成功时ESP_OK
 */
esp_err_t esp_hidh_dev_get_idle(esp_hidh_dev_t *dev);

/**
 * @brief Set_Idle命令。
 * @note 目前，此功能仅用于经典蓝牙。
 *
 * @param dev           ：指向设备的指针
 * @param idle_time     ：空闲时间
 *
 * @return: 成功时ESP_OK
 */
esp_err_t esp_hidh_dev_set_idle(esp_hidh_dev_t *dev, uint8_t idle_time);

/**
 * @brief Get_Protocol命令。
 * @note 目前，此功能仅用于经典蓝牙。
 *
 * @param dev               ：指向设备的指针
 *
 * @return: 成功时ESP_OK
 */
esp_err_t esp_hidh_dev_get_protocol(esp_hidh_dev_t *dev);

/**
 * @brief Set_Protocol命令。
 * @note 目前，此功能仅用于经典蓝牙。
 *
 * @param dev           ：指向设备的指针
 * @param protocol_mode ：协议模式（_M）
 *
 * @return: 成功时ESP_OK
 */
esp_err_t esp_hidh_dev_set_protocol(esp_hidh_dev_t *dev, uint8_t protocol_mode);

/**
 * @brief 将HID设备的属性转储到UART
 * @param dev ：指向HID设备的指针
 * @param fp  ：指向输出文件的指针
 */
void esp_hidh_dev_dump(esp_hidh_dev_t *dev, FILE *fp);

/**
 * @brief 获取HID设备的BT设备地址
 * @param dev ：指向HID设备的指针
 *
 * @return: 指向BDA字节数组或NULL的指针
 */
const uint8_t *esp_hidh_dev_bda_get(esp_hidh_dev_t *dev);

/**
 * @brief 获取HID设备传输
 * @param dev ：指向HID设备的指针
 *
 * @return: 连接设备或ESP_HID_transport_MAX的传输
 */
esp_hid_transport_t esp_hidh_dev_transport_get(esp_hidh_dev_t *dev);

/**
 * @brief 获取HID设备配置
 * @param dev ：指向HID设备的指针
 *
 * @return: 指向配置结构的指针或NULL
 */
const esp_hid_device_config_t *esp_hidh_dev_config_get(esp_hidh_dev_t *dev);

/**
 * @brief 获取HID设备的名称
 * @param dev ：指向HID设备的指针
 *
 * @return: 指向字符数组的指针或NULL
 */
const char *esp_hidh_dev_name_get(esp_hidh_dev_t *dev);

/**
 * @brief 获取HID设备的制造商
 * @param dev ：指向HID设备的指针
 *
 * @return: 指向字符数组的指针
 */
const char *esp_hidh_dev_manufacturer_get(esp_hidh_dev_t *dev);

/**
 * @brief 获取HID设备的序列号
 * @param dev ：指向HID设备的指针
 *
 * @return: 指向字符数组的指针或NULL
 */
const char *esp_hidh_dev_serial_get(esp_hidh_dev_t *dev);

/**
 * @brief 获取HID设备的VID
 * @param dev ：指向HID设备的指针
 *
 * @return: VID值
 */
uint16_t esp_hidh_dev_vendor_id_get(esp_hidh_dev_t *dev);

/**
 * @brief 获取HID设备的PID
 * @param dev ：指向HID设备的指针
 *
 * @return: PID值
 */
uint16_t esp_hidh_dev_product_id_get(esp_hidh_dev_t *dev);

/**
 * @brief 获取HID设备版本
 * @param dev ：指向HID设备的指针
 *
 * @return: 版本值
 */
uint16_t esp_hidh_dev_version_get(esp_hidh_dev_t *dev);

/**
 * @brief 获取BLE HID设备的外观
 * @param dev ：指向BLE HID设备的指针
 *
 * @return: 外观值
 */
uint16_t esp_hidh_dev_appearance_get(esp_hidh_dev_t *dev); //仅BLE

/**
 * @brief 获取计算的HID设备使用类型
 * @param dev ：指向HID设备的指针
 *
 * @return: hid使用类型
 */
esp_hid_usage_t esp_hidh_dev_usage_get(esp_hidh_dev_t *dev);

/**
 * @brief 获取设备上找到的所有报告的数组
 * @param dev           ：指向设备的指针
 * @param num_reports   ：指向将设置为报告数的值的指针
 * @param reports       ：设置到报表数组指针的位置
 *
 * @return: 成功时ESP_OK
 */
esp_err_t esp_hidh_dev_reports_get(esp_hidh_dev_t *dev, size_t *num_reports, esp_hid_report_item_t **reports);

/**
 * @brief 获取设备上找到的报告映射的数组
 * @param dev        ：指向设备的指针
 * @param num_maps   ：指向将设置为找到的报告映射数的值的指针
 * @param maps       ：设置到报表映射数组指针的位置
 *
 * @return: 成功时ESP_OK
 */
esp_err_t esp_hidh_dev_report_maps_get(esp_hidh_dev_t *dev, size_t *num_maps, esp_hid_raw_report_map_t **maps);

#include "esp_hidh_transport.h"

#ifdef __cplusplus
}
#endif

