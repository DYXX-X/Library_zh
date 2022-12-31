// 版权所有2015-2018 Espressif Systems（上海）私人有限公司
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
#include <stdint.h>
#include "sdkconfig.h"
#include "soc/soc.h"
#include "soc/periph_defs.h"

//包括soc相关（生成的）定义
#include "soc/soc_caps.h"
#include "soc/soc_pins.h"
#include "soc/spi_reg.h"
#include "soc/spi_struct.h"
#include "soc/gpio_sig_map.h"
#if SOC_MEMSPI_IS_INDEPENDENT
#include "soc/spi_mem_struct.h"
#include "soc/spi_mem_reg.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

#if CONFIG_IDF_TARGET_ESP32S2
#define SPI_FREAD_DIO 0
#define SPI_FREAD_QIO 0
#define SPI_FWRITE_DIO 0
#define SPI_FWRITE_QIO 0
#endif

/*
 存储一堆每spi外围数据。
*/
typedef struct {
    const uint8_t spiclk_out;       //GPIO多路复用器输出信号
    const uint8_t spiclk_in;
    const uint8_t spid_out;
    const uint8_t spiq_out;
    const uint8_t spiwp_out;
    const uint8_t spihd_out;
#if SOC_SPI_SUPPORT_OCT
    const uint8_t spid4_out;
    const uint8_t spid5_out;
    const uint8_t spid6_out;
    const uint8_t spid7_out;
#endif // SOC_SPI_SUPPORT_OCT
    const uint8_t spid_in;          //GPIO多路复用器输入信号
    const uint8_t spiq_in;
    const uint8_t spiwp_in;
    const uint8_t spihd_in;
#if SOC_SPI_SUPPORT_OCT
    const uint8_t spid4_in;
    const uint8_t spid5_in;
    const uint8_t spid6_in;
    const uint8_t spid7_in;
#endif // SOC_SPI_SUPPORT_OCT
    const uint8_t spics_out[3];     // /CS GPIO输出多路复用器信号
    const uint8_t spics_in;
    const uint8_t spidqs_out;
    const uint8_t spicd_out;
    const uint8_t spiclk_iomux_pin;    //IO_MUX复用信号的IO引脚
    const uint8_t spid_iomux_pin;
    const uint8_t spiq_iomux_pin;
    const uint8_t spiwp_iomux_pin;
    const uint8_t spihd_iomux_pin;
    const uint8_t spics0_iomux_pin;
    const uint8_t irq;              //中断多路复用器的irq源
    const uint8_t irq_dma;          //用于中断多路复用器的dma irq源
    const periph_module_t module;   //外围模块，用于启用时钟等
    const int func;             //IOMUX的函数号
    spi_dev_t *hw;              //指向硬件寄存器的指针
} spi_signal_conn_t;

extern const spi_signal_conn_t spi_periph_signal[SOC_SPI_PERIPH_NUM];

#ifdef __cplusplus
}
#endif

