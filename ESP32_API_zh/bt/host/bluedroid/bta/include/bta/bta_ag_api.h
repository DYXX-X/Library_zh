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
 * 这是BTA音频网关（AG）子系统的公共接口文件，BTA是Broadcom的移动电话蓝牙应用层。
 *
 ******************************************************************************/
#ifndef BTA_AG_API_H
#define BTA_AG_API_H

#include "bta_api.h"
#include "bta_hfp_defs.h"
#include "esp_hf_defs.h"

#if (BTA_AG_INCLUDED == TRUE)
/*****************************************************************************
**  常量和数据类型
*****************************************************************************/

/* AG功能掩码*/
#define BTA_AG_FEAT_3WAY    0x00000001   /* 三向呼叫*/
#define BTA_AG_FEAT_ECNR    0x00000002   /* 回声消除和/或降噪*/
#define BTA_AG_FEAT_VREC    0x00000004   /* 语音识别*/
#define BTA_AG_FEAT_INBAND  0x00000008   /* 带内铃声*/
#define BTA_AG_FEAT_VTAG    0x00000010   /* 将电话号码附加到声控标签*/
#define BTA_AG_FEAT_REJECT  0x00000020   /* 拒绝来电的能力*/
#define BTA_AG_FEAT_ECS     0x00000040   /* 增强的呼叫状态*/
#define BTA_AG_FEAT_ECC     0x00000080   /* 增强的呼叫控制*/
#define BTA_AG_FEAT_EXTERR  0x00000100   /* 扩展错误代码*/
#define BTA_AG_FEAT_CODEC   0x00000200   /* 编解码器协商*/
#define BTA_AG_FEAT_VOIP    0x00000400   /* VoIP通话*/
/* 专有功能：使用31~16位*/
#define BTA_AG_FEAT_BTRH    0x00010000   /* CCAP来电保持*/
#define BTA_AG_FEAT_UNAT    0x00020000   /* 将未知AT命令传递给应用程序*/
#define BTA_AG_FEAT_NOSCO   0x00040000   /* BTA AG未执行SCO控制*/
#define BTA_AG_FEAT_NO_ESCO 0x00080000   /* 不允许或使用eSCO*/
typedef UINT32 tBTA_AG_FEAT;

/* HFP对等功能*/
#define BTA_AG_PEER_FEAT_ECNR       0x0001  /* 回声消除和/或降噪*/
#define BTA_AG_PEER_FEAT_3WAY       0x0002  /* 呼叫等待和三方呼叫*/
#define BTA_AG_PEER_FEAT_CLI        0x0004  /* 来电显示功能*/
#define BTA_AG_PEER_FEAT_VREC       0x0008  /* 语音识别激活*/
#define BTA_AG_PEER_FEAT_VOL        0x0010  /* 远程音量控制*/
#define BTA_AG_PEER_FEAT_ECS        0x0020  /* 增强的呼叫状态*/
#define BTA_AG_PEER_FEAT_ECC        0x0040  /* 增强的呼叫控制*/
#define BTA_AG_PEER_FEAT_CODEC      0x0080  /* 编解码器协商*/
#define BTA_AG_PEER_FEAT_VOIP       0x0100  /* VoIP通话*/
typedef UINT16 tBTA_AG_PEER_FEAT;

/* AG扩展呼叫处理-掩码与任何规范无关*/
#define BTA_AG_CLIENT_CHLD_REL          0x00000001  /* 0释放等待呼叫或保留呼叫*/
#define BTA_AG_CLIENT_CHLD_REL_ACC      0x00000002  /* 1释放激活的呼叫并接受其他（等待或保持的）呼叫*/
#define BTA_AG_CLIENT_CHLD_REL_X        0x00000004  /* 1x释放x呼叫*/
#define BTA_AG_CLIENT_CHLD_HOLD_ACC     0x00000008  /* 2个当前通话保持并接受其他通话*/
#define BTA_AG_CLIENT_CHLD_PRIV_X       0x00000010  /* 2x活动多方通话保持，通话x除外*/
#define BTA_AG_CLIENT_CHLD_MERGE        0x00000020  /* 3将保留呼叫添加到多方*/
#define BTA_AG_CLIENT_CHLD_MERGE_DETACH 0x00000040  /* 4将保留呼叫添加到多方*/
typedef UINT16 tBTA_AG_CHLD_FEAT;

