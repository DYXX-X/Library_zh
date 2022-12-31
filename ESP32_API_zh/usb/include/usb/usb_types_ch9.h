/*
 * SPDX文件版权所有文本：2015-2022 Espressif Systems（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */

/*
警告：USB主机库API仍然是测试版，可能会更改
*/

#pragma once

#include <stdint.h>

#ifdef __cplusplus
extern "C"
{
#endif

#define USB_DESC_ATTR                   __attribute__((packed))

// ----------------------------------------------------第9章------------------------------------------------------

/**
 * @brief USB2.0设备状态
 *
 * 详见USB2.0规范表9-1
 *
 * @note USB_DEVICE_STATE_NOT_ATTACHED不是USB2.0规范的一部分，但对于突然断开连接或端口错误后需要清理的设备，它是一种包罗万象的状态。
 */
typedef enum {
    USB_DEVICE_STATE_NOT_ATTACHED,              /**<设备以前已配置或挂起，但不再连接（突然断开连接或端口错误）*/
    USB_DEVICE_STATE_ATTACHED,                  /**<设备连接到USB，但未通电。*/
    USB_DEVICE_STATE_POWERED,                   /**<设备已连接到USB并通电，但尚未重置。*/
    USB_DEVICE_STATE_DEFAULT,                   /**<设备已连接到USB并通电，并且已重置，但尚未分配唯一地址。设备以默认地址响应。*/
    USB_DEVICE_STATE_ADDRESS,                   /**<设备连接到USB，已通电，已重置，并且已分配唯一的设备地址。未配置设备。*/
    USB_DEVICE_STATE_CONFIGURED,                /**<设备连接到USB、已通电、已重置、具有唯一地址、已配置且未挂起。主机现在可以使用设备提供的功能。*/
    USB_DEVICE_STATE_SUSPENDED,                 /**<设备至少连接到USB，已通电，3毫秒内未看到总线活动。它也可能具有唯一的地址并配置为使用。但是，由于设备已挂起，主机可能无法使用设备的功能。*/
} usb_device_state_t;

/**
 * @brief USB2.0规范表9.5中的描述符类型
 */
#define USB_B_DESCRIPTOR_TYPE_DEVICE                        0x01
#define USB_B_DESCRIPTOR_TYPE_CONFIGURATION                 0x02
#define USB_B_DESCRIPTOR_TYPE_STRING                        0x03
#define USB_B_DESCRIPTOR_TYPE_INTERFACE                     0x04
#define USB_B_DESCRIPTOR_TYPE_ENDPOINT                      0x05
#define USB_B_DESCRIPTOR_TYPE_DEVICE_QUALIFIER              0x06
#define USB_B_DESCRIPTOR_TYPE_OTHER_SPEED_CONFIGURATION     0x07
#define USB_B_DESCRIPTOR_TYPE_INTERFACE_POWER               0x08

/**
 * @brief USB 2.0 ECN中的描述符类型
 */
#define USB_B_DESCRIPTOR_TYPE_OTG                           0x09
#define USB_B_DESCRIPTOR_TYPE_DEBUG                         0x0a
#define USB_B_DESCRIPTOR_TYPE_INTERFACE_ASSOCIATION         0x0b

/**
 * @brief 无线USB规范中的描述符类型
 */
#define USB_B_DESCRIPTOR_TYPE_SECURITY                      0x0c
#define USB_B_DESCRIPTOR_TYPE_KEY                           0x0d
#define USB_B_DESCRIPTOR_TYPE_ENCRYPTION_TYPE               0x0e
#define USB_B_DESCRIPTOR_TYPE_BOS                           0x0f
#define USB_B_DESCRIPTOR_TYPE_DEVICE_CAPABILITY             0x10
#define USB_B_DESCRIPTOR_TYPE_WIRELESS_ENDPOINT_COMP        0x11
#define USB_B_DESCRIPTOR_TYPE_WIRE_ADAPTER                  0x21
#define USB_B_DESCRIPTOR_TYPE_RPIPE                         0x22
#define USB_B_DESCRIPTOR_TYPE_CS_RADIO_CONTROL              0x23

/**
 * @brief UAS规范中的描述符类型
 */
#define USB_B_DESCRIPTOR_TYPE_PIPE_USAGE                    0x24

// --------------------设置数据包-----------------------

/**
 * @brief USB控制传输设置数据包的大小（字节）
 */
#define USB_SETUP_PACKET_SIZE               8

/**
 * @brief 表示USB控制传输设置包的结构
 *
 * 详见USB2.0规范表9-2
 */
typedef union {
    struct {
        uint8_t bmRequestType;              /**<请求的特征*/
        uint8_t bRequest;                   /**<特定请求*/
        uint16_t wValue;                    /**<根据请求而变化的单词大小字段*/
        uint16_t wIndex;                    /**<根据请求而变化的单词大小字段；通常用于传递索引或偏移*/
        uint16_t wLength;                   /**<如果有数据阶段，要传输的字节数*/
    } __attribute__((packed));
    uint8_t val[USB_SETUP_PACKET_SIZE];
} usb_setup_packet_t;
_Static_assert(sizeof(usb_setup_packet_t) == USB_SETUP_PACKET_SIZE, "Size of usb_setup_packet_t incorrect");

/**
 * @brief 属于设置数据包的bmRequestType字段的位掩码
 */
#define USB_BM_REQUEST_TYPE_DIR_OUT         (0X00 << 7)
#define USB_BM_REQUEST_TYPE_DIR_IN          (0x01 << 7)
#define USB_BM_REQUEST_TYPE_TYPE_STANDARD   (0x00 << 5)
#define USB_BM_REQUEST_TYPE_TYPE_CLASS      (0x01 << 5)
#define USB_BM_REQUEST_TYPE_TYPE_VENDOR     (0x02 << 5)
#define USB_BM_REQUEST_TYPE_TYPE_RESERVED   (0x03 << 5)
#define USB_BM_REQUEST_TYPE_TYPE_MASK       (0x03 << 5)
#define USB_BM_REQUEST_TYPE_RECIP_DEVICE    (0x00 << 0)
#define USB_BM_REQUEST_TYPE_RECIP_INTERFACE (0x01 << 0)
#define USB_BM_REQUEST_TYPE_RECIP_ENDPOINT  (0x02 << 0)
#define USB_BM_REQUEST_TYPE_RECIP_OTHER     (0x03 << 0)
#define USB_BM_REQUEST_TYPE_RECIP_MASK      (0x1f << 0)

/**
 * @brief 属于设置包的bRequest字段的位掩码
 */
#define USB_B_REQUEST_GET_STATUS            0x00
#define USB_B_REQUEST_CLEAR_FEATURE         0x01
#define USB_B_REQUEST_SET_FEATURE           0x03
#define USB_B_REQUEST_SET_ADDRESS           0x05
#define USB_B_REQUEST_GET_DESCRIPTOR        0x06
#define USB_B_REQUEST_SET_DESCRIPTOR        0x07
#define USB_B_REQUEST_GET_CONFIGURATION     0x08
#define USB_B_REQUEST_SET_CONFIGURATION     0x09
#define USB_B_REQUEST_GET_INTERFACE         0x0A
#define USB_B_REQUEST_SET_INTERFACE         0x0B
#define USB_B_REQUEST_SYNCH_FRAME           0x0C

/**
 * @brief 属于设置包的wValue字段的位掩码
 */
#define USB_W_VALUE_DT_DEVICE               0x01
#define USB_W_VALUE_DT_CONFIG               0x02
#define USB_W_VALUE_DT_STRING               0x03
#define USB_W_VALUE_DT_INTERFACE            0x04
#define USB_W_VALUE_DT_ENDPOINT             0x05
#define USB_W_VALUE_DT_DEVICE_QUALIFIER     0x06
#define USB_W_VALUE_DT_OTHER_SPEED_CONFIG   0x07
#define USB_W_VALUE_DT_INTERFACE_POWER      0x08

/**
 * @brief SET_ADDRESS请求的初始化器
 *
 * 设置连接设备的地址
 */
#define USB_SETUP_PACKET_INIT_SET_ADDR(setup_pkt_ptr, addr) ({  \
    (setup_pkt_ptr)->bmRequestType = USB_BM_REQUEST_TYPE_DIR_OUT | USB_BM_REQUEST_TYPE_TYPE_STANDARD |USB_BM_REQUEST_TYPE_RECIP_DEVICE;   \
    (setup_pkt_ptr)->bRequest = USB_B_REQUEST_SET_ADDRESS;  \
    (setup_pkt_ptr)->wValue = (addr);   \
    (setup_pkt_ptr)->wIndex = 0;    \
    (setup_pkt_ptr)->wLength = 0;   \
})

