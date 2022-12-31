// 版权所有2020 Espressif Systems（上海）私人有限公司
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
#include "soc/soc.h"
#include "soc/soc_caps.h"
#include "soc/periph_defs.h"

#ifdef __cplusplus
extern "C" {
#endif

#if SOC_DEDICATED_GPIO_SUPPORTED
typedef struct {
    const periph_module_t module; // 外围模块
    const int irq;                // 中断资源（-1表示不支持中断）
    struct {
        const int in_sig_per_channel[SOC_DEDIC_GPIO_IN_CHANNELS_NUM];
        const int out_sig_per_channel[SOC_DEDIC_GPIO_OUT_CHANNELS_NUM];
    } cores[SOC_CPU_CORES_NUM]; // GPIO矩阵的信号路由
} dedic_gpio_signal_conn_t;

extern const dedic_gpio_signal_conn_t dedic_gpio_periph_signals;
#endif // SOC_DEDICATED_GPIO_SUPPORTED

#ifdef __cplusplus
}
#endif

