/*
 *  LPCUSB，LPC微控制器的USB设备驱动程序版权所有（C）2006 Bertrik Sikken(bertrik@sikken.nl)版权所有（c）2016 Intel Corporation
 *
 *  在满足以下条件的情况下，允许以源代码和二进制形式重新分发和使用，无论是否进行修改：
 *
 *  1.源代码的重新分发必须保留上述版权声明、本条件列表和以下免责声明。2.二进制形式的再发行必须在随发行提供的文档和/或其他材料中复制上述版权声明、本条件列表和以下免责声明。3.未经事先书面许可，不得使用作者的姓名为本软件衍生的产品背书或推广。
 *
 *  THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * @file
 * @brief USB设备核心层API和结构
 *
 * 此文件包含USB设备核心层API和结构。
 */

#pragma once

#include <stddef.h>
#include <sys/cdefs.h>
#include "usb_dc.h"

#ifdef __cplusplus
extern "C" {
#endif

/*************************************************************************
 *  USB配置
 **************************************************************************/

#define MAX_PACKET_SIZE0    64        /**<EP 0的最大数据包大小*/
//注意：对于FS，这应该是8、16、32、64字节。HS最高可达512。

/*************************************************************************
 *  USB应用程序接口
 **************************************************************************/

/**设置数据包定义*/
struct usb_setup_packet {
    uint8_t bmRequestType;  /**<特定请求的特征*/
    uint8_t bRequest;       /**<特定请求*/
    uint16_t wValue;        /**<请求特定参数*/
    uint16_t wIndex;        /**<请求特定参数*/
    uint16_t wLength;       /**<数据阶段传输的数据长度*/
} __packed;


_Static_assert(sizeof(struct usb_setup_packet) == 8, "USB setup packet struct size error");

/**
 * 设备的回调函数签名
 */
typedef void (*usb_status_callback)(enum usb_dc_status_code status_code,
                                    uint8_t *param);

/**
 * USB端点状态的回调函数签名
 */
typedef void (*usb_ep_callback)(uint8_t ep,
                                enum usb_dc_ep_cb_status_code cb_status);

/**
 * 处理与设备描述符表中指定的接口号相对应的类特定请求的函数
 */
typedef int (*usb_request_handler) (struct usb_setup_packet *detup,
                                    int32_t *transfer_len, uint8_t **payload_data);

/**
 * 接口运行时配置的函数
 */
typedef void (*usb_interface_config)(uint8_t bInterfaceNumber);

/*
 * USB端点配置
 */
struct usb_ep_cfg_data {
    /**
     * 回调函数，用于通知应用程序已接收和可用的数据或已完成传输，如果应用程序代码不需要回调，则为NULL
     */
    usb_ep_callback ep_cb;
    /**
     * 设备配置结构中与EP相关的编号in EP=0x80|\<端点编号\>OUT EP=0x00|\<终点编号\>
     */
    uint8_t ep_addr;
};

/**
 * USB接口配置
 */
struct usb_interface_cfg_data {
    /**USB类特定控制（EP 0）通信的处理程序*/
    usb_request_handler class_handler;
    /**USB供应商特定命令的处理程序*/
    usb_request_handler vendor_handler;
    /**
     * 在将请求移交给“第9章”请求处理程序之前，自定义请求处理程序将获得处理请求的第一次机会
     */
    usb_request_handler custom_handler;
    /**
     * 该数据区域由应用程序分配，用于存储特定于类的命令数据，并且必须足够大，以存储与支持的最大类命令集相关联的最大有效负载。该数据区域可用于USB输入或输出通信
     */
    uint8_t *payload_data;
    /**
     * 该数据区域由应用程序分配，用于存储供应商特定的负载
     */
    uint8_t *vendor_data;
};

/*
 * @brief USB设备配置
 *
 * 应用程序使用使用“usb_set_config”函数添加的给定参数对此进行实例化。一旦调用此函数，对该结构的更改将导致未定义的行为。此结构只能在调用usb_deconfig后更新
 */
struct usb_cfg_data {
    /**
     * USB设备说明，请参阅http://www.beyondlogic.org/usbnutshell/usb5.shtml#DeviceDescriptors
     */
    const uint8_t *usb_device_description;
    /**指向接口描述符的指针*/
    const void *interface_descriptor;
    /**接口运行时配置的函数*/
    usb_interface_config interface_config;
    /**USB连接状态更改时通知的回调*/
    usb_status_callback cb_usb_status;
    /**USB接口（类）处理器和存储空间*/
    struct usb_interface_cfg_data interface;
    /**设备配置中单个端点的数量*/
    uint8_t num_endpoints;
    /**
     * 指向长度等于与设备描述相关的EP数量的端点结构数组的指针，不包括控制端点
     */
    struct usb_ep_cfg_data *endpoint;
};

/*
 * @brief 配置USB控制器
 *
 * 配置USB控制器的功能。配置参数必须有效或返回错误
 *
 * @param[in] config 指向配置结构的指针
 *
 * @return 成功时为0，失败时为负错误代码
 */
int usb_set_config(struct usb_cfg_data *config);

/*
 * @brief 将USB设备恢复到初始状态
 *
 * @return 成功时为0，失败时为负错误代码
 */
int usb_deconfig(void);

/*
 * @brief 为主机/设备连接启用USB
 *
 * 为主机/设备连接启用USB的功能。成功后，USB模块不再在硬件中进行时钟门控，它现在能够在USB总线上进行发送和接收，并生成中断。
 *
 * @return 成功时为0，失败时为负错误代码。
 */
int usb_enable(struct usb_cfg_data *config);

/*
 * @brief 禁用USB设备。
 *
 * 禁用USB设备的功能。成功后，指定的USB接口在硬件中被时钟门控，它不再能够生成中断。
 *
 * @return 成功时为0，失败时为负错误代码
 */
int usb_disable(void);

/*
 * @brief 检查在fifo中有足够的空间之前，是否会阻止写入ep
 *
 * @param[in]  ep        与设备配置表中列出的端点地址相对应的端点地址
 *
 * @return 如果可以自由写入，则为0；如果写入会阻塞，则为1；如果失败，则为负错误代码
 */
int usb_write_would_block(uint8_t ep);

/*
 * @brief 将数据写入指定的端点
 *
 * 函数将数据写入指定的端点。传输完成后，将调用提供的usb_ep_callback。
 *
 * @param[in]  ep        与设备配置表中列出的端点地址相对应的端点地址
 * @param[in]  data      指向要写入的数据的指针
 * @param[in]  data_len  请求写入的数据长度。对于零长度状态包，这可能为零。
 * @param[out] bytes_ret 写入EP FIFO的字节。如果应用程序希望写入所有字节，则此值可能为NULL
 *
 * @return 成功时为0，失败时为负错误代码
 */
int usb_write(uint8_t ep, const uint8_t *data, uint32_t data_len,
              uint32_t *bytes_ret);

/*
 * @brief 从指定端点读取数据
 *
 * 在接收到该EP的OUT中断后，端点处理程序函数调用此函数。应用程序只能通过提供的usb_ep_callback函数调用此函数。
 *
 * @param[in]  ep           与设备配置表中列出的端点地址相对应的端点地址
 * @param[in]  data         指向要写入的数据缓冲区的指针
 * @param[in]  max_data_len 要读取的最大数据长度
 * @param[out] ret_bytes    读取的字节数。如果数据为NULL且max_data_len为0，则返回可读取的字节数。
 *
 * @return  成功时为0，失败时为负错误代码
 */
int usb_read(uint8_t ep, uint8_t *data, uint32_t max_data_len,
             uint32_t *ret_bytes);

/*
 * @brief 在指定端点上设置STALL条件
 *
 * USB设备类处理程序代码调用此函数以在端点上设置暂停条件。
 *
 * @param[in]  ep           与设备配置表中列出的端点地址相对应的端点地址
 *
 * @return  成功时为0，失败时为负错误代码
 */
int usb_ep_set_stall(uint8_t ep);


/*
 * @brief 清除指定端点上的STALL条件
 *
 * USB设备类处理程序代码调用此函数以清除端点上的暂停条件。
 *
 * @param[in]  ep           与设备配置表中列出的端点地址相对应的端点地址
 *
 * @return  成功时为0，失败时为负错误代码
 */
int usb_ep_clear_stall(uint8_t ep);

/**
 * @brief 从指定端点读取数据
 *
 * 这与usb_ep_read类似，不同之处在于，它不会清除端点NAK，以便消费者在完成数据处理之前不会因进一步的上调而陷入困境。调用者应该通过调用usb_ep_read_continue（）来重新激活ep。
 *
 * @param[in]  ep           与设备配置表中列出的端点地址相对应的端点地址
 * @param[in]  data         指向要写入的数据缓冲区的指针
 * @param[in]  max_data_len 要读取的最大数据长度
 * @param[out] read_bytes   读取的字节数。如果数据为NULL且max_data_len为0，则应返回可读取的字节数。
 *
 * @return 成功时为0，失败时为负错误代码。
 */
int usb_ep_read_wait(uint8_t ep, uint8_t *data, uint32_t max_data_len,
                     uint32_t *read_bytes);


/**
 * @brief 继续从端点读取数据
 *
 * 清除端点NAK并使端点能够从主机接受更多数据。通常在用户可以接受更多数据时在usb_ep_read_wait（）之后调用。因此，这些调用一起充当流控制机制。
 *
 * @param[in]  ep           与设备配置表中列出的端点地址相对应的端点地址
 *
 * @return 成功时为0，失败时为负错误代码。
 */
int usb_ep_read_continue(uint8_t ep);

/**
 * 用于传输完成的回调函数签名。
 */
typedef void (*usb_transfer_callback)(uint8_t ep, int tsize, void *priv);

/* USB传输标志*/
#define USB_TRANS_READ       BIT(0)   /**读取传输标志*/
#define USB_TRANS_WRITE      BIT(1)   /**写入传输标志*/
#define USB_TRANS_NO_ZLP     BIT(2)   /**无零长度数据包标志*/

/**
 * @brief 传输管理端点回调
 *
 * 若USB类驱动程序想要使用高级传输函数，则驱动程序需要将此回调注册为USB端点回调。
 */
void usb_transfer_ep_callback(uint8_t ep, enum usb_dc_ep_cb_status_code);

/**
 * @brief 开始传输
 *
 * 启动数据缓冲区的usb传输。此函数是异步的，可以在IRQ上下文中执行。提供的回调将在线程上下文中的传输完成（或错误）时调用。
 *
 * @param[in]  ep           与设备配置表中列出的端点地址相对应的端点地址
 * @param[in]  data         指向要写入/读取的数据缓冲区的指针
 * @param[in]  dlen         数据缓冲区大小
 * @param[in]  flags        传输标志（USB_TRANS_READ、USB_TRANS_WRITE…）
 * @param[in]  cb           传输完成/失败时调用的函数
 * @param[in]  priv         传递回传输完成回调的数据
 *
 * @return 成功时为0，失败时为负错误代码。
 */
int usb_transfer(uint8_t ep, uint8_t *data, size_t dlen, unsigned int flags,
                 usb_transfer_callback cb, void *priv);

/**
 * @brief 开始传输并阻止等待完成
 *
 * usb_transfer的同步版本，请等待传输完成后再返回。
 *
 * @param[in]  ep           与设备配置表中列出的端点地址相对应的端点地址
 * @param[in]  data         指向要写入/读取的数据缓冲区的指针
 * @param[in]  dlen         数据缓冲区大小
 * @param[in]  flags        传输标志

 *
 * @return 成功时传输的字节数，失败时为负errno代码。
 */
int usb_transfer_sync(uint8_t ep, uint8_t *data, size_t dlen, unsigned int flags);

/**
 * @brief 取消指定端点上的任何正在进行的传输
 *
 * @param[in]  ep           与设备配置表中列出的端点地址相对应的端点地址
 *
 * @return 成功时为0，失败时为负错误代码。
 */
void usb_cancel_transfer(uint8_t ep);


void usb_dev_resume(int configuration);
int usb_dev_get_configuration(void);


#ifdef __cplusplus
}
#endif

