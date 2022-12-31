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
#ifndef __UART_REG_H__
#define __UART_REG_H__


#include "soc.h"

#define REG_UART_BASE( i )  (DR_REG_UART_BASE + (i) * 0x10000 + ( (i) > 1 ? 0xe000 : 0 ) )
#define REG_UART_AHB_BASE(i)  (0x60000000 + (i) * 0x10000 + ( (i) > 1 ? 0xe000 : 0 ) )
#define UART_FIFO_AHB_REG(i)  (REG_UART_AHB_BASE(i) + 0x0)
#define UART_FIFO_REG(i)          (REG_UART_BASE(i) + 0x0)

/* UART_RXFIFO_RD-BYTE:RO；位位置：[7:0]；默认值：8'b0；*/
/*description:此寄存器存储rx fifo读取的一字节数据。*/
#define UART_RXFIFO_RD_BYTE  0x000000FF
#define UART_RXFIFO_RD_BYTE_M  ((UART_RXFIFO_RD_BYTE_V)<<(UART_RXFIFO_RD_BYTE_S))
#define UART_RXFIFO_RD_BYTE_V  0xFF
#define UART_RXFIFO_RD_BYTE_S  0

#define UART_INT_RAW_REG(i)          (REG_UART_BASE(i) + 0x4)
/* UART_AT_CMD_CHAR_DET_INT_RAW:RO；位位置：[18]；默认值：1’b0；*/
/*description:当接收器检测到配置的at_cmd字符时，此中断原始位变为高电平。*/
#define UART_AT_CMD_CHAR_DET_INT_RAW  (BIT(18))
#define UART_AT_CMD_CHAR_DET_INT_RAW_M  (BIT(18))
#define UART_AT_CMD_CHAR_DET_INT_RAW_V  0x1
#define UART_AT_CMD_CHAR_DET_INT_RAW_S  18
/* UART_RS485_CLASH_INT_RAW:RO；位位置：[17]；默认值：1’b0；*/
/*描述：当rs485检测到发送器和接收器之间的冲突时，此中断原始位变为高电平。*/
#define UART_RS485_CLASH_INT_RAW  (BIT(17))
#define UART_RS485_CLASH_INT_RAW_M  (BIT(17))
#define UART_RS485_CLASH_INT_RAW_V  0x1
#define UART_RS485_CLASH_INT_RAW_S  17
/* UART_RS485_FRM_ERR_INT_RAW:RO；位位置：[16]；默认值：1’b0；*/
/*描述：当rs485检测到数据帧错误时，此中断原始位变为高电平。*/
#define UART_RS485_FRM_ERR_INT_RAW  (BIT(16))
#define UART_RS485_FRM_ERR_INT_RAW_M  (BIT(16))
#define UART_RS485_FRM_ERR_INT_RAW_V  0x1
#define UART_RS485_FRM_ERR_INT_RAW_S  16
/* UART_RS485_PARITY_ERR_INT_RAW:RO；位位置：[15]；默认值：1’b0；*/
/*描述：当rs485检测到奇偶校验错误时，此中断原始位变为高电平。*/
#define UART_RS485_PARITY_ERR_INT_RAW  (BIT(15))
#define UART_RS485_PARITY_ERR_INT_RAW_M  (BIT(15))
#define UART_RS485_PARITY_ERR_INT_RAW_V  0x1
#define UART_RS485_PARITY_ERR_INT_RAW_S  15
/* UART_TX_DONE_INT_RAW:RO；位位置：[14]；默认值：1’b0；*/
/*描述：当发射机发送fifo中的所有数据时，该中断原始位变为高电平。*/
#define UART_TX_DONE_INT_RAW  (BIT(14))
#define UART_TX_DONE_INT_RAW_M  (BIT(14))
#define UART_TX_DONE_INT_RAW_V  0x1
#define UART_TX_DONE_INT_RAW_S  14
/* UART_TX_bk_IDLE_DONE_INT_RAW:RO；位位置：[13]；默认值：1’b0；*/
/*描述：当发射机在发送最后一个数据后保持最短的持续时间时，该中断原始位变为高电平。*/
#define UART_TX_BRK_IDLE_DONE_INT_RAW  (BIT(13))
#define UART_TX_BRK_IDLE_DONE_INT_RAW_M  (BIT(13))
#define UART_TX_BRK_IDLE_DONE_INT_RAW_V  0x1
#define UART_TX_BRK_IDLE_DONE_INT_RAW_S  13
/* UART_TX_bk_DONE_INT_RAW:RO；位位置：[12]；默认值：1’b0；*/
/*描述：当发送器fifo中的所有数据发送完毕后，当发送器完成发送0时，此中断原始位变为高电平。*/
#define UART_TX_BRK_DONE_INT_RAW  (BIT(12))
#define UART_TX_BRK_DONE_INT_RAW_M  (BIT(12))
#define UART_TX_BRK_DONE_INT_RAW_V  0x1
#define UART_TX_BRK_DONE_INT_RAW_S  12
/* UART_gillid_DET_INT_RAW:RO；位位置：[11]；默认值：1’b0；*/
/*描述：当接收器检测到起始位时，此中断原始位变为高电平。*/
#define UART_GLITCH_DET_INT_RAW  (BIT(11))
#define UART_GLITCH_DET_INT_RAW_M  (BIT(11))
#define UART_GLITCH_DET_INT_RAW_V  0x1
#define UART_GLITCH_DET_INT_RAW_S  11
/* UART_SW_XOFF_INT_RAW:RO；位位置：[10]；默认值：1’b0；*/
/*描述：当接收器接收到uart_sw_flow_con_en设置为1的xon字符时，此中断原始位变为高电平。*/
#define UART_SW_XOFF_INT_RAW  (BIT(10))
#define UART_SW_XOFF_INT_RAW_M  (BIT(10))
#define UART_SW_XOFF_INT_RAW_V  0x1
#define UART_SW_XOFF_INT_RAW_S  10
/* UART_SW_XON_INT_RAW:RO；位位置：[9]；默认值：1’b0；*/
/*描述：当接收器接收到uart_sw_flow_con_en设置为1的xoff字符时，此中断原始位变为高电平。*/
#define UART_SW_XON_INT_RAW  (BIT(9))
#define UART_SW_XON_INT_RAW_M  (BIT(9))
#define UART_SW_XON_INT_RAW_V  0x1
#define UART_SW_XON_INT_RAW_S  9
/* UART_RXFIFO_out_INT_RAW:RO；位位置：[8]；默认值：1’b0；*/
/*描述：当接收器接收一个字节的时间超过rx_tout_thhd时，此中断原始位变为高电平。*/
#define UART_RXFIFO_TOUT_INT_RAW  (BIT(8))
#define UART_RXFIFO_TOUT_INT_RAW_M  (BIT(8))
#define UART_RXFIFO_TOUT_INT_RAW_V  0x1
#define UART_RXFIFO_TOUT_INT_RAW_S  8
/* UART_BRK_DET_INT_RAW:RO；位位置：[7]；默认值：1’b0；*/
/*描述：当接收器检测到停止位之后的0时，此中断原始位变为高电平。*/
#define UART_BRK_DET_INT_RAW  (BIT(7))
#define UART_BRK_DET_INT_RAW_M  (BIT(7))
#define UART_BRK_DET_INT_RAW_V  0x1
#define UART_BRK_DET_INT_RAW_S  7
/* UART_CTS_CHG_INT_RAW:RO；位位置：[6]；默认值：1’b0；*/
/*描述：当接收器检测到ctsn信号的边缘变化时，此中断原始位变为高电平。*/
#define UART_CTS_CHG_INT_RAW  (BIT(6))
#define UART_CTS_CHG_INT_RAW_M  (BIT(6))
#define UART_CTS_CHG_INT_RAW_V  0x1
#define UART_CTS_CHG_INT_RAW_S  6
/* UART_DSR_CHG_INT_RAW:RO；位位置：[5]；默认值：1’b0；*/
/*描述：当接收器检测到dsrn信号的边缘变化时，此中断原始位变为高电平。*/
#define UART_DSR_CHG_INT_RAW  (BIT(5))
#define UART_DSR_CHG_INT_RAW_M  (BIT(5))
#define UART_DSR_CHG_INT_RAW_V  0x1
#define UART_DSR_CHG_INT_RAW_S  5
/* UART_RXFIFO_vf_INT_RAW:RO；位位置：[4]；默认值：1’b0；*/
/*描述：当接收机接收到的数据超过fifo所能存储的数据时，此中断原始位变为高电平。*/
#define UART_RXFIFO_OVF_INT_RAW  (BIT(4))
#define UART_RXFIFO_OVF_INT_RAW_M  (BIT(4))
#define UART_RXFIFO_OVF_INT_RAW_V  0x1
#define UART_RXFIFO_OVF_INT_RAW_S  4
/* UART_FRM_ERR_INT_RAW:RO；位位置：[3]；默认值：1’b0；*/
/*描述：当接收器检测到数据的帧错误时，此中断原始位变为高电平。*/
#define UART_FRM_ERR_INT_RAW  (BIT(3))
#define UART_FRM_ERR_INT_RAW_M  (BIT(3))
#define UART_FRM_ERR_INT_RAW_V  0x1
#define UART_FRM_ERR_INT_RAW_S  3
/* UART_PARITY_ERR_INT_RAW:RO；位位置：[2]；默认值：1’b0；*/
/*描述：当接收器检测到数据的奇偶校验错误时，此中断原始位变为高电平。*/
#define UART_PARITY_ERR_INT_RAW  (BIT(2))
#define UART_PARITY_ERR_INT_RAW_M  (BIT(2))
#define UART_PARITY_ERR_INT_RAW_V  0x1
#define UART_PARITY_ERR_INT_RAW_S  2
/* UART_TXFIFO_EMPTY_INT_RAW:RO；位位置：[1]；默认值：1’b0；*/
/*描述：当发射机fifo中的数据量小于（（tx_mem_cnttxfifo_cnt）时，此中断原始位变为高电平。*/
#define UART_TXFIFO_EMPTY_INT_RAW  (BIT(1))
#define UART_TXFIFO_EMPTY_INT_RAW_M  (BIT(1))
#define UART_TXFIFO_EMPTY_INT_RAW_V  0x1
#define UART_TXFIFO_EMPTY_INT_RAW_S  1
/* UART_RXFIFO_FULL_INT_RAW:RO；位位置：[0]；默认值：1’b0；*/
/*描述：当接收器接收的数据超过（rx_flow_thrhd_h3 rx_flow_thrhd）时，此中断原始位变为高电平。*/
#define UART_RXFIFO_FULL_INT_RAW  (BIT(0))
#define UART_RXFIFO_FULL_INT_RAW_M  (BIT(0))
#define UART_RXFIFO_FULL_INT_RAW_V  0x1
#define UART_RXFIFO_FULL_INT_RAW_S  0

