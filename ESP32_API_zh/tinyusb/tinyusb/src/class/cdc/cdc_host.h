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

#ifndef _TUSB_CDC_HOST_H_
#define _TUSB_CDC_HOST_H_

#include "common/tusb_common.h"
#include "host/usbh.h"
#include "cdc.h"

#ifdef __cplusplus
 extern "C" {
#endif

//--------------------------------------------------------------------+
// CDC APPLICATION PUBLIC API
//--------------------------------------------------------------------+
/** \ingroup ClassDriver_CDC通信设备类（CDC）\addtogroup CDC_Serial Serial@{\defgroup CDC_Serial_Host主机
 * @{ */

bool tuh_cdc_set_control_line_state(uint8_t dev_addr, bool dtr, bool rts, tuh_control_complete_cb_t complete_cb);

static inline bool tuh_cdc_connect(uint8_t dev_addr, tuh_control_complete_cb_t complete_cb)
{
  return tuh_cdc_set_control_line_state(dev_addr, true, true, complete_cb);
}

static inline bool tuh_cdc_disconnect(uint8_t dev_addr, tuh_control_complete_cb_t complete_cb)
{
  return tuh_cdc_set_control_line_state(dev_addr, false, false, complete_cb);
}

/** \brief检查设备是否支持CDC串行接口\param[in]dev_addr设备地址\retval true如果设备支持\retval false如果设备不支持或未安装
 */
bool tuh_cdc_serial_is_mounted(uint8_t dev_addr);

/** \brief检查接口当前是否忙\param[in]dev_addr设备地址\param[iin]pipeid value from \ref cdc_pipeid_t以指示目标管道。\retval true（如果接口忙），表示堆栈仍在从/向设备传输/等待数据；retval false（如果接口不忙），则表示堆栈已成功从/到设备传输数据。注意：此函数用于检查上一次传输是否完成（成功或错误），以便安排下一次传输。在调用此函数之前，用户需要确保安装了相应的接口（通过\ref tuh_cdc_serial_is_mounted）。
 */
bool tuh_cdc_is_busy(uint8_t dev_addr, cdc_pipeid_t pipeid);

/** \brief将USB OUT传输到设备\param[in]dev_addr设备地址\param[iin]p_data包含数据的缓冲区。必须可由USB控制器访问（请参阅\ref CFG_TUSB_MEM_SECTION）\param[in]length要通过USB总线传输的字节数\retval TUSB_ERROR_NONE on success \retval TUSB_ERROR_INTERFACE_IS_BUSY，如果接口已经与设备传输数据\retval TUSB_ERROR _device_NOT_READY，如果设备尚未配置（通过SET configured请求）\retval参数不正确\注意：此函数是非阻塞的，并立即返回。USB传输的结果将由接口的回调函数报告。\p_data必须用\ref CFG_TUSB_MEM_SECTION声明。
 */
bool tuh_cdc_send(uint8_t dev_addr, void const * p_data, uint32_t length, bool is_notify);

/** \brief执行USB IN传输以从包含接收数据的设备\param[IN]dev_addr设备地址\param[iin]p_buffer缓冲区获取数据。必须可由USB控制器访问（请参阅\ref CFG_TUSB_MEM_SECTION）\param[in]length要通过USB总线传输的字节数\retval TUSB_ERROR_NONE on success \retval TUSB_ERROR_INTERFACE_IS_BUSY，如果接口已经与设备传输数据\retval TUSB_ERROR _device_NOT_READY，如果设备尚未配置（通过SET configured请求）\retval参数不正确\注意：此函数是非阻塞的，并立即返回。USB传输的结果将由接口的回调函数报告。\p_data必须用\ref CFG_TUSB_MEM_SECTION声明。
 */
bool tuh_cdc_receive(uint8_t dev_addr, void * p_buffer, uint32_t length, bool is_notify);

//--------------------------------------------------------------------+
// CDC APPLICATION CALLBACKS
//--------------------------------------------------------------------+

/** \发生传输事件时调用的简短回调函数\param[in]dev_addr设备的地址\param[iin]event来自\ref xfer_result_t的值\param[in]pipe_id来自\ref cdc_pipeid_t的值指示管道\param[i]xferred_bytes通过USB总线传输的字节数\注意事件可以是以下之一
 *              -XFER_RESULT_SSUCCESS：先前计划的传输成功完成。
 *              -XFER_RESULT_FAILED:先前计划的传输遇到事务错误。
 *              -XFER_RESULT_STALLED：设备暂停了先前计划的传输。\注释
 */
void tuh_cdc_xfer_isr(uint8_t dev_addr, xfer_result_t event, cdc_pipeid_t pipe_id, uint32_t xferred_bytes);

///@}//组CDC_Serial_Host
/// @}

//--------------------------------------------------------------------+
// 内部类驱动程序API
//--------------------------------------------------------------------+
void cdch_init(void);
bool cdch_open(uint8_t rhport, uint8_t dev_addr, tusb_desc_interface_t const *itf_desc, uint16_t *p_length);
bool cdch_set_config(uint8_t dev_addr, uint8_t itf_num);
bool cdch_xfer_cb(uint8_t dev_addr, uint8_t ep_addr, xfer_result_t event, uint32_t xferred_bytes);
void cdch_close(uint8_t dev_addr);

#ifdef __cplusplus
 }
#endif

#endif /* _TUSB_CDC_HOST_H_ */

