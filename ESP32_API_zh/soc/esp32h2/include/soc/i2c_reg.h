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
#ifndef _SOC_I2C_REG_H_
#define _SOC_I2C_REG_H_


#ifdef __cplusplus
extern "C" {
#endif
#include "soc.h"

#define I2C_SCL_LOW_PERIOD_REG(i)          (REG_I2C_BASE(i) + 0x0)
/* I2C_SCL_LOW_PERIOD:R/W；位位置：[8:0]；默认值：9'b0；*/
/*描述：。*/
#define I2C_SCL_LOW_PERIOD    0x000001FF
#define I2C_SCL_LOW_PERIOD_M  ((I2C_SCL_LOW_PERIOD_V)<<(I2C_SCL_LOW_PERIOD_S))
#define I2C_SCL_LOW_PERIOD_V  0x1FF
#define I2C_SCL_LOW_PERIOD_S  0

#define I2C_CTR_REG(i)          (REG_I2C_BASE(i) + 0x4)
/* I2C_ADDR_BROADCASTING_EN:R/W；位位置：[14]；默认值：1’b0；*/
/*描述：。*/
#define I2C_ADDR_BROADCASTING_EN    (BIT(14))
#define I2C_ADDR_BROADCASTING_EN_M  (BIT(14))
#define I2C_ADDR_BROADCASTING_EN_V  0x1
#define I2C_ADDR_BROADCASTING_EN_S  14
/* I2C_ADDR_10BIT_RW_CHECK_EN:R/W；位位置：[13]；默认值：1’b0；*/
/*描述：。*/
#define I2C_ADDR_10BIT_RW_CHECK_EN    (BIT(13))
#define I2C_ADDR_10BIT_RW_CHECK_EN_M  (BIT(13))
#define I2C_ADDR_10BIT_RW_CHECK_EN_V  0x1
#define I2C_ADDR_10BIT_RW_CHECK_EN_S  13
/* I2C_SLV_TX_AUTO_START_EN:R/W；位位置：[12]；默认值：1’b0；*/
/*描述：。*/
#define I2C_SLV_TX_AUTO_START_EN    (BIT(12))
#define I2C_SLV_TX_AUTO_START_EN_M  (BIT(12))
#define I2C_SLV_TX_AUTO_START_EN_V  0x1
#define I2C_SLV_TX_AUTO_START_EN_S  12
/* I2C_CONF_UPGATE:WT；位位置：[11]；默认值：1’b0；*/
/*描述：。*/
#define I2C_CONF_UPGATE    (BIT(11))
#define I2C_CONF_UPGATE_M  (BIT(11))
#define I2C_CONF_UPGATE_V  0x1
#define I2C_CONF_UPGATE_S  11
/* I2C_FSM_RST:WT；位位置：[10]；默认值：1’b0；*/
/*描述：。*/
#define I2C_FSM_RST    (BIT(10))
#define I2C_FSM_RST_M  (BIT(10))
#define I2C_FSM_RST_V  0x1
#define I2C_FSM_RST_S  10
/* I2C_ARBITRATION_EN:R/W；位位置：[9]；默认值：1’b1；*/
/*描述：。*/
#define I2C_ARBITRATION_EN    (BIT(9))
#define I2C_ARBITRATION_EN_M  (BIT(9))
#define I2C_ARBITRATION_EN_V  0x1
#define I2C_ARBITRATION_EN_S  9
/* I2C_CLK_EN:R/W；位位置：[8]；默认值：1’b0；*/
/*描述：。*/
#define I2C_CLK_EN    (BIT(8))
#define I2C_CLK_EN_M  (BIT(8))
#define I2C_CLK_EN_V  0x1
#define I2C_CLK_EN_S  8
/* I2C_RX_LSB_FIRST:R/W；位位置：[7]；默认值：1'0；*/
/*描述：。*/
#define I2C_RX_LSB_FIRST    (BIT(7))
#define I2C_RX_LSB_FIRST_M  (BIT(7))
#define I2C_RX_LSB_FIRST_V  0x1
#define I2C_RX_LSB_FIRST_S  7
/* I2C_TX_LSB_FIRST:R/W；位位置：[6]；默认值：1’b0；*/
/*描述：。*/
#define I2C_TX_LSB_FIRST    (BIT(6))
#define I2C_TX_LSB_FIRST_M  (BIT(6))
#define I2C_TX_LSB_FIRST_V  0x1
#define I2C_TX_LSB_FIRST_S  6
/* I2C_TRANS_START:WT；位位置：[5]；默认值：1’b0；*/
/*描述：。*/
#define I2C_TRANS_START    (BIT(5))
#define I2C_TRANS_START_M  (BIT(5))
#define I2C_TRANS_START_V  0x1
#define I2C_TRANS_START_S  5
/* I2C_MS_MODE：R/W；位位置：[4]；默认值：1’b0；*/
/*描述：。*/
#define I2C_MS_MODE    (BIT(4))
#define I2C_MS_MODE_M  (BIT(4))
#define I2C_MS_MODE_V  0x1
#define I2C_MS_MODE_S  4
/* I2C_RX_FULL_ACK_LEVEL:R/W；位位置：[3]；默认值：1’b1；*/
/*描述：。*/
#define I2C_RX_FULL_ACK_LEVEL    (BIT(3))
#define I2C_RX_FULL_ACK_LEVEL_M  (BIT(3))
#define I2C_RX_FULL_ACK_LEVEL_V  0x1
#define I2C_RX_FULL_ACK_LEVEL_S  3
/* I2C_SAMPLE_SCL_LEVEL:R/W；位位置：[2]；默认值：1’b0；*/
/*描述：。*/
#define I2C_SAMPLE_SCL_LEVEL    (BIT(2))
#define I2C_SAMPLE_SCL_LEVEL_M  (BIT(2))
#define I2C_SAMPLE_SCL_LEVEL_V  0x1
#define I2C_SAMPLE_SCL_LEVEL_S  2
/* I2C_SCL_FORCE_OUT:R/W；位位置：[1]；默认值：1’b1；*/
/*描述：。*/
#define I2C_SCL_FORCE_OUT    (BIT(1))
#define I2C_SCL_FORCE_OUT_M  (BIT(1))
#define I2C_SCL_FORCE_OUT_V  0x1
#define I2C_SCL_FORCE_OUT_S  1
/* I2C_SDA_frce_OUT:R/W；位位置：[0]；默认值：1’b1；*/
/*描述：。*/
#define I2C_SDA_FORCE_OUT    (BIT(0))
#define I2C_SDA_FORCE_OUT_M  (BIT(0))
#define I2C_SDA_FORCE_OUT_V  0x1
#define I2C_SDA_FORCE_OUT_S  0

#define I2C_SR_REG(i)          (REG_I2C_BASE(i) + 0x8)
/* I2C_SCL_STATE_LAST:RO；位位置：[30:28]；默认值：3'b0；*/
/*描述：。*/
#define I2C_SCL_STATE_LAST    0x00000007
#define I2C_SCL_STATE_LAST_M  ((I2C_SCL_STATE_LAST_V)<<(I2C_SCL_STATE_LAST_S))
#define I2C_SCL_STATE_LAST_V  0x7
#define I2C_SCL_STATE_LAST_S  28
/* I2C_SCL_MAIN_STATE_LAST:RO；比特位置：[26:24]；默认值：3'b0；*/
/*描述：。*/
#define I2C_SCL_MAIN_STATE_LAST    0x00000007
#define I2C_SCL_MAIN_STATE_LAST_M  ((I2C_SCL_MAIN_STATE_LAST_V)<<(I2C_SCL_MAIN_STATE_LAST_S))
#define I2C_SCL_MAIN_STATE_LAST_V  0x7
#define I2C_SCL_MAIN_STATE_LAST_S  24
/* I2C_TXFIFO_CNT:RO；比特位置：[23:18]；默认值：6'b0；*/
/*描述：。*/
#define I2C_TXFIFO_CNT    0x0000003F
#define I2C_TXFIFO_CNT_M  ((I2C_TXFIFO_CNT_V)<<(I2C_TXFIFO_CNT_S))
#define I2C_TXFIFO_CNT_V  0x3F
#define I2C_TXFIFO_CNT_S  18
/* I2C_STRETCH_CAUSE:RO；比特位置：[15:14]；默认值：2'h3；*/
/*描述：。*/
#define I2C_STRETCH_CAUSE    0x00000003
#define I2C_STRETCH_CAUSE_M  ((I2C_STRETCH_CAUSE_V)<<(I2C_STRETCH_CAUSE_S))
#define I2C_STRETCH_CAUSE_V  0x3
#define I2C_STRETCH_CAUSE_S  14
/* I2C_rxifo_CNT:RO；比特位置：[13:8]；默认值：6'b0；*/
/*描述：。*/
#define I2C_RXFIFO_CNT    0x0000003F
#define I2C_RXFIFO_CNT_M  ((I2C_RXFIFO_CNT_V)<<(I2C_RXFIFO_CNT_S))
#define I2C_RXFIFO_CNT_V  0x3F
#define I2C_RXFIFO_CNT_S  8
/* I2C_SLAVE_ADDRESSED:RO；位位置：[5]；默认值：1’b0；*/
/*描述：。*/
#define I2C_SLAVE_ADDRESSED    (BIT(5))
#define I2C_SLAVE_ADDRESSED_M  (BIT(5))
#define I2C_SLAVE_ADDRESSED_V  0x1
#define I2C_SLAVE_ADDRESSED_S  5
/* I2C_BUS_BUSY:RO；位位置：[4]；默认值：1’b0；*/
/*描述：。*/
#define I2C_BUS_BUSY    (BIT(4))
#define I2C_BUS_BUSY_M  (BIT(4))
#define I2C_BUS_BUSY_V  0x1
#define I2C_BUS_BUSY_S  4
/* I2C_ARB_list:RO；位位置：[3]；默认值：1’b0；*/
/*描述：。*/
#define I2C_ARB_LOST    (BIT(3))
#define I2C_ARB_LOST_M  (BIT(3))
#define I2C_ARB_LOST_V  0x1
#define I2C_ARB_LOST_S  3
/* I2C_SLAVE_RW:RO；位位置：[1]；默认值：1’b0；*/
/*描述：。*/
#define I2C_SLAVE_RW    (BIT(1))
#define I2C_SLAVE_RW_M  (BIT(1))
#define I2C_SLAVE_RW_V  0x1
#define I2C_SLAVE_RW_S  1
/* I2C_RESP_REC:RO；位位置：[0]；默认值：1’b0；*/
/*描述：。*/
#define I2C_RESP_REC    (BIT(0))
#define I2C_RESP_REC_M  (BIT(0))
#define I2C_RESP_REC_V  0x1
#define I2C_RESP_REC_S  0

#define I2C_TO_REG(i)          (REG_I2C_BASE(i) + 0xC)
/* I2C_TIME_OUT_EN:R/W；位位置：[5]；默认值：1’b0；*/
/*描述：。*/
#define I2C_TIME_OUT_EN    (BIT(5))
#define I2C_TIME_OUT_EN_M  (BIT(5))
#define I2C_TIME_OUT_EN_V  0x1
#define I2C_TIME_OUT_EN_S  5
/* I2C_TIME_OUT_REG:R/W；位位置：[4:0]；默认值：5’h10；*/
/*描述：。*/
#define I2C_TIME_OUT_REG    0x0000001F
#define I2C_TIME_OUT_REG_M  ((I2C_TIME_OUT_VALUE_V)<<(I2C_TIME_OUT_VALUE_S))
#define I2C_TIME_OUT_REG_V  0x1F
#define I2C_TIME_OUT_REG_S  0

#define I2C_SLAVE_ADDR_REG(i)          (REG_I2C_BASE(i) + 0x10)
/* I2C_ADDR_10BIT_EN:R/W；位位置：[31]；默认值：1’b0；*/
/*描述：。*/
#define I2C_ADDR_10BIT_EN    (BIT(31))
#define I2C_ADDR_10BIT_EN_M  (BIT(31))
#define I2C_ADDR_10BIT_EN_V  0x1
#define I2C_ADDR_10BIT_EN_S  31
/* I2C_SLAVE_ADDR:R/W；位位置：[14:0]；默认值：15'b0；*/
/*描述：。*/
#define I2C_SLAVE_ADDR    0x00007FFF
#define I2C_SLAVE_ADDR_M  ((I2C_SLAVE_ADDR_V)<<(I2C_SLAVE_ADDR_S))
#define I2C_SLAVE_ADDR_V  0x7FFF
#define I2C_SLAVE_ADDR_S  0

#define I2C_FIFO_ST_REG(i)          (REG_I2C_BASE(i) + 0x14)
/* I2C_SLAVE_RW_POINT:RO；位位置：[29:22]；默认值：8'b0；*/
/*描述：。*/
#define I2C_SLAVE_RW_POINT    0x000000FF
#define I2C_SLAVE_RW_POINT_M  ((I2C_SLAVE_RW_POINT_V)<<(I2C_SLAVE_RW_POINT_S))
#define I2C_SLAVE_RW_POINT_V  0xFF
#define I2C_SLAVE_RW_POINT_S  22
/* I2C_TXFIFO_addr:RO；比特位置：[19:15]；默认值：5’b0；*/
/*描述：。*/
#define I2C_TXFIFO_WADDR    0x0000001F
#define I2C_TXFIFO_WADDR_M  ((I2C_TXFIFO_WADDR_V)<<(I2C_TXFIFO_WADDR_S))
#define I2C_TXFIFO_WADDR_V  0x1F
#define I2C_TXFIFO_WADDR_S  15
/* I2C_TXFIFO雷达：RO；比特位置：[14:10]；默认值：5’b0；*/
/*描述：。*/
#define I2C_TXFIFO_RADDR    0x0000001F
#define I2C_TXFIFO_RADDR_M  ((I2C_TXFIFO_RADDR_V)<<(I2C_TXFIFO_RADDR_S))
#define I2C_TXFIFO_RADDR_V  0x1F
#define I2C_TXFIFO_RADDR_S  10
/* I2C_RXFIFO地址：RO；比特位置：[9:5]；默认值：5’b0；*/
/*描述：。*/
#define I2C_RXFIFO_WADDR    0x0000001F
#define I2C_RXFIFO_WADDR_M  ((I2C_RXFIFO_WADDR_V)<<(I2C_RXFIFO_WADDR_S))
#define I2C_RXFIFO_WADDR_V  0x1F
#define I2C_RXFIFO_WADDR_S  5
/* I2C_rxifo_addr:RO；位位置：[4:0]；默认值：5’b0；*/
/*描述：。*/
#define I2C_RXFIFO_RADDR    0x0000001F
#define I2C_RXFIFO_RADDR_M  ((I2C_RXFIFO_RADDR_V)<<(I2C_RXFIFO_RADDR_S))
#define I2C_RXFIFO_RADDR_V  0x1F
#define I2C_RXFIFO_RADDR_S  0

#define I2C_FIFO_CONF_REG(i)          (REG_I2C_BASE(i) + 0x18)
/* I2C_FIFO_PRT_EN:R/W；位位置：[14]；默认值：1’b1；*/
/*描述：。*/
#define I2C_FIFO_PRT_EN    (BIT(14))
#define I2C_FIFO_PRT_EN_M  (BIT(14))
#define I2C_FIFO_PRT_EN_V  0x1
#define I2C_FIFO_PRT_EN_S  14
/* I2C_TX_FIFO_RST:R/W；位位置：[13]；默认值：1’b0；*/
/*描述：。*/
#define I2C_TX_FIFO_RST    (BIT(13))
#define I2C_TX_FIFO_RST_M  (BIT(13))
#define I2C_TX_FIFO_RST_V  0x1
#define I2C_TX_FIFO_RST_S  13
/* I2C_RX_FIFO_RST:R/W；位位置：[12]；默认值：1’b0；*/
/*描述：。*/
#define I2C_RX_FIFO_RST    (BIT(12))
#define I2C_RX_FIFO_RST_M  (BIT(12))
#define I2C_RX_FIFO_RST_V  0x1
#define I2C_RX_FIFO_RST_S  12
/* I2C_FIFO_ADDR_CFG_EN:R/W；位位置：[11]；默认值：1’b0；*/
/*描述：。*/
#define I2C_FIFO_ADDR_CFG_EN    (BIT(11))
#define I2C_FIFO_ADDR_CFG_EN_M  (BIT(11))
#define I2C_FIFO_ADDR_CFG_EN_V  0x1
#define I2C_FIFO_ADDR_CFG_EN_S  11
/* I2C_nonifo_EN:R/W；位位置：[10]；默认值：1’b0；*/
/*描述：。*/
#define I2C_NONFIFO_EN    (BIT(10))
#define I2C_NONFIFO_EN_M  (BIT(10))
#define I2C_NONFIFO_EN_V  0x1
#define I2C_NONFIFO_EN_S  10
/* I2C_TXFIFO_WM_THRHD:R/W；比特位置：[9:5]；默认值：5'h4；*/
/*描述：。*/
#define I2C_TXFIFO_WM_THRHD    0x0000001F
#define I2C_TXFIFO_WM_THRHD_M  ((I2C_TXFIFO_WM_THRHD_V)<<(I2C_TXFIFO_WM_THRHD_S))
#define I2C_TXFIFO_WM_THRHD_V  0x1F
#define I2C_TXFIFO_WM_THRHD_S  5
/* I2C_rxfiform_WM_THRHD:R/W；位位置：[4:0]；默认值：5’hb；*/
/*描述：。*/
#define I2C_RXFIFO_WM_THRHD    0x0000001F
#define I2C_RXFIFO_WM_THRHD_M  ((I2C_RXFIFO_WM_THRHD_V)<<(I2C_RXFIFO_WM_THRHD_S))
#define I2C_RXFIFO_WM_THRHD_V  0x1F
#define I2C_RXFIFO_WM_THRHD_S  0

#define I2C_DATA_REG(i)          (REG_I2C_BASE(i) + 0x1C)
/* I2C_FIFO_data:RO；位位置：[7:0]；默认值：8'b0；*/
/*描述：。*/
#define I2C_FIFO_RDATA    0x000000FF
#define I2C_FIFO_RDATA_M  ((I2C_FIFO_RDATA_V)<<(I2C_FIFO_RDATA_S))
#define I2C_FIFO_RDATA_V  0xFF
#define I2C_FIFO_RDATA_S  0

#define I2C_INT_RAW_REG(i)          (REG_I2C_BASE(i) + 0x20)
/* I2C_GENERAL_CALL_INT_RAW:R/SS/WTC；位位置：[17]；默认值：1’b0；*/
/*描述：。*/
#define I2C_GENERAL_CALL_INT_RAW    (BIT(17))
#define I2C_GENERAL_CALL_INT_RAW_M  (BIT(17))
#define I2C_GENERAL_CALL_INT_RAW_V  0x1
#define I2C_GENERAL_CALL_INT_RAW_S  17
/* I2C_SLAVE_surch_INT_RAW:R/SS/WTC；位位置：[16]；默认值：1’b0；*/
/*描述：。*/
#define I2C_SLAVE_STRETCH_INT_RAW    (BIT(16))
#define I2C_SLAVE_STRETCH_INT_RAW_M  (BIT(16))
#define I2C_SLAVE_STRETCH_INT_RAW_V  0x1
#define I2C_SLAVE_STRETCH_INT_RAW_S  16
/* I2C_DET_START_INT_RAW:R/SS/WTC；位位置：[15]；默认值：1’b0；*/
/*描述：。*/
#define I2C_DET_START_INT_RAW    (BIT(15))
#define I2C_DET_START_INT_RAW_M  (BIT(15))
#define I2C_DET_START_INT_RAW_V  0x1
#define I2C_DET_START_INT_RAW_S  15
/* I2C_SCL_MAIN_ST_TO_INT_RAW:R/SS/WTC；位位置：[14]；默认值：1’b0；*/
/*描述：。*/
#define I2C_SCL_MAIN_ST_TO_INT_RAW    (BIT(14))
#define I2C_SCL_MAIN_ST_TO_INT_RAW_M  (BIT(14))
#define I2C_SCL_MAIN_ST_TO_INT_RAW_V  0x1
#define I2C_SCL_MAIN_ST_TO_INT_RAW_S  14
/* I2C_SCL_ST_TO_INT_RAW:R/SS/WTC；位位置：[13]；默认值：1’b0；*/
/*描述：。*/
#define I2C_SCL_ST_TO_INT_RAW    (BIT(13))
#define I2C_SCL_ST_TO_INT_RAW_M  (BIT(13))
#define I2C_SCL_ST_TO_INT_RAW_V  0x1
#define I2C_SCL_ST_TO_INT_RAW_S  13
/* I2C_rxfix_UDF_INT_RAW:R/SS/WTC；位位置：[12]；默认值：1’b0；*/
/*描述：。*/
#define I2C_RXFIFO_UDF_INT_RAW    (BIT(12))
#define I2C_RXFIFO_UDF_INT_RAW_M  (BIT(12))
#define I2C_RXFIFO_UDF_INT_RAW_V  0x1
#define I2C_RXFIFO_UDF_INT_RAW_S  12
/* I2C_TXFIFO_OVF_INT_RAW:R/SS/WTC；位位置：[11]；默认值：1’b0；*/
/*描述：。*/
#define I2C_TXFIFO_OVF_INT_RAW    (BIT(11))
#define I2C_TXFIFO_OVF_INT_RAW_M  (BIT(11))
#define I2C_TXFIFO_OVF_INT_RAW_V  0x1
#define I2C_TXFIFO_OVF_INT_RAW_S  11
/* I2C_NACK_INT_RAW:R/SS/WTC；位位置：[10]；默认值：1’b0；*/
/*描述：。*/
#define I2C_NACK_INT_RAW    (BIT(10))
#define I2C_NACK_INT_RAW_M  (BIT(10))
#define I2C_NACK_INT_RAW_V  0x1
#define I2C_NACK_INT_RAW_S  10
/* I2C_TRANS_START_INT_RAW:R/SS/WTC；位位置：[9]；默认值：1’b0；*/
/*描述：。*/
#define I2C_TRANS_START_INT_RAW    (BIT(9))
#define I2C_TRANS_START_INT_RAW_M  (BIT(9))
#define I2C_TRANS_START_INT_RAW_V  0x1
#define I2C_TRANS_START_INT_RAW_S  9
/* I2C_TIME_OUT_INT_RAW:R/SS/WTC；位位置：[8]；默认值：1’b0；*/
/*描述：。*/
#define I2C_TIME_OUT_INT_RAW    (BIT(8))
#define I2C_TIME_OUT_INT_RAW_M  (BIT(8))
#define I2C_TIME_OUT_INT_RAW_V  0x1
#define I2C_TIME_OUT_INT_RAW_S  8
/* I2C_TRANS_COMPLETE_INT_RAW:R/SS/WTC；位位置：[7]；默认值：1’b0；*/
/*描述：。*/
#define I2C_TRANS_COMPLETE_INT_RAW    (BIT(7))
#define I2C_TRANS_COMPLETE_INT_RAW_M  (BIT(7))
#define I2C_TRANS_COMPLETE_INT_RAW_V  0x1
#define I2C_TRANS_COMPLETE_INT_RAW_S  7
/* I2C_MST_txifo_UDF_INT_RAW:R/SS/WTC；位位置：[6]；默认值：1’b0；*/
/*描述：。*/
#define I2C_MST_TXFIFO_UDF_INT_RAW    (BIT(6))
#define I2C_MST_TXFIFO_UDF_INT_RAW_M  (BIT(6))
#define I2C_MST_TXFIFO_UDF_INT_RAW_V  0x1
#define I2C_MST_TXFIFO_UDF_INT_RAW_S  6
/* I2C_arbitation_LOST_INT_RAW:R/SS/WTC；位位置：[5]；默认值：1’b0；*/
/*描述：。*/
#define I2C_ARBITRATION_LOST_INT_RAW    (BIT(5))
#define I2C_ARBITRATION_LOST_INT_RAW_M  (BIT(5))
#define I2C_ARBITRATION_LOST_INT_RAW_V  0x1
#define I2C_ARBITRATION_LOST_INT_RAW_S  5
/* I2C_BYTE_TRANS_DONE_INT_RAW:R/SS/WTC；位位置：[4]；默认值：1’b0；*/
/*描述：。*/
#define I2C_BYTE_TRANS_DONE_INT_RAW    (BIT(4))
#define I2C_BYTE_TRANS_DONE_INT_RAW_M  (BIT(4))
#define I2C_BYTE_TRANS_DONE_INT_RAW_V  0x1
#define I2C_BYTE_TRANS_DONE_INT_RAW_S  4
/* I2C_END_DETECT_INT_RAW:R/SS/WTC；位位置：[3]；默认值：1’b0；*/
/*描述：。*/
#define I2C_END_DETECT_INT_RAW    (BIT(3))
#define I2C_END_DETECT_INT_RAW_M  (BIT(3))
#define I2C_END_DETECT_INT_RAW_V  0x1
#define I2C_END_DETECT_INT_RAW_S  3
/* I2C_RXFIFO_OVF_INT_RAW:R/SS/WTC；位位置：[2]；默认值：1’b0；*/
/*描述：。*/
#define I2C_RXFIFO_OVF_INT_RAW    (BIT(2))
#define I2C_RXFIFO_OVF_INT_RAW_M  (BIT(2))
#define I2C_RXFIFO_OVF_INT_RAW_V  0x1
#define I2C_RXFIFO_OVF_INT_RAW_S  2
/* I2C_TXFIFO_WM_INT_RAW:R/SS/WTC；位位置：[1]；默认值：1’b1；*/
/*描述：。*/
#define I2C_TXFIFO_WM_INT_RAW    (BIT(1))
#define I2C_TXFIFO_WM_INT_RAW_M  (BIT(1))
#define I2C_TXFIFO_WM_INT_RAW_V  0x1
#define I2C_TXFIFO_WM_INT_RAW_S  1
/* I2C_rxifo_WM_INT_RAW:R/SS/WTC；位位置：[0]；默认值：1’b0；*/
/*描述：。*/
#define I2C_RXFIFO_WM_INT_RAW    (BIT(0))
#define I2C_RXFIFO_WM_INT_RAW_M  (BIT(0))
#define I2C_RXFIFO_WM_INT_RAW_V  0x1
#define I2C_RXFIFO_WM_INT_RAW_S  0

#define I2C_INT_CLR_REG(i)          (REG_I2C_BASE(i) + 0x24)
/* I2C_GENERAL_CALL_INT_CLR:WT；位位置：[17]；默认值：1’b0；*/
/*描述：。*/
#define I2C_GENERAL_CALL_INT_CLR    (BIT(17))
#define I2C_GENERAL_CALL_INT_CLR_M  (BIT(17))
#define I2C_GENERAL_CALL_INT_CLR_V  0x1
#define I2C_GENERAL_CALL_INT_CLR_S  17
/* I2C_SLAVE_surch_INT_CLR:WT；位位置：[16]；默认值：1’b0；*/
/*描述：。*/
#define I2C_SLAVE_STRETCH_INT_CLR    (BIT(16))
#define I2C_SLAVE_STRETCH_INT_CLR_M  (BIT(16))
#define I2C_SLAVE_STRETCH_INT_CLR_V  0x1
#define I2C_SLAVE_STRETCH_INT_CLR_S  16
/* I2C_DET_START_INT_CLR:WT；位位置：[15]；默认值：1’b0；*/
/*描述：。*/
#define I2C_DET_START_INT_CLR    (BIT(15))
#define I2C_DET_START_INT_CLR_M  (BIT(15))
#define I2C_DET_START_INT_CLR_V  0x1
#define I2C_DET_START_INT_CLR_S  15
/* I2C_SCL_MAIN_ST_TO_INT_CLR:WT；位位置：[14]；默认值：1’b0；*/
/*描述：。*/
#define I2C_SCL_MAIN_ST_TO_INT_CLR    (BIT(14))
#define I2C_SCL_MAIN_ST_TO_INT_CLR_M  (BIT(14))
#define I2C_SCL_MAIN_ST_TO_INT_CLR_V  0x1
#define I2C_SCL_MAIN_ST_TO_INT_CLR_S  14
/* I2C_SCL_ST_TO_INT_CLR:WT；位位置：[13]；默认值：1’b0；*/
/*描述：。*/
#define I2C_SCL_ST_TO_INT_CLR    (BIT(13))
#define I2C_SCL_ST_TO_INT_CLR_M  (BIT(13))
#define I2C_SCL_ST_TO_INT_CLR_V  0x1
#define I2C_SCL_ST_TO_INT_CLR_S  13
/* I2C_rxfix_UDF_INT_CLR:WT；位位置：[12]；默认值：1’b0；*/
/*描述：。*/
#define I2C_RXFIFO_UDF_INT_CLR    (BIT(12))
#define I2C_RXFIFO_UDF_INT_CLR_M  (BIT(12))
#define I2C_RXFIFO_UDF_INT_CLR_V  0x1
#define I2C_RXFIFO_UDF_INT_CLR_S  12
/* I2C_TXFIFO_OVF_INT_CLR:WT；位位置：[11]；默认值：1’b0；*/
/*描述：。*/
#define I2C_TXFIFO_OVF_INT_CLR    (BIT(11))
#define I2C_TXFIFO_OVF_INT_CLR_M  (BIT(11))
#define I2C_TXFIFO_OVF_INT_CLR_V  0x1
#define I2C_TXFIFO_OVF_INT_CLR_S  11
/* I2C_NACK_INT_CLR:WT；位位置：[10]；默认值：1’b0；*/
/*描述：。*/
#define I2C_NACK_INT_CLR    (BIT(10))
#define I2C_NACK_INT_CLR_M  (BIT(10))
#define I2C_NACK_INT_CLR_V  0x1
#define I2C_NACK_INT_CLR_S  10
/* I2C_TRANS_START_INT_CLR:WT；位位置：[9]；默认值：1’b0；*/
/*描述：。*/
#define I2C_TRANS_START_INT_CLR    (BIT(9))
#define I2C_TRANS_START_INT_CLR_M  (BIT(9))
#define I2C_TRANS_START_INT_CLR_V  0x1
#define I2C_TRANS_START_INT_CLR_S  9
/* I2C_TIME_OUT_INT_CLR:WT；位位置：[8]；默认值：1’b0；*/
/*描述：。*/
#define I2C_TIME_OUT_INT_CLR    (BIT(8))
#define I2C_TIME_OUT_INT_CLR_M  (BIT(8))
#define I2C_TIME_OUT_INT_CLR_V  0x1
#define I2C_TIME_OUT_INT_CLR_S  8
/* I2C_TRANS_COMPLETE_INT_CLR:WT；位位置：[7]；默认值：1’b0；*/
/*描述：。*/
#define I2C_TRANS_COMPLETE_INT_CLR    (BIT(7))
#define I2C_TRANS_COMPLETE_INT_CLR_M  (BIT(7))
#define I2C_TRANS_COMPLETE_INT_CLR_V  0x1
#define I2C_TRANS_COMPLETE_INT_CLR_S  7
/* I2C_MST_xfifo_UDF_INT_CLR:WT；位位置：[6]；默认值：1’b0；*/
/*描述：。*/
#define I2C_MST_TXFIFO_UDF_INT_CLR    (BIT(6))
#define I2C_MST_TXFIFO_UDF_INT_CLR_M  (BIT(6))
#define I2C_MST_TXFIFO_UDF_INT_CLR_V  0x1
#define I2C_MST_TXFIFO_UDF_INT_CLR_S  6
/* I2C_arbitation_LOST_INT_CLR:WT；位位置：[5]；默认值：1’b0；*/
/*描述：。*/
#define I2C_ARBITRATION_LOST_INT_CLR    (BIT(5))
#define I2C_ARBITRATION_LOST_INT_CLR_M  (BIT(5))
#define I2C_ARBITRATION_LOST_INT_CLR_V  0x1
#define I2C_ARBITRATION_LOST_INT_CLR_S  5
/* I2C_BYTE_TRANS_DONE_INT_CLR:WT；位位置：[4]；默认值：1’b0；*/
/*描述：。*/
#define I2C_BYTE_TRANS_DONE_INT_CLR    (BIT(4))
#define I2C_BYTE_TRANS_DONE_INT_CLR_M  (BIT(4))
#define I2C_BYTE_TRANS_DONE_INT_CLR_V  0x1
#define I2C_BYTE_TRANS_DONE_INT_CLR_S  4
/* I2C_END_DETECT_INT_CLR:WT；位位置：[3]；默认值：1’b0；*/
/*描述：。*/
#define I2C_END_DETECT_INT_CLR    (BIT(3))
#define I2C_END_DETECT_INT_CLR_M  (BIT(3))
#define I2C_END_DETECT_INT_CLR_V  0x1
#define I2C_END_DETECT_INT_CLR_S  3
/* I2C_RXFIFO_OVF_INT_CLR:WT；位位置：[2]；默认值：1’b0；*/
/*描述：。*/
#define I2C_RXFIFO_OVF_INT_CLR    (BIT(2))
#define I2C_RXFIFO_OVF_INT_CLR_M  (BIT(2))
#define I2C_RXFIFO_OVF_INT_CLR_V  0x1
#define I2C_RXFIFO_OVF_INT_CLR_S  2
/* I2C_TXFIFO_WM_INT_CLR:WT；位位置：[1]；默认值：1’b0；*/
/*描述：。*/
#define I2C_TXFIFO_WM_INT_CLR    (BIT(1))
#define I2C_TXFIFO_WM_INT_CLR_M  (BIT(1))
#define I2C_TXFIFO_WM_INT_CLR_V  0x1
#define I2C_TXFIFO_WM_INT_CLR_S  1
/* I2C_rxifo_WM_INT_CLR:WT；位位置：[0]；默认值：1’b0；*/
/*描述：。*/
#define I2C_RXFIFO_WM_INT_CLR    (BIT(0))
#define I2C_RXFIFO_WM_INT_CLR_M  (BIT(0))
#define I2C_RXFIFO_WM_INT_CLR_V  0x1
#define I2C_RXFIFO_WM_INT_CLR_S  0

#define I2C_INT_ENA_REG(i)          (REG_I2C_BASE(i) + 0x28)
/* I2C_GENERAL_CALL_INT_ENA:R/W；位位置：[17]；默认值：1’b0；*/
/*描述：。*/
#define I2C_GENERAL_CALL_INT_ENA    (BIT(17))
#define I2C_GENERAL_CALL_INT_ENA_M  (BIT(17))
#define I2C_GENERAL_CALL_INT_ENA_V  0x1
#define I2C_GENERAL_CALL_INT_ENA_S  17
/* I2C_SLAVE_surch_INT_ENA:R/W；位位置：[16]；默认值：1’b0；*/
/*描述：。*/
#define I2C_SLAVE_STRETCH_INT_ENA    (BIT(16))
#define I2C_SLAVE_STRETCH_INT_ENA_M  (BIT(16))
#define I2C_SLAVE_STRETCH_INT_ENA_V  0x1
#define I2C_SLAVE_STRETCH_INT_ENA_S  16
/* I2C_DET_START_INT_ENA:R/W；位位置：[15]；默认值：1’b0；*/
/*描述：。*/
#define I2C_DET_START_INT_ENA    (BIT(15))
#define I2C_DET_START_INT_ENA_M  (BIT(15))
#define I2C_DET_START_INT_ENA_V  0x1
#define I2C_DET_START_INT_ENA_S  15
/* I2C_SCL_MAIN_ST_TO_INT_ENA:R/W；位位置：[14]；默认值：1’b0；*/
/*描述：。*/
#define I2C_SCL_MAIN_ST_TO_INT_ENA    (BIT(14))
#define I2C_SCL_MAIN_ST_TO_INT_ENA_M  (BIT(14))
#define I2C_SCL_MAIN_ST_TO_INT_ENA_V  0x1
#define I2C_SCL_MAIN_ST_TO_INT_ENA_S  14
/* I2C_SCL_ST_TO_INT_ENA:R/W；位位置：[13]；默认值：1’b0；*/
/*描述：。*/
#define I2C_SCL_ST_TO_INT_ENA    (BIT(13))
#define I2C_SCL_ST_TO_INT_ENA_M  (BIT(13))
#define I2C_SCL_ST_TO_INT_ENA_V  0x1
#define I2C_SCL_ST_TO_INT_ENA_S  13
/* I2C_rxfix_UDF_INT_ENA:R/W；位位置：[12]；默认值：1’b0；*/
/*描述：。*/
#define I2C_RXFIFO_UDF_INT_ENA    (BIT(12))
#define I2C_RXFIFO_UDF_INT_ENA_M  (BIT(12))
#define I2C_RXFIFO_UDF_INT_ENA_V  0x1
#define I2C_RXFIFO_UDF_INT_ENA_S  12
/* I2C_TXFIFO_OVF_INT_ENA:R/W；位位置：[11]；默认值：1’b0；*/
/*描述：。*/
#define I2C_TXFIFO_OVF_INT_ENA    (BIT(11))
#define I2C_TXFIFO_OVF_INT_ENA_M  (BIT(11))
#define I2C_TXFIFO_OVF_INT_ENA_V  0x1
#define I2C_TXFIFO_OVF_INT_ENA_S  11
/* I2C_NACK_INT_ENA:R/W；位位置：[10]；默认值：1’b0；*/
/*描述：。*/
#define I2C_NACK_INT_ENA    (BIT(10))
#define I2C_NACK_INT_ENA_M  (BIT(10))
#define I2C_NACK_INT_ENA_V  0x1
#define I2C_NACK_INT_ENA_S  10
/* I2C_TRANS_START_INT_ENA:R/W；位位置：[9]；默认值：1’b0；*/
/*描述：。*/
#define I2C_TRANS_START_INT_ENA    (BIT(9))
#define I2C_TRANS_START_INT_ENA_M  (BIT(9))
#define I2C_TRANS_START_INT_ENA_V  0x1
#define I2C_TRANS_START_INT_ENA_S  9
/* I2C_TIME_OUT_INT_ENA:R/W；位位置：[8]；默认值：1’b0；*/
/*描述：。*/
#define I2C_TIME_OUT_INT_ENA    (BIT(8))
#define I2C_TIME_OUT_INT_ENA_M  (BIT(8))
#define I2C_TIME_OUT_INT_ENA_V  0x1
#define I2C_TIME_OUT_INT_ENA_S  8
/* I2C_TRANS_COMPLETE_INT_ENA:R/W；位位置：[7]；默认值：1’b0；*/
/*描述：。*/
#define I2C_TRANS_COMPLETE_INT_ENA    (BIT(7))
#define I2C_TRANS_COMPLETE_INT_ENA_M  (BIT(7))
#define I2C_TRANS_COMPLETE_INT_ENA_V  0x1
#define I2C_TRANS_COMPLETE_INT_ENA_S  7
/* I2C_MST_txifo_UDF-INT_ENA:R/W；位位置：[6]；默认值：1’b0；*/
/*描述：。*/
#define I2C_MST_TXFIFO_UDF_INT_ENA    (BIT(6))
#define I2C_MST_TXFIFO_UDF_INT_ENA_M  (BIT(6))
#define I2C_MST_TXFIFO_UDF_INT_ENA_V  0x1
#define I2C_MST_TXFIFO_UDF_INT_ENA_S  6
/* I2C_arbitation_LOST_INT_ENA:R/W；位位置：[5]；默认值：1’b0；*/
/*描述：。*/
#define I2C_ARBITRATION_LOST_INT_ENA    (BIT(5))
#define I2C_ARBITRATION_LOST_INT_ENA_M  (BIT(5))
#define I2C_ARBITRATION_LOST_INT_ENA_V  0x1
#define I2C_ARBITRATION_LOST_INT_ENA_S  5
/* I2C_BYTE_TRANS_DONE_INT_ENA：R/W；位位置：[4]；默认值：1’b0；*/
/*描述：。*/
#define I2C_BYTE_TRANS_DONE_INT_ENA    (BIT(4))
#define I2C_BYTE_TRANS_DONE_INT_ENA_M  (BIT(4))
#define I2C_BYTE_TRANS_DONE_INT_ENA_V  0x1
#define I2C_BYTE_TRANS_DONE_INT_ENA_S  4
/* I2C_END_DETECT_INT_ENA:R/W；位位置：[3]；默认值：1’b0；*/
/*描述：。*/
#define I2C_END_DETECT_INT_ENA    (BIT(3))
#define I2C_END_DETECT_INT_ENA_M  (BIT(3))
#define I2C_END_DETECT_INT_ENA_V  0x1
#define I2C_END_DETECT_INT_ENA_S  3
/* I2C_RXFIFO_OVF_INT_ENA：R/W；位位置：[2]；默认值：1’b0；*/
/*描述：。*/
#define I2C_RXFIFO_OVF_INT_ENA    (BIT(2))
#define I2C_RXFIFO_OVF_INT_ENA_M  (BIT(2))
#define I2C_RXFIFO_OVF_INT_ENA_V  0x1
#define I2C_RXFIFO_OVF_INT_ENA_S  2
/* I2C_TXFIFO_WM_INT_ENA:R/W；位位置：[1]；默认值：1’b0；*/
/*描述：。*/
#define I2C_TXFIFO_WM_INT_ENA    (BIT(1))
#define I2C_TXFIFO_WM_INT_ENA_M  (BIT(1))
#define I2C_TXFIFO_WM_INT_ENA_V  0x1
#define I2C_TXFIFO_WM_INT_ENA_S  1
/* I2C_rxfiform_WM_INT_ENA:R/W；位位置：[0]；默认值：1’b0；*/
/*描述：。*/
#define I2C_RXFIFO_WM_INT_ENA    (BIT(0))
#define I2C_RXFIFO_WM_INT_ENA_M  (BIT(0))
#define I2C_RXFIFO_WM_INT_ENA_V  0x1
#define I2C_RXFIFO_WM_INT_ENA_S  0

#define I2C_INT_STATUS_REG(i)          (REG_I2C_BASE(i) + 0x2C)
/* I2C_GENERAL_CALL_INT_ST:RO；位位置：[17]；默认值：1’b0；*/
/*描述：。*/
#define I2C_GENERAL_CALL_INT_ST    (BIT(17))
#define I2C_GENERAL_CALL_INT_ST_M  (BIT(17))
#define I2C_GENERAL_CALL_INT_ST_V  0x1
#define I2C_GENERAL_CALL_INT_ST_S  17
/* I2C_SLAVE_strech_INT_ST:RO；位位置：[16]；默认值：1’b0；*/
/*描述：。*/
#define I2C_SLAVE_STRETCH_INT_ST    (BIT(16))
#define I2C_SLAVE_STRETCH_INT_ST_M  (BIT(16))
#define I2C_SLAVE_STRETCH_INT_ST_V  0x1
#define I2C_SLAVE_STRETCH_INT_ST_S  16
/* I2C_DET_START_INT_ST:RO；位位置：[15]；默认值：1’b0；*/
/*描述：。*/
#define I2C_DET_START_INT_ST    (BIT(15))
#define I2C_DET_START_INT_ST_M  (BIT(15))
#define I2C_DET_START_INT_ST_V  0x1
#define I2C_DET_START_INT_ST_S  15
/* I2C_SCL_MAIN_ST_TO_INT_ST:RO；位位置：[14]；默认值：1’b0；*/
/*描述：。*/
#define I2C_SCL_MAIN_ST_TO_INT_ST    (BIT(14))
#define I2C_SCL_MAIN_ST_TO_INT_ST_M  (BIT(14))
#define I2C_SCL_MAIN_ST_TO_INT_ST_V  0x1
#define I2C_SCL_MAIN_ST_TO_INT_ST_S  14
/* I2C_SCL_ST_TO_INT_ST:RO；位位置：[13]；默认值：1’b0；*/
/*描述：。*/
#define I2C_SCL_ST_TO_INT_ST    (BIT(13))
#define I2C_SCL_ST_TO_INT_ST_M  (BIT(13))
#define I2C_SCL_ST_TO_INT_ST_V  0x1
#define I2C_SCL_ST_TO_INT_ST_S  13
/* I2C_rxfix_UDF_INT_ST:RO；位位置：[12]；默认值：1’b0；*/
/*描述：。*/
#define I2C_RXFIFO_UDF_INT_ST    (BIT(12))
#define I2C_RXFIFO_UDF_INT_ST_M  (BIT(12))
#define I2C_RXFIFO_UDF_INT_ST_V  0x1
#define I2C_RXFIFO_UDF_INT_ST_S  12
/* I2C_TXFIFO_OVF_INT_ST:RO；位位置：[11]；默认值：1’b0；*/
/*描述：。*/
#define I2C_TXFIFO_OVF_INT_ST    (BIT(11))
#define I2C_TXFIFO_OVF_INT_ST_M  (BIT(11))
#define I2C_TXFIFO_OVF_INT_ST_V  0x1
#define I2C_TXFIFO_OVF_INT_ST_S  11
/* I2C_NACK_INT_ST:RO；位位置：[10]；默认值：1’b0；*/
/*描述：。*/
#define I2C_NACK_INT_ST    (BIT(10))
#define I2C_NACK_INT_ST_M  (BIT(10))
#define I2C_NACK_INT_ST_V  0x1
#define I2C_NACK_INT_ST_S  10
/* I2C_TRANS_START_INT_ST:RO；位位置：[9]；默认值：1’b0；*/
/*描述：。*/
#define I2C_TRANS_START_INT_ST    (BIT(9))
#define I2C_TRANS_START_INT_ST_M  (BIT(9))
#define I2C_TRANS_START_INT_ST_V  0x1
#define I2C_TRANS_START_INT_ST_S  9
/* I2C_TIME_OUT_INT_ST:RO；位位置：[8]；默认值：1’b0；*/
/*描述：。*/
#define I2C_TIME_OUT_INT_ST    (BIT(8))
#define I2C_TIME_OUT_INT_ST_M  (BIT(8))
#define I2C_TIME_OUT_INT_ST_V  0x1
#define I2C_TIME_OUT_INT_ST_S  8
/* I2C_TRANS_COMPLETE_INT_ST:RO；位位置：[7]；默认值：1’b0；*/
/*描述：。*/
#define I2C_TRANS_COMPLETE_INT_ST    (BIT(7))
#define I2C_TRANS_COMPLETE_INT_ST_M  (BIT(7))
#define I2C_TRANS_COMPLETE_INT_ST_V  0x1
#define I2C_TRANS_COMPLETE_INT_ST_S  7
/* I2C_MST_txifo_UDF_INT_ST:RO；位位置：[6]；默认值：1’b0；*/
/*描述：。*/
#define I2C_MST_TXFIFO_UDF_INT_ST    (BIT(6))
#define I2C_MST_TXFIFO_UDF_INT_ST_M  (BIT(6))
#define I2C_MST_TXFIFO_UDF_INT_ST_V  0x1
#define I2C_MST_TXFIFO_UDF_INT_ST_S  6
/* I2C_arbitation_LOST_INT_ST:RO；位位置：[5]；默认值：1’b0；*/
/*描述：。*/
#define I2C_ARBITRATION_LOST_INT_ST    (BIT(5))
#define I2C_ARBITRATION_LOST_INT_ST_M  (BIT(5))
#define I2C_ARBITRATION_LOST_INT_ST_V  0x1
#define I2C_ARBITRATION_LOST_INT_ST_S  5
/* I2C_BYTE_TRANS_DONE_INT_ST:RO；位位置：[4]；默认值：1’b0；*/
/*描述：。*/
#define I2C_BYTE_TRANS_DONE_INT_ST    (BIT(4))
#define I2C_BYTE_TRANS_DONE_INT_ST_M  (BIT(4))
#define I2C_BYTE_TRANS_DONE_INT_ST_V  0x1
#define I2C_BYTE_TRANS_DONE_INT_ST_S  4
/* I2C_END_DETECT_INT_ST:RO；位位置：[3]；默认值：1’b0；*/
/*描述：。*/
#define I2C_END_DETECT_INT_ST    (BIT(3))
#define I2C_END_DETECT_INT_ST_M  (BIT(3))
#define I2C_END_DETECT_INT_ST_V  0x1
#define I2C_END_DETECT_INT_ST_S  3
/* I2C_RXFIFO_OVF_INT_ST:RO；位位置：[2]；默认值：1’b0；*/
/*描述：。*/
#define I2C_RXFIFO_OVF_INT_ST    (BIT(2))
#define I2C_RXFIFO_OVF_INT_ST_M  (BIT(2))
#define I2C_RXFIFO_OVF_INT_ST_V  0x1
#define I2C_RXFIFO_OVF_INT_ST_S  2
/* I2C_TXFIFO_WM_INT_ST:RO；位位置：[1]；默认值：1’b0；*/
/*描述：。*/
#define I2C_TXFIFO_WM_INT_ST    (BIT(1))
#define I2C_TXFIFO_WM_INT_ST_M  (BIT(1))
#define I2C_TXFIFO_WM_INT_ST_V  0x1
#define I2C_TXFIFO_WM_INT_ST_S  1
/* I2C_rxifo_WM_INT_ST:RO；位位置：[0]；默认值：1’b0；*/
/*描述：。*/
#define I2C_RXFIFO_WM_INT_ST    (BIT(0))
#define I2C_RXFIFO_WM_INT_ST_M  (BIT(0))
#define I2C_RXFIFO_WM_INT_ST_V  0x1
#define I2C_RXFIFO_WM_INT_ST_S  0

#define I2C_SDA_HOLD_REG(i)          (REG_I2C_BASE(i) + 0x30)
/* I2C_SDA_HOLD_TIME:R/W；位位置：[8:0]；默认值：9'b0；*/
/*描述：。*/
#define I2C_SDA_HOLD_TIME    0x000001FF
#define I2C_SDA_HOLD_TIME_M  ((I2C_SDA_HOLD_TIME_V)<<(I2C_SDA_HOLD_TIME_S))
#define I2C_SDA_HOLD_TIME_V  0x1FF
#define I2C_SDA_HOLD_TIME_S  0

#define I2C_SDA_SAMPLE_REG(i)          (REG_I2C_BASE(i) + 0x34)
/* I2C_SDA_SAMPLE_TIME:R/W；位位置：[8:0]；默认值：9'b0；*/
/*描述：。*/
#define I2C_SDA_SAMPLE_TIME    0x000001FF
#define I2C_SDA_SAMPLE_TIME_M  ((I2C_SDA_SAMPLE_TIME_V)<<(I2C_SDA_SAMPLE_TIME_S))
#define I2C_SDA_SAMPLE_TIME_V  0x1FF
#define I2C_SDA_SAMPLE_TIME_S  0

#define I2C_SCL_HIGH_PERIOD_REG(i)          (REG_I2C_BASE(i) + 0x38)
/* I2C_SCL_WAIT_HIGH_PERIOD:R/W；比特位置：[15:9]；默认值：7'b0；*/
/*描述：。*/
#define I2C_SCL_WAIT_HIGH_PERIOD    0x0000007F
#define I2C_SCL_WAIT_HIGH_PERIOD_M  ((I2C_SCL_WAIT_HIGH_PERIOD_V)<<(I2C_SCL_WAIT_HIGH_PERIOD_S))
#define I2C_SCL_WAIT_HIGH_PERIOD_V  0x7F
#define I2C_SCL_WAIT_HIGH_PERIOD_S  9
/* I2C_SCL_HIGH-PERIOD:R/W；位位置：[8:0]；默认值：9'b0；*/
/*描述：。*/
#define I2C_SCL_HIGH_PERIOD    0x000001FF
#define I2C_SCL_HIGH_PERIOD_M  ((I2C_SCL_HIGH_PERIOD_V)<<(I2C_SCL_HIGH_PERIOD_S))
#define I2C_SCL_HIGH_PERIOD_V  0x1FF
#define I2C_SCL_HIGH_PERIOD_S  0

#define I2C_SCL_START_HOLD_REG(i)          (REG_I2C_BASE(i) + 0x40)
/* I2C_SCL_START_HOLD_TIME:R/W；位位置：[8:0]；默认值：9'b1000；*/
/*描述：。*/
#define I2C_SCL_START_HOLD_TIME    0x000001FF
#define I2C_SCL_START_HOLD_TIME_M  ((I2C_SCL_START_HOLD_TIME_V)<<(I2C_SCL_START_HOLD_TIME_S))
#define I2C_SCL_START_HOLD_TIME_V  0x1FF
#define I2C_SCL_START_HOLD_TIME_S  0

#define I2C_SCL_RSTART_SETUP_REG(i)          (REG_I2C_BASE(i) + 0x44)
/* I2C_SCL_RSTART_SETUP_TIME:R/W；位位置：[8:0]；默认值：9'b1000；*/
/*描述：。*/
#define I2C_SCL_RSTART_SETUP_TIME    0x000001FF
#define I2C_SCL_RSTART_SETUP_TIME_M  ((I2C_SCL_RSTART_SETUP_TIME_V)<<(I2C_SCL_RSTART_SETUP_TIME_S))
#define I2C_SCL_RSTART_SETUP_TIME_V  0x1FF
#define I2C_SCL_RSTART_SETUP_TIME_S  0

#define I2C_SCL_STOP_HOLD_REG(i)          (REG_I2C_BASE(i) + 0x48)
/* I2C_SCL_STOP_HOLD_TIME:R/W；位位置：[8:0]；默认值：9'b1000；*/
/*描述：。*/
#define I2C_SCL_STOP_HOLD_TIME    0x000001FF
#define I2C_SCL_STOP_HOLD_TIME_M  ((I2C_SCL_STOP_HOLD_TIME_V)<<(I2C_SCL_STOP_HOLD_TIME_S))
#define I2C_SCL_STOP_HOLD_TIME_V  0x1FF
#define I2C_SCL_STOP_HOLD_TIME_S  0

#define I2C_SCL_STOP_SETUP_REG(i)          (REG_I2C_BASE(i) + 0x4C)
/* I2C_SCL_STOP_SETUP_TIME:R/W；位位置：[8:0]；默认值：9'b1000；*/
/*描述：。*/
#define I2C_SCL_STOP_SETUP_TIME    0x000001FF
#define I2C_SCL_STOP_SETUP_TIME_M  ((I2C_SCL_STOP_SETUP_TIME_V)<<(I2C_SCL_STOP_SETUP_TIME_S))
#define I2C_SCL_STOP_SETUP_TIME_V  0x1FF
#define I2C_SCL_STOP_SETUP_TIME_S  0

#define I2C_FILTER_CFG_REG(i)          (REG_I2C_BASE(i) + 0x50)
/* I2C_SDA_FILTER_EN:R/W；位位置：[9]；默认值：1’b1；*/
/*描述：。*/
#define I2C_SDA_FILTER_EN    (BIT(9))
#define I2C_SDA_FILTER_EN_M  (BIT(9))
#define I2C_SDA_FILTER_EN_V  0x1
#define I2C_SDA_FILTER_EN_S  9
/* I2C_SCL_FILTER_EN:R/W；位位置：[8]；默认值：1’b1；*/
/*描述：。*/
#define I2C_SCL_FILTER_EN    (BIT(8))
#define I2C_SCL_FILTER_EN_M  (BIT(8))
#define I2C_SCL_FILTER_EN_V  0x1
#define I2C_SCL_FILTER_EN_S  8
/* I2C_SDA_FILTER_threes:R/W；位位置：[7:4]；默认值：4'b0；*/
/*描述：。*/
#define I2C_SDA_FILTER_THRES    0x0000000F
#define I2C_SDA_FILTER_THRES_M  ((I2C_SDA_FILTER_THRES_V)<<(I2C_SDA_FILTER_THRES_S))
#define I2C_SDA_FILTER_THRES_V  0xF
#define I2C_SDA_FILTER_THRES_S  4
/* I2C_SCL_FILTER_threes:R/W；位位置：[3:0]；默认值：4'b0；*/
/*描述：。*/
#define I2C_SCL_FILTER_THRES    0x0000000F
#define I2C_SCL_FILTER_THRES_M  ((I2C_SCL_FILTER_THRES_V)<<(I2C_SCL_FILTER_THRES_S))
#define I2C_SCL_FILTER_THRES_V  0xF
#define I2C_SCL_FILTER_THRES_S  0

#define I2C_CLK_CONF_REG(i)          (REG_I2C_BASE(i) + 0x54)
/* I2C_SCLK_ACTIVE:R/W；位位置：[21]；默认值：1’b1；*/
/*描述：。*/
#define I2C_SCLK_ACTIVE    (BIT(21))
#define I2C_SCLK_ACTIVE_M  (BIT(21))
#define I2C_SCLK_ACTIVE_V  0x1
#define I2C_SCLK_ACTIVE_S  21
/* I2C_SCLK_SEL:R/W；位位置：[20]；默认值：1’b0；*/
/*描述：。*/
#define I2C_SCLK_SEL    (BIT(20))
#define I2C_SCLK_SEL_M  (BIT(20))
#define I2C_SCLK_SEL_V  0x1
#define I2C_SCLK_SEL_S  20
/* I2C_SCLK_DIV_B:R/W；比特位置：[19:14]；默认值：6'b0；*/
/*描述：。*/
#define I2C_SCLK_DIV_B    0x0000003F
#define I2C_SCLK_DIV_B_M  ((I2C_SCLK_DIV_B_V)<<(I2C_SCLK_DIV_B_S))
#define I2C_SCLK_DIV_B_V  0x3F
#define I2C_SCLK_DIV_B_S  14
/* I2C_SCLK_DIV_A:R/W；比特位置：[13:8]；默认值：6'b0；*/
/*描述：。*/
#define I2C_SCLK_DIV_A    0x0000003F
#define I2C_SCLK_DIV_A_M  ((I2C_SCLK_DIV_A_V)<<(I2C_SCLK_DIV_A_S))
#define I2C_SCLK_DIV_A_V  0x3F
#define I2C_SCLK_DIV_A_S  8
/* I2C_SCLK_DIV_NUM:R/W；位位置：[7:0]；默认值：8'b0；*/
/*描述：。*/
#define I2C_SCLK_DIV_NUM    0x000000FF
#define I2C_SCLK_DIV_NUM_M  ((I2C_SCLK_DIV_NUM_V)<<(I2C_SCLK_DIV_NUM_S))
#define I2C_SCLK_DIV_NUM_V  0xFF
#define I2C_SCLK_DIV_NUM_S  0

#define I2C_COMD0_REG(i)          (REG_I2C_BASE(i) + 0x58)
/* I2C_COMMAND0_DONE:R/W/SS；位位置：[31]；默认值：1’b0；*/
/*描述：。*/
#define I2C_COMMAND0_DONE    (BIT(31))
#define I2C_COMMAND0_DONE_M  (BIT(31))
#define I2C_COMMAND0_DONE_V  0x1
#define I2C_COMMAND0_DONE_S  31
/* I2C_COMMAND0:R/W；比特位置：[13:0]；默认值：14'b0；*/
/*描述：。*/
#define I2C_COMMAND0    0x00003FFF
#define I2C_COMMAND0_M  ((I2C_COMMAND0_V)<<(I2C_COMMAND0_S))
#define I2C_COMMAND0_V  0x3FFF
#define I2C_COMMAND0_S  0

#define I2C_COMD1_REG(i)          (REG_I2C_BASE(i) + 0x5C)
/* I2C_COMMAND1_DONE:R/W/SS；位位置：[31]；默认值：1’b0；*/
/*描述：。*/
#define I2C_COMMAND1_DONE    (BIT(31))
#define I2C_COMMAND1_DONE_M  (BIT(31))
#define I2C_COMMAND1_DONE_V  0x1
#define I2C_COMMAND1_DONE_S  31
/* I2C_COMMAND1:R/W；比特位置：[13:0]；默认值：14'b0；*/
/*描述：。*/
#define I2C_COMMAND1    0x00003FFF
#define I2C_COMMAND1_M  ((I2C_COMMAND1_V)<<(I2C_COMMAND1_S))
#define I2C_COMMAND1_V  0x3FFF
#define I2C_COMMAND1_S  0

#define I2C_COMD2_REG(i)          (REG_I2C_BASE(i) + 0x60)
/* I2C_COMMAND2_DONE:R/W/SS；位位置：[31]；默认值：1’b0；*/
/*描述：。*/
#define I2C_COMMAND2_DONE    (BIT(31))
#define I2C_COMMAND2_DONE_M  (BIT(31))
#define I2C_COMMAND2_DONE_V  0x1
#define I2C_COMMAND2_DONE_S  31
/* I2C_COMMAND2:R/W；比特位置：[13:0]；默认值：14'b0；*/
/*描述：。*/
#define I2C_COMMAND2    0x00003FFF
#define I2C_COMMAND2_M  ((I2C_COMMAND2_V)<<(I2C_COMMAND2_S))
#define I2C_COMMAND2_V  0x3FFF
#define I2C_COMMAND2_S  0

#define I2C_COMD3_REG(i)          (REG_I2C_BASE(i) + 0x64)
/* I2C_COMMAND3_DONE:R/W/SS；位位置：[31]；默认值：1’b0；*/
/*描述：。*/
#define I2C_COMMAND3_DONE    (BIT(31))
#define I2C_COMMAND3_DONE_M  (BIT(31))
#define I2C_COMMAND3_DONE_V  0x1
#define I2C_COMMAND3_DONE_S  31
/* I2C_COMMAND3:R/W；比特位置：[13:0]；默认值：14'b0；*/
/*描述：。*/
#define I2C_COMMAND3    0x00003FFF
#define I2C_COMMAND3_M  ((I2C_COMMAND3_V)<<(I2C_COMMAND3_S))
#define I2C_COMMAND3_V  0x3FFF
#define I2C_COMMAND3_S  0

#define I2C_COMD4_REG(i)          (REG_I2C_BASE(i) + 0x68)
/* I2C_COMMAND4_DONE:R/W/SS；位位置：[31]；默认值：1’b0；*/
/*描述：。*/
#define I2C_COMMAND4_DONE    (BIT(31))
#define I2C_COMMAND4_DONE_M  (BIT(31))
#define I2C_COMMAND4_DONE_V  0x1
#define I2C_COMMAND4_DONE_S  31
/* I2C_COMMAND4:R/W；比特位置：[13:0]；默认值：14'b0；*/
/*描述：。*/
#define I2C_COMMAND4    0x00003FFF
#define I2C_COMMAND4_M  ((I2C_COMMAND4_V)<<(I2C_COMMAND4_S))
#define I2C_COMMAND4_V  0x3FFF
#define I2C_COMMAND4_S  0

#define I2C_COMD5_REG(i)          (REG_I2C_BASE(i) + 0x6C)
/* I2C_COMMAND5_DONE:R/W/SS；位位置：[31]；默认值：1’b0；*/
/*描述：。*/
#define I2C_COMMAND5_DONE    (BIT(31))
#define I2C_COMMAND5_DONE_M  (BIT(31))
#define I2C_COMMAND5_DONE_V  0x1
#define I2C_COMMAND5_DONE_S  31
/* I2C_COMMAND5:R/W；比特位置：[13:0]；默认值：14'b0；*/
/*描述：。*/
#define I2C_COMMAND5    0x00003FFF
#define I2C_COMMAND5_M  ((I2C_COMMAND5_V)<<(I2C_COMMAND5_S))
#define I2C_COMMAND5_V  0x3FFF
#define I2C_COMMAND5_S  0

#define I2C_COMD6_REG(i)          (REG_I2C_BASE(i) + 0x70)
/* I2C_COMMAND6_DONE:R/W/SS；位位置：[31]；默认值：1’b0；*/
/*描述：。*/
#define I2C_COMMAND6_DONE    (BIT(31))
#define I2C_COMMAND6_DONE_M  (BIT(31))
#define I2C_COMMAND6_DONE_V  0x1
#define I2C_COMMAND6_DONE_S  31
/* I2C_COMMAND6:R/W；比特位置：[13:0]；默认值：14'b0；*/
/*描述：。*/
#define I2C_COMMAND6    0x00003FFF
#define I2C_COMMAND6_M  ((I2C_COMMAND6_V)<<(I2C_COMMAND6_S))
#define I2C_COMMAND6_V  0x3FFF
#define I2C_COMMAND6_S  0

#define I2C_COMD7_REG(i)          (REG_I2C_BASE(i) + 0x74)
/* I2C_COMMAND7_DONE:R/W/SS；位位置：[31]；默认值：1’b0；*/
/*描述：。*/
#define I2C_COMMAND7_DONE    (BIT(31))
#define I2C_COMMAND7_DONE_M  (BIT(31))
#define I2C_COMMAND7_DONE_V  0x1
#define I2C_COMMAND7_DONE_S  31
/* I2C_COMMAND7:R/W；比特位置：[13:0]；默认值：14'b0；*/
/*描述：。*/
#define I2C_COMMAND7    0x00003FFF
#define I2C_COMMAND7_M  ((I2C_COMMAND7_V)<<(I2C_COMMAND7_S))
#define I2C_COMMAND7_V  0x3FFF
#define I2C_COMMAND7_S  0

#define I2C_SCL_ST_TIME_OUT_REG(i)          (REG_I2C_BASE(i) + 0x78)
/* I2C_SCL_ST_TO_REG:R/W；位位置：[4:0]；默认值：5’h10；*/
/*描述：不超过23。*/
#define I2C_SCL_ST_TO_REG    0x0000001F
#define I2C_SCL_ST_TO_REG_M  ((I2C_SCL_ST_TO_REG_V)<<(I2C_SCL_ST_TO_REG_S))
#define I2C_SCL_ST_TO_REG_V  0x1F
#define I2C_SCL_ST_TO_REG_S  0

#define I2C_SCL_MAIN_ST_TIME_OUT_REG(i)          (REG_I2C_BASE(i) + 0x7C)
/* I2C_SCL_MAIN_ST_TO_REG:R/W；位位置：[4:0]；默认值：5’h10；*/
/*描述：不超过23。*/
#define I2C_SCL_MAIN_ST_TO_REG    0x0000001F
#define I2C_SCL_MAIN_ST_TO_REG_M  ((I2C_SCL_MAIN_ST_TO_REG_V)<<(I2C_SCL_MAIN_ST_TO_REG_S))
#define I2C_SCL_MAIN_ST_TO_REG_V  0x1F
#define I2C_SCL_MAIN_ST_TO_REG_S  0

#define I2C_SCL_SP_CONF_REG(i)          (REG_I2C_BASE(i) + 0x80)
/* I2C_SDA_d_EN:R/W；位位置：[7]；默认值：1’b0；*/
/*描述：。*/
#define I2C_SDA_PD_EN    (BIT(7))
#define I2C_SDA_PD_EN_M  (BIT(7))
#define I2C_SDA_PD_EN_V  0x1
#define I2C_SDA_PD_EN_S  7
/* I2C_SCL_PD_EN:R/W；位位置：[6]；默认值：1’b0；*/
/*描述：。*/
#define I2C_SCL_PD_EN    (BIT(6))
#define I2C_SCL_PD_EN_M  (BIT(6))
#define I2C_SCL_PD_EN_V  0x1
#define I2C_SCL_PD_EN_S  6
/* I2C_SCL_RST_SLV_NUM:R/W；比特位置：[5:1]；默认值：5’b0；*/
/*描述：。*/
#define I2C_SCL_RST_SLV_NUM    0x0000001F
#define I2C_SCL_RST_SLV_NUM_M  ((I2C_SCL_RST_SLV_NUM_V)<<(I2C_SCL_RST_SLV_NUM_S))
#define I2C_SCL_RST_SLV_NUM_V  0x1F
#define I2C_SCL_RST_SLV_NUM_S  1
/* I2C_SCL_RST_SLV_EN:R/W/SC；位位置：[0]；默认值：1’b0；*/
/*描述：。*/
#define I2C_SCL_RST_SLV_EN    (BIT(0))
#define I2C_SCL_RST_SLV_EN_M  (BIT(0))
#define I2C_SCL_RST_SLV_EN_V  0x1
#define I2C_SCL_RST_SLV_EN_S  0

#define I2C_SCL_STRETCH_CONF_REG(i)          (REG_I2C_BASE(i) + 0x84)
/* I2C_SLAVE_BYTE_ACK_LVL:R/W；位位置：[13]；默认值：1’b0；*/
/*描述：。*/
#define I2C_SLAVE_BYTE_ACK_LVL    (BIT(13))
#define I2C_SLAVE_BYTE_ACK_LVL_M  (BIT(13))
#define I2C_SLAVE_BYTE_ACK_LVL_V  0x1
#define I2C_SLAVE_BYTE_ACK_LVL_S  13
/* I2C_SLAVE_BYTE_ACK_CTL_EN:R/W；位位置：[12]；默认值：1’b0；*/
/*描述：。*/
#define I2C_SLAVE_BYTE_ACK_CTL_EN    (BIT(12))
#define I2C_SLAVE_BYTE_ACK_CTL_EN_M  (BIT(12))
#define I2C_SLAVE_BYTE_ACK_CTL_EN_V  0x1
#define I2C_SLAVE_BYTE_ACK_CTL_EN_S  12
/* I2C_SLAVE_SCL_STRETCH_CLR:WT；位位置：[11]；默认值：1’b0；*/
/*描述：。*/
#define I2C_SLAVE_SCL_STRETCH_CLR    (BIT(11))
#define I2C_SLAVE_SCL_STRETCH_CLR_M  (BIT(11))
#define I2C_SLAVE_SCL_STRETCH_CLR_V  0x1
#define I2C_SLAVE_SCL_STRETCH_CLR_S  11
/* I2C_SLAVE_SCL_STRETCH_EN:R/W；位位置：[10]；默认值：1’b0；*/
/*描述：。*/
#define I2C_SLAVE_SCL_STRETCH_EN    (BIT(10))
#define I2C_SLAVE_SCL_STRETCH_EN_M  (BIT(10))
#define I2C_SLAVE_SCL_STRETCH_EN_V  0x1
#define I2C_SLAVE_SCL_STRETCH_EN_S  10
/* I2C_STRETCH_PROTECT_NUM:R/W；位位置：[9:0]；默认值：10'b0；*/
/*描述：。*/
#define I2C_STRETCH_PROTECT_NUM    0x000003FF
#define I2C_STRETCH_PROTECT_NUM_M  ((I2C_STRETCH_PROTECT_NUM_V)<<(I2C_STRETCH_PROTECT_NUM_S))
#define I2C_STRETCH_PROTECT_NUM_V  0x3FF
#define I2C_STRETCH_PROTECT_NUM_S  0

#define I2C_DATE_REG(i)          (REG_I2C_BASE(i) + 0xF8)
/* I2C_DATE:R/W；位位置：[31:0]；默认值：32'h20070201；*/
/*描述：。*/
#define I2C_DATE    0xFFFFFFFF
#define I2C_DATE_M  ((I2C_DATE_V)<<(I2C_DATE_S))
#define I2C_DATE_V  0xFFFFFFFF
#define I2C_DATE_S  0

#define I2C_TXFIFO_START_ADDR_REG(i)          (REG_I2C_BASE(i) + 0x100)

#define I2C_RXFIFO_START_ADDR_REG(i)          (REG_I2C_BASE(i) + 0x180)


#ifdef __cplusplus
}
#endif



#endif /*_SOC_I2C_REG_H_ */

