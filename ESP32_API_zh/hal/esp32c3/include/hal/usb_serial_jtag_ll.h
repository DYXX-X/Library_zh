// 版权所有2021 Espressif Systems（上海）
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

// USB串行jtag控制器的LL层

#pragma once
#include "soc/usb_serial_jtag_reg.h"
#include "soc/usb_serial_jtag_struct.h"

#ifdef __cplusplus
extern "C" {
#endif

//输入和输出端点如此长。
#define USB_SERIAL_JTAG_PACKET_SZ_BYTES 64

#define USB_SERIAL_JTAG_LL_INTR_MASK         (0x7ffff) //所有中断掩码

// 定义USB_SERIAL_JTAG中断
// 注意，硬件有更多的中断，但它们只对调试有用
// 硬件。
typedef enum {
    USB_SERIAL_JTAG_INTR_SOF                    = (1 << 1),
    USB_SERIAL_JTAG_INTR_SERIAL_OUT_RECV_PKT    = (1 << 2),
    USB_SERIAL_JTAG_INTR_SERIAL_IN_EMPTY        = (1 << 3),
    USB_SERIAL_JTAG_INTR_TOKEN_REC_IN_EP1       = (1 << 8),
    USB_SERIAL_JTAG_INTR_BUS_RESET              = (1 << 9),
    USB_SERIAL_JTAG_INTR_EP1_ZERO_PAYLOAD       = (1 << 10),
} usb_serial_jtag_ll_intr_t;

/**
 * @brief  基于给定掩码启用USB_SERIAL_JTAG中断。
 *
 * @param  mask 需要启用中断位图。
 *
 * @return 没有一个
 */
static inline void usb_serial_jtag_ll_ena_intr_mask(uint32_t mask)
{
    USB_SERIAL_JTAG.int_ena.val |= mask;
}

/**
 * @brief  基于给定掩码禁用USB_SERIAL_JTAG中断。
 *
 * @param  mask 需要禁用中断位图。
 *
 * @return 没有一个
 */
static inline void usb_serial_jtag_ll_disable_intr_mask(uint32_t mask)
{
    USB_SERIAL_JTAG.int_ena.val &= (~mask);
}

/**
 * @brief  获取USB_SERIAL_JTAG中断状态。
 *
 * @return USB_SERIAL_JTAG中断状态。
 */
static inline uint32_t usb_serial_jtag_ll_get_intsts_mask(void)
{
    return USB_SERIAL_JTAG.int_st.val;
}

/**
 * @brief  根据给定掩码清除USB_SERIAL_JTAG中断状态。
 *
 * @param  mask 需要清除中断位图。
 *
 * @return 没有一个
 */
static inline void usb_serial_jtag_ll_clr_intsts_mask(uint32_t mask)
{
    USB_SERIAL_JTAG.int_clr.val = mask;
}

/**
 * @brief  获取已启用中断的状态。
 *
 * @return 中断使能值
 */
static inline uint32_t usb_serial_jtag_ll_get_intr_ena_status(void)
{
    return USB_SERIAL_JTAG.int_ena.val;
}

/**
 * @brief  从USB_SERIAL_JTAG rxfifo读取字节。
 *
 * @param  buf 数据缓冲区。
 * @param  rd_len 需要读取数据长度。
 *
 * @return 读取的字节数
 */
static inline int usb_serial_jtag_ll_read_rxfifo(uint8_t *buf, uint32_t rd_len)
{
    int i;
    for (i = 0; i < (int)rd_len; i++) {
        if (!USB_SERIAL_JTAG.ep1_conf.serial_out_ep_data_avail) break;
        buf[i] = USB_SERIAL_JTAG.ep1.rdwr_byte;
    }
    return i;
}

/**
 * @brief  将字节写入USB_SERIAL_JTAG txfifo。如果缓冲区中有空间，则只写入长度为/的字节。
 *
 * @param  buf 数据缓冲区。
 * @param  wr_len 数据长度需要写入。
 *
 * @return 实际写入的字节数。可能小于wr_len。
 */
static inline int usb_serial_jtag_ll_write_txfifo(const uint8_t *buf, uint32_t wr_len)
{
    int i;
    for (i = 0; i < (int)wr_len; i++) {
        if (!USB_SERIAL_JTAG.ep1_conf.serial_in_ep_data_free) break;
        USB_SERIAL_JTAG.ep1.rdwr_byte = buf[i];
    }
    return i;
}

/**
 * @brief  如果USB_SERIAL_JTAG rxfifo具有可用数据，则返回1。
 *
 * @return 如果没有可用数据，则为0；如果数据可用，则为1
 */
static inline int usb_serial_jtag_ll_rxfifo_data_available(void)
{
    return USB_SERIAL_JTAG.ep1_conf.serial_out_ep_data_avail;
}

/**
 * @brief  如果USB_SERIAL_JTAG txfifo有空间，则返回1。
 *
 * @return 如果没有可用数据，则为0；如果数据可用，则为1
 */
static inline int usb_serial_jtag_ll_txfifo_writable(void)
{
    return USB_SERIAL_JTAG.ep1_conf.serial_in_ep_data_free;
}

/**
 * @brief  刷新TX缓冲区，即使其可供主机拾取。
 *
 * @note  当fifo已满（64字节）时，HW将自动刷新缓冲区。如果fifo中没有任何内容，它将不会被执行。
 *
 * @return 纳
 */
static inline void usb_serial_jtag_ll_txfifo_flush(void)
{
    USB_SERIAL_JTAG.ep1_conf.wr_done=1;
}


#ifdef __cplusplus
}
#endif

