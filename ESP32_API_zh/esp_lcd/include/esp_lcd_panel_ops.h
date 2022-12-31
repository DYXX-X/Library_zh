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
 * @brief 重置LCD面板
 *
 * @note 在尝试使用“esp_lcd_Panel_init（）”初始化面板之前，必须调用面板重置。
 *
 * @param[in] panel LCD面板句柄，由其他工厂API创建，如`esp_LCD_new_panel_st7789（）`
 * @return
 *          -成功时ESP_OK
 */
esp_err_t esp_lcd_panel_reset(esp_lcd_panel_handle_t panel);

/**
 * @brief 初始化LCD面板
 *
 * @note 在调用此函数之前，请确保LCD面板已通过“esp_LCD_panel_reset（）”完成“重置”阶段。
 *
 * @param[in] panel LCD面板句柄，由其他工厂API创建，如`esp_LCD_new_panel_st7789（）`
 * @return
 *          -成功时ESP_OK
 */
esp_err_t esp_lcd_panel_init(esp_lcd_panel_handle_t panel);

/**
 * @brief 取消初始化LCD面板
 *
 * @param[in] panel LCD面板句柄，由其他工厂API创建，如`esp_LCD_new_panel_st7789（）`
 * @return
 *          -成功时ESP_OK
 */
esp_err_t esp_lcd_panel_del(esp_lcd_panel_handle_t panel);

/**
 * @brief 在LCD面板上绘制位图
 *
 * @param[in] panel LCD面板句柄，由其他工厂API创建，如`esp_LCD_new_panel_st7789（）`
 * @param[in] x_start x轴上的起始索引（包括x_Start）
 * @param[in] y_start y轴上的起始索引（包括y_Start）
 * @param[in] x_end x轴上的结束索引（不包括x_End）
 * @param[in] y_end y轴上的结束索引（不包括y_End）
 * @param[in] color_data 将转储到特定窗口范围的RGB颜色数据
 * @return
 *          -成功时ESP_OK
 */
esp_err_t esp_lcd_panel_draw_bitmap(esp_lcd_panel_handle_t panel, int x_start, int y_start, int x_end, int y_end, const void *color_data);

/**
 * @brief 在特定轴上镜像LCD面板
 *
 * @note 结合“esp_lcd_panel_swap_xy（）”，可以实现屏幕旋转
 *
 * @param[in] panel LCD面板句柄，由其他工厂API创建，如`esp_LCD_new_panel_st7789（）`
 * @param[in] mirror_x 面板是否将围绕x轴镜像
 * @param[in] mirror_y 面板是否将围绕y轴镜像
 * @return
 *          -成功时ESP_OK
 *          -如果面板不支持此功能，则为ESP_ERR_NOT_SUPPORTED
 */
esp_err_t esp_lcd_panel_mirror(esp_lcd_panel_handle_t panel, bool mirror_x, bool mirror_y);

/**
 * @brief 交换/交换x和y轴
 *
 * @note 结合“esp_lcd_panel_mirror（）”，可以实现屏幕旋转
 *
 * @param[in] panel LCD面板句柄，由其他工厂API创建，如`esp_LCD_new_panel_st7789（）`
 * @param[in] swap_axes 是否交换x轴和y轴
 * @return
 *          -成功时ESP_OK
 *          -如果面板不支持此功能，则为ESP_ERR_NOT_SUPPORTED
 */
esp_err_t esp_lcd_panel_swap_xy(esp_lcd_panel_handle_t panel, bool swap_axes);

/**
 * @brief 在x和y轴上设置额外间隙
 *
 * 间隙是LCD面板的左侧/顶部与显示的实际内容的第一行/列之间的空间（以像素为单位）。
 *
 * @note 当定位或定心小于LCD的框架时，设置间隙非常有用。
 *
 * @param[in] panel LCD面板句柄，由其他工厂API创建，如`esp_LCD_new_panel_st7789（）`
 * @param[in] x_gap x轴上的额外间隙（像素）
 * @param[in] y_gap y轴上的额外间隙（像素）
 * @return
 *          -成功时ESP_OK
 */
esp_err_t esp_lcd_panel_set_gap(esp_lcd_panel_handle_t panel, int x_gap, int y_gap);

/**
 * @brief 反转颜色（逐位反转颜色数据线）
 *
 * @param[in] panel LCD面板句柄，由其他工厂API创建，如`esp_LCD_new_panel_st7789（）`
 * @param[in] invert_color_data 是否反转颜色数据
 * @return
 *          -成功时ESP_OK
 */
esp_err_t esp_lcd_panel_invert_color(esp_lcd_panel_handle_t panel, bool invert_color_data);

/**
 * @brief 关闭显示器
 *
 * @param[in] panel LCD面板句柄，由其他工厂API创建，如`esp_LCD_new_panel_st7789（）`
 * @param[in] off 是否关闭屏幕
 * @return
 *          -成功时ESP_OK
 *          -如果面板不支持此功能，则为ESP_ERR_NOT_SUPPORTED
 */
esp_err_t esp_lcd_panel_disp_off(esp_lcd_panel_handle_t panel, bool off);

#ifdef __cplusplus
}
#endif