/**
 * @brief 获取设备的设备描述符请求的初始化器
 */
#define USB_SETUP_PACKET_INIT_GET_DEVICE_DESC(setup_pkt_ptr) ({  \
    (setup_pkt_ptr)->bmRequestType = USB_BM_REQUEST_TYPE_DIR_IN | USB_BM_REQUEST_TYPE_TYPE_STANDARD | USB_BM_REQUEST_TYPE_RECIP_DEVICE;   \
    (setup_pkt_ptr)->bRequest = USB_B_REQUEST_GET_DESCRIPTOR;   \
    (setup_pkt_ptr)->wValue = (USB_W_VALUE_DT_DEVICE << 8); \
    (setup_pkt_ptr)->wIndex = 0;    \
    (setup_pkt_ptr)->wLength = 18;  \
})

/**
 * @brief 获取设备当前配置号请求的初始化器
 */
#define USB_SETUP_PACKET_INIT_GET_CONFIG(setup_pkt_ptr) ({  \
    (setup_pkt_ptr)->bmRequestType = USB_BM_REQUEST_TYPE_DIR_IN | USB_BM_REQUEST_TYPE_TYPE_STANDARD | USB_BM_REQUEST_TYPE_RECIP_DEVICE;   \
    (setup_pkt_ptr)->bRequest = USB_B_REQUEST_GET_CONFIGURATION;    \
    (setup_pkt_ptr)->wValue = 0;    \
    (setup_pkt_ptr)->wIndex = 0;    \
    (setup_pkt_ptr)->wLength = 1;   \
})

