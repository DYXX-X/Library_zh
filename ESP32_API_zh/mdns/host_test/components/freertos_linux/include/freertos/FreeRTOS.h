// 版权所有2021 Espressif Systems（Shanghai）PTE LTD
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

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>

#define portTICK_PERIOD_MS 1
#define portMAX_DELAY ( TickType_t ) 0xffffffffUL

typedef void * xSemaphoreHandle;
typedef void * SemaphoreHandle_t;
typedef void * xQueueHandle;
typedef void * QueueHandle_t;
typedef void * TaskHandle_t;
typedef uint32_t TickType_t;
typedef uint32_t portTickType;

typedef void (*TaskFunction_t)( void * );
typedef unsigned int	UBaseType_t;
typedef int 			BaseType_t;

#define pdFALSE			( ( BaseType_t ) 0 )
#define pdTRUE			( ( BaseType_t ) 1 )

#define pdPASS			( pdTRUE )
#define pdFAIL			( pdFALSE )

#define portTICK_RATE_MS portTICK_PERIOD_MS
#define pdMS_TO_TICKS(tick)    (tick)

uint32_t esp_get_free_heap_size(void);
uint32_t esp_random(void);

