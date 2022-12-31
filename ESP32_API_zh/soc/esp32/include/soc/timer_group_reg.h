// 版权所有2015-2016 Espressif Systems（上海）私人有限公司
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
#ifndef __TIMG_REG_H__
#define __TIMG_REG_H__
#include "soc.h"

/* 需要写入TIMG_WDT_WKEY以启用WDT寄存器的值*/
#define TIMG_WDT_WKEY_VALUE 0x50D83AA1

/* TIMG_WDT_STGx的可能值*/
#define TIMG_WDT_STG_SEL_OFF 0
#define TIMG_WDT_STG_SEL_INT 1
#define TIMG_WDT_STG_SEL_RESET_CPU 2
#define TIMG_WDT_STG_SEL_RESET_SYSTEM 3

/* TIMG_WDT_CPU_RESET_LENGTH和TIMG_WDT_SYS_RESET_LENGTH的可能值*/
#define TIMG_WDT_RESET_LENGTH_100_NS    0
#define TIMG_WDT_RESET_LENGTH_200_NS    1
#define TIMG_WDT_RESET_LENGTH_300_NS    2
#define TIMG_WDT_RESET_LENGTH_400_NS    3
#define TIMG_WDT_RESET_LENGTH_500_NS    4
#define TIMG_WDT_RESET_LENGTH_800_NS    5
#define TIMG_WDT_RESET_LENGTH_1600_NS   6
#define TIMG_WDT_RESET_LENGTH_3200_NS   7

#define REG_TIMG_BASE(i)       (DR_REG_TIMERGROUP0_BASE + i*0x1000)
#define TIMG_T0CONFIG_REG(i)          (REG_TIMG_BASE(i) + 0x0000)
/* TIMG_T0_EN:R/W；位位置：[31]；默认值：1'0；*/
/*description:启用设置计时器0时基计数器时*/
#define TIMG_T0_EN  (BIT(31))
#define TIMG_T0_EN_M  (BIT(31))
#define TIMG_T0_EN_V  0x1
#define TIMG_T0_EN_S  31
/* TIMG_T0_增加：R/W；位位置：[30]；默认值：1'h1；*/
/*description:将计时器设置为0时基计数器递增。清除计时器0时，时基计数器递减。*/
#define TIMG_T0_INCREASE  (BIT(30))
#define TIMG_T0_INCREASE_M  (BIT(30))
#define TIMG_T0_INCREASE_V  0x1
#define TIMG_T0_INCREASE_S  30
/* TIMG_T0_AUTORELOAD:R/W；位位置：[29]；默认值：1'h1；*/
/*description:当设置计时器0时，启用报警时自动重新加载*/
#define TIMG_T0_AUTORELOAD  (BIT(29))
#define TIMG_T0_AUTORELOAD_M  (BIT(29))
#define TIMG_T0_AUTORELOAD_V  0x1
#define TIMG_T0_AUTORELOAD_S  29
/* TIMG_T0_DIVIDER:R/W；比特位置：[28:13]；默认值：16'h1；*/
/*description:计时器0时钟（T0_clk）预缩放值。*/
#define TIMG_T0_DIVIDER  0x0000FFFF
#define TIMG_T0_DIVIDER_M  ((TIMG_T0_DIVIDER_V)<<(TIMG_T0_DIVIDER_S))
#define TIMG_T0_DIVIDER_V  0xFFFF
#define TIMG_T0_DIVIDER_S  13
/* TIMG_T0_EDGE_INT_EN:R/W；位位置：[12]；默认值：1'0；*/
/*description:报警时将生成设置边缘类型的中断*/
#define TIMG_T0_EDGE_INT_EN  (BIT(12))
#define TIMG_T0_EDGE_INT_EN_M  (BIT(12))
#define TIMG_T0_EDGE_INT_EN_V  0x1
#define TIMG_T0_EDGE_INT_EN_S  12
/* TIMG_T0_LEVEL_INT_EN:R/W；位位置：[11]；默认值：1'0；*/
/*description:报警时将生成设置级别类型的中断*/
#define TIMG_T0_LEVEL_INT_EN  (BIT(11))
#define TIMG_T0_LEVEL_INT_EN_M  (BIT(11))
#define TIMG_T0_LEVEL_INT_EN_V  0x1
#define TIMG_T0_LEVEL_INT_EN_S  11
/* TIMG_T0_ALARM_EN:R/W；位位置：[10]；默认值：1'0；*/
/*description:启用设置报警时*/
#define TIMG_T0_ALARM_EN  (BIT(10))
#define TIMG_T0_ALARM_EN_M  (BIT(10))
#define TIMG_T0_ALARM_EN_V  0x1
#define TIMG_T0_ALARM_EN_S  10

#define TIMG_T0LO_REG(i)          (REG_TIMG_BASE(i) + 0x0004)
/* TIMG_T0_LO:RO；位位置：[31:0]；默认值：32'h0；*/
/*description:寄存器存储计时器0时基计数器电流值低32位。*/
#define TIMG_T0_LO  0xFFFFFFFF
#define TIMG_T0_LO_M  ((TIMG_T0_LO_V)<<(TIMG_T0_LO_S))
#define TIMG_T0_LO_V  0xFFFFFFFF
#define TIMG_T0_LO_S  0

#define TIMG_T0HI_REG(i)          (REG_TIMG_BASE(i) + 0x0008)
/* TIMG_T0_HI:RO；位位置：[31:0]；默认值：32'h0；*/
/*description:寄存器以存储计时器0时基计数器电流值（高于32位）。*/
#define TIMG_T0_HI  0xFFFFFFFF
#define TIMG_T0_HI_M  ((TIMG_T0_HI_V)<<(TIMG_T0_HI_S))
#define TIMG_T0_HI_V  0xFFFFFFFF
#define TIMG_T0_HI_S  0

