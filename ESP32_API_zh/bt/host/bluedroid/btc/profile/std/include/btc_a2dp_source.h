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

/*******************************************************************************
 * 文件名：btc_a2dp_source.h
 *
 *******************************************************************************/

#ifndef __BTC_A2DP_SOURCE_H__
#define __BTC_A2DP_SOURCE_H__

#include <stdbool.h>
#include "common/bt_target.h"
#include "bta/bta_api.h"
#include "btc_av_api.h"
#include "esp_a2dp_api.h"

#if BTC_AV_SRC_INCLUDED
/*******************************************************************************
 **  数据类型
 *******************************************************************************/

/* tBTC_MEDIA_INIT_AUDIO消息结构*/
typedef struct {
    BT_HDR hdr;
    UINT16 SamplingFreq; /* 16k、32k、44.1k或48k*/
    UINT8 ChannelMode; /* 单声道、双声道、立体声或联合立体声*/
    UINT8 NumOfSubBands; /* 4或8*/
    UINT8 NumOfBlocks; /* 4、8、12或16*/
    UINT8 AllocationMethod; /* 响度或SNR*/
    UINT16 MtuSize; /* 对等mtu大小*/
} tBTC_MEDIA_INIT_AUDIO;

/* tBTC_MEDIA_UPDATE_AUDIO消息结构*/
typedef struct {
    BT_HDR hdr;
    UINT16 MinMtuSize; /* 最小对等mtu大小*/
    UINT8 MaxBitPool; /* 最大对等位池*/
    UINT8 MinBitPool; /* 最小对等位池*/
} tBTC_MEDIA_UPDATE_AUDIO;

/* tBTC_MEDIA_INIT_AUDIO_FEDING消息结构*/
typedef struct {
    BT_HDR hdr;
    tBTC_AV_FEEDING_MODE feeding_mode;
    tBTC_AV_MEDIA_FEEDINGS feeding;
} tBTC_MEDIA_INIT_AUDIO_FEEDING;

/*******************************************************************************
 **  公共职能
 *******************************************************************************/

/*******************************************************************************
 ** 函数btc_a2dp_source_startup
 **
 ** 说明初始化并启动A2DP源模块。使用模块前，BTC AV状态机应调用此功能
 **
 ** 返回TRUE表示成功
 **
 *******************************************************************************/
bool btc_a2dp_source_startup(void);

/*******************************************************************************
 ** 函数btc_a2dp_source_shutdown
 **
 ** 说明关闭并清理A2DP源模块。
 **
 *******************************************************************************/
void btc_a2dp_source_shutdown(void);

/*******************************************************************************
 ** 函数btc_a2dp_source_enc_init_req
 **
 ** 说明初始化媒体任务编码器的请求
 **
 ** 返回TRUE表示成功
 **
 *******************************************************************************/
BOOLEAN btc_a2dp_source_enc_init_req(tBTC_MEDIA_INIT_AUDIO *p_msg);

/*******************************************************************************
 ** 函数btc_a2dp_source_enc_udpate_req
 **
 ** 说明请求更新媒体任务编码器
 **
 ** 返回TRUE表示成功
 **
 *******************************************************************************/
BOOLEAN btc_a2dp_source_enc_update_req(tBTC_MEDIA_UPDATE_AUDIO *p_msg);


/*******************************************************************************
 ** 函数btc_a2dp_source_start_audio_req
 **
 ** 说明请求启动音频编码任务
 **
 ** 返回TRUE表示成功
 **
 *******************************************************************************/
BOOLEAN btc_a2dp_source_start_audio_req(void);

/*******************************************************************************
 ** 函数btc_a2dp_source_stop_audio_req
 **
 ** 说明请求停止音频编码任务
 **
 ** 返回TRUE表示成功
 **
 *******************************************************************************/
BOOLEAN btc_a2dp_source_stop_audio_req(void);

/*******************************************************************************
 ** 函数btc_a2dp_source_tx_flush_req
 **
 ** 说明请求刷新音频编码管道
 **
 ** 返回TRUE表示成功
 **
 *******************************************************************************/
BOOLEAN btc_a2dp_source_tx_flush_req(void);

/*******************************************************************************
 ** 函数btc_a2dp_source_audio_readbuf
 **
 ** 说明从BTC媒体传输队列读取音频缓冲区
 **
 ** 返回准备发送的aa缓冲区上的指针
 **
 *******************************************************************************/
BT_HDR *btc_a2dp_source_audio_readbuf(void);

/*******************************************************************************
 ** 函数btc_a2dp_source_audio_feeding_init_req
 **
 ** 说明请求初始化音频馈送
 **
 ** 如果成功，则返回TRUE
 **
 *******************************************************************************/

BOOLEAN btc_a2dp_source_audio_feeding_init_req(tBTC_MEDIA_INIT_AUDIO_FEEDING *p_msg);

/*******************************************************************************
 ** 函数btc_a2dp_source_is_streaming
 **
 ** 说明检查A2DP源是否处于流状态
 **
 *******************************************************************************/
bool btc_a2dp_source_is_streaming(void);

/*******************************************************************************
 ** 函数btc_a2dp_source_is_task_shutting_down
 **
 ** 说明检查A2DP源媒体任务是否正在关闭
 **
 *******************************************************************************/
bool btc_a2dp_source_is_task_shutting_down(void);


/*******************************************************************************
 ** 函数btc_a2dp_source_on_idle
 **
 ** 说明初始化期间来自BTC AV状态机的“空闲”请求
 **
 *******************************************************************************/
void btc_a2dp_source_on_idle(void);

/*******************************************************************************
 ** 函数btc_a2dp_source_on_stopped
 **
 ** 说明处理来自BTC AV状态机的“停止”请求，以停止A2DP流
 **
 *******************************************************************************/
void btc_a2dp_source_on_stopped(tBTA_AV_SUSPEND *p_av);

/*******************************************************************************
 ** 函数btc_a2dp_source_on_suspended
 **
 ** 说明处理来自BTC AV状态机的“暂停”请求以停止A2DP流
 **
 *******************************************************************************/
void btc_a2dp_source_on_suspended(tBTA_AV_SUSPEND *p_av);

/*******************************************************************************
 ** 函数btc_a2dp_source_setup_dec
 **
 ** 说明初始化编码器参数
 **
 *******************************************************************************/
void btc_a2dp_source_setup_codec(void);

/*******************************************************************************
 ** 函数btc_a2dp_source_set_tx_flush
 **
 ** 描述启用/禁用丢弃传输帧
 **
 *******************************************************************************/
void btc_a2dp_source_set_tx_flush(BOOLEAN enable);

/*******************************************************************************
 ** 函数btc_a2dp_source_encoder_update
 **
 ** 描述更新更改的SBC编码器参数
 **
 *******************************************************************************/
void btc_a2dp_source_encoder_update(void);

#endif /* #如果BTC_AV_SRC_INCLUDED*/

#endif /* __BTC_A2DP_SOURCE_H__ */
