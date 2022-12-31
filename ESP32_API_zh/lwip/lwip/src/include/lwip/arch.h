/**
 * @file 支持不同的处理器和编译器体系结构
 */

/*
 * 版权所有（c）2001-2004瑞典计算机科学研究所。保留所有权利。
 *
 * 在满足以下条件的情况下，允许以源代码和二进制形式重新分发和使用，无论是否进行修改：
 *
 * 1.源代码的重新分发必须保留上述版权声明、本条件列表和以下免责声明。2.二进制形式的再发行必须在随发行提供的文档和/或其他材料中复制上述版权声明、本条件列表和以下免责声明。3.未经事先书面许可，不得使用作者的姓名为本软件衍生的产品背书或推广。
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * 此文件是lwIP TCP/IP堆栈的一部分。
 *
 * 作者：Adam Dunkels<adam@sics.se>
 *
 */
#ifndef LWIP_HDR_ARCH_H
#define LWIP_HDR_ARCH_H

#ifndef LITTLE_ENDIAN
#define LITTLE_ENDIAN 1234
#endif

#ifndef BIG_ENDIAN
#define BIG_ENDIAN 4321
#endif

#include "arch/cc.h"

/**
 * @defgroup compiler_abstraction编译器/平台抽象
 * @ingroup sys_layer与此节相关的所有定义都不能放在lwipopts中。h、 但在拱/cc中。啊！如果编译器不提供memset（），则该文件必须包含它的定义，或包含定义它的文件。无法在lwipopts中定义这些选项。h，因为它们不是lwIP本身的选项，而是系统的lwIP端口的选项@{
 */

/** 定义系统的字节顺序。需要将网络数据转换为主机字节顺序。允许值：LITTLE_ENDIAN和BIG_ENDIAN
 */
#ifndef BYTE_ORDER
#define BYTE_ORDER LITTLE_ENDIAN
#endif

/**定义系统的随机数生成器功能*/
#ifdef __DOXYGEN__
#define LWIP_RAND() ((u32_t)rand())
#endif

/** 平台特定诊断输出。\请注意，默认实现会引入printf，这反过来可能会引入大量标准库代码。在资源受限的系统中，这应该被定义为资源消耗更少的东西。
 */
#ifndef LWIP_PLATFORM_DIAG
#define LWIP_PLATFORM_DIAG(x) do {printf x;} while(0)
#include <stdio.h>
#include <stdlib.h>
#endif

/** 特定于平台的断言处理。\请注意，默认实现会引入printf、fflush和abort，这反过来可能会引入大量标准库代码。在资源受限的系统中，这应该被定义为资源消耗更少的东西。
 */
#ifndef LWIP_PLATFORM_ASSERT
#define LWIP_PLATFORM_ASSERT(x) do {printf("Assertion \"%s\" failed at line %d in %s\n", \
                                     x, __LINE__, __FILE__); fflush(NULL); abort();} while(0)
#include <stdio.h>
#include <stdlib.h>
#endif

/** 在arch/cc中将其定义为1。如果不想包含stddef，请使用端口的h。h标头以获取size_t。在这种情况下，您需要自己键入def size_t。
 */
#ifndef LWIP_NO_STDDEF_H
#define LWIP_NO_STDDEF_H 0
#endif

#if !LWIP_NO_STDDEF_H
#include <stddef.h> /* 对于size_t*/
#endif

/** 在arch/cc中将其定义为1。如果编译器不提供stdint，则返回端口的h。h标题。您需要typedef lwip/arch中列出的泛型类型。在这种情况下（u8_t、u16_t…）。
 */
#ifndef LWIP_NO_STDINT_H
#define LWIP_NO_STDINT_H 0
#endif

/* 定义lwIP中使用的泛型类型*/
#if !LWIP_NO_STDINT_H
#include <stdint.h>
/* 标准整数。h是C99，它还应支持64位整数*/
#if !defined(LWIP_HAVE_INT64) && defined(UINT64_MAX)
#define LWIP_HAVE_INT64 1
#endif
typedef uint8_t   u8_t;
typedef int8_t    s8_t;
typedef uint16_t  u16_t;
typedef int16_t   s16_t;
typedef uint32_t  u32_t;
typedef int32_t   s32_t;
#if LWIP_HAVE_INT64
typedef uint64_t  u64_t;
typedef int64_t   s64_t;
#endif
typedef uintptr_t mem_ptr_t;
#endif