#define TIMG_T0UPDATE_REG(i)          (REG_TIMG_BASE(i) + 0x000c)
/* TIMG_T0_UPDATE:WO；位位置：[31:0]；默认值：32'h0；*/
/*description:写入任何值都将触发计时器0时基计数器值更新（计时器0当前值将存储在上面的寄存器中）*/
#define TIMG_T0_UPDATE  0xFFFFFFFF
#define TIMG_T0_UPDATE_M  ((TIMG_T0_UPDATE_V)<<(TIMG_T0_UPDATE_S))
#define TIMG_T0_UPDATE_V  0xFFFFFFFF
#define TIMG_T0_UPDATE_S  0

#define TIMG_T0ALARMLO_REG(i)          (REG_TIMG_BASE(i) + 0x0010)
/* TIMG_T0_ALARM_LO:R/W；位位置：[31:0]；默认值：32'h0；*/
/*描述：计时器0时基计数器值低于32位，将触发报警*/
#define TIMG_T0_ALARM_LO  0xFFFFFFFF
#define TIMG_T0_ALARM_LO_M  ((TIMG_T0_ALARM_LO_V)<<(TIMG_T0_ALARM_LO_S))
#define TIMG_T0_ALARM_LO_V  0xFFFFFFFF
#define TIMG_T0_ALARM_LO_S  0

#define TIMG_T0ALARMHI_REG(i)          (REG_TIMG_BASE(i) + 0x0014)
/* TIMG_T0_ALARM_HI:R/W；位位置：[31:0]；默认值：32'h0；*/
/*描述：计时器0时基计数器值高于32位，将触发报警*/
#define TIMG_T0_ALARM_HI  0xFFFFFFFF
#define TIMG_T0_ALARM_HI_M  ((TIMG_T0_ALARM_HI_V)<<(TIMG_T0_ALARM_HI_S))
#define TIMG_T0_ALARM_HI_V  0xFFFFFFFF
#define TIMG_T0_ALARM_HI_S  0

#define TIMG_T0LOADLO_REG(i)          (REG_TIMG_BASE(i) + 0x0018)
/* TIMG_T0_LOAD_LO:R/W；位位置：[31:0]；默认值：32'h0；*/
/*description:将加载到计时器0时基计数器中的值的低32位*/
#define TIMG_T0_LOAD_LO  0xFFFFFFFF
#define TIMG_T0_LOAD_LO_M  ((TIMG_T0_LOAD_LO_V)<<(TIMG_T0_LOAD_LO_S))
#define TIMG_T0_LOAD_LO_V  0xFFFFFFFF
#define TIMG_T0_LOAD_LO_S  0

#define TIMG_T0LOADHI_REG(i)          (REG_TIMG_BASE(i) + 0x001c)
/* TIMG_T0_LOAD_HI:R/W；位位置：[31:0]；默认值：32'h0；*/
/*描述：将加载到计时器0时基计数器中的值的32位*/
#define TIMG_T0_LOAD_HI  0xFFFFFFFF
#define TIMG_T0_LOAD_HI_M  ((TIMG_T0_LOAD_HI_V)<<(TIMG_T0_LOAD_HI_S))
#define TIMG_T0_LOAD_HI_V  0xFFFFFFFF
#define TIMG_T0_LOAD_HI_S  0

#define TIMG_T0LOAD_REG(i)          (REG_TIMG_BASE(i) + 0x0020)
/* TIMG_T0_LOAD:WO；位位置：[31:0]；默认值：32'h0；*/
/*description:写入任何值都将触发计时器0时基计数器重新加载*/
#define TIMG_T0_LOAD  0xFFFFFFFF
#define TIMG_T0_LOAD_M  ((TIMG_T0_LOAD_V)<<(TIMG_T0_LOAD_S))
#define TIMG_T0_LOAD_V  0xFFFFFFFF
#define TIMG_T0_LOAD_S  0

#define TIMG_T1CONFIG_REG(i)          (REG_TIMG_BASE(i) + 0x0024)
/* TIMG_T1_EN:R/W；位位置：[31]；默认值：1'0；*/
/*描述：当启用设置计时器1时基计数器时*/
#define TIMG_T1_EN  (BIT(31))
#define TIMG_T1_EN_M  (BIT(31))
#define TIMG_T1_EN_V  0x1
#define TIMG_T1_EN_S  31
/* TIMG_T1_增加：R/W；位位置：[30]；默认值：1'h1；*/
/*description:当设置计时器1时基计数器增量时。清除计时器1时，时基计数器递减。*/
#define TIMG_T1_INCREASE  (BIT(30))
#define TIMG_T1_INCREASE_M  (BIT(30))
#define TIMG_T1_INCREASE_V  0x1
#define TIMG_T1_INCREASE_S  30
/* TIMG_T1_AUTORELOAD:R/W；位位置：[29]；默认值：1'h1；*/
/*描述：当设置计时器1时，启用报警时自动重新加载*/
#define TIMG_T1_AUTORELOAD  (BIT(29))
#define TIMG_T1_AUTORELOAD_M  (BIT(29))
#define TIMG_T1_AUTORELOAD_V  0x1
#define TIMG_T1_AUTORELOAD_S  29
/* TIMG_T1_DIVIDER:R/W；比特位置：[28:13]；默认值：16'h1；*/
/*description:计时器1时钟（T1_clk）预缩放值。*/
#define TIMG_T1_DIVIDER  0x0000FFFF
#define TIMG_T1_DIVIDER_M  ((TIMG_T1_DIVIDER_V)<<(TIMG_T1_DIVIDER_S))
#define TIMG_T1_DIVIDER_V  0xFFFF
#define TIMG_T1_DIVIDER_S  13
/* TIMG_T1_EDGE_INT_EN:R/W；位位置：[12]；默认值：1'0；*/
/*description:报警时将生成设置边缘类型的中断*/
#define TIMG_T1_EDGE_INT_EN  (BIT(12))
#define TIMG_T1_EDGE_INT_EN_M  (BIT(12))
#define TIMG_T1_EDGE_INT_EN_V  0x1
#define TIMG_T1_EDGE_INT_EN_S  12
/* TIMG_T1_LEVEL_INT_EN:R/W；位位置：[11]；默认值：1'0；*/
/*description:报警时将生成设置级别类型的中断*/
#define TIMG_T1_LEVEL_INT_EN  (BIT(11))
#define TIMG_T1_LEVEL_INT_EN_M  (BIT(11))
#define TIMG_T1_LEVEL_INT_EN_V  0x1
#define TIMG_T1_LEVEL_INT_EN_S  11
/* TIMG_T1_ALARM_EN:R/W；位位置：[10]；默认值：1'0；*/
/*description:启用设置报警时*/
#define TIMG_T1_ALARM_EN  (BIT(10))
#define TIMG_T1_ALARM_EN_M  (BIT(10))
#define TIMG_T1_ALARM_EN_V  0x1
#define TIMG_T1_ALARM_EN_S  10

