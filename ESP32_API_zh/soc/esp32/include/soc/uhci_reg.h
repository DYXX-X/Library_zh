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
#ifndef _SOC_UHCI_REG_H_
#define _SOC_UHCI_REG_H_


#include "soc.h"
#define REG_UHCI_BASE(i)         (DR_REG_UHCI0_BASE - (i) * 0x8000)
#define UHCI_CONF0_REG(i)          (REG_UHCI_BASE(i) + 0x0)
/* UHCI_UART_RX_BRK_of_EN:R/W；位位置：[23]；默认值：1’b0；*/
/*description:设置此位以启用brk-char作为数据帧的结尾。*/
#define UHCI_UART_RX_BRK_EOF_EN  (BIT(23))
#define UHCI_UART_RX_BRK_EOF_EN_M  (BIT(23))
#define UHCI_UART_RX_BRK_EOF_EN_V  0x1
#define UHCI_UART_RX_BRK_EOF_EN_S  23
/* UHCI_CLK_EN:R/W；位位置：[22]；默认值：1’b0；*/
/*description:设置此位以启用读或写寄存器的时钟门控。*/
#define UHCI_CLK_EN  (BIT(22))
#define UHCI_CLK_EN_M  (BIT(22))
#define UHCI_CLK_EN_V  0x1
#define UHCI_CLK_EN_S  22
/* UHCI_ENCODE_CRC_EN:R/W；位位置：[21]；默认值：1’b1；*/
/*description:当头包中的位6为1时，设置此位以启用数据帧的crc计算。*/
#define UHCI_ENCODE_CRC_EN  (BIT(21))
#define UHCI_ENCODE_CRC_EN_M  (BIT(21))
#define UHCI_ENCODE_CRC_EN_V  0x1
#define UHCI_ENCODE_CRC_EN_S  21
/* UHCI_LEN_EOF_EN:R/W；位位置：[20]；默认值：1’b1；*/
/*description:设置此位，以便在接收到的数据等于packet_len时，能够在包头中使用packet_len-这意味着数据帧的结束。*/
#define UHCI_LEN_EOF_EN  (BIT(20))
#define UHCI_LEN_EOF_EN_M  (BIT(20))
#define UHCI_LEN_EOF_EN_V  0x1
#define UHCI_LEN_EOF_EN_S  20
/* UHCI_UART_IDLE_EOF_EN:R/W；位位置：[19]；默认值：1’b0；*/
/*description:设置此位，以便在满足数据帧后的空闲时间时使用空闲时间，这意味着数据帧的结束。*/
#define UHCI_UART_IDLE_EOF_EN  (BIT(19))
#define UHCI_UART_IDLE_EOF_EN_M  (BIT(19))
#define UHCI_UART_IDLE_EOF_EN_V  0x1
#define UHCI_UART_IDLE_EOF_EN_S  19
/* UHCI_CRC_REC_EN:R/W；位位置：[18]；默认值：1’b1；*/
/*description:当头包中的crc_en位为1时，设置此位以启用接收器的crc计算能力，那么data_frame之后将有crc字节*/
#define UHCI_CRC_REC_EN  (BIT(18))
#define UHCI_CRC_REC_EN_M  (BIT(18))
#define UHCI_CRC_REC_EN_V  0x1
#define UHCI_CRC_REC_EN_S  18
/* UHCI_HEAD_EN:R/W；位位置：[17]；默认值：1’b1；*/
/*description:设置此位以启用在数据帧之前使用头数据包。*/
#define UHCI_HEAD_EN  (BIT(17))
#define UHCI_HEAD_EN_M  (BIT(17))
#define UHCI_HEAD_EN_V  0x1
#define UHCI_HEAD_EN_S  17
/* UHCI_SEPER_EN:R/W；位位置：[16]；默认值：1’b1；*/
/*description:设置此位以使用特殊字符分隔数据帧。*/
#define UHCI_SEPER_EN  (BIT(16))
#define UHCI_SEPER_EN_M  (BIT(16))
#define UHCI_SEPER_EN_V  0x1
#define UHCI_SEPER_EN_S  16
/* UHCI_MEM_TRANS_EN:R/W；位位置：[15]；默认值：1’b0；*/
/*说明：*/
#define UHCI_MEM_TRANS_EN  (BIT(15))
#define UHCI_MEM_TRANS_EN_M  (BIT(15))
#define UHCI_MEM_TRANS_EN_V  0x1
#define UHCI_MEM_TRANS_EN_S  15
/* UHCI_OUT_DATA_BURST_EN:R/W；位位置：[14]；默认值：1’b0；*/
/*description:设置此位以启用DMA突发模式*/
#define UHCI_OUT_DATA_BURST_EN  (BIT(14))
#define UHCI_OUT_DATA_BURST_EN_M  (BIT(14))
#define UHCI_OUT_DATA_BURST_EN_V  0x1
#define UHCI_OUT_DATA_BURST_EN_S  14
/* UHCI_INDSCR_BURST_EN:R/W；位位置：[13]；默认值：1’b0；*/
/*description:设置此位以启用DMA输出链接以使用突发模式。*/
#define UHCI_INDSCR_BURST_EN  (BIT(13))
#define UHCI_INDSCR_BURST_EN_M  (BIT(13))
#define UHCI_INDSCR_BURST_EN_V  0x1
#define UHCI_INDSCR_BURST_EN_S  13
/* UHCI_OUTDSCR_BURST_EN:R/W；位位置：[12]；默认值：1’b0；*/
/*description:设置此位以启用链接中的DMA以使用突发模式。*/
#define UHCI_OUTDSCR_BURST_EN  (BIT(12))
#define UHCI_OUTDSCR_BURST_EN_M  (BIT(12))
#define UHCI_OUTDSCR_BURST_EN_V  0x1
#define UHCI_OUTDSCR_BURST_EN_S  12
/* UHCI_UART2_CE:R/W；位位置：[11]；默认值：1’b0；*/
/*description:设置此位以使用UART2发送或接收数据。*/
#define UHCI_UART2_CE  (BIT(11))
#define UHCI_UART2_CE_M  (BIT(11))
#define UHCI_UART2_CE_V  0x1
#define UHCI_UART2_CE_S  11
/* UHCI_UART1_CE:R/W；位位置：[10]；默认值：1’b0；*/
/*description:设置此位以使用UART1发送或接收数据。*/
#define UHCI_UART1_CE  (BIT(10))
#define UHCI_UART1_CE_M  (BIT(10))
#define UHCI_UART1_CE_V  0x1
#define UHCI_UART1_CE_S  10
/* UHCI_UART0_CE:R/W；位位置：[9]；默认值：1’b0；*/
/*description:设置此位以使用UART发送或接收数据。*/
#define UHCI_UART0_CE  (BIT(9))
#define UHCI_UART0_CE_M  (BIT(9))
#define UHCI_UART0_CE_V  0x1
#define UHCI_UART0_CE_S  9
/* UHCI_OUT_EOF_MODE模式：R/W；位位置：[8]；默认值：1’b1；*/
/*description:设置此位以在DMA弹出所有数据后生成eof，清除此位以使DMA推送所有数据后产生eof*/
#define UHCI_OUT_EOF_MODE  (BIT(8))
#define UHCI_OUT_EOF_MODE_M  (BIT(8))
#define UHCI_OUT_EOF_MODE_V  0x1
#define UHCI_OUT_EOF_MODE_S  8
/* UHCI_OUT_NO_RESTART_CLR:R/W；位位置：[7]；默认值：1’b0；*/
/*description:不使用*/
#define UHCI_OUT_NO_RESTART_CLR  (BIT(7))
#define UHCI_OUT_NO_RESTART_CLR_M  (BIT(7))
#define UHCI_OUT_NO_RESTART_CLR_V  0x1
#define UHCI_OUT_NO_RESTART_CLR_S  7
/* UHCI_OUT_AUTO_werback:R/W；位位置：[6]；默认值：1’b0；*/
/*描述：当in链接的长度为0时，继续自动使用下一个in链接。*/
#define UHCI_OUT_AUTO_WRBACK  (BIT(6))
#define UHCI_OUT_AUTO_WRBACK_M  (BIT(6))
#define UHCI_OUT_AUTO_WRBACK_V  0x1
#define UHCI_OUT_AUTO_WRBACK_S  6
/* UHCI_OUT_LOOP_TEST:R/W；位位置：[5]；默认值：1’b0；*/
/*description:设置此位以启用输出链接的循环测试。*/
#define UHCI_OUT_LOOP_TEST  (BIT(5))
#define UHCI_OUT_LOOP_TEST_M  (BIT(5))
#define UHCI_OUT_LOOP_TEST_V  0x1
#define UHCI_OUT_LOOP_TEST_S  5
/* UHCI_IN_LOOP_TEST:R/W；位位置：[4]；默认值：1’b0；*/
/*description:设置此位以启用in链接的循环测试。*/
#define UHCI_IN_LOOP_TEST  (BIT(4))
#define UHCI_IN_LOOP_TEST_M  (BIT(4))
#define UHCI_IN_LOOP_TEST_V  0x1
#define UHCI_IN_LOOP_TEST_S  4
/* UHCI_AHBM_RST:R/W；位位置：[3]；默认值：1’b0；*/
/*description:设置此位以重置dma ahb接口。*/
#define UHCI_AHBM_RST  (BIT(3))
#define UHCI_AHBM_RST_M  (BIT(3))
#define UHCI_AHBM_RST_V  0x1
#define UHCI_AHBM_RST_S  3
/* UHCI_AHBM_FIFO_RST:R/W；位位置：[2]；默认值：1’b0；*/
/*description:设置此位以重置dma ahb fifo。*/
#define UHCI_AHBM_FIFO_RST  (BIT(2))
#define UHCI_AHBM_FIFO_RST_M  (BIT(2))
#define UHCI_AHBM_FIFO_RST_V  0x1
#define UHCI_AHBM_FIFO_RST_S  2
/* UHCI_OUT_RST:R/W；位位置：[1]；默认值：1’b0；*/
/*description:设置此位以重置链接操作。*/
#define UHCI_OUT_RST  (BIT(1))
#define UHCI_OUT_RST_M  (BIT(1))
#define UHCI_OUT_RST_V  0x1
#define UHCI_OUT_RST_S  1
/* UHCI_IN_RST:R/W；位位置：[0]；默认值：1'0；*/
/*description:设置此位以在链接操作中重置。*/
#define UHCI_IN_RST  (BIT(0))
#define UHCI_IN_RST_M  (BIT(0))
#define UHCI_IN_RST_V  0x1
#define UHCI_IN_RST_S  0

