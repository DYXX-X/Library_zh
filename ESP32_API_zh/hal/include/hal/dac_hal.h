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

#pragma once

#include "hal/dac_ll.h"

/**
 * 打开dac模块电源并启动输出电压。
 *
 * @note 通电前，确保DAC PAD设置为RTC PAD和浮动状态。
 * @param channel DAC通道编号。
 */
#define dac_hal_power_on(channel) dac_ll_power_on(channel)

/**
 * 给dac模块通电并停止输出电压。
 *
 * @param channel DAC通道编号。
 */
#define dac_hal_power_down(channel) dac_ll_power_down(channel)

/**
 * 启用/禁用ADC1和DAC的同步操作功能。
 *
 * @note  如果启用（默认），ADC RTC控制器采样将导致DAC通道输出电压。
 *
 * @param enable 启用或禁用adc和dac同步功能。
 */
#define  dac_hal_rtc_sync_by_adc(enable) dac_ll_rtc_sync_by_adc(enable)

/**
 * 输出电压值（8位）。
 *
 * @param channel DAC通道编号。
 * @param value 输出值。值范围：0~255。对应的电压范围为0v~VDD3P3_RTC。
 */
#define dac_hal_update_output_value(channel, value) dac_ll_update_output_value(channel, value)

/**
 * 启用余弦波发生器输出。
 */
#define dac_hal_cw_generator_enable() dac_ll_cw_generator_enable()

/**
 * 禁用余弦波发生器输出。
 */
#define dac_hal_cw_generator_disable() dac_ll_cw_generator_disable()

/**
 * 在DAC模块中配置余弦波发生器功能。
 *
 * @param cw 配置
 */
void dac_hal_cw_generator_config(dac_cw_config_t *cw);

/**
 * 启用/禁用DMA的DAC输出数据。
 */
#define dac_hal_digi_enable_dma(enable) dac_ll_digi_enable_dma(enable)