#define UART_INT_ST_REG(i)          (REG_UART_BASE(i) + 0x8)
/* UART_AT_CMD_CHAR_DET_INT_ST:RO；位位置：[18]；默认值：1’b0；*/
/*description:这是at_cmd_char_det_int_ena设置为1时at_cmd_det_int_raw的状态位。*/
#define UART_AT_CMD_CHAR_DET_INT_ST  (BIT(18))
#define UART_AT_CMD_CHAR_DET_INT_ST_M  (BIT(18))
#define UART_AT_CMD_CHAR_DET_INT_ST_V  0x1
#define UART_AT_CMD_CHAR_DET_INT_ST_S  18
/* UART_RS485_CLASH_INT_ST:RO；位位置：[17]；默认值：1’b0；*/
/*description:当rs485_clash_int_ena设置为1时，这是rs485_clash_int_raw的状态位。*/
#define UART_RS485_CLASH_INT_ST  (BIT(17))
#define UART_RS485_CLASH_INT_ST_M  (BIT(17))
#define UART_RS485_CLASH_INT_ST_V  0x1
#define UART_RS485_CLASH_INT_ST_S  17
/* UART_RS485_FRM_ERR_INT_ST:RO；位位置：[16]；默认值：1’b0；*/
/*description:这是当rs485_fm_err_int_ena设置为1时，rs485_fm_err_int_raw的状态位。*/
#define UART_RS485_FRM_ERR_INT_ST  (BIT(16))
#define UART_RS485_FRM_ERR_INT_ST_M  (BIT(16))
#define UART_RS485_FRM_ERR_INT_ST_V  0x1
#define UART_RS485_FRM_ERR_INT_ST_S  16
/* UART_RS485_PARITY_ERR_INT_ST:RO；位位置：[15]；默认值：1’b0；*/
/*description:这是rs485_parity_int_ena设置为1时rs485_parite_err_int_raw的状态位。*/
#define UART_RS485_PARITY_ERR_INT_ST  (BIT(15))
#define UART_RS485_PARITY_ERR_INT_ST_M  (BIT(15))
#define UART_RS485_PARITY_ERR_INT_ST_V  0x1
#define UART_RS485_PARITY_ERR_INT_ST_S  15
/* UART_TX_DONE_INT_ST:RO；位位置：[14]；默认值：1’b0；*/
/*description:这是tx_done_int_ena设置为1时tx_done_It_raw的状态位。*/
#define UART_TX_DONE_INT_ST  (BIT(14))
#define UART_TX_DONE_INT_ST_M  (BIT(14))
#define UART_TX_DONE_INT_ST_V  0x1
#define UART_TX_DONE_INT_ST_S  14
/* UART_TX_bk_IDLE_DONE_INT_ST:RO；位位置：[13]；默认值：1’b0；*/
/*description:这是当tx_brk_idle_done_int_ena设置为1时，tx_brk_idle_done_int.raw的stauts位。*/
#define UART_TX_BRK_IDLE_DONE_INT_ST  (BIT(13))
#define UART_TX_BRK_IDLE_DONE_INT_ST_M  (BIT(13))
#define UART_TX_BRK_IDLE_DONE_INT_ST_V  0x1
#define UART_TX_BRK_IDLE_DONE_INT_ST_S  13
/* UART_TX_bk_DONE_INT_ST:RO；位位置：[12]；默认值：1’b0；*/
/*description:这是tx_brk_done_int_ena设置为1时tx_brk_done_int_raw的状态位。*/
#define UART_TX_BRK_DONE_INT_ST  (BIT(12))
#define UART_TX_BRK_DONE_INT_ST_M  (BIT(12))
#define UART_TX_BRK_DONE_INT_ST_V  0x1
#define UART_TX_BRK_DONE_INT_ST_S  12
/* UART_gillid_DET_INT_ST:RO；位位置：[11]；默认值：1’b0；*/
/*description:这是当glitch_det_int_ena设置为1时，glitch_ded_int_raw的状态位。*/
#define UART_GLITCH_DET_INT_ST  (BIT(11))
#define UART_GLITCH_DET_INT_ST_M  (BIT(11))
#define UART_GLITCH_DET_INT_ST_V  0x1
#define UART_GLITCH_DET_INT_ST_S  11
/* UART_SW_XOFF_INT_ST:RO；位位置：[10]；默认值：1’b0；*/
/*description:这是sw_xoff_int_ena设置为1时sw_xoff_int_raw的状态位。*/
#define UART_SW_XOFF_INT_ST  (BIT(10))
#define UART_SW_XOFF_INT_ST_M  (BIT(10))
#define UART_SW_XOFF_INT_ST_V  0x1
#define UART_SW_XOFF_INT_ST_S  10
/* UART_SW_XON_INT_ST:RO；位位置：[9]；默认值：1’b0；*/
/*description:这是sw_xon_int_ena设置为1时sw_xon_ent_raw的状态位。*/
#define UART_SW_XON_INT_ST  (BIT(9))
#define UART_SW_XON_INT_ST_M  (BIT(9))
#define UART_SW_XON_INT_ST_V  0x1
#define UART_SW_XON_INT_ST_S  9
/* UART_RXFIFO_out_INT_ST:RO；位位置：[8]；默认值：1’b0；*/
/*description:这是rxfifo_out_int_ena设置为1时rxfify_out_int_raw的状态位。*/
#define UART_RXFIFO_TOUT_INT_ST  (BIT(8))
#define UART_RXFIFO_TOUT_INT_ST_M  (BIT(8))
#define UART_RXFIFO_TOUT_INT_ST_V  0x1
#define UART_RXFIFO_TOUT_INT_ST_S  8
/* UART_BRK_DET_INT:RO；位位置：[7]；默认值：1’b0；*/
/*description:这是brk_det_int_ena设置为1时brk_dep_int_raw的状态位。*/
#define UART_BRK_DET_INT_ST  (BIT(7))
#define UART_BRK_DET_INT_ST_M  (BIT(7))
#define UART_BRK_DET_INT_ST_V  0x1
#define UART_BRK_DET_INT_ST_S  7
/* UART_CTS_CHG_INT_ST:RO；位位置：[6]；默认值：1’b0；*/
/*description:这是当cts_chg_int_ena设置为1时，cts_chg_int_raw的状态位。*/
#define UART_CTS_CHG_INT_ST  (BIT(6))
#define UART_CTS_CHG_INT_ST_M  (BIT(6))
#define UART_CTS_CHG_INT_ST_V  0x1
#define UART_CTS_CHG_INT_ST_S  6
/* UART_DSR_CHG_INT_ST:RO；位位置：[5]；默认值：1’b0；*/
/*description:这是dsr_chg_int_ena设置为1时dsr_chg_int_raw的状态位。*/
#define UART_DSR_CHG_INT_ST  (BIT(5))
#define UART_DSR_CHG_INT_ST_M  (BIT(5))
#define UART_DSR_CHG_INT_ST_V  0x1
#define UART_DSR_CHG_INT_ST_S  5
/* UART_RXFIFO_vf_INT_ST:RO；位位置：[4]；默认值：1’b0；*/
/*description:这是当rxfifo_ovf_int_ena设置为1时rxfifouovf_int_raw的状态位。*/
#define UART_RXFIFO_OVF_INT_ST  (BIT(4))
#define UART_RXFIFO_OVF_INT_ST_M  (BIT(4))
#define UART_RXFIFO_OVF_INT_ST_V  0x1
#define UART_RXFIFO_OVF_INT_ST_S  4
/* UART_FRM_ERR_INT_ST:RO；位位置：[3]；默认值：1’b0；*/
/*description:这是当fm_err_int_ena设置为1时frm_err_int_raw的状态位。*/
#define UART_FRM_ERR_INT_ST  (BIT(3))
#define UART_FRM_ERR_INT_ST_M  (BIT(3))
#define UART_FRM_ERR_INT_ST_V  0x1
#define UART_FRM_ERR_INT_ST_S  3
/* UART_PARITY_ERR_INT_ST:RO；位位置：[2]；默认值：1’b0；*/
/*description:这是parity_err_int_ena设置为1时parity_err _int_raw的状态位。*/
#define UART_PARITY_ERR_INT_ST  (BIT(2))
#define UART_PARITY_ERR_INT_ST_M  (BIT(2))
#define UART_PARITY_ERR_INT_ST_V  0x1
#define UART_PARITY_ERR_INT_ST_S  2
/* UART_TXFIFO_EMPTY_INT_ST:RO；位位置：[1]；默认值：1’b0；*/
/*description:这是当txfifo_empty_int_ena设置为1时，txfifo_oempty_int_raw的状态位。*/
#define UART_TXFIFO_EMPTY_INT_ST  (BIT(1))
#define UART_TXFIFO_EMPTY_INT_ST_M  (BIT(1))
#define UART_TXFIFO_EMPTY_INT_ST_V  0x1
#define UART_TXFIFO_EMPTY_INT_ST_S  1
/* UART_RXFIFO_FULL_INT_ST:RO；位位置：[0]；默认值：1’b0；*/
/*description:这是当rxifif_full_int_ena设置为1时rxififufull_int_raw的状态位。*/
#define UART_RXFIFO_FULL_INT_ST  (BIT(0))
#define UART_RXFIFO_FULL_INT_ST_M  (BIT(0))
#define UART_RXFIFO_FULL_INT_ST_V  0x1
#define UART_RXFIFO_FULL_INT_ST_S  0