#define TIMG_T1LO_REG(i)          (REG_TIMG_BASE(i) + 0x0028)
/* TIMG_T1_LO:RO；位位置：[31:0]；默认值：32'h0；*/
/*description:寄存器存储计时器1时基计数器电流值低32位。*/
#define TIMG_T1_LO  0xFFFFFFFF
#define TIMG_T1_LO_M  ((TIMG_T1_LO_V)<<(TIMG_T1_LO_S))
#define TIMG_T1_LO_V  0xFFFFFFFF
#define TIMG_T1_LO_S  0

#define TIMG_T1HI_REG(i)          (REG_TIMG_BASE(i) + 0x002c)
/* TIMG_T1_HI:RO；位位置：[31:0]；默认值：32'h0；*/
/*description:寄存器存储计时器1时基计数器电流值（32位以上）。*/
#define TIMG_T1_HI  0xFFFFFFFF
#define TIMG_T1_HI_M  ((TIMG_T1_HI_V)<<(TIMG_T1_HI_S))
#define TIMG_T1_HI_V  0xFFFFFFFF
#define TIMG_T1_HI_S  0

#define TIMG_T1UPDATE_REG(i)          (REG_TIMG_BASE(i) + 0x0030)
/* TIMG_T1_UPDATE:WO；位位置：[31:0]；默认值：32'h0；*/
/*description:写入任何值都将触发计时器1时基计数器值更新（计时器1当前值将存储在上面的寄存器中）*/
#define TIMG_T1_UPDATE  0xFFFFFFFF
#define TIMG_T1_UPDATE_M  ((TIMG_T1_UPDATE_V)<<(TIMG_T1_UPDATE_S))
#define TIMG_T1_UPDATE_V  0xFFFFFFFF
#define TIMG_T1_UPDATE_S  0

#define TIMG_T1ALARMLO_REG(i)          (REG_TIMG_BASE(i) + 0x0034)
/* TIMG_T1_ALARM_LO:R/W；位位置：[31:0]；默认值：32'h0；*/
/*描述：计时器1时基计数器值低于32位，将触发报警*/
#define TIMG_T1_ALARM_LO  0xFFFFFFFF
#define TIMG_T1_ALARM_LO_M  ((TIMG_T1_ALARM_LO_V)<<(TIMG_T1_ALARM_LO_S))
#define TIMG_T1_ALARM_LO_V  0xFFFFFFFF
#define TIMG_T1_ALARM_LO_S  0

#define TIMG_T1ALARMHI_REG(i)          (REG_TIMG_BASE(i) + 0x0038)
/* TIMG_T1_ALARM_HI:R/W；位位置：[31:0]；默认值：32'h0；*/
/*描述：计时器1时基计数器值高于32位，将触发报警*/
#define TIMG_T1_ALARM_HI  0xFFFFFFFF
#define TIMG_T1_ALARM_HI_M  ((TIMG_T1_ALARM_HI_V)<<(TIMG_T1_ALARM_HI_S))
#define TIMG_T1_ALARM_HI_V  0xFFFFFFFF
#define TIMG_T1_ALARM_HI_S  0

#define TIMG_T1LOADLO_REG(i)          (REG_TIMG_BASE(i) + 0x003c)
/* TIMG_T1_LOAD_LO:R/W；位位置：[31:0]；默认值：32'h0；*/
/*description:将加载到计时器1时基计数器中的值的低32位*/
#define TIMG_T1_LOAD_LO  0xFFFFFFFF
#define TIMG_T1_LOAD_LO_M  ((TIMG_T1_LOAD_LO_V)<<(TIMG_T1_LOAD_LO_S))
#define TIMG_T1_LOAD_LO_V  0xFFFFFFFF
#define TIMG_T1_LOAD_LO_S  0

#define TIMG_T1LOADHI_REG(i)          (REG_TIMG_BASE(i) + 0x0040)
/* TIMG_T1_LOAD_HI:R/W；位位置：[31:0]；默认值：32'h0；*/
/*描述：将加载到计时器1时基计数器中的值的较高32位*/
#define TIMG_T1_LOAD_HI  0xFFFFFFFF
#define TIMG_T1_LOAD_HI_M  ((TIMG_T1_LOAD_HI_V)<<(TIMG_T1_LOAD_HI_S))
#define TIMG_T1_LOAD_HI_V  0xFFFFFFFF
#define TIMG_T1_LOAD_HI_S  0

#define TIMG_T1LOAD_REG(i)          (REG_TIMG_BASE(i) + 0x0044)
/* TIMG_T1_LOAD:WO；位位置：[31:0]；默认值：32'h0；*/
/*description:写入任何值都将触发计时器1时基计数器重新加载*/
#define TIMG_T1_LOAD  0xFFFFFFFF
#define TIMG_T1_LOAD_M  ((TIMG_T1_LOAD_V)<<(TIMG_T1_LOAD_S))
#define TIMG_T1_LOAD_V  0xFFFFFFFF
#define TIMG_T1_LOAD_S  0

