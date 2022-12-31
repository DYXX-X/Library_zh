/* 版权所有（c）INRIA和Microsoft Corporation。保留所有权利。根据Apache 2.0许可证许可。*/

#ifndef __KREMLIN_TARGET_H
#define __KREMLIN_TARGET_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <inttypes.h>
#include <limits.h>

#include "kremlin/internal/callconv.h"

/******************************************************************************/
/* KreMLin将生成的宏。*/
/******************************************************************************/

/* 对于没有C stdlib的“裸”目标，用户可能希望使用[-add early include'“mydefinitions.h”']并覆盖这些。*/
#ifndef KRML_HOST_PRINTF
#  define KRML_HOST_PRINTF printf
#endif

#if (                                                                          \
    (defined __STDC_VERSION__) && (__STDC_VERSION__ >= 199901L) &&             \
    (!(defined KRML_HOST_EPRINTF)))
#  define KRML_HOST_EPRINTF(...) fprintf(stderr, __VA_ARGS__)
#endif

#ifndef KRML_HOST_EXIT
#  define KRML_HOST_EXIT exit
#endif

#ifndef KRML_HOST_MALLOC
#  define KRML_HOST_MALLOC malloc
#endif

#ifndef KRML_HOST_CALLOC
#  define KRML_HOST_CALLOC calloc
#endif

#ifndef KRML_HOST_FREE
#  define KRML_HOST_FREE free
#endif

#ifndef KRML_HOST_TIME

#  include <time.h>

/* Prims_nat尚未在范围内*/
inline static int32_t krml_time() {
  return (int32_t)time(NULL);
}

#  define KRML_HOST_TIME krml_time
#endif

/* 在声明位置，退出很容易。*/
#define KRML_EXIT                                                              \
  do {                                                                         \
    KRML_HOST_PRINTF("Unimplemented function at %s:%d\n", __FILE__, __LINE__); \
    KRML_HOST_EXIT(254);                                                       \
  } while (0)

/* 在表达式位置，使用逗号运算符和malloc返回正确大小的表达式。KreMLin将t作为参数传递给宏。
 */
#define KRML_EABORT(t, msg)                                                    \
  (KRML_HOST_PRINTF("KreMLin abort at %s:%d\n%s\n", __FILE__, __LINE__, msg),  \
   KRML_HOST_EXIT(255), *((t *)KRML_HOST_MALLOC(sizeof(t))))

/* 在FStar.Buffer.fst中，数组的大小是uint32_t，但它是多个元素。做一个丑陋的运行时检查（KreMLin可以消除其中的一些）。
 */

#ifdef __GNUC__
#  define _KRML_CHECK_SIZE_PRAGMA                                              \
    _Pragma("GCC diagnostic ignored \"-Wtype-limits\"")
#else
#  define _KRML_CHECK_SIZE_PRAGMA
#endif

#define KRML_CHECK_SIZE(size_elt, sz)                                          \
  do {                                                                         \
    _KRML_CHECK_SIZE_PRAGMA                                                    \
    if (((size_t)(sz)) > ((size_t)(SIZE_MAX / (size_elt)))) {                  \
      KRML_HOST_PRINTF(                                                        \
          "Maximum allocatable size exceeded, aborting before overflow at "    \
          "%s:%d\n",                                                           \
          __FILE__, __LINE__);                                                 \
      KRML_HOST_EXIT(253);                                                     \
    }                                                                          \
  } while (0)

#if defined(_MSC_VER) && _MSC_VER < 1900
#  define KRML_HOST_SNPRINTF(buf, sz, fmt, arg) _snprintf_s(buf, sz, _TRUNCATE, fmt, arg)
#else
#  define KRML_HOST_SNPRINTF(buf, sz, fmt, arg) snprintf(buf, sz, fmt, arg)
#endif

#endif

