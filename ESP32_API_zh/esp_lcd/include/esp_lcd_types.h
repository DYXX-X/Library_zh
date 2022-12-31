/*
 * SPDX文件版权文本：2021浓缩咖啡系统（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */
#pragma once

#ifdef __cplusplus
extern "C" {
#endif

typedef struct esp_lcd_panel_io_t *esp_lcd_panel_io_handle_t; /*!< LCD面板IO手柄类型*/
typedef struct esp_lcd_panel_t *esp_lcd_panel_handle_t;       /*!< LCD面板手柄类型*/

/**
 * @brief LCD颜色空间类型定义
 */
typedef enum {
    ESP_LCD_COLOR_SPACE_RGB,        /*!< 颜色空间：RGB*/
    ESP_LCD_COLOR_SPACE_BGR,        /*!< 颜色空间：BGR*/
    ESP_LCD_COLOR_SPACE_MONOCHROME, /*!< 颜色空间：单色*/
} esp_lcd_color_space_t;

#ifdef __cplusplus
}
#endif

