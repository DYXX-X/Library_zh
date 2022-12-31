/*
 * SPDX文件版权所有文本：2015-2022 Espressif Systems（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */

#ifndef __ESP_ATTR_H__
#define __ESP_ATTR_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "sdkconfig.h"

#define ROMFN_ATTR

//通常，链接器脚本会将所有代码和rodata放在flash中，
//以及共享RAM中的所有变量。这些宏可用于重定向
//特定函数/变量到其他存储器区域。

// 强制代码进入IRAM而不是闪存
#define IRAM_ATTR _SECTION_ATTR_IMPL(".iram1", __COUNTER__)

// 强制数据进入DRAM而不是闪存
#define DRAM_ATTR _SECTION_ATTR_IMPL(".dram1", __COUNTER__)

// 当设置CONFIG_ESP32_IRAM_as_8BIT_ACCESSIBLE_memory时，IRAM只能作为ESP32上的8位内存访问
#define IRAM_8BIT_ACCESSIBLE (CONFIG_IDF_TARGET_ESP32 && CONFIG_ESP32_IRAM_AS_8BIT_ACCESSIBLE_MEMORY)

// 确保IRAM可作为ESP32上的8位内存访问。
// 如果不是这样的话，coredump无法从IRAM转储数据。
#if IRAM_8BIT_ACCESSIBLE
// 强制数据进入IRAM而不是DRAM
#define IRAM_DATA_ATTR __attribute__((section(".iram.data")))

// 强制数据进入IRAM而不是DRAM，并将其映射到核心转储
#define COREDUMP_IRAM_DATA_ATTR _SECTION_ATTR_IMPL(".iram2.coredump", __COUNTER__)

// 强制bss进入IRAM而不是DRAM
#define IRAM_BSS_ATTR __attribute__((section(".iram.bss")))
#else

// IRAM不能作为8位内存访问，请将IRAM核心转储变量放入DRAM
#define COREDUMP_IRAM_DATA_ATTR COREDUMP_DRAM_ATTR
#define IRAM_DATA_ATTR

#define IRAM_BSS_ATTR
#endif

// 强制数据对齐4字节
#define WORD_ALIGNED_ATTR __attribute__((aligned(4)))

// 强制将数据放置到支持DMA的位置
#define DMA_ATTR WORD_ALIGNED_ATTR DRAM_ATTR

// 强制内联函数
#define FORCE_INLINE_ATTR static inline __attribute__((always_inline))

// 将字符串强制写入DRAM而不是闪存
// 用作esp_rom_printf（DRAM_STR（“Hello world！\n”））；
#define DRAM_STR(str) (__extension__({static const DRAM_ATTR char __c[] = (str); (const char *)&__c;}))

// 强制代码进入RTC快速内存。请参阅“docs/deep-sleepstub.rst”
#define RTC_IRAM_ATTR _SECTION_ATTR_IMPL(".rtc.text", __COUNTER__)

#if CONFIG_SPIRAM_ALLOW_BSS_SEG_EXTERNAL_MEMORY
// 强制bss变量进入外部内存。"
#define EXT_RAM_ATTR _SECTION_ATTR_IMPL(".ext_ram.bss", __COUNTER__)
#else
#define EXT_RAM_ATTR
#endif

// 强制数据进入RTC慢速内存。请参阅“docs/deep-sleepstub.rst”
// 标记有此属性的任何变量都将保留其值
// 在深度睡眠/唤醒周期期间。
#define RTC_DATA_ATTR _SECTION_ATTR_IMPL(".rtc.data", __COUNTER__)

// 强制只读数据进入RTC内存。请参阅“docs/deep-sleepstub.rst”
#define RTC_RODATA_ATTR _SECTION_ATTR_IMPL(".rtc.rodata", __COUNTER__)

// 允许将数据放入RTC_SLOW内存。
#define RTC_SLOW_ATTR _SECTION_ATTR_IMPL(".rtc.force_slow", __COUNTER__)

// 允许将数据放入RTC_FAST内存。
#define RTC_FAST_ATTR _SECTION_ATTR_IMPL(".rtc.force_fast", __COUNTER__)

// 强制数据进入noinit部分以避免重新启动后的初始化。
#define __NOINIT_ATTR _SECTION_ATTR_IMPL(".noinit", __COUNTER__)

