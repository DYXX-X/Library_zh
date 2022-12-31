// 版权所有2016-2018 Espressif Systems（上海）私人有限公司
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

#include "soc.h"

/**
 * 此文件列出了作为RTC一部分的I2C控制器的外围寄存器。ULP协处理器使用该控制器实现I2C_RD和I2C_WR指令。
 *
 * 此控制器的部分功能（如从属模式和多字节传输）未连接到ULP，因此ULP程序不可用。
 */

#define RTC_I2C_SCL_LOW_PERIOD_REG          (DR_REG_RTC_I2C_BASE + 0x000)
/* RTC_I2C_SCL_LOW_PERIOD:R/W；比特位置：[18:0]；默认值：19'b0；*/
/*description:scl==0的循环数*/
#define RTC_I2C_SCL_LOW_PERIOD    0x1FFFFFF
#define RTC_I2C_SCL_LOW_PERIOD_M  ((RTC_I2C_SCL_LOW_PERIOD_V)<<(RTC_I2C_SCL_LOW_PERIOD_S))
#define RTC_I2C_SCL_LOW_PERIOD_V  0x1FFFFFF
#define RTC_I2C_SCL_LOW_PERIOD_S  0

#define RTC_I2C_CTRL_REG          (DR_REG_RTC_I2C_BASE + 0x004)
/* RTC_I2C_RX_LSB_FIRST:R/W；位位置：[7]；默认值：1’b0；*/
/*description:先接收LSB*/
#define RTC_I2C_RX_LSB_FIRST	BIT(7)
#define RTC_I2C_RX_LSB_FIRST_M  BIT(7)
#define RTC_I2C_RX_LSB_FIRST_V  (1)
#define RTC_I2C_RX_LSB_FIRST_S  (7)
/* RTC_I2C_TX_LSB_FIRST:R/W；位位置：[6]；默认值：1’b0；*/
/*description:先发送LSB*/
#define RTC_I2C_TX_LSB_FIRST	BIT(6)
#define RTC_I2C_TX_LSB_FIRST_M  BIT(6)
#define RTC_I2C_TX_LSB_FIRST_V  (1)
#define RTC_I2C_TX_LSB_FIRST_S  (6)
/* RTC_I2C_TRANS_START:R/W；位位置：[5]；默认值：1’b0；*/
/*description:强制生成启动条件*/
#define RTC_I2C_TRANS_START	   BIT(5)
#define RTC_I2C_TRANS_START_M  BIT(5)
#define RTC_I2C_TRANS_START_V  (1)
#define RTC_I2C_TRANS_START_S  (5)
/* RTC_I2C_MS_MODE：R/W；位位置：[4]；默认值：1’b0；*/
/*description:主（1）或从（0）*/
#define RTC_I2C_MS_MODE	   BIT(4)
#define RTC_I2C_MS_MODE_M  BIT(4)
#define RTC_I2C_MS_MODE_V  (1)
#define RTC_I2C_MS_MODE_S  (4)
/* RTC_I2C_SCL_FORCE_OUT:R/W；位位置：[1]；默认值：1’b0；*/
/*描述：SCL为推拉式（1）或开放式（0）*/
#define RTC_I2C_SCL_FORCE_OUT	 BIT(1)
#define RTC_I2C_SCL_FORCE_OUT_M  BIT(1)
#define RTC_I2C_SCL_FORCE_OUT_V  (1)
#define RTC_I2C_SCL_FORCE_OUT_S  (1)
/* RTC_I2C_SDA_frce_OUT:R/W；位位置：[0]；默认值：1’b0；*/
/*描述：SDA为推拉式（1）或开放式（0）*/
#define RTC_I2C_SDA_FORCE_OUT	 BIT(0)
#define RTC_I2C_SDA_FORCE_OUT_M  BIT(0)
#define RTC_I2C_SDA_FORCE_OUT_V  (1)
#define RTC_I2C_SDA_FORCE_OUT_S  (0)

