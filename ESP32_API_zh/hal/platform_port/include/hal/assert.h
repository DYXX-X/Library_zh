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

#include "sdkconfig.h"

#ifdef __cplusplus
extern "C" {
#endif

extern void __assert_func(const char *file, int line, const char *func, const char *expr);
extern void abort(void);

#ifndef __ASSERT_FUNC
#ifdef __ASSERT_FUNCTION
#define __ASSERT_FUNC __ASSERT_FUNCTION
#else
#define __ASSERT_FUNC "??"
#endif
#endif

#if CONFIG_HAL_DEFAULT_ASSERTION_LEVEL == 1 // 不说话的
#define HAL_ASSERT(__e) (__builtin_expect(!!(__e), 1) ? (void)0 : abort())
#elif CONFIG_HAL_DEFAULT_ASSERTION_LEVEL == 2 // 完全断言
#define HAL_ASSERT(__e) (__builtin_expect(!!(__e), 1) ? (void)0 : __assert_func(__FILE__, __LINE__, __ASSERT_FUNC, #__e))
#else // 无断言
#define HAL_ASSERT(__e) ((void)(__e))
#endif

#ifdef __cplusplus
}
#endif