/* HFP对等支持的编解码器掩码*/
// TODO（谷歌）这应该使用通用定义
// 在hci/include/hci_audio.h中
#define BTA_AG_CODEC_NONE           BTM_SCO_CODEC_NONE
#define BTA_AG_CODEC_CVSD           BTM_SCO_CODEC_CVSD      /* CVSD */
#define BTA_AG_CODEC_MSBC           BTM_SCO_CODEC_MSBC      /* 毫秒BC*/
typedef UINT16 tBTA_AG_PEER_CODEC;

/* AG解析模式*/
#define BTA_AG_PARSE            0 /* 在AG中执行AT命令解析*/
#define BTA_AG_PASS_THROUGH     1 /* 将数据直接传递给手机AT命令解释器*/
typedef UINT8 tBTA_AG_PARSE_MODE;

/* AG打开状态*/
#define BTA_AG_SUCCESS          0 /* 连接已成功打开*/
#define BTA_AG_FAIL_SDP         1 /* 由于SDP，打开失败*/
#define BTA_AG_FAIL_RFCOMM      2 /* 由于RFCOMM，打开失败*/
#define BTA_AG_FAIL_RESOURCES   3 /* 资源不足故障*/
typedef UINT8 tBTA_AG_STATUS;

/* 与BTA_AgResult一起使用的句柄值*/
#define BTA_AG_HANDLE_NONE      0
#define BTA_AG_HANDLE_ALL       0xFFFF
/* 使用与BTA_AG_HANDLE_ALL HANDLE_ALL相同的值是安全的，该值用于传递指示SCO_NO_CHANGE用于更改SCO行为它们不会相互干扰
 */
#define BTA_AG_HANDLE_SCO_NO_CHANGE 0xFFFF

/* 与BTA_AgResult一起使用的AG结果代码*/
#define BTA_AG_SPK_RES              0   /* 更新扬声器音量*/
#define BTA_AG_MIC_RES              1   /* 更新麦克风音量*/
#define BTA_AG_INBAND_RING_RES      2   /* 更新带内环状态AT+BSIR*/
#define BTA_AG_CIND_RES             3   /* 发送AT+CIND的指示器响应*/
#define BTA_AG_BINP_RES             4   /* 发送AT+BINP语音标签的电话号码*/
#define BTA_AG_IND_RES              5   /* 更新指示器值+CIEV<…>*/
#define BTA_AG_BVRA_RES             6   /* 更新AT+BVRA的语音识别状态*/
#define BTA_AG_CNUM_RES             7   /* 发送AT+CNUM的订户号码响应*/
#define BTA_AG_BTRH_RES             8   /* 发送CCAP来电保持*/
#define BTA_AG_CLCC_RES             9   /* 查询AT+CLCC呼叫列表*/
#define BTA_AG_COPS_RES             10  /* 读取AT+COPS的网络运营商*/
#define BTA_AG_IN_CALL_RES          11  /* 指示来电*/
#define BTA_AG_IN_CALL_CONN_RES     12  /* 已连接来电*/
#define BTA_AG_CALL_WAIT_RES        13  /* AT+CCWA的呼叫等待通知*/
#define BTA_AG_OUT_CALL_ORIG_RES    14  /* AT+ATD呼出电话*/
#define BTA_AG_OUT_CALL_ALERT_RES   15  /* 呼出电话提醒远程方*/
#define BTA_AG_OUT_CALL_CONN_RES    16  /* 已连接呼出电话*/
#define BTA_AG_CALL_CANCEL_RES      17  /* 连接前取消了输入/输出三通*/
#define BTA_AG_END_CALL_RES         18  /* 结束呼叫AT+CHUP*/
#define BTA_AG_IN_CALL_HELD_RES     19  /* 保持AT+CHLD的来电*/
#define BTA_AG_UNAT_RES             20  /* 对未知AT命令事件AT+UNAT的响应*/
#define BTA_AG_MULTI_CALL_RES       21  /* 三路呼叫时的SLC*/
typedef UINT8 tBTA_AG_RES;

