/*
 * SPDX文件版权文本：2021浓缩咖啡系统（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */

#pragma once

#include <stdbool.h>
#include <stdint.h>
#include "sdkconfig.h"
#include "esp_bit_defs.h"

#ifdef __cplusplus
extern "C" {
#endif


/**
 * @brief 芯片型号
 */
typedef enum {
    CHIP_ESP32  = 1, //!< ESP32
    CHIP_ESP32S2 = 2, //!< ESP32-S2
    CHIP_ESP32S3 = 9, //!< ESP32-S3
    CHIP_ESP32C3 = 5, //!< ESP32-C3
    CHIP_ESP32H2 = 6, //!< ESP32-H2
} esp_chip_model_t;

/* 芯片特征标志，用于esp_Chip_info_t*/
#define CHIP_FEATURE_EMB_FLASH      BIT(0)      //!< 芯片内置闪存
#define CHIP_FEATURE_WIFI_BGN       BIT(1)      //!< 芯片具有2.4GHz WiFi
#define CHIP_FEATURE_BLE            BIT(4)      //!< 芯片具有蓝牙LE
#define CHIP_FEATURE_BT             BIT(5)      //!< 芯片具有蓝牙经典
#define CHIP_FEATURE_IEEE802154     BIT(6)      //!< 芯片具有IEEE 802.15.4
#define CHIP_FEATURE_EMB_PSRAM      BIT(7)      //!< 芯片已嵌入psram

/**
 * @brief 该结构表示有关芯片的信息
 */
typedef struct {
    esp_chip_model_t model;  //!< 芯片模型，esp_chip_modelt之一
    uint32_t features;       //!< CHIP_FEATURE_x特征标志的位掩码
    uint8_t cores;           //!< CPU核数
    uint8_t revision;        //!< 芯片修订号
} esp_chip_info_t;

/**
 * @brief 用有关芯片的信息填充esp_chip_info_t结构
 * @param[out] out_info 待填充结构
 */
void esp_chip_info(esp_chip_info_t* out_info);

#if CONFIG_ESP32_ECO3_CACHE_LOCK_FIX
/**
 * @brief 缓存锁定错误是否存在
 *
 * @return
 *          -真：错误存在
 *          -false：错误不存在
 */
bool soc_has_cache_lock_bug(void);
#endif

#ifdef __cplusplus
}
#endif

