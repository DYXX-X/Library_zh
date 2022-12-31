// 版权所有2018 Espressif Systems（上海）私人有限公司
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
#include "stdint.h"
#include "soc/io_mux_reg.h"
#include "soc/gpio_struct.h"
#include "soc/gpio_reg.h"
#include "soc/soc_caps.h"
#include "soc/gpio_sig_map.h"

#ifdef __cplusplus
extern "C"
{
#endif

extern const uint32_t GPIO_PIN_MUX_REG[SOC_GPIO_PIN_COUNT];

extern const uint32_t GPIO_HOLD_MASK[SOC_GPIO_PIN_COUNT];

#ifdef __cplusplus
}
#endif

