/*
 * SPDX文件版权文本：2015-2021浓缩咖啡系统（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */

#pragma once
#include <stdint.h>
#include <stdbool.h>
#include "esp_err.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @file PHY初始化参数和API
 */


/**
 * @brief 保存PHY初始化参数的结构
 */
typedef struct {
	uint8_t params[128];                    /*!< 不透明PHY初始化参数*/
} esp_phy_init_data_t;

/**
 * @brief 不透明PHY校准数据
 */
typedef struct {
    uint8_t version[4];                     /*!< PHY版本*/
    uint8_t mac[6];                         /*!< 站点的MAC地址*/
    uint8_t opaque[1894];                   /*!< 校准数据*/
} esp_phy_calibration_data_t;

typedef enum {
    PHY_RF_CAL_PARTIAL = 0x00000000,        /*!< 进行部分射频校准。应在通电复位后使用。*/
    PHY_RF_CAL_NONE    = 0x00000001,        /*!< 不要进行任何射频校准。此模式仅建议在深度睡眠重置后使用。*/
    PHY_RF_CAL_FULL    = 0x00000002         /*!< 进行全射频校准。产生最佳结果，但也消耗大量时间和电流。建议使用一次。*/
} esp_phy_calibration_mode_t;

#if CONFIG_ESP_PHY_MULTIPLE_INIT_DATA_BIN
/**
 * @brief PHY初始化数据类型
 */
typedef enum {
    ESP_PHY_INIT_DATA_TYPE_DEFAULT = 0,
    ESP_PHY_INIT_DATA_TYPE_SRRC,
    ESP_PHY_INIT_DATA_TYPE_FCC,
    ESP_PHY_INIT_DATA_TYPE_CE,
    ESP_PHY_INIT_DATA_TYPE_NCC,
    ESP_PHY_INIT_DATA_TYPE_KCC,
    ESP_PHY_INIT_DATA_TYPE_MIC,
    ESP_PHY_INIT_DATA_TYPE_IC,
    ESP_PHY_INIT_DATA_TYPE_ACMA,
    ESP_PHY_INIT_DATA_TYPE_ANATEL,
    ESP_PHY_INIT_DATA_TYPE_ISED,
    ESP_PHY_INIT_DATA_TYPE_WPC,
    ESP_PHY_INIT_DATA_TYPE_OFCA,
    ESP_PHY_INIT_DATA_TYPE_IFETEL,
    ESP_PHY_INIT_DATA_TYPE_RCM,
    ESP_PHY_INIT_DATA_TYPE_NUMBER,
} phy_init_data_type_t;
#endif

/**
 * @brief 获取PHY初始化数据
 *
 * 如果在menuconfig中设置了“Use a partition to store PHY init data”（使用分区存储PHY初始化数据）选项，则此函数将从分区加载PHY init数据。否则，PHY初始化数据将被编译到应用程序本身中，该函数将返回指向位于只读存储器（DROM）中的PHY初始化的数据的指针。
 *
 * 如果启用了“Use a partition to store PHY init data”（使用分区存储PHY初始化数据）选项，如果从闪存加载的数据无效，则此函数可能返回NULL。
 *
 * @note 在调用esp_wifi_init之后，调用esp_phy_release_init_data以释放使用此函数获得的指针。
 *
 * @return 指向PHY初始化数据结构的指针
 */
const esp_phy_init_data_t* esp_phy_get_init_data(void);

/**
 * @brief 释放PHY初始化数据
 * @param data  指向从esp_PHY_get_init_data函数获得的PHY init数据结构的指针
 */
void esp_phy_release_init_data(const esp_phy_init_data_t* data);

/**
 * @brief esp_phy_init调用函数加载phy校准数据
 *
 * 这是一个方便的功能，可用于从NVS加载PHY校准数据。可以使用esp_phy_store_cal_Data_to_NVS函数将数据存储到NVS。
 *
 * 如果NVS中不存在校准数据，或数据无效（从具有不同MAC地址的芯片获得，或从不同版本的软件获得），此函数将返回错误。
 *
 * 如果在menuconfig中设置了“初始化启动代码中的PHY”选项，则该功能将用于加载校准数据。要为加载校准数据提供不同的机制，请禁用menuconfig中的“初始化启动代码中的PHY”选项，并从应用程序调用esp_PHY_init函数。有关esp_phy_init和此函数的示例用法，请参见cpu_start.c中的esp_phy_store_cal_data_to_nvs函数
 *
 * @param out_cal_data 指向要填充加载数据的校准数据结构的指针。
 * @return 成功时ESP_OK
 */
