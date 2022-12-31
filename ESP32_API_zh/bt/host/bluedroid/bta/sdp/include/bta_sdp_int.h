

/******************************************************************************
 * 版权所有（C）2014 Android开源项目版权所有（B）2003-2012 Broadcom Corporation
 *
 *  根据Apache许可证2.0版（“许可证”）获得许可；除非符合许可证，否则不得使用此文件。您可以在以下地址获取许可证副本：
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 *  除非适用法律要求或书面同意，否则根据许可证分发的软件是按“原样”分发的，无任何明示或暗示的担保或条件。有关许可证下权限和限制的具体语言，请参阅许可证。
 *
 ******************************************************************************/

/******************************************************************************
 * 这是BTA SDP I/F的专用接口文件
 *
 ******************************************************************************/
#ifndef BTA_SDP_INT_H
#define BTA_SDP_INT_H

#include "bta/bta_sys.h"
#include "bta/bta_api.h"
#include "bta/bta_sdp_api.h"

#if (SDP_INCLUDED == TRUE)
/*****************************************************************************
**  常量
*****************************************************************************/

enum {
    /* 这些事件由状态机处理*/
    BTA_SDP_API_ENABLE_EVT = BTA_SYS_EVT_START(BTA_ID_SDP),
    BTA_SDP_API_SEARCH_EVT,
    BTA_SDP_API_CREATE_RECORD_USER_EVT,
    BTA_SDP_API_REMOVE_RECORD_USER_EVT,
    BTA_SDP_MAX_INT_EVT
};

enum {
    BTA_SDP_ACTIVE_NONE = 0,
    BTA_SDP_ACTIVE_YES       /* 等待SDP结果*/
};



/* BTA_SDP_API_ENABLE_EVT的数据类型*/
typedef struct {
    BT_HDR             hdr;
    tBTA_SDP_DM_CBACK  *p_cback;
} tBTA_SDP_API_ENABLE;

/* BTA_SDP_API_SEARCH_EVT的数据类型*/
typedef struct {
    BT_HDR          hdr;
    BD_ADDR         bd_addr;
    tSDP_UUID       uuid;
} tBTA_SDP_API_SEARCH;

/* BTA_SDP_API_SEARCH_EVT的数据类型*/
typedef struct {
    BT_HDR          hdr;
    void           *user_data;
} tBTA_SDP_API_RECORD_USER;

/* 所有数据类型的联合*/
typedef union {
    /* 事件缓冲区标头*/
    BT_HDR                                 hdr;
    tBTA_SDP_API_ENABLE                    enable;
    tBTA_SDP_API_SEARCH                    get_search;
    tBTA_SDP_API_RECORD_USER               record;
} tBTA_SDP_MSG;

/* SDP控制块*/
typedef struct {
    UINT8              sdp_active;  /* 参见BTA_SDP_SDP_ACT_**/
    BD_ADDR            remote_addr;
    tBTA_SDP_DM_CBACK  *p_dm_cback;
} tBTA_SDP_CB;


/* SDP控制块*/
#if BTA_DYNAMIC_MEMORY == FALSE
extern tBTA_SDP_CB bta_sdp_cb;
#else
extern tBTA_SDP_CB *bta_sdp_cb_ptr;
#define bta_sdp_cb (*bta_sdp_cb_ptr)
#endif

/* 配置结构*/
extern tBTA_SDP_CFG *p_bta_sdp_cfg;

extern BOOLEAN bta_sdp_sm_execute(BT_HDR *p_msg);

extern void bta_sdp_enable (tBTA_SDP_MSG *p_data);
extern void bta_sdp_search (tBTA_SDP_MSG *p_data);
extern void bta_sdp_create_record(tBTA_SDP_MSG *p_data);
extern void bta_sdp_remove_record(tBTA_SDP_MSG *p_data);

#endif  ///SDP_INCLUDED == TRUE

#endif /* BTA_SDP_INT_H */

