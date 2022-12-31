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

/** \ingroup组_usbd
 *  @{ */

#ifndef _TUSB_USBD_H_
#define _TUSB_USBD_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "common/tusb_common.h"

//--------------------------------------------------------------------+
// 应用程序API
//--------------------------------------------------------------------+

// 初始化设备堆栈
bool tud_init (void);

// 应在主/rtos循环中调用任务函数
void tud_task (void);

// 检查是否存在需要通过tud_task（）处理的挂起事件
bool tud_task_event_ready(void);

// 中断处理程序，DCD的别名
extern void dcd_int_handler(uint8_t rhport);
#define tud_int_handler   dcd_int_handler

// 获取当前总线速度
tusb_speed_t tud_speed_get(void);

// 检查设备是否已连接（可能尚未安装/配置）
// 如果刚刚退出总线重置并从主机接收到第一个数据，则为True
bool tud_connected(void);

// 检查设备是否已连接和配置
bool tud_mounted(void);

// 检查设备是否已挂起
bool tud_suspended(void);

// 检查设备是否准备好传输
static inline bool tud_ready(void)
{
  return tud_mounted() && !tud_suspended();
}

// 远程唤醒主机，仅当主机挂起并启用时
bool tud_remote_wakeup(void);

// 启用D+D上的上拉电阻器-
// 在不受支持的MCU上返回false
bool tud_disconnect(void);

// 禁用D+D上的上拉电阻器-
// 在不受支持的MCU上返回false
bool tud_connect(void);

// 执行控制传输的数据和状态阶段
// -如果len=0，则相当于仅发送状态
// -如果len>wLength：将被截断
bool tud_control_xfer(uint8_t rhport, tusb_control_request_t const * request, void* buffer, uint16_t len);

// 发送STATUS（零长度）数据包
bool tud_control_status(uint8_t rhport, tusb_control_request_t const * request);

//--------------------------------------------------------------------+
// 应用程序回调（WEAK是可选的）
//--------------------------------------------------------------------+

// 收到GET DEVICE DESCRIPTOR请求时调用
// 应用程序返回指向描述符的指针
uint8_t const * tud_descriptor_device_cb(void);

// 收到GET BOS DESCRIPTOR请求时调用
// 应用程序返回指向描述符的指针
TU_ATTR_WEAK uint8_t const * tud_descriptor_bos_cb(void);

// 收到GET CONFIGURATION DESCRIPTOR请求时调用
// 应用程序返回指向描述符的指针，其内容必须存在足够长的时间才能完成传输
uint8_t const * tud_descriptor_configuration_cb(uint8_t index);

// 收到GET STRING DESCRIPTOR请求时调用
// 应用程序返回指向描述符的指针，其内容必须存在足够长的时间才能完成传输
uint16_t const* tud_descriptor_string_cb(uint8_t index, uint16_t langid);

// 收到GET DEVICE QUALIFIER DESCRIPTOR请求时调用
// 应用程序返回指向描述符的指针，其内容必须存在足够长的时间才能完成传输
TU_ATTR_WEAK uint8_t const* tud_descriptor_device_qualifier_cb(void);

// 在装载（配置）设备时调用
TU_ATTR_WEAK void tud_mount_cb(void);

// 在卸载设备时调用
TU_ATTR_WEAK void tud_umount_cb(void);

// 在usb总线挂起时调用
// 在7ms内，设备必须从总线汲取小于2.5 mA的平均电流
TU_ATTR_WEAK void tud_suspend_cb(bool remote_wakeup_en);

// 恢复usb总线时调用
TU_ATTR_WEAK void tud_resume_cb(void);

// 收到供应商类型的控制请求时调用
TU_ATTR_WEAK bool tud_vendor_control_xfer_cb(uint8_t rhport, uint8_t stage, tusb_control_request_t const * request);

//--------------------------------------------------------------------+
// 二进制设备对象存储（BOS）描述符模板
//--------------------------------------------------------------------+

#define TUD_BOS_DESC_LEN      5

// 总长度、设备帽数
#define TUD_BOS_DESCRIPTOR(_total_len, _caps_num) \
  5, TUSB_DESC_BOS, U16_TO_U8S_LE(_total_len), _caps_num

// 设备能力平台128位UUID+数据
#define TUD_BOS_PLATFORM_DESCRIPTOR(...) \
  4+TU_ARGS_NUM(__VA_ARGS__), TUSB_DESC_DEVICE_CAPABILITY, DEVICE_CAPABILITY_PLATFORM, 0x00, __VA_ARGS__

//-------------WebUSB BOS平台-------------//

// 描述符长度
#define TUD_BOS_WEBUSB_DESC_LEN         24

// 供应商代码，iLandingPage
#define TUD_BOS_WEBUSB_DESCRIPTOR(_vendor_code, _ipage) \
  TUD_BOS_PLATFORM_DESCRIPTOR(TUD_BOS_WEBUSB_UUID, U16_TO_U8S_LE(0x0100), _vendor_code, _ipage)

#define TUD_BOS_WEBUSB_UUID   \
  0x38, 0xB6, 0x08, 0x34, 0xA9, 0x09, 0xA0, 0x47, \
  0x8B, 0xFD, 0xA0, 0x76, 0x88, 0x15, 0xB6, 0x65

//-------------Microsoft OS 2.0平台-------------//
#define TUD_BOS_MICROSOFT_OS_DESC_LEN   28

// 描述符集的总长度，供应商代码
#define TUD_BOS_MS_OS_20_DESCRIPTOR(_desc_set_len, _vendor_code) \
  TUD_BOS_PLATFORM_DESCRIPTOR(TUD_BOS_MS_OS_20_UUID, U32_TO_U8S_LE(0x06030000), U16_TO_U8S_LE(_desc_set_len), _vendor_code, 0)

#define TUD_BOS_MS_OS_20_UUID \
    0xDF, 0x60, 0xDD, 0xD8, 0x89, 0x45, 0xC7, 0x4C, \
  0x9C, 0xD2, 0x65, 0x9D, 0x9E, 0x64, 0x8A, 0x9F

//--------------------------------------------------------------------+
// 配置和接口描述符模板
//--------------------------------------------------------------------+

//-------------配置-------------//
#define TUD_CONFIG_DESC_LEN   (9)

// 配置编号、接口计数、字符串索引、总长度、属性、功率（mA）
#define TUD_CONFIG_DESCRIPTOR(config_num, _itfcount, _stridx, _total_len, _attribute, _power_ma) \
  9, TUSB_DESC_CONFIGURATION, U16_TO_U8S_LE(_total_len), _itfcount, config_num, _stridx, TU_BIT(7) | _attribute, (_power_ma)/2

//------------- CDC -------------//

// 模板描述符长度：66字节
#define TUD_CDC_DESC_LEN  (8+9+5+5+4+5+7+9+7+7)

// CDC描述符模板
// 接口编号、字符串索引、EP通知地址和大小、EP数据地址（输出、输入）和大小。
#define TUD_CDC_DESCRIPTOR(_itfnum, _stridx, _ep_notif, _ep_notif_size, _epout, _epin, _epsize) \
  /* 接口关联*/\
  8, TUSB_DESC_INTERFACE_ASSOCIATION, _itfnum, 2, TUSB_CLASS_CDC, CDC_COMM_SUBCLASS_ABSTRACT_CONTROL_MODEL, CDC_COMM_PROTOCOL_NONE, 0,\
  /* CDC控制接口*/\
  9, TUSB_DESC_INTERFACE, _itfnum, 0, 1, TUSB_CLASS_CDC, CDC_COMM_SUBCLASS_ABSTRACT_CONTROL_MODEL, CDC_COMM_PROTOCOL_NONE, _stridx,\
  /* CDC标题*/\
  5, TUSB_DESC_CS_INTERFACE, CDC_FUNC_DESC_HEADER, U16_TO_U8S_LE(0x0120),\
  /* CDC电话*/\
  5, TUSB_DESC_CS_INTERFACE, CDC_FUNC_DESC_CALL_MANAGEMENT, 0, (uint8_t)((_itfnum) + 1),\
  /* CDC ACM：支持线请求*/\
  4, TUSB_DESC_CS_INTERFACE, CDC_FUNC_DESC_ABSTRACT_CONTROL_MANAGEMENT, 2,\
  /* CDC联盟*/\
  5, TUSB_DESC_CS_INTERFACE, CDC_FUNC_DESC_UNION, _itfnum, (uint8_t)((_itfnum) + 1),\
  /* 终结点通知*/\
  7, TUSB_DESC_ENDPOINT, _ep_notif, TUSB_XFER_INTERRUPT, U16_TO_U8S_LE(_ep_notif_size), 16,\
  /* CDC数据接口*/\
  9, TUSB_DESC_INTERFACE, (uint8_t)((_itfnum)+1), 0, 2, TUSB_CLASS_CDC_DATA, 0, 0, 0,\
  /* 端点输出*/\
  7, TUSB_DESC_ENDPOINT, _epout, TUSB_XFER_BULK, U16_TO_U8S_LE(_epsize), 0,\
  /* 端点输入*/\
  7, TUSB_DESC_ENDPOINT, _epin, TUSB_XFER_BULK, U16_TO_U8S_LE(_epsize), 0

