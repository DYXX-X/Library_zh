/* usb_dc。h-USB设备控制器驱动程序接口*/

/*
 * 版权所有（c）2016 Intel Corporation。
 *
 * SPDX许可证标识符：Apache-2.0
 */

/**
 * @file
 * @brief USB设备控制器API
 *
 * 此文件包含USB设备控制器API。所有设备控制器驱动程序都应实现本文件中描述的API。
 */

#pragma once

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * USB端点方向和编号。
 */

#define USB_EP_DIR_MASK 0x80
#define USB_EP_DIR_IN   0x80
#define USB_EP_DIR_OUT  0x00

/**
 * USB驱动程序状态代码
 */
enum usb_dc_status_code {
    USB_DC_ERROR,        /* 控制器报告的USB错误*/
    USB_DC_RESET,        /* USB复位*/
    /* USB连接已建立，硬件枚举已完成*/
    USB_DC_CONNECTED,
    USB_DC_CONFIGURED,   /* USB配置完成*/
    USB_DC_DISCONNECTED, /* USB连接丢失*/
    USB_DC_SUSPEND,      /* 主机挂起USB连接*/
    USB_DC_RESUME,       /* 主机恢复USB连接*/
    USB_DC_INTERFACE,    /* 已选择USB接口*/
    USB_DC_SET_HALT,     /* 收到设置功能ENDPOINT_HALT*/
    USB_DC_CLEAR_HALT,   /* 接收到清除功能ENDPOINT_HALT*/
    USB_DC_UNKNOWN       /* 初始USB连接状态*/
};

/**
 * USB端点回调状态代码
 */
enum usb_dc_ep_cb_status_code {
    USB_DC_EP_SETUP,    /* SETUP已接收*/
    /* 此EP上的传出事务，数据可供读取*/
    USB_DC_EP_DATA_OUT,
    USB_DC_EP_DATA_IN,  /* 在此EP上完成的事务中*/
};

/**
 * USB端点类型
 */
enum usb_dc_ep_type {
    USB_DC_EP_CONTROL = 0,  /* 控件类型终结点*/
    USB_DC_EP_ISOCHRONOUS,  /* 等时型终点*/
    USB_DC_EP_BULK,         /* 批量类型终结点*/
    USB_DC_EP_INTERRUPT     /* 中断类型终结点*/
};

/**
 * USB端点配置。
 */
struct usb_dc_ep_cfg_data {
    /** 设备配置结构中与EP相关的编号in EP=0x80|\<端点编号\>OUT EP=0x00|\<终点编号\>
     */
    uint8_t ep_addr;
    uint16_t ep_mps;             /**端点最大数据包大小*/
    enum usb_dc_ep_type ep_type; /**终结点类型*/
};

/**
 * USB端点状态的回调函数签名
 */
typedef void (*usb_dc_ep_callback)(uint8_t ep,
                                   enum usb_dc_ep_cb_status_code cb_status);

/**
 * 设备的回调函数签名
 */
typedef void (*usb_dc_status_callback)(enum usb_dc_status_code cb_status,
                                       uint8_t *param);

/**
 * @brief 连接USB用于设备连接
 *
 * 连接USB用于设备连接的功能。一旦成功，USB PLL被启用，并且USB设备现在能够在USB总线上发送和接收以及生成中断。
 *
 * @return 成功时为0，失败时为负错误代码。
 */
int usb_dc_attach(void);

/**
 * @brief 分离USB设备
 *
 * 分离USB设备的功能。成功后，USB硬件PLL断电，USB通信被禁用。
 *
 * @return 成功时为0，失败时为负错误代码。
 */
int usb_dc_detach(void);

/**
 * @brief 重置USB设备
 *
 * 此函数将USB设备和固件返回到初始状态。N、 B.USB PLL由USB_detach函数处理
 *
 * @return 成功时为0，失败时为负错误代码。
 */
int usb_dc_reset(void);

/**
 * @brief 设置USB设备地址
 *
 * @param[in] addr 设备地址
 *
 * @return 成功时为0，失败时为负错误代码。
 */
