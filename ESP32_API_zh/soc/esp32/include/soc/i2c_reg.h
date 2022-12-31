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
#ifndef _SOC_I2C_REG_H_
#define _SOC_I2C_REG_H_


#include "soc.h"

#define REG_I2C_BASE(i)    (DR_REG_I2C_EXT_BASE + (i) * 0x14000 )

#define I2C_SCL_LOW_PERIOD_REG(i)          (REG_I2C_BASE(i) + 0x0000)
/* I2C_SCL_LOW_PERIOD:R/W；比特位置：[13:0]；默认值：14'b0；*/
/*description:此寄存器用于配置SCL时钟的低电平宽度。*/
#define I2C_SCL_LOW_PERIOD  0x00003FFF
#define I2C_SCL_LOW_PERIOD_M  ((I2C_SCL_LOW_PERIOD_V)<<(I2C_SCL_LOW_PERIOD_S))
#define I2C_SCL_LOW_PERIOD_V  0x3FFF
#define I2C_SCL_LOW_PERIOD_S  0

#define I2C_CTR_REG(i)          (REG_I2C_BASE(i) + 0x0004)
/* I2C_CLK_EN:R/W；位位置：[8]；默认值：1’b0；*/
/*description:这是用于读取或写入寄存器的时钟门控控制位。*/
#define I2C_CLK_EN  (BIT(8))
#define I2C_CLK_EN_M  (BIT(8))
#define I2C_CLK_EN_V  0x1
#define I2C_CLK_EN_S  8
/* I2C_RX_LSB_FIRST:R/W；位位置：[7]；默认值：1'0；*/
/*description:此位用于控制接收数据的存储模式。1： 从最高有效位0接收数据：从最低有效位接收数据*/
#define I2C_RX_LSB_FIRST  (BIT(7))
#define I2C_RX_LSB_FIRST_M  (BIT(7))
#define I2C_RX_LSB_FIRST_V  0x1
#define I2C_RX_LSB_FIRST_S  7
/* I2C_TX_LSB_FIRST:R/W；位位置：[6]；默认值：1’b0；*/
/*description:此位用于控制需要发送的数据的发送模式。1： 从最高有效位0接收数据：从最低有效位接收数据*/
#define I2C_TX_LSB_FIRST  (BIT(6))
#define I2C_TX_LSB_FIRST_M  (BIT(6))
#define I2C_TX_LSB_FIRST_V  0x1
#define I2C_TX_LSB_FIRST_S  6
/* I2C_TRANS_START:R/W；位位置：[5]；默认值：1’b0；*/
/*description:设置此位以开始在txfifo中发送数据。*/
#define I2C_TRANS_START  (BIT(5))
#define I2C_TRANS_START_M  (BIT(5))
#define I2C_TRANS_START_V  0x1
#define I2C_TRANS_START_S  5
/* I2C_MS_MODE：R/W；位位置：[4]；默认值：1’b0；*/
/*description:设置此位以将模块配置为i2c主设备，清除此位以配置模块为i2c从设备。*/
#define I2C_MS_MODE  (BIT(4))
#define I2C_MS_MODE_M  (BIT(4))
#define I2C_MS_MODE_V  0x1
#define I2C_MS_MODE_S  4
/* I2C_SAMPLE_SCL_LEVEL:R/W；位位置：[2]；默认值：1’b0；*/
/*description:将此位设置为SCL低电平的采样数据。清除此位以采样SCL高电平的数据。*/
#define I2C_SAMPLE_SCL_LEVEL  (BIT(2))
#define I2C_SAMPLE_SCL_LEVEL_M  (BIT(2))
#define I2C_SAMPLE_SCL_LEVEL_V  0x1
#define I2C_SAMPLE_SCL_LEVEL_S  2
/* I2C_SCL_FORCE_OUT:R/W；位位置：[1]；默认值：1’b1；*/
/*描述：1：正常输出scl时钟0：交换scl_o和scl_oe的功能（scl_o是原始的内部输出scl信号scl_oe是内部输出scl信号的启用位）*/
#define I2C_SCL_FORCE_OUT  (BIT(1))
#define I2C_SCL_FORCE_OUT_M  (BIT(1))
#define I2C_SCL_FORCE_OUT_V  0x1
#define I2C_SCL_FORCE_OUT_S  1
/* I2C_SDA_frce_OUT:R/W；位位置：[0]；默认值：1’b1；*/
/*描述：1：正常输出sda数据0：交换sda\o和sda\oe的函数（sda\o是原始内部输出sda信号sda\oee是内部输出sdb信号的启用位）*/
#define I2C_SDA_FORCE_OUT  (BIT(0))
#define I2C_SDA_FORCE_OUT_M  (BIT(0))
#define I2C_SDA_FORCE_OUT_V  0x1
#define I2C_SDA_FORCE_OUT_S  0

#define I2C_SR_REG(i)          (REG_I2C_BASE(i) + 0x0008)
/* I2C_SCL_STATE_LAST:RO；位位置：[30:28]；默认值：3'b0；*/
/*description:此寄存器存储状态机的值以生成SCL。3'h0:SCL_IDLE 3'h1:SCL_START 3'h2:SCL_LOW_EDGE 3'h3:SCL_LLOW 3'h4:SCL_HIGH_EDGE 3'h5:SCL_HIGH 3'h6:SCL_STOP*/
#define I2C_SCL_STATE_LAST  0x00000007
#define I2C_SCL_STATE_LAST_M  ((I2C_SCL_STATE_LAST_V)<<(I2C_SCL_STATE_LAST_S))
#define I2C_SCL_STATE_LAST_V  0x7
#define I2C_SCL_STATE_LAST_S  28
/* I2C_SCL_MAIN_STATE_LAST:RO；比特位置：[26:24]；默认值：3'b0；*/
/*description:此寄存器存储i2c模块的状态机值。3'h0:SCL_MAIN_IDLE 3'h1:SCL_ADDRESS_SHIFT 3'h2:SCL_ACK_ADDRESS 3'h3:SCL_RX_DATA 3'h4 SCL_TX_DATA 3'h5:SCL_SEND_ACK 3'h6:SCL_WAIT_ACK*/
#define I2C_SCL_MAIN_STATE_LAST  0x00000007
#define I2C_SCL_MAIN_STATE_LAST_M  ((I2C_SCL_MAIN_STATE_LAST_V)<<(I2C_SCL_MAIN_STATE_LAST_S))
#define I2C_SCL_MAIN_STATE_LAST_V  0x7
#define I2C_SCL_MAIN_STATE_LAST_S  24
/* I2C_TXFIFO_CNT:RO；比特位置：[23:18]；默认值：6'b0；*/
/*description:此寄存器将接收的数据量存储在ram中。*/
#define I2C_TXFIFO_CNT  0x0000003F
#define I2C_TXFIFO_CNT_M  ((I2C_TXFIFO_CNT_V)<<(I2C_TXFIFO_CNT_S))
#define I2C_TXFIFO_CNT_V  0x3F
#define I2C_TXFIFO_CNT_S  18
/* I2C_rxifo_CNT:RO；比特位置：[13:8]；默认值：6'b0；*/
/*description:此寄存器表示需要发送的数据量。*/
#define I2C_RXFIFO_CNT  0x0000003F
#define I2C_RXFIFO_CNT_M  ((I2C_RXFIFO_CNT_V)<<(I2C_RXFIFO_CNT_S))
#define I2C_RXFIFO_CNT_V  0x3F
#define I2C_RXFIFO_CNT_S  8
/* I2C_BYTE_TRANS:RO；位位置：[6]；默认值：1’b0；*/
/*description:当传输一个字节时，此寄存器变为高电平。*/
#define I2C_BYTE_TRANS  (BIT(6))
#define I2C_BYTE_TRANS_M  (BIT(6))
#define I2C_BYTE_TRANS_V  0x1
#define I2C_BYTE_TRANS_S  6
/* I2C_SLAVE_ADDRESSED:RO；位位置：[5]；默认值：1’b0；*/
/*描述：当配置为i2c从设备，并且主设备发送的地址等于从设备的地址时，该位将为高电平。*/
#define I2C_SLAVE_ADDRESSED  (BIT(5))
#define I2C_SLAVE_ADDRESSED_M  (BIT(5))
#define I2C_SLAVE_ADDRESSED_V  0x1
#define I2C_SLAVE_ADDRESSED_S  5
/* I2C_BUS_BUSY:RO；位位置：[4]；默认值：1’b0；*/
/*描述：1:I2C总线正忙于传输数据。0:I2C总线处于空闲状态。*/
#define I2C_BUS_BUSY  (BIT(4))
#define I2C_BUS_BUSY_M  (BIT(4))
#define I2C_BUS_BUSY_V  0x1
#define I2C_BUS_BUSY_S  4
/* I2C_ARB_list:RO；位位置：[3]；默认值：1’b0；*/
/*描述：当I2C失去对SDA线的控制时，此寄存器变为高电平。*/
#define I2C_ARB_LOST  (BIT(3))
#define I2C_ARB_LOST_M  (BIT(3))
#define I2C_ARB_LOST_V  0x1
#define I2C_ARB_LOST_S  3
/* I2C_TIME_OUT:RO；位位置：[2]；默认值：1’b0；*/
/*描述：当I2C需要超过time_out_reg时钟才能接收数据时，此寄存器将变为高电平。*/
#define I2C_TIME_OUT  (BIT(2))
#define I2C_TIME_OUT_M  (BIT(2))
#define I2C_TIME_OUT_V  0x1
#define I2C_TIME_OUT_S  2
/* I2C_SLAVE_RW:RO；位位置：[1]；默认值：1’b0；*/
/*描述：当处于从模式1时：主读从0：主写从。*/
#define I2C_SLAVE_RW  (BIT(1))
#define I2C_SLAVE_RW_M  (BIT(1))
#define I2C_SLAVE_RW_V  0x1
#define I2C_SLAVE_RW_S  1
/* I2C_ACK_REC:RO；位位置：[0]；默认值：1’b0；*/
/*description:此寄存器存储ACK位的值。*/
#define I2C_ACK_REC  (BIT(0))
#define I2C_ACK_REC_M  (BIT(0))
#define I2C_ACK_REC_V  0x1
#define I2C_ACK_REC_S  0

