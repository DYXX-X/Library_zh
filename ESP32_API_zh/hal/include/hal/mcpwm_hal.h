// 版权所有2015-2021 Espressif Systems（Shanghai）PTE LTD
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

/*******************************************************************************
 * 注意：hal不是公共api，不要在应用程序代码中使用。请参阅自述文件。在hal/include/hal/readme.md中的md
 ******************************************************************************/

// MCPWM的HAL层（公共部分）

#pragma once

#include "soc/mcpwm_struct.h"

typedef struct {
    int host_id; ///<要使用的MCPWM外围设备，0-1。
} mcpwm_hal_init_config_t;

typedef struct {
    mcpwm_dev_t *dev; ///<单个MCPWM单元的外围寄存器的起始地址。调用`mcpwm_hal_init`对其进行初始化。
} mcpwm_hal_context_t;

/**
 * @brief 初始化HAL的内部状态。
 *
 * @param hal HAL层的上下文。
 * @param init_config HAL配置只能使用一次。
 */
void mcpwm_hal_init(mcpwm_hal_context_t *hal, const mcpwm_hal_init_config_t *init_config);