/* AG回调事件*/
#define BTA_AG_ENABLE_EVT       0  /* AG已启用*/
#define BTA_AG_REGISTER_EVT     1  /* AG注册*/
#define BTA_AG_OPEN_EVT         2  /* AG连接打开*/
#define BTA_AG_CLOSE_EVT        3  /* AG连接关闭*/
#define BTA_AG_CONN_EVT         4  /* 服务级别连接已打开*/
#define BTA_AG_AUDIO_OPEN_EVT   5  /* 音频连接打开*/
#define BTA_AG_AUDIO_CLOSE_EVT  6  /* 音频连接已关闭*/
#define BTA_AG_SPK_EVT          7  /* 扬声器音量已更改*/
#define BTA_AG_MIC_EVT          8  /* 麦克风音量已更改*/
#define BTA_AG_AT_CKPD_EVT      9  /* 来自HS的CKPD*/
#define BTA_AG_DISABLE_EVT      30 /* AG已禁用*/
#if (BTM_WBS_INCLUDED == TRUE )
#define BTA_AG_WBS_EVT          31 /* SCO编解码器nego*/
#endif
#define BTA_AG_AUDIO_MSBC_OPEN_EVT 32 /* 打开mSBC编解码器的音频连接*/

/* 以下值仅适用于HFP*/
#define BTA_AG_AT_A_EVT         10 /* 接听来电*/
#define BTA_AG_AT_D_EVT         11 /* 使用号码或记忆拨号拨打电话*/
#define BTA_AG_AT_CHLD_EVT      12 /* 呼叫保持*/
#define BTA_AG_AT_CHUP_EVT      13 /* 挂断电话*/
#define BTA_AG_AT_CIND_EVT      14 /* 读取指示器设置*/
#define BTA_AG_AT_VTS_EVT       15 /* 发送DTMF音调*/
#define BTA_AG_AT_BINP_EVT      16 /* 从声控标签中检索号码*/
#define BTA_AG_AT_BLDN_EVT      17 /* 拨打最后拨打的号码*/
#define BTA_AG_AT_BVRA_EVT      18 /* 启用/禁用语音识别*/
#define BTA_AG_AT_NREC_EVT      19 /* 禁用回声消除*/
#define BTA_AG_AT_CNUM_EVT      20 /* 检索用户号码*/
#define BTA_AG_AT_BTRH_EVT      21 /* CCAP型来电保持*/
#define BTA_AG_AT_CLCC_EVT      22 /* 查询当前通话列表*/
#define BTA_AG_AT_COPS_EVT      23 /* 查询AG上的当前操作员姓名*/
#define BTA_AG_AT_UNAT_EVT      24 /* 未知AT命令*/
#define BTA_AG_AT_CBC_EVT       25 /* 指标更新*/
#define BTA_AG_AT_BAC_EVT       26 /* 可用编解码器*/
#define BTA_AG_AT_BCS_EVT       27 /* 编解码器选择*/
typedef UINT8 tBTA_AG_EVT;

/* HFP错误代码-在“OK_flag”中返回BTA_AG_OK_ERROR时设置*/
#define BTA_AG_ERR_PHONE_FAILURE    0       /* 电话故障*/
#define BTA_AG_ERR_NO_CONN_PHONE    1       /* 无法连接到电话*/
#define BTA_AG_ERR_OP_NOT_ALLOWED   3       /* 不允许操作*/
#define BTA_AG_ERR_OP_NOT_SUPPORTED 4       /* 不支持操作*/
#define BTA_AG_ERR_PHSIM_PIN_REQ    5       /* 需要PH-SIM PIN*/
#define BTA_AG_ERR_SIM_NOT_INSERTED 10      /* SIM卡未插入*/
#define BTA_AG_ERR_SIM_PIN_REQ      11      /* 需要SIM卡PIN*/
#define BTA_AG_ERR_SIM_PUK_REQ      12      /* 需要SIM PUK*/
#define BTA_AG_ERR_SIM_FAILURE      13      /* SIM卡故障*/
#define BTA_AG_ERR_SIM_BUSY         14      /* SIM卡忙*/
#define BTA_AG_ERR_INCORRECT_PWD    16      /* 密码不正确*/
#define BTA_AG_ERR_SIM_PIN2_REQ     17      /* 需要SIM卡PIN2*/
#define BTA_AG_ERR_SIM_PUK2_REQ     18      /* 需要SIM PUK2*/
#define BTA_AG_ERR_MEMORY_FULL      20      /* 内存已满*/
#define BTA_AG_ERR_INVALID_INDEX    21      /* 无效的索引*/
#define BTA_AG_ERR_MEMORY_FAILURE   23      /* 内存故障*/
#define BTA_AG_ERR_TEXT_TOO_LONG    24      /* 文本字符串太长*/
#define BTA_AG_ERR_INV_CHAR_IN_TSTR 25      /* 文本字符串中的字符无效*/
#define BTA_AG_ERR_DSTR_TOO_LONG    26      /* 拨号字符串过长*/
#define BTA_AG_ERR_INV_CHAR_IN_DSTR 27      /* 拨号字符串中的字符无效*/
#define BTA_AG_ERR_NO_NETWORK_SERV  30      /* 无网络服务*/
#define BTA_AG_ERR_NETWORK_TIME_OUT 31      /* 网络超时*/
#define BTA_AG_ERR_NO_NET_EMG_ONLY  32      /* 不允许网络-仅限紧急服务*/
#define BTA_AG_ERR_VOIP_CS_CALLS    33      /* AG无法同时创建VoIP和CS呼叫*/
#define BTA_AG_ERR_NOT_FOR_VOIP     34      /* 此呼叫类型不支持（VoIP）*/
#define BTA_AG_ERR_SIP_RESP_CODE    35      /* SIP 3位响应代码*/
typedef UINT8 tBTA_AG_ERR_TYPE;

