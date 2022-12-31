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

#ifndef _TUSB_CDC_DEVICE_H_
#define _TUSB_CDC_DEVICE_H_

#include "common/tusb_common.h"
#include "device/usbd.h"
#include "cdc.h"

//--------------------------------------------------------------------+
// 类驱动程序配置
//--------------------------------------------------------------------+
#if !defined(CFG_TUD_CDC_EP_BUFSIZE) && defined(CFG_TUD_CDC_EPSIZE)
  #warning CFG_TUD_CDC_EPSIZE is renamed to CFG_TUD_CDC_EP_BUFSIZE, please update to use the new name
  #define CFG_TUD_CDC_EP_BUFSIZE    CFG_TUD_CDC_EPSIZE
#endif

#ifndef CFG_TUD_CDC_EP_BUFSIZE
  #define CFG_TUD_CDC_EP_BUFSIZE    (TUD_OPT_HIGH_SPEED ? 512 : 64)
#endif

#ifdef __cplusplus
 extern "C" {
#endif

/** \addtogroup CDC_Serial Serial @{ \defgroup CDC_Serial_Device设备
 *  @{ */

//--------------------------------------------------------------------+
// 应用程序API（多端口）
// CFG_TUD_CDC > 1
//--------------------------------------------------------------------+

// 检查终端是否连接到此端口
bool     tud_cdc_n_connected       (uint8_t itf);

// 获取当前线路状态。位0:DTR（数据终端就绪），位1:RTS（请求发送）
uint8_t  tud_cdc_n_get_line_state  (uint8_t itf);

// 获取当前行编码：比特率、停止比特奇偶校验等。。
void     tud_cdc_n_get_line_coding (uint8_t itf, cdc_line_coding_t* coding);

// 设置特殊字符，该字符将在接收时触发tud_dc_rx_wanted_cb（）回调
void     tud_cdc_n_set_wanted_char (uint8_t itf, char wanted);

// 获取可读取的字节数
uint32_t tud_cdc_n_available       (uint8_t itf);

// 读取接收的字节
uint32_t tud_cdc_n_read            (uint8_t itf, void* buffer, uint32_t bufsize);

// 读取一个字节，如果没有，则返回-1
static inline
int32_t  tud_cdc_n_read_char       (uint8_t itf);

// 清除接收的FIFO
void     tud_cdc_n_read_flush      (uint8_t itf);

// 在指定位置从FIFO中获取一个字节，而不删除它
bool     tud_cdc_n_peek            (uint8_t itf, int pos, uint8_t* u8);

// 将字节写入TX FIFO，数据可能会在FIFO中保留一段时间
uint32_t tud_cdc_n_write           (uint8_t itf, void const* buffer, uint32_t bufsize);

// 写入一个字节
static inline
uint32_t tud_cdc_n_write_char      (uint8_t itf, char ch);

// 写入以空结尾的字符串
static inline
uint32_t tud_cdc_n_write_str       (uint8_t itf, char const* str);

// 如果可能，强制发送数据，返回强制字节数
uint32_t tud_cdc_n_write_flush     (uint8_t itf);

// 返回在单个n_write操作中可用于写入TX FIFO缓冲区的字节数（字符）。
uint32_t tud_cdc_n_write_available (uint8_t itf);

// 清除传输FIFO
bool tud_cdc_n_write_clear (uint8_t itf);

//--------------------------------------------------------------------+
// 应用程序API（单端口）
//--------------------------------------------------------------------+
static inline bool     tud_cdc_connected       (void);
static inline uint8_t  tud_cdc_get_line_state  (void);
static inline void     tud_cdc_get_line_coding (cdc_line_coding_t* coding);
static inline void     tud_cdc_set_wanted_char (char wanted);

static inline uint32_t tud_cdc_available       (void);
static inline int32_t  tud_cdc_read_char       (void);
static inline uint32_t tud_cdc_read            (void* buffer, uint32_t bufsize);
static inline void     tud_cdc_read_flush      (void);
static inline bool     tud_cdc_peek            (int pos, uint8_t* u8);

static inline uint32_t tud_cdc_write_char      (char ch);
static inline uint32_t tud_cdc_write           (void const* buffer, uint32_t bufsize);
static inline uint32_t tud_cdc_write_str       (char const* str);
static inline uint32_t tud_cdc_write_flush     (void);
static inline uint32_t tud_cdc_write_available (void);
static inline bool     tud_cdc_write_clear     (void);

//--------------------------------------------------------------------+
// 应用程序回调API（弱是可选的）
//--------------------------------------------------------------------+

// 收到新数据时调用
TU_ATTR_WEAK void tud_cdc_rx_cb(uint8_t itf);

// 收到`wanted_char时调用`
TU_ATTR_WEAK void tud_cdc_rx_wanted_cb(uint8_t itf, char wanted_char);

// 当TX缓冲区中的空间可用时调用
TU_ATTR_WEAK void tud_cdc_tx_complete_cb(uint8_t itf);

// 通过SET_CONTROL_line_state更改线路状态DTR和RTS时调用
TU_ATTR_WEAK void tud_cdc_line_state_cb(uint8_t itf, bool dtr, bool rts);

// 通过SET_line_coding更改行编码时调用
TU_ATTR_WEAK void tud_cdc_line_coding_cb(uint8_t itf, cdc_line_coding_t const* p_line_coding);

// 收到发送中断时调用
TU_ATTR_WEAK void tud_cdc_send_break_cb(uint8_t itf, uint16_t duration_ms);

//--------------------------------------------------------------------+
// 内联函数
//--------------------------------------------------------------------+
static inline int32_t tud_cdc_n_read_char (uint8_t itf)
{
  uint8_t ch;
  return tud_cdc_n_read(itf, &ch, 1) ? (int32_t) ch : -1;
}

static inline uint32_t tud_cdc_n_write_char(uint8_t itf, char ch)
{
  return tud_cdc_n_write(itf, &ch, 1);
}

static inline uint32_t tud_cdc_n_write_str (uint8_t itf, char const* str)
{
  return tud_cdc_n_write(itf, str, strlen(str));
}

static inline bool tud_cdc_connected (void)
{
  return tud_cdc_n_connected(0);
}

static inline uint8_t tud_cdc_get_line_state (void)
{
  return tud_cdc_n_get_line_state(0);
}

static inline void tud_cdc_get_line_coding (cdc_line_coding_t* coding)
{
  tud_cdc_n_get_line_coding(0, coding);
}

static inline void tud_cdc_set_wanted_char (char wanted)
{
  tud_cdc_n_set_wanted_char(0, wanted);
}

static inline uint32_t tud_cdc_available (void)
{
  return tud_cdc_n_available(0);
}

static inline int32_t tud_cdc_read_char (void)
{
  return tud_cdc_n_read_char(0);
}

static inline uint32_t tud_cdc_read (void* buffer, uint32_t bufsize)
{
  return tud_cdc_n_read(0, buffer, bufsize);
}

static inline void tud_cdc_read_flush (void)
{
  tud_cdc_n_read_flush(0);
}

static inline bool tud_cdc_peek (int pos, uint8_t* u8)
{
  return tud_cdc_n_peek(0, pos, u8);
}

static inline uint32_t tud_cdc_write_char (char ch)
{
  return tud_cdc_n_write_char(0, ch);
}

static inline uint32_t tud_cdc_write (void const* buffer, uint32_t bufsize)
{
  return tud_cdc_n_write(0, buffer, bufsize);
}

static inline uint32_t tud_cdc_write_str (char const* str)
{
  return tud_cdc_n_write_str(0, str);
}

static inline uint32_t tud_cdc_write_flush (void)
{
  return tud_cdc_n_write_flush(0);
}

static inline uint32_t tud_cdc_write_available(void)
{
  return tud_cdc_n_write_available(0);
}

static inline bool tud_cdc_write_clear(void)
{
  return tud_cdc_n_write_clear(0);
}

/** @} */
/** @} */

//--------------------------------------------------------------------+
// INTERNAL USBD-CLASS DRIVER API
//--------------------------------------------------------------------+
void     cdcd_init            (void);
void     cdcd_reset           (uint8_t rhport);
uint16_t cdcd_open            (uint8_t rhport, tusb_desc_interface_t const * itf_desc, uint16_t max_len);
bool     cdcd_control_xfer_cb (uint8_t rhport, uint8_t stage, tusb_control_request_t const * request);
bool     cdcd_xfer_cb         (uint8_t rhport, uint8_t ep_addr, xfer_result_t result, uint32_t xferred_bytes);

#ifdef __cplusplus
 }
#endif

#endif /* _TUSB_CDC_DEVICE_H_ */

