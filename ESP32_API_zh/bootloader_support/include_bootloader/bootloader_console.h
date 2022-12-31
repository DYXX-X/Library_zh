/*
 * SPDX文件版权文本：2020-2021浓缩咖啡系统（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */

#pragma once

/**
 * @brief 初始化控制台输出（UART或USB）
 */
void bootloader_console_init(void);

/**
 * @brief 刷新或以其他方式取消初始化控制台输出。
 */
void bootloader_console_deinit(void);

/**
 * @brief ets_install_putc1的“将字符写入USB”功能。仅当USB CDC用于控制台输出时才定义。
 */
void bootloader_console_write_char_usb(char c);