#define I2C_TO_REG(i)          (REG_I2C_BASE(i) + 0x000c)
/* I2C_TIME_OUT_REG:R/W；比特位置：[19:0]；默认值：20'b0；*/
/*description:此寄存器用于配置接收数据的最大时钟数。*/
#define I2C_TIME_OUT_REG  0x000FFFFF
#define I2C_TIME_OUT_REG_M  ((I2C_TIME_OUT_REG_V)<<(I2C_TIME_OUT_REG_S))
#define I2C_TIME_OUT_REG_V  0xFFFFF
#define I2C_TIME_OUT_REG_S  0

#define I2C_SLAVE_ADDR_REG(i)          (REG_I2C_BASE(i) + 0x0010)
/* I2C_ADDR_10BIT_EN:R/W；位位置：[31]；默认值：1’b0；*/
/*description:此寄存器用于启用从设备10位地址模式。*/
#define I2C_ADDR_10BIT_EN  (BIT(31))
#define I2C_ADDR_10BIT_EN_M  (BIT(31))
#define I2C_ADDR_10BIT_EN_V  0x1
#define I2C_ADDR_10BIT_EN_S  31
/* I2C_SLAVE_ADDR:R/W；位位置：[14:0]；默认值：15'b0；*/
/*描述：当配置为i2c从机时，此寄存器用于配置从机的地址。*/
#define I2C_SLAVE_ADDR  0x00007FFF
#define I2C_SLAVE_ADDR_M  ((I2C_SLAVE_ADDR_V)<<(I2C_SLAVE_ADDR_S))
#define I2C_SLAVE_ADDR_V  0x7FFF
#define I2C_SLAVE_ADDR_S  0

#define I2C_RXFIFO_ST_REG(i)          (REG_I2C_BASE(i) + 0x0014)
/* I2C_TXFIFO_END_ADDR:RO；比特位置：[19:15]；默认值：5’b0；*/
/*description：这是最后一次发送数据的偏移地址，如nonfof_tx_thres寄存器中所述。*/
#define I2C_TXFIFO_END_ADDR  0x0000001F
#define I2C_TXFIFO_END_ADDR_M  ((I2C_TXFIFO_END_ADDR_V)<<(I2C_TXFIFO_END_ADDR_S))
#define I2C_TXFIFO_END_ADDR_V  0x1F
#define I2C_TXFIFO_END_ADDR_S  15
/* I2C_TXFIFO_START_ADDR:RO；比特位置：[14:10]；默认值：5’b0；*/
/*description：这是第一个发送数据的偏移地址，如nonfof_tx_thres寄存器中所述。*/
#define I2C_TXFIFO_START_ADDR  0x0000001F
#define I2C_TXFIFO_START_ADDR_M  ((I2C_TXFIFO_START_ADDR_V)<<(I2C_TXFIFO_START_ADDR_S))
#define I2C_TXFIFO_START_ADDR_V  0x1F
#define I2C_TXFIFO_START_ADDR_S  10
/* I2C_rxifo_END_ADDR:RO；比特位置：[9:5]；默认值：5’b0；*/
/*description:这是第一个接收数据的偏移地址，如nonifo_rx_thres_register中所述。*/
#define I2C_RXFIFO_END_ADDR  0x0000001F
#define I2C_RXFIFO_END_ADDR_M  ((I2C_RXFIFO_END_ADDR_V)<<(I2C_RXFIFO_END_ADDR_S))
#define I2C_RXFIFO_END_ADDR_V  0x1F
#define I2C_RXFIFO_END_ADDR_S  5
/* I2C_rxfix_START_ADDR:RO；位位置：[4:0]；默认值：5’b0；*/
/*description:这是最后一个接收数据的偏移地址，如nonifo_rx_thres_register中所述。*/
#define I2C_RXFIFO_START_ADDR  0x0000001F
#define I2C_RXFIFO_START_ADDR_M  ((I2C_RXFIFO_START_ADDR_V)<<(I2C_RXFIFO_START_ADDR_S))
#define I2C_RXFIFO_START_ADDR_V  0x1F
#define I2C_RXFIFO_START_ADDR_S  0

#define I2C_FIFO_CONF_REG(i)          (REG_I2C_BASE(i) + 0x0018)
/* I2C_nonfiform_TX_THRES:R/W；位位置：[25:20]；默认值：6'h15；*/
/*描述：当I2C发送的数据超过非ifo_tx_thres数据时，它将产生tx_send_empty_int_raw中断，并更新发送数据的当前偏移地址。*/
#define I2C_NONFIFO_TX_THRES  0x0000003F
#define I2C_NONFIFO_TX_THRES_M  ((I2C_NONFIFO_TX_THRES_V)<<(I2C_NONFIFO_TX_THRES_S))
#define I2C_NONFIFO_TX_THRES_V  0x3F
#define I2C_NONFIFO_TX_THRES_S  20
/* I2C_nonifo_RX_THRES:R/W；比特位置：[19:14]；默认值：6'h15；*/
/*描述：当I2C接收到的数据超过非ifo_rx_thres数据时，它将产生rx_send_full_int_raw中断，并更新接收数据的当前偏移地址。*/
#define I2C_NONFIFO_RX_THRES  0x0000003F
#define I2C_NONFIFO_RX_THRES_M  ((I2C_NONFIFO_RX_THRES_V)<<(I2C_NONFIFO_RX_THRES_S))
#define I2C_NONFIFO_RX_THRES_V  0x3F
#define I2C_NONFIFO_RX_THRES_S  14
/* I2C_TX_FIFO_RST:R/W；位位置：[13]；默认值：1’b0；*/
/*description:当使用apb fifo访问时，设置此位以重置tx fifo。*/
#define I2C_TX_FIFO_RST  (BIT(13))
#define I2C_TX_FIFO_RST_M  (BIT(13))
#define I2C_TX_FIFO_RST_V  0x1
#define I2C_TX_FIFO_RST_S  13
/* I2C_RX_FIFO_RST:R/W；位位置：[12]；默认值：1’b0；*/
/*description:当使用apb fifo访问时，设置此位以重置rx fifo。*/
#define I2C_RX_FIFO_RST  (BIT(12))
#define I2C_RX_FIFO_RST_M  (BIT(12))
#define I2C_RX_FIFO_RST_V  0x1
#define I2C_RX_FIFO_RST_S  12
/* I2C_FIFO_ADDR_CFG_EN:R/W；位位置：[11]；默认值：1’b0；*/
/*描述：当该位设置为1时，地址后的字节表示I2C从机ram的偏移地址。*/
#define I2C_FIFO_ADDR_CFG_EN  (BIT(11))
#define I2C_FIFO_ADDR_CFG_EN_M  (BIT(11))
#define I2C_FIFO_ADDR_CFG_EN_V  0x1
#define I2C_FIFO_ADDR_CFG_EN_S  11
/* I2C_nonifo_EN:R/W；位位置：[10]；默认值：1’b0；*/
/*description:将此位设置为enble apb nonifo访问。*/
#define I2C_NONFIFO_EN  (BIT(10))
#define I2C_NONFIFO_EN_M  (BIT(10))
#define I2C_NONFIFO_EN_V  0x1
#define I2C_NONFIFO_EN_S  10
/* I2C_TXFIFO_EMPTY_thrd:R/W；比特位置：[9:5]；默认值：5'h4；*/
/*description:使用apb-fifo访问时配置txfifo空threhd值*/
#define I2C_TXFIFO_EMPTY_THRHD  0x0000001F
#define I2C_TXFIFO_EMPTY_THRHD_M  ((I2C_TXFIFO_EMPTY_THRHD_V)<<(I2C_TXFIFO_EMPTY_THRHD_S))
#define I2C_TXFIFO_EMPTY_THRHD_V  0x1F
#define I2C_TXFIFO_EMPTY_THRHD_S  5
/* I2C_rxifo_FULL_THRHD:R/W；位位置：[4:0]；默认值：5’hb；*/
/*说明：*/
#define I2C_RXFIFO_FULL_THRHD  0x0000001F
#define I2C_RXFIFO_FULL_THRHD_M  ((I2C_RXFIFO_FULL_THRHD_V)<<(I2C_RXFIFO_FULL_THRHD_S))
#define I2C_RXFIFO_FULL_THRHD_V  0x1F
#define I2C_RXFIFO_FULL_THRHD_S  0

