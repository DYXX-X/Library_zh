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

#pragma once

#include "sdmmc_cmd.h"
#include "driver/spi_master.h"
#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"


struct essl_dev_t;
///ESSL设备的手柄
typedef struct essl_dev_t* essl_handle_t;

/**
 * @brief 初始化从属设备。
 *
 * @param handle ESSL设备的手柄。
 * @param wait_ms 毫秒在超时前等待，如果设置为0-9，则根本不会等待。
 * @return
 *        -ESP_OK：如果成功
 *        -ESP_ERR_NOT_SUPPORTED：当前设备不支持此功能。
 *        -从下层“init”返回的其他值。
 */
esp_err_t essl_init(essl_handle_t handle, uint32_t wait_ms);

/** 等待ESSL从设备中断。
 *
 * @param handle ESSL设备的手柄。
 * @param wait_ms 毫秒在超时前等待，如果设置为0-9，则根本不会等待。
 *
 * @return
 *      -ESP_OK：如果成功
 *      -ESP_ERR_NOT_SUPPORTED：当前设备不支持此功能。
 *      -SDMMC主机控制器的错误代码之一
 */
esp_err_t essl_wait_for_ready(essl_handle_t handle, uint32_t wait_ms);

/** 获取主机向从机发送数据的缓冲区编号。缓冲区的大小为“buffer_size”。
 *
 * @param handle ESSL设备的手柄。
 * @param out_tx_num 主机可以向ESSL从机发送数据的缓冲区编号的输出。
 * @param wait_ms 毫秒在超时前等待，如果设置为0-9，则根本不会等待。
 *
 * @return
 *      -ESP_OK：成功
 *      -ESP_ERR_NOT_SUPPORTED:此模式不支持此API
 *      -SDMMC/SPI主机控制器的错误代码之一
 */
esp_err_t essl_get_tx_buffer_num(essl_handle_t handle, uint32_t *out_tx_num, uint32_t wait_ms);

/** 获取ESSL从设备准备发送的数据的大小（以字节为单位）
 *
 * @param handle ESSL设备的手柄。
 * @param out_rx_size 从从设备读取的数据大小输出（字节）
 * @param wait_ms 毫秒在超时前等待，如果设置为0-9，则根本不会等待。
 *
 * @return
 *      -ESP_OK：成功
 *      -ESP_ERR_NOT_SUPPORTED:此模式不支持此API
 *      -SDMMC/SPI主机控制器的错误代码之一
 */
esp_err_t essl_get_rx_data_size(essl_handle_t handle, uint32_t *out_rx_size, uint32_t wait_ms);


/** 重置此组件的计数器。通常，除非您知道从属设备已重置，否则不需要执行此操作。
 *
 * @param handle ESSL设备的手柄。
 *
 * @return
 *        -ESP_OK：成功
 *        -ESP_ERR_NOT_SUPPORTED:此模式不支持此API
 *        -ESP_ERR_INVALID_ARG:参数无效，句柄不是init。
 */
esp_err_t essl_reset_cnt(essl_handle_t handle);

/** 向ESSL从站发送数据包。从设备将数据包接收到大小为“buffer_size”（在初始化期间配置）的缓冲区中。
 *
 * @param handle ESSL设备的手柄。
 * @param start 要发送的数据包的起始地址
 * @param length 要发送的数据长度，如果数据包过大，它将被分成块并自动保存到不同的缓冲区中。
 * @param wait_ms 毫秒在超时前等待，如果设置为0-9，则根本不会等待。
 *
 * @return
 *      -ESP_OK成功
 *      -ESP_ERR_INVALID_ARG：参数无效，句柄不是init或其他参数无效。
 *      -ESP_ERR_TIMEOUT：无缓冲区可供使用，或SDMMC主机控制器出错。
 *      -ESP_ERR_NOT_FOUND：从机未准备好接收。
 *      -ESP_ERR_NOT_SUPPORTED:此模式不支持此API
 *      -SDMMC/SPI主机控制器的错误代码之一。
 */
esp_err_t essl_send_packet(essl_handle_t handle, const void *start, size_t length, uint32_t wait_ms);

/** 从ESSL从属设备获取数据包。
 *
 * @param handle ESSL设备的手柄。
 * @param[out] out_data 数据输出地址
 * @param size 输出缓冲区的大小，如果缓冲区小于要从从属设备接收的数据大小，则驱动程序返回``ESP_ERR_NOT_FINISHED``
 * @param[out] out_length 实际从从设备接收的数据的长度输出。
 * @param wait_ms 毫秒在超时前等待，如果设置为0-9，则根本不会等待。
 *
 * @return
 *     -ESP_OK成功：所有数据都已从从机读取。
 *     -ESP_ERR_INVALID_ARG：参数无效，句柄未初始化或其他参数无效。
 *     -ESP_ERR_NOT_FINISHED：读取成功，但仍有数据剩余。
 *     -ESP_ERR_NOT_FOUND：从机未准备好发送数据。
 *     -ESP_ERR_NOT_SUPPORTED:此模式不支持此API
 *     -SDMMC/SPI主机控制器的错误代码之一。
 */
esp_err_t essl_get_packet(essl_handle_t handle, void *out_data, size_t size, size_t *out_length, uint32_t wait_ms);

