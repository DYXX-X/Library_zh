/* 
 * MIT许可证（MIT）
 *
 * 版权所有（c）2020 Jerzy Kasenbreg
 *
 * 特此免费授予获得本软件和相关文档文件（“软件”）副本的任何人无限制地处理软件的权利，包括但不限于使用、复制、修改、合并、发布、分发、再许可和/或销售软件副本的权利，并允许向其提供软件的人这样做，符合以下条件：
 *
 * 上述版权声明和本许可声明应包含在软件的所有副本或主要部分中。
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 */

#ifndef _USB_DESCRIPTORS_H_
#define _USB_DESCRIPTORS_H_

// #包括“tusb.h”

// 单位编号是任意选择的
#define UAC2_ENTITY_CLOCK               0x04
// 扬声器路径
#define UAC2_ENTITY_SPK_INPUT_TERMINAL  0x01
#define UAC2_ENTITY_SPK_FEATURE_UNIT    0x02
#define UAC2_ENTITY_SPK_OUTPUT_TERMINAL 0x03
// 麦克风路径
#define UAC2_ENTITY_MIC_INPUT_TERMINAL  0x11
#define UAC2_ENTITY_MIC_OUTPUT_TERMINAL 0x13

enum
{
  ITF_NUM_AUDIO_CONTROL = 0,
  ITF_NUM_AUDIO_STREAMING_SPK,
  ITF_NUM_AUDIO_STREAMING_MIC,
  ITF_NUM_TOTAL
};

#define TUD_AUDIO_HEADSET_STEREO_DESC_LEN (TUD_AUDIO_DESC_IAD_LEN\
    + TUD_AUDIO_DESC_STD_AC_LEN\
    + TUD_AUDIO_DESC_CS_AC_LEN\
    + TUD_AUDIO_DESC_CLK_SRC_LEN\
    + TUD_AUDIO_DESC_INPUT_TERM_LEN\
    + TUD_AUDIO_DESC_FEATURE_UNIT_TWO_CHANNEL_LEN\
    + TUD_AUDIO_DESC_OUTPUT_TERM_LEN\
    + TUD_AUDIO_DESC_INPUT_TERM_LEN\
    + TUD_AUDIO_DESC_OUTPUT_TERM_LEN\
    + TUD_AUDIO_DESC_STD_AS_INT_LEN\
    + TUD_AUDIO_DESC_STD_AS_INT_LEN\
    + TUD_AUDIO_DESC_CS_AS_INT_LEN\
    + TUD_AUDIO_DESC_TYPE_I_FORMAT_LEN\
    + TUD_AUDIO_DESC_STD_AS_ISO_EP_LEN\
    + TUD_AUDIO_DESC_CS_AS_ISO_EP_LEN\
    + TUD_AUDIO_DESC_STD_AS_INT_LEN\
    + TUD_AUDIO_DESC_STD_AS_INT_LEN\
    + TUD_AUDIO_DESC_CS_AS_INT_LEN\
    + TUD_AUDIO_DESC_TYPE_I_FORMAT_LEN\
    + TUD_AUDIO_DESC_STD_AS_ISO_EP_LEN\
    + TUD_AUDIO_DESC_CS_AS_ISO_EP_LEN)


