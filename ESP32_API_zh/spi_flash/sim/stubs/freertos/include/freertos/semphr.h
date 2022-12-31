/*
 * SPDX文件版权文本：2015-2021浓缩咖啡系统（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 *
 * 这是编译ESP-IDF以在主机系统上运行测试时使用的STUB FILE HEADER。通常用于ESP-IDF的头文件具有相同的名称，但位于其他位置。
 */
#pragma once

#if defined(__cplusplus)
extern "C" {
#endif

#define vSemaphoreDelete( xSemaphore )
#define xSemaphoreCreateMutex()                     ((void*)(1))
#define xSemaphoreGive( xSemaphore )
#define xSemaphoreTake( xSemaphore, xBlockTime )    pdTRUE

typedef void* SemaphoreHandle_t;

#if defined(__cplusplus)
}
#endif