#define UHCI_INT_RAW_REG(i)          (REG_UHCI_BASE(i) + 0x4)
/* UHCI_DMA_INFIFO_FULL_WM_INT_RAW:RO；位位置：[16]；默认值：1’b0；*/
/*说明：*/
#define UHCI_DMA_INFIFO_FULL_WM_INT_RAW  (BIT(16))
#define UHCI_DMA_INFIFO_FULL_WM_INT_RAW_M  (BIT(16))
#define UHCI_DMA_INFIFO_FULL_WM_INT_RAW_V  0x1
#define UHCI_DMA_INFIFO_FULL_WM_INT_RAW_S  16
/* UHCI_SEND_A_Q_INT_RAW:RO；位位置：[15]；默认值：1’b0；*/
/*描述：当使用alwayssend寄存器发送一系列短数据包时，当dma发送了短数据包后，将产生此中断。*/
#define UHCI_SEND_A_Q_INT_RAW  (BIT(15))
#define UHCI_SEND_A_Q_INT_RAW_M  (BIT(15))
#define UHCI_SEND_A_Q_INT_RAW_V  0x1
#define UHCI_SEND_A_Q_INT_RAW_S  15
/* UHCI_SEND_S_Q_INT_RAW:RO；位位置：[14]；默认值：1’b0；*/
/*描述：当使用单个发送寄存器发送短数据包时，当dma发送了短数据包后，将产生此中断。*/
#define UHCI_SEND_S_Q_INT_RAW  (BIT(14))
#define UHCI_SEND_S_Q_INT_RAW_M  (BIT(14))
#define UHCI_SEND_S_Q_INT_RAW_V  0x1
#define UHCI_SEND_S_Q_INT_RAW_S  14
/* UHCI_OUT_TOTAL_EOF_INT_RAW:RO；位位置：[13]；默认值：1’b0；*/
/*description:当所有数据都已发送时，将产生uhci_out_total_eof_int中断。*/
#define UHCI_OUT_TOTAL_EOF_INT_RAW  (BIT(13))
#define UHCI_OUT_TOTAL_EOF_INT_RAW_M  (BIT(13))
#define UHCI_OUT_TOTAL_EOF_INT_RAW_V  0x1
#define UHCI_OUT_TOTAL_EOF_INT_RAW_S  13
/* UHCI_OUTLINK_EOF_ERR_INT_RAW:RO；位位置：[12]；默认值：1’b0；*/
/*描述：当outlink描述符中有一些关于eof的错误时，它将产生uhci_outlink_eof_err_int中断。*/
#define UHCI_OUTLINK_EOF_ERR_INT_RAW  (BIT(12))
#define UHCI_OUTLINK_EOF_ERR_INT_RAW_M  (BIT(12))
#define UHCI_OUTLINK_EOF_ERR_INT_RAW_V  0x1
#define UHCI_OUTLINK_EOF_ERR_INT_RAW_S  12
/* UHCI_IN_DSCR_EMPTY_INT_RAW:RO；位位置：[11]；默认值：1’b0；*/
/*描述：当DMA没有足够的内部链路时，它将产生uhci_in_dscr_err_int中断。*/
#define UHCI_IN_DSCR_EMPTY_INT_RAW  (BIT(11))
#define UHCI_IN_DSCR_EMPTY_INT_RAW_M  (BIT(11))
#define UHCI_IN_DSCR_EMPTY_INT_RAW_V  0x1
#define UHCI_IN_DSCR_EMPTY_INT_RAW_S  11
/* UHCI_OUT_DSCR_ERR_INT_RAW:RO；位位置：[10]；默认值：1’b0；*/
/*描述：当链接内描述符出现一些错误时，它将产生uhci_outdscr_err_int中断。*/
#define UHCI_OUT_DSCR_ERR_INT_RAW  (BIT(10))
#define UHCI_OUT_DSCR_ERR_INT_RAW_M  (BIT(10))
#define UHCI_OUT_DSCR_ERR_INT_RAW_V  0x1
#define UHCI_OUT_DSCR_ERR_INT_RAW_S  10
/* UHCI_IN_DSCR_ERR_INT_RAW:RO；位位置：[9]；默认值：1’b0；*/
/*描述：当输出链接描述符出现一些错误时，它将产生uhci_indscr_errint中断。*/
#define UHCI_IN_DSCR_ERR_INT_RAW  (BIT(9))
#define UHCI_IN_DSCR_ERR_INT_RAW_M  (BIT(9))
#define UHCI_IN_DSCR_ERR_INT_RAW_V  0x1
#define UHCI_IN_DSCR_ERR_INT_RAW_S  9
/* UHCI_OUT_EOF_INT_RAW:RO；位位置：[8]；默认值：1’b0；*/
/*描述：当当前描述符的eof位为1时，将产生uhci_out_eof_int中断。*/
#define UHCI_OUT_EOF_INT_RAW  (BIT(8))
#define UHCI_OUT_EOF_INT_RAW_M  (BIT(8))
#define UHCI_OUT_EOF_INT_RAW_V  0x1
#define UHCI_OUT_EOF_INT_RAW_S  8
/* UHCI_OUT_DONE_INT_RAW:RO；位位置：[7]；默认值：1’b0；*/
/*描述：当一个输出链接描述符完成时，它将产生uhci_out_done_int中断。*/
#define UHCI_OUT_DONE_INT_RAW  (BIT(7))
#define UHCI_OUT_DONE_INT_RAW_M  (BIT(7))
#define UHCI_OUT_DONE_INT_RAW_V  0x1
#define UHCI_OUT_DONE_INT_RAW_S  7
/* UHCI_IN_ERR_EOF_INT_RAW:RO；位位置：[6]；默认值：1’b0；*/
/*描述：当链接描述符中的eof出现一些错误时，它将产生uhci_in_err_eof_int中断。*/
#define UHCI_IN_ERR_EOF_INT_RAW  (BIT(6))
#define UHCI_IN_ERR_EOF_INT_RAW_M  (BIT(6))
#define UHCI_IN_ERR_EOF_INT_RAW_V  0x1
#define UHCI_IN_ERR_EOF_INT_RAW_S  6
/* UHCI_IN_SUC_EOF_INT_RAW:RO；位位置：[5]；默认值：1’b0；*/
/*描述：当接收到数据包时，它将产生uhci_in_suc_eof_int中断。*/
#define UHCI_IN_SUC_EOF_INT_RAW  (BIT(5))
#define UHCI_IN_SUC_EOF_INT_RAW_M  (BIT(5))
#define UHCI_IN_SUC_EOF_INT_RAW_V  0x1
#define UHCI_IN_SUC_EOF_INT_RAW_S  5
/* UHCI_IN_DONE_INT_RAW:RO；位位置：[4]；默认值：1’b0；*/
/*描述：当一个链接内描述符完成后，它将产生uhci_indone_int中断。*/
#define UHCI_IN_DONE_INT_RAW  (BIT(4))
#define UHCI_IN_DONE_INT_RAW_M  (BIT(4))
#define UHCI_IN_DONE_INT_RAW_V  0x1
#define UHCI_IN_DONE_INT_RAW_S  4
/* UHCI_TX_HUNG_INT_RAW:RO；位位置：[3]；默认值：1’b0；*/
/*描述：当DMA花费大量时间从RAM读取数据时，将产生uhci_tx_hung_int中断。*/
#define UHCI_TX_HUNG_INT_RAW  (BIT(3))
#define UHCI_TX_HUNG_INT_RAW_M  (BIT(3))
#define UHCI_TX_HUNG_INT_RAW_V  0x1
#define UHCI_TX_HUNG_INT_RAW_S  3
/* UHCI_RX_HUNG_INT_RAW:RO；位位置：[2]；默认值：1’b0；*/
/*描述：当DMA花费大量时间接收数据时，它将产生uhci_rx_hung_int中断。*/
#define UHCI_RX_HUNG_INT_RAW  (BIT(2))
#define UHCI_RX_HUNG_INT_RAW_M  (BIT(2))
#define UHCI_RX_HUNG_INT_RAW_V  0x1
#define UHCI_RX_HUNG_INT_RAW_S  2
/* UHCI_TX_START_INT_RAW:RO；位位置：[1]；默认值：1’b0；*/
/*描述：当DMA检测到分隔符字符时，它将产生uhci_tx_start_int中断。*/
#define UHCI_TX_START_INT_RAW  (BIT(1))
#define UHCI_TX_START_INT_RAW_M  (BIT(1))
#define UHCI_TX_START_INT_RAW_V  0x1
#define UHCI_TX_START_INT_RAW_S  1
/* UHCI_RX_START_INT_RAW:RO；位位置：[0]；默认值：1’b0；*/
/*描述：发送分隔符字符后，将产生uhcirxstartint中断。*/
#define UHCI_RX_START_INT_RAW  (BIT(0))
#define UHCI_RX_START_INT_RAW_M  (BIT(0))
#define UHCI_RX_START_INT_RAW_V  0x1
#define UHCI_RX_START_INT_RAW_S  0

#define UHCI_INT_ST_REG(i)          (REG_UHCI_BASE(i) + 0x8)
/* UHCI_DMA_INFIFO_FULL_WM_INT_ST:RO；位位置：[16]；默认值：1’b0；*/
/*说明：*/
#define UHCI_DMA_INFIFO_FULL_WM_INT_ST  (BIT(16))
#define UHCI_DMA_INFIFO_FULL_WM_INT_ST_M  (BIT(16))
#define UHCI_DMA_INFIFO_FULL_WM_INT_ST_V  0x1
#define UHCI_DMA_INFIFO_FULL_WM_INT_ST_S  16
/* UHCI_SEND_A_Q_INT_ST:RO；位位置：[15]；默认值：1’b0；*/
/*说明：*/
#define UHCI_SEND_A_Q_INT_ST  (BIT(15))
#define UHCI_SEND_A_Q_INT_ST_M  (BIT(15))
#define UHCI_SEND_A_Q_INT_ST_V  0x1
#define UHCI_SEND_A_Q_INT_ST_S  15
/* UHCI_SEND_S_Q_INT_ST:RO；位位置：[14]；默认值：1’b0；*/
/*说明：*/
#define UHCI_SEND_S_Q_INT_ST  (BIT(14))
#define UHCI_SEND_S_Q_INT_ST_M  (BIT(14))
#define UHCI_SEND_S_Q_INT_ST_V  0x1
#define UHCI_SEND_S_Q_INT_ST_S  14
/* 时间：RO；位位置：[13]；默认值：1’b0；*/
/*说明：*/
#define UHCI_OUT_TOTAL_EOF_INT_ST  (BIT(13))
#define UHCI_OUT_TOTAL_EOF_INT_ST_M  (BIT(13))
#define UHCI_OUT_TOTAL_EOF_INT_ST_V  0x1
#define UHCI_OUT_TOTAL_EOF_INT_ST_S  13
/* UHCI_OUTLINK_EOF_ERR_INT_ST:RO；位位置：[12]；默认值：1’b0；*/
/*说明：*/
#define UHCI_OUTLINK_EOF_ERR_INT_ST  (BIT(12))
#define UHCI_OUTLINK_EOF_ERR_INT_ST_M  (BIT(12))
#define UHCI_OUTLINK_EOF_ERR_INT_ST_V  0x1
#define UHCI_OUTLINK_EOF_ERR_INT_ST_S  12
/* UHCI_IN_DSCR_EMPTY_INT_ST:RO；位位置：[11]；默认值：1’b0；*/
/*说明：*/
#define UHCI_IN_DSCR_EMPTY_INT_ST  (BIT(11))
#define UHCI_IN_DSCR_EMPTY_INT_ST_M  (BIT(11))
#define UHCI_IN_DSCR_EMPTY_INT_ST_V  0x1
#define UHCI_IN_DSCR_EMPTY_INT_ST_S  11
/* UHCI_OUT_DSCR_ERR_INT_ST:RO；位位置：[10]；默认值：1’b0；*/
/*说明：*/
#define UHCI_OUT_DSCR_ERR_INT_ST  (BIT(10))
#define UHCI_OUT_DSCR_ERR_INT_ST_M  (BIT(10))
#define UHCI_OUT_DSCR_ERR_INT_ST_V  0x1
#define UHCI_OUT_DSCR_ERR_INT_ST_S  10
/* UHCI_IN_DSCR_ERR_INT_ST:RO；位位置：[9]；默认值：1’b0；*/
/*说明：*/
#define UHCI_IN_DSCR_ERR_INT_ST  (BIT(9))
#define UHCI_IN_DSCR_ERR_INT_ST_M  (BIT(9))
#define UHCI_IN_DSCR_ERR_INT_ST_V  0x1
#define UHCI_IN_DSCR_ERR_INT_ST_S  9
/* UHCI_OUT_EOF_INT_ST:RO；位位置：[8]；默认值：1’b0；*/
/*说明：*/
#define UHCI_OUT_EOF_INT_ST  (BIT(8))
#define UHCI_OUT_EOF_INT_ST_M  (BIT(8))
#define UHCI_OUT_EOF_INT_ST_V  0x1
#define UHCI_OUT_EOF_INT_ST_S  8
/* UHCI_OUT_DONE_INT_ST:RO；位位置：[7]；默认值：1’b0；*/
/*说明：*/
#define UHCI_OUT_DONE_INT_ST  (BIT(7))
#define UHCI_OUT_DONE_INT_ST_M  (BIT(7))
#define UHCI_OUT_DONE_INT_ST_V  0x1
#define UHCI_OUT_DONE_INT_ST_S  7
/* UHCI_IN_ERR_EOF_INT_ST:RO；位位置：[6]；默认值：1’b0；*/
/*说明：*/
#define UHCI_IN_ERR_EOF_INT_ST  (BIT(6))
#define UHCI_IN_ERR_EOF_INT_ST_M  (BIT(6))
#define UHCI_IN_ERR_EOF_INT_ST_V  0x1
#define UHCI_IN_ERR_EOF_INT_ST_S  6
/* UHCI_IN_SUC_EOF_INT_ST:RO；位位置：[5]；默认值：1’b0；*/
/*说明：*/
#define UHCI_IN_SUC_EOF_INT_ST  (BIT(5))
#define UHCI_IN_SUC_EOF_INT_ST_M  (BIT(5))
#define UHCI_IN_SUC_EOF_INT_ST_V  0x1
#define UHCI_IN_SUC_EOF_INT_ST_S  5
/* UHCI_IN_DONE_INT_ST:RO；位位置：[4]；默认值：1’b0；*/
/*说明：*/
#define UHCI_IN_DONE_INT_ST  (BIT(4))
#define UHCI_IN_DONE_INT_ST_M  (BIT(4))
#define UHCI_IN_DONE_INT_ST_V  0x1
#define UHCI_IN_DONE_INT_ST_S  4
/* UHCI_TX_HUNG_INT_ST:RO；位位置：[3]；默认值：1’b0；*/
/*说明：*/
#define UHCI_TX_HUNG_INT_ST  (BIT(3))
#define UHCI_TX_HUNG_INT_ST_M  (BIT(3))
#define UHCI_TX_HUNG_INT_ST_V  0x1
#define UHCI_TX_HUNG_INT_ST_S  3
/* UHCI_RX_HUNG_INT_ST:RO；位位置：[2]；默认值：1’b0；*/
/*说明：*/
#define UHCI_RX_HUNG_INT_ST  (BIT(2))
#define UHCI_RX_HUNG_INT_ST_M  (BIT(2))
#define UHCI_RX_HUNG_INT_ST_V  0x1
#define UHCI_RX_HUNG_INT_ST_S  2
/* UHCI_TX_START_INT_ST:RO；位位置：[1]；默认值：1’b0；*/
/*说明：*/
#define UHCI_TX_START_INT_ST  (BIT(1))
#define UHCI_TX_START_INT_ST_M  (BIT(1))
#define UHCI_TX_START_INT_ST_V  0x1
#define UHCI_TX_START_INT_ST_S  1
/* UHCI_RX_START_INT_ST:RO；位位置：[0]；默认值：1’b0；*/
/*说明：*/
#define UHCI_RX_START_INT_ST  (BIT(0))
#define UHCI_RX_START_INT_ST_M  (BIT(0))
#define UHCI_RX_START_INT_ST_V  0x1
#define UHCI_RX_START_INT_ST_S  0

