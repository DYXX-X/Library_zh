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
#ifndef _SOC_DMA_REG_H_
#define _SOC_DMA_REG_H_


#ifdef __cplusplus
extern "C" {
#endif
#include "soc.h"
#define DMA_INT_RAW_CH0_REG          (DR_REG_GDMA_BASE + 0x000)
/* DMA_OUTFIFO_UDF_CH0_INT_RAW:R/WTC/SS；位位置：[12]；默认值：1’b0；*/
/*描述：当Tx信道0的1级fifo下溢时，此原始中断位变为高电平。*/
#define DMA_OUTFIFO_UDF_CH0_INT_RAW  (BIT(12))
#define DMA_OUTFIFO_UDF_CH0_INT_RAW_M  (BIT(12))
#define DMA_OUTFIFO_UDF_CH0_INT_RAW_V  0x1
#define DMA_OUTFIFO_UDF_CH0_INT_RAW_S  12
/* DMA_OUTFIFO_off_CH0_INT_RAW:R/WTC/SS；位位置：[11]；默认值：1’b0；*/
/*描述：当Tx信道0的1级fifo溢出时，此原始中断位变为高电平。*/
#define DMA_OUTFIFO_OVF_CH0_INT_RAW  (BIT(11))
#define DMA_OUTFIFO_OVF_CH0_INT_RAW_M  (BIT(11))
#define DMA_OUTFIFO_OVF_CH0_INT_RAW_V  0x1
#define DMA_OUTFIFO_OVF_CH0_INT_RAW_S  11
/* DMA_INFIFO_UDF_CH0_INT_RAW:R/WTC/SS；位位置：[10]；默认值：1’b0；*/
/*描述：当Rx通道0的1级fifo下溢时，此原始中断位变为高电平。*/
#define DMA_INFIFO_UDF_CH0_INT_RAW  (BIT(10))
#define DMA_INFIFO_UDF_CH0_INT_RAW_M  (BIT(10))
#define DMA_INFIFO_UDF_CH0_INT_RAW_V  0x1
#define DMA_INFIFO_UDF_CH0_INT_RAW_S  10
/* DMA_INFIFO_off_CH0_INT_RAW:R/WTC/SS；位位置：[9]；默认值：1’b0；*/
/*描述：当Rx通道0的1级fifo溢出时，此原始中断位变为高电平。*/
#define DMA_INFIFO_OVF_CH0_INT_RAW  (BIT(9))
#define DMA_INFIFO_OVF_CH0_INT_RAW_M  (BIT(9))
#define DMA_INFIFO_OVF_CH0_INT_RAW_V  0x1
#define DMA_INFIFO_OVF_CH0_INT_RAW_S  9
/* DMA_OUT_TOTAL_EOF_CH0_INT_RAW:R/WTC/SS；位位置：[8]；默认值：1’b0；*/
/*描述：当针对Tx信道0发送出对应于outlink（包括一个链路描述符或几个链路描述符）的数据时，原始中断位变为高电平。*/
#define DMA_OUT_TOTAL_EOF_CH0_INT_RAW  (BIT(8))
#define DMA_OUT_TOTAL_EOF_CH0_INT_RAW_M  (BIT(8))
#define DMA_OUT_TOTAL_EOF_CH0_INT_RAW_V  0x1
#define DMA_OUT_TOTAL_EOF_CH0_INT_RAW_S  8
/* DMA_IN_DSCR_EMPTY_CH0_INT_RAW:R/WTC/SS；位位置：[7]；默认值：1’b0；*/
/*描述：当内联指向的Rx缓冲区已满且接收数据未完成，但Rx通道0没有更多内联时，原始中断位变为高电平。*/
#define DMA_IN_DSCR_EMPTY_CH0_INT_RAW  (BIT(7))
#define DMA_IN_DSCR_EMPTY_CH0_INT_RAW_M  (BIT(7))
#define DMA_IN_DSCR_EMPTY_CH0_INT_RAW_V  0x1
#define DMA_IN_DSCR_EMPTY_CH0_INT_RAW_S  7
/* DMA_OUT_DSCR_ERR_CH0_INT_RAW:R/WTC/SS；位位置：[6]；默认值：1’b0；*/
/*描述：当检测到包括所有者错误在内的Tx信道0的outlink描述符的第二个和第三个字错误时，原始中断位变为高电平。*/
#define DMA_OUT_DSCR_ERR_CH0_INT_RAW  (BIT(6))
#define DMA_OUT_DSCR_ERR_CH0_INT_RAW_M  (BIT(6))
#define DMA_OUT_DSCR_ERR_CH0_INT_RAW_V  0x1
#define DMA_OUT_DSCR_ERR_CH0_INT_RAW_S  6
/* DMA_IN_DSCR_ERR_CH0_INT_RAW:R/WTC/SS；位位置：[5]；默认值：1’b0；*/
/*描述：当检测到内联描述符错误时，原始中断位变为高电平，包括所有者错误Rx通道0的内联描述符的第二个和第三个字错误。*/
#define DMA_IN_DSCR_ERR_CH0_INT_RAW  (BIT(5))
#define DMA_IN_DSCR_ERR_CH0_INT_RAW_M  (BIT(5))
#define DMA_IN_DSCR_ERR_CH0_INT_RAW_V  0x1
#define DMA_IN_DSCR_ERR_CH0_INT_RAW_S  5
/* DMA_OUT_EOF_CH0_INT_RAW:R/WTC/SS；位位置：[4]；默认值：1’b0；*/
/*描述：当从Tx信道0的存储器中读取了一个输出描述符所指向的最后一个数据时，原始中断位变为高电平。*/
#define DMA_OUT_EOF_CH0_INT_RAW  (BIT(4))
#define DMA_OUT_EOF_CH0_INT_RAW_M  (BIT(4))
#define DMA_OUT_EOF_CH0_INT_RAW_V  0x1
#define DMA_OUT_EOF_CH0_INT_RAW_S  4
/* DMA_OUT_DONE_CH0_INT_RAW:R/WTC/SS；位位置：[3]；默认值：1’b0；*/
/*描述：当一个输出描述符所指向的最后一个数据已传输到Tx信道0的外围设备时，原始中断位变为高电平。*/
#define DMA_OUT_DONE_CH0_INT_RAW  (BIT(3))
#define DMA_OUT_DONE_CH0_INT_RAW_M  (BIT(3))
#define DMA_OUT_DONE_CH0_INT_RAW_V  0x1
#define DMA_OUT_DONE_CH0_INT_RAW_S  3
/* DMA_IN_ERR_EOF_CH0_INT_RAW:R/WTC/SS；位位置：[2]；默认值：1’b0；*/
/*描述：当仅在外围设备为UHCI0用于Rx信道0的情况下检测到数据错误时，原始中断位变为高电平。对于其他外围设备，保留此原始中断。*/
#define DMA_IN_ERR_EOF_CH0_INT_RAW  (BIT(2))
#define DMA_IN_ERR_EOF_CH0_INT_RAW_M  (BIT(2))
#define DMA_IN_ERR_EOF_CH0_INT_RAW_V  0x1
#define DMA_IN_ERR_EOF_CH0_INT_RAW_S  2
/* DMA_IN_SUC_EOF_CH0_INT_RAW:R/WTC/SS；位位置：[1]；默认值：1’b0；*/
/*描述：当接收到Rx信道0的一个内联描述符指向的最后一个数据时，原始中断位变为高电平。对于UHCI0，当接收到一个内联描述符指向的最后数据且未检测到Rx通道0的数据错误时，原始断开位变为低电平。*/
#define DMA_IN_SUC_EOF_CH0_INT_RAW  (BIT(1))
#define DMA_IN_SUC_EOF_CH0_INT_RAW_M  (BIT(1))
#define DMA_IN_SUC_EOF_CH0_INT_RAW_V  0x1
#define DMA_IN_SUC_EOF_CH0_INT_RAW_S  1
/* DMA_IN_DONE_CH0_INT_RAW:R/WTC/SS；位位置：[0]；默认值：1’b0；*/
/*描述：当接收到Rx通道0的一个内联描述符所指向的最后一个数据时，原始中断位变为高电平。*/
#define DMA_IN_DONE_CH0_INT_RAW  (BIT(0))
#define DMA_IN_DONE_CH0_INT_RAW_M  (BIT(0))
#define DMA_IN_DONE_CH0_INT_RAW_V  0x1
#define DMA_IN_DONE_CH0_INT_RAW_S  0

#define DMA_INT_ST_CH0_REG          (DR_REG_GDMA_BASE + 0x004)
/* DMA_OUTFIFO_UDF_CH0_INT_ST:RO；位位置：[12]；默认值：1’b0；*/
/*description:OUTFIFO_UDF_L1_CH_INT中断的原始中断状态位。*/
#define DMA_OUTFIFO_UDF_CH0_INT_ST  (BIT(12))
#define DMA_OUTFIFO_UDF_CH0_INT_ST_M  (BIT(12))
#define DMA_OUTFIFO_UDF_CH0_INT_ST_V  0x1
#define DMA_OUTFIFO_UDF_CH0_INT_ST_S  12
/* DMA_OUTFIFO_off_CH0_INT_ST:RO；位位置：[11]；默认值：1’b0；*/
/*description:OUTFIFO_OVF_L1_CH_INT中断的原始中断状态位。*/
#define DMA_OUTFIFO_OVF_CH0_INT_ST  (BIT(11))
#define DMA_OUTFIFO_OVF_CH0_INT_ST_M  (BIT(11))
#define DMA_OUTFIFO_OVF_CH0_INT_ST_V  0x1
#define DMA_OUTFIFO_OVF_CH0_INT_ST_S  11
/* DMA_INFIFO_UDF_CH0_INT_ST:RO；位位置：[10]；默认值：1’b0；*/
/*description:INFIFO_UDF_L1_CH_INT中断的原始中断状态位。*/
#define DMA_INFIFO_UDF_CH0_INT_ST  (BIT(10))
#define DMA_INFIFO_UDF_CH0_INT_ST_M  (BIT(10))
#define DMA_INFIFO_UDF_CH0_INT_ST_V  0x1
#define DMA_INFIFO_UDF_CH0_INT_ST_S  10
/* DMA_INFIFO_off_CH0_INT_ST:RO；位位置：[9]；默认值：1’b0；*/
/*description:INFIFO_OVF_L1_CH_INT中断的原始中断状态位。*/
#define DMA_INFIFO_OVF_CH0_INT_ST  (BIT(9))
#define DMA_INFIFO_OVF_CH0_INT_ST_M  (BIT(9))
#define DMA_INFIFO_OVF_CH0_INT_ST_V  0x1
#define DMA_INFIFO_OVF_CH0_INT_ST_S  9
/* DMA_OUT_TOTAL_EOF_CH0_INT_ST:RO；位位置：[8]；默认值：1’b0；*/
/*description:OUT_TOTAL_EOF_CH_INT中断的原始中断状态位。*/
#define DMA_OUT_TOTAL_EOF_CH0_INT_ST  (BIT(8))
#define DMA_OUT_TOTAL_EOF_CH0_INT_ST_M  (BIT(8))
#define DMA_OUT_TOTAL_EOF_CH0_INT_ST_V  0x1
#define DMA_OUT_TOTAL_EOF_CH0_INT_ST_S  8
/* DMA_IN_DSCR_EMPTY_CH0_INT_ST:RO；位位置：[7]；默认值：1’b0；*/
/*description:IN_DSCR_EMPTY_CH_INT中断的原始中断状态位。*/
#define DMA_IN_DSCR_EMPTY_CH0_INT_ST  (BIT(7))
#define DMA_IN_DSCR_EMPTY_CH0_INT_ST_M  (BIT(7))
#define DMA_IN_DSCR_EMPTY_CH0_INT_ST_V  0x1
#define DMA_IN_DSCR_EMPTY_CH0_INT_ST_S  7
/* DMA_OUT_DSCR_ERR_CH0_INT_ST:RO；位位置：[6]；默认值：1’b0；*/
/*description:OUT_DSCR_ERR_CH_INT中断的原始中断状态位。*/
#define DMA_OUT_DSCR_ERR_CH0_INT_ST  (BIT(6))
#define DMA_OUT_DSCR_ERR_CH0_INT_ST_M  (BIT(6))
#define DMA_OUT_DSCR_ERR_CH0_INT_ST_V  0x1
#define DMA_OUT_DSCR_ERR_CH0_INT_ST_S  6
/* DMA_IN_DSCR_ERR_CH0_INT_ST:RO；位位置：[5]；默认值：1’b0；*/
/*description:IN_DSCR_ERR_CH_INT中断的原始中断状态位。*/
#define DMA_IN_DSCR_ERR_CH0_INT_ST  (BIT(5))
#define DMA_IN_DSCR_ERR_CH0_INT_ST_M  (BIT(5))
#define DMA_IN_DSCR_ERR_CH0_INT_ST_V  0x1
#define DMA_IN_DSCR_ERR_CH0_INT_ST_S  5
/* DMA_OUT_EOF_CH0_INT_ST:RO；位位置：[4]；默认值：1’b0；*/
/*description:OUT_EOF_CH_INT中断的原始中断状态位。*/
#define DMA_OUT_EOF_CH0_INT_ST  (BIT(4))
#define DMA_OUT_EOF_CH0_INT_ST_M  (BIT(4))
#define DMA_OUT_EOF_CH0_INT_ST_V  0x1
#define DMA_OUT_EOF_CH0_INT_ST_S  4
/* DMA_OUT_DONE_CH0_INT_ST:RO；位位置：[3]；默认值：1’b0；*/
/*description:OUT_DONE_CH_INT中断的原始中断状态位。*/
#define DMA_OUT_DONE_CH0_INT_ST  (BIT(3))
#define DMA_OUT_DONE_CH0_INT_ST_M  (BIT(3))
#define DMA_OUT_DONE_CH0_INT_ST_V  0x1
#define DMA_OUT_DONE_CH0_INT_ST_S  3
/* DMA_IN_ERR_EOF_CH0_INT_ST:RO；位位置：[2]；默认值：1’b0；*/
/*description:IN_ERR_EOF_CH_INT中断的原始中断状态位。*/
#define DMA_IN_ERR_EOF_CH0_INT_ST  (BIT(2))
#define DMA_IN_ERR_EOF_CH0_INT_ST_M  (BIT(2))
#define DMA_IN_ERR_EOF_CH0_INT_ST_V  0x1
#define DMA_IN_ERR_EOF_CH0_INT_ST_S  2
/* DMA_IN_SUC_EOF_CH0_INT_ST:RO；位位置：[1]；默认值：1’b0；*/
/*description:IN_SUC_EOF_CH_INT中断的原始中断状态位。*/
#define DMA_IN_SUC_EOF_CH0_INT_ST  (BIT(1))
#define DMA_IN_SUC_EOF_CH0_INT_ST_M  (BIT(1))
#define DMA_IN_SUC_EOF_CH0_INT_ST_V  0x1
#define DMA_IN_SUC_EOF_CH0_INT_ST_S  1
/* DMA_IN_DONE_CH0_INT_ST:RO；位位置：[0]；默认值：1’b0；*/
/*description:IN_DONE_CH_INT中断的原始中断状态位。*/
#define DMA_IN_DONE_CH0_INT_ST  (BIT(0))
#define DMA_IN_DONE_CH0_INT_ST_M  (BIT(0))
#define DMA_IN_DONE_CH0_INT_ST_V  0x1
#define DMA_IN_DONE_CH0_INT_ST_S  0

#define DMA_INT_ENA_CH0_REG          (DR_REG_GDMA_BASE + 0x008)
/* DMA_OUTFIFO_UDF_CH0_INT_ENA:R/W；位位置：[12]；默认值：1’b0；*/
/*description:OUTFIFO_UDF_L1_CH_INT中断的中断启用位。*/
#define DMA_OUTFIFO_UDF_CH0_INT_ENA  (BIT(12))
#define DMA_OUTFIFO_UDF_CH0_INT_ENA_M  (BIT(12))
#define DMA_OUTFIFO_UDF_CH0_INT_ENA_V  0x1
#define DMA_OUTFIFO_UDF_CH0_INT_ENA_S  12
/* DMA_OUTFIFO_off_CH0_INT_ENA:R/W；位位置：[11]；默认值：1’b0；*/
/*description:OUTFIFO_OVF_L1_CH_INT中断的中断启用位。*/
#define DMA_OUTFIFO_OVF_CH0_INT_ENA  (BIT(11))
#define DMA_OUTFIFO_OVF_CH0_INT_ENA_M  (BIT(11))
#define DMA_OUTFIFO_OVF_CH0_INT_ENA_V  0x1
#define DMA_OUTFIFO_OVF_CH0_INT_ENA_S  11
/* DMA_INFIFO_UDF_CH0_INT_ENA:R/W；位位置：[10]；默认值：1’b0；*/
/*description:INFIFO_UDF_L1_CH_INT中断的中断启用位。*/
#define DMA_INFIFO_UDF_CH0_INT_ENA  (BIT(10))
#define DMA_INFIFO_UDF_CH0_INT_ENA_M  (BIT(10))
#define DMA_INFIFO_UDF_CH0_INT_ENA_V  0x1
#define DMA_INFIFO_UDF_CH0_INT_ENA_S  10
/* DMA_INFIFO_off_CH0_INT_ENA:R/W；位位置：[9]；默认值：1’b0；*/
/*description:INFIFO_OVF_L1_CH_INT中断的中断启用位。*/
#define DMA_INFIFO_OVF_CH0_INT_ENA  (BIT(9))
#define DMA_INFIFO_OVF_CH0_INT_ENA_M  (BIT(9))
#define DMA_INFIFO_OVF_CH0_INT_ENA_V  0x1
#define DMA_INFIFO_OVF_CH0_INT_ENA_S  9
/* DMA_OUT_TOTAL_EOF_CH0_INT_ENA:R/W；位位置：[8]；默认值：1’b0；*/
/*description:OUT_TOTAL_EOF_CH_INT中断的中断启用位。*/
#define DMA_OUT_TOTAL_EOF_CH0_INT_ENA  (BIT(8))
#define DMA_OUT_TOTAL_EOF_CH0_INT_ENA_M  (BIT(8))
#define DMA_OUT_TOTAL_EOF_CH0_INT_ENA_V  0x1
#define DMA_OUT_TOTAL_EOF_CH0_INT_ENA_S  8
/* DMA_IN_DSCR_EMPTY_CH0_INT_ENA:R/W；位位置：[7]；默认值：1’b0；*/
/*description:IN_DSCR_EMPTY_CH_INT中断的中断启用位。*/
#define DMA_IN_DSCR_EMPTY_CH0_INT_ENA  (BIT(7))
#define DMA_IN_DSCR_EMPTY_CH0_INT_ENA_M  (BIT(7))
#define DMA_IN_DSCR_EMPTY_CH0_INT_ENA_V  0x1
#define DMA_IN_DSCR_EMPTY_CH0_INT_ENA_S  7
/* DMA_OUT_DSCR_ERR_CH0_INT_ENA:R/W；位位置：[6]；默认值：1’b0；*/
/*description:OUT_DSCR_ERR_CH_INT中断的中断启用位。*/
#define DMA_OUT_DSCR_ERR_CH0_INT_ENA  (BIT(6))
#define DMA_OUT_DSCR_ERR_CH0_INT_ENA_M  (BIT(6))
#define DMA_OUT_DSCR_ERR_CH0_INT_ENA_V  0x1
#define DMA_OUT_DSCR_ERR_CH0_INT_ENA_S  6
/* DMA_IN_DSCR_ERR_CH0_INT_ENA:R/W；位位置：[5]；默认值：1’b0；*/
/*description:IN_DSCR_ERR_CH_INT中断的中断启用位。*/
#define DMA_IN_DSCR_ERR_CH0_INT_ENA  (BIT(5))
#define DMA_IN_DSCR_ERR_CH0_INT_ENA_M  (BIT(5))
#define DMA_IN_DSCR_ERR_CH0_INT_ENA_V  0x1
#define DMA_IN_DSCR_ERR_CH0_INT_ENA_S  5
/* DMA_OUT_EOF_CH0_INT_ENA:R/W；位位置：[4]；默认值：1’b0；*/
/*description:OUT_EOF_CH_INT中断的中断启用位。*/
#define DMA_OUT_EOF_CH0_INT_ENA  (BIT(4))
#define DMA_OUT_EOF_CH0_INT_ENA_M  (BIT(4))
#define DMA_OUT_EOF_CH0_INT_ENA_V  0x1
#define DMA_OUT_EOF_CH0_INT_ENA_S  4
/* DMA_OUT_DONE_CH0_INT_ENA:R/W；位位置：[3]；默认值：1’b0；*/
/*description:OUT_DONE_CH_INT中断的中断启用位。*/
#define DMA_OUT_DONE_CH0_INT_ENA  (BIT(3))
#define DMA_OUT_DONE_CH0_INT_ENA_M  (BIT(3))
#define DMA_OUT_DONE_CH0_INT_ENA_V  0x1
#define DMA_OUT_DONE_CH0_INT_ENA_S  3
/* DMA_IN_ERR_EOF_CH0_INT_ENA:R/W；位位置：[2]；默认值：1’b0；*/
/*description:IN_ERR_EOF_CH_INT中断的中断启用位。*/
#define DMA_IN_ERR_EOF_CH0_INT_ENA  (BIT(2))
#define DMA_IN_ERR_EOF_CH0_INT_ENA_M  (BIT(2))
#define DMA_IN_ERR_EOF_CH0_INT_ENA_V  0x1
#define DMA_IN_ERR_EOF_CH0_INT_ENA_S  2
/* DMA_IN_SUC_EOF_CH0_INT_ENA:R/W；位位置：[1]；默认值：1’b0；*/
/*description:IN_SUC_EOF_CH_INT中断的中断启用位。*/
#define DMA_IN_SUC_EOF_CH0_INT_ENA  (BIT(1))
#define DMA_IN_SUC_EOF_CH0_INT_ENA_M  (BIT(1))
#define DMA_IN_SUC_EOF_CH0_INT_ENA_V  0x1
#define DMA_IN_SUC_EOF_CH0_INT_ENA_S  1
/* DMA_IN_DONE_CH0_INT_ENA:R/W；位位置：[0]；默认值：1’b0；*/
/*description:IN_DONE_CH_INT中断的中断启用位。*/
#define DMA_IN_DONE_CH0_INT_ENA  (BIT(0))
#define DMA_IN_DONE_CH0_INT_ENA_M  (BIT(0))
#define DMA_IN_DONE_CH0_INT_ENA_V  0x1
#define DMA_IN_DONE_CH0_INT_ENA_S  0

#define DMA_INT_CLR_CH0_REG          (DR_REG_GDMA_BASE + 0x00C)
/* DMA_OUTFIFO_UDF_CH0_INT_CLR:WT；位位置：[12]；默认值：1’b0；*/
/*description:设置此位以清除OUTFIFO_UDF_L1_CH_INT中断。*/
#define DMA_OUTFIFO_UDF_CH0_INT_CLR  (BIT(12))
#define DMA_OUTFIFO_UDF_CH0_INT_CLR_M  (BIT(12))
#define DMA_OUTFIFO_UDF_CH0_INT_CLR_V  0x1
#define DMA_OUTFIFO_UDF_CH0_INT_CLR_S  12
/* DMA_OUTFIFO_off_CH0_INT_CLR:WT；位位置：[11]；默认值：1’b0；*/
/*description:设置此位以清除OUTFIFO_OVF_L1_CH_INT中断。*/
#define DMA_OUTFIFO_OVF_CH0_INT_CLR  (BIT(11))
#define DMA_OUTFIFO_OVF_CH0_INT_CLR_M  (BIT(11))
#define DMA_OUTFIFO_OVF_CH0_INT_CLR_V  0x1
#define DMA_OUTFIFO_OVF_CH0_INT_CLR_S  11
/* DMA_INFIFO_UDF_CH0_INT_CLR:WT；位位置：[10]；默认值：1’b0；*/
/*description:设置此位以清除INFIFO_UDF_L1_CH_INT中断。*/
#define DMA_INFIFO_UDF_CH0_INT_CLR  (BIT(10))
#define DMA_INFIFO_UDF_CH0_INT_CLR_M  (BIT(10))
#define DMA_INFIFO_UDF_CH0_INT_CLR_V  0x1
#define DMA_INFIFO_UDF_CH0_INT_CLR_S  10
/* DMA_INFIFO_off_CH0_INT_CLR:WT；位位置：[9]；默认值：1’b0；*/
/*description:设置此位以清除INFIFO_OVF_L1_CH_INT中断。*/
#define DMA_INFIFO_OVF_CH0_INT_CLR  (BIT(9))
#define DMA_INFIFO_OVF_CH0_INT_CLR_M  (BIT(9))
#define DMA_INFIFO_OVF_CH0_INT_CLR_V  0x1
#define DMA_INFIFO_OVF_CH0_INT_CLR_S  9
/* DMA_OUT_TOTAL_EOF_CH0_INT_CLR:WT；位位置：[8]；默认值：1’b0；*/
/*description:设置此位以清除OUT_TOTAL_EOF_CH_INT中断。*/
#define DMA_OUT_TOTAL_EOF_CH0_INT_CLR  (BIT(8))
#define DMA_OUT_TOTAL_EOF_CH0_INT_CLR_M  (BIT(8))
#define DMA_OUT_TOTAL_EOF_CH0_INT_CLR_V  0x1
#define DMA_OUT_TOTAL_EOF_CH0_INT_CLR_S  8
/* DMA_IN_DSCR_EMPTY_CH0_INT_CLR:WT；位位置：[7]；默认值：1’b0；*/
/*description:设置此位以清除IN_DSCR_EMPTY_CH_INT中断。*/
#define DMA_IN_DSCR_EMPTY_CH0_INT_CLR  (BIT(7))
#define DMA_IN_DSCR_EMPTY_CH0_INT_CLR_M  (BIT(7))
#define DMA_IN_DSCR_EMPTY_CH0_INT_CLR_V  0x1
#define DMA_IN_DSCR_EMPTY_CH0_INT_CLR_S  7
/* DMA_OUT_DSCR_ERR_CH0_INT_CLR:WT；位位置：[6]；默认值：1’b0；*/
/*description:设置此位以清除OUT_DSCR_ERR_CH_INT中断。*/
#define DMA_OUT_DSCR_ERR_CH0_INT_CLR  (BIT(6))
#define DMA_OUT_DSCR_ERR_CH0_INT_CLR_M  (BIT(6))
#define DMA_OUT_DSCR_ERR_CH0_INT_CLR_V  0x1
#define DMA_OUT_DSCR_ERR_CH0_INT_CLR_S  6
/* DMA_IN_DSCR_ERR_CH0_INT_CLR:WT；位位置：[5]；默认值：1’b0；*/
/*description:设置此位以清除IN_DSCR_ERR_CH_INT中断。*/
#define DMA_IN_DSCR_ERR_CH0_INT_CLR  (BIT(5))
#define DMA_IN_DSCR_ERR_CH0_INT_CLR_M  (BIT(5))
#define DMA_IN_DSCR_ERR_CH0_INT_CLR_V  0x1
#define DMA_IN_DSCR_ERR_CH0_INT_CLR_S  5
/* DMA_OUT_EOF_CH0_INT_CLR:WT；位位置：[4]；默认值：1’b0；*/
/*description:设置此位以清除OUT_EOF_CH_INT中断。*/
#define DMA_OUT_EOF_CH0_INT_CLR  (BIT(4))
#define DMA_OUT_EOF_CH0_INT_CLR_M  (BIT(4))
#define DMA_OUT_EOF_CH0_INT_CLR_V  0x1
#define DMA_OUT_EOF_CH0_INT_CLR_S  4
/* DMA_OUT_DONE_CH0_INT_CLR:WT；位位置：[3]；默认值：1’b0；*/
/*description:设置此位以清除OUT_DONE_CH_INT中断。*/
#define DMA_OUT_DONE_CH0_INT_CLR  (BIT(3))
#define DMA_OUT_DONE_CH0_INT_CLR_M  (BIT(3))
#define DMA_OUT_DONE_CH0_INT_CLR_V  0x1
#define DMA_OUT_DONE_CH0_INT_CLR_S  3
/* DMA_IN_ERR_EOF_CH0_INT_CLR:WT；位位置：[2]；默认值：1’b0；*/
/*description:设置此位以清除IN_ERR_EOF_CH_INT中断。*/
#define DMA_IN_ERR_EOF_CH0_INT_CLR  (BIT(2))
#define DMA_IN_ERR_EOF_CH0_INT_CLR_M  (BIT(2))
#define DMA_IN_ERR_EOF_CH0_INT_CLR_V  0x1
#define DMA_IN_ERR_EOF_CH0_INT_CLR_S  2
/* DMA_IN_SUC_EOF_CH0_INT_CLR:WT；位位置：[1]；默认值：1’b0；*/
/*description:设置此位以清除IN_SUC_EOF_CH_INT中断。*/
#define DMA_IN_SUC_EOF_CH0_INT_CLR  (BIT(1))
#define DMA_IN_SUC_EOF_CH0_INT_CLR_M  (BIT(1))
#define DMA_IN_SUC_EOF_CH0_INT_CLR_V  0x1
#define DMA_IN_SUC_EOF_CH0_INT_CLR_S  1
/* DMA_IN_DONE_CH0_INT_CLR:WT；位位置：[0]；默认值：1’b0；*/
/*description:设置此位以清除IN_DONE_CH_INT中断。*/
#define DMA_IN_DONE_CH0_INT_CLR  (BIT(0))
#define DMA_IN_DONE_CH0_INT_CLR_M  (BIT(0))
#define DMA_IN_DONE_CH0_INT_CLR_V  0x1
#define DMA_IN_DONE_CH0_INT_CLR_S  0

#define DMA_INT_RAW_CH1_REG          (DR_REG_GDMA_BASE + 0x010)
/* DMA_OUTFIFO_UDF_CH1_INT_RAW:R/WTC/SS；位位置：[12]；默认值：1’b0；*/
/*描述：当Tx信道1的1级fifo下溢时，此原始中断位变为高电平。*/
#define DMA_OUTFIFO_UDF_CH1_INT_RAW  (BIT(12))
#define DMA_OUTFIFO_UDF_CH1_INT_RAW_M  (BIT(12))
#define DMA_OUTFIFO_UDF_CH1_INT_RAW_V  0x1
#define DMA_OUTFIFO_UDF_CH1_INT_RAW_S  12
/* DMA_OUTFIFO_off_CH1_INT_RAW:R/WTC/SS；位位置：[11]；默认值：1’b0；*/
/*描述：当Tx信道1的1级fifo溢出时，此原始中断位变为高电平。*/
#define DMA_OUTFIFO_OVF_CH1_INT_RAW  (BIT(11))
#define DMA_OUTFIFO_OVF_CH1_INT_RAW_M  (BIT(11))
#define DMA_OUTFIFO_OVF_CH1_INT_RAW_V  0x1
#define DMA_OUTFIFO_OVF_CH1_INT_RAW_S  11
/* DMA_INFIFO_UDF_CH1_INT_RAW:R/WTC/SS；位位置：[10]；默认值：1’b0；*/
/*描述：当Rx通道1的1级fifo下溢时，此原始中断位变为高电平。*/
#define DMA_INFIFO_UDF_CH1_INT_RAW  (BIT(10))
#define DMA_INFIFO_UDF_CH1_INT_RAW_M  (BIT(10))
#define DMA_INFIFO_UDF_CH1_INT_RAW_V  0x1
#define DMA_INFIFO_UDF_CH1_INT_RAW_S  10
/* DMA_INFIFO_off_CH1_INT_RAW:R/WTC/SS；位位置：[9]；默认值：1’b0；*/
/*描述：当Rx通道1的1级fifo溢出时，此原始中断位变为高电平。*/
#define DMA_INFIFO_OVF_CH1_INT_RAW  (BIT(9))
#define DMA_INFIFO_OVF_CH1_INT_RAW_M  (BIT(9))
#define DMA_INFIFO_OVF_CH1_INT_RAW_V  0x1
#define DMA_INFIFO_OVF_CH1_INT_RAW_S  9
/* DMA_OUT_TOTAL_EOF_CH1_INT_RAW:R/WTC/SS；位位置：[8]；默认值：1’b0；*/
/*描述：当对应于Tx信道1的输出链接（包括一个链路描述符或几个链路描述符）的数据被发送出去时，原始中断位变为高电平。*/
#define DMA_OUT_TOTAL_EOF_CH1_INT_RAW  (BIT(8))
#define DMA_OUT_TOTAL_EOF_CH1_INT_RAW_M  (BIT(8))
#define DMA_OUT_TOTAL_EOF_CH1_INT_RAW_V  0x1
#define DMA_OUT_TOTAL_EOF_CH1_INT_RAW_S  8
/* DMA_IN_DSCR_EMPTY_CH1_INT_RAW:R/WTC/SS；位位置：[7]；默认值：1’b0；*/
/*描述：当内联指向的Rx缓冲区已满且接收数据未完成但Rx通道1没有更多内联时，原始中断位变为高电平。*/
#define DMA_IN_DSCR_EMPTY_CH1_INT_RAW  (BIT(7))
#define DMA_IN_DSCR_EMPTY_CH1_INT_RAW_M  (BIT(7))
#define DMA_IN_DSCR_EMPTY_CH1_INT_RAW_V  0x1
#define DMA_IN_DSCR_EMPTY_CH1_INT_RAW_S  7
/* DMA_OUT_DSCR_ERR_CH1_INT_RAW:R/WTC/SS；位位置：[6]；默认值：1’b0；*/
/*描述：当检测到包括所有者错误在内的Tx信道1的outlink描述符的第二个和第三个字错误的outlink描述符错误时，原始中断位变为高电平。*/
#define DMA_OUT_DSCR_ERR_CH1_INT_RAW  (BIT(6))
#define DMA_OUT_DSCR_ERR_CH1_INT_RAW_M  (BIT(6))
#define DMA_OUT_DSCR_ERR_CH1_INT_RAW_V  0x1
#define DMA_OUT_DSCR_ERR_CH1_INT_RAW_S  6
/* DMA_IN_DSCR_ERR_CH1_INT_RAW:R/WTC/SS；位位置：[5]；默认值：1’b0；*/
/*描述：当检测到内联描述符错误（包括所有者错误）时，原始中断位变为高电平，其中包括Rx通道1的内联描述符的第二个和第三个字错误。*/
#define DMA_IN_DSCR_ERR_CH1_INT_RAW  (BIT(5))
#define DMA_IN_DSCR_ERR_CH1_INT_RAW_M  (BIT(5))
#define DMA_IN_DSCR_ERR_CH1_INT_RAW_V  0x1
#define DMA_IN_DSCR_ERR_CH1_INT_RAW_S  5
/* DMA_OUT_EOF_CH1_INT_RAW:R/WTC/SS；位位置：[4]；默认值：1’b0；*/
/*描述：当从Tx信道1的存储器中读取了一个输出描述符所指向的最后一个数据时，原始中断位变为高电平。*/
#define DMA_OUT_EOF_CH1_INT_RAW  (BIT(4))
#define DMA_OUT_EOF_CH1_INT_RAW_M  (BIT(4))
#define DMA_OUT_EOF_CH1_INT_RAW_V  0x1
#define DMA_OUT_EOF_CH1_INT_RAW_S  4
/* DMA_OUT_DONE_CH1_INT_RAW:R/WTC/SS；位位置：[3]；默认值：1’b0；*/
/*描述：当一个输出描述符所指向的最后一个数据已传输到Tx信道1的外围设备时，原始中断位变为高电平。*/
#define DMA_OUT_DONE_CH1_INT_RAW  (BIT(3))
#define DMA_OUT_DONE_CH1_INT_RAW_M  (BIT(3))
#define DMA_OUT_DONE_CH1_INT_RAW_V  0x1
#define DMA_OUT_DONE_CH1_INT_RAW_S  3
/* DMA_IN_ERR_EOF_CH1_INT_RAW:R/WTC/SS；位位置：[2]；默认值：1’b0；*/
/*描述：当仅在外围设备为Rx信道1的UHCI0的情况下检测到数据错误时，原始中断位变为高电平。对于其他外围设备，保留此原始中断。*/
#define DMA_IN_ERR_EOF_CH1_INT_RAW  (BIT(2))
#define DMA_IN_ERR_EOF_CH1_INT_RAW_M  (BIT(2))
#define DMA_IN_ERR_EOF_CH1_INT_RAW_V  0x1
#define DMA_IN_ERR_EOF_CH1_INT_RAW_S  2
/* DMA_IN_SUC_EOF_CH1_INT_RAW:R/WTC/SS；位位置：[1]；默认值：1’b0；*/
/*描述：当接收到Rx信道1的一个内联描述符指向的最后一个数据时，原始中断位变为高电平。对于UHCI0，当接收到一个内联描述符指向的最后数据且未检测到Rx通道1的数据错误时，原始断开位变为低电平。*/
#define DMA_IN_SUC_EOF_CH1_INT_RAW  (BIT(1))
#define DMA_IN_SUC_EOF_CH1_INT_RAW_M  (BIT(1))
#define DMA_IN_SUC_EOF_CH1_INT_RAW_V  0x1
#define DMA_IN_SUC_EOF_CH1_INT_RAW_S  1
/* DMA_IN_DONE_CH1_INT_RAW:R/WTC/SS；位位置：[0]；默认值：1’b0；*/
/*描述：当接收到Rx通道1的一个内联描述符所指向的最后一个数据时，原始中断位变为高电平。*/
#define DMA_IN_DONE_CH1_INT_RAW  (BIT(0))
#define DMA_IN_DONE_CH1_INT_RAW_M  (BIT(0))
#define DMA_IN_DONE_CH1_INT_RAW_V  0x1
#define DMA_IN_DONE_CH1_INT_RAW_S  0

#define DMA_INT_ST_CH1_REG          (DR_REG_GDMA_BASE + 0x014)
/* DMA_OUTFIFO_UDF_CH1_INT_ST:RO；位位置：[12]；默认值：1’b0；*/
/*description:OUTFIFO_UDF_L1_CH_INT中断的原始中断状态位。*/
#define DMA_OUTFIFO_UDF_CH1_INT_ST  (BIT(12))
#define DMA_OUTFIFO_UDF_CH1_INT_ST_M  (BIT(12))
#define DMA_OUTFIFO_UDF_CH1_INT_ST_V  0x1
#define DMA_OUTFIFO_UDF_CH1_INT_ST_S  12
/* DMA_OUTFIFO_off_CH1_INT_ST:RO；位位置：[11]；默认值：1’b0；*/
/*description:OUTFIFO_OVF_L1_CH_INT中断的原始中断状态位。*/
#define DMA_OUTFIFO_OVF_CH1_INT_ST  (BIT(11))
#define DMA_OUTFIFO_OVF_CH1_INT_ST_M  (BIT(11))
#define DMA_OUTFIFO_OVF_CH1_INT_ST_V  0x1
#define DMA_OUTFIFO_OVF_CH1_INT_ST_S  11
/* DMA_INFIFO_UDF_CH1_INT_ST:RO；位位置：[10]；默认值：1’b0；*/
/*description:INFIFO_UDF_L1_CH_INT中断的原始中断状态位。*/
#define DMA_INFIFO_UDF_CH1_INT_ST  (BIT(10))
#define DMA_INFIFO_UDF_CH1_INT_ST_M  (BIT(10))
#define DMA_INFIFO_UDF_CH1_INT_ST_V  0x1
#define DMA_INFIFO_UDF_CH1_INT_ST_S  10
/* DMA_INFIFO_off_CH1_INT_ST:RO；位位置：[9]；默认值：1’b0；*/
/*description:INFIFO_OVF_L1_CH_INT中断的原始中断状态位。*/
#define DMA_INFIFO_OVF_CH1_INT_ST  (BIT(9))
#define DMA_INFIFO_OVF_CH1_INT_ST_M  (BIT(9))
#define DMA_INFIFO_OVF_CH1_INT_ST_V  0x1
#define DMA_INFIFO_OVF_CH1_INT_ST_S  9
/* DMA_OUT_TOTAL_EOF_CH1_INT_ST:RO；位位置：[8]；默认值：1’b0；*/
/*description:OUT_TOTAL_EOF_CH_INT中断的原始中断状态位。*/
#define DMA_OUT_TOTAL_EOF_CH1_INT_ST  (BIT(8))
#define DMA_OUT_TOTAL_EOF_CH1_INT_ST_M  (BIT(8))
#define DMA_OUT_TOTAL_EOF_CH1_INT_ST_V  0x1
#define DMA_OUT_TOTAL_EOF_CH1_INT_ST_S  8
/* DMA_IN_DSCR_EMPTY_CH1_INT_ST:RO；位位置：[7]；默认值：1’b0；*/
/*description:IN_DSCR_EMPTY_CH_INT中断的原始中断状态位。*/
#define DMA_IN_DSCR_EMPTY_CH1_INT_ST  (BIT(7))
#define DMA_IN_DSCR_EMPTY_CH1_INT_ST_M  (BIT(7))
#define DMA_IN_DSCR_EMPTY_CH1_INT_ST_V  0x1
#define DMA_IN_DSCR_EMPTY_CH1_INT_ST_S  7
/* DMA_OUT_DSCR_ERR_CH1_INT_ST:RO；位位置：[6]；默认值：1’b0；*/
/*description:OUT_DSCR_ERR_CH_INT中断的原始中断状态位。*/
#define DMA_OUT_DSCR_ERR_CH1_INT_ST  (BIT(6))
#define DMA_OUT_DSCR_ERR_CH1_INT_ST_M  (BIT(6))
#define DMA_OUT_DSCR_ERR_CH1_INT_ST_V  0x1
#define DMA_OUT_DSCR_ERR_CH1_INT_ST_S  6
/* DMA_IN_DSCR_ERR_CH1_INT_ST:RO；位位置：[5]；默认值：1’b0；*/
/*description:IN_DSCR_ERR_CH_INT中断的原始中断状态位。*/
#define DMA_IN_DSCR_ERR_CH1_INT_ST  (BIT(5))
#define DMA_IN_DSCR_ERR_CH1_INT_ST_M  (BIT(5))
#define DMA_IN_DSCR_ERR_CH1_INT_ST_V  0x1
#define DMA_IN_DSCR_ERR_CH1_INT_ST_S  5
/* DMA_OUT_EOF_CH1_INT_ST:RO；位位置：[4]；默认值：1’b0；*/
/*description:OUT_EOF_CH_INT中断的原始中断状态位。*/
#define DMA_OUT_EOF_CH1_INT_ST  (BIT(4))
#define DMA_OUT_EOF_CH1_INT_ST_M  (BIT(4))
#define DMA_OUT_EOF_CH1_INT_ST_V  0x1
#define DMA_OUT_EOF_CH1_INT_ST_S  4
/* DMA_OUT_DONE_CH1_INT_ST:RO；位位置：[3]；默认值：1’b0；*/
/*description:OUT_DONE_CH_INT中断的原始中断状态位。*/
#define DMA_OUT_DONE_CH1_INT_ST  (BIT(3))
#define DMA_OUT_DONE_CH1_INT_ST_M  (BIT(3))
#define DMA_OUT_DONE_CH1_INT_ST_V  0x1
#define DMA_OUT_DONE_CH1_INT_ST_S  3
/* DMA_IN_ERR_EOF_CH1_INT_ST:RO；位位置：[2]；默认值：1’b0；*/
/*description:IN_ERR_EOF_CH_INT中断的原始中断状态位。*/
#define DMA_IN_ERR_EOF_CH1_INT_ST  (BIT(2))
#define DMA_IN_ERR_EOF_CH1_INT_ST_M  (BIT(2))
#define DMA_IN_ERR_EOF_CH1_INT_ST_V  0x1
#define DMA_IN_ERR_EOF_CH1_INT_ST_S  2
/* DMA_IN_SUC_EOF_CH1_INT_ST:RO；位位置：[1]；默认值：1’b0；*/
/*description:IN_SUC_EOF_CH_INT中断的原始中断状态位。*/
#define DMA_IN_SUC_EOF_CH1_INT_ST  (BIT(1))
#define DMA_IN_SUC_EOF_CH1_INT_ST_M  (BIT(1))
#define DMA_IN_SUC_EOF_CH1_INT_ST_V  0x1
#define DMA_IN_SUC_EOF_CH1_INT_ST_S  1
/* DMA_IN_DONE_CH1_INT_ST:RO；位位置：[0]；默认值：1’b0；*/
/*description:IN_DONE_CH_INT中断的原始中断状态位。*/
#define DMA_IN_DONE_CH1_INT_ST  (BIT(0))
#define DMA_IN_DONE_CH1_INT_ST_M  (BIT(0))
#define DMA_IN_DONE_CH1_INT_ST_V  0x1
#define DMA_IN_DONE_CH1_INT_ST_S  0

#define DMA_INT_ENA_CH1_REG          (DR_REG_GDMA_BASE + 0x018)
/* DMA_OUTFIFO_UDF_CH1_INT_ENA:R/W；位位置：[12]；默认值：1’b0；*/
/*description:OUTFIFO_UDF_L1_CH_INT中断的中断启用位。*/
#define DMA_OUTFIFO_UDF_CH1_INT_ENA  (BIT(12))
#define DMA_OUTFIFO_UDF_CH1_INT_ENA_M  (BIT(12))
#define DMA_OUTFIFO_UDF_CH1_INT_ENA_V  0x1
#define DMA_OUTFIFO_UDF_CH1_INT_ENA_S  12
/* DMA_OUTFIFO_off_CH1_INT_ENA:R/W；位位置：[11]；默认值：1’b0；*/
/*description:OUTFIFO_OVF_L1_CH_INT中断的中断启用位。*/
#define DMA_OUTFIFO_OVF_CH1_INT_ENA  (BIT(11))
#define DMA_OUTFIFO_OVF_CH1_INT_ENA_M  (BIT(11))
#define DMA_OUTFIFO_OVF_CH1_INT_ENA_V  0x1
#define DMA_OUTFIFO_OVF_CH1_INT_ENA_S  11
/* DMA_INFIFO_UDF_CH1_INT_ENA:R/W；位位置：[10]；默认值：1’b0；*/
/*description:INFIFO_UDF_L1_CH_INT中断的中断启用位。*/
#define DMA_INFIFO_UDF_CH1_INT_ENA  (BIT(10))
#define DMA_INFIFO_UDF_CH1_INT_ENA_M  (BIT(10))
#define DMA_INFIFO_UDF_CH1_INT_ENA_V  0x1
#define DMA_INFIFO_UDF_CH1_INT_ENA_S  10
/* DMA_INFIFO_off_CH1_INT_ENA:R/W；位位置：[9]；默认值：1’b0；*/
/*description:INFIFO_OVF_L1_CH_INT中断的中断启用位。*/
#define DMA_INFIFO_OVF_CH1_INT_ENA  (BIT(9))
#define DMA_INFIFO_OVF_CH1_INT_ENA_M  (BIT(9))
#define DMA_INFIFO_OVF_CH1_INT_ENA_V  0x1
#define DMA_INFIFO_OVF_CH1_INT_ENA_S  9
/* DMA_OUT_TOTAL_EOF_CH1_INT_ENA:R/W；位位置：[8]；默认值：1’b0；*/
/*description:OUT_TOTAL_EOF_CH_INT中断的中断启用位。*/
#define DMA_OUT_TOTAL_EOF_CH1_INT_ENA  (BIT(8))
#define DMA_OUT_TOTAL_EOF_CH1_INT_ENA_M  (BIT(8))
#define DMA_OUT_TOTAL_EOF_CH1_INT_ENA_V  0x1
#define DMA_OUT_TOTAL_EOF_CH1_INT_ENA_S  8
/* DMA_IN_DSCR_EMPTY_CH1_INT_ENA:R/W；位位置：[7]；默认值：1’b0；*/
/*description:IN_DSCR_EMPTY_CH_INT中断的中断启用位。*/
#define DMA_IN_DSCR_EMPTY_CH1_INT_ENA  (BIT(7))
#define DMA_IN_DSCR_EMPTY_CH1_INT_ENA_M  (BIT(7))
#define DMA_IN_DSCR_EMPTY_CH1_INT_ENA_V  0x1
#define DMA_IN_DSCR_EMPTY_CH1_INT_ENA_S  7
/* DMA_OUT_DSCR_ERR_CH1_INT_ENA:R/W；位位置：[6]；默认值：1’b0；*/
/*description:OUT_DSCR_ERR_CH_INT中断的中断启用位。*/
#define DMA_OUT_DSCR_ERR_CH1_INT_ENA  (BIT(6))
#define DMA_OUT_DSCR_ERR_CH1_INT_ENA_M  (BIT(6))
#define DMA_OUT_DSCR_ERR_CH1_INT_ENA_V  0x1
#define DMA_OUT_DSCR_ERR_CH1_INT_ENA_S  6
/* DMA_IN_DSCR_ERR_CH1_INT_ENA:R/W；位位置：[5]；默认值：1’b0；*/
/*description:IN_DSCR_ERR_CH_INT中断的中断启用位。*/
#define DMA_IN_DSCR_ERR_CH1_INT_ENA  (BIT(5))
#define DMA_IN_DSCR_ERR_CH1_INT_ENA_M  (BIT(5))
#define DMA_IN_DSCR_ERR_CH1_INT_ENA_V  0x1
#define DMA_IN_DSCR_ERR_CH1_INT_ENA_S  5
/* DMA_OUT_EOF_CH1_INT_ENA:R/W；位位置：[4]；默认值：1’b0；*/
/*description:OUT_EOF_CH_INT中断的中断启用位。*/
#define DMA_OUT_EOF_CH1_INT_ENA  (BIT(4))
#define DMA_OUT_EOF_CH1_INT_ENA_M  (BIT(4))
#define DMA_OUT_EOF_CH1_INT_ENA_V  0x1
#define DMA_OUT_EOF_CH1_INT_ENA_S  4
/* DMA_OUT_DONE_CH1_INT_ENA:R/W；位位置：[3]；默认值：1’b0；*/
/*description:OUT_DONE_CH_INT中断的中断启用位。*/
#define DMA_OUT_DONE_CH1_INT_ENA  (BIT(3))
#define DMA_OUT_DONE_CH1_INT_ENA_M  (BIT(3))
#define DMA_OUT_DONE_CH1_INT_ENA_V  0x1
#define DMA_OUT_DONE_CH1_INT_ENA_S  3
/* DMA_IN_ERR_EOF_CH1_INT_ENA:R/W；位位置：[2]；默认值：1’b0；*/
/*description:IN_ERR_EOF_CH_INT中断的中断启用位。*/
#define DMA_IN_ERR_EOF_CH1_INT_ENA  (BIT(2))
#define DMA_IN_ERR_EOF_CH1_INT_ENA_M  (BIT(2))
#define DMA_IN_ERR_EOF_CH1_INT_ENA_V  0x1
#define DMA_IN_ERR_EOF_CH1_INT_ENA_S  2
/* DMA_IN_SUC_EOF_CH1_INT_ENA:R/W；位位置：[1]；默认值：1’b0；*/
/*description:IN_SUC_EOF_CH_INT中断的中断启用位。*/
#define DMA_IN_SUC_EOF_CH1_INT_ENA  (BIT(1))
#define DMA_IN_SUC_EOF_CH1_INT_ENA_M  (BIT(1))
#define DMA_IN_SUC_EOF_CH1_INT_ENA_V  0x1
#define DMA_IN_SUC_EOF_CH1_INT_ENA_S  1
/* DMA_IN_DONE_CH1_INT_ENA:R/W；位位置：[0]；默认值：1’b0；*/
/*description:IN_DONE_CH_INT中断的中断启用位。*/
#define DMA_IN_DONE_CH1_INT_ENA  (BIT(0))
#define DMA_IN_DONE_CH1_INT_ENA_M  (BIT(0))
#define DMA_IN_DONE_CH1_INT_ENA_V  0x1
#define DMA_IN_DONE_CH1_INT_ENA_S  0

#define DMA_INT_CLR_CH1_REG          (DR_REG_GDMA_BASE + 0x01C)
/* DMA_OUTFIFO_UDF_CH1_INT_CLR:WT；位位置：[12]；默认值：1’b0；*/
/*description:设置此位以清除OUTFIFO_UDF_L1_CH_INT中断。*/
#define DMA_OUTFIFO_UDF_CH1_INT_CLR  (BIT(12))
#define DMA_OUTFIFO_UDF_CH1_INT_CLR_M  (BIT(12))
#define DMA_OUTFIFO_UDF_CH1_INT_CLR_V  0x1
#define DMA_OUTFIFO_UDF_CH1_INT_CLR_S  12
/* DMA_OUTFIFO_off_CH1_INT_CLR:WT；位位置：[11]；默认值：1’b0；*/
/*description:设置此位以清除OUTFIFO_OVF_L1_CH_INT中断。*/
#define DMA_OUTFIFO_OVF_CH1_INT_CLR  (BIT(11))
#define DMA_OUTFIFO_OVF_CH1_INT_CLR_M  (BIT(11))
#define DMA_OUTFIFO_OVF_CH1_INT_CLR_V  0x1
#define DMA_OUTFIFO_OVF_CH1_INT_CLR_S  11
/* DMA_INFIFO_UDF_CH1_INT_CLR:WT；位位置：[10]；默认值：1’b0；*/
/*description:设置此位以清除INFIFO_UDF_L1_CH_INT中断。*/
#define DMA_INFIFO_UDF_CH1_INT_CLR  (BIT(10))
#define DMA_INFIFO_UDF_CH1_INT_CLR_M  (BIT(10))
#define DMA_INFIFO_UDF_CH1_INT_CLR_V  0x1
#define DMA_INFIFO_UDF_CH1_INT_CLR_S  10
/* DMA_INFIFO_off_CH1_INT_CLR:WT；位位置：[9]；默认值：1’b0；*/
/*description:设置此位以清除INFIFO_OVF_L1_CH_INT中断。*/
#define DMA_INFIFO_OVF_CH1_INT_CLR  (BIT(9))
#define DMA_INFIFO_OVF_CH1_INT_CLR_M  (BIT(9))
#define DMA_INFIFO_OVF_CH1_INT_CLR_V  0x1
#define DMA_INFIFO_OVF_CH1_INT_CLR_S  9
/* DMA_OUT_TOTAL_EOF_CH1_INT_CLR:WT；位位置：[8]；默认值：1’b0；*/
/*description:设置此位以清除OUT_TOTAL_EOF_CH_INT中断。*/
#define DMA_OUT_TOTAL_EOF_CH1_INT_CLR  (BIT(8))
#define DMA_OUT_TOTAL_EOF_CH1_INT_CLR_M  (BIT(8))
#define DMA_OUT_TOTAL_EOF_CH1_INT_CLR_V  0x1
#define DMA_OUT_TOTAL_EOF_CH1_INT_CLR_S  8
/* DMA_IN_DSCR_EMPTY_CH1_INT_CLR:WT；位位置：[7]；默认值：1’b0；*/
/*description:设置此位以清除IN_DSCR_EMPTY_CH_INT中断。*/
#define DMA_IN_DSCR_EMPTY_CH1_INT_CLR  (BIT(7))
#define DMA_IN_DSCR_EMPTY_CH1_INT_CLR_M  (BIT(7))
#define DMA_IN_DSCR_EMPTY_CH1_INT_CLR_V  0x1
#define DMA_IN_DSCR_EMPTY_CH1_INT_CLR_S  7
/* DMA_OUT_DSCR_ERR_CH1_INT_CLR:WT；位位置：[6]；默认值：1’b0；*/
/*description:设置此位以清除OUT_DSCR_ERR_CH_INT中断。*/
#define DMA_OUT_DSCR_ERR_CH1_INT_CLR  (BIT(6))
#define DMA_OUT_DSCR_ERR_CH1_INT_CLR_M  (BIT(6))
#define DMA_OUT_DSCR_ERR_CH1_INT_CLR_V  0x1
#define DMA_OUT_DSCR_ERR_CH1_INT_CLR_S  6
/* DMA_IN_DSCR_ERR_CH1_INT_CLR:WT；位位置：[5]；默认值：1’b0；*/
/*description:设置此位以清除IN_DSCR_ERR_CH_INT中断。*/
#define DMA_IN_DSCR_ERR_CH1_INT_CLR  (BIT(5))
#define DMA_IN_DSCR_ERR_CH1_INT_CLR_M  (BIT(5))
#define DMA_IN_DSCR_ERR_CH1_INT_CLR_V  0x1
#define DMA_IN_DSCR_ERR_CH1_INT_CLR_S  5
/* DMA_OUT_EOF_CH1_INT_CLR:WT；位位置：[4]；默认值：1’b0；*/
/*description:设置此位以清除OUT_EOF_CH_INT中断。*/
#define DMA_OUT_EOF_CH1_INT_CLR  (BIT(4))
#define DMA_OUT_EOF_CH1_INT_CLR_M  (BIT(4))
#define DMA_OUT_EOF_CH1_INT_CLR_V  0x1
#define DMA_OUT_EOF_CH1_INT_CLR_S  4
/* DMA_OUT_DONE_CH1_INT_CLR:WT；位位置：[3]；默认值：1’b0；*/
/*description:设置此位以清除OUT_DONE_CH_INT中断。*/
#define DMA_OUT_DONE_CH1_INT_CLR  (BIT(3))
#define DMA_OUT_DONE_CH1_INT_CLR_M  (BIT(3))
#define DMA_OUT_DONE_CH1_INT_CLR_V  0x1
#define DMA_OUT_DONE_CH1_INT_CLR_S  3
/* DMA_IN_ERR_EOF_CH1_INT_CLR:WT；位位置：[2]；默认值：1’b0；*/
/*description:设置此位以清除IN_ERR_EOF_CH_INT中断。*/
#define DMA_IN_ERR_EOF_CH1_INT_CLR  (BIT(2))
#define DMA_IN_ERR_EOF_CH1_INT_CLR_M  (BIT(2))
#define DMA_IN_ERR_EOF_CH1_INT_CLR_V  0x1
#define DMA_IN_ERR_EOF_CH1_INT_CLR_S  2
/* DMA_IN_SUC_EOF_CH1_INT_CLR:WT；位位置：[1]；默认值：1’b0；*/
/*description:设置此位以清除IN_SUC_EOF_CH_INT中断。*/
#define DMA_IN_SUC_EOF_CH1_INT_CLR  (BIT(1))
#define DMA_IN_SUC_EOF_CH1_INT_CLR_M  (BIT(1))
#define DMA_IN_SUC_EOF_CH1_INT_CLR_V  0x1
#define DMA_IN_SUC_EOF_CH1_INT_CLR_S  1
/* DMA_IN_DONE_CH1_INT_CLR:WT；位位置：[0]；默认值：1’b0；*/
/*description:设置此位以清除IN_DONE_CH_INT中断。*/
#define DMA_IN_DONE_CH1_INT_CLR  (BIT(0))
#define DMA_IN_DONE_CH1_INT_CLR_M  (BIT(0))
#define DMA_IN_DONE_CH1_INT_CLR_V  0x1
#define DMA_IN_DONE_CH1_INT_CLR_S  0

#define DMA_INT_RAW_CH2_REG          (DR_REG_GDMA_BASE + 0x020)
/* DMA_OUTFIFO_UDF_CH2_INT_RAW:R/WTC/SS；位位置：[12]；默认值：1’b0；*/
/*描述：当Tx信道2的1级fifo下溢时，此原始中断位变为高电平。*/
#define DMA_OUTFIFO_UDF_CH2_INT_RAW  (BIT(12))
#define DMA_OUTFIFO_UDF_CH2_INT_RAW_M  (BIT(12))
#define DMA_OUTFIFO_UDF_CH2_INT_RAW_V  0x1
#define DMA_OUTFIFO_UDF_CH2_INT_RAW_S  12
/* DMA_OUTFIFO_off_CH2_INT_RAW:R/WTC/SS；位位置：[11]；默认值：1’b0；*/
/*描述：当Tx信道2的1级fifo溢出时，此原始中断位变为高电平。*/
#define DMA_OUTFIFO_OVF_CH2_INT_RAW  (BIT(11))
#define DMA_OUTFIFO_OVF_CH2_INT_RAW_M  (BIT(11))
#define DMA_OUTFIFO_OVF_CH2_INT_RAW_V  0x1
#define DMA_OUTFIFO_OVF_CH2_INT_RAW_S  11
/* DMA_INFIFO_UDF_CH2_INT_RAW:R/WTC/SS；位位置：[10]；默认值：1’b0；*/
/*描述：当Rx通道2的1级fifo下溢时，此原始中断位变为高电平。*/
#define DMA_INFIFO_UDF_CH2_INT_RAW  (BIT(10))
#define DMA_INFIFO_UDF_CH2_INT_RAW_M  (BIT(10))
#define DMA_INFIFO_UDF_CH2_INT_RAW_V  0x1
#define DMA_INFIFO_UDF_CH2_INT_RAW_S  10
/* DMA_INFIFO_off_CH2_INT_RAW:R/WTC/SS；位位置：[9]；默认值：1’b0；*/
/*描述：当Rx通道2的1级fifo溢出时，此原始中断位变为高电平。*/
#define DMA_INFIFO_OVF_CH2_INT_RAW  (BIT(9))
#define DMA_INFIFO_OVF_CH2_INT_RAW_M  (BIT(9))
#define DMA_INFIFO_OVF_CH2_INT_RAW_V  0x1
#define DMA_INFIFO_OVF_CH2_INT_RAW_S  9
/* DMA_OUT_TOTAL_EOF_CH2_INT_RAW:R/WTC/SS；位位置：[8]；默认值：1’b0；*/
/*描述：当针对Tx信道2发送出与输出链接（包括一个链路描述符或几个链路描述符）相对应的数据时，原始中断位变为高电平。*/
#define DMA_OUT_TOTAL_EOF_CH2_INT_RAW  (BIT(8))
#define DMA_OUT_TOTAL_EOF_CH2_INT_RAW_M  (BIT(8))
#define DMA_OUT_TOTAL_EOF_CH2_INT_RAW_V  0x1
#define DMA_OUT_TOTAL_EOF_CH2_INT_RAW_S  8
/* DMA_IN_DSCR_EMPTY_CH2_INT_RAW:R/WTC/SS；位位置：[7]；默认值：1’b0；*/
/*描述：当内联指向的Rx缓冲区已满且接收数据未完成但Rx通道2没有更多内联时，原始中断位变为高电平。*/
#define DMA_IN_DSCR_EMPTY_CH2_INT_RAW  (BIT(7))
#define DMA_IN_DSCR_EMPTY_CH2_INT_RAW_M  (BIT(7))
#define DMA_IN_DSCR_EMPTY_CH2_INT_RAW_V  0x1
#define DMA_IN_DSCR_EMPTY_CH2_INT_RAW_S  7
/* DMA_OUT_DSCR_ERR_CH2_INT_RAW:R/WTC/SS；位位置：[6]；默认值：1’b0；*/
/*描述：当检测到包括所有者错误在内的Tx信道2的outlink描述符的第二和第三字错误时，原始中断位变为高电平。*/
#define DMA_OUT_DSCR_ERR_CH2_INT_RAW  (BIT(6))
#define DMA_OUT_DSCR_ERR_CH2_INT_RAW_M  (BIT(6))
#define DMA_OUT_DSCR_ERR_CH2_INT_RAW_V  0x1
#define DMA_OUT_DSCR_ERR_CH2_INT_RAW_S  6
/* DMA_IN_DSCR_ERR_CH2_INT_RAW:R/WTC/SS；位位置：[5]；默认值：1’b0；*/
/*描述：当检测到内联描述符错误时，原始中断位变为高电平，包括Rx通道2的内联描述符的所有者错误、第二个和第三个字错误。*/
#define DMA_IN_DSCR_ERR_CH2_INT_RAW  (BIT(5))
#define DMA_IN_DSCR_ERR_CH2_INT_RAW_M  (BIT(5))
#define DMA_IN_DSCR_ERR_CH2_INT_RAW_V  0x1
#define DMA_IN_DSCR_ERR_CH2_INT_RAW_S  5
/* DMA_OUT_EOF_CH2_INT_RAW:R/WTC/SS；位位置：[4]；默认值：1’b0；*/
/*描述：当从Tx信道2的存储器中读取了一个输出描述符所指向的最后一个数据时，原始中断位变为高电平。*/
#define DMA_OUT_EOF_CH2_INT_RAW  (BIT(4))
#define DMA_OUT_EOF_CH2_INT_RAW_M  (BIT(4))
#define DMA_OUT_EOF_CH2_INT_RAW_V  0x1
#define DMA_OUT_EOF_CH2_INT_RAW_S  4
/* DMA_OUT_DONE_CH2_INT_RAW:R/WTC/SS；位位置：[3]；默认值：1’b0；*/
/*描述：当一个输出描述符所指向的最后一个数据已传输到Tx信道2的外围设备时，原始中断位变为高电平。*/
#define DMA_OUT_DONE_CH2_INT_RAW  (BIT(3))
#define DMA_OUT_DONE_CH2_INT_RAW_M  (BIT(3))
#define DMA_OUT_DONE_CH2_INT_RAW_V  0x1
#define DMA_OUT_DONE_CH2_INT_RAW_S  3
/* DMA_IN_ERR_EOF_CH2_INT_RAW:R/WTC/SS；位位置：[2]；默认值：1’b0；*/
/*描述：当仅在外围设备为Rx信道2的UHCI0的情况下检测到数据错误时，原始中断位变为高电平。对于其他外围设备，保留此原始中断。*/
#define DMA_IN_ERR_EOF_CH2_INT_RAW  (BIT(2))
#define DMA_IN_ERR_EOF_CH2_INT_RAW_M  (BIT(2))
#define DMA_IN_ERR_EOF_CH2_INT_RAW_V  0x1
#define DMA_IN_ERR_EOF_CH2_INT_RAW_S  2
/* DMA_IN_SUC_EOF_CH2_INT_RAW:R/WTC/SS；位位置：[1]；默认值：1’b0；*/
/*描述：当接收到Rx信道2的一个内联描述符指向的最后一个数据时，原始中断位变为高电平。对于UHCI0，当接收到一个内联描述符指向的最后数据且未检测到Rx通道2的数据错误时，原始断开位变为低电平。*/
#define DMA_IN_SUC_EOF_CH2_INT_RAW  (BIT(1))
#define DMA_IN_SUC_EOF_CH2_INT_RAW_M  (BIT(1))
#define DMA_IN_SUC_EOF_CH2_INT_RAW_V  0x1
#define DMA_IN_SUC_EOF_CH2_INT_RAW_S  1
/* DMA_IN_DONE_CH2_INT_RAW:R/WTC/SS；位位置：[0]；默认值：1’b0；*/
/*描述：当接收到Rx通道2的一个内联描述符所指向的最后一个数据时，原始中断位变为高电平。*/
#define DMA_IN_DONE_CH2_INT_RAW  (BIT(0))
#define DMA_IN_DONE_CH2_INT_RAW_M  (BIT(0))
#define DMA_IN_DONE_CH2_INT_RAW_V  0x1
#define DMA_IN_DONE_CH2_INT_RAW_S  0

#define DMA_INT_ST_CH2_REG          (DR_REG_GDMA_BASE + 0x024)
/* DMA_OUTFIFO_UDF_CH2_INT_ST:RO；位位置：[12]；默认值：1’b0；*/
/*description:OUTFIFO_UDF_L1_CH_INT中断的原始中断状态位。*/
#define DMA_OUTFIFO_UDF_CH2_INT_ST  (BIT(12))
#define DMA_OUTFIFO_UDF_CH2_INT_ST_M  (BIT(12))
#define DMA_OUTFIFO_UDF_CH2_INT_ST_V  0x1
#define DMA_OUTFIFO_UDF_CH2_INT_ST_S  12
/* DMA_OUTFIFO_off_CH2_INT_ST:RO；位位置：[11]；默认值：1’b0；*/
/*description:OUTFIFO_OVF_L1_CH_INT中断的原始中断状态位。*/
#define DMA_OUTFIFO_OVF_CH2_INT_ST  (BIT(11))
#define DMA_OUTFIFO_OVF_CH2_INT_ST_M  (BIT(11))
#define DMA_OUTFIFO_OVF_CH2_INT_ST_V  0x1
#define DMA_OUTFIFO_OVF_CH2_INT_ST_S  11
/* DMA_INFIFO_UDF_CH2_INT_ST:RO；位位置：[10]；默认值：1’b0；*/
/*description:INFIFO_UDF_L1_CH_INT中断的原始中断状态位。*/
#define DMA_INFIFO_UDF_CH2_INT_ST  (BIT(10))
#define DMA_INFIFO_UDF_CH2_INT_ST_M  (BIT(10))
#define DMA_INFIFO_UDF_CH2_INT_ST_V  0x1
#define DMA_INFIFO_UDF_CH2_INT_ST_S  10
/* DMA_INFIFO_off_CH2_INT_ST:RO；位位置：[9]；默认值：1’b0；*/
/*description:INFIFO_OVF_L1_CH_INT中断的原始中断状态位。*/
#define DMA_INFIFO_OVF_CH2_INT_ST  (BIT(9))
#define DMA_INFIFO_OVF_CH2_INT_ST_M  (BIT(9))
#define DMA_INFIFO_OVF_CH2_INT_ST_V  0x1
#define DMA_INFIFO_OVF_CH2_INT_ST_S  9
/* 出口到出口的货物数量；位位置：[8]；默认值：1’b0；*/
/*description:OUT_TOTAL_EOF_CH_INT中断的原始中断状态位。*/
#define DMA_OUT_TOTAL_EOF_CH2_INT_ST  (BIT(8))
#define DMA_OUT_TOTAL_EOF_CH2_INT_ST_M  (BIT(8))
#define DMA_OUT_TOTAL_EOF_CH2_INT_ST_V  0x1
#define DMA_OUT_TOTAL_EOF_CH2_INT_ST_S  8
/* DMA_IN_DSCR_EMPTY_CH2_INT_ST:RO；位位置：[7]；默认值：1’b0；*/
/*description:IN_DSCR_EMPTY_CH_INT中断的原始中断状态位。*/
#define DMA_IN_DSCR_EMPTY_CH2_INT_ST  (BIT(7))
#define DMA_IN_DSCR_EMPTY_CH2_INT_ST_M  (BIT(7))
#define DMA_IN_DSCR_EMPTY_CH2_INT_ST_V  0x1
#define DMA_IN_DSCR_EMPTY_CH2_INT_ST_S  7
/* DMA_OUT_DSCR_ERR_CH2_INT_ST:RO；位位置：[6]；默认值：1’b0；*/
/*description:OUT_DSCR_ERR_CH_INT中断的原始中断状态位。*/
#define DMA_OUT_DSCR_ERR_CH2_INT_ST  (BIT(6))
#define DMA_OUT_DSCR_ERR_CH2_INT_ST_M  (BIT(6))
#define DMA_OUT_DSCR_ERR_CH2_INT_ST_V  0x1
#define DMA_OUT_DSCR_ERR_CH2_INT_ST_S  6
/* DMA_IN_DSCR_ERR_CH2_INT_ST:RO；位位置：[5]；默认值：1’b0；*/
/*description:IN_DSCR_ERR_CH_INT中断的原始中断状态位。*/
#define DMA_IN_DSCR_ERR_CH2_INT_ST  (BIT(5))
#define DMA_IN_DSCR_ERR_CH2_INT_ST_M  (BIT(5))
#define DMA_IN_DSCR_ERR_CH2_INT_ST_V  0x1
#define DMA_IN_DSCR_ERR_CH2_INT_ST_S  5
/* DMA_OUT_EOF_CH2_INT_ST:RO；位位置：[4]；默认值：1’b0；*/
/*description:OUT_EOF_CH_INT中断的原始中断状态位。*/
#define DMA_OUT_EOF_CH2_INT_ST  (BIT(4))
#define DMA_OUT_EOF_CH2_INT_ST_M  (BIT(4))
#define DMA_OUT_EOF_CH2_INT_ST_V  0x1
#define DMA_OUT_EOF_CH2_INT_ST_S  4
/* DMA_OUT_DONE_CH2_INT_ST:RO；位位置：[3]；默认值：1’b0；*/
/*description:OUT_DONE_CH_INT中断的原始中断状态位。*/
#define DMA_OUT_DONE_CH2_INT_ST  (BIT(3))
#define DMA_OUT_DONE_CH2_INT_ST_M  (BIT(3))
#define DMA_OUT_DONE_CH2_INT_ST_V  0x1
#define DMA_OUT_DONE_CH2_INT_ST_S  3
/* DMA_IN_ERR_EOF_CH2_INT_ST:RO；位位置：[2]；默认值：1’b0；*/
/*description:IN_ERR_EOF_CH_INT中断的原始中断状态位。*/
#define DMA_IN_ERR_EOF_CH2_INT_ST  (BIT(2))
#define DMA_IN_ERR_EOF_CH2_INT_ST_M  (BIT(2))
#define DMA_IN_ERR_EOF_CH2_INT_ST_V  0x1
#define DMA_IN_ERR_EOF_CH2_INT_ST_S  2
/* DMA_IN_SUC_EOF_CH2_INT_ST:RO；位位置：[1]；默认值：1’b0；*/
/*description:IN_SUC_EOF_CH_INT中断的原始中断状态位。*/
#define DMA_IN_SUC_EOF_CH2_INT_ST  (BIT(1))
#define DMA_IN_SUC_EOF_CH2_INT_ST_M  (BIT(1))
#define DMA_IN_SUC_EOF_CH2_INT_ST_V  0x1
#define DMA_IN_SUC_EOF_CH2_INT_ST_S  1
/* DMA_IN_DONE_CH2_INT_ST:RO；位位置：[0]；默认值：1’b0；*/
/*description:IN_DONE_CH_INT中断的原始中断状态位。*/
#define DMA_IN_DONE_CH2_INT_ST  (BIT(0))
#define DMA_IN_DONE_CH2_INT_ST_M  (BIT(0))
#define DMA_IN_DONE_CH2_INT_ST_V  0x1
#define DMA_IN_DONE_CH2_INT_ST_S  0

#define DMA_INT_ENA_CH2_REG          (DR_REG_GDMA_BASE + 0x028)
/* DMA_OUTFIFO_UDF_CH2_INT_ENA:R/W；位位置：[12]；默认值：1’b0；*/
/*description:OUTFIFO_UDF_L1_CH_INT中断的中断启用位。*/
#define DMA_OUTFIFO_UDF_CH2_INT_ENA  (BIT(12))
#define DMA_OUTFIFO_UDF_CH2_INT_ENA_M  (BIT(12))
#define DMA_OUTFIFO_UDF_CH2_INT_ENA_V  0x1
#define DMA_OUTFIFO_UDF_CH2_INT_ENA_S  12
/* DMA_OUTFIFO_off_CH2_INT_ENA:R/W；位位置：[11]；默认值：1’b0；*/
/*description:OUTFIFO_OVF_L1_CH_INT中断的中断启用位。*/
#define DMA_OUTFIFO_OVF_CH2_INT_ENA  (BIT(11))
#define DMA_OUTFIFO_OVF_CH2_INT_ENA_M  (BIT(11))
#define DMA_OUTFIFO_OVF_CH2_INT_ENA_V  0x1
#define DMA_OUTFIFO_OVF_CH2_INT_ENA_S  11
/* DMA_INFIFO_UDF_CH2_INT_ENA:R/W；位位置：[10]；默认值：1’b0；*/
/*description:INFIFO_UDF_L1_CH_INT中断的中断启用位。*/
#define DMA_INFIFO_UDF_CH2_INT_ENA  (BIT(10))
#define DMA_INFIFO_UDF_CH2_INT_ENA_M  (BIT(10))
#define DMA_INFIFO_UDF_CH2_INT_ENA_V  0x1
#define DMA_INFIFO_UDF_CH2_INT_ENA_S  10
/* DMA_INFIFO_off_CH2_INT_ENA:R/W；位位置：[9]；默认值：1’b0；*/
/*description:INFIFO_OVF_L1_CH_INT中断的中断启用位。*/
#define DMA_INFIFO_OVF_CH2_INT_ENA  (BIT(9))
#define DMA_INFIFO_OVF_CH2_INT_ENA_M  (BIT(9))
#define DMA_INFIFO_OVF_CH2_INT_ENA_V  0x1
#define DMA_INFIFO_OVF_CH2_INT_ENA_S  9
/* DMA_OUT_TOTAL_EOF_CH2_INT_ENA:R/W；位位置：[8]；默认值：1’b0；*/
/*description:OUT_TOTAL_EOF_CH_INT中断的中断启用位。*/
#define DMA_OUT_TOTAL_EOF_CH2_INT_ENA  (BIT(8))
#define DMA_OUT_TOTAL_EOF_CH2_INT_ENA_M  (BIT(8))
#define DMA_OUT_TOTAL_EOF_CH2_INT_ENA_V  0x1
#define DMA_OUT_TOTAL_EOF_CH2_INT_ENA_S  8
/* DMA_IN_DSCR_EMPTY_CH2_INT_ENA:R/W；位位置：[7]；默认值：1’b0；*/
/*description:IN_DSCR_EMPTY_CH_INT中断的中断启用位。*/
#define DMA_IN_DSCR_EMPTY_CH2_INT_ENA  (BIT(7))
#define DMA_IN_DSCR_EMPTY_CH2_INT_ENA_M  (BIT(7))
#define DMA_IN_DSCR_EMPTY_CH2_INT_ENA_V  0x1
#define DMA_IN_DSCR_EMPTY_CH2_INT_ENA_S  7
/* DMA_OUT_DSCR_ERR_CH2_INT_ENA:R/W；位位置：[6]；默认值：1’b0；*/
/*description:OUT_DSCR_ERR_CH_INT中断的中断启用位。*/
#define DMA_OUT_DSCR_ERR_CH2_INT_ENA  (BIT(6))
#define DMA_OUT_DSCR_ERR_CH2_INT_ENA_M  (BIT(6))
#define DMA_OUT_DSCR_ERR_CH2_INT_ENA_V  0x1
#define DMA_OUT_DSCR_ERR_CH2_INT_ENA_S  6
/* DMA_IN_DSCR_ERR_CH2_INT_ENA:R/W；位位置：[5]；默认值：1’b0；*/
/*description:IN_DSCR_ERR_CH_INT中断的中断启用位。*/
#define DMA_IN_DSCR_ERR_CH2_INT_ENA  (BIT(5))
#define DMA_IN_DSCR_ERR_CH2_INT_ENA_M  (BIT(5))
#define DMA_IN_DSCR_ERR_CH2_INT_ENA_V  0x1
#define DMA_IN_DSCR_ERR_CH2_INT_ENA_S  5
/* DMA_OUT_EOF_CH2_INT_ENA:R/W；位位置：[4]；默认值：1’b0；*/
/*description:OUT_EOF_CH_INT中断的中断启用位。*/
#define DMA_OUT_EOF_CH2_INT_ENA  (BIT(4))
#define DMA_OUT_EOF_CH2_INT_ENA_M  (BIT(4))
#define DMA_OUT_EOF_CH2_INT_ENA_V  0x1
#define DMA_OUT_EOF_CH2_INT_ENA_S  4
/* DMA_OUT_DONE_CH2_INT_ENA:R/W；位位置：[3]；默认值：1’b0；*/
/*description:OUT_DONE_CH_INT中断的中断启用位。*/
#define DMA_OUT_DONE_CH2_INT_ENA  (BIT(3))
#define DMA_OUT_DONE_CH2_INT_ENA_M  (BIT(3))
#define DMA_OUT_DONE_CH2_INT_ENA_V  0x1
#define DMA_OUT_DONE_CH2_INT_ENA_S  3
/* DMA_IN_ERR_EOF_CH2_INT_ENA:R/W；位位置：[2]；默认值：1’b0；*/
/*description:IN_ERR_EOF_CH_INT中断的中断启用位。*/
#define DMA_IN_ERR_EOF_CH2_INT_ENA  (BIT(2))
#define DMA_IN_ERR_EOF_CH2_INT_ENA_M  (BIT(2))
#define DMA_IN_ERR_EOF_CH2_INT_ENA_V  0x1
#define DMA_IN_ERR_EOF_CH2_INT_ENA_S  2
/* DMA_IN_SUC_EOF_CH2_INT_ENA:R/W；位位置：[1]；默认值：1’b0；*/
/*description:IN_SUC_EOF_CH_INT中断的中断启用位。*/
#define DMA_IN_SUC_EOF_CH2_INT_ENA  (BIT(1))
#define DMA_IN_SUC_EOF_CH2_INT_ENA_M  (BIT(1))
#define DMA_IN_SUC_EOF_CH2_INT_ENA_V  0x1
#define DMA_IN_SUC_EOF_CH2_INT_ENA_S  1
/* DMA_IN_DONE_CH2_INT_ENA:R/W；位位置：[0]；默认值：1’b0；*/
/*description:IN_DONE_CH_INT中断的中断启用位。*/
#define DMA_IN_DONE_CH2_INT_ENA  (BIT(0))
#define DMA_IN_DONE_CH2_INT_ENA_M  (BIT(0))
#define DMA_IN_DONE_CH2_INT_ENA_V  0x1
#define DMA_IN_DONE_CH2_INT_ENA_S  0

#define DMA_INT_CLR_CH2_REG          (DR_REG_GDMA_BASE + 0x02C)
/* DMA_OUTFIFO_UDF_CH2_INT_CLR:WT；位位置：[12]；默认值：1’b0；*/
/*description:设置此位以清除OUTFIFO_UDF_L1_CH_INT中断。*/
#define DMA_OUTFIFO_UDF_CH2_INT_CLR  (BIT(12))
#define DMA_OUTFIFO_UDF_CH2_INT_CLR_M  (BIT(12))
#define DMA_OUTFIFO_UDF_CH2_INT_CLR_V  0x1
#define DMA_OUTFIFO_UDF_CH2_INT_CLR_S  12
/* DMA_OUTFIFO_off_CH2_INT_CLR:WT；位位置：[11]；默认值：1’b0；*/
/*description:设置此位以清除OUTFIFO_OVF_L1_CH_INT中断。*/
#define DMA_OUTFIFO_OVF_CH2_INT_CLR  (BIT(11))
#define DMA_OUTFIFO_OVF_CH2_INT_CLR_M  (BIT(11))
#define DMA_OUTFIFO_OVF_CH2_INT_CLR_V  0x1
#define DMA_OUTFIFO_OVF_CH2_INT_CLR_S  11
/* DMA_INFIFO_UDF_CH2_INT_CLR:WT；位位置：[10]；默认值：1’b0；*/
/*description:设置此位以清除INFIFO_UDF_L1_CH_INT中断。*/
#define DMA_INFIFO_UDF_CH2_INT_CLR  (BIT(10))
#define DMA_INFIFO_UDF_CH2_INT_CLR_M  (BIT(10))
#define DMA_INFIFO_UDF_CH2_INT_CLR_V  0x1
#define DMA_INFIFO_UDF_CH2_INT_CLR_S  10
/* DMA_INFIFO_off_CH2_INT_CLR:WT；位位置：[9]；默认值：1’b0；*/
/*description:设置此位以清除INFIFO_OVF_L1_CH_INT中断。*/
#define DMA_INFIFO_OVF_CH2_INT_CLR  (BIT(9))
#define DMA_INFIFO_OVF_CH2_INT_CLR_M  (BIT(9))
#define DMA_INFIFO_OVF_CH2_INT_CLR_V  0x1
#define DMA_INFIFO_OVF_CH2_INT_CLR_S  9
/* DMA_OUT_TOTAL_EOF_CH2_INT_CLR:WT；位位置：[8]；默认值：1’b0；*/
/*description:设置此位以清除OUT_TOTAL_EOF_CH_INT中断。*/
#define DMA_OUT_TOTAL_EOF_CH2_INT_CLR  (BIT(8))
#define DMA_OUT_TOTAL_EOF_CH2_INT_CLR_M  (BIT(8))
#define DMA_OUT_TOTAL_EOF_CH2_INT_CLR_V  0x1
#define DMA_OUT_TOTAL_EOF_CH2_INT_CLR_S  8
/* DMA_IN_DSCR_EMPTY-CH2_INT_CLR:WT；位位置：[7]；默认值：1’b0；*/
/*description:设置此位以清除IN_DSCR_EMPTY_CH_INT中断。*/
#define DMA_IN_DSCR_EMPTY_CH2_INT_CLR  (BIT(7))
#define DMA_IN_DSCR_EMPTY_CH2_INT_CLR_M  (BIT(7))
#define DMA_IN_DSCR_EMPTY_CH2_INT_CLR_V  0x1
#define DMA_IN_DSCR_EMPTY_CH2_INT_CLR_S  7
/* DMA_OUT_DSCR_ERR_CH2_INT_CLR:WT；位位置：[6]；默认值：1’b0；*/
/*description:设置此位以清除OUT_DSCR_ERR_CH_INT中断。*/
#define DMA_OUT_DSCR_ERR_CH2_INT_CLR  (BIT(6))
#define DMA_OUT_DSCR_ERR_CH2_INT_CLR_M  (BIT(6))
#define DMA_OUT_DSCR_ERR_CH2_INT_CLR_V  0x1
#define DMA_OUT_DSCR_ERR_CH2_INT_CLR_S  6
/* DMA_IN_DSCR_ERR_CH2_INT_CLR:WT；位位置：[5]；默认值：1’b0；*/
/*description:设置此位以清除IN_DSCR_ERR_CH_INT中断。*/
#define DMA_IN_DSCR_ERR_CH2_INT_CLR  (BIT(5))
#define DMA_IN_DSCR_ERR_CH2_INT_CLR_M  (BIT(5))
#define DMA_IN_DSCR_ERR_CH2_INT_CLR_V  0x1
#define DMA_IN_DSCR_ERR_CH2_INT_CLR_S  5
/* DMA_OUT_EOF_CH2_INT_CLR:WT；位位置：[4]；默认值：1’b0；*/
/*description:设置此位以清除OUT_EOF_CH_INT中断。*/
#define DMA_OUT_EOF_CH2_INT_CLR  (BIT(4))
#define DMA_OUT_EOF_CH2_INT_CLR_M  (BIT(4))
#define DMA_OUT_EOF_CH2_INT_CLR_V  0x1
#define DMA_OUT_EOF_CH2_INT_CLR_S  4
/* DMA_OUT_DONE_CH2_INT_CLR:WT；位位置：[3]；默认值：1’b0；*/
/*description:设置此位以清除OUT_DONE_CH_INT中断。*/
#define DMA_OUT_DONE_CH2_INT_CLR  (BIT(3))
#define DMA_OUT_DONE_CH2_INT_CLR_M  (BIT(3))
#define DMA_OUT_DONE_CH2_INT_CLR_V  0x1
#define DMA_OUT_DONE_CH2_INT_CLR_S  3
/* DMA_IN_ERR_EOF_CH2_INT_CLR:WT；位位置：[2]；默认值：1’b0；*/
/*description:设置此位以清除IN_ERR_EOF_CH_INT中断。*/
#define DMA_IN_ERR_EOF_CH2_INT_CLR  (BIT(2))
#define DMA_IN_ERR_EOF_CH2_INT_CLR_M  (BIT(2))
#define DMA_IN_ERR_EOF_CH2_INT_CLR_V  0x1
#define DMA_IN_ERR_EOF_CH2_INT_CLR_S  2
/* DMA_IN_SUC_EOF_CH2_INT_CLR:WT；位位置：[1]；默认值：1’b0；*/
/*description:设置此位以清除IN_SUC_EOF_CH_INT中断。*/
#define DMA_IN_SUC_EOF_CH2_INT_CLR  (BIT(1))
#define DMA_IN_SUC_EOF_CH2_INT_CLR_M  (BIT(1))
#define DMA_IN_SUC_EOF_CH2_INT_CLR_V  0x1
#define DMA_IN_SUC_EOF_CH2_INT_CLR_S  1
/* DMA_IN_DONE_CH2_INT_CLR:WT；位位置：[0]；默认值：1’b0；*/
/*description:设置此位以清除IN_DONE_CH_INT中断。*/
#define DMA_IN_DONE_CH2_INT_CLR  (BIT(0))
#define DMA_IN_DONE_CH2_INT_CLR_M  (BIT(0))
#define DMA_IN_DONE_CH2_INT_CLR_V  0x1
#define DMA_IN_DONE_CH2_INT_CLR_S  0

#define DMA_AHB_TEST_REG          (DR_REG_GDMA_BASE + 0x040)
/* DMA_AHB_testadr:R/W；比特位置：[5:4]；默认值：2’b0；*/
/*description:保留*/
#define DMA_AHB_TESTADDR  0x00000003
#define DMA_AHB_TESTADDR_M  ((DMA_AHB_TESTADDR_V)<<(DMA_AHB_TESTADDR_S))
#define DMA_AHB_TESTADDR_V  0x3
#define DMA_AHB_TESTADDR_S  4
/* DMA_AHB_TESTMODE:R/W；位位置：[2:0]；默认值：3'b0；*/
/*description:保留*/
#define DMA_AHB_TESTMODE  0x00000007
#define DMA_AHB_TESTMODE_M  ((DMA_AHB_TESTMODE_V)<<(DMA_AHB_TESTMODE_S))
#define DMA_AHB_TESTMODE_V  0x7
#define DMA_AHB_TESTMODE_S  0

#define DMA_MISC_CONF_REG          (DR_REG_GDMA_BASE + 0x044)
/* DMA_CLK_EN:R/W；位位置：[3]；默认值：1’b0；*/
/*说明：*/
#define DMA_CLK_EN  (BIT(3))
#define DMA_CLK_EN_M  (BIT(3))
#define DMA_CLK_EN_V  0x1
#define DMA_CLK_EN_S  3
/* DMA_ARB_PRI_DIS:R/W；位位置：[2]；默认值：1’b0；*/
/*description:设置此位以禁用优先级仲裁功能。*/
#define DMA_ARB_PRI_DIS  (BIT(2))
#define DMA_ARB_PRI_DIS_M  (BIT(2))
#define DMA_ARB_PRI_DIS_V  0x1
#define DMA_ARB_PRI_DIS_S  2
/* DMA_AHBM_RST_INTER：R/W；位位置：[0]；默认值：1’b0；*/
/*description:设置此位，然后清除此位以重置内部ahb FSM。*/
#define DMA_AHBM_RST_INTER  (BIT(0))
#define DMA_AHBM_RST_INTER_M  (BIT(0))
#define DMA_AHBM_RST_INTER_V  0x1
#define DMA_AHBM_RST_INTER_S  0

#define DMA_DATE_REG          (DR_REG_GDMA_BASE + 0x048)
/* DMA_DATE:R/W；位位置：[31:0]；默认值：32'h2008250；*/
/*description:注册版本。*/
#define DMA_DATE  0xFFFFFFFF
#define DMA_DATE_M  ((DMA_DATE_V)<<(DMA_DATE_S))
#define DMA_DATE_V  0xFFFFFFFF
#define DMA_DATE_S  0

#define DMA_IN_CONF0_CH0_REG          (DR_REG_GDMA_BASE + 0x070)
/* DMA_MEM_TRANS_EN_CH0:R/W；位位置：[4]；默认值：1’b0；*/
/*description:将此位设置为1，以启用通过DMA将数据从存储器自动传输到存储器。*/
#define DMA_MEM_TRANS_EN_CH0  (BIT(4))
#define DMA_MEM_TRANS_EN_CH0_M  (BIT(4))
#define DMA_MEM_TRANS_EN_CH0_V  0x1
#define DMA_MEM_TRANS_EN_CH0_S  4
/* DMA_IN_DATA_BURST_EN_CH0:R/W；位位置：[3]；默认值：1’b0；*/
/*description:将此位设置为1，以在访问内部SRAM时启用接收数据的Rx通道0的INCR突发传输。*/
#define DMA_IN_DATA_BURST_EN_CH0  (BIT(3))
#define DMA_IN_DATA_BURST_EN_CH0_M  (BIT(3))
#define DMA_IN_DATA_BURST_EN_CH0_V  0x1
#define DMA_IN_DATA_BURST_EN_CH0_S  3
/* DMA_INDSCR_BURST_EN_CH0:R/W；位位置：[2]；默认值：1’b0；*/
/*description:当访问内部SRAM时，将此位设置为1以启用Rx通道0读取链路描述符的INCR突发传输。*/
#define DMA_INDSCR_BURST_EN_CH0  (BIT(2))
#define DMA_INDSCR_BURST_EN_CH0_M  (BIT(2))
#define DMA_INDSCR_BURST_EN_CH0_V  0x1
#define DMA_INDSCR_BURST_EN_CH0_S  2
/* DMA_IN_LOOP_TEST_CH0:R/W；位位置：[1]；默认值：1’b0；*/
/*description:保留*/
#define DMA_IN_LOOP_TEST_CH0  (BIT(1))
#define DMA_IN_LOOP_TEST_CH0_M  (BIT(1))
#define DMA_IN_LOOP_TEST_CH0_V  0x1
#define DMA_IN_LOOP_TEST_CH0_S  1
/* DMA_IN_RST_CH0:R/W；位位置：[0]；默认值：1'0；*/
/*描述：此位用于重置DMA通道0 Rx FSM和Rx FIFO指针。*/
#define DMA_IN_RST_CH0  (BIT(0))
#define DMA_IN_RST_CH0_M  (BIT(0))
#define DMA_IN_RST_CH0_V  0x1
#define DMA_IN_RST_CH0_S  0

#define DMA_IN_CONF1_CH0_REG          (DR_REG_GDMA_BASE + 0x074)
/* DMA_IN_CHECK_OWNER_CH0:R/W；位位置：[12]；默认值：1’b0；*/
/*description:设置此位以启用检查链接描述符的所有者属性。*/
#define DMA_IN_CHECK_OWNER_CH0  (BIT(12))
#define DMA_IN_CHECK_OWNER_CH0_M  (BIT(12))
#define DMA_IN_CHECK_OWNER_CH0_V  0x1
#define DMA_IN_CHECK_OWNER_CH0_S  12

#define DMA_INFIFO_STATUS_CH0_REG          (DR_REG_GDMA_BASE + 0x078)
/* DMA_IN_BUF_HUNGRY_CH0:RO；位位置：[27]；默认值：1’b0；*/
/*description:保留*/
#define DMA_IN_BUF_HUNGRY_CH0  (BIT(27))
#define DMA_IN_BUF_HUNGRY_CH0_M  (BIT(27))
#define DMA_IN_BUF_HUNGRY_CH0_V  0x1
#define DMA_IN_BUF_HUNGRY_CH0_S  27
/* DMA_IN_REMAIN_UNDER_4B_CH0:RO；位位置：[26]；默认值：1’b1；*/
/*description:保留*/
#define DMA_IN_REMAIN_UNDER_4B_CH0  (BIT(26))
#define DMA_IN_REMAIN_UNDER_4B_CH0_M  (BIT(26))
#define DMA_IN_REMAIN_UNDER_4B_CH0_V  0x1
#define DMA_IN_REMAIN_UNDER_4B_CH0_S  26
/* DMA_IN_REMAIN_UNDER_3B_CH0:RO；位位置：[25]；默认值：1’b1；*/
/*description:保留*/
#define DMA_IN_REMAIN_UNDER_3B_CH0  (BIT(25))
#define DMA_IN_REMAIN_UNDER_3B_CH0_M  (BIT(25))
#define DMA_IN_REMAIN_UNDER_3B_CH0_V  0x1
#define DMA_IN_REMAIN_UNDER_3B_CH0_S  25
/* DMA_IN_REMAIN_UNDER_2B_CH0:RO；位位置：[24]；默认值：1’b1；*/
/*description:保留*/
#define DMA_IN_REMAIN_UNDER_2B_CH0  (BIT(24))
#define DMA_IN_REMAIN_UNDER_2B_CH0_M  (BIT(24))
#define DMA_IN_REMAIN_UNDER_2B_CH0_V  0x1
#define DMA_IN_REMAIN_UNDER_2B_CH0_S  24
/* DMA_IN_REMAIN_UNDER_1B_CH0:RO；位位置：[23]；默认值：1’b1；*/
/*description:保留*/
#define DMA_IN_REMAIN_UNDER_1B_CH0  (BIT(23))
#define DMA_IN_REMAIN_UNDER_1B_CH0_M  (BIT(23))
#define DMA_IN_REMAIN_UNDER_1B_CH0_V  0x1
#define DMA_IN_REMAIN_UNDER_1B_CH0_S  23
/* DMA_INFIFO_CNT_CH0:RO；位位置：[7:2]；默认值：6'b0；*/
/*描述：寄存器将数据的字节数存储在Rx通道0的L1 Rx FIFO中。*/
#define DMA_INFIFO_CNT_CH0  0x0000003F
#define DMA_INFIFO_CNT_CH0_M  ((DMA_INFIFO_CNT_CH0_V)<<(DMA_INFIFO_CNT_CH0_S))
#define DMA_INFIFO_CNT_CH0_V  0x3F
#define DMA_INFIFO_CNT_CH0_S  2
/* DMA_INFIFO_EMPTY_CH0:RO；位位置：[1]；默认值：1’b1；*/
/*描述：Rx信道0的L1 Rx FIFO空信号。*/
#define DMA_INFIFO_EMPTY_CH0  (BIT(1))
#define DMA_INFIFO_EMPTY_CH0_M  (BIT(1))
#define DMA_INFIFO_EMPTY_CH0_V  0x1
#define DMA_INFIFO_EMPTY_CH0_S  1
/* DMA_INFIFO_FULL_CH0:RO；位位置：[0]；默认值：1’b1；*/
/*描述：Rx信道0的L1 Rx FIFO满信号。*/
#define DMA_INFIFO_FULL_CH0  (BIT(0))
#define DMA_INFIFO_FULL_CH0_M  (BIT(0))
#define DMA_INFIFO_FULL_CH0_V  0x1
#define DMA_INFIFO_FULL_CH0_S  0

#define DMA_IN_POP_CH0_REG          (DR_REG_GDMA_BASE + 0x07C)
/* DMA_INFIFO_POP_CH0:R/W/SC；位位置：[12]；默认值：1'0；*/
/*description:设置此位以从DMA FIFO弹出数据。*/
#define DMA_INFIFO_POP_CH0  (BIT(12))
#define DMA_INFIFO_POP_CH0_M  (BIT(12))
#define DMA_INFIFO_POP_CH0_V  0x1
#define DMA_INFIFO_POP_CH0_S  12
/* DMA_INFIFO_data_CH0:RO；位位置：[11:0]；默认值：12'h800；*/
/*description:此寄存器存储从DMA FIFO弹出的数据。*/
#define DMA_INFIFO_RDATA_CH0  0x00000FFF
#define DMA_INFIFO_RDATA_CH0_M  ((DMA_INFIFO_RDATA_CH0_V)<<(DMA_INFIFO_RDATA_CH0_S))
#define DMA_INFIFO_RDATA_CH0_V  0xFFF
#define DMA_INFIFO_RDATA_CH0_S  0

#define DMA_IN_LINK_CH0_REG          (DR_REG_GDMA_BASE + 0x080)
/* DMA_INLINK_PARK_CH0:RO；位位置：[24]；默认值：1'h1；*/
/*description:1：内联描述符的FSM处于空闲状态。0:内联描述符的FSM正在工作。*/
#define DMA_INLINK_PARK_CH0  (BIT(24))
#define DMA_INLINK_PARK_CH0_M  (BIT(24))
#define DMA_INLINK_PARK_CH0_V  0x1
#define DMA_INLINK_PARK_CH0_S  24
/* DMA_INLINK_RESTART_CH0:R/W/SC；位位置：[23]；默认值：1’b0；*/
/*description:设置此位以装入新的内联描述符。*/
#define DMA_INLINK_RESTART_CH0  (BIT(23))
#define DMA_INLINK_RESTART_CH0_M  (BIT(23))
#define DMA_INLINK_RESTART_CH0_V  0x1
#define DMA_INLINK_RESTART_CH0_S  23
/* DMA_INLINK_START_CH0:R/W/SC；位位置：[22]；默认值：1’b0；*/
/*description:设置此位以开始处理内联描述符。*/
#define DMA_INLINK_START_CH0  (BIT(22))
#define DMA_INLINK_START_CH0_M  (BIT(22))
#define DMA_INLINK_START_CH0_V  0x1
#define DMA_INLINK_START_CH0_S  22
/* DMA_INLINK_STOP_CH0:R/W/SC；位位置：[21]；默认值：1’b0；*/
/*description:设置此位以停止处理内联描述符。*/
#define DMA_INLINK_STOP_CH0  (BIT(21))
#define DMA_INLINK_STOP_CH0_M  (BIT(21))
#define DMA_INLINK_STOP_CH0_V  0x1
#define DMA_INLINK_STOP_CH0_S  21
/* DMA_INLINK_AUTO_RET_CH0:R/W；位位置：[20]；默认值：1’b1；*/
/*description:当当前接收数据中存在一些错误时，设置此位以返回当前内联描述符的地址。*/
#define DMA_INLINK_AUTO_RET_CH0  (BIT(20))
#define DMA_INLINK_AUTO_RET_CH0_M  (BIT(20))
#define DMA_INLINK_AUTO_RET_CH0_V  0x1
#define DMA_INLINK_AUTO_RET_CH0_S  20
/* DMA_INLINK_ADDR_CH0:R/W；比特位置：[19:0]；默认值：20'00；*/
/*description:此寄存器存储第一个内联描述符地址的20个最低有效位。*/
#define DMA_INLINK_ADDR_CH0  0x000FFFFF
#define DMA_INLINK_ADDR_CH0_M  ((DMA_INLINK_ADDR_CH0_V)<<(DMA_INLINK_ADDR_CH0_S))
#define DMA_INLINK_ADDR_CH0_V  0xFFFFF
#define DMA_INLINK_ADDR_CH0_S  0

#define DMA_IN_STATE_CH0_REG          (DR_REG_GDMA_BASE + 0x084)
/* DMA_IN_STATE_CH0:RO；比特位置：[22:20]；默认值：3'b0；*/
/*description:保留*/
#define DMA_IN_STATE_CH0  0x00000007
#define DMA_IN_STATE_CH0_M  ((DMA_IN_STATE_CH0_V)<<(DMA_IN_STATE_CH0_S))
#define DMA_IN_STATE_CH0_V  0x7
#define DMA_IN_STATE_CH0_S  20
/* DMA_IN_DSCR_STATE_CH0:RO；比特位置：[19:18]；默认值：2’b0；*/
/*description:保留*/
#define DMA_IN_DSCR_STATE_CH0  0x00000003
#define DMA_IN_DSCR_STATE_CH0_M  ((DMA_IN_DSCR_STATE_CH0_V)<<(DMA_IN_DSCR_STATE_CH0_S))
#define DMA_IN_DSCR_STATE_CH0_V  0x3
#define DMA_IN_DSCR_STATE_CH0_S  18
/* DMA_INLINK_DSCR_ADDR_CH0:RO；比特位置：[17:00]；默认值：18'b0；*/
/*description:此寄存器存储当前内联描述符的地址。*/
#define DMA_INLINK_DSCR_ADDR_CH0  0x0003FFFF
#define DMA_INLINK_DSCR_ADDR_CH0_M  ((DMA_INLINK_DSCR_ADDR_CH0_V)<<(DMA_INLINK_DSCR_ADDR_CH0_S))
#define DMA_INLINK_DSCR_ADDR_CH0_V  0x3FFFF
#define DMA_INLINK_DSCR_ADDR_CH0_S  0

#define DMA_IN_SUC_EOF_DES_ADDR_CH0_REG          (DR_REG_GDMA_BASE + 0x088)
/* DMA_IN_SUC_EOF_DES_ADDR_CH0:RO；位位置：[31:0]；默认值：32'h0；*/
/*description:当此描述符中的EOF位为1时，此寄存器存储内联描述符的地址。*/
#define DMA_IN_SUC_EOF_DES_ADDR_CH0  0xFFFFFFFF
#define DMA_IN_SUC_EOF_DES_ADDR_CH0_M  ((DMA_IN_SUC_EOF_DES_ADDR_CH0_V)<<(DMA_IN_SUC_EOF_DES_ADDR_CH0_S))
#define DMA_IN_SUC_EOF_DES_ADDR_CH0_V  0xFFFFFFFF
#define DMA_IN_SUC_EOF_DES_ADDR_CH0_S  0

#define DMA_IN_ERR_EOF_DES_ADDR_CH0_REG          (DR_REG_GDMA_BASE + 0x08C)
/* DMA_IN_ERR_EOF_DES_ADDR_CH0:RO；位位置：[31:0]；默认值：32'h0；*/
/*description:当当前接收数据中存在一些错误时，此寄存器存储内联描述符的地址。仅当外围设备为UHCI0时使用。*/
#define DMA_IN_ERR_EOF_DES_ADDR_CH0  0xFFFFFFFF
#define DMA_IN_ERR_EOF_DES_ADDR_CH0_M  ((DMA_IN_ERR_EOF_DES_ADDR_CH0_V)<<(DMA_IN_ERR_EOF_DES_ADDR_CH0_S))
#define DMA_IN_ERR_EOF_DES_ADDR_CH0_V  0xFFFFFFFF
#define DMA_IN_ERR_EOF_DES_ADDR_CH0_S  0

#define DMA_IN_DSCR_CH0_REG          (DR_REG_GDMA_BASE + 0x090)
/* DMA_INLINK_DSCR_CH0:RO；位位置：[31:0]；默认值：32'b0；*/
/*description:当前内联描述符x的地址。*/
#define DMA_INLINK_DSCR_CH0  0xFFFFFFFF
#define DMA_INLINK_DSCR_CH0_M  ((DMA_INLINK_DSCR_CH0_V)<<(DMA_INLINK_DSCR_CH0_S))
#define DMA_INLINK_DSCR_CH0_V  0xFFFFFFFF
#define DMA_INLINK_DSCR_CH0_S  0

#define DMA_IN_DSCR_BF0_CH0_REG          (DR_REG_GDMA_BASE + 0x094)
/* DMA_INLINK_DSCR_BF0_CH0:RO；位位置：[31:0]；默认值：32'b0；*/
/*description:最后一个内联描述符x-1的地址。*/
#define DMA_INLINK_DSCR_BF0_CH0  0xFFFFFFFF
#define DMA_INLINK_DSCR_BF0_CH0_M  ((DMA_INLINK_DSCR_BF0_CH0_V)<<(DMA_INLINK_DSCR_BF0_CH0_S))
#define DMA_INLINK_DSCR_BF0_CH0_V  0xFFFFFFFF
#define DMA_INLINK_DSCR_BF0_CH0_S  0

#define DMA_IN_DSCR_BF1_CH0_REG          (DR_REG_GDMA_BASE + 0x098)
/* DMA_INLINK_DSCR_BF1_CH0:RO；位位置：[31:0]；默认值：32'b0；*/
/*description:倒数第二个内联描述符x-2的地址。*/
#define DMA_INLINK_DSCR_BF1_CH0  0xFFFFFFFF
#define DMA_INLINK_DSCR_BF1_CH0_M  ((DMA_INLINK_DSCR_BF1_CH0_V)<<(DMA_INLINK_DSCR_BF1_CH0_S))
#define DMA_INLINK_DSCR_BF1_CH0_V  0xFFFFFFFF
#define DMA_INLINK_DSCR_BF1_CH0_S  0

#define DMA_IN_PRI_CH0_REG          (DR_REG_GDMA_BASE + 0x09C)
/* DMA_RX_PRI_CH0:R/W；位位置：[3:0]；默认值：4'b0；*/
/*description:Rx通道0的优先级。值越大，优先级越高。*/
#define DMA_RX_PRI_CH0  0x0000000F
#define DMA_RX_PRI_CH0_M  ((DMA_RX_PRI_CH0_V)<<(DMA_RX_PRI_CH0_S))
#define DMA_RX_PRI_CH0_V  0xF
#define DMA_RX_PRI_CH0_S  0

#define DMA_IN_PERI_SEL_CH0_REG          (DR_REG_GDMA_BASE + 0x0A0)
/* DMA_PERI_IN_SEL_CH0:R/W；比特位置：[5:0]；默认值：6'h3F；*/
/*描述：此寄存器用于为Rx通道选择外设。0:SPI2.1:保留。2： UHCI0.3:I2S0.4：保留。5： 保留。6： AES。7： 沙。8： ADC_DAC。*/
#define DMA_PERI_IN_SEL_CH0  0x0000003F
#define DMA_PERI_IN_SEL_CH0_M  ((DMA_PERI_IN_SEL_CH0_V)<<(DMA_PERI_IN_SEL_CH0_S))
#define DMA_PERI_IN_SEL_CH0_V  0x3F
#define DMA_PERI_IN_SEL_CH0_S  0

#define DMA_OUT_CONF0_CH0_REG          (DR_REG_GDMA_BASE + 0x0D0)
/* DMA_OUT_DATA_BURST_EN_CH0:R/W；位位置：[5]；默认值：1’b0；*/
/*description:将此位设置为1，以在访问内部SRAM时启用传输数据的Tx信道0的INCR突发传输。*/
#define DMA_OUT_DATA_BURST_EN_CH0  (BIT(5))
#define DMA_OUT_DATA_BURST_EN_CH0_M  (BIT(5))
#define DMA_OUT_DATA_BURST_EN_CH0_V  0x1
#define DMA_OUT_DATA_BURST_EN_CH0_S  5
/* DMA_OUTDSCR_BURST_EN_CH0:R/W；位位置：[4]；默认值：1’b0；*/
/*description:将此位设置为1，以便在访问内部SRAM时，为Tx通道0读取链路描述符启用INCR突发传输。*/
#define DMA_OUTDSCR_BURST_EN_CH0  (BIT(4))
#define DMA_OUTDSCR_BURST_EN_CH0_M  (BIT(4))
#define DMA_OUTDSCR_BURST_EN_CH0_V  0x1
#define DMA_OUTDSCR_BURST_EN_CH0_S  4
/* DMA_OUT_EOF_MODE_CH0:R/W；位位置：[3]；默认值：1’b1；*/
/*描述：传输数据时EOF标志生成模式。1： 当需要传输的数据从DMA中的FIFO弹出时，生成Tx信道0的EOF标志*/
#define DMA_OUT_EOF_MODE_CH0  (BIT(3))
#define DMA_OUT_EOF_MODE_CH0_M  (BIT(3))
#define DMA_OUT_EOF_MODE_CH0_V  0x1
#define DMA_OUT_EOF_MODE_CH0_S  3
/* DMA_OUT_AUTO_WRBACK_CH0:R/W；位位置：[2]；默认值：1’b0；*/
/*description:设置此位以在传输tx缓冲区中的所有数据时启用自动outlink写回。*/
#define DMA_OUT_AUTO_WRBACK_CH0  (BIT(2))
#define DMA_OUT_AUTO_WRBACK_CH0_M  (BIT(2))
#define DMA_OUT_AUTO_WRBACK_CH0_V  0x1
#define DMA_OUT_AUTO_WRBACK_CH0_S  2
/* DMA_OUT_LOOP_TEST_CH0:R/W；位位置：[1]；默认值：1’b0；*/
/*description:保留*/
#define DMA_OUT_LOOP_TEST_CH0  (BIT(1))
#define DMA_OUT_LOOP_TEST_CH0_M  (BIT(1))
#define DMA_OUT_LOOP_TEST_CH0_V  0x1
#define DMA_OUT_LOOP_TEST_CH0_S  1
/* DMA_OUT_RST_CH0:R/W；位位置：[0]；默认值：1’b0；*/
/*描述：此位用于重置DMA通道0 Tx FSM和Tx FIFO指针。*/
#define DMA_OUT_RST_CH0  (BIT(0))
#define DMA_OUT_RST_CH0_M  (BIT(0))
#define DMA_OUT_RST_CH0_V  0x1
#define DMA_OUT_RST_CH0_S  0

#define DMA_OUT_CONF1_CH0_REG          (DR_REG_GDMA_BASE + 0x0D4)
/* DMA_OUT_CHECK_OWNER_CH0:R/W；位位置：[12]；默认值：1’b0；*/
/*description:设置此位以启用检查链接描述符的所有者属性。*/
#define DMA_OUT_CHECK_OWNER_CH0  (BIT(12))
#define DMA_OUT_CHECK_OWNER_CH0_M  (BIT(12))
#define DMA_OUT_CHECK_OWNER_CH0_V  0x1
#define DMA_OUT_CHECK_OWNER_CH0_S  12

#define DMA_OUTFIFO_STATUS_CH0_REG          (DR_REG_GDMA_BASE + 0x0D8)
/* DMA_OUT_REMAIN_UNDER_4B_CH0:RO；位位置：[26]；默认值：1’b1；*/
/*description:保留*/
#define DMA_OUT_REMAIN_UNDER_4B_CH0  (BIT(26))
#define DMA_OUT_REMAIN_UNDER_4B_CH0_M  (BIT(26))
#define DMA_OUT_REMAIN_UNDER_4B_CH0_V  0x1
#define DMA_OUT_REMAIN_UNDER_4B_CH0_S  26
/* DMA_OUT_REMAIN_UNDER_3B_CH0:RO；位位置：[25]；默认值：1’b1；*/
/*description:保留*/
#define DMA_OUT_REMAIN_UNDER_3B_CH0  (BIT(25))
#define DMA_OUT_REMAIN_UNDER_3B_CH0_M  (BIT(25))
#define DMA_OUT_REMAIN_UNDER_3B_CH0_V  0x1
#define DMA_OUT_REMAIN_UNDER_3B_CH0_S  25
/* DMA_OUT_REMAIN_UNDER_2B_CH0:RO；位位置：[24]；默认值：1’b1；*/
/*description:保留*/
#define DMA_OUT_REMAIN_UNDER_2B_CH0  (BIT(24))
#define DMA_OUT_REMAIN_UNDER_2B_CH0_M  (BIT(24))
#define DMA_OUT_REMAIN_UNDER_2B_CH0_V  0x1
#define DMA_OUT_REMAIN_UNDER_2B_CH0_S  24
/* DMA_OUT_REMAIN_UNDER_1B_CH0:RO；位位置：[23]；默认值：1’b1；*/
/*description:保留*/
#define DMA_OUT_REMAIN_UNDER_1B_CH0  (BIT(23))
#define DMA_OUT_REMAIN_UNDER_1B_CH0_M  (BIT(23))
#define DMA_OUT_REMAIN_UNDER_1B_CH0_V  0x1
#define DMA_OUT_REMAIN_UNDER_1B_CH0_S  23
/* DMA_OUTFIFO_CNT_CH0:RO；位位置：[7:2]；默认值：6'b0；*/
/*描述：寄存器将Tx信道0的数据字节数存储在L1 Tx FIFO中。*/
#define DMA_OUTFIFO_CNT_CH0  0x0000003F
#define DMA_OUTFIFO_CNT_CH0_M  ((DMA_OUTFIFO_CNT_CH0_V)<<(DMA_OUTFIFO_CNT_CH0_S))
#define DMA_OUTFIFO_CNT_CH0_V  0x3F
#define DMA_OUTFIFO_CNT_CH0_S  2
/* DMA_OUTFIFO_EMPTY_CH0:RO；位位置：[1]；默认值：1’b1；*/
/*描述：Tx信道0的L1 Tx FIFO空信号。*/
#define DMA_OUTFIFO_EMPTY_CH0  (BIT(1))
#define DMA_OUTFIFO_EMPTY_CH0_M  (BIT(1))
#define DMA_OUTFIFO_EMPTY_CH0_V  0x1
#define DMA_OUTFIFO_EMPTY_CH0_S  1
/* DMA_OUTFIFO_FULL_CH0:RO；位位置：[0]；默认值：1’b0；*/
/*描述：Tx信道0的L1 Tx FIFO满信号。*/
#define DMA_OUTFIFO_FULL_CH0  (BIT(0))
#define DMA_OUTFIFO_FULL_CH0_M  (BIT(0))
#define DMA_OUTFIFO_FULL_CH0_V  0x1
#define DMA_OUTFIFO_FULL_CH0_S  0

#define DMA_OUT_PUSH_CH0_REG          (DR_REG_GDMA_BASE + 0x0DC)
/* DMA_OUTFIFO_PUSH_CH0:R/W/SC；位位置：[9]；默认值：1'0；*/
/*description:设置此位以将数据推入DMA FIFO。*/
#define DMA_OUTFIFO_PUSH_CH0  (BIT(9))
#define DMA_OUTFIFO_PUSH_CH0_M  (BIT(9))
#define DMA_OUTFIFO_PUSH_CH0_V  0x1
#define DMA_OUTFIFO_PUSH_CH0_S  9
/* DMA_OUTFIFO_WDATA_CH0:R/W；位位置：[8:0]；默认值：9'0；*/
/*description:此寄存器存储需要推入DMA FIFO的数据。*/
#define DMA_OUTFIFO_WDATA_CH0  0x000001FF
#define DMA_OUTFIFO_WDATA_CH0_M  ((DMA_OUTFIFO_WDATA_CH0_V)<<(DMA_OUTFIFO_WDATA_CH0_S))
#define DMA_OUTFIFO_WDATA_CH0_V  0x1FF
#define DMA_OUTFIFO_WDATA_CH0_S  0

#define DMA_OUT_LINK_CH0_REG          (DR_REG_GDMA_BASE + 0x0E0)
/* DMA_OUTLINK_PARK_CH0:RO；位位置：[23]；默认值：1'h1；*/
/*描述：1:outlink描述符的FSM处于空闲状态。0:outlink描述符的FSM正在工作。*/
#define DMA_OUTLINK_PARK_CH0  (BIT(23))
#define DMA_OUTLINK_PARK_CH0_M  (BIT(23))
#define DMA_OUTLINK_PARK_CH0_V  0x1
#define DMA_OUTLINK_PARK_CH0_S  23
/* DMA_OUTLINK_RESTART_CH0:R/W/SC；位位置：[22]；默认值：1’b0；*/
/*description:设置此位以从上一个地址重新启动新的outlink。*/
#define DMA_OUTLINK_RESTART_CH0  (BIT(22))
#define DMA_OUTLINK_RESTART_CH0_M  (BIT(22))
#define DMA_OUTLINK_RESTART_CH0_V  0x1
#define DMA_OUTLINK_RESTART_CH0_S  22
/* DMA_OUTLINK_START_CH0:R/W/SC；位位置：[21]；默认值：1’b0；*/
/*description:设置此位以开始处理outlink描述符。*/
#define DMA_OUTLINK_START_CH0  (BIT(21))
#define DMA_OUTLINK_START_CH0_M  (BIT(21))
#define DMA_OUTLINK_START_CH0_V  0x1
#define DMA_OUTLINK_START_CH0_S  21
/* DMA_OUTLINK_STOP_CH0:R/W/SC；位位置：[20]；默认值：1’b0；*/
/*description:设置此位以停止处理outlink描述符。*/
#define DMA_OUTLINK_STOP_CH0  (BIT(20))
#define DMA_OUTLINK_STOP_CH0_M  (BIT(20))
#define DMA_OUTLINK_STOP_CH0_V  0x1
#define DMA_OUTLINK_STOP_CH0_S  20
/* DMA_OUTLINK_ADDR_CH0:R/W；比特位置：[19:0]；默认值：20'00；*/
/*description:此寄存器存储第一个outlink描述符地址的20个最低有效位。*/
#define DMA_OUTLINK_ADDR_CH0  0x000FFFFF
#define DMA_OUTLINK_ADDR_CH0_M  ((DMA_OUTLINK_ADDR_CH0_V)<<(DMA_OUTLINK_ADDR_CH0_S))
#define DMA_OUTLINK_ADDR_CH0_V  0xFFFFF
#define DMA_OUTLINK_ADDR_CH0_S  0

#define DMA_OUT_STATE_CH0_REG          (DR_REG_GDMA_BASE + 0x0E4)
/* DMA_OUT_STATE_CH0:RO；比特位置：[22:20]；默认值：3'b0；*/
/*description:保留*/
#define DMA_OUT_STATE_CH0  0x00000007
#define DMA_OUT_STATE_CH0_M  ((DMA_OUT_STATE_CH0_V)<<(DMA_OUT_STATE_CH0_S))
#define DMA_OUT_STATE_CH0_V  0x7
#define DMA_OUT_STATE_CH0_S  20
/* DMA_OUT_DSCR_STATE_CH0:RO；比特位置：[19:18]；默认值：2’b0；*/
/*description:保留*/
#define DMA_OUT_DSCR_STATE_CH0  0x00000003
#define DMA_OUT_DSCR_STATE_CH0_M  ((DMA_OUT_DSCR_STATE_CH0_V)<<(DMA_OUT_DSCR_STATE_CH0_S))
#define DMA_OUT_DSCR_STATE_CH0_V  0x3
#define DMA_OUT_DSCR_STATE_CH0_S  18
/* DMA_OUTLINK_DSCR_ADDR_CH0:RO；比特位置：[17:00]；默认值：18'b0；*/
/*description:此寄存器存储当前outlink描述符的地址。*/
#define DMA_OUTLINK_DSCR_ADDR_CH0  0x0003FFFF
#define DMA_OUTLINK_DSCR_ADDR_CH0_M  ((DMA_OUTLINK_DSCR_ADDR_CH0_V)<<(DMA_OUTLINK_DSCR_ADDR_CH0_S))
#define DMA_OUTLINK_DSCR_ADDR_CH0_V  0x3FFFF
#define DMA_OUTLINK_DSCR_ADDR_CH0_S  0

#define DMA_OUT_EOF_DES_ADDR_CH0_REG          (DR_REG_GDMA_BASE + 0x0E8)
/* DMA_OUT_EOF_DES_ADDR_CH0:RO；位位置：[31:0]；默认值：32'h0；*/
/*description:当此描述符中的EOF位为1时，此寄存器存储outlink描述符的地址。*/
#define DMA_OUT_EOF_DES_ADDR_CH0  0xFFFFFFFF
#define DMA_OUT_EOF_DES_ADDR_CH0_M  ((DMA_OUT_EOF_DES_ADDR_CH0_V)<<(DMA_OUT_EOF_DES_ADDR_CH0_S))
#define DMA_OUT_EOF_DES_ADDR_CH0_V  0xFFFFFFFF
#define DMA_OUT_EOF_DES_ADDR_CH0_S  0

#define DMA_OUT_EOF_BFR_DES_ADDR_CH0_REG          (DR_REG_GDMA_BASE + 0x0EC)
/* DMA_OUT_EOF_BFR_DES_ADDR_CH0:RO；位位置：[31:0]；默认值：32'h0；*/
/*description:此寄存器存储最后一个outlink描述符之前的outlink描述符的地址。*/
#define DMA_OUT_EOF_BFR_DES_ADDR_CH0  0xFFFFFFFF
#define DMA_OUT_EOF_BFR_DES_ADDR_CH0_M  ((DMA_OUT_EOF_BFR_DES_ADDR_CH0_V)<<(DMA_OUT_EOF_BFR_DES_ADDR_CH0_S))
#define DMA_OUT_EOF_BFR_DES_ADDR_CH0_V  0xFFFFFFFF
#define DMA_OUT_EOF_BFR_DES_ADDR_CH0_S  0

#define DMA_OUT_DSCR_CH0_REG          (DR_REG_GDMA_BASE + 0x0F0)
/* DMA_OUTLINK_DSCR_CH0:RO；位位置：[31:0]；默认值：32'b0；*/
/*description:当前outlink描述符y的地址。*/
#define DMA_OUTLINK_DSCR_CH0  0xFFFFFFFF
#define DMA_OUTLINK_DSCR_CH0_M  ((DMA_OUTLINK_DSCR_CH0_V)<<(DMA_OUTLINK_DSCR_CH0_S))
#define DMA_OUTLINK_DSCR_CH0_V  0xFFFFFFFF
#define DMA_OUTLINK_DSCR_CH0_S  0

#define DMA_OUT_DSCR_BF0_CH0_REG          (DR_REG_GDMA_BASE + 0x0F4)
/* DMA_OUTLINK_DSCR_BF0_CH0:RO；位位置：[31:0]；默认值：32'b0；*/
/*description:最后一个outlink描述符y-1的地址。*/
#define DMA_OUTLINK_DSCR_BF0_CH0  0xFFFFFFFF
#define DMA_OUTLINK_DSCR_BF0_CH0_M  ((DMA_OUTLINK_DSCR_BF0_CH0_V)<<(DMA_OUTLINK_DSCR_BF0_CH0_S))
#define DMA_OUTLINK_DSCR_BF0_CH0_V  0xFFFFFFFF
#define DMA_OUTLINK_DSCR_BF0_CH0_S  0

#define DMA_OUT_DSCR_BF1_CH0_REG          (DR_REG_GDMA_BASE + 0x0F8)
/* DMA_OUTLINK_DSCR_BF1_CH0:RO；位位置：[31:0]；默认值：32'b0；*/
/*description:倒数第二个内联描述符x-2的地址。*/
#define DMA_OUTLINK_DSCR_BF1_CH0  0xFFFFFFFF
#define DMA_OUTLINK_DSCR_BF1_CH0_M  ((DMA_OUTLINK_DSCR_BF1_CH0_V)<<(DMA_OUTLINK_DSCR_BF1_CH0_S))
#define DMA_OUTLINK_DSCR_BF1_CH0_V  0xFFFFFFFF
#define DMA_OUTLINK_DSCR_BF1_CH0_S  0

#define DMA_OUT_PRI_CH0_REG          (DR_REG_GDMA_BASE + 0x0FC)
/* DMA_TX_PRI_CH0:R/W；位位置：[3:0]；默认值：4'b0；*/
/*description:Tx信道0的优先级。值越大，优先级越高。*/
#define DMA_TX_PRI_CH0  0x0000000F
#define DMA_TX_PRI_CH0_M  ((DMA_TX_PRI_CH0_V)<<(DMA_TX_PRI_CH0_S))
#define DMA_TX_PRI_CH0_V  0xF
#define DMA_TX_PRI_CH0_S  0

#define DMA_OUT_PERI_SEL_CH0_REG          (DR_REG_GDMA_BASE + 0x100)
/* DMA_PERI_OUT_SEL_CH0:R/W；比特位置：[5:0]；默认值：6'h3F；*/
/*描述：此寄存器用于为Tx信道选择外设。0:SPI2.1:保留。2： UHCI0.3:I2S0.4：保留。5： 保留。6： AES。7： 沙。8： ADC_DAC。*/
#define DMA_PERI_OUT_SEL_CH0  0x0000003F
#define DMA_PERI_OUT_SEL_CH0_M  ((DMA_PERI_OUT_SEL_CH0_V)<<(DMA_PERI_OUT_SEL_CH0_S))
#define DMA_PERI_OUT_SEL_CH0_V  0x3F
#define DMA_PERI_OUT_SEL_CH0_S  0

#define DMA_IN_CONF0_CH1_REG          (DR_REG_GDMA_BASE + 0x130)
/* DMA_MEM_TRANS_EN_CH1:R/W；位位置：[4]；默认值：1’b0；*/
/*description:将此位设置为1，以启用通过DMA将数据从存储器自动传输到存储器。*/
#define DMA_MEM_TRANS_EN_CH1  (BIT(4))
#define DMA_MEM_TRANS_EN_CH1_M  (BIT(4))
#define DMA_MEM_TRANS_EN_CH1_V  0x1
#define DMA_MEM_TRANS_EN_CH1_S  4
/* DMA_IN_DATA_BURST_EN_CH1:R/W；位位置：[3]；默认值：1’b0；*/
/*description:将此位设置为1，以在访问内部SRAM时启用接收数据的Rx通道1的INCR突发传输。*/
#define DMA_IN_DATA_BURST_EN_CH1  (BIT(3))
#define DMA_IN_DATA_BURST_EN_CH1_M  (BIT(3))
#define DMA_IN_DATA_BURST_EN_CH1_V  0x1
#define DMA_IN_DATA_BURST_EN_CH1_S  3
/* DMA_INDSCR_BURST_EN_CH1:R/W；位位置：[2]；默认值：1’b0；*/
/*description:将此位设置为1，以在访问内部SRAM时启用Rx通道1读取链路描述符的INCR突发传输。*/
#define DMA_INDSCR_BURST_EN_CH1  (BIT(2))
#define DMA_INDSCR_BURST_EN_CH1_M  (BIT(2))
#define DMA_INDSCR_BURST_EN_CH1_V  0x1
#define DMA_INDSCR_BURST_EN_CH1_S  2
/* DMA_IN_LOOP_TEST_CH1:R/W；位位置：[1]；默认值：1’b0；*/
/*description:保留*/
#define DMA_IN_LOOP_TEST_CH1  (BIT(1))
#define DMA_IN_LOOP_TEST_CH1_M  (BIT(1))
#define DMA_IN_LOOP_TEST_CH1_V  0x1
#define DMA_IN_LOOP_TEST_CH1_S  1
/* DMA_IN_RST_CH1:R/W；位位置：[0]；默认值：1'0；*/
/*描述：此位用于重置DMA通道1 Rx FSM和Rx FIFO指针。*/
#define DMA_IN_RST_CH1  (BIT(0))
#define DMA_IN_RST_CH1_M  (BIT(0))
#define DMA_IN_RST_CH1_V  0x1
#define DMA_IN_RST_CH1_S  0

#define DMA_IN_CONF1_CH1_REG          (DR_REG_GDMA_BASE + 0x134)
/* DMA_IN_CHECK_OWNER_CH1:R/W；位位置：[12]；默认值：1’b0；*/
/*description:设置此位以启用检查链接描述符的所有者属性。*/
#define DMA_IN_CHECK_OWNER_CH1  (BIT(12))
#define DMA_IN_CHECK_OWNER_CH1_M  (BIT(12))
#define DMA_IN_CHECK_OWNER_CH1_V  0x1
#define DMA_IN_CHECK_OWNER_CH1_S  12

#define DMA_INFIFO_STATUS_CH1_REG          (DR_REG_GDMA_BASE + 0x138)
/* DMA_IN_BUF_HUNGRY_CH1:RO；位位置：[27]；默认值：1’b0；*/
/*description:保留*/
#define DMA_IN_BUF_HUNGRY_CH1  (BIT(27))
#define DMA_IN_BUF_HUNGRY_CH1_M  (BIT(27))
#define DMA_IN_BUF_HUNGRY_CH1_V  0x1
#define DMA_IN_BUF_HUNGRY_CH1_S  27
/* DMA_IN_REMAIN_UNDER_4B_CH1:RO；位位置：[26]；默认值：1’b1；*/
/*description:保留*/
#define DMA_IN_REMAIN_UNDER_4B_CH1  (BIT(26))
#define DMA_IN_REMAIN_UNDER_4B_CH1_M  (BIT(26))
#define DMA_IN_REMAIN_UNDER_4B_CH1_V  0x1
#define DMA_IN_REMAIN_UNDER_4B_CH1_S  26
/* DMA_IN_REMAIN_UNDER_3B_CH1:RO；位位置：[25]；默认值：1’b1；*/
/*description:保留*/
#define DMA_IN_REMAIN_UNDER_3B_CH1  (BIT(25))
#define DMA_IN_REMAIN_UNDER_3B_CH1_M  (BIT(25))
#define DMA_IN_REMAIN_UNDER_3B_CH1_V  0x1
#define DMA_IN_REMAIN_UNDER_3B_CH1_S  25
/* DMA_IN_REMAIN_UNDER_2B_CH1:RO；位位置：[24]；默认值：1’b1；*/
/*description:保留*/
#define DMA_IN_REMAIN_UNDER_2B_CH1  (BIT(24))
#define DMA_IN_REMAIN_UNDER_2B_CH1_M  (BIT(24))
#define DMA_IN_REMAIN_UNDER_2B_CH1_V  0x1
#define DMA_IN_REMAIN_UNDER_2B_CH1_S  24
/* DMA_IN_REMAIN_UNDER_1B_CH1:RO；位位置：[23]；默认值：1’b1；*/
/*description:保留*/
#define DMA_IN_REMAIN_UNDER_1B_CH1  (BIT(23))
#define DMA_IN_REMAIN_UNDER_1B_CH1_M  (BIT(23))
#define DMA_IN_REMAIN_UNDER_1B_CH1_V  0x1
#define DMA_IN_REMAIN_UNDER_1B_CH1_S  23
/* DMA_INFIFO_CNT_CH1:RO；位位置：[7:2]；默认值：6'b0；*/
/*描述：寄存器将数据的字节数存储在Rx通道1的L1 Rx FIFO中。*/
#define DMA_INFIFO_CNT_CH1  0x0000003F
#define DMA_INFIFO_CNT_CH1_M  ((DMA_INFIFO_CNT_CH1_V)<<(DMA_INFIFO_CNT_CH1_S))
#define DMA_INFIFO_CNT_CH1_V  0x3F
#define DMA_INFIFO_CNT_CH1_S  2
/* DMA_INFIFO_EMPTY_CH1:RO；位位置：[1]；默认值：1’b1；*/
/*描述：Rx信道1的L1 Rx FIFO空信号。*/
#define DMA_INFIFO_EMPTY_CH1  (BIT(1))
#define DMA_INFIFO_EMPTY_CH1_M  (BIT(1))
#define DMA_INFIFO_EMPTY_CH1_V  0x1
#define DMA_INFIFO_EMPTY_CH1_S  1
/* DMA_INFIFO_FULL_CH1:RO；位位置：[0]；默认值：1’b1；*/
/*描述：Rx信道1的L1 Rx FIFO满信号。*/
#define DMA_INFIFO_FULL_CH1  (BIT(0))
#define DMA_INFIFO_FULL_CH1_M  (BIT(0))
#define DMA_INFIFO_FULL_CH1_V  0x1
#define DMA_INFIFO_FULL_CH1_S  0

#define DMA_IN_POP_CH1_REG          (DR_REG_GDMA_BASE + 0x13C)
/* DMA_INFIFO_POP_CH1:R/W/SC；位位置：[12]；默认值：1'0；*/
/*description:设置此位以从DMA FIFO弹出数据。*/
#define DMA_INFIFO_POP_CH1  (BIT(12))
#define DMA_INFIFO_POP_CH1_M  (BIT(12))
#define DMA_INFIFO_POP_CH1_V  0x1
#define DMA_INFIFO_POP_CH1_S  12
/* DMA_INFIFO_data_CH1:RO；位位置：[11:0]；默认值：12'h800；*/
/*description:此寄存器存储从DMA FIFO弹出的数据。*/
#define DMA_INFIFO_RDATA_CH1  0x00000FFF
#define DMA_INFIFO_RDATA_CH1_M  ((DMA_INFIFO_RDATA_CH1_V)<<(DMA_INFIFO_RDATA_CH1_S))
#define DMA_INFIFO_RDATA_CH1_V  0xFFF
#define DMA_INFIFO_RDATA_CH1_S  0

#define DMA_IN_LINK_CH1_REG          (DR_REG_GDMA_BASE + 0x140)
/* DMA_INLINK_PARK_CH1:RO；位位置：[24]；默认值：1'h1；*/
/*description:1：内联描述符的FSM处于空闲状态。0:内联描述符的FSM正在工作。*/
#define DMA_INLINK_PARK_CH1  (BIT(24))
#define DMA_INLINK_PARK_CH1_M  (BIT(24))
#define DMA_INLINK_PARK_CH1_V  0x1
#define DMA_INLINK_PARK_CH1_S  24
/* DMA_INLINK_RESTART_CH1:R/W/SC；位位置：[23]；默认值：1’b0；*/
/*description:设置此位以装入新的内联描述符。*/
#define DMA_INLINK_RESTART_CH1  (BIT(23))
#define DMA_INLINK_RESTART_CH1_M  (BIT(23))
#define DMA_INLINK_RESTART_CH1_V  0x1
#define DMA_INLINK_RESTART_CH1_S  23
/* DMA_INLINK_START_CH1:R/W/SC；位位置：[22]；默认值：1’b0；*/
/*description:设置此位以开始处理内联描述符。*/
#define DMA_INLINK_START_CH1  (BIT(22))
#define DMA_INLINK_START_CH1_M  (BIT(22))
#define DMA_INLINK_START_CH1_V  0x1
#define DMA_INLINK_START_CH1_S  22
/* DMA_INLINK_STOP_CH1:R/W/SC；位位置：[21]；默认值：1’b0；*/
/*description:设置此位以停止处理内联描述符。*/
#define DMA_INLINK_STOP_CH1  (BIT(21))
#define DMA_INLINK_STOP_CH1_M  (BIT(21))
#define DMA_INLINK_STOP_CH1_V  0x1
#define DMA_INLINK_STOP_CH1_S  21
/* DMA_INLINK_AUTO_RET_CH1:R/W；位位置：[20]；默认值：1’b1；*/
/*description:当当前接收数据中存在一些错误时，设置此位以返回当前内联描述符的地址。*/
#define DMA_INLINK_AUTO_RET_CH1  (BIT(20))
#define DMA_INLINK_AUTO_RET_CH1_M  (BIT(20))
#define DMA_INLINK_AUTO_RET_CH1_V  0x1
#define DMA_INLINK_AUTO_RET_CH1_S  20
/* DMA_INLINK_ADDR_CH1:R/W；比特位置：[19:0]；默认值：20'00；*/
/*description:此寄存器存储第一个内联描述符地址的20个最低有效位。*/
#define DMA_INLINK_ADDR_CH1  0x000FFFFF
#define DMA_INLINK_ADDR_CH1_M  ((DMA_INLINK_ADDR_CH1_V)<<(DMA_INLINK_ADDR_CH1_S))
#define DMA_INLINK_ADDR_CH1_V  0xFFFFF
#define DMA_INLINK_ADDR_CH1_S  0

#define DMA_IN_STATE_CH1_REG          (DR_REG_GDMA_BASE + 0x144)
/* DMA_IN_STATE_CH1:RO；比特位置：[22:20]；默认值：3'b0；*/
/*description:保留*/
#define DMA_IN_STATE_CH1  0x00000007
#define DMA_IN_STATE_CH1_M  ((DMA_IN_STATE_CH1_V)<<(DMA_IN_STATE_CH1_S))
#define DMA_IN_STATE_CH1_V  0x7
#define DMA_IN_STATE_CH1_S  20
/* DMA_IN_DSCR_STATE_CH1:RO；比特位置：[19:18]；默认值：2’b0；*/
/*description:保留*/
#define DMA_IN_DSCR_STATE_CH1  0x00000003
#define DMA_IN_DSCR_STATE_CH1_M  ((DMA_IN_DSCR_STATE_CH1_V)<<(DMA_IN_DSCR_STATE_CH1_S))
#define DMA_IN_DSCR_STATE_CH1_V  0x3
#define DMA_IN_DSCR_STATE_CH1_S  18
/* DMA_INLINK_DSCR_ADDR_CH1:RO；比特位置：[17:00]；默认值：18'b0；*/
/*description:此寄存器存储当前内联描述符的地址。*/
#define DMA_INLINK_DSCR_ADDR_CH1  0x0003FFFF
#define DMA_INLINK_DSCR_ADDR_CH1_M  ((DMA_INLINK_DSCR_ADDR_CH1_V)<<(DMA_INLINK_DSCR_ADDR_CH1_S))
#define DMA_INLINK_DSCR_ADDR_CH1_V  0x3FFFF
#define DMA_INLINK_DSCR_ADDR_CH1_S  0

#define DMA_IN_SUC_EOF_DES_ADDR_CH1_REG          (DR_REG_GDMA_BASE + 0x148)
/* DMA_IN_SUC_EOF_DES_ADDR_CH1:RO；位位置：[31:0]；默认值：32'h0；*/
/*description:当此描述符中的EOF位为1时，此寄存器存储内联描述符的地址。*/
#define DMA_IN_SUC_EOF_DES_ADDR_CH1  0xFFFFFFFF
#define DMA_IN_SUC_EOF_DES_ADDR_CH1_M  ((DMA_IN_SUC_EOF_DES_ADDR_CH1_V)<<(DMA_IN_SUC_EOF_DES_ADDR_CH1_S))
#define DMA_IN_SUC_EOF_DES_ADDR_CH1_V  0xFFFFFFFF
#define DMA_IN_SUC_EOF_DES_ADDR_CH1_S  0

#define DMA_IN_ERR_EOF_DES_ADDR_CH1_REG          (DR_REG_GDMA_BASE + 0x14C)
/* DMA_IN_ERR_EOF_DES_ADDR_CH1:RO；位位置：[31:0]；默认值：32'h0；*/
/*description:当当前接收数据中存在一些错误时，此寄存器存储内联描述符的地址。仅当外围设备为UHCI0时使用。*/
#define DMA_IN_ERR_EOF_DES_ADDR_CH1  0xFFFFFFFF
#define DMA_IN_ERR_EOF_DES_ADDR_CH1_M  ((DMA_IN_ERR_EOF_DES_ADDR_CH1_V)<<(DMA_IN_ERR_EOF_DES_ADDR_CH1_S))
#define DMA_IN_ERR_EOF_DES_ADDR_CH1_V  0xFFFFFFFF
#define DMA_IN_ERR_EOF_DES_ADDR_CH1_S  0

#define DMA_IN_DSCR_CH1_REG          (DR_REG_GDMA_BASE + 0x150)
/* DMA_INLINK_DSCR_CH1:RO；位位置：[31:0]；默认值：32'b0；*/
/*description:当前内联描述符x的地址。*/
#define DMA_INLINK_DSCR_CH1  0xFFFFFFFF
#define DMA_INLINK_DSCR_CH1_M  ((DMA_INLINK_DSCR_CH1_V)<<(DMA_INLINK_DSCR_CH1_S))
#define DMA_INLINK_DSCR_CH1_V  0xFFFFFFFF
#define DMA_INLINK_DSCR_CH1_S  0

#define DMA_IN_DSCR_BF0_CH1_REG          (DR_REG_GDMA_BASE + 0x154)
/* DMA_INLINK_DSCR_BF0_CH1:RO；位位置：[31:0]；默认值：32'b0；*/
/*description:最后一个内联描述符x-1的地址。*/
#define DMA_INLINK_DSCR_BF0_CH1  0xFFFFFFFF
#define DMA_INLINK_DSCR_BF0_CH1_M  ((DMA_INLINK_DSCR_BF0_CH1_V)<<(DMA_INLINK_DSCR_BF0_CH1_S))
#define DMA_INLINK_DSCR_BF0_CH1_V  0xFFFFFFFF
#define DMA_INLINK_DSCR_BF0_CH1_S  0

#define DMA_IN_DSCR_BF1_CH1_REG          (DR_REG_GDMA_BASE + 0x158)
/* DMA_INLINK_DSCR_BF1_CH1:RO；位位置：[31:0]；默认值：32'b0；*/
/*description:倒数第二个内联描述符x-2的地址。*/
#define DMA_INLINK_DSCR_BF1_CH1  0xFFFFFFFF
#define DMA_INLINK_DSCR_BF1_CH1_M  ((DMA_INLINK_DSCR_BF1_CH1_V)<<(DMA_INLINK_DSCR_BF1_CH1_S))
#define DMA_INLINK_DSCR_BF1_CH1_V  0xFFFFFFFF
#define DMA_INLINK_DSCR_BF1_CH1_S  0

#define DMA_IN_PRI_CH1_REG          (DR_REG_GDMA_BASE + 0x15C)
/* DMA_RX_PRI_CH1:R/W；位位置：[3:0]；默认值：4'b0；*/
/*description:Rx通道1的优先级。值越大，优先级越高。*/
#define DMA_RX_PRI_CH1  0x0000000F
#define DMA_RX_PRI_CH1_M  ((DMA_RX_PRI_CH1_V)<<(DMA_RX_PRI_CH1_S))
#define DMA_RX_PRI_CH1_V  0xF
#define DMA_RX_PRI_CH1_S  0

#define DMA_IN_PERI_SEL_CH1_REG          (DR_REG_GDMA_BASE + 0x160)
/* DMA_PERI_IN_SEL_CH1:R/W；比特位置：[5:0]；默认值：6'h3F；*/
/*描述：此寄存器用于为Rx通道1选择外围设备。0：SPI2。1：保留。2： UHCI0.3:I2S0.4：保留。5： 保留。6： AES。7： 沙。8： ADC_DAC。*/
#define DMA_PERI_IN_SEL_CH1  0x0000003F
#define DMA_PERI_IN_SEL_CH1_M  ((DMA_PERI_IN_SEL_CH1_V)<<(DMA_PERI_IN_SEL_CH1_S))
#define DMA_PERI_IN_SEL_CH1_V  0x3F
#define DMA_PERI_IN_SEL_CH1_S  0

#define DMA_OUT_CONF0_CH1_REG          (DR_REG_GDMA_BASE + 0x190)
/* DMA_OUT_DATA_BURST_EN_CH1:R/W；位位置：[5]；默认值：1’b0；*/
/*description:将此位设置为1，以便在访问内部SRAM时为传输数据的Tx信道1启用INCR突发传输。*/
#define DMA_OUT_DATA_BURST_EN_CH1  (BIT(5))
#define DMA_OUT_DATA_BURST_EN_CH1_M  (BIT(5))
#define DMA_OUT_DATA_BURST_EN_CH1_V  0x1
#define DMA_OUT_DATA_BURST_EN_CH1_S  5
/* DMA_OUTDSCR_BURST_EN_CH1:R/W；位位置：[4]；默认值：1’b0；*/
/*description:将此位设置为1，以便在访问内部SRAM时，为Tx信道1读取链路描述符启用INCR突发传输。*/
#define DMA_OUTDSCR_BURST_EN_CH1  (BIT(4))
#define DMA_OUTDSCR_BURST_EN_CH1_M  (BIT(4))
#define DMA_OUTDSCR_BURST_EN_CH1_V  0x1
#define DMA_OUTDSCR_BURST_EN_CH1_S  4
/* DMA_OUT_EOF_MODE_CH1:R/W；位位置：[3]；默认值：1’b1；*/
/*描述：传输数据时EOF标志生成模式。1： 当需要传输的数据从DMA中的FIFO弹出时，生成Tx信道1的EOF标志*/
#define DMA_OUT_EOF_MODE_CH1  (BIT(3))
#define DMA_OUT_EOF_MODE_CH1_M  (BIT(3))
#define DMA_OUT_EOF_MODE_CH1_V  0x1
#define DMA_OUT_EOF_MODE_CH1_S  3
/* DMA_OUT_AUTO_WRBACK_CH1:R/W；位位置：[2]；默认值：1’b0；*/
/*description:设置此位以在传输tx缓冲区中的所有数据时启用自动outlink写回。*/
#define DMA_OUT_AUTO_WRBACK_CH1  (BIT(2))
#define DMA_OUT_AUTO_WRBACK_CH1_M  (BIT(2))
#define DMA_OUT_AUTO_WRBACK_CH1_V  0x1
#define DMA_OUT_AUTO_WRBACK_CH1_S  2
/* DMA_OUT_LOOP_TEST_CH1:R/W；位位置：[1]；默认值：1’b0；*/
/*description:保留*/
#define DMA_OUT_LOOP_TEST_CH1  (BIT(1))
#define DMA_OUT_LOOP_TEST_CH1_M  (BIT(1))
#define DMA_OUT_LOOP_TEST_CH1_V  0x1
#define DMA_OUT_LOOP_TEST_CH1_S  1
/* DMA_OUT_RST_CH1:R/W；位位置：[0]；默认值：1’b0；*/
/*描述：此位用于重置DMA通道1 Tx FSM和Tx FIFO指针。*/
#define DMA_OUT_RST_CH1  (BIT(0))
#define DMA_OUT_RST_CH1_M  (BIT(0))
#define DMA_OUT_RST_CH1_V  0x1
#define DMA_OUT_RST_CH1_S  0

#define DMA_OUT_CONF1_CH1_REG          (DR_REG_GDMA_BASE + 0x194)
/* DMA_OUT_CHECK_OWNER_CH1:R/W；位位置：[12]；默认值：1’b0；*/
/*description:设置此位以启用检查链接描述符的所有者属性。*/
#define DMA_OUT_CHECK_OWNER_CH1  (BIT(12))
#define DMA_OUT_CHECK_OWNER_CH1_M  (BIT(12))
#define DMA_OUT_CHECK_OWNER_CH1_V  0x1
#define DMA_OUT_CHECK_OWNER_CH1_S  12

#define DMA_OUTFIFO_STATUS_CH1_REG          (DR_REG_GDMA_BASE + 0x198)
/* DMA_OUT_REMAIN_UNDER_4B_CH1:RO；位位置：[26]；默认值：1’b1；*/
/*description:保留*/
#define DMA_OUT_REMAIN_UNDER_4B_CH1  (BIT(26))
#define DMA_OUT_REMAIN_UNDER_4B_CH1_M  (BIT(26))
#define DMA_OUT_REMAIN_UNDER_4B_CH1_V  0x1
#define DMA_OUT_REMAIN_UNDER_4B_CH1_S  26
/* DMA_OUT_REMAIN_UNDER_3B_CH1:RO；位位置：[25]；默认值：1’b1；*/
/*description:保留*/
#define DMA_OUT_REMAIN_UNDER_3B_CH1  (BIT(25))
#define DMA_OUT_REMAIN_UNDER_3B_CH1_M  (BIT(25))
#define DMA_OUT_REMAIN_UNDER_3B_CH1_V  0x1
#define DMA_OUT_REMAIN_UNDER_3B_CH1_S  25
/* DMA_OUT_REMAIN_UNDER_2B_CH1:RO；位位置：[24]；默认值：1’b1；*/
/*description:保留*/
#define DMA_OUT_REMAIN_UNDER_2B_CH1  (BIT(24))
#define DMA_OUT_REMAIN_UNDER_2B_CH1_M  (BIT(24))
#define DMA_OUT_REMAIN_UNDER_2B_CH1_V  0x1
#define DMA_OUT_REMAIN_UNDER_2B_CH1_S  24
/* DMA_OUT_REMAIN_UNDER_1B_CH1:RO；位位置：[23]；默认值：1’b1；*/
/*description:保留*/
#define DMA_OUT_REMAIN_UNDER_1B_CH1  (BIT(23))
#define DMA_OUT_REMAIN_UNDER_1B_CH1_M  (BIT(23))
#define DMA_OUT_REMAIN_UNDER_1B_CH1_V  0x1
#define DMA_OUT_REMAIN_UNDER_1B_CH1_S  23
/* DMA_OUTFIFO_CNT_CH1:RO；位位置：[7:2]；默认值：6'b0；*/
/*描述：寄存器将数据的字节数存储在Tx信道1的L1 Tx FIFO中。*/
#define DMA_OUTFIFO_CNT_CH1  0x0000003F
#define DMA_OUTFIFO_CNT_CH1_M  ((DMA_OUTFIFO_CNT_CH1_V)<<(DMA_OUTFIFO_CNT_CH1_S))
#define DMA_OUTFIFO_CNT_CH1_V  0x3F
#define DMA_OUTFIFO_CNT_CH1_S  2
/* DMA_OUTFIFO_EMPTY_CH1:RO；位位置：[1]；默认值：1’b1；*/
/*描述：Tx信道1的L1 Tx FIFO空信号。*/
#define DMA_OUTFIFO_EMPTY_CH1  (BIT(1))
#define DMA_OUTFIFO_EMPTY_CH1_M  (BIT(1))
#define DMA_OUTFIFO_EMPTY_CH1_V  0x1
#define DMA_OUTFIFO_EMPTY_CH1_S  1
/* DMA_OUTFIFO_FULL_CH1:RO；位位置：[0]；默认值：1’b0；*/
/*描述：Tx信道1的L1 Tx FIFO满信号。*/
#define DMA_OUTFIFO_FULL_CH1  (BIT(0))
#define DMA_OUTFIFO_FULL_CH1_M  (BIT(0))
#define DMA_OUTFIFO_FULL_CH1_V  0x1
#define DMA_OUTFIFO_FULL_CH1_S  0

#define DMA_OUT_PUSH_CH1_REG          (DR_REG_GDMA_BASE + 0x19C)
/* DMA_OUTFIFO_PUSH_CH1:R/W/SC；位位置：[9]；默认值：1'0；*/
/*description:设置此位以将数据推入DMA FIFO。*/
#define DMA_OUTFIFO_PUSH_CH1  (BIT(9))
#define DMA_OUTFIFO_PUSH_CH1_M  (BIT(9))
#define DMA_OUTFIFO_PUSH_CH1_V  0x1
#define DMA_OUTFIFO_PUSH_CH1_S  9
/* DMA_OUTFIFO_WDATA_CH1:R/W；位位置：[8:0]；默认值：9'0；*/
/*description:此寄存器存储需要推入DMA FIFO的数据。*/
#define DMA_OUTFIFO_WDATA_CH1  0x000001FF
#define DMA_OUTFIFO_WDATA_CH1_M  ((DMA_OUTFIFO_WDATA_CH1_V)<<(DMA_OUTFIFO_WDATA_CH1_S))
#define DMA_OUTFIFO_WDATA_CH1_V  0x1FF
#define DMA_OUTFIFO_WDATA_CH1_S  0

#define DMA_OUT_LINK_CH1_REG          (DR_REG_GDMA_BASE + 0x1A0)
/* DMA_OUTLINK_PARK_CH1:RO；位位置：[23]；默认值：1'h1；*/
/*描述：1:outlink描述符的FSM处于空闲状态。0:outlink描述符的FSM正在工作。*/
#define DMA_OUTLINK_PARK_CH1  (BIT(23))
#define DMA_OUTLINK_PARK_CH1_M  (BIT(23))
#define DMA_OUTLINK_PARK_CH1_V  0x1
#define DMA_OUTLINK_PARK_CH1_S  23
/* DMA_OUTLINK_RESTART_CH1:R/W/SC；位位置：[22]；默认值：1’b0；*/
/*description:设置此位以从上一个地址重新启动新的outlink。*/
#define DMA_OUTLINK_RESTART_CH1  (BIT(22))
#define DMA_OUTLINK_RESTART_CH1_M  (BIT(22))
#define DMA_OUTLINK_RESTART_CH1_V  0x1
#define DMA_OUTLINK_RESTART_CH1_S  22
/* DMA_OUTLINK_START_CH1:R/W/SC；位位置：[21]；默认值：1’b0；*/
/*description:设置此位以开始处理outlink描述符。*/
#define DMA_OUTLINK_START_CH1  (BIT(21))
#define DMA_OUTLINK_START_CH1_M  (BIT(21))
#define DMA_OUTLINK_START_CH1_V  0x1
#define DMA_OUTLINK_START_CH1_S  21
/* DMA_OUTLINK_STOP_CH1:R/W/SC；位位置：[20]；默认值：1’b0；*/
/*description:设置此位以停止处理outlink描述符。*/
#define DMA_OUTLINK_STOP_CH1  (BIT(20))
#define DMA_OUTLINK_STOP_CH1_M  (BIT(20))
#define DMA_OUTLINK_STOP_CH1_V  0x1
#define DMA_OUTLINK_STOP_CH1_S  20
/* DMA_OUTLINK_ADDR_CH1:R/W；比特位置：[19:0]；默认值：20'00；*/
/*description:此寄存器存储第一个outlink描述符地址的20个最低有效位。*/
#define DMA_OUTLINK_ADDR_CH1  0x000FFFFF
#define DMA_OUTLINK_ADDR_CH1_M  ((DMA_OUTLINK_ADDR_CH1_V)<<(DMA_OUTLINK_ADDR_CH1_S))
#define DMA_OUTLINK_ADDR_CH1_V  0xFFFFF
#define DMA_OUTLINK_ADDR_CH1_S  0

#define DMA_OUT_STATE_CH1_REG          (DR_REG_GDMA_BASE + 0x1A4)
/* DMA_OUT_STATE_CH1:RO；比特位置：[22:20]；默认值：3'b0；*/
/*description:保留*/
#define DMA_OUT_STATE_CH1  0x00000007
#define DMA_OUT_STATE_CH1_M  ((DMA_OUT_STATE_CH1_V)<<(DMA_OUT_STATE_CH1_S))
#define DMA_OUT_STATE_CH1_V  0x7
#define DMA_OUT_STATE_CH1_S  20
/* DMA_OUT_DSCR_STATE_CH1:RO；比特位置：[19:18]；默认值：2’b0；*/
/*description:保留*/
#define DMA_OUT_DSCR_STATE_CH1  0x00000003
#define DMA_OUT_DSCR_STATE_CH1_M  ((DMA_OUT_DSCR_STATE_CH1_V)<<(DMA_OUT_DSCR_STATE_CH1_S))
#define DMA_OUT_DSCR_STATE_CH1_V  0x3
#define DMA_OUT_DSCR_STATE_CH1_S  18
/* DMA_OUTLINK_DSCR_ADDR_CH1:RO；比特位置：[17:00]；默认值：18'b0；*/
/*description:此寄存器存储当前outlink描述符的地址。*/
#define DMA_OUTLINK_DSCR_ADDR_CH1  0x0003FFFF
#define DMA_OUTLINK_DSCR_ADDR_CH1_M  ((DMA_OUTLINK_DSCR_ADDR_CH1_V)<<(DMA_OUTLINK_DSCR_ADDR_CH1_S))
#define DMA_OUTLINK_DSCR_ADDR_CH1_V  0x3FFFF
#define DMA_OUTLINK_DSCR_ADDR_CH1_S  0

#define DMA_OUT_EOF_DES_ADDR_CH1_REG          (DR_REG_GDMA_BASE + 0x1A8)
/* DMA_OUT_EOF_DES_ADDR_CH1:RO；位位置：[31:0]；默认值：32'h0；*/
/*description:当此描述符中的EOF位为1时，此寄存器存储outlink描述符的地址。*/
#define DMA_OUT_EOF_DES_ADDR_CH1  0xFFFFFFFF
#define DMA_OUT_EOF_DES_ADDR_CH1_M  ((DMA_OUT_EOF_DES_ADDR_CH1_V)<<(DMA_OUT_EOF_DES_ADDR_CH1_S))
#define DMA_OUT_EOF_DES_ADDR_CH1_V  0xFFFFFFFF
#define DMA_OUT_EOF_DES_ADDR_CH1_S  0

#define DMA_OUT_EOF_BFR_DES_ADDR_CH1_REG          (DR_REG_GDMA_BASE + 0x1AC)
/* DMA_OUT_EOF_BFR_DES_ADDR_CH1:RO；位位置：[31:0]；默认值：32'h0；*/
/*description:此寄存器存储最后一个outlink描述符之前的outlink描述符的地址。*/
#define DMA_OUT_EOF_BFR_DES_ADDR_CH1  0xFFFFFFFF
#define DMA_OUT_EOF_BFR_DES_ADDR_CH1_M  ((DMA_OUT_EOF_BFR_DES_ADDR_CH1_V)<<(DMA_OUT_EOF_BFR_DES_ADDR_CH1_S))
#define DMA_OUT_EOF_BFR_DES_ADDR_CH1_V  0xFFFFFFFF
#define DMA_OUT_EOF_BFR_DES_ADDR_CH1_S  0

#define DMA_OUT_DSCR_CH1_REG          (DR_REG_GDMA_BASE + 0x1B0)
/* DMA_OUTLINK_DSCR_CH1:RO；位位置：[31:0]；默认值：32'b0；*/
/*description:当前outlink描述符y的地址。*/
#define DMA_OUTLINK_DSCR_CH1  0xFFFFFFFF
#define DMA_OUTLINK_DSCR_CH1_M  ((DMA_OUTLINK_DSCR_CH1_V)<<(DMA_OUTLINK_DSCR_CH1_S))
#define DMA_OUTLINK_DSCR_CH1_V  0xFFFFFFFF
#define DMA_OUTLINK_DSCR_CH1_S  0

#define DMA_OUT_DSCR_BF0_CH1_REG          (DR_REG_GDMA_BASE + 0x1B4)
/* DMA_OUTLINK_DSCR_BF0_CH1:RO；位位置：[31:0]；默认值：32'b0；*/
/*description:最后一个outlink描述符y-1的地址。*/
#define DMA_OUTLINK_DSCR_BF0_CH1  0xFFFFFFFF
#define DMA_OUTLINK_DSCR_BF0_CH1_M  ((DMA_OUTLINK_DSCR_BF0_CH1_V)<<(DMA_OUTLINK_DSCR_BF0_CH1_S))
#define DMA_OUTLINK_DSCR_BF0_CH1_V  0xFFFFFFFF
#define DMA_OUTLINK_DSCR_BF0_CH1_S  0

#define DMA_OUT_DSCR_BF1_CH1_REG          (DR_REG_GDMA_BASE + 0x1B8)
/* DMA_OUTLINK_DSCR_BF1_CH1:RO；位位置：[31:0]；默认值：32'b0；*/
/*description:倒数第二个内联描述符x-2的地址。*/
#define DMA_OUTLINK_DSCR_BF1_CH1  0xFFFFFFFF
#define DMA_OUTLINK_DSCR_BF1_CH1_M  ((DMA_OUTLINK_DSCR_BF1_CH1_V)<<(DMA_OUTLINK_DSCR_BF1_CH1_S))
#define DMA_OUTLINK_DSCR_BF1_CH1_V  0xFFFFFFFF
#define DMA_OUTLINK_DSCR_BF1_CH1_S  0

#define DMA_OUT_PRI_CH1_REG          (DR_REG_GDMA_BASE + 0x1BC)
/* DMA_TX_PRI_CH1:R/W；位位置：[3:0]；默认值：4'b0；*/
/*description:Tx信道1的优先级。值越大，优先级越高。*/
#define DMA_TX_PRI_CH1  0x0000000F
#define DMA_TX_PRI_CH1_M  ((DMA_TX_PRI_CH1_V)<<(DMA_TX_PRI_CH1_S))
#define DMA_TX_PRI_CH1_V  0xF
#define DMA_TX_PRI_CH1_S  0

#define DMA_OUT_PERI_SEL_CH1_REG          (DR_REG_GDMA_BASE + 0x1C0)
/* DMA_PERI_OUT_SEL_CH1:R/W；比特位置：[5:0]；默认值：6'h3F；*/
/*description:此寄存器用于为Tx信道1选择外设。0:SPI2.1:保留。2： UHCI0.3:I2S0.4：保留。5： 保留。6： AES。7： 沙。8： ADC_DAC。*/
#define DMA_PERI_OUT_SEL_CH1  0x0000003F
#define DMA_PERI_OUT_SEL_CH1_M  ((DMA_PERI_OUT_SEL_CH1_V)<<(DMA_PERI_OUT_SEL_CH1_S))
#define DMA_PERI_OUT_SEL_CH1_V  0x3F
#define DMA_PERI_OUT_SEL_CH1_S  0

#define DMA_IN_CONF0_CH2_REG          (DR_REG_GDMA_BASE + 0x1F0)
/* DMA_MEM_TRANS_EN_CH2:R/W；位位置：[4]；默认值：1’b0；*/
/*description:将此位设置为1，以启用通过DMA将数据从存储器自动传输到存储器。*/
#define DMA_MEM_TRANS_EN_CH2  (BIT(4))
#define DMA_MEM_TRANS_EN_CH2_M  (BIT(4))
#define DMA_MEM_TRANS_EN_CH2_V  0x1
#define DMA_MEM_TRANS_EN_CH2_S  4
/* DMA_IN_DATA_BURST_EN_CH2:R/W；位位置：[3]；默认值：1’b0；*/
/*description:将此位设置为1，以在访问内部SRAM时启用接收数据的Rx通道2的INCR突发传输。*/
#define DMA_IN_DATA_BURST_EN_CH2  (BIT(3))
#define DMA_IN_DATA_BURST_EN_CH2_M  (BIT(3))
#define DMA_IN_DATA_BURST_EN_CH2_V  0x1
#define DMA_IN_DATA_BURST_EN_CH2_S  3
/* DMA_INDSCR_BURST_EN_CH2:R/W；位位置：[2]；默认值：1’b0；*/
/*description:当访问内部SRAM时，将此位设置为1以启用Rx通道2读取链路描述符的INCR突发传输。*/
#define DMA_INDSCR_BURST_EN_CH2  (BIT(2))
#define DMA_INDSCR_BURST_EN_CH2_M  (BIT(2))
#define DMA_INDSCR_BURST_EN_CH2_V  0x1
#define DMA_INDSCR_BURST_EN_CH2_S  2
/* DMA_IN_LOOP_TEST_CH2:R/W；位位置：[1]；默认值：1’b0；*/
/*description:保留*/
#define DMA_IN_LOOP_TEST_CH2  (BIT(1))
#define DMA_IN_LOOP_TEST_CH2_M  (BIT(1))
#define DMA_IN_LOOP_TEST_CH2_V  0x1
#define DMA_IN_LOOP_TEST_CH2_S  1
/* DMA_IN_RST_CH2:R/W；位位置：[0]；默认值：1'0；*/
/*描述：此位用于重置DMA通道2 Rx FSM和Rx FIFO指针。*/
#define DMA_IN_RST_CH2  (BIT(0))
#define DMA_IN_RST_CH2_M  (BIT(0))
#define DMA_IN_RST_CH2_V  0x1
#define DMA_IN_RST_CH2_S  0

#define DMA_IN_CONF1_CH2_REG          (DR_REG_GDMA_BASE + 0x1F4)
/* DMA_IN_CHECK_OWNER_CH2:R/W；位位置：[12]；默认值：1’b0；*/
/*description:设置此位以启用检查链接描述符的所有者属性。*/
#define DMA_IN_CHECK_OWNER_CH2  (BIT(12))
#define DMA_IN_CHECK_OWNER_CH2_M  (BIT(12))
#define DMA_IN_CHECK_OWNER_CH2_V  0x1
#define DMA_IN_CHECK_OWNER_CH2_S  12

#define DMA_INFIFO_STATUS_CH2_REG          (DR_REG_GDMA_BASE + 0x1F8)
/* DMA_IN_BUF_HUNGRY_CH2:RO；位位置：[27]；默认值：1’b0；*/
/*description:保留*/
#define DMA_IN_BUF_HUNGRY_CH2  (BIT(27))
#define DMA_IN_BUF_HUNGRY_CH2_M  (BIT(27))
#define DMA_IN_BUF_HUNGRY_CH2_V  0x1
#define DMA_IN_BUF_HUNGRY_CH2_S  27
/* DMA_IN_REMAIN_UNDER_4B_CH2:RO；位位置：[26]；默认值：1’b1；*/
/*description:保留*/
#define DMA_IN_REMAIN_UNDER_4B_CH2  (BIT(26))
#define DMA_IN_REMAIN_UNDER_4B_CH2_M  (BIT(26))
#define DMA_IN_REMAIN_UNDER_4B_CH2_V  0x1
#define DMA_IN_REMAIN_UNDER_4B_CH2_S  26
/* DMA_IN_REMAIN_UNDER_3B_CH2:RO；位位置：[25]；默认值：1’b1；*/
/*description:保留*/
#define DMA_IN_REMAIN_UNDER_3B_CH2  (BIT(25))
#define DMA_IN_REMAIN_UNDER_3B_CH2_M  (BIT(25))
#define DMA_IN_REMAIN_UNDER_3B_CH2_V  0x1
#define DMA_IN_REMAIN_UNDER_3B_CH2_S  25
/* DMA_IN_REMAIN_UNDER_2B_CH2:RO；位位置：[24]；默认值：1’b1；*/
/*description:保留*/
#define DMA_IN_REMAIN_UNDER_2B_CH2  (BIT(24))
#define DMA_IN_REMAIN_UNDER_2B_CH2_M  (BIT(24))
#define DMA_IN_REMAIN_UNDER_2B_CH2_V  0x1
#define DMA_IN_REMAIN_UNDER_2B_CH2_S  24
/* DMA_IN_REMAIN_UNDER_1B_CH2:RO；位位置：[23]；默认值：1’b1；*/
/*description:保留*/
#define DMA_IN_REMAIN_UNDER_1B_CH2  (BIT(23))
#define DMA_IN_REMAIN_UNDER_1B_CH2_M  (BIT(23))
#define DMA_IN_REMAIN_UNDER_1B_CH2_V  0x1
#define DMA_IN_REMAIN_UNDER_1B_CH2_S  23
/* DMA_INFIFO_CNT_CH2:RO；位位置：[7:2]；默认值：6'b0；*/
/*描述：寄存器将数据的字节数存储在Rx信道2的L1 Rx FIFO中。*/
#define DMA_INFIFO_CNT_CH2  0x0000003F
#define DMA_INFIFO_CNT_CH2_M  ((DMA_INFIFO_CNT_CH2_V)<<(DMA_INFIFO_CNT_CH2_S))
#define DMA_INFIFO_CNT_CH2_V  0x3F
#define DMA_INFIFO_CNT_CH2_S  2
/* DMA_INFIFO_EMPTY-CH2:RO；位位置：[1]；默认值：1’b1；*/
/*描述：Rx信道2的L1 Rx FIFO空信号。*/
#define DMA_INFIFO_EMPTY_CH2  (BIT(1))
#define DMA_INFIFO_EMPTY_CH2_M  (BIT(1))
#define DMA_INFIFO_EMPTY_CH2_V  0x1
#define DMA_INFIFO_EMPTY_CH2_S  1
/* DMA_INFIFO_FULL_CH2:RO；位位置：[0]；默认值：1’b1；*/
/*描述：Rx信道2的L1 Rx FIFO满信号。*/
#define DMA_INFIFO_FULL_CH2  (BIT(0))
#define DMA_INFIFO_FULL_CH2_M  (BIT(0))
#define DMA_INFIFO_FULL_CH2_V  0x1
#define DMA_INFIFO_FULL_CH2_S  0

#define DMA_IN_POP_CH2_REG          (DR_REG_GDMA_BASE + 0x1FC)
/* DMA_INFIFO_POP_CH2:R/W/SC；位位置：[12]；默认值：1'0；*/
/*description:设置此位以从DMA FIFO弹出数据。*/
#define DMA_INFIFO_POP_CH2  (BIT(12))
#define DMA_INFIFO_POP_CH2_M  (BIT(12))
#define DMA_INFIFO_POP_CH2_V  0x1
#define DMA_INFIFO_POP_CH2_S  12
/* DMA_INFIFO_data_CH2:RO；位位置：[11:0]；默认值：12'h800；*/
/*description:此寄存器存储从DMA FIFO弹出的数据。*/
#define DMA_INFIFO_RDATA_CH2  0x00000FFF
#define DMA_INFIFO_RDATA_CH2_M  ((DMA_INFIFO_RDATA_CH2_V)<<(DMA_INFIFO_RDATA_CH2_S))
#define DMA_INFIFO_RDATA_CH2_V  0xFFF
#define DMA_INFIFO_RDATA_CH2_S  0

#define DMA_IN_LINK_CH2_REG          (DR_REG_GDMA_BASE + 0x200)
/* DMA_INLINK_PARK_CH2:RO；位位置：[24]；默认值：1'h1；*/
/*description:1：内联描述符的FSM处于空闲状态。0:内联描述符的FSM正在工作。*/
#define DMA_INLINK_PARK_CH2  (BIT(24))
#define DMA_INLINK_PARK_CH2_M  (BIT(24))
#define DMA_INLINK_PARK_CH2_V  0x1
#define DMA_INLINK_PARK_CH2_S  24
/* DMA_INLINK_RESTART_CH2:R/W/SC；位位置：[23]；默认值：1’b0；*/
/*description:设置此位以装入新的内联描述符。*/
#define DMA_INLINK_RESTART_CH2  (BIT(23))
#define DMA_INLINK_RESTART_CH2_M  (BIT(23))
#define DMA_INLINK_RESTART_CH2_V  0x1
#define DMA_INLINK_RESTART_CH2_S  23
/* DMA_INLINK_START_CH2:R/W/SC；位位置：[22]；默认值：1’b0；*/
/*description:设置此位以开始处理内联描述符。*/
#define DMA_INLINK_START_CH2  (BIT(22))
#define DMA_INLINK_START_CH2_M  (BIT(22))
#define DMA_INLINK_START_CH2_V  0x1
#define DMA_INLINK_START_CH2_S  22
/* DMA_INLINK_STOP_CH2:R/W/SC；位位置：[21]；默认值：1’b0；*/
/*description:设置此位以停止处理内联描述符。*/
#define DMA_INLINK_STOP_CH2  (BIT(21))
#define DMA_INLINK_STOP_CH2_M  (BIT(21))
#define DMA_INLINK_STOP_CH2_V  0x1
#define DMA_INLINK_STOP_CH2_S  21
/* DMA_INLINK_AUTO_RET_CH2:R/W；位位置：[20]；默认值：1’b1；*/
/*description:当当前接收数据中存在一些错误时，设置此位以返回当前内联描述符的地址。*/
#define DMA_INLINK_AUTO_RET_CH2  (BIT(20))
#define DMA_INLINK_AUTO_RET_CH2_M  (BIT(20))
#define DMA_INLINK_AUTO_RET_CH2_V  0x1
#define DMA_INLINK_AUTO_RET_CH2_S  20
/* DMA_INLINK_ADDR_CH2:R/W；比特位置：[19:0]；默认值：20'00；*/
/*description:此寄存器存储第一个内联描述符地址的20个最低有效位。*/
#define DMA_INLINK_ADDR_CH2  0x000FFFFF
#define DMA_INLINK_ADDR_CH2_M  ((DMA_INLINK_ADDR_CH2_V)<<(DMA_INLINK_ADDR_CH2_S))
#define DMA_INLINK_ADDR_CH2_V  0xFFFFF
#define DMA_INLINK_ADDR_CH2_S  0

#define DMA_IN_STATE_CH2_REG          (DR_REG_GDMA_BASE + 0x204)
/* DMA_IN_STATE_CH2:RO；比特位置：[22:20]；默认值：3'b0；*/
/*description:保留*/
#define DMA_IN_STATE_CH2  0x00000007
#define DMA_IN_STATE_CH2_M  ((DMA_IN_STATE_CH2_V)<<(DMA_IN_STATE_CH2_S))
#define DMA_IN_STATE_CH2_V  0x7
#define DMA_IN_STATE_CH2_S  20
/* DMA_IN_DSCR_STATE_CH2:RO；比特位置：[19:18]；默认值：2’b0；*/
/*description:保留*/
#define DMA_IN_DSCR_STATE_CH2  0x00000003
#define DMA_IN_DSCR_STATE_CH2_M  ((DMA_IN_DSCR_STATE_CH2_V)<<(DMA_IN_DSCR_STATE_CH2_S))
#define DMA_IN_DSCR_STATE_CH2_V  0x3
#define DMA_IN_DSCR_STATE_CH2_S  18
/* DMA_INLINK_DSCR_ADDR_CH2:RO；比特位置：[17:00]；默认值：18'b0；*/
/*description:此寄存器存储当前内联描述符的地址。*/
#define DMA_INLINK_DSCR_ADDR_CH2  0x0003FFFF
#define DMA_INLINK_DSCR_ADDR_CH2_M  ((DMA_INLINK_DSCR_ADDR_CH2_V)<<(DMA_INLINK_DSCR_ADDR_CH2_S))
#define DMA_INLINK_DSCR_ADDR_CH2_V  0x3FFFF
#define DMA_INLINK_DSCR_ADDR_CH2_S  0

#define DMA_IN_SUC_EOF_DES_ADDR_CH2_REG          (DR_REG_GDMA_BASE + 0x208)
/* DMA_IN_SUC_EOF_DES_ADDR_CH2:RO；位位置：[31:0]；默认值：32'h0；*/
/*description:当此描述符中的EOF位为1时，此寄存器存储内联描述符的地址。*/
#define DMA_IN_SUC_EOF_DES_ADDR_CH2  0xFFFFFFFF
#define DMA_IN_SUC_EOF_DES_ADDR_CH2_M  ((DMA_IN_SUC_EOF_DES_ADDR_CH2_V)<<(DMA_IN_SUC_EOF_DES_ADDR_CH2_S))
#define DMA_IN_SUC_EOF_DES_ADDR_CH2_V  0xFFFFFFFF
#define DMA_IN_SUC_EOF_DES_ADDR_CH2_S  0

#define DMA_IN_ERR_EOF_DES_ADDR_CH2_REG          (DR_REG_GDMA_BASE + 0x20C)
/* DMA_IN_ERR_EOF_DES_ADDR_CH2:RO；位位置：[31:0]；默认值：32'h0；*/
/*description:当当前接收数据中存在一些错误时，此寄存器存储内联描述符的地址。仅当外围设备为UHCI0时使用。*/
#define DMA_IN_ERR_EOF_DES_ADDR_CH2  0xFFFFFFFF
#define DMA_IN_ERR_EOF_DES_ADDR_CH2_M  ((DMA_IN_ERR_EOF_DES_ADDR_CH2_V)<<(DMA_IN_ERR_EOF_DES_ADDR_CH2_S))
#define DMA_IN_ERR_EOF_DES_ADDR_CH2_V  0xFFFFFFFF
#define DMA_IN_ERR_EOF_DES_ADDR_CH2_S  0

#define DMA_IN_DSCR_CH2_REG          (DR_REG_GDMA_BASE + 0x210)
/* DMA_INLINK_DSCR_CH2:RO；位位置：[31:0]；默认值：32'b0；*/
/*description:当前内联描述符x的地址。*/
#define DMA_INLINK_DSCR_CH2  0xFFFFFFFF
#define DMA_INLINK_DSCR_CH2_M  ((DMA_INLINK_DSCR_CH2_V)<<(DMA_INLINK_DSCR_CH2_S))
#define DMA_INLINK_DSCR_CH2_V  0xFFFFFFFF
#define DMA_INLINK_DSCR_CH2_S  0

#define DMA_IN_DSCR_BF0_CH2_REG          (DR_REG_GDMA_BASE + 0x214)
/* DMA_INLINK_DSCR_BF0_CH2:RO；位位置：[31:0]；默认值：32'b0；*/
/*description:最后一个内联描述符x-1的地址。*/
#define DMA_INLINK_DSCR_BF0_CH2  0xFFFFFFFF
#define DMA_INLINK_DSCR_BF0_CH2_M  ((DMA_INLINK_DSCR_BF0_CH2_V)<<(DMA_INLINK_DSCR_BF0_CH2_S))
#define DMA_INLINK_DSCR_BF0_CH2_V  0xFFFFFFFF
#define DMA_INLINK_DSCR_BF0_CH2_S  0

#define DMA_IN_DSCR_BF1_CH2_REG          (DR_REG_GDMA_BASE + 0x218)
/* DMA_INLINK_DSCR_BF1_CH2:RO；位位置：[31:0]；默认值：32'b0；*/
/*description:倒数第二个内联描述符x-2的地址。*/
#define DMA_INLINK_DSCR_BF1_CH2  0xFFFFFFFF
#define DMA_INLINK_DSCR_BF1_CH2_M  ((DMA_INLINK_DSCR_BF1_CH2_V)<<(DMA_INLINK_DSCR_BF1_CH2_S))
#define DMA_INLINK_DSCR_BF1_CH2_V  0xFFFFFFFF
#define DMA_INLINK_DSCR_BF1_CH2_S  0

#define DMA_IN_PRI_CH2_REG          (DR_REG_GDMA_BASE + 0x21C)
/* DMA_RX_PRI_CH2:R/W；位位置：[3:0]；默认值：4'b0；*/
/*description:Rx通道2的优先级。值越大，优先级越高。*/
#define DMA_RX_PRI_CH2  0x0000000F
#define DMA_RX_PRI_CH2_M  ((DMA_RX_PRI_CH2_V)<<(DMA_RX_PRI_CH2_S))
#define DMA_RX_PRI_CH2_V  0xF
#define DMA_RX_PRI_CH2_S  0

#define DMA_IN_PERI_SEL_CH2_REG          (DR_REG_GDMA_BASE + 0x220)
/* DMA_PERI_IN_SEL_CH2:R/W；比特位置：[5:0]；默认值：6'h3F；*/
/*描述：此寄存器用于为Rx通道2选择外围设备。0:SPI2.1:保留。2： UHCI0.3:I2S0.4：保留。5： 保留。6： AES。7： 沙。8： ADC_DAC。*/
#define DMA_PERI_IN_SEL_CH2  0x0000003F
#define DMA_PERI_IN_SEL_CH2_M  ((DMA_PERI_IN_SEL_CH2_V)<<(DMA_PERI_IN_SEL_CH2_S))
#define DMA_PERI_IN_SEL_CH2_V  0x3F
#define DMA_PERI_IN_SEL_CH2_S  0

#define DMA_OUT_CONF0_CH2_REG          (DR_REG_GDMA_BASE + 0x250)
/* DMA_OUT_DATA_BURST_EN_CH2:R/W；位位置：[5]；默认值：1’b0；*/
/*description:将此位设置为1，以便在访问内部SRAM时为传输数据的Tx信道2启用INCR突发传输。*/
#define DMA_OUT_DATA_BURST_EN_CH2  (BIT(5))
#define DMA_OUT_DATA_BURST_EN_CH2_M  (BIT(5))
#define DMA_OUT_DATA_BURST_EN_CH2_V  0x1
#define DMA_OUT_DATA_BURST_EN_CH2_S  5
/* DMA_OUTDSCR_BURST_EN_CH2:R/W；位位置：[4]；默认值：1’b0；*/
/*description:将此位设置为1，以便在访问内部SRAM时，为Tx信道2读取链路描述符启用INCR突发传输。*/
#define DMA_OUTDSCR_BURST_EN_CH2  (BIT(4))
#define DMA_OUTDSCR_BURST_EN_CH2_M  (BIT(4))
#define DMA_OUTDSCR_BURST_EN_CH2_V  0x1
#define DMA_OUTDSCR_BURST_EN_CH2_S  4
/* DMA_OUT_EOF_MODE_CH2:R/W；位位置：[3]；默认值：1’b1；*/
/*描述：传输数据时EOF标志生成模式。1： 当需要传输的数据从DMA中的FIFO弹出时，生成Tx信道2的EOF标志*/
#define DMA_OUT_EOF_MODE_CH2  (BIT(3))
#define DMA_OUT_EOF_MODE_CH2_M  (BIT(3))
#define DMA_OUT_EOF_MODE_CH2_V  0x1
#define DMA_OUT_EOF_MODE_CH2_S  3
/* DMA_OUT_AUTO_WRBACK_CH2:R/W；位位置：[2]；默认值：1’b0；*/
/*description:设置此位以在传输tx缓冲区中的所有数据时启用自动outlink写回。*/
#define DMA_OUT_AUTO_WRBACK_CH2  (BIT(2))
#define DMA_OUT_AUTO_WRBACK_CH2_M  (BIT(2))
#define DMA_OUT_AUTO_WRBACK_CH2_V  0x1
#define DMA_OUT_AUTO_WRBACK_CH2_S  2
/* DMA_OUT_LOOP_TEST_CH2:R/W；位位置：[1]；默认值：1’b0；*/
/*description:保留*/
#define DMA_OUT_LOOP_TEST_CH2  (BIT(1))
#define DMA_OUT_LOOP_TEST_CH2_M  (BIT(1))
#define DMA_OUT_LOOP_TEST_CH2_V  0x1
#define DMA_OUT_LOOP_TEST_CH2_S  1
/* DMA_OUT_RST_CH2:R/W；位位置：[0]；默认值：1’b0；*/
/*描述：此位用于重置DMA通道2 Tx FSM和Tx FIFO指针。*/
#define DMA_OUT_RST_CH2  (BIT(0))
#define DMA_OUT_RST_CH2_M  (BIT(0))
#define DMA_OUT_RST_CH2_V  0x1
#define DMA_OUT_RST_CH2_S  0

#define DMA_OUT_CONF1_CH2_REG          (DR_REG_GDMA_BASE + 0x254)
/* DMA_OUT_CHECK_OWNER_CH2:R/W；位位置：[12]；默认值：1’b0；*/
/*description:设置此位以启用检查链接描述符的所有者属性。*/
#define DMA_OUT_CHECK_OWNER_CH2  (BIT(12))
#define DMA_OUT_CHECK_OWNER_CH2_M  (BIT(12))
#define DMA_OUT_CHECK_OWNER_CH2_V  0x1
#define DMA_OUT_CHECK_OWNER_CH2_S  12

#define DMA_OUTFIFO_STATUS_CH2_REG          (DR_REG_GDMA_BASE + 0x258)
/* DMA_OUT_REMAIN_UNDER_4B_CH2:RO；位位置：[26]；默认值：1’b1；*/
/*description:保留*/
#define DMA_OUT_REMAIN_UNDER_4B_CH2  (BIT(26))
#define DMA_OUT_REMAIN_UNDER_4B_CH2_M  (BIT(26))
#define DMA_OUT_REMAIN_UNDER_4B_CH2_V  0x1
#define DMA_OUT_REMAIN_UNDER_4B_CH2_S  26
/* DMA_OUT_REMAIN_UNDER_3B_CH2:RO；位位置：[25]；默认值：1’b1；*/
/*description:保留*/
#define DMA_OUT_REMAIN_UNDER_3B_CH2  (BIT(25))
#define DMA_OUT_REMAIN_UNDER_3B_CH2_M  (BIT(25))
#define DMA_OUT_REMAIN_UNDER_3B_CH2_V  0x1
#define DMA_OUT_REMAIN_UNDER_3B_CH2_S  25
/* DMA_OUT_REMAIN_UNDER_2B_CH2:RO；位位置：[24]；默认值：1’b1；*/
/*description:保留*/
#define DMA_OUT_REMAIN_UNDER_2B_CH2  (BIT(24))
#define DMA_OUT_REMAIN_UNDER_2B_CH2_M  (BIT(24))
#define DMA_OUT_REMAIN_UNDER_2B_CH2_V  0x1
#define DMA_OUT_REMAIN_UNDER_2B_CH2_S  24
/* DMA_OUT_REMAIN_UNDER_1B_CH2:RO；位位置：[23]；默认值：1’b1；*/
/*description:保留*/
#define DMA_OUT_REMAIN_UNDER_1B_CH2  (BIT(23))
#define DMA_OUT_REMAIN_UNDER_1B_CH2_M  (BIT(23))
#define DMA_OUT_REMAIN_UNDER_1B_CH2_V  0x1
#define DMA_OUT_REMAIN_UNDER_1B_CH2_S  23
/* DMA_OUTFIFO_CNT_CH2:RO；位位置：[7:2]；默认值：6'b0；*/
/*描述：寄存器将数据的字节数存储在Tx信道2的L1 Tx FIFO中。*/
#define DMA_OUTFIFO_CNT_CH2  0x0000003F
#define DMA_OUTFIFO_CNT_CH2_M  ((DMA_OUTFIFO_CNT_CH2_V)<<(DMA_OUTFIFO_CNT_CH2_S))
#define DMA_OUTFIFO_CNT_CH2_V  0x3F
#define DMA_OUTFIFO_CNT_CH2_S  2
/* DMA_OUTFIFO_EMPTY_CH2:RO；位位置：[1]；默认值：1’b1；*/
/*描述：Tx信道2的L1 Tx FIFO空信号。*/
#define DMA_OUTFIFO_EMPTY_CH2  (BIT(1))
#define DMA_OUTFIFO_EMPTY_CH2_M  (BIT(1))
#define DMA_OUTFIFO_EMPTY_CH2_V  0x1
#define DMA_OUTFIFO_EMPTY_CH2_S  1
/* DMA_OUTFIFO_FULL_CH2:RO；位位置：[0]；默认值：1’b0；*/
/*描述：Tx信道2的L1 Tx FIFO满信号。*/
#define DMA_OUTFIFO_FULL_CH2  (BIT(0))
#define DMA_OUTFIFO_FULL_CH2_M  (BIT(0))
#define DMA_OUTFIFO_FULL_CH2_V  0x1
#define DMA_OUTFIFO_FULL_CH2_S  0

#define DMA_OUT_PUSH_CH2_REG          (DR_REG_GDMA_BASE + 0x25C)
/* DMA_OUTFIFO_PUSH_CH2:R/W/SC；位位置：[9]；默认值：1'0；*/
/*description:设置此位以将数据推入DMA FIFO。*/
#define DMA_OUTFIFO_PUSH_CH2  (BIT(9))
#define DMA_OUTFIFO_PUSH_CH2_M  (BIT(9))
#define DMA_OUTFIFO_PUSH_CH2_V  0x1
#define DMA_OUTFIFO_PUSH_CH2_S  9
/* DMA_OUTFIFO_WDATA_CH2:R/W；位位置：[8:0]；默认值：9'0；*/
/*description:此寄存器存储需要推入DMA FIFO的数据。*/
#define DMA_OUTFIFO_WDATA_CH2  0x000001FF
#define DMA_OUTFIFO_WDATA_CH2_M  ((DMA_OUTFIFO_WDATA_CH2_V)<<(DMA_OUTFIFO_WDATA_CH2_S))
#define DMA_OUTFIFO_WDATA_CH2_V  0x1FF
#define DMA_OUTFIFO_WDATA_CH2_S  0

#define DMA_OUT_LINK_CH2_REG          (DR_REG_GDMA_BASE + 0x260)
/* DMA_OUTLINK_PARK_CH2:RO；位位置：[23]；默认值：1'h1；*/
/*描述：1:outlink描述符的FSM处于空闲状态。0:outlink描述符的FSM正在工作。*/
#define DMA_OUTLINK_PARK_CH2  (BIT(23))
#define DMA_OUTLINK_PARK_CH2_M  (BIT(23))
#define DMA_OUTLINK_PARK_CH2_V  0x1
#define DMA_OUTLINK_PARK_CH2_S  23
/* DMA_OUTLINK_RESTART_CH2:R/W/SC；位位置：[22]；默认值：1’b0；*/
/*description:设置此位以从上一个地址重新启动新的outlink。*/
#define DMA_OUTLINK_RESTART_CH2  (BIT(22))
#define DMA_OUTLINK_RESTART_CH2_M  (BIT(22))
#define DMA_OUTLINK_RESTART_CH2_V  0x1
#define DMA_OUTLINK_RESTART_CH2_S  22
/* DMA_OUTLINK_START_CH2:R/W/SC；位位置：[21]；默认值：1’b0；*/
/*description:设置此位以开始处理outlink描述符。*/
#define DMA_OUTLINK_START_CH2  (BIT(21))
#define DMA_OUTLINK_START_CH2_M  (BIT(21))
#define DMA_OUTLINK_START_CH2_V  0x1
#define DMA_OUTLINK_START_CH2_S  21
/* DMA_OUTLINK_STOP_CH2:R/W/SC；位位置：[20]；默认值：1’b0；*/
/*description:设置此位以停止处理outlink描述符。*/
#define DMA_OUTLINK_STOP_CH2  (BIT(20))
#define DMA_OUTLINK_STOP_CH2_M  (BIT(20))
#define DMA_OUTLINK_STOP_CH2_V  0x1
#define DMA_OUTLINK_STOP_CH2_S  20
/* DMA_OUTLINK_ADDR_CH2:R/W；比特位置：[19:0]；默认值：20'00；*/
/*description:此寄存器存储第一个outlink描述符地址的20个最低有效位。*/
#define DMA_OUTLINK_ADDR_CH2  0x000FFFFF
#define DMA_OUTLINK_ADDR_CH2_M  ((DMA_OUTLINK_ADDR_CH2_V)<<(DMA_OUTLINK_ADDR_CH2_S))
#define DMA_OUTLINK_ADDR_CH2_V  0xFFFFF
#define DMA_OUTLINK_ADDR_CH2_S  0

#define DMA_OUT_STATE_CH2_REG          (DR_REG_GDMA_BASE + 0x264)
/* DMA_OUT_STATE_CH2:RO；比特位置：[22:20]；默认值：3'b0；*/
/*description:保留*/
#define DMA_OUT_STATE_CH2  0x00000007
#define DMA_OUT_STATE_CH2_M  ((DMA_OUT_STATE_CH2_V)<<(DMA_OUT_STATE_CH2_S))
#define DMA_OUT_STATE_CH2_V  0x7
#define DMA_OUT_STATE_CH2_S  20
/* DMA_OUT_DSCR_STATE_CH2:RO；比特位置：[19:18]；默认值：2’b0；*/
/*description:保留*/
#define DMA_OUT_DSCR_STATE_CH2  0x00000003
#define DMA_OUT_DSCR_STATE_CH2_M  ((DMA_OUT_DSCR_STATE_CH2_V)<<(DMA_OUT_DSCR_STATE_CH2_S))
#define DMA_OUT_DSCR_STATE_CH2_V  0x3
#define DMA_OUT_DSCR_STATE_CH2_S  18
/* DMA_OUTLINK_DSCR_ADDR_CH2:RO；比特位置：[17:00]；默认值：18'b0；*/
/*description:此寄存器存储当前outlink描述符的地址。*/
#define DMA_OUTLINK_DSCR_ADDR_CH2  0x0003FFFF
#define DMA_OUTLINK_DSCR_ADDR_CH2_M  ((DMA_OUTLINK_DSCR_ADDR_CH2_V)<<(DMA_OUTLINK_DSCR_ADDR_CH2_S))
#define DMA_OUTLINK_DSCR_ADDR_CH2_V  0x3FFFF
#define DMA_OUTLINK_DSCR_ADDR_CH2_S  0

#define DMA_OUT_EOF_DES_ADDR_CH2_REG          (DR_REG_GDMA_BASE + 0x268)
/* DMA_OUT_EOF_DES_ADDR_CH2:RO；位位置：[31:0]；默认值：32'h0；*/
/*description:当此描述符中的EOF位为1时，此寄存器存储outlink描述符的地址。*/
#define DMA_OUT_EOF_DES_ADDR_CH2  0xFFFFFFFF
#define DMA_OUT_EOF_DES_ADDR_CH2_M  ((DMA_OUT_EOF_DES_ADDR_CH2_V)<<(DMA_OUT_EOF_DES_ADDR_CH2_S))
#define DMA_OUT_EOF_DES_ADDR_CH2_V  0xFFFFFFFF
#define DMA_OUT_EOF_DES_ADDR_CH2_S  0

#define DMA_OUT_EOF_BFR_DES_ADDR_CH2_REG          (DR_REG_GDMA_BASE + 0x26C)
/* DMA_OUT_EOF_BFR_DES_ADDR_CH2:RO；位位置：[31:0]；默认值：32'h0；*/
/*description:此寄存器存储最后一个outlink描述符之前的outlink描述符的地址。*/
#define DMA_OUT_EOF_BFR_DES_ADDR_CH2  0xFFFFFFFF
#define DMA_OUT_EOF_BFR_DES_ADDR_CH2_M  ((DMA_OUT_EOF_BFR_DES_ADDR_CH2_V)<<(DMA_OUT_EOF_BFR_DES_ADDR_CH2_S))
#define DMA_OUT_EOF_BFR_DES_ADDR_CH2_V  0xFFFFFFFF
#define DMA_OUT_EOF_BFR_DES_ADDR_CH2_S  0

#define DMA_OUT_DSCR_CH2_REG          (DR_REG_GDMA_BASE + 0x270)
/* DMA_OUTLINK_DSCR_CH2:RO；位位置：[31:0]；默认值：32'b0；*/
/*description:当前outlink描述符y的地址。*/
#define DMA_OUTLINK_DSCR_CH2  0xFFFFFFFF
#define DMA_OUTLINK_DSCR_CH2_M  ((DMA_OUTLINK_DSCR_CH2_V)<<(DMA_OUTLINK_DSCR_CH2_S))
#define DMA_OUTLINK_DSCR_CH2_V  0xFFFFFFFF
#define DMA_OUTLINK_DSCR_CH2_S  0

#define DMA_OUT_DSCR_BF0_CH2_REG          (DR_REG_GDMA_BASE + 0x274)
/* DMA_OUTLINK_DSCR_BF0_CH2:RO；位位置：[31:0]；默认值：32'b0；*/
/*description:最后一个outlink描述符y-1的地址。*/
#define DMA_OUTLINK_DSCR_BF0_CH2  0xFFFFFFFF
#define DMA_OUTLINK_DSCR_BF0_CH2_M  ((DMA_OUTLINK_DSCR_BF0_CH2_V)<<(DMA_OUTLINK_DSCR_BF0_CH2_S))
#define DMA_OUTLINK_DSCR_BF0_CH2_V  0xFFFFFFFF
#define DMA_OUTLINK_DSCR_BF0_CH2_S  0

#define DMA_OUT_DSCR_BF1_CH2_REG          (DR_REG_GDMA_BASE + 0x278)
/* DMA_OUTLINK_DSCR_BF1_CH2:RO；位位置：[31:0]；默认值：32'b0；*/
/*description:倒数第二个内联描述符x-2的地址。*/
#define DMA_OUTLINK_DSCR_BF1_CH2  0xFFFFFFFF
#define DMA_OUTLINK_DSCR_BF1_CH2_M  ((DMA_OUTLINK_DSCR_BF1_CH2_V)<<(DMA_OUTLINK_DSCR_BF1_CH2_S))
#define DMA_OUTLINK_DSCR_BF1_CH2_V  0xFFFFFFFF
#define DMA_OUTLINK_DSCR_BF1_CH2_S  0

#define DMA_OUT_PRI_CH2_REG          (DR_REG_GDMA_BASE + 0x27C)
/* DMA_TX_PRI_CH2:R/W；位位置：[3:0]；默认值：4'b0；*/
/*description:Tx信道2的优先级。值越大，优先级越高。*/
#define DMA_TX_PRI_CH2  0x0000000F
#define DMA_TX_PRI_CH2_M  ((DMA_TX_PRI_CH2_V)<<(DMA_TX_PRI_CH2_S))
#define DMA_TX_PRI_CH2_V  0xF
#define DMA_TX_PRI_CH2_S  0

#define DMA_OUT_PERI_SEL_CH2_REG          (DR_REG_GDMA_BASE + 0x280)
/* DMA_PERI_OUT_SEL_CH2:R/W；比特位置：[5:0]；默认值：6'h3F；*/
/*description:此寄存器用于为Tx信道2选择外设。0:SPI2.1:保留。2： UHCI0.3:I2S0.4：保留。5： 保留。6： AES。7： 沙。8： ADC_DAC。*/
#define DMA_PERI_OUT_SEL_CH2  0x0000003F
#define DMA_PERI_OUT_SEL_CH2_M  ((DMA_PERI_OUT_SEL_CH2_V)<<(DMA_PERI_OUT_SEL_CH2_S))
#define DMA_PERI_OUT_SEL_CH2_V  0x3F
#define DMA_PERI_OUT_SEL_CH2_S  0

#ifdef __cplusplus
}
#endif



#endif /*_SOC_DMA_REG_H_ */

