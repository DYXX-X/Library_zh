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

/** \inggroup group_class\defgroup group_Custom自定义类（尚不支持）
 *  @{ */

#ifndef _TUSB_VENDOR_HOST_H_
#define _TUSB_VENDOR_HOST_H_

#include "common/tusb_common.h"
#include "host/usbh.h"

#ifdef __cplusplus
 extern "C" {
#endif

typedef struct {
  pipe_handle_t pipe_in;
  pipe_handle_t pipe_out;
}custom_interface_info_t;

//--------------------------------------------------------------------+
// USBH-CLASS DRIVER API
//--------------------------------------------------------------------+
static inline bool tusbh_custom_is_mounted(uint8_t dev_addr, uint16_t vendor_id, uint16_t product_id)
{
  (void) vendor_id; // TODO稍后检查
  (void) product_id;
//  返回（tusbh_device_get_mounted_class_flag（dev_addr）和TU_BIT（TUSB_class_MAPPED_INDEX_END-1））！=0;
  return false;
}

tusb_error_t tusbh_custom_read(uint8_t dev_addr, uint16_t vendor_id, uint16_t product_id, void * p_buffer, uint16_t length);
tusb_error_t tusbh_custom_write(uint8_t dev_addr, uint16_t vendor_id, uint16_t product_id, void const * p_data, uint16_t length);

//--------------------------------------------------------------------+
// 内部类驱动程序API
//--------------------------------------------------------------------+
void         cush_init(void);
tusb_error_t cush_open_subtask(uint8_t dev_addr, tusb_desc_interface_t const *p_interface_desc, uint16_t *p_length);
void         cush_isr(pipe_handle_t pipe_hdl, xfer_result_t event);
void         cush_close(uint8_t dev_addr);

#ifdef __cplusplus
 }
#endif

#endif /* _TUSB_VENDOR_HOST_H_ */

/** @} */

