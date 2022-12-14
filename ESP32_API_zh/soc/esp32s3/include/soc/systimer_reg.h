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
/** SYSTIMER_SYSTIMER_CLK_FO:R/W；位位置：[0]；默认值：0；系统时钟力开启
 */
#define SYSTIMER_SYSTIMER_CLK_FO    (BIT(0))
#define SYSTIMER_SYSTIMER_CLK_FO_M  (SYSTIMER_SYSTIMER_CLK_FO_V << SYSTIMER_SYSTIMER_CLK_FO_S)
#define SYSTIMER_SYSTIMER_CLK_FO_V  0x00000001
#define SYSTIMER_SYSTIMER_CLK_FO_S  0
/** SYSTIMER_TARGET2_WORK_EN:R/W；位位置：[22]；默认值：0；target2工作启用
 */
#define SYSTIMER_TARGET2_WORK_EN    (BIT(22))
#define SYSTIMER_TARGET2_WORK_EN_M  (SYSTIMER_TARGET2_WORK_EN_V << SYSTIMER_TARGET2_WORK_EN_S)
#define SYSTIMER_TARGET2_WORK_EN_V  0x00000001
#define SYSTIMER_TARGET2_WORK_EN_S  22
/** SYSTIMER_TARGET1_WORK_EN:R/W；位位置：[23]；默认值：0；target1工作启用
 */
#define SYSTIMER_TARGET1_WORK_EN    (BIT(23))
#define SYSTIMER_TARGET1_WORK_EN_M  (SYSTIMER_TARGET1_WORK_EN_V << SYSTIMER_TARGET1_WORK_EN_S)
#define SYSTIMER_TARGET1_WORK_EN_V  0x00000001
#define SYSTIMER_TARGET1_WORK_EN_S  23
/** SYSTIMER_TARGET0_WORK_EN:R/W；位位置：[24]；默认值：0；target0工作启用
 */
#define SYSTIMER_TARGET0_WORK_EN    (BIT(24))
#define SYSTIMER_TARGET0_WORK_EN_M  (SYSTIMER_TARGET0_WORK_EN_V << SYSTIMER_TARGET0_WORK_EN_S)
#define SYSTIMER_TARGET0_WORK_EN_V  0x00000001
#define SYSTIMER_TARGET0_WORK_EN_S  24
/** SYSTIMER_TIMER_UNIT1_CORE1_STALL_EN:右侧；位位置：[25]；默认值：1；如果核心1暂停时计时器第一单元暂停
 */
#define SYSTIMER_TIMER_UNIT1_CORE1_STALL_EN    (BIT(25))
#define SYSTIMER_TIMER_UNIT1_CORE1_STALL_EN_M  (SYSTIMER_TIMER_UNIT1_CORE1_STALL_EN_V << SYSTIMER_TIMER_UNIT1_CORE1_STALL_EN_S)
#define SYSTIMER_TIMER_UNIT1_CORE1_STALL_EN_V  0x00000001
#define SYSTIMER_TIMER_UNIT1_CORE1_STALL_EN_S  25
/** SYSTIMER_TIMER_UNIT1_CORE0_STALL_EN:右侧；位位置：[26]；默认值：1；如果核心0停止时计时器第一单元停止
 */
#define SYSTIMER_TIMER_UNIT1_CORE0_STALL_EN    (BIT(26))
#define SYSTIMER_TIMER_UNIT1_CORE0_STALL_EN_M  (SYSTIMER_TIMER_UNIT1_CORE0_STALL_EN_V << SYSTIMER_TIMER_UNIT1_CORE0_STALL_EN_S)
#define SYSTIMER_TIMER_UNIT1_CORE0_STALL_EN_V  0x00000001
#define SYSTIMER_TIMER_UNIT1_CORE0_STALL_EN_S  26
/** SYSTIMER_TIMER_UNIT0_CORE1_install_EN:R/W；位位置：[27]；默认值：0；如果内核1停止时计时器单元0停止
 */
#define SYSTIMER_TIMER_UNIT0_CORE1_STALL_EN    (BIT(27))
#define SYSTIMER_TIMER_UNIT0_CORE1_STALL_EN_M  (SYSTIMER_TIMER_UNIT0_CORE1_STALL_EN_V << SYSTIMER_TIMER_UNIT0_CORE1_STALL_EN_S)
#define SYSTIMER_TIMER_UNIT0_CORE1_STALL_EN_V  0x00000001
#define SYSTIMER_TIMER_UNIT0_CORE1_STALL_EN_S  27
/** SYSTIMER_TIMER_UNIT0_CORE0_install_EN:R/W；位位置：[28]；默认值：0；如果内核0停止时计时器单元0停止
 */
#define SYSTIMER_TIMER_UNIT0_CORE0_STALL_EN    (BIT(28))
#define SYSTIMER_TIMER_UNIT0_CORE0_STALL_EN_M  (SYSTIMER_TIMER_UNIT0_CORE0_STALL_EN_V << SYSTIMER_TIMER_UNIT0_CORE0_STALL_EN_S)
#define SYSTIMER_TIMER_UNIT0_CORE0_STALL_EN_V  0x00000001
#define SYSTIMER_TIMER_UNIT0_CORE0_STALL_EN_S  28
/** SYSTIMER_TIMER_UNIT1_WORK_EN:R/W；位位置：[29]；默认值：0；定时器第一单元工作启用
 */
