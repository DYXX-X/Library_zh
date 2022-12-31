/* 版权所有（c）INRIA和Microsoft Corporation。保留所有权利。根据Apache 2.0许可证许可。*/

#ifndef __KREMLIN_DEBUG_H
#define __KREMLIN_DEBUG_H

#include <inttypes.h>

#include "kremlin/internal/target.h"

/******************************************************************************/
/* 调试助手-仅适用于KreMLin开发人员*/
/******************************************************************************/

/* 为了支持“-wasm-d force-c”：我们可能需要向前声明这个函数，因为对WasmSupport的依赖出现得很晚，在SimplifyWasm之后，而且很遗憾，在拓扑顺序完成之后。*/
void WasmSupport_check_buffer_size(uint32_t s);

/* 跟踪函数调用的一系列GCC暴行（kremlin的[-d c-calls]选项）。在尝试调试（例如Wasm）以比较跟踪时很有用。*/
/* clang格式关闭*/
#ifdef __GNUC__
#define KRML_FORMAT(X) _Generic((X),                                           \
  uint8_t : "0x%08" PRIx8,                                                     \
  uint16_t: "0x%08" PRIx16,                                                    \
  uint32_t: "0x%08" PRIx32,                                                    \
  uint64_t: "0x%08" PRIx64,                                                    \
  int8_t  : "0x%08" PRIx8,                                                     \
  int16_t : "0x%08" PRIx16,                                                    \
  int32_t : "0x%08" PRIx32,                                                    \
  int64_t : "0x%08" PRIx64,                                                    \
  default : "%s")

#define KRML_FORMAT_ARG(X) _Generic((X),                                       \
  uint8_t : X,                                                                 \
  uint16_t: X,                                                                 \
  uint32_t: X,                                                                 \
  uint64_t: X,                                                                 \
  int8_t  : X,                                                                 \
  int16_t : X,                                                                 \
  int32_t : X,                                                                 \
  int64_t : X,                                                                 \
  default : "unknown")
/* clang格式打开*/

#  define KRML_DEBUG_RETURN(X)                                                 \
    ({                                                                         \
      __auto_type _ret = (X);                                                  \
      KRML_HOST_PRINTF("returning: ");                                         \
      KRML_HOST_PRINTF(KRML_FORMAT(_ret), KRML_FORMAT_ARG(_ret));              \
      KRML_HOST_PRINTF(" \n");                                                 \
      _ret;                                                                    \
    })
#endif

#endif

