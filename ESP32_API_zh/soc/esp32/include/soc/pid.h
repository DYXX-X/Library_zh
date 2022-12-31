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
#ifndef _SOC_PID_H_
#define _SOC_PID_H_

#define PROPID_GEN_BASE 0x3FF1F000
//位1..7:1，如果中断将触发PID更改
#define PROPID_CONFIG_INTERRUPT_ENABLE	((PROPID_GEN_BASE)+0x000)
//各种中断处理程序的矢量
#define PROPID_CONFIG_INTERRUPT_ADDR_1	((PROPID_GEN_BASE)+0x004)
#define PROPID_CONFIG_INTERRUPT_ADDR_2	((PROPID_GEN_BASE)+0x008)
#define PROPID_CONFIG_INTERRUPT_ADDR_3	((PROPID_GEN_BASE)+0x00C)
#define PROPID_CONFIG_INTERRUPT_ADDR_4	((PROPID_GEN_BASE)+0x010)
#define PROPID_CONFIG_INTERRUPT_ADDR_5	((PROPID_GEN_BASE)+0x014)
#define PROPID_CONFIG_INTERRUPT_ADDR_6	((PROPID_GEN_BASE)+0x018)
#define PROPID_CONFIG_INTERRUPT_ADDR_7	((PROPID_GEN_BASE)+0x01C)

//切换到新PID之前的延迟（以CPU周期为单位）
#define PROPID_CONFIG_PID_DELAY			((PROPID_GEN_BASE)+0x020)
#define PROPID_CONFIG_NMI_DELAY			((PROPID_GEN_BASE)+0x024)

//上次检测到中断。由硬件在内部设置。
#define PROPID_TABLE_LEVEL				((PROPID_GEN_BASE)+0x028)
//每个int的PID/prev int数据
#define PROPID_FROM_1					((PROPID_GEN_BASE)+0x02C)
#define PROPID_FROM_2					((PROPID_GEN_BASE)+0x030)
#define PROPID_FROM_3					((PROPID_GEN_BASE)+0x034)
#define PROPID_FROM_4					((PROPID_GEN_BASE)+0x038)
#define PROPID_FROM_5					((PROPID_GEN_BASE)+0x03C)
#define PROPID_FROM_6					((PROPID_GEN_BASE)+0x040)
#define PROPID_FROM_7					((PROPID_GEN_BASE)+0x044)
#define PROPID_FROM_PID_MASK	0x7
#define PROPID_FROM_PID_S		0
#define PROPID_FROM_INT_MASK	0xF
#define PROPID_FROM_INT_S		3

//确认程序后设置PID
#define PROPID_PID_NEW					((PROPID_GEN_BASE)+0x048)
//写入以启动PID更改
#define PROPID_PID_CONFIRM				((PROPID_GEN_BASE)+0x04c)
//当前PID？
#define PROPID_PID_REG					((PROPID_GEN_BASE)+0x050)

//写入掩码NMI
#define PROPID_PID_NMI_MASK_HW_ENABLE	((PROPID_GEN_BASE)+0x054)
//写入以取消屏蔽NMI
#define PROPID_PID_NMI_MASK_HW_DISABLE	((PROPID_GEN_BASE)+0x058)
#define PROPID_PID_NMI_MASK_HW_REG		((PROPID_GEN_BASE)+0x05c)

//调试注册表
#define PROPID_PID						((PROPID_GEN_BASE)+0x060)
#define PROPID_NMI_MASK_HW				((PROPID_GEN_BASE)+0x064)

#endif /* _SOC_PID_H_ */