//------------- MSC -------------//

// 模板描述符长度：23字节
#define TUD_MSC_DESC_LEN    (9 + 7 + 7)

// 接口编号、字符串索引、EP输出和EP输入地址、EP大小
#define TUD_MSC_DESCRIPTOR(_itfnum, _stridx, _epout, _epin, _epsize) \
  /* 界面*/\
  9, TUSB_DESC_INTERFACE, _itfnum, 0, 2, TUSB_CLASS_MSC, MSC_SUBCLASS_SCSI, MSC_PROTOCOL_BOT, _stridx,\
  /* 端点输出*/\
  7, TUSB_DESC_ENDPOINT, _epout, TUSB_XFER_BULK, U16_TO_U8S_LE(_epsize), 0,\
  /* 端点输入*/\
  7, TUSB_DESC_ENDPOINT, _epin, TUSB_XFER_BULK, U16_TO_U8S_LE(_epsize), 0

//------------- HID -------------//

// 模板描述符长度：25字节
#define TUD_HID_DESC_LEN    (9 + 9 + 7)

// HID仅输入描述符
// 接口编号、字符串索引、协议、报告描述符长度、EP-In地址、大小和轮询间隔
#define TUD_HID_DESCRIPTOR(_itfnum, _stridx, _boot_protocol, _report_desc_len, _epin, _epsize, _ep_interval) \
  /* 界面*/\
  9, TUSB_DESC_INTERFACE, _itfnum, 0, 1, TUSB_CLASS_HID, (uint8_t)((_boot_protocol) ? HID_SUBCLASS_BOOT : 0), _boot_protocol, _stridx,\
  /* HID描述符*/\
  9, HID_DESC_TYPE_HID, U16_TO_U8S_LE(0x0111), 0, 1, HID_DESC_TYPE_REPORT, U16_TO_U8S_LE(_report_desc_len),\
  /* 端点输入*/\
  7, TUSB_DESC_ENDPOINT, _epin, TUSB_XFER_INTERRUPT, U16_TO_U8S_LE(_epsize), _ep_interval

// 模板描述符长度：32字节
#define TUD_HID_INOUT_DESC_LEN    (9 + 9 + 7 + 7)

// HID输入和输出描述符
// 接口编号、字符串索引、协议、报告描述符长度、EP OUT&IN地址、大小和轮询间隔
#define TUD_HID_INOUT_DESCRIPTOR(_itfnum, _stridx, _boot_protocol, _report_desc_len, _epout, _epin, _epsize, _ep_interval) \
  /* 界面*/\
  9, TUSB_DESC_INTERFACE, _itfnum, 0, 2, TUSB_CLASS_HID, (uint8_t)((_boot_protocol) ? HID_SUBCLASS_BOOT : 0), _boot_protocol, _stridx,\
  /* HID描述符*/\
  9, HID_DESC_TYPE_HID, U16_TO_U8S_LE(0x0111), 0, 1, HID_DESC_TYPE_REPORT, U16_TO_U8S_LE(_report_desc_len),\
  /* 端点输出*/\
  7, TUSB_DESC_ENDPOINT, _epout, TUSB_XFER_INTERRUPT, U16_TO_U8S_LE(_epsize), _ep_interval, \
  /* 端点输入*/\
  7, TUSB_DESC_ENDPOINT, _epin, TUSB_XFER_INTERRUPT, U16_TO_U8S_LE(_epsize), _ep_interval

//------------- MIDI -------------//
// MIDI v1.0基于Audio v1.0

#define TUD_MIDI_DESC_HEAD_LEN (9 + 9 + 9 + 7)
#define TUD_MIDI_DESC_HEAD(_itfnum,  _stridx, _numcables) \
  /* 音频控制（AC）接口*/\
  9, TUSB_DESC_INTERFACE, _itfnum, 0, 0, TUSB_CLASS_AUDIO, AUDIO_SUBCLASS_CONTROL, AUDIO_FUNC_PROTOCOL_CODE_UNDEF, _stridx,\
  /* AC接头*/\
  9, TUSB_DESC_CS_INTERFACE, AUDIO_CS_AC_INTERFACE_HEADER, U16_TO_U8S_LE(0x0100), U16_TO_U8S_LE(0x0009), 1, (uint8_t)((_itfnum) + 1),\
  /* MIDI流（MS）接口*/\
  9, TUSB_DESC_INTERFACE, (uint8_t)((_itfnum) + 1), 0, 2, TUSB_CLASS_AUDIO, AUDIO_SUBCLASS_MIDI_STREAMING, AUDIO_FUNC_PROTOCOL_CODE_UNDEF, 0,\
  /* MS标题*/\
  7, TUSB_DESC_CS_INTERFACE, MIDI_CS_INTERFACE_HEADER, U16_TO_U8S_LE(0x0100), U16_TO_U8S_LE(7 + (_numcables) * TUD_MIDI_DESC_JACK_LEN)

#define TUD_MIDI_JACKID_IN_EMB(_cablenum) \
  (uint8_t)(((_cablenum) - 1) * 4 + 1)

#define TUD_MIDI_JACKID_IN_EXT(_cablenum) \
  (uint8_t)(((_cablenum) - 1) * 4 + 2)

#define TUD_MIDI_JACKID_OUT_EMB(_cablenum) \
  (uint8_t)(((_cablenum) - 1) * 4 + 3)

#define TUD_MIDI_JACKID_OUT_EXT(_cablenum) \
  (uint8_t)(((_cablenum) - 1) * 4 + 4)

#define TUD_MIDI_DESC_JACK_LEN (6 + 6 + 9 + 9)
#define TUD_MIDI_DESC_JACK(_cablenum) \
  /* MS插孔（嵌入式）*/\
  6, TUSB_DESC_CS_INTERFACE, MIDI_CS_INTERFACE_IN_JACK, MIDI_JACK_EMBEDDED, TUD_MIDI_JACKID_IN_EMB(_cablenum), 0,\
  /* MS插孔（外部）*/\
  6, TUSB_DESC_CS_INTERFACE, MIDI_CS_INTERFACE_IN_JACK, MIDI_JACK_EXTERNAL, TUD_MIDI_JACKID_IN_EXT(_cablenum), 0,\
  /* MS输出插孔（嵌入式），连接到外部输入插孔*/\
  9, TUSB_DESC_CS_INTERFACE, MIDI_CS_INTERFACE_OUT_JACK, MIDI_JACK_EMBEDDED, TUD_MIDI_JACKID_OUT_EMB(_cablenum), 1, TUD_MIDI_JACKID_IN_EXT(_cablenum), 1, 0,\
  /* MS输出插孔（外部），连接到嵌入式插孔*/\
  9, TUSB_DESC_CS_INTERFACE, MIDI_CS_INTERFACE_OUT_JACK, MIDI_JACK_EXTERNAL, TUD_MIDI_JACKID_OUT_EXT(_cablenum), 1, TUD_MIDI_JACKID_IN_EMB(_cablenum), 1, 0

#define TUD_MIDI_DESC_EP_LEN(_numcables) (9 + 4 + (_numcables))
#define TUD_MIDI_DESC_EP(_epout, _epsize, _numcables) \
  /* 端点：注意Audio v1.0的端点有9个字节，而不是7个字节*/\
  9, TUSB_DESC_ENDPOINT, _epout, TUSB_XFER_BULK, U16_TO_U8S_LE(_epsize), 0, 0, 0, \
  /* MS端点（连接到嵌入式插孔）*/\
  (uint8_t)(4 + (_numcables)), TUSB_DESC_CS_ENDPOINT, MIDI_CS_ENDPOINT_GENERAL, _numcables

// 模板描述符的长度（88字节）
#define TUD_MIDI_DESC_LEN (TUD_MIDI_DESC_HEAD_LEN + TUD_MIDI_DESC_JACK_LEN + TUD_MIDI_DESC_EP_LEN(1) * 2)

