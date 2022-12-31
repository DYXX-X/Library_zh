/******************************************************************************
 * 版权所有（c）2014 Android开源项目版权所有（c）2003-2012 Broadcom Corporation
 *
 *  根据Apache许可证2.0版（“许可证”）获得许可；除非符合许可证，否则不得使用此文件。您可以在以下地址获取许可证副本：
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 *  除非适用法律要求或书面同意，否则根据许可证分发的软件是按“原样”分发的，无任何明示或暗示的担保或条件。有关许可证下权限和限制的具体语言，请参阅许可证。
 *
 ******************************************************************************/

/******************************************************************************
 * 这是免提（HF角色）子系统的公共接口文件
 *
 ******************************************************************************/
#ifndef BTA_HF_CLIENT_API_H
#define BTA_HF_CLIENT_API_H

#include "bta_api.h"
#include "bta_hfp_defs.h"

#if (BTA_HF_INCLUDED == TRUE)
/*****************************************************************************
**  常量和数据类型
*****************************************************************************/

/* 免提单元（HF）版本*/
#define HFP_HF_VERSION_1_6             0x0106       /* 第1.6版*/
#define HFP_HF_VERSION_1_7             0x0107       /* 第1.7版*/

/* HFP对等（AG）功能*/
#define BTA_HF_CLIENT_PEER_FEAT_3WAY   0x00000001  /* 三向呼叫*/
#define BTA_HF_CLIENT_PEER_FEAT_ECNR   0x00000002  /* 回声消除和/或降噪*/
#define BTA_HF_CLIENT_PEER_FEAT_VREC   0x00000004  /* 语音识别*/
#define BTA_HF_CLIENT_PEER_INBAND      0x00000008  /* 带内铃声*/
#define BTA_HF_CLIENT_PEER_VTAG        0x00000010  /* 将电话号码附加到声控标签*/
#define BTA_HF_CLIENT_PEER_REJECT      0x00000020  /* 拒绝来电的能力*/
#define BTA_HF_CLIENT_PEER_ECS         0x00000040  /* 增强的呼叫状态*/
#define BTA_HF_CLIENT_PEER_ECC         0x00000080  /* 增强的呼叫控制*/
#define BTA_HF_CLIENT_PEER_EXTERR      0x00000100  /* 扩展错误代码*/
#define BTA_HF_CLIENT_PEER_CODEC       0x00000200  /* 编解码器协商*/
/* HFP 1.7+ */
#define BTA_HF_CLIENT_PEER_HF_IND      0x00000400  /* 高频指示器*/
#define BTA_HF_CLIENT_PEER_ESCO_S4     0x00000800  /* 支持eSCO S4设置*/

typedef UINT16 tBTA_HF_CLIENT_PEER_FEAT;

/* HFP HF功能*/
#define BTA_HF_CLIENT_FEAT_ECNR        0x00000001  /* 回声消除和/或降噪*/
#define BTA_HF_CLIENT_FEAT_3WAY        0x00000002  /* 呼叫等待和三方呼叫*/
#define BTA_HF_CLIENT_FEAT_CLI         0x00000004  /* 来电显示功能*/
#define BTA_HF_CLIENT_FEAT_VREC        0x00000008  /* 语音识别激活*/
#define BTA_HF_CLIENT_FEAT_VOL         0x00000010  /* 远程音量控制*/
#define BTA_HF_CLIENT_FEAT_ECS         0x00000020  /* 增强的呼叫状态*/
#define BTA_HF_CLIENT_FEAT_ECC         0x00000040  /* 增强的呼叫控制*/
#define BTA_HF_CLIENT_FEAT_CODEC       0x00000080  /* 编解码器协商*/
#define BTA_HF_CLIENT_FEAT_HF_IND      0x00000100  /* 高频指示器*/
#define BTA_HF_CLIENT_FEAT_ESCO_S4     0x00000200  /* 支持eSCO S4设置*/

/* HFP HF扩展呼叫处理-掩码与任何规范无关*/
#define BTA_HF_CLIENT_CHLD_REL          0x00000001  /* 0释放等待呼叫或保留呼叫*/
#define BTA_HF_CLIENT_CHLD_REL_ACC      0x00000002  /* 1释放激活的呼叫并接受其他（等待或保持的）呼叫*/
#define BTA_HF_CLIENT_CHLD_REL_X        0x00000004  /* 1x释放x呼叫*/
#define BTA_HF_CLIENT_CHLD_HOLD_ACC     0x00000008  /* 2个当前通话保持并接受其他通话*/
#define BTA_HF_CLIENT_CHLD_PRIV_X       0x00000010  /* 2x活动多方通话保持，通话x除外*/
#define BTA_HF_CLIENT_CHLD_MERGE        0x00000020  /* 3将保留呼叫添加到多方*/
#define BTA_HF_CLIENT_CHLD_MERGE_DETACH 0x00000040  /* 4将保留呼叫添加到多方*/

