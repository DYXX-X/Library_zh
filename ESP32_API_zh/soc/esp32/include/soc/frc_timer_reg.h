// 版权所有2015-2016 Espressif Systems（上海）私人有限公司
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

#ifndef _SOC_FRC_TIMER_REG_H_
#define _SOC_FRC_TIMER_REG_H_

#include "soc.h"

/**
 * 以下是“传统”计时器的寄存器定义
 */

#define REG_FRC_TIMER_BASE(i)           (DR_REG_FRC_TIMER_BASE + i*0x20)

#define FRC_TIMER_LOAD_REG(i)           (REG_FRC_TIMER_BASE(i) + 0x0)   // 计时器负载值（i==0时为23位，i==1时为32位）
#define FRC_TIMER_LOAD_VALUE(i)         ((i == 0)?0x007FFFFF:0xffffffff)
#define FRC_TIMER_LOAD_VALUE_S          0

#define FRC_TIMER_COUNT_REG(i)          (REG_FRC_TIMER_BASE(i) + 0x4)   // 计时器计数值（i==0时为23位，i==1时为32位）
#define FRC_TIMER_COUNT                 ((i == 0)?0x007FFFFF:0xffffffff)
#define FRC_TIMER_COUNT_S               0

#define FRC_TIMER_CTRL_REG(i)           (REG_FRC_TIMER_BASE(i) + 0x8)
#define FRC_TIMER_INT_STATUS            (BIT(8))        // 中断状态（RO）
#define FRC_TIMER_ENABLE                (BIT(7))        // 启用计时器
#define FRC_TIMER_AUTOLOAD              (BIT(6))        // 启用自动加载
#define FRC_TIMER_PRESCALER             0x00000007
#define FRC_TIMER_PRESCALER_S           1
#define FRC_TIMER_PRESCALER_1           (0 << FRC_TIMER_PRESCALER_S)
#define FRC_TIMER_PRESCALER_16          (2 << FRC_TIMER_PRESCALER_S)
#define FRC_TIMER_PRESCALER_256         (4 << FRC_TIMER_PRESCALER_S)
#define FRC_TIMER_LEVEL_INT             (BIT(0))        // 1： 级别，0：边缘

#define FRC_TIMER_INT_REG(i)            (REG_FRC_TIMER_BASE(i) + 0xC)
#define FRC_TIMER_INT_CLR               (BIT(0))        // 清除中断

#define FRC_TIMER_ALARM_REG(i)          (REG_FRC_TIMER_BASE(i) + 0x10)  // 定时器报警值；寄存器仅存在于i==1
#define FRC_TIMER_ALARM                 0xFFFFFFFF
#define FRC_TIMER_ALARM_S               0

#endif //_SOC_FRC_TIMER_REG_H_

