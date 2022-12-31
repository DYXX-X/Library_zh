/******************************************************************************
 * 版权所有（C）2004-2012 Broadcom Corporation
 *
 *  根据Apache许可证2.0版（“许可证”）获得许可；除非符合许可证，否则不得使用此文件。您可以在以下地址获取许可证副本：
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 *  除非适用法律要求或书面同意，否则根据许可证分发的软件是按“原样”分发的，无任何明示或暗示的担保或条件。有关许可证下权限和限制的具体语言，请参阅许可证。
 *
 ******************************************************************************/

/******************************************************************************
 * 这是BTA高级音频/视频流（AV）子系统的公共接口文件，BTA是Broadcom的移动电话蓝牙应用层。
 *
 ******************************************************************************/
#ifndef BTA_AV_API_H
#define BTA_AV_API_H

#include "stack/avrc_api.h"
#include "stack/avdt_api.h"
#include "stack/a2d_api.h"
#include "bta/bta_api.h"

#if (BTA_AV_INCLUDED == TRUE)

/*****************************************************************************
**  常量和数据类型
*****************************************************************************/
/* AV状态值*/
#define BTA_AV_SUCCESS          0       /* 成功的操作*/
#define BTA_AV_FAIL             1       /* 一般性故障*/
#define BTA_AV_FAIL_SDP         2       /* 未找到服务*/
#define BTA_AV_FAIL_STREAM      3       /* 流连接失败*/
#define BTA_AV_FAIL_RESOURCES   4       /* 没有资源*/
#define BTA_AV_FAIL_ROLE        5       /* 由于角色管理相关问题而失败*/
#define BTA_AV_FAIL_GET_CAP     6       /* 由于对等端上没有SEP可用，获取功能失败*/

typedef UINT8 tBTA_AV_STATUS;

/* AV功能掩码*/
#define BTA_AV_FEAT_RCTG        0x0001  /* 遥控目标*/
#define BTA_AV_FEAT_RCCT        0x0002  /* 遥控控制器*/
#define BTA_AV_FEAT_PROTECT     0x0004  /* 流媒体冲突保护*/
#define BTA_AV_FEAT_VENDOR      0x0008  /* 远程控制供应商相关命令*/
#define BTA_AV_FEAT_REPORT      0x0020  /* 使用VDP的报告服务*/
#define BTA_AV_FEAT_METADATA    0x0040  /* 远程控制元数据传输命令/响应*/
#define BTA_AV_FEAT_MULTI_AV    0x0080  /* 如果控制器支持，请使用多av*/
#define BTA_AV_FEAT_BROWSE      0x0010  /* 使用浏览频道*/
#define BTA_AV_FEAT_MASTER      0x0100  /* 仅作为主角色流*/
#define BTA_AV_FEAT_ADV_CTRL    0x0200  /* 远程控制高级控制命令/响应*/
#define BTA_AV_FEAT_DELAY_RPT   0x0400  /* 允许延迟报告*/
#define BTA_AV_FEAT_ACP_START   0x0800  /* 接受第二个SNK时开始流*/

/* 内部特征*/
#define BTA_AV_FEAT_NO_SCO_SSPD 0x8000  /* 对于AG事件（SCO或Call），不要暂停av流*/

typedef UINT16 tBTA_AV_FEAT;

/* AV频道值*/
#define BTA_AV_CHNL_MSK             0xC0
#define BTA_AV_CHNL_AUDIO           0x40  /* 音频通道*/
#define BTA_AV_CHNL_VIDEO           0x80  /* 视频频道*/
typedef UINT8 tBTA_AV_CHNL;


#define BTA_AV_HNDL_MSK             0x3F
typedef UINT8 tBTA_AV_HNDL;
/* 掩码的句柄索引*/
#define BTA_AV_HNDL_TO_MSK(h)       ((UINT8)(1 << (h)))

/* tBTA_AV_HNDL至掩码*/
#define BTA_AV_HNDL_TYPE_TO_MSK(h)  ((UINT8)(1 << (h&BTA_AV_HNDL_MSK)))

/* 编解码器信息字节数组中编解码器类型的偏移*/
#define BTA_AV_CODEC_TYPE_IDX       AVDT_CODEC_TYPE_INDEX   /* 2 */



/* 创建的最大流数：1个用于音频，1个用于视频*/
#ifndef BTA_AV_NUM_STRS
#define BTA_AV_NUM_STRS         2
#endif

#ifndef BTA_AV_MAX_SEPS
#define BTA_AV_MAX_SEPS         1
#endif

#ifndef BTA_AV_MAX_A2DP_MTU
/*#定义BTA_AV_MAX_A2DP_MTU 668//224（DM5）*3-4（L2CAP标头）*/
#define BTA_AV_MAX_A2DP_MTU     1008
#endif

#ifndef BTA_AV_MAX_VDP_MTU
#define BTA_AV_MAX_VDP_MTU      1008
#endif


