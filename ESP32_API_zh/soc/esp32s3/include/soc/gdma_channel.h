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

// 以下宏的格式为SOC_[periph][instance_id]，以便与`GDMA_make_TRIGGER一起使用`
#define SOC_GDMA_TRIG_PERIPH_M2M0    (-1)
#define SOC_GDMA_TRIG_PERIPH_SPI2    (0)
#define SOC_GDMA_TRIG_PERIPH_SPI3    (1)
#define SOC_GDMA_TRIG_PERIPH_UART0   (2)
#define SOC_GDMA_TRIG_PERIPH_I2S0    (3)
#define SOC_GDMA_TRIG_PERIPH_I2S1    (4)
#define SOC_GDMA_TRIG_PERIPH_LCD0    (5)
#define SOC_GDMA_TRIG_PERIPH_CAM0    (5)
#define SOC_GDMA_TRIG_PERIPH_AES0    (6)
#define SOC_GDMA_TRIG_PERIPH_SHA0    (7)
#define SOC_GDMA_TRIG_PERIPH_ADC0    (8)
#define SOC_GDMA_TRIG_PERIPH_DAC0    (8)
#define SOC_GDMA_TRIG_PERIPH_RMT0    (9)

