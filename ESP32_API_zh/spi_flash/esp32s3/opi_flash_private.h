/*
 * SPDX文件版权文本：2019-2021浓缩咖啡系统（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */

/**
 * 系统级OPI Flash API（专用）
 */

#pragma once

#include <stdint.h>
#include <stdbool.h>
#include "sdkconfig.h"
#include "esp_err.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 注册ROM功能和初始化闪存设备寄存器以使用八进制闪存
 *
 * @param chip_id 通过RDID命令读取的完整设备ID
 */
esp_err_t esp_opiflash_init(uint32_t chip_id);

/**
 * @brief 在此设置Octal Flash芯片特别需要的MSPI寄存器设置
 */
void esp_opiflash_set_required_regs(void);

#ifdef __cplusplus
}
#endif

