/*
 * SPDX文件版权文本：2015-2021浓缩咖啡系统（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 *
 * 这是编译ESP-IDF以在主机系统上运行测试时使用的STUB FILE HEADER。通常用于ESP-IDF的头文件具有相同的名称，但位于其他位置。
 */
#ifndef __ESP_PARTITION_H__
#define __ESP_PARTITION_H__

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include "esp_err.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    ESP_PARTITION_TYPE_APP = 0x00,       //!< 应用程序分区类型
    ESP_PARTITION_TYPE_DATA = 0x01,      //!< 数据分区类型
} esp_partition_type_t;

typedef enum {
    ESP_PARTITION_SUBTYPE_APP_FACTORY = 0x00,                                 //!< 工厂应用程序分区
    ESP_PARTITION_SUBTYPE_APP_OTA_MIN = 0x10,                                 //!< OTA分区子类型的基础
    ESP_PARTITION_SUBTYPE_APP_OTA_0 = ESP_PARTITION_SUBTYPE_APP_OTA_MIN + 0,  //!< OTA分区0
    ESP_PARTITION_SUBTYPE_APP_OTA_1 = ESP_PARTITION_SUBTYPE_APP_OTA_MIN + 1,  //!< OTA分区1
    ESP_PARTITION_SUBTYPE_APP_OTA_2 = ESP_PARTITION_SUBTYPE_APP_OTA_MIN + 2,  //!< OTA分区2
    ESP_PARTITION_SUBTYPE_APP_OTA_3 = ESP_PARTITION_SUBTYPE_APP_OTA_MIN + 3,  //!< OTA分区3
    ESP_PARTITION_SUBTYPE_APP_OTA_4 = ESP_PARTITION_SUBTYPE_APP_OTA_MIN + 4,  //!< OTA分区4
    ESP_PARTITION_SUBTYPE_APP_OTA_5 = ESP_PARTITION_SUBTYPE_APP_OTA_MIN + 5,  //!< OTA分区5
    ESP_PARTITION_SUBTYPE_APP_OTA_6 = ESP_PARTITION_SUBTYPE_APP_OTA_MIN + 6,  //!< OTA分区6
    ESP_PARTITION_SUBTYPE_APP_OTA_7 = ESP_PARTITION_SUBTYPE_APP_OTA_MIN + 7,  //!< OTA分区7
    ESP_PARTITION_SUBTYPE_APP_OTA_8 = ESP_PARTITION_SUBTYPE_APP_OTA_MIN + 8,  //!< OTA分区8
    ESP_PARTITION_SUBTYPE_APP_OTA_9 = ESP_PARTITION_SUBTYPE_APP_OTA_MIN + 9,  //!< OTA分区9
    ESP_PARTITION_SUBTYPE_APP_OTA_10 = ESP_PARTITION_SUBTYPE_APP_OTA_MIN + 10,//!< OTA分区10
    ESP_PARTITION_SUBTYPE_APP_OTA_11 = ESP_PARTITION_SUBTYPE_APP_OTA_MIN + 11,//!< OTA分区11
    ESP_PARTITION_SUBTYPE_APP_OTA_12 = ESP_PARTITION_SUBTYPE_APP_OTA_MIN + 12,//!< OTA分区12
    ESP_PARTITION_SUBTYPE_APP_OTA_13 = ESP_PARTITION_SUBTYPE_APP_OTA_MIN + 13,//!< OTA分区13
    ESP_PARTITION_SUBTYPE_APP_OTA_14 = ESP_PARTITION_SUBTYPE_APP_OTA_MIN + 14,//!< OTA分区14
    ESP_PARTITION_SUBTYPE_APP_OTA_15 = ESP_PARTITION_SUBTYPE_APP_OTA_MIN + 15,//!< OTA分区15
    ESP_PARTITION_SUBTYPE_APP_OTA_MAX = ESP_PARTITION_SUBTYPE_APP_OTA_MIN + 16,//!< OTA分区的最大子类型
    ESP_PARTITION_SUBTYPE_APP_TEST = 0x20,                                    //!< 测试应用程序分区

    ESP_PARTITION_SUBTYPE_DATA_OTA = 0x00,                                    //!< OTA选择分区
    ESP_PARTITION_SUBTYPE_DATA_PHY = 0x01,                                    //!< PHY初始化数据分区
    ESP_PARTITION_SUBTYPE_DATA_NVS = 0x02,                                    //!< NVS分区
    ESP_PARTITION_SUBTYPE_DATA_COREDUMP = 0x03,                               //!< COREDUMP分区
    ESP_PARTITION_SUBTYPE_DATA_NVS_KEYS = 0x04,                               //!< NVS密钥分区
    ESP_PARTITION_SUBTYPE_DATA_EFUSE_EM = 0x05,                               //!< 模拟eFuse位的分区
    ESP_PARTITION_SUBTYPE_DATA_UNDEFINED = 0x06,                              //!< 未定义（或未指定）的数据分区

    ESP_PARTITION_SUBTYPE_DATA_ESPHTTPD = 0x80,                               //!< ESPHTTPD分区
    ESP_PARTITION_SUBTYPE_DATA_FAT = 0x81,                                    //!< FAT分区
    ESP_PARTITION_SUBTYPE_DATA_SPIFFS = 0x82,                                 //!< SPIFFS分区

    ESP_PARTITION_SUBTYPE_ANY = 0xff,                                         //!< 用于搜索具有任何子类型的分区
} esp_partition_subtype_t;

/**
 * @brief 不透明分区迭代器类型
 */
typedef struct esp_partition_iterator_opaque_* esp_partition_iterator_t;

/**
 * @brief 分区信息结构
 *
 * 这不是flash中的格式，而是esp_partition_info_t。
 *
 * 然而，这是此API使用的格式。
 */
typedef struct {
    void* flash_chip;            /*!< 分区所在的SPI闪存芯片*/
    esp_partition_type_t type;          /*!< 分区类型（app/data）*/
    esp_partition_subtype_t subtype;    /*!< 分区子类型*/
    uint32_t address;                   /*!< 闪存中分区的起始地址*/
    uint32_t size;                      /*!< 分区大小，以字节为单位*/
    char label[17];                     /*!< 分区标签，以零结尾的ASCII字符串*/
    bool encrypted;                     /*!< 如果分区已加密，则标志设置为true*/
} esp_partition_t;

#ifdef __cplusplus
}
#endif


#endif /* __ESP_PARTITION_H__ */