#define I2C_DATA_APB_REG(i)      (0x60013000 + (i) * 0x14000 + 0x001c)

#define I2C_DATA_REG(i)          (REG_I2C_BASE(i) + 0x001c)
/* I2C_FIFO_data:RO；位位置：[7:0]；默认值：8'b0；*/
/*description:寄存器表示使用apb-fifo访问时从rxfifo读取的字节数据*/
#define I2C_FIFO_RDATA  0x000000FF
#define I2C_FIFO_RDATA_M  ((I2C_FIFO_RDATA_V)<<(I2C_FIFO_RDATA_S))
#define I2C_FIFO_RDATA_V  0xFF
#define I2C_FIFO_RDATA_S  0

#define I2C_INT_RAW_REG(i)          (REG_I2C_BASE(i) + 0x0020)
/* I2C_TX_SEND_EMPTY_INT_RAW:RO；位位置：[12]；默认值：1’b0；*/
/*description:tx_send_empty_int中断的原始中断状态位。当I2C发送的数据多于非ifo_tx_thres时，它将产生tx_send_empty_int中断。。*/
#define I2C_TX_SEND_EMPTY_INT_RAW  (BIT(12))
#define I2C_TX_SEND_EMPTY_INT_RAW_M  (BIT(12))
#define I2C_TX_SEND_EMPTY_INT_RAW_V  0x1
#define I2C_TX_SEND_EMPTY_INT_RAW_S  12
/* I2C_RX_REC_FULL_INT_RAW:RO；位位置：[11]；默认值：1’b0；*/
/*description:rx_rec_full_int中断的原始中断状态位。当I2C接收的数据多于非ifo_rx_thres时，它将产生rx_rec_full_int中断。*/
#define I2C_RX_REC_FULL_INT_RAW  (BIT(11))
#define I2C_RX_REC_FULL_INT_RAW_M  (BIT(11))
#define I2C_RX_REC_FULL_INT_RAW_V  0x1
#define I2C_RX_REC_FULL_INT_RAW_S  11
/* I2C_ACK_ERR_INT_RAW:RO；位位置：[10]；默认值：1’b0；*/
/*description:ack_err_int中断的原始中断状态位。当I2C接收到错误的ACK位时，它将产生ACK_err_int中断。。*/
#define I2C_ACK_ERR_INT_RAW  (BIT(10))
#define I2C_ACK_ERR_INT_RAW_M  (BIT(10))
#define I2C_ACK_ERR_INT_RAW_V  0x1
#define I2C_ACK_ERR_INT_RAW_S  10
/* I2C_TRANS_START_INT_RAW:RO；位位置：[9]；默认值：1’b0；*/
/*description:trans_start_int中断的原始中断状态位。当I2C发送START位时，它将产生trans_START_int中断。*/
#define I2C_TRANS_START_INT_RAW  (BIT(9))
#define I2C_TRANS_START_INT_RAW_M  (BIT(9))
#define I2C_TRANS_START_INT_RAW_V  0x1
#define I2C_TRANS_START_INT_RAW_S  9
/* I2C_TIME_OUT_INT_RAW:RO；位位置：[8]；默认值：1’b0；*/
/*description:time_out_int中断的原始中断状态位。当I2C花费大量时间来接收数据时，它将产生time_out_int中断。*/
#define I2C_TIME_OUT_INT_RAW  (BIT(8))
#define I2C_TIME_OUT_INT_RAW_M  (BIT(8))
#define I2C_TIME_OUT_INT_RAW_V  0x1
#define I2C_TIME_OUT_INT_RAW_S  8
/* I2C_TRANS_COMPLETE_INT_RAW:RO；位位置：[7]；默认值：1’b0；*/
/*description:trans_complete_int中断的原始中断状态位。当I2C Master完成STOP命令时，它将产生trans_complete_int中断。*/
#define I2C_TRANS_COMPLETE_INT_RAW  (BIT(7))
#define I2C_TRANS_COMPLETE_INT_RAW_M  (BIT(7))
#define I2C_TRANS_COMPLETE_INT_RAW_V  0x1
#define I2C_TRANS_COMPLETE_INT_RAW_S  7
/* I2C_MASTER_TRAN_COMP_INT_RAW:RO；位位置：[6]；默认值：1’b0；*/
/*description:master_tra_comp_int中断的原始中断状态位。当I2C Master发送或接收字节时，它将产生Master_tran_comp_int中断。*/
#define I2C_MASTER_TRAN_COMP_INT_RAW  (BIT(6))
#define I2C_MASTER_TRAN_COMP_INT_RAW_M  (BIT(6))
#define I2C_MASTER_TRAN_COMP_INT_RAW_V  0x1
#define I2C_MASTER_TRAN_COMP_INT_RAW_S  6
/* I2C_arbitation_LOST_INT_RAW:RO；位位置：[5]；默认值：1’b0；*/
/*description:arbitation_lost_int中断的原始中断状态位。当I2C失去I2C总线的使用权时，它将产生仲裁_。*/
#define I2C_ARBITRATION_LOST_INT_RAW  (BIT(5))
#define I2C_ARBITRATION_LOST_INT_RAW_M  (BIT(5))
#define I2C_ARBITRATION_LOST_INT_RAW_V  0x1
#define I2C_ARBITRATION_LOST_INT_RAW_S  5
/* I2C_SLAVE_trans_COMP_INT_RAW:RO；位位置：[4]；默认值：1’b0；*/
/*description:slave_trans_comp_int中断的原始中断状态位。当I2C从设备检测到STOP位时，它将产生Slave_trans_comp_int中断。*/
#define I2C_SLAVE_TRAN_COMP_INT_RAW  (BIT(4))
#define I2C_SLAVE_TRAN_COMP_INT_RAW_M  (BIT(4))
#define I2C_SLAVE_TRAN_COMP_INT_RAW_V  0x1
#define I2C_SLAVE_TRAN_COMP_INT_RAW_S  4
/* I2C_END_DETECT_INT_RAW:RO；位位置：[3]；默认值：1’b0；*/
/*description:end_detect_int中断的原始中断状态位。当I2C处理END命令时，它将产生END_detect_int中断。*/
#define I2C_END_DETECT_INT_RAW  (BIT(3))
#define I2C_END_DETECT_INT_RAW_M  (BIT(3))
#define I2C_END_DETECT_INT_RAW_V  0x1
#define I2C_END_DETECT_INT_RAW_S  3
/* I2C_RXFIFO_OVF_INT_RAW:RO；位位置：[2]；默认值：1’b0；*/
/*描述：当使用apb-fifo访问时，用于接收数据溢出的原始中断状态位。*/
#define I2C_RXFIFO_OVF_INT_RAW  (BIT(2))
#define I2C_RXFIFO_OVF_INT_RAW_M  (BIT(2))
#define I2C_RXFIFO_OVF_INT_RAW_V  0x1
#define I2C_RXFIFO_OVF_INT_RAW_S  2
/* I2C_TXFIFO_EMPTY_INT_RAW:RO；位位置：[1]；默认值：1’b0；*/
/*description:当使用apb-fifo访问时，txfifo的原始中断状态位为空。*/
#define I2C_TXFIFO_EMPTY_INT_RAW  (BIT(1))
#define I2C_TXFIFO_EMPTY_INT_RAW_M  (BIT(1))
#define I2C_TXFIFO_EMPTY_INT_RAW_V  0x1
#define I2C_TXFIFO_EMPTY_INT_RAW_S  1
/* I2C_rxfix_FULL_INT_RAW:RO；位位置：[0]；默认值：1’b0；*/
/*description:使用apb-fifo访问时rxfifo full的原始中断状态位。*/
#define I2C_RXFIFO_FULL_INT_RAW  (BIT(0))
#define I2C_RXFIFO_FULL_INT_RAW_M  (BIT(0))
#define I2C_RXFIFO_FULL_INT_RAW_V  0x1
#define I2C_RXFIFO_FULL_INT_RAW_S  0

