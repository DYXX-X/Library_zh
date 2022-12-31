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
#ifndef _SOC_SPI_MEM_REG_H_
#define _SOC_SPI_MEM_REG_H_


#ifdef __cplusplus
extern "C" {
#endif
#include "soc.h"
#define REG_SPI_MEM_BASE(i)     (DR_REG_SPI0_BASE - (i) * 0x1000)

#define SPI_MEM_CMD_REG(i)          (REG_SPI_MEM_BASE(i) + 0x000)
/* SPI_MEM_FLASH_READ:R/W；位位置：[31]；默认值：1’b0；*/
/*description:读取闪存启用。设置位时，将触发读取闪存操作。操作完成后，该位将被清除。1： 启用0：禁用。*/
#define SPI_MEM_FLASH_READ  (BIT(31))
#define SPI_MEM_FLASH_READ_M  (BIT(31))
#define SPI_MEM_FLASH_READ_V  0x1
#define SPI_MEM_FLASH_READ_S  31
/* SPI_MEM_FLASH_WREN：随机；位位置：[30]；默认值：1’b0；*/
/*description:写入闪存启用。设置位时，将发送写入启用命令。操作完成后，该位将被清除。1： 启用0：禁用。*/
#define SPI_MEM_FLASH_WREN  (BIT(30))
#define SPI_MEM_FLASH_WREN_M  (BIT(30))
#define SPI_MEM_FLASH_WREN_V  0x1
#define SPI_MEM_FLASH_WREN_S  30
/* SPI_MEM_FLASH_WRDI:R/W；位位置：[29]；默认值：1’b0；*/
/*description:写入闪存禁用。设置位时将发送写禁用命令。操作完成后，该位将被清除。1： 启用0：禁用。*/
#define SPI_MEM_FLASH_WRDI  (BIT(29))
#define SPI_MEM_FLASH_WRDI_M  (BIT(29))
#define SPI_MEM_FLASH_WRDI_V  0x1
#define SPI_MEM_FLASH_WRDI_S  29
/* SPI_MEM_FLASH_rid:R/W；位位置：[28]；默认值：1’b0；*/
/*description:读取JEDEC ID。设置位时将发送读取ID命令。操作完成后，该位将被清除。1： 启用0：禁用。*/
#define SPI_MEM_FLASH_RDID  (BIT(28))
#define SPI_MEM_FLASH_RDID_M  (BIT(28))
#define SPI_MEM_FLASH_RDID_V  0x1
#define SPI_MEM_FLASH_RDID_S  28
/* SPI_MEM_FLASH_RDSR:R/W；位位置：[27]；默认值：1’b0；*/
/*description:读取状态寄存器-1。设置位时将触发读取状态操作。操作完成后，该位将被清除。1： 启用0：禁用。*/
#define SPI_MEM_FLASH_RDSR  (BIT(27))
#define SPI_MEM_FLASH_RDSR_M  (BIT(27))
#define SPI_MEM_FLASH_RDSR_V  0x1
#define SPI_MEM_FLASH_RDSR_S  27
/* SPI_MEM_FLASH_WRSR:R/W；位位置：[26]；默认值：1’b0；*/
/*description:写入状态寄存器启用。设置位时将触发写入状态操作。操作完成后，该位将被清除。1： 启用0：禁用。*/
#define SPI_MEM_FLASH_WRSR  (BIT(26))
#define SPI_MEM_FLASH_WRSR_M  (BIT(26))
#define SPI_MEM_FLASH_WRSR_V  0x1
#define SPI_MEM_FLASH_WRSR_S  26
/* SPI_MEM_FLASH_PP:R/W；位位置：[25]；默认值：1’b0；*/
/*description:页面程序启用（要编程的数据为1字节~256字节）。设置位时将触发页面程序操作。一旦操作完成，该位将被清除。1：启用0：禁用。*/
#define SPI_MEM_FLASH_PP  (BIT(25))
#define SPI_MEM_FLASH_PP_M  (BIT(25))
#define SPI_MEM_FLASH_PP_V  0x1
#define SPI_MEM_FLASH_PP_S  25
/* SPI_MEM_FLASH_SE:R/W；位位置：[24]；默认值：1’b0；*/
/*description:扇区擦除启用（4KB）。设置位时将触发扇区擦除操作。操作完成后，该位将被清除。1： 启用0：禁用。*/
#define SPI_MEM_FLASH_SE  (BIT(24))
#define SPI_MEM_FLASH_SE_M  (BIT(24))
#define SPI_MEM_FLASH_SE_V  0x1
#define SPI_MEM_FLASH_SE_S  24
/* SPI_MEM_FLASH_BE:R/W；位位置：[23]；默认值：1’b0；*/
/*description:块擦除启用（32KB）。设置位时将触发块擦除操作。操作完成后，该位将被清除。1： 启用0：禁用。*/
#define SPI_MEM_FLASH_BE  (BIT(23))
#define SPI_MEM_FLASH_BE_M  (BIT(23))
#define SPI_MEM_FLASH_BE_V  0x1
#define SPI_MEM_FLASH_BE_S  23
/* SPI_MEM_FLASH_CE:R/W；位位置：[22]；默认值：1’b0；*/
/*description:芯片擦除启用。设置位时将触发芯片擦除操作。操作完成后，该位将被清除。1： 启用0：禁用。*/
#define SPI_MEM_FLASH_CE  (BIT(22))
#define SPI_MEM_FLASH_CE_M  (BIT(22))
#define SPI_MEM_FLASH_CE_V  0x1
#define SPI_MEM_FLASH_CE_S  22
/* SPI_MEM_FLASH_DP:R/W；位位置：[21]；默认值：1’b0；*/
/*description:驱动Flash关闭电源。设置位时将触发操作。操作完成后，该位将被清除。1： 启用0：禁用。*/
#define SPI_MEM_FLASH_DP  (BIT(21))
#define SPI_MEM_FLASH_DP_M  (BIT(21))
#define SPI_MEM_FLASH_DP_V  0x1
#define SPI_MEM_FLASH_DP_S  21
/* SPI_MEM_FLASH_RES:R/W；位位置：[20]；默认值：1’b0；*/
/*description:此位与reg_resandres位结合，将Flash从断电状态或高性能模式释放，并获取设备ID。一旦操作完成，该位将被清除。1： 启用0：禁用。*/
#define SPI_MEM_FLASH_RES  (BIT(20))
#define SPI_MEM_FLASH_RES_M  (BIT(20))
#define SPI_MEM_FLASH_RES_V  0x1
#define SPI_MEM_FLASH_RES_S  20
/* SPI_MEM_FLASH_HPM:R/W；位位置：[19]；默认值：1’b0；*/
/*description:将Flash驱动到高性能模式。操作完成后，该位将被清除。1： 启用0：禁用。*/
#define SPI_MEM_FLASH_HPM  (BIT(19))
#define SPI_MEM_FLASH_HPM_M  (BIT(19))
#define SPI_MEM_FLASH_HPM_V  0x1
#define SPI_MEM_FLASH_HPM_S  19
/* SPI_MEM_USR:R/W；位位置：[18]；默认值：1’b0；*/
/*description:用户定义命令启用。设置位时将触发操作。操作完成后，该位将被清除。1： 启用0：禁用。*/
#define SPI_MEM_USR  (BIT(18))
#define SPI_MEM_USR_M  (BIT(18))
#define SPI_MEM_USR_V  0x1
#define SPI_MEM_USR_S  18
/* SPI_MEM_FLASH_PE:R/W；位位置：[17]；默认值：1’b0；*/
/*description:在用户模式下，设置为指示将触发编程/擦除操作。该位与spi_mem_usr位组合。操作完成后，该位将被清除。1： 启用0：禁用。*/
#define SPI_MEM_FLASH_PE  (BIT(17))
#define SPI_MEM_FLASH_PE_M  (BIT(17))
#define SPI_MEM_FLASH_PE_V  0x1
#define SPI_MEM_FLASH_PE_S  17

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
/* SPI_MEM_FCMD_OCT:R/W；位位置：[9]；默认值：1’b0；*/
/*description:在命令阶段1：启用0：禁用期间应用8个信号*/
#define SPI_MEM_FCMD_OCT  (BIT(9))
#define SPI_MEM_FCMD_OCT_M  (BIT(9))
#define SPI_MEM_FCMD_OCT_V  0x1
#define SPI_MEM_FCMD_OCT_S  9
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
/* SPI_MEM_FADDR_OCT:R/W；位位置：[6]；默认值：1’b0；*/
/*description:在地址阶段1：启用0：禁用期间应用8个信号*/
#define SPI_MEM_FADDR_OCT  (BIT(6))
#define SPI_MEM_FADDR_OCT_M  (BIT(6))
#define SPI_MEM_FADDR_OCT_V  0x1
#define SPI_MEM_FADDR_OCT_S  6
/* SPI_MEM_FDIN_OCT:R/W；位位置：[5]；默认值：1’b0；*/
/*description:在读取数据阶段1：启用0：禁用期间应用8个信号*/
#define SPI_MEM_FDIN_OCT  (BIT(5))
#define SPI_MEM_FDIN_OCT_M  (BIT(5))
#define SPI_MEM_FDIN_OCT_V  0x1
#define SPI_MEM_FDIN_OCT_S  5
/* SPI_MEM_FDOUT_OCT:R/W；位位置：[4]；默认值：1’b0；*/
/*description:在写入数据阶段1：启用0：禁用期间应用8个信号*/
#define SPI_MEM_FDOUT_OCT  (BIT(4))
#define SPI_MEM_FDOUT_OCT_M  (BIT(4))
#define SPI_MEM_FDOUT_OCT_V  0x1
#define SPI_MEM_FDOUT_OCT_S  4
/* SPI_MEM_FDUMMY_OUT:R/W；位位置：[3]；默认值：1’b0；*/
/*描述：在虚拟阶段，spi的信号电平由spi控制器输出。*/
#define SPI_MEM_FDUMMY_OUT  (BIT(3))
#define SPI_MEM_FDUMMY_OUT_M  (BIT(3))
#define SPI_MEM_FDUMMY_OUT_V  0x1
#define SPI_MEM_FDUMMY_OUT_S  3

#define SPI_MEM_CTRL1_REG(i)          (REG_SPI_MEM_BASE(i) + 0x00C)
/* SPI_MEM_CS_DLY_EDGE:R/W；位位置：[31]；默认值：1’b0；*/
/*描述：该位用于选择spi时钟边沿以修改CS线路定时。*/
#define SPI_MEM_CS_DLY_EDGE  (BIT(31))
#define SPI_MEM_CS_DLY_EDGE_M  (BIT(31))
#define SPI_MEM_CS_DLY_EDGE_V  0x1
#define SPI_MEM_CS_DLY_EDGE_S  31
/* SPI_MEM_CS_DLY_MODE:R/W；位位置：[30:28]；默认值：3'h0；*/
/*描述：cs信号被系统时钟周期延迟0：输出而不延迟1：输出具有clk_apb的偏倚2输出具有clk _apb的负边3：输出具有clk_160的偏倚4输出具有clk160的负边5：输出具有spi_clk*/
#define SPI_MEM_CS_DLY_MODE  0x00000007
#define SPI_MEM_CS_DLY_MODE_M  ((SPI_MEM_CS_DLY_MODE_V)<<(SPI_MEM_CS_DLY_MODE_S))
#define SPI_MEM_CS_DLY_MODE_V  0x7
#define SPI_MEM_CS_DLY_MODE_S  28
/* SPI_MEM_CS_DLY_NUM:R/W；位位置：[27:26]；默认值：2'h0；*/
/*描述：spi_mem_cs信号被系统时钟周期延迟*/
#define SPI_MEM_CS_DLY_NUM  0x00000003
#define SPI_MEM_CS_DLY_NUM_M  ((SPI_MEM_CS_DLY_NUM_V)<<(SPI_MEM_CS_DLY_NUM_S))
#define SPI_MEM_CS_DLY_NUM_V  0x3
#define SPI_MEM_CS_DLY_NUM_S  26
/* SPI_MEM_CS_HOLD_DLY:R/W；比特位置：[25:14]；默认值：12'h1；*/
/*描述：SPI fsm被SPI时钟周期延迟到空闲。*/
#define SPI_MEM_CS_HOLD_DLY  0x00000FFF
#define SPI_MEM_CS_HOLD_DLY_M  ((SPI_MEM_CS_HOLD_DLY_V)<<(SPI_MEM_CS_HOLD_DLY_S))
#define SPI_MEM_CS_HOLD_DLY_V  0xFFF
#define SPI_MEM_CS_HOLD_DLY_S  14
/* SPI_MEM_CS_HOLD_DLY_RES:R/W；比特位置：[13:2]；默认值：12'fff；*/
/*description:当spi时钟启用从待机模式恢复闪存时，恢复闪存的延迟周期。*/
#define SPI_MEM_CS_HOLD_DLY_RES  0x00000FFF
#define SPI_MEM_CS_HOLD_DLY_RES_M  ((SPI_MEM_CS_HOLD_DLY_RES_V)<<(SPI_MEM_CS_HOLD_DLY_RES_S))
#define SPI_MEM_CS_HOLD_DLY_RES_V  0xFFF
#define SPI_MEM_CS_HOLD_DLY_RES_S  2
/* SPI_MEM_CLK_MODE：R/W；位位置：[1:0]；默认值：2'h0；*/
/*description:SPI时钟模式位。0:当CS不活动时SPI时钟关闭1:在CS不活动后SPI时钟延迟一个周期2:在CS不激活后SPI时钟推迟两个周期3:SPI时钟始终打开。*/
#define SPI_MEM_CLK_MODE  0x00000003
#define SPI_MEM_CLK_MODE_M  ((SPI_MEM_CLK_MODE_V)<<(SPI_MEM_CLK_MODE_S))
#define SPI_MEM_CLK_MODE_V  0x3
#define SPI_MEM_CLK_MODE_S  0

#define SPI_MEM_CTRL2_REG(i)          (REG_SPI_MEM_BASE(i) + 0x010)
/* SPI_MEM_SYNC_RESET:R/W；位位置：[31]；默认值：1’b0；*/
/*description:将重置FSM。*/
#define SPI_MEM_SYNC_RESET  (BIT(31))
#define SPI_MEM_SYNC_RESET_M  (BIT(31))
#define SPI_MEM_SYNC_RESET_V  0x1
#define SPI_MEM_SYNC_RESET_S  31
/* SPI_MEM_CS_HOLD_TIME:R/W；比特位置：[25:13]；默认值：13'h1；*/
/*描述：Spi cs信号被Spi时钟延迟为无效，该位与Spi_mem_cs_hold位组合。*/
#define SPI_MEM_CS_HOLD_TIME  0x00001FFF
#define SPI_MEM_CS_HOLD_TIME_M  ((SPI_MEM_CS_HOLD_TIME_V)<<(SPI_MEM_CS_HOLD_TIME_S))
#define SPI_MEM_CS_HOLD_TIME_V  0x1FFF
#define SPI_MEM_CS_HOLD_TIME_S  13
/* SPI_MEM_CS_SETUP_TIME:R/W；位位置：[12:0]；默认值：13'h1；*/
/*描述：spi时钟准备阶段的（周期-1）此位与spi_mem_cs_setup位组合。*/
#define SPI_MEM_CS_SETUP_TIME  0x00001FFF
#define SPI_MEM_CS_SETUP_TIME_M  ((SPI_MEM_CS_SETUP_TIME_V)<<(SPI_MEM_CS_SETUP_TIME_S))
#define SPI_MEM_CS_SETUP_TIME_V  0x1FFF
#define SPI_MEM_CS_SETUP_TIME_S  0

#define SPI_MEM_CLOCK_REG(i)          (REG_SPI_MEM_BASE(i) + 0x014)
/* SPI_MEM_CLK_EQU_SYSCLK:R/W；位位置：[31]；默认值：1’b0；*/
/*description:保留*/
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
/* SPI_MEM_USR_DUMMY_CYCLELEN:R/W；位位置：[7:0]；默认值：8'd7；*/
/*description:伪相位的spi_mem_clk周期长度。寄存器值应为（cycle_num-1）。*/
#define SPI_MEM_USR_DUMMY_CYCLELEN  0x000000FF
#define SPI_MEM_USR_DUMMY_CYCLELEN_M  ((SPI_MEM_USR_DUMMY_CYCLELEN_V)<<(SPI_MEM_USR_DUMMY_CYCLELEN_S))
#define SPI_MEM_USR_DUMMY_CYCLELEN_V  0xFF
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
/* SPI_MEM_USR_MOSI_ditlen:R/W；位位置：[10:0]；默认值：11'0；*/
/*description:写入数据的长度（以位为单位）。寄存器值应为（bit_num-1）。*/
#define SPI_MEM_USR_MOSI_DBITLEN  0x000007FF
#define SPI_MEM_USR_MOSI_DBITLEN_M  ((SPI_MEM_USR_MOSI_DBITLEN_V)<<(SPI_MEM_USR_MOSI_DBITLEN_S))
#define SPI_MEM_USR_MOSI_DBITLEN_V  0x7FF
#define SPI_MEM_USR_MOSI_DBITLEN_S  0

#define SPI_MEM_MISO_DLEN_REG(i)          (REG_SPI_MEM_BASE(i) + 0x028)
/* SPI_MEM_USR_MISO_DBITLEN:R/W；位位置：[10:0]；默认值：11'0；*/
/*description:读取数据的位长度。寄存器值应为（bit_num-1）。*/
#define SPI_MEM_USR_MISO_DBITLEN  0x000007FF
#define SPI_MEM_USR_MISO_DBITLEN_M  ((SPI_MEM_USR_MISO_DBITLEN_V)<<(SPI_MEM_USR_MISO_DBITLEN_S))
#define SPI_MEM_USR_MISO_DBITLEN_V  0x7FF
#define SPI_MEM_USR_MISO_DBITLEN_S  0

#define SPI_MEM_RD_STATUS_REG(i)          (REG_SPI_MEM_BASE(i) + 0x02C)
/* SPI_MEM_WB_MODE:R/W；比特位置：[23:16]；默认值：8'00；*/
/*description:快速读取模式中的模式位与spi_mem_fastrd_Mode位组合。*/
#define SPI_MEM_WB_MODE  0x000000FF
#define SPI_MEM_WB_MODE_M  ((SPI_MEM_WB_MODE_V)<<(SPI_MEM_WB_MODE_S))
#define SPI_MEM_WB_MODE_V  0xFF
#define SPI_MEM_WB_MODE_S  16
/* SPI_MEM_STATUS:R/W；比特位置：[15:0]；默认值：16'b0；*/
/*描述：设置spi_mem_flash_rdsr位和spi_mem_flash_res位时存储该值。*/
#define SPI_MEM_STATUS  0x0000FFFF
#define SPI_MEM_STATUS_M  ((SPI_MEM_STATUS_V)<<(SPI_MEM_STATUS_S))
#define SPI_MEM_STATUS_V  0xFFFF
#define SPI_MEM_STATUS_S  0

#define SPI_MEM_EXT_ADDR_REG(i)          (REG_SPI_MEM_BASE(i) + 0x030)
/* SPI_MEM_EXT_ADDR:R/W；位位置：[31:0]；默认值：32'b0；*/
/*描述：在64位地址模式下，寄存器是较高的32位。*/
#define SPI_MEM_EXT_ADDR  0xFFFFFFFF
#define SPI_MEM_EXT_ADDR_M  ((SPI_MEM_EXT_ADDR_V)<<(SPI_MEM_EXT_ADDR_S))
#define SPI_MEM_EXT_ADDR_V  0xFFFFFFFF
#define SPI_MEM_EXT_ADDR_S  0

#define SPI_MEM_MISC_REG(i)          (REG_SPI_MEM_BASE(i) + 0x034)
/* SPI_MEM_AUTO_PER:R/W；位位置：[11]；默认值：1’b0；*/
/*description:保留*/
#define SPI_MEM_AUTO_PER  (BIT(11))
#define SPI_MEM_AUTO_PER_M  (BIT(11))
#define SPI_MEM_AUTO_PER_V  0x1
#define SPI_MEM_AUTO_PER_S  11
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
/* SPI_MEM_sub_PIN:R/W；位位置：[8]；默认值：1’b0；*/
/*description:对于SPI0，sram连接到SUBPIN。*/
#define SPI_MEM_SSUB_PIN  (BIT(8))
#define SPI_MEM_SSUB_PIN_M  (BIT(8))
#define SPI_MEM_SSUB_PIN_V  0x1
#define SPI_MEM_SSUB_PIN_S  8
/* SPI_MEM_FSUB_PIN:R/W；位位置：[7]；默认值：1’b0；*/
/*description:对于SPI0，闪存连接到SUBPINs。*/
#define SPI_MEM_FSUB_PIN  (BIT(7))
#define SPI_MEM_FSUB_PIN_M  (BIT(7))
#define SPI_MEM_FSUB_PIN_V  0x1
#define SPI_MEM_FSUB_PIN_S  7
/* SPI_MEM_CS_POL:R/W；比特位置：[6:5]；默认值：2’b0；*/
/*描述：在主模式中，位是spi cs线的极性，值等于spi_mem_cs^spi_mem_master_cs_pol。*/
#define SPI_MEM_CS_POL  0x00000003
#define SPI_MEM_CS_POL_M  ((SPI_MEM_CS_POL_V)<<(SPI_MEM_CS_POL_S))
#define SPI_MEM_CS_POL_V  0x3
#define SPI_MEM_CS_POL_S  5
/* SPI_MEM_TRANS_END_INT_ENA:R/W；位位置：[4]；默认值：1’b0；*/
/*description:该位用于启用SPI传输中断。*/
#define SPI_MEM_TRANS_END_INT_ENA  (BIT(4))
#define SPI_MEM_TRANS_END_INT_ENA_M  (BIT(4))
#define SPI_MEM_TRANS_END_INT_ENA_V  0x1
#define SPI_MEM_TRANS_END_INT_ENA_S  4
/* SPI_MEM_TRANS_END:R/W；位位置：[3]；默认值：1’b0；*/
/*description:该位用于指示传输已完成。*/
#define SPI_MEM_TRANS_END  (BIT(3))
#define SPI_MEM_TRANS_END_M  (BIT(3))
#define SPI_MEM_TRANS_END_V  0x1
#define SPI_MEM_TRANS_END_S  3
/* SPI_MEM_CS1_DIS:R/W；位位置：[1]；默认值：1’b1；*/
/*描述：SPI CS1引脚启用1：禁用CS1 0：SPI_mem_CS1信号来自/至CS1引脚*/
#define SPI_MEM_CS1_DIS  (BIT(1))
#define SPI_MEM_CS1_DIS_M  (BIT(1))
#define SPI_MEM_CS1_DIS_V  0x1
#define SPI_MEM_CS1_DIS_S  1
/* SPI_MEM_CS0_DIS:R/W；位位置：[0]；默认值：1’b0；*/
/*描述：SPI CS0引脚启用1：禁用CS0 0：SPI_mem_CS0信号来自/至CS0引脚*/
#define SPI_MEM_CS0_DIS  (BIT(0))
#define SPI_MEM_CS0_DIS_M  (BIT(0))
#define SPI_MEM_CS0_DIS_V  0x1
#define SPI_MEM_CS0_DIS_S  0

#define SPI_MEM_TX_CRC_REG(i)          (REG_SPI_MEM_BASE(i) + 0x038)
/* SPI_MEM_TX_CRC_DATA:RO；位位置：[31:0]；默认值：32'b0；*/
/*description:对于SPI1，crc32的值。*/
#define SPI_MEM_TX_CRC_DATA  0xFFFFFFFF
#define SPI_MEM_TX_CRC_DATA_M  ((SPI_MEM_TX_CRC_DATA_V)<<(SPI_MEM_TX_CRC_DATA_S))
#define SPI_MEM_TX_CRC_DATA_V  0xFFFFFFFF
#define SPI_MEM_TX_CRC_DATA_S  0

#define SPI_MEM_CACHE_FCTRL_REG(i)          (REG_SPI_MEM_BASE(i) + 0x03C)
/* SPI_MEM_FADDR_QUAD:R/W；位位置：[8]；默认值：1’b0；*/
/*描述：对于SPI0闪存地址阶段，应用4个信号。1： 启用0：禁用。该位与spi_mem_fread_qio相同。*/
#define SPI_MEM_FADDR_QUAD  (BIT(8))
#define SPI_MEM_FADDR_QUAD_M  (BIT(8))
#define SPI_MEM_FADDR_QUAD_V  0x1
#define SPI_MEM_FADDR_QUAD_S  8
/* SPI_MEM_FDOUT_QUAD:R/W；位位置：[7]；默认值：1’b0；*/
/*描述：对于SPI0闪存双相，应用4个信号。1： 启用0：禁用。该位与spi_mem_fread_qio相同。*/
#define SPI_MEM_FDOUT_QUAD  (BIT(7))
#define SPI_MEM_FDOUT_QUAD_M  (BIT(7))
#define SPI_MEM_FDOUT_QUAD_V  0x1
#define SPI_MEM_FDOUT_QUAD_S  7
/* SPI_MEM_FDIN_QUAD:R/W；位位置：[6]；默认值：1’b0；*/
/*描述：对于SPI0闪存，相位应用4个信号。1： 启用0：禁用。该位与spi_mem_fread_qio相同。*/
#define SPI_MEM_FDIN_QUAD  (BIT(6))
#define SPI_MEM_FDIN_QUAD_M  (BIT(6))
#define SPI_MEM_FDIN_QUAD_V  0x1
#define SPI_MEM_FDIN_QUAD_S  6
/* SPI_MEM_FADDR_DUAL:R/W；位位置：[5]；默认值：1’b0；*/
/*描述：对于SPI0闪存地址阶段，应用2个信号。1： 启用0：禁用。该位与spi_mem_fread_dio相同。*/
#define SPI_MEM_FADDR_DUAL  (BIT(5))
#define SPI_MEM_FADDR_DUAL_M  (BIT(5))
#define SPI_MEM_FADDR_DUAL_V  0x1
#define SPI_MEM_FADDR_DUAL_S  5
/* SPI_MEM_FDOUT_DUAL:R/W；位位置：[4]；默认值：1’b0；*/
/*描述：对于SPI0闪存双相应用2个信号。1： 启用0：禁用。该位与spi_mem_fread_dio相同。*/
#define SPI_MEM_FDOUT_DUAL  (BIT(4))
#define SPI_MEM_FDOUT_DUAL_M  (BIT(4))
#define SPI_MEM_FDOUT_DUAL_V  0x1
#define SPI_MEM_FDOUT_DUAL_S  4
/* SPI_MEM_FDIN_DUAL:R/W；位位置：[3]；默认值：1’b0；*/
/*描述：对于SPI0闪存，相位应用2个信号。1： 启用0：禁用。该位与spi_mem_fread_dio相同。*/
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
/* SPI_MEM_CACHE_USR_CMD_4BYTE:R/W；位位置：[1]；默认值：1’b0；*/
/*description:对于4字节的SPI0缓存读取闪存，命令1:enable0:disable。*/
#define SPI_MEM_CACHE_USR_CMD_4BYTE  (BIT(1))
#define SPI_MEM_CACHE_USR_CMD_4BYTE_M  (BIT(1))
#define SPI_MEM_CACHE_USR_CMD_4BYTE_V  0x1
#define SPI_MEM_CACHE_USR_CMD_4BYTE_S  1
/* SPI_MEM_CACHE_REQ_EN:R/W；位位置：[0]；默认值：1’b0；*/
/*description:对于SPI0缓存访问，启用1:启用0:禁用。*/
#define SPI_MEM_CACHE_REQ_EN  (BIT(0))
#define SPI_MEM_CACHE_REQ_EN_M  (BIT(0))
#define SPI_MEM_CACHE_REQ_EN_V  0x1
#define SPI_MEM_CACHE_REQ_EN_S  0

#define SPI_MEM_CACHE_SCTRL_REG(i)          (REG_SPI_MEM_BASE(i) + 0x040)
/* SPI_MEM_SRAM_WDUMMY_CYCLELEN:R/W；位位置：[29:22]；默认值：8'b1；*/
/*description:对于SPI0，在sram模式下，它是写入虚拟阶段的长度（以位为单位）。寄存器值应为（bit_num-1）。*/
#define SPI_MEM_SRAM_WDUMMY_CYCLELEN  0x000000FF
#define SPI_MEM_SRAM_WDUMMY_CYCLELEN_M  ((SPI_MEM_SRAM_WDUMMY_CYCLELEN_V)<<(SPI_MEM_SRAM_WDUMMY_CYCLELEN_S))
#define SPI_MEM_SRAM_WDUMMY_CYCLELEN_V  0xFF
#define SPI_MEM_SRAM_WDUMMY_CYCLELEN_S  22
/* SPI_MEM_SRAM_OCT:R/W；位位置：[21]；默认值：1’b0；*/
/*description:保留*/
#define SPI_MEM_SRAM_OCT  (BIT(21))
#define SPI_MEM_SRAM_OCT_M  (BIT(21))
#define SPI_MEM_SRAM_OCT_V  0x1
#define SPI_MEM_SRAM_OCT_S  21
/* SPI_MEM_CACHE_SRAM_USR_WCMD:R/W；位位置：[20]；默认值：1’b1；*/
/*description:对于SPI0在spi-sram模式缓存中为用户定义命令写入sram*/
#define SPI_MEM_CACHE_SRAM_USR_WCMD  (BIT(20))
#define SPI_MEM_CACHE_SRAM_USR_WCMD_M  (BIT(20))
#define SPI_MEM_CACHE_SRAM_USR_WCMD_V  0x1
#define SPI_MEM_CACHE_SRAM_USR_WCMD_S  20
/* SPI_MEM_SRAM_ADDR_标题：R/W；比特位置：[19:14]；默认值：6'd23；*/
/*description:对于SPI0，在sram模式下，它是地址相位的位长度。寄存器值应为（bit_num-1）。*/
#define SPI_MEM_SRAM_ADDR_BITLEN  0x0000003F
#define SPI_MEM_SRAM_ADDR_BITLEN_M  ((SPI_MEM_SRAM_ADDR_BITLEN_V)<<(SPI_MEM_SRAM_ADDR_BITLEN_S))
#define SPI_MEM_SRAM_ADDR_BITLEN_V  0x3F
#define SPI_MEM_SRAM_ADDR_BITLEN_S  14
/* SPI_MEM_SRAM_RDUMMY_CYCLELEN:R/W；比特位置：[13:6]；默认值：8'b1；*/
/*description:对于SPI0，在sram模式下，它是读取伪相位的长度（以位为单位）。寄存器值应为（bit_num-1）。*/
#define SPI_MEM_SRAM_RDUMMY_CYCLELEN  0x000000FF
#define SPI_MEM_SRAM_RDUMMY_CYCLELEN_M  ((SPI_MEM_SRAM_RDUMMY_CYCLELEN_V)<<(SPI_MEM_SRAM_RDUMMY_CYCLELEN_S))
#define SPI_MEM_SRAM_RDUMMY_CYCLELEN_V  0xFF
#define SPI_MEM_SRAM_RDUMMY_CYCLELEN_S  6
/* SPI_MEM_CACHE_SRAM_USR_RCMD:R/W；位位置：[5]；默认值：1’b1；*/
/*description:对于SPI0，在spi-sram模式缓存中读取sram，用于用户定义命令。*/
#define SPI_MEM_CACHE_SRAM_USR_RCMD  (BIT(5))
#define SPI_MEM_CACHE_SRAM_USR_RCMD_M  (BIT(5))
#define SPI_MEM_CACHE_SRAM_USR_RCMD_V  0x1
#define SPI_MEM_CACHE_SRAM_USR_RCMD_S  5
/* SPI_MEM_USR_RD_sramdumm:R/W；位位置：[4]；默认值：1’b1；*/
/*description:对于SPI0，在spi-sram模式中，它是读取操作的虚拟阶段的启用位。*/
#define SPI_MEM_USR_RD_SRAM_DUMMY  (BIT(4))
#define SPI_MEM_USR_RD_SRAM_DUMMY_M  (BIT(4))
#define SPI_MEM_USR_RD_SRAM_DUMMY_V  0x1
#define SPI_MEM_USR_RD_SRAM_DUMMY_S  4
/* SPI_MEM_USR_WR_SRAM虚拟：R/W；位位置：[3]；默认值：1’b0；*/
/*description:对于SPI0，在spi-sram模式中，它是写入操作的虚拟阶段的启用位。*/
#define SPI_MEM_USR_WR_SRAM_DUMMY  (BIT(3))
#define SPI_MEM_USR_WR_SRAM_DUMMY_M  (BIT(3))
#define SPI_MEM_USR_WR_SRAM_DUMMY_V  0x1
#define SPI_MEM_USR_WR_SRAM_DUMMY_S  3
/* SPI_MEM_USR_SRAM_QIO:R/W；位位置：[2]；默认值：1’b0；*/
/*description:对于SPI0在spi-sram模式下，spiquad I/O模式启用1：启用0：禁用*/
#define SPI_MEM_USR_SRAM_QIO  (BIT(2))
#define SPI_MEM_USR_SRAM_QIO_M  (BIT(2))
#define SPI_MEM_USR_SRAM_QIO_V  0x1
#define SPI_MEM_USR_SRAM_QIO_S  2
/* SPI_MEM_USR_SRAM_DIO:R/W；位位置：[1]；默认值：1’b0；*/
/*description:对于SPI0在spi-sram模式下，spi双I/O模式启用1：启用0：禁用*/
#define SPI_MEM_USR_SRAM_DIO  (BIT(1))
#define SPI_MEM_USR_SRAM_DIO_M  (BIT(1))
#define SPI_MEM_USR_SRAM_DIO_V  0x1
#define SPI_MEM_USR_SRAM_DIO_S  1
/* SPI_MEM_CACHE_USR_SCMD_4BYTE:R/W；位位置：[0]；默认值：1’b0；*/
/*description:对于SPI0，在spi-sram模式缓存中读取4字节闪存命令1:enable0:disable。*/
#define SPI_MEM_CACHE_USR_SCMD_4BYTE  (BIT(0))
#define SPI_MEM_CACHE_USR_SCMD_4BYTE_M  (BIT(0))
#define SPI_MEM_CACHE_USR_SCMD_4BYTE_V  0x1
#define SPI_MEM_CACHE_USR_SCMD_4BYTE_S  0

#define SPI_MEM_SRAM_CMD_REG(i)          (REG_SPI_MEM_BASE(i) + 0x044)
/* SPI_MEM_SDUMMY_OUT:R/W；位位置：[22]；默认值：1’b0；*/
/*描述：在虚拟阶段，spi的信号电平由spi控制器输出。*/
#define SPI_MEM_SDUMMY_OUT  (BIT(22))
#define SPI_MEM_SDUMMY_OUT_M  (BIT(22))
#define SPI_MEM_SDUMMY_OUT_V  0x1
#define SPI_MEM_SDUMMY_OUT_S  22
/* SPI_MEM_SCMD_OCT:R/W；位位置：[21]；默认值：1’b0；*/
/*描述：对于SPI0 sram cmd相位应用8个信号。1： 启用0：禁用。*/
#define SPI_MEM_SCMD_OCT  (BIT(21))
#define SPI_MEM_SCMD_OCT_M  (BIT(21))
#define SPI_MEM_SCMD_OCT_V  0x1
#define SPI_MEM_SCMD_OCT_S  21
/* SPI_MEM_SADDR_OCT:R/W；位位置：[20]；默认值：1’b0；*/
/*描述：对于SPI0 sram地址相位，应用4个信号。1： 启用0：禁用。*/
#define SPI_MEM_SADDR_OCT  (BIT(20))
#define SPI_MEM_SADDR_OCT_M  (BIT(20))
#define SPI_MEM_SADDR_OCT_V  0x1
#define SPI_MEM_SADDR_OCT_S  20
/* SPI_MEM_SDOUT_OCT:R/W；位位置：[19]；默认值：1’b0；*/
/*描述：对于SPI0 sram双相位应用8个信号。1： 启用0：禁用。*/
#define SPI_MEM_SDOUT_OCT  (BIT(19))
#define SPI_MEM_SDOUT_OCT_M  (BIT(19))
#define SPI_MEM_SDOUT_OCT_V  0x1
#define SPI_MEM_SDOUT_OCT_S  19
/* SPI_MEM_SDIN_OCT:R/W；位位置：[18]；默认值：1’b0；*/
/*描述：对于SPI0 sram din相位应用8个信号。1： 启用0：禁用。*/
#define SPI_MEM_SDIN_OCT  (BIT(18))
#define SPI_MEM_SDIN_OCT_M  (BIT(18))
#define SPI_MEM_SDIN_OCT_V  0x1
#define SPI_MEM_SDIN_OCT_S  18
/* SPI_MEM_SCMD_QUAD:R/W；位位置：[17]；默认值：1’b0；*/
/*描述：对于SPI0 sram cmd相位应用4个信号。1： 启用0：禁用。该位与spi_mem_usr_sram_qio相同。*/
#define SPI_MEM_SCMD_QUAD  (BIT(17))
#define SPI_MEM_SCMD_QUAD_M  (BIT(17))
#define SPI_MEM_SCMD_QUAD_V  0x1
#define SPI_MEM_SCMD_QUAD_S  17
/* SPI_MEM_SADDR_QUAD:R/W；位位置：[16]；默认值：1’b0；*/
/*描述：对于SPI0 sram地址相位，应用4个信号。1： 启用0：禁用。该位与spi_mem_usr_sram_qio相同。*/
#define SPI_MEM_SADDR_QUAD  (BIT(16))
#define SPI_MEM_SADDR_QUAD_M  (BIT(16))
#define SPI_MEM_SADDR_QUAD_V  0x1
#define SPI_MEM_SADDR_QUAD_S  16
/* SPI_MEM_SDOUT_QUAD:R/W；位位置：[15]；默认值：1’b0；*/
/*描述：对于SPI0 sram双相位应用4个信号。1： 启用0：禁用。该位与spi_mem_usr_sram_qio相同。*/
#define SPI_MEM_SDOUT_QUAD  (BIT(15))
#define SPI_MEM_SDOUT_QUAD_M  (BIT(15))
#define SPI_MEM_SDOUT_QUAD_V  0x1
#define SPI_MEM_SDOUT_QUAD_S  15
/* SPI_MEM_SDIN_QUAD:R/W；位位置：[14]；默认值：1’b0；*/
/*描述：对于SPI0 sram din相位应用4个信号。1： 启用0：禁用。该位与spi_mem_usr_sram_qio相同。*/
#define SPI_MEM_SDIN_QUAD  (BIT(14))
#define SPI_MEM_SDIN_QUAD_M  (BIT(14))
#define SPI_MEM_SDIN_QUAD_V  0x1
#define SPI_MEM_SDIN_QUAD_S  14
/* SPI_MEM_SCMD_DUAL:R/W；位位置：[13]；默认值：1’b0；*/
/*描述：对于SPI0 sram cmd相位应用2个信号。1： 启用0：禁用。该位与spi_mem_usr_sram_dio相同。*/
#define SPI_MEM_SCMD_DUAL  (BIT(13))
#define SPI_MEM_SCMD_DUAL_M  (BIT(13))
#define SPI_MEM_SCMD_DUAL_V  0x1
#define SPI_MEM_SCMD_DUAL_S  13
/* SPI_MEM_SADDR_DUAL:R/W；位位置：[12]；默认值：1’b0；*/
/*描述：对于SPI0 sram地址相位，应用2个信号。1： 启用0：禁用。该位与spi_mem_usr_sram_dio相同。*/
#define SPI_MEM_SADDR_DUAL  (BIT(12))
#define SPI_MEM_SADDR_DUAL_M  (BIT(12))
#define SPI_MEM_SADDR_DUAL_V  0x1
#define SPI_MEM_SADDR_DUAL_S  12
/* SPI_MEM_SDOUT_DUAL:R/W；位位置：[11]；默认值：1’b0；*/
/*描述：对于SPI0 sram双相位应用2个信号。1： 启用0：禁用。该位与spi_mem_usr_sram_dio相同。*/
#define SPI_MEM_SDOUT_DUAL  (BIT(11))
#define SPI_MEM_SDOUT_DUAL_M  (BIT(11))
#define SPI_MEM_SDOUT_DUAL_V  0x1
#define SPI_MEM_SDOUT_DUAL_S  11
/* SPI_MEM_SDIN_DUAL:R/W；位位置：[10]；默认值：1’b0；*/
/*描述：对于SPI0 sram din相位应用2个信号。1： 启用0：禁用。该位与spi_mem_usr_sram_dio相同。*/
#define SPI_MEM_SDIN_DUAL  (BIT(10))
#define SPI_MEM_SDIN_DUAL_M  (BIT(10))
#define SPI_MEM_SDIN_DUAL_V  0x1
#define SPI_MEM_SDIN_DUAL_S  10
/* SPI_MEM_SWB_MODE：R/W；比特位置：[9:2]；默认值：8'b0；*/
/*description:psram快速读取模式中的模式位与spi_mem_fastrd_Mode位组合。*/
#define SPI_MEM_SWB_MODE  0x000000FF
#define SPI_MEM_SWB_MODE_M  ((SPI_MEM_SWB_MODE_V)<<(SPI_MEM_SWB_MODE_S))
#define SPI_MEM_SWB_MODE_V  0xFF
#define SPI_MEM_SWB_MODE_S  2
/* SPI_MEM_SCLK_MODE：R/W；位位置：[1:0]；默认值：2'd0；*/
/*description:SPI时钟模式位。0:当CS不活动时SPI时钟关闭1:在CS不活动后SPI时钟延迟一个周期2:在CS不激活后SPI时钟推迟两个周期3:SPI时钟始终打开。*/
#define SPI_MEM_SCLK_MODE  0x00000003
#define SPI_MEM_SCLK_MODE_M  ((SPI_MEM_SCLK_MODE_V)<<(SPI_MEM_SCLK_MODE_S))
#define SPI_MEM_SCLK_MODE_V  0x3
#define SPI_MEM_SCLK_MODE_S  0

#define SPI_MEM_SRAM_DRD_CMD_REG(i)          (REG_SPI_MEM_BASE(i) + 0x048)
/* SPI_MEM_CACHE_SRAM_USR_RD_CMD_BITLEN:R/W；位位置：[31:28]；默认值：4'0；*/
/*description:对于SPI0，当启用缓存模式时，它是sram命令阶段的位长度。寄存器值应为（bit_num-1）。*/
#define SPI_MEM_CACHE_SRAM_USR_RD_CMD_BITLEN  0x0000000F
#define SPI_MEM_CACHE_SRAM_USR_RD_CMD_BITLEN_M  ((SPI_MEM_CACHE_SRAM_USR_RD_CMD_BITLEN_V)<<(SPI_MEM_CACHE_SRAM_USR_RD_CMD_BITLEN_S))
#define SPI_MEM_CACHE_SRAM_USR_RD_CMD_BITLEN_V  0xF
#define SPI_MEM_CACHE_SRAM_USR_RD_CMD_BITLEN_S  28
/* SPI_MEM_CACHE_SRAM_USR_RD_CMD_VALUE:R/W；比特位置：[15:0]；默认值：16'0；*/
/*description:对于SPI0，当启用缓存模式时，它是sram命令阶段的读取命令值。*/
#define SPI_MEM_CACHE_SRAM_USR_RD_CMD_VALUE  0x0000FFFF
#define SPI_MEM_CACHE_SRAM_USR_RD_CMD_VALUE_M  ((SPI_MEM_CACHE_SRAM_USR_RD_CMD_VALUE_V)<<(SPI_MEM_CACHE_SRAM_USR_RD_CMD_VALUE_S))
#define SPI_MEM_CACHE_SRAM_USR_RD_CMD_VALUE_V  0xFFFF
#define SPI_MEM_CACHE_SRAM_USR_RD_CMD_VALUE_S  0

#define SPI_MEM_SRAM_DWR_CMD_REG(i)          (REG_SPI_MEM_BASE(i) + 0x04C)
/* SPI_MEM_CACHE_SRAM_USR_WR_CMD_BITLEN:R/W；位位置：[31:28]；默认值：4'0；*/
/*description:对于SPI0，当启用缓存模式时，它是sram命令阶段的位。寄存器值应为（bit_num-1）。*/
#define SPI_MEM_CACHE_SRAM_USR_WR_CMD_BITLEN  0x0000000F
#define SPI_MEM_CACHE_SRAM_USR_WR_CMD_BITLEN_M  ((SPI_MEM_CACHE_SRAM_USR_WR_CMD_BITLEN_V)<<(SPI_MEM_CACHE_SRAM_USR_WR_CMD_BITLEN_S))
#define SPI_MEM_CACHE_SRAM_USR_WR_CMD_BITLEN_V  0xF
#define SPI_MEM_CACHE_SRAM_USR_WR_CMD_BITLEN_S  28
/* SPI_MEM_CACHE_SRAM_USR_WR_CMD_VALUE:R/W；比特位置：[15:0]；默认值：16'0；*/
/*description:对于SPI0，当启用缓存模式时，它是sram命令阶段的写入命令值。*/
#define SPI_MEM_CACHE_SRAM_USR_WR_CMD_VALUE  0x0000FFFF
#define SPI_MEM_CACHE_SRAM_USR_WR_CMD_VALUE_M  ((SPI_MEM_CACHE_SRAM_USR_WR_CMD_VALUE_V)<<(SPI_MEM_CACHE_SRAM_USR_WR_CMD_VALUE_S))
#define SPI_MEM_CACHE_SRAM_USR_WR_CMD_VALUE_V  0xFFFF
#define SPI_MEM_CACHE_SRAM_USR_WR_CMD_VALUE_S  0

#define SPI_MEM_SRAM_CLK_REG(i)          (REG_SPI_MEM_BASE(i) + 0x050)
/* SPI_MEM_SCLK_equi_SYSCLK:R/W；位位置：[31]；默认值：1’b0；*/
/*描述：对于SPI0 sram接口1：spi_mem_clk与系统0相等：spi_mem _clk从系统时钟分频。*/
#define SPI_MEM_SCLK_EQU_SYSCLK  (BIT(31))
#define SPI_MEM_SCLK_EQU_SYSCLK_M  (BIT(31))
#define SPI_MEM_SCLK_EQU_SYSCLK_V  0x1
#define SPI_MEM_SCLK_EQU_SYSCLK_S  31
/* SPI_MEM_SCLKCNT_N:R/W；比特位置：[23:16]；默认值：8'h3；*/
/*description:对于SPI0 sram接口，它是spi_mem_clk的除法器。因此spi_mem_clk频率为系统/（spi_mem_clkcnt_N+1）*/
#define SPI_MEM_SCLKCNT_N  0x000000FF
#define SPI_MEM_SCLKCNT_N_M  ((SPI_MEM_SCLKCNT_N_V)<<(SPI_MEM_SCLKCNT_N_S))
#define SPI_MEM_SCLKCNT_N_V  0xFF
#define SPI_MEM_SCLKCNT_N_S  16
/* SPI_MEM_SCLKCNT_H:R/W；比特位置：[15:8]；默认值：8'h1；*/
/*description:对于SPI0 sram接口，它必须是floor（（spi_mem_clkcnt_N+1）/2-1）。*/
#define SPI_MEM_SCLKCNT_H  0x000000FF
#define SPI_MEM_SCLKCNT_H_M  ((SPI_MEM_SCLKCNT_H_V)<<(SPI_MEM_SCLKCNT_H_S))
#define SPI_MEM_SCLKCNT_H_V  0xFF
#define SPI_MEM_SCLKCNT_H_S  8
/* SPI_MEM_SCLKCNT_L:R/W；位位置：[7:0]；默认值：8'h3；*/
/*description:对于SPI0 sram接口，它必须等于spi_mem_clkcnt_N。*/
#define SPI_MEM_SCLKCNT_L  0x000000FF
#define SPI_MEM_SCLKCNT_L_M  ((SPI_MEM_SCLKCNT_L_V)<<(SPI_MEM_SCLKCNT_L_S))
#define SPI_MEM_SCLKCNT_L_V  0xFF
#define SPI_MEM_SCLKCNT_L_S  0

#define SPI_MEM_FSM_REG(i)          (REG_SPI_MEM_BASE(i) + 0x054)
/* SPI_MEM_ST:RO；位位置：[2:0]；默认值：3'b0；*/
/*description:spi状态机的状态。0：空闲状态1：准备状态2：发送命令状态3：发送数据状态4：红色数据状态5：写入数据状态6：等待状态7：完成状态。*/
#define SPI_MEM_ST  0x00000007
#define SPI_MEM_ST_M  ((SPI_MEM_ST_V)<<(SPI_MEM_ST_S))
#define SPI_MEM_ST_V  0x7
#define SPI_MEM_ST_S  0

#define SPI_MEM_W0_REG(i)          (REG_SPI_MEM_BASE(i) + 0x058)
/* SPI_MEM_BUF0:SRW；位位置：[31:0]；默认值：32'b0；*/
/*描述：数据缓冲区*/
#define SPI_MEM_BUF0  0xFFFFFFFF
#define SPI_MEM_BUF0_M  ((SPI_MEM_BUF0_V)<<(SPI_MEM_BUF0_S))
#define SPI_MEM_BUF0_V  0xFFFFFFFF
#define SPI_MEM_BUF0_S  0

#define SPI_MEM_W1_REG(i)          (REG_SPI_MEM_BASE(i) + 0x05C)
/* SPI_MEM_BUF1:SRW；位位置：[31:0]；默认值：32'b0；*/
/*描述：数据缓冲区*/
#define SPI_MEM_BUF1  0xFFFFFFFF
#define SPI_MEM_BUF1_M  ((SPI_MEM_BUF1_V)<<(SPI_MEM_BUF1_S))
#define SPI_MEM_BUF1_V  0xFFFFFFFF
#define SPI_MEM_BUF1_S  0

#define SPI_MEM_W2_REG(i)          (REG_SPI_MEM_BASE(i) + 0x060)
/* SPI_MEM_BUF2:SRW；位位置：[31:0]；默认值：32'b0；*/
/*描述：数据缓冲区*/
#define SPI_MEM_BUF2  0xFFFFFFFF
#define SPI_MEM_BUF2_M  ((SPI_MEM_BUF2_V)<<(SPI_MEM_BUF2_S))
#define SPI_MEM_BUF2_V  0xFFFFFFFF
#define SPI_MEM_BUF2_S  0

#define SPI_MEM_W3_REG(i)          (REG_SPI_MEM_BASE(i) + 0x064)
/* SPI_MEM_BUF3:SRW；位位置：[31:0]；默认值：32'b0；*/
/*描述：数据缓冲区*/
#define SPI_MEM_BUF3  0xFFFFFFFF
#define SPI_MEM_BUF3_M  ((SPI_MEM_BUF3_V)<<(SPI_MEM_BUF3_S))
#define SPI_MEM_BUF3_V  0xFFFFFFFF
#define SPI_MEM_BUF3_S  0

#define SPI_MEM_W4_REG(i)          (REG_SPI_MEM_BASE(i) + 0x068)
/* SPI_MEM_BUF4:SRW；位位置：[31:0]；默认值：32'b0；*/
/*描述：数据缓冲区*/
#define SPI_MEM_BUF4  0xFFFFFFFF
#define SPI_MEM_BUF4_M  ((SPI_MEM_BUF4_V)<<(SPI_MEM_BUF4_S))
#define SPI_MEM_BUF4_V  0xFFFFFFFF
#define SPI_MEM_BUF4_S  0

#define SPI_MEM_W5_REG(i)          (REG_SPI_MEM_BASE(i) + 0x06C)
/* SPI_MEM_BUF5:SRW；位位置：[31:0]；默认值：32'b0；*/
/*描述：数据缓冲区*/
#define SPI_MEM_BUF5  0xFFFFFFFF
#define SPI_MEM_BUF5_M  ((SPI_MEM_BUF5_V)<<(SPI_MEM_BUF5_S))
#define SPI_MEM_BUF5_V  0xFFFFFFFF
#define SPI_MEM_BUF5_S  0

#define SPI_MEM_W6_REG(i)          (REG_SPI_MEM_BASE(i) + 0x070)
/* SPI_MEM_BUF6:SRW；位位置：[31:0]；默认值：32'b0；*/
/*描述：数据缓冲区*/
#define SPI_MEM_BUF6  0xFFFFFFFF
#define SPI_MEM_BUF6_M  ((SPI_MEM_BUF6_V)<<(SPI_MEM_BUF6_S))
#define SPI_MEM_BUF6_V  0xFFFFFFFF
#define SPI_MEM_BUF6_S  0

#define SPI_MEM_W7_REG(i)          (REG_SPI_MEM_BASE(i) + 0x074)
/* SPI_MEM_BUF7:SRW；位位置：[31:0]；默认值：32'b0；*/
/*描述：数据缓冲区*/
#define SPI_MEM_BUF7  0xFFFFFFFF
#define SPI_MEM_BUF7_M  ((SPI_MEM_BUF7_V)<<(SPI_MEM_BUF7_S))
#define SPI_MEM_BUF7_V  0xFFFFFFFF
#define SPI_MEM_BUF7_S  0

#define SPI_MEM_W8_REG(i)          (REG_SPI_MEM_BASE(i) + 0x078)
/* SPI_MEM_BUF8:SRW；位位置：[31:0]；默认值：32'b0；*/
/*描述：数据缓冲区*/
#define SPI_MEM_BUF8  0xFFFFFFFF
#define SPI_MEM_BUF8_M  ((SPI_MEM_BUF8_V)<<(SPI_MEM_BUF8_S))
#define SPI_MEM_BUF8_V  0xFFFFFFFF
#define SPI_MEM_BUF8_S  0

#define SPI_MEM_W9_REG(i)          (REG_SPI_MEM_BASE(i) + 0x07C)
/* SPI_MEM_BUF9:SRW；位位置：[31:0]；默认值：32'b0；*/
/*描述：数据缓冲区*/
#define SPI_MEM_BUF9  0xFFFFFFFF
#define SPI_MEM_BUF9_M  ((SPI_MEM_BUF9_V)<<(SPI_MEM_BUF9_S))
#define SPI_MEM_BUF9_V  0xFFFFFFFF
#define SPI_MEM_BUF9_S  0

#define SPI_MEM_W10_REG(i)          (REG_SPI_MEM_BASE(i) + 0x080)
/* SPI_MEM_BUF10:SRW；位位置：[31:0]；默认值：32'b0；*/
/*描述：数据缓冲区*/
#define SPI_MEM_BUF10  0xFFFFFFFF
#define SPI_MEM_BUF10_M  ((SPI_MEM_BUF10_V)<<(SPI_MEM_BUF10_S))
#define SPI_MEM_BUF10_V  0xFFFFFFFF
#define SPI_MEM_BUF10_S  0

#define SPI_MEM_W11_REG(i)          (REG_SPI_MEM_BASE(i) + 0x084)
/* SPI_MEM_BUF11:SRW；位位置：[31:0]；默认值：32'b0；*/
/*描述：数据缓冲区*/
#define SPI_MEM_BUF11  0xFFFFFFFF
#define SPI_MEM_BUF11_M  ((SPI_MEM_BUF11_V)<<(SPI_MEM_BUF11_S))
#define SPI_MEM_BUF11_V  0xFFFFFFFF
#define SPI_MEM_BUF11_S  0

#define SPI_MEM_W12_REG(i)          (REG_SPI_MEM_BASE(i) + 0x088)
/* SPI_MEM_BUF12:SRW；位位置：[31:0]；默认值：32'b0；*/
/*描述：数据缓冲区*/
#define SPI_MEM_BUF12  0xFFFFFFFF
#define SPI_MEM_BUF12_M  ((SPI_MEM_BUF12_V)<<(SPI_MEM_BUF12_S))
#define SPI_MEM_BUF12_V  0xFFFFFFFF
#define SPI_MEM_BUF12_S  0

#define SPI_MEM_W13_REG(i)          (REG_SPI_MEM_BASE(i) + 0x08C)
/* SPI_MEM_BUF13:SRW；位位置：[31:0]；默认值：32'b0；*/
/*描述：数据缓冲区*/
#define SPI_MEM_BUF13  0xFFFFFFFF
#define SPI_MEM_BUF13_M  ((SPI_MEM_BUF13_V)<<(SPI_MEM_BUF13_S))
#define SPI_MEM_BUF13_V  0xFFFFFFFF
#define SPI_MEM_BUF13_S  0

#define SPI_MEM_W14_REG(i)          (REG_SPI_MEM_BASE(i) + 0x090)
/* SPI_MEM_BUF14:SRW；位位置：[31:0]；默认值：32'b0；*/
/*描述：数据缓冲区*/
#define SPI_MEM_BUF14  0xFFFFFFFF
#define SPI_MEM_BUF14_M  ((SPI_MEM_BUF14_V)<<(SPI_MEM_BUF14_S))
#define SPI_MEM_BUF14_V  0xFFFFFFFF
#define SPI_MEM_BUF14_S  0

#define SPI_MEM_W15_REG(i)          (REG_SPI_MEM_BASE(i) + 0x094)
/* SPI_MEM_BUF15:SRW；位位置：[31:0]；默认值：32'b0；*/
/*描述：数据缓冲区*/
#define SPI_MEM_BUF15  0xFFFFFFFF
#define SPI_MEM_BUF15_M  ((SPI_MEM_BUF15_V)<<(SPI_MEM_BUF15_S))
#define SPI_MEM_BUF15_V  0xFFFFFFFF
#define SPI_MEM_BUF15_S  0

#define SPI_MEM_FLASH_WAITI_CTRL_REG(i)          (REG_SPI_MEM_BASE(i) + 0x098)
/* SPI_MEM_WAITI-ddummy_CYCLELEN:R/W；比特位置：[17:10]；默认值：8'0；*/
/*description:自动等待闪存空闲时的虚拟周期长度*/
#define SPI_MEM_WAITI_DUMMY_CYCLELEN  0x000000FF
#define SPI_MEM_WAITI_DUMMY_CYCLELEN_M  ((SPI_MEM_WAITI_DUMMY_CYCLELEN_V)<<(SPI_MEM_WAITI_DUMMY_CYCLELEN_S))
#define SPI_MEM_WAITI_DUMMY_CYCLELEN_V  0xFF
#define SPI_MEM_WAITI_DUMMY_CYCLELEN_S  10
/* SPI_MEM_WAITI_CMD:R/W；比特位置：[9:2]；默认值：8'h05；*/
/*description:自动等待空闲的命令*/
#define SPI_MEM_WAITI_CMD  0x000000FF
#define SPI_MEM_WAITI_CMD_M  ((SPI_MEM_WAITI_CMD_V)<<(SPI_MEM_WAITI_CMD_S))
#define SPI_MEM_WAITI_CMD_V  0xFF
#define SPI_MEM_WAITI_CMD_S  2
/* SPI_MEM_WAITI_dedumm:R/W；位位置：[1]；默认值：1’b0；*/
/*description:自动等待闪存空闲时的虚拟阶段启用*/
#define SPI_MEM_WAITI_DUMMY  (BIT(1))
#define SPI_MEM_WAITI_DUMMY_M  (BIT(1))
#define SPI_MEM_WAITI_DUMMY_V  0x1
#define SPI_MEM_WAITI_DUMMY_S  1
/* SPI_MEM_WAITI_EN:R/W；位位置：[0]；默认值：1’b0；*/
/*描述：程序闪存或擦除闪存时自动等待闪存空闲操作。1： 启用0：禁用。*/
#define SPI_MEM_WAITI_EN  (BIT(0))
#define SPI_MEM_WAITI_EN_M  (BIT(0))
#define SPI_MEM_WAITI_EN_V  0x1
#define SPI_MEM_WAITI_EN_S  0

#define SPI_MEM_FLASH_SUS_CMD_REG(i)          (REG_SPI_MEM_BASE(i) + 0x09C)
/* SPI_MEM_FLASH_PES:R/W；位位置：[1]；默认值：1’b0；*/
/*描述：程序擦除暂停位程序擦除暂停操作将在设置位时触发。操作完成后，该位将被清除。1： 启用0：禁用。*/
#define SPI_MEM_FLASH_PES  (BIT(1))
#define SPI_MEM_FLASH_PES_M  (BIT(1))
#define SPI_MEM_FLASH_PES_V  0x1
#define SPI_MEM_FLASH_PES_S  1
/* SPI_MEM_FLASH_PER:R/W；位位置：[0]；默认值：1’b0；*/
/*描述：程序擦除恢复位程序擦除暂停操作将在设置位时触发。操作完成后，该位将被清除。1： 启用0：禁用。*/
#define SPI_MEM_FLASH_PER  (BIT(0))
#define SPI_MEM_FLASH_PER_M  (BIT(0))
#define SPI_MEM_FLASH_PER_V  0x1
#define SPI_MEM_FLASH_PER_S  0

#define SPI_MEM_FLASH_SUS_CTRL_REG(i)          (REG_SPI_MEM_BASE(i) + 0x0A0)
/* SPI_MEM_FLASH_pas_COMMAND:R/W；比特位置：[16:9]；默认值：8'75；*/
/*description:编程/擦除暂停命令。*/
#define SPI_MEM_FLASH_PES_COMMAND  0x000000FF
#define SPI_MEM_FLASH_PES_COMMAND_M  ((SPI_MEM_FLASH_PES_COMMAND_V)<<(SPI_MEM_FLASH_PES_COMMAND_S))
#define SPI_MEM_FLASH_PES_COMMAND_V  0xFF
#define SPI_MEM_FLASH_PES_COMMAND_S  9
/* SPI_MEM_FLASH_PER_COMMAND:R/W；位位置：[8:1]；默认值：8'h7a；*/
/*description:编程/擦除恢复命令。*/
#define SPI_MEM_FLASH_PER_COMMAND  0x000000FF
#define SPI_MEM_FLASH_PER_COMMAND_M  ((SPI_MEM_FLASH_PER_COMMAND_V)<<(SPI_MEM_FLASH_PER_COMMAND_S))
#define SPI_MEM_FLASH_PER_COMMAND_V  0xFF
#define SPI_MEM_FLASH_PER_COMMAND_S  1
/* SPI_MEM_FLASH_ppes_EN:R/W；位位置：[0]；默认值：1’b0；*/
/*description:自动挂起启用*/
#define SPI_MEM_FLASH_PES_EN  (BIT(0))
#define SPI_MEM_FLASH_PES_EN_M  (BIT(0))
#define SPI_MEM_FLASH_PES_EN_V  0x1
#define SPI_MEM_FLASH_PES_EN_S  0

#define SPI_MEM_SUS_STATUS_REG(i)          (REG_SPI_MEM_BASE(i) + 0x0A4)
/* SPI_MEM_FLASH_SUS:R/W；位位置：[0]；默认值：1'0；*/
/*description:flash suspend的状态仅在SPI1中使用。*/
#define SPI_MEM_FLASH_SUS  (BIT(0))
#define SPI_MEM_FLASH_SUS_M  (BIT(0))
#define SPI_MEM_FLASH_SUS_V  0x1
#define SPI_MEM_FLASH_SUS_S  0

#define SPI_MEM_TIMING_CALI_REG(i)          (REG_SPI_MEM_BASE(i) + 0x0A8)
/* SPI_MEM_EXTRA_DUMMY_CYCLELEN:R/W；位位置：[3:2]；默认值：2'd0；*/
/*描述：为spi时钟校准添加额外的伪spi时钟周期长度。*/
#define SPI_MEM_EXTRA_DUMMY_CYCLELEN  0x00000003
#define SPI_MEM_EXTRA_DUMMY_CYCLELEN_M  ((SPI_MEM_EXTRA_DUMMY_CYCLELEN_V)<<(SPI_MEM_EXTRA_DUMMY_CYCLELEN_S))
#define SPI_MEM_EXTRA_DUMMY_CYCLELEN_V  0x3
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
/* SPI_MEM_DINS_MODE：R/W；比特位置：[26:24]；默认值：3'h0；*/
/*描述：输入信号被系统时钟周期延迟0：输入无延迟1：输入clk_apb的偏旁2输入clk.apb的负边3：输入spi_clk*/
#define SPI_MEM_DINS_MODE  0x00000007
#define SPI_MEM_DINS_MODE_M  ((SPI_MEM_DINS_MODE_V)<<(SPI_MEM_DINS_MODE_S))
#define SPI_MEM_DINS_MODE_V  0x7
#define SPI_MEM_DINS_MODE_S  24
/* SPI_MEM_DIN7模式：R/W；比特位置：[23:21]；默认值：3'h0；*/
/*描述：输入信号被系统时钟周期延迟0：输入无延迟1：输入clk_apb的偏旁2输入clk.apb的负边3：输入spi_clk*/
#define SPI_MEM_DIN7_MODE  0x00000007
#define SPI_MEM_DIN7_MODE_M  ((SPI_MEM_DIN7_MODE_V)<<(SPI_MEM_DIN7_MODE_S))
#define SPI_MEM_DIN7_MODE_V  0x7
#define SPI_MEM_DIN7_MODE_S  21
/* SPI_MEM_DIN6_MODE模式：R/W；比特位置：[20:18]；默认值：3'h0；*/
/*描述：输入信号被系统时钟周期延迟0：输入无延迟1：输入clk_apb的偏旁2输入clk.apb的负边3：输入spi_clk*/
#define SPI_MEM_DIN6_MODE  0x00000007
#define SPI_MEM_DIN6_MODE_M  ((SPI_MEM_DIN6_MODE_V)<<(SPI_MEM_DIN6_MODE_S))
#define SPI_MEM_DIN6_MODE_V  0x7
#define SPI_MEM_DIN6_MODE_S  18
/* SPI_MEM_DIN5_MODE：R/W；比特位置：[17:15]；默认值：3'h0；*/
/*描述：输入信号被系统时钟周期延迟0：输入无延迟1：输入clk_apb的偏旁2输入clk.apb的负边3：输入spi_clk*/
#define SPI_MEM_DIN5_MODE  0x00000007
#define SPI_MEM_DIN5_MODE_M  ((SPI_MEM_DIN5_MODE_V)<<(SPI_MEM_DIN5_MODE_S))
#define SPI_MEM_DIN5_MODE_V  0x7
#define SPI_MEM_DIN5_MODE_S  15
/* SPI_MEM_DIN4_MODE:R/W；比特位置：[14:12]；默认值：3'h0；*/
/*描述：输入信号被系统时钟周期延迟0：输入无延迟1：输入clk_apb的偏旁2输入clk.apb的负边3：输入spi_clk*/
#define SPI_MEM_DIN4_MODE  0x00000007
#define SPI_MEM_DIN4_MODE_M  ((SPI_MEM_DIN4_MODE_V)<<(SPI_MEM_DIN4_MODE_S))
#define SPI_MEM_DIN4_MODE_V  0x7
#define SPI_MEM_DIN4_MODE_S  12
/* SPI_MEM_DIN3_MODE：R/W；比特位置：[11:9]；默认值：3'h0；*/
/*描述：输入信号被系统时钟周期延迟0：输入而不延迟1：输入clk_apb的偏倚2输入clk_apb的负边3：输入clk160的偏倚4输入clk_160的负边5：输入spi_clk的高边6：输入spi_clk的低边*/
#define SPI_MEM_DIN3_MODE  0x00000007
#define SPI_MEM_DIN3_MODE_M  ((SPI_MEM_DIN3_MODE_V)<<(SPI_MEM_DIN3_MODE_S))
#define SPI_MEM_DIN3_MODE_V  0x7
#define SPI_MEM_DIN3_MODE_S  9
/* SPI_MEM_din_模式：R/W；位位置：[8:6]；默认值：3'h0；*/
/*描述：输入信号被系统时钟周期延迟0：输入而不延迟1：输入clk_apb的偏倚2输入clk_apb的负边3：输入clk160的偏倚4输入clk_160的负边5：输入spi_clk的高边6：输入spi_clk的低边*/
#define SPI_MEM_DIN2_MODE  0x00000007
#define SPI_MEM_DIN2_MODE_M  ((SPI_MEM_DIN2_MODE_V)<<(SPI_MEM_DIN2_MODE_S))
#define SPI_MEM_DIN2_MODE_V  0x7
#define SPI_MEM_DIN2_MODE_S  6
/* SPI_MEM_DIN1_MODE：R/W；比特位置：[5:3]；默认值：3'h0；*/
/*描述：输入信号被系统时钟周期延迟0：输入而不延迟1：输入clk_apb的偏倚2输入clk_apb的负边3：输入clk160的偏倚4输入clk_160的负边5：输入spi_clk的高边6：输入spi_clk的低边*/
#define SPI_MEM_DIN1_MODE  0x00000007
#define SPI_MEM_DIN1_MODE_M  ((SPI_MEM_DIN1_MODE_V)<<(SPI_MEM_DIN1_MODE_S))
#define SPI_MEM_DIN1_MODE_V  0x7
#define SPI_MEM_DIN1_MODE_S  3
/* SPI_MEM_DIN0_MODE:R/W；位位置：[2:0]；默认值：3'h0；*/
/*描述：输入信号被系统时钟周期延迟0：输入而不延迟1：输入clk_apb的偏倚2输入clk_apb的负边3：输入clk160的偏倚4输入clk_160的负边5：输入spi_clk的高边6：输入spi_clk的低边*/
#define SPI_MEM_DIN0_MODE  0x00000007
#define SPI_MEM_DIN0_MODE_M  ((SPI_MEM_DIN0_MODE_V)<<(SPI_MEM_DIN0_MODE_S))
#define SPI_MEM_DIN0_MODE_V  0x7
#define SPI_MEM_DIN0_MODE_S  0

#define SPI_MEM_DIN_NUM_REG(i)          (REG_SPI_MEM_BASE(i) + 0x0B0)
/* SPI_MEM_DINS_NUM:R/W；比特位置：[17:16]；默认值：2'h0；*/
/*描述：输入信号延迟系统时钟周期0：延迟1个周期1：延迟2个周期。。。*/
#define SPI_MEM_DINS_NUM  0x00000003
#define SPI_MEM_DINS_NUM_M  ((SPI_MEM_DINS_NUM_V)<<(SPI_MEM_DINS_NUM_S))
#define SPI_MEM_DINS_NUM_V  0x3
#define SPI_MEM_DINS_NUM_S  16
/* SPI_MEM_DIN7_NUM:R/W；比特位置：[15:14]；默认值：2'h0；*/
/*描述：输入信号延迟系统时钟周期0：延迟1个周期1：延迟2个周期。。。*/
#define SPI_MEM_DIN7_NUM  0x00000003
#define SPI_MEM_DIN7_NUM_M  ((SPI_MEM_DIN7_NUM_V)<<(SPI_MEM_DIN7_NUM_S))
#define SPI_MEM_DIN7_NUM_V  0x3
#define SPI_MEM_DIN7_NUM_S  14
/* SPI_MEM_DIN6_NUM：随机；比特位置：[13:12]；默认值：2'h0；*/
/*描述：输入信号延迟系统时钟周期0：延迟1个周期1：延迟2个周期。。。*/
#define SPI_MEM_DIN6_NUM  0x00000003
#define SPI_MEM_DIN6_NUM_M  ((SPI_MEM_DIN6_NUM_V)<<(SPI_MEM_DIN6_NUM_S))
#define SPI_MEM_DIN6_NUM_V  0x3
#define SPI_MEM_DIN6_NUM_S  12
/* SPI_MEM_DIN5_NUM:R/W；比特位置：[11:10]；默认值：2'h0；*/
/*描述：输入信号延迟系统时钟周期0：延迟1个周期1：延迟2个周期。。。*/
#define SPI_MEM_DIN5_NUM  0x00000003
#define SPI_MEM_DIN5_NUM_M  ((SPI_MEM_DIN5_NUM_V)<<(SPI_MEM_DIN5_NUM_S))
#define SPI_MEM_DIN5_NUM_V  0x3
#define SPI_MEM_DIN5_NUM_S  10
/* SPI_MEM_DIN4_NUM:R/W；比特位置：[9:8]；默认值：2'h0；*/
/*描述：输入信号延迟系统时钟周期0：延迟1个周期1：延迟2个周期。。。*/
#define SPI_MEM_DIN4_NUM  0x00000003
#define SPI_MEM_DIN4_NUM_M  ((SPI_MEM_DIN4_NUM_V)<<(SPI_MEM_DIN4_NUM_S))
#define SPI_MEM_DIN4_NUM_V  0x3
#define SPI_MEM_DIN4_NUM_S  8
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
/* SPI_MEM_DOUTS_MODE：R/W；比特位置：[26:24]；默认值：3'h0；*/
/*描述：输出信号被系统时钟周期延迟0：无延迟输出1：带clk_apb的偏旁输出2：带clk的负边输出3：带spiclk的输出*/
#define SPI_MEM_DOUTS_MODE  0x00000007
#define SPI_MEM_DOUTS_MODE_M  ((SPI_MEM_DOUTS_MODE_V)<<(SPI_MEM_DOUTS_MODE_S))
#define SPI_MEM_DOUTS_MODE_V  0x7
#define SPI_MEM_DOUTS_MODE_S  24
/* SPI_MEM_DOUT7_模式：R/W；比特位置：[23:21]；默认值：3'h0；*/
/*描述：输出信号被系统时钟周期延迟0：无延迟输出1：带clk_apb的偏旁输出2：带clk的负边输出3：带spiclk的输出*/
#define SPI_MEM_DOUT7_MODE  0x00000007
#define SPI_MEM_DOUT7_MODE_M  ((SPI_MEM_DOUT7_MODE_V)<<(SPI_MEM_DOUT7_MODE_S))
#define SPI_MEM_DOUT7_MODE_V  0x7
#define SPI_MEM_DOUT7_MODE_S  21
/* SPI_MEM_DOUT6_MODE模式：R/W；比特位置：[20:18]；默认值：3'h0；*/
/*描述：输出信号被系统时钟周期延迟0：无延迟输出1：带clk_apb的偏旁输出2：带clk的负边输出3：带spiclk的输出*/
#define SPI_MEM_DOUT6_MODE  0x00000007
#define SPI_MEM_DOUT6_MODE_M  ((SPI_MEM_DOUT6_MODE_V)<<(SPI_MEM_DOUT6_MODE_S))
#define SPI_MEM_DOUT6_MODE_V  0x7
#define SPI_MEM_DOUT6_MODE_S  18
/* SPI_MEM_DOUT5_MODE：R/W；比特位置：[17:15]；默认值：3'h0；*/
/*描述：输出信号被系统时钟周期延迟0：无延迟输出1：带clk_apb的偏旁输出2：带clk的负边输出3：带spiclk的输出*/
#define SPI_MEM_DOUT5_MODE  0x00000007
#define SPI_MEM_DOUT5_MODE_M  ((SPI_MEM_DOUT5_MODE_V)<<(SPI_MEM_DOUT5_MODE_S))
#define SPI_MEM_DOUT5_MODE_V  0x7
#define SPI_MEM_DOUT5_MODE_S  15
/* SPI_MEM_DOUT4_MODE:R/W；比特位置：[14:12]；默认值：3'h0；*/
/*描述：输出信号被系统时钟周期延迟0：无延迟输出1：带clk_apb的偏旁输出2：带clk的负边输出3：带spiclk的输出*/
#define SPI_MEM_DOUT4_MODE  0x00000007
#define SPI_MEM_DOUT4_MODE_M  ((SPI_MEM_DOUT4_MODE_V)<<(SPI_MEM_DOUT4_MODE_S))
#define SPI_MEM_DOUT4_MODE_V  0x7
#define SPI_MEM_DOUT4_MODE_S  12
/* SPI_MEM_DOUT3_MODE：R/W；比特位置：[11:9]；默认值：3'h0；*/
/*描述：输出信号被系统时钟周期延迟0：无延迟输出1：带clk_apb的偏序输出2：带clk _apb的负边输出3：带clk160的偏序的输出4：带clk260的负边的输出5：带spi_clk的高边输出6：带spi_clk的低边输出*/
#define SPI_MEM_DOUT3_MODE  0x00000007
#define SPI_MEM_DOUT3_MODE_M  ((SPI_MEM_DOUT3_MODE_V)<<(SPI_MEM_DOUT3_MODE_S))
#define SPI_MEM_DOUT3_MODE_V  0x7
#define SPI_MEM_DOUT3_MODE_S  9
/* SPI_MEM_DOUT2_MODE:R/W；位位置：[8:6]；默认值：3'h0；*/
/*描述：输出信号被系统时钟周期延迟0：无延迟输出1：带clk_apb的偏序输出2：带clk _apb的负边输出3：带clk160的偏序的输出4：带clk260的负边的输出5：带spi_clk的高边输出6：带spi_clk的低边输出*/
#define SPI_MEM_DOUT2_MODE  0x00000007
#define SPI_MEM_DOUT2_MODE_M  ((SPI_MEM_DOUT2_MODE_V)<<(SPI_MEM_DOUT2_MODE_S))
#define SPI_MEM_DOUT2_MODE_V  0x7
#define SPI_MEM_DOUT2_MODE_S  6
/* SPI_MEM_DOUT1_MODE：R/W；比特位置：[5:3]；默认值：3'h0；*/
/*描述：输出信号被系统时钟周期延迟0：无延迟输出1：带clk_apb的偏序输出2：带clk _apb的负边输出3：带clk160的偏序的输出4：带clk260的负边的输出5：带spi_clk的高边输出6：带spi_clk的低边输出*/
#define SPI_MEM_DOUT1_MODE  0x00000007
#define SPI_MEM_DOUT1_MODE_M  ((SPI_MEM_DOUT1_MODE_V)<<(SPI_MEM_DOUT1_MODE_S))
#define SPI_MEM_DOUT1_MODE_V  0x7
#define SPI_MEM_DOUT1_MODE_S  3
/* SPI_MEM_DOUT0_MODE:R/W；位位置：[2:0]；默认值：3'h0；*/
/*描述：输出信号被系统时钟周期延迟0：无延迟输出1：带clk_apb的偏序输出2：带clk _apb的负边输出3：带clk160的偏序的输出4：带clk260的负边的输出5：带spi_clk的高边输出6：带spi_clk的低边输出*/
#define SPI_MEM_DOUT0_MODE  0x00000007
#define SPI_MEM_DOUT0_MODE_M  ((SPI_MEM_DOUT0_MODE_V)<<(SPI_MEM_DOUT0_MODE_S))
#define SPI_MEM_DOUT0_MODE_V  0x7
#define SPI_MEM_DOUT0_MODE_S  0

#define SPI_MEM_DOUT_NUM_REG(i)          (REG_SPI_MEM_BASE(i) + 0x0B8)
/* SPI_MEM_DOUTS_NUM:R/W；比特位置：[17:16]；默认值：2'h0；*/
/*描述：输出信号延迟系统时钟周期0：延迟1个周期1：延迟2个周期。。。*/
#define SPI_MEM_DOUTS_NUM  0x00000003
#define SPI_MEM_DOUTS_NUM_M  ((SPI_MEM_DOUTS_NUM_V)<<(SPI_MEM_DOUTS_NUM_S))
#define SPI_MEM_DOUTS_NUM_V  0x3
#define SPI_MEM_DOUTS_NUM_S  16
/* SPI_MEM_DOUT7_NUM:R/W；比特位置：[15:14]；默认值：2'h0；*/
/*描述：输出信号延迟系统时钟周期0：延迟1个周期1：延迟2个周期。。。*/
#define SPI_MEM_DOUT7_NUM  0x00000003
#define SPI_MEM_DOUT7_NUM_M  ((SPI_MEM_DOUT7_NUM_V)<<(SPI_MEM_DOUT7_NUM_S))
#define SPI_MEM_DOUT7_NUM_V  0x3
#define SPI_MEM_DOUT7_NUM_S  14
/* SPI_MEM_DOUT6_NUM：随机；比特位置：[13:12]；默认值：2'h0；*/
/*描述：输出信号延迟系统时钟周期0：延迟1个周期1：延迟2个周期。。。*/
#define SPI_MEM_DOUT6_NUM  0x00000003
#define SPI_MEM_DOUT6_NUM_M  ((SPI_MEM_DOUT6_NUM_V)<<(SPI_MEM_DOUT6_NUM_S))
#define SPI_MEM_DOUT6_NUM_V  0x3
#define SPI_MEM_DOUT6_NUM_S  12
/* SPI_MEM_DOUT5_NUM:R/W；比特位置：[11:10]；默认值：2'h0；*/
/*描述：输出信号延迟系统时钟周期0：延迟1个周期1：延迟2个周期。。。*/
#define SPI_MEM_DOUT5_NUM  0x00000003
#define SPI_MEM_DOUT5_NUM_M  ((SPI_MEM_DOUT5_NUM_V)<<(SPI_MEM_DOUT5_NUM_S))
#define SPI_MEM_DOUT5_NUM_V  0x3
#define SPI_MEM_DOUT5_NUM_S  10
/* SPI_MEM_DOUT4_NUM:R/W；比特位置：[9:8]；默认值：2'h0；*/
/*描述：输出信号延迟系统时钟周期0：延迟1个周期1：延迟2个周期。。。*/
#define SPI_MEM_DOUT4_NUM  0x00000003
#define SPI_MEM_DOUT4_NUM_M  ((SPI_MEM_DOUT4_NUM_V)<<(SPI_MEM_DOUT4_NUM_S))
#define SPI_MEM_DOUT4_NUM_V  0x3
#define SPI_MEM_DOUT4_NUM_S  8
/* SPI_MEM_DOUT3_NUM:R/W；位位置：[7:6]；默认值：2'h0；*/
/*描述：输出信号延迟系统时钟周期0：延迟1个周期1：延迟2个周期。。。*/
#define SPI_MEM_DOUT3_NUM  0x00000003
#define SPI_MEM_DOUT3_NUM_M  ((SPI_MEM_DOUT3_NUM_V)<<(SPI_MEM_DOUT3_NUM_S))
#define SPI_MEM_DOUT3_NUM_V  0x3
#define SPI_MEM_DOUT3_NUM_S  6
/* SPI_MEM_DOUT2_NUM:R/W；比特位置：[5:4]；默认值：2'h0；*/
/*描述：输出信号延迟系统时钟周期0：延迟1个周期1：延迟2个周期。。。*/
#define SPI_MEM_DOUT2_NUM  0x00000003
#define SPI_MEM_DOUT2_NUM_M  ((SPI_MEM_DOUT2_NUM_V)<<(SPI_MEM_DOUT2_NUM_S))
#define SPI_MEM_DOUT2_NUM_V  0x3
#define SPI_MEM_DOUT2_NUM_S  4
/* SPI_MEM_DOUT1_NUM:R/W；位位置：[3:2]；默认值：2'h0；*/
/*描述：输出信号延迟系统时钟周期0：延迟1个周期1：延迟2个周期。。。*/
#define SPI_MEM_DOUT1_NUM  0x00000003
#define SPI_MEM_DOUT1_NUM_M  ((SPI_MEM_DOUT1_NUM_V)<<(SPI_MEM_DOUT1_NUM_S))
#define SPI_MEM_DOUT1_NUM_V  0x3
#define SPI_MEM_DOUT1_NUM_S  2
/* SPI_MEM_DOUT0_NUM:R/W；位位置：[1:0]；默认值：2'h0；*/
/*描述：输出信号延迟系统时钟周期0：延迟1个周期1：延迟2个周期。。。*/
#define SPI_MEM_DOUT0_NUM  0x00000003
#define SPI_MEM_DOUT0_NUM_M  ((SPI_MEM_DOUT0_NUM_V)<<(SPI_MEM_DOUT0_NUM_S))
#define SPI_MEM_DOUT0_NUM_V  0x3
#define SPI_MEM_DOUT0_NUM_S  0

#define SPI_MEM_SPI_SMEM_TIMING_CALI_REG(i)          (REG_SPI_MEM_BASE(i) + 0x0BC)
/* SPI_MEM_SPI_SMEM_EXTRA_DUMMY_CYCLELEN:R/W；位位置：[3:2]；默认值：2'd0；*/
/*描述：对于sram，为spi时钟校准添加额外的伪spi时钟周期长度。*/
#define SPI_MEM_SPI_SMEM_EXTRA_DUMMY_CYCLELEN  0x00000003
#define SPI_MEM_SPI_SMEM_EXTRA_DUMMY_CYCLELEN_M  ((SPI_MEM_SPI_SMEM_EXTRA_DUMMY_CYCLELEN_V)<<(SPI_MEM_SPI_SMEM_EXTRA_DUMMY_CYCLELEN_S))
#define SPI_MEM_SPI_SMEM_EXTRA_DUMMY_CYCLELEN_V  0x3
#define SPI_MEM_SPI_SMEM_EXTRA_DUMMY_CYCLELEN_S  2
/* SPI_MEM_SPI_SMEM_timeng_CALI:R/W；位位置：[1]；默认值：1’b0；*/
/*描述：对于sram，该位用于启用所有读取操作的定时自动校准。*/
#define SPI_MEM_SPI_SMEM_TIMING_CALI  (BIT(1))
#define SPI_MEM_SPI_SMEM_TIMING_CALI_M  (BIT(1))
#define SPI_MEM_SPI_SMEM_TIMING_CALI_V  0x1
#define SPI_MEM_SPI_SMEM_TIMING_CALI_S  1
/* SPI_MEM_SPI_SMEM_TIMING_CLK_ENA:R/W；位位置：[0]；默认值：1’b1；*/
/*描述：对于sram，该位用于为所有读取操作启用定时调整时钟。*/
#define SPI_MEM_SPI_SMEM_TIMING_CLK_ENA  (BIT(0))
#define SPI_MEM_SPI_SMEM_TIMING_CLK_ENA_M  (BIT(0))
#define SPI_MEM_SPI_SMEM_TIMING_CLK_ENA_V  0x1
#define SPI_MEM_SPI_SMEM_TIMING_CLK_ENA_S  0

#define SPI_MEM_SPI_SMEM_DIN_MODE_REG(i)          (REG_SPI_MEM_BASE(i) + 0x0C0)
/* SPI_MEM_SPI_SMEM_DINS_MODE：R/W；比特位置：[26:24]；默认值：3'h0；*/
/*描述：输入信号被系统时钟周期延迟0：输入而不延迟1：输入clk_apb的偏倚2输入clk_apb的负边3：输入clk160的偏倚4输入clk_160的负边5：输入spi_clk的高边6：输入spi_clk的低边*/
#define SPI_MEM_SPI_SMEM_DINS_MODE  0x00000007
#define SPI_MEM_SPI_SMEM_DINS_MODE_M  ((SPI_MEM_SPI_SMEM_DINS_MODE_V)<<(SPI_MEM_SPI_SMEM_DINS_MODE_S))
#define SPI_MEM_SPI_SMEM_DINS_MODE_V  0x7
#define SPI_MEM_SPI_SMEM_DINS_MODE_S  24
/* SPI_MEM_SPI_SMEM_DIN7模式：R/W；比特位置：[23:21]；默认值：3'h0；*/
/*描述：输入信号被系统时钟周期延迟0：输入而不延迟1：输入clk_apb的偏倚2输入clk_apb的负边3：输入clk160的偏倚4输入clk_160的负边5：输入spi_clk的高边6：输入spi_clk的低边*/
#define SPI_MEM_SPI_SMEM_DIN7_MODE  0x00000007
#define SPI_MEM_SPI_SMEM_DIN7_MODE_M  ((SPI_MEM_SPI_SMEM_DIN7_MODE_V)<<(SPI_MEM_SPI_SMEM_DIN7_MODE_S))
#define SPI_MEM_SPI_SMEM_DIN7_MODE_V  0x7
#define SPI_MEM_SPI_SMEM_DIN7_MODE_S  21
/* SPI_MEM_SPI_SMEM_DIN6_MODE模式：R/W；比特位置：[20:18]；默认值：3'h0；*/
/*描述：输入信号被系统时钟周期延迟0：输入而不延迟1：输入clk_apb的偏倚2输入clk_apb的负边3：输入clk160的偏倚4输入clk_160的负边5：输入spi_clk的高边6：输入spi_clk的低边*/
#define SPI_MEM_SPI_SMEM_DIN6_MODE  0x00000007
#define SPI_MEM_SPI_SMEM_DIN6_MODE_M  ((SPI_MEM_SPI_SMEM_DIN6_MODE_V)<<(SPI_MEM_SPI_SMEM_DIN6_MODE_S))
#define SPI_MEM_SPI_SMEM_DIN6_MODE_V  0x7
#define SPI_MEM_SPI_SMEM_DIN6_MODE_S  18
/* SPI_MEM_SPI_SMEM_DIN5_MODE：R/W；比特位置：[17:15]；默认值：3'h0；*/
/*描述：输入信号被系统时钟周期延迟0：输入而不延迟1：输入clk_apb的偏倚2输入clk_apb的负边3：输入clk160的偏倚4输入clk_160的负边5：输入spi_clk的高边6：输入spi_clk的低边*/
#define SPI_MEM_SPI_SMEM_DIN5_MODE  0x00000007
#define SPI_MEM_SPI_SMEM_DIN5_MODE_M  ((SPI_MEM_SPI_SMEM_DIN5_MODE_V)<<(SPI_MEM_SPI_SMEM_DIN5_MODE_S))
#define SPI_MEM_SPI_SMEM_DIN5_MODE_V  0x7
#define SPI_MEM_SPI_SMEM_DIN5_MODE_S  15
/* SPI_MEM_SPI_SMEM_DIN4模式：R/W；比特位置：[14:12]；默认值：3'h0；*/
/*描述：输入信号被系统时钟周期延迟0：输入而不延迟1：输入clk_apb的偏倚2输入clk_apb的负边3：输入clk160的偏倚4输入clk_160的负边5：输入spi_clk的高边6：输入spi_clk的低边*/
#define SPI_MEM_SPI_SMEM_DIN4_MODE  0x00000007
#define SPI_MEM_SPI_SMEM_DIN4_MODE_M  ((SPI_MEM_SPI_SMEM_DIN4_MODE_V)<<(SPI_MEM_SPI_SMEM_DIN4_MODE_S))
#define SPI_MEM_SPI_SMEM_DIN4_MODE_V  0x7
#define SPI_MEM_SPI_SMEM_DIN4_MODE_S  12
/* SPI_MEM_SPI_SMEM_DIN3_MODE：R/W；比特位置：[11:9]；默认值：3'h0；*/
/*描述：输入信号被系统时钟周期延迟0：输入而不延迟1：输入clk_apb的偏倚2输入clk_apb的负边3：输入clk160的偏倚4输入clk_160的负边5：输入spi_clk的高边6：输入spi_clk的低边*/
#define SPI_MEM_SPI_SMEM_DIN3_MODE  0x00000007
#define SPI_MEM_SPI_SMEM_DIN3_MODE_M  ((SPI_MEM_SPI_SMEM_DIN3_MODE_V)<<(SPI_MEM_SPI_SMEM_DIN3_MODE_S))
#define SPI_MEM_SPI_SMEM_DIN3_MODE_V  0x7
#define SPI_MEM_SPI_SMEM_DIN3_MODE_S  9
/* SPI_MEM_SPI_SMEM_din_模式：R/W；位位置：[8:6]；默认值：3'h0；*/
/*描述：输入信号被系统时钟周期延迟0：输入而不延迟1：输入clk_apb的偏倚2输入clk_apb的负边3：输入clk160的偏倚4输入clk_160的负边5：输入spi_clk的高边6：输入spi_clk的低边*/
#define SPI_MEM_SPI_SMEM_DIN2_MODE  0x00000007
#define SPI_MEM_SPI_SMEM_DIN2_MODE_M  ((SPI_MEM_SPI_SMEM_DIN2_MODE_V)<<(SPI_MEM_SPI_SMEM_DIN2_MODE_S))
#define SPI_MEM_SPI_SMEM_DIN2_MODE_V  0x7
#define SPI_MEM_SPI_SMEM_DIN2_MODE_S  6
/* SPI_MEM_SPI_SMEM_DIN1_MODE：R/W；比特位置：[5:3]；默认值：3'h0；*/
/*描述：输入信号被系统时钟周期延迟0：输入而不延迟1：输入clk_apb的偏倚2输入clk_apb的负边3：输入clk160的偏倚4输入clk_160的负边5：输入spi_clk的高边6：输入spi_clk的低边*/
#define SPI_MEM_SPI_SMEM_DIN1_MODE  0x00000007
#define SPI_MEM_SPI_SMEM_DIN1_MODE_M  ((SPI_MEM_SPI_SMEM_DIN1_MODE_V)<<(SPI_MEM_SPI_SMEM_DIN1_MODE_S))
#define SPI_MEM_SPI_SMEM_DIN1_MODE_V  0x7
#define SPI_MEM_SPI_SMEM_DIN1_MODE_S  3
/* SPI_MEM_SPI_SMEM_DIN0_MODE:R/W；位位置：[2:0]；默认值：3'h0；*/
/*描述：输入信号被系统时钟周期延迟0：输入而不延迟1：输入clk_apb的偏倚2输入clk_apb的负边3：输入clk160的偏倚4输入clk_160的负边5：输入spi_clk的高边6：输入spi_clk的低边*/
#define SPI_MEM_SPI_SMEM_DIN0_MODE  0x00000007
#define SPI_MEM_SPI_SMEM_DIN0_MODE_M  ((SPI_MEM_SPI_SMEM_DIN0_MODE_V)<<(SPI_MEM_SPI_SMEM_DIN0_MODE_S))
#define SPI_MEM_SPI_SMEM_DIN0_MODE_V  0x7
#define SPI_MEM_SPI_SMEM_DIN0_MODE_S  0

#define SPI_MEM_SPI_SMEM_DIN_NUM_REG(i)          (REG_SPI_MEM_BASE(i) + 0x0C4)
/* SPI_MEM_SPI_SMEM_DINS_NUM:R/W；比特位置：[17:16]；默认值：2'h0；*/
/*描述：输入信号被系统时钟周期延迟0：输入而不延迟1：输入clk_apb的偏倚2输入clk_apb的负边3：输入clk160的偏倚4输入clk_160的负边5：输入spi_clk的高边6：输入spi_clk的低边*/
#define SPI_MEM_SPI_SMEM_DINS_NUM  0x00000003
#define SPI_MEM_SPI_SMEM_DINS_NUM_M  ((SPI_MEM_SPI_SMEM_DINS_NUM_V)<<(SPI_MEM_SPI_SMEM_DINS_NUM_S))
#define SPI_MEM_SPI_SMEM_DINS_NUM_V  0x3
#define SPI_MEM_SPI_SMEM_DINS_NUM_S  16
/* SPI_MEM_SPI_SMEM_DIN7_NUM:R/W；比特位置：[15:14]；默认值：2'h0；*/
/*描述：输入信号延迟系统时钟周期0：延迟1个周期1：延迟2个周期。。。*/
#define SPI_MEM_SPI_SMEM_DIN7_NUM  0x00000003
#define SPI_MEM_SPI_SMEM_DIN7_NUM_M  ((SPI_MEM_SPI_SMEM_DIN7_NUM_V)<<(SPI_MEM_SPI_SMEM_DIN7_NUM_S))
#define SPI_MEM_SPI_SMEM_DIN7_NUM_V  0x3
#define SPI_MEM_SPI_SMEM_DIN7_NUM_S  14
/* SPI_MEM_SPI_SMEM_DIN6_NUM：随机；比特位置：[13:12]；默认值：2'h0；*/
/*描述：输入信号延迟系统时钟周期0：延迟1个周期1：延迟2个周期。。。*/
#define SPI_MEM_SPI_SMEM_DIN6_NUM  0x00000003
#define SPI_MEM_SPI_SMEM_DIN6_NUM_M  ((SPI_MEM_SPI_SMEM_DIN6_NUM_V)<<(SPI_MEM_SPI_SMEM_DIN6_NUM_S))
#define SPI_MEM_SPI_SMEM_DIN6_NUM_V  0x3
#define SPI_MEM_SPI_SMEM_DIN6_NUM_S  12
/* SPI_MEM_SPI_SMEM_DIN5_NUM:R/W；比特位置：[11:10]；默认值：2'h0；*/
/*描述：输入信号延迟系统时钟周期0：延迟1个周期1：延迟2个周期。。。*/
#define SPI_MEM_SPI_SMEM_DIN5_NUM  0x00000003
#define SPI_MEM_SPI_SMEM_DIN5_NUM_M  ((SPI_MEM_SPI_SMEM_DIN5_NUM_V)<<(SPI_MEM_SPI_SMEM_DIN5_NUM_S))
#define SPI_MEM_SPI_SMEM_DIN5_NUM_V  0x3
#define SPI_MEM_SPI_SMEM_DIN5_NUM_S  10
/* SPI_MEM_SPI_SMEM_DIN4_NUM:R/W；比特位置：[9:8]；默认值：2'h0；*/
/*描述：输入信号延迟系统时钟周期0：延迟1个周期1：延迟2个周期。。。*/
#define SPI_MEM_SPI_SMEM_DIN4_NUM  0x00000003
#define SPI_MEM_SPI_SMEM_DIN4_NUM_M  ((SPI_MEM_SPI_SMEM_DIN4_NUM_V)<<(SPI_MEM_SPI_SMEM_DIN4_NUM_S))
#define SPI_MEM_SPI_SMEM_DIN4_NUM_V  0x3
#define SPI_MEM_SPI_SMEM_DIN4_NUM_S  8
/* SPI_MEM_SPI_SMEM_DIN3_NUM:R/W；位位置：[7:6]；默认值：2'h0；*/
/*描述：输入信号延迟系统时钟周期0：延迟1个周期1：延迟2个周期。。。*/
#define SPI_MEM_SPI_SMEM_DIN3_NUM  0x00000003
#define SPI_MEM_SPI_SMEM_DIN3_NUM_M  ((SPI_MEM_SPI_SMEM_DIN3_NUM_V)<<(SPI_MEM_SPI_SMEM_DIN3_NUM_S))
#define SPI_MEM_SPI_SMEM_DIN3_NUM_V  0x3
#define SPI_MEM_SPI_SMEM_DIN3_NUM_S  6
/* SPI_MEM_SPI_SMEM_DIN2_NUM:R/W；比特位置：[5:4]；默认值：2'h0；*/
/*描述：输入信号延迟系统时钟周期0：延迟1个周期1：延迟2个周期。。。*/
#define SPI_MEM_SPI_SMEM_DIN2_NUM  0x00000003
#define SPI_MEM_SPI_SMEM_DIN2_NUM_M  ((SPI_MEM_SPI_SMEM_DIN2_NUM_V)<<(SPI_MEM_SPI_SMEM_DIN2_NUM_S))
#define SPI_MEM_SPI_SMEM_DIN2_NUM_V  0x3
#define SPI_MEM_SPI_SMEM_DIN2_NUM_S  4
/* SPI_MEM_SPI_SMEM_DIN1_NUM:R/W；位位置：[3:2]；默认值：2'h0；*/
/*描述：输入信号延迟系统时钟周期0：延迟1个周期1：延迟2个周期。。。*/
#define SPI_MEM_SPI_SMEM_DIN1_NUM  0x00000003
#define SPI_MEM_SPI_SMEM_DIN1_NUM_M  ((SPI_MEM_SPI_SMEM_DIN1_NUM_V)<<(SPI_MEM_SPI_SMEM_DIN1_NUM_S))
#define SPI_MEM_SPI_SMEM_DIN1_NUM_V  0x3
#define SPI_MEM_SPI_SMEM_DIN1_NUM_S  2
/* SPI_MEM_SPI_SMEM_DIN0_NUM:R/W；位位置：[1:0]；默认值：2'h0；*/
/*描述：输入信号延迟系统时钟周期0：延迟1个周期1：延迟2个周期。。。*/
#define SPI_MEM_SPI_SMEM_DIN0_NUM  0x00000003
#define SPI_MEM_SPI_SMEM_DIN0_NUM_M  ((SPI_MEM_SPI_SMEM_DIN0_NUM_V)<<(SPI_MEM_SPI_SMEM_DIN0_NUM_S))
#define SPI_MEM_SPI_SMEM_DIN0_NUM_V  0x3
#define SPI_MEM_SPI_SMEM_DIN0_NUM_S  0

#define SPI_MEM_SPI_SMEM_DOUT_MODE_REG(i)          (REG_SPI_MEM_BASE(i) + 0x0C8)
/* SPI_MEM_SPI_SMEM_DOUTS_MODE：R/W；比特位置：[26:24]；默认值：3'h0；*/
/*描述：输出信号被系统时钟周期延迟0：无延迟输出1：带clk_apb的偏序输出2：带clk _apb的负边输出3：带clk160的偏序的输出4：带clk260的负边的输出5：带spi_clk的高边输出6：带spi_clk的低边输出*/
#define SPI_MEM_SPI_SMEM_DOUTS_MODE  0x00000007
#define SPI_MEM_SPI_SMEM_DOUTS_MODE_M  ((SPI_MEM_SPI_SMEM_DOUTS_MODE_V)<<(SPI_MEM_SPI_SMEM_DOUTS_MODE_S))
#define SPI_MEM_SPI_SMEM_DOUTS_MODE_V  0x7
#define SPI_MEM_SPI_SMEM_DOUTS_MODE_S  24
/* SPI_MEM_SPI_SMEM_DOUT7_模式：R/W；比特位置：[23:21]；默认值：3'h0；*/
/*描述：输出信号被系统时钟周期延迟0：无延迟输出1：带clk_apb的偏序输出2：带clk _apb的负边输出3：带clk160的偏序的输出4：带clk260的负边的输出5：带spi_clk的高边输出6：带spi_clk的低边输出*/
#define SPI_MEM_SPI_SMEM_DOUT7_MODE  0x00000007
#define SPI_MEM_SPI_SMEM_DOUT7_MODE_M  ((SPI_MEM_SPI_SMEM_DOUT7_MODE_V)<<(SPI_MEM_SPI_SMEM_DOUT7_MODE_S))
#define SPI_MEM_SPI_SMEM_DOUT7_MODE_V  0x7
#define SPI_MEM_SPI_SMEM_DOUT7_MODE_S  21
/* SPI_MEM_SPI_SMEM_DOUT6_MODE模式：R/W；比特位置：[20:18]；默认值：3'h0；*/
/*描述：输出信号被系统时钟周期延迟0：无延迟输出1：带clk_apb的偏序输出2：带clk _apb的负边输出3：带clk160的偏序的输出4：带clk260的负边的输出5：带spi_clk的高边输出6：带spi_clk的低边输出*/
#define SPI_MEM_SPI_SMEM_DOUT6_MODE  0x00000007
#define SPI_MEM_SPI_SMEM_DOUT6_MODE_M  ((SPI_MEM_SPI_SMEM_DOUT6_MODE_V)<<(SPI_MEM_SPI_SMEM_DOUT6_MODE_S))
#define SPI_MEM_SPI_SMEM_DOUT6_MODE_V  0x7
#define SPI_MEM_SPI_SMEM_DOUT6_MODE_S  18
/* SPI_MEM_SPI_SMEM_DOUT5_MODE：R/W；比特位置：[17:15]；默认值：3'h0；*/
/*描述：输出信号被系统时钟周期延迟0：无延迟输出1：带clk_apb的偏序输出2：带clk _apb的负边输出3：带clk160的偏序的输出4：带clk260的负边的输出5：带spi_clk的高边输出6：带spi_clk的低边输出*/
#define SPI_MEM_SPI_SMEM_DOUT5_MODE  0x00000007
#define SPI_MEM_SPI_SMEM_DOUT5_MODE_M  ((SPI_MEM_SPI_SMEM_DOUT5_MODE_V)<<(SPI_MEM_SPI_SMEM_DOUT5_MODE_S))
#define SPI_MEM_SPI_SMEM_DOUT5_MODE_V  0x7
#define SPI_MEM_SPI_SMEM_DOUT5_MODE_S  15
/* SPI_MEM_SPI_SMEM_DOUT4_MODE：R/W；比特位置：[14:12]；默认值：3'h0；*/
/*描述：输出信号被系统时钟周期延迟0：无延迟输出1：带clk_apb的偏序输出2：带clk _apb的负边输出3：带clk160的偏序的输出4：带clk260的负边的输出5：带spi_clk的高边输出6：带spi_clk的低边输出*/
#define SPI_MEM_SPI_SMEM_DOUT4_MODE  0x00000007
#define SPI_MEM_SPI_SMEM_DOUT4_MODE_M  ((SPI_MEM_SPI_SMEM_DOUT4_MODE_V)<<(SPI_MEM_SPI_SMEM_DOUT4_MODE_S))
#define SPI_MEM_SPI_SMEM_DOUT4_MODE_V  0x7
#define SPI_MEM_SPI_SMEM_DOUT4_MODE_S  12
/* SPI_MEM_SPI_SMEM_DOUT3_MODE：R/W；比特位置：[11:9]；默认值：3'h0；*/
/*描述：输出信号被系统时钟周期延迟0：无延迟输出1：带clk_apb的偏序输出2：带clk _apb的负边输出3：带clk160的偏序的输出4：带clk260的负边的输出5：带spi_clk的高边输出6：带spi_clk的低边输出*/
#define SPI_MEM_SPI_SMEM_DOUT3_MODE  0x00000007
#define SPI_MEM_SPI_SMEM_DOUT3_MODE_M  ((SPI_MEM_SPI_SMEM_DOUT3_MODE_V)<<(SPI_MEM_SPI_SMEM_DOUT3_MODE_S))
#define SPI_MEM_SPI_SMEM_DOUT3_MODE_V  0x7
#define SPI_MEM_SPI_SMEM_DOUT3_MODE_S  9
/* SPI_MEM_SPI_SMEM_DOUT2_MODE:R/W；位位置：[8:6]；默认值：3'h0；*/
/*描述：输出信号被系统时钟周期延迟0：无延迟输出1：带clk_apb的偏序输出2：带clk _apb的负边输出3：带clk160的偏序的输出4：带clk260的负边的输出5：带spi_clk的高边输出6：带spi_clk的低边输出*/
#define SPI_MEM_SPI_SMEM_DOUT2_MODE  0x00000007
#define SPI_MEM_SPI_SMEM_DOUT2_MODE_M  ((SPI_MEM_SPI_SMEM_DOUT2_MODE_V)<<(SPI_MEM_SPI_SMEM_DOUT2_MODE_S))
#define SPI_MEM_SPI_SMEM_DOUT2_MODE_V  0x7
#define SPI_MEM_SPI_SMEM_DOUT2_MODE_S  6
/* SPI_MEM_SPI_SMEM_DOUT1_MODE：R/W；比特位置：[5:3]；默认值：3'h0；*/
/*描述：输出信号被系统时钟周期延迟0：无延迟输出1：带clk_apb的偏序输出2：带clk _apb的负边输出3：带clk160的偏序的输出4：带clk260的负边的输出5：带spi_clk的高边输出6：带spi_clk的低边输出*/
#define SPI_MEM_SPI_SMEM_DOUT1_MODE  0x00000007
#define SPI_MEM_SPI_SMEM_DOUT1_MODE_M  ((SPI_MEM_SPI_SMEM_DOUT1_MODE_V)<<(SPI_MEM_SPI_SMEM_DOUT1_MODE_S))
#define SPI_MEM_SPI_SMEM_DOUT1_MODE_V  0x7
#define SPI_MEM_SPI_SMEM_DOUT1_MODE_S  3
/* SPI_MEM_SPI_SMEM_DOUT0_MODE：R/W；位位置：[2:0]；默认值：3'h0；*/
/*描述：输出信号被系统时钟周期延迟0：无延迟输出1：带clk_apb的偏序输出2：带clk _apb的负边输出3：带clk160的偏序的输出4：带clk260的负边的输出5：带spi_clk的高边输出6：带spi_clk的低边输出*/
#define SPI_MEM_SPI_SMEM_DOUT0_MODE  0x00000007
#define SPI_MEM_SPI_SMEM_DOUT0_MODE_M  ((SPI_MEM_SPI_SMEM_DOUT0_MODE_V)<<(SPI_MEM_SPI_SMEM_DOUT0_MODE_S))
#define SPI_MEM_SPI_SMEM_DOUT0_MODE_V  0x7
#define SPI_MEM_SPI_SMEM_DOUT0_MODE_S  0

#define SPI_MEM_SPI_SMEM_DOUT_NUM_REG(i)          (REG_SPI_MEM_BASE(i) + 0x0CC)
/* SPI_MEM_SPI_SMEM_DOUTS_NUM:R/W；比特位置：[17:16]；默认值：2'h0；*/
/*描述：输出信号被系统时钟周期延迟0：无延迟输出1：带clk_apb的偏序输出2：带clk _apb的负边输出3：带clk160的偏序的输出4：带clk260的负边的输出5：带spi_clk的高边输出6：带spi_clk的低边输出*/
#define SPI_MEM_SPI_SMEM_DOUTS_NUM  0x00000003
#define SPI_MEM_SPI_SMEM_DOUTS_NUM_M  ((SPI_MEM_SPI_SMEM_DOUTS_NUM_V)<<(SPI_MEM_SPI_SMEM_DOUTS_NUM_S))
#define SPI_MEM_SPI_SMEM_DOUTS_NUM_V  0x3
#define SPI_MEM_SPI_SMEM_DOUTS_NUM_S  16
/* SPI_MEM_SPI_SMEM_DOUT7_NUM:R/W；比特位置：[15:14]；默认值：2'h0；*/
/*描述：输出信号被系统时钟周期延迟0：无延迟输出1：带clk_apb的偏序输出2：带clk _apb的负边输出3：带clk160的偏序的输出4：带clk260的负边的输出5：带spi_clk的高边输出6：带spi_clk的低边输出*/
#define SPI_MEM_SPI_SMEM_DOUT7_NUM  0x00000003
#define SPI_MEM_SPI_SMEM_DOUT7_NUM_M  ((SPI_MEM_SPI_SMEM_DOUT7_NUM_V)<<(SPI_MEM_SPI_SMEM_DOUT7_NUM_S))
#define SPI_MEM_SPI_SMEM_DOUT7_NUM_V  0x3
#define SPI_MEM_SPI_SMEM_DOUT7_NUM_S  14
/* SPI_MEM_SPI_SMEM_DOUT6_NUM：随机；比特位置：[13:12]；默认值：2'h0；*/
/*描述：输出信号被系统时钟周期延迟0：无延迟输出1：带clk_apb的偏序输出2：带clk _apb的负边输出3：带clk160的偏序的输出4：带clk260的负边的输出5：带spi_clk的高边输出6：带spi_clk的低边输出*/
#define SPI_MEM_SPI_SMEM_DOUT6_NUM  0x00000003
#define SPI_MEM_SPI_SMEM_DOUT6_NUM_M  ((SPI_MEM_SPI_SMEM_DOUT6_NUM_V)<<(SPI_MEM_SPI_SMEM_DOUT6_NUM_S))
#define SPI_MEM_SPI_SMEM_DOUT6_NUM_V  0x3
#define SPI_MEM_SPI_SMEM_DOUT6_NUM_S  12
/* SPI_MEM_SPI_SMEM_DOUT5_NUM:R/W；比特位置：[11:10]；默认值：2'h0；*/
/*描述：输出信号被系统时钟周期延迟0：无延迟输出1：带clk_apb的偏序输出2：带clk _apb的负边输出3：带clk160的偏序的输出4：带clk260的负边的输出5：带spi_clk的高边输出6：带spi_clk的低边输出*/
#define SPI_MEM_SPI_SMEM_DOUT5_NUM  0x00000003
#define SPI_MEM_SPI_SMEM_DOUT5_NUM_M  ((SPI_MEM_SPI_SMEM_DOUT5_NUM_V)<<(SPI_MEM_SPI_SMEM_DOUT5_NUM_S))
#define SPI_MEM_SPI_SMEM_DOUT5_NUM_V  0x3
#define SPI_MEM_SPI_SMEM_DOUT5_NUM_S  10
/* SPI_MEM_SPI_SMEM_DOUT4_NUM:R/W；比特位置：[9:8]；默认值：2'h0；*/
/*描述：输出信号被系统时钟周期延迟0：无延迟输出1：带clk_apb的偏序输出2：带clk _apb的负边输出3：带clk160的偏序的输出4：带clk260的负边的输出5：带spi_clk的高边输出6：带spi_clk的低边输出*/
#define SPI_MEM_SPI_SMEM_DOUT4_NUM  0x00000003
#define SPI_MEM_SPI_SMEM_DOUT4_NUM_M  ((SPI_MEM_SPI_SMEM_DOUT4_NUM_V)<<(SPI_MEM_SPI_SMEM_DOUT4_NUM_S))
#define SPI_MEM_SPI_SMEM_DOUT4_NUM_V  0x3
#define SPI_MEM_SPI_SMEM_DOUT4_NUM_S  8
/* SPI_MEM_SPI_SMEM_DOUT3_NUM:R/W；位位置：[7:6]；默认值：2'h0；*/
/*描述：输出信号延迟系统时钟周期0：延迟1个周期1：延迟2个周期。。。*/
#define SPI_MEM_SPI_SMEM_DOUT3_NUM  0x00000003
#define SPI_MEM_SPI_SMEM_DOUT3_NUM_M  ((SPI_MEM_SPI_SMEM_DOUT3_NUM_V)<<(SPI_MEM_SPI_SMEM_DOUT3_NUM_S))
#define SPI_MEM_SPI_SMEM_DOUT3_NUM_V  0x3
#define SPI_MEM_SPI_SMEM_DOUT3_NUM_S  6
/* SPI_MEM_SPI_SMEM_DOUT2_NUM:R/W；比特位置：[5:4]；默认值：2'h0；*/
/*描述：输出信号延迟系统时钟周期0：延迟1个周期1：延迟2个周期。。。*/
#define SPI_MEM_SPI_SMEM_DOUT2_NUM  0x00000003
#define SPI_MEM_SPI_SMEM_DOUT2_NUM_M  ((SPI_MEM_SPI_SMEM_DOUT2_NUM_V)<<(SPI_MEM_SPI_SMEM_DOUT2_NUM_S))
#define SPI_MEM_SPI_SMEM_DOUT2_NUM_V  0x3
#define SPI_MEM_SPI_SMEM_DOUT2_NUM_S  4
/* SPI_MEM_SPI_SMEM_DOUT1_NUM:R/W；位位置：[3:2]；默认值：2'h0；*/
/*描述：输出信号延迟系统时钟周期0：延迟1个周期1：延迟2个周期。。。*/
#define SPI_MEM_SPI_SMEM_DOUT1_NUM  0x00000003
#define SPI_MEM_SPI_SMEM_DOUT1_NUM_M  ((SPI_MEM_SPI_SMEM_DOUT1_NUM_V)<<(SPI_MEM_SPI_SMEM_DOUT1_NUM_S))
#define SPI_MEM_SPI_SMEM_DOUT1_NUM_V  0x3
#define SPI_MEM_SPI_SMEM_DOUT1_NUM_S  2
/* SPI_MEM_SPI_SMEM_DOUT0_NUM:R/W；位位置：[1:0]；默认值：2'h0；*/
/*描述：输出信号延迟系统时钟周期0：延迟1个周期1：延迟2个周期。。。*/
#define SPI_MEM_SPI_SMEM_DOUT0_NUM  0x00000003
#define SPI_MEM_SPI_SMEM_DOUT0_NUM_M  ((SPI_MEM_SPI_SMEM_DOUT0_NUM_V)<<(SPI_MEM_SPI_SMEM_DOUT0_NUM_S))
#define SPI_MEM_SPI_SMEM_DOUT0_NUM_V  0x3
#define SPI_MEM_SPI_SMEM_DOUT0_NUM_S  0

#define SPI_MEM_SPI_SMEM_AC_REG(i)          (REG_SPI_MEM_BASE(i) + 0x0D0)
/* SPI_MEM_SPI_SMEM_CS_HOLD_TIME:R/W；比特位置：[27:15]；默认值：13'h1；*/
/*描述：对于spi0，spi-cs信号被spi时钟延迟为无效，该位与spi_mem_cs_hold位组合。*/
#define SPI_MEM_SPI_SMEM_CS_HOLD_TIME  0x00001FFF
#define SPI_MEM_SPI_SMEM_CS_HOLD_TIME_M  ((SPI_MEM_SPI_SMEM_CS_HOLD_TIME_V)<<(SPI_MEM_SPI_SMEM_CS_HOLD_TIME_S))
#define SPI_MEM_SPI_SMEM_CS_HOLD_TIME_V  0x1FFF
#define SPI_MEM_SPI_SMEM_CS_HOLD_TIME_S  15
/* SPI_MEM_SPI_SMEM_CS_SETUP_TIME:R/W；比特位置：[14:2]；默认值：13'h1；*/
/*description:对于spi时钟准备阶段的spi0（周期-1），此位与spi_mem_cs_setup位组合。*/
#define SPI_MEM_SPI_SMEM_CS_SETUP_TIME  0x00001FFF
#define SPI_MEM_SPI_SMEM_CS_SETUP_TIME_M  ((SPI_MEM_SPI_SMEM_CS_SETUP_TIME_V)<<(SPI_MEM_SPI_SMEM_CS_SETUP_TIME_S))
#define SPI_MEM_SPI_SMEM_CS_SETUP_TIME_V  0x1FFF
#define SPI_MEM_SPI_SMEM_CS_SETUP_TIME_S  2
/* SPI_MEM_SPI_SMEM_CS_HOLD:R/W；位位置：[1]；默认值：1’b0；*/
/*描述：对于spi0，当spi处于完成阶段时，spi cs保持低。1： 启用0：禁用。*/
#define SPI_MEM_SPI_SMEM_CS_HOLD  (BIT(1))
#define SPI_MEM_SPI_SMEM_CS_HOLD_M  (BIT(1))
#define SPI_MEM_SPI_SMEM_CS_HOLD_V  0x1
#define SPI_MEM_SPI_SMEM_CS_HOLD_S  1
/* SPI_MEM_SPI_SMEM_CS_SETUP:R/W；位位置：[0]；默认值：1’b0；*/
/*description:对于spi0，当spi处于准备阶段时，启用spi cs。1： 启用0：禁用。*/
#define SPI_MEM_SPI_SMEM_CS_SETUP  (BIT(0))
#define SPI_MEM_SPI_SMEM_CS_SETUP_M  (BIT(0))
#define SPI_MEM_SPI_SMEM_CS_SETUP_V  0x1
#define SPI_MEM_SPI_SMEM_CS_SETUP_S  0

#define SPI_MEM_DDR_REG(i)          (REG_SPI_MEM_BASE(i) + 0x0D4)
/* SPI_MEM_SPI_FMEM_DDR_DQS_LOOP_MODE：R/W；比特位置：[23:22]；默认值：2’b0；*/
/*描述：这些位与用于在ddr模式中选择数据选通生成模式的位spifmem_ddr_fdqs循环组合。*/
#define SPI_MEM_SPI_FMEM_DDR_DQS_LOOP_MODE  0x00000003
#define SPI_MEM_SPI_FMEM_DDR_DQS_LOOP_MODE_M  ((SPI_MEM_SPI_FMEM_DDR_DQS_LOOP_MODE_V)<<(SPI_MEM_SPI_FMEM_DDR_DQS_LOOP_MODE_S))
#define SPI_MEM_SPI_FMEM_DDR_DQS_LOOP_MODE_V  0x3
#define SPI_MEM_SPI_FMEM_DDR_DQS_LOOP_MODE_S  22
/* SPI_MEM_SPI_FMEM_DDR_DQS_LOOP:R/W；位位置：[21]；默认值：1’b0；*/
/*description:数据选通由SPI生成。*/
#define SPI_MEM_SPI_FMEM_DDR_DQS_LOOP  (BIT(21))
#define SPI_MEM_SPI_FMEM_DDR_DQS_LOOP_M  (BIT(21))
#define SPI_MEM_SPI_FMEM_DDR_DQS_LOOP_V  0x1
#define SPI_MEM_SPI_FMEM_DDR_DQS_LOOP_S  21
/* SPI_MEM_SPI_FMEM_USR_DDR_DQS_THD:R/W；比特位置：[20:13]；默认值：8'b0；*/
/*描述：基于SPI时钟从存储器中读取的数据选通的延迟数。*/
#define SPI_MEM_SPI_FMEM_USR_DDR_DQS_THD  0x000000FF
#define SPI_MEM_SPI_FMEM_USR_DDR_DQS_THD_M  ((SPI_MEM_SPI_FMEM_USR_DDR_DQS_THD_V)<<(SPI_MEM_SPI_FMEM_USR_DDR_DQS_THD_S))
#define SPI_MEM_SPI_FMEM_USR_DDR_DQS_THD_V  0xFF
#define SPI_MEM_SPI_FMEM_USR_DDR_DQS_THD_S  13
/* SPI_MEM_SPI_FMEM_outmin字节：R/W；比特位置：[12:5]；默认值：8'b1；*/
/*description:这是panda设备中的最小输出数据长度。*/
#define SPI_MEM_SPI_FMEM_OUTMINBYTELEN  0x000000FF
#define SPI_MEM_SPI_FMEM_OUTMINBYTELEN_M  ((SPI_MEM_SPI_FMEM_OUTMINBYTELEN_V)<<(SPI_MEM_SPI_FMEM_OUTMINBYTELEN_S))
#define SPI_MEM_SPI_FMEM_OUTMINBYTELEN_V  0xFF
#define SPI_MEM_SPI_FMEM_OUTMINBYTELEN_S  5
/* SPI_MEM_SPI_FMEM_DDR_CMD_DIS:R/W；位位置：[4]；默认值：1’b0；*/
/*描述：当ddr模式时，该位用于在命令阶段禁用双边缘。*/
#define SPI_MEM_SPI_FMEM_DDR_CMD_DIS  (BIT(4))
#define SPI_MEM_SPI_FMEM_DDR_CMD_DIS_M  (BIT(4))
#define SPI_MEM_SPI_FMEM_DDR_CMD_DIS_V  0x1
#define SPI_MEM_SPI_FMEM_DDR_CMD_DIS_S  4
/* SPI_MEM_SPI_FMEM_DDR_WDAT_SWP:R/W；位位置：[3]；默认值：1’b0；*/
/*description:设置位以重新排序spi-ddr模式下单词的tx数据。*/
#define SPI_MEM_SPI_FMEM_DDR_WDAT_SWP  (BIT(3))
#define SPI_MEM_SPI_FMEM_DDR_WDAT_SWP_M  (BIT(3))
#define SPI_MEM_SPI_FMEM_DDR_WDAT_SWP_V  0x1
#define SPI_MEM_SPI_FMEM_DDR_WDAT_SWP_S  3
/* SPI_MEM_SPI_FMEM_DDR_RDAT_SWP:R/W；位位置：[2]；默认值：1’b0；*/
/*description:设置位以重新排序spi-ddr模式下单词的rx数据。*/
#define SPI_MEM_SPI_FMEM_DDR_RDAT_SWP  (BIT(2))
#define SPI_MEM_SPI_FMEM_DDR_RDAT_SWP_M  (BIT(2))
#define SPI_MEM_SPI_FMEM_DDR_RDAT_SWP_V  0x1
#define SPI_MEM_SPI_FMEM_DDR_RDAT_SWP_S  2
/* SPI_MEM_SPI_FMEM_VAR_DUMMY:R/W；位位置：[1]；默认值：1’b0；*/
/*description:设置位以启用spi-ddr模式下的可变虚拟周期。*/
#define SPI_MEM_SPI_FMEM_VAR_DUMMY  (BIT(1))
#define SPI_MEM_SPI_FMEM_VAR_DUMMY_M  (BIT(1))
#define SPI_MEM_SPI_FMEM_VAR_DUMMY_V  0x1
#define SPI_MEM_SPI_FMEM_VAR_DUMMY_S  1
/* SPI_MEM_SPI_FMEM_DDR_EN:R/W；位位置：[0]；默认值：1’b0；*/
/*描述：1：在ddr模式中0在sdr模式中*/
#define SPI_MEM_SPI_FMEM_DDR_EN  (BIT(0))
#define SPI_MEM_SPI_FMEM_DDR_EN_M  (BIT(0))
#define SPI_MEM_SPI_FMEM_DDR_EN_V  0x1
#define SPI_MEM_SPI_FMEM_DDR_EN_S  0

#define SPI_MEM_SPI_SMEM_DDR_REG(i)          (REG_SPI_MEM_BASE(i) + 0x0D8)
/* SPI_MEM_SPI_SMEM_DDR_DQS_LOOP_MODE：R/W；比特位置：[23:22]；默认值：2’b0；*/
/*描述：这些位与用于在ddr模式中选择数据选通生成模式的位spimem_ddr_fdqs循环组合。*/
#define SPI_MEM_SPI_SMEM_DDR_DQS_LOOP_MODE  0x00000003
#define SPI_MEM_SPI_SMEM_DDR_DQS_LOOP_MODE_M  ((SPI_MEM_SPI_SMEM_DDR_DQS_LOOP_MODE_V)<<(SPI_MEM_SPI_SMEM_DDR_DQS_LOOP_MODE_S))
#define SPI_MEM_SPI_SMEM_DDR_DQS_LOOP_MODE_V  0x3
#define SPI_MEM_SPI_SMEM_DDR_DQS_LOOP_MODE_S  22
/* SPI_MEM_SPI_SMEM_DDR_DQS_LOOP:R/W；位位置：[21]；默认值：1’b0；*/
/*description:数据选通由SPI生成。*/
#define SPI_MEM_SPI_SMEM_DDR_DQS_LOOP  (BIT(21))
#define SPI_MEM_SPI_SMEM_DDR_DQS_LOOP_M  (BIT(21))
#define SPI_MEM_SPI_SMEM_DDR_DQS_LOOP_V  0x1
#define SPI_MEM_SPI_SMEM_DDR_DQS_LOOP_S  21
/* SPI_MEM_SPI_SMEM_USR_DDR_DQS_THD:R/W；比特位置：[20:13]；默认值：8'b0；*/
/*描述：基于SPI时钟从存储器中读取的数据选通的延迟数。*/
#define SPI_MEM_SPI_SMEM_USR_DDR_DQS_THD  0x000000FF
#define SPI_MEM_SPI_SMEM_USR_DDR_DQS_THD_M  ((SPI_MEM_SPI_SMEM_USR_DDR_DQS_THD_V)<<(SPI_MEM_SPI_SMEM_USR_DDR_DQS_THD_S))
#define SPI_MEM_SPI_SMEM_USR_DDR_DQS_THD_V  0xFF
#define SPI_MEM_SPI_SMEM_USR_DDR_DQS_THD_S  13
/* SPI_MEM_SPI_SMEM_outmin字节：R/W；比特位置：[12:5]；默认值：8'b1；*/
/*description:这是ddr-psram中的最小输出数据长度。*/
#define SPI_MEM_SPI_SMEM_OUTMINBYTELEN  0x000000FF
#define SPI_MEM_SPI_SMEM_OUTMINBYTELEN_M  ((SPI_MEM_SPI_SMEM_OUTMINBYTELEN_V)<<(SPI_MEM_SPI_SMEM_OUTMINBYTELEN_S))
#define SPI_MEM_SPI_SMEM_OUTMINBYTELEN_V  0xFF
#define SPI_MEM_SPI_SMEM_OUTMINBYTELEN_S  5
/* SPI_MEM_SPI_SMEM_DDR_CMD_DIS:R/W；位位置：[4]；默认值：1’b0；*/
/*描述：当ddr模式时，该位用于在命令阶段禁用双边缘。*/
#define SPI_MEM_SPI_SMEM_DDR_CMD_DIS  (BIT(4))
#define SPI_MEM_SPI_SMEM_DDR_CMD_DIS_M  (BIT(4))
#define SPI_MEM_SPI_SMEM_DDR_CMD_DIS_V  0x1
#define SPI_MEM_SPI_SMEM_DDR_CMD_DIS_S  4
/* SPI_MEM_SPI_SMEM_DDR_WDAT_SWP:R/W；位位置：[3]；默认值：1’b0；*/
/*description:设置位以重新排序spi-ddr模式下单词的tx数据。*/
#define SPI_MEM_SPI_SMEM_DDR_WDAT_SWP  (BIT(3))
#define SPI_MEM_SPI_SMEM_DDR_WDAT_SWP_M  (BIT(3))
#define SPI_MEM_SPI_SMEM_DDR_WDAT_SWP_V  0x1
#define SPI_MEM_SPI_SMEM_DDR_WDAT_SWP_S  3
/* SPI_MEM_SPI_SMEM_DDR_RDAT_SWP:R/W；位位置：[2]；默认值：1’b0；*/
/*description:设置位以重新排序spi-ddr模式下单词的rx数据。*/
#define SPI_MEM_SPI_SMEM_DDR_RDAT_SWP  (BIT(2))
#define SPI_MEM_SPI_SMEM_DDR_RDAT_SWP_M  (BIT(2))
#define SPI_MEM_SPI_SMEM_DDR_RDAT_SWP_V  0x1
#define SPI_MEM_SPI_SMEM_DDR_RDAT_SWP_S  2
/* SPI_MEM_SPI_SMEM_VAR_DUMMY:R/W；位位置：[1]；默认值：1’b0；*/
/*description:设置位以启用spi-ddr模式下的可变虚拟周期。*/
#define SPI_MEM_SPI_SMEM_VAR_DUMMY  (BIT(1))
#define SPI_MEM_SPI_SMEM_VAR_DUMMY_M  (BIT(1))
#define SPI_MEM_SPI_SMEM_VAR_DUMMY_V  0x1
#define SPI_MEM_SPI_SMEM_VAR_DUMMY_S  1
/* SPI_MEM_SPI_SMEM_DDR_EN:R/W；位位置：[0]；默认值：1’b0；*/
/*描述：1：在ddr模式中0在sdr模式中*/
#define SPI_MEM_SPI_SMEM_DDR_EN  (BIT(0))
#define SPI_MEM_SPI_SMEM_DDR_EN_M  (BIT(0))
#define SPI_MEM_SPI_SMEM_DDR_EN_V  0x1
#define SPI_MEM_SPI_SMEM_DDR_EN_S  0

#define SPI_MEM_CLOCK_GATE_REG(i)          (REG_SPI_MEM_BASE(i) + 0x0DC)
/* SPI_MEM_CLK_EN:R/W；位位置：[0]；默认值：1’b1；*/
/*说明：*/
#define SPI_MEM_CLK_EN  (BIT(0))
#define SPI_MEM_CLK_EN_M  (BIT(0))
#define SPI_MEM_CLK_EN_V  0x1
#define SPI_MEM_CLK_EN_S  0

#define SPI_MEM_DATE_REG(i)          (REG_SPI_MEM_BASE(i) + 0x3FC)
/* SPI_MEM_DATE:R/W；位位置：[27:0]；默认值：28'h1905270；*/
/*description:SPI寄存器版本。*/
#define SPI_MEM_DATE  0x0FFFFFFF
#define SPI_MEM_DATE_M  ((SPI_MEM_DATE_V)<<(SPI_MEM_DATE_S))
#define SPI_MEM_DATE_V  0xFFFFFFF
#define SPI_MEM_DATE_S  0

#ifdef __cplusplus
}
#endif



#endif /*_SOC_SPI_MEM_REG_H_ */

