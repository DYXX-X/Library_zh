/******************************************************************************
 * 版权所有（C）2003-2012 Broadcom Corporation
 *
 *  根据Apache许可证2.0版（“许可证”）获得许可；除非符合许可证，否则不得使用此文件。您可以在以下地址获取许可证副本：
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 *  除非适用法律要求或书面同意，否则根据许可证分发的软件是按“原样”分发的，无任何明示或暗示的担保或条件。有关许可证下权限和限制的具体语言，请参阅许可证。
 *
 ******************************************************************************/

/******************************************************************************
 * 这是高级音频/视频呼叫功能的接口文件。
 *
 ******************************************************************************/
#ifndef BTA_AV_CO_H
#define BTA_AV_CO_H

#include "stack/l2c_api.h"
#include "bta/bta_av_api.h"

#if (BTA_AV_INCLUDED == TRUE)

/*****************************************************************************
**  常量和数据类型
*****************************************************************************/

/* TRUE使用SCMS-T内容保护*/
#ifndef BTA_AV_CO_CP_SCMS_T
#define BTA_AV_CO_CP_SCMS_T     FALSE
#endif

/* BT SIG分配的内容保护ID*/
#define BTA_AV_CP_SCMS_T_ID     0x0002
#define BTA_AV_CP_DTCP_ID       0x0001

#define BTA_AV_CP_LOSC                  2
#define BTA_AV_CP_INFO_LEN              3

#define BTA_AV_CP_SCMS_COPY_MASK        3
#define BTA_AV_CP_SCMS_COPY_FREE        2
#define BTA_AV_CP_SCMS_COPY_ONCE        1
#define BTA_AV_CP_SCMS_COPY_NEVER       0

#define BTA_AV_CO_DEFAULT_AUDIO_OFFSET      AVDT_MEDIA_OFFSET

enum {
    BTA_AV_CO_ST_INIT,
    BTA_AV_CO_ST_IN,
    BTA_AV_CO_ST_OUT,
    BTA_AV_CO_ST_OPEN,
    BTA_AV_CO_ST_STREAM
};


/* 音频编解码器信息的数据类型*/
typedef struct {
    UINT16  bit_rate;       /* SBC编码器比特率（kbps）*/
    UINT16  bit_rate_busy;  /* SBC编码器比特率（kbps）*/
    UINT16  bit_rate_swampd;/* SBC编码器比特率（kbps）*/
    UINT8   busy_level;     /* 指示要使用的比特率的忙电平*/
    UINT8   codec_info[AVDT_CODEC_SIZE];
    UINT8   codec_type;     /* 编解码器类型*/
} tBTA_AV_AUDIO_CODEC_INFO;

/*******************************************************************************
** 函数bta_av_co_audio_init
**
** 说明当通过调用BTA_AvEnable（）启动时，AV将执行此调用函数。手机可以使用此功能来初始化音频路径或用于其他初始化目的。
**
** 返回流编解码器和内容保护功能信息。
**
*******************************************************************************/
extern BOOLEAN bta_av_co_audio_init(UINT8 *p_codec_type, UINT8 *p_codec_info,
                                    UINT8 *p_num_protect, UINT8 *p_protect_info, UINT8 tsep);

/*******************************************************************************
** 函数bta_av_co_audio_disc_res
**
** 说明此调出功能由AV执行，以报告在AVDT流发现过程中发现的流端点（SEP）数量。
**
** 返回void。
**
*******************************************************************************/
extern void bta_av_co_audio_disc_res(tBTA_AV_HNDL hndl, UINT8 num_seps,
                                     UINT8 num_snk, UINT8 num_src, BD_ADDR addr, UINT16 uuid_local);

/*******************************************************************************
** 函数bta_av_co_video_disc_res
**
** 说明此调出功能由AV执行，以报告在AVDT流发现过程中发现的流端点（SEP）数量。
**
** 返回void。
**
*******************************************************************************/
extern void bta_av_co_video_disc_res(tBTA_AV_HNDL hndl, UINT8 num_seps,
                                     UINT8 num_snk, BD_ADDR addr);

