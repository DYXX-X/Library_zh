/*
 * SPDX文件版权文本：2010-2021浓缩咖啡系统（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */

#pragma once

#include <stdint.h>
#include <stdbool.h>
#include "esp_err.h"
#ifndef SPI_MOCK
#include "soc/lldesc.h"
#include "soc/spi_periph.h"
#endif
#include "hal/spi_types.h"
#include "sdkconfig.h"

#ifdef __cplusplus
extern "C"
{
#endif

//一个DMA描述符中可放入的最大字节数
#define SPI_MAX_DMA_LEN (4096-4)

/**
 * 将长度<=32位的无符号整数转换为SPI驱动程序可以直接发送的格式。
 *
 * E、 g.要发送9位数据，您可以：
 *
 *      uint16_t数据=SPI_SWAP_data_TX（0x145，9）；
 *
 * 然后将tx_buffer指向``&data``。
 *
 * @param DATA 要发送的数据可以是uint8_t、uint16_t或uint32_t。
 * @param LEN 要发送的数据长度，因为SPI外围设备从MSB发送，这有助于将数据转移到MSB。
 */
#define SPI_SWAP_DATA_TX(DATA, LEN) __builtin_bswap32((uint32_t)(DATA)<<(32-(LEN)))

/**
 * 将长度<=32位的接收数据转换为无符号整数的格式。
 *
 * E、 g.将放置在4字节阵列中的15位数据转换为整数：
 *
 *      uint16_t数据=SPI_SWAP_data_RX（*（uint32_t*）t->RX_data，15）；
 *
 * @param DATA 要重新排列的数据可以是uint8_t、uint16_t或uint32_t。
 * @param LEN 接收到的数据长度，因为SPI外围设备从MSB写入，这有助于将数据转移到LSB。
 */
#define SPI_SWAP_DATA_RX(DATA, LEN) (__builtin_bswap32(DATA)>>(32-(LEN)))

#define SPICOMMON_BUSFLAG_SLAVE         0          ///<在从属模式下初始化I/O
#define SPICOMMON_BUSFLAG_MASTER        (1<<0)     ///<在主模式下初始化I/O
#define SPICOMMON_BUSFLAG_IOMUX_PINS    (1<<1)     ///<使用iomux引脚检查。或表示引脚是通过IO多路复用器而不是GPIO矩阵配置的。
#define SPICOMMON_BUSFLAG_GPIO_PINS     (1<<2)     ///<强制信号通过GPIO矩阵路由。或表示引脚通过GPIO矩阵布线。
#define SPICOMMON_BUSFLAG_SCLK          (1<<3)     ///<检查SCLK引脚的存在。或表示CLK线已初始化。
#define SPICOMMON_BUSFLAG_MISO          (1<<4)     ///<检查MISO引脚的存在。或表示MISO线已初始化。
#define SPICOMMON_BUSFLAG_MOSI          (1<<5)     ///<检查MOSI引脚的存在。或表示MOSI线已初始化。
#define SPICOMMON_BUSFLAG_DUAL          (1<<6)     ///<检查MOSI和MISO引脚是否可以输出。或表示总线能够在DIO模式下工作。
#define SPICOMMON_BUSFLAG_WPHD          (1<<7)     ///<检查WP和HD引脚的存在。或表示WP和HD引脚已初始化。
#define SPICOMMON_BUSFLAG_QUAD          (SPICOMMON_BUSFLAG_DUAL|SPICOMMON_BUSFLAG_WPHD)     ///<检查输出的MOSI/MISO/WP/HD引脚是否存在。或表示总线能够在QIO模式下工作。
#define SPICOMMON_BUSFLAG_IO4_IO7       (1<<8)     ///<检查IO4~IO7引脚的存在。或表示IO4~IO7引脚已初始化。
#define SPICOMMON_BUSFLAG_OCTAL         (SPICOMMON_BUSFLAG_QUAD|SPICOMMON_BUSFLAG_IO4_IO7)  ///<检查作为输出的MOSI/MISO/WP/HD/SPIIO4/SPIIO5/SPIIO6/SPIIO7引脚是否存在。或表示总线能够在八进制模式下工作。
#define SPICOMMON_BUSFLAG_NATIVE_PINS   SPICOMMON_BUSFLAG_IOMUX_PINS

/**
 * @brief SPI DMA通道
 */
typedef enum {
  SPI_DMA_DISABLED = 0,     ///<不为SPI启用DMA
#if CONFIG_IDF_TARGET_ESP32
  SPI_DMA_CH1      = 1,     ///<启用DMA，选择DMA通道1
  SPI_DMA_CH2      = 2,     ///<启用DMA，选择DMA通道2
#endif
  SPI_DMA_CH_AUTO  = 3,     ///<启用DMA，通道由驱动程序自动选择
} spi_common_dma_t;

#if __cplusplus
/* 需要C++向后兼容早期的ESP-IDF，其中此参数为空的“int”。可在ESP-IDF 5中删除*/
typedef int spi_dma_chan_t;
#else
typedef spi_common_dma_t spi_dma_chan_t;
#endif

/**
 * @brief 这是SPI总线的配置结构。
 *
 * 您可以使用此结构指定总线的GPIO引脚。通常，驱动器将使用GPIO矩阵来路由信号。当所有信号都可以通过IO_MUX路由或为-1时，会出现异常。在这种情况下，使用IO_MUX，允许超过40MHz的速度。
 *
 * @note 请注意，从属驱动程序不使用quadwp/quadhd行，spi_bus_config_t中引用这些行的字段将被忽略，因此可以安全地保持未初始化状态。
 */
typedef struct {
    union {
      int mosi_io_num;    ///<主输出从输入（=spi_d）信号的GPIO引脚，如果未使用，则为-1。
      int data0_io_num;   ///<GPIO引脚用于四/八进制模式下的spi data0信号，如果未使用，则为-1。
    };
    union {
      int miso_io_num;    ///<主输入从输出（=spi_q）信号的GPIO引脚，如果未使用，则为-1。
      int data1_io_num;   ///<四/八进制模式下spi data1信号的GPIO引脚，如果未使用，则为-1。
    };
    int sclk_io_num;      ///<SPI时钟信号的GPIO引脚，如果未使用，则为-1。
    union {
      int quadwp_io_num;  ///<用于WP（写保护）信号的GPIO引脚，如果未使用，则为-1。
      int data2_io_num;   ///<四/八进制模式下spi data2信号的GPIO引脚，如果未使用，则为-1。
    };
    union {
      int quadhd_io_num;  ///<用于HD（保持）信号的GPIO引脚，如果未使用，则为-1。
      int data3_io_num;   ///<四/八进制模式下spi data3信号的GPIO引脚，如果未使用，则为-1。
    };
    int data4_io_num;     ///<GPIO引脚用于八进制模式下的spi data4信号，如果未使用，则为-1。
    int data5_io_num;     ///<GPIO引脚用于八进制模式下的spi data5信号，如果未使用，则为-1。
    int data6_io_num;     ///<GPIO引脚用于八进制模式下的spi data6信号，如果未使用，则为-1。
    int data7_io_num;     ///<GPIO引脚用于八进制模式下的spi data7信号，如果未使用，则为-1。
    int max_transfer_sz;  ///<最大传输大小（字节）。如果启用DMA时为0，则默认值为4092；如果禁用DMA，则默认为“SOC_SPI_MAXIMUM_BUFFER_SIZE”。
    uint32_t flags;       ///<由驾驶员检查的公交车能力。或``SPICOMMON_BUSFLAG_*``标志的ed值。
    int intr_flags;       /**< 用于设置优先级的总线中断标志和IRAM属性，请参见``esp_intr_alloc.h``。请注意，驱动程序会忽略EDGE、INTRDISABLED属性。请注意，如果设置了ESP_INTR_FLAG_IRAM，则驱动程序的所有回调及其被调用函数都应该放在IRAM中。
                           */
} spi_bus_config_t;


/**
 * @brief 初始化SPI总线
 *
 * @warning 不支持SPI0/1
 *
 * @param host_id       控制此总线的SPI外围设备
 * @param bus_config    指向spi_bus_config_t结构的指针，该结构指定应如何初始化主机
 * @param dma_chan      -为SPI总线选择DMA通道允许总线上的事务，其大小仅受内部内存量的限制。
 *                      -选择SPI_DMA_DISABLED将限制事务的大小。
 *                      -如果只有SPI闪存使用此总线，则设置为SPI_DMA_DISABLED。
 *                      -设置为SPI_DMA_CH_AUTO，让驱动程序分配DMA通道。
 *
 * @warning 如果选择了DMA信道，则所使用的任何发送和接收缓冲区都应分配到支持DMA的存储器中。
 *
 * @warning SPI的ISR始终在调用此函数的内核上执行。切勿使此核心上的ISR挨饿，否则SPI事务将无法处理。
 *
 * @return
 *         -如果配置无效，则为ESP_ERR_INVALID_ARG
 *         -如果主机已在使用，则为ESP_ERR_INVALID_STATE
 *         -如果没有可用的DMA信道，则为ESP_ERR_NOT_FOUND
 *         -ESP_ERR_NO_MEM（如果内存不足）
 *         -成功时ESP_OK
 */
esp_err_t spi_bus_initialize(spi_host_device_t host_id, const spi_bus_config_t *bus_config, spi_dma_chan_t dma_chan);

/**
 * @brief 释放SPI总线
 *
 * @warning 为了成功，必须首先移除所有设备。
 *
 * @param host_id SPI外设到空闲
 * @return
 *         -如果参数无效，则为ESP_ERR_INVALID_ARG
 *         -如果不是总线上的所有设备都被释放，则为ESP_ERR_INVALID_STATE
 *         -成功时ESP_OK
 */
esp_err_t spi_bus_free(spi_host_device_t host_id);

#ifdef __cplusplus
}
#endif

