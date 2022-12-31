// 版权所有2015-2018 Espressif Systems（上海）私人有限公司
//
// 根据Apache许可证2.0版（“许可证”）获得许可；
// 除非符合许可证，否则不得使用此文件。
// 您可以在以下地址获取许可证副本：

//     http://www.apache.org/licenses/LICENSE-2.0
//
// 除非适用法律要求或书面同意，软件
// 根据许可证分发的内容是按“原样”分发的，
// 无任何明示或暗示的保证或条件。
// 有关管理权限和
// 许可证下的限制。

#pragma once
#include <stdint.h>
//包括soc相关（生成的）定义
#include "soc/soc_caps.h"
#include "soc/soc_pins.h"
#ifdef SOC_SDIO_SLAVE_SUPPORTED
#include "soc/slc_reg.h"
#include "soc/slc_struct.h"
#endif
#include "soc/host_reg.h"
#include "soc/host_struct.h"
#include "soc/hinf_reg.h"
#include "soc/hinf_struct.h"

#ifdef __cplusplus
extern "C" {
#endif

/**每个插槽的引脚和信号信息*/
typedef struct {
    uint32_t clk_gpio;
    uint32_t cmd_gpio;
    uint32_t d0_gpio;
    uint32_t d1_gpio;
    uint32_t d2_gpio;
    uint32_t d3_gpio;
    int      func;
} sdio_slave_slot_info_t;

extern const sdio_slave_slot_info_t sdio_slave_slot_info[];

#ifdef __cplusplus
}
#endif

