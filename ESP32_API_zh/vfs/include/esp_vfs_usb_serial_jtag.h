/*
 * SPDX文件版权文本：2021浓缩咖啡系统（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */

#pragma once

#include "esp_err.h"
#include "esp_vfs.h"
#include "esp_vfs_common.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 添加/dev/usbserjtag虚拟文件系统驱动程序
 *
 * 从启动代码调用此函数以启用控制台输出
 */
esp_err_t esp_vfs_dev_usb_serial_jtag_register(void);

/**
 * @brief 设置预期接收的行尾
 *
 * 这指定接收到的换行符与传递到stdin的换行符（'\n'，LF）之间的转换：
 *
 * -ESP_LINE_ENDINGS_CRLF：将CRLF转换为LF
 * -ESP_LINE_ENDINGS_CR：将CR转换为LF
 * -ESP_LINE_ENDINGS_LF：无修改
 *
 * @note 此函数不是线程安全的w.r.t.读取
 *
 * @param mode 需要行结尾
 */
void esp_vfs_dev_usb_serial_jtag_set_rx_line_endings(esp_line_endings_t mode);

/**
 * @brief 设置要发送的行尾
 *
 * 这指定stdout上的换行符（'\n'，LF）与发送的换行符之间的转换：
 *
 * -ESP_LINE_ENDINGS_CRLF：将LF转换为CRLF
 * -ESP_LINE_ENDINGS_CR：将LF转换为CR
 * -ESP_LINE_ENDINGS_LF：无修改
 *
 * @note 此函数不是线程安全的w.r.t.编写
 *
 * @param mode 要发送的行尾
 */
void esp_vfs_dev_usb_serial_jtag_set_tx_line_endings(esp_line_endings_t mode);

#ifdef __cplusplus
}
#endif