#if 0   /* 不适用于蓝牙HFP 1.5规范*/
#define BTA_AG_ERR_PHADAP_LNK_RES   2       /* 电话适配器链接已保留*/
#define BTA_AG_ERR_PHFSIM_PIN_REQ   6       /* 需要PH-FSIM PIN*/
#define BTA_AG_ERR_PHFSIM_PUK_REQ   7       /* 需要PH-FSIM PUK*/
#define BTA_AG_ERR_SIM_WRONG        15      /* SIM卡错误*/
#define BTA_AG_ERR_NOT_FOUND        22      /* 未找到*/
#define BTA_AG_ERR_NETWORK_TIMEOUT  31      /* 网络超时*/
#define BTA_AG_ERR_NET_PIN_REQ      40      /* 需要网络个性化PIN*/
#define BTA_AG_ERR_NET_PUK_REQ      41      /* 需要网络个性化PUK*/
#define BTA_AG_ERR_SUBSET_PIN_REQ   42      /* 需要网络子集个性化PIN*/
#define BTA_AG_ERR_SUBSET_PUK_REQ   43      /* 需要网络子集个性化PUK*/
#define BTA_AG_ERR_SERVPRO_PIN_REQ  44      /* 需要服务提供商个性化PIN*/
#define BTA_AG_ERR_SERVPRO_PUK_REQ  45      /* 需要服务提供商个性化PUK*/
#define BTA_AG_ERR_CORP_PIN_REQ     46      /* 需要公司个性化PIN*/
#define BTA_AG_ERR_CORP_PUK_REQ     47      /* 需要企业个性化PUK*/
#define BTA_AG_ERR_UNKNOWN          100    /* 未知错误*/
/* GPRS相关错误*/
#define BTA_AG_ERR_ILL_MS           103    /* 非法MS（#3）*/
#define BTA_AG_ERR_ILL_ME           106    /* 非法ME（#6）*/
#define BTA_AG_ERR_GPRS_NOT_ALLOWED 107    /* 不允许GPRS服务（#7）*/
#define BTA_AG_ERR_PLMN_NOT_ALLOWED 111    /* 不允许PLMN服务（#11）*/
#define BTA_AG_ERR_LOC_NOT_ALLOWED  112    /* 不允许的位置区域（#12）*/
#define BTA_AG_ERR_ROAM_NOT_ALLOWED 113    /* 此位置区域不允许漫游（#13）*/
/* 与激活上下文失败相关的错误*/
#define BTA_AG_ERR_OPT_NOT_SUPP     132    /* 不支持服务选项（#32）*/
#define BTA_AG_ERR_OPT_NOT_SUBSCR   133    /* 请求的服务选项未订阅（#33）*/
#define BTA_AG_ERR_OPT_OUT_OF_ORDER 134    /* 服务选项暂时失效（#34）*/
#define BTA_AG_ERR_PDP_AUTH_FAILURE 149    /* PDP身份验证失败*/
/* 其他GPRS错误*/
#define BTA_AG_ERR_INV_MOBILE_CLASS 150    /* 移动类无效*/
#define BTA_AG_ERR_UNSPEC_GPRS_ERR  148    /* 未指定的GPRS错误*/
#endif  /* 未使用的错误代码*/

