/*
 * SPDX文件版权所有文本：2016-2022 Espressif Systems（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */

#ifndef PHY_INIT_DATA_H
#define PHY_INIT_DATA_H /* 这里不要使用#pragma一次，我们有时会编译这个文件*/
#include "esp_phy_init.h"
#include "sdkconfig.h"

#ifdef __cplusplus
extern "C" {
#endif

// 将值限制在“低”和“高”之间（含）
#define LIMIT(val, low, high) ((val < low) ? low : (val > high) ? high : val)

#define PHY_INIT_MAGIC "PHYINIT"

// 将最低tx功率定义为lowest_PHY_tx_power
#define PHY_TX_POWER_LOWEST LIMIT(CONFIG_ESP_PHY_MAX_TX_POWER * 4, 0, 52)
#define PHY_TX_POWER_OFFSET 44
#define PHY_TX_POWER_NUM    5

#if CONFIG_ESP_PHY_MULTIPLE_INIT_DATA_BIN
#define PHY_CRC_ALGORITHM 1
#define PHY_COUNTRY_CODE_LEN 2
#define PHY_INIT_DATA_TYPE_OFFSET 126
#define PHY_SUPPORT_MULTIPLE_BIN_OFFSET 125
#endif

static const char phy_init_magic_pre[] = PHY_INIT_MAGIC;

/**
 * @brief 包含默认建议的PHY初始化参数的结构。
 */
static const esp_phy_init_data_t phy_init_data= { {
        0x80,
        0x00,
        LIMIT(CONFIG_ESP_PHY_MAX_TX_POWER * 4, 0, 0x4E),
        LIMIT(CONFIG_ESP_PHY_MAX_TX_POWER * 4, 0, 0x4E),
        LIMIT(CONFIG_ESP_PHY_MAX_TX_POWER * 4, 0, 0x48),
        LIMIT(CONFIG_ESP_PHY_MAX_TX_POWER * 4, 0, 0x48),
        LIMIT(CONFIG_ESP_PHY_MAX_TX_POWER * 4, 0, 0x48),
        LIMIT(CONFIG_ESP_PHY_MAX_TX_POWER * 4, 0, 0x48),
        LIMIT(CONFIG_ESP_PHY_MAX_TX_POWER * 4, 0, 0x48),
        LIMIT(CONFIG_ESP_PHY_MAX_TX_POWER * 4, 0, 0x48),
        LIMIT(CONFIG_ESP_PHY_MAX_TX_POWER * 4, 0, 0x44),
        LIMIT(CONFIG_ESP_PHY_MAX_TX_POWER * 4, 0, 0x44),
        LIMIT(CONFIG_ESP_PHY_MAX_TX_POWER * 4, 0, 0x48),
        LIMIT(CONFIG_ESP_PHY_MAX_TX_POWER * 4, 0, 0x48),
        LIMIT(CONFIG_ESP_PHY_MAX_TX_POWER * 4, 0, 0x44),
        LIMIT(CONFIG_ESP_PHY_MAX_TX_POWER * 4, 0, 0x42),
        0x00,
        0x00,
        0x00,
        0xff,
        0xff,
        0xff,
        0xff,
        0xff,
        0xff,
        0xff,
        0xff,
        0xff,
        0xff,
        0xff,
        0xff,
        0xff,
        0xff,
        0xff,
        0xff,
        0xff,
        0xff,
        0xff,
        0xff,
        0xff,
        0xff,
        0xff,
        0xff,
        0xff,
        0xff,
        0xff,
        0xff,
        0xff,
        0xff,
        0xff,
        0xff,
        0xff,
        0xff,
        0xff,
        0xff,
        0xff,
        0xff,
        0xff,
        0xff,
        0xff,
        0xff,
        0xff,
        0xff,
        0xff,
        0xff,
        0xff,
        0xff,
        0xff,
        0xff,
        0xff,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0xf1
} };

static const char phy_init_magic_post[] = PHY_INIT_MAGIC;

#if CONFIG_ESP_PHY_MULTIPLE_INIT_DATA_BIN
/**
 * @brief PHY初始化数据控制信息结构
 */
typedef struct {
    uint8_t control_info_checksum[4];     /*!< 4字节控制信息校验和*/
    uint8_t multiple_bin_checksum[4];     /*!< 4字节多箱校验和*/
    uint8_t check_algorithm;              /*!< 校验算法*/
    uint8_t version;                      /*!< PHY初始化数据箱版本*/
    uint8_t number;                       /*!< PHY初始化数据箱编号*/
    uint8_t length[2];                    /*!< 每个PHY初始化数据仓的长度*/
    uint8_t reserved[19];                 /*!< 保留19字节*/
} __attribute__ ((packed)) phy_control_info_data_t;

/**
 * @brief 国家对应于PHY初始化数据类型结构
 */
typedef struct {
    char cc[PHY_COUNTRY_CODE_LEN];
    uint8_t type;
} phy_country_to_bin_type_t;
#endif

#ifdef __cplusplus
}
#endif

#endif /* PHY_INIT_DATA_H */

