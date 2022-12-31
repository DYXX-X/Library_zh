/*
 * SPDX文件版权文本：2015-2021浓缩咖啡系统（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */

#pragma once

#include "esp_vfs.h"
#include "esp_vfs_common.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 添加/dev/uart虚拟文件系统驱动程序
 *
 * 从启动代码调用此函数以启用串行输出
 */
void esp_vfs_dev_uart_register(void);

/**
 * @brief 设置预期在UART上接收的线路末端
 *
 * 这指定UART上接收到的行结尾与传递到stdin的换行符（'\n'，LF）之间的转换：
 *
 * -ESP_LINE_ENDINGS_CRLF：将CRLF转换为LF
 * -ESP_LINE_ENDINGS_CR：将CR转换为LF
 * -ESP_LINE_ENDINGS_LF：无修改
 *
 * @note 从UART读取时，此函数不是线程安全的
 *
 * @param mode UART上需要行结尾
 */
void esp_vfs_dev_uart_set_rx_line_endings(esp_line_endings_t mode) __attribute__((deprecated));

/**
 * @brief 设置发送到UART的线路末端
 *
 * 这指定stdout上的换行符（'\n'，LF）与通过UART发送的换行符之间的转换：
 *
 * -ESP_LINE_ENDINGS_CRLF：将LF转换为CRLF
 * -ESP_LINE_ENDINGS_CR：将LF转换为CR
 * -ESP_LINE_ENDINGS_LF：无修改
 *
 * @note 此函数在写入UART时不是线程安全的
 *
 * @param mode 发送到UART的线路末端
 */
void esp_vfs_dev_uart_set_tx_line_endings(esp_line_endings_t mode) __attribute__((deprecated));

/**
 * @brief 设置预期在指定UART上接收的线路末端
 *
 * 这指定UART上接收到的行结尾与传递到stdin的换行符（'\n'，LF）之间的转换：
 *
 * -ESP_LINE_ENDINGS_CRLF：将CRLF转换为LF
 * -ESP_LINE_ENDINGS_CR：将CR转换为LF
 * -ESP_LINE_ENDINGS_LF：无修改
 *
 * @note 从UART读取时，此函数不是线程安全的
 *
 * @param uart_num UART编号
 * @param mode 发送到UART的线路末端
 * @return  如果成功，则为0；如果发生错误（由errno指定），则为-1。
 */
int esp_vfs_dev_uart_port_set_rx_line_endings(int uart_num, esp_line_endings_t mode);

/**
 * @brief 设置发送到指定UART的线路末端
 *
 * 这指定stdout上的换行符（'\n'，LF）与通过UART发送的换行符之间的转换：
 *
 * -ESP_LINE_ENDINGS_CRLF：将LF转换为CRLF
 * -ESP_LINE_ENDINGS_CR：将LF转换为CR
 * -ESP_LINE_ENDINGS_LF：无修改
 *
 * @note 此函数在写入UART时不是线程安全的
 *
 * @param uart_num UART编号
 * @param mode 发送到UART的线路末端
  * @return  如果成功，则为0；如果发生错误（由errno指定），则为-1。
 */
int esp_vfs_dev_uart_port_set_tx_line_endings(int uart_num, esp_line_endings_t mode);

/**
 * @brief 将VFS设置为使用简单的函数来读取和写入UART。读取是非阻塞的，写入是忙碌的，等待TX FIFO有足够的空间。默认情况下使用这些功能。
 * @param uart_num UART外围设备编号
 */
void esp_vfs_dev_uart_use_nonblocking(int uart_num);

/**
 * @brief 将VFS设置为使用UART驱动程序进行读写
 * @note 在调用这些函数之前，应用程序必须配置UART驱动程序。使用这些函数，读取和写入是阻塞和中断驱动的。
 * @param uart_num UART外围设备编号
 */
void esp_vfs_dev_uart_use_driver(int uart_num);

/**
 * @brief 将VFS设置为使用USB-SRIAL-JTAG驱动程序进行读写
 * @note 应用程序在调用这些函数之前必须配置USB-SRIAL-JTAG驱动程序。使用这些函数，读取和写入是阻塞和中断驱动的。
 */
void esp_vfs_usb_serial_jtag_use_driver(void);

/**
 * @brief 将VFS设置为使用简单的函数来读取和写入UART。读取是非阻塞的，写入是忙碌的，等待TX FIFO有足够的空间。默认情况下使用这些功能。
 */
void esp_vfs_usb_serial_jtag_use_nonblocking(void);

#ifdef __cplusplus
}
#endif