/* HFP结果数据“ok_flag”*/
#define BTA_AG_OK_CONTINUE          0       /* 发送响应（更多响应即将到来）*/
#define BTA_AG_OK_DONE              1       /* 发送响应，然后是OK（已完成）*/
#define BTA_AG_OK_ERROR             2       /* 错误响应*/
typedef UINT8 tBTA_AG_AT_RESULT_TYPE;

/* BTRH值*/
#define BTA_AG_BTRH_SET_HOLD        0       /* 保持来电*/
#define BTA_AG_BTRH_SET_ACC         1       /* 等待时接听来电*/
#define BTA_AG_BTRH_SET_REJ         2       /* 拒绝等待中的来电*/
#define BTA_AG_BTRH_READ            3       /* 读取当前值*/
#define BTA_AG_BTRH_NO_RESP         4       /* 不在RH州（答复如下）*/
typedef UINT8 tBTA_AG_BTRH_TYPE;

/* AT命令或结果参数的ASCII字符串*/
#ifndef BTA_AG_AT_MAX_LEN
#define BTA_AG_AT_MAX_LEN           256
#endif

/* 指示常数HFP 1.1及更高版本*/
#define BTA_AG_IND_CALL             0   /* 呼叫指示器位置*/
#define BTA_AG_IND_CALLSETUP        1   /* 呼叫设置指示器的位置*/
#define BTA_AG_IND_SERVICE          2   /* 服务指示器位置*/
/* 指示常数HFP 1.5及更高*/
#define BTA_AG_IND_SIGNAL           3   /* 信号强度指示器位置*/
#define BTA_AG_IND_ROAM             4   /* 漫游指示器位置*/
#define BTA_AG_IND_BATTCHG          5   /* 蓄电池充电指示器的位置*/
#define BTA_AG_IND_CALLHELD         6   /* 被叫指示器的位置*/
#define BTA_AG_IND_BEARER           7   /* 支座位置指示器*/
typedef UINT16 tBTA_AG_IND_TYPE;

/* 呼叫指示器值*/
#define BTA_AG_CALL_INACTIVE        0   /* 电话呼叫未激活*/
#define BTA_AG_CALL_ACTIVE          1   /* 电话呼叫激活*/
/* callsetup指示器值*/
#define BTA_AG_CALLSETUP_NONE       0   /* 当前未在呼叫设置中*/
#define BTA_AG_CALLSETUP_INCOMING   1   /* 正在进行来电处理*/
#define BTA_AG_CALLSETUP_OUTGOING   2   /* 正在设置传出呼叫*/
#define BTA_AG_CALLSETUP_ALERTING   3   /* 在呼出呼叫中提醒远程方*/
/* 服务指标值*/
#define BTA_AG_SERVICE_NONE         0   /* CS和VoIP服务均不可用*/
#define BTA_AG_SERVICE_CS           1   /* 只有CS服务可用*/
#define BTA_AG_SERVICE_VOIP         2   /* 只有VoIP服务可用*/
#define BTA_AG_SERVICE_CS_VOIP      3   /* CS和VoIP服务均可用*/
/* 调用的指示符值*/
#define BTA_AG_CALLHELD_INACTIVE    0   /* 没有挂起的呼叫*/
#define BTA_AG_CALLHELD_ACTIVE      1   /* 呼叫保持和呼叫激活*/
#define BTA_AG_CALLHELD_NOACTIVE    2   /* 呼叫保持，但没有激活的呼叫*/
/* 信号强度指示值*/
#define BTA_AG_ROAMING_INACTIVE     0   /* 电话呼叫未激活*/
#define BTA_AG_ROAMING_ACTIVE       1   /* 电话呼叫激活*/
/* 承载指示符值*/
#define BTA_AG_BEARER_WLAN          0   /* WLAN         */
#define BTA_AG_BEARER_BLUETOOTH     1   /* 蓝牙*/
#define BTA_AG_BEARER_WIRED         2   /* 有线*/
#define BTA_AG_BEARER_2G3G          3   /* 2G 3G        */
#define BTA_AG_BEARER_WIMAX         4   /* WIMAX        */
#define BTA_AG_BEARER_RES1          5   /* 保留*/
#define BTA_AG_BEARER_RES2          6   /* 保留*/
#define BTA_AG_BEARER_RES3          7   /* 保留*/

