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
#ifndef __SPI_REG_H__
#define __SPI_REG_H__


#include "soc.h"
#define REG_SPI_BASE(i)     (DR_REG_SPI1_BASE + (((i)>1) ? (((i)* 0x1000) + 0x20000) : (((~(i)) & 1)* 0x1000 )))

#define SPI_CMD_REG(i)          (REG_SPI_BASE(i) + 0x0)
/* SPI_FLASH_READ:R/W；位位置：[31]；默认值：1’b0；*/
/*description:读取闪存启用。设置位时，将触发读取闪存操作。操作完成后，该位将被清除。1： 启用0：禁用。*/
#define SPI_FLASH_READ  (BIT(31))
#define SPI_FLASH_READ_M  (BIT(31))
#define SPI_FLASH_READ_V  0x1
#define SPI_FLASH_READ_S  31
/* SPI_FLASH_WREN：R/W；位位置：[30]；默认值：1’b0；*/
/*description:写入闪存启用。设置位时，将发送写入启用命令。操作完成后，该位将被清除。1： 启用0：禁用。*/
#define SPI_FLASH_WREN  (BIT(30))
#define SPI_FLASH_WREN_M  (BIT(30))
#define SPI_FLASH_WREN_V  0x1
#define SPI_FLASH_WREN_S  30
/* SPI_FLASH_WRDI:R/W；位位置：[29]；默认值：1’b0；*/
/*description:写入闪存禁用。设置位时将发送写禁用命令。操作完成后，该位将被清除。1： 启用0：禁用。*/
#define SPI_FLASH_WRDI  (BIT(29))
#define SPI_FLASH_WRDI_M  (BIT(29))
#define SPI_FLASH_WRDI_V  0x1
#define SPI_FLASH_WRDI_S  29
/* SPI_FLASH_rid:R/W；位位置：[28]；默认值：1’b0；*/
/*description:读取JEDEC ID。设置位时将发送读取ID命令。操作完成后，该位将被清除。1： 启用0：禁用。*/
#define SPI_FLASH_RDID  (BIT(28))
#define SPI_FLASH_RDID_M  (BIT(28))
#define SPI_FLASH_RDID_V  0x1
#define SPI_FLASH_RDID_S  28
/* SPI_FLASH_RDSR:R/W；位位置：[27]；默认值：1’b0；*/
/*description:读取状态寄存器-1。设置位时将触发读取状态操作。操作完成后，该位将被清除。1： 启用0：禁用。*/
#define SPI_FLASH_RDSR  (BIT(27))
#define SPI_FLASH_RDSR_M  (BIT(27))
#define SPI_FLASH_RDSR_V  0x1
#define SPI_FLASH_RDSR_S  27
/* SPI_FLASH_WRSR:R/W；位位置：[26]；默认值：1’b0；*/
/*description:写入状态寄存器启用。设置位时将触发写入状态操作。操作完成后，该位将被清除。1： 启用0：禁用。*/
#define SPI_FLASH_WRSR  (BIT(26))
#define SPI_FLASH_WRSR_M  (BIT(26))
#define SPI_FLASH_WRSR_V  0x1
#define SPI_FLASH_WRSR_S  26
/* SPI_FLASH_PP：R/W；位位置：[25]；默认值：1’b0；*/
/*description:页面程序启用（要编程的数据为1字节~256字节）。设置位时将触发页面程序操作。一旦操作完成，该位将被清除。1：启用0：禁用。*/
#define SPI_FLASH_PP  (BIT(25))
#define SPI_FLASH_PP_M  (BIT(25))
#define SPI_FLASH_PP_V  0x1
#define SPI_FLASH_PP_S  25
/* SPI_FLASH_SE:R/W；位位置：[24]；默认值：1’b0；*/
/*description:扇区擦除启用。通过SPI命令20H擦除4KB扇区。设置位时将触发扇区擦除操作。操作完成后，该位将被清除。1： 启用0：禁用。*/
#define SPI_FLASH_SE  (BIT(24))
#define SPI_FLASH_SE_M  (BIT(24))
#define SPI_FLASH_SE_V  0x1
#define SPI_FLASH_SE_S  24
/* SPI_FLASH_BE:R/W；位位置：[23]；默认值：1’b0；*/
/*description:块擦除启用。64KB块通过SPI命令D8H擦除。设置位时将触发块擦除操作。操作完成后，该位将被清除。1： 启用0：禁用。*/
#define SPI_FLASH_BE  (BIT(23))
#define SPI_FLASH_BE_M  (BIT(23))
#define SPI_FLASH_BE_V  0x1
#define SPI_FLASH_BE_S  23
/* SPI_FLASH_CE:R/W；位位置：[22]；默认值：1’b0；*/
/*description:芯片擦除启用。设置位时将触发芯片擦除操作。操作完成后，该位将被清除。1： 启用0：禁用。*/
#define SPI_FLASH_CE  (BIT(22))
#define SPI_FLASH_CE_M  (BIT(22))
#define SPI_FLASH_CE_V  0x1
#define SPI_FLASH_CE_S  22
/* SPI_FLASH_DP:R/W；位位置：[21]；默认值：1’b0；*/
/*description:驱动Flash关闭电源。设置位时将触发操作。操作完成后，该位将被清除。1： 启用0：禁用。*/
#define SPI_FLASH_DP  (BIT(21))
#define SPI_FLASH_DP_M  (BIT(21))
#define SPI_FLASH_DP_V  0x1
#define SPI_FLASH_DP_S  21
/* SPI_FLASH_RES:R/W；位位置：[20]；默认值：1’b0；*/
/*description:此位与reg_resandres位结合，将Flash从断电状态或高性能模式释放，并获取设备ID。一旦操作完成，该位将被清除。1： 启用0：禁用。*/
#define SPI_FLASH_RES  (BIT(20))
#define SPI_FLASH_RES_M  (BIT(20))
#define SPI_FLASH_RES_V  0x1
#define SPI_FLASH_RES_S  20
/* SPI_FLASH-HPM:R/W；位位置：[19]；默认值：1’b0；*/
/*description:将Flash驱动到高性能模式。操作完成后，该位将被清除。1： 启用0：禁用。*/
#define SPI_FLASH_HPM  (BIT(19))
#define SPI_FLASH_HPM_M  (BIT(19))
#define SPI_FLASH_HPM_V  0x1
#define SPI_FLASH_HPM_S  19
/* SPI_USR:R/W；位位置：[18]；默认值：1’b0；*/
/*description:用户定义命令启用。设置位时将触发操作。操作完成后，该位将被清除。1： 启用0：禁用。*/
#define SPI_USR  (BIT(18))
#define SPI_USR_M  (BIT(18))
#define SPI_USR_V  0x1
#define SPI_USR_S  18
/* SPI_FLASH_PES:R/W；位位置：[17]；默认值：1’b0；*/
/*描述：程序擦除暂停位程序擦除暂停操作将在设置位时触发。操作完成后，该位将被清除。1： 启用0：禁用。*/
#define SPI_FLASH_PES  (BIT(17))
#define SPI_FLASH_PES_M  (BIT(17))
#define SPI_FLASH_PES_V  0x1
#define SPI_FLASH_PES_S  17
/* SPI_FLASH_PER:R/W；位位置：[16]；默认值：1’b0；*/
/*描述：程序擦除恢复位程序擦除暂停操作将在设置位时触发。操作完成后，该位将被清除。1： 启用0：禁用。*/
#define SPI_FLASH_PER  (BIT(16))
#define SPI_FLASH_PER_M  (BIT(16))
#define SPI_FLASH_PER_V  0x1
#define SPI_FLASH_PER_S  16

#define SPI_ADDR_REG(i)          (REG_SPI_BASE(i) + 0x4)
//CSV实际上是错误的。它表示该寄存器的低8位被保留。这不是真的，
//所有32位SPI_ ADDR_。

#define SPI_CTRL_REG(i)          (REG_SPI_BASE(i) + 0x8)
/* SPI_WR_BIT_ORDER:R/W；位位置：[26]；默认值：1’b0；*/
/*描述：在命令地址写入数据（MOSI）阶段1:LSB第一个0:MSB第一个*/
#define SPI_WR_BIT_ORDER  (BIT(26))
#define SPI_WR_BIT_ORDER_M  (BIT(26))
#define SPI_WR_BIT_ORDER_V  0x1
#define SPI_WR_BIT_ORDER_S  26
/* SPI_RD_BIT_ORDER:R/W；位位置：[25]；默认值：1’b0；*/
/*描述：在读取数据（MISO）阶段1:LSB优先0:MSB优先*/
#define SPI_RD_BIT_ORDER  (BIT(25))
#define SPI_RD_BIT_ORDER_M  (BIT(25))
#define SPI_RD_BIT_ORDER_V  0x1
#define SPI_RD_BIT_ORDER_S  25
/* SPI_FREAD_QIO:R/W；位位置：[24]；默认值：1’b0；*/
/*描述：在读取操作中，地址阶段和读取数据阶段应用4个信号。1： 启用0：禁用。*/
#define SPI_FREAD_QIO  (BIT(24))
#define SPI_FREAD_QIO_M  (BIT(24))
#define SPI_FREAD_QIO_V  0x1
#define SPI_FREAD_QIO_S  24
/* SPI_FREAD_DIO:R/W；位位置：[23]；默认值：1’b0；*/
/*描述：在读取操作中，地址阶段和读取数据阶段应用2个信号。1： 启用0：禁用。*/
#define SPI_FREAD_DIO  (BIT(23))
#define SPI_FREAD_DIO_M  (BIT(23))
#define SPI_FREAD_DIO_V  0x1
#define SPI_FREAD_DIO_S  23
/* SPI_wrsr2b:R/W；位位置：[22]；默认值：1’b0；*/
/*描述：设置状态寄存器时，两个字节的数据将写入状态寄存器。1： 启用0：禁用。*/
#define SPI_WRSR_2B  (BIT(22))
#define SPI_WRSR_2B_M  (BIT(22))
#define SPI_WRSR_2B_V  0x1
#define SPI_WRSR_2B_S  22
/* SPI_WP_REG:R/W；位位置：[21]；默认值：1’b1；*/
/*description:SPI空闲时写保护信号输出。1： 输出高0：输出低。*/
#define SPI_WP_REG  (BIT(21))
#define SPI_WP_REG_M  (BIT(21))
#define SPI_WP_REG_V  0x1
#define SPI_WP_REG_S  21
/* SPI_FREAD_QUAD:R/W；位位置：[20]；默认值：1’b0；*/
/*描述：在读取操作中，读取数据阶段应用4个信号。1： 启用0：禁用。*/
#define SPI_FREAD_QUAD  (BIT(20))
#define SPI_FREAD_QUAD_M  (BIT(20))
#define SPI_FREAD_QUAD_V  0x1
#define SPI_FREAD_QUAD_S  20
/* SPI_RESANDRES:R/W；位位置：[15]；默认值：1’b1；*/
/*description:设备ID被读出到SPI_RD_STATUS寄存器，该位与SPI_flash_res位组合。1： 启用0：禁用。*/
#define SPI_RESANDRES  (BIT(15))
#define SPI_RESANDRES_M  (BIT(15))
#define SPI_RESANDRES_V  0x1
#define SPI_RESANDRES_S  15
/* SPI_FREAD_DUAL:R/W；位位置：[14]；默认值：1’b0；*/
/*描述：在读取操作中，读取数据阶段应用2个信号。1： 启用0：禁用。*/
#define SPI_FREAD_DUAL  (BIT(14))
#define SPI_FREAD_DUAL_M  (BIT(14))
#define SPI_FREAD_DUAL_V  0x1
#define SPI_FREAD_DUAL_S  14
/* SPI_FASTRD_MODE：R/W；位位置：[13]；默认值：1’b1；*/
/*description:此位启用位：spi_fread_qio spi_fread_dio spi_fread_6out和spi_fread_dout。1： 启用0：禁用。*/
#define SPI_FASTRD_MODE  (BIT(13))
#define SPI_FASTRD_MODE_M  (BIT(13))
#define SPI_FASTRD_MODE_V  0x1
#define SPI_FASTRD_MODE_S  13
/* SPI_WAIT_FLASH_inidle_EN:R/W；位位置：[12]；默认值：1’b0；*/
/*描述：当程序闪存或擦除闪存时，等待闪存空闲。1： 启用0：禁用。*/
#define SPI_WAIT_FLASH_IDLE_EN  (BIT(12))
#define SPI_WAIT_FLASH_IDLE_EN_M  (BIT(12))
#define SPI_WAIT_FLASH_IDLE_EN_V  0x1
#define SPI_WAIT_FLASH_IDLE_EN_S  12
/* SPI_TX_CRC_EN:R/W；位位置：[11]；默认值：1’b0；*/
/*description:对于SPI1，在将加密数据写入闪存时启用crc32。1： 启用0:禁用*/
#define SPI_TX_CRC_EN  (BIT(11))
#define SPI_TX_CRC_EN_M  (BIT(11))
#define SPI_TX_CRC_EN_V  0x1
#define SPI_TX_CRC_EN_S  11
/* SPI_FCS_CRC_EN:R/W；位位置：[10]；默认值：1’b1；*/
/*description:对于SPI1，在将加密数据写入闪存之前初始化crc32模块。低激活。*/
#define SPI_FCS_CRC_EN  (BIT(10))
#define SPI_FCS_CRC_EN_M  (BIT(10))
#define SPI_FCS_CRC_EN_V  0x1
#define SPI_FCS_CRC_EN_S  10

#define SPI_CTRL1_REG(i)          (REG_SPI_BASE(i) + 0xC)
/* SPI_CS_HOLD_DELAY：R/W；位位置：[31:28]；默认值：4'h5；*/
/*描述：SPI cs信号被SPI时钟周期延迟*/
#define SPI_CS_HOLD_DELAY  0x0000000F
#define SPI_CS_HOLD_DELAY_M  ((SPI_CS_HOLD_DELAY_V)<<(SPI_CS_HOLD_DELAY_S))
#define SPI_CS_HOLD_DELAY_V  0xF
#define SPI_CS_HOLD_DELAY_S  28
/* SPI_CS_HOLD_DELAY_RES:R/W；比特位置：[27:16]；默认值：12'fff；*/
/*description:当spi时钟启用恢复闪存时，恢复闪存的延迟周期。*/
#define SPI_CS_HOLD_DELAY_RES  0x00000FFF
#define SPI_CS_HOLD_DELAY_RES_M  ((SPI_CS_HOLD_DELAY_RES_V)<<(SPI_CS_HOLD_DELAY_RES_S))
#define SPI_CS_HOLD_DELAY_RES_V  0xFFF
#define SPI_CS_HOLD_DELAY_RES_S  16

#define SPI_RD_STATUS_REG(i)          (REG_SPI_BASE(i) + 0x10)
/* SPI_STATUS_EXT:R/W；位位置：[31:24]；默认值：8'00；*/
/*description:在从属模式下，它是主机读取的状态。*/
#define SPI_STATUS_EXT  0x000000FF
#define SPI_STATUS_EXT_M  ((SPI_STATUS_EXT_V)<<(SPI_STATUS_EXT_S))
#define SPI_STATUS_EXT_V  0xFF
#define SPI_STATUS_EXT_S  24
/* SPI_WB_MODE：R/W；比特位置：[23:16]；默认值：8'00；*/
/*description:快速读取模式中的模式位，它与spi_fastrd_Mode位组合。*/
#define SPI_WB_MODE  0x000000FF
#define SPI_WB_MODE_M  ((SPI_WB_MODE_V)<<(SPI_WB_MODE_S))
#define SPI_WB_MODE_V  0xFF
#define SPI_WB_MODE_S  16
/* SPI_STATUS:R/W；比特位置：[15:0]；默认值：16'b0；*/
/*description:在从属模式下，它是主机读取的状态。*/
#define SPI_STATUS  0x0000FFFF
#define SPI_STATUS_M  ((SPI_STATUS_V)<<(SPI_STATUS_S))
#define SPI_STATUS_V  0xFFFF
#define SPI_STATUS_S  0

