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

/** \inggroup group_usbh USB主机核心（usbh）
 *  @{ */

#ifndef _TUSB_USBH_H_
#define _TUSB_USBH_H_

#ifdef __cplusplus
 extern "C" {
#endif

//--------------------------------------------------------------------+
// INCLUDE
//--------------------------------------------------------------------+
#include "osal/osal.h" // TODO折射器移动到公共位置。嗯？
#include "hcd.h"

//--------------------------------------------------------------------+
// MACRO CONSTANT TYPEDEF
//--------------------------------------------------------------------+
typedef enum tusb_interface_status_{
  TUSB_INTERFACE_STATUS_READY = 0,
  TUSB_INTERFACE_STATUS_BUSY,
  TUSB_INTERFACE_STATUS_COMPLETE,
  TUSB_INTERFACE_STATUS_ERROR,
  TUSB_INTERFACE_STATUS_INVALID_PARA
} tusb_interface_status_t;

typedef struct {
  #if CFG_TUSB_DEBUG >= 2
  char const* name;
  #endif

  uint8_t class_code;

  void (* const init       )(void);
  bool (* const open       )(uint8_t rhport, uint8_t dev_addr, tusb_desc_interface_t const * itf_desc, uint16_t* outlen);
  bool (* const set_config )(uint8_t dev_addr, uint8_t itf_num);
  bool (* const xfer_cb    )(uint8_t dev_addr, uint8_t ep_addr, xfer_result_t result, uint32_t xferred_bytes);
  void (* const close      )(uint8_t dev_addr);
} usbh_class_driver_t;

typedef bool (*tuh_control_complete_cb_t)(uint8_t dev_addr, tusb_control_request_t const * request, xfer_result_t result);

//--------------------------------------------------------------------+
// INTERNAL OBJECT & FUNCTION DECLARATION
//--------------------------------------------------------------------+

//--------------------------------------------------------------------+
// APPLICATION API
//--------------------------------------------------------------------+

// 初始化主机堆栈
bool tuh_init(void);

// 应在主/rtos循环中调用任务函数
void tuh_task(void);

// 中断处理程序，HCD的别名
extern void hcd_int_handler(uint8_t rhport);
#define tuh_int_handler   hcd_int_handler

tusb_device_state_t tuh_device_get_state (uint8_t dev_addr);
tusb_speed_t tuh_device_get_speed (uint8_t dev_addr);
static inline bool tuh_device_is_configured(uint8_t dev_addr)
{
  return tuh_device_get_state(dev_addr) == TUSB_DEVICE_STATE_CONFIGURED;
}

bool tuh_control_xfer (uint8_t dev_addr, tusb_control_request_t const* request, void* buffer, tuh_control_complete_cb_t complete_cb);

//--------------------------------------------------------------------+
// APPLICATION CALLBACK
//--------------------------------------------------------------------+
//TU_ATTR_WEAK uint8_t tuh_attach_cb（tusb_desc_device_t const*desc_device）；

/**装载（配置）设备时调用回调*/
TU_ATTR_WEAK void tuh_mount_cb (uint8_t dev_addr);

/**卸载设备时调用回调（总线重置/拔出）*/
TU_ATTR_WEAK void tuh_umount_cb(uint8_t dev_addr);

//--------------------------------------------------------------------+
// CLASS-USBH & INTERNAL API
// TODO移动到usbh_pvt.h
//--------------------------------------------------------------------+

bool usbh_edpt_open(uint8_t rhport, uint8_t dev_addr, tusb_desc_endpoint_t const * ep_desc);
bool usbh_edpt_xfer(uint8_t dev_addr, uint8_t ep_addr, uint8_t * buffer, uint16_t total_bytes);

// 在提交传输之前声明端点。
// 若调用者并没有进行任何传输，它必须为其他人释放端点。
bool usbh_edpt_claim(uint8_t dev_addr, uint8_t ep_addr);

void usbh_driver_set_config_complete(uint8_t dev_addr, uint8_t itf_num);

uint8_t usbh_get_rhport(uint8_t dev_addr);

#ifdef __cplusplus
 }
#endif

#endif /* _TUSB_USBH_H_ */

/** @} */

