/* 
 * MIT许可证（MIT）
 *
 * 版权所有（c）2019 Ha Thach（tinyusb.org）版权所有（c）2020 Reinhard Panhuber
 *
 * 特此免费授予获得本软件和相关文档文件（“软件”）副本的任何人无限制地处理软件的权利，包括但不限于使用、复制、修改、合并、发布、分发、再许可和/或销售软件副本的权利，并允许向其提供软件的人这样做，符合以下条件：
 *
 * 上述版权声明和本许可声明应包含在软件的所有副本或主要部分中。
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * 此文件是TinyUSB堆栈的一部分。
 */

/** \inggroup group_class\defgroup ClassDriver_Audio Audio当前仅支持MIDI子类
 *  @{ */

#ifndef _TUSB_AUDIO_H__
#define _TUSB_AUDIO_H__

#include "common/tusb_common.h"

#ifdef __cplusplus
extern "C" {
#endif

///音频设备类别代码

///A.2-音频功能子类代码
typedef enum
{
  AUDIO_FUNCTION_SUBCLASS_UNDEFINED = 0x00,
} audio_function_subclass_type_t;

///A.3-音频功能协议代码
typedef enum
{
  AUDIO_FUNC_PROTOCOL_CODE_UNDEF       = 0x00,
  AUDIO_FUNC_PROTOCOL_CODE_V2          = 0x20, ///<版本2.0
} audio_function_protocol_code_t;

///A.5-音频接口子类代码
typedef enum
{
  AUDIO_SUBCLASS_UNDEFINED = 0x00,
  AUDIO_SUBCLASS_CONTROL         , ///<音频控制
  AUDIO_SUBCLASS_STREAMING       , ///<音频流
  AUDIO_SUBCLASS_MIDI_STREAMING  , ///<MIDI流媒体
} audio_subclass_type_t;

///A.6-音频接口协议代码
typedef enum
{
  AUDIO_INT_PROTOCOL_CODE_UNDEF       = 0x00,
  AUDIO_INT_PROTOCOL_CODE_V2          = 0x20, ///<版本2.0
} audio_interface_protocol_code_t;

///A.7-音频功能类别代码
typedef enum
{
  AUDIO_FUNC_UNDEF              = 0x00,
  AUDIO_FUNC_DESKTOP_SPEAKER    = 0x01,
  AUDIO_FUNC_HOME_THEATER       = 0x02,
  AUDIO_FUNC_MICROPHONE         = 0x03,
  AUDIO_FUNC_HEADSET            = 0x04,
  AUDIO_FUNC_TELEPHONE          = 0x05,
  AUDIO_FUNC_CONVERTER          = 0x06,
  AUDIO_FUNC_SOUND_RECODER      = 0x07,
  AUDIO_FUNC_IO_BOX             = 0x08,
  AUDIO_FUNC_MUSICAL_INSTRUMENT = 0x09,
  AUDIO_FUNC_PRO_AUDIO          = 0x0A,
  AUDIO_FUNC_AUDIO_VIDEO        = 0x0B,
  AUDIO_FUNC_CONTROL_PANEL      = 0x0C,
  AUDIO_FUNC_OTHER              = 0xFF,
} audio_function_code_t;

///A.9-音频类特定AC接口描述符子类型UAC2
typedef enum
{
  AUDIO_CS_AC_INTERFACE_AC_DESCRIPTOR_UNDEF   = 0x00,
  AUDIO_CS_AC_INTERFACE_HEADER                = 0x01,
  AUDIO_CS_AC_INTERFACE_INPUT_TERMINAL        = 0x02,
  AUDIO_CS_AC_INTERFACE_OUTPUT_TERMINAL       = 0x03,
  AUDIO_CS_AC_INTERFACE_MIXER_UNIT            = 0x04,
  AUDIO_CS_AC_INTERFACE_SELECTOR_UNIT         = 0x05,
  AUDIO_CS_AC_INTERFACE_FEATURE_UNIT          = 0x06,
  AUDIO_CS_AC_INTERFACE_EFFECT_UNIT           = 0x07,
  AUDIO_CS_AC_INTERFACE_PROCESSING_UNIT       = 0x08,
  AUDIO_CS_AC_INTERFACE_EXTENSION_UNIT        = 0x09,
  AUDIO_CS_AC_INTERFACE_CLOCK_SOURCE          = 0x0A,
  AUDIO_CS_AC_INTERFACE_CLOCK_SELECTOR        = 0x0B,
  AUDIO_CS_AC_INTERFACE_CLOCK_MULTIPLIER      = 0x0C,
  AUDIO_CS_AC_INTERFACE_SAMPLE_RATE_CONVERTER = 0x0D,
} audio_cs_ac_interface_subtype_t;

///A.10-音频类特定AS接口描述符子类型UAC2
typedef enum
{
  AUDIO_CS_AS_INTERFACE_AS_DESCRIPTOR_UNDEF   = 0x00,
  AUDIO_CS_AS_INTERFACE_AS_GENERAL            = 0x01,
  AUDIO_CS_AS_INTERFACE_FORMAT_TYPE           = 0x02,
  AUDIO_CS_AS_INTERFACE_ENCODER               = 0x03,
  AUDIO_CS_AS_INTERFACE_DECODER               = 0x04,
} audio_cs_as_interface_subtype_t;

///A.11-效果单元效果类型
typedef enum
{
  AUDIO_EFFECT_TYPE_UNDEF                     = 0x00,
  AUDIO_EFFECT_TYPE_PARAM_EQ_SECTION          = 0x01,
  AUDIO_EFFECT_TYPE_REVERBERATION             = 0x02,
  AUDIO_EFFECT_TYPE_MOD_DELAY                 = 0x03,
  AUDIO_EFFECT_TYPE_DYN_RANGE_COMP            = 0x04,
} audio_effect_unit_effect_type_t;

///A.12-处理单元工艺类型
typedef enum
{
  AUDIO_PROCESS_TYPE_UNDEF                    = 0x00,
  AUDIO_PROCESS_TYPE_UP_DOWN_MIX              = 0x01,
  AUDIO_PROCESS_TYPE_DOLBY_PROLOGIC           = 0x02,
  AUDIO_PROCESS_TYPE_STEREO_EXTENDER          = 0x03,
} audio_processing_unit_process_type_t;

///A.13-音频类特定EP描述符子类型UAC2
typedef enum
{
  AUDIO_CS_EP_SUBTYPE_UNDEF                   = 0x00,
  AUDIO_CS_EP_SUBTYPE_GENERAL                 = 0x01,
} audio_cs_ep_subtype_t;

///A.14-音频类别特定请求代码
typedef enum
{
  AUDIO_CS_REQ_UNDEF                          = 0x00,
  AUDIO_CS_REQ_CUR                            = 0x01,
  AUDIO_CS_REQ_RANGE                          = 0x02,
  AUDIO_CS_REQ_MEM                            = 0x03,
} audio_cs_req_t;

///A.17-控制选择器代码

///A.17.1-时钟源控制选择器
typedef enum
{
  AUDIO_CS_CTRL_UNDEF                         = 0x00,
  AUDIO_CS_CTRL_SAM_FREQ                      = 0x01,
  AUDIO_CS_CTRL_CLK_VALID                     = 0x02,
} audio_clock_src_control_selector_t;

///A.17.2-时钟选择器控制选择器
typedef enum
{
  AUDIO_CX_CTRL_UNDEF                         = 0x00,
  AUDIO_CX_CTRL_CONTROL                       = 0x01,
} audio_clock_sel_control_selector_t;

///A.17.3-时钟乘法器控制选择器
typedef enum
{
  AUDIO_CM_CTRL_UNDEF                         = 0x00,
  AUDIO_CM_CTRL_NUMERATOR_CONTROL             = 0x01,
  AUDIO_CM_CTRL_DENOMINATOR_CONTROL           = 0x02,
} audio_clock_mul_control_selector_t;

///A.17.4-终端控制选择器
typedef enum
{
  AUDIO_TE_CTRL_UNDEF                         = 0x00,
  AUDIO_TE_CTRL_COPY_PROTECT                  = 0x01,
  AUDIO_TE_CTRL_CONNECTOR                     = 0x02,
  AUDIO_TE_CTRL_OVERLOAD                      = 0x03,
  AUDIO_TE_CTRL_CLUSTER                       = 0x04,
  AUDIO_TE_CTRL_UNDERFLOW                     = 0x05,
  AUDIO_TE_CTRL_OVERFLOW                      = 0x06,
  AUDIO_TE_CTRL_LATENCY                       = 0x07,
} audio_terminal_control_selector_t;

///A.17.5-混合器控制选择器
typedef enum
{
  AUDIO_MU_CTRL_UNDEF                         = 0x00,
  AUDIO_MU_CTRL_MIXER                         = 0x01,
  AUDIO_MU_CTRL_CLUSTER                       = 0x02,
  AUDIO_MU_CTRL_UNDERFLOW                     = 0x03,
  AUDIO_MU_CTRL_OVERFLOW                      = 0x04,
  AUDIO_MU_CTRL_LATENCY                       = 0x05,
} audio_mixer_control_selector_t;

///A.17.6-选择器控制选择器
typedef enum
{
  AUDIO_SU_CTRL_UNDEF                         = 0x00,
  AUDIO_SU_CTRL_SELECTOR                      = 0x01,
  AUDIO_SU_CTRL_LATENCY                       = 0x02,
} audio_sel_control_selector_t;

///A.17.7-功能单元控制选择器
typedef enum
{
  AUDIO_FU_CTRL_UNDEF                         = 0x00,
  AUDIO_FU_CTRL_MUTE                          = 0x01,
  AUDIO_FU_CTRL_VOLUME                        = 0x02,
  AUDIO_FU_CTRL_BASS                          = 0x03,
  AUDIO_FU_CTRL_MID                           = 0x04,
  AUDIO_FU_CTRL_TREBLE                        = 0x05,
  AUDIO_FU_CTRL_GRAPHIC_EQUALIZER             = 0x06,
  AUDIO_FU_CTRL_AGC                           = 0x07,
  AUDIO_FU_CTRL_DELAY                         = 0x08,
  AUDIO_FU_CTRL_BASS_BOOST                    = 0x09,
  AUDIO_FU_CTRL_LOUDNESS                      = 0x0A,
  AUDIO_FU_CTRL_INPUT_GAIN                    = 0x0B,
  AUDIO_FU_CTRL_GAIN_PAD                      = 0x0C,
  AUDIO_FU_CTRL_INVERTER                      = 0x0D,
  AUDIO_FU_CTRL_UNDERFLOW                     = 0x0E,
  AUDIO_FU_CTRL_OVERVLOW                      = 0x0F,
  AUDIO_FU_CTRL_LATENCY                       = 0x10,
} audio_feature_unit_control_selector_t;

///A.17.8效果单元控制选择器

///A.17.8.1参数均衡器截面效应单元控制选择器
typedef enum
{
  AUDIO_PE_CTRL_UNDEF                         = 0x00,
  AUDIO_PE_CTRL_ENABLE                        = 0x01,
  AUDIO_PE_CTRL_CENTERFREQ                    = 0x02,
  AUDIO_PE_CTRL_QFACTOR                       = 0x03,
  AUDIO_PE_CTRL_GAIN                          = 0x04,
  AUDIO_PE_CTRL_UNDERFLOW                     = 0x05,
  AUDIO_PE_CTRL_OVERFLOW                      = 0x06,
  AUDIO_PE_CTRL_LATENCY                       = 0x07,
} audio_parametric_equalizer_control_selector_t;

///A.17.8.2混响效果单元控制选择器
typedef enum
{
  AUDIO_RV_CTRL_UNDEF                         = 0x00,
  AUDIO_RV_CTRL_ENABLE                        = 0x01,
  AUDIO_RV_CTRL_TYPE                          = 0x02,
  AUDIO_RV_CTRL_LEVEL                         = 0x03,
  AUDIO_RV_CTRL_TIME                          = 0x04,
  AUDIO_RV_CTRL_FEEDBACK                      = 0x05,
  AUDIO_RV_CTRL_PREDELAY                      = 0x06,
  AUDIO_RV_CTRL_DENSITY                       = 0x07,
  AUDIO_RV_CTRL_HIFREQ_ROLLOFF                = 0x08,
  AUDIO_RV_CTRL_UNDERFLOW                     = 0x09,
  AUDIO_RV_CTRL_OVERFLOW                      = 0x0A,
  AUDIO_RV_CTRL_LATENCY                       = 0x0B,
} audio_reverberation_effect_control_selector_t;

///A.17.8.3调制延迟效应单元控制选择器
typedef enum
{
  AUDIO_MD_CTRL_UNDEF                         = 0x00,
  AUDIO_MD_CTRL_ENABLE                        = 0x01,
  AUDIO_MD_CTRL_BALANCE                       = 0x02,
  AUDIO_MD_CTRL_RATE                          = 0x03,
  AUDIO_MD_CTRL_DEPTH                         = 0x04,
  AUDIO_MD_CTRL_TIME                          = 0x05,
  AUDIO_MD_CTRL_FEEDBACK                      = 0x06,
  AUDIO_MD_CTRL_UNDERFLOW                     = 0x07,
  AUDIO_MD_CTRL_OVERFLOW                      = 0x08,
  AUDIO_MD_CTRL_LATENCY                       = 0x09,
} audio_modulation_delay_control_selector_t;

///A.17.8.4动态范围压缩机效果单元控制选择器
typedef enum
{
  AUDIO_DR_CTRL_UNDEF                         = 0x00,
  AUDIO_DR_CTRL_ENABLE                        = 0x01,
  AUDIO_DR_CTRL_COMPRESSION_RATE              = 0x02,
  AUDIO_DR_CTRL_MAXAMPL                       = 0x03,
  AUDIO_DR_CTRL_THRESHOLD                     = 0x04,
  AUDIO_DR_CTRL_ATTACK_TIME                   = 0x05,
  AUDIO_DR_CTRL_RELEASE_TIME                  = 0x06,
  AUDIO_DR_CTRL_UNDERFLOW                     = 0x07,
  AUDIO_DR_CTRL_OVERFLOW                      = 0x08,
  AUDIO_DR_CTRL_LATENCY                       = 0x09,
} audio_dynamic_range_compression_control_selector_t;

///A.17.9处理单元控制选择器

///A.17.9.1上/下混合处理单元控制选择器
typedef enum
{
  AUDIO_UD_CTRL_UNDEF                         = 0x00,
  AUDIO_UD_CTRL_ENABLE                        = 0x01,
  AUDIO_UD_CTRL_MODE_SELECT                   = 0x02,
  AUDIO_UD_CTRL_CLUSTER                       = 0x03,
  AUDIO_UD_CTRL_UNDERFLOW                     = 0x04,
  AUDIO_UD_CTRL_OVERFLOW                      = 0x05,
  AUDIO_UD_CTRL_LATENCY                       = 0x06,
} audio_up_down_mix_control_selector_t;

///A.17.9.2杜比Prologic™ 处理单元控制选择器
typedef enum
{
  AUDIO_DP_CTRL_UNDEF                         = 0x00,
  AUDIO_DP_CTRL_ENABLE                        = 0x01,
  AUDIO_DP_CTRL_MODE_SELECT                   = 0x02,
  AUDIO_DP_CTRL_CLUSTER                       = 0x03,
  AUDIO_DP_CTRL_UNDERFLOW                     = 0x04,
  AUDIO_DP_CTRL_OVERFLOW                      = 0x05,
  AUDIO_DP_CTRL_LATENCY                       = 0x06,
} audio_dolby_prologic_control_selector_t;

///A.17.9.3立体声扩展器处理单元控制选择器
typedef enum
{
  AUDIO_ST_EXT_CTRL_UNDEF                     = 0x00,
  AUDIO_ST_EXT_CTRL_ENABLE                    = 0x01,
  AUDIO_ST_EXT_CTRL_WIDTH                     = 0x02,
  AUDIO_ST_EXT_CTRL_UNDERFLOW                 = 0x03,
  AUDIO_ST_EXT_CTRL_OVERFLOW                  = 0x04,
  AUDIO_ST_EXT_CTRL_LATENCY                   = 0x05,
} audio_stereo_extender_control_selector_t;

///A.17.10扩展单元控制选择器
typedef enum
{
  AUDIO_XU_CTRL_UNDEF                         = 0x00,
  AUDIO_XU_CTRL_ENABLE                        = 0x01,
  AUDIO_XU_CTRL_CLUSTER                       = 0x02,
  AUDIO_XU_CTRL_UNDERFLOW                     = 0x03,
  AUDIO_XU_CTRL_OVERFLOW                      = 0x04,
  AUDIO_XU_CTRL_LATENCY                       = 0x05,
} audio_extension_unit_control_selector_t;

///A.17.11音频流接口控制选择器
typedef enum
{
  AUDIO_AS_CTRL_UNDEF                         = 0x00,
  AUDIO_AS_CTRL_ACT_ALT_SETTING               = 0x01,
  AUDIO_AS_CTRL_VAL_ALT_SETTINGS              = 0x02,
  AUDIO_AS_CTRL_AUDIO_DATA_FORMAT             = 0x03,
} audio_audiostreaming_interface_control_selector_t;

///A.17.12编码器控制选择器
typedef enum
{
  AUDIO_EN_CTRL_UNDEF                         = 0x00,
  AUDIO_EN_CTRL_BIT_RATE                      = 0x01,
  AUDIO_EN_CTRL_QUALITY                       = 0x02,
  AUDIO_EN_CTRL_VBR                           = 0x03,
  AUDIO_EN_CTRL_TYPE                          = 0x04,
  AUDIO_EN_CTRL_UNDERFLOW                     = 0x05,
  AUDIO_EN_CTRL_OVERFLOW                      = 0x06,
  AUDIO_EN_CTRL_ENCODER_ERROR                 = 0x07,
  AUDIO_EN_CTRL_PARAM1                        = 0x08,
  AUDIO_EN_CTRL_PARAM2                        = 0x09,
  AUDIO_EN_CTRL_PARAM3                        = 0x0A,
  AUDIO_EN_CTRL_PARAM4                        = 0x0B,
  AUDIO_EN_CTRL_PARAM5                        = 0x0C,
  AUDIO_EN_CTRL_PARAM6                        = 0x0D,
  AUDIO_EN_CTRL_PARAM7                        = 0x0E,
  AUDIO_EN_CTRL_PARAM8                        = 0x0F,
} audio_encoder_control_selector_t;

///A.17.13解码器控制选择器

///A.17.13.1 MPEG解码器控制选择器
typedef enum
{
  AUDIO_MPD_CTRL_UNDEF                        = 0x00,
  AUDIO_MPD_CTRL_DUAL_CHANNEL                 = 0x01,
  AUDIO_MPD_CTRL_SECOND_STEREO                = 0x02,
  AUDIO_MPD_CTRL_MULTILINGUAL                 = 0x03,
  AUDIO_MPD_CTRL_DYN_RANGE                    = 0x04,
  AUDIO_MPD_CTRL_SCALING                      = 0x05,
  AUDIO_MPD_CTRL_HILO_SCALING                 = 0x06,
  AUDIO_MPD_CTRL_UNDERFLOW                    = 0x07,
  AUDIO_MPD_CTRL_OVERFLOW                     = 0x08,
  AUDIO_MPD_CTRL_DECODER_ERROR                = 0x09,
} audio_MPEG_decoder_control_selector_t;

///A.17.13.2 AC-3解码器控制选择器
typedef enum
{
  AUDIO_AD_CTRL_UNDEF                         = 0x00,
  AUDIO_AD_CTRL_MODE                          = 0x01,
  AUDIO_AD_CTRL_DYN_RANGE                     = 0x02,
  AUDIO_AD_CTRL_SCALING                       = 0x03,
  AUDIO_AD_CTRL_HILO_SCALING                  = 0x04,
  AUDIO_AD_CTRL_UNDERFLOW                     = 0x05,
  AUDIO_AD_CTRL_OVERFLOW                      = 0x06,
  AUDIO_AD_CTRL_DECODER_ERROR                 = 0x07,
} audio_AC3_decoder_control_selector_t;

///A.17.13.3 WMA解码器控制选择器
typedef enum
{
  AUDIO_WD_CTRL_UNDEF                         = 0x00,
  AUDIO_WD_CTRL_UNDERFLOW                     = 0x01,
  AUDIO_WD_CTRL_OVERFLOW                      = 0x02,
  AUDIO_WD_CTRL_DECODER_ERROR                 = 0x03,
} audio_WMA_decoder_control_selector_t;

///A.17.13.4 DTS解码器控制选择器
typedef enum
{
  AUDIO_DD_CTRL_UNDEF                         = 0x00,
  AUDIO_DD_CTRL_UNDERFLOW                     = 0x01,
  AUDIO_DD_CTRL_OVERFLOW                      = 0x02,
  AUDIO_DD_CTRL_DECODER_ERROR                 = 0x03,
} audio_DTS_decoder_control_selector_t;

///A.17.14端点控制选择器
typedef enum
{
  AUDIO_EP_CTRL_UNDEF                         = 0x00,
  AUDIO_EP_CTRL_PITCH                         = 0x01,
  AUDIO_EP_CTRL_DATA_OVERRUN                  = 0x02,
  AUDIO_EP_CTRL_DATA_UNDERRUN                 = 0x03,
} audio_EP_control_selector_t;

///端子类型

///2.1-音频类终端类型UAC2
typedef enum
{
  AUDIO_TERM_TYPE_USB_UNDEFINED       = 0x0100,
  AUDIO_TERM_TYPE_USB_STREAMING       = 0x0101,
  AUDIO_TERM_TYPE_USB_VENDOR_SPEC     = 0x01FF,
} audio_terminal_type_t;

///2.2-音频类输入端子类型UAC2
typedef enum
{
  AUDIO_TERM_TYPE_IN_UNDEFINED        = 0x0200,
  AUDIO_TERM_TYPE_IN_GENERIC_MIC      = 0x0201,
  AUDIO_TERM_TYPE_IN_DESKTOP_MIC      = 0x0202,
  AUDIO_TERM_TYPE_IN_PERSONAL_MIC     = 0x0203,
  AUDIO_TERM_TYPE_IN_OMNI_MIC         = 0x0204,
  AUDIO_TERM_TYPE_IN_ARRAY_MIC        = 0x0205,
  AUDIO_TERM_TYPE_IN_PROC_ARRAY_MIC   = 0x0206,
} audio_terminal_input_type_t;

///2.3-音频类输出端子类型UAC2
typedef enum
{
  AUDIO_TERM_TYPE_OUT_UNDEFINED               = 0x0300,
  AUDIO_TERM_TYPE_OUT_GENERIC_SPEAKER         = 0x0301,
  AUDIO_TERM_TYPE_OUT_HEADPHONES              = 0x0302,
  AUDIO_TERM_TYPE_OUT_HEAD_MNT_DISP_AUIDO     = 0x0303,
  AUDIO_TERM_TYPE_OUT_DESKTOP_SPEAKER         = 0x0304,
  AUDIO_TERM_TYPE_OUT_ROOM_SPEAKER            = 0x0305,
  AUDIO_TERM_TYPE_OUT_COMMUNICATION_SPEAKER   = 0x0306,
  AUDIO_TERM_TYPE_OUT_LOW_FRQ_EFFECTS_SPEAKER = 0x0307,
} audio_terminal_output_type_t;

///其余尚未实施

///其他音频设备类别代码-源：音频数据格式

///A.1-音频类格式类型代码UAC2
typedef enum
{
  AUDIO_FORMAT_TYPE_UNDEFINED     = 0x00,
  AUDIO_FORMAT_TYPE_I             = 0x01,
  AUDIO_FORMAT_TYPE_II            = 0x02,
  AUDIO_FORMAT_TYPE_III           = 0x03,
  AUDIO_FORMAT_TYPE_IV            = 0x04,
  AUDIO_EXT_FORMAT_TYPE_I         = 0x81,
  AUDIO_EXT_FORMAT_TYPE_II        = 0x82,
  AUDIO_EXT_FORMAT_TYPE_III       = 0x83,
} audio_format_type_t;

// A、 2.1-音频类音频数据格式类型I UAC2
typedef enum
{
  AUDIO_DATA_FORMAT_TYPE_I_PCM            = (uint32_t) (1 << 0),
  AUDIO_DATA_FORMAT_TYPE_I_PCM8           = (uint32_t) (1 << 1),
  AUDIO_DATA_FORMAT_TYPE_I_IEEE_FLOAT     = (uint32_t) (1 << 2),
  AUDIO_DATA_FORMAT_TYPE_I_ALAW           = (uint32_t) (1 << 3),
  AUDIO_DATA_FORMAT_TYPE_I_MULAW          = (uint32_t) (1 << 4),
  AUDIO_DATA_FORMAT_TYPE_I_RAW_DATA       = 0x100000000,
} audio_data_format_type_I_t;

///所有剩余的定义均取自UAC2主规范中的描述符描述

///等时端点属性
typedef enum
{
  TUSB_ISO_EP_ATT_NO_SYNC         = 0x00,
  TUSB_ISO_EP_ATT_ASYNCHRONOUS    = 0x04,
  TUSB_ISO_EP_ATT_ADAPTIVE        = 0x08,
  TUSB_ISO_EP_ATT_SYNCHRONOUS     = 0x0C,
  TUSB_ISO_EP_ATT_DATA            = 0x00, ///<数据端点
  TUSB_ISO_EP_ATT_EXPLICIT_FB     = 0x10, ///<反馈终点
  TUSB_ISO_EP_ATT_IMPLICIT_FB     = 0x20, ///<同时用作隐式反馈的数据端点
} tusb_iso_ep_attribute_t;

///音频等级控制值UAC2
typedef enum
{
  AUDIO_CTRL_NONE     = 0x00,         ///<无主机访问
  AUDIO_CTRL_R        = 0x01,         ///<主机只读访问
  AUDIO_CTRL_RW       = 0x03,         ///<主机读写访问
} audio_control_t;

///音频类特定AC接口描述符控件UAC2
typedef enum
{
  AUDIO_CS_AS_INTERFACE_CTRL_LATENCY_POS  = 0,
} audio_cs_ac_interface_control_pos_t;

///音频类特定AS接口描述符控制UAC2
typedef enum
{
  AUDIO_CS_AS_INTERFACE_CTRL_ACTIVE_ALT_SET_POS   = 0,
  AUDIO_CS_AS_INTERFACE_CTRL_VALID_ALT_SET_POS    = 2,
} audio_cs_as_interface_control_pos_t;

///音频类特定AS等时数据EP属性UAC2
typedef enum
{
  AUDIO_CS_AS_ISO_DATA_EP_ATT_MAX_PACKETS_ONLY    = 0x80,
  AUDIO_CS_AS_ISO_DATA_EP_ATT_NON_MAX_PACKETS_OK  = 0x00,
} audio_cs_as_iso_data_ep_attribute_t;

///音频类特定AS同步数据EP控制UAC2
typedef enum
{
  AUDIO_CS_AS_ISO_DATA_EP_CTRL_PITCH_POS          = 0,
  AUDIO_CS_AS_ISO_DATA_EP_CTRL_DATA_OVERRUN_POS   = 2,
  AUDIO_CS_AS_ISO_DATA_EP_CTRL_DATA_UNDERRUN_POS  = 4,
} audio_cs_as_iso_data_ep_control_pos_t;

///音频类特定AS同步数据EP锁定延迟单元UAC2
typedef enum
{
  AUDIO_CS_AS_ISO_DATA_EP_LOCK_DELAY_UNIT_UNDEFINED       = 0x00,
  AUDIO_CS_AS_ISO_DATA_EP_LOCK_DELAY_UNIT_MILLISEC        = 0x01,
  AUDIO_CS_AS_ISO_DATA_EP_LOCK_DELAY_UNIT_PCM_SAMPLES     = 0x02,
} audio_cs_as_iso_data_ep_lock_delay_unit_t;

///音频类时钟源属性UAC2
typedef enum
{
  AUDIO_CLOCK_SOURCE_ATT_EXT_CLK      = 0x00,
  AUDIO_CLOCK_SOURCE_ATT_INT_FIX_CLK  = 0x01,
  AUDIO_CLOCK_SOURCE_ATT_INT_VAR_CLK  = 0x02,
  AUDIO_CLOCK_SOURCE_ATT_INT_PRO_CLK  = 0x03,
  AUDIO_CLOCK_SOURCE_ATT_CLK_SYC_SOF  = 0x04,
} audio_clock_source_attribute_t;

///音频级时钟源控制UAC2
typedef enum
{
  AUDIO_CLOCK_SOURCE_CTRL_CLK_FRQ_POS     = 0,
  AUDIO_CLOCK_SOURCE_CTRL_CLK_VAL_POS     = 2,
} audio_clock_source_control_pos_t;

///音频级时钟选择器控制UAC2
typedef enum
{
  AUDIO_CLOCK_SELECTOR_CTRL_POS   = 0,
} audio_clock_selector_control_pos_t;

///音频级时钟乘法器控制UAC2
typedef enum
{
  AUDIO_CLOCK_MULTIPLIER_CTRL_NUMERATOR_POS       = 0,
  AUDIO_CLOCK_MULTIPLIER_CTRL_DENOMINATOR_POS     = 2,
} audio_clock_multiplier_control_pos_t;

///音频级输入端子控制UAC2
typedef enum
{
  AUDIO_IN_TERM_CTRL_CPY_PROT_POS     = 0,
  AUDIO_IN_TERM_CTRL_CONNECTOR_POS    = 2,
  AUDIO_IN_TERM_CTRL_OVERLOAD_POS     = 4,
  AUDIO_IN_TERM_CTRL_CLUSTER_POS      = 6,
  AUDIO_IN_TERM_CTRL_UNDERFLOW_POS    = 8,
  AUDIO_IN_TERM_CTRL_OVERFLOW_POS     = 10,
} audio_terminal_input_control_pos_t;

///音频级输出端子控制UAC2
typedef enum
{
  AUDIO_OUT_TERM_CTRL_CPY_PROT_POS    = 0,
  AUDIO_OUT_TERM_CTRL_CONNECTOR_POS   = 2,
  AUDIO_OUT_TERM_CTRL_OVERLOAD_POS    = 4,
  AUDIO_OUT_TERM_CTRL_UNDERFLOW_POS   = 6,
  AUDIO_OUT_TERM_CTRL_OVERFLOW_POS    = 8,
} audio_terminal_output_control_pos_t;

///音频级功能单元控制UAC2
typedef enum
{
  AUDIO_FEATURE_UNIT_CTRL_MUTE_POS            = 0,
  AUDIO_FEATURE_UNIT_CTRL_VOLUME_POS          = 2,
  AUDIO_FEATURE_UNIT_CTRL_BASS_POS            = 4,
  AUDIO_FEATURE_UNIT_CTRL_MID_POS             = 6,
  AUDIO_FEATURE_UNIT_CTRL_TREBLE_POS          = 8,
  AUDIO_FEATURE_UNIT_CTRL_GRAPHIC_EQU_POS     = 10,
  AUDIO_FEATURE_UNIT_CTRL_AGC_POS             = 12,
  AUDIO_FEATURE_UNIT_CTRL_DELAY_POS           = 14,
  AUDIO_FEATURE_UNIT_CTRL_BASS_BOOST_POS      = 16,
  AUDIO_FEATURE_UNIT_CTRL_LOUDNESS_POS        = 18,
  AUDIO_FEATURE_UNIT_CTRL_INPUT_GAIN_POS      = 20,
  AUDIO_FEATURE_UNIT_CTRL_INPUT_GAIN_PAD_POS  = 22,
  AUDIO_FEATURE_UNIT_CTRL_PHASE_INV_POS       = 24,
  AUDIO_FEATURE_UNIT_CTRL_UNDERFLOW_POS       = 26,
  AUDIO_FEATURE_UNIT_CTRL_OVERFLOW_POS        = 28,
} audio_feature_unit_control_pos_t;

///音频级音频通道配置UAC2
typedef enum
{
  AUDIO_CHANNEL_CONFIG_NON_PREDEFINED             = 0x00000000,
  AUDIO_CHANNEL_CONFIG_FRONT_LEFT                 = 0x00000001,
  AUDIO_CHANNEL_CONFIG_FRONT_RIGHT                = 0x00000002,
  AUDIO_CHANNEL_CONFIG_FRONT_CENTER               = 0x00000004,
  AUDIO_CHANNEL_CONFIG_LOW_FRQ_EFFECTS            = 0x00000008,
  AUDIO_CHANNEL_CONFIG_BACK_LEFT                  = 0x00000010,
  AUDIO_CHANNEL_CONFIG_BACK_RIGHT                 = 0x00000020,
  AUDIO_CHANNEL_CONFIG_FRONT_LEFT_OF_CENTER       = 0x00000040,
  AUDIO_CHANNEL_CONFIG_FRONT_RIGHT_OF_CENTER      = 0x00000080,
  AUDIO_CHANNEL_CONFIG_BACK_CENTER                = 0x00000100,
  AUDIO_CHANNEL_CONFIG_SIDE_LEFT                  = 0x00000200,
  AUDIO_CHANNEL_CONFIG_SIDE_RIGHT                 = 0x00000400,
  AUDIO_CHANNEL_CONFIG_TOP_CENTER                 = 0x00000800,
  AUDIO_CHANNEL_CONFIG_TOP_FRONT_LEFT             = 0x00001000,
  AUDIO_CHANNEL_CONFIG_TOP_FRONT_CENTER           = 0x00002000,
  AUDIO_CHANNEL_CONFIG_TOP_FRONT_RIGHT            = 0x00004000,
  AUDIO_CHANNEL_CONFIG_TOP_BACK_LEFT              = 0x00008000,
  AUDIO_CHANNEL_CONFIG_TOP_BACK_CENTER            = 0x00010000,
  AUDIO_CHANNEL_CONFIG_TOP_BACK_RIGHT             = 0x00020000,
  AUDIO_CHANNEL_CONFIG_TOP_FRONT_LEFT_OF_CENTER   = 0x00040000,
  AUDIO_CHANNEL_CONFIG_TOP_FRONT_RIGHT_OF_CENTER  = 0x00080000,
  AUDIO_CHANNEL_CONFIG_LEFT_LOW_FRQ_EFFECTS       = 0x00100000,
  AUDIO_CHANNEL_CONFIG_RIGHT_LOW_FRQ_EFFECTS      = 0x00200000,
  AUDIO_CHANNEL_CONFIG_TOP_SIDE_LEFT              = 0x00400000,
  AUDIO_CHANNEL_CONFIG_TOP_SIDE_RIGHT             = 0x00800000,
  AUDIO_CHANNEL_CONFIG_BOTTOM_CENTER              = 0x01000000,
  AUDIO_CHANNEL_CONFIG_BACK_LEFT_OF_CENTER        = 0x02000000,
  AUDIO_CHANNEL_CONFIG_BACK_RIGHT_OF_CENTER       = 0x04000000,
  AUDIO_CHANNEL_CONFIG_RAW_DATA                   = 0x80000000,
} audio_channel_config_t;

///音频通道群集描述符（4.1）
typedef struct TU_ATTR_PACKED {
  uint8_t                 bNrChannels;        ///<当前连接的信道数。
  audio_channel_config_t  bmChannelConfig;    ///<根据“audio_channel_config_t”的位图，如果通道已连接，则设置1，否则设置0。如果通道是非预定义的，则在此处忽略它们（参见UAC2规范4.1音频通道群集描述符）。
  uint8_t                 iChannelNames;      ///<字符串描述符的索引，描述具有非预定义空间位置的第一个插入通道的名称。
} audio_desc_channel_cluster_t;

///音频类特定AC接口标题描述符（4.7.2）
typedef struct TU_ATTR_PACKED
{
  uint8_t bLength            ; ///<此描述符的大小（字节）：9。
  uint8_t bDescriptorType    ; ///<描述符类型。值：TUSB_DESC_CS_INTERFACE。
  uint8_t bDescriptorSubType ; ///<描述符子类型。值：AUDIO_CS_AC_INTERFACE_HEADER。
  uint16_t bcdADC            ; ///<以二进制编码十进制表示的音频设备类别规范发布编号。值：U16_TO_U8S_LE（0x0200）。
  uint8_t bCategory          ; ///<常量，表示制造商预期的此音频功能的主要用途。参见：audio_function_t。
  uint16_t wTotalLength      ; ///<为类特定AudioControl接口描述符返回的总字节数。包括此描述符标头和所有时钟源、单元和终端描述符的组合长度。
  uint8_t bmControls         ; ///<参见：audio_cs_ac_interface_control_pos_t。
} audio_desc_cs_ac_interface_t;

///音频时钟源描述符（4.7.2.1）
typedef struct TU_ATTR_PACKED
{
  uint8_t bLength            ; ///<此描述符的大小（字节）：8。
  uint8_t bDescriptorType    ; ///<描述符类型。值：TUSB_DESC_CS_INTERFACE。
  uint8_t bDescriptorSubType ; ///<描述符子类型。值：AUDIO_CS_AC_INTERFACE_CLOCK_SOURCE。
  uint8_t bClockID           ; ///<在音频功能中唯一标识时钟源实体的常量。此值用于处理此实体的所有请求。
  uint8_t bmAttributes       ; ///<参见：audio_clock_source_attribute_t。
  uint8_t bmControls         ; ///<参见：audio_clock_source_control_pos_t。
  uint8_t bAssocTerminal     ; ///<与此时钟源关联的终端的终端ID。
  uint8_t iClockSource       ; ///<字符串描述符的索引，描述时钟源实体。
} audio_desc_clock_source_t;

///一个引脚的音频时钟选择器描述符（4.7.2.2）
typedef struct TU_ATTR_PACKED
{
  uint8_t bLength            ; ///<此描述符的大小（字节）：7+p。
  uint8_t bDescriptorType    ; ///<描述符类型。值：TUSB_DESC_CS_INTERFACE。
  uint8_t bDescriptorSubType ; ///<描述符子类型。值：AUDIO_CS_AC_INTERFACE_CLOCK_SELECTOR。
  uint8_t bClockID           ; ///<在音频功能中唯一标识时钟选择器实体的常量。此值用于处理此实体的所有请求。
  uint8_t bNrInPins          ; ///<此单元的输入引脚数：p=1，因此bNrInPins=1。
  uint8_t baCSourceID        ; ///<此时钟选择器实体的第一个时钟输入引脚所连接的时钟实体的ID。。
  uint8_t bmControls         ; ///<参见：audio_clock_selector_control_pos_t。
  uint8_t iClockSource       ; ///<字符串描述符的索引，描述时钟选择器实体。
} audio_desc_clock_selector_t;

///多个引脚的音频时钟选择器描述符（4.7.2.2）
#define audio_desc_clock_selector_n_t(source_num) \
    struct TU_ATTR_PACKED {       \
  uint8_t bLength               ; \
  uint8_t bDescriptorType       ; \
  uint8_t bDescriptorSubType    ; \
  uint8_t bClockID              ; \
  uint8_t bNrInPins             ; \
  struct TU_ATTR_PACKED {         \
    uint8_t baSourceID          ; \
  } sourceID[source_num]        ; \
  uint8_t bmControls            ; \
  uint8_t iClockSource          ; \
}

///音频时钟乘法器描述符（4.7.2.3）
typedef struct TU_ATTR_PACKED
{
  uint8_t bLength            ; ///<此描述符的大小（字节）：7。
  uint8_t bDescriptorType    ; ///<描述符类型。值：TUSB_DESC_CS_INTERFACE。
  uint8_t bDescriptorSubType ; ///<描述符子类型。值：AUDIO_CS_AC_INTERFACE_CLOCK_MULTIPLIER。
  uint8_t bClockID           ; ///<在音频函数中唯一标识时钟乘法器实体的常数。此值用于处理此实体的所有请求。
  uint8_t bCSourceID         ; ///<此时钟选择器实体的最后一个时钟输入引脚所连接的时钟实体的ID。
  uint8_t bmControls         ; ///<参见：audio_clock_multipier_control_pos_t。
  uint8_t iClockSource       ; ///<字符串描述符的索引，描述时钟乘数实体。
} audio_desc_clock_multiplier_t;

///音频输入终端描述符（4.7.2.4）
typedef struct TU_ATTR_PACKED
{
  uint8_t bLength            ; ///<此描述符的大小，以字节为单位：17。
  uint8_t bDescriptorType    ; ///<描述符类型。值：TUSB_DESC_CS_INTERFACE。
  uint8_t bDescriptorSubType ; ///<描述符子类型。值：AUDIO_CS_AC_INTERFACE_INPUT_TERMINAL。
  uint16_t wTerminalType     ; ///<表征终端类型的常数。请参见：audio_terminal_type_t了解USB流，audio_terminatl_input_type_t了解其他输入类型。
  uint8_t bAssocTerminal     ; ///<与此输入端子关联的输出端子的ID。
  uint8_t bCSourceID         ; ///<此输入端子所连接的时钟实体的ID。
  uint8_t bNrChannels        ; ///<终端输出音频通道集群中的逻辑输出通道数。
  uint32_t bmChannelConfig   ; ///<描述逻辑通道的空间位置。参见：audio_channel_config_t。
  uint16_t bmControls        ; ///<参见：audio_terminal_input_control_pos_t。
  uint8_t iTerminal          ; ///<字符串描述符的索引，描述输入终端。
} audio_desc_input_terminal_t;

///音频输出端子描述符（4.7.2.5）
typedef struct TU_ATTR_PACKED
{
  uint8_t bLength            ; ///<此描述符的大小，以字节为单位：12。
  uint8_t bDescriptorType    ; ///<描述符类型。值：TUSB_DESC_CS_INTERFACE。
  uint8_t bDescriptorSubType ; ///<描述符子类型。值：AUDIO_CS_AC_INTERFACE_OUTPUT_TERMINAL。
  uint8_t bTerminalID        ; ///<在音频功能中唯一标识终端的常量。此值用于寻址此终端的所有请求中。
  uint16_t wTerminalType     ; ///<表征终端类型的常数。请参见：audio_terminal_type_t了解USB流，audio_terminatl_output_type_t了解其他输出类型。
  uint8_t bAssocTerminal     ; ///<常量，标识与此输出端子关联的输入端子。
  uint8_t bSourceID          ; ///<此终端所连接的装置或终端的ID。
  uint8_t bCSourceID         ; ///<此输出端子所连接的时钟实体的ID。
  uint16_t bmControls        ; ///<参见：audio_terminal_output_type_t。
  uint8_t iTerminal          ; ///<字符串描述符的索引，描述输出终端。
} audio_desc_output_terminal_t;

///一个通道的音频功能单元描述符（4.7.2.8）
typedef struct TU_ATTR_PACKED
{
  uint8_t bLength            ; ///<此描述符的大小，以字节为单位：14。
  uint8_t bDescriptorType    ; ///<描述符类型。值：TUSB_DESC_CS_INTERFACE。
  uint8_t bDescriptorSubType ; ///<描述符子类型。值：AUDIO_CS_AC_INTERFACE_FEATURE_UNIT。
  uint8_t bUnitID            ; ///<在音频功能中唯一标识单元的常量。此值用于处理此单元的所有请求。
  uint8_t bSourceID          ; ///<此功能单元所连接的单元或终端的ID。
  struct TU_ATTR_PACKED {
    uint32_t bmaControls     ; ///<请参见：audio_feature_unit_control_pos_t。Controls0是主信道0（始终存在），Controls1是逻辑信道1。
  } controls[2]              ;
  uint8_t iTerminal          ; ///<描述此功能单元的字符串描述符的索引。
} audio_desc_feature_unit_t;

///多通道音频功能单元描述符（4.7.2.8）
#define audio_desc_feature_unit_n_t(ch_num)\
    struct TU_ATTR_PACKED {         \
  uint8_t bLength               ; /* 6+（ch_num+1）*4*/\
    uint8_t bDescriptorType     ; \
    uint8_t bDescriptorSubType  ; \
    uint8_t bUnitID             ; \
    uint8_t bSourceID           ; \
    struct TU_ATTR_PACKED {       \
      uint32_t bmaControls      ; \
    } controls[ch_num+1]        ; \
    uint8_t iTerminal           ; \
}

///音频类特定AS接口描述符（4.9.2）
typedef struct TU_ATTR_PACKED
{
  uint8_t bLength            ; ///<此描述符的大小，以字节为单位：16。
  uint8_t bDescriptorType    ; ///<描述符类型。值：TUSB_DESC_CS_INTERFACE。
  uint8_t bDescriptorSubType ; ///<描述符子类型。值：AUDIO_CS_AS_INTERFACE_AS_GENERAL。
  uint8_t bTerminalLink      ; ///<此接口所连接的终端的终端ID。
  uint8_t bmControls         ; ///<参见：audio_cs_as_interface_control_pos_t。
  uint8_t bFormatType        ; ///<标识AudioStream接口正在使用的格式类型的常量。请参见：audio_format_type_t。
  uint32_t bmFormats         ; ///<可用于与此接口通信的音频数据格式。请参见：audio_data_format_type_I_t。
  uint8_t bNrChannels        ; ///<AS接口音频通道集群中的物理通道数。
  uint32_t bmChannelConfig   ; ///<描述物理通道的空间位置。参见：audio_channel_config_t。
  uint8_t iChannelNames      ; ///<字符串描述符的索引，描述第一个物理通道的名称。
} audio_desc_cs_as_interface_t;

///音频I型格式类型描述符（2.3.1.6-音频格式）
typedef struct TU_ATTR_PACKED
{
  uint8_t bLength            ; ///<此描述符的大小（字节）：6。
  uint8_t bDescriptorType    ; ///<描述符类型。值：TUSB_DESC_CS_INTERFACE。
  uint8_t bDescriptorSubType ; ///<描述符子类型。值：AUDIO_CS_AS_INTERFACE_FORMAT_TYPE。
  uint8_t bFormatType        ; ///<标识AudioStream接口正在使用的格式类型的常量。值：AUDIO_FORMAT_TYPE_I。
  uint8_t bSubslotSize       ; ///<一个音频子时隙占用的字节数。可以是1、2、3或4。
  uint8_t bBitResolution     ; ///<音频子时隙中可用比特中有效使用的比特数。
} audio_desc_type_I_format_t;

///音频类特定AS等时音频数据端点描述符（4.10.1.2）
typedef struct TU_ATTR_PACKED
{
  uint8_t bLength            ; ///<此描述符的大小（字节）：8。
  uint8_t bDescriptorType    ; ///<描述符类型。值：TUSB_DESC_CS_ENDPOINT。
  uint8_t bDescriptorSubType ; ///<描述符子类型。值：AUDIO_CS_EP_SUBTYPE_GENERAL。
  uint8_t bmAttributes       ; ///<参见：audio_cs_as_iso_data_ep_attribute_t。
  uint8_t bmControls         ; ///<请参见：audio_cs_as_iso_data_ep_control_pos_t。
  uint8_t bLockDelayUnits    ; ///<表示用于wLockDelay字段的单位。请参见：audio_cs_as_iso_data_ep_lock_delay_unit_t。
  uint16_t wLockDelay        ; ///<表示此端点可靠锁定其内部时钟恢复电路所需的时间。使用的单位取决于bLockDelayUnits字段的值。
} audio_desc_cs_as_iso_data_ep_t;

////5.2.3控制请求参数块布局

// 5.2.3.1 1字节控制CUR参数块
typedef struct TU_ATTR_PACKED
{
  int8_t bCur               ;   ///<寻址控件的CUR属性设置
} audio_control_cur_1_t;

// 5.2.3.2 2字节控制CUR参数块
typedef struct TU_ATTR_PACKED
{
  int16_t bCur              ;   ///<寻址控件的CUR属性设置
} audio_control_cur_2_t;

// 5.2.3.3 4字节控制CUR参数块
typedef struct TU_ATTR_PACKED
{
  int32_t bCur              ;   ///<寻址控件的CUR属性设置
} audio_control_cur_4_t;

// 仅对RECEIVE数据使用以下命令-编译器不知道定义了多少子范围！对于预定义的长度，请使用下面的一个，或者如果你知道你在做什么，就做你喜欢的事情
// 5.2.3.1 1字节控制范围参数块
typedef struct TU_ATTR_PACKED {
  uint16_t wNumSubRanges;
  struct TU_ATTR_PACKED {
    int8_t bMin             ; /*寻址控件第n个子范围的MIN属性设置*/
    int8_t bMax             ; /*寻址控件第n个子范围的MAX属性设置*/
    uint8_t bRes            ; /*寻址控件第n个子范围的RES属性设置*/
  } subrange[]              ;
} audio_control_range_1_t;

// 5.2.3.2 2字节控制范围参数块
typedef struct TU_ATTR_PACKED {
  uint16_t wNumSubRanges;
  struct TU_ATTR_PACKED {
    int16_t bMin            ; /*寻址控件第n个子范围的MIN属性设置*/
    int16_t bMax            ; /*寻址控件第n个子范围的MAX属性设置*/
    uint16_t bRes           ; /*寻址控件第n个子范围的RES属性设置*/
  } subrange[]              ;
} audio_control_range_2_t;

// 5.2.3.3 4字节控制范围参数块
typedef struct TU_ATTR_PACKED {
  uint16_t wNumSubRanges;
  struct TU_ATTR_PACKED {
    int32_t bMin            ; /*寻址控件第n个子范围的MIN属性设置*/
    int32_t bMax            ; /*寻址控件第n个子范围的MAX属性设置*/
    uint32_t bRes           ; /*寻址控件第n个子范围的RES属性设置*/
  } subrange[]              ;
} audio_control_range_4_t;

// 5.2.3.1 1字节控制范围参数块
#define audio_control_range_1_n_t(numSubRanges) \
    struct TU_ATTR_PACKED {                     \
  uint16_t wNumSubRanges;                       \
  struct TU_ATTR_PACKED {                       \
      int8_t bMin               ; /*寻址控件第n个子范围的MIN属性设置*/\
    int8_t bMax                 ; /*寻址控件第n个子范围的MAX属性设置*/\
    uint8_t bRes                ; /*寻址控件第n个子范围的RES属性设置*/\
    } subrange[numSubRanges]    ;               \
}

///5.2.3.2 2字节控制范围参数块
#define audio_control_range_2_n_t(numSubRanges) \
    struct TU_ATTR_PACKED {                     \
  uint16_t wNumSubRanges;                       \
  struct TU_ATTR_PACKED {                       \
      int16_t bMin          ; /*寻址控件第n个子范围的MIN属性设置*/\
    int16_t bMax            ; /*寻址控件第n个子范围的MAX属性设置*/\
    uint16_t bRes           ; /*寻址控件第n个子范围的RES属性设置*/\
    } subrange[numSubRanges];                   \
}

// 5.2.3.3 4字节控制范围参数块
#define audio_control_range_4_n_t(numSubRanges) \
    struct TU_ATTR_PACKED {                     \
  uint16_t wNumSubRanges;                       \
  struct TU_ATTR_PACKED {                       \
      int32_t bMin          ; /*寻址控件第n个子范围的MIN属性设置*/\
    int32_t bMax            ; /*寻址控件第n个子范围的MAX属性设置*/\
    uint32_t bRes           ; /*寻址控件第n个子范围的RES属性设置*/\
    } subrange[numSubRanges];                   \
}

/** @} */

#ifdef __cplusplus
}
#endif

#endif

/** @} */