/**
 * @brief 获取设备当前配置描述符之一的请求的初始化器
 *
 * -desc_index表示配置的索引编号
 * -要获取的配置描述符的字节数
 */
#define USB_SETUP_PACKET_INIT_GET_CONFIG_DESC(setup_pkt_ptr, desc_index, desc_len) ({    \
    (setup_pkt_ptr)->bmRequestType = USB_BM_REQUEST_TYPE_DIR_IN | USB_BM_REQUEST_TYPE_TYPE_STANDARD | USB_BM_REQUEST_TYPE_RECIP_DEVICE;   \
    (setup_pkt_ptr)->bRequest = USB_B_REQUEST_GET_DESCRIPTOR;   \
    (setup_pkt_ptr)->wValue = (USB_W_VALUE_DT_CONFIG << 8) | ((desc_index) & 0xFF); \
    (setup_pkt_ptr)->wIndex = 0;    \
    (setup_pkt_ptr)->wLength = (desc_len);  \
})

/**
 * @brief 设置设备当前配置号请求的初始化器
 */
#define USB_SETUP_PACKET_INIT_SET_CONFIG(setup_pkt_ptr, config_num) ({  \
    (setup_pkt_ptr)->bmRequestType = USB_BM_REQUEST_TYPE_DIR_OUT | USB_BM_REQUEST_TYPE_TYPE_STANDARD | USB_BM_REQUEST_TYPE_RECIP_DEVICE;   \
    (setup_pkt_ptr)->bRequest = USB_B_REQUEST_SET_CONFIGURATION;    \
    (setup_pkt_ptr)->wValue = (config_num); \
    (setup_pkt_ptr)->wIndex = 0;    \
    (setup_pkt_ptr)->wLength = 0;   \
})

/**
 * @brief 设置接口备用设置请求的初始化器
 */
#define USB_SETUP_PACKET_INIT_SET_INTERFACE(setup_pkt_ptr, intf_num, alt_setting_num) ({    \
    (setup_pkt_ptr)->bmRequestType = USB_BM_REQUEST_TYPE_DIR_OUT | USB_BM_REQUEST_TYPE_TYPE_STANDARD | USB_BM_REQUEST_TYPE_RECIP_INTERFACE;  \
    (setup_pkt_ptr)->bRequest = USB_B_REQUEST_SET_INTERFACE; \
    (setup_pkt_ptr)->wValue = (alt_setting_num); \
    (setup_pkt_ptr)->wIndex = (intf_num);  \
    (setup_pkt_ptr)->wLength = 0;   \
})

/**
 * @brief 获取字符串描述符请求的初始化器
 */
#define USB_SETUP_PACKET_INIT_GET_STR_DESC(setup_pkt_ptr, string_index, lang_id, desc_len) ({ \
    (setup_pkt_ptr)->bmRequestType = USB_BM_REQUEST_TYPE_DIR_IN | USB_BM_REQUEST_TYPE_TYPE_STANDARD | USB_BM_REQUEST_TYPE_RECIP_DEVICE; \
    (setup_pkt_ptr)->bRequest = USB_B_REQUEST_GET_DESCRIPTOR; \
    (setup_pkt_ptr)->wValue = (USB_W_VALUE_DT_STRING << 8) | ((string_index) & 0xFF); \
    (setup_pkt_ptr)->wIndex = (lang_id); \
    (setup_pkt_ptr)->wLength = (desc_len); \
})

