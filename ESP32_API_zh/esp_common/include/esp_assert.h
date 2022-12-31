// 版权所有2015-2017 Espressif Systems（上海）私人有限公司
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
#ifndef __ESP_ASSERT_H__
#define __ESP_ASSERT_H__

#include "assert.h"

/* 如果可能，在编译时断言，否则在运行时断言*/
#ifndef __cplusplus
/* __builtin_choose_expr（）仅在C语言中，使其更加简洁*/
#define TRY_STATIC_ASSERT(CONDITION, MSG) do {                                                              \
            _Static_assert(__builtin_choose_expr(__builtin_constant_p(CONDITION), (CONDITION), 1), #MSG);   \
            assert(#MSG && (CONDITION));                                                                    \
        } while(0)
#else
/* 对于C++，使用__attribute__（（error））-几乎与_Static_assert一样有效*/
#define TRY_STATIC_ASSERT(CONDITION, MSG) do {                                                              \
            if (__builtin_constant_p(CONDITION) && !(CONDITION)) {          \
                extern __attribute__((error(#MSG))) void failed_compile_time_assert(void);      \
                failed_compile_time_assert();                                                   \
            }                                                                                   \
            assert(#MSG && (CONDITION));                                                                    \
        } while(0)
#endif /* __cplusplus公司*/

#endif /* __ESP_ASSERT_H__ */