#define SYSTIMER_TIMER_UNIT1_WORK_EN    (BIT(29))
#define SYSTIMER_TIMER_UNIT1_WORK_EN_M  (SYSTIMER_TIMER_UNIT1_WORK_EN_V << SYSTIMER_TIMER_UNIT1_WORK_EN_S)
#define SYSTIMER_TIMER_UNIT1_WORK_EN_V  0x00000001
#define SYSTIMER_TIMER_UNIT1_WORK_EN_S  29
/** SYSTIMER_TIMER_UNIT0_WORK_EN:R/W；位位置：[30]；默认值：1；计时器单元0工作启用
 */
#define SYSTIMER_TIMER_UNIT0_WORK_EN    (BIT(30))
#define SYSTIMER_TIMER_UNIT0_WORK_EN_M  (SYSTIMER_TIMER_UNIT0_WORK_EN_V << SYSTIMER_TIMER_UNIT0_WORK_EN_S)
#define SYSTIMER_TIMER_UNIT0_WORK_EN_V  0x00000001
#define SYSTIMER_TIMER_UNIT0_WORK_EN_S  30
/** SYSTIMER_CLK_EN:R/W；位位置：[31]；默认值：0；寄存器文件clk门控
 */
#define SYSTIMER_CLK_EN    (BIT(31))
#define SYSTIMER_CLK_EN_M  (SYSTIMER_CLK_EN_V << SYSTIMER_CLK_EN_S)
#define SYSTIMER_CLK_EN_V  0x00000001
#define SYSTIMER_CLK_EN_S  31

/** SYSTIMER_UNIT0_OP_REG寄存器系统计时器单元0值更新寄存器
 */
#define SYSTIMER_UNIT0_OP_REG (DR_REG_SYSTIMER_BASE + 0x4)
/** SYSTIMER_TIMER_UNIT0_VALUE_VALID:R/SS/WTC；位位置：[29]；默认值：0；计时器值同步且有效
 */
#define SYSTIMER_TIMER_UNIT0_VALUE_VALID    (BIT(29))
#define SYSTIMER_TIMER_UNIT0_VALUE_VALID_M  (SYSTIMER_TIMER_UNIT0_VALUE_VALID_V << SYSTIMER_TIMER_UNIT0_VALUE_VALID_S)
#define SYSTIMER_TIMER_UNIT0_VALUE_VALID_V  0x00000001
#define SYSTIMER_TIMER_UNIT0_VALUE_VALID_S  29
/** SYSTIMER_TIMER_UNIT0_UPDATE:WT；位位置：[30]；默认值：0；更新timer_unit0
 */
#define SYSTIMER_TIMER_UNIT0_UPDATE    (BIT(30))
#define SYSTIMER_TIMER_UNIT0_UPDATE_M  (SYSTIMER_TIMER_UNIT0_UPDATE_V << SYSTIMER_TIMER_UNIT0_UPDATE_S)
#define SYSTIMER_TIMER_UNIT0_UPDATE_V  0x00000001
#define SYSTIMER_TIMER_UNIT0_UPDATE_S  30

/** SYSTIMER_UNIT1_OP_REG寄存器系统计时器第一单元值更新寄存器
 */
#define SYSTIMER_UNIT1_OP_REG (DR_REG_SYSTIMER_BASE + 0x8)
/** SYSTIMER_TIMER_UNIT1_VALUE_VALID:R/SS/WTC；位位置：[29]；默认值：0；计时器值同步且有效
 */
#define SYSTIMER_TIMER_UNIT1_VALUE_VALID    (BIT(29))
#define SYSTIMER_TIMER_UNIT1_VALUE_VALID_M  (SYSTIMER_TIMER_UNIT1_VALUE_VALID_V << SYSTIMER_TIMER_UNIT1_VALUE_VALID_S)
#define SYSTIMER_TIMER_UNIT1_VALUE_VALID_V  0x00000001
#define SYSTIMER_TIMER_UNIT1_VALUE_VALID_S  29
/** SYSTIMER_TIMER_UNIT1_UPDATE:WT；位位置：[30]；默认值：0；更新计时器第一单元
 */
#define SYSTIMER_TIMER_UNIT1_UPDATE    (BIT(30))
#define SYSTIMER_TIMER_UNIT1_UPDATE_M  (SYSTIMER_TIMER_UNIT1_UPDATE_V << SYSTIMER_TIMER_UNIT1_UPDATE_S)
#define SYSTIMER_TIMER_UNIT1_UPDATE_V  0x00000001
#define SYSTIMER_TIMER_UNIT1_UPDATE_S  30

/** SYSTIMER_UNIT0_LOAD_HI_REG寄存器系统计时器单元0值高负载寄存器
 */
#define SYSTIMER_UNIT0_LOAD_HI_REG (DR_REG_SYSTIMER_BASE + 0xc)
/** SYSTIMER_TIMER_UNIT0_LOAD_HI:R/W；比特位置：[19:0]；默认值：0；计时器单元0加载高20位
 */
#define SYSTIMER_TIMER_UNIT0_LOAD_HI    0x000FFFFF
#define SYSTIMER_TIMER_UNIT0_LOAD_HI_M  (SYSTIMER_TIMER_UNIT0_LOAD_HI_V << SYSTIMER_TIMER_UNIT0_LOAD_HI_S)
#define SYSTIMER_TIMER_UNIT0_LOAD_HI_V  0x000FFFFF
#define SYSTIMER_TIMER_UNIT0_LOAD_HI_S  0

/** SYSTIMER_UNIT0_LOAD_LO_REG寄存器系统计时器单元0值低负载寄存器
 */
#define SYSTIMER_UNIT0_LOAD_LO_REG (DR_REG_SYSTIMER_BASE + 0x10)
/** SYSTIMER_TIMER_UNIT0_LOAD_LO:R/W；位位置：[31:0]；默认值：0；计时器单元0负载低32位
 */
