/* 
 * MIT许可证（MIT）
 *
 * 版权所有（c）2020 Jerzy Kasenberg
 *
 * 特此免费授予获得本软件和相关文档文件（“软件”）副本的任何人无限制地处理软件的权利，包括但不限于使用、复制、修改、合并、发布、分发、再许可和/或销售软件副本的权利，并允许向其提供软件的人这样做，符合以下条件：
 *
 * 上述版权声明和本许可声明应包含在软件的所有副本或主要部分中。
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * 此文件是TinyUSB堆栈的一部分。
 */

#ifndef _TUSB_BTH_DEVICE_H_
#define _TUSB_BTH_DEVICE_H_

#include <common/tusb_common.h>
#include <device/usbd.h>

//--------------------------------------------------------------------+
// 类驱动程序配置
//--------------------------------------------------------------------+
#ifndef CFG_TUD_BTH_EVENT_EPSIZE
#define CFG_TUD_BTH_EVENT_EPSIZE     16
#endif
#ifndef CFG_TUD_BTH_DATA_EPSIZE
#define CFG_TUD_BTH_DATA_EPSIZE      64
#endif

typedef struct TU_ATTR_PACKED
{
  uint16_t op_code;
  uint8_t param_length;
  uint8_t param[255];
} bt_hci_cmd_t;

#ifdef __cplusplus
 extern "C" {
#endif

//--------------------------------------------------------------------+
// 应用程序回调API（弱是可选的）
//--------------------------------------------------------------------+

// 通过USB从蓝牙主机接收到HCI命令时调用。
// 详细格式在蓝牙核心规范第2卷中描述，
// 第E部分，5.4.1。
// 命令的长度为3字节（OpCode为2字节，
// 参数总长度为1字节）设置为258。
TU_ATTR_WEAK void tud_bt_hci_cmd_cb(void *hci_cmd, size_t cmd_len);

// 通过USB从蓝牙主机接收ACL数据时调用。
// 详细格式在蓝牙核心规范第2卷中描述，
// E部分5.4.2。
// 长度从4字节开始（12位用于句柄，4位用于标志
// 数据总长度为16位）到端点大小。
TU_ATTR_WEAK void tud_bt_acl_data_received_cb(void *acl_data, uint16_t data_len);

// 当使用tud_bt_event_send（）发送的事件传递到bt堆栈时调用。
// 此时，控制器可以释放/重用带有事件包的缓冲区。
TU_ATTR_WEAK void tud_bt_event_sent_cb(uint16_t sent_bytes);

// 当使用tud_bt_ACL_data_send（）发送ACL数据时调用
// 被传送到BT堆栈。
// 此时，控制器可以释放/重用具有ACL数据包的缓冲区。
TU_ATTR_WEAK void tud_bt_acl_data_sent_cb(uint16_t sent_bytes);

// 蓝牙控制器在想要发送偶数数据包时调用此功能
// 如蓝牙核心规范第2卷E部分5.4.4所述。
// 事件至少有2个字节，第一个是事件代码，第二个包含参数
// 总长度。控制器可以在
// 调用tud_bt_event_sent_cb（）。
bool tud_bt_event_send(void *event, uint16_t event_len);

// 蓝牙控制器调用此命令以发送ACL数据包
// 如蓝牙核心规范第2卷E部分5.4.2所述
// 最小长度为4字节，（句柄为12位，标志为4位
// 数据总长度为16位）。上限不受限制
// 到端点大小，因为缓冲区由控制器分配
// 并且在调用tud_bt_acl_data_sent_cb（）之前不得重复使用。
bool tud_bt_acl_data_send(void *acl_data, uint16_t data_len);

//--------------------------------------------------------------------+
// 内部类驱动程序API
//--------------------------------------------------------------------+
void     btd_init            (void);
void     btd_reset           (uint8_t rhport);
uint16_t btd_open            (uint8_t rhport, tusb_desc_interface_t const * itf_desc, uint16_t max_len);
bool     btd_control_xfer_cb (uint8_t rhport, uint8_t stage, tusb_control_request_t const *request);
bool     btd_xfer_cb         (uint8_t rhport, uint8_t edpt_addr, xfer_result_t result, uint32_t xferred_bytes);

#ifdef __cplusplus
 }
#endif

#endif /* _TUSB_BTH_DEVICE_H_ */