// ----------------标准描述符--------------------

/**
 * @brief 虚拟USB标准描述符的大小
 */
#define USB_STANDARD_DESC_SIZE              2

/**
 * @brief USB标准描述符
 *
 * 所有USB标准描述符都以这两个字节开头。遍历配置描述符时使用此类型
 */
typedef union {
    struct {
        uint8_t bLength;                    /**<描述符的大小（字节）*/
        uint8_t bDescriptorType;            /**<描述符类型*/
    } USB_DESC_ATTR;
    uint8_t val[USB_STANDARD_DESC_SIZE];
} usb_standard_desc_t;
_Static_assert(sizeof(usb_standard_desc_t) == USB_STANDARD_DESC_SIZE, "Size of usb_standard_desc_t incorrect");

// ------------------设备描述符--------------------

/**
 * @brief USB设备描述符的大小（字节）
 */
#define USB_DEVICE_DESC_SIZE                18

/**
 * @brief 表示USB设备描述符的结构
 *
 * 详见USB2.0规范表9-8
 */
typedef union {
    struct {
        uint8_t bLength;                    /**<描述符的大小（字节）*/
        uint8_t bDescriptorType;            /**<设备描述符类型*/
        uint16_t bcdUSB;                    /**<以二进制编码十进制表示的USB规范版本号（即2.10为210H）*/
        uint8_t bDeviceClass;               /**<类别代码（由USB-IF分配）*/
        uint8_t bDeviceSubClass;            /**<子类代码（由USB-IF分配）*/
        uint8_t bDeviceProtocol;            /**<协议代码（由USB-IF分配）*/
        uint8_t bMaxPacketSize0;            /**<端点0的最大数据包大小（仅8、16、32或64有效）*/
        uint16_t idVendor;                  /**<供应商ID（由USB-IF分配）*/
        uint16_t idProduct;                 /**<产品ID（由制造商指定）*/
        uint16_t bcdDevice;                 /**<以二进制编码十进制表示的设备版本号*/
        uint8_t iManufacturer;              /**<描述制造商的字符串描述符索引*/
        uint8_t iProduct;                   /**<描述产品的字符串描述符索引*/
        uint8_t iSerialNumber;              /**<描述设备序列号的字符串描述符索引*/
        uint8_t bNumConfigurations;         /**<可能配置的数量*/
    } USB_DESC_ATTR;
    uint8_t val[USB_DEVICE_DESC_SIZE];
} usb_device_desc_t;
_Static_assert(sizeof(usb_device_desc_t) == USB_DEVICE_DESC_SIZE, "Size of usb_device_desc_t incorrect");

/**
 * @brief USB设备描述符的bDeviceClass字段的可能基类值
 */
#define USB_CLASS_PER_INTERFACE             0x00
#define USB_CLASS_AUDIO                     0x01
#define USB_CLASS_COMM                      0x02
#define USB_CLASS_HID                       0x03
#define USB_CLASS_PHYSICAL                  0x05
#define USB_CLASS_STILL_IMAGE               0x06
#define USB_CLASS_PRINTER                   0x07
#define USB_CLASS_MASS_STORAGE              0x08
#define USB_CLASS_HUB                       0x09
#define USB_CLASS_CDC_DATA                  0x0a
#define USB_CLASS_CSCID                     0x0b
#define USB_CLASS_CONTENT_SEC               0x0d
#define USB_CLASS_VIDEO                     0x0e
#define USB_CLASS_WIRELESS_CONTROLLER       0xe0
#define USB_CLASS_PERSONAL_HEALTHCARE       0x0f
#define USB_CLASS_AUDIO_VIDEO               0x10
#define USB_CLASS_BILLBOARD                 0x11
#define USB_CLASS_USB_TYPE_C_BRIDGE         0x12
#define USB_CLASS_MISC                      0xef
#define USB_CLASS_APP_SPEC                  0xfe
#define USB_CLASS_VENDOR_SPEC               0xff

/**
 * @brief 供应商特定子类代码
 */
#define USB_SUBCLASS_VENDOR_SPEC            0xff

// --------------配置描述符-----------------

/**
 * @brief 短USB配置描述符的大小（字节）
 *
 * @note 完整USB配置的大小包括该配置的所有接口和端点描述符。
 */