/** 在arch/cc中将其定义为1。如果编译器不提供int类型，则返回端口的h。h标题。您需要定义lwip/arch中列出的格式字符串。在这种情况下（X8_F、U16_F…）。
 */
#ifndef LWIP_NO_INTTYPES_H
#define LWIP_NO_INTTYPES_H 0
#endif

/* 为这些lwIP类型定义（sn）printf格式器*/
#if !LWIP_NO_INTTYPES_H
#include <inttypes.h>
#ifndef X8_F
#define X8_F  "02" PRIx8
#endif
#ifndef U16_F
#define U16_F PRIu16
#endif
#ifndef S16_F
#define S16_F PRId16
#endif
#ifndef X16_F
#define X16_F PRIx16
#endif
#ifndef U32_F
#define U32_F PRIu32
#endif
#ifndef S32_F
#define S32_F PRId32
#endif
#ifndef X32_F
#define X32_F PRIx32
#endif
#ifndef SZT_F
#define SZT_F PRIuPTR
#endif
#endif

/** 在arch/cc中将其定义为1。如果编译器未提供限制，则返回端口的h。h标题。在这种情况下，您需要自己定义类型限制（例如INT_MAX、SSIZE_MAX）。
 */
#ifndef LWIP_NO_LIMITS_H
#define LWIP_NO_LIMITS_H 0
#endif

/* 包括限制。嗯？*/
#if !LWIP_NO_LIMITS_H
#include <limits.h>
#endif

/* 我们需要定义ssize_t吗？这是一个兼容性黑客：不幸的是，这种类型在某些系统上似乎不可用（即使sys/types或unistd.h可用）。这样，如果未定义SSIZE_MAX，我们将其定义为“int”。
 */
#ifdef SSIZE_MAX
/* 如果定义了SSIZE_MAX，则为unistd。h也应提供类型*/
#ifndef LWIP_NO_UNISTD_H
#define LWIP_NO_UNISTD_H 0
#endif
#if !LWIP_NO_UNISTD_H
#include <unistd.h>
#endif
#else /* SSIZE_MAX */
typedef int ssize_t;
#define SSIZE_MAX INT_MAX
#endif /* SSIZE_MAX */

/* lwip代码中需要的一些最大值*/
#define LWIP_UINT32_MAX 0xffffffff

/** 在arch/cc中将其定义为1。如果编译器不提供ctype，则返回端口的h。h标题。如果ctype。h可用时，将几个字符函数映射到适当的函数（lwip_isloter、lwip_isdigit…），如果不可用，则提供私有实现。
 */
#ifndef LWIP_NO_CTYPE_H
#define LWIP_NO_CTYPE_H 0
#endif

#if LWIP_NO_CTYPE_H
#define lwip_in_range(c, lo, up)  ((u8_t)(c) >= (lo) && (u8_t)(c) <= (up))
#define lwip_isdigit(c)           lwip_in_range((c), '0', '9')
#define lwip_isxdigit(c)          (lwip_isdigit(c) || lwip_in_range((c), 'a', 'f') || lwip_in_range((c), 'A', 'F'))
#define lwip_islower(c)           lwip_in_range((c), 'a', 'z')
#define lwip_isspace(c)           ((c) == ' ' || (c) == '\f' || (c) == '\n' || (c) == '\r' || (c) == '\t' || (c) == '\v')
#define lwip_isupper(c)           lwip_in_range((c), 'A', 'Z')
#define lwip_tolower(c)           (lwip_isupper(c) ? (c) - 'A' + 'a' : c)
#define lwip_toupper(c)           (lwip_islower(c) ? (c) - 'a' + 'A' : c)
#else
#include <ctype.h>
#define lwip_isdigit(c)           isdigit((unsigned char)(c))
#define lwip_isxdigit(c)          isxdigit((unsigned char)(c))
#define lwip_islower(c)           islower((unsigned char)(c))
#define lwip_isspace(c)           isspace((unsigned char)(c))
#define lwip_isupper(c)           isupper((unsigned char)(c))
#define lwip_tolower(c)           tolower((unsigned char)(c))
#define lwip_toupper(c)           toupper((unsigned char)(c))
#endif

