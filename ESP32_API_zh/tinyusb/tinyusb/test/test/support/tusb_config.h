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
 */

#ifndef _TUSB_CONFIG_H_
#define _TUSB_CONFIG_H_

// 测试框架
#include "unity.h"

#ifdef __cplusplus
 extern "C" {
#endif

//--------------------------------------------------------------------
// COMMON CONFIGURATION
//--------------------------------------------------------------------

// 由编译器标志定义以实现灵活性
#ifndef CFG_TUSB_MCU
  //#必须定义错误CFG_TUSB_MCU
  #define CFG_TUSB_MCU  OPT_MCU_NRF5X
#endif

#ifndef CFG_TUSB_RHPORT0_MODE
#define CFG_TUSB_RHPORT0_MODE    (OPT_MODE_DEVICE | OPT_MODE_HIGH_SPEED)
#endif

#define CFG_TUSB_OS              OPT_OS_NONE

// CFG_TUSB_DEBUG由编译器在DEBUG构建中定义
#ifndef CFG_TUSB_DEBUG
#define CFG_TUSB_DEBUG           0
#endif

/* 某些MCU上的USB DMA只能访问特定的SRAM区域，但对对齐有限制。Tinyusb使用以下宏声明传输内存，以便将它们放入特定的部分。例如
 * -CFG_TUSB_MEM节：__attribute__（节（“.usb_ram”））
 * -CFG_TUSB_MEM_ALIGN:__属性__（对齐（4））
 */
#ifndef CFG_TUSB_MEM_SECTION
#define CFG_TUSB_MEM_SECTION
#endif

#ifndef CFG_TUSB_MEM_ALIGN
#define CFG_TUSB_MEM_ALIGN       __attribute__ ((aligned(4)))
#endif

//--------------------------------------------------------------------
// DEVICE CONFIGURATION
//--------------------------------------------------------------------

#define CFG_TUD_TASK_QUEUE_SZ    100
#define CFG_TUD_ENDPOINT0_SIZE    64

//------------- CLASS -------------//
//#定义CFG_TUD_CDC 0
#define CFG_TUD_MSC              1
//#定义CFG_TUD_HID 0
//#定义CFG_TUD_MIDI 0
//#定义CFG_TUD_VENDOR 0

//------------- CDC -------------//

// CDC TX和RX的FIFO大小
#define CFG_TUD_CDC_RX_BUFSIZE   512
#define CFG_TUD_CDC_TX_BUFSIZE   512

//------------- MSC -------------//

// 设备大容量存储的缓冲区大小
#define CFG_TUD_MSC_BUFSIZE      512

//------------- HID -------------//

// 应足以保存ID（如有）+数据
#define CFG_TUD_HID_EP_BUFSIZE    64

#ifdef __cplusplus
 }
#endif

#endif /* _TUSB_CONFIG_H_ */