#define RTC_I2C_DEBUG_STATUS_REG          (DR_REG_RTC_I2C_BASE + 0x008)
/* RTC_I2C_SCL_STATE:R/W；位位置：[30:28]；默认值：3'b0；*/
/*描述：SCL状态机的状态*/
#define RTC_I2C_SCL_STATE	 0x7
#define RTC_I2C_SCL_STATE_M  ((RTC_I2C_SCL_STATE_V)<<(RTC_I2C_SCL_STATE_S))
#define RTC_I2C_SCL_STATE_V  0x7
#define RTC_I2C_SCL_STATE_S  28
/* RTC_I2C_MAIN_STATE:R/W；位位置：[27:25]；默认值：3'b0；*/
/*description:主状态机的状态*/
#define RTC_I2C_MAIN_STATE    0x7
#define RTC_I2C_MAIN_STATE_M  ((RTC_I2C_MAIN_STATE_V)<<(RTC_I2C_MAIN_STATE_S))
#define RTC_I2C_MAIN_STATE_V  0x7
#define RTC_I2C_MAIN_STATE_S  25
/* RTC_I2C_BYTE_TRANS:R/W；位位置：[6]；默认值：1’b0；*/
/*描述：8位传输完成*/
#define RTC_I2C_BYTE_TRANS	   BIT(6)
#define RTC_I2C_BYTE_TRANS_M  BIT(6)
#define RTC_I2C_BYTE_TRANS_V  (1)
#define RTC_I2C_BYTE_TRANS_S  (6)
/* RTC_I2C_SLAVE_ADDR_MATCH:R/W；位位置：[5]；默认值：1’b0；*/
/*description:作为从属服务器工作时，地址是否匹配*/
#define RTC_I2C_SLAVE_ADDR_MATCH	   BIT(5)
#define RTC_I2C_SLAVE_ADDR_MATCH_M  BIT(5)
#define RTC_I2C_SLAVE_ADDR_MATCH_V  (1)
#define RTC_I2C_SLAVE_ADDR_MATCH_S  (5)
/* RTC_I2C_BUS_BUSY:R/W；位位置：[4]；默认值：1’b0；*/
/*description:操作正在进行*/
#define RTC_I2C_BUS_BUSY	   BIT(4)
#define RTC_I2C_BUS_BUSY_M  BIT(4)
#define RTC_I2C_BUS_BUSY_V  (1)
#define RTC_I2C_BUS_BUSY_S  (4)
/* RTC_I2C_ARB_list:R/W；位位置：[3]；默认值：1’b0；*/
/*描述：作为主机工作时，I2C总线失去控制*/
#define RTC_I2C_ARB_LOST	   BIT(3)
#define RTC_I2C_ARB_LOST_M  BIT(3)
#define RTC_I2C_ARB_LOST_V  (1)
#define RTC_I2C_ARB_LOST_S  (3)
/* RTC_I2C_TIMED_OUT:R/W；位位置：[2]；默认值：1’b0；*/
/*description:传输已超时*/
#define RTC_I2C_TIMED_OUT	   BIT(2)
#define RTC_I2C_TIMED_OUT_M  BIT(2)
#define RTC_I2C_TIMED_OUT_V  (1)
#define RTC_I2C_TIMED_OUT_S  (2)
/* RTC_I2C_SLAVE_RW:R/W；位位置：[1]；默认值：1’b0；*/
/*description:当作为从机工作时，收到的R/W位的值*/
#define RTC_I2C_SLAVE_RW	   BIT(1)
#define RTC_I2C_SLAVE_RW_M  BIT(1)
#define RTC_I2C_SLAVE_RW_V  (1)
#define RTC_I2C_SLAVE_RW_S  (1)
/* RTC_I2C_ACK_VAL:R/W；位位置：[0]；默认值：1’b0；*/
/*description:总线上确认信号的值*/
#define RTC_I2C_ACK_VAL	   BIT(0)
#define RTC_I2C_ACK_VAL_M  BIT(0)
#define RTC_I2C_ACK_VAL_V  (1)
#define RTC_I2C_ACK_VAL_S  (0)

