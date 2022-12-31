/*
 * SPDX文件版权文本：2019-2021浓缩咖啡系统（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */

#pragma once

#include <esp_types.h>
#include <esp_err.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief ESP32的电子保险丝盒类型
 */
typedef enum {
    EFUSE_BLK0              = 0, /**<电子保险丝盒的数量。保留。*/

    EFUSE_BLK1              = 1, /**<电子保险丝盒的数量。用于闪存加密。如果不使用Flash加密功能，则可以将其用于其他目的。*/
    EFUSE_BLK_KEY0          = 1, /**<电子保险丝盒的数量。用于闪存加密。如果不使用Flash加密功能，则可以将其用于其他目的。*/
    EFUSE_BLK_ENCRYPT_FLASH = 1, /**<电子保险丝盒的数量。用于闪存加密。如果不使用Flash加密功能，则可以将其用于其他目的。*/

    EFUSE_BLK2              = 2, /**<电子保险丝盒的数量。用于安全引导。如果不使用该安全引导功能，它们可以用于其他目的。*/
    EFUSE_BLK_KEY1          = 2, /**<电子保险丝盒的数量。用于安全引导。如果不使用该安全引导功能，它们可以用于其他目的。*/
    EFUSE_BLK_SECURE_BOOT   = 2, /**<电子保险丝盒的数量。用于安全引导。如果不使用该安全引导功能，它们可以用于其他目的。*/

    EFUSE_BLK3              = 3, /**<电子保险丝盒的数量。用于用户目的。*/
    EFUSE_BLK_KEY2          = 3, /**<电子保险丝盒的数量。用于用户目的。*/
    EFUSE_BLK_KEY_MAX       = 4,

    EFUSE_BLK_MAX           = 4,
} esp_efuse_block_t;

/**
 * @brief 编码方案类型
 */
typedef enum {
    EFUSE_CODING_SCHEME_NONE    = 0,    /**<无*/
    EFUSE_CODING_SCHEME_3_4     = 1,    /**<3/4编码*/
    EFUSE_CODING_SCHEME_REPEAT  = 2,    /**<重复编码*/
} esp_efuse_coding_scheme_t;

/**
 * @brief 关键用途类型（虚拟，因为ESP32对块只有固定用途）
 */
typedef enum {
    ESP_EFUSE_KEY_PURPOSE_USER = 0,              /**< BLOCK3 */
    ESP_EFUSE_KEY_PURPOSE_SYSTEM = 1,            /**< BLOCK0 */
    ESP_EFUSE_KEY_PURPOSE_FLASH_ENCRYPTION = 2,  /**< BLOCK1 */
    ESP_EFUSE_KEY_PURPOSE_SECURE_BOOT_V2 = 3,    /**< BLOCK2 */
    ESP_EFUSE_KEY_PURPOSE_MAX,                   /**< MAX PURPOSE*/
} esp_efuse_purpose_t;


/**
 * @brief 永久更新写入efuse写入寄存器的值
 *
 * 用要写入的新值更新EFUSE_BLKx_WDATAx_REG寄存器后，调用此函数将其永久写入EFUSE。
 *
 * @note efuse中的设置位是永久的，不能取消设置。
 *
 * @note 由于此限制，您不需要将值从匹配的读寄存器复制到Efuse写寄存器，在读寄存器中设置但在匹配的写寄存器中未设置的位在写入新值时将保持不变。
 *
 * @note 此函数不是线程安全的，若调用代码从多个任务中更新efuse值，则这是调用者的责任。
 *
 * @deprecated 使用批处理模式，而不是直接调用burn命令。
 *
 * 在燃烧新的efuse之后，读取寄存器将被更新以匹配新的efuses值。
 */
void esp_efuse_burn_new_values(void) __attribute__ ((deprecated));

/* @brief 将随机数据写入efuse键块写入寄存器
 *
 * @note 调用方负责在调用之前确保efuse块为空且不受写保护。
 *
 * @note 行为取决于编码方案：为编码方案“无”生成并写入256位密钥，生成192位密钥，通过编码方案扩展到256位，然后为3/4编码方案写入。
 *
 * @note 此函数不会燃烧新值，调用方应在准备好时调用esp_efuse_burn_new_values（）。
 *
 * @deprecated 使用以下代码代替此函数：
 *
 * @code{c}
 * uint32_t键[8]；
 * size_t key_size=256；
 * 如果（coding_scheme==EFUSE_coding_scheme_3_4）{
 *     key_size＝192；
 * }
 * bootloader_fill_random（键，key_size/8）；
 * esp_efuse_write_block（efuse_BLK1，key，0，key_size）；
 * @endcode
 *
 * @param blk_wdata0_reg 块中第一个数据写入寄存器的地址
 */
void esp_efuse_write_random_key(uint32_t blk_wdata0_reg) __attribute__ ((deprecated));

#ifdef __cplusplus
}
#endif