#define SYSTIMER_TIMER_UNIT0_LOAD_LO    0xFFFFFFFF
#define SYSTIMER_TIMER_UNIT0_LOAD_LO_M  (SYSTIMER_TIMER_UNIT0_LOAD_LO_V << SYSTIMER_TIMER_UNIT0_LOAD_LO_S)
#define SYSTIMER_TIMER_UNIT0_LOAD_LO_V  0xFFFFFFFF
#define SYSTIMER_TIMER_UNIT0_LOAD_LO_S  0

/** SYSTIMER_UNIT1_LOAD_HI_REG寄存器系统计时器第一单元值高负载寄存器
 */
#define SYSTIMER_UNIT1_LOAD_HI_REG (DR_REG_SYSTIMER_BASE + 0x14)
/** SYSTIMER_TIMER_UNIT1_LOAD_HI:R/W；比特位置：[19:0]；默认值：0；定时器第一单元负载高20位
 */
#define SYSTIMER_TIMER_UNIT1_LOAD_HI    0x000FFFFF
#define SYSTIMER_TIMER_UNIT1_LOAD_HI_M  (SYSTIMER_TIMER_UNIT1_LOAD_HI_V << SYSTIMER_TIMER_UNIT1_LOAD_HI_S)
#define SYSTIMER_TIMER_UNIT1_LOAD_HI_V  0x000FFFFF
#define SYSTIMER_TIMER_UNIT1_LOAD_HI_S  0

/** SYSTIMER_UNIT1_LOAD_LO_REG寄存器系统计时器第一单元值低负载寄存器
 */
#define SYSTIMER_UNIT1_LOAD_LO_REG (DR_REG_SYSTIMER_BASE + 0x18)
/** SYSTIMER_TIMER_UNIT1_LOAD_LO:R/W；位位置：[31:0]；默认值：0；定时器第一单元负载低32位
 */
#define SYSTIMER_TIMER_UNIT1_LOAD_LO    0xFFFFFFFF
#define SYSTIMER_TIMER_UNIT1_LOAD_LO_M  (SYSTIMER_TIMER_UNIT1_LOAD_LO_V << SYSTIMER_TIMER_UNIT1_LOAD_LO_S)
#define SYSTIMER_TIMER_UNIT1_LOAD_LO_V  0xFFFFFFFF
#define SYSTIMER_TIMER_UNIT1_LOAD_LO_S  0

/** SYSTIMER_TARGET0_HI_REG寄存器系统计时器comp0值高寄存器
 */
#define SYSTIMER_TARGET0_HI_REG (DR_REG_SYSTIMER_BASE + 0x1c)
/** SYSTIMER_TIMER_TARGET0_HI:R/W；比特位置：[19:0]；默认值：0；计时器taget0高20位
 */
#define SYSTIMER_TIMER_TARGET0_HI    0x000FFFFF
#define SYSTIMER_TIMER_TARGET0_HI_M  (SYSTIMER_TIMER_TARGET0_HI_V << SYSTIMER_TIMER_TARGET0_HI_S)
#define SYSTIMER_TIMER_TARGET0_HI_V  0x000FFFFF
#define SYSTIMER_TIMER_TARGET0_HI_S  0

/** SYSTIMER_TARGET0_LO_REG寄存器系统计时器comp0值低寄存器
 */
#define SYSTIMER_TARGET0_LO_REG (DR_REG_SYSTIMER_BASE + 0x20)
/** SYSTIMER_TIMER_TARGET0_LO:R/W；位位置：[31:0]；默认值：0；计时器taget0低32位
 */
#define SYSTIMER_TIMER_TARGET0_LO    0xFFFFFFFF
#define SYSTIMER_TIMER_TARGET0_LO_M  (SYSTIMER_TIMER_TARGET0_LO_V << SYSTIMER_TIMER_TARGET0_LO_S)
#define SYSTIMER_TIMER_TARGET0_LO_V  0xFFFFFFFF
#define SYSTIMER_TIMER_TARGET0_LO_S  0

/** SYSTIMER_TARGET1_HI_REG寄存器系统计时器comp1值高寄存器
 */
#define SYSTIMER_TARGET1_HI_REG (DR_REG_SYSTIMER_BASE + 0x24)
/** SYSTIMER_TIMER_TARGET1_HI:R/W；比特位置：[19:0]；默认值：0；计时器taget1高20位
 */
#define SYSTIMER_TIMER_TARGET1_HI    0x000FFFFF
#define SYSTIMER_TIMER_TARGET1_HI_M  (SYSTIMER_TIMER_TARGET1_HI_V << SYSTIMER_TIMER_TARGET1_HI_S)
#define SYSTIMER_TIMER_TARGET1_HI_V  0x000FFFFF
#define SYSTIMER_TIMER_TARGET1_HI_S  0

/** SYSTIMER_TARGET1_LO_REG寄存器系统计时器comp1值低寄存器
 */
#define SYSTIMER_TARGET1_LO_REG (DR_REG_SYSTIMER_BASE + 0x28)
/** SYSTIMER_TIMER_TARGET1_LO:R/W；位位置：[31:0]；默认值：0；计时器taget1低32位
 */
#define SYSTIMER_TIMER_TARGET1_LO    0xFFFFFFFF
#define SYSTIMER_TIMER_TARGET1_LO_M  (SYSTIMER_TIMER_TARGET1_LO_V << SYSTIMER_TIMER_TARGET1_LO_S)
#define SYSTIMER_TIMER_TARGET1_LO_V  0xFFFFFFFF
#define SYSTIMER_TIMER_TARGET1_LO_S  0

