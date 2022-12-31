/** 版权所有2020 Espressif Systems（上海）私人有限公司
 *
 *  根据Apache许可证2.0版（“许可证”）获得许可；除非符合许可证，否则不得使用此文件。您可以在以下地址获取许可证副本：
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 *  除非适用法律要求或书面同意，否则根据许可证分发的软件是按“原样”分发的，无任何明示或暗示的担保或条件。有关许可证下权限和限制的具体语言，请参阅许可证。
 */
#pragma once

#include <stdint.h>
#include "soc/soc.h"
#ifdef __cplusplus
extern "C" {
#endif

/** CP_DMA_INT_RAW_REG寄存器原始中断状态
 */
#define CP_DMA_INT_RAW_REG (DR_REG_CP_BASE + 0x0)
/** CP_DMA_IN_DONE_INT_RAW:RO；位位置：[0]；默认值：0；这是中断原始位。当接收到帧的最后一个数据或内联描述符指示的接收缓冲区已满时触发。
 */
#define CP_DMA_IN_DONE_INT_RAW    (BIT(0))
#define CP_DMA_IN_DONE_INT_RAW_M  (CP_DMA_IN_DONE_INT_RAW_V << CP_DMA_IN_DONE_INT_RAW_S)
#define CP_DMA_IN_DONE_INT_RAW_V  0x00000001
#define CP_DMA_IN_DONE_INT_RAW_S  0
/** CP_DMA_IN_SUC_EOF_INT_RAW:RO；位位置：[1]；默认值：0；这是中断原始位。当接收到一帧的最后数据时触发。
 */
#define CP_DMA_IN_SUC_EOF_INT_RAW    (BIT(1))
#define CP_DMA_IN_SUC_EOF_INT_RAW_M  (CP_DMA_IN_SUC_EOF_INT_RAW_V << CP_DMA_IN_SUC_EOF_INT_RAW_S)
#define CP_DMA_IN_SUC_EOF_INT_RAW_V  0x00000001
#define CP_DMA_IN_SUC_EOF_INT_RAW_S  1
/** CP_DMA_OUT_DONE_INT_RAW:RO；位位置：[2]；默认值：0；这是中断原始位。当一个输出描述符指示的所有数据都被推入Tx FIFO时触发。
 */
#define CP_DMA_OUT_DONE_INT_RAW    (BIT(2))
#define CP_DMA_OUT_DONE_INT_RAW_M  (CP_DMA_OUT_DONE_INT_RAW_V << CP_DMA_OUT_DONE_INT_RAW_S)
#define CP_DMA_OUT_DONE_INT_RAW_V  0x00000001
#define CP_DMA_OUT_DONE_INT_RAW_S  2
/** CP_DMA_OUT_EOF_INT_RAW:RO；位位置：[3]；默认值：0；这是中断原始位。当带有EOF标志的最后一个数据被推入Tx FIFO时触发。
 */
#define CP_DMA_OUT_EOF_INT_RAW    (BIT(3))
#define CP_DMA_OUT_EOF_INT_RAW_M  (CP_DMA_OUT_EOF_INT_RAW_V << CP_DMA_OUT_EOF_INT_RAW_S)
#define CP_DMA_OUT_EOF_INT_RAW_V  0x00000001
#define CP_DMA_OUT_EOF_INT_RAW_S  3
/** CP_DMA_IN_DSCR_ERR_INT_RAW:RO；位位置：[4]；默认值：0；这是中断原始位。检测到内联描述符错误时触发，包括所有者错误、内联描述符的第二个和第三个单词错误。
 */
#define CP_DMA_IN_DSCR_ERR_INT_RAW    (BIT(4))
#define CP_DMA_IN_DSCR_ERR_INT_RAW_M  (CP_DMA_IN_DSCR_ERR_INT_RAW_V << CP_DMA_IN_DSCR_ERR_INT_RAW_S)
#define CP_DMA_IN_DSCR_ERR_INT_RAW_V  0x00000001
#define CP_DMA_IN_DSCR_ERR_INT_RAW_S  4
/** CP_DMA_OUT_DSCR_ERR_INT_RAW:RO；位位置：[5]；默认值：0；这是中断原始位。检测到outlink描述符错误时触发，包括所有者错误、outlink描述符的第二个和第三个单词错误。
 */
#define CP_DMA_OUT_DSCR_ERR_INT_RAW    (BIT(5))
#define CP_DMA_OUT_DSCR_ERR_INT_RAW_M  (CP_DMA_OUT_DSCR_ERR_INT_RAW_V << CP_DMA_OUT_DSCR_ERR_INT_RAW_S)
#define CP_DMA_OUT_DSCR_ERR_INT_RAW_V  0x00000001
#define CP_DMA_OUT_DSCR_ERR_INT_RAW_S  5
/** CP_DMA_IN_DSCR_EMPTY_INT_RAW:RO；位位置：[6]；默认值：0；这是中断原始位。当接收数据完成且没有更多内联描述符时触发。
 */
#define CP_DMA_IN_DSCR_EMPTY_INT_RAW    (BIT(6))
#define CP_DMA_IN_DSCR_EMPTY_INT_RAW_M  (CP_DMA_IN_DSCR_EMPTY_INT_RAW_V << CP_DMA_IN_DSCR_EMPTY_INT_RAW_S)
#define CP_DMA_IN_DSCR_EMPTY_INT_RAW_V  0x00000001
#define CP_DMA_IN_DSCR_EMPTY_INT_RAW_S  6
/** CP_DMA_OUT_TOTAL_EOF_INT_RAW:RO；位位置：[7]；默认值：0；这是中断原始位。当发送出与所有outlink描述符和具有有效EOF的最后一个描述符相对应的数据时触发。
 */
#define CP_DMA_OUT_TOTAL_EOF_INT_RAW    (BIT(7))
#define CP_DMA_OUT_TOTAL_EOF_INT_RAW_M  (CP_DMA_OUT_TOTAL_EOF_INT_RAW_V << CP_DMA_OUT_TOTAL_EOF_INT_RAW_S)
#define CP_DMA_OUT_TOTAL_EOF_INT_RAW_V  0x00000001
#define CP_DMA_OUT_TOTAL_EOF_INT_RAW_S  7
/** CP_DMA_CRC_DONE_INT_RAW:RO；位位置：[8]；默认值：0；这是中断原始位。完成crc计算时触发。
 */
#define CP_DMA_CRC_DONE_INT_RAW    (BIT(8))
#define CP_DMA_CRC_DONE_INT_RAW_M  (CP_DMA_CRC_DONE_INT_RAW_V << CP_DMA_CRC_DONE_INT_RAW_S)
#define CP_DMA_CRC_DONE_INT_RAW_V  0x00000001
#define CP_DMA_CRC_DONE_INT_RAW_S  8

/** CP_DMA_INT_ST_REG寄存器屏蔽中断状态
 */
#define CP_DMA_INT_ST_REG (DR_REG_CP_BASE + 0x4)
/** CP_DMA_IN_DONE_INT_ST:RO；位位置：[0]；默认值：0；这是当cp_in_done_int_ena设置为1时，cp_in_done _int中断的屏蔽中断位。
 */
#define CP_DMA_IN_DONE_INT_ST    (BIT(0))
#define CP_DMA_IN_DONE_INT_ST_M  (CP_DMA_IN_DONE_INT_ST_V << CP_DMA_IN_DONE_INT_ST_S)
#define CP_DMA_IN_DONE_INT_ST_V  0x00000001
#define CP_DMA_IN_DONE_INT_ST_S  0
/** CP_DMA_IN_SUC_EOF_INT_ST:RO；位位置：[1]；默认值：0；这是当cp_in_suc_eof_int_ena设置为1时，cp_in_suce_eof_int中断的屏蔽中断位。
 */
#define CP_DMA_IN_SUC_EOF_INT_ST    (BIT(1))
#define CP_DMA_IN_SUC_EOF_INT_ST_M  (CP_DMA_IN_SUC_EOF_INT_ST_V << CP_DMA_IN_SUC_EOF_INT_ST_S)
#define CP_DMA_IN_SUC_EOF_INT_ST_V  0x00000001
#define CP_DMA_IN_SUC_EOF_INT_ST_S  1
/** CP_DMA_OUT_DONE_INT_ST:RO；位位置：[2]；默认值：0；这是当cp_out_done_int_ena设置为1时，cp_out_done_int中断的屏蔽中断位。
 */
#define CP_DMA_OUT_DONE_INT_ST    (BIT(2))
#define CP_DMA_OUT_DONE_INT_ST_M  (CP_DMA_OUT_DONE_INT_ST_V << CP_DMA_OUT_DONE_INT_ST_S)
#define CP_DMA_OUT_DONE_INT_ST_V  0x00000001
#define CP_DMA_OUT_DONE_INT_ST_S  2
/** CP_DMA_OUT_EOF_INT_ST:RO；位位置：[3]；默认值：0；这是当cp_out_eof_int_ena设置为1时，cp_out_eof_int中断的屏蔽中断位。
 */
#define CP_DMA_OUT_EOF_INT_ST    (BIT(3))
#define CP_DMA_OUT_EOF_INT_ST_M  (CP_DMA_OUT_EOF_INT_ST_V << CP_DMA_OUT_EOF_INT_ST_S)
#define CP_DMA_OUT_EOF_INT_ST_V  0x00000001
#define CP_DMA_OUT_EOF_INT_ST_S  3
/** CP_DMA_IN_DSCR_ERR_INT_ST:RO；位位置：[4]；默认值：0；这是当cp_in_dscr_err_int_ena设置为1时，cp_in_dcr_err_int中断的屏蔽中断位。
 */
#define CP_DMA_IN_DSCR_ERR_INT_ST    (BIT(4))
#define CP_DMA_IN_DSCR_ERR_INT_ST_M  (CP_DMA_IN_DSCR_ERR_INT_ST_V << CP_DMA_IN_DSCR_ERR_INT_ST_S)
#define CP_DMA_IN_DSCR_ERR_INT_ST_V  0x00000001
#define CP_DMA_IN_DSCR_ERR_INT_ST_S  4
/** CP_DMA_OUT_DSCR_ERR_INT_ST:RO；位位置：[5]；默认值：0；这是当cp_out_dscr_err_int_ena设置为1时，cp_out_dscr_err.int中断的屏蔽中断位。
 */
#define CP_DMA_OUT_DSCR_ERR_INT_ST    (BIT(5))
#define CP_DMA_OUT_DSCR_ERR_INT_ST_M  (CP_DMA_OUT_DSCR_ERR_INT_ST_V << CP_DMA_OUT_DSCR_ERR_INT_ST_S)
#define CP_DMA_OUT_DSCR_ERR_INT_ST_V  0x00000001
#define CP_DMA_OUT_DSCR_ERR_INT_ST_S  5
/** CP_DMA_IN_DSCR_EMPTY_INT_ST:RO；位位置：[6]；默认值：0；这是当cp_in_dscr_empty_int_ena设置为1时，cp_in_dcr_empty.int中断的屏蔽中断位。
 */
#define CP_DMA_IN_DSCR_EMPTY_INT_ST    (BIT(6))
#define CP_DMA_IN_DSCR_EMPTY_INT_ST_M  (CP_DMA_IN_DSCR_EMPTY_INT_ST_V << CP_DMA_IN_DSCR_EMPTY_INT_ST_S)
#define CP_DMA_IN_DSCR_EMPTY_INT_ST_V  0x00000001
#define CP_DMA_IN_DSCR_EMPTY_INT_ST_S  6
/** CP_DMA_OUT_TOTAL_EOF_INT_ST:RO；位位置：[7]；默认值：0；这是当cp_out_total_eof_int_ena设置为1时，cp_out_total_eoff_int中断的屏蔽中断位。
 */
#define CP_DMA_OUT_TOTAL_EOF_INT_ST    (BIT(7))
#define CP_DMA_OUT_TOTAL_EOF_INT_ST_M  (CP_DMA_OUT_TOTAL_EOF_INT_ST_V << CP_DMA_OUT_TOTAL_EOF_INT_ST_S)
#define CP_DMA_OUT_TOTAL_EOF_INT_ST_V  0x00000001
#define CP_DMA_OUT_TOTAL_EOF_INT_ST_S  7
/** CP_DMA_CRC_DONE_INT_ST:RO；位位置：[8]；默认值：0；这是当cp_crc_done_int_ena设置为1时，cp_crc_done_int中断的屏蔽中断位。
 */
#define CP_DMA_CRC_DONE_INT_ST    (BIT(8))
#define CP_DMA_CRC_DONE_INT_ST_M  (CP_DMA_CRC_DONE_INT_ST_V << CP_DMA_CRC_DONE_INT_ST_S)
#define CP_DMA_CRC_DONE_INT_ST_V  0x00000001
#define CP_DMA_CRC_DONE_INT_ST_S  8

/** CP_DMA_INT_ENA_REG寄存器中断启用位
 */
#define CP_DMA_INT_ENA_REG (DR_REG_CP_BASE + 0x8)
/** CP_DMA_IN_DONE_INT_ENA:R/W；位位置：[0]；默认值：0；这是cp_in_done_int中断的中断启用位。
 */
#define CP_DMA_IN_DONE_INT_ENA    (BIT(0))
#define CP_DMA_IN_DONE_INT_ENA_M  (CP_DMA_IN_DONE_INT_ENA_V << CP_DMA_IN_DONE_INT_ENA_S)
#define CP_DMA_IN_DONE_INT_ENA_V  0x00000001
#define CP_DMA_IN_DONE_INT_ENA_S  0
/** CP_DMA_IN_SUC_EOF_INT_ENA:R/W；位位置：[1]；默认值：0；这是cp_in_suc_eof_int中断的中断启用位。
 */
#define CP_DMA_IN_SUC_EOF_INT_ENA    (BIT(1))
#define CP_DMA_IN_SUC_EOF_INT_ENA_M  (CP_DMA_IN_SUC_EOF_INT_ENA_V << CP_DMA_IN_SUC_EOF_INT_ENA_S)
#define CP_DMA_IN_SUC_EOF_INT_ENA_V  0x00000001
#define CP_DMA_IN_SUC_EOF_INT_ENA_S  1
/** CP_DMA_OUT_DONE_INT_ENA：R/W；位位置：[2]；默认值：0；这是cp_out_done_int中断的中断启用位。
 */
#define CP_DMA_OUT_DONE_INT_ENA    (BIT(2))
#define CP_DMA_OUT_DONE_INT_ENA_M  (CP_DMA_OUT_DONE_INT_ENA_V << CP_DMA_OUT_DONE_INT_ENA_S)
#define CP_DMA_OUT_DONE_INT_ENA_V  0x00000001
#define CP_DMA_OUT_DONE_INT_ENA_S  2
/** CP_DMA_OUT_EOF_INT_ENA：R/W；位位置：[3]；默认值：0；这是cp_out_eof_int中断的中断启用位。
 */
#define CP_DMA_OUT_EOF_INT_ENA    (BIT(3))
#define CP_DMA_OUT_EOF_INT_ENA_M  (CP_DMA_OUT_EOF_INT_ENA_V << CP_DMA_OUT_EOF_INT_ENA_S)
#define CP_DMA_OUT_EOF_INT_ENA_V  0x00000001
#define CP_DMA_OUT_EOF_INT_ENA_S  3
/** CP_DMA_IN_DSCR_ERR_INT_ENA:R/W；位位置：[4]；默认值：0；这是cp_in_dscr_err_int中断的中断启用位。
 */
#define CP_DMA_IN_DSCR_ERR_INT_ENA    (BIT(4))
#define CP_DMA_IN_DSCR_ERR_INT_ENA_M  (CP_DMA_IN_DSCR_ERR_INT_ENA_V << CP_DMA_IN_DSCR_ERR_INT_ENA_S)
#define CP_DMA_IN_DSCR_ERR_INT_ENA_V  0x00000001
#define CP_DMA_IN_DSCR_ERR_INT_ENA_S  4
/** CP_DMA_OUT_DSCR_ERR_INT_ENA:R/W；位位置：[5]；默认值：0；这是cp_out_dscr_err_int中断的中断启用位。
 */
#define CP_DMA_OUT_DSCR_ERR_INT_ENA    (BIT(5))
#define CP_DMA_OUT_DSCR_ERR_INT_ENA_M  (CP_DMA_OUT_DSCR_ERR_INT_ENA_V << CP_DMA_OUT_DSCR_ERR_INT_ENA_S)
#define CP_DMA_OUT_DSCR_ERR_INT_ENA_V  0x00000001
#define CP_DMA_OUT_DSCR_ERR_INT_ENA_S  5
/** CP_DMA_IN_DSCR_EMPTY_INT_ENA:R/W；位位置：[6]；默认值：0；这是cp_in_dscr_empty_int中断的中断启用位。
 */
#define CP_DMA_IN_DSCR_EMPTY_INT_ENA    (BIT(6))
#define CP_DMA_IN_DSCR_EMPTY_INT_ENA_M  (CP_DMA_IN_DSCR_EMPTY_INT_ENA_V << CP_DMA_IN_DSCR_EMPTY_INT_ENA_S)
#define CP_DMA_IN_DSCR_EMPTY_INT_ENA_V  0x00000001
#define CP_DMA_IN_DSCR_EMPTY_INT_ENA_S  6
/** CP_DMA_OUT_TOTAL_EOF_INT_ENA:R/W；位位置：[7]；默认值：0；这是cp_out_total_eof_int中断的中断启用位。
 */
#define CP_DMA_OUT_TOTAL_EOF_INT_ENA    (BIT(7))
#define CP_DMA_OUT_TOTAL_EOF_INT_ENA_M  (CP_DMA_OUT_TOTAL_EOF_INT_ENA_V << CP_DMA_OUT_TOTAL_EOF_INT_ENA_S)
#define CP_DMA_OUT_TOTAL_EOF_INT_ENA_V  0x00000001
#define CP_DMA_OUT_TOTAL_EOF_INT_ENA_S  7
/** CP_DMA_CRC_DONE_INT_ENA：R/W；位位置：[8]；默认值：0；这是cp_crc_done_int中断的中断启用位。
 */
#define CP_DMA_CRC_DONE_INT_ENA    (BIT(8))
#define CP_DMA_CRC_DONE_INT_ENA_M  (CP_DMA_CRC_DONE_INT_ENA_V << CP_DMA_CRC_DONE_INT_ENA_S)
#define CP_DMA_CRC_DONE_INT_ENA_V  0x00000001
#define CP_DMA_CRC_DONE_INT_ENA_S  8

/** CP_DMA_INT_CLR_REG寄存器中断清除位
 */
#define CP_DMA_INT_CLR_REG (DR_REG_CP_BASE + 0xc)
/** CP_DMA_IN_DONE_INT_CLR:WO；位位置：[0]；默认值：0；设置此位以清除cp_in_done_int中断。
 */
#define CP_DMA_IN_DONE_INT_CLR    (BIT(0))
#define CP_DMA_IN_DONE_INT_CLR_M  (CP_DMA_IN_DONE_INT_CLR_V << CP_DMA_IN_DONE_INT_CLR_S)
#define CP_DMA_IN_DONE_INT_CLR_V  0x00000001
#define CP_DMA_IN_DONE_INT_CLR_S  0
/** CP_DMA_IN_SUC_EOF_INT_CLR:WO；位位置：[1]；默认值：0；设置此位以清除cp_in_suc_eof_int中断。
 */
#define CP_DMA_IN_SUC_EOF_INT_CLR    (BIT(1))
#define CP_DMA_IN_SUC_EOF_INT_CLR_M  (CP_DMA_IN_SUC_EOF_INT_CLR_V << CP_DMA_IN_SUC_EOF_INT_CLR_S)
#define CP_DMA_IN_SUC_EOF_INT_CLR_V  0x00000001
#define CP_DMA_IN_SUC_EOF_INT_CLR_S  1
/** CP_DMA_OUT_DONE_INT_CLR:WO；位位置：[2]；默认值：0；设置此位以清除cp_out_done_int中断。
 */
#define CP_DMA_OUT_DONE_INT_CLR    (BIT(2))
#define CP_DMA_OUT_DONE_INT_CLR_M  (CP_DMA_OUT_DONE_INT_CLR_V << CP_DMA_OUT_DONE_INT_CLR_S)
#define CP_DMA_OUT_DONE_INT_CLR_V  0x00000001
#define CP_DMA_OUT_DONE_INT_CLR_S  2
/** CP_DMA_OUT_EOF_INT_CLR:WO；位位置：[3]；默认值：0；设置此位以清除cp_out_eof_int中断。
 */
#define CP_DMA_OUT_EOF_INT_CLR    (BIT(3))
#define CP_DMA_OUT_EOF_INT_CLR_M  (CP_DMA_OUT_EOF_INT_CLR_V << CP_DMA_OUT_EOF_INT_CLR_S)
#define CP_DMA_OUT_EOF_INT_CLR_V  0x00000001
#define CP_DMA_OUT_EOF_INT_CLR_S  3
/** CP_DMA_IN_DSCR_ERR_INT_CLR:WO；位位置：[4]；默认值：0；设置此位以清除cp_in_dscr_err_int中断。
 */
#define CP_DMA_IN_DSCR_ERR_INT_CLR    (BIT(4))
#define CP_DMA_IN_DSCR_ERR_INT_CLR_M  (CP_DMA_IN_DSCR_ERR_INT_CLR_V << CP_DMA_IN_DSCR_ERR_INT_CLR_S)
#define CP_DMA_IN_DSCR_ERR_INT_CLR_V  0x00000001
#define CP_DMA_IN_DSCR_ERR_INT_CLR_S  4
/** CP_DMA_OUT_DSCR_ERR_INT_CLR:WO；位位置：[5]；默认值：0；设置此位以清除cp_out_dscr_err_int中断。
 */
#define CP_DMA_OUT_DSCR_ERR_INT_CLR    (BIT(5))
#define CP_DMA_OUT_DSCR_ERR_INT_CLR_M  (CP_DMA_OUT_DSCR_ERR_INT_CLR_V << CP_DMA_OUT_DSCR_ERR_INT_CLR_S)
#define CP_DMA_OUT_DSCR_ERR_INT_CLR_V  0x00000001
#define CP_DMA_OUT_DSCR_ERR_INT_CLR_S  5
/** CP_DMA_IN_DSCR_EMPTY_INT_CLR:WO；位位置：[6]；默认值：0；设置此位以清除cp_in_dscr_empty_int中断。
 */
#define CP_DMA_IN_DSCR_EMPTY_INT_CLR    (BIT(6))
#define CP_DMA_IN_DSCR_EMPTY_INT_CLR_M  (CP_DMA_IN_DSCR_EMPTY_INT_CLR_V << CP_DMA_IN_DSCR_EMPTY_INT_CLR_S)
#define CP_DMA_IN_DSCR_EMPTY_INT_CLR_V  0x00000001
#define CP_DMA_IN_DSCR_EMPTY_INT_CLR_S  6
/** CP_DMA_OUT_TOTAL_EOF_INT_CLR:WO；位位置：[7]；默认值：0；设置此位以清除cp_out_total_eof_int中断。
 */
#define CP_DMA_OUT_TOTAL_EOF_INT_CLR    (BIT(7))
#define CP_DMA_OUT_TOTAL_EOF_INT_CLR_M  (CP_DMA_OUT_TOTAL_EOF_INT_CLR_V << CP_DMA_OUT_TOTAL_EOF_INT_CLR_S)
#define CP_DMA_OUT_TOTAL_EOF_INT_CLR_V  0x00000001
#define CP_DMA_OUT_TOTAL_EOF_INT_CLR_S  7
/** CP_DMA_CRC_DONE_INT_CLR:WO；位位置：[8]；默认值：0；设置此位以清除cp_crc_done_int中断。
 */
#define CP_DMA_CRC_DONE_INT_CLR    (BIT(8))
#define CP_DMA_CRC_DONE_INT_CLR_M  (CP_DMA_CRC_DONE_INT_CLR_V << CP_DMA_CRC_DONE_INT_CLR_S)
#define CP_DMA_CRC_DONE_INT_CLR_V  0x00000001
#define CP_DMA_CRC_DONE_INT_CLR_S  8

/** CP_DMA_OUT_LINK_REG寄存器链路描述符地址和控制
 */
#define CP_DMA_OUT_LINK_REG (DR_REG_CP_BASE + 0x10)
/** CP_DMA_OUTLINK_ADDR:R/W；比特位置：[19:0]；默认值：0；该寄存器用于指定第一个输出链接描述符地址的最低有效20位。
 */
#define CP_DMA_OUTLINK_ADDR    0x000FFFFF
#define CP_DMA_OUTLINK_ADDR_M  (CP_DMA_OUTLINK_ADDR_V << CP_DMA_OUTLINK_ADDR_S)
#define CP_DMA_OUTLINK_ADDR_V  0x000FFFFF
#define CP_DMA_OUTLINK_ADDR_S  0
/** CP_DMA_OUTLINK_STOP：R/W；位位置：[28]；默认值：0；设置此位以停止处理outlink描述符。
 */
#define CP_DMA_OUTLINK_STOP    (BIT(28))
#define CP_DMA_OUTLINK_STOP_M  (CP_DMA_OUTLINK_STOP_V << CP_DMA_OUTLINK_STOP_S)
#define CP_DMA_OUTLINK_STOP_V  0x00000001
#define CP_DMA_OUTLINK_STOP_S  28
/** CP_DMA_OUTLINK_START:R/W；位位置：[29]；默认值：0；设置此位以启动新的outlink描述符。
 */
#define CP_DMA_OUTLINK_START    (BIT(29))
#define CP_DMA_OUTLINK_START_M  (CP_DMA_OUTLINK_START_V << CP_DMA_OUTLINK_START_S)
#define CP_DMA_OUTLINK_START_V  0x00000001
#define CP_DMA_OUTLINK_START_S  29
/** CP_DMA_OUTLINK_RESTART：R/W；位位置：[30]；默认值：0；设置此位以从最后一个地址重新启动outlink descriptpr。
 */
#define CP_DMA_OUTLINK_RESTART    (BIT(30))
#define CP_DMA_OUTLINK_RESTART_M  (CP_DMA_OUTLINK_RESTART_V << CP_DMA_OUTLINK_RESTART_S)
#define CP_DMA_OUTLINK_RESTART_V  0x00000001
#define CP_DMA_OUTLINK_RESTART_S  30
/** CP_DMA_OUTLINK_PARK:RO；位位置：[31]；默认值：0；1： outlink描述符的FSM处于空闲状态。0:outlink描述符的FSM正在工作。
 */
#define CP_DMA_OUTLINK_PARK    (BIT(31))
#define CP_DMA_OUTLINK_PARK_M  (CP_DMA_OUTLINK_PARK_V << CP_DMA_OUTLINK_PARK_S)
#define CP_DMA_OUTLINK_PARK_V  0x00000001
#define CP_DMA_OUTLINK_PARK_S  31

/** CP_DMA_IN_LINK_REG寄存器链路描述符地址和控制
 */
#define CP_DMA_IN_LINK_REG (DR_REG_CP_BASE + 0x14)
/** CP_DMA_INLINK_ADDR:R/W；比特位置：[19:0]；默认值：0；该寄存器用于指定第一个内联描述符地址的最低有效20位。
 */
#define CP_DMA_INLINK_ADDR    0x000FFFFF
#define CP_DMA_INLINK_ADDR_M  (CP_DMA_INLINK_ADDR_V << CP_DMA_INLINK_ADDR_S)
#define CP_DMA_INLINK_ADDR_V  0x000FFFFF
#define CP_DMA_INLINK_ADDR_S  0
/** CP_DMA_INLINK_STOP：R/W；位位置：[28]；默认值：0；设置此位以停止处理内联描述符。
 */
#define CP_DMA_INLINK_STOP    (BIT(28))
#define CP_DMA_INLINK_STOP_M  (CP_DMA_INLINK_STOP_V << CP_DMA_INLINK_STOP_S)
#define CP_DMA_INLINK_STOP_V  0x00000001
#define CP_DMA_INLINK_STOP_S  28
/** CP_DMA_INLINK_START:R/W；位位置：[29]；默认值：0；设置此位以开始处理内联描述符。
 */
#define CP_DMA_INLINK_START    (BIT(29))
#define CP_DMA_INLINK_START_M  (CP_DMA_INLINK_START_V << CP_DMA_INLINK_START_S)
#define CP_DMA_INLINK_START_V  0x00000001
#define CP_DMA_INLINK_START_S  29
/** CP_DMA_INLINK_RESTART：R/W；位位置：[30]；默认值：0；设置此位以重新启动新的内联描述符。
 */
#define CP_DMA_INLINK_RESTART    (BIT(30))
#define CP_DMA_INLINK_RESTART_M  (CP_DMA_INLINK_RESTART_V << CP_DMA_INLINK_RESTART_S)
#define CP_DMA_INLINK_RESTART_V  0x00000001
#define CP_DMA_INLINK_RESTART_S  30
/** CP_DMA_INLINK_PARK:RO；位位置：[31]；默认值：0；1： 内联描述符的FSM处于空闲状态。0:内联描述符的FSM正在工作。
 */
#define CP_DMA_INLINK_PARK    (BIT(31))
#define CP_DMA_INLINK_PARK_M  (CP_DMA_INLINK_PARK_V << CP_DMA_INLINK_PARK_S)
#define CP_DMA_INLINK_PARK_V  0x00000001
#define CP_DMA_INLINK_PARK_S  31

/** 发生EOF时CP_DMA_OUT_EOF_DES_ADDR_REG寄存器异常描述符地址
 */
#define CP_DMA_OUT_EOF_DES_ADDR_REG (DR_REG_CP_BASE + 0x18)
/** CP_DMA_OUT_EOF_DES_ADDR:RO；位位置：[31:0]；默认值：0；当该描述符中的EOF位为1时，该寄存器存储outlink描述符的地址。
 */
#define CP_DMA_OUT_EOF_DES_ADDR    0xFFFFFFFF
#define CP_DMA_OUT_EOF_DES_ADDR_M  (CP_DMA_OUT_EOF_DES_ADDR_V << CP_DMA_OUT_EOF_DES_ADDR_S)
#define CP_DMA_OUT_EOF_DES_ADDR_V  0xFFFFFFFF
#define CP_DMA_OUT_EOF_DES_ADDR_S  0

/** 发生EOF时CP_DMA_IN_EOF_DES_ADDR_REG寄存器Inlink描述符地址
 */
#define CP_DMA_IN_EOF_DES_ADDR_REG (DR_REG_CP_BASE + 0x1c)
/** CP_DMA_IN_SUC_EOF_DES_ADDR:RO；位位置：[31:0]；默认值：0；当收到成功的EOF时，此寄存器存储内联描述符的地址。
 */
#define CP_DMA_IN_SUC_EOF_DES_ADDR    0xFFFFFFFF
#define CP_DMA_IN_SUC_EOF_DES_ADDR_M  (CP_DMA_IN_SUC_EOF_DES_ADDR_V << CP_DMA_IN_SUC_EOF_DES_ADDR_S)
#define CP_DMA_IN_SUC_EOF_DES_ADDR_V  0xFFFFFFFF
#define CP_DMA_IN_SUC_EOF_DES_ADDR_S  0

/** CP_DMA_OUT_EOF_BFR_DES_ADDR_REG寄存器最后一个大纲描述符之前的大纲描述符地址
 */
#define CP_DMA_OUT_EOF_BFR_DES_ADDR_REG (DR_REG_CP_BASE + 0x20)
/** CP_DMA_OUT_EOF_BFR_DES_ADDR:RO；位位置：[31:0]；默认值：0；此寄存器存储最后一个outlink描述符之前的outlink描述符的地址。
 */
#define CP_DMA_OUT_EOF_BFR_DES_ADDR    0xFFFFFFFF
#define CP_DMA_OUT_EOF_BFR_DES_ADDR_M  (CP_DMA_OUT_EOF_BFR_DES_ADDR_V << CP_DMA_OUT_EOF_BFR_DES_ADDR_S)
#define CP_DMA_OUT_EOF_BFR_DES_ADDR_V  0xFFFFFFFF
#define CP_DMA_OUT_EOF_BFR_DES_ADDR_S  0

/** CP_DMA_INLINK_DSCR_REG寄存器当前内联描述符的地址
 */
#define CP_DMA_INLINK_DSCR_REG (DR_REG_CP_BASE + 0x24)
/** CP_DMA_INLINK_DSCR:RO；位位置：[31:0]；默认值：0；当前内联描述符x的地址。
 */
#define CP_DMA_INLINK_DSCR    0xFFFFFFFF
#define CP_DMA_INLINK_DSCR_M  (CP_DMA_INLINK_DSCR_V << CP_DMA_INLINK_DSCR_S)
#define CP_DMA_INLINK_DSCR_V  0xFFFFFFFF
#define CP_DMA_INLINK_DSCR_S  0

/** CP_DMA_INLINK_DSCR_BF0_REG寄存器最后一个内联描述符的地址
 */
#define CP_DMA_INLINK_DSCR_BF0_REG (DR_REG_CP_BASE + 0x28)
/** CP_DMA_INLINK_DSCR_BF0:RO；位位置：[31:0]；默认值：0；最后一个内联描述符x-1的地址。
 */
#define CP_DMA_INLINK_DSCR_BF0    0xFFFFFFFF
#define CP_DMA_INLINK_DSCR_BF0_M  (CP_DMA_INLINK_DSCR_BF0_V << CP_DMA_INLINK_DSCR_BF0_S)
#define CP_DMA_INLINK_DSCR_BF0_V  0xFFFFFFFF
#define CP_DMA_INLINK_DSCR_BF0_S  0

/** CP_DMA_INLINK_DSCR_BF1_REG寄存器倒数第二个内联描述符的地址
 */
#define CP_DMA_INLINK_DSCR_BF1_REG (DR_REG_CP_BASE + 0x2c)
/** CP_DMA_INLINK_DSCR_BF1:RO；位位置：[31:0]；默认值：0；倒数第二个内联描述符x-2的地址。
 */
#define CP_DMA_INLINK_DSCR_BF1    0xFFFFFFFF
#define CP_DMA_INLINK_DSCR_BF1_M  (CP_DMA_INLINK_DSCR_BF1_V << CP_DMA_INLINK_DSCR_BF1_S)
#define CP_DMA_INLINK_DSCR_BF1_V  0xFFFFFFFF
#define CP_DMA_INLINK_DSCR_BF1_S  0

/** CP_DMA_OUTLINK_DSCR_REG寄存器当前输出链接描述符的地址
 */
#define CP_DMA_OUTLINK_DSCR_REG (DR_REG_CP_BASE + 0x30)
/** CP_DMA_OUTLINK_DSCR:RO；位位置：[31:0]；默认值：0；当前outlink描述符y的地址。
 */
#define CP_DMA_OUTLINK_DSCR    0xFFFFFFFF
#define CP_DMA_OUTLINK_DSCR_M  (CP_DMA_OUTLINK_DSCR_V << CP_DMA_OUTLINK_DSCR_S)
#define CP_DMA_OUTLINK_DSCR_V  0xFFFFFFFF
#define CP_DMA_OUTLINK_DSCR_S  0

/** CP_DMA_OUTLINK_DSCR_BF0_REG寄存器最后一个输出链接描述符的地址
 */
#define CP_DMA_OUTLINK_DSCR_BF0_REG (DR_REG_CP_BASE + 0x34)
/** CP_DMA_OUTLINK_DSCR_BF0:RO；位位置：[31:0]；默认值：0；最后一个outlink描述符y-1的地址。
 */
#define CP_DMA_OUTLINK_DSCR_BF0    0xFFFFFFFF
#define CP_DMA_OUTLINK_DSCR_BF0_M  (CP_DMA_OUTLINK_DSCR_BF0_V << CP_DMA_OUTLINK_DSCR_BF0_S)
#define CP_DMA_OUTLINK_DSCR_BF0_V  0xFFFFFFFF
#define CP_DMA_OUTLINK_DSCR_BF0_S  0

/** CP_DMA_OUTLINK_DSCR_BF1_REG寄存器倒数第二个输出链接描述符的地址
 */
#define CP_DMA_OUTLINK_DSCR_BF1_REG (DR_REG_CP_BASE + 0x38)
/** CP_DMA_OUTLINK_DSCR_BF1:RO；位位置：[31:0]；默认值：0；倒数第二个outlink描述符y-2的地址。
 */
#define CP_DMA_OUTLINK_DSCR_BF1    0xFFFFFFFF
#define CP_DMA_OUTLINK_DSCR_BF1_M  (CP_DMA_OUTLINK_DSCR_BF1_V << CP_DMA_OUTLINK_DSCR_BF1_S)
#define CP_DMA_OUTLINK_DSCR_BF1_V  0xFFFFFFFF
#define CP_DMA_OUTLINK_DSCR_BF1_S  0

/** CP_DMA_CONF_REG寄存器复制DMA配置寄存器
 */
#define CP_DMA_CONF_REG (DR_REG_CP_BASE + 0x3c)
/** CP_DMA_IN_RST:R/W；位位置：[0]；默认值：0；设置此位以重置in_inf状态机。
 */
#define CP_DMA_IN_RST    (BIT(0))
#define CP_DMA_IN_RST_M  (CP_DMA_IN_RST_V << CP_DMA_IN_RST_S)
#define CP_DMA_IN_RST_V  0x00000001
#define CP_DMA_IN_RST_S  0
/** CP_DMA_OUT_RST:R/W；位位置：[1]；默认值：0；设置此位以重置out_inf状态机。
 */
#define CP_DMA_OUT_RST    (BIT(1))
#define CP_DMA_OUT_RST_M  (CP_DMA_OUT_RST_V << CP_DMA_OUT_RST_S)
#define CP_DMA_OUT_RST_V  0x00000001
#define CP_DMA_OUT_RST_S  1
/** CP_DMA_CMDFIFO_RST:R/W；位位置：[2]；默认值：0；设置此位以重置in_cmd fifo和out_cmd fivo。
 */
#define CP_DMA_CMDFIFO_RST    (BIT(2))
#define CP_DMA_CMDFIFO_RST_M  (CP_DMA_CMDFIFO_RST_V << CP_DMA_CMDFIFO_RST_S)
#define CP_DMA_CMDFIFO_RST_V  0x00000001
#define CP_DMA_CMDFIFO_RST_S  2
/** CP_DMA_FIFO_RST:R/W；位位置：[3]；默认值：0；设置此位以重置接收FIFO中的数据。
 */
#define CP_DMA_FIFO_RST    (BIT(3))
#define CP_DMA_FIFO_RST_M  (CP_DMA_FIFO_RST_V << CP_DMA_FIFO_RST_S)
#define CP_DMA_FIFO_RST_V  0x00000001
#define CP_DMA_FIFO_RST_S  3
/** CP_DMA_OUT_OWNER:R/W；位位置：[4]；默认值：0；这用于配置OUT描述符中的所有者位。这仅在设置reg_out_auto_wrback时有效。
 */
#define CP_DMA_OUT_OWNER    (BIT(4))
#define CP_DMA_OUT_OWNER_M  (CP_DMA_OUT_OWNER_V << CP_DMA_OUT_OWNER_S)
#define CP_DMA_OUT_OWNER_V  0x00000001
#define CP_DMA_OUT_OWNER_S  4
/** CP_DMA_IN_OWNER:R/W；位位置：[5]；默认值：0；这用于配置in描述符中的所有者位。
 */
#define CP_DMA_IN_OWNER    (BIT(5))
#define CP_DMA_IN_OWNER_M  (CP_DMA_IN_OWNER_V << CP_DMA_IN_OWNER_S)
#define CP_DMA_IN_OWNER_V  0x00000001
#define CP_DMA_IN_OWNER_S  5
/** CP_DMA_OUT_AUTO_werback:R/W；位位置：[6]；默认值：0；当硬件已经使用此描述符时，此位用于写回描述符。
 */
#define CP_DMA_OUT_AUTO_WRBACK    (BIT(6))
#define CP_DMA_OUT_AUTO_WRBACK_M  (CP_DMA_OUT_AUTO_WRBACK_V << CP_DMA_OUT_AUTO_WRBACK_S)
#define CP_DMA_OUT_AUTO_WRBACK_V  0x00000001
#define CP_DMA_OUT_AUTO_WRBACK_S  6
/** CP_DMA_CHECK_OWNER:R/W；位位置：[7]；默认值：0；设置此位以启用所有者位签入描述符。
 */
#define CP_DMA_CHECK_OWNER    (BIT(7))
#define CP_DMA_CHECK_OWNER_M  (CP_DMA_CHECK_OWNER_V << CP_DMA_CHECK_OWNER_S)
#define CP_DMA_CHECK_OWNER_V  0x00000001
#define CP_DMA_CHECK_OWNER_S  7
/** CP_DMA_CRC_CAL_RESET:R/W；位位置：[8]；默认值：0；设置此位以重置crc计算。
 */
#define CP_DMA_CRC_CAL_RESET    (BIT(8))
#define CP_DMA_CRC_CAL_RESET_M  (CP_DMA_CRC_CAL_RESET_V << CP_DMA_CRC_CAL_RESET_S)
#define CP_DMA_CRC_CAL_RESET_V  0x00000001
#define CP_DMA_CRC_CAL_RESET_S  8
/** CP_DMA_CRC_CAL_EN:R/W；位位置：[9]；默认值：0；设置此位启用crc计算功能。
 */
#define CP_DMA_CRC_CAL_EN    (BIT(9))
#define CP_DMA_CRC_CAL_EN_M  (CP_DMA_CRC_CAL_EN_V << CP_DMA_CRC_CAL_EN_S)
#define CP_DMA_CRC_CAL_EN_V  0x00000001
#define CP_DMA_CRC_CAL_EN_S  9
/** CP_DMA_CRC_BIG_endin_EN:R/W；位位置：[10]；默认值：0；设置此位以重新排序将被发送以执行crc的数据位。
 */
#define CP_DMA_CRC_BIG_ENDIAN_EN    (BIT(10))
#define CP_DMA_CRC_BIG_ENDIAN_EN_M  (CP_DMA_CRC_BIG_ENDIAN_EN_V << CP_DMA_CRC_BIG_ENDIAN_EN_S)
#define CP_DMA_CRC_BIG_ENDIAN_EN_V  0x00000001
#define CP_DMA_CRC_BIG_ENDIAN_EN_S  10
/** CP_DMA_CRC_OUT_REVERSE_EN:R/W；位位置：[11]；默认值：0；设置此位以反转crc计算结果。
 */
#define CP_DMA_CRC_OUT_REVERSE_EN    (BIT(11))
#define CP_DMA_CRC_OUT_REVERSE_EN_M  (CP_DMA_CRC_OUT_REVERSE_EN_V << CP_DMA_CRC_OUT_REVERSE_EN_S)
#define CP_DMA_CRC_OUT_REVERSE_EN_V  0x00000001
#define CP_DMA_CRC_OUT_REVERSE_EN_S  11
/** CP_DMA_CLK_EN:R/W；位位置：[31]；默认值：0；1’b1：强制打开寄存器时钟。1’b0：仅当应用程序写入寄存器时才支持时钟。
 */
#define CP_DMA_CLK_EN    (BIT(31))
#define CP_DMA_CLK_EN_M  (CP_DMA_CLK_EN_V << CP_DMA_CLK_EN_S)
#define CP_DMA_CLK_EN_V  0x00000001
#define CP_DMA_CLK_EN_S  31

/** CP_DMA_IN_ST_REG寄存器接收数据的状态寄存器
 */
#define CP_DMA_IN_ST_REG (DR_REG_CP_BASE + 0x40)
/** CP_DMA_INLINK_DSCR_ADDR:RO；比特位置：[17:00]；默认值：0；此寄存器存储当前内联描述符的地址。
 */
#define CP_DMA_INLINK_DSCR_ADDR    0x0003FFFF
#define CP_DMA_INLINK_DSCR_ADDR_M  (CP_DMA_INLINK_DSCR_ADDR_V << CP_DMA_INLINK_DSCR_ADDR_S)
#define CP_DMA_INLINK_DSCR_ADDR_V  0x0003FFFF
#define CP_DMA_INLINK_DSCR_ADDR_S  0
/** CP_DMA_IN_DSCR_STATE:RO；比特位置：[19:18]；默认值：0；保留。
 */
#define CP_DMA_IN_DSCR_STATE    0x00000003
#define CP_DMA_IN_DSCR_STATE_M  (CP_DMA_IN_DSCR_STATE_V << CP_DMA_IN_DSCR_STATE_S)
#define CP_DMA_IN_DSCR_STATE_V  0x00000003
#define CP_DMA_IN_DSCR_STATE_S  18
/** CP_DMA_IN_STATE:RO；比特位置：[22:20]；默认值：0；保留。
 */
#define CP_DMA_IN_STATE    0x00000007
#define CP_DMA_IN_STATE_M  (CP_DMA_IN_STATE_V << CP_DMA_IN_STATE_S)
#define CP_DMA_IN_STATE_V  0x00000007
#define CP_DMA_IN_STATE_S  20
/** CP_DMA_FIFO_EMPTY:RO；位位置：[23]；默认值：0；复制DMA FIFO空信号。
 */
#define CP_DMA_FIFO_EMPTY    (BIT(23))
#define CP_DMA_FIFO_EMPTY_M  (CP_DMA_FIFO_EMPTY_V << CP_DMA_FIFO_EMPTY_S)
#define CP_DMA_FIFO_EMPTY_V  0x00000001
#define CP_DMA_FIFO_EMPTY_S  23

/** CP_DMA_OUT_ST_REG寄存器传输数据状态寄存器
 */
#define CP_DMA_OUT_ST_REG (DR_REG_CP_BASE + 0x44)
/** CP_DMA_OUTLINK_DSCR_ADDR:RO；比特位置：[17:00]；默认值：0；此寄存器存储当前outlink描述符的地址。
 */
#define CP_DMA_OUTLINK_DSCR_ADDR    0x0003FFFF
#define CP_DMA_OUTLINK_DSCR_ADDR_M  (CP_DMA_OUTLINK_DSCR_ADDR_V << CP_DMA_OUTLINK_DSCR_ADDR_S)
#define CP_DMA_OUTLINK_DSCR_ADDR_V  0x0003FFFF
#define CP_DMA_OUTLINK_DSCR_ADDR_S  0
/** CP_DMA_OUT_DSCR_STATE:RO；比特位置：[19:18]；默认值：0；保留。
 */
#define CP_DMA_OUT_DSCR_STATE    0x00000003
#define CP_DMA_OUT_DSCR_STATE_M  (CP_DMA_OUT_DSCR_STATE_V << CP_DMA_OUT_DSCR_STATE_S)
#define CP_DMA_OUT_DSCR_STATE_V  0x00000003
#define CP_DMA_OUT_DSCR_STATE_S  18
/** CP_DMA_OUT_STATE:RO；比特位置：[22:20]；默认值：0；保留。
 */
#define CP_DMA_OUT_STATE    0x00000007
#define CP_DMA_OUT_STATE_M  (CP_DMA_OUT_STATE_V << CP_DMA_OUT_STATE_S)
#define CP_DMA_OUT_STATE_V  0x00000007
#define CP_DMA_OUT_STATE_S  20
/** CP_DMA_FIFO_FULL:RO；位位置：[23]；默认值：0；复制DMA FIFO满信号。
 */
#define CP_DMA_FIFO_FULL    (BIT(23))
#define CP_DMA_FIFO_FULL_M  (CP_DMA_FIFO_FULL_V << CP_DMA_FIFO_FULL_S)
#define CP_DMA_FIFO_FULL_V  0x00000001
#define CP_DMA_FIFO_FULL_S  23

/** CP_DMA_CRC_OUT_REG寄存器CRC结果寄存器
 */
#define CP_DMA_CRC_OUT_REG (DR_REG_CP_BASE + 0x48)
/** CP_DMA_CRC_RESULT:RO；位位置：[31:0]；默认值：0；该寄存器存储CRC的结果。
 */
#define CP_DMA_CRC_RESULT    0xFFFFFFFF
#define CP_DMA_CRC_RESULT_M  (CP_DMA_CRC_RESULT_V << CP_DMA_CRC_RESULT_S)
#define CP_DMA_CRC_RESULT_V  0xFFFFFFFF
#define CP_DMA_CRC_RESULT_S  0

/** CP_DMA_DATE_REG寄存器复制DMA版本寄存器
 */
#define CP_DMA_DATE_REG (DR_REG_CP_BASE + 0xfc)
/** CP_DMA_DMA_DATE:R/W；位位置：[31:0]；默认值：403185664；这是版本寄存器。
 */
#define CP_DMA_DMA_DATE    0xFFFFFFFF
#define CP_DMA_DMA_DATE_M  (CP_DMA_DMA_DATE_V << CP_DMA_DMA_DATE_S)
#define CP_DMA_DMA_DATE_V  0xFFFFFFFF
#define CP_DMA_DMA_DATE_S  0

#ifdef __cplusplus
}
#endif

