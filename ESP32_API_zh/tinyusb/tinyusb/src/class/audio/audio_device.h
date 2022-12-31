/* 
 * MIT许可证（MIT）
 *
 * 版权所有（c）2020 Ha Thach（tinyusb.org）版权所有（c）2020 Reinhard Panhuber
 *
 * 特此免费授予获得本软件和相关文档文件（“软件”）副本的任何人无限制地处理软件的权利，包括但不限于使用、复制、修改、合并、发布、分发、再许可和/或销售软件副本的权利，并允许向其提供软件的人这样做，符合以下条件：
 *
 * 上述版权声明和本许可声明应包含在软件的所有副本或主要部分中。
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * 此文件是TinyUSB堆栈的一部分。
 */

#ifndef _TUSB_AUDIO_DEVICE_H_
#define _TUSB_AUDIO_DEVICE_H_

#include "assert.h"
#include "common/tusb_common.h"
#include "device/usbd.h"

#include "audio.h"

//--------------------------------------------------------------------+
// 类驱动程序配置
//--------------------------------------------------------------------+

// 所有大小均以字节为单位！

#ifndef CFG_TUD_AUDIO_FUNC_1_DESC_LEN
#error You must tell the driver the length of the audio function descriptor including IAD descriptor
#endif
#if CFG_TUD_AUDIO > 1
#ifndef CFG_TUD_AUDIO_FUNC_2_DESC_LEN
#error You must tell the driver the length of the audio function descriptor including IAD descriptor
#endif
#endif
#if CFG_TUD_AUDIO > 2
#ifndef CFG_TUD_AUDIO_FUNC_3_DESC_LEN
#error You must tell the driver the length of the audio function descriptor including IAD descriptor
#endif
#endif

// 每个音频功能定义的标准AS接口描述符（4.9.1）的数量-需要能够记住这些接口的当前替代设置
#ifndef CFG_TUD_AUDIO_FUNC_1_N_AS_INT
#error You must tell the driver the number of Standard AS Interface Descriptors you have defined in the audio function descriptor!
#endif
#if CFG_TUD_AUDIO > 1
#ifndef CFG_TUD_AUDIO_FUNC_2_N_AS_INT
#error You must tell the driver the number of Standard AS Interface Descriptors you have defined in the audio function descriptor!
#endif
#endif
#if CFG_TUD_AUDIO > 2
#ifndef CFG_TUD_AUDIO_FUNC_3_N_AS_INT
#error You must tell the driver the number of Standard AS Interface Descriptors you have defined in the audio function descriptor!
#endif
#endif

// 用于通过EP0接收和发送控制消息的控制缓冲区大小必须足够大，以容纳最大的请求结构，例如定义了多个间隔的范围请求或集群描述符
#ifndef CFG_TUD_AUDIO_FUNC_1_CTRL_BUF_SZ
#error You must define an audio class control request buffer size!
#endif

#if CFG_TUD_AUDIO > 1
#ifndef CFG_TUD_AUDIO_FUNC_2_CTRL_BUF_SZ
#error You must define an audio class control request buffer size!
#endif
#endif

#if CFG_TUD_AUDIO > 2
#ifndef CFG_TUD_AUDIO_FUNC_3_CTRL_BUF_SZ
#error You must define an audio class control request buffer size!
#endif
#endif

// 终点尺寸IN BYTES-限制：全速<=1023，高速<=1024
#ifndef CFG_TUD_AUDIO_ENABLE_EP_IN
#define CFG_TUD_AUDIO_ENABLE_EP_IN 0   // TX
#endif

#ifndef CFG_TUD_AUDIO_ENABLE_EP_OUT
#define CFG_TUD_AUDIO_ENABLE_EP_OUT 0  // RX
#endif