#define RTC_I2C_TIMEOUT_REG          (DR_REG_RTC_I2C_BASE + 0x00c)
/* RTC_I2C_TIMEOUT:R/W；比特位置：[19:0]；默认值：20'b0；*/
/*description:传输可以采用的FAST_CLK周期的最大数量*/
#define RTC_I2C_TIMEOUT	   0xFFFFF
#define RTC_I2C_TIMEOUT_M  ((RTC_I2C_TIMEOUT_V)<<(RTC_I2C_TIMEOUT_S))
#define RTC_I2C_TIMEOUT_V  0xFFFFF
#define RTC_I2C_TIMEOUT_S  0

#define RTC_I2C_SLAVE_ADDR_REG          (DR_REG_RTC_I2C_BASE + 0x010)
/* RTC_I2C_SLAVE_ADDR_10位：R/W；位位置：[31]；默认值：1’b0；*/
/*description:设置本地从属地址是否为10位*/
#define RTC_I2C_SLAVE_ADDR_10BIT	BIT(31)
#define RTC_I2C_SLAVE_ADDR_10BIT_M  BIT(31)
#define RTC_I2C_SLAVE_ADDR_10BIT_V  (1)
#define RTC_I2C_SLAVE_ADDR_10BIT_S  (31)
/* RTC_I2C_SLAVE_ADDR:R/W；位位置：[14:0]；默认值：15'b0；*/
/*description:本地从属地址*/
#define RTC_I2C_SLAVE_ADDR	  0x7FFF
#define RTC_I2C_SLAVE_ADDR_M  ((RTC_I2C_SLAVE_ADDR_V)<<(RTC_I2C_SLAVE_ADDR_S))
#define RTC_I2C_SLAVE_ADDR_V  0x7FFF
#define RTC_I2C_SLAVE_ADDR_S  0

/* 上次读取操作的结果。不直接使用，因为数据将返回到ULP。列出用于调试目的。
 */
#define RTC_I2C_DATA_REG         (DR_REG_RTC_I2C_BASE + 0x01c)

/* 中断寄存器；由于来自RTC_I2C的中断未连接，因此列出这些寄存器仅用于调试目的。
 */

/* 中断原始状态寄存器*/
#define RTC_I2C_INT_RAW_REG         (DR_REG_RTC_I2C_BASE + 0x020)
/* RTC_I2C_TIME_OUT_INT_RAW:R/O；位位置：[7]；默认值：1’b0；*/
/*描述：超时中断原始状态*/
#define RTC_I2C_TIME_OUT_INT_RAW	   BIT(7)
#define RTC_I2C_TIME_OUT_INT_RAW_M  BIT(7)
#define RTC_I2C_TIME_OUT_INT_RAW_V  (1)
#define RTC_I2C_TIME_OUT_INT_RAW_S  (7)
/* RTC_I2C_TRANS_COMPLETE_INT_RAW:R/W；位位置：[6]；默认值：1’b0；*/
/*description:已检测到停止条件中断原始状态*/
#define RTC_I2C_TRANS_COMPLETE_INT_RAW	   BIT(6)
#define RTC_I2C_TRANS_COMPLETE_INT_RAW_M  BIT(6)
#define RTC_I2C_TRANS_COMPLETE_INT_RAW_V  (1)
#define RTC_I2C_TRANS_COMPLETE_INT_RAW_S  (6)
/* RTC_I2C_MASTER_TRANS_COMPLETE_INT_RAW:R/W；位位置：[5]；默认值：1’b0；*/
/*说明：*/
#define RTC_I2C_MASTER_TRANS_COMPLETE_INT_RAW	   BIT(5)
#define RTC_I2C_MASTER_TRANS_COMPLETE_INT_RAW_M  BIT(5)
#define RTC_I2C_MASTER_TRANS_COMPLETE_INT_RAW_V  (1)
#define RTC_I2C_MASTER_TRANS_COMPLETE_INT_RAW_S  (5)
/* RTC_I2C_ARBITRATION_LOST_INT_RAW:R/W；位位置：[4]；默认值：1’b0；*/
/*description:Master败诉仲裁*/
#define RTC_I2C_ARBITRATION_LOST_INT_RAW	   BIT(4)
#define RTC_I2C_ARBITRATION_LOST_INT_RAW_M  BIT(4)
#define RTC_I2C_ARBITRATION_LOST_INT_RAW_V  (1)
#define RTC_I2C_ARBITRATION_LOST_INT_RAW_S  (4)
/* RTC_I2C_SLAVE_TRANS_COMPLETE_INT_RAW:R/W；位位置：[3]；默认值：1’b0；*/
/*description:从机接受1字节，地址匹配*/
#define RTC_I2C_SLAVE_TRANS_COMPLETE_INT_RAW	   BIT(3)
#define RTC_I2C_SLAVE_TRANS_COMPLETE_INT_RAW_M  BIT(3)
#define RTC_I2C_SLAVE_TRANS_COMPLETE_INT_RAW_V  (1)
#define RTC_I2C_SLAVE_TRANS_COMPLETE_INT_RAW_S  (3)