/* 编解码器类型*/
#define BTA_AV_CODEC_SBC        A2D_MEDIA_CT_SBC        /* SBC媒体编解码器类型*/
#define BTA_AV_CODEC_M12        A2D_MEDIA_CT_M12        /* MPEG-1，2音频媒体编解码器类型*/
#define BTA_AV_CODEC_M24        A2D_MEDIA_CT_M24        /* MPEG-2，4 AAC媒体编解码器类型*/
#define BTA_AV_CODEC_ATRAC      A2D_MEDIA_CT_ATRAC      /* ATRAC系列媒体编解码器类型*/
#define BTA_AV_CODEC_H263_P0    VDP_MEDIA_CT_H263_P0    /* H、 263基线（配置文件0）*/
#define BTA_AV_CODEC_MPEG4      VDP_MEDIA_CT_MPEG4      /* MPEG-4视觉简单配置文件*/
#define BTA_AV_CODEC_H263_P3    VDP_MEDIA_CT_H263_P3    /* H、 263剖面图3*/
#define BTA_AV_CODEC_H263_P8    VDP_MEDIA_CT_H263_P8    /* H、 263剖面图8*/
#define BTA_AV_CODEC_VEND       VDP_MEDIA_CT_VEND       /* 非VDP*/

typedef UINT8 tBTA_AV_CODEC;

/* BT分配号码中的公司ID*/
#define BTA_AV_BT_VENDOR_ID     VDP_BT_VENDOR_ID        /* 博通公司*/

/* 供应商特定的编解码器ID*/
#define BTA_AV_CODEC_ID_H264    VDP_CODEC_ID_H264       /* 非VDP编解码器ID-H.264*/
#define BTA_AV_CODEC_ID_IMG     VDP_CODEC_ID_IMG        /* 非VDP编解码器ID-图像/幻灯片*/

/* BTA_AvRemoteCmd的操作id列表*/
#define BTA_AV_RC_SELECT        AVRC_ID_SELECT      /* 选择*/
#define BTA_AV_RC_UP            AVRC_ID_UP          /* 向上的*/
#define BTA_AV_RC_DOWN          AVRC_ID_DOWN        /* 向下*/
#define BTA_AV_RC_LEFT          AVRC_ID_LEFT        /* 左边*/
#define BTA_AV_RC_RIGHT         AVRC_ID_RIGHT       /* 正确的*/
#define BTA_AV_RC_RIGHT_UP      AVRC_ID_RIGHT_UP    /* 向上*/
#define BTA_AV_RC_RIGHT_DOWN    AVRC_ID_RIGHT_DOWN  /* 向右向下*/
#define BTA_AV_RC_LEFT_UP       AVRC_ID_LEFT_UP     /* 左上*/
#define BTA_AV_RC_LEFT_DOWN     AVRC_ID_LEFT_DOWN   /* 左下*/
#define BTA_AV_RC_ROOT_MENU     AVRC_ID_ROOT_MENU   /* 根菜单*/
#define BTA_AV_RC_SETUP_MENU    AVRC_ID_SETUP_MENU  /* 设置菜单*/
#define BTA_AV_RC_CONT_MENU     AVRC_ID_CONT_MENU   /* 目录菜单*/
#define BTA_AV_RC_FAV_MENU      AVRC_ID_FAV_MENU    /* 收藏夹菜单*/
#define BTA_AV_RC_EXIT          AVRC_ID_EXIT        /* 出口*/
#define BTA_AV_RC_0             AVRC_ID_0           /* 0 */
#define BTA_AV_RC_1             AVRC_ID_1           /* 1 */
#define BTA_AV_RC_2             AVRC_ID_2           /* 2 */
#define BTA_AV_RC_3             AVRC_ID_3           /* 3 */
#define BTA_AV_RC_4             AVRC_ID_4           /* 4 */
#define BTA_AV_RC_5             AVRC_ID_5           /* 5 */
#define BTA_AV_RC_6             AVRC_ID_6           /* 6 */
#define BTA_AV_RC_7             AVRC_ID_7           /* 7 */
#define BTA_AV_RC_8             AVRC_ID_8           /* 8 */
#define BTA_AV_RC_9             AVRC_ID_9           /* 9 */
#define BTA_AV_RC_DOT           AVRC_ID_DOT         /* 点*/
#define BTA_AV_RC_ENTER         AVRC_ID_ENTER       /* 进来*/
#define BTA_AV_RC_CLEAR         AVRC_ID_CLEAR       /* 清楚的*/
#define BTA_AV_RC_CHAN_UP       AVRC_ID_CHAN_UP     /* 通道向上*/
#define BTA_AV_RC_CHAN_DOWN     AVRC_ID_CHAN_DOWN   /* 通道关闭*/
#define BTA_AV_RC_PREV_CHAN     AVRC_ID_PREV_CHAN   /* 前一频道*/
#define BTA_AV_RC_SOUND_SEL     AVRC_ID_SOUND_SEL   /* 声音选择*/
#define BTA_AV_RC_INPUT_SEL     AVRC_ID_INPUT_SEL   /* 输入选择*/
#define BTA_AV_RC_DISP_INFO     AVRC_ID_DISP_INFO   /* 显示信息*/
#define BTA_AV_RC_HELP          AVRC_ID_HELP        /* 帮助*/
#define BTA_AV_RC_PAGE_UP       AVRC_ID_PAGE_UP     /* 向上翻页*/
#define BTA_AV_RC_PAGE_DOWN     AVRC_ID_PAGE_DOWN   /* 向下翻页*/
#define BTA_AV_RC_POWER         AVRC_ID_POWER       /* 权力*/
#define BTA_AV_RC_VOL_UP        AVRC_ID_VOL_UP      /* 音量增大*/
#define BTA_AV_RC_VOL_DOWN      AVRC_ID_VOL_DOWN    /* 音量降低*/
#define BTA_AV_RC_MUTE          AVRC_ID_MUTE        /* 沉默的*/
#define BTA_AV_RC_PLAY          AVRC_ID_PLAY        /* 玩*/
#define BTA_AV_RC_STOP          AVRC_ID_STOP        /* 停止*/
#define BTA_AV_RC_PAUSE         AVRC_ID_PAUSE       /* 暂停*/
#define BTA_AV_RC_RECORD        AVRC_ID_RECORD      /* 记录*/
#define BTA_AV_RC_REWIND        AVRC_ID_REWIND      /* 重绕*/
#define BTA_AV_RC_FAST_FOR      AVRC_ID_FAST_FOR    /* 快进*/
#define BTA_AV_RC_EJECT         AVRC_ID_EJECT       /* 弹出*/
#define BTA_AV_RC_FORWARD       AVRC_ID_FORWARD     /* 向前地*/
#define BTA_AV_RC_BACKWARD      AVRC_ID_BACKWARD    /* 向后的*/
#define BTA_AV_RC_ANGLE         AVRC_ID_ANGLE       /* 角*/
#define BTA_AV_RC_SUBPICT       AVRC_ID_SUBPICT     /* 子画面*/
#define BTA_AV_RC_F1            AVRC_ID_F1          /* F1 */
#define BTA_AV_RC_F2            AVRC_ID_F2          /* F2 */
#define BTA_AV_RC_F3            AVRC_ID_F3          /* F3 */
#define BTA_AV_RC_F4            AVRC_ID_F4          /* F4 */
#define BTA_AV_RC_F5            AVRC_ID_F5          /* F5 */
#define BTA_AV_VENDOR           AVRC_ID_VENDOR      /* 供应商独有*/

