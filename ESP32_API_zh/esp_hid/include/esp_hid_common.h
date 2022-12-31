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

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <stdio.h>

/* HID报告映射值*/
#define HID_RM_INPUT                        0x80
#define HID_RM_OUTPUT                       0x90
#define HID_RM_FEATURE                      0xb0
#define HID_RM_COLLECTION                   0xa0
#define HID_RM_END_COLLECTION               0xc0
#define HID_RM_USAGE_PAGE                   0x04
#define HID_RM_LOGICAL_MINIMUM              0x14
#define HID_RM_LOGICAL_MAXIMUM              0x24
#define HID_RM_PHYSICAL_MINIMUM             0x34
#define HID_RM_PHYSICAL_MAXIMUM             0x44
#define HID_RM_UNIT_EXPONENT                0x54
#define HID_RM_UNIT                         0x64
#define HID_RM_REPORT_SIZE                  0x74
#define HID_RM_REPORT_ID                    0x84
#define HID_RM_REPORT_COUNT                 0x94
#define HID_RM_PUSH                         0xa4
#define HID_RM_POP                          0xb4
#define HID_RM_USAGE                        0x08
#define HID_RM_USAGE_MINIMUM                0x18
#define HID_RM_USAGE_MAXIMUM                0x28
#define HID_RM_DESIGNATOR_INDEX             0x38
#define HID_RM_DESIGNATOR_MINIMUM           0x48
#define HID_RM_DESIGNATOR_MAXIMUM           0x58
#define HID_RM_STRING_INDEX                 0x78
#define HID_RM_STRING_MINIMUM               0x88
#define HID_RM_STRING_MAXIMUM               0x98
#define HID_RM_DELIMITER                    0xa8

/* HID使用页面和用法*/
#define HID_USAGE_PAGE_GENERIC_DESKTOP      0x01
#define HID_USAGE_KEYBOARD                  0x06
#define HID_USAGE_MOUSE                     0x02
#define HID_USAGE_JOYSTICK                  0x04
#define HID_USAGE_GAMEPAD                   0x05

#define HID_USAGE_PAGE_CONSUMER_DEVICE      0x0C
#define HID_USAGE_CONSUMER_CONTROL          0x01

/* HID BT COD外围设备最小值主要作用*/
#define ESP_HID_COD_MIN_KEYBOARD            0x10
#define ESP_HID_COD_MIN_MOUSE               0x20

/* HID BLE外观*/
#define ESP_HID_APPEARANCE_GENERIC          0x03C0
#define ESP_HID_APPEARANCE_KEYBOARD         0x03C1
#define ESP_HID_APPEARANCE_MOUSE            0x03C2
#define ESP_HID_APPEARANCE_JOYSTICK         0x03C3
#define ESP_HID_APPEARANCE_GAMEPAD          0x03C4

/* HID报告类型*/
#define ESP_HID_REPORT_TYPE_INPUT           1
#define ESP_HID_REPORT_TYPE_OUTPUT          2
#define ESP_HID_REPORT_TYPE_FEATURE         3

/* HID协议模式*/
#define ESP_HID_PROTOCOL_MODE_BOOT          0x00      // 启动协议模式
#define ESP_HID_PROTOCOL_MODE_REPORT        0x01      // 报告协议模式

/* HID信息标志*/
#define ESP_HID_FLAGS_REMOTE_WAKE           0x01      // 远程唤醒
#define ESP_HID_FLAGS_NORMALLY_CONNECTABLE  0x02      // 正常可连接

/* 控制点命令*/
#define ESP_HID_CONTROL_SUSPEND             0x00      // 悬
#define ESP_HID_CONTROL_EXIT_SUSPEND        0x01      // 退出挂起

/* 客户端特征配置值*/
#define ESP_HID_CCC_NOTIFICATIONS_ENABLED   0x01      // 已启用通知
#define ESP_HID_CCC_INDICATIONS_ENABLED     0x02      // 指示已启用

/* HID传输*/
typedef enum {
    ESP_HID_TRANSPORT_BT,
    ESP_HID_TRANSPORT_BLE,
    ESP_HID_TRANSPORT_USB,
    ESP_HID_TRANSPORT_MAX
} esp_hid_transport_t;

/* HID使用类型*/
typedef enum {
    ESP_HID_USAGE_GENERIC  = 0,
    ESP_HID_USAGE_KEYBOARD = 1,
    ESP_HID_USAGE_MOUSE    = 2,
    ESP_HID_USAGE_JOYSTICK = 4,
    ESP_HID_USAGE_GAMEPAD  = 8,
    ESP_HID_USAGE_TABLET   = 16,
    ESP_HID_USAGE_CCONTROL = 32,
    ESP_HID_USAGE_VENDOR   = 64
} esp_hid_usage_t;

/* HID BT COD外围最小值。掩码（键盘|鼠标|ESP_HIDH_COD_*）*/
typedef enum {
    ESP_HID_COD_MIN_GENERIC,
    ESP_HID_COD_MIN_JOYSTICK,
    ESP_HID_COD_MIN_GAMEPAD,
    ESP_HID_COD_MIN_REMOTE,
    ESP_HID_COD_MIN_SENSOR,
    ESP_HID_COD_MIN_TABLET,
    ESP_HID_COD_MIN_CARD_READER,
    ESP_HID_COD_MIN_MAX
} esp_hid_cod_min_t;

