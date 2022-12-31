// 版权所有2010-2016 Espressif Systems（上海）私人有限公司
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

#ifndef _SOC_BOOT_MODE_H_
#define _SOC_BOOT_MODE_H_

#include "soc.h"

/*SPI引导*/
#define IS_1XXXX(v)				(((v)&0x10)==0x10)

/*HSPI引导*/
#define IS_010XX(v)				(((v)&0x1c)==0x08)

/*下载引导，SDIO/UART0/UART1*/
#define IS_00XXX(v)				(((v)&0x18)==0x00)

/*下载引导，SDIO/UART0/UART1，FEI_FEO V2*/
#define IS_00X00(v)				(((v)&0x1b)==0x00)

/*下载引导，SDIO/UART0/UART1，FEI_REO V2*/
#define IS_00X01(v)				(((v)&0x1b)==0x01)

/*下载引导，SDIO/UART0/UART1，REI_FEO V2*/
#define IS_00X10(v)				(((v)&0x1b)==0x02)

/*下载引导，SDIO/UART0/UART1，REI_FEO V2*/
#define IS_00X11(v)				(((v)&0x1b)==0x03)

/*ATE/ANALOG模式*/
#define IS_01110(v)				(((v)&0x1f)==0x0e)

/*诊断模式+UART0下载模式*/
#define IS_01111(v)				(((v)&0x1f)==0x0f)

/*传统SPI引导*/
#define IS_01100(v)				(((v)&0x1f)==0x0c)

/*SDIO_从属下载模式V1.1*/
#define IS_01101(v)				(((v)&0x1f)==0x0d)



#define BOOT_MODE_GET()                                 (GPIO_REG_READ(GPIO_STRAP))

/*不包括下载模式*/
#define ETS_IS_UART_BOOT()				IS_01111(BOOT_MODE_GET())

/*所有spi引导，包括spi/hspi/legacy*/
#define ETS_IS_FLASH_BOOT()				(IS_1XXXX(BOOT_MODE_GET()) || IS_010XX(BOOT_MODE_GET()) || IS_01100(BOOT_MODE_GET()))

/*所有更快的spi引导，包括spi/hspi*/
#define ETS_IS_FAST_FLASH_BOOT()				(IS_1XXXX(BOOT_MODE_GET()) || IS_010XX(BOOT_MODE_GET()))

/*所有spi引导，包括spi/遗留*/
#define ETS_IS_SPI_FLASH_BOOT()				(IS_1XXXX(BOOT_MODE_GET()) || IS_01100(BOOT_MODE_GET()))

/*所有spi引导，包括hspi/legacy*/
#define ETS_IS_HSPI_FLASH_BOOT()				IS_010XX(BOOT_MODE_GET())

/*故障边缘输入、故障边缘输出的所有sdio V2*/
#define ETS_IS_SDIO_FEI_FEO_V2_BOOT()				IS_00X00(BOOT_MODE_GET())

/*故障边缘输入、上升边缘输出的所有sdio V2*/
#define ETS_IS_SDIO_FEI_REO_V2_BOOT()				IS_00X01(BOOT_MODE_GET())

/*上升沿输入、下降沿输出的所有sdio V2*/
#define ETS_IS_SDIO_REI_FEO_V2_BOOT()				IS_00X10(BOOT_MODE_GET())

/*上升沿输入、上升沿输出的所有信号V2*/
#define ETS_IS_SDIO_REI_REO_V2_BOOT()				IS_00X11(BOOT_MODE_GET())

/*上升沿输入、下降沿输出的所有信号V1*/
#define ETS_IS_SDIO_REI_FEO_V1_BOOT()				IS_01101(BOOT_MODE_GET())

/*不包括下载模式*/
#define ETS_IS_SDIO_BOOT()				IS_01101(BOOT_MODE_GET())

/*联合下载引导*/
#define ETS_IS_SDIO_UART_BOOT()				IS_00XXX(BOOT_MODE_GET())

/*ATE模式*/
#define ETS_IS_ATE_BOOT()				IS_01110(BOOT_MODE_GET())

/*有点控制闪存引导打印*/
#define ETS_IS_PRINT_BOOT()                             (BOOT_MODE_GET() & 0x2)

/*由ETS_IS_SDIO_ART_BOOT使用*/
#define SEL_NO_BOOT                                    0
#define SEL_SDIO_BOOT                                 BIT0
#define SEL_UART_BOOT                                BIT1

#endif /* _SOC_BOOT_MODE_H_ */

