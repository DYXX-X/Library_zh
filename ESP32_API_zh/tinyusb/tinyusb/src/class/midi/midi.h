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

/** \inggroup group_class\defgroup ClassDriver_CDC通信设备类（CDC）当前仅支持抽象控制模型子类
 *  @{ */

#ifndef _TUSB_MIDI_H__
#define _TUSB_MIDI_H__

#include "common/tusb_common.h"

#ifdef __cplusplus
 extern "C" {
#endif

//--------------------------------------------------------------------+
// 类特定描述符
//--------------------------------------------------------------------+

typedef enum
{
  MIDI_CS_INTERFACE_HEADER    = 0x01,
  MIDI_CS_INTERFACE_IN_JACK   = 0x02,
  MIDI_CS_INTERFACE_OUT_JACK  = 0x03,
  MIDI_CS_INTERFACE_ELEMENT   = 0x04,
} midi_cs_interface_subtype_t;

typedef enum
{
  MIDI_CS_ENDPOINT_GENERAL = 0x01
} midi_cs_endpoint_subtype_t;

typedef enum
{
  MIDI_JACK_EMBEDDED = 0x01,
  MIDI_JACK_EXTERNAL = 0x02
} midi_jack_type_t;

typedef enum
{
  MIDI_CIN_MISC              = 0,
  MIDI_CIN_CABLE_EVENT       = 1,
  MIDI_CIN_SYSCOM_2BYTE      = 2, // 2字节系统通用消息，如MTC、SongSelect
  MIDI_CIN_SYSCOM_3BYTE      = 3, // 3字节系统通用消息，如SPP
  MIDI_CIN_SYSEX_START       = 4, // SysEx启动或继续
  MIDI_CIN_SYSEX_END_1BYTE   = 5, // SysEx以1个数据或1字节系统公共消息结尾
  MIDI_CIN_SYSEX_END_2BYTE   = 6, // SysEx以2个数据结尾
  MIDI_CIN_SYSEX_END_3BYTE   = 7, // SysEx以3个数据结尾
  MIDI_CIN_NOTE_ON           = 8,
  MIDI_CIN_NOTE_OFF          = 9,
  MIDI_CIN_POLY_KEYPRESS     = 10,
  MIDI_CIN_CONTROL_CHANGE    = 11,
  MIDI_CIN_PROGRAM_CHANGE    = 12,
  MIDI_CIN_CHANNEL_PRESSURE  = 13,
  MIDI_CIN_PITCH_BEND_CHANGE = 14,
  MIDI_CIN_1BYTE_DATA = 15
} midi_code_index_number_t;

// MIDI 1.0状态字节
enum
{
  //-------------系统独占-------------//
  MIDI_STATUS_SYSEX_START                    = 0xF0,
  MIDI_STATUS_SYSEX_END                      = 0xF7,

  //-------------系统公用-------------//
  MIDI_STATUS_SYSCOM_TIME_CODE_QUARTER_FRAME = 0xF1,
  MIDI_STATUS_SYSCOM_SONG_POSITION_POINTER   = 0xF2,
  MIDI_STATUS_SYSCOM_SONG_SELECT             = 0xF3,
  // F4、F5未定义
  MIDI_STATUS_SYSCOM_TUNE_REQUEST            = 0xF6,

  //-------------系统实时-------------//
  MIDI_STATUS_SYSREAL_TIMING_CLOCK           = 0xF8,
  // 0xF9未定义
  MIDI_STATUS_SYSREAL_START                  = 0xFA,
  MIDI_STATUS_SYSREAL_CONTINUE               = 0xFB,
  MIDI_STATUS_SYSREAL_STOP                   = 0xFC,
  // 0xFD未定义
  MIDI_STATUS_SYSREAL_ACTIVE_SENSING         = 0xFE,
  MIDI_STATUS_SYSREAL_SYSTEM_RESET           = 0xFF,
};

///MIDI接口标题描述符
typedef struct TU_ATTR_PACKED
{
  uint8_t bLength            ; ///<此描述符的大小（字节）。
  uint8_t bDescriptorType    ; ///<描述符类型，必须是类特定的
  uint8_t bDescriptorSubType ; ///<描述符子类型
  uint16_t bcdMSC            ; ///＜MidiStream子类发布编号（二进制编码十进制）
  uint16_t wTotalLength      ;
} midi_desc_header_t;

///MIDI插孔描述符
typedef struct TU_ATTR_PACKED
{
  uint8_t bLength            ; ///<此描述符的大小（字节）。
  uint8_t bDescriptorType    ; ///<描述符类型，必须是类特定的
  uint8_t bDescriptorSubType ; ///<描述符子类型
  uint8_t bJackType          ; ///<嵌入式或外部
  uint8_t bJackID            ; ///<MIDI IN插孔的唯一ID
  uint8_t iJack              ; ///<字符串描述符
} midi_desc_in_jack_t;


///带单引脚的MIDI输出插孔描述符
typedef struct TU_ATTR_PACKED
{
  uint8_t bLength            ; ///<此描述符的大小（字节）。
  uint8_t bDescriptorType    ; ///<描述符类型，必须是类特定的
  uint8_t bDescriptorSubType ; ///<描述符子类型
  uint8_t bJackType          ; ///<嵌入式或外部
  uint8_t bJackID            ; ///<MIDI IN插孔的唯一ID
  uint8_t bNrInputPins;

  uint8_t baSourceID;
  uint8_t baSourcePin;

  uint8_t iJack              ; ///<字符串描述符
} midi_desc_out_jack_t ;

///带多个引脚的MIDI输出插孔描述符
#define midi_desc_out_jack_n_t(input_num) \
  struct TU_ATTR_PACKED { \
    uint8_t bLength            ; \
    uint8_t bDescriptorType    ; \
    uint8_t bDescriptorSubType ; \
    uint8_t bJackType          ; \
    uint8_t bJackID            ; \
    uint8_t bNrInputPins       ; \
    struct TU_ATTR_PACKED {      \
        uint8_t baSourceID;      \
        uint8_t baSourcePin;     \
    } pins[input_num];           \
   uint8_t iJack              ;  \
  }

///MIDI元素描述符
typedef struct TU_ATTR_PACKED
{
  uint8_t bLength            ; ///<此描述符的大小（字节）。
  uint8_t bDescriptorType    ; ///<描述符类型，必须是类特定的
  uint8_t bDescriptorSubType ; ///<描述符子类型
  uint8_t bElementID;

  uint8_t bNrInputPins;
  uint8_t baSourceID;
  uint8_t baSourcePin;

  uint8_t bNrOutputPins;
  uint8_t bInTerminalLink;
  uint8_t bOutTerminalLink;
  uint8_t bElCapsSize;

  uint16_t bmElementCaps;
  uint8_t  iElement;
} midi_desc_element_t;

///具有多个管脚的MIDI元素描述符
#define midi_desc_element_n_t(input_num) \
  struct TU_ATTR_PACKED {       \
    uint8_t bLength;            \
    uint8_t bDescriptorType;    \
    uint8_t bDescriptorSubType; \
    uint8_t bElementID;         \
    uint8_t bNrInputPins;       \
    struct TU_ATTR_PACKED {     \
        uint8_t baSourceID;     \
        uint8_t baSourcePin;    \
    } pins[input_num];          \
    uint8_t bNrOutputPins;      \
    uint8_t bInTerminalLink;    \
    uint8_t bOutTerminalLink;   \
    uint8_t bElCapsSize;        \
    uint16_t bmElementCaps;     \
    uint8_t  iElement;          \
 }

/** @} */

#ifdef __cplusplus
 }
#endif

#endif

/** @} */

