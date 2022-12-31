// 版权所有2015-2020 Espressif Systems（上海）私人有限公司
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

/*******************************************************************************
 * 注意：hal不是公共api，不要在应用程序代码中使用。请参阅自述文件。在hal/include/hal/readme.md中的md
 ******************************************************************************/

/*
 * SPI从属HD模式的HAL层。
 *
 * 用法（分段模式）：
 * -首先，使用`spi_slave_hd_hal_init初始化从属设备`
 *
 * -事件处理：
 *     -（可选）调用``spi_slave_hd_hal_enable_event_intr``以启用使用的中断
 *     -（基本）调用``spi_slave_hd_hal_check_clear_event``检查事件是否发生，并清除其中断。对于事件：SPI_EV_BUF_TX、SPI_EV_BUF_RX、SPI_EV-BUF_RX、SPI_EV_CMD9和SPI_EV_CMDA。
 *     -（高级）调用“spi_slave_hd_hal_check_disable_event”禁用事件中断，以便任务稍后可以调用“spi_slave_hd-hal_invoke_event_intr”手动调用ISR。对于SPI_EV_SEND，SPI_EV_RECV。
 *
 * - TXDMA:
 *     -要通过DMA发送数据，请调用`spi_slave_hd_hal_txdma`
 *     -操作完成后，将触发SPI_EV_SEND。
 *
 * - RXDMA:
 *     -要通过DMA接收数据，请调用`spi_slave_hd_hal_rxdma`
 *     -操作完成后，将触发SPI_EV_RECV。
 *     -调用``spi_slave_hd_hal_rxdma_seg_get_len``获取接收的长度
 *
 *  -共享缓冲区：
 *      -调用``spi_slave_hd_hal_write_buffer``写入共享寄存器缓冲区。当主设备读取缓冲区时（无论读取地址如何），将触发SPI_EV_BUF_TX
 *      -调用``spi_slave_hd_hal_read_buffer``读取共享寄存器缓冲区。当主设备写入缓冲区时（无论写入地址如何），将触发SPI_EV_BUF_RX。
 */

#pragma once

#include <esp_types.h>
#include "esp_err.h"
#include "hal/spi_ll.h"
#include "hal/spi_types.h"

/**
 * @brief 带有附加成员的dma描述符类型此结构继承dma描述符，并带有指向用户传递的事务描述符的指针。
 */
typedef struct {
    lldesc_t      desc;                             ///<DMA描述符
    void          *arg;                             ///<这指向用户传入的事务描述符
} spi_slave_hd_hal_desc_append_t;

///HAL的配置
typedef struct {
    uint32_t      host_id;                          ///<spi外围设备的主机ID
    spi_dma_dev_t *dma_in;                          ///<输入DMA（DMA->RAM）外围寄存器地址
    spi_dma_dev_t *dma_out;                         ///<输出DMA（RAM->DMA）外围寄存器地址
    bool          dma_enabled;                      ///<是否启用DMA
    uint32_t      tx_dma_chan;                      ///<使用的TX DMA信道。
    uint32_t      rx_dma_chan;                      ///<使用的RX DMA信道。
    bool          append_mode;                      ///<对于DMA附加模式为True，对于段模式为false
    uint32_t      spics_io_num;                     ///<此设备的CS GPIO引脚
    uint8_t       mode;                             ///<SPI模式（0-3）
    uint32_t      command_bits;                     ///<命令字段位，8的倍数，至少8。
    uint32_t      address_bits;                     ///<地址字段位，8的倍数，至少8。
    uint32_t      dummy_bits;                       ///<伪字段位，8的倍数，至少8。

    struct {
        uint32_t  tx_lsbfirst : 1;                  ///<是否应首先使用LSB发送TX数据。
        uint32_t  rx_lsbfirst : 1;                  ///<是否应首先使用LSB读取RX数据。
    };
} spi_slave_hd_hal_config_t;