typedef UINT16 tBTA_HF_CLIENT_CHLD_FEAT;

/* HFP AG错误未正常发送至HF装置*/
#define BTA_HF_CLIENT_AT_RESULT_OK            0
#define BTA_HF_CLIENT_AT_RESULT_ERROR         1
#define BTA_HF_CLIENT_AT_RESULT_NO_CARRIER    2
#define BTA_HF_CLIENT_AT_RESULT_BUSY          3
#define BTA_HF_CLIENT_AT_RESULT_NO_ANSWER     4
#define BTA_HF_CLIENT_AT_RESULT_DELAY         5
#define BTA_HF_CLIENT_AT_RESULT_BLACKLISTED   6
#define BTA_HF_CLIENT_AT_RESULT_CME           7

typedef UINT8 tBTA_HF_CLIENT_AT_RESULT_TYPE;

/* HF客户端回调事件*/
#define BTA_HF_CLIENT_ENABLE_EVT            0  /* HF客户端已启用*/
#define BTA_HF_CLIENT_REGISTER_EVT          1  /* HF客户端已注册*/
#define BTA_HF_CLIENT_OPEN_EVT              2  /* HF客户端连接打开*/
#define BTA_HF_CLIENT_CLOSE_EVT             3  /* HF客户端连接已关闭*/
#define BTA_HF_CLIENT_CONN_EVT              4  /* 服务级别连接已打开*/
#define BTA_HF_CLIENT_AUDIO_OPEN_EVT        5  /* 音频连接打开*/
#define BTA_HF_CLIENT_AUDIO_MSBC_OPEN_EVT   6  /* 打开mSBC编解码器的音频连接*/
#define BTA_HF_CLIENT_AUDIO_CLOSE_EVT       7  /* 音频连接已关闭*/
#define BTA_HF_CLIENT_SPK_EVT               8  /* 扬声器音量已更改*/
#define BTA_HF_CLIENT_MIC_EVT               9  /* 麦克风音量已更改*/
#define BTA_HF_CLIENT_IND_EVT               10 /* 指示信号*/
#define BTA_HF_CLIENT_VOICE_REC_EVT         11 /* AG更改了语音识别设置*/
#define BTA_HF_CLIENT_OPERATOR_NAME_EVT     12 /* 已获取操作员姓名*/
#define BTA_HF_CLIENT_CLIP_EVT              13 /* 主叫线识别事件*/
#define BTA_HF_CLIENT_CCWA_EVT              14 /* 呼叫等待通知*/
#define BTA_HF_CLIENT_AT_RESULT_EVT         15 /* 呼叫等待通知*/
#define BTA_HF_CLIENT_CLCC_EVT              16 /* 当前呼叫事件*/
#define BTA_HF_CLIENT_CNUM_EVT              17 /* 订户信息事件*/
#define BTA_HF_CLIENT_BTRH_EVT              18 /* 蓝牙响应和保持事件*/
#define BTA_HF_CLIENT_BSIR_EVT              19 /* 带内铃声设置更改事件*/
#define BTA_HF_CLIENT_BINP_EVT              20 /* binp数事件*/
#define BTA_HF_CLIENT_RING_INDICATION       21 /* HF客户端振铃指示*/
#define BTA_HF_CLIENT_DISABLE_EVT           30 /* HF客户端已禁用*/

typedef UINT8 tBTA_HF_CLIENT_EVT;

/* HF客户端打开状态*/
#define BTA_HF_CLIENT_SUCCESS          0 /* 连接已成功打开*/
#define BTA_HF_CLIENT_FAIL_SDP         1 /* 由于SDP，打开失败*/
#define BTA_HF_CLIENT_FAIL_RFCOMM      2 /* 由于RFCOMM，打开失败*/
#define BTA_HF_CLIENT_FAIL_RESOURCES   3 /* 资源不足故障*/

typedef UINT8 tBTA_HF_CLIENT_STATUS;

/* 指示常数HFP 1.1及更高版本*/
#define BTA_HF_CLIENT_IND_CALL             0   /* 呼叫指示器位置*/
#define BTA_HF_CLIENT_IND_CALLSETUP        1   /* 呼叫设置指示器的位置*/
#define BTA_HF_CLIENT_IND_SERVICE          2   /* 服务指示器位置*/
/* 指示常数HFP 1.5及更高*/
#define BTA_HF_CLIENT_IND_SIGNAL           3   /* 信号强度指示器位置*/
#define BTA_HF_CLIENT_IND_ROAM             4   /* 漫游指示器位置*/
#define BTA_HF_CLIENT_IND_BATTCH           5   /* 蓄电池充电指示器的位置*/
#define BTA_HF_CLIENT_IND_CALLHELD         6   /* 被叫指示器的位置*/
#define BTA_HF_CLIENT_IND_BEARER           7   /* 支座位置指示器*/
typedef UINT8 tBTA_HF_CLIENT_IND_TYPE;

