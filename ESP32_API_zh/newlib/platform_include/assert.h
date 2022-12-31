// 版权所有2017 Espressif Systems（上海）私人有限公司
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


/* 这个头文件包装了newlib自己未修改的断言。h，并增加了对静默断言失败的支持。
*/
#pragma once
#include <sdkconfig.h>
#include <stdlib.h>
#include <stdint.h>

#include_next <assert.h>

/* 将libc提供的assert的一部分移动到此处允许调整assert宏以使用__builtin_expect（）并减少“assert OK”代码路径中的跳转
 *
 * 注意：使用__builtin_expect（）not likely（）避免在可能包含此标准头的非IDF代码的命名空间中定义可能的宏。
 */
#undef assert

/* __FILENAME__指向文件名而不是路径+文件名，例如__file__指向“/apps/test.c”，其中__FILENAME__指“test.c”
 */
#define __FILENAME__ (__builtin_strrchr( "/" __FILE__, '/') + 1)

#if defined(NDEBUG)

#define assert(__e) ((void)(__e))

#elif CONFIG_COMPILER_OPTIMIZATION_ASSERTIONS_SILENT

#define assert(__e) (__builtin_expect(!!(__e), 1) ? (void)0 : __assert_func(NULL, 0, NULL, NULL))

#else // !CONFIG_COMPILER_OPTIMIZATION_ASSERTIONS_SILENT

#define assert(__e) (__builtin_expect(!!(__e), 1) ? (void)0 : __assert_func (__FILENAME__, __LINE__, \
                                                                             __ASSERT_FUNC, #__e))
#endif

