/*
 * SPDX文件版权文本：2010-2021浓缩咖啡系统（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */

#ifndef _ESP_CPU_H
#define _ESP_CPU_H

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

#include "hal/cpu_hal.h"

#ifdef __cplusplus
extern "C" {
#endif

#define ESP_WATCHPOINT_LOAD 0x40000000
#define ESP_WATCHPOINT_STORE 0x80000000
#define ESP_WATCHPOINT_ACCESS 0xC0000000

typedef uint32_t esp_cpu_ccount_t;

/** @brief 读取当前堆栈指针地址
 *
 */
static inline void *esp_cpu_get_sp(void)
{
    return cpu_hal_get_sp();
}

/**
 * @brief 使用RTC控制器暂停CPU
 * @param cpu_id 要暂停的CPU ID（0=PRO，1=APP）
 */
void esp_cpu_stall(int cpu_id);

/**
 * @brief 使用RTC控制器卸载CPU
 * @param cpu_id 要卸载的CPU ID（0=PRO，1=APP）
 */
void esp_cpu_unstall(int cpu_id);

/**
 * @brief 使用RTC控制器重置CPU
 * @param cpu_id 要重置的CPU ID（0=PRO，1=APP）
 */
void esp_cpu_reset(int cpu_id);

/**
 * @brief 如果JTAG调试器连接到CPU OCD（片上调试）端口，则返回true。
 *
 * @note 如果禁用“使异常和恐慌处理程序JTAG/OCD感知”，则此函数始终返回false。
 */
bool esp_cpu_in_ocd_debug_mode(void);

static inline esp_cpu_ccount_t esp_cpu_get_ccount(void)
{
    return cpu_hal_get_cycle_count();
}

static inline void esp_cpu_set_ccount(esp_cpu_ccount_t val)
{
    cpu_hal_set_cycle_count(val);
}

/**
 * @brief 设置一个观察点，以在访问特定内存范围时中断/死机。
 *
 * @param no 观察点编号。在ESP32上，这可以是0或1。
 * @param adr 要监视的基地址
 * @param size 要监视的区域的大小，从基地址开始。必须是2^n之一，n在[0..6]中。
 * @param flags ESP_WATCHPOINT_*标志之一
 *
 * @return 无效参数上的ESP_ERR_INVALID_ARG，否则为ESP_OK
 *
 * @warning ESP32监视点硬件通过有效屏蔽大小为2^n的区域的较低n位来监视字节区域。如果adr对于这些较低的n位不为零，那么您可能没有看到您想要的区域。
 */
esp_err_t esp_cpu_set_watchpoint(int no, void *adr, int size, int flags);

/**
 * @brief 清除观察点
 *
 * @param no 要清除的观察点
 *
 */
void esp_cpu_clear_watchpoint(int no);

#ifdef __cplusplus
}
#endif

#endif // _ESP_CPU_H

