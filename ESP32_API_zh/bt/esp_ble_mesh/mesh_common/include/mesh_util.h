/*
 * SPDX文件版权文本：2011-2014 Wind River Systems，Inc。
 *
 * SPDX许可证标识符：Apache-2.0
 */

/**
 * @file
 * @brief 其他实用程序
 *
 * 内核和应用程序代码可使用的其他实用程序。
 */

#ifndef _BLE_MESH_UTIL_H_
#define _BLE_MESH_UTIL_H_

#include <stddef.h>
#include "esp_bit_defs.h"
#include "mesh_types.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Helper将int作为指针传递，反之亦然。这些可用于32位架构：
 */
#ifndef POINTER_TO_UINT
#define POINTER_TO_UINT(x) ((uint32_t)  (x))
#endif
#ifndef UINT_TO_POINTER
#define UINT_TO_POINTER(x) ((void *) (x))
#endif
#ifndef POINTER_TO_INT
#define POINTER_TO_INT(x)  ((int32_t)  (x))
#endif
#ifndef INT_TO_POINTER
#define INT_TO_POINTER(x)  ((void *) (x))
#endif

/* 如果cond为true ish，则求值为0；否则编译错误*/
#ifndef ZERO_OR_COMPILE_ERROR
#define ZERO_OR_COMPILE_ERROR(cond) ((int) sizeof(char[1 - 2 * !(cond)]) - 1)
#endif

/* 如果数组是数组，则求值为0；如果不是数组，则编译错误（例如指针）
 */
#ifndef IS_ARRAY
#define IS_ARRAY(array) \
        ZERO_OR_COMPILE_ERROR( \
        !__builtin_types_compatible_p(__typeof__(array), \
            __typeof__(&(array)[0])))
#endif

/* 计算数组中的元素数；如果不是数组（例如指针），则编译错误
 */
#ifndef ARRAY_SIZE
#define ARRAY_SIZE(array) (sizeof(array) / sizeof((array)[0]))
#endif

/* 如果ptr是数组的一部分，则求值为1，否则为0；如果“array”参数不是数组（例如“ptr”和“array），则编译错误
 */
#ifndef PART_OF_ARRAY
#define PART_OF_ARRAY(array, ptr) \
        ((ptr) && ((ptr) >= &array[0] && (ptr) < &array[ARRAY_SIZE(array)]))
#endif

#ifndef CONTAINER_OF
#define CONTAINER_OF(ptr, type, field) \
        ((type *)(((char *)(ptr)) - offsetof(type, field)))
#endif

/* 将“x”向上/向下舍入到“align”的下一个倍数（必须是2的幂）*/
#ifndef ROUND_UP
#define ROUND_UP(x, align) \
        (((unsigned long)(x) + ((unsigned long)align - 1)) & \
        ~((unsigned long)align - 1))
#endif

#ifndef ROUND_DOWN
#define ROUND_DOWN(x, align) ((unsigned long)(x) & ~((unsigned long)align - 1))
#endif

/* 向上/向下舍入到下一个单词边界*/
#ifndef WB_UP
#define WB_UP(x) ROUND_UP(x, sizeof(void *))
#endif

#ifndef WB_DN
#define WB_DN(x) ROUND_DOWN(x, sizeof(void *))
#endif

#ifndef ceiling_fraction
#define ceiling_fraction(numerator, divider) \
        (((numerator) + ((divider) - 1)) / (divider))
#endif

#ifndef CHECKIF
#define CHECKIF(expr)   if (expr)
#endif

/** @brief 返回提供的两个表达式的较大值。
 *
 * @note 参数求值两次。请参见Z_MAX，仅用于GCC，单个评估版本。
 */
#ifndef MAX
#define MAX(a, b) (((a) > (b)) ? (a) : (b))
#endif

/** @brief 返回提供的两个表达式中较小的值。
 *
 * @note 参数求值两次。参见Z_MIN，仅用于GCC，单个评估版本。
 */
#ifndef MIN
#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#endif

#ifndef BIT
#define BIT(n)      (1UL << (n))
#endif

#ifndef BIT_MASK
#define BIT_MASK(n) (BIT(n) - 1)
#endif

/**
 * @brief 检查编译器可见表达式中的宏定义
 *
 * 这种技巧在Linux中被首创为config_enabled（）宏。疯狂的效果是取一个宏值，该宏值可以定义为“1”（例如CONFIG_MYFEATURE），也可以根本不定义，并将其转换为可以在“运行时”使用的文字表达式。也就是说，它的工作方式与“defined（CONFIG_MYFEATURE）”类似，只是它是一个扩展，可以存在于标准表达式中，并且可以被编译器和优化器看到。因此，ifdef的用法可以替换为更简洁的表达式，如：
 *
 *     如果（IS_ENABLED（CONFIG_MYFEATURE））MYFEATURE_enable（）；
 *
 * 内部首先，为了扩展任何现有宏，我们需要宏值在下一个宏中的扩展时为文本“1”，而不是“（1）”等。标准递归扩展不起作用。
 */
#define IS_ENABLED(config_macro) Z_IS_ENABLED1(config_macro)

/* 现在，坚持使用“_XXXX”前缀，如果config_macro为“1”，则现在为“_XXXX1”，如果未定义，则仅为“_XXXX”。已启用：Z_IS_ENABLED2（_XXXX1）已禁用Z_IS_ENABLED2（_XXXX）
 */
#define Z_IS_ENABLED1(config_macro) Z_IS_ENABLED2(_XXXX##config_macro)

/* 这是核心技巧，我们将“_XXXX1”映射到“_YYYY”（即一个带逗号的字符串），因此只有在值定义为“1”ENABLED:_YYYY，<---注意逗号！禁用：_XXXX
 */
#define _XXXX1 _YYYY,

/* 然后我们附加一个额外的参数，以欺骗gcc预处理器将其接受为varargs宏。arg1 arg2 arg3已启用：Z_IS_ENABLED3（_YYYY，1，0）已禁用Z_IS_ENABLED3（_XXXX 1，0
 */
#define Z_IS_ENABLED2(one_or_two_args) Z_IS_ENABLED3(one_or_two_args true, false)

/* 因此，在将值定义为1的情况下，我们的第二个参数现在变为1，如果不是，则变为0：
 */
#define Z_IS_ENABLED3(ignore_this, val, ...) val

const char *bt_hex(const void *buf, size_t len);

void mem_rcopy(uint8_t *dst, uint8_t const *src, uint16_t len);

#ifdef __cplusplus
}
#endif

#endif /* _BLE_MESH_UTIL_H_ */