/*******************************************************************************
** 函数bta_av_co_audio_getconfig
**
** 说明此调出功能由AV执行，以检索音频流所需的编解码器和内容保护配置。
**
** 返回流编解码器和内容保护配置信息。
**
*******************************************************************************/
extern UINT8 bta_av_co_audio_getconfig(tBTA_AV_HNDL hndl, tBTA_AV_CODEC codec_type,
                                       UINT8 *p_codec_info, UINT8 *p_sep_info_idx, UINT8 seid,
                                       UINT8 *p_num_protect, UINT8 *p_protect_info);

/*******************************************************************************
** 函数bta_av_co_video_getonfig
**
** 说明此调出功能由AV执行，以检索视频流所需的编解码器和内容保护配置。
**
** 返回流编解码器和内容保护配置信息。
**
*******************************************************************************/
extern UINT8 bta_av_co_video_getconfig(tBTA_AV_HNDL hndl, tBTA_AV_CODEC codec_type,
                                       UINT8 *p_codec_info, UINT8 *p_sep_info_idx, UINT8 seid,
                                       UINT8 *p_num_protect, UINT8 *p_protect_info);

/*******************************************************************************
** 函数bta_av_co_audio_setconfig
**
** 说明此调出功能由AV执行，以设置音频流的编解码器和内容保护配置。
**
** 返回void
**
*******************************************************************************/
extern void bta_av_co_audio_setconfig(tBTA_AV_HNDL hndl, tBTA_AV_CODEC codec_type,
                                      UINT8 *p_codec_info, UINT8 seid, BD_ADDR addr,
                                      UINT8 num_protect, UINT8 *p_protect_info, UINT8 t_local_sep, UINT8 avdt_handle);

/*******************************************************************************
** 函数bta_av_co_video_setconfig
**
** 说明此调出功能由AV执行，以设置视频流的编解码器和内容保护配置。
**
** 返回void
**
*******************************************************************************/
extern void bta_av_co_video_setconfig(tBTA_AV_HNDL hndl, tBTA_AV_CODEC codec_type,
                                      UINT8 *p_codec_info, UINT8 seid, BD_ADDR addr,
                                      UINT8 num_protect, UINT8 *p_protect_info);

/*******************************************************************************
** 函数bta_av_co_audio_open
**
** 说明打开音频流连接时，AV会调用此功能。BTA-AV保持A2DP流的MTU。如果这是第二个音频流，则mtu是两个流中较小的一个。
**
** 返回void
**
*******************************************************************************/
extern void bta_av_co_audio_open(tBTA_AV_HNDL hndl,
                                 tBTA_AV_CODEC codec_type, UINT8 *p_codec_info,
                                 UINT16 mtu);

/*******************************************************************************
** 函数bta_av_co_video_open
**
** 说明打开视频流连接时，AV会调用此功能。
**
** 返回void
**
*******************************************************************************/
extern void bta_av_co_video_open(tBTA_AV_HNDL hndl,
                                 tBTA_AV_CODEC codec_type, UINT8 *p_codec_info,
                                 UINT16 mtu);

/*******************************************************************************
** 函数bta_av_co_audio_close
**
** 说明当音频流连接关闭时，AV会调用此功能。BTA-AV保持A2DP流的MTU。当一个流关闭而没有其他音频流打开时，mtu报告为0。否则，mtu保持打开。
**
** 返回void
**
*******************************************************************************/
extern void bta_av_co_audio_close(tBTA_AV_HNDL hndl, tBTA_AV_CODEC codec_type,
                                  UINT16 mtu);

/*******************************************************************************
** 函数bta_av_co_video_close
**
** 说明当视频流连接关闭时，AV会调用此功能。
**
** 返回void
**
*******************************************************************************/
extern void bta_av_co_video_close(tBTA_AV_HNDL hndl, tBTA_AV_CODEC codec_type,
                                  UINT16 mtu);