#define SPI_CTRL2_REG(i)          (REG_SPI_BASE(i) + 0x14)
/* SPI_CS_DELAY_NUM:R/W；位位置：[31:28]；默认值：4'0；*/
/*描述：spi_cs信号被系统时钟周期延迟*/
#define SPI_CS_DELAY_NUM  0x0000000F
#define SPI_CS_DELAY_NUM_M  ((SPI_CS_DELAY_NUM_V)<<(SPI_CS_DELAY_NUM_S))
#define SPI_CS_DELAY_NUM_V  0xF
#define SPI_CS_DELAY_NUM_S  28
/* SPI_CS_DELAY_MODE：R/W；位位置：[27:26]；默认值：2'h0；*/
/*描述：spi_cs信号延迟spi_clk。0：零1：如果spi_ck_out_edge或spi_ck_iedge设置为1延迟半个周期，否则延迟一个周期2：如果spi_ck_out-edge或spi_ck_iedge设置为1，则延迟一个循环，否则延迟半个循环3：延迟一个*/
#define SPI_CS_DELAY_MODE  0x00000003
#define SPI_CS_DELAY_MODE_M  ((SPI_CS_DELAY_MODE_V)<<(SPI_CS_DELAY_MODE_S))
#define SPI_CS_DELAY_MODE_V  0x3
#define SPI_CS_DELAY_MODE_S  26
/* SPI_MOSI_DELAY_NUM:R/W；位位置：[25:23]；默认值：3'h0；*/
/*描述：MOSI信号被系统时钟周期延迟*/
#define SPI_MOSI_DELAY_NUM  0x00000007
#define SPI_MOSI_DELAY_NUM_M  ((SPI_MOSI_DELAY_NUM_V)<<(SPI_MOSI_DELAY_NUM_S))
#define SPI_MOSI_DELAY_NUM_V  0x7
#define SPI_MOSI_DELAY_NUM_S  23
/* SPI_MOSI_DELAY_MODE:R/W；比特位置：[22:21]；默认值：2'h0；*/
/*描述：MOSI信号延迟spi_clk。0：零1：如果spi_ck_out_edge或spi_ck_iedge设置为1延迟半个周期，否则延迟一个周期2：如果spi_ck_out-edge或spi_ck_iedge设置为1，否则延迟半个循环3：延迟一个循环*/
#define SPI_MOSI_DELAY_MODE  0x00000003
#define SPI_MOSI_DELAY_MODE_M  ((SPI_MOSI_DELAY_MODE_V)<<(SPI_MOSI_DELAY_MODE_S))
#define SPI_MOSI_DELAY_MODE_V  0x3
#define SPI_MOSI_DELAY_MODE_S  21
/* SPI_MISO_DELAY_NUM:R/W；比特位置：[20:18]；默认值：3'h0；*/
/*描述：MISO信号被系统时钟周期延迟*/
#define SPI_MISO_DELAY_NUM  0x00000007
#define SPI_MISO_DELAY_NUM_M  ((SPI_MISO_DELAY_NUM_V)<<(SPI_MISO_DELAY_NUM_S))
#define SPI_MISO_DELAY_NUM_V  0x7
#define SPI_MISO_DELAY_NUM_S  18
/* SPI_MISO_DELAY_MODE：R/W；比特位置：[17:16]；默认值：2'h0；*/
/*描述：MISO信号延迟spi_clk。0：零1：如果spi_ck_out_edge或spi_ck_iedge设置为1延迟半个周期，否则延迟一个周期2：如果spi_ck_out-edge或spi_ck_iedge设置为1，否则延迟半个循环3：延迟一个循环*/
#define SPI_MISO_DELAY_MODE  0x00000003
#define SPI_MISO_DELAY_MODE_M  ((SPI_MISO_DELAY_MODE_V)<<(SPI_MISO_DELAY_MODE_S))
#define SPI_MISO_DELAY_MODE_V  0x3
#define SPI_MISO_DELAY_MODE_S  16
/* SPI_CK_OUT_HIGH_MODE：R/W；比特位置：[15:12]；默认值：4'0；*/
/*描述：当值大于8时，修改spi时钟占空比，这些位与spi_clkcnt_N位和spi_clkcnt_H位组合。*/
#define SPI_CK_OUT_HIGH_MODE  0x0000000F
#define SPI_CK_OUT_HIGH_MODE_M  ((SPI_CK_OUT_HIGH_MODE_V)<<(SPI_CK_OUT_HIGH_MODE_S))
#define SPI_CK_OUT_HIGH_MODE_V  0xF
#define SPI_CK_OUT_HIGH_MODE_S  12
/* SPI_CK_OUT_LOW_MODE：R/W；位位置：[11:8]；默认值：4'0；*/
/*描述：当值大于8时，修改spi时钟占空比，这些位与spi_clkcnt_N位和spi_clkcnt_L位组合。*/
#define SPI_CK_OUT_LOW_MODE  0x0000000F
#define SPI_CK_OUT_LOW_MODE_M  ((SPI_CK_OUT_LOW_MODE_V)<<(SPI_CK_OUT_LOW_MODE_S))
#define SPI_CK_OUT_LOW_MODE_V  0xF
#define SPI_CK_OUT_LOW_MODE_S  8
/* SPI_HOLD_TIME:R/W；位位置：[7:4]；默认值：4'h1；*/
/*描述：通过spi时钟延迟cs引脚的周期，该位与spicshold位组合。*/
#define SPI_HOLD_TIME  0x0000000F
#define SPI_HOLD_TIME_M  ((SPI_HOLD_TIME_V)<<(SPI_HOLD_TIME_S))
#define SPI_HOLD_TIME_V  0xF
#define SPI_HOLD_TIME_S  4
/* SPI_SETUP_TIME:R/W；位位置：[3:0]；默认值：4'h1；*/
/*描述：（周期-1）通过spi时钟进行“准备”阶段，该位与spicssetup位组合。*/
#define SPI_SETUP_TIME  0x0000000F
#define SPI_SETUP_TIME_M  ((SPI_SETUP_TIME_V)<<(SPI_SETUP_TIME_S))
#define SPI_SETUP_TIME_V  0xF
#define SPI_SETUP_TIME_S  0

#define SPI_CLOCK_REG(i)          (REG_SPI_BASE(i) + 0x18)
/* SPI_CLK_EQU_SYSCLK:R/W；位位置：[31]；默认值：1’b1；*/
/*description:在主模式1中：spi_clk与系统0相等：spi_clk与系统时钟分开。*/
#define SPI_CLK_EQU_SYSCLK  (BIT(31))
#define SPI_CLK_EQU_SYSCLK_M  (BIT(31))
#define SPI_CLK_EQU_SYSCLK_V  0x1
#define SPI_CLK_EQU_SYSCLK_S  31
/* SPI_CLKDIV_PRE:R/W；比特位置：[30:18]；默认值：13'b0；*/
/*description:在主模式下，它是spi_clk的预除法器。*/
#define SPI_CLKDIV_PRE  0x00001FFF
#define SPI_CLKDIV_PRE_M  ((SPI_CLKDIV_PRE_V)<<(SPI_CLKDIV_PRE_S))
#define SPI_CLKDIV_PRE_V  0x1FFF
#define SPI_CLKDIV_PRE_S  18
/* SPI_CLKCNT_N:R/W；比特位置：[17:12]；默认值：6'h3；*/
/*description:在主模式下，它是spi_clk的除法器。因此spi_clk频率为系统/（spi_clkdiv_pre+1）/（spi_clkcnt_N+1）*/
#define SPI_CLKCNT_N  0x0000003F
#define SPI_CLKCNT_N_M  ((SPI_CLKCNT_N_V)<<(SPI_CLKCNT_N_S))
#define SPI_CLKCNT_N_V  0x3F
#define SPI_CLKCNT_N_S  12
/* SPI_CLKCNT_H:R/W；位位置：[11:6]；默认值：6'h1；*/
/*description:在主模式下，它必须是floor（（spi_clkcnt_N+1）/2-1）。在从属模式下，必须为0。*/
#define SPI_CLKCNT_H  0x0000003F
#define SPI_CLKCNT_H_M  ((SPI_CLKCNT_H_V)<<(SPI_CLKCNT_H_S))
#define SPI_CLKCNT_H_V  0x3F
#define SPI_CLKCNT_H_S  6
/* SPI_CLKCNT_L:R/W；比特位置：[5:0]；默认值：6'h3；*/
/*description:在主模式下，它必须等于spi_clkcnt_N。在从属模式下，必须为0。*/
#define SPI_CLKCNT_L  0x0000003F
#define SPI_CLKCNT_L_M  ((SPI_CLKCNT_L_V)<<(SPI_CLKCNT_L_S))
#define SPI_CLKCNT_L_V  0x3F
#define SPI_CLKCNT_L_S  0

#define SPI_USER_REG(i)          (REG_SPI_BASE(i) + 0x1C)
/* SPI_USR_COMMAND：R/W；位位置：[31]；默认值：1’b1；*/
/*description:此位启用操作的命令阶段。*/
#define SPI_USR_COMMAND  (BIT(31))
#define SPI_USR_COMMAND_M  (BIT(31))
#define SPI_USR_COMMAND_V  0x1
#define SPI_USR_COMMAND_S  31
/* SPI_USR_ADDR:R/W；位位置：[30]；默认值：1’b0；*/
/*description:此位启用操作的地址阶段。*/
#define SPI_USR_ADDR  (BIT(30))
#define SPI_USR_ADDR_M  (BIT(30))
#define SPI_USR_ADDR_V  0x1
#define SPI_USR_ADDR_S  30
/* SPI_USR_DUMMY:R/W；位位置：[29]；默认值：1’b0；*/
/*description:此位启用操作的虚拟阶段。*/
#define SPI_USR_DUMMY  (BIT(29))
#define SPI_USR_DUMMY_M  (BIT(29))
#define SPI_USR_DUMMY_V  0x1
#define SPI_USR_DUMMY_S  29
/* SPI_USR_MISO:R/W；位位置：[28]；默认值：1’b0；*/
/*description:此位启用操作的读取数据阶段。*/
#define SPI_USR_MISO  (BIT(28))
#define SPI_USR_MISO_M  (BIT(28))
#define SPI_USR_MISO_V  0x1
#define SPI_USR_MISO_S  28
/* SPI_USR_MOSI:R/W；位位置：[27]；默认值：1’b0；*/
/*description:此位启用操作的写入数据阶段。*/
#define SPI_USR_MOSI  (BIT(27))
#define SPI_USR_MOSI_M  (BIT(27))
#define SPI_USR_MOSI_V  0x1
#define SPI_USR_MOSI_S  27
/* SPI_USR_dumm_IDLE:R/W；位位置：[26]；默认值：1’b0；*/
/*描述：当位被启用时，spi时钟在虚拟阶段被禁用。*/
#define SPI_USR_DUMMY_IDLE  (BIT(26))
#define SPI_USR_DUMMY_IDLE_M  (BIT(26))
#define SPI_USR_DUMMY_IDLE_V  0x1
#define SPI_USR_DUMMY_IDLE_S  26
/* SPI_USR_MOSI-HIGHPART:R/W；位位置：[25]；默认值：1’b0；*/
/*描述：写入数据阶段仅访问缓冲区的高部分spiw8～spiw15。1：启用0：禁用。*/
#define SPI_USR_MOSI_HIGHPART  (BIT(25))
#define SPI_USR_MOSI_HIGHPART_M  (BIT(25))
#define SPI_USR_MOSI_HIGHPART_V  0x1
#define SPI_USR_MOSI_HIGHPART_S  25
/* SPI_USR_MISO_HIGHPART:R/W；位位置：[24]；默认值：1’b0；*/
/*描述：读取数据阶段仅访问缓冲区的高部分spiw8～spiw15。1：启用0：禁用。*/
#define SPI_USR_MISO_HIGHPART  (BIT(24))
#define SPI_USR_MISO_HIGHPART_M  (BIT(24))
#define SPI_USR_MISO_HIGHPART_V  0x1
#define SPI_USR_MISO_HIGHPART_S  24
/* SPI_USR_PREP_HOLD：R/W；位位置：[23]；默认值：1’b0；*/
/*描述：spi保持在准备状态，该位与spi_usr_hold_pol位组合。*/
#define SPI_USR_PREP_HOLD  (BIT(23))
#define SPI_USR_PREP_HOLD_M  (BIT(23))
#define SPI_USR_PREP_HOLD_V  0x1
#define SPI_USR_PREP_HOLD_S  23
/* SPI_USR_CMD_HOLD：R/W；位位置：[22]；默认值：1’b0；*/
/*描述：spi保持在命令状态，该位与spi_usr_hold_pol位组合。*/
#define SPI_USR_CMD_HOLD  (BIT(22))
#define SPI_USR_CMD_HOLD_M  (BIT(22))
#define SPI_USR_CMD_HOLD_V  0x1
#define SPI_USR_CMD_HOLD_S  22
/* SPI_USR_ADDR_HOLD:R/W；位位置：[21]；默认值：1’b0；*/
/*描述：spi保持在与spi_usr_hold_pol位组合的地址状态。*/
#define SPI_USR_ADDR_HOLD  (BIT(21))
#define SPI_USR_ADDR_HOLD_M  (BIT(21))
#define SPI_USR_ADDR_HOLD_V  0x1
#define SPI_USR_ADDR_HOLD_S  21
/* SPI_USR_DUMMY_HOLD:R/W；位位置：[20]；默认值：1’b0；*/
/*描述：spi保持在与spi_usr_hold_pol位组合的伪状态。*/
#define SPI_USR_DUMMY_HOLD  (BIT(20))
#define SPI_USR_DUMMY_HOLD_M  (BIT(20))
#define SPI_USR_DUMMY_HOLD_V  0x1
#define SPI_USR_DUMMY_HOLD_S  20
/* SPI_USR_DIN_HOLD:R/W；位位置：[19]；默认值：1’b0；*/
/*描述：spi保持在与spiusr_hold_pol位组合的数据状态。*/
#define SPI_USR_DIN_HOLD  (BIT(19))
#define SPI_USR_DIN_HOLD_M  (BIT(19))
#define SPI_USR_DIN_HOLD_V  0x1
#define SPI_USR_DIN_HOLD_S  19
/* SPI_USR_DOUT_HOLD:R/W；位位置：[18]；默认值：1’b0；*/
/*描述：spi保持在数据输出状态，该位与spiusr_hold_pol位组合。*/
#define SPI_USR_DOUT_HOLD  (BIT(18))
#define SPI_USR_DOUT_HOLD_M  (BIT(18))
#define SPI_USR_DOUT_HOLD_V  0x1
#define SPI_USR_DOUT_HOLD_S  18
/* SPI_USR_HOLD_POL:R/W；位位置：[17]；默认值：1’b0；*/
/*描述：它与保持位相结合，用于设置spi保持线的极性1：当spi保持行为高时，spi将保持0：当spi保持行为低时，spi保持*/
#define SPI_USR_HOLD_POL  (BIT(17))
#define SPI_USR_HOLD_POL_M  (BIT(17))
#define SPI_USR_HOLD_POL_V  0x1
#define SPI_USR_HOLD_POL_S  17
/* SPI_SIO:R/W；位位置：[16]；默认值：1’b0；*/
/*description:设置该位以启用3线半双工通信mosi和miso信号共享同一引脚。1： 启用0：禁用。*/
#define SPI_SIO  (BIT(16))
#define SPI_SIO_M  (BIT(16))
#define SPI_SIO_V  0x1
#define SPI_SIO_S  16
/* SPI_FWRITE_QIO:R/W；位位置：[15]；默认值：1’b0；*/
/*描述：在写入操作中，地址阶段和读取数据阶段应用4个信号。*/
#define SPI_FWRITE_QIO  (BIT(15))
#define SPI_FWRITE_QIO_M  (BIT(15))
#define SPI_FWRITE_QIO_V  0x1
#define SPI_FWRITE_QIO_S  15
/* SPI_FWRITE_DIO:R/W；位位置：[14]；默认值：1’b0；*/
/*描述：在写入操作中，地址阶段和读取数据阶段应用2个信号。*/
#define SPI_FWRITE_DIO  (BIT(14))
#define SPI_FWRITE_DIO_M  (BIT(14))
#define SPI_FWRITE_DIO_V  0x1
#define SPI_FWRITE_DIO_S  14
/* SPI_FWRITE_QUAD:R/W；位位置：[13]；默认值：1’b0；*/
/*描述：在写入操作中，读取数据阶段应用4个信号*/
#define SPI_FWRITE_QUAD  (BIT(13))
#define SPI_FWRITE_QUAD_M  (BIT(13))
#define SPI_FWRITE_QUAD_V  0x1
#define SPI_FWRITE_QUAD_S  13
/* SPI_FWRITE_DUAL:R/W；位位置：[12]；默认值：1’b0；*/
/*描述：在写入操作中，读取数据阶段应用2个信号*/
#define SPI_FWRITE_DUAL  (BIT(12))
#define SPI_FWRITE_DUAL_M  (BIT(12))
#define SPI_FWRITE_DUAL_V  0x1
#define SPI_FWRITE_DUAL_S  12
/* SPI_WR_BYTE_ORDER:R/W；位位置：[11]；默认值：1’b0；*/
/*description:在命令地址写入数据（MOSI）阶段1:big endian 0:litte_endian*/
#define SPI_WR_BYTE_ORDER  (BIT(11))
#define SPI_WR_BYTE_ORDER_M  (BIT(11))
#define SPI_WR_BYTE_ORDER_V  0x1
#define SPI_WR_BYTE_ORDER_S  11
/* SPI_RD_BYTE_ORDER:R/W；位位置：[10]；默认值：1’b0；*/
/*description:在读取数据（MISO）阶段1:big endian 0:little_endian*/
#define SPI_RD_BYTE_ORDER  (BIT(10))
#define SPI_RD_BYTE_ORDER_M  (BIT(10))
#define SPI_RD_BYTE_ORDER_V  0x1
#define SPI_RD_BYTE_ORDER_S  10
/* SPI_CK_OUT_EDGE：R/W；位位置：[7]；默认值：1’b0；*/
/*描述：该位与spi_mosidelaymode位组合以设置mosi信号延迟模式。*/
#define SPI_CK_OUT_EDGE  (BIT(7))
#define SPI_CK_OUT_EDGE_M  (BIT(7))
#define SPI_CK_OUT_EDGE_V  0x1
#define SPI_CK_OUT_EDGE_S  7
/* SPI_CK_iedge:R/W；位位置：[6]；默认值：1’b1；*/
/*description:在从属模式下，位与主模式下的spi_ck_out_edge相同。它与spi_miso_delay_mode位组合。*/
#define SPI_CK_I_EDGE  (BIT(6))
#define SPI_CK_I_EDGE_M  (BIT(6))
#define SPI_CK_I_EDGE_V  0x1
#define SPI_CK_I_EDGE_S  6
/* SPI_CS_SETUP:R/W；位位置：[5]；默认值：1’b0；*/
/*描述：当spi处于“准备”阶段时，启用spi cs。1： 启用0：禁用。*/
#define SPI_CS_SETUP  (BIT(5))
#define SPI_CS_SETUP_M  (BIT(5))
#define SPI_CS_SETUP_V  0x1
#define SPI_CS_SETUP_S  5
/* SPI_CS_HOLD:R/W；位位置：[4]；默认值：1’b0；*/
/*描述：当spi处于“完成”阶段时，spi cs保持低。1： 启用0：禁用。*/
#define SPI_CS_HOLD  (BIT(4))
#define SPI_CS_HOLD_M  (BIT(4))
#define SPI_CS_HOLD_V  0x1
#define SPI_CS_HOLD_S  4
/* SPI_DOUTDIN:R/W；位位置：[0]；默认值：1’b0；*/
/*description:设置位以启用全双工通信。1： 启用0：禁用。*/
#define SPI_DOUTDIN  (BIT(0))
#define SPI_DOUTDIN_M  (BIT(0))
#define SPI_DOUTDIN_V  0x1
#define SPI_DOUTDIN_S  0

