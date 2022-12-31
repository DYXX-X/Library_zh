/*
 * SPDX文件版权所有文本：2016 Cesanta Software Limited
 *
 * SPDX许可证标识符：GPL-2.0或
 *
 * SPDX文件贡献者：2016-2022 Espressif Systems（上海）有限公司
 */

#pragma once

#include <stdint.h>
#include <stdbool.h>

/* 调用以初始化I/O（此时为UART或USB CDC）。参数是一个回调函数，当使用异步（中断驱动）RX时，它将处理接收的字符。它将在中断上下文中调用。
 */
void stub_io_init(void(*rx_cb_func)(char));

/* 为UART或USB启用或禁用异步（中断驱动）RX。当前只需要read_flash命令。
 */
void stub_rx_async_enable(bool enable);

/* uart_tx_one_char或USB CDC输出函数的包装器。（ROM中的uart_tx_one_char也可以处理USB CDC，但它非常慢，因为它在每个字节后刷新FIFO）。
 */
void stub_tx_one_char(char c);

/* 接收一个字符的阻塞（轮询）功能。应仅在异步（中断驱动）RX被禁用时使用。当前只需要read_flash命令。
 */
char stub_rx_one_char(void);

/* 确保所有输出都已发送到主机后返回*/
void stub_tx_flush(void);

/* 根据当前波特率（从主机角度）和请求的波特率更新波特率除法器。USB CDC无操作。
 */
void stub_io_set_baudrate(uint32_t current_baud, uint32_t new_baud);

/* 在等待命令时定期调用。UART无操作，USB CDC处理DTR/RTS重置。
 */
void stub_io_idle_hook(void);



