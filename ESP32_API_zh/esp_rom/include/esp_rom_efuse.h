// 版权所有2010-2020 Espressif Systems（上海）私人有限公司
//
// 根据Apache许可证2.0版（“许可证”）获得许可；
// 除非符合许可证，否则不得使用此文件。
// 您可以在以下地址获取许可证副本：
//
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
#include <stdbool.h>

#define ESP_ROM_EFUSE_FLASH_DEFAULT_SPI  (0)
#define ESP_ROM_EFUSE_FLASH_DEFAULT_HSPI (1)

/**
 * @brief 用于eFuse中存储的MAC地址的CRC8算法
 *
 * @param data 指向原始数据的指针
 * @param len 数据长度（字节）
 * @return uint8_t CRC值
 */
uint8_t esp_rom_efuse_mac_address_crc8(const uint8_t *data, uint32_t len);

/**
 * @brief 从eFuse获取SPI闪存GPIO引脚配置
 *
 * @return uint32_t
 *          -0：默认SPI引脚（ESP_ROM_EFUSE_FLASH_default_SPI）
 *          -1：默认HSPI引脚（ESP_ROM_EFUSE_FLASH_default_HSPI）
 *          -其他：定制引脚配置掩码。引脚按照EFUSE_SPICONFIG_RET_SPICLK、EFUSE_SPICONFIG_RET_SPIQ、EFUSE_StPICONFIG_RET_SPID、EFUSE_PPICONFIG_RET_SPICS0、EFUSE_SPICONFIG-RET_SPIHD宏进行编码。
 *
 * @note WP引脚（用于四输入/输出模式）未保存在eFuse中，且此功能不会返回。
 */
uint32_t esp_rom_efuse_get_flash_gpio_info(void);

/**
 * @brief 从eFuse获取SPI闪存WP引脚信息
 *
 * @return uint32_t
 *      -0x3F:GPIO编号无效
 *      -0~46：有效的GPIO编号
 */
uint32_t esp_rom_efuse_get_flash_wp_gpio(void);

/**
 * @brief 读取eFuse以检查安全引导是否已启用
 *
 * @return 如果启用了安全引导，则为true，否则为false
 */
bool esp_rom_efuse_is_secure_boot_enabled(void);

#ifdef __cplusplus
}
#endif