/* 中断清除寄存器*/
#define RTC_I2C_INT_CLR_REG         (DR_REG_RTC_I2C_BASE + 0x024)
/* RTC_I2C_TIME_OUT_INT_CLR:W/O；位位置：[8]；默认值：1’b0；*/
/*说明：*/
#define RTC_I2C_TIME_OUT_INT_CLR	   BIT(8)
#define RTC_I2C_TIME_OUT_INT_CLR_M  BIT(8)
#define RTC_I2C_TIME_OUT_INT_CLR_V  (1)
#define RTC_I2C_TIME_OUT_INT_CLR_S  (8)
/* RTC_I2C_TRANS_COMPLETE_INT_CLR:R/W；位位置：[7]；默认值：1’b0；*/
/*说明：*/
#define RTC_I2C_TRANS_COMPLETE_INT_CLR	   BIT(7)
#define RTC_I2C_TRANS_COMPLETE_INT_CLR_M  BIT(7)
#define RTC_I2C_TRANS_COMPLETE_INT_CLR_V  (1)
#define RTC_I2C_TRANS_COMPLETE_INT_CLR_S  (7)
/* RTC_I2C_MASTER_TRANS_COMPLETE_INT_CLR:R/W；位位置：[6]；默认值：1’b0；*/
/*说明：*/
#define RTC_I2C_MASTER_TRANS_COMPLETE_INT_CLR	   BIT(6)
#define RTC_I2C_MASTER_TRANS_COMPLETE_INT_CLR_M  BIT(6)
#define RTC_I2C_MASTER_TRANS_COMPLETE_INT_CLR_V  (1)
#define RTC_I2C_MASTER_TRANS_COMPLETE_INT_CLR_S  (6)
/* RTC_I2C_ARBITRATION_LOST_INT_CLR:R/W；位位置：[5]；默认值：1’b0；*/
/*说明：*/
#define RTC_I2C_ARBITRATION_LOST_INT_CLR	   BIT(5)
#define RTC_I2C_ARBITRATION_LOST_INT_CLR_M  BIT(5)
#define RTC_I2C_ARBITRATION_LOST_INT_CLR_V  (1)
#define RTC_I2C_ARBITRATION_LOST_INT_CLR_S  (5)
/* RTC_I2C_SLAVE_TRANS_COMPLETE_INT_CLR:R/W；位位置：[4]；默认值：1’b0；*/
/*说明：*/
#define RTC_I2C_SLAVE_TRANS_COMPLETE_INT_CLR	   BIT(4)
#define RTC_I2C_SLAVE_TRANS_COMPLETE_INT_CLR_M  BIT(4)
#define RTC_I2C_SLAVE_TRANS_COMPLETE_INT_CLR_V  (1)
#define RTC_I2C_SLAVE_TRANS_COMPLETE_INT_CLR_S  (4)

/* 中断启用寄存器。此处未给出位定义，因为未使用RTC_I2C的中断功能。
 */
#define RTC_I2C_INT_EN_REG          (DR_REG_RTC_I2C_BASE + 0x028)

/* 屏蔽中断状态寄存器。此处未给出位定义，因为未使用RTC_I2C的中断功能。
 */
#define RTC_I2C_INT_ST_REG          (DR_REG_RTC_I2C_BASE + 0x02c)

