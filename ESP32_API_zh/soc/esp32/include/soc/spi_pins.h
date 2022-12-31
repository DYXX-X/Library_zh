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

#define SPI_FUNC_NUM            1
#define SPI_IOMUX_PIN_NUM_MISO  7
#define SPI_IOMUX_PIN_NUM_MOSI  8
#define SPI_IOMUX_PIN_NUM_CLK   6
#define SPI_IOMUX_PIN_NUM_CS    11
#define SPI_IOMUX_PIN_NUM_WP    10
#define SPI_IOMUX_PIN_NUM_HD    9

//用于D2WD和PICO-D4芯片
#define SPI_D2WD_PIN_NUM_MISO  17
#define SPI_D2WD_PIN_NUM_MOSI  8
#define SPI_D2WD_PIN_NUM_CLK   6
#define SPI_D2WD_PIN_NUM_CS    16
#define SPI_D2WD_PIN_NUM_WP    7
#define SPI_D2WD_PIN_NUM_HD    11

#define SPI2_FUNC_NUM           HSPI_FUNC_NUM
#define SPI2_IOMUX_PIN_NUM_MISO HSPI_IOMUX_PIN_NUM_MISO
#define SPI2_IOMUX_PIN_NUM_MOSI HSPI_IOMUX_PIN_NUM_MOSI
#define SPI2_IOMUX_PIN_NUM_CLK  HSPI_IOMUX_PIN_NUM_CLK
#define SPI2_IOMUX_PIN_NUM_CS   HSPI_IOMUX_PIN_NUM_CS
#define SPI2_IOMUX_PIN_NUM_WP   HSPI_IOMUX_PIN_NUM_WP
#define SPI2_IOMUX_PIN_NUM_HD   HSPI_IOMUX_PIN_NUM_HD

#define SPI3_FUNC_NUM           VSPI_FUNC_NUM
#define SPI3_IOMUX_PIN_NUM_MISO VSPI_IOMUX_PIN_NUM_MISO
#define SPI3_IOMUX_PIN_NUM_MOSI VSPI_IOMUX_PIN_NUM_MOSI
#define SPI3_IOMUX_PIN_NUM_CLK  VSPI_IOMUX_PIN_NUM_CLK
#define SPI3_IOMUX_PIN_NUM_CS   VSPI_IOMUX_PIN_NUM_CS
#define SPI3_IOMUX_PIN_NUM_WP   VSPI_IOMUX_PIN_NUM_WP
#define SPI3_IOMUX_PIN_NUM_HD   VSPI_IOMUX_PIN_NUM_HD

//以下宏已弃用。请使用上面的宏
#define HSPI_FUNC_NUM           1
#define HSPI_IOMUX_PIN_NUM_MISO 12
#define HSPI_IOMUX_PIN_NUM_MOSI 13
#define HSPI_IOMUX_PIN_NUM_CLK  14
#define HSPI_IOMUX_PIN_NUM_CS   15
#define HSPI_IOMUX_PIN_NUM_WP   2
#define HSPI_IOMUX_PIN_NUM_HD   4

#define VSPI_FUNC_NUM           1
#define VSPI_IOMUX_PIN_NUM_MISO 19
#define VSPI_IOMUX_PIN_NUM_MOSI 23
#define VSPI_IOMUX_PIN_NUM_CLK  18
#define VSPI_IOMUX_PIN_NUM_CS   5
#define VSPI_IOMUX_PIN_NUM_WP   22
#define VSPI_IOMUX_PIN_NUM_HD   21