#define SPI_USER1_REG(i)          (REG_SPI_BASE(i) + 0x20)
/* SPI_USR_ADDR_title：RO；位位置：[31:26]；默认值：6'd23；*/
/*description:地址相位的长度（以位为单位）。寄存器值应为（bit_num-1）。*/
#define SPI_USR_ADDR_BITLEN  0x0000003F
#define SPI_USR_ADDR_BITLEN_M  ((SPI_USR_ADDR_BITLEN_V)<<(SPI_USR_ADDR_BITLEN_S))
#define SPI_USR_ADDR_BITLEN_V  0x3F
#define SPI_USR_ADDR_BITLEN_S  26
/* SPI_USR_DUMMY_CYCLELEN:R/W；位位置：[7:0]；默认值：8'd7；*/
/*description:虚拟相位的spi_clk周期长度。寄存器值应为（cycle_num-1）。*/
#define SPI_USR_DUMMY_CYCLELEN  0x000000FF
#define SPI_USR_DUMMY_CYCLELEN_M  ((SPI_USR_DUMMY_CYCLELEN_V)<<(SPI_USR_DUMMY_CYCLELEN_S))
#define SPI_USR_DUMMY_CYCLELEN_V  0xFF
#define SPI_USR_DUMMY_CYCLELEN_S  0

#define SPI_USER2_REG(i)          (REG_SPI_BASE(i) + 0x24)
/* SPI_USR_COMMAND_BITLEN:R/W；位位置：[31:28]；默认值：4'd7；*/
/*description:命令阶段的长度（以位为单位）。寄存器值应为（bit_num-1）*/
#define SPI_USR_COMMAND_BITLEN  0x0000000F
#define SPI_USR_COMMAND_BITLEN_M  ((SPI_USR_COMMAND_BITLEN_V)<<(SPI_USR_COMMAND_BITLEN_S))
#define SPI_USR_COMMAND_BITLEN_V  0xF
#define SPI_USR_COMMAND_BITLEN_S  28
/* SPI_USR_COMMAND_VALUE:R/W；比特位置：[15:0]；默认值：16'b0；*/
/*description:命令的值。*/
#define SPI_USR_COMMAND_VALUE  0x0000FFFF
#define SPI_USR_COMMAND_VALUE_M  ((SPI_USR_COMMAND_VALUE_V)<<(SPI_USR_COMMAND_VALUE_S))
#define SPI_USR_COMMAND_VALUE_V  0xFFFF
#define SPI_USR_COMMAND_VALUE_S  0

#define SPI_MOSI_DLEN_REG(i)          (REG_SPI_BASE(i) + 0x28)
/* SPI_USR_MOSI_ditlen:R/W；比特位置：[23:0]；默认值：24小时；*/
/*description:写入数据的长度（以位为单位）。寄存器值应为（bit_num-1）。*/
#define SPI_USR_MOSI_DBITLEN  0x00FFFFFF
#define SPI_USR_MOSI_DBITLEN_M  ((SPI_USR_MOSI_DBITLEN_V)<<(SPI_USR_MOSI_DBITLEN_S))
#define SPI_USR_MOSI_DBITLEN_V  0xFFFFFF
#define SPI_USR_MOSI_DBITLEN_S  0

#define SPI_MISO_DLEN_REG(i)          (REG_SPI_BASE(i) + 0x2C)
/* SPI_USR_MISO_DBITLEN:R/W；比特位置：[23:0]；默认值：24小时；*/
/*description:读取数据的位长度。寄存器值应为（bit_num-1）。*/
#define SPI_USR_MISO_DBITLEN  0x00FFFFFF
#define SPI_USR_MISO_DBITLEN_M  ((SPI_USR_MISO_DBITLEN_V)<<(SPI_USR_MISO_DBITLEN_S))
#define SPI_USR_MISO_DBITLEN_V  0xFFFFFF
#define SPI_USR_MISO_DBITLEN_S  0

#define SPI_SLV_WR_STATUS_REG(i)          (REG_SPI_BASE(i) + 0x30)
/* SPI_SLV_WR_ST:R/W；位位置：[31:0]；默认值：32'b0；*/
/*description:在从属模式下，该寄存器是主设备要写入的状态寄存器。在主模式中，该寄存器是64位地址条件下的较高32位。*/
#define SPI_SLV_WR_ST  0xFFFFFFFF
#define SPI_SLV_WR_ST_M  ((SPI_SLV_WR_ST_V)<<(SPI_SLV_WR_ST_S))
#define SPI_SLV_WR_ST_V  0xFFFFFFFF
#define SPI_SLV_WR_ST_S  0

#define SPI_PIN_REG(i)          (REG_SPI_BASE(i) + 0x34)
/* SPI_CS_KEEP_ACTIVE:R/W；位位置：[30]；默认值：1’b0；*/
/*描述：设置位时，spi cs线保持低电平。*/
#define SPI_CS_KEEP_ACTIVE  (BIT(30))
#define SPI_CS_KEEP_ACTIVE_M  (BIT(30))
#define SPI_CS_KEEP_ACTIVE_V  0x1
#define SPI_CS_KEEP_ACTIVE_S  30
/* SPI_CK_inidle_EDGE：R/W；位位置：[29]；默认值：1’b0；*/
/*描述：1：空闲时spi-clk线为高0：空闲时spi-clk线路为低*/
#define SPI_CK_IDLE_EDGE  (BIT(29))
#define SPI_CK_IDLE_EDGE_M  (BIT(29))
#define SPI_CK_IDLE_EDGE_V  0x1
#define SPI_CK_IDLE_EDGE_S  29
/* SPI_MASTER_CK_SEL:R/W；比特位置：[13:11]；默认值：3'b0；*/
/*描述：在主模式下，spi-cs行被启用为spi-clk，它与spi_cs_dis spi_cs1_dis spi_cs2_dis组合。*/
#define SPI_MASTER_CK_SEL  0x00000007
#define SPI_MASTER_CK_SEL_M  ((SPI_MASTER_CK_SEL_V)<<(SPI_MASTER_CK_SEL_S))
#define SPI_MASTER_CK_SEL_V  0x07
#define SPI_MASTER_CK_SEL_S  11
/* SPI_MASTER_CS_POL:R/W；位位置：[8:6]；默认值：3'b0；*/
/*描述：在主模式中，位是spi cs线的极性，值等于spi_cs^spi_master_cs_pol。*/
#define SPI_MASTER_CS_POL  0x00000007
#define SPI_MASTER_CS_POL_M  ((SPI_MASTER_CS_POL_V)<<(SPI_MASTER_CS_POL_S))
#define SPI_MASTER_CS_POL_V  0x7
#define SPI_MASTER_CS_POL_S  6
/* SPI_CK_DIS:R/W；位位置：[5]；默认值：1’b0；*/
/*描述：1:spi-clk-out禁用0:spi-clk-out启用*/
#define SPI_CK_DIS  (BIT(5))
#define SPI_CK_DIS_M  (BIT(5))
#define SPI_CK_DIS_V  0x1
#define SPI_CK_DIS_S  5
/* SPI_CS2_DIS:R/W；位位置：[2]；默认值：1’b1；*/
/*描述：SPI CS2引脚启用，1：禁用CS2，0：SPI_CS2信号来自/至CS2引脚*/
#define SPI_CS2_DIS  (BIT(2))
#define SPI_CS2_DIS_M  (BIT(2))
#define SPI_CS2_DIS_V  0x1
#define SPI_CS2_DIS_S  2
/* SPI_CS1_DIS:R/W；位位置：[1]；默认值：1’b1；*/
/*描述：SPI CS1引脚启用，1：禁用CS1，0：SPI_CS1信号来自/至CS1引脚*/
#define SPI_CS1_DIS  (BIT(1))
#define SPI_CS1_DIS_M  (BIT(1))
#define SPI_CS1_DIS_V  0x1
#define SPI_CS1_DIS_S  1
/* SPI_CS0_DIS:R/W；位位置：[0]；默认值：1’b0；*/
/*描述：SPI CS0引脚启用，1：禁用CS0，0：SPI_CS0信号来自/至CS0引脚*/
#define SPI_CS0_DIS  (BIT(0))
#define SPI_CS0_DIS_M  (BIT(0))
#define SPI_CS0_DIS_V  0x1
#define SPI_CS0_DIS_S  0