#define UHCI_INT_ENA_REG(i)          (REG_UHCI_BASE(i) + 0xC)
/* UHCI_DMA_INFIFO_FULL_WM_INT_ENA:R/W；位位置：[16]；默认值：1’b0；*/
/*说明：*/
#define UHCI_DMA_INFIFO_FULL_WM_INT_ENA  (BIT(16))
#define UHCI_DMA_INFIFO_FULL_WM_INT_ENA_M  (BIT(16))
#define UHCI_DMA_INFIFO_FULL_WM_INT_ENA_V  0x1
#define UHCI_DMA_INFIFO_FULL_WM_INT_ENA_S  16
/* UHCI_SEND_A_Q_INT_ENA:R/W；位位置：[15]；默认值：1’b0；*/
/*说明：*/
#define UHCI_SEND_A_Q_INT_ENA  (BIT(15))
#define UHCI_SEND_A_Q_INT_ENA_M  (BIT(15))
#define UHCI_SEND_A_Q_INT_ENA_V  0x1
#define UHCI_SEND_A_Q_INT_ENA_S  15
/* UHCI_SEND_S_Q_INT_ENA:R/W；位位置：[14]；默认值：1’b0；*/
/*说明：*/
#define UHCI_SEND_S_Q_INT_ENA  (BIT(14))
#define UHCI_SEND_S_Q_INT_ENA_M  (BIT(14))
#define UHCI_SEND_S_Q_INT_ENA_V  0x1
#define UHCI_SEND_S_Q_INT_ENA_S  14
/* UHCI_OUT_TOTAL_EOF_INT_ENA:R/W；位位置：[13]；默认值：1’b0；*/
/*说明：*/
#define UHCI_OUT_TOTAL_EOF_INT_ENA  (BIT(13))
#define UHCI_OUT_TOTAL_EOF_INT_ENA_M  (BIT(13))
#define UHCI_OUT_TOTAL_EOF_INT_ENA_V  0x1
#define UHCI_OUT_TOTAL_EOF_INT_ENA_S  13
/* UHCI_OUTLINK_EOF_ERR_INT_ENA:R/W；位位置：[12]；默认值：1’b0；*/
/*说明：*/
#define UHCI_OUTLINK_EOF_ERR_INT_ENA  (BIT(12))
#define UHCI_OUTLINK_EOF_ERR_INT_ENA_M  (BIT(12))
#define UHCI_OUTLINK_EOF_ERR_INT_ENA_V  0x1
#define UHCI_OUTLINK_EOF_ERR_INT_ENA_S  12
/* UHCI_IN_DSCR_EMPTY_INT_ENA:R/W；位位置：[11]；默认值：1’b0；*/
/*说明：*/
#define UHCI_IN_DSCR_EMPTY_INT_ENA  (BIT(11))
#define UHCI_IN_DSCR_EMPTY_INT_ENA_M  (BIT(11))
#define UHCI_IN_DSCR_EMPTY_INT_ENA_V  0x1
#define UHCI_IN_DSCR_EMPTY_INT_ENA_S  11
/* UHCI_OUT_DSCR_ERR_INT_ENA:R/W；位位置：[10]；默认值：1’b0；*/
/*说明：*/
#define UHCI_OUT_DSCR_ERR_INT_ENA  (BIT(10))
#define UHCI_OUT_DSCR_ERR_INT_ENA_M  (BIT(10))
#define UHCI_OUT_DSCR_ERR_INT_ENA_V  0x1
#define UHCI_OUT_DSCR_ERR_INT_ENA_S  10
/* UHCI_IN_DSCR_ERR_INT_ENA:R/W；位位置：[9]；默认值：1’b0；*/
/*说明：*/
#define UHCI_IN_DSCR_ERR_INT_ENA  (BIT(9))
#define UHCI_IN_DSCR_ERR_INT_ENA_M  (BIT(9))
#define UHCI_IN_DSCR_ERR_INT_ENA_V  0x1
#define UHCI_IN_DSCR_ERR_INT_ENA_S  9
/* UHCI_OUT_EOF_INT_ENA:R/W；位位置：[8]；默认值：1’b0；*/
/*说明：*/
#define UHCI_OUT_EOF_INT_ENA  (BIT(8))
#define UHCI_OUT_EOF_INT_ENA_M  (BIT(8))
#define UHCI_OUT_EOF_INT_ENA_V  0x1
#define UHCI_OUT_EOF_INT_ENA_S  8
/* UHCI_OUT_DONE_INT_ENA:R/W；位位置：[7]；默认值：1’b0；*/
/*说明：*/
#define UHCI_OUT_DONE_INT_ENA  (BIT(7))
#define UHCI_OUT_DONE_INT_ENA_M  (BIT(7))
#define UHCI_OUT_DONE_INT_ENA_V  0x1
#define UHCI_OUT_DONE_INT_ENA_S  7
/* UHCI_IN_ERR_EOF_INT_ENA:R/W；位位置：[6]；默认值：1’b0；*/
/*说明：*/
#define UHCI_IN_ERR_EOF_INT_ENA  (BIT(6))
#define UHCI_IN_ERR_EOF_INT_ENA_M  (BIT(6))
#define UHCI_IN_ERR_EOF_INT_ENA_V  0x1
#define UHCI_IN_ERR_EOF_INT_ENA_S  6
/* UHCI_IN_SUC_EOF_INT_ENA:R/W；位位置：[5]；默认值：1’b0；*/
/*说明：*/
#define UHCI_IN_SUC_EOF_INT_ENA  (BIT(5))
#define UHCI_IN_SUC_EOF_INT_ENA_M  (BIT(5))
#define UHCI_IN_SUC_EOF_INT_ENA_V  0x1
#define UHCI_IN_SUC_EOF_INT_ENA_S  5
/* UHCI_IN_DONE_INT_ENA:R/W；位位置：[4]；默认值：1’b0；*/
/*说明：*/
#define UHCI_IN_DONE_INT_ENA  (BIT(4))
#define UHCI_IN_DONE_INT_ENA_M  (BIT(4))
#define UHCI_IN_DONE_INT_ENA_V  0x1
#define UHCI_IN_DONE_INT_ENA_S  4
/* UHCI_TX_HUNG_INT_ENA:R/W；位位置：[3]；默认值：1’b0；*/
/*说明：*/
#define UHCI_TX_HUNG_INT_ENA  (BIT(3))
#define UHCI_TX_HUNG_INT_ENA_M  (BIT(3))
#define UHCI_TX_HUNG_INT_ENA_V  0x1
#define UHCI_TX_HUNG_INT_ENA_S  3
/* UHCI_RX_HUNG_INT_ENA:R/W；位位置：[2]；默认值：1’b0；*/
/*说明：*/
#define UHCI_RX_HUNG_INT_ENA  (BIT(2))
#define UHCI_RX_HUNG_INT_ENA_M  (BIT(2))
#define UHCI_RX_HUNG_INT_ENA_V  0x1
#define UHCI_RX_HUNG_INT_ENA_S  2
/* UHCI_TX_START_INT_ENA:R/W；位位置：[1]；默认值：1’b0；*/
/*说明：*/
#define UHCI_TX_START_INT_ENA  (BIT(1))
#define UHCI_TX_START_INT_ENA_M  (BIT(1))
#define UHCI_TX_START_INT_ENA_V  0x1
#define UHCI_TX_START_INT_ENA_S  1
/* UHCI_RX_START_INT_ENA:R/W；位位置：[0]；默认值：1’b0；*/
/*说明：*/
#define UHCI_RX_START_INT_ENA  (BIT(0))
#define UHCI_RX_START_INT_ENA_M  (BIT(0))
#define UHCI_RX_START_INT_ENA_V  0x1
#define UHCI_RX_START_INT_ENA_S  0

