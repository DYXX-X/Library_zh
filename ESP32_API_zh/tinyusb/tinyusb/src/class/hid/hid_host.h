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

/** \添加组ClassDriver_HID
 *  @{ */

#ifndef _TUSB_HID_HOST_H_
#define _TUSB_HID_HOST_H_

#include "common/tusb_common.h"
#include "host/usbh.h"
#include "hid.h"

#ifdef __cplusplus
 extern "C" {
#endif

//--------------------------------------------------------------------+
// KEYBOARD应用程序API
//--------------------------------------------------------------------+
/** \addtogroup ClassDriver_HID_键盘键盘
 *  @{ */

/** \defgroup Keyboard_Host Host接口API包括状态检查功能、数据传输功能和回调功能
 *  @{ */

extern uint8_t const hid_keycode_to_ascii_tbl[2][128]; // 如果在未启用KEYBOARD的情况下生成失败，TODO使用了弱属性

/** \brief检查设备是否支持键盘接口\param[in]dev_addr设备地址\retval true如果设备支持键盘接口\retval false如果设备不支持键盘接口或未安装
 */
bool tuh_hid_keyboard_is_mounted(uint8_t dev_addr);

/** \brief检查接口当前是否忙\param[in]dev_addr device address\retval true如果接口忙，则表示堆栈仍在从设备/向设备传输/等待数据\retval false如果接口不忙，则意味着堆栈已成功从设备/设备传输数据\note此函数主要用于在\ref之后轮询/等待结果tuh-hid_keyboard_get_report。或者，可以使用异步事件API
 */
bool tuh_hid_keyboard_is_busy(uint8_t dev_addr);

/** \brief从键盘接口\param[in]dev_addr设备地址\param[in，out]p_report地址执行获取报告，该地址用于存储设备中的数据。必须可通过usb控制器访问（请参阅\ref CFG_TUSB_MEM_SECTION）\returns\ref TUSB_error_t类型以指示成功或错误情况。\成功时retval TUSB_ERROR_NONE \如果接口已经在与设备传输数据，则retval TUSB _ERROR_INTERFACE_IS_BUSY \如果设备尚未配置（通过SET configured请求），则ret瓦尔TUSB_ERR OR_device_NOT_READY \如果输入参数不正确，则retvalTUSB_EERROR_INVALID_PARA \注意：此函数不阻塞，并立即返回。usb传输的结果将由接口的回调函数报告
 */
tusb_error_t  tuh_hid_keyboard_get_report(uint8_t dev_addr, void * p_report);

//-------------应用程序回调-------------//
/** \发生传输事件时调用的简短回调函数\param[in]dev_addr设备的地址\param[iin]event来自\ref xfer_result_t\note事件的值可以是以下值之一
 *              -XFER_RESULT_SSUCCESS：先前计划的传输成功完成。
 *              -XFER_RESULT_FAILED:先前计划的传输遇到事务错误。
 *              -XFER_RESULT_STALLED：设备暂停了先前计划的传输。\注意：应用程序应通过在此回调中调用\ref tuh_hid_keyboard_get_report来计划下一个报告
 */
void tuh_hid_keyboard_isr(uint8_t dev_addr, xfer_result_t event);

/** \安装带有键盘接口的设备时将调用的简短回调函数\param[in]dev_addr新安装设备的地址\注意应用程序应使用此回调设置接口相关数据
 */
void tuh_hid_keyboard_mounted_cb(uint8_t dev_addr);

/** \卸载带有键盘接口的设备时将调用的简短回调函数\param[in]dev_addr新卸载设备的地址\注意：应用程序应使用此回调来删除与接口相关的数据
 */
void tuh_hid_keyboard_unmounted_cb(uint8_t dev_addr);

/** @} */ // 键盘_主机
/** @} */ // ClassDriver_HID_键盘

//--------------------------------------------------------------------+
// MOUSE应用程序API
//--------------------------------------------------------------------+
/** \添加组ClassDriver_HID_Mouse鼠标
 *  @{ */

/** \defgroup Mouse_Host Host接口API包括状态检查功能、数据传输功能和回调功能
 *  @{ */

/** \brief检查设备是否支持鼠标接口\param[in]dev_addr设备地址\retval true如果设备支持鼠标接口\retval false如果设备不支持鼠标接口或未安装
 */
bool          tuh_hid_mouse_is_mounted(uint8_t dev_addr);

/** \brief检查接口当前是否忙\param[in]dev_addr device address\retval true如果接口忙，则表示堆栈仍在从设备/向设备传输/等待数据\retval false如果接口不忙，则意味着堆栈已成功从设备/设备传输数据\note此函数主要用于在\ref之后轮询/等待结果tuh-hid_muse_get_report。或者，可以使用异步事件API
 */
bool          tuh_hid_mouse_is_busy(uint8_t dev_addr);

/** \brief从鼠标界面执行获取报告\param[in]dev_addr设备地址\param[in，out]p_report地址，用于存储设备中的数据。必须可通过usb控制器访问（请参阅\ref CFG_TUSB_MEM_SECTION）\returns\ref TUSB_error_t类型以指示成功或错误情况。\成功时retval TUSB_ERROR_NONE \如果接口已经在与设备传输数据，则retval TUSB _ERROR_INTERFACE_IS_BUSY \如果设备尚未配置（通过SET configured请求），则ret瓦尔TUSB_ERR OR_device_NOT_READY \如果输入参数不正确，则retvalTUSB_EERROR_INVALID_PARA \注意：此函数不阻塞，并立即返回。usb传输的结果将由接口的回调函数报告
 */
tusb_error_t  tuh_hid_mouse_get_report(uint8_t dev_addr, void* p_report);

//-------------应用程序回调-------------//
/** \发生传输事件时调用的简短回调函数\param[in]dev_addr设备的地址\param[iin]event来自\ref xfer_result_t\note事件的值可以是以下值之一
 *              -XFER_RESULT_SSUCCESS：先前计划的传输成功完成。
 *              -XFER_RESULT_FAILED:先前计划的传输遇到事务错误。
 *              -XFER_RESULT_STALLED：设备暂停了先前计划的传输。\注意：应用程序应通过在此回调中调用\ref tuh_hid_muse_get_report来安排下一个报告
 */
void tuh_hid_mouse_isr(uint8_t dev_addr, xfer_result_t event);

/** \安装带有鼠标接口的设备时将调用的简短回调函数\param[in]dev_addr新安装设备的地址\注意应用程序应使用此回调设置接口相关数据
 */
void tuh_hid_mouse_mounted_cb(uint8_t dev_addr);

/** \卸载带有鼠标接口的设备时将调用的简短回调函数\param[in]dev_addr新卸载设备的地址\注意：应用程序应使用此回调来删除与接口相关的数据
 */
void tuh_hid_mouse_unmounted_cb(uint8_t dev_addr);

/** @} */ // 鼠标_主机
/** @} */ // 类驱动程序_HID_Mouse

//--------------------------------------------------------------------+
// GENERIC应用程序API
//--------------------------------------------------------------------+
/** \addtogroup ClassDriver_HID_Generic Generic（尚不支持）
 *  @{ */

/** \defgroup Generic_Host Host接口API包括状态检查函数、数据传输函数和回调函数
 *  @{ */

bool          tuh_hid_generic_is_mounted(uint8_t dev_addr);
tusb_error_t  tuh_hid_generic_get_report(uint8_t dev_addr, void* p_report, bool int_on_complete);
tusb_error_t  tuh_hid_generic_set_report(uint8_t dev_addr, void* p_report, bool int_on_complete);
tusb_interface_status_t tuh_hid_generic_get_status(uint8_t dev_addr);
tusb_interface_status_t tuh_hid_generic_set_status(uint8_t dev_addr);

//-------------应用程序回调-------------//
void tuh_hid_generic_isr(uint8_t dev_addr, xfer_result_t event);

/** @} */ // 通用_主机
/** @} */ // 类驱动程序_HID_Generic

//--------------------------------------------------------------------+
// 内部类驱动程序API
//--------------------------------------------------------------------+
void hidh_init(void);
bool hidh_open_subtask(uint8_t rhport, uint8_t dev_addr, tusb_desc_interface_t const *p_interface_desc, uint16_t *p_length);
bool hidh_set_config(uint8_t dev_addr, uint8_t itf_num);
bool hidh_xfer_cb(uint8_t dev_addr, uint8_t ep_addr, xfer_result_t event, uint32_t xferred_bytes);
void hidh_close(uint8_t dev_addr);

#ifdef __cplusplus
}
#endif

#endif /* _TUSB_HID_HOST_H_ */

/** @} */ // 类驱动程序_HID

