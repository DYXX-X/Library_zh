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

#define SOC_ADC1_DATA_INVERT_DEFAULT    (1)
#define SOC_ADC2_DATA_INVERT_DEFAULT    (1)

#define SOC_ADC_DIGI_DATA_INVERT_DEFAULT(PERIPH_NUM) (1)

#define SOC_ADC_FSM_RSTB_WAIT_DEFAULT       (8)
#define SOC_ADC_FSM_START_WAIT_DEFAULT      (SOC_ADC_DIGI_SAR_CLK_DIV_DEFAULT)
#define SOC_ADC_FSM_STANDBY_WAIT_DEFAULT    (100)
#define ADC_FSM_SAMPLE_CYCLE_DEFAULT        (2)

#define SOC_ADC_PWDET_CCT_DEFAULT           (4)

#define SOC_ADC_SAR_CLK_DIV_DEFAULT(PERIPH_NUM) (2)

#define SOC_ADC_DIGI_SAR_CLK_DIV_DEFAULT    (16)

