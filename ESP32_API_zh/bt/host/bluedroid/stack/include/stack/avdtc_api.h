/******************************************************************************
 * 版权所有（C）2002-2012 Broadcom Corporation
 *
 *  根据Apache许可证2.0版（“许可证”）获得许可；除非符合许可证，否则不得使用此文件。您可以在以下地址获取许可证副本：
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 *  除非适用法律要求或书面同意，否则根据许可证分发的软件是按“原样”分发的，无任何明示或暗示的担保或条件。有关许可证下权限和限制的具体语言，请参阅许可证。
 *
 ******************************************************************************/

/******************************************************************************
 * 此接口文件包含接口AVDTP一致性API。这些额外的API函数和回调事件仅用于一致性测试。应用程序不打算使用它们。
 *
 ******************************************************************************/
#ifndef AVDT_CAPI_H
#define AVDT_CAPI_H

#include "stack/avdt_api.h"

/* 在此处启动AVDTC事件以区别于AVDT事件*/
#define AVDTC_EVT_BEGIN             0x80

#define AVDTC_DISCOVER_IND_EVT      (0 + AVDTC_EVT_BEGIN)   /* 发现指示*/
#define AVDTC_GETCAP_IND_EVT        (1 + AVDTC_EVT_BEGIN)   /* 获取功能指示*/
#define AVDTC_SETCONFIG_CFM_EVT     (2 + AVDTC_EVT_BEGIN)   /* 设置配置确认*/
#define AVDTC_GETCONFIG_IND_EVT     (3 + AVDTC_EVT_BEGIN)   /* 获取配置指示*/
#define AVDTC_GETCONFIG_CFM_EVT     (4 + AVDTC_EVT_BEGIN)   /* 获取配置确认*/
#define AVDTC_OPEN_IND_EVT          (5 + AVDTC_EVT_BEGIN)   /* 打开指示灯*/
#define AVDTC_START_IND_EVT         (6 + AVDTC_EVT_BEGIN)   /* 启动指示*/
#define AVDTC_CLOSE_IND_EVT         (7 + AVDTC_EVT_BEGIN)   /* 关闭指示*/
#define AVDTC_SUSPEND_IND_EVT       (8 + AVDTC_EVT_BEGIN)   /* 暂停指示*/
#define AVDTC_ABORT_IND_EVT         (9 + AVDTC_EVT_BEGIN)   /* 中止指示*/
#define AVDTC_ABORT_CFM_EVT         (10 + AVDTC_EVT_BEGIN)  /* 中止确认*/

typedef struct {
    tAVDT_EVT_HDR   hdr;                        /* 事件标题*/
    UINT8           seid_list[AVDT_NUM_SEPS];   /* SEID值数组*/
    UINT8           num_seps;                   /* 数组中的值数*/
} tAVDT_MULTI;

/* 所有控件回调事件数据结构的联合*/
typedef union {
    tAVDT_EVT_HDR       hdr;
    tAVDT_CONFIG        getconfig_cfm;
    tAVDT_MULTI         start_ind;
    tAVDT_MULTI         suspend_ind;
} tAVDTC_CTRL;

typedef void tAVDTC_CTRL_CBACK(UINT8 handle, BD_ADDR bd_addr, UINT8 event, tAVDTC_CTRL *p_data);

#ifdef __cplusplus
extern "C"
{
#endif

/*******************************************************************************
** 函数AVDTC_Init
**
** 说明调用此函数以开始使用一致性API。它必须在AVDT_Register（）之后以及在调用任何其他API或一致性API函数之前调用。
**
** 返回void
**
*******************************************************************************/
extern void AVDTC_Init(tAVDTC_CTRL_CBACK *p_cback);

/*******************************************************************************
** 函数AVDTC_DiscoverRsp
**
** 说明发送发现响应。
**
** 返回void
**
*******************************************************************************/
extern void AVDTC_DiscoverRsp(BD_ADDR bd_addr, UINT8 label,
                              tAVDT_SEP_INFO sep_info[], UINT8 num_seps);

/*******************************************************************************
** 函数AVDTC_GetCapRsp
**
** 描述发送获取功能响应。
**
** 返回void
**
*******************************************************************************/
extern void AVDTC_GetCapRsp(BD_ADDR bd_addr, UINT8 label, tAVDT_CFG *p_cap);

/*******************************************************************************
** 函数AVDTC_GetAllCapRsp
**
** 描述发送获取所有功能响应。
**
** 返回void
**
*******************************************************************************/
extern void AVDTC_GetAllCapRsp(BD_ADDR bd_addr, UINT8 label, tAVDT_CFG *p_cap);

/*******************************************************************************
** 函数AVDTC_GetConfigReq
**
** 说明发送获取配置请求。
**
** 返回void
**
*******************************************************************************/
extern void AVDTC_GetConfigReq(UINT8 handle);

/*******************************************************************************
** 函数AVDTC_GetConfigRsp
**
** 说明发送获取配置响应。
**
** 返回void
**
*******************************************************************************/
extern void AVDTC_GetConfigRsp(UINT8 handle, UINT8 label, tAVDT_CFG *p_cfg);

/*******************************************************************************
** 函数AVDTC_OpenReq
**
** 说明发送打开请求。
**
** 返回void
**
*******************************************************************************/
extern void AVDTC_OpenReq(UINT8 handle);

/*******************************************************************************
** 函数AVDTC_OpenRsp
**
** 说明发送打开的响应。
**
** 返回void
**
*******************************************************************************/
extern void AVDTC_OpenRsp(UINT8 handle, UINT8 label);

/*******************************************************************************
** 函数AVDTC_StartRsp
**
** 说明发送启动响应。
**
** 返回void
**
*******************************************************************************/
extern void AVDTC_StartRsp(UINT8 *p_handles, UINT8 num_handles, UINT8 label);

/*******************************************************************************
** 函数AVDTC_CloseRsp
**
** 说明发送关闭响应。
**
** 返回void
**
*******************************************************************************/
extern void AVDTC_CloseRsp(UINT8 handle, UINT8 label);

/*******************************************************************************
** 函数AVDTC_SuspendRsp
**
** 说明发送挂起响应。
**
** 返回void
**
*******************************************************************************/
extern void AVDTC_SuspendRsp(UINT8 *p_handles, UINT8 num_handles, UINT8 label);

/*******************************************************************************
** 函数AVDTC_AbortReq
**
** 说明发送中止请求。
**
** 返回void
**
*******************************************************************************/
extern void AVDTC_AbortReq(UINT8 handle);

/*******************************************************************************
** 函数AVDTC_AbortRsp
**
** 说明发送中止响应。
**
** 返回void
**
*******************************************************************************/
extern void AVDTC_AbortRsp(UINT8 handle, UINT8 label);

/*******************************************************************************
** 函数AVDTC_Rej
**
** 说明发送拒绝消息。
**
** 返回void
**
*******************************************************************************/
extern void AVDTC_Rej(UINT8 handle, BD_ADDR bd_addr, UINT8 cmd, UINT8 label,
                      UINT8 err_code, UINT8 err_param);

#ifdef __cplusplus
}
#endif

#endif /* AVDT_CAPI_H */

