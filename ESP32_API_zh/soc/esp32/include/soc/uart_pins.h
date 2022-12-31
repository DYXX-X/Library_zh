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
#define U0TXD_GPIO_NUM  (1)
#define U0RXD_GPIO_NUM  (3)
#define U0CTS_GPIO_NUM  (19)
#define U0RTS_GPIO_NUM  (22)

#define U1TXD_GPIO_NUM  (10)
#define U1RXD_GPIO_NUM  (9)
#define U1CTS_GPIO_NUM  (6)
#define U1RTS_GPIO_NUM  (11)

#define U2TXD_GPIO_NUM  (17)
#define U2RXD_GPIO_NUM  (16)
#define U2CTS_GPIO_NUM  (8)
#define U2RTS_GPIO_NUM  (7)

/* 以下定义是在运行时重新配置UART以使用IOMUX所必需的。*/
#define U0TXD_MUX_FUNC  (FUNC_U0TXD_U0TXD)
#define U0RXD_MUX_FUNC  (FUNC_U0RXD_U0RXD)
#define U0RTS_MUX_FUNC  (FUNC_GPIO22_U0RTS)
#define U0CTS_MUX_FUNC  (FUNC_GPIO19_U0CTS)

#define U1TXD_MUX_FUNC  (FUNC_SD_DATA3_U1TXD)
#define U1RXD_MUX_FUNC  (FUNC_SD_DATA2_U1RXD)
#define U1RTS_MUX_FUNC  (FUNC_SD_CMD_U1RTS)
#define U1CTS_MUX_FUNC  (FUNC_SD_CLK_U1CTS)

#define U2TXD_MUX_FUNC  (FUNC_GPIO17_U2TXD)
#define U2RXD_MUX_FUNC  (FUNC_GPIO16_U2RXD)
#define U2RTS_MUX_FUNC  (FUNC_SD_DATA0_U2RTS)
#define U2CTS_MUX_FUNC  (FUNC_SD_DATA1_U2CTS)