#if CONFIG_SPIRAM_ALLOW_NOINIT_SEG_EXTERNAL_MEMORY
// 强制数据进入外部内存noinit部分，以避免重新启动后的初始化。
#define EXT_RAM_NOINIT_ATTR _SECTION_ATTR_IMPL(".ext_ram_noinit", __COUNTER__)
#else
// 放置在内部nonit部分
#define EXT_RAM_NOINIT_ATTR __NOINIT_ATTR
#endif

// 强制数据进入.ninit节的RTC慢速内存。
// 标记有此属性的任何变量都将保留其值
// 在重启之后或在深度睡眠/唤醒周期期间。
#define RTC_NOINIT_ATTR  _SECTION_ATTR_IMPL(".rtc_noinit", __COUNTER__)

// 强制代码进入DRAM而不是闪存，并将其映射到核心转储
// 使用dram2而不是dram1以确保不包含此部分
// 通过链接器脚本中的dram1部分
#define COREDUMP_DRAM_ATTR _SECTION_ATTR_IMPL(".dram2.coredump", __COUNTER__)

// 强制数据进入RTC内存并将其映射到coredump
#define COREDUMP_RTC_DATA_ATTR _SECTION_ATTR_IMPL(".rtc.coredump", __COUNTER__)

// 允许将数据放入RTC_FAST内存并将其映射到coredump
#define COREDUMP_RTC_FAST_ATTR _SECTION_ATTR_IMPL(".rtc.fast.coredump", __COUNTER__)

// 强制不内联函数
#define NOINLINE_ATTR __attribute__((noinline))

// 这允许在C中使用enum作为标志++
// 格式：FLAG_ATTR（FLAG_enum_t）
#ifdef __cplusplus

// 此处需要内联以避免链接器中的多重定义错误
#define FLAG_ATTR_IMPL(TYPE, INT_TYPE) \
FORCE_INLINE_ATTR constexpr TYPE operator~ (TYPE a) { return (TYPE)~(INT_TYPE)a; } \
FORCE_INLINE_ATTR constexpr TYPE operator| (TYPE a, TYPE b) { return (TYPE)((INT_TYPE)a | (INT_TYPE)b); } \
FORCE_INLINE_ATTR constexpr TYPE operator& (TYPE a, TYPE b) { return (TYPE)((INT_TYPE)a & (INT_TYPE)b); } \
FORCE_INLINE_ATTR constexpr TYPE operator^ (TYPE a, TYPE b) { return (TYPE)((INT_TYPE)a ^ (INT_TYPE)b); } \
FORCE_INLINE_ATTR constexpr TYPE operator>> (TYPE a, int b) { return (TYPE)((INT_TYPE)a >> b); } \
FORCE_INLINE_ATTR constexpr TYPE operator<< (TYPE a, int b) { return (TYPE)((INT_TYPE)a << b); } \
FORCE_INLINE_ATTR TYPE& operator|=(TYPE& a, TYPE b) { a = a | b; return a; } \
FORCE_INLINE_ATTR TYPE& operator&=(TYPE& a, TYPE b) { a = a & b; return a; } \
FORCE_INLINE_ATTR TYPE& operator^=(TYPE& a, TYPE b) { a = a ^ b; return a; } \
FORCE_INLINE_ATTR TYPE& operator>>=(TYPE& a, int b) { a >>= b; return a; } \
FORCE_INLINE_ATTR TYPE& operator<<=(TYPE& a, int b) { a <<= b; return a; }

#define FLAG_ATTR_U32(TYPE) FLAG_ATTR_IMPL(TYPE, uint32_t)
#define FLAG_ATTR FLAG_ATTR_U32

#else
#define FLAG_ATTR(TYPE)
#endif

// 唯一自定义节的实现
//
// 这可以防止gcc生成“x导致与y的节类型冲突”
// 如果同一源文件中的两个变量具有不同的链接（可能是常量和非常量），但放置在同一自定义节中，则会出现错误
//
// 使用唯一节也意味着--gc节可以删除未使用的
// 具有自定义截面类型集的数据
#define _SECTION_ATTR_IMPL(SECTION, COUNTER) __attribute__((section(SECTION "." _COUNTER_STRINGIFY(COUNTER))))

#define _COUNTER_STRINGIFY(COUNTER) #COUNTER

/* 使用IDF_DEPRECATED属性标记任何不推荐在ESP-IDF自己的源代码中使用的内容，但不推荐外部用户使用。
*/
#ifdef IDF_CI_BUILD
#define IDF_DEPRECATED(REASON) __attribute__((deprecated(REASON)))
#else
#define IDF_DEPRECATED(REASON)
#endif

#ifdef __cplusplus
}
#endif
#endif /* __ESP_ATTR_H__ */