// 所有备用AS接口设置的最大EP大小-用于检查和缓冲区分配
#if CFG_TUD_AUDIO_ENABLE_EP_IN
#ifndef CFG_TUD_AUDIO_FUNC_1_EP_IN_SZ_MAX
#error You must tell the driver the biggest EP IN size!
#endif
#if CFG_TUD_AUDIO > 1
#ifndef CFG_TUD_AUDIO_FUNC_2_EP_IN_SZ_MAX
#error You must tell the driver the biggest EP IN size!
#endif
#endif
#if CFG_TUD_AUDIO > 2
#ifndef CFG_TUD_AUDIO_FUNC_3_EP_IN_SZ_MAX
#error You must tell the driver the biggest EP IN size!
#endif
#endif
#endif // CFG_TUD_AUDIO_ENABLE_EP_IN

#if CFG_TUD_AUDIO_ENABLE_EP_OUT
#ifndef CFG_TUD_AUDIO_FUNC_1_EP_OUT_SZ_MAX
#error You must tell the driver the biggest EP OUT size!
#endif
#if CFG_TUD_AUDIO > 1
#ifndef CFG_TUD_AUDIO_FUNC_2_EP_OUT_SZ_MAX
#error You must tell the driver the biggest EP OUT size!
#endif
#endif
#if CFG_TUD_AUDIO > 2
#ifndef CFG_TUD_AUDIO_FUNC_3_EP_OUT_SZ_MAX
#error You must tell the driver the biggest EP OUT size!
#endif
#endif
#endif // CFG_TUD_AUDIO_ENABLE_EP_OUT

// 软件EP FIFO缓冲区大小-必须>=最大EP sizes！
#ifndef CFG_TUD_AUDIO_FUNC_1_EP_IN_SW_BUF_SZ
#define CFG_TUD_AUDIO_FUNC_1_EP_IN_SW_BUF_SZ                0
#endif
#ifndef CFG_TUD_AUDIO_FUNC_2_EP_IN_SW_BUF_SZ
#define CFG_TUD_AUDIO_FUNC_2_EP_IN_SW_BUF_SZ                0
#endif
#ifndef CFG_TUD_AUDIO_FUNC_3_EP_IN_SW_BUF_SZ
#define CFG_TUD_AUDIO_FUNC_3_EP_IN_SW_BUF_SZ                0
#endif

#ifndef CFG_TUD_AUDIO_FUNC_1_EP_OUT_SW_BUF_SZ
#define CFG_TUD_AUDIO_FUNC_1_EP_OUT_SW_BUF_SZ               0
#endif
#ifndef CFG_TUD_AUDIO_FUNC_2_EP_OUT_SW_BUF_SZ
#define CFG_TUD_AUDIO_FUNC_2_EP_OUT_SW_BUF_SZ               0
#endif
#ifndef CFG_TUD_AUDIO_FUNC_3_EP_OUT_SW_BUF_SZ
#define CFG_TUD_AUDIO_FUNC_3_EP_OUT_SW_BUF_SZ               0
#endif

#if CFG_TUD_AUDIO_ENABLE_EP_IN
#if CFG_TUD_AUDIO_FUNC_1_EP_IN_SW_BUF_SZ < CFG_TUD_AUDIO_FUNC_1_EP_IN_SZ_MAX
#error EP software buffer size MUST BE at least as big as maximum EP size
#endif

#if CFG_TUD_AUDIO > 1
#if CFG_TUD_AUDIO_FUNC_2_EP_IN_SW_BUF_SZ < CFG_TUD_AUDIO_FUNC_2_EP_IN_SZ_MAX
#error EP software buffer size MUST BE at least as big as maximum EP size
#endif
#endif

#if CFG_TUD_AUDIO > 2
#if CFG_TUD_AUDIO_FUNC_3_EP_IN_SW_BUF_SZ < CFG_TUD_AUDIO_FUNC_3_EP_IN_SZ_MAX
#error EP software buffer size MUST BE at least as big as maximum EP size
#endif
#endif
#endif

#if CFG_TUD_AUDIO_ENABLE_EP_OUT
#if CFG_TUD_AUDIO_FUNC_1_EP_OUT_SW_BUF_SZ < CFG_TUD_AUDIO_FUNC_1_EP_OUT_SZ_MAX
#error EP software buffer size MUST BE at least as big as maximum EP size
#endif

