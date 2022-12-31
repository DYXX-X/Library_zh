// 版权所有2020 Espressif Systems（上海）私人有限公司
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
#ifdef __cplusplus
extern "C"
{
#endif

#include <stdint.h>

/* USB IN EP索引*/
typedef enum {
    USB_IN_EP_0 = 0,
    USB_IN_EP_1,
    USB_IN_EP_2,
    USB_IN_EP_3,
    USB_IN_EP_4,
    USB_IN_EP_5,
    USB_IN_EP_6,
    USB_IN_EP_NUM
} usb_in_ep_idx_t;

/* USB OUT EP索引*/
typedef enum {
    USB_OUT_EP_0 = 0,
    USB_OUT_EP_1,
    USB_OUT_EP_2,
    USB_OUT_EP_3,
    USB_OUT_EP_4,
    USB_OUT_EP_5,
    USB_OUT_EP_6,
    USB_OUT_EP_NUM
} usb_out_ep_idx_t;

/* USB IN EP寄存器块类型*/
typedef struct usb_in_ep_reg {
    volatile uint32_t diepctl;
    uint32_t reserved;
    volatile uint32_t diepint;
    uint32_t reserved1;
    volatile uint32_t dieptsiz;
    volatile uint32_t diepdma;
    volatile uint32_t dtxfsts;
    uint32_t reserved2;
} usb_in_endpoint_t;

/* USB OUT EP寄存器块类型*/
typedef struct usb_out_ep_reg {
    volatile uint32_t doepctl;
    uint32_t reserved;
    volatile uint32_t doepint;
    uint32_t reserved1;
    volatile uint32_t doeptsiz;
    volatile uint32_t doepdma;
    uint32_t reserved2;
    uint32_t reserved3;
} usb_out_endpoint_t;

#ifdef __cplusplus
}
#endif

