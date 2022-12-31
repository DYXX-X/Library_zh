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

/*******************************************************************************
 * 注意：hal不是公共api，不要在应用程序代码中使用。请参阅自述文件。在hal/include/hal/readme.md中的md
 ******************************************************************************/

// DAC的HAL层（esp32s2特定部分）

#pragma once

#include "hal/dac_ll.h"
#include "hal/dac_types.h"

#include_next "hal/dac_hal.h"

#ifdef __cplusplus
extern "C" {
#endif

/*---------------------------------------------------------------
                    数字控制器设置
---------------------------------------------------------------*/
/**
 * 数字控制器初始化。
 */
void dac_hal_digi_init(void);

/**
 * 数字控制器去初始化。
 */
void dac_hal_digi_deinit(void);

/**
 * 设置DAC数字控制器。
 *
 * @param cfg 指向数字控制器参数的指针。
 */
void dac_hal_digi_controller_config(const dac_digi_config_t *cfg);

/**
 * DAC数字控制器启动输出电压。
 */
void dac_hal_digi_start(void);

/**
 * DAC数字控制器停止输出电压。
 */
void dac_hal_digi_stop(void);

/**
 * 重置DAC数字控制器FIFO。
 */
#define dac_hal_digi_fifo_reset() dac_ll_digi_fifo_reset()

/**
 * 重置DAC数字控制器。
 */
#define dac_hal_digi_reset() dac_ll_digi_reset()

#ifdef __cplusplus
}
#endif

