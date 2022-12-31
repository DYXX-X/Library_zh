// 版权所有2017-2018 Espressif Systems（上海）私人有限公司
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
#ifndef _SOC_I2S_REG_H_
#define _SOC_I2S_REG_H_


#ifdef __cplusplus
extern "C" {
#endif
#include "soc.h"
#define I2S_CONF_REG(i)          (REG_I2S_BASE(i) + 0x0008)
/* I2S_RX_RESET_ST:RO；位位置：[29]；默认值：1’b0；*/
/*说明：*/
#define I2S_RX_RESET_ST  (BIT(29))
#define I2S_RX_RESET_ST_M  (BIT(29))
#define I2S_RX_RESET_ST_V  0x1
#define I2S_RX_RESET_ST_S  29
/* I2S_RX_BIG_ENDIAN:R/W；位位置：[28]；默认值：1’b0；*/
/*说明：*/
#define I2S_RX_BIG_ENDIAN  (BIT(28))
#define I2S_RX_BIG_ENDIAN_M  (BIT(28))
#define I2S_RX_BIG_ENDIAN_V  0x1
#define I2S_RX_BIG_ENDIAN_S  28
/* I2S_TX_BIG_ENDIAN:R/W；位位置：[27]；默认值：1’b0；*/
/*说明：*/
#define I2S_TX_BIG_ENDIAN  (BIT(27))
#define I2S_TX_BIG_ENDIAN_M  (BIT(27))
#define I2S_TX_BIG_ENDIAN_V  0x1
#define I2S_TX_BIG_ENDIAN_S  27
/* I2S_PRE_REQ_EN:R/W；位位置：[26]；默认值：1’b0；*/
/*description:设置此位以使i2s能够更早地准备数据*/
#define I2S_PRE_REQ_EN  (BIT(26))
#define I2S_PRE_REQ_EN_M  (BIT(26))
#define I2S_PRE_REQ_EN_V  0x1
#define I2S_PRE_REQ_EN_S  26
/* I2S_RX_DMA_EQUAL:R/W；位位置：[25]；默认值：1’b0；*/
/*描述：1：左通道的数据等于右通道的数据*/
#define I2S_RX_DMA_EQUAL  (BIT(25))
#define I2S_RX_DMA_EQUAL_M  (BIT(25))
#define I2S_RX_DMA_EQUAL_V  0x1
#define I2S_RX_DMA_EQUAL_S  25
/* I2S_TX_DMA_EQUAL:R/W；位位置：[24]；默认值：1’b0；*/
/*描述：1：左通道的数据等于右通道的数据*/
#define I2S_TX_DMA_EQUAL  (BIT(24))
#define I2S_TX_DMA_EQUAL_M  (BIT(24))
#define I2S_TX_DMA_EQUAL_V  0x1
#define I2S_TX_DMA_EQUAL_S  24
/* I2S_TX_RESET_ST:RO；位位置：[23]；默认值：1’b0；*/
/*描述：1:i2s_tx_reset不正常0:i2s_tx-reset正常*/
#define I2S_TX_RESET_ST  (BIT(23))
#define I2S_TX_RESET_ST_M  (BIT(23))
#define I2S_TX_RESET_ST_V  0x1
#define I2S_TX_RESET_ST_S  23
/* I2S_RX_FIFO_RESET_ST:RO；位位置：[22]；默认值：1’b0；*/
/*描述：1:i2s_rx_fifo重置不正常0:i2s_rx-fifo重置正常*/
#define I2S_RX_FIFO_RESET_ST  (BIT(22))
#define I2S_RX_FIFO_RESET_ST_M  (BIT(22))
#define I2S_RX_FIFO_RESET_ST_V  0x1
#define I2S_RX_FIFO_RESET_ST_S  22
/* I2S_TX_FIFO_RESET_ST:RO；位位置：[21]；默认值：1’b0；*/
/*描述：1:i2s_tx_fifo重置不正常0:i2s_tx_fifo_reset正常*/
#define I2S_TX_FIFO_RESET_ST  (BIT(21))
#define I2S_TX_FIFO_RESET_ST_M  (BIT(21))
#define I2S_TX_FIFO_RESET_ST_V  0x1
#define I2S_TX_FIFO_RESET_ST_S  21
/* I2S_SIG_LOOPBACK:R/W；位位置：[20]；默认值：1’b0；*/
/*描述：启用信号环回模式，发射器模块和接收器模块共享相同的WS和BCK信号。*/
#define I2S_SIG_LOOPBACK  (BIT(20))
#define I2S_SIG_LOOPBACK_M  (BIT(20))
#define I2S_SIG_LOOPBACK_V  0x1
#define I2S_SIG_LOOPBACK_S  20
/* I2S_RX_LSB_FIRST_DMA:R/W；位位置：[19]；默认值：1’b1；*/
/*描述：1:DMA/APB中的数据从低位转换*/
#define I2S_RX_LSB_FIRST_DMA  (BIT(19))
#define I2S_RX_LSB_FIRST_DMA_M  (BIT(19))
#define I2S_RX_LSB_FIRST_DMA_V  0x1
#define I2S_RX_LSB_FIRST_DMA_S  19
/* I2S_TX_LSB_FIRST_DMA:R/W；位位置：[18]；默认值：1’b1；*/
/*描述：1:DMA/APB中的数据从低位转换*/
#define I2S_TX_LSB_FIRST_DMA  (BIT(18))
#define I2S_TX_LSB_FIRST_DMA_M  (BIT(18))
#define I2S_TX_LSB_FIRST_DMA_V  0x1
#define I2S_TX_LSB_FIRST_DMA_S  18
/* I2S_RX_MSB_右：R/W；位位置：[17]；默认值：1’b0；*/
/*description:设置此位以将右通道数据置于接收FIFO中的MSB。*/
#define I2S_RX_MSB_RIGHT  (BIT(17))
#define I2S_RX_MSB_RIGHT_M  (BIT(17))
#define I2S_RX_MSB_RIGHT_V  0x1
#define I2S_RX_MSB_RIGHT_S  17
/* I2S_TX_MSB_RIGHT:R/W；位位置：[16]；默认值：1’b0；*/
/*description:设置此位以将右通道数据置于传输FIFO中的MSB。*/
#define I2S_TX_MSB_RIGHT  (BIT(16))
#define I2S_TX_MSB_RIGHT_M  (BIT(16))
#define I2S_TX_MSB_RIGHT_V  0x1
#define I2S_TX_MSB_RIGHT_S  16
/* I2S_RX单声道：R/W；位位置：[15]；默认值：1’b0；*/
/*description:设置此位以启用单声道模式下的接收器*/
#define I2S_RX_MONO  (BIT(15))
#define I2S_RX_MONO_M  (BIT(15))
#define I2S_RX_MONO_V  0x1
#define I2S_RX_MONO_S  15
/* I2S_TX_MONO:R/W；位位置：[14]；默认值：1’b0；*/
/*description:设置此位以启用单声道模式下的发射器*/
#define I2S_TX_MONO  (BIT(14))
#define I2S_TX_MONO_M  (BIT(14))
#define I2S_TX_MONO_V  0x1
#define I2S_TX_MONO_S  14
/* I2S_RX_SHORT_SYNC:R/W；位位置：[13]；默认值：1’b0；*/
/*description:设置此位以启用PCM标准模式下的接收器*/
#define I2S_RX_SHORT_SYNC  (BIT(13))
#define I2S_RX_SHORT_SYNC_M  (BIT(13))
#define I2S_RX_SHORT_SYNC_V  0x1
#define I2S_RX_SHORT_SYNC_S  13
/* I2S_TX_SHORT_SYNC:R/W；位位置：[12]；默认值：1’b0；*/
/*description:设置此位以启用PCM标准模式下的发射器*/
#define I2S_TX_SHORT_SYNC  (BIT(12))
#define I2S_TX_SHORT_SYNC_M  (BIT(12))
#define I2S_TX_SHORT_SYNC_V  0x1
#define I2S_TX_SHORT_SYNC_S  12
/* I2S_RX_MSB_SHIFT:R/W；位位置：[11]；默认值：1’b0；*/
/*description:设置此位以启用菲利普斯标准模式下的接收器*/
#define I2S_RX_MSB_SHIFT  (BIT(11))
#define I2S_RX_MSB_SHIFT_M  (BIT(11))
#define I2S_RX_MSB_SHIFT_V  0x1
#define I2S_RX_MSB_SHIFT_S  11
/* I2S_TX_MSB_SHIFT:R/W；位位置：[10]；默认值：1’b0；*/
/*description:设置此位以启用菲利普斯标准模式下的变送器*/
#define I2S_TX_MSB_SHIFT  (BIT(10))
#define I2S_TX_MSB_SHIFT_M  (BIT(10))
#define I2S_TX_MSB_SHIFT_V  0x1
#define I2S_TX_MSB_SHIFT_S  10
/* I2S_RX_RIGHT_FIRST:R/W；位位置：[9]；默认值：1’b1；*/
/*description:设置此位以首先接收右通道数据*/
#define I2S_RX_RIGHT_FIRST  (BIT(9))
#define I2S_RX_RIGHT_FIRST_M  (BIT(9))
#define I2S_RX_RIGHT_FIRST_V  0x1
#define I2S_RX_RIGHT_FIRST_S  9
/* I2S_TX_RIGHT_FIRST:R/W；位位置：[8]；默认值：1’b1；*/
/*description:设置此位以先传输右通道数据*/
#define I2S_TX_RIGHT_FIRST  (BIT(8))
#define I2S_TX_RIGHT_FIRST_M  (BIT(8))
#define I2S_TX_RIGHT_FIRST_V  0x1
#define I2S_TX_RIGHT_FIRST_S  8
/* I2S_RX_SLAVE-MOD:R/W；位位置：[7]；默认值：1’b0；*/
/*description:设置此位以启用从属接收器模式*/
#define I2S_RX_SLAVE_MOD  (BIT(7))
#define I2S_RX_SLAVE_MOD_M  (BIT(7))
#define I2S_RX_SLAVE_MOD_V  0x1
#define I2S_RX_SLAVE_MOD_S  7
/* I2S_TX_SLAVE_mode:R/W；位位置：[6]；默认值：1’b0；*/
/*description:设置此位以启用从发射机模式*/
#define I2S_TX_SLAVE_MOD  (BIT(6))
#define I2S_TX_SLAVE_MOD_M  (BIT(6))
#define I2S_TX_SLAVE_MOD_V  0x1
#define I2S_TX_SLAVE_MOD_S  6
/* I2S_RX启动：R/W；位位置：[5]；默认值：1’b0；*/
/*description:设置此位以开始接收数据*/
#define I2S_RX_START  (BIT(5))
#define I2S_RX_START_M  (BIT(5))
#define I2S_RX_START_V  0x1
#define I2S_RX_START_S  5
/* I2S_TX_START:R/W；位位置：[4]；默认值：1’b0；*/
/*description:设置此位以开始传输数据*/
#define I2S_TX_START  (BIT(4))
#define I2S_TX_START_M  (BIT(4))
#define I2S_TX_START_V  0x1
#define I2S_TX_START_S  4
/* I2S_RX_FIFO_RESET:WO；位位置：[3]；默认值：1’b0；*/
/*description:设置此位以重置rxFIFO*/
#define I2S_RX_FIFO_RESET  (BIT(3))
#define I2S_RX_FIFO_RESET_M  (BIT(3))
#define I2S_RX_FIFO_RESET_V  0x1
#define I2S_RX_FIFO_RESET_S  3
/* I2S_TX_FIFO_RESET:WO；位位置：[2]；默认值：1’b0；*/
/*description:设置此位以重置txFIFO*/
#define I2S_TX_FIFO_RESET  (BIT(2))
#define I2S_TX_FIFO_RESET_M  (BIT(2))
#define I2S_TX_FIFO_RESET_V  0x1
#define I2S_TX_FIFO_RESET_S  2
/* I2S_RX重置：WO；位位置：[1]；默认值：1’b0；*/
/*description:设置此位以重置接收器*/
#define I2S_RX_RESET  (BIT(1))
#define I2S_RX_RESET_M  (BIT(1))
#define I2S_RX_RESET_V  0x1
#define I2S_RX_RESET_S  1
/* I2S_TX_RESET:WO；位位置：[0]；默认值：1’b0；*/
/*description:设置此位重置变送器*/
#define I2S_TX_RESET  (BIT(0))
#define I2S_TX_RESET_M  (BIT(0))
#define I2S_TX_RESET_V  0x1
#define I2S_TX_RESET_S  0

#define I2S_INT_RAW_REG(i)          (REG_I2S_BASE(i) + 0x000c)
/* I2S_V_SYNC_INT_RAW:RO；位位置：[17]；默认值：1’b0；*/
/*description:i2s_v_sync_int中断的原始中断状态位*/
#define I2S_V_SYNC_INT_RAW  (BIT(17))
#define I2S_V_SYNC_INT_RAW_M  (BIT(17))
#define I2S_V_SYNC_INT_RAW_V  0x1
#define I2S_V_SYNC_INT_RAW_S  17
/* I2S_OUT_TOTAL_EOF_INT_RAW:RO；位位置：[16]；默认值：1’b0；*/
/*description:i2s_out_total_eof_int中断的原始中断状态位*/
#define I2S_OUT_TOTAL_EOF_INT_RAW  (BIT(16))
#define I2S_OUT_TOTAL_EOF_INT_RAW_M  (BIT(16))
#define I2S_OUT_TOTAL_EOF_INT_RAW_V  0x1
#define I2S_OUT_TOTAL_EOF_INT_RAW_S  16
/* I2S_IN_DSCR_EMPTY_INT_RAW:RO；位位置：[15]；默认值：1’b0；*/
/*description:i2s_in_dscr_empty_int中断的原始中断状态位*/
#define I2S_IN_DSCR_EMPTY_INT_RAW  (BIT(15))
#define I2S_IN_DSCR_EMPTY_INT_RAW_M  (BIT(15))
#define I2S_IN_DSCR_EMPTY_INT_RAW_V  0x1
#define I2S_IN_DSCR_EMPTY_INT_RAW_S  15
/* I2S_OUT_DSCR_ERR_INT_RAW:RO；位位置：[14]；默认值：1’b0；*/
/*description:i2s_out_dscr_err_int中断的原始中断状态位*/
#define I2S_OUT_DSCR_ERR_INT_RAW  (BIT(14))
#define I2S_OUT_DSCR_ERR_INT_RAW_M  (BIT(14))
#define I2S_OUT_DSCR_ERR_INT_RAW_V  0x1
#define I2S_OUT_DSCR_ERR_INT_RAW_S  14
/* I2S_IN_DSCR_ERR_INT_RAW:RO；位位置：[13]；默认值：1’b0；*/
/*description:i2s_in_dscr_err_int中断的原始中断状态位*/
#define I2S_IN_DSCR_ERR_INT_RAW  (BIT(13))
#define I2S_IN_DSCR_ERR_INT_RAW_M  (BIT(13))
#define I2S_IN_DSCR_ERR_INT_RAW_V  0x1
#define I2S_IN_DSCR_ERR_INT_RAW_S  13
/* I2S_OUT_EOF_INT_RAW:RO；位位置：[12]；默认值：1’b0；*/
/*description:i2s_out_eof_int中断的原始中断状态位*/
#define I2S_OUT_EOF_INT_RAW  (BIT(12))
#define I2S_OUT_EOF_INT_RAW_M  (BIT(12))
#define I2S_OUT_EOF_INT_RAW_V  0x1
#define I2S_OUT_EOF_INT_RAW_S  12
/* I2S_OUT_DONE_INT_RAW:RO；位位置：[11]；默认值：1’b0；*/
/*description:i2s_out_done_int中断的原始中断状态位*/
#define I2S_OUT_DONE_INT_RAW  (BIT(11))
#define I2S_OUT_DONE_INT_RAW_M  (BIT(11))
#define I2S_OUT_DONE_INT_RAW_V  0x1
#define I2S_OUT_DONE_INT_RAW_S  11
/* I2S_IN_ERR_EOF_INT_RAW:RO；位位置：[10]；默认值：1’b0；*/
/*description:不使用*/
#define I2S_IN_ERR_EOF_INT_RAW  (BIT(10))
#define I2S_IN_ERR_EOF_INT_RAW_M  (BIT(10))
#define I2S_IN_ERR_EOF_INT_RAW_V  0x1
#define I2S_IN_ERR_EOF_INT_RAW_S  10
/* I2S_IN_SUC_EOF_INT_RAW:RO；位位置：[9]；默认值：1’b0；*/
/*description:i2s_in_suc_eof_int中断的原始中断状态位*/
#define I2S_IN_SUC_EOF_INT_RAW  (BIT(9))
#define I2S_IN_SUC_EOF_INT_RAW_M  (BIT(9))
#define I2S_IN_SUC_EOF_INT_RAW_V  0x1
#define I2S_IN_SUC_EOF_INT_RAW_S  9
/* I2S_IN_DONE_INT_RAW:RO；位位置：[8]；默认值：1’b0；*/
/*description:i2s_in_done_int中断的原始中断状态位*/
#define I2S_IN_DONE_INT_RAW  (BIT(8))
#define I2S_IN_DONE_INT_RAW_M  (BIT(8))
#define I2S_IN_DONE_INT_RAW_V  0x1
#define I2S_IN_DONE_INT_RAW_S  8
/* I2S_TX_HUNG_INT_RAW:RO；位位置：[7]；默认值：1’b0；*/
/*description:i2s_tx_hung_int中断的原始中断状态位*/
#define I2S_TX_HUNG_INT_RAW  (BIT(7))
#define I2S_TX_HUNG_INT_RAW_M  (BIT(7))
#define I2S_TX_HUNG_INT_RAW_V  0x1
#define I2S_TX_HUNG_INT_RAW_S  7
/* I2S_RX-HUNG_INT_RAW:RO；位位置：[6]；默认值：1’b0；*/
/*description:i2s_rx_hung_int中断的原始中断状态位*/
#define I2S_RX_HUNG_INT_RAW  (BIT(6))
#define I2S_RX_HUNG_INT_RAW_M  (BIT(6))
#define I2S_RX_HUNG_INT_RAW_V  0x1
#define I2S_RX_HUNG_INT_RAW_S  6
/* I2S_TX_REMPTY_INT_RAW:RO；位位置：[5]；默认值：1’b0；*/
/*description:i2s_tx_rempty_int中断的原始中断状态位*/
#define I2S_TX_REMPTY_INT_RAW  (BIT(5))
#define I2S_TX_REMPTY_INT_RAW_M  (BIT(5))
#define I2S_TX_REMPTY_INT_RAW_V  0x1
#define I2S_TX_REMPTY_INT_RAW_S  5
/* I2S_TX_WFULL_INT_RAW:RO；位位置：[4]；默认值：1’b0；*/
/*description:i2s_tx_wfull_int中断的原始中断状态位*/
#define I2S_TX_WFULL_INT_RAW  (BIT(4))
#define I2S_TX_WFULL_INT_RAW_M  (BIT(4))
#define I2S_TX_WFULL_INT_RAW_V  0x1
#define I2S_TX_WFULL_INT_RAW_S  4
/* I2S_RX-REMPTY_INT_RAW:RO；位位置：[3]；默认值：1’b0；*/
/*description:i2s_rx_rempty_int中断的原始中断状态位*/
#define I2S_RX_REMPTY_INT_RAW  (BIT(3))
#define I2S_RX_REMPTY_INT_RAW_M  (BIT(3))
#define I2S_RX_REMPTY_INT_RAW_V  0x1
#define I2S_RX_REMPTY_INT_RAW_S  3
/* I2S_RX_wull_INT_RAW:RO；位位置：[2]；默认值：1’b0；*/
/*description:i2s_rx_wull_int中断的原始中断状态位*/
#define I2S_RX_WFULL_INT_RAW  (BIT(2))
#define I2S_RX_WFULL_INT_RAW_M  (BIT(2))
#define I2S_RX_WFULL_INT_RAW_V  0x1
#define I2S_RX_WFULL_INT_RAW_S  2
/* I2S_TX_PUT_DATA_INT_RAW:RO；位位置：[1]；默认值：1’b0；*/
/*description:i2s_tx_put_data_int中断的原始中断状态位*/
#define I2S_TX_PUT_DATA_INT_RAW  (BIT(1))
#define I2S_TX_PUT_DATA_INT_RAW_M  (BIT(1))
#define I2S_TX_PUT_DATA_INT_RAW_V  0x1
#define I2S_TX_PUT_DATA_INT_RAW_S  1
/* I2S_RX_TAKE_DATA_INT_RAW:RO；位位置：[0]；默认值：1’b0；*/
/*description:i2s_rx_take_data_int中断的原始中断状态位*/
#define I2S_RX_TAKE_DATA_INT_RAW  (BIT(0))
#define I2S_RX_TAKE_DATA_INT_RAW_M  (BIT(0))
#define I2S_RX_TAKE_DATA_INT_RAW_V  0x1
#define I2S_RX_TAKE_DATA_INT_RAW_S  0

#define I2S_INT_ST_REG(i)          (REG_I2S_BASE(i) + 0x0010)
/* I2S_V_SYNC_INT_ST:RO；位位置：[17]；默认值：1’b0；*/
/*description:i2s_v_sync_int中断的屏蔽中断状态位*/
#define I2S_V_SYNC_INT_ST  (BIT(17))
#define I2S_V_SYNC_INT_ST_M  (BIT(17))
#define I2S_V_SYNC_INT_ST_V  0x1
#define I2S_V_SYNC_INT_ST_S  17
/* I2S_OUT_TOTAL_EOF_INT_ST:RO；位位置：[16]；默认值：1’b0；*/
/*description:i2s_out_total_eof_int中断的屏蔽中断状态位*/
#define I2S_OUT_TOTAL_EOF_INT_ST  (BIT(16))
#define I2S_OUT_TOTAL_EOF_INT_ST_M  (BIT(16))
#define I2S_OUT_TOTAL_EOF_INT_ST_V  0x1
#define I2S_OUT_TOTAL_EOF_INT_ST_S  16
/* I2S_IN_DSCR_EMPTY_INT_ST:RO；位位置：[15]；默认值：1’b0；*/
/*description:i2s_in_dscr_empty_int中断的屏蔽中断状态位*/
#define I2S_IN_DSCR_EMPTY_INT_ST  (BIT(15))
#define I2S_IN_DSCR_EMPTY_INT_ST_M  (BIT(15))
#define I2S_IN_DSCR_EMPTY_INT_ST_V  0x1
#define I2S_IN_DSCR_EMPTY_INT_ST_S  15
/* I2S_OUT_DSCR_ERR_INT_ST:RO；位位置：[14]；默认值：1’b0；*/
/*description:i2s_out_dscr_err_int中断的屏蔽中断状态位*/
#define I2S_OUT_DSCR_ERR_INT_ST  (BIT(14))
#define I2S_OUT_DSCR_ERR_INT_ST_M  (BIT(14))
#define I2S_OUT_DSCR_ERR_INT_ST_V  0x1
#define I2S_OUT_DSCR_ERR_INT_ST_S  14
/* I2S_IN_DSCR_ERR_INT_ST:RO；位位置：[13]；默认值：1’b0；*/
/*description:i2s_in_dscr_err_int中断的屏蔽中断状态位*/
#define I2S_IN_DSCR_ERR_INT_ST  (BIT(13))
#define I2S_IN_DSCR_ERR_INT_ST_M  (BIT(13))
#define I2S_IN_DSCR_ERR_INT_ST_V  0x1
#define I2S_IN_DSCR_ERR_INT_ST_S  13
/* I2S_OUT_EOF_INT_ST:RO；位位置：[12]；默认值：1’b0；*/
/*description:i2s_out_eof_int中断的屏蔽中断状态位*/
#define I2S_OUT_EOF_INT_ST  (BIT(12))
#define I2S_OUT_EOF_INT_ST_M  (BIT(12))
#define I2S_OUT_EOF_INT_ST_V  0x1
#define I2S_OUT_EOF_INT_ST_S  12
/* I2S_OUT_DONE_INT_ST:RO；位位置：[11]；默认值：1’b0；*/
/*description:i2s_out_done_int中断的屏蔽中断状态位*/
#define I2S_OUT_DONE_INT_ST  (BIT(11))
#define I2S_OUT_DONE_INT_ST_M  (BIT(11))
#define I2S_OUT_DONE_INT_ST_V  0x1
#define I2S_OUT_DONE_INT_ST_S  11
/* I2S_IN_ERR_EOF_INT_ST:RO；位位置：[10]；默认值：1’b0；*/
/*description:不使用*/
#define I2S_IN_ERR_EOF_INT_ST  (BIT(10))
#define I2S_IN_ERR_EOF_INT_ST_M  (BIT(10))
#define I2S_IN_ERR_EOF_INT_ST_V  0x1
#define I2S_IN_ERR_EOF_INT_ST_S  10
/* I2S_IN_SUC_EOF_INT_ST:RO；位位置：[9]；默认值：1’b0；*/
/*description:i2s_in_suc_eof_int中断的屏蔽中断状态位*/
#define I2S_IN_SUC_EOF_INT_ST  (BIT(9))
#define I2S_IN_SUC_EOF_INT_ST_M  (BIT(9))
#define I2S_IN_SUC_EOF_INT_ST_V  0x1
#define I2S_IN_SUC_EOF_INT_ST_S  9
/* I2S_IN_DONE_INT_ST:RO；位位置：[8]；默认值：1’b0；*/
/*description:i2s_in_done_int中断的屏蔽中断状态位*/
#define I2S_IN_DONE_INT_ST  (BIT(8))
#define I2S_IN_DONE_INT_ST_M  (BIT(8))
#define I2S_IN_DONE_INT_ST_V  0x1
#define I2S_IN_DONE_INT_ST_S  8
/* I2S_TX_HUNG_INT_ST:RO；位位置：[7]；默认值：1’b0；*/
/*description:i2s_tx_hung_int中断的屏蔽中断状态位*/
#define I2S_TX_HUNG_INT_ST  (BIT(7))
#define I2S_TX_HUNG_INT_ST_M  (BIT(7))
#define I2S_TX_HUNG_INT_ST_V  0x1
#define I2S_TX_HUNG_INT_ST_S  7
/* I2S_RX-HUNG_INT_ST:RO；位位置：[6]；默认值：1’b0；*/
/*description:i2s_rx_hung_int中断的屏蔽中断状态位*/
#define I2S_RX_HUNG_INT_ST  (BIT(6))
#define I2S_RX_HUNG_INT_ST_M  (BIT(6))
#define I2S_RX_HUNG_INT_ST_V  0x1
#define I2S_RX_HUNG_INT_ST_S  6
/* I2S_TX_REMPTY_INT_ST:RO；位位置：[5]；默认值：1’b0；*/
/*description:i2s_tx_rempty_int中断的屏蔽中断状态位*/
#define I2S_TX_REMPTY_INT_ST  (BIT(5))
#define I2S_TX_REMPTY_INT_ST_M  (BIT(5))
#define I2S_TX_REMPTY_INT_ST_V  0x1
#define I2S_TX_REMPTY_INT_ST_S  5
/* I2S_TX_WFULL_INT_ST:RO；位位置：[4]；默认值：1’b0；*/
/*description:i2s_tx_wfull_int中断的屏蔽中断状态位*/
#define I2S_TX_WFULL_INT_ST  (BIT(4))
#define I2S_TX_WFULL_INT_ST_M  (BIT(4))
#define I2S_TX_WFULL_INT_ST_V  0x1
#define I2S_TX_WFULL_INT_ST_S  4
/* I2S_RX_REMPTY_INT_ST:RO；位位置：[3]；默认值：1’b0；*/
/*description:i2s_rx_rempty_int中断的屏蔽中断状态位*/
#define I2S_RX_REMPTY_INT_ST  (BIT(3))
#define I2S_RX_REMPTY_INT_ST_M  (BIT(3))
#define I2S_RX_REMPTY_INT_ST_V  0x1
#define I2S_RX_REMPTY_INT_ST_S  3
/* I2S_RX_wull_INT_ST:RO；位位置：[2]；默认值：1’b0；*/
/*description:i2s_rx_wull_int中断的屏蔽中断状态位*/
#define I2S_RX_WFULL_INT_ST  (BIT(2))
#define I2S_RX_WFULL_INT_ST_M  (BIT(2))
#define I2S_RX_WFULL_INT_ST_V  0x1
#define I2S_RX_WFULL_INT_ST_S  2
/* I2S_TX_PUT_DATA_INT_ST:RO；位位置：[1]；默认值：1’b0；*/
/*description:i2s_tx_put_data_int中断的屏蔽中断状态位*/
#define I2S_TX_PUT_DATA_INT_ST  (BIT(1))
#define I2S_TX_PUT_DATA_INT_ST_M  (BIT(1))
#define I2S_TX_PUT_DATA_INT_ST_V  0x1
#define I2S_TX_PUT_DATA_INT_ST_S  1
/* I2S_RX_TAKE_DATA_INT_ST:RO；位位置：[0]；默认值：1’b0；*/
/*description:i2s_rx_take_data_int中断的屏蔽中断状态位*/
#define I2S_RX_TAKE_DATA_INT_ST  (BIT(0))
#define I2S_RX_TAKE_DATA_INT_ST_M  (BIT(0))
#define I2S_RX_TAKE_DATA_INT_ST_V  0x1
#define I2S_RX_TAKE_DATA_INT_ST_S  0

#define I2S_INT_ENA_REG(i)          (REG_I2S_BASE(i) + 0x0014)
/* I2S_V_SYNC_INT_ENA:R/W；位位置：[17]；默认值：1’b0；*/
/*description:i2s_v_sync_int中断的中断启用位*/
#define I2S_V_SYNC_INT_ENA  (BIT(17))
#define I2S_V_SYNC_INT_ENA_M  (BIT(17))
#define I2S_V_SYNC_INT_ENA_V  0x1
#define I2S_V_SYNC_INT_ENA_S  17
/* I2S_OUT_TOTAL_EOF_INT_ENA:R/W；位位置：[16]；默认值：1’b0；*/
/*description:i2s_out_total_eof_int中断的中断启用位*/
#define I2S_OUT_TOTAL_EOF_INT_ENA  (BIT(16))
#define I2S_OUT_TOTAL_EOF_INT_ENA_M  (BIT(16))
#define I2S_OUT_TOTAL_EOF_INT_ENA_V  0x1
#define I2S_OUT_TOTAL_EOF_INT_ENA_S  16
/* I2S_IN_DSCR_EMPTY_INT_ENA:R/W；位位置：[15]；默认值：1’b0；*/
/*description:i2s_in_dscr_empty_int中断的中断启用位*/
#define I2S_IN_DSCR_EMPTY_INT_ENA  (BIT(15))
#define I2S_IN_DSCR_EMPTY_INT_ENA_M  (BIT(15))
#define I2S_IN_DSCR_EMPTY_INT_ENA_V  0x1
#define I2S_IN_DSCR_EMPTY_INT_ENA_S  15
/* I2S_OUT_DSCR_ERR_INT_ENA:R/W；位位置：[14]；默认值：1’b0；*/
/*description:i2s_out_dscr_err_int中断的中断启用位*/
#define I2S_OUT_DSCR_ERR_INT_ENA  (BIT(14))
#define I2S_OUT_DSCR_ERR_INT_ENA_M  (BIT(14))
#define I2S_OUT_DSCR_ERR_INT_ENA_V  0x1
#define I2S_OUT_DSCR_ERR_INT_ENA_S  14
/* I2S_IN_DSCR_ERR_INT_ENA:R/W；位位置：[13]；默认值：1’b0；*/
/*description:i2s_in_dscr_err_int中断的中断启用位*/
#define I2S_IN_DSCR_ERR_INT_ENA  (BIT(13))
#define I2S_IN_DSCR_ERR_INT_ENA_M  (BIT(13))
#define I2S_IN_DSCR_ERR_INT_ENA_V  0x1
#define I2S_IN_DSCR_ERR_INT_ENA_S  13
/* I2S_OUT_EOF_INT_ENA：R/W；位位置：[12]；默认值：1’b0；*/
/*description:i2s_out_eof_int中断的中断启用位*/
#define I2S_OUT_EOF_INT_ENA  (BIT(12))
#define I2S_OUT_EOF_INT_ENA_M  (BIT(12))
#define I2S_OUT_EOF_INT_ENA_V  0x1
#define I2S_OUT_EOF_INT_ENA_S  12
/* I2S_OUT_DONE_INT_ENA:R/W；位位置：[11]；默认值：1’b0；*/
/*description:i2s_out_done_int中断的中断启用位*/
#define I2S_OUT_DONE_INT_ENA  (BIT(11))
#define I2S_OUT_DONE_INT_ENA_M  (BIT(11))
#define I2S_OUT_DONE_INT_ENA_V  0x1
#define I2S_OUT_DONE_INT_ENA_S  11
/* I2S_IN_ERR_EOF_INT_ENA:R/W；位位置：[10]；默认值：1’b0；*/
/*description:不使用*/
#define I2S_IN_ERR_EOF_INT_ENA  (BIT(10))
#define I2S_IN_ERR_EOF_INT_ENA_M  (BIT(10))
#define I2S_IN_ERR_EOF_INT_ENA_V  0x1
#define I2S_IN_ERR_EOF_INT_ENA_S  10
/* I2S_IN_SUC_EOF_INT_ENA:R/W；位位置：[9]；默认值：1’b0；*/
/*description:i2s_in_suc_eof_int中断的中断启用位*/
#define I2S_IN_SUC_EOF_INT_ENA  (BIT(9))
#define I2S_IN_SUC_EOF_INT_ENA_M  (BIT(9))
#define I2S_IN_SUC_EOF_INT_ENA_V  0x1
#define I2S_IN_SUC_EOF_INT_ENA_S  9
/* I2S_IN_DONE_INT_ENA:R/W；位位置：[8]；默认值：1’b0；*/
/*description:i2s_in_done_int中断的中断启用位*/
#define I2S_IN_DONE_INT_ENA  (BIT(8))
#define I2S_IN_DONE_INT_ENA_M  (BIT(8))
#define I2S_IN_DONE_INT_ENA_V  0x1
#define I2S_IN_DONE_INT_ENA_S  8
/* I2S_TX_HUNG_INT_ENA:R/W；位位置：[7]；默认值：1’b0；*/
/*description:i2s_tx_hung_int中断的中断启用位*/
#define I2S_TX_HUNG_INT_ENA  (BIT(7))
#define I2S_TX_HUNG_INT_ENA_M  (BIT(7))
#define I2S_TX_HUNG_INT_ENA_V  0x1
#define I2S_TX_HUNG_INT_ENA_S  7
/* I2S_RX-HUNG_INT_ENA:R/W；位位置：[6]；默认值：1’b0；*/
/*description:i2s_rx_hung_int中断的中断启用位*/
#define I2S_RX_HUNG_INT_ENA  (BIT(6))
#define I2S_RX_HUNG_INT_ENA_M  (BIT(6))
#define I2S_RX_HUNG_INT_ENA_V  0x1
#define I2S_RX_HUNG_INT_ENA_S  6
/* I2S_TX_REMPTY_INT_ENA:R/W；位位置：[5]；默认值：1’b0；*/
/*description:i2s_tx_rempty_int中断的中断启用位*/
#define I2S_TX_REMPTY_INT_ENA  (BIT(5))
#define I2S_TX_REMPTY_INT_ENA_M  (BIT(5))
#define I2S_TX_REMPTY_INT_ENA_V  0x1
#define I2S_TX_REMPTY_INT_ENA_S  5
/* I2S_TX_WFULL_INT_ENA:R/W；位位置：[4]；默认值：1’b0；*/
/*description:i2s_tx_wfull_int中断的中断启用位*/
#define I2S_TX_WFULL_INT_ENA  (BIT(4))
#define I2S_TX_WFULL_INT_ENA_M  (BIT(4))
#define I2S_TX_WFULL_INT_ENA_V  0x1
#define I2S_TX_WFULL_INT_ENA_S  4
/* I2S_RX-REMPTY_INT_ENA:R/W；位位置：[3]；默认值：1’b0；*/
/*description:i2s_rx_rempty_int中断的中断启用位*/
#define I2S_RX_REMPTY_INT_ENA  (BIT(3))
#define I2S_RX_REMPTY_INT_ENA_M  (BIT(3))
#define I2S_RX_REMPTY_INT_ENA_V  0x1
#define I2S_RX_REMPTY_INT_ENA_S  3
/* I2S_RX_wull_INT_ENA:R/W；位位置：[2]；默认值：1’b0；*/
/*description:i2s_rx_wull_int中断的中断启用位*/
#define I2S_RX_WFULL_INT_ENA  (BIT(2))
#define I2S_RX_WFULL_INT_ENA_M  (BIT(2))
#define I2S_RX_WFULL_INT_ENA_V  0x1
#define I2S_RX_WFULL_INT_ENA_S  2
/* I2S_TX_PUT_DATA_INT_ENA：R/W；位位置：[1]；默认值：1’b0；*/
/*description:i2s_tx_put_data_int中断的中断启用位*/
#define I2S_TX_PUT_DATA_INT_ENA  (BIT(1))
#define I2S_TX_PUT_DATA_INT_ENA_M  (BIT(1))
#define I2S_TX_PUT_DATA_INT_ENA_V  0x1
#define I2S_TX_PUT_DATA_INT_ENA_S  1
/* I2S_RX_TAKE_DATA_INT_ENA:R/W；位位置：[0]；默认值：1’b0；*/
/*description:i2s_rx_take_data_int中断的中断启用位*/
#define I2S_RX_TAKE_DATA_INT_ENA  (BIT(0))
#define I2S_RX_TAKE_DATA_INT_ENA_M  (BIT(0))
#define I2S_RX_TAKE_DATA_INT_ENA_V  0x1
#define I2S_RX_TAKE_DATA_INT_ENA_S  0

#define I2S_INT_CLR_REG(i)          (REG_I2S_BASE(i) + 0x0018)
/* I2S_V_SYNC_INT_CLR:WO；位位置：[17]；默认值：1’b0；*/
/*description:设置此位以清除i2s_v_sync_int中断*/
#define I2S_V_SYNC_INT_CLR  (BIT(17))
#define I2S_V_SYNC_INT_CLR_M  (BIT(17))
#define I2S_V_SYNC_INT_CLR_V  0x1
#define I2S_V_SYNC_INT_CLR_S  17
/* I2S_OUT_TOTAL_EOF_INT_CLR:WO；位位置：[16]；默认值：1’b0；*/
/*description:设置此位以清除i2s_out_total_eof_int中断*/
#define I2S_OUT_TOTAL_EOF_INT_CLR  (BIT(16))
#define I2S_OUT_TOTAL_EOF_INT_CLR_M  (BIT(16))
#define I2S_OUT_TOTAL_EOF_INT_CLR_V  0x1
#define I2S_OUT_TOTAL_EOF_INT_CLR_S  16
/* I2S_IN_DSCR_EMPTY_INT_CLR:WO；位位置：[15]；默认值：1’b0；*/
/*description:设置此位以清除i2s_in_dscr_empty_int中断*/
#define I2S_IN_DSCR_EMPTY_INT_CLR  (BIT(15))
#define I2S_IN_DSCR_EMPTY_INT_CLR_M  (BIT(15))
#define I2S_IN_DSCR_EMPTY_INT_CLR_V  0x1
#define I2S_IN_DSCR_EMPTY_INT_CLR_S  15
/* I2S_OUT_DSCR_ERR_INT_CLR:WO；位位置：[14]；默认值：1’b0；*/
/*description:设置此位以清除i2s_out_dscr_err_int中断*/
#define I2S_OUT_DSCR_ERR_INT_CLR  (BIT(14))
#define I2S_OUT_DSCR_ERR_INT_CLR_M  (BIT(14))
#define I2S_OUT_DSCR_ERR_INT_CLR_V  0x1
#define I2S_OUT_DSCR_ERR_INT_CLR_S  14
/* I2S_IN_DSCR_ERR_INT_CLR:WO；位位置：[13]；默认值：1’b0；*/
/*description:设置此位以清除i2s_in_dscr_err_int中断*/
#define I2S_IN_DSCR_ERR_INT_CLR  (BIT(13))
#define I2S_IN_DSCR_ERR_INT_CLR_M  (BIT(13))
#define I2S_IN_DSCR_ERR_INT_CLR_V  0x1
#define I2S_IN_DSCR_ERR_INT_CLR_S  13
/* I2S_OUT_EOF_INT_CLR:WO；位位置：[12]；默认值：1’b0；*/
/*description:设置此位以清除i2s_out_eof_int中断*/
#define I2S_OUT_EOF_INT_CLR  (BIT(12))
#define I2S_OUT_EOF_INT_CLR_M  (BIT(12))
#define I2S_OUT_EOF_INT_CLR_V  0x1
#define I2S_OUT_EOF_INT_CLR_S  12
/* I2S_OUT_DONE_INT_CLR:WO；位位置：[11]；默认值：1’b0；*/
/*description:设置此位以清除i2s_out_done_int中断*/
#define I2S_OUT_DONE_INT_CLR  (BIT(11))
#define I2S_OUT_DONE_INT_CLR_M  (BIT(11))
#define I2S_OUT_DONE_INT_CLR_V  0x1
#define I2S_OUT_DONE_INT_CLR_S  11
/* I2S_IN_ERR_EOF_INT_CLR:WO；位位置：[10]；默认值：1’b0；*/
/*description:不使用*/
#define I2S_IN_ERR_EOF_INT_CLR  (BIT(10))
#define I2S_IN_ERR_EOF_INT_CLR_M  (BIT(10))
#define I2S_IN_ERR_EOF_INT_CLR_V  0x1
#define I2S_IN_ERR_EOF_INT_CLR_S  10
/* I2S_IN_SUC_EOF_INT_CLR:WO；位位置：[9]；默认值：1’b0；*/
/*description:设置此位以清除i2s_in_suc_eof_int中断*/
#define I2S_IN_SUC_EOF_INT_CLR  (BIT(9))
#define I2S_IN_SUC_EOF_INT_CLR_M  (BIT(9))
#define I2S_IN_SUC_EOF_INT_CLR_V  0x1
#define I2S_IN_SUC_EOF_INT_CLR_S  9
/* I2S_IN_DONE_INT_CLR:WO；位位置：[8]；默认值：1’b0；*/
/*description:设置此位以清除i2s_in_done_int中断*/
#define I2S_IN_DONE_INT_CLR  (BIT(8))
#define I2S_IN_DONE_INT_CLR_M  (BIT(8))
#define I2S_IN_DONE_INT_CLR_V  0x1
#define I2S_IN_DONE_INT_CLR_S  8
/* I2S_TX_HUNG_INT_CLR:WO；位位置：[7]；默认值：1’b0；*/
/*description:设置此位以清除i2s_tx_hung_int中断*/
#define I2S_TX_HUNG_INT_CLR  (BIT(7))
#define I2S_TX_HUNG_INT_CLR_M  (BIT(7))
#define I2S_TX_HUNG_INT_CLR_V  0x1
#define I2S_TX_HUNG_INT_CLR_S  7
/* I2S_RX-HUNG_INT_CLR:WO；位位置：[6]；默认值：1’b0；*/
/*description:设置此位以清除i2s_rx_hung_int中断*/
#define I2S_RX_HUNG_INT_CLR  (BIT(6))
#define I2S_RX_HUNG_INT_CLR_M  (BIT(6))
#define I2S_RX_HUNG_INT_CLR_V  0x1
#define I2S_RX_HUNG_INT_CLR_S  6
/* I2S_TX_REMPTY_INT_CLR:WO；位位置：[5]；默认值：1’b0；*/
/*description:设置此位以清除i2s_tx_rempty_int中断*/
#define I2S_TX_REMPTY_INT_CLR  (BIT(5))
#define I2S_TX_REMPTY_INT_CLR_M  (BIT(5))
#define I2S_TX_REMPTY_INT_CLR_V  0x1
#define I2S_TX_REMPTY_INT_CLR_S  5
/* I2S_TX_WFULL_INT_CLR:WO；位位置：[4]；默认值：1’b0；*/
/*description:设置此位以清除i2s_tx_wfull_int中断*/
#define I2S_TX_WFULL_INT_CLR  (BIT(4))
#define I2S_TX_WFULL_INT_CLR_M  (BIT(4))
#define I2S_TX_WFULL_INT_CLR_V  0x1
#define I2S_TX_WFULL_INT_CLR_S  4
/* I2S_RX-REMPTY_INT_CLR:WO；位位置：[3]；默认值：1’b0；*/
/*description:设置此位以清除i2s_rx_rempty_int中断*/
#define I2S_RX_REMPTY_INT_CLR  (BIT(3))
#define I2S_RX_REMPTY_INT_CLR_M  (BIT(3))
#define I2S_RX_REMPTY_INT_CLR_V  0x1
#define I2S_RX_REMPTY_INT_CLR_S  3
/* I2S_RX_wull_INT_CLR:WO；位位置：[2]；默认值：1’b0；*/
/*description:设置此位以清除i2s_rx_wull_int中断*/
#define I2S_RX_WFULL_INT_CLR  (BIT(2))
#define I2S_RX_WFULL_INT_CLR_M  (BIT(2))
#define I2S_RX_WFULL_INT_CLR_V  0x1
#define I2S_RX_WFULL_INT_CLR_S  2
/* I2S_PUT_DATA_INT_CLR:WO；位位置：[1]；默认值：1’b0；*/
/*description:设置此位以清除i2s_tx_put_data_int中断*/
#define I2S_PUT_DATA_INT_CLR  (BIT(1))
#define I2S_PUT_DATA_INT_CLR_M  (BIT(1))
#define I2S_PUT_DATA_INT_CLR_V  0x1
#define I2S_PUT_DATA_INT_CLR_S  1
/* I2S_TAKE_DATA_INT_CLR:WO；位位置：[0]；默认值：1’b0；*/
/*description:设置此位以清除i2s_rx_take_data_int中断*/
#define I2S_TAKE_DATA_INT_CLR  (BIT(0))
#define I2S_TAKE_DATA_INT_CLR_M  (BIT(0))
#define I2S_TAKE_DATA_INT_CLR_V  0x1
#define I2S_TAKE_DATA_INT_CLR_S  0

#define I2S_TIMING_REG(i)          (REG_I2S_BASE(i) + 0x001c)
/* I2S_TX_BCK_IN_INV:R/W；位位置：[24]；默认值：1’b0；*/
/*描述：设置此位以反转输入到从发射机的BCK信号*/
#define I2S_TX_BCK_IN_INV  (BIT(24))
#define I2S_TX_BCK_IN_INV_M  (BIT(24))
#define I2S_TX_BCK_IN_INV_V  0x1
#define I2S_TX_BCK_IN_INV_S  24
/* I2S_DATA_ENABLE_DELAY：R/W；比特位置：[23:22]；默认值：2’b0；*/
/*description:数据有效标志的延迟周期数。*/
#define I2S_DATA_ENABLE_DELAY  0x00000003
#define I2S_DATA_ENABLE_DELAY_M  ((I2S_DATA_ENABLE_DELAY_V)<<(I2S_DATA_ENABLE_DELAY_S))
#define I2S_DATA_ENABLE_DELAY_V  0x3
#define I2S_DATA_ENABLE_DELAY_S  22
/* I2S_RX_DSYNC_SW:R/W；位位置：[21]；默认值：1’b0；*/
/*description:设置此位以将信号与双同步方法同步到接收器中*/
#define I2S_RX_DSYNC_SW  (BIT(21))
#define I2S_RX_DSYNC_SW_M  (BIT(21))
#define I2S_RX_DSYNC_SW_V  0x1
#define I2S_RX_DSYNC_SW_S  21
/* I2S_TX_DSYNC_SW:R/W；位位置：[20]；默认值：1’b0；*/
/*description:设置此位以使信号与双同步方法同步到发射机*/
#define I2S_TX_DSYNC_SW  (BIT(20))
#define I2S_TX_DSYNC_SW_M  (BIT(20))
#define I2S_TX_DSYNC_SW_V  0x1
#define I2S_TX_DSYNC_SW_S  20
/* I2S_RX_BCK_OUT_DELAY:R/W；比特位置：[19:18]；默认值：2’b0；*/
/*描述：接收器外BCK的延迟周期数*/
#define I2S_RX_BCK_OUT_DELAY  0x00000003
#define I2S_RX_BCK_OUT_DELAY_M  ((I2S_RX_BCK_OUT_DELAY_V)<<(I2S_RX_BCK_OUT_DELAY_S))
#define I2S_RX_BCK_OUT_DELAY_V  0x3
#define I2S_RX_BCK_OUT_DELAY_S  18
/* I2S_RX_WS_OUT_DELAY:R/W；比特位置：[17:16]；默认值：2’b0；*/
/*description:WS离开接收器的延迟周期数*/
#define I2S_RX_WS_OUT_DELAY  0x00000003
#define I2S_RX_WS_OUT_DELAY_M  ((I2S_RX_WS_OUT_DELAY_V)<<(I2S_RX_WS_OUT_DELAY_S))
#define I2S_RX_WS_OUT_DELAY_V  0x3
#define I2S_RX_WS_OUT_DELAY_S  16
/* I2S_TX_SD_OUT_DELAY:R/W；比特位置：[15:14]；默认值：2’b0；*/
/*description:SD从变送器输出的延迟周期数*/
#define I2S_TX_SD_OUT_DELAY  0x00000003
#define I2S_TX_SD_OUT_DELAY_M  ((I2S_TX_SD_OUT_DELAY_V)<<(I2S_TX_SD_OUT_DELAY_S))
#define I2S_TX_SD_OUT_DELAY_V  0x3
#define I2S_TX_SD_OUT_DELAY_S  14
/* I2S_TX_WS_OUT_DELAY:R/W；比特位置：[13:12]；默认值：2’b0；*/
/*description:WS离开发射机的延迟周期数*/
#define I2S_TX_WS_OUT_DELAY  0x00000003
#define I2S_TX_WS_OUT_DELAY_M  ((I2S_TX_WS_OUT_DELAY_V)<<(I2S_TX_WS_OUT_DELAY_S))
#define I2S_TX_WS_OUT_DELAY_V  0x3
#define I2S_TX_WS_OUT_DELAY_S  12
/* I2S_TX_BCK_OUT_DELAY：R/W；比特位置：[11:10]；默认值：2’b0；*/
/*描述：BCK离开发射机的延迟周期数*/
#define I2S_TX_BCK_OUT_DELAY  0x00000003
#define I2S_TX_BCK_OUT_DELAY_M  ((I2S_TX_BCK_OUT_DELAY_V)<<(I2S_TX_BCK_OUT_DELAY_S))
#define I2S_TX_BCK_OUT_DELAY_V  0x3
#define I2S_TX_BCK_OUT_DELAY_S  10
/* I2S_RX_SD_IN_DELAY：R/W；比特位置：[9:8]；默认值：2’b0；*/
/*description:SD进入接收器的延迟周期数*/
#define I2S_RX_SD_IN_DELAY  0x00000003
#define I2S_RX_SD_IN_DELAY_M  ((I2S_RX_SD_IN_DELAY_V)<<(I2S_RX_SD_IN_DELAY_S))
#define I2S_RX_SD_IN_DELAY_V  0x3
#define I2S_RX_SD_IN_DELAY_S  8
/* I2S_RX_WS_IN_DELAY：R/W；位位置：[7:6]；默认值：2’b0；*/
/*description:WS进入接收器的延迟周期数*/
#define I2S_RX_WS_IN_DELAY  0x00000003
#define I2S_RX_WS_IN_DELAY_M  ((I2S_RX_WS_IN_DELAY_V)<<(I2S_RX_WS_IN_DELAY_S))
#define I2S_RX_WS_IN_DELAY_V  0x3
#define I2S_RX_WS_IN_DELAY_S  6
/* I2S_RX_BCK_IN_DELAY：R/W；比特位置：[5:4]；默认值：2’b0；*/
/*描述：BCK进入接收机的延迟周期数*/
#define I2S_RX_BCK_IN_DELAY  0x00000003
#define I2S_RX_BCK_IN_DELAY_M  ((I2S_RX_BCK_IN_DELAY_V)<<(I2S_RX_BCK_IN_DELAY_S))
#define I2S_RX_BCK_IN_DELAY_V  0x3
#define I2S_RX_BCK_IN_DELAY_S  4
/* I2S_TX_WS_IN_DELAY：R/W；位位置：[3:2]；默认值：2’b0；*/
/*description:WS进入发射机的延迟周期数*/
#define I2S_TX_WS_IN_DELAY  0x00000003
#define I2S_TX_WS_IN_DELAY_M  ((I2S_TX_WS_IN_DELAY_V)<<(I2S_TX_WS_IN_DELAY_S))
#define I2S_TX_WS_IN_DELAY_V  0x3
#define I2S_TX_WS_IN_DELAY_S  2
/* I2S_TX_BCK_IN_DELAY：R/W；位位置：[1:0]；默认值：2’b0；*/
/*描述：BCK进入发射机的延迟周期数*/
#define I2S_TX_BCK_IN_DELAY  0x00000003
#define I2S_TX_BCK_IN_DELAY_M  ((I2S_TX_BCK_IN_DELAY_V)<<(I2S_TX_BCK_IN_DELAY_S))
#define I2S_TX_BCK_IN_DELAY_V  0x3
#define I2S_TX_BCK_IN_DELAY_S  0

#define I2S_FIFO_CONF_REG(i)          (REG_I2S_BASE(i) + 0x0020)
/* I2S_TX_24MSB_EN:R/W；位位置：[23]；默认值：1’b0；*/
/*description:仅在tx 24位模式下有用。1： 高24位在i2s fifo 0中有效：低24位在i2s fifo中有效*/
#define I2S_TX_24MSB_EN  (BIT(23))
#define I2S_TX_24MSB_EN_M  (BIT(23))
#define I2S_TX_24MSB_EN_V  0x1
#define I2S_TX_24MSB_EN_S  23
/* I2S_RX-24MSB-EN:R/W；位位置：[22]；默认值：1’b0；*/
/*description:仅在rx 24位模式下有用。1： 高24位在i2s fifo 0中有效：低24位在i2s fifo中有效*/
#define I2S_RX_24MSB_EN  (BIT(22))
#define I2S_RX_24MSB_EN_M  (BIT(22))
#define I2S_RX_24MSB_EN_V  0x1
#define I2S_RX_24MSB_EN_S  22
/* I2S_RX_fio_SYNC:R/W；位位置：[21]；默认值：1’b0；*/
/*描述：强制将rx数据写回内存*/
#define I2S_RX_FIFO_SYNC  (BIT(21))
#define I2S_RX_FIFO_SYNC_M  (BIT(21))
#define I2S_RX_FIFO_SYNC_V  0x1
#define I2S_RX_FIFO_SYNC_S  21
/* I2S_RX_FIFO_MOD_FORCE_EN:R/W；位位置：[20]；默认值：1’b0；*/
/*description:该位应始终设置为1*/
#define I2S_RX_FIFO_MOD_FORCE_EN  (BIT(20))
#define I2S_RX_FIFO_MOD_FORCE_EN_M  (BIT(20))
#define I2S_RX_FIFO_MOD_FORCE_EN_V  0x1
#define I2S_RX_FIFO_MOD_FORCE_EN_S  20
/* I2S_TX_FIFO_MOD_FORCE_EN:R/W；位位置：[19]；默认值：1’b0；*/
/*description:该位应始终设置为1*/
#define I2S_TX_FIFO_MOD_FORCE_EN  (BIT(19))
#define I2S_TX_FIFO_MOD_FORCE_EN_M  (BIT(19))
#define I2S_TX_FIFO_MOD_FORCE_EN_V  0x1
#define I2S_TX_FIFO_MOD_FORCE_EN_S  19
/* I2S_RX_fio-MOD:R/W；比特位置：[18:16]；默认值：3'b0；*/
/*description:接收器FIFO模式配置位*/
#define I2S_RX_FIFO_MOD  0x00000007
#define I2S_RX_FIFO_MOD_M  ((I2S_RX_FIFO_MOD_V)<<(I2S_RX_FIFO_MOD_S))
#define I2S_RX_FIFO_MOD_V  0x7
#define I2S_RX_FIFO_MOD_S  16
/* I2S_TX_FIFO_MOD:R/W；比特位置：[15:13]；默认值：3'b0；*/
/*description:发射机FIFO模式配置位*/
#define I2S_TX_FIFO_MOD  0x00000007
#define I2S_TX_FIFO_MOD_M  ((I2S_TX_FIFO_MOD_V)<<(I2S_TX_FIFO_MOD_S))
#define I2S_TX_FIFO_MOD_V  0x7
#define I2S_TX_FIFO_MOD_S  13
/* I2S_DSCR_EN:R/W；位位置：[12]；默认值：1'd1；*/
/*description:设置此位以启用I2S DMA模式*/
#define I2S_DSCR_EN  (BIT(12))
#define I2S_DSCR_EN_M  (BIT(12))
#define I2S_DSCR_EN_V  0x1
#define I2S_DSCR_EN_S  12
/* I2S_TX_DATA_NUM:R/W；位位置：[11:6]；默认值：6'd32；*/
/*description:发送器FIFO中的数据长度阈值*/
#define I2S_TX_DATA_NUM  0x0000003F
#define I2S_TX_DATA_NUM_M  ((I2S_TX_DATA_NUM_V)<<(I2S_TX_DATA_NUM_S))
#define I2S_TX_DATA_NUM_V  0x3F
#define I2S_TX_DATA_NUM_S  6
/* I2S_RX_DATA_NUM:R/W；比特位置：[5:0]；默认值：6'd32；*/
/*description:接收器FIFO中的数据长度阈值*/
#define I2S_RX_DATA_NUM  0x0000003F
#define I2S_RX_DATA_NUM_M  ((I2S_RX_DATA_NUM_V)<<(I2S_RX_DATA_NUM_S))
#define I2S_RX_DATA_NUM_V  0x3F
#define I2S_RX_DATA_NUM_S  0

#define I2S_RXEOF_NUM_REG(i)          (REG_I2S_BASE(i) + 0x0024)
/* I2S_RX_of_NUM:R/W；位位置：[31:0]；默认值：32'd64；*/
/*description:要接收的数据长度。它将触发i2s_in_suc_eof_int。*/
#define I2S_RX_EOF_NUM  0xFFFFFFFF
#define I2S_RX_EOF_NUM_M  ((I2S_RX_EOF_NUM_V)<<(I2S_RX_EOF_NUM_S))
#define I2S_RX_EOF_NUM_V  0xFFFFFFFF
#define I2S_RX_EOF_NUM_S  0

#define I2S_CONF_SIGLE_DATA_REG(i)          (REG_I2S_BASE(i) + 0x0028)
/* I2S_SIGLE_DATA:R/W；位位置：[31:0]；默认值：32'd0；*/
/*描述：右通道或左通道根据tx_chan_mod和reg_tx_msb_right输出存储在此寄存器中的常量值*/
#define I2S_SIGLE_DATA  0xFFFFFFFF
#define I2S_SIGLE_DATA_M  ((I2S_SIGLE_DATA_V)<<(I2S_SIGLE_DATA_S))
#define I2S_SIGLE_DATA_V  0xFFFFFFFF
#define I2S_SIGLE_DATA_S  0

#define I2S_CONF_CHAN_REG(i)          (REG_I2S_BASE(i) + 0x002c)
/* I2S_RX通道模式：R/W；位位置：[4:3]；默认值：2’b0；*/
/*描述：I2S接收机信道模式配置位。*/
#define I2S_RX_CHAN_MOD  0x00000003
#define I2S_RX_CHAN_MOD_M  ((I2S_RX_CHAN_MOD_V)<<(I2S_RX_CHAN_MOD_S))
#define I2S_RX_CHAN_MOD_V  0x3
#define I2S_RX_CHAN_MOD_S  3
/* I2S_TX_CHAN模式：R/W；位位置：[2:0]；默认值：3'b0；*/
/*描述：I2S发射机信道模式配置位。*/
#define I2S_TX_CHAN_MOD  0x00000007
#define I2S_TX_CHAN_MOD_M  ((I2S_TX_CHAN_MOD_V)<<(I2S_TX_CHAN_MOD_S))
#define I2S_TX_CHAN_MOD_V  0x7
#define I2S_TX_CHAN_MOD_S  0

#define I2S_OUT_LINK_REG(i)          (REG_I2S_BASE(i) + 0x0030)
/* I2S_OUTLINK_PARK:RO；位位置：[31]；默认值：1'0；*/
/*说明：*/
#define I2S_OUTLINK_PARK  (BIT(31))
#define I2S_OUTLINK_PARK_M  (BIT(31))
#define I2S_OUTLINK_PARK_V  0x1
#define I2S_OUTLINK_PARK_S  31
/* I2S_OUTLINK_RESTART：R/W；位位置：[30]；默认值：1’b0；*/
/*description:设置此位以重新启动outlink描述符*/
#define I2S_OUTLINK_RESTART  (BIT(30))
#define I2S_OUTLINK_RESTART_M  (BIT(30))
#define I2S_OUTLINK_RESTART_V  0x1
#define I2S_OUTLINK_RESTART_S  30
/* I2S_OUTLINK_START:R/W；位位置：[29]；默认值：1’b0；*/
/*description:设置此位以启动outlink描述符*/
#define I2S_OUTLINK_START  (BIT(29))
#define I2S_OUTLINK_START_M  (BIT(29))
#define I2S_OUTLINK_START_V  0x1
#define I2S_OUTLINK_START_S  29
/* I2S_OUTLINK_STOP：R/W；位位置：[28]；默认值：1’b0；*/
/*description:设置此位以停止outlink描述符*/
#define I2S_OUTLINK_STOP  (BIT(28))
#define I2S_OUTLINK_STOP_M  (BIT(28))
#define I2S_OUTLINK_STOP_V  0x1
#define I2S_OUTLINK_STOP_S  28
/* I2S_OUTLINK_ADDR:R/W；比特位置：[19:0]；默认值：20'00；*/
/*description:第一个outlink描述符的地址*/
#define I2S_OUTLINK_ADDR  0x000FFFFF
#define I2S_OUTLINK_ADDR_M  ((I2S_OUTLINK_ADDR_V)<<(I2S_OUTLINK_ADDR_S))
#define I2S_OUTLINK_ADDR_V  0xFFFFF
#define I2S_OUTLINK_ADDR_S  0

#define I2S_IN_LINK_REG(i)          (REG_I2S_BASE(i) + 0x0034)
/* I2S_INLINK_PARK:RO；位位置：[31]；默认值：1'0；*/
/*说明：*/
#define I2S_INLINK_PARK  (BIT(31))
#define I2S_INLINK_PARK_M  (BIT(31))
#define I2S_INLINK_PARK_V  0x1
#define I2S_INLINK_PARK_S  31
/* I2S_INLINK_RESTART：R/W；位位置：[30]；默认值：1’b0；*/
/*description:设置此位以重新启动内联描述符*/
#define I2S_INLINK_RESTART  (BIT(30))
#define I2S_INLINK_RESTART_M  (BIT(30))
#define I2S_INLINK_RESTART_V  0x1
#define I2S_INLINK_RESTART_S  30
/* I2S_INLINK_START:R/W；位位置：[29]；默认值：1’b0；*/
/*description:设置此位以启动内联描述符*/
#define I2S_INLINK_START  (BIT(29))
#define I2S_INLINK_START_M  (BIT(29))
#define I2S_INLINK_START_V  0x1
#define I2S_INLINK_START_S  29
/* I2S_INLINK_STOP:R/W；位位置：[28]；默认值：1’b0；*/
/*description:设置此位以停止内联描述符*/
#define I2S_INLINK_STOP  (BIT(28))
#define I2S_INLINK_STOP_M  (BIT(28))
#define I2S_INLINK_STOP_V  0x1
#define I2S_INLINK_STOP_S  28
/* I2S_INLINK_ADDR:R/W；比特位置：[19:0]；默认值：20'00；*/
/*description:第一个内联描述符的地址*/
#define I2S_INLINK_ADDR  0x000FFFFF
#define I2S_INLINK_ADDR_M  ((I2S_INLINK_ADDR_V)<<(I2S_INLINK_ADDR_S))
#define I2S_INLINK_ADDR_V  0xFFFFF
#define I2S_INLINK_ADDR_S  0

#define I2S_OUT_EOF_DES_ADDR_REG(i)          (REG_I2S_BASE(i) + 0x0038)
/* I2S_OUT_EOF_DES_ADDR:RO；位位置：[31:0]；默认值：32'h0；*/
/*description:生成EOF的outlink描述符的地址*/
#define I2S_OUT_EOF_DES_ADDR  0xFFFFFFFF
#define I2S_OUT_EOF_DES_ADDR_M  ((I2S_OUT_EOF_DES_ADDR_V)<<(I2S_OUT_EOF_DES_ADDR_S))
#define I2S_OUT_EOF_DES_ADDR_V  0xFFFFFFFF
#define I2S_OUT_EOF_DES_ADDR_S  0

#define I2S_IN_EOF_DES_ADDR_REG(i)          (REG_I2S_BASE(i) + 0x003c)
/* I2S_IN_SUC_EOF_DES_ADDR:RO；位位置：[31:0]；默认值：32'h0；*/
/*description:生成EOF的内联描述符的地址*/
#define I2S_IN_SUC_EOF_DES_ADDR  0xFFFFFFFF
#define I2S_IN_SUC_EOF_DES_ADDR_M  ((I2S_IN_SUC_EOF_DES_ADDR_V)<<(I2S_IN_SUC_EOF_DES_ADDR_S))
#define I2S_IN_SUC_EOF_DES_ADDR_V  0xFFFFFFFF
#define I2S_IN_SUC_EOF_DES_ADDR_S  0

#define I2S_OUT_EOF_BFR_DES_ADDR_REG(i)          (REG_I2S_BASE(i) + 0x0040)
/* I2S_OUT_EOF_BFR_DES_ADDR:RO；位位置：[31:0]；默认值：32'h0；*/
/*description:相对于产生EOF的outlink描述符的缓冲区地址*/
#define I2S_OUT_EOF_BFR_DES_ADDR  0xFFFFFFFF
#define I2S_OUT_EOF_BFR_DES_ADDR_M  ((I2S_OUT_EOF_BFR_DES_ADDR_V)<<(I2S_OUT_EOF_BFR_DES_ADDR_S))
#define I2S_OUT_EOF_BFR_DES_ADDR_V  0xFFFFFFFF
#define I2S_OUT_EOF_BFR_DES_ADDR_S  0

#define I2S_AHB_TEST_REG(i)          (REG_I2S_BASE(i) + 0x0044)
/* I2S_AHB_testadr:R/W；比特位置：[5:4]；默认值：2’b0；*/
/*说明：*/
#define I2S_AHB_TESTADDR  0x00000003
#define I2S_AHB_TESTADDR_M  ((I2S_AHB_TESTADDR_V)<<(I2S_AHB_TESTADDR_S))
#define I2S_AHB_TESTADDR_V  0x3
#define I2S_AHB_TESTADDR_S  4
/* I2S_AHB_TESTMODE:R/W；位位置：[2:0]；默认值：3'b0；*/
/*说明：*/
#define I2S_AHB_TESTMODE  0x00000007
#define I2S_AHB_TESTMODE_M  ((I2S_AHB_TESTMODE_V)<<(I2S_AHB_TESTMODE_S))
#define I2S_AHB_TESTMODE_V  0x7
#define I2S_AHB_TESTMODE_S  0

#define I2S_INLINK_DSCR_REG(i)          (REG_I2S_BASE(i) + 0x0048)
/* I2S_INLINK_DSCR:RO；位位置：[31:0]；默认值：32'b0；*/
/*description:当前内联描述符的地址*/
#define I2S_INLINK_DSCR  0xFFFFFFFF
#define I2S_INLINK_DSCR_M  ((I2S_INLINK_DSCR_V)<<(I2S_INLINK_DSCR_S))
#define I2S_INLINK_DSCR_V  0xFFFFFFFF
#define I2S_INLINK_DSCR_S  0

#define I2S_INLINK_DSCR_BF0_REG(i)          (REG_I2S_BASE(i) + 0x004C)
/* I2S_INLINK_DSCR_BF0:RO；位位置：[31:0]；默认值：32'b0；*/
/*description:下一个内联描述符的地址*/
#define I2S_INLINK_DSCR_BF0  0xFFFFFFFF
#define I2S_INLINK_DSCR_BF0_M  ((I2S_INLINK_DSCR_BF0_V)<<(I2S_INLINK_DSCR_BF0_S))
#define I2S_INLINK_DSCR_BF0_V  0xFFFFFFFF
#define I2S_INLINK_DSCR_BF0_S  0

#define I2S_INLINK_DSCR_BF1_REG(i)          (REG_I2S_BASE(i) + 0x0050)
/* I2S_INLINK_DSCR_BF1:RO；位位置：[31:0]；默认值：32'b0；*/
/*description:下一个内联数据缓冲区的地址*/
#define I2S_INLINK_DSCR_BF1  0xFFFFFFFF
#define I2S_INLINK_DSCR_BF1_M  ((I2S_INLINK_DSCR_BF1_V)<<(I2S_INLINK_DSCR_BF1_S))
#define I2S_INLINK_DSCR_BF1_V  0xFFFFFFFF
#define I2S_INLINK_DSCR_BF1_S  0

#define I2S_OUTLINK_DSCR_REG(i)          (REG_I2S_BASE(i) + 0x0054)
/* I2S_OUTLINK_DSCR:RO；位位置：[31:0]；默认值：32'b0；*/
/*description:当前outlink描述符的地址*/
#define I2S_OUTLINK_DSCR  0xFFFFFFFF
#define I2S_OUTLINK_DSCR_M  ((I2S_OUTLINK_DSCR_V)<<(I2S_OUTLINK_DSCR_S))
#define I2S_OUTLINK_DSCR_V  0xFFFFFFFF
#define I2S_OUTLINK_DSCR_S  0

#define I2S_OUTLINK_DSCR_BF0_REG(i)          (REG_I2S_BASE(i) + 0x0058)
/* I2S_OUTLINK_DSCR_BF0:RO；位位置：[31:0]；默认值：32'b0；*/
/*description:下一个outlink描述符的地址*/
#define I2S_OUTLINK_DSCR_BF0  0xFFFFFFFF
#define I2S_OUTLINK_DSCR_BF0_M  ((I2S_OUTLINK_DSCR_BF0_V)<<(I2S_OUTLINK_DSCR_BF0_S))
#define I2S_OUTLINK_DSCR_BF0_V  0xFFFFFFFF
#define I2S_OUTLINK_DSCR_BF0_S  0

#define I2S_OUTLINK_DSCR_BF1_REG(i)          (REG_I2S_BASE(i) + 0x005C)
/* I2S_OUTLINK_DSCR_BF1:RO；位位置：[31:0]；默认值：32'b0；*/
/*description:下一个outlink数据缓冲区的地址*/
#define I2S_OUTLINK_DSCR_BF1  0xFFFFFFFF
#define I2S_OUTLINK_DSCR_BF1_M  ((I2S_OUTLINK_DSCR_BF1_V)<<(I2S_OUTLINK_DSCR_BF1_S))
#define I2S_OUTLINK_DSCR_BF1_V  0xFFFFFFFF
#define I2S_OUTLINK_DSCR_BF1_S  0

#define I2S_LC_CONF_REG(i)          (REG_I2S_BASE(i) + 0x0060)
/* I2S_EXT_MEM_BK_SIZE:R/W；比特位置：[15:14]；默认值：2’b0；*/
/*描述：DMA访问外部内存块大小。0:16字节1:32字节2:64字节3:保留*/
#define I2S_EXT_MEM_BK_SIZE  0x00000003
#define I2S_EXT_MEM_BK_SIZE_M  ((I2S_EXT_MEM_BK_SIZE_V)<<(I2S_EXT_MEM_BK_SIZE_S))
#define I2S_EXT_MEM_BK_SIZE_V  0x3
#define I2S_EXT_MEM_BK_SIZE_S  14
/* I2S_MEM_TRANS_EN:R/W；位位置：[13]；默认值：1’b0；*/
/*description:不使用*/
#define I2S_MEM_TRANS_EN  (BIT(13))
#define I2S_MEM_TRANS_EN_M  (BIT(13))
#define I2S_MEM_TRANS_EN_V  0x1
#define I2S_MEM_TRANS_EN_S  13
/* I2S_CHECK_OWNER:R/W；位位置：[12]；默认值：1’b0；*/
/*description:设置此位以启用硬件检查所有者位*/
#define I2S_CHECK_OWNER  (BIT(12))
#define I2S_CHECK_OWNER_M  (BIT(12))
#define I2S_CHECK_OWNER_V  0x1
#define I2S_CHECK_OWNER_S  12
/* I2S_OUT_DATA_BURST_EN:R/W；位位置：[11]；默认值：1’b0；*/
/*description:变送器数据传输模式配置位。1： 以突发模式0准备输出数据：以字节模式准备输出数据*/
#define I2S_OUT_DATA_BURST_EN  (BIT(11))
#define I2S_OUT_DATA_BURST_EN_M  (BIT(11))
#define I2S_OUT_DATA_BURST_EN_V  0x1
#define I2S_OUT_DATA_BURST_EN_S  11
/* I2S_indcr_BURST_EN:R/W；位位置：[10]；默认值：1’b0；*/
/*description:DMA内联描述符传输模式配置位。1： 使用突发模式0准备内联描述符：使用字节模式准备内联描述符*/
#define I2S_INDSCR_BURST_EN  (BIT(10))
#define I2S_INDSCR_BURST_EN_M  (BIT(10))
#define I2S_INDSCR_BURST_EN_V  0x1
#define I2S_INDSCR_BURST_EN_S  10
/* I2S_OUTDSCR_BURST_EN:R/W；位位置：[9]；默认值：1’b0；*/
/*描述：DMA outlink描述符传输模式配置位。1： 使用突发模式0准备outlink描述符：使用字节模式准备outlink描述符*/
#define I2S_OUTDSCR_BURST_EN  (BIT(9))
#define I2S_OUTDSCR_BURST_EN_M  (BIT(9))
#define I2S_OUTDSCR_BURST_EN_V  0x1
#define I2S_OUTDSCR_BURST_EN_S  9
/* I2S_OUT_EOF_MODE：R/W；位位置：[8]；默认值：1’b1；*/
/*描述：DMA输出EOF标志生成模式。1： dma从FIFO 0中弹出所有数据时：ahb将所有数据推送到FIFO时*/
#define I2S_OUT_EOF_MODE  (BIT(8))
#define I2S_OUT_EOF_MODE_M  (BIT(8))
#define I2S_OUT_EOF_MODE_V  0x1
#define I2S_OUT_EOF_MODE_S  8
/* I2S_OUT_NO_RESTART_CLR:R/W；位位置：[7]；默认值：1’b0；*/
/*description:不使用*/
#define I2S_OUT_NO_RESTART_CLR  (BIT(7))
#define I2S_OUT_NO_RESTART_CLR_M  (BIT(7))
#define I2S_OUT_NO_RESTART_CLR_V  0x1
#define I2S_OUT_NO_RESTART_CLR_S  7
/* I2S_OUT_AUTO_werback:R/W；位位置：[6]；默认值：1’b0；*/
/*description:设置此位以在输出缓冲区传输完成时启用自动写回的outlink。*/
#define I2S_OUT_AUTO_WRBACK  (BIT(6))
#define I2S_OUT_AUTO_WRBACK_M  (BIT(6))
#define I2S_OUT_AUTO_WRBACK_V  0x1
#define I2S_OUT_AUTO_WRBACK_S  6
/* I2S_IN_LOOP_TEST:R/W；位位置：[5]；默认值：1’b0；*/
/*description:将此位设置为循环测试输出链接*/
#define I2S_IN_LOOP_TEST  (BIT(5))
#define I2S_IN_LOOP_TEST_M  (BIT(5))
#define I2S_IN_LOOP_TEST_V  0x1
#define I2S_IN_LOOP_TEST_S  5
/* I2S_OUT_LOOP_TEST:R/W；位位置：[4]；默认值：1’b0；*/
/*description:将此位设置为循环测试内联*/
#define I2S_OUT_LOOP_TEST  (BIT(4))
#define I2S_OUT_LOOP_TEST_M  (BIT(4))
#define I2S_OUT_LOOP_TEST_V  0x1
#define I2S_OUT_LOOP_TEST_S  4
/* I2S_AHBM_RST:R/W；位位置：[3]；默认值：1’b0；*/
/*description:设置此位以重置DMA的ahb接口*/
#define I2S_AHBM_RST  (BIT(3))
#define I2S_AHBM_RST_M  (BIT(3))
#define I2S_AHBM_RST_V  0x1
#define I2S_AHBM_RST_S  3
/* I2S_AHBM_FIFO_RST:R/W；位位置：[2]；默认值：1’b0；*/
/*description:设置此位以重置DMA的ahb接口cmdFIFO*/
#define I2S_AHBM_FIFO_RST  (BIT(2))
#define I2S_AHBM_FIFO_RST_M  (BIT(2))
#define I2S_AHBM_FIFO_RST_V  0x1
#define I2S_AHBM_FIFO_RST_S  2
/* I2S_OUT_RST:R/W；位位置：[1]；默认值：1’b0；*/
/*description:设置此位以重置dma FSM*/
#define I2S_OUT_RST  (BIT(1))
#define I2S_OUT_RST_M  (BIT(1))
#define I2S_OUT_RST_V  0x1
#define I2S_OUT_RST_S  1
/* I2S_IN_RST:R/W；位位置：[0]；默认值：1'0；*/
/*description:在dma FSM中将此位设置为重置*/
#define I2S_IN_RST  (BIT(0))
#define I2S_IN_RST_M  (BIT(0))
#define I2S_IN_RST_V  0x1
#define I2S_IN_RST_S  0

#define I2S_OUTFIFO_PUSH_REG(i)          (REG_I2S_BASE(i) + 0x0064)
/* I2S_outifo_PUSH:R/W；位位置：[16]；默认值：1'0；*/
/*说明：*/
#define I2S_OUTFIFO_PUSH  (BIT(16))
#define I2S_OUTFIFO_PUSH_M  (BIT(16))
#define I2S_OUTFIFO_PUSH_V  0x1
#define I2S_OUTFIFO_PUSH_S  16
/* I2S_outifo_WDATA:R/W；位位置：[8:0]；默认值：9'0；*/
/*说明：*/
#define I2S_OUTFIFO_WDATA  0x000001FF
#define I2S_OUTFIFO_WDATA_M  ((I2S_OUTFIFO_WDATA_V)<<(I2S_OUTFIFO_WDATA_S))
#define I2S_OUTFIFO_WDATA_V  0x1FF
#define I2S_OUTFIFO_WDATA_S  0

#define I2S_INFIFO_POP_REG(i)          (REG_I2S_BASE(i) + 0x0068)
/* I2S_infinfo_POP:R/W；位位置：[16]；默认值：1'0；*/
/*说明：*/
#define I2S_INFIFO_POP  (BIT(16))
#define I2S_INFIFO_POP_M  (BIT(16))
#define I2S_INFIFO_POP_V  0x1
#define I2S_INFIFO_POP_S  16
/* I2S_infinfo_RDATA:RO；位位置：[11:0]；默认值：12'0；*/
/*说明：*/
#define I2S_INFIFO_RDATA  0x00000FFF
#define I2S_INFIFO_RDATA_M  ((I2S_INFIFO_RDATA_V)<<(I2S_INFIFO_RDATA_S))
#define I2S_INFIFO_RDATA_V  0xFFF
#define I2S_INFIFO_RDATA_S  0

#define I2S_LC_STATE0_REG(i)          (REG_I2S_BASE(i) + 0x006C)
/* I2S_OUT_EMPTY:RO；位位置：[31]；默认值：1'0；*/
/*描述：DMA发射机状态寄存器*/
#define I2S_OUT_EMPTY  (BIT(31))
#define I2S_OUT_EMPTY_M  (BIT(31))
#define I2S_OUT_EMPTY_V  0x1
#define I2S_OUT_EMPTY_S  31
/* I2S_OUT_FULL:RO；位位置：[30]；默认值：1’b0；*/
/*说明：*/
#define I2S_OUT_FULL  (BIT(30))
#define I2S_OUT_FULL_M  (BIT(30))
#define I2S_OUT_FULL_V  0x1
#define I2S_OUT_FULL_S  30
/* I2S_outifo_CNT:RO；位位置：[29:23]；默认值：7'b0；*/
/*说明：*/
#define I2S_OUTFIFO_CNT  0x0000007F
#define I2S_OUTFIFO_CNT_M  ((I2S_OUTFIFO_CNT_V)<<(I2S_OUTFIFO_CNT_S))
#define I2S_OUTFIFO_CNT_V  0x7F
#define I2S_OUTFIFO_CNT_S  23
/* I2S_OUT_STATE:RO；比特位置：[22:20]；默认值：3'b0；*/
/*说明：*/
#define I2S_OUT_STATE  0x00000007
#define I2S_OUT_STATE_M  ((I2S_OUT_STATE_V)<<(I2S_OUT_STATE_S))
#define I2S_OUT_STATE_V  0x7
#define I2S_OUT_STATE_S  20
/* I2S_OUT_DSCR_STATE:RO；比特位置：[19:18]；默认值：2’b0；*/
/*说明：*/
#define I2S_OUT_DSCR_STATE  0x00000003
#define I2S_OUT_DSCR_STATE_M  ((I2S_OUT_DSCR_STATE_V)<<(I2S_OUT_DSCR_STATE_S))
#define I2S_OUT_DSCR_STATE_V  0x3
#define I2S_OUT_DSCR_STATE_S  18
/* I2S_OUTLINK_DSCR_ADDR:RO；比特位置：[17:00]；默认值：18'0；*/
/*说明：*/
#define I2S_OUTLINK_DSCR_ADDR  0x0003FFFF
#define I2S_OUTLINK_DSCR_ADDR_M  ((I2S_OUTLINK_DSCR_ADDR_V)<<(I2S_OUTLINK_DSCR_ADDR_S))
#define I2S_OUTLINK_DSCR_ADDR_V  0x3FFFF
#define I2S_OUTLINK_DSCR_ADDR_S  0

#define I2S_LC_STATE1_REG(i)          (REG_I2S_BASE(i) + 0x0070)
/* I2S_IN_EMPTY:RO；位位置：[31]；默认值：1'0；*/
/*描述：DMA接收机状态寄存器*/
#define I2S_IN_EMPTY  (BIT(31))
#define I2S_IN_EMPTY_M  (BIT(31))
#define I2S_IN_EMPTY_V  0x1
#define I2S_IN_EMPTY_S  31
/* I2S_IN_FULL:RO；位位置：[30]；默认值：1’b0；*/
/*说明：*/
#define I2S_IN_FULL  (BIT(30))
#define I2S_IN_FULL_M  (BIT(30))
#define I2S_IN_FULL_V  0x1
#define I2S_IN_FULL_S  30
/* I2S_infinfo_CNT_DEBUG:RO；位位置：[29:23]；默认值：7'b0；*/
/*说明：*/
#define I2S_INFIFO_CNT_DEBUG  0x0000007F
#define I2S_INFIFO_CNT_DEBUG_M  ((I2S_INFIFO_CNT_DEBUG_V)<<(I2S_INFIFO_CNT_DEBUG_S))
#define I2S_INFIFO_CNT_DEBUG_V  0x7F
#define I2S_INFIFO_CNT_DEBUG_S  23
/* I2S_IN_STATE:RO；比特位置：[22:20]；默认值：3'b0；*/
/*说明：*/
#define I2S_IN_STATE  0x00000007
#define I2S_IN_STATE_M  ((I2S_IN_STATE_V)<<(I2S_IN_STATE_S))
#define I2S_IN_STATE_V  0x7
#define I2S_IN_STATE_S  20
/* I2S_IN_DSCR_STATE:RO；比特位置：[19:18]；默认值：2’b0；*/
/*说明：*/
#define I2S_IN_DSCR_STATE  0x00000003
#define I2S_IN_DSCR_STATE_M  ((I2S_IN_DSCR_STATE_V)<<(I2S_IN_DSCR_STATE_S))
#define I2S_IN_DSCR_STATE_V  0x3
#define I2S_IN_DSCR_STATE_S  18
/* I2S_INLINK_dcr_ADDR:RO；比特位置：[17:00]；默认值：18'0；*/
/*说明：*/
#define I2S_INLINK_DSCR_ADDR  0x0003FFFF
#define I2S_INLINK_DSCR_ADDR_M  ((I2S_INLINK_DSCR_ADDR_V)<<(I2S_INLINK_DSCR_ADDR_S))
#define I2S_INLINK_DSCR_ADDR_V  0x3FFFF
#define I2S_INLINK_DSCR_ADDR_S  0

#define I2S_LC_HUNG_CONF_REG(i)          (REG_I2S_BASE(i) + 0x0074)
/* I2S_LC_FIFO_TIMEOUT_ENA:R/W；位位置：[11]；默认值：1’b1；*/
/*description:FIFO超时的启用位*/
#define I2S_LC_FIFO_TIMEOUT_ENA  (BIT(11))
#define I2S_LC_FIFO_TIMEOUT_ENA_M  (BIT(11))
#define I2S_LC_FIFO_TIMEOUT_ENA_V  0x1
#define I2S_LC_FIFO_TIMEOUT_ENA_S  11
/* I2S_LC_FIFO_TIMEOUT_SHIFT:R/W；比特位置：[10:8]；默认值：3'b0；*/
/*description:位用于缩放刻度计数器阈值。当计数器值>=88000/2^i2s_lc_fifo_timeout_shift时，滴答计数器复位*/
#define I2S_LC_FIFO_TIMEOUT_SHIFT  0x00000007
#define I2S_LC_FIFO_TIMEOUT_SHIFT_M  ((I2S_LC_FIFO_TIMEOUT_SHIFT_V)<<(I2S_LC_FIFO_TIMEOUT_SHIFT_S))
#define I2S_LC_FIFO_TIMEOUT_SHIFT_V  0x7
#define I2S_LC_FIFO_TIMEOUT_SHIFT_S  8
/* I2S_LC_FIFO_TIMEOUT:R/W；位位置：[7:0]；默认值：8'h10；*/
/*描述：当fifo挂起计数器等于此值时，将触发i2s_tx_hung_int中断或i2s_rx-hung_int*/
#define I2S_LC_FIFO_TIMEOUT  0x000000FF
#define I2S_LC_FIFO_TIMEOUT_M  ((I2S_LC_FIFO_TIMEOUT_V)<<(I2S_LC_FIFO_TIMEOUT_S))
#define I2S_LC_FIFO_TIMEOUT_V  0xFF
#define I2S_LC_FIFO_TIMEOUT_S  0

#define I2S_CONF1_REG(i)          (REG_I2S_BASE(i) + 0x00a0)
/* I2S_TX_ZEROS_RM_EN:R/W；位位置：[9]；默认值：1'd0；*/
/*description:不使用*/
#define I2S_TX_ZEROS_RM_EN  (BIT(9))
#define I2S_TX_ZEROS_RM_EN_M  (BIT(9))
#define I2S_TX_ZEROS_RM_EN_V  0x1
#define I2S_TX_ZEROS_RM_EN_S  9
/* I2S_TX_STOP_EN:R/W；位位置：[8]；默认值：1'd0；*/
/*description:当tx FIFO为emtpy时，设置此位以停止禁用输出BCK信号和WS信号*/
#define I2S_TX_STOP_EN  (BIT(8))
#define I2S_TX_STOP_EN_M  (BIT(8))
#define I2S_TX_STOP_EN_V  0x1
#define I2S_TX_STOP_EN_S  8
/* I2S_rxpcm_BYPASS:R/W；位位置：[7]；默认值：1'h1；*/
/*description:设置此位以绕过接收数据的压缩/解压缩模块。*/
#define I2S_RX_PCM_BYPASS  (BIT(7))
#define I2S_RX_PCM_BYPASS_M  (BIT(7))
#define I2S_RX_PCM_BYPASS_V  0x1
#define I2S_RX_PCM_BYPASS_S  7
/* I2S_rxpcm_CONF:R/W；比特位置：[6:4]；默认值：3'h0；*/
/*description:压缩/解压缩模块配置位。0：解压缩接收数据1：压缩接收数据*/
#define I2S_RX_PCM_CONF  0x00000007
#define I2S_RX_PCM_CONF_M  ((I2S_RX_PCM_CONF_V)<<(I2S_RX_PCM_CONF_S))
#define I2S_RX_PCM_CONF_V  0x7
#define I2S_RX_PCM_CONF_S  4
/* I2S_TX_PCM_BYPASS:R/W；位位置：[3]；默认值：1'h1；*/
/*description:设置此位以绕过传输数据的压缩/解压缩模块。*/
#define I2S_TX_PCM_BYPASS  (BIT(3))
#define I2S_TX_PCM_BYPASS_M  (BIT(3))
#define I2S_TX_PCM_BYPASS_V  0x1
#define I2S_TX_PCM_BYPASS_S  3
/* I2S_TX_PCM_CONF:R/W；位位置：[2:0]；默认值：3'h1；*/
/*description:压缩/解压缩模块配置位。0：解压缩传输数据1：压缩传输数据*/
#define I2S_TX_PCM_CONF  0x00000007
#define I2S_TX_PCM_CONF_M  ((I2S_TX_PCM_CONF_V)<<(I2S_TX_PCM_CONF_S))
#define I2S_TX_PCM_CONF_V  0x7
#define I2S_TX_PCM_CONF_S  0

#define I2S_PD_CONF_REG(i)          (REG_I2S_BASE(i) + 0x00a4)
/* I2S_DMA_RAM_CLK_FO:R/W；位位置：[6]；默认值：1'0；*/
/*说明：*/
#define I2S_DMA_RAM_CLK_FO  (BIT(6))
#define I2S_DMA_RAM_CLK_FO_M  (BIT(6))
#define I2S_DMA_RAM_CLK_FO_V  0x1
#define I2S_DMA_RAM_CLK_FO_S  6
/* I2S_DMA_RAM_FORCE_PU:R/W；位位置：[5]；默认值：1'h1；*/
/*说明：*/
#define I2S_DMA_RAM_FORCE_PU  (BIT(5))
#define I2S_DMA_RAM_FORCE_PU_M  (BIT(5))
#define I2S_DMA_RAM_FORCE_PU_V  0x1
#define I2S_DMA_RAM_FORCE_PU_S  5
/* I2S_DMA_RAM_FORCE_PD:R/W；位位置：[4]；默认值：1'0；*/
/*说明：*/
#define I2S_DMA_RAM_FORCE_PD  (BIT(4))
#define I2S_DMA_RAM_FORCE_PD_M  (BIT(4))
#define I2S_DMA_RAM_FORCE_PD_V  0x1
#define I2S_DMA_RAM_FORCE_PD_S  4
/* I2S_PLC_MEM_FORCE_PU:R/W；位位置：[3]；默认值：1'h1；*/
/*说明：*/
#define I2S_PLC_MEM_FORCE_PU  (BIT(3))
#define I2S_PLC_MEM_FORCE_PU_M  (BIT(3))
#define I2S_PLC_MEM_FORCE_PU_V  0x1
#define I2S_PLC_MEM_FORCE_PU_S  3
/* I2S_PLC_MEM_FORCE_PD:R/W；位位置：[2]；默认值：1'0；*/
/*说明：*/
#define I2S_PLC_MEM_FORCE_PD  (BIT(2))
#define I2S_PLC_MEM_FORCE_PD_M  (BIT(2))
#define I2S_PLC_MEM_FORCE_PD_V  0x1
#define I2S_PLC_MEM_FORCE_PD_S  2
/* I2S_FIFO_FORCE_PU:R/W；位位置：[1]；默认值：1'h1；*/
/*description:强制FIFO通电*/
#define I2S_FIFO_FORCE_PU  (BIT(1))
#define I2S_FIFO_FORCE_PU_M  (BIT(1))
#define I2S_FIFO_FORCE_PU_V  0x1
#define I2S_FIFO_FORCE_PU_S  1
/* I2S_FIFO_FORCE_PD:R/W；位位置：[0]；默认值：1'0；*/
/*description:强制FIFO断电*/
#define I2S_FIFO_FORCE_PD  (BIT(0))
#define I2S_FIFO_FORCE_PD_M  (BIT(0))
#define I2S_FIFO_FORCE_PD_V  0x1
#define I2S_FIFO_FORCE_PD_S  0

#define I2S_CONF2_REG(i)          (REG_I2S_BASE(i) + 0x00a8)
/* I2S_i2siv_SYNC_FILTER_threes:R/W；比特位置：[13:11]；默认值：3'b0；*/
/*说明：*/
#define I2S_I2SI_V_SYNC_FILTER_THRES  0x00000007
#define I2S_I2SI_V_SYNC_FILTER_THRES_M  ((I2S_I2SI_V_SYNC_FILTER_THRES_V)<<(I2S_I2SI_V_SYNC_FILTER_THRES_S))
#define I2S_I2SI_V_SYNC_FILTER_THRES_V  0x7
#define I2S_I2SI_V_SYNC_FILTER_THRES_S  11
/* I2S_i2siv_SYNC_FILTER_EN:R/W；位位置：[10]；默认值：1’b0；*/
/*说明：*/
#define I2S_I2SI_V_SYNC_FILTER_EN  (BIT(10))
#define I2S_I2SI_V_SYNC_FILTER_EN_M  (BIT(10))
#define I2S_I2SI_V_SYNC_FILTER_EN_V  0x1
#define I2S_I2SI_V_SYNC_FILTER_EN_S  10
/* I2S_CAM_CLK_LOOPBACK:R/W；位位置：[9]；默认值：1’b0；*/
/*description:将此位设置为从i2s_rx环回cam_clk*/
#define I2S_CAM_CLK_LOOPBACK  (BIT(9))
#define I2S_CAM_CLK_LOOPBACK_M  (BIT(9))
#define I2S_CAM_CLK_LOOPBACK_V  0x1
#define I2S_CAM_CLK_LOOPBACK_S  9
/* I2S_CAM_SYNC_FIFO_RESET:R/W；位位置：[8]；默认值：1’b0；*/
/*description:设置此位以重置cam_sync_fifo*/
#define I2S_CAM_SYNC_FIFO_RESET  (BIT(8))
#define I2S_CAM_SYNC_FIFO_RESET_M  (BIT(8))
#define I2S_CAM_SYNC_FIFO_RESET_V  0x1
#define I2S_CAM_SYNC_FIFO_RESET_S  8
/* I2S_INTER_VALID_EN:R/W；位位置：[7]；默认值：1’b0；*/
/*description:设置此位以启用相机内部有效*/
#define I2S_INTER_VALID_EN  (BIT(7))
#define I2S_INTER_VALID_EN_M  (BIT(7))
#define I2S_INTER_VALID_EN_V  0x1
#define I2S_INTER_VALID_EN_S  7
/* I2S_EXT_ADC_START_EN:R/W；位位置：[6]；默认值：1’b0；*/
/*description:设置此位以启用外部信号触发ADC模式的功能。*/
#define I2S_EXT_ADC_START_EN  (BIT(6))
#define I2S_EXT_ADC_START_EN_M  (BIT(6))
#define I2S_EXT_ADC_START_EN_V  0x1
#define I2S_EXT_ADC_START_EN_S  6
/* I2S_LCD_EN:R/W；位位置：[5]；默认值：1’b0；*/
/*description:设置此位以启用LCD模式*/
#define I2S_LCD_EN  (BIT(5))
#define I2S_LCD_EN_M  (BIT(5))
#define I2S_LCD_EN_V  0x1
#define I2S_LCD_EN_S  5
/* I2S_DATA_ENABLE:R/W；位位置：[4]；默认值：1'0；*/
/*描述：用于调试相机模式启用*/
#define I2S_DATA_ENABLE  (BIT(4))
#define I2S_DATA_ENABLE_M  (BIT(4))
#define I2S_DATA_ENABLE_V  0x1
#define I2S_DATA_ENABLE_S  4
/* I2S_DATA_ENABLE_TEST_EN:R/W；位位置：[3]；默认值：1'0；*/
/*描述：用于调试相机模式启用*/
#define I2S_DATA_ENABLE_TEST_EN  (BIT(3))
#define I2S_DATA_ENABLE_TEST_EN_M  (BIT(3))
#define I2S_DATA_ENABLE_TEST_EN_V  0x1
#define I2S_DATA_ENABLE_TEST_EN_S  3
/* I2S_LCD_TX_SDX2_EN:R/W；位位置：[2]；默认值：1'0；*/
/*description:将此位设置为在LCD模式下复制数据对（帧格式2）。*/
#define I2S_LCD_TX_SDX2_EN  (BIT(2))
#define I2S_LCD_TX_SDX2_EN_M  (BIT(2))
#define I2S_LCD_TX_SDX2_EN_V  0x1
#define I2S_LCD_TX_SDX2_EN_S  2
/* I2S_LCD_TX_WRX2_EN:R/W；位位置：[1]；默认值：1'0；*/
/*说明：LCD WR双用于一个基准。*/
#define I2S_LCD_TX_WRX2_EN  (BIT(1))
#define I2S_LCD_TX_WRX2_EN_M  (BIT(1))
#define I2S_LCD_TX_WRX2_EN_V  0x1
#define I2S_LCD_TX_WRX2_EN_S  1
/* I2S_CAMERA_EN:R/W；位位置：[0]；默认值：1'0；*/
/*description:设置此位以启用相机模式*/
#define I2S_CAMERA_EN  (BIT(0))
#define I2S_CAMERA_EN_M  (BIT(0))
#define I2S_CAMERA_EN_V  0x1
#define I2S_CAMERA_EN_S  0

#define I2S_CLKM_CONF_REG(i)          (REG_I2S_BASE(i) + 0x00ac)
/* I2S_CLK_SEL:R/W；比特位置：[22:21]；默认值：2’b0；*/
/*description:设置此位以启用clk_apl*/
#define I2S_CLK_SEL  0x00000003
#define I2S_CLK_SEL_M  ((I2S_CLK_SEL_V)<<(I2S_CLK_SEL_S))
#define I2S_CLK_SEL_V  0x3
#define I2S_CLK_SEL_S  21
#define I2S_CLK_AUDIO_PLL 1
#define I2S_CLK_160M_PLL 2
/* I2S_CLK_EN:R/W；位位置：[20]；默认值：1’b0；*/
/*description:设置此位以启用clk门*/
#define I2S_CLK_EN  (BIT(20))
#define I2S_CLK_EN_M  (BIT(20))
#define I2S_CLK_EN_V  0x1
#define I2S_CLK_EN_S  20
/* I2S_CLKM_DIV_A:R/W；比特位置：[19:14]；默认值：6'0；*/
/*description:分数分频器分母值*/
#define I2S_CLKM_DIV_A  0x0000003F
#define I2S_CLKM_DIV_A_M  ((I2S_CLKM_DIV_A_V)<<(I2S_CLKM_DIV_A_S))
#define I2S_CLKM_DIV_A_V  0x3F
#define I2S_CLKM_DIV_A_S  14
/* I2S_CLKM_DIV_B:R/W；比特位置：[13:8]；默认值：6'0；*/
/*description:分数分频器分子值*/
#define I2S_CLKM_DIV_B  0x0000003F
#define I2S_CLKM_DIV_B_M  ((I2S_CLKM_DIV_B_V)<<(I2S_CLKM_DIV_B_S))
#define I2S_CLKM_DIV_B_V  0x3F
#define I2S_CLKM_DIV_B_S  8
/* I2S_CLKM_DIV_NUM:R/W；位位置：[7:0]；默认值：8'd4；*/
/*description:积分I2S时钟分频器值*/
#define I2S_CLKM_DIV_NUM  0x000000FF
#define I2S_CLKM_DIV_NUM_M  ((I2S_CLKM_DIV_NUM_V)<<(I2S_CLKM_DIV_NUM_S))
#define I2S_CLKM_DIV_NUM_V  0xFF
#define I2S_CLKM_DIV_NUM_S  0

#define I2S_SAMPLE_RATE_CONF_REG(i)          (REG_I2S_BASE(i) + 0x00b0)
/* I2S_RX位_模：R/W；比特位置：[23:18]；默认值：6'd16；*/
/*description:设置比特以配置I2S接收器信道的比特长度。*/
#define I2S_RX_BITS_MOD  0x0000003F
#define I2S_RX_BITS_MOD_M  ((I2S_RX_BITS_MOD_V)<<(I2S_RX_BITS_MOD_S))
#define I2S_RX_BITS_MOD_V  0x3F
#define I2S_RX_BITS_MOD_S  18
/* I2S_TX_BITS模式：R/W；比特位置：[17:12]；默认值：6'd16；*/
/*description:设置比特以配置I2S发射机信道的比特长度。*/
#define I2S_TX_BITS_MOD  0x0000003F
#define I2S_TX_BITS_MOD_M  ((I2S_TX_BITS_MOD_V)<<(I2S_TX_BITS_MOD_S))
#define I2S_TX_BITS_MOD_V  0x3F
#define I2S_TX_BITS_MOD_S  12
/* I2S_RX_BCK_DIV_NUM:R/W；位位置：[11:6]；默认值：6'd6；*/
/*description:接收器模式中的位时钟配置位。*/
#define I2S_RX_BCK_DIV_NUM  0x0000003F
#define I2S_RX_BCK_DIV_NUM_M  ((I2S_RX_BCK_DIV_NUM_V)<<(I2S_RX_BCK_DIV_NUM_S))
#define I2S_RX_BCK_DIV_NUM_V  0x3F
#define I2S_RX_BCK_DIV_NUM_S  6
/* I2S_TX_BCK_DIV_NUM:R/W；比特位置：[5:0]；默认值：6'd6；*/
/*description:发射机模式下的位时钟配置位。*/
#define I2S_TX_BCK_DIV_NUM  0x0000003F
#define I2S_TX_BCK_DIV_NUM_M  ((I2S_TX_BCK_DIV_NUM_V)<<(I2S_TX_BCK_DIV_NUM_S))
#define I2S_TX_BCK_DIV_NUM_V  0x3F
#define I2S_TX_BCK_DIV_NUM_S  0

#define I2S_STATE_REG(i)          (REG_I2S_BASE(i) + 0x00bc)
/* I2S_TX_IDLE:RO；位位置：[0]；默认值：1’b1；*/
/*说明：*/
#define I2S_TX_IDLE  (BIT(0))
#define I2S_TX_IDLE_M  (BIT(0))
#define I2S_TX_IDLE_V  0x1
#define I2S_TX_IDLE_S  0

#define I2S_DATE_REG(i)          (REG_I2S_BASE(i) + 0x00fc)
/* I2S_I2SDATE:R/W；位位置：[31:0]；默认值：32'h19052500；*/
/*说明：*/
#define I2S_I2SDATE  0xFFFFFFFF
#define I2S_I2SDATE_M  ((I2S_I2SDATE_V)<<(I2S_I2SDATE_S))
#define I2S_I2SDATE_V  0xFFFFFFFF
#define I2S_I2SDATE_S  0

#ifdef __cplusplus
}
#endif



#endif /*_SOC_I2S_REG_H_ */