#define TIMG_WDTCONFIG0_REG(i)          (REG_TIMG_BASE(i) + 0x0048)
/* TIMG_WDT_EN:R/W；位位置：[31]；默认值：1'0；*/
/*description:启用设置SWDT时*/
#define TIMG_WDT_EN  (BIT(31))
#define TIMG_WDT_EN_M  (BIT(31))
#define TIMG_WDT_EN_V  0x1
#define TIMG_WDT_EN_S  31
/* TIMG_WDT_STG0:R/W；位位置：[30:29]；默认值：1'd0；*/
/*description:阶段0配置。0：关闭1：中断2：复位CPU 3：复位系统*/
#define TIMG_WDT_STG0  0x00000003
#define TIMG_WDT_STG0_M  ((TIMG_WDT_STG0_V)<<(TIMG_WDT_STG0_S))
#define TIMG_WDT_STG0_V  0x3
#define TIMG_WDT_STG0_S  29
/* TIMG_WDT_STG1:R/W；位位置：[28:27]；默认值：1'd0；*/
/*description:阶段1配置。0：关闭1：中断2：复位CPU 3：复位系统*/
#define TIMG_WDT_STG1  0x00000003
#define TIMG_WDT_STG1_M  ((TIMG_WDT_STG1_V)<<(TIMG_WDT_STG1_S))
#define TIMG_WDT_STG1_V  0x3
#define TIMG_WDT_STG1_S  27
/* TIMG_WDT_STG2:R/W；比特位置：[26:25]；默认值：1'd0；*/
/*description:阶段2配置。0：关闭1：中断2：复位CPU 3：复位系统*/
#define TIMG_WDT_STG2  0x00000003
#define TIMG_WDT_STG2_M  ((TIMG_WDT_STG2_V)<<(TIMG_WDT_STG2_S))
#define TIMG_WDT_STG2_V  0x3
#define TIMG_WDT_STG2_S  25
/* TIMG_WDT_STG3:R/W；位位置：[24:23]；默认值：1'd0；*/
/*description:阶段3配置。0：关闭1：中断2：复位CPU 3：复位系统*/
#define TIMG_WDT_STG3  0x00000003
#define TIMG_WDT_STG3_M  ((TIMG_WDT_STG3_V)<<(TIMG_WDT_STG3_S))
#define TIMG_WDT_STG3_V  0x3
#define TIMG_WDT_STG3_S  23
/* TIMG_WDT_EDGE_INT_EN:R/W；位位置：[22]；默认值：1'0；*/
/*description:启用设置边缘类型中断生成时*/
#define TIMG_WDT_EDGE_INT_EN  (BIT(22))
#define TIMG_WDT_EDGE_INT_EN_M  (BIT(22))
#define TIMG_WDT_EDGE_INT_EN_V  0x1
#define TIMG_WDT_EDGE_INT_EN_S  22
/* TIMG_WDT_LEVEL_INT_EN:R/W；位位置：[21]；默认值：1'0；*/
/*description:启用设置级别类型中断生成时*/
#define TIMG_WDT_LEVEL_INT_EN  (BIT(21))
#define TIMG_WDT_LEVEL_INT_EN_M  (BIT(21))
#define TIMG_WDT_LEVEL_INT_EN_V  0x1
#define TIMG_WDT_LEVEL_INT_EN_S  21
/* TIMG_WDT_CPU_RESET_LENGTH:R/W；比特位置：[20:18]；默认值：3'h1；*/
/*description:CPU重置选择的长度。0：100ns 1：200ns 2：300ns 3：400ns 4：500ns 5：800ns 6：1.6us 7：3.2us*/
#define TIMG_WDT_CPU_RESET_LENGTH  0x00000007
#define TIMG_WDT_CPU_RESET_LENGTH_M  ((TIMG_WDT_CPU_RESET_LENGTH_V)<<(TIMG_WDT_CPU_RESET_LENGTH_S))
#define TIMG_WDT_CPU_RESET_LENGTH_V  0x7
#define TIMG_WDT_CPU_RESET_LENGTH_S  18
/* TIMG_WDT_SYS_RESET_LENGTH:R/W；比特位置：[17:15]；默认值：3'h1；*/
/*description:系统重置选择的长度。0：100ns 1：200ns 2：300ns 3：400ns 4：500ns 5：800ns 6：1.6us 7：3.2us*/
#define TIMG_WDT_SYS_RESET_LENGTH  0x00000007
#define TIMG_WDT_SYS_RESET_LENGTH_M  ((TIMG_WDT_SYS_RESET_LENGTH_V)<<(TIMG_WDT_SYS_RESET_LENGTH_S))
#define TIMG_WDT_SYS_RESET_LENGTH_V  0x7
#define TIMG_WDT_SYS_RESET_LENGTH_S  15
/* TIMG_WDT_FLASHBOOT_MOD_EN:R/W；位位置：[14]；默认值：1'h1；*/
/*description:启用设置闪存启动保护时*/
#define TIMG_WDT_FLASHBOOT_MOD_EN  (BIT(14))
#define TIMG_WDT_FLASHBOOT_MOD_EN_M  (BIT(14))
#define TIMG_WDT_FLASHBOOT_MOD_EN_V  0x1
#define TIMG_WDT_FLASHBOOT_MOD_EN_S  14

#define TIMG_WDTCONFIG1_REG(i)          (REG_TIMG_BASE(i) + 0x004c)
/* TIMG_WDT_CLK_PRESCALE：R/W；比特位置：[31:16]；默认值：16'h1；*/
/*description:SWDT时钟预缩放值。周期=12.5ns*存储在此寄存器中的值*/
#define TIMG_WDT_CLK_PRESCALE  0x0000FFFF
#define TIMG_WDT_CLK_PRESCALE_M  ((TIMG_WDT_CLK_PRESCALE_V)<<(TIMG_WDT_CLK_PRESCALE_S))
#define TIMG_WDT_CLK_PRESCALE_V  0xFFFF
#define TIMG_WDT_CLK_PRESCALE_S  16