esp_err_t esp_phy_load_cal_data_from_nvs(esp_phy_calibration_data_t* out_cal_data);

/**
 * @brief esp_phy_init调用的函数，用于存储phy校准数据
 *
 * 这是一个方便的功能，可用于将PHY校准数据存储到NVS。校准数据由esp_phy_init函数返回。使用此函数保存到NVS的数据稍后可以使用esp_phy_store_cal_Data_to_NVS函数加载。
 *
 * 如果在menuconfig中设置了“初始化启动代码中的PHY”选项，则此功能将用于存储校准数据。要为存储校准数据提供不同的机制，请禁用menuconfig中的“初始化启动代码中的PHY”选项，并从应用程序调用esp_PHY_init函数。
 *
 * @param cal_data 指向必须保存的校准数据的指针。
 * @return 成功时ESP_OK
 */
esp_err_t esp_phy_store_cal_data_to_nvs(const esp_phy_calibration_data_t* cal_data);

/**
 * @brief 擦除存储在NVS中的PHY校准数据
 *
 * 这是一个功能，如果使用部分校准，则可用于触发完全校准，作为最后的补救措施。可以根据某些条件（例如，在某些诊断模式中提供的选项）在应用程序中调用它。
 *
 * @return 成功时ESP_OK
 * @return 其他人失败了。请参阅NVS API返回值错误编号。
 */
esp_err_t esp_phy_erase_cal_data_in_nvs(void);

/**
 * @brief 启用PHY和RF模块
 *
 * 为了使用WiFi或BT，应启用PHY和RF模块。现在，当启动WiFi或BT时，PHY和射频启用工作将自动完成。用户不应在应用程序中调用此API。
 *
 */
void esp_phy_enable(void);

/**
 * @brief 禁用PHY和RF模块
 *
 * 为了关闭WiFi或BT，应禁用PHY模块。现在，当停止WiFi或BT时，PHY和RF禁用工作将自动完成。用户不应在应用程序中调用此API。
 *
 */
void esp_phy_disable(void);

/**
 * @brief 从NVS加载校准数据并初始化PHY和RF模块
 */
void esp_phy_load_cal_and_init(void);

#if CONFIG_MAC_BB_PD
/**
 * @brief 为MAC和基带通电/断电初始化备份内存
 */
void esp_mac_bb_pd_mem_init(void);

/**
 * @brief 启动MAC和基带
 */
void esp_mac_bb_power_up(void);

/**
 * @brief 关闭MAC和基带电源
 */
void esp_mac_bb_power_down(void);
#endif

/**
 * @brief 启用WiFi/BT公共时钟
 *
 */
void esp_phy_common_clock_enable(void);

/**
 * @brief 禁用WiFi/BT公共时钟
 *
 */
void esp_phy_common_clock_disable(void);

/**
 * @brief            获取PHY/RF打开时的时间戳
 * @return           如果PHY/RF从未打开，则返回0。否则，返回自上次打开PHY/RF时启动后的微秒时间
*/
int64_t esp_phy_rf_get_on_ts(void);

/**
 * @brief 根据Wi-Fi的国家代码更新相应的PHY初始化类型。
 */
esp_err_t esp_phy_update_country_info(const char *country);


#if CONFIG_ESP_PHY_MULTIPLE_INIT_DATA_BIN
/**
 * @brief 将PHY初始化bin应用于PHY
 * @return ESP_OK成功。
 * @return ESP_FAIL失败。
 */
esp_err_t esp_phy_apply_phy_init_data(uint8_t *init_data);
#endif

/**
 * @brief 获取PHY库版本
 * @return PHY库版本。
 */
char * get_phy_version_str(void);

#ifdef __cplusplus
}
#endif