int usb_dc_set_address(const uint8_t addr);

/**
 * @brief 设置USB设备控制器状态回调
 *
 * 设置USB设备控制器状态回调的函数。注册的回调用于报告设备控制器状态的更改。
 *
 * @param[in] cb 回调函数
 *
 * @return 成功时为0，失败时为负错误代码。
 */
int usb_dc_set_status_callback(const usb_dc_status_callback cb);

/**
 * @brief 检查端点功能
 *
 * 函数检查端点的功能。usbdc_ep_cfgdata结构提供端点配置参数：端点地址、端点最大数据包大小和端点类型。驱动程序应检查端点功能，如果端点配置可行，则返回0。
 *
 * @param[in] cfg 终结点配置
 *
 * @return 成功时为0，失败时为负错误代码。
 */
int usb_dc_ep_check_cap(const struct usb_dc_ep_cfg_data *const cfg);

/**
 * @brief 配置端点
 *
 * 函数来配置端点。usbdc_ep_cfgdata结构提供端点配置参数：端点地址、端点最大数据包大小和端点类型。
 *
 * @param[in] cfg 终结点配置
 *
 * @return 成功时为0，失败时为负错误代码。
 */
int usb_dc_ep_configure(const struct usb_dc_ep_cfg_data *const cfg);

/**
 * @brief 为所选端点设置暂停条件
 *
 * @param[in] ep 与设备配置表中列出的端点地址相对应的端点地址
 *
 * @return 成功时为0，失败时为负错误代码。
 */
int usb_dc_ep_set_stall(const uint8_t ep);

/**
 * @brief 清除选定端点的暂停条件
 *
 * @param[in] ep 与设备配置表中列出的端点地址相对应的端点地址
 *
 * @return 成功时为0，失败时为负错误代码。
 */
int usb_dc_ep_clear_stall(const uint8_t ep);

/**
 * @brief 检查所选端点是否已停止
 *
 * @param[in]  ep       与设备配置表中列出的端点地址相对应的端点地址
 * @param[out] stalled  终结点暂停状态
 *
 * @return 成功时为0，失败时为负错误代码。
 */
int usb_dc_ep_is_stalled(const uint8_t ep, uint8_t *const stalled);

/**
 * @brief 停止选定的端点
 *
 * @param[in] ep 与设备配置表中列出的端点地址相对应的端点地址
 *
 * @return 成功时为0，失败时为负错误代码。
 */
int usb_dc_ep_halt(const uint8_t ep);

/**
 * @brief 启用所选端点
 *
 * 函数以启用所选端点。成功后，为相应的端点启用中断，并且该端点准备好发送/接收数据。
 *
 * @param[in] ep 与设备配置表中列出的端点地址相对应的端点地址
 *
 * @return 成功时为0，失败时为负错误代码。
 */
int usb_dc_ep_enable(const uint8_t ep);

/**
 * @brief 禁用所选端点
 *
 * 函数禁用所选端点。成功后，将禁用相应端点的中断，并且该端点不再能够发送/接收数据。
 *
 * @param[in] ep 与设备配置表中列出的端点地址相对应的端点地址
 *
 * @return 成功时为0，失败时为负错误代码。
 */
int usb_dc_ep_disable(const uint8_t ep);

/**
 * @brief 刷新选定的端点
 *
 * @param[in] ep 与设备配置表中列出的端点地址相对应的端点地址
 *
 * @return 成功时为0，失败时为负错误代码。
 */
int usb_dc_ep_flush(const uint8_t ep);

/**
 * @brief 将数据写入指定的端点
 *
 * 调用此函数将数据写入指定的端点。发送数据时，将调用提供的usb_ep_callback函数。
 *
 * @param[in]  ep        与设备配置表中列出的端点地址相对应的端点地址
 * @param[in]  data      指向要写入的数据的指针
 * @param[in]  data_len  请求写入的数据长度。对于零长度状态包，这可能为零。
 * @param[out] ret_bytes 计划传输的字节数。如果应用程序希望写入所有字节，则此值可能为NULL
 *
 * @return 成功时为0，失败时为负错误代码。
 */
