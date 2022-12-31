// 版权所有2021 Espressif Systems（Shanghai）PTE LTD
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

//+-----------------------------------------------术语---------------------------------------------+
//|                                                                                                       |
//|CPU重置：仅重置CPU核心，一旦重置完成，CPU将从重置向量执行|
//|                                                                                                       |
//|核心重置：重置整个数字系统，RTC子系统除外|
//|                                                                                                       |
//|系统重置：重置整个数字系统，包括RTC子系统|
//|                                                                                                       |
//|芯片重置：重置整个芯片，包括模拟部分|
//|                                                                                                       |
//+-------------------------------------------------------------------------------------------------------+

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 命名约定：RESET_REASON_｛重置级别｝_｛复位原因｝
 * @note 请参阅TRM:<Reset and Clock>一章
 */
typedef enum {
    RESET_REASON_CHIP_POWER_ON   = 0x01, // 上电复位
    RESET_REASON_CHIP_BROWN_OUT  = 0x01, // VDD电压不稳定并重置芯片
    RESET_REASON_CHIP_SUPER_WDT  = 0x01, // 超级看门狗重置芯片
    RESET_REASON_CORE_SW         = 0x03, // 软件通过RTC_CNTL_SW_SYS_RST重置数字核心
    RESET_REASON_CORE_DEEP_SLEEP = 0x05, // 深度睡眠重置数字核心
    RESET_REASON_CORE_MWDT0      = 0x07, // 主看门狗0重置数字核心
    RESET_REASON_CORE_MWDT1      = 0x08, // 主看门狗1重置数字核心
    RESET_REASON_CORE_RTC_WDT    = 0x09, // RTC看门狗重置数字核心
    RESET_REASON_CPU0_MWDT0      = 0x0B, // 主看门狗0重置CPU 0
    RESET_REASON_CPU1_MWDT0      = 0x0B, // 主监视器0重置CPU 1
    RESET_REASON_CPU0_SW         = 0x0C, // 软件通过RTC_CNTL_SW_PROCPU_RST重置CPU 0
    RESET_REASON_CPU1_SW         = 0x0C, // 软件通过RTC_CNTL_SW_APPCPU_RST重置CPU 1
    RESET_REASON_CPU0_RTC_WDT    = 0x0D, // RTC看门狗重置CPU 0
    RESET_REASON_CPU1_RTC_WDT    = 0x0D, // RTC看门狗重置CPU 1
    RESET_REASON_SYS_BROWN_OUT   = 0x0F, // VDD电压不稳定并重置数字核心
    RESET_REASON_SYS_RTC_WDT     = 0x10, // RTC看门狗重置数字核心和RTC模块
    RESET_REASON_CPU0_MWDT1      = 0x11, // 主监视器1重置CPU 0
    RESET_REASON_CPU1_MWDT1      = 0x11, // 主看门狗1重置CPU 1
    RESET_REASON_SYS_SUPER_WDT   = 0x12, // 超级看门狗重置数字核心和rtc模块
    RESET_REASON_SYS_CLK_GLITCH  = 0x13, // 时钟闪烁重置数字核心和rtc模块
    RESET_REASON_CORE_EFUSE_CRC  = 0x14, // eFuse CRC错误重置数字核心
    RESET_REASON_CORE_USB_UART   = 0x15, // USB UART重置数字核心
    RESET_REASON_CORE_USB_JTAG   = 0x16, // USB JTAG重置数字核心
    RESET_REASON_CORE_PWR_GLITCH = 0x17, // 电源故障重置数字核心
} soc_reset_reason_t;

#ifdef __cplusplus
}
#endif

