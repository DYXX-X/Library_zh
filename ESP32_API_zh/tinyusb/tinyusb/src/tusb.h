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

#ifndef _TUSB_H_
#define _TUSB_H_

#ifdef __cplusplus
 extern "C" {
#endif

//--------------------------------------------------------------------+
// INCLUDE
//--------------------------------------------------------------------+
#include "common/tusb_common.h"
#include "osal/osal.h"
#include "common/tusb_fifo.h"

//------------- HOST -------------//
#if TUSB_OPT_HOST_ENABLED
  #include "host/usbh.h"

  #if HOST_CLASS_HID
    #include "class/hid/hid_host.h"
  #endif

  #if CFG_TUH_MSC
    #include "class/msc/msc_host.h"
  #endif

  #if CFG_TUH_CDC
    #include "class/cdc/cdc_host.h"
  #endif

  #if CFG_TUH_VENDOR
    #include "class/vendor/vendor_host.h"
  #endif

#endif

//------------- DEVICE -------------//
#if TUSB_OPT_DEVICE_ENABLED
  #include "device/usbd.h"

  #if CFG_TUD_HID
    #include "class/hid/hid_device.h"
  #endif

  #if CFG_TUD_CDC
    #include "class/cdc/cdc_device.h"
  #endif

  #if CFG_TUD_MSC
    #include "class/msc/msc_device.h"
  #endif

#if CFG_TUD_AUDIO
  #include "class/audio/audio_device.h"
#endif

  #if CFG_TUD_MIDI
    #include "class/midi/midi_device.h"
  #endif

  #if CFG_TUD_VENDOR
    #include "class/vendor/vendor_device.h"
  #endif

  #if CFG_TUD_USBTMC
    #include "class/usbtmc/usbtmc_device.h"
  #endif

  #if CFG_TUD_DFU_RUNTIME
    #include "class/dfu/dfu_rt_device.h"
  #endif

  #if CFG_TUD_NET
    #include "class/net/net_device.h"
  #endif

  #if CFG_TUD_BTH
    #include "class/bth/bth_device.h"
  #endif
#endif


//--------------------------------------------------------------------+
// APPLICATION API
//--------------------------------------------------------------------+
/** \组组应用程序api
 *  @{ */

// 初始化设备/主机堆栈
// 注意：当与RTOS一起使用时，应该在调度器/内核启动后调用。
// 否则，它可能会导致内核问题，因为USB IRQ处理程序确实使用RTOS队列API。
bool tusb_init(void);

// 检查堆栈是否已初始化
bool tusb_inited(void);

// TODO
// bool tusb_teardown（无效）；

/** @} */

#ifdef __cplusplus
 }
#endif

#endif /* _TUSB_H_ */

