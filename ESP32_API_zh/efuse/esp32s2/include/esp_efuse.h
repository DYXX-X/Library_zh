/*
 * SPDX文件版权文本：2019-2021浓缩咖啡系统（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 电子保险丝盒类型ESP32S2
 */
typedef enum {
    EFUSE_BLK0                 = 0,   /**<电子保险丝BLOCK0.REPEAT_DATA的数量*/

    EFUSE_BLK1                 = 1,   /**<eFuse BLOCK1.MAC_SPI_8M_SYS数量*/

    EFUSE_BLK2                 = 2,   /**<eFuse BLOCK2.SYS_DATA_PART1的数量*/
    EFUSE_BLK_SYS_DATA_PART1   = 2,   /**<eFuse BLOCK2.SYS_DATA_PART1的数量*/

    EFUSE_BLK3                 = 3,   /**<eFuse BLOCK3.USER_DATA的数量*/
    EFUSE_BLK_USER_DATA        = 3,   /**<eFuse BLOCK3.USER_DATA的数量*/

    EFUSE_BLK4                 = 4,   /**<eFuse BLOCK4.KEY0的数量*/
    EFUSE_BLK_KEY0             = 4,   /**<eFuse BLOCK4.KEY0的数量*/

    EFUSE_BLK5                 = 5,   /**<eFuse BLOCK5.KEY1的数量*/
    EFUSE_BLK_KEY1             = 5,   /**<eFuse BLOCK5.KEY1的数量*/

    EFUSE_BLK6                 = 6,   /**<eFuse BLOCK6.KEY2的数量*/
    EFUSE_BLK_KEY2             = 6,   /**<eFuse BLOCK6.KEY2的数量*/

    EFUSE_BLK7                 = 7,   /**<eFuse BLOCK7.KEY3的数量*/
    EFUSE_BLK_KEY3             = 7,   /**<eFuse BLOCK7.KEY3的数量*/

    EFUSE_BLK8                 = 8,   /**<eFuse BLOCK8.KEY4的数量*/
    EFUSE_BLK_KEY4             = 8,   /**<eFuse BLOCK8.KEY4的数量*/

    EFUSE_BLK9                 = 9,   /**<eFuse BLOCK9.KEY5的数量*/
    EFUSE_BLK_KEY5             = 9,   /**<eFuse BLOCK9.KEY5的数量*/
    EFUSE_BLK_KEY_MAX          = 10,

    EFUSE_BLK10                = 10,  /**<eFuse BLOCK10.SYS_DATA_PART2的数量*/
    EFUSE_BLK_SYS_DATA_PART2   = 10,  /**<eFuse BLOCK10.SYS_DATA_PART2的数量*/

    EFUSE_BLK_MAX
} esp_efuse_block_t;

/**
 * @brief 编码方案类型
 */
typedef enum {
    EFUSE_CODING_SCHEME_NONE    = 0,    /**<无*/
    EFUSE_CODING_SCHEME_RS      = 3,    /**<里德-所罗门编码*/
} esp_efuse_coding_scheme_t;

/**
 * @brief 关键用途类型
 */
typedef enum {
    ESP_EFUSE_KEY_PURPOSE_USER = 0,                         /**<用户用途（仅限软件使用）*/
    ESP_EFUSE_KEY_PURPOSE_RESERVED = 1,                     /**<保留*/
    ESP_EFUSE_KEY_PURPOSE_XTS_AES_256_KEY_1 = 2,            /**<XTS_AES_256_KEY_1（闪存/PSRAM加密）*/
    ESP_EFUSE_KEY_PURPOSE_XTS_AES_256_KEY_2 = 3,            /**<XTS_AES_256_KEY_2（闪存/PSRAM加密）*/
    ESP_EFUSE_KEY_PURPOSE_XTS_AES_128_KEY = 4,              /**<XTS_AES_128_KEY（闪存/PSRAM加密）*/
    ESP_EFUSE_KEY_PURPOSE_HMAC_DOWN_ALL = 5,                /**<HMAC下游模式*/
    ESP_EFUSE_KEY_PURPOSE_HMAC_DOWN_JTAG = 6,               /**<JTAG软启用键（使用HMAC下游模式）*/
    ESP_EFUSE_KEY_PURPOSE_HMAC_DOWN_DIGITAL_SIGNATURE = 7,  /**<数字签名外围密钥（使用HMAC下游模式）*/
    ESP_EFUSE_KEY_PURPOSE_HMAC_UP = 8,                      /**<HMAC上游模式*/
    ESP_EFUSE_KEY_PURPOSE_SECURE_BOOT_DIGEST0 = 9,          /**<SECURE_BOOT_DIGEST0（安全引导密钥摘要）*/
    ESP_EFUSE_KEY_PURPOSE_SECURE_BOOT_DIGEST1 = 10,         /**<SECURE_BOOT_DIGEST1（安全引导密钥摘要）*/
    ESP_EFUSE_KEY_PURPOSE_SECURE_BOOT_DIGEST2 = 11,         /**<SECURE_BOOT_DIGEST2（安全引导密钥摘要）*/
    ESP_EFUSE_KEY_PURPOSE_MAX,                              /**< MAX PURPOSE */
} esp_efuse_purpose_t;

#ifdef __cplusplus
}
#endif