#define UHCI_INT_CLR_REG(i)          (REG_UHCI_BASE(i) + 0x10)
/* UHCI_DMA_INFIFO_FULL_WM_INT_CLR:WO；位位置：[16]；默认值：1’b0；*/
/*说明：*/
#define UHCI_DMA_INFIFO_FULL_WM_INT_CLR  (BIT(16))
#define UHCI_DMA_INFIFO_FULL_WM_INT_CLR_M  (BIT(16))
#define UHCI_DMA_INFIFO_FULL_WM_INT_CLR_V  0x1
#define UHCI_DMA_INFIFO_FULL_WM_INT_CLR_S  16
/* UHCI_SEND_A_Q_INT_CLR:WO；位位置：[15]；默认值：1’b0；*/
/*说明：*/
#define UHCI_SEND_A_Q_INT_CLR  (BIT(15))
#define UHCI_SEND_A_Q_INT_CLR_M  (BIT(15))
#define UHCI_SEND_A_Q_INT_CLR_V  0x1
#define UHCI_SEND_A_Q_INT_CLR_S  15
/* UHCI_SEND_S_Q_INT_CLR:WO；位位置：[14]；默认值：1’b0；*/
/*说明：*/
#define UHCI_SEND_S_Q_INT_CLR  (BIT(14))
#define UHCI_SEND_S_Q_INT_CLR_M  (BIT(14))
#define UHCI_SEND_S_Q_INT_CLR_V  0x1
#define UHCI_SEND_S_Q_INT_CLR_S  14
/* UHCI_OUT_TOTAL_EOF_INT_CLR:WO；位位置：[13]；默认值：1’b0；*/
/*说明：*/
#define UHCI_OUT_TOTAL_EOF_INT_CLR  (BIT(13))
#define UHCI_OUT_TOTAL_EOF_INT_CLR_M  (BIT(13))
#define UHCI_OUT_TOTAL_EOF_INT_CLR_V  0x1
#define UHCI_OUT_TOTAL_EOF_INT_CLR_S  13
/* UHCI_OUTLINK_EOF_ERR_INT_CLR:WO；位位置：[12]；默认值：1’b0；*/
/*说明：*/
#define UHCI_OUTLINK_EOF_ERR_INT_CLR  (BIT(12))
#define UHCI_OUTLINK_EOF_ERR_INT_CLR_M  (BIT(12))
#define UHCI_OUTLINK_EOF_ERR_INT_CLR_V  0x1
#define UHCI_OUTLINK_EOF_ERR_INT_CLR_S  12
/* UHCI_IN_DSCR_EMPTY_INT_CLR:WO；位位置：[11]；默认值：1’b0；*/
/*说明：*/
#define UHCI_IN_DSCR_EMPTY_INT_CLR  (BIT(11))
#define UHCI_IN_DSCR_EMPTY_INT_CLR_M  (BIT(11))
#define UHCI_IN_DSCR_EMPTY_INT_CLR_V  0x1
#define UHCI_IN_DSCR_EMPTY_INT_CLR_S  11
/* UHCI_OUT_DSCR_ERR_INT_CLR:WO；位位置：[10]；默认值：1’b0；*/
/*说明：*/
#define UHCI_OUT_DSCR_ERR_INT_CLR  (BIT(10))
#define UHCI_OUT_DSCR_ERR_INT_CLR_M  (BIT(10))
#define UHCI_OUT_DSCR_ERR_INT_CLR_V  0x1
#define UHCI_OUT_DSCR_ERR_INT_CLR_S  10
/* UHCI_IN_DSCR_ERR_INT_CLR:WO；位位置：[9]；默认值：1’b0；*/
/*说明：*/
#define UHCI_IN_DSCR_ERR_INT_CLR  (BIT(9))
#define UHCI_IN_DSCR_ERR_INT_CLR_M  (BIT(9))
#define UHCI_IN_DSCR_ERR_INT_CLR_V  0x1
#define UHCI_IN_DSCR_ERR_INT_CLR_S  9
/* UHCI_OUT_EOF_INT_CLR:WO；位位置：[8]；默认值：1’b0；*/
/*说明：*/
#define UHCI_OUT_EOF_INT_CLR  (BIT(8))
#define UHCI_OUT_EOF_INT_CLR_M  (BIT(8))
#define UHCI_OUT_EOF_INT_CLR_V  0x1
#define UHCI_OUT_EOF_INT_CLR_S  8
/* UHCI_OUT_DONE_INT_CLR:WO；位位置：[7]；默认值：1’b0；*/
/*说明：*/
#define UHCI_OUT_DONE_INT_CLR  (BIT(7))
#define UHCI_OUT_DONE_INT_CLR_M  (BIT(7))
#define UHCI_OUT_DONE_INT_CLR_V  0x1
#define UHCI_OUT_DONE_INT_CLR_S  7
/* UHCI_IN_ERR_EOF_INT_CLR:WO；位位置：[6]；默认值：1’b0；*/
/*说明：*/
#define UHCI_IN_ERR_EOF_INT_CLR  (BIT(6))
#define UHCI_IN_ERR_EOF_INT_CLR_M  (BIT(6))
#define UHCI_IN_ERR_EOF_INT_CLR_V  0x1
#define UHCI_IN_ERR_EOF_INT_CLR_S  6
/* UHCI_IN_SUC_EOF_INT_CLR:WO；位位置：[5]；默认值：1’b0；*/
/*说明：*/
#define UHCI_IN_SUC_EOF_INT_CLR  (BIT(5))
#define UHCI_IN_SUC_EOF_INT_CLR_M  (BIT(5))
#define UHCI_IN_SUC_EOF_INT_CLR_V  0x1
#define UHCI_IN_SUC_EOF_INT_CLR_S  5
/* UHCI_IN_DONE_INT_CLR:WO；位位置：[4]；默认值：1’b0；*/
/*说明：*/
#define UHCI_IN_DONE_INT_CLR  (BIT(4))
#define UHCI_IN_DONE_INT_CLR_M  (BIT(4))
#define UHCI_IN_DONE_INT_CLR_V  0x1
#define UHCI_IN_DONE_INT_CLR_S  4
/* UHCI_TX_HUNG_INT_CLR:WO；位位置：[3]；默认值：1’b0；*/
/*说明：*/
#define UHCI_TX_HUNG_INT_CLR  (BIT(3))
#define UHCI_TX_HUNG_INT_CLR_M  (BIT(3))
#define UHCI_TX_HUNG_INT_CLR_V  0x1
#define UHCI_TX_HUNG_INT_CLR_S  3
/* UHCI_RX_HUNG_INT_CLR:WO；位位置：[2]；默认值：1’b0；*/
/*说明：*/
#define UHCI_RX_HUNG_INT_CLR  (BIT(2))
#define UHCI_RX_HUNG_INT_CLR_M  (BIT(2))
#define UHCI_RX_HUNG_INT_CLR_V  0x1
#define UHCI_RX_HUNG_INT_CLR_S  2
/* UHCI_TX_START_INT_CLR:WO；位位置：[1]；默认值：1’b0；*/
/*说明：*/
#define UHCI_TX_START_INT_CLR  (BIT(1))
#define UHCI_TX_START_INT_CLR_M  (BIT(1))
#define UHCI_TX_START_INT_CLR_V  0x1
#define UHCI_TX_START_INT_CLR_S  1
/* UHCI_RX_START_INT_CLR:WO；位位置：[0]；默认值：1’b0；*/
/*说明：*/
#define UHCI_RX_START_INT_CLR  (BIT(0))
#define UHCI_RX_START_INT_CLR_M  (BIT(0))
#define UHCI_RX_START_INT_CLR_V  0x1
#define UHCI_RX_START_INT_CLR_S  0

#define UHCI_DMA_OUT_STATUS_REG(i)          (REG_UHCI_BASE(i) + 0x14)
/* UHCI_OUT_EMPTY:RO；位位置：[1]；默认值：1’b1；*/
/*描述：1:DMA在链接描述符的fifo中为空。*/
#define UHCI_OUT_EMPTY  (BIT(1))
#define UHCI_OUT_EMPTY_M  (BIT(1))
#define UHCI_OUT_EMPTY_V  0x1
#define UHCI_OUT_EMPTY_S  1
/* UHCI_OUT_FULL:RO；位位置：[0]；默认值：1’b0；*/
/*描述：1:DMA输出链接描述符的fifo已满。*/
#define UHCI_OUT_FULL  (BIT(0))
#define UHCI_OUT_FULL_M  (BIT(0))
#define UHCI_OUT_FULL_V  0x1
#define UHCI_OUT_FULL_S  0

#define UHCI_DMA_OUT_PUSH_REG(i)          (REG_UHCI_BASE(i) + 0x18)
/* UHCI_OUTFIFO推送：R/W；位位置：[16]；默认值：1'0；*/
/*description:设置此位以将数据推送到链接描述符的fifo中。*/
#define UHCI_OUTFIFO_PUSH  (BIT(16))
#define UHCI_OUTFIFO_PUSH_M  (BIT(16))
#define UHCI_OUTFIFO_PUSH_V  0x1
#define UHCI_OUTFIFO_PUSH_S  16
/* UHCI_OUTFIFO_WDATA：R/W；位位置：[8:0]；默认值：9'0；*/
/*description:这是需要将数据推送到链接描述符的fifo中。*/
#define UHCI_OUTFIFO_WDATA  0x000001FF
#define UHCI_OUTFIFO_WDATA_M  ((UHCI_OUTFIFO_WDATA_V)<<(UHCI_OUTFIFO_WDATA_S))
#define UHCI_OUTFIFO_WDATA_V  0x1FF
#define UHCI_OUTFIFO_WDATA_S  0

#define UHCI_DMA_IN_STATUS_REG(i)          (REG_UHCI_BASE(i) + 0x1C)
/* UHCI_RX_ERR_CAUSE:RO；比特位置：[6:4]；默认值：3'h0；*/
/*description:此寄存器存储出链路描述符的数据包中导致的错误。*/
#define UHCI_RX_ERR_CAUSE  0x00000007
#define UHCI_RX_ERR_CAUSE_M  ((UHCI_RX_ERR_CAUSE_V)<<(UHCI_RX_ERR_CAUSE_S))
#define UHCI_RX_ERR_CAUSE_V  0x7
#define UHCI_RX_ERR_CAUSE_S  4
/* UHCI_IN_EMPTY:RO；位位置：[1]；默认值：1’b1；*/
/*说明：*/
#define UHCI_IN_EMPTY  (BIT(1))
#define UHCI_IN_EMPTY_M  (BIT(1))
#define UHCI_IN_EMPTY_V  0x1
#define UHCI_IN_EMPTY_S  1
/* UHCI_IN_FULL:RO；位位置：[0]；默认值：1’b0；*/
/*说明：*/
#define UHCI_IN_FULL  (BIT(0))
#define UHCI_IN_FULL_M  (BIT(0))
#define UHCI_IN_FULL_V  0x1
#define UHCI_IN_FULL_S  0

#define UHCI_DMA_IN_POP_REG(i)          (REG_UHCI_BASE(i) + 0x20)
/* UHCI_infifopop:R/W；位位置：[16]；默认值：1'0；*/
/*description:设置此位以在链接描述符的fifo中弹出数据。*/
#define UHCI_INFIFO_POP  (BIT(16))
#define UHCI_INFIFO_POP_M  (BIT(16))
#define UHCI_INFIFO_POP_V  0x1
#define UHCI_INFIFO_POP_S  16
/* UHCI_infifoordata:RO；位位置：[11:0]；默认值：12'0；*/
/*description:此寄存器存储链接描述符的fifo中弹出的数据。*/
#define UHCI_INFIFO_RDATA  0x00000FFF
#define UHCI_INFIFO_RDATA_M  ((UHCI_INFIFO_RDATA_V)<<(UHCI_INFIFO_RDATA_S))
#define UHCI_INFIFO_RDATA_V  0xFFF
#define UHCI_INFIFO_RDATA_S  0

