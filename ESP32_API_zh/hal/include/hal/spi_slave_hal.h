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

/*******************************************************************************
 * 注意：hal不是公共api，不要在应用程序代码中使用。请参阅自述文件。在hal/include/hal/readme.md中的md
 ******************************************************************************/

// SPI从站的HAL层（公共部分）

// SPI从属HAL用法：
// 1.初始化总线
// 2.如果使用DMA，初始化DMA描述符
// 3.调用setup_device更新设备的参数
// 4.准备要发送的数据，并准备接收缓冲区
// 5.触发用户定义的SPI事务以启动
// 6.等待用户事务完成
// 7.存储接收到的数据并获取长度
// 8.在下一个事务之前检查并重置DMA（如果需要）

#pragma once

#include <esp_types.h>
#include "soc/lldesc.h"
#include "soc/spi_struct.h"
#include "soc/soc_caps.h"
#include "hal/spi_ll.h"

/**
 * 驱动程序和HAL都应维护的上下文。
 */
typedef struct {
    /* 初始化时由驱动程序配置，请勿触摸*/
    spi_dev_t     *hw;              ///<外围寄存器的起始地址。
    spi_dma_dev_t *dma_in;          ///<将从外设接收的数据存储到RAM中的DMA外设寄存器的地址。
    spi_dma_dev_t *dma_out;         ///<将数据从RAM传输到外设的DMA外设寄存器的地址。
    /* 应在初始化时由驱动程序配置*/
    lldesc_t      *dmadesc_rx;      /**< TX DMA使用的DMA描述符数组。金额应大于dmadesc_n。驱动程序应确保要发送的数据比描述符所能容纳的数据短。
                                     */
    lldesc_t      *dmadesc_tx;      /**< RX DMA使用的DMA描述符数组。金额应大于dmadesc_n。驱动程序应确保要发送的数据比描述符所能容纳的数据短。
                                     */
    int           dmadesc_n;        ///<HAL可以使用的“dmadesc_tx”和“dmadesc_rx”描述符的数量。
    uint32_t      tx_dma_chan;      ///<TX DMA信道
    uint32_t      rx_dma_chan;      ///<RX DMA信道

    /*
     * 要在“spi_slave_hal_init”之后填充的配置。在调用“spi_slave_hal_setup_device”时更新到外围寄存器。
     */
    struct {
        uint32_t rx_lsbfirst : 1;
        uint32_t tx_lsbfirst : 1;
        uint32_t use_dma     : 1;
    };
    int mode;

    /*
     * 事务特定（数据），所有这些参数将在每次事务中更新到外围设备。
     */
    uint32_t bitlen;                ///<事务的预期最大长度，以位为单位。
    const void *tx_buffer;          ///<要发送的数据
    void *rx_buffer;                ///<保存接收数据的缓冲区。

    /*  一笔交易后的其他交易结果*/
    uint32_t rcv_bitlen;            ///<最后一个事务的长度，以位为单位。
} spi_slave_hal_context_t;

typedef struct {
    uint32_t host_id;               ///<SPI控制器ID
    spi_dma_dev_t *dma_in;          ///<输入DMA（DMA->RAM）外围寄存器地址
    spi_dma_dev_t *dma_out;         ///<输出DMA（RAM->DMA）外围寄存器地址
} spi_slave_hal_config_t;

/**
 * 初始化外围设备和上下文。
 *
 * @param hal        HAL层的上下文。
 * @param hal_config HAL的配置
 */
void spi_slave_hal_init(spi_slave_hal_context_t *hal, const spi_slave_hal_config_t *hal_config);

/**
 * 取消外围设备（如果需要，还可以取消上下文）。
 *
 * @param hal HAL层的上下文。
 */
void spi_slave_hal_deinit(spi_slave_hal_context_t *hal);

/**
 * 根据上下文中的设置设置与设备相关的配置。
 *
 * @param hal HAL层的上下文。
 */
void spi_slave_hal_setup_device(const spi_slave_hal_context_t *hal);

/**
 * 准备当前事务的数据。
 *
 * @param hal HAL层的上下文。
 */
void spi_slave_hal_prepare_data(const spi_slave_hal_context_t *hal);

/**
 * 触发器启动用户定义的事务。
 *
 * @param hal HAL层的上下文。
 */
void spi_slave_hal_user_start(const spi_slave_hal_context_t *hal);

/**
 * 检查事务是否完成（trans_done已设置）。
 *
 * @param hal HAL层的上下文。
 */
bool spi_slave_hal_usr_is_done(spi_slave_hal_context_t* hal);

/**
 * 执行事务操作后，从缓冲区提取数据并重新记录长度。
 *
 * @param hal HAL层的上下文。
 */
void spi_slave_hal_store_result(spi_slave_hal_context_t *hal);

/**
 * 获取最后一个事务的长度（以位为单位）。应在``spi_slave_hal_store_result``之后调用。
 *
 * 注意，如果最后一个事务比之前配置的长，则返回值将被截断为配置的长度。
 *
 * @param hal HAL层的上下文。
 *
 * @return 最后一个事务的长度，以位为单位。
 */
uint32_t spi_slave_hal_get_rcv_bitlen(spi_slave_hal_context_t *hal);

/**
 * 检查是否需要根据上次事务的状态重置DMA。
 *
 * 在ESP32中，有时我们可能需要在下一个事务之前重置从属设备的DMA。打电话给我检查一下。
 *
 * @param hal HAL层的上下文。
 *
 * @return 如果需要重置，则为true，否则为false。
 */
bool spi_slave_hal_dma_need_reset(const spi_slave_hal_context_t *hal);

