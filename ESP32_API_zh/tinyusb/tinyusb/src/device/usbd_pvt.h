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
#ifndef USBD_PVT_H_
#define USBD_PVT_H_

#include "osal/osal.h"
#include "common/tusb_fifo.h"

#ifdef __cplusplus
 extern "C" {
#endif

//--------------------------------------------------------------------+
// 类驱动程序
//--------------------------------------------------------------------+

typedef struct
{
  #if CFG_TUSB_DEBUG >= 2
  char const* name;
  #endif

  void     (* init             ) (void);
  void     (* reset            ) (uint8_t rhport);
  uint16_t (* open             ) (uint8_t rhport, tusb_desc_interface_t const * desc_intf, uint16_t max_len);
  bool     (* control_xfer_cb  ) (uint8_t rhport, uint8_t stage, tusb_control_request_t const * request);
  bool     (* xfer_cb          ) (uint8_t rhport, uint8_t ep_addr, xfer_result_t event, uint32_t xferred_bytes);
  void     (* sof              ) (uint8_t rhport); /* 可选择的*/
} usbd_class_driver_t;

// 初始化设备堆栈以获取其他类驱动程序时调用。
// 可以选择由应用程序实现以扩展/覆盖类驱动程序支持。
// 注意：当堆栈处于活动状态时，驱动程序阵列必须始终可访问
usbd_class_driver_t const* usbd_app_driver_get_cb(uint8_t* driver_count) TU_ATTR_WEAK;


typedef bool (*usbd_control_xfer_cb_t)(uint8_t rhport, uint8_t stage, tusb_control_request_t const * request);

//--------------------------------------------------------------------+
// USBD端点API
//--------------------------------------------------------------------+

// 打开端点
bool usbd_edpt_open(uint8_t rhport, tusb_desc_endpoint_t const * desc_ep);

// 关闭端点
void usbd_edpt_close(uint8_t rhport, uint8_t ep_addr);

// 提交usb传输
bool usbd_edpt_xfer(uint8_t rhport, uint8_t ep_addr, uint8_t * buffer, uint16_t total_bytes);

// 使用FIFO（环形缓冲区）提交usb ISO传输-FIFO中的所有字节都会被传输
bool usbd_edpt_iso_xfer(uint8_t rhport, uint8_t ep_addr, tu_fifo_t * ff, uint16_t total_bytes);

// 在提交传输之前声明端点。
// 若调用者并没有进行任何传输，它必须为其他人释放端点。
bool usbd_edpt_claim(uint8_t rhport, uint8_t ep_addr);

// 释放端点而不提交传输
bool usbd_edpt_release(uint8_t rhport, uint8_t ep_addr);

// 检查端点传输是否完成
bool usbd_edpt_busy(uint8_t rhport, uint8_t ep_addr);

// 暂停端点
void usbd_edpt_stall(uint8_t rhport, uint8_t ep_addr);

// 清除暂停的端点
void usbd_edpt_clear_stall(uint8_t rhport, uint8_t ep_addr);

// 检查端点是否已停止
bool usbd_edpt_stalled(uint8_t rhport, uint8_t ep_addr);

static inline
bool usbd_edpt_ready(uint8_t rhport, uint8_t ep_addr)
{
  return !usbd_edpt_busy(rhport, ep_addr) && !usbd_edpt_stalled(rhport, ep_addr);
}

/*------------------------------------------------------------------*/
/* 帮手
 *------------------------------------------------------------------*/

bool usbd_open_edpt_pair(uint8_t rhport, uint8_t const* p_desc, uint8_t ep_count, uint8_t xfer_type, uint8_t* ep_out, uint8_t* ep_in);
void usbd_defer_func( osal_task_func_t func, void* param, bool in_isr );


#ifdef __cplusplus
 }
#endif

#endif /* USBD_PVT_H_ */

