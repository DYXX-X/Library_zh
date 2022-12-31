
/*
 * MIT许可证（MIT）
 *
 * 版权所有（c）2019 N Conrad
 *
 * 特此免费授予获得本软件和相关文档文件（“软件”）副本的任何人无限制地处理软件的权利，包括但不限于使用、复制、修改、合并、发布、分发、再许可和/或销售软件副本的权利，并允许向其提供软件的人这样做，符合以下条件：
 *
 * 上述版权声明和本许可声明应包含在软件的所有副本或主要部分中。
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * 此文件是TinyUSB堆栈的一部分。
 */

#ifndef _TUSB_USBTMC_H__
#define _TUSB_USBTMC_H__

#include "common/tusb_common.h"


/* 实施USBTMC版本1.0，2003年4月14日

 字符串描述符必须具有“LANGID=0x409”/US英文字符串。字符必须为0x20（“”）到0x7E（“~”）ASCII，但不能包含：“/：？\也不能有前导或尾随空格（“”

 如果USB488设备能力。D2=1（SR1），则必须有INT端点。
*/

#define USBTMC_VERSION 0x0100
#define USBTMC_488_VERSION 0x0100

typedef enum {
  USBTMC_MSGID_DEV_DEP_MSG_OUT = 1u,
  USBTMC_MSGID_DEV_DEP_MSG_IN = 2u,
  USBTMC_MSGID_VENDOR_SPECIFIC_MSG_OUT = 126u,
  USBTMC_MSGID_VENDOR_SPECIFIC_IN = 127u,
  USBTMC_MSGID_USB488_TRIGGER = 128u,
} usbtmc_msgid_enum;

///\brief消息头（用于BULK OUT和BULK IN）；4字节
typedef struct TU_ATTR_PACKED
{
  uint8_t MsgID              ; ///<消息类型ID（usbtmc_msgid_enum）
  uint8_t bTag    		       ; ///<传输ID 1<=bTag<=255
  uint8_t bTagInverse        ; ///<标签的补码
  uint8_t _reserved           ; ///<必须为0x00
} usbtmc_msg_header_t;

typedef struct TU_ATTR_PACKED
{
  usbtmc_msg_header_t header;
  uint8_t data[8];
} usbtmc_msg_generic_t;

/* 在批量输出端点上使用：*/
// 接下来的8个字节是特定于消息的
typedef struct TU_ATTR_PACKED {
	usbtmc_msg_header_t header ; ///<标题
	uint32_t TransferSize      ; ///<传输大小；LSB优先
	struct TU_ATTR_PACKED
	{
	  unsigned int EOM  : 1         ; ///<EOM设置在最后一个字节
  } bmTransferAttributes;
  uint8_t _reserved[3];
} usbtmc_msg_request_dev_dep_out;

TU_VERIFY_STATIC(sizeof(usbtmc_msg_request_dev_dep_out) == 12u, "struct wrong length");

// 接下来的8个字节是特定于消息的
typedef struct TU_ATTR_PACKED
{
  usbtmc_msg_header_t header ; ///<标题
  uint32_t TransferSize      ; ///<传输大小；LSB优先
  struct TU_ATTR_PACKED
  {
    unsigned int TermCharEnabled  : 1 ; ///<“批量输入传输必须在指定的TermChar终止。”；能力必须列出TermChar
  } bmTransferAttributes;
  uint8_t TermChar;
  uint8_t _reserved[2];
} usbtmc_msg_request_dev_dep_in;

TU_VERIFY_STATIC(sizeof(usbtmc_msg_request_dev_dep_in) == 12u, "struct wrong length");

/* 集管中的散装*/

typedef struct TU_ATTR_PACKED
{
  usbtmc_msg_header_t header;
  uint32_t TransferSize;
  struct TU_ATTR_PACKED
  {
    uint8_t EOM: 1;           ///<传输的最后一个字节是消息的结尾
    uint8_t UsingTermChar: 1; ///<支持TermChar&&Request。TermCharEnabled&&传输中的最后一个字符是TermChar
  } bmTransferAttributes;
  uint8_t _reserved[3];
} usbtmc_msg_dev_dep_msg_in_header_t;