#define UHCI_DMA_OUT_LINK_REG(i)          (REG_UHCI_BASE(i) + 0x24)
/* UHCI_OUTLINK_PARK:RO；位位置：[31]；默认值：1'0；*/
/*描述：1：输出链路描述符的fsm处于空闲状态。0:输出链接描述符的fsm正在工作。*/
#define UHCI_OUTLINK_PARK  (BIT(31))
#define UHCI_OUTLINK_PARK_M  (BIT(31))
#define UHCI_OUTLINK_PARK_V  0x1
#define UHCI_OUTLINK_PARK_S  31
/* UHCI_OUTLINK_RESTART：R/W；位位置：[30]；默认值：1’b0；*/
/*description:设置此位以装入新的输出链接描述符*/
#define UHCI_OUTLINK_RESTART  (BIT(30))
#define UHCI_OUTLINK_RESTART_M  (BIT(30))
#define UHCI_OUTLINK_RESTART_V  0x1
#define UHCI_OUTLINK_RESTART_S  30
/* UHCI_OUTLINK_START:R/W；位位置：[29]；默认值：1’b0；*/
/*description:设置此位以开始处理输出链接描述符。*/
#define UHCI_OUTLINK_START  (BIT(29))
#define UHCI_OUTLINK_START_M  (BIT(29))
#define UHCI_OUTLINK_START_V  0x1
#define UHCI_OUTLINK_START_S  29
/* UHCI_OUTLINK_STOP:R/W；位位置：[28]；默认值：1’b0；*/
/*description:设置此位以停止处理输出链接描述符。*/
#define UHCI_OUTLINK_STOP  (BIT(28))
#define UHCI_OUTLINK_STOP_M  (BIT(28))
#define UHCI_OUTLINK_STOP_V  0x1
#define UHCI_OUTLINK_STOP_S  28
/* UHCI_OUTLINK_ADDR:R/W；比特位置：[19:0]；默认值：20'00；*/
/*description:此寄存器存储第一个出链路描述符地址的至少20位。*/
#define UHCI_OUTLINK_ADDR  0x000FFFFF
#define UHCI_OUTLINK_ADDR_M  ((UHCI_OUTLINK_ADDR_V)<<(UHCI_OUTLINK_ADDR_S))
#define UHCI_OUTLINK_ADDR_V  0xFFFFF
#define UHCI_OUTLINK_ADDR_S  0

#define UHCI_DMA_IN_LINK_REG(i)          (REG_UHCI_BASE(i) + 0x28)
/* UHCI_INLINK_PARK:RO；位位置：[31]；默认值：1'0；*/
/*描述：1：链接内描述符的fsm处于空闲状态。0:链接内描述符的fsm正在工作*/
#define UHCI_INLINK_PARK  (BIT(31))
#define UHCI_INLINK_PARK_M  (BIT(31))
#define UHCI_INLINK_PARK_V  0x1
#define UHCI_INLINK_PARK_S  31
/* UHCI_INLINK_RESTART：R/W；位位置：[30]；默认值：1’b0；*/
/*description:设置此位以装入新的链接内描述符*/
#define UHCI_INLINK_RESTART  (BIT(30))
#define UHCI_INLINK_RESTART_M  (BIT(30))
#define UHCI_INLINK_RESTART_V  0x1
#define UHCI_INLINK_RESTART_S  30
/* UHCI_INLINK_START:R/W；位位置：[29]；默认值：1’b0；*/
/*description:设置此位以开始处理链接内描述符。*/
#define UHCI_INLINK_START  (BIT(29))
#define UHCI_INLINK_START_M  (BIT(29))
#define UHCI_INLINK_START_V  0x1
#define UHCI_INLINK_START_S  29
/* UHCI_INLINK_STOP:R/W；位位置：[28]；默认值：1’b0；*/
/*description:设置此位以停止处理链接内描述符。*/
#define UHCI_INLINK_STOP  (BIT(28))
#define UHCI_INLINK_STOP_M  (BIT(28))
#define UHCI_INLINK_STOP_V  0x1
#define UHCI_INLINK_STOP_S  28
/* UHCI_INLINK_AUTO_RET:R/W；位位置：[20]；默认值：1’b1；*/
/*描述：1：当数据包在链接描述符中出错时，返回到最近使用的描述符。*/
#define UHCI_INLINK_AUTO_RET  (BIT(20))
#define UHCI_INLINK_AUTO_RET_M  (BIT(20))
#define UHCI_INLINK_AUTO_RET_V  0x1
#define UHCI_INLINK_AUTO_RET_S  20
/* UHCI_INLINK_ADDR:R/W；比特位置：[19:0]；默认值：20'00；*/
/*description:此寄存器存储第一个链接描述符地址的至少20位。*/
#define UHCI_INLINK_ADDR  0x000FFFFF
#define UHCI_INLINK_ADDR_M  ((UHCI_INLINK_ADDR_V)<<(UHCI_INLINK_ADDR_S))
#define UHCI_INLINK_ADDR_V  0xFFFFF
#define UHCI_INLINK_ADDR_S  0

#define UHCI_CONF1_REG(i)          (REG_UHCI_BASE(i) + 0x2C)
/* UHCI_DMA_INFIFO_FULL_THRS:R/W；比特位置：[20:9]；默认值：12'b0；*/
/*描述：当链接描述符的fifo中的数据量大于此寄存器值时，将产生uhci_dma_infifofull_wm_int中断。*/
#define UHCI_DMA_INFIFO_FULL_THRS  0x00000FFF
#define UHCI_DMA_INFIFO_FULL_THRS_M  ((UHCI_DMA_INFIFO_FULL_THRS_V)<<(UHCI_DMA_INFIFO_FULL_THRS_S))
#define UHCI_DMA_INFIFO_FULL_THRS_V  0xFFF
#define UHCI_DMA_INFIFO_FULL_THRS_S  9
/* UHCI_SW_START:R/W；位位置：[8]；默认值：1’b0；*/
/*description:设置此位以开始插入数据包标头。*/
#define UHCI_SW_START  (BIT(8))
#define UHCI_SW_START_M  (BIT(8))
#define UHCI_SW_START_V  0x1
#define UHCI_SW_START_S  8
/* UHCI_WAIT_SW_START:R/W；位位置：[7]；默认值：1’b0；*/
/*description:设置此位以启用软件方式添加数据包标头。*/
#define UHCI_WAIT_SW_START  (BIT(7))
#define UHCI_WAIT_SW_START_M  (BIT(7))
#define UHCI_WAIT_SW_START_V  0x1
#define UHCI_WAIT_SW_START_S  7
/* UHCI_CHECK_OWNER:R/W；位位置：[6]；默认值：1’b0；*/
/*description:设置此位以检查链接描述符中的所有者位。*/
#define UHCI_CHECK_OWNER  (BIT(6))
#define UHCI_CHECK_OWNER_M  (BIT(6))
#define UHCI_CHECK_OWNER_V  0x1
#define UHCI_CHECK_OWNER_S  6
/* UHCI_TX_ACK_NUM_RE:R/W；位位置：[5]；默认值：1’b1；*/
/*description:设置此位以启用硬件自动替换包头中的ack num。*/
#define UHCI_TX_ACK_NUM_RE  (BIT(5))
#define UHCI_TX_ACK_NUM_RE_M  (BIT(5))
#define UHCI_TX_ACK_NUM_RE_V  0x1
#define UHCI_TX_ACK_NUM_RE_S  5
/* UHCI_TX_CHECK_SUM_RE:R/W；位位置：[4]；默认值：1’b1；*/
/*description:设置此位以启用硬件自动替换包头中的check_sum。*/
#define UHCI_TX_CHECK_SUM_RE  (BIT(4))
#define UHCI_TX_CHECK_SUM_RE_M  (BIT(4))
#define UHCI_TX_CHECK_SUM_RE_V  0x1
#define UHCI_TX_CHECK_SUM_RE_S  4
/* UHCI_SAVE_HEAD:R/W；位位置：[3]；默认值：1’b0；*/
/*description:设置此位以保存数据包标头。*/
#define UHCI_SAVE_HEAD  (BIT(3))
#define UHCI_SAVE_HEAD_M  (BIT(3))
#define UHCI_SAVE_HEAD_V  0x1
#define UHCI_SAVE_HEAD_S  3
/* UHCI_CRC_DISABLE:R/W；位位置：[2]；默认值：1’b0；*/
/*description:设置此位以禁用crc计算。*/
#define UHCI_CRC_DISABLE  (BIT(2))
#define UHCI_CRC_DISABLE_M  (BIT(2))
#define UHCI_CRC_DISABLE_V  0x1
#define UHCI_CRC_DISABLE_S  2
/* UHCI_CHECK_SEQ_EN:R/W；位位置：[1]；默认值：1’b1；*/
/*description:设置此位以使解码器能够检查数据包标头中的seq num。*/
#define UHCI_CHECK_SEQ_EN  (BIT(1))
#define UHCI_CHECK_SEQ_EN_M  (BIT(1))
#define UHCI_CHECK_SEQ_EN_V  0x1
#define UHCI_CHECK_SEQ_EN_S  1
/* UHCI_CHECK_SUM_EN:R/W；位位置：[0]；默认值：1’b1；*/
/*description:设置此位以使解码器能够检查数据包标头中的check_sum。*/
#define UHCI_CHECK_SUM_EN  (BIT(0))
#define UHCI_CHECK_SUM_EN_M  (BIT(0))
#define UHCI_CHECK_SUM_EN_V  0x1
#define UHCI_CHECK_SUM_EN_S  0

#define UHCI_STATE0_REG(i)          (REG_UHCI_BASE(i) + 0x30)
/* UHCI_STATE0:RO；位位置：[31:0]；默认值：32'h0；*/
/*说明：*/
#define UHCI_STATE0  0xFFFFFFFF
#define UHCI_STATE0_M  ((UHCI_STATE0_V)<<(UHCI_STATE0_S))
#define UHCI_STATE0_V  0xFFFFFFFF
#define UHCI_STATE0_S  0

#define UHCI_STATE1_REG(i)          (REG_UHCI_BASE(i) + 0x34)
/* UHCI_STATE1:RO；位位置：[31:0]；默认值：32'h0；*/
/*说明：*/
#define UHCI_STATE1  0xFFFFFFFF
#define UHCI_STATE1_M  ((UHCI_STATE1_V)<<(UHCI_STATE1_S))
#define UHCI_STATE1_V  0xFFFFFFFF
#define UHCI_STATE1_S  0

#define UHCI_DMA_OUT_EOF_DES_ADDR_REG(i)          (REG_UHCI_BASE(i) + 0x38)
/* UHCI_OUT_EOF_DES_ADDR:RO；位位置：[31:0]；默认值：32'h0；*/
/*description:当此描述符中的eof位为1时，此寄存器存储出链路描述符ir的地址。*/
#define UHCI_OUT_EOF_DES_ADDR  0xFFFFFFFF
#define UHCI_OUT_EOF_DES_ADDR_M  ((UHCI_OUT_EOF_DES_ADDR_V)<<(UHCI_OUT_EOF_DES_ADDR_S))
#define UHCI_OUT_EOF_DES_ADDR_V  0xFFFFFFFF
#define UHCI_OUT_EOF_DES_ADDR_S  0

#define UHCI_DMA_IN_SUC_EOF_DES_ADDR_REG(i)          (REG_UHCI_BASE(i) + 0x3C)
/* UHCI_IN_SUC_EOF_DES_ADDR:RO；位位置：[31:0]；默认值：32'h0；*/
/*description:当此描述符中的eof位为1时，此寄存器存储链接内描述符的地址。*/
#define UHCI_IN_SUC_EOF_DES_ADDR  0xFFFFFFFF
#define UHCI_IN_SUC_EOF_DES_ADDR_M  ((UHCI_IN_SUC_EOF_DES_ADDR_V)<<(UHCI_IN_SUC_EOF_DES_ADDR_S))
#define UHCI_IN_SUC_EOF_DES_ADDR_V  0xFFFFFFFF
#define UHCI_IN_SUC_EOF_DES_ADDR_S  0