#define I2C_INT_CLR_REG(i)          (REG_I2C_BASE(i) + 0x0024)
/* I2C_TX_SEND_EMPTY_INT_CLR:WO；位位置：[12]；默认值：1’b0；*/
/*description:设置此位以清除tx_send_empty_int中断。*/
#define I2C_TX_SEND_EMPTY_INT_CLR  (BIT(12))
#define I2C_TX_SEND_EMPTY_INT_CLR_M  (BIT(12))
#define I2C_TX_SEND_EMPTY_INT_CLR_V  0x1
#define I2C_TX_SEND_EMPTY_INT_CLR_S  12
/* I2C_RX_REC_FULL_INT_CLR:WO；位位置：[11]；默认值：1’b0；*/
/*description:设置此位以清除rx_rec_full_int中断。*/
#define I2C_RX_REC_FULL_INT_CLR  (BIT(11))
#define I2C_RX_REC_FULL_INT_CLR_M  (BIT(11))
#define I2C_RX_REC_FULL_INT_CLR_V  0x1
#define I2C_RX_REC_FULL_INT_CLR_S  11
/* I2C_ACK_ERR_INT_CLR:WO；位位置：[10]；默认值：1’b0；*/
/*description:设置此位以清除ack_err_int中断。*/
#define I2C_ACK_ERR_INT_CLR  (BIT(10))
#define I2C_ACK_ERR_INT_CLR_M  (BIT(10))
#define I2C_ACK_ERR_INT_CLR_V  0x1
#define I2C_ACK_ERR_INT_CLR_S  10
/* I2C_TRANS_START_INT_CLR:WO；位位置：[9]；默认值：1’b0；*/
/*description:设置此位以清除trans_start_int中断。*/
#define I2C_TRANS_START_INT_CLR  (BIT(9))
#define I2C_TRANS_START_INT_CLR_M  (BIT(9))
#define I2C_TRANS_START_INT_CLR_V  0x1
#define I2C_TRANS_START_INT_CLR_S  9
/* I2C_TIME_OUT_INT_CLR:WO；位位置：[8]；默认值：1’b0；*/
/*description:设置此位以清除time_out_int中断。*/
#define I2C_TIME_OUT_INT_CLR  (BIT(8))
#define I2C_TIME_OUT_INT_CLR_M  (BIT(8))
#define I2C_TIME_OUT_INT_CLR_V  0x1
#define I2C_TIME_OUT_INT_CLR_S  8
/* I2C_TRANS_COMPLETE_INT_CLR:WO；位位置：[7]；默认值：1’b0；*/
/*description:设置此位以清除trans_complete_int中断。*/
#define I2C_TRANS_COMPLETE_INT_CLR  (BIT(7))
#define I2C_TRANS_COMPLETE_INT_CLR_M  (BIT(7))
#define I2C_TRANS_COMPLETE_INT_CLR_V  0x1
#define I2C_TRANS_COMPLETE_INT_CLR_S  7
/* I2C_MASTER_TRAN_COMP_INT_CLR:WO；位位置：[6]；默认值：1’b0；*/
/*description:设置此位以清除master_tran_comp中断。*/
#define I2C_MASTER_TRAN_COMP_INT_CLR  (BIT(6))
#define I2C_MASTER_TRAN_COMP_INT_CLR_M  (BIT(6))
#define I2C_MASTER_TRAN_COMP_INT_CLR_V  0x1
#define I2C_MASTER_TRAN_COMP_INT_CLR_S  6
/* I2C_arbitation_LOST_INT_CLR:WO；位位置：[5]；默认值：1’b0；*/
/*description:设置此位以清除仲裁_列表_中断。*/
#define I2C_ARBITRATION_LOST_INT_CLR  (BIT(5))
#define I2C_ARBITRATION_LOST_INT_CLR_M  (BIT(5))
#define I2C_ARBITRATION_LOST_INT_CLR_V  0x1
#define I2C_ARBITRATION_LOST_INT_CLR_S  5
/* I2C_SLAVE_trans_COMP_INT_CLR:WO；位位置：[4]；默认值：1’b0；*/
/*description:设置此位以清除slave_trans_comp_int中断。*/
#define I2C_SLAVE_TRAN_COMP_INT_CLR  (BIT(4))
#define I2C_SLAVE_TRAN_COMP_INT_CLR_M  (BIT(4))
#define I2C_SLAVE_TRAN_COMP_INT_CLR_V  0x1
#define I2C_SLAVE_TRAN_COMP_INT_CLR_S  4
/* I2C_END_DETECT_INT_CLR:WO；位位置：[3]；默认值：1’b0；*/
/*description:设置此位以清除end_detect_int中断。*/
#define I2C_END_DETECT_INT_CLR  (BIT(3))
#define I2C_END_DETECT_INT_CLR_M  (BIT(3))
#define I2C_END_DETECT_INT_CLR_V  0x1
#define I2C_END_DETECT_INT_CLR_S  3
/* I2C_RXFIFO_OVF_INT_CLR:WO；位位置：[2]；默认值：1’b0；*/
/*description:设置此位以清除rxfifo_ovf_int中断。*/
#define I2C_RXFIFO_OVF_INT_CLR  (BIT(2))
#define I2C_RXFIFO_OVF_INT_CLR_M  (BIT(2))
#define I2C_RXFIFO_OVF_INT_CLR_V  0x1
#define I2C_RXFIFO_OVF_INT_CLR_S  2
/* I2C_TXFIFO_EMPTY_INT_CLR:WO；位位置：[1]；默认值：1’b0；*/
/*description:设置此位以清除txfifo_empty_int中断。*/
#define I2C_TXFIFO_EMPTY_INT_CLR  (BIT(1))
#define I2C_TXFIFO_EMPTY_INT_CLR_M  (BIT(1))
#define I2C_TXFIFO_EMPTY_INT_CLR_V  0x1
#define I2C_TXFIFO_EMPTY_INT_CLR_S  1
/* I2C_rxfix_FULL_INT_CLR:WO；位位置：[0]；默认值：1’b0；*/
/*description：设置此位以清除rxifo_full_int中断。*/
#define I2C_RXFIFO_FULL_INT_CLR  (BIT(0))
#define I2C_RXFIFO_FULL_INT_CLR_M  (BIT(0))
#define I2C_RXFIFO_FULL_INT_CLR_V  0x1
#define I2C_RXFIFO_FULL_INT_CLR_S  0

