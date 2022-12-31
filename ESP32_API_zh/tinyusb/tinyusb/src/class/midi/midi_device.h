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

#ifndef _TUSB_MIDI_DEVICE_H_
#define _TUSB_MIDI_DEVICE_H_

#include "common/tusb_common.h"
#include "device/usbd.h"

#include "class/audio/audio.h"
#include "midi.h"

//--------------------------------------------------------------------+
// 类驱动程序配置
//--------------------------------------------------------------------+

#if !defined(CFG_TUD_MIDI_EP_BUFSIZE) && defined(CFG_TUD_MIDI_EPSIZE)
  #warning CFG_TUD_MIDI_EPSIZE is renamed to CFG_TUD_MIDI_EP_BUFSIZE, please update to use the new name
  #define CFG_TUD_MIDI_EP_BUFSIZE    CFG_TUD_MIDI_EPSIZE
#endif

#ifndef CFG_TUD_MIDI_EP_BUFSIZE
  #define CFG_TUD_MIDI_EP_BUFSIZE     (TUD_OPT_HIGH_SPEED ? 512 : 64)
#endif

#ifdef __cplusplus
 extern "C" {
#endif

/** \addtogroup MIDI_Serial Serial @{ \defgroup MIDI_Serial_Device设备
 *  @{ */

//--------------------------------------------------------------------+
// 应用程序API（多接口）
// CFG_TUD_MIDI > 1
//--------------------------------------------------------------------+

// 检查是否安装了midi接口
bool     tud_midi_n_mounted      (uint8_t itf);

// 获取可读取的字节数
uint32_t tud_midi_n_available    (uint8_t itf, uint8_t cable_num);

// 读取字节流（传统）
uint32_t tud_midi_n_stream_read  (uint8_t itf, uint8_t cable_num, void* buffer, uint32_t bufsize);

// 写入字节流（传统）
uint32_t tud_midi_n_stream_write (uint8_t itf, uint8_t cable_num, uint8_t const* buffer, uint32_t bufsize);

// 读取事件包（4字节）
bool     tud_midi_n_packet_read  (uint8_t itf, uint8_t packet[4]);

// 写入事件数据包（4字节）
bool     tud_midi_n_packet_write (uint8_t itf, uint8_t const packet[4]);

//--------------------------------------------------------------------+
// 应用程序API（单接口）
//--------------------------------------------------------------------+
static inline bool     tud_midi_mounted      (void);
static inline uint32_t tud_midi_available    (void);

static inline uint32_t tud_midi_stream_read  (void* buffer, uint32_t bufsize);
static inline uint32_t tud_midi_stream_write (uint8_t cable_num, uint8_t const* buffer, uint32_t bufsize);

static inline bool     tud_midi_packet_read  (uint8_t packet[4]);
static inline bool     tud_midi_packet_write (uint8_t const packet[4]);

//-------------不推荐的API名称-------------//
// 0.10.0版本后删除TODO

TU_ATTR_DEPRECATED("tud_midi_read() is renamed to tud_midi_stream_read()")
static inline uint32_t tud_midi_read (void* buffer, uint32_t bufsize)
{
  return tud_midi_stream_read(buffer, bufsize);
}

TU_ATTR_DEPRECATED("tud_midi_write() is renamed to tud_midi_stream_write()")
static inline uint32_t tud_midi_write(uint8_t cable_num, uint8_t const* buffer, uint32_t bufsize)
{
  return tud_midi_stream_write(cable_num, buffer, bufsize);
}


TU_ATTR_DEPRECATED("tud_midi_send() is renamed to tud_midi_packet_write()")
static inline bool tud_midi_send(uint8_t packet[4])
{
  return tud_midi_packet_write(packet);
}

TU_ATTR_DEPRECATED("tud_midi_receive() is renamed to tud_midi_packet_read()")
static inline bool tud_midi_receive(uint8_t packet[4])
{
  return tud_midi_packet_read(packet);
}

//--------------------------------------------------------------------+
// 应用程序回调API（弱是可选的）
//--------------------------------------------------------------------+
TU_ATTR_WEAK void tud_midi_rx_cb(uint8_t itf);

//--------------------------------------------------------------------+
// 内联函数
//--------------------------------------------------------------------+

static inline bool tud_midi_mounted (void)
{
  return tud_midi_n_mounted(0);
}

static inline uint32_t tud_midi_available (void)
{
  return tud_midi_n_available(0, 0);
}

static inline uint32_t tud_midi_stream_read (void* buffer, uint32_t bufsize)
{
  return tud_midi_n_stream_read(0, 0, buffer, bufsize);
}

static inline uint32_t tud_midi_stream_write (uint8_t cable_num, uint8_t const* buffer, uint32_t bufsize)
{
  return tud_midi_n_stream_write(0, cable_num, buffer, bufsize);
}

static inline bool tud_midi_packet_read (uint8_t packet[4])
{
  return tud_midi_n_packet_read(0, packet);
}

static inline bool tud_midi_packet_write (uint8_t const packet[4])
{
  return tud_midi_n_packet_write(0, packet);
}

//--------------------------------------------------------------------+
// 内部类驱动程序API
//--------------------------------------------------------------------+
void     midid_init            (void);
void     midid_reset           (uint8_t rhport);
uint16_t midid_open            (uint8_t rhport, tusb_desc_interface_t const * itf_desc, uint16_t max_len);
bool     midid_control_xfer_cb (uint8_t rhport, uint8_t stage, tusb_control_request_t const * request);
bool     midid_xfer_cb         (uint8_t rhport, uint8_t edpt_addr, xfer_result_t result, uint32_t xferred_bytes);

#ifdef __cplusplus
 }
#endif

#endif /* _TUSB_MIDI_DEVICE_H_ */

/** @} */
/** @} */

