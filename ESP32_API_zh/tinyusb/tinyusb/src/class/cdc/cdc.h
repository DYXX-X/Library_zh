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

/** \inggroup group_class\defgroup ClassDriver_CDC通信设备类（CDC）当前仅支持抽象控制模型子类
 *  @{ */

#ifndef _TUSB_CDC_H__
#define _TUSB_CDC_H__

#include "common/tusb_common.h"

#ifdef __cplusplus
 extern "C" {
#endif

/** \defgroup ClassDriver_CDC_通用通用定义
 *  @{ */

// TODO删除
///CDC管道ID，用于指示API寻址到哪个管道（通知、输出、输入）
typedef enum
{
  CDC_PIPE_NOTIFICATION , ///<通知管道
  CDC_PIPE_DATA_IN      , ///<管道中的数据
  CDC_PIPE_DATA_OUT     , ///<数据输出管道
  CDC_PIPE_ERROR        , ///<管道ID无效
}cdc_pipeid_t;

//--------------------------------------------------------------------+
// CDC通信接口类
//--------------------------------------------------------------------+

///通信接口子类代码
typedef enum
{
  CDC_COMM_SUBCLASS_DIRECT_LINE_CONTROL_MODEL = 0x01  , ///<直接线路控制模型[USBPSTN1.2]
  CDC_COMM_SUBCLASS_ABSTRACT_CONTROL_MODEL            , ///<抽象控制模型[USBPSTN1.2]
  CDC_COMM_SUBCLASS_TELEPHONE_CONTROL_MODEL           , ///<电话控制型号[USBPSTN1.2]
  CDC_COMM_SUBCLASS_MULTICHANNEL_CONTROL_MODEL        , ///<多通道控制模型[USBISDN1.2]
  CDC_COMM_SUBCLASS_CAPI_CONTROL_MODEL                , ///<CAPI控制模型[USBISDN1.2]
  CDC_COMM_SUBCLASS_ETHERNET_CONTROL_MODEL            , ///<以太网网络控制模型[USBECM1.2]
  CDC_COMM_SUBCLASS_ATM_NETWORKING_CONTROL_MODEL      , ///<ATM网络控制模型[USBATM1.2]
  CDC_COMM_SUBCLASS_WIRELESS_HANDSET_CONTROL_MODEL    , ///<无线手持设备控制型号[USBWMC1.1]
  CDC_COMM_SUBCLASS_DEVICE_MANAGEMENT                 , ///<设备管理[USBWMC1.1]
  CDC_COMM_SUBCLASS_MOBILE_DIRECT_LINE_MODEL          , ///<Mobile Direct Line型号[USBWMC1.1]
  CDC_COMM_SUBCLASS_OBEX                              , ///< OBEX  [USBWMC1.1]
  CDC_COMM_SUBCLASS_ETHERNET_EMULATION_MODEL            ///<以太网仿真模型[USBEEM1.0]
} cdc_comm_sublcass_type_t;

///通信接口协议代码
typedef enum
{
  CDC_COMM_PROTOCOL_NONE                   = 0x00 , ///<无特定协议
  CDC_COMM_PROTOCOL_ATCOMMAND                     , ///<AT命令：V.250等
  CDC_COMM_PROTOCOL_ATCOMMAND_PCCA_101            , ///<PCCA-101定义的AT命令
  CDC_COMM_PROTOCOL_ATCOMMAND_PCCA_101_AND_ANNEXO , ///<PCCA-101和附录O定义的AT命令
  CDC_COMM_PROTOCOL_ATCOMMAND_GSM_707             , ///<GSM 07.07定义的AT命令
  CDC_COMM_PROTOCOL_ATCOMMAND_3GPP_27007          , ///<3GPP 27.007定义的AT命令
  CDC_COMM_PROTOCOL_ATCOMMAND_CDMA                , ///<TIA为CDMA定义的AT命令
  CDC_COMM_PROTOCOL_ETHERNET_EMULATION_MODEL        ///<以太网仿真模型
} cdc_comm_protocol_type_t;

//-------------COMM函数描述符中的子类型描述符-------------//
///通信接口子类型描述符
typedef enum
{
  CDC_FUNC_DESC_HEADER                                           = 0x00 , ///＜Header Functional Descriptor，它标记接口的功能描述符连接集的开始。
  CDC_FUNC_DESC_CALL_MANAGEMENT                                  = 0x01 , ///<呼叫管理功能描述符。
  CDC_FUNC_DESC_ABSTRACT_CONTROL_MANAGEMENT                      = 0x02 , ///<抽象控制管理功能描述符。
  CDC_FUNC_DESC_DIRECT_LINE_MANAGEMENT                           = 0x03 , ///<直接线路管理功能描述符。
  CDC_FUNC_DESC_TELEPHONE_RINGER                                 = 0x04 , ///<电话响铃功能描述符。
  CDC_FUNC_DESC_TELEPHONE_CALL_AND_LINE_STATE_REPORTING_CAPACITY = 0x05 , ///<电话呼叫和线路状态报告功能描述符。
  CDC_FUNC_DESC_UNION                                            = 0x06 , ///<联合函数描述符
  CDC_FUNC_DESC_COUNTRY_SELECTION                                = 0x07 , ///<国家选择功能描述符
  CDC_FUNC_DESC_TELEPHONE_OPERATIONAL_MODES                      = 0x08 , ///<电话操作模式功能描述符
  CDC_FUNC_DESC_USB_TERMINAL                                     = 0x09 , ///<USB终端功能描述符
  CDC_FUNC_DESC_NETWORK_CHANNEL_TERMINAL                         = 0x0A , ///<网络信道终端描述符
  CDC_FUNC_DESC_PROTOCOL_UNIT                                    = 0x0B , ///<协议单元功能描述符
  CDC_FUNC_DESC_EXTENSION_UNIT                                   = 0x0C , ///<扩展单元功能描述符
  CDC_FUNC_DESC_MULTICHANEL_MANAGEMENT                           = 0x0D , ///<多通道管理功能描述符
  CDC_FUNC_DESC_CAPI_CONTROL_MANAGEMENT                          = 0x0E , ///<CAPI控制管理功能描述符
  CDC_FUNC_DESC_ETHERNET_NETWORKING                              = 0x0F , ///<以太网网络功能描述符
  CDC_FUNC_DESC_ATM_NETWORKING                                   = 0x10 , ///<ATM网络功能描述符
  CDC_FUNC_DESC_WIRELESS_HANDSET_CONTROL_MODEL                   = 0x11 , ///<无线手持设备控制模型功能描述符
  CDC_FUNC_DESC_MOBILE_DIRECT_LINE_MODEL                         = 0x12 , ///<移动直接线路模型功能描述符
  CDC_FUNC_DESC_MOBILE_DIRECT_LINE_MODEL_DETAIL                  = 0x13 , ///<MDLM详细功能描述符
  CDC_FUNC_DESC_DEVICE_MANAGEMENT_MODEL                          = 0x14 , ///<设备管理模型功能描述符
  CDC_FUNC_DESC_OBEX                                             = 0x15 , ///<OBEX功能描述符
  CDC_FUNC_DESC_COMMAND_SET                                      = 0x16 , ///<命令集功能描述符
  CDC_FUNC_DESC_COMMAND_SET_DETAIL                               = 0x17 , ///<命令集详细功能描述符
  CDC_FUNC_DESC_TELEPHONE_CONTROL_MODEL                          = 0x18 , ///<电话控制模型功能描述符
  CDC_FUNC_DESC_OBEX_SERVICE_IDENTIFIER                          = 0x19   ///<OBEX服务标识符功能描述符
}cdc_func_desc_type_t;

//--------------------------------------------------------------------+
// CDC数据接口类
//--------------------------------------------------------------------+

// 未使用数据接口的SUBCLASS代码，应/必须为零
///数据接口协议代码
typedef enum{
  CDC_DATA_PROTOCOL_ISDN_BRI                               = 0x30, ///<ISDN BRI的物理接口协议
  CDC_DATA_PROTOCOL_HDLC                                   = 0x31, ///< HDLC
  CDC_DATA_PROTOCOL_TRANSPARENT                            = 0x32, ///<透明
  CDC_DATA_PROTOCOL_Q921_MANAGEMENT                        = 0x50, ///<Q.921数据链路协议的管理协议
  CDC_DATA_PROTOCOL_Q921_DATA_LINK                         = 0x51, ///<Q.931的数据链路协议
  CDC_DATA_PROTOCOL_Q921_TEI_MULTIPLEXOR                   = 0x52, ///<Q.921数据链路协议的TEI多路复用器
  CDC_DATA_PROTOCOL_V42BIS_DATA_COMPRESSION                = 0x90, ///<数据压缩程序
  CDC_DATA_PROTOCOL_EURO_ISDN                              = 0x91, ///<欧洲ISDN协议控制
  CDC_DATA_PROTOCOL_V24_RATE_ADAPTION_TO_ISDN              = 0x92, ///<V.24速率适应ISDN
  CDC_DATA_PROTOCOL_CAPI_COMMAND                           = 0x93, ///<CAPI命令
  CDC_DATA_PROTOCOL_HOST_BASED_DRIVER                      = 0xFD, ///<基于主机的驱动程序。注意：此协议代码只能在主机和设备之间的消息中使用，以标识协议堆栈的主机驱动程序部分。
  CDC_DATA_PROTOCOL_IN_PROTOCOL_UNIT_FUNCTIONAL_DESCRIPTOR = 0xFE  ///<使用通信类接口上的ProtocolUnit功能描述符描述协议
}cdc_data_protocol_type_t;

//--------------------------------------------------------------------+
// 管理元素请求（控制端点）
//--------------------------------------------------------------------+

///通信接口管理元素请求代码
typedef enum
{
  CDC_REQUEST_SEND_ENCAPSULATED_COMMAND                    = 0x00, ///<用于以通信类接口支持的控制协议的格式发出命令
  CDC_REQUEST_GET_ENCAPSULATED_RESPONSE                    = 0x01, ///<用于请求通信类接口支持的控制协议格式的响应。

  CDC_REQUEST_SET_COMM_FEATURE                             = 0x02,
  CDC_REQUEST_GET_COMM_FEATURE                             = 0x03,
  CDC_REQUEST_CLEAR_COMM_FEATURE                           = 0x04,

  CDC_REQUEST_SET_AUX_LINE_STATE                           = 0x10,
  CDC_REQUEST_SET_HOOK_STATE                               = 0x11,
  CDC_REQUEST_PULSE_SETUP                                  = 0x12,
  CDC_REQUEST_SEND_PULSE                                   = 0x13,
  CDC_REQUEST_SET_PULSE_TIME                               = 0x14,
  CDC_REQUEST_RING_AUX_JACK                                = 0x15,

  CDC_REQUEST_SET_LINE_CODING                              = 0x20,
  CDC_REQUEST_GET_LINE_CODING                              = 0x21,
  CDC_REQUEST_SET_CONTROL_LINE_STATE                       = 0x22,
  CDC_REQUEST_SEND_BREAK                                   = 0x23,

  CDC_REQUEST_SET_RINGER_PARMS                             = 0x30,
  CDC_REQUEST_GET_RINGER_PARMS                             = 0x31,
  CDC_REQUEST_SET_OPERATION_PARMS                          = 0x32,
  CDC_REQUEST_GET_OPERATION_PARMS                          = 0x33,
  CDC_REQUEST_SET_LINE_PARMS                               = 0x34,
  CDC_REQUEST_GET_LINE_PARMS                               = 0x35,
  CDC_REQUEST_DIAL_DIGITS                                  = 0x36,
  CDC_REQUEST_SET_UNIT_PARAMETER                           = 0x37,
  CDC_REQUEST_GET_UNIT_PARAMETER                           = 0x38,
  CDC_REQUEST_CLEAR_UNIT_PARAMETER                         = 0x39,
  CDC_REQUEST_GET_PROFILE                                  = 0x3A,

  CDC_REQUEST_SET_ETHERNET_MULTICAST_FILTERS               = 0x40,
  CDC_REQUEST_SET_ETHERNET_POWER_MANAGEMENT_PATTERN_FILTER = 0x41,
  CDC_REQUEST_GET_ETHERNET_POWER_MANAGEMENT_PATTERN_FILTER = 0x42,
  CDC_REQUEST_SET_ETHERNET_PACKET_FILTER                   = 0x43,
  CDC_REQUEST_GET_ETHERNET_STATISTIC                       = 0x44,

  CDC_REQUEST_SET_ATM_DATA_FORMAT                          = 0x50,
  CDC_REQUEST_GET_ATM_DEVICE_STATISTICS                    = 0x51,
  CDC_REQUEST_SET_ATM_DEFAULT_VC                           = 0x52,
  CDC_REQUEST_GET_ATM_VC_STATISTICS                        = 0x53,

  CDC_REQUEST_MDLM_SEMANTIC_MODEL                          = 0x60,
}cdc_management_request_t;

//--------------------------------------------------------------------+
// 管理元素通知（通知端点）
//--------------------------------------------------------------------+

///通信接口管理元素通知代码
typedef enum
{
  NETWORK_CONNECTION               = 0x00, ///<此通知允许设备向主机通知网络连接状态。
  RESPONSE_AVAILABLE               = 0x01, ///<此通知允许设备通知主机响应可用。可以使用后续的\ref CDC_REQUEST_GET_ENCAPSULATED_REPONSE请求检索此响应。

  AUX_JACK_HOOK_STATE              = 0x08,
  RING_DETECT                      = 0x09,

  SERIAL_STATE                     = 0x20,

  CALL_STATE_CHANGE                = 0x28,
  LINE_STATE_CHANGE                = 0x29,
  CONNECTION_SPEED_CHANGE          = 0x2A, ///<此通知允许设备通知主机网络驱动程序连接的上游或下游比特率发生了变化
  MDLM_SEMANTIC_MODEL_NOTIFICATION = 0x40,
}cdc_notification_request_t;

//--------------------------------------------------------------------+
// 类特定函数描述符（通信接口）
//--------------------------------------------------------------------+

///标题功能描述符（通信接口）
typedef struct TU_ATTR_PACKED
{
  uint8_t bLength            ; ///<此描述符的大小（字节）。
  uint8_t bDescriptorType    ; ///<描述符类型，必须是类特定的
  uint8_t bDescriptorSubType ; ///<描述符子类型CDC_FUNC_DESC_
  uint16_t bcdCDC            ; ///<CDC版本号（二进制编码十进制）
}cdc_desc_func_header_t;

///联合功能描述符（通信接口）
typedef struct TU_ATTR_PACKED
{
  uint8_t bLength                  ; ///<此描述符的大小（字节）。
  uint8_t bDescriptorType          ; ///<描述符类型，必须是类特定的
  uint8_t bDescriptorSubType       ; ///<描述符子类型CDC_FUCN_DESC_
  uint8_t bControlInterface        ; ///<通信接口的接口编号
  uint8_t bSubordinateInterface    ; ///<数据接口的接口编号数组
}cdc_desc_func_union_t;

#define cdc_desc_func_union_n_t(no_slave)\
 struct TU_ATTR_PACKED { \
  uint8_t bLength                         ;\
  uint8_t bDescriptorType                 ;\
  uint8_t bDescriptorSubType              ;\
  uint8_t bControlInterface               ;\
  uint8_t bSubordinateInterface[no_slave] ;\
}

///国家选择功能描述符（通信接口）
typedef struct TU_ATTR_PACKED
{
  uint8_t bLength             ; ///<此描述符的大小（字节）。
  uint8_t bDescriptorType     ; ///<描述符类型，必须是类特定的
  uint8_t bDescriptorSubType  ; ///<描述符子类型CDC_FUCN_DESC_
  uint8_t iCountryCodeRelDate ; ///<给出已实施ISO 3166国家代码发布日期的字符串索引。
  uint16_t wCountryCode       ; ///<采用[IISO3166]中定义的格式的国家/地区代码，第一个受支持国家/地区的发布日期在偏移集3中指定。
}cdc_desc_func_country_selection_t;

#define cdc_desc_func_country_selection_n_t(no_country) \
  struct TU_ATTR_PACKED {\
  uint8_t bLength                   ;\
  uint8_t bDescriptorType           ;\
  uint8_t bDescriptorSubType        ;\
  uint8_t iCountryCodeRelDate       ;\
  uint16_t wCountryCode[no_country] ;\
}

//--------------------------------------------------------------------+
// PUBLIC SWITCHED TELEPHONE NETWORK (PSTN) SUBCLASS
//--------------------------------------------------------------------+

///\ brief呼叫管理功能描述符
///\details此函数描述符描述通信类接口调用的处理。
typedef struct TU_ATTR_PACKED
{
  uint8_t bLength            ; ///<此描述符的大小（字节）。
  uint8_t bDescriptorType    ; ///<描述符类型，必须是类特定的
  uint8_t bDescriptorSubType ; ///<描述符子类型CDC_FUCN_DESC_

  struct {
    uint8_t handle_call    : 1; ///<0-设备仅通过通信类接口发送/接收呼叫管理信息。1-设备可以通过数据类接口发送/接收呼叫管理信息。
    uint8_t send_recv_call : 1; ///<0-设备本身不处理呼叫管理。1-设备本身处理呼叫管理。
    uint8_t TU_RESERVED    : 6;
  } bmCapabilities;

  uint8_t bDataInterface;
}cdc_desc_func_call_management_t;


typedef struct TU_ATTR_PACKED
{
  uint8_t support_comm_request                    : 1; ///<设备支持Set_Comm_Feature、Clear_Comm_FFeature和Get_Comm_F特徵的请求组合。
  uint8_t support_line_request                    : 1; ///<设备支持Set_Line_Coding、Set_Control_Line_State、Get_Line_Coming和通知Serial_State的请求组合。
  uint8_t support_send_break                      : 1; ///<设备支持请求Send_Break
  uint8_t support_notification_network_connection : 1; ///<设备支持通知Network_Connection。
  uint8_t TU_RESERVED                             : 4;
}cdc_acm_capability_t;

TU_VERIFY_STATIC(sizeof(cdc_acm_capability_t) == 1, "mostly problem with compiler");

///\ brief抽象控件管理功能描述符
///\details此功能描述符描述了通信类接口支持的命令，子类代码为\ref CDC_COMM_SubClass_ABSTRACT_CONTROL_MODEL
typedef struct TU_ATTR_PACKED
{
  uint8_t bLength                  ; ///<此描述符的大小（字节）。
  uint8_t bDescriptorType          ; ///<描述符类型，必须是类特定的
  uint8_t bDescriptorSubType       ; ///<描述符子类型CDC_FUCN_DESC_
  cdc_acm_capability_t bmCapabilities ;
}cdc_desc_func_acm_t;

///\field Direct Line Management功能描述符
///\details此功能描述符描述了通信类接口支持的命令，子类代码为\ref CDC_FUNC_DESC_DIRECT_LINE_MANAGEMENT
typedef struct TU_ATTR_PACKED
{
  uint8_t bLength            ; ///<此描述符的大小（字节）。
  uint8_t bDescriptorType    ; ///<描述符类型，必须是类特定的
  uint8_t bDescriptorSubType ; ///<描述符子类型CDC_FUCN_DESC_
  struct {
    uint8_t require_pulse_setup   : 1; ///<设备在脉冲拨号序列期间需要额外的Pulse_Setup请求以断开保持电路。
    uint8_t support_aux_request   : 1; ///<设备支持Set_Aux_Line_State、Ring_Aux_Jack和通知Aux_Jack_Hook_State的请求组合。
    uint8_t support_pulse_request : 1; ///<设备支持Pulse_Setup、Send_Pulse和Set_Pulse_Time的请求组合。
    uint8_t TU_RESERVED           : 5;
  } bmCapabilities;
}cdc_desc_func_direct_line_management_t;

///电话响铃功能描述符
///电话响铃功能描述符描述了通信类接口支持的响铃功能，
///子类代码为\ref CDC_COMM_SubClass_TELEPHONE_CONTROL_MODEL
typedef struct TU_ATTR_PACKED
{
  uint8_t bLength            ; ///<此描述符的大小（字节）。
  uint8_t bDescriptorType    ; ///<描述符类型，必须是类特定的
  uint8_t bDescriptorSubType ; ///<描述符子类型CDC_FUCN_DESC_
  uint8_t bRingerVolSteps    ;
  uint8_t bNumRingerPatterns ;
}cdc_desc_func_telephone_ringer_t;

///电话操作模式功能描述符
///电话操作模式功能描述符描述了
///通信类接口，子类代码为\ref CDC_COMM_SubClass_TELEPHONE_CONTROL_MODEL
typedef struct TU_ATTR_PACKED
{
  uint8_t bLength            ; ///<此描述符的大小（字节）。
  uint8_t bDescriptorType    ; ///<描述符类型，必须是类特定的
  uint8_t bDescriptorSubType ; ///<描述符子类型CDC_FUCN_DESC_
  struct {
    uint8_t simple_mode           : 1;
    uint8_t standalone_mode       : 1;
    uint8_t computer_centric_mode : 1;
    uint8_t TU_RESERVED           : 5;
  } bmCapabilities;
}cdc_desc_func_telephone_operational_modes_t;

///电话呼叫和线路状态报告功能描述符
///\details电话呼叫和线路状态报告功能描述符描述了
///报告可选呼叫和线路状态的电话设备。
typedef struct TU_ATTR_PACKED
{
  uint8_t bLength            ; ///<此描述符的大小（字节）。
  uint8_t bDescriptorType    ; ///<描述符类型，必须是类特定的
  uint8_t bDescriptorSubType ; ///<描述符子类型CDC_FUCN_DESC_
  struct {
    uint32_t interrupted_dialtone   : 1; ///<0：仅报告拨号音（不区分正常拨号音和中断拨号音）。1：报告正常拨号音之外的中断拨号音
    uint32_t ringback_busy_fastbusy : 1; ///<0:仅报告拨号状态。1：报告回铃、忙和快忙状态。
    uint32_t caller_id              : 1; ///<0:不报告呼叫方ID。1:报告呼叫方标识信息。
    uint32_t incoming_distinctive   : 1; ///<0：仅报告传入振铃。1：报告传入的独特铃声模式。
    uint32_t dual_tone_multi_freq   : 1; ///<0：无法报告通过电话线远程输入的双音多频（DTMF）数字。1：可以报告通过电话线远程输入的DTMF数字。
    uint32_t line_state_change      : 1; ///<0:不支持行状态更改通知。1：是否支持线路状态更改通知
    uint32_t TU_RESERVED            : 26;
  } bmCapabilities;
}cdc_desc_func_telephone_call_state_reporting_capabilities_t;

static inline uint8_t cdc_functional_desc_typeof(uint8_t const * p_desc)
{
  return p_desc[2];
}

//--------------------------------------------------------------------+
// 请求
//--------------------------------------------------------------------+
typedef struct TU_ATTR_PACKED
{
  uint32_t bit_rate;
  uint8_t  stop_bits; ///<0:1停止位-1:1.5停止位-2:2停止位
  uint8_t  parity;    ///<0:无-1:奇数-2:偶数-3:标记-4:空格
  uint8_t  data_bits; ///<可以是5、6、7、8或16
} cdc_line_coding_t;

TU_VERIFY_STATIC(sizeof(cdc_line_coding_t) == 7, "size is not correct");

typedef struct TU_ATTR_PACKED
{
  uint16_t dte_is_present : 1; ///<指示DCE是否存在DTE。该信号对应于V.24信号108/2和RS-232信号DTR。
  uint16_t half_duplex_carrier_control : 1;
  uint16_t : 14;
} cdc_line_control_state_t;

TU_VERIFY_STATIC(sizeof(cdc_line_control_state_t) == 2, "size is not correct");

/** @} */

#ifdef __cplusplus
 }
#endif

#endif

/** @} */