/** SYSTIMER_TARGET2_HI_REG寄存器系统计时器comp2值高寄存器
 */
#define SYSTIMER_TARGET2_HI_REG (DR_REG_SYSTIMER_BASE + 0x2c)
/** SYSTIMER_TIMER_TARGET2_HI:R/W；比特位置：[19:0]；默认值：0；计时器taget2高20位
 */
#define SYSTIMER_TIMER_TARGET2_HI    0x000FFFFF
#define SYSTIMER_TIMER_TARGET2_HI_M  (SYSTIMER_TIMER_TARGET2_HI_V << SYSTIMER_TIMER_TARGET2_HI_S)
#define SYSTIMER_TIMER_TARGET2_HI_V  0x000FFFFF
#define SYSTIMER_TIMER_TARGET2_HI_S  0

/** SYSTIMER_TARGET2_LO_REG寄存器系统计时器comp2值低寄存器
 */
#define SYSTIMER_TARGET2_LO_REG (DR_REG_SYSTIMER_BASE + 0x30)
/** SYSTIMER_TIMER_TARGET2_LO:R/W；位位置：[31:0]；默认值：0；计时器taget2低32位
 */
#define SYSTIMER_TIMER_TARGET2_LO    0xFFFFFFFF
#define SYSTIMER_TIMER_TARGET2_LO_M  (SYSTIMER_TIMER_TARGET2_LO_V << SYSTIMER_TIMER_TARGET2_LO_S)
#define SYSTIMER_TIMER_TARGET2_LO_V  0xFFFFFFFF
#define SYSTIMER_TIMER_TARGET2_LO_S  0

/** SYSTIMER_TARGET0_CONF_REG寄存器系统计时器comp0目标模式寄存器
 */
#define SYSTIMER_TARGET0_CONF_REG (DR_REG_SYSTIMER_BASE + 0x34)
/** SYSTIMER_TARGET0_周期：R/W；位位置：[25:0]；默认值：0；target0周期
 */
#define SYSTIMER_TARGET0_PERIOD    0x03FFFFFF
#define SYSTIMER_TARGET0_PERIOD_M  (SYSTIMER_TARGET0_PERIOD_V << SYSTIMER_TARGET0_PERIOD_S)
#define SYSTIMER_TARGET0_PERIOD_V  0x03FFFFFF
#define SYSTIMER_TARGET0_PERIOD_S  0
/** 系统目标周期模式：R/W；位位置：[30]；默认值：0；将target0设置为周期模式
 */
#define SYSTIMER_TARGET0_PERIOD_MODE    (BIT(30))
#define SYSTIMER_TARGET0_PERIOD_MODE_M  (SYSTIMER_TARGET0_PERIOD_MODE_V << SYSTIMER_TARGET0_PERIOD_MODE_S)
#define SYSTIMER_TARGET0_PERIOD_MODE_V  0x00000001
#define SYSTIMER_TARGET0_PERIOD_MODE_S  30
/** SYSTIMER_TARGET0_TIMER_UNIT_SEL:R/W；位位置：[31]；默认值：0；选择要比较的单位
 */
#define SYSTIMER_TARGET0_TIMER_UNIT_SEL    (BIT(31))
#define SYSTIMER_TARGET0_TIMER_UNIT_SEL_M  (SYSTIMER_TARGET0_TIMER_UNIT_SEL_V << SYSTIMER_TARGET0_TIMER_UNIT_SEL_S)
#define SYSTIMER_TARGET0_TIMER_UNIT_SEL_V  0x00000001
#define SYSTIMER_TARGET0_TIMER_UNIT_SEL_S  31

/** SYSTIMER_TARGET1_CONF_REG寄存器系统计时器comp1目标模式寄存器
 */
#define SYSTIMER_TARGET1_CONF_REG (DR_REG_SYSTIMER_BASE + 0x38)
/** SYSTIMER_TARGET1_PERIOD:R/W；位位置：[25:0]；默认值：0；目标1周期
 */
#define SYSTIMER_TARGET1_PERIOD    0x03FFFFFF
#define SYSTIMER_TARGET1_PERIOD_M  (SYSTIMER_TARGET1_PERIOD_V << SYSTIMER_TARGET1_PERIOD_S)
#define SYSTIMER_TARGET1_PERIOD_V  0x03FFFFFF
#define SYSTIMER_TARGET1_PERIOD_S  0
/** SYSTIMER_TARGET1_PERIOD_MODE：R/W；位位置：[30]；默认值：0；将target1设置为周期模式
 */
#define SYSTIMER_TARGET1_PERIOD_MODE    (BIT(30))
#define SYSTIMER_TARGET1_PERIOD_MODE_M  (SYSTIMER_TARGET1_PERIOD_MODE_V << SYSTIMER_TARGET1_PERIOD_MODE_S)
#define SYSTIMER_TARGET1_PERIOD_MODE_V  0x00000001
#define SYSTIMER_TARGET1_PERIOD_MODE_S  30
/** SYSTIMER_TARGET1_TIMER_UNIT_SEL:R/W；位位置：[31]；默认值：0；选择要比较的单位
 */
#define SYSTIMER_TARGET1_TIMER_UNIT_SEL    (BIT(31))
#define SYSTIMER_TARGET1_TIMER_UNIT_SEL_M  (SYSTIMER_TARGET1_TIMER_UNIT_SEL_V << SYSTIMER_TARGET1_TIMER_UNIT_SEL_S)
#define SYSTIMER_TARGET1_TIMER_UNIT_SEL_V  0x00000001
#define SYSTIMER_TARGET1_TIMER_UNIT_SEL_S  31

