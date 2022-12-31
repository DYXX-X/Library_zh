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
#ifndef _SOC_I2S_REG_H_
#define _SOC_I2S_REG_H_


#ifdef __cplusplus
extern "C" {
#endif
#include "soc.h"
#define I2S_INT_RAW_REG(i)          (REG_I2S_BASE(i) + 0x000c)
/* I2S_TX_HUNG_INT_RAW:RO；位位置：[3]；默认值：1’b0；*/
/*description:i2s_tx_hung_int中断的原始中断状态位*/
#define I2S_TX_HUNG_INT_RAW  (BIT(3))
#define I2S_TX_HUNG_INT_RAW_M  (BIT(3))
#define I2S_TX_HUNG_INT_RAW_V  0x1
#define I2S_TX_HUNG_INT_RAW_S  3
/* I2S_RX-HUNG_INT_RAW:RO；位位置：[2]；默认值：1’b0；*/
/*description:i2s_rx_hung_int中断的原始中断状态位*/
#define I2S_RX_HUNG_INT_RAW  (BIT(2))
#define I2S_RX_HUNG_INT_RAW_M  (BIT(2))
#define I2S_RX_HUNG_INT_RAW_V  0x1
#define I2S_RX_HUNG_INT_RAW_S  2
/* I2S_TX_DONE_INT_RAW:RO；位位置：[1]；默认值：1’b0；*/
/*description:i2s_tx_done_int中断的原始中断状态位*/
#define I2S_TX_DONE_INT_RAW  (BIT(1))
#define I2S_TX_DONE_INT_RAW_M  (BIT(1))
#define I2S_TX_DONE_INT_RAW_V  0x1
#define I2S_TX_DONE_INT_RAW_S  1
/* I2S_RX_DONE_INT_RAW:RO；位位置：[0]；默认值：1’b0；*/
/*description:i2s_rx_done_int中断的原始中断状态位*/
#define I2S_RX_DONE_INT_RAW  (BIT(0))
#define I2S_RX_DONE_INT_RAW_M  (BIT(0))
#define I2S_RX_DONE_INT_RAW_V  0x1
#define I2S_RX_DONE_INT_RAW_S  0

#define I2S_INT_ST_REG(i)          (REG_I2S_BASE(i) + 0x0010)
/* I2S_TX_HUNG_INT_ST:RO；位位置：[3]；默认值：1’b0；*/
/*description:i2s_tx_hung_int中断的屏蔽中断状态位*/
#define I2S_TX_HUNG_INT_ST  (BIT(3))
#define I2S_TX_HUNG_INT_ST_M  (BIT(3))
#define I2S_TX_HUNG_INT_ST_V  0x1
#define I2S_TX_HUNG_INT_ST_S  3
/* I2S_RX-HUNG_INT_ST:RO；位位置：[2]；默认值：1’b0；*/
/*description:i2s_rx_hung_int中断的屏蔽中断状态位*/
#define I2S_RX_HUNG_INT_ST  (BIT(2))
#define I2S_RX_HUNG_INT_ST_M  (BIT(2))
#define I2S_RX_HUNG_INT_ST_V  0x1
#define I2S_RX_HUNG_INT_ST_S  2
/* I2S_TX_DONE_INT_ST:RO；位位置：[1]；默认值：1’b0；*/
/*description:i2s_tx_done_int中断的屏蔽中断状态位*/
#define I2S_TX_DONE_INT_ST  (BIT(1))
#define I2S_TX_DONE_INT_ST_M  (BIT(1))
#define I2S_TX_DONE_INT_ST_V  0x1
#define I2S_TX_DONE_INT_ST_S  1
/* I2S_RX完成时间：RO；位位置：[0]；默认值：1’b0；*/
/*description:i2s_rx_done_int中断的屏蔽中断状态位*/
#define I2S_RX_DONE_INT_ST  (BIT(0))
#define I2S_RX_DONE_INT_ST_M  (BIT(0))
#define I2S_RX_DONE_INT_ST_V  0x1
#define I2S_RX_DONE_INT_ST_S  0

#define I2S_INT_ENA_REG(i)          (REG_I2S_BASE(i) + 0x0014)
/* I2S_TX_HUNG_INT_ENA:R/W；位位置：[3]；默认值：1’b0；*/
/*description:i2s_tx_hung_int中断的中断启用位*/
#define I2S_TX_HUNG_INT_ENA  (BIT(3))
#define I2S_TX_HUNG_INT_ENA_M  (BIT(3))
#define I2S_TX_HUNG_INT_ENA_V  0x1
#define I2S_TX_HUNG_INT_ENA_S  3
/* I2S_RX-HUNG_INT_ENA:R/W；位位置：[2]；默认值：1’b0；*/
/*description:i2s_rx_hung_int中断的中断启用位*/
#define I2S_RX_HUNG_INT_ENA  (BIT(2))
#define I2S_RX_HUNG_INT_ENA_M  (BIT(2))
#define I2S_RX_HUNG_INT_ENA_V  0x1
#define I2S_RX_HUNG_INT_ENA_S  2
/* I2S_TX_DONE_INT_ENA:R/W；位位置：[1]；默认值：1’b0；*/
/*description:i2s_tx_done_int中断的中断启用位*/
#define I2S_TX_DONE_INT_ENA  (BIT(1))
#define I2S_TX_DONE_INT_ENA_M  (BIT(1))
#define I2S_TX_DONE_INT_ENA_V  0x1
#define I2S_TX_DONE_INT_ENA_S  1
/* I2S_RX_DONE_INT_ENA:R/W；位位置：[0]；默认值：1’b0；*/
/*description:i2s_rx_done_int中断的中断启用位*/
#define I2S_RX_DONE_INT_ENA  (BIT(0))
#define I2S_RX_DONE_INT_ENA_M  (BIT(0))
#define I2S_RX_DONE_INT_ENA_V  0x1
#define I2S_RX_DONE_INT_ENA_S  0

#define I2S_INT_CLR_REG(i)          (REG_I2S_BASE(i) + 0x0018)
/* I2S_TX_HUNG_INT_CLR:WO；位位置：[3]；默认值：1’b0；*/
/*description:设置此位以清除i2s_tx_hung_int中断*/
#define I2S_TX_HUNG_INT_CLR  (BIT(3))
#define I2S_TX_HUNG_INT_CLR_M  (BIT(3))
#define I2S_TX_HUNG_INT_CLR_V  0x1
#define I2S_TX_HUNG_INT_CLR_S  3
/* I2S_RX-HUNG_INT_CLR:WO；位位置：[2]；默认值：1’b0；*/
/*description:设置此位以清除i2s_rx_hung_int中断*/
#define I2S_RX_HUNG_INT_CLR  (BIT(2))
#define I2S_RX_HUNG_INT_CLR_M  (BIT(2))
#define I2S_RX_HUNG_INT_CLR_V  0x1
#define I2S_RX_HUNG_INT_CLR_S  2
/* I2S_TX_DONE_INT_CLR:WO；位位置：[1]；默认值：1’b0；*/
/*description:设置此位以清除i2s_tx_done_int中断*/
#define I2S_TX_DONE_INT_CLR  (BIT(1))
#define I2S_TX_DONE_INT_CLR_M  (BIT(1))
#define I2S_TX_DONE_INT_CLR_V  0x1
#define I2S_TX_DONE_INT_CLR_S  1
/* I2S_RX_完成_时间CLR:WO；位位置：[0]；默认值：1’b0；*/
/*description:设置此位以清除i2s_rx_done_int中断*/
#define I2S_RX_DONE_INT_CLR  (BIT(0))
#define I2S_RX_DONE_INT_CLR_M  (BIT(0))
#define I2S_RX_DONE_INT_CLR_V  0x1
#define I2S_RX_DONE_INT_CLR_S  0

#define I2S_RX_CONF_REG(i)          (REG_I2S_BASE(i) + 0x0020)
/* I2S_RX_PDM_EN:R/W；位位置：[20]；默认值：1'0；*/
/*description:1:启用I2S PDM Rx模式。0:禁用。*/
#define I2S_RX_PDM_EN  (BIT(20))
#define I2S_RX_PDM_EN_M  (BIT(20))
#define I2S_RX_PDM_EN_V  0x1
#define I2S_RX_PDM_EN_S  20
/* I2S_RX_TDM_EN:R/W；位位置：[19]；默认值：1'0；*/
/*description:1:启用I2S TDM Rx模式。0:禁用。*/
#define I2S_RX_TDM_EN  (BIT(19))
#define I2S_RX_TDM_EN_M  (BIT(19))
#define I2S_RX_TDM_EN_V  0x1
#define I2S_RX_TDM_EN_S  19
/* I2S_RX位顺序：R/W；位位置：[18]；默认值：1'0；*/
/*description:I2S Rx位尾数。1： 首先接收LSB的小端。0:首先接收MSB的大端。*/
#define I2S_RX_BIT_ORDER  (BIT(18))
#define I2S_RX_BIT_ORDER_M  (BIT(18))
#define I2S_RX_BIT_ORDER_V  0x1
#define I2S_RX_BIT_ORDER_S  18
/* I2S_RX_WS_IDLE_POL:R/W；位位置：[17]；默认值：1'0；*/
/*描述：0:WS在接收左通道数据时应为0，而WS在右通道中为1。1： 当接收左声道数据时，WS应为1，而右声道中WS应为0。*/
#define I2S_RX_WS_IDLE_POL  (BIT(17))
#define I2S_RX_WS_IDLE_POL_M  (BIT(17))
#define I2S_RX_WS_IDLE_POL_V  0x1
#define I2S_RX_WS_IDLE_POL_S  17
/* I2S_RX-24_照明：R/W；位位置：[16]；默认值：1'0；*/
/*描述：1：存储24通道位到32位。0：存储24个通道位到24个位。*/
#define I2S_RX_24_FILL_EN  (BIT(16))
#define I2S_RX_24_FILL_EN_M  (BIT(16))
#define I2S_RX_24_FILL_EN_V  0x1
#define I2S_RX_24_FILL_EN_S  16
/* I2S_RX左对齐：R/W；位位置：[15]；默认值：1’b1；*/
/*描述：1:I2S RX左对齐模式。0:I2S RX右对齐模式。*/
#define I2S_RX_LEFT_ALIGN  (BIT(15))
#define I2S_RX_LEFT_ALIGN_M  (BIT(15))
#define I2S_RX_LEFT_ALIGN_V  0x1
#define I2S_RX_LEFT_ALIGN_S  15
/* I2S_RX停止模式：R/W；比特位置：[14:13]；默认值：2'd0；*/
/*描述：0:I2S Rx仅在清除reg_Rx_start时停止。1： 当reg_rx_start为0或in_suc_eof为1时停止。2：当reg_rx.start为0或者rx FIFO已满时停止I2S rx。*/
#define I2S_RX_STOP_MODE  0x00000003
#define I2S_RX_STOP_MODE_M  ((I2S_RX_STOP_MODE_V)<<(I2S_RX_STOP_MODE_S))
#define I2S_RX_STOP_MODE_V  0x3
#define I2S_RX_STOP_MODE_S  13
/* I2S_rxpcm_BYPASS:R/W；位位置：[12]；默认值：1'h1；*/
/*description:设置此位以绕过接收数据的压缩/解压缩模块。*/
#define I2S_RX_PCM_BYPASS  (BIT(12))
#define I2S_RX_PCM_BYPASS_M  (BIT(12))
#define I2S_RX_PCM_BYPASS_V  0x1
#define I2S_RX_PCM_BYPASS_S  12
/* I2S_rxpcm_CONF:R/W；比特位置：[11:10]；默认值：2'h1；*/
/*描述：I2S RX压缩/解压缩配置位。&0（环礁）：A-Law解压缩1（ltoa）：A-Law压缩2（utol）：u-Law解压缩3（ltou）：u-Law压缩&*/
#define I2S_RX_PCM_CONF  0x00000003
#define I2S_RX_PCM_CONF_M  ((I2S_RX_PCM_CONF_V)<<(I2S_RX_PCM_CONF_S))
#define I2S_RX_PCM_CONF_V  0x3
#define I2S_RX_PCM_CONF_S  10
/* I2S_RX_mone_FST_VLD:R/W；位位置：[9]；默认值：1’b1；*/
/*description:1：第一个信道数据值在I2S RX单声道模式下有效。0：第二个信道数据值在I2S RX单声道模式下有效。*/
#define I2S_RX_MONO_FST_VLD  (BIT(9))
#define I2S_RX_MONO_FST_VLD_M  (BIT(9))
#define I2S_RX_MONO_FST_VLD_V  0x1
#define I2S_RX_MONO_FST_VLD_S  9
/* I2S_RX更新：R/W；位位置：[8]；默认值：1’b0；*/
/*description:设置1以将I2S RX寄存器从APB时钟域更新到I2S RX时钟域。更新寄存器完成后，硬件将清除该位。*/
#define I2S_RX_UPDATE  (BIT(8))
#define I2S_RX_UPDATE_M  (BIT(8))
#define I2S_RX_UPDATE_V  0x1
#define I2S_RX_UPDATE_S  8
/* I2S_RX_BIG_ENDIAN:R/W；位位置：[7]；默认值：1’b0；*/
/*描述：I2S Rx字节端1：低地址值到高地址。0：地址值低的低地址。*/
#define I2S_RX_BIG_ENDIAN  (BIT(7))
#define I2S_RX_BIG_ENDIAN_M  (BIT(7))
#define I2S_RX_BIG_ENDIAN_V  0x1
#define I2S_RX_BIG_ENDIAN_S  7
/* I2S_RX单声道：R/W；位位置：[5]；默认值：1’b0；*/
/*description:设置此位以启用单声道模式下的接收器*/
#define I2S_RX_MONO  (BIT(5))
#define I2S_RX_MONO_M  (BIT(5))
#define I2S_RX_MONO_V  0x1
#define I2S_RX_MONO_S  5
/* I2S_RX_SLAVE-MOD:R/W；位位置：[3]；默认值：1’b0；*/
/*description:设置此位以启用从属接收器模式*/
#define I2S_RX_SLAVE_MOD  (BIT(3))
#define I2S_RX_SLAVE_MOD_M  (BIT(3))
#define I2S_RX_SLAVE_MOD_V  0x1
#define I2S_RX_SLAVE_MOD_S  3
/* I2S_RX启动：R/W；位位置：[2]；默认值：1’b0；*/
/*description:设置此位以开始接收数据*/
#define I2S_RX_START  (BIT(2))
#define I2S_RX_START_M  (BIT(2))
#define I2S_RX_START_V  0x1
#define I2S_RX_START_S  2
/* I2S_RX_FIFO_RESET:WO；位位置：[1]；默认值：1’b0；*/
/*description:设置此位以重置Rx AFIFO*/
#define I2S_RX_FIFO_RESET  (BIT(1))
#define I2S_RX_FIFO_RESET_M  (BIT(1))
#define I2S_RX_FIFO_RESET_V  0x1
#define I2S_RX_FIFO_RESET_S  1
/* I2S_RX重置：WO；位位置：[0]；默认值：1’b0；*/
/*description:设置此位以重置接收器*/
#define I2S_RX_RESET  (BIT(0))
#define I2S_RX_RESET_M  (BIT(0))
#define I2S_RX_RESET_V  0x1
#define I2S_RX_RESET_S  0

#define I2S_TX_CONF_REG(i)          (REG_I2S_BASE(i) + 0x0024)
/* I2S_SIG_LOOPBACK:R/W；位位置：[27]；默认值：1’b0；*/
/*描述：启用信号环回模式，发射器模块和接收器模块共享相同的WS和BCK信号。*/
#define I2S_SIG_LOOPBACK  (BIT(27))
#define I2S_SIG_LOOPBACK_M  (BIT(27))
#define I2S_SIG_LOOPBACK_V  0x1
#define I2S_SIG_LOOPBACK_S  27
/* I2S_TX_CHAN模式：R/W；比特位置：[26:24]；默认值：3'b0；*/
/*描述：I2S发射机信道模式配置位。*/
#define I2S_TX_CHAN_MOD  0x00000007
#define I2S_TX_CHAN_MOD_M  ((I2S_TX_CHAN_MOD_V)<<(I2S_TX_CHAN_MOD_S))
#define I2S_TX_CHAN_MOD_V  0x7
#define I2S_TX_CHAN_MOD_S  24
/* I2S_TX_PDM_EN:R/W；位位置：[20]；默认值：1'0；*/
/*description:1:启用I2S PDM Tx模式。0:禁用。*/
#define I2S_TX_PDM_EN  (BIT(20))
#define I2S_TX_PDM_EN_M  (BIT(20))
#define I2S_TX_PDM_EN_V  0x1
#define I2S_TX_PDM_EN_S  20
/* I2S_TX_TDM_EN:R/W；位位置：[19]；默认值：1'0；*/
/*description:1:启用I2S TDM Tx模式。0:禁用。*/
#define I2S_TX_TDM_EN  (BIT(19))
#define I2S_TX_TDM_EN_M  (BIT(19))
#define I2S_TX_TDM_EN_V  0x1
#define I2S_TX_TDM_EN_S  19
/* I2S_TX_BIT_ORDER:R/W；位位置：[18]；默认值：1'0；*/
/*description:I2S Tx位端。1： 首先发送LSB的小端。0:首先发送MSB的大端。*/
#define I2S_TX_BIT_ORDER  (BIT(18))
#define I2S_TX_BIT_ORDER_M  (BIT(18))
#define I2S_TX_BIT_ORDER_V  0x1
#define I2S_TX_BIT_ORDER_S  18
/* I2S_TX_WS_IDLE_POL:R/W；位位置：[17]；默认值：1'0；*/
/*描述：0:发送左通道数据时WS应为0，右通道中WS为1。1： 发送左通道数据时WS应为1，右通道中WS应为0。*/
#define I2S_TX_WS_IDLE_POL  (BIT(17))
#define I2S_TX_WS_IDLE_POL_M  (BIT(17))
#define I2S_TX_WS_IDLE_POL_V  0x1
#define I2S_TX_WS_IDLE_POL_S  17
/* I2S_TX_24_FILL_EN:R/W；位位置：[16]；默认值：1'0；*/
/*description:1：以24通道位模式发送32位。0：以24通道位模式发送24位*/
#define I2S_TX_24_FILL_EN  (BIT(16))
#define I2S_TX_24_FILL_EN_M  (BIT(16))
#define I2S_TX_24_FILL_EN_V  0x1
#define I2S_TX_24_FILL_EN_S  16
/* I2S_TX_LEFT_ALIGN:R/W；位位置：[15]；默认值：1'h1；*/
/*描述：1:I2S TX左对齐模式。0:I2S TX右对齐模式。*/
#define I2S_TX_LEFT_ALIGN  (BIT(15))
#define I2S_TX_LEFT_ALIGN_M  (BIT(15))
#define I2S_TX_LEFT_ALIGN_V  0x1
#define I2S_TX_LEFT_ALIGN_S  15
/* I2S_TX_STOP_EN:R/W；位位置：[13]；默认值：1'h1；*/
/*description:当tx FIFO为emtpy时，设置此位以停止禁用输出BCK信号和WS信号*/
#define I2S_TX_STOP_EN  (BIT(13))
#define I2S_TX_STOP_EN_M  (BIT(13))
#define I2S_TX_STOP_EN_V  0x1
#define I2S_TX_STOP_EN_S  13
/* I2S_TX_PCM_BYPASS:R/W；位位置：[12]；默认值：1'h1；*/
/*description:设置此位以绕过传输数据的压缩/解压缩模块。*/
#define I2S_TX_PCM_BYPASS  (BIT(12))
#define I2S_TX_PCM_BYPASS_M  (BIT(12))
#define I2S_TX_PCM_BYPASS_V  0x1
#define I2S_TX_PCM_BYPASS_S  12
/* I2S_TX_PCM_CONF:R/W；比特位置：[11:10]；默认值：2'h0；*/
/*描述：I2S TX压缩/解压缩配置位。&0（环礁）：A-Law解压缩1（ltoa）：A-Law压缩2（utol）：u-Law解压缩3（ltou）：u-Law压缩&*/
#define I2S_TX_PCM_CONF  0x00000003
#define I2S_TX_PCM_CONF_M  ((I2S_TX_PCM_CONF_V)<<(I2S_TX_PCM_CONF_S))
#define I2S_TX_PCM_CONF_V  0x3
#define I2S_TX_PCM_CONF_S  10
/* I2S_TX_MONO_FST_VLD:R/W；位位置：[9]；默认值：1’b1；*/
/*description:1：第一个信道数据值在I2S TX单声道模式下有效。0：第二个信道数据值在I2S TX单声道模式下有效。*/
#define I2S_TX_MONO_FST_VLD  (BIT(9))
#define I2S_TX_MONO_FST_VLD_M  (BIT(9))
#define I2S_TX_MONO_FST_VLD_V  0x1
#define I2S_TX_MONO_FST_VLD_S  9
/* I2S_TX_UPDATE:R/W；位位置：[8]；默认值：1’b0；*/
/*description:设置1以将I2S TX寄存器从APB时钟域更新到I2S TX时钟域。更新寄存器完成后，硬件将清除该位。*/
#define I2S_TX_UPDATE  (BIT(8))
#define I2S_TX_UPDATE_M  (BIT(8))
#define I2S_TX_UPDATE_V  0x1
#define I2S_TX_UPDATE_S  8
/* I2S_TX_BIG_ENDIAN:R/W；位位置：[7]；默认值：1’b0；*/
/*描述：I2S Tx字节端1：低地址值到高地址。0：地址值低的低地址。*/
#define I2S_TX_BIG_ENDIAN  (BIT(7))
#define I2S_TX_BIG_ENDIAN_M  (BIT(7))
#define I2S_TX_BIG_ENDIAN_V  0x1
#define I2S_TX_BIG_ENDIAN_S  7
/* I2S_TX_CHAN_EQUAL:R/W；位位置：[6]；默认值：1’b0；*/
/*description:1：在I2S TX单声道模式或TDM信道选择模式下，左声道数据的值等于右声道数据的。0：在i2s TX单声道模式或TDM信道选择模式下，无效信道数据为reg_i2s_single_data。*/
#define I2S_TX_CHAN_EQUAL  (BIT(6))
#define I2S_TX_CHAN_EQUAL_M  (BIT(6))
#define I2S_TX_CHAN_EQUAL_V  0x1
#define I2S_TX_CHAN_EQUAL_S  6
/* I2S_TX_MONO:R/W；位位置：[5]；默认值：1’b0；*/
/*description:设置此位以启用单声道模式下的发射器*/
#define I2S_TX_MONO  (BIT(5))
#define I2S_TX_MONO_M  (BIT(5))
#define I2S_TX_MONO_V  0x1
#define I2S_TX_MONO_S  5
/* I2S_TX_SLAVE_mode:R/W；位位置：[3]；默认值：1’b0；*/
/*description:设置此位以启用从发射机模式*/
#define I2S_TX_SLAVE_MOD  (BIT(3))
#define I2S_TX_SLAVE_MOD_M  (BIT(3))
#define I2S_TX_SLAVE_MOD_V  0x1
#define I2S_TX_SLAVE_MOD_S  3
/* I2S_TX_START:R/W；位位置：[2]；默认值：1’b0；*/
/*description:设置此位以开始传输数据*/
#define I2S_TX_START  (BIT(2))
#define I2S_TX_START_M  (BIT(2))
#define I2S_TX_START_V  0x1
#define I2S_TX_START_S  2
/* I2S_TX_FIFO_RESET:WO；位位置：[1]；默认值：1’b0；*/
/*description:设置此位以重置Tx AFIFO*/
#define I2S_TX_FIFO_RESET  (BIT(1))
#define I2S_TX_FIFO_RESET_M  (BIT(1))
#define I2S_TX_FIFO_RESET_V  0x1
#define I2S_TX_FIFO_RESET_S  1
/* I2S_TX_RESET:WO；位位置：[0]；默认值：1’b0；*/
/*description:设置此位重置变送器*/
#define I2S_TX_RESET  (BIT(0))
#define I2S_TX_RESET_M  (BIT(0))
#define I2S_TX_RESET_V  0x1
#define I2S_TX_RESET_S  0

#define I2S_RX_CONF1_REG(i)          (REG_I2S_BASE(i) + 0x0028)
/* I2S_RX_MSB_SHIFT:R/W；位位置：[29]；默认值：1’b1；*/
/*description:设置此位以启用菲利普斯标准模式下的接收器*/
#define I2S_RX_MSB_SHIFT  (BIT(29))
#define I2S_RX_MSB_SHIFT_M  (BIT(29))
#define I2S_RX_MSB_SHIFT_V  0x1
#define I2S_RX_MSB_SHIFT_S  29
/* I2S_RX_TDM_CHAN_BITS：R/W；位位置：[28:24]；默认值：5'hF；*/
/*description:TDM模式下每个信道的Rx位数减去1。*/
#define I2S_RX_TDM_CHAN_BITS  0x0000001F
#define I2S_RX_TDM_CHAN_BITS_M  ((I2S_RX_TDM_CHAN_BITS_V)<<(I2S_RX_TDM_CHAN_BITS_S))
#define I2S_RX_TDM_CHAN_BITS_V  0x1F
#define I2S_RX_TDM_CHAN_BITS_S  24
/* I2S_RX_半采样位：R/W；比特位置：[23:18]；默认值：6'hF；*/
/*描述：I2S Rx半采样位-1。*/
#define I2S_RX_HALF_SAMPLE_BITS  0x0000003F
#define I2S_RX_HALF_SAMPLE_BITS_M  ((I2S_RX_HALF_SAMPLE_BITS_V)<<(I2S_RX_HALF_SAMPLE_BITS_S))
#define I2S_RX_HALF_SAMPLE_BITS_V  0x3F
#define I2S_RX_HALF_SAMPLE_BITS_S  18
/* I2S_RX位_模：R/W；比特位置：[17:13]；默认值：5'hF；*/
/*description:设置比特以配置I2S接收器信道的比特长度。*/
#define I2S_RX_BITS_MOD  0x0000001F
#define I2S_RX_BITS_MOD_M  ((I2S_RX_BITS_MOD_V)<<(I2S_RX_BITS_MOD_S))
#define I2S_RX_BITS_MOD_V  0x1F
#define I2S_RX_BITS_MOD_S  13
/* I2S_RX_BCK_DIV_NUM:R/W；比特位置：[12:7]；默认值：6'd6；*/
/*description:接收器模式中的位时钟配置位。*/
#define I2S_RX_BCK_DIV_NUM  0x0000003F
#define I2S_RX_BCK_DIV_NUM_M  ((I2S_RX_BCK_DIV_NUM_V)<<(I2S_RX_BCK_DIV_NUM_S))
#define I2S_RX_BCK_DIV_NUM_V  0x3F
#define I2S_RX_BCK_DIV_NUM_S  7
/* I2S_RX_TDM-WS_WIDTH:R/W；比特位置：[6:0]；默认值：7'0；*/
/*描述：TDM模式下rx_ws_out的宽度为（reg_rx_TDM_ws_width[6:0]+1）*T_bck*/
#define I2S_RX_TDM_WS_WIDTH  0x0000007F
#define I2S_RX_TDM_WS_WIDTH_M  ((I2S_RX_TDM_WS_WIDTH_V)<<(I2S_RX_TDM_WS_WIDTH_S))
#define I2S_RX_TDM_WS_WIDTH_V  0x7F
#define I2S_RX_TDM_WS_WIDTH_S  0

#define I2S_TX_CONF1_REG(i)          (REG_I2S_BASE(i) + 0x002C)
/* I2S_TX_MSB_SHIFT:R/W；位位置：[29]；默认值：1’b1；*/
/*description:设置此位以启用菲利普斯标准模式下的变送器*/
#define I2S_TX_MSB_SHIFT  (BIT(29))
#define I2S_TX_MSB_SHIFT_M  (BIT(29))
#define I2S_TX_MSB_SHIFT_V  0x1
#define I2S_TX_MSB_SHIFT_S  29
/* I2S_TX_TDM_CHAN_BITS：R/W；位位置：[28:24]；默认值：5'hF；*/
/*description:TDM模式下每个信道的Tx位数减去1。*/
#define I2S_TX_TDM_CHAN_BITS  0x0000001F
#define I2S_TX_TDM_CHAN_BITS_M  ((I2S_TX_TDM_CHAN_BITS_V)<<(I2S_TX_TDM_CHAN_BITS_S))
#define I2S_TX_TDM_CHAN_BITS_V  0x1F
#define I2S_TX_TDM_CHAN_BITS_S  24
/* I2S_TX_HALF_SAMPLE_BITS：R/W；比特位置：[23:18]；默认值：6'hF；*/
/*描述：I2S Tx半采样位-1。*/
#define I2S_TX_HALF_SAMPLE_BITS  0x0000003F
#define I2S_TX_HALF_SAMPLE_BITS_M  ((I2S_TX_HALF_SAMPLE_BITS_V)<<(I2S_TX_HALF_SAMPLE_BITS_S))
#define I2S_TX_HALF_SAMPLE_BITS_V  0x3F
#define I2S_TX_HALF_SAMPLE_BITS_S  18
/* I2S_TX_BITS模式：R/W；比特位置：[17:13]；默认值：5'hF；*/
/*description:设置比特以配置I2S发射机信道的比特长度。*/
#define I2S_TX_BITS_MOD  0x0000001F
#define I2S_TX_BITS_MOD_M  ((I2S_TX_BITS_MOD_V)<<(I2S_TX_BITS_MOD_S))
#define I2S_TX_BITS_MOD_V  0x1F
#define I2S_TX_BITS_MOD_S  13
/* I2S_TX_BCK_DIV_NUM:R/W；比特位置：[12:7]；默认值：6'd6；*/
/*description:发射机模式下的位时钟配置位。*/
#define I2S_TX_BCK_DIV_NUM  0x0000003F
#define I2S_TX_BCK_DIV_NUM_M  ((I2S_TX_BCK_DIV_NUM_V)<<(I2S_TX_BCK_DIV_NUM_S))
#define I2S_TX_BCK_DIV_NUM_V  0x3F
#define I2S_TX_BCK_DIV_NUM_S  7
/* I2S_TX_TDM_WS_WIDTH:R/W；比特位置：[6:0]；默认值：7'0；*/
/*description:TDM模式下tx_ws_out的宽度为（reg_tx_TDM_ws_width[6:0]+1）*T_bck*/
#define I2S_TX_TDM_WS_WIDTH  0x0000007F
#define I2S_TX_TDM_WS_WIDTH_M  ((I2S_TX_TDM_WS_WIDTH_V)<<(I2S_TX_TDM_WS_WIDTH_S))
#define I2S_TX_TDM_WS_WIDTH_V  0x7F
#define I2S_TX_TDM_WS_WIDTH_S  0

#define I2S_RX_CLKM_CONF_REG(i)          (REG_I2S_BASE(i) + 0x0030)
/* I2S_MCLK_SEL:R/W；位位置：[29]；默认值：1’b0；*/
/*description:0：将I2S Tx模块时钟用作I2S_MCLK_OUT。1： 使用I2S Rx模块时钟作为I2S_MCLK_OUT。*/
#define I2S_MCLK_SEL  (BIT(29))
#define I2S_MCLK_SEL_M  (BIT(29))
#define I2S_MCLK_SEL_V  0x1
#define I2S_MCLK_SEL_S  29
/* I2S_RX_CLK_SEL:R/W；位位置：[28:27]；默认值：2’b0；*/
/*description:选择I2S Rx模块源时钟。0：无时钟。1： 应用程序。2： CLK160.3:I2S_MCLK_in。*/
#define I2S_RX_CLK_SEL  0x00000003
#define I2S_RX_CLK_SEL_M  ((I2S_RX_CLK_SEL_V)<<(I2S_RX_CLK_SEL_S))
#define I2S_RX_CLK_SEL_V  0x3
#define I2S_RX_CLK_SEL_S  27
/* I2S_RX_CLK_ACTIVE:R/W；位位置：[26]；默认值：1’b0；*/
/*描述：I2S Rx模块时钟启用信号。*/
#define I2S_RX_CLK_ACTIVE  (BIT(26))
#define I2S_RX_CLK_ACTIVE_M  (BIT(26))
#define I2S_RX_CLK_ACTIVE_V  0x1
#define I2S_RX_CLK_ACTIVE_S  26
/* I2S_RX_CLKM_DIV_NUM:R/W；位位置：[7:0]；默认值：8'd2；*/
/*description:积分I2S时钟分频器值*/
#define I2S_RX_CLKM_DIV_NUM  0x000000FF
#define I2S_RX_CLKM_DIV_NUM_M  ((I2S_RX_CLKM_DIV_NUM_V)<<(I2S_RX_CLKM_DIV_NUM_S))
#define I2S_RX_CLKM_DIV_NUM_V  0xFF
#define I2S_RX_CLKM_DIV_NUM_S  0

#define I2S_TX_CLKM_CONF_REG(i)          (REG_I2S_BASE(i) + 0x0034)
/* I2S_CLK_EN:R/W；位位置：[29]；默认值：1’b0；*/
/*description:设置此位以启用clk门*/
#define I2S_CLK_EN  (BIT(29))
#define I2S_CLK_EN_M  (BIT(29))
#define I2S_CLK_EN_V  0x1
#define I2S_CLK_EN_S  29
/* I2S_TX_CLK_SEL:R/W；位位置：[28:27]；默认值：2’b0；*/
/*description:选择I2S Tx模块源时钟。0:XTAL时钟。1： 应用程序。2： CLK160.3:I2S_MCLK_in。*/
#define I2S_TX_CLK_SEL  0x00000003
#define I2S_TX_CLK_SEL_M  ((I2S_TX_CLK_SEL_V)<<(I2S_TX_CLK_SEL_S))
#define I2S_TX_CLK_SEL_V  0x3
#define I2S_TX_CLK_SEL_S  27
/* I2S_TX_CLK_ACTIVE:R/W；位位置：[26]；默认值：1’b0；*/
/*描述：I2S Tx模块时钟启用信号。*/
#define I2S_TX_CLK_ACTIVE  (BIT(26))
#define I2S_TX_CLK_ACTIVE_M  (BIT(26))
#define I2S_TX_CLK_ACTIVE_V  0x1
#define I2S_TX_CLK_ACTIVE_S  26
/* I2S_TX_CLKM_DIV_NUM:R/W；位位置：[7:0]；默认值：8'd2；*/
/*description:积分I2S TX时钟分频器值。f_ I2S_CLK＝f_。将有（a-b）n-div和b*（n+1）-div。因此，平均组合将是：对于b<=a/2z*[x*n-div+（n+1）-div]+y*n-div。对于b>a/2z*[n-div+x*（n+1）-div]+y*（n+2）-div。*/
#define I2S_TX_CLKM_DIV_NUM  0x000000FF
#define I2S_TX_CLKM_DIV_NUM_M  ((I2S_TX_CLKM_DIV_NUM_V)<<(I2S_TX_CLKM_DIV_NUM_S))
#define I2S_TX_CLKM_DIV_NUM_V  0xFF
#define I2S_TX_CLKM_DIV_NUM_S  0

#define I2S_RX_CLKM_DIV_CONF_REG(i)          (REG_I2S_BASE(i) + 0x0038)
/* I2S_RX_CLKM_DIV_YN1:R/W；位位置：[27]；默认值：1’b0；*/
/*description:对于b<=a/2，I2S_RX_CLKM_DIV_YN1的值为0。对于b>a/2，I2S_RX_CLKM_DIV_SYN1的值是1。*/
#define I2S_RX_CLKM_DIV_YN1  (BIT(27))
#define I2S_RX_CLKM_DIV_YN1_M  (BIT(27))
#define I2S_RX_CLKM_DIV_YN1_V  0x1
#define I2S_RX_CLKM_DIV_YN1_S  27
/* I2S_RX_CLKM_DIV_X:R/W；比特位置：[26:18]；默认值：9'0；*/
/*描述：对于b<=a/2，I2S_RX_CLKM_DIV_X的值为（a/b）-1。对于b>a/2，则I2S_RX_COLKM_DIF_X的值是（a/（a-b））-1。*/
#define I2S_RX_CLKM_DIV_X  0x000001FF
#define I2S_RX_CLKM_DIV_X_M  ((I2S_RX_CLKM_DIV_X_V)<<(I2S_RX_CLKM_DIV_X_S))
#define I2S_RX_CLKM_DIV_X_V  0x1FF
#define I2S_RX_CLKM_DIV_X_S  18
/* I2S_RX_CLKM_DIV_Y：R/W；比特位置：[17:9]；默认值：9'h1；*/
/*描述：对于b<=a/2，I2S_RX_CLKM_DIV_Y的值为（a%b）。对于b>a/2，则I2S_RX_COLKM_DIF_Y的值是（a%（a-b））。*/
#define I2S_RX_CLKM_DIV_Y  0x000001FF
#define I2S_RX_CLKM_DIV_Y_M  ((I2S_RX_CLKM_DIV_Y_V)<<(I2S_RX_CLKM_DIV_Y_S))
#define I2S_RX_CLKM_DIV_Y_V  0x1FF
#define I2S_RX_CLKM_DIV_Y_S  9
/* I2S_RX_CLKM_DIV_Z:R/W；位位置：[8:0]；默认值：9'0；*/
/*description:对于b<=a/2，I2S_RX_CLKM_DIV_Z的值为b。对于b>a/2，则I2S_RX_COLKM_DIF_Z的值是（a-b）。*/
#define I2S_RX_CLKM_DIV_Z  0x000001FF
#define I2S_RX_CLKM_DIV_Z_M  ((I2S_RX_CLKM_DIV_Z_V)<<(I2S_RX_CLKM_DIV_Z_S))
#define I2S_RX_CLKM_DIV_Z_V  0x1FF
#define I2S_RX_CLKM_DIV_Z_S  0

#define I2S_TX_CLKM_DIV_CONF_REG(i)          (REG_I2S_BASE(i) + 0x003C)
/* I2S_TX_CLKM_DIV_YN1:R/W；位位置：[27]；默认值：1’b0；*/
/*description:对于b<=a/2，I2S_TX_CLKM_DIV_YN1的值为0。对于b>a/2，12S_TX_CLKM_DIV_SYN1的值是1。*/
#define I2S_TX_CLKM_DIV_YN1  (BIT(27))
#define I2S_TX_CLKM_DIV_YN1_M  (BIT(27))
#define I2S_TX_CLKM_DIV_YN1_V  0x1
#define I2S_TX_CLKM_DIV_YN1_S  27
/* I2S_TX_CLKM_DIV_X:R/W；比特位置：[26:18]；默认值：9'0；*/
/*description:对于b<=a/2，I2S_TX_CLKM_DIV_X的值为（a/b）-1。对于b>a/2，则I2S_TX-CLKM_DIF_X的值是（a/（a-b））-1。*/
#define I2S_TX_CLKM_DIV_X  0x000001FF
#define I2S_TX_CLKM_DIV_X_M  ((I2S_TX_CLKM_DIV_X_V)<<(I2S_TX_CLKM_DIV_X_S))
#define I2S_TX_CLKM_DIV_X_V  0x1FF
#define I2S_TX_CLKM_DIV_X_S  18
/* I2S_TX_CLKM_DIV_Y：R/W；比特位置：[17:9]；默认值：9'h1；*/
/*description:对于b<=a/2，I2S_TX_CLKM_DIV_Y的值为（a%b）。对于b>a/2，则I2S_TX-CLKM_DIV_Y的值是（a%（a-b））。*/
#define I2S_TX_CLKM_DIV_Y  0x000001FF
#define I2S_TX_CLKM_DIV_Y_M  ((I2S_TX_CLKM_DIV_Y_V)<<(I2S_TX_CLKM_DIV_Y_S))
#define I2S_TX_CLKM_DIV_Y_V  0x1FF
#define I2S_TX_CLKM_DIV_Y_S  9
/* I2S_TX_CLKM_DIV_Z:R/W；位位置：[8:0]；默认值：9'0；*/
/*description:对于b<=a/2，I2S_TX_CLKM_DIV_Z的值为b。对于b>a/2，则I2S_TX-CLKM_DIV_Z的值是（a-b）。*/
#define I2S_TX_CLKM_DIV_Z  0x000001FF
#define I2S_TX_CLKM_DIV_Z_M  ((I2S_TX_CLKM_DIV_Z_V)<<(I2S_TX_CLKM_DIV_Z_S))
#define I2S_TX_CLKM_DIV_Z_V  0x1FF
#define I2S_TX_CLKM_DIV_Z_S  0

#define I2S_TX_PCM2PDM_CONF_REG(i)          (REG_I2S_BASE(i) + 0x040)
/* I2S_PCM2PDM_conf_EN:R/W；位位置：[25]；默认值：1’b0；*/
/*description:I2S TX PDM转换器启用。*/
#define I2S_PCM2PDM_CONV_EN    (BIT(25))
#define I2S_PCM2PDM_CONV_EN_M  (BIT(25))
#define I2S_PCM2PDM_CONV_EN_V  0x1
#define I2S_PCM2PDM_CONV_EN_S  25
/* I2S_TX_PDM_DAC_MODE_EN:R/W；位位置：[24]；默认值：1’b0；*/
/*描述：I2S TX PDM dac 2信道启用。*/
#define I2S_TX_PDM_DAC_MODE_EN    (BIT(24))
#define I2S_TX_PDM_DAC_MODE_EN_M  (BIT(24))
#define I2S_TX_PDM_DAC_MODE_EN_V  0x1
#define I2S_TX_PDM_DAC_MODE_EN_S  24
/* I2S_TX_PDM_DAC_2OUT_EN:R/W；位位置：[23]；默认值：1’b0；*/
/*描述：I2S TX PDM dac模式启用。*/
#define I2S_TX_PDM_DAC_2OUT_EN    (BIT(23))
#define I2S_TX_PDM_DAC_2OUT_EN_M  (BIT(23))
#define I2S_TX_PDM_DAC_2OUT_EN_V  0x1
#define I2S_TX_PDM_DAC_2OUT_EN_S  23
/* I2S_TX_PDM_sigmadeta_dother:R/W；位位置：[22]；默认值：1’b1；*/
/*描述：I2S TX PDM sigmadelta抖动值。*/
#define I2S_TX_PDM_SIGMADELTA_DITHER    (BIT(22))
#define I2S_TX_PDM_SIGMADELTA_DITHER_M  (BIT(22))
#define I2S_TX_PDM_SIGMADELTA_DITHER_V  0x1
#define I2S_TX_PDM_SIGMADELTA_DITHER_S  22
/* I2S_TX_PDM_SIGMADELTA_DITHER2:R/W；位位置：[21]；默认值：1’b0；*/
/*描述：I2S TX PDM sigmadelta抖动2值。*/
#define I2S_TX_PDM_SIGMADELTA_DITHER2    (BIT(21))
#define I2S_TX_PDM_SIGMADELTA_DITHER2_M  (BIT(21))
#define I2S_TX_PDM_SIGMADELTA_DITHER2_V  0x1
#define I2S_TX_PDM_SIGMADELTA_DITHER2_S  21
/* I2S_TX_PDM_sgmadelta_IN_SHIFT:R/W；比特位置：[20:19]；默认值：2'h1；*/
/*描述：I2S TX PDM sigmadelta刻度移位数：0:/2，1:x1，2:x2，3:x4。*/
#define I2S_TX_PDM_SIGMADELTA_IN_SHIFT    0x00000003
#define I2S_TX_PDM_SIGMADELTA_IN_SHIFT_M  ((I2S_TX_PDM_SIGMADELTA_IN_SHIFT_V)<<(I2S_TX_PDM_SIGMADELTA_IN_SHIFT_S))
#define I2S_TX_PDM_SIGMADELTA_IN_SHIFT_V  0x3
#define I2S_TX_PDM_SIGMADELTA_IN_SHIFT_S  19
/* I2S_TX_PDM_SINC_IN_SHIFT:R/W；比特位置：[18:17]；默认值：2'h1；*/
/*描述：I2S TX PDM sigmadelta刻度移位数：0:/2，1:x1，2:x2，3:x4。*/
#define I2S_TX_PDM_SINC_IN_SHIFT    0x00000003
#define I2S_TX_PDM_SINC_IN_SHIFT_M  ((I2S_TX_PDM_SINC_IN_SHIFT_V)<<(I2S_TX_PDM_SINC_IN_SHIFT_S))
#define I2S_TX_PDM_SINC_IN_SHIFT_V  0x3
#define I2S_TX_PDM_SINC_IN_SHIFT_S  17
/* I2S_TX_PDM_LP_IN_SHIFT:R/W；比特位置：[16:15]；默认值：2'h1；*/
/*描述：I2S TX PDM sigmadelta刻度移位数：0:/2，1:x1，2:x2，3:x4。*/
#define I2S_TX_PDM_LP_IN_SHIFT    0x00000003
#define I2S_TX_PDM_LP_IN_SHIFT_M  ((I2S_TX_PDM_LP_IN_SHIFT_V)<<(I2S_TX_PDM_LP_IN_SHIFT_S))
#define I2S_TX_PDM_LP_IN_SHIFT_V  0x3
#define I2S_TX_PDM_LP_IN_SHIFT_S  15
/* I2S_TX_PDM_HP_IN_SHIFT:R/W；比特位置：[14:13]；默认值：2'h1；*/
/*描述：I2S TX PDM sigmadelta刻度移位数：0:/2，1:x1，2:x2，3:x4。*/
#define I2S_TX_PDM_HP_IN_SHIFT    0x00000003
#define I2S_TX_PDM_HP_IN_SHIFT_M  ((I2S_TX_PDM_HP_IN_SHIFT_V)<<(I2S_TX_PDM_HP_IN_SHIFT_S))
#define I2S_TX_PDM_HP_IN_SHIFT_V  0x3
#define I2S_TX_PDM_HP_IN_SHIFT_S  13
/* I2S_TX_PDM_PRESCALE:R/W；比特位置：[12:5]；默认值：8'0；*/
/*说明：用于sigmadelta的I2S TX PDM预缩放。*/
#define I2S_TX_PDM_PRESCALE    0x000000FF
#define I2S_TX_PDM_PRESCALE_M  ((I2S_TX_PDM_PRESCALE_V)<<(I2S_TX_PDM_PRESCALE_S))
#define I2S_TX_PDM_PRESCALE_V  0xFF
#define I2S_TX_PDM_PRESCALE_S  5
/* I2S_TX_PDM_SINC_OSR2:R/W；比特位置：[4:1]；默认值：4'h2；*/
/*description:I2S TX PDM OSR2值。*/
#define I2S_TX_PDM_SINC_OSR2    0x0000000F
#define I2S_TX_PDM_SINC_OSR2_M  ((I2S_TX_PDM_SINC_OSR2_V)<<(I2S_TX_PDM_SINC_OSR2_S))
#define I2S_TX_PDM_SINC_OSR2_V  0xF
#define I2S_TX_PDM_SINC_OSR2_S  1
/* I2S_TX_PDM_HP_BYPASS:R/W；位位置：[0]；默认值：1’b0；*/
/*说明：I2S TX PDM是否旁通hp过滤器。该选项已删除。。*/
#define I2S_TX_PDM_HP_BYPASS    (BIT(0))
#define I2S_TX_PDM_HP_BYPASS_M  (BIT(0))
#define I2S_TX_PDM_HP_BYPASS_V  0x1
#define I2S_TX_PDM_HP_BYPASS_S  0

#define I2S_TX_PCM2PDM_CONF1_REG(i)          (REG_I2S_BASE(i) + 0x44)
/* I2S_TX_IIR_HP_MULT12_0:R/W；位位置：[25:23]；默认值：3'd7；*/
/*description:PDM TX IIR_HP滤波器级1的第四个参数是（504+I2S_TX_IIR_HP_MULT12_0[2:0]）。*/
#define I2S_TX_IIR_HP_MULT12_0    0x00000007
#define I2S_TX_IIR_HP_MULT12_0_M  ((I2S_TX_IIR_HP_MULT12_0_V)<<(I2S_TX_IIR_HP_MULT12_0_S))
#define I2S_TX_IIR_HP_MULT12_0_V  0x7
#define I2S_TX_IIR_HP_MULT12_0_S  23
/* I2S_TX_IIR_HP_MULT12_5:R/W；比特位置：[22:20]；默认值：3'd7；*/
/*description:PDM TX IIR_HP滤波器2级的第四个参数是（504+I2S_TX_IIR_HP_MULT125[2:0]）。*/
#define I2S_TX_IIR_HP_MULT12_5    0x00000007
#define I2S_TX_IIR_HP_MULT12_5_M  ((I2S_TX_IIR_HP_MULT12_5_V)<<(I2S_TX_IIR_HP_MULT12_5_S))
#define I2S_TX_IIR_HP_MULT12_5_V  0x7
#define I2S_TX_IIR_HP_MULT12_5_S  20
/* I2S_TX_PDM_FS:R/W；比特位置：[19:10]；默认值：10'd480；*/
/*描述：I2S TX PDM Fs。*/
#define I2S_TX_PDM_FS    0x000003FF
#define I2S_TX_PDM_FS_M  ((I2S_TX_PDM_FS_V)<<(I2S_TX_PDM_FS_S))
#define I2S_TX_PDM_FS_V  0x3FF
#define I2S_TX_PDM_FS_S  10
/* I2S_TX_PDM_FP:R/W；位位置：[9:0]；默认值：10'd960；*/
/*描述：I2S TX PDM Fp。*/
#define I2S_TX_PDM_FP    0x000003FF
#define I2S_TX_PDM_FP_M  ((I2S_TX_PDM_FP_V)<<(I2S_TX_PDM_FP_S))
#define I2S_TX_PDM_FP_V  0x3FF
#define I2S_TX_PDM_FP_S  0

#define I2S_RX_TDM_CTRL_REG(i)          (REG_I2S_BASE(i) + 0x050)
/* I2S_RX_tdmtot_CHAN_NUM:R/W；比特位置：[19:16]；默认值：4'0；*/
/*description:I2S TX TDM模式的总信道数。*/
#define I2S_RX_TDM_TOT_CHAN_NUM  0x0000000F
#define I2S_RX_TDM_TOT_CHAN_NUM_M  ((I2S_RX_TDM_TOT_CHAN_NUM_V)<<(I2S_RX_TDM_TOT_CHAN_NUM_S))
#define I2S_RX_TDM_TOT_CHAN_NUM_V  0xF
#define I2S_RX_TDM_TOT_CHAN_NUM_S  16
/* I2S_RX_TDM_CHAN15_EN:R/W；位位置：[15]；默认值：1'h1；*/
/*description:1：启用I2S RX TDM信道$n的有效数据输入。0：仅禁用此通道中的输入0。*/
#define I2S_RX_TDM_CHAN15_EN  (BIT(15))
#define I2S_RX_TDM_CHAN15_EN_M  (BIT(15))
#define I2S_RX_TDM_CHAN15_EN_V  0x1
#define I2S_RX_TDM_CHAN15_EN_S  15
/* I2S_RX_TDM-CHAN14_EN:R/W；位位置：[14]；默认值：1'h1；*/
/*description:1：启用I2S RX TDM信道$n的有效数据输入。0：仅禁用此通道中的输入0。*/
#define I2S_RX_TDM_CHAN14_EN  (BIT(14))
#define I2S_RX_TDM_CHAN14_EN_M  (BIT(14))
#define I2S_RX_TDM_CHAN14_EN_V  0x1
#define I2S_RX_TDM_CHAN14_EN_S  14
/* I2S_RX_TDM-CHAN13_EN:R/W；位位置：[13]；默认值：1'h1；*/
/*description:1：启用I2S RX TDM信道$n的有效数据输入。0：仅禁用此通道中的输入0。*/
#define I2S_RX_TDM_CHAN13_EN  (BIT(13))
#define I2S_RX_TDM_CHAN13_EN_M  (BIT(13))
#define I2S_RX_TDM_CHAN13_EN_V  0x1
#define I2S_RX_TDM_CHAN13_EN_S  13
/* I2S_RX_TDM-CHAN12_EN:R/W；位位置：[12]；默认值：1'h1；*/
/*description:1：启用I2S RX TDM信道$n的有效数据输入。0：仅禁用此通道中的输入0。*/
#define I2S_RX_TDM_CHAN12_EN  (BIT(12))
#define I2S_RX_TDM_CHAN12_EN_M  (BIT(12))
#define I2S_RX_TDM_CHAN12_EN_V  0x1
#define I2S_RX_TDM_CHAN12_EN_S  12
/* I2S_RX_TDM_CHAN11_EN:R/W；位位置：[11]；默认值：1'h1；*/
/*description:1：启用I2S RX TDM信道$n的有效数据输入。0：仅禁用此通道中的输入0。*/
#define I2S_RX_TDM_CHAN11_EN  (BIT(11))
#define I2S_RX_TDM_CHAN11_EN_M  (BIT(11))
#define I2S_RX_TDM_CHAN11_EN_V  0x1
#define I2S_RX_TDM_CHAN11_EN_S  11
/* I2S_RX_TDM_CHAN10_EN:R/W；位位置：[10]；默认值：1'h1；*/
/*description:1：启用I2S RX TDM信道$n的有效数据输入。0：仅禁用此通道中的输入0。*/
#define I2S_RX_TDM_CHAN10_EN  (BIT(10))
#define I2S_RX_TDM_CHAN10_EN_M  (BIT(10))
#define I2S_RX_TDM_CHAN10_EN_V  0x1
#define I2S_RX_TDM_CHAN10_EN_S  10
/* I2S_RX_TDM_CHAN9_EN:R/W；位位置：[9]；默认值：1'h1；*/
/*description:1：启用I2S RX TDM信道$n的有效数据输入。0：仅禁用此通道中的输入0。*/
#define I2S_RX_TDM_CHAN9_EN  (BIT(9))
#define I2S_RX_TDM_CHAN9_EN_M  (BIT(9))
#define I2S_RX_TDM_CHAN9_EN_V  0x1
#define I2S_RX_TDM_CHAN9_EN_S  9
/* I2S_RX_TDM-CHAN8_EN:R/W；位位置：[8]；默认值：1'h1；*/
/*description:1：启用I2S RX TDM信道$n的有效数据输入。0：仅禁用此通道中的输入0。*/
#define I2S_RX_TDM_CHAN8_EN  (BIT(8))
#define I2S_RX_TDM_CHAN8_EN_M  (BIT(8))
#define I2S_RX_TDM_CHAN8_EN_V  0x1
#define I2S_RX_TDM_CHAN8_EN_S  8
/* I2S_RX_TDM_PDM_CHAN7_EN:R/W；位位置：[7]；默认值：1'h1；*/
/*description:1：启用I2S RX TDM或PDM信道$n的有效数据输入。0：仅禁用此通道中的输入0。*/
#define I2S_RX_TDM_PDM_CHAN7_EN  (BIT(7))
#define I2S_RX_TDM_PDM_CHAN7_EN_M  (BIT(7))
#define I2S_RX_TDM_PDM_CHAN7_EN_V  0x1
#define I2S_RX_TDM_PDM_CHAN7_EN_S  7
/* I2S_RX_TDM_PDM_CHAN6_EN:R/W；位位置：[6]；默认值：1'h1；*/
/*description:1：启用I2S RX TDM或PDM信道$n的有效数据输入。0：仅禁用此通道中的输入0。*/
#define I2S_RX_TDM_PDM_CHAN6_EN  (BIT(6))
#define I2S_RX_TDM_PDM_CHAN6_EN_M  (BIT(6))
#define I2S_RX_TDM_PDM_CHAN6_EN_V  0x1
#define I2S_RX_TDM_PDM_CHAN6_EN_S  6
/* I2S_RX_TDM_PDM-CHAN5_EN:R/W；位位置：[5]；默认值：1'h1；*/
/*description:1：启用I2S RX TDM或PDM信道$n的有效数据输入。0：仅禁用此通道中的输入0。*/
#define I2S_RX_TDM_PDM_CHAN5_EN  (BIT(5))
#define I2S_RX_TDM_PDM_CHAN5_EN_M  (BIT(5))
#define I2S_RX_TDM_PDM_CHAN5_EN_V  0x1
#define I2S_RX_TDM_PDM_CHAN5_EN_S  5
/* I2S_RX_TDM_PDM-CHAN4_EN:R/W；位位置：[4]；默认值：1'h1；*/
/*description:1：启用I2S RX TDM或PDM信道$n的有效数据输入。0：仅禁用此通道中的输入0。*/
#define I2S_RX_TDM_PDM_CHAN4_EN  (BIT(4))
#define I2S_RX_TDM_PDM_CHAN4_EN_M  (BIT(4))
#define I2S_RX_TDM_PDM_CHAN4_EN_V  0x1
#define I2S_RX_TDM_PDM_CHAN4_EN_S  4
/* I2S_RX_TDM_PDM_CHAN3_EN:R/W；位位置：[3]；默认值：1'h1；*/
/*description:1：启用I2S RX TDM或PDM信道$n的有效数据输入。0：仅禁用此通道中的输入0。*/
#define I2S_RX_TDM_PDM_CHAN3_EN  (BIT(3))
#define I2S_RX_TDM_PDM_CHAN3_EN_M  (BIT(3))
#define I2S_RX_TDM_PDM_CHAN3_EN_V  0x1
#define I2S_RX_TDM_PDM_CHAN3_EN_S  3
/* I2S_RX_TDM_PDM-CHAN2_EN:R/W；位位置：[2]；默认值：1'h1；*/
/*description:1：启用I2S RX TDM或PDM信道$n的有效数据输入。0：仅禁用此通道中的输入0。*/
#define I2S_RX_TDM_PDM_CHAN2_EN  (BIT(2))
#define I2S_RX_TDM_PDM_CHAN2_EN_M  (BIT(2))
#define I2S_RX_TDM_PDM_CHAN2_EN_V  0x1
#define I2S_RX_TDM_PDM_CHAN2_EN_S  2
/* I2S_RX_TDM_PDM_CHAN1_EN:R/W；位位置：[1]；默认值：1'h1；*/
/*description:1：启用I2S RX TDM或PDM信道$n的有效数据输入。0：仅禁用此通道中的输入0。*/
#define I2S_RX_TDM_PDM_CHAN1_EN  (BIT(1))
#define I2S_RX_TDM_PDM_CHAN1_EN_M  (BIT(1))
#define I2S_RX_TDM_PDM_CHAN1_EN_V  0x1
#define I2S_RX_TDM_PDM_CHAN1_EN_S  1
/* I2S_RX_TDM_PDM_CHAN0_EN:R/W；位位置：[0]；默认值：1'h1；*/
/*description:1：启用I2S RX TDM或PDM信道$n的有效数据输入。0：仅禁用此通道中的输入0。*/
#define I2S_RX_TDM_PDM_CHAN0_EN  (BIT(0))
#define I2S_RX_TDM_PDM_CHAN0_EN_M  (BIT(0))
#define I2S_RX_TDM_PDM_CHAN0_EN_V  0x1
#define I2S_RX_TDM_PDM_CHAN0_EN_S  0

#define I2S_TX_TDM_CTRL_REG(i)          (REG_I2S_BASE(i) + 0x0054)
/* I2S_TX_TDM_SKIP_MSK_EN:R/W；位位置：[20]；默认值：1’b0；*/
/*描述：当DMA TX缓冲区存储（REG_TX_TDM_TOT_CHAN_NUM+1）信道的数据，并且仅发送启用信道的数据时，应设置此位。当DMA TX缓冲区中存储的所有数据都用于启用的信道时，清除该选项。*/
#define I2S_TX_TDM_SKIP_MSK_EN  (BIT(20))
#define I2S_TX_TDM_SKIP_MSK_EN_M  (BIT(20))
#define I2S_TX_TDM_SKIP_MSK_EN_V  0x1
#define I2S_TX_TDM_SKIP_MSK_EN_S  20
/* I2S_TX_TDM_to_CHAN_NUM:R/W；比特位置：[19:16]；默认值：4'0；*/
/*description:I2S TX TDM模式的总信道数减1。*/
#define I2S_TX_TDM_TOT_CHAN_NUM  0x0000000F
#define I2S_TX_TDM_TOT_CHAN_NUM_M  ((I2S_TX_TDM_TOT_CHAN_NUM_V)<<(I2S_TX_TDM_TOT_CHAN_NUM_S))
#define I2S_TX_TDM_TOT_CHAN_NUM_V  0xF
#define I2S_TX_TDM_TOT_CHAN_NUM_S  16
/* I2S_TX_TDM_CHAN15_EN:R/W；位位置：[15]；默认值：1'h1；*/
/*description:1：启用I2S TX TDM信道$n的有效数据输出。0：仅禁用此通道中的输出0。*/
#define I2S_TX_TDM_CHAN15_EN  (BIT(15))
#define I2S_TX_TDM_CHAN15_EN_M  (BIT(15))
#define I2S_TX_TDM_CHAN15_EN_V  0x1
#define I2S_TX_TDM_CHAN15_EN_S  15
/* I2S_TX_TDM_CHAN14_EN:R/W；位位置：[14]；默认值：1'h1；*/
/*description:1：启用I2S TX TDM信道$n的有效数据输出。0：仅禁用此通道中的输出0。*/
#define I2S_TX_TDM_CHAN14_EN  (BIT(14))
#define I2S_TX_TDM_CHAN14_EN_M  (BIT(14))
#define I2S_TX_TDM_CHAN14_EN_V  0x1
#define I2S_TX_TDM_CHAN14_EN_S  14
/* I2S_TX_TDM_CHAN13_EN:R/W；位位置：[13]；默认值：1'h1；*/
/*description:1：启用I2S TX TDM信道$n的有效数据输出。0：仅禁用此通道中的输出0。*/
#define I2S_TX_TDM_CHAN13_EN  (BIT(13))
#define I2S_TX_TDM_CHAN13_EN_M  (BIT(13))
#define I2S_TX_TDM_CHAN13_EN_V  0x1
#define I2S_TX_TDM_CHAN13_EN_S  13
/* I2S_TX_TDM_CHAN12_EN:R/W；位位置：[12]；默认值：1'h1；*/
/*description:1：启用I2S TX TDM信道$n的有效数据输出。0：仅禁用此通道中的输出0。*/
#define I2S_TX_TDM_CHAN12_EN  (BIT(12))
#define I2S_TX_TDM_CHAN12_EN_M  (BIT(12))
#define I2S_TX_TDM_CHAN12_EN_V  0x1
#define I2S_TX_TDM_CHAN12_EN_S  12
/* I2S_TX_TDM_CHAN11_EN:R/W；位位置：[11]；默认值：1'h1；*/
/*description:1：启用I2S TX TDM信道$n的有效数据输出。0：仅禁用此通道中的输出0。*/
#define I2S_TX_TDM_CHAN11_EN  (BIT(11))
#define I2S_TX_TDM_CHAN11_EN_M  (BIT(11))
#define I2S_TX_TDM_CHAN11_EN_V  0x1
#define I2S_TX_TDM_CHAN11_EN_S  11
/* I2S_TX_TDM_CHAN10_EN:R/W；位位置：[10]；默认值：1'h1；*/
/*description:1：启用I2S TX TDM信道$n的有效数据输出。0：仅禁用此通道中的输出0。*/
#define I2S_TX_TDM_CHAN10_EN  (BIT(10))
#define I2S_TX_TDM_CHAN10_EN_M  (BIT(10))
#define I2S_TX_TDM_CHAN10_EN_V  0x1
#define I2S_TX_TDM_CHAN10_EN_S  10
/* I2S_TX_TDM_CHAN9_EN:R/W；位位置：[9]；默认值：1'h1；*/
/*description:1：启用I2S TX TDM信道$n的有效数据输出。0：仅禁用此通道中的输出0。*/
#define I2S_TX_TDM_CHAN9_EN  (BIT(9))
#define I2S_TX_TDM_CHAN9_EN_M  (BIT(9))
#define I2S_TX_TDM_CHAN9_EN_V  0x1
#define I2S_TX_TDM_CHAN9_EN_S  9
/* I2S_TX_TDM_CHAN8_EN:R/W；位位置：[8]；默认值：1'h1；*/
/*description:1：启用I2S TX TDM信道$n的有效数据输出。0：仅禁用此通道中的输出0。*/
#define I2S_TX_TDM_CHAN8_EN  (BIT(8))
#define I2S_TX_TDM_CHAN8_EN_M  (BIT(8))
#define I2S_TX_TDM_CHAN8_EN_V  0x1
#define I2S_TX_TDM_CHAN8_EN_S  8
/* I2S_TX_TDM_CHAN7_EN:R/W；位位置：[7]；默认值：1'h1；*/
/*description:1：启用I2S TX TDM信道$n的有效数据输出。0：仅禁用此通道中的输出0。*/
#define I2S_TX_TDM_CHAN7_EN  (BIT(7))
#define I2S_TX_TDM_CHAN7_EN_M  (BIT(7))
#define I2S_TX_TDM_CHAN7_EN_V  0x1
#define I2S_TX_TDM_CHAN7_EN_S  7
/* I2S_TX_TDM_CHAN6_EN:R/W；位位置：[6]；默认值：1'h1；*/
/*description:1：启用I2S TX TDM信道$n的有效数据输出。0：仅禁用此通道中的输出0。*/
#define I2S_TX_TDM_CHAN6_EN  (BIT(6))
#define I2S_TX_TDM_CHAN6_EN_M  (BIT(6))
#define I2S_TX_TDM_CHAN6_EN_V  0x1
#define I2S_TX_TDM_CHAN6_EN_S  6
/* I2S_TX_TDM_CHAN5_EN:R/W；位位置：[5]；默认值：1'h1；*/
/*description:1：启用I2S TX TDM信道$n的有效数据输出。0：仅禁用此通道中的输出0。*/
#define I2S_TX_TDM_CHAN5_EN  (BIT(5))
#define I2S_TX_TDM_CHAN5_EN_M  (BIT(5))
#define I2S_TX_TDM_CHAN5_EN_V  0x1
#define I2S_TX_TDM_CHAN5_EN_S  5
/* I2S_TX_TDM_CHAN4_EN:R/W；位位置：[4]；默认值：1'h1；*/
/*description:1：启用I2S TX TDM信道$n的有效数据输出。0：仅禁用此通道中的输出0。*/
#define I2S_TX_TDM_CHAN4_EN  (BIT(4))
#define I2S_TX_TDM_CHAN4_EN_M  (BIT(4))
#define I2S_TX_TDM_CHAN4_EN_V  0x1
#define I2S_TX_TDM_CHAN4_EN_S  4
/* I2S_TX_TDM_CHAN3_EN:R/W；位位置：[3]；默认值：1'h1；*/
/*description:1：启用I2S TX TDM信道$n的有效数据输出。0：仅禁用此通道中的输出0。*/
#define I2S_TX_TDM_CHAN3_EN  (BIT(3))
#define I2S_TX_TDM_CHAN3_EN_M  (BIT(3))
#define I2S_TX_TDM_CHAN3_EN_V  0x1
#define I2S_TX_TDM_CHAN3_EN_S  3
/* I2S_TX_TDM_CHAN2_EN:R/W；位位置：[2]；默认值：1'h1；*/
/*description:1：启用I2S TX TDM信道$n的有效数据输出。0：仅禁用此通道中的输出0。*/
#define I2S_TX_TDM_CHAN2_EN  (BIT(2))
#define I2S_TX_TDM_CHAN2_EN_M  (BIT(2))
#define I2S_TX_TDM_CHAN2_EN_V  0x1
#define I2S_TX_TDM_CHAN2_EN_S  2
/* I2S_TX_TDM_CHAN1_EN:R/W；位位置：[1]；默认值：1'h1；*/
/*description:1：启用I2S TX TDM信道$n的有效数据输出。0：仅禁用此通道中的输出0。*/
#define I2S_TX_TDM_CHAN1_EN  (BIT(1))
#define I2S_TX_TDM_CHAN1_EN_M  (BIT(1))
#define I2S_TX_TDM_CHAN1_EN_V  0x1
#define I2S_TX_TDM_CHAN1_EN_S  1
/* I2S_TX_TDM_CHAN0_EN:R/W；位位置：[0]；默认值：1'h1；*/
/*description:1：启用I2S TX TDM信道$n的有效数据输出。0：仅禁用此通道中的输出0。*/
#define I2S_TX_TDM_CHAN0_EN  (BIT(0))
#define I2S_TX_TDM_CHAN0_EN_M  (BIT(0))
#define I2S_TX_TDM_CHAN0_EN_V  0x1
#define I2S_TX_TDM_CHAN0_EN_S  0

#define I2S_RX_TIMING_REG(i)          (REG_I2S_BASE(i) + 0x0058)
/* I2S_RX_BCK_IN_DM:R/W；位位置：[29:28]；默认值：2'h0；*/
/*描述：I2S Rx BCK输入信号的延迟模式。0：旁路。1： pos边缘延迟。2： 负边缘延迟。3： 未使用。*/
#define I2S_RX_BCK_IN_DM  0x00000003
#define I2S_RX_BCK_IN_DM_M  ((I2S_RX_BCK_IN_DM_V)<<(I2S_RX_BCK_IN_DM_S))
#define I2S_RX_BCK_IN_DM_V  0x3
#define I2S_RX_BCK_IN_DM_S  28
/* I2S_RX_WS_IN_DM:R/W；位位置：[25:24]；默认值：2'h0；*/
/*描述：I2S Rx WS输入信号的延迟模式。0：旁路。1： pos边缘延迟。2： 负边缘延迟。3： 未使用。*/
#define I2S_RX_WS_IN_DM  0x00000003
#define I2S_RX_WS_IN_DM_M  ((I2S_RX_WS_IN_DM_V)<<(I2S_RX_WS_IN_DM_S))
#define I2S_RX_WS_IN_DM_V  0x3
#define I2S_RX_WS_IN_DM_S  24
/* I2S_RX_BCK_OUT_DM:R/W；比特位置：[21:20]；默认值：2'h0；*/
/*描述：I2S Rx BCK输出信号的延迟模式。0：旁路。1： pos边缘延迟。2： 负边缘延迟。3： 未使用。*/
#define I2S_RX_BCK_OUT_DM  0x00000003
#define I2S_RX_BCK_OUT_DM_M  ((I2S_RX_BCK_OUT_DM_V)<<(I2S_RX_BCK_OUT_DM_S))
#define I2S_RX_BCK_OUT_DM_V  0x3
#define I2S_RX_BCK_OUT_DM_S  20
/* I2S_RX_WS_OUT_DM:R/W；比特位置：[17:16]；默认值：2'h0；*/
/*描述：I2S Rx WS输出信号的延迟模式。0：旁路。1： pos边缘延迟。2： 负边缘延迟。3： 未使用。*/
#define I2S_RX_WS_OUT_DM  0x00000003
#define I2S_RX_WS_OUT_DM_M  ((I2S_RX_WS_OUT_DM_V)<<(I2S_RX_WS_OUT_DM_S))
#define I2S_RX_WS_OUT_DM_V  0x3
#define I2S_RX_WS_OUT_DM_S  16
/* I2S_RX_SD_IN_DM:R/W；位位置：[1:0]；默认值：2'h0；*/
/*描述：I2S Rx SD输入信号的延迟模式。0：旁路。1： pos边缘延迟。2： 负边缘延迟。3： 未使用。*/
#define I2S_RX_SD_IN_DM  0x00000003
#define I2S_RX_SD_IN_DM_M  ((I2S_RX_SD_IN_DM_V)<<(I2S_RX_SD_IN_DM_S))
#define I2S_RX_SD_IN_DM_V  0x3
#define I2S_RX_SD_IN_DM_S  0

#define I2S_TX_TIMING_REG(i)          (REG_I2S_BASE(i) + 0x005C)
/* I2S_TX_BCK_IN_DM:R/W；位位置：[29:28]；默认值：2'h0；*/
/*描述：I2S Tx BCK输入信号的延迟模式。0：旁路。1： pos边缘延迟。2： 负边缘延迟。3： 未使用。*/
#define I2S_TX_BCK_IN_DM  0x00000003
#define I2S_TX_BCK_IN_DM_M  ((I2S_TX_BCK_IN_DM_V)<<(I2S_TX_BCK_IN_DM_S))
#define I2S_TX_BCK_IN_DM_V  0x3
#define I2S_TX_BCK_IN_DM_S  28
/* I2S_TX_WS_IN_DM:R/W；位位置：[25:24]；默认值：2'h0；*/
/*描述：I2S Tx WS输入信号的延迟模式。0：旁路。1： pos边缘延迟。2： 负边缘延迟。3： 未使用。*/
#define I2S_TX_WS_IN_DM  0x00000003
#define I2S_TX_WS_IN_DM_M  ((I2S_TX_WS_IN_DM_V)<<(I2S_TX_WS_IN_DM_S))
#define I2S_TX_WS_IN_DM_V  0x3
#define I2S_TX_WS_IN_DM_S  24
/* I2S_TX_BCK_OUT_DM:R/W；比特位置：[21:20]；默认值：2'h0；*/
/*描述：I2S Tx BCK输出信号的延迟模式。0：旁路。1： pos边缘延迟。2： 负边缘延迟。3： 未使用。*/
#define I2S_TX_BCK_OUT_DM  0x00000003
#define I2S_TX_BCK_OUT_DM_M  ((I2S_TX_BCK_OUT_DM_V)<<(I2S_TX_BCK_OUT_DM_S))
#define I2S_TX_BCK_OUT_DM_V  0x3
#define I2S_TX_BCK_OUT_DM_S  20
/* I2S_TX_WS_OUT_DM:R/W；比特位置：[17:16]；默认值：2'h0；*/
/*描述：I2S Tx WS输出信号的延迟模式。0：旁路。1： pos边缘延迟。2： 负边缘延迟。3： 未使用。*/
#define I2S_TX_WS_OUT_DM  0x00000003
#define I2S_TX_WS_OUT_DM_M  ((I2S_TX_WS_OUT_DM_V)<<(I2S_TX_WS_OUT_DM_S))
#define I2S_TX_WS_OUT_DM_V  0x3
#define I2S_TX_WS_OUT_DM_S  16
/* I2S_TX_SD1_OUT_DM:R/W；比特位置：[5:4]；默认值：2'h0；*/
/*描述：I2S TX SD1输出信号的延迟模式。0：旁路。1： pos边缘延迟。2： 负边缘延迟。3： 未使用。。*/
#define I2S_TX_SD1_OUT_DM    0x00000003
#define I2S_TX_SD1_OUT_DM_M  ((I2S_TX_SD1_OUT_DM_V)<<(I2S_TX_SD1_OUT_DM_S))
#define I2S_TX_SD1_OUT_DM_V  0x3
#define I2S_TX_SD1_OUT_DM_S  4
/* I2S_TX_SD_OUT_DM:R/W；位位置：[1:0]；默认值：2'h0；*/
/*描述：I2S Tx SD输出信号的延迟模式。0：旁路。1： pos边缘延迟。2： 负边缘延迟。3： 未使用。*/
#define I2S_TX_SD_OUT_DM  0x00000003
#define I2S_TX_SD_OUT_DM_M  ((I2S_TX_SD_OUT_DM_V)<<(I2S_TX_SD_OUT_DM_S))
#define I2S_TX_SD_OUT_DM_V  0x3
#define I2S_TX_SD_OUT_DM_S  0

#define I2S_LC_HUNG_CONF_REG(i)          (REG_I2S_BASE(i) + 0x0060)
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

#define I2S_RXEOF_NUM_REG(i)          (REG_I2S_BASE(i) + 0x0064)
/* I2S_RX_of_NUM:R/W；位位置：[11:0]；默认值：12'h40；*/
/*description:要接收的数据长度。它将触发i2s_in_suc_eof_int。*/
#define I2S_RX_EOF_NUM  0x00000FFF
#define I2S_RX_EOF_NUM_M  ((I2S_RX_EOF_NUM_V)<<(I2S_RX_EOF_NUM_S))
#define I2S_RX_EOF_NUM_V  0xFFF
#define I2S_RX_EOF_NUM_S  0

#define I2S_CONF_SIGLE_DATA_REG(i)          (REG_I2S_BASE(i) + 0x0068)
/* I2S_SINGLE_DATA:R/W；位位置：[31:0]；默认值：32'd0；*/
/*描述：右通道或左通道根据tx_chan_mod和reg_tx_msb_right输出存储在此寄存器中的常量值*/
#define I2S_SINGLE_DATA  0xFFFFFFFF
#define I2S_SINGLE_DATA_M  ((I2S_SINGLE_DATA_V)<<(I2S_SINGLE_DATA_S))
#define I2S_SINGLE_DATA_V  0xFFFFFFFF
#define I2S_SINGLE_DATA_S  0

#define I2S_STATE_REG(i)          (REG_I2S_BASE(i) + 0x006C)
/* I2S_TX_IDLE:RO；位位置：[0]；默认值：1’b1；*/
/*描述：1:i2s_tx为空闲状态。0:i2s_tx正在工作。*/
#define I2S_TX_IDLE  (BIT(0))
#define I2S_TX_IDLE_M  (BIT(0))
#define I2S_TX_IDLE_V  0x1
#define I2S_TX_IDLE_S  0

#define I2S_DATE_REG(i)          (REG_I2S_BASE(i) + 0x0080)
/* I2S_DATE:R/W；位位置：[27:0]；默认值：28'h2003230；*/
/*description:版本控制寄存器*/
#define I2S_DATE  0x0FFFFFFF
#define I2S_DATE_M  ((I2S_DATE_V)<<(I2S_DATE_S))
#define I2S_DATE_V  0xFFFFFFF
#define I2S_DATE_S  0

#ifdef __cplusplus
}
#endif



#endif /*_SOC_I2S_REG_H_ */

