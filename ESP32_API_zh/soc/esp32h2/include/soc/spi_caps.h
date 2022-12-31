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

#pragma once

#define SOC_SPI_PERIPH_NUM      2
#define SOC_SPI_DMA_CHAN_NUM    3
#define SOC_SPI_PERIPH_CS_NUM(i)    3

#define SOC_SPI_MAXIMUM_BUFFER_SIZE     72

//#定义SOC_SPI_SUPPORT_AS_CS//不支持在时钟切换时切换CS
#define SOC_SPI_SUPPORT_DDRCLK              1
#define SOC_SPI_SLAVE_SUPPORT_SEG_TRANS     1
#define SOC_SPI_SUPPORT_CD_SIG              1
#define SOC_SPI_SUPPORT_CONTINUOUS_TRANS    1
#define SOC_SPI_SUPPORT_SLAVE_HD_VER2       1

// 外围设备支持DIO、DOUT、QIO或QOUT
#define SOC_SPI_PERIPH_SUPPORT_MULTILINE_MODE(host_id)          ((host_id) != 2)

// 外围设备在其“虚拟阶段”支持输出给定电平
#define SOC_SPI_PERIPH_SUPPORT_CONTROL_DUMMY_OUTPUT              1

#define SOC_MEMSPI_IS_INDEPENDENT 1

#define SOC_SPI_MAX_PRE_DIVIDER 16