#if CFG_TUD_AUDIO > 1
#if CFG_TUD_AUDIO_FUNC_2_EP_OUT_SW_BUF_SZ < CFG_TUD_AUDIO_FUNC_2_EP_OUT_SZ_MAX
#error EP software buffer size MUST BE at least as big as maximum EP size
#endif
#endif

#if CFG_TUD_AUDIO > 2
#if CFG_TUD_AUDIO_FUNC_3_EP_OUT_SW_BUF_SZ < CFG_TUD_AUDIO_FUNC_3_EP_OUT_SZ_MAX
#error EP software buffer size MUST BE at least as big as maximum EP size
#endif
#endif
#endif

// 启用/禁用反馈EP（异步RX应用需要）
#ifndef CFG_TUD_AUDIO_ENABLE_FEEDBACK_EP
#define CFG_TUD_AUDIO_ENABLE_FEEDBACK_EP                    0                             // 反馈-0或1
#endif

// 音频中断控制EP大小-如果为0，则禁用
#ifndef CFG_TUD_AUDIO_INT_CTR_EPSIZE_IN
#define CFG_TUD_AUDIO_INT_CTR_EPSIZE_IN                     0                             // 音频中断控制-如果需要-6字节，符合UAC 2规范（第74页）
#endif

#ifndef CFG_TUD_AUDIO_INT_CTR_EP_IN_SW_BUFFER_SIZE
#define CFG_TUD_AUDIO_INT_CTR_EP_IN_SW_BUFFER_SIZE          6                             // 根据UAC 2规范，音频控制中断EP-6字节的缓冲区大小（第74页）
#endif

// 使用软件编码/解码

// 驱动程序的软件编码功能不是强制性的。例如，如果您有两个需要交错的I2S流，那么它是有用的
// 作为SAMPLE_1|SAMPLE_2|SAMPLE_3|SAMPLE_4。
//
// 目前，仅支持PCM I型编码/解码！
//
// 如果要使用编码功能，则需要配置支持FIFO。其尺寸和数量定义如下。

// 编码/解码在软件中完成，因此耗时。如果您可以更有效地编码/解码流，请不要使用
// 支持FIFO，但使用
// -tud_audio_n_write（）或
// -tud_audio_n_read（）。
// 要写入/读取支持FIFO，请使用
// -tud_audio_n_write_support_ff（）或
// -tud_audio_n_read_support_ff（）。
//
// 完成的编码/解码格式类型定义如下。
//
// 当私有回调函数时，编码/解码开始
// -音频_tx_done_cb（）
// -音频_rx_done_cb（）
// 被调用。如果使用支持FIFO，则从那里调用相应的编码/解码函数。
// 编码/解码完成后，结果直接输入EP_X_SW_BUFFER_FIFO。您可以使用公共回调函数
// -tud_audio_tx_done_pre_load_cb（）或tud_audio-tx_done_post_load_cb（
// -tud_audio_rx.done_pre_read_cb（）或tud_audio.rx.done_post_read_cb（
// 如果你想知道发生了什么。
//
// 如果不使用支持FIFO，则可以使用公共回调函数
// -tud_audio_tx_done_pre_load_cb（）或tud_audio-tx_done_post_load_cb（
// -tud_audio_rx.done_pre_read_cb（）或tud_audio.rx.done_post_read_cb（
// 以便在正确的时间写入/读取EP_X_SW_BUFFER_FIFO。
//
// 如果您需要一种目前不支持的不同编码，请在
// -音频_tx_done_cb（）
// -音频_rx_done_cb（）
// 功能。

// 启用编码/解码-要使其工作，需要以适当的数量和大小设置支持FIFO
// 根据描述符解析活动AS备用接口的实际编码参数

// FIFO的项目大小始终固定为1，即字节！此外，主动使用的FIFO深度被重新配置，使得深度是当前样本大小的倍数，以避免在FIFO环形缓冲区中发生缠绕时样本被拆分（深度=（max_depth/sampe_sz）*sampe_sz）！
// 这是重要的提醒，以防您使用DMA！如果样本大小发生变化，DMA必须重新配置，就像不同深度的FIFO一样！！！