typedef UINT8 tBTA_AV_RC;

/* 传递命令的状态标志*/
#define BTA_AV_STATE_PRESS      AVRC_STATE_PRESS    /* 按键已按下*/
#define BTA_AV_STATE_RELEASE    AVRC_STATE_RELEASE  /* 密钥已释放*/

typedef UINT8 tBTA_AV_STATE;

/* BTA_AvVendorCmd的命令代码*/
#define BTA_AV_CMD_CTRL         AVRC_CMD_CTRL
#define BTA_AV_CMD_STATUS       AVRC_CMD_STATUS
#define BTA_AV_CMD_SPEC_INQ     AVRC_CMD_SPEC_INQ
#define BTA_AV_CMD_NOTIF        AVRC_CMD_NOTIF
#define BTA_AV_CMD_GEN_INQ      AVRC_CMD_GEN_INQ

typedef UINT8 tBTA_AV_CMD;

/* BTA_AvVendorRsp的响应代码*/
#define BTA_AV_RSP_NOT_IMPL     AVRC_RSP_NOT_IMPL
#define BTA_AV_RSP_ACCEPT       AVRC_RSP_ACCEPT
#define BTA_AV_RSP_REJ          AVRC_RSP_REJ
#define BTA_AV_RSP_IN_TRANS     AVRC_RSP_IN_TRANS
#define BTA_AV_RSP_IMPL_STBL    AVRC_RSP_IMPL_STBL
#define BTA_AV_RSP_CHANGED      AVRC_RSP_CHANGED
#define BTA_AV_RSP_INTERIM      AVRC_RSP_INTERIM

typedef UINT8 tBTA_AV_CODE;

/* BTA_AvProtectRsp的错误代码*/
#define BTA_AV_ERR_NONE             A2D_SUCCESS         /* 成功，无错误*/
#define BTA_AV_ERR_BAD_STATE        AVDT_ERR_BAD_STATE  /* 无法在此状态下处理消息*/
#define BTA_AV_ERR_RESOURCE         AVDT_ERR_RESOURCE   /* 资源不足*/
#define BTA_AV_ERR_BAD_CP_TYPE      A2D_BAD_CP_TYPE     /* 不支持请求的内容保护类型*/
#define BTA_AV_ERR_BAD_CP_FORMAT    A2D_BAD_CP_FORMAT   /* 内容保护数据的格式不正确*/

typedef UINT8 tBTA_AV_ERR;