#define SPI_SLAVE_REG(i)          (REG_SPI_BASE(i) + 0x38)
/* SPI_SYNC_RESET:R/W；位位置：[31]；默认值：1’b0；*/
/*description:软件重置启用，重置spi时钟线cs线和数据线。*/
#define SPI_SYNC_RESET  (BIT(31))
#define SPI_SYNC_RESET_M  (BIT(31))
#define SPI_SYNC_RESET_V  0x1
#define SPI_SYNC_RESET_S  31
/* SPI_SLAVE_MODE：R/W；位位置：[30]；默认值：1’b0；*/
/*描述：1：从模式0：主模式。*/
#define SPI_SLAVE_MODE  (BIT(30))
#define SPI_SLAVE_MODE_M  (BIT(30))
#define SPI_SLAVE_MODE_V  0x1
#define SPI_SLAVE_MODE_S  30
/* SPI_SLV_WR_RD_BUF_EN:R/W；位位置：[29]；默认值：1’b0；*/
/*描述：在从属模式下启用写入和读取缓冲区*/
#define SPI_SLV_WR_RD_BUF_EN  (BIT(29))
#define SPI_SLV_WR_RD_BUF_EN_M  (BIT(29))
#define SPI_SLV_WR_RD_BUF_EN_V  0x1
#define SPI_SLV_WR_RD_BUF_EN_S  29
/* SPI_SLV_WR_RD_STA_EN:R/W；位位置：[28]；默认值：1’b0；*/
/*描述：在从属模式下启用写入和读取状态*/
#define SPI_SLV_WR_RD_STA_EN  (BIT(28))
#define SPI_SLV_WR_RD_STA_EN_M  (BIT(28))
#define SPI_SLV_WR_RD_STA_EN_V  0x1
#define SPI_SLV_WR_RD_STA_EN_S  28
/* SPI_SLV_CMD_DEFINE:R/W；位位置：[27]；默认值：1’b0；*/
/*描述：1：从模式命令在SPI_SLAVE3中定义。0：从模式指令固定为：1：写入状态2：写入缓冲区和3：读取缓冲区。*/
#define SPI_SLV_CMD_DEFINE  (BIT(27))
#define SPI_SLV_CMD_DEFINE_M  (BIT(27))
#define SPI_SLV_CMD_DEFINE_V  0x1
#define SPI_SLV_CMD_DEFINE_S  27
/* SPI_TRANS_CNT:RO；比特位置：[26:23]；默认值：4'b0；*/
/*description:主模式和从模式下的操作计数器。4： 读取状态*/
#define SPI_TRANS_CNT  0x0000000F
#define SPI_TRANS_CNT_M  ((SPI_TRANS_CNT_V)<<(SPI_TRANS_CNT_S))
#define SPI_TRANS_CNT_V  0xF
#define SPI_TRANS_CNT_S  23
/* SPI_SLV_LAST_STATE:RO；比特位置：[22:20]；默认值：3'b0；*/
/*description:在从属模式下，这是spi状态机的状态。*/
#define SPI_SLV_LAST_STATE  0x00000007
#define SPI_SLV_LAST_STATE_M  ((SPI_SLV_LAST_STATE_V)<<(SPI_SLV_LAST_STATE_S))
#define SPI_SLV_LAST_STATE_V  0x7
#define SPI_SLV_LAST_STATE_S  20
/* SPI_SLV_LAST_COMMAND:RO；比特位置：[19:17]；默认值：3'b0；*/
/*description:在从属模式下，它是命令的值。*/
#define SPI_SLV_LAST_COMMAND  0x00000007
#define SPI_SLV_LAST_COMMAND_M  ((SPI_SLV_LAST_COMMAND_V)<<(SPI_SLV_LAST_COMMAND_S))
#define SPI_SLV_LAST_COMMAND_V  0x7
#define SPI_SLV_LAST_COMMAND_S  17
/* SPI_CS_I_MODE：R/W；比特位置：[11:10]；默认值：2’b0；*/
/*描述：在从属模式下，该位用于同步输入spi cs信号并消除spi cs抖动。*/
#define SPI_CS_I_MODE  0x00000003
#define SPI_CS_I_MODE_M  ((SPI_CS_I_MODE_V)<<(SPI_CS_I_MODE_S))
#define SPI_CS_I_MODE_V  0x3
#define SPI_CS_I_MODE_S  10
/* SPI_INT_EN:R/W；比特位置：[9:5]；默认值：5'b1_0000；*/
/*description:以下5个源的中断启用位*/
#define SPI_INT_EN  0x0000001F
#define SPI_INT_EN_M  ((SPI_INT_EN_V)<<(SPI_INT_EN_S))
#define SPI_INT_EN_V  0x1F
#define SPI_INT_EN_S  5
/* SPI_TRANS_DONE:R/W；位位置：[4]；默认值：1’b0；*/
/*description:在主模式和从模式下完成任何操作的中断原始位。*/
#define SPI_TRANS_DONE  (BIT(4))
#define SPI_TRANS_DONE_M  (BIT(4))
#define SPI_TRANS_DONE_V  0x1
#define SPI_TRANS_DONE_S  4
/* SPI_SLV_WR_STA_DONE:R/W；位位置：[3]；默认值：1’b0；*/
/*description:用于在从属模式下完成写入状态操作的中断原始位。*/
#define SPI_SLV_WR_STA_DONE  (BIT(3))
#define SPI_SLV_WR_STA_DONE_M  (BIT(3))
#define SPI_SLV_WR_STA_DONE_V  0x1
#define SPI_SLV_WR_STA_DONE_S  3
/* SPI_SLV_RD_STA_DONE:R/W；位位置：[2]；默认值：1’b0；*/
/*description:用于在从属模式下完成读取状态操作的中断原始位。*/
#define SPI_SLV_RD_STA_DONE  (BIT(2))
#define SPI_SLV_RD_STA_DONE_M  (BIT(2))
#define SPI_SLV_RD_STA_DONE_V  0x1
#define SPI_SLV_RD_STA_DONE_S  2
/* SPI_SLV_WR_BUF_DONE:R/W；位位置：[1]；默认值：1’b0；*/
/*description:用于在从属模式下完成写缓冲操作的中断原始位。*/
#define SPI_SLV_WR_BUF_DONE  (BIT(1))
#define SPI_SLV_WR_BUF_DONE_M  (BIT(1))
#define SPI_SLV_WR_BUF_DONE_V  0x1
#define SPI_SLV_WR_BUF_DONE_S  1
/* SPI_SLV_RD_BUF_DONE:R/W；位位置：[0]；默认值：1’b0；*/
/*description:用于在从属模式下完成读缓冲操作的中断原始位。*/
#define SPI_SLV_RD_BUF_DONE  (BIT(0))
#define SPI_SLV_RD_BUF_DONE_M  (BIT(0))
#define SPI_SLV_RD_BUF_DONE_V  0x1
#define SPI_SLV_RD_BUF_DONE_S  0

#define SPI_SLAVE1_REG(i)          (REG_SPI_BASE(i) + 0x3C)
/* SPI_SLV_STATUS_BITLEN:R/W；位位置：[31:27]；默认值：5’b0；*/
/*description:在从属模式下，它是状态位的长度。*/
#define SPI_SLV_STATUS_BITLEN  0x0000001F
#define SPI_SLV_STATUS_BITLEN_M  ((SPI_SLV_STATUS_BITLEN_V)<<(SPI_SLV_STATUS_BITLEN_S))
#define SPI_SLV_STATUS_BITLEN_V  0x1F
#define SPI_SLV_STATUS_BITLEN_S  27
/* SPI_SLV_STATUS_FAST_EN:R/W；位位置：[26]；默认值：1’b0；*/
/*description:在从属模式下，启用快速读取状态。*/
#define SPI_SLV_STATUS_FAST_EN  (BIT(26))
#define SPI_SLV_STATUS_FAST_EN_M  (BIT(26))
#define SPI_SLV_STATUS_FAST_EN_V  0x1
#define SPI_SLV_STATUS_FAST_EN_S  26
/* SPI_SLV_STATUS_READBACK:R/W；位位置：[25]；默认值：1’b1；*/
/*description:从模式1：读取SPI_SLV_WR_STATUS的寄存器0：读取SPI_RD_STATUS的。*/
#define SPI_SLV_STATUS_READBACK  (BIT(25))
#define SPI_SLV_STATUS_READBACK_M  (BIT(25))
#define SPI_SLV_STATUS_READBACK_V  0x1
#define SPI_SLV_STATUS_READBACK_S  25
/* SPI_SLV_RD_ADDR_BITLEN:R/W；比特位置：[15:10]；默认值：6'0；*/
/*description:在从属模式下，它是读取缓冲区操作的地址长度（以位为单位）。寄存器值应为（bit_num-1）。*/
#define SPI_SLV_RD_ADDR_BITLEN  0x0000003F
#define SPI_SLV_RD_ADDR_BITLEN_M  ((SPI_SLV_RD_ADDR_BITLEN_V)<<(SPI_SLV_RD_ADDR_BITLEN_S))
#define SPI_SLV_RD_ADDR_BITLEN_V  0x3F
#define SPI_SLV_RD_ADDR_BITLEN_S  10
/* SPI_SLV_WR_ADDR_BITLEN:R/W；比特位置：[9:4]；默认值：6'0；*/
/*description:在从属模式下，它是写入缓冲区操作的地址长度（以位为单位）。寄存器值应为（bit_num-1）。*/
#define SPI_SLV_WR_ADDR_BITLEN  0x0000003F
#define SPI_SLV_WR_ADDR_BITLEN_M  ((SPI_SLV_WR_ADDR_BITLEN_V)<<(SPI_SLV_WR_ADDR_BITLEN_S))
#define SPI_SLV_WR_ADDR_BITLEN_V  0x3F
#define SPI_SLV_WR_ADDR_BITLEN_S  4
/* SPI_SLV_WRSTA_dumy_EN:R/W；位位置：[3]；默认值：1’b0；*/
/*description:在从属模式下，它是写入状态操作的虚拟阶段的启用位。*/
#define SPI_SLV_WRSTA_DUMMY_EN  (BIT(3))
#define SPI_SLV_WRSTA_DUMMY_EN_M  (BIT(3))
#define SPI_SLV_WRSTA_DUMMY_EN_V  0x1
#define SPI_SLV_WRSTA_DUMMY_EN_S  3
/* SPI_SLV_RDSTA_dumy_EN:R/W；位位置：[2]；默认值：1’b0；*/
/*description:在从属模式下，它是读取状态操作的虚拟阶段的启用位。*/
#define SPI_SLV_RDSTA_DUMMY_EN  (BIT(2))
#define SPI_SLV_RDSTA_DUMMY_EN_M  (BIT(2))
#define SPI_SLV_RDSTA_DUMMY_EN_V  0x1
#define SPI_SLV_RDSTA_DUMMY_EN_S  2
/* SPI_SLV_WRBUF_DUMMY_EN:R/W；位位置：[1]；默认值：1’b0；*/
/*description:在从属模式下，它是写入缓冲区操作的虚拟阶段的启用位。*/
#define SPI_SLV_WRBUF_DUMMY_EN  (BIT(1))
#define SPI_SLV_WRBUF_DUMMY_EN_M  (BIT(1))
#define SPI_SLV_WRBUF_DUMMY_EN_V  0x1
#define SPI_SLV_WRBUF_DUMMY_EN_S  1
/* SPI_SLV_RDBUF_DUMMY_EN:R/W；位位置：[0]；默认值：1’b0；*/
/*description:在从属模式下，它是读取缓冲区操作的虚拟阶段的启用位。*/
#define SPI_SLV_RDBUF_DUMMY_EN  (BIT(0))
#define SPI_SLV_RDBUF_DUMMY_EN_M  (BIT(0))
#define SPI_SLV_RDBUF_DUMMY_EN_V  0x1
#define SPI_SLV_RDBUF_DUMMY_EN_S  0

#define SPI_SLAVE2_REG(i)          (REG_SPI_BASE(i) + 0x40)
/* SPI_SLV_WRBUF_DUMMY_CYCLELEN:R/W；位位置：[31:24]；默认值：8'b0；*/
/*description:在从属模式下，它是写入缓冲区操作的虚拟阶段的spi_clk周期长度。寄存器值应为（cycle_num-1）。*/
#define SPI_SLV_WRBUF_DUMMY_CYCLELEN  0x000000FF
#define SPI_SLV_WRBUF_DUMMY_CYCLELEN_M  ((SPI_SLV_WRBUF_DUMMY_CYCLELEN_V)<<(SPI_SLV_WRBUF_DUMMY_CYCLELEN_S))
#define SPI_SLV_WRBUF_DUMMY_CYCLELEN_V  0xFF
#define SPI_SLV_WRBUF_DUMMY_CYCLELEN_S  24
/* SPI_SLV_RDBUF_DUMMY_CYCLELEN:R/W；比特位置：[23:16]；默认值：8'0；*/
/*description:在从属模式下，它是读取缓冲区操作的虚拟阶段的spi_clk周期长度。寄存器值应为（cycle_num-1）。*/
#define SPI_SLV_RDBUF_DUMMY_CYCLELEN  0x000000FF
#define SPI_SLV_RDBUF_DUMMY_CYCLELEN_M  ((SPI_SLV_RDBUF_DUMMY_CYCLELEN_V)<<(SPI_SLV_RDBUF_DUMMY_CYCLELEN_S))
#define SPI_SLV_RDBUF_DUMMY_CYCLELEN_V  0xFF
#define SPI_SLV_RDBUF_DUMMY_CYCLELEN_S  16
/* SPI_SLV_WRSTA_dumy_CYCLELEN:R/W；比特位置：[15:8]；默认值：8'0；*/
/*description:在从属模式下，它是写入状态操作的虚拟阶段的spi_clk周期长度。寄存器值应为（cycle_num-1）。*/
#define SPI_SLV_WRSTA_DUMMY_CYCLELEN  0x000000FF
#define SPI_SLV_WRSTA_DUMMY_CYCLELEN_M  ((SPI_SLV_WRSTA_DUMMY_CYCLELEN_V)<<(SPI_SLV_WRSTA_DUMMY_CYCLELEN_S))
#define SPI_SLV_WRSTA_DUMMY_CYCLELEN_V  0xFF
#define SPI_SLV_WRSTA_DUMMY_CYCLELEN_S  8
/* SPI_SLV_RDSTA_dmmy_CYCLELEN:R/W；位位置：[7:0]；默认值：8'0；*/
/*description:在从属模式下，它是读取状态操作的虚拟阶段的spi_clk周期长度。寄存器值应为（cycle_num-1）。*/
#define SPI_SLV_RDSTA_DUMMY_CYCLELEN  0x000000FF
#define SPI_SLV_RDSTA_DUMMY_CYCLELEN_M  ((SPI_SLV_RDSTA_DUMMY_CYCLELEN_V)<<(SPI_SLV_RDSTA_DUMMY_CYCLELEN_S))
#define SPI_SLV_RDSTA_DUMMY_CYCLELEN_V  0xFF
#define SPI_SLV_RDSTA_DUMMY_CYCLELEN_S  0

#define SPI_SLAVE3_REG(i)          (REG_SPI_BASE(i) + 0x44)
/* SPI_SLV_WRSTA_CMD_VALUE:R/W；位位置：[31:24]；默认值：8'b0；*/
/*description:在从属模式下，它是写入状态命令的值。*/
#define SPI_SLV_WRSTA_CMD_VALUE  0x000000FF
#define SPI_SLV_WRSTA_CMD_VALUE_M  ((SPI_SLV_WRSTA_CMD_VALUE_V)<<(SPI_SLV_WRSTA_CMD_VALUE_S))
#define SPI_SLV_WRSTA_CMD_VALUE_V  0xFF
#define SPI_SLV_WRSTA_CMD_VALUE_S  24
/* SPI_SLV_RDSTA_CMD_VALUE:R/W；比特位置：[23:16]；默认值：8'b0；*/
/*description:在从属模式下，它是读取状态命令的值。*/
#define SPI_SLV_RDSTA_CMD_VALUE  0x000000FF
#define SPI_SLV_RDSTA_CMD_VALUE_M  ((SPI_SLV_RDSTA_CMD_VALUE_V)<<(SPI_SLV_RDSTA_CMD_VALUE_S))
#define SPI_SLV_RDSTA_CMD_VALUE_V  0xFF
#define SPI_SLV_RDSTA_CMD_VALUE_S  16
/* SPI_SLV_WRBUF_CMD_VALUE:R/W；比特位置：[15:8]；默认值：8'b0；*/
/*description:在从属模式下，它是写入缓冲区命令的值。*/
#define SPI_SLV_WRBUF_CMD_VALUE  0x000000FF
#define SPI_SLV_WRBUF_CMD_VALUE_M  ((SPI_SLV_WRBUF_CMD_VALUE_V)<<(SPI_SLV_WRBUF_CMD_VALUE_S))
#define SPI_SLV_WRBUF_CMD_VALUE_V  0xFF
#define SPI_SLV_WRBUF_CMD_VALUE_S  8
/* SPI_SLV_RDBUF_CMD_VALUE:R/W；位位置：[7:0]；默认值：8'b0；*/
/*description:在从属模式下，它是读取缓冲区命令的值。*/
#define SPI_SLV_RDBUF_CMD_VALUE  0x000000FF
#define SPI_SLV_RDBUF_CMD_VALUE_M  ((SPI_SLV_RDBUF_CMD_VALUE_V)<<(SPI_SLV_RDBUF_CMD_VALUE_S))
#define SPI_SLV_RDBUF_CMD_VALUE_V  0xFF
#define SPI_SLV_RDBUF_CMD_VALUE_S  0

#define SPI_SLV_WRBUF_DLEN_REG(i)          (REG_SPI_BASE(i) + 0x48)
/* SPI_SLV_WRBUF_DBITLEN:R/W；比特位置：[23:0]；默认值：24小时；*/
/*description:在从属模式下，它是写入缓冲区操作的长度（以位为单位）。寄存器值应为（bit_num-1）。*/
#define SPI_SLV_WRBUF_DBITLEN  0x00FFFFFF
#define SPI_SLV_WRBUF_DBITLEN_M  ((SPI_SLV_WRBUF_DBITLEN_V)<<(SPI_SLV_WRBUF_DBITLEN_S))
#define SPI_SLV_WRBUF_DBITLEN_V  0xFFFFFF
#define SPI_SLV_WRBUF_DBITLEN_S  0