///HAL的上下文，由：cpp:func:`spi_slave_hd_HAL_init`初始化。
typedef struct {
    /* 这两个需要首先由驱动程序分配*/
    spi_slave_hd_hal_desc_append_t  *dmadesc_tx;            ///<TX DMA描述符的头。
    spi_slave_hd_hal_desc_append_t  *dmadesc_rx;            ///<RX DMA描述符的头。

    /* 硬件地址*/
    spi_dev_t                       *dev;                   ///<外围寄存器的起始地址。
    spi_dma_dev_t                   *dma_in;                ///<将从外设接收的数据存储到RAM中的DMA外设寄存器的地址。
    spi_dma_dev_t                   *dma_out;               ///<将数据从RAM传输到外设的DMA外设寄存器的地址。
    bool                            dma_enabled;            ///<是否启用DMA
    uint32_t                        tx_dma_chan;            ///<使用的TX DMA信道。
    uint32_t                        rx_dma_chan;            ///<使用的RX DMA信道。
    bool                            append_mode;            ///<对于DMA附加模式为True，对于段模式为false
    uint32_t                        dma_desc_num;           ///<可用DMA描述符的数量。根据``bus_max_transfer_size ``计算。
    spi_slave_hd_hal_desc_append_t  *tx_cur_desc;           ///<可以链接（设置）的当前TX DMA描述符。
    spi_slave_hd_hal_desc_append_t  *tx_dma_head;           ///<硬件未使用的链接TX DMA描述符的头
    spi_slave_hd_hal_desc_append_t  *tx_dma_tail;           ///<硬件未使用的链接TX DMA描述符的尾部
    spi_slave_hd_hal_desc_append_t  tx_dummy_head;          ///<启动``tx_dma_head``的伪描述符
    uint32_t                        tx_used_desc_cnt;       ///<已设置的TX描述符的数量
    uint32_t                        tx_recycled_desc_cnt;   ///<可回收的TX描述符的数量
    spi_slave_hd_hal_desc_append_t  *rx_cur_desc;           ///<可以链接（设置）的当前RX DMA描述符。
    spi_slave_hd_hal_desc_append_t  *rx_dma_head;           ///<硬件未使用的链接RX DMA描述符的头
    spi_slave_hd_hal_desc_append_t  *rx_dma_tail;           ///<硬件未使用的链接RX DMA描述符的尾部
    spi_slave_hd_hal_desc_append_t  rx_dummy_head;          ///<要启动的“rx_dm_head”的伪描述符
    uint32_t                        rx_used_desc_cnt;       ///<已设置的RX描述符的数量
    uint32_t                        rx_recycled_desc_cnt;   ///<可回收的RX描述符的数量

    /* HAL实现使用的内部状态，初始化为0。*/
    uint32_t                        intr_not_triggered;
    bool                            tx_dma_started;
    bool                            rx_dma_started;
} spi_slave_hd_hal_context_t;

/**
 * @brief 初始化硬件和部分上下文
 *
 * @param hal        HAL层的上下文
 * @param hal_config HAL的配置
 */
void spi_slave_hd_hal_init(spi_slave_hd_hal_context_t *hal, const spi_slave_hd_hal_config_t *hal_config);

/**
 * @brief 获取一个DMA描述符的大小
 *
 * @param hal       HAL层的上下文
 * @param bus_size  SPI总线最大传输大小（字节）。
 * @return          所有DMA描述符所需的总大小
 */
uint32_t spi_slave_hd_hal_get_total_desc_size(spi_slave_hd_hal_context_t *hal, uint32_t bus_size);

/**
 * @brief 获取实际总线大小
 *
 * @param hal       HAL层的上下文
 * @return          实际总线事务大小
 */
uint32_t spi_salve_hd_hal_get_max_bus_size(spi_slave_hd_hal_context_t *hal);

/**
 * @brief 检查并清除一个事件的信号
 *
 * @param hal       HAL层的上下文
 * @param ev        要检查的事件
 * @return          如果事件触发，则为True，否则为false
 */
bool spi_slave_hd_hal_check_clear_event(spi_slave_hd_hal_context_t* hal, spi_event_t ev);

/**
 * @brief 检查并清除一个事件的中断。
 *
 * @note 将保留事件源，以便：cpp:func:`spi_slave_hd_hal_invoke_event_intr`调用中断。如果事件未被触发，其中断源也不会被禁用。
 *
 * @param hal       HAL层的上下文
 * @param ev        要检查和禁用的事件
 * @return          如果事件触发，则为True，否则为false
 */
bool spi_slave_hd_hal_check_disable_event(spi_slave_hd_hal_context_t* hal, spi_event_t ev);

/**
 * @brief 启用以调用相应事件的ISR。
 *
 * @note 与：cpp:func:`spi_slave_hd_hal_enable_event_intr`相比，该函数包含强制触发中断的解决方法，即使中断源无法正确初始化。
 *
 * @param hal       HAL层的上下文
 * @param ev        调用ISR的事件（原因）
 */
void spi_slave_hd_hal_invoke_event_intr(spi_slave_hd_hal_context_t* hal, spi_event_t ev);

/**
 * @brief 启用相应事件的中断源。
 *
 * @param hal       HAL层的上下文
 * @param ev        应启用其相应中断源的事件。
 */
void spi_slave_hd_hal_enable_event_intr(spi_slave_hd_hal_context_t* hal, spi_event_t ev);

////////////////////////////////////////////////////////////////////////////////
// RX DMA
////////////////////////////////////////////////////////////////////////////////
/**
 * @brief 对指定的缓冲区启动RX DMA操作。
 *
 * @param hal       HAL层的上下文
 * @param[out] out_buf  接收数据的缓冲区
 * @param len       接收的最大长度
 */
void spi_slave_hd_hal_rxdma(spi_slave_hd_hal_context_t *hal, uint8_t *out_buf, size_t len);

/**
 * @brief 获取总接收数据的长度
 *
 * @param hal       HAL层的上下文
 * @return          接收的长度
 */
