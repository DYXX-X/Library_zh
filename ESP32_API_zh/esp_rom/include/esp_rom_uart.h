// 版权所有2010-2020 Espressif Systems（上海）私人有限公司
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

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#define ESP_ROM_CDC_ACM_WORK_BUF_MIN 128

typedef enum {
    ESP_ROM_UART_0,
    ESP_ROM_UART_1,
    ESP_ROM_UART_USB
} esp_rom_uart_num_t;

/**
 * @brief 等待UART TX FIFO为空，所有数据都已发送出去。
 *
 * @param uart_no UART端口号
 */
void esp_rom_uart_tx_wait_idle(uint8_t uart_no);

/**
 * @brief 设置UART的时钟源和波特率。
 *
 * @param uart_no UART端口号
 * @param clock_hz 源时钟（Hz）
 * @param baud_rate 要设置的波特率
 */
void esp_rom_uart_set_clock_baudrate(uint8_t uart_no, uint32_t clock_hz, uint32_t baud_rate);

/**
 * @brief 等待UART TX FIFO为空（即刷新TX FIFO）
 *
 * @param uart_no UART端口号
 */
void esp_rom_uart_flush_tx(uint8_t uart_no);

/**
 * @brief 将一个字符传输到控制台通道。
 *
 * @param c 要发送的字符
 * @return
 *      -成功时为0
 *      -1出现故障
 */
int esp_rom_uart_tx_one_char(uint8_t c);

/**
 * @brief 将一个字符传输到控制台通道。
 * @note 此函数是esp_rom_uart_tx_one_char的包装器，它可以通过将“\n”替换为“\r\n”来帮助处理行结束问题。
 *
 * @param c 要发送的字符
 */
void esp_rom_uart_putc(char c);

/**
 * @brief 从控制台频道获取一个字符。
 *
 * @param c 存储字符的位置
 * @return
 *      -成功时为0
 *      -1故障或无可用数据
 */
int esp_rom_uart_rx_one_char(uint8_t *c);

/**
 * @brief 从控制台通道获取一行字符串（行结束不会存储在缓冲区中）。
 *
 * @param str 字符串的存储位置
 * @param max_len 缓冲区的最大长度（包括NULL分隔符）
 * @return 成功时始终返回0，或在循环中等待rx数据
 */
int esp_rom_uart_rx_string(uint8_t *str, uint8_t max_len);

/**
 * @brief 设置ets_printf使用的UART端口。
 *
 * @param uart_no UART端口号
 */
void esp_rom_uart_set_as_console(uint8_t uart_no);

/**
 * @brief 初始化USB ACM UART
 * @note ACM工作内存大小应至少为128字节（ESP_ROM_CDC_ACM_WORK_BUF_MIN）。
 *
 * @param cdc_acm_work_mem 指向用于CDC-ACM的工作内存的指针
 * @param cdc_acm_work_mem_len 工作记忆长度
 */
void esp_rom_uart_usb_acm_init(void *cdc_acm_work_mem, int cdc_acm_work_mem_len);

#ifdef __cplusplus
}
#endif