// 用于PCM编码/解码

#ifndef CFG_TUD_AUDIO_ENABLE_ENCODING
#define CFG_TUD_AUDIO_ENABLE_ENCODING                       0
#endif

#ifndef CFG_TUD_AUDIO_ENABLE_DECODING
#define CFG_TUD_AUDIO_ENABLE_DECODING                       0
#endif

// 此启用允许保存当前编码参数，例如每个样本的字节数等。TYPE_I包括通用PCM编码
#ifndef CFG_TUD_AUDIO_ENABLE_TYPE_I_ENCODING
#define CFG_TUD_AUDIO_ENABLE_TYPE_I_ENCODING                0
#endif

#ifndef CFG_TUD_AUDIO_ENABLE_TYPE_I_DECODING
#define CFG_TUD_AUDIO_ENABLE_TYPE_I_DECODING                0
#endif

// UAC2描述符中未给出I类编码参数
// 可以允许更灵活的设置，而不按以下方式修复此参数。然而，这通常是不需要的，如果真的需要，可以留到以后。更灵活的设置可以在set_interface（）中实现，但是，如何保存每个备用设置的值有待确定！
#if CFG_TUD_AUDIO_ENABLE_EP_IN && CFG_TUD_AUDIO_ENABLE_ENCODING && CFG_TUD_AUDIO_ENABLE_TYPE_I_ENCODING
#ifndef CFG_TUD_AUDIO_FUNC_1_CHANNEL_PER_FIFO_TX
#error You must tell the driver the number of channels per FIFO for the interleaved encoding! E.g. for an I2S interface having two channels, CHANNEL_PER_FIFO = 2 as the I2S stream having two channels is usually saved within one FIFO
#endif
#if CFG_TUD_AUDIO > 1
#ifndef CFG_TUD_AUDIO_FUNC_2_CHANNEL_PER_FIFO_TX
#error You must tell the driver the number of channels per FIFO for the interleaved encoding! E.g. for an I2S interface having two channels, CHANNEL_PER_FIFO = 2 as the I2S stream having two channels is usually saved within one FIFO
#endif
#endif
#if CFG_TUD_AUDIO > 2
#ifndef CFG_TUD_AUDIO_FUNC_3_CHANNEL_PER_FIFO_TX
#error You must tell the driver the number of channels per FIFO for the interleaved encoding! E.g. for an I2S interface having two channels, CHANNEL_PER_FIFO = 2 as the I2S stream having two channels is usually saved within one FIFO
#endif
#endif
#endif

#if CFG_TUD_AUDIO_ENABLE_EP_OUT && CFG_TUD_AUDIO_ENABLE_DECODING && CFG_TUD_AUDIO_ENABLE_TYPE_I_DECODING
#ifndef CFG_TUD_AUDIO_FUNC_1_CHANNEL_PER_FIFO_RX
#error You must tell the driver the number of channels per FIFO for the interleaved encoding! E.g. for an I2S interface having two channels, CHANNEL_PER_FIFO = 2 as the I2S stream having two channels is usually saved within one FIFO
#endif
#if CFG_TUD_AUDIO > 1
#ifndef CFG_TUD_AUDIO_FUNC_2_CHANNEL_PER_FIFO_RX
#error You must tell the driver the number of channels per FIFO for the interleaved encoding! E.g. for an I2S interface having two channels, CHANNEL_PER_FIFO = 2 as the I2S stream having two channels is usually saved within one FIFO
#endif
#endif
#if CFG_TUD_AUDIO > 2
#ifndef CFG_TUD_AUDIO_FUNC_3_CHANNEL_PER_FIFO_RX
#error You must tell the driver the number of channels per FIFO for the interleaved encoding! E.g. for an I2S interface having two channels, CHANNEL_PER_FIFO = 2 as the I2S stream having two channels is usually saved within one FIFO
#endif
#endif
#endif

// 到目前为止不支持的其余类型