/*******************************************************************************
** 函数bta_av_co_audio_start
**
** 说明启动音频流数据传输时，AV会调用此功能。
**
** 返回void
**
*******************************************************************************/
extern void bta_av_co_audio_start(tBTA_AV_HNDL hndl, tBTA_AV_CODEC codec_type,
                                  UINT8 *p_codec_info, BOOLEAN *p_no_rtp_hdr);

/*******************************************************************************
** 函数bta_av_co_video_start
**
** 说明启动视频流数据传输时，AV会调用此功能。
**
** 返回void
**
*******************************************************************************/
extern void bta_av_co_video_start(tBTA_AV_HNDL hndl, tBTA_AV_CODEC codec_type,
                                  UINT8 *p_codec_info, BOOLEAN *p_no_rtp_hdr);

/*******************************************************************************
** 函数bta_av_co_audio_stop
**
** 说明当音频流数据传输停止时，AV会调用此功能。
**
** 返回void
**
*******************************************************************************/
extern void bta_av_co_audio_stop(tBTA_AV_HNDL hndl, tBTA_AV_CODEC codec_type);

/*******************************************************************************
** 函数bta_av_co_video_stop
**
** 说明当视频流数据传输停止时，AV会调用此功能。
**
** 返回void
**
*******************************************************************************/
extern void bta_av_co_video_stop(tBTA_AV_HNDL hndl, tBTA_AV_CODEC codec_type);

/*******************************************************************************
** 函数bta_av_co_audio_src_data_path
**
** 描述调用此函数以从音频编解码器获取下一个数据缓冲区
**
** 如果数据未就绪，则返回NULL。否则，包含音频数据的缓冲器（BT_HDR）。
**
*******************************************************************************/
extern void *bta_av_co_audio_src_data_path(tBTA_AV_CODEC codec_type,
        UINT32 *p_len, UINT32 *p_timestamp);

/*******************************************************************************
** 函数bta_av_co_video_src_data_path
**
** 描述调用此函数以从视频编解码器获取下一个数据缓冲区。
**
** 如果数据未就绪，则返回NULL。否则，视频数据缓冲器（UINT8）。
**
*******************************************************************************/
extern void *bta_av_co_video_src_data_path(tBTA_AV_CODEC codec_type,
        UINT32 *p_len, UINT32 *p_timestamp);

/*******************************************************************************
** 函数bta_av_co_audio_drop
**
** 说明音频数据包已丢弃。带此手柄的连接耳机很可能被移动得很远。该实现可能希望减小编码器比特率设置以减小分组大小。
**
** 返回void
**
*******************************************************************************/
extern void bta_av_co_audio_drop(tBTA_AV_HNDL hndl);

/*******************************************************************************
** 函数bta_av_co_video_report_conn
**
** 说明当报告通道打开（打开=TRUE）或关闭（打开=FALSE）时，AV调用此功能。
**
** 返回void
**
*******************************************************************************/
extern void bta_av_co_video_report_conn (BOOLEAN open, UINT8 avdt_handle);

/*******************************************************************************
** 函数bta_av_co_video_report_rr
**
** 说明收到接收方报告时，AV调用此功能
**
** 返回void
**
*******************************************************************************/
extern void bta_av_co_video_report_rr (UINT32 packet_lost);

/*******************************************************************************
** 函数bta_av_co_audio_delay
**
** 说明当音频流连接需要向连接的SRC发送初始延迟报告时，AV调用此功能。
**
** 返回void
**
*******************************************************************************/
extern void bta_av_co_audio_delay(tBTA_AV_HNDL hndl, UINT16 delay);

/*******************************************************************************
** 函数bta_av_co_video_lay
**
** 说明当视频流连接需要向连接的SRC发送初始延迟报告时，AV调用此功能。
**
** 返回void
**
*******************************************************************************/
extern void bta_av_co_video_delay(tBTA_AV_HNDL hndl, UINT16 delay);

#endif  ///BTA_AV_INCLUDED == TRUE

#endif /* BTA_AV_CO_H */

