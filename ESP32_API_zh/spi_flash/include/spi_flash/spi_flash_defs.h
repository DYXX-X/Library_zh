// 版权所有2015-2019 Espressif Systems（上海）私人有限公司
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

#pragma once

/* SPI命令（实际在线命令而非SPI控制器位掩码）适用于SPI_flash_hal_common_commandstatic函数。
*/
#define CMD_RDID       0x9F
#define CMD_RDUID      0x4B   /* 读取闪存唯一ID*/
#define CMD_WRSR       0x01
#define  SR_WIP         (1<<0) /* 状态寄存器写入进行中位*/
#define  SR_WREN        (1<<1) /* 状态寄存器写入启用位*/
#define CMD_WRSR2      0x31 /* 并非所有SPI闪存都使用此命令*/
#define CMD_WREN       0x06
#define CMD_WRDI       0x04
#define CMD_RDSR       0x05
#define CMD_RDSR2      0x35 /* 并非所有SPI闪存都使用此命令*/
#define CMD_RDSCUR     0x2B /* 在特定（MXIC）板上，读取安全寄存器*/
#define CMD_RDFR       0x48 /* 在特定（ISSI）板上，读取功能寄存器*/

#define CMD_FASTRD_QIO      0xEB
#define CMD_FASTRD_QIO_4B   0xEC
#define CMD_FASTRD_QUAD     0x6B
#define CMD_FASTRD_QUAD_4B  0x6C
#define CMD_FASTRD_DIO      0xBB
#define CMD_FASTRD_DIO_4B   0xBC
#define CMD_FASTRD_DUAL     0x3B
#define CMD_FASTRD_DUAL_4B  0x3C
#define CMD_FASTRD          0x0B
#define CMD_FASTRD_4B       0x0C
#define CMD_READ            0x03 /* 速度受限*/
#define CMD_READ_4B         0x13 /* 速度受限*/

#define CMD_CHIP_ERASE          0xC7
#define CMD_SECTOR_ERASE        0x20
#define CMD_SECTOR_ERASE_4B     0x21
#define CMD_LARGE_BLOCK_ERASE   0xD8 /* 64KB块擦除命令*/
#define CMD_LARGE_BLOCK_ERASE_4B 0xDC /* 64KB块擦除命令*/
#define CMD_PROGRAM_PAGE        0x02
#define CMD_PROGRAM_PAGE_4B     0x12
#define CMD_SUSPEND             0x75
#define CMD_RESUME              0x7A

#define CMD_RST_EN      0x66
#define CMD_RST_DEV     0x99

#define SPI_FLASH_DIO_ADDR_BITLEN       24
#define SPI_FLASH_DIO_DUMMY_BITLEN      4
#define SPI_FLASH_QIO_ADDR_BITLEN       24
#define SPI_FLASH_QIO_DUMMY_BITLEN      6
#define SPI_FLASH_QOUT_ADDR_BITLEN      24
#define SPI_FLASH_QOUT_DUMMY_BITLEN     8
#define SPI_FLASH_DOUT_ADDR_BITLEN      24
#define SPI_FLASH_DOUT_DUMMY_BITLEN     8
#define SPI_FLASH_FASTRD_ADDR_BITLEN    24
#define SPI_FLASH_FASTRD_DUMMY_BITLEN   8
#define SPI_FLASH_SLOWRD_ADDR_BITLEN    24
#define SPI_FLASH_SLOWRD_DUMMY_BITLEN   0
#define SPI_FLASH_OPISTR_ADDR_BITLEN    32
#define SPI_FLASH_OPISTR_DUMMY_BITLEN   20
#define SPI_FLASH_OPIDTR_ADDR_BITLEN    32
#define SPI_FLASH_OPIDTR_DUMMY_BITLEN   40