#define SPI_SLV_RDBUF_DLEN_REG(i)          (REG_SPI_BASE(i) + 0x4C)
/* SPI_SLV_RDBUF_DBITLEN:R/W；比特位置：[23:0]；默认值：24小时；*/
/*description:在从属模式下，它是读取缓冲区操作的位长度。寄存器值应为（bit_num-1）。*/
#define SPI_SLV_RDBUF_DBITLEN  0x00FFFFFF
#define SPI_SLV_RDBUF_DBITLEN_M  ((SPI_SLV_RDBUF_DBITLEN_V)<<(SPI_SLV_RDBUF_DBITLEN_S))
#define SPI_SLV_RDBUF_DBITLEN_V  0xFFFFFF
#define SPI_SLV_RDBUF_DBITLEN_S  0

#define SPI_CACHE_FCTRL_REG(i)          (REG_SPI_BASE(i) + 0x50)
/* SPI_CACHE_FLASH_pas_EN:R/W；位位置：[3]；默认值：1’b0；*/
/*description:对于SPI0，spi1在缓存读取闪存1之前发送suspend命令：enable 0：disable。*/
#define SPI_CACHE_FLASH_PES_EN  (BIT(3))
#define SPI_CACHE_FLASH_PES_EN_M  (BIT(3))
#define SPI_CACHE_FLASH_PES_EN_V  0x1
#define SPI_CACHE_FLASH_PES_EN_S  3
/* SPI_CACHE_FLASH_USR_CMD:R/W；位位置：[2]；默认值：1’b0；*/
/*description:对于用户定义命令1:enable0:disable的SPI0缓存读取闪存。*/
#define SPI_CACHE_FLASH_USR_CMD  (BIT(2))
#define SPI_CACHE_FLASH_USR_CMD_M  (BIT(2))
#define SPI_CACHE_FLASH_USR_CMD_V  0x1
#define SPI_CACHE_FLASH_USR_CMD_S  2
/* SPI_CACHE_USR_CMD_4BYTE:R/W；位位置：[1]；默认值：1’b0；*/
/*description:对于4字节的SPI0缓存读取闪存，命令1:enable0:disable。*/
#define SPI_CACHE_USR_CMD_4BYTE  (BIT(1))
#define SPI_CACHE_USR_CMD_4BYTE_M  (BIT(1))
#define SPI_CACHE_USR_CMD_4BYTE_V  0x1
#define SPI_CACHE_USR_CMD_4BYTE_S  1
/* SPI_CACHE_REQ_EN:R/W；位位置：[0]；默认值：1’b0；*/
/*description:对于SPI0缓存访问，启用1:启用0:禁用。*/
#define SPI_CACHE_REQ_EN  (BIT(0))
#define SPI_CACHE_REQ_EN_M  (BIT(0))
#define SPI_CACHE_REQ_EN_V  0x1
#define SPI_CACHE_REQ_EN_S  0

#define SPI_CACHE_SCTRL_REG(i)          (REG_SPI_BASE(i) + 0x54)
/* SPI_CACHE_SRAM_USR_WCMD:R/W；位位置：[28]；默认值：1’b1；*/
/*description:对于SPI0在spi-sram模式缓存中为用户定义命令写入sram*/
#define SPI_CACHE_SRAM_USR_WCMD  (BIT(28))
#define SPI_CACHE_SRAM_USR_WCMD_M  (BIT(28))
#define SPI_CACHE_SRAM_USR_WCMD_V  0x1
#define SPI_CACHE_SRAM_USR_WCMD_S  28
/* SPI_SRAM_ADDR_title：R/W；位位置：[27:22]；默认值：6'd23；*/
/*description:对于SPI0，在sram模式下，它是地址相位的位长度。寄存器值应为（bit_num-1）。*/
#define SPI_SRAM_ADDR_BITLEN  0x0000003F
#define SPI_SRAM_ADDR_BITLEN_M  ((SPI_SRAM_ADDR_BITLEN_V)<<(SPI_SRAM_ADDR_BITLEN_S))
#define SPI_SRAM_ADDR_BITLEN_V  0x3F
#define SPI_SRAM_ADDR_BITLEN_S  22
/* SPI_SRAM_DUMMY_CYCLELEN:R/W；比特位置：[21:14]；默认值：8'b1；*/
/*description:对于SPI0，在sram模式下，它是地址相位的位长度。寄存器值应为（bit_num-1）。*/
#define SPI_SRAM_DUMMY_CYCLELEN  0x000000FF
#define SPI_SRAM_DUMMY_CYCLELEN_M  ((SPI_SRAM_DUMMY_CYCLELEN_V)<<(SPI_SRAM_DUMMY_CYCLELEN_S))
#define SPI_SRAM_DUMMY_CYCLELEN_V  0xFF
#define SPI_SRAM_DUMMY_CYCLELEN_S  14
/* SPI_SRAM_BYTES_LEN:R/W；比特位置：[13:6]；默认值：8'b32；*/
/*description:对于SPI0在sram模式下，它是spi读取sram数据的字节长度。*/
#define SPI_SRAM_BYTES_LEN  0x000000FF
#define SPI_SRAM_BYTES_LEN_M  ((SPI_SRAM_BYTES_LEN_V)<<(SPI_SRAM_BYTES_LEN_S))
#define SPI_SRAM_BYTES_LEN_V  0xFF
#define SPI_SRAM_BYTES_LEN_S  6
/* SPI_CACHE_SRAM_USR_RCMD:R/W；位位置：[5]；默认值：1’b1；*/
/*description:对于SPI0，在spi-sram模式缓存中读取sram，用于用户定义命令。*/
#define SPI_CACHE_SRAM_USR_RCMD  (BIT(5))
#define SPI_CACHE_SRAM_USR_RCMD_M  (BIT(5))
#define SPI_CACHE_SRAM_USR_RCMD_V  0x1
#define SPI_CACHE_SRAM_USR_RCMD_S  5
/* SPI_USR_RD_sramdumm:R/W；位位置：[4]；默认值：1’b1；*/
/*description:对于SPI0，在spi-sram模式中，它是读取操作的虚拟阶段的启用位。*/
#define SPI_USR_RD_SRAM_DUMMY  (BIT(4))
#define SPI_USR_RD_SRAM_DUMMY_M  (BIT(4))
#define SPI_USR_RD_SRAM_DUMMY_V  0x1
#define SPI_USR_RD_SRAM_DUMMY_S  4
/* SPI_USR_WR_sramdumm:R/W；位位置：[3]；默认值：1’b0；*/
/*description:对于SPI0，在spi-sram模式中，它是写入操作的虚拟阶段的启用位。*/
#define SPI_USR_WR_SRAM_DUMMY  (BIT(3))
#define SPI_USR_WR_SRAM_DUMMY_M  (BIT(3))
#define SPI_USR_WR_SRAM_DUMMY_V  0x1
#define SPI_USR_WR_SRAM_DUMMY_S  3
/* SPI_USR_SRAM_QIO:R/W；位位置：[2]；默认值：1’b0；*/
/*description:对于SPI0在spi-sram模式下，spiquad I/O模式启用1：启用0：禁用*/
#define SPI_USR_SRAM_QIO  (BIT(2))
#define SPI_USR_SRAM_QIO_M  (BIT(2))
#define SPI_USR_SRAM_QIO_V  0x1
#define SPI_USR_SRAM_QIO_S  2
/* SPI_USR_SRAM_DIO:R/W；位位置：[1]；默认值：1’b0；*/
/*description:对于SPI0在spi-sram模式下，spi双I/O模式启用1：启用0：禁用*/
#define SPI_USR_SRAM_DIO  (BIT(1))
#define SPI_USR_SRAM_DIO_M  (BIT(1))
#define SPI_USR_SRAM_DIO_V  0x1
#define SPI_USR_SRAM_DIO_S  1

#define SPI_SRAM_CMD_REG(i)          (REG_SPI_BASE(i) + 0x58)
/* SPI_SRAM_RSTIO:R/W；位位置：[4]；默认值：1’b0；*/
/*description:用于SPI0 SRAM IO模式重置启用。当位被设置时，SRAM IO模式复位操作将被触发。一旦操作完成，该位将被清除*/
#define SPI_SRAM_RSTIO  (BIT(4))
#define SPI_SRAM_RSTIO_M  (BIT(4))
#define SPI_SRAM_RSTIO_V  0x1
#define SPI_SRAM_RSTIO_S  4
/* SPI_SRAM_QIO:R/W；位位置：[1]；默认值：1’b0；*/
/*description:对于SPI0 SRAM QIO模式启用。SRAM QIO启用命令将在设置位时发送。操作完成后，该位将被清除。*/
#define SPI_SRAM_QIO  (BIT(1))
#define SPI_SRAM_QIO_M  (BIT(1))
#define SPI_SRAM_QIO_V  0x1
#define SPI_SRAM_QIO_S  1
/* SPI_SRAM_DIO:R/W；位位置：[0]；默认值：1’b0；*/
/*description:对于SPI0 SRAM DIO模式启用。当设置位时，将发送SRAM DIO启用命令。操作完成后，该位将被清除。*/
#define SPI_SRAM_DIO  (BIT(0))
#define SPI_SRAM_DIO_M  (BIT(0))
#define SPI_SRAM_DIO_V  0x1
#define SPI_SRAM_DIO_S  0

#define SPI_SRAM_DRD_CMD_REG(i)          (REG_SPI_BASE(i) + 0x5C)
/* SPI_CACHE_SRAM_USR_RD_CMD_BITLEN:R/W；位位置：[31:28]；默认值：4'0；*/
/*description:对于SPI0，当启用缓存模式时，它是SRAM命令阶段的位长度。寄存器值应为（bit_num-1）。*/
#define SPI_CACHE_SRAM_USR_RD_CMD_BITLEN  0x0000000F
#define SPI_CACHE_SRAM_USR_RD_CMD_BITLEN_M  ((SPI_CACHE_SRAM_USR_RD_CMD_BITLEN_V)<<(SPI_CACHE_SRAM_USR_RD_CMD_BITLEN_S))
#define SPI_CACHE_SRAM_USR_RD_CMD_BITLEN_V  0xF
#define SPI_CACHE_SRAM_USR_RD_CMD_BITLEN_S  28
/* SPI_CACHE_SRAM_USR_RD_CMD_VALUE:R/W；比特位置：[15:0]；默认值：16'0；*/
/*description:对于SPI0，当启用缓存模式时，它是SRAM命令阶段的读取命令值。*/
#define SPI_CACHE_SRAM_USR_RD_CMD_VALUE  0x0000FFFF
#define SPI_CACHE_SRAM_USR_RD_CMD_VALUE_M  ((SPI_CACHE_SRAM_USR_RD_CMD_VALUE_V)<<(SPI_CACHE_SRAM_USR_RD_CMD_VALUE_S))
#define SPI_CACHE_SRAM_USR_RD_CMD_VALUE_V  0xFFFF
#define SPI_CACHE_SRAM_USR_RD_CMD_VALUE_S  0

#define SPI_SRAM_DWR_CMD_REG(i)          (REG_SPI_BASE(i) + 0x60)
/* SPI_CACHE_SRAM_USR_WR_CMD_BITLEN:R/W；位位置：[31:28]；默认值：4'0；*/
/*description:对于SPI0，当启用缓存模式时，它是SRAM命令阶段的位。寄存器值应为（bit_num-1）。*/
#define SPI_CACHE_SRAM_USR_WR_CMD_BITLEN  0x0000000F
#define SPI_CACHE_SRAM_USR_WR_CMD_BITLEN_M  ((SPI_CACHE_SRAM_USR_WR_CMD_BITLEN_V)<<(SPI_CACHE_SRAM_USR_WR_CMD_BITLEN_S))
#define SPI_CACHE_SRAM_USR_WR_CMD_BITLEN_V  0xF
#define SPI_CACHE_SRAM_USR_WR_CMD_BITLEN_S  28
/* SPI_CACHE_SRAM_USR_WR_CMD_VALUE:R/W；比特位置：[15:0]；默认值：16'0；*/
/*description:对于SPI0，当启用缓存模式时，它是SRAM命令阶段的写入命令值。*/
#define SPI_CACHE_SRAM_USR_WR_CMD_VALUE  0x0000FFFF
#define SPI_CACHE_SRAM_USR_WR_CMD_VALUE_M  ((SPI_CACHE_SRAM_USR_WR_CMD_VALUE_V)<<(SPI_CACHE_SRAM_USR_WR_CMD_VALUE_S))
#define SPI_CACHE_SRAM_USR_WR_CMD_VALUE_V  0xFFFF
#define SPI_CACHE_SRAM_USR_WR_CMD_VALUE_S  0

#define SPI_SLV_RD_BIT_REG(i)          (REG_SPI_BASE(i) + 0x64)
/* SPI_SLV_RDATA_BIT:RW；比特位置：[23:0]；默认值：24'b0；*/
/*description:在从属模式下，它是读取数据的位长度。值为长度-1。*/
#define SPI_SLV_RDATA_BIT  0x00FFFFFF
#define SPI_SLV_RDATA_BIT_M  ((SPI_SLV_RDATA_BIT_V)<<(SPI_SLV_RDATA_BIT_S))
#define SPI_SLV_RDATA_BIT_V  0xFFFFFF
#define SPI_SLV_RDATA_BIT_S  0

#define SPI_W0_REG(i)          (REG_SPI_BASE(i) + 0x80)
/* SPI_BUF0:R/W；位位置：[31:0]；默认值：32'b0；*/
/*描述：数据缓冲区*/
#define SPI_BUF0  0xFFFFFFFF
#define SPI_BUF0_M  ((SPI_BUF0_V)<<(SPI_BUF0_S))
#define SPI_BUF0_V  0xFFFFFFFF
#define SPI_BUF0_S  0

#define SPI_W1_REG(i)          (REG_SPI_BASE(i) + 0x84)
/* SPI_BUF1:R/W；位位置：[31:0]；默认值：32'b0；*/
/*描述：数据缓冲区*/
#define SPI_BUF1  0xFFFFFFFF
#define SPI_BUF1_M  ((SPI_BUF1_V)<<(SPI_BUF1_S))
#define SPI_BUF1_V  0xFFFFFFFF
#define SPI_BUF1_S  0

#define SPI_W2_REG(i)          (REG_SPI_BASE(i) + 0x88)
/* SPI_BUF2:R/W；位位置：[31:0]；默认值：32'b0；*/
/*描述：数据缓冲区*/
#define SPI_BUF2  0xFFFFFFFF
#define SPI_BUF2_M  ((SPI_BUF2_V)<<(SPI_BUF2_S))
#define SPI_BUF2_V  0xFFFFFFFF
#define SPI_BUF2_S  0

#define SPI_W3_REG(i)          (REG_SPI_BASE(i) + 0x8C)
/* SPI_BUF3:R/W；位位置：[31:0]；默认值：32'b0；*/
/*描述：数据缓冲区*/
#define SPI_BUF3  0xFFFFFFFF
#define SPI_BUF3_M  ((SPI_BUF3_V)<<(SPI_BUF3_S))
#define SPI_BUF3_V  0xFFFFFFFF
#define SPI_BUF3_S  0

#define SPI_W4_REG(i)          (REG_SPI_BASE(i) + 0x90)
/* SPI_BUF4:R/W；位位置：[31:0]；默认值：32'b0；*/
/*描述：数据缓冲区*/
#define SPI_BUF4  0xFFFFFFFF
#define SPI_BUF4_M  ((SPI_BUF4_V)<<(SPI_BUF4_S))
#define SPI_BUF4_V  0xFFFFFFFF
#define SPI_BUF4_S  0

#define SPI_W5_REG(i)          (REG_SPI_BASE(i) + 0x94)
/* SPI_BUF5:R/W；位位置：[31:0]；默认值：32'b0；*/
/*描述：数据缓冲区*/
#define SPI_BUF5  0xFFFFFFFF
#define SPI_BUF5_M  ((SPI_BUF5_V)<<(SPI_BUF5_S))
#define SPI_BUF5_V  0xFFFFFFFF
#define SPI_BUF5_S  0

