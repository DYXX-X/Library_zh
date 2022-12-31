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

#include "soc/sens_reg.h"
#include "soc/sens_struct.h"
#include "soc/rtc_io_reg.h"
#include "soc/rtc_io_struct.h"
#include "soc/rtc.h"
#include "soc/dac_channel.h"
#include "soc/soc_caps.h"

#ifdef __cplusplus
extern "C"
{
#endif

typedef struct {
    const uint8_t dac_channel_io_num[SOC_DAC_PERIPH_NUM];
} dac_signal_conn_t;

extern const dac_signal_conn_t dac_periph_signal;

#ifdef __cplusplus
}
#endif