// MIDI简单描述符
// -1个嵌入式插孔连接到1个外部插孔
// -1个嵌入式插孔连接到1个外部插孔
#define TUD_MIDI_DESCRIPTOR(_itfnum, _stridx, _epout, _epin, _epsize) \
  TUD_MIDI_DESC_HEAD(_itfnum, _stridx, 1),\
  TUD_MIDI_DESC_JACK(1),\
  TUD_MIDI_DESC_EP(_epout, _epsize, 1),\
  TUD_MIDI_JACKID_IN_EMB(1),\
  TUD_MIDI_DESC_EP(_epin, _epsize, 1),\
  TUD_MIDI_JACKID_OUT_EMB(1)

//------------- AUDIO -------------//

/* 标准接口关联描述符（IAD）*/
#define TUD_AUDIO_DESC_IAD_LEN 8
#define TUD_AUDIO_DESC_IAD(_firstitfs, _nitfs, _stridx) \
  TUD_AUDIO_DESC_IAD_LEN, TUSB_DESC_INTERFACE_ASSOCIATION, _firstitfs, _nitfs, TUSB_CLASS_AUDIO, AUDIO_FUNCTION_SUBCLASS_UNDEFINED, AUDIO_FUNC_PROTOCOL_CODE_V2, _stridx

/* 标准交流接口描述符（4.7.1）*/
#define TUD_AUDIO_DESC_STD_AC_LEN 9
#define TUD_AUDIO_DESC_STD_AC(_itfnum, _nEPs, _stridx) /* _nEP为0或1*/\
  TUD_AUDIO_DESC_STD_AC_LEN, TUSB_DESC_INTERFACE, _itfnum, /* 固定为零*/ 0x00, _nEPs, TUSB_CLASS_AUDIO, AUDIO_SUBCLASS_CONTROL, AUDIO_INT_PROTOCOL_CODE_V2, _stridx

/* 类特定AC接口头描述符（4.7.2）*/
#define TUD_AUDIO_DESC_CS_AC_LEN 9
#define TUD_AUDIO_DESC_CS_AC(_bcdADC, _category, _totallen, _ctrl) /* _bcdedit ADC:音频设备类规范发行号（二进制编码十进制），_category:请参阅Audio_function_t，_totallen：为类特定AudioControl接口返回的字节总数，即时钟源、单元和终端描述符-不包括TUD_Audio_DESC_CS_AC_LEN，我们已经在此处执行了此操作*/ \
  TUD_AUDIO_DESC_CS_AC_LEN, TUSB_DESC_CS_INTERFACE, AUDIO_CS_AC_INTERFACE_HEADER, U16_TO_U8S_LE(_bcdADC), _category, U16_TO_U8S_LE(_totallen + TUD_AUDIO_DESC_CS_AC_LEN), _ctrl

/* 时钟源描述符（4.7.2.1）*/
#define TUD_AUDIO_DESC_CLK_SRC_LEN 8
#define TUD_AUDIO_DESC_CLK_SRC(_clkid, _attr, _ctrl, _assocTerm, _stridx) \
  TUD_AUDIO_DESC_CLK_SRC_LEN, TUSB_DESC_CS_INTERFACE, AUDIO_CS_AC_INTERFACE_CLOCK_SOURCE, _clkid, _attr, _ctrl, _assocTerm, _stridx

/* 输入终端描述符（4.7.2.4）*/
#define TUD_AUDIO_DESC_INPUT_TERM_LEN 17
#define TUD_AUDIO_DESC_INPUT_TERM(_termid, _termtype, _assocTerm, _clkid, _nchannelslogical, _channelcfg, _idxchannelnames, _ctrl, _stridx) \
  TUD_AUDIO_DESC_INPUT_TERM_LEN, TUSB_DESC_CS_INTERFACE, AUDIO_CS_AC_INTERFACE_INPUT_TERMINAL, _termid, U16_TO_U8S_LE(_termtype), _assocTerm, _clkid, _nchannelslogical, U32_TO_U8S_LE(_channelcfg), _idxchannelnames, U16_TO_U8S_LE(_ctrl), _stridx

/* 输出端子描述符（4.7.2.5）*/
#define TUD_AUDIO_DESC_OUTPUT_TERM_LEN 12
#define TUD_AUDIO_DESC_OUTPUT_TERM(_termid, _termtype, _assocTerm, _srcid, _clkid, _ctrl, _stridx) \
  TUD_AUDIO_DESC_OUTPUT_TERM_LEN, TUSB_DESC_CS_INTERFACE, AUDIO_CS_AC_INTERFACE_OUTPUT_TERMINAL, _termid, U16_TO_U8S_LE(_termtype), _assocTerm, _srcid, _clkid, U16_TO_U8S_LE(_ctrl), _stridx

/* 功能单元描述符（4.7.2.8）*/
// 1-通道
#define TUD_AUDIO_DESC_FEATURE_UNIT_ONE_CHANNEL_LEN 6+(1+1)*4
#define TUD_AUDIO_DESC_FEATURE_UNIT_ONE_CHANNEL(_unitid, _srcid, _ctrlch0master, _ctrlch1, _stridx) \
  TUD_AUDIO_DESC_FEATURE_UNIT_ONE_CHANNEL_LEN, TUSB_DESC_CS_INTERFACE, AUDIO_CS_AC_INTERFACE_FEATURE_UNIT, _unitid, _srcid, U32_TO_U8S_LE(_ctrlch0master), U32_TO_U8S_LE(_ctrlch1), _stridx

// 2-通道
#define TUD_AUDIO_DESC_FEATURE_UNIT_TWO_CHANNEL_LEN (6+(2+1)*4)
#define TUD_AUDIO_DESC_FEATURE_UNIT_TWO_CHANNEL(_unitid, _srcid, _ctrlch0master, _ctrlch1, _ctrlch2, _stridx) \
		TUD_AUDIO_DESC_FEATURE_UNIT_TWO_CHANNEL_LEN, TUSB_DESC_CS_INTERFACE, AUDIO_CS_AC_INTERFACE_FEATURE_UNIT, _unitid, _srcid, U32_TO_U8S_LE(_ctrlch0master), U32_TO_U8S_LE(_ctrlch1), U32_TO_U8S_LE(_ctrlch2), _stridx
// 4-通道
#define TUD_AUDIO_DESC_FEATURE_UNIT_FOUR_CHANNEL_LEN (6+(4+1)*4)
#define TUD_AUDIO_DESC_FEATURE_UNIT_FOUR_CHANNEL(_unitid, _srcid, _ctrlch0master, _ctrlch1, _ctrlch2, _ctrlch3, _ctrlch4, _stridx) \
                    TUD_AUDIO_DESC_FEATURE_UNIT_FOUR_CHANNEL_LEN, TUSB_DESC_CS_INTERFACE, AUDIO_CS_AC_INTERFACE_FEATURE_UNIT, _unitid, _srcid, U32_TO_U8S_LE(_ctrlch0master), U32_TO_U8S_LE(_ctrlch1), U32_TO_U8S_LE(_ctrlch2), U32_TO_U8S_LE(_ctrlch3), U32_TO_U8S_LE(_ctrlch4), _stridx

// 有关更多频道，请在此处添加定义

/* 标准AS接口描述符（4.9.1）*/
#define TUD_AUDIO_DESC_STD_AS_INT_LEN 9
#define TUD_AUDIO_DESC_STD_AS_INT(_itfnum, _altset, _nEPs, _stridx) \
  TUD_AUDIO_DESC_STD_AS_INT_LEN, TUSB_DESC_INTERFACE, _itfnum, _altset, _nEPs, TUSB_CLASS_AUDIO, AUDIO_SUBCLASS_STREAMING, AUDIO_INT_PROTOCOL_CODE_V2, _stridx

/* 类特定AS接口描述符（4.9.2）*/
#define TUD_AUDIO_DESC_CS_AS_INT_LEN 16
#define TUD_AUDIO_DESC_CS_AS_INT(_termid, _ctrl, _formattype, _formats, _nchannelsphysical, _channelcfg, _stridx) \
  TUD_AUDIO_DESC_CS_AS_INT_LEN, TUSB_DESC_CS_INTERFACE, AUDIO_CS_AS_INTERFACE_AS_GENERAL, _termid, _ctrl, _formattype, U32_TO_U8S_LE(_formats), _nchannelsphysical, U32_TO_U8S_LE(_channelcfg), _stridx