#define UART_INT_ENA_REG(i)          (REG_UART_BASE(i) + 0xC)
/* UART_AT_CMD_CHAR_DET_INT_ENA:R/W；位位置：[18]；默认值：1’b0；*/
/*description:这是at_cmd_char_det_int_st寄存器的启用位。*/
#define UART_AT_CMD_CHAR_DET_INT_ENA  (BIT(18))
#define UART_AT_CMD_CHAR_DET_INT_ENA_M  (BIT(18))
#define UART_AT_CMD_CHAR_DET_INT_ENA_V  0x1
#define UART_AT_CMD_CHAR_DET_INT_ENA_S  18
/* UART_RS485_CLASH_INT_ENA:R/W；位位置：[17]；默认值：1’b0；*/
/*description:这是rs485_clash_int_st寄存器的启用位。*/
#define UART_RS485_CLASH_INT_ENA  (BIT(17))
#define UART_RS485_CLASH_INT_ENA_M  (BIT(17))
#define UART_RS485_CLASH_INT_ENA_V  0x1
#define UART_RS485_CLASH_INT_ENA_S  17
/* UART_RS485_FRM_ERR_INT_ENA:R/W；位位置：[16]；默认值：1’b0；*/
/*description:这是rs485_parity_err_int_st寄存器的启用位。*/
#define UART_RS485_FRM_ERR_INT_ENA  (BIT(16))
#define UART_RS485_FRM_ERR_INT_ENA_M  (BIT(16))
#define UART_RS485_FRM_ERR_INT_ENA_V  0x1
#define UART_RS485_FRM_ERR_INT_ENA_S  16
/* UART_RS485_PARITY_ERR_INT_ENA:R/W；位位置：[15]；默认值：1’b0；*/
/*description:这是rs485_parity_err_int_st寄存器的启用位。*/
#define UART_RS485_PARITY_ERR_INT_ENA  (BIT(15))
#define UART_RS485_PARITY_ERR_INT_ENA_M  (BIT(15))
#define UART_RS485_PARITY_ERR_INT_ENA_V  0x1
#define UART_RS485_PARITY_ERR_INT_ENA_S  15
/* UART_TX_DONE_INT_ENA:R/W；位位置：[14]；默认值：1’b0；*/
/*description:这是tx_done_int_st寄存器的启用位。*/
#define UART_TX_DONE_INT_ENA  (BIT(14))
#define UART_TX_DONE_INT_ENA_M  (BIT(14))
#define UART_TX_DONE_INT_ENA_V  0x1
#define UART_TX_DONE_INT_ENA_S  14
/* UART_TX_bk_IDLE_DONE_INT_ENA：R/W；位位置：[13]；默认值：1’b0；*/
/*description:这是tx_brk_idle_done_int_st寄存器的启用位。*/
#define UART_TX_BRK_IDLE_DONE_INT_ENA  (BIT(13))
#define UART_TX_BRK_IDLE_DONE_INT_ENA_M  (BIT(13))
#define UART_TX_BRK_IDLE_DONE_INT_ENA_V  0x1
#define UART_TX_BRK_IDLE_DONE_INT_ENA_S  13
/* UART_TX_bk_DONE_INT_ENA：R/W；位位置：[12]；默认值：1’b0；*/
/*description:这是tx_brk_done_int_st寄存器的启用位。*/
#define UART_TX_BRK_DONE_INT_ENA  (BIT(12))
#define UART_TX_BRK_DONE_INT_ENA_M  (BIT(12))
#define UART_TX_BRK_DONE_INT_ENA_V  0x1
#define UART_TX_BRK_DONE_INT_ENA_S  12
/* UART_gillid_DET_INT_ENA:R/W；位位置：[11]；默认值：1’b0；*/
/*description:这是glitch_det_int_st寄存器的启用位。*/
#define UART_GLITCH_DET_INT_ENA  (BIT(11))
#define UART_GLITCH_DET_INT_ENA_M  (BIT(11))
#define UART_GLITCH_DET_INT_ENA_V  0x1
#define UART_GLITCH_DET_INT_ENA_S  11
/* UART_SW_XOFF_INT_ENA:R/W；位位置：[10]；默认值：1’b0；*/
/*description:这是sw_xoff_int_st寄存器的启用位。*/
#define UART_SW_XOFF_INT_ENA  (BIT(10))
#define UART_SW_XOFF_INT_ENA_M  (BIT(10))
#define UART_SW_XOFF_INT_ENA_V  0x1
#define UART_SW_XOFF_INT_ENA_S  10
/* UART_SW_XON_INT_ENA:R/W；位位置：[9]；默认值：1’b0；*/
/*description:这是sw_xon_int_st寄存器的启用位。*/
#define UART_SW_XON_INT_ENA  (BIT(9))
#define UART_SW_XON_INT_ENA_M  (BIT(9))
#define UART_SW_XON_INT_ENA_V  0x1
#define UART_SW_XON_INT_ENA_S  9
/* UART_RXFIFO_out_INT_ENA:R/W；位位置：[8]；默认值：1’b0；*/
/*description:这是rxifo_out_int_st寄存器的启用位。*/
#define UART_RXFIFO_TOUT_INT_ENA  (BIT(8))
#define UART_RXFIFO_TOUT_INT_ENA_M  (BIT(8))
#define UART_RXFIFO_TOUT_INT_ENA_V  0x1
#define UART_RXFIFO_TOUT_INT_ENA_S  8
/* UART_BRK_DET_INT_ENA:R/W；位位置：[7]；默认值：1’b0；*/
/*description:这是brk_det_int寄存器的启用位。*/
#define UART_BRK_DET_INT_ENA  (BIT(7))
#define UART_BRK_DET_INT_ENA_M  (BIT(7))
#define UART_BRK_DET_INT_ENA_V  0x1
#define UART_BRK_DET_INT_ENA_S  7
/* UART_CTS_CHG_INT_ENA:R/W；位位置：[6]；默认值：1’b0；*/
/*description:这是cts_chg_int_st寄存器的启用位。*/
#define UART_CTS_CHG_INT_ENA  (BIT(6))
#define UART_CTS_CHG_INT_ENA_M  (BIT(6))
#define UART_CTS_CHG_INT_ENA_V  0x1
#define UART_CTS_CHG_INT_ENA_S  6
/* UART_DSR_CHG_INT_ENA:R/W；位位置：[5]；默认值：1’b0；*/
/*description:这是dsr_chg_int_st寄存器的启用位。*/
#define UART_DSR_CHG_INT_ENA  (BIT(5))
#define UART_DSR_CHG_INT_ENA_M  (BIT(5))
#define UART_DSR_CHG_INT_ENA_V  0x1
#define UART_DSR_CHG_INT_ENA_S  5
/* UART_RXFIFO_vf_INT_ENA:R/W；位位置：[4]；默认值：1’b0；*/
/*description:这是rxfifo_ovf_int_st寄存器的启用位。*/
#define UART_RXFIFO_OVF_INT_ENA  (BIT(4))
#define UART_RXFIFO_OVF_INT_ENA_M  (BIT(4))
#define UART_RXFIFO_OVF_INT_ENA_V  0x1
#define UART_RXFIFO_OVF_INT_ENA_S  4
/* UART_FRM_ERR_INT_ENA:R/W；位位置：[3]；默认值：1’b0；*/
/*description:这是frm_err_int_st寄存器的启用位。*/
#define UART_FRM_ERR_INT_ENA  (BIT(3))
#define UART_FRM_ERR_INT_ENA_M  (BIT(3))
#define UART_FRM_ERR_INT_ENA_V  0x1
#define UART_FRM_ERR_INT_ENA_S  3
/* UART_partity_ERR_INT_ENA:R/W；位位置：[2]；默认值：1’b0；*/
/*description:这是parity_err_int_st寄存器的启用位。*/
#define UART_PARITY_ERR_INT_ENA  (BIT(2))
#define UART_PARITY_ERR_INT_ENA_M  (BIT(2))
#define UART_PARITY_ERR_INT_ENA_V  0x1
#define UART_PARITY_ERR_INT_ENA_S  2
/* UART_TXFIFO_EMPTY_INT_ENA:R/W；位位置：[1]；默认值：1’b0；*/
/*description:这是rxifo_full_int_st寄存器的启用位。*/
#define UART_TXFIFO_EMPTY_INT_ENA  (BIT(1))
#define UART_TXFIFO_EMPTY_INT_ENA_M  (BIT(1))
#define UART_TXFIFO_EMPTY_INT_ENA_V  0x1
#define UART_TXFIFO_EMPTY_INT_ENA_S  1
/* UART_RXFIFO_FULL_INT_ENA:R/W；位位置：[0]；默认值：1’b0；*/
/*description:这是rxifo_full_int_st寄存器的启用位。*/
#define UART_RXFIFO_FULL_INT_ENA  (BIT(0))
#define UART_RXFIFO_FULL_INT_ENA_M  (BIT(0))
#define UART_RXFIFO_FULL_INT_ENA_V  0x1
#define UART_RXFIFO_FULL_INT_ENA_S  0