TU_VERIFY_STATIC(sizeof(usbtmc_msg_dev_dep_msg_in_header_t) == 12u, "struct wrong length");

/* 不受支持的供应商的东西……这些曾经被使用过吗？*/

typedef struct TU_ATTR_PACKED
{
  usbtmc_msg_header_t header ; ///<标题
  uint32_t TransferSize      ; ///<传输大小；LSB优先
  uint8_t _reserved[4];
} usbtmc_msg_request_vendor_specific_out;


TU_VERIFY_STATIC(sizeof(usbtmc_msg_request_vendor_specific_out) == 12u, "struct wrong length");

typedef struct TU_ATTR_PACKED
{
  usbtmc_msg_header_t header ; ///<标题
  uint32_t TransferSize      ; ///<传输大小；LSB优先
  uint8_t _reserved[4];
} usbtmc_msg_request_vendor_specific_in;

TU_VERIFY_STATIC(sizeof(usbtmc_msg_request_vendor_specific_in) == 12u, "struct wrong length");

// 控制请求类型应使用tusb_Control_request_t

/*
typedef struct TU_ATTR_PACKED｛struct｛unsigned int Recipient:5；///＜EOM set on last byte unsigned int-Type:2；///＞EOM set IN last byte-signed int DirectionToHost：1；///<0是OUT，1是IN｝bmRequestType；uint8_t b请求；///<如果bmRequestType。类型=类，请参见usmtmc_request_Type_enum uint16_t wValue；uint16_t wIndex；uint16_t wLength；//数据阶段中的字节数}usbtmc_class_specific_control_req；

*/
// 批量协议错误
enum {
  USBTMC_BULK_IN_ERR_INCOMPLETE_HEADER = 1u,
  USBTMC_BULK_IN_ERR_UNSUPPORTED = 2u,
  USBTMC_BULK_IN_ERR_BAD_PARAMETER = 3u,
  USBTMC_BULK_IN_ERR_DATA_TOO_SHORT = 4u,
  USBTMC_BULK_IN_ERR_DATA_TOO_LONG = 5u,
};
// bult in halt错误
enum {
  USBTMC_BULK_IN_ERR = 1u, ///<接收USBTMC命令消息
                           ///正在进行批量IN传输
};

typedef enum {
  USBTMC_bREQUEST_INITIATE_ABORT_BULK_OUT      = 1u,
  USBTMC_bREQUEST_CHECK_ABORT_BULK_OUT_STATUS  = 2u,
  USBTMC_bREQUEST_INITIATE_ABORT_BULK_IN       = 3u,
  USBTMC_bREQUEST_CHECK_ABORT_BULK_IN_STATUS   = 4u,
  USBTMC_bREQUEST_INITIATE_CLEAR               = 5u,
  USBTMC_bREQUEST_CHECK_CLEAR_STATUS           = 6u,
  USBTMC_bREQUEST_GET_CAPABILITIES             = 7u,

  USBTMC_bREQUEST_INDICATOR_PULSE               = 64u, // 可选择的

  /****** USBTMC 488 *************/
  USB488_bREQUEST_READ_STATUS_BYTE  = 128u,
  USB488_bREQUEST_REN_CONTROL       = 160u,
  USB488_bREQUEST_GO_TO_LOCAL       = 161u,
  USB488_bREQUEST_LOCAL_LOCKOUT     = 162u,

} usmtmc_request_type_enum;

typedef enum {
  USBTMC_STATUS_SUCCESS = 0x01,
  USBTMC_STATUS_PENDING = 0x02,
  USBTMC_STATUS_FAILED = 0x80,
  USBTMC_STATUS_TRANSFER_NOT_IN_PROGRESS = 0x81,
  USBTMC_STATUS_SPLIT_NOT_IN_PROGRESS = 0x82,
  USBTMC_STATUS_SPLIT_IN_PROGRESS  = 0x83
} usbtmc_status_enum;

/************************************************************
 * 控制响应
 */

