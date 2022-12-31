/*
 * MIT许可证（MIT）
 *
 * 版权所有（c）2019 Ha Thach（tinyusb.org）
 *
 * 特此免费授予获得本软件和相关文档文件（“软件”）副本的任何人无限制地处理软件的权利，包括但不限于使用、复制、修改、合并、发布、分发、再许可和/或销售软件副本的权利，并允许向其提供软件的人这样做，符合以下条件：
 *
 * 上述版权声明和本许可声明应包含在软件的所有副本或主要部分中。
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * 此文件是TinyUSB堆栈的一部分。
 */

/** \inggroup group_usb_definitions\defgroup USBDef_Type usb类型
 *  @{ */

#ifndef _TUSB_TYPES_H_
#define _TUSB_TYPES_H_

#include <stdbool.h>
#include <stdint.h>
#include "tusb_compiler.h"

#ifdef __cplusplus
 extern "C" {
#endif

/*------------------------------------------------------------------*/
/* CONSTANTS
 *------------------------------------------------------------------*/

///基于端点速度的EHCI规格值定义
typedef enum
{
  TUSB_SPEED_FULL = 0,
  TUSB_SPEED_LOW     ,
  TUSB_SPEED_HIGH,
  TUSB_SPEED_INVALID = 0xff,
}tusb_speed_t;

///基于USB规范端点的bmAttributes定义
typedef enum
{
  TUSB_XFER_CONTROL = 0 ,
  TUSB_XFER_ISOCHRONOUS ,
  TUSB_XFER_BULK        ,
  TUSB_XFER_INTERRUPT
}tusb_xfer_type_t;

typedef enum
{
  TUSB_DIR_OUT = 0,
  TUSB_DIR_IN  = 1,

  TUSB_DIR_IN_MASK = 0x80
}tusb_dir_t;

///USB描述符类型
typedef enum
{
  TUSB_DESC_DEVICE                = 0x01,
  TUSB_DESC_CONFIGURATION         = 0x02,
  TUSB_DESC_STRING                = 0x03,
  TUSB_DESC_INTERFACE             = 0x04,
  TUSB_DESC_ENDPOINT              = 0x05,
  TUSB_DESC_DEVICE_QUALIFIER      = 0x06,
  TUSB_DESC_OTHER_SPEED_CONFIG    = 0x07,
  TUSB_DESC_INTERFACE_POWER       = 0x08,
  TUSB_DESC_OTG                   = 0x09,
  TUSB_DESC_DEBUG                 = 0x0A,
  TUSB_DESC_INTERFACE_ASSOCIATION = 0x0B,

  TUSB_DESC_BOS                   = 0x0F,
  TUSB_DESC_DEVICE_CAPABILITY     = 0x10,

  TUSB_DESC_FUNCTIONAL            = 0x21,

  // 类特定描述符
  TUSB_DESC_CS_DEVICE             = 0x21,
  TUSB_DESC_CS_CONFIGURATION      = 0x22,
  TUSB_DESC_CS_STRING             = 0x23,
  TUSB_DESC_CS_INTERFACE          = 0x24,
  TUSB_DESC_CS_ENDPOINT           = 0x25,

  TUSB_DESC_SUPERSPEED_ENDPOINT_COMPANION     = 0x30,
  TUSB_DESC_SUPERSPEED_ISO_ENDPOINT_COMPANION = 0x31
}tusb_desc_type_t;

typedef enum
{
  TUSB_REQ_GET_STATUS        = 0  ,
  TUSB_REQ_CLEAR_FEATURE     = 1  ,
  TUSB_REQ_RESERVED          = 2  ,
  TUSB_REQ_SET_FEATURE       = 3  ,
  TUSB_REQ_RESERVED2         = 4  ,
  TUSB_REQ_SET_ADDRESS       = 5  ,
  TUSB_REQ_GET_DESCRIPTOR    = 6  ,
  TUSB_REQ_SET_DESCRIPTOR    = 7  ,
  TUSB_REQ_GET_CONFIGURATION = 8  ,
  TUSB_REQ_SET_CONFIGURATION = 9  ,
  TUSB_REQ_GET_INTERFACE     = 10 ,
  TUSB_REQ_SET_INTERFACE     = 11 ,
  TUSB_REQ_SYNCH_FRAME       = 12
}tusb_request_code_t;

typedef enum
{
  TUSB_REQ_FEATURE_EDPT_HALT     = 0,
  TUSB_REQ_FEATURE_REMOTE_WAKEUP = 1,
  TUSB_REQ_FEATURE_TEST_MODE     = 2
}tusb_request_feature_selector_t;

typedef enum
{
  TUSB_REQ_TYPE_STANDARD = 0,
  TUSB_REQ_TYPE_CLASS,
  TUSB_REQ_TYPE_VENDOR,
  TUSB_REQ_TYPE_INVALID
} tusb_request_type_t;

typedef enum
{
  TUSB_REQ_RCPT_DEVICE =0,
  TUSB_REQ_RCPT_INTERFACE,
  TUSB_REQ_RCPT_ENDPOINT,
  TUSB_REQ_RCPT_OTHER
} tusb_request_recipient_t;

// https://www.usb.org/defined-class-codes
typedef enum
{
  TUSB_CLASS_UNSPECIFIED          = 0    ,
  TUSB_CLASS_AUDIO                = 1    ,
  TUSB_CLASS_CDC                  = 2    ,
  TUSB_CLASS_HID                  = 3    ,
  TUSB_CLASS_RESERVED_4           = 4    ,
  TUSB_CLASS_PHYSICAL             = 5    ,
  TUSB_CLASS_IMAGE                = 6    ,
  TUSB_CLASS_PRINTER              = 7    ,
  TUSB_CLASS_MSC                  = 8    ,
  TUSB_CLASS_HUB                  = 9    ,
  TUSB_CLASS_CDC_DATA             = 10   ,
  TUSB_CLASS_SMART_CARD           = 11   ,
  TUSB_CLASS_RESERVED_12          = 12   ,
  TUSB_CLASS_CONTENT_SECURITY     = 13   ,
  TUSB_CLASS_VIDEO                = 14   ,
  TUSB_CLASS_PERSONAL_HEALTHCARE  = 15   ,
  TUSB_CLASS_AUDIO_VIDEO          = 16   ,

  TUSB_CLASS_DIAGNOSTIC           = 0xDC ,
  TUSB_CLASS_WIRELESS_CONTROLLER  = 0xE0 ,
  TUSB_CLASS_MISC                 = 0xEF ,
  TUSB_CLASS_APPLICATION_SPECIFIC = 0xFE ,
  TUSB_CLASS_VENDOR_SPECIFIC      = 0xFF
}tusb_class_code_t;

typedef enum
{
  MISC_SUBCLASS_COMMON = 2
}misc_subclass_type_t;

typedef enum
{
  MISC_PROTOCOL_IAD = 1
}misc_protocol_type_t;

typedef enum
{
  APP_SUBCLASS_USBTMC = 0x03,
  APP_SUBCLASS_DFU_RUNTIME = 0x01
} app_subclass_type_t;

typedef enum
{
  DEVICE_CAPABILITY_WIRELESS_USB               = 0x01,
  DEVICE_CAPABILITY_USB20_EXTENSION            = 0x02,
  DEVICE_CAPABILITY_SUPERSPEED_USB             = 0x03,
  DEVICE_CAPABILITY_CONTAINER_id               = 0x04,
  DEVICE_CAPABILITY_PLATFORM                   = 0x05,
  DEVICE_CAPABILITY_POWER_DELIVERY             = 0x06,
  DEVICE_CAPABILITY_BATTERY_INFO               = 0x07,
  DEVICE_CAPABILITY_PD_CONSUMER_PORT           = 0x08,
  DEVICE_CAPABILITY_PD_PROVIDER_PORT           = 0x09,
  DEVICE_CAPABILITY_SUPERSPEED_PLUS            = 0x0A,
  DEVICE_CAPABILITY_PRECESION_TIME_MEASUREMENT = 0x0B,
  DEVICE_CAPABILITY_WIRELESS_USB_EXT           = 0x0C,
  DEVICE_CAPABILITY_BILLBOARD                  = 0x0D,
  DEVICE_CAPABILITY_AUTHENTICATION             = 0x0E,
  DEVICE_CAPABILITY_BILLBOARD_EX               = 0x0F,
  DEVICE_CAPABILITY_CONFIGURATION_SUMMARY      = 0x10
}device_capability_type_t;

enum {
  TUSB_DESC_CONFIG_ATT_REMOTE_WAKEUP = TU_BIT(5),
  TUSB_DESC_CONFIG_ATT_SELF_POWERED  = TU_BIT(6),
};

#define TUSB_DESC_CONFIG_POWER_MA(x)  ((x)/2)

///设备状态TODO删除
typedef enum
{
  TUSB_DEVICE_STATE_UNPLUG = 0  ,
  TUSB_DEVICE_STATE_CONFIGURED  ,
  TUSB_DEVICE_STATE_SUSPENDED   ,
}tusb_device_state_t;

typedef enum
{
  XFER_RESULT_SUCCESS,
  XFER_RESULT_FAILED,
  XFER_RESULT_STALLED,
}xfer_result_t;

enum // TODO删除
{
  DESC_OFFSET_LEN  = 0,
  DESC_OFFSET_TYPE = 1
};

enum
{
  INTERFACE_INVALID_NUMBER = 0xff
};


typedef enum
{
  MS_OS_20_SET_HEADER_DESCRIPTOR       = 0x00,
  MS_OS_20_SUBSET_HEADER_CONFIGURATION = 0x01,
  MS_OS_20_SUBSET_HEADER_FUNCTION      = 0x02,
  MS_OS_20_FEATURE_COMPATBLE_ID        = 0x03,
  MS_OS_20_FEATURE_REG_PROPERTY        = 0x04,
  MS_OS_20_FEATURE_MIN_RESUME_TIME     = 0x05,
  MS_OS_20_FEATURE_MODEL_ID            = 0x06,
  MS_OS_20_FEATURE_CCGP_DEVICE         = 0x07,
  MS_OS_20_FEATURE_VENDOR_REVISION     = 0x08
} microsoft_os_20_type_t;

enum
{
  CONTROL_STAGE_SETUP,
  CONTROL_STAGE_DATA,
  CONTROL_STAGE_ACK
};

//--------------------------------------------------------------------+
// USB描述符
//--------------------------------------------------------------------+

///USB设备描述符
typedef struct TU_ATTR_PACKED
{
  uint8_t  bLength            ; ///<此描述符的大小（字节）。
  uint8_t  bDescriptorType    ; ///<设备描述符类型。
  uint16_t bcdUSB             ; ///<以二进制编码十进制表示的BUSB规范版本号（即2.10为210H）。此字段标识设备及其描述符符合的USB规范的版本。

  uint8_t  bDeviceClass       ; ///<类别代码（由USB-IF分配）。\li如果此字段重置为零，则配置中的每个接口都指定自己的类信息，并且各个接口独立运行。\li如果此字段设置为介于1和FEH之间的值，则设备在不同接口上支持不同的类规范，并且接口可能无法独立运行。此值标识用于聚合接口的类定义。\li如果此字段设置为FFH，则设备类别是特定于供应商的。
  uint8_t  bDeviceSubClass    ; ///<子类代码（由USB-IF分配）。这些代码由bDeviceClass字段的值限定。\li如果bDeviceClass字段重置为零，则该字段也必须重置为零。\li如果bDeviceClass字段未设置为FFH，则所有值都保留给USB-If分配。
  uint8_t  bDeviceProtocol    ; ///<协议代码（由USB-IF分配）。这些代码由bDeviceClass和bDeviceSubClass字段的值限定。如果设备支持基于设备的特定于类的协议，而不是基于接口的协议，则此代码标识设备使用的协议，如设备类规范所定义的。\li如果此字段重置为零，则设备不在设备基础上使用特定于类的协议。然而，它可以在接口基础上使用特定于类的协议。\li如果此字段设置为FFH，则设备在设备基础上使用特定于供应商的协议。
  uint8_t  bMaxPacketSize0    ; ///<端点0的最大数据包大小（只有8、16、32或64有效）。对于HS设备，固定为64。

  uint16_t idVendor           ; ///<供应商ID（由USB-IF分配）。
  uint16_t idProduct          ; ///<产品ID（由制造商指定）。
  uint16_t bcdDevice          ; ///<以二进制编码的十进制表示的设备版本号。
  uint8_t  iManufacturer      ; ///<描述制造商的字符串描述符索引。
  uint8_t  iProduct           ; ///<描述产品的字符串描述符索引。
  uint8_t  iSerialNumber      ; ///<描述设备序列号的字符串描述符索引。

  uint8_t  bNumConfigurations ; ///<可能配置的数量。
} tusb_desc_device_t;

TU_VERIFY_STATIC( sizeof(tusb_desc_device_t) == 18, "size is not correct");

// USB二进制设备对象存储（BOS）描述符
typedef struct TU_ATTR_PACKED
{
  uint8_t  bLength         ; ///<此描述符的大小（字节）
  uint8_t  bDescriptorType ; ///<配置描述符类型
  uint16_t wTotalLength    ; ///<为此描述符返回的数据的总长度
  uint8_t  bNumDeviceCaps  ; ///<BOS中设备能力描述符的数量
} tusb_desc_bos_t;

///USB配置描述符
typedef struct TU_ATTR_PACKED
{
  uint8_t  bLength             ; ///<此描述符的大小（字节）
  uint8_t  bDescriptorType     ; ///<配置描述符类型
  uint16_t wTotalLength        ; ///<此配置返回的数据的总长度。包括为此配置返回的所有描述符（配置、接口、端点和特定于类或供应商）的组合长度。

  uint8_t  bNumInterfaces      ; ///<此配置支持的接口数
  uint8_t  bConfigurationValue ; ///<Value用作SetConfiguration（）请求的参数，以选择此配置。
  uint8_t  iConfiguration      ; ///<描述此配置的字符串描述符索引
  uint8_t  bmAttributes        ; ///<配置特征\n D7：保留（设置为1）\n D6：自供电\n D5：远程唤醒\n D4…0：保留（重置为零）\n D7是保留的，由于历史原因必须设置为1。\n使用来自总线和本地电源的电源的设备配置报告bMaxPower中的非零值，以指示所需的总线电源量，并设置D6。运行时的实际电源可使用GetStatus（device）请求确定（参见USB 2.0规范第9.4.5节）。\n如果设备配置支持远程唤醒，则D5设置为1。
  uint8_t  bMaxPower           ; ///<当设备完全运行时，此特定配置中USB设备从总线的最大功耗。以2 mA单位表示（即50=100 mA）。
} tusb_desc_configuration_t;

///USB接口描述符
typedef struct TU_ATTR_PACKED
{
  uint8_t  bLength            ; ///<此描述符的大小（字节）
  uint8_t  bDescriptorType    ; ///<接口描述符类型

  uint8_t  bInterfaceNumber   ; ///<此接口的编号。从零开始的值标识此配置支持的并发接口数组中的索引。
  uint8_t  bAlternateSetting  ; ///<用于为上一字段中标识的接口选择此备用设置的值
  uint8_t  bNumEndpoints      ; ///<此接口使用的端点数（不包括端点零）。如果该值为零，则该接口仅使用默认控制管道。
  uint8_t  bInterfaceClass    ; ///<类别代码（由USB-IF分配）。\li为将来的标准化保留零值。\li如果此字段设置为FFH，则接口类是特定于供应商的。\li所有其他值都保留给USB-IF分配。
  uint8_t  bInterfaceSubClass ; ///<子类代码（由USB-IF分配）。\n这些代码由bInterfaceClass字段的值限定。\li如果bInterfaceClass字段重置为零，则该字段也必须重置为零。\li如果bInterfaceClass字段未设置为FFH，则所有值都保留给USB-If分配。
  uint8_t  bInterfaceProtocol ; ///<协议代码（由USB分配）。\n这些代码由bInterfaceClass和bInterfaceSubClass字段的值限定。如果接口支持特定于类的请求，则此代码标识设备使用的协议，如设备类规范所定义的。\li如果此字段重置为零，则设备在此接口上不使用特定于类的协议。\li如果此字段设置为FFH，则设备使用供应商特定的协议用于此接口。
  uint8_t  iInterface         ; ///<描述此接口的字符串描述符索引
} tusb_desc_interface_t;

///USB端点描述符
typedef struct TU_ATTR_PACKED
{
  uint8_t  bLength          ; ///<此描述符的大小（字节）
  uint8_t  bDescriptorType  ; ///<ENDPOINT描述符类型

  uint8_t  bEndpointAddress ; ///<此描述符描述的USB设备上端点的地址。地址编码如下：\n位3…0：端点编号\n位6…4：保留，重置为零\n位7：方向，对于控制端点0=OUT端点1=IN端点忽略。

  struct TU_ATTR_PACKED {
    uint8_t xfer  : 2;
    uint8_t sync  : 2;
    uint8_t usage : 2;
    uint8_t       : 2;
  } bmAttributes     ; ///<此字段描述使用bConfigurationValue配置端点时的端点属性。\n位1..0：传输类型\n-00=控制\n-01=同步\n-10=批量\n-11=中断\n如果不是同步端点，则保留位5..2，并且必须设置为零。如果是同步的，则其定义如下：\n位3..2：同步类型\n-00=无同步\n-01=异步\n-10=自适应\n-11=同步\n位5..4：使用类型\n-00=数据端点\n-01=反馈端点\n-10=隐式反馈数据端点\n-11=保留\n有关详细信息，请参阅USB 2.0规范的第5章。\n保留所有其他位，必须重置为零。主机必须忽略保留位。

  struct TU_ATTR_PACKED {
    uint16_t size           : 11; ///<选择此配置时，此端点能够发送或接收的最大数据包大小。\n对于等时端点，该值用于在调度中保留每（微）帧数据有效载荷所需的总线时间。管道可能会在持续的基础上实际使用比预留带宽更少的带宽。如果需要，该设备通过其正常的非USB定义机制报告实际使用的带宽。\n对于所有端点，位10..0指定最大数据包大小（以字节为单位）。\n对于高速同步和中断端点：\n位12..11指定每个微帧的额外事务机会数：\n-00=无（每个微帧1个事务）\n-01=1个额外（每个微框架2个）\n-10=2个额外（每微帧3个）\n-11=保留\n位15..13是保留的，必须设置为零。
    uint16_t hs_period_mult : 2;
    uint16_t TU_RESERVED    : 3;
  }wMaxPacketSize;

  uint8_t  bInterval        ; ///<数据传输轮询终结点的间隔。以帧或微帧表示，取决于设备操作速度（即，1毫秒或125 us单位）。\n-对于全/高速等时端点，此值必须在1到16之间。bInterval值用作\f$2^（bInterval-1）\f$值的指数；e、 例如，b间隔4表示8（\f$2^（4-1）\f$）。\n-对于全/低速中断端点，此字段的值可以从1到255。\n-对于高速中断端点，b间隔值用作a\f$2^（b间隔-1）\f$value的指数；e、 例如，b间隔4表示8（\f$2^（4-1）\f$）。此值必须介于1到16之间。\n-对于高速批量/控制OUT终结点，bInterval必须指定终结点的最大NAK速率。值0表示端点从不NAK。其他值表示每个微帧的间隔数最多为1 NAK。此值必须介于0到255之间。\n有关详细信息，请参阅USB 2.0规范的第5章。
} tusb_desc_endpoint_t;

///USB其他速度配置描述符
typedef struct TU_ATTR_PACKED
{
  uint8_t  bLength             ; ///<描述符大小
  uint8_t  bDescriptorType     ; ///<Other_speed_Configuration Type（其他速度配置类型）
  uint16_t wTotalLength        ; ///<返回数据的总长度

  uint8_t  bNumInterfaces      ; ///<此速度配置支持的接口数
  uint8_t  bConfigurationValue ; ///<用于选择配置的值
  uint8_t  IConfiguration      ; ///<字符串描述符索引
  uint8_t  bmAttributes        ; ///<与配置描述符相同
  uint8_t  bMaxPower           ; ///<与配置描述符相同
} tusb_desc_other_speed_t;

///USB设备限定符描述符
typedef struct TU_ATTR_PACKED
{
  uint8_t  bLength            ; ///<描述符大小
  uint8_t  bDescriptorType    ; ///<设备限定符类型
  uint16_t bcdUSB             ; ///<USB规范版本号（例如，V2.00的0200H）

  uint8_t  bDeviceClass       ; ///<类别代码
  uint8_t  bDeviceSubClass    ; ///<子类代码
  uint8_t  bDeviceProtocol    ; ///<协议代码
  uint8_t  bMaxPacketSize0    ; ///<其他速度的最大数据包大小
  uint8_t  bNumConfigurations ; ///<其他速度配置的数量
  uint8_t  bReserved          ; ///<保留供将来使用，必须为零
} tusb_desc_device_qualifier_t;

///USB接口关联描述符（IAD ECN）
typedef struct TU_ATTR_PACKED
{
  uint8_t bLength           ; ///<描述符大小
  uint8_t bDescriptorType   ; ///<Other_speed_Configuration Type（其他速度配置类型）

  uint8_t bFirstInterface   ; ///<第一个关联接口的索引。
  uint8_t bInterfaceCount   ; ///<关联接口的总数。

  uint8_t bFunctionClass    ; ///<接口类ID。
  uint8_t bFunctionSubClass ; ///<接口子类ID。
  uint8_t bFunctionProtocol ; ///<接口协议ID。

  uint8_t iFunction         ; ///<描述接口关联的字符串描述符的索引。
} tusb_desc_interface_assoc_t;

// USB字符串描述符
typedef struct TU_ATTR_PACKED
{
  uint8_t  bLength         ; ///<此描述符的大小（字节）
  uint8_t  bDescriptorType ; ///<描述符类型
  uint16_t unicode_string[];
} tusb_desc_string_t;

// USB二进制设备对象存储（BOS）
typedef struct TU_ATTR_PACKED
{
  uint8_t bLength;
  uint8_t bDescriptorType ;
  uint8_t bDevCapabilityType;
  uint8_t bReserved;
  uint8_t PlatformCapabilityUUID[16];
  uint8_t CapabilityData[];
} tusb_desc_bos_platform_t;

// USB WebuSB URL描述符
typedef struct TU_ATTR_PACKED
{
  uint8_t bLength;
  uint8_t bDescriptorType;
  uint8_t bScheme;
  char    url[];
} tusb_desc_webusb_url_t;

/*------------------------------------------------------------------*/
/* 类型
 *------------------------------------------------------------------*/
typedef struct TU_ATTR_PACKED{
  union {
    struct TU_ATTR_PACKED {
      uint8_t recipient :  5; ///<收件人类型tusb_request_Recipient_t。
      uint8_t type      :  2; ///<请求类型tusb_Request_type_t。
      uint8_t direction :  1; ///<方向类型。tusb_dir_t
    } bmRequestType_bit;

    uint8_t bmRequestType;
  };

  uint8_t  bRequest;
  uint16_t wValue;
  uint16_t wIndex;
  uint16_t wLength;
} tusb_control_request_t;

TU_VERIFY_STATIC( sizeof(tusb_control_request_t) == 8, "size is not correct");

// TODO移动到合适的位置
static inline uint8_t bm_request_type(uint8_t direction, uint8_t type, uint8_t recipient)
{
  return ((uint8_t) (direction << 7)) | ((uint8_t) (type << 5)) | (recipient);
}

//--------------------------------------------------------------------+
// 终结点帮助程序
//--------------------------------------------------------------------+

// 从端点地址获取方向
static inline tusb_dir_t tu_edpt_dir(uint8_t addr)
{
  return (addr & TUSB_DIR_IN_MASK) ? TUSB_DIR_IN : TUSB_DIR_OUT;
}

// 从地址获取端点编号
static inline uint8_t tu_edpt_number(uint8_t addr)
{
  return (uint8_t)(addr & (~TUSB_DIR_IN_MASK));
}

static inline uint8_t tu_edpt_addr(uint8_t num, uint8_t dir)
{
  return (uint8_t)(num | (dir ? TUSB_DIR_IN_MASK : 0));
}

//--------------------------------------------------------------------+
// 描述符帮助程序
//--------------------------------------------------------------------+
static inline uint8_t const * tu_desc_next(void const* desc)
{
  uint8_t const* desc8 = (uint8_t const*) desc;
  return desc8 + desc8[DESC_OFFSET_LEN];
}

static inline uint8_t tu_desc_type(void const* desc)
{
  return ((uint8_t const*) desc)[DESC_OFFSET_TYPE];
}

static inline uint8_t tu_desc_len(void const* desc)
{
  return ((uint8_t const*) desc)[DESC_OFFSET_LEN];
}

#ifdef __cplusplus
 }
#endif

#endif /* _TUSB_TYPES_H_ */

/** @} */