#define UART_INT_CLR_REG(i)          (REG_UART_BASE(i) + 0x10)
/* UART_AT_CMD_CHAR_DET_INT_CLR:WO；位位置：[18]；默认值：1’b0；*/
/*description:设置此位以清除at_cmd_char_det_int_raw中断。*/
#define UART_AT_CMD_CHAR_DET_INT_CLR  (BIT(18))
#define UART_AT_CMD_CHAR_DET_INT_CLR_M  (BIT(18))
#define UART_AT_CMD_CHAR_DET_INT_CLR_V  0x1
#define UART_AT_CMD_CHAR_DET_INT_CLR_S  18
/* UART_RS485_CLASH_INT_CLR:WO；位位置：[17]；默认值：1’b0；*/
/*description:设置此位以清除rs485_clash_int_raw中断。*/
#define UART_RS485_CLASH_INT_CLR  (BIT(17))
#define UART_RS485_CLASH_INT_CLR_M  (BIT(17))
#define UART_RS485_CLASH_INT_CLR_V  0x1
#define UART_RS485_CLASH_INT_CLR_S  17
/* UART_RS485_FRM_ERR_INT_CLR:WO；位位置：[16]；默认值：1’b0；*/
/*description:设置此位以清除rs485_frm_err_int_raw中断。*/
#define UART_RS485_FRM_ERR_INT_CLR  (BIT(16))
#define UART_RS485_FRM_ERR_INT_CLR_M  (BIT(16))
#define UART_RS485_FRM_ERR_INT_CLR_V  0x1
#define UART_RS485_FRM_ERR_INT_CLR_S  16
/* UART_RS485_PARITY_ERR_INT_CLR:WO；位位置：[15]；默认值：1’b0；*/
/*description:设置此位以清除rs485_parity_err_int_raw中断。*/
#define UART_RS485_PARITY_ERR_INT_CLR  (BIT(15))
#define UART_RS485_PARITY_ERR_INT_CLR_M  (BIT(15))
#define UART_RS485_PARITY_ERR_INT_CLR_V  0x1
#define UART_RS485_PARITY_ERR_INT_CLR_S  15
/* UART_TX_DONE_INT_CLR:WO；位位置：[14]；默认值：1’b0；*/
/*description:设置此位以清除tx_done_int_raw中断。*/
#define UART_TX_DONE_INT_CLR  (BIT(14))
#define UART_TX_DONE_INT_CLR_M  (BIT(14))
#define UART_TX_DONE_INT_CLR_V  0x1
#define UART_TX_DONE_INT_CLR_S  14
/* UART_TX_bark_IDLE_DONE_INT_CLR:WO；位位置：[13]；默认值：1’b0；*/
/*description:设置此位以清除tx_brk_idle_done_int_raw中断。*/
#define UART_TX_BRK_IDLE_DONE_INT_CLR  (BIT(13))
#define UART_TX_BRK_IDLE_DONE_INT_CLR_M  (BIT(13))
#define UART_TX_BRK_IDLE_DONE_INT_CLR_V  0x1
#define UART_TX_BRK_IDLE_DONE_INT_CLR_S  13
/* UART_TX_bk_DONE_INT_CLR:WO；位位置：[12]；默认值：1’b0；*/
/*description:设置此位以清除tx_brk_done_int_raw中断。。*/
#define UART_TX_BRK_DONE_INT_CLR  (BIT(12))
#define UART_TX_BRK_DONE_INT_CLR_M  (BIT(12))
#define UART_TX_BRK_DONE_INT_CLR_V  0x1
#define UART_TX_BRK_DONE_INT_CLR_S  12
/* UART_gillid_DET_INT_CLR:WO；位位置：[11]；默认值：1’b0；*/
/*description:设置此位以清除glitch_det_int_raw中断。*/
#define UART_GLITCH_DET_INT_CLR  (BIT(11))
#define UART_GLITCH_DET_INT_CLR_M  (BIT(11))
#define UART_GLITCH_DET_INT_CLR_V  0x1
#define UART_GLITCH_DET_INT_CLR_S  11
/* UART_SW_XOFF_INT_CLR:WO；位位置：[10]；默认值：1’b0；*/
/*description:设置此位以清除sw_xon_int_raw中断。*/
#define UART_SW_XOFF_INT_CLR  (BIT(10))
#define UART_SW_XOFF_INT_CLR_M  (BIT(10))
#define UART_SW_XOFF_INT_CLR_V  0x1
#define UART_SW_XOFF_INT_CLR_S  10
/* UART_SW_XON_INT_CLR:WO；位位置：[9]；默认值：1’b0；*/
/*description:设置此位以清除sw_xon_int_raw中断。*/
#define UART_SW_XON_INT_CLR  (BIT(9))
#define UART_SW_XON_INT_CLR_M  (BIT(9))
#define UART_SW_XON_INT_CLR_V  0x1
#define UART_SW_XON_INT_CLR_S  9
/* UART_RXFIFO_out_INT_CLR:WO；位位置：[8]；默认值：1’b0；*/
/*description:设置此位以清除rxifo_out_int_raw中断。*/
#define UART_RXFIFO_TOUT_INT_CLR  (BIT(8))
#define UART_RXFIFO_TOUT_INT_CLR_M  (BIT(8))
#define UART_RXFIFO_TOUT_INT_CLR_V  0x1
#define UART_RXFIFO_TOUT_INT_CLR_S  8
/* UART_BRK_DET_INT_CLR:WO；位位置：[7]；默认值：1’b0；*/
/*description:设置此位以清除brk_det_int_raw中断。*/
#define UART_BRK_DET_INT_CLR  (BIT(7))
#define UART_BRK_DET_INT_CLR_M  (BIT(7))
#define UART_BRK_DET_INT_CLR_V  0x1
#define UART_BRK_DET_INT_CLR_S  7
/* UART_CTS_CHG_INT_CLR:WO；位位置：[6]；默认值：1’b0；*/
/*description:设置此位以清除cts_chg_int_raw中断。*/
#define UART_CTS_CHG_INT_CLR  (BIT(6))
#define UART_CTS_CHG_INT_CLR_M  (BIT(6))
#define UART_CTS_CHG_INT_CLR_V  0x1
#define UART_CTS_CHG_INT_CLR_S  6
/* UART_DSR_CHG_INT_CLR:WO；位位置：[5]；默认值：1’b0；*/
/*description:设置此位以清除dsr_chg_int_raw中断。*/
#define UART_DSR_CHG_INT_CLR  (BIT(5))
#define UART_DSR_CHG_INT_CLR_M  (BIT(5))
#define UART_DSR_CHG_INT_CLR_V  0x1
#define UART_DSR_CHG_INT_CLR_S  5
/* UART_RXFIFO_ov_INT_CLR:WO；位位置：[4]；默认值：1’b0；*/
/*description:设置此位以清除rxfifo_ovf_int_raw中断。*/
#define UART_RXFIFO_OVF_INT_CLR  (BIT(4))
#define UART_RXFIFO_OVF_INT_CLR_M  (BIT(4))
#define UART_RXFIFO_OVF_INT_CLR_V  0x1
#define UART_RXFIFO_OVF_INT_CLR_S  4
/* UART_FRM_ERR_INT_CLR:WO；位位置：[3]；默认值：1’b0；*/
/*description:设置此位以清除frm_err_int_raw中断。*/
#define UART_FRM_ERR_INT_CLR  (BIT(3))
#define UART_FRM_ERR_INT_CLR_M  (BIT(3))
#define UART_FRM_ERR_INT_CLR_V  0x1
#define UART_FRM_ERR_INT_CLR_S  3
/* UART_PARITY_ERR_INT_CLR:WO；位位置：[2]；默认值：1’b0；*/
/*description:设置此位以清除parity_err_int_raw中断。*/
#define UART_PARITY_ERR_INT_CLR  (BIT(2))
#define UART_PARITY_ERR_INT_CLR_M  (BIT(2))
#define UART_PARITY_ERR_INT_CLR_V  0x1
#define UART_PARITY_ERR_INT_CLR_S  2
/* UART_TXFIFO_EMPTY_INT_CLR:WO；位位置：[1]；默认值：1’b0；*/
/*description:设置此位以清除txfifo_empty_int_raw中断。*/
#define UART_TXFIFO_EMPTY_INT_CLR  (BIT(1))
#define UART_TXFIFO_EMPTY_INT_CLR_M  (BIT(1))
#define UART_TXFIFO_EMPTY_INT_CLR_V  0x1
#define UART_TXFIFO_EMPTY_INT_CLR_S  1
/* UART_RXFIFO_FULL_INT_CLR:WO；位位置：[0]；默认值：1’b0；*/
/*description:设置此位以清除rxfifo_full_int_raw中断。*/
#define UART_RXFIFO_FULL_INT_CLR  (BIT(0))
#define UART_RXFIFO_FULL_INT_CLR_M  (BIT(0))
#define UART_RXFIFO_FULL_INT_CLR_V  0x1
#define UART_RXFIFO_FULL_INT_CLR_S  0

#define UART_CLKDIV_REG(i)          (REG_UART_BASE(i) + 0x14)
/* UART_CLKDIV_FRAG:R/W；比特位置：[23:20]；默认值：4'0；*/
/*description:寄存器值是分频器系数的小数部分。*/
#define UART_CLKDIV_FRAG  0x0000000F
#define UART_CLKDIV_FRAG_M  ((UART_CLKDIV_FRAG_V)<<(UART_CLKDIV_FRAG_S))
#define UART_CLKDIV_FRAG_V  0xF
#define UART_CLKDIV_FRAG_S  20
/* UART_CLKDIV:R/W；比特位置：[19:0]；默认值：20'h2B6；*/
/*description:寄存器值是分频器因数的整数部分。*/
#define UART_CLKDIV  0x000FFFFF
#define UART_CLKDIV_M  ((UART_CLKDIV_V)<<(UART_CLKDIV_S))
#define UART_CLKDIV_V  0xFFFFF
#define UART_CLKDIV_S  0

#define UART_AUTOBAUD_REG(i)          (REG_UART_BASE(i) + 0x18)
/* UART_gillid_FILT:R/W；比特位置：[15:8]；默认值：8'h10；*/
/*描述：当输入脉冲宽度低于该值时，该脉冲即为该值。该寄存器用于自动波特率检测过程。*/
#define UART_GLITCH_FILT  0x000000FF
#define UART_GLITCH_FILT_M  ((UART_GLITCH_FILT_V)<<(UART_GLITCH_FILT_S))
#define UART_GLITCH_FILT_V  0xFF
#define UART_GLITCH_FILT_S  8
/* UART_AUTOBAUD_EN:R/W；位位置：[0]；默认值：1’b0；*/
/*description:这是检测波特率的启用位。*/
#define UART_AUTOBAUD_EN  (BIT(0))
#define UART_AUTOBAUD_EN_M  (BIT(0))
#define UART_AUTOBAUD_EN_V  0x1
#define UART_AUTOBAUD_EN_S  0