/** SYSTIMER_TARGET2_CONF_REG寄存器系统计时器comp2目标模式寄存器
 */
#define SYSTIMER_TARGET2_CONF_REG (DR_REG_SYSTIMER_BASE + 0x3c)
/** SYSTIMER_TARGET2_PERIOD:R/W；位位置：[25:0]；默认值：0；target2周期
 */
#define SYSTIMER_TARGET2_PERIOD    0x03FFFFFF
#define SYSTIMER_TARGET2_PERIOD_M  (SYSTIMER_TARGET2_PERIOD_V << SYSTIMER_TARGET2_PERIOD_S)
#define SYSTIMER_TARGET2_PERIOD_V  0x03FFFFFF
#define SYSTIMER_TARGET2_PERIOD_S  0
/** SYSTIMER_TARGET2_PERIOD_MODE：R/W；位位置：[30]；默认值：0；将target2设置为周期模式
 */
#define SYSTIMER_TARGET2_PERIOD_MODE    (BIT(30))
#define SYSTIMER_TARGET2_PERIOD_MODE_M  (SYSTIMER_TARGET2_PERIOD_MODE_V << SYSTIMER_TARGET2_PERIOD_MODE_S)
#define SYSTIMER_TARGET2_PERIOD_MODE_V  0x00000001
#define SYSTIMER_TARGET2_PERIOD_MODE_S  30
/** SYSTIMER_TARGET2_TIMER_UNIT_SEL:R/W；位位置：[31]；默认值：0；选择要比较的单位
 */
#define SYSTIMER_TARGET2_TIMER_UNIT_SEL    (BIT(31))
#define SYSTIMER_TARGET2_TIMER_UNIT_SEL_M  (SYSTIMER_TARGET2_TIMER_UNIT_SEL_V << SYSTIMER_TARGET2_TIMER_UNIT_SEL_S)
#define SYSTIMER_TARGET2_TIMER_UNIT_SEL_V  0x00000001
#define SYSTIMER_TARGET2_TIMER_UNIT_SEL_S  31

/** SYSTIMER_UNIT0_VALUE_HI_REG寄存器系统计时器单元0值高寄存器
 */
#define SYSTIMER_UNIT0_VALUE_HI_REG (DR_REG_SYSTIMER_BASE + 0x40)
/** SYSTIMER_TIMER_UNIT0_VALUE_HI:RO；比特位置：[19:0]；默认值：0；计时器读取值高20位
 */
#define SYSTIMER_TIMER_UNIT0_VALUE_HI    0x000FFFFF
#define SYSTIMER_TIMER_UNIT0_VALUE_HI_M  (SYSTIMER_TIMER_UNIT0_VALUE_HI_V << SYSTIMER_TIMER_UNIT0_VALUE_HI_S)
#define SYSTIMER_TIMER_UNIT0_VALUE_HI_V  0x000FFFFF
#define SYSTIMER_TIMER_UNIT0_VALUE_HI_S  0

/** SYSTIMER_UNIT0_VALUE_LO_REG寄存器系统计时器单元0值低寄存器
 */
#define SYSTIMER_UNIT0_VALUE_LO_REG (DR_REG_SYSTIMER_BASE + 0x44)
/** SYSTIMER_TIMER_UNIT0_VALUE_LO:RO；位位置：[31:0]；默认值：0；计时器读取值低32位
 */
#define SYSTIMER_TIMER_UNIT0_VALUE_LO    0xFFFFFFFF
#define SYSTIMER_TIMER_UNIT0_VALUE_LO_M  (SYSTIMER_TIMER_UNIT0_VALUE_LO_V << SYSTIMER_TIMER_UNIT0_VALUE_LO_S)
#define SYSTIMER_TIMER_UNIT0_VALUE_LO_V  0xFFFFFFFF
#define SYSTIMER_TIMER_UNIT0_VALUE_LO_S  0

/** SYSTIMER_UNIT1_VALUE_HI_REG寄存器系统计时器第一单元值高位寄存器
 */
#define SYSTIMER_UNIT1_VALUE_HI_REG (DR_REG_SYSTIMER_BASE + 0x48)
/** SYSTIMER_TIMER_UNIT1_VALUE_HI:RO；比特位置：[19:0]；默认值：0；计时器读取值高20位
 */
#define SYSTIMER_TIMER_UNIT1_VALUE_HI    0x000FFFFF
#define SYSTIMER_TIMER_UNIT1_VALUE_HI_M  (SYSTIMER_TIMER_UNIT1_VALUE_HI_V << SYSTIMER_TIMER_UNIT1_VALUE_HI_S)
#define SYSTIMER_TIMER_UNIT1_VALUE_HI_V  0x000FFFFF
#define SYSTIMER_TIMER_UNIT1_VALUE_HI_S  0

/** SYSTIMER_UNIT1_VALUE_LO_REG寄存器系统计时器第一单元值低寄存器
 */
#define SYSTIMER_UNIT1_VALUE_LO_REG (DR_REG_SYSTIMER_BASE + 0x4c)
/** SYSTIMER_TIMER_UNIT1_VALUE_LO:RO；位位置：[31:0]；默认值：0；计时器读取值低32位
 */
#define SYSTIMER_TIMER_UNIT1_VALUE_LO    0xFFFFFFFF
#define SYSTIMER_TIMER_UNIT1_VALUE_LO_M  (SYSTIMER_TIMER_UNIT1_VALUE_LO_V << SYSTIMER_TIMER_UNIT1_VALUE_LO_S)
#define SYSTIMER_TIMER_UNIT1_VALUE_LO_V  0xFFFFFFFF
#define SYSTIMER_TIMER_UNIT1_VALUE_LO_S  0

