/* 
 * MIT许可证（MIT）
 *
 * 版权所有（c）2020 Peter Lawrence版权所有（c）2019 Ha Thach（tinyusb.org）
 *
 * 特此免费授予获得本软件和相关文档文件（“软件”）副本的任何人无限制地处理软件的权利，包括但不限于使用、复制、修改、合并、发布、分发、再许可和/或销售软件副本的权利，并允许向其提供软件的人这样做，符合以下条件：
 *
 * 上述版权声明和本许可声明应包含在软件的所有副本或主要部分中。
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * 此文件是TinyUSB堆栈的一部分。
 */

#ifndef _TUSB_NET_DEVICE_H_
#define _TUSB_NET_DEVICE_H_

#include "common/tusb_common.h"
#include "device/usbd.h"
#include "class/cdc/cdc.h"

/* 此处声明，而不是在usb_descriptors中。c、 以便驾驶员可以根据需要智能地进行ZLP*/
#define CFG_TUD_NET_ENDPOINT_SIZE (TUD_OPT_HIGH_SPEED ? 512 : 64)

/* 网络的最大传输单位（字节），包括以太网报头*/
#ifndef CFG_TUD_NET_MTU
#define CFG_TUD_NET_MTU           1514
#endif

#ifdef __cplusplus
 extern "C" {
#endif

//--------------------------------------------------------------------+
// 应用程序API
//--------------------------------------------------------------------+

// 客户端必须提供：将任何网络状态初始化回开头
void tud_network_init_cb(void);

// 客户端必须提供：如果数据包缓冲区未被接受，则返回false
bool tud_network_recv_cb(const uint8_t *src, uint16_t size);

// 客户端必须提供：从网络堆栈复制数据包指针到dst
uint16_t tud_network_xmit_cb(uint8_t *dst, void *ref, uint16_t arg);

// 客户端必须提供：48位MAC地址
// TODO稍后被删除，因为它不是tinyusb堆栈的一部分
extern const uint8_t tud_network_mac_address[6];

// 向网络驱动程序指示客户端已完成向network_recv_cb（）提供的数据包
void tud_network_recv_renew(void);

// 轮询网络驱动程序接受另一个数据包传输的能力
bool tud_network_can_xmit(void);

// 如果network_can-xmit（）返回true，则可以调用network_xmit（）一次
void tud_network_xmit(void *ref, uint16_t arg);

//--------------------------------------------------------------------+
// INTERNAL USBD-CLASS DRIVER API
//--------------------------------------------------------------------+
void     netd_init            (void);
void     netd_reset           (uint8_t rhport);
uint16_t netd_open            (uint8_t rhport, tusb_desc_interface_t const * itf_desc, uint16_t max_len);
bool     netd_control_xfer_cb (uint8_t rhport, uint8_t stage, tusb_control_request_t const * request);
bool     netd_xfer_cb         (uint8_t rhport, uint8_t ep_addr, xfer_result_t result, uint32_t xferred_bytes);
void     netd_report          (uint8_t *buf, uint16_t len);

#ifdef __cplusplus
 }
#endif

#endif /* _TUSB_NET_DEVICE_H_ */