#define TIMG_WDTCONFIG2_REG(i)          (REG_TIMG_BASE(i) + 0x0050)
/* TIMG_WDT_STG0_HOLD:R/W；位位置：[31:0]；默认值：32'd26000000；*/
/*description:SWDT时钟周期中的阶段0超时值*/
#define TIMG_WDT_STG0_HOLD  0xFFFFFFFF
#define TIMG_WDT_STG0_HOLD_M  ((TIMG_WDT_STG0_HOLD_V)<<(TIMG_WDT_STG0_HOLD_S))
#define TIMG_WDT_STG0_HOLD_V  0xFFFFFFFF
#define TIMG_WDT_STG0_HOLD_S  0

#define TIMG_WDTCONFIG3_REG(i)          (REG_TIMG_BASE(i) + 0x0054)
/* TIMG_WDT_STG1_HOLD：R/W；位位置：[31:0]；默认值：32'h7ffffff；*/
/*description:SWDT时钟周期中的阶段1超时值*/
#define TIMG_WDT_STG1_HOLD  0xFFFFFFFF
#define TIMG_WDT_STG1_HOLD_M  ((TIMG_WDT_STG1_HOLD_V)<<(TIMG_WDT_STG1_HOLD_S))
#define TIMG_WDT_STG1_HOLD_V  0xFFFFFFFF
#define TIMG_WDT_STG1_HOLD_S  0

#define TIMG_WDTCONFIG4_REG(i)          (REG_TIMG_BASE(i) + 0x0058)
/* TIMG_WDT_STG2_HOLD:R/W；位位置：[31:0]；默认值：32'fffff；*/
/*description:SWDT时钟周期中的阶段2超时值*/
#define TIMG_WDT_STG2_HOLD  0xFFFFFFFF
#define TIMG_WDT_STG2_HOLD_M  ((TIMG_WDT_STG2_HOLD_V)<<(TIMG_WDT_STG2_HOLD_S))
#define TIMG_WDT_STG2_HOLD_V  0xFFFFFFFF
#define TIMG_WDT_STG2_HOLD_S  0

#define TIMG_WDTCONFIG5_REG(i)          (REG_TIMG_BASE(i) + 0x005c)
/* TIMG_WDT_STG3_HOLD:R/W；位位置：[31:0]；默认值：32'fffff；*/
/*description:SWDT时钟周期中的阶段3超时值*/
#define TIMG_WDT_STG3_HOLD  0xFFFFFFFF
#define TIMG_WDT_STG3_HOLD_M  ((TIMG_WDT_STG3_HOLD_V)<<(TIMG_WDT_STG3_HOLD_S))
#define TIMG_WDT_STG3_HOLD_V  0xFFFFFFFF
#define TIMG_WDT_STG3_HOLD_S  0

#define TIMG_WDTFEED_REG(i)          (REG_TIMG_BASE(i) + 0x0060)
/* TIMG_WDT_FEED：WO；位位置：[31:0]；默认值：32'h0；*/
/*description:写入任何值都将馈送SWDT*/
#define TIMG_WDT_FEED  0xFFFFFFFF
#define TIMG_WDT_FEED_M  ((TIMG_WDT_FEED_V)<<(TIMG_WDT_FEED_S))
#define TIMG_WDT_FEED_V  0xFFFFFFFF
#define TIMG_WDT_FEED_S  0

#define TIMG_WDTWPROTECT_REG(i)          (REG_TIMG_BASE(i) + 0x0064)
/* TIMG_WDT_WKEY:R/W；位位置：[31:0]；默认值：32'h50d83aa1；*/
/*description:如果从默认值更改其值，则启用写保护。*/
#define TIMG_WDT_WKEY  0xFFFFFFFF
#define TIMG_WDT_WKEY_M  ((TIMG_WDT_WKEY_V)<<(TIMG_WDT_WKEY_S))
#define TIMG_WDT_WKEY_V  0xFFFFFFFF
#define TIMG_WDT_WKEY_S  0

#define TIMG_RTCCALICFG_REG(i)          (REG_TIMG_BASE(i) + 0x0068)
/* TIMG_RTC_CALI_START：R/W；位位置：[31]；默认值：1'0；*/
/*说明：*/
#define TIMG_RTC_CALI_START  (BIT(31))
#define TIMG_RTC_CALI_START_M  (BIT(31))
#define TIMG_RTC_CALI_START_V  0x1
#define TIMG_RTC_CALI_START_S  31
/* TIMG_RTC_CALI_MAX：R/W；比特位置：[30:16]；默认值：15'h1；*/
/*说明：*/
#define TIMG_RTC_CALI_MAX  0x00007FFF
#define TIMG_RTC_CALI_MAX_M  ((TIMG_RTC_CALI_MAX_V)<<(TIMG_RTC_CALI_MAX_S))
#define TIMG_RTC_CALI_MAX_V  0x7FFF
#define TIMG_RTC_CALI_MAX_S  16
/* TIMG_RTC_CALI_RDY:RO；位位置：[15]；默认值：1'0；*/
/*说明：*/
#define TIMG_RTC_CALI_RDY  (BIT(15))
#define TIMG_RTC_CALI_RDY_M  (BIT(15))
#define TIMG_RTC_CALI_RDY_V  0x1
#define TIMG_RTC_CALI_RDY_S  15
/* TIMG_RTC_CALI_CLK_SEL:R/W；比特位置：[14:13]；默认值：2'h1；*/
/*说明：*/
#define TIMG_RTC_CALI_CLK_SEL  0x00000003
#define TIMG_RTC_CALI_CLK_SEL_M  ((TIMG_RTC_CALI_CLK_SEL_V)<<(TIMG_RTC_CALI_CLK_SEL_S))
#define TIMG_RTC_CALI_CLK_SEL_V  0x3
#define TIMG_RTC_CALI_CLK_SEL_S  13
/* TIMG_RTC_CALI_START循环：R/W；位位置：[12]；默认值：1'd1；*/
/*说明：*/
#define TIMG_RTC_CALI_START_CYCLING  (BIT(12))
#define TIMG_RTC_CALI_START_CYCLING_M  (BIT(12))
#define TIMG_RTC_CALI_START_CYCLING_V  0x1
#define TIMG_RTC_CALI_START_CYCLING_S  12

