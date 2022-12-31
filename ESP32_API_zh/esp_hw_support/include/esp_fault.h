/*
 * SPDX文件版权文本：2020-2021浓缩咖啡系统（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */
#include "sdkconfig.h"
#include "soc/rtc_cntl_reg.h"
#include "esp_rom_sys.h"

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 断言条件为真，其方式应能抵抗单故障攻击的故障注入。
 *
 * -多次扩展条件（条件必须没有副作用）
 * -编译器在每次求值条件之前都会被告知所有寄存器都是无效的，以避免错误导致对条件的所有三次求值中使用的寄存器的误读。
 * -如果条件为假，则触发系统重置。
 *
 * @note 在“正常”检查条件后放置此宏，条件检查将失败，并显示正常错误消息。这是在故障注入攻击跳过或损坏检查结果时的回退。（尽管确保攻击者不能使用错误注入跳过“正常”错误消息，以完全避免此检查。）
 *
 * @note 此宏会增加二进制大小，速度较慢，应谨慎使用。
 *
 * @note 此宏不能保证故障注入电阻。特别是必须仔细选择条件-此宏不会检测到将条件设置为真的故障注入攻击。还必须注意，攻击者不能使用错误来完全绕过调用任何函数测试ESP_fault_ASSERT。
 *
 * @note 这很难调试，因为故障会触发软件立即重置，并且UART输出经常被截断（因为FIFO未刷新）。定义ESP_FAULT_ASSERT_DEBUG宏以调试此宏由于软件错误而导致的任何故障。
 *
 * @param CONDITION 除非攻击者使用错误注入跳过或破坏某些其他关键系统计算，否则评估为真的条件。
 *
 */
#define ESP_FAULT_ASSERT(CONDITION) do {                \
        asm volatile ("" ::: "memory");                 \
        if(!(CONDITION)) _ESP_FAULT_RESET();            \
        asm volatile ("" ::: "memory");                 \
        if(!(CONDITION)) _ESP_FAULT_RESET();            \
        asm volatile ("" ::: "memory");                 \
        if(!(CONDITION)) _ESP_FAULT_RESET();            \
} while(0)

#ifndef CONFIG_IDF_TARGET_ARCH_RISCV
#define _ESP_FAULT_ILLEGAL_INSTRUCTION asm volatile("ill.n; ill.n; ill.n; ill.n; ill.n; ill.n; ill.n;")
#else
#define _ESP_FAULT_ILLEGAL_INSTRUCTION asm volatile("unimp; unimp; unimp; unimp; unimp;")
#endif

// 如果ESP_FAULT_ASSERT（）失败，请取消注释此宏以获取调试输出
//
// 请注意，取消注释此宏会降低反FI效果
//
//#定义ESP_FAULT_ASSERT_DEBUG

/* 内部宏，目的是在检测到故障注入导致的不一致时触发系统重置。

   存在非法指令操作码，以防CPU未按预期重置，从而使CPU崩溃。
*/
#ifndef ESP_FAULT_ASSERT_DEBUG

#define _ESP_FAULT_RESET()  do {                                \
        REG_WRITE(RTC_CNTL_OPTIONS0_REG, RTC_CNTL_SW_SYS_RST);  \
        _ESP_FAULT_ILLEGAL_INSTRUCTION;                         \
    } while(0)

#else // ESP_FAULT_ASSERT_DEBUG

#warning "Enabling ESP_FAULT_ASSERT_DEBUG makes ESP_FAULT_ASSERT() less effective"

#define _ESP_FAULT_RESET()  do {                                        \
        esp_rom_printf("ESP_FAULT_ASSERT %s:%d\n", __FILE__, __LINE__); \
        _ESP_FAULT_ILLEGAL_INSTRUCTION;                                 \
    } while(0)

#endif // ESP_FAULT_ASSERT_DEBUG

#ifdef __cplusplus
}
#endif

