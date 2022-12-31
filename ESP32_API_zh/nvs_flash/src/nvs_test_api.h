// 版权所有2015-2016 Espressif Systems（上海）私人有限公司
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

#include "nvs_flash.h"

/**
 * @brief 使用自定义闪存扇区布局初始化NVS闪存
 *
 * @note  此API旨在用于单元测试。
 *
 * @param partName 根据分区表的NVS分区的分区名称
 * @param baseSector 启动NVS的闪存扇区（4096字节单位）偏移量
 * @param sectorCount NVS区域的长度（以闪存扇区为单位）。NVS分区必须至少有3个扇区长。
 * @return ESP_OK（如果闪存已成功初始化）
 */
esp_err_t nvs_flash_init_custom(const char *partName, uint32_t baseSector, uint32_t sectorCount);

#ifdef CONFIG_NVS_ENCRYPTION
/**
 * @brief 使用自定义闪存扇区布局初始化NVS闪存
 *
 * @note  此API旨在用于单元测试。
 *
 * @param partName 根据分区表的NVS分区的分区名称
 * @param baseSector 启动NVS的闪存扇区（4096字节单位）偏移量
 * @param sectorCount NVS区域的长度（以闪存扇区为单位）。NVS分区必须至少有3个扇区长。
 * @param[in]  cfg    用于NVS加密/解密的安全配置（密钥）。如果cfg为空，则不使用加密/解密。
 * @return ESP_OK（如果闪存已成功初始化）
 */
esp_err_t nvs_flash_secure_init_custom(const char *partName, uint32_t baseSector, uint32_t sectorCount, nvs_sec_cfg_t* cfg);
#endif

/**
 * @brief 将NVS存储的内容转储到标准输出
 *
 * 此功能可用于调试目的，以检查NVS页面的状态。对于每个页面，还将转储条目列表。
 *
 * @param partName 根据分区表的NVS分区的分区名称
 */
void nvs_dump(const char *partName);


#ifdef __cplusplus
}
#endif