// 要设置的支持FIFO的数量-一个FIFO可以处理多个通道-非常常见的是，一个I2S接口产生的每个FIFO有两个通道
#ifndef CFG_TUD_AUDIO_FUNC_1_N_TX_SUPP_SW_FIFO
#define CFG_TUD_AUDIO_FUNC_1_N_TX_SUPP_SW_FIFO              0
#endif
#ifndef CFG_TUD_AUDIO_FUNC_2_N_TX_SUPP_SW_FIFO
#define CFG_TUD_AUDIO_FUNC_2_N_TX_SUPP_SW_FIFO              0
#endif
#ifndef CFG_TUD_AUDIO_FUNC_3_N_TX_SUPP_SW_FIFO
#define CFG_TUD_AUDIO_FUNC_3_N_TX_SUPP_SW_FIFO              0
#endif

#ifndef CFG_TUD_AUDIO_FUNC_1_N_RX_SUPP_SW_FIFO
#define CFG_TUD_AUDIO_FUNC_1_N_RX_SUPP_SW_FIFO              0
#endif
#ifndef CFG_TUD_AUDIO_FUNC_2_N_RX_SUPP_SW_FIFO
#define CFG_TUD_AUDIO_FUNC_2_N_RX_SUPP_SW_FIFO              0
#endif
#ifndef CFG_TUD_AUDIO_FUNC_3_N_RX_SUPP_SW_FIFO
#define CFG_TUD_AUDIO_FUNC_3_N_RX_SUPP_SW_FIFO              0
#endif

// BYTES中支持FIFO的大小-如果大小>0，则设置的FIFO数量与CFG_TUD_AUDIO_FUNC_X_N_TX_SUPP_SW_FIFO和CFG_TUD-AUDIO_FENC_X_RX_SUP_SW_FIFO一样多
#ifndef CFG_TUD_AUDIO_FUNC_1_TX_SUPP_SW_FIFO_SZ
#define CFG_TUD_AUDIO_FUNC_1_TX_SUPP_SW_FIFO_SZ             0         // FIFO大小-最小大小：ceil（f_s/1000）*max（TX信道数）/（TX支持FIFO的数量）*max
#endif
#ifndef CFG_TUD_AUDIO_FUNC_2_TX_SUPP_SW_FIFO_SZ
#define CFG_TUD_AUDIO_FUNC_2_TX_SUPP_SW_FIFO_SZ             0
#endif
#ifndef CFG_TUD_AUDIO_FUNC_3_TX_SUPP_SW_FIFO_SZ
#define CFG_TUD_AUDIO_FUNC_3_TX_SUPP_SW_FIFO_SZ             0
#endif

#ifndef CFG_TUD_AUDIO_FUNC_1_RX_SUPP_SW_FIFO_SZ
#define CFG_TUD_AUDIO_FUNC_1_RX_SUPP_SW_FIFO_SZ             0         // FIFO大小-最小大小：ceil（f_s/1000）*max（RX信道数）/（RX支持FIFO的数量）*max
#endif
#ifndef CFG_TUD_AUDIO_FUNC_2_RX_SUPP_SW_FIFO_SZ
#define CFG_TUD_AUDIO_FUNC_2_RX_SUPP_SW_FIFO_SZ             0
#endif
#ifndef CFG_TUD_AUDIO_FUNC_3_RX_SUPP_SW_FIFO_SZ
#define CFG_TUD_AUDIO_FUNC_3_RX_SUPP_SW_FIFO_SZ             0
#endif

//静态断言（sizeof（tud_audio_desc_lengths）！=CFG_TUD_AUDIO，“提供音频功能描述符包长度！”）；

// 此驱动程序的支持类型：
// AUDIO_DATA_FORMAT_TYPE_I_PCM-所需定义：CFG_TUD_AUDIO_N_CHANNELS和CFG_TUD-AUDIO_BYTES_PER_CHANNEL

