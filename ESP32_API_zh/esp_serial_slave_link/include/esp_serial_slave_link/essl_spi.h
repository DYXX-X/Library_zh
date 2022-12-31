// 版权所有2010-2020 Espressif Systems（上海）私人有限公司
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

#include "esp_err.h"
#include "esp_serial_slave_link/essl.h"


#ifdef __cplusplus
extern "C"
{
#endif

///ESSL SPI设备的配置
typedef struct {
    spi_device_handle_t *spi;           ///<指向SPI设备句柄的指针。
    uint32_t            tx_buf_size;    ///<主机和从机使用的预先协商的主TX缓冲区大小。
    uint8_t             tx_sync_reg;    ///<主TX从RX同步的预协商寄存器ID。将为同步保留1个字（4字节）。
    uint8_t             rx_sync_reg;    ///<主RX从TX同步的预协商寄存器ID。将为同步保留1个字（4字节）。
} essl_spi_config_t;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// DMA附加模式的API
// 此模式对于连续半双工SPI事务具有更好的性能。
//
// *您可以将“essl_spi_init_dev”和“essl_spi_deinit_dev”与“essl”中的API一起使用。h``通信
//   ESP SPI从设备处于半双工DMA附加模式。请参阅SPI从属半双工应用模式示例。
// *您还可以使用以下API创建自己的逻辑。
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * @brief 初始化ESSL SPI设备功能列表并获取其句柄
 *
 * @param[out] out_handle    手柄输出
 * @param      init_config   ESSL SPI设备的配置
 * @return
 *        -ESP_OK：成功时
 *        -ESP_ERR_NO_MEM:内存耗尽
 *        -ESP_ERR_INVALID_STATE:SPI驱动程序未初始化
 *        -ESP_ERR_INVALID_ARG：错误的寄存器ID
 */
esp_err_t essl_spi_init_dev(essl_handle_t *out_handle, const essl_spi_config_t *init_config);

/**
 * @brief 取消初始化ESSL SPI设备并释放设备使用的内存
 *
 * @param handle    ESSL SPI设备的手柄
 * @return
 *        -ESP_OK：成功时
 *        -ESP_ERR_INVALID_STATE:ESSL SPI未使用
 */
esp_err_t essl_spi_deinit_dev(essl_handle_t handle);

/**
 * @brief 从共享寄存器读取
 *
 * @note 保留主/从同步寄存器。不要使用它们。（请参见“essl_spi_config_t”中的“rx_sync_reg”）
 *
 * @param      arg        组件的上下文。（来自``essl_handle_t``的成员``arg``）
 * @param      addr       共享寄存器的地址。（有效：0~SOC_SPI_MAXIMUM_BUFFER_SIZE，保留M/S同步寄存器，见注释1）。
 * @param[out] out_value  共享寄存器的读取缓冲区。
 * @param      wait_ms    超时前等待的时间（保留供将来使用，用户应将其设置为0）。
 * @return
 *        -ESP_OK：成功
 *        -ESP_ERR_INVALID_STATE:ESSL SPI尚未初始化。
 *        -ESP_ERR_INVALID_ARG:地址参数无效。见注1。
 *        -或来自：cpp:func:`spi_device_transmission`的其他返回值。
 */
esp_err_t essl_spi_read_reg(void *arg, uint8_t addr, uint8_t *out_value, uint32_t wait_ms);

/**
 * @brief 从Slave获取数据包
 *
 * @param      arg         组件的上下文。（来自``essl_handle_t``的成员``arg``）
 * @param[out] out_data    输出数据地址
 * @param      size        输出数据的大小。
 * @param      wait_ms     超时前等待的时间（保留供将来使用，用户应将其设置为0）。
 * @return
 *        -ESP_OK：成功时
 *        -ESP_ERR_INVALID_STATE:ESSL SPI尚未初始化。
 *        -ESP_ERR_INVALID_ARG：输出数据地址既不支持DMA，也不支持4字节对齐
 *        -ESP_ERR_INVALID_SIZE:主设备需要“大小”字节的数据，但从设备没有加载足够的字节。
 */
esp_err_t essl_spi_get_packet(void *arg, void *out_data, size_t size, uint32_t wait_ms);

/**
 * @brief 写入共享寄存器
 *
 * @note 保留主/从同步寄存器。不要使用它们。（请参见“essl_spi_config_t”中的“tx_sync_reg”）
 * @note 不支持检查实际写入值（``out_value``）的功能。
 *
 * @param      arg        组件的上下文。（来自``essl_handle_t``的成员``arg``）
 * @param      addr       共享寄存器的地址。（有效：0~SOC_SPI_MAXIMUM_BUFFER_SIZE，保留M/S同步寄存器，见注释1）
 * @param      value      要发送的数据的缓冲区应与4对齐。
 * @param[out] out_value  不支持，应设置为NULL。
 * @param      wait_ms    超时前等待的时间（保留供将来使用，用户应将其设置为0）。
 * @return
 *        -ESP_OK：成功
 *        -ESP_ERR_INVALID_STATE:ESSL SPI尚未初始化。
 *        -ESP_ERR_INVALID_ARG:地址参数无效。见注1。
 *        -ESP_ERR_NOT_SUPPORTED:应将``out_value``设置为NULL。见注2。
 *        -或来自：cpp:func:`spi_device_transmission`的其他返回值。
 *
 */
esp_err_t essl_spi_write_reg(void *arg, uint8_t addr, uint8_t value, uint8_t *out_value, uint32_t wait_ms);

/**
 * @brief 向从属设备发送数据包
 *
 * @param arg        组件的上下文。（来自``essl_handle_t``的成员``arg``）
 * @param data       要发送的数据的地址
 * @param size       要发送的数据大小。
 * @param wait_ms    超时前等待的时间（保留供将来使用，用户应将其设置为0）。
 * @return
 *        -ESP_OK：成功时
 *        -ESP_ERR_INVALID_STATE:ESSL SPI尚未初始化。
 *        -ESP_ERR_INVALID_ARG：数据地址不支持DMA
 *        -ESP_ERR_INVALID_SIZE:主机将发送“大小”字节的数据，但从机未加载足够的RX缓冲区
 */
esp_err_t essl_spi_send_packet(void *arg, const void *data, size_t size, uint32_t wait_ms);

/**
 * @brief 重置主上下文中的计数器
 *
 * @note 仅当从属设备已重置其计数器时才应调用。否则，从属设备和主设备将不同步
 *
 * @param arg    组件的上下文。（来自``essl_handle_t``的成员``arg``）
 */
void essl_spi_reset_cnt(void *arg);

////////////////////////////////////////////////////////////////////////////////
// 与ESP32-S2上的SPI从属HD通信的基本命令
////////////////////////////////////////////////////////////////////////////////
/**
 * @brief 以ISR方式从从机读取共享缓冲区
 *
 * @note 从设备的硬件不能保证一个SPI事务中的数据是一致的。它以字节为单位发送数据。换句话说，如果当rdbuf SPI事务正在运行时，从属软件试图更新共享寄存器，则主软件获得的数据将是从属软件不同写入的字节的组合。
 *
 * @note ``out_data“”应以文字和DRAM形式准备。DMA可以用字来写入缓冲器。当写入一个字节时，同一单词中的剩余字节也将被覆盖，即使“len”比单词短。
 *
 * @param      spi       代表从属设备的SPI设备句柄
 * @param[out] out_data  用于读取数据的缓冲区，强烈建议位于DRAM中，并与4对齐
 * @param      addr      从属共享缓冲区的地址
 * @param      len       要读取的长度
 * @param      flags     `SPI_TRANS_*`标志，用于控制要发送的事务的事务模式。
 * @return
 *      -ESP_OK：成功时
 *      -或来自：cpp:func:`spi_device_transmission`的其他返回值。
 */
esp_err_t essl_spi_rdbuf(spi_device_handle_t spi, uint8_t *out_data, int addr, int len, uint32_t flags);

/**
 * @brief 以轮询方式从从机读取共享缓冲区
 *
 * @note ``out_data“”应以文字和DRAM形式准备。DMA可以用字来写入缓冲器。当写入一个字节时，同一单词中的剩余字节也将被覆盖，即使“len”比单词短。
 *
 * @param      spi       代表从属设备的SPI设备句柄
 * @param[out] out_data  用于读取数据的缓冲区，强烈建议位于DRAM中，并与4对齐
 * @param      addr      从属共享缓冲区的地址
 * @param      len       要读取的长度
 * @param      flags     `SPI_TRANS_*`标志，用于控制要发送的事务的事务模式。
 * @return
 *      -ESP_OK：成功时
 *      -或来自：cpp:func:`spi_device_transmission`的其他返回值。
 */
esp_err_t essl_spi_rdbuf_polling(spi_device_handle_t spi, uint8_t *out_data, int addr, int len, uint32_t flags);

/**
 * @brief 以ISR方式写入从机的共享缓冲区
 *
 * @note ``out_data“”应以文字和DRAM形式准备。DMA可以用字来写入缓冲器。当写入一个字节时，同一单词中的剩余字节也将被覆盖，即使“len”比单词短。
 *
 * @param spi       代表从属设备的SPI设备句柄
 * @param data      发送数据的缓冲区，强烈建议在DRAM中
 * @param addr      从属共享缓冲器的地址，
 * @param len       要写入的长度
 * @param flags     `SPI_TRANS_*`标志，用于控制要发送的事务的事务模式。
 * @return
 *      -ESP_OK：成功
 *      -或来自：cpp:func:`spi_device_transmission`的其他返回值。
 */
esp_err_t essl_spi_wrbuf(spi_device_handle_t spi, const uint8_t *data, int addr, int len, uint32_t flags);

/**
 * @brief 以轮询方式写入从机的共享缓冲区
 *
 * @note ``out_data“”应以文字和DRAM形式准备。DMA可以用字来写入缓冲器。当写入一个字节时，同一单词中的剩余字节也将被覆盖，即使“len”比单词短。
 *
 * @param spi       代表从属设备的SPI设备句柄
 * @param data      发送数据的缓冲区，强烈建议在DRAM中
 * @param addr      从属共享缓冲器的地址，
 * @param len       要写入的长度
 * @param flags     `SPI_TRANS_*`标志，用于控制要发送的事务的事务模式。
 * @return
 *      -ESP_OK：成功
 *      -或来自：cpp:func:`spi_device_polling_transport`的其他返回值。
 */
esp_err_t essl_spi_wrbuf_polling(spi_device_handle_t spi, const uint8_t *data, int addr, int len, uint32_t flags);

/**
 * @brief 通过DMA从从属设备接收分段的长缓冲区。
 *
 * @note 此函数在末尾结合了多个：cpp:func:`essl_spi_rddma_seg`和一个：cpp:func:` essl_spi_rddma_done`。当从属设备在分段模式下工作时使用。
 *
 * @param      spi       代表从属设备的SPI设备句柄
 * @param[out] out_data  保存接收数据的缓冲区，强烈建议在DRAM中，并与4对齐
 * @param      len       要接收的数据的总长度。
 * @param      seg_len 每个段的长度，不大于spi设备允许的最大事务长度。建议为4的倍数。当设置为<0时，表示在一个段中发送所有数据（仍将发送“rddma_done”）
 * @param flags     `SPI_TRANS_*`标志，用于控制要发送的事务的事务模式。
 * @return
 *      -ESP_OK：成功
 *      -或来自：cpp:func:`spi_device_transmission`的其他返回值。
 */
esp_err_t essl_spi_rddma(spi_device_handle_t spi, uint8_t *out_data, int len, int seg_len, uint32_t flags);

/**
 * @brief 通过DMA从从设备读取一个数据段。
 *
 * @note 要读取长缓冲区，请改为调用：cpp:func:`essl_spi_rddma`。
 *
 * @param      spi       代表从属设备的SPI设备句柄
 * @param[out] out_data  保存接收数据的缓冲区。强烈建议在DRAM中，并与4
 * @param      seg_len   此段的长度
 * @param      flags     `SPI_TRANS_*`标志，用于控制要发送的事务的事务模式。
 * @return
 *      -ESP_OK：成功
 *      -或来自：cpp:func:`spi_device_transmission`的其他返回值。
 */
esp_err_t essl_spi_rddma_seg(spi_device_handle_t spi, uint8_t *out_data, int seg_len, uint32_t flags);

/**
 * @brief 向从属设备发送``rddma_done``命令。收到此命令后，即使有数据未发送，从属设备也将停止发送当前缓冲区，并可能准备发送下一个缓冲区。
 *
 * @note 仅当从属设备在分段模式下工作时，才需要此选项。
 *
 * @param spi       代表从属设备的SPI设备句柄
 * @param flags     `SPI_TRANS_*`标志，用于控制要发送的事务的事务模式。
 * @return
 *      -ESP_OK：成功
 *      -或来自：cpp:func:`spi_device_transmission`的其他返回值。
 */
esp_err_t essl_spi_rddma_done(spi_device_handle_t spi, uint32_t flags);

/**
 * @brief 通过DMA将长缓冲区分段发送给从属设备。
 *
 * @note 此函数在末尾结合了多个：cpp:func:`essl_spi_wrdma_seg`和一个：cpp:func:` essl_spi_wrdma_done`。当从属设备在分段模式下工作时使用。
 *
 * @param spi       代表从属设备的SPI设备句柄
 * @param data      发送数据的缓冲区，强烈建议在DRAM中
 * @param len       要发送的数据的总长度。
 * @param seg_len 每个段的长度，不大于spi设备允许的最大事务长度。建议为4的倍数。当设置为<0时，表示在一个段中发送所有数据（仍将发送“wrdma_done”）
 * @param flags     `SPI_TRANS_*`标志，用于控制要发送的事务的事务模式。
 * @return
 *      -ESP_OK：成功
 *      -或来自：cpp:func:`spi_device_transmission`的其他返回值。
 */
esp_err_t essl_spi_wrdma(spi_device_handle_t spi, const uint8_t *data, int len, int seg_len, uint32_t flags);

/**
 * @brief 通过DMA向从属设备发送一个数据段。
 *
 * @note 要发送长缓冲区，请改为调用：cpp:func:`essl_spi_wrdma`。
 *
 * @param spi       代表从属设备的SPI设备句柄
 * @param data      发送数据的缓冲区，强烈建议在DRAM中
 * @param seg_len   此段的长度
 * @param flags     `SPI_TRANS_*`标志，用于控制要发送的事务的事务模式。
 * @return
 *      -ESP_OK：成功
 *      -或来自：cpp:func:`spi_device_transmission`的其他返回值。
 */
esp_err_t essl_spi_wrdma_seg(spi_device_handle_t spi, const uint8_t *data, int seg_len, uint32_t flags);

/**
 * @brief 向从属设备发送“wrdma_done”命令。收到该命令后，从站将停止接收，处理接收到的数据，并可能准备下一个缓冲区进行接收。
 *
 * @note 仅当从属设备在分段模式下工作时，才需要此选项。
 *
 * @param spi       代表从属设备的SPI设备句柄
 * @param flags     `SPI_TRANS_*`标志，用于控制要发送的事务的事务模式。
 * @return
 *      -ESP_OK：成功
 *      -或来自：cpp:func:`spi_device_transmission`的其他返回值。
 */
esp_err_t essl_spi_wrdma_done(spi_device_handle_t spi, uint32_t flags);

#ifdef __cplusplus
}
#endif

