// 版权所有2019 Espressif Systems（上海）私人有限公司
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

#include "soc/soc_caps.h"
#include "soc/mcpwm_reg.h"
#include "soc/mcpwm_struct.h"
#include "soc/periph_defs.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    struct {
        const periph_module_t module; // 外围模块
        const int irq_id;
        struct {
            struct {
                const uint32_t pwm_sig;
            } generators[SOC_MCPWM_GENERATORS_PER_OPERATOR];
        } operators[SOC_MCPWM_OPERATORS_PER_GROUP];
        struct {
            const uint32_t fault_sig;
        } gpio_faults[SOC_MCPWM_GPIO_FAULTS_PER_GROUP];
        struct {
            const uint32_t cap_sig;
        } captures[SOC_MCPWM_CAPTURE_CHANNELS_PER_TIMER];
        struct {
            const uint32_t sync_sig;
        } gpio_synchros[SOC_MCPWM_GPIO_SYNCHROS_PER_GROUP];
    } groups[SOC_MCPWM_GROUPS];
} mcpwm_signal_conn_t;

extern const mcpwm_signal_conn_t mcpwm_periph_signals;

#ifdef __cplusplus
}
#endif

