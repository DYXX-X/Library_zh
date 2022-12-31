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
#ifndef _SOC_CRYPTO_DMA_REG_H_
#define _SOC_CRYPTO_DMA_REG_H_


#ifdef __cplusplus
extern "C" {
#endif
#include "soc.h"

/* CRYPTO_DMA_CONF0:RO；比特位置：[31:14]；默认值：18'0；*/
/* CONF0_REG_GEN_CLK_EN:RW；位位置：[13]；默认值：1’b0；*/
/*说明：*/
#define CONF0_REG_GEN_CLK_EN   (BIT(13))
#define CONF0_REG_GEN_CLK_EN_M (BIT(13))
#define CONF0_REG_GEN_CLK_EN_V 0x1
#define CONF0_REG_GEN_CLK_EN_S 13
/* CONF0_REG_MEM_TRANS_EN:RW；位位置：[12]；默认值：1’b0；*/
/*说明：*/
#define CONF0_REG_MEM_TRANS_EN   (BIT(12))
#define CONF0_REG_MEM_TRANS_EN_M (BIT(12))
#define CONF0_REG_MEM_TRANS_EN_V 0x1
#define CONF0_REG_MEM_TRANS_EN_S 12
/* CONF0_REG_OUT_DATA_BURST_EN:RW；位位置：[11]；默认值：1’b0；*/
/*说明：*/
#define CONF0_REG_OUT_DATA_BURST_EN   (BIT(11))
#define CONF0_REG_OUT_DATA_BURST_EN_M (BIT(11))
#define CONF0_REG_OUT_DATA_BURST_EN_V 0x1
#define CONF0_REG_OUT_DATA_BURST_EN_S 11
/* CONF0_REG_indcr_BURST_EN:RW；位位置：[10]；默认值：1’b0；*/
/*说明：*/
#define CONF0_REG_INDSCR_BURST_EN   (BIT(10))
#define CONF0_REG_INDSCR_BURST_EN_M  (BIT(10))
#define CONF0_REG_INDSCR_BURST_EN_V  0x1
#define CONF0_REG_INDSCR_BURST_EN_S  10
/* CONF0_REG_OUTDSCR_BURST_EN:RW；位位置：[9]；默认值：1’b0；*/
/*说明：*/
#define CONF0_REG_OUTDSCR_BURST_EN   (BIT(9))
#define CONF0_REG_OUTDSCR_BURST_EN_M  (BIT(9))
#define CONF0_REG_OUTDSCR_BURST_EN_V  0x1
#define CONF0_REG_OUTDSCR_BURST_EN_S  9
/* CONF0_REG_OUT_EOF_MODE：RW；位位置：[8]；默认值：1’b0；*/
/*说明：*/
#define CONF0_REG_OUT_EOF_MODE   (BIT(8))
#define CONF0_REG_OUT_EOF_MODE_M  (BIT(8))
#define CONF0_REG_OUT_EOF_MODE_V  0x1
#define CONF0_REG_OUT_EOF_MODE_S  8
/* CONF0_REG_OUT_NO_RESTART_CLR:RW；位位置：[7]；默认值：1’b0；*/
/*说明：*/
#define CONF0_REG_OUT_NO_RESTART_CLR   (BIT(7))
#define CONF0_REG_OUT_NO_RESTART_CLR_M  (BIT(7))
#define CONF0_REG_OUT_NO_RESTART_CLR_V  0x1
#define CONF0_REG_OUT_NO_RESTART_CLR_S  7
/* CONF0_REG_OUT_AUTO_werback:RW；位位置：[6]；默认值：1’b0；*/
/*说明：*/
#define CONF0_REG_OUT_AUTO_WRBACK   (BIT(6))
#define CONF0_REG_OUT_AUTO_WRBACK_M  (BIT(6))
#define CONF0_REG_OUT_AUTO_WRBACK_V  0x1
#define CONF0_REG_OUT_AUTO_WRBACK_S  6
/* CONF0_REG_OUT_LOOP_TEST:RW；位位置：[5]；默认值：1’b0；*/
/*说明：*/
#define CONF0_REG_OUT_LOOP_TEST   (BIT(5))
#define CONF0_REG_OUT_LOOP_TEST_M  (BIT(5))
#define CONF0_REG_OUT_LOOP_TEST_V  0x1
#define CONF0_REG_OUT_LOOP_TEST_S  5
/* CONF0_REG_IN_LOOP_TEST:RW；位位置：[4]；默认值：1’b0；*/
/*说明：*/
#define CONF0_REG_IN_LOOP_TEST   (BIT(4))
#define CONF0_REG_IN_LOOP_TEST_M  (BIT(4))
#define CONF0_REG_IN_LOOP_TEST_V  0x1
#define CONF0_REG_IN_LOOP_TEST_S  4
/* CONF0_REG_AHBM_RST:RW；位位置：[3]；默认值：1’b0；*/
/*说明：*/
#define CONF0_REG_AHBM_RST   (BIT(3))
#define CONF0_REG_AHBM_RST_M  (BIT(3))
#define CONF0_REG_AHBM_RST_V  0x1
#define CONF0_REG_AHBM_RST_S  3
/* CONF0_REG_AHBM_FIFO_RST:RW；位位置：[2]；默认值：1’b0；*/
/*说明：*/
#define CONF0_REG_AHBM_FIFO_RST   (BIT(2))
#define CONF0_REG_AHBM_FIFO_RST_M  (BIT(2))
#define CONF0_REG_AHBM_FIFO_RST_V  0x1
#define CONF0_REG_AHBM_FIFO_RST_S  2
/* CONF0_REG_OUT_RST:RW；位位置：[1]；默认值：1’b0；*/
/*说明：*/
#define CONF0_REG_OUT_RST   (BIT(1))
#define CONF0_REG_OUT_RST_M  (BIT(1))
#define CONF0_REG_OUT_RST_V  0x1
#define CONF0_REG_OUT_RST_S  1
/* CONF0_REG_IN_RST:RW；位位置：[0]；默认值：1’b0；*/
/*说明：*/
#define CONF0_REG_IN_RST   (BIT(0))
#define CONF0_REG_IN_RST_M  (BIT(0))
#define CONF0_REG_IN_RST_V  0x1
#define CONF0_REG_IN_RST_S  0
/* CRYPTO_DMA_INT_RAW:RO；比特位置：[31:10]；默认值：22'h0；*/
/* INT_RAW_OUT_TOTAL_EOF:RW；位位置：[8]；默认值：1’b0；*/
/*说明：*/
#define INT_RAW_OUT_TOTAL_EOF  ( BIT(8))
#define INT_RAW_OUT_TOTAL_EOF_M  (BIT(8))
#define INT_RAW_OUT_TOTAL_EOF_V  0x1
#define INT_RAW_OUT_TOTAL_EOF_S  8
/* INT_RAW_IN_SUC_EOF:RW；位位置：[1]；默认值：1’b0；*/
/*说明：*/
#define INT_RAW_IN_SUC_EOF  ( BIT(1))
#define INT_RAW_IN_SUC_EOF_M  (BIT(1))
#define INT_RAW_IN_SUC_EOF_V  0x1
#define INT_RAW_IN_SUC_EOF_S  1
/* CRYPTO_DMA_OUT_LINK:RO；位位置：[31]；默认值：1'0；*/
/* OUT_LINK_REG_OUTLINK_RESTART：RW；位位置：[30]；默认值：1’b0；*/
/*说明：*/
#define OUT_LINK_REG_OUTLINK_RESTART  ( BIT(30))
#define OUT_LINK_REG_OUTLINK_RESTART_M  (BIT(30))
#define OUT_LINK_REG_OUTLINK_RESTART_V  0x1
#define OUT_LINK_REG_OUTLINK_RESTART_S  30
/* OUT_LINK_REG_OUTLINK_START:RW；位位置：[29]；默认值：1’b0；*/
/*说明：*/
#define OUT_LINK_REG_OUTLINK_START  ( BIT(29))
#define OUT_LINK_REG_OUTLINK_START_M  (BIT(29))
#define OUT_LINK_REG_OUTLINK_START_V  0x1
#define OUT_LINK_REG_OUTLINK_START_S  29
/* OUT_LINK_REG_OUTLINK_STOP:RW；位位置：[28]；默认值：1’b0；*/
/*说明：*/
#define OUT_LINK_REG_OUTLINK_STOP  ( BIT(28))
#define OUT_LINK_REG_OUTLINK_STOP_M  (BIT(28))
#define OUT_LINK_REG_OUTLINK_STOP_V  0x1
#define OUT_LINK_REG_OUTLINK_STOP_S  28
/* OUT_LINK_REG_OUTLINK_ADDR:RW；比特位置：[19:0]；默认值：20'00；*/
/*说明：*/
#define OUT_LINK_REG_OUTLINK_ADDR  0x000FFFFF
#define OUT_LINK_REG_OUTLINK_ADDR_M  (OUT_LINK_REG_OUTLINK_ADDR_V<<OUT_LINK_REG_OUTLINK_ADDR_S)
#define OUT_LINK_REG_OUTLINK_ADDR_V  0xFFFFF
#define OUT_LINK_REG_OUTLINK_ADDR_S  0
/* CRYPTO_DMA_IN_LINK:RO；位位置：[31]；默认值：1'0；*/
/* IN_LINK_REG_INLINK_RESTART：RW；位位置：[30]；默认值：1’b0；*/
/*说明：*/
#define IN_LINK_REG_INLINK_RESTART  ( BIT(30))
#define IN_LINK_REG_INLINK_RESTART_M  (BIT(30))
#define IN_LINK_REG_INLINK_RESTART_V  0x1
#define IN_LINK_REG_INLINK_RESTART_S  30
/* IN_LINK_REG_INLINK_START:RW；位位置：[29]；默认值：1’b0；*/
/*说明：*/
#define IN_LINK_REG_INLINK_START  ( BIT(29))
#define IN_LINK_REG_INLINK_START_M  (BIT(29))
#define IN_LINK_REG_INLINK_START_V  0x1
#define IN_LINK_REG_INLINK_START_S  29
/* IN_LINK_REG_INLINK_STOP:RW；位位置：[28]；默认值：1’b0；*/
/*说明：*/
#define IN_LINK_REG_INLINK_STOP  ( BIT(28))
#define IN_LINK_REG_INLINK_STOP_M  (BIT(28))
#define IN_LINK_REG_INLINK_STOP_V  0x1
#define IN_LINK_REG_INLINK_STOP_S  28
/* IN_LINK_REG_INLINK_ADDR:RW；比特位置：[19:0]；默认值：20'00；*/
/*说明：*/
#define IN_LINK_REG_INLINK_ADDR  0x000FFFFF
#define IN_LINK_REG_INLINK_ADDR_M  (IN_LINK_REG_INLINK_ADDR_V<<IN_LINK_REG_INLINK_ADDR_S)
#define IN_LINK_REG_INLINK_ADDR_V  0xFFFFF
#define IN_LINK_REG_INLINK_ADDR_S  0
/* CRYPTO_DMA_AES_SHA_SELECT:RO；位位置：[31:1]；默认值：31'b0；*/
/* AES_SHA_SELECT:RW；位位置：[0]；默认值：1’b0；*/
/*说明：*/
#define AES_SHA_SELECT  ( BIT(0))
#define AES_SHA_SELECT_M  (BIT(0))
#define AES_SHA_SELECT_V  0x1
#define AES_SHA_SELECT_S  0

#ifdef __cplusplus
}
#endif



#endif /*_SOC_CRYPTO_DMA_REG_H_ */