/* AT命令*/
#define BTA_HF_CLIENT_AT_CMD_VTS    0
#define BTA_HF_CLIENT_AT_CMD_BTRH   1
#define BTA_HF_CLIENT_AT_CMD_CHUP   2
#define BTA_HF_CLIENT_AT_CMD_CHLD   3
#define BTA_HF_CLIENT_AT_CMD_BCC    4
#define BTA_HF_CLIENT_AT_CMD_CNUM   5
#define BTA_HF_CLIENT_AT_CMD_ATA    6
#define BTA_HF_CLIENT_AT_CMD_COPS   7
#define BTA_HF_CLIENT_AT_CMD_ATD    8
#define BTA_HF_CLIENT_AT_CMD_VGM    9
#define BTA_HF_CLIENT_AT_CMD_VGS    10
#define BTA_HF_CLIENT_AT_CMD_BVRA   11
#define BTA_HF_CLIENT_AT_CMD_CLCC   12
#define BTA_HF_CLIENT_AT_CMD_BINP   13
#define BTA_HF_CLIENT_AT_CMD_BLDN   14
#define BTA_HF_CLIENT_AT_CMD_NREC   15

typedef UINT8 tBTA_HF_CLIENT_AT_CMD_TYPE;

/* 与大多数非AT事件相关的数据*/
/* 占位符，如果不需要，应删除*/
typedef struct {
} tBTA_HF_CLIENT_HDR;

/* 与BTA_HF_CLIENT_REGISTER_EVT相关的数据*/
typedef struct {
    tBTA_HF_CLIENT_HDR      hdr;
    UINT16                  handle;
    tBTA_HF_CLIENT_STATUS   status;
} tBTA_HF_CLIENT_REGISTER;

/* 与BTA_HF_CLIENT_OPEN_EVT相关的数据*/
typedef struct {
    tBTA_HF_CLIENT_HDR      hdr;
    BD_ADDR                 bd_addr;
    tBTA_HF_CLIENT_STATUS   status;
} tBTA_HF_CLIENT_OPEN;

/* 与BTA_HF_CLIENT_CONN_EVT相关的数据*/
typedef struct {
    tBTA_HF_CLIENT_HDR         hdr;
    tBTA_HF_CLIENT_PEER_FEAT   peer_feat;
    tBTA_HF_CLIENT_CHLD_FEAT   chld_feat;
} tBTA_HF_CLIENT_CONN;

/* 与BTA_HF_CLIENT_IND_EVT事件相关的数据*/
typedef struct {
    tBTA_HF_CLIENT_HDR         hdr;
    tBTA_HF_CLIENT_IND_TYPE    type;
    UINT16                     value;
} tBTA_HF_CLIENT_IND;

/* 与BTA_HF_CLIENT_OPERATOR_NAME_EVT相关的数据*/
#define BTA_HF_CLIENT_OPERATOR_NAME_LEN 16
typedef struct {
    char                       name[BTA_HF_CLIENT_OPERATOR_NAME_LEN + 1];
} tBTA_HF_CLIENT_OPERATOR_NAME;

/* 与BTA_HF_CLIENT_CLIP_EVT和BTA_HF-CLIENT_CCWA_EVT相关的数据*/
#define BTA_HF_CLIENT_NUMBER_LEN 32
typedef struct {
    char                       number[BTA_HF_CLIENT_NUMBER_LEN + 1];
} tBTA_HF_CLIENT_NUMBER;

/* 与BTA_HF_CLIENT_AT_RESULT_EVT事件相关的数据*/
typedef struct {
    tBTA_HF_CLIENT_AT_RESULT_TYPE    type;
    UINT16                           cme;
} tBTA_HF_CLIENT_AT_RESULT;

/* 与BTA_HF_CLIENT_CLCC_EVT事件关联的数据*/
typedef struct {
    UINT32                     idx;
    BOOLEAN                    inc;
    UINT8                      status;
    BOOLEAN                    mpty;
    BOOLEAN                    number_present;
    char                       number[BTA_HF_CLIENT_NUMBER_LEN + 1];
} tBTA_HF_CLIENT_CLCC;

