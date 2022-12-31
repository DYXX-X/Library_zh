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

// ESP SDIO从链路，由ESP主机用于与ESP SDIO从属设备通信。

#pragma once

#include "esp_err.h"
#include "esp_serial_slave_link/essl.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/sdmmc_defs.h"

///ESSL SDIO设备的配置
typedef struct {
    sdmmc_card_t *card;     ///<从设备的初始化sdmmc卡指针。
    int recv_buffer_size;   ///<主机和从机使用的预先协商的recv缓冲区大小。
} essl_sdio_config_t;

/**
 * @brief 初始化ESSL SDIO设备并获取其句柄。
 *
 * @param out_handle 手柄的输出。
 * @param config    ESSL SDIO设备的配置。
 * @return
 *  -ESP_OK：成功时
 *  -ESP_ERR_NO_MEM:内存耗尽。
 */
esp_err_t essl_sdio_init_dev(essl_handle_t *out_handle, const essl_sdio_config_t *config);

/**
 * @brief 取消初始化并释放ESSL SDIO设备使用的空间。
 *
 * @param handle 要卸载的ESSL SDIO设备的句柄。
 * @return
 *  -ESP_OK：成功时
 *  -ESP_ERR_INVALID_ARG：传递了错误的句柄
 */
esp_err_t essl_sdio_deinit_dev(essl_handle_t handle);

//请在不使用“sdio”的情况下调用“essl_”函数，而不是直接调用这些函数。
/**@秒*/
/**
 * ESSL SDIO从设备的SDIO初始化过程。
 *
 * @param arg “essl”组件的上下文。稍后发送到其他功能。
 * @param wait_ms 操作完成前等待的时间，以毫秒为单位。
 *
 * @return
 *      -ESP_OK（如果成功）
 *      -SDMMC主机控制器的错误代码之一
 */
esp_err_t essl_sdio_init(void *arg, uint32_t wait_ms);

/**
 * 等待ESSL SDIO从设备中断。
 *
 * @param arg “essl”组件的上下文。
 * @param wait_ms 操作完成前等待的时间，以毫秒为单位。
 *
 * @return
 *      -ESP_OK（如果成功）
 *      -SDMMC主机控制器的错误代码之一
 */
esp_err_t essl_sdio_wait_for_ready(void *arg, uint32_t wait_ms);

/**
 * 获取主机向从机发送数据的缓冲区编号。缓冲区的大小为“buffer_size”。
 *
 * @param arg 组件的上下文。
 *
 * @return
 *      -ESP_OK成功
 *      -SDMMC主机控制器的错误代码之一
 */
uint32_t essl_sdio_get_tx_buffer_num(void *arg);

/** 获取ESSL SDIO从设备准备发送到主机的数据量。
 *
 * @param arg 组件的上下文。
 *
 * @return
 *      -ESP_OK成功
 *      -SDMMC主机控制器的错误代码之一
 */
uint32_t essl_sdio_get_rx_data_size(void *arg);

/**
 * 向ESSL SDIO从设备发送数据包。从设备将数据包接收到缓冲区中，缓冲区的大小为arg中的“buffer_size”。
 *
 * @param arg 组件的上下文。
 * @param start 要发送的数据包的起始地址
 * @param length 要发送的数据长度，如果数据包过大，它将被分成块并自动保存到不同的缓冲区中。
 * @param wait_ms 超时前等待的时间，以毫秒为单位。
 *
 * @return
 *      -ESP_OK成功
 *      -ESP_ERR_TIMEOUT无缓冲区可使用，或SDMMC主机控制器出错
 *      -SDMMC主机控制器的错误代码之一
 */
esp_err_t essl_sdio_send_packet(void *arg, const void *start, size_t length, uint32_t wait_ms);

/**
 * 从ESSL SDIO从设备获取数据包。
 *
 * @param arg 组件的上下文。
 * @param[out] out_data 数据输出地址
 * @param size 输出缓冲区的大小，如果缓冲区小于要从从属设备接收的数据大小，则驱动程序返回``ESP_ERR_NOT_FINISHED``
 * @param wait_ms 超时前等待的时间，以毫秒为单位。
 *
 * @return
 *     -ESP_OK成功，从从机读取所有数据。
 *     -ESP_ERR_NOT_FINISHED读取成功，但仍有数据。
 *     -SDMMC主机控制器的错误代码之一
 */
esp_err_t essl_sdio_get_packet(void *arg, void *out_data, size_t size, uint32_t wait_ms);

/**
 * 等待来自SDIO从属设备的中断。
 *
 * @param arg 组件的上下文。
 * @param wait_ms 超时前等待的时间，以毫秒为单位。
 * @return
 *  -ESP_ERR_NOT_SUPPORTED：如果中断线未正确初始化。
 *  -ESP_OK：如果发生中断
 *  -ESP_ERR_TIMEOUT：如果发生中断前超时。
 *  -或从“card->host”结构的“io_int_wait”成员返回的其他值。
 */
