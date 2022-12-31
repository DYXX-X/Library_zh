/*
 * SPDX文件版权所有文本：2015-2022 Espressif Systems（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */

#pragma once
#include "esp_phy_init.h"

#ifdef __cplusplus
extern "C" {
#endif

#define ESP_CAL_DATA_CHECK_FAIL 1

/**
 * @file 物理h
 * @brief libphy.a提供的函数声明
 */

/**
 * @brief 从PHY库返回ROM函数指针表。
 */
void phy_get_romfunc_addr(void);

/**
 * @brief 初始化PHY模块并进行RF校准
 * @param[in] init_data PHY使用的初始化参数
 * @param[inout] cal_data 输入之前获得的校准数据。作为输出，将包含新的校准数据。
 * @param[in] cal_mode  射频校准模式
 * @return ESP_CAL_DATA_CHECK_FAIL如果校准数据校验和失败，则保留其他值以供将来使用
 */
int register_chipv7_phy(const esp_phy_init_data_t* init_data, esp_phy_calibration_data_t *cal_data, esp_phy_calibration_mode_t cal_mode);

/**
 * @brief 获取PHY库使用的校准数据的格式版本。
 * @return 格式版本号，如果PHY处于仅WIFI模式，则用位（16）“或”。
 */
uint32_t phy_get_rf_cal_version(void);

/**
 * @brief 仅为WIFI模式或共存（WIFI和BT）模式设置RF/BB
 * @param[in] true 仅适用于WIFI模式，false适用于共存模式。默认值为0。
 * @return NULL
 */
void phy_set_wifi_mode_only(bool wifi_only);

/**
 * @brief 在共存模式下，将BT设置为最高优先级。
 * @return NULL
 */
void coex_bt_high_prio(void);

/**
 * @brief 打开PHY和RF。
 */
void phy_wakeup_init(void);

/**
 * @brief 关闭PHY和RF。
 */
void phy_close_rf(void);

#if !CONFIG_IDF_TARGET_ESP32
/**
 * @brief 禁用PHY温度传感器。
 */
void phy_xpd_tsens(void);
#endif

#if CONFIG_IDF_TARGET_ESP32C3
/**
 * @brief 当wifi deinit关闭wifi电源域时，更新PHY的内部状态。
 */
void phy_init_flag(void);
#endif

/**
 * @brief 存储和加载PHY数字寄存器。
 *
 * @param     backup_en  如果backup_en为真，则将PHY数字寄存器存储到存储器中。否则，从内存加载PHY数字寄存器
 * @param     mem_addr   存储和加载PHY数字寄存器的存储器地址
 *
 * @return    存储器大小
 */
uint8_t phy_dig_reg_backup(bool backup_en, uint32_t *mem_addr);

#if CONFIG_MAC_BB_PD
/**
 * @brief 存储和加载基带寄存器。
 */
void phy_freq_mem_backup(bool backup_en, uint32_t *mem);
#endif

#if CONFIG_ESP_PHY_ENABLE_USB
/**
 * @brief phy初始化时启用或禁用USB。
 */
void phy_bbpll_en_usb(bool en);
#endif

#if CONFIG_IDF_TARGET_ESP32S2
/**
 * @brief ESP32S2的物理版本选择
 */
void phy_eco_version_sel(uint8_t chip_ver);
#endif

#ifdef __cplusplus
}
#endif

