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
#ifndef _SOC_SPI_REG_H_
#define _SOC_SPI_REG_H_


#ifdef __cplusplus
extern "C" {
#endif
#include "soc.h"

#define SPI_CMD_REG(i)          (REG_SPI_BASE(i) + 0x0)
/* SPI_USR:R/W/SC；位位置：[24]；默认值：1’b0；*/
/*description:用户定义命令启用。设置位时将触发操作。操作完成后，该位将被清除。1： 启用0：禁用。无法通过CONF_buf更改。。*/
#define SPI_USR    (BIT(24))
#define SPI_USR_M  (BIT(24))
#define SPI_USR_V  0x1
#define SPI_USR_S  24
/* SPI_UPDATE:WT；位位置：[23]；默认值：1’b0；*/
/*description:设置此位以将SPI寄存器从APB时钟域同步到SPI模块时钟域，这仅用于SPI主模式。。*/
#define SPI_UPDATE    (BIT(23))
#define SPI_UPDATE_M  (BIT(23))
#define SPI_UPDATE_V  0x1
#define SPI_UPDATE_S  23
/* SPI_CONF_BITLEN:R/W；比特位置：[17:00]；默认值：18'd0；*/
/*description:定义SPI_CONF状态的APB周期。可在形态状态下配置。。*/
#define SPI_CONF_BITLEN    0x0003FFFF
#define SPI_CONF_BITLEN_M  ((SPI_CONF_BITLEN_V)<<(SPI_CONF_BITLEN_S))
#define SPI_CONF_BITLEN_V  0x3FFFF
#define SPI_CONF_BITLEN_S  0

#define SPI_ADDR_REG(i)          (REG_SPI_BASE(i) + 0x4)
/* SPI_USR_ADDR_VALUE：R/W；位位置：[31:0]；默认值：32'b0；*/
/*description:从设备的地址。可在形态状态下配置。。*/
#define SPI_USR_ADDR_VALUE    0xFFFFFFFF
#define SPI_USR_ADDR_VALUE_M  ((SPI_USR_ADDR_VALUE_V)<<(SPI_USR_ADDR_VALUE_S))
#define SPI_USR_ADDR_VALUE_V  0xFFFFFFFF
#define SPI_USR_ADDR_VALUE_S  0

#define SPI_CTRL_REG(i)          (REG_SPI_BASE(i) + 0x008)
/* SPI_WR_BIT_ORDER:R/W；比特位置：[26:25]；默认值：2’b0；*/
/*description:在命令地址写入数据（MOSI）阶段1:LSB首先0:MSB。可在形态状态下配置。*/
#define SPI_WR_BIT_ORDER  0x00000003
#define SPI_WR_BIT_ORDER_M  ((SPI_WR_BIT_ORDER_V)<<(SPI_WR_BIT_ORDER_S))
#define SPI_WR_BIT_ORDER_V  0x3
#define SPI_WR_BIT_ORDER_S  25
/* SPI_RD_BIT_ORDER:R/W；位位置：[24:23]；默认值：2’b0；*/
/*描述：在读取数据（MISO）阶段1:LSB优先0:MSB优先。可在形态状态下配置。*/
#define SPI_RD_BIT_ORDER  0x00000003
#define SPI_RD_BIT_ORDER_M  ((SPI_RD_BIT_ORDER_V)<<(SPI_RD_BIT_ORDER_S))
#define SPI_RD_BIT_ORDER_V  0x3
#define SPI_RD_BIT_ORDER_S  23
/* SPI_WP_POL:R/W；位位置：[21]；默认值：1’b1；*/
/*description:SPI空闲时写保护信号输出。1： 输出高，0：输出低。可在形态状态下配置。。*/
#define SPI_WP_POL    (BIT(21))
#define SPI_WP_POL_M  (BIT(21))
#define SPI_WP_POL_V  0x1
#define SPI_WP_POL_S  21
/* SPI_HOLD_POL:R/W；位位置：[20]；默认值：1’b1；*/
/*description:SPI空闲时的SPI_HOLD输出值。1： 输出高，0：输出低。可在形态状态下配置。。*/
#define SPI_HOLD_POL    (BIT(20))
#define SPI_HOLD_POL_M  (BIT(20))
#define SPI_HOLD_POL_V  0x1
#define SPI_HOLD_POL_S  20
/* SPI_D_POL:R/W；位位置：[19]；默认值：1’b1；*/
/*description:该位用于设置MOSI线极性，1：高0，低。可在CONF状态下配置。。*/
#define SPI_D_POL    (BIT(19))
#define SPI_D_POL_M  (BIT(19))
#define SPI_D_POL_V  0x1
#define SPI_D_POL_S  19
/* SPI_Q_POL:R/W；位位置：[18]；默认值：1’b1；*/
/*description:该位用于设置MISO线极性，1：高0，低。可在CONF状态下配置。。*/
#define SPI_Q_POL    (BIT(18))
#define SPI_Q_POL_M  (BIT(18))
#define SPI_Q_POL_V  0x1
#define SPI_Q_POL_S  18
/* SPI_FREAD_QUAD:R/W；位位置：[15]；默认值：1’b0；*/
/*描述：在读取操作中，读取数据阶段应用4个信号。1： 启用0：禁用。可在形态状态下配置。。*/
#define SPI_FREAD_QUAD    (BIT(15))
#define SPI_FREAD_QUAD_M  (BIT(15))
#define SPI_FREAD_QUAD_V  0x1
#define SPI_FREAD_QUAD_S  15
/* SPI_FREAD_DUAL:R/W；位位置：[14]；默认值：1’b0；*/
/*description:在读取操作中，读取数据阶段应用2个信号。1： 启用0：禁用。可在形态状态下配置。。*/
#define SPI_FREAD_DUAL    (BIT(14))
#define SPI_FREAD_DUAL_M  (BIT(14))
#define SPI_FREAD_DUAL_V  0x1
#define SPI_FREAD_DUAL_S  14
/* SPI_FCMD_QUAD:R/W；位位置：[9]；默认值：1’b0；*/
/*description:在命令阶段1：启用0：禁用期间应用4个信号。可在形态状态下配置。。*/
#define SPI_FCMD_QUAD    (BIT(9))
#define SPI_FCMD_QUAD_M  (BIT(9))
#define SPI_FCMD_QUAD_V  0x1
#define SPI_FCMD_QUAD_S  9
/* SPI_FCMD_DUAL:R/W；位位置：[8]；默认值：1’b0；*/
/*description:在命令阶段1：启用0：禁用期间应用2个信号。可在形态状态下配置。。*/
#define SPI_FCMD_DUAL    (BIT(8))
#define SPI_FCMD_DUAL_M  (BIT(8))
#define SPI_FCMD_DUAL_V  0x1
#define SPI_FCMD_DUAL_S  8
/* SPI_FADDR_QUAD:R/W；位位置：[6]；默认值：1’b0；*/
/*description:在addr阶段1：启用0：禁用期间应用4个信号。可在形态状态下配置。。*/
#define SPI_FADDR_QUAD    (BIT(6))
#define SPI_FADDR_QUAD_M  (BIT(6))
#define SPI_FADDR_QUAD_V  0x1
#define SPI_FADDR_QUAD_S  6
/* SPI_FADDR_DUAL:R/W；位位置：[5]；默认值：1’b0；*/
/*description:在addr阶段1：启用0：禁用期间应用2个信号。可在形态状态下配置。。*/
#define SPI_FADDR_DUAL    (BIT(5))
#define SPI_FADDR_DUAL_M  (BIT(5))
#define SPI_FADDR_DUAL_V  0x1
#define SPI_FADDR_DUAL_S  5
/* SPI_DUMMY_OUT:R/W；位位置：[3]；默认值：1’b0；*/
/*描述：在虚拟阶段，spi的信号电平由spi控制器输出。可以配置为CONF状态。。*/
#define SPI_DUMMY_OUT    (BIT(3))
#define SPI_DUMMY_OUT_M  (BIT(3))
#define SPI_DUMMY_OUT_V  0x1
#define SPI_DUMMY_OUT_S  3

#define SPI_CLOCK_REG(i)          (REG_SPI_BASE(i) + 0xC)
/* SPI_CLK_EQU_SYSCLK:R/W；位位置：[31]；默认值：1’b1；*/
/*description:在主模式1中：spi_clk与系统0相等：spi_clk与系统时钟分开。可在形态状态下配置。。*/
#define SPI_CLK_EQU_SYSCLK    (BIT(31))
#define SPI_CLK_EQU_SYSCLK_M  (BIT(31))
#define SPI_CLK_EQU_SYSCLK_V  0x1
#define SPI_CLK_EQU_SYSCLK_S  31
/* SPI_CLKDIV_PRE:R/W；比特位置：[21:18]；默认值：4'b0；*/
/*description:在主模式下，它是spi_clk的预除法器。可在形态状态下配置。。*/
#define SPI_CLKDIV_PRE    0x0000000F
#define SPI_CLKDIV_PRE_M  ((SPI_CLKDIV_PRE_V)<<(SPI_CLKDIV_PRE_S))
#define SPI_CLKDIV_PRE_V  0xF
#define SPI_CLKDIV_PRE_S  18
/* SPI_CLKCNT_N:R/W；比特位置：[17:12]；默认值：6'h3；*/
/*description:在主模式下，它是spi_clk的除法器。因此spi_clk频率为系统/（spi_clkdiv_pre+1）/（spi_clkcnt_N+1）。可在形态状态下配置。。*/
#define SPI_CLKCNT_N    0x0000003F
#define SPI_CLKCNT_N_M  ((SPI_CLKCNT_N_V)<<(SPI_CLKCNT_N_S))
#define SPI_CLKCNT_N_V  0x3F
#define SPI_CLKCNT_N_S  12
/* SPI_CLKCNT_H:R/W；位位置：[11:6]；默认值：6'h1；*/
/*description:在主模式下，它必须是floor（（spi_clkcnt_N+1）/2-1）。在从属模式下，它必须为0。可以在CONF状态下配置。。*/
#define SPI_CLKCNT_H    0x0000003F
#define SPI_CLKCNT_H_M  ((SPI_CLKCNT_H_V)<<(SPI_CLKCNT_H_S))
#define SPI_CLKCNT_H_V  0x3F
#define SPI_CLKCNT_H_S  6
/* SPI_CLKCNT_L:R/W；比特位置：[5:0]；默认值：6'h3；*/
/*description:在主模式下，它必须等于spi_clkcnt_N。在从属模式下，它必须为0。可以在CONF状态下配置。。*/
#define SPI_CLKCNT_L    0x0000003F
#define SPI_CLKCNT_L_M  ((SPI_CLKCNT_L_V)<<(SPI_CLKCNT_L_S))
#define SPI_CLKCNT_L_V  0x3F
#define SPI_CLKCNT_L_S  0

#define SPI_USER_REG(i)          (REG_SPI_BASE(i) + 0x10)
/* SPI_USR_COMMAND：R/W；位位置：[31]；默认值：1’b1；*/
/*description:此位启用操作的命令阶段。可在形态状态下配置。。*/
#define SPI_USR_COMMAND    (BIT(31))
#define SPI_USR_COMMAND_M  (BIT(31))
#define SPI_USR_COMMAND_V  0x1
#define SPI_USR_COMMAND_S  31
/* SPI_USR_ADDR:R/W；位位置：[30]；默认值：1’b0；*/
/*description:此位启用操作的地址阶段。可在形态状态下配置。。*/
#define SPI_USR_ADDR    (BIT(30))
#define SPI_USR_ADDR_M  (BIT(30))
#define SPI_USR_ADDR_V  0x1
#define SPI_USR_ADDR_S  30
/* SPI_USR_DUMMY:R/W；位位置：[29]；默认值：1’b0；*/
/*description: 此位启用操作的虚拟阶段。可在形态状态下配置
..*/
#define SPI_USR_DUMMY    (BIT(29))
#define SPI_USR_DUMMY_M  (BIT(29))
#define SPI_USR_DUMMY_V  0x1
#define SPI_USR_DUMMY_S  29
/* SPI_USR_MISO:R/W；位位置：[28]；默认值：1’b0；*/
/*description:此位启用操作的读取数据阶段。可在形态状态下配置。。*/
#define SPI_USR_MISO    (BIT(28))
#define SPI_USR_MISO_M  (BIT(28))
#define SPI_USR_MISO_V  0x1
#define SPI_USR_MISO_S  28
/* SPI_USR_MOSI:R/W；位位置：[27]；默认值：1’b0；*/
/*description:此位启用操作的写入数据阶段。可在配置状态下配置。。*/
#define SPI_USR_MOSI    (BIT(27))
#define SPI_USR_MOSI_M  (BIT(27))
#define SPI_USR_MOSI_V  0x1
#define SPI_USR_MOSI_S  27
/* SPI_USR_dumm_IDLE:R/W；位位置：[26]；默认值：1’b0；*/
/*描述：当位被启用时，spi时钟在虚拟阶段被禁用。可在形态状态下配置。。*/
#define SPI_USR_DUMMY_IDLE    (BIT(26))
#define SPI_USR_DUMMY_IDLE_M  (BIT(26))
#define SPI_USR_DUMMY_IDLE_V  0x1
#define SPI_USR_DUMMY_IDLE_S  26
/* SPI_USR_MOSI-HIGHPART:R/W；位位置：[25]；默认值：1’b0；*/
/*描述：写入数据阶段仅访问缓冲区的高部分spiw8～spiw15。1：启用0：禁用。可在形态状态下配置。。*/
#define SPI_USR_MOSI_HIGHPART    (BIT(25))
#define SPI_USR_MOSI_HIGHPART_M  (BIT(25))
#define SPI_USR_MOSI_HIGHPART_V  0x1
#define SPI_USR_MOSI_HIGHPART_S  25
/* SPI_USR_MISO_HIGHPART:R/W；位位置：[24]；默认值：1’b0；*/
/*描述：读取数据阶段仅访问缓冲区的高部分spiw8～spiw15。1：启用0：禁用。可在形态状态下配置。。*/
#define SPI_USR_MISO_HIGHPART    (BIT(24))
#define SPI_USR_MISO_HIGHPART_M  (BIT(24))
#define SPI_USR_MISO_HIGHPART_V  0x1
#define SPI_USR_MISO_HIGHPART_S  24
/* SPI_SIO:R/W；位位置：[17]；默认值：1’b0；*/
/*description:设置该位以启用3线半双工通信mosi和miso信号共享同一引脚。1： 启用0：禁用。可在形态状态下配置。。*/
#define SPI_SIO    (BIT(17))
#define SPI_SIO_M  (BIT(17))
#define SPI_SIO_V  0x1
#define SPI_SIO_S  17
/* SPI_USR_CONF_NXT：R/W；位位置：[15]；默认值：1’b0；*/
/*description:1：启用下一个seg传输操作的DMA CONF阶段，这意味着seg传输将继续。0：分段传输将在当前SPI分段传输之后结束，或者这不是分段传输模式。可在形态状态下配置。。*/
#define SPI_USR_CONF_NXT    (BIT(15))
#define SPI_USR_CONF_NXT_M  (BIT(15))
#define SPI_USR_CONF_NXT_V  0x1
#define SPI_USR_CONF_NXT_S  15
/* SPI_FWRITE_QUAD:R/W；位位置：[13]；默认值：1’b0；*/
/*描述：在写入操作中，读取数据阶段应用4个信号。可在形态状态下配置。。*/
#define SPI_FWRITE_QUAD    (BIT(13))
#define SPI_FWRITE_QUAD_M  (BIT(13))
#define SPI_FWRITE_QUAD_V  0x1
#define SPI_FWRITE_QUAD_S  13
/* SPI_FWRITE_DUAL:R/W；位位置：[12]；默认值：1’b0；*/
/*描述：在写入操作中，读取数据阶段应用2个信号。可在形态状态下配置。。*/
#define SPI_FWRITE_DUAL    (BIT(12))
#define SPI_FWRITE_DUAL_M  (BIT(12))
#define SPI_FWRITE_DUAL_V  0x1
#define SPI_FWRITE_DUAL_S  12
/* SPI_CK_OUT_EDGE：R/W；位位置：[9]；默认值：1’b0；*/
/*描述：该位与spi_mosidelaymode位组合以设置mosi信号延迟模式。可在形态状态下配置。。*/
#define SPI_CK_OUT_EDGE    (BIT(9))
#define SPI_CK_OUT_EDGE_M  (BIT(9))
#define SPI_CK_OUT_EDGE_V  0x1
#define SPI_CK_OUT_EDGE_S  9
/* SPI_rscki_EDGE:R/W；位位置：[8]；默认值：1’b0；*/
/*description:在从属模式下，此位可用于更改rsck的极性。0:rsck=！spi_ck_。1： rsck=spi_ck_i。。*/
#define SPI_RSCK_I_EDGE    (BIT(8))
#define SPI_RSCK_I_EDGE_M  (BIT(8))
#define SPI_RSCK_I_EDGE_V  0x1
#define SPI_RSCK_I_EDGE_S  8
/* SPI_CS_SETUP:R/W；位位置：[7]；默认值：1’b1；*/
/*描述：当spi处于准备阶段时，启用spi cs。1： 启用0：禁用。可在形态状态下配置。。*/
#define SPI_CS_SETUP    (BIT(7))
#define SPI_CS_SETUP_M  (BIT(7))
#define SPI_CS_SETUP_V  0x1
#define SPI_CS_SETUP_S  7
/* SPI_CS_HOLD:R/W；位位置：[6]；默认值：1’b1；*/
/*描述：当spi处于完成阶段时，spi cs保持低。1： 启用0：禁用。可在形态状态下配置。。*/
#define SPI_CS_HOLD    (BIT(6))
#define SPI_CS_HOLD_M  (BIT(6))
#define SPI_CS_HOLD_V  0x1
#define SPI_CS_HOLD_S  6
/* SPI_tscki_EDGE:R/W；位位置：[5]；默认值：1’b0；*/
/*description:在从属模式下，此位可用于更改tsck的极性。0:tsck=spi_ck_i。1： tsck=！spi_ck_i。。*/
#define SPI_TSCK_I_EDGE    (BIT(5))
#define SPI_TSCK_I_EDGE_M  (BIT(5))
#define SPI_TSCK_I_EDGE_V  0x1
#define SPI_TSCK_I_EDGE_S  5
/* SPI_QPI_MODE：R/W/SS/SC；位位置：[3]；默认值：1’b0；*/
/*description:主模式和从模式。1： spi控制器处于QPI模式。0：其他。可在形态状态下配置。。*/
#define SPI_QPI_MODE    (BIT(3))
#define SPI_QPI_MODE_M  (BIT(3))
#define SPI_QPI_MODE_V  0x1
#define SPI_QPI_MODE_S  3
/* SPI_DOUTDIN:R/W；位位置：[0]；默认值：1’b0；*/
/*description:设置位以启用全双工通信。1： 启用0：禁用。可在形态状态下配置。。*/
#define SPI_DOUTDIN    (BIT(0))
#define SPI_DOUTDIN_M  (BIT(0))
#define SPI_DOUTDIN_V  0x1
#define SPI_DOUTDIN_S  0

#define SPI_USER1_REG(i)          (REG_SPI_BASE(i) + 0x14)
/* SPI_USR_ADDR_title：R/W；位位置：[31:27]；默认值：5'd23；*/
/*description:地址相位的长度（以位为单位）。寄存器值应为（bit_num-1）。可在形态状态下配置。。*/
#define SPI_USR_ADDR_BITLEN    0x0000001F
#define SPI_USR_ADDR_BITLEN_M  ((SPI_USR_ADDR_BITLEN_V)<<(SPI_USR_ADDR_BITLEN_S))
#define SPI_USR_ADDR_BITLEN_V  0x1F
#define SPI_USR_ADDR_BITLEN_S  27
/* SPI_CS_HOLD_TIME:R/W；比特位置：[26:22]；默认值：5'h1；*/
/*描述：cs引脚的spi时钟延迟周期此位与spicshold位组合。可在形态状态下配置。。*/
#define SPI_CS_HOLD_TIME    0x0000001F
#define SPI_CS_HOLD_TIME_M  ((SPI_CS_HOLD_TIME_V)<<(SPI_CS_HOLD_TIME_S))
#define SPI_CS_HOLD_TIME_V  0x1F
#define SPI_CS_HOLD_TIME_S  22
/* SPI_CS_SETUP_TIME:R/W；比特位置：[21:17]；默认值：5’b0；*/
/*描述：spi时钟准备阶段的（周期+1）此位与spicssetup位组合。可在形态状态下配置。。*/
#define SPI_CS_SETUP_TIME    0x0000001F
#define SPI_CS_SETUP_TIME_M  ((SPI_CS_SETUP_TIME_V)<<(SPI_CS_SETUP_TIME_S))
#define SPI_CS_SETUP_TIME_V  0x1F
#define SPI_CS_SETUP_TIME_S  17
/* SPI_MST_WFULL_ERR_END_EN:R/W；位位置：[16]；默认值：1’b1；*/
/*描述：1：当SPI RX AFIFO wfull错误在GP-SPI主FD/HD模式下有效时，SPI传输结束。0:当SPI RX AFIFO wfull错误在GP-SPI主FD/HD模式下有效时，SPI传输未结束。。*/
#define SPI_MST_WFULL_ERR_END_EN    (BIT(16))
#define SPI_MST_WFULL_ERR_END_EN_M  (BIT(16))
#define SPI_MST_WFULL_ERR_END_EN_V  0x1
#define SPI_MST_WFULL_ERR_END_EN_S  16
/* SPI_USR_DUMMY_CYCLELEN:R/W；位位置：[7:0]；默认值：8'd7；*/
/*description:虚拟相位的spi_clk周期长度。寄存器值应为（cycle_num-1）。可在形态状态下配置。。*/
#define SPI_USR_DUMMY_CYCLELEN    0x000000FF
#define SPI_USR_DUMMY_CYCLELEN_M  ((SPI_USR_DUMMY_CYCLELEN_V)<<(SPI_USR_DUMMY_CYCLELEN_S))
#define SPI_USR_DUMMY_CYCLELEN_V  0xFF
#define SPI_USR_DUMMY_CYCLELEN_S  0

#define SPI_USER2_REG(i)          (REG_SPI_BASE(i) + 0x18)
/* SPI_USR_COMMAND_BITLEN:R/W；位位置：[31:28]；默认值：4'd7；*/
/*description:命令阶段的长度（以位为单位）。寄存器值应为（bit_num-1）。可在形态状态下配置。。*/
#define SPI_USR_COMMAND_BITLEN    0x0000000F
#define SPI_USR_COMMAND_BITLEN_M  ((SPI_USR_COMMAND_BITLEN_V)<<(SPI_USR_COMMAND_BITLEN_S))
#define SPI_USR_COMMAND_BITLEN_V  0xF
#define SPI_USR_COMMAND_BITLEN_S  28
/* SPI_MST_REMPTY_ERR_END_EN:R/W；位位置：[27]；默认值：1’b1；*/
/*描述：1：当SPI TX AFIFO读取空错误在GP-SPI主FD/HD模式下有效时，SPI传输结束。0:当SPI TX AFIFO读取空错误在GP-SPI主FD/HD模式下有效时，SPI传输未结束。。*/
#define SPI_MST_REMPTY_ERR_END_EN    (BIT(27))
#define SPI_MST_REMPTY_ERR_END_EN_M  (BIT(27))
#define SPI_MST_REMPTY_ERR_END_EN_V  0x1
#define SPI_MST_REMPTY_ERR_END_EN_S  27
/* SPI_USR_COMMAND_VALUE:R/W；比特位置：[15:0]；默认值：16'b0；*/
/*description:命令的值。可在形态状态下配置。。*/
#define SPI_USR_COMMAND_VALUE    0x0000FFFF
#define SPI_USR_COMMAND_VALUE_M  ((SPI_USR_COMMAND_VALUE_V)<<(SPI_USR_COMMAND_VALUE_S))
#define SPI_USR_COMMAND_VALUE_V  0xFFFF
#define SPI_USR_COMMAND_VALUE_S  0

#define SPI_MS_DLEN_REG(i)          (REG_SPI_BASE(i) + 0x1C)
/* SPI_MS_DATA_BITLEN:R/W；比特位置：[17:00]；默认值：18'b0；*/
/*描述：这些位的值是在主模式DMA控制传输或CPU控制传输中配置的SPI传输数据位长度。该值也是从属模式DMA RX控制传输中配置的比特长度。寄存器值应为（bit_num-1）。可在形态状态下配置。。*/
#define SPI_MS_DATA_BITLEN    0x0003FFFF
#define SPI_MS_DATA_BITLEN_M  ((SPI_MS_DATA_BITLEN_V)<<(SPI_MS_DATA_BITLEN_S))
#define SPI_MS_DATA_BITLEN_V  0x3FFFF
#define SPI_MS_DATA_BITLEN_S  0

#define SPI_MISC_REG(i)          (REG_SPI_BASE(i) + 0x20)
/* SPI_QUAD_DIN_PIN_SWAP:R/W；位位置：[31]；默认值：1’b0；*/
/*描述：1:spi四输入交换启用0:spi四输出交换禁用。可在形态状态下配置。。*/
#define SPI_QUAD_DIN_PIN_SWAP    (BIT(31))
#define SPI_QUAD_DIN_PIN_SWAP_M  (BIT(31))
#define SPI_QUAD_DIN_PIN_SWAP_V  0x1
#define SPI_QUAD_DIN_PIN_SWAP_S  31
/* SPI_CS_KEEP_ACTIVE:R/W；位位置：[30]；默认值：1’b0；*/
/*描述：设置位时，spi cs线保持低电平。可在形态状态下配置。。*/
#define SPI_CS_KEEP_ACTIVE    (BIT(30))
#define SPI_CS_KEEP_ACTIVE_M  (BIT(30))
#define SPI_CS_KEEP_ACTIVE_V  0x1
#define SPI_CS_KEEP_ACTIVE_S  30
/* SPI_CK_inidle_EDGE：R/W；位位置：[29]；默认值：1’b0；*/
/*描述：1：空闲时spi-clk线为高0：空闲时spi-clk线路为低。可在形态状态下配置。。*/
#define SPI_CK_IDLE_EDGE    (BIT(29))
#define SPI_CK_IDLE_EDGE_M  (BIT(29))
#define SPI_CK_IDLE_EDGE_V  0x1
#define SPI_CK_IDLE_EDGE_S  29
/* SPI_SLAVE_CS_POL:R/W；位位置：[23]；默认值：1’b0；*/
/*描述：spi从输入cs极性选择。1： 发票0：未更改。可在CONF状态下配置。。*/
#define SPI_SLAVE_CS_POL    (BIT(23))
#define SPI_SLAVE_CS_POL_M  (BIT(23))
#define SPI_SLAVE_CS_POL_V  0x1
#define SPI_SLAVE_CS_POL_S  23
/* SPI_MASTER_CS_POL:R/W；比特位置：[12:7]；默认值：6'b0；*/
/*描述：在主模式中，位是spi-cs线的极性，值等于spi_cs^spi_master_cs_pol。可在形态状态下配置。。*/
#define SPI_MASTER_CS_POL    0x0000003F
#define SPI_MASTER_CS_POL_M  ((SPI_MASTER_CS_POL_V)<<(SPI_MASTER_CS_POL_S))
#define SPI_MASTER_CS_POL_V  0x3F
#define SPI_MASTER_CS_POL_S  7
/* SPI_CK_DIS:R/W；位位置：[6]；默认值：1’b0；*/
/*描述：1:spi-clk-out禁用，0:spi-clk-out启用。可在形态状态下配置。。*/
#define SPI_CK_DIS    (BIT(6))
#define SPI_CK_DIS_M  (BIT(6))
#define SPI_CK_DIS_V  0x1
#define SPI_CK_DIS_S  6
/* SPI_CS5_DIS:R/W；位位置：[5]；默认值：1’b1；*/
/*描述：SPI CS$n引脚启用，1：禁用CS$n，0：SPI_CS$n信号来自/到CS$n。可在形态状态下配置。。*/
#define SPI_CS5_DIS    (BIT(5))
#define SPI_CS5_DIS_M  (BIT(5))
#define SPI_CS5_DIS_V  0x1
#define SPI_CS5_DIS_S  5
/* SPI_CS4_DIS:R/W；位位置：[4]；默认值：1’b1；*/
/*描述：SPI CS$n引脚启用，1：禁用CS$n，0：SPI_CS$n信号来自/到CS$n。可在形态状态下配置。。*/
#define SPI_CS4_DIS    (BIT(4))
#define SPI_CS4_DIS_M  (BIT(4))
#define SPI_CS4_DIS_V  0x1
#define SPI_CS4_DIS_S  4
/* SPI_CS3_DIS：R/W；位位置：[3]；默认值：1’b1；*/
/*描述：SPI CS$n引脚启用，1：禁用CS$n，0：SPI_CS$n信号来自/到CS$n。可在形态状态下配置。。*/
#define SPI_CS3_DIS    (BIT(3))
#define SPI_CS3_DIS_M  (BIT(3))
#define SPI_CS3_DIS_V  0x1
#define SPI_CS3_DIS_S  3
/* SPI_CS2_DIS:R/W；位位置：[2]；默认值：1’b1；*/
/*描述：SPI CS$n引脚启用，1：禁用CS$n，0：SPI_CS$n信号来自/到CS$n。可在形态状态下配置。。*/
#define SPI_CS2_DIS    (BIT(2))
#define SPI_CS2_DIS_M  (BIT(2))
#define SPI_CS2_DIS_V  0x1
#define SPI_CS2_DIS_S  2
/* SPI_CS1_DIS:R/W；位位置：[1]；默认值：1’b1；*/
/*描述：SPI CS$n引脚启用，1：禁用CS$n，0：SPI_CS$n信号来自/到CS$n。可在形态状态下配置。。*/
#define SPI_CS1_DIS    (BIT(1))
#define SPI_CS1_DIS_M  (BIT(1))
#define SPI_CS1_DIS_V  0x1
#define SPI_CS1_DIS_S  1
/* SPI_CS0_DIS:R/W；位位置：[0]；默认值：1’b0；*/
/*描述：SPI CS$n引脚启用，1：禁用CS$n，0：SPI_CS$n信号来自/到CS$n。可在形态状态下配置。。*/
#define SPI_CS0_DIS    (BIT(0))
#define SPI_CS0_DIS_M  (BIT(0))
#define SPI_CS0_DIS_V  0x1
#define SPI_CS0_DIS_S  0

#define SPI_DIN_MODE_REG(i)          (REG_SPI_BASE(i) + 0x24)
/* SPI_TIMING_HCLK_ACTIVE:R/W；位位置：[16]；默认值：1’b0；*/
/*描述：1：启用SPI输入定时模块中的hclk。0：禁用。可在形态状态下配置。。*/
#define SPI_TIMING_HCLK_ACTIVE    (BIT(16))
#define SPI_TIMING_HCLK_ACTIVE_M  (BIT(16))
#define SPI_TIMING_HCLK_ACTIVE_V  0x1
#define SPI_TIMING_HCLK_ACTIVE_S  16
/* SPI_DIN3_MODE：R/W；位位置：[7:6]；默认值：2’b0；*/
/*描述：输入信号被SPI模块时钟周期延迟，0：输入无延迟，1：带clk_apb的偏旁输入，2：带clk _apb的负边输入，3：带SPI_clk的输入。可在形态状态下配置。。*/
#define SPI_DIN3_MODE    0x00000003
#define SPI_DIN3_MODE_M  ((SPI_DIN3_MODE_V)<<(SPI_DIN3_MODE_S))
#define SPI_DIN3_MODE_V  0x3
#define SPI_DIN3_MODE_S  6
/* SPI_din_模式：R/W；比特位置：[5:4]；默认值：2’b0；*/
/*描述：输入信号被SPI模块时钟周期延迟，0：输入无延迟，1：带clk_apb的偏旁输入，2：带clk _apb的负边输入，3：带SPI_clk的输入。可在形态状态下配置。。*/
#define SPI_DIN2_MODE    0x00000003
#define SPI_DIN2_MODE_M  ((SPI_DIN2_MODE_V)<<(SPI_DIN2_MODE_S))
#define SPI_DIN2_MODE_V  0x3
#define SPI_DIN2_MODE_S  4
/* SPI_DIN1_MODE：R/W；位位置：[3:2]；默认值：2’b0；*/
/*描述：输入信号被SPI模块时钟周期延迟，0：输入无延迟，1：带clk_apb的偏旁输入，2：带clk _apb的负边输入，3：带SPI_clk的输入。可在形态状态下配置。。*/
#define SPI_DIN1_MODE    0x00000003
#define SPI_DIN1_MODE_M  ((SPI_DIN1_MODE_V)<<(SPI_DIN1_MODE_S))
#define SPI_DIN1_MODE_V  0x3
#define SPI_DIN1_MODE_S  2
/* SPI_DIN0_MODE：R/W；位位置：[1:0]；默认值：2’b0；*/
/*描述：输入信号被SPI模块时钟周期延迟，0：输入无延迟，1：带clk_apb的偏旁输入，2：带clk _apb的负边输入，3：带SPI_clk的输入。可在形态状态下配置。。*/
#define SPI_DIN0_MODE    0x00000003
#define SPI_DIN0_MODE_M  ((SPI_DIN0_MODE_V)<<(SPI_DIN0_MODE_S))
#define SPI_DIN0_MODE_V  0x3
#define SPI_DIN0_MODE_S  0

#define SPI_DIN_NUM_REG(i)          (REG_SPI_BASE(i) + 0x28)
/* SPI_DIN3_NUM:R/W；位位置：[7:6]；默认值：2’b0；*/
/*描述：输入信号延迟SPI模块时钟周期，0：延迟1个周期，1：延迟2个周期，…可配置为CONF状态。。*/
#define SPI_DIN3_NUM    0x00000003
#define SPI_DIN3_NUM_M  ((SPI_DIN3_NUM_V)<<(SPI_DIN3_NUM_S))
#define SPI_DIN3_NUM_V  0x3
#define SPI_DIN3_NUM_S  6
/* SPI_din_NUM:R/W；比特位置：[5:4]；默认值：2’b0；*/
/*描述：输入信号延迟SPI模块时钟周期，0：延迟1个周期，1：延迟2个周期，…可配置为CONF状态。。*/
#define SPI_DIN2_NUM    0x00000003
#define SPI_DIN2_NUM_M  ((SPI_DIN2_NUM_V)<<(SPI_DIN2_NUM_S))
#define SPI_DIN2_NUM_V  0x3
#define SPI_DIN2_NUM_S  4
/* SPI_DIN1_NUM：随机；位位置：[3:2]；默认值：2’b0；*/
/*描述：输入信号延迟SPI模块时钟周期，0：延迟1个周期，1：延迟2个周期，…可配置为CONF状态。。*/
#define SPI_DIN1_NUM    0x00000003
#define SPI_DIN1_NUM_M  ((SPI_DIN1_NUM_V)<<(SPI_DIN1_NUM_S))
#define SPI_DIN1_NUM_V  0x3
#define SPI_DIN1_NUM_S  2
/* SPI_DIN0_NUM:R/W；位位置：[1:0]；默认值：2’b0；*/
/*描述：输入信号延迟SPI模块时钟周期，0：延迟1个周期，1：延迟2个周期，…可配置为CONF状态。。*/
#define SPI_DIN0_NUM    0x00000003
#define SPI_DIN0_NUM_M  ((SPI_DIN0_NUM_V)<<(SPI_DIN0_NUM_S))
#define SPI_DIN0_NUM_V  0x3
#define SPI_DIN0_NUM_S  0

#define SPI_DOUT_MODE_REG(i)          (REG_SPI_BASE(i) + 0x2C)
/* SPI_DOUT3_MODE：R/W；位位置：[3]；默认值：1’b0；*/
/*描述：输出信号$n被SPI模块时钟延迟，0：无延迟输出，1：负边缘SPI模块时钟周期的输出延迟。可在形态状态下配置。。*/
#define SPI_DOUT3_MODE    (BIT(3))
#define SPI_DOUT3_MODE_M  (BIT(3))
#define SPI_DOUT3_MODE_V  0x1
#define SPI_DOUT3_MODE_S  3
/* SPI_DOUT2_MODE：R/W；位位置：[2]；默认值：1’b0；*/
/*描述：输出信号$n被SPI模块时钟延迟，0：无延迟输出，1：负边缘SPI模块时钟周期的输出延迟。可在形态状态下配置。。*/
#define SPI_DOUT2_MODE    (BIT(2))
#define SPI_DOUT2_MODE_M  (BIT(2))
#define SPI_DOUT2_MODE_V  0x1
#define SPI_DOUT2_MODE_S  2
/* SPI_DOUT1_MODE：R/W；位位置：[1]；默认值：1’b0；*/
/*描述：输出信号$n被SPI模块时钟延迟，0：无延迟输出，1：负边缘SPI模块时钟周期的输出延迟。可在形态状态下配置。。*/
#define SPI_DOUT1_MODE    (BIT(1))
#define SPI_DOUT1_MODE_M  (BIT(1))
#define SPI_DOUT1_MODE_V  0x1
#define SPI_DOUT1_MODE_S  1
/* SPI_DOUT0_MODE：R/W；位位置：[0]；默认值：1’b0；*/
/*描述：输出信号$n被SPI模块时钟延迟，0：无延迟输出，1：负边缘SPI模块时钟周期的输出延迟。可在形态状态下配置。。*/
#define SPI_DOUT0_MODE    (BIT(0))
#define SPI_DOUT0_MODE_M  (BIT(0))
#define SPI_DOUT0_MODE_V  0x1
#define SPI_DOUT0_MODE_S  0

#define SPI_DMA_CONF_REG(i)          (REG_SPI_BASE(i) + 0x30)
/* SPI_DMA_AFIFO_RST:WT；位位置：[31]；默认值：1’b0；*/
/*description:设置此位以重置DMA TX AFIFO，用于在SPI slaveDMA控制模式传输中发送数据。。*/
#define SPI_DMA_AFIFO_RST    (BIT(31))
#define SPI_DMA_AFIFO_RST_M  (BIT(31))
#define SPI_DMA_AFIFO_RST_V  0x1
#define SPI_DMA_AFIFO_RST_S  31
/* SPI_BUF_AFIFO_RST:WT；位位置：[30]；默认值：1’b0；*/
/*description:设置此位以重置BUF TX AFIFO，用于在SPI从CPU控制模式传输和主模式传输中发送数据。。*/
#define SPI_BUF_AFIFO_RST    (BIT(30))
#define SPI_BUF_AFIFO_RST_M  (BIT(30))
#define SPI_BUF_AFIFO_RST_V  0x1
#define SPI_BUF_AFIFO_RST_S  30
/* SPI_RX_AFIFO_RST:WT；位位置：[29]；默认值：1’b0；*/
/*description:设置此位以重置RX AFIFO，用于在SPI主从模式传输中接收数据。。*/
#define SPI_RX_AFIFO_RST    (BIT(29))
#define SPI_RX_AFIFO_RST_M  (BIT(29))
#define SPI_RX_AFIFO_RST_V  0x1
#define SPI_RX_AFIFO_RST_S  29
/* SPI_DMA_TX_ENA:R/W；位位置：[28]；默认值：1’b0；*/
/*description:设置此位以启用SPI DMA控制的发送数据模式。。*/
#define SPI_DMA_TX_ENA    (BIT(28))
#define SPI_DMA_TX_ENA_M  (BIT(28))
#define SPI_DMA_TX_ENA_V  0x1
#define SPI_DMA_TX_ENA_S  28
/* SPI_DMA_RX_ENA:R/W；位位置：[27]；默认值：1'd0；*/
/*description:设置此位以启用SPI DMA控制的接收数据模式。。*/
#define SPI_DMA_RX_ENA    (BIT(27))
#define SPI_DMA_RX_ENA_M  (BIT(27))
#define SPI_DMA_RX_ENA_V  0x1
#define SPI_DMA_RX_ENA_S  27
/* SPI_RX_EOF_EN:R/W；位位置：[21]；默认值：1’b0；*/
/*描述：1：当dma推送数据字节数等于spi-dma转换中的spi_slv/mst_dma_rd_bytelen[19:0]的值时，设置spi_dma_inlink_eof。0:spi_dma_inlink_eof由非seg trans中的spi_trans_done或seg trans中的spi_dma_seg_trans_done设置。。*/
#define SPI_RX_EOF_EN    (BIT(21))
#define SPI_RX_EOF_EN_M  (BIT(21))
#define SPI_RX_EOF_EN_V  0x1
#define SPI_RX_EOF_EN_S  21
/* SPI_SLV_TX_SEG_TRANS_CLR_EN:R/W；位位置：[20]；默认值：1’b0；*/
/*描述：1:spi_dma_outfifo_empty_vld由spi从命令6清除。0:spi_dma_outfifo-empty-vld由spi_trans_done清除。。*/
#define SPI_SLV_TX_SEG_TRANS_CLR_EN    (BIT(20))
#define SPI_SLV_TX_SEG_TRANS_CLR_EN_M  (BIT(20))
#define SPI_SLV_TX_SEG_TRANS_CLR_EN_V  0x1
#define SPI_SLV_TX_SEG_TRANS_CLR_EN_S  20
/* SPI_SLV_RX_SEG_TRANS_CLR_EN:R/W；位位置：[19]；默认值：1’b0；*/
/*描述：1:spi_dma_infifo_full_vld由spi-slave cmd 5清除。0:spi_dma.infifo_ffull_vld由spi_trans_done清除。。*/
#define SPI_SLV_RX_SEG_TRANS_CLR_EN    (BIT(19))
#define SPI_SLV_RX_SEG_TRANS_CLR_EN_M  (BIT(19))
#define SPI_SLV_RX_SEG_TRANS_CLR_EN_V  0x1
#define SPI_SLV_RX_SEG_TRANS_CLR_EN_S  19
/* SPI_DMA_SLV_SEG_TRANS_EN:R/W；位位置：[18]；默认值：1’b0；*/
/*description:在spi-dma半从模式下启用dma段传输。1： 启用。0:禁用。。*/
#define SPI_DMA_SLV_SEG_TRANS_EN    (BIT(18))
#define SPI_DMA_SLV_SEG_TRANS_EN_M  (BIT(18))
#define SPI_DMA_SLV_SEG_TRANS_EN_V  0x1
#define SPI_DMA_SLV_SEG_TRANS_EN_S  18
/* SPI_DMA_infifofull:RO；位位置：[1]；默认值：1’b1；*/
/*description:记录DMA RX FIFO的状态。1： DMA RX FIFO未准备好接收数据。0:DMA RX FIFO已准备好接收数据。*/
#define SPI_DMA_INFIFO_FULL  (BIT(1))
#define SPI_DMA_INFIFO_FULL_M  (BIT(1))
#define SPI_DMA_INFIFO_FULL_V  0x1
#define SPI_DMA_INFIFO_FULL_S  1
/* SPI_DMA_OUTFIFO空：RO；位位置：[0]；默认值：1’b1；*/
/*description:记录DMA TX FIFO的状态。1： DMA TX FIFO未准备好发送数据。0:DMA TX FIFO已准备好发送数据。*/
#define SPI_DMA_OUTFIFO_EMPTY  (BIT(0))
#define SPI_DMA_OUTFIFO_EMPTY_M  (BIT(0))
#define SPI_DMA_OUTFIFO_EMPTY_V  0x1
#define SPI_DMA_OUTFIFO_EMPTY_S  0

#define SPI_DMA_INT_ENA_REG(i)          (REG_SPI_BASE(i) + 0x34)
/* SPI_APP1_INT_ENA:R/W；位位置：[20]；默认值：1’b0；*/
/*description:SPI_APP1_INT中断的启用位。。*/
#define SPI_APP1_INT_ENA    (BIT(20))
#define SPI_APP1_INT_ENA_M  (BIT(20))
#define SPI_APP1_INT_ENA_V  0x1
#define SPI_APP1_INT_ENA_S  20
/* SPI_APP2_INT_ENA:R/W；位位置：[19]；默认值：1’b0；*/
/*description:SPI_APP2_INT中断的启用位。。*/
#define SPI_APP2_INT_ENA    (BIT(19))
#define SPI_APP2_INT_ENA_M  (BIT(19))
#define SPI_APP2_INT_ENA_V  0x1
#define SPI_APP2_INT_ENA_S  19
/* SPI_MST_TX_AFIFO_REMPTY_ERR_INT_ENA:R/W；位位置：[18]；默认值：1’b0；*/
/*description:SPI_MST_TX_AFIFO_REMPTY_ERR_INT中断的启用位。。*/
#define SPI_MST_TX_AFIFO_REMPTY_ERR_INT_ENA    (BIT(18))
#define SPI_MST_TX_AFIFO_REMPTY_ERR_INT_ENA_M  (BIT(18))
#define SPI_MST_TX_AFIFO_REMPTY_ERR_INT_ENA_V  0x1
#define SPI_MST_TX_AFIFO_REMPTY_ERR_INT_ENA_S  18
/* SPI_MST_RX_AFIFO_wull_ERR_INT_ENA:R/W；位位置：[17]；默认值：1’b0；*/
/*description:SPI_MST_RX_AFIFO_WFULL_ERROR_INT中断的启用位。。*/
#define SPI_MST_RX_AFIFO_WFULL_ERR_INT_ENA    (BIT(17))
#define SPI_MST_RX_AFIFO_WFULL_ERR_INT_ENA_M  (BIT(17))
#define SPI_MST_RX_AFIFO_WFULL_ERR_INT_ENA_V  0x1
#define SPI_MST_RX_AFIFO_WFULL_ERR_INT_ENA_S  17
/* SPI_SLV_CMD_ERR_INT_ENA：R/W；位位置：[16]；默认值：1’b0；*/
/*description:SPI_SLV_CMD_ERR_INT中断的启用位。。*/
#define SPI_SLV_CMD_ERR_INT_ENA    (BIT(16))
#define SPI_SLV_CMD_ERR_INT_ENA_M  (BIT(16))
#define SPI_SLV_CMD_ERR_INT_ENA_V  0x1
#define SPI_SLV_CMD_ERR_INT_ENA_S  16
/* SPI_SLV_BUF_ADDR_ERR_INT_ENA:R/W；位位置：[15]；默认值：1’b0；*/
/*description:SPI_SLV_BUF_ADDR_ERR_INT中断的启用位。。*/
#define SPI_SLV_BUF_ADDR_ERR_INT_ENA    (BIT(15))
#define SPI_SLV_BUF_ADDR_ERR_INT_ENA_M  (BIT(15))
#define SPI_SLV_BUF_ADDR_ERR_INT_ENA_V  0x1
#define SPI_SLV_BUF_ADDR_ERR_INT_ENA_S  15
/* SPI_SEG_MAGIC_ERR_INT_ENA：R/W；位位置：[14]；默认值：1’b0；*/
/*description:SPI_SEG_MAGIC_ERR_INT中断的启用位。。*/
#define SPI_SEG_MAGIC_ERR_INT_ENA    (BIT(14))
#define SPI_SEG_MAGIC_ERR_INT_ENA_M  (BIT(14))
#define SPI_SEG_MAGIC_ERR_INT_ENA_V  0x1
#define SPI_SEG_MAGIC_ERR_INT_ENA_S  14
/* SPI_DMA_SEG_TRANS_DONE_INT_ENA:R/W；位位置：[13]；默认值：1’b0；*/
/*description:SPI_DMA_SEG_TRANS_DONE_INT中断的启用位。。*/
#define SPI_DMA_SEG_TRANS_DONE_INT_ENA    (BIT(13))
#define SPI_DMA_SEG_TRANS_DONE_INT_ENA_M  (BIT(13))
#define SPI_DMA_SEG_TRANS_DONE_INT_ENA_V  0x1
#define SPI_DMA_SEG_TRANS_DONE_INT_ENA_S  13
/* SPI_TRANS_DONE_INT_ENA：R/W；位位置：[12]；默认值：1’b0；*/
/*description:SPI_TRANS_DONE_INT中断的启用位。。*/
#define SPI_TRANS_DONE_INT_ENA    (BIT(12))
#define SPI_TRANS_DONE_INT_ENA_M  (BIT(12))
#define SPI_TRANS_DONE_INT_ENA_V  0x1
#define SPI_TRANS_DONE_INT_ENA_S  12
/* SPI_SLV_WR_BUF_DONE_INT_ENA:R/W；位位置：[11]；默认值：1’b0；*/
/*description:SPI_SLV_WR_BUF_DON_INT中断的启用位。。*/
#define SPI_SLV_WR_BUF_DONE_INT_ENA    (BIT(11))
#define SPI_SLV_WR_BUF_DONE_INT_ENA_M  (BIT(11))
#define SPI_SLV_WR_BUF_DONE_INT_ENA_V  0x1
#define SPI_SLV_WR_BUF_DONE_INT_ENA_S  11
/* SPI_SLV_RD_BUF_DONE_INT_ENA:R/W；位位置：[10]；默认值：1’b0；*/
/*description:SPI_SLV_RD_BUF_DON_INT中断的启用位。。*/
#define SPI_SLV_RD_BUF_DONE_INT_ENA    (BIT(10))
#define SPI_SLV_RD_BUF_DONE_INT_ENA_M  (BIT(10))
#define SPI_SLV_RD_BUF_DONE_INT_ENA_V  0x1
#define SPI_SLV_RD_BUF_DONE_INT_ENA_S  10
/* SPI_SLV_WR_DMA_DONE_INT_ENA：R/W；位位置：[9]；默认值：1’b0；*/
/*description:SPI_SLV_WR_DMA_DONE_INT中断的启用位。。*/
#define SPI_SLV_WR_DMA_DONE_INT_ENA    (BIT(9))
#define SPI_SLV_WR_DMA_DONE_INT_ENA_M  (BIT(9))
#define SPI_SLV_WR_DMA_DONE_INT_ENA_V  0x1
#define SPI_SLV_WR_DMA_DONE_INT_ENA_S  9
/* SPI_SLV_RD_DMA_DONE_INT_ENA:R/W；位位置：[8]；默认值：1’b0；*/
/*description:SPI_SLV_RD_DMA_DONE_INT中断的启用位。。*/
#define SPI_SLV_RD_DMA_DONE_INT_ENA    (BIT(8))
#define SPI_SLV_RD_DMA_DONE_INT_ENA_M  (BIT(8))
#define SPI_SLV_RD_DMA_DONE_INT_ENA_V  0x1
#define SPI_SLV_RD_DMA_DONE_INT_ENA_S  8
/* SPI_SLV_CMDA_INT_ENA:R/W；位位置：[7]；默认值：1’b0；*/
/*description:SPI从属CMDA中断的启用位。。*/
#define SPI_SLV_CMDA_INT_ENA    (BIT(7))
#define SPI_SLV_CMDA_INT_ENA_M  (BIT(7))
#define SPI_SLV_CMDA_INT_ENA_V  0x1
#define SPI_SLV_CMDA_INT_ENA_S  7
/* SPI_SLV_CMD9_INT_ENA：R/W；位位置：[6]；默认值：1’b0；*/
/*description:SPI从属CMD9中断的启用位。。*/
#define SPI_SLV_CMD9_INT_ENA    (BIT(6))
#define SPI_SLV_CMD9_INT_ENA_M  (BIT(6))
#define SPI_SLV_CMD9_INT_ENA_V  0x1
#define SPI_SLV_CMD9_INT_ENA_S  6
/* SPI_SLV_CMD8_INT_ENA：R/W；位位置：[5]；默认值：1’b0；*/
/*description:SPI从属CMD8中断的启用位。。*/
#define SPI_SLV_CMD8_INT_ENA    (BIT(5))
#define SPI_SLV_CMD8_INT_ENA_M  (BIT(5))
#define SPI_SLV_CMD8_INT_ENA_V  0x1
#define SPI_SLV_CMD8_INT_ENA_S  5
/* SPI_SLV_CMD7_INT_ENA:R/W；位位置：[4]；默认值：1’b0；*/
/*description:SPI从属CMD7中断的启用位。。*/
#define SPI_SLV_CMD7_INT_ENA    (BIT(4))
#define SPI_SLV_CMD7_INT_ENA_M  (BIT(4))
#define SPI_SLV_CMD7_INT_ENA_V  0x1
#define SPI_SLV_CMD7_INT_ENA_S  4
/* SPI_SLV_EN_QPI_INT_ENA:R/W；位位置：[3]；默认值：1’b0；*/
/*description:SPI从属En_QPI中断的启用位。。*/
#define SPI_SLV_EN_QPI_INT_ENA    (BIT(3))
#define SPI_SLV_EN_QPI_INT_ENA_M  (BIT(3))
#define SPI_SLV_EN_QPI_INT_ENA_V  0x1
#define SPI_SLV_EN_QPI_INT_ENA_S  3
/* SPI_SLV_EX_QPI_INT_ENA:R/W；位位置：[2]；默认值：1’b0；*/
/*description:SPI从设备Ex_QPI中断的启用位。。*/
#define SPI_SLV_EX_QPI_INT_ENA    (BIT(2))
#define SPI_SLV_EX_QPI_INT_ENA_M  (BIT(2))
#define SPI_SLV_EX_QPI_INT_ENA_V  0x1
#define SPI_SLV_EX_QPI_INT_ENA_S  2
/* SPI_DMA_OUTFIFO_EMPTY_ERR_INT_ENA:R/W；位位置：[1]；默认值：1’b0；*/
/*description:SPI_DMA_OUTFIFO_EMPTY_ERR_INT中断的启用位。。*/
#define SPI_DMA_OUTFIFO_EMPTY_ERR_INT_ENA    (BIT(1))
#define SPI_DMA_OUTFIFO_EMPTY_ERR_INT_ENA_M  (BIT(1))
#define SPI_DMA_OUTFIFO_EMPTY_ERR_INT_ENA_V  0x1
#define SPI_DMA_OUTFIFO_EMPTY_ERR_INT_ENA_S  1
/* SPI_DMA_INFIFO_FULL_ERR_INT_ENA:R/W；位位置：[0]；默认值：1’b0；*/
/*description:SPI_DMA_INFIFO_FULL_ERROR_INT中断的启用位。。*/
#define SPI_DMA_INFIFO_FULL_ERR_INT_ENA    (BIT(0))
#define SPI_DMA_INFIFO_FULL_ERR_INT_ENA_M  (BIT(0))
#define SPI_DMA_INFIFO_FULL_ERR_INT_ENA_V  0x1
#define SPI_DMA_INFIFO_FULL_ERR_INT_ENA_S  0

#define SPI_DMA_INT_CLR_REG(i)          (REG_SPI_BASE(i) + 0x38)
/* SPI_APP1_INT_CLR:WT；位位置：[20]；默认值：1’b0；*/
/*description:SPI_APP1_INT中断的清除位。。*/
#define SPI_APP1_INT_CLR    (BIT(20))
#define SPI_APP1_INT_CLR_M  (BIT(20))
#define SPI_APP1_INT_CLR_V  0x1
#define SPI_APP1_INT_CLR_S  20
/* SPI_APP2_INT_CLR:WT；位位置：[19]；默认值：1’b0；*/
/*description:SPI_APP2_INT中断的清除位。。*/
#define SPI_APP2_INT_CLR    (BIT(19))
#define SPI_APP2_INT_CLR_M  (BIT(19))
#define SPI_APP2_INT_CLR_V  0x1
#define SPI_APP2_INT_CLR_S  19
/* SPI_MST_TX_AFIFO_REMPTY_ERR_INT_CLR:WT；位位置：[18]；默认值：1’b0；*/
/*description:SPI_MST_TX_AFIFO_REMPTY_ERR_INT中断的清除位。。*/
#define SPI_MST_TX_AFIFO_REMPTY_ERR_INT_CLR    (BIT(18))
#define SPI_MST_TX_AFIFO_REMPTY_ERR_INT_CLR_M  (BIT(18))
#define SPI_MST_TX_AFIFO_REMPTY_ERR_INT_CLR_V  0x1
#define SPI_MST_TX_AFIFO_REMPTY_ERR_INT_CLR_S  18
/* SPI_MST_RX_AFIFO_wull_ERR_INT_CLR:WT；位位置：[17]；默认值：1’b0；*/
/*description:SPI_MST_RX_AFIFO_WFULL_ERROR_INT中断的清除位。。*/
#define SPI_MST_RX_AFIFO_WFULL_ERR_INT_CLR    (BIT(17))
#define SPI_MST_RX_AFIFO_WFULL_ERR_INT_CLR_M  (BIT(17))
#define SPI_MST_RX_AFIFO_WFULL_ERR_INT_CLR_V  0x1
#define SPI_MST_RX_AFIFO_WFULL_ERR_INT_CLR_S  17
/* SPI_SLV_CMD_ERR_INT_CLR:WT；位位置：[16]；默认值：1’b0；*/
/*description:SPI_SLV_CMD_ERR_INT中断的清除位。。*/
#define SPI_SLV_CMD_ERR_INT_CLR    (BIT(16))
#define SPI_SLV_CMD_ERR_INT_CLR_M  (BIT(16))
#define SPI_SLV_CMD_ERR_INT_CLR_V  0x1
#define SPI_SLV_CMD_ERR_INT_CLR_S  16
/* SPI_SLV_BUF_ADDR_ERR_INT_CLR:WT；位位置：[15]；默认值：1’b0；*/
/*description:SPI_SLV_BUF_ADDR_ERR_INT中断的清除位。。*/
#define SPI_SLV_BUF_ADDR_ERR_INT_CLR    (BIT(15))
#define SPI_SLV_BUF_ADDR_ERR_INT_CLR_M  (BIT(15))
#define SPI_SLV_BUF_ADDR_ERR_INT_CLR_V  0x1
#define SPI_SLV_BUF_ADDR_ERR_INT_CLR_S  15
/* SPI_SEG_MAGIC_ERR_INT_CLR:WT；位位置：[14]；默认值：1’b0；*/
/*description:SPI_SEG_MAGIC_ERR_INT中断的清除位。。*/
#define SPI_SEG_MAGIC_ERR_INT_CLR    (BIT(14))
#define SPI_SEG_MAGIC_ERR_INT_CLR_M  (BIT(14))
#define SPI_SEG_MAGIC_ERR_INT_CLR_V  0x1
#define SPI_SEG_MAGIC_ERR_INT_CLR_S  14
/* SPI_DMA_SEG_TRANS_DONE_INT_CLR:WT；位位置：[13]；默认值：1’b0；*/
/*description:SPI_DMA_SEG_TRANS_DONE_INT中断的清除位。。*/
#define SPI_DMA_SEG_TRANS_DONE_INT_CLR    (BIT(13))
#define SPI_DMA_SEG_TRANS_DONE_INT_CLR_M  (BIT(13))
#define SPI_DMA_SEG_TRANS_DONE_INT_CLR_V  0x1
#define SPI_DMA_SEG_TRANS_DONE_INT_CLR_S  13
/* SPI_TRANS_DONE_INT_CLR:WT；位位置：[12]；默认值：1’b0；*/
/*description:SPI_TRANS_DONE_INT中断的清除位。。*/
#define SPI_TRANS_DONE_INT_CLR    (BIT(12))
#define SPI_TRANS_DONE_INT_CLR_M  (BIT(12))
#define SPI_TRANS_DONE_INT_CLR_V  0x1
#define SPI_TRANS_DONE_INT_CLR_S  12
/* SPI_SLV_WR_BUF_DONE_INT_CLR:WT；位位置：[11]；默认值：1’b0；*/
/*description:SPI_SLV_WR_BUF_DON_INT中断的清除位。。*/
#define SPI_SLV_WR_BUF_DONE_INT_CLR    (BIT(11))
#define SPI_SLV_WR_BUF_DONE_INT_CLR_M  (BIT(11))
#define SPI_SLV_WR_BUF_DONE_INT_CLR_V  0x1
#define SPI_SLV_WR_BUF_DONE_INT_CLR_S  11
/* SPI_SLV_RD_BUF_DONE_INT_CLR:WT；位位置：[10]；默认值：1’b0；*/
/*description:SPI_SLV_RD_BUF_DON_INT中断的清除位。。*/
#define SPI_SLV_RD_BUF_DONE_INT_CLR    (BIT(10))
#define SPI_SLV_RD_BUF_DONE_INT_CLR_M  (BIT(10))
#define SPI_SLV_RD_BUF_DONE_INT_CLR_V  0x1
#define SPI_SLV_RD_BUF_DONE_INT_CLR_S  10
/* SPI_SLV_WR_DMA_DONE_INT_CLR:WT；位位置：[9]；默认值：1’b0；*/
/*description:SPI_SLV_WR_DMA_DONE_INT中断的清除位。。*/
#define SPI_SLV_WR_DMA_DONE_INT_CLR    (BIT(9))
#define SPI_SLV_WR_DMA_DONE_INT_CLR_M  (BIT(9))
#define SPI_SLV_WR_DMA_DONE_INT_CLR_V  0x1
#define SPI_SLV_WR_DMA_DONE_INT_CLR_S  9
/* SPI_SLV_RD_DMA_DONE_INT_CLR:WT；位位置：[8]；默认值：1’b0；*/
/*description:SPI_SLV_RD_DMA_DONE_INT中断的清除位。。*/
#define SPI_SLV_RD_DMA_DONE_INT_CLR    (BIT(8))
#define SPI_SLV_RD_DMA_DONE_INT_CLR_M  (BIT(8))
#define SPI_SLV_RD_DMA_DONE_INT_CLR_V  0x1
#define SPI_SLV_RD_DMA_DONE_INT_CLR_S  8
/* SPI_SLV_CMDA_INT_CLR:WT；位位置：[7]；默认值：1’b0；*/
/*description:SPI从属CMDA中断的清除位。。*/
#define SPI_SLV_CMDA_INT_CLR    (BIT(7))
#define SPI_SLV_CMDA_INT_CLR_M  (BIT(7))
#define SPI_SLV_CMDA_INT_CLR_V  0x1
#define SPI_SLV_CMDA_INT_CLR_S  7
/* SPI_SLV_CMD9_INT_CLR:WT；位位置：[6]；默认值：1’b0；*/
/*description:SPI从属CMD9中断的清除位。。*/
#define SPI_SLV_CMD9_INT_CLR    (BIT(6))
#define SPI_SLV_CMD9_INT_CLR_M  (BIT(6))
#define SPI_SLV_CMD9_INT_CLR_V  0x1
#define SPI_SLV_CMD9_INT_CLR_S  6
/* SPI_SLV_CMD8_INT_CLR:WT；位位置：[5]；默认值：1’b0；*/
/*description:SPI从属CMD8中断的清除位。。*/
#define SPI_SLV_CMD8_INT_CLR    (BIT(5))
#define SPI_SLV_CMD8_INT_CLR_M  (BIT(5))
#define SPI_SLV_CMD8_INT_CLR_V  0x1
#define SPI_SLV_CMD8_INT_CLR_S  5
/* SPI_SLV_CMD7_INT_CLR:WT；位位置：[4]；默认值：1’b0；*/
/*description:SPI从属CMD7中断的清除位。。*/
#define SPI_SLV_CMD7_INT_CLR    (BIT(4))
#define SPI_SLV_CMD7_INT_CLR_M  (BIT(4))
#define SPI_SLV_CMD7_INT_CLR_V  0x1
#define SPI_SLV_CMD7_INT_CLR_S  4
/* SPI_SLV_EN_QPI_INT_CLR:WT；位位置：[3]；默认值：1’b0；*/
/*description:SPI从属En_QPI中断的清除位。。*/
#define SPI_SLV_EN_QPI_INT_CLR    (BIT(3))
#define SPI_SLV_EN_QPI_INT_CLR_M  (BIT(3))
#define SPI_SLV_EN_QPI_INT_CLR_V  0x1
#define SPI_SLV_EN_QPI_INT_CLR_S  3
/* SPI_SLV_EX_QPI_INT_CLR:WT；位位置：[2]；默认值：1’b0；*/
/*description:SPI从设备Ex_QPI中断的清除位。。*/
#define SPI_SLV_EX_QPI_INT_CLR    (BIT(2))
#define SPI_SLV_EX_QPI_INT_CLR_M  (BIT(2))
#define SPI_SLV_EX_QPI_INT_CLR_V  0x1
#define SPI_SLV_EX_QPI_INT_CLR_S  2
/* SPI_DMA_OUTFIFO_EMPTY_ERR_INT_CLR:WT；位位置：[1]；默认值：1’b0；*/
/*description:SPI_DMA_OUTFIFO_EMPTY_ERR_INT中断的清除位。。*/
#define SPI_DMA_OUTFIFO_EMPTY_ERR_INT_CLR    (BIT(1))
#define SPI_DMA_OUTFIFO_EMPTY_ERR_INT_CLR_M  (BIT(1))
#define SPI_DMA_OUTFIFO_EMPTY_ERR_INT_CLR_V  0x1
#define SPI_DMA_OUTFIFO_EMPTY_ERR_INT_CLR_S  1
/* SPI_DMA_INFIFO_FULL_ERR_INT_CLR:WT；位位置：[0]；默认值：1’b0；*/
/*description:SPI_DMA_INFIFO_FULL_ERROR_INT中断的清除位。。*/
#define SPI_DMA_INFIFO_FULL_ERR_INT_CLR    (BIT(0))
#define SPI_DMA_INFIFO_FULL_ERR_INT_CLR_M  (BIT(0))
#define SPI_DMA_INFIFO_FULL_ERR_INT_CLR_V  0x1
#define SPI_DMA_INFIFO_FULL_ERR_INT_CLR_S  0

#define SPI_DMA_INT_RAW_REG(i)          (REG_SPI_BASE(i) + 0x3C)
/* SPI_APP1_INT_RAW:R/W/WTC；位位置：[20]；默认值：1’b0；*/
/*description:SPI_APP1_INT中断的原始位。该值仅由应用程序控制。。*/
#define SPI_APP1_INT_RAW    (BIT(20))
#define SPI_APP1_INT_RAW_M  (BIT(20))
#define SPI_APP1_INT_RAW_V  0x1
#define SPI_APP1_INT_RAW_S  20
/* SPI_APP2_INT_RAW:R/W/WTC；位位置：[19]；默认值：1’b0；*/
/*description:SPI_APP2_INT中断的原始位。该值仅由应用程序控制。。*/
#define SPI_APP2_INT_RAW    (BIT(19))
#define SPI_APP2_INT_RAW_M  (BIT(19))
#define SPI_APP2_INT_RAW_V  0x1
#define SPI_APP2_INT_RAW_S  19
/* SPI_MST_TX_AFIFO_REMPTY_ERR_INT_RAW:R/W/WTC/SS；位位置：[18]；默认值：1’b0；*/
/*description:SPI_MST_TX_AFIFO_REMPTY_ERR_INT中断的原始位。1： 当SPI以主模式输出数据时，存在TX BUFFIFO读取空错误。0：其他。。*/
#define SPI_MST_TX_AFIFO_REMPTY_ERR_INT_RAW    (BIT(18))
#define SPI_MST_TX_AFIFO_REMPTY_ERR_INT_RAW_M  (BIT(18))
#define SPI_MST_TX_AFIFO_REMPTY_ERR_INT_RAW_V  0x1
#define SPI_MST_TX_AFIFO_REMPTY_ERR_INT_RAW_S  18
/* SPI_MST_RX_AFIFO_wull_ERR_INT_RAW:R/W/WTC/SS；位位置：[17]；默认值：1’b0；*/
/*description:SPI_MST_RX_AFIFO_WFULL_ERROR_INT中断的原始位。1： 当SPI在主模式下输入数据时，存在RX AFIFO写满错误。0：其他。。*/
#define SPI_MST_RX_AFIFO_WFULL_ERR_INT_RAW    (BIT(17))
#define SPI_MST_RX_AFIFO_WFULL_ERR_INT_RAW_M  (BIT(17))
#define SPI_MST_RX_AFIFO_WFULL_ERR_INT_RAW_V  0x1
#define SPI_MST_RX_AFIFO_WFULL_ERR_INT_RAW_S  17
/* SPI_SLV_CMD_ERR_INT_RAW:R/W/WTC/SS；位位置：[16]；默认值：1’b0；*/
/*description:SPI_SLV_CMD_ERR_INT中断的原始位。1： 当前SPI从属HD模式传输中的从属命令值不受支持。0：其他。。*/
#define SPI_SLV_CMD_ERR_INT_RAW    (BIT(16))
#define SPI_SLV_CMD_ERR_INT_RAW_M  (BIT(16))
#define SPI_SLV_CMD_ERR_INT_RAW_V  0x1
#define SPI_SLV_CMD_ERR_INT_RAW_S  16
/* SPI_SLV_BUF_ADDR_ERR_INT_RAW:R/W/WTC/SS；位位置：[15]；默认值：1’b0；*/
/*description:SPI_SLV_BUF_ADDR_ERR_INT中断的原始位。1： 当前SPI从模式CPU控制的FD、Wr_BUF或Rd_BUF传输的访问数据地址大于63.0：其他。。*/
#define SPI_SLV_BUF_ADDR_ERR_INT_RAW    (BIT(15))
#define SPI_SLV_BUF_ADDR_ERR_INT_RAW_M  (BIT(15))
#define SPI_SLV_BUF_ADDR_ERR_INT_RAW_V  0x1
#define SPI_SLV_BUF_ADDR_ERR_INT_RAW_S  15
/* SPI_SEG_MAGIC_ERR_INT_RAW:R/W/WTC/SS；位位置：[14]；默认值：1’b0；*/
/*description:SPI_SEG_MAGIC_ERR_INT中断的原始位。1： CONF缓冲区中的神奇值是DMA seg-CONF传输中的错误。0:其他。。*/
#define SPI_SEG_MAGIC_ERR_INT_RAW    (BIT(14))
#define SPI_SEG_MAGIC_ERR_INT_RAW_M  (BIT(14))
#define SPI_SEG_MAGIC_ERR_INT_RAW_V  0x1
#define SPI_SEG_MAGIC_ERR_INT_RAW_S  14
/* SPI_DMA_SEG_TRANS_DONE_INT_RAW:R/W/WTC/SS；位位置：[13]；默认值：1’b0；*/
/*description:SPI_DMA_SEG_TRANS_DONE_INT中断的原始位。1： spi主DMA全双工/半双工seg-conf传输结束或从半双工seg传输结束。数据已被推送到相应的存储器。0:seg conf trans或seg trans未结束或未发生。*/
#define SPI_DMA_SEG_TRANS_DONE_INT_RAW    (BIT(13))
#define SPI_DMA_SEG_TRANS_DONE_INT_RAW_M  (BIT(13))
#define SPI_DMA_SEG_TRANS_DONE_INT_RAW_V  0x1
#define SPI_DMA_SEG_TRANS_DONE_INT_RAW_S  13
/* SPI_TRANS_DONE_INT_RAW:R/W/WTC/SS；位位置：[12]；默认值：1’b0；*/
/*description:SPI_TRANS_DONE_INT中断的原始位。1： SPI主模式传输结束。0:其他。。*/
#define SPI_TRANS_DONE_INT_RAW    (BIT(12))
#define SPI_TRANS_DONE_INT_RAW_M  (BIT(12))
#define SPI_TRANS_DONE_INT_RAW_V  0x1
#define SPI_TRANS_DONE_INT_RAW_S  12
/* SPI_SLV_WR_BUF_DONE_INT_RAW:R/W/WTC/SS；位位置：[11]；默认值：1’b0；*/
/*description:SPI_SLV_WR_BUF_DON_INT中断的原始位。1： SPI从模式Wr_BUF传输结束。0：其他。。*/
#define SPI_SLV_WR_BUF_DONE_INT_RAW    (BIT(11))
#define SPI_SLV_WR_BUF_DONE_INT_RAW_M  (BIT(11))
#define SPI_SLV_WR_BUF_DONE_INT_RAW_V  0x1
#define SPI_SLV_WR_BUF_DONE_INT_RAW_S  11
/* SPI_SLV_RD_BUF_DONE_INT_RAW:R/W/WTC/SS；位位置：[10]；默认值：1’b0；*/
/*description:SPI_SLV_RD_BUF_DON_INT中断的原始位。1： SPI从模式Rd_BUF传输结束。0：其他。。*/
#define SPI_SLV_RD_BUF_DONE_INT_RAW    (BIT(10))
#define SPI_SLV_RD_BUF_DONE_INT_RAW_M  (BIT(10))
#define SPI_SLV_RD_BUF_DONE_INT_RAW_V  0x1
#define SPI_SLV_RD_BUF_DONE_INT_RAW_S  10
/* SPI_SLV_WR_DMA_DONE_INT_RAW:R/W/WTC/SS；位位置：[9]；默认值：1’b0；*/
/*description:SPI_SLV_WR_DMA_DONE_INT中断的原始位。1： SPI从属模式Wr_DMA传输结束。0：其他。。*/
#define SPI_SLV_WR_DMA_DONE_INT_RAW    (BIT(9))
#define SPI_SLV_WR_DMA_DONE_INT_RAW_M  (BIT(9))
#define SPI_SLV_WR_DMA_DONE_INT_RAW_V  0x1
#define SPI_SLV_WR_DMA_DONE_INT_RAW_S  9
/* SPI_SLV_RD_DMA_DONE_INT_RAW:R/W/WTC/SS；位位置：[8]；默认值：1’b0；*/
/*description:SPI_SLV_RD_DMA_DONE_INT中断的原始位。1： SPI从属模式Rd_DMA传输结束。0：其他。。*/
#define SPI_SLV_RD_DMA_DONE_INT_RAW    (BIT(8))
#define SPI_SLV_RD_DMA_DONE_INT_RAW_M  (BIT(8))
#define SPI_SLV_RD_DMA_DONE_INT_RAW_V  0x1
#define SPI_SLV_RD_DMA_DONE_INT_RAW_S  8
/* SPI_SLV_CMDA_INT_RAW:R/W/WTC/SS；位位置：[7]；默认值：1’b0；*/
/*description:SPI从属CMDA中断的原始位。1： SPI从模式CMDA传输结束。0：其他。。*/
#define SPI_SLV_CMDA_INT_RAW    (BIT(7))
#define SPI_SLV_CMDA_INT_RAW_M  (BIT(7))
#define SPI_SLV_CMDA_INT_RAW_V  0x1
#define SPI_SLV_CMDA_INT_RAW_S  7
/* SPI_SLV_CMD9_INT_RAW:R/W/WTC/SS；位位置：[6]；默认值：1’b0；*/
/*description:SPI从属CMD9中断的原始位。1： SPI从模式CMD9传输结束。0：其他。。*/
#define SPI_SLV_CMD9_INT_RAW    (BIT(6))
#define SPI_SLV_CMD9_INT_RAW_M  (BIT(6))
#define SPI_SLV_CMD9_INT_RAW_V  0x1
#define SPI_SLV_CMD9_INT_RAW_S  6
/* SPI_SLV_CMD8_INT_RAW:R/W/WTC/SS；位位置：[5]；默认值：1’b0；*/
/*description:SPI从属CMD8中断的原始位。1： SPI从模式CMD8传输结束。0：其他。。*/
#define SPI_SLV_CMD8_INT_RAW    (BIT(5))
#define SPI_SLV_CMD8_INT_RAW_M  (BIT(5))
#define SPI_SLV_CMD8_INT_RAW_V  0x1
#define SPI_SLV_CMD8_INT_RAW_S  5
/* SPI_SLV_CMD7_INT_RAW:R/W/WTC/SS；位位置：[4]；默认值：1’b0；*/
/*description:SPI从属CMD7中断的原始位。1： SPI从模式CMD7传输结束。0：其他。。*/
#define SPI_SLV_CMD7_INT_RAW    (BIT(4))
#define SPI_SLV_CMD7_INT_RAW_M  (BIT(4))
#define SPI_SLV_CMD7_INT_RAW_V  0x1
#define SPI_SLV_CMD7_INT_RAW_S  4
/* SPI_SLV_EN_QPI_INT_RAW:R/W/WTC/SS；位位置：[3]；默认值：1’b0；*/
/*description:SPI从属En_QPI中断的原始位。1： SPI从属模式En_QPI传输结束。0：其他。。*/
#define SPI_SLV_EN_QPI_INT_RAW    (BIT(3))
#define SPI_SLV_EN_QPI_INT_RAW_M  (BIT(3))
#define SPI_SLV_EN_QPI_INT_RAW_V  0x1
#define SPI_SLV_EN_QPI_INT_RAW_S  3
/* SPI_SLV_EX_QPI_INT_RAW:R/W/WTC/SS；位位置：[2]；默认值：1’b0；*/
/*description:SPI从属Ex_QPI中断的原始位。1： SPI从模式Ex_QPI传输结束。0：其他。。*/
#define SPI_SLV_EX_QPI_INT_RAW    (BIT(2))
#define SPI_SLV_EX_QPI_INT_RAW_M  (BIT(2))
#define SPI_SLV_EX_QPI_INT_RAW_V  0x1
#define SPI_SLV_EX_QPI_INT_RAW_S  2
/* SPI_DMA_OUTFIFO_EMPTY_ERR_INT_RAW:R/W/WTC/SS；位位置：[1]；默认值：1’b0；*/
/*描述：1:DMA TX的当前数据速率小于SPI。SPI将在主模式下停止，并在从模式下发送所有0。0：其他。*/
#define SPI_DMA_OUTFIFO_EMPTY_ERR_INT_RAW    (BIT(1))
#define SPI_DMA_OUTFIFO_EMPTY_ERR_INT_RAW_M  (BIT(1))
#define SPI_DMA_OUTFIFO_EMPTY_ERR_INT_RAW_V  0x1
#define SPI_DMA_OUTFIFO_EMPTY_ERR_INT_RAW_S  1
/* SPI_DMA_INFIFO_FULL_ERR_INT_RAW:R/W/WTC/SS；位位置：[0]；默认值：1’b0；*/
/*描述：1:DMA Rx的当前数据速率小于SPI，这将丢失接收数据。0：其他。*/
#define SPI_DMA_INFIFO_FULL_ERR_INT_RAW    (BIT(0))
#define SPI_DMA_INFIFO_FULL_ERR_INT_RAW_M  (BIT(0))
#define SPI_DMA_INFIFO_FULL_ERR_INT_RAW_V  0x1
#define SPI_DMA_INFIFO_FULL_ERR_INT_RAW_S  0

#define SPI_DMA_INT_ST_REG(i)          (REG_SPI_BASE(i) + 0x40)
/* SPI_APP1_INT_ST:RO；位位置：[20]；默认值：1’b0；*/
/*description:SPI_APP1_INT中断的状态位。。*/
#define SPI_APP1_INT_ST    (BIT(20))
#define SPI_APP1_INT_ST_M  (BIT(20))
#define SPI_APP1_INT_ST_V  0x1
#define SPI_APP1_INT_ST_S  20
/* SPI_APP2_INT_ST:RO；位位置：[19]；默认值：1’b0；*/
/*description:SPI_APP2_INT中断的状态位。。*/
#define SPI_APP2_INT_ST    (BIT(19))
#define SPI_APP2_INT_ST_M  (BIT(19))
#define SPI_APP2_INT_ST_V  0x1
#define SPI_APP2_INT_ST_S  19
/* SPI_MST_TX_AFIFO_REMPTY_ERR_INT_ST:RO；位位置：[18]；默认值：1’b0；*/
/*description:SPI_MST_TX_AFIFO_REMPTY_ERR_INT中断的状态位。。*/
#define SPI_MST_TX_AFIFO_REMPTY_ERR_INT_ST    (BIT(18))
#define SPI_MST_TX_AFIFO_REMPTY_ERR_INT_ST_M  (BIT(18))
#define SPI_MST_TX_AFIFO_REMPTY_ERR_INT_ST_V  0x1
#define SPI_MST_TX_AFIFO_REMPTY_ERR_INT_ST_S  18
/* SPI_MST_RX_AFIFO_wull_ERR_INT_ST:RO；位位置：[17]；默认值：1’b0；*/
/*description:SPI_MST_RX_AFIFO_WFULL_ERROR_INT中断的状态位。。*/
#define SPI_MST_RX_AFIFO_WFULL_ERR_INT_ST    (BIT(17))
#define SPI_MST_RX_AFIFO_WFULL_ERR_INT_ST_M  (BIT(17))
#define SPI_MST_RX_AFIFO_WFULL_ERR_INT_ST_V  0x1
#define SPI_MST_RX_AFIFO_WFULL_ERR_INT_ST_S  17
/* SPI_SLV_CMD_ERR_INT_ST:RO；位位置：[16]；默认值：1’b0；*/
/*description:SPI_SLV_CMD_ERR_INT中断的状态位。。*/
#define SPI_SLV_CMD_ERR_INT_ST    (BIT(16))
#define SPI_SLV_CMD_ERR_INT_ST_M  (BIT(16))
#define SPI_SLV_CMD_ERR_INT_ST_V  0x1
#define SPI_SLV_CMD_ERR_INT_ST_S  16
/* SPI_SLV_BUF_ADDR_ERR_INT_ST:RO；位位置：[15]；默认值：1’b0；*/
/*description:SPI_SLV_BUF_ADDR_ERR_INT中断的状态位。。*/
#define SPI_SLV_BUF_ADDR_ERR_INT_ST    (BIT(15))
#define SPI_SLV_BUF_ADDR_ERR_INT_ST_M  (BIT(15))
#define SPI_SLV_BUF_ADDR_ERR_INT_ST_V  0x1
#define SPI_SLV_BUF_ADDR_ERR_INT_ST_S  15
/* SPI_SEG_MAGIC_ERR_INT_ST:RO；位位置：[14]；默认值：1’b0；*/
/*description:SPI_SEG_MAGIC_ERR_INT中断的状态位。。*/
#define SPI_SEG_MAGIC_ERR_INT_ST    (BIT(14))
#define SPI_SEG_MAGIC_ERR_INT_ST_M  (BIT(14))
#define SPI_SEG_MAGIC_ERR_INT_ST_V  0x1
#define SPI_SEG_MAGIC_ERR_INT_ST_S  14
/* SPI_DMA_SEG_TRANS_DONE_INT_ST:RO；位位置：[13]；默认值：1’b0；*/
/*description:SPI_DMA_SEG_TRANS_DONE_INT中断的状态位。。*/
#define SPI_DMA_SEG_TRANS_DONE_INT_ST    (BIT(13))
#define SPI_DMA_SEG_TRANS_DONE_INT_ST_M  (BIT(13))
#define SPI_DMA_SEG_TRANS_DONE_INT_ST_V  0x1
#define SPI_DMA_SEG_TRANS_DONE_INT_ST_S  13
/* SPI_TRANS_DONE_INT_ST:RO；位位置：[12]；默认值：1’b0；*/
/*description:SPI_TRANS_DONE_INT中断的状态位。。*/
#define SPI_TRANS_DONE_INT_ST    (BIT(12))
#define SPI_TRANS_DONE_INT_ST_M  (BIT(12))
#define SPI_TRANS_DONE_INT_ST_V  0x1
#define SPI_TRANS_DONE_INT_ST_S  12
/* SPI_SLV_WR_BUF_DONE_INT_ST:RO；位位置：[11]；默认值：1’b0；*/
/*description:SPI_SLV_WR_BUF_DON_INT中断的状态位。。*/
#define SPI_SLV_WR_BUF_DONE_INT_ST    (BIT(11))
#define SPI_SLV_WR_BUF_DONE_INT_ST_M  (BIT(11))
#define SPI_SLV_WR_BUF_DONE_INT_ST_V  0x1
#define SPI_SLV_WR_BUF_DONE_INT_ST_S  11
/* SPI_SLV_RD_BUF_DONE_INT_ST:RO；位位置：[10]；默认值：1’b0；*/
/*description:SPI_SLV_RD_BUF_DON_INT中断的状态位。。*/
#define SPI_SLV_RD_BUF_DONE_INT_ST    (BIT(10))
#define SPI_SLV_RD_BUF_DONE_INT_ST_M  (BIT(10))
#define SPI_SLV_RD_BUF_DONE_INT_ST_V  0x1
#define SPI_SLV_RD_BUF_DONE_INT_ST_S  10
/* SPI_SLV_WR_DMA_DONE_INT_ST:RO；位位置：[9]；默认值：1’b0；*/
/*description:SPI_SLV_WR_DMA_DONE_INT中断的状态位。。*/
#define SPI_SLV_WR_DMA_DONE_INT_ST    (BIT(9))
#define SPI_SLV_WR_DMA_DONE_INT_ST_M  (BIT(9))
#define SPI_SLV_WR_DMA_DONE_INT_ST_V  0x1
#define SPI_SLV_WR_DMA_DONE_INT_ST_S  9
/* SPI_SLV_RD_DMA_DONE_INT_ST:RO；位位置：[8]；默认值：1’b0；*/
/*description:SPI_SLV_RD_DMA_DONE_INT中断的状态位。。*/
#define SPI_SLV_RD_DMA_DONE_INT_ST    (BIT(8))
#define SPI_SLV_RD_DMA_DONE_INT_ST_M  (BIT(8))
#define SPI_SLV_RD_DMA_DONE_INT_ST_V  0x1
#define SPI_SLV_RD_DMA_DONE_INT_ST_S  8
/* SPI_SLV_CMDA_INT_ST:RO；位位置：[7]；默认值：1’b0；*/
/*description:SPI从属CMDA中断的状态位。。*/
#define SPI_SLV_CMDA_INT_ST    (BIT(7))
#define SPI_SLV_CMDA_INT_ST_M  (BIT(7))
#define SPI_SLV_CMDA_INT_ST_V  0x1
#define SPI_SLV_CMDA_INT_ST_S  7
/* SPI_SLV_CMD9_INT_ST:RO；位位置：[6]；默认值：1’b0；*/
/*description:SPI从属CMD9中断的状态位。。*/
#define SPI_SLV_CMD9_INT_ST    (BIT(6))
#define SPI_SLV_CMD9_INT_ST_M  (BIT(6))
#define SPI_SLV_CMD9_INT_ST_V  0x1
#define SPI_SLV_CMD9_INT_ST_S  6
/* SPI_SLV_CMD8_INT_ST:RO；位位置：[5]；默认值：1’b0；*/
/*description:SPI从属CMD8中断的状态位。。*/
#define SPI_SLV_CMD8_INT_ST    (BIT(5))
#define SPI_SLV_CMD8_INT_ST_M  (BIT(5))
#define SPI_SLV_CMD8_INT_ST_V  0x1
#define SPI_SLV_CMD8_INT_ST_S  5
/* SPI_SLV_CMD7_INT_ST:RO；位位置：[4]；默认值：1’b0；*/
/*description:SPI从属CMD7中断的状态位。。*/
#define SPI_SLV_CMD7_INT_ST    (BIT(4))
#define SPI_SLV_CMD7_INT_ST_M  (BIT(4))
#define SPI_SLV_CMD7_INT_ST_V  0x1
#define SPI_SLV_CMD7_INT_ST_S  4
/* SPI_SLV_EN_QPI_INT_ST:RO；位位置：[3]；默认值：1’b0；*/
/*description:SPI从属En_QPI中断的状态位。。*/
#define SPI_SLV_EN_QPI_INT_ST    (BIT(3))
#define SPI_SLV_EN_QPI_INT_ST_M  (BIT(3))
#define SPI_SLV_EN_QPI_INT_ST_V  0x1
#define SPI_SLV_EN_QPI_INT_ST_S  3
/* SPI_SLV_EX_QPI_INT_ST:RO；位位置：[2]；默认值：1’b0；*/
/*description:SPI从属Ex_QPI中断的状态位。。*/
#define SPI_SLV_EX_QPI_INT_ST    (BIT(2))
#define SPI_SLV_EX_QPI_INT_ST_M  (BIT(2))
#define SPI_SLV_EX_QPI_INT_ST_V  0x1
#define SPI_SLV_EX_QPI_INT_ST_S  2
/* SPI_DMA_OUTFIFO_EMPTY_ERR_INT_ST:RO；位位置：[1]；默认值：1’b0；*/
/*description:SPI_DMA_OUTFIFO_EMPTY_ERR_INT中断的状态位。。*/
#define SPI_DMA_OUTFIFO_EMPTY_ERR_INT_ST    (BIT(1))
#define SPI_DMA_OUTFIFO_EMPTY_ERR_INT_ST_M  (BIT(1))
#define SPI_DMA_OUTFIFO_EMPTY_ERR_INT_ST_V  0x1
#define SPI_DMA_OUTFIFO_EMPTY_ERR_INT_ST_S  1
/* SPI_DMA_INFIFO_FULL_ERR_INT_ST:RO；位位置：[0]；默认值：1’b0；*/
/*description:SPI_DMA_INFIFO_FULL_ERROR_INT中断的状态位。。*/
#define SPI_DMA_INFIFO_FULL_ERR_INT_ST    (BIT(0))
#define SPI_DMA_INFIFO_FULL_ERR_INT_ST_M  (BIT(0))
#define SPI_DMA_INFIFO_FULL_ERR_INT_ST_V  0x1
#define SPI_DMA_INFIFO_FULL_ERR_INT_ST_S  0

#define SPI_DMA_INT_SET_REG(i)          (REG_SPI_BASE(i) + 0x044)
/* SPI_APP1_INT_SET:WT；位位置：[20]；默认值：1’b0；*/
/*description:SPI_APP1_INT中断的软件设置位。*/
#define SPI_APP1_INT_SET  (BIT(20))
#define SPI_APP1_INT_SET_M  (BIT(20))
#define SPI_APP1_INT_SET_V  0x1
#define SPI_APP1_INT_SET_S  20
/* SPI_APP2_INT_SET:WT；位位置：[19]；默认值：1’b0；*/
/*description:SPI_APP2_INT中断的软件设置位。*/
#define SPI_APP2_INT_SET  (BIT(19))
#define SPI_APP2_INT_SET_M  (BIT(19))
#define SPI_APP2_INT_SET_V  0x1
#define SPI_APP2_INT_SET_S  19
/* SPI_MST_TX_AFIFO_REMPTY_ERR_INT_SET:WT；位位置：[18]；默认值：1’b0；*/
/*description:SPI_MST_TX_AFIFO_REMPTY_ERR_INT中断的软件设置位。*/
#define SPI_MST_TX_AFIFO_REMPTY_ERR_INT_SET  (BIT(18))
#define SPI_MST_TX_AFIFO_REMPTY_ERR_INT_SET_M  (BIT(18))
#define SPI_MST_TX_AFIFO_REMPTY_ERR_INT_SET_V  0x1
#define SPI_MST_TX_AFIFO_REMPTY_ERR_INT_SET_S  18
/* SPI_MST_RX_AFIFO_WFULL_ERR_INT_SET:WT；位位置：[17]；默认值：1’b0；*/
/*description:SPI_MST_RX_AFIFO_WFULL_ERROR_INT中断的软件设置位。*/
#define SPI_MST_RX_AFIFO_WFULL_ERR_INT_SET  (BIT(17))
#define SPI_MST_RX_AFIFO_WFULL_ERR_INT_SET_M  (BIT(17))
#define SPI_MST_RX_AFIFO_WFULL_ERR_INT_SET_V  0x1
#define SPI_MST_RX_AFIFO_WFULL_ERR_INT_SET_S  17
/* SPI_SLV_CMD_ERR_INT_SET:WT；位位置：[16]；默认值：1’b0；*/
/*description:SPI_SLV_CMD_ERR_INT中断的软件设置位。*/
#define SPI_SLV_CMD_ERR_INT_SET  (BIT(16))
#define SPI_SLV_CMD_ERR_INT_SET_M  (BIT(16))
#define SPI_SLV_CMD_ERR_INT_SET_V  0x1
#define SPI_SLV_CMD_ERR_INT_SET_S  16
/* SPI_SLV_BUF_ADDR_ERR_INT_SET:WT；位位置：[15]；默认值：1’b0；*/
/*description:SPI_SLV_BUF_ADDR_ERR_INT中断的软件设置位。*/
#define SPI_SLV_BUF_ADDR_ERR_INT_SET  (BIT(15))
#define SPI_SLV_BUF_ADDR_ERR_INT_SET_M  (BIT(15))
#define SPI_SLV_BUF_ADDR_ERR_INT_SET_V  0x1
#define SPI_SLV_BUF_ADDR_ERR_INT_SET_S  15
/* SPI_SEG_MAGIC_ERR_INT_SET:WT；位位置：[14]；默认值：1’b0；*/
/*description:SPI_SEG_MAGIC_ERR_INT中断的软件设置位。*/
#define SPI_SEG_MAGIC_ERR_INT_SET  (BIT(14))
#define SPI_SEG_MAGIC_ERR_INT_SET_M  (BIT(14))
#define SPI_SEG_MAGIC_ERR_INT_SET_V  0x1
#define SPI_SEG_MAGIC_ERR_INT_SET_S  14
/* SPI_DMA_SEG_TRANS_DONE_INT_SET:WT；位位置：[13]；默认值：1’b0；*/
/*description:SPI_DMA_SEG_TRANS_DONE_INT中断的软件设置位。*/
#define SPI_DMA_SEG_TRANS_DONE_INT_SET  (BIT(13))
#define SPI_DMA_SEG_TRANS_DONE_INT_SET_M  (BIT(13))
#define SPI_DMA_SEG_TRANS_DONE_INT_SET_V  0x1
#define SPI_DMA_SEG_TRANS_DONE_INT_SET_S  13
/* SPI_TRANS_DONE_INT_SET:WT；位位置：[12]；默认值：1’b0；*/
/*description:SPI_TRANS_DONE_INT中断的软件设置位。*/
#define SPI_TRANS_DONE_INT_SET  (BIT(12))
#define SPI_TRANS_DONE_INT_SET_M  (BIT(12))
#define SPI_TRANS_DONE_INT_SET_V  0x1
#define SPI_TRANS_DONE_INT_SET_S  12
/* SPI_SLV_WR_BUF_DONE_INT_SET:WT；位位置：[11]；默认值：1’b0；*/
/*description:SPI_SLV_WR_BUF_DON_INT中断的软件设置位。*/
#define SPI_SLV_WR_BUF_DONE_INT_SET  (BIT(11))
#define SPI_SLV_WR_BUF_DONE_INT_SET_M  (BIT(11))
#define SPI_SLV_WR_BUF_DONE_INT_SET_V  0x1
#define SPI_SLV_WR_BUF_DONE_INT_SET_S  11
/* SPI_SLV_RD_BUF_DONE_INT_SET:WT；位位置：[10]；默认值：1’b0；*/
/*description:SPI_SLV_RD_BUF_DON_INT中断的软件设置位。*/
#define SPI_SLV_RD_BUF_DONE_INT_SET  (BIT(10))
#define SPI_SLV_RD_BUF_DONE_INT_SET_M  (BIT(10))
#define SPI_SLV_RD_BUF_DONE_INT_SET_V  0x1
#define SPI_SLV_RD_BUF_DONE_INT_SET_S  10
/* SPI_SLV_WR_DMA_DONE_INT_SET:WT；位位置：[9]；默认值：1’b0；*/
/*description:SPI_SLV_WR_DMA_DONE_INT中断的软件设置位。*/
#define SPI_SLV_WR_DMA_DONE_INT_SET  (BIT(9))
#define SPI_SLV_WR_DMA_DONE_INT_SET_M  (BIT(9))
#define SPI_SLV_WR_DMA_DONE_INT_SET_V  0x1
#define SPI_SLV_WR_DMA_DONE_INT_SET_S  9
/* SPI_SLV_RD_DMA_DONE_INT_SET:WT；位位置：[8]；默认值：1’b0；*/
/*description:SPI_SLV_RD_DMA_DONE_INT中断的软件设置位。*/
#define SPI_SLV_RD_DMA_DONE_INT_SET  (BIT(8))
#define SPI_SLV_RD_DMA_DONE_INT_SET_M  (BIT(8))
#define SPI_SLV_RD_DMA_DONE_INT_SET_V  0x1
#define SPI_SLV_RD_DMA_DONE_INT_SET_S  8
/* SPI_SLV_CMDA_INT_SET:WT；位位置：[7]；默认值：1’b0；*/
/*description:SPI从属CMDA中断的软件设置位。*/
#define SPI_SLV_CMDA_INT_SET  (BIT(7))
#define SPI_SLV_CMDA_INT_SET_M  (BIT(7))
#define SPI_SLV_CMDA_INT_SET_V  0x1
#define SPI_SLV_CMDA_INT_SET_S  7
/* SPI_SLV_CMD9_INT_SET:WT；位位置：[6]；默认值：1’b0；*/
/*description:SPI从属CMD9中断的软件设置位。*/
#define SPI_SLV_CMD9_INT_SET  (BIT(6))
#define SPI_SLV_CMD9_INT_SET_M  (BIT(6))
#define SPI_SLV_CMD9_INT_SET_V  0x1
#define SPI_SLV_CMD9_INT_SET_S  6
/* SPI_SLV_CMD8_INT_SET:WT；位位置：[5]；默认值：1’b0；*/
/*description:SPI从属CMD8中断的软件设置位。*/
#define SPI_SLV_CMD8_INT_SET  (BIT(5))
#define SPI_SLV_CMD8_INT_SET_M  (BIT(5))
#define SPI_SLV_CMD8_INT_SET_V  0x1
#define SPI_SLV_CMD8_INT_SET_S  5
/* SPI_SLV_CMD7_INT_SET:WT；位位置：[4]；默认值：1’b0；*/
/*description:SPI从属CMD7中断的软件设置位。*/
#define SPI_SLV_CMD7_INT_SET  (BIT(4))
#define SPI_SLV_CMD7_INT_SET_M  (BIT(4))
#define SPI_SLV_CMD7_INT_SET_V  0x1
#define SPI_SLV_CMD7_INT_SET_S  4
/* SPI_SLV_EN_QPI_INT_SET:WT；位位置：[3]；默认值：1’b0；*/
/*description:SPI从属En_QPI中断的软件设置位。*/
#define SPI_SLV_EN_QPI_INT_SET  (BIT(3))
#define SPI_SLV_EN_QPI_INT_SET_M  (BIT(3))
#define SPI_SLV_EN_QPI_INT_SET_V  0x1
#define SPI_SLV_EN_QPI_INT_SET_S  3
/* SPI_SLV_EX_QPI_INT_SET:WT；位位置：[2]；默认值：1’b0；*/
/*description:SPI从设备Ex_QPI中断的软件设置位。*/
#define SPI_SLV_EX_QPI_INT_SET  (BIT(2))
#define SPI_SLV_EX_QPI_INT_SET_M  (BIT(2))
#define SPI_SLV_EX_QPI_INT_SET_V  0x1
#define SPI_SLV_EX_QPI_INT_SET_S  2
/* SPI_DMA_OUTFIFO_EMPTY_ERR_INT_SET:WT；位位置：[1]；默认值：1’b0；*/
/*description:SPI_DMA_OUTFIFO_EMPTY_ERR_INT中断的软件设置位。*/
#define SPI_DMA_OUTFIFO_EMPTY_ERR_INT_SET  (BIT(1))
#define SPI_DMA_OUTFIFO_EMPTY_ERR_INT_SET_M  (BIT(1))
#define SPI_DMA_OUTFIFO_EMPTY_ERR_INT_SET_V  0x1
#define SPI_DMA_OUTFIFO_EMPTY_ERR_INT_SET_S  1
/* SPI_DMA_INFIFO_FULL_ERR_INT_SET:WT；位位置：[0]；默认值：1’b0；*/
/*description:SPI_DMA_INFIFO_FULL_ERROR_INT中断的软件设置位。*/
#define SPI_DMA_INFIFO_FULL_ERR_INT_SET  (BIT(0))
#define SPI_DMA_INFIFO_FULL_ERR_INT_SET_M  (BIT(0))
#define SPI_DMA_INFIFO_FULL_ERR_INT_SET_V  0x1
#define SPI_DMA_INFIFO_FULL_ERR_INT_SET_S  0

#define SPI_W0_REG(i)          (REG_SPI_BASE(i) + 0x098)
/* SPI_BUF0:R/W/SS；位位置：[31:0]；默认值：32'd0；*/
/*描述：数据缓冲区*/
#define SPI_BUF0  0xFFFFFFFF
#define SPI_BUF0_M  ((SPI_BUF0_V)<<(SPI_BUF0_S))
#define SPI_BUF0_V  0xFFFFFFFF
#define SPI_BUF0_S  0

#define SPI_W1_REG(i)          (REG_SPI_BASE(i) + 0x09C)
/* SPI_BUF1:R/W/SS；位位置：[31:0]；默认值：32'd0；*/
/*描述：数据缓冲区*/
#define SPI_BUF1  0xFFFFFFFF
#define SPI_BUF1_M  ((SPI_BUF1_V)<<(SPI_BUF1_S))
#define SPI_BUF1_V  0xFFFFFFFF
#define SPI_BUF1_S  0

#define SPI_W2_REG(i)          (REG_SPI_BASE(i) + 0x0A0)
/* SPI_BUF2:R/W/SS；位位置：[31:0]；默认值：32'd0；*/
/*描述：数据缓冲区*/
#define SPI_BUF2  0xFFFFFFFF
#define SPI_BUF2_M  ((SPI_BUF2_V)<<(SPI_BUF2_S))
#define SPI_BUF2_V  0xFFFFFFFF
#define SPI_BUF2_S  0

#define SPI_W3_REG(i)          (REG_SPI_BASE(i) + 0x0A4)
/* SPI_BUF3:R/W/SS；位位置：[31:0]；默认值：32'd0；*/
/*描述：数据缓冲区*/
#define SPI_BUF3  0xFFFFFFFF
#define SPI_BUF3_M  ((SPI_BUF3_V)<<(SPI_BUF3_S))
#define SPI_BUF3_V  0xFFFFFFFF
#define SPI_BUF3_S  0

#define SPI_W4_REG(i)          (REG_SPI_BASE(i) + 0x0A8)
/* SPI_BUF4:R/W/SS；位位置：[31:0]；默认值：32'd0；*/
/*描述：数据缓冲区*/
#define SPI_BUF4  0xFFFFFFFF
#define SPI_BUF4_M  ((SPI_BUF4_V)<<(SPI_BUF4_S))
#define SPI_BUF4_V  0xFFFFFFFF
#define SPI_BUF4_S  0

#define SPI_W5_REG(i)          (REG_SPI_BASE(i) + 0x0AC)
/* SPI_BUF5:R/W/SS；位位置：[31:0]；默认值：32'd0；*/
/*描述：数据缓冲区*/
#define SPI_BUF5  0xFFFFFFFF
#define SPI_BUF5_M  ((SPI_BUF5_V)<<(SPI_BUF5_S))
#define SPI_BUF5_V  0xFFFFFFFF
#define SPI_BUF5_S  0

#define SPI_W6_REG(i)          (REG_SPI_BASE(i) + 0x0B0)
/* SPI_BUF6:R/W/SS；位位置：[31:0]；默认值：32'd0；*/
/*描述：数据缓冲区*/
#define SPI_BUF6  0xFFFFFFFF
#define SPI_BUF6_M  ((SPI_BUF6_V)<<(SPI_BUF6_S))
#define SPI_BUF6_V  0xFFFFFFFF
#define SPI_BUF6_S  0

#define SPI_W7_REG(i)          (REG_SPI_BASE(i) + 0x0B4)
/* SPI_BUF7:R/W/SS；位位置：[31:0]；默认值：32'd0；*/
/*描述：数据缓冲区*/
#define SPI_BUF7  0xFFFFFFFF
#define SPI_BUF7_M  ((SPI_BUF7_V)<<(SPI_BUF7_S))
#define SPI_BUF7_V  0xFFFFFFFF
#define SPI_BUF7_S  0

#define SPI_W8_REG(i)          (REG_SPI_BASE(i) + 0x0B8)
/* SPI_BUF8:R/W/SS；位位置：[31:0]；默认值：32'd0；*/
/*描述：数据缓冲区*/
#define SPI_BUF8  0xFFFFFFFF
#define SPI_BUF8_M  ((SPI_BUF8_V)<<(SPI_BUF8_S))
#define SPI_BUF8_V  0xFFFFFFFF
#define SPI_BUF8_S  0

#define SPI_W9_REG(i)          (REG_SPI_BASE(i) + 0x0BC)
/* SPI_BUF9:R/W/SS；位位置：[31:0]；默认值：32'd0；*/
/*描述：数据缓冲区*/
#define SPI_BUF9  0xFFFFFFFF
#define SPI_BUF9_M  ((SPI_BUF9_V)<<(SPI_BUF9_S))
#define SPI_BUF9_V  0xFFFFFFFF
#define SPI_BUF9_S  0

#define SPI_W10_REG(i)          (REG_SPI_BASE(i) + 0x0C0)
/* SPI_BUF10:R/W/SS；位位置：[31:0]；默认值：32'd0；*/
/*描述：数据缓冲区*/
#define SPI_BUF10  0xFFFFFFFF
#define SPI_BUF10_M  ((SPI_BUF10_V)<<(SPI_BUF10_S))
#define SPI_BUF10_V  0xFFFFFFFF
#define SPI_BUF10_S  0

#define SPI_W11_REG(i)          (REG_SPI_BASE(i) + 0x0C4)
/* SPI_BUF11:R/W/SS；位位置：[31:0]；默认值：32'd0；*/
/*描述：数据缓冲区*/
#define SPI_BUF11  0xFFFFFFFF
#define SPI_BUF11_M  ((SPI_BUF11_V)<<(SPI_BUF11_S))
#define SPI_BUF11_V  0xFFFFFFFF
#define SPI_BUF11_S  0

#define SPI_W12_REG(i)          (REG_SPI_BASE(i) + 0x0C8)
/* SPI_BUF12:R/W/SS；位位置：[31:0]；默认值：32'd0；*/
/*描述：数据缓冲区*/
#define SPI_BUF12  0xFFFFFFFF
#define SPI_BUF12_M  ((SPI_BUF12_V)<<(SPI_BUF12_S))
#define SPI_BUF12_V  0xFFFFFFFF
#define SPI_BUF12_S  0

#define SPI_W13_REG(i)          (REG_SPI_BASE(i) + 0x0CC)
/* SPI_BUF13:R/W/SS；位位置：[31:0]；默认值：32'd0；*/
/*描述：数据缓冲区*/
#define SPI_BUF13  0xFFFFFFFF
#define SPI_BUF13_M  ((SPI_BUF13_V)<<(SPI_BUF13_S))
#define SPI_BUF13_V  0xFFFFFFFF
#define SPI_BUF13_S  0

#define SPI_W14_REG(i)          (REG_SPI_BASE(i) + 0x0D0)
/* SPI_BUF14:R/W/SS；位位置：[31:0]；默认值：32'd0；*/
/*描述：数据缓冲区*/
#define SPI_BUF14  0xFFFFFFFF
#define SPI_BUF14_M  ((SPI_BUF14_V)<<(SPI_BUF14_S))
#define SPI_BUF14_V  0xFFFFFFFF
#define SPI_BUF14_S  0

#define SPI_W15_REG(i)          (REG_SPI_BASE(i) + 0x0D4)
/* SPI_BUF15:R/W/SS；位位置：[31:0]；默认值：32'd0；*/
/*描述：数据缓冲区*/
#define SPI_BUF15  0xFFFFFFFF
#define SPI_BUF15_M  ((SPI_BUF15_V)<<(SPI_BUF15_S))
#define SPI_BUF15_V  0xFFFFFFFF
#define SPI_BUF15_S  0

#define SPI_SLAVE_REG(i)          (REG_SPI_BASE(i) + 0x0E0)
/* SPI_USR_CONF:R/W；位位置：[28]；默认值：1’b0；*/
/*description:1：启用当前seg trans操作的DMA CONF阶段，这意味着seg trans将启动。0：这不是seg trans模式。*/
#define SPI_USR_CONF  (BIT(28))
#define SPI_USR_CONF_M  (BIT(28))
#define SPI_USR_CONF_V  0x1
#define SPI_USR_CONF_S  28
/* SPI_SOFT_RESET:WT；位位置：[27]；默认值：1’b0；*/
/*描述：软件复位使能复位spi时钟线cs线和数据线。可在形态状态下配置。*/
#define SPI_SOFT_RESET  (BIT(27))
#define SPI_SOFT_RESET_M  (BIT(27))
#define SPI_SOFT_RESET_V  0x1
#define SPI_SOFT_RESET_S  27
/* SPI_SLAVE_MODE：R/W；位位置：[26]；默认值：1’b0；*/
/*description:设置SPI工作模式。1： 从模式0：主模式。*/
#define SPI_SLAVE_MODE  (BIT(26))
#define SPI_SLAVE_MODE_M  (BIT(26))
#define SPI_SLAVE_MODE_V  0x1
#define SPI_SLAVE_MODE_S  26
/* SPI_DMA_SEG_MAGIC_VALUE:R/W；位位置：[25:22]；默认值：4'd10；*/
/*描述：主DMA seg trans中BM表的神奇值。*/
#define SPI_DMA_SEG_MAGIC_VALUE  0x0000000F
#define SPI_DMA_SEG_MAGIC_VALUE_M  ((SPI_DMA_SEG_MAGIC_VALUE_V)<<(SPI_DMA_SEG_MAGIC_VALUE_S))
#define SPI_DMA_SEG_MAGIC_VALUE_V  0xF
#define SPI_DMA_SEG_MAGIC_VALUE_S  22
/* SPI_SLV_WRBUF_BITLEN_EN:R/W；位位置：[11]；默认值：1’b0；*/
/*描述：1:SPI_SLV_DATA_BITLEN在CPU控制模式（Wr_BUF）下存储主写从数据长度的数据位长度。0:其他*/
#define SPI_SLV_WRBUF_BITLEN_EN  (BIT(11))
#define SPI_SLV_WRBUF_BITLEN_EN_M  (BIT(11))
#define SPI_SLV_WRBUF_BITLEN_EN_V  0x1
#define SPI_SLV_WRBUF_BITLEN_EN_S  11
/* SPI_SLV_RDBUF_BITLEN_EN:R/W；位位置：[10]；默认值：1’b0；*/
/*描述：1:SPI_SLV_DATA_BITLEN以CPU控制模式（Rd_BUF）存储主从数据长度的数据位长度。0:其他*/
#define SPI_SLV_RDBUF_BITLEN_EN  (BIT(10))
#define SPI_SLV_RDBUF_BITLEN_EN_M  (BIT(10))
#define SPI_SLV_RDBUF_BITLEN_EN_V  0x1
#define SPI_SLV_RDBUF_BITLEN_EN_S  10
/* SPI_SLV_WRDMA_BITLEN_EN:R/W；位位置：[9]；默认值：1’b0；*/
/*描述：1:SPI_SLV_DATA_BITLEN以DMA控制模式（Wr_DMA）存储主写从数据长度的数据位长度。0:其他*/
#define SPI_SLV_WRDMA_BITLEN_EN  (BIT(9))
#define SPI_SLV_WRDMA_BITLEN_EN_M  (BIT(9))
#define SPI_SLV_WRDMA_BITLEN_EN_V  0x1
#define SPI_SLV_WRDMA_BITLEN_EN_S  9
/* SPI_SLV_RDDMA_BITLEN_EN:R/W；位位置：[8]；默认值：1’b0；*/
/*描述：1:SPI_SLV_DATA_BITLEN以DMA控制模式（Rd_DMA）存储主从数据长度的数据位长度。0:其他*/
#define SPI_SLV_RDDMA_BITLEN_EN  (BIT(8))
#define SPI_SLV_RDDMA_BITLEN_EN_M  (BIT(8))
#define SPI_SLV_RDDMA_BITLEN_EN_V  0x1
#define SPI_SLV_RDDMA_BITLEN_EN_S  8
/* SPI_RSCK_DATA_OUT:R/W；位位置：[3]；默认值：1’b0；*/
/*description:当tsck与rsck相同时，可以节省半个周期。1： rsck posedge 0处的输出数据：tsck posedge处的输出*/
#define SPI_RSCK_DATA_OUT  (BIT(3))
#define SPI_RSCK_DATA_OUT_M  (BIT(3))
#define SPI_RSCK_DATA_OUT_V  0x1
#define SPI_RSCK_DATA_OUT_S  3
/* SPI_CLK_MODE_13:R/W；位位置：[2]；默认值：1’b0；*/
/*描述：｛CPOL CPHA｝1：支持spi-clk模式1和3第一边缘输出数据B[0]/B[7]。0：支持spi-clk模式0和2第一边缘输出数据B[1]/B[6]。*/
#define SPI_CLK_MODE_13  (BIT(2))
#define SPI_CLK_MODE_13_M  (BIT(2))
#define SPI_CLK_MODE_13_V  0x1
#define SPI_CLK_MODE_13_S  2
/* SPI_CLK_MODE：R/W；位位置：[1:0]；默认值：2’b0；*/
/*description:SPI时钟模式位。0:当CS不活动时SPI时钟关闭1:在CS不活动后SPI时钟延迟一个周期2:在CS不激活后SPI时钟推迟两个周期3:SPI时钟始终打开。可以在CONF状态下配置。*/
#define SPI_CLK_MODE  0x00000003
#define SPI_CLK_MODE_M  ((SPI_CLK_MODE_V)<<(SPI_CLK_MODE_S))
#define SPI_CLK_MODE_V  0x3
#define SPI_CLK_MODE_S  0

#define SPI_SLAVE1_REG(i)          (REG_SPI_BASE(i) + 0x0E4)
/* SPI_SLV_LAST_ADDR:R/W/SS；位位置：[31:26]；默认值：6'd0；*/
/*description:在从属模式下，它是地址的值。*/
#define SPI_SLV_LAST_ADDR  0x0000003F
#define SPI_SLV_LAST_ADDR_M  ((SPI_SLV_LAST_ADDR_V)<<(SPI_SLV_LAST_ADDR_S))
#define SPI_SLV_LAST_ADDR_V  0x3F
#define SPI_SLV_LAST_ADDR_S  26
/* SPI_SLV_LAST_COMMAND：R/W/SS；比特位置：[25:18]；默认值：8'b0；*/
/*description:在从属模式下，它是命令的值。*/
#define SPI_SLV_LAST_COMMAND  0x000000FF
#define SPI_SLV_LAST_COMMAND_M  ((SPI_SLV_LAST_COMMAND_V)<<(SPI_SLV_LAST_COMMAND_S))
#define SPI_SLV_LAST_COMMAND_V  0xFF
#define SPI_SLV_LAST_COMMAND_S  18
/* SPI_SLV_DATA_BITLEN:R/W/SS；比特位置：[17:00]；默认值：18'd0；*/
/*description:SPI从FD和HD模式下传输的数据位长度。*/
#define SPI_SLV_DATA_BITLEN  0x0003FFFF
#define SPI_SLV_DATA_BITLEN_M  ((SPI_SLV_DATA_BITLEN_V)<<(SPI_SLV_DATA_BITLEN_S))
#define SPI_SLV_DATA_BITLEN_V  0x3FFFF
#define SPI_SLV_DATA_BITLEN_S  0

#define SPI_CLK_GATE_REG(i)          (REG_SPI_BASE(i) + 0x0E8)
/* SPI_MST_CLK_SEL:R/W；位位置：[2]；默认值：1’b0；*/
/*description:此位用于在主模式下选择SPI模块时钟源。1： PLL_CLK_80M。0:XTAL CLK。*/
#define SPI_MST_CLK_SEL  (BIT(2))
#define SPI_MST_CLK_SEL_M  (BIT(2))
#define SPI_MST_CLK_SEL_V  0x1
#define SPI_MST_CLK_SEL_S  2
/* SPI_MST_CLK_ACTIVE:R/W；位位置：[1]；默认值：1’b0；*/
/*description:设置此位以打开SPI模块时钟。*/
#define SPI_MST_CLK_ACTIVE  (BIT(1))
#define SPI_MST_CLK_ACTIVE_M  (BIT(1))
#define SPI_MST_CLK_ACTIVE_V  0x1
#define SPI_MST_CLK_ACTIVE_S  1
/* SPI_CLK_EN:R/W；位位置：[0]；默认值：1’b0；*/
/*description:设置此位以启用clk门*/
#define SPI_CLK_EN  (BIT(0))
#define SPI_CLK_EN_M  (BIT(0))
#define SPI_CLK_EN_V  0x1
#define SPI_CLK_EN_S  0

#define SPI_DATE_REG(i)          (REG_SPI_BASE(i) + 0x0F0)
/* SPI_日期：R/W；位位置：[27:0]；默认值：28'h2101040；*/
/*description:SPI寄存器版本。*/
#define SPI_DATE  0x0FFFFFFF
#define SPI_DATE_M  ((SPI_DATE_V)<<(SPI_DATE_S))
#define SPI_DATE_V  0xFFFFFFF
#define SPI_DATE_S  0


#ifdef __cplusplus
}
#endif



#endif /*_SOC_SPI_REG_H_ */

