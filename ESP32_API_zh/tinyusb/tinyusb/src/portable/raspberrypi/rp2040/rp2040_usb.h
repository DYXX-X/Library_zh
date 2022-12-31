#ifndef RP2040_COMMON_H_
#define RP2040_COMMON_H_

#if defined(RP2040_USB_HOST_MODE) && defined(RP2040_USB_DEVICE_MODE)
#error TinyUSB device and host mode not supported at the same time
#endif

#include "common/tusb_common.h"

#include "pico.h"
#include "hardware/structs/usb.h"
#include "hardware/irq.h"
#include "hardware/resets.h"

#if defined(PICO_RP2040_USB_DEVICE_ENUMERATION_FIX) && !defined(TUD_OPT_RP2040_USB_DEVICE_ENUMERATION_FIX)
#define TUD_OPT_RP2040_USB_DEVICE_ENUMERATION_FIX PICO_RP2040_USB_DEVICE_ENUMERATION_FIX
#endif

// 对于memset
#include <string.h>

#if false && !defined(NDEBUG)
#define pico_trace(format,args...) printf(format, ## args)
#else
#define pico_trace(format,...) ((void)0)
#endif

#if false && !defined(NDEBUG)
#define pico_info(format,args...) printf(format, ## args)
#else
#define pico_info(format,...) ((void)0)
#endif

#if false && !defined(NDEBUG)
#define pico_warn(format,args...) printf(format, ## args)
#else
#define pico_warn(format,...) ((void)0)
#endif

// 每个端点的硬件信息
struct hw_endpoint
{
    // 这是有效的结构吗
    bool configured;
    
    // 传输方向（即IN是主机的rx，而tx是设备）
    // 允许我们共用传递函数
    bool rx;
    
    uint8_t ep_addr;
    uint8_t next_pid;

    // 端点控制寄存器
    io_rw_32 *endpoint_control;
    // 缓冲区控制寄存器
    io_rw_32 *buffer_control;

    // usb dpram中的缓冲区指针
    uint8_t *hw_data_buf;

    // 我们被困了吗
    bool stalled;

    // 当前转移信息
    bool active;
    uint16_t total_len;
    uint16_t len;
    // 硬件的数据量
    uint16_t transfer_size;
    // 主内存中的用户缓冲区
    uint8_t *user_buf;

    // EP描述符所需的数据
    uint16_t wMaxPacketSize;
    // 中断、批量等
    uint8_t transfer_type;
    
#if TUSB_OPT_HOST_ENABLED
    // 仅主机模式需要
    bool last_buf;
    // 主机错误。主机将错误写入缓冲区的上半部分
    // 传输>1个数据包时的控制寄存器
    uint8_t buf_sel;
    // 仅主机需要
    uint8_t dev_addr;
    bool sent_setup;
    // 如果中断端点
    uint8_t interrupt_num;
#endif
};

void rp2040_usb_init(void);

void hw_endpoint_reset_transfer(struct hw_endpoint *ep);
void _hw_endpoint_xfer(struct hw_endpoint *ep, uint8_t *buffer, uint16_t total_len, bool start);
void _hw_endpoint_start_next_buffer(struct hw_endpoint *ep);
void _hw_endpoint_xfer_start(struct hw_endpoint *ep, uint8_t *buffer, uint16_t total_len);
void _hw_endpoint_xfer_sync(struct hw_endpoint *ep);
bool _hw_endpoint_xfer_continue(struct hw_endpoint *ep);
void _hw_endpoint_buffer_control_update32(struct hw_endpoint *ep, uint32_t and_mask, uint32_t or_mask);
static inline uint32_t _hw_endpoint_buffer_control_get_value32(struct hw_endpoint *ep) {
    return *ep->buffer_control;
}
static inline void _hw_endpoint_buffer_control_set_value32(struct hw_endpoint *ep, uint32_t value) {
    return _hw_endpoint_buffer_control_update32(ep, 0, value);
}
static inline void _hw_endpoint_buffer_control_set_mask32(struct hw_endpoint *ep, uint32_t value) {
    return _hw_endpoint_buffer_control_update32(ep, ~value, value);
}
static inline void _hw_endpoint_buffer_control_clear_mask32(struct hw_endpoint *ep, uint32_t value) {
    return _hw_endpoint_buffer_control_update32(ep, ~value, 0);
}

static inline uintptr_t hw_data_offset(uint8_t *buf)
{
    // 从缓冲指针中移除usb底座
    return (uintptr_t)buf ^ (uintptr_t)usb_dpram;
}

extern const char *ep_dir_string[];

#endif