/* I类格式类型描述符（2.3.1.6-音频格式）*/
#define TUD_AUDIO_DESC_TYPE_I_FORMAT_LEN 6
#define TUD_AUDIO_DESC_TYPE_I_FORMAT(_subslotsize, _bitresolution) /* _子时隙大小是每个样本（即子时隙）的字节数，可以是1、2、3或4*/\
  TUD_AUDIO_DESC_TYPE_I_FORMAT_LEN, TUSB_DESC_CS_INTERFACE, AUDIO_CS_AS_INTERFACE_FORMAT_TYPE, AUDIO_FORMAT_TYPE_I, _subslotsize, _bitresolution

/* 标准AS等时音频数据端点描述符（4.10.1.1）*/
#define TUD_AUDIO_DESC_STD_AS_ISO_EP_LEN 7
#define TUD_AUDIO_DESC_STD_AS_ISO_EP(_ep, _attr, _maxEPsize, _interval) \
  TUD_AUDIO_DESC_STD_AS_ISO_EP_LEN, TUSB_DESC_ENDPOINT, _ep, _attr, U16_TO_U8S_LE(_maxEPsize), _interval

/* 类特定AS等时音频数据端点描述符（4.10.1.2）*/
#define TUD_AUDIO_DESC_CS_AS_ISO_EP_LEN 8
#define TUD_AUDIO_DESC_CS_AS_ISO_EP(_attr, _ctrl, _lockdelayunit, _lockdelay) \
  TUD_AUDIO_DESC_CS_AS_ISO_EP_LEN, TUSB_DESC_CS_ENDPOINT, AUDIO_CS_EP_SUBTYPE_GENERAL, _attr, _ctrl, _lockdelayunit, U16_TO_U8S_LE(_lockdelay)

/* 标准AS等时反馈端点描述符（4.10.2.1）*/
#define TUD_AUDIO_DESC_STD_AS_ISO_FB_EP_LEN 7
#define TUD_AUDIO_DESC_STD_AS_ISO_FB_EP(_ep, _interval) \
  TUD_AUDIO_DESC_STD_AS_ISO_FB_EP_LEN, TUSB_DESC_ENDPOINT, _ep, (TUSB_XFER_ISOCHRONOUS | TUSB_ISO_EP_ATT_NO_SYNC | TUSB_ISO_EP_ATT_EXPLICIT_FB), U16_TO_U8S_LE(4), _interval

// 1个麦克风输入的音频简单描述符（UAC2）
// -1个输入端子、1个功能单元（静音和音量控制）、1个输出端子和1个时钟源

#define TUD_AUDIO_MIC_ONE_CH_DESC_LEN (TUD_AUDIO_DESC_IAD_LEN\
  + TUD_AUDIO_DESC_STD_AC_LEN\
  + TUD_AUDIO_DESC_CS_AC_LEN\
  + TUD_AUDIO_DESC_CLK_SRC_LEN\
  + TUD_AUDIO_DESC_INPUT_TERM_LEN\
  + TUD_AUDIO_DESC_OUTPUT_TERM_LEN\
  + TUD_AUDIO_DESC_FEATURE_UNIT_ONE_CHANNEL_LEN\
  + TUD_AUDIO_DESC_STD_AS_INT_LEN\
  + TUD_AUDIO_DESC_STD_AS_INT_LEN\
  + TUD_AUDIO_DESC_CS_AS_INT_LEN\
  + TUD_AUDIO_DESC_TYPE_I_FORMAT_LEN\
  + TUD_AUDIO_DESC_STD_AS_ISO_EP_LEN\
  + TUD_AUDIO_DESC_CS_AS_ISO_EP_LEN)

#define TUD_AUDIO_MIC_ONE_CH_DESC_N_AS_INT 1 	// AS接口数量

#define TUD_AUDIO_MIC_ONE_CH_DESCRIPTOR(_itfnum, _stridx, _nBytesPerSample, _nBitsUsedPerSample, _epin, _epsize) \
  /* 标准接口关联描述符（IAD）*/\
  TUD_AUDIO_DESC_IAD(/*_第一次*/ _itfnum, /*_硝酸盐*/ 0x02, /*_斯特里克斯*/ 0x00),\
  /* 标准交流接口描述符（4.7.1）*/\
  TUD_AUDIO_DESC_STD_AC(/*_itfnum公司*/ _itfnum, /*_nEP*/ 0x00, /*_斯特里克斯*/ _stridx),\
  /* 类特定AC接口头描述符（4.7.2）*/\
  TUD_AUDIO_DESC_CS_AC(/*_bcdADC*/ 0x0200, /*_类别*/ AUDIO_FUNC_MICROPHONE, /*_总计*/ TUD_AUDIO_DESC_CLK_SRC_LEN+TUD_AUDIO_DESC_INPUT_TERM_LEN+TUD_AUDIO_DESC_OUTPUT_TERM_LEN+TUD_AUDIO_DESC_FEATURE_UNIT_ONE_CHANNEL_LEN, /*_ctrl键*/ AUDIO_CS_AS_INTERFACE_CTRL_LATENCY_POS),\
  /* 时钟源描述符（4.7.2.1）*/\
  TUD_AUDIO_DESC_CLK_SRC(/*_clkid公司*/ 0x04, /*_属性*/ AUDIO_CLOCK_SOURCE_ATT_INT_FIX_CLK, /*_ctrl键*/ (AUDIO_CTRL_R << AUDIO_CLOCK_SOURCE_CTRL_CLK_FRQ_POS), /*_关联术语*/ 0x01,  /*_斯特里克斯*/ 0x00),\
  /* 输入终端描述符（4.7.2.4）*/\
  TUD_AUDIO_DESC_INPUT_TERM(/*_白蚁*/ 0x01, /*_术语类型*/ AUDIO_TERM_TYPE_IN_GENERIC_MIC, /*_关联术语*/ 0x03, /*_clkid公司*/ 0x04, /*_n信道逻辑的*/ 0x01, /*_频道配置文件*/ AUDIO_CHANNEL_CONFIG_NON_PREDEFINED, /*_idxchannel名称*/ 0x00, /*_ctrl键*/ AUDIO_CTRL_R << AUDIO_IN_TERM_CTRL_CONNECTOR_POS, /*_斯特里克斯*/ 0x00),\
  /* 输出端子描述符（4.7.2.5）*/\
  TUD_AUDIO_DESC_OUTPUT_TERM(/*_白蚁*/ 0x03, /*_术语类型*/ AUDIO_TERM_TYPE_USB_STREAMING, /*_关联术语*/ 0x01, /*_srcid公司*/ 0x02, /*_clkid公司*/ 0x04, /*_ctrl键*/ 0x0000, /*_斯特里克斯*/ 0x00),\
  /* 功能单元描述符（4.7.2.8）*/\
  TUD_AUDIO_DESC_FEATURE_UNIT_ONE_CHANNEL(/*_单位化的*/ 0x02, /*_srcid公司*/ 0x01, /*_ctrlch0主机*/ AUDIO_CTRL_RW << AUDIO_FEATURE_UNIT_CTRL_MUTE_POS | AUDIO_CTRL_RW << AUDIO_FEATURE_UNIT_CTRL_VOLUME_POS, /*_控制1*/ AUDIO_CTRL_RW << AUDIO_FEATURE_UNIT_CTRL_MUTE_POS | AUDIO_CTRL_RW << AUDIO_FEATURE_UNIT_CTRL_VOLUME_POS, /*_斯特里克斯*/ 0x00),\
  /* 标准AS接口描述符（4.9.1）*/\
  /* 接口1，备用0-默认备用设置，带宽为0*/\
  TUD_AUDIO_DESC_STD_AS_INT(/*_itfnum公司*/ (uint8_t)((_itfnum)+1), /*_阿尔特塞特*/ 0x00, /*_nEP*/ 0x00, /*_斯特里克斯*/ 0x00),\
  /* 标准AS接口描述符（4.9.1）*/\
  /* 接口1，备用1-数据流的备用接口*/\
  TUD_AUDIO_DESC_STD_AS_INT(/*_itfnum公司*/ (uint8_t)((_itfnum)+1), /*_阿尔特塞特*/ 0x01, /*_nEP*/ 0x01, /*_斯特里克斯*/ 0x00),\
  /* 类特定AS接口描述符（4.9.2）*/\
  TUD_AUDIO_DESC_CS_AS_INT(/*_白蚁*/ 0x03, /*_ctrl键*/ AUDIO_CTRL_NONE, /*_格式类型*/ AUDIO_FORMAT_TYPE_I, /*_格式*/ AUDIO_DATA_FORMAT_TYPE_I_PCM, /*_n信道物理*/ 0x01, /*_频道配置文件*/ AUDIO_CHANNEL_CONFIG_NON_PREDEFINED, /*_斯特里克斯*/ 0x00),\
  /* I类格式类型描述符（2.3.1.6-音频格式）*/\
  TUD_AUDIO_DESC_TYPE_I_FORMAT(_nBytesPerSample, _nBitsUsedPerSample),\
  /* 标准AS等时音频数据端点描述符（4.10.1.1）*/\
  TUD_AUDIO_DESC_STD_AS_ISO_EP(/*_环境保护部*/ _epin, /*_属性*/ (TUSB_XFER_ISOCHRONOUS | TUSB_ISO_EP_ATT_ASYNCHRONOUS | TUSB_ISO_EP_ATT_DATA), /*_最大EPsize*/ _epsize, /*_间隔，间隔*/ (CFG_TUSB_RHPORT0_MODE & OPT_MODE_HIGH_SPEED) ? 0x04 : 0x01),\
  /* 类特定AS等时音频数据端点描述符（4.10.1.2）*/\
  TUD_AUDIO_DESC_CS_AS_ISO_EP(/*_属性*/ AUDIO_CS_AS_ISO_DATA_EP_ATT_NON_MAX_PACKETS_OK, /*_ctrl键*/ AUDIO_CTRL_NONE, /*_洛克德拉尤尼特*/ AUDIO_CS_AS_ISO_DATA_EP_LOCK_DELAY_UNIT_UNDEFINED, /*_锁定延迟*/ 0x0000)

