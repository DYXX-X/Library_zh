/*
 * SPDX文件版权文本：2015-2021浓缩咖啡系统（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */

#pragma once

/**
 * @brief 将数据信息发送到数字范围。
 * @param data 发送buff的指针。
 * @param channel_num 要显示的频道数。
 * @return 成功传输数据的长度。
 */
int test_tp_print_to_scope(float *data, unsigned char channel_num);

/**
 * @brief 初始化UART，以便将触摸传感器数据输出到数字示波器。
 * @return
 *      -ESP_OK成功
 *      -ESP_FAIL UART错误
 */
esp_err_t test_tp_scope_debug_init(uint8_t uart_num, int tx_io_num, int rx_io_num, int baud_rate);