/** SYSTIMER_COMP0_LOAD_REG寄存器系统计时器COMP0 conf同步寄存器
 */
#define SYSTIMER_COMP0_LOAD_REG (DR_REG_SYSTIMER_BASE + 0x50)
/** SYSTIMER_TIMER_COMP0_LOAD:WT；位位置：[0]；默认值：0；定时器comp0同步使能信号
 */
#define SYSTIMER_TIMER_COMP0_LOAD    (BIT(0))
#define SYSTIMER_TIMER_COMP0_LOAD_M  (SYSTIMER_TIMER_COMP0_LOAD_V << SYSTIMER_TIMER_COMP0_LOAD_S)
#define SYSTIMER_TIMER_COMP0_LOAD_V  0x00000001
#define SYSTIMER_TIMER_COMP0_LOAD_S  0

/** SYSTIMER_COMP1_LOAD_REG寄存器系统计时器COMP1 conf同步寄存器
 */
#define SYSTIMER_COMP1_LOAD_REG (DR_REG_SYSTIMER_BASE + 0x54)
/** SYSTIMER_TIMER_COMP1_LOAD:WT；位位置：[0]；默认值：0；定时器comp1同步使能信号
 */
#define SYSTIMER_TIMER_COMP1_LOAD    (BIT(0))
#define SYSTIMER_TIMER_COMP1_LOAD_M  (SYSTIMER_TIMER_COMP1_LOAD_V << SYSTIMER_TIMER_COMP1_LOAD_S)
#define SYSTIMER_TIMER_COMP1_LOAD_V  0x00000001
#define SYSTIMER_TIMER_COMP1_LOAD_S  0

/** SYSTIMER_COMP2_LOAD_REG寄存器系统计时器COMP2 conf同步寄存器
 */
#define SYSTIMER_COMP2_LOAD_REG (DR_REG_SYSTIMER_BASE + 0x58)
/** SYSTIMER_TIMER_COMP2_LOAD:WT；位位置：[0]；默认值：0；定时器comp2同步使能信号
 */
#define SYSTIMER_TIMER_COMP2_LOAD    (BIT(0))
#define SYSTIMER_TIMER_COMP2_LOAD_M  (SYSTIMER_TIMER_COMP2_LOAD_V << SYSTIMER_TIMER_COMP2_LOAD_S)
#define SYSTIMER_TIMER_COMP2_LOAD_V  0x00000001
#define SYSTIMER_TIMER_COMP2_LOAD_S  0

/** SYSTIMER_UNIT0_LOAD_REG寄存器系统计时器单元0 conf同步寄存器
 */
#define SYSTIMER_UNIT0_LOAD_REG (DR_REG_SYSTIMER_BASE + 0x5c)
/** SYSTIMER_TIMER_UNIT0_LOAD:WT；位位置：[0]；默认值：0；定时器单元0同步使能信号
 */
#define SYSTIMER_TIMER_UNIT0_LOAD    (BIT(0))
#define SYSTIMER_TIMER_UNIT0_LOAD_M  (SYSTIMER_TIMER_UNIT0_LOAD_V << SYSTIMER_TIMER_UNIT0_LOAD_S)
#define SYSTIMER_TIMER_UNIT0_LOAD_V  0x00000001
#define SYSTIMER_TIMER_UNIT0_LOAD_S  0

/** SYSTIMER_UNIT1_LOAD_REG寄存器系统计时器第一单元conf同步寄存器
 */
#define SYSTIMER_UNIT1_LOAD_REG (DR_REG_SYSTIMER_BASE + 0x60)
/** SYSTIMER_TIMER_UNIT1_LOAD:WT；位位置：[0]；默认值：0；定时器第一单元同步启用信号
 */
#define SYSTIMER_TIMER_UNIT1_LOAD    (BIT(0))
#define SYSTIMER_TIMER_UNIT1_LOAD_M  (SYSTIMER_TIMER_UNIT1_LOAD_V << SYSTIMER_TIMER_UNIT1_LOAD_S)
#define SYSTIMER_TIMER_UNIT1_LOAD_V  0x00000001
#define SYSTIMER_TIMER_UNIT1_LOAD_S  0

/** SYSTIMER_INT_ENA_REG寄存器SYSTIMER中断启用寄存器
 */
#define SYSTIMER_INT_ENA_REG (DR_REG_SYSTIMER_BASE + 0x64)
/** SYSTIMER_TARGET0_INT_ENA:R/W；位位置：[0]；默认值：0；interupt0启用
 */
#define SYSTIMER_TARGET0_INT_ENA    (BIT(0))
#define SYSTIMER_TARGET0_INT_ENA_M  (SYSTIMER_TARGET0_INT_ENA_V << SYSTIMER_TARGET0_INT_ENA_S)
#define SYSTIMER_TARGET0_INT_ENA_V  0x00000001
#define SYSTIMER_TARGET0_INT_ENA_S  0
/** SYSTIMER_TARGET1_INT_ENA:R/W；位位置：[1]；默认值：0；interupt1启用
 */
#define SYSTIMER_TARGET1_INT_ENA    (BIT(1))
#define SYSTIMER_TARGET1_INT_ENA_M  (SYSTIMER_TARGET1_INT_ENA_V << SYSTIMER_TARGET1_INT_ENA_S)
#define SYSTIMER_TARGET1_INT_ENA_V  0x00000001
#define SYSTIMER_TARGET1_INT_ENA_S  1
/** SYSTIMER_TARGET2_INT_ENA:R/W；位位置：[2]；默认值：0；interupt2启用
 */