#define RTC_I2C_SDA_DUTY_REG          (DR_REG_RTC_I2C_BASE + 0x030)
/* RTC_I2C_SDA_DUTY:R/W；比特位置：[19:0]；默认值：20'b0；*/
/*描述：SCL下降沿后SDA将切换的FAST_CLK周期数*/
#define RTC_I2C_SDA_DUTY	0xFFFFF
#define RTC_I2C_SDA_DUTY_M  ((RTC_I2C_SDA_DUTY_V)<<(RTC_I2C_SDA_DUTY_S))
#define RTC_I2C_SDA_DUTY_V  0xFFFFF
#define RTC_I2C_SDA_DUTY_S  0

#define RTC_I2C_SCL_HIGH_PERIOD_REG          (DR_REG_RTC_I2C_BASE + 0x038)
/* RTC_I2C_SCL_HIGH-PERIOD:R/W；比特位置：[19:0]；默认值：20'b0；*/
/*description:SCL的FAST_CLK周期数高*/
#define RTC_I2C_SCL_HIGH_PERIOD	   0xFFFFF
#define RTC_I2C_SCL_HIGH_PERIOD_M  ((RTC_I2C_SCL_HIGH_PERIOD_V)<<(RTC_I2C_SCL_HIGH_PERIOD_S))
#define RTC_I2C_SCL_HIGH_PERIOD_V  0xFFFFF
#define RTC_I2C_SCL_HIGH_PERIOD_S  0

#define RTC_I2C_SCL_START_PERIOD_REG          (DR_REG_RTC_I2C_BASE + 0x040)
/* RTC_I2C_SCL_START_PERIOD:R/W；比特位置：[19:0]；默认值：20'b0；*/
/*description:在生成启动条件之前等待的FAST_CLK周期数*/
#define RTC_I2C_SCL_START_PERIOD	0xFFFFF
#define RTC_I2C_SCL_START_PERIOD_M  ((RTC_I2C_SCL_START_PERIOD_V)<<(RTC_I2C_SCL_START_PERIOD_S))
#define RTC_I2C_SCL_START_PERIOD_V  0xFFFFF
#define RTC_I2C_SCL_START_PERIOD_S  0

#define RTC_I2C_SCL_STOP_PERIOD_REG          (DR_REG_RTC_I2C_BASE + 0x044)
/* RTC_I2C_SCL_STOP_PERIOD:R/W；比特位置：[19:0]；默认值：20'b0；*/
/*description:在生成停止条件之前等待的FAST_CLK周期数*/
#define RTC_I2C_SCL_STOP_PERIOD	   0xFFFFF
#define RTC_I2C_SCL_STOP_PERIOD_M  ((RTC_I2C_SCL_STOP_PERIOD_V)<<(RTC_I2C_SCL_STOP_PERIOD_S))
#define RTC_I2C_SCL_STOP_PERIOD_V  0xFFFFF
#define RTC_I2C_SCL_STOP_PERIOD_S  0

/* 一个由16个RTC_I2C_CMD寄存器组成的块，用于描述要执行的I2C操作。ULP控制RTC_I2C时未使用。
 */
#define RTC_I2C_CMD_REG_COUNT   16
#define RTC_I2C_CMD_REG(i)          (DR_REG_RTC_I2C_BASE + 0x048 + (i) * 4)
/* RTC_I2C_CMD_DONE:R/W；位位置：[31]；默认值：1’b0；*/
/*description:命令完成时，由HW设置位*/
#define RTC_I2C_CMD_DONE	   BIT(31)
#define RTC_I2C_CMD_DONE_M  BIT(31)
#define RTC_I2C_CMD_DONE_V  (1)
#define RTC_I2C_CMD_DONE_S  (31)
/* RTC_I2C_VAL:R/W；比特位置：[13:0]；默认值：14'b0；*/
/*description:命令内容*/
#define RTC_I2C_VAL	   0
#define RTC_I2C_VAL_M  ((RTC_I2C_VAL_V)<<(RTC_I2C_VAL_S))
#define RTC_I2C_VAL_V  0x3FFF
#define RTC_I2C_VAL_S  0