#define UART_STATUS_REG(i)          (REG_UART_BASE(i) + 0x1C)
/* UART_TXD:RO；位位置：[31]；默认值：8'0；*/
/*描述：此寄存器表示内部uart rxd信号的电平值。*/
#define UART_TXD  (BIT(31))
#define UART_TXD_M  (BIT(31))
#define UART_TXD_V  0x1
#define UART_TXD_S  31
/* UART_RTSN:RO；位位置：[30]；默认值：1’b0；*/
/*description:此寄存器表示内部uart cts信号的电平值。*/
#define UART_RTSN  (BIT(30))
#define UART_RTSN_M  (BIT(30))
#define UART_RTSN_V  0x1
#define UART_RTSN_S  30
/* UART_dtn:RO；位位置：[29]；默认值：1’b0；*/
/*description:寄存器表示内部uart dsr信号的电平值。*/
#define UART_DTRN  (BIT(29))
#define UART_DTRN_M  (BIT(29))
#define UART_DTRN_V  0x1
#define UART_DTRN_S  29
/* UART_ST_UTX_OUT:RO；位位置：[27:24]；默认值：4'b0；*/
/*description:此寄存器存储发射器的有限状态机的值。0:TX_IDLE 1:TX_STRT 2:TX_DAT0 3:TX_DAT1 4:TX_DAT2 5:TX_DAT3 6:TX_DAT4 7:TX_DAT5 8:TX_DAT6 9:TX_DAT7 10:TX_PRTY 11:TX_STP1 12:TX_STP2 13:TX_DL0 14:TX_DL1*/
#define UART_ST_UTX_OUT  0x0000000F
#define UART_ST_UTX_OUT_M  ((UART_ST_UTX_OUT_V)<<(UART_ST_UTX_OUT_S))
#define UART_ST_UTX_OUT_V  0xF
#define UART_ST_UTX_OUT_S  24
/* UART_TXFIFO_CNT:RO；比特位置：[23:16]；默认值：8'b0；*/
/*描述：（tx_mem_cnt txfifo cnt）存储发射机fifo中有效数据的字节数。tx_mem_cnt存储3个最高有效位txfifo_cnt存储8个最低有效位。*/
#define UART_TXFIFO_CNT  0x000000FF
#define UART_TXFIFO_CNT_M  ((UART_TXFIFO_CNT_V)<<(UART_TXFIFO_CNT_S))
#define UART_TXFIFO_CNT_V  0xFF
#define UART_TXFIFO_CNT_S  16
/* UART_RXD:RO；位位置：[15]；默认值：1’b0；*/
/*描述：此寄存器存储内部uart rxd信号的电平值。*/
#define UART_RXD  (BIT(15))
#define UART_RXD_M  (BIT(15))
#define UART_RXD_V  0x1
#define UART_RXD_S  15
/* UART_CTSN:RO；位位置：[14]；默认值：1’b0；*/
/*description:此寄存器存储内部uart cts信号的电平值。*/
#define UART_CTSN  (BIT(14))
#define UART_CTSN_M  (BIT(14))
#define UART_CTSN_V  0x1
#define UART_CTSN_S  14
/* UART_DSRN:RO；位位置：[13]；默认值：1’b0；*/
/*description:此寄存器存储内部uart dsr信号的电平值。*/
#define UART_DSRN  (BIT(13))
#define UART_DSRN_M  (BIT(13))
#define UART_DSRN_V  0x1
#define UART_DSRN_S  13
/* UART_ST_URX_OUT:RO；位位置：[11:8]；默认值：4'b0；*/
/*description:此寄存器存储接收器的有限状态机的值。0:RX空闲1:RX字符串2:RX数据3:RX数据4:RX数据5:RX数据6:RX数据7:RX数据8:RX数据9:RX数据10:RX数据11:RX STP1 12:RX STP2 13:RX DL1*/
#define UART_ST_URX_OUT  0x0000000F
#define UART_ST_URX_OUT_M  ((UART_ST_URX_OUT_V)<<(UART_ST_URX_OUT_S))
#define UART_ST_URX_OUT_V  0xF
#define UART_ST_URX_OUT_S  8
/* UART_RXFIFO_CNT:RO；位位置：[7:0]；默认值：8'b0；*/
/*描述：（rxmemcnt rxfifocnt）存储接收器fifo中有效数据的字节数。rxmem_cnt寄存器存储3个最高有效位，rxifo_cnt存储8个最低有效位。*/
#define UART_RXFIFO_CNT  0x000000FF
#define UART_RXFIFO_CNT_M  ((UART_RXFIFO_CNT_V)<<(UART_RXFIFO_CNT_S))
#define UART_RXFIFO_CNT_V  0xFF
#define UART_RXFIFO_CNT_S  0

#define UART_CONF0_REG(i)          (REG_UART_BASE(i) + 0x20)
/* UART_TICK_REF_ALWAYS_ON:R/W；位位置：[27]；默认值：1’b1；*/
/*description:此寄存器用于选择时钟.1.apb时钟0:ref_tick*/
#define UART_TICK_REF_ALWAYS_ON  (BIT(27))
#define UART_TICK_REF_ALWAYS_ON_M  (BIT(27))
#define UART_TICK_REF_ALWAYS_ON_V  0x1
#define UART_TICK_REF_ALWAYS_ON_S  27
/* UART_ERR_WR_MASK:R/W；位位置：[26]；默认值：1’b0；*/
/*描述：1.当数据错误时，接收器停止在fifo中存储数据。0.receiver存储数据，即使接收到的数据是错误的。*/
#define UART_ERR_WR_MASK  (BIT(26))
#define UART_ERR_WR_MASK_M  (BIT(26))
#define UART_ERR_WR_MASK_V  0x1
#define UART_ERR_WR_MASK_S  26
/* UART_CLK_EN:R/W；位位置：[25]；默认值：1'0；*/
/*描述：1.强制打开寄存器的时钟。仅在写入寄存器时支持时钟*/
#define UART_CLK_EN  (BIT(25))
#define UART_CLK_EN_M  (BIT(25))
#define UART_CLK_EN_V  0x1
#define UART_CLK_EN_S  25
/* UART_DTR_INV：R/W；位位置：[24]；默认值：1'0；*/
/*description:设置此位以反转uart dtr信号的电平值。*/
#define UART_DTR_INV  (BIT(24))
#define UART_DTR_INV_M  (BIT(24))
#define UART_DTR_INV_V  0x1
#define UART_DTR_INV_S  24
/* UART_RTS_INV：R/W；位位置：[23]；默认值：1'0；*/
/*description:设置此位以反转uart rts信号的电平值。*/
#define UART_RTS_INV  (BIT(23))
#define UART_RTS_INV_M  (BIT(23))
#define UART_RTS_INV_V  0x1
#define UART_RTS_INV_S  23
/* UART_TXD_INV：R/W；位位置：[22]；默认值：1'0；*/
/*description:设置此位以反转uart txd信号的电平值。*/
#define UART_TXD_INV  (BIT(22))
#define UART_TXD_INV_M  (BIT(22))
#define UART_TXD_INV_V  0x1
#define UART_TXD_INV_S  22
/* UART_DSR_INV：R/W；位位置：[21]；默认值：1'0；*/
/*description:设置此位以反转uart dsr信号的电平值。*/
#define UART_DSR_INV  (BIT(21))
#define UART_DSR_INV_M  (BIT(21))
#define UART_DSR_INV_V  0x1
#define UART_DSR_INV_S  21
/* UART_CTS_INV：R/W；位位置：[20]；默认值：1'0；*/
/*description:设置此位以反转uart cts信号的电平值。*/
#define UART_CTS_INV  (BIT(20))
#define UART_CTS_INV_M  (BIT(20))
#define UART_CTS_INV_V  0x1
#define UART_CTS_INV_S  20
/* UART_RXD_INV:R/W；位位置：[19]；默认值：1'0；*/
/*description:设置此位以反转uart rxd信号的电平值。*/
#define UART_RXD_INV  (BIT(19))
#define UART_RXD_INV_M  (BIT(19))
#define UART_RXD_INV_V  0x1
#define UART_RXD_INV_S  19
/* UART_TXFIFO_RST:R/W；位位置：[18]；默认值：1'0；*/
/*description:设置此位以重置uart发射器的fifo。*/
#define UART_TXFIFO_RST  (BIT(18))
#define UART_TXFIFO_RST_M  (BIT(18))
#define UART_TXFIFO_RST_V  0x1
#define UART_TXFIFO_RST_S  18
/* UART_RXFIFO_RST:R/W；位位置：[17]；默认值：1'0；*/
/*description:设置此位以重置uart接收器的fifo。*/
#define UART_RXFIFO_RST  (BIT(17))
#define UART_RXFIFO_RST_M  (BIT(17))
#define UART_RXFIFO_RST_V  0x1
#define UART_RXFIFO_RST_S  17
/* UART_IRDA_EN:R/W；位位置：[16]；默认值：1'0；*/
/*description:设置此位以启用irda协议。*/
#define UART_IRDA_EN  (BIT(16))
#define UART_IRDA_EN_M  (BIT(16))
#define UART_IRDA_EN_V  0x1
#define UART_IRDA_EN_S  16
/* UART_TX_FLOW_EN:R/W；位位置：[15]；默认值：1’b0；*/
/*description:设置此位以启用变送器的流量控制功能。*/
#define UART_TX_FLOW_EN  (BIT(15))
#define UART_TX_FLOW_EN_M  (BIT(15))
#define UART_TX_FLOW_EN_V  0x1
#define UART_TX_FLOW_EN_S  15
/* UART_环回：R/W；位位置：[14]；默认值：1’b0；*/
/*description:设置此位以启用uart环回测试模式。*/
#define UART_LOOPBACK  (BIT(14))
#define UART_LOOPBACK_M  (BIT(14))
#define UART_LOOPBACK_V  0x1
#define UART_LOOPBACK_S  14
/* UART_IRDA_RX_INV:R/W；位位置：[13]；默认值：1’b0；*/
/*description:设置此位以反转irda接收机电平的电平值。*/
#define UART_IRDA_RX_INV  (BIT(13))
#define UART_IRDA_RX_INV_M  (BIT(13))
#define UART_IRDA_RX_INV_V  0x1
#define UART_IRDA_RX_INV_S  13
/* UART_IRDA_TX_INV:R/W；位位置：[12]；默认值：1’b0；*/
/*description:设置此位以反转irda发射机电平的电平值。*/
#define UART_IRDA_TX_INV  (BIT(12))
#define UART_IRDA_TX_INV_M  (BIT(12))
#define UART_IRDA_TX_INV_V  0x1
#define UART_IRDA_TX_INV_S  12
/* UART_IRDA_WCTL:R/W；位位置：[11]；默认值：1’b0；*/
/*说明：1.irda发射机的第11位与第10位相同。0.将irda发射器的第11位设置为0。*/
#define UART_IRDA_WCTL  (BIT(11))
#define UART_IRDA_WCTL_M  (BIT(11))
#define UART_IRDA_WCTL_V  0x1
#define UART_IRDA_WCTL_S  11
/* UART_IRDA_TX_EN:R/W；位位置：[10]；默认值：1’b0；*/
/*description:这是irda发射机的启动启用位。*/
#define UART_IRDA_TX_EN  (BIT(10))
#define UART_IRDA_TX_EN_M  (BIT(10))
#define UART_IRDA_TX_EN_V  0x1
#define UART_IRDA_TX_EN_S  10
/* UART_IRDA_DPLX:R/W；位位置：[9]；默认值：1’b0；*/
/*description:设置此位以启用irda环回模式。*/
#define UART_IRDA_DPLX  (BIT(9))
#define UART_IRDA_DPLX_M  (BIT(9))
#define UART_IRDA_DPLX_V  0x1
#define UART_IRDA_DPLX_S  9
/* UART_TXD_BRK:R/W；位位置：[8]；默认值：1’b0；*/
/*description:当发送数据的过程完成时，将此位设置为enbale发射机发送0。*/
#define UART_TXD_BRK  (BIT(8))
#define UART_TXD_BRK_M  (BIT(8))
#define UART_TXD_BRK_V  0x1
#define UART_TXD_BRK_S  8
/* UART_SW_DTR:R/W；位位置：[7]；默认值：1’b0；*/
/*说明：此寄存器用于配置软件流控制中使用的软件dtr信号。。*/
#define UART_SW_DTR  (BIT(7))
#define UART_SW_DTR_M  (BIT(7))
#define UART_SW_DTR_V  0x1
#define UART_SW_DTR_S  7
/* UART_SW_RTS:R/W；位位置：[6]；默认值：1’b0；*/
/*描述：此寄存器用于配置软件流控制中使用的软件rts信号。*/
#define UART_SW_RTS  (BIT(6))
#define UART_SW_RTS_M  (BIT(6))
#define UART_SW_RTS_V  0x1
#define UART_SW_RTS_S  6
/* UART_STOP_BIT_NUM:R/W；比特位置：[5:4]；默认值：2'd1；*/
/*description:此寄存器用于设置停止位的长度。1： 1位2:1.5位3:2位*/
#define UART_STOP_BIT_NUM  0x00000003
#define UART_STOP_BIT_NUM_M  ((UART_STOP_BIT_NUM_V)<<(UART_STOP_BIT_NUM_S))
#define UART_STOP_BIT_NUM_V  0x3
#define UART_STOP_BIT_NUM_S  4
/* UART_BIT_NUM:R/W；位位置：[3:2]；默认值：2'd3；*/
/*description:此寄存器用于设置数据长度：0:5位1:6位2:7位3:8位*/
#define UART_BIT_NUM  0x00000003
#define UART_BIT_NUM_M  ((UART_BIT_NUM_V)<<(UART_BIT_NUM_S))
#define UART_BIT_NUM_V  0x3
#define UART_BIT_NUM_S  2
/* UART_PARITY_EN:R/W；位位置：[1]；默认值：1’b0；*/
/*description:设置此位以启用uart奇偶校验。*/
#define UART_PARITY_EN  (BIT(1))
#define UART_PARITY_EN_M  (BIT(1))
#define UART_PARITY_EN_V  0x1
#define UART_PARITY_EN_S  1
/* UART_奇偶校验：R/W；位位置：[0]；默认值：1’b0；*/
/*description:此寄存器用于配置奇偶校验模式。0：偶数1：奇数*/
#define UART_PARITY  (BIT(0))
#define UART_PARITY_M  (BIT(0))
#define UART_PARITY_V  0x1
#define UART_PARITY_S  0