/* 与BTA_HF_CLIENT_CNUM_EVT事件相关的数据*/
typedef struct {
    UINT16                     service;
    char                       number[BTA_HF_CLIENT_NUMBER_LEN + 1];
} tBTA_HF_CLIENT_CNUM;

/* 与其他事件相关的数据*/
typedef struct {
    UINT16                     value;
} tBTA_HF_CLIENT_VAL;

/* 与AG回调关联的数据的并集*/
typedef union {
    tBTA_HF_CLIENT_HDR              hdr;
    tBTA_HF_CLIENT_REGISTER         reg;
    tBTA_HF_CLIENT_OPEN             open;
    tBTA_HF_CLIENT_CONN             conn;
    tBTA_HF_CLIENT_IND              ind;
    tBTA_HF_CLIENT_VAL              val;
    tBTA_HF_CLIENT_OPERATOR_NAME    operator;
    tBTA_HF_CLIENT_NUMBER           number;
    tBTA_HF_CLIENT_AT_RESULT        result;
    tBTA_HF_CLIENT_CLCC             clcc;
    tBTA_HF_CLIENT_CNUM             cnum;
} tBTA_HF_CLIENT;

typedef UINT32 tBTA_HF_CLIENT_FEAT;

/* HF客户端回调*/
typedef void (tBTA_HF_CLIENT_CBACK)(tBTA_HF_CLIENT_EVT event, void *p_data);

#ifdef __cplusplus
extern "C"
{
#endif

/*****************************************************************************
**  外部函数声明
*****************************************************************************/

/*******************************************************************************
** 功能BTA_HfClientEnable
**
** 说明启用HF CLient服务。启用操作完成后，将使用BTA_HF_CLIENT_enable_EVT调用回调函数。在调用HF CLient API中的其他函数之前，必须先调用此函数。
**
** 如果OK，则返回BTA_SUCCESS，否则返回BTA_FAILURE。
**
*******************************************************************************/
tBTA_STATUS BTA_HfClientEnable(tBTA_HF_CLIENT_CBACK *p_cback);

/*******************************************************************************
** 功能BTA_HfClientDisable
**
** 说明禁用HF客户端服务
**
** 返回void
**
*******************************************************************************/
void BTA_HfClientDisable(void);

/*******************************************************************************
** 函数BTA_HfClientRegister
**
** 说明注册HF客户端服务。
**
** 返回void
**
*******************************************************************************/
void BTA_HfClientRegister(tBTA_SEC sec_mask, tBTA_HF_CLIENT_FEAT features,
                          char *p_service_name);

/*******************************************************************************
** 函数BTA_HfClientDeregister
**
** 说明取消注册HF客户端服务。
**
** 返回void
**
*******************************************************************************/
void BTA_HfClientDeregister(UINT16 handle);

/*******************************************************************************
** 函数BTA_HfClientOpen
**
** 说明打开与音频网关的连接。当连接打开时，使用BTA_HF_CLIENT_open_EVT调用回调函数。仅打开数据连接。音频连接未打开。
**
** 返回void
**
*******************************************************************************/
void BTA_HfClientOpen(UINT16 handle, BD_ADDR bd_addr, tBTA_SEC sec_mask);

/*******************************************************************************
** 函数BTA_HfClientClose
**
** 说明关闭与音频网关的当前连接。任何当前音频连接也将关闭
**
** 返回void
**
*******************************************************************************/
void BTA_HfClientClose(UINT16 handle);

/*******************************************************************************
** 功能BTA_HfCllientAudioOpen
**
** 说明打开到当前连接的音频网关的音频连接
**
** 返回void
**
*******************************************************************************/
void BTA_HfClientAudioOpen(UINT16 handle);

/*******************************************************************************
** 函数BTA_HfClientAudioClose
**
** 说明关闭与音频网关的当前活动音频连接。数据连接保持打开
**
** 返回void
**
*******************************************************************************/
void BTA_HfClientAudioClose(UINT16 handle);

/*******************************************************************************
** 函数BTA_HfClientSendAT
**
** 描述发送AT命令
**
** 返回void
**
*******************************************************************************/
void BTA_HfClientSendAT(UINT16 handle, tBTA_HF_CLIENT_AT_CMD_TYPE at, UINT32 val1, UINT32 val2, const char *str);

#if (BTM_SCO_HCI_INCLUDED == TRUE )
void BTA_HfClientCiData(void);
#endif /*#如果（BTM_SCO_HCI_INCLUDED==真）*/

int BTA_HfClientGetCbDataSize(tBTA_HF_CLIENT_EVT event);

#ifdef __cplusplus
}
#endif
#endif /* #如果（BTA_HF_INCLUDE==真）*/
#endif /* BTA_HF_CLIENT_API_H */

