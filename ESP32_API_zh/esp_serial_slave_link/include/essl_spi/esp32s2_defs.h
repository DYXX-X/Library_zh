// 版权所有2010-2020 Espressif Systems（上海）私人有限公司
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

// 注：从主视图看
#define CMD_HD_WRBUF_REG    0x01
#define CMD_HD_RDBUF_REG    0x02
#define CMD_HD_WRDMA_REG    0x03
#define CMD_HD_RDDMA_REG    0x04

#define CMD_HD_ONEBIT_MODE  0x00
#define CMD_HD_DOUT_MODE    0x10
#define CMD_HD_QOUT_MODE    0x20
#define CMD_HD_DIO_MODE     0x50
#define CMD_HD_QIO_MODE     0xA0

#define CMD_HD_SEG_END_REG  0x05
#define CMD_HD_EN_QPI_REG   0x06
#define CMD_HD_WR_END_REG   0x07
#define CMD_HD_INT0_REG     0x08
#define CMD_HD_INT1_REG     0x09
#define CMD_HD_INT2_REG     0x0A
#define CMD_HD_EX_QPI_REG   0xDD

#define SPI_SLAVE_HD_BUFFER_SIZE 72

