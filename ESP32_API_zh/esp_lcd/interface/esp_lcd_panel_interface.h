/*
 * SPDX文件版权文本：2021浓缩咖啡系统（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */
#pragma once

#include <stdbool.h>
#include "esp_err.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct esp_lcd_panel_t esp_lcd_panel_t;  /*!< LCD面板类型*/

/**
 * @brief LCD面板接口
 */
struct esp_lcd_panel_t {
    /**
     * @brief 重置LCD面板
     *
     * @param[in] panel LCD面板句柄，由其他工厂API创建，如`esp_LCD_new_panel_st7789（）`@return
     *          -成功时ESP_OK
     */
    esp_err_t (*reset)(esp_lcd_panel_t *panel);

    /**
     * @brief 初始化LCD面板
     *
     * @param[in] panel LCD面板句柄，由其他工厂API创建，如`esp_LCD_new_panel_st7789（）`@return
     *          -成功时ESP_OK
     */
    esp_err_t (*init)(esp_lcd_panel_t *panel);

    /**
     * @brief Destory LCD面板
     *
     * @param[in] panel LCD面板句柄，由其他工厂API创建，如`esp_LCD_new_panel_st7789（）`@return
     *          -成功时ESP_OK
     */
    esp_err_t (*del)(esp_lcd_panel_t *panel);

    /**
     * @brief 在LCD面板上绘制位图
     *
     * @param[in] panel LCD面板句柄，由其他工厂API创建，如`esp_LCD_new_panel_st7789（）`
     * @param[in] x_start x轴上的起始索引（包括x_Start）
     * @param[in] y_start y轴上的起始索引（包括y_Start）
     * @param[in] x_end x轴上的结束索引（不包括x_End）
     * @param[in] y_end y轴上的结束索引（不包括y_End）
     * @param[in] color_data 将转储到特定窗口范围@return的RGB颜色数据
     *          -成功时ESP_OK
     */
    esp_err_t (*draw_bitmap)(esp_lcd_panel_t *panel, int x_start, int y_start, int x_end, int y_end, const void *color_data);

    /**
     * @brief 在特定轴上镜像LCD面板
     *
     * @note 将此功能与“swap_xy”结合使用，可以实现屏幕旋转
     *
     * @param[in] panel LCD面板句柄，由其他工厂API创建，如`esp_LCD_new_panel_st7789（）`
     * @param[in] x_axis 面板是否将围绕x_轴镜像
     * @param[in] y_axis 面板是否将围绕y_axis@return镜像
     *          -成功时ESP_OK
     *          -如果面板不支持此功能，则为ESP_ERR_NOT_SUPPORTED
     */
    esp_err_t (*mirror)(esp_lcd_panel_t *panel, bool x_axis, bool y_axis);

    /**
     * @brief 交换/交换x和y轴
     *
     * @note 将此功能与“镜像”结合，可以实现屏幕旋转
     *
     * @param[in] panel LCD面板句柄，由其他工厂API创建，如`esp_LCD_new_panel_st7789（）`
     * @param[in] swap_axes 返回时是否交换x轴和y轴
     *          -成功时ESP_OK
     *          -如果面板不支持此功能，则为ESP_ERR_NOT_SUPPORTED
     */
    esp_err_t (*swap_xy)(esp_lcd_panel_t *panel, bool swap_axes);

    /**
     * @brief 在x和y轴上设置额外间隙
     *
     * @note 间隙仅用于计算实际坐标。
     *
     * @param[in] panel LCD面板句柄，由其他工厂API创建，如`esp_LCD_new_panel_st7789（）`
     * @param[in] x_gap x轴上的额外间隙（像素）
     * @param[in] y_gap y轴上的额外间隙，单位为像素@返回
     *          -成功时ESP_OK
     */
    esp_err_t (*set_gap)(esp_lcd_panel_t *panel, int x_gap, int y_gap);

    /**
     * @brief 反转颜色（颜色数据线的位1->0，反之亦然）
     *
     * @param[in] panel LCD面板句柄，由其他工厂API创建，如`esp_LCD_new_panel_st7789（）`
     * @param[in] invert_color_data 是否反转颜色数据@return
     *          -成功时ESP_OK
     */
    esp_err_t (*invert_color)(esp_lcd_panel_t *panel, bool invert_color_data);

    /**
     * @brief 关闭显示器
     *
     * @param[in] panel LCD面板句柄，由其他工厂API创建，如`esp_LCD_new_panel_st7789（）`
     * @param[in] off 是否关闭屏幕@return
     *          -成功时ESP_OK
     *          -如果面板不支持此功能，则为ESP_ERR_NOT_SUPPORTED
     */
    esp_err_t (*disp_off)(esp_lcd_panel_t *panel, bool off);
};

#ifdef __cplusplus
}
#endif

