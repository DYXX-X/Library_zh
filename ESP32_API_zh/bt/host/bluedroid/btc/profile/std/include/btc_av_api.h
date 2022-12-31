// 版权所有2015-2016 Espressif Systems（上海）私人有限公司
//
// 根据Apache许可证2.0版（“许可证”）获得许可；
// 除非符合许可证，否则不得使用此文件。
// 您可以在以下地址获取许可证副本：

//     http://www.apache.org/licenses/LICENSE-2.0
//
// 除非适用法律要求或书面同意，软件
// 根据许可证分发的内容是按“原样”分发的，
// 无任何明示或暗示的保证或条件。
// 有关管理权限和
// 许可证下的限制。


/*****************************************************************************
 ** 名称：btc_av_api.h
 **
 **  描述：这是BTC高级音频/视频流（AV）子系统的公共接口文件。
 **
 *****************************************************************************/

#ifndef __BTC_AV_API_H__
#define __BTC_AV_API_H__

#include "common/bt_target.h"
#include "bta/bta_av_api.h"
#include "stack/a2d_api.h"
#include "stack/a2d_sbc.h"

#if (BTC_AV_INCLUDED == TRUE)
/*****************************************************************************
 **  常量和数据类型
 *****************************************************************************/

/* 编解码器类型*/
#define BTC_AV_CODEC_NONE       0xFF
#define BTC_AV_CODEC_SBC        A2D_MEDIA_CT_SBC        /* SBC媒体编解码器类型*/

#define BTC_AV_CODEC_PCM        0x5                     /* 原始PCM*/

typedef UINT8 tBTC_AV_CODEC_ID;

/* AV功能掩码*/
#define BTC_AV_FEAT_RCTG        BTA_AV_FEAT_RCTG      /* 遥控目标*/
#define BTC_AV_FEAT_RCCT        BTA_AV_FEAT_RCCT      /* 遥控控制器*/
#define BTC_AV_FEAT_METADATA    BTA_AV_FEAT_METADATA  /* 远程控制元数据传输命令/响应*/

typedef UINT16 tBTC_AV_FEAT;

/* AV频道值*/
#define BTC_AV_CHNL_MSK         BTA_AV_CHNL_MSK
#define BTC_AV_CHNL_AUDIO       BTA_AV_CHNL_AUDIO       /* 音频通道*/
#define BTC_AV_CHNL_VIDEO       BTA_AV_CHNL_VIDEO       /* 视频频道*/
typedef UINT8 tBTC_AV_CHNL;

typedef UINT8 tBTC_AV_HNDL;

/* BTC_AvRemoteCmd的操作id列表*/
#define BTC_AV_ID_SELECT      0x00    /* 选择*/
#define BTC_AV_ID_UP          0x01    /* 向上的*/
#define BTC_AV_ID_DOWN        0x02    /* 向下*/
#define BTC_AV_ID_LEFT        0x03    /* 左边*/
#define BTC_AV_ID_RIGHT       0x04    /* 正确的*/
#define BTC_AV_ID_RIGHT_UP    0x05    /* 向上*/
#define BTC_AV_ID_RIGHT_DOWN  0x06    /* 向右向下*/
#define BTC_AV_ID_LEFT_UP     0x07    /* 左上*/
#define BTC_AV_ID_LEFT_DOWN   0x08    /* 左下*/
#define BTC_AV_ID_ROOT_MENU   0x09    /* 根菜单*/
#define BTC_AV_ID_SETUP_MENU  0x0A    /* 设置菜单*/
#define BTC_AV_ID_CONT_MENU   0x0B    /* 目录菜单*/
#define BTC_AV_ID_FAV_MENU    0x0C    /* 收藏夹菜单*/
#define BTC_AV_ID_EXIT        0x0D    /* 出口*/
#define BTC_AV_ID_0           0x20    /* 0 */
#define BTC_AV_ID_1           0x21    /* 1 */
#define BTC_AV_ID_2           0x22    /* 2 */
#define BTC_AV_ID_3           0x23    /* 3 */
#define BTC_AV_ID_4           0x24    /* 4 */
#define BTC_AV_ID_5           0x25    /* 5 */
#define BTC_AV_ID_6           0x26    /* 6 */
#define BTC_AV_ID_7           0x27    /* 7 */
#define BTC_AV_ID_8           0x28    /* 8 */
#define BTC_AV_ID_9           0x29    /* 9 */
#define BTC_AV_ID_DOT         0x2A    /* 点*/
#define BTC_AV_ID_ENTER       0x2B    /* 进来*/
#define BTC_AV_ID_CLEAR       0x2C    /* 清楚的*/
#define BTC_AV_ID_CHAN_UP     0x30    /* 通道向上*/
#define BTC_AV_ID_CHAN_DOWN   0x31    /* 通道关闭*/
#define BTC_AV_ID_PREV_CHAN   0x32    /* 前一频道*/
#define BTC_AV_ID_SOUND_SEL   0x33    /* 声音选择*/
#define BTC_AV_ID_INPUT_SEL   0x34    /* 输入选择*/
#define BTC_AV_ID_DISP_INFO   0x35    /* 显示信息*/
#define BTC_AV_ID_HELP        0x36    /* 帮助*/
#define BTC_AV_ID_PAGE_UP     0x37    /* 向上翻页*/
#define BTC_AV_ID_PAGE_DOWN   0x38    /* 向下翻页*/
#define BTC_AV_ID_POWER       0x40    /* 权力*/
#define BTC_AV_ID_VOL_UP      0x41    /* 音量增大*/
#define BTC_AV_ID_VOL_DOWN    0x42    /* 音量降低*/
#define BTC_AV_ID_MUTE        0x43    /* 沉默的*/
#define BTC_AV_ID_PLAY        0x44    /* 玩*/
#define BTC_AV_ID_STOP        0x45    /* 停止*/
#define BTC_AV_ID_PAUSE       0x46    /* 暂停*/
#define BTC_AV_ID_RECORD      0x47    /* 记录*/
#define BTC_AV_ID_REWIND      0x48    /* 重绕*/
#define BTC_AV_ID_FAST_FOR    0x49    /* 快进*/
#define BTC_AV_ID_EJECT       0x4A    /* 弹出*/
#define BTC_AV_ID_FORWARD     0x4B    /* 向前地*/
#define BTC_AV_ID_BACKWARD    0x4C    /* 向后的*/
#define BTC_AV_ID_ANGLE       0x50    /* 角*/
#define BTC_AV_ID_SUBPICT     0x51    /* 子画面*/
#define BTC_AV_ID_F1          0x71    /* F1 */
#define BTC_AV_ID_F2          0x72    /* F2 */
#define BTC_AV_ID_F3          0x73    /* F3 */
#define BTC_AV_ID_F4          0x74    /* F4 */
#define BTC_AV_ID_F5          0x75    /* F5 */
#define BTC_AV_ID_VENDOR      0x7E    /* 供应商独有*/
#define BTC_AV_KEYPRESSED_RELEASE 0x80

