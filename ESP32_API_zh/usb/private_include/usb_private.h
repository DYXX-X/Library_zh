/*
 * SPDX文件版权文本：2015-2021浓缩咖啡系统（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */

#pragma once

#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>
#include <sys/queue.h>
#include "usb/usb_types_ch9.h"
#include "usb/usb_types_stack.h"

#ifdef __cplusplus
extern "C" {
#endif

// ------------------------------------------------------类型--------------------------------------------------------

typedef struct {
    uint8_t *data_buffer;
    size_t data_buffer_size;
    int num_bytes;
    int actual_num_bytes;
    uint32_t flags;
    usb_device_handle_t device_handle;
    uint8_t bEndpointAddress;
    usb_transfer_status_t status;
    uint32_t timeout;
    usb_transfer_cb_t callback;
    void *context;
    int num_isoc_packets;
    usb_isoc_packet_desc_t isoc_packet_desc[0];
} usb_transfer_dummy_t;
_Static_assert(sizeof(usb_transfer_dummy_t) == sizeof(usb_transfer_t), "usb_transfer_dummy_t does not match usb_transfer_t");

struct urb_s{
    TAILQ_ENTRY(urb_s) tailq_entry;
    //HCD处理程序指针和变量。必须分别初始化为NULL和0
    void *hcd_ptr;
    uint32_t hcd_var;
    //主机驱动程序层处理程序
    void *usb_host_client;  //当前仅在提交到共享管道（即设备默认管道）时使用
    size_t usb_host_header_size; //USB主机可能需要数据缓冲区以具有透明标头
    //公共转移结构。由于数组长度可变，必须是最后一个
    usb_transfer_t transfer;
};
typedef struct urb_s urb_t;

typedef enum {
    USB_NOTIF_SOURCE_USBH = 0x01,
    USB_NOTIF_SOURCE_HUB = 0x02,
} usb_notif_source_t;

typedef bool (*usb_notif_cb_t)(usb_notif_source_t source, bool in_isr, void *context);

// ---------------------------------------------------分配------------------------------------------------------

/**
 * @brief 分配URB
 *
 * -数据缓冲区分配在支持DMA的内存中
 * -URB的常量字段也已设置
 * -URB的data_buffer字段设置为指向头之后分配的数据缓冲区的开始。要访问标头，用户需要从data_buffer获得负偏移量。
 *
 * @param data_buffer_size URB数据缓冲区的大小
 * @param header_size 放在URB数据缓冲区前面的标头大小
 * @param num_isoc_packets 同步数据包描述符的数量
 * @return urb_t*urb对象
 */
urb_t *urb_alloc(size_t data_buffer_size, size_t header_size, int num_isoc_packets);

/**
 * @brief 释放URB
 *
 * @param urb URB对象
 */
void urb_free(urb_t *urb);

#ifdef __cplusplus
}
#endif

