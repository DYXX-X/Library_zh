// 版权所有2015-2019 Espressif Systems（上海）私人有限公司
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

#pragma once
#include <stdint.h>
#include "freertos/xtensa_context.h"
#include "gdbstub_target_config.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef XtExcFrame esp_gdbstub_frame_t;

/* GDB regfile结构，取决于配置*/
typedef struct {
    uint32_t pc;
    uint32_t a[XCHAL_NUM_AREGS];

#if XCHAL_HAVE_LOOPS
    uint32_t lbeg;
    uint32_t lend;
    uint32_t lcount;
#endif

    uint32_t sar;

#if XCHAL_HAVE_WINDOWED
    uint32_t windowbase;
    uint32_t windowstart;
#endif

    uint32_t configid0;
    uint32_t configid1;
    uint32_t ps;

#if XCHAL_HAVE_THREADPTR
    uint32_t threadptr;
#endif

#if XCHAL_HAVE_BOOLEANS
    uint32_t br;
#endif

#if XCHAL_HAVE_S32C1I
    uint32_t scompare1;
#endif

#if XCHAL_HAVE_MAC16
    uint32_t acclo;
    uint32_t acchi;
    uint32_t m0;
    uint32_t m1;
    uint32_t m2;
    uint32_t m3;
#endif

#if XCHAL_HAVE_DFP_ACCEL
    uint32_t expstate;
    uint32_t f64r_lo;
    uint32_t f64r_hi;
    uint32_t f64s;
#endif

#if XCHAL_HAVE_FP
    uint32_t f[16];
    uint32_t fcr;
    uint32_t fsr;
#endif

#if GDBSTUB_EXTRA_TIE_SIZE > 0
    uint32_t tie[GDBSTUB_EXTRA_TIE_SIZE];
#endif

} esp_gdbstub_gdb_regfile_t;


#ifdef __cplusplus
}
#endif