/* AV回调事件*/
#define BTA_AV_ENABLE_EVT       0       /* AV已启用*/
#define BTA_AV_REGISTER_EVT     1       /* 注册到AVDT*/
#define BTA_AV_OPEN_EVT         2       /* 连接已打开*/
#define BTA_AV_CLOSE_EVT        3       /* 连接已关闭*/
#define BTA_AV_START_EVT        4       /* 流数据传输已启动*/
#define BTA_AV_STOP_EVT         5       /* 流数据传输已停止*/
#define BTA_AV_PROTECT_REQ_EVT  6       /* 内容保护请求*/
#define BTA_AV_PROTECT_RSP_EVT  7       /* 内容保护响应*/
#define BTA_AV_RC_OPEN_EVT      8       /* 遥控通道打开*/
#define BTA_AV_RC_CLOSE_EVT     9       /* 遥控通道关闭*/
#define BTA_AV_REMOTE_CMD_EVT   10      /* 远程控制命令*/
#define BTA_AV_REMOTE_RSP_EVT   11      /* 遥控器响应*/
#define BTA_AV_VENDOR_CMD_EVT   12      /* 依赖于供应商的远程控制命令*/
#define BTA_AV_VENDOR_RSP_EVT   13      /* 依赖于供应商的远程控制响应*/
#define BTA_AV_RECONFIG_EVT     14      /* 重新配置响应*/
#define BTA_AV_SUSPEND_EVT      15      /* 暂停响应*/
#define BTA_AV_PENDING_EVT      16      /* 传入连接挂起：BTA_AV_SIG_TIME_VAL ms后信号通道打开且流未打开**/
#define BTA_AV_META_MSG_EVT     17      /* 元数据消息*/
#define BTA_AV_REJECT_EVT       18      /* 传入连接被拒绝*/
#define BTA_AV_RC_FEAT_EVT      19      /* 远程控制信道对等支持的功能更新*/
#define BTA_AV_MEDIA_SINK_CFG_EVT    20      /* 配置编解码器的命令*/
#define BTA_AV_MEDIA_DATA_EVT   21      /* 向媒体任务发送数据*/
/* 最大BTA事件*/
#define BTA_AV_MAX_EVT          22


/* 调用函数的函数类型*/
typedef BOOLEAN (*tBTA_AV_CO_INIT) (UINT8 *p_codec_type, UINT8 *p_codec_info,
                                    UINT8 *p_num_protect, UINT8 *p_protect_info, UINT8 tsep);
typedef void (*tBTA_AV_CO_DISC_RES) (tBTA_AV_HNDL hndl, UINT8 num_seps,
                                     UINT8 num_snk, UINT8 num_src, BD_ADDR addr, UINT16 uuid_local);
typedef UINT8 (*tBTA_AV_CO_GETCFG) (tBTA_AV_HNDL hndl, tBTA_AV_CODEC codec_type,
                                    UINT8 *p_codec_info, UINT8 *p_sep_info_idx, UINT8 seid,
                                    UINT8 *p_num_protect, UINT8 *p_protect_info);
typedef void (*tBTA_AV_CO_SETCFG) (tBTA_AV_HNDL hndl, tBTA_AV_CODEC codec_type,
                                   UINT8 *p_codec_info, UINT8 seid, BD_ADDR addr,
                                   UINT8 num_protect, UINT8 *p_protect_info,
                                   UINT8 t_local_sep, UINT8 avdt_handle);
typedef void (*tBTA_AV_CO_OPEN) (tBTA_AV_HNDL hndl,
                                 tBTA_AV_CODEC codec_type, UINT8 *p_codec_info,
                                 UINT16 mtu);
typedef void (*tBTA_AV_CO_CLOSE) (tBTA_AV_HNDL hndl, tBTA_AV_CODEC codec_type, UINT16 mtu);
typedef void (*tBTA_AV_CO_START) (tBTA_AV_HNDL hndl, tBTA_AV_CODEC codec_type, UINT8 *p_codec_info, BOOLEAN *p_no_rtp_hdr);
typedef void (*tBTA_AV_CO_STOP) (tBTA_AV_HNDL hndl, tBTA_AV_CODEC codec_type);
typedef void *(*tBTA_AV_CO_DATAPATH) (tBTA_AV_CODEC codec_type,
                                      UINT32 *p_len, UINT32 *p_timestamp);
typedef void (*tBTA_AV_CO_DELAY) (tBTA_AV_HNDL hndl, UINT16 delay);

///AVRCP调出功能
// 检查是否支持PASSTHROUGH命令
typedef BOOLEAN (*tBTA_AVRC_CO_CMD_ALLOWED) (tBTA_AV_RC rc_id);
// 获取事件通知功能
typedef UINT8 (*tBTA_AVRC_CO_RN_EVT_CAP) (UINT8 *event_ids);
// 检查是否支持event_id
typedef BOOLEAN (*tBTA_AVRC_CO_RN_EVT_SUPPORTED) (UINT8 event_id);

