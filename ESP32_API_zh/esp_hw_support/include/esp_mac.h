/*
 * SPDX文件版权文本：2021浓缩咖啡系统（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */

#pragma once

#include "esp_err.h"
#include "sdkconfig.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    ESP_MAC_WIFI_STA,
    ESP_MAC_WIFI_SOFTAP,
    ESP_MAC_BT,
    ESP_MAC_ETH,
    ESP_MAC_IEEE802154,
} esp_mac_type_t;

/**@秒*/
#define TWO_UNIVERSAL_MAC_ADDR 2
#define FOUR_UNIVERSAL_MAC_ADDR 4
#if CONFIG_IDF_TARGET_ESP32
#define UNIVERSAL_MAC_ADDR_NUM CONFIG_ESP32_UNIVERSAL_MAC_ADDRESSES
#elif CONFIG_IDF_TARGET_ESP32S2
#define UNIVERSAL_MAC_ADDR_NUM CONFIG_ESP32S2_UNIVERSAL_MAC_ADDRESSES
#elif CONFIG_IDF_TARGET_ESP32S3
#define UNIVERSAL_MAC_ADDR_NUM CONFIG_ESP32S3_UNIVERSAL_MAC_ADDRESSES
#elif CONFIG_IDF_TARGET_ESP32C3
#define UNIVERSAL_MAC_ADDR_NUM CONFIG_ESP32C3_UNIVERSAL_MAC_ADDRESSES
#elif CONFIG_IDF_TARGET_ESP32H2
#define UNIVERSAL_MAC_ADDR_NUM CONFIG_ESP32H2_UNIVERSAL_MAC_ADDRESSES
#endif
/**@结束秒*/


/**
  * @brief  使用EFUSE的BLK3或外部存储器（如闪存和EEPROM）中存储的MAC地址设置基本MAC地址。
  *
  * 基本MAC地址用于生成网络接口使用的MAC地址。
  *
  * 如果使用自定义的基本MAC地址，请在初始化任何网络接口之前调用此API。有关如何使用基本MAC的详细信息，请参阅ESP-IDF编程指南。
  *
  * @note 基本MAC必须是单播MAC（第一个字节的最低有效位必须为零）。
  *
  * @note 如果未使用有效的OUI，请设置“本地管理”位（第一个字节中的位值0x02）以避免冲突。
  *
  * @param  mac 基本MAC地址，长度：6字节/8字节。长度：MAC-48为6字节EUI-64为8字节（用于IEEE 802.15.4）
  *
  * @return 成功时ESP_OK ESP_ERR_INVALID_ARG如果mac为空或不是单播mac
  */
esp_err_t esp_base_mac_addr_set(const uint8_t *mac);

/**
  * @brief  返回使用esp_base_MAC_addr_set设置的基本MAC地址。
  *
  * @note 如果未设置自定义基本MAC，则返回预先编程的Espressif基本MAC地址。
  *
  * @param  mac 基本MAC地址，长度：6字节/8字节。长度：MAC-48为6字节EUI-64为8字节（用于IEEE 802.15.4）
  *
  * @return ESP_ERR_INVALID_ARG mac成功时的ESP_OK为空ESP_ERR_INVALID_mac基mac地址尚未设置
  */
esp_err_t esp_base_mac_addr_get(uint8_t *mac);

/**
  * @brief  返回先前写入EFUSE的BLK3的基本MAC地址。
  *
  * 基本MAC地址用于生成网络接口使用的MAC地址。此API返回先前以指定格式写入EFUSE BLK3的自定义基本MAC地址。
  *
  * 编写此EFUSE允许设置不同的（非Espressif）基本MAC地址。也可以在其他地方存储自定义的基本MAC地址，有关详细信息，请参阅esp_base_MAC_addr_set（）。
  *
  * @note 此功能目前仅在ESP32上受支持。
  *
  * @param  mac 基本MAC地址，长度：6字节/8字节。长度：MAC-48为6字节EUI-64为8字节（用于IEEE 802.15.4）
  *
  * @return 成功时ESP_OK ESP_ERR_INVALID_ARG mac为空ESP_ERR_INVALID_mac CUSTOM_mac地址未设置，全为零（对于esp32 xx）ESP_ERR_IVALID_VERSION从EFUSE的BLK3读取了无效的mac版本字段（对于ESP 32）ESP_ERR _INVALID_CRC从EFUSE（对于esp2）的BLK3读取了无效mac CRC
  */
esp_err_t esp_efuse_mac_get_custom(uint8_t *mac);

/**
  * @brief  返回由Espressif在EFUSE中工厂编程的基本MAC地址。
  *
  * @param  mac 基本MAC地址，长度：6字节/8字节。长度：MAC-48为6字节EUI-64为8字节（用于IEEE 802.15.4）
  *
  * @return 成功时ESP_OK ESP_ERR_INVALID_ARG mac为空
  */
esp_err_t esp_efuse_mac_get_default(uint8_t *mac);

/**
  * @brief  读取基本MAC地址并设置接口的MAC地址。
  *
  * 此函数首先使用esp_base_MAC_addr_get（）获取基本MAC地址。然后计算所请求的特定接口的MAC地址，有关算法，请参阅ESP-IDF编程指南。
  *
  * @param  mac 基本MAC地址，长度：6字节/8字节。长度：MAC-48为6字节EUI-64为8字节（用于IEEE 802.15.4）
  * @param  type 要返回的MAC地址类型
  *
  * @return 成功时ESP_OK
  */
esp_err_t esp_read_mac(uint8_t *mac, esp_mac_type_t type);

/**
  * @brief 从通用MAC地址导出本地MAC地址。
  *
  * 此函数复制通用MAC地址，然后在第一个八位字节中设置“本地管理”位（位0x2），从而创建本地管理的MAC地址。
  *
  * 如果通用MAC地址参数已经是本地管理的MAC地址，则第一个八位字节与0x4进行异或，以创建不同的本地管理的IP地址。
  *
  * @param  mac 基本MAC地址，长度：6字节/8字节。长度：MAC-48为6字节EUI-64为8字节（用于IEEE 802.15.4）
  * @param  universal_mac  源通用MAC地址，长度：6字节。
  *
  * @return 成功时ESP_OK
  */
esp_err_t esp_derive_local_mac(uint8_t *local_mac, const uint8_t *universal_mac);

#ifdef __cplusplus
}
#endif