/**C++const_cast＜target_type＞（val）等效于从值中删除常量（GCC-Wcast qual）*/
#ifndef LWIP_CONST_CAST
#define LWIP_CONST_CAST(target_type, val) ((target_type)((ptrdiff_t)val))
#endif

/**消除对齐转换警告（GCC-Wcast align）*/
#ifndef LWIP_ALIGNMENT_CAST
#define LWIP_ALIGNMENT_CAST(target_type, val) LWIP_CONST_CAST(target_type, val)
#endif

/** 消除与指针到数字的转换相关的警告，反之亦然，例如“从'u8_t'转换为更大大小的'void'”
 */
#ifndef LWIP_PTR_NUMERIC_CAST
#define LWIP_PTR_NUMERIC_CAST(target_type, val) LWIP_CONST_CAST(target_type, val)
#endif

/**通过执行显式转换，避免与隐式转换打包属性相关的警告/错误*/
#ifndef LWIP_PACKED_CAST
#define LWIP_PACKED_CAST(target_type, val) LWIP_CONST_CAST(target_type, val)
#endif

/** 分配指定大小的内存缓冲区，该缓冲区的大小足以使用LWIP_MEM_align对齐其起始地址。您可以在此处声明自己的版本，例如，在不添加尾随填充字节的情况下强制对齐（请参阅LWIP_MEM_ALIGN_BUFFER）或您自己的节放置要求。\n例如，如果您使用gcc并需要32位对齐：\n\#define LWIP_DECLARE_MEMORY_ALIGNED（variable_name，size）u8_t variable_name[size]\__attribute\_\_（（ALIGNED（4）））\n或更便携：\n\#fine LWIP_DECLARE_MEMORIY_ALIGNED（variablename，size）u22_t variable_name[（size+sizeof（u32_t）-1）/sizeof（u32 _t）]
 */
#ifndef LWIP_DECLARE_MEMORY_ALIGNED
#define LWIP_DECLARE_MEMORY_ALIGNED(variable_name, size) u8_t variable_name[LWIP_MEM_ALIGN_BUFFER(size)]
#endif

/** 计算对齐缓冲区的内存大小-返回MEM_ALIGNMENT的下一个最高倍数（例如，LWIP_MEM_ALIGN_size（3）和LWIP_MEM _ALIGN_size（4）都将为MEM_ALIGNMENT==4产生4）。
 */
#ifndef LWIP_MEM_ALIGN_SIZE
#define LWIP_MEM_ALIGN_SIZE(size) (((size) + MEM_ALIGNMENT - 1U) & ~(MEM_ALIGNMENT-1U))
#endif

/** 使用未对齐类型作为存储时，计算对齐缓冲区的安全内存大小。这包括开始时（MEM_ALIGNMENT-1）的安全裕度（例如，如果缓冲区为u8_t[]，而实际数据为u32_t）
 */
#ifndef LWIP_MEM_ALIGN_BUFFER
#define LWIP_MEM_ALIGN_BUFFER(size) (((size) + MEM_ALIGNMENT - 1U))
#endif

/** 将内存指针与MEM_alignment定义的对齐对齐，以便ADDR%MEM_ALINMENT==0
 */
#ifndef LWIP_MEM_ALIGN
#define LWIP_MEM_ALIGN(addr) ((void *)(((mem_ptr_t)(addr) + MEM_ALIGNMENT - 1) & ~(mem_ptr_t)(MEM_ALIGNMENT-1)))
#endif