int spi_slave_hd_hal_rxdma_seg_get_len(spi_slave_hd_hal_context_t *hal);

////////////////////////////////////////////////////////////////////////////////
// TX DMA
////////////////////////////////////////////////////////////////////////////////
/**
 * @brief 使用指定的缓冲区启动TX DMA操作
 *
 * @param hal       HAL层的上下文
 * @param data      要发送的数据缓冲区
 * @param len       缓冲区的大小，也是要发送的最大长度
 */
void spi_slave_hd_hal_txdma(spi_slave_hd_hal_context_t *hal, uint8_t *data, size_t len);

////////////////////////////////////////////////////////////////////////////////
// 共享缓冲区
////////////////////////////////////////////////////////////////////////////////
/**
 * @brief 从共享寄存器缓冲区读取
 *
 * @param hal       HAL层的上下文
 * @param addr      要读取的共享注册表的地址
 * @param out_data  用于存储读取数据的缓冲区
 * @param len       从共享缓冲区读取的长度
 */
void spi_slave_hd_hal_read_buffer(spi_slave_hd_hal_context_t *hal, int addr, uint8_t *out_data, size_t len);

/**
 * @brief 写入共享寄存器缓冲区
 *
 * @param hal       HAL层的上下文
 * @param addr      要写入的共享寄存器的地址
 * @param data      要写入的数据的缓冲区
 * @param len       写入共享缓冲区的长度
 */
void spi_slave_hd_hal_write_buffer(spi_slave_hd_hal_context_t *hal, int addr, uint8_t *data, size_t len);

/**
 * @brief 获取上一笔交易的长度。
 *
 * @param hal       HAL层的上下文
 * @return          上次交易的长度
 */
int spi_slave_hd_hal_get_rxlen(spi_slave_hd_hal_context_t *hal);

/**
 * @brief 获取上次交易的地址
 *
 * @param hal       HAL层的上下文
 * @return          上次交易的地址
 */
int spi_slave_hd_hal_get_last_addr(spi_slave_hd_hal_context_t *hal);

#if CONFIG_IDF_TARGET_ESP32S2
//现在仅在ESP32S2上支持附加模式
////////////////////////////////////////////////////////////////////////////////
// 附加模式
////////////////////////////////////////////////////////////////////////////////
/**
 * @brief 返回完成的TX事务
 *
 * @note 该API基于这样的假设：当前事务完成的硬件行为仅由其自身的调用方层修改。这意味着如果其他代码改变了硬件行为（例如清除intr原始位），或者调用方在没有注意到硬件行为的情况下调用此API，则此API将出错。
 *
 * @param hal            HAL层的上下文
 * @param out_trans      指向调用者定义事务的指针
 * @return               1： 交易完成；0:事务未完成
 */
bool spi_slave_hd_hal_get_tx_finished_trans(spi_slave_hd_hal_context_t *hal, void **out_trans);

/**
 * @brief 返回已完成的RX事务
 *
 * @note 该API基于这样的假设：当前事务完成的硬件行为仅由其自身的调用方层修改。这意味着如果其他代码改变了硬件行为（例如清除intr原始位），或者调用方在没有注意到硬件行为的情况下调用此API，则此API将出错。
 *
 * @param hal            HAL层的上下文
 * @param out_trans      指向调用者定义事务的指针
 * @param out_len        接收数据的实际字节数
 * @return               1： 交易完成；0:事务未完成
 */
bool spi_slave_hd_hal_get_rx_finished_trans(spi_slave_hd_hal_context_t *hal, void **out_trans, size_t *out_len);

/**
 * @brief 加载TX DMA描述符而不停止DMA
 *
 * @param hal            HAL层的上下文
 * @param data           事务数据的缓冲区
 * @param len            数据的长度
 * @param arg            调用者用于指示转换的指针。事务完成时，将由``spi_slave_hd_hal_get_tx_finished_trans``返回
 * @return
 *        -ESP_OK：成功时
 *        -ESP_ERR_INVALID_STATE:调用的函数处于无效状态。
 */
esp_err_t spi_slave_hd_hal_txdma_append(spi_slave_hd_hal_context_t *hal, uint8_t *data, size_t len, void *arg);

/**
 * @brief 加载RX DMA描述符而不停止DMA
 *
 * @param hal            HAL层的上下文
 * @param data           事务数据的缓冲区
 * @param len            数据的长度
 * @param arg            调用者用于指示转换的指针。事务完成时，将由``spi_slave_hd_hal_get_rx_finished_trans``返回
 * @return
 *        -ESP_OK：成功时
 *        -ESP_ERR_INVALID_STATE:调用的函数处于无效状态。
 */
esp_err_t spi_slave_hd_hal_rxdma_append(spi_slave_hd_hal_context_t *hal, uint8_t *data, size_t len, void *arg);
#endif  //#如果配置IDF_TARGET_ESP32S2

