/*
 * SPDX文件版权文本：2021-2022浓缩咖啡系统（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */
#pragma once

#include <stdbool.h>
#include "esp_err.h"
#include "esp_lcd_types.h"
#include "soc/soc_caps.h"
#include "hal/lcd_types.h"

#ifdef __cplusplus
extern "C" {
#endif

#if SOC_LCD_RGB_SUPPORTED
/**
 * @brief LCD RGB时序结构
 * @verbatim 总宽度<-------------------------------------------->HSYNC宽度HBP有效宽度HFP<---><--><--------------------------------------------><--->____ ____ | _______________________________________ | ____ | | | | ___ | | | || | | __ | | |/| | | || | | | VSYNC | | |｜| | |宽度\ |/| __ | ||/| | ||||| | |VBP | | |//////////////////////////| | | | |///////////////////////|总计||/////////////////////////////| |高度|||////////////////////////////| | |活动||////////////\////////////////| ||高度|/////////活动显示区域////|| | | | |///////////////////////////| | | | |/////////////////| | | | ||/////////////////////////| | || | |////////////////////| || |||//////////////||||\|/______|_______________________________________ | |/| |/||VFP | | | \|/\|/_____|______________________________________________________|
 * @endverbatim
 */
typedef struct {
    unsigned int pclk_hz;           /*!< 像素时钟频率*/
    unsigned int h_res;             /*!< 水平分辨率，即一行中的像素数*/
    unsigned int v_res;             /*!< 垂直分辨率，即帧中的行数*/
    unsigned int hsync_pulse_width; /*!< 水平同步宽度，单位：PCLK周期*/
    unsigned int hsync_back_porch;  /*!< 水平后沿，hsync和行起始活动数据之间的PCLK数*/
    unsigned int hsync_front_porch; /*!< 水平前廊，活动数据结束和下一次hsync之间的PCLK数*/
    unsigned int vsync_pulse_width; /*!< 垂直同步宽度，单位：行数*/
    unsigned int vsync_back_porch;  /*!< 垂直后廊，vsync和帧开始之间的无效行数*/
    unsigned int vsync_front_porch; /*!< 垂直前廊，帧结束和下一个vsync之间的无效行数*/
    struct {
        unsigned int hsync_idle_low: 1;  /*!< hsync信号在IDLE（怠速）状态下为低电平*/
        unsigned int vsync_idle_low: 1;  /*!< 在IDLE状态下，vsync信号为低*/
        unsigned int de_idle_high: 1;    /*!< 在IDLE状态下，de信号为高*/
        unsigned int pclk_active_neg: 1; /*!< 显示数据是否在PCLK下降沿计时*/
        unsigned int pclk_idle_high: 1;  /*!< PCLK在IDLE阶段保持高电平*/
    } flags;
} esp_lcd_rgb_timing_t;

/**
 * @brief RGB LCD面板事件数据的类型
 */
typedef struct {
} esp_lcd_rgb_panel_event_data_t;

/**
 * @brief 声明当面板IO完成传输颜色数据时将调用的函数的原型
 *
 * @param[in] panel LCD面板句柄，从`esp_LCD_new_rgb_panel返回`
 * @param[in] edata 面板事件数据，由驾驶员提供
 * @param[in] user_ctx 用户数据，从`esp_lcd_rgb_panel_config_t传递`
 * @return 此函数是否唤醒了高优先级任务
 */
typedef bool (*esp_lcd_rgb_panel_frame_trans_done_cb_t)(esp_lcd_panel_handle_t panel, esp_lcd_rgb_panel_event_data_t *edata, void *user_ctx);

/**
 * @brief LCD RGB面板配置结构
 */
typedef struct {
    lcd_clock_source_t clk_src;   /*!< RGB LCD外围设备的时钟源*/
    esp_lcd_rgb_timing_t timings; /*!< RGB定时参数*/
    size_t data_width;            /*!< 数据线数量*/
    size_t sram_trans_align;      /*!< SRAM中分配的帧缓冲区对齐*/
    size_t psram_trans_align;     /*!< PSRAM中分配的帧缓冲区对齐*/
    int hsync_gpio_num;           /*!< 用于HSYNC信号的GPIO*/
    int vsync_gpio_num;           /*!< 用于VSYNC信号的GPIO*/
    int de_gpio_num;              /*!< GPIO用于DE信号，如果未使用，则设置为-1*/
    int pclk_gpio_num;            /*!< 用于PCLK信号的GPIO*/
    int data_gpio_nums[SOC_LCD_RGB_DATA_WIDTH]; /*!< 用于数据线的GPIO*/
    int disp_gpio_num; /*!< GPIO用于显示控制信号，如果未使用，则设置为-1*/
    esp_lcd_rgb_panel_frame_trans_done_cb_t on_frame_trans_done; /*!< 当一个帧缓冲区传输完成时调用回调*/
    void *user_ctx; /*!< 将传递给on_frame_trans_done的User_ctx的用户数据*/
    struct {
        unsigned int disp_active_low: 1; /*!< 如果该标志被启用，低电平的显示控制信号可以打开屏幕；反之亦然*/
        unsigned int relax_on_idle: 1;   /*!< 如果启用此标志，则如果主机的帧缓冲区中没有任何变化，主机将不会刷新LCD（这对于内置GRAM的LCD非常有用）*/
        unsigned int fb_in_psram: 1;     /*!< 如果启用此标志，将优先从PSRAM分配帧缓冲区*/
    } flags;
} esp_lcd_rgb_panel_config_t;

/**
 * @brief 创建RGB LCD面板
 *
 * @param rgb_panel_config RGB面板配置
 * @param ret_panel 返回的LCD面板手柄
 * @return
 *          -如果参数无效，则为ESP_ERR_INVALID_ARG
 *          -ESP_ERR_NO_MEM（如果内存不足）
 *          -ESP_ERR_NOT_FOUND（如果没有可用的RGB面板）
 *          -成功时ESP_OK
 */
esp_err_t esp_lcd_new_rgb_panel(const esp_lcd_rgb_panel_config_t *rgb_panel_config, esp_lcd_panel_handle_t *ret_panel);

#endif // SOC_LCD_RGB_SUPPORTED

#ifdef __cplusplus
}
#endif

