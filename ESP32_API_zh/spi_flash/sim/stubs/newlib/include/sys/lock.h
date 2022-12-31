/*
 * SPDX文件版权文本：2015-2021浓缩咖啡系统（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 *
 * 这是编译ESP-IDF以在主机系统上运行测试时使用的STUB FILE HEADER。通常用于ESP-IDF的头文件具有相同的名称，但位于其他位置。
 */
#pragma once

#include <time.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef int _lock_t;

void _lock_acquire(_lock_t *lock);
void _lock_close(_lock_t *lock);
void _lock_init(_lock_t *lock);
void _lock_release(_lock_t *lock);

#ifdef __cplusplus
}
#endif