#define UART_CONF1_REG(i)          (REG_UART_BASE(i) + 0x24)
/* UART_RX_TOUT_EN:R/W；位位置：[31]；默认值：1’b0；*/
/*description:这是uart接收器超时函数的enble位。*/
#define UART_RX_TOUT_EN  (BIT(31))
#define UART_RX_TOUT_EN_M  (BIT(31))
#define UART_RX_TOUT_EN_V  0x1
#define UART_RX_TOUT_EN_S  31
/* UART_RX_TOUT_thrd:R/W；位位置：[30:24]；默认值：7'b0；*/
/*description:此寄存器用于配置uart接收器接收字节的超时值。*/
#define UART_RX_TOUT_THRHD  0x0000007F
#define UART_RX_TOUT_THRHD_M  ((UART_RX_TOUT_THRHD_V)<<(UART_RX_TOUT_THRHD_S))
#define UART_RX_TOUT_THRHD_V  0x7F
#define UART_RX_TOUT_THRHD_S  24
/* UART_RX_FLOW_EN:R/W；位位置：[23]；默认值：1’b0；*/
/*description:这是uart接收器的流启用位。1： 通过配置sw_rts信号选择软件流控制*/
#define UART_RX_FLOW_EN  (BIT(23))
#define UART_RX_FLOW_EN_M  (BIT(23))
#define UART_RX_FLOW_EN_V  0x1
#define UART_RX_FLOW_EN_S  23
/* UART_RX_FLOW_THRHD:R/W；比特位置：[22:16]；默认值：7'0；*/
/*描述：当接收器接收的数据超过其阈值时。接收机产生信号，告知发射机停止传输数据。阈值是（rx_flow_thrhd_h3 rx-flow_thrhd）。*/
#define UART_RX_FLOW_THRHD  0x0000007F
#define UART_RX_FLOW_THRHD_M  ((UART_RX_FLOW_THRHD_V)<<(UART_RX_FLOW_THRHD_S))
#define UART_RX_FLOW_THRHD_V  0x7F
#define UART_RX_FLOW_THRHD_S  16
/* UART_TXFIFO_EMPTY_thrd:R/W；比特位置：[14:8]；默认值：7'460；*/
/*描述：当发射机fifo中的数据量小于其阈值时。它将产生txfifoempty_int_raw中断。阈值为（tx_mem_empty_thrd txfifoempty.thrd）*/
#define UART_TXFIFO_EMPTY_THRHD  0x0000007F
#define UART_TXFIFO_EMPTY_THRHD_M  ((UART_TXFIFO_EMPTY_THRHD_V)<<(UART_TXFIFO_EMPTY_THRHD_S))
#define UART_TXFIFO_EMPTY_THRHD_V  0x7F
#define UART_TXFIFO_EMPTY_THRHD_S  8
/* UART_RXFIFO_FULL_THRHD:R/W；比特位置：[6:0]；默认值：7'460；*/
/*描述：当接收器接收的数据超过其阈值时。接收机将产生rxfiff_full_int_raw中断。阈值是（rx_flow_thrhd_h3 rxfiff_full_thrhd）。*/
#define UART_RXFIFO_FULL_THRHD  0x0000007F
#define UART_RXFIFO_FULL_THRHD_M  ((UART_RXFIFO_FULL_THRHD_V)<<(UART_RXFIFO_FULL_THRHD_S))
#define UART_RXFIFO_FULL_THRHD_V  0x7F
#define UART_RXFIFO_FULL_THRHD_S  0

#define UART_LOWPULSE_REG(i)          (REG_UART_BASE(i) + 0x28)
/* UART_LOWPULSE_MIN_CNT:RO；比特位置：[19:0]；默认值：20'FFFFF；*/
/*description:此寄存器存储低电平脉冲的最小持续时间值。它用于波特率检测过程。*/
#define UART_LOWPULSE_MIN_CNT  0x000FFFFF
#define UART_LOWPULSE_MIN_CNT_M  ((UART_LOWPULSE_MIN_CNT_V)<<(UART_LOWPULSE_MIN_CNT_S))
#define UART_LOWPULSE_MIN_CNT_V  0xFFFFF
#define UART_LOWPULSE_MIN_CNT_S  0

#define UART_HIGHPULSE_REG(i)          (REG_UART_BASE(i) + 0x2C)
/* UART_higpulse_MIN_CNT:RO；比特位置：[19:0]；默认值：20'FFFFF；*/
/*description:此寄存器存储高电平脉冲的最大持续时间值。它用于波特率检测过程。*/
#define UART_HIGHPULSE_MIN_CNT  0x000FFFFF
#define UART_HIGHPULSE_MIN_CNT_M  ((UART_HIGHPULSE_MIN_CNT_V)<<(UART_HIGHPULSE_MIN_CNT_S))
#define UART_HIGHPULSE_MIN_CNT_V  0xFFFFF
#define UART_HIGHPULSE_MIN_CNT_S  0

#define UART_RXD_CNT_REG(i)          (REG_UART_BASE(i) + 0x30)
/* UART_RXD_EDGE_CNT:RO；位位置：[9:0]；默认值：10'0；*/
/*description:此寄存器存储rxd边缘更改的计数。它用于波特率检测过程。*/
#define UART_RXD_EDGE_CNT  0x000003FF
#define UART_RXD_EDGE_CNT_M  ((UART_RXD_EDGE_CNT_V)<<(UART_RXD_EDGE_CNT_S))
#define UART_RXD_EDGE_CNT_V  0x3FF
#define UART_RXD_EDGE_CNT_S  0

#define UART_FLOW_CONF_REG(i)          (REG_UART_BASE(i) + 0x34)
/* UART_SEND_XOFF:R/W；位位置：[5]；默认值：1’b0；*/
/*description:设置此位以发送xoff字符。它由硬件自动清除。*/
#define UART_SEND_XOFF  (BIT(5))
#define UART_SEND_XOFF_M  (BIT(5))
#define UART_SEND_XOFF_V  0x1
#define UART_SEND_XOFF_S  5
/* UART_SEND_XON:R/W；位位置：[4]；默认值：1’b0；*/
/*description:设置此位以发送xon字符。它由硬件自动清除。*/
#define UART_SEND_XON  (BIT(4))
#define UART_SEND_XON_M  (BIT(4))
#define UART_SEND_XON_V  0x1
#define UART_SEND_XON_S  4
/* UART_FORCE_off:R/W；位位置：[3]；默认值：1’b0；*/
/*description:设置此位以设置ctsn，使发射器能够继续发送数据。*/
#define UART_FORCE_XOFF  (BIT(3))
#define UART_FORCE_XOFF_M  (BIT(3))
#define UART_FORCE_XOFF_V  0x1
#define UART_FORCE_XOFF_S  3
/* UART_FORCE_XON:R/W；位位置：[2]；默认值：1’b0；*/
/*description:将此位设置为清除ctsn以停止发射器发送数据。*/
#define UART_FORCE_XON  (BIT(2))
#define UART_FORCE_XON_M  (BIT(2))
#define UART_FORCE_XON_V  0x1
#define UART_FORCE_XON_S  2
/* UART_XONOFF_DEL:R/W；位位置：[1]；默认值：1’b0；*/
/*description:设置此位以从接收的数据中删除流控制字符。*/
#define UART_XONOFF_DEL  (BIT(1))
#define UART_XONOFF_DEL_M  (BIT(1))
#define UART_XONOFF_DEL_V  0x1
#define UART_XONOFF_DEL_S  1
/* UART_SW_FLOW_CON_EN:R/W；位位置：[0]；默认值：1’b0；*/
/*description:设置此位以启用软件流控制。它与寄存器swxon或swxoff一起使用。*/
#define UART_SW_FLOW_CON_EN  (BIT(0))
#define UART_SW_FLOW_CON_EN_M  (BIT(0))
#define UART_SW_FLOW_CON_EN_V  0x1
#define UART_SW_FLOW_CON_EN_S  0

