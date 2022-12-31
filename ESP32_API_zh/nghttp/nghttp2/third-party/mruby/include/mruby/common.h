/*
**"common.h -mruby公共平台定义“
**
** 参见mruby.h中的版权声明
*/

#ifndef MRUBY_COMMON_H
#define MRUBY_COMMON_H

#ifdef __APPLE__
  #ifndef __TARGETCONDITIONALS__
  #include "TargetConditionals.h"
  #endif
#endif

#ifdef __cplusplus
#ifdef MRB_ENABLE_CXX_ABI
#define MRB_BEGIN_DECL
#define MRB_END_DECL
#else
# define MRB_BEGIN_DECL extern "C" {
# define MRB_END_DECL }
#endif
#else
/**以C模式启动声明*/
# define MRB_BEGIN_DECL
/**C模式下的结束声明*/
# define MRB_END_DECL
#endif

/**
 * 共享编译器宏
 */
MRB_BEGIN_DECL

/**声明永不返回的函数。*/
#if defined __STDC_VERSION__ && __STDC_VERSION__ >= 201112L
# define mrb_noreturn _Noreturn
#elif defined __GNUC__ && !defined __STRICT_ANSI__
# define mrb_noreturn __attribute__((noreturn))
#elif defined _MSC_VER
# define mrb_noreturn __declspec(noreturn)
#else
# define mrb_noreturn
#endif

/**将函数标记为已弃用。*/
#if defined __GNUC__ && !defined __STRICT_ANSI__
# define mrb_deprecated __attribute__((deprecated))
#elif defined _MSC_VER
# define mrb_deprecated __declspec(deprecated)
#else
# define mrb_deprecated
#endif

/**将函数声明为始终内联。*/
#if defined(_MSC_VER)
# define MRB_INLINE static __inline
#else
# define MRB_INLINE static inline
#endif


/**声明公共MRuby API函数。*/
#if defined(MRB_BUILD_AS_DLL)
#if defined(MRB_CORE) || defined(MRB_LIB)
# define MRB_API __declspec(dllexport)
#else
# define MRB_API __declspec(dllimport)
#endif
#else
# define MRB_API extern
#endif

MRB_END_DECL

#endif  /* MRUBY_COMMON_H */