#define I2C_INT_ENA_REG(i)          (REG_I2C_BASE(i) + 0x0028)
/* I2C_TX_SEND_EMPTY_INT_ENA:R/W；位位置：[12]；默认值：1’b0；*/
/*description:tx_send_empty_int中断的启用位。*/
#define I2C_TX_SEND_EMPTY_INT_ENA  (BIT(12))
#define I2C_TX_SEND_EMPTY_INT_ENA_M  (BIT(12))
#define I2C_TX_SEND_EMPTY_INT_ENA_V  0x1
#define I2C_TX_SEND_EMPTY_INT_ENA_S  12
/* I2C_RX_REC_FULL_INT_ENA:R/W；位位置：[11]；默认值：1’b0；*/
/*description:rx_rec_full_int中断的启用位。*/
#define I2C_RX_REC_FULL_INT_ENA  (BIT(11))
#define I2C_RX_REC_FULL_INT_ENA_M  (BIT(11))
#define I2C_RX_REC_FULL_INT_ENA_V  0x1
#define I2C_RX_REC_FULL_INT_ENA_S  11
/* I2C_ACK_ERR_INT_ENA:R/W；位位置：[10]；默认值：1’b0；*/
/*description:ack_err_int中断的启用位。*/
#define I2C_ACK_ERR_INT_ENA  (BIT(10))
#define I2C_ACK_ERR_INT_ENA_M  (BIT(10))
#define I2C_ACK_ERR_INT_ENA_V  0x1
#define I2C_ACK_ERR_INT_ENA_S  10
/* I2C_TRANS_START_INT_ENA:R/W；位位置：[9]；默认值：1’b0；*/
/*description:trans_start_int中断的启用位。*/
#define I2C_TRANS_START_INT_ENA  (BIT(9))
#define I2C_TRANS_START_INT_ENA_M  (BIT(9))
#define I2C_TRANS_START_INT_ENA_V  0x1
#define I2C_TRANS_START_INT_ENA_S  9
/* I2C_TIME_OUT_INT_ENA:R/W；位位置：[8]；默认值：1’b0；*/
/*description:time_out_int中断的启用位。*/
#define I2C_TIME_OUT_INT_ENA  (BIT(8))
#define I2C_TIME_OUT_INT_ENA_M  (BIT(8))
#define I2C_TIME_OUT_INT_ENA_V  0x1
#define I2C_TIME_OUT_INT_ENA_S  8
/* I2C_TRANS_COMPLETE_INT_ENA:R/W；位位置：[7]；默认值：1’b0；*/
/*description:trans_complete_int中断的启用位。*/
#define I2C_TRANS_COMPLETE_INT_ENA  (BIT(7))
#define I2C_TRANS_COMPLETE_INT_ENA_M  (BIT(7))
#define I2C_TRANS_COMPLETE_INT_ENA_V  0x1
#define I2C_TRANS_COMPLETE_INT_ENA_S  7
/* I2C_MASTER_TRAN_COMP_INT_ENA:R/W；位位置：[6]；默认值：1’b0；*/
/*description:master_tran_comp_int中断的启用位。*/
#define I2C_MASTER_TRAN_COMP_INT_ENA  (BIT(6))
#define I2C_MASTER_TRAN_COMP_INT_ENA_M  (BIT(6))
#define I2C_MASTER_TRAN_COMP_INT_ENA_V  0x1
#define I2C_MASTER_TRAN_COMP_INT_ENA_S  6
/* I2C_arbitation_LOST_INT_ENA:R/W；位位置：[5]；默认值：1’b0；*/
/*description:arbitation_lost_int中断的启用位。*/
#define I2C_ARBITRATION_LOST_INT_ENA  (BIT(5))
#define I2C_ARBITRATION_LOST_INT_ENA_M  (BIT(5))
#define I2C_ARBITRATION_LOST_INT_ENA_V  0x1
#define I2C_ARBITRATION_LOST_INT_ENA_S  5
/* I2C_SLAVE_trans_COMP_INT_ENA:R/W；位位置：[4]；默认值：1’b0；*/
/*description:slave_trans_comp_int中断的启用位。*/
#define I2C_SLAVE_TRAN_COMP_INT_ENA  (BIT(4))
#define I2C_SLAVE_TRAN_COMP_INT_ENA_M  (BIT(4))
#define I2C_SLAVE_TRAN_COMP_INT_ENA_V  0x1
#define I2C_SLAVE_TRAN_COMP_INT_ENA_S  4
/* I2C_END_DETECT_INT_ENA:R/W；位位置：[3]；默认值：1’b0；*/
/*description:end_detect_int中断的启用位。*/
#define I2C_END_DETECT_INT_ENA  (BIT(3))
#define I2C_END_DETECT_INT_ENA_M  (BIT(3))
#define I2C_END_DETECT_INT_ENA_V  0x1
#define I2C_END_DETECT_INT_ENA_S  3
/* I2C_RXFIFO_OVF_INT_ENA：R/W；位位置：[2]；默认值：1’b0；*/
/*description:rxfifo_ovf_int中断的启用位。*/
#define I2C_RXFIFO_OVF_INT_ENA  (BIT(2))
#define I2C_RXFIFO_OVF_INT_ENA_M  (BIT(2))
#define I2C_RXFIFO_OVF_INT_ENA_V  0x1
#define I2C_RXFIFO_OVF_INT_ENA_S  2
/* I2C_TXFIFO_EMPTY_INT_ENA:R/W；位位置：[1]；默认值：1’b0；*/
/*description:txfifo_empty_int中断的启用位。*/
#define I2C_TXFIFO_EMPTY_INT_ENA  (BIT(1))
#define I2C_TXFIFO_EMPTY_INT_ENA_M  (BIT(1))
#define I2C_TXFIFO_EMPTY_INT_ENA_V  0x1
#define I2C_TXFIFO_EMPTY_INT_ENA_S  1
/* I2C_rxifo_FULL_INT_ENA:R/W；位位置：[0]；默认值：1’b0；*/
/*description:rxfifo_full_int中断的启用位。*/
#define I2C_RXFIFO_FULL_INT_ENA  (BIT(0))
#define I2C_RXFIFO_FULL_INT_ENA_M  (BIT(0))
#define I2C_RXFIFO_FULL_INT_ENA_V  0x1
#define I2C_RXFIFO_FULL_INT_ENA_S  0

#define I2C_INT_STATUS_REG(i)          (REG_I2C_BASE(i) + 0x002c)
/* I2C_TX_SEND_EMPTY_INT_ST:RO；位位置：[12]；默认值：1’b0；*/
/*description:tx_send_empty_int中断的屏蔽中断状态。*/
#define I2C_TX_SEND_EMPTY_INT_ST  (BIT(12))
#define I2C_TX_SEND_EMPTY_INT_ST_M  (BIT(12))
#define I2C_TX_SEND_EMPTY_INT_ST_V  0x1
#define I2C_TX_SEND_EMPTY_INT_ST_S  12
/* I2C_RX_REC_FULL_INT_ST:RO；位位置：[11]；默认值：1’b0；*/
/*description:rx_rec_full_int中断的屏蔽中断状态。*/
#define I2C_RX_REC_FULL_INT_ST  (BIT(11))
#define I2C_RX_REC_FULL_INT_ST_M  (BIT(11))
#define I2C_RX_REC_FULL_INT_ST_V  0x1
#define I2C_RX_REC_FULL_INT_ST_S  11
/* I2C_ACK_ERR_INT_ST:RO；位位置：[10]；默认值：1’b0；*/
/*description:ack_err_int中断的屏蔽中断状态。*/
#define I2C_ACK_ERR_INT_ST  (BIT(10))
#define I2C_ACK_ERR_INT_ST_M  (BIT(10))
#define I2C_ACK_ERR_INT_ST_V  0x1
#define I2C_ACK_ERR_INT_ST_S  10
/* I2C_TRANS_START_INT_ST:RO；位位置：[9]；默认值：1’b0；*/
/*description:trans_start_int中断的屏蔽中断状态。*/
#define I2C_TRANS_START_INT_ST  (BIT(9))
#define I2C_TRANS_START_INT_ST_M  (BIT(9))
#define I2C_TRANS_START_INT_ST_V  0x1
#define I2C_TRANS_START_INT_ST_S  9
/* I2C_TIME_OUT_INT_ST:RO；位位置：[8]；默认值：1’b0；*/
/*description:time_out_int中断的屏蔽中断状态。*/
#define I2C_TIME_OUT_INT_ST  (BIT(8))
#define I2C_TIME_OUT_INT_ST_M  (BIT(8))
#define I2C_TIME_OUT_INT_ST_V  0x1
#define I2C_TIME_OUT_INT_ST_S  8
/* I2C_TRANS_COMPLETE_INT_ST:RO；位位置：[7]；默认值：1’b0；*/
/*description:trans_complete_int中断的屏蔽中断状态。*/
#define I2C_TRANS_COMPLETE_INT_ST  (BIT(7))
#define I2C_TRANS_COMPLETE_INT_ST_M  (BIT(7))
#define I2C_TRANS_COMPLETE_INT_ST_V  0x1
#define I2C_TRANS_COMPLETE_INT_ST_S  7
/* I2C_MASTER_TRAN_COMP_INT_ST:RO；位位置：[6]；默认值：1’b0；*/
/*description:master_tran_comp_int中断的屏蔽中断状态。*/
#define I2C_MASTER_TRAN_COMP_INT_ST  (BIT(6))
#define I2C_MASTER_TRAN_COMP_INT_ST_M  (BIT(6))
#define I2C_MASTER_TRAN_COMP_INT_ST_V  0x1
#define I2C_MASTER_TRAN_COMP_INT_ST_S  6
/* I2C_arbitation_LOST_INT_ST:RO；位位置：[5]；默认值：1’b0；*/
/*description:arbitation_lost_int中断的屏蔽中断状态。*/
#define I2C_ARBITRATION_LOST_INT_ST  (BIT(5))
#define I2C_ARBITRATION_LOST_INT_ST_M  (BIT(5))
#define I2C_ARBITRATION_LOST_INT_ST_V  0x1
#define I2C_ARBITRATION_LOST_INT_ST_S  5
/* I2C_SLAVE_trans_COMP_INT_ST:RO；位位置：[4]；默认值：1’b0；*/
/*description:slave_trans_comp_int中断的屏蔽中断状态。*/
#define I2C_SLAVE_TRAN_COMP_INT_ST  (BIT(4))
#define I2C_SLAVE_TRAN_COMP_INT_ST_M  (BIT(4))
#define I2C_SLAVE_TRAN_COMP_INT_ST_V  0x1
#define I2C_SLAVE_TRAN_COMP_INT_ST_S  4
/* I2C_END_DETECT_INT_ST:RO；位位置：[3]；默认值：1’b0；*/
/*description:end_detect_int中断的屏蔽中断状态。*/
#define I2C_END_DETECT_INT_ST  (BIT(3))
#define I2C_END_DETECT_INT_ST_M  (BIT(3))
#define I2C_END_DETECT_INT_ST_V  0x1
#define I2C_END_DETECT_INT_ST_S  3
/* I2C_RXFIFO_OVF_INT_ST:RO；位位置：[2]；默认值：1’b0；*/
/*description:rxfifo_ovf_int中断的屏蔽中断状态。*/
#define I2C_RXFIFO_OVF_INT_ST  (BIT(2))
#define I2C_RXFIFO_OVF_INT_ST_M  (BIT(2))
#define I2C_RXFIFO_OVF_INT_ST_V  0x1
#define I2C_RXFIFO_OVF_INT_ST_S  2
/* I2C_TXFIFO_EMPTY_INT_ST:RO；位位置：[1]；默认值：1’b0；*/
/*description:txfifo_empty_int中断的屏蔽中断状态。*/
#define I2C_TXFIFO_EMPTY_INT_ST  (BIT(1))
#define I2C_TXFIFO_EMPTY_INT_ST_M  (BIT(1))
#define I2C_TXFIFO_EMPTY_INT_ST_V  0x1
#define I2C_TXFIFO_EMPTY_INT_ST_S  1
/* I2C_rxfix_FULL_INT_ST:RO；位位置：[0]；默认值：1’b0；*/
/*description:rxfifo_full_int中断的屏蔽中断状态。*/
#define I2C_RXFIFO_FULL_INT_ST  (BIT(0))
#define I2C_RXFIFO_FULL_INT_ST_M  (BIT(0))
#define I2C_RXFIFO_FULL_INT_ST_V  0x1
#define I2C_RXFIFO_FULL_INT_ST_S  0