/* 一个流的调用函数*/
typedef struct {
    tBTA_AV_CO_INIT               init;
    tBTA_AV_CO_DISC_RES           disc_res;
    tBTA_AV_CO_GETCFG             getcfg;
    tBTA_AV_CO_SETCFG             setcfg;
    tBTA_AV_CO_OPEN               open;
    tBTA_AV_CO_CLOSE              close;
    tBTA_AV_CO_START              start;
    tBTA_AV_CO_STOP               stop;
    tBTA_AV_CO_DATAPATH           data;
    tBTA_AV_CO_DELAY              delay;
} tBTA_AV_CO_FUNCTS;

/* AVRCP的调出功能*/
typedef struct {
    tBTA_AVRC_CO_CMD_ALLOWED         rc_cmd;
    tBTA_AVRC_CO_RN_EVT_CAP          rn_evt_cap;
    tBTA_AVRC_CO_RN_EVT_SUPPORTED    rn_evt_supported;
} tBTA_AVRC_CO_FUNCTS;

typedef UINT8 tBTA_AV_EVT;

/* 与BTA_AV_ENABLE_EVT相关的事件*/
typedef struct {
    tBTA_AV_FEAT    features;
} tBTA_AV_ENABLE;

/* 与BTA_AV_REGISTER_EVT相关的事件*/
typedef struct {
    tBTA_AV_CHNL    chnl;       /* 音频/视频*/
    tBTA_AV_HNDL    hndl;       /* 与流关联的句柄。*/
    UINT8           app_id;     /* 与调用BTA_AvRegister（）关联的ID*/
    tBTA_AV_STATUS  status;
    tBTA_AV_CO_FUNCTS *p_bta_av_cos;
    tBTA_AVRC_CO_FUNCTS *p_bta_avrc_cos;
} tBTA_AV_REGISTER;

/* 与BTA_AV_OPEN_EVT相关的数据*/
#define BTA_AV_EDR_2MBPS        0x01
#define BTA_AV_EDR_3MBPS        0x02
typedef UINT8 tBTA_AV_EDR;

typedef struct {
    tBTA_AV_CHNL    chnl;
    tBTA_AV_HNDL    hndl;
    BD_ADDR         bd_addr;
    tBTA_AV_STATUS  status;
    BOOLEAN         starting;
    tBTA_AV_EDR     edr;        /* 0，如果对等设备不支持EDR*/
    UINT8           sep;        /*  对等设备的sep类型*/
} tBTA_AV_OPEN;

/* 与BTA_AV_CLOSE_EVT相关的数据*/
typedef struct {
    tBTA_AV_CHNL    chnl;
    tBTA_AV_HNDL    hndl;
    UINT8           disc_rsn;    /* 断开连接原因*/
} tBTA_AV_CLOSE;

/* 与BTA_AV_START_EVT相关的数据*/
typedef struct {
    tBTA_AV_CHNL    chnl;
    tBTA_AV_HNDL    hndl;
    tBTA_AV_STATUS  status;
    BOOLEAN         initiator; /* TRUE，如果本地设备启动START*/
    BOOLEAN         suspending;
} tBTA_AV_START;

/* 与BTA_AV_SUSPEND_EVT相关的数据*/
typedef struct {
    tBTA_AV_CHNL    chnl;
    tBTA_AV_HNDL    hndl;
    BOOLEAN         initiator; /* TRUE，如果本地设备启动SUSPEND*/
    tBTA_AV_STATUS  status;
} tBTA_AV_SUSPEND;

/* 与BTA_AV_RECONFIG_EVT相关的数据*/
typedef struct {
    tBTA_AV_CHNL    chnl;
    tBTA_AV_HNDL    hndl;
    tBTA_AV_STATUS  status;
} tBTA_AV_RECONFIG;

/* 与BTA_AV_PROTECT_REQ_EVT相关的数据*/
typedef struct {
    tBTA_AV_CHNL    chnl;
    tBTA_AV_HNDL    hndl;
    UINT8           *p_data;
    UINT16          len;
} tBTA_AV_PROTECT_REQ;

/* 与BTA_AV_PROTECT_RSP_EVT相关的数据*/
typedef struct {
    tBTA_AV_CHNL    chnl;
    tBTA_AV_HNDL    hndl;
    UINT8           *p_data;
    UINT16          len;
    tBTA_AV_ERR     err_code;
} tBTA_AV_PROTECT_RSP;

/* 与BTA_AV_RC_OPEN_EVT相关的数据*/
typedef struct {
    UINT8           rc_handle;
    BOOLEAN         sdp_disc_done;
    tBTA_AV_FEAT    peer_features;
    UINT16          peer_ct_features;
    UINT16          peer_tg_features;
    BD_ADDR         peer_addr;
    tBTA_AV_STATUS  status;
} tBTA_AV_RC_OPEN;

/* 与BTA_AV_RC_CLOSE_EVT相关的数据*/
typedef struct {
    UINT8           rc_handle;
    BD_ADDR         peer_addr;
} tBTA_AV_RC_CLOSE;