// 4麦克风输入的音频简单描述符（UAC2）
// -1个输入端子、1个功能单元（静音和音量控制）、1个输出端子和1个时钟源

#define TUD_AUDIO_MIC_FOUR_CH_DESC_LEN (TUD_AUDIO_DESC_IAD_LEN\
  + TUD_AUDIO_DESC_STD_AC_LEN\
  + TUD_AUDIO_DESC_CS_AC_LEN\
  + TUD_AUDIO_DESC_CLK_SRC_LEN\
  + TUD_AUDIO_DESC_INPUT_TERM_LEN\
  + TUD_AUDIO_DESC_OUTPUT_TERM_LEN\
  + TUD_AUDIO_DESC_FEATURE_UNIT_FOUR_CHANNEL_LEN\
  + TUD_AUDIO_DESC_STD_AS_INT_LEN\
  + TUD_AUDIO_DESC_STD_AS_INT_LEN\
  + TUD_AUDIO_DESC_CS_AS_INT_LEN\
  + TUD_AUDIO_DESC_TYPE_I_FORMAT_LEN\
  + TUD_AUDIO_DESC_STD_AS_ISO_EP_LEN\
  + TUD_AUDIO_DESC_CS_AS_ISO_EP_LEN)

#define TUD_AUDIO_MIC_FOUR_CH_DESC_N_AS_INT 1   // AS接口数量

#define TUD_AUDIO_MIC_FOUR_CH_DESCRIPTOR(_itfnum, _stridx, _nBytesPerSample, _nBitsUsedPerSample, _epin, _epsize) \
  /* 标准接口关联描述符（IAD）*/\
  TUD_AUDIO_DESC_IAD(/*_第一次*/ _itfnum, /*_硝酸盐*/ 0x02, /*_斯特里克斯*/ 0x00),\
  /* 标准交流接口描述符（4.7.1）*/\
  TUD_AUDIO_DESC_STD_AC(/*_itfnum公司*/ _itfnum, /*_nEP*/ 0x00, /*_斯特里克斯*/ _stridx),\
  /* 类特定AC接口头描述符（4.7.2）*/\
  TUD_AUDIO_DESC_CS_AC(/*_bcdADC*/ 0x0200, /*_类别*/ AUDIO_FUNC_MICROPHONE, /*_总计*/ TUD_AUDIO_DESC_CLK_SRC_LEN+TUD_AUDIO_DESC_INPUT_TERM_LEN+TUD_AUDIO_DESC_OUTPUT_TERM_LEN+TUD_AUDIO_DESC_FEATURE_UNIT_FOUR_CHANNEL_LEN, /*_ctrl键*/ AUDIO_CS_AS_INTERFACE_CTRL_LATENCY_POS),\
  /* 时钟源描述符（4.7.2.1）*/\
  TUD_AUDIO_DESC_CLK_SRC(/*_clkid公司*/ 0x04, /*_属性*/ AUDIO_CLOCK_SOURCE_ATT_INT_FIX_CLK, /*_ctrl键*/ (AUDIO_CTRL_R << AUDIO_CLOCK_SOURCE_CTRL_CLK_FRQ_POS), /*_关联术语*/ 0x01,  /*_斯特里克斯*/ 0x00),\
  /* 输入终端描述符（4.7.2.4）*/\
  TUD_AUDIO_DESC_INPUT_TERM(/*_白蚁*/ 0x01, /*_术语类型*/ AUDIO_TERM_TYPE_IN_GENERIC_MIC, /*_关联术语*/ 0x03, /*_clkid公司*/ 0x04, /*_n信道逻辑的*/ 0x04, /*_频道配置文件*/ AUDIO_CHANNEL_CONFIG_NON_PREDEFINED, /*_idxchannel名称*/ 0x00, /*_ctrl键*/ AUDIO_CTRL_R << AUDIO_IN_TERM_CTRL_CONNECTOR_POS, /*_斯特里克斯*/ 0x00),\
  /* 输出端子描述符（4.7.2.5）*/\
  TUD_AUDIO_DESC_OUTPUT_TERM(/*_白蚁*/ 0x03, /*_术语类型*/ AUDIO_TERM_TYPE_USB_STREAMING, /*_关联术语*/ 0x01, /*_srcid公司*/ 0x02, /*_clkid公司*/ 0x04, /*_ctrl键*/ 0x0000, /*_斯特里克斯*/ 0x00),\
  /* 功能单元描述符（4.7.2.8）*/\
  TUD_AUDIO_DESC_FEATURE_UNIT_FOUR_CHANNEL(/*_单位化的*/ 0x02, /*_srcid公司*/ 0x01, /*_ctrlch0主机*/ AUDIO_CTRL_RW << AUDIO_FEATURE_UNIT_CTRL_MUTE_POS | AUDIO_CTRL_RW << AUDIO_FEATURE_UNIT_CTRL_VOLUME_POS, /*_控制1*/ AUDIO_CTRL_RW << AUDIO_FEATURE_UNIT_CTRL_MUTE_POS | AUDIO_CTRL_RW << AUDIO_FEATURE_UNIT_CTRL_VOLUME_POS, /*_控制2*/ AUDIO_CTRL_RW << AUDIO_FEATURE_UNIT_CTRL_MUTE_POS | AUDIO_CTRL_RW << AUDIO_FEATURE_UNIT_CTRL_VOLUME_POS, /*_控制3*/ AUDIO_CTRL_RW << AUDIO_FEATURE_UNIT_CTRL_MUTE_POS | AUDIO_CTRL_RW << AUDIO_FEATURE_UNIT_CTRL_VOLUME_POS, /*_控制4*/ AUDIO_CTRL_RW << AUDIO_FEATURE_UNIT_CTRL_MUTE_POS | AUDIO_CTRL_RW << AUDIO_FEATURE_UNIT_CTRL_VOLUME_POS, /*_斯特里克斯*/ 0x00),\
  /* 标准AS接口描述符（4.9.1）*/\
  /* 接口1，备用0-默认备用设置，带宽为0*/\
  TUD_AUDIO_DESC_STD_AS_INT(/*_itfnum公司*/ (uint8_t)((_itfnum)+1), /*_阿尔特塞特*/ 0x00, /*_nEP*/ 0x00, /*_斯特里克斯*/ 0x00),\
  /* 标准AS接口描述符（4.9.1）*/\
  /* 接口1，备用1-数据流的备用接口*/\
  TUD_AUDIO_DESC_STD_AS_INT(/*_itfnum公司*/ (uint8_t)((_itfnum)+1), /*_阿尔特塞特*/ 0x01, /*_nEP*/ 0x01, /*_斯特里克斯*/ 0x00),\
  /* 类特定AS接口描述符（4.9.2）*/\
  TUD_AUDIO_DESC_CS_AS_INT(/*_白蚁*/ 0x03, /*_ctrl键*/ AUDIO_CTRL_NONE, /*_格式类型*/ AUDIO_FORMAT_TYPE_I, /*_格式*/ AUDIO_DATA_FORMAT_TYPE_I_PCM, /*_n信道物理*/ 0x04, /*_频道配置文件*/ AUDIO_CHANNEL_CONFIG_NON_PREDEFINED, /*_斯特里克斯*/ 0x00),\
  /* I类格式类型描述符（2.3.1.6-音频格式）*/\
  TUD_AUDIO_DESC_TYPE_I_FORMAT(_nBytesPerSample, _nBitsUsedPerSample),\
  /* 标准AS等时音频数据端点描述符（4.10.1.1）*/\
  TUD_AUDIO_DESC_STD_AS_ISO_EP(/*_环境保护部*/ _epin, /*_属性*/ (TUSB_XFER_ISOCHRONOUS | TUSB_ISO_EP_ATT_ASYNCHRONOUS | TUSB_ISO_EP_ATT_DATA), /*_最大EPsize*/ _epsize, /*_间隔，间隔*/ (CFG_TUSB_RHPORT0_MODE & OPT_MODE_HIGH_SPEED) ? 0x04 : 0x01),\
  /* 类特定AS等时音频数据端点描述符（4.10.1.2）*/\
  TUD_AUDIO_DESC_CS_AS_ISO_EP(/*_属性*/ AUDIO_CS_AS_ISO_DATA_EP_ATT_NON_MAX_PACKETS_OK, /*_ctrl键*/ AUDIO_CTRL_NONE, /*_洛克德拉尤尼特*/ AUDIO_CS_AS_ISO_DATA_EP_LOCK_DELAY_UNIT_UNDEFINED, /*_锁定延迟*/ 0x0000)