#define I2C_SDA_HOLD_REG(i)          (REG_I2C_BASE(i) + 0x0030)
/* I2C_SDA_HOLD_TIME:R/W；位位置：[9:0]；默认值：10'b0；*/
/*描述：此寄存器用于配置时钟num I2C，用于在SCL的负边缘之后保存数据。*/
#define I2C_SDA_HOLD_TIME  0x000003FF
#define I2C_SDA_HOLD_TIME_M  ((I2C_SDA_HOLD_TIME_V)<<(I2C_SDA_HOLD_TIME_S))
#define I2C_SDA_HOLD_TIME_V  0x3FF
#define I2C_SDA_HOLD_TIME_S  0

#define I2C_SDA_SAMPLE_REG(i)          (REG_I2C_BASE(i) + 0x0034)
/* I2C_SDA_SAMPLE_TIME:R/W；位位置：[9:0]；默认值：10'b0；*/
/*描述：此寄存器用于配置时钟num I2C，用于在SCL的偏倚之后对SDA上的数据进行采样*/
#define I2C_SDA_SAMPLE_TIME  0x000003FF
#define I2C_SDA_SAMPLE_TIME_M  ((I2C_SDA_SAMPLE_TIME_V)<<(I2C_SDA_SAMPLE_TIME_S))
#define I2C_SDA_SAMPLE_TIME_V  0x3FF
#define I2C_SDA_SAMPLE_TIME_S  0

#define I2C_SCL_HIGH_PERIOD_REG(i)          (REG_I2C_BASE(i) + 0x0038)
/* I2C_SCL_HIGH-PERIOD:R/W；比特位置：[13:0]；默认值：14'b0；*/
/*描述：此寄存器用于在SCL为低电平期间配置时钟num。*/
#define I2C_SCL_HIGH_PERIOD  0x00003FFF
#define I2C_SCL_HIGH_PERIOD_M  ((I2C_SCL_HIGH_PERIOD_V)<<(I2C_SCL_HIGH_PERIOD_S))
#define I2C_SCL_HIGH_PERIOD_V  0x3FFF
#define I2C_SCL_HIGH_PERIOD_S  0

#define I2C_SCL_START_HOLD_REG(i)          (REG_I2C_BASE(i) + 0x0040)
/* I2C_SCL_START_HOLD_TIME:R/W；位位置：[9:0]；默认值：10'b1000；*/
/*描述：此寄存器用于配置SDA的负边缘和SCL的负边缘之间的时钟编号，用于开始标记。*/
#define I2C_SCL_START_HOLD_TIME  0x000003FF
#define I2C_SCL_START_HOLD_TIME_M  ((I2C_SCL_START_HOLD_TIME_V)<<(I2C_SCL_START_HOLD_TIME_S))
#define I2C_SCL_START_HOLD_TIME_V  0x3FF
#define I2C_SCL_START_HOLD_TIME_S  0

#define I2C_SCL_RSTART_SETUP_REG(i)          (REG_I2C_BASE(i) + 0x0044)
/* I2C_SCL_RSTART_SETUP_TIME:R/W；位位置：[9:0]；默认值：10'b1000；*/
/*description:此寄存器用于配置SCL的偏旁和SDA的负边之间的时钟num，以用于重新启动标记。*/
#define I2C_SCL_RSTART_SETUP_TIME  0x000003FF
#define I2C_SCL_RSTART_SETUP_TIME_M  ((I2C_SCL_RSTART_SETUP_TIME_V)<<(I2C_SCL_RSTART_SETUP_TIME_S))
#define I2C_SCL_RSTART_SETUP_TIME_V  0x3FF
#define I2C_SCL_RSTART_SETUP_TIME_S  0

#define I2C_SCL_STOP_HOLD_REG(i)          (REG_I2C_BASE(i) + 0x0048)
/* I2C_SCL_STOP_HOLD_TIME:R/W；比特位置：[13:0]；默认值：14'b0；*/
/*description:此寄存器用于配置STOP位的posedge之后的时钟num。*/
#define I2C_SCL_STOP_HOLD_TIME  0x00003FFF
#define I2C_SCL_STOP_HOLD_TIME_M  ((I2C_SCL_STOP_HOLD_TIME_V)<<(I2C_SCL_STOP_HOLD_TIME_S))
#define I2C_SCL_STOP_HOLD_TIME_V  0x3FFF
#define I2C_SCL_STOP_HOLD_TIME_S  0

#define I2C_SCL_STOP_SETUP_REG(i)          (REG_I2C_BASE(i) + 0x004C)
/* I2C_SCL_STOP_SETUP_TIME:R/W；位位置：[9:0]；默认值：10'b0；*/
/*description:此寄存器用于配置SCL的偏旁和SDA的偏旁之间的时钟num。*/
#define I2C_SCL_STOP_SETUP_TIME  0x000003FF
#define I2C_SCL_STOP_SETUP_TIME_M  ((I2C_SCL_STOP_SETUP_TIME_V)<<(I2C_SCL_STOP_SETUP_TIME_S))
#define I2C_SCL_STOP_SETUP_TIME_V  0x3FF
#define I2C_SCL_STOP_SETUP_TIME_S  0

#define I2C_SCL_FILTER_CFG_REG(i)          (REG_I2C_BASE(i) + 0x0050)
/* I2C_SCL_FILTER_EN:R/W；位位置：[3]；默认值：1’b1；*/
/*description:这是SCL的筛选器启用位。*/
#define I2C_SCL_FILTER_EN  (BIT(3))
#define I2C_SCL_FILTER_EN_M  (BIT(3))
#define I2C_SCL_FILTER_EN_V  0x1
#define I2C_SCL_FILTER_EN_S  3
/* I2C_SCL_FILTER_threes:R/W；位位置：[2:0]；默认值：3'b0；*/
/*描述：当输入SCL的脉冲宽度小于此寄存器值时，I2C忽略此脉冲。*/
#define I2C_SCL_FILTER_THRES  0x00000007
#define I2C_SCL_FILTER_THRES_M  ((I2C_SCL_FILTER_THRES_V)<<(I2C_SCL_FILTER_THRES_S))
#define I2C_SCL_FILTER_THRES_V  0x7
#define I2C_SCL_FILTER_THRES_S  0

#define I2C_SDA_FILTER_CFG_REG(i)          (REG_I2C_BASE(i) + 0x0054)
/* I2C_SDA_FILTER_EN:R/W；位位置：[3]；默认值：1’b1；*/
/*description:这是SDA的过滤器启用位。*/
#define I2C_SDA_FILTER_EN  (BIT(3))
#define I2C_SDA_FILTER_EN_M  (BIT(3))
#define I2C_SDA_FILTER_EN_V  0x1
#define I2C_SDA_FILTER_EN_S  3
/* I2C_SDA_FILTER_threes:R/W；位位置：[2:0]；默认值：3'b0；*/
/*描述：当输入SCL的脉冲宽度小于此寄存器值时，I2C忽略此脉冲。*/
#define I2C_SDA_FILTER_THRES  0x00000007
#define I2C_SDA_FILTER_THRES_M  ((I2C_SDA_FILTER_THRES_V)<<(I2C_SDA_FILTER_THRES_S))
#define I2C_SDA_FILTER_THRES_V  0x7
#define I2C_SDA_FILTER_THRES_S  0

#define I2C_COMD0_REG(i)          (REG_I2C_BASE(i) + 0x0058)
/* I2C_COMMAND0_DONE:R/W；位位置：[31]；默认值：1’b0；*/
/*描述：当在I2C主模式下完成命令0时，此位变为高电平。*/
#define I2C_COMMAND0_DONE  (BIT(31))
#define I2C_COMMAND0_DONE_M  (BIT(31))
#define I2C_COMMAND0_DONE_V  0x1
#define I2C_COMMAND0_DONE_S  31
/* I2C_COMMAND0:R/W；比特位置：[13:0]；默认值：14'b0；*/
/*description:这是command0的内容。它由三部分组成。op_code是命令0:RSTART 1:WRITE 2:READ 3:STOP。4:END。Byte_num表示需要发送或接收的数据数量。ack_check_en ack_exp和ack值用于控制ack位。*/
#define I2C_COMMAND0  0x00003FFF
#define I2C_COMMAND0_M  ((I2C_COMMAND0_V)<<(I2C_COMMAND0_S))
#define I2C_COMMAND0_V  0x3FFF
#define I2C_COMMAND0_S  0