#define SYSTIMER_TARGET2_INT_ENA    (BIT(2))
#define SYSTIMER_TARGET2_INT_ENA_M  (SYSTIMER_TARGET2_INT_ENA_V << SYSTIMER_TARGET2_INT_ENA_S)
#define SYSTIMER_TARGET2_INT_ENA_V  0x00000001
#define SYSTIMER_TARGET2_INT_ENA_S  2

/** SYSTIMER_INT_RAW_REG寄存器SYSTIMER中断原始寄存器
 */
#define SYSTIMER_INT_RAW_REG (DR_REG_SYSTIMER_BASE + 0x68)
/** SYSTIMER_TARGET0_INT_RAW:R/WTC/SS；位位置：[0]；默认值：0；中断0原始
 */
#define SYSTIMER_TARGET0_INT_RAW    (BIT(0))
#define SYSTIMER_TARGET0_INT_RAW_M  (SYSTIMER_TARGET0_INT_RAW_V << SYSTIMER_TARGET0_INT_RAW_S)
#define SYSTIMER_TARGET0_INT_RAW_V  0x00000001
#define SYSTIMER_TARGET0_INT_RAW_S  0
/** SYSTIMER_TARGET1_INT_RAW:R/WTC/SS；位位置：[1]；默认值：0；中断1原始
 */
#define SYSTIMER_TARGET1_INT_RAW    (BIT(1))
#define SYSTIMER_TARGET1_INT_RAW_M  (SYSTIMER_TARGET1_INT_RAW_V << SYSTIMER_TARGET1_INT_RAW_S)
#define SYSTIMER_TARGET1_INT_RAW_V  0x00000001
#define SYSTIMER_TARGET1_INT_RAW_S  1
/** SYSTIMER_TARGET2_INT_RAW:R/WTC/SS；位位置：[2]；默认值：0；中断2原始
 */
#define SYSTIMER_TARGET2_INT_RAW    (BIT(2))
#define SYSTIMER_TARGET2_INT_RAW_M  (SYSTIMER_TARGET2_INT_RAW_V << SYSTIMER_TARGET2_INT_RAW_S)
#define SYSTIMER_TARGET2_INT_RAW_V  0x00000001
#define SYSTIMER_TARGET2_INT_RAW_S  2

/** SYSTIMER_INT_CLR_REG寄存器SYSTIMER中断清除寄存器
 */
#define SYSTIMER_INT_CLR_REG (DR_REG_SYSTIMER_BASE + 0x6c)
/** SYSTIMER_TARGET0_INT_CLR:WT；位位置：[0]；默认值：0；中断0清除
 */
#define SYSTIMER_TARGET0_INT_CLR    (BIT(0))
#define SYSTIMER_TARGET0_INT_CLR_M  (SYSTIMER_TARGET0_INT_CLR_V << SYSTIMER_TARGET0_INT_CLR_S)
#define SYSTIMER_TARGET0_INT_CLR_V  0x00000001
#define SYSTIMER_TARGET0_INT_CLR_S  0
/** SYSTIMER_TARGET1_INT_CLR:WT；位位置：[1]；默认值：0；中断1清除
 */
#define SYSTIMER_TARGET1_INT_CLR    (BIT(1))
#define SYSTIMER_TARGET1_INT_CLR_M  (SYSTIMER_TARGET1_INT_CLR_V << SYSTIMER_TARGET1_INT_CLR_S)
#define SYSTIMER_TARGET1_INT_CLR_V  0x00000001
#define SYSTIMER_TARGET1_INT_CLR_S  1
/** SYSTIMER_TARGET2_INT_CLR:WT；位位置：[2]；默认值：0；中断2清除
 */
#define SYSTIMER_TARGET2_INT_CLR    (BIT(2))
#define SYSTIMER_TARGET2_INT_CLR_M  (SYSTIMER_TARGET2_INT_CLR_V << SYSTIMER_TARGET2_INT_CLR_S)
#define SYSTIMER_TARGET2_INT_CLR_V  0x00000001
#define SYSTIMER_TARGET2_INT_CLR_S  2

/** SYSTIMER_INT_ST_REG寄存器SYSTIMER中断状态寄存器
 */
#define SYSTIMER_INT_ST_REG (DR_REG_SYSTIMER_BASE + 0x70)
/** SYSTIMER_TARGET0_INT_ST:RO；位位置：[0]；默认值：0；中断0状态
 */
#define SYSTIMER_TARGET0_INT_ST    (BIT(0))
#define SYSTIMER_TARGET0_INT_ST_M  (SYSTIMER_TARGET0_INT_ST_V << SYSTIMER_TARGET0_INT_ST_S)
#define SYSTIMER_TARGET0_INT_ST_V  0x00000001
#define SYSTIMER_TARGET0_INT_ST_S  0
/** SYSTIMER_TARGET1_INT_ST:RO；位位置：[1]；默认值：0；中断1状态
 */
#define SYSTIMER_TARGET1_INT_ST    (BIT(1))
#define SYSTIMER_TARGET1_INT_ST_M  (SYSTIMER_TARGET1_INT_ST_V << SYSTIMER_TARGET1_INT_ST_S)
#define SYSTIMER_TARGET1_INT_ST_V  0x00000001
#define SYSTIMER_TARGET1_INT_ST_S  1
/** SYSTIMER_TARGET2_INT_ST:RO；位位置：[2]；默认值：0；interupt2状态
 */
