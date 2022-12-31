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

/** \inggroup group_usbd\defgroup group_dcd设备控制器驱动程序（dcd）
 *  @{ */

#ifndef _TUSB_DCD_H_
#define _TUSB_DCD_H_

#include "common/tusb_common.h"
#include "common/tusb_fifo.h"

#ifdef __cplusplus
 extern "C" {
#endif

typedef enum
{
  DCD_EVENT_INVALID = 0,
  DCD_EVENT_BUS_RESET,
  DCD_EVENT_UNPLUGGED,
  DCD_EVENT_SOF,
  DCD_EVENT_SUSPEND, // TODO LPM Sleep L1支持
  DCD_EVENT_RESUME,

  DCD_EVENT_SETUP_RECEIVED,
  DCD_EVENT_XFER_COMPLETE,

  // 不是DCD事件，只是延迟ISR功能的一种方便方式
  USBD_EVENT_FUNC_CALL,

  DCD_EVENT_COUNT
} dcd_eventid_t;

typedef struct TU_ATTR_ALIGNED(4)
{
  uint8_t rhport;
  uint8_t event_id;

  union
  {
    // BUS RESET
    struct {
      tusb_speed_t speed;
    } bus_reset;

    // SETUP_RECEIVED
    tusb_control_request_t setup_received;

    // XFER_COMPLETE
    struct {
      uint8_t  ep_addr;
      uint8_t  result;
      uint32_t len;
    }xfer_complete;

    // FUNC_CALL
    struct {
      void (*func) (void*);
      void* param;
    }func_call;
  };
} dcd_event_t;

//TU_VERIFY_STATIC（sizeof（dcd_event_t）<=12，“大小不正确”）；

//--------------------------------------------------------------------+
// 控制器API
//--------------------------------------------------------------------+

// 将控制器初始化为设备模式
void dcd_init       (uint8_t rhport);

// 中断处理程序
void dcd_int_handler(uint8_t rhport);

// 启用设备中断
void dcd_int_enable (uint8_t rhport);

// 禁用设备中断
void dcd_int_disable(uint8_t rhport);

// 接收设置地址请求，mcu端口还必须包括状态IN响应
void dcd_set_address(uint8_t rhport, uint8_t dev_addr);

// 唤醒主机
void dcd_remote_wakeup(uint8_t rhport);

// 通过启用D+/D上的内部上拉电阻器进行连接-
void dcd_connect(uint8_t rhport) TU_ATTR_WEAK;

// 通过禁用D+/D上的内部上拉电阻器断开-
void dcd_disconnect(uint8_t rhport) TU_ATTR_WEAK;

//--------------------------------------------------------------------+
// 端点API
//--------------------------------------------------------------------+

// 在控制传输的状态阶段完成时调用。
// 可以帮助DCD为下一次控制转移做好准备，此API是可选的。
void dcd_edpt0_status_complete(uint8_t rhport, tusb_control_request_t const * request) TU_ATTR_WEAK;

// 根据描述符配置端点的寄存器
bool dcd_edpt_open            (uint8_t rhport, tusb_desc_endpoint_t const * p_endpoint_desc);

// 关闭端点。
// 由于它很弱，调用方必须在调用它之前TU_ASSERT该函数的存在。
void dcd_edpt_close           (uint8_t rhport, uint8_t ep_addr) TU_ATTR_WEAK;

// 提交传输，当调用完成dcd_event_xfer_complete（）通知堆栈时
bool dcd_edpt_xfer            (uint8_t rhport, uint8_t ep_addr, uint8_t * buffer, uint16_t total_bytes);

// 使用fifo提交传输，当调用完成dcd_event_xfer_complete（）通知堆栈时
// 此API是可选的，可能对基于寄存器的数据传输有用。
bool dcd_edpt_xfer_fifo       (uint8_t rhport, uint8_t ep_addr, tu_fifo_t * ff, uint16_t total_bytes) TU_ATTR_WEAK;

// 暂停端点
void dcd_edpt_stall           (uint8_t rhport, uint8_t ep_addr);

// 清除暂停，数据切换也重置为DATA0
void dcd_edpt_clear_stall     (uint8_t rhport, uint8_t ep_addr);

//--------------------------------------------------------------------+
// 事件API（由堆栈实现）
//--------------------------------------------------------------------+

// 由DCD调用以通知设备堆栈
extern void dcd_event_handler(dcd_event_t const * event, bool in_isr);

// 发送总线信号事件的助手
extern void dcd_event_bus_signal (uint8_t rhport, dcd_eventid_t eid, bool in_isr);

// 发送总线重置事件的助手
extern void dcd_event_bus_reset (uint8_t rhport, tusb_speed_t speed, bool in_isr);

// 收到要发送安装程序的助手
extern void dcd_event_setup_received(uint8_t rhport, uint8_t const * setup, bool in_isr);

// 发送传输完成事件的助手
extern void dcd_event_xfer_complete (uint8_t rhport, uint8_t ep_addr, uint32_t xferred_bytes, uint8_t result, bool in_isr);

#ifdef __cplusplus
 }
#endif

#endif /* _TUSB_DCD_H_ */

/// @}

