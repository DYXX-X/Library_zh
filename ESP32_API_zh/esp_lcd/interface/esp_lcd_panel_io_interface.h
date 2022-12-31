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

typedef struct esp_lcd_panel_io_t esp_lcd_panel_io_t; /*!< LCD面板IO类型*/

/**
 * @brief LCD面板IO接口
 */
struct esp_lcd_panel_io_t {
    /**
     * @brief 发送LCD命令和相应参数
     *
     * @note 这是由函数“esp_lcd_panel_io_tx_param（）”调用的面板特定接口。
     *
     * @param[in] io LCD面板IO句柄，由其他工厂API创建，如`esp_LCD_new_panel_IO_spi（）`
     * @param[in] lcd_cmd 特定LCD命令
     * @param[in] param 保存命令特定参数的缓冲区，如果命令不需要参数，则设置为NULL
     * @param[in] param_size 内存中“param”的大小（字节），如果命令@return不需要参数，则设置为零
     *          -如果参数无效，则为ESP_ERR_INVALID_ARG
     *          -成功时ESP_OK
     */
    esp_err_t (*tx_param)(esp_lcd_panel_io_t *io, int lcd_cmd, const void *param, size_t param_size);

    /**
     * @brief 传输LCD RGB数据
     *
     * @note 这是由函数“esp_lcd_panel_io_tx_color（）”调用的面板特定接口。
     *
     * @param[in] io LCD面板IO句柄，由其他工厂API创建，如`esp_LCD_new_panel_IO_spi（）`
     * @param[in] lcd_cmd 特定LCD命令
     * @param[in] color 保存RGB颜色数据的缓冲区
     * @param[in] color_size 内存中“color”的大小（字节@返回）
     *          -如果参数无效，则为ESP_ERR_INVALID_ARG
     *          -成功时ESP_OK
     */
    esp_err_t (*tx_color)(esp_lcd_panel_io_t *io, int lcd_cmd, const void *color, size_t color_size);

    /**
     * @brief Destory LCD面板IO句柄（取消初始化所有可用资源）
     *
     * @param[in] io LCD面板IO句柄，由其他工厂API创建，如`esp_LCD_new_panel_IO_spi（）`@return
     *          -如果参数无效，则为ESP_ERR_INVALID_ARG
     *          -成功时ESP_OK
     */
    esp_err_t (*del)(esp_lcd_panel_io_t *io);
};

#ifdef __cplusplus
}
#endif

