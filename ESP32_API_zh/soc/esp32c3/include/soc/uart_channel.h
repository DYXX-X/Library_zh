/*
 * SPDX文件版权所有文本：2020-2022 Espressif Systems（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */

// 该文件定义了ESP32C3上可用UART IO_MUX引脚的GPIO查找宏。

#ifndef _SOC_UART_CHANNEL_H
#define _SOC_UART_CHANNEL_H

//UART通道
#define UART_GPIO21_DIRECT_CHANNEL      UART_NUM_0
#define UART_NUM_0_TXD_DIRECT_GPIO_NUM  21
#define UART_GPIO20_DIRECT_CHANNEL      UART_NUM_0
#define UART_NUM_0_RXD_DIRECT_GPIO_NUM  20

#define UART_TXD_GPIO21_DIRECT_CHANNEL  UART_GPIO21_DIRECT_CHANNEL
#define UART_RXD_GPIO20_DIRECT_CHANNEL  UART_GPIO20_DIRECT_CHANNEL

#endif