#define SPI_W6_REG(i)          (REG_SPI_BASE(i) + 0x98)
/* SPI_BUF6:R/W；位位置：[31:0]；默认值：32'b0；*/
/*描述：数据缓冲区*/
#define SPI_BUF6  0xFFFFFFFF
#define SPI_BUF6_M  ((SPI_BUF6_V)<<(SPI_BUF6_S))
#define SPI_BUF6_V  0xFFFFFFFF
#define SPI_BUF6_S  0

#define SPI_W7_REG(i)          (REG_SPI_BASE(i) + 0x9C)
/* SPI_BUF7:R/W；位位置：[31:0]；默认值：32'b0；*/
/*描述：数据缓冲区*/
#define SPI_BUF7  0xFFFFFFFF
#define SPI_BUF7_M  ((SPI_BUF7_V)<<(SPI_BUF7_S))
#define SPI_BUF7_V  0xFFFFFFFF
#define SPI_BUF7_S  0

#define SPI_W8_REG(i)          (REG_SPI_BASE(i) + 0xA0)
/* SPI_BUF8:R/W；位位置：[31:0]；默认值：32'b0；*/
/*描述：数据缓冲区*/
#define SPI_BUF8  0xFFFFFFFF
#define SPI_BUF8_M  ((SPI_BUF8_V)<<(SPI_BUF8_S))
#define SPI_BUF8_V  0xFFFFFFFF
#define SPI_BUF8_S  0

#define SPI_W9_REG(i)          (REG_SPI_BASE(i) + 0xA4)
/* SPI_BUF9:R/W；位位置：[31:0]；默认值：32'b0；*/
/*描述：数据缓冲区*/
#define SPI_BUF9  0xFFFFFFFF
#define SPI_BUF9_M  ((SPI_BUF9_V)<<(SPI_BUF9_S))
#define SPI_BUF9_V  0xFFFFFFFF
#define SPI_BUF9_S  0

#define SPI_W10_REG(i)          (REG_SPI_BASE(i) + 0xA8)
/* SPI_BUF10:R/W；位位置：[31:0]；默认值：32'b0；*/
/*描述：数据缓冲区*/
#define SPI_BUF10  0xFFFFFFFF
#define SPI_BUF10_M  ((SPI_BUF10_V)<<(SPI_BUF10_S))
#define SPI_BUF10_V  0xFFFFFFFF
#define SPI_BUF10_S  0

#define SPI_W11_REG(i)          (REG_SPI_BASE(i) + 0xAC)
/* SPI_BUF11:R/W；位位置：[31:0]；默认值：32'b0；*/
/*描述：数据缓冲区*/
#define SPI_BUF11  0xFFFFFFFF
#define SPI_BUF11_M  ((SPI_BUF11_V)<<(SPI_BUF11_S))
#define SPI_BUF11_V  0xFFFFFFFF
#define SPI_BUF11_S  0

#define SPI_W12_REG(i)          (REG_SPI_BASE(i) + 0xB0)
/* SPI_BUF12:R/W；位位置：[31:0]；默认值：32'b0；*/
/*描述：数据缓冲区*/
#define SPI_BUF12  0xFFFFFFFF
#define SPI_BUF12_M  ((SPI_BUF12_V)<<(SPI_BUF12_S))
#define SPI_BUF12_V  0xFFFFFFFF
#define SPI_BUF12_S  0

#define SPI_W13_REG(i)          (REG_SPI_BASE(i) + 0xB4)
/* SPI_BUF13:R/W；位位置：[31:0]；默认值：32'b0；*/
/*描述：数据缓冲区*/
#define SPI_BUF13  0xFFFFFFFF
#define SPI_BUF13_M  ((SPI_BUF13_V)<<(SPI_BUF13_S))
#define SPI_BUF13_V  0xFFFFFFFF
#define SPI_BUF13_S  0

#define SPI_W14_REG(i)          (REG_SPI_BASE(i) + 0xB8)
/* SPI_BUF14:R/W；位位置：[31:0]；默认值：32'b0；*/
/*描述：数据缓冲区*/
#define SPI_BUF14  0xFFFFFFFF
#define SPI_BUF14_M  ((SPI_BUF14_V)<<(SPI_BUF14_S))
#define SPI_BUF14_V  0xFFFFFFFF
#define SPI_BUF14_S  0

#define SPI_W15_REG(i)          (REG_SPI_BASE(i) + 0xBC)
/* SPI_BUF15:R/W；位位置：[31:0]；默认值：32'b0；*/
/*描述：数据缓冲区*/
#define SPI_BUF15  0xFFFFFFFF
#define SPI_BUF15_M  ((SPI_BUF15_V)<<(SPI_BUF15_S))
#define SPI_BUF15_V  0xFFFFFFFF
#define SPI_BUF15_S  0

#define SPI_TX_CRC_REG(i)          (REG_SPI_BASE(i) + 0xC0)
/* SPI_TX_CRC_DATA：R/W；位位置：[31:0]；默认值：32'b0；*/
/*description:对于SPI1，256位数据的crc32值。*/
#define SPI_TX_CRC_DATA  0xFFFFFFFF
#define SPI_TX_CRC_DATA_M  ((SPI_TX_CRC_DATA_V)<<(SPI_TX_CRC_DATA_S))
#define SPI_TX_CRC_DATA_V  0xFFFFFFFF
#define SPI_TX_CRC_DATA_S  0

#define SPI_EXT0_REG(i)          (REG_SPI_BASE(i) + 0xF0)
/* SPI_T_PP_ENA:R/W；位位置：[31]；默认值：1’b1；*/
/*description:页面程序延迟启用。*/
#define SPI_T_PP_ENA  (BIT(31))
#define SPI_T_PP_ENA_M  (BIT(31))
#define SPI_T_PP_ENA_V  0x1
#define SPI_T_PP_ENA_S  31
/* SPI_T_PP_SHIFT:R/W；比特位置：[19:16]；默认值：4'd10；*/
/*描述：页面程序延迟时间偏移。*/
#define SPI_T_PP_SHIFT  0x0000000F
#define SPI_T_PP_SHIFT_M  ((SPI_T_PP_SHIFT_V)<<(SPI_T_PP_SHIFT_S))
#define SPI_T_PP_SHIFT_V  0xF
#define SPI_T_PP_SHIFT_S  16
/* SPI_T_PP_TIME:R/W；位位置：[11:0]；默认值：12'd80；*/
/*描述：按系统时钟计算的页面程序延迟时间。*/
#define SPI_T_PP_TIME  0x00000FFF
#define SPI_T_PP_TIME_M  ((SPI_T_PP_TIME_V)<<(SPI_T_PP_TIME_S))
#define SPI_T_PP_TIME_V  0xFFF
#define SPI_T_PP_TIME_S  0

#define SPI_EXT1_REG(i)          (REG_SPI_BASE(i) + 0xF4)
/* SPI_T_ERASE_ENA:R/W；位位置：[31]；默认值：1’b1；*/
/*描述：擦除闪存延迟启用。*/
#define SPI_T_ERASE_ENA  (BIT(31))
#define SPI_T_ERASE_ENA_M  (BIT(31))
#define SPI_T_ERASE_ENA_V  0x1
#define SPI_T_ERASE_ENA_S  31
/* SPI_T_ERASE_SHIFT:R/W；比特位置：[19:16]；默认值：4'd15；*/
/*描述：擦除闪存延迟时间偏移。*/
#define SPI_T_ERASE_SHIFT  0x0000000F
#define SPI_T_ERASE_SHIFT_M  ((SPI_T_ERASE_SHIFT_V)<<(SPI_T_ERASE_SHIFT_S))
#define SPI_T_ERASE_SHIFT_V  0xF
#define SPI_T_ERASE_SHIFT_S  16
/* SPI_T_ERASE_TIME:R/W；位位置：[11:0]；默认值：12'd0；*/
/*描述：通过系统时钟擦除闪存延迟时间。*/
#define SPI_T_ERASE_TIME  0x00000FFF
#define SPI_T_ERASE_TIME_M  ((SPI_T_ERASE_TIME_V)<<(SPI_T_ERASE_TIME_S))
#define SPI_T_ERASE_TIME_V  0xFFF
#define SPI_T_ERASE_TIME_S  0

#define SPI_EXT2_REG(i)          (REG_SPI_BASE(i) + 0xF8)
/* SPI_ST:RO；位位置：[2:0]；默认值：3'b0；*/
/*description:spi状态机的状态。*/
#define SPI_ST  0x00000007
#define SPI_ST_M  ((SPI_ST_V)<<(SPI_ST_S))
#define SPI_ST_V  0x7
#define SPI_ST_S  0

#define SPI_EXT3_REG(i)          (REG_SPI_BASE(i) + 0xFC)
/* SPI_INT_HOLD_ENA:R/W；位位置：[1:0]；默认值：2’b0；*/
/*描述：此寄存器用于两个SPI主机共享相同的cs时钟和数据信号。如果另一个SPI忙，则设置一个SPI的位，SPI将保持。1（3）：在“空闲”阶段保持2：在“准备”阶段保持。*/
#define SPI_INT_HOLD_ENA  0x00000003
#define SPI_INT_HOLD_ENA_M  ((SPI_INT_HOLD_ENA_V)<<(SPI_INT_HOLD_ENA_S))
#define SPI_INT_HOLD_ENA_V  0x3
#define SPI_INT_HOLD_ENA_S  0

#define SPI_DMA_CONF_REG(i)          (REG_SPI_BASE(i) + 0x100)
/* SPI_DMA_CONTINUE:R/W；位位置：[16]；默认值：1’b0；*/
/*描述：spi-dma继续tx/rx数据。*/
#define SPI_DMA_CONTINUE  (BIT(16))
#define SPI_DMA_CONTINUE_M  (BIT(16))
#define SPI_DMA_CONTINUE_V  0x1
#define SPI_DMA_CONTINUE_S  16
/* SPI_DMA_TX_STOP:R/W；位位置：[15]；默认值：1’b0；*/
/*描述：当处于continue tx/rx模式时，spidma写入数据停止。*/
#define SPI_DMA_TX_STOP  (BIT(15))
#define SPI_DMA_TX_STOP_M  (BIT(15))
#define SPI_DMA_TX_STOP_V  0x1
#define SPI_DMA_TX_STOP_S  15
/* SPI_DMA_RX_STOP:R/W；位位置：[14]；默认值：1’b0；*/
/*描述：当处于continue tx/rx模式时，spidma读取数据停止。*/
#define SPI_DMA_RX_STOP  (BIT(14))
#define SPI_DMA_RX_STOP_M  (BIT(14))
#define SPI_DMA_RX_STOP_V  0x1
#define SPI_DMA_RX_STOP_S  14
/* SPI_OUT_DATA_BURST_EN:R/W；位位置：[12]；默认值：1’b0；*/
/*描述：spidma以突发模式从内存读取数据。*/
#define SPI_OUT_DATA_BURST_EN  (BIT(12))
#define SPI_OUT_DATA_BURST_EN_M  (BIT(12))
#define SPI_OUT_DATA_BURST_EN_V  0x1
#define SPI_OUT_DATA_BURST_EN_S  12
/* SPI_INDSCR_BURST_EN:R/W；位位置：[11]；默认值：1’b0；*/
/*描述：当将数据写入内存时，读取描述符使用突发模式。*/
#define SPI_INDSCR_BURST_EN  (BIT(11))
#define SPI_INDSCR_BURST_EN_M  (BIT(11))
#define SPI_INDSCR_BURST_EN_V  0x1
#define SPI_INDSCR_BURST_EN_S  11
/* SPI_OUTDSCR_BURST_EN:R/W；位位置：[10]；默认值：1’b0；*/
/*描述：读取描述符在读取内存数据时使用突发模式。*/
#define SPI_OUTDSCR_BURST_EN  (BIT(10))
#define SPI_OUTDSCR_BURST_EN_M  (BIT(10))
#define SPI_OUTDSCR_BURST_EN_V  0x1
#define SPI_OUTDSCR_BURST_EN_S  10
/* SPI_OUT_EOF_MODE：R/W；位位置：[9]；默认值：1’b1；*/
/*描述：退出eof标志生成模式。1：当dma从fifo弹出所有数据时0：当ahb将所有数据推送到fifo时。*/
#define SPI_OUT_EOF_MODE  (BIT(9))
#define SPI_OUT_EOF_MODE_M  (BIT(9))
#define SPI_OUT_EOF_MODE_V  0x1
#define SPI_OUT_EOF_MODE_S  9
/* SPI_OUT_AUTO_werback:R/W；位位置：[8]；默认值：1’b0；*/
/*描述：当链接为空时，自动跳转到下一个。*/
#define SPI_OUT_AUTO_WRBACK  (BIT(8))
#define SPI_OUT_AUTO_WRBACK_M  (BIT(8))
#define SPI_OUT_AUTO_WRBACK_V  0x1
#define SPI_OUT_AUTO_WRBACK_S  8
/* SPI_OUT_LOOP_TEST:R/W；位位置：[7]；默认值：1’b0；*/
/*description:设置位以测试链接。*/
#define SPI_OUT_LOOP_TEST  (BIT(7))
#define SPI_OUT_LOOP_TEST_M  (BIT(7))
#define SPI_OUT_LOOP_TEST_V  0x1
#define SPI_OUT_LOOP_TEST_S  7
/* SPI_IN_LOOP_TEST:R/W；位位置：[6]；默认值：1’b0；*/
/*description:设置要在链接中测试的位。*/
#define SPI_IN_LOOP_TEST  (BIT(6))
#define SPI_IN_LOOP_TEST_M  (BIT(6))
#define SPI_IN_LOOP_TEST_V  0x1
#define SPI_IN_LOOP_TEST_S  6
/* SPI_AHBM_RST:R/W；位位置：[5]；默认值：1’b0；*/
/*描述：重置spi-dma-ahb主机。*/
#define SPI_AHBM_RST  (BIT(5))
#define SPI_AHBM_RST_M  (BIT(5))
#define SPI_AHBM_RST_V  0x1
#define SPI_AHBM_RST_S  5
/* SPI_AHBM_FIFO_RST:R/W；位位置：[4]；默认值：1’b0；*/
/*描述：重置spi-dmaahb主fifo指针。*/
#define SPI_AHBM_FIFO_RST  (BIT(4))
#define SPI_AHBM_FIFO_RST_M  (BIT(4))
#define SPI_AHBM_FIFO_RST_V  0x1
#define SPI_AHBM_FIFO_RST_S  4
/* SPI_OUT_RST:R/W；位位置：[3]；默认值：1’b0；*/
/*描述：该位用于重置dma fsm和数据fifo指针。*/
#define SPI_OUT_RST  (BIT(3))
#define SPI_OUT_RST_M  (BIT(3))
#define SPI_OUT_RST_V  0x1
#define SPI_OUT_RST_S  3
/* SPI_IN_RST:R/W；位位置：[2]；默认值：1’b0；*/
/*描述：该位用于在dma fsm和数据fifo指针中重置。*/
#define SPI_IN_RST  (BIT(2))
#define SPI_IN_RST_M  (BIT(2))
#define SPI_IN_RST_V  0x1
#define SPI_IN_RST_S  2

