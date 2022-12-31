/** 版权所有2021 Espressif Systems（Shanghai）PTE LTD
 *
 *  根据Apache许可证2.0版（“许可证”）获得许可；除非符合许可证，否则不得使用此文件。您可以在以下地址获取许可证副本：
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  除非适用法律要求或书面同意，否则根据许可证分发的软件是按“原样”分发的，无任何明示或暗示的担保或条件。有关许可证下权限和限制的具体语言，请参阅许可证。
 */
#pragma once

#include <stdint.h>
#include "soc/soc.h"
#ifdef __cplusplus
extern "C" {
#endif

/** SYSTIMER_CONF_REG寄存器配置系统计时器时钟
 */
#define SYSTIMER_CONF_REG (DR_REG_SYSTIMER_BASE + 0x0)
/** SYSTIMER_CLK_FO:R/W；位位置：[0]；默认值：0；系统计时器强制时钟启用
 */
#define SYSTIMER_CLK_FO    (BIT(0))
#define SYSTIMER_CLK_FO_M  (SYSTIMER_CLK_FO_V << SYSTIMER_CLK_FO_S)
#define SYSTIMER_CLK_FO_V  0x00000001
#define SYSTIMER_CLK_FO_S  0
/** SYSTIMER_CLK_EN:R/W；位位置：[31]；默认值：0；寄存器时钟启用
 */
#define SYSTIMER_CLK_EN    (BIT(31))
#define SYSTIMER_CLK_EN_M  (SYSTIMER_CLK_EN_V << SYSTIMER_CLK_EN_S)
#define SYSTIMER_CLK_EN_V  0x00000001
#define SYSTIMER_CLK_EN_S  31

/** SYSTIMER_LOAD_REG将加载值注册到系统计时器
 */
#define SYSTIMER_LOAD_REG (DR_REG_SYSTIMER_BASE + 0x4)
/** SYSTIMER_TIMER_LOAD：WO；位位置：[31]；默认值：0；系统计时器的负载值
 */
#define SYSTIMER_TIMER_LOAD    (BIT(31))
#define SYSTIMER_TIMER_LOAD_M  (SYSTIMER_TIMER_LOAD_V << SYSTIMER_TIMER_LOAD_S)
#define SYSTIMER_TIMER_LOAD_V  0x00000001
#define SYSTIMER_TIMER_LOAD_S  31

/** SYSTIMER_LOAD_HI_REG寄存器高32位加载到系统计时器
 */
#define SYSTIMER_LOAD_HI_REG (DR_REG_SYSTIMER_BASE + 0x8)
/** SYSTIMER_TIMER_LOAD_HI:R/W；位位置：[31:0]；默认值：0；高32位系统计时器负载
 */
#define SYSTIMER_TIMER_LOAD_HI    0xFFFFFFFF
#define SYSTIMER_TIMER_LOAD_HI_M  (SYSTIMER_TIMER_LOAD_HI_V << SYSTIMER_TIMER_LOAD_HI_S)
#define SYSTIMER_TIMER_LOAD_HI_V  0xFFFFFFFF
#define SYSTIMER_TIMER_LOAD_HI_S  0

/** SYSTIMER_LOAD_LO_REG寄存器低32位加载到系统计时器
 */
#define SYSTIMER_LOAD_LO_REG (DR_REG_SYSTIMER_BASE + 0xc)
/** SYSTIMER_TIMER_LOAD_LO:R/W；位位置：[31:0]；默认值：0；低32位系统计时器负载
 */
#define SYSTIMER_TIMER_LOAD_LO    0xFFFFFFFF
#define SYSTIMER_TIMER_LOAD_LO_M  (SYSTIMER_TIMER_LOAD_LO_V << SYSTIMER_TIMER_LOAD_LO_S)
#define SYSTIMER_TIMER_LOAD_LO_V  0xFFFFFFFF
#define SYSTIMER_TIMER_LOAD_LO_S  0

/** SYSTIMER_STEP_REG寄存器系统计时器累加步骤
 */
#define SYSTIMER_STEP_REG (DR_REG_SYSTIMER_BASE + 0x10)
/** SYSTIMER_TIMER_XTAL_STEP:R/W；位位置：[9:0]；默认值：80；使用XTAL时的系统计时器累积步骤
 */
#define SYSTIMER_TIMER_XTAL_STEP    0x000003FF
#define SYSTIMER_TIMER_XTAL_STEP_M  (SYSTIMER_TIMER_XTAL_STEP_V << SYSTIMER_TIMER_XTAL_STEP_S)
#define SYSTIMER_TIMER_XTAL_STEP_V  0x000003FF
#define SYSTIMER_TIMER_XTAL_STEP_S  0
/** SYSTIMER_TIMER_PLL_STEP:R/W；比特位置：[19:10]；默认值：1；使用PLL时的系统计时器累积步骤
 */
#define SYSTIMER_TIMER_PLL_STEP    0x000003FF
#define SYSTIMER_TIMER_PLL_STEP_M  (SYSTIMER_TIMER_PLL_STEP_V << SYSTIMER_TIMER_PLL_STEP_S)
#define SYSTIMER_TIMER_PLL_STEP_V  0x000003FF
#define SYSTIMER_TIMER_PLL_STEP_S  10

/** SYSTIMER_TARGET0_HI_REG寄存器系统计时器目标0高32位
 */
#define SYSTIMER_TARGET0_HI_REG (DR_REG_SYSTIMER_BASE + 0x14)
/** SYSTIMER_TIMER_TARGET0_HI:R/W；位位置：[31:0]；默认值：0；系统计时器target0高32位
 */
#define SYSTIMER_TIMER_TARGET0_HI    0xFFFFFFFF
#define SYSTIMER_TIMER_TARGET0_HI_M  (SYSTIMER_TIMER_TARGET0_HI_V << SYSTIMER_TIMER_TARGET0_HI_S)
#define SYSTIMER_TIMER_TARGET0_HI_V  0xFFFFFFFF
#define SYSTIMER_TIMER_TARGET0_HI_S  0

/** SYSTIMER_TARGET0_LO_REG寄存器系统计时器目标0低32位
 */
#define SYSTIMER_TARGET0_LO_REG (DR_REG_SYSTIMER_BASE + 0x18)
/** SYSTIMER_TIMER_TARGET0_LO:R/W；位位置：[31:0]；默认值：0；系统计时器target0低32位
 */
#define SYSTIMER_TIMER_TARGET0_LO    0xFFFFFFFF
#define SYSTIMER_TIMER_TARGET0_LO_M  (SYSTIMER_TIMER_TARGET0_LO_V << SYSTIMER_TIMER_TARGET0_LO_S)
#define SYSTIMER_TIMER_TARGET0_LO_V  0xFFFFFFFF
#define SYSTIMER_TIMER_TARGET0_LO_S  0

/** SYSTIMER_TARGET1_HI_REG寄存器系统计时器TARGET1高32位
 */
#define SYSTIMER_TARGET1_HI_REG (DR_REG_SYSTIMER_BASE + 0x1c)
/** SYSTIMER_TIMER_TARGET1_HI:R/W；位位置：[31:0]；默认值：0；系统计时器target1高32位
 */
#define SYSTIMER_TIMER_TARGET1_HI    0xFFFFFFFF
#define SYSTIMER_TIMER_TARGET1_HI_M  (SYSTIMER_TIMER_TARGET1_HI_V << SYSTIMER_TIMER_TARGET1_HI_S)
#define SYSTIMER_TIMER_TARGET1_HI_V  0xFFFFFFFF
#define SYSTIMER_TIMER_TARGET1_HI_S  0

/** SYSTIMER_TARGET1_LO_REG寄存器系统计时器TARGET1低32位
 */
#define SYSTIMER_TARGET1_LO_REG (DR_REG_SYSTIMER_BASE + 0x20)
/** SYSTIMER_TIMER_TARGET1_LO:R/W；位位置：[31:0]；默认值：0；系统计时器target1低32位
 */
#define SYSTIMER_TIMER_TARGET1_LO    0xFFFFFFFF
#define SYSTIMER_TIMER_TARGET1_LO_M  (SYSTIMER_TIMER_TARGET1_LO_V << SYSTIMER_TIMER_TARGET1_LO_S)
#define SYSTIMER_TIMER_TARGET1_LO_V  0xFFFFFFFF
#define SYSTIMER_TIMER_TARGET1_LO_S  0

/** SYSTIMER_TARGET2_HI_REG寄存器系统计时器TARGET2高32位
 */
#define SYSTIMER_TARGET2_HI_REG (DR_REG_SYSTIMER_BASE + 0x24)
/** SYSTIMER_TIMER_TARGET2_HI:R/W；位位置：[31:0]；默认值：0；系统计时器target2高32位
 */
#define SYSTIMER_TIMER_TARGET2_HI    0xFFFFFFFF
#define SYSTIMER_TIMER_TARGET2_HI_M  (SYSTIMER_TIMER_TARGET2_HI_V << SYSTIMER_TIMER_TARGET2_HI_S)
#define SYSTIMER_TIMER_TARGET2_HI_V  0xFFFFFFFF
#define SYSTIMER_TIMER_TARGET2_HI_S  0

/** SYSTIMER_TARGET2_LO_REG寄存器系统计时器TARGET2低32位
 */
#define SYSTIMER_TARGET2_LO_REG (DR_REG_SYSTIMER_BASE + 0x28)
/** SYSTIMER_TIMER_TARGET2_LO:R/W；位位置：[31:0]；默认值：0；系统计时器target2低32位
 */
#define SYSTIMER_TIMER_TARGET2_LO    0xFFFFFFFF
#define SYSTIMER_TIMER_TARGET2_LO_M  (SYSTIMER_TIMER_TARGET2_LO_V << SYSTIMER_TIMER_TARGET2_LO_S)
#define SYSTIMER_TIMER_TARGET2_LO_V  0xFFFFFFFF
#define SYSTIMER_TIMER_TARGET2_LO_S  0

/** SYSTIMER_TARGET0_CONF_REG寄存器配置系统计时器TARGET0工作模式
 */
#define SYSTIMER_TARGET0_CONF_REG (DR_REG_SYSTIMER_BASE + 0x2c)
/** SYSTIMER_TARGET0_周期：R/W；位位置：[29:0]；默认值：0；系统计时器target0报警周期
 */
#define SYSTIMER_TARGET0_PERIOD    0x3FFFFFFF
#define SYSTIMER_TARGET0_PERIOD_M  (SYSTIMER_TARGET0_PERIOD_V << SYSTIMER_TARGET0_PERIOD_S)
#define SYSTIMER_TARGET0_PERIOD_V  0x3FFFFFFF
#define SYSTIMER_TARGET0_PERIOD_S  0
/** 系统目标周期模式：R/W；位位置：[30]；默认值：0；系统计时器target0是否在周期模式下工作
 */
#define SYSTIMER_TARGET0_PERIOD_MODE    (BIT(30))
#define SYSTIMER_TARGET0_PERIOD_MODE_M  (SYSTIMER_TARGET0_PERIOD_MODE_V << SYSTIMER_TARGET0_PERIOD_MODE_S)
#define SYSTIMER_TARGET0_PERIOD_MODE_V  0x00000001
#define SYSTIMER_TARGET0_PERIOD_MODE_S  30
/** SYSTIMER_TARGET0_WORK_EN:R/W；位位置：[31]；默认值：0；系统计时器target0工作启用
 */
#define SYSTIMER_TARGET0_WORK_EN    (BIT(31))
#define SYSTIMER_TARGET0_WORK_EN_M  (SYSTIMER_TARGET0_WORK_EN_V << SYSTIMER_TARGET0_WORK_EN_S)
#define SYSTIMER_TARGET0_WORK_EN_V  0x00000001
#define SYSTIMER_TARGET0_WORK_EN_S  31

/** SYSTIMER_TARGET1_CONF_REG寄存器配置系统计时器TARGET1工作模式
 */
#define SYSTIMER_TARGET1_CONF_REG (DR_REG_SYSTIMER_BASE + 0x30)
/** SYSTIMER_TARGET1_PERIOD:R/W；位位置：[29:0]；默认值：0；系统计时器target1报警周期
 */
#define SYSTIMER_TARGET1_PERIOD    0x3FFFFFFF
#define SYSTIMER_TARGET1_PERIOD_M  (SYSTIMER_TARGET1_PERIOD_V << SYSTIMER_TARGET1_PERIOD_S)
#define SYSTIMER_TARGET1_PERIOD_V  0x3FFFFFFF
#define SYSTIMER_TARGET1_PERIOD_S  0
/** SYSTIMER_TARGET1_PERIOD_MODE：R/W；位位置：[30]；默认值：0；系统计时器target1是否在周期模式下工作
 */
#define SYSTIMER_TARGET1_PERIOD_MODE    (BIT(30))
#define SYSTIMER_TARGET1_PERIOD_MODE_M  (SYSTIMER_TARGET1_PERIOD_MODE_V << SYSTIMER_TARGET1_PERIOD_MODE_S)
#define SYSTIMER_TARGET1_PERIOD_MODE_V  0x00000001
#define SYSTIMER_TARGET1_PERIOD_MODE_S  30
/** SYSTIMER_TARGET1_WORK_EN:R/W；位位置：[31]；默认值：0；系统计时器target1工作启用
 */
#define SYSTIMER_TARGET1_WORK_EN    (BIT(31))
#define SYSTIMER_TARGET1_WORK_EN_M  (SYSTIMER_TARGET1_WORK_EN_V << SYSTIMER_TARGET1_WORK_EN_S)
#define SYSTIMER_TARGET1_WORK_EN_V  0x00000001
#define SYSTIMER_TARGET1_WORK_EN_S  31

/** SYSTIMER_TARGET2_CONF_REG寄存器配置系统计时器TARGET2工作模式
 */
#define SYSTIMER_TARGET2_CONF_REG (DR_REG_SYSTIMER_BASE + 0x34)
/** SYSTIMER_TARGET2_PERIOD:R/W；位位置：[29:0]；默认值：0；系统计时器target2报警周期
 */
#define SYSTIMER_TARGET2_PERIOD    0x3FFFFFFF
#define SYSTIMER_TARGET2_PERIOD_M  (SYSTIMER_TARGET2_PERIOD_V << SYSTIMER_TARGET2_PERIOD_S)
#define SYSTIMER_TARGET2_PERIOD_V  0x3FFFFFFF
#define SYSTIMER_TARGET2_PERIOD_S  0
/** SYSTIMER_TARGET2_PERIOD_MODE：R/W；位位置：[30]；默认值：0；系统计时器target2是否在周期模式下工作
 */
#define SYSTIMER_TARGET2_PERIOD_MODE    (BIT(30))
#define SYSTIMER_TARGET2_PERIOD_MODE_M  (SYSTIMER_TARGET2_PERIOD_MODE_V << SYSTIMER_TARGET2_PERIOD_MODE_S)
#define SYSTIMER_TARGET2_PERIOD_MODE_V  0x00000001
#define SYSTIMER_TARGET2_PERIOD_MODE_S  30
/** SYSTIMER_TARGET2_WORK_EN:R/W；位位置：[31]；默认值：0；系统计时器target2工作启用
 */
#define SYSTIMER_TARGET2_WORK_EN    (BIT(31))
#define SYSTIMER_TARGET2_WORK_EN_M  (SYSTIMER_TARGET2_WORK_EN_V << SYSTIMER_TARGET2_WORK_EN_S)
#define SYSTIMER_TARGET2_WORK_EN_V  0x00000001
#define SYSTIMER_TARGET2_WORK_EN_S  31

/** SYSTIMER_UPDATE_REG寄存器读取系统计时器值
 */
#define SYSTIMER_UPDATE_REG (DR_REG_SYSTIMER_BASE + 0x38)
/** SYSTIMER_TIMER_VALUE_VALID:RO；位位置：[30]；默认值：0；如果从寄存器中读取计时器值是有效的
 */
#define SYSTIMER_TIMER_VALUE_VALID    (BIT(30))
#define SYSTIMER_TIMER_VALUE_VALID_M  (SYSTIMER_TIMER_VALUE_VALID_V << SYSTIMER_TIMER_VALUE_VALID_S)
#define SYSTIMER_TIMER_VALUE_VALID_V  0x00000001
#define SYSTIMER_TIMER_VALUE_VALID_S  30
/** SYSTIMER_TIMER_UPDATE:WO；位位置：[31]；默认值：0；更新系统计时器值以注册
 */
#define SYSTIMER_TIMER_UPDATE    (BIT(31))
#define SYSTIMER_TIMER_UPDATE_M  (SYSTIMER_TIMER_UPDATE_V << SYSTIMER_TIMER_UPDATE_S)
#define SYSTIMER_TIMER_UPDATE_V  0x00000001
#define SYSTIMER_TIMER_UPDATE_S  31

/** SYSTIMER_VALUE_HI_REG寄存器系统定时器高32位
 */
#define SYSTIMER_VALUE_HI_REG (DR_REG_SYSTIMER_BASE + 0x3c)
/** SYSTIMER_TIMER_VALUE_HI:RO；位位置：[31:0]；默认值：0；系统计时器高32位
 */
#define SYSTIMER_TIMER_VALUE_HI    0xFFFFFFFF
#define SYSTIMER_TIMER_VALUE_HI_M  (SYSTIMER_TIMER_VALUE_HI_V << SYSTIMER_TIMER_VALUE_HI_S)
#define SYSTIMER_TIMER_VALUE_HI_V  0xFFFFFFFF
#define SYSTIMER_TIMER_VALUE_HI_S  0

/** SYSTIMER_VALUE_LO_REG寄存器系统计时器低32位
 */
#define SYSTIMER_VALUE_LO_REG (DR_REG_SYSTIMER_BASE + 0x40)
/** SYSTIMER_TIMER_VALUE_LO:RO；位位置：[31:0]；默认值：0；系统计时器低32位
 */
#define SYSTIMER_TIMER_VALUE_LO    0xFFFFFFFF
#define SYSTIMER_TIMER_VALUE_LO_M  (SYSTIMER_TIMER_VALUE_LO_V << SYSTIMER_TIMER_VALUE_LO_S)
#define SYSTIMER_TIMER_VALUE_LO_V  0xFFFFFFFF
#define SYSTIMER_TIMER_VALUE_LO_S  0

/** SYSTIMER_INT_ENA_REG寄存器系统定时器中断启用
 */
#define SYSTIMER_INT_ENA_REG (DR_REG_SYSTIMER_BASE + 0x44)
/** SYSTIMER_SYSTIMER_INT0_ENA:R/W；位位置：[0]；默认值：0；系统计时器target0中断启用
 */
#define SYSTIMER_SYSTIMER_INT0_ENA    (BIT(0))
#define SYSTIMER_SYSTIMER_INT0_ENA_M  (SYSTIMER_SYSTIMER_INT0_ENA_V << SYSTIMER_SYSTIMER_INT0_ENA_S)
#define SYSTIMER_SYSTIMER_INT0_ENA_V  0x00000001
#define SYSTIMER_SYSTIMER_INT0_ENA_S  0
/** SYSTIMER_SYSTIMER_INT1_ENA:R/W；位位置：[1]；默认值：0；系统计时器target1中断启用
 */
#define SYSTIMER_SYSTIMER_INT1_ENA    (BIT(1))
#define SYSTIMER_SYSTIMER_INT1_ENA_M  (SYSTIMER_SYSTIMER_INT1_ENA_V << SYSTIMER_SYSTIMER_INT1_ENA_S)
#define SYSTIMER_SYSTIMER_INT1_ENA_V  0x00000001
#define SYSTIMER_SYSTIMER_INT1_ENA_S  1
/** SYSTIMER_SYSTIMER_INT2_ENA:R/W；位位置：[2]；默认值：0；系统计时器target2中断启用
 */
#define SYSTIMER_SYSTIMER_INT2_ENA    (BIT(2))
#define SYSTIMER_SYSTIMER_INT2_ENA_M  (SYSTIMER_SYSTIMER_INT2_ENA_V << SYSTIMER_SYSTIMER_INT2_ENA_S)
#define SYSTIMER_SYSTIMER_INT2_ENA_V  0x00000001
#define SYSTIMER_SYSTIMER_INT2_ENA_S  2

/** SYSTIMER_INT_RAW_REG寄存器系统定时器中断原始
 */
#define SYSTIMER_INT_RAW_REG (DR_REG_SYSTIMER_BASE + 0x48)
/** SYSTIMER_SYSTIMER_INT0_RAW:RO；位位置：[0]；默认值：0；系统计时器target0中断原始
 */
#define SYSTIMER_SYSTIMER_INT0_RAW    (BIT(0))
#define SYSTIMER_SYSTIMER_INT0_RAW_M  (SYSTIMER_SYSTIMER_INT0_RAW_V << SYSTIMER_SYSTIMER_INT0_RAW_S)
#define SYSTIMER_SYSTIMER_INT0_RAW_V  0x00000001
#define SYSTIMER_SYSTIMER_INT0_RAW_S  0
/** SYSTIMER_SYSTIMER_INT1_RAW:RO；位位置：[1]；默认值：0；系统计时器target1中断原始
 */
#define SYSTIMER_SYSTIMER_INT1_RAW    (BIT(1))
#define SYSTIMER_SYSTIMER_INT1_RAW_M  (SYSTIMER_SYSTIMER_INT1_RAW_V << SYSTIMER_SYSTIMER_INT1_RAW_S)
#define SYSTIMER_SYSTIMER_INT1_RAW_V  0x00000001
#define SYSTIMER_SYSTIMER_INT1_RAW_S  1
/** SYSTIMER_SYSTIMER_INT2_RAW:RO；位位置：[2]；默认值：0；系统计时器target2中断原始
 */
#define SYSTIMER_SYSTIMER_INT2_RAW    (BIT(2))
#define SYSTIMER_SYSTIMER_INT2_RAW_M  (SYSTIMER_SYSTIMER_INT2_RAW_V << SYSTIMER_SYSTIMER_INT2_RAW_S)
#define SYSTIMER_SYSTIMER_INT2_RAW_V  0x00000001
#define SYSTIMER_SYSTIMER_INT2_RAW_S  2

/** SYSTIMER_INT_CLR_REG寄存器系统计时器中断清除
 */
#define SYSTIMER_INT_CLR_REG (DR_REG_SYSTIMER_BASE + 0x4c)
/** SYSTIMER_SYSTIMER_INT0_CLR:WO；位位置：[0]；默认值：0；系统计时器target0中断清除
 */
#define SYSTIMER_SYSTIMER_INT0_CLR    (BIT(0))
#define SYSTIMER_SYSTIMER_INT0_CLR_M  (SYSTIMER_SYSTIMER_INT0_CLR_V << SYSTIMER_SYSTIMER_INT0_CLR_S)
#define SYSTIMER_SYSTIMER_INT0_CLR_V  0x00000001
#define SYSTIMER_SYSTIMER_INT0_CLR_S  0
/** SYSTIMER_SYSTIMER_INT1_CLR:WO；位位置：[1]；默认值：0；系统计时器target1中断清除
 */
#define SYSTIMER_SYSTIMER_INT1_CLR    (BIT(1))
#define SYSTIMER_SYSTIMER_INT1_CLR_M  (SYSTIMER_SYSTIMER_INT1_CLR_V << SYSTIMER_SYSTIMER_INT1_CLR_S)
#define SYSTIMER_SYSTIMER_INT1_CLR_V  0x00000001
#define SYSTIMER_SYSTIMER_INT1_CLR_S  1
/** SYSTIMER_SYSTIMER_INT2_CLR:WO；位位置：[2]；默认值：0；系统计时器target2中断清除
 */
#define SYSTIMER_SYSTIMER_INT2_CLR    (BIT(2))
#define SYSTIMER_SYSTIMER_INT2_CLR_M  (SYSTIMER_SYSTIMER_INT2_CLR_V << SYSTIMER_SYSTIMER_INT2_CLR_S)
#define SYSTIMER_SYSTIMER_INT2_CLR_V  0x00000001
#define SYSTIMER_SYSTIMER_INT2_CLR_S  2

/** SYSTIMER_DATE_REG寄存器系统计时器寄存器版本
 */
#define SYSTIMER_DATE_REG (DR_REG_SYSTIMER_BASE + 0xfc)
/** 系统日期：R/W；位位置：[31:0]；默认值：25194848；系统计时器寄存器版本
 */
#define SYSTIMER_DATE    0xFFFFFFFF
#define SYSTIMER_DATE_M  (SYSTIMER_DATE_V << SYSTIMER_DATE_S)
#define SYSTIMER_DATE_V  0xFFFFFFFF
#define SYSTIMER_DATE_S  0

#ifdef __cplusplus
}
#endif