#define UHCI_DMA_IN_ERR_EOF_DES_ADDR_REG(i)          (REG_UHCI_BASE(i) + 0x40)
/* UHCI_IN_ERR_EOF_DES_ADDR:RO；位位置：[31:0]；默认值：32'h0；*/
/*description:当此描述符中存在一些错误时，此寄存器存储链接内描述符的地址。*/
#define UHCI_IN_ERR_EOF_DES_ADDR  0xFFFFFFFF
#define UHCI_IN_ERR_EOF_DES_ADDR_M  ((UHCI_IN_ERR_EOF_DES_ADDR_V)<<(UHCI_IN_ERR_EOF_DES_ADDR_S))
#define UHCI_IN_ERR_EOF_DES_ADDR_V  0xFFFFFFFF
#define UHCI_IN_ERR_EOF_DES_ADDR_S  0

#define UHCI_DMA_OUT_EOF_BFR_DES_ADDR_REG(i)          (REG_UHCI_BASE(i) + 0x44)
/* UHCI_OUT_EOF_BFR_DES_ADDR:RO；位位置：[31:0]；默认值：32'h0；*/
/*description:当此描述符中存在一些错误时，此寄存器存储输出链接描述符的地址。*/
#define UHCI_OUT_EOF_BFR_DES_ADDR  0xFFFFFFFF
#define UHCI_OUT_EOF_BFR_DES_ADDR_M  ((UHCI_OUT_EOF_BFR_DES_ADDR_V)<<(UHCI_OUT_EOF_BFR_DES_ADDR_S))
#define UHCI_OUT_EOF_BFR_DES_ADDR_V  0xFFFFFFFF
#define UHCI_OUT_EOF_BFR_DES_ADDR_S  0

#define UHCI_AHB_TEST_REG(i)          (REG_UHCI_BASE(i) + 0x48)
/* UHCI_AHB_testadr:R/W；比特位置：[5:4]；默认值：2’b0；*/
/*description:这两位代表ahb总线地址位[20:19]*/
#define UHCI_AHB_TESTADDR  0x00000003
#define UHCI_AHB_TESTADDR_M  ((UHCI_AHB_TESTADDR_V)<<(UHCI_AHB_TESTADDR_S))
#define UHCI_AHB_TESTADDR_V  0x3
#define UHCI_AHB_TESTADDR_S  4
/* UHCI_AHB_TESTMODE:R/W；位位置：[2:0]；默认值：3'b0；*/
/*描述：bit2是ahb总线测试启用，bit1用于选择wrtie（1）或read（0）模式。bit0用于选择仅测试一次（1）或继续（0）*/
#define UHCI_AHB_TESTMODE  0x00000007
#define UHCI_AHB_TESTMODE_M  ((UHCI_AHB_TESTMODE_V)<<(UHCI_AHB_TESTMODE_S))
#define UHCI_AHB_TESTMODE_V  0x7
#define UHCI_AHB_TESTMODE_S  0

#define UHCI_DMA_IN_DSCR_REG(i)          (REG_UHCI_BASE(i) + 0x4C)
/* UHCI_INLINK_DSCR:RO；位位置：[31:0]；默认值：32'b0；*/
/*description:当前链接描述符的第三个dword的内容*/
#define UHCI_INLINK_DSCR  0xFFFFFFFF
#define UHCI_INLINK_DSCR_M  ((UHCI_INLINK_DSCR_V)<<(UHCI_INLINK_DSCR_S))
#define UHCI_INLINK_DSCR_V  0xFFFFFFFF
#define UHCI_INLINK_DSCR_S  0

#define UHCI_DMA_IN_DSCR_BF0_REG(i)          (REG_UHCI_BASE(i) + 0x50)
/* UHCI_INLINK_DSCR_BF0:RO；位位置：[31:0]；默认值：32'b0；*/
/*description:当前链接描述符的第一个dword的内容*/
#define UHCI_INLINK_DSCR_BF0  0xFFFFFFFF
#define UHCI_INLINK_DSCR_BF0_M  ((UHCI_INLINK_DSCR_BF0_V)<<(UHCI_INLINK_DSCR_BF0_S))
#define UHCI_INLINK_DSCR_BF0_V  0xFFFFFFFF
#define UHCI_INLINK_DSCR_BF0_S  0

#define UHCI_DMA_IN_DSCR_BF1_REG(i)          (REG_UHCI_BASE(i) + 0x54)
/* UHCI_INLINK_DSCR_BF1:RO；位位置：[31:0]；默认值：32'b0；*/
/*description:当前链接描述符的第二个dword的内容*/
#define UHCI_INLINK_DSCR_BF1  0xFFFFFFFF
#define UHCI_INLINK_DSCR_BF1_M  ((UHCI_INLINK_DSCR_BF1_V)<<(UHCI_INLINK_DSCR_BF1_S))
#define UHCI_INLINK_DSCR_BF1_V  0xFFFFFFFF
#define UHCI_INLINK_DSCR_BF1_S  0

#define UHCI_DMA_OUT_DSCR_REG(i)          (REG_UHCI_BASE(i) + 0x58)
/* UHCI_OUTLINK_DSCR:RO；位位置：[31:0]；默认值：32'b0；*/
/*description:当前输出链接描述符的第三个dword的内容*/
#define UHCI_OUTLINK_DSCR  0xFFFFFFFF
#define UHCI_OUTLINK_DSCR_M  ((UHCI_OUTLINK_DSCR_V)<<(UHCI_OUTLINK_DSCR_S))
#define UHCI_OUTLINK_DSCR_V  0xFFFFFFFF
#define UHCI_OUTLINK_DSCR_S  0

#define UHCI_DMA_OUT_DSCR_BF0_REG(i)          (REG_UHCI_BASE(i) + 0x5C)
/* UHCI_OUTLINK_DSCR_BF0:RO；位位置：[31:0]；默认值：32'b0；*/
/*description:当前输出链接描述符的第一个dword的内容*/
#define UHCI_OUTLINK_DSCR_BF0  0xFFFFFFFF
#define UHCI_OUTLINK_DSCR_BF0_M  ((UHCI_OUTLINK_DSCR_BF0_V)<<(UHCI_OUTLINK_DSCR_BF0_S))
#define UHCI_OUTLINK_DSCR_BF0_V  0xFFFFFFFF
#define UHCI_OUTLINK_DSCR_BF0_S  0

#define UHCI_DMA_OUT_DSCR_BF1_REG(i)          (REG_UHCI_BASE(i) + 0x60)
/* UHCI_OUTLINK_DSCR_BF1:RO；位位置：[31:0]；默认值：32'b0；*/
/*description:当前输出链接描述符的第二个dword的内容*/
#define UHCI_OUTLINK_DSCR_BF1  0xFFFFFFFF
#define UHCI_OUTLINK_DSCR_BF1_M  ((UHCI_OUTLINK_DSCR_BF1_V)<<(UHCI_OUTLINK_DSCR_BF1_S))
#define UHCI_OUTLINK_DSCR_BF1_V  0xFFFFFFFF
#define UHCI_OUTLINK_DSCR_BF1_S  0

#define UHCI_ESCAPE_CONF_REG(i)          (REG_UHCI_BASE(i) + 0x64)
/* UHCI_RX_13_ESC_EN:R/W；位位置：[7]；默认值：1’b0；*/
/*description:设置此位以在DMA发送数据时启用流控制字符0x13替换。*/
#define UHCI_RX_13_ESC_EN  (BIT(7))
#define UHCI_RX_13_ESC_EN_M  (BIT(7))
#define UHCI_RX_13_ESC_EN_V  0x1
#define UHCI_RX_13_ESC_EN_S  7
/* UHCI_RX_11_ESC_EN:R/W；位位置：[6]；默认值：1’b0；*/
/*description:设置此位以在DMA发送数据时启用流控制字符0x11替换。*/
#define UHCI_RX_11_ESC_EN  (BIT(6))
#define UHCI_RX_11_ESC_EN_M  (BIT(6))
#define UHCI_RX_11_ESC_EN_V  0x1
#define UHCI_RX_11_ESC_EN_S  6
/* UHCI_RX_DB_ESC_EN:R/W；位位置：[5]；默认值：1’b1；*/
/*description:设置此位以在DMA发送数据时启用0xdb字符替换。*/
#define UHCI_RX_DB_ESC_EN  (BIT(5))
#define UHCI_RX_DB_ESC_EN_M  (BIT(5))
#define UHCI_RX_DB_ESC_EN_V  0x1
#define UHCI_RX_DB_ESC_EN_S  5
/* UHCI_RX_C0_es_EN:R/W；位位置：[4]；默认值：1’b1；*/
/*description:设置此位以在DMA发送数据时启用0xc0字符替换。*/
#define UHCI_RX_C0_ESC_EN  (BIT(4))
#define UHCI_RX_C0_ESC_EN_M  (BIT(4))
#define UHCI_RX_C0_ESC_EN_V  0x1
#define UHCI_RX_C0_ESC_EN_S  4
/* UHCI_TX_13_ESC_EN:R/W；位位置：[3]；默认值：1’b0；*/
/*description:设置此位以在DMA接收数据时启用流控制字符0x13解码。*/
#define UHCI_TX_13_ESC_EN  (BIT(3))
#define UHCI_TX_13_ESC_EN_M  (BIT(3))
#define UHCI_TX_13_ESC_EN_V  0x1
#define UHCI_TX_13_ESC_EN_S  3
/* UHCI_TX_11_ESC_EN:R/W；位位置：[2]；默认值：1’b0；*/
/*description:设置此位以在DMA接收数据时启用流控制字符0x11解码。*/
#define UHCI_TX_11_ESC_EN  (BIT(2))
#define UHCI_TX_11_ESC_EN_M  (BIT(2))
#define UHCI_TX_11_ESC_EN_V  0x1
#define UHCI_TX_11_ESC_EN_S  2
/* UHCI_TX_DB_ESC_EN:R/W；位位置：[1]；默认值：1’b1；*/
/*description:设置此位以在DMA接收数据时启用0xdb字符解码。*/
#define UHCI_TX_DB_ESC_EN  (BIT(1))
#define UHCI_TX_DB_ESC_EN_M  (BIT(1))
#define UHCI_TX_DB_ESC_EN_V  0x1
#define UHCI_TX_DB_ESC_EN_S  1
/* UHCI_TX_C0_ESC_EN:R/W；位位置：[0]；默认值：1’b1；*/
/*description:设置此位以在DMA接收数据时启用0xc0字符解码。*/
#define UHCI_TX_C0_ESC_EN  (BIT(0))
#define UHCI_TX_C0_ESC_EN_M  (BIT(0))
#define UHCI_TX_C0_ESC_EN_V  0x1
#define UHCI_TX_C0_ESC_EN_S  0

