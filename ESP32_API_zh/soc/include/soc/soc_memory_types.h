// 版权所有2010-2016 Espressif Systems（上海）私人有限公司
//
// 根据Apache许可证2.0版（“许可证”）获得许可；
// 除非符合许可证，否则不得使用此文件。
// 您可以在以下地址获取许可证副本：

//     http://www.apache.org/licenses/LICENSE-2.0
//
// 除非适用法律要求或书面同意，软件
// 根据许可证分发的内容是按“原样”分发的，
// 无任何明示或暗示的保证或条件。
// 有关管理权限和
// 许可证下的限制。

#pragma once
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#include "soc/soc.h"
#include "soc/soc_caps.h"
#include "sdkconfig.h"
#include "esp_attr.h"

#ifdef __cplusplus
extern "C" {
#endif

inline static bool IRAM_ATTR esp_ptr_dma_capable(const void *p)
{
    return (intptr_t)p >= SOC_DMA_LOW && (intptr_t)p < SOC_DMA_HIGH;
}

inline static bool IRAM_ATTR esp_ptr_dma_ext_capable(const void *p)
{
#ifdef SOC_PSRAM_DMA_CAPABLE
    return (intptr_t)p >= SOC_DMA_EXT_LOW && (intptr_t)p < SOC_DMA_EXT_HIGH;
#else
    return false;
#endif
}

inline static bool IRAM_ATTR esp_ptr_word_aligned(const void *p)
{
    return ((intptr_t)p) % 4 == 0;
}

inline static bool IRAM_ATTR esp_ptr_executable(const void *p)
{
    intptr_t ip = (intptr_t) p;
    return (ip >= SOC_IROM_LOW && ip < SOC_IROM_HIGH)
        || (ip >= SOC_IRAM_LOW && ip < SOC_IRAM_HIGH)
        || (ip >= SOC_IROM_MASK_LOW && ip < SOC_IROM_MASK_HIGH)
#if defined(SOC_CACHE_APP_LOW) && defined(CONFIG_FREERTOS_UNICORE)
        || (ip >= SOC_CACHE_APP_LOW && ip < SOC_CACHE_APP_HIGH)
#endif
        || (ip >= SOC_RTC_IRAM_LOW && ip < SOC_RTC_IRAM_HIGH);
}

inline static bool IRAM_ATTR esp_ptr_byte_accessible(const void *p)
{
    intptr_t ip = (intptr_t) p;
    bool r;
    r = (ip >= SOC_BYTE_ACCESSIBLE_LOW && ip < SOC_BYTE_ACCESSIBLE_HIGH);
#if CONFIG_ESP_SYSTEM_ALLOW_RTC_FAST_MEM_AS_HEAP
    /* 对于ESP32情况，RTC快速内存仅可由PRO cpu访问，因此对于单核配置（将其添加到系统堆中），需要进行额外检查*/
    r |= (ip >= SOC_RTC_DRAM_LOW && ip < SOC_RTC_DRAM_HIGH);
#endif
#if CONFIG_SPIRAM
#if CONFIG_SPIRAM_SIZE != -1 // 固定大小，可以更精确
    r |= (ip >= SOC_EXTRAM_DATA_LOW && ip < (SOC_EXTRAM_DATA_LOW + CONFIG_SPIRAM_SIZE));
#else
    r |= (ip >= SOC_EXTRAM_DATA_LOW && ip < (SOC_EXTRAM_DATA_HIGH));
#endif
#endif
    return r;
}

inline static bool IRAM_ATTR esp_ptr_internal(const void *p) {
    bool r;
    r = ((intptr_t)p >= SOC_MEM_INTERNAL_LOW && (intptr_t)p < SOC_MEM_INTERNAL_HIGH);
    r |= ((intptr_t)p >= SOC_RTC_DATA_LOW && (intptr_t)p < SOC_RTC_DATA_HIGH);
#if CONFIG_ESP_SYSTEM_ALLOW_RTC_FAST_MEM_AS_HEAP
    /* 对于ESP32情况，RTC快速内存仅可由PRO cpu访问，因此对于单核配置（将其添加到系统堆中），需要进行额外检查*/
    r |= ((intptr_t)p >= SOC_RTC_DRAM_LOW && (intptr_t)p < SOC_RTC_DRAM_HIGH);
#endif
    return r;
}


inline static bool IRAM_ATTR esp_ptr_external_ram(const void *p) {
#if SOC_SPIRAM_SUPPORTED
    return ((intptr_t)p >= SOC_EXTRAM_DATA_LOW && (intptr_t)p < SOC_EXTRAM_DATA_HIGH);
#else
    return false; // SoC没有外部RAM
#endif
}

inline static bool IRAM_ATTR esp_ptr_in_iram(const void *p) {
#if CONFIG_IDF_TARGET_ESP32 && CONFIG_FREERTOS_UNICORE
    return ((intptr_t)p >= SOC_CACHE_APP_LOW && (intptr_t)p < SOC_IRAM_HIGH);
#else
    return ((intptr_t)p >= SOC_IRAM_LOW && (intptr_t)p < SOC_IRAM_HIGH);
#endif
}

inline static bool IRAM_ATTR esp_ptr_in_drom(const void *p) {
    return ((intptr_t)p >= SOC_DROM_LOW && (intptr_t)p < SOC_DROM_HIGH);
}

inline static bool IRAM_ATTR esp_ptr_in_dram(const void *p) {
    return ((intptr_t)p >= SOC_DRAM_LOW && (intptr_t)p < SOC_DRAM_HIGH);
}

inline static bool IRAM_ATTR esp_ptr_in_diram_dram(const void *p) {
    return ((intptr_t)p >= SOC_DIRAM_DRAM_LOW && (intptr_t)p < SOC_DIRAM_DRAM_HIGH);
}

inline static bool IRAM_ATTR esp_ptr_in_diram_iram(const void *p) {
    return ((intptr_t)p >= SOC_DIRAM_IRAM_LOW && (intptr_t)p < SOC_DIRAM_IRAM_HIGH);
}

inline static bool IRAM_ATTR esp_ptr_in_rtc_iram_fast(const void *p) {
    return ((intptr_t)p >= SOC_RTC_IRAM_LOW && (intptr_t)p < SOC_RTC_IRAM_HIGH);
}

inline static bool IRAM_ATTR esp_ptr_in_rtc_dram_fast(const void *p) {
    return ((intptr_t)p >= SOC_RTC_DRAM_LOW && (intptr_t)p < SOC_RTC_DRAM_HIGH);
}

inline static bool IRAM_ATTR esp_ptr_in_rtc_slow(const void *p) {
    return ((intptr_t)p >= SOC_RTC_DATA_LOW && (intptr_t)p < SOC_RTC_DATA_HIGH);
}

/* 将D/IRAM DRAM指针转换为IRAM中的等效字地址

   -地址必须对齐
   -地址必须通过esp_ptr_in_dram_dram（）测试，否则结果将是无效指针
*/
inline static void * IRAM_ATTR esp_ptr_diram_dram_to_iram(const void *p) {
#if SOC_DIRAM_INVERTED
    return (void *) ( SOC_DIRAM_IRAM_LOW + (SOC_DIRAM_DRAM_HIGH - (intptr_t)p) - 4);
#else
    return (void *) ( SOC_DIRAM_IRAM_LOW + ((intptr_t)p - SOC_DIRAM_DRAM_LOW) );
#endif
}

/* 将D/IRAM IRAM指针转换为DRAM中的等效字地址

   -地址必须对齐
   -地址必须通过esp_ptr_in_diram_iram（）测试，否则结果将是无效指针
*/
inline static void * IRAM_ATTR esp_ptr_diram_iram_to_dram(const void *p) {
#if SOC_DIRAM_INVERTED
    return (void *) ( SOC_DIRAM_DRAM_LOW + (SOC_DIRAM_IRAM_HIGH - (intptr_t)p) - 4);
#else
    return (void *) ( SOC_DIRAM_DRAM_LOW + ((intptr_t)p - SOC_DIRAM_IRAM_LOW) );
#endif
}

inline static bool IRAM_ATTR esp_stack_ptr_in_dram(uint32_t sp)
{
    //检查堆栈指针是否位于SOC_DRAM_LOW和SOC_DRAM_HIGH之间，并且16字节对齐。
    return !(sp < SOC_DRAM_LOW + 0x10 || sp > SOC_DRAM_HIGH - 0x10 || ((sp & 0xF) != 0));
}

#if CONFIG_SPIRAM_ALLOW_STACK_EXTERNAL_MEMORY
inline static bool IRAM_ATTR esp_stack_ptr_in_extram(uint32_t sp)
{
    //检查堆栈指针是否位于SOC_EXTRAM_DATA_LOW和SOC_EXTRAM _DATA_HIGH之间，并且16字节对齐。
    return !(sp < SOC_EXTRAM_DATA_LOW + 0x10 || sp > SOC_EXTRAM_DATA_HIGH - 0x10 || ((sp & 0xF) != 0));
}
#endif

inline static bool IRAM_ATTR esp_stack_ptr_is_sane(uint32_t sp)
{
    return esp_stack_ptr_in_dram(sp)
#if CONFIG_SPIRAM_ALLOW_STACK_EXTERNAL_MEMORY
        || esp_stack_ptr_in_extram(sp)
#endif
#if CONFIG_ESP_SYSTEM_ALLOW_RTC_FAST_MEM_AS_HEAP
        || esp_ptr_in_rtc_dram_fast((void*) sp)
#endif
        ;
}

#ifdef __cplusplus
}
#endif