/** 写入ESSL从设备的通用R/W寄存器（8位）。
 *
 * @param handle ESSL设备的手柄。
 * @param addr 要写入的寄存器地址。对于SDIO，有效地址：0-59。对于SPI，请参阅``essl_SPI.h``
 * @param value 要写入寄存器的值。
 * @param value_o 返回的写入值的输出。
 * @param wait_ms 毫秒在超时前等待，如果设置为0-9，则根本不会等待。
 *
 * @note sdio 28-31被保留，较低的API有助于跳过。
 *
 * @return
 *      -ESP_OK成功
 *      -SDMMC/SPI主机控制器的错误代码之一
 */
esp_err_t essl_write_reg(essl_handle_t handle, uint8_t addr, uint8_t value, uint8_t *value_o, uint32_t wait_ms);

/** 读取ESSL从设备的通用R/W寄存器（8位）。
 *
 * @param handle “essl”设备的句柄。
 * @param add 要读取的寄存器地址。对于SDIO，有效地址：0-27，32-63（28-31保留，读取时返回中断位）。有关SPI，请参见``essl_SPI.h``
 * @param value_o 从寄存器读取的输出值。
 * @param wait_ms 毫秒在超时前等待，如果设置为0-9，则根本不会等待。
 *
 * @return
 *      -ESP_OK成功
 *      -SDMMC/SPI主机控制器的错误代码之一
 */
esp_err_t essl_read_reg(essl_handle_t handle, uint8_t add, uint8_t *value_o, uint32_t wait_ms);

/** 等待从属设备的中断
 *
 * @param handle ESSL设备的手柄。
 * @param wait_ms 毫秒在超时前等待，如果设置为0-9，则根本不会等待。
 *
 * @return
 *        -ESP_OK：如果触发中断。
 *        -ESP_ERR_NOT_SUPPORTED：当前设备不支持此功能。
 *        -ESP_ERR_TIMEOUT：超时前没有中断。
 */
esp_err_t essl_wait_int(essl_handle_t handle, uint32_t wait_ms);

/** 清除ESSL从站的中断位。掩码中设置的所有位将被清除，而其他位将保持不变。
 *
 * @param handle ESSL设备的手柄。
 * @param intr_mask 要清除的中断位掩码。
 * @param wait_ms 毫秒在超时前等待，如果设置为0-9，则根本不会等待。
 *
 * @return
 *        -ESP_OK：成功
 *        -ESP_ERR_NOT_SUPPORTED：当前设备不支持此功能。
 *        -SDMMC主机控制器的错误代码之一
 */
esp_err_t essl_clear_intr(essl_handle_t handle, uint32_t intr_mask, uint32_t wait_ms);

/** 获取ESSL从设备的中断位。
 *
 * @param handle ESSL设备的手柄。
 * @param intr_raw 原始中断位的输出。如果仅读取掩码位，则设置为NULL。
 * @param intr_st 屏蔽中断位的输出。如果仅读取原始位，则设置为NULL。
 * @param wait_ms 毫秒在超时前等待，如果设置为0-9，则根本不会等待。
 *
 * @return
 *        -ESP_OK：成功
 *        -ESP_INVALID_ARG：如果“intr_raw”和“intr_st”都为NULL。
 *        -ESP_ERR_NOT_SUPPORTED：当前设备不支持此功能。
 *        -SDMMC主机控制器的错误代码之一
 */
esp_err_t essl_get_intr(essl_handle_t handle, uint32_t *intr_raw, uint32_t *intr_st, uint32_t wait_ms);

/** 设置ESSL从设备的中断启用位。当原始状态和启用设置都有一位时，从设备仅在线路上发送中断。
 *
 * @param handle ESSL设备的手柄。
 * @param ena_mask 要启用的中断位掩码。
 * @param wait_ms 毫秒在超时前等待，如果设置为0-9，则根本不会等待。
 *
 * @return
 *        -ESP_OK：成功
 *        -ESP_ERR_NOT_SUPPORTED：当前设备不支持此功能。
 *        -SDMMC主机控制器的错误代码之一
 */
esp_err_t essl_set_intr_ena(essl_handle_t handle, uint32_t ena_mask, uint32_t wait_ms);

/** 获取ESSL从设备的中断启用位。
 *
 * @param handle ESSL设备的手柄。
 * @param ena_mask_o 中断位启用掩码的输出。
 * @param wait_ms 毫秒在超时前等待，如果设置为0-9，则根本不会等待。
 *
 * @return
 *      -ESP_OK成功
 *      -SDMMC主机控制器的错误代码之一
 */
esp_err_t essl_get_intr_ena(essl_handle_t handle, uint32_t *ena_mask_o, uint32_t wait_ms);

/** 向从属设备发送中断。中断的每一位都将被触发。
 *
 * @param handle ESSL设备的手柄。
 * @param intr_mask 要发送到从属设备的中断位掩码。
 * @param wait_ms 毫秒在超时前等待，如果设置为0-9，则根本不会等待。
 *
 * @return
 *        -ESP_OK：成功
 *        -ESP_ERR_NOT_SUPPORTED：当前设备不支持此功能。
 *        -SDMMC主机控制器的错误代码之一
 */
esp_err_t essl_send_slave_intr(essl_handle_t handle, uint32_t intr_mask, uint32_t wait_ms);

