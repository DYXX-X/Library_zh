// 版权所有2015-2020 Espressif Systems（上海）私人有限公司
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

#pragma once

#define SPI_FUNC_NUM            0
#define SPI_IOMUX_PIN_NUM_HD    27
#define SPI_IOMUX_PIN_NUM_CS    29
#define SPI_IOMUX_PIN_NUM_MOSI  32
#define SPI_IOMUX_PIN_NUM_CLK   30
#define SPI_IOMUX_PIN_NUM_MISO  31
#define SPI_IOMUX_PIN_NUM_WP    28

// 有2组GPIO引脚，可路由至FSPICS0、FSPICLK、FSPID、FSPIQ、FSPIHD、FSPIWP。
// 然而，只有一组GPIO引脚可以路由到FSPIIO4、FSPIIO5、FSPIIO 6和FSPIIO7。
// 默认情况下（当我们不打算使用八进制SPI时），我们使用SPI2_FUNC_NUM将2组GPIO引脚中的一个路由到FSPICS0~FSPIWP，如下所示。
#define SPI2_FUNC_NUM           4
#define SPI2_IOMUX_PIN_NUM_HD   9
#define SPI2_IOMUX_PIN_NUM_CS   10
#define SPI2_IOMUX_PIN_NUM_MOSI 11
#define SPI2_IOMUX_PIN_NUM_CLK  12
#define SPI2_IOMUX_PIN_NUM_MISO 13
#define SPI2_IOMUX_PIN_NUM_WP   14

// 当使用八进制SPI时，我们使用SPI2_FUNC_NUM_OCT按如下方式路由它们。
#define SPI2_FUNC_NUM_OCT           2
#define SPI2_IOMUX_PIN_NUM_HD_OCT   33
#define SPI2_IOMUX_PIN_NUM_CS_OCT   34
#define SPI2_IOMUX_PIN_NUM_MOSI_OCT 35
#define SPI2_IOMUX_PIN_NUM_CLK_OCT  36
#define SPI2_IOMUX_PIN_NUM_MISO_OCT 37
#define SPI2_IOMUX_PIN_NUM_WP_OCT   38
#define SPI2_IOMUX_PIN_NUM_IO4_OCT  10
#define SPI2_IOMUX_PIN_NUM_IO5_OCT  11
#define SPI2_IOMUX_PIN_NUM_IO6_OCT  12
#define SPI2_IOMUX_PIN_NUM_IO7_OCT  13

//SPI3没有iomux引脚