// 单声道扬声器的音频简单描述符（UAC2）
// -1个输入端子，2个功能单元（静音和音量控制），3个输出端子，4个时钟源

#define TUD_AUDIO_SPEAKER_MONO_FB_DESC_LEN (TUD_AUDIO_DESC_IAD_LEN\
  + TUD_AUDIO_DESC_STD_AC_LEN\
  + TUD_AUDIO_DESC_CS_AC_LEN\
  + TUD_AUDIO_DESC_CLK_SRC_LEN\
  + TUD_AUDIO_DESC_INPUT_TERM_LEN\
  + TUD_AUDIO_DESC_OUTPUT_TERM_LEN\
  + TUD_AUDIO_DESC_FEATURE_UNIT_ONE_CHANNEL_LEN\
  + TUD_AUDIO_DESC_STD_AS_INT_LEN\
  + TUD_AUDIO_DESC_STD_AS_INT_LEN\
  + TUD_AUDIO_DESC_CS_AS_INT_LEN\
  + TUD_AUDIO_DESC_TYPE_I_FORMAT_LEN\
  + TUD_AUDIO_DESC_STD_AS_ISO_EP_LEN\
  + TUD_AUDIO_DESC_CS_AS_ISO_EP_LEN\
  + TUD_AUDIO_DESC_STD_AS_ISO_FB_EP_LEN)

#define TUD_AUDIO_SPEAKER_MONO_FB_DESCRIPTOR(_itfnum, _stridx, _nBytesPerSample, _nBitsUsedPerSample, _epout, _epsize, _epfb) \
  /* 标准接口关联描述符（IAD）*/\
  TUD_AUDIO_DESC_IAD(/*_第一次*/ _itfnum, /*_硝酸盐*/ 0x02, /*_斯特里克斯*/ 0x00),\
  /* 标准交流接口描述符（4.7.1）*/\
  TUD_AUDIO_DESC_STD_AC(/*_itfnum公司*/ _itfnum, /*_nEP*/ 0x00, /*_斯特里克斯*/ _stridx),\
  /* 类特定AC接口头描述符（4.7.2）*/\
  TUD_AUDIO_DESC_CS_AC(/*_bcdADC*/ 0x0200, /*_类别*/ AUDIO_FUNC_DESKTOP_SPEAKER, /*_总计*/ TUD_AUDIO_DESC_CLK_SRC_LEN+TUD_AUDIO_DESC_INPUT_TERM_LEN+TUD_AUDIO_DESC_OUTPUT_TERM_LEN+TUD_AUDIO_DESC_FEATURE_UNIT_ONE_CHANNEL_LEN, /*_ctrl键*/ AUDIO_CS_AS_INTERFACE_CTRL_LATENCY_POS),\
  /* 时钟源描述符（4.7.2.1）*/\
  TUD_AUDIO_DESC_CLK_SRC(/*_clkid公司*/ 0x04, /*_属性*/ AUDIO_CLOCK_SOURCE_ATT_INT_FIX_CLK, /*_ctrl键*/ (AUDIO_CTRL_R << AUDIO_CLOCK_SOURCE_CTRL_CLK_FRQ_POS), /*_关联术语*/ 0x01,  /*_斯特里克斯*/ 0x00),\
  /* 输入终端描述符（4.7.2.4）*/\
  TUD_AUDIO_DESC_INPUT_TERM(/*_白蚁*/ 0x01, /*_术语类型*/ AUDIO_TERM_TYPE_USB_STREAMING, /*_关联术语*/ 0x00, /*_clkid公司*/ 0x04, /*_n信道逻辑的*/ 0x01, /*_频道配置文件*/ AUDIO_CHANNEL_CONFIG_NON_PREDEFINED, /*_idxchannel名称*/ 0x00, /*_ctrl键*/ 0 * (AUDIO_CTRL_R << AUDIO_IN_TERM_CTRL_CONNECTOR_POS), /*_斯特里克斯*/ 0x00),\
  /* 输出端子描述符（4.7.2.5）*/\
  TUD_AUDIO_DESC_OUTPUT_TERM(/*_白蚁*/ 0x03, /*_术语类型*/ AUDIO_TERM_TYPE_OUT_DESKTOP_SPEAKER, /*_关联术语*/ 0x01, /*_srcid公司*/ 0x02, /*_clkid公司*/ 0x04, /*_ctrl键*/ 0x0000, /*_斯特里克斯*/ 0x00),\
  /* 功能单元描述符（4.7.2.8）*/\
  TUD_AUDIO_DESC_FEATURE_UNIT_ONE_CHANNEL(/*_单位化的*/ 0x02, /*_srcid公司*/ 0x01, /*_ctrlch0主机*/ 0 * (AUDIO_CTRL_RW << AUDIO_FEATURE_UNIT_CTRL_MUTE_POS | AUDIO_CTRL_RW << AUDIO_FEATURE_UNIT_CTRL_VOLUME_POS), /*_控制1*/ 0 * (AUDIO_CTRL_RW << AUDIO_FEATURE_UNIT_CTRL_MUTE_POS | AUDIO_CTRL_RW << AUDIO_FEATURE_UNIT_CTRL_VOLUME_POS), /*_斯特里克斯*/ 0x00),\
  /* 标准AS接口描述符（4.9.1）*/\
  /* 接口1，备用0-默认备用设置，带宽为0*/\
  TUD_AUDIO_DESC_STD_AS_INT(/*_itfnum公司*/ (uint8_t)((_itfnum) + 1), /*_阿尔特塞特*/ 0x00, /*_nEP*/ 0x00, /*_斯特里克斯*/ 0x00),\
  /* 标准AS接口描述符（4.9.1）*/\
  /* 接口1，备用1-数据流的备用接口*/\
  TUD_AUDIO_DESC_STD_AS_INT(/*_itfnum公司*/ (uint8_t)((_itfnum) + 1), /*_阿尔特塞特*/ 0x01, /*_nEP*/ 0x02, /*_斯特里克斯*/ 0x00),\
  /* 类特定AS接口描述符（4.9.2）*/\
  TUD_AUDIO_DESC_CS_AS_INT(/*_白蚁*/ 0x01, /*_ctrl键*/ AUDIO_CTRL_NONE, /*_格式类型*/ AUDIO_FORMAT_TYPE_I, /*_格式*/ AUDIO_DATA_FORMAT_TYPE_I_PCM, /*_n信道物理*/ 0x01, /*_频道配置文件*/ AUDIO_CHANNEL_CONFIG_NON_PREDEFINED, /*_斯特里克斯*/ 0x00),\
  /* I类格式类型描述符（2.3.1.6-音频格式）*/\
  TUD_AUDIO_DESC_TYPE_I_FORMAT(_nBytesPerSample, _nBitsUsedPerSample),\
  /* 标准AS等时音频数据端点描述符（4.10.1.1）*/\
  TUD_AUDIO_DESC_STD_AS_ISO_EP(/*_环境保护部*/ _epout, /*_属性*/ (TUSB_XFER_ISOCHRONOUS | TUSB_ISO_EP_ATT_ASYNCHRONOUS | TUSB_ISO_EP_ATT_DATA), /*_最大EPsize*/ _epsize, /*_间隔，间隔*/ (CFG_TUSB_RHPORT0_MODE & OPT_MODE_HIGH_SPEED) ? 0x04 : 0x01),\
  /* 类特定AS等时音频数据端点描述符（4.10.1.2）*/\
  TUD_AUDIO_DESC_CS_AS_ISO_EP(/*_属性*/ AUDIO_CS_AS_ISO_DATA_EP_ATT_NON_MAX_PACKETS_OK, /*_ctrl键*/ AUDIO_CTRL_NONE, /*_洛克德拉尤尼特*/ AUDIO_CS_AS_ISO_DATA_EP_LOCK_DELAY_UNIT_UNDEFINED, /*_锁定延迟*/ 0x0000),\
  /* 标准AS等时反馈端点描述符（4.10.2.1）*/\
  TUD_AUDIO_DESC_STD_AS_ISO_FB_EP(/*_环境保护部*/ _epfb, /*_间隔，间隔*/ 1)\