#ifdef __cplusplus
extern "C" {
#endif

/** 打包结构支持。放置在压缩结构的BEFORE声明中。\n有关打包结构声明的示例，请参见include/lwip/prot/subfolder。\n lwIP中包含到GCC/clang的端口，如果您使用这些编译器，则无需在此处执行任何操作。
  */
#ifndef PACK_STRUCT_BEGIN
#define PACK_STRUCT_BEGIN
#endif /* PACK_STRUCT_BEGIN */

/** 打包结构支持。放置压缩结构的AFTER声明。\n有关打包结构声明的示例，请参见include/lwip/prot/subfolder。\n lwIP中包含到GCC/clang的端口，如果您使用这些编译器，则无需在此处执行任何操作。
  */
#ifndef PACK_STRUCT_END
#define PACK_STRUCT_END
#endif /* PACK_STRUCT_END */

/** 打包结构支持。放置在压缩结构的声明结尾和尾随分号之间。\n有关打包结构声明的示例，请参见include/lwip/prot/subfolder。\n lwIP中包含到GCC/clang的端口，如果您使用这些编译器，则无需在此处执行任何操作。
  */
#ifndef PACK_STRUCT_STRUCT
#if defined(__GNUC__) || defined(__clang__)
#define PACK_STRUCT_STRUCT __attribute__((packed))
#else
#define PACK_STRUCT_STRUCT
#endif
#endif /* PACK_STRUCT_STRUCT */

/** 打包结构支持。包装u32_t和u16_t成员。\n有关打包结构声明的示例，请参见include/lwip/prot/subfolder。\n lwIP中包含到GCC/clang的端口，如果您使用这些编译器，则无需在此处执行任何操作。
  */
#ifndef PACK_STRUCT_FIELD
#define PACK_STRUCT_FIELD(x) x
#endif /* PACK_STRUCT_FIELD */

/** 打包结构支持。包装u8_t成员，其中一些编译器警告不需要打包。\n有关打包结构声明的示例，请参见include/lwip/prot/subfolder。\n lwIP中包含到GCC/clang的端口，如果您使用这些编译器，则无需在此处执行任何操作。
  */
#ifndef PACK_STRUCT_FLD_8
#define PACK_STRUCT_FLD_8(x) PACK_STRUCT_FIELD(x)
#endif /* PACK_STRUCT_FLD_8 */

/** 打包结构支持。包装打包结构本身的成员，其中一些编译器警告不需要打包。\n有关打包结构声明的示例，请参见include/lwip/prot/subfolder。\n lwIP中包含到GCC/clang的端口，如果您使用这些编译器，则无需在此处执行任何操作。
  */
#ifndef PACK_STRUCT_FLD_S
#define PACK_STRUCT_FLD_S(x) PACK_STRUCT_FIELD(x)
#endif /* PACK_STRUCT_FLD_S */

/** PACK_STRUCT_USE_INCLUDES==1：打包结构支持在要打包的结构之前和之后使用\#include文件。\n结构之前包含的文件是“arch/bpstruct.h”。\n结构之后包含的文件是“arch/epstruct.h”。\n这可用于在MS Visual C编译器上实现结构打包，请参阅lwIP contrib存储库中的Win32端口以供参考。有关打包结构声明的示例，请参见include/lwip/prot/subfolder。\n lwIP中包含到GCC/clang的端口，如果您使用这些编译器，则无需在此处执行任何操作。
 */
#ifdef __DOXYGEN__
#define PACK_STRUCT_USE_INCLUDES
#endif

/**消除编译器关于未使用参数的警告（GCC-Wextra-Wunused）。*/
#ifndef LWIP_UNUSED_ARG
#define LWIP_UNUSED_ARG(x) (void)x
#endif /* LWIP_UNUSED_ARG */

/** LWIP_PROVIDE_ERRNO==1:让LWIP提供ERRNO值和“ERRNO”变量。如果禁用，请抄送。h必须定义“errno”或include<errno。h> ，定义LWIP_ERRNO_STDINCLUDE以获取<ERRNO。h> 包含或将LWIP_ERRNO_INCLUDE定义为<ERRNO。h> 或同等产品。
 */
#if defined __DOXYGEN__
#define LWIP_PROVIDE_ERRNO
#endif

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* LWIP_HDR_ARCH_H */