#define UHCI_HUNG_CONF_REG(i)          (REG_UHCI_BASE(i) + 0x68)
/* UHCI_RXFIFO_TIMEOUT_ENA:R/W；位位置：[23]；默认值：1’b1；*/
/*description:这是DMA发送数据超时的启用位*/
#define UHCI_RXFIFO_TIMEOUT_ENA  (BIT(23))
#define UHCI_RXFIFO_TIMEOUT_ENA_M  (BIT(23))
#define UHCI_RXFIFO_TIMEOUT_ENA_V  0x1
#define UHCI_RXFIFO_TIMEOUT_ENA_S  23
/* UHCI_RXFIFO_TIMEOUT_SHIFT:R/W；比特位置：[22:20]；默认值：3'b0；*/
/*description:当刻度计数的值>=（17'd8000>>reg_rxfifo_timeout_shift）时，将清除刻度计数*/
#define UHCI_RXFIFO_TIMEOUT_SHIFT  0x00000007
#define UHCI_RXFIFO_TIMEOUT_SHIFT_M  ((UHCI_RXFIFO_TIMEOUT_SHIFT_V)<<(UHCI_RXFIFO_TIMEOUT_SHIFT_S))
#define UHCI_RXFIFO_TIMEOUT_SHIFT_V  0x7
#define UHCI_RXFIFO_TIMEOUT_SHIFT_S  20
/* UHCI_RXFIFO_TIMEOUT:R/W；比特位置：[19:12]；默认值：8'h10；*/
/*description:此寄存器存储超时值。当DMA从RAM读取数据所花费的时间超过该寄存器值时，它将产生uhci_rx_hung_int中断。*/
#define UHCI_RXFIFO_TIMEOUT  0x000000FF
#define UHCI_RXFIFO_TIMEOUT_M  ((UHCI_RXFIFO_TIMEOUT_V)<<(UHCI_RXFIFO_TIMEOUT_S))
#define UHCI_RXFIFO_TIMEOUT_V  0xFF
#define UHCI_RXFIFO_TIMEOUT_S  12
/* UHCI_TXFIFO_TIMEOUT_ENA:R/W；位位置：[11]；默认值：1’b1；*/
/*description:txfifo接收数据超时的启用位*/
#define UHCI_TXFIFO_TIMEOUT_ENA  (BIT(11))
#define UHCI_TXFIFO_TIMEOUT_ENA_M  (BIT(11))
#define UHCI_TXFIFO_TIMEOUT_ENA_V  0x1
#define UHCI_TXFIFO_TIMEOUT_ENA_S  11
/* UHCI_TXFIFO_TIMEOUT_SHIFT:R/W；比特位置：[10:8]；默认值：3'b0；*/
/*description:当刻度计数的值>=（17'd8000>>reg_txfifo_timeout_shift）时，将清除刻度计数*/
#define UHCI_TXFIFO_TIMEOUT_SHIFT  0x00000007
#define UHCI_TXFIFO_TIMEOUT_SHIFT_M  ((UHCI_TXFIFO_TIMEOUT_SHIFT_V)<<(UHCI_TXFIFO_TIMEOUT_SHIFT_S))
#define UHCI_TXFIFO_TIMEOUT_SHIFT_V  0x7
#define UHCI_TXFIFO_TIMEOUT_SHIFT_S  8
/* UHCI_TXFIFO_TIMEOUT:R/W；位位置：[7:0]；默认值：8'h10；*/
/*description:此寄存器存储超时值。当DMA接收数据所花费的时间超过该寄存器值时，它将产生uhci_tx_hung_int中断。*/
#define UHCI_TXFIFO_TIMEOUT  0x000000FF
#define UHCI_TXFIFO_TIMEOUT_M  ((UHCI_TXFIFO_TIMEOUT_V)<<(UHCI_TXFIFO_TIMEOUT_S))
#define UHCI_TXFIFO_TIMEOUT_V  0xFF
#define UHCI_TXFIFO_TIMEOUT_S  0

#define UHCI_ACK_NUM_REG(i)          (REG_UHCI_BASE(i) + 0x6C)

#define UHCI_RX_HEAD_REG(i)          (REG_UHCI_BASE(i) + 0x70)
/* UHCI_RX_HEAD:RO；位位置：[31:0]；默认值：32'h0；*/
/*description:此寄存器存储DMA接收的数据包头*/
#define UHCI_RX_HEAD  0xFFFFFFFF
#define UHCI_RX_HEAD_M  ((UHCI_RX_HEAD_V)<<(UHCI_RX_HEAD_S))
#define UHCI_RX_HEAD_V  0xFFFFFFFF
#define UHCI_RX_HEAD_S  0

#define UHCI_QUICK_SENT_REG(i)          (REG_UHCI_BASE(i) + 0x74)
/* UHCI_ALWAYS_SEND_EN:R/W；位位置：[7]；默认值：1’b0；*/
/*description:设置此位以允许连续发送相同的短数据包*/
#define UHCI_ALWAYS_SEND_EN  (BIT(7))
#define UHCI_ALWAYS_SEND_EN_M  (BIT(7))
#define UHCI_ALWAYS_SEND_EN_V  0x1
#define UHCI_ALWAYS_SEND_EN_S  7
/* UHCI_ALWAYS_SEND_NUM:R/W；比特位置：[6:4]；默认值：3'h0；*/
/*description:位用于选择哪个短数据包*/
#define UHCI_ALWAYS_SEND_NUM  0x00000007
#define UHCI_ALWAYS_SEND_NUM_M  ((UHCI_ALWAYS_SEND_NUM_V)<<(UHCI_ALWAYS_SEND_NUM_S))
#define UHCI_ALWAYS_SEND_NUM_V  0x7
#define UHCI_ALWAYS_SEND_NUM_S  4
/* UHCI_SINGLE_SEND_EN:R/W；位位置：[3]；默认值：1’b0；*/
/*description:设置此位以启用发送短数据包*/
#define UHCI_SINGLE_SEND_EN  (BIT(3))
#define UHCI_SINGLE_SEND_EN_M  (BIT(3))
#define UHCI_SINGLE_SEND_EN_V  0x1
#define UHCI_SINGLE_SEND_EN_S  3
/* UHCI_SINGLE_SEND_NUM:R/W；位位置：[2:0]；默认值：3'h0；*/
/*description:位用于选择哪个短数据包*/
#define UHCI_SINGLE_SEND_NUM  0x00000007
#define UHCI_SINGLE_SEND_NUM_M  ((UHCI_SINGLE_SEND_NUM_V)<<(UHCI_SINGLE_SEND_NUM_S))
#define UHCI_SINGLE_SEND_NUM_V  0x7
#define UHCI_SINGLE_SEND_NUM_S  0

#define UHCI_Q0_WORD0_REG(i)          (REG_UHCI_BASE(i) + 0x78)
/* UHCI_SEND_Q0_WORD0:R/W；位位置：[31:0]；默认值：32'h0；*/
/*description:此寄存器存储短数据包的第一个双字的内容*/
#define UHCI_SEND_Q0_WORD0  0xFFFFFFFF
#define UHCI_SEND_Q0_WORD0_M  ((UHCI_SEND_Q0_WORD0_V)<<(UHCI_SEND_Q0_WORD0_S))
#define UHCI_SEND_Q0_WORD0_V  0xFFFFFFFF
#define UHCI_SEND_Q0_WORD0_S  0

#define UHCI_Q0_WORD1_REG(i)          (REG_UHCI_BASE(i) + 0x7C)
/* UHCI_SEND_Q0_WORD1:R/W；位位置：[31:0]；默认值：32'h0；*/
/*description:此寄存器存储短数据包的第二个双字的内容*/
#define UHCI_SEND_Q0_WORD1  0xFFFFFFFF
#define UHCI_SEND_Q0_WORD1_M  ((UHCI_SEND_Q0_WORD1_V)<<(UHCI_SEND_Q0_WORD1_S))
#define UHCI_SEND_Q0_WORD1_V  0xFFFFFFFF
#define UHCI_SEND_Q0_WORD1_S  0

#define UHCI_Q1_WORD0_REG(i)          (REG_UHCI_BASE(i) + 0x80)
/* UHCI_SEND_Q1_WORD0:R/W；位位置：[31:0]；默认值：32'h0；*/
/*description:此寄存器存储短数据包的第一个双字的内容*/
#define UHCI_SEND_Q1_WORD0  0xFFFFFFFF
#define UHCI_SEND_Q1_WORD0_M  ((UHCI_SEND_Q1_WORD0_V)<<(UHCI_SEND_Q1_WORD0_S))
#define UHCI_SEND_Q1_WORD0_V  0xFFFFFFFF
#define UHCI_SEND_Q1_WORD0_S  0

#define UHCI_Q1_WORD1_REG(i)          (REG_UHCI_BASE(i) + 0x84)
/* UHCI_SEND_Q1_WORD1:R/W；位位置：[31:0]；默认值：32'h0；*/
/*description:此寄存器存储短数据包的第二个双字的内容*/
#define UHCI_SEND_Q1_WORD1  0xFFFFFFFF
#define UHCI_SEND_Q1_WORD1_M  ((UHCI_SEND_Q1_WORD1_V)<<(UHCI_SEND_Q1_WORD1_S))
#define UHCI_SEND_Q1_WORD1_V  0xFFFFFFFF
#define UHCI_SEND_Q1_WORD1_S  0

#define UHCI_Q2_WORD0_REG(i)          (REG_UHCI_BASE(i) + 0x88)
/* UHCI_SEND_Q2_WORD0:R/W；位位置：[31:0]；默认值：32'h0；*/
/*description:此寄存器存储短数据包的第一个双字的内容*/
#define UHCI_SEND_Q2_WORD0  0xFFFFFFFF
#define UHCI_SEND_Q2_WORD0_M  ((UHCI_SEND_Q2_WORD0_V)<<(UHCI_SEND_Q2_WORD0_S))
#define UHCI_SEND_Q2_WORD0_V  0xFFFFFFFF
#define UHCI_SEND_Q2_WORD0_S  0

#define UHCI_Q2_WORD1_REG(i)          (REG_UHCI_BASE(i) + 0x8C)
/* UHCI_SEND_Q2_WORD1:R/W；位位置：[31:0]；默认值：32'h0；*/
/*description:此寄存器存储短数据包的第二个双字的内容*/
#define UHCI_SEND_Q2_WORD1  0xFFFFFFFF
#define UHCI_SEND_Q2_WORD1_M  ((UHCI_SEND_Q2_WORD1_V)<<(UHCI_SEND_Q2_WORD1_S))
#define UHCI_SEND_Q2_WORD1_V  0xFFFFFFFF
#define UHCI_SEND_Q2_WORD1_S  0

#define UHCI_Q3_WORD0_REG(i)          (REG_UHCI_BASE(i) + 0x90)
/* UHCI_SEND_Q3_WORD0:R/W；位位置：[31:0]；默认值：32'h0；*/
/*description:此寄存器存储短数据包的第一个双字的内容*/
#define UHCI_SEND_Q3_WORD0  0xFFFFFFFF
#define UHCI_SEND_Q3_WORD0_M  ((UHCI_SEND_Q3_WORD0_V)<<(UHCI_SEND_Q3_WORD0_S))
#define UHCI_SEND_Q3_WORD0_V  0xFFFFFFFF
#define UHCI_SEND_Q3_WORD0_S  0

#define UHCI_Q3_WORD1_REG(i)          (REG_UHCI_BASE(i) + 0x94)
/* UHCI_SEND_Q3_WORD1:R/W；位位置：[31:0]；默认值：32'h0；*/
/*description:此寄存器存储短数据包的第二个双字的内容*/
#define UHCI_SEND_Q3_WORD1  0xFFFFFFFF
#define UHCI_SEND_Q3_WORD1_M  ((UHCI_SEND_Q3_WORD1_V)<<(UHCI_SEND_Q3_WORD1_S))
#define UHCI_SEND_Q3_WORD1_V  0xFFFFFFFF
#define UHCI_SEND_Q3_WORD1_S  0

#define UHCI_Q4_WORD0_REG(i)          (REG_UHCI_BASE(i) + 0x98)
/* UHCI_SEND_Q4_WORD0:R/W；位位置：[31:0]；默认值：32'h0；*/
/*description:此寄存器存储短数据包的第一个双字的内容*/
#define UHCI_SEND_Q4_WORD0  0xFFFFFFFF
#define UHCI_SEND_Q4_WORD0_M  ((UHCI_SEND_Q4_WORD0_V)<<(UHCI_SEND_Q4_WORD0_S))
#define UHCI_SEND_Q4_WORD0_V  0xFFFFFFFF
#define UHCI_SEND_Q4_WORD0_S  0

