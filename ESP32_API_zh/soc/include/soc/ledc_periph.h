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
#include "soc/ledc_reg.h"
#include "soc/ledc_struct.h"

#ifdef __cplusplus
extern "C" {
#endif

/*
 存储一堆每个led的外围数据。
*/
typedef struct {
    const uint8_t sig_out0_idx;
} ledc_signal_conn_t;

#if SOC_LEDC_SUPPORT_HS_MODE
extern const ledc_signal_conn_t ledc_periph_signal[2];
#else
extern const ledc_signal_conn_t ledc_periph_signal[1];
#endif

#ifdef __cplusplus
}
#endif

