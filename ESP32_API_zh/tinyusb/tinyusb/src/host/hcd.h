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

/** \inggroup group_usbh\defgroup group_HCD主机控制器驱动程序（HCD）
 *  @{ */

#ifndef _TUSB_HCD_H_
#define _TUSB_HCD_H_

#include <common/tusb_common.h>

#ifdef __cplusplus
 extern "C" {
#endif

 //--------------------------------------------------------------------+
// MACRO CONSTANT TYPEDEF
//--------------------------------------------------------------------+
typedef enum
{
  HCD_EVENT_DEVICE_ATTACH,
  HCD_EVENT_DEVICE_REMOVE,
  HCD_EVENT_XFER_COMPLETE,

  // 不是HCD事件，只是延迟ISR功能的一种方便方式
  USBH_EVENT_FUNC_CALL,

  HCD_EVENT_COUNT
} hcd_eventid_t;

typedef struct
{
  uint8_t rhport;
  uint8_t event_id;
  uint8_t dev_addr;

  union
  {
    // 连接、删除
    struct {
      uint8_t hub_addr;
      uint8_t hub_port;
    } connection;

    // XFER_COMPLETE
    struct {
      uint8_t ep_addr;
      uint8_t result;
      uint32_t len;
    } xfer_complete;

    // FUNC_CALL
    struct {
      void (*func) (void*);
      void* param;
    }func_call;
  };

} hcd_event_t;

#if TUSB_OPT_HOST_ENABLED
// 每个设备的最大端点数
enum {
  HCD_MAX_ENDPOINT = CFG_TUSB_HOST_DEVICE_MAX*(CFG_TUH_HUB + CFG_TUH_HID_KEYBOARD + CFG_TUH_HID_MOUSE + CFG_TUSB_HOST_HID_GENERIC +
                     CFG_TUH_MSC*2 + CFG_TUH_CDC*3),

  HCD_MAX_XFER     = HCD_MAX_ENDPOINT*2,
};

//#定义HCD_MAX_ENDPOINT 16
//#定义HCD_MAX_XFER 16
#endif

//--------------------------------------------------------------------+
// 控制器和端口API
//--------------------------------------------------------------------+
bool hcd_init(uint8_t rhport);
void hcd_int_handler(uint8_t rhport);
void hcd_int_enable (uint8_t rhport);
void hcd_int_disable(uint8_t rhport);

// 获取微帧编号（125 us）
uint32_t hcd_uframe_number(uint8_t rhport);

// 获取帧数（1ms）
static inline uint32_t hcd_frame_number(uint8_t rhport)
{
  return hcd_uframe_number(rhport) >> 3;
}

///返回roothub端口的当前连接状态
bool hcd_port_connect_status(uint8_t hostid);
void hcd_port_reset(uint8_t hostid);
void hcd_port_reset_end(uint8_t rhport);
tusb_speed_t hcd_port_speed_get(uint8_t hostid);

// HCD关闭属于此设备的所有打开端点
void hcd_device_close(uint8_t rhport, uint8_t dev_addr);

//--------------------------------------------------------------------+
// 端点API
//--------------------------------------------------------------------+
bool hcd_setup_send(uint8_t rhport, uint8_t dev_addr, uint8_t const setup_packet[8]);
bool hcd_edpt_open(uint8_t rhport, uint8_t dev_addr, tusb_desc_endpoint_t const * ep_desc);

bool hcd_edpt_busy(uint8_t dev_addr, uint8_t ep_addr);
bool hcd_edpt_stalled(uint8_t dev_addr, uint8_t ep_addr);
bool hcd_edpt_clear_stall(uint8_t dev_addr, uint8_t ep_addr);

// TODO与pipe_xfer合并
bool hcd_edpt_xfer(uint8_t rhport, uint8_t dev_addr, uint8_t ep_addr, uint8_t * buffer, uint16_t buflen);

//--------------------------------------------------------------------+
// PIPE API
//--------------------------------------------------------------------+
// TODO控件xfer应通过usbh层使用
bool hcd_pipe_queue_xfer(uint8_t dev_addr, uint8_t ep_addr, uint8_t buffer[], uint16_t total_bytes); // 仅队列，尚未传输
bool hcd_pipe_xfer(uint8_t dev_addr, uint8_t ep_addr, uint8_t buffer[], uint16_t total_bytes, bool int_on_complete);

// tusb_error_t hcd_pipe_cancel（）；

//--------------------------------------------------------------------+
// 事件API（由堆栈实现）
//--------------------------------------------------------------------+

// 由HCD调用以通知堆栈
extern void hcd_event_handler(hcd_event_t const* event, bool in_isr);

// 发送设备附加事件的帮助程序
extern void hcd_event_device_attach(uint8_t rhport, bool in_isr);

// 帮助程序发送设备删除事件
extern void hcd_event_device_remove(uint8_t rhport, bool in_isr);

// 帮助程序发送USB传输事件
extern void hcd_event_xfer_complete(uint8_t dev_addr, uint8_t ep_addr, uint32_t xferred_bytes, xfer_result_t result, bool in_isr);

#ifdef __cplusplus
 }
#endif

#endif /* _TUSB_HCD_H_ */

/// @}