#define TUD_AUDIO_HEADSET_STEREO_DESCRIPTOR(_stridx, _nBytesPerSample, _nBitsUsedPerSample, _epout, _epoutsize, _epin, _epinsize) \
    /* 标准接口关联描述符（IAD）*/\
    TUD_AUDIO_DESC_IAD(/*_第一次*/ ITF_NUM_AUDIO_CONTROL, /*_硝酸盐*/ ITF_NUM_TOTAL, /*_斯特里克斯*/ 0x00),\
    /* 标准交流接口描述符（4.7.1）*/\
    TUD_AUDIO_DESC_STD_AC(/*_itfnum公司*/ ITF_NUM_AUDIO_CONTROL, /*_nEP*/ 0x00, /*_斯特里克斯*/ _stridx),\
    /* 类特定AC接口头描述符（4.7.2）*/\
    TUD_AUDIO_DESC_CS_AC(/*_bcdADC*/ 0x0200, /*_类别*/ AUDIO_FUNC_HEADSET, /*_总计*/ TUD_AUDIO_DESC_CLK_SRC_LEN+TUD_AUDIO_DESC_FEATURE_UNIT_TWO_CHANNEL_LEN+TUD_AUDIO_DESC_INPUT_TERM_LEN+TUD_AUDIO_DESC_OUTPUT_TERM_LEN+TUD_AUDIO_DESC_INPUT_TERM_LEN+TUD_AUDIO_DESC_OUTPUT_TERM_LEN, /*_ctrl键*/ AUDIO_CS_AS_INTERFACE_CTRL_LATENCY_POS),\
    /* 时钟源描述符（4.7.2.1）*/\
    TUD_AUDIO_DESC_CLK_SRC(/*_clkid公司*/ UAC2_ENTITY_CLOCK, /*_属性*/ 3, /*_ctrl键*/ 5, /*_关联术语*/ 0x00,  /*_斯特里克斯*/ 0x00),    \
    /* 输入终端描述符（4.7.2.4）*/\
    TUD_AUDIO_DESC_INPUT_TERM(/*_白蚁*/ UAC2_ENTITY_SPK_INPUT_TERMINAL, /*_术语类型*/ AUDIO_TERM_TYPE_USB_STREAMING, /*_关联术语*/ 0x00, /*_clkid公司*/ UAC2_ENTITY_CLOCK, /*_n信道逻辑的*/ 0x02, /*_频道配置文件*/ AUDIO_CHANNEL_CONFIG_NON_PREDEFINED, /*_idxchannel名称*/ 0x00, /*_ctrl键*/ 0 * (AUDIO_CTRL_R << AUDIO_IN_TERM_CTRL_CONNECTOR_POS), /*_斯特里克斯*/ 0x00),\
    /* 功能单元描述符（4.7.2.8）*/\
    TUD_AUDIO_DESC_FEATURE_UNIT_TWO_CHANNEL(/*_单位化的*/ UAC2_ENTITY_SPK_FEATURE_UNIT, /*_srcid公司*/ UAC2_ENTITY_SPK_INPUT_TERMINAL, /*_ctrlch0主机*/ (AUDIO_CTRL_RW << AUDIO_FEATURE_UNIT_CTRL_MUTE_POS | AUDIO_CTRL_RW << AUDIO_FEATURE_UNIT_CTRL_VOLUME_POS), /*_控制1*/ (AUDIO_CTRL_RW << AUDIO_FEATURE_UNIT_CTRL_MUTE_POS | AUDIO_CTRL_RW << AUDIO_FEATURE_UNIT_CTRL_VOLUME_POS), /*_控制2*/ (AUDIO_CTRL_RW << AUDIO_FEATURE_UNIT_CTRL_MUTE_POS | AUDIO_CTRL_RW << AUDIO_FEATURE_UNIT_CTRL_VOLUME_POS), /*_斯特里克斯*/ 0x00),\
    /* 输出端子描述符（4.7.2.5）*/\
    TUD_AUDIO_DESC_OUTPUT_TERM(/*_白蚁*/ UAC2_ENTITY_SPK_OUTPUT_TERMINAL, /*_术语类型*/ AUDIO_TERM_TYPE_OUT_GENERIC_SPEAKER, /*_关联术语*/ 0x00, /*_srcid公司*/ UAC2_ENTITY_SPK_FEATURE_UNIT, /*_clkid公司*/ UAC2_ENTITY_CLOCK, /*_ctrl键*/ 0x0000, /*_斯特里克斯*/ 0x00),\
    /* 输入终端描述符（4.7.2.4）*/\
    TUD_AUDIO_DESC_INPUT_TERM(/*_白蚁*/ UAC2_ENTITY_MIC_INPUT_TERMINAL, /*_术语类型*/ AUDIO_TERM_TYPE_IN_GENERIC_MIC, /*_关联术语*/ 0x00, /*_clkid公司*/ UAC2_ENTITY_CLOCK, /*_n信道逻辑的*/ 0x01, /*_频道配置文件*/ AUDIO_CHANNEL_CONFIG_NON_PREDEFINED, /*_idxchannel名称*/ 0x00, /*_ctrl键*/ 0 * (AUDIO_CTRL_R << AUDIO_IN_TERM_CTRL_CONNECTOR_POS), /*_斯特里克斯*/ 0x00),\
    /* 输出端子描述符（4.7.2.5）*/\
    TUD_AUDIO_DESC_OUTPUT_TERM(/*_白蚁*/ UAC2_ENTITY_MIC_OUTPUT_TERMINAL, /*_术语类型*/ AUDIO_TERM_TYPE_USB_STREAMING, /*_关联术语*/ 0x00, /*_srcid公司*/ UAC2_ENTITY_MIC_INPUT_TERMINAL, /*_clkid公司*/ UAC2_ENTITY_CLOCK, /*_ctrl键*/ 0x0000, /*_斯特里克斯*/ 0x00),\
    /* 标准AS接口描述符（4.9.1）*/\
    /* 接口1，备用0-默认备用设置，带宽为0*/\
    TUD_AUDIO_DESC_STD_AS_INT(/*_itfnum公司*/ (uint8_t)(ITF_NUM_AUDIO_STREAMING_SPK), /*_阿尔特塞特*/ 0x00, /*_nEP*/ 0x00, /*_斯特里克斯*/ 0x05),\
    /* 标准AS接口描述符（4.9.1）*/\
    /* 接口1，备用1-数据流的备用接口*/\
    TUD_AUDIO_DESC_STD_AS_INT(/*_itfnum公司*/ (uint8_t)(ITF_NUM_AUDIO_STREAMING_SPK), /*_阿尔特塞特*/ 0x01, /*_nEP*/ 0x01, /*_斯特里克斯*/ 0x05),\
    /* 类特定AS接口描述符（4.9.2）*/\
    TUD_AUDIO_DESC_CS_AS_INT(/*_白蚁*/ UAC2_ENTITY_SPK_INPUT_TERMINAL, /*_ctrl键*/ AUDIO_CTRL_NONE, /*_格式类型*/ AUDIO_FORMAT_TYPE_I, /*_格式*/ AUDIO_DATA_FORMAT_TYPE_I_PCM, /*_n信道物理*/ 0x02, /*_频道配置文件*/ AUDIO_CHANNEL_CONFIG_NON_PREDEFINED, /*_斯特里克斯*/ 0x00),\
    /* I类格式类型描述符（2.3.1.6-音频格式）*/\
    TUD_AUDIO_DESC_TYPE_I_FORMAT(_nBytesPerSample, _nBitsUsedPerSample),\
    /* 标准AS等时音频数据端点描述符（4.10.1.1）*/\
    TUD_AUDIO_DESC_STD_AS_ISO_EP(/*_环境保护部*/ _epout, /*_属性*/ (TUSB_XFER_ISOCHRONOUS | TUSB_ISO_EP_ATT_ADAPTIVE | TUSB_ISO_EP_ATT_DATA), /*_最大EPsize*/ _epoutsize, /*_间隔，间隔*/ (CFG_TUSB_RHPORT0_MODE & OPT_MODE_HIGH_SPEED) ? 0x04 : 0x01),\
    /* 类特定AS等时音频数据端点描述符（4.10.1.2）*/\
    TUD_AUDIO_DESC_CS_AS_ISO_EP(/*_属性*/ AUDIO_CS_AS_ISO_DATA_EP_ATT_NON_MAX_PACKETS_OK, /*_ctrl键*/ AUDIO_CTRL_NONE, /*_洛克德拉尤尼特*/ AUDIO_CS_AS_ISO_DATA_EP_LOCK_DELAY_UNIT_MILLISEC, /*_锁定延迟*/ 0x0001),\
    /* 标准AS接口描述符（4.9.1）*/\
    /* 接口2，备用0-0带宽的默认备用设置*/\
    TUD_AUDIO_DESC_STD_AS_INT(/*_itfnum公司*/ (uint8_t)(ITF_NUM_AUDIO_STREAMING_MIC), /*_阿尔特塞特*/ 0x00, /*_nEP*/ 0x00, /*_斯特里克斯*/ 0x04),\
    /* 标准AS接口描述符（4.9.1）*/\
    /* 接口1，备用1-数据流的备用接口*/\
    TUD_AUDIO_DESC_STD_AS_INT(/*_itfnum公司*/ (uint8_t)(ITF_NUM_AUDIO_STREAMING_MIC), /*_阿尔特塞特*/ 0x01, /*_nEP*/ 0x01, /*_斯特里克斯*/ 0x04),\
    /* 类特定AS接口描述符（4.9.2）*/\
    TUD_AUDIO_DESC_CS_AS_INT(/*_白蚁*/ UAC2_ENTITY_MIC_OUTPUT_TERMINAL, /*_ctrl键*/ AUDIO_CTRL_NONE, /*_格式类型*/ AUDIO_FORMAT_TYPE_I, /*_格式*/ AUDIO_DATA_FORMAT_TYPE_I_PCM, /*_n信道物理*/ 0x01, /*_频道配置文件*/ AUDIO_CHANNEL_CONFIG_NON_PREDEFINED, /*_斯特里克斯*/ 0x00),\
    /* I类格式类型描述符（2.3.1.6-音频格式）*/\
    TUD_AUDIO_DESC_TYPE_I_FORMAT(_nBytesPerSample, _nBitsUsedPerSample),\
    /* 标准AS等时音频数据端点描述符（4.10.1.1）*/\
    TUD_AUDIO_DESC_STD_AS_ISO_EP(/*_环境保护部*/ _epin, /*_属性*/ (TUSB_XFER_ISOCHRONOUS | TUSB_ISO_EP_ATT_ASYNCHRONOUS | TUSB_ISO_EP_ATT_DATA), /*_最大EPsize*/ _epinsize, /*_间隔，间隔*/ (CFG_TUSB_RHPORT0_MODE & OPT_MODE_HIGH_SPEED) ? 0x04 : 0x01),\
    /* 类特定AS等时音频数据端点描述符（4.10.1.2）*/\
    TUD_AUDIO_DESC_CS_AS_ISO_EP(/*_属性*/ AUDIO_CS_AS_ISO_DATA_EP_ATT_NON_MAX_PACKETS_OK, /*_ctrl键*/ AUDIO_CTRL_NONE, /*_洛克德拉尤尼特*/ AUDIO_CS_AS_ISO_DATA_EP_LOCK_DELAY_UNIT_UNDEFINED, /*_锁定延迟*/ 0x0000)\

#endif

