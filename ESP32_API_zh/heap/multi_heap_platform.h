/*
 * SPDX文件版权文本：2015-2021浓缩咖啡系统（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */
#pragma once

#ifdef MULTI_HEAP_FREERTOS

#include "freertos/FreeRTOS.h"

#include "sdkconfig.h"
#include "esp_rom_sys.h"
#if CONFIG_IDF_TARGET_ESP32
#include "esp32/rom/ets_sys.h" // 将在idf v5.0中删除
#elif CONFIG_IDF_TARGET_ESP32S2
#include "esp32s2/rom/ets_sys.h"
#endif
#include <assert.h>

typedef portMUX_TYPE multi_heap_lock_t;

/* 因为malloc/free可以在ISR上下文中发生，所以我们需要在这里使用portmux自旋锁，而不是RTOS互斥锁*/
#define MULTI_HEAP_LOCK(PLOCK) do {                         \
        if((PLOCK) != NULL) {                               \
            portENTER_CRITICAL((PLOCK));                    \
        }                                                   \
    } while(0)


#define MULTI_HEAP_UNLOCK(PLOCK) do {                       \
        if ((PLOCK) != NULL) {                              \
            portEXIT_CRITICAL((PLOCK));                     \
        }                                                   \
    } while(0)

#define MULTI_HEAP_LOCK_INIT(PLOCK) do {                    \
        portMUX_INITIALIZE((PLOCK));                        \
    } while(0)

#define MULTI_HEAP_LOCK_STATIC_INITIALIZER     portMUX_INITIALIZER_UNLOCKED

/* 在portmux关键部分中使用stdi/o不安全，可能会死锁，因此我们使用ROM等效函数。*/

#define MULTI_HEAP_PRINTF esp_rom_printf
#define MULTI_HEAP_STDERR_PRINTF(MSG, ...) esp_rom_printf(MSG, __VA_ARGS__)

inline static void multi_heap_assert(bool condition, const char *format, int line, intptr_t address)
{
    /* 在这里不能使用libc assert（），因为它调用printf（），这会导致另一个malloc（）用于新的lib锁。

       此外，能够打印检测到损坏的内存地址也是很有用的。
    */
#ifndef NDEBUG
    if(!condition) {
#ifndef CONFIG_COMPILER_OPTIMIZATION_ASSERTIONS_SILENT
        esp_rom_printf(format, line, address);
#endif  // CONFIG_COMPILER_OPTIMIZATION_ASSERTIONS_SILENT
        abort();
    }
#else // NDEBUG
    (void) condition;
#endif // NDEBUG
}

#define MULTI_HEAP_ASSERT(CONDITION, ADDRESS) \
    multi_heap_assert((CONDITION), "CORRUPT HEAP: multi_heap.c:%d detected at 0x%08x\n", \
                      __LINE__, (intptr_t)(ADDRESS))

#ifdef CONFIG_HEAP_TASK_TRACKING
#include <freertos/task.h>
#define MULTI_HEAP_BLOCK_OWNER TaskHandle_t task;
#define MULTI_HEAP_SET_BLOCK_OWNER(HEAD) (HEAD)->task = xTaskGetCurrentTaskHandle()
#define MULTI_HEAP_GET_BLOCK_OWNER(HEAD) ((HEAD)->task)
#else
#define MULTI_HEAP_BLOCK_OWNER
#define MULTI_HEAP_SET_BLOCK_OWNER(HEAD)
#define MULTI_HEAP_GET_BLOCK_OWNER(HEAD) (NULL)
#endif

#else // MULTI_HEAP_FREERTOS

#include <assert.h>

#define MULTI_HEAP_PRINTF printf
#define MULTI_HEAP_STDERR_PRINTF(MSG, ...) fprintf(stderr, MSG, __VA_ARGS__)
#define MULTI_HEAP_LOCK(PLOCK)  (void) (PLOCK)
#define MULTI_HEAP_UNLOCK(PLOCK)  (void) (PLOCK)
#define MULTI_HEAP_LOCK_INIT(PLOCK)  (void) (PLOCK)
#define MULTI_HEAP_LOCK_STATIC_INITIALIZER  0

#define MULTI_HEAP_ASSERT(CONDITION, ADDRESS) assert((CONDITION) && "Heap corrupt")

#define MULTI_HEAP_BLOCK_OWNER
#define MULTI_HEAP_SET_BLOCK_OWNER(HEAD)
#define MULTI_HEAP_GET_BLOCK_OWNER(HEAD) (NULL)

#endif // MULTI_HEAP_FREERTOS