typedef struct TU_ATTR_PACKED {
  uint8_t USBTMC_status;                 ///<usbtmc_status_enum
  uint8_t _reserved;
  uint16_t bcdUSBTMC;                    ///< USBTMC_VERSION

  struct TU_ATTR_PACKED
  {
    unsigned int listenOnly :1;
    unsigned int talkOnly :1;
    unsigned int supportsIndicatorPulse :1;
  } bmIntfcCapabilities;
  struct TU_ATTR_PACKED
  {
    unsigned int canEndBulkInOnTermChar :1;
  } bmDevCapabilities;
  uint8_t _reserved2[6];
  uint8_t _reserved3[12];
} usbtmc_response_capabilities_t;

TU_VERIFY_STATIC(sizeof(usbtmc_response_capabilities_t) == 0x18, "struct wrong length");

typedef struct TU_ATTR_PACKED
{
  uint8_t USBTMC_status;
  struct TU_ATTR_PACKED
  {
    unsigned int BulkInFifoBytes :1;
  } bmClear;
} usbtmc_get_clear_status_rsp_t;

TU_VERIFY_STATIC(sizeof(usbtmc_get_clear_status_rsp_t) == 2u, "struct wrong length");

// 用于中止批量输入和批量输出
typedef struct TU_ATTR_PACKED
{
  uint8_t USBTMC_status;
  uint8_t bTag;
} usbtmc_initiate_abort_rsp_t;

TU_VERIFY_STATIC(sizeof(usbtmc_get_clear_status_rsp_t) == 2u, "struct wrong length");

// 用于check_abort_bulk_in_status和check_abort.bulk_out_status
typedef struct TU_ATTR_PACKED
{
  uint8_t USBTMC_status;
  struct TU_ATTR_PACKED
  {
    unsigned int BulkInFifoBytes : 1; ///<有排队的数据或排队的短数据包
  } bmAbortBulkIn;
  uint8_t _reserved[2];               ///<必须为零
  uint32_t NBYTES_RXD_TXD;
} usbtmc_check_abort_bulk_rsp_t;

TU_VERIFY_STATIC(sizeof(usbtmc_check_abort_bulk_rsp_t) == 8u, "struct wrong length");

typedef struct TU_ATTR_PACKED
{
  uint8_t USBTMC_status;                 ///<usbtmc_status_enum
  uint8_t _reserved;
  uint16_t bcdUSBTMC;                    ///< USBTMC_VERSION

  struct TU_ATTR_PACKED
  {
    unsigned int listenOnly :1;
    unsigned int talkOnly :1;
    unsigned int supportsIndicatorPulse :1;
  } bmIntfcCapabilities;

  struct TU_ATTR_PACKED
  {
    unsigned int canEndBulkInOnTermChar :1;
  } bmDevCapabilities;

  uint8_t _reserved2[6];
  uint16_t bcdUSB488;

  struct TU_ATTR_PACKED
  {
    unsigned int is488_2 :1;
    unsigned int supportsREN_GTL_LLO :1;
    unsigned int supportsTrigger :1;
  } bmIntfcCapabilities488;

  struct TU_ATTR_PACKED
  {
    unsigned int SCPI :1;
    unsigned int SR1 :1;
    unsigned int RL1 :1;
    unsigned int DT1 :1;
  } bmDevCapabilities488;
  uint8_t _reserved3[8];
} usbtmc_response_capabilities_488_t;

TU_VERIFY_STATIC(sizeof(usbtmc_response_capabilities_488_t) == 0x18, "struct wrong length");

typedef struct TU_ATTR_PACKED
{
  uint8_t USBTMC_status;
  uint8_t bTag;
  uint8_t statusByte;
} usbtmc_read_stb_rsp_488_t;

TU_VERIFY_STATIC(sizeof(usbtmc_read_stb_rsp_488_t) == 3u, "struct wrong length");

typedef struct TU_ATTR_PACKED
{
  struct TU_ATTR_PACKED
  {
      unsigned int bTag : 7;
      unsigned int one  : 1;
  } bNotify1;
  uint8_t StatusByte;
} usbtmc_read_stb_interrupt_488_t;

TU_VERIFY_STATIC(sizeof(usbtmc_read_stb_interrupt_488_t) == 2u, "struct wrong length");

#endif