/* HID事务类型*/
typedef enum {
    ESP_HID_TRANS_HANDSHAKE = 0,
    ESP_HID_TRANS_CONTROL = 1,
    ESP_HID_TRANS_GET_REPORT = 4,
    ESP_HID_TRANS_SET_REPORT = 5,
    ESP_HID_TRANS_GET_PROTOCOL = 6,
    ESP_HID_TRANS_SET_PROTOCOL = 7,
    ESP_HID_TRANS_GET_IDLE = 8,
    ESP_HID_TRANS_SET_IDLE = 9,
    ESP_HID_TRANS_DATA = 10,
    ESP_HID_TRANS_DATAC = 11,
    ESP_HID_TRANS_MAX
} esp_hid_trans_type_t;

/**
 * @brief HID报告项结构
 */
typedef struct {
    uint8_t map_index;              /*!< HID报告映射索引*/
    uint8_t report_id;              /*!< HID报告id*/
    uint8_t report_type;            /*!< HID报告类型*/
    uint8_t protocol_mode;          /*!< HID协议模式*/
    esp_hid_usage_t usage;          /*!< HID使用类型*/
    uint16_t value_len;             /*!< HID报告长度（字节）*/
} esp_hid_report_item_t;

/**
 * @brief HID解析的报表映射结构
 */
typedef struct {
    esp_hid_usage_t usage;              /*!< 主要的HID使用。（键盘>鼠标>游戏杆>游戏板>通用）*/
    uint16_t appearance;                /*!< 基于主要用途计算的HID外观*/
    uint8_t reports_len;                /*!< 报告映射中发现的报告数*/
    esp_hid_report_item_t *reports;     /*!< 在报告映射中发现的报告*/
} esp_hid_report_map_t;

/**
 * @brief HID原始报告映射结构
 */
typedef struct {
    const uint8_t *data;                /*!< 指向HID报告映射数据的指针*/
    uint16_t len;                       /*!< HID报告映射数据长度*/
} esp_hid_raw_report_map_t;

/**
 * @brief HID设备配置结构
 */
typedef struct {
    uint16_t vendor_id;                     /*!< HID供应商ID*/
    uint16_t product_id;                    /*!< HID产品ID*/
    uint16_t version;                       /*!< HID产品版本*/
    const char *device_name;                /*!< HID设备名称*/
    const char *manufacturer_name;          /*!< HID制造商*/
    const char *serial_number;              /*!< HID序列号*/
    esp_hid_raw_report_map_t *report_maps;  /*!< 原始HID报告映射的数组*/
    uint8_t report_maps_len;                /*!< 阵列中的原始报表映射数*/
} esp_hid_device_config_t;

/*
 * @brief 解析RAW HID报告映射当不再需要时，用户有责任释放解析后的报告映射。使用esp_hid_free_report_map
 * @param hid_rm      ：指向隐藏报表映射数据的指针
 * @param hid_rm_len  ：隐藏报告映射数据的长度
 *
 * @return: 指向已分析报表映射的指针
 */
esp_hid_report_map_t *esp_hid_parse_report_map(const uint8_t *hid_rm, size_t hid_rm_len);

/*
 * @brief 自由解析的HID报告映射
 * @param map      ：指向已分析的隐藏报表映射的指针
 */
void esp_hid_free_report_map(esp_hid_report_map_t *map);

/**
 * @brief 根据BLE外观计算HID设备使用类型
 * @param appearance ：BLE外观值
 *
 * @return: hid使用类型
 */
esp_hid_usage_t esp_hid_usage_from_appearance(uint16_t appearance);

/**
 * @brief 根据BT CoD计算HID设备使用类型
 * @param cod ：BT CoD值
 *
 * @return: hid使用类型
 */
esp_hid_usage_t esp_hid_usage_from_cod(uint32_t cod);

/**
 * @brief 将设备使用类型转换为字符串
 * @param usage ：要转换的HID使用类型
 *
 * @return: 指向字符串或NULL的指针
 */
const char *esp_hid_usage_str(esp_hid_usage_t usage);

/**
 * @brief 将HID协议模式转换为字符串
 * @param protocol_mode ：HID协议模式以转换BOOT/REPORT
 *
 * @return: 指向字符串或NULL的指针
 */
const char *esp_hid_protocol_mode_str(uint8_t protocol_mode);

/**
 * @brief 将HID报告类型转换为字符串
 * @param report_type ：要转换INPUT/OUTPUTE/FEATURE的HID报告类型
 *
 * @return: 指向字符串或NULL的指针
 */
const char *esp_hid_report_type_str(uint8_t report_type);

/**
 * @brief 将BT CoD大调转换为字符串
 * @param cod_major ：要转换的CoD主要值
 *
 * @return: 指向字符串或NULL的指针
 */
const char *esp_hid_cod_major_str(uint8_t cod_major);

/**
 * @brief 打印BT CoD次要值
 * @param cod_min ：要打印的CoD次要值
 * @param fp      ：指向输出文件的指针
 */
void esp_hid_cod_minor_print(uint8_t cod_min, FILE *fp);

/**
 * @brief 将BLE断开原因转换为字符串
 * @param reason ：原因的价值
 *
 * @return: 指向字符串或NULL的指针
 */
const char *esp_hid_disconnect_reason_str(esp_hid_transport_t transport, int reason);

#ifdef __cplusplus
}
#endif

