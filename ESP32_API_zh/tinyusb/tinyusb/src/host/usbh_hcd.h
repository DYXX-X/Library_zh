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

/** \内部组_HCD
 *  @{ */

#ifndef _TUSB_USBH_HCD_H_
#define _TUSB_USBH_HCD_H_

#ifdef __cplusplus
 extern "C" {
#endif

//--------------------------------------------------------------------+
// INCLUDE
//--------------------------------------------------------------------+
#include "common/tusb_common.h"
#include "osal/osal.h"

#ifndef CFG_TUH_EP_MAX
#define CFG_TUH_EP_MAX          9
#endif

//--------------------------------------------------------------------+
// USBH-HCD通用数据结构
//--------------------------------------------------------------------+

// TODO移至usbh.c
typedef struct {
  //-------------港口-------------//
  uint8_t rhport;
  uint8_t hub_addr;
  uint8_t hub_port;
  uint8_t speed;

  //-------------设备描述符-------------//
  uint16_t vendor_id;
  uint16_t product_id;
  uint8_t  ep0_packet_size;

  //-------------配置描述符-------------//
  // uint8_t接口计数；//bNumInterfaces别名

  //-------------设备-------------//
  struct TU_ATTR_PACKED
  {
    uint8_t connected    : 1;
    uint8_t addressed    : 1;
    uint8_t configured   : 1;
    uint8_t suspended    : 1;
  };

  volatile uint8_t state;             // 设备状态，枚举tusbh_device_state_t中的值

  uint8_t itf2drv[16];  // 将接口号映射到驱动程序（0xff无效）
  uint8_t ep2drv[CFG_TUH_EP_MAX][2]; // 将端点映射到驱动程序（0xff无效）

  struct TU_ATTR_PACKED
  {
    volatile bool busy    : 1;
    volatile bool stalled : 1;
    volatile bool claimed : 1;

    // TODO此处合并ep2drv，4位应该足够了
  }ep_status[CFG_TUH_EP_MAX][2];

  // Mutex用于声明端点，仅在与抢占的RTOS一起使用时需要
#if CFG_TUSB_OS != OPT_OS_NONE
  osal_mutex_def_t mutexdef;
  osal_mutex_t mutex;
#endif

} usbh_device_t;

extern usbh_device_t _usbh_devices[CFG_TUSB_HOST_DEVICE_MAX+1]; // 包括零地址

//--------------------------------------------------------------------+
// 来自HCD ISR的回调
//--------------------------------------------------------------------+



#ifdef __cplusplus
 }
#endif

#endif /* _TUSB_USBH_HCD_H_ */

/** @} */

