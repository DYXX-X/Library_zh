/*
 * MIT许可证（MIT）
 *
 * 版权所有（c）2020 Ha Thach（tinyusb.org）版权所有（c）2020 Jerzy Kasenberg
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

#ifdef __cplusplus
extern "C" {
#endif

//--------------------------------------------------------------------
// COMMON CONFIGURATION
//--------------------------------------------------------------------

#include "usb_descriptors.h"

// 由编译器标志定义以实现灵活性
#ifndef CFG_TUSB_MCU
#error CFG_TUSB_MCU must be defined
#endif

#if CFG_TUSB_MCU == OPT_MCU_LPC43XX || CFG_TUSB_MCU == OPT_MCU_LPC18XX || CFG_TUSB_MCU == OPT_MCU_MIMXRT10XX
#define CFG_TUSB_RHPORT0_MODE       (OPT_MODE_DEVICE | OPT_MODE_HIGH_SPEED)
#else
#define CFG_TUSB_RHPORT0_MODE       OPT_MODE_DEVICE
#endif

#ifndef CFG_TUSB_OS
#define CFG_TUSB_OS                 OPT_OS_NONE
#endif

#ifndef CFG_TUSB_DEBUG
// 可以在编译期间设置，即：make LOG=<value for CFG_TUSB_DEBUG>BOARD=<bsp>
// 请记住，在数据流传输时启用日志可能会中断数据流。
// 尽管在测试/调试音频单元请求时，它会非常有用。
#define CFG_TUSB_DEBUG              0
#endif

/* 某些MCU上的USB DMA只能访问特定的SRAM区域，但对对齐有限制。Tinyusb使用以下宏声明传输内存，以便将它们放入特定的部分。例如
 * -CFG_TUSB_MEM节：__attribute__（节（“.usb_ram”））
 * -CFG_TUSB_MEM_ALIGN:__属性__（对齐（4））
 */
#ifndef CFG_TUSB_MEM_SECTION
#define CFG_TUSB_MEM_SECTION
#endif

#ifndef CFG_TUSB_MEM_ALIGN
#define CFG_TUSB_MEM_ALIGN          __attribute__ ((aligned(4)))
#endif

//--------------------------------------------------------------------
// DEVICE CONFIGURATION
//--------------------------------------------------------------------

#ifndef CFG_TUD_ENDPOINT0_SIZE
#define CFG_TUD_ENDPOINT0_SIZE    64
#endif

//------------- CLASS -------------//
#define CFG_TUD_CDC               0
#define CFG_TUD_MSC               0
#define CFG_TUD_HID               0
#define CFG_TUD_MIDI              0
#define CFG_TUD_AUDIO             1
#define CFG_TUD_VENDOR            0

//--------------------------------------------------------------------
// AUDIO CLASS DRIVER CONFIGURATION
//--------------------------------------------------------------------
#define CFG_TUD_AUDIO_IN_PATH                     (CFG_TUD_AUDIO)
#define CFG_TUD_AUDIO_OUT_PATH                    (CFG_TUD_AUDIO)

//#define CFG_TUD_AUDIO_FUNC_1_DESC_LEN 220//这等于TUD_AUDUO_HEADSET_STEREO_DESC_LEN，但是，从usb_descriptors中包含它。由于一些奇怪的包含问题，h是不可能的
#define CFG_TUD_AUDIO_FUNC_1_DESC_LEN                       TUD_AUDIO_HEADSET_STEREO_DESC_LEN

// 音频格式类型I规格
#define CFG_TUD_AUDIO_FUNC_1_N_CHANNELS_TX                  1
#define CFG_TUD_AUDIO_FUNC_1_N_BYTES_PER_SAMPLE_TX          2
#define CFG_TUD_AUDIO_FUNC_1_N_CHANNELS_RX                  2
#define CFG_TUD_AUDIO_FUNC_1_N_BYTES_PER_SAMPLE_RX          2
#define CFG_TUD_AUDIO_ENABLE_FEEDBACK_EP                    0

// EP和缓冲区大小-对于同步EP，缓冲区和EP大小相等（不同大小不合理）
#define CFG_TUD_AUDIO_ENABLE_EP_IN                1
#define CFG_TUD_AUDIO_EP_SZ_IN                    (CFG_TUD_AUDIO_IN_PATH * (48 + 1) * (CFG_TUD_AUDIO_FUNC_1_N_BYTES_PER_SAMPLE_TX) * (CFG_TUD_AUDIO_FUNC_1_N_CHANNELS_TX)) // 48个样本（48 kHz）x 2字节/样本x n个信道
#define CFG_TUD_AUDIO_FUNC_1_EP_IN_SW_BUF_SZ      CFG_TUD_AUDIO_EP_SZ_IN
#define CFG_TUD_AUDIO_FUNC_1_EP_IN_SZ_MAX         CFG_TUD_AUDIO_EP_SZ_IN                  // 使用的所有AS备用设置的最大EP IN大小

// EP和缓冲区大小-对于同步EP，缓冲区和EP大小相等（不同大小不合理）
#define CFG_TUD_AUDIO_ENABLE_EP_OUT               1
#define CFG_TUD_AUDIO_EP_OUT_SZ                   (CFG_TUD_AUDIO_OUT_PATH * ((48 + CFG_TUD_AUDIO_ENABLE_FEEDBACK_EP) * (CFG_TUD_AUDIO_FUNC_1_N_BYTES_PER_SAMPLE_RX) * (CFG_TUD_AUDIO_FUNC_1_N_CHANNELS_RX))) // N个样本（N kHz）x 2字节/样本x N个信道
#define CFG_TUD_AUDIO_FUNC_1_EP_OUT_SW_BUF_SZ     CFG_TUD_AUDIO_EP_OUT_SZ*3
#define CFG_TUD_AUDIO_FUNC_1_EP_OUT_SZ_MAX        CFG_TUD_AUDIO_EP_OUT_SZ                 // 使用的所有AS备用设置的最大EP IN大小

// 每个音频功能定义的标准AS接口描述符（4.9.1）的数量-这是能够记住这些接口的当前替代设置所必需的-我们在这里限制所有音频功能都有一个常量（这意味着这必须是音频功能具有的AS接口的最大数量，而具有较少AS接口的第二个音频功能仅浪费几个字节）
#define CFG_TUD_AUDIO_FUNC_1_N_AS_INT 	          1

// 控制请求缓冲区的大小
#define CFG_TUD_AUDIO_FUNC_1_CTRL_BUF_SZ	64

#ifdef __cplusplus
}
#endif

#endif /* _TUSB_CONFIG_H_ */

