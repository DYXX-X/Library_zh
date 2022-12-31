/******************************************************************************
 * 版权所有（C）2015 Android开源项目
 *
 *  根据Apache许可证2.0版（“许可证”）获得许可；除非符合许可证，否则不得使用此文件。您可以在以下地址获取许可证副本：
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 *  除非适用法律要求或书面同意，否则根据许可证分发的软件是按“原样”分发的，无任何明示或暗示的担保或条件。有关许可证下权限和限制的具体语言，请参阅许可证。
 *
 ******************************************************************************/

/******************************************************************************
 * 这是BTA SDP I/F的公共接口文件
 *
 ******************************************************************************/
#ifndef BTA_SDP_API_H
#define BTA_SDP_API_H

#include "bt_sdp.h"
#include "common/bt_target.h"
#include "stack/bt_types.h"
#include "bta/bta_api.h"
#include "stack/btm_api.h"

#if (SDP_INCLUDED == TRUE)
/* 状态值*/
#define BTA_SDP_SUCCESS                  0            /* 操作成功。*/
#define BTA_SDP_FAILURE                  1            /* 一般故障。*/
#define BTA_SDP_BUSY                     2            /* 暂时无法处理此请求。*/

typedef UINT8 tBTA_SDP_STATUS;

/* SDP I/F回调事件*/
/* tBTA_SDP_DM_CBACK接收的事件*/
#define BTA_SDP_ENABLE_EVT               0  /* SDP服务i/f已启用*/
#define BTA_SDP_SEARCH_EVT               1  /* SDP服务已启动*/
#define BTA_SDP_SEARCH_COMP_EVT          2  /* SDP搜索完成*/
#define BTA_SDP_CREATE_RECORD_USER_EVT   3  /* SDP搜索完成*/
#define BTA_SDP_REMOVE_RECORD_USER_EVT   4  /* SDP搜索完成*/
#define BTA_SDP_MAX_EVT                  5  /* SDP事件的最大数量*/

#define BTA_SDP_MAX_RECORDS 15

typedef UINT16 tBTA_SDP_EVT;

/* 与BTA_SDP_DISCOVERY_COMP_EVT相关的数据*/
typedef struct {
    tBTA_SDP_STATUS      status;
    BD_ADDR              remote_addr;
    tBT_UUID             uuid;
    int                  record_count;
    bluetooth_sdp_record records[BTA_SDP_MAX_RECORDS];
} tBTA_SDP_SEARCH_COMP;

typedef union {
    tBTA_SDP_STATUS              status;            /* BTA_SDP_SEARCH_EVT */
    tBTA_SDP_SEARCH_COMP         sdp_search_comp;   /* BTA_SDP_SEARCH_COMP_EVT */
} tBTA_SDP;

/* SDP DM接口回调*/
typedef void (tBTA_SDP_DM_CBACK)(tBTA_SDP_EVT event, tBTA_SDP *p_data, void *user_data);

/* MCE配置结构*/
typedef struct {
    UINT16  sdp_db_size;            /* p_sdp_db的大小*/
#if (SDP_INCLUDED == TRUE)
    tSDP_DISCOVERY_DB   *p_sdp_db;  /* 保存SDP数据库的数据缓冲区*/
#endif  ///SDP_INCLUDED == TRUE
} tBTA_SDP_CFG;

#ifdef __cplusplus
extern "C"
{
#endif
/*******************************************************************************
** 功能BTA_SdpEnable
**
** 说明启用SDP I/F服务。启用操作完成后，将使用BTA_SDP_enable_EVT调用回调函数。必须在调用MCE API中的其他函数之前调用此函数。
**
** 如果成功，则返回BTA_SDP_SUCCESS。如果内部故障，则返回BTA_SDP_FAIL。
**
*******************************************************************************/
extern tBTA_SDP_STATUS BTA_SdpEnable(tBTA_SDP_DM_CBACK *p_cback);

/*******************************************************************************
** 功能BTA_SdpDisable
**
** 说明禁用SDP搜索I/F服务。SDP配置结构的可用缓冲区。
**
** 如果成功，则返回BTA_SDP_SUCCESS。如果内部故障，则返回BTA_SDP_FAIL。
**
*******************************************************************************/
extern tBTA_SDP_STATUS BTA_SdpDisable(void);

/*******************************************************************************
** 函数BTA_SdpSearch
**
** 说明使用特定配置文件uuid开始搜索特定BD_ADDR的sdp记录。搜索操作完成后，将使用BTA_SDP_search_EVT调用回调函数。如果成功，则返回BTA_SDP_SUCCESS。如果内部故障，则返回BTA_SDP_FAIL。
**
*******************************************************************************/
extern tBTA_SDP_STATUS BTA_SdpSearch(BD_ADDR bd_addr, tSDP_UUID *uuid);

/*******************************************************************************
** 函数BTA_SdpCreateRecordByUser
**
** 说明此函数用于请求回调以创建SDP记录。将使用事件BTA_SDP_CREATE_RECORD_USER_EVT调用已注册的回调。
**
** 如果正在处理请求，则返回BTA_SDP_SUCCESS。否则为BTA_SDP_FAILURE。
**
*******************************************************************************/
extern tBTA_SDP_STATUS BTA_SdpCreateRecordByUser(void *user_data);

/*******************************************************************************
** 函数BTA_SdpRemoveRecordByUser
**
** 说明此函数用于请求回调以删除SDP记录。将使用事件BTA_SDP_REMOVE_RECORD_USER_EVT调用已注册的回调。
**
** 如果正在处理请求，则返回BTA_SDP_SUCCESS。否则为BTA_SDP_FAILURE。
**
*******************************************************************************/
extern tBTA_SDP_STATUS BTA_SdpRemoveRecordByUser(void *user_data);

#ifdef __cplusplus
}
#endif

#endif  ///SDP_INCLUDED == TRUE

#endif /* BTA_SDP_API_H */

