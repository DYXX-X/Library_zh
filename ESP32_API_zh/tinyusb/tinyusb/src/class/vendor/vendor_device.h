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

#ifndef _TUSB_VENDOR_DEVICE_H_
#define _TUSB_VENDOR_DEVICE_H_

#include "common/tusb_common.h"
#include "device/usbd.h"

#ifndef CFG_TUD_VENDOR_EPSIZE
#define CFG_TUD_VENDOR_EPSIZE     64
#endif

#ifdef __cplusplus
 extern "C" {
#endif

//--------------------------------------------------------------------+
// 应用程序API（多接口）
//--------------------------------------------------------------------+
bool     tud_vendor_n_mounted         (uint8_t itf);

uint32_t tud_vendor_n_available       (uint8_t itf);
uint32_t tud_vendor_n_read            (uint8_t itf, void* buffer, uint32_t bufsize);
bool     tud_vendor_n_peek            (uint8_t itf, int pos, uint8_t* u8);

uint32_t tud_vendor_n_write           (uint8_t itf, void const* buffer, uint32_t bufsize);
uint32_t tud_vendor_n_write_available (uint8_t itf);

static inline
uint32_t tud_vendor_n_write_str       (uint8_t itf, char const* str);

//--------------------------------------------------------------------+
// 应用程序API（单端口）
//--------------------------------------------------------------------+
static inline bool     tud_vendor_mounted         (void);
static inline uint32_t tud_vendor_available       (void);
static inline uint32_t tud_vendor_read            (void* buffer, uint32_t bufsize);
static inline bool     tud_vendor_peek            (int pos, uint8_t* u8);
static inline uint32_t tud_vendor_write           (void const* buffer, uint32_t bufsize);
static inline uint32_t tud_vendor_write_str       (char const* str);
static inline uint32_t tud_vendor_write_available (void);

//--------------------------------------------------------------------+
// 应用程序回调API（弱是可选的）
//--------------------------------------------------------------------+

// 收到新数据时调用
TU_ATTR_WEAK void tud_vendor_rx_cb(uint8_t itf);

//--------------------------------------------------------------------+
// 内联函数
//--------------------------------------------------------------------+

static inline uint32_t tud_vendor_n_write_str (uint8_t itf, char const* str)
{
  return tud_vendor_n_write(itf, str, strlen(str));
}

static inline bool tud_vendor_mounted (void)
{
  return tud_vendor_n_mounted(0);
}

static inline uint32_t tud_vendor_available (void)
{
  return tud_vendor_n_available(0);
}

static inline uint32_t tud_vendor_read (void* buffer, uint32_t bufsize)
{
  return tud_vendor_n_read(0, buffer, bufsize);
}

static inline bool tud_vendor_peek (int pos, uint8_t* u8)
{
  return tud_vendor_n_peek(0, pos, u8);
}

static inline uint32_t tud_vendor_write (void const* buffer, uint32_t bufsize)
{
  return tud_vendor_n_write(0, buffer, bufsize);
}

static inline uint32_t tud_vendor_write_str (char const* str)
{
  return tud_vendor_n_write_str(0, str);
}

static inline uint32_t tud_vendor_write_available (void)
{
  return tud_vendor_n_write_available(0);
}

//--------------------------------------------------------------------+
// 内部类驱动程序API
//--------------------------------------------------------------------+
void     vendord_init(void);
void     vendord_reset(uint8_t rhport);
uint16_t vendord_open(uint8_t rhport, tusb_desc_interface_t const * itf_desc, uint16_t max_len);
bool     vendord_xfer_cb(uint8_t rhport, uint8_t ep_addr, xfer_result_t event, uint32_t xferred_bytes);

#ifdef __cplusplus
 }
#endif

#endif /* _TUSB_VENDOR_DEVICE_H_ */

