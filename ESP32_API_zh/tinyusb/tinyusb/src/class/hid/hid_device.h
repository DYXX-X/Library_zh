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

#ifndef _TUSB_HID_DEVICE_H_
#define _TUSB_HID_DEVICE_H_

#include "common/tusb_common.h"
#include "device/usbd.h"
#include "hid.h"

#ifdef __cplusplus
 extern "C" {
#endif

//--------------------------------------------------------------------+
// 类驱动程序默认配置和验证
//--------------------------------------------------------------------+

#if !defined(CFG_TUD_HID_EP_BUFSIZE) & defined(CFG_TUD_HID_BUFSIZE)
  // TODO警告用户稍后使用新名称
  // #警告CFG_TUD_HID_BUFSIZE已重命名为CFG_TUD-HID_EP_BUFSIZE，请更新以使用新名称
  #define CFG_TUD_HID_EP_BUFSIZE  CFG_TUD_HID_BUFSIZE
#endif

#ifndef CFG_TUD_HID_EP_BUFSIZE
  #define CFG_TUD_HID_EP_BUFSIZE     64
#endif

//--------------------------------------------------------------------+
// 应用程序API（多端口）
// CFG_TUD_HID > 1
//--------------------------------------------------------------------+

// 检查接口是否可以使用
bool tud_hid_n_ready(uint8_t itf);

// 检查当前模式是引导（true）还是报告（false）
bool tud_hid_n_boot_mode(uint8_t itf);

// 向主机发送报告
bool tud_hid_n_report(uint8_t itf, uint8_t report_id, void const* report, uint8_t len);

// KEYBOARD：方便的助手，如果应用程序发送键盘报告
// 使用hidkeyboard_reportt定义的模板布局报告
bool tud_hid_n_keyboard_report(uint8_t itf, uint8_t report_id, uint8_t modifier, uint8_t keycode[6]);

// MOUSE：在应用程序中发送鼠标报告的方便助手
// 使用hid_muse_reportt定义的模板布局报告
bool tud_hid_n_mouse_report(uint8_t itf, uint8_t report_id, uint8_t buttons, int8_t x, int8_t y, int8_t vertical, int8_t horizontal);

// Gamepad：在应用程序中发送鼠标报告的方便助手
// 使用模板布局报告TUD_HID_report_DESC_GAMEPAD
bool tud_hid_n_gamepad_report(uint8_t itf, uint8_t report_id, int8_t x, int8_t y, int8_t z, int8_t rz, int8_t rx, int8_t ry, uint8_t hat, uint16_t buttons);

//--------------------------------------------------------------------+
// 应用程序API（单端口）
//--------------------------------------------------------------------+
static inline bool tud_hid_ready(void);
static inline bool tud_hid_boot_mode(void);
static inline bool tud_hid_report(uint8_t report_id, void const* report, uint8_t len);
static inline bool tud_hid_keyboard_report(uint8_t report_id, uint8_t modifier, uint8_t keycode[6]);
static inline bool tud_hid_mouse_report(uint8_t report_id, uint8_t buttons, int8_t x, int8_t y, int8_t vertical, int8_t horizontal);

//--------------------------------------------------------------------+
// 回调（弱是可选的）
//--------------------------------------------------------------------+

// 收到GET HID REPORT DESCRIPTOR请求时调用
// 应用程序返回指向描述符的指针，其内容必须存在足够长的时间才能完成传输
uint8_t const * tud_hid_descriptor_report_cb(uint8_t itf);

// 收到GET_REPORT控制请求时调用
// 应用程序必须填充缓冲区报告的内容并返回其长度。
// 返回零将导致堆栈STALL请求
uint16_t tud_hid_get_report_cb(uint8_t itf, uint8_t report_id, hid_report_type_t report_type, uint8_t* buffer, uint16_t reqlen);

// 在收到SET_REPORT控制请求或
// OUT端点上收到的数据（报告ID=0，类型=0）
void tud_hid_set_report_cb(uint8_t itf, uint8_t report_id, hid_report_type_t report_type, uint8_t const* buffer, uint16_t bufsize);

// 收到SET_PROTOCOL请求时调用（模式切换启动<->报告）
TU_ATTR_WEAK void tud_hid_boot_mode_cb(uint8_t itf, uint8_t boot_mode);

// 收到SET_IDLE请求时调用。return false将暂停请求
// -空闲率=0：仅在发生更改时发送报告，即跳过重复
// -空闲速率>0：跳过复制，但每个空闲速率（以4毫秒为单位）至少发送1个报告。
TU_ATTR_WEAK bool tud_hid_set_idle_cb(uint8_t itf, uint8_t idle_rate);

// 成功将REPORT发送到主机时调用
// 应用程序可以使用它发送下一个报告
// 注意：对于复合报表，报表[0]是报表ID
TU_ATTR_WEAK void tud_hid_report_complete_cb(uint8_t itf, uint8_t const* report, uint8_t len);


//--------------------------------------------------------------------+
// 内联函数
//--------------------------------------------------------------------+
static inline bool tud_hid_ready(void)
{
  return tud_hid_n_ready(0);
}

static inline bool tud_hid_boot_mode(void)
{
  return tud_hid_n_boot_mode(0);
}

static inline bool tud_hid_report(uint8_t report_id, void const* report, uint8_t len)
{
  return tud_hid_n_report(0, report_id, report, len);
}

static inline bool tud_hid_keyboard_report(uint8_t report_id, uint8_t modifier, uint8_t keycode[6])
{
  return tud_hid_n_keyboard_report(0, report_id, modifier, keycode);
}

static inline bool tud_hid_mouse_report(uint8_t report_id, uint8_t buttons, int8_t x, int8_t y, int8_t vertical, int8_t horizontal)
{
  return tud_hid_n_mouse_report(0, report_id, buttons, x, y, vertical, horizontal);
}

/* --------------------------------------------------------------------+
 * HID报告描述符模板
 *
 * 方便声明流行的HID设备（键盘、鼠标、消费者、游戏板等）。模板将“HID_REPORT_ID（n）”作为输入，如果未使用多个报告，则将其留空
 *
 * -仅1个报告：无参数uint8_t const report_desc[]=｛TUD_HID_report_desc_KEYBOARD（）｝；
 *
 * -多个报告：“HID_REPORT_ID（ID）”必须传递给模板uint8_t const REPORT_desc[]=｛TUD_HID_REPORT_desc_KEYBOARD（HID_REPORTID（1）），TUD_HID_REPORT_desc_MOUSE（HID_REPORT_ID（2））｝；
 *--------------------------------------------------------------------*/

// 键盘报告描述符模板
#define TUD_HID_REPORT_DESC_KEYBOARD(...) \
  HID_USAGE_PAGE ( HID_USAGE_PAGE_DESKTOP     )                    ,\
  HID_USAGE      ( HID_USAGE_DESKTOP_KEYBOARD )                    ,\
  HID_COLLECTION ( HID_COLLECTION_APPLICATION )                    ,\
    /* 报告ID（如果有）*/\
    __VA_ARGS__ \
    /* 8位修改键（Shfit、Control、Alt）*/ \
    HID_USAGE_PAGE ( HID_USAGE_PAGE_KEYBOARD )                     ,\
      HID_USAGE_MIN    ( 224                                    )  ,\
      HID_USAGE_MAX    ( 231                                    )  ,\
      HID_LOGICAL_MIN  ( 0                                      )  ,\
      HID_LOGICAL_MAX  ( 1                                      )  ,\
      HID_REPORT_COUNT ( 8                                      )  ,\
      HID_REPORT_SIZE  ( 1                                      )  ,\
      HID_INPUT        ( HID_DATA | HID_VARIABLE | HID_ABSOLUTE )  ,\
      /* 保留8位*/ \
      HID_REPORT_COUNT ( 1                                      )  ,\
      HID_REPORT_SIZE  ( 8                                      )  ,\
      HID_INPUT        ( HID_CONSTANT                           )  ,\
    /* 6字节键码*/ \
    HID_USAGE_PAGE ( HID_USAGE_PAGE_KEYBOARD )                     ,\
      HID_USAGE_MIN    ( 0                                   )     ,\
      HID_USAGE_MAX    ( 255                                 )     ,\
      HID_LOGICAL_MIN  ( 0                                   )     ,\
      HID_LOGICAL_MAX  ( 255                                 )     ,\
      HID_REPORT_COUNT ( 6                                   )     ,\
      HID_REPORT_SIZE  ( 8                                   )     ,\
      HID_INPUT        ( HID_DATA | HID_ARRAY | HID_ABSOLUTE )     ,\
    /* 5位LED指示器假名|合成| ScrollLock | CapsLock | NumLock*/ \
    HID_USAGE_PAGE  ( HID_USAGE_PAGE_LED                   )       ,\
      HID_USAGE_MIN    ( 1                                       ) ,\
      HID_USAGE_MAX    ( 5                                       ) ,\
      HID_REPORT_COUNT ( 5                                       ) ,\
      HID_REPORT_SIZE  ( 1                                       ) ,\
      HID_OUTPUT       ( HID_DATA | HID_VARIABLE | HID_ABSOLUTE  ) ,\
      /* led衬垫*/ \
      HID_REPORT_COUNT ( 1                                       ) ,\
      HID_REPORT_SIZE  ( 3                                       ) ,\
      HID_OUTPUT       ( HID_CONSTANT                            ) ,\
  HID_COLLECTION_END \

// 鼠标报告描述符模板
#define TUD_HID_REPORT_DESC_MOUSE(...) \
  HID_USAGE_PAGE ( HID_USAGE_PAGE_DESKTOP      )                   ,\
  HID_USAGE      ( HID_USAGE_DESKTOP_MOUSE     )                   ,\
  HID_COLLECTION ( HID_COLLECTION_APPLICATION  )                   ,\
    /* 报告ID（如果有）*/\
    __VA_ARGS__ \
    HID_USAGE      ( HID_USAGE_DESKTOP_POINTER )                   ,\
    HID_COLLECTION ( HID_COLLECTION_PHYSICAL   )                   ,\
      HID_USAGE_PAGE  ( HID_USAGE_PAGE_BUTTON  )                   ,\
        HID_USAGE_MIN   ( 1                                      ) ,\
        HID_USAGE_MAX   ( 5                                      ) ,\
        HID_LOGICAL_MIN ( 0                                      ) ,\
        HID_LOGICAL_MAX ( 1                                      ) ,\
        /* 左、右、中、后、前按钮*/ \
        HID_REPORT_COUNT( 5                                      ) ,\
        HID_REPORT_SIZE ( 1                                      ) ,\
        HID_INPUT       ( HID_DATA | HID_VARIABLE | HID_ABSOLUTE ) ,\
        /* 3位填充*/ \
        HID_REPORT_COUNT( 1                                      ) ,\
        HID_REPORT_SIZE ( 3                                      ) ,\
        HID_INPUT       ( HID_CONSTANT                           ) ,\
      HID_USAGE_PAGE  ( HID_USAGE_PAGE_DESKTOP )                   ,\
        /* 十、 Y位置[-127127]*/ \
        HID_USAGE       ( HID_USAGE_DESKTOP_X                    ) ,\
        HID_USAGE       ( HID_USAGE_DESKTOP_Y                    ) ,\
        HID_LOGICAL_MIN ( 0x81                                   ) ,\
        HID_LOGICAL_MAX ( 0x7f                                   ) ,\
        HID_REPORT_COUNT( 2                                      ) ,\
        HID_REPORT_SIZE ( 8                                      ) ,\
        HID_INPUT       ( HID_DATA | HID_VARIABLE | HID_RELATIVE ) ,\
        /* Verital滚轮[-127，127]*/ \
        HID_USAGE       ( HID_USAGE_DESKTOP_WHEEL                )  ,\
        HID_LOGICAL_MIN ( 0x81                                   )  ,\
        HID_LOGICAL_MAX ( 0x7f                                   )  ,\
        HID_REPORT_COUNT( 1                                      )  ,\
        HID_REPORT_SIZE ( 8                                      )  ,\
        HID_INPUT       ( HID_DATA | HID_VARIABLE | HID_RELATIVE )  ,\
      HID_USAGE_PAGE  ( HID_USAGE_PAGE_CONSUMER ), \
       /* 水平滚轮滚动[-127，127]*/ \
        HID_USAGE_N     ( HID_USAGE_CONSUMER_AC_PAN, 2           ), \
        HID_LOGICAL_MIN ( 0x81                                   ), \
        HID_LOGICAL_MAX ( 0x7f                                   ), \
        HID_REPORT_COUNT( 1                                      ), \
        HID_REPORT_SIZE ( 8                                      ), \
        HID_INPUT       ( HID_DATA | HID_VARIABLE | HID_RELATIVE ), \
    HID_COLLECTION_END                                            , \
  HID_COLLECTION_END \

// 消费者控制报告描述符模板
#define TUD_HID_REPORT_DESC_CONSUMER(...) \
  HID_USAGE_PAGE ( HID_USAGE_PAGE_CONSUMER    )              ,\
  HID_USAGE      ( HID_USAGE_CONSUMER_CONTROL )              ,\
  HID_COLLECTION ( HID_COLLECTION_APPLICATION )              ,\
    /* 报告ID（如果有）*/\
    __VA_ARGS__ \
    HID_LOGICAL_MIN  ( 0x00                                ) ,\
    HID_LOGICAL_MAX_N( 0x03FF, 2                           ) ,\
    HID_USAGE_MIN    ( 0x00                                ) ,\
    HID_USAGE_MAX_N  ( 0x03FF, 2                           ) ,\
    HID_REPORT_COUNT ( 1                                   ) ,\
    HID_REPORT_SIZE  ( 16                                  ) ,\
    HID_INPUT        ( HID_DATA | HID_ARRAY | HID_ABSOLUTE ) ,\
  HID_COLLECTION_END \

/* 系统控制报告描述符模板0x00-不执行任何操作0x01-关闭电源0x02-待机0x04-唤醒主机
 */
#define TUD_HID_REPORT_DESC_SYSTEM_CONTROL(...) \
  HID_USAGE_PAGE ( HID_USAGE_PAGE_DESKTOP           )        ,\
  HID_USAGE      ( HID_USAGE_DESKTOP_SYSTEM_CONTROL )        ,\
  HID_COLLECTION ( HID_COLLECTION_APPLICATION       )        ,\
    /* 报告ID（如果有）*/\
    __VA_ARGS__ \
    /* 2位系统电源控制*/ \
    HID_LOGICAL_MIN  ( 1                                   ) ,\
    HID_LOGICAL_MAX  ( 3                                   ) ,\
    HID_REPORT_COUNT ( 1                                   ) ,\
    HID_REPORT_SIZE  ( 2                                   ) ,\
    HID_USAGE        ( HID_USAGE_DESKTOP_SYSTEM_SLEEP      ) ,\
    HID_USAGE        ( HID_USAGE_DESKTOP_SYSTEM_POWER_DOWN ) ,\
    HID_USAGE        ( HID_USAGE_DESKTOP_SYSTEM_WAKE_UP    ) ,\
    HID_INPUT        ( HID_DATA | HID_ARRAY | HID_ABSOLUTE ) ,\
    /* 6位填充*/ \
    HID_REPORT_COUNT ( 1                                   ) ,\
    HID_REPORT_SIZE  ( 6                                   ) ,\
    HID_INPUT        ( HID_CONSTANT                        ) ,\
  HID_COLLECTION_END \

// Gamepad报告描述符模板
// 带有16个按钮、2个操纵杆和1个帽子/dpad，布局如下
// |X|Y|Z|Rz|Rx|Ry（每个1字节）|hat/DPAD（1字节）|按钮映射（2字节）|
#define TUD_HID_REPORT_DESC_GAMEPAD(...) \
  HID_USAGE_PAGE ( HID_USAGE_PAGE_DESKTOP     )                 ,\
  HID_USAGE      ( HID_USAGE_DESKTOP_GAMEPAD  )                 ,\
  HID_COLLECTION ( HID_COLLECTION_APPLICATION )                 ,\
    /* 报告ID（如果有）*/\
    __VA_ARGS__ \
    /* 8位X、Y、Z、Rz、Rx、Ry（最小-127，最大127）*/ \
    HID_USAGE_PAGE   ( HID_USAGE_PAGE_DESKTOP                 ) ,\
    HID_USAGE        ( HID_USAGE_DESKTOP_X                    ) ,\
    HID_USAGE        ( HID_USAGE_DESKTOP_Y                    ) ,\
    HID_USAGE        ( HID_USAGE_DESKTOP_Z                    ) ,\
    HID_USAGE        ( HID_USAGE_DESKTOP_RZ                   ) ,\
    HID_USAGE        ( HID_USAGE_DESKTOP_RX                   ) ,\
    HID_USAGE        ( HID_USAGE_DESKTOP_RY                   ) ,\
    HID_LOGICAL_MIN  ( 0x81                                   ) ,\
    HID_LOGICAL_MAX  ( 0x7f                                   ) ,\
    HID_REPORT_COUNT ( 6                                      ) ,\
    HID_REPORT_SIZE  ( 8                                      ) ,\
    HID_INPUT        ( HID_DATA | HID_VARIABLE | HID_ABSOLUTE ) ,\
    /* 8位DPad/帽子按钮映射*/ \
    HID_USAGE_PAGE   ( HID_USAGE_PAGE_DESKTOP                 ) ,\
    HID_USAGE        ( HID_USAGE_DESKTOP_HAT_SWITCH           ) ,\
    HID_LOGICAL_MIN  ( 1                                      ) ,\
    HID_LOGICAL_MAX  ( 8                                      ) ,\
    HID_PHYSICAL_MIN ( 0                                      ) ,\
    HID_PHYSICAL_MAX_N ( 315, 2                               ) ,\
    HID_REPORT_COUNT ( 1                                      ) ,\
    HID_REPORT_SIZE  ( 8                                      ) ,\
    HID_INPUT        ( HID_DATA | HID_VARIABLE | HID_ABSOLUTE ) ,\
    /* 16位按钮映射*/ \
    HID_USAGE_PAGE   ( HID_USAGE_PAGE_BUTTON                  ) ,\
    HID_USAGE_MIN    ( 1                                      ) ,\
    HID_USAGE_MAX    ( 16                                     ) ,\
    HID_LOGICAL_MIN  ( 0                                      ) ,\
    HID_LOGICAL_MAX  ( 1                                      ) ,\
    HID_REPORT_COUNT ( 16                                     ) ,\
    HID_REPORT_SIZE  ( 1                                      ) ,\
    HID_INPUT        ( HID_DATA | HID_VARIABLE | HID_ABSOLUTE ) ,\
  HID_COLLECTION_END \

// HID通用输入和输出
// -第一个参数是报告大小（必填）
// -第二个参数是报告id HID_report_id（n）（可选）
#define TUD_HID_REPORT_DESC_GENERIC_INOUT(report_size, ...) \
    HID_USAGE_PAGE_N ( HID_USAGE_PAGE_VENDOR, 2   ),\
    HID_USAGE        ( 0x01                       ),\
    HID_COLLECTION   ( HID_COLLECTION_APPLICATION ),\
      /* 报告ID（如果有）*/\
      __VA_ARGS__ \
      /* 输入*/ \
      HID_USAGE       ( 0x02                                   ),\
      HID_LOGICAL_MIN ( 0x00                                   ),\
      HID_LOGICAL_MAX ( 0xff                                   ),\
      HID_REPORT_SIZE ( 8                                      ),\
      HID_REPORT_COUNT( report_size                            ),\
      HID_INPUT       ( HID_DATA | HID_VARIABLE | HID_ABSOLUTE ),\
      /* 输出*/ \
      HID_USAGE       ( 0x03                                    ),\
      HID_LOGICAL_MIN ( 0x00                                    ),\
      HID_LOGICAL_MAX ( 0xff                                    ),\
      HID_REPORT_SIZE ( 8                                       ),\
      HID_REPORT_COUNT( report_size                             ),\
      HID_OUTPUT      ( HID_DATA | HID_VARIABLE | HID_ABSOLUTE  ),\
    HID_COLLECTION_END \

//--------------------------------------------------------------------+
// 内部类驱动程序API
//--------------------------------------------------------------------+
void     hidd_init            (void);
void     hidd_reset           (uint8_t rhport);
uint16_t hidd_open            (uint8_t rhport, tusb_desc_interface_t const * itf_desc, uint16_t max_len);
bool     hidd_control_xfer_cb (uint8_t rhport, uint8_t stage, tusb_control_request_t const * request);
bool     hidd_xfer_cb         (uint8_t rhport, uint8_t ep_addr, xfer_result_t event, uint32_t xferred_bytes);

#ifdef __cplusplus
 }
#endif

#endif /* _TUSB_HID_DEVICE_H_ */

