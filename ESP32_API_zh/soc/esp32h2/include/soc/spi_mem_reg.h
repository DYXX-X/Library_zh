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
#ifndef _SOC_SPI_MEM_REG_H_
#define _SOC_SPI_MEM_REG_H_


#ifdef __cplusplus
extern "C" {
#endif
#include "soc.h"
#define SPI_MEM_CMD_REG(i)          (REG_SPI_MEM_BASE(i) + 0x000)
/* SPI_MEM_FLASH_READ：R/W/SC；位位置：[31]；默认值：1’b0；*/
/*description:读取闪存启用。设置位时，将触发读取闪存操作。操作完成后，该位将被清除。1： 启用0：禁用。*/
#define SPI_MEM_FLASH_READ  (BIT(31))
#define SPI_MEM_FLASH_READ_M  (BIT(31))
#define SPI_MEM_FLASH_READ_V  0x1
#define SPI_MEM_FLASH_READ_S  31
/* SPI_MEM_FLASH_WREN：R/W/SC；位位置：[30]；默认值：1’b0；*/
/*description:写入闪存启用。设置位时，将发送写入启用命令。操作完成后，该位将被清除。1： 启用0：禁用。*/
#define SPI_MEM_FLASH_WREN  (BIT(30))
#define SPI_MEM_FLASH_WREN_M  (BIT(30))
#define SPI_MEM_FLASH_WREN_V  0x1
#define SPI_MEM_FLASH_WREN_S  30
/* SPI_MEM_FLASH_WRDI:R/W/SC；位位置：[29]；默认值：1’b0；*/
/*description:写入闪存禁用。设置位时将发送写禁用命令。操作完成后，该位将被清除。1： 启用0：禁用。*/
#define SPI_MEM_FLASH_WRDI  (BIT(29))
#define SPI_MEM_FLASH_WRDI_M  (BIT(29))
#define SPI_MEM_FLASH_WRDI_V  0x1
#define SPI_MEM_FLASH_WRDI_S  29
/* SPI_MEM_FLASH_rid:R/W/SC；位位置：[28]；默认值：1’b0；*/
/*description:读取JEDEC ID。设置位时将发送读取ID命令。操作完成后，该位将被清除。1： 启用0：禁用。*/
#define SPI_MEM_FLASH_RDID  (BIT(28))
#define SPI_MEM_FLASH_RDID_M  (BIT(28))
#define SPI_MEM_FLASH_RDID_V  0x1
#define SPI_MEM_FLASH_RDID_S  28
/* SPI_MEM_FLASH_RDSR:R/W/SC；位位置：[27]；默认值：1’b0；*/
/*description:读取状态寄存器-1。设置位时将触发读取状态操作。操作完成后，该位将被清除。1： 启用0：禁用。*/
#define SPI_MEM_FLASH_RDSR  (BIT(27))
#define SPI_MEM_FLASH_RDSR_M  (BIT(27))
#define SPI_MEM_FLASH_RDSR_V  0x1
#define SPI_MEM_FLASH_RDSR_S  27
/* SPI_MEM_FLASH_WRSR:R/W/SC；位位置：[26]；默认值：1’b0；*/
/*description:写入状态寄存器启用。设置位时将触发写入状态操作。操作完成后，该位将被清除。1： 启用0：禁用。*/
#define SPI_MEM_FLASH_WRSR  (BIT(26))
#define SPI_MEM_FLASH_WRSR_M  (BIT(26))
#define SPI_MEM_FLASH_WRSR_V  0x1
#define SPI_MEM_FLASH_WRSR_S  26
/* SPI_MEM_FLASH_PP:R/W/SC；位位置：[25]；默认值：1’b0；*/
/*description:页面程序启用（要编程的数据为1字节~256字节）。设置位时将触发页面程序操作。一旦操作完成，该位将被清除。1：启用0：禁用。*/
#define SPI_MEM_FLASH_PP  (BIT(25))
#define SPI_MEM_FLASH_PP_M  (BIT(25))
#define SPI_MEM_FLASH_PP_V  0x1
#define SPI_MEM_FLASH_PP_S  25
/* SPI_MEM_FLASH_SE:R/W/SC；位位置：[24]；默认值：1’b0；*/
/*description:扇区擦除启用（4KB）。设置位时将触发扇区擦除操作。操作完成后，该位将被清除。1： 启用0：禁用。*/
#define SPI_MEM_FLASH_SE  (BIT(24))
#define SPI_MEM_FLASH_SE_M  (BIT(24))
#define SPI_MEM_FLASH_SE_V  0x1
#define SPI_MEM_FLASH_SE_S  24
/* SPI_MEM_FLASH_BE:R/W/SC；位位置：[23]；默认值：1’b0；*/
/*description:块擦除启用（32KB）。设置位时将触发块擦除操作。操作完成后，该位将被清除。1： 启用0：禁用。*/
#define SPI_MEM_FLASH_BE  (BIT(23))
#define SPI_MEM_FLASH_BE_M  (BIT(23))
#define SPI_MEM_FLASH_BE_V  0x1
#define SPI_MEM_FLASH_BE_S  23
/* SPI_MEM_FLASH_CE:R/W/SC；位位置：[22]；默认值：1’b0；*/
/*description:芯片擦除启用。设置位时将触发芯片擦除操作。操作完成后，该位将被清除。1： 启用0：禁用。*/
#define SPI_MEM_FLASH_CE  (BIT(22))
#define SPI_MEM_FLASH_CE_M  (BIT(22))
#define SPI_MEM_FLASH_CE_V  0x1
#define SPI_MEM_FLASH_CE_S  22
/* SPI_MEM_FLASH_DP:R/W/SC；位位置：[21]；默认值：1’b0；*/
/*description:驱动Flash关闭电源。设置位时将触发操作。操作完成后，该位将被清除。1： 启用0：禁用。*/
#define SPI_MEM_FLASH_DP  (BIT(21))
#define SPI_MEM_FLASH_DP_M  (BIT(21))
#define SPI_MEM_FLASH_DP_V  0x1
#define SPI_MEM_FLASH_DP_S  21
/* SPI_MEM_FLASH_RES:R/W/SC；位位置：[20]；默认值：1’b0；*/
/*description:此位与reg_resandres位结合，将Flash从断电状态或高性能模式释放，并获取设备ID。一旦操作完成，该位将被清除。1： 启用0：禁用。*/
#define SPI_MEM_FLASH_RES  (BIT(20))
#define SPI_MEM_FLASH_RES_M  (BIT(20))
#define SPI_MEM_FLASH_RES_V  0x1
#define SPI_MEM_FLASH_RES_S  20
/* SPI_MEM_FLASH-HPM:R/W/SC；位位置：[19]；默认值：1’b0；*/
/*description:将Flash驱动到高性能模式。操作完成后，该位将被清除。1： 启用0：禁用。*/
#define SPI_MEM_FLASH_HPM  (BIT(19))
#define SPI_MEM_FLASH_HPM_M  (BIT(19))
#define SPI_MEM_FLASH_HPM_V  0x1
#define SPI_MEM_FLASH_HPM_S  19
/* SPI_MEM_USR:R/W/SC；位位置：[18]；默认值：1’b0；*/
/*description:用户定义命令启用。设置位时将触发操作。操作完成后，该位将被清除。1： 启用0：禁用。*/
#define SPI_MEM_USR  (BIT(18))
#define SPI_MEM_USR_M  (BIT(18))
#define SPI_MEM_USR_V  0x1
#define SPI_MEM_USR_S  18
/* SPI_MEM_FLASH_PE:R/W/SC；位位置：[17]；默认值：1’b0；*/
/*description:在用户模式下，设置为指示将触发编程/擦除操作。该位与spi_mem_usr位组合。操作完成后，该位将被清除。1： 启用0：禁用。*/
#define SPI_MEM_FLASH_PE  (BIT(17))
#define SPI_MEM_FLASH_PE_M  (BIT(17))
#define SPI_MEM_FLASH_PE_V  0x1
#define SPI_MEM_FLASH_PE_S  17
/* SPI_MEM_SLV_ST:RO；位位置：[7:4]；默认值：4'b0；*/
/*description:SPI1从FSM的当前状态：mspi_st。0：空闲状态1：准备状态2：发送命令状态3：发送地址状态4：等待状态5：读取数据状态6：写入数据状态7：完成状态8：读取数据结束状态。*/
#define SPI_MEM_SLV_ST  0x0000000F
#define SPI_MEM_SLV_ST_M  ((SPI_MEM_SLV_ST_V)<<(SPI_MEM_SLV_ST_S))
#define SPI_MEM_SLV_ST_V  0xF
#define SPI_MEM_SLV_ST_S  4
/* SPI_MEM_MST_ST:RO；位位置：[3:0]；默认值：4'b0；*/
/*description:SPI1主FSM的当前状态。*/
#define SPI_MEM_MST_ST  0x0000000F
#define SPI_MEM_MST_ST_M  ((SPI_MEM_MST_ST_V)<<(SPI_MEM_MST_ST_S))
#define SPI_MEM_MST_ST_V  0xF
#define SPI_MEM_MST_ST_S  0

#define SPI_MEM_ADDR_REG(i)          (REG_SPI_MEM_BASE(i) + 0x004)
/* SPI_MEM_USR_ADDR_值：R/W；位位置：[31:0]；默认值：32'h0；*/
/*description:在用户模式下，它是内存地址。除此之外，位0位23是存储器地址，位24位31是传输的字节长度。*/
#define SPI_MEM_USR_ADDR_VALUE  0xFFFFFFFF
#define SPI_MEM_USR_ADDR_VALUE_M  ((SPI_MEM_USR_ADDR_VALUE_V)<<(SPI_MEM_USR_ADDR_VALUE_S))
#define SPI_MEM_USR_ADDR_VALUE_V  0xFFFFFFFF
#define SPI_MEM_USR_ADDR_VALUE_S  0

#define SPI_MEM_CTRL_REG(i)          (REG_SPI_MEM_BASE(i) + 0x008)
/* SPI_MEM_FREAD_QIO:R/W；位位置：[24]；默认值：1’b0；*/
/*描述：在读取操作中，地址阶段和读取数据阶段应用4个信号。1： 启用0：禁用。*/
#define SPI_MEM_FREAD_QIO  (BIT(24))
#define SPI_MEM_FREAD_QIO_M  (BIT(24))
#define SPI_MEM_FREAD_QIO_V  0x1
#define SPI_MEM_FREAD_QIO_S  24
/* SPI_MEM_FREAD_DIO:R/W；位位置：[23]；默认值：1’b0；*/
/*描述：在读取操作中，地址阶段和读取数据阶段应用2个信号。1： 启用0：禁用。*/
#define SPI_MEM_FREAD_DIO  (BIT(23))
#define SPI_MEM_FREAD_DIO_M  (BIT(23))
#define SPI_MEM_FREAD_DIO_V  0x1
#define SPI_MEM_FREAD_DIO_S  23
/* SPI_MEM_wrsr2b:R/W；位位置：[22]；默认值：1’b0；*/
/*描述：设置状态寄存器时，两个字节的数据将写入状态寄存器。1： 启用0：禁用。*/
#define SPI_MEM_WRSR_2B  (BIT(22))
#define SPI_MEM_WRSR_2B_M  (BIT(22))
#define SPI_MEM_WRSR_2B_V  0x1
#define SPI_MEM_WRSR_2B_S  22
/* SPI_MEM_WP_REG:R/W；位位置：[21]；默认值：1’b1；*/
/*description:SPI空闲时写保护信号输出。1： 输出高0：输出低。*/
#define SPI_MEM_WP_REG  (BIT(21))
#define SPI_MEM_WP_REG_M  (BIT(21))
#define SPI_MEM_WP_REG_V  0x1
#define SPI_MEM_WP_REG_S  21
/* SPI_MEM_FREAD_QUAD:R/W；位位置：[20]；默认值：1’b0；*/
/*描述：在读取操作中，读取数据阶段应用4个信号。1： 启用0：禁用。*/
#define SPI_MEM_FREAD_QUAD  (BIT(20))
#define SPI_MEM_FREAD_QUAD_M  (BIT(20))
#define SPI_MEM_FREAD_QUAD_V  0x1
#define SPI_MEM_FREAD_QUAD_S  20
/* SPI_MEM_D_POL:R/W；位位置：[19]；默认值：1’b1；*/
/*description:该位用于设置MOSI线极性1：高0低*/
#define SPI_MEM_D_POL  (BIT(19))
#define SPI_MEM_D_POL_M  (BIT(19))
#define SPI_MEM_D_POL_V  0x1
#define SPI_MEM_D_POL_S  19
/* SPI_MEM_Q_POL:R/W；位位置：[18]；默认值：1’b1；*/
/*description:该位用于设置MISO线极性1:高0低*/
#define SPI_MEM_Q_POL  (BIT(18))
#define SPI_MEM_Q_POL_M  (BIT(18))
#define SPI_MEM_Q_POL_V  0x1
#define SPI_MEM_Q_POL_S  18
/* SPI_MEM_RESANDRES:R/W；位位置：[15]；默认值：1’b1；*/
/*description:将设备ID读取到SPI_MEM_RD_STATUS寄存器，此位与SPI_MEM_flash_res位组合。1： 启用0：禁用。*/
#define SPI_MEM_RESANDRES  (BIT(15))
#define SPI_MEM_RESANDRES_M  (BIT(15))
#define SPI_MEM_RESANDRES_V  0x1
#define SPI_MEM_RESANDRES_S  15
/* SPI_MEM_FREAD_DUAL:R/W；位位置：[14]；默认值：1’b0；*/
/*描述：在读取操作中，读取数据阶段应用2个信号。1： 启用0：禁用。*/
#define SPI_MEM_FREAD_DUAL  (BIT(14))
#define SPI_MEM_FREAD_DUAL_M  (BIT(14))
#define SPI_MEM_FREAD_DUAL_V  0x1
#define SPI_MEM_FREAD_DUAL_S  14
/* SPI_MEM_FASTRD_MODE：R/W；位位置：[13]；默认值：1’b1；*/
/*description:此位启用位：spi_mem_fread_qio spi_mem-fread_dio spi_mem_fread_qout和spi_mem.fread_dout。1： 启用0：禁用。*/
#define SPI_MEM_FASTRD_MODE  (BIT(13))
#define SPI_MEM_FASTRD_MODE_M  (BIT(13))
#define SPI_MEM_FASTRD_MODE_V  0x1
#define SPI_MEM_FASTRD_MODE_S  13
/* SPI_MEM_TX_CRC_EN:R/W；位位置：[11]；默认值：1’b0；*/
/*description:对于SPI1，在将加密数据写入闪存时启用crc32。1： 启用0:禁用*/
#define SPI_MEM_TX_CRC_EN  (BIT(11))
#define SPI_MEM_TX_CRC_EN_M  (BIT(11))
#define SPI_MEM_TX_CRC_EN_V  0x1
#define SPI_MEM_TX_CRC_EN_S  11
/* SPI_MEM_FCS_CRC_EN:R/W；位位置：[10]；默认值：1’b0；*/
/*description:对于SPI1，在将加密数据写入闪存之前初始化crc32模块。低激活。*/
#define SPI_MEM_FCS_CRC_EN  (BIT(10))
#define SPI_MEM_FCS_CRC_EN_M  (BIT(10))
#define SPI_MEM_FCS_CRC_EN_V  0x1
#define SPI_MEM_FCS_CRC_EN_S  10
/* SPI_MEM_FCMD_QUAD:R/W；位位置：[8]；默认值：1’b0；*/
/*description:在命令阶段1：启用0：禁用期间应用4个信号*/
#define SPI_MEM_FCMD_QUAD  (BIT(8))
#define SPI_MEM_FCMD_QUAD_M  (BIT(8))
#define SPI_MEM_FCMD_QUAD_V  0x1
#define SPI_MEM_FCMD_QUAD_S  8
/* SPI_MEM_FCMD_DUAL:R/W；位位置：[7]；默认值：1’b0；*/
/*description:在命令阶段1：启用0：禁用期间应用2个信号*/
#define SPI_MEM_FCMD_DUAL  (BIT(7))
#define SPI_MEM_FCMD_DUAL_M  (BIT(7))
#define SPI_MEM_FCMD_DUAL_V  0x1
#define SPI_MEM_FCMD_DUAL_S  7
/* SPI_MEM_FDUMMY_OUT:R/W；位位置：[3]；默认值：1’b0；*/
/*描述：在虚拟阶段，spi的信号电平由spi控制器输出。*/
#define SPI_MEM_FDUMMY_OUT  (BIT(3))
#define SPI_MEM_FDUMMY_OUT_M  (BIT(3))
#define SPI_MEM_FDUMMY_OUT_V  0x1
#define SPI_MEM_FDUMMY_OUT_S  3

#define SPI_MEM_CTRL1_REG(i)          (REG_SPI_MEM_BASE(i) + 0x00C)
/* SPI_MEM_RXFIFO_full_ERR:RO；位位置：[31]；默认值：1’b0；*/
/*description:1:SPI0 RX FIFO写满错误Cache/EDMA未读取所有数据。0：无错误。*/
#define SPI_MEM_RXFIFO_WFULL_ERR  (BIT(31))
#define SPI_MEM_RXFIFO_WFULL_ERR_M  (BIT(31))
#define SPI_MEM_RXFIFO_WFULL_ERR_V  0x1
#define SPI_MEM_RXFIFO_WFULL_ERR_S  31
/* SPI_MEM_RXFIFO_RST:WT；位位置：[30]；默认值：1’b0；*/
/*描述：SPI0 RX FIFO复位信号。*/
#define SPI_MEM_RXFIFO_RST  (BIT(30))
#define SPI_MEM_RXFIFO_RST_M  (BIT(30))
#define SPI_MEM_RXFIFO_RST_V  0x1
#define SPI_MEM_RXFIFO_RST_S  30
/* SPI_MEM_CS_HOLD_DLY_RES:R/W；位位置：[11:2]；默认值：10'h3ff；*/
/*description:发送RES/DP/HPM命令后，SPI1等待（SPI_MEM_CS_HOLD_DELAY_RES[9:0]512）SPI_CLK周期。*/
#define SPI_MEM_CS_HOLD_DLY_RES  0x000003FF
#define SPI_MEM_CS_HOLD_DLY_RES_M  ((SPI_MEM_CS_HOLD_DLY_RES_V)<<(SPI_MEM_CS_HOLD_DLY_RES_S))
#define SPI_MEM_CS_HOLD_DLY_RES_V  0x3FF
#define SPI_MEM_CS_HOLD_DLY_RES_S  2
/* SPI_MEM_CLK_MODE：R/W；位位置：[1:0]；默认值：2'h0；*/
/*description:SPI时钟模式位。0:当CS不活动时SPI时钟关闭1:在CS不活动后SPI时钟延迟一个周期2:在CS不激活后SPI时钟推迟两个周期3:SPI时钟始终打开。*/
#define SPI_MEM_CLK_MODE  0x00000003
#define SPI_MEM_CLK_MODE_M  ((SPI_MEM_CLK_MODE_V)<<(SPI_MEM_CLK_MODE_S))
#define SPI_MEM_CLK_MODE_V  0x3
#define SPI_MEM_CLK_MODE_S  0

#define SPI_MEM_CTRL2_REG(i)          (REG_SPI_MEM_BASE(i) + 0x010)
/* SPI_MEM_SYNC_RESET:WT；位位置：[31]；默认值：1’b0；*/
/*description:将重置FSM。*/
#define SPI_MEM_SYNC_RESET  (BIT(31))
#define SPI_MEM_SYNC_RESET_M  (BIT(31))
#define SPI_MEM_SYNC_RESET_V  0x1
#define SPI_MEM_SYNC_RESET_S  31
/* SPI_MEM_CS_HOLD_DELAY：R/W；位位置：[30:25]；默认值：6'd0；*/
/*描述：这些位用于设置访问闪存时SPI突发传输之间的最小CS高时间tSHSL。tSHSL是（SPI_MEM_CS_HOLD_DELAY[5:0]+1）MSPI核心时钟周期。*/
#define SPI_MEM_CS_HOLD_DELAY  0x0000003F
#define SPI_MEM_CS_HOLD_DELAY_M  ((SPI_MEM_CS_HOLD_DELAY_V)<<(SPI_MEM_CS_HOLD_DELAY_S))
#define SPI_MEM_CS_HOLD_DELAY_V  0x3F
#define SPI_MEM_CS_HOLD_DELAY_S  25
/* SPI_MEM_CS_HOLD_TIME:R/W；比特位置：[9:5]；默认值：5'h1；*/
/*描述：Spi cs信号被Spi时钟延迟为无效，该位与Spi_mem_cs_hold位组合。*/
#define SPI_MEM_CS_HOLD_TIME  0x0000001F
#define SPI_MEM_CS_HOLD_TIME_M  ((SPI_MEM_CS_HOLD_TIME_V)<<(SPI_MEM_CS_HOLD_TIME_S))
#define SPI_MEM_CS_HOLD_TIME_V  0x1F
#define SPI_MEM_CS_HOLD_TIME_S  5
/* SPI_MEM_CS_SETUP_TIME:R/W；位位置：[4:0]；默认值：5'h1；*/
/*描述：spi时钟准备阶段的（周期-1）此位与spi_mem_cs_setup位组合。*/
#define SPI_MEM_CS_SETUP_TIME  0x0000001F
#define SPI_MEM_CS_SETUP_TIME_M  ((SPI_MEM_CS_SETUP_TIME_V)<<(SPI_MEM_CS_SETUP_TIME_S))
#define SPI_MEM_CS_SETUP_TIME_V  0x1F
#define SPI_MEM_CS_SETUP_TIME_S  0

#define SPI_MEM_CLOCK_REG(i)          (REG_SPI_MEM_BASE(i) + 0x014)
/* SPI_MEM_CLK_EQU_SYSCLK:R/W；位位置：[31]；默认值：1’b0；*/
/*description:将此位设置为1分割模式。为spi1保留*/
#define SPI_MEM_CLK_EQU_SYSCLK  (BIT(31))
#define SPI_MEM_CLK_EQU_SYSCLK_M  (BIT(31))
#define SPI_MEM_CLK_EQU_SYSCLK_V  0x1
#define SPI_MEM_CLK_EQU_SYSCLK_S  31
/* SPI_MEM_CLKCNT_N:R/W；比特位置：[23:16]；默认值：8'h3；*/
/*description:在主模式下，它是spi_mem_clk的除法器。因此spi_mem_clk频率为系统/（spi_mem_clkcnt_N+1）*/
#define SPI_MEM_CLKCNT_N  0x000000FF
#define SPI_MEM_CLKCNT_N_M  ((SPI_MEM_CLKCNT_N_V)<<(SPI_MEM_CLKCNT_N_S))
#define SPI_MEM_CLKCNT_N_V  0xFF
#define SPI_MEM_CLKCNT_N_S  16
/* SPI_MEM_CLKCNT_H:R/W；比特位置：[15:8]；默认值：8'h1；*/
/*description:在主模式下，它必须是floor（（spi_mem_clkcnt_N+1）/2-1）。*/
#define SPI_MEM_CLKCNT_H  0x000000FF
#define SPI_MEM_CLKCNT_H_M  ((SPI_MEM_CLKCNT_H_V)<<(SPI_MEM_CLKCNT_H_S))
#define SPI_MEM_CLKCNT_H_V  0xFF
#define SPI_MEM_CLKCNT_H_S  8
/* SPI_MEM_CLKCNT_L:R/W；位位置：[7:0]；默认值：8'h3；*/
/*description:在主模式下，它必须等于spi_mem_clkcnt_N。*/
#define SPI_MEM_CLKCNT_L  0x000000FF
#define SPI_MEM_CLKCNT_L_M  ((SPI_MEM_CLKCNT_L_V)<<(SPI_MEM_CLKCNT_L_S))
#define SPI_MEM_CLKCNT_L_V  0xFF
#define SPI_MEM_CLKCNT_L_S  0

#define SPI_MEM_USER_REG(i)          (REG_SPI_MEM_BASE(i) + 0x018)
/* SPI_MEM_USR_COMMAND:R/W；位位置：[31]；默认值：1’b1；*/
/*description:此位启用操作的命令阶段。*/
#define SPI_MEM_USR_COMMAND  (BIT(31))
#define SPI_MEM_USR_COMMAND_M  (BIT(31))
#define SPI_MEM_USR_COMMAND_V  0x1
#define SPI_MEM_USR_COMMAND_S  31
/* SPI_MEM_USR_ADDR:R/W；位位置：[30]；默认值：1’b0；*/
/*description:此位启用操作的地址阶段。*/
#define SPI_MEM_USR_ADDR  (BIT(30))
#define SPI_MEM_USR_ADDR_M  (BIT(30))
#define SPI_MEM_USR_ADDR_V  0x1
#define SPI_MEM_USR_ADDR_S  30
/* SPI_MEM_USR_DUMMY:R/W；位位置：[29]；默认值：1’b0；*/
/*description:此位启用操作的虚拟阶段。*/
#define SPI_MEM_USR_DUMMY  (BIT(29))
#define SPI_MEM_USR_DUMMY_M  (BIT(29))
#define SPI_MEM_USR_DUMMY_V  0x1
#define SPI_MEM_USR_DUMMY_S  29
/* SPI_MEM_USR_MISO:R/W；位位置：[28]；默认值：1’b0；*/
/*description:此位启用操作的读取数据阶段。*/
#define SPI_MEM_USR_MISO  (BIT(28))
#define SPI_MEM_USR_MISO_M  (BIT(28))
#define SPI_MEM_USR_MISO_V  0x1
#define SPI_MEM_USR_MISO_S  28
/* SPI_MEM_USR_MOSI:R/W；位位置：[27]；默认值：1’b0；*/
/*description:此位启用操作的写入数据阶段。*/
#define SPI_MEM_USR_MOSI  (BIT(27))
#define SPI_MEM_USR_MOSI_M  (BIT(27))
#define SPI_MEM_USR_MOSI_V  0x1
#define SPI_MEM_USR_MOSI_S  27
/* SPI_MEM_USR_dumm_IDLE:R/W；位位置：[26]；默认值：1’b0；*/
/*描述：当位被启用时，spi时钟在虚拟阶段被禁用。*/
#define SPI_MEM_USR_DUMMY_IDLE  (BIT(26))
#define SPI_MEM_USR_DUMMY_IDLE_M  (BIT(26))
#define SPI_MEM_USR_DUMMY_IDLE_V  0x1
#define SPI_MEM_USR_DUMMY_IDLE_S  26
/* SPI_MEM_USR_MOSI-HIGHPART:R/W；位位置：[25]；默认值：1’b0；*/
/*描述：写入数据阶段仅访问缓冲区的高部分spi_mem_w8～spi_mem-w15。1：启用0：禁用。*/
#define SPI_MEM_USR_MOSI_HIGHPART  (BIT(25))
#define SPI_MEM_USR_MOSI_HIGHPART_M  (BIT(25))
#define SPI_MEM_USR_MOSI_HIGHPART_V  0x1
#define SPI_MEM_USR_MOSI_HIGHPART_S  25
/* SPI_MEM_USR_MISO_HIGHPART:R/W；位位置：[24]；默认值：1’b0；*/
/*描述：读取数据阶段仅访问缓冲区的高部分spi_mem_w8~spi_mem-w15。1：启用0：禁用。*/
#define SPI_MEM_USR_MISO_HIGHPART  (BIT(24))
#define SPI_MEM_USR_MISO_HIGHPART_M  (BIT(24))
#define SPI_MEM_USR_MISO_HIGHPART_V  0x1
#define SPI_MEM_USR_MISO_HIGHPART_S  24
/* SPI_MEM_FWRITE_QIO:R/W；位位置：[15]；默认值：1’b0；*/
/*描述：在写入操作中，地址阶段和读取数据阶段应用4个信号。*/
#define SPI_MEM_FWRITE_QIO  (BIT(15))
#define SPI_MEM_FWRITE_QIO_M  (BIT(15))
#define SPI_MEM_FWRITE_QIO_V  0x1
#define SPI_MEM_FWRITE_QIO_S  15
/* SPI_MEM_FWRITE_DIO:R/W；位位置：[14]；默认值：1’b0；*/
/*描述：在写入操作中，地址阶段和读取数据阶段应用2个信号。*/
#define SPI_MEM_FWRITE_DIO  (BIT(14))
#define SPI_MEM_FWRITE_DIO_M  (BIT(14))
#define SPI_MEM_FWRITE_DIO_V  0x1
#define SPI_MEM_FWRITE_DIO_S  14
/* SPI_MEM_FWRITE_QUAD:R/W；位位置：[13]；默认值：1’b0；*/
/*描述：在写入操作中，读取数据阶段应用4个信号*/
#define SPI_MEM_FWRITE_QUAD  (BIT(13))
#define SPI_MEM_FWRITE_QUAD_M  (BIT(13))
#define SPI_MEM_FWRITE_QUAD_V  0x1
#define SPI_MEM_FWRITE_QUAD_S  13
/* SPI_MEM_frite_DUAL:R/W；位位置：[12]；默认值：1’b0；*/
/*描述：在写入操作中，读取数据阶段应用2个信号*/
#define SPI_MEM_FWRITE_DUAL  (BIT(12))
#define SPI_MEM_FWRITE_DUAL_M  (BIT(12))
#define SPI_MEM_FWRITE_DUAL_V  0x1
#define SPI_MEM_FWRITE_DUAL_S  12
/* SPI_MEM_CK_OUT_EDGE:R/W；位位置：[9]；默认值：1’b0；*/
/*描述：该位与spi_mem_msi_delaymode位组合以设置mosi信号延迟模式。*/
#define SPI_MEM_CK_OUT_EDGE  (BIT(9))
#define SPI_MEM_CK_OUT_EDGE_M  (BIT(9))
#define SPI_MEM_CK_OUT_EDGE_V  0x1
#define SPI_MEM_CK_OUT_EDGE_S  9
/* SPI_MEM_CS_SETUP:R/W；位位置：[7]；默认值：1’b0；*/
/*描述：当spi处于准备阶段时，启用spi cs。1： 启用0：禁用。*/
#define SPI_MEM_CS_SETUP  (BIT(7))
#define SPI_MEM_CS_SETUP_M  (BIT(7))
#define SPI_MEM_CS_SETUP_V  0x1
#define SPI_MEM_CS_SETUP_S  7
/* SPI_MEM_CS_HOLD:R/W；位位置：[6]；默认值：1’b0；*/
/*描述：当spi处于完成阶段时，spi cs保持低。1： 启用0：禁用。*/
#define SPI_MEM_CS_HOLD  (BIT(6))
#define SPI_MEM_CS_HOLD_M  (BIT(6))
#define SPI_MEM_CS_HOLD_V  0x1
#define SPI_MEM_CS_HOLD_S  6

#define SPI_MEM_USER1_REG(i)          (REG_SPI_MEM_BASE(i) + 0x01C)
/* SPI_MEM_USR_ADDR_标题：R/W；位位置：[31:26]；默认值：6'd23；*/
/*description:地址相位的长度（以位为单位）。寄存器值应为（bit_num-1）。*/
#define SPI_MEM_USR_ADDR_BITLEN  0x0000003F
#define SPI_MEM_USR_ADDR_BITLEN_M  ((SPI_MEM_USR_ADDR_BITLEN_V)<<(SPI_MEM_USR_ADDR_BITLEN_S))
#define SPI_MEM_USR_ADDR_BITLEN_V  0x3F
#define SPI_MEM_USR_ADDR_BITLEN_S  26
/* SPI_MEM_USR_DUMMY_CYCLELEN:R/W；比特位置：[5:0]；默认值：6'd7；*/
/*description:伪相位的spi_mem_clk周期长度。寄存器值应为（cycle_num-1）。*/
#define SPI_MEM_USR_DUMMY_CYCLELEN  0x0000003F
#define SPI_MEM_USR_DUMMY_CYCLELEN_M  ((SPI_MEM_USR_DUMMY_CYCLELEN_V)<<(SPI_MEM_USR_DUMMY_CYCLELEN_S))
#define SPI_MEM_USR_DUMMY_CYCLELEN_V  0x3F
#define SPI_MEM_USR_DUMMY_CYCLELEN_S  0

#define SPI_MEM_USER2_REG(i)          (REG_SPI_MEM_BASE(i) + 0x020)
/* SPI_MEM_USR_COMMAND_BITLEN:R/W；位位置：[31:28]；默认值：4'd7；*/
/*description:命令阶段的长度（以位为单位）。寄存器值应为（bit_num-1）*/
#define SPI_MEM_USR_COMMAND_BITLEN  0x0000000F
#define SPI_MEM_USR_COMMAND_BITLEN_M  ((SPI_MEM_USR_COMMAND_BITLEN_V)<<(SPI_MEM_USR_COMMAND_BITLEN_S))
#define SPI_MEM_USR_COMMAND_BITLEN_V  0xF
#define SPI_MEM_USR_COMMAND_BITLEN_S  28
/* SPI_MEM_USR_COMMAND_VALUE:R/W；比特位置：[15:0]；默认值：16'b0；*/
/*description:命令的值。*/
#define SPI_MEM_USR_COMMAND_VALUE  0x0000FFFF
#define SPI_MEM_USR_COMMAND_VALUE_M  ((SPI_MEM_USR_COMMAND_VALUE_V)<<(SPI_MEM_USR_COMMAND_VALUE_S))
#define SPI_MEM_USR_COMMAND_VALUE_V  0xFFFF
#define SPI_MEM_USR_COMMAND_VALUE_S  0

#define SPI_MEM_MOSI_DLEN_REG(i)          (REG_SPI_MEM_BASE(i) + 0x024)
/* SPI_MEM_USR_MOSI_ditlen:R/W；位位置：[9:0]；默认值：10'0；*/
/*description:写入数据的长度（以位为单位）。寄存器值应为（bit_num-1）。*/
#define SPI_MEM_USR_MOSI_DBITLEN  0x000003FF
#define SPI_MEM_USR_MOSI_DBITLEN_M  ((SPI_MEM_USR_MOSI_DBITLEN_V)<<(SPI_MEM_USR_MOSI_DBITLEN_S))
#define SPI_MEM_USR_MOSI_DBITLEN_V  0x3FF
#define SPI_MEM_USR_MOSI_DBITLEN_S  0

#define SPI_MEM_MISO_DLEN_REG(i)          (REG_SPI_MEM_BASE(i) + 0x028)
/* SPI_MEM_USR_MISO_DBITLEN:R/W；位位置：[9:0]；默认值：10'0；*/
/*description:读取数据的位长度。寄存器值应为（bit_num-1）。*/
#define SPI_MEM_USR_MISO_DBITLEN  0x000003FF
#define SPI_MEM_USR_MISO_DBITLEN_M  ((SPI_MEM_USR_MISO_DBITLEN_V)<<(SPI_MEM_USR_MISO_DBITLEN_S))
#define SPI_MEM_USR_MISO_DBITLEN_V  0x3FF
#define SPI_MEM_USR_MISO_DBITLEN_S  0

#define SPI_MEM_RD_STATUS_REG(i)          (REG_SPI_MEM_BASE(i) + 0x02C)
/* SPI_MEM_WB_MODE:R/W；比特位置：[23:16]；默认值：8'00；*/
/*description:快速读取模式中的模式位与spi_mem_fastrd_Mode位组合。*/
#define SPI_MEM_WB_MODE  0x000000FF
#define SPI_MEM_WB_MODE_M  ((SPI_MEM_WB_MODE_V)<<(SPI_MEM_WB_MODE_S))
#define SPI_MEM_WB_MODE_V  0xFF
#define SPI_MEM_WB_MODE_S  16
/* SPI_MEM_STATUS:R/W/SS；比特位置：[15:0]；默认值：16'b0；*/
/*描述：设置spi_mem_flash_rdsr位和spi_mem_flash_res位时存储该值。*/
#define SPI_MEM_STATUS  0x0000FFFF
#define SPI_MEM_STATUS_M  ((SPI_MEM_STATUS_V)<<(SPI_MEM_STATUS_S))
#define SPI_MEM_STATUS_V  0xFFFF
#define SPI_MEM_STATUS_S  0

#define SPI_MEM_MISC_REG(i)          (REG_SPI_MEM_BASE(i) + 0x034)
/* SPI_MEM_CS_KEEP_ACTIVE:R/W；位位置：[10]；默认值：1’b0；*/
/*描述：设置位时，spi cs线保持低电平。*/
#define SPI_MEM_CS_KEEP_ACTIVE  (BIT(10))
#define SPI_MEM_CS_KEEP_ACTIVE_M  (BIT(10))
#define SPI_MEM_CS_KEEP_ACTIVE_V  0x1
#define SPI_MEM_CS_KEEP_ACTIVE_S  10
/* SPI_MEM_CK_inidle_EDGE：R/W；位位置：[9]；默认值：1’b0；*/
/*描述：1：空闲时spi-clk线为高0：空闲时spi-clk线路为低*/
#define SPI_MEM_CK_IDLE_EDGE  (BIT(9))
#define SPI_MEM_CK_IDLE_EDGE_M  (BIT(9))
#define SPI_MEM_CK_IDLE_EDGE_V  0x1
#define SPI_MEM_CK_IDLE_EDGE_S  9
/* SPI_MEM_SLV_ST_TRANS_END_INT_ENA:R/W；位位置：[6]；默认值：1’b0；*/
/*描述：该位用于启用spi0_slv_st控制传输的中断。*/
#define SPI_MEM_SLV_ST_TRANS_END_INT_ENA  (BIT(6))
#define SPI_MEM_SLV_ST_TRANS_END_INT_ENA_M  (BIT(6))
#define SPI_MEM_SLV_ST_TRANS_END_INT_ENA_V  0x1
#define SPI_MEM_SLV_ST_TRANS_END_INT_ENA_S  6
/* SPI_MEM_SLV_ST_TRANS_END：R/W/SS；位位置：[5]；默认值：1’b0；*/
/*description:该位用于指示完成了spi0_slv_st控制的传输。*/
#define SPI_MEM_SLV_ST_TRANS_END  (BIT(5))
#define SPI_MEM_SLV_ST_TRANS_END_M  (BIT(5))
#define SPI_MEM_SLV_ST_TRANS_END_V  0x1
#define SPI_MEM_SLV_ST_TRANS_END_S  5
/* SPI_MEM_CSPI_ST_TRANS_END_INT_ENA:R/W；位位置：[4]；默认值：1’b0；*/
/*描述：该位用于启用SPI0 cspi_st控制传输的中断。*/
#define SPI_MEM_CSPI_ST_TRANS_END_INT_ENA  (BIT(4))
#define SPI_MEM_CSPI_ST_TRANS_END_INT_ENA_M  (BIT(4))
#define SPI_MEM_CSPI_ST_TRANS_END_INT_ENA_V  0x1
#define SPI_MEM_CSPI_ST_TRANS_END_INT_ENA_S  4
/* SPI_MEM_CSPI_ST_TRANS_END：R/W/SS；位位置：[3]；默认值：1’b0；*/
/*描述：该位用于指示SPI0 cspi_st控制的传输已完成。*/
#define SPI_MEM_CSPI_ST_TRANS_END  (BIT(3))
#define SPI_MEM_CSPI_ST_TRANS_END_M  (BIT(3))
#define SPI_MEM_CSPI_ST_TRANS_END_V  0x1
#define SPI_MEM_CSPI_ST_TRANS_END_S  3
/* SPI_MEM_TRANS_END_INT_ENA:R/W；位位置：[2]；默认值：1’b0；*/
/*描述：该位用于启用SPI0 em_st控制传输的中断。*/
#define SPI_MEM_TRANS_END_INT_ENA  (BIT(2))
#define SPI_MEM_TRANS_END_INT_ENA_M  (BIT(2))
#define SPI_MEM_TRANS_END_INT_ENA_V  0x1
#define SPI_MEM_TRANS_END_INT_ENA_S  2
/* SPI_MEM_CS1_DIS:R/W；位位置：[1]；默认值：1’b1；*/
/*描述：SPI_CS1引脚启用1：禁用SPI_CS1 0：SPI_CS1引脚激活以选择SPI设备，如闪存外部RAM等。*/
#define SPI_MEM_CS1_DIS  (BIT(1))
#define SPI_MEM_CS1_DIS_M  (BIT(1))
#define SPI_MEM_CS1_DIS_V  0x1
#define SPI_MEM_CS1_DIS_S  1
/* SPI_MEM_CS0_DIS:R/W；位位置：[0]；默认值：1’b0；*/
/*描述：SPI_CS0引脚启用1：禁用SPI_CS00：SPI_CSO引脚激活以选择SPI设备，如闪存外部RAM等。*/
#define SPI_MEM_CS0_DIS  (BIT(0))
#define SPI_MEM_CS0_DIS_M  (BIT(0))
#define SPI_MEM_CS0_DIS_V  0x1
#define SPI_MEM_CS0_DIS_S  0

#define SPI_MEM_TX_CRC_REG(i)          (REG_SPI_MEM_BASE(i) + 0x038)
/* SPI_MEM_TX_CRC_DATA:RO；位位置：[31:0]；默认值：32'ffffffff；*/
/*description:对于SPI1，crc32的值。*/
#define SPI_MEM_TX_CRC_DATA  0xFFFFFFFF
#define SPI_MEM_TX_CRC_DATA_M  ((SPI_MEM_TX_CRC_DATA_V)<<(SPI_MEM_TX_CRC_DATA_S))
#define SPI_MEM_TX_CRC_DATA_V  0xFFFFFFFF
#define SPI_MEM_TX_CRC_DATA_S  0

#define SPI_MEM_CACHE_FCTRL_REG(i)          (REG_SPI_MEM_BASE(i) + 0x03C)
/* SPI_MEM_FADDR_QUAD:R/W；位位置：[8]；默认值：1’b0；*/
/*描述：对于SPI1地址相位，应用4个信号。1： 启用0：禁用。该位与spi_mem_fread_qio相同。*/
#define SPI_MEM_FADDR_QUAD  (BIT(8))
#define SPI_MEM_FADDR_QUAD_M  (BIT(8))
#define SPI_MEM_FADDR_QUAD_V  0x1
#define SPI_MEM_FADDR_QUAD_S  8
/* SPI_MEM_FDOUT_QUAD:R/W；位位置：[7]；默认值：1’b0；*/
/*描述：对于SPI1双相位，应用4个信号。1： 启用0：禁用。该位与spi_mem_fread_qio相同。*/
#define SPI_MEM_FDOUT_QUAD  (BIT(7))
#define SPI_MEM_FDOUT_QUAD_M  (BIT(7))
#define SPI_MEM_FDOUT_QUAD_V  0x1
#define SPI_MEM_FDOUT_QUAD_S  7
/* SPI_MEM_FDIN_QUAD:R/W；位位置：[6]；默认值：1’b0；*/
/*描述：对于SPI1反相应用4个信号。1： 启用0：禁用。该位与spi_mem_fread_qio相同。*/
#define SPI_MEM_FDIN_QUAD  (BIT(6))
#define SPI_MEM_FDIN_QUAD_M  (BIT(6))
#define SPI_MEM_FDIN_QUAD_V  0x1
#define SPI_MEM_FDIN_QUAD_S  6
/* SPI_MEM_FADDR_DUAL:R/W；位位置：[5]；默认值：1’b0；*/
/*描述：对于SPI1地址相位，应用2个信号。1： 启用0：禁用。该位与spi_mem_fread_dio相同。*/
#define SPI_MEM_FADDR_DUAL  (BIT(5))
#define SPI_MEM_FADDR_DUAL_M  (BIT(5))
#define SPI_MEM_FADDR_DUAL_V  0x1
#define SPI_MEM_FADDR_DUAL_S  5
/* SPI_MEM_FDOUT_DUAL:R/W；位位置：[4]；默认值：1’b0；*/
/*描述：对于SPI1双相位，应用2个信号。1： 启用0：禁用。该位与spi_mem_fread_dio相同。*/
#define SPI_MEM_FDOUT_DUAL  (BIT(4))
#define SPI_MEM_FDOUT_DUAL_M  (BIT(4))
#define SPI_MEM_FDOUT_DUAL_V  0x1
#define SPI_MEM_FDOUT_DUAL_S  4
/* SPI_MEM_FDIN_DUAL:R/W；位位置：[3]；默认值：1’b0；*/
/*描述：对于SPI1反相应用2个信号。1： 启用0：禁用。该位与spi_mem_fread_dio相同。*/
#define SPI_MEM_FDIN_DUAL  (BIT(3))
#define SPI_MEM_FDIN_DUAL_M  (BIT(3))
#define SPI_MEM_FDIN_DUAL_V  0x1
#define SPI_MEM_FDIN_DUAL_S  3
/* SPI_MEM_CACHE_FLASH_USR_CMD:R/W；位位置：[2]；默认值：1’b0；*/
/*description:对于用户定义命令1:enable0:disable的SPI0缓存读取闪存。*/
#define SPI_MEM_CACHE_FLASH_USR_CMD  (BIT(2))
#define SPI_MEM_CACHE_FLASH_USR_CMD_M  (BIT(2))
#define SPI_MEM_CACHE_FLASH_USR_CMD_V  0x1
#define SPI_MEM_CACHE_FLASH_USR_CMD_S  2
/* SPI_MEM_CACHE_USR_ADDR_4字节：R/W；位位置：[1]；默认值：1’b0；*/
/*description:对于4字节地址为1:enable0:disable的SPI0缓存读取闪存。*/
#define SPI_MEM_CACHE_USR_ADDR_4BYTE  (BIT(1))
#define SPI_MEM_CACHE_USR_ADDR_4BYTE_M  (BIT(1))
#define SPI_MEM_CACHE_USR_ADDR_4BYTE_V  0x1
#define SPI_MEM_CACHE_USR_ADDR_4BYTE_S  1
/* SPI_MEM_CACHE_REQ_EN:R/W；位位置：[0]；默认值：1’b0；*/
/*description:对于SPI0缓存访问，启用1:启用0:禁用。*/
#define SPI_MEM_CACHE_REQ_EN  (BIT(0))
#define SPI_MEM_CACHE_REQ_EN_M  (BIT(0))
#define SPI_MEM_CACHE_REQ_EN_V  0x1
#define SPI_MEM_CACHE_REQ_EN_S  0

#define SPI_MEM_FSM_REG(i)          (REG_SPI_MEM_BASE(i) + 0x054)
/* SPI_MEM_CSPI_LOCK_DELAY_TIME:R/W；比特位置：[11:7]；默认值：5'd4；*/
/*description:SPI1发送PER后，cspi_st对SPI0/1仲裁器的锁定延迟时间。*/
#define SPI_MEM_CSPI_LOCK_DELAY_TIME  0x0000001F
#define SPI_MEM_CSPI_LOCK_DELAY_TIME_M  ((SPI_MEM_CSPI_LOCK_DELAY_TIME_V)<<(SPI_MEM_CSPI_LOCK_DELAY_TIME_S))
#define SPI_MEM_CSPI_LOCK_DELAY_TIME_V  0x1F
#define SPI_MEM_CSPI_LOCK_DELAY_TIME_S  7
/* SPI_MEM_EM_ST:RO；比特位置：[6:4]；默认值：3'h0；*/
/*description:SPI0主FSM:cspi_st的当前状态。0:空闲状态1:EM_CACHE_GRANT 2:编程/擦除挂起状态3:SPI0读取数据状态4:等待缓存/EDMA发送数据存储在SPI0 TX FIFO 5:SPI0写入数据状态。*/
#define SPI_MEM_EM_ST  0x00000007
#define SPI_MEM_EM_ST_M  ((SPI_MEM_EM_ST_V)<<(SPI_MEM_EM_ST_S))
#define SPI_MEM_EM_ST_V  0x7
#define SPI_MEM_EM_ST_S  4
/* SPI_MEM_CSPI_ST:RO；位位置：[3:0]；默认值：4'0；*/
/*description:SPI0从属FSM:cspi_st的当前状态。0：空闲状态1：准备状态2：发送命令状态3：发送地址状态4：等待状态5：读取数据状态6：写入数据状态7：完成状态8：读取数据结束状态。*/
#define SPI_MEM_CSPI_ST  0x0000000F
#define SPI_MEM_CSPI_ST_M  ((SPI_MEM_CSPI_ST_V)<<(SPI_MEM_CSPI_ST_S))
#define SPI_MEM_CSPI_ST_V  0xF
#define SPI_MEM_CSPI_ST_S  0

#define SPI_MEM_W0_REG(i)          (REG_SPI_MEM_BASE(i) + 0x058)
/* SPI_MEM_BUF0:R/W/SS；位位置：[31:0]；默认值：32'b0；*/
/*描述：数据缓冲区*/
#define SPI_MEM_BUF0  0xFFFFFFFF
#define SPI_MEM_BUF0_M  ((SPI_MEM_BUF0_V)<<(SPI_MEM_BUF0_S))
#define SPI_MEM_BUF0_V  0xFFFFFFFF
#define SPI_MEM_BUF0_S  0

#define SPI_MEM_W1_REG(i)          (REG_SPI_MEM_BASE(i) + 0x05C)
/* SPI_MEM_BUF1:R/W/SS；位位置：[31:0]；默认值：32'b0；*/
/*描述：数据缓冲区*/
#define SPI_MEM_BUF1  0xFFFFFFFF
#define SPI_MEM_BUF1_M  ((SPI_MEM_BUF1_V)<<(SPI_MEM_BUF1_S))
#define SPI_MEM_BUF1_V  0xFFFFFFFF
#define SPI_MEM_BUF1_S  0

#define SPI_MEM_W2_REG(i)          (REG_SPI_MEM_BASE(i) + 0x060)
/* SPI_MEM_BUF2:R/W/SS；位位置：[31:0]；默认值：32'b0；*/
/*描述：数据缓冲区*/
#define SPI_MEM_BUF2  0xFFFFFFFF
#define SPI_MEM_BUF2_M  ((SPI_MEM_BUF2_V)<<(SPI_MEM_BUF2_S))
#define SPI_MEM_BUF2_V  0xFFFFFFFF
#define SPI_MEM_BUF2_S  0

#define SPI_MEM_W3_REG(i)          (REG_SPI_MEM_BASE(i) + 0x064)
/* SPI_MEM_BUF3:R/W/SS；位位置：[31:0]；默认值：32'b0；*/
/*描述：数据缓冲区*/
#define SPI_MEM_BUF3  0xFFFFFFFF
#define SPI_MEM_BUF3_M  ((SPI_MEM_BUF3_V)<<(SPI_MEM_BUF3_S))
#define SPI_MEM_BUF3_V  0xFFFFFFFF
#define SPI_MEM_BUF3_S  0

#define SPI_MEM_W4_REG(i)          (REG_SPI_MEM_BASE(i) + 0x068)
/* SPI_MEM_BUF4:R/W/SS；位位置：[31:0]；默认值：32'b0；*/
/*描述：数据缓冲区*/
#define SPI_MEM_BUF4  0xFFFFFFFF
#define SPI_MEM_BUF4_M  ((SPI_MEM_BUF4_V)<<(SPI_MEM_BUF4_S))
#define SPI_MEM_BUF4_V  0xFFFFFFFF
#define SPI_MEM_BUF4_S  0

#define SPI_MEM_W5_REG(i)          (REG_SPI_MEM_BASE(i) + 0x06C)
/* SPI_MEM_BUF5:R/W/SS；位位置：[31:0]；默认值：32'b0；*/
/*描述：数据缓冲区*/
#define SPI_MEM_BUF5  0xFFFFFFFF
#define SPI_MEM_BUF5_M  ((SPI_MEM_BUF5_V)<<(SPI_MEM_BUF5_S))
#define SPI_MEM_BUF5_V  0xFFFFFFFF
#define SPI_MEM_BUF5_S  0

#define SPI_MEM_W6_REG(i)          (REG_SPI_MEM_BASE(i) + 0x070)
/* SPI_MEM_BUF6:R/W/SS；位位置：[31:0]；默认值：32'b0；*/
/*描述：数据缓冲区*/
#define SPI_MEM_BUF6  0xFFFFFFFF
#define SPI_MEM_BUF6_M  ((SPI_MEM_BUF6_V)<<(SPI_MEM_BUF6_S))
#define SPI_MEM_BUF6_V  0xFFFFFFFF
#define SPI_MEM_BUF6_S  0

#define SPI_MEM_W7_REG(i)          (REG_SPI_MEM_BASE(i) + 0x074)
/* SPI_MEM_BUF7:R/W/SS；位位置：[31:0]；默认值：32'b0；*/
/*描述：数据缓冲区*/
#define SPI_MEM_BUF7  0xFFFFFFFF
#define SPI_MEM_BUF7_M  ((SPI_MEM_BUF7_V)<<(SPI_MEM_BUF7_S))
#define SPI_MEM_BUF7_V  0xFFFFFFFF
#define SPI_MEM_BUF7_S  0

#define SPI_MEM_W8_REG(i)          (REG_SPI_MEM_BASE(i) + 0x078)
/* SPI_MEM_BUF8:R/W/SS；位位置：[31:0]；默认值：32'b0；*/
/*描述：数据缓冲区*/
#define SPI_MEM_BUF8  0xFFFFFFFF
#define SPI_MEM_BUF8_M  ((SPI_MEM_BUF8_V)<<(SPI_MEM_BUF8_S))
#define SPI_MEM_BUF8_V  0xFFFFFFFF
#define SPI_MEM_BUF8_S  0

#define SPI_MEM_W9_REG(i)          (REG_SPI_MEM_BASE(i) + 0x07C)
/* SPI_MEM_BUF9:R/W/SS；位位置：[31:0]；默认值：32'b0；*/
/*描述：数据缓冲区*/
#define SPI_MEM_BUF9  0xFFFFFFFF
#define SPI_MEM_BUF9_M  ((SPI_MEM_BUF9_V)<<(SPI_MEM_BUF9_S))
#define SPI_MEM_BUF9_V  0xFFFFFFFF
#define SPI_MEM_BUF9_S  0

#define SPI_MEM_W10_REG(i)          (REG_SPI_MEM_BASE(i) + 0x080)
/* SPI_MEM_BUF10:R/W/SS；位位置：[31:0]；默认值：32'b0；*/
/*描述：数据缓冲区*/
#define SPI_MEM_BUF10  0xFFFFFFFF
#define SPI_MEM_BUF10_M  ((SPI_MEM_BUF10_V)<<(SPI_MEM_BUF10_S))
#define SPI_MEM_BUF10_V  0xFFFFFFFF
#define SPI_MEM_BUF10_S  0

#define SPI_MEM_W11_REG(i)          (REG_SPI_MEM_BASE(i) + 0x084)
/* SPI_MEM_BUF11:R/W/SS；位位置：[31:0]；默认值：32'b0；*/
/*描述：数据缓冲区*/
#define SPI_MEM_BUF11  0xFFFFFFFF
#define SPI_MEM_BUF11_M  ((SPI_MEM_BUF11_V)<<(SPI_MEM_BUF11_S))
#define SPI_MEM_BUF11_V  0xFFFFFFFF
#define SPI_MEM_BUF11_S  0

#define SPI_MEM_W12_REG(i)          (REG_SPI_MEM_BASE(i) + 0x088)
/* SPI_MEM_BUF12:R/W/SS；位位置：[31:0]；默认值：32'b0；*/
/*描述：数据缓冲区*/
#define SPI_MEM_BUF12  0xFFFFFFFF
#define SPI_MEM_BUF12_M  ((SPI_MEM_BUF12_V)<<(SPI_MEM_BUF12_S))
#define SPI_MEM_BUF12_V  0xFFFFFFFF
#define SPI_MEM_BUF12_S  0

#define SPI_MEM_W13_REG(i)          (REG_SPI_MEM_BASE(i) + 0x08C)
/* SPI_MEM_BUF13:R/W/SS；位位置：[31:0]；默认值：32'b0；*/
/*描述：数据缓冲区*/
#define SPI_MEM_BUF13  0xFFFFFFFF
#define SPI_MEM_BUF13_M  ((SPI_MEM_BUF13_V)<<(SPI_MEM_BUF13_S))
#define SPI_MEM_BUF13_V  0xFFFFFFFF
#define SPI_MEM_BUF13_S  0

#define SPI_MEM_W14_REG(i)          (REG_SPI_MEM_BASE(i) + 0x090)
/* SPI_MEM_BUF14:R/W/SS；位位置：[31:0]；默认值：32'b0；*/
/*描述：数据缓冲区*/
#define SPI_MEM_BUF14  0xFFFFFFFF
#define SPI_MEM_BUF14_M  ((SPI_MEM_BUF14_V)<<(SPI_MEM_BUF14_S))
#define SPI_MEM_BUF14_V  0xFFFFFFFF
#define SPI_MEM_BUF14_S  0

#define SPI_MEM_W15_REG(i)          (REG_SPI_MEM_BASE(i) + 0x094)
/* SPI_MEM_BUF15:R/W/SS；位位置：[31:0]；默认值：32'b0；*/
/*描述：数据缓冲区*/
#define SPI_MEM_BUF15  0xFFFFFFFF
#define SPI_MEM_BUF15_M  ((SPI_MEM_BUF15_V)<<(SPI_MEM_BUF15_S))
#define SPI_MEM_BUF15_V  0xFFFFFFFF
#define SPI_MEM_BUF15_S  0

#define SPI_MEM_FLASH_WAITI_CTRL_REG(i)          (REG_SPI_MEM_BASE(i) + 0x098)
/* SPI_MEM_WAITI-ddummy_CYCLELEN:R/W；比特位置：[15:10]；默认值：6'0；*/
/*description:等待闪存空闲（RDSR）时的虚拟周期长度。*/
#define SPI_MEM_WAITI_DUMMY_CYCLELEN  0x0000003F
#define SPI_MEM_WAITI_DUMMY_CYCLELEN_M  ((SPI_MEM_WAITI_DUMMY_CYCLELEN_V)<<(SPI_MEM_WAITI_DUMMY_CYCLELEN_S))
#define SPI_MEM_WAITI_DUMMY_CYCLELEN_V  0x3F
#define SPI_MEM_WAITI_DUMMY_CYCLELEN_S  10
/* SPI_MEM_WAITI_CMD:R/W；比特位置：[9:2]；默认值：8'h05；*/
/*description:等待闪存空闲（RDSR）的命令。*/
#define SPI_MEM_WAITI_CMD  0x000000FF
#define SPI_MEM_WAITI_CMD_M  ((SPI_MEM_WAITI_CMD_V)<<(SPI_MEM_WAITI_CMD_S))
#define SPI_MEM_WAITI_CMD_V  0xFF
#define SPI_MEM_WAITI_CMD_S  2
/* SPI_MEM_WAITI_dedumm:R/W；位位置：[1]；默认值：1’b0；*/
/*description:等待闪存空闲（RDSR）时的虚拟阶段启用*/
#define SPI_MEM_WAITI_DUMMY  (BIT(1))
#define SPI_MEM_WAITI_DUMMY_M  (BIT(1))
#define SPI_MEM_WAITI_DUMMY_V  0x1
#define SPI_MEM_WAITI_DUMMY_S  1

#define SPI_MEM_FLASH_SUS_CTRL_REG(i)          (REG_SPI_MEM_BASE(i) + 0x09C)
/* SPI_MEM_SUS_TIMEOUT_CNT:R/W；位位置：[31:25]；默认值：7'h4；*/
/*描述：当SPI1检查SPI_MEM_SUS_TIMEOUT_CNT[6:0]次的SUS/SUS1/SUS2位失败时，它将被视为检查通过。*/
#define SPI_MEM_SUS_TIMEOUT_CNT  0x0000007F
#define SPI_MEM_SUS_TIMEOUT_CNT_M  ((SPI_MEM_SUS_TIMEOUT_CNT_V)<<(SPI_MEM_SUS_TIMEOUT_CNT_S))
#define SPI_MEM_SUS_TIMEOUT_CNT_V  0x7F
#define SPI_MEM_SUS_TIMEOUT_CNT_S  25
/* SPI_MEM_PES_END_EN:R/W；位位置：[24]；默认值：1’b0；*/
/*description:1：应检查WIP和SUS/SUS1/SUS2位，以确保闪存的挂起状态。0：只需检查WIP为0。*/
#define SPI_MEM_PES_END_EN  (BIT(24))
#define SPI_MEM_PES_END_EN_M  (BIT(24))
#define SPI_MEM_PES_END_EN_V  0x1
#define SPI_MEM_PES_END_EN_S  24
/* SPI_MEM_PER_END_EN:R/W；位位置：[23]；默认值：1’b0；*/
/*description:1：应检查WIP和SUS/SUS1/SUS2位，以确保闪存的恢复状态。0：只需检查WIP为0。*/
#define SPI_MEM_PER_END_EN  (BIT(23))
#define SPI_MEM_PER_END_EN_M  (BIT(23))
#define SPI_MEM_PER_END_EN_V  0x1
#define SPI_MEM_PER_END_EN_S  23
/* SPI_MEM_FMEM_RD_SUS_2B:R/W；位位置：[22]；默认值：1’b0；*/
/*description:1：检查闪存SUS/SUS1/SUS2状态位时读取两个字节。0：检查闪存SUS/SUS1/SUS2状态位时读取一个字节*/
#define SPI_MEM_FMEM_RD_SUS_2B  (BIT(22))
#define SPI_MEM_FMEM_RD_SUS_2B_M  (BIT(22))
#define SPI_MEM_FMEM_RD_SUS_2B_V  0x1
#define SPI_MEM_FMEM_RD_SUS_2B_S  22
/* SPI_MEM_PESR_END_MSK:R/W；比特位置：[21:6]；默认值：16'h80；*/
/*description:检查SUS/SUS1/SUS2状态位时的掩码值。如果读取的状态值为status_in[15:0]（当仅读取一个字节的数据时，只有status_in[7:0]有效，而当读取两个字节数据时，status_in[15:0]有效）SUS/SUS1/SUS2=status_in[15:0]^SPI_MEM_PESR_END_MSK[15:0]。*/
#define SPI_MEM_PESR_END_MSK  0x0000FFFF
#define SPI_MEM_PESR_END_MSK_M  ((SPI_MEM_PESR_END_MSK_V)<<(SPI_MEM_PESR_END_MSK_S))
#define SPI_MEM_PESR_END_MSK_V  0xFFFF
#define SPI_MEM_PESR_END_MSK_S  6
/* SPI_MEM_FLASH_ppes_EN:R/W；位位置：[5]；默认值：1’b0；*/
/*description:设置此位以启用自动暂停功能。*/
#define SPI_MEM_FLASH_PES_EN  (BIT(5))
#define SPI_MEM_FLASH_PES_EN_M  (BIT(5))
#define SPI_MEM_FLASH_PES_EN_V  0x1
#define SPI_MEM_FLASH_PES_EN_S  5
/* SPI_MEM_PES_PER_EN:R/W；位位置：[4]；默认值：1’b0；*/
/*description:设置此位以启用PES传输触发PES传输选项。如果该位为0，应用程序应在PES完成后发送PER。*/
#define SPI_MEM_PES_PER_EN  (BIT(4))
#define SPI_MEM_PES_PER_EN_M  (BIT(4))
#define SPI_MEM_PES_PER_EN_V  0x1
#define SPI_MEM_PES_PER_EN_S  4
/* SPI_MEM_FLASH_pas_WAIT_EN:R/W；位位置：[3]；默认值：1’b0；*/
/*description:设置此位以启用程序擦除暂停后的SPI1等待（SPI_MEM_CS_HOLD_DELAY_RES[9:0]4）SPI_CLK周期。*/
#define SPI_MEM_FLASH_PES_WAIT_EN  (BIT(3))
#define SPI_MEM_FLASH_PES_WAIT_EN_M  (BIT(3))
#define SPI_MEM_FLASH_PES_WAIT_EN_V  0x1
#define SPI_MEM_FLASH_PES_WAIT_EN_S  3
/* SPI_MEM_FLASH_PER_WAIT_EN:R/W；位位置：[2]；默认值：1’b0；*/
/*description:设置此位以启用程序擦除恢复后的SPI1等待（SPI_MEM_CS_HOLD_DELAY_RES[9:0]4）SPI_CLK周期。*/
#define SPI_MEM_FLASH_PER_WAIT_EN  (BIT(2))
#define SPI_MEM_FLASH_PER_WAIT_EN_M  (BIT(2))
#define SPI_MEM_FLASH_PER_WAIT_EN_V  0x1
#define SPI_MEM_FLASH_PER_WAIT_EN_S  2
/* SPI_MEM_FLASH_PES:R/W/SC；位位置：[1]；默认值：1’b0；*/
/*描述：程序擦除暂停位程序擦除暂停操作将在设置位时触发。操作完成后，该位将被清除。1： 启用0：禁用。*/
#define SPI_MEM_FLASH_PES  (BIT(1))
#define SPI_MEM_FLASH_PES_M  (BIT(1))
#define SPI_MEM_FLASH_PES_V  0x1
#define SPI_MEM_FLASH_PES_S  1
/* SPI_MEM_FLASH_par:R/W/SC；位位置：[0]；默认值：1’b0；*/
/*描述：程序擦除恢复位程序擦除暂停操作将在设置位时触发。操作完成后，该位将被清除。1： 启用0：禁用。*/
#define SPI_MEM_FLASH_PER  (BIT(0))
#define SPI_MEM_FLASH_PER_M  (BIT(0))
#define SPI_MEM_FLASH_PER_V  0x1
#define SPI_MEM_FLASH_PER_S  0

#define SPI_MEM_FLASH_SUS_CMD_REG(i)          (REG_SPI_MEM_BASE(i) + 0x0A0)
/* SPI_MEM_WAIT_PESR命令：R/W；比特位置：[31:16]；默认值：16'h05；*/
/*description:Flash SUS/SUS1/SUS2状态位读取命令。当应检查SUS/SUS1/SUS2位以确保闪存的挂起或恢复状态时，应发送命令。*/
#define SPI_MEM_WAIT_PESR_COMMAND  0x0000FFFF
#define SPI_MEM_WAIT_PESR_COMMAND_M  ((SPI_MEM_WAIT_PESR_COMMAND_V)<<(SPI_MEM_WAIT_PESR_COMMAND_S))
#define SPI_MEM_WAIT_PESR_COMMAND_V  0xFFFF
#define SPI_MEM_WAIT_PESR_COMMAND_S  16
/* SPI_MEM_FLASH_pas_COMMAND:R/W；比特位置：[15:8]；默认值：8'75；*/
/*description:编程/擦除暂停命令。*/
#define SPI_MEM_FLASH_PES_COMMAND  0x000000FF
#define SPI_MEM_FLASH_PES_COMMAND_M  ((SPI_MEM_FLASH_PES_COMMAND_V)<<(SPI_MEM_FLASH_PES_COMMAND_S))
#define SPI_MEM_FLASH_PES_COMMAND_V  0xFF
#define SPI_MEM_FLASH_PES_COMMAND_S  8
/* SPI_MEM_FLASH_PER_COMMAND:R/W；位位置：[7:0]；默认值：8'h7a；*/
/*description:编程/擦除恢复命令。*/
#define SPI_MEM_FLASH_PER_COMMAND  0x000000FF
#define SPI_MEM_FLASH_PER_COMMAND_M  ((SPI_MEM_FLASH_PER_COMMAND_V)<<(SPI_MEM_FLASH_PER_COMMAND_S))
#define SPI_MEM_FLASH_PER_COMMAND_V  0xFF
#define SPI_MEM_FLASH_PER_COMMAND_S  0

#define SPI_MEM_SUS_STATUS_REG(i)          (REG_SPI_MEM_BASE(i) + 0x0A4)
/* SPI_MEM_SPI0_LOCK_EN:R/W；位位置：[7]；默认值：1’b0；*/
/*description:1:启用SPI0锁SPI0/1仲裁器选项。0：禁用。*/
#define SPI_MEM_SPI0_LOCK_EN  (BIT(7))
#define SPI_MEM_SPI0_LOCK_EN_M  (BIT(7))
#define SPI_MEM_SPI0_LOCK_EN_V  0x1
#define SPI_MEM_SPI0_LOCK_EN_S  7
/* SPI_MEM_FLASH_ppes_DLY_128:R/W；位位置：[6]；默认值：1’b0；*/
/*description:当SPI_MEM_FLASH_PES_WAIT_EN为1时有效。1:SPI1在发送PES命令后等待（SPI_MEM_CS_HOLD_DELAY_RES[9:0]128）SPI_CLK周期。0:SPI1在发送PES命令后等待（SPI_MEM_CS_HOLD_DELAY_RES[9:0]*4）SPI_CLK周期。*/
#define SPI_MEM_FLASH_PES_DLY_128  (BIT(6))
#define SPI_MEM_FLASH_PES_DLY_128_M  (BIT(6))
#define SPI_MEM_FLASH_PES_DLY_128_V  0x1
#define SPI_MEM_FLASH_PES_DLY_128_S  6
/* SPI_MEM_FLASH_PER_DLY_128:R/W；位位置：[5]；默认值：1’b0；*/
/*description:当SPI_MEM_FLASH_PER_WAIT_EN为1时有效。1:SPI1在发送PER命令后等待（SPI_MEM_CS_HOLD_DELAY_RES[9:0]128）SPI_CLK周期。0:发送PER命令后，SPI1等待（SPI_MEM_CS_HOLD_DELAY_RES[9:0]*4）SPI_CLK周期。*/
#define SPI_MEM_FLASH_PER_DLY_128  (BIT(5))
#define SPI_MEM_FLASH_PER_DLY_128_M  (BIT(5))
#define SPI_MEM_FLASH_PER_DLY_128_V  0x1
#define SPI_MEM_FLASH_PER_DLY_128_S  5
/* SPI_MEM_FLASH_DP_DLY_128:R/W；位位置：[4]；默认值：1’b0；*/
/*描述：1:SPI1在发送DP命令后等待（SPI_MEM_CS_HOLD_DELAY_RES[9:0]*128）SPI_CLK周期。0:SPI1在发送DP命令后等待（SPI_MEM_CS_HOLD_DELAY_RES[9:0]*4）SPI_CLK周期。*/
#define SPI_MEM_FLASH_DP_DLY_128  (BIT(4))
#define SPI_MEM_FLASH_DP_DLY_128_M  (BIT(4))
#define SPI_MEM_FLASH_DP_DLY_128_V  0x1
#define SPI_MEM_FLASH_DP_DLY_128_S  4
/* SPI_MEM_FLASH_RES_DLY_128:R/W；位位置：[3]；默认值：1’b0；*/
/*描述：1:SPI1在发送RES命令后等待（SPI_MEM_CS_HOLD_DELAY_RES[9:0]*128）SPI_CLK周期。0:发送RES命令后，SPI1等待（SPI_MEM_CS_HOLD_DELAY_RES[9:0]*4）SPI_CLK周期。*/
#define SPI_MEM_FLASH_RES_DLY_128  (BIT(3))
#define SPI_MEM_FLASH_RES_DLY_128_M  (BIT(3))
#define SPI_MEM_FLASH_RES_DLY_128_V  0x1
#define SPI_MEM_FLASH_RES_DLY_128_S  3
/* SPI_MEM_FLASH_HPM_DLY_128:R/W；位位置：[2]；默认值：1’b0；*/
/*描述：1:SPI1在发送HPM命令后等待（SPI_MEM_CS_HOLD_DELAY_RES[9:0]*128）SPI_CLK周期。0:SPI1在发送HPM命令后等待（SPI_MEM_CS_HOLD_DELAY_RES[9:0]*4）SPI_CLK周期。*/
#define SPI_MEM_FLASH_HPM_DLY_128  (BIT(2))
#define SPI_MEM_FLASH_HPM_DLY_128_M  (BIT(2))
#define SPI_MEM_FLASH_HPM_DLY_128_V  0x1
#define SPI_MEM_FLASH_HPM_DLY_128_S  2
/* SPI_MEM_WAIT_PESR_CMD_2B:R/W；位位置：[1]；默认值：1’b0；*/
/*description:1:SPI1发送SPI_MEM_WAIT_PER_COMMAND[15:0]以检查SUS/SUS1/SUS2位。0:SPI1发送SPI_MEM_WAIT_PER_COMMAND[7:0]以检查SUS/SUS1/SUS2位。*/
#define SPI_MEM_WAIT_PESR_CMD_2B  (BIT(1))
#define SPI_MEM_WAIT_PESR_CMD_2B_M  (BIT(1))
#define SPI_MEM_WAIT_PESR_CMD_2B_V  0x1
#define SPI_MEM_WAIT_PESR_CMD_2B_S  1
/* SPI_MEM_FLASH_SUS:R/W/SS/SC；位位置：[0]；默认值：1'0；*/
/*description:flash suspend的状态仅在SPI1中使用。*/
#define SPI_MEM_FLASH_SUS  (BIT(0))
#define SPI_MEM_FLASH_SUS_M  (BIT(0))
#define SPI_MEM_FLASH_SUS_V  0x1
#define SPI_MEM_FLASH_SUS_S  0

#define SPI_MEM_TIMING_CALI_REG(i)          (REG_SPI_MEM_BASE(i) + 0x0A8)
/* SPI_MEM_EXTRA_DUMMY_CYCLELEN:R/W；位位置：[4:2]；默认值：3'd0；*/
/*描述：为spi时钟校准添加额外的伪spi时钟周期长度。*/
#define SPI_MEM_EXTRA_DUMMY_CYCLELEN  0x00000007
#define SPI_MEM_EXTRA_DUMMY_CYCLELEN_M  ((SPI_MEM_EXTRA_DUMMY_CYCLELEN_V)<<(SPI_MEM_EXTRA_DUMMY_CYCLELEN_S))
#define SPI_MEM_EXTRA_DUMMY_CYCLELEN_V  0x7
#define SPI_MEM_EXTRA_DUMMY_CYCLELEN_S  2
/* SPI_MEM_timeng_CALI:R/W；位位置：[1]；默认值：1’b0；*/
/*description:该位用于启用所有读取操作的定时自动校准。*/
#define SPI_MEM_TIMING_CALI  (BIT(1))
#define SPI_MEM_TIMING_CALI_M  (BIT(1))
#define SPI_MEM_TIMING_CALI_V  0x1
#define SPI_MEM_TIMING_CALI_S  1
/* SPI_MEM_TIMING_CLK_ENA:R/W；位位置：[0]；默认值：1’b1；*/
/*description:该位用于为所有读取操作启用定时调整时钟。*/
#define SPI_MEM_TIMING_CLK_ENA  (BIT(0))
#define SPI_MEM_TIMING_CLK_ENA_M  (BIT(0))
#define SPI_MEM_TIMING_CLK_ENA_V  0x1
#define SPI_MEM_TIMING_CLK_ENA_S  0

#define SPI_MEM_DIN_MODE_REG(i)          (REG_SPI_MEM_BASE(i) + 0x0AC)
/* SPI_MEM_DIN3_MODE：R/W；位位置：[7:6]；默认值：2'h0；*/
/*描述：输入信号被系统时钟周期延迟0：输入而不延迟1：输入clk_apb的偏倚2输入clk_apb的负边3：输入clk160的偏倚4输入clk_160的负边5：输入spi_clk的高边6：输入spi_clk的低边*/
#define SPI_MEM_DIN3_MODE  0x00000003
#define SPI_MEM_DIN3_MODE_M  ((SPI_MEM_DIN3_MODE_V)<<(SPI_MEM_DIN3_MODE_S))
#define SPI_MEM_DIN3_MODE_V  0x3
#define SPI_MEM_DIN3_MODE_S  6
/* SPI_MEM_din_模式：R/W；比特位置：[5:4]；默认值：2'h0；*/
/*描述：输入信号被系统时钟周期延迟0：输入而不延迟1：输入clk_apb的偏倚2输入clk_apb的负边3：输入clk160的偏倚4输入clk_160的负边5：输入spi_clk的高边6：输入spi_clk的低边*/
#define SPI_MEM_DIN2_MODE  0x00000003
#define SPI_MEM_DIN2_MODE_M  ((SPI_MEM_DIN2_MODE_V)<<(SPI_MEM_DIN2_MODE_S))
#define SPI_MEM_DIN2_MODE_V  0x3
#define SPI_MEM_DIN2_MODE_S  4
/* SPI_MEM_DIN1_MODE：R/W；位位置：[3:2]；默认值：2'h0；*/
/*描述：输入信号被系统时钟周期延迟0：输入而不延迟1：输入clk_apb的偏倚2输入clk_apb的负边3：输入clk160的偏倚4输入clk_160的负边5：输入spi_clk的高边6：输入spi_clk的低边*/
#define SPI_MEM_DIN1_MODE  0x00000003
#define SPI_MEM_DIN1_MODE_M  ((SPI_MEM_DIN1_MODE_V)<<(SPI_MEM_DIN1_MODE_S))
#define SPI_MEM_DIN1_MODE_V  0x3
#define SPI_MEM_DIN1_MODE_S  2
/* SPI_MEM_DIN0_MODE:R/W；位位置：[1:0]；默认值：2'h0；*/
/*描述：输入信号被系统时钟周期延迟0：输入而不延迟1：输入clk_apb的偏倚2输入clk_apb的负边3：输入clk160的偏倚4输入clk_160的负边5：输入spi_clk的高边6：输入spi_clk的低边*/
#define SPI_MEM_DIN0_MODE  0x00000003
#define SPI_MEM_DIN0_MODE_M  ((SPI_MEM_DIN0_MODE_V)<<(SPI_MEM_DIN0_MODE_S))
#define SPI_MEM_DIN0_MODE_V  0x3
#define SPI_MEM_DIN0_MODE_S  0

#define SPI_MEM_DIN_NUM_REG(i)          (REG_SPI_MEM_BASE(i) + 0x0B0)
/* SPI_MEM_DIN3_NUM:R/W；位位置：[7:6]；默认值：2'h0；*/
/*描述：输入信号延迟系统时钟周期0：延迟1个周期1：延迟2个周期。。。*/
#define SPI_MEM_DIN3_NUM  0x00000003
#define SPI_MEM_DIN3_NUM_M  ((SPI_MEM_DIN3_NUM_V)<<(SPI_MEM_DIN3_NUM_S))
#define SPI_MEM_DIN3_NUM_V  0x3
#define SPI_MEM_DIN3_NUM_S  6
/* SPI_MEM_dindi_NUM:R/W；比特位置：[5:4]；默认值：2'h0；*/
/*描述：输入信号延迟系统时钟周期0：延迟1个周期1：延迟2个周期。。。*/
#define SPI_MEM_DIN2_NUM  0x00000003
#define SPI_MEM_DIN2_NUM_M  ((SPI_MEM_DIN2_NUM_V)<<(SPI_MEM_DIN2_NUM_S))
#define SPI_MEM_DIN2_NUM_V  0x3
#define SPI_MEM_DIN2_NUM_S  4
/* SPI_MEM_DIN1_NUM：随机；位位置：[3:2]；默认值：2'h0；*/
/*描述：输入信号延迟系统时钟周期0：延迟1个周期1：延迟2个周期。。。*/
#define SPI_MEM_DIN1_NUM  0x00000003
#define SPI_MEM_DIN1_NUM_M  ((SPI_MEM_DIN1_NUM_V)<<(SPI_MEM_DIN1_NUM_S))
#define SPI_MEM_DIN1_NUM_V  0x3
#define SPI_MEM_DIN1_NUM_S  2
/* SPI_MEM_DIN0_NUM:R/W；位位置：[1:0]；默认值：2'h0；*/
/*描述：输入信号延迟系统时钟周期0：延迟1个周期1：延迟2个周期。。。*/
#define SPI_MEM_DIN0_NUM  0x00000003
#define SPI_MEM_DIN0_NUM_M  ((SPI_MEM_DIN0_NUM_V)<<(SPI_MEM_DIN0_NUM_S))
#define SPI_MEM_DIN0_NUM_V  0x3
#define SPI_MEM_DIN0_NUM_S  0

#define SPI_MEM_DOUT_MODE_REG(i)          (REG_SPI_MEM_BASE(i) + 0x0B4)
/* SPI_MEM_DOUT3_MODE：R/W；位位置：[3]；默认值：1'0；*/
/*描述：输出信号被系统时钟周期延迟0：无延迟输出1：带clk_apb的偏序输出2：带clk _apb的负边输出3：带clk160的偏序的输出4：带clk260的负边的输出5：带spi_clk的高边输出6：带spi_clk的低边输出*/
#define SPI_MEM_DOUT3_MODE  (BIT(3))
#define SPI_MEM_DOUT3_MODE_M  (BIT(3))
#define SPI_MEM_DOUT3_MODE_V  0x1
#define SPI_MEM_DOUT3_MODE_S  3
/* SPI_MEM_DOUT2_MODE:R/W；位位置：[2]；默认值：1'0；*/
/*描述：输出信号被系统时钟周期延迟0：无延迟输出1：带clk_apb的偏序输出2：带clk _apb的负边输出3：带clk160的偏序的输出4：带clk260的负边的输出5：带spi_clk的高边输出6：带spi_clk的低边输出*/
#define SPI_MEM_DOUT2_MODE  (BIT(2))
#define SPI_MEM_DOUT2_MODE_M  (BIT(2))
#define SPI_MEM_DOUT2_MODE_V  0x1
#define SPI_MEM_DOUT2_MODE_S  2
/* SPI_MEM_DOUT1_MODE：R/W；位位置：[1]；默认值：1'0；*/
/*描述：输出信号被系统时钟周期延迟0：无延迟输出1：带clk_apb的偏序输出2：带clk _apb的负边输出3：带clk160的偏序的输出4：带clk260的负边的输出5：带spi_clk的高边输出6：带spi_clk的低边输出*/
#define SPI_MEM_DOUT1_MODE  (BIT(1))
#define SPI_MEM_DOUT1_MODE_M  (BIT(1))
#define SPI_MEM_DOUT1_MODE_V  0x1
#define SPI_MEM_DOUT1_MODE_S  1
/* SPI_MEM_DOUT0_MODE:R/W；位位置：[0]；默认值：1'0；*/
/*描述：输出信号被系统时钟周期延迟0：无延迟输出1：带clk_apb的偏序输出2：带clk _apb的负边输出3：带clk160的偏序的输出4：带clk260的负边的输出5：带spi_clk的高边输出6：带spi_clk的低边输出*/
#define SPI_MEM_DOUT0_MODE  (BIT(0))
#define SPI_MEM_DOUT0_MODE_M  (BIT(0))
#define SPI_MEM_DOUT0_MODE_V  0x1
#define SPI_MEM_DOUT0_MODE_S  0

#define SPI_MEM_INT_ENA_REG(i)          (REG_SPI_MEM_BASE(i) + 0x0C0)
/* SPI_MEM_MST_ST_END_INT_ENA:R/W；位位置：[4]；默认值：1’b0；*/
/*description:SPI_MEM_MST_ST_END_INT中断的启用位。*/
#define SPI_MEM_MST_ST_END_INT_ENA  (BIT(4))
#define SPI_MEM_MST_ST_END_INT_ENA_M  (BIT(4))
#define SPI_MEM_MST_ST_END_INT_ENA_V  0x1
#define SPI_MEM_MST_ST_END_INT_ENA_S  4
/* SPI_MEM_SLV_ST_END_INT_ENA:R/W；位位置：[3]；默认值：1’b0；*/
/*description:SPI_MEM_SLV_ST_END_INT中断的启用位。*/
#define SPI_MEM_SLV_ST_END_INT_ENA  (BIT(3))
#define SPI_MEM_SLV_ST_END_INT_ENA_M  (BIT(3))
#define SPI_MEM_SLV_ST_END_INT_ENA_V  0x1
#define SPI_MEM_SLV_ST_END_INT_ENA_S  3
/* SPI_MEM_WPE_END_INT_ENA:R/W；位位置：[2]；默认值：1’b0；*/
/*description:SPI_MEM_WPE_END_INT中断的启用位。*/
#define SPI_MEM_WPE_END_INT_ENA  (BIT(2))
#define SPI_MEM_WPE_END_INT_ENA_M  (BIT(2))
#define SPI_MEM_WPE_END_INT_ENA_V  0x1
#define SPI_MEM_WPE_END_INT_ENA_S  2
/* SPI_MEM_PES_END_INT_ENA:R/W；位位置：[1]；默认值：1’b0；*/
/*description:SPI_MEM_PES_END_INT中断的启用位。*/
#define SPI_MEM_PES_END_INT_ENA  (BIT(1))
#define SPI_MEM_PES_END_INT_ENA_M  (BIT(1))
#define SPI_MEM_PES_END_INT_ENA_V  0x1
#define SPI_MEM_PES_END_INT_ENA_S  1
/* SPI_MEM_PER_END_INT_ENA:R/W；位位置：[0]；默认值：1’b0；*/
/*description:SPI_MEM_PER_END_INT中断的启用位。*/
#define SPI_MEM_PER_END_INT_ENA  (BIT(0))
#define SPI_MEM_PER_END_INT_ENA_M  (BIT(0))
#define SPI_MEM_PER_END_INT_ENA_V  0x1
#define SPI_MEM_PER_END_INT_ENA_S  0

#define SPI_MEM_INT_CLR_REG(i)          (REG_SPI_MEM_BASE(i) + 0x0C4)
/* SPI_MEM_MST_ST_END_INT_CLR:WT；位位置：[4]；默认值：1’b0；*/
/*description:SPI_MEM_MST_ST_END_INT中断的清除位。*/
#define SPI_MEM_MST_ST_END_INT_CLR  (BIT(4))
#define SPI_MEM_MST_ST_END_INT_CLR_M  (BIT(4))
#define SPI_MEM_MST_ST_END_INT_CLR_V  0x1
#define SPI_MEM_MST_ST_END_INT_CLR_S  4
/* SPI_MEM_SLV_ST_END_INT_CLR:WT；位位置：[3]；默认值：1’b0；*/
/*description:SPI_MEM_SLV_ST_END_INT中断的清除位。*/
#define SPI_MEM_SLV_ST_END_INT_CLR  (BIT(3))
#define SPI_MEM_SLV_ST_END_INT_CLR_M  (BIT(3))
#define SPI_MEM_SLV_ST_END_INT_CLR_V  0x1
#define SPI_MEM_SLV_ST_END_INT_CLR_S  3
/* SPI_MEM_WPE_END_INT_CLR:WT；位位置：[2]；默认值：1’b0；*/
/*description:SPI_MEM_WPE_END_INT中断的清除位。*/
#define SPI_MEM_WPE_END_INT_CLR  (BIT(2))
#define SPI_MEM_WPE_END_INT_CLR_M  (BIT(2))
#define SPI_MEM_WPE_END_INT_CLR_V  0x1
#define SPI_MEM_WPE_END_INT_CLR_S  2
/* SPI_MEM_PES_END_INT_CLR:WT；位位置：[1]；默认值：1’b0；*/
/*description:SPI_MEM_PES_END_INT中断的清除位。*/
#define SPI_MEM_PES_END_INT_CLR  (BIT(1))
#define SPI_MEM_PES_END_INT_CLR_M  (BIT(1))
#define SPI_MEM_PES_END_INT_CLR_V  0x1
#define SPI_MEM_PES_END_INT_CLR_S  1
/* SPI_MEM_PER_END_INT_CLR:WT；位位置：[0]；默认值：1’b0；*/
/*description:SPI_MEM_PER_END_INT中断的清除位。*/
#define SPI_MEM_PER_END_INT_CLR  (BIT(0))
#define SPI_MEM_PER_END_INT_CLR_M  (BIT(0))
#define SPI_MEM_PER_END_INT_CLR_V  0x1
#define SPI_MEM_PER_END_INT_CLR_S  0

#define SPI_MEM_INT_RAW_REG(i)          (REG_SPI_MEM_BASE(i) + 0x0C8)
/* SPI_MEM_MST_ST_END_INT_RAW:R/WTC/SS；位位置：[4]；默认值：1’b0；*/
/*description:SPI_MEM_MST_ST_END_INT中断的原始位。1： 当spi1_mst_st从非空闲状态更改为空闲状态时触发。0：其他。*/
#define SPI_MEM_MST_ST_END_INT_RAW  (BIT(4))
#define SPI_MEM_MST_ST_END_INT_RAW_M  (BIT(4))
#define SPI_MEM_MST_ST_END_INT_RAW_V  0x1
#define SPI_MEM_MST_ST_END_INT_RAW_S  4
/* SPI_MEM_SLV_ST_END_INT_RAW:R/WTC/SS；位位置：[3]；默认值：1’b0；*/
/*description:SPI_MEM_SLV_ST_END_INT中断的原始位。1： 当spi1_slv_st从非空闲状态更改为空闲状态时触发。这意味着SPI_CS升高。0：其他*/
#define SPI_MEM_SLV_ST_END_INT_RAW  (BIT(3))
#define SPI_MEM_SLV_ST_END_INT_RAW_M  (BIT(3))
#define SPI_MEM_SLV_ST_END_INT_RAW_V  0x1
#define SPI_MEM_SLV_ST_END_INT_RAW_S  3
/* SPI_MEM_WPE_END_INT_RAW:R/WTC/SS；位位置：[2]；默认值：1’b0；*/
/*description:SPI_MEM_WPE_END_INT中断的原始位。1： 发送WRSR/PP/SE/BE/CE且闪存已空闲时触发。0：其他。*/
#define SPI_MEM_WPE_END_INT_RAW  (BIT(2))
#define SPI_MEM_WPE_END_INT_RAW_M  (BIT(2))
#define SPI_MEM_WPE_END_INT_RAW_V  0x1
#define SPI_MEM_WPE_END_INT_RAW_S  2
/* SPI_MEM_PES_END_INT_RAW:R/WTC/SS；位位置：[1]；默认值：1’b0；*/
/*description:SPI_MEM_PES_END_INT中断的原始位。1： 发送自动暂停命令（0x75）并暂停闪存时触发。0：其他。*/
#define SPI_MEM_PES_END_INT_RAW  (BIT(1))
#define SPI_MEM_PES_END_INT_RAW_M  (BIT(1))
#define SPI_MEM_PES_END_INT_RAW_V  0x1
#define SPI_MEM_PES_END_INT_RAW_S  1
/* SPI_MEM_PER_END_INT_RAW:R/WTC/SS；位位置：[0]；默认值：1’b0；*/
/*description:SPI_MEM_PER_END_INT中断的原始位。1： 发送自动恢复命令（0x7A）并恢复闪存时触发。0：其他。*/
#define SPI_MEM_PER_END_INT_RAW  (BIT(0))
#define SPI_MEM_PER_END_INT_RAW_M  (BIT(0))
#define SPI_MEM_PER_END_INT_RAW_V  0x1
#define SPI_MEM_PER_END_INT_RAW_S  0

#define SPI_MEM_INT_ST_REG(i)          (REG_SPI_MEM_BASE(i) + 0x0CC)
/* SPI_MEM_MST_ST_END_INT_ST:RO；位位置：[4]；默认值：1’b0；*/
/*description:SPI_MEM_MST_ST_END_INT中断的状态位。*/
#define SPI_MEM_MST_ST_END_INT_ST  (BIT(4))
#define SPI_MEM_MST_ST_END_INT_ST_M  (BIT(4))
#define SPI_MEM_MST_ST_END_INT_ST_V  0x1
#define SPI_MEM_MST_ST_END_INT_ST_S  4
/* SPI_MEM_SLV_ST_END_INT_ST:RO；位位置：[3]；默认值：1’b0；*/
/*description:SPI_MEM_SLV_ST_END_INT中断的状态位。*/
#define SPI_MEM_SLV_ST_END_INT_ST  (BIT(3))
#define SPI_MEM_SLV_ST_END_INT_ST_M  (BIT(3))
#define SPI_MEM_SLV_ST_END_INT_ST_V  0x1
#define SPI_MEM_SLV_ST_END_INT_ST_S  3
/* SPI_MEM_WPE_END_INT_ST:RO；位位置：[2]；默认值：1’b0；*/
/*description:SPI_MEM_WPE_END_INT中断的状态位。*/
#define SPI_MEM_WPE_END_INT_ST  (BIT(2))
#define SPI_MEM_WPE_END_INT_ST_M  (BIT(2))
#define SPI_MEM_WPE_END_INT_ST_V  0x1
#define SPI_MEM_WPE_END_INT_ST_S  2
/* SPI_MEM_PES_END_INT_ST:RO；位位置：[1]；默认值：1’b0；*/
/*description:SPI_MEM_PES_END_INT中断的状态位。*/
#define SPI_MEM_PES_END_INT_ST  (BIT(1))
#define SPI_MEM_PES_END_INT_ST_M  (BIT(1))
#define SPI_MEM_PES_END_INT_ST_V  0x1
#define SPI_MEM_PES_END_INT_ST_S  1
/* SPI_MEM_PER_END_INT_ST:RO；位位置：[0]；默认值：1’b0；*/
/*description:SPI_MEM_PER_END_INT中断的状态位。*/
#define SPI_MEM_PER_END_INT_ST  (BIT(0))
#define SPI_MEM_PER_END_INT_ST_M  (BIT(0))
#define SPI_MEM_PER_END_INT_ST_V  0x1
#define SPI_MEM_PER_END_INT_ST_S  0

#define SPI_MEM_CLOCK_GATE_REG(i)          (REG_SPI_MEM_BASE(i) + 0x0DC)
/* SPI_MEM_CLK_EN:R/W；位位置：[0]；默认值：1’b1；*/
/*description:寄存器时钟门使能信号。1： 启用。0：禁用。*/
#define SPI_MEM_CLK_EN  (BIT(0))
#define SPI_MEM_CLK_EN_M  (BIT(0))
#define SPI_MEM_CLK_EN_V  0x1
#define SPI_MEM_CLK_EN_S  0

#define SPI_MEM_CORE_CLK_SEL_REG(i)          (REG_SPI_MEM_BASE(i) + 0x0E0)
/* SPI_MEM_SPI01_CLK_SEL:R/W；位位置：[1:0]；默认值：2'd0；*/
/*描述：当数字系统时钟选择PLL时钟且PLL时钟的频率为480MHz时，reg_spi01_clk_sel:0:SPI0/1模块时钟（clk）的值为80MHz。1： SPI0/1模块时钟（clk）为120MHz。2： SPI0/1模块时钟（clk）160MHz。3： 未使用。当数字系统时钟选择PLL时钟且PLL时钟的频率为320MHz时，reg_spi01_clk_sel:0:SPI0/1模块时钟（clk）的值为80MHz。1： SPI0/1模块时钟（clk）为80MHz。2： SPI0/1模块时钟（clk）160MHz。3： 未使用。*/
#define SPI_MEM_SPI01_CLK_SEL  0x00000003
#define SPI_MEM_SPI01_CLK_SEL_M  ((SPI_MEM_SPI01_CLK_SEL_V)<<(SPI_MEM_SPI01_CLK_SEL_S))
#define SPI_MEM_SPI01_CLK_SEL_V  0x3
#define SPI_MEM_SPI01_CLK_SEL_S  0

#define SPI_MEM_DATE_REG(i)          (REG_SPI_MEM_BASE(i) + 0x3FC)
/* SPI_MEM_DATE:R/W；位位置：[27:0]；默认值：28'h2007170；*/
/*description:版本控制寄存器*/
#define SPI_MEM_DATE  0x0FFFFFFF
#define SPI_MEM_DATE_M  ((SPI_MEM_DATE_V)<<(SPI_MEM_DATE_S))
#define SPI_MEM_DATE_V  0xFFFFFFF
#define SPI_MEM_DATE_S  0

#ifdef __cplusplus
}
#endif



#endif /*_SOC_SPI_MEM_REG_H_ */

