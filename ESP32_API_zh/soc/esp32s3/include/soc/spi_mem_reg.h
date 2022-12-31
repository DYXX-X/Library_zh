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
#ifndef _SOC_SPI_MEM_REG_H_
#define _SOC_SPI_MEM_REG_H_


#include "soc.h"
#ifdef __cplusplus
extern "C" {
#endif

#define SPI_MEM_CMD_REG(i)          (REG_SPI_MEM_BASE(i) + 0x0)
/* SPI_MEM_FLASH_READ：R/W/SC；位位置：[31]；默认值：1’b0；*/
/*description:读取闪存启用。设置位时，将触发读取闪存操作。操作完成后，该位将被清除。1： 启用0:禁用。*/
#define SPI_MEM_FLASH_READ    (BIT(31))
#define SPI_MEM_FLASH_READ_M  (BIT(31))
#define SPI_MEM_FLASH_READ_V  0x1
#define SPI_MEM_FLASH_READ_S  31
/* SPI_MEM_FLASH_WREN：R/W/SC；位位置：[30]；默认值：1’b0；*/
/*description:写入闪存启用。设置位时，将发送写入启用命令。操作完成后，该位将被清除。1： 启用0:禁用。*/
#define SPI_MEM_FLASH_WREN    (BIT(30))
#define SPI_MEM_FLASH_WREN_M  (BIT(30))
#define SPI_MEM_FLASH_WREN_V  0x1
#define SPI_MEM_FLASH_WREN_S  30
/* SPI_MEM_FLASH_WRDI:R/W/SC；位位置：[29]；默认值：1’b0；*/
/*description:写入闪存禁用。设置位时将发送写禁用命令。操作完成后，该位将被清除。1： 启用0:禁用。*/
#define SPI_MEM_FLASH_WRDI    (BIT(29))
#define SPI_MEM_FLASH_WRDI_M  (BIT(29))
#define SPI_MEM_FLASH_WRDI_V  0x1
#define SPI_MEM_FLASH_WRDI_S  29
/* SPI_MEM_FLASH_rid:R/W/SC；位位置：[28]；默认值：1’b0；*/
/*description:读取JEDEC ID。设置位时将发送读取ID命令。操作完成后，该位将被清除。1： 启用0:禁用。*/
#define SPI_MEM_FLASH_RDID    (BIT(28))
#define SPI_MEM_FLASH_RDID_M  (BIT(28))
#define SPI_MEM_FLASH_RDID_V  0x1
#define SPI_MEM_FLASH_RDID_S  28
/* SPI_MEM_FLASH_RDSR:R/W/SC；位位置：[27]；默认值：1’b0；*/
/*description:读取状态寄存器-1。设置位时将触发读取状态操作。操作完成后，该位将被清除。1： 启用0:禁用。*/
#define SPI_MEM_FLASH_RDSR    (BIT(27))
#define SPI_MEM_FLASH_RDSR_M  (BIT(27))
#define SPI_MEM_FLASH_RDSR_V  0x1
#define SPI_MEM_FLASH_RDSR_S  27
/* SPI_MEM_FLASH_WRSR:R/W/SC；位位置：[26]；默认值：1’b0；*/
/*description:写入状态寄存器启用。设置位时将触发写入状态操作。操作完成后，该位将被清除。1： 启用0:禁用。*/
#define SPI_MEM_FLASH_WRSR    (BIT(26))
#define SPI_MEM_FLASH_WRSR_M  (BIT(26))
#define SPI_MEM_FLASH_WRSR_V  0x1
#define SPI_MEM_FLASH_WRSR_S  26
/* SPI_MEM_FLASH_PP:R/W/SC；位位置：[25]；默认值：1’b0；*/
/*description:页面程序启用（要编程的数据为1字节~64字节）。设置位时将触发页面程序操作。一旦操作完成，该位将被清除。1:启用0:禁用。*/
#define SPI_MEM_FLASH_PP    (BIT(25))
#define SPI_MEM_FLASH_PP_M  (BIT(25))
#define SPI_MEM_FLASH_PP_V  0x1
#define SPI_MEM_FLASH_PP_S  25
/* SPI_MEM_FLASH_SE:R/W/SC；位位置：[24]；默认值：1’b0；*/
/*description:扇区擦除启用（4KB）。设置位时将触发扇区擦除操作。操作完成后，该位将被清除。1： 启用0:禁用。*/
#define SPI_MEM_FLASH_SE    (BIT(24))
#define SPI_MEM_FLASH_SE_M  (BIT(24))
#define SPI_MEM_FLASH_SE_V  0x1
#define SPI_MEM_FLASH_SE_S  24
/* SPI_MEM_FLASH_BE:R/W/SC；位位置：[23]；默认值：1’b0；*/
/*description:块擦除启用（32KB）。设置位时将触发块擦除操作。操作完成后，该位将被清除。1： 启用0:禁用。*/
#define SPI_MEM_FLASH_BE    (BIT(23))
#define SPI_MEM_FLASH_BE_M  (BIT(23))
#define SPI_MEM_FLASH_BE_V  0x1
#define SPI_MEM_FLASH_BE_S  23
/* SPI_MEM_FLASH_CE:R/W/SC；位位置：[22]；默认值：1’b0；*/
/*description:芯片擦除启用。设置位时将触发芯片擦除操作。操作完成后，该位将被清除。1： 启用0:禁用。*/
#define SPI_MEM_FLASH_CE    (BIT(22))
#define SPI_MEM_FLASH_CE_M  (BIT(22))
#define SPI_MEM_FLASH_CE_V  0x1
#define SPI_MEM_FLASH_CE_S  22
/* SPI_MEM_FLASH_DP:R/W/SC；位位置：[21]；默认值：1’b0；*/
/*description:驱动Flash关闭电源。设置位时将触发操作。操作完成后，该位将被清除。1： 启用0:禁用。*/
#define SPI_MEM_FLASH_DP    (BIT(21))
#define SPI_MEM_FLASH_DP_M  (BIT(21))
#define SPI_MEM_FLASH_DP_V  0x1
#define SPI_MEM_FLASH_DP_S  21
/* SPI_MEM_FLASH_RES:R/W/SC；位位置：[20]；默认值：1’b0；*/
/*description:此位与SPI_MEM_RESANRES位组合，将Flash从断电状态或高性能模式释放，并获取设备ID。一旦操作完成，该位将被清除。1： 启用0:禁用。*/
#define SPI_MEM_FLASH_RES    (BIT(20))
#define SPI_MEM_FLASH_RES_M  (BIT(20))
#define SPI_MEM_FLASH_RES_V  0x1
#define SPI_MEM_FLASH_RES_S  20
/* SPI_MEM_FLASH-HPM:R/W/SC；位位置：[19]；默认值：1’b0；*/
/*description:将Flash驱动到高性能模式。操作完成后，该位将被清除。1： 启用0:禁用。*/
#define SPI_MEM_FLASH_HPM    (BIT(19))
#define SPI_MEM_FLASH_HPM_M  (BIT(19))
#define SPI_MEM_FLASH_HPM_V  0x1
#define SPI_MEM_FLASH_HPM_S  19
/* SPI_MEM_USR:R/W/SC；位位置：[18]；默认值：1’b0；*/
/*description:用户定义命令启用。设置位时将触发操作。操作完成后，该位将被清除。1： 启用0:禁用。*/
#define SPI_MEM_USR    (BIT(18))
#define SPI_MEM_USR_M  (BIT(18))
#define SPI_MEM_USR_V  0x1
#define SPI_MEM_USR_S  18
/* SPI_MEM_FLASH_PE:R/W/SC；位位置：[17]；默认值：1’b0；*/
/*description:在用户模式下，设置为指示将触发编程/擦除操作。该位与SPI_MEM_USR位组合。操作完成后，该位将被清除。1： 启用0:禁用。*/
#define SPI_MEM_FLASH_PE    (BIT(17))
#define SPI_MEM_FLASH_PE_M  (BIT(17))
#define SPI_MEM_FLASH_PE_V  0x1
#define SPI_MEM_FLASH_PE_S  17

#define SPI_MEM_ADDR_REG(i)          (REG_SPI_MEM_BASE(i) + 0x4)
/* SPI_MEM_USR_ADDR_值：R/W；位位置：[31:0]；默认值：32'h0；*/
/*description:在用户模式下，它是内存地址。除此之外，位0至位23是存储器地址，位24至位31是传输的字节长度。。*/
#define SPI_MEM_USR_ADDR_VALUE    0xFFFFFFFF
#define SPI_MEM_USR_ADDR_VALUE_M  ((SPI_MEM_USR_ADDR_VALUE_V)<<(SPI_MEM_USR_ADDR_VALUE_S))
#define SPI_MEM_USR_ADDR_VALUE_V  0xFFFFFFFF
#define SPI_MEM_USR_ADDR_VALUE_S  0

#define SPI_MEM_CTRL_REG(i)          (REG_SPI_MEM_BASE(i) + 0x8)
/* SPI_MEM_FREAD_QIO:R/W；位位置：[24]；默认值：1’b0；*/
/*描述：在硬件0xEB读取操作中，ADDR相位和DIN相位应用4个信号（4位模式）。1： 启用0:禁用。*/
#define SPI_MEM_FREAD_QIO    (BIT(24))
#define SPI_MEM_FREAD_QIO_M  (BIT(24))
#define SPI_MEM_FREAD_QIO_V  0x1
#define SPI_MEM_FREAD_QIO_S  24
/* SPI_MEM_FREAD_DIO:R/W；位位置：[23]；默认值：1’b0；*/
/*描述：在硬件0xBB读取操作中，ADDR相位和DIN相位应用2个信号（2位模式）。1： 启用0:禁用。*/
#define SPI_MEM_FREAD_DIO    (BIT(23))
#define SPI_MEM_FREAD_DIO_M  (BIT(23))
#define SPI_MEM_FREAD_DIO_V  0x1
#define SPI_MEM_FREAD_DIO_S  23
/* SPI_MEM_wrsr2b:R/W；位位置：[22]；默认值：1’b0；*/
/*description:设置状态寄存器时，两个字节的数据将写入状态寄存器。1： 启用0:禁用。*/
#define SPI_MEM_WRSR_2B    (BIT(22))
#define SPI_MEM_WRSR_2B_M  (BIT(22))
#define SPI_MEM_WRSR_2B_V  0x1
#define SPI_MEM_WRSR_2B_S  22
/* SPI_MEM_WP_REG:R/W；位位置：[21]；默认值：1’b1；*/
/*description:SPI空闲时写保护信号输出。1： 输出高，0：输出低。*/
#define SPI_MEM_WP_REG    (BIT(21))
#define SPI_MEM_WP_REG_M  (BIT(21))
#define SPI_MEM_WP_REG_V  0x1
#define SPI_MEM_WP_REG_S  21
/* SPI_MEM_FREAD_QUAD:R/W；位位置：[20]；默认值：1’b0；*/
/*描述：在硬件0x6B读取操作中，DIN相位应用4个信号（4位模式）。1： 启用0:禁用。*/
#define SPI_MEM_FREAD_QUAD    (BIT(20))
#define SPI_MEM_FREAD_QUAD_M  (BIT(20))
#define SPI_MEM_FREAD_QUAD_V  0x1
#define SPI_MEM_FREAD_QUAD_S  20
/* SPI_MEM_D_POL:R/W；位位置：[19]；默认值：1’b1；*/
/*description:该位用于设置MOSI线极性，1：高0，低。*/
#define SPI_MEM_D_POL    (BIT(19))
#define SPI_MEM_D_POL_M  (BIT(19))
#define SPI_MEM_D_POL_V  0x1
#define SPI_MEM_D_POL_S  19
/* SPI_MEM_Q_POL:R/W；位位置：[18]；默认值：1’b1；*/
/*description:该位用于设置MISO线极性，1：高0，低。*/
#define SPI_MEM_Q_POL    (BIT(18))
#define SPI_MEM_Q_POL_M  (BIT(18))
#define SPI_MEM_Q_POL_V  0x1
#define SPI_MEM_Q_POL_S  18
/* SPI_MEM_RESANDRES:R/W；位位置：[15]；默认值：1’b1；*/
/*description:设备ID被读出到SPI_MEM_RD_STATUS寄存器，该位与SPI_MEM_flash_res位组合。1： 启用0:禁用。*/
#define SPI_MEM_RESANDRES    (BIT(15))
#define SPI_MEM_RESANDRES_M  (BIT(15))
#define SPI_MEM_RESANDRES_V  0x1
#define SPI_MEM_RESANDRES_S  15
/* SPI_MEM_FREAD_DUAL:R/W；位位置：[14]；默认值：1’b0；*/
/*description: 在硬件0x3B读取操作中，DIN相位施加2个信号。1： 启用0:禁用
. .*/
#define SPI_MEM_FREAD_DUAL    (BIT(14))
#define SPI_MEM_FREAD_DUAL_M  (BIT(14))
#define SPI_MEM_FREAD_DUAL_V  0x1
#define SPI_MEM_FREAD_DUAL_S  14
/* SPI_MEM_FASTRD_MODE：R/W；位位置：[13]；默认值：1’b1；*/
/*description:当设置SPI_MEM_FREAD_QIO、SPI_MEM-FREAD_DIO、SPI-MEM_FREAD_DQUAD或SPI_MEM.FREAD_DUAL时，应设置此位。。*/
#define SPI_MEM_FASTRD_MODE    (BIT(13))
#define SPI_MEM_FASTRD_MODE_M  (BIT(13))
#define SPI_MEM_FASTRD_MODE_V  0x1
#define SPI_MEM_FASTRD_MODE_S  13
/* SPI_MEM_TX_CRC_EN:R/W；位位置：[11]；默认值：1’b0；*/
/*description:对于SPI1，在将加密数据写入闪存时启用crc32。1： 启用0：禁用。*/
#define SPI_MEM_TX_CRC_EN    (BIT(11))
#define SPI_MEM_TX_CRC_EN_M  (BIT(11))
#define SPI_MEM_TX_CRC_EN_V  0x1
#define SPI_MEM_TX_CRC_EN_S  11
/* SPI_MEM_FCS_CRC_EN:R/W；位位置：[10]；默认值：1’b0；*/
/*description:对于SPI1，在将加密数据写入闪存之前初始化crc32模块。活动低。。*/
#define SPI_MEM_FCS_CRC_EN    (BIT(10))
#define SPI_MEM_FCS_CRC_EN_M  (BIT(10))
#define SPI_MEM_FCS_CRC_EN_V  0x1
#define SPI_MEM_FCS_CRC_EN_S  10
/* SPI_MEM_FCMD_OCT:R/W；位位置：[9]；默认值：1’b0；*/
/*description:设置此位以在CMD阶段启用8位模式（8-bm）。。*/
#define SPI_MEM_FCMD_OCT    (BIT(9))
#define SPI_MEM_FCMD_OCT_M  (BIT(9))
#define SPI_MEM_FCMD_OCT_V  0x1
#define SPI_MEM_FCMD_OCT_S  9
/* SPI_MEM_FCMD_QUAD:R/W；位位置：[8]；默认值：1’b0；*/
/*description:将此位设置为在CMD阶段启用4位模式（4-bm）。。*/
#define SPI_MEM_FCMD_QUAD    (BIT(8))
#define SPI_MEM_FCMD_QUAD_M  (BIT(8))
#define SPI_MEM_FCMD_QUAD_V  0x1
#define SPI_MEM_FCMD_QUAD_S  8
/* SPI_MEM_FCMD_DUAL:R/W；位位置：[7]；默认值：1’b0；*/
/*description:设置此位以在CMD阶段启用2位模式（2-bm）。。*/
#define SPI_MEM_FCMD_DUAL    (BIT(7))
#define SPI_MEM_FCMD_DUAL_M  (BIT(7))
#define SPI_MEM_FCMD_DUAL_V  0x1
#define SPI_MEM_FCMD_DUAL_S  7
/* SPI_MEM_FADDR_OCT:R/W；位位置：[6]；默认值：1’b0；*/
/*description:设置此位以在ADDR阶段启用8位模式（8-bm）。。*/
#define SPI_MEM_FADDR_OCT    (BIT(6))
#define SPI_MEM_FADDR_OCT_M  (BIT(6))
#define SPI_MEM_FADDR_OCT_V  0x1
#define SPI_MEM_FADDR_OCT_S  6
/* SPI_MEM_FDIN_OCT:R/W；位位置：[5]；默认值：1’b0；*/
/*description:设置此位以在DIN阶段启用8位模式（8-bm）。。*/
#define SPI_MEM_FDIN_OCT    (BIT(5))
#define SPI_MEM_FDIN_OCT_M  (BIT(5))
#define SPI_MEM_FDIN_OCT_V  0x1
#define SPI_MEM_FDIN_OCT_S  5
/* SPI_MEM_FDOUT_OCT:R/W；位位置：[4]；默认值：1’b0；*/
/*description:设置此位以在DOUT阶段启用8位模式（8-bm）。。*/
#define SPI_MEM_FDOUT_OCT    (BIT(4))
#define SPI_MEM_FDOUT_OCT_M  (BIT(4))
#define SPI_MEM_FDOUT_OCT_V  0x1
#define SPI_MEM_FDOUT_OCT_S  4
/* SPI_MEM_FDUMMY_OUT:R/W；位位置：[3]；默认值：1’b0；*/
/*描述：在DUMMY阶段，SPI总线的信号电平由SPI0控制器输出。。*/
#define SPI_MEM_FDUMMY_OUT    (BIT(3))
#define SPI_MEM_FDUMMY_OUT_M  (BIT(3))
#define SPI_MEM_FDUMMY_OUT_V  0x1
#define SPI_MEM_FDUMMY_OUT_S  3

#define SPI_MEM_CTRL1_REG(i)          (REG_SPI_MEM_BASE(i) + 0xC)
/* SPI_MEM_RXFIFO_RST:R/W；位位置：[30]；默认值：1’b0；*/
/*description: SPI0 RX FIFO复位信号。设置此位并在SPI0传输开始前清除
..*/
#define SPI_MEM_RXFIFO_RST    (BIT(30))
#define SPI_MEM_RXFIFO_RST_M  (BIT(30))
#define SPI_MEM_RXFIFO_RST_V  0x1
#define SPI_MEM_RXFIFO_RST_S  30
/* SPI_MEM_CS_HOLD_DLY_RES:R/W；位位置：[11:2]；默认值：10'h3ff；*/
/*描述：发送RES/DP/HPM/PES/PER命令后，SPI1可能会等待（SPI_MEM_CS_HOLD_DELAY_RES[9:0]4或*256）SPI_CLK周期。。*/
#define SPI_MEM_CS_HOLD_DLY_RES    0x000003FF
#define SPI_MEM_CS_HOLD_DLY_RES_M  ((SPI_MEM_CS_HOLD_DLY_RES_V)<<(SPI_MEM_CS_HOLD_DLY_RES_S))
#define SPI_MEM_CS_HOLD_DLY_RES_V  0x3FF
#define SPI_MEM_CS_HOLD_DLY_RES_S  2
/* SPI_MEM_CLK_MODE：R/W；位位置：[1:0]；默认值：2'h0；*/
/*描述：SPI总线时钟（SPI_CLK）模式位。0：当CS不活动时，SPI总线时钟（SPI_CLK）关闭1：SPI_CLK在SPI_CS不活动后延迟一个周期2：SPI_C在SPI_C不活动后推迟两个周期3：SPI_CLK始终打开。。*/
#define SPI_MEM_CLK_MODE    0x00000003
#define SPI_MEM_CLK_MODE_M  ((SPI_MEM_CLK_MODE_V)<<(SPI_MEM_CLK_MODE_S))
#define SPI_MEM_CLK_MODE_V  0x3
#define SPI_MEM_CLK_MODE_S  0

#define SPI_MEM_CTRL2_REG(i)          (REG_SPI_MEM_BASE(i) + 0x10)
/* SPI_MEM_SYNC_RESET：R/W/SC；位位置：[31]；默认值：1’b0；*/
/*description:将重置FSM。。*/
#define SPI_MEM_SYNC_RESET    (BIT(31))
#define SPI_MEM_SYNC_RESET_M  (BIT(31))
#define SPI_MEM_SYNC_RESET_V  0x1
#define SPI_MEM_SYNC_RESET_S  31
/* SPI_MEM_CS_HOLD_DELAY：R/W；位位置：[30:25]；默认值：6'd0；*/
/*描述：这些位用于设置访问闪存时SPI突发传输之间的最小CS高时间tSHSL。tSHSL是（SPI_MEM_CS_HOLD_DELAY[5:0]+1）MSPI核心时钟周期。。*/
#define SPI_MEM_CS_HOLD_DELAY    0x0000003F
#define SPI_MEM_CS_HOLD_DELAY_M  ((SPI_MEM_CS_HOLD_DELAY_V)<<(SPI_MEM_CS_HOLD_DELAY_S))
#define SPI_MEM_CS_HOLD_DELAY_V  0x3F
#define SPI_MEM_CS_HOLD_DELAY_S  25
/* SPI_MEM_ECC_16TO18_BYTE_EN:R/W；位位置：[14]；默认值：1’b0；*/
/*描述：设置此位以在访问闪存时启用MSPI ECC 16字节数据和2 ECC字节模式。。*/
#define SPI_MEM_ECC_16TO18_BYTE_EN    (BIT(14))
#define SPI_MEM_ECC_16TO18_BYTE_EN_M  (BIT(14))
#define SPI_MEM_ECC_16TO18_BYTE_EN_V  0x1
#define SPI_MEM_ECC_16TO18_BYTE_EN_S  14
/* SPI_MEM_ECC_SKIP_PAGE_CORNER:R/W；位位置：[13]；默认值：1’b1；*/
/*描述：1:MSPI在访问闪存时跳过页角。0：访问闪存时不跳过页角。。*/
#define SPI_MEM_ECC_SKIP_PAGE_CORNER    (BIT(13))
#define SPI_MEM_ECC_SKIP_PAGE_CORNER_M  (BIT(13))
#define SPI_MEM_ECC_SKIP_PAGE_CORNER_V  0x1
#define SPI_MEM_ECC_SKIP_PAGE_CORNER_S  13
/* SPI_MEM_ECC_CS_HOLD_TIME:R/W；比特位置：[12:10]；默认值：3'd3；*/
/*描述：SPI_MEM_CS_HOLD_TIME+SPI_MEM_ECC_CS_HOLD _TIME是访问闪存时ECC模式下的SPI_CS保持周期。。*/
#define SPI_MEM_ECC_CS_HOLD_TIME    0x00000007
#define SPI_MEM_ECC_CS_HOLD_TIME_M  ((SPI_MEM_ECC_CS_HOLD_TIME_V)<<(SPI_MEM_ECC_CS_HOLD_TIME_S))
#define SPI_MEM_ECC_CS_HOLD_TIME_V  0x7
#define SPI_MEM_ECC_CS_HOLD_TIME_S  10
/* SPI_MEM_CS_HOLD_TIME:R/W；比特位置：[9:5]；默认值：5'h1；*/
/*描述：SPI总线CS（SPI_CS）信号被SPI总线时钟（SPI_CLK）延迟到非活动状态，这是非ECC模式下的SPI_CS保持时间。这些位与SPI_MEM_CS_HOLD位组合。。*/
#define SPI_MEM_CS_HOLD_TIME    0x0000001F
#define SPI_MEM_CS_HOLD_TIME_M  ((SPI_MEM_CS_HOLD_TIME_V)<<(SPI_MEM_CS_HOLD_TIME_S))
#define SPI_MEM_CS_HOLD_TIME_V  0x1F
#define SPI_MEM_CS_HOLD_TIME_S  5
/* SPI_MEM_CS_SETUP_TIME:R/W；位位置：[4:0]；默认值：5'h1；*/
/*description:通过SPI_CLK（即SPI_CS设置时间）执行PREP阶段的（周期-1）。这些位与SPI_MEM_CS_SETUP位组合。。*/
#define SPI_MEM_CS_SETUP_TIME    0x0000001F
#define SPI_MEM_CS_SETUP_TIME_M  ((SPI_MEM_CS_SETUP_TIME_V)<<(SPI_MEM_CS_SETUP_TIME_S))
#define SPI_MEM_CS_SETUP_TIME_V  0x1F
#define SPI_MEM_CS_SETUP_TIME_S  0

#define SPI_MEM_CLOCK_REG(i)          (REG_SPI_MEM_BASE(i) + 0x14)
/* SPI_MEM_CLK_EQU_SYSCLK:R/W；位位置：[31]；默认值：1’b0；*/
/*描述：当SPI1访问闪存或Ext_RAM时，将此位设置为1分区模式，f_SPI_CLK=f_MSPI_CORE_CLK。。*/
#define SPI_MEM_CLK_EQU_SYSCLK    (BIT(31))
#define SPI_MEM_CLK_EQU_SYSCLK_M  (BIT(31))
#define SPI_MEM_CLK_EQU_SYSCLK_V  0x1
#define SPI_MEM_CLK_EQU_SYSCLK_S  31
/* SPI_MEM_CLKCNT_N:R/W；比特位置：[23:16]；默认值：8'h3；*/
/*描述：当SPI1访问闪存或Ext_RAM时，f_SPI_CLK=f_MSPI_CORE_CLK/（SPI_MEM_CLKCNT_N+1）。*/
#define SPI_MEM_CLKCNT_N    0x000000FF
#define SPI_MEM_CLKCNT_N_M  ((SPI_MEM_CLKCNT_N_V)<<(SPI_MEM_CLKCNT_N_S))
#define SPI_MEM_CLKCNT_N_V  0xFF
#define SPI_MEM_CLKCNT_N_S  16
/* SPI_MEM_CLKCNT_H:R/W；比特位置：[15:8]；默认值：8'h1；*/
/*description:必须是下限值（（SPI_MEM_CLKCNT_N+1）/2-1）。。*/
#define SPI_MEM_CLKCNT_H    0x000000FF
#define SPI_MEM_CLKCNT_H_M  ((SPI_MEM_CLKCNT_H_V)<<(SPI_MEM_CLKCNT_H_S))
#define SPI_MEM_CLKCNT_H_V  0xFF
#define SPI_MEM_CLKCNT_H_S  8
/* SPI_MEM_CLKCNT_L:R/W；位位置：[7:0]；默认值：8'h3；*/
/*description:它必须等于SPI_MEM_CLKCNT_N的值。*/
#define SPI_MEM_CLKCNT_L    0x000000FF
#define SPI_MEM_CLKCNT_L_M  ((SPI_MEM_CLKCNT_L_V)<<(SPI_MEM_CLKCNT_L_S))
#define SPI_MEM_CLKCNT_L_V  0xFF
#define SPI_MEM_CLKCNT_L_S  0

#define SPI_MEM_USER_REG(i)          (REG_SPI_MEM_BASE(i) + 0x18)
/* SPI_MEM_USR_COMMAND:R/W；位位置：[31]；默认值：1’b1；*/
/*description:设置此位以启用操作的CMD阶段。。*/
#define SPI_MEM_USR_COMMAND    (BIT(31))
#define SPI_MEM_USR_COMMAND_M  (BIT(31))
#define SPI_MEM_USR_COMMAND_V  0x1
#define SPI_MEM_USR_COMMAND_S  31
/* SPI_MEM_USR_ADDR:R/W；位位置：[30]；默认值：1’b0；*/
/*description:设置此位以启用操作的ADDR阶段。。*/
#define SPI_MEM_USR_ADDR    (BIT(30))
#define SPI_MEM_USR_ADDR_M  (BIT(30))
#define SPI_MEM_USR_ADDR_V  0x1
#define SPI_MEM_USR_ADDR_S  30
/* SPI_MEM_USR_DUMMY:R/W；位位置：[29]；默认值：1’b0；*/
/*description:设置此位以启用操作的DUMMY阶段。。*/
#define SPI_MEM_USR_DUMMY    (BIT(29))
#define SPI_MEM_USR_DUMMY_M  (BIT(29))
#define SPI_MEM_USR_DUMMY_V  0x1
#define SPI_MEM_USR_DUMMY_S  29
/* SPI_MEM_USR_MISO:R/W；位位置：[28]；默认值：1’b0；*/
/*description:设置此位以启用读取数据操作的DIN阶段。。*/
#define SPI_MEM_USR_MISO    (BIT(28))
#define SPI_MEM_USR_MISO_M  (BIT(28))
#define SPI_MEM_USR_MISO_V  0x1
#define SPI_MEM_USR_MISO_S  28
/* SPI_MEM_USR_MOSI:R/W；位位置：[27]；默认值：1’b0；*/
/*description:设置此位以启用写入数据操作的DOUT阶段。。*/
#define SPI_MEM_USR_MOSI    (BIT(27))
#define SPI_MEM_USR_MOSI_M  (BIT(27))
#define SPI_MEM_USR_MOSI_V  0x1
#define SPI_MEM_USR_MOSI_S  27
/* SPI_MEM_USR_dumm_IDLE:R/W；位位置：[26]；默认值：1’b0；*/
/*描述：启用位时，在DUMMY阶段禁用SPI_CLK（无时钟边沿）。。*/
#define SPI_MEM_USR_DUMMY_IDLE    (BIT(26))
#define SPI_MEM_USR_DUMMY_IDLE_M  (BIT(26))
#define SPI_MEM_USR_DUMMY_IDLE_V  0x1
#define SPI_MEM_USR_DUMMY_IDLE_S  26
/* SPI_MEM_USR_MOSI-HIGHPART:R/W；位位置：[25]；默认值：1’b0；*/
/*描述：DOUT阶段仅访问缓冲区SPI_MEM_W8_REG~SPI_MEM-W15_REG的高部分。1： 启用0:禁用。*/
#define SPI_MEM_USR_MOSI_HIGHPART    (BIT(25))
#define SPI_MEM_USR_MOSI_HIGHPART_M  (BIT(25))
#define SPI_MEM_USR_MOSI_HIGHPART_V  0x1
#define SPI_MEM_USR_MOSI_HIGHPART_S  25
/* SPI_MEM_USR_MISO_HIGHPART:R/W；位位置：[24]；默认值：1’b0；*/
/*描述：DIN阶段仅访问缓冲区SPI_MEM_W8_REG~SPI_MEM-W15_REG的高部分。1： 启用0:禁用。*/
#define SPI_MEM_USR_MISO_HIGHPART    (BIT(24))
#define SPI_MEM_USR_MISO_HIGHPART_M  (BIT(24))
#define SPI_MEM_USR_MISO_HIGHPART_V  0x1
#define SPI_MEM_USR_MISO_HIGHPART_S  24
/* SPI_MEM_FWRITE_QIO:R/W；位位置：[15]；默认值：1’b0；*/
/*description:设置此位以启用SPI1写入操作中ADDR和DOUT阶段的4位模式（4-bm）。。*/
#define SPI_MEM_FWRITE_QIO    (BIT(15))
#define SPI_MEM_FWRITE_QIO_M  (BIT(15))
#define SPI_MEM_FWRITE_QIO_V  0x1
#define SPI_MEM_FWRITE_QIO_S  15
/* SPI_MEM_FWRITE_DIO:R/W；位位置：[14]；默认值：1’b0；*/
/*description:设置此位以启用SPI1写入操作中ADDR和DOUT阶段的2-bm。。*/
#define SPI_MEM_FWRITE_DIO    (BIT(14))
#define SPI_MEM_FWRITE_DIO_M  (BIT(14))
#define SPI_MEM_FWRITE_DIO_V  0x1
#define SPI_MEM_FWRITE_DIO_S  14
/* SPI_MEM_FWRITE_QUAD:R/W；位位置：[13]；默认值：1’b0；*/
/*description:设置此位以启用SPI1写入操作中DOUT阶段的4-bm。。*/
#define SPI_MEM_FWRITE_QUAD    (BIT(13))
#define SPI_MEM_FWRITE_QUAD_M  (BIT(13))
#define SPI_MEM_FWRITE_QUAD_V  0x1
#define SPI_MEM_FWRITE_QUAD_S  13
/* SPI_MEM_frite_DUAL:R/W；位位置：[12]；默认值：1’b0；*/
/*description:设置此位以启用SPI1写入操作中DOUT阶段的2-bm。。*/
#define SPI_MEM_FWRITE_DUAL    (BIT(12))
#define SPI_MEM_FWRITE_DUAL_M  (BIT(12))
#define SPI_MEM_FWRITE_DUAL_V  0x1
#define SPI_MEM_FWRITE_DUAL_S  12
/* SPI_MEM_CK_OUT_EDGE:R/W；位位置：[9]；默认值：1’b0；*/
/*描述：此位与SPI_MEM_CK_IDLE_EDGE位结合，用于更改SPI_CLK的时钟模式0~3。*/
#define SPI_MEM_CK_OUT_EDGE    (BIT(9))
#define SPI_MEM_CK_OUT_EDGE_M  (BIT(9))
#define SPI_MEM_CK_OUT_EDGE_V  0x1
#define SPI_MEM_CK_OUT_EDGE_S  9
/* SPI_MEM_CS_SETUP:R/W；位位置：[7]；默认值：1’b0；*/
/*description:当MSPI处于PREP状态时，设置此位以保持SPI_CS为低。。*/
#define SPI_MEM_CS_SETUP    (BIT(7))
#define SPI_MEM_CS_SETUP_M  (BIT(7))
#define SPI_MEM_CS_SETUP_V  0x1
#define SPI_MEM_CS_SETUP_S  7
/* SPI_MEM_CS_HOLD:R/W；位位置：[6]；默认值：1’b0；*/
/*description:当MSPI处于DONE状态时，设置此位以保持SPI_CS为低。。*/
#define SPI_MEM_CS_HOLD    (BIT(6))
#define SPI_MEM_CS_HOLD_M  (BIT(6))
#define SPI_MEM_CS_HOLD_V  0x1
#define SPI_MEM_CS_HOLD_S  6

#define SPI_MEM_USER1_REG(i)          (REG_SPI_MEM_BASE(i) + 0x1C)
/* SPI_MEM_USR_ADDR_标题：R/W；位位置：[31:26]；默认值：6'd23；*/
/*description:ADDR相位的位长度。寄存器值应为（bit_num-1）。。*/
#define SPI_MEM_USR_ADDR_BITLEN    0x0000003F
#define SPI_MEM_USR_ADDR_BITLEN_M  ((SPI_MEM_USR_ADDR_BITLEN_V)<<(SPI_MEM_USR_ADDR_BITLEN_S))
#define SPI_MEM_USR_ADDR_BITLEN_V  0x3F
#define SPI_MEM_USR_ADDR_BITLEN_S  26
/* SPI_MEM_USR_DUMMY_CYCLELEN:R/W；比特位置：[5:0]；默认值：6'd7；*/
/*描述：DUMMY相位的SPI_CLK周期长度减1。。*/
#define SPI_MEM_USR_DUMMY_CYCLELEN    0x0000003F
#define SPI_MEM_USR_DUMMY_CYCLELEN_M  ((SPI_MEM_USR_DUMMY_CYCLELEN_V)<<(SPI_MEM_USR_DUMMY_CYCLELEN_S))
#define SPI_MEM_USR_DUMMY_CYCLELEN_V  0x3F
#define SPI_MEM_USR_DUMMY_CYCLELEN_S  0

#define SPI_MEM_USER2_REG(i)          (REG_SPI_MEM_BASE(i) + 0x20)
/* SPI_MEM_USR_COMMAND_BITLEN:R/W；位位置：[31:28]；默认值：4'd7；*/
/*description:CMD阶段的位长度。寄存器值应为（bit_num-1）。*/
#define SPI_MEM_USR_COMMAND_BITLEN    0x0000000F
#define SPI_MEM_USR_COMMAND_BITLEN_M  ((SPI_MEM_USR_COMMAND_BITLEN_V)<<(SPI_MEM_USR_COMMAND_BITLEN_S))
#define SPI_MEM_USR_COMMAND_BITLEN_V  0xF
#define SPI_MEM_USR_COMMAND_BITLEN_S  28
/* SPI_MEM_USR_COMMAND_VALUE:R/W；比特位置：[15:0]；默认值：16'b0；*/
/*description:用户定义（USR）命令的值。。*/
#define SPI_MEM_USR_COMMAND_VALUE    0x0000FFFF
#define SPI_MEM_USR_COMMAND_VALUE_M  ((SPI_MEM_USR_COMMAND_VALUE_V)<<(SPI_MEM_USR_COMMAND_VALUE_S))
#define SPI_MEM_USR_COMMAND_VALUE_V  0xFFFF
#define SPI_MEM_USR_COMMAND_VALUE_S  0

#define SPI_MEM_MOSI_DLEN_REG(i)          (REG_SPI_MEM_BASE(i) + 0x24)
/* SPI_MEM_USR_MOSI_ditlen:R/W；位位置：[9:0]；默认值：10'0；*/
/*description:DOUT相位的长度（以位为单位）。寄存器值应为（bit_num-1）。。*/
#define SPI_MEM_USR_MOSI_DBITLEN    0x000003FF
#define SPI_MEM_USR_MOSI_DBITLEN_M  ((SPI_MEM_USR_MOSI_DBITLEN_V)<<(SPI_MEM_USR_MOSI_DBITLEN_S))
#define SPI_MEM_USR_MOSI_DBITLEN_V  0x3FF
#define SPI_MEM_USR_MOSI_DBITLEN_S  0

#define SPI_MEM_MISO_DLEN_REG(i)          (REG_SPI_MEM_BASE(i) + 0x28)
/* SPI_MEM_USR_MISO_DBITLEN:R/W；位位置：[9:0]；默认值：10'0；*/
/*description:DIN相位的位长度。寄存器值应为（bit_num-1）。。*/
#define SPI_MEM_USR_MISO_DBITLEN    0x000003FF
#define SPI_MEM_USR_MISO_DBITLEN_M  ((SPI_MEM_USR_MISO_DBITLEN_V)<<(SPI_MEM_USR_MISO_DBITLEN_S))
#define SPI_MEM_USR_MISO_DBITLEN_V  0x3FF
#define SPI_MEM_USR_MISO_DBITLEN_S  0

#define SPI_MEM_RD_STATUS_REG(i)          (REG_SPI_MEM_BASE(i) + 0x2C)
/* SPI_MEM_WB_MODE:R/W；比特位置：[23:16]；默认值：8'00；*/
/*description:快速读取模式中的模式位与SPI_MEM_FASTRD_Mode位组合。。*/
#define SPI_MEM_WB_MODE    0x000000FF
#define SPI_MEM_WB_MODE_M  ((SPI_MEM_WB_MODE_V)<<(SPI_MEM_WB_MODE_S))
#define SPI_MEM_WB_MODE_V  0xFF
#define SPI_MEM_WB_MODE_S  16
/* SPI_MEM_STATUS:R/W/SS；比特位置：[15:0]；默认值：16'b0；*/
/*描述：设置SPI_MEM_FLASH_RDSR位和SPI_MEM-FLASH_RES位时存储该值。。*/
#define SPI_MEM_STATUS    0x0000FFFF
#define SPI_MEM_STATUS_M  ((SPI_MEM_STATUS_V)<<(SPI_MEM_STATUS_S))
#define SPI_MEM_STATUS_V  0xFFFF
#define SPI_MEM_STATUS_S  0

#define SPI_MEM_EXT_ADDR_REG(i)          (REG_SPI_MEM_BASE(i) + 0x30)
/* SPI_MEM_EXT_ADDR:R/W；位位置：[31:0]；默认值：32'b0；*/
/*描述：在64位地址模式中，寄存器是较高的32位。。*/
#define SPI_MEM_EXT_ADDR    0xFFFFFFFF
#define SPI_MEM_EXT_ADDR_M  ((SPI_MEM_EXT_ADDR_V)<<(SPI_MEM_EXT_ADDR_S))
#define SPI_MEM_EXT_ADDR_V  0xFFFFFFFF
#define SPI_MEM_EXT_ADDR_S  0

#define SPI_MEM_MISC_REG(i)          (REG_SPI_MEM_BASE(i) + 0x34)
/* SPI_MEM_AUTO_PER:R/W；位位置：[11]；默认值：1’b0；*/
/*description:设置此位以启用自动PER功能。如果发送PES命令，硬件将发送PER命令。。*/
#define SPI_MEM_AUTO_PER    (BIT(11))
#define SPI_MEM_AUTO_PER_M  (BIT(11))
#define SPI_MEM_AUTO_PER_V  0x1
#define SPI_MEM_AUTO_PER_S  11
/* SPI_MEM_CS_KEEP_ACTIVE:R/W；位位置：[10]；默认值：1’b0；*/
/*description:设置位时，SPI_CS行保持低位。。*/
#define SPI_MEM_CS_KEEP_ACTIVE    (BIT(10))
#define SPI_MEM_CS_KEEP_ACTIVE_M  (BIT(10))
#define SPI_MEM_CS_KEEP_ACTIVE_V  0x1
#define SPI_MEM_CS_KEEP_ACTIVE_S  10
/* SPI_MEM_CK_inidle_EDGE：R/W；位位置：[9]；默认值：1’b0；*/
/*描述：1:MSPI空闲时SPI_CLK线为高。0:MSPI空闲时SPI_CLK线低。。*/
#define SPI_MEM_CK_IDLE_EDGE    (BIT(9))
#define SPI_MEM_CK_IDLE_EDGE_M  (BIT(9))
#define SPI_MEM_CK_IDLE_EDGE_V  0x1
#define SPI_MEM_CK_IDLE_EDGE_S  9
/* SPI_MEM_sub_PIN:R/W；位位置：[8]；默认值：1’b0；*/
/*描述：Ext_RAM连接到SPI SUBPIN总线。。*/
#define SPI_MEM_SSUB_PIN    (BIT(8))
#define SPI_MEM_SSUB_PIN_M  (BIT(8))
#define SPI_MEM_SSUB_PIN_V  0x1
#define SPI_MEM_SSUB_PIN_S  8
/* SPI_MEM_FSUB_PIN:R/W；位位置：[7]；默认值：1’b0；*/
/*description:Flash连接到SPI SUBPIN总线。。*/
#define SPI_MEM_FSUB_PIN    (BIT(7))
#define SPI_MEM_FSUB_PIN_M  (BIT(7))
#define SPI_MEM_FSUB_PIN_V  0x1
#define SPI_MEM_FSUB_PIN_S  7
/* SPI_MEM_CS1_DIS:R/W；位位置：[1]；默认值：1’b1；*/
/*description:设置此位以提升高SPI_CS1引脚，这意味着当SPI1传输开始时，连接到SPI_CS1的SPI设备（Ext_RAM）处于低电平。。*/
#define SPI_MEM_CS1_DIS    (BIT(1))
#define SPI_MEM_CS1_DIS_M  (BIT(1))
#define SPI_MEM_CS1_DIS_V  0x1
#define SPI_MEM_CS1_DIS_S  1
/* SPI_MEM_CS0_DIS:R/W；位位置：[0]；默认值：1’b0；*/
/*description:设置此位以提升高SPI_CS引脚，这意味着当SPI1传输开始时，连接到SPI_CS的SPI设备（闪存）处于低电平。。*/
#define SPI_MEM_CS0_DIS    (BIT(0))
#define SPI_MEM_CS0_DIS_M  (BIT(0))
#define SPI_MEM_CS0_DIS_V  0x1
#define SPI_MEM_CS0_DIS_S  0

#define SPI_MEM_TX_CRC_REG(i)          (REG_SPI_MEM_BASE(i) + 0x38)
/* SPI_MEM_TX_CRC_DATA:RO；位位置：[31:0]；默认值：32'ffffffff；*/
/*description:对于SPI1，crc32。。*/
#define SPI_MEM_TX_CRC_DATA    0xFFFFFFFF
#define SPI_MEM_TX_CRC_DATA_M  ((SPI_MEM_TX_CRC_DATA_V)<<(SPI_MEM_TX_CRC_DATA_S))
#define SPI_MEM_TX_CRC_DATA_V  0xFFFFFFFF
#define SPI_MEM_TX_CRC_DATA_S  0

#define SPI_MEM_CACHE_FCTRL_REG(i)          (REG_SPI_MEM_BASE(i) + 0x3C)
/* SPI_MEM_FADDR_QUAD:R/W；位位置：[8]；默认值：1’b0；*/
/*描述：当SPI1访问闪存或Ext_RAM时，将此位设置为在ADDR阶段启用4-bm。。*/
#define SPI_MEM_FADDR_QUAD    (BIT(8))
#define SPI_MEM_FADDR_QUAD_M  (BIT(8))
#define SPI_MEM_FADDR_QUAD_V  0x1
#define SPI_MEM_FADDR_QUAD_S  8
/* SPI_MEM_FDOUT_QUAD:R/W；位位置：[7]；默认值：1’b0；*/
/*描述：当SPI1访问闪存或Ext_RAM时，将此位设置为在DOUT阶段启用4-bm。。*/
#define SPI_MEM_FDOUT_QUAD    (BIT(7))
#define SPI_MEM_FDOUT_QUAD_M  (BIT(7))
#define SPI_MEM_FDOUT_QUAD_V  0x1
#define SPI_MEM_FDOUT_QUAD_S  7
/* SPI_MEM_FDIN_QUAD:R/W；位位置：[6]；默认值：1’b0；*/
/*description: 当SPI1访问闪存或Ext_RAM时，将此位设置为在DIN阶段启用4-bm
..*/
#define SPI_MEM_FDIN_QUAD    (BIT(6))
#define SPI_MEM_FDIN_QUAD_M  (BIT(6))
#define SPI_MEM_FDIN_QUAD_V  0x1
#define SPI_MEM_FDIN_QUAD_S  6
/* SPI_MEM_FADDR_DUAL:R/W；位位置：[5]；默认值：1’b0；*/
/*描述：当SPI1访问闪存或Ext_RAM时，将此位设置为在ADDR阶段启用2-bm。。*/
#define SPI_MEM_FADDR_DUAL    (BIT(5))
#define SPI_MEM_FADDR_DUAL_M  (BIT(5))
#define SPI_MEM_FADDR_DUAL_V  0x1
#define SPI_MEM_FADDR_DUAL_S  5
/* SPI_MEM_FDOUT_DUAL:R/W；位位置：[4]；默认值：1’b0；*/
/*描述：当SPI1访问闪存或Ext_RAM时，将此位设置为在DOUT阶段启用2-bm。。*/
#define SPI_MEM_FDOUT_DUAL    (BIT(4))
#define SPI_MEM_FDOUT_DUAL_M  (BIT(4))
#define SPI_MEM_FDOUT_DUAL_V  0x1
#define SPI_MEM_FDOUT_DUAL_S  4
/* SPI_MEM_FDIN_DUAL:R/W；位位置：[3]；默认值：1’b0；*/
/*description: 当SPI1访问闪存或Ext_RAM时，将此位设置为在DIN阶段启用2-bm
..*/
#define SPI_MEM_FDIN_DUAL    (BIT(3))
#define SPI_MEM_FDIN_DUAL_M  (BIT(3))
#define SPI_MEM_FDIN_DUAL_V  0x1
#define SPI_MEM_FDIN_DUAL_S  3
/* SPI_MEM_CACHE_FLASH_USR_CMD:R/W；位位置：[2]；默认值：1’b0；*/
/*description:1:SPI0 reads flash命令值为SPI_MEM_USR_command_value。0：硬件读取命令值，由SPI_MEM_FREAD_QIO、SPI_MEM-FREAD_DIO、SPI_MEM_FREAD_FQUAD、SPI_MEM _FREAD_DUAL和SPI_MEM.FASTRD_MODE位控制。。*/
#define SPI_MEM_CACHE_FLASH_USR_CMD    (BIT(2))
#define SPI_MEM_CACHE_FLASH_USR_CMD_M  (BIT(2))
#define SPI_MEM_CACHE_FLASH_USR_CMD_V  0x1
#define SPI_MEM_CACHE_FLASH_USR_CMD_S  2
/* SPI_MEM_CACHE_USR_CMD_4BYTE:R/W；位位置：[1]；默认值：1’b0；*/
/*description:设置此位以启用32位地址的SPI1传输。SPI_MEM_USR_ADDR_BITLEN的值应为31。。*/
#define SPI_MEM_CACHE_USR_CMD_4BYTE    (BIT(1))
#define SPI_MEM_CACHE_USR_CMD_4BYTE_M  (BIT(1))
#define SPI_MEM_CACHE_USR_CMD_4BYTE_V  0x1
#define SPI_MEM_CACHE_USR_CMD_4BYTE_S  1
/* SPI_MEM_CACHE_REQ_EN:R/W；位位置：[0]；默认值：1’b0；*/
/*description:设置此位以启用Cache的访问和SPI0的传输。。*/
#define SPI_MEM_CACHE_REQ_EN    (BIT(0))
#define SPI_MEM_CACHE_REQ_EN_M  (BIT(0))
#define SPI_MEM_CACHE_REQ_EN_V  0x1
#define SPI_MEM_CACHE_REQ_EN_S  0

#define SPI_MEM_CACHE_SCTRL_REG(i)          (REG_SPI_MEM_BASE(i) + 0x40)
/* SPI_MEM_SRAM_WDUMMY_CYCLELEN:R/W；位位置：[27:22]；默认值：6'b1；*/
/*描述：当SPI0访问Ext_RAM时，写入数据传输中的SPI_CLK周期减去DUMMY阶段的1。。*/
#define SPI_MEM_SRAM_WDUMMY_CYCLELEN    0x0000003F
#define SPI_MEM_SRAM_WDUMMY_CYCLELEN_M  ((SPI_MEM_SRAM_WDUMMY_CYCLELEN_V)<<(SPI_MEM_SRAM_WDUMMY_CYCLELEN_S))
#define SPI_MEM_SRAM_WDUMMY_CYCLELEN_V  0x3F
#define SPI_MEM_SRAM_WDUMMY_CYCLELEN_S  22
/* SPI_MEM_SRAM_OCT:R/W；位位置：[21]；默认值：1’b0；*/
/*description:设置位以在所有SPI0 Ext_RAM传输中启用OPI模式。。*/
#define SPI_MEM_SRAM_OCT    (BIT(21))
#define SPI_MEM_SRAM_OCT_M  (BIT(21))
#define SPI_MEM_SRAM_OCT_V  0x1
#define SPI_MEM_SRAM_OCT_S  21
/* SPI_MEM_CACHE_SRAM_USR_WCMD:R/W；位位置：[20]；默认值：1’b1；*/
/*description:1:SPI0 write Ext_RAM的命令值为SPI_MEM_CACHE_SRAM_USR_RD_CMD_value。0：值为0x3。。*/
#define SPI_MEM_CACHE_SRAM_USR_WCMD    (BIT(20))
#define SPI_MEM_CACHE_SRAM_USR_WCMD_M  (BIT(20))
#define SPI_MEM_CACHE_SRAM_USR_WCMD_V  0x1
#define SPI_MEM_CACHE_SRAM_USR_WCMD_S  20
/* SPI_MEM_SRAM_ADDR_标题：R/W；比特位置：[19:14]；默认值：6'd23；*/
/*description:当SPI0访问Ext_RAM时，它是ADDR相位的位长度。寄存器值应为（bit_num-1）。。*/
#define SPI_MEM_SRAM_ADDR_BITLEN    0x0000003F
#define SPI_MEM_SRAM_ADDR_BITLEN_M  ((SPI_MEM_SRAM_ADDR_BITLEN_V)<<(SPI_MEM_SRAM_ADDR_BITLEN_S))
#define SPI_MEM_SRAM_ADDR_BITLEN_V  0x3F
#define SPI_MEM_SRAM_ADDR_BITLEN_S  14
/* SPI_MEM_SRAM_RDUMMY_CYCLELEN:R/W；位位置：[11:6]；默认值：6'b1；*/
/*描述：当SPI0访问Ext_RAM时，读取数据传输中的SPI_CLK周期减去DUMMY阶段的1。。*/
#define SPI_MEM_SRAM_RDUMMY_CYCLELEN    0x0000003F
#define SPI_MEM_SRAM_RDUMMY_CYCLELEN_M  ((SPI_MEM_SRAM_RDUMMY_CYCLELEN_V)<<(SPI_MEM_SRAM_RDUMMY_CYCLELEN_S))
#define SPI_MEM_SRAM_RDUMMY_CYCLELEN_V  0x3F
#define SPI_MEM_SRAM_RDUMMY_CYCLELEN_S  6
/* SPI_MEM_CACHE_SRAM_USR_RCMD:R/W；位位置：[5]；默认值：1’b1；*/
/*description:1:SPI0读取Ext_RAM的命令值为SPI_MEM_CACHE_SRAM_USR_WR_CMD_value。0：值为0x2。。*/
#define SPI_MEM_CACHE_SRAM_USR_RCMD    (BIT(5))
#define SPI_MEM_CACHE_SRAM_USR_RCMD_M  (BIT(5))
#define SPI_MEM_CACHE_SRAM_USR_RCMD_V  0x1
#define SPI_MEM_CACHE_SRAM_USR_RCMD_S  5
/* SPI_MEM_USR_RD_sramdumm:R/W；位位置：[4]；默认值：1’b1；*/
/*描述：当SPI0访问Ext_RAM时，设置此位以启用读取操作中的DUMMY阶段。。*/
#define SPI_MEM_USR_RD_SRAM_DUMMY    (BIT(4))
#define SPI_MEM_USR_RD_SRAM_DUMMY_M  (BIT(4))
#define SPI_MEM_USR_RD_SRAM_DUMMY_V  0x1
#define SPI_MEM_USR_RD_SRAM_DUMMY_S  4
/* SPI_MEM_USR_WR_SRAM虚拟：R/W；位位置：[3]；默认值：1’b0；*/
/*描述：当SPI0访问Ext_RAM时，设置此位以启用写入操作中的DUMMY阶段。。*/
#define SPI_MEM_USR_WR_SRAM_DUMMY    (BIT(3))
#define SPI_MEM_USR_WR_SRAM_DUMMY_M  (BIT(3))
#define SPI_MEM_USR_WR_SRAM_DUMMY_V  0x1
#define SPI_MEM_USR_WR_SRAM_DUMMY_S  3
/* SPI_MEM_USR_SRAM_QIO:R/W；位位置：[2]；默认值：1’b0；*/
/*description:设置位以在所有SPI0 Ext_RAM传输中启用QPI模式。。*/
#define SPI_MEM_USR_SRAM_QIO    (BIT(2))
#define SPI_MEM_USR_SRAM_QIO_M  (BIT(2))
#define SPI_MEM_USR_SRAM_QIO_V  0x1
#define SPI_MEM_USR_SRAM_QIO_S  2
/* SPI_MEM_USR_SRAM_DIO:R/W；位位置：[1]；默认值：1’b0；*/
/*description:将该位设置为在SPI0 Ext_RAM传输的所有阶段启用2-bm。。*/
#define SPI_MEM_USR_SRAM_DIO    (BIT(1))
#define SPI_MEM_USR_SRAM_DIO_M  (BIT(1))
#define SPI_MEM_USR_SRAM_DIO_V  0x1
#define SPI_MEM_USR_SRAM_DIO_S  1
/* SPI_MEM_CACHE_USR_SCMD_4BYTE:R/W；位位置：[0]；默认值：1’b0；*/
/*description:设置此位以启用SPI0读取32位地址的Ext_RAM。SPI_MEM_SRAM_ADDR_BITLEN的值应为31。。*/
#define SPI_MEM_CACHE_USR_SCMD_4BYTE    (BIT(0))
#define SPI_MEM_CACHE_USR_SCMD_4BYTE_M  (BIT(0))
#define SPI_MEM_CACHE_USR_SCMD_4BYTE_V  0x1
#define SPI_MEM_CACHE_USR_SCMD_4BYTE_S  0

#define SPI_MEM_SRAM_CMD_REG(i)          (REG_SPI_MEM_BASE(i) + 0x44)
/* SPI_MEM_SDUMMY_OUT:R/W；位位置：[22]；默认值：1’b0；*/
/*描述：当SPI0访问Ext_RAM时，在DUMMY阶段，SPI总线的信号电平由SPI0控制器输出。。*/
#define SPI_MEM_SDUMMY_OUT    (BIT(22))
#define SPI_MEM_SDUMMY_OUT_M  (BIT(22))
#define SPI_MEM_SDUMMY_OUT_V  0x1
#define SPI_MEM_SDUMMY_OUT_S  22
/* SPI_MEM_SCMD_OCT:R/W；位位置：[21]；默认值：1’b0；*/
/*描述：当SPI0访问Ext_RAM时，将此位设置为在CMD阶段启用8-bm。。*/
#define SPI_MEM_SCMD_OCT    (BIT(21))
#define SPI_MEM_SCMD_OCT_M  (BIT(21))
#define SPI_MEM_SCMD_OCT_V  0x1
#define SPI_MEM_SCMD_OCT_S  21
/* SPI_MEM_SADDR_OCT:R/W；位位置：[20]；默认值：1’b0；*/
/*描述：当SPI0访问Ext_RAM时，将此位设置为在ADDR阶段启用8-bm。。*/
#define SPI_MEM_SADDR_OCT    (BIT(20))
#define SPI_MEM_SADDR_OCT_M  (BIT(20))
#define SPI_MEM_SADDR_OCT_V  0x1
#define SPI_MEM_SADDR_OCT_S  20
/* SPI_MEM_SDOUT_OCT:R/W；位位置：[19]；默认值：1’b0；*/
/*描述：当SPI0访问Ext_RAM时，将此位设置为在DOUT阶段启用8-bm。。*/
#define SPI_MEM_SDOUT_OCT    (BIT(19))
#define SPI_MEM_SDOUT_OCT_M  (BIT(19))
#define SPI_MEM_SDOUT_OCT_V  0x1
#define SPI_MEM_SDOUT_OCT_S  19
/* SPI_MEM_SDIN_OCT:R/W；位位置：[18]；默认值：1’b0；*/
/*描述：当SPI0访问Ext_RAM时，将此位设置为在DIN阶段启用8-bm。。*/
#define SPI_MEM_SDIN_OCT    (BIT(18))
#define SPI_MEM_SDIN_OCT_M  (BIT(18))
#define SPI_MEM_SDIN_OCT_V  0x1
#define SPI_MEM_SDIN_OCT_S  18
/* SPI_MEM_SCMD_QUAD:R/W；位位置：[17]；默认值：1’b0；*/
/*描述：当SPI0访问Ext_RAM时，将此位设置为在CMD阶段启用4-bm。。*/
#define SPI_MEM_SCMD_QUAD    (BIT(17))
#define SPI_MEM_SCMD_QUAD_M  (BIT(17))
#define SPI_MEM_SCMD_QUAD_V  0x1
#define SPI_MEM_SCMD_QUAD_S  17
/* SPI_MEM_SADDR_QUAD:R/W；位位置：[16]；默认值：1’b0；*/
/*描述：当SPI0访问Ext_RAM时，将此位设置为在ADDR阶段启用4-bm。。*/
#define SPI_MEM_SADDR_QUAD    (BIT(16))
#define SPI_MEM_SADDR_QUAD_M  (BIT(16))
#define SPI_MEM_SADDR_QUAD_V  0x1
#define SPI_MEM_SADDR_QUAD_S  16
/* SPI_MEM_SDOUT_QUAD:R/W；位位置：[15]；默认值：1’b0；*/
/*描述：当SPI0访问Ext_RAM时，将此位设置为在DOUT阶段启用4-bm。。*/
#define SPI_MEM_SDOUT_QUAD    (BIT(15))
#define SPI_MEM_SDOUT_QUAD_M  (BIT(15))
#define SPI_MEM_SDOUT_QUAD_V  0x1
#define SPI_MEM_SDOUT_QUAD_S  15
/* SPI_MEM_SDIN_QUAD:R/W；位位置：[14]；默认值：1’b0；*/
/*描述：当SPI0访问Ext_RAM时，将此位设置为在DIN阶段启用4-bm。。*/
#define SPI_MEM_SDIN_QUAD    (BIT(14))
#define SPI_MEM_SDIN_QUAD_M  (BIT(14))
#define SPI_MEM_SDIN_QUAD_V  0x1
#define SPI_MEM_SDIN_QUAD_S  14
/* SPI_MEM_SCMD_DUAL:R/W；位位置：[13]；默认值：1’b0；*/
/*描述：当SPI0访问Ext_RAM时，将此位设置为在CMD阶段启用2-bm。。*/
#define SPI_MEM_SCMD_DUAL    (BIT(13))
#define SPI_MEM_SCMD_DUAL_M  (BIT(13))
#define SPI_MEM_SCMD_DUAL_V  0x1
#define SPI_MEM_SCMD_DUAL_S  13
/* SPI_MEM_SADDR_DUAL:R/W；位位置：[12]；默认值：1’b0；*/
/*描述：当SPI0访问Ext_RAM时，将此位设置为在ADDR阶段启用2-bm。。*/
#define SPI_MEM_SADDR_DUAL    (BIT(12))
#define SPI_MEM_SADDR_DUAL_M  (BIT(12))
#define SPI_MEM_SADDR_DUAL_V  0x1
#define SPI_MEM_SADDR_DUAL_S  12
/* SPI_MEM_SDOUT_DUAL:R/W；位位置：[11]；默认值：1’b0；*/
/*描述：当SPI0访问Ext_RAM时，将此位设置为在DOUT阶段启用2-bm。。*/
#define SPI_MEM_SDOUT_DUAL    (BIT(11))
#define SPI_MEM_SDOUT_DUAL_M  (BIT(11))
#define SPI_MEM_SDOUT_DUAL_V  0x1
#define SPI_MEM_SDOUT_DUAL_S  11
/* SPI_MEM_SDIN_DUAL:R/W；位位置：[10]；默认值：1’b0；*/
/*描述：当SPI0访问Ext_RAM时，将此位设置为在DIN阶段启用2-bm。。*/
#define SPI_MEM_SDIN_DUAL    (BIT(10))
#define SPI_MEM_SDIN_DUAL_M  (BIT(10))
#define SPI_MEM_SDIN_DUAL_V  0x1
#define SPI_MEM_SDIN_DUAL_S  10
/* SPI_MEM_SWB_MODE：R/W；比特位置：[9:2]；默认值：8'b0；*/
/*description:SPI0访问Ext_RAM时的模式位。。*/
#define SPI_MEM_SWB_MODE    0x000000FF
#define SPI_MEM_SWB_MODE_M  ((SPI_MEM_SWB_MODE_V)<<(SPI_MEM_SWB_MODE_S))
#define SPI_MEM_SWB_MODE_V  0xFF
#define SPI_MEM_SWB_MODE_S  2
/* SPI_MEM_SCLK_MODE：R/W；位位置：[1:0]；默认值：2'd0；*/
/*描述：SPI0访问Ext_RAM时的SPI_CLK模式位。0:当CS不活动时，SPI_CLK关闭1:在CS不活动后，SPI_CLK延迟一个周期2:在CS不激活后，SPI-CLK延迟两个周期3:SPI_CLK始终打开。。*/
#define SPI_MEM_SCLK_MODE    0x00000003
#define SPI_MEM_SCLK_MODE_M  ((SPI_MEM_SCLK_MODE_V)<<(SPI_MEM_SCLK_MODE_S))
#define SPI_MEM_SCLK_MODE_V  0x3
#define SPI_MEM_SCLK_MODE_S  0

#define SPI_MEM_SRAM_DRD_CMD_REG(i)          (REG_SPI_MEM_BASE(i) + 0x48)
/* SPI_MEM_CACHE_SRAM_USR_RD_CMD_BITLEN:R/W；位位置：[31:28]；默认值：4'0；*/
/*description:当SPI0读取Ext_RAM时，它是CMD阶段的位长度。寄存器值应为（bit_num-1）。。*/
#define SPI_MEM_CACHE_SRAM_USR_RD_CMD_BITLEN    0x0000000F
#define SPI_MEM_CACHE_SRAM_USR_RD_CMD_BITLEN_M  ((SPI_MEM_CACHE_SRAM_USR_RD_CMD_BITLEN_V)<<(SPI_MEM_CACHE_SRAM_USR_RD_CMD_BITLEN_S))
#define SPI_MEM_CACHE_SRAM_USR_RD_CMD_BITLEN_V  0xF
#define SPI_MEM_CACHE_SRAM_USR_RD_CMD_BITLEN_S  28
/* SPI_MEM_CACHE_SRAM_USR_RD_CMD_VALUE:R/W；比特位置：[15:0]；默认值：16'0；*/
/*description:当SPI0读取Ext_RAM时，它是CMD阶段的命令值。。*/
#define SPI_MEM_CACHE_SRAM_USR_RD_CMD_VALUE    0x0000FFFF
#define SPI_MEM_CACHE_SRAM_USR_RD_CMD_VALUE_M  ((SPI_MEM_CACHE_SRAM_USR_RD_CMD_VALUE_V)<<(SPI_MEM_CACHE_SRAM_USR_RD_CMD_VALUE_S))
#define SPI_MEM_CACHE_SRAM_USR_RD_CMD_VALUE_V  0xFFFF
#define SPI_MEM_CACHE_SRAM_USR_RD_CMD_VALUE_S  0

#define SPI_MEM_SRAM_DWR_CMD_REG(i)          (REG_SPI_MEM_BASE(i) + 0x4C)
/* SPI_MEM_CACHE_SRAM_USR_WR_CMD_BITLEN:R/W；位位置：[31:28]；默认值：4'0；*/
/*description:当SPI0写入Ext_RAM时，它是CMD阶段的位长度。寄存器值应为（bit_num-1）。。*/
#define SPI_MEM_CACHE_SRAM_USR_WR_CMD_BITLEN    0x0000000F
#define SPI_MEM_CACHE_SRAM_USR_WR_CMD_BITLEN_M  ((SPI_MEM_CACHE_SRAM_USR_WR_CMD_BITLEN_V)<<(SPI_MEM_CACHE_SRAM_USR_WR_CMD_BITLEN_S))
#define SPI_MEM_CACHE_SRAM_USR_WR_CMD_BITLEN_V  0xF
#define SPI_MEM_CACHE_SRAM_USR_WR_CMD_BITLEN_S  28
/* SPI_MEM_CACHE_SRAM_USR_WR_CMD_VALUE:R/W；比特位置：[15:0]；默认值：16'0；*/
/*description:当SPI0写入Ext_RAM时，它是CMD阶段的命令值。。*/
#define SPI_MEM_CACHE_SRAM_USR_WR_CMD_VALUE    0x0000FFFF
#define SPI_MEM_CACHE_SRAM_USR_WR_CMD_VALUE_M  ((SPI_MEM_CACHE_SRAM_USR_WR_CMD_VALUE_V)<<(SPI_MEM_CACHE_SRAM_USR_WR_CMD_VALUE_S))
#define SPI_MEM_CACHE_SRAM_USR_WR_CMD_VALUE_V  0xFFFF
#define SPI_MEM_CACHE_SRAM_USR_WR_CMD_VALUE_S  0

#define SPI_MEM_SRAM_CLK_REG(i)          (REG_SPI_MEM_BASE(i) + 0x50)
/* SPI_MEM_SCLK_equi_SYSCLK:R/W；位位置：[31]；默认值：1’b0；*/
/*描述：当SPI0访问Ext_RAM时，将此位设置为1分区模式，f_SPI_CLK=f_MSPI_CORE_CLK。。*/
#define SPI_MEM_SCLK_EQU_SYSCLK    (BIT(31))
#define SPI_MEM_SCLK_EQU_SYSCLK_M  (BIT(31))
#define SPI_MEM_SCLK_EQU_SYSCLK_V  0x1
#define SPI_MEM_SCLK_EQU_SYSCLK_S  31
/* SPI_MEM_SCLKCNT_N:R/W；比特位置：[23:16]；默认值：8'h3；*/
/*description:当SPI0访问Ext_RAM时，f_SPI_CLK=f_MSPI_CORE_CLK/（SPI_MEM_SCLKCNT_N+1）。*/
#define SPI_MEM_SCLKCNT_N    0x000000FF
#define SPI_MEM_SCLKCNT_N_M  ((SPI_MEM_SCLKCNT_N_V)<<(SPI_MEM_SCLKCNT_N_S))
#define SPI_MEM_SCLKCNT_N_V  0xFF
#define SPI_MEM_SCLKCNT_N_S  16
/* SPI_MEM_SCLKCNT_H:R/W；比特位置：[15:8]；默认值：8'h1；*/
/*description:它必须是下限值（（SPI_MEM_SCLKCNT_N+1）/2-1）。。*/
#define SPI_MEM_SCLKCNT_H    0x000000FF
#define SPI_MEM_SCLKCNT_H_M  ((SPI_MEM_SCLKCNT_H_V)<<(SPI_MEM_SCLKCNT_H_S))
#define SPI_MEM_SCLKCNT_H_V  0xFF
#define SPI_MEM_SCLKCNT_H_S  8
/* SPI_MEM_SCLKCNT_L:R/W；位位置：[7:0]；默认值：8'h3；*/
/*description:它必须等于SPI_MEM_SCLKCNT_N的值。*/
#define SPI_MEM_SCLKCNT_L    0x000000FF
#define SPI_MEM_SCLKCNT_L_M  ((SPI_MEM_SCLKCNT_L_V)<<(SPI_MEM_SCLKCNT_L_S))
#define SPI_MEM_SCLKCNT_L_V  0xFF
#define SPI_MEM_SCLKCNT_L_S  0

#define SPI_MEM_FSM_REG(i)          (REG_SPI_MEM_BASE(i) + 0x54)
/* SPI_MEM_ST:RO；位位置：[2:0]；默认值：3'b0；*/
/*description:SPI1状态机的状态。0：空闲状态（idle），1：准备状态（PREP），2：发送命令状态（CMD），3：发送地址状态（ADDR），4：红色数据状态（DIN），5：写入数据状态（DOUT），6：等待状态（DUMMY），7：完成状态（done）。。*/
#define SPI_MEM_ST    0x00000007
#define SPI_MEM_ST_M  ((SPI_MEM_ST_V)<<(SPI_MEM_ST_S))
#define SPI_MEM_ST_V  0x7
#define SPI_MEM_ST_S  0

#define SPI_MEM_W0_REG(i)          (REG_SPI_MEM_BASE(i) + 0x58)
/* SPI_MEM_BUF0:R/W/SS；位位置：[31:0]；默认值：32'b0；*/
/*description:数据缓冲区。*/
#define SPI_MEM_BUF0    0xFFFFFFFF
#define SPI_MEM_BUF0_M  ((SPI_MEM_BUF0_V)<<(SPI_MEM_BUF0_S))
#define SPI_MEM_BUF0_V  0xFFFFFFFF
#define SPI_MEM_BUF0_S  0

#define SPI_MEM_W1_REG(i)          (REG_SPI_MEM_BASE(i) + 0x5C)
/* SPI_MEM_BUF1:R/W/SS；位位置：[31:0]；默认值：32'b0；*/
/*description:数据缓冲区。*/
#define SPI_MEM_BUF1    0xFFFFFFFF
#define SPI_MEM_BUF1_M  ((SPI_MEM_BUF1_V)<<(SPI_MEM_BUF1_S))
#define SPI_MEM_BUF1_V  0xFFFFFFFF
#define SPI_MEM_BUF1_S  0

#define SPI_MEM_W2_REG(i)          (REG_SPI_MEM_BASE(i) + 0x60)
/* SPI_MEM_BUF2:R/W/SS；位位置：[31:0]；默认值：32'b0；*/
/*description:数据缓冲区。*/
#define SPI_MEM_BUF2    0xFFFFFFFF
#define SPI_MEM_BUF2_M  ((SPI_MEM_BUF2_V)<<(SPI_MEM_BUF2_S))
#define SPI_MEM_BUF2_V  0xFFFFFFFF
#define SPI_MEM_BUF2_S  0

#define SPI_MEM_W3_REG(i)          (REG_SPI_MEM_BASE(i) + 0x64)
/* SPI_MEM_BUF3:R/W/SS；位位置：[31:0]；默认值：32'b0；*/
/*description:数据缓冲区。*/
#define SPI_MEM_BUF3    0xFFFFFFFF
#define SPI_MEM_BUF3_M  ((SPI_MEM_BUF3_V)<<(SPI_MEM_BUF3_S))
#define SPI_MEM_BUF3_V  0xFFFFFFFF
#define SPI_MEM_BUF3_S  0

#define SPI_MEM_W4_REG(i)          (REG_SPI_MEM_BASE(i) + 0x68)
/* SPI_MEM_BUF4:R/W/SS；位位置：[31:0]；默认值：32'b0；*/
/*description:数据缓冲区。*/
#define SPI_MEM_BUF4    0xFFFFFFFF
#define SPI_MEM_BUF4_M  ((SPI_MEM_BUF4_V)<<(SPI_MEM_BUF4_S))
#define SPI_MEM_BUF4_V  0xFFFFFFFF
#define SPI_MEM_BUF4_S  0

#define SPI_MEM_W5_REG(i)          (REG_SPI_MEM_BASE(i) + 0x6C)
/* SPI_MEM_BUF5:R/W/SS；位位置：[31:0]；默认值：32'b0；*/
/*description:数据缓冲区。*/
#define SPI_MEM_BUF5    0xFFFFFFFF
#define SPI_MEM_BUF5_M  ((SPI_MEM_BUF5_V)<<(SPI_MEM_BUF5_S))
#define SPI_MEM_BUF5_V  0xFFFFFFFF
#define SPI_MEM_BUF5_S  0

#define SPI_MEM_W6_REG(i)          (REG_SPI_MEM_BASE(i) + 0x70)
/* SPI_MEM_BUF6:R/W/SS；位位置：[31:0]；默认值：32'b0；*/
/*description:数据缓冲区。*/
#define SPI_MEM_BUF6    0xFFFFFFFF
#define SPI_MEM_BUF6_M  ((SPI_MEM_BUF6_V)<<(SPI_MEM_BUF6_S))
#define SPI_MEM_BUF6_V  0xFFFFFFFF
#define SPI_MEM_BUF6_S  0

#define SPI_MEM_W7_REG(i)          (REG_SPI_MEM_BASE(i) + 0x74)
/* SPI_MEM_BUF7:R/W/SS；位位置：[31:0]；默认值：32'b0；*/
/*description:数据缓冲区。*/
#define SPI_MEM_BUF7    0xFFFFFFFF
#define SPI_MEM_BUF7_M  ((SPI_MEM_BUF7_V)<<(SPI_MEM_BUF7_S))
#define SPI_MEM_BUF7_V  0xFFFFFFFF
#define SPI_MEM_BUF7_S  0

#define SPI_MEM_W8_REG(i)          (REG_SPI_MEM_BASE(i) + 0x78)
/* SPI_MEM_BUF8:R/W/SS；位位置：[31:0]；默认值：32'b0；*/
/*description:数据缓冲区。*/
#define SPI_MEM_BUF8    0xFFFFFFFF
#define SPI_MEM_BUF8_M  ((SPI_MEM_BUF8_V)<<(SPI_MEM_BUF8_S))
#define SPI_MEM_BUF8_V  0xFFFFFFFF
#define SPI_MEM_BUF8_S  0

#define SPI_MEM_W9_REG(i)          (REG_SPI_MEM_BASE(i) + 0x7C)
/* SPI_MEM_BUF9:R/W/SS；位位置：[31:0]；默认值：32'b0；*/
/*description:数据缓冲区。*/
#define SPI_MEM_BUF9    0xFFFFFFFF
#define SPI_MEM_BUF9_M  ((SPI_MEM_BUF9_V)<<(SPI_MEM_BUF9_S))
#define SPI_MEM_BUF9_V  0xFFFFFFFF
#define SPI_MEM_BUF9_S  0

#define SPI_MEM_W10_REG(i)          (REG_SPI_MEM_BASE(i) + 0x80)
/* SPI_MEM_BUF10:R/W/SS；位位置：[31:0]；默认值：32'b0；*/
/*description:数据缓冲区。*/
#define SPI_MEM_BUF10    0xFFFFFFFF
#define SPI_MEM_BUF10_M  ((SPI_MEM_BUF10_V)<<(SPI_MEM_BUF10_S))
#define SPI_MEM_BUF10_V  0xFFFFFFFF
#define SPI_MEM_BUF10_S  0

#define SPI_MEM_W11_REG(i)          (REG_SPI_MEM_BASE(i) + 0x84)
/* SPI_MEM_BUF11:R/W/SS；位位置：[31:0]；默认值：32'b0；*/
/*description:数据缓冲区。*/
#define SPI_MEM_BUF11    0xFFFFFFFF
#define SPI_MEM_BUF11_M  ((SPI_MEM_BUF11_V)<<(SPI_MEM_BUF11_S))
#define SPI_MEM_BUF11_V  0xFFFFFFFF
#define SPI_MEM_BUF11_S  0

#define SPI_MEM_W12_REG(i)          (REG_SPI_MEM_BASE(i) + 0x88)
/* SPI_MEM_BUF12:R/W/SS；位位置：[31:0]；默认值：32'b0；*/
/*description:数据缓冲区。*/
#define SPI_MEM_BUF12    0xFFFFFFFF
#define SPI_MEM_BUF12_M  ((SPI_MEM_BUF12_V)<<(SPI_MEM_BUF12_S))
#define SPI_MEM_BUF12_V  0xFFFFFFFF
#define SPI_MEM_BUF12_S  0

#define SPI_MEM_W13_REG(i)          (REG_SPI_MEM_BASE(i) + 0x8C)
/* SPI_MEM_BUF13:R/W/SS；位位置：[31:0]；默认值：32'b0；*/
/*description:数据缓冲区。*/
#define SPI_MEM_BUF13    0xFFFFFFFF
#define SPI_MEM_BUF13_M  ((SPI_MEM_BUF13_V)<<(SPI_MEM_BUF13_S))
#define SPI_MEM_BUF13_V  0xFFFFFFFF
#define SPI_MEM_BUF13_S  0

#define SPI_MEM_W14_REG(i)          (REG_SPI_MEM_BASE(i) + 0x90)
/* SPI_MEM_BUF14:R/W/SS；位位置：[31:0]；默认值：32'b0；*/
/*description:数据缓冲区。*/
#define SPI_MEM_BUF14    0xFFFFFFFF
#define SPI_MEM_BUF14_M  ((SPI_MEM_BUF14_V)<<(SPI_MEM_BUF14_S))
#define SPI_MEM_BUF14_V  0xFFFFFFFF
#define SPI_MEM_BUF14_S  0

#define SPI_MEM_W15_REG(i)          (REG_SPI_MEM_BASE(i) + 0x94)
/* SPI_MEM_BUF15:R/W/SS；位位置：[31:0]；默认值：32'b0；*/
/*description:数据缓冲区。*/
#define SPI_MEM_BUF15    0xFFFFFFFF
#define SPI_MEM_BUF15_M  ((SPI_MEM_BUF15_V)<<(SPI_MEM_BUF15_S))
#define SPI_MEM_BUF15_V  0xFFFFFFFF
#define SPI_MEM_BUF15_S  0

#define SPI_MEM_FLASH_WAITI_CTRL_REG(i)          (REG_SPI_MEM_BASE(i) + 0x98)
/* SPI_MEM_WAITI-ddummy_CYCLELEN:R/W；比特位置：[15:10]；默认值：6'0；*/
/*description:等待闪存空闲（RDSR）时的虚拟周期长度。。*/
#define SPI_MEM_WAITI_DUMMY_CYCLELEN    0x0000003F
#define SPI_MEM_WAITI_DUMMY_CYCLELEN_M  ((SPI_MEM_WAITI_DUMMY_CYCLELEN_V)<<(SPI_MEM_WAITI_DUMMY_CYCLELEN_S))
#define SPI_MEM_WAITI_DUMMY_CYCLELEN_V  0x3F
#define SPI_MEM_WAITI_DUMMY_CYCLELEN_S  10
/* SPI_MEM_WAITI_CMD:R/W；比特位置：[9:2]；默认值：8'h05；*/
/*description:自动等待闪存空闲传输（RDSR）的命令值。。*/
#define SPI_MEM_WAITI_CMD    0x000000FF
#define SPI_MEM_WAITI_CMD_M  ((SPI_MEM_WAITI_CMD_V)<<(SPI_MEM_WAITI_CMD_S))
#define SPI_MEM_WAITI_CMD_V  0xFF
#define SPI_MEM_WAITI_CMD_S  2
/* SPI_MEM_WAITI_dedumm:R/W；位位置：[1]；默认值：1’b0；*/
/*description:设置此位以启用自动等待闪存空闲传输（RDSR）中的DUMMY阶段。。*/
#define SPI_MEM_WAITI_DUMMY    (BIT(1))
#define SPI_MEM_WAITI_DUMMY_M  (BIT(1))
#define SPI_MEM_WAITI_DUMMY_V  0x1
#define SPI_MEM_WAITI_DUMMY_S  1
/* SPI_MEM_WAITI_EN:R/W；位位置：[0]；默认值：1’b0；*/
/*description:设置此位以在发送PP/SE/BE/CE/WRSR/PES命令时启用自动等待闪存空闲操作。。*/
#define SPI_MEM_WAITI_EN    (BIT(0))
#define SPI_MEM_WAITI_EN_M  (BIT(0))
#define SPI_MEM_WAITI_EN_V  0x1
#define SPI_MEM_WAITI_EN_S  0

#define SPI_MEM_FLASH_SUS_CMD_REG(i)          (REG_SPI_MEM_BASE(i) + 0x9C)
/* SPI_MEM_PESR_IDLE_EN:R/W；位位置：[5]；默认值：1’b0；*/
/*description:1：分离PER闪存等待空闲和PES闪存等待空闲。0：不分开。。*/
#define SPI_MEM_PESR_IDLE_EN    (BIT(5))
#define SPI_MEM_PESR_IDLE_EN_M  (BIT(5))
#define SPI_MEM_PESR_IDLE_EN_V  0x1
#define SPI_MEM_PESR_IDLE_EN_S  5
/* SPI_MEM_PES_PER_EN:R/W；位位置：[4]；默认值：1’b0；*/
/*description:设置此位以启用PES传输触发PES传输选项。。*/
#define SPI_MEM_PES_PER_EN    (BIT(4))
#define SPI_MEM_PES_PER_EN_M  (BIT(4))
#define SPI_MEM_PES_PER_EN_V  0x1
#define SPI_MEM_PES_PER_EN_S  4
/* SPI_MEM_FLASH_pas_WAIT_EN:R/W；位位置：[3]；默认值：1’b0；*/
/*description:设置此位以在发送程序擦除暂停（PES）命令后添加延迟时间。。*/
#define SPI_MEM_FLASH_PES_WAIT_EN    (BIT(3))
#define SPI_MEM_FLASH_PES_WAIT_EN_M  (BIT(3))
#define SPI_MEM_FLASH_PES_WAIT_EN_V  0x1
#define SPI_MEM_FLASH_PES_WAIT_EN_S  3
/* SPI_MEM_FLASH_PER_WAIT_EN:R/W；位位置：[2]；默认值：1’b0；*/
/*description:设置此位以在发送程序擦除恢复（PER）后添加延迟时间。。*/
#define SPI_MEM_FLASH_PER_WAIT_EN    (BIT(2))
#define SPI_MEM_FLASH_PER_WAIT_EN_M  (BIT(2))
#define SPI_MEM_FLASH_PER_WAIT_EN_V  0x1
#define SPI_MEM_FLASH_PER_WAIT_EN_S  2
/* SPI_MEM_FLASH_PES:R/W/SS/SC；位位置：[1]；默认值：1’b0；*/
/*描述：程序擦除暂停位，当该位被设置时，将触发程序擦除暂停操作。操作完成后，该位将被清除。1： 启用0:禁用。*/
#define SPI_MEM_FLASH_PES    (BIT(1))
#define SPI_MEM_FLASH_PES_M  (BIT(1))
#define SPI_MEM_FLASH_PES_V  0x1
#define SPI_MEM_FLASH_PES_S  1
/* SPI_MEM_FLASH_par:R/W/SS/SC；位位置：[0]；默认值：1’b0；*/
/*描述：程序擦除恢复位，程序擦除暂停操作将在设置位时触发。操作完成后，该位将被清除。1： 启用0:禁用。*/
#define SPI_MEM_FLASH_PER    (BIT(0))
#define SPI_MEM_FLASH_PER_M  (BIT(0))
#define SPI_MEM_FLASH_PER_V  0x1
#define SPI_MEM_FLASH_PER_S  0

#define SPI_MEM_FLASH_SUS_CTRL_REG(i)          (REG_SPI_MEM_BASE(i) + 0xA0)
/* SPI_MEM_FLASH_pas_COMMAND:R/W；比特位置：[16:9]；默认值：8'75；*/
/*description:编程/擦除挂起命令值。。*/
#define SPI_MEM_FLASH_PES_COMMAND    0x000000FF
#define SPI_MEM_FLASH_PES_COMMAND_M  ((SPI_MEM_FLASH_PES_COMMAND_V)<<(SPI_MEM_FLASH_PES_COMMAND_S))
#define SPI_MEM_FLASH_PES_COMMAND_V  0xFF
#define SPI_MEM_FLASH_PES_COMMAND_S  9
/* SPI_MEM_FLASH_PER_COMMAND:R/W；位位置：[8:1]；默认值：8'h7a；*/
/*description:编程/擦除恢复命令值。。*/
#define SPI_MEM_FLASH_PER_COMMAND    0x000000FF
#define SPI_MEM_FLASH_PER_COMMAND_M  ((SPI_MEM_FLASH_PER_COMMAND_V)<<(SPI_MEM_FLASH_PER_COMMAND_S))
#define SPI_MEM_FLASH_PER_COMMAND_V  0xFF
#define SPI_MEM_FLASH_PER_COMMAND_S  1
/* SPI_MEM_FLASH_ppes_EN:R/W；位位置：[0]；默认值：1’b0；*/
/*description:设置此位以启用自动挂起功能。。*/
#define SPI_MEM_FLASH_PES_EN    (BIT(0))
#define SPI_MEM_FLASH_PES_EN_M  (BIT(0))
#define SPI_MEM_FLASH_PES_EN_V  0x1
#define SPI_MEM_FLASH_PES_EN_S  0

#define SPI_MEM_SUS_STATUS_REG(i)          (REG_SPI_MEM_BASE(i) + 0xA4)
/* SPI_MEM_FLASH_ppes_DLY_256:R/W；位位置：[6]；默认值：1’b0；*/
/*description:当SPI_MEM_FLASH_PES_WAIT_EN为1时有效。1:SPI1在发送PES命令后等待（SPI_MEM_CS_HOLD_DELAY_RES[9:0]256）SPI_CLK周期。0:发送PES命令后，SPI1等待（SPI_MEM_CS_HOLD_DELAY_RES[9:0]4）SPI_CLK周期。。*/
#define SPI_MEM_FLASH_PES_DLY_256    (BIT(6))
#define SPI_MEM_FLASH_PES_DLY_256_M  (BIT(6))
#define SPI_MEM_FLASH_PES_DLY_256_V  0x1
#define SPI_MEM_FLASH_PES_DLY_256_S  6
/* SPI_MEM_FLASH_PER_DLY_256:R/W；位位置：[5]；默认值：1’b0；*/
/*description:当SPI_MEM_FLASH_PER_WAIT_EN为1时有效。1:SPI1在发送PER命令后等待（SPI_MEM_CS_HOLD_DELAY_RES[9:0]256）SPI_CLK周期。0:发送PER命令后，SPI1等待（SPI_MEM_CS_HOLD_DELAY_RES[9:0]4）SPI_CLK周期。。*/
#define SPI_MEM_FLASH_PER_DLY_256    (BIT(5))
#define SPI_MEM_FLASH_PER_DLY_256_M  (BIT(5))
#define SPI_MEM_FLASH_PER_DLY_256_V  0x1
#define SPI_MEM_FLASH_PER_DLY_256_S  5
/* SPI_MEM_FLASH_DP_DLY_256:R/W；位位置：[4]；默认值：1’b0；*/
/*描述：1:SPI1在发送DP命令后等待（SPI_MEM_CS_HOLD_DELAY_RES[9:0]*256）SPI_CLK周期。0:发送DP命令后，SPI1等待（SPI_MEM_CS_HOLD_DELAY_RES[9:0]4）SPI_CLK循环。。*/
#define SPI_MEM_FLASH_DP_DLY_256    (BIT(4))
#define SPI_MEM_FLASH_DP_DLY_256_M  (BIT(4))
#define SPI_MEM_FLASH_DP_DLY_256_V  0x1
#define SPI_MEM_FLASH_DP_DLY_256_S  4
/* SPI_MEM_FLASH_RES_DLY_256:R/W；位位置：[3]；默认值：1’b0；*/
/*描述：1:SPI1在发送RES命令后等待（SPI_MEM_CS_HOLD_DELAY_RES[9:0]*256）SPI_CLK周期。0:发送RES命令后，SPI1等待（SPI_MEM_CS_HOLD_DELAY_RES[9:0]4）SPI_CLK周期。。*/
#define SPI_MEM_FLASH_RES_DLY_256    (BIT(3))
#define SPI_MEM_FLASH_RES_DLY_256_M  (BIT(3))
#define SPI_MEM_FLASH_RES_DLY_256_V  0x1
#define SPI_MEM_FLASH_RES_DLY_256_S  3
/* SPI_MEM_FLASH_HPM_DLY_256:R/W；位位置：[2]；默认值：1’b0；*/
/*描述：1:SPI1在发送HPM命令后等待（SPI_MEM_CS_HOLD_DELAY_RES[9:0]*256）SPI_CLK周期。0:发送HPM命令后，SPI1等待（SPI_MEM_CS_HOLD_DELAY_RES[9:0]4）SPI_CLK周期。。*/
#define SPI_MEM_FLASH_HPM_DLY_256    (BIT(2))
#define SPI_MEM_FLASH_HPM_DLY_256_M  (BIT(2))
#define SPI_MEM_FLASH_HPM_DLY_256_V  0x1
#define SPI_MEM_FLASH_HPM_DLY_256_S  2
/* SPI_MEM_FLASH_SUS:R/W/SS/SC；位位置：[0]；默认值：1'0；*/
/*description:闪存暂停的状态。发送PES命令时设置该位，发送PER时清除该位。仅用于SPI1。。*/
#define SPI_MEM_FLASH_SUS    (BIT(0))
#define SPI_MEM_FLASH_SUS_M  (BIT(0))
#define SPI_MEM_FLASH_SUS_V  0x1
#define SPI_MEM_FLASH_SUS_S  0

#define SPI_MEM_TIMING_CALI_REG(i)          (REG_SPI_MEM_BASE(i) + 0xA8)
/* SPI_MEM_EXTRA_DUMMY_CYCLELEN:R/W；位位置：[4:2]；默认值：3'd0；*/
/*description:在DUMMY阶段添加额外的SPI_CLK周期用于定时补偿。设置SPI_MEM_TIMING_CALI位时激活。。*/
#define SPI_MEM_EXTRA_DUMMY_CYCLELEN    0x00000007
#define SPI_MEM_EXTRA_DUMMY_CYCLELEN_M  ((SPI_MEM_EXTRA_DUMMY_CYCLELEN_V)<<(SPI_MEM_EXTRA_DUMMY_CYCLELEN_S))
#define SPI_MEM_EXTRA_DUMMY_CYCLELEN_V  0x7
#define SPI_MEM_EXTRA_DUMMY_CYCLELEN_S  2
/* SPI_MEM_timeng_CALI:R/W；位位置：[1]；默认值：1’b0；*/
/*description:设置此位以在DUMMY阶段为所有读取操作添加额外的SPI_CLK周期。。*/
#define SPI_MEM_TIMING_CALI    (BIT(1))
#define SPI_MEM_TIMING_CALI_M  (BIT(1))
#define SPI_MEM_TIMING_CALI_V  0x1
#define SPI_MEM_TIMING_CALI_S  1
/* SPI_MEM_TIMING_CLK_ENA:R/W；位位置：[0]；默认值：1’b0；*/
/*description:将此位设置为开启HCLK。当PLL通电时，HCLK的频率等于PLL的频率。否则，频率等于XTAL的频率。。*/
#define SPI_MEM_TIMING_CLK_ENA    (BIT(0))
#define SPI_MEM_TIMING_CLK_ENA_M  (BIT(0))
#define SPI_MEM_TIMING_CLK_ENA_V  0x1
#define SPI_MEM_TIMING_CLK_ENA_S  0

#define SPI_MEM_DIN_MODE_REG(i)          (REG_SPI_MEM_BASE(i) + 0xAC)
/* SPI_MEM_DINS_MODE：R/W；比特位置：[26:24]；默认值：3'h0；*/
/*description:SPI_DQS输入延迟模式。0：无延迟。1： MSPI_CORE_CLK负边缘（SPI_MEM_DINS_NUM+1）周期的延迟。2： HCLK正边缘处（SPI_MEM_DINS_NUM+1）个周期和MSPI_CORE_CLK正边缘处一个周期的延迟。3： HCLK正边缘处（SPI_MEM_DINS_NUM+1）个周期和MSPI_CORE_CLK负边缘处一个周期的延迟。4： HCLK负边缘处（SPI_MEM_DINS_NUM+1）个周期和MSPI_CORE_CLK正边缘处一个周期的延迟。5： HCLK负边缘处（SPI_MEM_DINS_NUM+1）周期和MSPI_CORE_CLK负边缘处一个周期的延迟。。*/
#define SPI_MEM_DINS_MODE    0x00000007
#define SPI_MEM_DINS_MODE_M  ((SPI_MEM_DINS_MODE_V)<<(SPI_MEM_DINS_MODE_S))
#define SPI_MEM_DINS_MODE_V  0x7
#define SPI_MEM_DINS_MODE_S  24
/* SPI_MEM_DIN7模式：R/W；比特位置：[23:21]；默认值：3'h0；*/
/*description:SPI_IO7输入延迟模式。0：无延迟。1： MSPI_CORE_CLK负边缘处（SPI_MEM_DIN$n_NUM+1）个周期的延迟。2： HCLK正边缘处（SPI_MEM_DIN$n_NUM+1）个周期和MSPI_CORE_CLK正边缘处一个周期的延迟。3： HCLK正边缘处（SPI_MEM_DIN$n_NUM+1）个周期和MSPI_CORE_CLK负边缘处一个周期的延迟。4： HCLK负边缘处（SPI_MEM_DIN$n_NUM+1）个周期和MSPI_CORE_CLK正边缘处一个周期的延迟。5： HCLK负边缘处（SPI_MEM_DIN$n_NUM+1）个周期和MSPI_CORE_CLK负边缘处一个周期的延迟。。*/
#define SPI_MEM_DIN7_MODE    0x00000007
#define SPI_MEM_DIN7_MODE_M  ((SPI_MEM_DIN7_MODE_V)<<(SPI_MEM_DIN7_MODE_S))
#define SPI_MEM_DIN7_MODE_V  0x7
#define SPI_MEM_DIN7_MODE_S  21
/* SPI_MEM_DIN6_MODE模式：R/W；比特位置：[20:18]；默认值：3'h0；*/
/*description:SPI_IO6输入延迟模式。0：无延迟。1： MSPI_CORE_CLK负边缘（SPI_MEM_DIN$n_NUM+1）个周期的延迟。2： HCLK正边缘处（SPI_MEM_DIN$n_NUM+1）个周期和MSPI_CORE_CLK正边缘处一个周期的延迟。3： HCLK正边缘处（SPI_MEM_DIN$n_NUM+1）个周期和MSPI_CORE_CLK负边缘处一个周期的延迟。4： HCLK负边缘处（SPI_MEM_DIN$n_NUM+1）个周期和MSPI_CORE_CLK正边缘处一个周期的延迟。5： HCLK负边缘处（SPI_MEM_DIN$n_NUM+1）个周期和MSPI_CORE_CLK负边缘处一个周期的延迟。。*/
#define SPI_MEM_DIN6_MODE    0x00000007
#define SPI_MEM_DIN6_MODE_M  ((SPI_MEM_DIN6_MODE_V)<<(SPI_MEM_DIN6_MODE_S))
#define SPI_MEM_DIN6_MODE_V  0x7
#define SPI_MEM_DIN6_MODE_S  18
/* SPI_MEM_DIN5_MODE：R/W；比特位置：[17:15]；默认值：3'h0；*/
/*description:SPI_IO5输入延迟模式。0：无延迟。1： MSPI_CORE_CLK负边缘（SPI_MEM_DIN$n_NUM+1）个周期的延迟。2： HCLK正边缘处（SPI_MEM_DIN$n_NUM+1）个周期和MSPI_CORE_CLK正边缘处一个周期的延迟。3： HCLK正边缘处（SPI_MEM_DIN$n_NUM+1）个周期和MSPI_CORE_CLK负边缘处一个周期的延迟。4： HCLK负边缘处（SPI_MEM_DIN$n_NUM+1）个周期和MSPI_CORE_CLK正边缘处一个周期的延迟。5： HCLK负边缘处（SPI_MEM_DIN$n_NUM+1）个周期和MSPI_CORE_CLK负边缘处一个周期的延迟。。*/
#define SPI_MEM_DIN5_MODE    0x00000007
#define SPI_MEM_DIN5_MODE_M  ((SPI_MEM_DIN5_MODE_V)<<(SPI_MEM_DIN5_MODE_S))
#define SPI_MEM_DIN5_MODE_V  0x7
#define SPI_MEM_DIN5_MODE_S  15
/* SPI_MEM_DIN4_MODE:R/W；比特位置：[14:12]；默认值：3'h0；*/
/*description:SPI_IO4输入延迟模式。0：无延迟。1： MSPI_CORE_CLK负边缘（SPI_MEM_DIN$n_NUM+1）个周期的延迟。2： HCLK正边缘处（SPI_MEM_DIN$n_NUM+1）个周期和MSPI_CORE_CLK正边缘处一个周期的延迟。3： HCLK正边缘处（SPI_MEM_DIN$n_NUM+1）个周期和MSPI_CORE_CLK负边缘处一个周期的延迟。4： HCLK负边缘处（SPI_MEM_DIN$n_NUM+1）个周期和MSPI_CORE_CLK正边缘处一个周期的延迟。5： HCLK负边缘处（SPI_MEM_DIN$n_NUM+1）个周期和MSPI_CORE_CLK负边缘处一个周期的延迟。。*/
#define SPI_MEM_DIN4_MODE    0x00000007
#define SPI_MEM_DIN4_MODE_M  ((SPI_MEM_DIN4_MODE_V)<<(SPI_MEM_DIN4_MODE_S))
#define SPI_MEM_DIN4_MODE_V  0x7
#define SPI_MEM_DIN4_MODE_S  12
/* SPI_MEM_DIN3_MODE：R/W；比特位置：[11:9]；默认值：3'h0；*/
/*description:SPI_HD输入延迟模式。0：无延迟。1： MSPI_CORE_CLK负边缘（SPI_MEM_DIN$n_NUM+1）周期的延迟。2： HCLK正边缘处（SPI_MEM_DIN$n_NUM+1）个周期和MSPI_CORE_CLK正边缘处一个周期的延迟。3： HCLK正边缘处（SPI_MEM_DIN$n_NUM+1）个周期和MSPI_CORE_CLK负边缘处一个周期的延迟。4： HCLK负边缘处（SPI_MEM_DIN$n_NUM+1）个周期和MSPI_CORE_CLK正边缘处一个周期的延迟。5： HCLK负边缘处（SPI_MEM_DIN$n_NUM+1）个周期和MSPI_CORE_CLK负边缘处一个周期的延迟。。*/
#define SPI_MEM_DIN3_MODE    0x00000007
#define SPI_MEM_DIN3_MODE_M  ((SPI_MEM_DIN3_MODE_V)<<(SPI_MEM_DIN3_MODE_S))
#define SPI_MEM_DIN3_MODE_V  0x7
#define SPI_MEM_DIN3_MODE_S  9
/* SPI_MEM_din_模式：R/W；位位置：[8:6]；默认值：3'h0；*/
/*description:SPI_WP输入延迟模式。0：无延迟。1： MSPI_CORE_CLK负边缘（SPI_MEM_DIN$n_NUM+1）周期的延迟。2： HCLK正边缘处（SPI_MEM_DIN$n_NUM+1）个周期和MSPI_CORE_CLK正边缘处一个周期的延迟。3： HCLK正边缘处（SPI_MEM_DIN$n_NUM+1）个周期和MSPI_CORE_CLK负边缘处一个周期的延迟。4： HCLK负边缘处（SPI_MEM_DIN$n_NUM+1）个周期和MSPI_CORE_CLK正边缘处一个周期的延迟。5： HCLK负边缘处（SPI_MEM_DIN$n_NUM+1）个周期和MSPI_CORE_CLK负边缘处一个周期的延迟。。*/
#define SPI_MEM_DIN2_MODE    0x00000007
#define SPI_MEM_DIN2_MODE_M  ((SPI_MEM_DIN2_MODE_V)<<(SPI_MEM_DIN2_MODE_S))
#define SPI_MEM_DIN2_MODE_V  0x7
#define SPI_MEM_DIN2_MODE_S  6
/* SPI_MEM_DIN1_MODE：R/W；比特位置：[5:3]；默认值：3'h0；*/
/*description:SPI_Q输入延迟模式。0：无延迟。1： MSPI_CORE_CLK负边缘（SPI_MEM_DIN$n_NUM+1）个周期的延迟。2： HCLK正边缘处（SPI_MEM_DIN$n_NUM+1）个周期和MSPI_CORE_CLK正边缘处一个周期的延迟。3： HCLK正边缘处（SPI_MEM_DIN$n_NUM+1）个周期和MSPI_CORE_CLK负边缘处一个周期的延迟。4： HCLK负边缘处（SPI_MEM_DIN$n_NUM+1）个周期和MSPI_CORE_CLK正边缘处一个周期的延迟。5： HCLK负边缘处（SPI_MEM_DIN$n_NUM+1）个周期和MSPI_CORE_CLK负边缘处一个周期的延迟。。*/
#define SPI_MEM_DIN1_MODE    0x00000007
#define SPI_MEM_DIN1_MODE_M  ((SPI_MEM_DIN1_MODE_V)<<(SPI_MEM_DIN1_MODE_S))
#define SPI_MEM_DIN1_MODE_V  0x7
#define SPI_MEM_DIN1_MODE_S  3
/* SPI_MEM_DIN0_MODE:R/W；位位置：[2:0]；默认值：3'h0；*/
/*description:SPI_D输入延迟模式。0：无延迟。1： MSPI_CORE_CLK负边缘（SPI_MEM_DIN$n_NUM+1）个周期的延迟。2： HCLK正边缘处（SPI_MEM_DIN$n_NUM+1）个周期和MSPI_CORE_CLK正边缘处一个周期的延迟。3： HCLK正边缘处（SPI_MEM_DIN$n_NUM+1）个周期和MSPI_CORE_CLK负边缘处一个周期的延迟。4： HCLK负边缘处（SPI_MEM_DIN$n_NUM+1）个周期和MSPI_CORE_CLK正边缘处一个周期的延迟。5： HCLK负边缘处（SPI_MEM_DIN$n_NUM+1）个周期和MSPI_CORE_CLK负边缘处一个周期的延迟。。*/
#define SPI_MEM_DIN0_MODE    0x00000007
#define SPI_MEM_DIN0_MODE_M  ((SPI_MEM_DIN0_MODE_V)<<(SPI_MEM_DIN0_MODE_S))
#define SPI_MEM_DIN0_MODE_V  0x7
#define SPI_MEM_DIN0_MODE_S  0

#define SPI_MEM_DIN_NUM_REG(i)          (REG_SPI_MEM_BASE(i) + 0xB0)
/* SPI_MEM_DINS_NUM:R/W；比特位置：[17:16]；默认值：2'h0；*/
/*description:SPI_DQS输入延迟数。。*/
#define SPI_MEM_DINS_NUM    0x00000003
#define SPI_MEM_DINS_NUM_M  ((SPI_MEM_DINS_NUM_V)<<(SPI_MEM_DINS_NUM_S))
#define SPI_MEM_DINS_NUM_V  0x3
#define SPI_MEM_DINS_NUM_S  16
/* SPI_MEM_DIN7_NUM:R/W；比特位置：[15:14]；默认值：2'h0；*/
/*description:SPI_IO7输入延迟数。。*/
#define SPI_MEM_DIN7_NUM    0x00000003
#define SPI_MEM_DIN7_NUM_M  ((SPI_MEM_DIN7_NUM_V)<<(SPI_MEM_DIN7_NUM_S))
#define SPI_MEM_DIN7_NUM_V  0x3
#define SPI_MEM_DIN7_NUM_S  14
/* SPI_MEM_DIN6_NUM：随机；比特位置：[13:12]；默认值：2'h0；*/
/*description:SPI_IO6输入延迟数。。*/
#define SPI_MEM_DIN6_NUM    0x00000003
#define SPI_MEM_DIN6_NUM_M  ((SPI_MEM_DIN6_NUM_V)<<(SPI_MEM_DIN6_NUM_S))
#define SPI_MEM_DIN6_NUM_V  0x3
#define SPI_MEM_DIN6_NUM_S  12
/* SPI_MEM_DIN5_NUM:R/W；比特位置：[11:10]；默认值：2'h0；*/
/*description:SPI_IO5输入延迟数。。*/
#define SPI_MEM_DIN5_NUM    0x00000003
#define SPI_MEM_DIN5_NUM_M  ((SPI_MEM_DIN5_NUM_V)<<(SPI_MEM_DIN5_NUM_S))
#define SPI_MEM_DIN5_NUM_V  0x3
#define SPI_MEM_DIN5_NUM_S  10
/* SPI_MEM_DIN4_NUM:R/W；比特位置：[9:8]；默认值：2'h0；*/
/*description:SPI_IO4输入延迟数。。*/
#define SPI_MEM_DIN4_NUM    0x00000003
#define SPI_MEM_DIN4_NUM_M  ((SPI_MEM_DIN4_NUM_V)<<(SPI_MEM_DIN4_NUM_S))
#define SPI_MEM_DIN4_NUM_V  0x3
#define SPI_MEM_DIN4_NUM_S  8
/* SPI_MEM_DIN3_NUM:R/W；位位置：[7:6]；默认值：2'h0；*/
/*description:SPI_HD输入延迟数。。*/
#define SPI_MEM_DIN3_NUM    0x00000003
#define SPI_MEM_DIN3_NUM_M  ((SPI_MEM_DIN3_NUM_V)<<(SPI_MEM_DIN3_NUM_S))
#define SPI_MEM_DIN3_NUM_V  0x3
#define SPI_MEM_DIN3_NUM_S  6
/* SPI_MEM_dindi_NUM:R/W；比特位置：[5:4]；默认值：2'h0；*/
/*description:SPI_WP输入延迟数。。*/
#define SPI_MEM_DIN2_NUM    0x00000003
#define SPI_MEM_DIN2_NUM_M  ((SPI_MEM_DIN2_NUM_V)<<(SPI_MEM_DIN2_NUM_S))
#define SPI_MEM_DIN2_NUM_V  0x3
#define SPI_MEM_DIN2_NUM_S  4
/* SPI_MEM_DIN1_NUM：随机；位位置：[3:2]；默认值：2'h0；*/
/*description:SPI_Q输入延迟数。。*/
#define SPI_MEM_DIN1_NUM    0x00000003
#define SPI_MEM_DIN1_NUM_M  ((SPI_MEM_DIN1_NUM_V)<<(SPI_MEM_DIN1_NUM_S))
#define SPI_MEM_DIN1_NUM_V  0x3
#define SPI_MEM_DIN1_NUM_S  2
/* SPI_MEM_DIN0_NUM:R/W；位位置：[1:0]；默认值：2'h0；*/
/*description:SPI_D输入延迟数。。*/
#define SPI_MEM_DIN0_NUM    0x00000003
#define SPI_MEM_DIN0_NUM_M  ((SPI_MEM_DIN0_NUM_V)<<(SPI_MEM_DIN0_NUM_S))
#define SPI_MEM_DIN0_NUM_V  0x3
#define SPI_MEM_DIN0_NUM_S  0

#define SPI_MEM_DOUT_MODE_REG(i)          (REG_SPI_MEM_BASE(i) + 0xB4)
/* SPI_MEM_DOUTS_MODE：R/W；位位置：[8]；默认值：1'0；*/
/*description:SPI_DQS输出延迟模式。0：无延迟。1： 在MSPI_CORE_CLK负边缘延迟一个周期。。*/
#define SPI_MEM_DOUTS_MODE    (BIT(8))
#define SPI_MEM_DOUTS_MODE_M  (BIT(8))
#define SPI_MEM_DOUTS_MODE_V  0x1
#define SPI_MEM_DOUTS_MODE_S  8
/* SPI_MEM_DOUT7_模式：R/W；位位置：[7]；默认值：1'0；*/
/*description:SPI_IO7输出延迟模式。0：无延迟。1： 在MSPI_CORE_CLK负边缘延迟一个周期。。*/
#define SPI_MEM_DOUT7_MODE    (BIT(7))
#define SPI_MEM_DOUT7_MODE_M  (BIT(7))
#define SPI_MEM_DOUT7_MODE_V  0x1
#define SPI_MEM_DOUT7_MODE_S  7
/* SPI_MEM_DOUT6_MODE模式：R/W；位位置：[6]；默认值：1'0；*/
/*description:SPI_IO6输出延迟模式。0：无延迟。1： 在MSPI_CORE_CLK负边缘延迟一个周期。。*/
#define SPI_MEM_DOUT6_MODE    (BIT(6))
#define SPI_MEM_DOUT6_MODE_M  (BIT(6))
#define SPI_MEM_DOUT6_MODE_V  0x1
#define SPI_MEM_DOUT6_MODE_S  6
/* SPI_MEM_DOUT5_MODE：R/W；位位置：[5]；默认值：1'0；*/
/*description:SPI_IO5输出延迟模式。0：无延迟。1： 在MSPI_CORE_CLK负边缘延迟一个周期。。*/
#define SPI_MEM_DOUT5_MODE    (BIT(5))
#define SPI_MEM_DOUT5_MODE_M  (BIT(5))
#define SPI_MEM_DOUT5_MODE_V  0x1
#define SPI_MEM_DOUT5_MODE_S  5
/* SPI_MEM_DOUT4_MODE:R/W；位位置：[4]；默认值：1'0；*/
/*description:SPI_IO4输出延迟模式。0：无延迟。1： 在MSPI_CORE_CLK负边缘延迟一个周期。。*/
#define SPI_MEM_DOUT4_MODE    (BIT(4))
#define SPI_MEM_DOUT4_MODE_M  (BIT(4))
#define SPI_MEM_DOUT4_MODE_V  0x1
#define SPI_MEM_DOUT4_MODE_S  4
/* SPI_MEM_DOUT3_MODE：R/W；位位置：[3]；默认值：1'0；*/
/*description:SPI_HD输出延迟模式。0：无延迟。1： 在MSPI_CORE_CLK负边缘延迟一个周期。。*/
#define SPI_MEM_DOUT3_MODE    (BIT(3))
#define SPI_MEM_DOUT3_MODE_M  (BIT(3))
#define SPI_MEM_DOUT3_MODE_V  0x1
#define SPI_MEM_DOUT3_MODE_S  3
/* SPI_MEM_DOUT2_MODE:R/W；位位置：[2]；默认值：1'0；*/
/*description:SPI_WP输出延迟模式。0：无延迟。1： 在MSPI_CORE_CLK负边缘延迟一个周期。。*/
#define SPI_MEM_DOUT2_MODE    (BIT(2))
#define SPI_MEM_DOUT2_MODE_M  (BIT(2))
#define SPI_MEM_DOUT2_MODE_V  0x1
#define SPI_MEM_DOUT2_MODE_S  2
/* SPI_MEM_DOUT1_MODE：R/W；位位置：[1]；默认值：1'0；*/
/*description:SPI_Q输出延迟模式。0：无延迟。1： 在MSPI_CORE_CLK负边缘延迟一个周期。。*/
#define SPI_MEM_DOUT1_MODE    (BIT(1))
#define SPI_MEM_DOUT1_MODE_M  (BIT(1))
#define SPI_MEM_DOUT1_MODE_V  0x1
#define SPI_MEM_DOUT1_MODE_S  1
/* SPI_MEM_DOUT0_MODE:R/W；位位置：[0]；默认值：1'0；*/
/*description:SPI_D输出延迟模式。0：无延迟。1： 在MSPI_CORE_CLK负边缘延迟一个周期。。*/
#define SPI_MEM_DOUT0_MODE    (BIT(0))
#define SPI_MEM_DOUT0_MODE_M  (BIT(0))
#define SPI_MEM_DOUT0_MODE_V  0x1
#define SPI_MEM_DOUT0_MODE_S  0

#define SPI_MEM_SPI_SMEM_TIMING_CALI_REG(i)          (REG_SPI_MEM_BASE(i) + 0xBC)
/* SPI_MEM_SPI_SMEM_EXTRA_DUMMY_CYCLELEN:R/W；位位置：[4:2]；默认值：3'd0；*/
/*描述：当SPI0访问Ext_RAM时，在DUMMY阶段添加额外的SPI_CLK周期用于定时补偿。设置SPI_SMEM_TIMING_CALI位时激活。。*/
#define SPI_MEM_SPI_SMEM_EXTRA_DUMMY_CYCLELEN    0x00000007
#define SPI_MEM_SPI_SMEM_EXTRA_DUMMY_CYCLELEN_M  ((SPI_MEM_SPI_SMEM_EXTRA_DUMMY_CYCLELEN_V)<<(SPI_MEM_SPI_SMEM_EXTRA_DUMMY_CYCLELEN_S))
#define SPI_MEM_SPI_SMEM_EXTRA_DUMMY_CYCLELEN_V  0x7
#define SPI_MEM_SPI_SMEM_EXTRA_DUMMY_CYCLELEN_S  2
/* SPI_MEM_SPI_SMEM_timeng_CALI:R/W；位位置：[1]；默认值：1’b0；*/
/*description:设置此位以在DUMMY阶段为所有读取操作添加额外的SPI_CLK周期。。*/
#define SPI_MEM_SPI_SMEM_TIMING_CALI    (BIT(1))
#define SPI_MEM_SPI_SMEM_TIMING_CALI_M  (BIT(1))
#define SPI_MEM_SPI_SMEM_TIMING_CALI_V  0x1
#define SPI_MEM_SPI_SMEM_TIMING_CALI_S  1
/* SPI_MEM_SPI_SMEM_TIMING_CLK_ENA:R/W；位位置：[0]；默认值：1’b0；*/
/*description:将此位设置为开启HCLK。当PLL通电时，HCLK的频率等于PLL的频率。否则，频率等于XTAL的频率。。*/
#define SPI_MEM_SPI_SMEM_TIMING_CLK_ENA    (BIT(0))
#define SPI_MEM_SPI_SMEM_TIMING_CLK_ENA_M  (BIT(0))
#define SPI_MEM_SPI_SMEM_TIMING_CLK_ENA_V  0x1
#define SPI_MEM_SPI_SMEM_TIMING_CLK_ENA_S  0

#define SPI_MEM_SPI_SMEM_DIN_MODE_REG(i)          (REG_SPI_MEM_BASE(i) + 0xC0)
/* SPI_MEM_SPI_SMEM_DINS_MODE：R/W；比特位置：[26:24]；默认值：3'h0；*/
/*description:SPI_DQS输入延迟模式。0：无延迟。1： MSPI_CORE_CLK负边缘处（SPI_SMEM_DINS_NUM+1）个周期的延迟。2： HCLK正边缘处（SPI_SMEM_DINS_NUM+1）个周期和MSPI_CORE_CLK正边缘处一个周期的延迟。3： HCLK正边缘处（SPI_SMEM_DINS_NUM+1）个周期和MSPI_CORE_CLK负边缘处一个周期的延迟。4： HCLK负边缘处（SPI_SMEM_DINS_NUM+1）个周期和MSPI_CORE_CLK正边缘处一个周期的延迟。5： HCLK负边缘处（SPI_SMEM_DINS_NUM+1）个周期和MSPI_CORE_CLK负边缘处一个周期的延迟。。*/
#define SPI_MEM_SPI_SMEM_DINS_MODE    0x00000007
#define SPI_MEM_SPI_SMEM_DINS_MODE_M  ((SPI_MEM_SPI_SMEM_DINS_MODE_V)<<(SPI_MEM_SPI_SMEM_DINS_MODE_S))
#define SPI_MEM_SPI_SMEM_DINS_MODE_V  0x7
#define SPI_MEM_SPI_SMEM_DINS_MODE_S  24
/* SPI_MEM_SPI_SMEM_DIN7模式：R/W；比特位置：[23:21]；默认值：3'h0；*/
/*description:SPI_IO7输入延迟模式。0：无延迟。1： MSPI_CORE_CLK负边缘处（SPI_SMEM_DIN$n_NUM+1）个周期的延迟。2： HCLK正边缘处（SPI_SMEM_DIN$n_NUM+1）个周期和MSPI_CORE_CLK正边缘处一个周期的延迟。3： HCLK正边缘处（SPI_SMEM_DIN$n_NUM+1）个周期和MSPI_CORE_CLK负边缘处一个周期的延迟。4： HCLK负边缘处（SPI_SMEM_DIN$n_NUM+1）个周期和MSPI_CORE_CLK正边缘处一个周期的延迟。5： HCLK负边缘处（SPI_SMEM_DIN$n_NUM+1）个周期和MSPI_CORE_CLK负边缘处一个周期的延迟。。*/
#define SPI_MEM_SPI_SMEM_DIN7_MODE    0x00000007
#define SPI_MEM_SPI_SMEM_DIN7_MODE_M  ((SPI_MEM_SPI_SMEM_DIN7_MODE_V)<<(SPI_MEM_SPI_SMEM_DIN7_MODE_S))
#define SPI_MEM_SPI_SMEM_DIN7_MODE_V  0x7
#define SPI_MEM_SPI_SMEM_DIN7_MODE_S  21
/* SPI_MEM_SPI_SMEM_DIN6_MODE模式：R/W；比特位置：[20:18]；默认值：3'h0；*/
/*description:SPI_IO6输入延迟模式。0：无延迟。1： MSPI_CORE_CLK负边缘处（SPI_SMEM_DIN$n_NUM+1）个周期的延迟。2： HCLK正边缘处（SPI_SMEM_DIN$n_NUM+1）个周期和MSPI_CORE_CLK正边缘处一个周期的延迟。3： HCLK正边缘处（SPI_SMEM_DIN$n_NUM+1）个周期和MSPI_CORE_CLK负边缘处一个周期的延迟。4： HCLK负边缘处（SPI_SMEM_DIN$n_NUM+1）个周期和MSPI_CORE_CLK正边缘处一个周期的延迟。5： HCLK负边缘处（SPI_SMEM_DIN$n_NUM+1）个周期和MSPI_CORE_CLK负边缘处一个周期的延迟。。*/
#define SPI_MEM_SPI_SMEM_DIN6_MODE    0x00000007
#define SPI_MEM_SPI_SMEM_DIN6_MODE_M  ((SPI_MEM_SPI_SMEM_DIN6_MODE_V)<<(SPI_MEM_SPI_SMEM_DIN6_MODE_S))
#define SPI_MEM_SPI_SMEM_DIN6_MODE_V  0x7
#define SPI_MEM_SPI_SMEM_DIN6_MODE_S  18
/* SPI_MEM_SPI_SMEM_DIN5_MODE：R/W；比特位置：[17:15]；默认值：3'h0；*/
/*description:SPI_IO5输入延迟模式。0：无延迟。1： MSPI_CORE_CLK负边缘处（SPI_SMEM_DIN$n_NUM+1）个周期的延迟。2： HCLK正边缘处（SPI_SMEM_DIN$n_NUM+1）个周期和MSPI_CORE_CLK正边缘处一个周期的延迟。3： HCLK正边缘处（SPI_SMEM_DIN$n_NUM+1）个周期和MSPI_CORE_CLK负边缘处一个周期的延迟。4： HCLK负边缘处（SPI_SMEM_DIN$n_NUM+1）个周期和MSPI_CORE_CLK正边缘处一个周期的延迟。5： HCLK负边缘处（SPI_SMEM_DIN$n_NUM+1）个周期和MSPI_CORE_CLK负边缘处一个周期的延迟。。*/
#define SPI_MEM_SPI_SMEM_DIN5_MODE    0x00000007
#define SPI_MEM_SPI_SMEM_DIN5_MODE_M  ((SPI_MEM_SPI_SMEM_DIN5_MODE_V)<<(SPI_MEM_SPI_SMEM_DIN5_MODE_S))
#define SPI_MEM_SPI_SMEM_DIN5_MODE_V  0x7
#define SPI_MEM_SPI_SMEM_DIN5_MODE_S  15
/* SPI_MEM_SPI_SMEM_DIN4模式：R/W；比特位置：[14:12]；默认值：3'h0；*/
/*description:SPI_IO4输入延迟模式。0：无延迟。1： MSPI_CORE_CLK负边缘处（SPI_SMEM_DIN$n_NUM+1）个周期的延迟。2： HCLK正边缘处（SPI_SMEM_DIN$n_NUM+1）个周期和MSPI_CORE_CLK正边缘处一个周期的延迟。3： HCLK正边缘处（SPI_SMEM_DIN$n_NUM+1）个周期和MSPI_CORE_CLK负边缘处一个周期的延迟。4： HCLK负边缘处（SPI_SMEM_DIN$n_NUM+1）个周期和MSPI_CORE_CLK正边缘处一个周期的延迟。5： HCLK负边缘处（SPI_SMEM_DIN$n_NUM+1）个周期和MSPI_CORE_CLK负边缘处一个周期的延迟。。*/
#define SPI_MEM_SPI_SMEM_DIN4_MODE    0x00000007
#define SPI_MEM_SPI_SMEM_DIN4_MODE_M  ((SPI_MEM_SPI_SMEM_DIN4_MODE_V)<<(SPI_MEM_SPI_SMEM_DIN4_MODE_S))
#define SPI_MEM_SPI_SMEM_DIN4_MODE_V  0x7
#define SPI_MEM_SPI_SMEM_DIN4_MODE_S  12
/* SPI_MEM_SPI_SMEM_DIN3_MODE：R/W；比特位置：[11:9]；默认值：3'h0；*/
/*description:SPI_HD输入延迟模式。0：无延迟。1： MSPI_CORE_CLK负边缘处（SPI_SMEM_DIN$n_NUM+1）个周期的延迟。2： HCLK正边缘处（SPI_SMEM_DIN$n_NUM+1）个周期和MSPI_CORE_CLK正边缘处一个周期的延迟。3： HCLK正边缘处（SPI_SMEM_DIN$n_NUM+1）个周期和MSPI_CORE_CL负边缘处一个周期的延迟。4： HCLK负边缘的（SPI_SMEM_DIN$n_NUM+1）个周期和MSPI_CORE_CLK正边缘的一个周期的延迟。5： HCLK负边缘处（SPI_SMEM_DIN$n_NUM+1）个周期和MSPI_CORE_CLK负边缘处一个周期的延迟。。*/
#define SPI_MEM_SPI_SMEM_DIN3_MODE    0x00000007
#define SPI_MEM_SPI_SMEM_DIN3_MODE_M  ((SPI_MEM_SPI_SMEM_DIN3_MODE_V)<<(SPI_MEM_SPI_SMEM_DIN3_MODE_S))
#define SPI_MEM_SPI_SMEM_DIN3_MODE_V  0x7
#define SPI_MEM_SPI_SMEM_DIN3_MODE_S  9
/* SPI_MEM_SPI_SMEM_din_模式：R/W；位位置：[8:6]；默认值：3'h0；*/
/*description:SPI_WP输入延迟模式。0：无延迟。1： MSPI_CORE_CLK负边缘处（SPI_SMEM_DIN$n_NUM+1）个周期的延迟。2： HCLK正边缘处（SPI_SMEM_DIN$n_NUM+1）个周期和MSPI_CORE_CLK正边缘处一个周期的延迟。3： HCLK正边缘处（SPI_SMEM_DIN$n_NUM+1）个周期和MSPI_CORE_CL负边缘处一个周期的延迟。4： HCLK负边缘的（SPI_SMEM_DIN$n_NUM+1）个周期和MSPI_CORE_CLK正边缘的一个周期的延迟。5： HCLK负边缘处（SPI_SMEM_DIN$n_NUM+1）个周期和MSPI_CORE_CLK负边缘处一个周期的延迟。。*/
#define SPI_MEM_SPI_SMEM_DIN2_MODE    0x00000007
#define SPI_MEM_SPI_SMEM_DIN2_MODE_M  ((SPI_MEM_SPI_SMEM_DIN2_MODE_V)<<(SPI_MEM_SPI_SMEM_DIN2_MODE_S))
#define SPI_MEM_SPI_SMEM_DIN2_MODE_V  0x7
#define SPI_MEM_SPI_SMEM_DIN2_MODE_S  6
/* SPI_MEM_SPI_SMEM_DIN1_MODE：R/W；比特位置：[5:3]；默认值：3'h0；*/
/*description:SPI_Q输入延迟模式。0：无延迟。1： MSPI_CORE_CLK负边缘（SPI_SMEM_DIN$n_NUM+1）循环的延迟。2： HCLK正边缘处（SPI_SMEM_DIN$n_NUM+1）个周期和MSPI_CORE_CLK正边缘处一个周期的延迟。3： HCLK正边缘处（SPI_SMEM_DIN$n_NUM+1）个周期和MSPI_CORE_CLK负边缘处一个周期的延迟。4： HCLK负边缘处（SPI_SMEM_DIN$n_NUM+1）个周期和MSPI_CORE_CLK正边缘处一个周期的延迟。5： HCLK负边缘处（SPI_SMEM_DIN$n_NUM+1）个周期和MSPI_CORE_CLK负边缘处一个周期的延迟。。*/
#define SPI_MEM_SPI_SMEM_DIN1_MODE    0x00000007
#define SPI_MEM_SPI_SMEM_DIN1_MODE_M  ((SPI_MEM_SPI_SMEM_DIN1_MODE_V)<<(SPI_MEM_SPI_SMEM_DIN1_MODE_S))
#define SPI_MEM_SPI_SMEM_DIN1_MODE_V  0x7
#define SPI_MEM_SPI_SMEM_DIN1_MODE_S  3
/* SPI_MEM_SPI_SMEM_DIN0_MODE:R/W；位位置：[2:0]；默认值：3'h0；*/
/*description:SPI_D输入延迟模式。0：无延迟。1： MSPI_CORE_CLK负边缘（SPI_SMEM_DIN$n_NUM+1）循环的延迟。2： HCLK正边缘处（SPI_SMEM_DIN$n_NUM+1）个周期和MSPI_CORE_CLK正边缘处一个周期的延迟。3： HCLK正边缘处（SPI_SMEM_DIN$n_NUM+1）个周期和MSPI_CORE_CLK负边缘处一个周期的延迟。4： HCLK负边缘处（SPI_SMEM_DIN$n_NUM+1）个周期和MSPI_CORE_CLK正边缘处一个周期的延迟。5： HCLK负边缘处（SPI_SMEM_DIN$n_NUM+1）个周期和MSPI_CORE_CLK负边缘处一个周期的延迟。。*/
#define SPI_MEM_SPI_SMEM_DIN0_MODE    0x00000007
#define SPI_MEM_SPI_SMEM_DIN0_MODE_M  ((SPI_MEM_SPI_SMEM_DIN0_MODE_V)<<(SPI_MEM_SPI_SMEM_DIN0_MODE_S))
#define SPI_MEM_SPI_SMEM_DIN0_MODE_V  0x7
#define SPI_MEM_SPI_SMEM_DIN0_MODE_S  0

#define SPI_MEM_SPI_SMEM_DIN_NUM_REG(i)          (REG_SPI_MEM_BASE(i) + 0xC4)
/* SPI_MEM_SPI_SMEM_DINS_NUM:R/W；比特位置：[17:16]；默认值：2'h0；*/
/*description:SPI_DQS输入延迟数。。*/
#define SPI_MEM_SPI_SMEM_DINS_NUM    0x00000003
#define SPI_MEM_SPI_SMEM_DINS_NUM_M  ((SPI_MEM_SPI_SMEM_DINS_NUM_V)<<(SPI_MEM_SPI_SMEM_DINS_NUM_S))
#define SPI_MEM_SPI_SMEM_DINS_NUM_V  0x3
#define SPI_MEM_SPI_SMEM_DINS_NUM_S  16
/* SPI_MEM_SPI_SMEM_DIN7_NUM:R/W；比特位置：[15:14]；默认值：2'h0；*/
/*description:SPI_IO7输入延迟数。。*/
#define SPI_MEM_SPI_SMEM_DIN7_NUM    0x00000003
#define SPI_MEM_SPI_SMEM_DIN7_NUM_M  ((SPI_MEM_SPI_SMEM_DIN7_NUM_V)<<(SPI_MEM_SPI_SMEM_DIN7_NUM_S))
#define SPI_MEM_SPI_SMEM_DIN7_NUM_V  0x3
#define SPI_MEM_SPI_SMEM_DIN7_NUM_S  14
/* SPI_MEM_SPI_SMEM_DIN6_NUM：随机；比特位置：[13:12]；默认值：2'h0；*/
/*description:SPI_IO6输入延迟数。。*/
#define SPI_MEM_SPI_SMEM_DIN6_NUM    0x00000003
#define SPI_MEM_SPI_SMEM_DIN6_NUM_M  ((SPI_MEM_SPI_SMEM_DIN6_NUM_V)<<(SPI_MEM_SPI_SMEM_DIN6_NUM_S))
#define SPI_MEM_SPI_SMEM_DIN6_NUM_V  0x3
#define SPI_MEM_SPI_SMEM_DIN6_NUM_S  12
/* SPI_MEM_SPI_SMEM_DIN5_NUM:R/W；比特位置：[11:10]；默认值：2'h0；*/
/*description:SPI_IO5输入延迟数。。*/
#define SPI_MEM_SPI_SMEM_DIN5_NUM    0x00000003
#define SPI_MEM_SPI_SMEM_DIN5_NUM_M  ((SPI_MEM_SPI_SMEM_DIN5_NUM_V)<<(SPI_MEM_SPI_SMEM_DIN5_NUM_S))
#define SPI_MEM_SPI_SMEM_DIN5_NUM_V  0x3
#define SPI_MEM_SPI_SMEM_DIN5_NUM_S  10
/* SPI_MEM_SPI_SMEM_DIN4_NUM:R/W；比特位置：[9:8]；默认值：2'h0；*/
/*description:SPI_IO4输入延迟数。。*/
#define SPI_MEM_SPI_SMEM_DIN4_NUM    0x00000003
#define SPI_MEM_SPI_SMEM_DIN4_NUM_M  ((SPI_MEM_SPI_SMEM_DIN4_NUM_V)<<(SPI_MEM_SPI_SMEM_DIN4_NUM_S))
#define SPI_MEM_SPI_SMEM_DIN4_NUM_V  0x3
#define SPI_MEM_SPI_SMEM_DIN4_NUM_S  8
/* SPI_MEM_SPI_SMEM_DIN3_NUM:R/W；位位置：[7:6]；默认值：2'h0；*/
/*description:SPI_HD输入延迟数。。*/
#define SPI_MEM_SPI_SMEM_DIN3_NUM    0x00000003
#define SPI_MEM_SPI_SMEM_DIN3_NUM_M  ((SPI_MEM_SPI_SMEM_DIN3_NUM_V)<<(SPI_MEM_SPI_SMEM_DIN3_NUM_S))
#define SPI_MEM_SPI_SMEM_DIN3_NUM_V  0x3
#define SPI_MEM_SPI_SMEM_DIN3_NUM_S  6
/* SPI_MEM_SPI_SMEM_DIN2_NUM:R/W；比特位置：[5:4]；默认值：2'h0；*/
/*description:SPI_WP输入延迟数。。*/
#define SPI_MEM_SPI_SMEM_DIN2_NUM    0x00000003
#define SPI_MEM_SPI_SMEM_DIN2_NUM_M  ((SPI_MEM_SPI_SMEM_DIN2_NUM_V)<<(SPI_MEM_SPI_SMEM_DIN2_NUM_S))
#define SPI_MEM_SPI_SMEM_DIN2_NUM_V  0x3
#define SPI_MEM_SPI_SMEM_DIN2_NUM_S  4
/* SPI_MEM_SPI_SMEM_DIN1_NUM:R/W；位位置：[3:2]；默认值：2'h0；*/
/*description:SPI_Q输入延迟数。。*/
#define SPI_MEM_SPI_SMEM_DIN1_NUM    0x00000003
#define SPI_MEM_SPI_SMEM_DIN1_NUM_M  ((SPI_MEM_SPI_SMEM_DIN1_NUM_V)<<(SPI_MEM_SPI_SMEM_DIN1_NUM_S))
#define SPI_MEM_SPI_SMEM_DIN1_NUM_V  0x3
#define SPI_MEM_SPI_SMEM_DIN1_NUM_S  2
/* SPI_MEM_SPI_SMEM_DIN0_NUM:R/W；位位置：[1:0]；默认值：2'h0；*/
/*description:SPI_D输入延迟数。。*/
#define SPI_MEM_SPI_SMEM_DIN0_NUM    0x00000003
#define SPI_MEM_SPI_SMEM_DIN0_NUM_M  ((SPI_MEM_SPI_SMEM_DIN0_NUM_V)<<(SPI_MEM_SPI_SMEM_DIN0_NUM_S))
#define SPI_MEM_SPI_SMEM_DIN0_NUM_V  0x3
#define SPI_MEM_SPI_SMEM_DIN0_NUM_S  0

#define SPI_MEM_SPI_SMEM_DOUT_MODE_REG(i)          (REG_SPI_MEM_BASE(i) + 0xC8)
/* SPI_MEM_SPI_SMEM_DOUTS_MODE：R/W；位位置：[8]；默认值：1'0；*/
/*description:SPI_DQS输出延迟模式。0：无延迟。1： 在MSPI_CORE_CLK负边缘延迟一个周期。。*/
#define SPI_MEM_SPI_SMEM_DOUTS_MODE    (BIT(8))
#define SPI_MEM_SPI_SMEM_DOUTS_MODE_M  (BIT(8))
#define SPI_MEM_SPI_SMEM_DOUTS_MODE_V  0x1
#define SPI_MEM_SPI_SMEM_DOUTS_MODE_S  8
/* SPI_MEM_SPI_SMEM_DOUT7_模式：R/W；位位置：[7]；默认值：1'0；*/
/*description:SPI_IO7输出延迟模式。0：无延迟。1： 在MSPI_CORE_CLK负边缘延迟一个周期。。*/
#define SPI_MEM_SPI_SMEM_DOUT7_MODE    (BIT(7))
#define SPI_MEM_SPI_SMEM_DOUT7_MODE_M  (BIT(7))
#define SPI_MEM_SPI_SMEM_DOUT7_MODE_V  0x1
#define SPI_MEM_SPI_SMEM_DOUT7_MODE_S  7
/* SPI_MEM_SPI_SMEM_DOUT6_MODE模式：R/W；位位置：[6]；默认值：1'0；*/
/*description:SPI_IO6输出延迟模式。0：无延迟。1： 在MSPI_CORE_CLK负边缘延迟一个周期。。*/
#define SPI_MEM_SPI_SMEM_DOUT6_MODE    (BIT(6))
#define SPI_MEM_SPI_SMEM_DOUT6_MODE_M  (BIT(6))
#define SPI_MEM_SPI_SMEM_DOUT6_MODE_V  0x1
#define SPI_MEM_SPI_SMEM_DOUT6_MODE_S  6
/* SPI_MEM_SPI_SMEM_DOUT5_MODE：R/W；位位置：[5]；默认值：1'0；*/
/*description:SPI_IO5输出延迟模式。0：无延迟。1： 在MSPI_CORE_CLK负边缘延迟一个周期。。*/
#define SPI_MEM_SPI_SMEM_DOUT5_MODE    (BIT(5))
#define SPI_MEM_SPI_SMEM_DOUT5_MODE_M  (BIT(5))
#define SPI_MEM_SPI_SMEM_DOUT5_MODE_V  0x1
#define SPI_MEM_SPI_SMEM_DOUT5_MODE_S  5
/* SPI_MEM_SPI_SMEM_DOUT4_MODE：R/W；位位置：[4]；默认值：1'0；*/
/*description:SPI_IO4输出延迟模式。0：无延迟。1： 在MSPI_CORE_CLK负边缘延迟一个周期。。*/
#define SPI_MEM_SPI_SMEM_DOUT4_MODE    (BIT(4))
#define SPI_MEM_SPI_SMEM_DOUT4_MODE_M  (BIT(4))
#define SPI_MEM_SPI_SMEM_DOUT4_MODE_V  0x1
#define SPI_MEM_SPI_SMEM_DOUT4_MODE_S  4
/* SPI_MEM_SPI_SMEM_DOUT3_MODE：R/W；位位置：[3]；默认值：1'0；*/
/*description:SPI_HD输出延迟模式。0：无延迟。1： 在MSPI_CORE_CLK负边缘延迟一个周期。。*/
#define SPI_MEM_SPI_SMEM_DOUT3_MODE    (BIT(3))
#define SPI_MEM_SPI_SMEM_DOUT3_MODE_M  (BIT(3))
#define SPI_MEM_SPI_SMEM_DOUT3_MODE_V  0x1
#define SPI_MEM_SPI_SMEM_DOUT3_MODE_S  3
/* SPI_MEM_SPI_SMEM_DOUT2_MODE:R/W；位位置：[2]；默认值：1'0；*/
/*description:SPI_WP输出延迟模式。0：无延迟。1： 在MSPI_CORE_CLK负边缘延迟一个周期。。*/
#define SPI_MEM_SPI_SMEM_DOUT2_MODE    (BIT(2))
#define SPI_MEM_SPI_SMEM_DOUT2_MODE_M  (BIT(2))
#define SPI_MEM_SPI_SMEM_DOUT2_MODE_V  0x1
#define SPI_MEM_SPI_SMEM_DOUT2_MODE_S  2
/* SPI_MEM_SPI_SMEM_DOUT1_MODE：R/W；位位置：[1]；默认值：1'0；*/
/*description:SPI_Q输出延迟模式。0：无延迟。1： 在MSPI_CORE_CLK负边缘延迟一个周期。。*/
#define SPI_MEM_SPI_SMEM_DOUT1_MODE    (BIT(1))
#define SPI_MEM_SPI_SMEM_DOUT1_MODE_M  (BIT(1))
#define SPI_MEM_SPI_SMEM_DOUT1_MODE_V  0x1
#define SPI_MEM_SPI_SMEM_DOUT1_MODE_S  1
/* SPI_MEM_SPI_SMEM_DOUT0_MODE：R/W；位位置：[0]；默认值：1'0；*/
/*description:SPI_D输出延迟模式。0：无延迟。1： 在MSPI_CORE_CLK负边缘延迟一个周期。。*/
#define SPI_MEM_SPI_SMEM_DOUT0_MODE    (BIT(0))
#define SPI_MEM_SPI_SMEM_DOUT0_MODE_M  (BIT(0))
#define SPI_MEM_SPI_SMEM_DOUT0_MODE_V  0x1
#define SPI_MEM_SPI_SMEM_DOUT0_MODE_S  0

#define SPI_MEM_ECC_CTRL_REG(i)          (REG_SPI_MEM_BASE(i) + 0xCC)
/* SPI_MEM_SPI_FMEM_ECC_ERR_INT_EN:R/W；位位置：[8]；默认值：1’b0；*/
/*description:设置此位以计算访问闪存时MSPI ECC读取的错误时间。。*/
#define SPI_MEM_SPI_FMEM_ECC_ERR_INT_EN    (BIT(8))
#define SPI_MEM_SPI_FMEM_ECC_ERR_INT_EN_M  (BIT(8))
#define SPI_MEM_SPI_FMEM_ECC_ERR_INT_EN_V  0x1
#define SPI_MEM_SPI_FMEM_ECC_ERR_INT_EN_S  8
/* SPI_MEM_ECC_ERR_INT_NUM:R/W；位位置：[7:0]；默认值：8'd10；*/
/*description:设置MSPI ECC读取的错误时间，以生成MSPI SPI_MEM_ECC_ERR_INT中断。。*/
#define SPI_MEM_ECC_ERR_INT_NUM    0x000000FF
#define SPI_MEM_ECC_ERR_INT_NUM_M  ((SPI_MEM_ECC_ERR_INT_NUM_V)<<(SPI_MEM_ECC_ERR_INT_NUM_S))
#define SPI_MEM_ECC_ERR_INT_NUM_V  0xFF
#define SPI_MEM_ECC_ERR_INT_NUM_S  0

#define SPI_MEM_ECC_ERR_ADDR_REG(i)          (REG_SPI_MEM_BASE(i) + 0xD0)
/* SPI_MEM_ECC_ERR_ADDR:R/SS/WTC；位位置：[31:0]；默认值：32'h0；*/
/*描述：当设置SPI_FMEM_ECC_ERR_INT_EN/SPI_SMEM_ECC-ERR_INT_EN并访问闪存/Ext_RAM时，这些位显示第一个MSPI ECC错误地址，包括ECC字节错误和数据错误。设置SPI_MEM_ECC_ERR_INT_CLR位时清除。*/
#define SPI_MEM_ECC_ERR_ADDR    0xFFFFFFFF
#define SPI_MEM_ECC_ERR_ADDR_M  ((SPI_MEM_ECC_ERR_ADDR_V)<<(SPI_MEM_ECC_ERR_ADDR_S))
#define SPI_MEM_ECC_ERR_ADDR_V  0xFFFFFFFF
#define SPI_MEM_ECC_ERR_ADDR_S  0

#define SPI_MEM_ECC_ERR_BIT_REG(i)          (REG_SPI_MEM_BASE(i) + 0xD4)
/* SPI_MEM_ECC_ERR_CNT:RO；比特位置：[24:17]；默认值：8'd0；*/
/*描述：此位显示MSPI ECC读取的错误时间，包括ECC字节错误和数据字节错误。设置SPI_MEM_ECC_ERR_INT_CLR位时清除。*/
#define SPI_MEM_ECC_ERR_CNT    0x000000FF
#define SPI_MEM_ECC_ERR_CNT_M  ((SPI_MEM_ECC_ERR_CNT_V)<<(SPI_MEM_ECC_ERR_CNT_S))
#define SPI_MEM_ECC_ERR_CNT_V  0xFF
#define SPI_MEM_ECC_ERR_CNT_S  17
/* SPI_MEM_ECC_BYTE_ERR:R/SS/WTC；位位置：[16]；默认值：1'd0；*/
/*description:设置SPI_FMEM_ECC_ERR_INT_EN/SPI_SMEM_ECC-ERR_INT_EN并访问flash/Ext_RAM时，记录第一个ECC字节错误。它由SPI_MEM_ECC_ERR_INT_CLR位清除。。*/
#define SPI_MEM_ECC_BYTE_ERR    (BIT(16))
#define SPI_MEM_ECC_BYTE_ERR_M  (BIT(16))
#define SPI_MEM_ECC_BYTE_ERR_V  0x1
#define SPI_MEM_ECC_BYTE_ERR_S  16
/* SPI_MEM_ECC_CHK_ERR_BIT:R/SS/WTC；比特位置：[15:13]；默认值：3'd0；*/
/*description:设置SPI_MEM_ECC_BYTE_ERR时，这些位显示ECC字节的错误位数。。*/
#define SPI_MEM_ECC_CHK_ERR_BIT    0x00000007
#define SPI_MEM_ECC_CHK_ERR_BIT_M  ((SPI_MEM_ECC_CHK_ERR_BIT_V)<<(SPI_MEM_ECC_CHK_ERR_BIT_S))
#define SPI_MEM_ECC_CHK_ERR_BIT_V  0x7
#define SPI_MEM_ECC_CHK_ERR_BIT_S  13
/* SPI_MEM_ECC_DATA_ERR_BIT:R/SS/WTC；比特位置：[12:6]；默认值：7'd0；*/
/*description:设置SPI_FMEM_ECC_ERR_INT_EN/SPI_SMEM_ECC-ERR_INT_EN并访问flash/Ext_RAM时，记录第一个ECC数据错误位号。该值的范围为0~127，对应于16个数据字节中的位数。它由SPI_MEM_ECC_ERR_INT_CLR位清除。。*/
#define SPI_MEM_ECC_DATA_ERR_BIT    0x0000007F
#define SPI_MEM_ECC_DATA_ERR_BIT_M  ((SPI_MEM_ECC_DATA_ERR_BIT_V)<<(SPI_MEM_ECC_DATA_ERR_BIT_S))
#define SPI_MEM_ECC_DATA_ERR_BIT_V  0x7F
#define SPI_MEM_ECC_DATA_ERR_BIT_S  6

#define SPI_MEM_SPI_SMEM_AC_REG(i)          (REG_SPI_MEM_BASE(i) + 0xDC)
/* SPI_MEM_SPI_SMEM_CS_HOLD_DELAY：R/W；位位置：[30:25]；默认值：6'd0；*/
/*描述：当访问外部RAM时，这些位用于设置SPI突发传输之间的最小CS高时间tSHSL。tSHSL是（SPI_SMEM_CS_HOLD_DELAY[5:0]+1）MSPI核心时钟周期。。*/
#define SPI_MEM_SPI_SMEM_CS_HOLD_DELAY    0x0000003F
#define SPI_MEM_SPI_SMEM_CS_HOLD_DELAY_M  ((SPI_MEM_SPI_SMEM_CS_HOLD_DELAY_V)<<(SPI_MEM_SPI_SMEM_CS_HOLD_DELAY_S))
#define SPI_MEM_SPI_SMEM_CS_HOLD_DELAY_V  0x3F
#define SPI_MEM_SPI_SMEM_CS_HOLD_DELAY_S  25
/* SPI_MEM_SPI_SMEM_ECC_ERR_INT_EN:R/W；位位置：[24]；默认值：1’b0；*/
/*description:设置此位以计算访问外部RAM时MSPI ECC读取的错误时间。。*/
#define SPI_MEM_SPI_SMEM_ECC_ERR_INT_EN    (BIT(24))
#define SPI_MEM_SPI_SMEM_ECC_ERR_INT_EN_M  (BIT(24))
#define SPI_MEM_SPI_SMEM_ECC_ERR_INT_EN_V  0x1
#define SPI_MEM_SPI_SMEM_ECC_ERR_INT_EN_S  24
/* SPI_MEM_SPI_SMEM_ECC_16TO18_BYTE_EN:R/W；位位置：[16]；默认值：1’b0；*/
/*描述：设置此位以在访问外部RAM时启用MSPI ECC 16字节数据和2 ECC字节模式。。*/
#define SPI_MEM_SPI_SMEM_ECC_16TO18_BYTE_EN    (BIT(16))
#define SPI_MEM_SPI_SMEM_ECC_16TO18_BYTE_EN_M  (BIT(16))
#define SPI_MEM_SPI_SMEM_ECC_16TO18_BYTE_EN_V  0x1
#define SPI_MEM_SPI_SMEM_ECC_16TO18_BYTE_EN_S  16
/* SPI_MEM_SPI_SMEM_ECC_SKIP_PAGE_CORNER:R/W；位位置：[15]；默认值：1’b1；*/
/*描述：1:MSPI在访问外部RAM时跳过页角。0：访问外部RAM时不跳过页角。。*/
#define SPI_MEM_SPI_SMEM_ECC_SKIP_PAGE_CORNER    (BIT(15))
#define SPI_MEM_SPI_SMEM_ECC_SKIP_PAGE_CORNER_M  (BIT(15))
#define SPI_MEM_SPI_SMEM_ECC_SKIP_PAGE_CORNER_V  0x1
#define SPI_MEM_SPI_SMEM_ECC_SKIP_PAGE_CORNER_S  15
/* SPI_MEM_SPI_SMEM_ECC_CS_HOLD_TIME:R/W；比特位置：[14:12]；默认值：3'd3；*/
/*描述：SPI_SMEM_CS_HOLD_TIME+SPI_SMEM_ECC_CS_HOLD _TIME是访问外部RAM时ECC模式下的MSPI CS保持周期。。*/
#define SPI_MEM_SPI_SMEM_ECC_CS_HOLD_TIME    0x00000007
#define SPI_MEM_SPI_SMEM_ECC_CS_HOLD_TIME_M  ((SPI_MEM_SPI_SMEM_ECC_CS_HOLD_TIME_V)<<(SPI_MEM_SPI_SMEM_ECC_CS_HOLD_TIME_S))
#define SPI_MEM_SPI_SMEM_ECC_CS_HOLD_TIME_V  0x7
#define SPI_MEM_SPI_SMEM_ECC_CS_HOLD_TIME_S  12
/* SPI_MEM_SPI_SMEM_CS_HOLD_TIME:R/W；比特位置：[11:7]；默认值：5'h1；*/
/*描述：SPI总线CS（SPI_CS）信号被SPI总线时钟（SPI_CLK）延迟到非活动状态，这是非ECC模式下的SPI_CS保持时间。这些位与SPI_MEM_CS_HOLD位组合。。*/
#define SPI_MEM_SPI_SMEM_CS_HOLD_TIME    0x0000001F
#define SPI_MEM_SPI_SMEM_CS_HOLD_TIME_M  ((SPI_MEM_SPI_SMEM_CS_HOLD_TIME_V)<<(SPI_MEM_SPI_SMEM_CS_HOLD_TIME_S))
#define SPI_MEM_SPI_SMEM_CS_HOLD_TIME_V  0x1F
#define SPI_MEM_SPI_SMEM_CS_HOLD_TIME_S  7
/* SPI_MEM_SPI_SMEM_CS_SETUP_TIME:R/W；位位置：[6:2]；默认值：5'h1；*/
/*description:通过SPI_CLK（即SPI_CS设置时间）执行PREP阶段的（周期-1）。这些位与SPI_MEM_CS_SETUP位组合。。*/
#define SPI_MEM_SPI_SMEM_CS_SETUP_TIME    0x0000001F
#define SPI_MEM_SPI_SMEM_CS_SETUP_TIME_M  ((SPI_MEM_SPI_SMEM_CS_SETUP_TIME_V)<<(SPI_MEM_SPI_SMEM_CS_SETUP_TIME_S))
#define SPI_MEM_SPI_SMEM_CS_SETUP_TIME_V  0x1F
#define SPI_MEM_SPI_SMEM_CS_SETUP_TIME_S  2
/* SPI_MEM_SPI_SMEM_CS_HOLD:R/W；位位置：[1]；默认值：1’b0；*/
/*description:当MSPI处于DONE状态时，设置此位以保持SPI_CS为低。。*/
#define SPI_MEM_SPI_SMEM_CS_HOLD    (BIT(1))
#define SPI_MEM_SPI_SMEM_CS_HOLD_M  (BIT(1))
#define SPI_MEM_SPI_SMEM_CS_HOLD_V  0x1
#define SPI_MEM_SPI_SMEM_CS_HOLD_S  1
/* SPI_MEM_SPI_SMEM_CS_SETUP:R/W；位位置：[0]；默认值：1’b0；*/
/*description:当MSPI处于PREP状态时，设置此位以保持SPI_CS为低。。*/
#define SPI_MEM_SPI_SMEM_CS_SETUP    (BIT(0))
#define SPI_MEM_SPI_SMEM_CS_SETUP_M  (BIT(0))
#define SPI_MEM_SPI_SMEM_CS_SETUP_V  0x1
#define SPI_MEM_SPI_SMEM_CS_SETUP_S  0

#define SPI_MEM_DDR_REG(i)          (REG_SPI_MEM_BASE(i) + 0xE0)
/* SPI_MEM_SPI_FMEM_HYPERBUS_CA:R/W；位位置：[30]；默认值：1’b0；*/
/*description:设置此位以在访问闪存时启用HyperRAM地址输出，这意味着addr_out[31:0]=｛spi_usr_addr_value[19:4]，13'd0，spi_usr_addr_value[3:1]｝。。*/
#define SPI_MEM_SPI_FMEM_HYPERBUS_CA    (BIT(30))
#define SPI_MEM_SPI_FMEM_HYPERBUS_CA_M  (BIT(30))
#define SPI_MEM_SPI_FMEM_HYPERBUS_CA_V  0x1
#define SPI_MEM_SPI_FMEM_HYPERBUS_CA_S  30
/* SPI_MEM_SPI_FMEM_OCTA_RAM_ADDR:R/W；位位置：[29]；默认值：1’b0；*/
/*description: 设置此位以在访问闪存时启用octa_ram地址输出，这意味着addr_out[31:0]={spi_usr_addr_value[25:4]，6'd0，spi_usr_addr_value[3:1]，1'b0}
..*/
#define SPI_MEM_SPI_FMEM_OCTA_RAM_ADDR    (BIT(29))
#define SPI_MEM_SPI_FMEM_OCTA_RAM_ADDR_M  (BIT(29))
#define SPI_MEM_SPI_FMEM_OCTA_RAM_ADDR_V  0x1
#define SPI_MEM_SPI_FMEM_OCTA_RAM_ADDR_S  29
/* SPI_MEM_SPI_FMEM_CLK_DIFF_INV:R/W；位位置：[28]；默认值：1’b0；*/
/*description:设置此位以在访问闪存时反转SPI_DIFF。。*/
#define SPI_MEM_SPI_FMEM_CLK_DIFF_INV    (BIT(28))
#define SPI_MEM_SPI_FMEM_CLK_DIFF_INV_M  (BIT(28))
#define SPI_MEM_SPI_FMEM_CLK_DIFF_INV_V  0x1
#define SPI_MEM_SPI_FMEM_CLK_DIFF_INV_S  28
/* SPI_MEM_SPI_FMEM_HYPERBUS_DUMMY_2X:R/W；位位置：[27]；默认值：1’b0；*/
/*description:当SPI0访问闪存或SPI1访问闪存或sram时，设置此位以启用SPI超级总线模式下的可变虚拟功能。。*/
#define SPI_MEM_SPI_FMEM_HYPERBUS_DUMMY_2X    (BIT(27))
#define SPI_MEM_SPI_FMEM_HYPERBUS_DUMMY_2X_M  (BIT(27))
#define SPI_MEM_SPI_FMEM_HYPERBUS_DUMMY_2X_V  0x1
#define SPI_MEM_SPI_FMEM_HYPERBUS_DUMMY_2X_S  27
/* SPI_MEM_SPI_FMEM_DQS_CA_IN:R/W；位位置：[26]；默认值：1’b0；*/
/*description: 设置此位以启用CMD和ADDR的SPI相位中的SPI_DQS信号输入
..*/
#define SPI_MEM_SPI_FMEM_DQS_CA_IN    (BIT(26))
#define SPI_MEM_SPI_FMEM_DQS_CA_IN_M  (BIT(26))
#define SPI_MEM_SPI_FMEM_DQS_CA_IN_V  0x1
#define SPI_MEM_SPI_FMEM_DQS_CA_IN_S  26
/* SPI_MEM_SPI_FMEM_HYPERBUS_MODE：R/W；位位置：[25]；默认值：1’b0；*/
/*description:设置此位以启用SPI超级总线模式。。*/
#define SPI_MEM_SPI_FMEM_HYPERBUS_MODE    (BIT(25))
#define SPI_MEM_SPI_FMEM_HYPERBUS_MODE_M  (BIT(25))
#define SPI_MEM_SPI_FMEM_HYPERBUS_MODE_V  0x1
#define SPI_MEM_SPI_FMEM_HYPERBUS_MODE_S  25
/* SPI_MEM_SPI_FMEM_CLK_DIFF_EN:R/W；位位置：[24]；默认值：1’b0；*/
/*description:设置此位以启用差分SPI_CLK#。。*/
#define SPI_MEM_SPI_FMEM_CLK_DIFF_EN    (BIT(24))
#define SPI_MEM_SPI_FMEM_CLK_DIFF_EN_M  (BIT(24))
#define SPI_MEM_SPI_FMEM_CLK_DIFF_EN_V  0x1
#define SPI_MEM_SPI_FMEM_CLK_DIFF_EN_S  24
/* SPI_MEM_SPI_FMEM_DDR_DQS_LOOP_MODE：R/W；位位置：[22]；默认值：1’b0；*/
/*description:设置SPI_FMEM_DDR_DQS_LOOP和SPI_FMEM-DDR_EN时，1：使用内部SPI_CLK作为数据选通。0：使用内部~SPI_CLK作为数据选通。否则，此位无效。。*/
#define SPI_MEM_SPI_FMEM_DDR_DQS_LOOP_MODE    (BIT(22))
#define SPI_MEM_SPI_FMEM_DDR_DQS_LOOP_MODE_M  (BIT(22))
#define SPI_MEM_SPI_FMEM_DDR_DQS_LOOP_MODE_V  0x1
#define SPI_MEM_SPI_FMEM_DDR_DQS_LOOP_MODE_S  22
/* SPI_MEM_SPI_FMEM_DDR_DQS_LOOP:R/W；位位置：[21]；默认值：1’b0；*/
/*描述：1：使用内部信号作为数据选通，选通不能被输入定时模块延迟。0：使用来自PAD的输入SPI_DQS信号作为数据选通，选通可由输入定时模块延迟。*/
#define SPI_MEM_SPI_FMEM_DDR_DQS_LOOP    (BIT(21))
#define SPI_MEM_SPI_FMEM_DDR_DQS_LOOP_M  (BIT(21))
#define SPI_MEM_SPI_FMEM_DDR_DQS_LOOP_V  0x1
#define SPI_MEM_SPI_FMEM_DDR_DQS_LOOP_S  21
/* SPI_MEM_SPI_FMEM_USR_DDR_DQS_THD:R/W；比特位置：[20:14]；默认值：7'b0；*/
/*description:基于SPI_CLK的内存数据选通的延迟数。。*/
#define SPI_MEM_SPI_FMEM_USR_DDR_DQS_THD    0x0000007F
#define SPI_MEM_SPI_FMEM_USR_DDR_DQS_THD_M  ((SPI_MEM_SPI_FMEM_USR_DDR_DQS_THD_V)<<(SPI_MEM_SPI_FMEM_USR_DDR_DQS_THD_S))
#define SPI_MEM_SPI_FMEM_USR_DDR_DQS_THD_V  0x7F
#define SPI_MEM_SPI_FMEM_USR_DDR_DQS_THD_S  14
/* SPI_MEM_SPI_FMEM_RX_DDR_MSK_EN:R/W；位位置：[13]；默认值：1'h1；*/
/*description:当访问闪存时，设置此位以屏蔽MSPI ECC DDR读取模式中的第一个或最后一个字节。。*/
#define SPI_MEM_SPI_FMEM_RX_DDR_MSK_EN    (BIT(13))
#define SPI_MEM_SPI_FMEM_RX_DDR_MSK_EN_M  (BIT(13))
#define SPI_MEM_SPI_FMEM_RX_DDR_MSK_EN_V  0x1
#define SPI_MEM_SPI_FMEM_RX_DDR_MSK_EN_S  13
/* SPI_MEM_SPI_FMEM_TX_DDR_MSK_EN:R/W；位位置：[12]；默认值：1'h1；*/
/*description:当访问闪存时，设置此位以屏蔽MSPI ECC DDR写入模式中的第一个或最后一个字节。。*/
#define SPI_MEM_SPI_FMEM_TX_DDR_MSK_EN    (BIT(12))
#define SPI_MEM_SPI_FMEM_TX_DDR_MSK_EN_M  (BIT(12))
#define SPI_MEM_SPI_FMEM_TX_DDR_MSK_EN_V  0x1
#define SPI_MEM_SPI_FMEM_TX_DDR_MSK_EN_S  12
/* SPI_MEM_SPI_FMEM_outmin字节：R/W；位位置：[11:5]；默认值：7'b1；*/
/*description:这是panda设备中的最小输出数据长度。。*/
#define SPI_MEM_SPI_FMEM_OUTMINBYTELEN    0x0000007F
#define SPI_MEM_SPI_FMEM_OUTMINBYTELEN_M  ((SPI_MEM_SPI_FMEM_OUTMINBYTELEN_V)<<(SPI_MEM_SPI_FMEM_OUTMINBYTELEN_S))
#define SPI_MEM_SPI_FMEM_OUTMINBYTELEN_V  0x7F
#define SPI_MEM_SPI_FMEM_OUTMINBYTELEN_S  5
/* SPI_MEM_SPI_FMEM_DDR_CMD_DIS:R/W；位位置：[4]；默认值：1’b0；*/
/*描述：当DDR模式时，该位用于在命令阶段禁用双边缘。。*/
#define SPI_MEM_SPI_FMEM_DDR_CMD_DIS    (BIT(4))
#define SPI_MEM_SPI_FMEM_DDR_CMD_DIS_M  (BIT(4))
#define SPI_MEM_SPI_FMEM_DDR_CMD_DIS_V  0x1
#define SPI_MEM_SPI_FMEM_DDR_CMD_DIS_S  4
/* SPI_MEM_SPI_FMEM_DDR_WDAT_SWP:R/W；位位置：[3]；默认值：1’b0；*/
/*description:在DDR模式下设置该位以重新排序该字的TX数据。。*/
#define SPI_MEM_SPI_FMEM_DDR_WDAT_SWP    (BIT(3))
#define SPI_MEM_SPI_FMEM_DDR_WDAT_SWP_M  (BIT(3))
#define SPI_MEM_SPI_FMEM_DDR_WDAT_SWP_V  0x1
#define SPI_MEM_SPI_FMEM_DDR_WDAT_SWP_S  3
/* SPI_MEM_SPI_FMEM_DDR_RDAT_SWP:R/W；位位置：[2]；默认值：1’b0；*/
/*description:设置位以重新排序DDR模式下的字的RX数据。。*/
#define SPI_MEM_SPI_FMEM_DDR_RDAT_SWP    (BIT(2))
#define SPI_MEM_SPI_FMEM_DDR_RDAT_SWP_M  (BIT(2))
#define SPI_MEM_SPI_FMEM_DDR_RDAT_SWP_V  0x1
#define SPI_MEM_SPI_FMEM_DDR_RDAT_SWP_S  2
/* SPI_MEM_SPI_FMEM_VAR_DUMMY:R/W；位位置：[1]；默认值：1’b0；*/
/*description:设置位以启用DDRmode中的可变虚拟周期。。*/
#define SPI_MEM_SPI_FMEM_VAR_DUMMY    (BIT(1))
#define SPI_MEM_SPI_FMEM_VAR_DUMMY_M  (BIT(1))
#define SPI_MEM_SPI_FMEM_VAR_DUMMY_V  0x1
#define SPI_MEM_SPI_FMEM_VAR_DUMMY_S  1
/* SPI_MEM_SPI_FMEM_DDR_EN:R/W；位位置：[0]；默认值：1’b0；*/
/*description:1:在DDR模式下，0:在SDR模式下。。*/
#define SPI_MEM_SPI_FMEM_DDR_EN    (BIT(0))
#define SPI_MEM_SPI_FMEM_DDR_EN_M  (BIT(0))
#define SPI_MEM_SPI_FMEM_DDR_EN_V  0x1
#define SPI_MEM_SPI_FMEM_DDR_EN_S  0

#define SPI_MEM_SPI_SMEM_DDR_REG(i)          (REG_SPI_MEM_BASE(i) + 0xE4)
/* SPI_MEM_SPI_SMEM_HYPERBUS_CA:R/W；位位置：[30]；默认值：1’b0；*/
/*description: 设置此位以在访问外部RAM时启用HyperRAM地址输出，这意味着ADDR_out[31:0]={spi_usr_ADDR_value[19:4]，13'd0，spi_usr_ADDR_value[3:1
]}..*/
#define SPI_MEM_SPI_SMEM_HYPERBUS_CA    (BIT(30))
#define SPI_MEM_SPI_SMEM_HYPERBUS_CA_M  (BIT(30))
#define SPI_MEM_SPI_SMEM_HYPERBUS_CA_V  0x1
#define SPI_MEM_SPI_SMEM_HYPERBUS_CA_S  30
/* SPI_MEM_SPI_SMEM_OCTA_RAM_ADDR:R/W；位位置：[29]；默认值：1’b0；*/
/*description:设置此位以在访问外部ram时启用octa_ram地址输出，这意味着ADDR_out[31:0]={spi_usr_ADDR_value[25:4]，6'd0，spi_usr_ADDR_value[3:1]，1'b0}。。*/
#define SPI_MEM_SPI_SMEM_OCTA_RAM_ADDR    (BIT(29))
#define SPI_MEM_SPI_SMEM_OCTA_RAM_ADDR_M  (BIT(29))
#define SPI_MEM_SPI_SMEM_OCTA_RAM_ADDR_V  0x1
#define SPI_MEM_SPI_SMEM_OCTA_RAM_ADDR_S  29
/* SPI_MEM_SPI_SMEM_CLK_DIFF_INV:R/W；位位置：[28]；默认值：1’b0；*/
/*description:设置此位以在访问外部RAM时反转SPI_DIFF。。*/
#define SPI_MEM_SPI_SMEM_CLK_DIFF_INV    (BIT(28))
#define SPI_MEM_SPI_SMEM_CLK_DIFF_INV_M  (BIT(28))
#define SPI_MEM_SPI_SMEM_CLK_DIFF_INV_V  0x1
#define SPI_MEM_SPI_SMEM_CLK_DIFF_INV_S  28
/* SPI_MEM_SPI_SMEM_HYPERBUS_DUMMY_2X:R/W；位位置：[27]；默认值：1’b0；*/
/*description:当SPI0访问闪存或SPI1访问闪存或sram时，设置此位以启用SPI超级总线模式下的可变虚拟功能。。*/
#define SPI_MEM_SPI_SMEM_HYPERBUS_DUMMY_2X    (BIT(27))
#define SPI_MEM_SPI_SMEM_HYPERBUS_DUMMY_2X_M  (BIT(27))
#define SPI_MEM_SPI_SMEM_HYPERBUS_DUMMY_2X_V  0x1
#define SPI_MEM_SPI_SMEM_HYPERBUS_DUMMY_2X_S  27
/* SPI_MEM_SPI_SMEM_DQS_CA_IN:R/W；位位置：[26]；默认值：1’b0；*/
/*description: 设置此位以启用CMD和ADDR的SPI相位中的SPI_DQS信号输入
..*/
#define SPI_MEM_SPI_SMEM_DQS_CA_IN    (BIT(26))
#define SPI_MEM_SPI_SMEM_DQS_CA_IN_M  (BIT(26))
#define SPI_MEM_SPI_SMEM_DQS_CA_IN_V  0x1
#define SPI_MEM_SPI_SMEM_DQS_CA_IN_S  26
/* SPI_MEM_SPI_SMEM_HYPERBUS_MODE：R/W；位位置：[25]；默认值：1’b0；*/
/*description:设置此位以启用SPI超级总线模式。。*/
#define SPI_MEM_SPI_SMEM_HYPERBUS_MODE    (BIT(25))
#define SPI_MEM_SPI_SMEM_HYPERBUS_MODE_M  (BIT(25))
#define SPI_MEM_SPI_SMEM_HYPERBUS_MODE_V  0x1
#define SPI_MEM_SPI_SMEM_HYPERBUS_MODE_S  25
/* SPI_MEM_SPI_SMEM_CLK_DIFF_EN:R/W；位位置：[24]；默认值：1’b0；*/
/*description:设置此位以启用差分SPI_CLK#。。*/
#define SPI_MEM_SPI_SMEM_CLK_DIFF_EN    (BIT(24))
#define SPI_MEM_SPI_SMEM_CLK_DIFF_EN_M  (BIT(24))
#define SPI_MEM_SPI_SMEM_CLK_DIFF_EN_V  0x1
#define SPI_MEM_SPI_SMEM_CLK_DIFF_EN_S  24
/* SPI_MEM_SPI_SMEM_DDR_DQS_LOOP_MODE：R/W；位位置：[22]；默认值：1’b0；*/
/*description:设置SPI_SMEM_DDR_DQS_LOOP和SPI_SMEM-DDR_EN时，1：使用内部SPI_CLK作为数据选通。0：使用内部~SPI_CLK作为数据选通。否则，此位无效。。*/
#define SPI_MEM_SPI_SMEM_DDR_DQS_LOOP_MODE    (BIT(22))
#define SPI_MEM_SPI_SMEM_DDR_DQS_LOOP_MODE_M  (BIT(22))
#define SPI_MEM_SPI_SMEM_DDR_DQS_LOOP_MODE_V  0x1
#define SPI_MEM_SPI_SMEM_DDR_DQS_LOOP_MODE_S  22
/* SPI_MEM_SPI_SMEM_DDR_DQS_LOOP:R/W；位位置：[21]；默认值：1’b0；*/
/*描述：1：使用内部信号作为数据选通，选通不能被输入定时模块延迟。0：使用来自PAD的输入SPI_DQS信号作为数据选通，选通可由输入定时模块延迟。*/
#define SPI_MEM_SPI_SMEM_DDR_DQS_LOOP    (BIT(21))
#define SPI_MEM_SPI_SMEM_DDR_DQS_LOOP_M  (BIT(21))
#define SPI_MEM_SPI_SMEM_DDR_DQS_LOOP_V  0x1
#define SPI_MEM_SPI_SMEM_DDR_DQS_LOOP_S  21
/* SPI_MEM_SPI_SMEM_USR_DDR_DQS_THD:R/W；比特位置：[20:14]；默认值：7'b0；*/
/*description:基于SPI_CLK的内存数据选通的延迟数。。*/
#define SPI_MEM_SPI_SMEM_USR_DDR_DQS_THD    0x0000007F
#define SPI_MEM_SPI_SMEM_USR_DDR_DQS_THD_M  ((SPI_MEM_SPI_SMEM_USR_DDR_DQS_THD_V)<<(SPI_MEM_SPI_SMEM_USR_DDR_DQS_THD_S))
#define SPI_MEM_SPI_SMEM_USR_DDR_DQS_THD_V  0x7F
#define SPI_MEM_SPI_SMEM_USR_DDR_DQS_THD_S  14
/* SPI_MEM_SPI_SMEM_RX_DDR_MSK_EN:R/W；位位置：[13]；默认值：1'h1；*/
/*description:当访问外部RAM时，设置此位以屏蔽MSPI ECC DDR读取模式中的第一个或最后一个字节。。*/
#define SPI_MEM_SPI_SMEM_RX_DDR_MSK_EN    (BIT(13))
#define SPI_MEM_SPI_SMEM_RX_DDR_MSK_EN_M  (BIT(13))
#define SPI_MEM_SPI_SMEM_RX_DDR_MSK_EN_V  0x1
#define SPI_MEM_SPI_SMEM_RX_DDR_MSK_EN_S  13
/* SPI_MEM_SPI_SMEM_TX_DDR_MSK_EN:R/W；位位置：[12]；默认值：1'h1；*/
/*description:当访问外部RAM时，设置此位以屏蔽MSPI ECC DDR写入模式中的第一个或最后一个字节。。*/
#define SPI_MEM_SPI_SMEM_TX_DDR_MSK_EN    (BIT(12))
#define SPI_MEM_SPI_SMEM_TX_DDR_MSK_EN_M  (BIT(12))
#define SPI_MEM_SPI_SMEM_TX_DDR_MSK_EN_V  0x1
#define SPI_MEM_SPI_SMEM_TX_DDR_MSK_EN_S  12
/* SPI_MEM_SPI_SMEM_outmin字节：R/W；位位置：[11:5]；默认值：7'b1；*/
/*description:这是ddr-psram中的最小输出数据长度。。*/
#define SPI_MEM_SPI_SMEM_OUTMINBYTELEN    0x0000007F
#define SPI_MEM_SPI_SMEM_OUTMINBYTELEN_M  ((SPI_MEM_SPI_SMEM_OUTMINBYTELEN_V)<<(SPI_MEM_SPI_SMEM_OUTMINBYTELEN_S))
#define SPI_MEM_SPI_SMEM_OUTMINBYTELEN_V  0x7F
#define SPI_MEM_SPI_SMEM_OUTMINBYTELEN_S  5
/* SPI_MEM_SPI_SMEM_DDR_CMD_DIS:R/W；位位置：[4]；默认值：1’b0；*/
/*描述：当ddr模式时，该位用于禁用CMD阶段的双边缘。。*/
#define SPI_MEM_SPI_SMEM_DDR_CMD_DIS    (BIT(4))
#define SPI_MEM_SPI_SMEM_DDR_CMD_DIS_M  (BIT(4))
#define SPI_MEM_SPI_SMEM_DDR_CMD_DIS_V  0x1
#define SPI_MEM_SPI_SMEM_DDR_CMD_DIS_S  4
/* SPI_MEM_SPI_SMEM_DDR_WDAT_SWP:R/W；位位置：[3]；默认值：1’b0；*/
/*description:设置位以重新排序spi-ddr模式下单词的tx数据。。*/
#define SPI_MEM_SPI_SMEM_DDR_WDAT_SWP    (BIT(3))
#define SPI_MEM_SPI_SMEM_DDR_WDAT_SWP_M  (BIT(3))
#define SPI_MEM_SPI_SMEM_DDR_WDAT_SWP_V  0x1
#define SPI_MEM_SPI_SMEM_DDR_WDAT_SWP_S  3
/* SPI_MEM_SPI_SMEM_DDR_RDAT_SWP:R/W；位位置：[2]；默认值：1’b0；*/
/*description:设置位以重新排序spi-ddr模式下单词的rx数据。。*/
#define SPI_MEM_SPI_SMEM_DDR_RDAT_SWP    (BIT(2))
#define SPI_MEM_SPI_SMEM_DDR_RDAT_SWP_M  (BIT(2))
#define SPI_MEM_SPI_SMEM_DDR_RDAT_SWP_V  0x1
#define SPI_MEM_SPI_SMEM_DDR_RDAT_SWP_S  2
/* SPI_MEM_SPI_SMEM_VAR_DUMMY:R/W；位位置：[1]；默认值：1’b0；*/
/*description:设置位以启用spi-ddr模式下的可变虚拟周期。。*/
#define SPI_MEM_SPI_SMEM_VAR_DUMMY    (BIT(1))
#define SPI_MEM_SPI_SMEM_VAR_DUMMY_M  (BIT(1))
#define SPI_MEM_SPI_SMEM_VAR_DUMMY_V  0x1
#define SPI_MEM_SPI_SMEM_VAR_DUMMY_S  1
/* SPI_MEM_SPI_SMEM_DDR_EN:R/W；位位置：[0]；默认值：1’b0；*/
/*描述：1：在ddr模式下，0在sdr模式下。*/
#define SPI_MEM_SPI_SMEM_DDR_EN    (BIT(0))
#define SPI_MEM_SPI_SMEM_DDR_EN_M  (BIT(0))
#define SPI_MEM_SPI_SMEM_DDR_EN_V  0x1
#define SPI_MEM_SPI_SMEM_DDR_EN_S  0

#define SPI_MEM_CLOCK_GATE_REG(i)          (REG_SPI_MEM_BASE(i) + 0xE8)
/* SPI_MEM_CLK_EN:R/W；位位置：[0]；默认值：1’b1；*/
/*description:寄存器时钟门使能信号。1： 启用。0:禁用。。*/
#define SPI_MEM_CLK_EN    (BIT(0))
#define SPI_MEM_CLK_EN_M  (BIT(0))
#define SPI_MEM_CLK_EN_V  0x1
#define SPI_MEM_CLK_EN_S  0

#define SPI_MEM_CORE_CLK_SEL_REG(i)          (REG_SPI_MEM_BASE(i) + 0xEC)
/* SPI_MEM_CORE_CLK_SEL:R/W；位位置：[1:0]；默认值：2'd0；*/
/*描述：当数字系统时钟选择PLL时钟且PLL时钟频率为480MHz时，SPI_MEM_CORE_CLK_SEL:0:SPI0/1模块时钟（MSPI_CORE_CLK）的值为80MHz。1： MSPI_CORE_CLK为120MHz。2： MSPI_CORE_CLK为160MHz。3： MSPI_CORE_CLK为240MHz。当数字系统时钟选择PLL时钟且PLL时钟的频率为320MHz时，SPI_MEM_CORE_CLK_SEL:0:MSPI_CORE_CLK的值为80MHz。1： MSPI_CORE_CLK为80MHz。2： MSPI_CORE_CLK 160MHz。3： 未使用。*/
#define SPI_MEM_CORE_CLK_SEL    0x00000003
#define SPI_MEM_CORE_CLK_SEL_M  ((SPI_MEM_CORE_CLK_SEL_V)<<(SPI_MEM_CORE_CLK_SEL_S))
#define SPI_MEM_CORE_CLK_SEL_V  0x3
#define SPI_MEM_CORE_CLK_SEL_S  0

#define SPI_MEM_INT_ENA_REG(i)          (REG_SPI_MEM_BASE(i) + 0xF0)
/* SPI_MEM_ECC_ERR_INT_ENA:R/W；位位置：[4]；默认值：1’b0；*/
/*description:SPI_MEM_ECC_ERR_INT中断的启用位。。*/
#define SPI_MEM_ECC_ERR_INT_ENA    (BIT(4))
#define SPI_MEM_ECC_ERR_INT_ENA_M  (BIT(4))
#define SPI_MEM_ECC_ERR_INT_ENA_V  0x1
#define SPI_MEM_ECC_ERR_INT_ENA_S  4
/* SPI_MEM_BROWN_OUT_INT_ENA：R/W；位位置：[3]；默认值：1’b0；*/
/*description:SPI_MEM_BROWN_OUT_INT中断的启用位。。*/
#define SPI_MEM_BROWN_OUT_INT_ENA    (BIT(3))
#define SPI_MEM_BROWN_OUT_INT_ENA_M  (BIT(3))
#define SPI_MEM_BROWN_OUT_INT_ENA_V  0x1
#define SPI_MEM_BROWN_OUT_INT_ENA_S  3
/* SPI_MEM_TOTAL_TRANS_END_INT_ENA:R/W；位位置：[2]；默认值：1’b0；*/
/*description:SPI_MEM_TOTAL_TRANS_END_INT中断的启用位。。*/
#define SPI_MEM_TOTAL_TRANS_END_INT_ENA    (BIT(2))
#define SPI_MEM_TOTAL_TRANS_END_INT_ENA_M  (BIT(2))
#define SPI_MEM_TOTAL_TRANS_END_INT_ENA_V  0x1
#define SPI_MEM_TOTAL_TRANS_END_INT_ENA_S  2
/* SPI_MEM_PES_END_INT_ENA:R/W；位位置：[1]；默认值：1’b0；*/
/*description:SPI_MEM_PES_END_INT中断的启用位。。*/
#define SPI_MEM_PES_END_INT_ENA    (BIT(1))
#define SPI_MEM_PES_END_INT_ENA_M  (BIT(1))
#define SPI_MEM_PES_END_INT_ENA_V  0x1
#define SPI_MEM_PES_END_INT_ENA_S  1
/* SPI_MEM_PER_END_INT_ENA:R/W；位位置：[0]；默认值：1’b0；*/
/*description:SPI_MEM_PER_END_INT中断的启用位。。*/
#define SPI_MEM_PER_END_INT_ENA    (BIT(0))
#define SPI_MEM_PER_END_INT_ENA_M  (BIT(0))
#define SPI_MEM_PER_END_INT_ENA_V  0x1
#define SPI_MEM_PER_END_INT_ENA_S  0

#define SPI_MEM_INT_CLR_REG(i)          (REG_SPI_MEM_BASE(i) + 0xF4)
/* SPI_MEM_ECC_ERR_INT_CLR:WT；位位置：[4]；默认值：1’b0；*/
/*description:SPI_MEM_ECC_ERR_INT中断的清除位。SPI_MEM_ECC_ERR_ADDR和SPI_MEM-ECC_ERR_CNT将被该位的脉冲清除。。*/
#define SPI_MEM_ECC_ERR_INT_CLR    (BIT(4))
#define SPI_MEM_ECC_ERR_INT_CLR_M  (BIT(4))
#define SPI_MEM_ECC_ERR_INT_CLR_V  0x1
#define SPI_MEM_ECC_ERR_INT_CLR_S  4
/* SPI_MEM_BROWN_OUT_INT_CLR:WT；位位置：[3]；默认值：1’b0；*/
/*description:SPI_MEM_BROWN_OUT_INT中断的状态位。。*/
#define SPI_MEM_BROWN_OUT_INT_CLR    (BIT(3))
#define SPI_MEM_BROWN_OUT_INT_CLR_M  (BIT(3))
#define SPI_MEM_BROWN_OUT_INT_CLR_V  0x1
#define SPI_MEM_BROWN_OUT_INT_CLR_S  3
/* SPI_MEM_TOTAL_TRANS_END_INT_CLR:WT；位位置：[2]；默认值：1’b0；*/
/*description:SPI_MEM_TOTAL_TRANS_END_INT中断的清除位。。*/
#define SPI_MEM_TOTAL_TRANS_END_INT_CLR    (BIT(2))
#define SPI_MEM_TOTAL_TRANS_END_INT_CLR_M  (BIT(2))
#define SPI_MEM_TOTAL_TRANS_END_INT_CLR_V  0x1
#define SPI_MEM_TOTAL_TRANS_END_INT_CLR_S  2
/* SPI_MEM_PES_END_INT_CLR:WT；位位置：[1]；默认值：1’b0；*/
/*description:SPI_MEM_PES_END_INT中断的清除位。。*/
#define SPI_MEM_PES_END_INT_CLR    (BIT(1))
#define SPI_MEM_PES_END_INT_CLR_M  (BIT(1))
#define SPI_MEM_PES_END_INT_CLR_V  0x1
#define SPI_MEM_PES_END_INT_CLR_S  1
/* SPI_MEM_PER_END_INT_CLR:WT；位位置：[0]；默认值：1’b0；*/
/*description:SPI_MEM_PER_END_INT中断的清除位。。*/
#define SPI_MEM_PER_END_INT_CLR    (BIT(0))
#define SPI_MEM_PER_END_INT_CLR_M  (BIT(0))
#define SPI_MEM_PER_END_INT_CLR_V  0x1
#define SPI_MEM_PER_END_INT_CLR_S  0

#define SPI_MEM_INT_RAW_REG(i)          (REG_SPI_MEM_BASE(i) + 0xF8)
/* SPI_MEM_ECC_ERR_INT_RAW:R/WTC/SS；位位置：[4]；默认值：1’b0；*/
/*description:SPI_MEM_ECC_ERR_INT中断的原始位。当APB_CTRL_FECC_ERR_INT_EN被设置并且APB_CTRL_SECC_ERR_INT_EN被清除时，当SPI0/1 ECC读闪存的错误时间等于或大于APB_CTRL_ECC_ERR_INT_NUM时，触发此位。当APB_CTRL_FECC_ERR_INT_EN被清除并且APB_CTRL_SECC_ERR_INT_EN被设置时，当SPI0/1 ECC读取外部RAM的错误时间等于或大于APB_CTRL_ECC_ERR_INT_NUM时，该位被触发。当设置APB_CTRL_FECC_ERR_INT_EN和APB_CTRL_SECC_ERR_INT_EN时，当SPI0/1 ECC读取外部RAM和闪存的总错误时间等于或大于APB_CTRL_ECC_ERR_INT_NUM时，触发此位。当APB_CTRL_FECC_ERR_INT_EN和APB_CTRL_SECC_ERR_INT_EN被清除时，该位将不会被触发。。*/
#define SPI_MEM_ECC_ERR_INT_RAW    (BIT(4))
#define SPI_MEM_ECC_ERR_INT_RAW_M  (BIT(4))
#define SPI_MEM_ECC_ERR_INT_RAW_V  0x1
#define SPI_MEM_ECC_ERR_INT_RAW_S  4
/* SPI_MEM_BROWN_OUT_INT_RAW:R/WTC/SS；位位置：[3]；默认值：1’b0；*/
/*description:SPI_MEM_BROWN_OUT_INT中断的原始位。1： 触发条件是芯片断电，RTC模块向SPI1发出棕色关闭闪存请求。SPI1向闪存发出暂停命令后，触发此中断，MSPI返回空闲状态。0：其他。。*/
#define SPI_MEM_BROWN_OUT_INT_RAW    (BIT(3))
#define SPI_MEM_BROWN_OUT_INT_RAW_M  (BIT(3))
#define SPI_MEM_BROWN_OUT_INT_RAW_V  0x1
#define SPI_MEM_BROWN_OUT_INT_RAW_S  3
/* SPI_MEM_TOTAL_TRANS_END_INT_RAW:R/WTC/SS；位位置：[2]；默认值：1’b0；*/
/*description:SPI_MEM_TOTAL_TRANS_END_INT中断的原始位。1： SPI1传输完成且闪存已空闲时触发。当WRSR/PP/SE/BE/CE被发送并且PES/PER命令被发送时，当WRSR/PP/SE-BE/CE成功时，该位被设置。0：其他。。*/
#define SPI_MEM_TOTAL_TRANS_END_INT_RAW    (BIT(2))
#define SPI_MEM_TOTAL_TRANS_END_INT_RAW_M  (BIT(2))
#define SPI_MEM_TOTAL_TRANS_END_INT_RAW_V  0x1
#define SPI_MEM_TOTAL_TRANS_END_INT_RAW_S  2
/* SPI_MEM_PES_END_INT_RAW:R/WTC/SS；位位置：[1]；默认值：1’b0；*/
/*description:SPI_MEM_PES_END_INT中断的原始位。1： 发送自动暂停命令（0x75）并成功暂停闪存时触发。0：其他。。*/
#define SPI_MEM_PES_END_INT_RAW    (BIT(1))
#define SPI_MEM_PES_END_INT_RAW_M  (BIT(1))
#define SPI_MEM_PES_END_INT_RAW_V  0x1
#define SPI_MEM_PES_END_INT_RAW_S  1
/* SPI_MEM_PER_END_INT_RAW:R/WTC/SS；位位置：[0]；默认值：1’b0；*/
/*description:SPI_MEM_PER_END_INT中断的原始位。1： 发送自动恢复命令（0x7A）并成功恢复闪存时触发。0：其他。。*/
#define SPI_MEM_PER_END_INT_RAW    (BIT(0))
#define SPI_MEM_PER_END_INT_RAW_M  (BIT(0))
#define SPI_MEM_PER_END_INT_RAW_V  0x1
#define SPI_MEM_PER_END_INT_RAW_S  0

#define SPI_MEM_INT_ST_REG(i)          (REG_SPI_MEM_BASE(i) + 0xFC)
/* SPI_MEM_ECC_ERR_INT_ST:RO；位位置：[4]；默认值：1’b0；*/
/*description:SPI_MEM_ECC_ERR_INT中断的状态位。。*/
#define SPI_MEM_ECC_ERR_INT_ST    (BIT(4))
#define SPI_MEM_ECC_ERR_INT_ST_M  (BIT(4))
#define SPI_MEM_ECC_ERR_INT_ST_V  0x1
#define SPI_MEM_ECC_ERR_INT_ST_S  4
/* SPI_MEM_BROWN_OUT_INT_ST:RO；位位置：[3]；默认值：1’b0；*/
/*description:SPI_MEM_BROWN_OUT_INT中断的状态位。。*/
#define SPI_MEM_BROWN_OUT_INT_ST    (BIT(3))
#define SPI_MEM_BROWN_OUT_INT_ST_M  (BIT(3))
#define SPI_MEM_BROWN_OUT_INT_ST_V  0x1
#define SPI_MEM_BROWN_OUT_INT_ST_S  3
/* SPI_MEM_TOTAL_TRANS_END_INT_ST:RO；位位置：[2]；默认值：1’b0；*/
/*description:SPI_MEM_TOTAL_TRANS_END_INT中断的状态位。。*/
#define SPI_MEM_TOTAL_TRANS_END_INT_ST    (BIT(2))
#define SPI_MEM_TOTAL_TRANS_END_INT_ST_M  (BIT(2))
#define SPI_MEM_TOTAL_TRANS_END_INT_ST_V  0x1
#define SPI_MEM_TOTAL_TRANS_END_INT_ST_S  2
/* SPI_MEM_PES_END_INT_ST:RO；位位置：[1]；默认值：1’b0；*/
/*description:SPI_MEM_PES_END_INT中断的状态位。。*/
#define SPI_MEM_PES_END_INT_ST    (BIT(1))
#define SPI_MEM_PES_END_INT_ST_M  (BIT(1))
#define SPI_MEM_PES_END_INT_ST_V  0x1
#define SPI_MEM_PES_END_INT_ST_S  1
/* SPI_MEM_PER_END_INT_ST:RO；位位置：[0]；默认值：1’b0；*/
/*description:SPI_MEM_PER_END_INT中断的状态位。。*/
#define SPI_MEM_PER_END_INT_ST    (BIT(0))
#define SPI_MEM_PER_END_INT_ST_M  (BIT(0))
#define SPI_MEM_PER_END_INT_ST_V  0x1
#define SPI_MEM_PER_END_INT_ST_S  0

#define SPI_MEM_DATE_REG(i)          (REG_SPI_MEM_BASE(i) + 0x3FC)
/* SPI_MEM_DATE:R/W；位位置：[27:5]；默认值：23'h108082；*/
/*description:SPI寄存器版本。。*/
#define SPI_MEM_DATE    0x007FFFFF
#define SPI_MEM_DATE_M  ((SPI_MEM_DATE_V)<<(SPI_MEM_DATE_S))
#define SPI_MEM_DATE_V  0x7FFFFF
#define SPI_MEM_DATE_S  5
/* SPI_MEM_SPICLK_PAD_DRV_CTL_EN:R/W；位位置：[4]；默认值：1’b0；*/
/*description:SPI_CLK PAD驱动器控制信号。1： SPI_CLK PAD的驱动器由位SPI_FMEM_SPICLK_FUN_DRV[1:0]和SPI_SMEM_SPICLK_FUN_DRV[1:0]控制。0:SPI_CLK PAD的驱动器由SPICLK PAD的位IO_MUX_FUNC_DRV[1:0]控制。。*/
#define SPI_MEM_SPICLK_PAD_DRV_CTL_EN    (BIT(4))
#define SPI_MEM_SPICLK_PAD_DRV_CTL_EN_M  (BIT(4))
#define SPI_MEM_SPICLK_PAD_DRV_CTL_EN_V  0x1
#define SPI_MEM_SPICLK_PAD_DRV_CTL_EN_S  4
/* SPI_MEM_SPI_FMEM_SPICLK_FUN_DRV:R/W；位位置：[3:2]；默认值：2’b0；*/
/*描述：当设置位SPI_SPICLK_PAD_DRV_CTL_EN并且MSPI访问闪存时，SPI_CLK PAD的驱动程序由位SPI_FMEM_SPICLK_FUN_DRV[1:0]控制。。*/
#define SPI_MEM_SPI_FMEM_SPICLK_FUN_DRV    0x00000003
#define SPI_MEM_SPI_FMEM_SPICLK_FUN_DRV_M  ((SPI_MEM_SPI_FMEM_SPICLK_FUN_DRV_V)<<(SPI_MEM_SPI_FMEM_SPICLK_FUN_DRV_S))
#define SPI_MEM_SPI_FMEM_SPICLK_FUN_DRV_V  0x3
#define SPI_MEM_SPI_FMEM_SPICLK_FUN_DRV_S  2
/* SPI_MEM_SPI_SMEM_SPICLK_FUN_DRV:R/W；位位置：[1:0]；默认值：2’b0；*/
/*描述：当设置位SPI_SPICLK_PAD_DRV_CTL_EN并且MSPI访问外部RAM时，SPI_CLK PAD的驱动程序由位SPI_SMEM_SPICLK_FUN_DRV[1:0]控制。。*/
#define SPI_MEM_SPI_SMEM_SPICLK_FUN_DRV    0x00000003
#define SPI_MEM_SPI_SMEM_SPICLK_FUN_DRV_M  ((SPI_MEM_SPI_SMEM_SPICLK_FUN_DRV_V)<<(SPI_MEM_SPI_SMEM_SPICLK_FUN_DRV_S))
#define SPI_MEM_SPI_SMEM_SPICLK_FUN_DRV_V  0x3
#define SPI_MEM_SPI_SMEM_SPICLK_FUN_DRV_S  0


#ifdef __cplusplus
}
#endif



#endif /*_SOC_SPI_MEM_REG_H_ */

