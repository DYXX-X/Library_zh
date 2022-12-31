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

#ifndef _ESP_HIDH_PRIVATE_H_
#define _ESP_HIDH_PRIVATE_H_

#include "esp_hidh.h"
#if CONFIG_BLUEDROID_ENABLED
#include "esp_gap_bt_api.h"
#endif /* CONFIG_BLUEDROID_ENABLED */
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "esp_event.h"
#include "sys/queue.h"
#include "esp_timer.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief HIDH设备报告数据
 */
typedef struct esp_hidh_dev_report_s {
    struct esp_hidh_dev_report_s *next;
    uint8_t map_index;      //报表映射的索引
    uint8_t report_id;      //报告的id
    uint8_t report_type;    //输入、输出或特征
    uint8_t protocol_mode;  //引导或报告
    size_t value_len;       //报表映射的最大值长度
    esp_hid_usage_t usage;  //通用，键盘或鼠标
    //BLE属性
    uint16_t handle;        //值的句柄
    uint16_t ccc_handle;    //客户端配置句柄
    uint8_t permissions;    //报表权限
} esp_hidh_dev_report_t;

/**
 * @brief HIDH设备数据
 */
struct esp_hidh_dev_s {
    struct esp_hidh_dev_s   *next;

    esp_hid_device_config_t config;
    esp_hid_usage_t         usage;
    esp_hid_transport_t     transport;      //BT、BLE或USB
    esp_hid_trans_type_t    trans_type;     //指示正在进行的事务，新的事务只允许在上一个事务完成后进行
    esp_timer_handle_t      trans_timer;    //事务计时器
    uint8_t                 report_type;    //获取报告传输报告类型
    uint8_t                 report_id;      //获取报告传输报告_id
    uint8_t                 protocol_mode;  //设备协议模式
    bool                    connected;      //我们有所有需要的数据进行通信
    bool                    opened;         //我们手动打开设备，否则设备将连接到我们
    bool                    added;          //如果下层已添加设备
    bool                    is_orig;        //如果主机启动连接
    bool                    in_use;         //如果为false，将从设备列表中删除。
    int                     status;         //最后一个命令的状态

    size_t                  reports_len;
    esp_hidh_dev_report_t   *reports;

    void                    *tmp;
    size_t                  tmp_len;

    xSemaphoreHandle        semaphore;
    xSemaphoreHandle        mutex;

    esp_err_t               (*close)        (esp_hidh_dev_t *dev);
    esp_err_t               (*report_write) (esp_hidh_dev_t *dev, size_t map_index, size_t report_id, int report_type, uint8_t *data, size_t len);
    esp_err_t               (*report_read)  (esp_hidh_dev_t *dev, size_t map_index, size_t report_id, int report_type, size_t max_length, uint8_t *value, size_t *value_len);
    esp_err_t               (*set_report)   (esp_hidh_dev_t *dev, size_t map_index, size_t report_id, int report_type, uint8_t *data, size_t len);
    esp_err_t               (*get_idle)     (esp_hidh_dev_t *dev);
    esp_err_t               (*set_idle)     (esp_hidh_dev_t *dev, uint8_t idle_time);
    esp_err_t               (*get_protocol) (esp_hidh_dev_t *dev);
    esp_err_t               (*set_protocol) (esp_hidh_dev_t *dev, uint8_t protocol_mode);
    void                    (*dump)         (esp_hidh_dev_t *dev, FILE *fp);

#if CONFIG_BLUEDROID_ENABLED
    esp_bd_addr_t bda;
#endif /* CONFIG_BLUEDROID_ENABLED */

    union {
#if CONFIG_BT_HID_HOST_ENABLED
        struct {
            esp_bt_cod_t cod;
            uint8_t handle;
            // uint8_t子类；
            // uint8_t app_id；
            // uint16_t属性_掩码；
        } bt;
#endif /* CONFIG_BT_HID_HOST_ENABLED */
#if CONFIG_GATTC_ENABLE
        struct {
            esp_ble_addr_type_t address_type;
            int conn_id;
            uint16_t appearance;
            uint16_t battery_handle;
            uint16_t battery_ccc_handle;
        } ble;
#endif /* CONFIG_GATTC_ENABLE */
    };
    TAILQ_ENTRY(esp_hidh_dev_s) devices;
};

typedef TAILQ_HEAD(esp_hidh_dev_head_s, esp_hidh_dev_s) esp_hidh_dev_head_t;

esp_hidh_dev_t *esp_hidh_dev_malloc(void);

#if CONFIG_BLUEDROID_ENABLED
esp_hidh_dev_t *esp_hidh_dev_get_by_bda(esp_bd_addr_t bda); //BT/BLE
esp_hidh_dev_t *esp_hidh_dev_get_by_handle(uint8_t handle); //仅限经典蓝牙
esp_hidh_dev_t *esp_hidh_dev_get_by_conn_id(uint16_t conn_id); //仅BLE
#endif /* CONFIG_BLUEDROID_ENABLED */

esp_hidh_dev_report_t *esp_hidh_dev_get_report_by_id_type_proto(esp_hidh_dev_t *dev, size_t map_index, size_t report_id, int report_type, uint8_t protocol_mode);
esp_hidh_dev_report_t *esp_hidh_dev_get_report_by_id_and_type(esp_hidh_dev_t *dev, size_t map_index, size_t report_id, int report_type);
esp_hidh_dev_report_t *esp_hidh_dev_get_input_report_by_len_and_proto(esp_hidh_dev_t *dev, size_t len, int protocol_mode);
esp_hidh_dev_report_t *esp_hidh_dev_get_input_report_by_id_and_proto(esp_hidh_dev_t *dev, size_t report_id, int protocol_mode);
esp_hidh_dev_report_t *esp_hidh_dev_get_input_report_by_proto_and_data(esp_hidh_dev_t *dev, int protocol_mode,
                                                                       size_t len, const uint8_t *data, bool *has_report_id);
esp_hidh_dev_report_t *esp_hidh_dev_get_report_by_handle(esp_hidh_dev_t *dev, uint16_t handle);  //仅BLE
void esp_hidh_process_event_data_handler(void *event_handler_arg, esp_event_base_t event_base, int32_t event_id,
                                         void *event_data);
void esp_hidh_dev_lock(esp_hidh_dev_t *dev);
void esp_hidh_dev_unlock(esp_hidh_dev_t *dev);
void esp_hidh_dev_wait(esp_hidh_dev_t *dev);
void esp_hidh_dev_send(esp_hidh_dev_t *dev);
esp_err_t esp_hidh_dev_free_inner(esp_hidh_dev_t *dev);
#ifdef __cplusplus
}
#endif

#endif /* _ESP_HIDH_PRIVATE_H_ */

