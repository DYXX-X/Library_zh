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

/** \inggroup group_class\defgroup ClassDriver_Hub Hub（仅限主机）\details与大多数PC的操作系统一样，应用程序完全不支持Hub。事实上，应用程序无法确定设备是直接通过roothub还是通过集线器的端口安装的。所有与集线器相关的过程都由tinyusb堆栈执行和管理。除非您正在尝试开发堆栈本身，否则Application无法使用任何其他功能。\注意：由于我的懒惰，仅支持1级集线器。换句话说，堆栈无法通过另一个集线器安装集线器@{
 */

#ifndef _TUSB_HUB_H_
#define _TUSB_HUB_H_

#include "common/tusb_common.h"
#include "usbh.h"

#ifdef __cplusplus
 extern "C" {
#endif

//D1…D0：逻辑电源切换模式
//00：联动电源切换（所有端口的电源处于
//一次）
//01：单端口电源切换
//1X：保留。仅在1.0兼容集线器上使用
//不进行电源切换
//D2：识别复合设备
//0:集线器不是复合设备的一部分。
//1： 轮毂是复合装置的一部分。
//D4…D3：过电流保护模式
//00：全局过电流保护。轮毂
//将过电流报告为所有值的总和
//端口电流消耗，无故障
//单个端口过流状态。
//01：单个端口过流保护。这个
//集线器按每个端口报告过流。
//每个端口都有过电流状态。
//1X：无过电流保护。此选项为
//仅允许总线供电的集线器
//实施过流保护。
//
//D6…D5:TT思考时间
//00:TT最多需要8 FS位时间的帧间
//全速/低速交易缺口
//下游总线。
//01:TT最多需要16 FS位时间。
//10： TT最多需要24 FS位时间。
//11： TT最多需要32 FS位时间。
//D7：支持的端口指示器
//0:其上不支持端口指示器
//面向下游的端口和
//PORT_INDICATOR请求无效。
//1： 其上支持端口指示器
//面向下游的端口和
//PORT_INDICATOR请求控制
//指标。见第11.5.3节。
//D15…D8：保留

typedef struct TU_ATTR_PACKED{
  uint8_t  bLength           ; ///<描述符大小
  uint8_t  bDescriptorType   ; ///<Other_speed_Configuration Type（其他速度配置类型）
  uint8_t  bNbrPorts;
  uint16_t wHubCharacteristics;
  uint8_t  bPwrOn2PwrGood;
  uint8_t  bHubContrCurrent;
  uint8_t  DeviceRemovable; // 端口的每个位位图（从位1开始）
  uint8_t  PortPwrCtrlMask; // 仅出于兼容性考虑，应为0xff
} descriptor_hub_desc_t;

TU_VERIFY_STATIC( sizeof(descriptor_hub_desc_t) == 9, "size is not correct");

enum {
  HUB_REQUEST_GET_STATUS      = 0  ,
  HUB_REQUEST_CLEAR_FEATURE   = 1  ,

  HUB_REQUEST_SET_FEATURE     = 3  ,

  HUB_REQUEST_GET_DESCRIPTOR  = 6  ,
  HUB_REQUEST_SET_DESCRIPTOR  = 7  ,
  HUB_REQUEST_CLEAR_TT_BUFFER = 8  ,
  HUB_REQUEST_RESET_TT        = 9  ,
  HUB_REQUEST_GET_TT_STATE    = 10 ,
  HUB_REQUEST_STOP_TT         = 11
};

enum {
  HUB_FEATURE_HUB_LOCAL_POWER_CHANGE = 0,
  HUB_FEATURE_HUB_OVER_CURRENT_CHANGE
};

enum{
  HUB_FEATURE_PORT_CONNECTION          = 0,
  HUB_FEATURE_PORT_ENABLE              = 1,
  HUB_FEATURE_PORT_SUSPEND             = 2,
  HUB_FEATURE_PORT_OVER_CURRENT        = 3,
  HUB_FEATURE_PORT_RESET               = 4,

  HUB_FEATURE_PORT_POWER               = 8,
  HUB_FEATURE_PORT_LOW_SPEED           = 9,

  HUB_FEATURE_PORT_CONNECTION_CHANGE   = 16,
  HUB_FEATURE_PORT_ENABLE_CHANGE       = 17,
  HUB_FEATURE_PORT_SUSPEND_CHANGE      = 18,
  HUB_FEATURE_PORT_OVER_CURRENT_CHANGE = 19,
  HUB_FEATURE_PORT_RESET_CHANGE        = 20,
  HUB_FEATURE_PORT_TEST                = 21,
  HUB_FEATURE_PORT_INDICATOR           = 22
};

// 响应HUB_REQUEST_GET_STATUS的数据，wIndex=0（集线器）
typedef struct {
  union{
    struct TU_ATTR_PACKED {
      uint16_t local_power_source : 1;
      uint16_t over_current       : 1;
      uint16_t : 14;
    };

    uint16_t value;
  } status, change;
} hub_status_response_t;

TU_VERIFY_STATIC( sizeof(hub_status_response_t) == 4, "size is not correct");

// 响应HUB_REQUEST_GET_STATUS的数据，wIndex=端口num
typedef struct {
  union {
    struct TU_ATTR_PACKED {
      uint16_t connection             : 1;
      uint16_t port_enable            : 1;
      uint16_t suspend                : 1;
      uint16_t over_current           : 1;
      uint16_t reset                  : 1;

      uint16_t                        : 3;
      uint16_t port_power             : 1;
      uint16_t low_speed              : 1;
      uint16_t high_speed             : 1;
      uint16_t port_test_mode         : 1;
      uint16_t port_indicator_control : 1;
      uint16_t TU_RESERVED            : 3;
    };

    uint16_t value;
  } status, change;
} hub_port_status_response_t;

TU_VERIFY_STATIC( sizeof(hub_port_status_response_t) == 4, "size is not correct");

bool hub_port_reset(uint8_t hub_addr, uint8_t hub_port, tuh_control_complete_cb_t complete_cb);
bool hub_port_get_status(uint8_t hub_addr, uint8_t hub_port, void* resp, tuh_control_complete_cb_t complete_cb);
bool hub_port_clear_feature(uint8_t hub_addr, uint8_t hub_port, uint8_t feature, tuh_control_complete_cb_t complete_cb);
bool hub_status_pipe_queue(uint8_t dev_addr);

//--------------------------------------------------------------------+
// 内部类驱动程序API
//--------------------------------------------------------------------+
void hub_init(void);
bool hub_open(uint8_t rhport, uint8_t dev_addr, tusb_desc_interface_t const *itf_desc, uint16_t *p_length);
bool hub_set_config(uint8_t dev_addr, uint8_t itf_num);
bool hub_xfer_cb(uint8_t dev_addr, uint8_t ep_addr, xfer_result_t event, uint32_t xferred_bytes);
void hub_close(uint8_t dev_addr);

#ifdef __cplusplus
 }
#endif

#endif /* _TUSB_HUB_H_ */

/** @} */

