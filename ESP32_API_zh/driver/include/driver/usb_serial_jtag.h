// 版权所有2021 Espressif Systems（Shanghai）PTE LTD
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

#include "esp_err.h"
#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief usb串行jtag驱动程序的配置结构。未来可扩展
 *
 * @note  tx_buffer_size和rx_buffer_size必须大于0
 */
typedef struct {
    uint32_t tx_buffer_size;                    /* TX方向的缓冲区大小（字节）*/
    uint32_t rx_buffer_size;                    /* RX方向的缓冲区大小（字节）*/
} usb_serial_jtag_driver_config_t;

#define USB_SERIAL_JTAG_DRIVER_CONFIG_DEFAULT() (usb_serial_jtag_driver_config_t) {\
    .rx_buffer_size = 256,\
    .tx_buffer_size = 256,\
}

/**
 * @brief 安装USB-SRIAL-JTAG驱动程序，并将USB-SERIAL-JTAG设置为默认配置。
 *
 * USB-SRIAL-JTAG驱动程序的ISR将连接到调用此函数的同一CPU内核。因此，用户应确保在调用“usb_serial_jtag_driver_uninstall（）”时使用相同的内核。
 *
 * @note  阻塞模式将导致usb_serial_jtag_write_bytes（）阻塞，直到所有字节都写入TX FIFO。
 *
 * @param usb_serial_jtag_driver_config_t usb_serial_jtag驱动程序的配置。
 *
 * @return
 *     -ESP_OK成功
 *     -ESP_FAIL由于某种原因失败。
 */
esp_err_t usb_serial_jtag_driver_install(usb_serial_jtag_driver_config_t *usb_serial_jtag_config);

/**
 * @brief USB_SERIAL_JTAG从USB_SERIAL-JTAG缓冲区读取字节
 *
 * @param buf     指向缓冲区的指针。
 * @param length  数据长度
 * @param ticks_to_wait RTOS计时超时
 *
 * @return
 *     -从USB_SERIAL FIFO读取的字节数
 */
int usb_serial_jtag_read_bytes(void* buf, uint32_t length, TickType_t ticks_to_wait);

/**
 * @brief 从给定的缓冲器和长度向USB-UART端口发送数据，
 *
 * 请确保“tx_buffer_size大于0”，如果“tx_bbuffer_size”>0，则在将所有数据复制到tx环形缓冲区后，此函数将返回，然后USB_SERIAL_JTAG ISR将逐渐将数据从环形缓冲区移动到tx FIFO。
 *
 * @param src   数据缓冲地址
 * @param size  要发送的数据长度
 * @param ticks_to_wait RTOS计时超时
 *
 * @return
 *     -推送到TX FIFO的字节数
 */
int usb_serial_jtag_write_bytes(const void* src, size_t size, TickType_t ticks_to_wait);

/**
 * @brief 卸载USB-SRIAL-JTAG驱动程序。
 *
 * @return
 *     -ESP_OK成功
 */
esp_err_t usb_serial_jtag_driver_uninstall(void);

#ifdef __cplusplus
}
#endif