#define UHCI_Q4_WORD1_REG(i)          (REG_UHCI_BASE(i) + 0x9C)
/* UHCI_SEND_Q4_WORD1:R/W；位位置：[31:0]；默认值：32'h0；*/
/*description:此寄存器存储短数据包的第二个双字的内容*/
#define UHCI_SEND_Q4_WORD1  0xFFFFFFFF
#define UHCI_SEND_Q4_WORD1_M  ((UHCI_SEND_Q4_WORD1_V)<<(UHCI_SEND_Q4_WORD1_S))
#define UHCI_SEND_Q4_WORD1_V  0xFFFFFFFF
#define UHCI_SEND_Q4_WORD1_S  0

#define UHCI_Q5_WORD0_REG(i)          (REG_UHCI_BASE(i) + 0xA0)
/* UHCI_SEND_Q5_WORD0:R/W；位位置：[31:0]；默认值：32'h0；*/
/*description:此寄存器存储短数据包的第一个双字的内容*/
#define UHCI_SEND_Q5_WORD0  0xFFFFFFFF
#define UHCI_SEND_Q5_WORD0_M  ((UHCI_SEND_Q5_WORD0_V)<<(UHCI_SEND_Q5_WORD0_S))
#define UHCI_SEND_Q5_WORD0_V  0xFFFFFFFF
#define UHCI_SEND_Q5_WORD0_S  0

#define UHCI_Q5_WORD1_REG(i)          (REG_UHCI_BASE(i) + 0xA4)
/* UHCI_SEND_Q5_WORD1:R/W；位位置：[31:0]；默认值：32'h0；*/
/*description:此寄存器存储短数据包的第二个双字的内容*/
#define UHCI_SEND_Q5_WORD1  0xFFFFFFFF
#define UHCI_SEND_Q5_WORD1_M  ((UHCI_SEND_Q5_WORD1_V)<<(UHCI_SEND_Q5_WORD1_S))
#define UHCI_SEND_Q5_WORD1_V  0xFFFFFFFF
#define UHCI_SEND_Q5_WORD1_S  0

#define UHCI_Q6_WORD0_REG(i)          (REG_UHCI_BASE(i) + 0xA8)
/* UHCI_SEND_Q6_WORD0:R/W；位位置：[31:0]；默认值：32'h0；*/
/*description:此寄存器存储短数据包的第一个双字的内容*/
#define UHCI_SEND_Q6_WORD0  0xFFFFFFFF
#define UHCI_SEND_Q6_WORD0_M  ((UHCI_SEND_Q6_WORD0_V)<<(UHCI_SEND_Q6_WORD0_S))
#define UHCI_SEND_Q6_WORD0_V  0xFFFFFFFF
#define UHCI_SEND_Q6_WORD0_S  0

#define UHCI_Q6_WORD1_REG(i)          (REG_UHCI_BASE(i) + 0xAC)
/* UHCI_SEND_Q6_WORD1:R/W；位位置：[31:0]；默认值：32'h0；*/
/*description:此寄存器存储短数据包的第二个双字的内容*/
#define UHCI_SEND_Q6_WORD1  0xFFFFFFFF
#define UHCI_SEND_Q6_WORD1_M  ((UHCI_SEND_Q6_WORD1_V)<<(UHCI_SEND_Q6_WORD1_S))
#define UHCI_SEND_Q6_WORD1_V  0xFFFFFFFF
#define UHCI_SEND_Q6_WORD1_S  0

#define UHCI_ESC_CONF0_REG(i)          (REG_UHCI_BASE(i) + 0xB0)
/* UHCI_SEPER_ESC_CHAR1:R/W；比特位置：[23:16]；默认值：8'hdc；*/
/*description:此寄存器存储用于替换数据中分隔符字符的第二个字符。默认情况下，0xdc 0xdb替换0xc0。*/
#define UHCI_SEPER_ESC_CHAR1  0x000000FF
#define UHCI_SEPER_ESC_CHAR1_M  ((UHCI_SEPER_ESC_CHAR1_V)<<(UHCI_SEPER_ESC_CHAR1_S))
#define UHCI_SEPER_ESC_CHAR1_V  0xFF
#define UHCI_SEPER_ESC_CHAR1_S  16
/* UHCI_SEPER_ESC_CHAR0:R/W；比特位置：[15:8]；默认值：8'hdb；*/
/*description:此寄存器存储用于替换数据中分隔符字符的第一个字符。*/
#define UHCI_SEPER_ESC_CHAR0  0x000000FF
#define UHCI_SEPER_ESC_CHAR0_M  ((UHCI_SEPER_ESC_CHAR0_V)<<(UHCI_SEPER_ESC_CHAR0_S))
#define UHCI_SEPER_ESC_CHAR0_V  0xFF
#define UHCI_SEPER_ESC_CHAR0_S  8
/* UHCI_SEPER_CHAR：R/W；位位置：[7:0]；默认值：8'hc0；*/
/*description:此寄存器存储分隔符字符分隔符字符用于分隔数据帧。*/
#define UHCI_SEPER_CHAR  0x000000FF
#define UHCI_SEPER_CHAR_M  ((UHCI_SEPER_CHAR_V)<<(UHCI_SEPER_CHAR_S))
#define UHCI_SEPER_CHAR_V  0xFF
#define UHCI_SEPER_CHAR_S  0

#define UHCI_ESC_CONF1_REG(i)          (REG_UHCI_BASE(i) + 0xB4)
/* UHCI_ESC_SEQ0_CHAR1:R/W；比特位置：[23:16]；默认值：8'hdd；*/
/*description:此寄存器存储用于替换数据中reg_esc_seq0的第二个字符*/
#define UHCI_ESC_SEQ0_CHAR1  0x000000FF
#define UHCI_ESC_SEQ0_CHAR1_M  ((UHCI_ESC_SEQ0_CHAR1_V)<<(UHCI_ESC_SEQ0_CHAR1_S))
#define UHCI_ESC_SEQ0_CHAR1_V  0xFF
#define UHCI_ESC_SEQ0_CHAR1_S  16
/* UHCI_ESC_SEQ0_CHAR0:R/W；比特位置：[15:8]；默认值：8'hdb；*/
/*description:此寄存器存储用于替换数据中reg_esc_seq0的第一个字符。*/
#define UHCI_ESC_SEQ0_CHAR0  0x000000FF
#define UHCI_ESC_SEQ0_CHAR0_M  ((UHCI_ESC_SEQ0_CHAR0_V)<<(UHCI_ESC_SEQ0_CHAR0_S))
#define UHCI_ESC_SEQ0_CHAR0_V  0xFF
#define UHCI_ESC_SEQ0_CHAR0_S  8
/* UHCI_ESC_SEQ0:R/W；位位置：[7:0]；默认值：8'hdb；*/
/*description:此寄存器存储用于替换分隔符字符的第一个替换字符。*/
#define UHCI_ESC_SEQ0  0x000000FF
#define UHCI_ESC_SEQ0_M  ((UHCI_ESC_SEQ0_V)<<(UHCI_ESC_SEQ0_S))
#define UHCI_ESC_SEQ0_V  0xFF
#define UHCI_ESC_SEQ0_S  0

#define UHCI_ESC_CONF2_REG(i)          (REG_UHCI_BASE(i) + 0xB8)
/* UHCI_ESC_SEQ1_CHAR1:R/W；比特位置：[23:16]；默认值：8'码；*/
/*description:此寄存器存储用于替换数据中的reg_esc_seq1的第二个字符。*/
#define UHCI_ESC_SEQ1_CHAR1  0x000000FF
#define UHCI_ESC_SEQ1_CHAR1_M  ((UHCI_ESC_SEQ1_CHAR1_V)<<(UHCI_ESC_SEQ1_CHAR1_S))
#define UHCI_ESC_SEQ1_CHAR1_V  0xFF
#define UHCI_ESC_SEQ1_CHAR1_S  16
/* UHCI_ESC_SEQ1_CHAR0:R/W；比特位置：[15:8]；默认值：8'hdb；*/
/*description:此寄存器存储用于替换数据中的reg_esc_seq1的第一个字符。*/
#define UHCI_ESC_SEQ1_CHAR0  0x000000FF
#define UHCI_ESC_SEQ1_CHAR0_M  ((UHCI_ESC_SEQ1_CHAR0_V)<<(UHCI_ESC_SEQ1_CHAR0_S))
#define UHCI_ESC_SEQ1_CHAR0_V  0xFF
#define UHCI_ESC_SEQ1_CHAR0_S  8
/* UHCI_ESC_SEQ1:R/W；位位置：[7:0]；默认值：8'h11；*/
/*description:此寄存器存储用于打开flow_control的流控制字符*/
#define UHCI_ESC_SEQ1  0x000000FF
#define UHCI_ESC_SEQ1_M  ((UHCI_ESC_SEQ1_V)<<(UHCI_ESC_SEQ1_S))
#define UHCI_ESC_SEQ1_V  0xFF
#define UHCI_ESC_SEQ1_S  0

#define UHCI_ESC_CONF3_REG(i)          (REG_UHCI_BASE(i) + 0xBC)
/* UHCI_ESC_SEQ2_CHAR1:R/W；比特位置：[23:16]；默认值：8'hdf；*/
/*description:此寄存器存储用于替换数据中的reg_esc_seq2的第二个字符。*/
#define UHCI_ESC_SEQ2_CHAR1  0x000000FF
#define UHCI_ESC_SEQ2_CHAR1_M  ((UHCI_ESC_SEQ2_CHAR1_V)<<(UHCI_ESC_SEQ2_CHAR1_S))
#define UHCI_ESC_SEQ2_CHAR1_V  0xFF
#define UHCI_ESC_SEQ2_CHAR1_S  16
/* UHCI_ESC_SEQ2_CHAR0:R/W；比特位置：[15:8]；默认值：8'hdb；*/
/*description:此寄存器存储用于替换数据中的reg_esc_seq2的第一个字符。*/
#define UHCI_ESC_SEQ2_CHAR0  0x000000FF
#define UHCI_ESC_SEQ2_CHAR0_M  ((UHCI_ESC_SEQ2_CHAR0_V)<<(UHCI_ESC_SEQ2_CHAR0_S))
#define UHCI_ESC_SEQ2_CHAR0_V  0xFF
#define UHCI_ESC_SEQ2_CHAR0_S  8
/* UHCI_ESC_SEQ2:R/W；位位置：[7:0]；默认值：8'h13；*/
/*description:此寄存器存储flow_control字符以关闭flow_controll*/
#define UHCI_ESC_SEQ2  0x000000FF
#define UHCI_ESC_SEQ2_M  ((UHCI_ESC_SEQ2_V)<<(UHCI_ESC_SEQ2_S))
#define UHCI_ESC_SEQ2_V  0xFF
#define UHCI_ESC_SEQ2_S  0

#define UHCI_PKT_THRES_REG(i)          (REG_UHCI_BASE(i) + 0xC0)
/* UHCI_PKT_THRS:R/W；位位置：[12:0]；默认值：13'80；*/
/*描述：当数据包有效载荷的量大于此值时，完成接收数据的过程。*/
#define UHCI_PKT_THRS  0x00001FFF
#define UHCI_PKT_THRS_M  ((UHCI_PKT_THRS_V)<<(UHCI_PKT_THRS_S))
#define UHCI_PKT_THRS_V  0x1FFF
#define UHCI_PKT_THRS_S  0

#define UHCI_DATE_REG(i)          (REG_UHCI_BASE(i) + 0xFC)
/* UHCI_日期：R/W；位位置：[31:0]；默认值：32'h16041001；*/
/*description:版本信息*/
#define UHCI_DATE  0xFFFFFFFF
#define UHCI_DATE_M  ((UHCI_DATE_V)<<(UHCI_DATE_S))
#define UHCI_DATE_V  0xFFFFFFFF
#define UHCI_DATE_S  0




#endif /*_SOC_UHCI_REG_H_ */