#ifdef __cplusplus
extern "C" {
#endif

/** \addtogroup AUDIO_Serial Serial @{ \defgroup AUDIO_Serial_Device设备
 *  @{ */

//--------------------------------------------------------------------+
// 应用程序API（多接口）
// CFG_TUD_AUDIO > 1
//--------------------------------------------------------------------+
bool     tud_audio_n_mounted    (uint8_t itf);

#if CFG_TUD_AUDIO_ENABLE_EP_OUT && !CFG_TUD_AUDIO_ENABLE_DECODING
uint16_t tud_audio_n_available                    (uint8_t itf);
uint16_t tud_audio_n_read                         (uint8_t itf, void* buffer, uint16_t bufsize);
bool     tud_audio_n_clear_ep_out_ff              (uint8_t itf);                          // 删除EP OUT FIFO中的所有内容
#endif

#if CFG_TUD_AUDIO_ENABLE_EP_OUT && CFG_TUD_AUDIO_ENABLE_DECODING
bool     tud_audio_n_clear_rx_support_ff          (uint8_t itf, uint8_t channelId);       // 删除支持RX FIFO中的所有内容
uint16_t tud_audio_n_available_support_ff         (uint8_t itf, uint8_t channelId);
uint16_t tud_audio_n_read_support_ff              (uint8_t itf, uint8_t channelId, void* buffer, uint16_t bufsize);
#endif

#if CFG_TUD_AUDIO_ENABLE_EP_IN && !CFG_TUD_AUDIO_ENABLE_ENCODING
uint16_t tud_audio_n_write                        (uint8_t itf, const void * data, uint16_t len);
bool     tud_audio_n_clear_ep_in_ff               (uint8_t itf);                          // 删除EP in FIFO中的所有内容
#endif

#if CFG_TUD_AUDIO_ENABLE_EP_IN && CFG_TUD_AUDIO_ENABLE_ENCODING
uint16_t tud_audio_n_flush_tx_support_ff          (uint8_t itf);      // 强制将支持TX FIFO中的所有内容写入EP SW FIFO
bool     tud_audio_n_clear_tx_support_ff          (uint8_t itf, uint8_t channelId);
uint16_t tud_audio_n_write_support_ff             (uint8_t itf, uint8_t channelId, const void * data, uint16_t len);
#endif

#if CFG_TUD_AUDIO_INT_CTR_EPSIZE_IN
uint16_t    tud_audio_int_ctr_n_write             (uint8_t itf, uint8_t const* buffer, uint16_t len);
#endif

//--------------------------------------------------------------------+
// 应用程序API（接口0）
//--------------------------------------------------------------------+

static inline bool         tud_audio_mounted                (void);

// RX API

#if CFG_TUD_AUDIO_ENABLE_EP_OUT && !CFG_TUD_AUDIO_ENABLE_DECODING
static inline uint16_t     tud_audio_available              (void);
static inline bool         tud_audio_clear_ep_out_ff        (void);                       // 删除EP OUT FIFO中的所有内容
static inline uint16_t     tud_audio_read                   (void* buffer, uint16_t bufsize);
#endif

#if CFG_TUD_AUDIO_ENABLE_EP_OUT && CFG_TUD_AUDIO_ENABLE_DECODING
static inline bool     tud_audio_clear_rx_support_ff        (uint8_t channelId);
static inline uint16_t tud_audio_available_support_ff       (uint8_t channelId);
static inline uint16_t tud_audio_read_support_ff            (uint8_t channelId, void* buffer, uint16_t bufsize);
#endif

// TX API

#if CFG_TUD_AUDIO_ENABLE_EP_IN && !CFG_TUD_AUDIO_ENABLE_ENCODING
static inline uint16_t tud_audio_write                      (const void * data, uint16_t len);
static inline bool 	   tud_audio_clear_ep_in_ff             (void);
#endif

#if CFG_TUD_AUDIO_ENABLE_EP_IN && CFG_TUD_AUDIO_ENABLE_ENCODING
static inline uint16_t tud_audio_flush_tx_support_ff        (void);
static inline uint16_t tud_audio_clear_tx_support_ff        (uint8_t channelId);
static inline uint16_t tud_audio_write_support_ff           (uint8_t channelId, const void * data, uint16_t len);
#endif

// INT CTR API

#if CFG_TUD_AUDIO_INT_CTR_EPSIZE_IN
static inline uint16_t tud_audio_int_ctr_write              (uint8_t const* buffer, uint16_t len);
#endif

// 缓冲控制EP数据并安排传输
// 如果您没有可用的持久缓冲区或内存位置（例如非本地变量），并且需要回答
// 获取请求。此函数将您的应答请求帧缓冲到相应音频驱动程序的控制缓冲区中，并安排发送。
// 由于传输是通过中断触发的，因此需要缓冲区指针指向的持久内存位置。如果你已经有了
// 可用时，您可以直接使用“tud_control_xfer（…）”。在这种情况下，不需要将数据复制到额外的缓冲区中，这样可以节省一些时间。
// 如果请求的wLength为零，则发送状态包。
bool tud_audio_buffer_and_schedule_control_xfer(uint8_t rhport, tusb_control_request_t const * p_request, void* data, uint16_t len);

//--------------------------------------------------------------------+
// 应用程序回调API（弱是可选的）
//--------------------------------------------------------------------+

#if CFG_TUD_AUDIO_ENABLE_EP_IN
TU_ATTR_WEAK bool tud_audio_tx_done_pre_load_cb(uint8_t rhport, uint8_t itf, uint8_t ep_in, uint8_t cur_alt_setting);
TU_ATTR_WEAK bool tud_audio_tx_done_post_load_cb(uint8_t rhport, uint16_t n_bytes_copied, uint8_t itf, uint8_t ep_in, uint8_t cur_alt_setting);
#endif

#if CFG_TUD_AUDIO_ENABLE_EP_OUT
TU_ATTR_WEAK bool tud_audio_rx_done_pre_read_cb(uint8_t rhport, uint16_t n_bytes_received, uint8_t itf, uint8_t ep_out, uint8_t cur_alt_setting);
TU_ATTR_WEAK bool tud_audio_rx_done_post_read_cb(uint8_t rhport, uint16_t n_bytes_received, uint8_t itf, uint8_t ep_out, uint8_t cur_alt_setting);
#endif

#if CFG_TUD_AUDIO_ENABLE_EP_OUT && CFG_TUD_AUDIO_ENABLE_FEEDBACK_EP
TU_ATTR_WEAK bool tud_audio_fb_done_cb(uint8_t rhport);
// 对于FS和HS，用户代码应使用16.16格式的反馈值调用此函数。
// FS值将自动更正为10.14格式。
// （参见通用串行总线规范修订版2.0 5.12.4.2）。
// 反馈值将以FB端点间隔发送，直到更改。
bool tud_audio_n_fb_set(uint8_t itf, uint32_t feedback);
static inline bool tud_audio_fb_set(uint32_t feedback);
#endif

#if CFG_TUD_AUDIO_INT_CTR_EPSIZE_IN
TU_ATTR_WEAK bool tud_audio_int_ctr_done_cb(uint8_t rhport, uint16_t n_bytes_copied);
#endif

// 收到音频集接口请求时调用
TU_ATTR_WEAK bool tud_audio_set_itf_cb(uint8_t rhport, tusb_control_request_t const * p_request);

// 当接收到关闭EP的音频集接口请求时调用
TU_ATTR_WEAK bool tud_audio_set_itf_close_EP_cb(uint8_t rhport, tusb_control_request_t const * p_request);

// 收到EP的音频类特定设置请求时调用
TU_ATTR_WEAK bool tud_audio_set_req_ep_cb(uint8_t rhport, tusb_control_request_t const * p_request, uint8_t *pBuff);

// 收到接口的音频类特定设置请求时调用
TU_ATTR_WEAK bool tud_audio_set_req_itf_cb(uint8_t rhport, tusb_control_request_t const * p_request, uint8_t *pBuff);

// 在收到实体的音频类特定集合请求时调用
TU_ATTR_WEAK bool tud_audio_set_req_entity_cb(uint8_t rhport, tusb_control_request_t const * p_request, uint8_t *pBuff);

// 在收到EP的音频类特定获取请求时调用
TU_ATTR_WEAK bool tud_audio_get_req_ep_cb(uint8_t rhport, tusb_control_request_t const * p_request);

// 在收到接口的音频类特定获取请求时调用
TU_ATTR_WEAK bool tud_audio_get_req_itf_cb(uint8_t rhport, tusb_control_request_t const * p_request);

// 在收到实体的音频类特定获取请求时调用
TU_ATTR_WEAK bool tud_audio_get_req_entity_cb(uint8_t rhport, tusb_control_request_t const * p_request);

//--------------------------------------------------------------------+
// 内联函数
//--------------------------------------------------------------------+

static inline bool tud_audio_mounted(void)
{
  return tud_audio_n_mounted(0);
}

// RX API

#if CFG_TUD_AUDIO_ENABLE_EP_OUT && !CFG_TUD_AUDIO_ENABLE_DECODING

static inline uint16_t tud_audio_available(void)
{
  return tud_audio_n_available(0);
}

static inline uint16_t tud_audio_read(void* buffer, uint16_t bufsize)
{
  return tud_audio_n_read(0, buffer, bufsize);
}

static inline bool tud_audio_clear_ep_out_ff(void)
{
  return tud_audio_n_clear_ep_out_ff(0);
}

#endif

#if CFG_TUD_AUDIO_ENABLE_EP_OUT && CFG_TUD_AUDIO_ENABLE_DECODING

static inline bool tud_audio_clear_rx_support_ff(uint8_t channelId)
{
  return tud_audio_n_clear_rx_support_ff(0, channelId);
}

static inline uint16_t tud_audio_available_support_ff(uint8_t channelId)
{
  return tud_audio_n_available_support_ff(0, channelId);
}

static inline uint16_t tud_audio_read_support_ff(uint8_t channelId, void* buffer, uint16_t bufsize)
{
  return tud_audio_n_read_support_ff(0, channelId, buffer, bufsize);
}

#endif

// TX API

#if CFG_TUD_AUDIO_ENABLE_EP_IN && !CFG_TUD_AUDIO_ENABLE_ENCODING

static inline uint16_t tud_audio_write(const void * data, uint16_t len)
{
  return tud_audio_n_write(0, data, len);
}

static inline bool tud_audio_clear_ep_in_ff(void)
{
  return tud_audio_n_clear_ep_in_ff(0);
}

#endif

#if CFG_TUD_AUDIO_ENABLE_EP_IN && CFG_TUD_AUDIO_ENABLE_ENCODING

static inline uint16_t tud_audio_flush_tx_support_ff(void)
{
  return tud_audio_n_flush_tx_support_ff(0);
}

static inline uint16_t tud_audio_clear_tx_support_ff(uint8_t channelId)
{
  return tud_audio_n_clear_tx_support_ff(0, channelId);
}

static inline uint16_t tud_audio_write_support_ff(uint8_t channelId, const void * data, uint16_t len)
{
  return tud_audio_n_write_support_ff(0, channelId, data, len);
}

#endif

#if CFG_TUD_AUDIO_INT_CTR_EPSIZE_IN
static inline uint16_t tud_audio_int_ctr_write(uint8_t const* buffer, uint16_t len)
{
  return tud_audio_int_ctr_n_write(0, buffer, len);
}
#endif

#if CFG_TUD_AUDIO_ENABLE_EP_OUT && CFG_TUD_AUDIO_ENABLE_FEEDBACK_EP
static inline bool tud_audio_fb_set(uint32_t feedback)
{
  return tud_audio_n_fb_set(0, feedback);
}
#endif

//--------------------------------------------------------------------+
// 内部类驱动程序API
//--------------------------------------------------------------------+
void     audiod_init           (void);
void     audiod_reset          (uint8_t rhport);
uint16_t audiod_open           (uint8_t rhport, tusb_desc_interface_t const * itf_desc, uint16_t max_len);
bool     audiod_control_xfer_cb(uint8_t rhport, uint8_t stage, tusb_control_request_t const * request);
bool     audiod_xfer_cb        (uint8_t rhport, uint8_t edpt_addr, xfer_result_t result, uint32_t xferred_bytes);

#ifdef __cplusplus
}
#endif

#endif /* _TUSB_AUDIO_DEVICE_H_ */

/** @} */
/** @} */

