/*
 * SPDX文件版权文本：2021浓缩咖啡系统（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

typedef struct lcd_cam_dev_t *lcd_soc_handle_t;

typedef struct {
    lcd_soc_handle_t dev;
} lcd_hal_context_t;

void lcd_hal_init(lcd_hal_context_t *hal, int id);

#ifdef __cplusplus
}
#endif

