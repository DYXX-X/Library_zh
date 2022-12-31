/*
** bconf先生。h-mruby核心配置
**
** 参见mruby.h中的版权声明
*/

#ifndef MRUBYCONF_H
#define MRUBYCONF_H

#include <limits.h>
#include <stdint.h>

/* 架构选择：*/
/* 指定-DMRB_32BIT或-DMRB_64BIT以覆盖*/
#if !defined(MRB_32BIT) && !defined(MRB_64BIT)
#if UINT64_MAX == SIZE_MAX
#define MRB_64BIT
#else
#define MRB_32BIT
#endif
#endif

#if defined(MRB_32BIT) && defined(MRB_64BIT)
#error Cannot build for 32 and 64 bit architecture at the same time
#endif

/* 配置选项：*/
/* 添加-DMRB_USE_FLOAT以对浮点数使用FLOAT而不是double*/
//#定义MRB_USE_FLOAT

/* 排除浮点数*/
//#定义MRB_WITHOUT_FLOAT

/* 添加-DMRB_METHOD_CACHE以使用方法缓存提高性能*/
//#定义MRB_METHOD_CACHE
/* 方法缓存的大小（需要是2的幂）*/
//#定义MRB_METHOD_CACHE_SIZE（1<<7）

/* 添加-DMRB_METHOD_TABLE_INLINE以减小方法表的大小*/
/* MRB_METHOD_ABLE_INLINE要求函数指针的LSB为零*/
/* 您可能需要指定--falign functions=n（其中n>1）*/
//#定义MRB_METHOD_ABLE_INLINE

/* 添加-DMRB_INT16以使用16位整数作为mrb_int；与MRB_INT64冲突*/
//#定义MRB_INT16

/* 添加-DMRB_INT64以使用64位整数作为mrb_int；与MRB_INT16冲突*/
//#定义MRB_INT64

/* 如果未选择特定整数类型*/
#if !defined(MRB_INT16) && !defined(MRB_INT32) && !defined(MRB_INT64)
# if defined(MRB_64BIT) && !defined(MRB_NAN_BOXING)
/* 在64位架构上使用64位整数（无MRB_NAN_BOXING）*/
#  define MRB_INT64
# else
/* 否则使用32位整数*/
#  define MRB_INT32
# endif
#endif

/* 在big endian机器上定义；由MRB_NAN_BOXING等使用。*/
#ifndef MRB_ENDIAN_BIG
# if (defined(BYTE_ORDER) && defined(BIG_ENDIAN) && BYTE_ORDER == BIG_ENDIAN) || \
     (defined(__BYTE_ORDER__) && defined(__ORDER_BIG_ENDIAN__) && __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__)
#  define MRB_ENDIAN_BIG
# endif
#endif

/* 用双框表示mrb_value；与MRB_USE_FLOAT和MRB_WITHOUT_FLOAT冲突*/
//#定义MRB_NAN_BOXING

/* 将mrb_value表示为单词（处理器的自然数据单位）*/
//#定义MRB_WORD_BOXING

/* 用于处理UTF-8编码的字符串类*/
//#定义MRB_UTF8_STRING

/* mrb_funcall中的argv最大大小*/
//#定义MRB_FUNCALL_ARGC_MAX 16

/* 每个堆页的对象数*/
//#定义MRB_HEAP_PAGE_SIZE 1024

/* 如果文本和数据可用，mruby可以减少符号使用的内存*/
//#定义MRB_USE_ETEXT_EDATA

/* 不要使用__init_array_start来确定只读数据段；仅在定义MRB_USE_ETEXT_EDATA时有效*/
//#定义MRB_NO_INIT_ARRAY_START

/* 默认情况下关闭世代GC*/
//#定义MRB_GC_TURN_OFF_GENERATIONAL

/* khash表桶的默认大小*/
//#定义KHASH_DEFAULT_SIZE 32

/* 分配内存地址对齐*/
//#定义POOL_ALIGNMENT 4

/* 内存池的页面大小*/
//#定义POOL_PAGE_SIZE 16000

/* 字符串缓冲区的初始最小大小*/
//#定义MRB_STR_BUF_MIN_SIZE 128

/* 竞技场规模*/
//#定义MRB_GC_ARENA_SIZE 100

/* 固定规模GC竞技场*/
//#定义MRB_GC_FIXED_ARENA

/* 状态atexit堆栈大小*/
//#定义MRB_FIXED_STATE_ATEXIT_STACK_SIZE 5

/* 固定大小状态atexit堆栈*/
//#定义MRB_FIXED_STATE_ATEXIT_STACK

/* -DMRB_DISABLE_XXXX删除以下功能*/
//#define MRB_DISABLE_STDIO /* stdio的使用*/

/* -DMRB_ENABLE_XXXX启用以下功能*/
//#define MRB_ENABLE_DEBUG_HOOK /* 调试器挂钩*/
//#define MRB_ENABLE_ALL_SYMBOLS /* 符号。所有符号（_S）*/

/* 配置结束*/

/* 从DISABLE_XXX定义MRB_DISABLE_XXXX（用于兼容性）*/
#ifdef DISABLE_STDIO
#define MRB_DISABLE_STDIO
#endif

/* 从ENABLE_XXX定义MRB_ENABLE_XXXX（用于兼容性）*/
#ifdef ENABLE_DEBUG
#define MRB_ENABLE_DEBUG_HOOK
#endif

#ifndef MRB_DISABLE_STDIO
# include <stdio.h>
#endif

#ifndef FALSE
# define FALSE 0
#endif

#ifndef TRUE
# define TRUE 1
#endif

#endif  /* MRUBYCONF_H */

