/*
 * SPDX文件版权文本：2010-2021浓缩咖啡系统（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */

#pragma once

#include "esp_types.h"
#include "soc/soc_caps.h"
#include "freertos/FreeRTOS.h"

#include "hal/spi_types.h"
#include "driver/spi_common.h"
#include "sdkconfig.h"

#ifdef __cplusplus
extern "C"
{
#endif

#if !SOC_SPI_SUPPORT_SLAVE_HD_VER2  && !CI_HEADER_CHECK
#error The SPI peripheral does not support this feature
#endif

///要发送/接收的数据描述符
typedef struct {
    uint8_t* data;                              ///<要发送的缓冲区，必须支持DMA
    size_t   len;                               ///<要发送/接收的数据长度。对于接收，缓冲区长度应为4字节的倍数，否则多余的部分将被截断。
    size_t   trans_len;                         ///<对于RX方向，表示实际接收的数据。对于TX方向，这是没有意义的。
    void*    arg;                               ///<标记此数据的额外参数
} spi_slave_hd_data_t;

///SPI从属HD事件信息
typedef struct {
    spi_event_t          event;                 ///<事件类型
    spi_slave_hd_data_t* trans;                 ///<SPI_EV_SEND和SPI_EV_RECV事件的对应事务
} spi_slave_hd_event_t;

///SPI从属HD的回调
typedef bool (*slave_cb_t)(void* arg, spi_slave_hd_event_t* event, BaseType_t* awoken);

///SPI从HD通道进行数据处理
typedef enum {
    SPI_SLAVE_CHAN_TX = 0,                      ///<输出通道（RDDMA）
    SPI_SLAVE_CHAN_RX = 1,                      ///<输入通道（WRDMA）
} spi_slave_chan_t;

///SPI从属HD的回调配置结构
typedef struct {
    slave_cb_t cb_buffer_tx;                    ///<主设备从共享缓冲区读取时的回调
    slave_cb_t cb_buffer_rx;                    ///<主设备写入共享缓冲区时的回调
    slave_cb_t cb_send_dma_ready;               ///<TX数据缓冲区加载到硬件（DMA）时的回调
    slave_cb_t cb_sent;                         ///<发送数据时回调
    slave_cb_t cb_recv_dma_ready;               ///<RX数据缓冲区加载到硬件（DMA）时的回调
    slave_cb_t cb_recv;                         ///<收到数据时回调
    slave_cb_t cb_cmd9;                         ///<收到CMD9时回调
    slave_cb_t cb_cmdA;                         ///<收到CMDA时回调
    void* arg;                                  ///<指示此SPI从属HD外围实例的参数
} spi_slave_hd_callback_config_t;


//要使用的“spi_slave_hd_slot_config_t”标志
#define SPI_SLAVE_HD_TXBIT_LSBFIRST     (1<<0)  ///<先发送命令/地址/数据LSB，而不是先发送默认MSB
#define SPI_SLAVE_HD_RXBIT_LSBFIRST     (1<<1)  ///<先接收数据LSB，而不是先接收默认MSB
#define SPI_SLAVE_HD_BIT_LSBFIRST       (SPI_SLAVE_HD_TXBIT_LSBFIRST|SPI_SLAVE_HD_RXBIT_LSBFIRST) ///<首先发送和接收LSB
#define SPI_SLAVE_HD_APPEND_MODE        (1<<2)  ///<事务采用DMA附加模式。在此模式下，用户可以加载（附加）DMA描述符而不停止DMA

///SPI从属HD驱动程序的配置结构
typedef struct {
    uint8_t mode;                               /**< SPI模式，表示一对（CPOL、CPHA）配置：
                                                     - 0: (0, 0)
                                                     - 1: (0, 1)
                                                     - 2: (1, 0)
                                                     - 3: (1, 1)
                                                 */
    uint32_t spics_io_num;                      ///<此设备的CS GPIO引脚
    uint32_t flags;                             ///<SPI_SLAVE_HD_*标志的位或
    uint32_t command_bits;                      ///<命令字段位，8的倍数，至少8。
    uint32_t address_bits;                      ///<地址字段位，8的倍数，至少8。
    uint32_t dummy_bits;                        ///<伪字段位，8的倍数，至少8。
    uint32_t queue_size;                        ///<事务队列大小。这设置了可以同时“悬空”的事务数（使用spi_slave_hd_queue_trans排队，但尚未使用spi_srave_hd_get_trans_result完成）
    spi_dma_chan_t dma_chan;                    ///<要使用的DMA通道。
    spi_slave_hd_callback_config_t cb_config;   ///<回调配置
} spi_slave_hd_slot_config_t;

/**
 * @brief 初始化SPI从属HD驱动程序。
 *
 * @param host_id       要使用的主机
 * @param bus_config    所用总线的总线配置
 * @param config        SPI从属HD驱动程序的配置
 * @return
 *  -ESP_OK：成功时
 *  -ESP_ERR_INVALID_ARG:给定的参数无效
 *  -ESP_ERR_INVALID_STATE:函数在无效状态下调用，可能是某些资源已在使用中
 *  -如果没有可用的DMA信道，则为ESP_ERR_NOT_FOUND
 *  -ESP_ERR_NO_MEM:内存分配失败
 *  -或`esp_intr_alloc中的其他返回值`
 */
esp_err_t spi_slave_hd_init(spi_host_device_t host_id, const spi_bus_config_t *bus_config,
                            const spi_slave_hd_slot_config_t *config);

/**
 * @brief 取消初始化SPI从属HD驱动程序
 *
 * @param host_id 要取消初始化驱动程序的主机
 * @return
 *  -ESP_OK：成功时
 *  -ESP_ERR_INVALID_ARG：如果host_id不正确
 */
esp_err_t spi_slave_hd_deinit(spi_host_device_t host_id);

/**
 * @brief 队列事务（分段模式）
 *
 * @param host_id   将事务排队的主机
 * @param chan      SPI_SLAVE_CHAN_TX或SPI_SLAVE _CHAN_RX
 * @param trans     事务描述符
 * @param timeout   数据排队前超时
 * @return
 *  -ESP_OK：成功时
 *  -ESP_ERR_INVALID_ARG:输入参数无效。可能是以下原因：
 *      -给定的缓冲区不支持DMA
 *      -数据长度无效（不大于0，或超过最大传输长度）
 *      -交易方向无效
 *  -ESP_ERR_TIMEOUT：超时前无法对数据进行排队。Master仍在处理上一个事务。
 *  -ESP_ERR_INVALID_STATE:调用的函数处于无效状态。应在段模式下调用此API。
 */
esp_err_t spi_slave_hd_queue_trans(spi_host_device_t host_id, spi_slave_chan_t chan, spi_slave_hd_data_t* trans, TickType_t timeout);

/**
 * @brief 获取数据事务的结果（分段模式）
 *
 * @note 此API应与“spi_slave_hd_queue_trans”成功调用的次数相同。
 *
 * @param host_id   将事务排队的主机
 * @param chan      获取结果的通道SPI_SLAVE_CHAN_TX或SPI_SLAVE _CHAN_RX
 * @param[out] out_trans 指向之前传递给驱动程序的事务描述符（``spi_slave_hd_data_t``）的指针。硬件已完成此事务。成员“trans_len”表示接收数据的实际字节数，这对于TX没有意义。
 * @param timeout   获得结果前超时
 * @return
 *  -ESP_OK：成功时
 *  -ESP_ERR_INVALID_ARG:函数无效
 *  -ESP_ERR_TIMEOUT：超时前没有事务完成
 *  -ESP_ERR_INVALID_STATE:调用的函数处于无效状态。应在段模式下调用此API。
 */
esp_err_t spi_slave_hd_get_trans_res(spi_host_device_t host_id, spi_slave_chan_t chan, spi_slave_hd_data_t **out_trans, TickType_t timeout);

/**
 * @brief 读取共享寄存器
 *
 * @param host_id   读取共享寄存器的主机
 * @param addr      要读取的寄存器地址，0到``SOC_SPI_MAXIMUM_BUFFER_SIZE-1``
 * @param[out] out_data 用于存储读取数据的输出缓冲区
 * @param len       要读取的长度，不大于``SOC_SPI_MAXIMUM_BUFFER_SIZE-addr``
 */
void spi_slave_hd_read_buffer(spi_host_device_t host_id, int addr, uint8_t *out_data, size_t len);

/**
 * @brief 写入共享寄存器
 *
 * @param host_id   写入共享寄存器的主机
 * @param addr      要写入的寄存器地址，0到``SOC_SPI_MAXIMUM_BUFFER_SIZE-1``
 * @param data      保存要写入的数据的缓冲区
 * @param len       要写入的长度，``SOC_SPI_MAXIMUM_BUFFER_SIZE-addr``
 */
void spi_slave_hd_write_buffer(spi_host_device_t host_id, int addr, uint8_t *data, size_t len);

/**
 * @brief 加载事务（追加模式）
 *
 * @note 在此模式下，用户事务描述符将附加到DMA，DMA将继续处理数据而不停止
 *
 * @param host_id   要加载事务的主机
 * @param chan      SPI_SLAVE_CHAN_TX或SPI_SLAVE _CHAN_RX
 * @param trans     事务描述符
 * @param timeout   加载事务前超时
 * @return
 *  -ESP_OK：成功时
 *  -ESP_ERR_INVALID_ARG:输入参数无效。可能是以下原因：
 *      -给定的缓冲区不支持DMA
 *      -数据长度无效（不大于0，或超过最大传输长度）
 *      -交易方向无效
 *  -ESP_ERR_TIMEOUT:Master仍在处理上一个事务。没有可用的事务可供从服务器加载
 *  -ESP_ERR_INVALID_STATE:调用的函数处于无效状态。应在追加模式下调用此API。
 */
esp_err_t spi_slave_hd_append_trans(spi_host_device_t host_id, spi_slave_chan_t chan, spi_slave_hd_data_t *trans, TickType_t timeout);

/**
 * @brief 获取数据事务的结果（追加模式）
 *
 * @note 此API的调用时间应与`` spi_slave_hd_append_trans相同``
 *
 * @param host_id   要加载事务的主机
 * @param chan      SPI_SLAVE_CHAN_TX或SPI_SLAVE _CHAN_RX
 * @param[out] out_trans 指向之前传递给驱动程序的事务描述符（``spi_slave_hd_data_t``）的指针。硬件已完成此事务。成员“trans_len”表示接收数据的实际字节数，这对于TX没有意义。
 * @param timeout   获得结果前超时
 * @return
 *  -ESP_OK：成功时
 *  -ESP_ERR_INVALID_ARG:函数无效
 *  -ESP_ERR_TIMEOUT：超时前没有事务完成
 *  -ESP_ERR_INVALID_STATE:调用的函数处于无效状态。应在追加模式下调用此API。
 */
esp_err_t spi_slave_hd_get_append_trans_res(spi_host_device_t host_id, spi_slave_chan_t chan, spi_slave_hd_data_t **out_trans, TickType_t timeout);

#ifdef __cplusplus
}
#endif