#define I2C_COMD1_REG(i)          (REG_I2C_BASE(i) + 0x005C)
/* I2C_COMMAND1_DONE:R/W；位位置：[31]；默认值：1’b0；*/
/*描述：当命令1在I2C主模式下完成时，该位变为高电平。*/
#define I2C_COMMAND1_DONE  (BIT(31))
#define I2C_COMMAND1_DONE_M  (BIT(31))
#define I2C_COMMAND1_DONE_V  0x1
#define I2C_COMMAND1_DONE_S  31
/* I2C_COMMAND1:R/W；比特位置：[13:0]；默认值：14'b0；*/
/*description:这是command1的内容。它由三部分组成。op_code是命令0:RSTART 1:WRITE 2:READ 3:STOP。4:END。Byte_num表示需要发送或接收的数据数量。ack_check_en ack_exp和ack值用于控制ack位。*/
#define I2C_COMMAND1  0x00003FFF
#define I2C_COMMAND1_M  ((I2C_COMMAND1_V)<<(I2C_COMMAND1_S))
#define I2C_COMMAND1_V  0x3FFF
#define I2C_COMMAND1_S  0

#define I2C_COMD2_REG(i)          (REG_I2C_BASE(i) + 0x0060)
/* I2C_COMMAND2_DONE:R/W；位位置：[31]；默认值：1’b0；*/
/*描述：当在I2C主模式下完成command2时，该位变为高电平。*/
#define I2C_COMMAND2_DONE  (BIT(31))
#define I2C_COMMAND2_DONE_M  (BIT(31))
#define I2C_COMMAND2_DONE_V  0x1
#define I2C_COMMAND2_DONE_S  31
/* I2C_COMMAND2:R/W；比特位置：[13:0]；默认值：14'b0；*/
/*description:这是command2的内容。它由三部分组成。op_code是命令0:RSTART 1:WRITE 2:READ 3:STOP。4:END。Byte_num表示需要发送或接收的数据数量。ack_check_en ack_exp和ack值用于控制ack位。*/
#define I2C_COMMAND2  0x00003FFF
#define I2C_COMMAND2_M  ((I2C_COMMAND2_V)<<(I2C_COMMAND2_S))
#define I2C_COMMAND2_V  0x3FFF
#define I2C_COMMAND2_S  0

#define I2C_COMD3_REG(i)          (REG_I2C_BASE(i) + 0x0064)
/* I2C_COMMAND3_DONE:R/W；位位置：[31]；默认值：1’b0；*/
/*描述：当在I2C主模式下完成命令3时，该位变为高电平。*/
#define I2C_COMMAND3_DONE  (BIT(31))
#define I2C_COMMAND3_DONE_M  (BIT(31))
#define I2C_COMMAND3_DONE_V  0x1
#define I2C_COMMAND3_DONE_S  31
/* I2C_COMMAND3:R/W；比特位置：[13:0]；默认值：14'b0；*/
/*description:这是command3的内容。它由三部分组成。op_code是命令0:RSTART 1:WRITE 2:READ 3:STOP。4:END。Byte_num表示需要发送或接收的数据数量。ack_check_en ack_exp和ack值用于控制ack位。*/
#define I2C_COMMAND3  0x00003FFF
#define I2C_COMMAND3_M  ((I2C_COMMAND3_V)<<(I2C_COMMAND3_S))
#define I2C_COMMAND3_V  0x3FFF
#define I2C_COMMAND3_S  0

#define I2C_COMD4_REG(i)          (REG_I2C_BASE(i) + 0x0068)
/* I2C_COMMAND4_DONE:R/W；位位置：[31]；默认值：1’b0；*/
/*描述：当在I2C主模式下完成command4时，该位变为高电平。*/
#define I2C_COMMAND4_DONE  (BIT(31))
#define I2C_COMMAND4_DONE_M  (BIT(31))
#define I2C_COMMAND4_DONE_V  0x1
#define I2C_COMMAND4_DONE_S  31
/* I2C_COMMAND4:R/W；比特位置：[13:0]；默认值：14'b0；*/
/*description:这是command4的内容。它由三部分组成。op_code是命令0:RSTART 1:WRITE 2:READ 3:STOP。4:END。Byte_num表示需要发送或接收的数据数量。ack_check_en ack_exp和ack值用于控制ack位。*/
#define I2C_COMMAND4  0x00003FFF
#define I2C_COMMAND4_M  ((I2C_COMMAND4_V)<<(I2C_COMMAND4_S))
#define I2C_COMMAND4_V  0x3FFF
#define I2C_COMMAND4_S  0

#define I2C_COMD5_REG(i)          (REG_I2C_BASE(i) + 0x006C)
/* I2C_COMMAND5_DONE:R/W；位位置：[31]；默认值：1’b0；*/
/*描述：当在I2C主模式下完成command5时，该位变为高电平。*/
#define I2C_COMMAND5_DONE  (BIT(31))
#define I2C_COMMAND5_DONE_M  (BIT(31))
#define I2C_COMMAND5_DONE_V  0x1
#define I2C_COMMAND5_DONE_S  31
/* I2C_COMMAND5:R/W；比特位置：[13:0]；默认值：14'b0；*/
/*description:这是command5的内容。它由三部分组成。op_code是命令0:RSTART 1:WRITE 2:READ 3:STOP。4:END。Byte_num表示需要发送或接收的数据数量。ack_check_en ack_exp和ack值用于控制ack位。*/
#define I2C_COMMAND5  0x00003FFF
#define I2C_COMMAND5_M  ((I2C_COMMAND5_V)<<(I2C_COMMAND5_S))
#define I2C_COMMAND5_V  0x3FFF
#define I2C_COMMAND5_S  0

#define I2C_COMD6_REG(i)          (REG_I2C_BASE(i) + 0x0070)
/* I2C_COMMAND6_DONE:R/W；位位置：[31]；默认值：1’b0；*/
/*描述：当命令6在I2C主模式下完成时，该位变为高电平。*/
#define I2C_COMMAND6_DONE  (BIT(31))
#define I2C_COMMAND6_DONE_M  (BIT(31))
#define I2C_COMMAND6_DONE_V  0x1
#define I2C_COMMAND6_DONE_S  31
/* I2C_COMMAND6:R/W；比特位置：[13:0]；默认值：14'b0；*/
/*description:这是command6的内容。它由三部分组成。op_code是命令0:RSTART 1:WRITE 2:READ 3:STOP。4:END。Byte_num表示需要发送或接收的数据数量。ack_check_en ack_exp和ack值用于控制ack位。*/
#define I2C_COMMAND6  0x00003FFF
#define I2C_COMMAND6_M  ((I2C_COMMAND6_V)<<(I2C_COMMAND6_S))
#define I2C_COMMAND6_V  0x3FFF
#define I2C_COMMAND6_S  0

#define I2C_COMD7_REG(i)          (REG_I2C_BASE(i) + 0x0074)
/* I2C_COMMAND7_DONE:R/W；位位置：[31]；默认值：1’b0；*/
/*描述：当在I2C主模式下完成命令7时，该位变为高电平。*/
#define I2C_COMMAND7_DONE  (BIT(31))
#define I2C_COMMAND7_DONE_M  (BIT(31))
#define I2C_COMMAND7_DONE_V  0x1
#define I2C_COMMAND7_DONE_S  31
/* I2C_COMMAND7:R/W；比特位置：[13:0]；默认值：14'b0；*/
/*description:这是command7的内容。它由三部分组成。op_code是命令0:RSTART 1:WRITE 2:READ 3:STOP。4:END。Byte_num表示需要发送或接收的数据数量。ack_check_en ack_exp和ack值用于控制ack位。*/
#define I2C_COMMAND7  0x00003FFF
#define I2C_COMMAND7_M  ((I2C_COMMAND7_V)<<(I2C_COMMAND7_S))
#define I2C_COMMAND7_V  0x3FFF
#define I2C_COMMAND7_S  0

#define I2C_COMD8_REG(i)          (REG_I2C_BASE(i) + 0x0078)
/* I2C_COMMAND8_DONE:R/W；位位置：[31]；默认值：1’b0；*/
/*描述：当命令8在I2C主模式下完成时，该位变为高电平。*/
#define I2C_COMMAND8_DONE  (BIT(31))
#define I2C_COMMAND8_DONE_M  (BIT(31))
#define I2C_COMMAND8_DONE_V  0x1
#define I2C_COMMAND8_DONE_S  31
/* I2C_COMMAND8:R/W；比特位置：[13:0]；默认值：14'b0；*/
/*description:这是command8的内容。它由三部分组成。op_code是命令0:RSTART 1:WRITE 2:READ 3:STOP。4:END。Byte_num表示需要发送或接收的数据数量。ack_check_en ack_exp和ack值用于控制ack位。*/
#define I2C_COMMAND8  0x00003FFF
#define I2C_COMMAND8_M  ((I2C_COMMAND8_V)<<(I2C_COMMAND8_S))
#define I2C_COMMAND8_V  0x3FFF
#define I2C_COMMAND8_S  0