//------------- TUD_USBTMC/USB488 -------------//
#define TUD_USBTMC_APP_CLASS    (TUSB_CLASS_APPLICATION_SPECIFIC)
#define TUD_USBTMC_APP_SUBCLASS 0x03u

#define TUD_USBTMC_PROTOCOL_STD    0x00u
#define TUD_USBTMC_PROTOCOL_USB488 0x01u

//   接口编号、端点数量、EP字符串索引、USB_TMC_PROTOCOL*、批量输出端点ID、，
//   批量输入端点ID
#define TUD_USBTMC_IF_DESCRIPTOR(_itfnum, _bNumEndpoints, _stridx, _itfProtocol) \
  /* 界面*/ \
  0x09, TUSB_DESC_INTERFACE, _itfnum, 0x00, _bNumEndpoints, TUD_USBTMC_APP_CLASS, TUD_USBTMC_APP_SUBCLASS, _itfProtocol, _stridx

#define TUD_USBTMC_IF_DESCRIPTOR_LEN 9u

#define TUD_USBTMC_BULK_DESCRIPTORS(_epout, _epin, _bulk_epsize) \
  /* 端点输出*/ \
  7, TUSB_DESC_ENDPOINT, _epout, TUSB_XFER_BULK, U16_TO_U8S_LE(_bulk_epsize), 0u, \
  /* 端点输入*/ \
  7, TUSB_DESC_ENDPOINT, _epin, TUSB_XFER_BULK, U16_TO_U8S_LE(_bulk_epsize), 0u

#define TUD_USBTMC_BULK_DESCRIPTORS_LEN (7u+7u)

/* 可选中断端点*/ \
// _int_pollingInterval：对于LS/FS，以帧（每帧1ms）表示。16可能是个好数字？
#define TUD_USBTMC_INT_DESCRIPTOR(_ep_interrupt, _ep_interrupt_size, _int_pollingInterval ) \
  7, TUSB_DESC_ENDPOINT, _ep_interrupt, TUSB_XFER_INTERRUPT, U16_TO_U8S_LE(_ep_interrupt_size), 0x16

#define TUD_USBTMC_INT_DESCRIPTOR_LEN (7u)


//-------------供应商-------------//
#define TUD_VENDOR_DESC_LEN  (9+7+7)

// 接口编号、字符串索引、EP输出和输入地址、EP大小
#define TUD_VENDOR_DESCRIPTOR(_itfnum, _stridx, _epout, _epin, _epsize) \
  /* 界面*/\
  9, TUSB_DESC_INTERFACE, _itfnum, 0, 2, TUSB_CLASS_VENDOR_SPECIFIC, 0x00, 0x00, _stridx,\
  /* 端点输出*/\
  7, TUSB_DESC_ENDPOINT, _epout, TUSB_XFER_BULK, U16_TO_U8S_LE(_epsize), 0,\
  /* 端点输入*/\
  7, TUSB_DESC_ENDPOINT, _epin, TUSB_XFER_BULK, U16_TO_U8S_LE(_epsize), 0

//-------------DFU运行时-------------//
#define TUD_DFU_APP_CLASS    (TUSB_CLASS_APPLICATION_SPECIFIC)
#define TUD_DFU_APP_SUBCLASS 0x01u

// 模板描述符长度：18字节
#define TUD_DFU_RT_DESC_LEN (9 + 9)

// DFU运行时描述符
// 接口编号、字符串索引、属性、分离超时、传输大小
#define TUD_DFU_RT_DESCRIPTOR(_itfnum, _stridx, _attr, _timeout, _xfer_size) \
  /* 界面*/ \
  9, TUSB_DESC_INTERFACE, _itfnum, 0, 0, TUD_DFU_APP_CLASS, TUD_DFU_APP_SUBCLASS, DFU_PROTOCOL_RT, _stridx, \
  /* 作用*/ \
  9, DFU_DESC_FUNCTIONAL, _attr, U16_TO_U8S_LE(_timeout), U16_TO_U8S_LE(_xfer_size), U16_TO_U8S_LE(0x0101)


//------------- CDC-ECM -------------//

// 模板描述符长度：71字节
#define TUD_CDC_ECM_DESC_LEN  (8+9+5+5+13+7+9+9+7+7)

// CDC-ECM描述符模板
// 接口编号、描述字符串索引、MAC地址字符串索引、EP通知地址和大小、EP数据地址（输出、输入）和大小、最大段大小。
#define TUD_CDC_ECM_DESCRIPTOR(_itfnum, _desc_stridx, _mac_stridx, _ep_notif, _ep_notif_size, _epout, _epin, _epsize, _maxsegmentsize) \
  /* 接口关联*/\
  8, TUSB_DESC_INTERFACE_ASSOCIATION, _itfnum, 2, TUSB_CLASS_CDC, CDC_COMM_SUBCLASS_ETHERNET_CONTROL_MODEL, 0, 0,\
  /* CDC控制接口*/\
  9, TUSB_DESC_INTERFACE, _itfnum, 0, 1, TUSB_CLASS_CDC, CDC_COMM_SUBCLASS_ETHERNET_CONTROL_MODEL, 0, _desc_stridx,\
  /* CDC-ECM收割台*/\
  5, TUSB_DESC_CS_INTERFACE, CDC_FUNC_DESC_HEADER, U16_TO_U8S_LE(0x0120),\
  /* CDC-ECM接头*/\
  5, TUSB_DESC_CS_INTERFACE, CDC_FUNC_DESC_UNION, _itfnum, (uint8_t)((_itfnum) + 1),\
  /* CDC-ECM功能描述符*/\
  13, TUSB_DESC_CS_INTERFACE, CDC_FUNC_DESC_ETHERNET_NETWORKING, _mac_stridx, 0, 0, 0, 0, U16_TO_U8S_LE(_maxsegmentsize), U16_TO_U8S_LE(0), 0,\
  /* 终结点通知*/\
  7, TUSB_DESC_ENDPOINT, _ep_notif, TUSB_XFER_INTERRUPT, U16_TO_U8S_LE(_ep_notif_size), 1,\
  /* CDC数据接口（默认为非活动）*/\
  9, TUSB_DESC_INTERFACE, (uint8_t)((_itfnum)+1), 0, 0, TUSB_CLASS_CDC_DATA, 0, 0, 0,\
  /* CDC数据接口（替代激活）*/\
  9, TUSB_DESC_INTERFACE, (uint8_t)((_itfnum)+1), 1, 2, TUSB_CLASS_CDC_DATA, 0, 0, 0,\
  /* 端点输入*/\
  7, TUSB_DESC_ENDPOINT, _epin, TUSB_XFER_BULK, U16_TO_U8S_LE(_epsize), 0,\
  /* 端点输出*/\
  7, TUSB_DESC_ENDPOINT, _epout, TUSB_XFER_BULK, U16_TO_U8S_LE(_epsize), 0


//------------- RNDIS -------------//

#if 0
/* Windows XP*/
#define TUD_RNDIS_ITF_CLASS    TUSB_CLASS_CDC
#define TUD_RNDIS_ITF_SUBCLASS CDC_COMM_SUBCLASS_ABSTRACT_CONTROL_MODEL
#define TUD_RNDIS_ITF_PROTOCOL 0xFF /* CDC_COMM_PROTOCOL_MICROSOFT_RNDIS */
#else
/* Windows 7+*/
#define TUD_RNDIS_ITF_CLASS    TUSB_CLASS_WIRELESS_CONTROLLER
#define TUD_RNDIS_ITF_SUBCLASS 0x01
#define TUD_RNDIS_ITF_PROTOCOL 0x03
#endif

// 模板描述符长度：66字节
#define TUD_RNDIS_DESC_LEN  (8+9+5+5+4+5+7+9+7+7)

