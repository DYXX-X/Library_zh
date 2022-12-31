// 版权所有2020 Espressif Systems（上海）私人有限公司
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
#pragma once

#include "soc/soc.h"
#include "soc/rtc_cntl_reg.h"
#include "soc/soc_caps.h"
#include "soc/rtc.h"

#ifdef __cplusplus
extern "C" {
#endif

static inline void soc_ll_stall_core(int core)
{
    const int rtc_cntl_c1_m[SOC_CPU_CORES_NUM] = {RTC_CNTL_SW_STALL_PROCPU_C1_M, RTC_CNTL_SW_STALL_APPCPU_C1_M};
    const int rtc_cntl_c1_s[SOC_CPU_CORES_NUM] = {RTC_CNTL_SW_STALL_PROCPU_C1_S, RTC_CNTL_SW_STALL_APPCPU_C1_S};
    const int rtc_cntl_c0_m[SOC_CPU_CORES_NUM] = {RTC_CNTL_SW_STALL_PROCPU_C0_M, RTC_CNTL_SW_STALL_APPCPU_C0_M};
    const int rtc_cntl_c0_s[SOC_CPU_CORES_NUM] = {RTC_CNTL_SW_STALL_PROCPU_C0_S, RTC_CNTL_SW_STALL_APPCPU_C0_S};

    CLEAR_PERI_REG_MASK(RTC_CNTL_SW_CPU_STALL_REG, rtc_cntl_c1_m[core]);
    SET_PERI_REG_MASK(RTC_CNTL_SW_CPU_STALL_REG, 0x21 << rtc_cntl_c1_s[core]);
    CLEAR_PERI_REG_MASK(RTC_CNTL_OPTIONS0_REG, rtc_cntl_c0_m[core]);
    SET_PERI_REG_MASK(RTC_CNTL_OPTIONS0_REG, 2 << rtc_cntl_c0_s[core]);
}

static inline void soc_ll_unstall_core(int core)
{
    const int rtc_cntl_c1_m[SOC_CPU_CORES_NUM] = {RTC_CNTL_SW_STALL_PROCPU_C1_M, RTC_CNTL_SW_STALL_APPCPU_C1_M};
    const int rtc_cntl_c0_m[SOC_CPU_CORES_NUM] = {RTC_CNTL_SW_STALL_PROCPU_C0_M, RTC_CNTL_SW_STALL_APPCPU_C0_M};
    CLEAR_PERI_REG_MASK(RTC_CNTL_SW_CPU_STALL_REG, rtc_cntl_c1_m[core]);
    CLEAR_PERI_REG_MASK(RTC_CNTL_OPTIONS0_REG, rtc_cntl_c0_m[core]);
}

static inline void soc_ll_reset_core(int core)
{
    SET_PERI_REG_MASK(RTC_CNTL_OPTIONS0_REG,
            core == 0 ? RTC_CNTL_SW_PROCPU_RST_M : RTC_CNTL_SW_APPCPU_RST_M);
}

#ifdef __cplusplus
}
#endif

