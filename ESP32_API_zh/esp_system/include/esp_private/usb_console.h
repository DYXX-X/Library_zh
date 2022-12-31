// 版权所有2019-2020 Espressif Systems（上海）私人有限公司
//
// 根据Apache许可证2.0版（“许可证”）获得许可；
// 除非符合许可证，否则不得使用此文件。
// 您可以在以下地址获取许可证副本：
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// 除非适用法律要求或书面同意，软件
// 根据许可证分发的内容是按“原样”分发的，
// 无任何明示或暗示的保证或条件。
// 有关管理权限和
// 许可证下的限制。

#pragma once

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include "esp_err.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @file usb_console。h此文件包含低级USB控制台功能的定义。这些函数不被视为公共接口，不应由应用程序直接调用。USB控制台的应用程序接口由“cdcacm”VFS驱动程序或TinyUSB中的USB CDC驱动程序提供。
 */


/**
 * RX/TX回调函数类型
 * @param arg  回调特定上下文指针
 */
typedef void (*esp_usb_console_cb_t)(void* arg);

/**
 * 使用ROM USB CDC驱动程序初始化USB控制台输出。如果选择USB CDC作为控制台输出选项，则早期启动代码会调用此功能。
 * @return
 *  -成功时ESP_OK
 *  - ESP_ERR_NO_MEM
 *  -来自中断分配器的其他错误代码
 */
esp_err_t esp_usb_console_init(void);

/**
 * 向USB CDC写入缓冲区
 * @param buf  要写入的数据
 * @param size  数据大小（字节）
 * @return -出错时为1，否则为字节数
 */
ssize_t esp_usb_console_write_buf(const char* buf, size_t size);

ssize_t esp_usb_console_flush(void);

ssize_t esp_usb_console_read_buf(char* buf, size_t buf_size);

bool esp_usb_console_read_available(void);

bool esp_usb_console_write_available(void);

esp_err_t esp_usb_console_set_cb(esp_usb_console_cb_t rx_cb, esp_usb_console_cb_t tx_cb, void* arg);

#ifdef __cplusplus
}
#endif