int usb_dc_ep_write(const uint8_t ep, const uint8_t *const data,
                    const uint32_t data_len, uint32_t *const ret_bytes);



/**
 * @brief 指示对IN端点的写入（使用usb_dc_ep_write）是否会阻塞以等待该端点有足够的空间
 *
 * @param[in]  ep        与设备配置表中列出的端点地址相对应的端点地址
 *
 * @return 可写时为0，不可写时则为0，失败时为负errno代码。
 */
int usb_dc_ep_write_would_block(const uint8_t ep);


/**
 * @brief 从指定端点读取数据
 *
 * 在接收到该EP的OUT中断后，端点处理程序函数调用此函数。应用程序只能通过提供的usb_ep_callback函数调用此函数。如果已读取端点FIFO中的所有数据，此函数将清除ENDPOINT NAK，以便从主机接收更多数据。
 *
 * @param[in]  ep           与设备配置表中列出的端点地址相对应的端点地址
 * @param[in]  data         指向要写入的数据缓冲区的指针
 * @param[in]  max_data_len 要读取的最大数据长度
 * @param[out] read_bytes   读取的字节数。如果数据为NULL且max_data_len为0，则应返回可读取的字节数。
 *
 * @return 成功时为0，失败时为负错误代码。
 */
int usb_dc_ep_read(const uint8_t ep, uint8_t *const data,
                   const uint32_t max_data_len, uint32_t *const read_bytes);

/**
 * @brief 为指定端点设置回调函数
 *
 * 函数设置回调函数，用于通知在所选端点上接收并可用于应用程序或传输的数据，如果应用程序代码不需要回调，则为NULL。
 *
 * @param[in] ep 与设备配置表中列出的端点地址相对应的端点地址
 * @param[in] cb 回调函数
 *
 * @return 成功时为0，失败时为负错误代码。
 */
int usb_dc_ep_set_callback(const uint8_t ep, const usb_dc_ep_callback cb);

/**
 * @brief 从指定端点读取数据
 *
 * 这与usb_dc_ep_read类似，不同之处在于，它不会清除端点NAK，以便消费者在完成数据处理之前不会因进一步的上调而陷入困境。调用者应该通过调用usb_dc_ep_read_continue（）来重新激活ep。
 *
 * @param[in]  ep           与设备配置表中列出的端点地址相对应的端点地址
 * @param[in]  data         指向要写入的数据缓冲区的指针
 * @param[in]  max_data_len 要读取的最大数据长度
 * @param[out] read_bytes   读取的字节数。如果数据为NULL且max_data_len为0，则应返回可读取的字节数。
 *
 * @return 成功时为0，失败时为负错误代码。
 */
int usb_dc_ep_read_wait(uint8_t ep, uint8_t *data, uint32_t max_data_len,
                        uint32_t *read_bytes);


/**
 * @brief 继续从端点读取数据
 *
 * 清除端点NAK并使端点能够从主机接受更多数据。通常在用户可以接受更多数据时在usb_dc_ep_read_wait（）之后调用。因此，这些调用一起充当流控制机制。
 *
 * @param[in]  ep           与设备配置表中列出的端点地址相对应的端点地址
 *
 * @return 成功时为0，失败时为负错误代码。
 */
int usb_dc_ep_read_continue(uint8_t ep);

/**
 * @brief 获取端点最大数据包大小
 *
 * @param[in]  ep           与设备配置表中列出的端点地址相对应的端点地址
 *
 * @return enpoint最大数据包大小（mps）
 */
int usb_dc_ep_mps(uint8_t ep);



//黑客-通过pollnfg伪造中断
void usb_dc_check_poll_for_interrupts(void);


//准备USB持久化。之后应该重新启动。
int usb_dc_prepare_persist(void);


void usb_dw_isr_handler(void);


int usb_dc_ep_write_would_block(const uint8_t ep);


#ifdef __cplusplus
}
#endif

