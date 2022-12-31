/*
 * SPDX文件版权文本：2015-2021浓缩咖啡系统（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */

#pragma once

#include "freertos/FreeRTOS.h"
#include "esp_err.h"
#include "sys/queue.h"

#include "hal/sdio_slave_types.h"
#include "soc/sdio_slave_periph.h"

#ifdef __cplusplus
extern "C" {
#endif

#define SDIO_SLAVE_RECV_MAX_BUFFER  (4096-4)

typedef void(*sdio_event_cb_t)(uint8_t event);


///SDIO从站配置
typedef struct {
    sdio_slave_timing_t timing;             ///<sdio_slave的计时。请参见“sdio_slave_timeng_t”。
    sdio_slave_sending_mode_t sending_mode; ///<sdio_slave模式`SDIO_SLAVE_MODE_STREAM`如果需要尽可能多地发送数据`SDIO_SLAVE_MODE_PACKET`如果数据应以数据包形式发送。
    int                 send_queue_size;    ///<发送前可排队的最大缓冲区。
    size_t              recv_buffer_size;
                            ///<如果buffer_size太小，则需要更多的CPU时间来处理更多的缓冲区。
                            ///<如果buffer_size太大，则大于事务长度的空间保留为空，但仍会计算缓冲区，缓冲区很容易用完。
                            ///<应根据实际传输的数据长度设置。
                            ///<所有未完全填充缓冲区的数据仍算作一个缓冲区。E、 g.如果每个缓冲区的大小为8字节，则10字节的数据需要2个缓冲区。
                            ///<通信前主机和从机之间预定义的从机缓冲区大小。给驱动程序的所有接收缓冲区应大于此值。
    sdio_event_cb_t     event_cb;           ///<当主机中断从机时，将使用中断号（0-7）调用此回调。
    uint32_t            flags; ///<要为从属设备启用的功能，``SDIO_slave_FLAG_*``的组合。
#define SDIO_SLAVE_FLAG_DAT2_DISABLED       BIT(0)      /**< SD规范要求，即使在1位模式或SPI模式下，也应使用所有4条数据线并将其上拉。然而，作为一个特征，用户可以指定该标志以在1位模式下使用DAT2引脚。请注意，主机无法读取CCCR寄存器，知道我们不再支持4位模式，请自行承担风险。
        */
#define SDIO_SLAVE_FLAG_HOST_INTR_DISABLED  BIT(1)      /**< DAT1线用作SDIO协议中的中断线。然而，作为一个特征，用户可以指定该标志以在1位模式下使用从设备的DAT1引脚。注意，主机必须对中断寄存器进行轮询，以了解是否有来自从机的中断。它无法读取CCCR寄存器，知道我们不再支持4位模式，请自行承担风险。
        */
#define SDIO_SLAVE_FLAG_INTERNAL_PULLUP     BIT(2)      /**< 为已启用的引脚启用内部上拉。SD规范要求，即使在1位模式或SPI模式下，所有4条数据线也应上拉。注意，内部上拉不足以稳定通信，请在总线上连接外部上拉。这仅用于示例和调试。
        */
} sdio_slave_config_t;

/** 接收缓冲区的句柄，通过调用``sdio_slave_recv_register_buf``注册句柄。使用句柄将缓冲区加载到驱动程序，如果不再使用，则调用``sdio_slave_recv_unregister_buf``。
 */
typedef void *sdio_slave_buf_handle_t;

/** 初始化sdio从属驱动程序
 *
 * @param config sdio从属驱动程序的配置。
 *
 * @return
 *     -如果未找到空闲中断，则返回ESP_ERR_NOT_FOUND。
 *     -ESP_ERR_INVALID_STATE（如果已初始化）。
 *     -如果由于内存分配失败而失败，则为ESP_ERR_NO_MEM。
 *     -ESP_OK（如果成功）
 */
esp_err_t sdio_slave_initialize(sdio_slave_config_t *config);

/** 取消初始化sdio从属驱动程序以释放资源。
 */
void sdio_slave_deinit(void);

/** 启动发送和接收硬件，并将IOREADY1设置为1。
 *
 * @note 驱动程序将继续从以前的数据发送和PKT_LEN计数，保持数据接收以及从当前TOKEN1计数开始接收。请参见`sdio_slave_reset``。
 *
 * @return
 *  -ESP_ERR_INVALID_STATE（如果已启动）。
 *  -否则为ESP_OK。
 */
esp_err_t sdio_slave_start(void);

/** 停止硬件发送和接收，同时将IOREADY1设置为0。
 *
 * @note 这将不会清除驱动器中已经存在的数据，也不会重置PKT_LEN和TOKEN1计数。调用``sdio_slave_reset``执行此操作。
 */
void sdio_slave_stop(void);

/** 清除驱动程序中的数据，并重置PKT_LEN和TOKEN1计数。
 *
 * @return 始终返回ESP_OK。
 */
esp_err_t sdio_slave_reset(void);

/*---------------------------------------------------------------------------
 *                  接收
 *--------------------------------------------------------------------------*/
/** 用于接收的寄存器缓冲区。所有缓冲区都应该在使用前注册，然后可以通过返回的句柄在驱动程序中使用（再次）。
 *
 * @param start 缓冲区的起始地址。
 *
 * @note 驱动程序将使用并且仅使用在“sdio_slave_config_t”中设置的“recv_buffer_size”成员中指定的空间量。所有缓冲区应大于此值。缓冲区由DMA使用，因此它应该具有DMA能力，并且32位对齐。
 *
 * @return 缓冲区句柄（如果成功），否则为NULL。
 */
sdio_slave_buf_handle_t sdio_slave_recv_register_buf(uint8_t *start);

/** 从驱动程序中注销缓冲区，并释放指向缓冲区的描述符所使用的空间。
 *
 * @param handle 要释放的缓冲区句柄。
 *
 * @return 如果成功，则ESP_OK；如果句柄为NULL或正在使用缓冲区，则ESP_ERR_INVALID_ARG。
 */
esp_err_t sdio_slave_recv_unregister_buf(sdio_slave_buf_handle_t handle);

/** 将缓冲区加载到等待接收数据的队列。驱动程序获取缓冲区的所有权，直到事务完成后“sdio_slave_send_get_finished”返回缓冲区。
 *
 * @param handle 准备接收数据的缓冲区句柄。
 *
 * @return
 *     -如果句柄无效或缓冲区已在队列中，则返回ESP_ERR_INVALID_ARG。只有在缓冲区由`sdio_slave_recv``重新获取后，才能再次加载它。
 *     -ESP_OK（如果成功）
 */
esp_err_t sdio_slave_recv_load_buf(sdio_slave_buf_handle_t handle);

/** 如果存在数据包信息，则获取接收数据的缓冲区。驱动程序将缓冲区的所有权返回给应用程序。
 *
 * 当您看到返回值为``ESP_ERR_NOT_FINISHED``时，应迭代调用此API，直到返回值为` `ESP_OK``。用``ESP_ERR_NOT_FINISHED`返回的所有连续缓冲区，连同用`ESP_OK`返回的最后一个缓冲区，都属于来自主机的一个数据包。
 *
 * 如果主机发送的数据从未超过接收缓冲区大小，或者您不关心数据包边界（例如，数据仅为字节流），则可以调用更简单的“sdio_slave_recv”。
 *
 * @param handle_ret 保存接收数据的缓冲区的句柄。在``sdio_slave_recv_load_buf（）``中使用此句柄再次在同一缓冲区中接收。
 * @param wait 接收数据之前等待的时间。
 *
 * @note 使用句柄调用``sdio_slave_load_buf``，将缓冲区重新加载到链接列表中，然后再次使用相同的缓冲区进行接收。此处获得的缓冲区地址和长度与从“sdio_slave_get_buffer”获得的相同。
 *
 * @return
 *     -如果handle_ret为空，则为ESP_ERR_INVALID_ARG
 *     -ESP_ERR_TIMEOUT（如果在接收新数据之前超时）
 *     -ESP_ERR_NOT_FINISHED如果返回的缓冲区不是来自主机的数据包的结尾，则应再次调用此API，直到数据包结束
 *     -ESP_OK（如果成功）
 */
esp_err_t sdio_slave_recv_packet(sdio_slave_buf_handle_t* handle_ret, TickType_t wait);

/** 获取接收到的数据（如果存在）。驱动程序将缓冲区的所有权返回给应用程序。
 *
 * @param handle_ret 保存接收数据的缓冲区句柄。在``sdio_slave_recv_load_buf``中使用此句柄，再次在同一缓冲区中接收。
 * @param[out] out_addr 起始地址的输出，如果不需要，则设置为NULL。
 * @param[out] out_len 缓冲区中数据的实际长度，如果不需要，则设置为NULL。
 * @param wait 接收数据之前等待的时间。
 *
 * @note 使用句柄调用``sdio_slave_load_buf``，将缓冲区重新加载到链接列表中，然后再次使用相同的缓冲区进行接收。此处获得的缓冲区地址和长度与从“sdio_slave_get_buffer”获得的相同。
 *
 * @return
 *     -如果handle_ret为空，则为ESP_ERR_INVALID_ARG
 *     -ESP_ERR_TIMEOUT（如果在接收新数据之前超时）
 *     -ESP_OK（如果成功）
 */
esp_err_t sdio_slave_recv(sdio_slave_buf_handle_t* handle_ret, uint8_t **out_addr, size_t *out_len, TickType_t wait);

/** 检索与句柄对应的缓冲区。
 *
 * @param handle 获取缓冲区的句柄。
 * @param len_o 缓冲区长度输出
 *
 * @return 如果成功，则为缓冲区地址，否则为NULL。
 */
uint8_t* sdio_slave_recv_get_buf(sdio_slave_buf_handle_t handle, size_t *len_o);

/*---------------------------------------------------------------------------
 *                  邮寄
 *--------------------------------------------------------------------------*/
/** 将新的发送传输放入发送队列。驱动程序获取缓冲区的所有权，直到事务完成后“sdio_slave_send_get_finished”返回缓冲区。
 *
 * @param addr 要发送的数据的地址。缓冲区应支持DMA，并与32位对齐。
 * @param len 数据长度不应超过4092字节（将来可能支持更长的数据长度）。
 * @param arg 在``sdio_slave_send_get_finished``中返回的参数。该参数可用于指示完成了哪个事务，或作为回调的参数。如果不需要，则设置为NULL。
 * @param wait 缓冲区已满时等待的时间。
 *
 * @return
 *     -如果长度不大于0，则返回ESP_ERR_INVALID_ARG。
 *     -ESP_ERR_TIMEOUT（如果队列在超时之前仍满）。
 *     -如果成功，则返回ESP_OK。
 */
esp_err_t sdio_slave_send_queue(uint8_t* addr, size_t len, void* arg, TickType_t wait);

/** 返回已完成交易的所有权。
 * @param out_arg 已完成事务的参数。如果未使用，则设置为NULL。
 * @param wait 如果没有完成发送事务，则需要等待。
 *
 * @return 如果未完成任何事务，则为ESP_ERR_TIMEOUT；如果成功，则为ESP _OK。
 */
esp_err_t sdio_slave_send_get_finished(void** out_arg, TickType_t wait);

/** 开始新的发送传输，并等待它（被阻止）完成。
 *
 * @param addr 要发送的缓冲区的起始地址
 * @param len 要发送的缓冲区长度。
 *
 * @return
 *     -如果描述符的长度不大于0，则返回ESP_ERR_INVALID_ARG。
 *     -如果队列已满或主机未在超时前启动传输，则返回ESP_ERR_TIMEOUT。
 *     -如果成功，则返回ESP_OK。
 */
esp_err_t sdio_slave_transmit(uint8_t* addr, size_t len);

/*---------------------------------------------------------------------------
 *                  主办
 *--------------------------------------------------------------------------*/
/** 读取与主机共享的spi从属寄存器。
 *
 * @param pos 寄存器地址为0-27或32-63。
 *
 * @note 寄存器28至31被保留用于中断向量。
 *
 * @return 寄存器的值。
 */
uint8_t sdio_slave_read_reg(int pos);

/** 写入与主机共享的spi从属寄存器。
 *
 * @param pos 寄存器地址0-11、14-15、18-19、24-27和32-63，其他地址被保留。
 * @param reg 要写入的值。
 *
 * @note 寄存器29和31用于中断向量。
 *
 * @return 如果地址错误，则为ESP_ERR_INVALID_ARG，否则为ESP_OK。
 */
esp_err_t sdio_slave_write_reg(int pos, uint8_t reg);

/** 获取主机的中断启用。
 *
 * @return 中断掩码。
 */
sdio_slave_hostint_t sdio_slave_get_host_intena(void);

/** 设置主机的中断启用。
 *
 * @param mask 启用主机中断掩码。
 */
void sdio_slave_set_host_intena(sdio_slave_hostint_t mask);

/** 通过通用中断中断主机。
 *
 * @param pos 中断编号，0-7。
 *
 * @return
 *     -如果中断num错误，则为ESP_ERR_INVALID_ARG
 *     -否则ESP_OK
 */
esp_err_t sdio_slave_send_host_int(uint8_t pos);

/** 清除主机的通用中断。
 *
 * @param mask 要清除的中断位，按位掩码。
 */
void sdio_slave_clear_host_int(sdio_slave_hostint_t mask);

/** 等待来自主机的通用中断。
 *
 * @param pos 要等待的中断源编号。设置。
 * @param wait 在触发中断之前等待的时间。
 *
 * @note 这将同时清除中断。
 *
 * @return 如果成功，则ESP_OK；如果超时，则ESP_ERR_TIMEOUT。
 */
esp_err_t sdio_slave_wait_int(int pos, TickType_t wait);


#ifdef __cplusplus
}
#endif