/* 与BTA_AV_RC_FEAT_EVT相关的数据*/
typedef struct {
    UINT8           rc_handle;
    tBTA_AV_FEAT    peer_features;
    UINT16          peer_ct_features;
    UINT16          peer_tg_features;
} tBTA_AV_RC_FEAT;

/* 与BTA_AV_REMOTE_CMD_EVT相关的数据*/
typedef struct {
    UINT8           rc_handle;
    tBTA_AV_RC      rc_id;
    tBTA_AV_STATE   key_state;
    UINT8           len;
    UINT8           *p_data;
    tAVRC_HDR       hdr;    /* 消息头。*/
    UINT8           label;
} tBTA_AV_REMOTE_CMD;

/* 与BTA_AV_REMOTE_RSP_VT相关的数据*/
typedef struct {
    UINT8           rc_handle;
    tBTA_AV_RC      rc_id;
    tBTA_AV_STATE   key_state;
    UINT8           len;
    UINT8           *p_data;
    tBTA_AV_CODE    rsp_code;
    UINT8           label;
} tBTA_AV_REMOTE_RSP;

/* 与BTA_AV_VENDOR_CMD_EVT、BTA_AV-VENDOR_RSP_EVT相关的数据*/
typedef struct {
    UINT8           rc_handle;
    UINT16          len;            /* 最大供应商相关消息为512*/
    UINT8           label;
    tBTA_AV_CODE    code;
    UINT32          company_id;
    UINT8           *p_data;
} tBTA_AV_VENDOR;

/* 与BTA_AV_META_MSG_EVT相关的数据*/
typedef struct {
    UINT8           rc_handle;
    UINT16          len;
    UINT8           label;
    tBTA_AV_CODE    code;
    UINT32          company_id;
    UINT8           *p_data;
    tAVRC_MSG       *p_msg;
} tBTA_AV_META_MSG;

/* 与BTA_AV_PENDING_EVT相关的数据*/
typedef struct {
    BD_ADDR         bd_addr;
} tBTA_AV_PEND;

/* 与BTA_AV_REJECT_EVT相关的数据*/
typedef struct {
    BD_ADDR         bd_addr;
    tBTA_AV_HNDL    hndl;       /* 与拒绝连接的流关联的句柄。*/
} tBTA_AV_REJECT;


/* 与AV回调相关的数据的并集*/
typedef union {
    tBTA_AV_CHNL        chnl;
    tBTA_AV_ENABLE      enable;
    tBTA_AV_REGISTER    registr;
    tBTA_AV_OPEN        open;
    tBTA_AV_CLOSE       close;
    tBTA_AV_START       start;
    tBTA_AV_PROTECT_REQ protect_req;
    tBTA_AV_PROTECT_RSP protect_rsp;
    tBTA_AV_RC_OPEN     rc_open;
    tBTA_AV_RC_CLOSE    rc_close;
    tBTA_AV_REMOTE_CMD  remote_cmd;
    tBTA_AV_REMOTE_RSP  remote_rsp;
    tBTA_AV_VENDOR      vendor_cmd;
    tBTA_AV_VENDOR      vendor_rsp;
    tBTA_AV_RECONFIG    reconfig;
    tBTA_AV_SUSPEND     suspend;
    tBTA_AV_PEND        pend;
    tBTA_AV_META_MSG    meta_msg;
    tBTA_AV_REJECT      reject;
    tBTA_AV_RC_FEAT     rc_feat;
} tBTA_AV;

/* 与AV媒体回调相关的数据联合*/
typedef union {
    BT_HDR     *p_data;
    UINT8      *codec_info;
} tBTA_AV_MEDIA;


#define BTA_AVC_PACKET_LEN                  AVRC_PACKET_LEN
#define BTA_VENDOR_DATA_OFFSET              6
#define BTA_VENDOR_HEADER_LEN               4
#define BTA_MAX_VENDOR_DEPENDENT_DATA_LEN   (BTA_AVC_PACKET_LEN-BTA_VENDOR_DATA_OFFSET-BTA_VENDOR_HEADER_LEN)
#define BTA_GROUP_NAVI_MSG_OP_DATA_LEN      5

#define BTA_ERROR_INVALID_CMD           AVRC_STS_BAD_CMD
#define BTA_ERROR_INVALID_PARAM         AVRC_STS_BAD_PARAM
#define BTA_ERROR_BAD_CONTENTS          AVRC_STS_NOT_FOUND
#define BTA_ERROR_INTERNAL              AVRC_STS_INTERNAL_ERR

#define BTA_AV_META_SINGLE_PACKET       AVRC_PKT_SINGLE

#define BTA_AV_CO_METADATA              AVRC_CO_METADATA

/* AV回拨*/
typedef void (tBTA_AV_CBACK)(tBTA_AV_EVT event, tBTA_AV *p_data);
typedef void (tBTA_AV_DATA_CBACK)(tBTA_AV_EVT event, tBTA_AV_MEDIA *p_data);

/* 流状态机操作函数的类型*/
typedef void (*tBTA_AV_ACT)(void *p_cb, void *p_data);

