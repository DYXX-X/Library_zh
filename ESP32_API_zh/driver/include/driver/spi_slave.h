/*
 * SPDX文件版权文本：2010-2021浓缩咖啡系统（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */


#ifndef _DRIVER_SPI_SLAVE_H_
#define _DRIVER_SPI_SLAVE_H_

#include "esp_err.h"
#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"
#include "driver/spi_common.h"


#ifdef __cplusplus
extern "C"
{
#endif


#define SPI_SLAVE_TXBIT_LSBFIRST          (1<<0)  ///<先发送命令/地址/数据LSB，而不是先发送默认MSB
#define SPI_SLAVE_RXBIT_LSBFIRST          (1<<1)  ///<先接收数据LSB，而不是先接收默认MSB
#define SPI_SLAVE_BIT_LSBFIRST            (SPI_SLAVE_TXBIT_LSBFIRST|SPI_SLAVE_RXBIT_LSBFIRST) ///<首先发送和接收LSB


typedef struct spi_slave_transaction_t spi_slave_transaction_t;
typedef void(*slave_transaction_cb_t)(spi_slave_transaction_t *trans);

/**
 * @brief 这是SPI主机充当从设备的配置。
 */
typedef struct {
    int spics_io_num;               ///<此设备的CS GPIO引脚
    uint32_t flags;                 ///<SPI_SLAVE_*标志的位或
    int queue_size;                 ///<事务队列大小。这设置了可以同时“空中传送”的事务数（使用spi_slave_queue_trans排队，但尚未使用spi_srave_get_trans_result完成）
    uint8_t mode;                   /**< SPI模式，表示一对（CPOL、CPHA）配置：
                                         - 0: (0, 0)
                                         - 1: (0, 1)
                                         - 2: (1, 0)
                                         - 3: (1, 1)
                                     */
    slave_transaction_cb_t post_setup_cb;  /**< SPI寄存器加载新数据后调用回调。
                                             *
                                             *  该回调是在中断上下文中调用的。为了获得最佳性能，应该在IRAM中调用，请参阅SPI主文档中的“传输速度”部分以了解详细信息。如果没有，则当使用ESP_INTR_FLAG_IRAM初始化驱动程序时，回调可能会在闪存操作期间崩溃。
                                             */
    slave_transaction_cb_t post_trans_cb;  /**< 事务完成后调用回调。
                                             *
                                             *  该回调是在中断上下文中调用的。为了获得最佳性能，应该在IRAM中调用，请参阅SPI主文档中的“传输速度”部分以了解详细信息。如果没有，则当使用ESP_INTR_FLAG_IRAM初始化驱动程序时，回调可能会在闪存操作期间崩溃。
                                             */
} spi_slave_interface_config_t;

/**
 * 此结构描述一个SPI事务
 */
struct spi_slave_transaction_t {
    size_t length;                  ///<总数据长度，以位为单位
    size_t trans_len;               ///<事务数据长度，以位为单位
    const void *tx_buffer;          ///<指向传输缓冲区的指针，或对于无MOSI阶段为NULL
    void *rx_buffer;                /**< 指向接收缓冲区的指针，或NULL表示没有MISO阶段。DMA合成时，必须从WORD边界开始（`rx_buffer%4==0`），长度为4字节的倍数。
                                     */
    void *user;                     ///<用户定义变量。可用于存储例如交易ID。
};

/**
 * @brief 将SPI总线初始化为从属接口
 *
 * @warning 不支持SPI0/1
 *
 * @param host          用作SPI从属接口的SPI外设
 * @param bus_config    指向spi_bus_config_t结构的指针，该结构指定应如何初始化主机
 * @param slave_config  指向指定从属接口详细信息的spi_slave_interface_config_t结构的指针
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
esp_err_t spi_slave_initialize(spi_host_device_t host, const spi_bus_config_t *bus_config, const spi_slave_interface_config_t *slave_config, spi_dma_chan_t dma_chan);

/**
 * @brief 释放声称为SPI从属接口的SPI总线
 *
 * @param host SPI外设到空闲
 * @return
 *         -如果参数无效，则为ESP_ERR_INVALID_ARG
 *         -如果不是总线上的所有设备都被释放，则为ESP_ERR_INVALID_STATE
 *         -成功时ESP_OK
 */
esp_err_t spi_slave_free(spi_host_device_t host);


/**
 * @brief 将SPI事务排队以执行
 *
 * 将要由该从属设备执行的SPI事务排队。（事务队列大小是在通过spi_slave_initialize初始化从属设备时指定的。）如果队列已满（取决于ticks_to_wait参数），此函数可能会阻塞。此功能不会直接启动SPI操作，当主控通过下拉CS并发送时钟信号来启动SPI事务时，将发生下一个排队事务。
 *
 * 此函数将“trans_desc”中缓冲区的所有权移交给SPI从属驱动程序；在调用“spislavequeuetrans”将所有权交还给应用程序之前，应用程序不会访问此内存。
 *
 * @param host 充当从属设备的SPI外围设备
 * @param trans_desc 要执行的事务的描述。不是常量，因为我们可能希望将状态写回事务描述中。
 * @param ticks_to_wait 勾选等待，直到队列中有空间；使用portMAX_DELAY永不超时。
 * @return
 *         -如果参数无效，则为ESP_ERR_INVALID_ARG
 *         -成功时ESP_OK
 */
esp_err_t spi_slave_queue_trans(spi_host_device_t host, const spi_slave_transaction_t *trans_desc, TickType_t ticks_to_wait);


/**
 * @brief 获取先前排队的SPI事务的结果
 *
 * 此例程将等待到给定设备的事务（之前使用spi_slave_queue_trans排队）成功完成。然后它将返回完成事务的描述，以便软件可以检查结果，例如释放内存或重新使用缓冲区。
 *
 * 对于“spi_slave_queue_trans”排队的任何事务，必须最终使用此函数。
 *
 * @param host 作为从属设备的SPI外围设备
 * @param[out] trans_desc 指向变量的指针，该变量能够包含指向所执行事务描述的指针
 * @param ticks_to_wait 勾选以等待返回的项目；使用portMAX_DELAY永不超时。
 * @return
 *         -如果参数无效，则为ESP_ERR_INVALID_ARG
 *         -成功时ESP_OK
 */
esp_err_t spi_slave_get_trans_result(spi_host_device_t host, spi_slave_transaction_t **trans_desc, TickType_t ticks_to_wait);


/**
 * @brief 执行SPI事务
 *
 * 本质上与spi_slave_queue_trans后跟spi_slav_get_trans_result相同。如果仍有一个事务队列尚未使用spi_slave_get_trans_result完成，请不要使用此选项。
 *
 * @param host 作为从属设备的SPI外围设备
 * @param trans_desc 指向变量的指针，该变量能够包含指向所执行事务描述的指针。不是常量，因为我们可能希望将状态写回事务描述中。
 * @param ticks_to_wait 勾选以等待返回的项目；使用portMAX_DELAY永不超时。
 * @return
 *         -如果参数无效，则为ESP_ERR_INVALID_ARG
 *         -成功时ESP_OK
 */
esp_err_t spi_slave_transmit(spi_host_device_t host, spi_slave_transaction_t *trans_desc, TickType_t ticks_to_wait);


#ifdef __cplusplus
}
#endif

#endif

