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

/** \inggroup group_class\defgroup ClassDriver_HID人机接口设备（HID）
 *  @{ */

#ifndef _TUSB_HID_H_
#define _TUSB_HID_H_

#include "common/tusb_common.h"

#ifdef __cplusplus
 extern "C" {
#endif

//--------------------------------------------------------------------+
// 通用定义
//--------------------------------------------------------------------+
/** \defgroup ClassDriver_HID_Common公共定义
 *  @{ */

 ///USB HID描述符
typedef struct TU_ATTR_PACKED
{
  uint8_t  bLength;         /**<HID描述符的总大小的数字表达式*/
  uint8_t  bDescriptorType; /**<指定HID描述符类型的常量名称。*/

  uint16_t bcdHID;          /**<标识HID类规范版本的数字表达式*/
  uint8_t  bCountryCode;    /**<标识本地化硬件的国家/地区代码的数字表达式。*/
  uint8_t  bNumDescriptors; /**<指定类描述符数量的数字表达式*/

  uint8_t  bReportType;     /**<HID类报告的类型。*/
  uint16_t wReportLength;   /**<报告描述符的总大小。*/
} tusb_hid_descriptor_hid_t;

///HID子类
typedef enum
{
  HID_SUBCLASS_NONE = 0, ///<无子类
  HID_SUBCLASS_BOOT = 1  ///<引导接口子类
}hid_subclass_type_t;

///HID协议
typedef enum
{
  HID_PROTOCOL_NONE     = 0, ///<无
  HID_PROTOCOL_KEYBOARD = 1, ///<键盘
  HID_PROTOCOL_MOUSE    = 2  ///<鼠标
}hid_protocol_type_t;

///HID描述符类型
typedef enum
{
  HID_DESC_TYPE_HID      = 0x21, ///<HID描述符
  HID_DESC_TYPE_REPORT   = 0x22, ///<报告描述符
  HID_DESC_TYPE_PHYSICAL = 0x23  ///<物理描述符
}hid_descriptor_type_t;

///HID请求报告类型
typedef enum
{
  HID_REPORT_TYPE_INVALID = 0,
  HID_REPORT_TYPE_INPUT,      ///<输入
  HID_REPORT_TYPE_OUTPUT,     ///<输出
  HID_REPORT_TYPE_FEATURE     ///<功能
}hid_report_type_t;

///HID类特定控制请求
typedef enum
{
  HID_REQ_CONTROL_GET_REPORT   = 0x01, ///<获取报告
  HID_REQ_CONTROL_GET_IDLE     = 0x02, ///<空闲
  HID_REQ_CONTROL_GET_PROTOCOL = 0x03, ///<获取协议
  HID_REQ_CONTROL_SET_REPORT   = 0x09, ///<设置报告
  HID_REQ_CONTROL_SET_IDLE     = 0x0a, ///<设置空闲
  HID_REQ_CONTROL_SET_PROTOCOL = 0x0b  ///<设置协议
}hid_request_type_t;

///HID国家代码
typedef enum
{
  HID_LOCAL_NotSupported = 0   , ///<不支持
  HID_LOCAL_Arabic             , ///<阿拉伯语
  HID_LOCAL_Belgian            , ///<比利时语
  HID_LOCAL_Canadian_Bilingual , ///<加拿大_双语
  HID_LOCAL_Canadian_French    , ///<加拿大_法国
  HID_LOCAL_Czech_Republic     , ///<捷克_公共
  HID_LOCAL_Danish             , ///<丹麦语
  HID_LOCAL_Finnish            , ///<芬兰语
  HID_LOCAL_French             , ///<法语
  HID_LOCAL_German             , ///<德语
  HID_LOCAL_Greek              , ///<希腊语
  HID_LOCAL_Hebrew             , ///<希伯来语
  HID_LOCAL_Hungary            , ///<匈牙利
  HID_LOCAL_International      , ///<国际
  HID_LOCAL_Italian            , ///<意大利语
  HID_LOCAL_Japan_Katakana     , ///<日语_片假名
  HID_LOCAL_Korean             , ///<朝鲜语
  HID_LOCAL_Latin_American     , ///<拉丁美洲
  HID_LOCAL_Netherlands_Dutch  , ///<荷兰语/荷兰语
  HID_LOCAL_Norwegian          , ///<挪威语
  HID_LOCAL_Persian_Farsi      , ///<波斯语（波斯语）
  HID_LOCAL_Poland             , ///<波兰
  HID_LOCAL_Portuguese         , ///<葡萄牙语
  HID_LOCAL_Russia             , ///<俄罗斯
  HID_LOCAL_Slovakia           , ///<斯洛伐克
  HID_LOCAL_Spanish            , ///<西班牙语
  HID_LOCAL_Swedish            , ///<瑞典语
  HID_LOCAL_Swiss_French       , ///<瑞士语/法语
  HID_LOCAL_Swiss_German       , ///<瑞士/德国
  HID_LOCAL_Switzerland        , ///<瑞士
  HID_LOCAL_Taiwan             , ///<台湾
  HID_LOCAL_Turkish_Q          , ///<突厥语-Q
  HID_LOCAL_UK                 , ///< UK
  HID_LOCAL_US                 , ///< US
  HID_LOCAL_Yugoslavia         , ///<南斯拉夫
  HID_LOCAL_Turkish_F            ///<突厥语-F
} hid_country_code_t;

/** @} */

//--------------------------------------------------------------------+
// GAMEPAD
//--------------------------------------------------------------------+
/** \添加组ClassDriver_HID_Gamepad游戏板
 *  @{ */

/* 从…起https://www.kernel.org/doc/html/latest/input/gamepad.html____________________________/[__ZL__][__ZR__]|/[__TL __][__ TR __]\ |前触发器__/________________________________ \ __ |////（N）\ |/| | __ | MO | __ _ _ |主极板|<==DP==>| SE | | ST |（W）-|-（E）| | | ___ ___///\//（S）/\ __ |/\________ | LS | ____ | RS | ________///|//\ \//\ ___//\ | |控制杆|/\_____/\____/\|__||/ \ | \_____/ \_____/

     |________|______||________|___________|D-Pad左-右动作垫斗杆

                 |_____________|菜单板

  大多数游戏手柄具有以下功能：
  -行动板4个菱形按钮（右侧）北、南、西和东。
  -D-Pad（方向板）4个按钮（位于左侧），分别指向上、下、左和右。
  -菜单板不同的星座，但大多数时候有两个按钮：选择-开始。
  -模拟杆提供可自由移动的杆来控制方向，如果您按下模拟杆，模拟杆也可以提供数字按钮。
  -触发器在垂直方向上位于衬垫的上侧。上部按钮通常命名为“左触发器”和“右触发器”，下部按钮命名为“Z向左”和“Z向右”。
  -隆隆声许多设备提供力反馈功能。但大多数只是简单的隆隆声电机。
 */

///HID游戏板协议报告。
typedef struct TU_ATTR_PACKED
{
  int8_t  x;         ///<左模拟杆的Delta x移动
  int8_t  y;         ///<左模拟杆的增量y移动
  int8_t  z;         ///<右模拟操纵杆的Delta z移动
  int8_t  rz;        ///<右模拟操纵杆的Delta Rz移动
  int8_t  rx;        ///<模拟左触发器的Delta Rx移动
  int8_t  ry;        ///<模拟右触发器的Delta Ry移动
  uint8_t hat;       ///<DPad/hat中当前按下按钮的按钮掩码
  uint16_t buttons;  ///<当前按下按钮的按钮掩码
}hid_gamepad_report_t;

///标准游戏板按钮位图（来自Linux输入事件代码）
typedef enum
{
  GAMEPAD_BUTTON_A      = TU_BIT(0),  ///<A/South按钮
  GAMEPAD_BUTTON_B      = TU_BIT(1),  ///<B/东按钮
  GAMEPAD_BUTTON_C      = TU_BIT(2),  ///<C按钮
  GAMEPAD_BUTTON_X      = TU_BIT(3),  ///<X/北按钮
  GAMEPAD_BUTTON_Y      = TU_BIT(4),  ///<Y/West按钮
  GAMEPAD_BUTTON_Z      = TU_BIT(5),  ///<Z按钮
  GAMEPAD_BUTTON_TL     = TU_BIT(6),  ///<L1按钮
  GAMEPAD_BUTTON_TR     = TU_BIT(7),  ///<R1按钮
  GAMEPAD_BUTTON_TL2    = TU_BIT(8),  ///<L2按钮
  GAMEPAD_BUTTON_TR2    = TU_BIT(9),  ///<R2按钮
  GAMEPAD_BUTTON_SELECT = TU_BIT(10), ///<选择按钮
  GAMEPAD_BUTTON_START  = TU_BIT(11), ///<开始按钮
  GAMEPAD_BUTTON_MODE   = TU_BIT(12), ///<模式按钮
  GAMEPAD_BUTTON_THUMBL = TU_BIT(13), ///<L3按钮
  GAMEPAD_BUTTON_THUMBR = TU_BIT(14), ///<R3按钮
//GAMEPAD_BUTTON_=TU_BIT（15），///<未定义按钮
}hid_gamepad_button_bm_t;

///标准Gamepad HAT/DPAD按钮（来自Linux输入事件代码）
typedef enum
{
  GAMEPAD_HAT_CENTERED   = 0,  ///< DPAD_CENTERED
  GAMEPAD_HAT_UP         = 1,  ///< DPAD_UP
  GAMEPAD_HAT_UP_RIGHT   = 2,  ///< DPAD_UP_RIGHT
  GAMEPAD_HAT_RIGHT      = 3,  ///< DPAD_RIGHT
  GAMEPAD_HAT_DOWN_RIGHT = 4,  ///< DPAD_DOWN_RIGHT
  GAMEPAD_HAT_DOWN       = 5,  ///< DPAD_DOWN
  GAMEPAD_HAT_DOWN_LEFT  = 6,  ///< DPAD_DOWN_LEFT
  GAMEPAD_HAT_LEFT       = 7,  ///< DPAD_LEFT
  GAMEPAD_HAT_UP_LEFT    = 8,  ///< DPAD_UP_LEFT
}hid_gamepad_hat_t;

/// @}

//--------------------------------------------------------------------+
// MOUSE
//--------------------------------------------------------------------+
/** \添加组ClassDriver_HID_Mouse鼠标
 *  @{ */

///标准HID引导协议鼠标报告。
typedef struct TU_ATTR_PACKED
{
  uint8_t buttons; /**＜buttons mask用于鼠标中当前按下的按钮。*/
  int8_t  x;       /**<鼠标的当前增量x移动。*/
  int8_t  y;       /**<鼠标上的当前增量y移动。*/
  int8_t  wheel;   /**<鼠标上的当前三角轮移动。*/
  int8_t  pan;     // 使用AC平移
} hid_mouse_report_t;

///标准鼠标按钮位图
typedef enum
{
  MOUSE_BUTTON_LEFT     = TU_BIT(0), ///<左按钮
  MOUSE_BUTTON_RIGHT    = TU_BIT(1), ///<右按钮
  MOUSE_BUTTON_MIDDLE   = TU_BIT(2), ///<中间按钮
  MOUSE_BUTTON_BACKWARD = TU_BIT(3), ///<后退按钮，
  MOUSE_BUTTON_FORWARD  = TU_BIT(4), ///<前进按钮，
}hid_mouse_button_bm_t;

/// @}

//--------------------------------------------------------------------+
// 键盘
//--------------------------------------------------------------------+
/** \addtogroup ClassDriver_HID_键盘键盘
 *  @{ */

///标准HID引导协议键盘报告。
typedef struct TU_ATTR_PACKED
{
  uint8_t modifier;   /**<键盘修饰符（Keyboard_modifier_*掩码）。*/
  uint8_t reserved;   /**<保留供OEM使用，始终设置为0。*/
  uint8_t keycode[6]; /**<当前按键的按键代码。*/
} hid_keyboard_report_t;

///键盘修改器代码位图
typedef enum
{
  KEYBOARD_MODIFIER_LEFTCTRL   = TU_BIT(0), ///<左控制
  KEYBOARD_MODIFIER_LEFTSHIFT  = TU_BIT(1), ///<左移
  KEYBOARD_MODIFIER_LEFTALT    = TU_BIT(2), ///<左Alt
  KEYBOARD_MODIFIER_LEFTGUI    = TU_BIT(3), ///<左窗口
  KEYBOARD_MODIFIER_RIGHTCTRL  = TU_BIT(4), ///<右控制
  KEYBOARD_MODIFIER_RIGHTSHIFT = TU_BIT(5), ///<右移
  KEYBOARD_MODIFIER_RIGHTALT   = TU_BIT(6), ///<右Alt
  KEYBOARD_MODIFIER_RIGHTGUI   = TU_BIT(7)  ///<右窗口
}hid_keyboard_modifier_bm_t;

typedef enum
{
  KEYBOARD_LED_NUMLOCK    = TU_BIT(0), ///<数字锁定LED
  KEYBOARD_LED_CAPSLOCK   = TU_BIT(1), ///<大写锁定LED
  KEYBOARD_LED_SCROLLLOCK = TU_BIT(2), ///<滚动锁定LED
  KEYBOARD_LED_COMPOSE    = TU_BIT(3), ///<合成模式
  KEYBOARD_LED_KANA       = TU_BIT(4) ///<假名模式
}hid_keyboard_led_bm_t;

/// @}

//--------------------------------------------------------------------+
// HID KEYCODE
//--------------------------------------------------------------------+
#define HID_KEY_NONE                      0x00
#define HID_KEY_A                         0x04
#define HID_KEY_B                         0x05
#define HID_KEY_C                         0x06
#define HID_KEY_D                         0x07
#define HID_KEY_E                         0x08
#define HID_KEY_F                         0x09
#define HID_KEY_G                         0x0A
#define HID_KEY_H                         0x0B
#define HID_KEY_I                         0x0C
#define HID_KEY_J                         0x0D
#define HID_KEY_K                         0x0E
#define HID_KEY_L                         0x0F
#define HID_KEY_M                         0x10
#define HID_KEY_N                         0x11
#define HID_KEY_O                         0x12
#define HID_KEY_P                         0x13
#define HID_KEY_Q                         0x14
#define HID_KEY_R                         0x15
#define HID_KEY_S                         0x16
#define HID_KEY_T                         0x17
#define HID_KEY_U                         0x18
#define HID_KEY_V                         0x19
#define HID_KEY_W                         0x1A
#define HID_KEY_X                         0x1B
#define HID_KEY_Y                         0x1C
#define HID_KEY_Z                         0x1D
#define HID_KEY_1                         0x1E
#define HID_KEY_2                         0x1F
#define HID_KEY_3                         0x20
#define HID_KEY_4                         0x21
#define HID_KEY_5                         0x22
#define HID_KEY_6                         0x23
#define HID_KEY_7                         0x24
#define HID_KEY_8                         0x25
#define HID_KEY_9                         0x26
#define HID_KEY_0                         0x27
#define HID_KEY_ENTER                     0x28
#define HID_KEY_ESCAPE                    0x29
#define HID_KEY_BACKSPACE                 0x2A
#define HID_KEY_TAB                       0x2B
#define HID_KEY_SPACE                     0x2C
#define HID_KEY_MINUS                     0x2D
#define HID_KEY_EQUAL                     0x2E
#define HID_KEY_BRACKET_LEFT              0x2F
#define HID_KEY_BRACKET_RIGHT             0x30
#define HID_KEY_BACKSLASH                 0x31
#define HID_KEY_EUROPE_1                  0x32
#define HID_KEY_SEMICOLON                 0x33
#define HID_KEY_APOSTROPHE                0x34
#define HID_KEY_GRAVE                     0x35
#define HID_KEY_COMMA                     0x36
#define HID_KEY_PERIOD                    0x37
#define HID_KEY_SLASH                     0x38
#define HID_KEY_CAPS_LOCK                 0x39
#define HID_KEY_F1                        0x3A
#define HID_KEY_F2                        0x3B
#define HID_KEY_F3                        0x3C
#define HID_KEY_F4                        0x3D
#define HID_KEY_F5                        0x3E
#define HID_KEY_F6                        0x3F
#define HID_KEY_F7                        0x40
#define HID_KEY_F8                        0x41
#define HID_KEY_F9                        0x42
#define HID_KEY_F10                       0x43
#define HID_KEY_F11                       0x44
#define HID_KEY_F12                       0x45
#define HID_KEY_PRINT_SCREEN              0x46
#define HID_KEY_SCROLL_LOCK               0x47
#define HID_KEY_PAUSE                     0x48
#define HID_KEY_INSERT                    0x49
#define HID_KEY_HOME                      0x4A
#define HID_KEY_PAGE_UP                   0x4B
#define HID_KEY_DELETE                    0x4C
#define HID_KEY_END                       0x4D
#define HID_KEY_PAGE_DOWN                 0x4E
#define HID_KEY_ARROW_RIGHT               0x4F
#define HID_KEY_ARROW_LEFT                0x50
#define HID_KEY_ARROW_DOWN                0x51
#define HID_KEY_ARROW_UP                  0x52
#define HID_KEY_NUM_LOCK                  0x53
#define HID_KEY_KEYPAD_DIVIDE             0x54
#define HID_KEY_KEYPAD_MULTIPLY           0x55
#define HID_KEY_KEYPAD_SUBTRACT           0x56
#define HID_KEY_KEYPAD_ADD                0x57
#define HID_KEY_KEYPAD_ENTER              0x58
#define HID_KEY_KEYPAD_1                  0x59
#define HID_KEY_KEYPAD_2                  0x5A
#define HID_KEY_KEYPAD_3                  0x5B
#define HID_KEY_KEYPAD_4                  0x5C
#define HID_KEY_KEYPAD_5                  0x5D
#define HID_KEY_KEYPAD_6                  0x5E
#define HID_KEY_KEYPAD_7                  0x5F
#define HID_KEY_KEYPAD_8                  0x60
#define HID_KEY_KEYPAD_9                  0x61
#define HID_KEY_KEYPAD_0                  0x62
#define HID_KEY_KEYPAD_DECIMAL            0x63
#define HID_KEY_EUROPE_2                  0x64
#define HID_KEY_APPLICATION               0x65
#define HID_KEY_POWER                     0x66
#define HID_KEY_KEYPAD_EQUAL              0x67
#define HID_KEY_F13                       0x68
#define HID_KEY_F14                       0x69
#define HID_KEY_F15                       0x6A
#define HID_KEY_F16                       0x6B
#define HID_KEY_F17                       0x6C
#define HID_KEY_F18                       0x6D
#define HID_KEY_F19                       0x6E
#define HID_KEY_F20                       0x6F
#define HID_KEY_F21                       0x70
#define HID_KEY_F22                       0x71
#define HID_KEY_F23                       0x72
#define HID_KEY_F24                       0x73
#define HID_KEY_EXECUTE                   0x74
#define HID_KEY_HELP                      0x75
#define HID_KEY_MENU                      0x76
#define HID_KEY_SELECT                    0x77
#define HID_KEY_STOP                      0x78
#define HID_KEY_AGAIN                     0x79
#define HID_KEY_UNDO                      0x7A
#define HID_KEY_CUT                       0x7B
#define HID_KEY_COPY                      0x7C
#define HID_KEY_PASTE                     0x7D
#define HID_KEY_FIND                      0x7E
#define HID_KEY_MUTE                      0x7F
#define HID_KEY_VOLUME_UP                 0x80
#define HID_KEY_VOLUME_DOWN               0x81
#define HID_KEY_LOCKING_CAPS_LOCK         0x82
#define HID_KEY_LOCKING_NUM_LOCK          0x83
#define HID_KEY_LOCKING_SCROLL_LOCK       0x84
#define HID_KEY_KEYPAD_COMMA              0x85
#define HID_KEY_KEYPAD_EQUAL_SIGN         0x86
#define HID_KEY_KANJI1                    0x87
#define HID_KEY_KANJI2                    0x88
#define HID_KEY_KANJI3                    0x89
#define HID_KEY_KANJI4                    0x8A
#define HID_KEY_KANJI5                    0x8B
#define HID_KEY_KANJI6                    0x8C
#define HID_KEY_KANJI7                    0x8D
#define HID_KEY_KANJI8                    0x8E
#define HID_KEY_KANJI9                    0x8F
#define HID_KEY_LANG1                     0x90
#define HID_KEY_LANG2                     0x91
#define HID_KEY_LANG3                     0x92
#define HID_KEY_LANG4                     0x93
#define HID_KEY_LANG5                     0x94
#define HID_KEY_LANG6                     0x95
#define HID_KEY_LANG7                     0x96
#define HID_KEY_LANG8                     0x97
#define HID_KEY_LANG9                     0x98
#define HID_KEY_ALTERNATE_ERASE           0x99
#define HID_KEY_SYSREQ_ATTENTION          0x9A
#define HID_KEY_CANCEL                    0x9B
#define HID_KEY_CLEAR                     0x9C
#define HID_KEY_PRIOR                     0x9D
#define HID_KEY_RETURN                    0x9E
#define HID_KEY_SEPARATOR                 0x9F
#define HID_KEY_OUT                       0xA0
#define HID_KEY_OPER                      0xA1
#define HID_KEY_CLEAR_AGAIN               0xA2
#define HID_KEY_CRSEL_PROPS               0xA3
#define HID_KEY_EXSEL                     0xA4
// 保留0xA5 DF
#define HID_KEY_CONTROL_LEFT              0xE0
#define HID_KEY_SHIFT_LEFT                0xE1
#define HID_KEY_ALT_LEFT                  0xE2
#define HID_KEY_GUI_LEFT                  0xE3
#define HID_KEY_CONTROL_RIGHT             0xE4
#define HID_KEY_SHIFT_RIGHT               0xE5
#define HID_KEY_ALT_RIGHT                 0xE6
#define HID_KEY_GUI_RIGHT                 0xE7


//--------------------------------------------------------------------+
// REPORT DESCRIPTOR
//--------------------------------------------------------------------+
//------------- ITEM & TAG -------------//
#define HID_REPORT_DATA_0(data)
#define HID_REPORT_DATA_1(data) , data
#define HID_REPORT_DATA_2(data) , U16_TO_U8S_LE(data)
#define HID_REPORT_DATA_3(data) , U32_TO_U8S_LE(data)

#define HID_REPORT_ITEM(data, tag, type, size) \
  (((tag) << 4) | ((type) << 2) | (size)) HID_REPORT_DATA_##size(data)

#define RI_TYPE_MAIN   0
#define RI_TYPE_GLOBAL 1
#define RI_TYPE_LOCAL  2

//------------- MAIN ITEMS 6.2.2.4 -------------//
#define HID_INPUT(x)           HID_REPORT_ITEM(x,  8, RI_TYPE_MAIN, 1)
#define HID_OUTPUT(x)          HID_REPORT_ITEM(x,  9, RI_TYPE_MAIN, 1)
#define HID_COLLECTION(x)      HID_REPORT_ITEM(x, 10, RI_TYPE_MAIN, 1)
#define HID_FEATURE(x)         HID_REPORT_ITEM(x, 11, RI_TYPE_MAIN, 1)
#define HID_COLLECTION_END     HID_REPORT_ITEM(x, 12, RI_TYPE_MAIN, 0)

//------------- INPUT, OUTPUT, FEATURE 6.2.2.5 -------------//
#define HID_DATA             (0<<0)
#define HID_CONSTANT         (1<<0)

#define HID_ARRAY            (0<<1)
#define HID_VARIABLE         (1<<1)

#define HID_ABSOLUTE         (0<<2)
#define HID_RELATIVE         (1<<2)

#define HID_WRAP_NO          (0<<3)
#define HID_WRAP             (1<<3)

#define HID_LINEAR           (0<<4)
#define HID_NONLINEAR        (1<<4)

#define HID_PREFERRED_STATE  (0<<5)
#define HID_PREFERRED_NO     (1<<5)

#define HID_NO_NULL_POSITION (0<<6)
#define HID_NULL_STATE       (1<<6)

#define HID_NON_VOLATILE     (0<<7)
#define HID_VOLATILE         (1<<7)

#define HID_BITFIELD         (0<<8)
#define HID_BUFFERED_BYTES   (1<<8)

//------------- COLLECTION ITEM 6.2.2.6 -------------//
enum {
  HID_COLLECTION_PHYSICAL = 0,
  HID_COLLECTION_APPLICATION,
  HID_COLLECTION_LOGICAL,
  HID_COLLECTION_REPORT,
  HID_COLLECTION_NAMED_ARRAY,
  HID_COLLECTION_USAGE_SWITCH,
  HID_COLLECTION_USAGE_MODIFIER
};

//------------- GLOBAL ITEMS 6.2.2.7 -------------//
#define HID_USAGE_PAGE(x)         HID_REPORT_ITEM(x, 0, RI_TYPE_GLOBAL, 1)
#define HID_USAGE_PAGE_N(x, n)    HID_REPORT_ITEM(x, 0, RI_TYPE_GLOBAL, n)

#define HID_LOGICAL_MIN(x)        HID_REPORT_ITEM(x, 1, RI_TYPE_GLOBAL, 1)
#define HID_LOGICAL_MIN_N(x, n)   HID_REPORT_ITEM(x, 1, RI_TYPE_GLOBAL, n)

#define HID_LOGICAL_MAX(x)        HID_REPORT_ITEM(x, 2, RI_TYPE_GLOBAL, 1)
#define HID_LOGICAL_MAX_N(x, n)   HID_REPORT_ITEM(x, 2, RI_TYPE_GLOBAL, n)

#define HID_PHYSICAL_MIN(x)       HID_REPORT_ITEM(x, 3, RI_TYPE_GLOBAL, 1)
#define HID_PHYSICAL_MIN_N(x, n)  HID_REPORT_ITEM(x, 3, RI_TYPE_GLOBAL, n)

#define HID_PHYSICAL_MAX(x)       HID_REPORT_ITEM(x, 4, RI_TYPE_GLOBAL, 1)
#define HID_PHYSICAL_MAX_N(x, n)  HID_REPORT_ITEM(x, 4, RI_TYPE_GLOBAL, n)

#define HID_UNIT_EXPONENT(x)      HID_REPORT_ITEM(x, 5, RI_TYPE_GLOBAL, 1)
#define HID_UNIT_EXPONENT_N(x, n) HID_REPORT_ITEM(x, 5, RI_TYPE_GLOBAL, n)

#define HID_UNIT(x)               HID_REPORT_ITEM(x, 6, RI_TYPE_GLOBAL, 1)
#define HID_UNIT_N(x, n)          HID_REPORT_ITEM(x, 6, RI_TYPE_GLOBAL, n)

#define HID_REPORT_SIZE(x)        HID_REPORT_ITEM(x, 7, RI_TYPE_GLOBAL, 1)
#define HID_REPORT_SIZE_N(x, n)   HID_REPORT_ITEM(x, 7, RI_TYPE_GLOBAL, n)

#define HID_REPORT_ID(x)          HID_REPORT_ITEM(x, 8, RI_TYPE_GLOBAL, 1),
#define HID_REPORT_ID_N(x)        HID_REPORT_ITEM(x, 8, RI_TYPE_GLOBAL, n),

#define HID_REPORT_COUNT(x)       HID_REPORT_ITEM(x, 9, RI_TYPE_GLOBAL, 1)
#define HID_REPORT_COUNT_N(x, n)  HID_REPORT_ITEM(x, 9, RI_TYPE_GLOBAL, n)

#define HID_PUSH                  HID_REPORT_ITEM(x, 10, RI_TYPE_GLOBAL, 0)
#define HID_POP                   HID_REPORT_ITEM(x, 11, RI_TYPE_GLOBAL, 0)

//------------- LOCAL ITEMS 6.2.2.8 -------------//
#define HID_USAGE(x)              HID_REPORT_ITEM(x, 0, RI_TYPE_LOCAL, 1)
#define HID_USAGE_N(x, n)         HID_REPORT_ITEM(x, 0, RI_TYPE_LOCAL, n)

#define HID_USAGE_MIN(x)          HID_REPORT_ITEM(x, 1, RI_TYPE_LOCAL, 1)
#define HID_USAGE_MIN_N(x, n)     HID_REPORT_ITEM(x, 1, RI_TYPE_LOCAL, n)

#define HID_USAGE_MAX(x)          HID_REPORT_ITEM(x, 2, RI_TYPE_LOCAL, 1)
#define HID_USAGE_MAX_N(x, n)     HID_REPORT_ITEM(x, 2, RI_TYPE_LOCAL, n)

//--------------------------------------------------------------------+
// 使用情况表
//--------------------------------------------------------------------+

///HID用法表-表1：用法页摘要
enum {
  HID_USAGE_PAGE_DESKTOP         = 0x01,
  HID_USAGE_PAGE_SIMULATE        = 0x02,
  HID_USAGE_PAGE_VIRTUAL_REALITY = 0x03,
  HID_USAGE_PAGE_SPORT           = 0x04,
  HID_USAGE_PAGE_GAME            = 0x05,
  HID_USAGE_PAGE_GENERIC_DEVICE  = 0x06,
  HID_USAGE_PAGE_KEYBOARD        = 0x07,
  HID_USAGE_PAGE_LED             = 0x08,
  HID_USAGE_PAGE_BUTTON          = 0x09,
  HID_USAGE_PAGE_ORDINAL         = 0x0a,
  HID_USAGE_PAGE_TELEPHONY       = 0x0b,
  HID_USAGE_PAGE_CONSUMER        = 0x0c,
  HID_USAGE_PAGE_DIGITIZER       = 0x0d,
  HID_USAGE_PAGE_PID             = 0x0f,
  HID_USAGE_PAGE_UNICODE         = 0x10,
  HID_USAGE_PAGE_ALPHA_DISPLAY   = 0x14,
  HID_USAGE_PAGE_MEDICAL         = 0x40,
  HID_USAGE_PAGE_MONITOR         = 0x80, //0x80-0x83
  HID_USAGE_PAGE_POWER           = 0x84, // 0x084-0x87
  HID_USAGE_PAGE_BARCODE_SCANNER = 0x8c,
  HID_USAGE_PAGE_SCALE           = 0x8d,
  HID_USAGE_PAGE_MSR             = 0x8e,
  HID_USAGE_PAGE_CAMERA          = 0x90,
  HID_USAGE_PAGE_ARCADE          = 0x91,
  HID_USAGE_PAGE_VENDOR          = 0xFF00 // 0xFF00-0xFFFF
};

///HID使用表-表6：通用桌面页
enum {
  HID_USAGE_DESKTOP_POINTER                               = 0x01,
  HID_USAGE_DESKTOP_MOUSE                                 = 0x02,
  HID_USAGE_DESKTOP_JOYSTICK                              = 0x04,
  HID_USAGE_DESKTOP_GAMEPAD                               = 0x05,
  HID_USAGE_DESKTOP_KEYBOARD                              = 0x06,
  HID_USAGE_DESKTOP_KEYPAD                                = 0x07,
  HID_USAGE_DESKTOP_MULTI_AXIS_CONTROLLER                 = 0x08,
  HID_USAGE_DESKTOP_TABLET_PC_SYSTEM                      = 0x09,
  HID_USAGE_DESKTOP_X                                     = 0x30,
  HID_USAGE_DESKTOP_Y                                     = 0x31,
  HID_USAGE_DESKTOP_Z                                     = 0x32,
  HID_USAGE_DESKTOP_RX                                    = 0x33,
  HID_USAGE_DESKTOP_RY                                    = 0x34,
  HID_USAGE_DESKTOP_RZ                                    = 0x35,
  HID_USAGE_DESKTOP_SLIDER                                = 0x36,
  HID_USAGE_DESKTOP_DIAL                                  = 0x37,
  HID_USAGE_DESKTOP_WHEEL                                 = 0x38,
  HID_USAGE_DESKTOP_HAT_SWITCH                            = 0x39,
  HID_USAGE_DESKTOP_COUNTED_BUFFER                        = 0x3a,
  HID_USAGE_DESKTOP_BYTE_COUNT                            = 0x3b,
  HID_USAGE_DESKTOP_MOTION_WAKEUP                         = 0x3c,
  HID_USAGE_DESKTOP_START                                 = 0x3d,
  HID_USAGE_DESKTOP_SELECT                                = 0x3e,
  HID_USAGE_DESKTOP_VX                                    = 0x40,
  HID_USAGE_DESKTOP_VY                                    = 0x41,
  HID_USAGE_DESKTOP_VZ                                    = 0x42,
  HID_USAGE_DESKTOP_VBRX                                  = 0x43,
  HID_USAGE_DESKTOP_VBRY                                  = 0x44,
  HID_USAGE_DESKTOP_VBRZ                                  = 0x45,
  HID_USAGE_DESKTOP_VNO                                   = 0x46,
  HID_USAGE_DESKTOP_FEATURE_NOTIFICATION                  = 0x47,
  HID_USAGE_DESKTOP_RESOLUTION_MULTIPLIER                 = 0x48,
  HID_USAGE_DESKTOP_SYSTEM_CONTROL                        = 0x80,
  HID_USAGE_DESKTOP_SYSTEM_POWER_DOWN                     = 0x81,
  HID_USAGE_DESKTOP_SYSTEM_SLEEP                          = 0x82,
  HID_USAGE_DESKTOP_SYSTEM_WAKE_UP                        = 0x83,
  HID_USAGE_DESKTOP_SYSTEM_CONTEXT_MENU                   = 0x84,
  HID_USAGE_DESKTOP_SYSTEM_MAIN_MENU                      = 0x85,
  HID_USAGE_DESKTOP_SYSTEM_APP_MENU                       = 0x86,
  HID_USAGE_DESKTOP_SYSTEM_MENU_HELP                      = 0x87,
  HID_USAGE_DESKTOP_SYSTEM_MENU_EXIT                      = 0x88,
  HID_USAGE_DESKTOP_SYSTEM_MENU_SELECT                    = 0x89,
  HID_USAGE_DESKTOP_SYSTEM_MENU_RIGHT                     = 0x8A,
  HID_USAGE_DESKTOP_SYSTEM_MENU_LEFT                      = 0x8B,
  HID_USAGE_DESKTOP_SYSTEM_MENU_UP                        = 0x8C,
  HID_USAGE_DESKTOP_SYSTEM_MENU_DOWN                      = 0x8D,
  HID_USAGE_DESKTOP_SYSTEM_COLD_RESTART                   = 0x8E,
  HID_USAGE_DESKTOP_SYSTEM_WARM_RESTART                   = 0x8F,
  HID_USAGE_DESKTOP_DPAD_UP                               = 0x90,
  HID_USAGE_DESKTOP_DPAD_DOWN                             = 0x91,
  HID_USAGE_DESKTOP_DPAD_RIGHT                            = 0x92,
  HID_USAGE_DESKTOP_DPAD_LEFT                             = 0x93,
  HID_USAGE_DESKTOP_SYSTEM_DOCK                           = 0xA0,
  HID_USAGE_DESKTOP_SYSTEM_UNDOCK                         = 0xA1,
  HID_USAGE_DESKTOP_SYSTEM_SETUP                          = 0xA2,
  HID_USAGE_DESKTOP_SYSTEM_BREAK                          = 0xA3,
  HID_USAGE_DESKTOP_SYSTEM_DEBUGGER_BREAK                 = 0xA4,
  HID_USAGE_DESKTOP_APPLICATION_BREAK                     = 0xA5,
  HID_USAGE_DESKTOP_APPLICATION_DEBUGGER_BREAK            = 0xA6,
  HID_USAGE_DESKTOP_SYSTEM_SPEAKER_MUTE                   = 0xA7,
  HID_USAGE_DESKTOP_SYSTEM_HIBERNATE                      = 0xA8,
  HID_USAGE_DESKTOP_SYSTEM_DISPLAY_INVERT                 = 0xB0,
  HID_USAGE_DESKTOP_SYSTEM_DISPLAY_INTERNAL               = 0xB1,
  HID_USAGE_DESKTOP_SYSTEM_DISPLAY_EXTERNAL               = 0xB2,
  HID_USAGE_DESKTOP_SYSTEM_DISPLAY_BOTH                   = 0xB3,
  HID_USAGE_DESKTOP_SYSTEM_DISPLAY_DUAL                   = 0xB4,
  HID_USAGE_DESKTOP_SYSTEM_DISPLAY_TOGGLE_INT_EXT         = 0xB5,
  HID_USAGE_DESKTOP_SYSTEM_DISPLAY_SWAP_PRIMARY_SECONDARY = 0xB6,
  HID_USAGE_DESKTOP_SYSTEM_DISPLAY_LCD_AUTOSCALE          = 0xB7
};


///HID用法表：使用者页（0x0C）
///仅包含Windows支持的控件（整个列表太长）
enum
{
  // 通用控件
  HID_USAGE_CONSUMER_CONTROL                           = 0x0001,

  // 电源控制
  HID_USAGE_CONSUMER_POWER                             = 0x0030,
  HID_USAGE_CONSUMER_RESET                             = 0x0031,
  HID_USAGE_CONSUMER_SLEEP                             = 0x0032,

  // 屏幕亮度
  HID_USAGE_CONSUMER_BRIGHTNESS_INCREMENT              = 0x006F,
  HID_USAGE_CONSUMER_BRIGHTNESS_DECREMENT              = 0x0070,

  // 这些HID用途仅在移动系统（电池供电）和
  // 需要Windows 8（版本8302或更高）。
  HID_USAGE_CONSUMER_WIRELESS_RADIO_CONTROLS           = 0x000C,
  HID_USAGE_CONSUMER_WIRELESS_RADIO_BUTTONS            = 0x00C6,
  HID_USAGE_CONSUMER_WIRELESS_RADIO_LED                = 0x00C7,
  HID_USAGE_CONSUMER_WIRELESS_RADIO_SLIDER_SWITCH      = 0x00C8,

  // 媒体控制
  HID_USAGE_CONSUMER_PLAY_PAUSE                        = 0x00CD,
  HID_USAGE_CONSUMER_SCAN_NEXT                         = 0x00B5,
  HID_USAGE_CONSUMER_SCAN_PREVIOUS                     = 0x00B6,
  HID_USAGE_CONSUMER_STOP                              = 0x00B7,
  HID_USAGE_CONSUMER_VOLUME                            = 0x00E0,
  HID_USAGE_CONSUMER_MUTE                              = 0x00E2,
  HID_USAGE_CONSUMER_BASS                              = 0x00E3,
  HID_USAGE_CONSUMER_TREBLE                            = 0x00E4,
  HID_USAGE_CONSUMER_BASS_BOOST                        = 0x00E5,
  HID_USAGE_CONSUMER_VOLUME_INCREMENT                  = 0x00E9,
  HID_USAGE_CONSUMER_VOLUME_DECREMENT                  = 0x00EA,
  HID_USAGE_CONSUMER_BASS_INCREMENT                    = 0x0152,
  HID_USAGE_CONSUMER_BASS_DECREMENT                    = 0x0153,
  HID_USAGE_CONSUMER_TREBLE_INCREMENT                  = 0x0154,
  HID_USAGE_CONSUMER_TREBLE_DECREMENT                  = 0x0155,

  // 应用程序启动器
  HID_USAGE_CONSUMER_AL_CONSUMER_CONTROL_CONFIGURATION = 0x0183,
  HID_USAGE_CONSUMER_AL_EMAIL_READER                   = 0x018A,
  HID_USAGE_CONSUMER_AL_CALCULATOR                     = 0x0192,
  HID_USAGE_CONSUMER_AL_LOCAL_BROWSER                  = 0x0194,

  // 浏览器/浏览器特定
  HID_USAGE_CONSUMER_AC_SEARCH                         = 0x0221,
  HID_USAGE_CONSUMER_AC_HOME                           = 0x0223,
  HID_USAGE_CONSUMER_AC_BACK                           = 0x0224,
  HID_USAGE_CONSUMER_AC_FORWARD                        = 0x0225,
  HID_USAGE_CONSUMER_AC_STOP                           = 0x0226,
  HID_USAGE_CONSUMER_AC_REFRESH                        = 0x0227,
  HID_USAGE_CONSUMER_AC_BOOKMARKS                      = 0x022A,

  // 鼠标水平滚动
  HID_USAGE_CONSUMER_AC_PAN                            = 0x0238,
};

/*--------------------------------------------------------------------
 * ASCII到KEYCODE的转换扩展到[128][2]的数组（shift，KEYCODE）
 *
 * 用法：将输入chr转换为键盘报告的示例（修饰符+keycode）
 *
 *  uint8_t常量conv_table[128][2]=｛HID_ASCII_TO_KEYCODE｝；
 *
 *  uint8_t键码[6]=｛0｝；uint8_t修饰符=0；
 *
 *  如果（conv_table[chr][0]）修饰符=KEYBOARD_modifier_LEFTSHIFT；键码[0]=conv_table[chr][1]；tud_hid_keyboard_report（report_id，修饰符，键码）；
 *
 *--------------------------------------------------------------------*/
#define HID_ASCII_TO_KEYCODE \
    {0, 0                     }, /* 0x00空*/ \
    {0, 0                     }, /* 0x01*/ \
    {0, 0                     }, /* 0x02*/ \
    {0, 0                     }, /* 0x03*/ \
    {0, 0                     }, /* 0x04*/ \
    {0, 0                     }, /* 0x05*/ \
    {0, 0                     }, /* 0x06*/ \
    {0, 0                     }, /* 0x07*/ \
    {0, HID_KEY_BACKSPACE     }, /* 0x08退格*/ \
    {0, HID_KEY_TAB           }, /* 0x09选项卡*/ \
    {0, HID_KEY_RETURN        }, /* 0x0A换行*/ \
    {0, 0                     }, /* 0x0B*/ \
    {0, 0                     }, /* 0x0C*/ \
    {0, HID_KEY_RETURN        }, /* 0x0D CR*/ \
    {0, 0                     }, /* 0x0E*/ \
    {0, 0                     }, /* 0x0F格式*/ \
    {0, 0                     }, /* 0x10像素*/ \
    {0, 0                     }, /* 0x11像素*/ \
    {0, 0                     }, /* 0x12像素*/ \
    {0, 0                     }, /* 0x13像素*/ \
    {0, 0                     }, /* 0x14像素*/ \
    {0, 0                     }, /* 0x15像素*/ \
    {0, 0                     }, /* 0x16像素*/ \
    {0, 0                     }, /* 0x17像素*/ \
    {0, 0                     }, /* 0x18像素*/ \
    {0, 0                     }, /* 0x19像素*/ \
    {0, 0                     }, /* 0x1安培*/ \
    {0, HID_KEY_ESCAPE        }, /* 0x1B逃生*/ \
    {0, 0                     }, /* 0摄氏度*/ \
    {0, 0                     }, /* 0x1D像素*/ \
    {0, 0                     }, /* 0x1E像素*/ \
    {0, 0                     }, /* 0x1华氏度*/ \
                                                      \
    {0, HID_KEY_SPACE         }, /* 20倍*/ \
    {1, HID_KEY_1             }, /* 0x21！*/ \
    {1, HID_KEY_APOSTROPHE    }, /* 0x22英寸*/ \
    {1, HID_KEY_3             }, /* 0x23号*/ \
    {1, HID_KEY_4             }, /* 0x24美元*/ \
    {1, HID_KEY_5             }, /* 0x25%*/ \
    {1, HID_KEY_7             }, /* 0x26和*/ \
    {0, HID_KEY_APOSTROPHE    }, /* 0x27英寸*/ \
    {1, HID_KEY_9             }, /* 0x28（*/ \
    {1, HID_KEY_0             }, /* 0x29）*/ \
    {1, HID_KEY_8             }, /* 0x2A**/ \
    {1, HID_KEY_EQUAL         }, /* 0x2B以上*/ \
    {0, HID_KEY_COMMA         }, /* 0x2C，*/ \
    {0, HID_KEY_MINUS         }, /* 0x2D-*/ \
    {0, HID_KEY_PERIOD        }, /* 0x2E。*/ \
    {0, HID_KEY_SLASH         }, /* 0x2F/*/ \
    {0, HID_KEY_0             }, /* 0x30 0*/ \
    {0, HID_KEY_1             }, /* 0x31 1*/ \
    {0, HID_KEY_2             }, /* 0x32 2*/ \
    {0, HID_KEY_3             }, /* 0x33 3*/ \
    {0, HID_KEY_4             }, /* 0x34 4*/ \
    {0, HID_KEY_5             }, /* 0x35 5*/ \
    {0, HID_KEY_6             }, /* 0x36 6*/ \
    {0, HID_KEY_7             }, /* 0x37 7*/ \
    {0, HID_KEY_8             }, /* 0x38 8*/ \
    {0, HID_KEY_9             }, /* 0x39 9*/ \
    {1, HID_KEY_SEMICOLON     }, /* 0x3A：*/ \
    {0, HID_KEY_SEMICOLON     }, /* 0x3B；*/ \
    {1, HID_KEY_COMMA         }, /* 0x3C<*/ \
    {0, HID_KEY_EQUAL         }, /* 0x3D=*/ \
    {1, HID_KEY_PERIOD        }, /* 0x3E>*/ \
    {1, HID_KEY_SLASH         }, /* 0x3F？*/ \
                                                      \
    {1, HID_KEY_2             }, /* 0x40英寸*/ \
    {1, HID_KEY_A             }, /* 0x41安*/ \
    {1, HID_KEY_B             }, /* 0x42字节*/ \
    {1, HID_KEY_C             }, /* 0x43摄氏度*/ \
    {1, HID_KEY_D             }, /* 0x44直径*/ \
    {1, HID_KEY_E             }, /* 0x45东经*/ \
    {1, HID_KEY_F             }, /* 0x46华氏度*/ \
    {1, HID_KEY_G             }, /* 0x47克*/ \
    {1, HID_KEY_H             }, /* 0x48高*/ \
    {1, HID_KEY_I             }, /* 0x49英寸*/ \
    {1, HID_KEY_J             }, /* 0x4A英寸*/ \
    {1, HID_KEY_K             }, /* 0x4B千*/ \
    {1, HID_KEY_L             }, /* 0x4C升*/ \
    {1, HID_KEY_M             }, /* 0x4D米*/ \
    {1, HID_KEY_N             }, /* 0x4E北*/ \
    {1, HID_KEY_O             }, /* 0x4F开*/ \
    {1, HID_KEY_P             }, /* 0x50像素*/ \
    {1, HID_KEY_Q             }, /* 0x51Ω*/ \
    {1, HID_KEY_R             }, /* 0x52右*/ \
    {1, HID_KEY_S             }, /* 0x53秒*/ \
    {1, HID_KEY_T             }, /* 0x55吨*/ \
    {1, HID_KEY_U             }, /* 0x55单位*/ \
    {1, HID_KEY_V             }, /* 0x56伏*/ \
    {1, HID_KEY_W             }, /* 0x57瓦*/ \
    {1, HID_KEY_X             }, /* 0x58倍*/ \
    {1, HID_KEY_Y             }, /* 0x59是*/ \
    {1, HID_KEY_Z             }, /* 0x5A Z*/ \
    {0, HID_KEY_BRACKET_LEFT  }, /* 0x5B[*/ \
    {0, HID_KEY_BACKSLASH     }, /* 0x5C“\”*/ \
    {0, HID_KEY_BRACKET_RIGHT }, /* 0x5D]*/ \
    {1, HID_KEY_6             }, /* 0x5E^*/ \
    {1, HID_KEY_MINUS         }, /* 0x5F*/ \
                                                      \
    {0, HID_KEY_GRAVE         }, /* 0x60`*/ \
    {0, HID_KEY_A             }, /* 0x61个*/ \
    {0, HID_KEY_B             }, /* 0x62字节*/ \
    {0, HID_KEY_C             }, /* 0x63厘米*/ \
    {0, HID_KEY_D             }, /* 0x66天*/ \
    {0, HID_KEY_E             }, /* 0x65英寸*/ \
    {0, HID_KEY_F             }, /* 0x66英尺*/ \
    {0, HID_KEY_G             }, /* 0x67克*/ \
    {0, HID_KEY_H             }, /* 0x68小时*/ \
    {0, HID_KEY_I             }, /* 0x69英寸*/ \
    {0, HID_KEY_J             }, /* 0x6A英寸*/ \
    {0, HID_KEY_K             }, /* 0x6B千*/ \
    {0, HID_KEY_L             }, /* 0x6C升*/ \
    {0, HID_KEY_M             }, /* 0x6D米*/ \
    {0, HID_KEY_N             }, /* 0x6E n*/ \
    {0, HID_KEY_O             }, /* 0x6F开*/ \
    {0, HID_KEY_P             }, /* 0x70像素*/ \
    {0, HID_KEY_Q             }, /* 0x71倍*/ \
    {0, HID_KEY_R             }, /* 0x72秒*/ \
    {0, HID_KEY_S             }, /* 0x73秒*/ \
    {0, HID_KEY_T             }, /* 0x75吨*/ \
    {0, HID_KEY_U             }, /* 0x75单位*/ \
    {0, HID_KEY_V             }, /* 0x76伏*/ \
    {0, HID_KEY_W             }, /* 0x77瓦*/ \
    {0, HID_KEY_X             }, /* 0x78倍*/ \
    {0, HID_KEY_Y             }, /* 0x79年*/ \
    {0, HID_KEY_Z             }, /* 0x7A赫兹*/ \
    {1, HID_KEY_BRACKET_LEFT  }, /* 0x7B｛*/ \
    {1, HID_KEY_BACKSLASH     }, /* 0x7C |*/ \
    {1, HID_KEY_BRACKET_RIGHT }, /* 0x7D｝*/ \
    {1, HID_KEY_GRAVE         }, /* 0x7E~*/ \
    {0, HID_KEY_DELETE        }  /* 0x7F删除*/ \

/*--------------------------------------------------------------------
 * KEYCODE到Ascii的转换扩展到[128][2]的数组（Ascii不带移位，Ascii带移位）
 *
 * 用法：从keycode（key）和shift修饰符（shift）转换ascii的示例。这里我们假设键<128（可打印）
 *
 *  uint8_t常量conv_table[128][2]=｛HID_KEYCODE_TO_ASCII｝；char-ch=移位？conv_table[chr][1]：conv_table[chr][0]；
 *
 *--------------------------------------------------------------------*/
#define HID_KEYCODE_TO_ASCII    \
    {0     , 0      }, /* 0x00位*/ \
    {0     , 0      }, /* 0x01*/ \
    {0     , 0      }, /* 0x02*/ \
    {0     , 0      }, /* 0x03*/ \
    {'a'   , 'A'    }, /* 0x04*/ \
    {'b'   , 'B'    }, /* 0x05*/ \
    {'c'   , 'C'    }, /* 0x06*/ \
    {'d'   , 'D'    }, /* 0x07*/ \
    {'e'   , 'E'    }, /* 0x08*/ \
    {'f'   , 'F'    }, /* 0x09*/ \
    {'g'   , 'G'    }, /* 0x0a*/ \
    {'h'   , 'H'    }, /* 0x0b*/ \
    {'i'   , 'I'    }, /* 0x0c*/ \
    {'j'   , 'J'    }, /* 0x0d（0x0d）*/ \
    {'k'   , 'K'    }, /* 0x0e*/ \
    {'l'   , 'L'    }, /* 0x0f*/ \
    {'m'   , 'M'    }, /* 0x10像素*/ \
    {'n'   , 'N'    }, /* 0x11像素*/ \
    {'o'   , 'O'    }, /* 0x12像素*/ \
    {'p'   , 'P'    }, /* 0x13像素*/ \
    {'q'   , 'Q'    }, /* 0x14像素*/ \
    {'r'   , 'R'    }, /* 0x15像素*/ \
    {'s'   , 'S'    }, /* 0x16像素*/ \
    {'t'   , 'T'    }, /* 0x17像素*/ \
    {'u'   , 'U'    }, /* 0x18像素*/ \
    {'v'   , 'V'    }, /* 0x19像素*/ \
    {'w'   , 'W'    }, /* 0x1英寸*/ \
    {'x'   , 'X'    }, /* 0x1b像素*/ \
    {'y'   , 'Y'    }, /* 0x1c像素*/ \
    {'z'   , 'Z'    }, /* 0x1天*/ \
    {'1'   , '!'    }, /* 0x1倍*/ \
    {'2'   , '@'    }, /* 0x1英尺*/ \
    {'3'   , '#'    }, /* 20倍*/ \
    {'4'   , '$'    }, /* 0时21分*/ \
    {'5'   , '%'    }, /* 0时22分*/ \
    {'6'   , '^'    }, /* 0月23日*/ \
    {'7'   , '&'    }, /* 0时24分*/ \
    {'8'   , '*'    }, /* 0x25像素*/ \
    {'9'   , '('    }, /* 0月26日*/ \
    {'0'   , ')'    }, /* 0月27日*/ \
    {'\r'  , '\r'   }, /* 第28位*/ \
    {'\x1b', '\x1b' }, /* 第29页*/ \
    {'\b'  , '\b'   }, /* 0x2a倍*/ \
    {'\t'  , '\t'   }, /* 0x2b倍*/ \
    {' '   , ' '    }, /* 0x2厘米*/ \
    {'-'   , '_'    }, /* 0x2d*/ \
    {'='   , '+'    }, /* 0x2e*/ \
    {'['   , '{'    }, /* 0x2f*/ \
    {']'   , '}'    }, /* 0x30*/ \
    {'\\'  , '|'    }, /* 0x31个*/ \
    {'#'   , '~'    }, /* 0x32个*/ \
    {';'   , ':'    }, /* 0x33个*/ \
    {'\''  , '\"'   }, /* 0x34个*/ \
    {'`'   , '~'    }, /* 0x35个*/ \
    {','   , '<'    }, /* 0x36个*/ \
    {'.'   , '>'    }, /* 0x37个*/ \
    {'/'   , '?'    }, /* 0x38个*/ \
                                  \
    {0     , 0      }, /* 0x39个*/ \
    {0     , 0      }, /* 0x3a*/ \
    {0     , 0      }, /* 0x3b*/ \
    {0     , 0      }, /* 0x3c*/ \
    {0     , 0      }, /* 0x3d*/ \
    {0     , 0      }, /* 0x3倍*/ \
    {0     , 0      }, /* 0x3英尺*/ \
    {0     , 0      }, /* 0x40倍*/ \
    {0     , 0      }, /* 0时41分*/ \
    {0     , 0      }, /* 0秒42*/ \
    {0     , 0      }, /* 第43位*/ \
    {0     , 0      }, /* 第44位*/ \
    {0     , 0      }, /* 0时45分*/ \
    {0     , 0      }, /* 0时46分*/ \
    {0     , 0      }, /* 第47页*/ \
    {0     , 0      }, /* 0x48秒*/ \
    {0     , 0      }, /* 0时49分*/ \
    {0     , 0      }, /* 0x4a*/ \
    {0     , 0      }, /* 0x4b*/ \
    {0     , 0      }, /* 0x4厘米*/ \
    {0     , 0      }, /* 0x4天*/ \
    {0     , 0      }, /* 0x4e*/ \
    {0     , 0      }, /* 0x4英尺*/ \
    {0     , 0      }, /* 50倍*/ \
    {0     , 0      }, /* 0倍51*/ \
    {0     , 0      }, /* 0秒52*/ \
    {0     , 0      }, /* 0秒53*/ \
                                  \
    {'/'   , '/'    }, /* 0时54分*/ \
    {'*'   , '*'    }, /* 0x55倍*/ \
    {'-'   , '-'    }, /* 0时56分*/ \
    {'+'   , '+'    }, /* 第57页*/ \
    {'\r'  , '\r'   }, /* 0x58倍*/ \
    {'1'   , 0      }, /* 第59页*/ \
    {'2'   , 0      }, /* 0x5a级*/ \
    {'3'   , 0      }, /* 0x5b*/ \
    {'4'   , 0      }, /* 0x5c*/ \
    {'5'   , '5'    }, /* 0x5天*/ \
    {'6'   , 0      }, /* 0x5e*/ \
    {'7'   , 0      }, /* 0x5英尺*/ \
    {'8'   , 0      }, /* 0x60倍*/ \
    {'9'   , 0      }, /* 第61位*/ \
    {'0'   , 0      }, /* 0秒62*/ \
    {'0'   , 0      }, /* 第63位*/ \
    {'='   , '='    }, /* 0秒67*/ \


#ifdef __cplusplus
 }
#endif

#endif /* _TUSB_HID_H__ */

/// @}

