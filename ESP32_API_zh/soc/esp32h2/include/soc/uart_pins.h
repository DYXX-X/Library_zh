// 版权所有2015-2021 Espressif Systems（Shanghai）PTE LTD
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

#include "soc/io_mux_reg.h"

/* 指定UART的引脚数*/
#define SOC_UART_PINS_COUNT  (4)

/* 指定IOMUX中每个UART信号的GPIO引脚号*/
#define U0RXD_GPIO_NUM 20
#define U0TXD_GPIO_NUM 21
#define U0RTS_GPIO_NUM (-1)
#define U0CTS_GPIO_NUM (-1)

#define U1RXD_GPIO_NUM (-1)
#define U1TXD_GPIO_NUM (-1)
#define U1RTS_GPIO_NUM (-1)
#define U1CTS_GPIO_NUM (-1)

/* 以下定义是在运行时重新配置UART以使用IOMUX所必需的。*/
#define U0TXD_MUX_FUNC  (FUNC_U0TXD_U0TXD)
#define U0RXD_MUX_FUNC  (FUNC_U0RXD_U0RXD)
/* 以下引脚无功能，不得使用*/
#define U0RTS_MUX_FUNC  (-1)
#define U0CTS_MUX_FUNC  (-1)
/* UART1也是如此*/
#define U1TXD_MUX_FUNC  (-1)
#define U1RXD_MUX_FUNC  (-1)
#define U1RTS_MUX_FUNC  (-1)
#define U1CTS_MUX_FUNC  (-1)

