// 版权所有2019-2020 Espressif Systems（上海）私人有限公司
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
#include "soc/soc_caps.h"
#include "soc/periph_defs.h"
#include "soc/pcnt_reg.h"
#include "soc/pcnt_struct.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    struct {
        struct {
            struct {
                const uint32_t pulse_sig;
                const uint32_t control_sig;
            } channels[SOC_PCNT_CHANNELS_PER_UNIT];
        } units[SOC_PCNT_UNITS_PER_GROUP];
        const uint32_t irq;
        const periph_module_t module;
    } groups[SOC_PCNT_GROUPS];
} pcnt_signal_conn_t;

extern const pcnt_signal_conn_t pcnt_periph_signals;

#ifdef __cplusplus
}
#endif