typedef UINT8 tBTC_AV_RC;

/* 传递命令的状态标志*/
#define BTC_AV_STATE_PRESS      0    /* 按键已按下*/
#define BTC_AV_STATE_RELEASE    1  /* 密钥已释放*/

typedef UINT8 tBTC_AV_STATE;

typedef UINT8 tBTC_AV_RC_HNDL;

/* BTC_AvVendorCmd的命令代码*/
#define BTC_AV_CMD_CTRL         0
#define BTC_AV_CMD_STATUS       1
#define BTC_AV_CMD_SPEC_INQ     2
#define BTC_AV_CMD_NOTIF        3
#define BTC_AV_CMD_GEN_INQ      4

typedef UINT8 tBTC_AV_CMD;

/* AV回调事件*/
#define BTC_AV_OPEN_EVT         0       /* 连接已打开*/
#define BTC_AV_CLOSE_EVT        1       /* 连接已关闭*/
#define BTC_AV_START_EVT        2       /* 流数据传输已启动*/
#define BTC_AV_STOP_EVT         3       /* 流数据传输已停止*/
#define BTC_AV_RC_OPEN_EVT      4       /* 遥控通道打开*/
#define BTC_AV_RC_CLOSE_EVT     5       /* 遥控通道关闭*/
#define BTC_AV_REMOTE_CMD_EVT   6      /* 远程控制命令*/
#define BTC_AV_REMOTE_RSP_EVT   7      /* 遥控器响应*/
#define BTC_AV_META_MSG_EVT     8      /* 元数据消息*/

typedef UINT8 tBTC_AV_EVT;

#define BTC_AV_FEEDING_ASYNCHRONOUS 0   /* 异步馈电，使用tx-av定时器*/
#define BTC_AV_FEEDING_SYNCHRONOUS  1   /* 同步馈电，无av tx定时器*/

#define BTC_AV_MAX_SYNCHRONOUS_LATENCY 80 /* BTC_AV_FEEDING_SYNCHRONOUS的最大延迟（毫秒）*/
#define BTC_AV_MIN_SYNCHRONOUS_LATENCY 4 /* BTC_AV_FEEDING_SYNCHRONOUS的最小延迟（毫秒）*/

typedef UINT8 tBTC_AV_FEEDING_MODE;

#define BTC_AV_CHANNEL_MODE_MONO    A2D_SBC_IE_CH_MD_MONO
#define BTC_AV_CHANNEL_MODE_STEREO  A2D_SBC_IE_CH_MD_STEREO
#define BTC_AV_CHANNEL_MODE_JOINT   A2D_SBC_IE_CH_MD_JOINT
#define BTC_AV_CHANNEL_MODE_DUAL    A2D_SBC_IE_CH_MD_DUAL

typedef UINT8 tBTC_AV_CHANNEL_MODE;

/**
 * 用于配置AV编解码器功能/config的结构
 */
typedef struct {
    tBTC_AV_CODEC_ID id;             /* 编解码器ID（以BTC表示）*/
    UINT8 info[AVDT_CODEC_SIZE];     /* 编解码器信息（可以是配置或功能）*/
} tBTC_AV_CODEC_INFO;

/**
 * 用于配置AV媒体馈送的结构
 */
typedef struct {
    UINT16 sampling_freq;   /* 44100、48000等*/
    UINT16 num_channel;     /* 1个用于单声道或2个立体声*/
    UINT8  bit_per_sample;  /* 每个样本的位数（8，16）*/
} tBTC_AV_MEDIA_FEED_CFG_PCM;

typedef union {
    tBTC_AV_MEDIA_FEED_CFG_PCM pcm;     /* 原始PCM馈送格式*/
} tBTC_AV_MEDIA_FEED_CFG;

typedef struct {
    tBTC_AV_CODEC_ID format;        /* 媒体编解码器标识符*/
    tBTC_AV_MEDIA_FEED_CFG cfg;     /* 媒体编解码器配置*/
} tBTC_AV_MEDIA_FEEDINGS;


#ifdef __cplusplus
}
#endif

#endif  ///BTC_AV_INCLUDED == TRUE

#endif /* __BTC_AV_API_H__ */