#define TIMG_RTCCALICFG1_REG(i)          (REG_TIMG_BASE(i) + 0x006c)
/* TIMG_RTC_CALI_VALUE:RO；比特位置：[31:7]；默认值：25'0；*/
/*说明：*/
#define TIMG_RTC_CALI_VALUE  0x01FFFFFF
#define TIMG_RTC_CALI_VALUE_M  ((TIMG_RTC_CALI_VALUE_V)<<(TIMG_RTC_CALI_VALUE_S))
#define TIMG_RTC_CALI_VALUE_V  0x1FFFFFF
#define TIMG_RTC_CALI_VALUE_S  7

#define TIMG_LACTCONFIG_REG(i)          (REG_TIMG_BASE(i) + 0x0070)
/* TIMG_LACT_EN:R/W；位位置：[31]；默认值：1'0；*/
/*说明：*/
#define TIMG_LACT_EN  (BIT(31))
#define TIMG_LACT_EN_M  (BIT(31))
#define TIMG_LACT_EN_V  0x1
#define TIMG_LACT_EN_S  31
/* TIMG_LACT_INCREASE:R/W；位位置：[30]；默认值：1'h1；*/
/*说明：*/
#define TIMG_LACT_INCREASE  (BIT(30))
#define TIMG_LACT_INCREASE_M  (BIT(30))
#define TIMG_LACT_INCREASE_V  0x1
#define TIMG_LACT_INCREASE_S  30
/* TIMG_LACT_AUTORELOAD:R/W；位位置：[29]；默认值：1'h1；*/
/*说明：*/
#define TIMG_LACT_AUTORELOAD  (BIT(29))
#define TIMG_LACT_AUTORELOAD_M  (BIT(29))
#define TIMG_LACT_AUTORELOAD_V  0x1
#define TIMG_LACT_AUTORELOAD_S  29
/* TIMG_LACT_DIVIDER:R/W；比特位置：[28:13]；默认值：16'h1；*/
/*说明：*/
#define TIMG_LACT_DIVIDER  0x0000FFFF
#define TIMG_LACT_DIVIDER_M  ((TIMG_LACT_DIVIDER_V)<<(TIMG_LACT_DIVIDER_S))
#define TIMG_LACT_DIVIDER_V  0xFFFF
#define TIMG_LACT_DIVIDER_S  13
/* TIMG_LACT_EDGE_INT_EN:R/W；位位置：[12]；默认值：1'0；*/
/*说明：*/
#define TIMG_LACT_EDGE_INT_EN  (BIT(12))
#define TIMG_LACT_EDGE_INT_EN_M  (BIT(12))
#define TIMG_LACT_EDGE_INT_EN_V  0x1
#define TIMG_LACT_EDGE_INT_EN_S  12
/* TIMG_LACT_LEVEL_INT_EN:R/W；位位置：[11]；默认值：1'0；*/
/*说明：*/
#define TIMG_LACT_LEVEL_INT_EN  (BIT(11))
#define TIMG_LACT_LEVEL_INT_EN_M  (BIT(11))
#define TIMG_LACT_LEVEL_INT_EN_V  0x1
#define TIMG_LACT_LEVEL_INT_EN_S  11
/* TIMG_LACT_ALARM_EN:R/W；位位置：[10]；默认值：1'0；*/
/*说明：*/
#define TIMG_LACT_ALARM_EN  (BIT(10))
#define TIMG_LACT_ALARM_EN_M  (BIT(10))
#define TIMG_LACT_ALARM_EN_V  0x1
#define TIMG_LACT_ALARM_EN_S  10
/* TIMG_LACT_LAC_EN:R/W；位位置：[9]；默认值：1'h1；*/
/*说明：*/
#define TIMG_LACT_LAC_EN  (BIT(9))
#define TIMG_LACT_LAC_EN_M  (BIT(9))
#define TIMG_LACT_LAC_EN_V  0x1
#define TIMG_LACT_LAC_EN_S  9
/* TIMG_LACT_CPST_EN:R/W；位位置：[8]；默认值：1'h1；*/
/*说明：*/
#define TIMG_LACT_CPST_EN  (BIT(8))
#define TIMG_LACT_CPST_EN_M  (BIT(8))
#define TIMG_LACT_CPST_EN_V  0x1
#define TIMG_LACT_CPST_EN_S  8
/* TIMG_LACT_RTC_ONLY:R/W；位位置：[7]；默认值：1'0；*/
/*说明：*/
#define TIMG_LACT_RTC_ONLY  (BIT(7))
#define TIMG_LACT_RTC_ONLY_M  (BIT(7))
#define TIMG_LACT_RTC_ONLY_V  0x1
#define TIMG_LACT_RTC_ONLY_S  7

#define TIMG_LACTRTC_REG(i)          (REG_TIMG_BASE(i) + 0x0074)
/* TIMG_LACT_RTC_STEP_LEN:R/W；位位置：[31:6]；默认值：26'h0；*/
/*说明：*/
#define TIMG_LACT_RTC_STEP_LEN  0x03FFFFFF
#define TIMG_LACT_RTC_STEP_LEN_M  ((TIMG_LACT_RTC_STEP_LEN_V)<<(TIMG_LACT_RTC_STEP_LEN_S))
#define TIMG_LACT_RTC_STEP_LEN_V  0x3FFFFFF
#define TIMG_LACT_RTC_STEP_LEN_S  6

#define TIMG_LACTLO_REG(i)          (REG_TIMG_BASE(i) + 0x0078)
/* TIMG_LACT_LO:RO；位位置：[31:0]；默认值：32'h0；*/
/*说明：*/
#define TIMG_LACT_LO  0xFFFFFFFF
#define TIMG_LACT_LO_M  ((TIMG_LACT_LO_V)<<(TIMG_LACT_LO_S))
#define TIMG_LACT_LO_V  0xFFFFFFFF
#define TIMG_LACT_LO_S  0