/* 用于注册VDP的类型*/
typedef void (tBTA_AV_REG) (tAVDT_CS *p_cs, char *p_service_name, void *p_data);

/* AV配置结构*/
typedef struct {
    UINT32  company_id;         /* AVRCP公司ID*/
    UINT16  avrc_mtu;           /* 控制信道L2CAP处的AVRCP MTU*/
    UINT16  avrc_br_mtu;        /* 用于浏览频道的L2CAP AVRCP MTU*/
    UINT16  avrc_snk_ct_cat;    /* AVRCP控制器类别为SNK*/
    UINT16  avrc_snk_tg_cat;    /* AVRCP目标类别SNK*/
    UINT16  avrc_src_ct_cat;    /* AVRCP控制器类别为SRC*/
    UINT16  avrc_src_tg_cat;    /* AVRCP目标类别为SRC*/
    UINT16  sig_mtu;            /* L2CAP处的AVDTP信令信道MTU*/
    UINT16  audio_mtu;          /* L2CAP上的AVDTP音频传输通道MTU*/
    const UINT16 *p_audio_flush_to;/* AVDTP音频传输通道刷新超时*/
    UINT16  audio_mqs;          /* AVDTP音频通道最大数据队列大小*/
    UINT16  video_mtu;          /* L2CAP上的AVDTP视频传输信道MTU*/
    UINT16  video_flush_to;     /* AVDTP视频传输通道刷新超时*/
    BOOLEAN avrc_group;         /* TRUE，接受AVRC 1.3组调查命令*/
    UINT8   num_co_ids;         /* p_meta_co_ids中的公司id计数*/
    tBTA_AV_CODE  rc_pass_rsp;  /* 传递命令的默认响应代码*/
    const UINT32 *p_meta_co_ids;/* 公司id的元数据“获取能力”响应*/
    const tBTA_AV_ACT *p_act_tbl;/* VDP流的动作函数表*/
    tBTA_AV_REG       *p_reg;   /* 寄存器VDP的动作函数*/
    char              avrc_controller_name[BTA_SERVICE_NAME_LEN]; /* 默认AVRCP控制器名称*/
    char              avrc_target_name[BTA_SERVICE_NAME_LEN];     /* 默认AVRCP目标名称*/
} tBTA_AV_CFG;

