/*
 * SPDX文件版权所有文本：2015-2022 Espressif Systems（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */

/*
警告：USB主机库API仍然是测试版，可能会更改
*/

#pragma once

#include "usb/usb_types_ch9.h"

#ifdef __cplusplus
extern "C" {
#endif

// ------------------------------------------------协议标准--------------------------------------------------

/**
 * @brief USB标准速度
 */
typedef enum {
    USB_SPEED_LOW = 0,                  /**<USB低速（1.5 Mbit/s）*/
    USB_SPEED_FULL,                     /**<USB全速（12 Mbit/s）*/
} usb_speed_t;

/**
 * @brief USB传输类型
 *
 * @note 枚举值需要与EP描述符的bmAttributes字段匹配
 */
typedef enum {
    USB_TRANSFER_TYPE_CTRL = 0,
    USB_TRANSFER_TYPE_ISOCHRONOUS,
    USB_TRANSFER_TYPE_BULK,
    USB_TRANSFER_TYPE_INTR,
} usb_transfer_type_t;

// -------------------------------------------------与设备相关----------------------------------------------------

/**
 * @brief 连接到USB主机的USB设备的手柄
 */
typedef struct usb_device_handle_s * usb_device_handle_t;

/**
 * @brief 枚举设备的基本信息
 */
typedef struct {
    usb_speed_t speed;                              /**<设备速度*/
    uint8_t dev_addr;                               /**<设备地址*/
    uint8_t bMaxPacketSize0;                        /**<设备默认端点的最大数据包大小*/
    uint8_t bConfigurationValue;                    /**<设备当前配置编号*/
    const usb_str_desc_t *str_desc_manufacturer;    /**<指向制造商字符串描述符的指针（可以为NULL）*/
    const usb_str_desc_t *str_desc_product;         /**<指向产品字符串描述符的指针（可以为NULL）*/
    const usb_str_desc_t *str_desc_serial_num;      /**<指向序列号字符串描述符的指针（可以为NULL）*/
} usb_device_info_t;

// ------------------------------------------------转账相关---------------------------------------------------

/**
 * @brief 特定传输的状态
 */
typedef enum {
    USB_TRANSFER_STATUS_COMPLETED,      /**<传输成功（但可能很短）*/
    USB_TRANSFER_STATUS_ERROR,          /**<由于错误过多（例如无响应或CRC错误），传输失败*/
    USB_TRANSFER_STATUS_TIMED_OUT,      /**<由于超时，传输失败*/
    USB_TRANSFER_STATUS_CANCELED,       /**<传输已取消*/
    USB_TRANSFER_STATUS_STALL,          /**<传输已停止*/
    USB_TRANSFER_STATUS_OVERFLOW,       /**<发送的数据多于请求的数据时进行传输*/
    USB_TRANSFER_STATUS_SKIPPED,        /**<仅限ISOC数据包。由于系统延迟或总线过载，数据包被跳过*/
    USB_TRANSFER_STATUS_NO_DEVICE,      /**<传输失败，因为目标设备不存在*/
} usb_transfer_status_t;

/**
 * @brief 等时分组描述符
 *
 * 如果等时传输中的字节数大于端点的MPS，则将传输拆分为以端点指定的间隔传输的多个数据包。一组等时分组描述符描述了如何将等时传输拆分为多个分组。
 */
typedef struct {
    int num_bytes;                                  /**<数据包中要发送/接收的字节数。IN数据包应为MPS的整数倍*/
    int actual_num_bytes;                           /**<数据包中发送/接收的实际字节数*/
    usb_transfer_status_t status;                   /**<数据包的状态*/
} usb_isoc_packet_desc_t;

/**
 * @brief USB传输结构
 *
 * 此结构用于表示通过USB总线从软件客户端到端点的传输。有些字段是故意设置为常量的，因为它们在分配时是固定的。用户应该调用适当的USB主机库函数来分配USB传输结构，而不是自己分配此结构。
 *
 * 传输类型是从发送此传输的终结点推断出来的。根据传输类型，用户应注意以下事项：
 *
 * -批量：此结构表示单个批量传输。如果字节数超过端点的MPS，传输将被分成多个MPS大小的数据包，然后是一个短数据包。
 * -控件：此结构表示单个控件传输。data_buffer的前8个字节必须填充设置数据包（请参见usb_setup_packet_t）。num_bytes字段应该是传输的总大小（即，设置数据包的大小+wLength）。
 * -中断：表示中断传输。如果num_bytes超过端点的MPS，则传输将被拆分为多个数据包，每个数据包将按端点指定的间隔传输。
 * -Isochronous：表示应以固定速率传输到端点的字节流。根据每个isoc_packet_desc将传输分成分组。在端点的每个间隔传输数据包。如果整个ISOC URB传输时没有错误（跳过的数据包不算作错误），则将更新URB的总体状态和每个数据包描述符的状态，而actual_num_bytes反映所有数据包传输的总字节数。如果ISOC URB遇到错误，则整个URB被认为是错误的，因此只更新整体状态。
 *
 * @note 对于批量/控制/中断IN传输，num_bytes必须是端点MPS的整数倍
 * @note 此结构应通过usb_host_transfer_alloc（）分配
 * @note 提交传输后，用户在传输完成之前不得修改结构
 */
typedef struct usb_transfer_s usb_transfer_t;

/**
 * @brief USB传输完成回调
 */
typedef void (*usb_transfer_cb_t)(usb_transfer_t *transfer);

struct usb_transfer_s{
    uint8_t *const data_buffer;                     /**<指向数据缓冲区的指针*/
    const size_t data_buffer_size;                  /**<数据缓冲区的大小（字节）*/
    int num_bytes;                                  /**<要传输的字节数。控制传输应包括设置数据包的大小。同步传输应该是所有数据包的总传输大小。对于非控制IN传输，num_bytes应为MPS的整数倍。*/
    int actual_num_bytes;                           /**<实际传输的字节数*/
    uint32_t flags;                                 /**<传输标志*/
    usb_device_handle_t device_handle;              /**<设备句柄*/
    uint8_t bEndpointAddress;                       /**<端点地址*/
    usb_transfer_status_t status;                   /**<传输状态*/
    uint32_t timeout_ms;                            /**<数据包超时（毫秒）（当前尚不支持）*/
    usb_transfer_cb_t callback;                     /**<传输回调*/
    void *context;                                  /**<传输的上下文变量，以将传输与某物关联*/
    const int num_isoc_packets;                     /**<仅与Isochronous相关。传输数据缓冲区的服务周期数（即间隔）。*/
    usb_isoc_packet_desc_t isoc_packet_desc[];      /**<每个等时数据包的描述符*/
};

/**
 * @brief 使用零长度数据包终止批量/中断OUT传输
 *
 * OUT传输通常在主机向设备传输了所需的确切数据量时终止。然而，对于批量和中断OUT传输，如果传输大小恰好是MPS的倍数，则不可能知道到同一端点的两个连续传输之间的边界。
 *
 * 因此，如果满足以下条件，该标志将导致传输在传输结束时自动添加零长度数据包（ZLP）：
 * -目标端点是批量/中断OUT端点（主机到设备）
 * -传输的长度（即transfer.num_bytes）是端点MPS的倍数
 *
 * 否则，此标志无效。
 *
 * 用户应检查其目标设备的类是否需要ZLP，因为并非所有批量/中断OUT端点都需要它们。例如：
 * -对于MSC仅批量传输类，主机不得发送ZLP。批量传输边界由CBW和CSW决定
 * -对于CDC以太网，如果段（即传输）是MPS的倍数，主机必须始终发送ZLP（参见3.3.1段描述）
 *
 * @note 有关详细信息，请参阅USB2.0规范5.7.3和5.8.3
 * @note IN传输通常在主机收到所需的确切数据量（必须是MPS的倍数）或端点向主机发送短数据包时终止
 */
#define USB_TRANSFER_FLAG_ZERO_PACK  0x01           /**<（仅适用于批量输出）。指示批量OUT传输应始终以短数据包终止，即使这意味着添加额外的零长度数据包*/

#ifdef __cplusplus
}
#endif

