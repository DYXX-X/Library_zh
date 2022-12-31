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

#ifndef _TUSB_DCD_LPC17_40_H_
#define _TUSB_DCD_LPC17_40_H_

#include "common/tusb_common.h"

#ifdef __cplusplus
 extern "C" {
#endif

//--------------------------------------------------------------------+
// 寄存器接口
//--------------------------------------------------------------------+

//-------------USB中断USBIntSt-------------//
//枚举{
//  DCD_USB_REQ_LOW_PRIO_MASK   = TU_BIT(0),
//  DCD_USB_REQ_HIGH_PRIO_MASK  = TU_BIT(1),
//  DCD_USB_REQ_DMA_MASK        = TU_BIT(2),
//  DCD_USB_REQ_NEED_CLOCK_MASK = TU_BIT(8),
//  DCD_USB_REQ_ENABLE_MASK     = TU_BIT(31)
//};

//-------------设备中断USBDevInt-------------//
enum {
  DEV_INT_FRAME_MASK              = TU_BIT(0),
  DEV_INT_ENDPOINT_FAST_MASK      = TU_BIT(1),
  DEV_INT_ENDPOINT_SLOW_MASK      = TU_BIT(2),
  DEV_INT_DEVICE_STATUS_MASK      = TU_BIT(3),
  DEV_INT_COMMAND_CODE_EMPTY_MASK = TU_BIT(4),
  DEV_INT_COMMAND_DATA_FULL_MASK  = TU_BIT(5),
  DEV_INT_RX_ENDPOINT_PACKET_MASK = TU_BIT(6),
  DEV_INT_TX_ENDPOINT_PACKET_MASK = TU_BIT(7),
  DEV_INT_ENDPOINT_REALIZED_MASK  = TU_BIT(8),
  DEV_INT_ERROR_MASK              = TU_BIT(9)
};

//-------------DMA中断USBDMAInt-------------//
enum {
  DMA_INT_END_OF_XFER_MASK    = TU_BIT(0),
  DMA_INT_NEW_DD_REQUEST_MASK = TU_BIT(1),
  DMA_INT_ERROR_MASK          = TU_BIT(2)
};

//-------------USB控制-------------//
enum {
  USBCTRL_READ_ENABLE_MASK  = TU_BIT(0),
  USBCTRL_WRITE_ENABLE_MASK = TU_BIT(1),
};

//-------------USBRxLen-------------//
enum {
  USBRXPLEN_PACKET_LENGTH_MASK = (TU_BIT(10)-1),
  USBRXPLEN_DATA_VALID_MASK    = TU_BIT(10),
  USBRXPLEN_PACKET_READY_MASK  = TU_BIT(11),
};

//-------------SIE命令代码-------------//
typedef enum
{
  SIE_CMDPHASE_WRITE   = 1,
  SIE_CMDPHASE_READ    = 2,
  SIE_CMDPHASE_COMMAND = 5
} sie_cmdphase_t;

enum {
  // 设备命令
  SIE_CMDCODE_SET_ADDRESS                     = 0xd0,
  SIE_CMDCODE_CONFIGURE_DEVICE                = 0xd8,
  SIE_CMDCODE_SET_MODE                        = 0xf3,
  SIE_CMDCODE_READ_FRAME_NUMBER               = 0xf5,
  SIE_CMDCODE_READ_TEST_REGISTER              = 0xfd,
  SIE_CMDCODE_DEVICE_STATUS                   = 0xfe,
  SIE_CMDCODE_GET_ERROR                       = 0xff,
  SIE_CMDCODE_READ_ERROR_STATUS               = 0xfb,

  // 端点命令
  SIE_CMDCODE_ENDPOINT_SELECT                 = 0x00, // +端点索引
  SIE_CMDCODE_ENDPOINT_SELECT_CLEAR_INTERRUPT = 0x40, // +端点索引，应改用USBEpIntClr
  SIE_CMDCODE_ENDPOINT_SET_STATUS             = 0x40, // +端点索引
  SIE_CMDCODE_BUFFER_CLEAR                    = 0xf2,
  SIE_CMDCODE_BUFFER_VALIDATE                 = 0xfa
};

//-------------SIE设备状态（从SIE_CMDCODE_Device_Status获取/设置）-------------//
enum {
  SIE_DEV_STATUS_CONNECT_STATUS_MASK = TU_BIT(0),
  SIE_DEV_STATUS_CONNECT_CHANGE_MASK = TU_BIT(1),
  SIE_DEV_STATUS_SUSPEND_MASK        = TU_BIT(2),
  SIE_DEV_STATUS_SUSPEND_CHANGE_MASK = TU_BIT(3),
  SIE_DEV_STATUS_RESET_MASK          = TU_BIT(4)
};

//-------------SIE选择端点命令-------------//
enum {
  SIE_SELECT_ENDPOINT_FULL_EMPTY_MASK         = TU_BIT(0), // 0：空，1已满。IN端点检查为空，OUT端点检查为满
  SIE_SELECT_ENDPOINT_STALL_MASK              = TU_BIT(1),
  SIE_SELECT_ENDPOINT_SETUP_RECEIVED_MASK     = TU_BIT(2), // 由SIE_CMDCODE_ENDPOINT_SELECT_clear_INTERRUPT清除
  SIE_SELECT_ENDPOINT_PACKET_OVERWRITTEN_MASK = TU_BIT(3), // 上一个数据包被SETUP数据包覆盖
  SIE_SELECT_ENDPOINT_NAK_MASK                = TU_BIT(4), // 最后一个数据包响应是NAK（通过ACK自动清除）
  SIE_SELECT_ENDPOINT_BUFFER1_FULL_MASK       = TU_BIT(5),
  SIE_SELECT_ENDPOINT_BUFFER2_FULL_MASK       = TU_BIT(6)
};

typedef enum
{
  SIE_SET_ENDPOINT_STALLED_MASK           = TU_BIT(0),
  SIE_SET_ENDPOINT_DISABLED_MASK          = TU_BIT(5),
  SIE_SET_ENDPOINT_RATE_FEEDBACK_MASK     = TU_BIT(6),
  SIE_SET_ENDPOINT_CONDITION_STALLED_MASK = TU_BIT(7),
}sie_endpoint_set_status_mask_t;

//-------------DMA描述符状态-------------//
enum {
  DD_STATUS_NOT_SERVICED = 0,
  DD_STATUS_BEING_SERVICED,
  DD_STATUS_NORMAL,
  DD_STATUS_DATA_UNDERUN, // 短数据包
  DD_STATUS_DATA_OVERRUN,
  DD_STATUS_SYSTEM_ERROR
};

#ifdef __cplusplus
 }
#endif

#endif

