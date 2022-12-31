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
#include "sdkconfig.h"
#include <stdint.h>
#include "soc/reset_reasons.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 将格式化的字符串打印到控制台设备
 * @note 不支持float和long-long数据！
 *
 * @param fmt 设置字符串格式
 * @param ... 其他参数，取决于格式字符串
 * @return int：成功时写入的字符总数；失败时为负数。
 */
int esp_rom_printf(const char *fmt, ...);

/**
 * @brief 暂停执行微秒
 *
 * @param us 暂停的微秒数
 */
void esp_rom_delay_us(uint32_t us);

/**
 * @brief esp_rom_printf可以同时将消息打印到不同的频道。此函数可以帮助安装esp_rom_printf的低级putc函数。
 *
 * @param channel 通道编号（从1开始）
 * @param putc 指向putc实现的函数指针。设置为NULL可以断开esp_rom_printf与putc的连接。
 */
void esp_rom_install_channel_putc(int channel, void (*putc)(char c));

/**
 * @brief 将UART1安装为默认控制台通道，相当于`esp_rom_Install_channel_putc（1，esp_rom_uart_putc）`
 */
void esp_rom_install_uart_printf(void);

/**
 * @brief 获取CPU复位原因
 *
 * @param cpu_no CPU编号
 * @return 重置原因代码（请参阅soc/Reset_freasons.h）
 */
soc_reset_reason_t esp_rom_get_reset_reason(int cpu_no);

#ifdef __cplusplus
}
#endif

