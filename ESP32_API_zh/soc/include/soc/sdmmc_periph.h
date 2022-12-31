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
#include "soc/sdmmc_reg.h"
#include "soc/sdmmc_struct.h"
#include "soc/gpio_sig_map.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * 通用SDMMC插槽信息，不取决于SOC_SDMMC_USE_{IOMUX，GPIO_MATRIX}
 */
typedef struct {
    uint8_t width;          /*!< 最大支持插槽宽度（1、4、8）*/
    uint8_t card_detect;    /*!< GPIO矩阵中的卡检测信号*/
    uint8_t write_protect;  /*!< GPIO矩阵中的写保护信号*/
    uint8_t card_int;       /*!< GPIO矩阵中的卡中断信号*/
} sdmmc_slot_info_t;

/**辅助SD主机信号的宽度和GPIO矩阵信号编号，每个插槽一个结构*/
extern const sdmmc_slot_info_t sdmmc_slot_info[SOC_SDMMC_NUM_SLOTS];

/**
 * 此结构列出了SD总线信号的引脚号（如果设置了SOC_SDMMC_USE_IOMUX）或GPIO矩阵信号号（如果已设置SOC_SDMMAC_USE_GPIO_Matrix）。字段名称与SD总线信号名称匹配。
 */
typedef struct {
    uint8_t clk;
    uint8_t cmd;
    uint8_t d0;
    uint8_t d1;
    uint8_t d2;
    uint8_t d3;
    uint8_t d4;
    uint8_t d5;
    uint8_t d6;
    uint8_t d7;
} sdmmc_slot_io_info_t;

/* 注：理论上，在同一个SoC中同时支持IOMUX和GPIO矩阵是可能的。但是，目前任何SoC都不支持这一点，这会使驱动程序复杂化。因此，一次只支持其中一个选项。
 */
#if SOC_SDMMC_USE_IOMUX
/**SD总线信号的GPIO引脚数，每个插槽一个结构*/
extern const sdmmc_slot_io_info_t sdmmc_slot_gpio_num[SOC_SDMMC_NUM_SLOTS];

#elif SOC_SDMMC_USE_GPIO_MATRIX
/**SD总线信号的GPIO矩阵信号数量，每个插槽一个结构*/
extern const sdmmc_slot_io_info_t sdmmc_slot_gpio_sig[SOC_SDMMC_NUM_SLOTS];

#endif // SOC_SDMMC_USE_{IOMUX,GPIO_MATRIX}

#ifdef __cplusplus
}
#endif

