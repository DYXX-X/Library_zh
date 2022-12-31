/* 版权所有（c）INRIA和Microsoft Corporation。保留所有权利。根据Apache 2.0许可证许可。*/

#ifndef __KREMLIN_CALLCONV_H
#define __KREMLIN_CALLCONV_H

/******************************************************************************/
/* 一些宏可简化兼容性*/
/******************************************************************************/

/* 我们希望安全地生成__cdecl，而不必担心它是未定义的。使用MSVC时，始终定义这些。在使用MinGW时，也定义了这些。它们对其他平台没有意义，因此我们将它们定义为其他情况下的空宏。*/
#ifndef _MSC_VER
#ifndef __cdecl
#define __cdecl
#endif
#ifndef __stdcall
#define __stdcall
#endif
#ifndef __fastcall
#define __fastcall
#endif
#endif

/* 由于KreMLin无条件地发出内联关键字，因此我们遵循以下指南https://gcc.gnu.org/onlinedocs/gcc/Inline.html并使其成为__inline_，以确保代码使用-std=c90和更早版本编译。*/
#ifdef __GNUC__
#  define inline __inline__
#endif

/* GCC特定属性语法；其他人都会获得标准的C内联属性。*/
#ifdef __GNU_C__
#  ifndef __clang__
#    define force_inline inline __attribute__((always_inline))
#  else
#    define force_inline inline
#  endif
#else
#  define force_inline inline
#endif

#endif