#define UART_SLEEP_CONF_REG(i)          (REG_UART_BASE(i) + 0x38)
/* UART_ACTIVE_THRESHOLD:R/W；位位置：[9:0]；默认值：10'hf0；*/
/*description:当输入rxd边缘变化超过此寄存器值时。uart从轻睡眠模式激活。*/
#define UART_ACTIVE_THRESHOLD  0x000003FF
#define UART_ACTIVE_THRESHOLD_M  ((UART_ACTIVE_THRESHOLD_V)<<(UART_ACTIVE_THRESHOLD_S))
#define UART_ACTIVE_THRESHOLD_V  0x3FF
#define UART_ACTIVE_THRESHOLD_S  0

#define UART_SWFC_CONF_REG(i)          (REG_UART_BASE(i) + 0x3C)
/* UART_XOFF_CHAR：R/W；位位置：[31:24]；默认值：8'h13；*/
/*description:此寄存器存储xoff流控制字符。*/
#define UART_XOFF_CHAR  0x000000FF
#define UART_XOFF_CHAR_M  ((UART_XOFF_CHAR_V)<<(UART_XOFF_CHAR_S))
#define UART_XOFF_CHAR_V  0xFF
#define UART_XOFF_CHAR_S  24
/* UART_XON_CHAR：R/W；比特位置：[23:16]；默认值：8'h11；*/
/*description:此寄存器存储xon流控制字符。*/
#define UART_XON_CHAR  0x000000FF
#define UART_XON_CHAR_M  ((UART_XON_CHAR_V)<<(UART_XON_CHAR_S))
#define UART_XON_CHAR_V  0xFF
#define UART_XON_CHAR_S  16
/* UART_XOFF_THRESHOLD:R/W；比特位置：[15:8]；默认值：8'he0；*/
/*description:当接收器fifo中的数据量小于此寄存器值时。它将发送uart_swflow_conen设置为1的xon字符。*/
#define UART_XOFF_THRESHOLD  0x000000FF
#define UART_XOFF_THRESHOLD_M  ((UART_XOFF_THRESHOLD_V)<<(UART_XOFF_THRESHOLD_S))
#define UART_XOFF_THRESHOLD_V  0xFF
#define UART_XOFF_THRESHOLD_S  8
/* UART_XON_THRESHOLD:R/W；位位置：[7:0]；默认值：8'0；*/
/*描述：当接收器fifo中的数据量大于此寄存器值时。它将发送uart_swflow_conen设置为1的xoff字符。*/
#define UART_XON_THRESHOLD  0x000000FF
#define UART_XON_THRESHOLD_M  ((UART_XON_THRESHOLD_V)<<(UART_XON_THRESHOLD_S))
#define UART_XON_THRESHOLD_V  0xFF
#define UART_XON_THRESHOLD_S  0

#define UART_IDLE_CONF_REG(i)          (REG_UART_BASE(i) + 0x40)
/* UART_TX_bk_NUM:R/W；位位置：[27:20]；默认值：8'ha；*/
/*description:此寄存器用于在发送数据的过程完成后配置num of 0 send。当txd_brk设置为1时，它是活动的。*/
#define UART_TX_BRK_NUM  0x000000FF
#define UART_TX_BRK_NUM_M  ((UART_TX_BRK_NUM_V)<<(UART_TX_BRK_NUM_S))
#define UART_TX_BRK_NUM_V  0xFF
#define UART_TX_BRK_NUM_S  20
/* UART_TX_IDLE_NUM:R/W；比特位置：[19:10]；默认值：10'h100；*/
/*description:此寄存器用于配置传输之间的持续时间。*/
#define UART_TX_IDLE_NUM  0x000003FF
#define UART_TX_IDLE_NUM_M  ((UART_TX_IDLE_NUM_V)<<(UART_TX_IDLE_NUM_S))
#define UART_TX_IDLE_NUM_V  0x3FF
#define UART_TX_IDLE_NUM_S  10
/* UART_RX_IDLE_THRHD:R/W；位位置：[9:0]；默认值：10'h100；*/
/*描述：当接收器接收字节数据所花费的时间超过此寄存器值时。它将产生用于uhci停止接收数据的帧结束信号。*/
#define UART_RX_IDLE_THRHD  0x000003FF
#define UART_RX_IDLE_THRHD_M  ((UART_RX_IDLE_THRHD_V)<<(UART_RX_IDLE_THRHD_S))
#define UART_RX_IDLE_THRHD_V  0x3FF
#define UART_RX_IDLE_THRHD_S  0

#define UART_RS485_CONF_REG(i)          (REG_UART_BASE(i) + 0x44)
/* UART_RS485_TX_DLY_NUM:R/W；比特位置：[9:6]；默认值：4'b0；*/
/*说明：此寄存器用于延迟变送器的内部数据信号。*/
#define UART_RS485_TX_DLY_NUM  0x0000000F
#define UART_RS485_TX_DLY_NUM_M  ((UART_RS485_TX_DLY_NUM_V)<<(UART_RS485_TX_DLY_NUM_S))
#define UART_RS485_TX_DLY_NUM_V  0xF
#define UART_RS485_TX_DLY_NUM_S  6
/* UART_RS485_RX_DLY_NUM:R/W；位位置：[5]；默认值：1’b0；*/
/*描述：此寄存器用于延迟接收器的内部数据信号。*/
#define UART_RS485_RX_DLY_NUM  (BIT(5))
#define UART_RS485_RX_DLY_NUM_M  (BIT(5))
#define UART_RS485_RX_DLY_NUM_V  0x1
#define UART_RS485_RX_DLY_NUM_S  5
/* UART_RS485RXBY_TX_EN:R/W；位位置：[4]；默认值：1’b0；*/
/*描述：1：当rs485的接收机忙时，启用rs485的发射机发送数据。0:rs485的发射机在接收机忙时不应发送数据。*/
#define UART_RS485RXBY_TX_EN  (BIT(4))
#define UART_RS485RXBY_TX_EN_M  (BIT(4))
#define UART_RS485RXBY_TX_EN_V  0x1
#define UART_RS485RXBY_TX_EN_S  4
/* UART_RS485TX_RX_EN:R/W；位位置：[3]；默认值：1’b0；*/
/*description:设置此位以启用环回发射器的输出数据信号到接收器的输入数据信号。*/
#define UART_RS485TX_RX_EN  (BIT(3))
#define UART_RS485TX_RX_EN_M  (BIT(3))
#define UART_RS485TX_RX_EN_V  0x1
#define UART_RS485TX_RX_EN_S  3
/* UART_DL1_EN:R/W；位位置：[2]；默认值：1’b0；*/
/*description:设置此位将停止位延迟1位。*/
#define UART_DL1_EN  (BIT(2))
#define UART_DL1_EN_M  (BIT(2))
#define UART_DL1_EN_V  0x1
#define UART_DL1_EN_S  2
/* UART_DL0_EN:R/W；位位置：[1]；默认值：1’b0；*/
/*description:设置此位将停止位延迟1位。*/
#define UART_DL0_EN  (BIT(1))
#define UART_DL0_EN_M  (BIT(1))
#define UART_DL0_EN_V  0x1
#define UART_DL0_EN_S  1
/* UART_RS485_EN:R/W；位位置：[0]；默认值：1’b0；*/
/*description:设置此位以选择rs485模式。*/
#define UART_RS485_EN  (BIT(0))
#define UART_RS485_EN_M  (BIT(0))
#define UART_RS485_EN_V  0x1
#define UART_RS485_EN_S  0

#define UART_AT_CMD_PRECNT_REG(i)          (REG_UART_BASE(i) + 0x48)
/* UART_PRE_IDLE_NUM:R/W；比特位置：[23:0]；默认值：24'h186a00；*/
/*description:此寄存器用于配置接收器接收第一个at_cmd之前的空闲持续时间。当持续时间小于该寄存器值时，它不会将接收到的下一个数据作为atcmdchar。*/
#define UART_PRE_IDLE_NUM  0x00FFFFFF
#define UART_PRE_IDLE_NUM_M  ((UART_PRE_IDLE_NUM_V)<<(UART_PRE_IDLE_NUM_S))
#define UART_PRE_IDLE_NUM_V  0xFFFFFF
#define UART_PRE_IDLE_NUM_S  0

#define UART_AT_CMD_POSTCNT_REG(i)          (REG_UART_BASE(i) + 0x4c)
/* UART_POST_IDLE_NUM:R/W；比特位置：[23:0]；默认值：24'h186a00；*/
/*description:此寄存器用于配置上一个at_cmd和下一个数据之间的持续时间。当持续时间小于此寄存器值时，它不会将先前的数据作为atcmdchar。*/
#define UART_POST_IDLE_NUM  0x00FFFFFF
#define UART_POST_IDLE_NUM_M  ((UART_POST_IDLE_NUM_V)<<(UART_POST_IDLE_NUM_S))
#define UART_POST_IDLE_NUM_V  0xFFFFFF
#define UART_POST_IDLE_NUM_S  0

#define UART_AT_CMD_GAPTOUT_REG(i)          (REG_UART_BASE(i) + 0x50)
/* UART_RX_GAP_out：R/W；比特位置：[23:0]；默认值：24'h1e00；*/
/*description:此寄存器用于配置at_cmd字符之间的持续时间。当持续时间小于此寄存器值时，它不会将数据作为连续的atcmd字符。*/
#define UART_RX_GAP_TOUT  0x00FFFFFF
#define UART_RX_GAP_TOUT_M  ((UART_RX_GAP_TOUT_V)<<(UART_RX_GAP_TOUT_S))
#define UART_RX_GAP_TOUT_V  0xFFFFFF
#define UART_RX_GAP_TOUT_S  0

#define UART_AT_CMD_CHAR_REG(i)          (REG_UART_BASE(i) + 0x54)
/* UART_CHAR_NUM:R/W；比特位置：[15:8]；默认值：8'h3；*/
/*description:此寄存器用于配置接收器接收的连续at_cmd字符数。*/
#define UART_CHAR_NUM  0x000000FF
#define UART_CHAR_NUM_M  ((UART_CHAR_NUM_V)<<(UART_CHAR_NUM_S))
#define UART_CHAR_NUM_V  0xFF
#define UART_CHAR_NUM_S  8
/* UART_AT_CMD_CHAR:R/W；位位置：[7:0]；默认值：8'h2b；*/
/*description:此寄存器用于配置at_cmd char的内容。*/
#define UART_AT_CMD_CHAR  0x000000FF
#define UART_AT_CMD_CHAR_M  ((UART_AT_CMD_CHAR_V)<<(UART_AT_CMD_CHAR_S))
#define UART_AT_CMD_CHAR_V  0xFF
#define UART_AT_CMD_CHAR_S  0