// RNDIS描述符模板
// 接口编号、字符串索引、EP通知地址和大小、EP数据地址（输出、输入）和大小。
#define TUD_RNDIS_DESCRIPTOR(_itfnum, _stridx, _ep_notif, _ep_notif_size, _epout, _epin, _epsize) \
  /* 接口关联*/\
  8, TUSB_DESC_INTERFACE_ASSOCIATION, _itfnum, 2, TUD_RNDIS_ITF_CLASS, TUD_RNDIS_ITF_SUBCLASS, TUD_RNDIS_ITF_PROTOCOL, 0,\
  /* CDC控制接口*/\
  9, TUSB_DESC_INTERFACE, _itfnum, 0, 1, TUD_RNDIS_ITF_CLASS, TUD_RNDIS_ITF_SUBCLASS, TUD_RNDIS_ITF_PROTOCOL, _stridx,\
  /* CDC-ACM标题*/\
  5, TUSB_DESC_CS_INTERFACE, CDC_FUNC_DESC_HEADER, U16_TO_U8S_LE(0x0110),\
  /* CDC呼叫管理*/\
  5, TUSB_DESC_CS_INTERFACE, CDC_FUNC_DESC_CALL_MANAGEMENT, 0, (uint8_t)((_itfnum) + 1),\
  /* ACM */\
  4, TUSB_DESC_CS_INTERFACE, CDC_FUNC_DESC_ABSTRACT_CONTROL_MANAGEMENT, 0,\
  /* CDC联盟*/\
  5, TUSB_DESC_CS_INTERFACE, CDC_FUNC_DESC_UNION, _itfnum, (uint8_t)((_itfnum) + 1),\
  /* 终结点通知*/\
  7, TUSB_DESC_ENDPOINT, _ep_notif, TUSB_XFER_INTERRUPT, U16_TO_U8S_LE(_ep_notif_size), 1,\
  /* CDC数据接口*/\
  9, TUSB_DESC_INTERFACE, (uint8_t)((_itfnum)+1), 0, 2, TUSB_CLASS_CDC_DATA, 0, 0, 0,\
  /* 端点输入*/\
  7, TUSB_DESC_ENDPOINT, _epin, TUSB_XFER_BULK, U16_TO_U8S_LE(_epsize), 0,\
  /* 端点输出*/\
  7, TUSB_DESC_ENDPOINT, _epout, TUSB_XFER_BULK, U16_TO_U8S_LE(_epsize), 0

//-------------BT收音机-------------//
#define TUD_BT_APP_CLASS                    (TUSB_CLASS_WIRELESS_CONTROLLER)
#define TUD_BT_APP_SUBCLASS                 0x01
#define TUD_BT_PROTOCOL_PRIMARY_CONTROLLER  0x01
#define TUD_BT_PROTOCOL_AMP_CONTROLLER      0x02

#ifndef CFG_TUD_BTH_ISO_ALT_COUNT
#define CFG_TUD_BTH_ISO_ALT_COUNT 0
#endif

// 模板描述符长度：30字节+ISO替代品数量*23
#define TUD_BTH_DESC_LEN (9 + 7 + 7 + 7 + (CFG_TUD_BTH_ISO_ALT_COUNT) * (9 + 7 + 7))

/* 主要接口*/
#define TUD_BTH_PRI_ITF(_itfnum, _stridx, _ep_evt, _ep_evt_size, _ep_evt_interval, _ep_in, _ep_out, _ep_size) \
  9, TUSB_DESC_INTERFACE, _itfnum, _stridx, 3, TUD_BT_APP_CLASS, TUD_BT_APP_SUBCLASS, TUD_BT_PROTOCOL_PRIMARY_CONTROLLER, 0, \
  /* 事件的终结点输入*/ \
  7, TUSB_DESC_ENDPOINT, _ep_evt, TUSB_XFER_INTERRUPT, U16_TO_U8S_LE(_ep_evt_size), _ep_evt_interval, \
  /* ACL数据的终结点输入*/ \
  7, TUSB_DESC_ENDPOINT, _ep_in, TUSB_XFER_BULK, U16_TO_U8S_LE(_ep_size), 1, \
  /* ACL数据的终结点输出*/ \
  7, TUSB_DESC_ENDPOINT, _ep_out, TUSB_XFER_BULK, U16_TO_U8S_LE(_ep_size), 1

#define TUD_BTH_ISO_ITF(_itfnum, _alt, _ep_in, _ep_out, _n) ,\
  /* 具有2个端点的接口*/ \
  9, TUSB_DESC_INTERFACE, _itfnum, _alt, 2, TUD_BT_APP_CLASS, TUD_BT_APP_SUBCLASS, TUD_BT_PROTOCOL_PRIMARY_CONTROLLER, 0, \
  /* 等时终点*/ \
  7, TUSB_DESC_ENDPOINT, _ep_in, TUSB_XFER_ISOCHRONOUS, U16_TO_U8S_LE(_n), 1, \
  7, TUSB_DESC_ENDPOINT, _ep_out, TUSB_XFER_ISOCHRONOUS, U16_TO_U8S_LE(_n), 1

#define _FIRST(a, ...) a
#define _REST(a, ...) __VA_ARGS__

#define TUD_BTH_ISO_ITF_0(_itfnum, ...)
#define TUD_BTH_ISO_ITF_1(_itfnum, _ep_in, _ep_out, ...) TUD_BTH_ISO_ITF(_itfnum, (CFG_TUD_BTH_ISO_ALT_COUNT) - 1, _ep_in, _ep_out, _FIRST(__VA_ARGS__))
#define TUD_BTH_ISO_ITF_2(_itfnum, _ep_in, _ep_out, ...) TUD_BTH_ISO_ITF(_itfnum, (CFG_TUD_BTH_ISO_ALT_COUNT) - 2, _ep_in, _ep_out, _FIRST(__VA_ARGS__)) \
  TUD_BTH_ISO_ITF_1(_itfnum, _ep_in, _ep_out, _REST(__VA_ARGS__))
#define TUD_BTH_ISO_ITF_3(_itfnum, _ep_in, _ep_out, ...) TUD_BTH_ISO_ITF(_itfnum, (CFG_TUD_BTH_ISO_ALT_COUNT) - 3, _ep_in, _ep_out, _FIRST(__VA_ARGS__)) \
  TUD_BTH_ISO_ITF_2(_itfnum, _ep_in, _ep_out, _REST(__VA_ARGS__))
#define TUD_BTH_ISO_ITF_4(_itfnum, _ep_in, _ep_out, ...) TUD_BTH_ISO_ITF(_itfnum, (CFG_TUD_BTH_ISO_ALT_COUNT) - 4, _ep_in, _ep_out, _FIRST(__VA_ARGS__)) \
  TUD_BTH_ISO_ITF_3(_itfnum, _ep_in, _ep_out, _REST(__VA_ARGS__))
#define TUD_BTH_ISO_ITF_5(_itfnum, _ep_in, _ep_out, ...) TUD_BTH_ISO_ITF(_itfnum, (CFG_TUD_BTH_ISO_ALT_COUNT) - 5, _ep_in, _ep_out, _FIRST(__VA_ARGS__)) \
  TUD_BTH_ISO_ITF_4(_itfnum, _ep_in, _ep_out, _REST(__VA_ARGS__))
#define TUD_BTH_ISO_ITF_6(_itfnum, _ep_in, _ep_out, ...) TUD_BTH_ISO_ITF(_itfnum, (CFG_TUD_BTH_ISO_ALT_COUNT) - 6, _ep_in, _ep_out, _FIRST(__VA_ARGS__)) \
  TUD_BTH_ISO_ITF_5(_itfnum, _ep_in, _ep_out, _REST(__VA_ARGS__))

#define TUD_BTH_ISO_ITFS(_itfnum, _ep_in, _ep_out, ...) \
  TU_XSTRCAT(TUD_BTH_ISO_ITF_, CFG_TUD_BTH_ISO_ALT_COUNT)(_itfnum, _ep_in, _ep_out, __VA_ARGS__)

// BT主控制器描述符
// 接口编号、字符串索引、属性、事件端点、事件端点大小、间隔、数据输入、数据输出、数据端点大小、iso端点大小
#define TUD_BTH_DESCRIPTOR(_itfnum, _stridx, _ep_evt, _ep_evt_size, _ep_evt_interval, _ep_in, _ep_out, _ep_size,...) \
  TUD_BTH_PRI_ITF(_itfnum, _stridx, _ep_evt, _ep_evt_size, _ep_evt_interval, _ep_in, _ep_out, _ep_size) \
  TUD_BTH_ISO_ITFS(_itfnum + 1, _ep_in + 1, _ep_out + 1, __VA_ARGS__)

#ifdef __cplusplus
}
#endif

#endif /* _TUSB_USBD_H_ */

/** @} */