#define USB_CONFIG_DESC_SIZE        9

/**
 * @brief 表示短USB配置描述符的结构
 *
 * 详见USB2.0规范表9-10
 *
 * @note 完整的USB配置包括该配置的所有接口和端点描述符。
 */
typedef union {
    struct {
        uint8_t bLength;                    /**<描述符的大小（字节）*/
        uint8_t bDescriptorType;            /**<配置描述符类型*/
        uint16_t wTotalLength;              /**<此配置返回的数据总长度*/
        uint8_t bNumInterfaces;             /**<此配置支持的接口数*/
        uint8_t bConfigurationValue;        /**<Value用作SetConfiguration（）请求的参数以选择此配置*/
        uint8_t iConfiguration;             /**<描述此配置的字符串描述符索引*/
        uint8_t bmAttributes;               /**<配置特征*/
        uint8_t bMaxPower;                  /**<当设备完全运行时，此特定配置中USB设备从总线的最大功耗。*/
    } USB_DESC_ATTR;
    uint8_t val[USB_CONFIG_DESC_SIZE];
} usb_config_desc_t;
_Static_assert(sizeof(usb_config_desc_t) == USB_CONFIG_DESC_SIZE, "Size of usb_config_desc_t incorrect");

/**
 * @brief 属于配置描述符的bmAttributes字段的位掩码
 */
#define USB_BM_ATTRIBUTES_ONE               (1 << 7)    //必须设置
#define USB_BM_ATTRIBUTES_SELFPOWER         (1 << 6)    //自供电
#define USB_BM_ATTRIBUTES_WAKEUP            (1 << 5)    //可以唤醒
#define USB_BM_ATTRIBUTES_BATTERY           (1 << 4)    //电池供电

// ----------接口关联描述符-------------

/**
 * @brief USB接口关联描述符的大小（字节）
 */
#define USB_IAD_DESC_SIZE    9

/**
 * @brief 表示USB接口关联描述符的结构
 */
typedef union {
    struct {
        uint8_t bLength;                    /**<描述符的大小（字节）*/
        uint8_t bDescriptorType;            /**<接口关联描述符类型*/
        uint8_t bFirstInterface;            /**<与此函数关联的第一个接口的接口号*/
        uint8_t bInterfaceCount;            /**<与此函数关联的连续接口数*/
        uint8_t bFunctionClass;             /**<类别代码（由USB-IF分配）*/
        uint8_t bFunctionSubClass;          /**<子类代码（由USB-IF分配）*/
        uint8_t bFunctionProtocol;          /**<协议代码（由USB-IF分配）*/
        uint8_t iFunction;                  /**<描述此函数的字符串描述符索引*/
    } USB_DESC_ATTR;
    uint8_t val[USB_IAD_DESC_SIZE];
} usb_iad_desc_t;
_Static_assert(sizeof(usb_iad_desc_t) == USB_IAD_DESC_SIZE, "Size of usb_iad_desc_t incorrect");

// ----------------接口描述符-------------------

/**
 * @brief USB接口描述符的大小（字节）
 */
#define USB_INTF_DESC_SIZE      9

/**
 * @brief 表示USB接口描述符的结构
 *
 * 详见USB2.0规范表9-12
 */
typedef union {
    struct {
        uint8_t bLength;                    /**<描述符的大小（字节）*/
        uint8_t bDescriptorType;            /**<接口描述符类型*/
        uint8_t bInterfaceNumber;           /**<此接口的编号。*/
        uint8_t bAlternateSetting;          /**<用于为上一字段中标识的接口选择此备用设置的值*/
        uint8_t bNumEndpoints;              /**<此接口使用的端点数（不包括端点零）。*/
        uint8_t bInterfaceClass;            /**<类别代码（由USB-IF分配）*/
        uint8_t bInterfaceSubClass;         /**<子类代码（由USB-IF分配）*/
        uint8_t bInterfaceProtocol;         /**<协议代码（由USB分配）*/
        uint8_t iInterface;                 /**<描述此接口的字符串描述符索引*/
    } USB_DESC_ATTR;
    uint8_t val[USB_INTF_DESC_SIZE];
} usb_intf_desc_t;
_Static_assert(sizeof(usb_intf_desc_t) == USB_INTF_DESC_SIZE, "Size of usb_intf_desc_t incorrect");

// -----------------终结点描述符-------------------

/**
 * @brief USB端点描述符的大小（字节）
 */