esp_err_t essl_sdio_wait_int(void *arg, uint32_t wait_ms);

/**
 * 清除ESSL SDIO从设备的中断位。掩码中设置的所有位将被清除，而其他位将保持不变。
 *
 * @param arg 组件的上下文。
 * @param intr_mask 要清除的中断位掩码。
 * @param wait_ms 超时前等待的时间，以毫秒为单位。
 *
 * @return
 *      -ESP_OK成功
 *      -SDMMC主机控制器的错误代码之一
 */
esp_err_t essl_sdio_clear_intr(void *arg, uint32_t intr_mask, uint32_t wait_ms);

/**
 * 获取ESSL SDIO从设备的中断位。
 *
 * @param arg 组件的上下文。
 * @param intr_raw 原始中断位的输出。如果仅读取掩码位，则设置为NULL。
 * @param intr_st 屏蔽中断位的输出。如果仅读取原始位，则设置为NULL。
 * @param wait_ms 超时前等待的时间，以毫秒为单位。
 *
 * @return
 *      -ESP_OK成功
 *      -如果“intr_raw”和“intr_st”都为NULL，则返回ESP_INVALID_ARG。
 *      -SDMMC主机控制器的错误代码之一
 */
esp_err_t essl_sdio_get_intr(void *arg, uint32_t *intr_raw, uint32_t *intr_st, uint32_t wait_ms);

/**
 * 设置ESSL SDIO从设备的中断启用位。当原始状态和启用设置都有一位时，从设备仅在线路上发送中断。
 *
 * @param arg 组件的上下文。
 * @param ena_mask 要启用的中断位掩码。
 * @param wait_ms 超时前等待的时间，以毫秒为单位。
 *
 * @return
 *      -ESP_OK成功
 *      -SDMMC主机控制器的错误代码之一
 */
esp_err_t essl_sdio_set_intr_ena(void *arg, uint32_t ena_mask, uint32_t wait_ms);

/**
 * 获取ESSL SDIO从设备的中断启用位。
 *
 * @param arg 组件的上下文。
 * @param ena_mask_o 中断位启用掩码的输出。
 * @param wait_ms 超时前等待的时间，以毫秒为单位。
 *
 * @return
 *      -ESP_OK成功
 *      -SDMMC主机控制器的错误代码之一
 */
esp_err_t essl_sdio_get_intr_ena(void *arg, uint32_t *ena_mask_o, uint32_t wait_ms);

/**
 * 写入ESSL SDIO从设备的通用R/W寄存器（8位）。
 *
 * @param arg 组件的上下文。
 * @param addr 要写入的寄存器地址。有效地址：0-27，32-63（28-31保留）。
 * @param value 要写入寄存器的值。
 * @param wait_ms 超时前等待的时间，以毫秒为单位。
 *
 * @return
 *      -ESP_OK成功
 *      -ESP_ERR_INVALID_ARG地址无效。
 *      -SDMMC主机控制器的错误代码之一
 */
esp_err_t essl_sdio_write_reg(void *arg, uint8_t addr, uint8_t value, uint8_t *value_o, uint32_t wait_ms);

/**
 * 读取ESSL SDIO从设备的通用R/W寄存器（8位）。
 *
 * @param arg 组件的上下文。
 * @param add 要读取的寄存器地址。有效地址：0-27，32-63（28-31保留，读取时返回中断位）。
 * @param value 从寄存器读取的输出值。
 * @param wait_ms 超时前等待的时间，以毫秒为单位。
 *
 * @return
 *      -ESP_OK成功
 *      -ESP_ERR_INVALID_ARG地址无效。
 *      -SDMMC主机控制器的错误代码之一
 */
esp_err_t essl_sdio_read_reg(void *arg, uint8_t add, uint8_t *value_o, uint32_t wait_ms);

/**
 * 向从属设备发送中断。中断的每一位都将被触发。
 *
 * @param arg 组件的上下文。
 * @param intr_mask 要发送到从属设备的中断位掩码。
 * @param wait_ms 超时前等待的时间，以毫秒为单位。
 *
 * @return
 *      -ESP_OK成功
 *      -SDMMC主机控制器的错误代码之一
 */
esp_err_t essl_sdio_send_slave_intr(void *arg, uint32_t intr_mask, uint32_t wait_ms);

/**
 * @brief 重置主机侧的计数器。
 *
 * @note 只有当您知道从属设备已重置其计数器时，才能调用，否则主设备和从属设备之间将不一致。
 *
 * @param arg  组件的上下文。
 */
void essl_sdio_reset_cnt(void *arg);

/**@结束秒*/

