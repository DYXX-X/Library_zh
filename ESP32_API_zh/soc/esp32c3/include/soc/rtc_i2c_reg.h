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
#ifndef _SOC_RTC_I2C_REG_H_
#define _SOC_RTC_I2C_REG_H_


#ifdef __cplusplus
extern "C" {
#endif
#include "soc.h"
#define RTC_I2C_SCL_LOW_PERIOD_REG          (DR_REG_RTC_I2C_BASE + 0x0000)
/* RTC_I2C_SCL_LOW_PERIOD:R/W；比特位置：[19:0]；默认值：20'h100；*/
/*description:scl=0的时间段*/
#define RTC_I2C_SCL_LOW_PERIOD  0x000FFFFF
#define RTC_I2C_SCL_LOW_PERIOD_M  ((RTC_I2C_SCL_LOW_PERIOD_V)<<(RTC_I2C_SCL_LOW_PERIOD_S))
#define RTC_I2C_SCL_LOW_PERIOD_V  0xFFFFF
#define RTC_I2C_SCL_LOW_PERIOD_S  0

#define RTC_I2C_CTRL_REG          (DR_REG_RTC_I2C_BASE + 0x0004)
/* RTC_I2C_CLK_EN:R/W；位位置：[31]；默认值：1’b0；*/
/*描述：rtc i2c reg clk门控*/
#define RTC_I2C_CLK_EN  (BIT(31))
#define RTC_I2C_CLK_EN_M  (BIT(31))
#define RTC_I2C_CLK_EN_V  0x1
#define RTC_I2C_CLK_EN_S  31
/* RTC_I2C_RESET:R/W；位位置：[30]；默认值：1’b0；*/
/*说明：rtc i2c sw重置*/
#define RTC_I2C_RESET  (BIT(30))
#define RTC_I2C_RESET_M  (BIT(30))
#define RTC_I2C_RESET_V  0x1
#define RTC_I2C_RESET_S  30
/* RTC_I2C_CTRL_CLK_GATE_EN:R/W；位位置：[29]；默认值：1’b0；*/
/*说明：*/
#define RTC_I2C_CTRL_CLK_GATE_EN  (BIT(29))
#define RTC_I2C_CTRL_CLK_GATE_EN_M  (BIT(29))
#define RTC_I2C_CTRL_CLK_GATE_EN_V  0x1
#define RTC_I2C_CTRL_CLK_GATE_EN_S  29
/* RTC_I2C_RX_LSB_FIRST:R/W；位位置：[5]；默认值：1’b0；*/
/*description:首先接收lsb*/
#define RTC_I2C_RX_LSB_FIRST  (BIT(5))
#define RTC_I2C_RX_LSB_FIRST_M  (BIT(5))
#define RTC_I2C_RX_LSB_FIRST_V  0x1
#define RTC_I2C_RX_LSB_FIRST_S  5
/* RTC_I2C_TX_LSB_FIRST:R/W；位位置：[4]；默认值：1’b0；*/
/*description:首先传输lsb*/
#define RTC_I2C_TX_LSB_FIRST  (BIT(4))
#define RTC_I2C_TX_LSB_FIRST_M  (BIT(4))
#define RTC_I2C_TX_LSB_FIRST_V  0x1
#define RTC_I2C_TX_LSB_FIRST_S  4
/* RTC_I2C_TRANS_START:R/W；位位置：[3]；默认值：1’b0；*/
/*description:强制启动*/
#define RTC_I2C_TRANS_START  (BIT(3))
#define RTC_I2C_TRANS_START_M  (BIT(3))
#define RTC_I2C_TRANS_START_V  0x1
#define RTC_I2C_TRANS_START_S  3
/* RTC_I2C_MS_MODE：R/W；位位置：[2]；默认值：1’b0；*/
/*description:1=主0=从*/
#define RTC_I2C_MS_MODE  (BIT(2))
#define RTC_I2C_MS_MODE_M  (BIT(2))
#define RTC_I2C_MS_MODE_V  0x1
#define RTC_I2C_MS_MODE_S  2
/* RTC_I2C_SCL_FORCE_OUT:R/W；位位置：[1]；默认值：1’b0；*/
/*描述：1=推拉0=开放式排水*/
#define RTC_I2C_SCL_FORCE_OUT  (BIT(1))
#define RTC_I2C_SCL_FORCE_OUT_M  (BIT(1))
#define RTC_I2C_SCL_FORCE_OUT_V  0x1
#define RTC_I2C_SCL_FORCE_OUT_S  1
/* RTC_I2C_SDA_frce_OUT:R/W；位位置：[0]；默认值：1’b0；*/
/*描述：1=推拉0=开放式排水*/
#define RTC_I2C_SDA_FORCE_OUT  (BIT(0))
#define RTC_I2C_SDA_FORCE_OUT_M  (BIT(0))
#define RTC_I2C_SDA_FORCE_OUT_V  0x1
#define RTC_I2C_SDA_FORCE_OUT_S  0

#define RTC_I2C_STATUS_REG          (DR_REG_RTC_I2C_BASE + 0x0008)
/* RTC_I2C_SCL_STATE_LAST:RO；位位置：[30:28]；默认值：3'b0；*/
/*description:scl上次状态*/
#define RTC_I2C_SCL_STATE_LAST  0x00000007
#define RTC_I2C_SCL_STATE_LAST_M  ((RTC_I2C_SCL_STATE_LAST_V)<<(RTC_I2C_SCL_STATE_LAST_S))
#define RTC_I2C_SCL_STATE_LAST_V  0x7
#define RTC_I2C_SCL_STATE_LAST_S  28
/* RTC_I2C_SCL_MAIN_STATE_LAST:RO；比特位置：[26:24]；默认值：3'b0；*/
/*description:i2c最后一个主状态*/
#define RTC_I2C_SCL_MAIN_STATE_LAST  0x00000007
#define RTC_I2C_SCL_MAIN_STATE_LAST_M  ((RTC_I2C_SCL_MAIN_STATE_LAST_V)<<(RTC_I2C_SCL_MAIN_STATE_LAST_S))
#define RTC_I2C_SCL_MAIN_STATE_LAST_V  0x7
#define RTC_I2C_SCL_MAIN_STATE_LAST_S  24
/* RTC_I2C_SHIFT:RO；比特位置：[23:16]；默认值：8'b0；*/
/*描述：移位器内容*/
#define RTC_I2C_SHIFT  0x000000FF
#define RTC_I2C_SHIFT_M  ((RTC_I2C_SHIFT_V)<<(RTC_I2C_SHIFT_S))
#define RTC_I2C_SHIFT_V  0xFF
#define RTC_I2C_SHIFT_S  16
/* RTC_I2C_OP_CNT:RO；位位置：[7:6]；默认值：2’b0；*/
/*description:哪个操作正在运行*/
#define RTC_I2C_OP_CNT  0x00000003
#define RTC_I2C_OP_CNT_M  ((RTC_I2C_OP_CNT_V)<<(RTC_I2C_OP_CNT_S))
#define RTC_I2C_OP_CNT_V  0x3
#define RTC_I2C_OP_CNT_S  6
/* RTC_I2C_BYTE_TRANS:RO；位位置：[5]；默认值：1’b0；*/
/*description:已完成一个字节的传输*/
#define RTC_I2C_BYTE_TRANS  (BIT(5))
#define RTC_I2C_BYTE_TRANS_M  (BIT(5))
#define RTC_I2C_BYTE_TRANS_V  0x1
#define RTC_I2C_BYTE_TRANS_S  5
/* RTC_I2C_SLAVE_address:RO；位位置：[4]；默认值：1’b0；*/
/*description:从属reg子地址*/
#define RTC_I2C_SLAVE_ADDRESSED  (BIT(4))
#define RTC_I2C_SLAVE_ADDRESSED_M  (BIT(4))
#define RTC_I2C_SLAVE_ADDRESSED_V  0x1
#define RTC_I2C_SLAVE_ADDRESSED_S  4
/* RTC_I2C_BUS_BUSY:RO；位位置：[3]；默认值：1’b0；*/
/*描述：总线繁忙*/
#define RTC_I2C_BUS_BUSY  (BIT(3))
#define RTC_I2C_BUS_BUSY_M  (BIT(3))
#define RTC_I2C_BUS_BUSY_V  0x1
#define RTC_I2C_BUS_BUSY_S  3
/* RTC_I2C_ARB_list:RO；位位置：[2]；默认值：1’b0；*/
/*描述：仲裁失败*/
#define RTC_I2C_ARB_LOST  (BIT(2))
#define RTC_I2C_ARB_LOST_M  (BIT(2))
#define RTC_I2C_ARB_LOST_V  0x1
#define RTC_I2C_ARB_LOST_S  2
/* RTC_I2C_SLAVE_RW:RO；位位置：[1]；默认值：1’b0；*/
/*description:从读或写*/
#define RTC_I2C_SLAVE_RW  (BIT(1))
#define RTC_I2C_SLAVE_RW_M  (BIT(1))
#define RTC_I2C_SLAVE_RW_V  0x1
#define RTC_I2C_SLAVE_RW_S  1
/* RTC_I2C_ACK_REC:RO；位位置：[0]；默认值：1’b0；*/
/*description:ack响应*/
#define RTC_I2C_ACK_REC  (BIT(0))
#define RTC_I2C_ACK_REC_M  (BIT(0))
#define RTC_I2C_ACK_REC_V  0x1
#define RTC_I2C_ACK_REC_S  0

#define RTC_I2C_TIMEOUT_REG          (DR_REG_RTC_I2C_BASE + 0x000c)
/* RTC_I2C_TIMEOUT:R/W；比特位置：[19:0]；默认值：20'h10000；*/
/*description:超时阈值*/
#define RTC_I2C_TIMEOUT  0x000FFFFF
#define RTC_I2C_TIMEOUT_M  ((RTC_I2C_TIMEOUT_V)<<(RTC_I2C_TIMEOUT_S))
#define RTC_I2C_TIMEOUT_V  0xFFFFF
#define RTC_I2C_TIMEOUT_S  0

#define RTC_I2C_SLAVE_ADDR_REG          (DR_REG_RTC_I2C_BASE + 0x0010)
/* RTC_I2C_ADDR_10BIT_EN:R/W；位位置：[31]；默认值：1’b0；*/
/*说明：i2c 10位模式启用*/
#define RTC_I2C_ADDR_10BIT_EN  (BIT(31))
#define RTC_I2C_ADDR_10BIT_EN_M  (BIT(31))
#define RTC_I2C_ADDR_10BIT_EN_V  0x1
#define RTC_I2C_ADDR_10BIT_EN_S  31
/* RTC_I2C_SLAVE_ADDR:R/W；位位置：[14:0]；默认值：15'b0；*/
/*description:从属地址*/
#define RTC_I2C_SLAVE_ADDR  0x00007FFF
#define RTC_I2C_SLAVE_ADDR_M  ((RTC_I2C_SLAVE_ADDR_V)<<(RTC_I2C_SLAVE_ADDR_S))
#define RTC_I2C_SLAVE_ADDR_V  0x7FFF
#define RTC_I2C_SLAVE_ADDR_S  0

#define RTC_I2C_SCL_HIGH_REG          (DR_REG_RTC_I2C_BASE + 0x0014)
/* RTC_I2C_SCL_HIGH-PERIOD:R/W；比特位置：[19:0]；默认值：20'h100；*/
/*描述：scl=1的时间段*/
#define RTC_I2C_SCL_HIGH_PERIOD  0x000FFFFF
#define RTC_I2C_SCL_HIGH_PERIOD_M  ((RTC_I2C_SCL_HIGH_PERIOD_V)<<(RTC_I2C_SCL_HIGH_PERIOD_S))
#define RTC_I2C_SCL_HIGH_PERIOD_V  0xFFFFF
#define RTC_I2C_SCL_HIGH_PERIOD_S  0

#define RTC_I2C_SDA_DUTY_REG          (DR_REG_RTC_I2C_BASE + 0x0018)
/* RTC_I2C_SDA_DUTY_NUM:R/W；比特位置：[19:0]；默认值：20'h10；*/
/*描述：SCL变低后SDA切换的时间段*/
#define RTC_I2C_SDA_DUTY_NUM  0x000FFFFF
#define RTC_I2C_SDA_DUTY_NUM_M  ((RTC_I2C_SDA_DUTY_NUM_V)<<(RTC_I2C_SDA_DUTY_NUM_S))
#define RTC_I2C_SDA_DUTY_NUM_V  0xFFFFF
#define RTC_I2C_SDA_DUTY_NUM_S  0

#define RTC_I2C_SCL_START_PERIOD_REG          (DR_REG_RTC_I2C_BASE + 0x001c)
/* RTC_I2C_SCL_START_PERIOD:R/W；比特位置：[19:0]；默认值：20'b1000；*/
/*描述：触发I2C启动后SCL切换的时间段*/
#define RTC_I2C_SCL_START_PERIOD  0x000FFFFF
#define RTC_I2C_SCL_START_PERIOD_M  ((RTC_I2C_SCL_START_PERIOD_V)<<(RTC_I2C_SCL_START_PERIOD_S))
#define RTC_I2C_SCL_START_PERIOD_V  0xFFFFF
#define RTC_I2C_SCL_START_PERIOD_S  0

#define RTC_I2C_SCL_STOP_PERIOD_REG          (DR_REG_RTC_I2C_BASE + 0x0020)
/* RTC_I2C_SCL_STOP_PERIOD:R/W；比特位置：[19:0]；默认值：20'b1000；*/
/*描述：触发I2C结束后SCL停止的时间段*/
#define RTC_I2C_SCL_STOP_PERIOD  0x000FFFFF
#define RTC_I2C_SCL_STOP_PERIOD_M  ((RTC_I2C_SCL_STOP_PERIOD_V)<<(RTC_I2C_SCL_STOP_PERIOD_S))
#define RTC_I2C_SCL_STOP_PERIOD_V  0xFFFFF
#define RTC_I2C_SCL_STOP_PERIOD_S  0

#define RTC_I2C_INT_CLR_REG          (DR_REG_RTC_I2C_BASE + 0x0024)
/* RTC_I2C_DETECT_START_INT_CLR:WO；位位置：[8]；默认值：1’b0；*/
/*描述：清除检测开始中断*/
#define RTC_I2C_DETECT_START_INT_CLR  (BIT(8))
#define RTC_I2C_DETECT_START_INT_CLR_M  (BIT(8))
#define RTC_I2C_DETECT_START_INT_CLR_V  0x1
#define RTC_I2C_DETECT_START_INT_CLR_S  8
/* RTC_I2C_TX_DATA_INT_CLR:WO；位位置：[7]；默认值：1’b0；*/
/*描述：清除运输装载数据完成中断*/
#define RTC_I2C_TX_DATA_INT_CLR  (BIT(7))
#define RTC_I2C_TX_DATA_INT_CLR_M  (BIT(7))
#define RTC_I2C_TX_DATA_INT_CLR_V  0x1
#define RTC_I2C_TX_DATA_INT_CLR_S  7
/* RTC_I2C_RX_DATA_INT_CLR:WO；位位置：[6]；默认值：1’b0；*/
/*description:清除接收数据中断*/
#define RTC_I2C_RX_DATA_INT_CLR  (BIT(6))
#define RTC_I2C_RX_DATA_INT_CLR_M  (BIT(6))
#define RTC_I2C_RX_DATA_INT_CLR_V  0x1
#define RTC_I2C_RX_DATA_INT_CLR_S  6
/* RTC_I2C_ACK_ERR_INT_CLR:WO；位位置：[5]；默认值：1’b0；*/
/*description:清除ack错误中断*/
#define RTC_I2C_ACK_ERR_INT_CLR  (BIT(5))
#define RTC_I2C_ACK_ERR_INT_CLR_M  (BIT(5))
#define RTC_I2C_ACK_ERR_INT_CLR_V  0x1
#define RTC_I2C_ACK_ERR_INT_CLR_S  5
/* RTC_I2C_TIMEOUT_INT_CLR:WO；位位置：[4]；默认值：1’b0；*/
/*description:清除超时中断*/
#define RTC_I2C_TIMEOUT_INT_CLR  (BIT(4))
#define RTC_I2C_TIMEOUT_INT_CLR_M  (BIT(4))
#define RTC_I2C_TIMEOUT_INT_CLR_V  0x1
#define RTC_I2C_TIMEOUT_INT_CLR_S  4
/* RTC_I2C_TRANS_COMPLETE_INT_CLR:WO；位位置：[3]；默认值：1’b0；*/
/*description:清除传输完成中断*/
#define RTC_I2C_TRANS_COMPLETE_INT_CLR  (BIT(3))
#define RTC_I2C_TRANS_COMPLETE_INT_CLR_M  (BIT(3))
#define RTC_I2C_TRANS_COMPLETE_INT_CLR_V  0x1
#define RTC_I2C_TRANS_COMPLETE_INT_CLR_S  3
/* RTC_I2C_MASTER_TRAN_COMP_INT_CLR:WO；位位置：[2]；默认值：1’b0；*/
/*描述：清除主传输完成中断*/
#define RTC_I2C_MASTER_TRAN_COMP_INT_CLR  (BIT(2))
#define RTC_I2C_MASTER_TRAN_COMP_INT_CLR_M  (BIT(2))
#define RTC_I2C_MASTER_TRAN_COMP_INT_CLR_V  0x1
#define RTC_I2C_MASTER_TRAN_COMP_INT_CLR_S  2
/* RTC_I2C_ARBITRATION_LOST_INT_CLR:WO；位位置：[1]；默认值：1’b0；*/
/*description:清除仲裁丢失中断*/
#define RTC_I2C_ARBITRATION_LOST_INT_CLR  (BIT(1))
#define RTC_I2C_ARBITRATION_LOST_INT_CLR_M  (BIT(1))
#define RTC_I2C_ARBITRATION_LOST_INT_CLR_V  0x1
#define RTC_I2C_ARBITRATION_LOST_INT_CLR_S  1
/* RTC_I2C_SLAVE_trans_COMP_INT_CLR:WO；位位置：[0]；默认值：1’b0；*/
/*description:清除从属传输完成中断*/
#define RTC_I2C_SLAVE_TRAN_COMP_INT_CLR  (BIT(0))
#define RTC_I2C_SLAVE_TRAN_COMP_INT_CLR_M  (BIT(0))
#define RTC_I2C_SLAVE_TRAN_COMP_INT_CLR_V  0x1
#define RTC_I2C_SLAVE_TRAN_COMP_INT_CLR_S  0

#define RTC_I2C_INT_RAW_REG          (DR_REG_RTC_I2C_BASE + 0x0028)
/* RTC_I2C_DETECT_START_INT_RAW:RO；位位置：[8]；默认值：1’b0；*/
/*描述：原始检测启动中断*/
#define RTC_I2C_DETECT_START_INT_RAW  (BIT(8))
#define RTC_I2C_DETECT_START_INT_RAW_M  (BIT(8))
#define RTC_I2C_DETECT_START_INT_RAW_V  0x1
#define RTC_I2C_DETECT_START_INT_RAW_S  8
/* RTC_I2C_TX_DATA_INT_RAW:RO；位位置：[7]；默认值：1’b0；*/
/*描述：原始传输数据中断*/
#define RTC_I2C_TX_DATA_INT_RAW  (BIT(7))
#define RTC_I2C_TX_DATA_INT_RAW_M  (BIT(7))
#define RTC_I2C_TX_DATA_INT_RAW_V  0x1
#define RTC_I2C_TX_DATA_INT_RAW_S  7
/* RTC_I2C_RX_DATA_INT_RAW:RO；位位置：[6]；默认值：1’b0；*/
/*description:原始接收数据中断*/
#define RTC_I2C_RX_DATA_INT_RAW  (BIT(6))
#define RTC_I2C_RX_DATA_INT_RAW_M  (BIT(6))
#define RTC_I2C_RX_DATA_INT_RAW_V  0x1
#define RTC_I2C_RX_DATA_INT_RAW_S  6
/* RTC_I2C_ACK_ERR_INT_RAW:RO；位位置：[5]；默认值：1’b0；*/
/*description:ack错误中断raw*/
#define RTC_I2C_ACK_ERR_INT_RAW  (BIT(5))
#define RTC_I2C_ACK_ERR_INT_RAW_M  (BIT(5))
#define RTC_I2C_ACK_ERR_INT_RAW_V  0x1
#define RTC_I2C_ACK_ERR_INT_RAW_S  5
/* RTC_I2C_TIMEOUT_INT_RAW:RO；位位置：[4]；默认值：1’b0；*/
/*描述：原始超时中断*/
#define RTC_I2C_TIMEOUT_INT_RAW  (BIT(4))
#define RTC_I2C_TIMEOUT_INT_RAW_M  (BIT(4))
#define RTC_I2C_TIMEOUT_INT_RAW_V  0x1
#define RTC_I2C_TIMEOUT_INT_RAW_S  4
/* RTC_I2C_TRANS_COMPLETE_INT_RAW:RO；位位置：[3]；默认值：1’b0；*/
/*描述：原始传输完成中断*/
#define RTC_I2C_TRANS_COMPLETE_INT_RAW  (BIT(3))
#define RTC_I2C_TRANS_COMPLETE_INT_RAW_M  (BIT(3))
#define RTC_I2C_TRANS_COMPLETE_INT_RAW_V  0x1
#define RTC_I2C_TRANS_COMPLETE_INT_RAW_S  3
/* RTC_I2C_MASTER_TRAN_COMP_INT_RAW:RO；位位置：[2]；默认值：1’b0；*/
/*描述：主传输完成中断原始*/
#define RTC_I2C_MASTER_TRAN_COMP_INT_RAW  (BIT(2))
#define RTC_I2C_MASTER_TRAN_COMP_INT_RAW_M  (BIT(2))
#define RTC_I2C_MASTER_TRAN_COMP_INT_RAW_V  0x1
#define RTC_I2C_MASTER_TRAN_COMP_INT_RAW_S  2
/* RTC_I2C_ARBITRATION_LOST_INT_RAW:RO；位位置：[1]；默认值：1’b0；*/
/*描述：仲裁丢失中断原始*/
#define RTC_I2C_ARBITRATION_LOST_INT_RAW  (BIT(1))
#define RTC_I2C_ARBITRATION_LOST_INT_RAW_M  (BIT(1))
#define RTC_I2C_ARBITRATION_LOST_INT_RAW_V  0x1
#define RTC_I2C_ARBITRATION_LOST_INT_RAW_S  1
/* RTC_I2C_SLAVE_trans_COMP_INT_RAW:RO；位位置：[0]；默认值：1’b0；*/
/*描述：从属传输完成中断原始*/
#define RTC_I2C_SLAVE_TRAN_COMP_INT_RAW  (BIT(0))
#define RTC_I2C_SLAVE_TRAN_COMP_INT_RAW_M  (BIT(0))
#define RTC_I2C_SLAVE_TRAN_COMP_INT_RAW_V  0x1
#define RTC_I2C_SLAVE_TRAN_COMP_INT_RAW_S  0

#define RTC_I2C_INT_ST_REG          (DR_REG_RTC_I2C_BASE + 0x002c)
/* RTC_I2C_DETECT_START_INT_ST:RO；位位置：[8]；默认值：1’b0；*/
/*描述：检测启动中断状态*/
#define RTC_I2C_DETECT_START_INT_ST  (BIT(8))
#define RTC_I2C_DETECT_START_INT_ST_M  (BIT(8))
#define RTC_I2C_DETECT_START_INT_ST_V  0x1
#define RTC_I2C_DETECT_START_INT_ST_S  8
/* RTC_I2C_TX_DATA_INT_ST:RO；位位置：[7]；默认值：1’b0；*/
/*描述：传输数据中断状态*/
#define RTC_I2C_TX_DATA_INT_ST  (BIT(7))
#define RTC_I2C_TX_DATA_INT_ST_M  (BIT(7))
#define RTC_I2C_TX_DATA_INT_ST_V  0x1
#define RTC_I2C_TX_DATA_INT_ST_S  7
/* RTC_I2C_RX_DATA_INT_ST:RO；位位置：[6]；默认值：1’b0；*/
/*description:接收数据中断状态*/
#define RTC_I2C_RX_DATA_INT_ST  (BIT(6))
#define RTC_I2C_RX_DATA_INT_ST_M  (BIT(6))
#define RTC_I2C_RX_DATA_INT_ST_V  0x1
#define RTC_I2C_RX_DATA_INT_ST_S  6
/* RTC_I2C_ACK_ERR_INT_ST:RO；位位置：[5]；默认值：1’b0；*/
/*description:ack错误中断状态*/
#define RTC_I2C_ACK_ERR_INT_ST  (BIT(5))
#define RTC_I2C_ACK_ERR_INT_ST_M  (BIT(5))
#define RTC_I2C_ACK_ERR_INT_ST_V  0x1
#define RTC_I2C_ACK_ERR_INT_ST_S  5
/* RTC_I2C_TIMEOUT_INT_ST:RO；位位置：[4]；默认值：1’b0；*/
/*description:超时中断状态*/
#define RTC_I2C_TIMEOUT_INT_ST  (BIT(4))
#define RTC_I2C_TIMEOUT_INT_ST_M  (BIT(4))
#define RTC_I2C_TIMEOUT_INT_ST_V  0x1
#define RTC_I2C_TIMEOUT_INT_ST_S  4
/* RTC_I2C_TRANS_COMPLETE_INT_ST:RO；位位置：[3]；默认值：1’b0；*/
/*描述：传输完成中断状态*/
#define RTC_I2C_TRANS_COMPLETE_INT_ST  (BIT(3))
#define RTC_I2C_TRANS_COMPLETE_INT_ST_M  (BIT(3))
#define RTC_I2C_TRANS_COMPLETE_INT_ST_V  0x1
#define RTC_I2C_TRANS_COMPLETE_INT_ST_S  3
/* RTC_I2C_MASTER_TRAN_COMP_INT_ST:RO；位位置：[2]；默认值：1’b0；*/
/*描述：主传输完成中断状态*/
#define RTC_I2C_MASTER_TRAN_COMP_INT_ST  (BIT(2))
#define RTC_I2C_MASTER_TRAN_COMP_INT_ST_M  (BIT(2))
#define RTC_I2C_MASTER_TRAN_COMP_INT_ST_V  0x1
#define RTC_I2C_MASTER_TRAN_COMP_INT_ST_S  2
/* RTC_I2C_ARBITRATION_LOST_INT_ST:RO；位位置：[1]；默认值：1’b0；*/
/*描述：仲裁丢失中断状态*/
#define RTC_I2C_ARBITRATION_LOST_INT_ST  (BIT(1))
#define RTC_I2C_ARBITRATION_LOST_INT_ST_M  (BIT(1))
#define RTC_I2C_ARBITRATION_LOST_INT_ST_V  0x1
#define RTC_I2C_ARBITRATION_LOST_INT_ST_S  1
/* RTC_I2C_SLAVE_trans_COMP_INT_ST:RO；位位置：[0]；默认值：1’b0；*/
/*描述：从传输完成中断状态*/
#define RTC_I2C_SLAVE_TRAN_COMP_INT_ST  (BIT(0))
#define RTC_I2C_SLAVE_TRAN_COMP_INT_ST_M  (BIT(0))
#define RTC_I2C_SLAVE_TRAN_COMP_INT_ST_V  0x1
#define RTC_I2C_SLAVE_TRAN_COMP_INT_ST_S  0

#define RTC_I2C_INT_ENA_REG          (DR_REG_RTC_I2C_BASE + 0x0030)
/* RTC_I2C_DETECT_START_INT_ENA:R/W；位位置：[8]；默认值：1’b0；*/
/*描述：启用检测启动中断*/
#define RTC_I2C_DETECT_START_INT_ENA  (BIT(8))
#define RTC_I2C_DETECT_START_INT_ENA_M  (BIT(8))
#define RTC_I2C_DETECT_START_INT_ENA_V  0x1
#define RTC_I2C_DETECT_START_INT_ENA_S  8
/* RTC_I2C_TX_DATA_INT_ENA：R/W；位位置：[7]；默认值：1’b0；*/
/*description:启用传输数据中断*/
#define RTC_I2C_TX_DATA_INT_ENA  (BIT(7))
#define RTC_I2C_TX_DATA_INT_ENA_M  (BIT(7))
#define RTC_I2C_TX_DATA_INT_ENA_V  0x1
#define RTC_I2C_TX_DATA_INT_ENA_S  7
/* RTC_I2C_RX_DATA_INT_ENA:R/W；位位置：[6]；默认值：1’b0；*/
/*description:启用接收数据中断*/
#define RTC_I2C_RX_DATA_INT_ENA  (BIT(6))
#define RTC_I2C_RX_DATA_INT_ENA_M  (BIT(6))
#define RTC_I2C_RX_DATA_INT_ENA_V  0x1
#define RTC_I2C_RX_DATA_INT_ENA_S  6
/* RTC_I2C_ACK_ERR_INT_ENA:R/W；位位置：[5]；默认值：1’b0；*/
/*描述：启用eack错误中断*/
#define RTC_I2C_ACK_ERR_INT_ENA  (BIT(5))
#define RTC_I2C_ACK_ERR_INT_ENA_M  (BIT(5))
#define RTC_I2C_ACK_ERR_INT_ENA_V  0x1
#define RTC_I2C_ACK_ERR_INT_ENA_S  5
/* RTC_I2C_TIMEOUT_INT_ENA：R/W；位位置：[4]；默认值：1’b0；*/
/*description:启用超时中断*/
#define RTC_I2C_TIMEOUT_INT_ENA  (BIT(4))
#define RTC_I2C_TIMEOUT_INT_ENA_M  (BIT(4))
#define RTC_I2C_TIMEOUT_INT_ENA_V  0x1
#define RTC_I2C_TIMEOUT_INT_ENA_S  4
/* RTC_I2C_TRANS_COMPLETE_INT_ENA:R/W；位位置：[3]；默认值：1’b0；*/
/*description:启用传输完成中断*/
#define RTC_I2C_TRANS_COMPLETE_INT_ENA  (BIT(3))
#define RTC_I2C_TRANS_COMPLETE_INT_ENA_M  (BIT(3))
#define RTC_I2C_TRANS_COMPLETE_INT_ENA_V  0x1
#define RTC_I2C_TRANS_COMPLETE_INT_ENA_S  3
/* RTC_I2C_MASTER_TRAN_COMP_INT_ENA:R/W；位位置：[2]；默认值：1’b0；*/
/*描述：启用主传输完成中断*/
#define RTC_I2C_MASTER_TRAN_COMP_INT_ENA  (BIT(2))
#define RTC_I2C_MASTER_TRAN_COMP_INT_ENA_M  (BIT(2))
#define RTC_I2C_MASTER_TRAN_COMP_INT_ENA_V  0x1
#define RTC_I2C_MASTER_TRAN_COMP_INT_ENA_S  2
/* RTC_I2C_ARBITRATION_LOST_INT_ENA:R/W；位位置：[1]；默认值：1’b0；*/
/*description:启用仲裁丢失中断*/
#define RTC_I2C_ARBITRATION_LOST_INT_ENA  (BIT(1))
#define RTC_I2C_ARBITRATION_LOST_INT_ENA_M  (BIT(1))
#define RTC_I2C_ARBITRATION_LOST_INT_ENA_V  0x1
#define RTC_I2C_ARBITRATION_LOST_INT_ENA_S  1
/* RTC_I2C_SLAVE_trans_COMP_INT_ENA:R/W；位位置：[0]；默认值：1’b0；*/
/*描述：启用从属传输完成中断*/
#define RTC_I2C_SLAVE_TRAN_COMP_INT_ENA  (BIT(0))
#define RTC_I2C_SLAVE_TRAN_COMP_INT_ENA_M  (BIT(0))
#define RTC_I2C_SLAVE_TRAN_COMP_INT_ENA_V  0x1
#define RTC_I2C_SLAVE_TRAN_COMP_INT_ENA_S  0

#define RTC_I2C_DATA_REG          (DR_REG_RTC_I2C_BASE + 0x0034)
/* RTC_I2C_DONE:RO；位位置：[31]；默认值：1’b0；*/
/*说明：i2c已完成*/
#define RTC_I2C_DONE  (BIT(31))
#define RTC_I2C_DONE_M  (BIT(31))
#define RTC_I2C_DONE_V  0x1
#define RTC_I2C_DONE_S  31
/* RTC_I2C_SLAVE_TX_DATA：R/W；比特位置：[15:8]；默认值：8'0；*/
/*description:从设备发送的数据*/
#define RTC_I2C_SLAVE_TX_DATA  0x000000FF
#define RTC_I2C_SLAVE_TX_DATA_M  ((RTC_I2C_SLAVE_TX_DATA_V)<<(RTC_I2C_SLAVE_TX_DATA_S))
#define RTC_I2C_SLAVE_TX_DATA_V  0xFF
#define RTC_I2C_SLAVE_TX_DATA_S  8
/* RTC_I2C_RDATA:RO；位位置：[7:0]；默认值：8'0；*/
/*description:接收的数据*/
#define RTC_I2C_RDATA  0x000000FF
#define RTC_I2C_RDATA_M  ((RTC_I2C_RDATA_V)<<(RTC_I2C_RDATA_S))
#define RTC_I2C_RDATA_V  0xFF
#define RTC_I2C_RDATA_S  0

#define RTC_I2C_CMD0_REG          (DR_REG_RTC_I2C_BASE + 0x0038)
/* RTC_I2C_COMMAND0_DONE:RO；位位置：[31]；默认值：1’b0；*/
/*描述：command0_done*/
#define RTC_I2C_COMMAND0_DONE  (BIT(31))
#define RTC_I2C_COMMAND0_DONE_M  (BIT(31))
#define RTC_I2C_COMMAND0_DONE_V  0x1
#define RTC_I2C_COMMAND0_DONE_S  31
/* RTC_I2C_COMMAND0:R/W；比特位置：[13:0]；默认值：14'h0903；*/
/*description:命令0*/
#define RTC_I2C_COMMAND0  0x00003FFF
#define RTC_I2C_COMMAND0_M  ((RTC_I2C_COMMAND0_V)<<(RTC_I2C_COMMAND0_S))
#define RTC_I2C_COMMAND0_V  0x3FFF
#define RTC_I2C_COMMAND0_S  0

#define RTC_I2C_CMD1_REG          (DR_REG_RTC_I2C_BASE + 0x003c)
/* RTC_I2C_COMMAND1_DONE:RO；位位置：[31]；默认值：1’b0；*/
/*描述：command1_done*/
#define RTC_I2C_COMMAND1_DONE  (BIT(31))
#define RTC_I2C_COMMAND1_DONE_M  (BIT(31))
#define RTC_I2C_COMMAND1_DONE_V  0x1
#define RTC_I2C_COMMAND1_DONE_S  31
/* RTC_I2C_COMMAND1:R/W；比特位置：[13:0]；默认值：14'h1901；*/
/*description:命令1*/
#define RTC_I2C_COMMAND1  0x00003FFF
#define RTC_I2C_COMMAND1_M  ((RTC_I2C_COMMAND1_V)<<(RTC_I2C_COMMAND1_S))
#define RTC_I2C_COMMAND1_V  0x3FFF
#define RTC_I2C_COMMAND1_S  0

#define RTC_I2C_CMD2_REG          (DR_REG_RTC_I2C_BASE + 0x0040)
/* RTC_I2C_COMMAND2_DONE:RO；位位置：[31]；默认值：1’b0；*/
/*描述：command2_done*/
#define RTC_I2C_COMMAND2_DONE  (BIT(31))
#define RTC_I2C_COMMAND2_DONE_M  (BIT(31))
#define RTC_I2C_COMMAND2_DONE_V  0x1
#define RTC_I2C_COMMAND2_DONE_S  31
/* RTC_I2C_COMMAND2:R/W；比特位置：[13:0]；默认值：14'h0902；*/
/*description:命令2*/
#define RTC_I2C_COMMAND2  0x00003FFF
#define RTC_I2C_COMMAND2_M  ((RTC_I2C_COMMAND2_V)<<(RTC_I2C_COMMAND2_S))
#define RTC_I2C_COMMAND2_V  0x3FFF
#define RTC_I2C_COMMAND2_S  0

#define RTC_I2C_CMD3_REG          (DR_REG_RTC_I2C_BASE + 0x0044)
/* RTC_I2C_COMMAND3_DONE:RO；位位置：[31]；默认值：1’b0；*/
/*描述：command3_done*/
#define RTC_I2C_COMMAND3_DONE  (BIT(31))
#define RTC_I2C_COMMAND3_DONE_M  (BIT(31))
#define RTC_I2C_COMMAND3_DONE_V  0x1
#define RTC_I2C_COMMAND3_DONE_S  31
/* RTC_I2C_COMMAND3:R/W；比特位置：[13:0]；默认值：14'h0101；*/
/*description:命令3*/
#define RTC_I2C_COMMAND3  0x00003FFF
#define RTC_I2C_COMMAND3_M  ((RTC_I2C_COMMAND3_V)<<(RTC_I2C_COMMAND3_S))
#define RTC_I2C_COMMAND3_V  0x3FFF
#define RTC_I2C_COMMAND3_S  0

#define RTC_I2C_CMD4_REG          (DR_REG_RTC_I2C_BASE + 0x0048)
/* RTC_I2C_COMMAND4_DONE:RO；位位置：[31]；默认值：1’b0；*/
/*description:command4_done*/
#define RTC_I2C_COMMAND4_DONE  (BIT(31))
#define RTC_I2C_COMMAND4_DONE_M  (BIT(31))
#define RTC_I2C_COMMAND4_DONE_V  0x1
#define RTC_I2C_COMMAND4_DONE_S  31
/* RTC_I2C_COMMAND4:R/W；比特位置：[13:0]；默认值：14'h0901；*/
/*description:命令4*/
#define RTC_I2C_COMMAND4  0x00003FFF
#define RTC_I2C_COMMAND4_M  ((RTC_I2C_COMMAND4_V)<<(RTC_I2C_COMMAND4_S))
#define RTC_I2C_COMMAND4_V  0x3FFF
#define RTC_I2C_COMMAND4_S  0

#define RTC_I2C_CMD5_REG          (DR_REG_RTC_I2C_BASE + 0x004c)
/* RTC_I2C_COMMAND5_DONE:RO；位位置：[31]；默认值：1’b0；*/
/*description:command5_done*/
#define RTC_I2C_COMMAND5_DONE  (BIT(31))
#define RTC_I2C_COMMAND5_DONE_M  (BIT(31))
#define RTC_I2C_COMMAND5_DONE_V  0x1
#define RTC_I2C_COMMAND5_DONE_S  31
/* RTC_I2C_COMMAND5:R/W；比特位置：[13:0]；默认值：14'h1701；*/
/*description:命令5*/
#define RTC_I2C_COMMAND5  0x00003FFF
#define RTC_I2C_COMMAND5_M  ((RTC_I2C_COMMAND5_V)<<(RTC_I2C_COMMAND5_S))
#define RTC_I2C_COMMAND5_V  0x3FFF
#define RTC_I2C_COMMAND5_S  0

#define RTC_I2C_CMD6_REG          (DR_REG_RTC_I2C_BASE + 0x0050)
/* RTC_I2C_COMMAND6_DONE:RO；位位置：[31]；默认值：1’b0；*/
/*描述：command6_done*/
#define RTC_I2C_COMMAND6_DONE  (BIT(31))
#define RTC_I2C_COMMAND6_DONE_M  (BIT(31))
#define RTC_I2C_COMMAND6_DONE_V  0x1
#define RTC_I2C_COMMAND6_DONE_S  31
/* RTC_I2C_COMMAND6:R/W；比特位置：[13:0]；默认值：14'h1901；*/
/*description:命令6*/
#define RTC_I2C_COMMAND6  0x00003FFF
#define RTC_I2C_COMMAND6_M  ((RTC_I2C_COMMAND6_V)<<(RTC_I2C_COMMAND6_S))
#define RTC_I2C_COMMAND6_V  0x3FFF
#define RTC_I2C_COMMAND6_S  0

#define RTC_I2C_CMD7_REG          (DR_REG_RTC_I2C_BASE + 0x0054)
/* RTC_I2C_COMMAND7_DONE:RO；位位置：[31]；默认值：1’b0；*/
/*描述：command7_done*/
#define RTC_I2C_COMMAND7_DONE  (BIT(31))
#define RTC_I2C_COMMAND7_DONE_M  (BIT(31))
#define RTC_I2C_COMMAND7_DONE_V  0x1
#define RTC_I2C_COMMAND7_DONE_S  31
/* RTC_I2C_COMMAND7:R/W；比特位置：[13:0]；默认值：14'h0904；*/
/*description:命令7*/
#define RTC_I2C_COMMAND7  0x00003FFF
#define RTC_I2C_COMMAND7_M  ((RTC_I2C_COMMAND7_V)<<(RTC_I2C_COMMAND7_S))
#define RTC_I2C_COMMAND7_V  0x3FFF
#define RTC_I2C_COMMAND7_S  0

#define RTC_I2C_CMD8_REG          (DR_REG_RTC_I2C_BASE + 0x0058)
/* RTC_I2C_COMMAND8_DONE:RO；位位置：[31]；默认值：1’b0；*/
/*描述：command8_done*/
#define RTC_I2C_COMMAND8_DONE  (BIT(31))
#define RTC_I2C_COMMAND8_DONE_M  (BIT(31))
#define RTC_I2C_COMMAND8_DONE_V  0x1
#define RTC_I2C_COMMAND8_DONE_S  31
/* RTC_I2C_COMMAND8:R/W；比特位置：[13:0]；默认值：14'h1901；*/
/*description:命令8*/
#define RTC_I2C_COMMAND8  0x00003FFF
#define RTC_I2C_COMMAND8_M  ((RTC_I2C_COMMAND8_V)<<(RTC_I2C_COMMAND8_S))
#define RTC_I2C_COMMAND8_V  0x3FFF
#define RTC_I2C_COMMAND8_S  0

#define RTC_I2C_CMD9_REG          (DR_REG_RTC_I2C_BASE + 0x005c)
/* RTC_I2C_COMMAND9_DONE:RO；位位置：[31]；默认值：1’b0；*/
/*描述：command9_done*/
#define RTC_I2C_COMMAND9_DONE  (BIT(31))
#define RTC_I2C_COMMAND9_DONE_M  (BIT(31))
#define RTC_I2C_COMMAND9_DONE_V  0x1
#define RTC_I2C_COMMAND9_DONE_S  31
/* RTC_I2C_COMMAND9:R/W；比特位置：[13:0]；默认值：14'h0903；*/
/*description:命令9*/
#define RTC_I2C_COMMAND9  0x00003FFF
#define RTC_I2C_COMMAND9_M  ((RTC_I2C_COMMAND9_V)<<(RTC_I2C_COMMAND9_S))
#define RTC_I2C_COMMAND9_V  0x3FFF
#define RTC_I2C_COMMAND9_S  0

#define RTC_I2C_CMD10_REG          (DR_REG_RTC_I2C_BASE + 0x0060)
/* RTC_I2C_COMMAND10_DONE:RO；位位置：[31]；默认值：1’b0；*/
/*描述：command10_done*/
#define RTC_I2C_COMMAND10_DONE  (BIT(31))
#define RTC_I2C_COMMAND10_DONE_M  (BIT(31))
#define RTC_I2C_COMMAND10_DONE_V  0x1
#define RTC_I2C_COMMAND10_DONE_S  31
/* RTC_I2C_COMMAND10:R/W；比特位置：[13:0]；默认值：14'h0101；*/
/*description:命令10*/
#define RTC_I2C_COMMAND10  0x00003FFF
#define RTC_I2C_COMMAND10_M  ((RTC_I2C_COMMAND10_V)<<(RTC_I2C_COMMAND10_S))
#define RTC_I2C_COMMAND10_V  0x3FFF
#define RTC_I2C_COMMAND10_S  0

#define RTC_I2C_CMD11_REG          (DR_REG_RTC_I2C_BASE + 0x0064)
/* RTC_I2C_COMMAND11_DONE:RO；位位置：[31]；默认值：1’b0；*/
/*描述：command11_done*/
#define RTC_I2C_COMMAND11_DONE  (BIT(31))
#define RTC_I2C_COMMAND11_DONE_M  (BIT(31))
#define RTC_I2C_COMMAND11_DONE_V  0x1
#define RTC_I2C_COMMAND11_DONE_S  31
/* RTC_I2C_COMMAND11:R/W；比特位置：[13:0]；默认值：14'h0901；*/
/*description:命令11*/
#define RTC_I2C_COMMAND11  0x00003FFF
#define RTC_I2C_COMMAND11_M  ((RTC_I2C_COMMAND11_V)<<(RTC_I2C_COMMAND11_S))
#define RTC_I2C_COMMAND11_V  0x3FFF
#define RTC_I2C_COMMAND11_S  0

#define RTC_I2C_CMD12_REG          (DR_REG_RTC_I2C_BASE + 0x0068)
/* RTC_I2C_COMMAND12_DONE:RO；位位置：[31]；默认值：1’b0；*/
/*描述：command12_done*/
#define RTC_I2C_COMMAND12_DONE  (BIT(31))
#define RTC_I2C_COMMAND12_DONE_M  (BIT(31))
#define RTC_I2C_COMMAND12_DONE_V  0x1
#define RTC_I2C_COMMAND12_DONE_S  31
/* RTC_I2C_COMMAND12:R/W；比特位置：[13:0]；默认值：14'h1701；*/
/*description:命令12*/
#define RTC_I2C_COMMAND12  0x00003FFF
#define RTC_I2C_COMMAND12_M  ((RTC_I2C_COMMAND12_V)<<(RTC_I2C_COMMAND12_S))
#define RTC_I2C_COMMAND12_V  0x3FFF
#define RTC_I2C_COMMAND12_S  0

#define RTC_I2C_CMD13_REG          (DR_REG_RTC_I2C_BASE + 0x006c)
/* RTC_I2C_COMMAND13_DONE:RO；位位置：[31]；默认值：1’b0；*/
/*描述：命令13_done*/
#define RTC_I2C_COMMAND13_DONE  (BIT(31))
#define RTC_I2C_COMMAND13_DONE_M  (BIT(31))
#define RTC_I2C_COMMAND13_DONE_V  0x1
#define RTC_I2C_COMMAND13_DONE_S  31
/* RTC_I2C_COMMAND13:R/W；比特位置：[13:0]；默认值：14'h1901；*/
/*description:命令13*/
#define RTC_I2C_COMMAND13  0x00003FFF
#define RTC_I2C_COMMAND13_M  ((RTC_I2C_COMMAND13_V)<<(RTC_I2C_COMMAND13_S))
#define RTC_I2C_COMMAND13_V  0x3FFF
#define RTC_I2C_COMMAND13_S  0

#define RTC_I2C_CMD14_REG          (DR_REG_RTC_I2C_BASE + 0x0070)
/* RTC_I2C_COMMAND14_DONE:RO；位位置：[31]；默认值：1’b0；*/
/*description:命令14_done*/
#define RTC_I2C_COMMAND14_DONE  (BIT(31))
#define RTC_I2C_COMMAND14_DONE_M  (BIT(31))
#define RTC_I2C_COMMAND14_DONE_V  0x1
#define RTC_I2C_COMMAND14_DONE_S  31
/* RTC_I2C_COMMAND14:R/W；比特位置：[13:0]；默认值：14'0；*/
/*description:命令14*/
#define RTC_I2C_COMMAND14  0x00003FFF
#define RTC_I2C_COMMAND14_M  ((RTC_I2C_COMMAND14_V)<<(RTC_I2C_COMMAND14_S))
#define RTC_I2C_COMMAND14_V  0x3FFF
#define RTC_I2C_COMMAND14_S  0

#define RTC_I2C_CMD15_REG          (DR_REG_RTC_I2C_BASE + 0x0074)
/* RTC_I2C_COMMAND15_DONE:RO；位位置：[31]；默认值：1’b0；*/
/*描述：command15_done*/
#define RTC_I2C_COMMAND15_DONE  (BIT(31))
#define RTC_I2C_COMMAND15_DONE_M  (BIT(31))
#define RTC_I2C_COMMAND15_DONE_V  0x1
#define RTC_I2C_COMMAND15_DONE_S  31
/* RTC_I2C_COMMAND15:R/W；比特位置：[13:0]；默认值：14'0；*/
/*description:命令15*/
#define RTC_I2C_COMMAND15  0x00003FFF
#define RTC_I2C_COMMAND15_M  ((RTC_I2C_COMMAND15_V)<<(RTC_I2C_COMMAND15_S))
#define RTC_I2C_COMMAND15_V  0x3FFF
#define RTC_I2C_COMMAND15_S  0

#define RTC_I2C_DATE_REG          (DR_REG_RTC_I2C_BASE + 0x00FC)
/* RTC_I2C_DATE:R/W；位位置：[27:0]；默认值：28'h1905310；*/
/*说明：*/
#define RTC_I2C_DATE  0x0FFFFFFF
#define RTC_I2C_DATE_M  ((RTC_I2C_DATE_V)<<(RTC_I2C_DATE_S))
#define RTC_I2C_DATE_V  0xFFFFFFF
#define RTC_I2C_DATE_S  0

#ifdef __cplusplus
}
#endif



#endif /*_SOC_RTC_I2C_REG_H_ */

