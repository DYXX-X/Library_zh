/*
 * SPDX文件版权文本：2021浓缩咖啡系统（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */

#pragma once

#include "esp_err.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 添加uart/usbserialjtag/usb_otg_accdc虚拟文件系统驱动程序
 *
 * 从启动代码调用此函数以启用串行输出
 */
esp_err_t esp_vfs_console_register(void);

#ifdef __cplusplus
}
#endif