/* 与BTA_AG_IND_RES相关的数据*/
typedef struct
{
    tBTA_AG_IND_TYPE  type;
    UINT16            value;
} tBTA_AG_IND;

/* BTA_AgResult（）的数据类型*/
typedef struct
{
    char            str[BTA_AG_AT_MAX_LEN+1]; /* 用于警察，clcc，cnum。。。*/
    tBTA_AG_IND     ind;            /* 用于指示器类型*/
    UINT16          num;            /* 用于编解码器状态*/
    UINT16          audio_handle;   /* 用于音频路径*/
    UINT16          errcode;        /* 仅当“ok_flag”设置为BTA_AG_ok_ERROR时有效*/
    UINT8           ok_flag;        /* 指示响应是否完成，以及是否发生错误*/
    BOOLEAN         state;
} tBTA_AG_RES_DATA;

/* 与大多数非AT事件相关的数据*/
typedef struct
{
    UINT16              handle;
    UINT8               app_id;
    tBTA_AG_STATUS      status;
} tBTA_AG_HDR;

/* 与BTA_AG_REGISTER_EVT相关的数据*/
typedef struct
{
    tBTA_AG_HDR         hdr;
    UINT16              handle;
    tBTA_AG_STATUS      status;
} tBTA_AG_REGISTER;

/* 与BTA_AG_OPEN_EVT相关的数据*/
typedef struct
{
    tBTA_AG_HDR         hdr;
    BD_ADDR             bd_addr;
    tBTA_SERVICE_ID     service_id;
    tBTA_AG_STATUS      status;
} tBTA_AG_OPEN;

/* 与BTA_AG_CLOSE_EVT相关的数据*/
typedef struct
{
    tBTA_AG_HDR         hdr;
    BD_ADDR             bd_addr;
} tBTA_AG_CLOSE;

/* 与BTA_AG_CONN_EVT相关的数据*/
typedef struct
{
    tBTA_AG_HDR         hdr;
    tBTA_AG_PEER_FEAT   peer_feat;
    BD_ADDR             bd_addr;
    tBTA_AG_PEER_CODEC  peer_codec;
    tBTA_AG_CHLD_FEAT   chld_feat;
} tBTA_AG_CONN;

/* 与AT命令事件相关的数据*/
typedef struct
{
    tBTA_AG_HDR         hdr;
    BD_ADDR             bd_addr;
    char                str[BTA_AG_AT_MAX_LEN+1];
    UINT16              num;    /* 语音识别状态*/
    UINT8               idx;    /* CLCC和CHLD使用的呼叫号码*/
    UINT16              value;
} tBTA_AG_VAL;

/* 与BTA_AG_CLIP_EVT和BTA_AG-CCWA_EVT相关的数据*/
#define BTA_AG_NUMBER_LEN 32
typedef struct {
    char      number[BTA_AG_NUMBER_LEN + 1];
} tBTA_AG_NUMBER;

/* 与BTA_HF_CLIENT_OPERATOR_NAME_EVT相关的数据*/
#define BTA_AG_COPS_LEN 16
typedef struct {
    char      name[BTA_AG_COPS_LEN + 1];
} tBTA_AG_COPS;

/* 与BTA_AG_AT_RESULT_EVT事件相关的数据*/
typedef struct {
    tBTA_AG_AT_RESULT_TYPE      type;
    UINT16                      cme;
} tBTA_AG_AT_RESULT;

/* 与BTA_AG_CLCC_EVT事件相关的数据*/
typedef struct {
    UINT32                     idx;
    BOOLEAN                    inc;
    UINT8                      status;
    BOOLEAN                    mpty;
    BOOLEAN                    number_present;
    char                       number[BTA_AG_NUMBER_LEN + 1];
} tBTA_AG_CLCC;

/* 与BTA_AG_CNUM_EVT事件相关的数据*/
typedef struct {
    UINT16                     service;
    char                       number[BTA_AG_NUMBER_LEN + 1];
} tBTA_AG_CNUM;

/* 与AG回调关联的数据的并集*/
typedef union
{
    tBTA_AG_HDR              hdr;
    tBTA_AG_REGISTER         reg;
    tBTA_AG_OPEN             open;
    tBTA_AG_CLOSE            close;
    tBTA_AG_CONN             conn;
    tBTA_AG_IND              ind;
    tBTA_AG_VAL              val;
    //添加
    tBTA_AG_COPS             operator;
    tBTA_AG_NUMBER           number;
    tBTA_AG_AT_RESULT        result;
    tBTA_AG_CLCC             clcc;
    tBTA_AG_CNUM             cnum;
} tBTA_AG;

