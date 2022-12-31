/*
 * SPDX文件版权文本：2021浓缩咖啡系统（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */
#pragma once

#include <stdbool.h>
#include "esp_err.h"
#include "esp_lcd_types.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 面板设备的配置结构
 */
typedef struct {
    int reset_gpio_num; /*!< GPIO用于重置LCD面板，如果未使用，则设置为-1*/
    esp_lcd_color_space_t color_space; /*!< 设置LCD面板使用的颜色空间*/
    unsigned int bits_per_pixel;       /*!< 颜色深度（bpp）*/
    struct {
        unsigned int reset_active_high: 1; /*!< 如果面板重置处于高电平激活状态，则设置此项*/
    } flags;
    void *vendor_config; /* 供应商特定配置，可选，如果未使用，则保留为NULL*/
} esp_lcd_panel_dev_config_t;

/**
 * @brief 为ST7789型创建LCD面板
 *
 * @param[in] io LCD面板IO手柄
 * @param[in] panel_dev_config 通用面板设备配置
 * @param[out] ret_panel 返回的LCD面板手柄
 * @return
 *          -如果参数无效，则为ESP_ERR_INVALID_ARG
 *          -ESP_ERR_NO_MEM（如果内存不足）
 *          -成功时ESP_OK
 */
esp_err_t esp_lcd_new_panel_st7789(const esp_lcd_panel_io_handle_t io, const esp_lcd_panel_dev_config_t *panel_dev_config, esp_lcd_panel_handle_t *ret_panel);

/**
 * @brief 为NT35510型创建LCD面板
 *
 * @param[in] io LCD面板IO手柄
 * @param[in] panel_dev_config 通用面板设备配置
 * @param[out] ret_panel 返回的LCD面板手柄
 * @return
 *          -如果参数无效，则为ESP_ERR_INVALID_ARG
 *          -ESP_ERR_NO_MEM（如果内存不足）
 *          -成功时ESP_OK
 */
esp_err_t esp_lcd_new_panel_nt35510(const esp_lcd_panel_io_handle_t io, const esp_lcd_panel_dev_config_t *panel_dev_config, esp_lcd_panel_handle_t *ret_panel);

/**
 * @brief 为型号SSD1306创建LCD面板
 *
 * @param[in] io LCD面板IO手柄
 * @param[in] panel_dev_config 通用面板设备配置
 * @param[out] ret_panel 返回的LCD面板手柄
 * @return
 *          -如果参数无效，则为ESP_ERR_INVALID_ARG
 *          -ESP_ERR_NO_MEM（如果内存不足）
 *          -成功时ESP_OK
 */
esp_err_t esp_lcd_new_panel_ssd1306(const esp_lcd_panel_io_handle_t io, const esp_lcd_panel_dev_config_t *panel_dev_config, esp_lcd_panel_handle_t *ret_panel);

#ifdef __cplusplus
}
#endif