#define USB_EP_DESC_SIZE        7

/**
 * @brief 表示USB端点描述符的结构
 *
 * 详见USB2.0规范表9-13
 */
typedef union {
    struct {
        uint8_t bLength;                    /**<描述符的大小（字节）*/
        uint8_t bDescriptorType;            /**<ENDPOINT描述符类型*/
        uint8_t bEndpointAddress;           /**<此描述符描述的USB设备上端点的地址*/
        uint8_t bmAttributes;               /**<此字段描述使用bConfigurationValue配置端点时的端点属性。*/
        uint16_t wMaxPacketSize;            /**<选择此配置时，此端点能够发送或接收的最大数据包大小。*/
        uint8_t bInterval;                  /**<轮询同步和中断端点的间隔。根据设备运行速度以帧或微帧表示（低速和全速为1ms，USB高速及以上为125us）。*/
    } USB_DESC_ATTR;
    uint8_t val[USB_EP_DESC_SIZE];
} usb_ep_desc_t;
_Static_assert(sizeof(usb_ep_desc_t) == USB_EP_DESC_SIZE, "Size of usb_ep_desc_t incorrect");

/**
 * @brief 属于端点描述符的bEndpointAddress字段的位掩码
 */
#define USB_B_ENDPOINT_ADDRESS_EP_NUM_MASK              0x0f
#define USB_B_ENDPOINT_ADDRESS_EP_DIR_MASK              0x80

/**
 * @brief 属于端点描述符的bmAttributes字段的位掩码
 */
#define USB_BM_ATTRIBUTES_XFERTYPE_MASK                 0x03
#define USB_BM_ATTRIBUTES_XFER_CONTROL                  (0 << 0)
#define USB_BM_ATTRIBUTES_XFER_ISOC                     (1 << 0)
#define USB_BM_ATTRIBUTES_XFER_BULK                     (2 << 0)
#define USB_BM_ATTRIBUTES_XFER_INT                      (3 << 0)
#define USB_BM_ATTRIBUTES_SYNCTYPE_MASK                 0x0C    /* 在bmAttributes中*/
#define USB_BM_ATTRIBUTES_SYNC_NONE                     (0 << 2)
#define USB_BM_ATTRIBUTES_SYNC_ASYNC                    (1 << 2)
#define USB_BM_ATTRIBUTES_SYNC_ADAPTIVE                 (2 << 2)
#define USB_BM_ATTRIBUTES_SYNC_SYNC                     (3 << 2)
#define USB_BM_ATTRIBUTES_USAGETYPE_MASK                0x30
#define USB_BM_ATTRIBUTES_USAGE_DATA                    (0 << 4)
#define USB_BM_ATTRIBUTES_USAGE_FEEDBACK                (1 << 4)
#define USB_BM_ATTRIBUTES_USAGE_IMPLICIT_FB             (2 << 4)

/**
 * @brief 宏助手，用于从其描述符获取有关端点的信息
 */
#define USB_EP_DESC_GET_XFERTYPE(desc_ptr) ((usb_transfer_type_t) ((desc_ptr)->bmAttributes & USB_BM_ATTRIBUTES_XFERTYPE_MASK))
#define USB_EP_DESC_GET_EP_NUM(desc_ptr) ((desc_ptr)->bEndpointAddress & USB_B_ENDPOINT_ADDRESS_EP_NUM_MASK)
#define USB_EP_DESC_GET_EP_DIR(desc_ptr) (((desc_ptr)->bEndpointAddress & USB_B_ENDPOINT_ADDRESS_EP_DIR_MASK) ? 1 : 0)
#define USB_EP_DESC_GET_MPS(desc_ptr) ((desc_ptr)->wMaxPacketSize & 0x7FF)

// ------------------字符串描述符--------------------

/**
 * @brief 短USB字符串描述符的大小（字节）
 */
#define USB_STR_DESC_SIZE       2

/**
 * @brief 表示USB字符串描述符的结构
 */
typedef union {
    struct {
        uint8_t bLength;                    /**<描述符的大小（字节）*/
        uint8_t bDescriptorType;            /**<字符串描述符类型*/
        uint16_t wData[];                   /**<UTF-16LE编码*/
    } USB_DESC_ATTR;
    uint8_t val[USB_STR_DESC_SIZE];
} usb_str_desc_t;
_Static_assert(sizeof(usb_str_desc_t) == USB_STR_DESC_SIZE, "Size of usb_str_desc_t incorrect");

#ifdef __cplusplus
}
#endif