#define SYSTIMER_TARGET2_INT_ST    (BIT(2))
#define SYSTIMER_TARGET2_INT_ST_M  (SYSTIMER_TARGET2_INT_ST_V << SYSTIMER_TARGET2_INT_ST_S)
#define SYSTIMER_TARGET2_INT_ST_V  0x00000001
#define SYSTIMER_TARGET2_INT_ST_S  2

/** SYSTIMER_REAL_TARGET0_LO_REG寄存器系统计时器comp0实际目标值低寄存器
 */
#define SYSTIMER_REAL_TARGET0_LO_REG (DR_REG_SYSTIMER_BASE + 0x74)
/** SYSTIMER_TARGET0_LO_RO:RO；位位置：[31:0]；默认值：0；实际目标值低32位
 */
#define SYSTIMER_TARGET0_LO_RO    0xFFFFFFFF
#define SYSTIMER_TARGET0_LO_RO_M  (SYSTIMER_TARGET0_LO_RO_V << SYSTIMER_TARGET0_LO_RO_S)
#define SYSTIMER_TARGET0_LO_RO_V  0xFFFFFFFF
#define SYSTIMER_TARGET0_LO_RO_S  0

/** SYSTIMER_REAL_TARGET0_HI_REG寄存器系统计时器comp0实际目标值高寄存器
 */
#define SYSTIMER_REAL_TARGET0_HI_REG (DR_REG_SYSTIMER_BASE + 0x78)
/** SYSTIMER_TARGET0_HI_RO:RO；比特位置：[19:0]；默认值：0；实际目标值高20位
 */
#define SYSTIMER_TARGET0_HI_RO    0x000FFFFF
#define SYSTIMER_TARGET0_HI_RO_M  (SYSTIMER_TARGET0_HI_RO_V << SYSTIMER_TARGET0_HI_RO_S)
#define SYSTIMER_TARGET0_HI_RO_V  0x000FFFFF
#define SYSTIMER_TARGET0_HI_RO_S  0

/** SYSTIMER_REAL_TARGET1_LO_REG寄存器系统计时器comp1实际目标值低寄存器
 */
#define SYSTIMER_REAL_TARGET1_LO_REG (DR_REG_SYSTIMER_BASE + 0x7c)
/** SYSTIMER_TARGET1_LO_RO:RO；位位置：[31:0]；默认值：0；实际目标值低32位
 */
#define SYSTIMER_TARGET1_LO_RO    0xFFFFFFFF
#define SYSTIMER_TARGET1_LO_RO_M  (SYSTIMER_TARGET1_LO_RO_V << SYSTIMER_TARGET1_LO_RO_S)
#define SYSTIMER_TARGET1_LO_RO_V  0xFFFFFFFF
#define SYSTIMER_TARGET1_LO_RO_S  0

/** SYSTIMER_REAL_TARGET1_HI_REG寄存器系统计时器comp1实际目标值高寄存器
 */
#define SYSTIMER_REAL_TARGET1_HI_REG (DR_REG_SYSTIMER_BASE + 0x80)
/** SYSTIMER_TARGET1_HI_RO:RO；比特位置：[19:0]；默认值：0；实际目标值高20位
 */
#define SYSTIMER_TARGET1_HI_RO    0x000FFFFF
#define SYSTIMER_TARGET1_HI_RO_M  (SYSTIMER_TARGET1_HI_RO_V << SYSTIMER_TARGET1_HI_RO_S)
#define SYSTIMER_TARGET1_HI_RO_V  0x000FFFFF
#define SYSTIMER_TARGET1_HI_RO_S  0

/** SYSTIMER_REAL_TARGET2_LO_REG寄存器系统计时器comp2实际目标值低寄存器
 */
#define SYSTIMER_REAL_TARGET2_LO_REG (DR_REG_SYSTIMER_BASE + 0x84)
/** SYSTIMER_TARGET2_LO_RO:RO；位位置：[31:0]；默认值：0；实际目标值低32位
 */
#define SYSTIMER_TARGET2_LO_RO    0xFFFFFFFF
#define SYSTIMER_TARGET2_LO_RO_M  (SYSTIMER_TARGET2_LO_RO_V << SYSTIMER_TARGET2_LO_RO_S)
#define SYSTIMER_TARGET2_LO_RO_V  0xFFFFFFFF
#define SYSTIMER_TARGET2_LO_RO_S  0

/** SYSTIMER_REAL_TARGET2_HI_REG寄存器系统计时器comp2实际目标值高寄存器
 */
#define SYSTIMER_REAL_TARGET2_HI_REG (DR_REG_SYSTIMER_BASE + 0x88)
/** SYSTIMER_TARGET2_HI_RO:RO；比特位置：[19:0]；默认值：0；实际目标值高20位
 */
#define SYSTIMER_TARGET2_HI_RO    0x000FFFFF
#define SYSTIMER_TARGET2_HI_RO_M  (SYSTIMER_TARGET2_HI_RO_V << SYSTIMER_TARGET2_HI_RO_S)
#define SYSTIMER_TARGET2_HI_RO_V  0x000FFFFF
#define SYSTIMER_TARGET2_HI_RO_S  0

/** SYSTIMER_DATE_REG寄存器系统计时器版本控制寄存器
 */
#define SYSTIMER_DATE_REG (DR_REG_SYSTIMER_BASE + 0xfc)
/** 系统日期：R/W；位位置：[31:0]；默认值：33628753；systimer寄存器版本
 */
#define SYSTIMER_DATE    0xFFFFFFFF
#define SYSTIMER_DATE_M  (SYSTIMER_DATE_V << SYSTIMER_DATE_S)
#define SYSTIMER_DATE_V  0xFFFFFFFF
#define SYSTIMER_DATE_S  0

#ifdef __cplusplus
}
#endif

