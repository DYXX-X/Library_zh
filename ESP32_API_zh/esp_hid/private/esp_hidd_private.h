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

#include "esp_err.h"
#include "esp_hidd.h"
#include "esp_hid_common.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef union {
    struct {
        uint16_t notify_enable : 1;
        uint16_t indicate_enable : 1;
        uint16_t reserved : 14;
    };
    uint16_t value;
} hidd_le_ccc_value_t;

typedef struct {
    uint8_t map_index;     // 报表映射的索引
    uint8_t report_id;     // 报告的id
    uint8_t report_type;   // 输入、输出或特征
    uint8_t protocol_mode; // 引导或报告
    esp_hid_usage_t usage; // 通用、键盘、鼠标、游戏杆或游戏板
    uint16_t value_len;    // 报表映射的最大值长度
    // 由gatts使用
    uint8_t index;           // gatts属性数据库中的值索引
    uint16_t handle;         // 注册所有属性后获得
    uint16_t ccc_handle;     // 注册所有属性后获得
    hidd_le_ccc_value_t ccc; // 已启用通知和/或指示
} hidd_report_item_t;

struct esp_hidd_dev_s {
    void *dev;
    esp_hid_transport_t transport;

    bool        (*connected)                (void *dev);
    esp_err_t   (*deinit)                   (void *dev);
    esp_err_t   (*disconnect)               (void *dev);
    esp_err_t   (*virtual_unplug)           (void *dev);
    esp_err_t   (*battery_set)              (void *dev, uint8_t level);
    esp_err_t   (*input_set)                (void *dev, size_t map_index, size_t report_id, uint8_t *data, size_t length);
    esp_err_t   (*feature_set)              (void *dev, size_t map_index, size_t report_id, uint8_t *data, size_t length);
    esp_err_t   (*event_handler_register)   (void *dev, esp_event_handler_t callback, esp_hidd_event_t event);
    esp_err_t   (*event_handler_unregister) (void *dev, esp_event_handler_t callback, esp_hidd_event_t event);
};

typedef struct esp_hidd_dev_s esp_hidd_dev_t;

void esp_hidd_process_event_data_handler(void *event_handler_arg, esp_event_base_t event_base, int32_t event_id,
                                         void *event_data);

#ifdef __cplusplus
}
#endif