#define UART_MEM_CONF_REG(i)          (REG_UART_BASE(i) + 0x58)
/* UART_TX_MEM_EMPTY_thrd:R/W；位位置：[30:28]；默认值：3'h0；*/
/*描述：请参阅txfifoempty_thrd的描述。*/
#define UART_TX_MEM_EMPTY_THRHD  0x00000007
#define UART_TX_MEM_EMPTY_THRHD_M  ((UART_TX_MEM_EMPTY_THRHD_V)<<(UART_TX_MEM_EMPTY_THRHD_S))
#define UART_TX_MEM_EMPTY_THRHD_V  0x7
#define UART_TX_MEM_EMPTY_THRHD_S  28
/* UART_RX_MEM_FULL_THRHD:R/W；位位置：[27:25]；默认值：3'h0；*/
/*description:请参阅rxfiffull_thrhd的描述。*/
#define UART_RX_MEM_FULL_THRHD  0x00000007
#define UART_RX_MEM_FULL_THRHD_M  ((UART_RX_MEM_FULL_THRHD_V)<<(UART_RX_MEM_FULL_THRHD_S))
#define UART_RX_MEM_FULL_THRHD_V  0x7
#define UART_RX_MEM_FULL_THRHD_S  25
/* UART_XOFF_THRESHOLD_H2:R/W；位位置：[24:23]；默认值：2'h0；*/
/*description:请参阅uart_xoff_threshold的描述。*/
#define UART_XOFF_THRESHOLD_H2  0x00000003
#define UART_XOFF_THRESHOLD_H2_M  ((UART_XOFF_THRESHOLD_H2_V)<<(UART_XOFF_THRESHOLD_H2_S))
#define UART_XOFF_THRESHOLD_H2_V  0x3
#define UART_XOFF_THRESHOLD_H2_S  23
/* UART_XON_THRESHOLD_H2:R/W；比特位置：[22:21]；默认值：2'h0；*/
/*描述：请参阅uart_xon_threshold的描述。*/
#define UART_XON_THRESHOLD_H2  0x00000003
#define UART_XON_THRESHOLD_H2_M  ((UART_XON_THRESHOLD_H2_V)<<(UART_XON_THRESHOLD_H2_S))
#define UART_XON_THRESHOLD_H2_V  0x3
#define UART_XON_THRESHOLD_H2_S  21
/* UART_RX_TOUT_thrhdh3:R/W；比特位置：[20:18]；默认值：3'h0；*/
/*说明：请参考rxtout_thhd的说明。*/
#define UART_RX_TOUT_THRHD_H3  0x00000007
#define UART_RX_TOUT_THRHD_H3_M  ((UART_RX_TOUT_THRHD_H3_V)<<(UART_RX_TOUT_THRHD_H3_S))
#define UART_RX_TOUT_THRHD_H3_V  0x7
#define UART_RX_TOUT_THRHD_H3_S  18
/* UART_RX_FLOW_THRHD_H3:R/W；比特位置：[17:15]；默认值：3'h0；*/
/*说明：参考rx-flow_thrhd的说明。*/
#define UART_RX_FLOW_THRHD_H3  0x00000007
#define UART_RX_FLOW_THRHD_H3_M  ((UART_RX_FLOW_THRHD_H3_V)<<(UART_RX_FLOW_THRHD_H3_S))
#define UART_RX_FLOW_THRHD_H3_V  0x7
#define UART_RX_FLOW_THRHD_H3_S  15
/* UART_TX_SIZE：R/W；比特位置：[10:7]；默认值：4'h1；*/
/*description:此寄存器用于配置分配给发射机fifo的内存量。默认字节num为128。*/
#define UART_TX_SIZE  0x0000000F
#define UART_TX_SIZE_M  ((UART_TX_SIZE_V)<<(UART_TX_SIZE_S))
#define UART_TX_SIZE_V  0xF
#define UART_TX_SIZE_S  7
/* UART_RX_SIZE:R/W；比特位置：[6:3]；默认值：4'h1；*/
/*description:此寄存器用于配置分配给接收方fifo的内存量。默认字节num为128。*/
#define UART_RX_SIZE  0x0000000F
#define UART_RX_SIZE_M  ((UART_RX_SIZE_V)<<(UART_RX_SIZE_S))
#define UART_RX_SIZE_V  0xF
#define UART_RX_SIZE_S  3
/* UART_MEM_PD:R/W；位位置：[0]；默认值：1’b0；*/
/*description:设置此位以关闭内存。当3个uart中的reg_mem_pd寄存器都设置为1时，mem将进入低功率模式。*/
#define UART_MEM_PD  (BIT(0))
#define UART_MEM_PD_M  (BIT(0))
#define UART_MEM_PD_V  0x1
#define UART_MEM_PD_S  0

#define UART_MEM_TX_STATUS_REG(i)          (REG_UART_BASE(i) + 0x5c)
/* UART_MEM_TX_STATUS：RO；比特位置：[23:0]；默认值：24小时；*/
/*说明：*/
#define UART_MEM_TX_STATUS  0x00FFFFFF
#define UART_MEM_TX_STATUS_M  ((UART_MEM_TX_STATUS_V)<<(UART_MEM_TX_STATUS_S))
#define UART_MEM_TX_STATUS_V  0xFFFFFF
#define UART_MEM_TX_STATUS_S  0

#define UART_MEM_RX_STATUS_REG(i)          (REG_UART_BASE(i) + 0x60)
/* UART_MEM_RX_STATUS：RO；比特位置：[23:0]；默认值：24小时；*/
/*description:此寄存器存储当前uart rx mem读地址和rx mem写地址*/
#define UART_MEM_RX_STATUS  0x00FFFFFF
#define UART_MEM_RX_STATUS_M  ((UART_MEM_RX_STATUS_V)<<(UART_MEM_RX_STATUS_S))
#define UART_MEM_RX_STATUS_V  0xFFFFFF
#define UART_MEM_RX_STATUS_S  0
/* UART_MEM_RX_RD_ADDR:RO；比特位置：[12:2]；默认值：11'0；*/
/*description:此寄存器存储rx-mem读取地址*/
#define UART_MEM_RX_RD_ADDR  0x000007FF
#define UART_MEM_RX_RD_ADDR_M ((UART_MEM_RX_RD_ADDR_V)<<(UART_MEM_RX_RD_ADDR_S))
#define UART_MEM_RX_RD_ADDR_V (0x7FF)
#define UART_MEM_RX_RD_ADDR_S (2)
/* UART_MEM_RX_WR_ADDR:RO；比特位置：[23:13]；默认值：11'0；*/
/*description:此寄存器存储rx-mem写地址*/
#define UART_MEM_RX_WR_ADDR   0x000007FF
#define UART_MEM_RX_WR_ADDR_M ((UART_MEM_RX_WR_ADDR_V)<<(UART_MEM_RX_WR_ADDR_S))
#define UART_MEM_RX_WR_ADDR_V (0x7FF)
#define UART_MEM_RX_WR_ADDR_S (13)

#define UART_MEM_CNT_STATUS_REG(i)          (REG_UART_BASE(i) + 0x64)
/* UART_TX_MEM_CNT:RO；比特位置：[5:3]；默认值：3'b0；*/
/*说明：请参阅txfifocnt的说明。*/
#define UART_TX_MEM_CNT  0x00000007
#define UART_TX_MEM_CNT_M  ((UART_TX_MEM_CNT_V)<<(UART_TX_MEM_CNT_S))
#define UART_TX_MEM_CNT_V  0x7
#define UART_TX_MEM_CNT_S  3
/* UART_RX_MEM_CNT:RO；位位置：[2:0]；默认值：3'b0；*/
/*description:请参阅rxfifocnt的描述。*/
#define UART_RX_MEM_CNT  0x00000007
#define UART_RX_MEM_CNT_M  ((UART_RX_MEM_CNT_V)<<(UART_RX_MEM_CNT_S))
#define UART_RX_MEM_CNT_V  0x7
#define UART_RX_MEM_CNT_S  0

#define UART_POSPULSE_REG(i)          (REG_UART_BASE(i) + 0x68)
/* UART_POSEDGE_MIN_CNT:RO；比特位置：[19:0]；默认值：20'FFFFF；*/
/*description:此寄存器存储rxd-posedge边缘的计数。将其应用于boudrate检测过程。*/
#define UART_POSEDGE_MIN_CNT  0x000FFFFF
#define UART_POSEDGE_MIN_CNT_M  ((UART_POSEDGE_MIN_CNT_V)<<(UART_POSEDGE_MIN_CNT_S))
#define UART_POSEDGE_MIN_CNT_V  0xFFFFF
#define UART_POSEDGE_MIN_CNT_S  0

#define UART_NEGPULSE_REG(i)          (REG_UART_BASE(i) + 0x6c)
/* UART_NEGEDGE_MIN_CNT:RO；比特位置：[19:0]；默认值：20'FFFFF；*/
/*description:此寄存器存储rxd负边缘的计数。将其应用于boudrate检测过程。*/
#define UART_NEGEDGE_MIN_CNT  0x000FFFFF
#define UART_NEGEDGE_MIN_CNT_M  ((UART_NEGEDGE_MIN_CNT_V)<<(UART_NEGEDGE_MIN_CNT_S))
#define UART_NEGEDGE_MIN_CNT_V  0xFFFFF
#define UART_NEGEDGE_MIN_CNT_S  0

#define UART_DATE_REG(i)          (REG_UART_BASE(i) + 0x78)
/* UART_DATE:R/W；位位置：[31:0]；默认值：32'h15122500；*/
/*说明：*/
#define UART_DATE  0xFFFFFFFF
#define UART_DATE_M  ((UART_DATE_V)<<(UART_DATE_S))
#define UART_DATE_V  0xFFFFFFFF
#define UART_DATE_S  0

#define UART_ID_REG(i)          (REG_UART_BASE(i) + 0x7C)
/* UART_ID:R/W；位位置：[31:0]；默认值：32'h0500；*/
/*说明：*/
#define UART_ID  0xFFFFFFFF
#define UART_ID_M  ((UART_ID_V)<<(UART_ID_S))
#define UART_ID_V  0xFFFFFFFF
#define UART_ID_S  0




#endif /*__UART_REG_H__ */

