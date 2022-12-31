/*
 * SPDX文件版权文本：2015-2021浓缩咖啡系统（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */

#pragma once

#include <stdint.h>
#include <stdbool.h>

#define MHZ (1000000)

#define DPORT_CPUPERIOD_SEL_80		0
#define DPORT_CPUPERIOD_SEL_160		1
#define DPORT_CPUPERIOD_SEL_240		2

#define DPORT_SOC_CLK_SEL_XTAL    0
#define DPORT_SOC_CLK_SEL_PLL    1
#define DPORT_SOC_CLK_SEL_8M     2
#define DPORT_SOC_CLK_SEL_APLL   3

#define RTC_FAST_CLK_FREQ_8M        8500000

#ifdef __cplusplus
extern "C" {
#endif

void rtc_clk_cpu_freq_to_xtal(int freq, int div);

/* RTC_XTAL_FREQ_REG和RTC_APB_FREQ_REG的值作为两个副本存储在低位和高位16位半部分中。这些是使用这种表示的例程。
 */
static inline bool clk_val_is_valid(uint32_t val) {
    return (val & 0xffff) == ((val >> 16) & 0xffff) &&
            val != 0 &&
            val != UINT32_MAX;
}

static inline uint32_t reg_val_to_clk_val(uint32_t val) {
    return val & UINT16_MAX;
}

static inline uint32_t clk_val_to_reg_val(uint32_t val) {
    return (val & UINT16_MAX) | ((val & UINT16_MAX) << 16);
}

#ifdef __cplusplus
}
#endif