#define TIMG_LACTHI_REG(i)          (REG_TIMG_BASE(i) + 0x007c)
/* TIMG_LACT_HI:RO；位位置：[31:0]；默认值：32'h0；*/
/*说明：*/
#define TIMG_LACT_HI  0xFFFFFFFF
#define TIMG_LACT_HI_M  ((TIMG_LACT_HI_V)<<(TIMG_LACT_HI_S))
#define TIMG_LACT_HI_V  0xFFFFFFFF
#define TIMG_LACT_HI_S  0

#define TIMG_LACTUPDATE_REG(i)          (REG_TIMG_BASE(i) + 0x0080)
/* TIMG_LACT_UPDATE:WO；位位置：[31:0]；默认值：32'h0；*/
/*说明：*/
#define TIMG_LACT_UPDATE  0xFFFFFFFF
#define TIMG_LACT_UPDATE_M  ((TIMG_LACT_UPDATE_V)<<(TIMG_LACT_UPDATE_S))
#define TIMG_LACT_UPDATE_V  0xFFFFFFFF
#define TIMG_LACT_UPDATE_S  0

#define TIMG_LACTALARMLO_REG(i)          (REG_TIMG_BASE(i) + 0x0084)
/* TIMG_LACT_ALARM_LO:R/W；位位置：[31:0]；默认值：32'h0；*/
/*说明：*/
#define TIMG_LACT_ALARM_LO  0xFFFFFFFF
#define TIMG_LACT_ALARM_LO_M  ((TIMG_LACT_ALARM_LO_V)<<(TIMG_LACT_ALARM_LO_S))
#define TIMG_LACT_ALARM_LO_V  0xFFFFFFFF
#define TIMG_LACT_ALARM_LO_S  0

#define TIMG_LACTALARMHI_REG(i)          (REG_TIMG_BASE(i) + 0x0088)
/* TIMG_LACT_ALARM-HI:R/W；位位置：[31:0]；默认值：32'h0；*/
/*说明：*/
#define TIMG_LACT_ALARM_HI  0xFFFFFFFF
#define TIMG_LACT_ALARM_HI_M  ((TIMG_LACT_ALARM_HI_V)<<(TIMG_LACT_ALARM_HI_S))
#define TIMG_LACT_ALARM_HI_V  0xFFFFFFFF
#define TIMG_LACT_ALARM_HI_S  0

#define TIMG_LACTLOADLO_REG(i)          (REG_TIMG_BASE(i) + 0x008c)
/* TIMG_LACT_LOAD_LO:R/W；位位置：[31:0]；默认值：32'h0；*/
/*说明：*/
#define TIMG_LACT_LOAD_LO  0xFFFFFFFF
#define TIMG_LACT_LOAD_LO_M  ((TIMG_LACT_LOAD_LO_V)<<(TIMG_LACT_LOAD_LO_S))
#define TIMG_LACT_LOAD_LO_V  0xFFFFFFFF
#define TIMG_LACT_LOAD_LO_S  0

#define TIMG_LACTLOADHI_REG(i)          (REG_TIMG_BASE(i) + 0x0090)
/* TIMG_LACT_LOAD_HI:R/W；位位置：[31:0]；默认值：32'h0；*/
/*说明：*/
#define TIMG_LACT_LOAD_HI  0xFFFFFFFF
#define TIMG_LACT_LOAD_HI_M  ((TIMG_LACT_LOAD_HI_V)<<(TIMG_LACT_LOAD_HI_S))
#define TIMG_LACT_LOAD_HI_V  0xFFFFFFFF
#define TIMG_LACT_LOAD_HI_S  0

#define TIMG_LACTLOAD_REG(i)          (REG_TIMG_BASE(i) + 0x0094)
/* TIMG_LACT_LOAD:WO；位位置：[31:0]；默认值：32'h0；*/
/*说明：*/
#define TIMG_LACT_LOAD  0xFFFFFFFF
#define TIMG_LACT_LOAD_M  ((TIMG_LACT_LOAD_V)<<(TIMG_LACT_LOAD_S))
#define TIMG_LACT_LOAD_V  0xFFFFFFFF
#define TIMG_LACT_LOAD_S  0

#define TIMG_INT_ENA_TIMERS_REG(i)          (REG_TIMG_BASE(i) + 0x0098)
/* TIMG_LACT_INT_ENA:R/W；位位置：[3]；默认值：1'0；*/
/*说明：*/
#define TIMG_LACT_INT_ENA  (BIT(3))
#define TIMG_LACT_INT_ENA_M  (BIT(3))
#define TIMG_LACT_INT_ENA_V  0x1
#define TIMG_LACT_INT_ENA_S  3
/* TIMG_WDT_INT_ENA:R/W；位位置：[2]；默认值：1'0；*/
/*description:中断阶段超时时中断*/
#define TIMG_WDT_INT_ENA  (BIT(2))
#define TIMG_WDT_INT_ENA_M  (BIT(2))
#define TIMG_WDT_INT_ENA_V  0x1
#define TIMG_WDT_INT_ENA_S  2
/* TIMG_T1_INT_ENA:R/W；位位置：[1]；默认值：1'0；*/
/*description:timer1报警时中断*/
#define TIMG_T1_INT_ENA  (BIT(1))
#define TIMG_T1_INT_ENA_M  (BIT(1))
#define TIMG_T1_INT_ENA_V  0x1
#define TIMG_T1_INT_ENA_S  1
/* TIMG_T0_INT_ENA:R/W；位位置：[0]；默认值：1'0；*/
/*description:timer0报警时中断*/
#define TIMG_T0_INT_ENA  (BIT(0))
#define TIMG_T0_INT_ENA_M  (BIT(0))
#define TIMG_T0_INT_ENA_V  0x1
#define TIMG_T0_INT_ENA_S  0