#ifdef __cplusplus
extern "C"
{
#endif

/*****************************************************************************
**  外部函数声明
*****************************************************************************/

/*******************************************************************************
** 功能BTA_AvEnable
**
** 说明启用高级音频/视频服务。启用操作完成后，将使用BTA_AV_enable_EVT调用回调函数。在调用AV API中的其他函数之前，必须先调用此函数。
**
** 返回void
**
*******************************************************************************/
void BTA_AvEnable(tBTA_SEC sec_mask, tBTA_AV_FEAT features,
                  tBTA_AV_CBACK *p_cback);

/*******************************************************************************
** 功能BTA_AvDisable
**
** 说明禁用高级音频/视频服务。
**
** 返回void
**
*******************************************************************************/
void BTA_AvDisable(void);

/*******************************************************************************
** 函数BTA_AvRegister
**
** 说明将音频或视频服务注册到堆栈。操作完成后，将使用BTA_AV_REGISTER_EVT调用回调函数。必须在AVDT流打开之前调用此函数。
**
** 返回void
**
*******************************************************************************/
void BTA_AvRegister(tBTA_AV_CHNL chnl, const char *p_service_name,
                    UINT8 app_id, tBTA_AV_DATA_CBACK  *p_data_cback,
                    tBTA_AV_CO_FUNCTS *bta_av_cos, tBTA_AVRC_CO_FUNCTS *bta_avrc_cos,
                    UINT8 tsep);

/*******************************************************************************
** 函数BTA_AvDeregister
**
** 说明取消注册音频或视频服务
**
** 返回void
**
*******************************************************************************/
void BTA_AvDeregister(tBTA_AV_HNDL hndl);

/*******************************************************************************
** 函数BTA_AvOpen
**
** 说明打开到对等设备的高级音频/视频连接。当连接打开时，使用BTA_AV_open_EVT调用回调函数。
**
** 返回void
**
*******************************************************************************/
void BTA_AvOpen(BD_ADDR bd_addr, tBTA_AV_HNDL handle,
                BOOLEAN use_rc, tBTA_SEC sec_mask, UINT16 uuid);

/*******************************************************************************
** 函数BTA_AvClose
**
** 说明关闭当前流。
**
** 返回void
**
*******************************************************************************/
void BTA_AvClose(tBTA_AV_HNDL handle);

/*******************************************************************************
** 功能BTA_AvDisconnect
**
** 说明关闭与地址的连接。
**
** 返回void
**
*******************************************************************************/
void BTA_AvDisconnect(BD_ADDR bd_addr);

/*******************************************************************************
** 函数BTA_AvEnable_Sink
**
** 说明启用/禁用A2DP接收器。
**
** 返回void
**
*******************************************************************************/
void BTA_AvEnable_Sink(int enable);

/*******************************************************************************
** 函数BTA_AvStart
**
** 说明开始音频/视频流数据传输。
**
** 返回void
**
*******************************************************************************/
void BTA_AvStart(void);

/*******************************************************************************
** 函数BTA_AvStop
**
** 说明停止音频/视频流数据传输。如果suspend为TRUE，则此函数将AVDT suspend信号发送到连接的对等端。
**
** 返回void
**
*******************************************************************************/
void BTA_AvStop(BOOLEAN suspend);

/*******************************************************************************
** 函数BTA_AvReconfig
**
** 说明重新配置音频/视频流。如果suspend为TRUE，则此函数将首先尝试suspend/reconfigurate过程。如果suspend为FALSE或suspend/reconfigure失败，此功能将关闭并重新打开AVDT连接。
**
** 返回void
**
*******************************************************************************/
void BTA_AvReconfig(tBTA_AV_HNDL hndl, BOOLEAN suspend, UINT8 sep_info_idx,
                    UINT8 *p_codec_info, UINT8 num_protect, UINT8 *p_protect_info);

/*******************************************************************************
** 函数BTA_AvProtectReq
**
** 说明发送内容保护请求。仅当使用BTA_AV_FEAT_PROTECT功能启用AV时，才能使用此功能。
**
** 返回void
**
*******************************************************************************/
void BTA_AvProtectReq(tBTA_AV_HNDL hndl, UINT8 *p_data, UINT16 len);

/*******************************************************************************
** 函数BTA_AvProtectRsp
**
** 说明发送内容保护响应。如果收到BTA_AV_PROTECT_REQ_EVT，则必须调用此函数。仅当使用BTA_AV_FEAT_PROTECT功能启用AV时，才能使用此功能。
**
** 返回void
**
*******************************************************************************/
void BTA_AvProtectRsp(tBTA_AV_HNDL hndl, UINT8 error_code, UINT8 *p_data,
                      UINT16 len);

/*******************************************************************************
** 函数BTA_AvRemoteCmd
**
** 说明发送远程控制命令。仅当使用BTA_AV_FEAT_RCCT功能启用AV时，才能使用此功能。
**
** 返回void
**
*******************************************************************************/
void BTA_AvRemoteCmd(UINT8 rc_handle, UINT8 label, tBTA_AV_RC rc_id,
                     tBTA_AV_STATE key_state);

/*******************************************************************************
** 函数BTA_AvVendorCmd
**
** 说明发送依赖于供应商的远程控制命令。仅当使用BTA_AV_FEAT_VENDOR功能启用AV时，才能使用此功能。
**
** 返回void
**
*******************************************************************************/
void BTA_AvVendorCmd(UINT8 rc_handle, UINT8 label, tBTA_AV_CODE cmd_code,
                     UINT8 *p_data, UINT16 len);

/*******************************************************************************
** 函数BTA_AvVendorRsp
**
** 说明发送依赖于供应商的远程控制响应。如果收到BTA_AV_VENDOR_CMD_EVT，则必须调用此函数。仅当使用BTA_AV_FEAT_VENDOR功能启用AV时，才能使用此功能。
**
** 返回void
**
*******************************************************************************/
void BTA_AvVendorRsp(UINT8 rc_handle, UINT8 label, tBTA_AV_CODE rsp_code,
                     UINT8 *p_data, UINT16 len, UINT32 company_id);


/*******************************************************************************
** 函数BTA_AvOpenRc
**
** 说明使用指定手柄打开设备的AVRCP连接
**
** 返回void
**
*******************************************************************************/
void BTA_AvOpenRc(tBTA_AV_HNDL handle);

/*******************************************************************************
** 函数BTA_AvCloseRc
**
** 说明关闭AVRCP连接
**
** 返回void
**
*******************************************************************************/
void BTA_AvCloseRc(UINT8 rc_handle);

/*******************************************************************************
** 函数BTA_AvMetaRsp
**
** 说明发送元数据命令/响应。p_pkt中包含的消息可以由AVRC实用程序函数组成。此功能仅在使用功能BTA_AV_FEAT_METADATA启用AV时使用。
**
** 返回void
**
*******************************************************************************/
void BTA_AvMetaRsp(UINT8 rc_handle, UINT8 label, tBTA_AV_CODE rsp_code,
                   BT_HDR *p_pkt);

/*******************************************************************************
** 函数BTA_AvMetaCmd
**
** 说明发送元数据/高级控制命令。p_pkt中包含的消息可以由AVRC实用程序函数组成。此功能仅在使用功能BTA_AV_FEAT_METADATA启用AV时使用。仅当对等方支持TG角色时才发送此消息。8现在唯一有意义的命令是绝对音量命令。
**
** 返回void
**
*******************************************************************************/
void BTA_AvMetaCmd(UINT8 rc_handle, UINT8 label, tBTA_AV_CMD cmd_code, BT_HDR *p_pkt);

#ifdef __cplusplus
}
#endif

#endif  ///BTA_AV_INCLUDED == TRUE

#endif /* BTA_AV_API_H */

