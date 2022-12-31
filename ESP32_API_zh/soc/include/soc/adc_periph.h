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

#include "soc/soc.h"
#include "soc/soc_caps.h"
#include "soc/syscon_struct.h"

#if SOC_ADC_RTC_CTRL_SUPPORTED
#include "soc/sens_reg.h"
#include "soc/sens_struct.h"
#endif

#if SOC_RTCIO_INPUT_OUTPUT_SUPPORTED
#include "soc/rtc_io_struct.h"
#endif
#include "soc/rtc_cntl_struct.h"
#include "soc/adc_channel.h"
#include "soc/soc_caps.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * 存储与ADC通道编号相对应的IO编号。
 *
 * @value
 *      ->=0：GPIO编号索引。
 *      --1：不支持。
 */
extern const int adc_channel_io_map[SOC_ADC_PERIPH_NUM][SOC_ADC_MAX_CHANNEL_NUM];

#ifdef __cplusplus
}
#endif