#define SPI_DMA_OUT_LINK_REG(i)          (REG_SPI_BASE(i) + 0x104)
/* SPI_OUTLINK_RESTART：R/W；位位置：[30]；默认值：1’b0；*/
/*description:设置要装入新outlink描述符的位。*/
#define SPI_OUTLINK_RESTART  (BIT(30))
#define SPI_OUTLINK_RESTART_M  (BIT(30))
#define SPI_OUTLINK_RESTART_V  0x1
#define SPI_OUTLINK_RESTART_S  30
/* SPI_OUTLINK_START:R/W；位位置：[29]；默认值：1’b0；*/
/*description:设置位以开始使用outlink描述符。*/
#define SPI_OUTLINK_START  (BIT(29))
#define SPI_OUTLINK_START_M  (BIT(29))
#define SPI_OUTLINK_START_V  0x1
#define SPI_OUTLINK_START_S  29
/* SPI_OUTLINK_STOP：R/W；位位置：[28]；默认值：1’b0；*/
/*description:将位设置为stop以使用outlink描述符。*/
#define SPI_OUTLINK_STOP  (BIT(28))
#define SPI_OUTLINK_STOP_M  (BIT(28))
#define SPI_OUTLINK_STOP_V  0x1
#define SPI_OUTLINK_STOP_S  28
/* SPI_OUTLINK_ADDR:R/W；比特位置：[19:0]；默认值：20'00；*/
/*description:第一个outlink描述符的地址。*/
#define SPI_OUTLINK_ADDR  0x000FFFFF
#define SPI_OUTLINK_ADDR_M  ((SPI_OUTLINK_ADDR_V)<<(SPI_OUTLINK_ADDR_S))
#define SPI_OUTLINK_ADDR_V  0xFFFFF
#define SPI_OUTLINK_ADDR_S  0

#define SPI_DMA_IN_LINK_REG(i)          (REG_SPI_BASE(i) + 0x108)
/* SPI_INLINK_RESTART：R/W；位位置：[30]；默认值：1’b0；*/
/*description:设置要装入新内联描述符的位。*/
#define SPI_INLINK_RESTART  (BIT(30))
#define SPI_INLINK_RESTART_M  (BIT(30))
#define SPI_INLINK_RESTART_V  0x1
#define SPI_INLINK_RESTART_S  30
/* SPI_INLINK_START:R/W；位位置：[29]；默认值：1’b0；*/
/*description:设置开始使用内联描述符的位。*/
#define SPI_INLINK_START  (BIT(29))
#define SPI_INLINK_START_M  (BIT(29))
#define SPI_INLINK_START_V  0x1
#define SPI_INLINK_START_S  29
/* SPI_INLINK_STOP：R/W；位位置：[28]；默认值：1’b0；*/
/*description:将位设置为stop以使用内联描述符。*/
#define SPI_INLINK_STOP  (BIT(28))
#define SPI_INLINK_STOP_M  (BIT(28))
#define SPI_INLINK_STOP_V  0x1
#define SPI_INLINK_STOP_S  28
/* SPI_INLINK_AUTO_RET:R/W；位位置：[20]；默认值：1’b0；*/
/*描述：当设置位时，内联描述符返回到下一个描述符，而数据包错误*/
#define SPI_INLINK_AUTO_RET  (BIT(20))
#define SPI_INLINK_AUTO_RET_M  (BIT(20))
#define SPI_INLINK_AUTO_RET_V  0x1
#define SPI_INLINK_AUTO_RET_S  20
/* SPI_INLINK_ADDR:R/W；比特位置：[19:0]；默认值：20'00；*/
/*description:第一个内联描述符的地址。*/
#define SPI_INLINK_ADDR  0x000FFFFF
#define SPI_INLINK_ADDR_M  ((SPI_INLINK_ADDR_V)<<(SPI_INLINK_ADDR_S))
#define SPI_INLINK_ADDR_V  0xFFFFF
#define SPI_INLINK_ADDR_S  0

#define SPI_DMA_STATUS_REG(i)          (REG_SPI_BASE(i) + 0x10C)
/* SPI_DMA_TX_EN:RO；位位置：[1]；默认值：1’b0；*/
/*描述：spidma写入数据状态位。*/
#define SPI_DMA_TX_EN  (BIT(1))
#define SPI_DMA_TX_EN_M  (BIT(1))
#define SPI_DMA_TX_EN_V  0x1
#define SPI_DMA_TX_EN_S  1
/* SPI_DMA_RX_EN:RO；位位置：[0]；默认值：1’b0；*/
/*描述：spidma读取数据状态位。*/
#define SPI_DMA_RX_EN  (BIT(0))
#define SPI_DMA_RX_EN_M  (BIT(0))
#define SPI_DMA_RX_EN_V  0x1
#define SPI_DMA_RX_EN_S  0

#define SPI_DMA_INT_ENA_REG(i)          (REG_SPI_BASE(i) + 0x110)
/* SPI_OUT_TOTAL_EOF_INT_ENA：R/W；位位置：[8]；默认值：1’b0；*/
/*description:向主机发送所有数据包的启用位已完成。*/
#define SPI_OUT_TOTAL_EOF_INT_ENA  (BIT(8))
#define SPI_OUT_TOTAL_EOF_INT_ENA_M  (BIT(8))
#define SPI_OUT_TOTAL_EOF_INT_ENA_V  0x1
#define SPI_OUT_TOTAL_EOF_INT_ENA_S  8
/* SPI_OUT_EOF_INT_ENA：R/W；位位置：[7]；默认值：1’b0；*/
/*description:向主机发送数据包的启用位已完成。*/
#define SPI_OUT_EOF_INT_ENA  (BIT(7))
#define SPI_OUT_EOF_INT_ENA_M  (BIT(7))
#define SPI_OUT_EOF_INT_ENA_V  0x1
#define SPI_OUT_EOF_INT_ENA_S  7
/* SPI_OUT_DONE_INT_ENA：R/W；位位置：[6]；默认值：1’b0；*/
/*description:用于完成outlink描述符使用的启用位。*/
#define SPI_OUT_DONE_INT_ENA  (BIT(6))
#define SPI_OUT_DONE_INT_ENA_M  (BIT(6))
#define SPI_OUT_DONE_INT_ENA_V  0x1
#define SPI_OUT_DONE_INT_ENA_S  6
/* SPI_IN_SUC_EOF_INT_ENA：R/W；位位置：[5]；默认值：1’b0；*/
/*description:用于完成从主机接收所有数据包的启用位。*/
#define SPI_IN_SUC_EOF_INT_ENA  (BIT(5))
#define SPI_IN_SUC_EOF_INT_ENA_M  (BIT(5))
#define SPI_IN_SUC_EOF_INT_ENA_V  0x1
#define SPI_IN_SUC_EOF_INT_ENA_S  5
/* SPI_IN_ERR_EOF_INT_ENA：R/W；位位置：[4]；默认值：1’b0；*/
/*description:接收错误的启用位。*/
#define SPI_IN_ERR_EOF_INT_ENA  (BIT(4))
#define SPI_IN_ERR_EOF_INT_ENA_M  (BIT(4))
#define SPI_IN_ERR_EOF_INT_ENA_V  0x1
#define SPI_IN_ERR_EOF_INT_ENA_S  4
/* SPI_IN_DONE_INT_ENA:R/W；位位置：[3]；默认值：1’b0；*/
/*description:用于完成内联描述符使用的启用位。*/
#define SPI_IN_DONE_INT_ENA  (BIT(3))
#define SPI_IN_DONE_INT_ENA_M  (BIT(3))
#define SPI_IN_DONE_INT_ENA_V  0x1
#define SPI_IN_DONE_INT_ENA_S  3
/* SPI_INLINK_DSCR_ERROR_INT_ENA:R/W；位位置：[2]；默认值：1’b0；*/
/*description:内联描述符错误的启用位。*/
#define SPI_INLINK_DSCR_ERROR_INT_ENA  (BIT(2))
#define SPI_INLINK_DSCR_ERROR_INT_ENA_M  (BIT(2))
#define SPI_INLINK_DSCR_ERROR_INT_ENA_V  0x1
#define SPI_INLINK_DSCR_ERROR_INT_ENA_S  2
/* SPI_OUTLINK_DSCR_ERROR_INT_ENA:R/W；位位置：[1]；默认值：1’b0；*/
/*description:outlink描述符错误的启用位。*/
#define SPI_OUTLINK_DSCR_ERROR_INT_ENA  (BIT(1))
#define SPI_OUTLINK_DSCR_ERROR_INT_ENA_M  (BIT(1))
#define SPI_OUTLINK_DSCR_ERROR_INT_ENA_V  0x1
#define SPI_OUTLINK_DSCR_ERROR_INT_ENA_S  1
/* SPI_INLINK_DSCR_EMPTY_INT_ENA:R/W；位位置：[0]；默认值：1’b0；*/
/*description:缺少足够内联描述符的启用位。*/
#define SPI_INLINK_DSCR_EMPTY_INT_ENA  (BIT(0))
#define SPI_INLINK_DSCR_EMPTY_INT_ENA_M  (BIT(0))
#define SPI_INLINK_DSCR_EMPTY_INT_ENA_V  0x1
#define SPI_INLINK_DSCR_EMPTY_INT_ENA_S  0

#define SPI_DMA_INT_RAW_REG(i)          (REG_SPI_BASE(i) + 0x114)
/* SPI_OUT_TOTAL_EOF_INT_RAW:RO；位位置：[8]；默认值：1’b0；*/
/*description:将所有数据包发送到主机的原始位已完成。*/
#define SPI_OUT_TOTAL_EOF_INT_RAW  (BIT(8))
#define SPI_OUT_TOTAL_EOF_INT_RAW_M  (BIT(8))
#define SPI_OUT_TOTAL_EOF_INT_RAW_V  0x1
#define SPI_OUT_TOTAL_EOF_INT_RAW_S  8
/* SPI_OUT_EOF_INT_RAW:RO；位位置：[7]；默认值：1’b0；*/
/*description:向主机发送数据包的原始位已完成。*/
#define SPI_OUT_EOF_INT_RAW  (BIT(7))
#define SPI_OUT_EOF_INT_RAW_M  (BIT(7))
#define SPI_OUT_EOF_INT_RAW_V  0x1
#define SPI_OUT_EOF_INT_RAW_S  7
/* SPI_OUT_DONE_INT_RAW:RO；位位置：[6]；默认值：1’b0；*/
/*description:用于完成outlink描述符使用的原始位。*/
#define SPI_OUT_DONE_INT_RAW  (BIT(6))
#define SPI_OUT_DONE_INT_RAW_M  (BIT(6))
#define SPI_OUT_DONE_INT_RAW_V  0x1
#define SPI_OUT_DONE_INT_RAW_S  6
/* SPI_IN_SUC_EOF_INT_RAW:RO；位位置：[5]；默认值：1’b0；*/
/*description:完成从主机接收所有数据包的原始位。*/
#define SPI_IN_SUC_EOF_INT_RAW  (BIT(5))
#define SPI_IN_SUC_EOF_INT_RAW_M  (BIT(5))
#define SPI_IN_SUC_EOF_INT_RAW_V  0x1
#define SPI_IN_SUC_EOF_INT_RAW_S  5
/* SPI_IN_ERR_EOF_INT_RAW:RO；位位置：[4]；默认值：1’b0；*/
/*description:接收错误的原始位。*/
#define SPI_IN_ERR_EOF_INT_RAW  (BIT(4))
#define SPI_IN_ERR_EOF_INT_RAW_M  (BIT(4))
#define SPI_IN_ERR_EOF_INT_RAW_V  0x1
#define SPI_IN_ERR_EOF_INT_RAW_S  4
/* SPI_IN_DONE_INT_RAW:RO；位位置：[3]；默认值：1’b0；*/
/*description:完成内联描述符使用的原始位。*/
#define SPI_IN_DONE_INT_RAW  (BIT(3))
#define SPI_IN_DONE_INT_RAW_M  (BIT(3))
#define SPI_IN_DONE_INT_RAW_V  0x1
#define SPI_IN_DONE_INT_RAW_S  3
/* SPI_INLINK_DSCR_ERROR_INT_RAW:RO；位位置：[2]；默认值：1’b0；*/
/*description:内联描述符错误的原始位。*/
#define SPI_INLINK_DSCR_ERROR_INT_RAW  (BIT(2))
#define SPI_INLINK_DSCR_ERROR_INT_RAW_M  (BIT(2))
#define SPI_INLINK_DSCR_ERROR_INT_RAW_V  0x1
#define SPI_INLINK_DSCR_ERROR_INT_RAW_S  2
/* SPI_OUTLINK_DSCR_ERROR_INT_RAW:RO；位位置：[1]；默认值：1’b0；*/
/*description:outlink描述符错误的原始位。*/
#define SPI_OUTLINK_DSCR_ERROR_INT_RAW  (BIT(1))
#define SPI_OUTLINK_DSCR_ERROR_INT_RAW_M  (BIT(1))
#define SPI_OUTLINK_DSCR_ERROR_INT_RAW_V  0x1
#define SPI_OUTLINK_DSCR_ERROR_INT_RAW_S  1
/* SPI_INLINK_DSCR_EMPTY_INT_RAW:RO；位位置：[0]；默认值：1’b0；*/
/*description:缺少足够的内联描述符的原始位。*/
#define SPI_INLINK_DSCR_EMPTY_INT_RAW  (BIT(0))
#define SPI_INLINK_DSCR_EMPTY_INT_RAW_M  (BIT(0))
#define SPI_INLINK_DSCR_EMPTY_INT_RAW_V  0x1
#define SPI_INLINK_DSCR_EMPTY_INT_RAW_S  0

#define SPI_DMA_INT_ST_REG(i)          (REG_SPI_BASE(i) + 0x118)
/* SPI_OUT_TOTAL_EOF_INT_ST:RO；位位置：[8]；默认值：1’b0；*/
/*description:向主机发送所有数据包的状态位已完成。*/
#define SPI_OUT_TOTAL_EOF_INT_ST  (BIT(8))
#define SPI_OUT_TOTAL_EOF_INT_ST_M  (BIT(8))
#define SPI_OUT_TOTAL_EOF_INT_ST_V  0x1
#define SPI_OUT_TOTAL_EOF_INT_ST_S  8
/* SPI_OUT_EOF_INT_ST:RO；位位置：[7]；默认值：1’b0；*/
/*description:向主机发送数据包的状态位已完成。*/
#define SPI_OUT_EOF_INT_ST  (BIT(7))
#define SPI_OUT_EOF_INT_ST_M  (BIT(7))
#define SPI_OUT_EOF_INT_ST_V  0x1
#define SPI_OUT_EOF_INT_ST_S  7
/* SPI_OUT_DONE_INT_ST:RO；位位置：[6]；默认值：1’b0；*/
/*description:用于完成outlink描述符使用的状态位。*/
#define SPI_OUT_DONE_INT_ST  (BIT(6))
#define SPI_OUT_DONE_INT_ST_M  (BIT(6))
#define SPI_OUT_DONE_INT_ST_V  0x1
#define SPI_OUT_DONE_INT_ST_S  6
/* SPI_IN_SUC_EOF_INT_ST:RO；位位置：[5]；默认值：1’b0；*/
/*description:完成从主机接收所有数据包的状态位。*/
#define SPI_IN_SUC_EOF_INT_ST  (BIT(5))
#define SPI_IN_SUC_EOF_INT_ST_M  (BIT(5))
#define SPI_IN_SUC_EOF_INT_ST_V  0x1
#define SPI_IN_SUC_EOF_INT_ST_S  5
/* SPI_IN_ERR_EOF_INT_ST:RO；位位置：[4]；默认值：1’b0；*/
/*description:接收错误的状态位。*/
#define SPI_IN_ERR_EOF_INT_ST  (BIT(4))
#define SPI_IN_ERR_EOF_INT_ST_M  (BIT(4))
#define SPI_IN_ERR_EOF_INT_ST_V  0x1
#define SPI_IN_ERR_EOF_INT_ST_S  4
/* SPI_IN_DONE_INT_ST:RO；位位置：[3]；默认值：1’b0；*/
/*description:完成内联描述符使用的状态位。*/
#define SPI_IN_DONE_INT_ST  (BIT(3))
#define SPI_IN_DONE_INT_ST_M  (BIT(3))
#define SPI_IN_DONE_INT_ST_V  0x1
#define SPI_IN_DONE_INT_ST_S  3
/* SPI_INLINK_DSCR_ERROR_INT_ST:RO；位位置：[2]；默认值：1’b0；*/
/*description:内联描述符错误的状态位。*/
#define SPI_INLINK_DSCR_ERROR_INT_ST  (BIT(2))
#define SPI_INLINK_DSCR_ERROR_INT_ST_M  (BIT(2))
#define SPI_INLINK_DSCR_ERROR_INT_ST_V  0x1
#define SPI_INLINK_DSCR_ERROR_INT_ST_S  2
/* SPI_OUTLINK_DSCR_ERROR_INT_ST:RO；位位置：[1]；默认值：1’b0；*/
/*description:outlink描述符错误的状态位。*/
#define SPI_OUTLINK_DSCR_ERROR_INT_ST  (BIT(1))
#define SPI_OUTLINK_DSCR_ERROR_INT_ST_M  (BIT(1))
#define SPI_OUTLINK_DSCR_ERROR_INT_ST_V  0x1
#define SPI_OUTLINK_DSCR_ERROR_INT_ST_S  1
/* SPI_INLINK_DSCR_EMPTY_INT_ST:RO；位位置：[0]；默认值：1’b0；*/
/*description:缺少足够的内联描述符的状态位。*/
#define SPI_INLINK_DSCR_EMPTY_INT_ST  (BIT(0))
#define SPI_INLINK_DSCR_EMPTY_INT_ST_M  (BIT(0))
#define SPI_INLINK_DSCR_EMPTY_INT_ST_V  0x1
#define SPI_INLINK_DSCR_EMPTY_INT_ST_S  0