#define TIMG_INT_RAW_TIMERS_REG(i)          (REG_TIMG_BASE(i) + 0x009c)
/* TIMG_LACT_INT_RO:RO；位位置：[3]；默认值：1'0；*/
/*说明：*/
#define TIMG_LACT_INT_RAW  (BIT(3))
#define TIMG_LACT_INT_RAW_M  (BIT(3))
#define TIMG_LACT_INT_RAW_V  0x1
#define TIMG_LACT_INT_RAW_S  3
/* TIMG_WDT_INT_RAW:RO；位位置：[2]；默认值：1'0；*/
/*description:中断阶段超时时中断*/
#define TIMG_WDT_INT_RAW  (BIT(2))
#define TIMG_WDT_INT_RAW_M  (BIT(2))
#define TIMG_WDT_INT_RAW_V  0x1
#define TIMG_WDT_INT_RAW_S  2
/* TIMG_T1_INT_RAW:RO；位位置：[1]；默认值：1'0；*/
/*description:timer1报警时中断*/
#define TIMG_T1_INT_RAW  (BIT(1))
#define TIMG_T1_INT_RAW_M  (BIT(1))
#define TIMG_T1_INT_RAW_V  0x1
#define TIMG_T1_INT_RAW_S  1
/* TIMG_T0_INT_RAW:RO；位位置：[0]；默认值：1'0；*/
/*description:timer0报警时中断*/
#define TIMG_T0_INT_RAW  (BIT(0))
#define TIMG_T0_INT_RAW_M  (BIT(0))
#define TIMG_T0_INT_RAW_V  0x1
#define TIMG_T0_INT_RAW_S  0

#define TIMG_INT_ST_TIMERS_REG(i)          (REG_TIMG_BASE(i) + 0x00a0)
/* TIMG_LACT_INT:RO；位位置：[3]；默认值：1'0；*/
/*说明：*/
#define TIMG_LACT_INT_ST  (BIT(3))
#define TIMG_LACT_INT_ST_M  (BIT(3))
#define TIMG_LACT_INT_ST_V  0x1
#define TIMG_LACT_INT_ST_S  3
/* TIMG_WDT_INT_ST:RO；位位置：[2]；默认值：1'0；*/
/*description:中断阶段超时时中断*/
#define TIMG_WDT_INT_ST  (BIT(2))
#define TIMG_WDT_INT_ST_M  (BIT(2))
#define TIMG_WDT_INT_ST_V  0x1
#define TIMG_WDT_INT_ST_S  2
/* TIMG_T1_INT_ST:RO；位位置：[1]；默认值：1'0；*/
/*description:timer1报警时中断*/
#define TIMG_T1_INT_ST  (BIT(1))
#define TIMG_T1_INT_ST_M  (BIT(1))
#define TIMG_T1_INT_ST_V  0x1
#define TIMG_T1_INT_ST_S  1
/* TIMG_T0_INT_ST:RO；位位置：[0]；默认值：1'0；*/
/*description:timer0报警时中断*/
#define TIMG_T0_INT_ST  (BIT(0))
#define TIMG_T0_INT_ST_M  (BIT(0))
#define TIMG_T0_INT_ST_V  0x1
#define TIMG_T0_INT_ST_S  0

#define TIMG_INT_CLR_TIMERS_REG(i)          (REG_TIMG_BASE(i) + 0x00a4)
/* TIMG_LACT_INT_CLR:WO；位位置：[3]；默认值：1'0；*/
/*说明：*/
#define TIMG_LACT_INT_CLR  (BIT(3))
#define TIMG_LACT_INT_CLR_M  (BIT(3))
#define TIMG_LACT_INT_CLR_V  0x1
#define TIMG_LACT_INT_CLR_S  3
/* TIMG_WDT_INT_CLR:WO；位位置：[2]；默认值：1'0；*/
/*description:中断阶段超时时中断*/
#define TIMG_WDT_INT_CLR  (BIT(2))
#define TIMG_WDT_INT_CLR_M  (BIT(2))
#define TIMG_WDT_INT_CLR_V  0x1
#define TIMG_WDT_INT_CLR_S  2
/* TIMG_T1_INT_CLR:WO；位位置：[1]；默认值：1'0；*/
/*description:timer1报警时中断*/
#define TIMG_T1_INT_CLR  (BIT(1))
#define TIMG_T1_INT_CLR_M  (BIT(1))
#define TIMG_T1_INT_CLR_V  0x1
#define TIMG_T1_INT_CLR_S  1
/* TIMG_T0_INT_CLR:WO；位位置：[0]；默认值：1'0；*/
/*description:timer0报警时中断*/
#define TIMG_T0_INT_CLR  (BIT(0))
#define TIMG_T0_INT_CLR_M  (BIT(0))
#define TIMG_T0_INT_CLR_V  0x1
#define TIMG_T0_INT_CLR_S  0

#define TIMG_NTIMERS_DATE_REG(i)          (REG_TIMG_BASE(i) + 0x00f8)
/* TIMG_NTIMERS_DATE:R/W；位位置：[27:0]；默认值：28'h1604290；*/
/*description:此regfile的版本*/
#define TIMG_NTIMERS_DATE  0x0FFFFFFF
#define TIMG_NTIMERS_DATE_M  ((TIMG_NTIMERS_DATE_V)<<(TIMG_NTIMERS_DATE_S))
#define TIMG_NTIMERS_DATE_V  0xFFFFFFF
#define TIMG_NTIMERS_DATE_S  0

#define TIMGCLK_REG(i)          (REG_TIMG_BASE(i) + 0x00fc)
/* TIMG_CLK_EN:R/W；位位置：[31]；默认值：1'0；*/
/*description:强制启用此regfile的时钟*/
#define TIMG_CLK_EN  (BIT(31))
#define TIMG_CLK_EN_M  (BIT(31))
#define TIMG_CLK_EN_V  0x1
#define TIMG_CLK_EN_S  31




#endif /*__TIMG_REG_H__ */

