/*
 *  版权所有（c）2016，OpenThread作者。保留所有权利。
 *
 *  在满足以下条件的情况下，允许以源代码和二进制形式重新分发和使用，无论是否进行修改：1.重新分发源代码必须保留上述版权声明、本条件列表和以下免责声明。2.二进制形式的再发行必须在随发行提供的文档和/或其他材料中复制上述版权声明、本条件列表和以下免责声明。3.未经事先书面许可，不得使用版权持有人的姓名或其贡献者的姓名为本软件衍生的产品背书或推广。
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * @addtogroup 平台工具链
 *
 * @brief 该模块通过宏定义工具链抽象层。
 *
 * 用法：
 *
 *    @code
 *
 *    类型定义
 *    OT_TOOL_PACKED_BEGIN
 *    结构
 *    {
 *        字符mField1；
 *        协会
 *        {
 *            字符mField2；
 *            长mField3；
 *        } OT_TOOL_PACKED_FIELD;
 *    }OT_TOOL_PACKED_END PACKED_struct_t；
 *
 *    @endcode
 *
 * @{
 *
 */

#ifndef OPENTHREAD_PLATFORM_TOOLCHAIN_H_
#define OPENTHREAD_PLATFORM_TOOLCHAIN_H_

#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @def OT_MUST_USE_RESULT
 *
 * 编译器特定的指示，当类或枚举是函数的返回值时，必须使用它。
 *
 * @note 这目前仅适用于clang（C++17将其实现为属性[[nodiscard]]）。
 * @note 要抑制“未使用的结果”警告/错误，请使用“-Wno未使用结果”编译器选项。
 *
 */
#if defined(__clang__) && (__clang_major__ >= 4 || (__clang_major__ >= 3 && __clang_minor__ >= 9))
#define OT_MUST_USE_RESULT __attribute__((warn_unused_result))
#else
#define OT_MUST_USE_RESULT
#endif

/**
 * @def OT_TOOL_PACKED_BEGIN
 *
 * 编译器特定的指示，表明类或结构必须是字节压缩的。
 *
 */

/**
 * @def OT_TOOL_PACKED_FIELD
 *
 * 向编译器指示要在字节压缩类或结构中打包的嵌套结构或联合。
 *
 */

/**
 * @def OT_TOOL_PACKED_END
 *
 * 字节压缩类或结构末尾的编译器特定指示。
 *
 */

/**
 * @def OT_TOOL_WEAK
 *
 * 编译器特定的弱符号修饰符。
 *
 */

// =========== TOOLCHAIN SELECTION : START ===========

#if defined(__GNUC__) || defined(__clang__) || defined(__CC_ARM) || defined(__TI_ARM__)

// https://gcc.gnu.org/onlinedocs/gcc/Common-Variable-Attributes.html
// http://www.keil.com/support/man/docs/armcc/armcc_chr1359124973480.htm

#define OT_TOOL_PACKED_BEGIN
#define OT_TOOL_PACKED_FIELD __attribute__((packed))
#define OT_TOOL_PACKED_END __attribute__((packed))
#define OT_TOOL_WEAK __attribute__((weak))

#elif defined(__ICCARM__) || defined(__ICC8051__)

// http://supp.iar.com/FilesPublic/UPDINFO/004916/arm/doc/EWARM_DevelopmentGuide.ENU.pdf

#include "intrinsics.h"

#define OT_TOOL_PACKED_BEGIN __packed
#define OT_TOOL_PACKED_FIELD
#define OT_TOOL_PACKED_END
#define OT_TOOL_WEAK __weak

#elif defined(__SDCC)

// 结构默认打包在sdcc中，因为它主要针对8位MCU。

#define OT_TOOL_PACKED_BEGIN
#define OT_TOOL_PACKED_FIELD
#define OT_TOOL_PACKED_END
#define OT_TOOL_WEAK

#else

#error "Error: No valid Toolchain specified"

// 脱氧剂符号

#define OT_TOOL_PACKED_BEGIN
#define OT_TOOL_PACKED_FIELD
#define OT_TOOL_PACKED_END
#define OT_TOOL_WEAK

#endif

// =========== TOOLCHAIN SELECTION : END ===========

/**
 * @def OT_UNUSED_VARIABLE
 *
 * 抑制特定工具链中未使用的变量警告。
 *
 */

/**
 * @def OT_UNREACHABLE_CODE
 *
 * 抑制特定工具链中的不可访问代码警告。
 *
 */

#if defined(__ICCARM__)

#include <stddef.h>

#define OT_UNUSED_VARIABLE(VARIABLE) \
    do                               \
    {                                \
        if (&VARIABLE == NULL)       \
        {                            \
        }                            \
    } while (false)

#define OT_UNREACHABLE_CODE(CODE)                                                                    \
    _Pragma("diag_suppress=Pe111") _Pragma("diag_suppress=Pe128") CODE _Pragma("diag_default=Pe111") \
        _Pragma("diag_default=Pe128")

#elif defined(__CC_ARM)

#include <stddef.h>

#define OT_UNUSED_VARIABLE(VARIABLE) \
    do                               \
    {                                \
        if (&VARIABLE == NULL)       \
        {                            \
        }                            \
    } while (false)

#define OT_UNREACHABLE_CODE(CODE) CODE

#elif defined(__TI_ARM__)

#include <stddef.h>

#define OT_UNUSED_VARIABLE(VARIABLE) \
    do                               \
    {                                \
        if (&VARIABLE == NULL)       \
        {                            \
        }                            \
    } while (false)

/*
 * #112-D语句不可访问#129-D循环不可访问
 */
#define OT_UNREACHABLE_CODE(CODE) \
    _Pragma("diag_push") _Pragma("diag_suppress 112") _Pragma("diag_suppress 129") CODE _Pragma("diag_pop")

#else

#define OT_UNUSED_VARIABLE(VARIABLE) \
    do                               \
    {                                \
        (void)(VARIABLE);            \
    } while (false)

#define OT_UNREACHABLE_CODE(CODE) CODE

#endif

/*
 * Keil和IAR编译器不提供C++的类型限制。
 */
#ifdef __cplusplus
#if defined(__CC_ARM) || defined(__ICCARM__)

#ifndef UINT8_MAX
#define UINT8_MAX 0xff
#endif

#ifndef UINT16_MAX
#define UINT16_MAX 0xffff
#endif

#endif
#endif

#ifdef __APPLE__
#define OT_APPLE_IGNORE_GNU_FOLDING_CONSTANT(...)                                               \
    _Pragma("GCC diagnostic push") _Pragma("GCC diagnostic ignored \"-Wgnu-folding-constant\"") \
        __VA_ARGS__ _Pragma("GCC diagnostic pop")
#else
#define OT_APPLE_IGNORE_GNU_FOLDING_CONSTANT(...) __VA_ARGS__
#endif

/**
 * @def OT_FALL_THROUGH
 *
 * 抑制特定编译器中的穿越警告。
 *
 */
#if defined(__cplusplus) && (__cplusplus >= 201703L)
#define OT_FALL_THROUGH [[fallthrough]]
#elif defined(__clang__)
#define OT_FALL_THROUGH [[clang::fallthrough]]
#elif defined(__GNUC__) && (__GNUC__ >= 7)
#define OT_FALL_THROUGH __attribute__((fallthrough))
#else
#define OT_FALL_THROUGH \
    do                  \
    {                   \
    } while (false) /* 通过，通过*/
#endif

/**
 * @}
 *
 */

#ifdef __cplusplus
} // 外部“C”
#endif

#endif // OPENTHREAD_PLATFORM_TOOLCHAIN_H_

