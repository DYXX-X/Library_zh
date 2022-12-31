// 版权所有2020 Espressif Systems（上海）私人有限公司
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
#define IS_1XXX(v)                              (((v)&0x08)==0x08)

/*下载引导，SPI（或SDIO_V2）/UART0*/
#define IS_00XX(v)                              (((v)&0x0c)==0x00)

/*下载引导，SDIO/UART0/UART1，FEI_FEO V2*/
#define IS_0000(v)                              (((v)&0x0f)==0x00)

/*下载引导，SDIO/UART0/UART1，FEI_REO V2*/
#define IS_0001(v)                              (((v)&0x0f)==0x01)

/*下载引导，SDIO/UART0/UART1，REI_FEO V2*/
#define IS_0010(v)                              (((v)&0x0f)==0x02)

/*下载引导，SDIO/UART0/UART1，REI_REO V2*/
#define IS_0011(v)                              (((v)&0x0f)==0x03)

/*传统SPI引导*/
#define IS_0100(v)                              (((v)&0x0f)==0x04)

/*ATE/ANALOG模式*/
#define IS_0101(v)                              (((v)&0x0f)==0x05)

/*SPI（或SDIO_V1）下载模式*/
#define IS_0110(v)                              (((v)&0x0f)==0x06)

/*诊断模式+UART0下载模式*/
#define IS_0111(v)                              (((v)&0x0f)==0x07)



#define BOOT_MODE_GET()                         (GPIO_REG_READ(GPIO_STRAP_REG))

/*不包括下载模式*/
#define ETS_IS_UART_BOOT()                      IS_0111(BOOT_MODE_GET())

/*所有spi引导，包括spi/遗留*/
#define ETS_IS_FLASH_BOOT()                     (IS_1XXX(BOOT_MODE_GET()) || IS_0100(BOOT_MODE_GET()))

/*所有更快的spi引导，包括spi*/
#define ETS_IS_FAST_FLASH_BOOT()                IS_1XXX(BOOT_MODE_GET())

#if SUPPORT_SDIO_DOWNLOAD

/*故障边缘输入、故障边缘输出的所有sdio V2*/
#define ETS_IS_SDIO_FEI_FEO_V2_BOOT()           IS_0000(BOOT_MODE_GET())

/*故障边缘输入、上升边缘输出的所有sdio V2*/
#define ETS_IS_SDIO_FEI_REO_V2_BOOT()           IS_0001(BOOT_MODE_GET())

/*上升沿输入、下降沿输出的所有sdio V2*/
#define ETS_IS_SDIO_REI_FEO_V2_BOOT()           IS_0010(BOOT_MODE_GET())

/*上升沿输入、上升沿输出的所有信号V2*/
#define ETS_IS_SDIO_REI_REO_V2_BOOT()           IS_0011(BOOT_MODE_GET())

/*上升沿输入、下降沿输出的所有信号V1*/
#define ETS_IS_SDIO_REI_FEO_V1_BOOT()           IS_0110(BOOT_MODE_GET())

/*不包括联合下载模式*/
#define ETS_IS_SDIO_BOOT()                      IS_0110(BOOT_MODE_GET())
#else

/*不包括联合下载模式*/
#define ETS_IS_SPI_DOWNLOAD_BOOT()              IS_0110(BOOT_MODE_GET())

#endif

/*联合下载引导*/
#define ETS_IS_JOINT_DOWNLOAD_BOOT()                  IS_00XX(BOOT_MODE_GET())

/*ATE模式*/
#define ETS_IS_ATE_BOOT()                       IS_0101(BOOT_MODE_GET())

/*由ETS_IS_SDIO_ART_BOOT使用*/
#define SEL_NO_BOOT                             0
#define SEL_SDIO_BOOT                           BIT0
#define SEL_UART_BOOT                           BIT1
#define SEL_SPI_SLAVE_BOOT                      BIT2

#endif /* _SOC_BOOT_MODE_H_ */

