// 版权所有2017-2021 Espressif Systems（Shanghai）PTE LTD
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
#ifndef _SOC_GDMA_REG_H_
#define _SOC_GDMA_REG_H_


#include "soc.h"
#ifdef __cplusplus
extern "C" {
#endif

#define GDMA_IN_CONF0_CH0_REG          (DR_REG_GDMA_BASE + 0x0)
/* GDMA_MEM_TRANS_EN_CH0:R/W；位位置：[4]；默认值：1’b0；*/
/*description:将此位设置为1，以启用通过DMA将数据从存储器自动传输到存储器。。*/
#define GDMA_MEM_TRANS_EN_CH0    (BIT(4))
#define GDMA_MEM_TRANS_EN_CH0_M  (BIT(4))
#define GDMA_MEM_TRANS_EN_CH0_V  0x1
#define GDMA_MEM_TRANS_EN_CH0_S  4
/* GDMA_IN_DATA_BURST_EN_CH0:R/W；位位置：[3]；默认值：1’b0；*/
/*description:当访问内部SRAM时，将此位设置为1以启用接收数据的Rx通道0的INCR突发传输。*/
#define GDMA_IN_DATA_BURST_EN_CH0    (BIT(3))
#define GDMA_IN_DATA_BURST_EN_CH0_M  (BIT(3))
#define GDMA_IN_DATA_BURST_EN_CH0_V  0x1
#define GDMA_IN_DATA_BURST_EN_CH0_S  3
/* GDMA_INDSCR_BURST_EN_CH0:R/W；位位置：[2]；默认值：1’b0；*/
/*description:当访问内部SRAM时，将此位设置为1以启用Rx通道0读取链路描述符的INCR突发传输。*/
#define GDMA_INDSCR_BURST_EN_CH0    (BIT(2))
#define GDMA_INDSCR_BURST_EN_CH0_M  (BIT(2))
#define GDMA_INDSCR_BURST_EN_CH0_V  0x1
#define GDMA_INDSCR_BURST_EN_CH0_S  2
/* GDMA_IN_LOOP_TEST_CH0:R/W；位位置：[1]；默认值：1’b0；*/
/*description:保留。*/
#define GDMA_IN_LOOP_TEST_CH0    (BIT(1))
#define GDMA_IN_LOOP_TEST_CH0_M  (BIT(1))
#define GDMA_IN_LOOP_TEST_CH0_V  0x1
#define GDMA_IN_LOOP_TEST_CH0_S  1
/* GDMA_IN_RST_CH0:R/W；位位置：[0]；默认值：1'0；*/
/*描述：此位用于重置DMA通道0 Rx FSM和Rx FIFO指针。。*/
#define GDMA_IN_RST_CH0    (BIT(0))
#define GDMA_IN_RST_CH0_M  (BIT(0))
#define GDMA_IN_RST_CH0_V  0x1
#define GDMA_IN_RST_CH0_S  0

#define GDMA_IN_CONF1_CH0_REG          (DR_REG_GDMA_BASE + 0x4)
/* GDMA_IN_EXT_MEM_BK_SIZE_CH0:R/W；比特位置：[14:13]；默认值：2’b0；*/
/*description:DMA访问外部SRAM时Rx通道0的块大小。0:16字节1:32字节2/3:保留。*/
#define GDMA_IN_EXT_MEM_BK_SIZE_CH0    0x00000003
#define GDMA_IN_EXT_MEM_BK_SIZE_CH0_M  ((GDMA_IN_EXT_MEM_BK_SIZE_CH0_V)<<(GDMA_IN_EXT_MEM_BK_SIZE_CH0_S))
#define GDMA_IN_EXT_MEM_BK_SIZE_CH0_V  0x3
#define GDMA_IN_EXT_MEM_BK_SIZE_CH0_S  13
/* GDMA_IN_CHECK_OWNER_CH0:R/W；位位置：[12]；默认值：1’b0；*/
/*description:设置此位以启用检查链接描述符的所有者属性。。*/
#define GDMA_IN_CHECK_OWNER_CH0    (BIT(12))
#define GDMA_IN_CHECK_OWNER_CH0_M  (BIT(12))
#define GDMA_IN_CHECK_OWNER_CH0_V  0x1
#define GDMA_IN_CHECK_OWNER_CH0_S  12
/* GDMA_DMA_INFIFO_FULL_THRS_CH0:R/W；位位置：[11:0]；默认值：12'hc；*/
/*描述：当Rx FIFO中的Rx通道0接收字节数达到寄存器值时，此寄存器用于生成INFIFO_FULL_WM_INT中断。。*/
#define GDMA_DMA_INFIFO_FULL_THRS_CH0    0x00000FFF
#define GDMA_DMA_INFIFO_FULL_THRS_CH0_M  ((GDMA_DMA_INFIFO_FULL_THRS_CH0_V)<<(GDMA_DMA_INFIFO_FULL_THRS_CH0_S))
#define GDMA_DMA_INFIFO_FULL_THRS_CH0_V  0xFFF
#define GDMA_DMA_INFIFO_FULL_THRS_CH0_S  0

#define GDMA_IN_INT_RAW_CH0_REG          (DR_REG_GDMA_BASE + 0x8)
/* GDMA_INFIFO_UDF_13_CH0_INT_RAW:R/WTC/SS；位位置：[9]；默认值：1’b0；*/
/*描述：当Rx通道0的第3级fifo未满流时，此原始中断位变为高电平。*/
#define GDMA_INFIFO_UDF_L3_CH0_INT_RAW    (BIT(9))
#define GDMA_INFIFO_UDF_L3_CH0_INT_RAW_M  (BIT(9))
#define GDMA_INFIFO_UDF_L3_CH0_INT_RAW_V  0x1
#define GDMA_INFIFO_UDF_L3_CH0_INT_RAW_S  9
/* GDMA_INFIFO_off_L3_CH0_INT_RAW:R/WTC/SS；位位置：[8]；默认值：1’b0；*/
/*描述：当Rx通道0的3级fifo等流量时，此原始中断位变为高电平。*/
#define GDMA_INFIFO_OVF_L3_CH0_INT_RAW    (BIT(8))
#define GDMA_INFIFO_OVF_L3_CH0_INT_RAW_M  (BIT(8))
#define GDMA_INFIFO_OVF_L3_CH0_INT_RAW_V  0x1
#define GDMA_INFIFO_OVF_L3_CH0_INT_RAW_S  8
/* GDMA_INFIFO_UDF_L1_CH0_INT_RAW:R/WTC/SS；位位置：[7]；默认值：1’b0；*/
/*描述：当Rx通道0的1级fifo处于低流量时，此原始中断位变为高电平。*/
#define GDMA_INFIFO_UDF_L1_CH0_INT_RAW    (BIT(7))
#define GDMA_INFIFO_UDF_L1_CH0_INT_RAW_M  (BIT(7))
#define GDMA_INFIFO_UDF_L1_CH0_INT_RAW_V  0x1
#define GDMA_INFIFO_UDF_L1_CH0_INT_RAW_S  7
/* GDMA_INFIFO_off_L1_CH0_INT_RAW:R/WTC/SS；位位置：[6]；默认值：1’b0；*/
/*描述：当Rx通道0的1级fifo等流量时，此原始中断位变为高电平。*/
#define GDMA_INFIFO_OVF_L1_CH0_INT_RAW    (BIT(6))
#define GDMA_INFIFO_OVF_L1_CH0_INT_RAW_M  (BIT(6))
#define GDMA_INFIFO_OVF_L1_CH0_INT_RAW_V  0x1
#define GDMA_INFIFO_OVF_L1_CH0_INT_RAW_S  6
/* GDMA_INFIFO_FULL_WM_CH0_INT_RAW:R/WTC/SS；位位置：[5]；默认值：1’b0；*/
/*描述：当接收的数据字节数达到信道0的Rx FIFO中REG_DMA_INFIFO_FULL_THS_CH0配置的阈值时，原始中断位变为高电平。。*/
#define GDMA_INFIFO_FULL_WM_CH0_INT_RAW    (BIT(5))
#define GDMA_INFIFO_FULL_WM_CH0_INT_RAW_M  (BIT(5))
#define GDMA_INFIFO_FULL_WM_CH0_INT_RAW_V  0x1
#define GDMA_INFIFO_FULL_WM_CH0_INT_RAW_S  5
/* GDMA_IN_DSCR_EMPTY_CH0_INT_RAW:R/WTC/SS；位位置：[4]；默认值：1’b0；*/
/*描述：当inlink指向的Rx缓冲区已满且未完成接收数据时，原始中断位变为高电平，但Rx通道0没有更多的inlink。。*/
#define GDMA_IN_DSCR_EMPTY_CH0_INT_RAW    (BIT(4))
#define GDMA_IN_DSCR_EMPTY_CH0_INT_RAW_M  (BIT(4))
#define GDMA_IN_DSCR_EMPTY_CH0_INT_RAW_V  0x1
#define GDMA_IN_DSCR_EMPTY_CH0_INT_RAW_S  4
/* GDMA_IN_DSCR_ERR_CH0_INT_RAW:R/WTC/SS；位位置：[3]；默认值：1’b0；*/
/*描述：当检测到内联描述符错误时，原始中断位变为高电平，包括所有者错误、Rx通道0的内联描述符的第二个和第三个字错误。。*/
#define GDMA_IN_DSCR_ERR_CH0_INT_RAW    (BIT(3))
#define GDMA_IN_DSCR_ERR_CH0_INT_RAW_M  (BIT(3))
#define GDMA_IN_DSCR_ERR_CH0_INT_RAW_V  0x1
#define GDMA_IN_DSCR_ERR_CH0_INT_RAW_S  3
/* GDMA_IN_ERR_EOF_CH0_INT_RAW:R/WTC/SS；位位置：[2]；默认值：1’b0；*/
/*描述：当仅在外围设备为UHCI0用于Rx信道0的情况下检测到数据错误时，原始中断位变为高电平。对于其他外围设备，保留此原始中断。。*/
#define GDMA_IN_ERR_EOF_CH0_INT_RAW    (BIT(2))
#define GDMA_IN_ERR_EOF_CH0_INT_RAW_M  (BIT(2))
#define GDMA_IN_ERR_EOF_CH0_INT_RAW_V  0x1
#define GDMA_IN_ERR_EOF_CH0_INT_RAW_S  2
/* GDMA_IN_SUC_EOF_CH0_INT_RAW:R/WTC/SS；位位置：[1]；默认值：1’b0；*/
/*描述：当接收到Rx通道0的一个内联描述符所指向的最后一个数据时，原始中断位变为高电平。对于UHCI0，当接收到一个内联描述符所指向的最近一个数据且未检测到Rx信道0的数据错误时，原始断开位变为低电平。。*/
#define GDMA_IN_SUC_EOF_CH0_INT_RAW    (BIT(1))
#define GDMA_IN_SUC_EOF_CH0_INT_RAW_M  (BIT(1))
#define GDMA_IN_SUC_EOF_CH0_INT_RAW_V  0x1
#define GDMA_IN_SUC_EOF_CH0_INT_RAW_S  1
/* GDMA_IN_DONE_CH0_INT_RAW:R/WTC/SS；位位置：[0]；默认值：1’b0；*/
/*描述：当接收到Rx通道0的一个内联描述符所指向的最后一个数据时，原始中断位变为高电平。。*/
#define GDMA_IN_DONE_CH0_INT_RAW    (BIT(0))
#define GDMA_IN_DONE_CH0_INT_RAW_M  (BIT(0))
#define GDMA_IN_DONE_CH0_INT_RAW_V  0x1
#define GDMA_IN_DONE_CH0_INT_RAW_S  0

#define GDMA_IN_INT_ST_CH0_REG          (DR_REG_GDMA_BASE + 0xC)
/* GDMA_INFIFO_UDF_13_CH0_INT_ST:RO；位位置：[9]；默认值：1’b0；*/
/*description:INFIFO_UDF_L3_CH_INT中断的原始中断状态位。。*/
#define GDMA_INFIFO_UDF_L3_CH0_INT_ST    (BIT(9))
#define GDMA_INFIFO_UDF_L3_CH0_INT_ST_M  (BIT(9))
#define GDMA_INFIFO_UDF_L3_CH0_INT_ST_V  0x1
#define GDMA_INFIFO_UDF_L3_CH0_INT_ST_S  9
/* GDMA_INFIFO_off_L3_CH0_INT_ST:RO；位位置：[8]；默认值：1’b0；*/
/*description:INFIFO_OVF_L3_CH_INT中断的原始中断状态位。。*/
#define GDMA_INFIFO_OVF_L3_CH0_INT_ST    (BIT(8))
#define GDMA_INFIFO_OVF_L3_CH0_INT_ST_M  (BIT(8))
#define GDMA_INFIFO_OVF_L3_CH0_INT_ST_V  0x1
#define GDMA_INFIFO_OVF_L3_CH0_INT_ST_S  8
/* GDMA_INFIFO_UDF_L1_CH0_INT_ST:RO；位位置：[7]；默认值：1’b0；*/
/*description:INFIFO_UDF_L1_CH_INT中断的原始中断状态位。。*/
#define GDMA_INFIFO_UDF_L1_CH0_INT_ST    (BIT(7))
#define GDMA_INFIFO_UDF_L1_CH0_INT_ST_M  (BIT(7))
#define GDMA_INFIFO_UDF_L1_CH0_INT_ST_V  0x1
#define GDMA_INFIFO_UDF_L1_CH0_INT_ST_S  7
/* GDMA_INFIFO_off_L1_CH0_INT_ST:RO；位位置：[6]；默认值：1’b0；*/
/*description:INFIFO_OVF_L1_CH_INT中断的原始中断状态位。。*/
#define GDMA_INFIFO_OVF_L1_CH0_INT_ST    (BIT(6))
#define GDMA_INFIFO_OVF_L1_CH0_INT_ST_M  (BIT(6))
#define GDMA_INFIFO_OVF_L1_CH0_INT_ST_V  0x1
#define GDMA_INFIFO_OVF_L1_CH0_INT_ST_S  6
/* GDMA_INFIFO_FULL_WM_CH0_INT_ST:RO；位位置：[5]；默认值：1’b0；*/
/*description:INFIFO_FULL_WM_CH_INT中断的原始中断状态位。。*/
#define GDMA_INFIFO_FULL_WM_CH0_INT_ST    (BIT(5))
#define GDMA_INFIFO_FULL_WM_CH0_INT_ST_M  (BIT(5))
#define GDMA_INFIFO_FULL_WM_CH0_INT_ST_V  0x1
#define GDMA_INFIFO_FULL_WM_CH0_INT_ST_S  5
/* GDMA_IN_DSCR_EMPTY-CH0_INT_ST:RO；位位置：[4]；默认值：1’b0；*/
/*description:IN_DSCR_EMPTY_CH_INT中断的原始中断状态位。。*/
#define GDMA_IN_DSCR_EMPTY_CH0_INT_ST    (BIT(4))
#define GDMA_IN_DSCR_EMPTY_CH0_INT_ST_M  (BIT(4))
#define GDMA_IN_DSCR_EMPTY_CH0_INT_ST_V  0x1
#define GDMA_IN_DSCR_EMPTY_CH0_INT_ST_S  4
/* GDMA_IN_DSCR_ERR_CH0_INT_ST:RO；位位置：[3]；默认值：1’b0；*/
/*description:IN_DSCR_ERR_CH_INT中断的原始中断状态位。。*/
#define GDMA_IN_DSCR_ERR_CH0_INT_ST    (BIT(3))
#define GDMA_IN_DSCR_ERR_CH0_INT_ST_M  (BIT(3))
#define GDMA_IN_DSCR_ERR_CH0_INT_ST_V  0x1
#define GDMA_IN_DSCR_ERR_CH0_INT_ST_S  3
/* GDMA_IN_ERR_EOF_CH0_INT_ST:RO；位位置：[2]；默认值：1’b0；*/
/*description:IN_ERR_EOF_CH_INT中断的原始中断状态位。。*/
#define GDMA_IN_ERR_EOF_CH0_INT_ST    (BIT(2))
#define GDMA_IN_ERR_EOF_CH0_INT_ST_M  (BIT(2))
#define GDMA_IN_ERR_EOF_CH0_INT_ST_V  0x1
#define GDMA_IN_ERR_EOF_CH0_INT_ST_S  2
/* GDMA_IN_SUC_EOF_CH0_INT_ST:RO；位位置：[1]；默认值：1’b0；*/
/*description:IN_SUC_EOF_CH_INT中断的原始中断状态位。。*/
#define GDMA_IN_SUC_EOF_CH0_INT_ST    (BIT(1))
#define GDMA_IN_SUC_EOF_CH0_INT_ST_M  (BIT(1))
#define GDMA_IN_SUC_EOF_CH0_INT_ST_V  0x1
#define GDMA_IN_SUC_EOF_CH0_INT_ST_S  1
/* GDMA_IN_DONE_CH0_INT_ST:RO；位位置：[0]；默认值：1’b0；*/
/*description:IN_DONE_CH_INT中断的原始中断状态位。。*/
#define GDMA_IN_DONE_CH0_INT_ST    (BIT(0))
#define GDMA_IN_DONE_CH0_INT_ST_M  (BIT(0))
#define GDMA_IN_DONE_CH0_INT_ST_V  0x1
#define GDMA_IN_DONE_CH0_INT_ST_S  0

#define GDMA_IN_INT_ENA_CH0_REG          (DR_REG_GDMA_BASE + 0x10)
/* GDMA_INFIFO_UDF_13_CH0_INT_ENA:R/W；位位置：[9]；默认值：1’b0；*/
/*description:INFIFO_UDF_L3_CH_INT中断的中断启用位。。*/
#define GDMA_INFIFO_UDF_L3_CH0_INT_ENA    (BIT(9))
#define GDMA_INFIFO_UDF_L3_CH0_INT_ENA_M  (BIT(9))
#define GDMA_INFIFO_UDF_L3_CH0_INT_ENA_V  0x1
#define GDMA_INFIFO_UDF_L3_CH0_INT_ENA_S  9
/* GDMA_INFIFO_off_13_CH0_INT_ENA:R/W；位位置：[8]；默认值：1’b0；*/
/*description:INFIFO_OVF_L3_CH_INT中断的中断启用位。。*/
#define GDMA_INFIFO_OVF_L3_CH0_INT_ENA    (BIT(8))
#define GDMA_INFIFO_OVF_L3_CH0_INT_ENA_M  (BIT(8))
#define GDMA_INFIFO_OVF_L3_CH0_INT_ENA_V  0x1
#define GDMA_INFIFO_OVF_L3_CH0_INT_ENA_S  8
/* GDMA_INFIFO_UDF_L1_CH0_INT_ENA:R/W；位位置：[7]；默认值：1’b0；*/
/*description:INFIFO_UDF_L1_CH_INT中断的中断启用位。。*/
#define GDMA_INFIFO_UDF_L1_CH0_INT_ENA    (BIT(7))
#define GDMA_INFIFO_UDF_L1_CH0_INT_ENA_M  (BIT(7))
#define GDMA_INFIFO_UDF_L1_CH0_INT_ENA_V  0x1
#define GDMA_INFIFO_UDF_L1_CH0_INT_ENA_S  7
/* GDMA_INFIFO_off_L1_CH0_INT_ENA:R/W；位位置：[6]；默认值：1’b0；*/
/*description:INFIFO_OVF_L1_CH_INT中断的中断启用位。。*/
#define GDMA_INFIFO_OVF_L1_CH0_INT_ENA    (BIT(6))
#define GDMA_INFIFO_OVF_L1_CH0_INT_ENA_M  (BIT(6))
#define GDMA_INFIFO_OVF_L1_CH0_INT_ENA_V  0x1
#define GDMA_INFIFO_OVF_L1_CH0_INT_ENA_S  6
/* GDMA_INFIFO_FULL_WM_CH0_INT_ENA:R/W；位位置：[5]；默认值：1’b0；*/
/*description:INFIFO_FULL_WM_CH_INT中断的中断启用位。。*/
#define GDMA_INFIFO_FULL_WM_CH0_INT_ENA    (BIT(5))
#define GDMA_INFIFO_FULL_WM_CH0_INT_ENA_M  (BIT(5))
#define GDMA_INFIFO_FULL_WM_CH0_INT_ENA_V  0x1
#define GDMA_INFIFO_FULL_WM_CH0_INT_ENA_S  5
/* GDMA_IN_DSCR_EMPTY-CH0_INT_ENA:R/W；位位置：[4]；默认值：1’b0；*/
/*description:IN_DSCR_EMPTY_CH_INT中断的中断启用位。。*/
#define GDMA_IN_DSCR_EMPTY_CH0_INT_ENA    (BIT(4))
#define GDMA_IN_DSCR_EMPTY_CH0_INT_ENA_M  (BIT(4))
#define GDMA_IN_DSCR_EMPTY_CH0_INT_ENA_V  0x1
#define GDMA_IN_DSCR_EMPTY_CH0_INT_ENA_S  4
/* GDMA_IN_DSCR_ERR_CH0_INT_ENA:R/W；位位置：[3]；默认值：1’b0；*/
/*description:IN_DSCR_ERR_CH_INT中断的中断启用位。。*/
#define GDMA_IN_DSCR_ERR_CH0_INT_ENA    (BIT(3))
#define GDMA_IN_DSCR_ERR_CH0_INT_ENA_M  (BIT(3))
#define GDMA_IN_DSCR_ERR_CH0_INT_ENA_V  0x1
#define GDMA_IN_DSCR_ERR_CH0_INT_ENA_S  3
/* GDMA_IN_ERR_EOF_CH0_INT_ENA:R/W；位位置：[2]；默认值：1’b0；*/
/*description:IN_ERR_EOF_CH_INT中断的中断启用位。。*/
#define GDMA_IN_ERR_EOF_CH0_INT_ENA    (BIT(2))
#define GDMA_IN_ERR_EOF_CH0_INT_ENA_M  (BIT(2))
#define GDMA_IN_ERR_EOF_CH0_INT_ENA_V  0x1
#define GDMA_IN_ERR_EOF_CH0_INT_ENA_S  2
/* GDMA_IN_SUC_EOF_CH0_INT_ENA:R/W；位位置：[1]；默认值：1’b0；*/
/*description:IN_SUC_EOF_CH_INT中断的中断启用位。。*/
#define GDMA_IN_SUC_EOF_CH0_INT_ENA    (BIT(1))
#define GDMA_IN_SUC_EOF_CH0_INT_ENA_M  (BIT(1))
#define GDMA_IN_SUC_EOF_CH0_INT_ENA_V  0x1
#define GDMA_IN_SUC_EOF_CH0_INT_ENA_S  1
/* GDMA_IN_DONE_CH0_INT_ENA:R/W；位位置：[0]；默认值：1’b0；*/
/*description:IN_DONE_CH_INT中断的中断启用位。。*/
#define GDMA_IN_DONE_CH0_INT_ENA    (BIT(0))
#define GDMA_IN_DONE_CH0_INT_ENA_M  (BIT(0))
#define GDMA_IN_DONE_CH0_INT_ENA_V  0x1
#define GDMA_IN_DONE_CH0_INT_ENA_S  0

#define GDMA_IN_INT_CLR_CH0_REG          (DR_REG_GDMA_BASE + 0x14)
/* GDMA_INFIFO_UDF_13_CH0_INT_CLR:WT；位位置：[9]；默认值：1’b0；*/
/*description:设置此位以清除INFIFO_UDF_L3_CH_INT中断。。*/
#define GDMA_INFIFO_UDF_L3_CH0_INT_CLR    (BIT(9))
#define GDMA_INFIFO_UDF_L3_CH0_INT_CLR_M  (BIT(9))
#define GDMA_INFIFO_UDF_L3_CH0_INT_CLR_V  0x1
#define GDMA_INFIFO_UDF_L3_CH0_INT_CLR_S  9
/* GDMA_INFIFO_off_13_CH0_INT_CLR:WT；位位置：[8]；默认值：1’b0；*/
/*description:设置此位以清除INFIFO_OVF_L3_CH_INT中断。。*/
#define GDMA_INFIFO_OVF_L3_CH0_INT_CLR    (BIT(8))
#define GDMA_INFIFO_OVF_L3_CH0_INT_CLR_M  (BIT(8))
#define GDMA_INFIFO_OVF_L3_CH0_INT_CLR_V  0x1
#define GDMA_INFIFO_OVF_L3_CH0_INT_CLR_S  8
/* GDMA_INFIFO_UDF_L1_CH0_INT_CLR:WT；位位置：[7]；默认值：1’b0；*/
/*description:设置此位以清除INFIFO_UDF_L1_CH_INT中断。。*/
#define GDMA_INFIFO_UDF_L1_CH0_INT_CLR    (BIT(7))
#define GDMA_INFIFO_UDF_L1_CH0_INT_CLR_M  (BIT(7))
#define GDMA_INFIFO_UDF_L1_CH0_INT_CLR_V  0x1
#define GDMA_INFIFO_UDF_L1_CH0_INT_CLR_S  7
/* GDMA_INFIFO_off_L1_CH0_INT_CLR:WT；位位置：[6]；默认值：1’b0；*/
/*description:设置此位以清除INFIFO_OVF_L1_CH_INT中断。。*/
#define GDMA_INFIFO_OVF_L1_CH0_INT_CLR    (BIT(6))
#define GDMA_INFIFO_OVF_L1_CH0_INT_CLR_M  (BIT(6))
#define GDMA_INFIFO_OVF_L1_CH0_INT_CLR_V  0x1
#define GDMA_INFIFO_OVF_L1_CH0_INT_CLR_S  6
/* GDMA_DMA_INFIFO_FULL_WM_CH0_INT_CLR:WT；位位置：[5]；默认值：1’b0；*/
/*description:设置此位以清除INFIFO_FULL_WM_CH_INT中断。。*/
#define GDMA_DMA_INFIFO_FULL_WM_CH0_INT_CLR    (BIT(5))
#define GDMA_DMA_INFIFO_FULL_WM_CH0_INT_CLR_M  (BIT(5))
#define GDMA_DMA_INFIFO_FULL_WM_CH0_INT_CLR_V  0x1
#define GDMA_DMA_INFIFO_FULL_WM_CH0_INT_CLR_S  5
/* GDMA_IN_DSCR_EMPTY-CH0_INT_CLR:WT；位位置：[4]；默认值：1’b0；*/
/*description:设置此位以清除IN_DSCR_EMPTY_CH_INT中断。。*/
#define GDMA_IN_DSCR_EMPTY_CH0_INT_CLR    (BIT(4))
#define GDMA_IN_DSCR_EMPTY_CH0_INT_CLR_M  (BIT(4))
#define GDMA_IN_DSCR_EMPTY_CH0_INT_CLR_V  0x1
#define GDMA_IN_DSCR_EMPTY_CH0_INT_CLR_S  4
/* GDMA_IN_DSCR_ERR_CH0_INT_CLR:WT；位位置：[3]；默认值：1’b0；*/
/*description:设置此位以清除IN_DSCR_ERR_CH_INT中断。。*/
#define GDMA_IN_DSCR_ERR_CH0_INT_CLR    (BIT(3))
#define GDMA_IN_DSCR_ERR_CH0_INT_CLR_M  (BIT(3))
#define GDMA_IN_DSCR_ERR_CH0_INT_CLR_V  0x1
#define GDMA_IN_DSCR_ERR_CH0_INT_CLR_S  3
/* GDMA_IN_ERR_EOF_CH0_INT_CLR:WT；位位置：[2]；默认值：1’b0；*/
/*description:设置此位以清除IN_ERR_EOF_CH_INT中断。。*/
#define GDMA_IN_ERR_EOF_CH0_INT_CLR    (BIT(2))
#define GDMA_IN_ERR_EOF_CH0_INT_CLR_M  (BIT(2))
#define GDMA_IN_ERR_EOF_CH0_INT_CLR_V  0x1
#define GDMA_IN_ERR_EOF_CH0_INT_CLR_S  2
/* GDMA_IN_SUC_EOF_CH0_INT_CLR:WT；位位置：[1]；默认值：1’b0；*/
/*description:设置此位以清除IN_SUC_EOF_CH_INT中断。。*/
#define GDMA_IN_SUC_EOF_CH0_INT_CLR    (BIT(1))
#define GDMA_IN_SUC_EOF_CH0_INT_CLR_M  (BIT(1))
#define GDMA_IN_SUC_EOF_CH0_INT_CLR_V  0x1
#define GDMA_IN_SUC_EOF_CH0_INT_CLR_S  1
/* GDMA_IN_DONE_CH0_INT_CLR:WT；位位置：[0]；默认值：1’b0；*/
/*description:设置此位以清除IN_DONE_CH_INT中断。。*/
#define GDMA_IN_DONE_CH0_INT_CLR    (BIT(0))
#define GDMA_IN_DONE_CH0_INT_CLR_M  (BIT(0))
#define GDMA_IN_DONE_CH0_INT_CLR_V  0x1
#define GDMA_IN_DONE_CH0_INT_CLR_S  0

#define GDMA_INFIFO_STATUS_CH0_REG          (DR_REG_GDMA_BASE + 0x18)
/* GDMA_IN_BUF_HUNGRY_CH0:RO；位位置：[28]；默认值：1’b0；*/
/*description:保留。*/
#define GDMA_IN_BUF_HUNGRY_CH0    (BIT(28))
#define GDMA_IN_BUF_HUNGRY_CH0_M  (BIT(28))
#define GDMA_IN_BUF_HUNGRY_CH0_V  0x1
#define GDMA_IN_BUF_HUNGRY_CH0_S  28
/* GDMA_IN_REMAIN_UNDER_4B_L3_CH0:RO；位位置：[27]；默认值：1’b1；*/
/*description:保留。*/
#define GDMA_IN_REMAIN_UNDER_4B_L3_CH0    (BIT(27))
#define GDMA_IN_REMAIN_UNDER_4B_L3_CH0_M  (BIT(27))
#define GDMA_IN_REMAIN_UNDER_4B_L3_CH0_V  0x1
#define GDMA_IN_REMAIN_UNDER_4B_L3_CH0_S  27
/* GDMA_IN_REMAIN_UNDER_3B_L3_CH0:RO；位位置：[26]；默认值：1’b1；*/
/*description:保留。*/
#define GDMA_IN_REMAIN_UNDER_3B_L3_CH0    (BIT(26))
#define GDMA_IN_REMAIN_UNDER_3B_L3_CH0_M  (BIT(26))
#define GDMA_IN_REMAIN_UNDER_3B_L3_CH0_V  0x1
#define GDMA_IN_REMAIN_UNDER_3B_L3_CH0_S  26
/* GDMA_IN_REMAIN_UNDER_2B_L3_CH0:RO；位位置：[25]；默认值：1’b1；*/
/*description:保留。*/
#define GDMA_IN_REMAIN_UNDER_2B_L3_CH0    (BIT(25))
#define GDMA_IN_REMAIN_UNDER_2B_L3_CH0_M  (BIT(25))
#define GDMA_IN_REMAIN_UNDER_2B_L3_CH0_V  0x1
#define GDMA_IN_REMAIN_UNDER_2B_L3_CH0_S  25
/* GDMA_IN_REMAIN_UNDER_1B_L3_CH0:RO；位位置：[24]；默认值：1’b1；*/
/*description:保留。*/
#define GDMA_IN_REMAIN_UNDER_1B_L3_CH0    (BIT(24))
#define GDMA_IN_REMAIN_UNDER_1B_L3_CH0_M  (BIT(24))
#define GDMA_IN_REMAIN_UNDER_1B_L3_CH0_V  0x1
#define GDMA_IN_REMAIN_UNDER_1B_L3_CH0_S  24
/* GDMA_INFIFO_CNT_L3_CH0:RO；比特位置：[23:19]；默认值：5’b0；*/
/*描述：寄存器存储Rx通道0的L3 Rx FIFO中数据的字节数。。*/
#define GDMA_INFIFO_CNT_L3_CH0    0x0000001F
#define GDMA_INFIFO_CNT_L3_CH0_M  ((GDMA_INFIFO_CNT_L3_CH0_V)<<(GDMA_INFIFO_CNT_L3_CH0_S))
#define GDMA_INFIFO_CNT_L3_CH0_V  0x1F
#define GDMA_INFIFO_CNT_L3_CH0_S  19
/* GDMA_INFIFO_CNT_L2_CH0:RO；比特位置：[18:12]；默认值：7'b0；*/
/*描述：寄存器将数据的字节数存储在Rx通道0的L2 Rx FIFO中。。*/
#define GDMA_INFIFO_CNT_L2_CH0    0x0000007F
#define GDMA_INFIFO_CNT_L2_CH0_M  ((GDMA_INFIFO_CNT_L2_CH0_V)<<(GDMA_INFIFO_CNT_L2_CH0_S))
#define GDMA_INFIFO_CNT_L2_CH0_V  0x7F
#define GDMA_INFIFO_CNT_L2_CH0_S  12
/* GDMA_INFIFO_CNT_L1_CH0:RO；位位置：[11:6]；默认值：6'b0；*/
/*描述：寄存器将数据的字节数存储在Rx通道0的L1 Rx FIFO中。。*/
#define GDMA_INFIFO_CNT_L1_CH0    0x0000003F
#define GDMA_INFIFO_CNT_L1_CH0_M  ((GDMA_INFIFO_CNT_L1_CH0_V)<<(GDMA_INFIFO_CNT_L1_CH0_S))
#define GDMA_INFIFO_CNT_L1_CH0_V  0x3F
#define GDMA_INFIFO_CNT_L1_CH0_S  6
/* GDMA_INFIFO_EMPTY_L3_CH0:RO；位位置：[5]；默认值：1’b1；*/
/*描述：Rx信道0的L3 Rx FIFO空信号。。*/
#define GDMA_INFIFO_EMPTY_L3_CH0    (BIT(5))
#define GDMA_INFIFO_EMPTY_L3_CH0_M  (BIT(5))
#define GDMA_INFIFO_EMPTY_L3_CH0_V  0x1
#define GDMA_INFIFO_EMPTY_L3_CH0_S  5
/* GDMA_INFIFO_FULL_L3_CH0:RO；位位置：[4]；默认值：1’b1；*/
/*描述：Rx信道0的L3 Rx FIFO满信号。。*/
#define GDMA_INFIFO_FULL_L3_CH0    (BIT(4))
#define GDMA_INFIFO_FULL_L3_CH0_M  (BIT(4))
#define GDMA_INFIFO_FULL_L3_CH0_V  0x1
#define GDMA_INFIFO_FULL_L3_CH0_S  4
/* GDMA_INFIFO_EMPTY_L2_CH0:RO；位位置：[3]；默认值：1’b1；*/
/*描述：Rx信道0的L2 Rx FIFO空信号。。*/
#define GDMA_INFIFO_EMPTY_L2_CH0    (BIT(3))
#define GDMA_INFIFO_EMPTY_L2_CH0_M  (BIT(3))
#define GDMA_INFIFO_EMPTY_L2_CH0_V  0x1
#define GDMA_INFIFO_EMPTY_L2_CH0_S  3
/* GDMA_INFIFO_FULL_L2_CH0:RO；位位置：[2]；默认值：1’b0；*/
/*描述：Rx信道0的L2 Rx FIFO满信号。。*/
#define GDMA_INFIFO_FULL_L2_CH0    (BIT(2))
#define GDMA_INFIFO_FULL_L2_CH0_M  (BIT(2))
#define GDMA_INFIFO_FULL_L2_CH0_V  0x1
#define GDMA_INFIFO_FULL_L2_CH0_S  2
/* GDMA_INFIFO_EMPTY_L1_CH0:RO；位位置：[1]；默认值：1’b1；*/
/*描述：Rx信道0的L1 Rx FIFO空信号。。*/
#define GDMA_INFIFO_EMPTY_L1_CH0    (BIT(1))
#define GDMA_INFIFO_EMPTY_L1_CH0_M  (BIT(1))
#define GDMA_INFIFO_EMPTY_L1_CH0_V  0x1
#define GDMA_INFIFO_EMPTY_L1_CH0_S  1
/* GDMA_INFIFO_FULL_L1_CH0:RO；位位置：[0]；默认值：1’b0；*/
/*描述：Rx信道0的L1 Rx FIFO完整信号。。*/
#define GDMA_INFIFO_FULL_L1_CH0    (BIT(0))
#define GDMA_INFIFO_FULL_L1_CH0_M  (BIT(0))
#define GDMA_INFIFO_FULL_L1_CH0_V  0x1
#define GDMA_INFIFO_FULL_L1_CH0_S  0

#define GDMA_IN_POP_CH0_REG          (DR_REG_GDMA_BASE + 0x1C)
/* GDMA_INFIFO_POP_CH0:R/W/SC；位位置：[12]；默认值：1'0；*/
/*description:将此位设置为从DMA FIFO弹出数据。。*/
#define GDMA_INFIFO_POP_CH0    (BIT(12))
#define GDMA_INFIFO_POP_CH0_M  (BIT(12))
#define GDMA_INFIFO_POP_CH0_V  0x1
#define GDMA_INFIFO_POP_CH0_S  12
/* GDMA_INFIFO_data_CH0:RO；位位置：[11:0]；默认值：12'h800；*/
/*description:此寄存器存储从DMA FIFO弹出的数据。。*/
#define GDMA_INFIFO_RDATA_CH0    0x00000FFF
#define GDMA_INFIFO_RDATA_CH0_M  ((GDMA_INFIFO_RDATA_CH0_V)<<(GDMA_INFIFO_RDATA_CH0_S))
#define GDMA_INFIFO_RDATA_CH0_V  0xFFF
#define GDMA_INFIFO_RDATA_CH0_S  0

#define GDMA_IN_LINK_CH0_REG          (DR_REG_GDMA_BASE + 0x20)
/* GDMA_INLINK_PARK_CH0:RO；位位置：[24]；默认值：1'h1；*/
/*description:1：内联描述符的FSM处于空闲状态。0:内联描述符的FSM正在工作。。*/
#define GDMA_INLINK_PARK_CH0    (BIT(24))
#define GDMA_INLINK_PARK_CH0_M  (BIT(24))
#define GDMA_INLINK_PARK_CH0_V  0x1
#define GDMA_INLINK_PARK_CH0_S  24
/* GDMA_INLINK_RESTART_CH0:R/W/SC；位位置：[23]；默认值：1’b0；*/
/*description:设置此位以装入新的内联描述符。。*/
#define GDMA_INLINK_RESTART_CH0    (BIT(23))
#define GDMA_INLINK_RESTART_CH0_M  (BIT(23))
#define GDMA_INLINK_RESTART_CH0_V  0x1
#define GDMA_INLINK_RESTART_CH0_S  23
/* GDMA_INLINK_START_CH0:R/W/SC；位位置：[22]；默认值：1’b0；*/
/*description:设置此位以开始处理内联描述符。。*/
#define GDMA_INLINK_START_CH0    (BIT(22))
#define GDMA_INLINK_START_CH0_M  (BIT(22))
#define GDMA_INLINK_START_CH0_V  0x1
#define GDMA_INLINK_START_CH0_S  22
/* GDMA_INLINK_STOP_CH0:R/W/SC；位位置：[21]；默认值：1’b0；*/
/*description:设置此位以停止处理内联描述符。。*/
#define GDMA_INLINK_STOP_CH0    (BIT(21))
#define GDMA_INLINK_STOP_CH0_M  (BIT(21))
#define GDMA_INLINK_STOP_CH0_V  0x1
#define GDMA_INLINK_STOP_CH0_S  21
/* GDMA_INLINK_AUTO_RET_CH0:R/W；位位置：[20]；默认值：1’b1；*/
/*description:当当前接收数据中存在一些错误时，将此位设置为返回当前内联描述符的地址。。*/
#define GDMA_INLINK_AUTO_RET_CH0    (BIT(20))
#define GDMA_INLINK_AUTO_RET_CH0_M  (BIT(20))
#define GDMA_INLINK_AUTO_RET_CH0_V  0x1
#define GDMA_INLINK_AUTO_RET_CH0_S  20
/* GDMA_INLINK_ADDR_CH0:R/W；比特位置：[19:0]；默认值：20'00；*/
/*description:此寄存器存储第一个内联描述符地址的20个最低有效位。。*/
#define GDMA_INLINK_ADDR_CH0    0x000FFFFF
#define GDMA_INLINK_ADDR_CH0_M  ((GDMA_INLINK_ADDR_CH0_V)<<(GDMA_INLINK_ADDR_CH0_S))
#define GDMA_INLINK_ADDR_CH0_V  0xFFFFF
#define GDMA_INLINK_ADDR_CH0_S  0

#define GDMA_IN_STATE_CH0_REG          (DR_REG_GDMA_BASE + 0x24)
/* GDMA_IN_STATE_CH0:RO；比特位置：[22:20]；默认值：3'b0；*/
/*description:保留。*/
#define GDMA_IN_STATE_CH0    0x00000007
#define GDMA_IN_STATE_CH0_M  ((GDMA_IN_STATE_CH0_V)<<(GDMA_IN_STATE_CH0_S))
#define GDMA_IN_STATE_CH0_V  0x7
#define GDMA_IN_STATE_CH0_S  20
/* GDMA_IN_DSCR_STATE_CH0:RO；比特位置：[19:18]；默认值：2’b0；*/
/*description:保留。*/
#define GDMA_IN_DSCR_STATE_CH0    0x00000003
#define GDMA_IN_DSCR_STATE_CH0_M  ((GDMA_IN_DSCR_STATE_CH0_V)<<(GDMA_IN_DSCR_STATE_CH0_S))
#define GDMA_IN_DSCR_STATE_CH0_V  0x3
#define GDMA_IN_DSCR_STATE_CH0_S  18
/* GDMA_INLINK_DSCR_ADDR_CH0:RO；比特位置：[17:00]；默认值：18'b0；*/
/*description:此寄存器存储当前内联描述符的地址。。*/
#define GDMA_INLINK_DSCR_ADDR_CH0    0x0003FFFF
#define GDMA_INLINK_DSCR_ADDR_CH0_M  ((GDMA_INLINK_DSCR_ADDR_CH0_V)<<(GDMA_INLINK_DSCR_ADDR_CH0_S))
#define GDMA_INLINK_DSCR_ADDR_CH0_V  0x3FFFF
#define GDMA_INLINK_DSCR_ADDR_CH0_S  0

#define GDMA_IN_SUC_EOF_DES_ADDR_CH0_REG          (DR_REG_GDMA_BASE + 0x28)
/* GDMA_IN_SUC_EOF_DES_ADDR_CH0:RO；位位置：[31:0]；默认值：32'h0；*/
/*description:当此描述符中的EOF位为1时，此寄存器存储内联描述符的地址。。*/
#define GDMA_IN_SUC_EOF_DES_ADDR_CH0    0xFFFFFFFF
#define GDMA_IN_SUC_EOF_DES_ADDR_CH0_M  ((GDMA_IN_SUC_EOF_DES_ADDR_CH0_V)<<(GDMA_IN_SUC_EOF_DES_ADDR_CH0_S))
#define GDMA_IN_SUC_EOF_DES_ADDR_CH0_V  0xFFFFFFFF
#define GDMA_IN_SUC_EOF_DES_ADDR_CH0_S  0

#define GDMA_IN_ERR_EOF_DES_ADDR_CH0_REG          (DR_REG_GDMA_BASE + 0x2C)
/* GDMA_IN_ERR_EOF_DES_ADDR_CH0:RO；位位置：[31:0]；默认值：32'h0；*/
/*description:当当前接收数据中存在一些错误时，此寄存器存储内联描述符的地址。仅当外围设备为UHCI0时使用。。*/
#define GDMA_IN_ERR_EOF_DES_ADDR_CH0    0xFFFFFFFF
#define GDMA_IN_ERR_EOF_DES_ADDR_CH0_M  ((GDMA_IN_ERR_EOF_DES_ADDR_CH0_V)<<(GDMA_IN_ERR_EOF_DES_ADDR_CH0_S))
#define GDMA_IN_ERR_EOF_DES_ADDR_CH0_V  0xFFFFFFFF
#define GDMA_IN_ERR_EOF_DES_ADDR_CH0_S  0

#define GDMA_IN_DSCR_CH0_REG          (DR_REG_GDMA_BASE + 0x30)
/* GDMA_INLINK_DSCR_CH0:RO；位位置：[31:0]；默认值：32'b0；*/
/*description:当前内联描述符x的地址。。*/
#define GDMA_INLINK_DSCR_CH0    0xFFFFFFFF
#define GDMA_INLINK_DSCR_CH0_M  ((GDMA_INLINK_DSCR_CH0_V)<<(GDMA_INLINK_DSCR_CH0_S))
#define GDMA_INLINK_DSCR_CH0_V  0xFFFFFFFF
#define GDMA_INLINK_DSCR_CH0_S  0

#define GDMA_IN_DSCR_BF0_CH0_REG          (DR_REG_GDMA_BASE + 0x34)
/* GDMA_INLINK_DSCR_BF0_CH0:RO；位位置：[31:0]；默认值：32'b0；*/
/*description:最后一个内联描述符x-1的地址。。*/
#define GDMA_INLINK_DSCR_BF0_CH0    0xFFFFFFFF
#define GDMA_INLINK_DSCR_BF0_CH0_M  ((GDMA_INLINK_DSCR_BF0_CH0_V)<<(GDMA_INLINK_DSCR_BF0_CH0_S))
#define GDMA_INLINK_DSCR_BF0_CH0_V  0xFFFFFFFF
#define GDMA_INLINK_DSCR_BF0_CH0_S  0

#define GDMA_IN_DSCR_BF1_CH0_REG          (DR_REG_GDMA_BASE + 0x38)
/* GDMA_INLINK_DSCR_BF1_CH0:RO；位位置：[31:0]；默认值：32'b0；*/
/*description:倒数第二个内联描述符x-2的地址。。*/
#define GDMA_INLINK_DSCR_BF1_CH0    0xFFFFFFFF
#define GDMA_INLINK_DSCR_BF1_CH0_M  ((GDMA_INLINK_DSCR_BF1_CH0_V)<<(GDMA_INLINK_DSCR_BF1_CH0_S))
#define GDMA_INLINK_DSCR_BF1_CH0_V  0xFFFFFFFF
#define GDMA_INLINK_DSCR_BF1_CH0_S  0

#define GDMA_IN_WIGHT_CH0_REG          (DR_REG_GDMA_BASE + 0x3C)
/* GDMA_RX_WEIGHT_CH0:R/W；位位置：[11:8]；默认值：4'hf；*/
/*description:Rx通道0的权重。*/
#define GDMA_RX_WEIGHT_CH0    0x0000000F
#define GDMA_RX_WEIGHT_CH0_M  ((GDMA_RX_WEIGHT_CH0_V)<<(GDMA_RX_WEIGHT_CH0_S))
#define GDMA_RX_WEIGHT_CH0_V  0xF
#define GDMA_RX_WEIGHT_CH0_S  8

#define GDMA_IN_PRI_CH0_REG          (DR_REG_GDMA_BASE + 0x44)
/* GDMA_RX_PRI_CH0:R/W；位位置：[3:0]；默认值：4'b0；*/
/*description:Rx通道0的优先级。值越大，优先级越高。。*/
#define GDMA_RX_PRI_CH0    0x0000000F
#define GDMA_RX_PRI_CH0_M  ((GDMA_RX_PRI_CH0_V)<<(GDMA_RX_PRI_CH0_S))
#define GDMA_RX_PRI_CH0_V  0xF
#define GDMA_RX_PRI_CH0_S  0

#define GDMA_IN_PERI_SEL_CH0_REG          (DR_REG_GDMA_BASE + 0x48)
/* GDMA_PERI_IN_SEL_CH0:R/W；比特位置：[5:0]；默认值：6'h3f；*/
/*描述：此寄存器用于选择Rx通道的外围设备。0:SPI2.1:SPI3.2:UHCI0.3:I2S0.4:I2S1.5:LCD_CAM。6： AES。7： 沙。8： ADC_DAC。9： RMT。。*/
#define GDMA_PERI_IN_SEL_CH0    0x0000003F
#define GDMA_PERI_IN_SEL_CH0_M  ((GDMA_PERI_IN_SEL_CH0_V)<<(GDMA_PERI_IN_SEL_CH0_S))
#define GDMA_PERI_IN_SEL_CH0_V  0x3F
#define GDMA_PERI_IN_SEL_CH0_S  0

#define GDMA_OUT_CONF0_CH0_REG          (DR_REG_GDMA_BASE + 0x60)
/* GDMA_OUT_DATA_BURST_EN_CH0:R/W；位位置：[5]；默认值：1’b0；*/
/*描述：当访问内部SRAM时，将此位设置为1以启用传输数据的Tx信道0的INCR突发传输。*/
#define GDMA_OUT_DATA_BURST_EN_CH0    (BIT(5))
#define GDMA_OUT_DATA_BURST_EN_CH0_M  (BIT(5))
#define GDMA_OUT_DATA_BURST_EN_CH0_V  0x1
#define GDMA_OUT_DATA_BURST_EN_CH0_S  5
/* GDMA_OUTDSCR_BURST_EN_CH0:R/W；位位置：[4]；默认值：1’b0；*/
/*description:将此位设置为1，以便在访问内部SRAM时，为Tx通道0读取链路描述符启用INCR突发传输。*/
#define GDMA_OUTDSCR_BURST_EN_CH0    (BIT(4))
#define GDMA_OUTDSCR_BURST_EN_CH0_M  (BIT(4))
#define GDMA_OUTDSCR_BURST_EN_CH0_V  0x1
#define GDMA_OUTDSCR_BURST_EN_CH0_S  4
/* GDMA_OUT_EOF_MODE_CH0:R/W；位位置：[3]；默认值：1’b1；*/
/*描述：传输数据时EOF标志生成模式。1： 当需要传输的数据从DMA中的FIFO弹出时，生成Tx信道0的EOF标志。*/
#define GDMA_OUT_EOF_MODE_CH0    (BIT(3))
#define GDMA_OUT_EOF_MODE_CH0_M  (BIT(3))
#define GDMA_OUT_EOF_MODE_CH0_V  0x1
#define GDMA_OUT_EOF_MODE_CH0_S  3
/* GDMA_OUT_AUTO_WRBACK_CH0:R/W；位位置：[2]；默认值：1’b0；*/
/*description:设置此位以在传输tx缓冲区中的所有数据时启用自动outlink写回。。*/
#define GDMA_OUT_AUTO_WRBACK_CH0    (BIT(2))
#define GDMA_OUT_AUTO_WRBACK_CH0_M  (BIT(2))
#define GDMA_OUT_AUTO_WRBACK_CH0_V  0x1
#define GDMA_OUT_AUTO_WRBACK_CH0_S  2
/* GDMA_OUT_LOOP_TEST_CH0:R/W；位位置：[1]；默认值：1’b0；*/
/*description:保留。*/
#define GDMA_OUT_LOOP_TEST_CH0    (BIT(1))
#define GDMA_OUT_LOOP_TEST_CH0_M  (BIT(1))
#define GDMA_OUT_LOOP_TEST_CH0_V  0x1
#define GDMA_OUT_LOOP_TEST_CH0_S  1
/* GDMA_OUT_RST_CH0:R/W；位位置：[0]；默认值：1’b0；*/
/*描述：此位用于重置DMA通道0 Tx FSM和Tx FIFO指针。。*/
#define GDMA_OUT_RST_CH0    (BIT(0))
#define GDMA_OUT_RST_CH0_M  (BIT(0))
#define GDMA_OUT_RST_CH0_V  0x1
#define GDMA_OUT_RST_CH0_S  0

#define GDMA_OUT_CONF1_CH0_REG          (DR_REG_GDMA_BASE + 0x64)
/* GDMA_OUT_EXT_MEM_BK_SIZE_CH0:R/W；比特位置：[14:13]；默认值：2’b0；*/
/*描述：DMA访问外部SRAM时Tx通道0的块大小。0:16字节1:32字节2/3:保留。*/
#define GDMA_OUT_EXT_MEM_BK_SIZE_CH0    0x00000003
#define GDMA_OUT_EXT_MEM_BK_SIZE_CH0_M  ((GDMA_OUT_EXT_MEM_BK_SIZE_CH0_V)<<(GDMA_OUT_EXT_MEM_BK_SIZE_CH0_S))
#define GDMA_OUT_EXT_MEM_BK_SIZE_CH0_V  0x3
#define GDMA_OUT_EXT_MEM_BK_SIZE_CH0_S  13
/* GDMA_OUT_CHECK_OWNER_CH0:R/W；位位置：[12]；默认值：1’b0；*/
/*description:设置此位以启用检查链接描述符的所有者属性。。*/
#define GDMA_OUT_CHECK_OWNER_CH0    (BIT(12))
#define GDMA_OUT_CHECK_OWNER_CH0_M  (BIT(12))
#define GDMA_OUT_CHECK_OWNER_CH0_V  0x1
#define GDMA_OUT_CHECK_OWNER_CH0_S  12

#define GDMA_OUT_INT_RAW_CH0_REG          (DR_REG_GDMA_BASE + 0x68)
/* GDMA_OUTFIFO_UDF_L3_CH0_INT_RAW:R/WTC/SS；位位置：[7]；默认值：1’b0；*/
/*描述：当Tx信道0的第3级fifo未满流时，此原始中断位变为高电平。*/
#define GDMA_OUTFIFO_UDF_L3_CH0_INT_RAW    (BIT(7))
#define GDMA_OUTFIFO_UDF_L3_CH0_INT_RAW_M  (BIT(7))
#define GDMA_OUTFIFO_UDF_L3_CH0_INT_RAW_V  0x1
#define GDMA_OUTFIFO_UDF_L3_CH0_INT_RAW_S  7
/* GDMA_OUTFIFO_off_L3_CH0_INT_RAW:R/WTC/SS；位位置：[6]；默认值：1’b0；*/
/*描述：当Tx信道0的3级fifo等流量时，此原始中断位变为高电平。*/
#define GDMA_OUTFIFO_OVF_L3_CH0_INT_RAW    (BIT(6))
#define GDMA_OUTFIFO_OVF_L3_CH0_INT_RAW_M  (BIT(6))
#define GDMA_OUTFIFO_OVF_L3_CH0_INT_RAW_V  0x1
#define GDMA_OUTFIFO_OVF_L3_CH0_INT_RAW_S  6
/* GDMA_OUTFIFO_UDF_L1_CH0_INT_RAW:R/WTC/SS；位位置：[5]；默认值：1’b0；*/
/*描述：当Tx信道0的1级fifo处于低流量时，此原始中断位变为高电平。*/
#define GDMA_OUTFIFO_UDF_L1_CH0_INT_RAW    (BIT(5))
#define GDMA_OUTFIFO_UDF_L1_CH0_INT_RAW_M  (BIT(5))
#define GDMA_OUTFIFO_UDF_L1_CH0_INT_RAW_V  0x1
#define GDMA_OUTFIFO_UDF_L1_CH0_INT_RAW_S  5
/* GDMA_OUTFIFO_off_L1_CH0_INT_RAW:R/WTC/SS；位位置：[4]；默认值：1’b0；*/
/*描述：当Tx信道0的1级fifo等流量时，此原始中断位变为高电平。*/
#define GDMA_OUTFIFO_OVF_L1_CH0_INT_RAW    (BIT(4))
#define GDMA_OUTFIFO_OVF_L1_CH0_INT_RAW_M  (BIT(4))
#define GDMA_OUTFIFO_OVF_L1_CH0_INT_RAW_V  0x1
#define GDMA_OUTFIFO_OVF_L1_CH0_INT_RAW_S  4
/* GDMA_OUT_TOTAL_EOF_CH0_INT_RAW:R/WTC/SS；位位置：[3]；默认值：1’b0；*/
/*描述：当针对Tx信道0发送出与输出链接（包括一个链接描述符或几个链接描述符）相对应的数据时，原始中断位变为高电平。。*/
#define GDMA_OUT_TOTAL_EOF_CH0_INT_RAW    (BIT(3))
#define GDMA_OUT_TOTAL_EOF_CH0_INT_RAW_M  (BIT(3))
#define GDMA_OUT_TOTAL_EOF_CH0_INT_RAW_V  0x1
#define GDMA_OUT_TOTAL_EOF_CH0_INT_RAW_S  3
/* GDMA_OUT_DSCR_ERR_CH0_INT_RAW:R/WTC/SS；位位置：[2]；默认值：1’b0；*/
/*描述：当检测到outlink描述符错误时，原始中断位变为高电平，包括所有者错误、Tx信道0的outlink描述符的第二个和第三个字错误。。*/
#define GDMA_OUT_DSCR_ERR_CH0_INT_RAW    (BIT(2))
#define GDMA_OUT_DSCR_ERR_CH0_INT_RAW_M  (BIT(2))
#define GDMA_OUT_DSCR_ERR_CH0_INT_RAW_V  0x1
#define GDMA_OUT_DSCR_ERR_CH0_INT_RAW_S  2
/* GDMA_OUT_EOF_CH0_INT_RAW:R/WTC/SS；位位置：[1]；默认值：1’b0；*/
/*描述：当从Tx通道0的存储器中读取一个输出描述符所指向的最后一个数据时，原始中断位变为高电平。*/
#define GDMA_OUT_EOF_CH0_INT_RAW    (BIT(1))
#define GDMA_OUT_EOF_CH0_INT_RAW_M  (BIT(1))
#define GDMA_OUT_EOF_CH0_INT_RAW_V  0x1
#define GDMA_OUT_EOF_CH0_INT_RAW_S  1
/* GDMA_OUT_DONE_CH0_INT_RAW:R/WTC/SS；位位置：[0]；默认值：1’b0；*/
/*描述：当一个输出描述符所指向的最后一个数据已传输到Tx信道0的外围设备时，原始中断位变为高电平。。*/
#define GDMA_OUT_DONE_CH0_INT_RAW    (BIT(0))
#define GDMA_OUT_DONE_CH0_INT_RAW_M  (BIT(0))
#define GDMA_OUT_DONE_CH0_INT_RAW_V  0x1
#define GDMA_OUT_DONE_CH0_INT_RAW_S  0

#define GDMA_OUT_INT_ST_CH0_REG          (DR_REG_GDMA_BASE + 0x6C)
/* GDMA_OUTFIFO_UDF_L3_CH0_INT_ST:RO；位位置：[7]；默认值：1’b0；*/
/*description:OUTFIFO_UDF_L3_CH_INT中断的原始中断状态位。。*/
#define GDMA_OUTFIFO_UDF_L3_CH0_INT_ST    (BIT(7))
#define GDMA_OUTFIFO_UDF_L3_CH0_INT_ST_M  (BIT(7))
#define GDMA_OUTFIFO_UDF_L3_CH0_INT_ST_V  0x1
#define GDMA_OUTFIFO_UDF_L3_CH0_INT_ST_S  7
/* GDMA_OUTFIFO_off_L3_CH0_INT_ST:RO；位位置：[6]；默认值：1’b0；*/
/*description:OUTFIFO_OVF_L3_CH_INT中断的原始中断状态位。。*/
#define GDMA_OUTFIFO_OVF_L3_CH0_INT_ST    (BIT(6))
#define GDMA_OUTFIFO_OVF_L3_CH0_INT_ST_M  (BIT(6))
#define GDMA_OUTFIFO_OVF_L3_CH0_INT_ST_V  0x1
#define GDMA_OUTFIFO_OVF_L3_CH0_INT_ST_S  6
/* GDMA_OUTFIFO_UDF_L1_CH0_INT_ST:RO；位位置：[5]；默认值：1’b0；*/
/*description:OUTFIFO_UDF_L1_CH_INT中断的原始中断状态位。。*/
#define GDMA_OUTFIFO_UDF_L1_CH0_INT_ST    (BIT(5))
#define GDMA_OUTFIFO_UDF_L1_CH0_INT_ST_M  (BIT(5))
#define GDMA_OUTFIFO_UDF_L1_CH0_INT_ST_V  0x1
#define GDMA_OUTFIFO_UDF_L1_CH0_INT_ST_S  5
/* GDMA_OUTFIFO_off_L1_CH0_INT_ST:RO；位位置：[4]；默认值：1’b0；*/
/*description:OUTFIFO_OVF_L1_CH_INT中断的原始中断状态位。。*/
#define GDMA_OUTFIFO_OVF_L1_CH0_INT_ST    (BIT(4))
#define GDMA_OUTFIFO_OVF_L1_CH0_INT_ST_M  (BIT(4))
#define GDMA_OUTFIFO_OVF_L1_CH0_INT_ST_V  0x1
#define GDMA_OUTFIFO_OVF_L1_CH0_INT_ST_S  4
/* GDMA_OUT_TOTAL_EOF_CH0_INT_ST:RO；位位置：[3]；默认值：1’b0；*/
/*description:OUT_TOTAL_EOF_CH_INT中断的原始中断状态位。。*/
#define GDMA_OUT_TOTAL_EOF_CH0_INT_ST    (BIT(3))
#define GDMA_OUT_TOTAL_EOF_CH0_INT_ST_M  (BIT(3))
#define GDMA_OUT_TOTAL_EOF_CH0_INT_ST_V  0x1
#define GDMA_OUT_TOTAL_EOF_CH0_INT_ST_S  3
/* GDMA_OUT_DSCR_ERR_CH0_INT_ST:RO；位位置：[2]；默认值：1’b0；*/
/*description:OUT_DSCR_ERR_CH_INT中断的原始中断状态位。。*/
#define GDMA_OUT_DSCR_ERR_CH0_INT_ST    (BIT(2))
#define GDMA_OUT_DSCR_ERR_CH0_INT_ST_M  (BIT(2))
#define GDMA_OUT_DSCR_ERR_CH0_INT_ST_V  0x1
#define GDMA_OUT_DSCR_ERR_CH0_INT_ST_S  2
/* GDMA_OUT_EOF_CH0_INT_ST:RO；位位置：[1]；默认值：1’b0；*/
/*description:OUT_EOF_CH_INT中断的原始中断状态位。。*/
#define GDMA_OUT_EOF_CH0_INT_ST    (BIT(1))
#define GDMA_OUT_EOF_CH0_INT_ST_M  (BIT(1))
#define GDMA_OUT_EOF_CH0_INT_ST_V  0x1
#define GDMA_OUT_EOF_CH0_INT_ST_S  1
/* GDMA_OUT_DONE_CH0_INT_ST:RO；位位置：[0]；默认值：1’b0；*/
/*description:OUT_DONE_CH_INT中断的原始中断状态位。。*/
#define GDMA_OUT_DONE_CH0_INT_ST    (BIT(0))
#define GDMA_OUT_DONE_CH0_INT_ST_M  (BIT(0))
#define GDMA_OUT_DONE_CH0_INT_ST_V  0x1
#define GDMA_OUT_DONE_CH0_INT_ST_S  0

#define GDMA_OUT_INT_ENA_CH0_REG          (DR_REG_GDMA_BASE + 0x70)
/* GDMA_OUTFIFO_UDF_13_CH0_INT_ENA:R/W；位位置：[7]；默认值：1’b0；*/
/*description:OUTFIFO_UDF_L3_CH_INT中断的中断启用位。。*/
#define GDMA_OUTFIFO_UDF_L3_CH0_INT_ENA    (BIT(7))
#define GDMA_OUTFIFO_UDF_L3_CH0_INT_ENA_M  (BIT(7))
#define GDMA_OUTFIFO_UDF_L3_CH0_INT_ENA_V  0x1
#define GDMA_OUTFIFO_UDF_L3_CH0_INT_ENA_S  7
/* GDMA_OUTFIFO_off_13_CH0_INT_ENA:R/W；位位置：[6]；默认值：1’b0；*/
/*description:OUTFIFO_OVF_L3_CH_INT中断的中断启用位。。*/
#define GDMA_OUTFIFO_OVF_L3_CH0_INT_ENA    (BIT(6))
#define GDMA_OUTFIFO_OVF_L3_CH0_INT_ENA_M  (BIT(6))
#define GDMA_OUTFIFO_OVF_L3_CH0_INT_ENA_V  0x1
#define GDMA_OUTFIFO_OVF_L3_CH0_INT_ENA_S  6
/* GDMA_OUTFIFO_UDF_L1_CH0_INT_ENA:R/W；位位置：[5]；默认值：1’b0；*/
/*description:OUTFIFO_UDF_L1_CH_INT中断的中断启用位。。*/
#define GDMA_OUTFIFO_UDF_L1_CH0_INT_ENA    (BIT(5))
#define GDMA_OUTFIFO_UDF_L1_CH0_INT_ENA_M  (BIT(5))
#define GDMA_OUTFIFO_UDF_L1_CH0_INT_ENA_V  0x1
#define GDMA_OUTFIFO_UDF_L1_CH0_INT_ENA_S  5
/* GDMA_OUTFIFO_off_L1_CH0_INT_ENA:R/W；位位置：[4]；默认值：1’b0；*/
/*description:OUTFIFO_OVF_L1_CH_INT中断的中断启用位。。*/
#define GDMA_OUTFIFO_OVF_L1_CH0_INT_ENA    (BIT(4))
#define GDMA_OUTFIFO_OVF_L1_CH0_INT_ENA_M  (BIT(4))
#define GDMA_OUTFIFO_OVF_L1_CH0_INT_ENA_V  0x1
#define GDMA_OUTFIFO_OVF_L1_CH0_INT_ENA_S  4
/* GDMA_OUT_TOTAL_EOF_CH0_INT_ENA:R/W；位位置：[3]；默认值：1’b0；*/
/*description:OUT_TOTAL_EOF_CH_INT中断的中断启用位。。*/
#define GDMA_OUT_TOTAL_EOF_CH0_INT_ENA    (BIT(3))
#define GDMA_OUT_TOTAL_EOF_CH0_INT_ENA_M  (BIT(3))
#define GDMA_OUT_TOTAL_EOF_CH0_INT_ENA_V  0x1
#define GDMA_OUT_TOTAL_EOF_CH0_INT_ENA_S  3
/* GDMA_OUT_DSCR_ERR_CH0_INT_ENA:R/W；位位置：[2]；默认值：1’b0；*/
/*description:OUT_DSCR_ERR_CH_INT中断的中断启用位。。*/
#define GDMA_OUT_DSCR_ERR_CH0_INT_ENA    (BIT(2))
#define GDMA_OUT_DSCR_ERR_CH0_INT_ENA_M  (BIT(2))
#define GDMA_OUT_DSCR_ERR_CH0_INT_ENA_V  0x1
#define GDMA_OUT_DSCR_ERR_CH0_INT_ENA_S  2
/* GDMA_OUT_EOF_CH0_INT_ENA:R/W；位位置：[1]；默认值：1’b0；*/
/*description:OUT_EOF_CH_INT中断的中断启用位。。*/
#define GDMA_OUT_EOF_CH0_INT_ENA    (BIT(1))
#define GDMA_OUT_EOF_CH0_INT_ENA_M  (BIT(1))
#define GDMA_OUT_EOF_CH0_INT_ENA_V  0x1
#define GDMA_OUT_EOF_CH0_INT_ENA_S  1
/* GDMA_OUT_DONE_CH0_INT_ENA:R/W；位位置：[0]；默认值：1’b0；*/
/*description:OUT_DONE_CH_INT中断的中断启用位。。*/
#define GDMA_OUT_DONE_CH0_INT_ENA    (BIT(0))
#define GDMA_OUT_DONE_CH0_INT_ENA_M  (BIT(0))
#define GDMA_OUT_DONE_CH0_INT_ENA_V  0x1
#define GDMA_OUT_DONE_CH0_INT_ENA_S  0

#define GDMA_OUT_INT_CLR_CH0_REG          (DR_REG_GDMA_BASE + 0x74)
/* GDMA_OUTFIFO_UDF_13_CH0_INT_CLR:WO；位位置：[7]；默认值：1’b0；*/
/*description:设置此位以清除OUTFIFO_UDF_L3_CH_INT中断。。*/
#define GDMA_OUTFIFO_UDF_L3_CH0_INT_CLR    (BIT(7))
#define GDMA_OUTFIFO_UDF_L3_CH0_INT_CLR_M  (BIT(7))
#define GDMA_OUTFIFO_UDF_L3_CH0_INT_CLR_V  0x1
#define GDMA_OUTFIFO_UDF_L3_CH0_INT_CLR_S  7
/* GDMA_OUTFIFO_off_13_CH0_INT_CLR:WO；位位置：[6]；默认值：1’b0；*/
/*description:设置此位以清除OUTFIFO_OVF_L3_CH_INT中断。。*/
#define GDMA_OUTFIFO_OVF_L3_CH0_INT_CLR    (BIT(6))
#define GDMA_OUTFIFO_OVF_L3_CH0_INT_CLR_M  (BIT(6))
#define GDMA_OUTFIFO_OVF_L3_CH0_INT_CLR_V  0x1
#define GDMA_OUTFIFO_OVF_L3_CH0_INT_CLR_S  6
/* GDMA_OUTFIFO_UDF_L1_CH0_INT_CLR:WO；位位置：[5]；默认值：1’b0；*/
/*description:设置此位以清除OUTFIFO_UDF_L1_CH_INT中断。。*/
#define GDMA_OUTFIFO_UDF_L1_CH0_INT_CLR    (BIT(5))
#define GDMA_OUTFIFO_UDF_L1_CH0_INT_CLR_M  (BIT(5))
#define GDMA_OUTFIFO_UDF_L1_CH0_INT_CLR_V  0x1
#define GDMA_OUTFIFO_UDF_L1_CH0_INT_CLR_S  5
/* GDMA_OUTFIFO_off_L1_CH0_INT_CLR:WO；位位置：[4]；默认值：1’b0；*/
/*description:设置此位以清除OUTFIFO_OVF_L1_CH_INT中断。。*/
#define GDMA_OUTFIFO_OVF_L1_CH0_INT_CLR    (BIT(4))
#define GDMA_OUTFIFO_OVF_L1_CH0_INT_CLR_M  (BIT(4))
#define GDMA_OUTFIFO_OVF_L1_CH0_INT_CLR_V  0x1
#define GDMA_OUTFIFO_OVF_L1_CH0_INT_CLR_S  4
/* GDMA_OUT_TOTAL_EOF_CH0_INT_CLR:WT；位位置：[3]；默认值：1’b0；*/
/*description:设置此位以清除OUT_TOTAL_EOF_CH_INT中断。。*/
#define GDMA_OUT_TOTAL_EOF_CH0_INT_CLR    (BIT(3))
#define GDMA_OUT_TOTAL_EOF_CH0_INT_CLR_M  (BIT(3))
#define GDMA_OUT_TOTAL_EOF_CH0_INT_CLR_V  0x1
#define GDMA_OUT_TOTAL_EOF_CH0_INT_CLR_S  3
/* GDMA_OUT_DSCR_ERR_CH0_INT_CLR:WT；位位置：[2]；默认值：1’b0；*/
/*description:设置此位以清除OUT_DSCR_ERR_CH_INT中断。。*/
#define GDMA_OUT_DSCR_ERR_CH0_INT_CLR    (BIT(2))
#define GDMA_OUT_DSCR_ERR_CH0_INT_CLR_M  (BIT(2))
#define GDMA_OUT_DSCR_ERR_CH0_INT_CLR_V  0x1
#define GDMA_OUT_DSCR_ERR_CH0_INT_CLR_S  2
/* GDMA_OUT_EOF_CH0_INT_CLR:WT；位位置：[1]；默认值：1’b0；*/
/*description:设置此位以清除OUT_EOF_CH_INT中断。。*/
#define GDMA_OUT_EOF_CH0_INT_CLR    (BIT(1))
#define GDMA_OUT_EOF_CH0_INT_CLR_M  (BIT(1))
#define GDMA_OUT_EOF_CH0_INT_CLR_V  0x1
#define GDMA_OUT_EOF_CH0_INT_CLR_S  1
/* GDMA_OUT_DONE_CH0_INT_CLR:WT；位位置：[0]；默认值：1’b0；*/
/*description:设置此位以清除OUT_DONE_CH_INT中断。。*/
#define GDMA_OUT_DONE_CH0_INT_CLR    (BIT(0))
#define GDMA_OUT_DONE_CH0_INT_CLR_M  (BIT(0))
#define GDMA_OUT_DONE_CH0_INT_CLR_V  0x1
#define GDMA_OUT_DONE_CH0_INT_CLR_S  0

#define GDMA_OUTFIFO_STATUS_CH0_REG          (DR_REG_GDMA_BASE + 0x78)
/* GDMA_OUT_REMAIN_UNDER_4B_L3_CH0:RO；位位置：[26]；默认值：1’b1；*/
/*description:保留。*/
#define GDMA_OUT_REMAIN_UNDER_4B_L3_CH0    (BIT(26))
#define GDMA_OUT_REMAIN_UNDER_4B_L3_CH0_M  (BIT(26))
#define GDMA_OUT_REMAIN_UNDER_4B_L3_CH0_V  0x1
#define GDMA_OUT_REMAIN_UNDER_4B_L3_CH0_S  26
/* GDMA_OUT_REMAIN_UNDER_3B_L3_CH0:RO；位位置：[25]；默认值：1’b1；*/
/*description:保留。*/
#define GDMA_OUT_REMAIN_UNDER_3B_L3_CH0    (BIT(25))
#define GDMA_OUT_REMAIN_UNDER_3B_L3_CH0_M  (BIT(25))
#define GDMA_OUT_REMAIN_UNDER_3B_L3_CH0_V  0x1
#define GDMA_OUT_REMAIN_UNDER_3B_L3_CH0_S  25
/* GDMA_OUT_REMAIN_UNDER_2B_L3_CH0:RO；位位置：[24]；默认值：1’b1；*/
/*description:保留。*/
#define GDMA_OUT_REMAIN_UNDER_2B_L3_CH0    (BIT(24))
#define GDMA_OUT_REMAIN_UNDER_2B_L3_CH0_M  (BIT(24))
#define GDMA_OUT_REMAIN_UNDER_2B_L3_CH0_V  0x1
#define GDMA_OUT_REMAIN_UNDER_2B_L3_CH0_S  24
/* GDMA_OUT_REMAIN_UNDER_1B_L3_CH0:RO；位位置：[23]；默认值：1’b1；*/
/*description:保留。*/
#define GDMA_OUT_REMAIN_UNDER_1B_L3_CH0    (BIT(23))
#define GDMA_OUT_REMAIN_UNDER_1B_L3_CH0_M  (BIT(23))
#define GDMA_OUT_REMAIN_UNDER_1B_L3_CH0_V  0x1
#define GDMA_OUT_REMAIN_UNDER_1B_L3_CH0_S  23
/* GDMA_OUTFIFO_CNT_L3_CH0:RO；比特位置：[22:18]；默认值：5’b0；*/
/*描述：寄存器将Tx信道0的L3 Tx FIFO中数据的字节数存储。。*/
#define GDMA_OUTFIFO_CNT_L3_CH0    0x0000001F
#define GDMA_OUTFIFO_CNT_L3_CH0_M  ((GDMA_OUTFIFO_CNT_L3_CH0_V)<<(GDMA_OUTFIFO_CNT_L3_CH0_S))
#define GDMA_OUTFIFO_CNT_L3_CH0_V  0x1F
#define GDMA_OUTFIFO_CNT_L3_CH0_S  18
/* GDMA_OUTFIFO_CNT_L2_CH0:RO；比特位置：[17:11]；默认值：7'b0；*/
/*描述：寄存器将数据的字节数存储在Tx信道0的L2 Tx FIFO中。。*/
#define GDMA_OUTFIFO_CNT_L2_CH0    0x0000007F
#define GDMA_OUTFIFO_CNT_L2_CH0_M  ((GDMA_OUTFIFO_CNT_L2_CH0_V)<<(GDMA_OUTFIFO_CNT_L2_CH0_S))
#define GDMA_OUTFIFO_CNT_L2_CH0_V  0x7F
#define GDMA_OUTFIFO_CNT_L2_CH0_S  11
/* GDMA_OUTFIFO_CNT_L1_CH0:RO；比特位置：[10:6]；默认值：5’b0；*/
/*描述：寄存器将Tx信道0的L1 Tx FIFO中的数据字节数存储。。*/
#define GDMA_OUTFIFO_CNT_L1_CH0    0x0000001F
#define GDMA_OUTFIFO_CNT_L1_CH0_M  ((GDMA_OUTFIFO_CNT_L1_CH0_V)<<(GDMA_OUTFIFO_CNT_L1_CH0_S))
#define GDMA_OUTFIFO_CNT_L1_CH0_V  0x1F
#define GDMA_OUTFIFO_CNT_L1_CH0_S  6
/* GDMA_OUTFIFO_EMPTY_L3_CH0:RO；位位置：[5]；默认值：1’b1；*/
/*描述：Tx信道0的L3 Tx FIFO空信号。。*/
#define GDMA_OUTFIFO_EMPTY_L3_CH0    (BIT(5))
#define GDMA_OUTFIFO_EMPTY_L3_CH0_M  (BIT(5))
#define GDMA_OUTFIFO_EMPTY_L3_CH0_V  0x1
#define GDMA_OUTFIFO_EMPTY_L3_CH0_S  5
/* GDMA_OUTFIFO_FULL_L3_CH0:RO；位位置：[4]；默认值：1’b0；*/
/*描述：Tx信道0的L3 Tx FIFO满信号。。*/
#define GDMA_OUTFIFO_FULL_L3_CH0    (BIT(4))
#define GDMA_OUTFIFO_FULL_L3_CH0_M  (BIT(4))
#define GDMA_OUTFIFO_FULL_L3_CH0_V  0x1
#define GDMA_OUTFIFO_FULL_L3_CH0_S  4
/* GDMA_OUTFIFO_EMPTY_L2_CH0:RO；位位置：[3]；默认值：1’b1；*/
/*描述：Tx信道0的L2 Tx FIFO空信号。。*/
#define GDMA_OUTFIFO_EMPTY_L2_CH0    (BIT(3))
#define GDMA_OUTFIFO_EMPTY_L2_CH0_M  (BIT(3))
#define GDMA_OUTFIFO_EMPTY_L2_CH0_V  0x1
#define GDMA_OUTFIFO_EMPTY_L2_CH0_S  3
/* GDMA_OUTFIFO_FULL_L2_CH0:RO；位位置：[2]；默认值：1’b0；*/
/*描述：Tx信道0的L2 Tx FIFO满信号。。*/
#define GDMA_OUTFIFO_FULL_L2_CH0    (BIT(2))
#define GDMA_OUTFIFO_FULL_L2_CH0_M  (BIT(2))
#define GDMA_OUTFIFO_FULL_L2_CH0_V  0x1
#define GDMA_OUTFIFO_FULL_L2_CH0_S  2
/* GDMA_OUTFIFO_EMPTY_L1_CH0:RO；位位置：[1]；默认值：1’b1；*/
/*描述：Tx信道0的L1 Tx FIFO空信号。。*/
#define GDMA_OUTFIFO_EMPTY_L1_CH0    (BIT(1))
#define GDMA_OUTFIFO_EMPTY_L1_CH0_M  (BIT(1))
#define GDMA_OUTFIFO_EMPTY_L1_CH0_V  0x1
#define GDMA_OUTFIFO_EMPTY_L1_CH0_S  1
/* GDMA_OUTFIFO_FULL_L1_CH0:RO；位位置：[0]；默认值：1’b0；*/
/*描述：Tx信道0的L1 Tx FIFO完整信号。。*/
#define GDMA_OUTFIFO_FULL_L1_CH0    (BIT(0))
#define GDMA_OUTFIFO_FULL_L1_CH0_M  (BIT(0))
#define GDMA_OUTFIFO_FULL_L1_CH0_V  0x1
#define GDMA_OUTFIFO_FULL_L1_CH0_S  0

#define GDMA_OUT_PUSH_CH0_REG          (DR_REG_GDMA_BASE + 0x7C)
/* GDMA_OUTFIFO_PUSH_CH0:R/W/SC；位位置：[9]；默认值：1'0；*/
/*description:设置此位以将数据推入DMA FIFO。。*/
#define GDMA_OUTFIFO_PUSH_CH0    (BIT(9))
#define GDMA_OUTFIFO_PUSH_CH0_M  (BIT(9))
#define GDMA_OUTFIFO_PUSH_CH0_V  0x1
#define GDMA_OUTFIFO_PUSH_CH0_S  9
/* GDMA_OUTFIFO_WDATA_CH0:R/W；位位置：[8:0]；默认值：9'0；*/
/*description:此寄存器存储需要推入DMA FIFO的数据。。*/
#define GDMA_OUTFIFO_WDATA_CH0    0x000001FF
#define GDMA_OUTFIFO_WDATA_CH0_M  ((GDMA_OUTFIFO_WDATA_CH0_V)<<(GDMA_OUTFIFO_WDATA_CH0_S))
#define GDMA_OUTFIFO_WDATA_CH0_V  0x1FF
#define GDMA_OUTFIFO_WDATA_CH0_S  0

#define GDMA_OUT_LINK_CH0_REG          (DR_REG_GDMA_BASE + 0x80)
/* GDMA_OUTLINK_PARK_CH0:RO；位位置：[23]；默认值：1'h1；*/
/*描述：1:outlink描述符的FSM处于空闲状态。0:outlink描述符的FSM正在工作。。*/
#define GDMA_OUTLINK_PARK_CH0    (BIT(23))
#define GDMA_OUTLINK_PARK_CH0_M  (BIT(23))
#define GDMA_OUTLINK_PARK_CH0_V  0x1
#define GDMA_OUTLINK_PARK_CH0_S  23
/* GDMA_OUTLINK_RESTART_CH0:R/W/SC；位位置：[22]；默认值：1’b0；*/
/*description:设置此位以从上一个地址重新启动新的outlink。*/
#define GDMA_OUTLINK_RESTART_CH0    (BIT(22))
#define GDMA_OUTLINK_RESTART_CH0_M  (BIT(22))
#define GDMA_OUTLINK_RESTART_CH0_V  0x1
#define GDMA_OUTLINK_RESTART_CH0_S  22
/* GDMA_OUTLINK_START_CH0:R/W/SC；位位置：[21]；默认值：1’b0；*/
/*description:设置此位以开始处理outlink描述符。。*/
#define GDMA_OUTLINK_START_CH0    (BIT(21))
#define GDMA_OUTLINK_START_CH0_M  (BIT(21))
#define GDMA_OUTLINK_START_CH0_V  0x1
#define GDMA_OUTLINK_START_CH0_S  21
/* GDMA_OUTLINK_STOP_CH0:R/W/SC；位位置：[20]；默认值：1’b0；*/
/*description:设置此位以停止处理outlink描述符。。*/
#define GDMA_OUTLINK_STOP_CH0    (BIT(20))
#define GDMA_OUTLINK_STOP_CH0_M  (BIT(20))
#define GDMA_OUTLINK_STOP_CH0_V  0x1
#define GDMA_OUTLINK_STOP_CH0_S  20
/* GDMA_OUTLINK_ADDR_CH0:R/W；比特位置：[19:0]；默认值：20'00；*/
/*description:此寄存器存储第一个outlink描述符地址的20个最低有效位。。*/
#define GDMA_OUTLINK_ADDR_CH0    0x000FFFFF
#define GDMA_OUTLINK_ADDR_CH0_M  ((GDMA_OUTLINK_ADDR_CH0_V)<<(GDMA_OUTLINK_ADDR_CH0_S))
#define GDMA_OUTLINK_ADDR_CH0_V  0xFFFFF
#define GDMA_OUTLINK_ADDR_CH0_S  0

#define GDMA_OUT_STATE_CH0_REG          (DR_REG_GDMA_BASE + 0x84)
/* GDMA_OUT_STATE_CH0:RO；比特位置：[22:20]；默认值：3'b0；*/
/*description:保留。*/
#define GDMA_OUT_STATE_CH0    0x00000007
#define GDMA_OUT_STATE_CH0_M  ((GDMA_OUT_STATE_CH0_V)<<(GDMA_OUT_STATE_CH0_S))
#define GDMA_OUT_STATE_CH0_V  0x7
#define GDMA_OUT_STATE_CH0_S  20
/* GDMA_OUT_DSCR_STATE_CH0:RO；比特位置：[19:18]；默认值：2’b0；*/
/*description:保留。*/
#define GDMA_OUT_DSCR_STATE_CH0    0x00000003
#define GDMA_OUT_DSCR_STATE_CH0_M  ((GDMA_OUT_DSCR_STATE_CH0_V)<<(GDMA_OUT_DSCR_STATE_CH0_S))
#define GDMA_OUT_DSCR_STATE_CH0_V  0x3
#define GDMA_OUT_DSCR_STATE_CH0_S  18
/* GDMA_OUTLINK_DSCR_ADDR_CH0:RO；比特位置：[17:00]；默认值：18'b0；*/
/*description:此寄存器存储当前outlink描述符的地址。。*/
#define GDMA_OUTLINK_DSCR_ADDR_CH0    0x0003FFFF
#define GDMA_OUTLINK_DSCR_ADDR_CH0_M  ((GDMA_OUTLINK_DSCR_ADDR_CH0_V)<<(GDMA_OUTLINK_DSCR_ADDR_CH0_S))
#define GDMA_OUTLINK_DSCR_ADDR_CH0_V  0x3FFFF
#define GDMA_OUTLINK_DSCR_ADDR_CH0_S  0

#define GDMA_OUT_EOF_DES_ADDR_CH0_REG          (DR_REG_GDMA_BASE + 0x88)
/* GDMA_OUT_EOF_DES_ADDR_CH0:RO；位位置：[31:0]；默认值：32'h0；*/
/*description:当此描述符中的EOF位为1时，此寄存器存储outlink描述符的地址。。*/
#define GDMA_OUT_EOF_DES_ADDR_CH0    0xFFFFFFFF
#define GDMA_OUT_EOF_DES_ADDR_CH0_M  ((GDMA_OUT_EOF_DES_ADDR_CH0_V)<<(GDMA_OUT_EOF_DES_ADDR_CH0_S))
#define GDMA_OUT_EOF_DES_ADDR_CH0_V  0xFFFFFFFF
#define GDMA_OUT_EOF_DES_ADDR_CH0_S  0

#define GDMA_OUT_EOF_BFR_DES_ADDR_CH0_REG          (DR_REG_GDMA_BASE + 0x8C)
/* GDMA_OUT_EOF_BFR_DES_ADDR_CH0:RO；位位置：[31:0]；默认值：32'h0；*/
/*description:此寄存器存储最后一个outlink描述符之前的outlink描述符的地址。。*/
#define GDMA_OUT_EOF_BFR_DES_ADDR_CH0    0xFFFFFFFF
#define GDMA_OUT_EOF_BFR_DES_ADDR_CH0_M  ((GDMA_OUT_EOF_BFR_DES_ADDR_CH0_V)<<(GDMA_OUT_EOF_BFR_DES_ADDR_CH0_S))
#define GDMA_OUT_EOF_BFR_DES_ADDR_CH0_V  0xFFFFFFFF
#define GDMA_OUT_EOF_BFR_DES_ADDR_CH0_S  0

#define GDMA_OUT_DSCR_CH0_REG          (DR_REG_GDMA_BASE + 0x90)
/* GDMA_OUTLINK_DSCR_CH0:RO；位位置：[31:0]；默认值：32'b0；*/
/*description:当前outlink描述符y的地址。。*/
#define GDMA_OUTLINK_DSCR_CH0    0xFFFFFFFF
#define GDMA_OUTLINK_DSCR_CH0_M  ((GDMA_OUTLINK_DSCR_CH0_V)<<(GDMA_OUTLINK_DSCR_CH0_S))
#define GDMA_OUTLINK_DSCR_CH0_V  0xFFFFFFFF
#define GDMA_OUTLINK_DSCR_CH0_S  0

#define GDMA_OUT_DSCR_BF0_CH0_REG          (DR_REG_GDMA_BASE + 0x94)
/* GDMA_OUTLINK_DSCR_BF0_CH0:RO；位位置：[31:0]；默认值：32'b0；*/
/*description:最后一个outlink描述符的地址y-1。。*/
#define GDMA_OUTLINK_DSCR_BF0_CH0    0xFFFFFFFF
#define GDMA_OUTLINK_DSCR_BF0_CH0_M  ((GDMA_OUTLINK_DSCR_BF0_CH0_V)<<(GDMA_OUTLINK_DSCR_BF0_CH0_S))
#define GDMA_OUTLINK_DSCR_BF0_CH0_V  0xFFFFFFFF
#define GDMA_OUTLINK_DSCR_BF0_CH0_S  0

#define GDMA_OUT_DSCR_BF1_CH0_REG          (DR_REG_GDMA_BASE + 0x98)
/* GDMA_OUTLINK_DSCR_BF1_CH0:RO；位位置：[31:0]；默认值：32'b0；*/
/*description:倒数第二个内联描述符x-2的地址。。*/
#define GDMA_OUTLINK_DSCR_BF1_CH0    0xFFFFFFFF
#define GDMA_OUTLINK_DSCR_BF1_CH0_M  ((GDMA_OUTLINK_DSCR_BF1_CH0_V)<<(GDMA_OUTLINK_DSCR_BF1_CH0_S))
#define GDMA_OUTLINK_DSCR_BF1_CH0_V  0xFFFFFFFF
#define GDMA_OUTLINK_DSCR_BF1_CH0_S  0

#define GDMA_OUT_WIGHT_CH0_REG          (DR_REG_GDMA_BASE + 0x9C)
/* GDMA_TX_WEIGHT_CH0:R/W；位位置：[11:8]；默认值：4'hf；*/
/*description:Tx信道的权重0。*/
#define GDMA_TX_WEIGHT_CH0    0x0000000F
#define GDMA_TX_WEIGHT_CH0_M  ((GDMA_TX_WEIGHT_CH0_V)<<(GDMA_TX_WEIGHT_CH0_S))
#define GDMA_TX_WEIGHT_CH0_V  0xF
#define GDMA_TX_WEIGHT_CH0_S  8

#define GDMA_OUT_PRI_CH0_REG          (DR_REG_GDMA_BASE + 0xA4)
/* GDMA_TX_PRI_CH0:R/W；位位置：[3:0]；默认值：4'b0；*/
/*description:Tx信道0的优先级。值越大，优先级越高。。*/
#define GDMA_TX_PRI_CH0    0x0000000F
#define GDMA_TX_PRI_CH0_M  ((GDMA_TX_PRI_CH0_V)<<(GDMA_TX_PRI_CH0_S))
#define GDMA_TX_PRI_CH0_V  0xF
#define GDMA_TX_PRI_CH0_S  0

#define GDMA_OUT_PERI_SEL_CH0_REG          (DR_REG_GDMA_BASE + 0xA8)
/* GDMA_PERI_OUT_SEL_CH0:R/W；比特位置：[5:0]；默认值：6'h3f；*/
/*描述：此寄存器用于为Tx信道选择外设。0:SPI2.1:SPI3.2:UHCI0.3:I2S0.4:I2S1.5:LCD_CAM。6： AES。7： 沙。8： ADC_DAC。9： 每立方米。；7： AES。8： 沙。9： ADC_DAC。。*/
#define GDMA_PERI_OUT_SEL_CH0    0x0000003F
#define GDMA_PERI_OUT_SEL_CH0_M  ((GDMA_PERI_OUT_SEL_CH0_V)<<(GDMA_PERI_OUT_SEL_CH0_S))
#define GDMA_PERI_OUT_SEL_CH0_V  0x3F
#define GDMA_PERI_OUT_SEL_CH0_S  0

#define GDMA_IN_CONF0_CH1_REG          (DR_REG_GDMA_BASE + 0xC0)
/* GDMA_MEM_TRANS_EN_CH1:R/W；位位置：[4]；默认值：1’b0；*/
/*description:将此位设置为1，以启用通过DMA将数据从存储器自动传输到存储器。。*/
#define GDMA_MEM_TRANS_EN_CH1    (BIT(4))
#define GDMA_MEM_TRANS_EN_CH1_M  (BIT(4))
#define GDMA_MEM_TRANS_EN_CH1_V  0x1
#define GDMA_MEM_TRANS_EN_CH1_S  4
/* GDMA_IN_DATA_BURST_EN_CH1:R/W；位位置：[3]；默认值：1’b0；*/
/*description:将此位设置为1，以在访问内部SRAM时启用接收数据的Rx通道1的INCR突发传输。*/
#define GDMA_IN_DATA_BURST_EN_CH1    (BIT(3))
#define GDMA_IN_DATA_BURST_EN_CH1_M  (BIT(3))
#define GDMA_IN_DATA_BURST_EN_CH1_V  0x1
#define GDMA_IN_DATA_BURST_EN_CH1_S  3
/* GDMA_INDSCR_BURST_EN_CH1:R/W；位位置：[2]；默认值：1’b0；*/
/*description:当访问内部SRAM时，将此位设置为1以启用Rx通道1读取链路描述符的INCR突发传输。*/
#define GDMA_INDSCR_BURST_EN_CH1    (BIT(2))
#define GDMA_INDSCR_BURST_EN_CH1_M  (BIT(2))
#define GDMA_INDSCR_BURST_EN_CH1_V  0x1
#define GDMA_INDSCR_BURST_EN_CH1_S  2
/* GDMA_IN_LOOP_TEST_CH1:R/W；位位置：[1]；默认值：1’b0；*/
/*description:保留。*/
#define GDMA_IN_LOOP_TEST_CH1    (BIT(1))
#define GDMA_IN_LOOP_TEST_CH1_M  (BIT(1))
#define GDMA_IN_LOOP_TEST_CH1_V  0x1
#define GDMA_IN_LOOP_TEST_CH1_S  1
/* GDMA_IN_RST_CH1:R/W；位位置：[0]；默认值：1'0；*/
/*描述：此位用于重置DMA通道1 Rx FSM和Rx FIFO指针。。*/
#define GDMA_IN_RST_CH1    (BIT(0))
#define GDMA_IN_RST_CH1_M  (BIT(0))
#define GDMA_IN_RST_CH1_V  0x1
#define GDMA_IN_RST_CH1_S  0

#define GDMA_IN_CONF1_CH1_REG          (DR_REG_GDMA_BASE + 0xC4)
/* GDMA_IN_EXT_MEM_BK_SIZE_CH1:R/W；比特位置：[14:13]；默认值：2’b0；*/
/*描述：DMA访问外部SRAM时Rx通道1的块大小。0:16字节1:32字节2/3:保留。*/
#define GDMA_IN_EXT_MEM_BK_SIZE_CH1    0x00000003
#define GDMA_IN_EXT_MEM_BK_SIZE_CH1_M  ((GDMA_IN_EXT_MEM_BK_SIZE_CH1_V)<<(GDMA_IN_EXT_MEM_BK_SIZE_CH1_S))
#define GDMA_IN_EXT_MEM_BK_SIZE_CH1_V  0x3
#define GDMA_IN_EXT_MEM_BK_SIZE_CH1_S  13
/* GDMA_IN_CHECK_OWNER_CH1:R/W；位位置：[12]；默认值：1’b0；*/
/*description:设置此位以启用检查链接描述符的所有者属性。。*/
#define GDMA_IN_CHECK_OWNER_CH1    (BIT(12))
#define GDMA_IN_CHECK_OWNER_CH1_M  (BIT(12))
#define GDMA_IN_CHECK_OWNER_CH1_V  0x1
#define GDMA_IN_CHECK_OWNER_CH1_S  12
/* GDMA_DMA_INFIFO_FULL_THRS_CH1:R/W；位位置：[11:0]；默认值：12'hc；*/
/*描述：当Rx FIFO中的Rx通道0接收字节数达到寄存器值时，此寄存器用于生成INFIFO_FULL_WM_INT中断。。*/
#define GDMA_DMA_INFIFO_FULL_THRS_CH1    0x00000FFF
#define GDMA_DMA_INFIFO_FULL_THRS_CH1_M  ((GDMA_DMA_INFIFO_FULL_THRS_CH1_V)<<(GDMA_DMA_INFIFO_FULL_THRS_CH1_S))
#define GDMA_DMA_INFIFO_FULL_THRS_CH1_V  0xFFF
#define GDMA_DMA_INFIFO_FULL_THRS_CH1_S  0

#define GDMA_IN_INT_RAW_CH1_REG          (DR_REG_GDMA_BASE + 0xC8)
/* GDMA_INFIFO_UDF_13_CH1_INT_RAW:R/WTC/SS；位位置：[9]；默认值：1’b0；*/
/*描述：当Rx通道1的第3级fifo未满流时，此原始中断位变为高电平。*/
#define GDMA_INFIFO_UDF_L3_CH1_INT_RAW    (BIT(9))
#define GDMA_INFIFO_UDF_L3_CH1_INT_RAW_M  (BIT(9))
#define GDMA_INFIFO_UDF_L3_CH1_INT_RAW_V  0x1
#define GDMA_INFIFO_UDF_L3_CH1_INT_RAW_S  9
/* GDMA_INFIFO_off_L3_CH1_INT_RAW:R/WTC/SS；位位置：[8]；默认值：1’b0；*/
/*描述：当Rx通道1的3级fifo等流量时，此原始中断位变为高电平。*/
#define GDMA_INFIFO_OVF_L3_CH1_INT_RAW    (BIT(8))
#define GDMA_INFIFO_OVF_L3_CH1_INT_RAW_M  (BIT(8))
#define GDMA_INFIFO_OVF_L3_CH1_INT_RAW_V  0x1
#define GDMA_INFIFO_OVF_L3_CH1_INT_RAW_S  8
/* GDMA_INFIFO_UDF_l_CH1_INT_RAW:R/WTC/SS；位位置：[7]；默认值：1’b0；*/
/*描述：当Rx通道1的第1级fifo未满流时，此原始中断位变为高电平。*/
#define GDMA_INFIFO_UDF_L1_CH1_INT_RAW    (BIT(7))
#define GDMA_INFIFO_UDF_L1_CH1_INT_RAW_M  (BIT(7))
#define GDMA_INFIFO_UDF_L1_CH1_INT_RAW_V  0x1
#define GDMA_INFIFO_UDF_L1_CH1_INT_RAW_S  7
/* GDMA_INFIFO_OVF_l_CH1_INT_RAW:R/WTC/SS；位位置：[6]；默认值：1’b0；*/
/*描述：当Rx通道1的1级fifo等流量时，此原始中断位变为高电平。*/
#define GDMA_INFIFO_OVF_L1_CH1_INT_RAW    (BIT(6))
#define GDMA_INFIFO_OVF_L1_CH1_INT_RAW_M  (BIT(6))
#define GDMA_INFIFO_OVF_L1_CH1_INT_RAW_V  0x1
#define GDMA_INFIFO_OVF_L1_CH1_INT_RAW_S  6
/* GDMA_INFIFO_FULL_WM_CH1_INT_RAW:R/WTC/SS；位位置：[5]；默认值：1’b0；*/
/*描述：当接收的数据字节数达到信道1的Rx FIFO中REG_DMA_INFIFO_FULL_THS_CH0配置的阈值时，原始中断位变为高电平。。*/
#define GDMA_INFIFO_FULL_WM_CH1_INT_RAW    (BIT(5))
#define GDMA_INFIFO_FULL_WM_CH1_INT_RAW_M  (BIT(5))
#define GDMA_INFIFO_FULL_WM_CH1_INT_RAW_V  0x1
#define GDMA_INFIFO_FULL_WM_CH1_INT_RAW_S  5
/* GDMA_IN_DSCR_EMPTY-CH1_INT_RAW:R/WTC/SS；位位置：[4]；默认值：1’b0；*/
/*描述：当inlink指向的Rx缓冲区已满且未完成接收数据时，原始中断位变为高电平，但Rx通道1没有更多的inlink。。*/
#define GDMA_IN_DSCR_EMPTY_CH1_INT_RAW    (BIT(4))
#define GDMA_IN_DSCR_EMPTY_CH1_INT_RAW_M  (BIT(4))
#define GDMA_IN_DSCR_EMPTY_CH1_INT_RAW_V  0x1
#define GDMA_IN_DSCR_EMPTY_CH1_INT_RAW_S  4
/* GDMA_IN_DSCR_ERR_CH1_INT_RAW:R/WTC/SS；位位置：[3]；默认值：1’b0；*/
/*描述：当检测到内联描述符错误时，原始中断位变为高电平，包括所有者错误、Rx通道1的内联描述符的第二个和第三个字错误。。*/
#define GDMA_IN_DSCR_ERR_CH1_INT_RAW    (BIT(3))
#define GDMA_IN_DSCR_ERR_CH1_INT_RAW_M  (BIT(3))
#define GDMA_IN_DSCR_ERR_CH1_INT_RAW_V  0x1
#define GDMA_IN_DSCR_ERR_CH1_INT_RAW_S  3
/* GDMA_IN_ERR_EOF_CH1_INT_RAW:R/WTC/SS；位位置：[2]；默认值：1’b0；*/
/*描述：仅当外围设备为Rx通道1的UHCI0时，检测到数据错误时，原始中断位变为高电平。对于其他外围设备，保留此原始中断。。*/
#define GDMA_IN_ERR_EOF_CH1_INT_RAW    (BIT(2))
#define GDMA_IN_ERR_EOF_CH1_INT_RAW_M  (BIT(2))
#define GDMA_IN_ERR_EOF_CH1_INT_RAW_V  0x1
#define GDMA_IN_ERR_EOF_CH1_INT_RAW_S  2
/* GDMA_IN_SUC_EOF_CH1_INT_RAW:R/WTC/SS；位位置：[1]；默认值：1’b0；*/
/*描述：当接收到Rx通道1的一个内联描述符指向的最后一个数据时，原始中断位变为高电平。对于UHCI0，当接收到一个内联描述符指向的最后数据且Rx通道0未检测到数据错误时，原始断开位变为低电平。。*/
#define GDMA_IN_SUC_EOF_CH1_INT_RAW    (BIT(1))
#define GDMA_IN_SUC_EOF_CH1_INT_RAW_M  (BIT(1))
#define GDMA_IN_SUC_EOF_CH1_INT_RAW_V  0x1
#define GDMA_IN_SUC_EOF_CH1_INT_RAW_S  1
/* GDMA_IN_DONE_CH1_INT_RAW:R/WTC/SS；位位置：[0]；默认值：1’b0；*/
/*描述：当接收到Rx通道1的一个内联描述符所指向的最后一个数据时，原始中断位变为高电平。。*/
#define GDMA_IN_DONE_CH1_INT_RAW    (BIT(0))
#define GDMA_IN_DONE_CH1_INT_RAW_M  (BIT(0))
#define GDMA_IN_DONE_CH1_INT_RAW_V  0x1
#define GDMA_IN_DONE_CH1_INT_RAW_S  0

#define GDMA_IN_INT_ST_CH1_REG          (DR_REG_GDMA_BASE + 0xCC)
/* GDMA_INFIFO_udfl3_CH1_INT_ST:RO；位位置：[9]；默认值：1’b0；*/
/*description:INFIFO_UDF_L3_CH_INT中断的原始中断状态位。。*/
#define GDMA_INFIFO_UDF_L3_CH1_INT_ST    (BIT(9))
#define GDMA_INFIFO_UDF_L3_CH1_INT_ST_M  (BIT(9))
#define GDMA_INFIFO_UDF_L3_CH1_INT_ST_V  0x1
#define GDMA_INFIFO_UDF_L3_CH1_INT_ST_S  9
/* GDMA_INFIFO_off_13_CH1_INT_ST:RO；位位置：[8]；默认值：1’b0；*/
/*description:INFIFO_OVF_L3_CH_INT中断的原始中断状态位。。*/
#define GDMA_INFIFO_OVF_L3_CH1_INT_ST    (BIT(8))
#define GDMA_INFIFO_OVF_L3_CH1_INT_ST_M  (BIT(8))
#define GDMA_INFIFO_OVF_L3_CH1_INT_ST_V  0x1
#define GDMA_INFIFO_OVF_L3_CH1_INT_ST_S  8
/* GDMA_INFIFO_UDF_1_CH1_INT_ST:RO；位位置：[7]；默认值：1’b0；*/
/*description:INFIFO_UDF_L1_CH_INT中断的原始中断状态位。。*/
#define GDMA_INFIFO_UDF_L1_CH1_INT_ST    (BIT(7))
#define GDMA_INFIFO_UDF_L1_CH1_INT_ST_M  (BIT(7))
#define GDMA_INFIFO_UDF_L1_CH1_INT_ST_V  0x1
#define GDMA_INFIFO_UDF_L1_CH1_INT_ST_S  7
/* GDMA_INFIFO_OVF_l_CH1_INT_ST:RO；位位置：[6]；默认值：1’b0；*/
/*description:INFIFO_OVF_L1_CH_INT中断的原始中断状态位。。*/
#define GDMA_INFIFO_OVF_L1_CH1_INT_ST    (BIT(6))
#define GDMA_INFIFO_OVF_L1_CH1_INT_ST_M  (BIT(6))
#define GDMA_INFIFO_OVF_L1_CH1_INT_ST_V  0x1
#define GDMA_INFIFO_OVF_L1_CH1_INT_ST_S  6
/* GDMA_INFIFO_FULL_WM_CH1_INT_ST:RO；位位置：[5]；默认值：1’b0；*/
/*description:INFIFO_FULL_WM_CH_INT中断的原始中断状态位。。*/
#define GDMA_INFIFO_FULL_WM_CH1_INT_ST    (BIT(5))
#define GDMA_INFIFO_FULL_WM_CH1_INT_ST_M  (BIT(5))
#define GDMA_INFIFO_FULL_WM_CH1_INT_ST_V  0x1
#define GDMA_INFIFO_FULL_WM_CH1_INT_ST_S  5
/* GDMA_IN_DSCR_EMPTY-CH1_INT_ST:RO；位位置：[4]；默认值：1’b0；*/
/*description:IN_DSCR_EMPTY_CH_INT中断的原始中断状态位。。*/
#define GDMA_IN_DSCR_EMPTY_CH1_INT_ST    (BIT(4))
#define GDMA_IN_DSCR_EMPTY_CH1_INT_ST_M  (BIT(4))
#define GDMA_IN_DSCR_EMPTY_CH1_INT_ST_V  0x1
#define GDMA_IN_DSCR_EMPTY_CH1_INT_ST_S  4
/* GDMA_IN_DSCR_ERR_CH1_INT_ST:RO；位位置：[3]；默认值：1’b0；*/
/*description:IN_DSCR_ERR_CH_INT中断的原始中断状态位。。*/
#define GDMA_IN_DSCR_ERR_CH1_INT_ST    (BIT(3))
#define GDMA_IN_DSCR_ERR_CH1_INT_ST_M  (BIT(3))
#define GDMA_IN_DSCR_ERR_CH1_INT_ST_V  0x1
#define GDMA_IN_DSCR_ERR_CH1_INT_ST_S  3
/* GDMA_IN_ERR_EOF_CH1_INT_ST:RO；位位置：[2]；默认值：1’b0；*/
/*description:IN_ERR_EOF_CH_INT中断的原始中断状态位。。*/
#define GDMA_IN_ERR_EOF_CH1_INT_ST    (BIT(2))
#define GDMA_IN_ERR_EOF_CH1_INT_ST_M  (BIT(2))
#define GDMA_IN_ERR_EOF_CH1_INT_ST_V  0x1
#define GDMA_IN_ERR_EOF_CH1_INT_ST_S  2
/* GDMA_IN_SUC_EOF_CH1_INT_ST:RO；位位置：[1]；默认值：1’b0；*/
/*description:IN_SUC_EOF_CH_INT中断的原始中断状态位。。*/
#define GDMA_IN_SUC_EOF_CH1_INT_ST    (BIT(1))
#define GDMA_IN_SUC_EOF_CH1_INT_ST_M  (BIT(1))
#define GDMA_IN_SUC_EOF_CH1_INT_ST_V  0x1
#define GDMA_IN_SUC_EOF_CH1_INT_ST_S  1
/* GDMA_IN_DONE_CH1_INT_ST:RO；位位置：[0]；默认值：1’b0；*/
/*description:IN_DONE_CH_INT中断的原始中断状态位。。*/
#define GDMA_IN_DONE_CH1_INT_ST    (BIT(0))
#define GDMA_IN_DONE_CH1_INT_ST_M  (BIT(0))
#define GDMA_IN_DONE_CH1_INT_ST_V  0x1
#define GDMA_IN_DONE_CH1_INT_ST_S  0

#define GDMA_IN_INT_ENA_CH1_REG          (DR_REG_GDMA_BASE + 0xD0)
/* GDMA_INFIFO_UDF_13_CH1_INT_ENA:R/W；位位置：[9]；默认值：1’b0；*/
/*description:INFIFO_UDF_L3_CH_INT中断的中断启用位。。*/
#define GDMA_INFIFO_UDF_L3_CH1_INT_ENA    (BIT(9))
#define GDMA_INFIFO_UDF_L3_CH1_INT_ENA_M  (BIT(9))
#define GDMA_INFIFO_UDF_L3_CH1_INT_ENA_V  0x1
#define GDMA_INFIFO_UDF_L3_CH1_INT_ENA_S  9
/* GDMA_INFIFO_off_13_CH1_INT_ENA:R/W；位位置：[8]；默认值：1’b0；*/
/*description:INFIFO_OVF_L3_CH_INT中断的中断启用位。。*/
#define GDMA_INFIFO_OVF_L3_CH1_INT_ENA    (BIT(8))
#define GDMA_INFIFO_OVF_L3_CH1_INT_ENA_M  (BIT(8))
#define GDMA_INFIFO_OVF_L3_CH1_INT_ENA_V  0x1
#define GDMA_INFIFO_OVF_L3_CH1_INT_ENA_S  8
/* GDMA_INFIFO_UDF_1_CH1_INT_ENA:R/W；位位置：[7]；默认值：1’b0；*/
/*description:INFIFO_UDF_L1_CH_INT中断的中断启用位。。*/
#define GDMA_INFIFO_UDF_L1_CH1_INT_ENA    (BIT(7))
#define GDMA_INFIFO_UDF_L1_CH1_INT_ENA_M  (BIT(7))
#define GDMA_INFIFO_UDF_L1_CH1_INT_ENA_V  0x1
#define GDMA_INFIFO_UDF_L1_CH1_INT_ENA_S  7
/* GDMA_INFIFO_OVF_l_CH1_INT_ENA:R/W；位位置：[6]；默认值：1’b0；*/
/*description:INFIFO_OVF_L1_CH_INT中断的中断启用位。。*/
#define GDMA_INFIFO_OVF_L1_CH1_INT_ENA    (BIT(6))
#define GDMA_INFIFO_OVF_L1_CH1_INT_ENA_M  (BIT(6))
#define GDMA_INFIFO_OVF_L1_CH1_INT_ENA_V  0x1
#define GDMA_INFIFO_OVF_L1_CH1_INT_ENA_S  6
/* GDMA_INFIFO_FULL_WM_CH1_INT_ENA:R/W；位位置：[5]；默认值：1’b0；*/
/*description:INFIFO_FULL_WM_CH_INT中断的中断启用位。。*/
#define GDMA_INFIFO_FULL_WM_CH1_INT_ENA    (BIT(5))
#define GDMA_INFIFO_FULL_WM_CH1_INT_ENA_M  (BIT(5))
#define GDMA_INFIFO_FULL_WM_CH1_INT_ENA_V  0x1
#define GDMA_INFIFO_FULL_WM_CH1_INT_ENA_S  5
/* GDMA_IN_DSCR_EMPTY-CH1_INT_ENA:R/W；位位置：[4]；默认值：1’b0；*/
/*description:IN_DSCR_EMPTY_CH_INT中断的中断启用位。。*/
#define GDMA_IN_DSCR_EMPTY_CH1_INT_ENA    (BIT(4))
#define GDMA_IN_DSCR_EMPTY_CH1_INT_ENA_M  (BIT(4))
#define GDMA_IN_DSCR_EMPTY_CH1_INT_ENA_V  0x1
#define GDMA_IN_DSCR_EMPTY_CH1_INT_ENA_S  4
/* GDMA_IN_DSCR_ERR_CH1_INT_ENA:R/W；位位置：[3]；默认值：1’b0；*/
/*description:IN_DSCR_ERR_CH_INT中断的中断启用位。。*/
#define GDMA_IN_DSCR_ERR_CH1_INT_ENA    (BIT(3))
#define GDMA_IN_DSCR_ERR_CH1_INT_ENA_M  (BIT(3))
#define GDMA_IN_DSCR_ERR_CH1_INT_ENA_V  0x1
#define GDMA_IN_DSCR_ERR_CH1_INT_ENA_S  3
/* GDMA_IN_ERR_EOF_CH1_INT_ENA:R/W；位位置：[2]；默认值：1’b0；*/
/*description:IN_ERR_EOF_CH_INT中断的中断启用位。。*/
#define GDMA_IN_ERR_EOF_CH1_INT_ENA    (BIT(2))
#define GDMA_IN_ERR_EOF_CH1_INT_ENA_M  (BIT(2))
#define GDMA_IN_ERR_EOF_CH1_INT_ENA_V  0x1
#define GDMA_IN_ERR_EOF_CH1_INT_ENA_S  2
/* GDMA_IN_SUC_EOF_CH1_INT_ENA:R/W；位位置：[1]；默认值：1’b0；*/
/*description:IN_SUC_EOF_CH_INT中断的中断启用位。。*/
#define GDMA_IN_SUC_EOF_CH1_INT_ENA    (BIT(1))
#define GDMA_IN_SUC_EOF_CH1_INT_ENA_M  (BIT(1))
#define GDMA_IN_SUC_EOF_CH1_INT_ENA_V  0x1
#define GDMA_IN_SUC_EOF_CH1_INT_ENA_S  1
/* GDMA_IN_DONE_CH1_INT_ENA:R/W；位位置：[0]；默认值：1’b0；*/
/*description:IN_DONE_CH_INT中断的中断启用位。。*/
#define GDMA_IN_DONE_CH1_INT_ENA    (BIT(0))
#define GDMA_IN_DONE_CH1_INT_ENA_M  (BIT(0))
#define GDMA_IN_DONE_CH1_INT_ENA_V  0x1
#define GDMA_IN_DONE_CH1_INT_ENA_S  0

#define GDMA_IN_INT_CLR_CH1_REG          (DR_REG_GDMA_BASE + 0xD4)
/* GDMA_INFIFO_udfl3_CH1_INT_CLR:WT；位位置：[9]；默认值：1’b0；*/
/*description:设置此位以清除INFIFO_UDF_L3_CH_INT中断。。*/
#define GDMA_INFIFO_UDF_L3_CH1_INT_CLR    (BIT(9))
#define GDMA_INFIFO_UDF_L3_CH1_INT_CLR_M  (BIT(9))
#define GDMA_INFIFO_UDF_L3_CH1_INT_CLR_V  0x1
#define GDMA_INFIFO_UDF_L3_CH1_INT_CLR_S  9
/* GDMA_INFIFO_off_13_CH1_INT_CLR:WT；位位置：[8]；默认值：1’b0；*/
/*description:设置此位以清除INFIFO_OVF_L3_CH_INT中断。。*/
#define GDMA_INFIFO_OVF_L3_CH1_INT_CLR    (BIT(8))
#define GDMA_INFIFO_OVF_L3_CH1_INT_CLR_M  (BIT(8))
#define GDMA_INFIFO_OVF_L3_CH1_INT_CLR_V  0x1
#define GDMA_INFIFO_OVF_L3_CH1_INT_CLR_S  8
/* GDMA_INFIFO_UDF_1_CH1_INT_CLR:WT；位位置：[7]；默认值：1’b0；*/
/*description:设置此位以清除INFIFO_UDF_L1_CH_INT中断。。*/
#define GDMA_INFIFO_UDF_L1_CH1_INT_CLR    (BIT(7))
#define GDMA_INFIFO_UDF_L1_CH1_INT_CLR_M  (BIT(7))
#define GDMA_INFIFO_UDF_L1_CH1_INT_CLR_V  0x1
#define GDMA_INFIFO_UDF_L1_CH1_INT_CLR_S  7
/* GDMA_INFIFO_OVF_l_CH1_INT_CLR:WT；位位置：[6]；默认值：1’b0；*/
/*description:设置此位以清除INFIFO_OVF_L1_CH_INT中断。。*/
#define GDMA_INFIFO_OVF_L1_CH1_INT_CLR    (BIT(6))
#define GDMA_INFIFO_OVF_L1_CH1_INT_CLR_M  (BIT(6))
#define GDMA_INFIFO_OVF_L1_CH1_INT_CLR_V  0x1
#define GDMA_INFIFO_OVF_L1_CH1_INT_CLR_S  6
/* GDMA_DMA_INFIFO_FULL_WM_CH1_INT_CLR:WT；位位置：[5]；默认值：1’b0；*/
/*description:设置此位以清除INFIFO_FULL_WM_CH_INT中断。。*/
#define GDMA_DMA_INFIFO_FULL_WM_CH1_INT_CLR    (BIT(5))
#define GDMA_DMA_INFIFO_FULL_WM_CH1_INT_CLR_M  (BIT(5))
#define GDMA_DMA_INFIFO_FULL_WM_CH1_INT_CLR_V  0x1
#define GDMA_DMA_INFIFO_FULL_WM_CH1_INT_CLR_S  5
/* GDMA_IN_DSCR_EMPTY-CH1_INT_CLR:WT；位位置：[4]；默认值：1’b0；*/
/*description:设置此位以清除IN_DSCR_EMPTY_CH_INT中断。。*/
#define GDMA_IN_DSCR_EMPTY_CH1_INT_CLR    (BIT(4))
#define GDMA_IN_DSCR_EMPTY_CH1_INT_CLR_M  (BIT(4))
#define GDMA_IN_DSCR_EMPTY_CH1_INT_CLR_V  0x1
#define GDMA_IN_DSCR_EMPTY_CH1_INT_CLR_S  4
/* GDMA_IN_DSCR_ERR_CH1_INT_CLR:WT；位位置：[3]；默认值：1’b0；*/
/*description:设置此位以清除IN_DSCR_ERR_CH_INT中断。。*/
#define GDMA_IN_DSCR_ERR_CH1_INT_CLR    (BIT(3))
#define GDMA_IN_DSCR_ERR_CH1_INT_CLR_M  (BIT(3))
#define GDMA_IN_DSCR_ERR_CH1_INT_CLR_V  0x1
#define GDMA_IN_DSCR_ERR_CH1_INT_CLR_S  3
/* GDMA_IN_ERR_EOF_CH1_INT_CLR:WT；位位置：[2]；默认值：1’b0；*/
/*description:设置此位以清除IN_ERR_EOF_CH_INT中断。。*/
#define GDMA_IN_ERR_EOF_CH1_INT_CLR    (BIT(2))
#define GDMA_IN_ERR_EOF_CH1_INT_CLR_M  (BIT(2))
#define GDMA_IN_ERR_EOF_CH1_INT_CLR_V  0x1
#define GDMA_IN_ERR_EOF_CH1_INT_CLR_S  2
/* GDMA_IN_SUC_EOF_CH1_INT_CLR:WT；位位置：[1]；默认值：1’b0；*/
/*description:设置此位以清除IN_SUC_EOF_CH_INT中断。。*/
#define GDMA_IN_SUC_EOF_CH1_INT_CLR    (BIT(1))
#define GDMA_IN_SUC_EOF_CH1_INT_CLR_M  (BIT(1))
#define GDMA_IN_SUC_EOF_CH1_INT_CLR_V  0x1
#define GDMA_IN_SUC_EOF_CH1_INT_CLR_S  1
/* GDMA_IN_DONE_CH1_INT_CLR:WT；位位置：[0]；默认值：1’b0；*/
/*description:设置此位以清除IN_DONE_CH_INT中断。。*/
#define GDMA_IN_DONE_CH1_INT_CLR    (BIT(0))
#define GDMA_IN_DONE_CH1_INT_CLR_M  (BIT(0))
#define GDMA_IN_DONE_CH1_INT_CLR_V  0x1
#define GDMA_IN_DONE_CH1_INT_CLR_S  0

#define GDMA_INFIFO_STATUS_CH1_REG          (DR_REG_GDMA_BASE + 0xD8)
/* GDMA_IN_BUF_HUNGRY_CH1:RO；位位置：[28]；默认值：1’b0；*/
/*description:保留。*/
#define GDMA_IN_BUF_HUNGRY_CH1    (BIT(28))
#define GDMA_IN_BUF_HUNGRY_CH1_M  (BIT(28))
#define GDMA_IN_BUF_HUNGRY_CH1_V  0x1
#define GDMA_IN_BUF_HUNGRY_CH1_S  28
/* GDMA_IN_REMAIN_UNDER_4B_L3_CH1:RO；位位置：[27]；默认值：1’b1；*/
/*description:保留。*/
#define GDMA_IN_REMAIN_UNDER_4B_L3_CH1    (BIT(27))
#define GDMA_IN_REMAIN_UNDER_4B_L3_CH1_M  (BIT(27))
#define GDMA_IN_REMAIN_UNDER_4B_L3_CH1_V  0x1
#define GDMA_IN_REMAIN_UNDER_4B_L3_CH1_S  27
/* GDMA_IN_REMAIN_UNDER_3B_L3_CH1:RO；位位置：[26]；默认值：1’b1；*/
/*description:保留。*/
#define GDMA_IN_REMAIN_UNDER_3B_L3_CH1    (BIT(26))
#define GDMA_IN_REMAIN_UNDER_3B_L3_CH1_M  (BIT(26))
#define GDMA_IN_REMAIN_UNDER_3B_L3_CH1_V  0x1
#define GDMA_IN_REMAIN_UNDER_3B_L3_CH1_S  26
/* GDMA_IN_REMAIN_UNDER_2B_L3_CH1:RO；位位置：[25]；默认值：1’b1；*/
/*description:保留。*/
#define GDMA_IN_REMAIN_UNDER_2B_L3_CH1    (BIT(25))
#define GDMA_IN_REMAIN_UNDER_2B_L3_CH1_M  (BIT(25))
#define GDMA_IN_REMAIN_UNDER_2B_L3_CH1_V  0x1
#define GDMA_IN_REMAIN_UNDER_2B_L3_CH1_S  25
/* GDMA_IN_REMAIN_UNDER_1B_L3_CH1:RO；位位置：[24]；默认值：1’b1；*/
/*description:保留。*/
#define GDMA_IN_REMAIN_UNDER_1B_L3_CH1    (BIT(24))
#define GDMA_IN_REMAIN_UNDER_1B_L3_CH1_M  (BIT(24))
#define GDMA_IN_REMAIN_UNDER_1B_L3_CH1_V  0x1
#define GDMA_IN_REMAIN_UNDER_1B_L3_CH1_S  24
/* GDMA_INFIFO_CNT_L3_CH1:RO；比特位置：[23:19]；默认值：5’b0；*/
/*描述：寄存器将数据的字节数存储在Rx通道1的L3 Rx FIFO中。。*/
#define GDMA_INFIFO_CNT_L3_CH1    0x0000001F
#define GDMA_INFIFO_CNT_L3_CH1_M  ((GDMA_INFIFO_CNT_L3_CH1_V)<<(GDMA_INFIFO_CNT_L3_CH1_S))
#define GDMA_INFIFO_CNT_L3_CH1_V  0x1F
#define GDMA_INFIFO_CNT_L3_CH1_S  19
/* GDMA_INFIFO_CNT_L2_CH1:RO；比特位置：[18:12]；默认值：7'b0；*/
/*描述：寄存器将数据的字节数存储在Rx通道1的L2 Rx FIFO中。。*/
#define GDMA_INFIFO_CNT_L2_CH1    0x0000007F
#define GDMA_INFIFO_CNT_L2_CH1_M  ((GDMA_INFIFO_CNT_L2_CH1_V)<<(GDMA_INFIFO_CNT_L2_CH1_S))
#define GDMA_INFIFO_CNT_L2_CH1_V  0x7F
#define GDMA_INFIFO_CNT_L2_CH1_S  12
/* GDMA_INFIFO_CNT_L1_CH1:RO；位位置：[11:6]；默认值：6'b0；*/
/*描述：寄存器将数据的字节数存储在Rx通道1的L1 Rx FIFO中。。*/
#define GDMA_INFIFO_CNT_L1_CH1    0x0000003F
#define GDMA_INFIFO_CNT_L1_CH1_M  ((GDMA_INFIFO_CNT_L1_CH1_V)<<(GDMA_INFIFO_CNT_L1_CH1_S))
#define GDMA_INFIFO_CNT_L1_CH1_V  0x3F
#define GDMA_INFIFO_CNT_L1_CH1_S  6
/* GDMA_INFIFO_EMPTY_L3_CH1:RO；位位置：[5]；默认值：1’b1；*/
/*描述：Rx信道1的L3 Rx FIFO空信号。。*/
#define GDMA_INFIFO_EMPTY_L3_CH1    (BIT(5))
#define GDMA_INFIFO_EMPTY_L3_CH1_M  (BIT(5))
#define GDMA_INFIFO_EMPTY_L3_CH1_V  0x1
#define GDMA_INFIFO_EMPTY_L3_CH1_S  5
/* GDMA_INFIFO_FULL_L3_CH1:RO；位位置：[4]；默认值：1’b1；*/
/*描述：Rx信道1的L3 Rx FIFO满信号。。*/
#define GDMA_INFIFO_FULL_L3_CH1    (BIT(4))
#define GDMA_INFIFO_FULL_L3_CH1_M  (BIT(4))
#define GDMA_INFIFO_FULL_L3_CH1_V  0x1
#define GDMA_INFIFO_FULL_L3_CH1_S  4
/* GDMA_INFIFO_EMPTY_L2_CH1:RO；位位置：[3]；默认值：1’b1；*/
/*描述：Rx信道1的L2 Rx FIFO空信号。。*/
#define GDMA_INFIFO_EMPTY_L2_CH1    (BIT(3))
#define GDMA_INFIFO_EMPTY_L2_CH1_M  (BIT(3))
#define GDMA_INFIFO_EMPTY_L2_CH1_V  0x1
#define GDMA_INFIFO_EMPTY_L2_CH1_S  3
/* GDMA_INFIFO_FULL_L2_CH1:RO；位位置：[2]；默认值：1’b0；*/
/*描述：Rx信道1的L2 Rx FIFO满信号。。*/
#define GDMA_INFIFO_FULL_L2_CH1    (BIT(2))
#define GDMA_INFIFO_FULL_L2_CH1_M  (BIT(2))
#define GDMA_INFIFO_FULL_L2_CH1_V  0x1
#define GDMA_INFIFO_FULL_L2_CH1_S  2
/* GDMA_INFIFO_EMPTY_L1_CH1:RO；位位置：[1]；默认值：1’b1；*/
/*描述：Rx信道1的L1 Rx FIFO空信号。。*/
#define GDMA_INFIFO_EMPTY_L1_CH1    (BIT(1))
#define GDMA_INFIFO_EMPTY_L1_CH1_M  (BIT(1))
#define GDMA_INFIFO_EMPTY_L1_CH1_V  0x1
#define GDMA_INFIFO_EMPTY_L1_CH1_S  1
/* GDMA_INFIFO_FULL_L1_CH1:RO；位位置：[0]；默认值：1’b0；*/
/*描述：Rx信道1的L1 Rx FIFO完整信号。。*/
#define GDMA_INFIFO_FULL_L1_CH1    (BIT(0))
#define GDMA_INFIFO_FULL_L1_CH1_M  (BIT(0))
#define GDMA_INFIFO_FULL_L1_CH1_V  0x1
#define GDMA_INFIFO_FULL_L1_CH1_S  0

#define GDMA_IN_POP_CH1_REG          (DR_REG_GDMA_BASE + 0xDC)
/* GDMA_INFIFO_POP_CH1:R/W/SC；位位置：[12]；默认值：1'0；*/
/*description:将此位设置为从DMA FIFO弹出数据。。*/
#define GDMA_INFIFO_POP_CH1    (BIT(12))
#define GDMA_INFIFO_POP_CH1_M  (BIT(12))
#define GDMA_INFIFO_POP_CH1_V  0x1
#define GDMA_INFIFO_POP_CH1_S  12
/* GDMA_INFIFO_data_CH1:RO；位位置：[11:0]；默认值：12'h800；*/
/*description:此寄存器存储从DMA FIFO弹出的数据。。*/
#define GDMA_INFIFO_RDATA_CH1    0x00000FFF
#define GDMA_INFIFO_RDATA_CH1_M  ((GDMA_INFIFO_RDATA_CH1_V)<<(GDMA_INFIFO_RDATA_CH1_S))
#define GDMA_INFIFO_RDATA_CH1_V  0xFFF
#define GDMA_INFIFO_RDATA_CH1_S  0

#define GDMA_IN_LINK_CH1_REG          (DR_REG_GDMA_BASE + 0xE0)
/* GDMA_INLINK_PARK_CH1:RO；位位置：[24]；默认值：1'h1；*/
/*description:1：内联描述符的FSM处于空闲状态。0:内联描述符的FSM正在工作。。*/
#define GDMA_INLINK_PARK_CH1    (BIT(24))
#define GDMA_INLINK_PARK_CH1_M  (BIT(24))
#define GDMA_INLINK_PARK_CH1_V  0x1
#define GDMA_INLINK_PARK_CH1_S  24
/* GDMA_INLINK_RESTART_CH1:R/W/SC；位位置：[23]；默认值：1’b0；*/
/*description:设置此位以装入新的内联描述符。。*/
#define GDMA_INLINK_RESTART_CH1    (BIT(23))
#define GDMA_INLINK_RESTART_CH1_M  (BIT(23))
#define GDMA_INLINK_RESTART_CH1_V  0x1
#define GDMA_INLINK_RESTART_CH1_S  23
/* GDMA_INLINK_START_CH1:R/W/SC；位位置：[22]；默认值：1’b0；*/
/*description:设置此位以开始处理内联描述符。。*/
#define GDMA_INLINK_START_CH1    (BIT(22))
#define GDMA_INLINK_START_CH1_M  (BIT(22))
#define GDMA_INLINK_START_CH1_V  0x1
#define GDMA_INLINK_START_CH1_S  22
/* GDMA_INLINK_STOP_CH1:R/W/SC；位位置：[21]；默认值：1’b0；*/
/*description:设置此位以停止处理内联描述符。。*/
#define GDMA_INLINK_STOP_CH1    (BIT(21))
#define GDMA_INLINK_STOP_CH1_M  (BIT(21))
#define GDMA_INLINK_STOP_CH1_V  0x1
#define GDMA_INLINK_STOP_CH1_S  21
/* GDMA_INLINK_AUTO_RET_CH1:R/W；位位置：[20]；默认值：1’b1；*/
/*description:当当前接收数据中存在一些错误时，将此位设置为返回当前内联描述符的地址。。*/
#define GDMA_INLINK_AUTO_RET_CH1    (BIT(20))
#define GDMA_INLINK_AUTO_RET_CH1_M  (BIT(20))
#define GDMA_INLINK_AUTO_RET_CH1_V  0x1
#define GDMA_INLINK_AUTO_RET_CH1_S  20
/* GDMA_INLINK_ADDR_CH1:R/W；比特位置：[19:0]；默认值：20'00；*/
/*description:此寄存器存储第一个内联描述符地址的20个最低有效位。。*/
#define GDMA_INLINK_ADDR_CH1    0x000FFFFF
#define GDMA_INLINK_ADDR_CH1_M  ((GDMA_INLINK_ADDR_CH1_V)<<(GDMA_INLINK_ADDR_CH1_S))
#define GDMA_INLINK_ADDR_CH1_V  0xFFFFF
#define GDMA_INLINK_ADDR_CH1_S  0

#define GDMA_IN_STATE_CH1_REG          (DR_REG_GDMA_BASE + 0xE4)
/* GDMA_IN_STATE_CH1:RO；比特位置：[22:20]；默认值：3'b0；*/
/*description:保留。*/
#define GDMA_IN_STATE_CH1    0x00000007
#define GDMA_IN_STATE_CH1_M  ((GDMA_IN_STATE_CH1_V)<<(GDMA_IN_STATE_CH1_S))
#define GDMA_IN_STATE_CH1_V  0x7
#define GDMA_IN_STATE_CH1_S  20
/* GDMA_IN_DSCR_STATE_CH1:RO；比特位置：[19:18]；默认值：2’b0；*/
/*description:保留。*/
#define GDMA_IN_DSCR_STATE_CH1    0x00000003
#define GDMA_IN_DSCR_STATE_CH1_M  ((GDMA_IN_DSCR_STATE_CH1_V)<<(GDMA_IN_DSCR_STATE_CH1_S))
#define GDMA_IN_DSCR_STATE_CH1_V  0x3
#define GDMA_IN_DSCR_STATE_CH1_S  18
/* GDMA_INLINK_DSCR_ADDR_CH1:RO；比特位置：[17:00]；默认值：18'b0；*/
/*description:此寄存器存储当前内联描述符的地址。。*/
#define GDMA_INLINK_DSCR_ADDR_CH1    0x0003FFFF
#define GDMA_INLINK_DSCR_ADDR_CH1_M  ((GDMA_INLINK_DSCR_ADDR_CH1_V)<<(GDMA_INLINK_DSCR_ADDR_CH1_S))
#define GDMA_INLINK_DSCR_ADDR_CH1_V  0x3FFFF
#define GDMA_INLINK_DSCR_ADDR_CH1_S  0

#define GDMA_IN_SUC_EOF_DES_ADDR_CH1_REG          (DR_REG_GDMA_BASE + 0xE8)
/* GDMA_IN_SUC_EOF_DES_ADDR_CH1:RO；位位置：[31:0]；默认值：32'h0；*/
/*description:当此描述符中的EOF位为1时，此寄存器存储内联描述符的地址。。*/
#define GDMA_IN_SUC_EOF_DES_ADDR_CH1    0xFFFFFFFF
#define GDMA_IN_SUC_EOF_DES_ADDR_CH1_M  ((GDMA_IN_SUC_EOF_DES_ADDR_CH1_V)<<(GDMA_IN_SUC_EOF_DES_ADDR_CH1_S))
#define GDMA_IN_SUC_EOF_DES_ADDR_CH1_V  0xFFFFFFFF
#define GDMA_IN_SUC_EOF_DES_ADDR_CH1_S  0

#define GDMA_IN_ERR_EOF_DES_ADDR_CH1_REG          (DR_REG_GDMA_BASE + 0xEC)
/* GDMA_IN_ERR_EOF_DES_ADDR_CH1:RO；位位置：[31:0]；默认值：32'h0；*/
/*description:当当前接收数据中存在一些错误时，此寄存器存储内联描述符的地址。仅当外围设备为UHCI0时使用。。*/
#define GDMA_IN_ERR_EOF_DES_ADDR_CH1    0xFFFFFFFF
#define GDMA_IN_ERR_EOF_DES_ADDR_CH1_M  ((GDMA_IN_ERR_EOF_DES_ADDR_CH1_V)<<(GDMA_IN_ERR_EOF_DES_ADDR_CH1_S))
#define GDMA_IN_ERR_EOF_DES_ADDR_CH1_V  0xFFFFFFFF
#define GDMA_IN_ERR_EOF_DES_ADDR_CH1_S  0

#define GDMA_IN_DSCR_CH1_REG          (DR_REG_GDMA_BASE + 0xF0)
/* GDMA_INLINK_DSCR_CH1:RO；位位置：[31:0]；默认值：32'b0；*/
/*description:当前内联描述符x的地址。。*/
#define GDMA_INLINK_DSCR_CH1    0xFFFFFFFF
#define GDMA_INLINK_DSCR_CH1_M  ((GDMA_INLINK_DSCR_CH1_V)<<(GDMA_INLINK_DSCR_CH1_S))
#define GDMA_INLINK_DSCR_CH1_V  0xFFFFFFFF
#define GDMA_INLINK_DSCR_CH1_S  0

#define GDMA_IN_DSCR_BF0_CH1_REG          (DR_REG_GDMA_BASE + 0xF4)
/* GDMA_INLINK_DSCR_BF0_CH1:RO；位位置：[31:0]；默认值：32'b0；*/
/*description:最后一个内联描述符x-1的地址。。*/
#define GDMA_INLINK_DSCR_BF0_CH1    0xFFFFFFFF
#define GDMA_INLINK_DSCR_BF0_CH1_M  ((GDMA_INLINK_DSCR_BF0_CH1_V)<<(GDMA_INLINK_DSCR_BF0_CH1_S))
#define GDMA_INLINK_DSCR_BF0_CH1_V  0xFFFFFFFF
#define GDMA_INLINK_DSCR_BF0_CH1_S  0

#define GDMA_IN_DSCR_BF1_CH1_REG          (DR_REG_GDMA_BASE + 0xF8)
/* GDMA_INLINK_DSCR_BF1_CH1:RO；位位置：[31:0]；默认值：32'b0；*/
/*description:倒数第二个内联描述符x-2的地址。。*/
#define GDMA_INLINK_DSCR_BF1_CH1    0xFFFFFFFF
#define GDMA_INLINK_DSCR_BF1_CH1_M  ((GDMA_INLINK_DSCR_BF1_CH1_V)<<(GDMA_INLINK_DSCR_BF1_CH1_S))
#define GDMA_INLINK_DSCR_BF1_CH1_V  0xFFFFFFFF
#define GDMA_INLINK_DSCR_BF1_CH1_S  0

#define GDMA_IN_WIGHT_CH1_REG          (DR_REG_GDMA_BASE + 0xFC)
/* GDMA_RX_WEIGHT_CH1:R/W；位位置：[11:8]；默认值：4'hf；*/
/*description:Rx通道1的权重。*/
#define GDMA_RX_WEIGHT_CH1    0x0000000F
#define GDMA_RX_WEIGHT_CH1_M  ((GDMA_RX_WEIGHT_CH1_V)<<(GDMA_RX_WEIGHT_CH1_S))
#define GDMA_RX_WEIGHT_CH1_V  0xF
#define GDMA_RX_WEIGHT_CH1_S  8

#define GDMA_IN_PRI_CH1_REG          (DR_REG_GDMA_BASE + 0x104)
/* GDMA_RX_PRI_CH1:R/W；位位置：[3:0]；默认值：4'b0；*/
/*description:Rx通道1的优先级。值越大，优先级越高。。*/
#define GDMA_RX_PRI_CH1    0x0000000F
#define GDMA_RX_PRI_CH1_M  ((GDMA_RX_PRI_CH1_V)<<(GDMA_RX_PRI_CH1_S))
#define GDMA_RX_PRI_CH1_V  0xF
#define GDMA_RX_PRI_CH1_S  0

#define GDMA_IN_PERI_SEL_CH1_REG          (DR_REG_GDMA_BASE + 0x108)
/* GDMA_PERI_IN_SEL_CH1:R/W；比特位置：[5:0]；默认值：6'h3f；*/
/*描述：此寄存器用于为Rx通道1.0:SPI2.1:SPI3.2:UHCI0.3:I2S0.4:I2S1.5:LCD_CAM选择外围设备。6： AES。7： 沙。8： ADC_DAC。9： RMT。。*/
#define GDMA_PERI_IN_SEL_CH1    0x0000003F
#define GDMA_PERI_IN_SEL_CH1_M  ((GDMA_PERI_IN_SEL_CH1_V)<<(GDMA_PERI_IN_SEL_CH1_S))
#define GDMA_PERI_IN_SEL_CH1_V  0x3F
#define GDMA_PERI_IN_SEL_CH1_S  0

#define GDMA_OUT_CONF0_CH1_REG          (DR_REG_GDMA_BASE + 0x120)
/* GDMA_OUT_DATA_BURST_EN_CH1:R/W；位位置：[5]；默认值：1’b0；*/
/*描述：当访问内部SRAM时，将此位设置为1以启用传输数据的Tx信道1的INCR突发传输。*/
#define GDMA_OUT_DATA_BURST_EN_CH1    (BIT(5))
#define GDMA_OUT_DATA_BURST_EN_CH1_M  (BIT(5))
#define GDMA_OUT_DATA_BURST_EN_CH1_V  0x1
#define GDMA_OUT_DATA_BURST_EN_CH1_S  5
/* GDMA_OUTDSCR_BURST_EN_CH1:R/W；位位置：[4]；默认值：1’b0；*/
/*description:将此位设置为1，以便在访问内部SRAM时，为Tx信道1读取链路描述符启用INCR突发传输。*/
#define GDMA_OUTDSCR_BURST_EN_CH1    (BIT(4))
#define GDMA_OUTDSCR_BURST_EN_CH1_M  (BIT(4))
#define GDMA_OUTDSCR_BURST_EN_CH1_V  0x1
#define GDMA_OUTDSCR_BURST_EN_CH1_S  4
/* GDMA_OUT_EOF_MODE_CH1:R/W；位位置：[3]；默认值：1’b1；*/
/*描述：传输数据时EOF标志生成模式。1： 当需要传输的数据从DMA中的FIFO弹出时，生成Tx信道0的EOF标志。*/
#define GDMA_OUT_EOF_MODE_CH1    (BIT(3))
#define GDMA_OUT_EOF_MODE_CH1_M  (BIT(3))
#define GDMA_OUT_EOF_MODE_CH1_V  0x1
#define GDMA_OUT_EOF_MODE_CH1_S  3
/* GDMA_OUT_AUTO_WRBACK_CH1:R/W；位位置：[2]；默认值：1’b0；*/
/*description:设置此位以在传输tx缓冲区中的所有数据时启用自动outlink写回。。*/
#define GDMA_OUT_AUTO_WRBACK_CH1    (BIT(2))
#define GDMA_OUT_AUTO_WRBACK_CH1_M  (BIT(2))
#define GDMA_OUT_AUTO_WRBACK_CH1_V  0x1
#define GDMA_OUT_AUTO_WRBACK_CH1_S  2
/* GDMA_OUT_LOOP_TEST_CH1:R/W；位位置：[1]；默认值：1’b0；*/
/*description:保留。*/
#define GDMA_OUT_LOOP_TEST_CH1    (BIT(1))
#define GDMA_OUT_LOOP_TEST_CH1_M  (BIT(1))
#define GDMA_OUT_LOOP_TEST_CH1_V  0x1
#define GDMA_OUT_LOOP_TEST_CH1_S  1
/* GDMA_OUT_RST_CH1:R/W；位位置：[0]；默认值：1’b0；*/
/*描述：此位用于重置DMA通道0 Tx FSM和Tx FIFO指针。。*/
#define GDMA_OUT_RST_CH1    (BIT(0))
#define GDMA_OUT_RST_CH1_M  (BIT(0))
#define GDMA_OUT_RST_CH1_V  0x1
#define GDMA_OUT_RST_CH1_S  0

#define GDMA_OUT_CONF1_CH1_REG          (DR_REG_GDMA_BASE + 0x124)
/* GDMA_OUT_EXT_MEM_BK_SIZE_CH1:R/W；比特位置：[14:13]；默认值：2’b0；*/
/*描述：DMA访问外部SRAM时Tx通道1的块大小。0:16字节1:32字节2/3:保留。*/
#define GDMA_OUT_EXT_MEM_BK_SIZE_CH1    0x00000003
#define GDMA_OUT_EXT_MEM_BK_SIZE_CH1_M  ((GDMA_OUT_EXT_MEM_BK_SIZE_CH1_V)<<(GDMA_OUT_EXT_MEM_BK_SIZE_CH1_S))
#define GDMA_OUT_EXT_MEM_BK_SIZE_CH1_V  0x3
#define GDMA_OUT_EXT_MEM_BK_SIZE_CH1_S  13
/* GDMA_OUT_CHECK_OWNER_CH1:R/W；位位置：[12]；默认值：1’b0；*/
/*description:设置此位以启用检查链接描述符的所有者属性。。*/
#define GDMA_OUT_CHECK_OWNER_CH1    (BIT(12))
#define GDMA_OUT_CHECK_OWNER_CH1_M  (BIT(12))
#define GDMA_OUT_CHECK_OWNER_CH1_V  0x1
#define GDMA_OUT_CHECK_OWNER_CH1_S  12

#define GDMA_OUT_INT_RAW_CH1_REG          (DR_REG_GDMA_BASE + 0x128)
/* GDMA_OUTFIFO_udfl_L3_CH1_INT_RAW:R/WTC/SS；位位置：[7]；默认值：1’b0；*/
/*描述：当Tx信道1的第3级fifo未满流时，此原始中断位变为高电平。*/
#define GDMA_OUTFIFO_UDF_L3_CH1_INT_RAW    (BIT(7))
#define GDMA_OUTFIFO_UDF_L3_CH1_INT_RAW_M  (BIT(7))
#define GDMA_OUTFIFO_UDF_L3_CH1_INT_RAW_V  0x1
#define GDMA_OUTFIFO_UDF_L3_CH1_INT_RAW_S  7
/* GDMA_OUTFIFO_off_13_CH1_INT_RAW:R/WTC/SS；位位置：[6]；默认值：1’b0；*/
/*描述：当Tx信道1的3级fifo等流量时，此原始中断位变为高电平。*/
#define GDMA_OUTFIFO_OVF_L3_CH1_INT_RAW    (BIT(6))
#define GDMA_OUTFIFO_OVF_L3_CH1_INT_RAW_M  (BIT(6))
#define GDMA_OUTFIFO_OVF_L3_CH1_INT_RAW_V  0x1
#define GDMA_OUTFIFO_OVF_L3_CH1_INT_RAW_S  6
/* GDMA_OUTFIFO_UDF_l_CH1_INT_RAW:R/WTC/SS；位位置：[5]；默认值：1’b0；*/
/*描述：当Tx信道1的第1级fifo未满流时，此原始中断位变为高电平。*/
#define GDMA_OUTFIFO_UDF_L1_CH1_INT_RAW    (BIT(5))
#define GDMA_OUTFIFO_UDF_L1_CH1_INT_RAW_M  (BIT(5))
#define GDMA_OUTFIFO_UDF_L1_CH1_INT_RAW_V  0x1
#define GDMA_OUTFIFO_UDF_L1_CH1_INT_RAW_S  5
/* GDMA_OUTFIFO_OVF_l_CH1_INT_RAW:R/WTC/SS；位位置：[4]；默认值：1’b0；*/
/*描述：当Tx信道1的1级fifo等流量时，此原始中断位变为高电平。*/
#define GDMA_OUTFIFO_OVF_L1_CH1_INT_RAW    (BIT(4))
#define GDMA_OUTFIFO_OVF_L1_CH1_INT_RAW_M  (BIT(4))
#define GDMA_OUTFIFO_OVF_L1_CH1_INT_RAW_V  0x1
#define GDMA_OUTFIFO_OVF_L1_CH1_INT_RAW_S  4
/* GDMA_OUT_TOTAL_EOF_CH1_INT_RAW:R/WTC/SS；位位置：[3]；默认值：1’b0；*/
/*描述：当针对Tx信道1发送出与输出链接（包括一个链接描述符或几个链接描述符）相对应的数据时，原始中断位变为高电平。。*/
#define GDMA_OUT_TOTAL_EOF_CH1_INT_RAW    (BIT(3))
#define GDMA_OUT_TOTAL_EOF_CH1_INT_RAW_M  (BIT(3))
#define GDMA_OUT_TOTAL_EOF_CH1_INT_RAW_V  0x1
#define GDMA_OUT_TOTAL_EOF_CH1_INT_RAW_S  3
/* GDMA_OUT_DSCR_ERR_CH1_INT_RAW:R/WTC/SS；位位置：[2]；默认值：1’b0；*/
/*描述：当检测到outlink描述符错误时，原始中断位变为高电平，包括所有者错误、Tx信道1的outlink描述符的第二个和第三个字错误。。*/
#define GDMA_OUT_DSCR_ERR_CH1_INT_RAW    (BIT(2))
#define GDMA_OUT_DSCR_ERR_CH1_INT_RAW_M  (BIT(2))
#define GDMA_OUT_DSCR_ERR_CH1_INT_RAW_V  0x1
#define GDMA_OUT_DSCR_ERR_CH1_INT_RAW_S  2
/* GDMA_OUT_EOF_CH1_INT_RAW:R/WTC/SS；位位置：[1]；默认值：1’b0；*/
/*描述：当从Tx信道1的存储器中读取一个输出描述符所指向的最后一个数据时，原始中断位变为高电平。*/
#define GDMA_OUT_EOF_CH1_INT_RAW    (BIT(1))
#define GDMA_OUT_EOF_CH1_INT_RAW_M  (BIT(1))
#define GDMA_OUT_EOF_CH1_INT_RAW_V  0x1
#define GDMA_OUT_EOF_CH1_INT_RAW_S  1
/* GDMA_OUT_DONE_CH1_INT_RAW:R/WTC/SS；位位置：[0]；默认值：1’b0；*/
/*描述：当一个输出描述符所指向的最后一个数据已传输到Tx信道1的外围设备时，原始中断位变为高电平。。*/
#define GDMA_OUT_DONE_CH1_INT_RAW    (BIT(0))
#define GDMA_OUT_DONE_CH1_INT_RAW_M  (BIT(0))
#define GDMA_OUT_DONE_CH1_INT_RAW_V  0x1
#define GDMA_OUT_DONE_CH1_INT_RAW_S  0

#define GDMA_OUT_INT_ST_CH1_REG          (DR_REG_GDMA_BASE + 0x12C)
/* GDMA_OUTFIFO_udfl3_CH1_INT_ST:RO；位位置：[7]；默认值：1’b0；*/
/*description:OUTFIFO_UDF_L3_CH_INT中断的原始中断状态位。。*/
#define GDMA_OUTFIFO_UDF_L3_CH1_INT_ST    (BIT(7))
#define GDMA_OUTFIFO_UDF_L3_CH1_INT_ST_M  (BIT(7))
#define GDMA_OUTFIFO_UDF_L3_CH1_INT_ST_V  0x1
#define GDMA_OUTFIFO_UDF_L3_CH1_INT_ST_S  7
/* GDMA_OUTFIFO_off_13_CH1_INT_ST:RO；位位置：[6]；默认值：1’b0；*/
/*description:OUTFIFO_OVF_L3_CH_INT中断的原始中断状态位。。*/
#define GDMA_OUTFIFO_OVF_L3_CH1_INT_ST    (BIT(6))
#define GDMA_OUTFIFO_OVF_L3_CH1_INT_ST_M  (BIT(6))
#define GDMA_OUTFIFO_OVF_L3_CH1_INT_ST_V  0x1
#define GDMA_OUTFIFO_OVF_L3_CH1_INT_ST_S  6
/* GDMA_OUTFIFO_UDF_l_CH1_INT_ST:RO；位位置：[5]；默认值：1’b0；*/
/*description:OUTFIFO_UDF_L1_CH_INT中断的原始中断状态位。。*/
#define GDMA_OUTFIFO_UDF_L1_CH1_INT_ST    (BIT(5))
#define GDMA_OUTFIFO_UDF_L1_CH1_INT_ST_M  (BIT(5))
#define GDMA_OUTFIFO_UDF_L1_CH1_INT_ST_V  0x1
#define GDMA_OUTFIFO_UDF_L1_CH1_INT_ST_S  5
/* GDMA_OUTFIFO_OVF_l_CH1_INT_ST:RO；位位置：[4]；默认值：1’b0；*/
/*description:OUTFIFO_OVF_L1_CH_INT中断的原始中断状态位。。*/
#define GDMA_OUTFIFO_OVF_L1_CH1_INT_ST    (BIT(4))
#define GDMA_OUTFIFO_OVF_L1_CH1_INT_ST_M  (BIT(4))
#define GDMA_OUTFIFO_OVF_L1_CH1_INT_ST_V  0x1
#define GDMA_OUTFIFO_OVF_L1_CH1_INT_ST_S  4
/* GDMA_OUT_TOTAL_EOF_CH1_INT_ST:RO；位位置：[3]；默认值：1’b0；*/
/*description:OUT_TOTAL_EOF_CH_INT中断的原始中断状态位。。*/
#define GDMA_OUT_TOTAL_EOF_CH1_INT_ST    (BIT(3))
#define GDMA_OUT_TOTAL_EOF_CH1_INT_ST_M  (BIT(3))
#define GDMA_OUT_TOTAL_EOF_CH1_INT_ST_V  0x1
#define GDMA_OUT_TOTAL_EOF_CH1_INT_ST_S  3
/* GDMA_OUT_DSCR_ERR_CH1_INT_ST:RO；位位置：[2]；默认值：1’b0；*/
/*description:OUT_DSCR_ERR_CH_INT中断的原始中断状态位。。*/
#define GDMA_OUT_DSCR_ERR_CH1_INT_ST    (BIT(2))
#define GDMA_OUT_DSCR_ERR_CH1_INT_ST_M  (BIT(2))
#define GDMA_OUT_DSCR_ERR_CH1_INT_ST_V  0x1
#define GDMA_OUT_DSCR_ERR_CH1_INT_ST_S  2
/* GDMA_OUT_EOF_CH1_INT_ST:RO；位位置：[1]；默认值：1’b0；*/
/*description:OUT_EOF_CH_INT中断的原始中断状态位。。*/
#define GDMA_OUT_EOF_CH1_INT_ST    (BIT(1))
#define GDMA_OUT_EOF_CH1_INT_ST_M  (BIT(1))
#define GDMA_OUT_EOF_CH1_INT_ST_V  0x1
#define GDMA_OUT_EOF_CH1_INT_ST_S  1
/* GDMA_OUT_DONE_CH1_INT_ST:RO；位位置：[0]；默认值：1’b0；*/
/*description:OUT_DONE_CH_INT中断的原始中断状态位。。*/
#define GDMA_OUT_DONE_CH1_INT_ST    (BIT(0))
#define GDMA_OUT_DONE_CH1_INT_ST_M  (BIT(0))
#define GDMA_OUT_DONE_CH1_INT_ST_V  0x1
#define GDMA_OUT_DONE_CH1_INT_ST_S  0

#define GDMA_OUT_INT_ENA_CH1_REG          (DR_REG_GDMA_BASE + 0x130)
/* GDMA_OUTFIFO_UDF_13_CH1_INT_ENA:R/W；位位置：[7]；默认值：1’b0；*/
/*description:OUTFIFO_UDF_L3_CH_INT中断的中断启用位。。*/
#define GDMA_OUTFIFO_UDF_L3_CH1_INT_ENA    (BIT(7))
#define GDMA_OUTFIFO_UDF_L3_CH1_INT_ENA_M  (BIT(7))
#define GDMA_OUTFIFO_UDF_L3_CH1_INT_ENA_V  0x1
#define GDMA_OUTFIFO_UDF_L3_CH1_INT_ENA_S  7
/* GDMA_OUTFIFO_off_13_CH1_INT_ENA:R/W；位位置：[6]；默认值：1’b0；*/
/*description:OUTFIFO_OVF_L3_CH_INT中断的中断启用位。。*/
#define GDMA_OUTFIFO_OVF_L3_CH1_INT_ENA    (BIT(6))
#define GDMA_OUTFIFO_OVF_L3_CH1_INT_ENA_M  (BIT(6))
#define GDMA_OUTFIFO_OVF_L3_CH1_INT_ENA_V  0x1
#define GDMA_OUTFIFO_OVF_L3_CH1_INT_ENA_S  6
/* GDMA_OUTFIFO_UDF_l_CH1_INT_ENA:R/W；位位置：[5]；默认值：1’b0；*/
/*description:OUTFIFO_UDF_L1_CH_INT中断的中断启用位。。*/
#define GDMA_OUTFIFO_UDF_L1_CH1_INT_ENA    (BIT(5))
#define GDMA_OUTFIFO_UDF_L1_CH1_INT_ENA_M  (BIT(5))
#define GDMA_OUTFIFO_UDF_L1_CH1_INT_ENA_V  0x1
#define GDMA_OUTFIFO_UDF_L1_CH1_INT_ENA_S  5
/* GDMA_OUTFIFO_OVF_l_CH1_INT_ENA：R/W；位位置：[4]；默认值：1’b0；*/
/*description:OUTFIFO_OVF_L1_CH_INT中断的中断启用位。。*/
#define GDMA_OUTFIFO_OVF_L1_CH1_INT_ENA    (BIT(4))
#define GDMA_OUTFIFO_OVF_L1_CH1_INT_ENA_M  (BIT(4))
#define GDMA_OUTFIFO_OVF_L1_CH1_INT_ENA_V  0x1
#define GDMA_OUTFIFO_OVF_L1_CH1_INT_ENA_S  4
/* GDMA_OUT_TOTAL_EOF_CH1_INT_ENA:R/W；位位置：[3]；默认值：1’b0；*/
/*description:OUT_TOTAL_EOF_CH_INT中断的中断启用位。。*/
#define GDMA_OUT_TOTAL_EOF_CH1_INT_ENA    (BIT(3))
#define GDMA_OUT_TOTAL_EOF_CH1_INT_ENA_M  (BIT(3))
#define GDMA_OUT_TOTAL_EOF_CH1_INT_ENA_V  0x1
#define GDMA_OUT_TOTAL_EOF_CH1_INT_ENA_S  3
/* GDMA_OUT_DSCR_ERR_CH1_INT_ENA:R/W；位位置：[2]；默认值：1’b0；*/
/*description:OUT_DSCR_ERR_CH_INT中断的中断启用位。。*/
#define GDMA_OUT_DSCR_ERR_CH1_INT_ENA    (BIT(2))
#define GDMA_OUT_DSCR_ERR_CH1_INT_ENA_M  (BIT(2))
#define GDMA_OUT_DSCR_ERR_CH1_INT_ENA_V  0x1
#define GDMA_OUT_DSCR_ERR_CH1_INT_ENA_S  2
/* GDMA_OUT_EOF_CH1_INT_ENA:R/W；位位置：[1]；默认值：1’b0；*/
/*description:OUT_EOF_CH_INT中断的中断启用位。。*/
#define GDMA_OUT_EOF_CH1_INT_ENA    (BIT(1))
#define GDMA_OUT_EOF_CH1_INT_ENA_M  (BIT(1))
#define GDMA_OUT_EOF_CH1_INT_ENA_V  0x1
#define GDMA_OUT_EOF_CH1_INT_ENA_S  1
/* GDMA_OUT_DONE_CH1_INT_ENA:R/W；位位置：[0]；默认值：1’b0；*/
/*description:OUT_DONE_CH_INT中断的中断启用位。。*/
#define GDMA_OUT_DONE_CH1_INT_ENA    (BIT(0))
#define GDMA_OUT_DONE_CH1_INT_ENA_M  (BIT(0))
#define GDMA_OUT_DONE_CH1_INT_ENA_V  0x1
#define GDMA_OUT_DONE_CH1_INT_ENA_S  0

#define GDMA_OUT_INT_CLR_CH1_REG          (DR_REG_GDMA_BASE + 0x134)
/* GDMA_OUTFIFO_udfl_L3_CH1_INT_CLR:WO；位位置：[7]；默认值：1’b0；*/
/*description:设置此位以清除OUTFIFO_UDF_L3_CH_INT中断。。*/
#define GDMA_OUTFIFO_UDF_L3_CH1_INT_CLR    (BIT(7))
#define GDMA_OUTFIFO_UDF_L3_CH1_INT_CLR_M  (BIT(7))
#define GDMA_OUTFIFO_UDF_L3_CH1_INT_CLR_V  0x1
#define GDMA_OUTFIFO_UDF_L3_CH1_INT_CLR_S  7
/* GDMA_OUTFIFO_off_13_CH1_INT_CLR:WO；位位置：[6]；默认值：1’b0；*/
/*description:设置此位以清除OUTFIFO_OVF_L3_CH_INT中断。。*/
#define GDMA_OUTFIFO_OVF_L3_CH1_INT_CLR    (BIT(6))
#define GDMA_OUTFIFO_OVF_L3_CH1_INT_CLR_M  (BIT(6))
#define GDMA_OUTFIFO_OVF_L3_CH1_INT_CLR_V  0x1
#define GDMA_OUTFIFO_OVF_L3_CH1_INT_CLR_S  6
/* GDMA_OUTFIFO_UDF_l_CH1_INT_CLR:WO；位位置：[5]；默认值：1’b0；*/
/*description:设置此位以清除OUTFIFO_UDF_L1_CH_INT中断。。*/
#define GDMA_OUTFIFO_UDF_L1_CH1_INT_CLR    (BIT(5))
#define GDMA_OUTFIFO_UDF_L1_CH1_INT_CLR_M  (BIT(5))
#define GDMA_OUTFIFO_UDF_L1_CH1_INT_CLR_V  0x1
#define GDMA_OUTFIFO_UDF_L1_CH1_INT_CLR_S  5
/* GDMA_OUTFIFO_OVF_l_CH1_INT_CLR:WO；位位置：[4]；默认值：1’b0；*/
/*description:设置此位以清除OUTFIFO_OVF_L1_CH_INT中断。。*/
#define GDMA_OUTFIFO_OVF_L1_CH1_INT_CLR    (BIT(4))
#define GDMA_OUTFIFO_OVF_L1_CH1_INT_CLR_M  (BIT(4))
#define GDMA_OUTFIFO_OVF_L1_CH1_INT_CLR_V  0x1
#define GDMA_OUTFIFO_OVF_L1_CH1_INT_CLR_S  4
/* GDMA_OUT_TOTAL_EOF_CH1_INT_CLR:WT；位位置：[3]；默认值：1’b0；*/
/*description:设置此位以清除OUT_TOTAL_EOF_CH_INT中断。。*/
#define GDMA_OUT_TOTAL_EOF_CH1_INT_CLR    (BIT(3))
#define GDMA_OUT_TOTAL_EOF_CH1_INT_CLR_M  (BIT(3))
#define GDMA_OUT_TOTAL_EOF_CH1_INT_CLR_V  0x1
#define GDMA_OUT_TOTAL_EOF_CH1_INT_CLR_S  3
/* GDMA_OUT_DSCR_ERR_CH1_INT_CLR:WT；位位置：[2]；默认值：1’b0；*/
/*description:设置此位以清除OUT_DSCR_ERR_CH_INT中断。。*/
#define GDMA_OUT_DSCR_ERR_CH1_INT_CLR    (BIT(2))
#define GDMA_OUT_DSCR_ERR_CH1_INT_CLR_M  (BIT(2))
#define GDMA_OUT_DSCR_ERR_CH1_INT_CLR_V  0x1
#define GDMA_OUT_DSCR_ERR_CH1_INT_CLR_S  2
/* GDMA_OUT_EOF_CH1_INT_CLR:WT；位位置：[1]；默认值：1’b0；*/
/*description:设置此位以清除OUT_EOF_CH_INT中断。。*/
#define GDMA_OUT_EOF_CH1_INT_CLR    (BIT(1))
#define GDMA_OUT_EOF_CH1_INT_CLR_M  (BIT(1))
#define GDMA_OUT_EOF_CH1_INT_CLR_V  0x1
#define GDMA_OUT_EOF_CH1_INT_CLR_S  1
/* GDMA_OUT_DONE_CH1_INT_CLR:WT；位位置：[0]；默认值：1’b0；*/
/*description:设置此位以清除OUT_DONE_CH_INT中断。。*/
#define GDMA_OUT_DONE_CH1_INT_CLR    (BIT(0))
#define GDMA_OUT_DONE_CH1_INT_CLR_M  (BIT(0))
#define GDMA_OUT_DONE_CH1_INT_CLR_V  0x1
#define GDMA_OUT_DONE_CH1_INT_CLR_S  0

#define GDMA_OUTFIFO_STATUS_CH1_REG          (DR_REG_GDMA_BASE + 0x138)
/* GDMA_OUT_REMAIN_UNDER_4B_L3_CH1:RO；位位置：[26]；默认值：1’b1；*/
/*description:保留。*/
#define GDMA_OUT_REMAIN_UNDER_4B_L3_CH1    (BIT(26))
#define GDMA_OUT_REMAIN_UNDER_4B_L3_CH1_M  (BIT(26))
#define GDMA_OUT_REMAIN_UNDER_4B_L3_CH1_V  0x1
#define GDMA_OUT_REMAIN_UNDER_4B_L3_CH1_S  26
/* GDMA_OUT_REMAIN_UNDER_3B_L3_CH1:RO；位位置：[25]；默认值：1’b1；*/
/*description:保留。*/
#define GDMA_OUT_REMAIN_UNDER_3B_L3_CH1    (BIT(25))
#define GDMA_OUT_REMAIN_UNDER_3B_L3_CH1_M  (BIT(25))
#define GDMA_OUT_REMAIN_UNDER_3B_L3_CH1_V  0x1
#define GDMA_OUT_REMAIN_UNDER_3B_L3_CH1_S  25
/* GDMA_OUT_REMAIN_UNDER_2B_L3_CH1:RO；位位置：[24]；默认值：1’b1；*/
/*description:保留。*/
#define GDMA_OUT_REMAIN_UNDER_2B_L3_CH1    (BIT(24))
#define GDMA_OUT_REMAIN_UNDER_2B_L3_CH1_M  (BIT(24))
#define GDMA_OUT_REMAIN_UNDER_2B_L3_CH1_V  0x1
#define GDMA_OUT_REMAIN_UNDER_2B_L3_CH1_S  24
/* GDMA_OUT_REMAIN_UNDER_1B_L3_CH1:RO；位位置：[23]；默认值：1’b1；*/
/*description:保留。*/
#define GDMA_OUT_REMAIN_UNDER_1B_L3_CH1    (BIT(23))
#define GDMA_OUT_REMAIN_UNDER_1B_L3_CH1_M  (BIT(23))
#define GDMA_OUT_REMAIN_UNDER_1B_L3_CH1_V  0x1
#define GDMA_OUT_REMAIN_UNDER_1B_L3_CH1_S  23
/* GDMA_OUTFIFO_CNT_L3_CH1:RO；比特位置：[22:18]；默认值：5’b0；*/
/*描述：寄存器将数据的字节数存储在Tx信道1的L3 Tx FIFO中。。*/
#define GDMA_OUTFIFO_CNT_L3_CH1    0x0000001F
#define GDMA_OUTFIFO_CNT_L3_CH1_M  ((GDMA_OUTFIFO_CNT_L3_CH1_V)<<(GDMA_OUTFIFO_CNT_L3_CH1_S))
#define GDMA_OUTFIFO_CNT_L3_CH1_V  0x1F
#define GDMA_OUTFIFO_CNT_L3_CH1_S  18
/* GDMA_OUTFIFO_CNT_L2_CH1:RO；比特位置：[17:11]；默认值：7'b0；*/
/*描述：寄存器将数据的字节数存储在Tx信道1的L2 Tx FIFO中。。*/
#define GDMA_OUTFIFO_CNT_L2_CH1    0x0000007F
#define GDMA_OUTFIFO_CNT_L2_CH1_M  ((GDMA_OUTFIFO_CNT_L2_CH1_V)<<(GDMA_OUTFIFO_CNT_L2_CH1_S))
#define GDMA_OUTFIFO_CNT_L2_CH1_V  0x7F
#define GDMA_OUTFIFO_CNT_L2_CH1_S  11
/* GDMA_OUTFIFO_CNT_L1_CH1:RO；比特位置：[10:6]；默认值：5’b0；*/
/*描述：寄存器将数据的字节数存储在Tx信道1的L1 Tx FIFO中。。*/
#define GDMA_OUTFIFO_CNT_L1_CH1    0x0000001F
#define GDMA_OUTFIFO_CNT_L1_CH1_M  ((GDMA_OUTFIFO_CNT_L1_CH1_V)<<(GDMA_OUTFIFO_CNT_L1_CH1_S))
#define GDMA_OUTFIFO_CNT_L1_CH1_V  0x1F
#define GDMA_OUTFIFO_CNT_L1_CH1_S  6
/* GDMA_OUTFIFO_EMPTY_L3_CH1:RO；位位置：[5]；默认值：1’b1；*/
/*描述：Tx信道1的L3 Tx FIFO空信号。。*/
#define GDMA_OUTFIFO_EMPTY_L3_CH1    (BIT(5))
#define GDMA_OUTFIFO_EMPTY_L3_CH1_M  (BIT(5))
#define GDMA_OUTFIFO_EMPTY_L3_CH1_V  0x1
#define GDMA_OUTFIFO_EMPTY_L3_CH1_S  5
/* GDMA_OUTFIFO_FULL_L3_CH1:RO；位位置：[4]；默认值：1’b0；*/
/*描述：Tx信道1的L3 Tx FIFO满信号。。*/
#define GDMA_OUTFIFO_FULL_L3_CH1    (BIT(4))
#define GDMA_OUTFIFO_FULL_L3_CH1_M  (BIT(4))
#define GDMA_OUTFIFO_FULL_L3_CH1_V  0x1
#define GDMA_OUTFIFO_FULL_L3_CH1_S  4
/* GDMA_OUTFIFO_EMPTY_L2_CH1:RO；位位置：[3]；默认值：1’b1；*/
/*描述：Tx信道1的L2 Tx FIFO空信号。。*/
#define GDMA_OUTFIFO_EMPTY_L2_CH1    (BIT(3))
#define GDMA_OUTFIFO_EMPTY_L2_CH1_M  (BIT(3))
#define GDMA_OUTFIFO_EMPTY_L2_CH1_V  0x1
#define GDMA_OUTFIFO_EMPTY_L2_CH1_S  3
/* GDMA_OUTFIFO_FULL_L2_CH1:RO；位位置：[2]；默认值：1’b0；*/
/*描述：Tx信道1的L2 Tx FIFO满信号。。*/
#define GDMA_OUTFIFO_FULL_L2_CH1    (BIT(2))
#define GDMA_OUTFIFO_FULL_L2_CH1_M  (BIT(2))
#define GDMA_OUTFIFO_FULL_L2_CH1_V  0x1
#define GDMA_OUTFIFO_FULL_L2_CH1_S  2
/* GDMA_OUTFIFO_EMPTY_L1_CH1:RO；位位置：[1]；默认值：1’b1；*/
/*描述：Tx信道1的L1 Tx FIFO空信号。。*/
#define GDMA_OUTFIFO_EMPTY_L1_CH1    (BIT(1))
#define GDMA_OUTFIFO_EMPTY_L1_CH1_M  (BIT(1))
#define GDMA_OUTFIFO_EMPTY_L1_CH1_V  0x1
#define GDMA_OUTFIFO_EMPTY_L1_CH1_S  1
/* GDMA_OUTFIFO_FULL_L1_CH1:RO；位位置：[0]；默认值：1’b0；*/
/*描述：Tx信道1的L1 Tx FIFO完整信号。。*/
#define GDMA_OUTFIFO_FULL_L1_CH1    (BIT(0))
#define GDMA_OUTFIFO_FULL_L1_CH1_M  (BIT(0))
#define GDMA_OUTFIFO_FULL_L1_CH1_V  0x1
#define GDMA_OUTFIFO_FULL_L1_CH1_S  0

#define GDMA_OUT_PUSH_CH1_REG          (DR_REG_GDMA_BASE + 0x13C)
/* GDMA_OUTFIFO_PUSH_CH1:R/W/SC；位位置：[9]；默认值：1'0；*/
/*description:设置此位以将数据推入DMA FIFO。。*/
#define GDMA_OUTFIFO_PUSH_CH1    (BIT(9))
#define GDMA_OUTFIFO_PUSH_CH1_M  (BIT(9))
#define GDMA_OUTFIFO_PUSH_CH1_V  0x1
#define GDMA_OUTFIFO_PUSH_CH1_S  9
/* GDMA_OUTFIFO_WDATA_CH1:R/W；位位置：[8:0]；默认值：9'0；*/
/*description:此寄存器存储需要推入DMA FIFO的数据。。*/
#define GDMA_OUTFIFO_WDATA_CH1    0x000001FF
#define GDMA_OUTFIFO_WDATA_CH1_M  ((GDMA_OUTFIFO_WDATA_CH1_V)<<(GDMA_OUTFIFO_WDATA_CH1_S))
#define GDMA_OUTFIFO_WDATA_CH1_V  0x1FF
#define GDMA_OUTFIFO_WDATA_CH1_S  0

#define GDMA_OUT_LINK_CH1_REG          (DR_REG_GDMA_BASE + 0x140)
/* GDMA_OUTLINK_PARK_CH1:RO；位位置：[23]；默认值：1'h1；*/
/*描述：1:outlink描述符的FSM处于空闲状态。0:outlink描述符的FSM正在工作。。*/
#define GDMA_OUTLINK_PARK_CH1    (BIT(23))
#define GDMA_OUTLINK_PARK_CH1_M  (BIT(23))
#define GDMA_OUTLINK_PARK_CH1_V  0x1
#define GDMA_OUTLINK_PARK_CH1_S  23
/* GDMA_OUTLINK_RESTART_CH1:R/W/SC；位位置：[22]；默认值：1’b0；*/
/*description:设置此位以从上一个地址重新启动新的outlink。*/
#define GDMA_OUTLINK_RESTART_CH1    (BIT(22))
#define GDMA_OUTLINK_RESTART_CH1_M  (BIT(22))
#define GDMA_OUTLINK_RESTART_CH1_V  0x1
#define GDMA_OUTLINK_RESTART_CH1_S  22
/* GDMA_OUTLINK_START_CH1:R/W/SC；位位置：[21]；默认值：1’b0；*/
/*description:设置此位以开始处理outlink描述符。。*/
#define GDMA_OUTLINK_START_CH1    (BIT(21))
#define GDMA_OUTLINK_START_CH1_M  (BIT(21))
#define GDMA_OUTLINK_START_CH1_V  0x1
#define GDMA_OUTLINK_START_CH1_S  21
/* GDMA_OUTLINK_STOP_CH1:R/W/SC；位位置：[20]；默认值：1’b0；*/
/*description:设置此位以停止处理outlink描述符。。*/
#define GDMA_OUTLINK_STOP_CH1    (BIT(20))
#define GDMA_OUTLINK_STOP_CH1_M  (BIT(20))
#define GDMA_OUTLINK_STOP_CH1_V  0x1
#define GDMA_OUTLINK_STOP_CH1_S  20
/* GDMA_OUTLINK_ADDR_CH1:R/W；比特位置：[19:0]；默认值：20'00；*/
/*description:此寄存器存储第一个outlink描述符地址的20个最低有效位。。*/
#define GDMA_OUTLINK_ADDR_CH1    0x000FFFFF
#define GDMA_OUTLINK_ADDR_CH1_M  ((GDMA_OUTLINK_ADDR_CH1_V)<<(GDMA_OUTLINK_ADDR_CH1_S))
#define GDMA_OUTLINK_ADDR_CH1_V  0xFFFFF
#define GDMA_OUTLINK_ADDR_CH1_S  0

#define GDMA_OUT_STATE_CH1_REG          (DR_REG_GDMA_BASE + 0x144)
/* GDMA_OUT_STATE_CH1:RO；比特位置：[22:20]；默认值：3'b0；*/
/*description:保留。*/
#define GDMA_OUT_STATE_CH1    0x00000007
#define GDMA_OUT_STATE_CH1_M  ((GDMA_OUT_STATE_CH1_V)<<(GDMA_OUT_STATE_CH1_S))
#define GDMA_OUT_STATE_CH1_V  0x7
#define GDMA_OUT_STATE_CH1_S  20
/* GDMA_OUT_DSCR_STATE_CH1:RO；比特位置：[19:18]；默认值：2’b0；*/
/*description:保留。*/
#define GDMA_OUT_DSCR_STATE_CH1    0x00000003
#define GDMA_OUT_DSCR_STATE_CH1_M  ((GDMA_OUT_DSCR_STATE_CH1_V)<<(GDMA_OUT_DSCR_STATE_CH1_S))
#define GDMA_OUT_DSCR_STATE_CH1_V  0x3
#define GDMA_OUT_DSCR_STATE_CH1_S  18
/* GDMA_OUTLINK_DSCR_ADDR_CH1:RO；比特位置：[17:00]；默认值：18'b0；*/
/*description:此寄存器存储当前outlink描述符的地址。。*/
#define GDMA_OUTLINK_DSCR_ADDR_CH1    0x0003FFFF
#define GDMA_OUTLINK_DSCR_ADDR_CH1_M  ((GDMA_OUTLINK_DSCR_ADDR_CH1_V)<<(GDMA_OUTLINK_DSCR_ADDR_CH1_S))
#define GDMA_OUTLINK_DSCR_ADDR_CH1_V  0x3FFFF
#define GDMA_OUTLINK_DSCR_ADDR_CH1_S  0

#define GDMA_OUT_EOF_DES_ADDR_CH1_REG          (DR_REG_GDMA_BASE + 0x148)
/* GDMA_OUT_EOF_DES_ADDR_CH1:RO；位位置：[31:0]；默认值：32'h0；*/
/*description:当此描述符中的EOF位为1时，此寄存器存储outlink描述符的地址。。*/
#define GDMA_OUT_EOF_DES_ADDR_CH1    0xFFFFFFFF
#define GDMA_OUT_EOF_DES_ADDR_CH1_M  ((GDMA_OUT_EOF_DES_ADDR_CH1_V)<<(GDMA_OUT_EOF_DES_ADDR_CH1_S))
#define GDMA_OUT_EOF_DES_ADDR_CH1_V  0xFFFFFFFF
#define GDMA_OUT_EOF_DES_ADDR_CH1_S  0

#define GDMA_OUT_EOF_BFR_DES_ADDR_CH1_REG          (DR_REG_GDMA_BASE + 0x14C)
/* GDMA_OUT_EOF_BFR_DES_ADDR_CH1:RO；位位置：[31:0]；默认值：32'h0；*/
/*description:此寄存器存储最后一个outlink描述符之前的outlink描述符的地址。。*/
#define GDMA_OUT_EOF_BFR_DES_ADDR_CH1    0xFFFFFFFF
#define GDMA_OUT_EOF_BFR_DES_ADDR_CH1_M  ((GDMA_OUT_EOF_BFR_DES_ADDR_CH1_V)<<(GDMA_OUT_EOF_BFR_DES_ADDR_CH1_S))
#define GDMA_OUT_EOF_BFR_DES_ADDR_CH1_V  0xFFFFFFFF
#define GDMA_OUT_EOF_BFR_DES_ADDR_CH1_S  0

#define GDMA_OUT_DSCR_CH1_REG          (DR_REG_GDMA_BASE + 0x150)
/* GDMA_OUTLINK_DSCR_CH1:RO；位位置：[31:0]；默认值：32'b0；*/
/*description:当前outlink描述符y的地址。。*/
#define GDMA_OUTLINK_DSCR_CH1    0xFFFFFFFF
#define GDMA_OUTLINK_DSCR_CH1_M  ((GDMA_OUTLINK_DSCR_CH1_V)<<(GDMA_OUTLINK_DSCR_CH1_S))
#define GDMA_OUTLINK_DSCR_CH1_V  0xFFFFFFFF
#define GDMA_OUTLINK_DSCR_CH1_S  0

#define GDMA_OUT_DSCR_BF0_CH1_REG          (DR_REG_GDMA_BASE + 0x154)
/* GDMA_OUTLINK_DSCR_BF0_CH1:RO；位位置：[31:0]；默认值：32'b0；*/
/*description:最后一个outlink描述符的地址y-1。。*/
#define GDMA_OUTLINK_DSCR_BF0_CH1    0xFFFFFFFF
#define GDMA_OUTLINK_DSCR_BF0_CH1_M  ((GDMA_OUTLINK_DSCR_BF0_CH1_V)<<(GDMA_OUTLINK_DSCR_BF0_CH1_S))
#define GDMA_OUTLINK_DSCR_BF0_CH1_V  0xFFFFFFFF
#define GDMA_OUTLINK_DSCR_BF0_CH1_S  0

#define GDMA_OUT_DSCR_BF1_CH1_REG          (DR_REG_GDMA_BASE + 0x158)
/* GDMA_OUTLINK_DSCR_BF1_CH1:RO；位位置：[31:0]；默认值：32'b0；*/
/*description:倒数第二个内联描述符x-2的地址。。*/
#define GDMA_OUTLINK_DSCR_BF1_CH1    0xFFFFFFFF
#define GDMA_OUTLINK_DSCR_BF1_CH1_M  ((GDMA_OUTLINK_DSCR_BF1_CH1_V)<<(GDMA_OUTLINK_DSCR_BF1_CH1_S))
#define GDMA_OUTLINK_DSCR_BF1_CH1_V  0xFFFFFFFF
#define GDMA_OUTLINK_DSCR_BF1_CH1_S  0

#define GDMA_OUT_WIGHT_CH1_REG          (DR_REG_GDMA_BASE + 0x15C)
/* GDMA_TX_WEIGHT_CH1:R/W；位位置：[11:8]；默认值：4'hf；*/
/*description:Tx信道1的权重。*/
#define GDMA_TX_WEIGHT_CH1    0x0000000F
#define GDMA_TX_WEIGHT_CH1_M  ((GDMA_TX_WEIGHT_CH1_V)<<(GDMA_TX_WEIGHT_CH1_S))
#define GDMA_TX_WEIGHT_CH1_V  0xF
#define GDMA_TX_WEIGHT_CH1_S  8

#define GDMA_OUT_PRI_CH1_REG          (DR_REG_GDMA_BASE + 0x164)
/* GDMA_TX_PRI_CH1:R/W；位位置：[3:0]；默认值：4'b0；*/
/*description:Tx信道1的优先级。值越大，优先级越高。。*/
#define GDMA_TX_PRI_CH1    0x0000000F
#define GDMA_TX_PRI_CH1_M  ((GDMA_TX_PRI_CH1_V)<<(GDMA_TX_PRI_CH1_S))
#define GDMA_TX_PRI_CH1_V  0xF
#define GDMA_TX_PRI_CH1_S  0

#define GDMA_OUT_PERI_SEL_CH1_REG          (DR_REG_GDMA_BASE + 0x168)
/* GDMA_PERI_OUT_SEL_CH1:R/W；比特位置：[5:0]；默认值：6'h3f；*/
/*描述：此寄存器用于为Tx通道1.0:SPI2.1:SPI3.2:UHCI0.3:I2S0.4:I2S1.5:LCD_CAM选择外围设备。6： AES。7： 沙。8： ADC_DAC。9： 每立方米。；7： AES。8： 沙。9： ADC_DAC。。*/
#define GDMA_PERI_OUT_SEL_CH1    0x0000003F
#define GDMA_PERI_OUT_SEL_CH1_M  ((GDMA_PERI_OUT_SEL_CH1_V)<<(GDMA_PERI_OUT_SEL_CH1_S))
#define GDMA_PERI_OUT_SEL_CH1_V  0x3F
#define GDMA_PERI_OUT_SEL_CH1_S  0

#define GDMA_IN_CONF0_CH2_REG          (DR_REG_GDMA_BASE + 0x180)
/* GDMA_MEM_TRANS_EN_CH2:R/W；位位置：[4]；默认值：1’b0；*/
/*description:将此位设置为1，以启用通过DMA将数据从存储器自动传输到存储器。。*/
#define GDMA_MEM_TRANS_EN_CH2    (BIT(4))
#define GDMA_MEM_TRANS_EN_CH2_M  (BIT(4))
#define GDMA_MEM_TRANS_EN_CH2_V  0x1
#define GDMA_MEM_TRANS_EN_CH2_S  4
/* GDMA_IN_DATA_BURST_EN_CH2:R/W；位位置：[3]；默认值：1’b0；*/
/*description:将此位设置为1，以在访问内部SRAM时启用接收数据的Rx通道2的INCR突发传输。*/
#define GDMA_IN_DATA_BURST_EN_CH2    (BIT(3))
#define GDMA_IN_DATA_BURST_EN_CH2_M  (BIT(3))
#define GDMA_IN_DATA_BURST_EN_CH2_V  0x1
#define GDMA_IN_DATA_BURST_EN_CH2_S  3
/* GDMA_INDSCR_BURST_EN_CH2:R/W；位位置：[2]；默认值：1’b0；*/
/*description:当访问内部SRAM时，将此位设置为1以启用Rx通道2读取链路描述符的INCR突发传输。*/
#define GDMA_INDSCR_BURST_EN_CH2    (BIT(2))
#define GDMA_INDSCR_BURST_EN_CH2_M  (BIT(2))
#define GDMA_INDSCR_BURST_EN_CH2_V  0x1
#define GDMA_INDSCR_BURST_EN_CH2_S  2
/* GDMA_IN_LOOP_TEST_CH2:R/W；位位置：[1]；默认值：1’b0；*/
/*description:保留。*/
#define GDMA_IN_LOOP_TEST_CH2    (BIT(1))
#define GDMA_IN_LOOP_TEST_CH2_M  (BIT(1))
#define GDMA_IN_LOOP_TEST_CH2_V  0x1
#define GDMA_IN_LOOP_TEST_CH2_S  1
/* GDMA_IN_RST_CH2:R/W；位位置：[0]；默认值：1'0；*/
/*描述：此位用于重置DMA通道2 Rx FSM和Rx FIFO指针。。*/
#define GDMA_IN_RST_CH2    (BIT(0))
#define GDMA_IN_RST_CH2_M  (BIT(0))
#define GDMA_IN_RST_CH2_V  0x1
#define GDMA_IN_RST_CH2_S  0

#define GDMA_IN_CONF1_CH2_REG          (DR_REG_GDMA_BASE + 0x184)
/* GDMA_IN_EXT_MEM_BK_SIZE_CH2:R/W；比特位置：[14:13]；默认值：2’b0；*/
/*描述：DMA访问外部SRAM时Rx通道2的块大小。0:16字节1:32字节2/3:保留。*/
#define GDMA_IN_EXT_MEM_BK_SIZE_CH2    0x00000003
#define GDMA_IN_EXT_MEM_BK_SIZE_CH2_M  ((GDMA_IN_EXT_MEM_BK_SIZE_CH2_V)<<(GDMA_IN_EXT_MEM_BK_SIZE_CH2_S))
#define GDMA_IN_EXT_MEM_BK_SIZE_CH2_V  0x3
#define GDMA_IN_EXT_MEM_BK_SIZE_CH2_S  13
/* GDMA_IN_CHECK_OWNER_CH2:R/W；位位置：[12]；默认值：1’b0；*/
/*description:设置此位以启用检查链接描述符的所有者属性。。*/
#define GDMA_IN_CHECK_OWNER_CH2    (BIT(12))
#define GDMA_IN_CHECK_OWNER_CH2_M  (BIT(12))
#define GDMA_IN_CHECK_OWNER_CH2_V  0x1
#define GDMA_IN_CHECK_OWNER_CH2_S  12
/* GDMA_DMA_INFIFO_FULL_THRS_CH2:R/W；位位置：[11:0]；默认值：12'hc；*/
/*描述：当Rx FIFO中的Rx通道2接收字节数达到寄存器值时，此寄存器用于生成INFIFO_FULL_WM_INT中断。。*/
#define GDMA_DMA_INFIFO_FULL_THRS_CH2    0x00000FFF
#define GDMA_DMA_INFIFO_FULL_THRS_CH2_M  ((GDMA_DMA_INFIFO_FULL_THRS_CH2_V)<<(GDMA_DMA_INFIFO_FULL_THRS_CH2_S))
#define GDMA_DMA_INFIFO_FULL_THRS_CH2_V  0xFFF
#define GDMA_DMA_INFIFO_FULL_THRS_CH2_S  0

#define GDMA_IN_INT_RAW_CH2_REG          (DR_REG_GDMA_BASE + 0x188)
/* GDMA_INFIFO_udfl_L3_CH2_INT_RAW:R/WTC/SS；位位置：[9]；默认值：1’b0；*/
/*描述：当Rx通道2的第3级fifo未满流时，此原始中断位变为高电平。*/
#define GDMA_INFIFO_UDF_L3_CH2_INT_RAW    (BIT(9))
#define GDMA_INFIFO_UDF_L3_CH2_INT_RAW_M  (BIT(9))
#define GDMA_INFIFO_UDF_L3_CH2_INT_RAW_V  0x1
#define GDMA_INFIFO_UDF_L3_CH2_INT_RAW_S  9
/* GDMA_INFIFO_off_L3_CH2_INT_RAW:R/WTC/SS；位位置：[8]；默认值：1’b0；*/
/*描述：当Rx通道2的3级fifo等流量时，此原始中断位变为高电平。*/
#define GDMA_INFIFO_OVF_L3_CH2_INT_RAW    (BIT(8))
#define GDMA_INFIFO_OVF_L3_CH2_INT_RAW_M  (BIT(8))
#define GDMA_INFIFO_OVF_L3_CH2_INT_RAW_V  0x1
#define GDMA_INFIFO_OVF_L3_CH2_INT_RAW_S  8
/* GDMA_INFIFO_UDF_l_CH2_INT_RAW:R/WTC/SS；位位置：[7]；默认值：1’b0；*/
/*描述：当Rx通道2的第1级fifo未满流时，此原始中断位变为高电平。*/
#define GDMA_INFIFO_UDF_L1_CH2_INT_RAW    (BIT(7))
#define GDMA_INFIFO_UDF_L1_CH2_INT_RAW_M  (BIT(7))
#define GDMA_INFIFO_UDF_L1_CH2_INT_RAW_V  0x1
#define GDMA_INFIFO_UDF_L1_CH2_INT_RAW_S  7
/* GDMA_INFIFO_OVF_l_CH2_INT_RAW:R/WTC/SS；位位置：[6]；默认值：1’b0；*/
/*描述：当Rx通道2的1级fifo等流量时，此原始中断位变为高电平。*/
#define GDMA_INFIFO_OVF_L1_CH2_INT_RAW    (BIT(6))
#define GDMA_INFIFO_OVF_L1_CH2_INT_RAW_M  (BIT(6))
#define GDMA_INFIFO_OVF_L1_CH2_INT_RAW_V  0x1
#define GDMA_INFIFO_OVF_L1_CH2_INT_RAW_S  6
/* GDMA_INFIFO_FULL_WM_CH2_INT_RAW:R/WTC/SS；位位置：[5]；默认值：1’b0；*/
/*描述：当接收的数据字节数达到信道2的Rx FIFO中REG_DMA_INFIFO_FULL_THS_CH0配置的阈值时，原始中断位变为高电平。。*/
#define GDMA_INFIFO_FULL_WM_CH2_INT_RAW    (BIT(5))
#define GDMA_INFIFO_FULL_WM_CH2_INT_RAW_M  (BIT(5))
#define GDMA_INFIFO_FULL_WM_CH2_INT_RAW_V  0x1
#define GDMA_INFIFO_FULL_WM_CH2_INT_RAW_S  5
/* GDMA_IN_DSCR_EMPTY-CH2_INT_RAW:R/WTC/SS；位位置：[4]；默认值：1’b0；*/
/*描述：当inlink指向的Rx缓冲区已满且未完成接收数据时，原始中断位变为高电平，但Rx通道2没有更多的inlink。。*/
#define GDMA_IN_DSCR_EMPTY_CH2_INT_RAW    (BIT(4))
#define GDMA_IN_DSCR_EMPTY_CH2_INT_RAW_M  (BIT(4))
#define GDMA_IN_DSCR_EMPTY_CH2_INT_RAW_V  0x1
#define GDMA_IN_DSCR_EMPTY_CH2_INT_RAW_S  4
/* GDMA_IN_DSCR_ERR_CH2_INT_RAW:R/WTC/SS；位位置：[3]；默认值：1’b0；*/
/*描述：当检测到内联描述符错误时，原始中断位变为高电平，包括所有者错误、Rx通道2的内联描述符的第二个和第三个字错误。。*/
#define GDMA_IN_DSCR_ERR_CH2_INT_RAW    (BIT(3))
#define GDMA_IN_DSCR_ERR_CH2_INT_RAW_M  (BIT(3))
#define GDMA_IN_DSCR_ERR_CH2_INT_RAW_V  0x1
#define GDMA_IN_DSCR_ERR_CH2_INT_RAW_S  3
/* GDMA_IN_ERR_EOF_CH2_INT_RAW:R/WTC/SS；位位置：[2]；默认值：1’b0；*/
/*描述：当仅在外围设备为Rx信道2的UHCI0的情况下检测到数据错误时，原始中断位变为高电平。对于其他外围设备，保留此原始中断。。*/
#define GDMA_IN_ERR_EOF_CH2_INT_RAW    (BIT(2))
#define GDMA_IN_ERR_EOF_CH2_INT_RAW_M  (BIT(2))
#define GDMA_IN_ERR_EOF_CH2_INT_RAW_V  0x1
#define GDMA_IN_ERR_EOF_CH2_INT_RAW_S  2
/* GDMA_IN_SUC_EOF_CH2_INT_RAW:R/WTC/SS；位位置：[1]；默认值：1’b0；*/
/*描述：当接收到Rx通道2的一个内联描述符指向的最后一个数据时，原始中断位变为高电平。对于UHCI0，当接收到一个内联描述符指向的最后数据且Rx通道0未检测到数据错误时，原始断开位变为低电平。。*/
#define GDMA_IN_SUC_EOF_CH2_INT_RAW    (BIT(1))
#define GDMA_IN_SUC_EOF_CH2_INT_RAW_M  (BIT(1))
#define GDMA_IN_SUC_EOF_CH2_INT_RAW_V  0x1
#define GDMA_IN_SUC_EOF_CH2_INT_RAW_S  1
/* GDMA_IN_DONE_CH2_INT_RAW:R/WTC/SS；位位置：[0]；默认值：1’b0；*/
/*描述：当接收到Rx通道2的一个内联描述符指向的最后一个数据时，原始中断位变为高电平。。*/
#define GDMA_IN_DONE_CH2_INT_RAW    (BIT(0))
#define GDMA_IN_DONE_CH2_INT_RAW_M  (BIT(0))
#define GDMA_IN_DONE_CH2_INT_RAW_V  0x1
#define GDMA_IN_DONE_CH2_INT_RAW_S  0

#define GDMA_IN_INT_ST_CH2_REG          (DR_REG_GDMA_BASE + 0x18C)
/* GDMA_INFIFO_udfl3_CH2_INT_ST:RO；位位置：[9]；默认值：1’b0；*/
/*description:INFIFO_UDF_L3_CH_INT中断的原始中断状态位。。*/
#define GDMA_INFIFO_UDF_L3_CH2_INT_ST    (BIT(9))
#define GDMA_INFIFO_UDF_L3_CH2_INT_ST_M  (BIT(9))
#define GDMA_INFIFO_UDF_L3_CH2_INT_ST_V  0x1
#define GDMA_INFIFO_UDF_L3_CH2_INT_ST_S  9
/* GDMA_INFIFO_off_13_CH2_INT_ST:RO；位位置：[8]；默认值：1’b0；*/
/*description:INFIFO_OVF_L3_CH_INT中断的原始中断状态位。。*/
#define GDMA_INFIFO_OVF_L3_CH2_INT_ST    (BIT(8))
#define GDMA_INFIFO_OVF_L3_CH2_INT_ST_M  (BIT(8))
#define GDMA_INFIFO_OVF_L3_CH2_INT_ST_V  0x1
#define GDMA_INFIFO_OVF_L3_CH2_INT_ST_S  8
/* GDMA_INFIFO_UDF_1_CH2_INT_ST:RO；位位置：[7]；默认值：1’b0；*/
/*description:INFIFO_UDF_L1_CH_INT中断的原始中断状态位。。*/
#define GDMA_INFIFO_UDF_L1_CH2_INT_ST    (BIT(7))
#define GDMA_INFIFO_UDF_L1_CH2_INT_ST_M  (BIT(7))
#define GDMA_INFIFO_UDF_L1_CH2_INT_ST_V  0x1
#define GDMA_INFIFO_UDF_L1_CH2_INT_ST_S  7
/* GDMA_INFIFO_OVF_l_CH2_INT_ST:RO；位位置：[6]；默认值：1’b0；*/
/*description:INFIFO_OVF_L1_CH_INT中断的原始中断状态位。。*/
#define GDMA_INFIFO_OVF_L1_CH2_INT_ST    (BIT(6))
#define GDMA_INFIFO_OVF_L1_CH2_INT_ST_M  (BIT(6))
#define GDMA_INFIFO_OVF_L1_CH2_INT_ST_V  0x1
#define GDMA_INFIFO_OVF_L1_CH2_INT_ST_S  6
/* GDMA_INFIFO_FULL_WM_CH2_INT_ST:RO；位位置：[5]；默认值：1’b0；*/
/*description:INFIFO_FULL_WM_CH_INT中断的原始中断状态位。。*/
#define GDMA_INFIFO_FULL_WM_CH2_INT_ST    (BIT(5))
#define GDMA_INFIFO_FULL_WM_CH2_INT_ST_M  (BIT(5))
#define GDMA_INFIFO_FULL_WM_CH2_INT_ST_V  0x1
#define GDMA_INFIFO_FULL_WM_CH2_INT_ST_S  5
/* GDMA_IN_DSCR_EMPTY-CH2_INT_ST:RO；位位置：[4]；默认值：1’b0；*/
/*description:IN_DSCR_EMPTY_CH_INT中断的原始中断状态位。。*/
#define GDMA_IN_DSCR_EMPTY_CH2_INT_ST    (BIT(4))
#define GDMA_IN_DSCR_EMPTY_CH2_INT_ST_M  (BIT(4))
#define GDMA_IN_DSCR_EMPTY_CH2_INT_ST_V  0x1
#define GDMA_IN_DSCR_EMPTY_CH2_INT_ST_S  4
/* GDMA_IN_DSCR_ERR_CH2_INT_ST:RO；位位置：[3]；默认值：1’b0；*/
/*description:IN_DSCR_ERR_CH_INT中断的原始中断状态位。。*/
#define GDMA_IN_DSCR_ERR_CH2_INT_ST    (BIT(3))
#define GDMA_IN_DSCR_ERR_CH2_INT_ST_M  (BIT(3))
#define GDMA_IN_DSCR_ERR_CH2_INT_ST_V  0x1
#define GDMA_IN_DSCR_ERR_CH2_INT_ST_S  3
/* GDMA_IN_ERR_EOF_CH2_INT_ST:RO；位位置：[2]；默认值：1’b0；*/
/*description:IN_ERR_EOF_CH_INT中断的原始中断状态位。。*/
#define GDMA_IN_ERR_EOF_CH2_INT_ST    (BIT(2))
#define GDMA_IN_ERR_EOF_CH2_INT_ST_M  (BIT(2))
#define GDMA_IN_ERR_EOF_CH2_INT_ST_V  0x1
#define GDMA_IN_ERR_EOF_CH2_INT_ST_S  2
/* GDMA_IN_SUC_EOF_CH2_INT_ST:RO；位位置：[1]；默认值：1’b0；*/
/*description:IN_SUC_EOF_CH_INT中断的原始中断状态位。。*/
#define GDMA_IN_SUC_EOF_CH2_INT_ST    (BIT(1))
#define GDMA_IN_SUC_EOF_CH2_INT_ST_M  (BIT(1))
#define GDMA_IN_SUC_EOF_CH2_INT_ST_V  0x1
#define GDMA_IN_SUC_EOF_CH2_INT_ST_S  1
/* GDMA_IN_DONE_CH2_INT_ST:RO；位位置：[0]；默认值：1’b0；*/
/*description:IN_DONE_CH_INT中断的原始中断状态位。。*/
#define GDMA_IN_DONE_CH2_INT_ST    (BIT(0))
#define GDMA_IN_DONE_CH2_INT_ST_M  (BIT(0))
#define GDMA_IN_DONE_CH2_INT_ST_V  0x1
#define GDMA_IN_DONE_CH2_INT_ST_S  0

#define GDMA_IN_INT_ENA_CH2_REG          (DR_REG_GDMA_BASE + 0x190)
/* GDMA_INFIFO_UDF_13_CH2_INT_ENA:R/W；位位置：[9]；默认值：1’b0；*/
/*description:INFIFO_UDF_L3_CH_INT中断的中断启用位。。*/
#define GDMA_INFIFO_UDF_L3_CH2_INT_ENA    (BIT(9))
#define GDMA_INFIFO_UDF_L3_CH2_INT_ENA_M  (BIT(9))
#define GDMA_INFIFO_UDF_L3_CH2_INT_ENA_V  0x1
#define GDMA_INFIFO_UDF_L3_CH2_INT_ENA_S  9
/* GDMA_INFIFO_off_13_CH2_INT_ENA:R/W；位位置：[8]；默认值：1’b0；*/
/*description:INFIFO_OVF_L3_CH_INT中断的中断启用位。。*/
#define GDMA_INFIFO_OVF_L3_CH2_INT_ENA    (BIT(8))
#define GDMA_INFIFO_OVF_L3_CH2_INT_ENA_M  (BIT(8))
#define GDMA_INFIFO_OVF_L3_CH2_INT_ENA_V  0x1
#define GDMA_INFIFO_OVF_L3_CH2_INT_ENA_S  8
/* GDMA_INFIFO_UDF_L1_CH2_INT_ENA:R/W；位位置：[7]；默认值：1’b0；*/
/*description:INFIFO_UDF_L1_CH_INT中断的中断启用位。。*/
#define GDMA_INFIFO_UDF_L1_CH2_INT_ENA    (BIT(7))
#define GDMA_INFIFO_UDF_L1_CH2_INT_ENA_M  (BIT(7))
#define GDMA_INFIFO_UDF_L1_CH2_INT_ENA_V  0x1
#define GDMA_INFIFO_UDF_L1_CH2_INT_ENA_S  7
/* GDMA_INFIFO_off_L1_CH2_INT_ENA:R/W；位位置：[6]；默认值：1’b0；*/
/*description:INFIFO_OVF_L1_CH_INT中断的中断启用位。。*/
#define GDMA_INFIFO_OVF_L1_CH2_INT_ENA    (BIT(6))
#define GDMA_INFIFO_OVF_L1_CH2_INT_ENA_M  (BIT(6))
#define GDMA_INFIFO_OVF_L1_CH2_INT_ENA_V  0x1
#define GDMA_INFIFO_OVF_L1_CH2_INT_ENA_S  6
/* GDMA_INFIFO_FULL_WM_CH2_INT_ENA:R/W；位位置：[5]；默认值：1’b0；*/
/*description:INFIFO_FULL_WM_CH_INT中断的中断启用位。。*/
#define GDMA_INFIFO_FULL_WM_CH2_INT_ENA    (BIT(5))
#define GDMA_INFIFO_FULL_WM_CH2_INT_ENA_M  (BIT(5))
#define GDMA_INFIFO_FULL_WM_CH2_INT_ENA_V  0x1
#define GDMA_INFIFO_FULL_WM_CH2_INT_ENA_S  5
/* GDMA_IN_DSCR_EMPTY-CH2_INT_ENA:R/W；位位置：[4]；默认值：1’b0；*/
/*description:IN_DSCR_EMPTY_CH_INT中断的中断启用位。。*/
#define GDMA_IN_DSCR_EMPTY_CH2_INT_ENA    (BIT(4))
#define GDMA_IN_DSCR_EMPTY_CH2_INT_ENA_M  (BIT(4))
#define GDMA_IN_DSCR_EMPTY_CH2_INT_ENA_V  0x1
#define GDMA_IN_DSCR_EMPTY_CH2_INT_ENA_S  4
/* GDMA_IN_DSCR_ERR_CH2_INT_ENA:R/W；位位置：[3]；默认值：1’b0；*/
/*description:IN_DSCR_ERR_CH_INT中断的中断启用位。。*/
#define GDMA_IN_DSCR_ERR_CH2_INT_ENA    (BIT(3))
#define GDMA_IN_DSCR_ERR_CH2_INT_ENA_M  (BIT(3))
#define GDMA_IN_DSCR_ERR_CH2_INT_ENA_V  0x1
#define GDMA_IN_DSCR_ERR_CH2_INT_ENA_S  3
/* GDMA_IN_ERR_EOF_CH2_INT_ENA:R/W；位位置：[2]；默认值：1’b0；*/
/*description:IN_ERR_EOF_CH_INT中断的中断启用位。。*/
#define GDMA_IN_ERR_EOF_CH2_INT_ENA    (BIT(2))
#define GDMA_IN_ERR_EOF_CH2_INT_ENA_M  (BIT(2))
#define GDMA_IN_ERR_EOF_CH2_INT_ENA_V  0x1
#define GDMA_IN_ERR_EOF_CH2_INT_ENA_S  2
/* GDMA_IN_SUC_EOF_CH2_INT_ENA:R/W；位位置：[1]；默认值：1’b0；*/
/*description:IN_SUC_EOF_CH_INT中断的中断启用位。。*/
#define GDMA_IN_SUC_EOF_CH2_INT_ENA    (BIT(1))
#define GDMA_IN_SUC_EOF_CH2_INT_ENA_M  (BIT(1))
#define GDMA_IN_SUC_EOF_CH2_INT_ENA_V  0x1
#define GDMA_IN_SUC_EOF_CH2_INT_ENA_S  1
/* GDMA_IN_DONE_CH2_INT_ENA:R/W；位位置：[0]；默认值：1’b0；*/
/*description:IN_DONE_CH_INT中断的中断启用位。。*/
#define GDMA_IN_DONE_CH2_INT_ENA    (BIT(0))
#define GDMA_IN_DONE_CH2_INT_ENA_M  (BIT(0))
#define GDMA_IN_DONE_CH2_INT_ENA_V  0x1
#define GDMA_IN_DONE_CH2_INT_ENA_S  0

#define GDMA_IN_INT_CLR_CH2_REG          (DR_REG_GDMA_BASE + 0x194)
/* GDMA_INFIFO_udfl3_CH2_INT_CLR:WT；位位置：[9]；默认值：1’b0；*/
/*description:设置此位以清除INFIFO_UDF_L3_CH_INT中断。。*/
#define GDMA_INFIFO_UDF_L3_CH2_INT_CLR    (BIT(9))
#define GDMA_INFIFO_UDF_L3_CH2_INT_CLR_M  (BIT(9))
#define GDMA_INFIFO_UDF_L3_CH2_INT_CLR_V  0x1
#define GDMA_INFIFO_UDF_L3_CH2_INT_CLR_S  9
/* GDMA_INFIFO_off_13_CH2_INT_CLR:WT；位位置：[8]；默认值：1’b0；*/
/*description:设置此位以清除INFIFO_OVF_L3_CH_INT中断。。*/
#define GDMA_INFIFO_OVF_L3_CH2_INT_CLR    (BIT(8))
#define GDMA_INFIFO_OVF_L3_CH2_INT_CLR_M  (BIT(8))
#define GDMA_INFIFO_OVF_L3_CH2_INT_CLR_V  0x1
#define GDMA_INFIFO_OVF_L3_CH2_INT_CLR_S  8
/* GDMA_INFIFO_UDF_1_CH2_INT_CLR:WT；位位置：[7]；默认值：1’b0；*/
/*description:设置此位以清除INFIFO_UDF_L1_CH_INT中断。。*/
#define GDMA_INFIFO_UDF_L1_CH2_INT_CLR    (BIT(7))
#define GDMA_INFIFO_UDF_L1_CH2_INT_CLR_M  (BIT(7))
#define GDMA_INFIFO_UDF_L1_CH2_INT_CLR_V  0x1
#define GDMA_INFIFO_UDF_L1_CH2_INT_CLR_S  7
/* GDMA_INFIFO_off_L1_CH2_INT_CLR:WT；位位置：[6]；默认值：1’b0；*/
/*description:设置此位以清除INFIFO_OVF_L1_CH_INT中断。。*/
#define GDMA_INFIFO_OVF_L1_CH2_INT_CLR    (BIT(6))
#define GDMA_INFIFO_OVF_L1_CH2_INT_CLR_M  (BIT(6))
#define GDMA_INFIFO_OVF_L1_CH2_INT_CLR_V  0x1
#define GDMA_INFIFO_OVF_L1_CH2_INT_CLR_S  6
/* GDMA_DMA_INFIFO_FULL_WM_CH2_INT_CLR:WT；位位置：[5]；默认值：1’b0；*/
/*description:设置此位以清除INFIFO_FULL_WM_CH_INT中断。。*/
#define GDMA_DMA_INFIFO_FULL_WM_CH2_INT_CLR    (BIT(5))
#define GDMA_DMA_INFIFO_FULL_WM_CH2_INT_CLR_M  (BIT(5))
#define GDMA_DMA_INFIFO_FULL_WM_CH2_INT_CLR_V  0x1
#define GDMA_DMA_INFIFO_FULL_WM_CH2_INT_CLR_S  5
/* GDMA_IN_DSCR_EMPTY-CH2_INT_CLR:WT；位位置：[4]；默认值：1’b0；*/
/*description:设置此位以清除IN_DSCR_EMPTY_CH_INT中断。。*/
#define GDMA_IN_DSCR_EMPTY_CH2_INT_CLR    (BIT(4))
#define GDMA_IN_DSCR_EMPTY_CH2_INT_CLR_M  (BIT(4))
#define GDMA_IN_DSCR_EMPTY_CH2_INT_CLR_V  0x1
#define GDMA_IN_DSCR_EMPTY_CH2_INT_CLR_S  4
/* GDMA_IN_DSCR_ERR_CH2_INT_CLR:WT；位位置：[3]；默认值：1’b0；*/
/*description:设置此位以清除IN_DSCR_ERR_CH_INT中断。。*/
#define GDMA_IN_DSCR_ERR_CH2_INT_CLR    (BIT(3))
#define GDMA_IN_DSCR_ERR_CH2_INT_CLR_M  (BIT(3))
#define GDMA_IN_DSCR_ERR_CH2_INT_CLR_V  0x1
#define GDMA_IN_DSCR_ERR_CH2_INT_CLR_S  3
/* GDMA_IN_ERR_EOF_CH2_INT_CLR:WT；位位置：[2]；默认值：1’b0；*/
/*description:设置此位以清除IN_ERR_EOF_CH_INT中断。。*/
#define GDMA_IN_ERR_EOF_CH2_INT_CLR    (BIT(2))
#define GDMA_IN_ERR_EOF_CH2_INT_CLR_M  (BIT(2))
#define GDMA_IN_ERR_EOF_CH2_INT_CLR_V  0x1
#define GDMA_IN_ERR_EOF_CH2_INT_CLR_S  2
/* GDMA_IN_SUC_EOF_CH2_INT_CLR:WT；位位置：[1]；默认值：1’b0；*/
/*description:设置此位以清除IN_SUC_EOF_CH_INT中断。。*/
#define GDMA_IN_SUC_EOF_CH2_INT_CLR    (BIT(1))
#define GDMA_IN_SUC_EOF_CH2_INT_CLR_M  (BIT(1))
#define GDMA_IN_SUC_EOF_CH2_INT_CLR_V  0x1
#define GDMA_IN_SUC_EOF_CH2_INT_CLR_S  1
/* GDMA_IN_DONE_CH2_INT_CLR:WT；位位置：[0]；默认值：1’b0；*/
/*description:设置此位以清除IN_DONE_CH_INT中断。。*/
#define GDMA_IN_DONE_CH2_INT_CLR    (BIT(0))
#define GDMA_IN_DONE_CH2_INT_CLR_M  (BIT(0))
#define GDMA_IN_DONE_CH2_INT_CLR_V  0x1
#define GDMA_IN_DONE_CH2_INT_CLR_S  0

#define GDMA_INFIFO_STATUS_CH2_REG          (DR_REG_GDMA_BASE + 0x198)
/* GDMA_IN_BUF_HUNGRY_CH2:RO；位位置：[28]；默认值：1’b0；*/
/*description:保留。*/
#define GDMA_IN_BUF_HUNGRY_CH2    (BIT(28))
#define GDMA_IN_BUF_HUNGRY_CH2_M  (BIT(28))
#define GDMA_IN_BUF_HUNGRY_CH2_V  0x1
#define GDMA_IN_BUF_HUNGRY_CH2_S  28
/* GDMA_IN_REMAIN_UNDER_4B_L3_CH2:RO；位位置：[27]；默认值：1’b1；*/
/*description:保留。*/
#define GDMA_IN_REMAIN_UNDER_4B_L3_CH2    (BIT(27))
#define GDMA_IN_REMAIN_UNDER_4B_L3_CH2_M  (BIT(27))
#define GDMA_IN_REMAIN_UNDER_4B_L3_CH2_V  0x1
#define GDMA_IN_REMAIN_UNDER_4B_L3_CH2_S  27
/* GDMA_IN_REMAIN_UNDER_3B_L3_CH2:RO；位位置：[26]；默认值：1’b1；*/
/*description:保留。*/
#define GDMA_IN_REMAIN_UNDER_3B_L3_CH2    (BIT(26))
#define GDMA_IN_REMAIN_UNDER_3B_L3_CH2_M  (BIT(26))
#define GDMA_IN_REMAIN_UNDER_3B_L3_CH2_V  0x1
#define GDMA_IN_REMAIN_UNDER_3B_L3_CH2_S  26
/* GDMA_IN_REMAIN_UNDER_2B_L3_CH2:RO；位位置：[25]；默认值：1’b1；*/
/*description:保留。*/
#define GDMA_IN_REMAIN_UNDER_2B_L3_CH2    (BIT(25))
#define GDMA_IN_REMAIN_UNDER_2B_L3_CH2_M  (BIT(25))
#define GDMA_IN_REMAIN_UNDER_2B_L3_CH2_V  0x1
#define GDMA_IN_REMAIN_UNDER_2B_L3_CH2_S  25
/* GDMA_IN_REMAIN_UNDER_1B_L3_CH2:RO；位位置：[24]；默认值：1’b1；*/
/*description:保留。*/
#define GDMA_IN_REMAIN_UNDER_1B_L3_CH2    (BIT(24))
#define GDMA_IN_REMAIN_UNDER_1B_L3_CH2_M  (BIT(24))
#define GDMA_IN_REMAIN_UNDER_1B_L3_CH2_V  0x1
#define GDMA_IN_REMAIN_UNDER_1B_L3_CH2_S  24
/* GDMA_INFIFO_CNT_L3_CH2:RO；比特位置：[23:19]；默认值：5’b0；*/
/*描述：寄存器将数据的字节数存储在Rx通道2的L3 Rx FIFO中。。*/
#define GDMA_INFIFO_CNT_L3_CH2    0x0000001F
#define GDMA_INFIFO_CNT_L3_CH2_M  ((GDMA_INFIFO_CNT_L3_CH2_V)<<(GDMA_INFIFO_CNT_L3_CH2_S))
#define GDMA_INFIFO_CNT_L3_CH2_V  0x1F
#define GDMA_INFIFO_CNT_L3_CH2_S  19
/* GDMA_INFIFO_CNT_L2_CH2:RO；比特位置：[18:12]；默认值：7'b0；*/
/*描述：寄存器将数据的字节数存储在Rx信道2的L2 Rx FIFO中。。*/
#define GDMA_INFIFO_CNT_L2_CH2    0x0000007F
#define GDMA_INFIFO_CNT_L2_CH2_M  ((GDMA_INFIFO_CNT_L2_CH2_V)<<(GDMA_INFIFO_CNT_L2_CH2_S))
#define GDMA_INFIFO_CNT_L2_CH2_V  0x7F
#define GDMA_INFIFO_CNT_L2_CH2_S  12
/* GDMA_INFIFO_CNT_L1_CH2:RO；位位置：[11:6]；默认值：6'b0；*/
/*描述：寄存器将数据的字节数存储在Rx信道2的L1 Rx FIFO中。。*/
#define GDMA_INFIFO_CNT_L1_CH2    0x0000003F
#define GDMA_INFIFO_CNT_L1_CH2_M  ((GDMA_INFIFO_CNT_L1_CH2_V)<<(GDMA_INFIFO_CNT_L1_CH2_S))
#define GDMA_INFIFO_CNT_L1_CH2_V  0x3F
#define GDMA_INFIFO_CNT_L1_CH2_S  6
/* GDMA_INFIFO_EMPTY_L3_CH2:RO；位位置：[5]；默认值：1’b1；*/
/*描述：Rx信道2的L3 Rx FIFO空信号。。*/
#define GDMA_INFIFO_EMPTY_L3_CH2    (BIT(5))
#define GDMA_INFIFO_EMPTY_L3_CH2_M  (BIT(5))
#define GDMA_INFIFO_EMPTY_L3_CH2_V  0x1
#define GDMA_INFIFO_EMPTY_L3_CH2_S  5
/* GDMA_INFIFO_FULL_L3_CH2:RO；位位置：[4]；默认值：1’b1；*/
/*描述：Rx信道2的L3 Rx FIFO满信号。。*/
#define GDMA_INFIFO_FULL_L3_CH2    (BIT(4))
#define GDMA_INFIFO_FULL_L3_CH2_M  (BIT(4))
#define GDMA_INFIFO_FULL_L3_CH2_V  0x1
#define GDMA_INFIFO_FULL_L3_CH2_S  4
/* GDMA_INFIFO_EMPTY_L2_CH2:RO；位位置：[3]；默认值：1’b1；*/
/*描述：Rx信道2的L2 Rx FIFO空信号。。*/
#define GDMA_INFIFO_EMPTY_L2_CH2    (BIT(3))
#define GDMA_INFIFO_EMPTY_L2_CH2_M  (BIT(3))
#define GDMA_INFIFO_EMPTY_L2_CH2_V  0x1
#define GDMA_INFIFO_EMPTY_L2_CH2_S  3
/* GDMA_INFIFO_FULL_L2_CH2:RO；位位置：[2]；默认值：1’b0；*/
/*描述：Rx信道2的L2 Rx FIFO满信号。。*/
#define GDMA_INFIFO_FULL_L2_CH2    (BIT(2))
#define GDMA_INFIFO_FULL_L2_CH2_M  (BIT(2))
#define GDMA_INFIFO_FULL_L2_CH2_V  0x1
#define GDMA_INFIFO_FULL_L2_CH2_S  2
/* GDMA_infifoempty_L1_CH2:RO；位位置：[1]；默认值：1’b1；*/
/*描述：Rx信道2的L1 Rx FIFO空信号。。*/
#define GDMA_INFIFO_EMPTY_L1_CH2    (BIT(1))
#define GDMA_INFIFO_EMPTY_L1_CH2_M  (BIT(1))
#define GDMA_INFIFO_EMPTY_L1_CH2_V  0x1
#define GDMA_INFIFO_EMPTY_L1_CH2_S  1
/* GDMA_INFIFO_FULL_L1_CH2:RO；位位置：[0]；默认值：1’b0；*/
/*描述：Rx信道2的L1 Rx FIFO完整信号。。*/
#define GDMA_INFIFO_FULL_L1_CH2    (BIT(0))
#define GDMA_INFIFO_FULL_L1_CH2_M  (BIT(0))
#define GDMA_INFIFO_FULL_L1_CH2_V  0x1
#define GDMA_INFIFO_FULL_L1_CH2_S  0

#define GDMA_IN_POP_CH2_REG          (DR_REG_GDMA_BASE + 0x19C)
/* GDMA_INFIFO_POP_CH2:R/W/SC；位位置：[12]；默认值：1'0；*/
/*description:将此位设置为从DMA FIFO弹出数据。。*/
#define GDMA_INFIFO_POP_CH2    (BIT(12))
#define GDMA_INFIFO_POP_CH2_M  (BIT(12))
#define GDMA_INFIFO_POP_CH2_V  0x1
#define GDMA_INFIFO_POP_CH2_S  12
/* GDMA_INFIFO_data_CH2:RO；位位置：[11:0]；默认值：12'h800；*/
/*description:此寄存器存储从DMA FIFO弹出的数据。。*/
#define GDMA_INFIFO_RDATA_CH2    0x00000FFF
#define GDMA_INFIFO_RDATA_CH2_M  ((GDMA_INFIFO_RDATA_CH2_V)<<(GDMA_INFIFO_RDATA_CH2_S))
#define GDMA_INFIFO_RDATA_CH2_V  0xFFF
#define GDMA_INFIFO_RDATA_CH2_S  0

#define GDMA_IN_LINK_CH2_REG          (DR_REG_GDMA_BASE + 0x1A0)
/* GDMA_INLINK_PARK_CH2:RO；位位置：[24]；默认值：1'h1；*/
/*description:1：内联描述符的FSM处于空闲状态。0:内联描述符的FSM正在工作。。*/
#define GDMA_INLINK_PARK_CH2    (BIT(24))
#define GDMA_INLINK_PARK_CH2_M  (BIT(24))
#define GDMA_INLINK_PARK_CH2_V  0x1
#define GDMA_INLINK_PARK_CH2_S  24
/* GDMA_INLINK_RESTART_CH2:R/W/SC；位位置：[23]；默认值：1’b0；*/
/*description:设置此位以装入新的内联描述符。。*/
#define GDMA_INLINK_RESTART_CH2    (BIT(23))
#define GDMA_INLINK_RESTART_CH2_M  (BIT(23))
#define GDMA_INLINK_RESTART_CH2_V  0x1
#define GDMA_INLINK_RESTART_CH2_S  23
/* GDMA_INLINK_START_CH2:R/W/SC；位位置：[22]；默认值：1’b0；*/
/*description:设置此位以开始处理内联描述符。。*/
#define GDMA_INLINK_START_CH2    (BIT(22))
#define GDMA_INLINK_START_CH2_M  (BIT(22))
#define GDMA_INLINK_START_CH2_V  0x1
#define GDMA_INLINK_START_CH2_S  22
/* GDMA_INLINK_STOP_CH2:R/W/SC；位位置：[21]；默认值：1’b0；*/
/*description:设置此位以停止处理内联描述符。。*/
#define GDMA_INLINK_STOP_CH2    (BIT(21))
#define GDMA_INLINK_STOP_CH2_M  (BIT(21))
#define GDMA_INLINK_STOP_CH2_V  0x1
#define GDMA_INLINK_STOP_CH2_S  21
/* GDMA_INLINK_AUTO_RET_CH2:R/W；位位置：[20]；默认值：1’b1；*/
/*description:当当前接收数据中存在一些错误时，将此位设置为返回当前内联描述符的地址。。*/
#define GDMA_INLINK_AUTO_RET_CH2    (BIT(20))
#define GDMA_INLINK_AUTO_RET_CH2_M  (BIT(20))
#define GDMA_INLINK_AUTO_RET_CH2_V  0x1
#define GDMA_INLINK_AUTO_RET_CH2_S  20
/* GDMA_INLINK_ADDR_CH2:R/W；比特位置：[19:0]；默认值：20'00；*/
/*description:此寄存器存储第一个内联描述符地址的20个最低有效位。。*/
#define GDMA_INLINK_ADDR_CH2    0x000FFFFF
#define GDMA_INLINK_ADDR_CH2_M  ((GDMA_INLINK_ADDR_CH2_V)<<(GDMA_INLINK_ADDR_CH2_S))
#define GDMA_INLINK_ADDR_CH2_V  0xFFFFF
#define GDMA_INLINK_ADDR_CH2_S  0

#define GDMA_IN_STATE_CH2_REG          (DR_REG_GDMA_BASE + 0x1A4)
/* GDMA_IN_STATE_CH2:RO；比特位置：[22:20]；默认值：3'b0；*/
/*description:保留。*/
#define GDMA_IN_STATE_CH2    0x00000007
#define GDMA_IN_STATE_CH2_M  ((GDMA_IN_STATE_CH2_V)<<(GDMA_IN_STATE_CH2_S))
#define GDMA_IN_STATE_CH2_V  0x7
#define GDMA_IN_STATE_CH2_S  20
/* GDMA_IN_DSCR_STATE_CH2:RO；比特位置：[19:18]；默认值：2’b0；*/
/*description:保留。*/
#define GDMA_IN_DSCR_STATE_CH2    0x00000003
#define GDMA_IN_DSCR_STATE_CH2_M  ((GDMA_IN_DSCR_STATE_CH2_V)<<(GDMA_IN_DSCR_STATE_CH2_S))
#define GDMA_IN_DSCR_STATE_CH2_V  0x3
#define GDMA_IN_DSCR_STATE_CH2_S  18
/* GDMA_INLINK_DSCR_ADDR_CH2:RO；比特位置：[17:00]；默认值：18'b0；*/
/*description:此寄存器存储当前内联描述符的地址。。*/
#define GDMA_INLINK_DSCR_ADDR_CH2    0x0003FFFF
#define GDMA_INLINK_DSCR_ADDR_CH2_M  ((GDMA_INLINK_DSCR_ADDR_CH2_V)<<(GDMA_INLINK_DSCR_ADDR_CH2_S))
#define GDMA_INLINK_DSCR_ADDR_CH2_V  0x3FFFF
#define GDMA_INLINK_DSCR_ADDR_CH2_S  0

#define GDMA_IN_SUC_EOF_DES_ADDR_CH2_REG          (DR_REG_GDMA_BASE + 0x1A8)
/* GDMA_IN_SUC_EOF_DES_ADDR_CH2:RO；位位置：[31:0]；默认值：32'h0；*/
/*description:当此描述符中的EOF位为1时，此寄存器存储内联描述符的地址。。*/
#define GDMA_IN_SUC_EOF_DES_ADDR_CH2    0xFFFFFFFF
#define GDMA_IN_SUC_EOF_DES_ADDR_CH2_M  ((GDMA_IN_SUC_EOF_DES_ADDR_CH2_V)<<(GDMA_IN_SUC_EOF_DES_ADDR_CH2_S))
#define GDMA_IN_SUC_EOF_DES_ADDR_CH2_V  0xFFFFFFFF
#define GDMA_IN_SUC_EOF_DES_ADDR_CH2_S  0

#define GDMA_IN_ERR_EOF_DES_ADDR_CH2_REG          (DR_REG_GDMA_BASE + 0x1AC)
/* GDMA_IN_ERR_EOF_DES_ADDR_CH2:RO；位位置：[31:0]；默认值：32'h0；*/
/*description:当当前接收数据中存在一些错误时，此寄存器存储内联描述符的地址。仅当外围设备为UHCI0时使用。。*/
#define GDMA_IN_ERR_EOF_DES_ADDR_CH2    0xFFFFFFFF
#define GDMA_IN_ERR_EOF_DES_ADDR_CH2_M  ((GDMA_IN_ERR_EOF_DES_ADDR_CH2_V)<<(GDMA_IN_ERR_EOF_DES_ADDR_CH2_S))
#define GDMA_IN_ERR_EOF_DES_ADDR_CH2_V  0xFFFFFFFF
#define GDMA_IN_ERR_EOF_DES_ADDR_CH2_S  0

#define GDMA_IN_DSCR_CH2_REG          (DR_REG_GDMA_BASE + 0x1B0)
/* GDMA_INLINK_DSCR_CH2:RO；位位置：[31:0]；默认值：32'b0；*/
/*description:当前内联描述符x的地址。。*/
#define GDMA_INLINK_DSCR_CH2    0xFFFFFFFF
#define GDMA_INLINK_DSCR_CH2_M  ((GDMA_INLINK_DSCR_CH2_V)<<(GDMA_INLINK_DSCR_CH2_S))
#define GDMA_INLINK_DSCR_CH2_V  0xFFFFFFFF
#define GDMA_INLINK_DSCR_CH2_S  0

#define GDMA_IN_DSCR_BF0_CH2_REG          (DR_REG_GDMA_BASE + 0x1B4)
/* GDMA_INLINK_DSCR_BF0_CH2:RO；位位置：[31:0]；默认值：32'b0；*/
/*description:最后一个内联描述符x-1的地址。。*/
#define GDMA_INLINK_DSCR_BF0_CH2    0xFFFFFFFF
#define GDMA_INLINK_DSCR_BF0_CH2_M  ((GDMA_INLINK_DSCR_BF0_CH2_V)<<(GDMA_INLINK_DSCR_BF0_CH2_S))
#define GDMA_INLINK_DSCR_BF0_CH2_V  0xFFFFFFFF
#define GDMA_INLINK_DSCR_BF0_CH2_S  0

#define GDMA_IN_DSCR_BF1_CH2_REG          (DR_REG_GDMA_BASE + 0x1B8)
/* GDMA_INLINK_DSCR_BF1_CH2:RO；位位置：[31:0]；默认值：32'b0；*/
/*description:倒数第二个内联描述符x-2的地址。。*/
#define GDMA_INLINK_DSCR_BF1_CH2    0xFFFFFFFF
#define GDMA_INLINK_DSCR_BF1_CH2_M  ((GDMA_INLINK_DSCR_BF1_CH2_V)<<(GDMA_INLINK_DSCR_BF1_CH2_S))
#define GDMA_INLINK_DSCR_BF1_CH2_V  0xFFFFFFFF
#define GDMA_INLINK_DSCR_BF1_CH2_S  0

#define GDMA_IN_WIGHT_CH2_REG          (DR_REG_GDMA_BASE + 0x1BC)
/* GDMA_RX_WEIGHT_CH2:R/W；位位置：[11:8]；默认值：4'hf；*/
/*description:Rx通道2的权重。*/
#define GDMA_RX_WEIGHT_CH2    0x0000000F
#define GDMA_RX_WEIGHT_CH2_M  ((GDMA_RX_WEIGHT_CH2_V)<<(GDMA_RX_WEIGHT_CH2_S))
#define GDMA_RX_WEIGHT_CH2_V  0xF
#define GDMA_RX_WEIGHT_CH2_S  8

#define GDMA_IN_PRI_CH2_REG          (DR_REG_GDMA_BASE + 0x1C4)
/* GDMA_RX_PRI_CH2:R/W；位位置：[3:0]；默认值：4'b0；*/
/*description:Rx通道2的优先级。值越大，优先级越高。。*/
#define GDMA_RX_PRI_CH2    0x0000000F
#define GDMA_RX_PRI_CH2_M  ((GDMA_RX_PRI_CH2_V)<<(GDMA_RX_PRI_CH2_S))
#define GDMA_RX_PRI_CH2_V  0xF
#define GDMA_RX_PRI_CH2_S  0

#define GDMA_IN_PERI_SEL_CH2_REG          (DR_REG_GDMA_BASE + 0x1C8)
/* GDMA_PERI_IN_SEL_CH2:R/W；比特位置：[5:0]；默认值：6'h3f；*/
/*描述：此寄存器用于为Rx通道2.0:SPI2.1:SPI3.2:UHCI0.3:I2S0.4:I2S1.5:LCD_CAM选择外围设备。6： AES。7： 沙。8： ADC_DAC。9： RMT。。*/
#define GDMA_PERI_IN_SEL_CH2    0x0000003F
#define GDMA_PERI_IN_SEL_CH2_M  ((GDMA_PERI_IN_SEL_CH2_V)<<(GDMA_PERI_IN_SEL_CH2_S))
#define GDMA_PERI_IN_SEL_CH2_V  0x3F
#define GDMA_PERI_IN_SEL_CH2_S  0

#define GDMA_OUT_CONF0_CH2_REG          (DR_REG_GDMA_BASE + 0x1E0)
/* GDMA_OUT_DATA_BURST_EN_CH2:R/W；位位置：[5]；默认值：1’b0；*/
/*描述：当访问内部SRAM时，将此位设置为1以启用传输数据的Tx信道2的INCR突发传输。*/
#define GDMA_OUT_DATA_BURST_EN_CH2    (BIT(5))
#define GDMA_OUT_DATA_BURST_EN_CH2_M  (BIT(5))
#define GDMA_OUT_DATA_BURST_EN_CH2_V  0x1
#define GDMA_OUT_DATA_BURST_EN_CH2_S  5
/* GDMA_OUTDSCR_BURST_EN_CH2:R/W；位位置：[4]；默认值：1’b0；*/
/*description:将此位设置为1，以便在访问内部SRAM时，为Tx信道2读取链路描述符启用INCR突发传输。*/
#define GDMA_OUTDSCR_BURST_EN_CH2    (BIT(4))
#define GDMA_OUTDSCR_BURST_EN_CH2_M  (BIT(4))
#define GDMA_OUTDSCR_BURST_EN_CH2_V  0x1
#define GDMA_OUTDSCR_BURST_EN_CH2_S  4
/* GDMA_OUT_EOF_MODE_CH2:R/W；位位置：[3]；默认值：1’b1；*/
/*描述：传输数据时EOF标志生成模式。1： 当需要传输的数据从DMA中的FIFO弹出时，生成Tx信道0的EOF标志。*/
#define GDMA_OUT_EOF_MODE_CH2    (BIT(3))
#define GDMA_OUT_EOF_MODE_CH2_M  (BIT(3))
#define GDMA_OUT_EOF_MODE_CH2_V  0x1
#define GDMA_OUT_EOF_MODE_CH2_S  3
/* GDMA_OUT_AUTO_WRBACK_CH2:R/W；位位置：[2]；默认值：1’b0；*/
/*description:设置此位以在传输tx缓冲区中的所有数据时启用自动outlink写回。。*/
#define GDMA_OUT_AUTO_WRBACK_CH2    (BIT(2))
#define GDMA_OUT_AUTO_WRBACK_CH2_M  (BIT(2))
#define GDMA_OUT_AUTO_WRBACK_CH2_V  0x1
#define GDMA_OUT_AUTO_WRBACK_CH2_S  2
/* GDMA_OUT_LOOP_TEST_CH2:R/W；位位置：[1]；默认值：1’b0；*/
/*description:保留。*/
#define GDMA_OUT_LOOP_TEST_CH2    (BIT(1))
#define GDMA_OUT_LOOP_TEST_CH2_M  (BIT(1))
#define GDMA_OUT_LOOP_TEST_CH2_V  0x1
#define GDMA_OUT_LOOP_TEST_CH2_S  1
/* GDMA_OUT_RST_CH2:R/W；位位置：[0]；默认值：1’b0；*/
/*描述：此位用于重置DMA通道2 Tx FSM和Tx FIFO指针。。*/
#define GDMA_OUT_RST_CH2    (BIT(0))
#define GDMA_OUT_RST_CH2_M  (BIT(0))
#define GDMA_OUT_RST_CH2_V  0x1
#define GDMA_OUT_RST_CH2_S  0

#define GDMA_OUT_CONF1_CH2_REG          (DR_REG_GDMA_BASE + 0x1E4)
/* GDMA_OUT_EXT_MEM_BK_SIZE_CH2:R/W；比特位置：[14:13]；默认值：2’b0；*/
/*描述：DMA访问外部SRAM时Tx通道2的块大小。0:16字节1:32字节2/3:保留。*/
#define GDMA_OUT_EXT_MEM_BK_SIZE_CH2    0x00000003
#define GDMA_OUT_EXT_MEM_BK_SIZE_CH2_M  ((GDMA_OUT_EXT_MEM_BK_SIZE_CH2_V)<<(GDMA_OUT_EXT_MEM_BK_SIZE_CH2_S))
#define GDMA_OUT_EXT_MEM_BK_SIZE_CH2_V  0x3
#define GDMA_OUT_EXT_MEM_BK_SIZE_CH2_S  13
/* GDMA_OUT_CHECK_OWNER_CH2:R/W；位位置：[12]；默认值：1’b0；*/
/*description:设置此位以启用检查链接描述符的所有者属性。。*/
#define GDMA_OUT_CHECK_OWNER_CH2    (BIT(12))
#define GDMA_OUT_CHECK_OWNER_CH2_M  (BIT(12))
#define GDMA_OUT_CHECK_OWNER_CH2_V  0x1
#define GDMA_OUT_CHECK_OWNER_CH2_S  12

#define GDMA_OUT_INT_RAW_CH2_REG          (DR_REG_GDMA_BASE + 0x1E8)
/* GDMA_OUTFIFO_udfl_L3_CH2_INT_RAW:R/WTC/SS；位位置：[7]；默认值：1’b0；*/
/*描述：当Tx信道2的第3级fifo未满流时，此原始中断位变为高电平。*/
#define GDMA_OUTFIFO_UDF_L3_CH2_INT_RAW    (BIT(7))
#define GDMA_OUTFIFO_UDF_L3_CH2_INT_RAW_M  (BIT(7))
#define GDMA_OUTFIFO_UDF_L3_CH2_INT_RAW_V  0x1
#define GDMA_OUTFIFO_UDF_L3_CH2_INT_RAW_S  7
/* GDMA_OUTFIFO_off_13_CH2_INT_RAW:R/WTC/SS；位位置：[6]；默认值：1’b0；*/
/*描述：当Tx信道2的3级fifo等流量时，此原始中断位变为高电平。*/
#define GDMA_OUTFIFO_OVF_L3_CH2_INT_RAW    (BIT(6))
#define GDMA_OUTFIFO_OVF_L3_CH2_INT_RAW_M  (BIT(6))
#define GDMA_OUTFIFO_OVF_L3_CH2_INT_RAW_V  0x1
#define GDMA_OUTFIFO_OVF_L3_CH2_INT_RAW_S  6
/* GDMA_OUTFIFO_UDF_l_CH2_INT_RAW:R/WTC/SS；位位置：[5]；默认值：1’b0；*/
/*描述：当Tx信道2的第1级fifo未满流时，此原始中断位变为高电平。*/
#define GDMA_OUTFIFO_UDF_L1_CH2_INT_RAW    (BIT(5))
#define GDMA_OUTFIFO_UDF_L1_CH2_INT_RAW_M  (BIT(5))
#define GDMA_OUTFIFO_UDF_L1_CH2_INT_RAW_V  0x1
#define GDMA_OUTFIFO_UDF_L1_CH2_INT_RAW_S  5
/* GDMA_OUTFIFO_OVF_l_CH2_INT_RAW:R/WTC/SS；位位置：[4]；默认值：1’b0；*/
/*描述：当Tx信道2的1级fifo等流量时，此原始中断位变为高电平。*/
#define GDMA_OUTFIFO_OVF_L1_CH2_INT_RAW    (BIT(4))
#define GDMA_OUTFIFO_OVF_L1_CH2_INT_RAW_M  (BIT(4))
#define GDMA_OUTFIFO_OVF_L1_CH2_INT_RAW_V  0x1
#define GDMA_OUTFIFO_OVF_L1_CH2_INT_RAW_S  4
/* GDMA_OUT_TOTAL_EOF_CH2_INT_RAW:R/WTC/SS；位位置：[3]；默认值：1’b0；*/
/*描述：当针对Tx信道2发送出与输出链接（包括一个链接描述符或几个链接描述符）相对应的数据时，原始中断位变为高电平。。*/
#define GDMA_OUT_TOTAL_EOF_CH2_INT_RAW    (BIT(3))
#define GDMA_OUT_TOTAL_EOF_CH2_INT_RAW_M  (BIT(3))
#define GDMA_OUT_TOTAL_EOF_CH2_INT_RAW_V  0x1
#define GDMA_OUT_TOTAL_EOF_CH2_INT_RAW_S  3
/* GDMA_OUT_DSCR_ERR_CH2_INT_RAW:R/WTC/SS；位位置：[2]；默认值：1’b0；*/
/*描述：当检测到outlink描述符错误时，原始中断位变为高电平，包括所有者错误、Tx信道2的outlink描述符的第二个和第三个字错误。。*/
#define GDMA_OUT_DSCR_ERR_CH2_INT_RAW    (BIT(2))
#define GDMA_OUT_DSCR_ERR_CH2_INT_RAW_M  (BIT(2))
#define GDMA_OUT_DSCR_ERR_CH2_INT_RAW_V  0x1
#define GDMA_OUT_DSCR_ERR_CH2_INT_RAW_S  2
/* GDMA_OUT_EOF_CH2_INT_RAW:R/WTC/SS；位位置：[1]；默认值：1’b0；*/
/*描述：当从Tx信道2的存储器中读取一个输出描述符所指向的最后一个数据时，原始中断位变为高电平。*/
#define GDMA_OUT_EOF_CH2_INT_RAW    (BIT(1))
#define GDMA_OUT_EOF_CH2_INT_RAW_M  (BIT(1))
#define GDMA_OUT_EOF_CH2_INT_RAW_V  0x1
#define GDMA_OUT_EOF_CH2_INT_RAW_S  1
/* GDMA_OUT_DONE_CH2_INT_RAW:R/WTC/SS；位位置：[0]；默认值：1’b0；*/
/*描述：当一个输出描述符所指向的最后一个数据已传输到Tx信道2的外围设备时，原始中断位变为高电平。。*/
#define GDMA_OUT_DONE_CH2_INT_RAW    (BIT(0))
#define GDMA_OUT_DONE_CH2_INT_RAW_M  (BIT(0))
#define GDMA_OUT_DONE_CH2_INT_RAW_V  0x1
#define GDMA_OUT_DONE_CH2_INT_RAW_S  0

#define GDMA_OUT_INT_ST_CH2_REG          (DR_REG_GDMA_BASE + 0x1EC)
/* GDMA_OUTFIFO_udfl3_CH2_INT_ST:RO；位位置：[7]；默认值：1’b0；*/
/*description:OUTFIFO_UDF_L3_CH_INT中断的原始中断状态位。。*/
#define GDMA_OUTFIFO_UDF_L3_CH2_INT_ST    (BIT(7))
#define GDMA_OUTFIFO_UDF_L3_CH2_INT_ST_M  (BIT(7))
#define GDMA_OUTFIFO_UDF_L3_CH2_INT_ST_V  0x1
#define GDMA_OUTFIFO_UDF_L3_CH2_INT_ST_S  7
/* GDMA_OUTFIFO_off_13_CH2_INT_ST:RO；位位置：[6]；默认值：1’b0；*/
/*description:OUTFIFO_OVF_L3_CH_INT中断的原始中断状态位。。*/
#define GDMA_OUTFIFO_OVF_L3_CH2_INT_ST    (BIT(6))
#define GDMA_OUTFIFO_OVF_L3_CH2_INT_ST_M  (BIT(6))
#define GDMA_OUTFIFO_OVF_L3_CH2_INT_ST_V  0x1
#define GDMA_OUTFIFO_OVF_L3_CH2_INT_ST_S  6
/* GDMA_OUTFIFO_UDF_l_CH2_INT_ST:RO；位位置：[5]；默认值：1’b0；*/
/*description:OUTFIFO_UDF_L1_CH_INT中断的原始中断状态位。。*/
#define GDMA_OUTFIFO_UDF_L1_CH2_INT_ST    (BIT(5))
#define GDMA_OUTFIFO_UDF_L1_CH2_INT_ST_M  (BIT(5))
#define GDMA_OUTFIFO_UDF_L1_CH2_INT_ST_V  0x1
#define GDMA_OUTFIFO_UDF_L1_CH2_INT_ST_S  5
/* GDMA_OUTFIFO_OVF_l_CH2_INT_ST:RO；位位置：[4]；默认值：1’b0；*/
/*description:OUTFIFO_OVF_L1_CH_INT中断的原始中断状态位。。*/
#define GDMA_OUTFIFO_OVF_L1_CH2_INT_ST    (BIT(4))
#define GDMA_OUTFIFO_OVF_L1_CH2_INT_ST_M  (BIT(4))
#define GDMA_OUTFIFO_OVF_L1_CH2_INT_ST_V  0x1
#define GDMA_OUTFIFO_OVF_L1_CH2_INT_ST_S  4
/* GDMA_OUT_TOTAL_EOF_CH2_INT_ST:RO；位位置：[3]；默认值：1’b0；*/
/*description:OUT_TOTAL_EOF_CH_INT中断的原始中断状态位。。*/
#define GDMA_OUT_TOTAL_EOF_CH2_INT_ST    (BIT(3))
#define GDMA_OUT_TOTAL_EOF_CH2_INT_ST_M  (BIT(3))
#define GDMA_OUT_TOTAL_EOF_CH2_INT_ST_V  0x1
#define GDMA_OUT_TOTAL_EOF_CH2_INT_ST_S  3
/* GDMA_OUT_DSCR_ERR_CH2_INT_ST:RO；位位置：[2]；默认值：1’b0；*/
/*description:OUT_DSCR_ERR_CH_INT中断的原始中断状态位。。*/
#define GDMA_OUT_DSCR_ERR_CH2_INT_ST    (BIT(2))
#define GDMA_OUT_DSCR_ERR_CH2_INT_ST_M  (BIT(2))
#define GDMA_OUT_DSCR_ERR_CH2_INT_ST_V  0x1
#define GDMA_OUT_DSCR_ERR_CH2_INT_ST_S  2
/* GDMA_OUT_EOF_CH2_INT_ST:RO；位位置：[1]；默认值：1’b0；*/
/*description:OUT_EOF_CH_INT中断的原始中断状态位。。*/
#define GDMA_OUT_EOF_CH2_INT_ST    (BIT(1))
#define GDMA_OUT_EOF_CH2_INT_ST_M  (BIT(1))
#define GDMA_OUT_EOF_CH2_INT_ST_V  0x1
#define GDMA_OUT_EOF_CH2_INT_ST_S  1
/* GDMA_OUT_DONE_CH2_INT_ST:RO；位位置：[0]；默认值：1’b0；*/
/*description:OUT_DONE_CH_INT中断的原始中断状态位。。*/
#define GDMA_OUT_DONE_CH2_INT_ST    (BIT(0))
#define GDMA_OUT_DONE_CH2_INT_ST_M  (BIT(0))
#define GDMA_OUT_DONE_CH2_INT_ST_V  0x1
#define GDMA_OUT_DONE_CH2_INT_ST_S  0

#define GDMA_OUT_INT_ENA_CH2_REG          (DR_REG_GDMA_BASE + 0x1F0)
/* GDMA_OUTFIFO_UDF_13_CH2_INT_ENA:R/W；位位置：[7]；默认值：1’b0；*/
/*description:OUTFIFO_UDF_L3_CH_INT中断的中断启用位。。*/
#define GDMA_OUTFIFO_UDF_L3_CH2_INT_ENA    (BIT(7))
#define GDMA_OUTFIFO_UDF_L3_CH2_INT_ENA_M  (BIT(7))
#define GDMA_OUTFIFO_UDF_L3_CH2_INT_ENA_V  0x1
#define GDMA_OUTFIFO_UDF_L3_CH2_INT_ENA_S  7
/* GDMA_OUTFIFO_off_13_CH2_INT_ENA:R/W；位位置：[6]；默认值：1’b0；*/
/*description:OUTFIFO_OVF_L3_CH_INT中断的中断启用位。。*/
#define GDMA_OUTFIFO_OVF_L3_CH2_INT_ENA    (BIT(6))
#define GDMA_OUTFIFO_OVF_L3_CH2_INT_ENA_M  (BIT(6))
#define GDMA_OUTFIFO_OVF_L3_CH2_INT_ENA_V  0x1
#define GDMA_OUTFIFO_OVF_L3_CH2_INT_ENA_S  6
/* GDMA_OUTFIFO_UDF_l_CH2_INT_ENA：R/W；位位置：[5]；默认值：1’b0；*/
/*description:OUTFIFO_UDF_L1_CH_INT中断的中断启用位。。*/
#define GDMA_OUTFIFO_UDF_L1_CH2_INT_ENA    (BIT(5))
#define GDMA_OUTFIFO_UDF_L1_CH2_INT_ENA_M  (BIT(5))
#define GDMA_OUTFIFO_UDF_L1_CH2_INT_ENA_V  0x1
#define GDMA_OUTFIFO_UDF_L1_CH2_INT_ENA_S  5
/* GDMA_OUTFIFO_off_L1_CH2_INT_ENA:R/W；位位置：[4]；默认值：1’b0；*/
/*description:OUTFIFO_OVF_L1_CH_INT中断的中断启用位。。*/
#define GDMA_OUTFIFO_OVF_L1_CH2_INT_ENA    (BIT(4))
#define GDMA_OUTFIFO_OVF_L1_CH2_INT_ENA_M  (BIT(4))
#define GDMA_OUTFIFO_OVF_L1_CH2_INT_ENA_V  0x1
#define GDMA_OUTFIFO_OVF_L1_CH2_INT_ENA_S  4
/* GDMA_OUT_TOTAL_EOF_CH2_INT_ENA:R/W；位位置：[3]；默认值：1’b0；*/
/*description:OUT_TOTAL_EOF_CH_INT中断的中断启用位。。*/
#define GDMA_OUT_TOTAL_EOF_CH2_INT_ENA    (BIT(3))
#define GDMA_OUT_TOTAL_EOF_CH2_INT_ENA_M  (BIT(3))
#define GDMA_OUT_TOTAL_EOF_CH2_INT_ENA_V  0x1
#define GDMA_OUT_TOTAL_EOF_CH2_INT_ENA_S  3
/* GDMA_OUT_DSCR_ERR_CH2_INT_ENA:R/W；位位置：[2]；默认值：1’b0；*/
/*description:OUT_DSCR_ERR_CH_INT中断的中断启用位。。*/
#define GDMA_OUT_DSCR_ERR_CH2_INT_ENA    (BIT(2))
#define GDMA_OUT_DSCR_ERR_CH2_INT_ENA_M  (BIT(2))
#define GDMA_OUT_DSCR_ERR_CH2_INT_ENA_V  0x1
#define GDMA_OUT_DSCR_ERR_CH2_INT_ENA_S  2
/* GDMA_OUT_EOF_CH2_INT_ENA:R/W；位位置：[1]；默认值：1’b0；*/
/*description:OUT_EOF_CH_INT中断的中断启用位。。*/
#define GDMA_OUT_EOF_CH2_INT_ENA    (BIT(1))
#define GDMA_OUT_EOF_CH2_INT_ENA_M  (BIT(1))
#define GDMA_OUT_EOF_CH2_INT_ENA_V  0x1
#define GDMA_OUT_EOF_CH2_INT_ENA_S  1
/* GDMA_OUT_DONE_CH2_INT_ENA:R/W；位位置：[0]；默认值：1’b0；*/
/*description:OUT_DONE_CH_INT中断的中断启用位。。*/
#define GDMA_OUT_DONE_CH2_INT_ENA    (BIT(0))
#define GDMA_OUT_DONE_CH2_INT_ENA_M  (BIT(0))
#define GDMA_OUT_DONE_CH2_INT_ENA_V  0x1
#define GDMA_OUT_DONE_CH2_INT_ENA_S  0

#define GDMA_OUT_INT_CLR_CH2_REG          (DR_REG_GDMA_BASE + 0x1F4)
/* GDMA_OUTFIFO_udfl3_CH2_INT_CLR:WO；位位置：[7]；默认值：1’b0；*/
/*description:设置此位以清除OUTFIFO_UDF_L3_CH_INT中断。。*/
#define GDMA_OUTFIFO_UDF_L3_CH2_INT_CLR    (BIT(7))
#define GDMA_OUTFIFO_UDF_L3_CH2_INT_CLR_M  (BIT(7))
#define GDMA_OUTFIFO_UDF_L3_CH2_INT_CLR_V  0x1
#define GDMA_OUTFIFO_UDF_L3_CH2_INT_CLR_S  7
/* GDMA_OUTFIFO_off_13_CH2_INT_CLR:WO；位位置：[6]；默认值：1’b0；*/
/*description:设置此位以清除OUTFIFO_OVF_L3_CH_INT中断。。*/
#define GDMA_OUTFIFO_OVF_L3_CH2_INT_CLR    (BIT(6))
#define GDMA_OUTFIFO_OVF_L3_CH2_INT_CLR_M  (BIT(6))
#define GDMA_OUTFIFO_OVF_L3_CH2_INT_CLR_V  0x1
#define GDMA_OUTFIFO_OVF_L3_CH2_INT_CLR_S  6
/* GDMA_OUTFIFO_UDF_l_CH2_INT_CLR:WO；位位置：[5]；默认值：1’b0；*/
/*description:设置此位以清除OUTFIFO_UDF_L1_CH_INT中断。。*/
#define GDMA_OUTFIFO_UDF_L1_CH2_INT_CLR    (BIT(5))
#define GDMA_OUTFIFO_UDF_L1_CH2_INT_CLR_M  (BIT(5))
#define GDMA_OUTFIFO_UDF_L1_CH2_INT_CLR_V  0x1
#define GDMA_OUTFIFO_UDF_L1_CH2_INT_CLR_S  5
/* GDMA_OUTFIFO_OVF_l_CH2_INT_CLR:WO；位位置：[4]；默认值：1’b0；*/
/*description:设置此位以清除OUTFIFO_OVF_L1_CH_INT中断。。*/
#define GDMA_OUTFIFO_OVF_L1_CH2_INT_CLR    (BIT(4))
#define GDMA_OUTFIFO_OVF_L1_CH2_INT_CLR_M  (BIT(4))
#define GDMA_OUTFIFO_OVF_L1_CH2_INT_CLR_V  0x1
#define GDMA_OUTFIFO_OVF_L1_CH2_INT_CLR_S  4
/* GDMA_OUT_TOTAL_EOF_CH2_INT_CLR:WT；位位置：[3]；默认值：1’b0；*/
/*description:设置此位以清除OUT_TOTAL_EOF_CH_INT中断。。*/
#define GDMA_OUT_TOTAL_EOF_CH2_INT_CLR    (BIT(3))
#define GDMA_OUT_TOTAL_EOF_CH2_INT_CLR_M  (BIT(3))
#define GDMA_OUT_TOTAL_EOF_CH2_INT_CLR_V  0x1
#define GDMA_OUT_TOTAL_EOF_CH2_INT_CLR_S  3
/* GDMA_OUT_DSCR_ERR_CH2_INT_CLR:WT；位位置：[2]；默认值：1’b0；*/
/*description:设置此位以清除OUT_DSCR_ERR_CH_INT中断。。*/
#define GDMA_OUT_DSCR_ERR_CH2_INT_CLR    (BIT(2))
#define GDMA_OUT_DSCR_ERR_CH2_INT_CLR_M  (BIT(2))
#define GDMA_OUT_DSCR_ERR_CH2_INT_CLR_V  0x1
#define GDMA_OUT_DSCR_ERR_CH2_INT_CLR_S  2
/* GDMA_OUT_EOF_CH2_INT_CLR:WT；位位置：[1]；默认值：1’b0；*/
/*description:设置此位以清除OUT_EOF_CH_INT中断。。*/
#define GDMA_OUT_EOF_CH2_INT_CLR    (BIT(1))
#define GDMA_OUT_EOF_CH2_INT_CLR_M  (BIT(1))
#define GDMA_OUT_EOF_CH2_INT_CLR_V  0x1
#define GDMA_OUT_EOF_CH2_INT_CLR_S  1
/* GDMA_OUT_DONE_CH2_INT_CLR:WT；位位置：[0]；默认值：1’b0；*/
/*description:设置此位以清除OUT_DONE_CH_INT中断。。*/
#define GDMA_OUT_DONE_CH2_INT_CLR    (BIT(0))
#define GDMA_OUT_DONE_CH2_INT_CLR_M  (BIT(0))
#define GDMA_OUT_DONE_CH2_INT_CLR_V  0x1
#define GDMA_OUT_DONE_CH2_INT_CLR_S  0

#define GDMA_OUTFIFO_STATUS_CH2_REG          (DR_REG_GDMA_BASE + 0x1F8)
/* GDMA_OUT_REMAIN_UNDER_4B_L3_CH2:RO；位位置：[26]；默认值：1’b1；*/
/*description:保留。*/
#define GDMA_OUT_REMAIN_UNDER_4B_L3_CH2    (BIT(26))
#define GDMA_OUT_REMAIN_UNDER_4B_L3_CH2_M  (BIT(26))
#define GDMA_OUT_REMAIN_UNDER_4B_L3_CH2_V  0x1
#define GDMA_OUT_REMAIN_UNDER_4B_L3_CH2_S  26
/* GDMA_OUT_REMAIN_UNDER_3B_L3_CH2:RO；位位置：[25]；默认值：1’b1；*/
/*description:保留。*/
#define GDMA_OUT_REMAIN_UNDER_3B_L3_CH2    (BIT(25))
#define GDMA_OUT_REMAIN_UNDER_3B_L3_CH2_M  (BIT(25))
#define GDMA_OUT_REMAIN_UNDER_3B_L3_CH2_V  0x1
#define GDMA_OUT_REMAIN_UNDER_3B_L3_CH2_S  25
/* GDMA_OUT_REMAIN_UNDER_2B_L3_CH2:RO；位位置：[24]；默认值：1’b1；*/
/*description:保留。*/
#define GDMA_OUT_REMAIN_UNDER_2B_L3_CH2    (BIT(24))
#define GDMA_OUT_REMAIN_UNDER_2B_L3_CH2_M  (BIT(24))
#define GDMA_OUT_REMAIN_UNDER_2B_L3_CH2_V  0x1
#define GDMA_OUT_REMAIN_UNDER_2B_L3_CH2_S  24
/* GDMA_OUT_REMAIN_UNDER_1B_L3_CH2:RO；位位置：[23]；默认值：1’b1；*/
/*description:保留。*/
#define GDMA_OUT_REMAIN_UNDER_1B_L3_CH2    (BIT(23))
#define GDMA_OUT_REMAIN_UNDER_1B_L3_CH2_M  (BIT(23))
#define GDMA_OUT_REMAIN_UNDER_1B_L3_CH2_V  0x1
#define GDMA_OUT_REMAIN_UNDER_1B_L3_CH2_S  23
/* GDMA_OUTFIFO_CNT_L3_CH2:RO；比特位置：[22:18]；默认值：5’b0；*/
/*描述：寄存器将数据的字节数存储在Tx信道2的L3 Tx FIFO中。。*/
#define GDMA_OUTFIFO_CNT_L3_CH2    0x0000001F
#define GDMA_OUTFIFO_CNT_L3_CH2_M  ((GDMA_OUTFIFO_CNT_L3_CH2_V)<<(GDMA_OUTFIFO_CNT_L3_CH2_S))
#define GDMA_OUTFIFO_CNT_L3_CH2_V  0x1F
#define GDMA_OUTFIFO_CNT_L3_CH2_S  18
/* GDMA_OUTFIFO_CNT_L2_CH2:RO；比特位置：[17:11]；默认值：7'b0；*/
/*描述：寄存器将数据的字节数存储在Tx信道2的L2 Tx FIFO中。。*/
#define GDMA_OUTFIFO_CNT_L2_CH2    0x0000007F
#define GDMA_OUTFIFO_CNT_L2_CH2_M  ((GDMA_OUTFIFO_CNT_L2_CH2_V)<<(GDMA_OUTFIFO_CNT_L2_CH2_S))
#define GDMA_OUTFIFO_CNT_L2_CH2_V  0x7F
#define GDMA_OUTFIFO_CNT_L2_CH2_S  11
/* GDMA_OUTFIFO_CNT_L1_CH2:RO；比特位置：[10:6]；默认值：5’b0；*/
/*描述：寄存器将数据的字节数存储在Tx信道2的L1 Tx FIFO中。。*/
#define GDMA_OUTFIFO_CNT_L1_CH2    0x0000001F
#define GDMA_OUTFIFO_CNT_L1_CH2_M  ((GDMA_OUTFIFO_CNT_L1_CH2_V)<<(GDMA_OUTFIFO_CNT_L1_CH2_S))
#define GDMA_OUTFIFO_CNT_L1_CH2_V  0x1F
#define GDMA_OUTFIFO_CNT_L1_CH2_S  6
/* GDMA_OUTFIFO_EMPTY_L3_CH2:RO；位位置：[5]；默认值：1’b1；*/
/*描述：Tx信道2的L3 Tx FIFO空信号。。*/
#define GDMA_OUTFIFO_EMPTY_L3_CH2    (BIT(5))
#define GDMA_OUTFIFO_EMPTY_L3_CH2_M  (BIT(5))
#define GDMA_OUTFIFO_EMPTY_L3_CH2_V  0x1
#define GDMA_OUTFIFO_EMPTY_L3_CH2_S  5
/* GDMA_OUTFIFO_FULL_L3_CH2:RO；位位置：[4]；默认值：1’b0；*/
/*描述：Tx信道2的L3 Tx FIFO满信号。。*/
#define GDMA_OUTFIFO_FULL_L3_CH2    (BIT(4))
#define GDMA_OUTFIFO_FULL_L3_CH2_M  (BIT(4))
#define GDMA_OUTFIFO_FULL_L3_CH2_V  0x1
#define GDMA_OUTFIFO_FULL_L3_CH2_S  4
/* GDMA_OUTFIFO_EMPTY_L2_CH2:RO；位位置：[3]；默认值：1’b1；*/
/*描述：Tx信道2的L2 Tx FIFO空信号。。*/
#define GDMA_OUTFIFO_EMPTY_L2_CH2    (BIT(3))
#define GDMA_OUTFIFO_EMPTY_L2_CH2_M  (BIT(3))
#define GDMA_OUTFIFO_EMPTY_L2_CH2_V  0x1
#define GDMA_OUTFIFO_EMPTY_L2_CH2_S  3
/* GDMA_OUTFIFO_FULL_L2_CH2:RO；位位置：[2]；默认值：1’b0；*/
/*描述：Tx信道2的L2 Tx FIFO满信号。。*/
#define GDMA_OUTFIFO_FULL_L2_CH2    (BIT(2))
#define GDMA_OUTFIFO_FULL_L2_CH2_M  (BIT(2))
#define GDMA_OUTFIFO_FULL_L2_CH2_V  0x1
#define GDMA_OUTFIFO_FULL_L2_CH2_S  2
/* GDMA_OUTFIFO_EMPTY_L1_CH2:RO；位位置：[1]；默认值：1’b1；*/
/*描述：Tx信道2的L1 Tx FIFO空信号。。*/
#define GDMA_OUTFIFO_EMPTY_L1_CH2    (BIT(1))
#define GDMA_OUTFIFO_EMPTY_L1_CH2_M  (BIT(1))
#define GDMA_OUTFIFO_EMPTY_L1_CH2_V  0x1
#define GDMA_OUTFIFO_EMPTY_L1_CH2_S  1
/* GDMA_OUTFIFO_FULL_L1_CH2:RO；位位置：[0]；默认值：1’b0；*/
/*描述：Tx信道2的L1 Tx FIFO完整信号。。*/
#define GDMA_OUTFIFO_FULL_L1_CH2    (BIT(0))
#define GDMA_OUTFIFO_FULL_L1_CH2_M  (BIT(0))
#define GDMA_OUTFIFO_FULL_L1_CH2_V  0x1
#define GDMA_OUTFIFO_FULL_L1_CH2_S  0

#define GDMA_OUT_PUSH_CH2_REG          (DR_REG_GDMA_BASE + 0x1FC)
/* GDMA_outfifopush_CH2:R/W/SC；位位置：[9]；默认值：1'0；*/
/*description:设置此位以将数据推入DMA FIFO。。*/
#define GDMA_OUTFIFO_PUSH_CH2    (BIT(9))
#define GDMA_OUTFIFO_PUSH_CH2_M  (BIT(9))
#define GDMA_OUTFIFO_PUSH_CH2_V  0x1
#define GDMA_OUTFIFO_PUSH_CH2_S  9
/* GDMA_OUTFIFO_WDATA_CH2:R/W；位位置：[8:0]；默认值：9'0；*/
/*description:此寄存器存储需要推入DMA FIFO的数据。。*/
#define GDMA_OUTFIFO_WDATA_CH2    0x000001FF
#define GDMA_OUTFIFO_WDATA_CH2_M  ((GDMA_OUTFIFO_WDATA_CH2_V)<<(GDMA_OUTFIFO_WDATA_CH2_S))
#define GDMA_OUTFIFO_WDATA_CH2_V  0x1FF
#define GDMA_OUTFIFO_WDATA_CH2_S  0

#define GDMA_OUT_LINK_CH2_REG          (DR_REG_GDMA_BASE + 0x200)
/* GDMA_OUTLINK_PARK_CH2:RO；位位置：[23]；默认值：1'h1；*/
/*描述：1:outlink描述符的FSM处于空闲状态。0:outlink描述符的FSM正在工作。。*/
#define GDMA_OUTLINK_PARK_CH2    (BIT(23))
#define GDMA_OUTLINK_PARK_CH2_M  (BIT(23))
#define GDMA_OUTLINK_PARK_CH2_V  0x1
#define GDMA_OUTLINK_PARK_CH2_S  23
/* GDMA_OUTLINK_RESTART_CH2:R/W/SC；位位置：[22]；默认值：1’b0；*/
/*description:设置此位以从上一个地址重新启动新的outlink。*/
#define GDMA_OUTLINK_RESTART_CH2    (BIT(22))
#define GDMA_OUTLINK_RESTART_CH2_M  (BIT(22))
#define GDMA_OUTLINK_RESTART_CH2_V  0x1
#define GDMA_OUTLINK_RESTART_CH2_S  22
/* GDMA_OUTLINK_START_CH2:R/W/SC；位位置：[21]；默认值：1’b0；*/
/*description:设置此位以开始处理outlink描述符。。*/
#define GDMA_OUTLINK_START_CH2    (BIT(21))
#define GDMA_OUTLINK_START_CH2_M  (BIT(21))
#define GDMA_OUTLINK_START_CH2_V  0x1
#define GDMA_OUTLINK_START_CH2_S  21
/* GDMA_OUTLINK_STOP_CH2:R/W/SC；位位置：[20]；默认值：1’b0；*/
/*description:设置此位以停止处理outlink描述符。。*/
#define GDMA_OUTLINK_STOP_CH2    (BIT(20))
#define GDMA_OUTLINK_STOP_CH2_M  (BIT(20))
#define GDMA_OUTLINK_STOP_CH2_V  0x1
#define GDMA_OUTLINK_STOP_CH2_S  20
/* GDMA_OUTLINK_ADDR_CH2:R/W；比特位置：[19:0]；默认值：20'00；*/
/*description:此寄存器存储第一个outlink描述符地址的20个最低有效位。。*/
#define GDMA_OUTLINK_ADDR_CH2    0x000FFFFF
#define GDMA_OUTLINK_ADDR_CH2_M  ((GDMA_OUTLINK_ADDR_CH2_V)<<(GDMA_OUTLINK_ADDR_CH2_S))
#define GDMA_OUTLINK_ADDR_CH2_V  0xFFFFF
#define GDMA_OUTLINK_ADDR_CH2_S  0

#define GDMA_OUT_STATE_CH2_REG          (DR_REG_GDMA_BASE + 0x204)
/* GDMA_OUT_STATE_CH2:RO；比特位置：[22:20]；默认值：3'b0；*/
/*description:保留。*/
#define GDMA_OUT_STATE_CH2    0x00000007
#define GDMA_OUT_STATE_CH2_M  ((GDMA_OUT_STATE_CH2_V)<<(GDMA_OUT_STATE_CH2_S))
#define GDMA_OUT_STATE_CH2_V  0x7
#define GDMA_OUT_STATE_CH2_S  20
/* GDMA_OUT_DSCR_STATE_CH2:RO；比特位置：[19:18]；默认值：2’b0；*/
/*description:保留。*/
#define GDMA_OUT_DSCR_STATE_CH2    0x00000003
#define GDMA_OUT_DSCR_STATE_CH2_M  ((GDMA_OUT_DSCR_STATE_CH2_V)<<(GDMA_OUT_DSCR_STATE_CH2_S))
#define GDMA_OUT_DSCR_STATE_CH2_V  0x3
#define GDMA_OUT_DSCR_STATE_CH2_S  18
/* GDMA_OUTLINK_DSCR_ADDR_CH2:RO；比特位置：[17:00]；默认值：18'b0；*/
/*description:此寄存器存储当前outlink描述符的地址。。*/
#define GDMA_OUTLINK_DSCR_ADDR_CH2    0x0003FFFF
#define GDMA_OUTLINK_DSCR_ADDR_CH2_M  ((GDMA_OUTLINK_DSCR_ADDR_CH2_V)<<(GDMA_OUTLINK_DSCR_ADDR_CH2_S))
#define GDMA_OUTLINK_DSCR_ADDR_CH2_V  0x3FFFF
#define GDMA_OUTLINK_DSCR_ADDR_CH2_S  0

#define GDMA_OUT_EOF_DES_ADDR_CH2_REG          (DR_REG_GDMA_BASE + 0x208)
/* GDMA_OUT_EOF_DES_ADDR_CH2:RO；位位置：[31:0]；默认值：32'h0；*/
/*description:当此描述符中的EOF位为1时，此寄存器存储outlink描述符的地址。。*/
#define GDMA_OUT_EOF_DES_ADDR_CH2    0xFFFFFFFF
#define GDMA_OUT_EOF_DES_ADDR_CH2_M  ((GDMA_OUT_EOF_DES_ADDR_CH2_V)<<(GDMA_OUT_EOF_DES_ADDR_CH2_S))
#define GDMA_OUT_EOF_DES_ADDR_CH2_V  0xFFFFFFFF
#define GDMA_OUT_EOF_DES_ADDR_CH2_S  0

#define GDMA_OUT_EOF_BFR_DES_ADDR_CH2_REG          (DR_REG_GDMA_BASE + 0x20C)
/* GDMA_OUT_EOF_BFR_DES_ADDR_CH2:RO；位位置：[31:0]；默认值：32'h0；*/
/*description:此寄存器存储最后一个outlink描述符之前的outlink描述符的地址。。*/
#define GDMA_OUT_EOF_BFR_DES_ADDR_CH2    0xFFFFFFFF
#define GDMA_OUT_EOF_BFR_DES_ADDR_CH2_M  ((GDMA_OUT_EOF_BFR_DES_ADDR_CH2_V)<<(GDMA_OUT_EOF_BFR_DES_ADDR_CH2_S))
#define GDMA_OUT_EOF_BFR_DES_ADDR_CH2_V  0xFFFFFFFF
#define GDMA_OUT_EOF_BFR_DES_ADDR_CH2_S  0

#define GDMA_OUT_DSCR_CH2_REG          (DR_REG_GDMA_BASE + 0x210)
/* GDMA_OUTLINK_DSCR_CH2:RO；位位置：[31:0]；默认值：32'b0；*/
/*description:当前outlink描述符y的地址。。*/
#define GDMA_OUTLINK_DSCR_CH2    0xFFFFFFFF
#define GDMA_OUTLINK_DSCR_CH2_M  ((GDMA_OUTLINK_DSCR_CH2_V)<<(GDMA_OUTLINK_DSCR_CH2_S))
#define GDMA_OUTLINK_DSCR_CH2_V  0xFFFFFFFF
#define GDMA_OUTLINK_DSCR_CH2_S  0

#define GDMA_OUT_DSCR_BF0_CH2_REG          (DR_REG_GDMA_BASE + 0x214)
/* GDMA_OUTLINK_DSCR_BF0_CH2:RO；位位置：[31:0]；默认值：32'b0；*/
/*description:最后一个outlink描述符的地址y-1。。*/
#define GDMA_OUTLINK_DSCR_BF0_CH2    0xFFFFFFFF
#define GDMA_OUTLINK_DSCR_BF0_CH2_M  ((GDMA_OUTLINK_DSCR_BF0_CH2_V)<<(GDMA_OUTLINK_DSCR_BF0_CH2_S))
#define GDMA_OUTLINK_DSCR_BF0_CH2_V  0xFFFFFFFF
#define GDMA_OUTLINK_DSCR_BF0_CH2_S  0

#define GDMA_OUT_DSCR_BF1_CH2_REG          (DR_REG_GDMA_BASE + 0x218)
/* GDMA_OUTLINK_DSCR_BF1_CH2:RO；位位置：[31:0]；默认值：32'b0；*/
/*description:倒数第二个内联描述符x-2的地址。。*/
#define GDMA_OUTLINK_DSCR_BF1_CH2    0xFFFFFFFF
#define GDMA_OUTLINK_DSCR_BF1_CH2_M  ((GDMA_OUTLINK_DSCR_BF1_CH2_V)<<(GDMA_OUTLINK_DSCR_BF1_CH2_S))
#define GDMA_OUTLINK_DSCR_BF1_CH2_V  0xFFFFFFFF
#define GDMA_OUTLINK_DSCR_BF1_CH2_S  0

#define GDMA_OUT_WIGHT_CH2_REG          (DR_REG_GDMA_BASE + 0x21C)
/* GDMA_TX_WEIGHT_CH2:R/W；位位置：[11:8]；默认值：4'hf；*/
/*description:Tx信道2的权重。*/
#define GDMA_TX_WEIGHT_CH2    0x0000000F
#define GDMA_TX_WEIGHT_CH2_M  ((GDMA_TX_WEIGHT_CH2_V)<<(GDMA_TX_WEIGHT_CH2_S))
#define GDMA_TX_WEIGHT_CH2_V  0xF
#define GDMA_TX_WEIGHT_CH2_S  8

#define GDMA_OUT_PRI_CH2_REG          (DR_REG_GDMA_BASE + 0x224)
/* GDMA_TX_PRI_CH2:R/W；位位置：[3:0]；默认值：4'b0；*/
/*description:Tx信道2的优先级。值越大，优先级越高。。*/
#define GDMA_TX_PRI_CH2    0x0000000F
#define GDMA_TX_PRI_CH2_M  ((GDMA_TX_PRI_CH2_V)<<(GDMA_TX_PRI_CH2_S))
#define GDMA_TX_PRI_CH2_V  0xF
#define GDMA_TX_PRI_CH2_S  0

#define GDMA_OUT_PERI_SEL_CH2_REG          (DR_REG_GDMA_BASE + 0x228)
/* GDMA_PERI_OUT_SEL_CH2:R/W；比特位置：[5:0]；默认值：6'h3f；*/
/*描述：此寄存器用于为Tx信道2.0:SPI2.1:SPI3.2:UHCI0.3:I2S0.4:I2S1.5:LCD_CAM选择外围设备。6： AES。7： 沙。8： ADC_DAC。9： 每立方米。；7： AES。8： 沙。9： ADC_DAC。。*/
#define GDMA_PERI_OUT_SEL_CH2    0x0000003F
#define GDMA_PERI_OUT_SEL_CH2_M  ((GDMA_PERI_OUT_SEL_CH2_V)<<(GDMA_PERI_OUT_SEL_CH2_S))
#define GDMA_PERI_OUT_SEL_CH2_V  0x3F
#define GDMA_PERI_OUT_SEL_CH2_S  0

#define GDMA_IN_CONF0_CH3_REG          (DR_REG_GDMA_BASE + 0x240)
/* GDMA_MEM_TRANS_EN_CH3:R/W；位位置：[4]；默认值：1’b0；*/
/*description:将此位设置为1，以启用通过DMA将数据从存储器自动传输到存储器。。*/
#define GDMA_MEM_TRANS_EN_CH3    (BIT(4))
#define GDMA_MEM_TRANS_EN_CH3_M  (BIT(4))
#define GDMA_MEM_TRANS_EN_CH3_V  0x1
#define GDMA_MEM_TRANS_EN_CH3_S  4
/* GDMA_IN_DATA_BURST_EN_CH3:R/W；位位置：[3]；默认值：1’b0；*/
/*description:将此位设置为1，以在访问内部SRAM时启用接收数据的Rx通道2的INCR突发传输。*/
#define GDMA_IN_DATA_BURST_EN_CH3    (BIT(3))
#define GDMA_IN_DATA_BURST_EN_CH3_M  (BIT(3))
#define GDMA_IN_DATA_BURST_EN_CH3_V  0x1
#define GDMA_IN_DATA_BURST_EN_CH3_S  3
/* GDMA_INDSCR_BURST_EN_CH3:R/W；位位置：[2]；默认值：1’b0；*/
/*description:当访问内部SRAM时，将此位设置为1以启用Rx通道2读取链路描述符的INCR突发传输。*/
#define GDMA_INDSCR_BURST_EN_CH3    (BIT(2))
#define GDMA_INDSCR_BURST_EN_CH3_M  (BIT(2))
#define GDMA_INDSCR_BURST_EN_CH3_V  0x1
#define GDMA_INDSCR_BURST_EN_CH3_S  2
/* GDMA_IN_LOOP_TEST_CH3:R/W；位位置：[1]；默认值：1’b0；*/
/*description:保留。*/
#define GDMA_IN_LOOP_TEST_CH3    (BIT(1))
#define GDMA_IN_LOOP_TEST_CH3_M  (BIT(1))
#define GDMA_IN_LOOP_TEST_CH3_V  0x1
#define GDMA_IN_LOOP_TEST_CH3_S  1
/* GDMA_IN_RST_CH3:R/W；位位置：[0]；默认值：1'0；*/
/*描述：此位用于重置DMA通道3 Rx FSM和Rx FIFO指针。。*/
#define GDMA_IN_RST_CH3    (BIT(0))
#define GDMA_IN_RST_CH3_M  (BIT(0))
#define GDMA_IN_RST_CH3_V  0x1
#define GDMA_IN_RST_CH3_S  0

#define GDMA_IN_CONF1_CH3_REG          (DR_REG_GDMA_BASE + 0x244)
/* GDMA_IN_EXT_MEM_BK_SIZE_CH3:R/W；比特位置：[14:13]；默认值：2’b0；*/
/*描述：DMA访问外部SRAM时Rx通道3的块大小。0:16字节1:32字节2/3:保留。*/
#define GDMA_IN_EXT_MEM_BK_SIZE_CH3    0x00000003
#define GDMA_IN_EXT_MEM_BK_SIZE_CH3_M  ((GDMA_IN_EXT_MEM_BK_SIZE_CH3_V)<<(GDMA_IN_EXT_MEM_BK_SIZE_CH3_S))
#define GDMA_IN_EXT_MEM_BK_SIZE_CH3_V  0x3
#define GDMA_IN_EXT_MEM_BK_SIZE_CH3_S  13
/* GDMA_IN_CHECK_OWNER_CH3:R/W；位位置：[12]；默认值：1’b0；*/
/*description:设置此位以启用检查链接描述符的所有者属性。。*/
#define GDMA_IN_CHECK_OWNER_CH3    (BIT(12))
#define GDMA_IN_CHECK_OWNER_CH3_M  (BIT(12))
#define GDMA_IN_CHECK_OWNER_CH3_V  0x1
#define GDMA_IN_CHECK_OWNER_CH3_S  12
/* GDMA_DMA_INFIFO_FULL_THRS_CH3:R/W；位位置：[11:0]；默认值：12'hc；*/
/*描述：当Rx FIFO中的Rx通道3接收字节数达到寄存器值时，此寄存器用于生成INFIFO_FULL_WM_INT中断。。*/
#define GDMA_DMA_INFIFO_FULL_THRS_CH3    0x00000FFF
#define GDMA_DMA_INFIFO_FULL_THRS_CH3_M  ((GDMA_DMA_INFIFO_FULL_THRS_CH3_V)<<(GDMA_DMA_INFIFO_FULL_THRS_CH3_S))
#define GDMA_DMA_INFIFO_FULL_THRS_CH3_V  0xFFF
#define GDMA_DMA_INFIFO_FULL_THRS_CH3_S  0

#define GDMA_IN_INT_RAW_CH3_REG          (DR_REG_GDMA_BASE + 0x248)
/* GDMA_INFIFO_UDF_L3_CH3_INT_RAW:R/WTC/SS；位位置：[9]；默认值：1’b0；*/
/*描述：当Rx通道3的第3级fifo未满流时，此原始中断位变为高电平。*/
#define GDMA_INFIFO_UDF_L3_CH3_INT_RAW    (BIT(9))
#define GDMA_INFIFO_UDF_L3_CH3_INT_RAW_M  (BIT(9))
#define GDMA_INFIFO_UDF_L3_CH3_INT_RAW_V  0x1
#define GDMA_INFIFO_UDF_L3_CH3_INT_RAW_S  9
/* GDMA_INFIFO_off_L3_CH3_INT_RAW:R/WTC/SS；位位置：[8]；默认值：1’b0；*/
/*描述：当Rx通道3的3级fifo等流量时，此原始中断位变为高电平。*/
#define GDMA_INFIFO_OVF_L3_CH3_INT_RAW    (BIT(8))
#define GDMA_INFIFO_OVF_L3_CH3_INT_RAW_M  (BIT(8))
#define GDMA_INFIFO_OVF_L3_CH3_INT_RAW_V  0x1
#define GDMA_INFIFO_OVF_L3_CH3_INT_RAW_S  8
/* GDMA_INFIFO_UDF_L1_CH3_INT_RAW:R/WTC/SS；位位置：[7]；默认值：1’b0；*/
/*描述：当Rx通道3的1级fifo未满流时，此原始中断位变为高电平。*/
#define GDMA_INFIFO_UDF_L1_CH3_INT_RAW    (BIT(7))
#define GDMA_INFIFO_UDF_L1_CH3_INT_RAW_M  (BIT(7))
#define GDMA_INFIFO_UDF_L1_CH3_INT_RAW_V  0x1
#define GDMA_INFIFO_UDF_L1_CH3_INT_RAW_S  7
/* GDMA_INFIFO_off_L1_CH3_INT_RAW:R/WTC/SS；位位置：[6]；默认值：1’b0；*/
/*描述：当Rx通道3的1级fifo等流量时，此原始中断位变为高电平。*/
#define GDMA_INFIFO_OVF_L1_CH3_INT_RAW    (BIT(6))
#define GDMA_INFIFO_OVF_L1_CH3_INT_RAW_M  (BIT(6))
#define GDMA_INFIFO_OVF_L1_CH3_INT_RAW_V  0x1
#define GDMA_INFIFO_OVF_L1_CH3_INT_RAW_S  6
/* GDMA_INFIFO_FULL_WM_CH3_INT_RAW:R/WTC/SS；位位置：[5]；默认值：1’b0；*/
/*描述：当接收的数据字节数达到信道3的Rx FIFO中REG_DMA_INFIFO_FULL_THS_CH0配置的阈值时，原始中断位变为高电平。。*/
#define GDMA_INFIFO_FULL_WM_CH3_INT_RAW    (BIT(5))
#define GDMA_INFIFO_FULL_WM_CH3_INT_RAW_M  (BIT(5))
#define GDMA_INFIFO_FULL_WM_CH3_INT_RAW_V  0x1
#define GDMA_INFIFO_FULL_WM_CH3_INT_RAW_S  5
/* GDMA_IN_DSCR_EMPTY-CH3_INT_RAW:R/WTC/SS；位位置：[4]；默认值：1’b0；*/
/*描述：当inlink指向的Rx缓冲区已满且未完成接收数据时，原始中断位变为高电平，但Rx通道3没有更多的inlink。。*/
#define GDMA_IN_DSCR_EMPTY_CH3_INT_RAW    (BIT(4))
#define GDMA_IN_DSCR_EMPTY_CH3_INT_RAW_M  (BIT(4))
#define GDMA_IN_DSCR_EMPTY_CH3_INT_RAW_V  0x1
#define GDMA_IN_DSCR_EMPTY_CH3_INT_RAW_S  4
/* GDMA_IN_DSCR_ERR_CH3_INT_RAW:R/WTC/SS；位位置：[3]；默认值：1’b0；*/
/*描述：当检测到内联描述符错误时，原始中断位变为高电平，包括所有者错误、Rx通道3的内联描述符的第二个和第三个字错误。。*/
#define GDMA_IN_DSCR_ERR_CH3_INT_RAW    (BIT(3))
#define GDMA_IN_DSCR_ERR_CH3_INT_RAW_M  (BIT(3))
#define GDMA_IN_DSCR_ERR_CH3_INT_RAW_V  0x1
#define GDMA_IN_DSCR_ERR_CH3_INT_RAW_S  3
/* GDMA_IN_ERR_EOF_CH3_INT_RAW:R/WTC/SS；位位置：[2]；默认值：1’b0；*/
/*描述：当仅在外围设备为Rx通道3的UHCI0的情况下检测到数据错误时，原始中断位变为高电平。对于其他外围设备，保留此原始中断。。*/
#define GDMA_IN_ERR_EOF_CH3_INT_RAW    (BIT(2))
#define GDMA_IN_ERR_EOF_CH3_INT_RAW_M  (BIT(2))
#define GDMA_IN_ERR_EOF_CH3_INT_RAW_V  0x1
#define GDMA_IN_ERR_EOF_CH3_INT_RAW_S  2
/* GDMA_IN_SUC_EOF_CH3_INT_RAW:R/WTC/SS；位位置：[1]；默认值：1’b0；*/
/*描述：当接收到Rx通道3的一个内联描述符指向的最后一个数据时，原始中断位变为高电平。对于UHCI0，当接收到一个内联描述符指向的最后数据且Rx通道0未检测到数据错误时，原始断开位变为低电平。。*/
#define GDMA_IN_SUC_EOF_CH3_INT_RAW    (BIT(1))
#define GDMA_IN_SUC_EOF_CH3_INT_RAW_M  (BIT(1))
#define GDMA_IN_SUC_EOF_CH3_INT_RAW_V  0x1
#define GDMA_IN_SUC_EOF_CH3_INT_RAW_S  1
/* GDMA_IN_DONE_CH3_INT_RAW:R/WTC/SS；位位置：[0]；默认值：1’b0；*/
/*描述：当接收到Rx通道3的一个内联描述符指向的最后一个数据时，原始中断位变为高电平。。*/
#define GDMA_IN_DONE_CH3_INT_RAW    (BIT(0))
#define GDMA_IN_DONE_CH3_INT_RAW_M  (BIT(0))
#define GDMA_IN_DONE_CH3_INT_RAW_V  0x1
#define GDMA_IN_DONE_CH3_INT_RAW_S  0

#define GDMA_IN_INT_ST_CH3_REG          (DR_REG_GDMA_BASE + 0x24C)
/* GDMA_INFIFO_UDF_L3_CH3_INT_ST:RO；位位置：[9]；默认值：1’b0；*/
/*description:INFIFO_UDF_L3_CH_INT中断的原始中断状态位。。*/
#define GDMA_INFIFO_UDF_L3_CH3_INT_ST    (BIT(9))
#define GDMA_INFIFO_UDF_L3_CH3_INT_ST_M  (BIT(9))
#define GDMA_INFIFO_UDF_L3_CH3_INT_ST_V  0x1
#define GDMA_INFIFO_UDF_L3_CH3_INT_ST_S  9
/* GDMA_INFIFO_off_L3_CH3_INT_ST:RO；位位置：[8]；默认值：1’b0；*/
/*description:INFIFO_OVF_L3_CH_INT中断的原始中断状态位。。*/
#define GDMA_INFIFO_OVF_L3_CH3_INT_ST    (BIT(8))
#define GDMA_INFIFO_OVF_L3_CH3_INT_ST_M  (BIT(8))
#define GDMA_INFIFO_OVF_L3_CH3_INT_ST_V  0x1
#define GDMA_INFIFO_OVF_L3_CH3_INT_ST_S  8
/* GDMA_INFIFO_UDF_L1_CH3_INT_ST:RO；位位置：[7]；默认值：1’b0；*/
/*description:INFIFO_UDF_L1_CH_INT中断的原始中断状态位。。*/
#define GDMA_INFIFO_UDF_L1_CH3_INT_ST    (BIT(7))
#define GDMA_INFIFO_UDF_L1_CH3_INT_ST_M  (BIT(7))
#define GDMA_INFIFO_UDF_L1_CH3_INT_ST_V  0x1
#define GDMA_INFIFO_UDF_L1_CH3_INT_ST_S  7
/* GDMA_INFIFO_off_L1_CH3_INT_ST:RO；位位置：[6]；默认值：1’b0；*/
/*description:INFIFO_OVF_L1_CH_INT中断的原始中断状态位。。*/
#define GDMA_INFIFO_OVF_L1_CH3_INT_ST    (BIT(6))
#define GDMA_INFIFO_OVF_L1_CH3_INT_ST_M  (BIT(6))
#define GDMA_INFIFO_OVF_L1_CH3_INT_ST_V  0x1
#define GDMA_INFIFO_OVF_L1_CH3_INT_ST_S  6
/* GDMA_INFIFO_FULL_WM_CH3_INT_ST:RO；位位置：[5]；默认值：1’b0；*/
/*description:INFIFO_FULL_WM_CH_INT中断的原始中断状态位。。*/
#define GDMA_INFIFO_FULL_WM_CH3_INT_ST    (BIT(5))
#define GDMA_INFIFO_FULL_WM_CH3_INT_ST_M  (BIT(5))
#define GDMA_INFIFO_FULL_WM_CH3_INT_ST_V  0x1
#define GDMA_INFIFO_FULL_WM_CH3_INT_ST_S  5
/* GDMA_IN_DSCR_EMPTY-CH3_INT_ST:RO；位位置：[4]；默认值：1’b0；*/
/*description:IN_DSCR_EMPTY_CH_INT中断的原始中断状态位。。*/
#define GDMA_IN_DSCR_EMPTY_CH3_INT_ST    (BIT(4))
#define GDMA_IN_DSCR_EMPTY_CH3_INT_ST_M  (BIT(4))
#define GDMA_IN_DSCR_EMPTY_CH3_INT_ST_V  0x1
#define GDMA_IN_DSCR_EMPTY_CH3_INT_ST_S  4
/* GDMA_IN_DSCR_ERR_CH3_INT_ST:RO；位位置：[3]；默认值：1’b0；*/
/*description:IN_DSCR_ERR_CH_INT中断的原始中断状态位。。*/
#define GDMA_IN_DSCR_ERR_CH3_INT_ST    (BIT(3))
#define GDMA_IN_DSCR_ERR_CH3_INT_ST_M  (BIT(3))
#define GDMA_IN_DSCR_ERR_CH3_INT_ST_V  0x1
#define GDMA_IN_DSCR_ERR_CH3_INT_ST_S  3
/* GDMA_IN_ERR_EOF_CH3_INT_ST:RO；位位置：[2]；默认值：1’b0；*/
/*description:IN_ERR_EOF_CH_INT中断的原始中断状态位。。*/
#define GDMA_IN_ERR_EOF_CH3_INT_ST    (BIT(2))
#define GDMA_IN_ERR_EOF_CH3_INT_ST_M  (BIT(2))
#define GDMA_IN_ERR_EOF_CH3_INT_ST_V  0x1
#define GDMA_IN_ERR_EOF_CH3_INT_ST_S  2
/* GDMA_IN_SUC_EOF_CH3_INT_ST:RO；位位置：[1]；默认值：1’b0；*/
/*description:IN_SUC_EOF_CH_INT中断的原始中断状态位。。*/
#define GDMA_IN_SUC_EOF_CH3_INT_ST    (BIT(1))
#define GDMA_IN_SUC_EOF_CH3_INT_ST_M  (BIT(1))
#define GDMA_IN_SUC_EOF_CH3_INT_ST_V  0x1
#define GDMA_IN_SUC_EOF_CH3_INT_ST_S  1
/* GDMA_IN_DONE_CH3_INT_ST:RO；位位置：[0]；默认值：1’b0；*/
/*description:IN_DONE_CH_INT中断的原始中断状态位。。*/
#define GDMA_IN_DONE_CH3_INT_ST    (BIT(0))
#define GDMA_IN_DONE_CH3_INT_ST_M  (BIT(0))
#define GDMA_IN_DONE_CH3_INT_ST_V  0x1
#define GDMA_IN_DONE_CH3_INT_ST_S  0

#define GDMA_IN_INT_ENA_CH3_REG          (DR_REG_GDMA_BASE + 0x250)
/* GDMA_INFIFO_UDF_13_CH3_INT_ENA:R/W；位位置：[9]；默认值：1’b0；*/
/*description:INFIFO_UDF_L3_CH_INT中断的中断启用位。。*/
#define GDMA_INFIFO_UDF_L3_CH3_INT_ENA    (BIT(9))
#define GDMA_INFIFO_UDF_L3_CH3_INT_ENA_M  (BIT(9))
#define GDMA_INFIFO_UDF_L3_CH3_INT_ENA_V  0x1
#define GDMA_INFIFO_UDF_L3_CH3_INT_ENA_S  9
/* GDMA_INFIFO_off_13_CH3_INT_ENA:R/W；位位置：[8]；默认值：1’b0；*/
/*description:INFIFO_OVF_L3_CH_INT中断的中断启用位。。*/
#define GDMA_INFIFO_OVF_L3_CH3_INT_ENA    (BIT(8))
#define GDMA_INFIFO_OVF_L3_CH3_INT_ENA_M  (BIT(8))
#define GDMA_INFIFO_OVF_L3_CH3_INT_ENA_V  0x1
#define GDMA_INFIFO_OVF_L3_CH3_INT_ENA_S  8
/* GDMA_INFIFO_UDF_L1_CH3_INT_ENA:R/W；位位置：[7]；默认值：1’b0；*/
/*description:INFIFO_UDF_L1_CH_INT中断的中断启用位。。*/
#define GDMA_INFIFO_UDF_L1_CH3_INT_ENA    (BIT(7))
#define GDMA_INFIFO_UDF_L1_CH3_INT_ENA_M  (BIT(7))
#define GDMA_INFIFO_UDF_L1_CH3_INT_ENA_V  0x1
#define GDMA_INFIFO_UDF_L1_CH3_INT_ENA_S  7
/* GDMA_INFIFO_off_L1_CH3_INT_ENA:R/W；位位置：[6]；默认值：1’b0；*/
/*description:INFIFO_OVF_L1_CH_INT中断的中断启用位。。*/
#define GDMA_INFIFO_OVF_L1_CH3_INT_ENA    (BIT(6))
#define GDMA_INFIFO_OVF_L1_CH3_INT_ENA_M  (BIT(6))
#define GDMA_INFIFO_OVF_L1_CH3_INT_ENA_V  0x1
#define GDMA_INFIFO_OVF_L1_CH3_INT_ENA_S  6
/* GDMA_INFIFO_FULL_WM_CH3_INT_ENA:R/W；位位置：[5]；默认值：1’b0；*/
/*description:INFIFO_FULL_WM_CH_INT中断的中断启用位。。*/
#define GDMA_INFIFO_FULL_WM_CH3_INT_ENA    (BIT(5))
#define GDMA_INFIFO_FULL_WM_CH3_INT_ENA_M  (BIT(5))
#define GDMA_INFIFO_FULL_WM_CH3_INT_ENA_V  0x1
#define GDMA_INFIFO_FULL_WM_CH3_INT_ENA_S  5
/* GDMA_IN_DSCR_EMPTY-CH3_INT_ENA:R/W；位位置：[4]；默认值：1’b0；*/
/*description:IN_DSCR_EMPTY_CH_INT中断的中断启用位。。*/
#define GDMA_IN_DSCR_EMPTY_CH3_INT_ENA    (BIT(4))
#define GDMA_IN_DSCR_EMPTY_CH3_INT_ENA_M  (BIT(4))
#define GDMA_IN_DSCR_EMPTY_CH3_INT_ENA_V  0x1
#define GDMA_IN_DSCR_EMPTY_CH3_INT_ENA_S  4
/* GDMA_IN_DSCR_ERR_CH3_INT_ENA:R/W；位位置：[3]；默认值：1’b0；*/
/*description:IN_DSCR_ERR_CH_INT中断的中断启用位。。*/
#define GDMA_IN_DSCR_ERR_CH3_INT_ENA    (BIT(3))
#define GDMA_IN_DSCR_ERR_CH3_INT_ENA_M  (BIT(3))
#define GDMA_IN_DSCR_ERR_CH3_INT_ENA_V  0x1
#define GDMA_IN_DSCR_ERR_CH3_INT_ENA_S  3
/* GDMA_IN_ERR_EOF_CH3_INT_ENA:R/W；位位置：[2]；默认值：1’b0；*/
/*description:IN_ERR_EOF_CH_INT中断的中断启用位。。*/
#define GDMA_IN_ERR_EOF_CH3_INT_ENA    (BIT(2))
#define GDMA_IN_ERR_EOF_CH3_INT_ENA_M  (BIT(2))
#define GDMA_IN_ERR_EOF_CH3_INT_ENA_V  0x1
#define GDMA_IN_ERR_EOF_CH3_INT_ENA_S  2
/* GDMA_IN_SUC_EOF_CH3_INT_ENA:R/W；位位置：[1]；默认值：1’b0；*/
/*description:IN_SUC_EOF_CH_INT中断的中断启用位。。*/
#define GDMA_IN_SUC_EOF_CH3_INT_ENA    (BIT(1))
#define GDMA_IN_SUC_EOF_CH3_INT_ENA_M  (BIT(1))
#define GDMA_IN_SUC_EOF_CH3_INT_ENA_V  0x1
#define GDMA_IN_SUC_EOF_CH3_INT_ENA_S  1
/* GDMA_IN_DONE_CH3_INT_ENA:R/W；位位置：[0]；默认值：1’b0；*/
/*description:IN_DONE_CH_INT中断的中断启用位。。*/
#define GDMA_IN_DONE_CH3_INT_ENA    (BIT(0))
#define GDMA_IN_DONE_CH3_INT_ENA_M  (BIT(0))
#define GDMA_IN_DONE_CH3_INT_ENA_V  0x1
#define GDMA_IN_DONE_CH3_INT_ENA_S  0

#define GDMA_IN_INT_CLR_CH3_REG          (DR_REG_GDMA_BASE + 0x254)
/* GDMA_INFIFO_UDF_13_CH3_INT_CLR:WT；位位置：[9]；默认值：1’b0；*/
/*description:设置此位以清除INFIFO_UDF_L3_CH_INT中断。。*/
#define GDMA_INFIFO_UDF_L3_CH3_INT_CLR    (BIT(9))
#define GDMA_INFIFO_UDF_L3_CH3_INT_CLR_M  (BIT(9))
#define GDMA_INFIFO_UDF_L3_CH3_INT_CLR_V  0x1
#define GDMA_INFIFO_UDF_L3_CH3_INT_CLR_S  9
/* GDMA_INFIFO_off_13_CH3_INT_CLR:WT；位位置：[8]；默认值：1’b0；*/
/*description:设置此位以清除INFIFO_OVF_L3_CH_INT中断。。*/
#define GDMA_INFIFO_OVF_L3_CH3_INT_CLR    (BIT(8))
#define GDMA_INFIFO_OVF_L3_CH3_INT_CLR_M  (BIT(8))
#define GDMA_INFIFO_OVF_L3_CH3_INT_CLR_V  0x1
#define GDMA_INFIFO_OVF_L3_CH3_INT_CLR_S  8
/* GDMA_INFIFO_UDF_L1_CH3_INT_CLR:WT；位位置：[7]；默认值：1’b0；*/
/*description:设置此位以清除INFIFO_UDF_L1_CH_INT中断。。*/
#define GDMA_INFIFO_UDF_L1_CH3_INT_CLR    (BIT(7))
#define GDMA_INFIFO_UDF_L1_CH3_INT_CLR_M  (BIT(7))
#define GDMA_INFIFO_UDF_L1_CH3_INT_CLR_V  0x1
#define GDMA_INFIFO_UDF_L1_CH3_INT_CLR_S  7
/* GDMA_INFIFO_off_L1_CH3_INT_CLR:WT；位位置：[6]；默认值：1’b0；*/
/*description:设置此位以清除INFIFO_OVF_L1_CH_INT中断。。*/
#define GDMA_INFIFO_OVF_L1_CH3_INT_CLR    (BIT(6))
#define GDMA_INFIFO_OVF_L1_CH3_INT_CLR_M  (BIT(6))
#define GDMA_INFIFO_OVF_L1_CH3_INT_CLR_V  0x1
#define GDMA_INFIFO_OVF_L1_CH3_INT_CLR_S  6
/* GDMA_DMA_INFIFO_FULL_WM_CH3_INT_CLR:WT；位位置：[5]；默认值：1’b0；*/
/*description:设置此位以清除INFIFO_FULL_WM_CH_INT中断。。*/
#define GDMA_DMA_INFIFO_FULL_WM_CH3_INT_CLR    (BIT(5))
#define GDMA_DMA_INFIFO_FULL_WM_CH3_INT_CLR_M  (BIT(5))
#define GDMA_DMA_INFIFO_FULL_WM_CH3_INT_CLR_V  0x1
#define GDMA_DMA_INFIFO_FULL_WM_CH3_INT_CLR_S  5
/* GDMA_IN_DSCR_EMPTY-CH3_INT_CLR:WT；位位置：[4]；默认值：1’b0；*/
/*description:设置此位以清除IN_DSCR_EMPTY_CH_INT中断。。*/
#define GDMA_IN_DSCR_EMPTY_CH3_INT_CLR    (BIT(4))
#define GDMA_IN_DSCR_EMPTY_CH3_INT_CLR_M  (BIT(4))
#define GDMA_IN_DSCR_EMPTY_CH3_INT_CLR_V  0x1
#define GDMA_IN_DSCR_EMPTY_CH3_INT_CLR_S  4
/* GDMA_IN_DSCR_ERR_CH3_INT_CLR:WT；位位置：[3]；默认值：1’b0；*/
/*description:设置此位以清除IN_DSCR_ERR_CH_INT中断。。*/
#define GDMA_IN_DSCR_ERR_CH3_INT_CLR    (BIT(3))
#define GDMA_IN_DSCR_ERR_CH3_INT_CLR_M  (BIT(3))
#define GDMA_IN_DSCR_ERR_CH3_INT_CLR_V  0x1
#define GDMA_IN_DSCR_ERR_CH3_INT_CLR_S  3
/* GDMA_IN_ERR_EOF_CH3_INT_CLR:WT；位位置：[2]；默认值：1’b0；*/
/*description:设置此位以清除IN_ERR_EOF_CH_INT中断。。*/
#define GDMA_IN_ERR_EOF_CH3_INT_CLR    (BIT(2))
#define GDMA_IN_ERR_EOF_CH3_INT_CLR_M  (BIT(2))
#define GDMA_IN_ERR_EOF_CH3_INT_CLR_V  0x1
#define GDMA_IN_ERR_EOF_CH3_INT_CLR_S  2
/* GDMA_IN_SUC_EOF_CH3_INT_CLR:WT；位位置：[1]；默认值：1’b0；*/
/*description:设置此位以清除IN_SUC_EOF_CH_INT中断。。*/
#define GDMA_IN_SUC_EOF_CH3_INT_CLR    (BIT(1))
#define GDMA_IN_SUC_EOF_CH3_INT_CLR_M  (BIT(1))
#define GDMA_IN_SUC_EOF_CH3_INT_CLR_V  0x1
#define GDMA_IN_SUC_EOF_CH3_INT_CLR_S  1
/* GDMA_IN_DONE_CH3_INT_CLR:WT；位位置：[0]；默认值：1’b0；*/
/*description:设置此位以清除IN_DONE_CH_INT中断。。*/
#define GDMA_IN_DONE_CH3_INT_CLR    (BIT(0))
#define GDMA_IN_DONE_CH3_INT_CLR_M  (BIT(0))
#define GDMA_IN_DONE_CH3_INT_CLR_V  0x1
#define GDMA_IN_DONE_CH3_INT_CLR_S  0

#define GDMA_INFIFO_STATUS_CH3_REG          (DR_REG_GDMA_BASE + 0x258)
/* GDMA_IN_BUF_HUNGRY_CH3:RO；位位置：[28]；默认值：1’b0；*/
/*description:保留。*/
#define GDMA_IN_BUF_HUNGRY_CH3    (BIT(28))
#define GDMA_IN_BUF_HUNGRY_CH3_M  (BIT(28))
#define GDMA_IN_BUF_HUNGRY_CH3_V  0x1
#define GDMA_IN_BUF_HUNGRY_CH3_S  28
/* GDMA_IN_REMAIN_UNDER_4B_L3_CH3:RO；位位置：[27]；默认值：1’b1；*/
/*description:保留。*/
#define GDMA_IN_REMAIN_UNDER_4B_L3_CH3    (BIT(27))
#define GDMA_IN_REMAIN_UNDER_4B_L3_CH3_M  (BIT(27))
#define GDMA_IN_REMAIN_UNDER_4B_L3_CH3_V  0x1
#define GDMA_IN_REMAIN_UNDER_4B_L3_CH3_S  27
/* GDMA_IN_REMAIN_UNDER_3B_L3_CH3:RO；位位置：[26]；默认值：1’b1；*/
/*description:保留。*/
#define GDMA_IN_REMAIN_UNDER_3B_L3_CH3    (BIT(26))
#define GDMA_IN_REMAIN_UNDER_3B_L3_CH3_M  (BIT(26))
#define GDMA_IN_REMAIN_UNDER_3B_L3_CH3_V  0x1
#define GDMA_IN_REMAIN_UNDER_3B_L3_CH3_S  26
/* GDMA_IN_REMAIN_UNDER_2B_L3_CH3:RO；位位置：[25]；默认值：1’b1；*/
/*description:保留。*/
#define GDMA_IN_REMAIN_UNDER_2B_L3_CH3    (BIT(25))
#define GDMA_IN_REMAIN_UNDER_2B_L3_CH3_M  (BIT(25))
#define GDMA_IN_REMAIN_UNDER_2B_L3_CH3_V  0x1
#define GDMA_IN_REMAIN_UNDER_2B_L3_CH3_S  25
/* GDMA_IN_REMAIN_UNDER_1B_L3_CH3:RO；位位置：[24]；默认值：1’b1；*/
/*description:保留。*/
#define GDMA_IN_REMAIN_UNDER_1B_L3_CH3    (BIT(24))
#define GDMA_IN_REMAIN_UNDER_1B_L3_CH3_M  (BIT(24))
#define GDMA_IN_REMAIN_UNDER_1B_L3_CH3_V  0x1
#define GDMA_IN_REMAIN_UNDER_1B_L3_CH3_S  24
/* GDMA_INFIFO_CNT_L3_CH3:RO；比特位置：[23:19]；默认值：5’b0；*/
/*描述：寄存器将数据的字节数存储在Rx通道3的L3 Rx FIFO中。。*/
#define GDMA_INFIFO_CNT_L3_CH3    0x0000001F
#define GDMA_INFIFO_CNT_L3_CH3_M  ((GDMA_INFIFO_CNT_L3_CH3_V)<<(GDMA_INFIFO_CNT_L3_CH3_S))
#define GDMA_INFIFO_CNT_L3_CH3_V  0x1F
#define GDMA_INFIFO_CNT_L3_CH3_S  19
/* GDMA_INFIFO_CNT_L2_CH3:RO；比特位置：[18:12]；默认值：7'b0；*/
/*描述：寄存器将数据的字节数存储在Rx通道3的L2 Rx FIFO中。。*/
#define GDMA_INFIFO_CNT_L2_CH3    0x0000007F
#define GDMA_INFIFO_CNT_L2_CH3_M  ((GDMA_INFIFO_CNT_L2_CH3_V)<<(GDMA_INFIFO_CNT_L2_CH3_S))
#define GDMA_INFIFO_CNT_L2_CH3_V  0x7F
#define GDMA_INFIFO_CNT_L2_CH3_S  12
/* GDMA_INFIFO_CNT_L1_CH3:RO；位位置：[11:6]；默认值：6'b0；*/
/*描述：寄存器将数据的字节数存储在Rx通道3的L1 Rx FIFO中。。*/
#define GDMA_INFIFO_CNT_L1_CH3    0x0000003F
#define GDMA_INFIFO_CNT_L1_CH3_M  ((GDMA_INFIFO_CNT_L1_CH3_V)<<(GDMA_INFIFO_CNT_L1_CH3_S))
#define GDMA_INFIFO_CNT_L1_CH3_V  0x3F
#define GDMA_INFIFO_CNT_L1_CH3_S  6
/* GDMA_INFIFO_EMPTY_L3_CH3:RO；位位置：[5]；默认值：1’b1；*/
/*描述：Rx信道3的L3 Rx FIFO空信号。。*/
#define GDMA_INFIFO_EMPTY_L3_CH3    (BIT(5))
#define GDMA_INFIFO_EMPTY_L3_CH3_M  (BIT(5))
#define GDMA_INFIFO_EMPTY_L3_CH3_V  0x1
#define GDMA_INFIFO_EMPTY_L3_CH3_S  5
/* GDMA_INFIFO_FULL_L3_CH3:RO；位位置：[4]；默认值：1’b1；*/
/*描述：Rx信道3的L3 Rx FIFO满信号。。*/
#define GDMA_INFIFO_FULL_L3_CH3    (BIT(4))
#define GDMA_INFIFO_FULL_L3_CH3_M  (BIT(4))
#define GDMA_INFIFO_FULL_L3_CH3_V  0x1
#define GDMA_INFIFO_FULL_L3_CH3_S  4
/* GDMA_INFIFO_EMPTY_L2_CH3:RO；位位置：[3]；默认值：1’b1；*/
/*描述：Rx信道3的L2 Rx FIFO空信号。。*/
#define GDMA_INFIFO_EMPTY_L2_CH3    (BIT(3))
#define GDMA_INFIFO_EMPTY_L2_CH3_M  (BIT(3))
#define GDMA_INFIFO_EMPTY_L2_CH3_V  0x1
#define GDMA_INFIFO_EMPTY_L2_CH3_S  3
/* GDMA_INFIFO_FULL_L2_CH3:RO；位位置：[2]；默认值：1’b0；*/
/*描述：Rx信道3的L2 Rx FIFO满信号。。*/
#define GDMA_INFIFO_FULL_L2_CH3    (BIT(2))
#define GDMA_INFIFO_FULL_L2_CH3_M  (BIT(2))
#define GDMA_INFIFO_FULL_L2_CH3_V  0x1
#define GDMA_INFIFO_FULL_L2_CH3_S  2
/* GDMA_INFIFO_EMPTY_L1_CH3:RO；位位置：[1]；默认值：1’b1；*/
/*描述：Rx信道3的L1 Rx FIFO空信号。。*/
#define GDMA_INFIFO_EMPTY_L1_CH3    (BIT(1))
#define GDMA_INFIFO_EMPTY_L1_CH3_M  (BIT(1))
#define GDMA_INFIFO_EMPTY_L1_CH3_V  0x1
#define GDMA_INFIFO_EMPTY_L1_CH3_S  1
/* GDMA_INFIFO_FULL_L1_CH3:RO；位位置：[0]；默认值：1’b0；*/
/*描述：Rx信道3的L1 Rx FIFO完整信号。。*/
#define GDMA_INFIFO_FULL_L1_CH3    (BIT(0))
#define GDMA_INFIFO_FULL_L1_CH3_M  (BIT(0))
#define GDMA_INFIFO_FULL_L1_CH3_V  0x1
#define GDMA_INFIFO_FULL_L1_CH3_S  0

#define GDMA_IN_POP_CH3_REG          (DR_REG_GDMA_BASE + 0x25C)
/* GDMA_INFIFO_POP_CH3:R/W/SC；位位置：[12]；默认值：1'0；*/
/*description:将此位设置为从DMA FIFO弹出数据。。*/
#define GDMA_INFIFO_POP_CH3    (BIT(12))
#define GDMA_INFIFO_POP_CH3_M  (BIT(12))
#define GDMA_INFIFO_POP_CH3_V  0x1
#define GDMA_INFIFO_POP_CH3_S  12
/* GDMA_INFIFO_data_CH3:RO；位位置：[11:0]；默认值：12'h800；*/
/*description:此寄存器存储从DMA FIFO弹出的数据。。*/
#define GDMA_INFIFO_RDATA_CH3    0x00000FFF
#define GDMA_INFIFO_RDATA_CH3_M  ((GDMA_INFIFO_RDATA_CH3_V)<<(GDMA_INFIFO_RDATA_CH3_S))
#define GDMA_INFIFO_RDATA_CH3_V  0xFFF
#define GDMA_INFIFO_RDATA_CH3_S  0

#define GDMA_IN_LINK_CH3_REG          (DR_REG_GDMA_BASE + 0x260)
/* GDMA_INLINK_PARK_CH3:RO；位位置：[24]；默认值：1'h1；*/
/*description:1：内联描述符的FSM处于空闲状态。0:内联描述符的FSM正在工作。。*/
#define GDMA_INLINK_PARK_CH3    (BIT(24))
#define GDMA_INLINK_PARK_CH3_M  (BIT(24))
#define GDMA_INLINK_PARK_CH3_V  0x1
#define GDMA_INLINK_PARK_CH3_S  24
/* GDMA_INLINK_RESTART_CH3:R/W/SC；位位置：[23]；默认值：1’b0；*/
/*description:设置此位以装入新的内联描述符。。*/
#define GDMA_INLINK_RESTART_CH3    (BIT(23))
#define GDMA_INLINK_RESTART_CH3_M  (BIT(23))
#define GDMA_INLINK_RESTART_CH3_V  0x1
#define GDMA_INLINK_RESTART_CH3_S  23
/* GDMA_INLINK_START_CH3:R/W/SC；位位置：[22]；默认值：1’b0；*/
/*description:设置此位以开始处理内联描述符。。*/
#define GDMA_INLINK_START_CH3    (BIT(22))
#define GDMA_INLINK_START_CH3_M  (BIT(22))
#define GDMA_INLINK_START_CH3_V  0x1
#define GDMA_INLINK_START_CH3_S  22
/* GDMA_INLINK_STOP_CH3:R/W/SC；位位置：[21]；默认值：1’b0；*/
/*description:设置此位以停止处理内联描述符。。*/
#define GDMA_INLINK_STOP_CH3    (BIT(21))
#define GDMA_INLINK_STOP_CH3_M  (BIT(21))
#define GDMA_INLINK_STOP_CH3_V  0x1
#define GDMA_INLINK_STOP_CH3_S  21
/* GDMA_INLINK_AUTO_RET_CH3:R/W；位位置：[20]；默认值：1’b1；*/
/*description:当当前接收数据中存在一些错误时，将此位设置为返回当前内联描述符的地址。。*/
#define GDMA_INLINK_AUTO_RET_CH3    (BIT(20))
#define GDMA_INLINK_AUTO_RET_CH3_M  (BIT(20))
#define GDMA_INLINK_AUTO_RET_CH3_V  0x1
#define GDMA_INLINK_AUTO_RET_CH3_S  20
/* GDMA_INLINK_ADDR_CH3:R/W；比特位置：[19:0]；默认值：20'00；*/
/*description:此寄存器存储第一个内联描述符地址的20个最低有效位。。*/
#define GDMA_INLINK_ADDR_CH3    0x000FFFFF
#define GDMA_INLINK_ADDR_CH3_M  ((GDMA_INLINK_ADDR_CH3_V)<<(GDMA_INLINK_ADDR_CH3_S))
#define GDMA_INLINK_ADDR_CH3_V  0xFFFFF
#define GDMA_INLINK_ADDR_CH3_S  0

#define GDMA_IN_STATE_CH3_REG          (DR_REG_GDMA_BASE + 0x264)
/* GDMA_IN_STATE_CH3:RO；比特位置：[22:20]；默认值：3'b0；*/
/*description:保留。*/
#define GDMA_IN_STATE_CH3    0x00000007
#define GDMA_IN_STATE_CH3_M  ((GDMA_IN_STATE_CH3_V)<<(GDMA_IN_STATE_CH3_S))
#define GDMA_IN_STATE_CH3_V  0x7
#define GDMA_IN_STATE_CH3_S  20
/* GDMA_IN_DSCR_STATE_CH3:RO；比特位置：[19:18]；默认值：2’b0；*/
/*description:保留。*/
#define GDMA_IN_DSCR_STATE_CH3    0x00000003
#define GDMA_IN_DSCR_STATE_CH3_M  ((GDMA_IN_DSCR_STATE_CH3_V)<<(GDMA_IN_DSCR_STATE_CH3_S))
#define GDMA_IN_DSCR_STATE_CH3_V  0x3
#define GDMA_IN_DSCR_STATE_CH3_S  18
/* GDMA_INLINK_DSCR_ADDR_CH3:RO；比特位置：[17:00]；默认值：18'b0；*/
/*description:此寄存器存储当前内联描述符的地址。。*/
#define GDMA_INLINK_DSCR_ADDR_CH3    0x0003FFFF
#define GDMA_INLINK_DSCR_ADDR_CH3_M  ((GDMA_INLINK_DSCR_ADDR_CH3_V)<<(GDMA_INLINK_DSCR_ADDR_CH3_S))
#define GDMA_INLINK_DSCR_ADDR_CH3_V  0x3FFFF
#define GDMA_INLINK_DSCR_ADDR_CH3_S  0

#define GDMA_IN_SUC_EOF_DES_ADDR_CH3_REG          (DR_REG_GDMA_BASE + 0x268)
/* GDMA_IN_SUC_EOF_DES_ADDR_CH3:RO；位位置：[31:0]；默认值：32'h0；*/
/*description:当此描述符中的EOF位为1时，此寄存器存储内联描述符的地址。。*/
#define GDMA_IN_SUC_EOF_DES_ADDR_CH3    0xFFFFFFFF
#define GDMA_IN_SUC_EOF_DES_ADDR_CH3_M  ((GDMA_IN_SUC_EOF_DES_ADDR_CH3_V)<<(GDMA_IN_SUC_EOF_DES_ADDR_CH3_S))
#define GDMA_IN_SUC_EOF_DES_ADDR_CH3_V  0xFFFFFFFF
#define GDMA_IN_SUC_EOF_DES_ADDR_CH3_S  0

#define GDMA_IN_ERR_EOF_DES_ADDR_CH3_REG          (DR_REG_GDMA_BASE + 0x26C)
/* GDMA_IN_ERR_EOF_DES_ADDR_CH3:RO；位位置：[31:0]；默认值：32'h0；*/
/*description:当当前接收数据中存在一些错误时，此寄存器存储内联描述符的地址。仅当外围设备为UHCI0时使用。。*/
#define GDMA_IN_ERR_EOF_DES_ADDR_CH3    0xFFFFFFFF
#define GDMA_IN_ERR_EOF_DES_ADDR_CH3_M  ((GDMA_IN_ERR_EOF_DES_ADDR_CH3_V)<<(GDMA_IN_ERR_EOF_DES_ADDR_CH3_S))
#define GDMA_IN_ERR_EOF_DES_ADDR_CH3_V  0xFFFFFFFF
#define GDMA_IN_ERR_EOF_DES_ADDR_CH3_S  0

#define GDMA_IN_DSCR_CH3_REG          (DR_REG_GDMA_BASE + 0x270)
/* GDMA_INLINK_DSCR_CH3:RO；位位置：[31:0]；默认值：32'b0；*/
/*description:当前内联描述符x的地址。。*/
#define GDMA_INLINK_DSCR_CH3    0xFFFFFFFF
#define GDMA_INLINK_DSCR_CH3_M  ((GDMA_INLINK_DSCR_CH3_V)<<(GDMA_INLINK_DSCR_CH3_S))
#define GDMA_INLINK_DSCR_CH3_V  0xFFFFFFFF
#define GDMA_INLINK_DSCR_CH3_S  0

#define GDMA_IN_DSCR_BF0_CH3_REG          (DR_REG_GDMA_BASE + 0x274)
/* GDMA_INLINK_DSCR_BF0_CH3:RO；位位置：[31:0]；默认值：32'b0；*/
/*description:最后一个内联描述符x-1的地址。。*/
#define GDMA_INLINK_DSCR_BF0_CH3    0xFFFFFFFF
#define GDMA_INLINK_DSCR_BF0_CH3_M  ((GDMA_INLINK_DSCR_BF0_CH3_V)<<(GDMA_INLINK_DSCR_BF0_CH3_S))
#define GDMA_INLINK_DSCR_BF0_CH3_V  0xFFFFFFFF
#define GDMA_INLINK_DSCR_BF0_CH3_S  0

#define GDMA_IN_DSCR_BF1_CH3_REG          (DR_REG_GDMA_BASE + 0x278)
/* GDMA_INLINK_DSCR_BF1_CH3:RO；位位置：[31:0]；默认值：32'b0；*/
/*description:倒数第二个内联描述符x-2的地址。。*/
#define GDMA_INLINK_DSCR_BF1_CH3    0xFFFFFFFF
#define GDMA_INLINK_DSCR_BF1_CH3_M  ((GDMA_INLINK_DSCR_BF1_CH3_V)<<(GDMA_INLINK_DSCR_BF1_CH3_S))
#define GDMA_INLINK_DSCR_BF1_CH3_V  0xFFFFFFFF
#define GDMA_INLINK_DSCR_BF1_CH3_S  0

#define GDMA_IN_WIGHT_CH3_REG          (DR_REG_GDMA_BASE + 0x27C)
/* GDMA_RX_WEIGHT_CH3:R/W；位位置：[11:8]；默认值：4'hf；*/
/*description:Rx通道3的权重。*/
#define GDMA_RX_WEIGHT_CH3    0x0000000F
#define GDMA_RX_WEIGHT_CH3_M  ((GDMA_RX_WEIGHT_CH3_V)<<(GDMA_RX_WEIGHT_CH3_S))
#define GDMA_RX_WEIGHT_CH3_V  0xF
#define GDMA_RX_WEIGHT_CH3_S  8

#define GDMA_IN_PRI_CH3_REG          (DR_REG_GDMA_BASE + 0x284)
/* GDMA_RX_PRI_CH3:R/W；位位置：[3:0]；默认值：4'b0；*/
/*description:Rx通道3的优先级。值越大，优先级越高。。*/
#define GDMA_RX_PRI_CH3    0x0000000F
#define GDMA_RX_PRI_CH3_M  ((GDMA_RX_PRI_CH3_V)<<(GDMA_RX_PRI_CH3_S))
#define GDMA_RX_PRI_CH3_V  0xF
#define GDMA_RX_PRI_CH3_S  0

#define GDMA_IN_PERI_SEL_CH3_REG          (DR_REG_GDMA_BASE + 0x288)
/* GDMA_PERI_IN_SEL_CH3:R/W；比特位置：[5:0]；默认值：6'h3f；*/
/*描述：此寄存器用于为Rx通道3.0:SPI2.1:SPI3.2:UHCI0.3:I2S0.4:I2S1.5:LCD_CAM选择外围设备。6： AES。7： 沙。8： ADC_DAC。9： RMT。。*/
#define GDMA_PERI_IN_SEL_CH3    0x0000003F
#define GDMA_PERI_IN_SEL_CH3_M  ((GDMA_PERI_IN_SEL_CH3_V)<<(GDMA_PERI_IN_SEL_CH3_S))
#define GDMA_PERI_IN_SEL_CH3_V  0x3F
#define GDMA_PERI_IN_SEL_CH3_S  0

#define GDMA_OUT_CONF0_CH3_REG          (DR_REG_GDMA_BASE + 0x2A0)
/* GDMA_OUT_DATA_BURST_EN_CH3:R/W；位位置：[5]；默认值：1’b0；*/
/*描述：当访问内部SRAM时，将此位设置为1以启用传输数据的Tx信道3的INCR突发传输。*/
#define GDMA_OUT_DATA_BURST_EN_CH3    (BIT(5))
#define GDMA_OUT_DATA_BURST_EN_CH3_M  (BIT(5))
#define GDMA_OUT_DATA_BURST_EN_CH3_V  0x1
#define GDMA_OUT_DATA_BURST_EN_CH3_S  5
/* GDMA_OUTDSCR_BURST_EN_CH3:R/W；位位置：[4]；默认值：1’b0；*/
/*description:将此位设置为1，以便在访问内部SRAM时，为Tx通道3读取链路描述符启用INCR突发传输。*/
#define GDMA_OUTDSCR_BURST_EN_CH3    (BIT(4))
#define GDMA_OUTDSCR_BURST_EN_CH3_M  (BIT(4))
#define GDMA_OUTDSCR_BURST_EN_CH3_V  0x1
#define GDMA_OUTDSCR_BURST_EN_CH3_S  4
/* GDMA_OUT_EOF_MODE_CH3:R/W；位位置：[3]；默认值：1’b1；*/
/*描述：传输数据时EOF标志生成模式。1： 当需要传输的数据已从DMA中的FIFO弹出时，生成Tx信道3的EOF标志。*/
#define GDMA_OUT_EOF_MODE_CH3    (BIT(3))
#define GDMA_OUT_EOF_MODE_CH3_M  (BIT(3))
#define GDMA_OUT_EOF_MODE_CH3_V  0x1
#define GDMA_OUT_EOF_MODE_CH3_S  3
/* GDMA_OUT_AUTO_WRBACK_CH3:R/W；位位置：[2]；默认值：1’b0；*/
/*description:设置此位以在传输tx缓冲区中的所有数据时启用自动outlink写回。。*/
#define GDMA_OUT_AUTO_WRBACK_CH3    (BIT(2))
#define GDMA_OUT_AUTO_WRBACK_CH3_M  (BIT(2))
#define GDMA_OUT_AUTO_WRBACK_CH3_V  0x1
#define GDMA_OUT_AUTO_WRBACK_CH3_S  2
/* GDMA_OUT_LOOP_TEST_CH3:R/W；位位置：[1]；默认值：1’b0；*/
/*description:保留。*/
#define GDMA_OUT_LOOP_TEST_CH3    (BIT(1))
#define GDMA_OUT_LOOP_TEST_CH3_M  (BIT(1))
#define GDMA_OUT_LOOP_TEST_CH3_V  0x1
#define GDMA_OUT_LOOP_TEST_CH3_S  1
/* GDMA_OUT_RST_CH3:R/W；位位置：[0]；默认值：1’b0；*/
/*描述：此位用于重置DMA通道3 Tx FSM和Tx FIFO指针。。*/
#define GDMA_OUT_RST_CH3    (BIT(0))
#define GDMA_OUT_RST_CH3_M  (BIT(0))
#define GDMA_OUT_RST_CH3_V  0x1
#define GDMA_OUT_RST_CH3_S  0

#define GDMA_OUT_CONF1_CH3_REG          (DR_REG_GDMA_BASE + 0x2A4)
/* GDMA_OUT_EXT_MEM_BK_SIZE_CH3:R/W；比特位置：[14:13]；默认值：2’b0；*/
/*描述：DMA访问外部SRAM时Tx通道3的块大小。0:16字节1:32字节2/3:保留。*/
#define GDMA_OUT_EXT_MEM_BK_SIZE_CH3    0x00000003
#define GDMA_OUT_EXT_MEM_BK_SIZE_CH3_M  ((GDMA_OUT_EXT_MEM_BK_SIZE_CH3_V)<<(GDMA_OUT_EXT_MEM_BK_SIZE_CH3_S))
#define GDMA_OUT_EXT_MEM_BK_SIZE_CH3_V  0x3
#define GDMA_OUT_EXT_MEM_BK_SIZE_CH3_S  13
/* GDMA_OUT_CHECK_OWNER_CH3:R/W；位位置：[12]；默认值：1’b0；*/
/*description:设置此位以启用检查链接描述符的所有者属性。。*/
#define GDMA_OUT_CHECK_OWNER_CH3    (BIT(12))
#define GDMA_OUT_CHECK_OWNER_CH3_M  (BIT(12))
#define GDMA_OUT_CHECK_OWNER_CH3_V  0x1
#define GDMA_OUT_CHECK_OWNER_CH3_S  12

#define GDMA_OUT_INT_RAW_CH3_REG          (DR_REG_GDMA_BASE + 0x2A8)
/* GDMA_OUTFIFO_UDF_L3_CH3_INT_RAW:R/WTC/SS；位位置：[7]；默认值：1’b0；*/
/*描述：当Tx信道3的第3级fifo未满流时，此原始中断位变为高电平。*/
#define GDMA_OUTFIFO_UDF_L3_CH3_INT_RAW    (BIT(7))
#define GDMA_OUTFIFO_UDF_L3_CH3_INT_RAW_M  (BIT(7))
#define GDMA_OUTFIFO_UDF_L3_CH3_INT_RAW_V  0x1
#define GDMA_OUTFIFO_UDF_L3_CH3_INT_RAW_S  7
/* GDMA_OUTFIFO_off_L3_CH3_INT_RAW:R/WTC/SS；位位置：[6]；默认值：1’b0；*/
/*描述：当Tx信道3的3级fifo等流量时，此原始中断位变为高电平。*/
#define GDMA_OUTFIFO_OVF_L3_CH3_INT_RAW    (BIT(6))
#define GDMA_OUTFIFO_OVF_L3_CH3_INT_RAW_M  (BIT(6))
#define GDMA_OUTFIFO_OVF_L3_CH3_INT_RAW_V  0x1
#define GDMA_OUTFIFO_OVF_L3_CH3_INT_RAW_S  6
/* GDMA_OUTFIFO_UDF_L1_CH3_INT_RAW:R/WTC/SS；位位置：[5]；默认值：1’b0；*/
/*描述：当Tx信道3的第1级fifo未满流时，此原始中断位变为高电平。*/
#define GDMA_OUTFIFO_UDF_L1_CH3_INT_RAW    (BIT(5))
#define GDMA_OUTFIFO_UDF_L1_CH3_INT_RAW_M  (BIT(5))
#define GDMA_OUTFIFO_UDF_L1_CH3_INT_RAW_V  0x1
#define GDMA_OUTFIFO_UDF_L1_CH3_INT_RAW_S  5
/* GDMA_OUTFIFO_off_L1_CH3_INT_RAW:R/WTC/SS；位位置：[4]；默认值：1’b0；*/
/*描述：当Tx信道3的1级fifo等流量时，此原始中断位变为高电平。*/
#define GDMA_OUTFIFO_OVF_L1_CH3_INT_RAW    (BIT(4))
#define GDMA_OUTFIFO_OVF_L1_CH3_INT_RAW_M  (BIT(4))
#define GDMA_OUTFIFO_OVF_L1_CH3_INT_RAW_V  0x1
#define GDMA_OUTFIFO_OVF_L1_CH3_INT_RAW_S  4
/* GDMA_OUT_TOTAL_EOF_CH3_INT_RAW:R/WTC/SS；位位置：[3]；默认值：1’b0；*/
/*描述：当针对Tx信道3发送出与输出链接（包括一个链路描述符或几个链路描述符）相对应的数据时，原始中断位变为高电平。。*/
#define GDMA_OUT_TOTAL_EOF_CH3_INT_RAW    (BIT(3))
#define GDMA_OUT_TOTAL_EOF_CH3_INT_RAW_M  (BIT(3))
#define GDMA_OUT_TOTAL_EOF_CH3_INT_RAW_V  0x1
#define GDMA_OUT_TOTAL_EOF_CH3_INT_RAW_S  3
/* GDMA_OUT_DSCR_ERR_CH3_INT_RAW:R/WTC/SS；位位置：[2]；默认值：1’b0；*/
/*描述：当检测到outlink描述符错误时，原始中断位变为高电平，包括所有者错误、Tx信道3的outlink描述符的第二个和第三个字错误。。*/
#define GDMA_OUT_DSCR_ERR_CH3_INT_RAW    (BIT(2))
#define GDMA_OUT_DSCR_ERR_CH3_INT_RAW_M  (BIT(2))
#define GDMA_OUT_DSCR_ERR_CH3_INT_RAW_V  0x1
#define GDMA_OUT_DSCR_ERR_CH3_INT_RAW_S  2
/* GDMA_OUT_EOF_CH3_INT_RAW:R/WTC/SS；位位置：[1]；默认值：1’b0；*/
/*描述：当从Tx信道3的存储器中读取一个输出描述符所指向的最后一个数据时，原始中断位变为高电平。*/
#define GDMA_OUT_EOF_CH3_INT_RAW    (BIT(1))
#define GDMA_OUT_EOF_CH3_INT_RAW_M  (BIT(1))
#define GDMA_OUT_EOF_CH3_INT_RAW_V  0x1
#define GDMA_OUT_EOF_CH3_INT_RAW_S  1
/* GDMA_OUT_DONE_CH3_INT_RAW:R/WTC/SS；位位置：[0]；默认值：1’b0；*/
/*描述：当一个输出描述符所指向的最后一个数据已传输到Tx信道3的外围设备时，原始中断位变为高电平。。*/
#define GDMA_OUT_DONE_CH3_INT_RAW    (BIT(0))
#define GDMA_OUT_DONE_CH3_INT_RAW_M  (BIT(0))
#define GDMA_OUT_DONE_CH3_INT_RAW_V  0x1
#define GDMA_OUT_DONE_CH3_INT_RAW_S  0

#define GDMA_OUT_INT_ST_CH3_REG          (DR_REG_GDMA_BASE + 0x2AC)
/* GDMA_OUTFIFO_UDF_L3_CH3_INT_ST:RO；位位置：[7]；默认值：1’b0；*/
/*description:OUTFIFO_UDF_L3_CH_INT中断的原始中断状态位。。*/
#define GDMA_OUTFIFO_UDF_L3_CH3_INT_ST    (BIT(7))
#define GDMA_OUTFIFO_UDF_L3_CH3_INT_ST_M  (BIT(7))
#define GDMA_OUTFIFO_UDF_L3_CH3_INT_ST_V  0x1
#define GDMA_OUTFIFO_UDF_L3_CH3_INT_ST_S  7
/* GDMA_OUTFIFO_off_L3_CH3_INT_ST:RO；位位置：[6]；默认值：1’b0；*/
/*description:OUTFIFO_OVF_L3_CH_INT中断的原始中断状态位。。*/
#define GDMA_OUTFIFO_OVF_L3_CH3_INT_ST    (BIT(6))
#define GDMA_OUTFIFO_OVF_L3_CH3_INT_ST_M  (BIT(6))
#define GDMA_OUTFIFO_OVF_L3_CH3_INT_ST_V  0x1
#define GDMA_OUTFIFO_OVF_L3_CH3_INT_ST_S  6
/* GDMA_OUTFIFO_UDF_L1_CH3_INT_ST:RO；位位置：[5]；默认值：1’b0；*/
/*description:OUTFIFO_UDF_L1_CH_INT中断的原始中断状态位。。*/
#define GDMA_OUTFIFO_UDF_L1_CH3_INT_ST    (BIT(5))
#define GDMA_OUTFIFO_UDF_L1_CH3_INT_ST_M  (BIT(5))
#define GDMA_OUTFIFO_UDF_L1_CH3_INT_ST_V  0x1
#define GDMA_OUTFIFO_UDF_L1_CH3_INT_ST_S  5
/* GDMA_OUTFIFO_off_L1_CH3_INT_ST:RO；位位置：[4]；默认值：1’b0；*/
/*description:OUTFIFO_OVF_L1_CH_INT中断的原始中断状态位。。*/
#define GDMA_OUTFIFO_OVF_L1_CH3_INT_ST    (BIT(4))
#define GDMA_OUTFIFO_OVF_L1_CH3_INT_ST_M  (BIT(4))
#define GDMA_OUTFIFO_OVF_L1_CH3_INT_ST_V  0x1
#define GDMA_OUTFIFO_OVF_L1_CH3_INT_ST_S  4
/* GDMA_OUT_TOTAL_EOF_CH3_INT_ST:RO；位位置：[3]；默认值：1’b0；*/
/*description:OUT_TOTAL_EOF_CH_INT中断的原始中断状态位。。*/
#define GDMA_OUT_TOTAL_EOF_CH3_INT_ST    (BIT(3))
#define GDMA_OUT_TOTAL_EOF_CH3_INT_ST_M  (BIT(3))
#define GDMA_OUT_TOTAL_EOF_CH3_INT_ST_V  0x1
#define GDMA_OUT_TOTAL_EOF_CH3_INT_ST_S  3
/* GDMA_OUT_DSCR_ERR_CH3_INT_ST:RO；位位置：[2]；默认值：1’b0；*/
/*description:OUT_DSCR_ERR_CH_INT中断的原始中断状态位。。*/
#define GDMA_OUT_DSCR_ERR_CH3_INT_ST    (BIT(2))
#define GDMA_OUT_DSCR_ERR_CH3_INT_ST_M  (BIT(2))
#define GDMA_OUT_DSCR_ERR_CH3_INT_ST_V  0x1
#define GDMA_OUT_DSCR_ERR_CH3_INT_ST_S  2
/* GDMA_OUT_EOF_CH3_INT_ST:RO；位位置：[1]；默认值：1’b0；*/
/*description:OUT_EOF_CH_INT中断的原始中断状态位。。*/
#define GDMA_OUT_EOF_CH3_INT_ST    (BIT(1))
#define GDMA_OUT_EOF_CH3_INT_ST_M  (BIT(1))
#define GDMA_OUT_EOF_CH3_INT_ST_V  0x1
#define GDMA_OUT_EOF_CH3_INT_ST_S  1
/* GDMA_OUT_DONE_CH3_INT_ST:RO；位位置：[0]；默认值：1’b0；*/
/*description:OUT_DONE_CH_INT中断的原始中断状态位。。*/
#define GDMA_OUT_DONE_CH3_INT_ST    (BIT(0))
#define GDMA_OUT_DONE_CH3_INT_ST_M  (BIT(0))
#define GDMA_OUT_DONE_CH3_INT_ST_V  0x1
#define GDMA_OUT_DONE_CH3_INT_ST_S  0

#define GDMA_OUT_INT_ENA_CH3_REG          (DR_REG_GDMA_BASE + 0x2B0)
/* GDMA_OUTFIFO_UDF_L3_CH3_INT_ENA:R/W；位位置：[7]；默认值：1’b0；*/
/*description:OUTFIFO_UDF_L3_CH_INT中断的中断启用位。。*/
#define GDMA_OUTFIFO_UDF_L3_CH3_INT_ENA    (BIT(7))
#define GDMA_OUTFIFO_UDF_L3_CH3_INT_ENA_M  (BIT(7))
#define GDMA_OUTFIFO_UDF_L3_CH3_INT_ENA_V  0x1
#define GDMA_OUTFIFO_UDF_L3_CH3_INT_ENA_S  7
/* GDMA_OUTFIFO_off_13_CH3_INT_ENA:R/W；位位置：[6]；默认值：1’b0；*/
/*description:OUTFIFO_OVF_L3_CH_INT中断的中断启用位。。*/
#define GDMA_OUTFIFO_OVF_L3_CH3_INT_ENA    (BIT(6))
#define GDMA_OUTFIFO_OVF_L3_CH3_INT_ENA_M  (BIT(6))
#define GDMA_OUTFIFO_OVF_L3_CH3_INT_ENA_V  0x1
#define GDMA_OUTFIFO_OVF_L3_CH3_INT_ENA_S  6
/* GDMA_OUTFIFO_UDF_L1_CH3_INT_ENA:R/W；位位置：[5]；默认值：1’b0；*/
/*description:OUTFIFO_UDF_L1_CH_INT中断的中断启用位。。*/
#define GDMA_OUTFIFO_UDF_L1_CH3_INT_ENA    (BIT(5))
#define GDMA_OUTFIFO_UDF_L1_CH3_INT_ENA_M  (BIT(5))
#define GDMA_OUTFIFO_UDF_L1_CH3_INT_ENA_V  0x1
#define GDMA_OUTFIFO_UDF_L1_CH3_INT_ENA_S  5
/* GDMA_OUTFIFO_off_L1_CH3_INT_ENA:R/W；位位置：[4]；默认值：1’b0；*/
/*description:OUTFIFO_OVF_L1_CH_INT中断的中断启用位。。*/
#define GDMA_OUTFIFO_OVF_L1_CH3_INT_ENA    (BIT(4))
#define GDMA_OUTFIFO_OVF_L1_CH3_INT_ENA_M  (BIT(4))
#define GDMA_OUTFIFO_OVF_L1_CH3_INT_ENA_V  0x1
#define GDMA_OUTFIFO_OVF_L1_CH3_INT_ENA_S  4
/* GDMA_OUT_TOTAL_EOF_CH3_INT_ENA:R/W；位位置：[3]；默认值：1’b0；*/
/*description:OUT_TOTAL_EOF_CH_INT中断的中断启用位。。*/
#define GDMA_OUT_TOTAL_EOF_CH3_INT_ENA    (BIT(3))
#define GDMA_OUT_TOTAL_EOF_CH3_INT_ENA_M  (BIT(3))
#define GDMA_OUT_TOTAL_EOF_CH3_INT_ENA_V  0x1
#define GDMA_OUT_TOTAL_EOF_CH3_INT_ENA_S  3
/* GDMA_OUT_DSCR_ERR_CH3_INT_ENA:R/W；位位置：[2]；默认值：1’b0；*/
/*description:OUT_DSCR_ERR_CH_INT中断的中断启用位。。*/
#define GDMA_OUT_DSCR_ERR_CH3_INT_ENA    (BIT(2))
#define GDMA_OUT_DSCR_ERR_CH3_INT_ENA_M  (BIT(2))
#define GDMA_OUT_DSCR_ERR_CH3_INT_ENA_V  0x1
#define GDMA_OUT_DSCR_ERR_CH3_INT_ENA_S  2
/* GDMA_OUT_EOF_CH3_INT_ENA:R/W；位位置：[1]；默认值：1’b0；*/
/*description:OUT_EOF_CH_INT中断的中断启用位。。*/
#define GDMA_OUT_EOF_CH3_INT_ENA    (BIT(1))
#define GDMA_OUT_EOF_CH3_INT_ENA_M  (BIT(1))
#define GDMA_OUT_EOF_CH3_INT_ENA_V  0x1
#define GDMA_OUT_EOF_CH3_INT_ENA_S  1
/* GDMA_OUT_DONE_CH3_INT_ENA:R/W；位位置：[0]；默认值：1’b0；*/
/*description:OUT_DONE_CH_INT中断的中断启用位。。*/
#define GDMA_OUT_DONE_CH3_INT_ENA    (BIT(0))
#define GDMA_OUT_DONE_CH3_INT_ENA_M  (BIT(0))
#define GDMA_OUT_DONE_CH3_INT_ENA_V  0x1
#define GDMA_OUT_DONE_CH3_INT_ENA_S  0

#define GDMA_OUT_INT_CLR_CH3_REG          (DR_REG_GDMA_BASE + 0x2B4)
/* GDMA_OUTFIFO_UDF_13_CH3_INT_CLR:WO；位位置：[7]；默认值：1’b0；*/
/*description:设置此位以清除OUTFIFO_UDF_L3_CH_INT中断。。*/
#define GDMA_OUTFIFO_UDF_L3_CH3_INT_CLR    (BIT(7))
#define GDMA_OUTFIFO_UDF_L3_CH3_INT_CLR_M  (BIT(7))
#define GDMA_OUTFIFO_UDF_L3_CH3_INT_CLR_V  0x1
#define GDMA_OUTFIFO_UDF_L3_CH3_INT_CLR_S  7
/* GDMA_OUTFIFO_off_13_CH3_INT_CLR:WO；位位置：[6]；默认值：1’b0；*/
/*description:设置此位以清除OUTFIFO_OVF_L3_CH_INT中断。。*/
#define GDMA_OUTFIFO_OVF_L3_CH3_INT_CLR    (BIT(6))
#define GDMA_OUTFIFO_OVF_L3_CH3_INT_CLR_M  (BIT(6))
#define GDMA_OUTFIFO_OVF_L3_CH3_INT_CLR_V  0x1
#define GDMA_OUTFIFO_OVF_L3_CH3_INT_CLR_S  6
/* GDMA_OUTFIFO_UDF_L1_CH3_INT_CLR:WO；位位置：[5]；默认值：1’b0；*/
/*description:设置此位以清除OUTFIFO_UDF_L1_CH_INT中断。。*/
#define GDMA_OUTFIFO_UDF_L1_CH3_INT_CLR    (BIT(5))
#define GDMA_OUTFIFO_UDF_L1_CH3_INT_CLR_M  (BIT(5))
#define GDMA_OUTFIFO_UDF_L1_CH3_INT_CLR_V  0x1
#define GDMA_OUTFIFO_UDF_L1_CH3_INT_CLR_S  5
/* GDMA_OUTFIFO_off_L1_CH3_INT_CLR:WO；位位置：[4]；默认值：1’b0；*/
/*description:设置此位以清除OUTFIFO_OVF_L1_CH_INT中断。。*/
#define GDMA_OUTFIFO_OVF_L1_CH3_INT_CLR    (BIT(4))
#define GDMA_OUTFIFO_OVF_L1_CH3_INT_CLR_M  (BIT(4))
#define GDMA_OUTFIFO_OVF_L1_CH3_INT_CLR_V  0x1
#define GDMA_OUTFIFO_OVF_L1_CH3_INT_CLR_S  4
/* GDMA_OUT_TOTAL_EOF_CH3_INT_CLR:WT；位位置：[3]；默认值：1’b0；*/
/*description:设置此位以清除OUT_TOTAL_EOF_CH_INT中断。。*/
#define GDMA_OUT_TOTAL_EOF_CH3_INT_CLR    (BIT(3))
#define GDMA_OUT_TOTAL_EOF_CH3_INT_CLR_M  (BIT(3))
#define GDMA_OUT_TOTAL_EOF_CH3_INT_CLR_V  0x1
#define GDMA_OUT_TOTAL_EOF_CH3_INT_CLR_S  3
/* GDMA_OUT_DSCR_ERR_CH3_INT_CLR:WT；位位置：[2]；默认值：1’b0；*/
/*description:设置此位以清除OUT_DSCR_ERR_CH_INT中断。。*/
#define GDMA_OUT_DSCR_ERR_CH3_INT_CLR    (BIT(2))
#define GDMA_OUT_DSCR_ERR_CH3_INT_CLR_M  (BIT(2))
#define GDMA_OUT_DSCR_ERR_CH3_INT_CLR_V  0x1
#define GDMA_OUT_DSCR_ERR_CH3_INT_CLR_S  2
/* GDMA_OUT_EOF_CH3_INT_CLR:WT；位位置：[1]；默认值：1’b0；*/
/*description:设置此位以清除OUT_EOF_CH_INT中断。。*/
#define GDMA_OUT_EOF_CH3_INT_CLR    (BIT(1))
#define GDMA_OUT_EOF_CH3_INT_CLR_M  (BIT(1))
#define GDMA_OUT_EOF_CH3_INT_CLR_V  0x1
#define GDMA_OUT_EOF_CH3_INT_CLR_S  1
/* GDMA_OUT_DONE_CH3_INT_CLR:WT；位位置：[0]；默认值：1’b0；*/
/*description:设置此位以清除OUT_DONE_CH_INT中断。。*/
#define GDMA_OUT_DONE_CH3_INT_CLR    (BIT(0))
#define GDMA_OUT_DONE_CH3_INT_CLR_M  (BIT(0))
#define GDMA_OUT_DONE_CH3_INT_CLR_V  0x1
#define GDMA_OUT_DONE_CH3_INT_CLR_S  0

#define GDMA_OUTFIFO_STATUS_CH3_REG          (DR_REG_GDMA_BASE + 0x2B8)
/* GDMA_OUT_REMAIN_UNDER_4B_L3_CH3:RO；位位置：[26]；默认值：1’b1；*/
/*description:保留。*/
#define GDMA_OUT_REMAIN_UNDER_4B_L3_CH3    (BIT(26))
#define GDMA_OUT_REMAIN_UNDER_4B_L3_CH3_M  (BIT(26))
#define GDMA_OUT_REMAIN_UNDER_4B_L3_CH3_V  0x1
#define GDMA_OUT_REMAIN_UNDER_4B_L3_CH3_S  26
/* GDMA_OUT_REMAIN_UNDER_3B_L3_CH3:RO；位位置：[25]；默认值：1’b1；*/
/*description:保留。*/
#define GDMA_OUT_REMAIN_UNDER_3B_L3_CH3    (BIT(25))
#define GDMA_OUT_REMAIN_UNDER_3B_L3_CH3_M  (BIT(25))
#define GDMA_OUT_REMAIN_UNDER_3B_L3_CH3_V  0x1
#define GDMA_OUT_REMAIN_UNDER_3B_L3_CH3_S  25
/* GDMA_OUT_REMAIN_UNDER_2B_L3_CH3:RO；位位置：[24]；默认值：1’b1；*/
/*description:保留。*/
#define GDMA_OUT_REMAIN_UNDER_2B_L3_CH3    (BIT(24))
#define GDMA_OUT_REMAIN_UNDER_2B_L3_CH3_M  (BIT(24))
#define GDMA_OUT_REMAIN_UNDER_2B_L3_CH3_V  0x1
#define GDMA_OUT_REMAIN_UNDER_2B_L3_CH3_S  24
/* GDMA_OUT_REMAIN_UNDER_1B_L3_CH3:RO；位位置：[23]；默认值：1’b1；*/
/*description:保留。*/
#define GDMA_OUT_REMAIN_UNDER_1B_L3_CH3    (BIT(23))
#define GDMA_OUT_REMAIN_UNDER_1B_L3_CH3_M  (BIT(23))
#define GDMA_OUT_REMAIN_UNDER_1B_L3_CH3_V  0x1
#define GDMA_OUT_REMAIN_UNDER_1B_L3_CH3_S  23
/* GDMA_OUTFIFO_CNT_L3_CH3:RO；比特位置：[22:18]；默认值：5’b0；*/
/*描述：寄存器将数据的字节数存储在Tx信道3的L3 Tx FIFO中。。*/
#define GDMA_OUTFIFO_CNT_L3_CH3    0x0000001F
#define GDMA_OUTFIFO_CNT_L3_CH3_M  ((GDMA_OUTFIFO_CNT_L3_CH3_V)<<(GDMA_OUTFIFO_CNT_L3_CH3_S))
#define GDMA_OUTFIFO_CNT_L3_CH3_V  0x1F
#define GDMA_OUTFIFO_CNT_L3_CH3_S  18
/* GDMA_OUTFIFO_CNT_L2_CH3:RO；比特位置：[17:11]；默认值：7'b0；*/
/*描述：寄存器将数据的字节数存储在Tx信道3的L2 Tx FIFO中。。*/
#define GDMA_OUTFIFO_CNT_L2_CH3    0x0000007F
#define GDMA_OUTFIFO_CNT_L2_CH3_M  ((GDMA_OUTFIFO_CNT_L2_CH3_V)<<(GDMA_OUTFIFO_CNT_L2_CH3_S))
#define GDMA_OUTFIFO_CNT_L2_CH3_V  0x7F
#define GDMA_OUTFIFO_CNT_L2_CH3_S  11
/* GDMA_OUTFIFO_CNT_L1_CH3:RO；比特位置：[10:6]；默认值：5’b0；*/
/*描述：寄存器将数据的字节数存储在Tx信道3的L1 Tx FIFO中。。*/
#define GDMA_OUTFIFO_CNT_L1_CH3    0x0000001F
#define GDMA_OUTFIFO_CNT_L1_CH3_M  ((GDMA_OUTFIFO_CNT_L1_CH3_V)<<(GDMA_OUTFIFO_CNT_L1_CH3_S))
#define GDMA_OUTFIFO_CNT_L1_CH3_V  0x1F
#define GDMA_OUTFIFO_CNT_L1_CH3_S  6
/* GDMA_OUTFIFO_EMPTY_L3_CH3:RO；位位置：[5]；默认值：1’b1；*/
/*描述：Tx信道3的L3 Tx FIFO空信号。。*/
#define GDMA_OUTFIFO_EMPTY_L3_CH3    (BIT(5))
#define GDMA_OUTFIFO_EMPTY_L3_CH3_M  (BIT(5))
#define GDMA_OUTFIFO_EMPTY_L3_CH3_V  0x1
#define GDMA_OUTFIFO_EMPTY_L3_CH3_S  5
/* GDMA_OUTFIFO_FULL_L3_CH3:RO；位位置：[4]；默认值：1’b0；*/
/*描述：Tx信道3的L3 Tx FIFO满信号。。*/
#define GDMA_OUTFIFO_FULL_L3_CH3    (BIT(4))
#define GDMA_OUTFIFO_FULL_L3_CH3_M  (BIT(4))
#define GDMA_OUTFIFO_FULL_L3_CH3_V  0x1
#define GDMA_OUTFIFO_FULL_L3_CH3_S  4
/* GDMA_OUTFIFO_EMPTY_L2_CH3:RO；位位置：[3]；默认值：1’b1；*/
/*描述：Tx信道3的L2 Tx FIFO空信号。。*/
#define GDMA_OUTFIFO_EMPTY_L2_CH3    (BIT(3))
#define GDMA_OUTFIFO_EMPTY_L2_CH3_M  (BIT(3))
#define GDMA_OUTFIFO_EMPTY_L2_CH3_V  0x1
#define GDMA_OUTFIFO_EMPTY_L2_CH3_S  3
/* GDMA_OUTFIFO_FULL_L2_CH3:RO；位位置：[2]；默认值：1’b0；*/
/*描述：Tx信道3的L2 Tx FIFO满信号。。*/
#define GDMA_OUTFIFO_FULL_L2_CH3    (BIT(2))
#define GDMA_OUTFIFO_FULL_L2_CH3_M  (BIT(2))
#define GDMA_OUTFIFO_FULL_L2_CH3_V  0x1
#define GDMA_OUTFIFO_FULL_L2_CH3_S  2
/* GDMA_OUTFIFO_EMPTY_L1_CH3:RO；位位置：[1]；默认值：1’b1；*/
/*描述：Tx信道3的L1 Tx FIFO空信号。。*/
#define GDMA_OUTFIFO_EMPTY_L1_CH3    (BIT(1))
#define GDMA_OUTFIFO_EMPTY_L1_CH3_M  (BIT(1))
#define GDMA_OUTFIFO_EMPTY_L1_CH3_V  0x1
#define GDMA_OUTFIFO_EMPTY_L1_CH3_S  1
/* GDMA_OUTFIFO_FULL_L1_CH3:RO；位位置：[0]；默认值：1’b0；*/
/*描述：Tx信道3的L1 Tx FIFO满信号。。*/
#define GDMA_OUTFIFO_FULL_L1_CH3    (BIT(0))
#define GDMA_OUTFIFO_FULL_L1_CH3_M  (BIT(0))
#define GDMA_OUTFIFO_FULL_L1_CH3_V  0x1
#define GDMA_OUTFIFO_FULL_L1_CH3_S  0

#define GDMA_OUT_PUSH_CH3_REG          (DR_REG_GDMA_BASE + 0x2BC)
/* GDMA_OUTFIFO_PUSH_CH3:R/W/SC；位位置：[9]；默认值：1'0；*/
/*description:设置此位以将数据推入DMA FIFO。。*/
#define GDMA_OUTFIFO_PUSH_CH3    (BIT(9))
#define GDMA_OUTFIFO_PUSH_CH3_M  (BIT(9))
#define GDMA_OUTFIFO_PUSH_CH3_V  0x1
#define GDMA_OUTFIFO_PUSH_CH3_S  9
/* GDMA_OUTFIFO_WDATA_CH3:R/W；位位置：[8:0]；默认值：9'0；*/
/*description:此寄存器存储需要推入DMA FIFO的数据。。*/
#define GDMA_OUTFIFO_WDATA_CH3    0x000001FF
#define GDMA_OUTFIFO_WDATA_CH3_M  ((GDMA_OUTFIFO_WDATA_CH3_V)<<(GDMA_OUTFIFO_WDATA_CH3_S))
#define GDMA_OUTFIFO_WDATA_CH3_V  0x1FF
#define GDMA_OUTFIFO_WDATA_CH3_S  0

#define GDMA_OUT_LINK_CH3_REG          (DR_REG_GDMA_BASE + 0x2C0)
/* GDMA_OUTLINK_PARK_CH3:RO；位位置：[23]；默认值：1'h1；*/
/*描述：1:outlink描述符的FSM处于空闲状态。0:outlink描述符的FSM正在工作。。*/
#define GDMA_OUTLINK_PARK_CH3    (BIT(23))
#define GDMA_OUTLINK_PARK_CH3_M  (BIT(23))
#define GDMA_OUTLINK_PARK_CH3_V  0x1
#define GDMA_OUTLINK_PARK_CH3_S  23
/* GDMA_OUTLINK_RESTART_CH3:R/W/SC；位位置：[22]；默认值：1’b0；*/
/*description:设置此位以从上一个地址重新启动新的outlink。*/
#define GDMA_OUTLINK_RESTART_CH3    (BIT(22))
#define GDMA_OUTLINK_RESTART_CH3_M  (BIT(22))
#define GDMA_OUTLINK_RESTART_CH3_V  0x1
#define GDMA_OUTLINK_RESTART_CH3_S  22
/* GDMA_OUTLINK_START_CH3:R/W/SC；位位置：[21]；默认值：1’b0；*/
/*description:设置此位以开始处理outlink描述符。。*/
#define GDMA_OUTLINK_START_CH3    (BIT(21))
#define GDMA_OUTLINK_START_CH3_M  (BIT(21))
#define GDMA_OUTLINK_START_CH3_V  0x1
#define GDMA_OUTLINK_START_CH3_S  21
/* GDMA_OUTLINK_STOP_CH3:R/W/SC；位位置：[20]；默认值：1’b0；*/
/*description:设置此位以停止处理outlink描述符。。*/
#define GDMA_OUTLINK_STOP_CH3    (BIT(20))
#define GDMA_OUTLINK_STOP_CH3_M  (BIT(20))
#define GDMA_OUTLINK_STOP_CH3_V  0x1
#define GDMA_OUTLINK_STOP_CH3_S  20
/* GDMA_OUTLINK_ADDR_CH3:R/W；比特位置：[19:0]；默认值：20'00；*/
/*description:此寄存器存储第一个outlink描述符地址的20个最低有效位。。*/
#define GDMA_OUTLINK_ADDR_CH3    0x000FFFFF
#define GDMA_OUTLINK_ADDR_CH3_M  ((GDMA_OUTLINK_ADDR_CH3_V)<<(GDMA_OUTLINK_ADDR_CH3_S))
#define GDMA_OUTLINK_ADDR_CH3_V  0xFFFFF
#define GDMA_OUTLINK_ADDR_CH3_S  0

#define GDMA_OUT_STATE_CH3_REG          (DR_REG_GDMA_BASE + 0x2C4)
/* GDMA_OUT_STATE_CH3:RO；比特位置：[22:20]；默认值：3'b0；*/
/*description:保留。*/
#define GDMA_OUT_STATE_CH3    0x00000007
#define GDMA_OUT_STATE_CH3_M  ((GDMA_OUT_STATE_CH3_V)<<(GDMA_OUT_STATE_CH3_S))
#define GDMA_OUT_STATE_CH3_V  0x7
#define GDMA_OUT_STATE_CH3_S  20
/* GDMA_OUT_DSCR_STATE_CH3:RO；比特位置：[19:18]；默认值：2’b0；*/
/*description:保留。*/
#define GDMA_OUT_DSCR_STATE_CH3    0x00000003
#define GDMA_OUT_DSCR_STATE_CH3_M  ((GDMA_OUT_DSCR_STATE_CH3_V)<<(GDMA_OUT_DSCR_STATE_CH3_S))
#define GDMA_OUT_DSCR_STATE_CH3_V  0x3
#define GDMA_OUT_DSCR_STATE_CH3_S  18
/* GDMA_OUTLINK_DSCR_ADDR_CH3:RO；比特位置：[17:00]；默认值：18'b0；*/
/*description:此寄存器存储当前outlink描述符的地址。。*/
#define GDMA_OUTLINK_DSCR_ADDR_CH3    0x0003FFFF
#define GDMA_OUTLINK_DSCR_ADDR_CH3_M  ((GDMA_OUTLINK_DSCR_ADDR_CH3_V)<<(GDMA_OUTLINK_DSCR_ADDR_CH3_S))
#define GDMA_OUTLINK_DSCR_ADDR_CH3_V  0x3FFFF
#define GDMA_OUTLINK_DSCR_ADDR_CH3_S  0

#define GDMA_OUT_EOF_DES_ADDR_CH3_REG          (DR_REG_GDMA_BASE + 0x2C8)
/* GDMA_OUT_EOF_DES_ADDR_CH3:RO；位位置：[31:0]；默认值：32'h0；*/
/*description:当此描述符中的EOF位为1时，此寄存器存储outlink描述符的地址。。*/
#define GDMA_OUT_EOF_DES_ADDR_CH3    0xFFFFFFFF
#define GDMA_OUT_EOF_DES_ADDR_CH3_M  ((GDMA_OUT_EOF_DES_ADDR_CH3_V)<<(GDMA_OUT_EOF_DES_ADDR_CH3_S))
#define GDMA_OUT_EOF_DES_ADDR_CH3_V  0xFFFFFFFF
#define GDMA_OUT_EOF_DES_ADDR_CH3_S  0

#define GDMA_OUT_EOF_BFR_DES_ADDR_CH3_REG          (DR_REG_GDMA_BASE + 0x2CC)
/* GDMA_OUT_EOF_BFR_DES_ADDR_CH3:RO；位位置：[31:0]；默认值：32'h0；*/
/*description:此寄存器存储最后一个outlink描述符之前的outlink描述符的地址。。*/
#define GDMA_OUT_EOF_BFR_DES_ADDR_CH3    0xFFFFFFFF
#define GDMA_OUT_EOF_BFR_DES_ADDR_CH3_M  ((GDMA_OUT_EOF_BFR_DES_ADDR_CH3_V)<<(GDMA_OUT_EOF_BFR_DES_ADDR_CH3_S))
#define GDMA_OUT_EOF_BFR_DES_ADDR_CH3_V  0xFFFFFFFF
#define GDMA_OUT_EOF_BFR_DES_ADDR_CH3_S  0

#define GDMA_OUT_DSCR_CH3_REG          (DR_REG_GDMA_BASE + 0x2D0)
/* GDMA_OUTLINK_DSCR_CH3:RO；位位置：[31:0]；默认值：32'b0；*/
/*description:当前outlink描述符y的地址。。*/
#define GDMA_OUTLINK_DSCR_CH3    0xFFFFFFFF
#define GDMA_OUTLINK_DSCR_CH3_M  ((GDMA_OUTLINK_DSCR_CH3_V)<<(GDMA_OUTLINK_DSCR_CH3_S))
#define GDMA_OUTLINK_DSCR_CH3_V  0xFFFFFFFF
#define GDMA_OUTLINK_DSCR_CH3_S  0

#define GDMA_OUT_DSCR_BF0_CH3_REG          (DR_REG_GDMA_BASE + 0x2D4)
/* GDMA_OUTLINK_DSCR_BF0_CH3:RO；位位置：[31:0]；默认值：32'b0；*/
/*description:最后一个outlink描述符的地址y-1。。*/
#define GDMA_OUTLINK_DSCR_BF0_CH3    0xFFFFFFFF
#define GDMA_OUTLINK_DSCR_BF0_CH3_M  ((GDMA_OUTLINK_DSCR_BF0_CH3_V)<<(GDMA_OUTLINK_DSCR_BF0_CH3_S))
#define GDMA_OUTLINK_DSCR_BF0_CH3_V  0xFFFFFFFF
#define GDMA_OUTLINK_DSCR_BF0_CH3_S  0

#define GDMA_OUT_DSCR_BF1_CH3_REG          (DR_REG_GDMA_BASE + 0x2D8)
/* GDMA_OUTLINK_DSCR_BF1_CH3:RO；位位置：[31:0]；默认值：32'b0；*/
/*description:倒数第二个内联描述符x-2的地址。。*/
#define GDMA_OUTLINK_DSCR_BF1_CH3    0xFFFFFFFF
#define GDMA_OUTLINK_DSCR_BF1_CH3_M  ((GDMA_OUTLINK_DSCR_BF1_CH3_V)<<(GDMA_OUTLINK_DSCR_BF1_CH3_S))
#define GDMA_OUTLINK_DSCR_BF1_CH3_V  0xFFFFFFFF
#define GDMA_OUTLINK_DSCR_BF1_CH3_S  0

#define GDMA_OUT_WIGHT_CH3_REG          (DR_REG_GDMA_BASE + 0x2DC)
/* GDMA_TX_WEIGHT_CH3:R/W；位位置：[11:8]；默认值：4'hf；*/
/*description:Tx信道3的权重。*/
#define GDMA_TX_WEIGHT_CH3    0x0000000F
#define GDMA_TX_WEIGHT_CH3_M  ((GDMA_TX_WEIGHT_CH3_V)<<(GDMA_TX_WEIGHT_CH3_S))
#define GDMA_TX_WEIGHT_CH3_V  0xF
#define GDMA_TX_WEIGHT_CH3_S  8

#define GDMA_OUT_PRI_CH3_REG          (DR_REG_GDMA_BASE + 0x2E4)
/* GDMA_TX_PRI_CH3:R/W；位位置：[3:0]；默认值：4'b0；*/
/*description:Tx信道3的优先级。值越大，优先级越高。。*/
#define GDMA_TX_PRI_CH3    0x0000000F
#define GDMA_TX_PRI_CH3_M  ((GDMA_TX_PRI_CH3_V)<<(GDMA_TX_PRI_CH3_S))
#define GDMA_TX_PRI_CH3_V  0xF
#define GDMA_TX_PRI_CH3_S  0

#define GDMA_OUT_PERI_SEL_CH3_REG          (DR_REG_GDMA_BASE + 0x2E8)
/* GDMA_PERI_OUT_SEL_CH3:R/W；比特位置：[5:0]；默认值：6'h3f；*/
/*描述：此寄存器用于为Tx信道3.0:SPI2.1:SPI3.2:UHCI0.3:I2S0.4:I2S1.5:LCD_CAM选择外围设备。6： AES。7： 沙。8： ADC_DAC。9： 每立方米。；7： AES。8： 沙。9： ADC_DAC。。*/
#define GDMA_PERI_OUT_SEL_CH3    0x0000003F
#define GDMA_PERI_OUT_SEL_CH3_M  ((GDMA_PERI_OUT_SEL_CH3_V)<<(GDMA_PERI_OUT_SEL_CH3_S))
#define GDMA_PERI_OUT_SEL_CH3_V  0x3F
#define GDMA_PERI_OUT_SEL_CH3_S  0

#define GDMA_IN_CONF0_CH4_REG          (DR_REG_GDMA_BASE + 0x300)
/* GDMA_MEM_TRANS_EN_CH4:R/W；位位置：[4]；默认值：1’b0；*/
/*description:将此位设置为1，以启用通过DMA将数据从存储器自动传输到存储器。。*/
#define GDMA_MEM_TRANS_EN_CH4    (BIT(4))
#define GDMA_MEM_TRANS_EN_CH4_M  (BIT(4))
#define GDMA_MEM_TRANS_EN_CH4_V  0x1
#define GDMA_MEM_TRANS_EN_CH4_S  4
/* GDMA_IN_DATA_BURST_EN_CH4:R/W；位位置：[3]；默认值：1’b0；*/
/*description:将此位设置为1，以在访问内部SRAM时启用接收数据的Rx通道2的INCR突发传输。*/
#define GDMA_IN_DATA_BURST_EN_CH4    (BIT(3))
#define GDMA_IN_DATA_BURST_EN_CH4_M  (BIT(3))
#define GDMA_IN_DATA_BURST_EN_CH4_V  0x1
#define GDMA_IN_DATA_BURST_EN_CH4_S  3
/* GDMA_INDSCR_BURST_EN_CH4:R/W；位位置：[2]；默认值：1’b0；*/
/*description:当访问内部SRAM时，将此位设置为1以启用Rx通道2读取链路描述符的INCR突发传输。*/
#define GDMA_INDSCR_BURST_EN_CH4    (BIT(2))
#define GDMA_INDSCR_BURST_EN_CH4_M  (BIT(2))
#define GDMA_INDSCR_BURST_EN_CH4_V  0x1
#define GDMA_INDSCR_BURST_EN_CH4_S  2
/* GDMA_IN_LOOP_TEST_CH4:R/W；位位置：[1]；默认值：1’b0；*/
/*description:保留。*/
#define GDMA_IN_LOOP_TEST_CH4    (BIT(1))
#define GDMA_IN_LOOP_TEST_CH4_M  (BIT(1))
#define GDMA_IN_LOOP_TEST_CH4_V  0x1
#define GDMA_IN_LOOP_TEST_CH4_S  1
/* GDMA_IN_RST_CH4:R/W；位位置：[0]；默认值：1'0；*/
/*描述：此位用于重置DMA通道4 Rx FSM和Rx FIFO指针。。*/
#define GDMA_IN_RST_CH4    (BIT(0))
#define GDMA_IN_RST_CH4_M  (BIT(0))
#define GDMA_IN_RST_CH4_V  0x1
#define GDMA_IN_RST_CH4_S  0

#define GDMA_IN_CONF1_CH4_REG          (DR_REG_GDMA_BASE + 0x304)
/* GDMA_IN_EXT_MEM_BK_SIZE_CH4:R/W；比特位置：[14:13]；默认值：2’b0；*/
/*描述：DMA访问外部SRAM时Rx通道4的块大小。0:16字节1:32字节2/3:保留。*/
#define GDMA_IN_EXT_MEM_BK_SIZE_CH4    0x00000003
#define GDMA_IN_EXT_MEM_BK_SIZE_CH4_M  ((GDMA_IN_EXT_MEM_BK_SIZE_CH4_V)<<(GDMA_IN_EXT_MEM_BK_SIZE_CH4_S))
#define GDMA_IN_EXT_MEM_BK_SIZE_CH4_V  0x3
#define GDMA_IN_EXT_MEM_BK_SIZE_CH4_S  13
/* GDMA_IN_CHECK_OWNER_CH4:R/W；位位置：[12]；默认值：1’b0；*/
/*description:设置此位以启用检查链接描述符的所有者属性。。*/
#define GDMA_IN_CHECK_OWNER_CH4    (BIT(12))
#define GDMA_IN_CHECK_OWNER_CH4_M  (BIT(12))
#define GDMA_IN_CHECK_OWNER_CH4_V  0x1
#define GDMA_IN_CHECK_OWNER_CH4_S  12
/* GDMA_DMA_INFIFO_FULL_THRS_CH4:R/W；位位置：[11:0]；默认值：12'hc；*/
/*描述：当Rx FIFO中的Rx通道4接收字节数达到寄存器值时，此寄存器用于生成INFIFO_FULL_WM_INT中断。。*/
#define GDMA_DMA_INFIFO_FULL_THRS_CH4    0x00000FFF
#define GDMA_DMA_INFIFO_FULL_THRS_CH4_M  ((GDMA_DMA_INFIFO_FULL_THRS_CH4_V)<<(GDMA_DMA_INFIFO_FULL_THRS_CH4_S))
#define GDMA_DMA_INFIFO_FULL_THRS_CH4_V  0xFFF
#define GDMA_DMA_INFIFO_FULL_THRS_CH4_S  0

#define GDMA_IN_INT_RAW_CH4_REG          (DR_REG_GDMA_BASE + 0x308)
/* GDMA_INFIFO_UDF_13_CH4_INT_RAW:R/WTC/SS；位位置：[9]；默认值：1’b0；*/
/*描述：当Rx通道4的第3级fifo未满流时，此原始中断位变为高电平。*/
#define GDMA_INFIFO_UDF_L3_CH4_INT_RAW    (BIT(9))
#define GDMA_INFIFO_UDF_L3_CH4_INT_RAW_M  (BIT(9))
#define GDMA_INFIFO_UDF_L3_CH4_INT_RAW_V  0x1
#define GDMA_INFIFO_UDF_L3_CH4_INT_RAW_S  9
/* GDMA_INFIFO_off_L3_CH4_INT_RAW:R/WTC/SS；位位置：[8]；默认值：1’b0；*/
/*描述：当Rx通道4的3级fifo等流量时，此原始中断位变为高电平。*/
#define GDMA_INFIFO_OVF_L3_CH4_INT_RAW    (BIT(8))
#define GDMA_INFIFO_OVF_L3_CH4_INT_RAW_M  (BIT(8))
#define GDMA_INFIFO_OVF_L3_CH4_INT_RAW_V  0x1
#define GDMA_INFIFO_OVF_L3_CH4_INT_RAW_S  8
/* GDMA_INFIFO_UDF_L1_CH4_INT_RAW:R/WTC/SS；位位置：[7]；默认值：1’b0；*/
/*描述：当Rx通道4的第1级fifo未满流时，此原始中断位变为高电平。*/
#define GDMA_INFIFO_UDF_L1_CH4_INT_RAW    (BIT(7))
#define GDMA_INFIFO_UDF_L1_CH4_INT_RAW_M  (BIT(7))
#define GDMA_INFIFO_UDF_L1_CH4_INT_RAW_V  0x1
#define GDMA_INFIFO_UDF_L1_CH4_INT_RAW_S  7
/* GDMA_INFIFO_off_L1_CH4_INT_RAW:R/WTC/SS；位位置：[6]；默认值：1’b0；*/
/*描述：当Rx通道4的1级fifo等流量时，此原始中断位变为高电平。*/
#define GDMA_INFIFO_OVF_L1_CH4_INT_RAW    (BIT(6))
#define GDMA_INFIFO_OVF_L1_CH4_INT_RAW_M  (BIT(6))
#define GDMA_INFIFO_OVF_L1_CH4_INT_RAW_V  0x1
#define GDMA_INFIFO_OVF_L1_CH4_INT_RAW_S  6
/* GDMA_INFIFO_FULL_WM_CH4_INT_RAW:R/WTC/SS；位位置：[5]；默认值：1’b0；*/
/*描述：当接收的数据字节数达到信道4的Rx FIFO中REG_DMA_INFIFO_FULL_THS_CH0配置的阈值时，原始中断位变为高电平。。*/
#define GDMA_INFIFO_FULL_WM_CH4_INT_RAW    (BIT(5))
#define GDMA_INFIFO_FULL_WM_CH4_INT_RAW_M  (BIT(5))
#define GDMA_INFIFO_FULL_WM_CH4_INT_RAW_V  0x1
#define GDMA_INFIFO_FULL_WM_CH4_INT_RAW_S  5
/* GDMA_IN_DSCR_EMPTY_CH4_INT_RAW:R/WTC/SS；位位置：[4]；默认值：1’b0；*/
/*描述：当inlink指向的Rx缓冲区已满且未完成接收数据时，原始中断位变为高电平，但Rx通道4没有更多的inlink。。*/
#define GDMA_IN_DSCR_EMPTY_CH4_INT_RAW    (BIT(4))
#define GDMA_IN_DSCR_EMPTY_CH4_INT_RAW_M  (BIT(4))
#define GDMA_IN_DSCR_EMPTY_CH4_INT_RAW_V  0x1
#define GDMA_IN_DSCR_EMPTY_CH4_INT_RAW_S  4
/* GDMA_IN_DSCR_ERR_CH4_INT_RAW:R/WTC/SS；位位置：[3]；默认值：1’b0；*/
/*描述：当检测到内联描述符错误时，原始中断位变为高电平，包括所有者错误、Rx通道4的内联描述符的第二个和第三个字错误。。*/
#define GDMA_IN_DSCR_ERR_CH4_INT_RAW    (BIT(3))
#define GDMA_IN_DSCR_ERR_CH4_INT_RAW_M  (BIT(3))
#define GDMA_IN_DSCR_ERR_CH4_INT_RAW_V  0x1
#define GDMA_IN_DSCR_ERR_CH4_INT_RAW_S  3
/* GDMA_IN_ERR_EOF_CH4_INT_RAW:R/WTC/SS；位位置：[2]；默认值：1’b0；*/
/*描述：当仅在外围设备为UHCI0用于Rx信道4的情况下检测到数据错误时，原始中断位变为高电平。对于其他外围设备，保留此原始中断。。*/
#define GDMA_IN_ERR_EOF_CH4_INT_RAW    (BIT(2))
#define GDMA_IN_ERR_EOF_CH4_INT_RAW_M  (BIT(2))
#define GDMA_IN_ERR_EOF_CH4_INT_RAW_V  0x1
#define GDMA_IN_ERR_EOF_CH4_INT_RAW_S  2
/* GDMA_IN_SUC_EOF_CH4_INT_RAW:R/WTC/SS；位位置：[1]；默认值：1’b0；*/
/*描述：当接收到Rx通道4的一个内联描述符指向的最后一个数据时，原始中断位变为高电平。对于UHCI0，当接收到一个内联描述符指向的最后数据且Rx通道0未检测到数据错误时，原始断开位变为低电平。。*/
#define GDMA_IN_SUC_EOF_CH4_INT_RAW    (BIT(1))
#define GDMA_IN_SUC_EOF_CH4_INT_RAW_M  (BIT(1))
#define GDMA_IN_SUC_EOF_CH4_INT_RAW_V  0x1
#define GDMA_IN_SUC_EOF_CH4_INT_RAW_S  1
/* GDMA_IN_DONE_CH4_INT_RAW:R/WTC/SS；位位置：[0]；默认值：1’b0；*/
/*描述：当接收到Rx通道4的一个内联描述符所指向的最后一个数据时，原始中断位变为高电平。。*/
#define GDMA_IN_DONE_CH4_INT_RAW    (BIT(0))
#define GDMA_IN_DONE_CH4_INT_RAW_M  (BIT(0))
#define GDMA_IN_DONE_CH4_INT_RAW_V  0x1
#define GDMA_IN_DONE_CH4_INT_RAW_S  0

#define GDMA_IN_INT_ST_CH4_REG          (DR_REG_GDMA_BASE + 0x30C)
/* GDMA_INFIFO_UDF_13_CH4_INT_ST:RO；位位置：[9]；默认值：1’b0；*/
/*description:INFIFO_UDF_L3_CH_INT中断的原始中断状态位。。*/
#define GDMA_INFIFO_UDF_L3_CH4_INT_ST    (BIT(9))
#define GDMA_INFIFO_UDF_L3_CH4_INT_ST_M  (BIT(9))
#define GDMA_INFIFO_UDF_L3_CH4_INT_ST_V  0x1
#define GDMA_INFIFO_UDF_L3_CH4_INT_ST_S  9
/* GDMA_INFIFO_off_13_CH4_INT_ST:RO；位位置：[8]；默认值：1’b0；*/
/*description:INFIFO_OVF_L3_CH_INT中断的原始中断状态位。。*/
#define GDMA_INFIFO_OVF_L3_CH4_INT_ST    (BIT(8))
#define GDMA_INFIFO_OVF_L3_CH4_INT_ST_M  (BIT(8))
#define GDMA_INFIFO_OVF_L3_CH4_INT_ST_V  0x1
#define GDMA_INFIFO_OVF_L3_CH4_INT_ST_S  8
/* GDMA_INFIFO_UDF_L1_CH4_INT_ST:RO；位位置：[7]；默认值：1’b0；*/
/*description:INFIFO_UDF_L1_CH_INT中断的原始中断状态位。。*/
#define GDMA_INFIFO_UDF_L1_CH4_INT_ST    (BIT(7))
#define GDMA_INFIFO_UDF_L1_CH4_INT_ST_M  (BIT(7))
#define GDMA_INFIFO_UDF_L1_CH4_INT_ST_V  0x1
#define GDMA_INFIFO_UDF_L1_CH4_INT_ST_S  7
/* GDMA_INFIFO_off_L1_CH4_INT_ST:RO；位位置：[6]；默认值：1’b0；*/
/*description:INFIFO_OVF_L1_CH_INT中断的原始中断状态位。。*/
#define GDMA_INFIFO_OVF_L1_CH4_INT_ST    (BIT(6))
#define GDMA_INFIFO_OVF_L1_CH4_INT_ST_M  (BIT(6))
#define GDMA_INFIFO_OVF_L1_CH4_INT_ST_V  0x1
#define GDMA_INFIFO_OVF_L1_CH4_INT_ST_S  6
/* GDMA_INFIFO_FULL_WM_CH4_INT_ST:RO；位位置：[5]；默认值：1’b0；*/
/*description:INFIFO_FULL_WM_CH_INT中断的原始中断状态位。。*/
#define GDMA_INFIFO_FULL_WM_CH4_INT_ST    (BIT(5))
#define GDMA_INFIFO_FULL_WM_CH4_INT_ST_M  (BIT(5))
#define GDMA_INFIFO_FULL_WM_CH4_INT_ST_V  0x1
#define GDMA_INFIFO_FULL_WM_CH4_INT_ST_S  5
/* GDMA_IN_DSCR_EMPTY-CH4_INT_ST:RO；位位置：[4]；默认值：1’b0；*/
/*description:IN_DSCR_EMPTY_CH_INT中断的原始中断状态位。。*/
#define GDMA_IN_DSCR_EMPTY_CH4_INT_ST    (BIT(4))
#define GDMA_IN_DSCR_EMPTY_CH4_INT_ST_M  (BIT(4))
#define GDMA_IN_DSCR_EMPTY_CH4_INT_ST_V  0x1
#define GDMA_IN_DSCR_EMPTY_CH4_INT_ST_S  4
/* GDMA_IN_DSCR_ERR_CH4_INT_ST:RO；位位置：[3]；默认值：1’b0；*/
/*description:IN_DSCR_ERR_CH_INT中断的原始中断状态位。。*/
#define GDMA_IN_DSCR_ERR_CH4_INT_ST    (BIT(3))
#define GDMA_IN_DSCR_ERR_CH4_INT_ST_M  (BIT(3))
#define GDMA_IN_DSCR_ERR_CH4_INT_ST_V  0x1
#define GDMA_IN_DSCR_ERR_CH4_INT_ST_S  3
/* GDMA_IN_ERR_EOF_CH4_INT_ST:RO；位位置：[2]；默认值：1’b0；*/
/*description:IN_ERR_EOF_CH_INT中断的原始中断状态位。。*/
#define GDMA_IN_ERR_EOF_CH4_INT_ST    (BIT(2))
#define GDMA_IN_ERR_EOF_CH4_INT_ST_M  (BIT(2))
#define GDMA_IN_ERR_EOF_CH4_INT_ST_V  0x1
#define GDMA_IN_ERR_EOF_CH4_INT_ST_S  2
/* GDMA_IN_SUC_EOF_CH4_INT_ST:RO；位位置：[1]；默认值：1’b0；*/
/*description:IN_SUC_EOF_CH_INT中断的原始中断状态位。。*/
#define GDMA_IN_SUC_EOF_CH4_INT_ST    (BIT(1))
#define GDMA_IN_SUC_EOF_CH4_INT_ST_M  (BIT(1))
#define GDMA_IN_SUC_EOF_CH4_INT_ST_V  0x1
#define GDMA_IN_SUC_EOF_CH4_INT_ST_S  1
/* GDMA_IN_DONE_CH4_INT_ST:RO；位位置：[0]；默认值：1’b0；*/
/*description:IN_DONE_CH_INT中断的原始中断状态位。。*/
#define GDMA_IN_DONE_CH4_INT_ST    (BIT(0))
#define GDMA_IN_DONE_CH4_INT_ST_M  (BIT(0))
#define GDMA_IN_DONE_CH4_INT_ST_V  0x1
#define GDMA_IN_DONE_CH4_INT_ST_S  0

#define GDMA_IN_INT_ENA_CH4_REG          (DR_REG_GDMA_BASE + 0x310)
/* GDMA_INFIFO_UDF_13_CH4_INT_ENA:R/W；位位置：[9]；默认值：1’b0；*/
/*description:INFIFO_UDF_L3_CH_INT中断的中断启用位。。*/
#define GDMA_INFIFO_UDF_L3_CH4_INT_ENA    (BIT(9))
#define GDMA_INFIFO_UDF_L3_CH4_INT_ENA_M  (BIT(9))
#define GDMA_INFIFO_UDF_L3_CH4_INT_ENA_V  0x1
#define GDMA_INFIFO_UDF_L3_CH4_INT_ENA_S  9
/* GDMA_INFIFO_off_13_CH4_INT_ENA:R/W；位位置：[8]；默认值：1’b0；*/
/*description:INFIFO_OVF_L3_CH_INT中断的中断启用位。。*/
#define GDMA_INFIFO_OVF_L3_CH4_INT_ENA    (BIT(8))
#define GDMA_INFIFO_OVF_L3_CH4_INT_ENA_M  (BIT(8))
#define GDMA_INFIFO_OVF_L3_CH4_INT_ENA_V  0x1
#define GDMA_INFIFO_OVF_L3_CH4_INT_ENA_S  8
/* GDMA_INFIFO_UDF_L1_CH4_INT_ENA:R/W；位位置：[7]；默认值：1’b0；*/
/*description:INFIFO_UDF_L1_CH_INT中断的中断启用位。。*/
#define GDMA_INFIFO_UDF_L1_CH4_INT_ENA    (BIT(7))
#define GDMA_INFIFO_UDF_L1_CH4_INT_ENA_M  (BIT(7))
#define GDMA_INFIFO_UDF_L1_CH4_INT_ENA_V  0x1
#define GDMA_INFIFO_UDF_L1_CH4_INT_ENA_S  7
/* GDMA_INFIFO_off_L1_CH4_INT_ENA:R/W；位位置：[6]；默认值：1’b0；*/
/*description:INFIFO_OVF_L1_CH_INT中断的中断启用位。。*/
#define GDMA_INFIFO_OVF_L1_CH4_INT_ENA    (BIT(6))
#define GDMA_INFIFO_OVF_L1_CH4_INT_ENA_M  (BIT(6))
#define GDMA_INFIFO_OVF_L1_CH4_INT_ENA_V  0x1
#define GDMA_INFIFO_OVF_L1_CH4_INT_ENA_S  6
/* GDMA_INFIFO_FULL_WM_CH4_INT_ENA:R/W；位位置：[5]；默认值：1’b0；*/
/*description:INFIFO_FULL_WM_CH_INT中断的中断启用位。。*/
#define GDMA_INFIFO_FULL_WM_CH4_INT_ENA    (BIT(5))
#define GDMA_INFIFO_FULL_WM_CH4_INT_ENA_M  (BIT(5))
#define GDMA_INFIFO_FULL_WM_CH4_INT_ENA_V  0x1
#define GDMA_INFIFO_FULL_WM_CH4_INT_ENA_S  5
/* GDMA_IN_DSCR_EMPTY_CH4_INT_ENA:R/W；位位置：[4]；默认值：1’b0；*/
/*description:IN_DSCR_EMPTY_CH_INT中断的中断启用位。。*/
#define GDMA_IN_DSCR_EMPTY_CH4_INT_ENA    (BIT(4))
#define GDMA_IN_DSCR_EMPTY_CH4_INT_ENA_M  (BIT(4))
#define GDMA_IN_DSCR_EMPTY_CH4_INT_ENA_V  0x1
#define GDMA_IN_DSCR_EMPTY_CH4_INT_ENA_S  4
/* GDMA_IN_DSCR_ERR_CH4_INT_ENA:R/W；位位置：[3]；默认值：1’b0；*/
/*description:IN_DSCR_ERR_CH_INT中断的中断启用位。。*/
#define GDMA_IN_DSCR_ERR_CH4_INT_ENA    (BIT(3))
#define GDMA_IN_DSCR_ERR_CH4_INT_ENA_M  (BIT(3))
#define GDMA_IN_DSCR_ERR_CH4_INT_ENA_V  0x1
#define GDMA_IN_DSCR_ERR_CH4_INT_ENA_S  3
/* GDMA_IN_ERR_EOF_CH4_INT_ENA:R/W；位位置：[2]；默认值：1’b0；*/
/*description:IN_ERR_EOF_CH_INT中断的中断启用位。。*/
#define GDMA_IN_ERR_EOF_CH4_INT_ENA    (BIT(2))
#define GDMA_IN_ERR_EOF_CH4_INT_ENA_M  (BIT(2))
#define GDMA_IN_ERR_EOF_CH4_INT_ENA_V  0x1
#define GDMA_IN_ERR_EOF_CH4_INT_ENA_S  2
/* GDMA_IN_SUC_EOF_CH4_INT_ENA:R/W；位位置：[1]；默认值：1’b0；*/
/*description:IN_SUC_EOF_CH_INT中断的中断启用位。。*/
#define GDMA_IN_SUC_EOF_CH4_INT_ENA    (BIT(1))
#define GDMA_IN_SUC_EOF_CH4_INT_ENA_M  (BIT(1))
#define GDMA_IN_SUC_EOF_CH4_INT_ENA_V  0x1
#define GDMA_IN_SUC_EOF_CH4_INT_ENA_S  1
/* GDMA_IN_DONE_CH4_INT_ENA:R/W；位位置：[0]；默认值：1’b0；*/
/*description:IN_DONE_CH_INT中断的中断启用位。。*/
#define GDMA_IN_DONE_CH4_INT_ENA    (BIT(0))
#define GDMA_IN_DONE_CH4_INT_ENA_M  (BIT(0))
#define GDMA_IN_DONE_CH4_INT_ENA_V  0x1
#define GDMA_IN_DONE_CH4_INT_ENA_S  0

#define GDMA_IN_INT_CLR_CH4_REG          (DR_REG_GDMA_BASE + 0x314)
/* GDMA_INFIFO_UDF_13_CH4_INT_CLR:WT；位位置：[9]；默认值：1’b0；*/
/*description:设置此位以清除INFIFO_UDF_L3_CH_INT中断。。*/
#define GDMA_INFIFO_UDF_L3_CH4_INT_CLR    (BIT(9))
#define GDMA_INFIFO_UDF_L3_CH4_INT_CLR_M  (BIT(9))
#define GDMA_INFIFO_UDF_L3_CH4_INT_CLR_V  0x1
#define GDMA_INFIFO_UDF_L3_CH4_INT_CLR_S  9
/* GDMA_INFIFO_off_13_CH4_INT_CLR:WT；位位置：[8]；默认值：1’b0；*/
/*description:设置此位以清除INFIFO_OVF_L3_CH_INT中断。。*/
#define GDMA_INFIFO_OVF_L3_CH4_INT_CLR    (BIT(8))
#define GDMA_INFIFO_OVF_L3_CH4_INT_CLR_M  (BIT(8))
#define GDMA_INFIFO_OVF_L3_CH4_INT_CLR_V  0x1
#define GDMA_INFIFO_OVF_L3_CH4_INT_CLR_S  8
/* GDMA_INFIFO_UDF_L1_CH4_INT_CLR:WT；位位置：[7]；默认值：1’b0；*/
/*description:设置此位以清除INFIFO_UDF_L1_CH_INT中断。。*/
#define GDMA_INFIFO_UDF_L1_CH4_INT_CLR    (BIT(7))
#define GDMA_INFIFO_UDF_L1_CH4_INT_CLR_M  (BIT(7))
#define GDMA_INFIFO_UDF_L1_CH4_INT_CLR_V  0x1
#define GDMA_INFIFO_UDF_L1_CH4_INT_CLR_S  7
/* GDMA_INFIFO_off_L1_CH4_INT_CLR:WT；位位置：[6]；默认值：1’b0；*/
/*description:设置此位以清除INFIFO_OVF_L1_CH_INT中断。。*/
#define GDMA_INFIFO_OVF_L1_CH4_INT_CLR    (BIT(6))
#define GDMA_INFIFO_OVF_L1_CH4_INT_CLR_M  (BIT(6))
#define GDMA_INFIFO_OVF_L1_CH4_INT_CLR_V  0x1
#define GDMA_INFIFO_OVF_L1_CH4_INT_CLR_S  6
/* GDMA_DMA_INFIFO_FULL_WM_CH4_INT_CLR:WT；位位置：[5]；默认值：1’b0；*/
/*description:设置此位以清除INFIFO_FULL_WM_CH_INT中断。。*/
#define GDMA_DMA_INFIFO_FULL_WM_CH4_INT_CLR    (BIT(5))
#define GDMA_DMA_INFIFO_FULL_WM_CH4_INT_CLR_M  (BIT(5))
#define GDMA_DMA_INFIFO_FULL_WM_CH4_INT_CLR_V  0x1
#define GDMA_DMA_INFIFO_FULL_WM_CH4_INT_CLR_S  5
/* GDMA_IN_DSCR_EMPTY-CH4_INT_CLR:WT；位位置：[4]；默认值：1’b0；*/
/*description:设置此位以清除IN_DSCR_EMPTY_CH_INT中断。。*/
#define GDMA_IN_DSCR_EMPTY_CH4_INT_CLR    (BIT(4))
#define GDMA_IN_DSCR_EMPTY_CH4_INT_CLR_M  (BIT(4))
#define GDMA_IN_DSCR_EMPTY_CH4_INT_CLR_V  0x1
#define GDMA_IN_DSCR_EMPTY_CH4_INT_CLR_S  4
/* GDMA_IN_DSCR_ERR_CH4_INT_CLR:WT；位位置：[3]；默认值：1’b0；*/
/*description:设置此位以清除IN_DSCR_ERR_CH_INT中断。。*/
#define GDMA_IN_DSCR_ERR_CH4_INT_CLR    (BIT(3))
#define GDMA_IN_DSCR_ERR_CH4_INT_CLR_M  (BIT(3))
#define GDMA_IN_DSCR_ERR_CH4_INT_CLR_V  0x1
#define GDMA_IN_DSCR_ERR_CH4_INT_CLR_S  3
/* GDMA_IN_ERR_EOF_CH4_INT_CLR:WT；位位置：[2]；默认值：1’b0；*/
/*description:设置此位以清除IN_ERR_EOF_CH_INT中断。。*/
#define GDMA_IN_ERR_EOF_CH4_INT_CLR    (BIT(2))
#define GDMA_IN_ERR_EOF_CH4_INT_CLR_M  (BIT(2))
#define GDMA_IN_ERR_EOF_CH4_INT_CLR_V  0x1
#define GDMA_IN_ERR_EOF_CH4_INT_CLR_S  2
/* GDMA_IN_SUC_EOF_CH4_INT_CLR:WT；位位置：[1]；默认值：1’b0；*/
/*description:设置此位以清除IN_SUC_EOF_CH_INT中断。。*/
#define GDMA_IN_SUC_EOF_CH4_INT_CLR    (BIT(1))
#define GDMA_IN_SUC_EOF_CH4_INT_CLR_M  (BIT(1))
#define GDMA_IN_SUC_EOF_CH4_INT_CLR_V  0x1
#define GDMA_IN_SUC_EOF_CH4_INT_CLR_S  1
/* GDMA_IN_DONE_CH4_INT_CLR:WT；位位置：[0]；默认值：1’b0；*/
/*description:设置此位以清除IN_DONE_CH_INT中断。。*/
#define GDMA_IN_DONE_CH4_INT_CLR    (BIT(0))
#define GDMA_IN_DONE_CH4_INT_CLR_M  (BIT(0))
#define GDMA_IN_DONE_CH4_INT_CLR_V  0x1
#define GDMA_IN_DONE_CH4_INT_CLR_S  0

#define GDMA_INFIFO_STATUS_CH4_REG          (DR_REG_GDMA_BASE + 0x318)
/* GDMA_IN_BUF_HUNGRY_CH4:RO；位位置：[28]；默认值：1’b0；*/
/*description:保留。*/
#define GDMA_IN_BUF_HUNGRY_CH4    (BIT(28))
#define GDMA_IN_BUF_HUNGRY_CH4_M  (BIT(28))
#define GDMA_IN_BUF_HUNGRY_CH4_V  0x1
#define GDMA_IN_BUF_HUNGRY_CH4_S  28
/* GDMA_IN_REMAIN_UNDER_4B_L3_CH4:RO；位位置：[27]；默认值：1’b1；*/
/*description:保留。*/
#define GDMA_IN_REMAIN_UNDER_4B_L3_CH4    (BIT(27))
#define GDMA_IN_REMAIN_UNDER_4B_L3_CH4_M  (BIT(27))
#define GDMA_IN_REMAIN_UNDER_4B_L3_CH4_V  0x1
#define GDMA_IN_REMAIN_UNDER_4B_L3_CH4_S  27
/* GDMA_IN_REMAIN_UNDER_3B_L3_CH4:RO；位位置：[26]；默认值：1’b1；*/
/*description:保留。*/
#define GDMA_IN_REMAIN_UNDER_3B_L3_CH4    (BIT(26))
#define GDMA_IN_REMAIN_UNDER_3B_L3_CH4_M  (BIT(26))
#define GDMA_IN_REMAIN_UNDER_3B_L3_CH4_V  0x1
#define GDMA_IN_REMAIN_UNDER_3B_L3_CH4_S  26
/* GDMA_IN_REMAIN_UNDER_2B_L3_CH4:RO；位位置：[25]；默认值：1’b1；*/
/*description:保留。*/
#define GDMA_IN_REMAIN_UNDER_2B_L3_CH4    (BIT(25))
#define GDMA_IN_REMAIN_UNDER_2B_L3_CH4_M  (BIT(25))
#define GDMA_IN_REMAIN_UNDER_2B_L3_CH4_V  0x1
#define GDMA_IN_REMAIN_UNDER_2B_L3_CH4_S  25
/* GDMA_IN_REMAIN_UNDER_1B_L3_CH4:RO；位位置：[24]；默认值：1’b1；*/
/*description:保留。*/
#define GDMA_IN_REMAIN_UNDER_1B_L3_CH4    (BIT(24))
#define GDMA_IN_REMAIN_UNDER_1B_L3_CH4_M  (BIT(24))
#define GDMA_IN_REMAIN_UNDER_1B_L3_CH4_V  0x1
#define GDMA_IN_REMAIN_UNDER_1B_L3_CH4_S  24
/* GDMA_INFIFO_CNT_L3_CH4:RO；比特位置：[23:19]；默认值：5’b0；*/
/*描述：寄存器将数据的字节数存储在Rx通道4的L3 Rx FIFO中。。*/
#define GDMA_INFIFO_CNT_L3_CH4    0x0000001F
#define GDMA_INFIFO_CNT_L3_CH4_M  ((GDMA_INFIFO_CNT_L3_CH4_V)<<(GDMA_INFIFO_CNT_L3_CH4_S))
#define GDMA_INFIFO_CNT_L3_CH4_V  0x1F
#define GDMA_INFIFO_CNT_L3_CH4_S  19
/* GDMA_INFIFO_CNT_L2_CH4:RO；比特位置：[18:12]；默认值：7'b0；*/
/*描述：寄存器将数据的字节数存储在Rx信道4的L2 Rx FIFO中。。*/
#define GDMA_INFIFO_CNT_L2_CH4    0x0000007F
#define GDMA_INFIFO_CNT_L2_CH4_M  ((GDMA_INFIFO_CNT_L2_CH4_V)<<(GDMA_INFIFO_CNT_L2_CH4_S))
#define GDMA_INFIFO_CNT_L2_CH4_V  0x7F
#define GDMA_INFIFO_CNT_L2_CH4_S  12
/* GDMA_INFIFO_CNT_L1_CH4:RO；位位置：[11:6]；默认值：6'b0；*/
/*描述：寄存器将数据的字节数存储在Rx信道4的L1 Rx FIFO中。。*/
#define GDMA_INFIFO_CNT_L1_CH4    0x0000003F
#define GDMA_INFIFO_CNT_L1_CH4_M  ((GDMA_INFIFO_CNT_L1_CH4_V)<<(GDMA_INFIFO_CNT_L1_CH4_S))
#define GDMA_INFIFO_CNT_L1_CH4_V  0x3F
#define GDMA_INFIFO_CNT_L1_CH4_S  6
/* GDMA_INFIFO_EMPTY_L3_CH4:RO；位位置：[5]；默认值：1’b1；*/
/*描述：Rx信道4的L3 Rx FIFO空信号。。*/
#define GDMA_INFIFO_EMPTY_L3_CH4    (BIT(5))
#define GDMA_INFIFO_EMPTY_L3_CH4_M  (BIT(5))
#define GDMA_INFIFO_EMPTY_L3_CH4_V  0x1
#define GDMA_INFIFO_EMPTY_L3_CH4_S  5
/* GDMA_INFIFO_FULL_L3_CH4:RO；位位置：[4]；默认值：1’b1；*/
/*描述：Rx信道4的L3 Rx FIFO完整信号。。*/
#define GDMA_INFIFO_FULL_L3_CH4    (BIT(4))
#define GDMA_INFIFO_FULL_L3_CH4_M  (BIT(4))
#define GDMA_INFIFO_FULL_L3_CH4_V  0x1
#define GDMA_INFIFO_FULL_L3_CH4_S  4
/* GDMA_INFIFO_EMPTY_L2_CH4:RO；位位置：[3]；默认值：1’b1；*/
/*描述：Rx信道4的L2 Rx FIFO空信号。。*/
#define GDMA_INFIFO_EMPTY_L2_CH4    (BIT(3))
#define GDMA_INFIFO_EMPTY_L2_CH4_M  (BIT(3))
#define GDMA_INFIFO_EMPTY_L2_CH4_V  0x1
#define GDMA_INFIFO_EMPTY_L2_CH4_S  3
/* GDMA_INFIFO_FULL_L2_CH4:RO；位位置：[2]；默认值：1’b0；*/
/*描述：Rx信道4的L2 Rx FIFO满信号。。*/
#define GDMA_INFIFO_FULL_L2_CH4    (BIT(2))
#define GDMA_INFIFO_FULL_L2_CH4_M  (BIT(2))
#define GDMA_INFIFO_FULL_L2_CH4_V  0x1
#define GDMA_INFIFO_FULL_L2_CH4_S  2
/* GDMA_INFIFO_EMPTY_L1_CH4:RO；位位置：[1]；默认值：1’b1；*/
/*描述：Rx信道4的L1 Rx FIFO空信号。。*/
#define GDMA_INFIFO_EMPTY_L1_CH4    (BIT(1))
#define GDMA_INFIFO_EMPTY_L1_CH4_M  (BIT(1))
#define GDMA_INFIFO_EMPTY_L1_CH4_V  0x1
#define GDMA_INFIFO_EMPTY_L1_CH4_S  1
/* GDMA_INFIFO_FULL_L1_CH4:RO；位位置：[0]；默认值：1’b0；*/
/*描述：Rx信道4的L1 Rx FIFO完整信号。。*/
#define GDMA_INFIFO_FULL_L1_CH4    (BIT(0))
#define GDMA_INFIFO_FULL_L1_CH4_M  (BIT(0))
#define GDMA_INFIFO_FULL_L1_CH4_V  0x1
#define GDMA_INFIFO_FULL_L1_CH4_S  0

#define GDMA_IN_POP_CH4_REG          (DR_REG_GDMA_BASE + 0x31C)
/* GDMA_INFIFO_POP_CH4:R/W/SC；位位置：[12]；默认值：1'0；*/
/*description:将此位设置为从DMA FIFO弹出数据。。*/
#define GDMA_INFIFO_POP_CH4    (BIT(12))
#define GDMA_INFIFO_POP_CH4_M  (BIT(12))
#define GDMA_INFIFO_POP_CH4_V  0x1
#define GDMA_INFIFO_POP_CH4_S  12
/* GDMA_INFIFO_data_CH4:RO；位位置：[11:0]；默认值：12'h800；*/
/*description:此寄存器存储从DMA FIFO弹出的数据。。*/
#define GDMA_INFIFO_RDATA_CH4    0x00000FFF
#define GDMA_INFIFO_RDATA_CH4_M  ((GDMA_INFIFO_RDATA_CH4_V)<<(GDMA_INFIFO_RDATA_CH4_S))
#define GDMA_INFIFO_RDATA_CH4_V  0xFFF
#define GDMA_INFIFO_RDATA_CH4_S  0

#define GDMA_IN_LINK_CH4_REG          (DR_REG_GDMA_BASE + 0x320)
/* GDMA_INLINK_PARK_CH4:RO；位位置：[24]；默认值：1'h1；*/
/*description:1：内联描述符的FSM处于空闲状态。0:内联描述符的FSM正在工作。。*/
#define GDMA_INLINK_PARK_CH4    (BIT(24))
#define GDMA_INLINK_PARK_CH4_M  (BIT(24))
#define GDMA_INLINK_PARK_CH4_V  0x1
#define GDMA_INLINK_PARK_CH4_S  24
/* GDMA_INLINK_RESTART_CH4：R/W/SC；位位置：[23]；默认值：1’b0；*/
/*description:设置此位以装入新的内联描述符。。*/
#define GDMA_INLINK_RESTART_CH4    (BIT(23))
#define GDMA_INLINK_RESTART_CH4_M  (BIT(23))
#define GDMA_INLINK_RESTART_CH4_V  0x1
#define GDMA_INLINK_RESTART_CH4_S  23
/* GDMA_INLINK_START_CH4：R/W/SC；位位置：[22]；默认值：1’b0；*/
/*description:设置此位以开始处理内联描述符。。*/
#define GDMA_INLINK_START_CH4    (BIT(22))
#define GDMA_INLINK_START_CH4_M  (BIT(22))
#define GDMA_INLINK_START_CH4_V  0x1
#define GDMA_INLINK_START_CH4_S  22
/* GDMA_INLINK_STOP_CH4：R/W/SC；位位置：[21]；默认值：1’b0；*/
/*description:设置此位以停止处理内联描述符。。*/
#define GDMA_INLINK_STOP_CH4    (BIT(21))
#define GDMA_INLINK_STOP_CH4_M  (BIT(21))
#define GDMA_INLINK_STOP_CH4_V  0x1
#define GDMA_INLINK_STOP_CH4_S  21
/* GDMA_INLINK_AUTO_RET_CH4:R/W；位位置：[20]；默认值：1’b1；*/
/*description:当当前接收数据中存在一些错误时，将此位设置为返回当前内联描述符的地址。。*/
#define GDMA_INLINK_AUTO_RET_CH4    (BIT(20))
#define GDMA_INLINK_AUTO_RET_CH4_M  (BIT(20))
#define GDMA_INLINK_AUTO_RET_CH4_V  0x1
#define GDMA_INLINK_AUTO_RET_CH4_S  20
/* GDMA_INLINK_ADDR_CH4:R/W；比特位置：[19:0]；默认值：20'00；*/
/*description:此寄存器存储第一个内联描述符地址的20个最低有效位。。*/
#define GDMA_INLINK_ADDR_CH4    0x000FFFFF
#define GDMA_INLINK_ADDR_CH4_M  ((GDMA_INLINK_ADDR_CH4_V)<<(GDMA_INLINK_ADDR_CH4_S))
#define GDMA_INLINK_ADDR_CH4_V  0xFFFFF
#define GDMA_INLINK_ADDR_CH4_S  0

#define GDMA_IN_STATE_CH4_REG          (DR_REG_GDMA_BASE + 0x324)
/* GDMA_IN_STATE_CH4:RO；比特位置：[22:20]；默认值：3'b0；*/
/*description:保留。*/
#define GDMA_IN_STATE_CH4    0x00000007
#define GDMA_IN_STATE_CH4_M  ((GDMA_IN_STATE_CH4_V)<<(GDMA_IN_STATE_CH4_S))
#define GDMA_IN_STATE_CH4_V  0x7
#define GDMA_IN_STATE_CH4_S  20
/* GDMA_IN_DSCR_STATE_CH4:RO；比特位置：[19:18]；默认值：2’b0；*/
/*description:保留。*/
#define GDMA_IN_DSCR_STATE_CH4    0x00000003
#define GDMA_IN_DSCR_STATE_CH4_M  ((GDMA_IN_DSCR_STATE_CH4_V)<<(GDMA_IN_DSCR_STATE_CH4_S))
#define GDMA_IN_DSCR_STATE_CH4_V  0x3
#define GDMA_IN_DSCR_STATE_CH4_S  18
/* GDMA_INLINK_DSCR_ADDR_CH4:RO；比特位置：[17:00]；默认值：18'b0；*/
/*description:此寄存器存储当前内联描述符的地址。。*/
#define GDMA_INLINK_DSCR_ADDR_CH4    0x0003FFFF
#define GDMA_INLINK_DSCR_ADDR_CH4_M  ((GDMA_INLINK_DSCR_ADDR_CH4_V)<<(GDMA_INLINK_DSCR_ADDR_CH4_S))
#define GDMA_INLINK_DSCR_ADDR_CH4_V  0x3FFFF
#define GDMA_INLINK_DSCR_ADDR_CH4_S  0

#define GDMA_IN_SUC_EOF_DES_ADDR_CH4_REG          (DR_REG_GDMA_BASE + 0x328)
/* GDMA_IN_SUC_EOF_DES_ADDR_CH4:RO；位位置：[31:0]；默认值：32'h0；*/
/*description:当此描述符中的EOF位为1时，此寄存器存储内联描述符的地址。。*/
#define GDMA_IN_SUC_EOF_DES_ADDR_CH4    0xFFFFFFFF
#define GDMA_IN_SUC_EOF_DES_ADDR_CH4_M  ((GDMA_IN_SUC_EOF_DES_ADDR_CH4_V)<<(GDMA_IN_SUC_EOF_DES_ADDR_CH4_S))
#define GDMA_IN_SUC_EOF_DES_ADDR_CH4_V  0xFFFFFFFF
#define GDMA_IN_SUC_EOF_DES_ADDR_CH4_S  0

#define GDMA_IN_ERR_EOF_DES_ADDR_CH4_REG          (DR_REG_GDMA_BASE + 0x32C)
/* GDMA_IN_ERR_EOF_DES_ADDR_CH4:RO；位位置：[31:0]；默认值：32'h0；*/
/*description:当当前接收数据中存在一些错误时，此寄存器存储内联描述符的地址。仅当外围设备为UHCI0时使用。。*/
#define GDMA_IN_ERR_EOF_DES_ADDR_CH4    0xFFFFFFFF
#define GDMA_IN_ERR_EOF_DES_ADDR_CH4_M  ((GDMA_IN_ERR_EOF_DES_ADDR_CH4_V)<<(GDMA_IN_ERR_EOF_DES_ADDR_CH4_S))
#define GDMA_IN_ERR_EOF_DES_ADDR_CH4_V  0xFFFFFFFF
#define GDMA_IN_ERR_EOF_DES_ADDR_CH4_S  0

#define GDMA_IN_DSCR_CH4_REG          (DR_REG_GDMA_BASE + 0x330)
/* GDMA_INLINK_DSCR_CH4:RO；位位置：[31:0]；默认值：32'b0；*/
/*description:当前内联描述符x的地址。。*/
#define GDMA_INLINK_DSCR_CH4    0xFFFFFFFF
#define GDMA_INLINK_DSCR_CH4_M  ((GDMA_INLINK_DSCR_CH4_V)<<(GDMA_INLINK_DSCR_CH4_S))
#define GDMA_INLINK_DSCR_CH4_V  0xFFFFFFFF
#define GDMA_INLINK_DSCR_CH4_S  0

#define GDMA_IN_DSCR_BF0_CH4_REG          (DR_REG_GDMA_BASE + 0x334)
/* GDMA_INLINK_DSCR_BF0_CH4:RO；位位置：[31:0]；默认值：32'b0；*/
/*description:最后一个内联描述符x-1的地址。。*/
#define GDMA_INLINK_DSCR_BF0_CH4    0xFFFFFFFF
#define GDMA_INLINK_DSCR_BF0_CH4_M  ((GDMA_INLINK_DSCR_BF0_CH4_V)<<(GDMA_INLINK_DSCR_BF0_CH4_S))
#define GDMA_INLINK_DSCR_BF0_CH4_V  0xFFFFFFFF
#define GDMA_INLINK_DSCR_BF0_CH4_S  0

#define GDMA_IN_DSCR_BF1_CH4_REG          (DR_REG_GDMA_BASE + 0x338)
/* GDMA_INLINK_DSCR_BF1_CH4:RO；位位置：[31:0]；默认值：32'b0；*/
/*description:倒数第二个内联描述符x-2的地址。。*/
#define GDMA_INLINK_DSCR_BF1_CH4    0xFFFFFFFF
#define GDMA_INLINK_DSCR_BF1_CH4_M  ((GDMA_INLINK_DSCR_BF1_CH4_V)<<(GDMA_INLINK_DSCR_BF1_CH4_S))
#define GDMA_INLINK_DSCR_BF1_CH4_V  0xFFFFFFFF
#define GDMA_INLINK_DSCR_BF1_CH4_S  0

#define GDMA_IN_WIGHT_CH4_REG          (DR_REG_GDMA_BASE + 0x33C)
/* GDMA_RX_WEIGHT_CH4:R/W；位位置：[11:8]；默认值：4'hf；*/
/*description:Rx通道4的权重。*/
#define GDMA_RX_WEIGHT_CH4    0x0000000F
#define GDMA_RX_WEIGHT_CH4_M  ((GDMA_RX_WEIGHT_CH4_V)<<(GDMA_RX_WEIGHT_CH4_S))
#define GDMA_RX_WEIGHT_CH4_V  0xF
#define GDMA_RX_WEIGHT_CH4_S  8

#define GDMA_IN_PRI_CH4_REG          (DR_REG_GDMA_BASE + 0x344)
/* GDMA_RX_PRI_CH4:R/W；位位置：[3:0]；默认值：4'b0；*/
/*description:Rx通道4的优先级。值越大，优先级越高。。*/
#define GDMA_RX_PRI_CH4    0x0000000F
#define GDMA_RX_PRI_CH4_M  ((GDMA_RX_PRI_CH4_V)<<(GDMA_RX_PRI_CH4_S))
#define GDMA_RX_PRI_CH4_V  0xF
#define GDMA_RX_PRI_CH4_S  0

#define GDMA_IN_PERI_SEL_CH4_REG          (DR_REG_GDMA_BASE + 0x348)
/* GDMA_PERI_IN_SEL_CH4:R/W；比特位置：[5:0]；默认值：6'h3f；*/
/*描述：此寄存器用于为Rx通道5.0:SPI2.1:SPI3.2:UHCI0.3:I2S0.4:I2S1.5:LCD_CAM选择外围设备。6： AES。7： 沙。8： ADC_DAC。9： RMT。。*/
#define GDMA_PERI_IN_SEL_CH4    0x0000003F
#define GDMA_PERI_IN_SEL_CH4_M  ((GDMA_PERI_IN_SEL_CH4_V)<<(GDMA_PERI_IN_SEL_CH4_S))
#define GDMA_PERI_IN_SEL_CH4_V  0x3F
#define GDMA_PERI_IN_SEL_CH4_S  0

#define GDMA_OUT_CONF0_CH4_REG          (DR_REG_GDMA_BASE + 0x360)
/* GDMA_OUT_DATA_BURST_EN_CH4:R/W；位位置：[5]；默认值：1’b0；*/
/*描述：当访问内部SRAM时，将此位设置为1以启用传输数据的Tx信道4的INCR突发传输。*/
#define GDMA_OUT_DATA_BURST_EN_CH4    (BIT(5))
#define GDMA_OUT_DATA_BURST_EN_CH4_M  (BIT(5))
#define GDMA_OUT_DATA_BURST_EN_CH4_V  0x1
#define GDMA_OUT_DATA_BURST_EN_CH4_S  5
/* GDMA_OUTDSCR_BURST_EN_CH4:R/W；位位置：[4]；默认值：1’b0；*/
/*description:当访问内部SRAM时，将此位设置为1以启用Tx信道4读取链路描述符的INCR突发传输。*/
#define GDMA_OUTDSCR_BURST_EN_CH4    (BIT(4))
#define GDMA_OUTDSCR_BURST_EN_CH4_M  (BIT(4))
#define GDMA_OUTDSCR_BURST_EN_CH4_V  0x1
#define GDMA_OUTDSCR_BURST_EN_CH4_S  4
/* GDMA_OUT_EOF_MODE_CH4:R/W；位位置：[3]；默认值：1’b1；*/
/*描述：传输数据时EOF标志生成模式。1： 当需要传输的数据已从DMA中的FIFO弹出时，生成Tx信道4的EOF标志。*/
#define GDMA_OUT_EOF_MODE_CH4    (BIT(3))
#define GDMA_OUT_EOF_MODE_CH4_M  (BIT(3))
#define GDMA_OUT_EOF_MODE_CH4_V  0x1
#define GDMA_OUT_EOF_MODE_CH4_S  3
/* GDMA_OUT_AUTO_WRBACK_CH4:R/W；位位置：[2]；默认值：1’b0；*/
/*description:设置此位以在传输tx缓冲区中的所有数据时启用自动outlink写回。。*/
#define GDMA_OUT_AUTO_WRBACK_CH4    (BIT(2))
#define GDMA_OUT_AUTO_WRBACK_CH4_M  (BIT(2))
#define GDMA_OUT_AUTO_WRBACK_CH4_V  0x1
#define GDMA_OUT_AUTO_WRBACK_CH4_S  2
/* GDMA_OUT_LOOP_TEST_CH4:R/W；位位置：[1]；默认值：1’b0；*/
/*description:保留。*/
#define GDMA_OUT_LOOP_TEST_CH4    (BIT(1))
#define GDMA_OUT_LOOP_TEST_CH4_M  (BIT(1))
#define GDMA_OUT_LOOP_TEST_CH4_V  0x1
#define GDMA_OUT_LOOP_TEST_CH4_S  1
/* GDMA_OUT_RST_CH4:R/W；位位置：[0]；默认值：1’b0；*/
/*描述：此位用于重置DMA通道4 Tx FSM和Tx FIFO指针。。*/
#define GDMA_OUT_RST_CH4    (BIT(0))
#define GDMA_OUT_RST_CH4_M  (BIT(0))
#define GDMA_OUT_RST_CH4_V  0x1
#define GDMA_OUT_RST_CH4_S  0

#define GDMA_OUT_CONF1_CH4_REG          (DR_REG_GDMA_BASE + 0x364)
/* GDMA_OUT_EXT_MEM_BK_SIZE_CH4:R/W；比特位置：[14:13]；默认值：2’b0；*/
/*描述：DMA访问外部SRAM时Tx通道4的块大小。0:16字节1:32字节2/3:保留。*/
#define GDMA_OUT_EXT_MEM_BK_SIZE_CH4    0x00000003
#define GDMA_OUT_EXT_MEM_BK_SIZE_CH4_M  ((GDMA_OUT_EXT_MEM_BK_SIZE_CH4_V)<<(GDMA_OUT_EXT_MEM_BK_SIZE_CH4_S))
#define GDMA_OUT_EXT_MEM_BK_SIZE_CH4_V  0x3
#define GDMA_OUT_EXT_MEM_BK_SIZE_CH4_S  13
/* GDMA_OUT_CHECK_OWNER_CH4:R/W；位位置：[12]；默认值：1’b0；*/
/*description:设置此位以启用检查链接描述符的所有者属性。。*/
#define GDMA_OUT_CHECK_OWNER_CH4    (BIT(12))
#define GDMA_OUT_CHECK_OWNER_CH4_M  (BIT(12))
#define GDMA_OUT_CHECK_OWNER_CH4_V  0x1
#define GDMA_OUT_CHECK_OWNER_CH4_S  12

#define GDMA_OUT_INT_RAW_CH4_REG          (DR_REG_GDMA_BASE + 0x368)
/* GDMA_OUTFIFO_UDF_L3_CH4_INT_RAW:R/WTC/SS；位位置：[7]；默认值：1’b0；*/
/*描述：当Tx信道4的第3级fifo未满流时，此原始中断位变为高电平。*/
#define GDMA_OUTFIFO_UDF_L3_CH4_INT_RAW    (BIT(7))
#define GDMA_OUTFIFO_UDF_L3_CH4_INT_RAW_M  (BIT(7))
#define GDMA_OUTFIFO_UDF_L3_CH4_INT_RAW_V  0x1
#define GDMA_OUTFIFO_UDF_L3_CH4_INT_RAW_S  7
/* GDMA_OUTFIFO_off_L3_CH4_INT_RAW:R/WTC/SS；位位置：[6]；默认值：1’b0；*/
/*描述：当Tx信道4的3级fifo等流量时，此原始中断位变为高电平。*/
#define GDMA_OUTFIFO_OVF_L3_CH4_INT_RAW    (BIT(6))
#define GDMA_OUTFIFO_OVF_L3_CH4_INT_RAW_M  (BIT(6))
#define GDMA_OUTFIFO_OVF_L3_CH4_INT_RAW_V  0x1
#define GDMA_OUTFIFO_OVF_L3_CH4_INT_RAW_S  6
/* GDMA_OUTFIFO_UDF_L1_CH4_INT_RAW:R/WTC/SS；位位置：[5]；默认值：1’b0；*/
/*描述：当Tx信道4的第1级fifo未满流时，此原始中断位变为高电平。*/
#define GDMA_OUTFIFO_UDF_L1_CH4_INT_RAW    (BIT(5))
#define GDMA_OUTFIFO_UDF_L1_CH4_INT_RAW_M  (BIT(5))
#define GDMA_OUTFIFO_UDF_L1_CH4_INT_RAW_V  0x1
#define GDMA_OUTFIFO_UDF_L1_CH4_INT_RAW_S  5
/* GDMA_OUTFIFO_off_L1_CH4_INT_RAW:R/WTC/SS；位位置：[4]；默认值：1’b0；*/
/*描述：当Tx信道4的1级fifo等流量时，此原始中断位变为高电平。*/
#define GDMA_OUTFIFO_OVF_L1_CH4_INT_RAW    (BIT(4))
#define GDMA_OUTFIFO_OVF_L1_CH4_INT_RAW_M  (BIT(4))
#define GDMA_OUTFIFO_OVF_L1_CH4_INT_RAW_V  0x1
#define GDMA_OUTFIFO_OVF_L1_CH4_INT_RAW_S  4
/* GDMA_OUT_TOTAL_EOF_CH4_INT_RAW:R/WTC/SS；位位置：[3]；默认值：1’b0；*/
/*描述：当针对Tx信道4发送出与输出链接（包括一个链路描述符或几个链路描述符）相对应的数据时，原始中断位变为高电平。。*/
#define GDMA_OUT_TOTAL_EOF_CH4_INT_RAW    (BIT(3))
#define GDMA_OUT_TOTAL_EOF_CH4_INT_RAW_M  (BIT(3))
#define GDMA_OUT_TOTAL_EOF_CH4_INT_RAW_V  0x1
#define GDMA_OUT_TOTAL_EOF_CH4_INT_RAW_S  3
/* GDMA_OUT_DSCR_ERR_CH4_INT_RAW:R/WTC/SS；位位置：[2]；默认值：1’b0；*/
/*描述：当检测到outlink描述符错误时，原始中断位变为高电平，包括所有者错误、Tx信道4的outlink描述符的第二个和第三个字错误。。*/
#define GDMA_OUT_DSCR_ERR_CH4_INT_RAW    (BIT(2))
#define GDMA_OUT_DSCR_ERR_CH4_INT_RAW_M  (BIT(2))
#define GDMA_OUT_DSCR_ERR_CH4_INT_RAW_V  0x1
#define GDMA_OUT_DSCR_ERR_CH4_INT_RAW_S  2
/* GDMA_OUT_EOF_CH4_INT_RAW:R/WTC/SS；位位置：[1]；默认值：1’b0；*/
/*描述：当从Tx信道4的存储器中读取一个输出描述符所指向的最后一个数据时，原始中断位变为高电平。*/
#define GDMA_OUT_EOF_CH4_INT_RAW    (BIT(1))
#define GDMA_OUT_EOF_CH4_INT_RAW_M  (BIT(1))
#define GDMA_OUT_EOF_CH4_INT_RAW_V  0x1
#define GDMA_OUT_EOF_CH4_INT_RAW_S  1
/* GDMA_OUT_DONE_CH4_INT_RAW:R/WTC/SS；位位置：[0]；默认值：1’b0；*/
/*描述：当一个输出描述符所指向的最后一个数据已传输到Tx信道4的外围设备时，原始中断位变为高电平。。*/
#define GDMA_OUT_DONE_CH4_INT_RAW    (BIT(0))
#define GDMA_OUT_DONE_CH4_INT_RAW_M  (BIT(0))
#define GDMA_OUT_DONE_CH4_INT_RAW_V  0x1
#define GDMA_OUT_DONE_CH4_INT_RAW_S  0

#define GDMA_OUT_INT_ST_CH4_REG          (DR_REG_GDMA_BASE + 0x36C)
/* GDMA_OUTFIFO_UDF_L3_CH4_INT_ST:RO；位位置：[7]；默认值：1’b0；*/
/*description:OUTFIFO_UDF_L3_CH_INT中断的原始中断状态位。。*/
#define GDMA_OUTFIFO_UDF_L3_CH4_INT_ST    (BIT(7))
#define GDMA_OUTFIFO_UDF_L3_CH4_INT_ST_M  (BIT(7))
#define GDMA_OUTFIFO_UDF_L3_CH4_INT_ST_V  0x1
#define GDMA_OUTFIFO_UDF_L3_CH4_INT_ST_S  7
/* GDMA_OUTFIFO_off_13_CH4_INT_ST:RO；位位置：[6]；默认值：1’b0；*/
/*description:OUTFIFO_OVF_L3_CH_INT中断的原始中断状态位。。*/
#define GDMA_OUTFIFO_OVF_L3_CH4_INT_ST    (BIT(6))
#define GDMA_OUTFIFO_OVF_L3_CH4_INT_ST_M  (BIT(6))
#define GDMA_OUTFIFO_OVF_L3_CH4_INT_ST_V  0x1
#define GDMA_OUTFIFO_OVF_L3_CH4_INT_ST_S  6
/* GDMA_OUTFIFO_UDF_L1_CH4_INT_ST:RO；位位置：[5]；默认值：1’b0；*/
/*description:OUTFIFO_UDF_L1_CH_INT中断的原始中断状态位。。*/
#define GDMA_OUTFIFO_UDF_L1_CH4_INT_ST    (BIT(5))
#define GDMA_OUTFIFO_UDF_L1_CH4_INT_ST_M  (BIT(5))
#define GDMA_OUTFIFO_UDF_L1_CH4_INT_ST_V  0x1
#define GDMA_OUTFIFO_UDF_L1_CH4_INT_ST_S  5
/* GDMA_OUTFIFO_off_L1_CH4_INT_ST:RO；位位置：[4]；默认值：1’b0；*/
/*description:OUTFIFO_OVF_L1_CH_INT中断的原始中断状态位。。*/
#define GDMA_OUTFIFO_OVF_L1_CH4_INT_ST    (BIT(4))
#define GDMA_OUTFIFO_OVF_L1_CH4_INT_ST_M  (BIT(4))
#define GDMA_OUTFIFO_OVF_L1_CH4_INT_ST_V  0x1
#define GDMA_OUTFIFO_OVF_L1_CH4_INT_ST_S  4
/* GDMA_OUT_TOTAL_EOF_CH4_INT_ST:RO；位位置：[3]；默认值：1’b0；*/
/*description:OUT_TOTAL_EOF_CH_INT中断的原始中断状态位。。*/
#define GDMA_OUT_TOTAL_EOF_CH4_INT_ST    (BIT(3))
#define GDMA_OUT_TOTAL_EOF_CH4_INT_ST_M  (BIT(3))
#define GDMA_OUT_TOTAL_EOF_CH4_INT_ST_V  0x1
#define GDMA_OUT_TOTAL_EOF_CH4_INT_ST_S  3
/* GDMA_OUT_DSCR_ERR_CH4_INT_ST:RO；位位置：[2]；默认值：1’b0；*/
/*description:OUT_DSCR_ERR_CH_INT中断的原始中断状态位。。*/
#define GDMA_OUT_DSCR_ERR_CH4_INT_ST    (BIT(2))
#define GDMA_OUT_DSCR_ERR_CH4_INT_ST_M  (BIT(2))
#define GDMA_OUT_DSCR_ERR_CH4_INT_ST_V  0x1
#define GDMA_OUT_DSCR_ERR_CH4_INT_ST_S  2
/* GDMA_OUT_EOF_CH4_INT_ST:RO；位位置：[1]；默认值：1’b0；*/
/*description:OUT_EOF_CH_INT中断的原始中断状态位。。*/
#define GDMA_OUT_EOF_CH4_INT_ST    (BIT(1))
#define GDMA_OUT_EOF_CH4_INT_ST_M  (BIT(1))
#define GDMA_OUT_EOF_CH4_INT_ST_V  0x1
#define GDMA_OUT_EOF_CH4_INT_ST_S  1
/* GDMA_OUT_DONE_CH4_INT_ST:RO；位位置：[0]；默认值：1’b0；*/
/*description:OUT_DONE_CH_INT中断的原始中断状态位。。*/
#define GDMA_OUT_DONE_CH4_INT_ST    (BIT(0))
#define GDMA_OUT_DONE_CH4_INT_ST_M  (BIT(0))
#define GDMA_OUT_DONE_CH4_INT_ST_V  0x1
#define GDMA_OUT_DONE_CH4_INT_ST_S  0

#define GDMA_OUT_INT_ENA_CH4_REG          (DR_REG_GDMA_BASE + 0x370)
/* GDMA_OUTFIFO_UDF_13_CH4_INT_ENA:R/W；位位置：[7]；默认值：1’b0；*/
/*description:OUTFIFO_UDF_L3_CH_INT中断的中断启用位。。*/
#define GDMA_OUTFIFO_UDF_L3_CH4_INT_ENA    (BIT(7))
#define GDMA_OUTFIFO_UDF_L3_CH4_INT_ENA_M  (BIT(7))
#define GDMA_OUTFIFO_UDF_L3_CH4_INT_ENA_V  0x1
#define GDMA_OUTFIFO_UDF_L3_CH4_INT_ENA_S  7
/* GDMA_OUTFIFO_off_13_CH4_INT_ENA:R/W；位位置：[6]；默认值：1’b0；*/
/*description:OUTFIFO_OVF_L3_CH_INT中断的中断启用位。。*/
#define GDMA_OUTFIFO_OVF_L3_CH4_INT_ENA    (BIT(6))
#define GDMA_OUTFIFO_OVF_L3_CH4_INT_ENA_M  (BIT(6))
#define GDMA_OUTFIFO_OVF_L3_CH4_INT_ENA_V  0x1
#define GDMA_OUTFIFO_OVF_L3_CH4_INT_ENA_S  6
/* GDMA_OUTFIFO_UDF_L1_CH4_INT_ENA:R/W；位位置：[5]；默认值：1’b0；*/
/*description:OUTFIFO_UDF_L1_CH_INT中断的中断启用位。。*/
#define GDMA_OUTFIFO_UDF_L1_CH4_INT_ENA    (BIT(5))
#define GDMA_OUTFIFO_UDF_L1_CH4_INT_ENA_M  (BIT(5))
#define GDMA_OUTFIFO_UDF_L1_CH4_INT_ENA_V  0x1
#define GDMA_OUTFIFO_UDF_L1_CH4_INT_ENA_S  5
/* GDMA_OUTFIFO_off_L1_CH4_INT_ENA:R/W；位位置：[4]；默认值：1’b0；*/
/*description:OUTFIFO_OVF_L1_CH_INT中断的中断启用位。。*/
#define GDMA_OUTFIFO_OVF_L1_CH4_INT_ENA    (BIT(4))
#define GDMA_OUTFIFO_OVF_L1_CH4_INT_ENA_M  (BIT(4))
#define GDMA_OUTFIFO_OVF_L1_CH4_INT_ENA_V  0x1
#define GDMA_OUTFIFO_OVF_L1_CH4_INT_ENA_S  4
/* GDMA_OUT_TOTAL_EOF_CH4_INT_ENA:R/W；位位置：[3]；默认值：1’b0；*/
/*description:OUT_TOTAL_EOF_CH_INT中断的中断启用位。。*/
#define GDMA_OUT_TOTAL_EOF_CH4_INT_ENA    (BIT(3))
#define GDMA_OUT_TOTAL_EOF_CH4_INT_ENA_M  (BIT(3))
#define GDMA_OUT_TOTAL_EOF_CH4_INT_ENA_V  0x1
#define GDMA_OUT_TOTAL_EOF_CH4_INT_ENA_S  3
/* GDMA_OUT_DSCR_ERR_CH4_INT_ENA:R/W；位位置：[2]；默认值：1’b0；*/
/*description:OUT_DSCR_ERR_CH_INT中断的中断启用位。。*/
#define GDMA_OUT_DSCR_ERR_CH4_INT_ENA    (BIT(2))
#define GDMA_OUT_DSCR_ERR_CH4_INT_ENA_M  (BIT(2))
#define GDMA_OUT_DSCR_ERR_CH4_INT_ENA_V  0x1
#define GDMA_OUT_DSCR_ERR_CH4_INT_ENA_S  2
/* GDMA_OUT_EOF_CH4_INT_ENA:R/W；位位置：[1]；默认值：1’b0；*/
/*description:OUT_EOF_CH_INT中断的中断启用位。。*/
#define GDMA_OUT_EOF_CH4_INT_ENA    (BIT(1))
#define GDMA_OUT_EOF_CH4_INT_ENA_M  (BIT(1))
#define GDMA_OUT_EOF_CH4_INT_ENA_V  0x1
#define GDMA_OUT_EOF_CH4_INT_ENA_S  1
/* GDMA_OUT_DONE_CH4_INT_ENA:R/W；位位置：[0]；默认值：1’b0；*/
/*description:OUT_DONE_CH_INT中断的中断启用位。。*/
#define GDMA_OUT_DONE_CH4_INT_ENA    (BIT(0))
#define GDMA_OUT_DONE_CH4_INT_ENA_M  (BIT(0))
#define GDMA_OUT_DONE_CH4_INT_ENA_V  0x1
#define GDMA_OUT_DONE_CH4_INT_ENA_S  0

#define GDMA_OUT_INT_CLR_CH4_REG          (DR_REG_GDMA_BASE + 0x374)
/* GDMA_OUTFIFO_UDF_13_CH4_INT_CLR:WO；位位置：[7]；默认值：1’b0；*/
/*description:设置此位以清除OUTFIFO_UDF_L3_CH_INT中断。。*/
#define GDMA_OUTFIFO_UDF_L3_CH4_INT_CLR    (BIT(7))
#define GDMA_OUTFIFO_UDF_L3_CH4_INT_CLR_M  (BIT(7))
#define GDMA_OUTFIFO_UDF_L3_CH4_INT_CLR_V  0x1
#define GDMA_OUTFIFO_UDF_L3_CH4_INT_CLR_S  7
/* GDMA_OUTFIFO_off_13_CH4_INT_CLR:WO；位位置：[6]；默认值：1’b0；*/
/*description:设置此位以清除OUTFIFO_OVF_L3_CH_INT中断。。*/
#define GDMA_OUTFIFO_OVF_L3_CH4_INT_CLR    (BIT(6))
#define GDMA_OUTFIFO_OVF_L3_CH4_INT_CLR_M  (BIT(6))
#define GDMA_OUTFIFO_OVF_L3_CH4_INT_CLR_V  0x1
#define GDMA_OUTFIFO_OVF_L3_CH4_INT_CLR_S  6
/* GDMA_OUTFIFO_UDF_L1_CH4_INT_CLR:WO；位位置：[5]；默认值：1’b0；*/
/*description:设置此位以清除OUTFIFO_UDF_L1_CH_INT中断。。*/
#define GDMA_OUTFIFO_UDF_L1_CH4_INT_CLR    (BIT(5))
#define GDMA_OUTFIFO_UDF_L1_CH4_INT_CLR_M  (BIT(5))
#define GDMA_OUTFIFO_UDF_L1_CH4_INT_CLR_V  0x1
#define GDMA_OUTFIFO_UDF_L1_CH4_INT_CLR_S  5
/* GDMA_OUTFIFO_off_L1_CH4_INT_CLR:WO；位位置：[4]；默认值：1’b0；*/
/*description:设置此位以清除OUTFIFO_OVF_L1_CH_INT中断。。*/
#define GDMA_OUTFIFO_OVF_L1_CH4_INT_CLR    (BIT(4))
#define GDMA_OUTFIFO_OVF_L1_CH4_INT_CLR_M  (BIT(4))
#define GDMA_OUTFIFO_OVF_L1_CH4_INT_CLR_V  0x1
#define GDMA_OUTFIFO_OVF_L1_CH4_INT_CLR_S  4
/* GDMA_OUT_TOTAL_EOF_CH4_INT_CLR:WT；位位置：[3]；默认值：1’b0；*/
/*description:设置此位以清除OUT_TOTAL_EOF_CH_INT中断。。*/
#define GDMA_OUT_TOTAL_EOF_CH4_INT_CLR    (BIT(3))
#define GDMA_OUT_TOTAL_EOF_CH4_INT_CLR_M  (BIT(3))
#define GDMA_OUT_TOTAL_EOF_CH4_INT_CLR_V  0x1
#define GDMA_OUT_TOTAL_EOF_CH4_INT_CLR_S  3
/* GDMA_OUT_DSCR_ERR_CH4_INT_CLR:WT；位位置：[2]；默认值：1’b0；*/
/*description:设置此位以清除OUT_DSCR_ERR_CH_INT中断。。*/
#define GDMA_OUT_DSCR_ERR_CH4_INT_CLR    (BIT(2))
#define GDMA_OUT_DSCR_ERR_CH4_INT_CLR_M  (BIT(2))
#define GDMA_OUT_DSCR_ERR_CH4_INT_CLR_V  0x1
#define GDMA_OUT_DSCR_ERR_CH4_INT_CLR_S  2
/* GDMA_OUT_EOF_CH4_INT_CLR:WT；位位置：[1]；默认值：1’b0；*/
/*description:设置此位以清除OUT_EOF_CH_INT中断。。*/
#define GDMA_OUT_EOF_CH4_INT_CLR    (BIT(1))
#define GDMA_OUT_EOF_CH4_INT_CLR_M  (BIT(1))
#define GDMA_OUT_EOF_CH4_INT_CLR_V  0x1
#define GDMA_OUT_EOF_CH4_INT_CLR_S  1
/* GDMA_OUT_DONE_CH4_INT_CLR:WT；位位置：[0]；默认值：1’b0；*/
/*description:设置此位以清除OUT_DONE_CH_INT中断。。*/
#define GDMA_OUT_DONE_CH4_INT_CLR    (BIT(0))
#define GDMA_OUT_DONE_CH4_INT_CLR_M  (BIT(0))
#define GDMA_OUT_DONE_CH4_INT_CLR_V  0x1
#define GDMA_OUT_DONE_CH4_INT_CLR_S  0

#define GDMA_OUTFIFO_STATUS_CH4_REG          (DR_REG_GDMA_BASE + 0x378)
/* GDMA_OUT_REMAIN_UNDER_4B_L3_CH4:RO；位位置：[26]；默认值：1’b1；*/
/*description:保留。*/
#define GDMA_OUT_REMAIN_UNDER_4B_L3_CH4    (BIT(26))
#define GDMA_OUT_REMAIN_UNDER_4B_L3_CH4_M  (BIT(26))
#define GDMA_OUT_REMAIN_UNDER_4B_L3_CH4_V  0x1
#define GDMA_OUT_REMAIN_UNDER_4B_L3_CH4_S  26
/* GDMA_OUT_REMAIN_UNDER_3B_L3_CH4:RO；位位置：[25]；默认值：1’b1；*/
/*description:保留。*/
#define GDMA_OUT_REMAIN_UNDER_3B_L3_CH4    (BIT(25))
#define GDMA_OUT_REMAIN_UNDER_3B_L3_CH4_M  (BIT(25))
#define GDMA_OUT_REMAIN_UNDER_3B_L3_CH4_V  0x1
#define GDMA_OUT_REMAIN_UNDER_3B_L3_CH4_S  25
/* GDMA_OUT_REMAIN_UNDER_2B_L3_CH4:RO；位位置：[24]；默认值：1’b1；*/
/*description:保留。*/
#define GDMA_OUT_REMAIN_UNDER_2B_L3_CH4    (BIT(24))
#define GDMA_OUT_REMAIN_UNDER_2B_L3_CH4_M  (BIT(24))
#define GDMA_OUT_REMAIN_UNDER_2B_L3_CH4_V  0x1
#define GDMA_OUT_REMAIN_UNDER_2B_L3_CH4_S  24
/* GDMA_OUT_REMAIN_UNDER_1B_L3_CH4:RO；位位置：[23]；默认值：1’b1；*/
/*description:保留。*/
#define GDMA_OUT_REMAIN_UNDER_1B_L3_CH4    (BIT(23))
#define GDMA_OUT_REMAIN_UNDER_1B_L3_CH4_M  (BIT(23))
#define GDMA_OUT_REMAIN_UNDER_1B_L3_CH4_V  0x1
#define GDMA_OUT_REMAIN_UNDER_1B_L3_CH4_S  23
/* GDMA_OUTFIFO_CNT_L3_CH4:RO；比特位置：[22:18]；默认值：5’b0；*/
/*描述：寄存器将数据的字节数存储在Tx信道4的L3 Tx FIFO中。。*/
#define GDMA_OUTFIFO_CNT_L3_CH4    0x0000001F
#define GDMA_OUTFIFO_CNT_L3_CH4_M  ((GDMA_OUTFIFO_CNT_L3_CH4_V)<<(GDMA_OUTFIFO_CNT_L3_CH4_S))
#define GDMA_OUTFIFO_CNT_L3_CH4_V  0x1F
#define GDMA_OUTFIFO_CNT_L3_CH4_S  18
/* GDMA_OUTFIFO_CNT_L2_CH4:RO；比特位置：[17:11]；默认值：7'b0；*/
/*描述：寄存器将数据的字节数存储在Tx信道4的L2 Tx FIFO中。。*/
#define GDMA_OUTFIFO_CNT_L2_CH4    0x0000007F
#define GDMA_OUTFIFO_CNT_L2_CH4_M  ((GDMA_OUTFIFO_CNT_L2_CH4_V)<<(GDMA_OUTFIFO_CNT_L2_CH4_S))
#define GDMA_OUTFIFO_CNT_L2_CH4_V  0x7F
#define GDMA_OUTFIFO_CNT_L2_CH4_S  11
/* GDMA_OUTFIFO_CNT_L1_CH4:RO；比特位置：[10:6]；默认值：5’b0；*/
/*描述：寄存器将数据的字节数存储在Tx信道4的L1 Tx FIFO中。。*/
#define GDMA_OUTFIFO_CNT_L1_CH4    0x0000001F
#define GDMA_OUTFIFO_CNT_L1_CH4_M  ((GDMA_OUTFIFO_CNT_L1_CH4_V)<<(GDMA_OUTFIFO_CNT_L1_CH4_S))
#define GDMA_OUTFIFO_CNT_L1_CH4_V  0x1F
#define GDMA_OUTFIFO_CNT_L1_CH4_S  6
/* GDMA_OUTFIFO_EMPTY_L3_CH4:RO；位位置：[5]；默认值：1’b1；*/
/*描述：Tx信道4的L3 Tx FIFO空信号。。*/
#define GDMA_OUTFIFO_EMPTY_L3_CH4    (BIT(5))
#define GDMA_OUTFIFO_EMPTY_L3_CH4_M  (BIT(5))
#define GDMA_OUTFIFO_EMPTY_L3_CH4_V  0x1
#define GDMA_OUTFIFO_EMPTY_L3_CH4_S  5
/* GDMA_OUTFIFO_FULL_L3_CH4:RO；位位置：[4]；默认值：1’b0；*/
/*描述：Tx信道4的L3 Tx FIFO满信号。。*/
#define GDMA_OUTFIFO_FULL_L3_CH4    (BIT(4))
#define GDMA_OUTFIFO_FULL_L3_CH4_M  (BIT(4))
#define GDMA_OUTFIFO_FULL_L3_CH4_V  0x1
#define GDMA_OUTFIFO_FULL_L3_CH4_S  4
/* GDMA_OUTFIFO_EMPTY_L2_CH4:RO；位位置：[3]；默认值：1’b1；*/
/*描述：Tx信道4的L2 Tx FIFO空信号。。*/
#define GDMA_OUTFIFO_EMPTY_L2_CH4    (BIT(3))
#define GDMA_OUTFIFO_EMPTY_L2_CH4_M  (BIT(3))
#define GDMA_OUTFIFO_EMPTY_L2_CH4_V  0x1
#define GDMA_OUTFIFO_EMPTY_L2_CH4_S  3
/* GDMA_OUTFIFO_FULL_L2_CH4:RO；位位置：[2]；默认值：1’b0；*/
/*描述：Tx信道4的L2 Tx FIFO满信号。。*/
#define GDMA_OUTFIFO_FULL_L2_CH4    (BIT(2))
#define GDMA_OUTFIFO_FULL_L2_CH4_M  (BIT(2))
#define GDMA_OUTFIFO_FULL_L2_CH4_V  0x1
#define GDMA_OUTFIFO_FULL_L2_CH4_S  2
/* GDMA_OUTFIFO_EMPTY_L1_CH4:RO；位位置：[1]；默认值：1’b1；*/
/*描述：Tx信道4的L1 Tx FIFO空信号。。*/
#define GDMA_OUTFIFO_EMPTY_L1_CH4    (BIT(1))
#define GDMA_OUTFIFO_EMPTY_L1_CH4_M  (BIT(1))
#define GDMA_OUTFIFO_EMPTY_L1_CH4_V  0x1
#define GDMA_OUTFIFO_EMPTY_L1_CH4_S  1
/* GDMA_OUTFIFO_FULL_L1_CH4:RO；位位置：[0]；默认值：1’b0；*/
/*描述：Tx信道4的L1 Tx FIFO完整信号。。*/
#define GDMA_OUTFIFO_FULL_L1_CH4    (BIT(0))
#define GDMA_OUTFIFO_FULL_L1_CH4_M  (BIT(0))
#define GDMA_OUTFIFO_FULL_L1_CH4_V  0x1
#define GDMA_OUTFIFO_FULL_L1_CH4_S  0

#define GDMA_OUT_PUSH_CH4_REG          (DR_REG_GDMA_BASE + 0x37C)
/* GDMA_OUTFIFO_PUSH_CH4:R/W/SC；位位置：[9]；默认值：1'0；*/
/*description:设置此位以将数据推入DMA FIFO。。*/
#define GDMA_OUTFIFO_PUSH_CH4    (BIT(9))
#define GDMA_OUTFIFO_PUSH_CH4_M  (BIT(9))
#define GDMA_OUTFIFO_PUSH_CH4_V  0x1
#define GDMA_OUTFIFO_PUSH_CH4_S  9
/* GDMA_OUTFIFO_WDATA_CH4:R/W；位位置：[8:0]；默认值：9'0；*/
/*description:此寄存器存储需要推入DMA FIFO的数据。。*/
#define GDMA_OUTFIFO_WDATA_CH4    0x000001FF
#define GDMA_OUTFIFO_WDATA_CH4_M  ((GDMA_OUTFIFO_WDATA_CH4_V)<<(GDMA_OUTFIFO_WDATA_CH4_S))
#define GDMA_OUTFIFO_WDATA_CH4_V  0x1FF
#define GDMA_OUTFIFO_WDATA_CH4_S  0

#define GDMA_OUT_LINK_CH4_REG          (DR_REG_GDMA_BASE + 0x380)
/* GDMA_OUTLINK_PARK_CH4:RO；位位置：[23]；默认值：1'h1；*/
/*描述：1:outlink描述符的FSM处于空闲状态。0:outlink描述符的FSM正在工作。。*/
#define GDMA_OUTLINK_PARK_CH4    (BIT(23))
#define GDMA_OUTLINK_PARK_CH4_M  (BIT(23))
#define GDMA_OUTLINK_PARK_CH4_V  0x1
#define GDMA_OUTLINK_PARK_CH4_S  23
/* GDMA_OUTLINK_RESTART_CH4：R/W/SC；位位置：[22]；默认值：1’b0；*/
/*description:设置此位以从上一个地址重新启动新的outlink。*/
#define GDMA_OUTLINK_RESTART_CH4    (BIT(22))
#define GDMA_OUTLINK_RESTART_CH4_M  (BIT(22))
#define GDMA_OUTLINK_RESTART_CH4_V  0x1
#define GDMA_OUTLINK_RESTART_CH4_S  22
/* GDMA_OUTLINK_START_CH4:R/W/SC；位位置：[21]；默认值：1’b0；*/
/*description:设置此位以开始处理outlink描述符。。*/
#define GDMA_OUTLINK_START_CH4    (BIT(21))
#define GDMA_OUTLINK_START_CH4_M  (BIT(21))
#define GDMA_OUTLINK_START_CH4_V  0x1
#define GDMA_OUTLINK_START_CH4_S  21
/* GDMA_OUTLINK_STOP_CH4:R/W/SC；位位置：[20]；默认值：1’b0；*/
/*description:设置此位以停止处理outlink描述符。。*/
#define GDMA_OUTLINK_STOP_CH4    (BIT(20))
#define GDMA_OUTLINK_STOP_CH4_M  (BIT(20))
#define GDMA_OUTLINK_STOP_CH4_V  0x1
#define GDMA_OUTLINK_STOP_CH4_S  20
/* GDMA_OUTLINK_ADDR_CH4:R/W；比特位置：[19:0]；默认值：20'00；*/
/*description:此寄存器存储第一个outlink描述符地址的20个最低有效位。。*/
#define GDMA_OUTLINK_ADDR_CH4    0x000FFFFF
#define GDMA_OUTLINK_ADDR_CH4_M  ((GDMA_OUTLINK_ADDR_CH4_V)<<(GDMA_OUTLINK_ADDR_CH4_S))
#define GDMA_OUTLINK_ADDR_CH4_V  0xFFFFF
#define GDMA_OUTLINK_ADDR_CH4_S  0

#define GDMA_OUT_STATE_CH4_REG          (DR_REG_GDMA_BASE + 0x384)
/* GDMA_OUT_STATE_CH4:RO；比特位置：[22:20]；默认值：3'b0；*/
/*description:保留。*/
#define GDMA_OUT_STATE_CH4    0x00000007
#define GDMA_OUT_STATE_CH4_M  ((GDMA_OUT_STATE_CH4_V)<<(GDMA_OUT_STATE_CH4_S))
#define GDMA_OUT_STATE_CH4_V  0x7
#define GDMA_OUT_STATE_CH4_S  20
/* GDMA_OUT_DSCR_STATE_CH4:RO；比特位置：[19:18]；默认值：2’b0；*/
/*description:保留。*/
#define GDMA_OUT_DSCR_STATE_CH4    0x00000003
#define GDMA_OUT_DSCR_STATE_CH4_M  ((GDMA_OUT_DSCR_STATE_CH4_V)<<(GDMA_OUT_DSCR_STATE_CH4_S))
#define GDMA_OUT_DSCR_STATE_CH4_V  0x3
#define GDMA_OUT_DSCR_STATE_CH4_S  18
/* GDMA_OUTLINK_DSCR_ADDR_CH4:RO；比特位置：[17:00]；默认值：18'b0；*/
/*description:此寄存器存储当前outlink描述符的地址。。*/
#define GDMA_OUTLINK_DSCR_ADDR_CH4    0x0003FFFF
#define GDMA_OUTLINK_DSCR_ADDR_CH4_M  ((GDMA_OUTLINK_DSCR_ADDR_CH4_V)<<(GDMA_OUTLINK_DSCR_ADDR_CH4_S))
#define GDMA_OUTLINK_DSCR_ADDR_CH4_V  0x3FFFF
#define GDMA_OUTLINK_DSCR_ADDR_CH4_S  0

#define GDMA_OUT_EOF_DES_ADDR_CH4_REG          (DR_REG_GDMA_BASE + 0x388)
/* GDMA_OUT_EOF_DES_ADDR_CH4:RO；位位置：[31:0]；默认值：32'h0；*/
/*description:当此描述符中的EOF位为1时，此寄存器存储outlink描述符的地址。。*/
#define GDMA_OUT_EOF_DES_ADDR_CH4    0xFFFFFFFF
#define GDMA_OUT_EOF_DES_ADDR_CH4_M  ((GDMA_OUT_EOF_DES_ADDR_CH4_V)<<(GDMA_OUT_EOF_DES_ADDR_CH4_S))
#define GDMA_OUT_EOF_DES_ADDR_CH4_V  0xFFFFFFFF
#define GDMA_OUT_EOF_DES_ADDR_CH4_S  0

#define GDMA_OUT_EOF_BFR_DES_ADDR_CH4_REG          (DR_REG_GDMA_BASE + 0x38C)
/* GDMA_OUT_EOF_BFR_DES_ADDR_CH4:RO；位位置：[31:0]；默认值：32'h0；*/
/*description:此寄存器存储最后一个outlink描述符之前的outlink描述符的地址。。*/
#define GDMA_OUT_EOF_BFR_DES_ADDR_CH4    0xFFFFFFFF
#define GDMA_OUT_EOF_BFR_DES_ADDR_CH4_M  ((GDMA_OUT_EOF_BFR_DES_ADDR_CH4_V)<<(GDMA_OUT_EOF_BFR_DES_ADDR_CH4_S))
#define GDMA_OUT_EOF_BFR_DES_ADDR_CH4_V  0xFFFFFFFF
#define GDMA_OUT_EOF_BFR_DES_ADDR_CH4_S  0

#define GDMA_OUT_DSCR_CH4_REG          (DR_REG_GDMA_BASE + 0x390)
/* GDMA_OUTLINK_DSCR_CH4:RO；位位置：[31:0]；默认值：32'b0；*/
/*description:当前outlink描述符y的地址。。*/
#define GDMA_OUTLINK_DSCR_CH4    0xFFFFFFFF
#define GDMA_OUTLINK_DSCR_CH4_M  ((GDMA_OUTLINK_DSCR_CH4_V)<<(GDMA_OUTLINK_DSCR_CH4_S))
#define GDMA_OUTLINK_DSCR_CH4_V  0xFFFFFFFF
#define GDMA_OUTLINK_DSCR_CH4_S  0

#define GDMA_OUT_DSCR_BF0_CH4_REG          (DR_REG_GDMA_BASE + 0x394)
/* GDMA_OUTLINK_DSCR_BF0_CH4:RO；位位置：[31:0]；默认值：32'b0；*/
/*description:最后一个outlink描述符的地址y-1。。*/
#define GDMA_OUTLINK_DSCR_BF0_CH4    0xFFFFFFFF
#define GDMA_OUTLINK_DSCR_BF0_CH4_M  ((GDMA_OUTLINK_DSCR_BF0_CH4_V)<<(GDMA_OUTLINK_DSCR_BF0_CH4_S))
#define GDMA_OUTLINK_DSCR_BF0_CH4_V  0xFFFFFFFF
#define GDMA_OUTLINK_DSCR_BF0_CH4_S  0

#define GDMA_OUT_DSCR_BF1_CH4_REG          (DR_REG_GDMA_BASE + 0x398)
/* GDMA_OUTLINK_DSCR_BF1_CH4:RO；位位置：[31:0]；默认值：32'b0；*/
/*description:倒数第二个内联描述符x-2的地址。。*/
#define GDMA_OUTLINK_DSCR_BF1_CH4    0xFFFFFFFF
#define GDMA_OUTLINK_DSCR_BF1_CH4_M  ((GDMA_OUTLINK_DSCR_BF1_CH4_V)<<(GDMA_OUTLINK_DSCR_BF1_CH4_S))
#define GDMA_OUTLINK_DSCR_BF1_CH4_V  0xFFFFFFFF
#define GDMA_OUTLINK_DSCR_BF1_CH4_S  0

#define GDMA_OUT_WIGHT_CH4_REG          (DR_REG_GDMA_BASE + 0x39C)
/* GDMA_TX_WEIGHT_CH4:R/W；位位置：[11:8]；默认值：4'hf；*/
/*description:Tx信道4的权重。*/
#define GDMA_TX_WEIGHT_CH4    0x0000000F
#define GDMA_TX_WEIGHT_CH4_M  ((GDMA_TX_WEIGHT_CH4_V)<<(GDMA_TX_WEIGHT_CH4_S))
#define GDMA_TX_WEIGHT_CH4_V  0xF
#define GDMA_TX_WEIGHT_CH4_S  8

#define GDMA_OUT_PRI_CH4_REG          (DR_REG_GDMA_BASE + 0x3A4)
/* GDMA_TX_PRI_CH4:R/W；位位置：[3:0]；默认值：4'b0；*/
/*description:Tx信道4的优先级。值越大，优先级越高。。*/
#define GDMA_TX_PRI_CH4    0x0000000F
#define GDMA_TX_PRI_CH4_M  ((GDMA_TX_PRI_CH4_V)<<(GDMA_TX_PRI_CH4_S))
#define GDMA_TX_PRI_CH4_V  0xF
#define GDMA_TX_PRI_CH4_S  0

#define GDMA_OUT_PERI_SEL_CH4_REG          (DR_REG_GDMA_BASE + 0x3A8)
/* GDMA_PERI_OUT_SEL_CH4:R/W；比特位置：[5:0]；默认值：6'h3f；*/
/*描述：此寄存器用于为Tx信道4.0:SPI2.1:SPI3.2:UHCI0.3:I2S0.4:I2S1.5:LCD_CAM选择外围设备。6： AES。7： 沙。8： ADC_DAC。9： 每立方米。；7： AES。8： 沙。9： ADC_DAC。。*/
#define GDMA_PERI_OUT_SEL_CH4    0x0000003F
#define GDMA_PERI_OUT_SEL_CH4_M  ((GDMA_PERI_OUT_SEL_CH4_V)<<(GDMA_PERI_OUT_SEL_CH4_S))
#define GDMA_PERI_OUT_SEL_CH4_V  0x3F
#define GDMA_PERI_OUT_SEL_CH4_S  0

#define GDMA_AHB_TEST_REG          (DR_REG_GDMA_BASE + 0x3C0)
/* GDMA_AHB_testadr:R/W；比特位置：[5:4]；默认值：2’b0；*/
/*description:保留。*/
#define GDMA_AHB_TESTADDR    0x00000003
#define GDMA_AHB_TESTADDR_M  ((GDMA_AHB_TESTADDR_V)<<(GDMA_AHB_TESTADDR_S))
#define GDMA_AHB_TESTADDR_V  0x3
#define GDMA_AHB_TESTADDR_S  4
/* GDMA_AHB_TESTMODE:R/W；位位置：[2:0]；默认值：3'b0；*/
/*description:保留。*/
#define GDMA_AHB_TESTMODE    0x00000007
#define GDMA_AHB_TESTMODE_M  ((GDMA_AHB_TESTMODE_V)<<(GDMA_AHB_TESTMODE_S))
#define GDMA_AHB_TESTMODE_V  0x7
#define GDMA_AHB_TESTMODE_S  0

#define GDMA_PD_CONF_REG          (DR_REG_GDMA_BASE + 0x3C4)
/* GDMA_DMA_RAM_CLK_FO:R/W；位位置：[6]；默认值：1’b0；*/
/*描述：1：在DMA中访问RAM时，强制打开时钟并绕过门时钟。0：在DMA中访问RAM时将使用门时钟。。*/
#define GDMA_DMA_RAM_CLK_FO    (BIT(6))
#define GDMA_DMA_RAM_CLK_FO_M  (BIT(6))
#define GDMA_DMA_RAM_CLK_FO_V  0x1
#define GDMA_DMA_RAM_CLK_FO_S  6
/* GDMA_DMA_RAM_FORCE_PU:R/W；位位置：[5]；默认值：1’b1；*/
/*描述：。*/
#define GDMA_DMA_RAM_FORCE_PU    (BIT(5))
#define GDMA_DMA_RAM_FORCE_PU_M  (BIT(5))
#define GDMA_DMA_RAM_FORCE_PU_V  0x1
#define GDMA_DMA_RAM_FORCE_PU_S  5
/* GDMA_DMA_RAM_FORCE_PD:R/W；位位置：[4]；默认值：1’b0；*/
/*description:断电。*/
#define GDMA_DMA_RAM_FORCE_PD    (BIT(4))
#define GDMA_DMA_RAM_FORCE_PD_M  (BIT(4))
#define GDMA_DMA_RAM_FORCE_PD_V  0x1
#define GDMA_DMA_RAM_FORCE_PD_S  4

#define GDMA_MISC_CONF_REG          (DR_REG_GDMA_BASE + 0x3C8)
/* GDMA_CLK_EN:R/W；位位置：[4]；默认值：1’b0；*/
/*描述：。*/
#define GDMA_CLK_EN    (BIT(4))
#define GDMA_CLK_EN_M  (BIT(4))
#define GDMA_CLK_EN_V  0x1
#define GDMA_CLK_EN_S  4
/* GDMA_ARB_PRI_DIS:R/W；位位置：[2]；默认值：1’b0；*/
/*description:设置此位以禁用优先级仲裁功能。。*/
#define GDMA_ARB_PRI_DIS    (BIT(2))
#define GDMA_ARB_PRI_DIS_M  (BIT(2))
#define GDMA_ARB_PRI_DIS_V  0x1
#define GDMA_ARB_PRI_DIS_S  2
/* GDMA_AHBM_RST_EXTER:R/W；位位置：[1]；默认值：1’b0；*/
/*description:设置此位，然后清除此位以重置外部ahb FSM。。*/
#define GDMA_AHBM_RST_EXTER    (BIT(1))
#define GDMA_AHBM_RST_EXTER_M  (BIT(1))
#define GDMA_AHBM_RST_EXTER_V  0x1
#define GDMA_AHBM_RST_EXTER_S  1
/* GDMA_AHBM_RST_INTER:R/W；位位置：[0]；默认值：1’b0；*/
/*description:设置此位，然后清除此位以重置内部ahb FSM。。*/
#define GDMA_AHBM_RST_INTER    (BIT(0))
#define GDMA_AHBM_RST_INTER_M  (BIT(0))
#define GDMA_AHBM_RST_INTER_V  0x1
#define GDMA_AHBM_RST_INTER_S  0

#define GDMA_IN_SRAM_SIZE_CH0_REG          (DR_REG_GDMA_BASE + 0x3CC)
/* GDMA_IN_SIZE_CH0:R/W；比特位置：[6:0]；默认值：7'd14；*/
/*描述：此寄存器用于配置Rx信道0.0:16字节的L2 Tx FIFO的大小。1： 24字节。2： 32字节。3： 40字节。4： 48字节。5： 56字节。6： 64字节。7： 72字节。8： 80字节。。*/
#define GDMA_IN_SIZE_CH0    0x0000007F
#define GDMA_IN_SIZE_CH0_M  ((GDMA_IN_SIZE_CH0_V)<<(GDMA_IN_SIZE_CH0_S))
#define GDMA_IN_SIZE_CH0_V  0x7F
#define GDMA_IN_SIZE_CH0_S  0

#define GDMA_OUT_SRAM_SIZE_CH0_REG          (DR_REG_GDMA_BASE + 0x3D0)
/* GDMA_OUT_SIZE_CH0:R/W；比特位置：[6:0]；默认值：7'd14；*/
/*描述：此寄存器用于配置Tx信道0.0:16字节的L2 Tx FIFO的大小。1： 24字节。2： 32字节。3： 40字节。4： 48字节。5： 56字节。6： 64字节。7： 72字节。8： 80字节。。*/
#define GDMA_OUT_SIZE_CH0    0x0000007F
#define GDMA_OUT_SIZE_CH0_M  ((GDMA_OUT_SIZE_CH0_V)<<(GDMA_OUT_SIZE_CH0_S))
#define GDMA_OUT_SIZE_CH0_V  0x7F
#define GDMA_OUT_SIZE_CH0_S  0

#define GDMA_IN_SRAM_SIZE_CH1_REG          (DR_REG_GDMA_BASE + 0x3D4)
/* GDMA_IN_SIZE_CH1:R/W；比特位置：[6:0]；默认值：7'd14；*/
/*描述：此寄存器用于配置Rx信道1.0:16字节的L2 Tx FIFO的大小。1： 24字节。2： 32字节。3： 40字节。4： 48字节。5： 56字节。6： 64字节。7： 72字节。8： 80字节。。*/
#define GDMA_IN_SIZE_CH1    0x0000007F
#define GDMA_IN_SIZE_CH1_M  ((GDMA_IN_SIZE_CH1_V)<<(GDMA_IN_SIZE_CH1_S))
#define GDMA_IN_SIZE_CH1_V  0x7F
#define GDMA_IN_SIZE_CH1_S  0

#define GDMA_OUT_SRAM_SIZE_CH1_REG          (DR_REG_GDMA_BASE + 0x3D8)
/* GDMA_OUT_SIZE_CH1:R/W；比特位置：[6:0]；默认值：7'd14；*/
/*描述：此寄存器用于为Tx信道1.0:16字节配置L2 Tx FIFO的大小。1： 24字节。2： 32字节。3： 40字节。4： 48字节。5： 56字节。6： 64字节。7： 72字节。8： 80字节。。*/
#define GDMA_OUT_SIZE_CH1    0x0000007F
#define GDMA_OUT_SIZE_CH1_M  ((GDMA_OUT_SIZE_CH1_V)<<(GDMA_OUT_SIZE_CH1_S))
#define GDMA_OUT_SIZE_CH1_V  0x7F
#define GDMA_OUT_SIZE_CH1_S  0

#define GDMA_IN_SRAM_SIZE_CH2_REG          (DR_REG_GDMA_BASE + 0x3DC)
/* GDMA_IN_SIZE_CH2:R/W；比特位置：[6:0]；默认值：7'd14；*/
/*描述：此寄存器用于配置Rx信道2.0:16字节的L2 Tx FIFO的大小。1： 24字节。2： 32字节。3： 40字节。4： 48字节。5： 56字节。6： 64字节。7： 72字节。8： 80字节。。*/
#define GDMA_IN_SIZE_CH2    0x0000007F
#define GDMA_IN_SIZE_CH2_M  ((GDMA_IN_SIZE_CH2_V)<<(GDMA_IN_SIZE_CH2_S))
#define GDMA_IN_SIZE_CH2_V  0x7F
#define GDMA_IN_SIZE_CH2_S  0

#define GDMA_OUT_SRAM_SIZE_CH2_REG          (DR_REG_GDMA_BASE + 0x3E0)
/* GDMA_OUT_SIZE_CH2:R/W；比特位置：[6:0]；默认值：7'd14；*/
/*描述：此寄存器用于为Tx信道2.0:16字节配置L2 Tx FIFO的大小。1： 24字节。2： 32字节。3： 40字节。4： 48字节。5： 56字节。6： 64字节。7： 72字节。8： 80字节。。*/
#define GDMA_OUT_SIZE_CH2    0x0000007F
#define GDMA_OUT_SIZE_CH2_M  ((GDMA_OUT_SIZE_CH2_V)<<(GDMA_OUT_SIZE_CH2_S))
#define GDMA_OUT_SIZE_CH2_V  0x7F
#define GDMA_OUT_SIZE_CH2_S  0

#define GDMA_IN_SRAM_SIZE_CH3_REG          (DR_REG_GDMA_BASE + 0x3E4)
/* GDMA_IN_SIZE_CH3:R/W；比特位置：[6:0]；默认值：7'd14；*/
/*描述：此寄存器用于配置Rx信道3.0:16字节的L2 Tx FIFO的大小。1： 24字节。2： 32字节。3： 40字节。4： 48字节。5： 56字节。6： 64字节。7： 72字节。8： 80字节。。*/
#define GDMA_IN_SIZE_CH3    0x0000007F
#define GDMA_IN_SIZE_CH3_M  ((GDMA_IN_SIZE_CH3_V)<<(GDMA_IN_SIZE_CH3_S))
#define GDMA_IN_SIZE_CH3_V  0x7F
#define GDMA_IN_SIZE_CH3_S  0

#define GDMA_OUT_SRAM_SIZE_CH3_REG          (DR_REG_GDMA_BASE + 0x3E8)
/* GDMA_OUT_SIZE_CH3:R/W；比特位置：[6:0]；默认值：7'd14；*/
/*描述：此寄存器用于为Tx信道3.0:16字节配置L2 Tx FIFO的大小。1： 24字节。2： 32字节。3： 40字节。4： 48字节。5： 56字节。6： 64字节。7： 72字节。8： 80字节。。*/
#define GDMA_OUT_SIZE_CH3    0x0000007F
#define GDMA_OUT_SIZE_CH3_M  ((GDMA_OUT_SIZE_CH3_V)<<(GDMA_OUT_SIZE_CH3_S))
#define GDMA_OUT_SIZE_CH3_V  0x7F
#define GDMA_OUT_SIZE_CH3_S  0

#define GDMA_IN_SRAM_SIZE_CH4_REG          (DR_REG_GDMA_BASE + 0x3EC)
/* GDMA_IN_SIZE_CH4:R/W；比特位置：[6:0]；默认值：7'd14；*/
/*描述：此寄存器用于配置Rx信道4.0:16字节的L2 Tx FIFO的大小。1： 24字节。2： 32字节。3： 40字节。4： 48字节。5： 56字节。6： 64字节。7： 72字节。8： 80字节。。*/
#define GDMA_IN_SIZE_CH4    0x0000007F
#define GDMA_IN_SIZE_CH4_M  ((GDMA_IN_SIZE_CH4_V)<<(GDMA_IN_SIZE_CH4_S))
#define GDMA_IN_SIZE_CH4_V  0x7F
#define GDMA_IN_SIZE_CH4_S  0

#define GDMA_OUT_SRAM_SIZE_CH4_REG          (DR_REG_GDMA_BASE + 0x3F0)
/* GDMA_OUT_SIZE_CH4:R/W；比特位置：[6:0]；默认值：7'd14；*/
/*描述：此寄存器用于为Tx信道4.0:16字节配置L2 Tx FIFO的大小。1： 24字节。2： 32字节。3： 40字节。4： 48字节。5： 56字节。6： 64字节。7： 72字节。8： 80字节。。*/
#define GDMA_OUT_SIZE_CH4    0x0000007F
#define GDMA_OUT_SIZE_CH4_M  ((GDMA_OUT_SIZE_CH4_V)<<(GDMA_OUT_SIZE_CH4_S))
#define GDMA_OUT_SIZE_CH4_V  0x7F
#define GDMA_OUT_SIZE_CH4_S  0

#define GDMA_EXTMEM_REJECT_ADDR_REG          (DR_REG_GDMA_BASE + 0x3F4)
/* GDMA_EXTMEM_REJECT_ADDR:RO；位位置：[31:0]；默认值：32'd0；*/
/*description:此寄存器存储访问外部RAM时权限控制拒绝的第一个地址。。*/
#define GDMA_EXTMEM_REJECT_ADDR    0xFFFFFFFF
#define GDMA_EXTMEM_REJECT_ADDR_M  ((GDMA_EXTMEM_REJECT_ADDR_V)<<(GDMA_EXTMEM_REJECT_ADDR_S))
#define GDMA_EXTMEM_REJECT_ADDR_V  0xFFFFFFFF
#define GDMA_EXTMEM_REJECT_ADDR_S  0

#define GDMA_EXTMEM_REJECT_ST_REG          (DR_REG_GDMA_BASE + 0x3F8)
/* GDMA_EXTMEM_REJECT_PERI_NUM:RO；位位置：[11:6]；默认值：6'b0；*/
/*description:此寄存器指示拒绝从哪个外围设备访问。。*/
#define GDMA_EXTMEM_REJECT_PERI_NUM    0x0000003F
#define GDMA_EXTMEM_REJECT_PERI_NUM_M  ((GDMA_EXTMEM_REJECT_PERI_NUM_V)<<(GDMA_EXTMEM_REJECT_PERI_NUM_S))
#define GDMA_EXTMEM_REJECT_PERI_NUM_V  0x3F
#define GDMA_EXTMEM_REJECT_PERI_NUM_S  6
/* GDMA_EXTMEM_REJECT_CHANNEL_NUM:RO；比特位置：[5:2]；默认值：4'b0；*/
/*description:寄存器指示拒绝从哪个通道访问。。*/
#define GDMA_EXTMEM_REJECT_CHANNEL_NUM    0x0000000F
#define GDMA_EXTMEM_REJECT_CHANNEL_NUM_M  ((GDMA_EXTMEM_REJECT_CHANNEL_NUM_V)<<(GDMA_EXTMEM_REJECT_CHANNEL_NUM_S))
#define GDMA_EXTMEM_REJECT_CHANNEL_NUM_V  0xF
#define GDMA_EXTMEM_REJECT_CHANNEL_NUM_S  2
/* GDMA_EXTMEM_REJECT_ATTR:RO；位位置：[1:0]；默认值：2’b0；*/
/*description:拒绝访问。位0：如果该位为1，则拒绝访问为READ。位1：如果该位为1，则拒绝访问为WRITE。。*/
#define GDMA_EXTMEM_REJECT_ATTR    0x00000003
#define GDMA_EXTMEM_REJECT_ATTR_M  ((GDMA_EXTMEM_REJECT_ATTR_V)<<(GDMA_EXTMEM_REJECT_ATTR_S))
#define GDMA_EXTMEM_REJECT_ATTR_V  0x3
#define GDMA_EXTMEM_REJECT_ATTR_S  0

#define GDMA_EXTMEM_REJECT_INT_RAW_REG          (DR_REG_GDMA_BASE + 0x3FC)
/* GDMA_EXTMEM_REJECT_INT_RAW:R/WTC/SS；位位置：[0]；默认值：1’b0；*/
/*描述：当访问外部RAM被权限控制拒绝时，原始中断位变为高电平。。*/
#define GDMA_EXTMEM_REJECT_INT_RAW    (BIT(0))
#define GDMA_EXTMEM_REJECT_INT_RAW_M  (BIT(0))
#define GDMA_EXTMEM_REJECT_INT_RAW_V  0x1
#define GDMA_EXTMEM_REJECT_INT_RAW_S  0

#define GDMA_EXTMEM_REJECT_INT_ST_REG          (DR_REG_GDMA_BASE + 0x400)
/* GDMA_EXTMEM_REJECT_INT_ST:RO；位位置：[0]；默认值：1’b0；*/
/*description:EXTMEM_REJECT_INT中断的原始中断状态位。。*/
#define GDMA_EXTMEM_REJECT_INT_ST    (BIT(0))
#define GDMA_EXTMEM_REJECT_INT_ST_M  (BIT(0))
#define GDMA_EXTMEM_REJECT_INT_ST_V  0x1
#define GDMA_EXTMEM_REJECT_INT_ST_S  0

#define GDMA_EXTMEM_REJECT_INT_ENA_REG          (DR_REG_GDMA_BASE + 0x404)
/* GDMA_EXTMEM_REJECT_INT_ENA:R/W；位位置：[0]；默认值：1’b0；*/
/*description:EXTMEM_REJECT_INT中断的中断启用位。。*/
#define GDMA_EXTMEM_REJECT_INT_ENA    (BIT(0))
#define GDMA_EXTMEM_REJECT_INT_ENA_M  (BIT(0))
#define GDMA_EXTMEM_REJECT_INT_ENA_V  0x1
#define GDMA_EXTMEM_REJECT_INT_ENA_S  0

#define GDMA_EXTMEM_REJECT_INT_CLR_REG          (DR_REG_GDMA_BASE + 0x408)
/* GDMA_EXTMEM_REJECT_INT_CLR:WT；位位置：[0]；默认值：1’b0；*/
/*description:设置此位以清除EXTMEM_REJECT_INT中断。。*/
#define GDMA_EXTMEM_REJECT_INT_CLR    (BIT(0))
#define GDMA_EXTMEM_REJECT_INT_CLR_M  (BIT(0))
#define GDMA_EXTMEM_REJECT_INT_CLR_V  0x1
#define GDMA_EXTMEM_REJECT_INT_CLR_S  0

#define GDMA_DATE_REG          (DR_REG_GDMA_BASE + 0x40C)
/* GDMA_DATE:R/W；位位置：[31:0]；默认值：32'h2101180；*/
/*description:注册版本。。*/
#define GDMA_DATE    0xFFFFFFFF
#define GDMA_DATE_M  ((GDMA_DATE_V)<<(GDMA_DATE_S))
#define GDMA_DATE_V  0xFFFFFFFF
#define GDMA_DATE_S  0


#ifdef __cplusplus
}
#endif



#endif /*_SOC_GDMA_REG_H_ */