#define SPI_DMA_INT_CLR_REG(i)          (REG_SPI_BASE(i) + 0x11C)
/* SPI_OUT_TOTAL_EOF_INT_CLR:R/W；位位置：[8]；默认值：1’b0；*/
/*description:将所有数据包发送到主机的清除位已完成。*/
#define SPI_OUT_TOTAL_EOF_INT_CLR  (BIT(8))
#define SPI_OUT_TOTAL_EOF_INT_CLR_M  (BIT(8))
#define SPI_OUT_TOTAL_EOF_INT_CLR_V  0x1
#define SPI_OUT_TOTAL_EOF_INT_CLR_S  8
/* 输出_输出_输入_输出_输出：R/W；位位置：[7]；默认值：1’b0；*/
/*description:向主机发送数据包的清除位已完成。*/
#define SPI_OUT_EOF_INT_CLR  (BIT(7))
#define SPI_OUT_EOF_INT_CLR_M  (BIT(7))
#define SPI_OUT_EOF_INT_CLR_V  0x1
#define SPI_OUT_EOF_INT_CLR_S  7
/* SPI_OUT_DONE_INT_CLR:R/W；位位置：[6]；默认值：1’b0；*/
/*description:用于完成outlink描述符使用的清除位。*/
#define SPI_OUT_DONE_INT_CLR  (BIT(6))
#define SPI_OUT_DONE_INT_CLR_M  (BIT(6))
#define SPI_OUT_DONE_INT_CLR_V  0x1
#define SPI_OUT_DONE_INT_CLR_S  6
/* SPI_IN_SUC_EOF_INT_CLR:R/W；位位置：[5]；默认值：1’b0；*/
/*description:完成从主机接收所有数据包的清除位。*/
#define SPI_IN_SUC_EOF_INT_CLR  (BIT(5))
#define SPI_IN_SUC_EOF_INT_CLR_M  (BIT(5))
#define SPI_IN_SUC_EOF_INT_CLR_V  0x1
#define SPI_IN_SUC_EOF_INT_CLR_S  5
/* SPI_IN_ERR_EOF_INT_CLR:R/W；位位置：[4]；默认值：1’b0；*/
/*description:接收错误的清除位。*/
#define SPI_IN_ERR_EOF_INT_CLR  (BIT(4))
#define SPI_IN_ERR_EOF_INT_CLR_M  (BIT(4))
#define SPI_IN_ERR_EOF_INT_CLR_V  0x1
#define SPI_IN_ERR_EOF_INT_CLR_S  4
/* SPI_IN_DONE_INT_CLR:R/W；位位置：[3]；默认值：1’b0；*/
/*description:用于完成内联描述符使用的清除位。*/
#define SPI_IN_DONE_INT_CLR  (BIT(3))
#define SPI_IN_DONE_INT_CLR_M  (BIT(3))
#define SPI_IN_DONE_INT_CLR_V  0x1
#define SPI_IN_DONE_INT_CLR_S  3
/* SPI_INLINK_DSCR_ERROR_INT_CLR:R/W；位位置：[2]；默认值：1’b0；*/
/*description:内联描述符错误的清除位。*/
#define SPI_INLINK_DSCR_ERROR_INT_CLR  (BIT(2))
#define SPI_INLINK_DSCR_ERROR_INT_CLR_M  (BIT(2))
#define SPI_INLINK_DSCR_ERROR_INT_CLR_V  0x1
#define SPI_INLINK_DSCR_ERROR_INT_CLR_S  2
/* SPI_OUTLINK_DSCR_ERROR_INT_CLR:R/W；位位置：[1]；默认值：1’b0；*/
/*description:outlink描述符错误的清除位。*/
#define SPI_OUTLINK_DSCR_ERROR_INT_CLR  (BIT(1))
#define SPI_OUTLINK_DSCR_ERROR_INT_CLR_M  (BIT(1))
#define SPI_OUTLINK_DSCR_ERROR_INT_CLR_V  0x1
#define SPI_OUTLINK_DSCR_ERROR_INT_CLR_S  1
/* SPI_INLINK_DSCR_EMPTY_INT_CLR:R/W；位位置：[0]；默认值：1’b0；*/
/*description:缺少足够的内联描述符的清除位。*/
#define SPI_INLINK_DSCR_EMPTY_INT_CLR  (BIT(0))
#define SPI_INLINK_DSCR_EMPTY_INT_CLR_M  (BIT(0))
#define SPI_INLINK_DSCR_EMPTY_INT_CLR_V  0x1
#define SPI_INLINK_DSCR_EMPTY_INT_CLR_S  0

#define SPI_IN_ERR_EOF_DES_ADDR_REG(i)          (REG_SPI_BASE(i) + 0x120)
/* SPI_DMA_IN_ERR_EOF_DES_ADDR:RO；位位置：[31:0]；默认值：32'b0；*/
/*description:spidma产生接收错误时的内联描述符地址。*/
#define SPI_DMA_IN_ERR_EOF_DES_ADDR  0xFFFFFFFF
#define SPI_DMA_IN_ERR_EOF_DES_ADDR_M  ((SPI_DMA_IN_ERR_EOF_DES_ADDR_V)<<(SPI_DMA_IN_ERR_EOF_DES_ADDR_S))
#define SPI_DMA_IN_ERR_EOF_DES_ADDR_V  0xFFFFFFFF
#define SPI_DMA_IN_ERR_EOF_DES_ADDR_S  0

#define SPI_IN_SUC_EOF_DES_ADDR_REG(i)          (REG_SPI_BASE(i) + 0x124)
/* SPI_DMA_IN_SUC_EOF_DES_ADDR:RO；位位置：[31:0]；默认值：32'b0；*/
/*description:spidma生成from_suc_eof时的最后一个内联描述符地址。*/
#define SPI_DMA_IN_SUC_EOF_DES_ADDR  0xFFFFFFFF
#define SPI_DMA_IN_SUC_EOF_DES_ADDR_M  ((SPI_DMA_IN_SUC_EOF_DES_ADDR_V)<<(SPI_DMA_IN_SUC_EOF_DES_ADDR_S))
#define SPI_DMA_IN_SUC_EOF_DES_ADDR_V  0xFFFFFFFF
#define SPI_DMA_IN_SUC_EOF_DES_ADDR_S  0

#define SPI_INLINK_DSCR_REG(i)          (REG_SPI_BASE(i) + 0x128)
/* SPI_DMA_INLINK_DSCR:RO；位位置：[31:0]；默认值：32'b0；*/
/*description:当前在描述符指针中的内容。*/
#define SPI_DMA_INLINK_DSCR  0xFFFFFFFF
#define SPI_DMA_INLINK_DSCR_M  ((SPI_DMA_INLINK_DSCR_V)<<(SPI_DMA_INLINK_DSCR_S))
#define SPI_DMA_INLINK_DSCR_V  0xFFFFFFFF
#define SPI_DMA_INLINK_DSCR_S  0

#define SPI_INLINK_DSCR_BF0_REG(i)          (REG_SPI_BASE(i) + 0x12C)
/* SPI_DMA_INLINK_DSCR_BF0:RO；位位置：[31:0]；默认值：32'b0；*/
/*description:描述符指针中next的内容。*/
#define SPI_DMA_INLINK_DSCR_BF0  0xFFFFFFFF
#define SPI_DMA_INLINK_DSCR_BF0_M  ((SPI_DMA_INLINK_DSCR_BF0_V)<<(SPI_DMA_INLINK_DSCR_BF0_S))
#define SPI_DMA_INLINK_DSCR_BF0_V  0xFFFFFFFF
#define SPI_DMA_INLINK_DSCR_BF0_S  0

#define SPI_INLINK_DSCR_BF1_REG(i)          (REG_SPI_BASE(i) + 0x130)
/* SPI_DMA_INLINK_DSCR_BF1:RO；位位置：[31:0]；默认值：32'b0；*/
/*description:描述符中当前数据缓冲区指针的内容。*/
#define SPI_DMA_INLINK_DSCR_BF1  0xFFFFFFFF
#define SPI_DMA_INLINK_DSCR_BF1_M  ((SPI_DMA_INLINK_DSCR_BF1_V)<<(SPI_DMA_INLINK_DSCR_BF1_S))
#define SPI_DMA_INLINK_DSCR_BF1_V  0xFFFFFFFF
#define SPI_DMA_INLINK_DSCR_BF1_S  0

#define SPI_OUT_EOF_BFR_DES_ADDR_REG(i)          (REG_SPI_BASE(i) + 0x134)
/* SPI_DMA_OUT_EOF_BFR_DES_ADDR:RO；位位置：[31:0]；默认值：32'b0；*/
/*description:相对于产生eof的outlink描述符的缓冲区地址。*/
#define SPI_DMA_OUT_EOF_BFR_DES_ADDR  0xFFFFFFFF
#define SPI_DMA_OUT_EOF_BFR_DES_ADDR_M  ((SPI_DMA_OUT_EOF_BFR_DES_ADDR_V)<<(SPI_DMA_OUT_EOF_BFR_DES_ADDR_S))
#define SPI_DMA_OUT_EOF_BFR_DES_ADDR_V  0xFFFFFFFF
#define SPI_DMA_OUT_EOF_BFR_DES_ADDR_S  0

#define SPI_OUT_EOF_DES_ADDR_REG(i)          (REG_SPI_BASE(i) + 0x138)
/* SPI_DMA_OUT_EOF_DES_ADDR:RO；位位置：[31:0]；默认值：32'b0；*/
/*description:spidma生成to_eof时的最后一个outlink描述符地址。*/
#define SPI_DMA_OUT_EOF_DES_ADDR  0xFFFFFFFF
#define SPI_DMA_OUT_EOF_DES_ADDR_M  ((SPI_DMA_OUT_EOF_DES_ADDR_V)<<(SPI_DMA_OUT_EOF_DES_ADDR_S))
#define SPI_DMA_OUT_EOF_DES_ADDR_V  0xFFFFFFFF
#define SPI_DMA_OUT_EOF_DES_ADDR_S  0

#define SPI_OUTLINK_DSCR_REG(i)          (REG_SPI_BASE(i) + 0x13C)
/* SPI_DMA_OUTLINK_DSCR:RO；位位置：[31:0]；默认值：32'b0；*/
/*description:当前输出描述符指针的内容。*/
#define SPI_DMA_OUTLINK_DSCR  0xFFFFFFFF
#define SPI_DMA_OUTLINK_DSCR_M  ((SPI_DMA_OUTLINK_DSCR_V)<<(SPI_DMA_OUTLINK_DSCR_S))
#define SPI_DMA_OUTLINK_DSCR_V  0xFFFFFFFF
#define SPI_DMA_OUTLINK_DSCR_S  0

#define SPI_OUTLINK_DSCR_BF0_REG(i)          (REG_SPI_BASE(i) + 0x140)
/* SPI_DMA_OUTLINK_DSCR_BF0:RO；位位置：[31:0]；默认值：32'b0；*/
/*description:next-out描述符指针的内容。*/
#define SPI_DMA_OUTLINK_DSCR_BF0  0xFFFFFFFF
#define SPI_DMA_OUTLINK_DSCR_BF0_M  ((SPI_DMA_OUTLINK_DSCR_BF0_V)<<(SPI_DMA_OUTLINK_DSCR_BF0_S))
#define SPI_DMA_OUTLINK_DSCR_BF0_V  0xFFFFFFFF
#define SPI_DMA_OUTLINK_DSCR_BF0_S  0

#define SPI_OUTLINK_DSCR_BF1_REG(i)          (REG_SPI_BASE(i) + 0x144)
/* SPI_DMA_OUTLINK_DSCR_BF1:RO；位位置：[31:0]；默认值：32'b0；*/
/*description:当前输出描述符数据缓冲区指针的内容。*/
#define SPI_DMA_OUTLINK_DSCR_BF1  0xFFFFFFFF
#define SPI_DMA_OUTLINK_DSCR_BF1_M  ((SPI_DMA_OUTLINK_DSCR_BF1_V)<<(SPI_DMA_OUTLINK_DSCR_BF1_S))
#define SPI_DMA_OUTLINK_DSCR_BF1_V  0xFFFFFFFF
#define SPI_DMA_OUTLINK_DSCR_BF1_S  0

#define SPI_DMA_RSTATUS_REG(i)          (REG_SPI_BASE(i) + 0x148)
/* SPI_DMA_OUT_STATUS:RO；位位置：[31:0]；默认值：32'b0；*/
/*描述：spidma从内存状态读取数据。*/
#define SPI_DMA_OUT_STATUS  0xFFFFFFFF
#define SPI_DMA_OUT_STATUS_M  ((SPI_DMA_OUT_STATUS_V)<<(SPI_DMA_OUT_STATUS_S))
#define SPI_DMA_OUT_STATUS_V  0xFFFFFFFF
#define SPI_DMA_OUT_STATUS_S  0

#define SPI_DMA_TSTATUS_REG(i)          (REG_SPI_BASE(i) + 0x14C)
/* SPI_DMA_IN_STATUS:RO；位位置：[31:0]；默认值：32'b0；*/
/*描述：spidma将数据写入内存状态。*/
#define SPI_DMA_IN_STATUS  0xFFFFFFFF
#define SPI_DMA_IN_STATUS_M  ((SPI_DMA_IN_STATUS_V)<<(SPI_DMA_IN_STATUS_S))
#define SPI_DMA_IN_STATUS_V  0xFFFFFFFF
#define SPI_DMA_IN_STATUS_S  0

#define SPI_DATE_REG(i)          (REG_SPI_BASE(i) + 0x3FC)
/* SPI_DATE:RO；位位置：[27:0]；默认值：32'h1604270；*/
/*description:SPI寄存器版本。*/
#define SPI_DATE  0x0FFFFFFF
#define SPI_DATE_M  ((SPI_DATE_V)<<(SPI_DATE_S))
#define SPI_DATE_V  0xFFFFFFF
#define SPI_DATE_S  0




#endif /*__SPI_REG_H__ */

