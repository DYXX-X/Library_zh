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

/** \ingroup CDC_RNDIS\defgroup CDC_RNSID_Host Host
 *  @{ */

#ifndef _TUSB_CDC_RNDIS_HOST_H_
#define _TUSB_CDC_RNDIS_HOST_H_

#include "common/tusb_common.h"
#include "host/usbh.h"
#include "cdc_rndis.h"

#ifdef __cplusplus
 extern "C" {
#endif

//--------------------------------------------------------------------+
// 内部RNDIS-CDC驱动程序API
//--------------------------------------------------------------------+
typedef struct {
  OSAL_SEM_DEF(semaphore_notification);
  osal_semaphore_handle_t sem_notification_hdl;  // 用于等待通知管道
  uint32_t max_xfer_size; // 从设备的消息获取初始化完成
  uint8_t mac_address[6];
}rndish_data_t;

void rndish_init(void);
tusb_error_t rndish_open_subtask(uint8_t dev_addr, cdch_data_t *p_cdc);
void rndish_xfer_isr(cdch_data_t *p_cdc, pipe_handle_t pipe_hdl, xfer_result_t event, uint32_t xferred_bytes);
void rndish_close(uint8_t dev_addr);

#ifdef __cplusplus
 }
#endif

#endif /* _TUSB_CDC_RNDIS_HOST_H_ */

/** @} */