#define I2C_COMD9_REG(i)          (REG_I2C_BASE(i) + 0x007C)
/* I2C_COMMAND9_DONE:R/W；位位置：[31]；默认值：1’b0；*/
/*描述：当在I2C主模式下完成命令9时，该位变为高电平。*/
#define I2C_COMMAND9_DONE  (BIT(31))
#define I2C_COMMAND9_DONE_M  (BIT(31))
#define I2C_COMMAND9_DONE_V  0x1
#define I2C_COMMAND9_DONE_S  31
/* I2C_COMMAND9:R/W；比特位置：[13:0]；默认值：14'b0；*/
/*description:这是command9的内容。它由三部分组成。op_code是命令0:RSTART 1:WRITE 2:READ 3:STOP。4:END。Byte_num表示需要发送或接收的数据数量。ack_check_en ack_exp和ack值用于控制ack位。*/
#define I2C_COMMAND9  0x00003FFF
#define I2C_COMMAND9_M  ((I2C_COMMAND9_V)<<(I2C_COMMAND9_S))
#define I2C_COMMAND9_V  0x3FFF
#define I2C_COMMAND9_S  0

#define I2C_COMD10_REG(i)          (REG_I2C_BASE(i) + 0x0080)
/* I2C_COMMAND10_DONE:R/W；位位置：[31]；默认值：1’b0；*/
/*描述：当命令10在I2C主模式下完成时，该位变为高电平。*/
#define I2C_COMMAND10_DONE  (BIT(31))
#define I2C_COMMAND10_DONE_M  (BIT(31))
#define I2C_COMMAND10_DONE_V  0x1
#define I2C_COMMAND10_DONE_S  31
/* I2C_COMMAND10:R/W；比特位置：[13:0]；默认值：14'b0；*/
/*description:这是command10的内容。它由三部分组成。op_code是命令0:RSTART 1:WRITE 2:READ 3:STOP。4:END。Byte_num表示需要发送或接收的数据数量。ack_check_en ack_exp和ack值用于控制ack位。*/
#define I2C_COMMAND10  0x00003FFF
#define I2C_COMMAND10_M  ((I2C_COMMAND10_V)<<(I2C_COMMAND10_S))
#define I2C_COMMAND10_V  0x3FFF
#define I2C_COMMAND10_S  0

#define I2C_COMD11_REG(i)          (REG_I2C_BASE(i) + 0x0084)
/* I2C_COMMAND11_DONE:R/W；位位置：[31]；默认值：1’b0；*/
/*描述：当命令11在I2C主模式下完成时，该位变为高电平。*/
#define I2C_COMMAND11_DONE  (BIT(31))
#define I2C_COMMAND11_DONE_M  (BIT(31))
#define I2C_COMMAND11_DONE_V  0x1
#define I2C_COMMAND11_DONE_S  31
/* I2C_COMMAND11:R/W；比特位置：[13:0]；默认值：14'b0；*/
/*description:这是command11的内容。它由三部分组成。op_code是命令0:RSTART 1:WRITE 2:READ 3:STOP。4:END。Byte_num表示需要发送或接收的数据数量。ack_check_en ack_exp和ack值用于控制ack位。*/
#define I2C_COMMAND11  0x00003FFF
#define I2C_COMMAND11_M  ((I2C_COMMAND11_V)<<(I2C_COMMAND11_S))
#define I2C_COMMAND11_V  0x3FFF
#define I2C_COMMAND11_S  0

#define I2C_COMD12_REG(i)          (REG_I2C_BASE(i) + 0x0088)
/* I2C_COMMAND12_DONE:R/W；位位置：[31]；默认值：1’b0；*/
/*描述：当在I2C主模式下执行命令12时，该位变为高电平。*/
#define I2C_COMMAND12_DONE  (BIT(31))
#define I2C_COMMAND12_DONE_M  (BIT(31))
#define I2C_COMMAND12_DONE_V  0x1
#define I2C_COMMAND12_DONE_S  31
/* I2C_COMMAND12:R/W；比特位置：[13:0]；默认值：14'b0；*/
/*description:这是command12的内容。它由三部分组成。op_code是命令0:RSTART 1:WRITE 2:READ 3:STOP。4:END。Byte_num表示需要发送或接收的数据数量。ack_check_en ack_exp和ack值用于控制ack位。*/
#define I2C_COMMAND12  0x00003FFF
#define I2C_COMMAND12_M  ((I2C_COMMAND12_V)<<(I2C_COMMAND12_S))
#define I2C_COMMAND12_V  0x3FFF
#define I2C_COMMAND12_S  0

#define I2C_COMD13_REG(i)          (REG_I2C_BASE(i) + 0x008C)
/* I2C_COMMAND13_DONE:R/W；位位置：[31]；默认值：1’b0；*/
/*描述：当在I2C主模式下执行命令13时，该位变为高电平。*/
#define I2C_COMMAND13_DONE  (BIT(31))
#define I2C_COMMAND13_DONE_M  (BIT(31))
#define I2C_COMMAND13_DONE_V  0x1
#define I2C_COMMAND13_DONE_S  31
/* I2C_COMMAND13:R/W；比特位置：[13:0]；默认值：14'b0；*/
/*description:这是command13的内容。它由三部分组成。op_code是命令0:RSTART 1:WRITE 2:READ 3:STOP。4:END。Byte_num表示需要发送或接收的数据数量。ack_check_en ack_exp和ack值用于控制ack位。*/
#define I2C_COMMAND13  0x00003FFF
#define I2C_COMMAND13_M  ((I2C_COMMAND13_V)<<(I2C_COMMAND13_S))
#define I2C_COMMAND13_V  0x3FFF
#define I2C_COMMAND13_S  0

#define I2C_COMD14_REG(i)          (REG_I2C_BASE(i) + 0x0090)
/* I2C_COMMAND14_DONE:R/W；位位置：[31]；默认值：1’b0；*/
/*描述：当在I2C主模式下执行命令14时，该位变为高电平。*/
#define I2C_COMMAND14_DONE  (BIT(31))
#define I2C_COMMAND14_DONE_M  (BIT(31))
#define I2C_COMMAND14_DONE_V  0x1
#define I2C_COMMAND14_DONE_S  31
/* I2C_COMMAND14:R/W；比特位置：[13:0]；默认值：14'b0；*/
/*description:这是command14的内容。它由三部分组成。op_code是命令0:RSTART 1:WRITE 2:READ 3:STOP。4:END。Byte_num表示需要发送或接收的数据数量。ack_check_en ack_exp和ack值用于控制ack位。*/
#define I2C_COMMAND14  0x00003FFF
#define I2C_COMMAND14_M  ((I2C_COMMAND14_V)<<(I2C_COMMAND14_S))
#define I2C_COMMAND14_V  0x3FFF
#define I2C_COMMAND14_S  0

#define I2C_COMD15_REG(i)          (REG_I2C_BASE(i) + 0x0094)
/* I2C_COMMAND15_DONE:R/W；位位置：[31]；默认值：1’b0；*/
/*描述：当在I2C主模式下执行命令15时，该位变为高电平。*/
#define I2C_COMMAND15_DONE  (BIT(31))
#define I2C_COMMAND15_DONE_M  (BIT(31))
#define I2C_COMMAND15_DONE_V  0x1
#define I2C_COMMAND15_DONE_S  31
/* I2C_COMMAND15:R/W；比特位置：[13:0]；默认值：14'b0；*/
/*description:这是command15的内容。它由三部分组成。op_code是命令0:RSTART 1:WRITE 2:READ 3:STOP。4:END。Byte_num表示需要发送或接收的数据数量。ack_check_en ack_exp和ack值用于控制ack位。*/
#define I2C_COMMAND15  0x00003FFF
#define I2C_COMMAND15_M  ((I2C_COMMAND15_V)<<(I2C_COMMAND15_S))
#define I2C_COMMAND15_V  0x3FFF
#define I2C_COMMAND15_S  0

#define I2C_DATE_REG(i)          (REG_I2C_BASE(i) + 0x00F8)
/* I2C_DATE:R/W；位位置：[31:0]；默认值：32'h16042000；*/
/*说明：*/
#define I2C_DATE  0xFFFFFFFF
#define I2C_DATE_M  ((I2C_DATE_V)<<(I2C_DATE_S))
#define I2C_DATE_V  0xFFFFFFFF
#define I2C_DATE_S  0

#define I2C_FIFO_START_ADDR_REG(i)          (REG_I2C_BASE(i) + 0x0100)




#endif /*_SOC_I2C_REG_H_ */

