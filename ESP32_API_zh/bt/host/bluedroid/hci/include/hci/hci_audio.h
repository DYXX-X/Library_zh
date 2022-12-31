/******************************************************************************
 * 版权所有（C）2015谷歌公司。
 *
 *  根据Apache许可证2.0版（“许可证”）获得许可；除非符合许可证，否则不得使用此文件。您可以在以下地址获取许可证副本：
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 *  除非适用法律要求或书面同意，否则根据许可证分发的软件是按“原样”分发的，无任何明示或暗示的担保或条件。有关许可证下权限和限制的具体语言，请参阅许可证。
 *
 ******************************************************************************/

#ifndef _HCI_AUDIO_H_
#define _HCI_AUDIO_H_
#include <stdint.h>

// 音频状态定义。
typedef enum {
    SCO_STATE_OFF = 0,      // 音频已关闭。
    SCO_STATE_OFF_TRANSFER, // 关闭，等待音频的最终传输。
    SCO_STATE_ON,           // 音频已打开。
    SCO_STATE_SETUP,        // 打开等待音频设置完成。
} sco_state_t;

// 编解码器类型定义。
typedef enum {
    SCO_CODEC_NONE = 0x0000,
    SCO_CODEC_CVSD = 0x0001,
    SCO_CODEC_MSBC = 0x0002,
} sco_codec_t;

// 使用
// 供应商库。
void set_audio_state(uint16_t handle, sco_codec_t codec, sco_state_t state);

#endif /* _HCI_AUDIO_H_ */