/* AG回调*/
typedef void (tBTA_AG_CBACK)(tBTA_AG_EVT event, tBTA_AG *p_data);

/* AG配置结构*/
typedef struct
{
    char         *cind_info;
    INT32        conn_tout;
    UINT16       sco_pkt_types;
    char         *chld_val_ecc;
    char         *chld_val;
} tBTA_AG_CFG;

#ifdef __cplusplus
extern "C"
{
#endif

/*****************************************************************************
**  外部函数声明
*****************************************************************************/

/*******************************************************************************
** 功能BTA_AgEnable
**
** 说明启用音频网关服务。启用操作完成后，将使用BTA_AG_enable_EVT调用回调函数。在调用AG API中的其他函数之前，必须先调用此函数。
**
** 如果OK，则返回BTA_SUCCESS，否则返回BTA_FAILURE。
**
*******************************************************************************/
tBTA_STATUS BTA_AgEnable(tBTA_AG_PARSE_MODE parse_mode, tBTA_AG_CBACK *p_cback);

/*******************************************************************************
** 功能BTA_AgDisable
**
** 说明禁用音频网关服务
**
** 返回void
**
*******************************************************************************/
void BTA_AgDisable(void);

/*******************************************************************************
** 函数BTA_AgRegister
**
** 说明注册音频网关服务。
**
** 返回void
**
*******************************************************************************/
void BTA_AgRegister(tBTA_SERVICE_MASK services, tBTA_SEC sec_mask,
                    tBTA_AG_FEAT features, char *p_service_names[], UINT8 app_id);

/*******************************************************************************
** 函数BTA_AgDeregister
**
** 说明取消注册音频网关服务。
**
** 返回void
**
*******************************************************************************/
void BTA_AgDeregister(UINT16 handle);

/*******************************************************************************
** 功能BTA_AgOpen
**
** 说明打开与耳机或免提设备的连接。当连接打开时，使用BTA_AG_open_EVT调用回调函数。仅打开数据连接。音频连接未打开。
**
** 返回void
**
*******************************************************************************/
void BTA_AgOpen(UINT16 handle, BD_ADDR bd_addr, tBTA_SEC sec_mask, tBTA_SERVICE_MASK services);

/*******************************************************************************
** 功能BTA_AgClose
**
** 说明关闭与耳机或免提装置的当前连接任何当前音频连接也将关闭
**
** 返回void
**
*******************************************************************************/
void BTA_AgClose(UINT16 handle);

/*******************************************************************************
** 功能BTA_AgAudioOpen
**
** 说明打开与当前连接的耳机或hnadsfree的音频连接
**
** 返回void
**
*******************************************************************************/
void BTA_AgAudioOpen(UINT16 handle);

/*******************************************************************************
** 功能BTA_AgAudioClose
**
** 说明关闭与耳机或hnadsfree的当前活动音频连接。数据连接保持打开
**
** 返回void
**
*******************************************************************************/
void BTA_AgAudioClose(UINT16 handle);

/*******************************************************************************
** 函数BTA_AgResult
**
** 说明向耳机或免提设备发送AT结果代码。此函数仅在AG解析模式设置为BTA_AG_parse时使用。
**
** 返回void
**
*******************************************************************************/
void BTA_AgResult(UINT16 handle, tBTA_AG_RES result, tBTA_AG_RES_DATA *p_data);

/*******************************************************************************
** 函数BTA_AgSetCodec
**
** 说明指定用于后续音频连接的编解码器类型。
**
**
**
** 返回void
**
*******************************************************************************/
void BTA_AgSetCodec(UINT16 handle, tBTA_AG_PEER_CODEC codec);


#if (BTM_SCO_HCI_INCLUDED == TRUE )
/*******************************************************************************
** 函数BTA_AgCiData
**
** 说明向BTA发送EVT，告知传出数据已准备就绪。
**
** 返回void
**
*******************************************************************************/
void BTA_AgCiData(UINT16 handle);
#endif /*#如果（BTM_SCO_HCI_INCLUDED==真）*/

#ifdef __cplusplus
}
#endif

#endif /* #如果（BTA_AG_INCLUDE==真）*/

#endif /* BTA_HF_API_H */

