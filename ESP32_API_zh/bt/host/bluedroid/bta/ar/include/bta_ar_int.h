/******************************************************************************
 * 版权所有（C）2008-2012 Broadcom Corporation
 *
 *  根据Apache许可证2.0版（“许可证”）获得许可；除非符合许可证，否则不得使用此文件。您可以在以下地址获取许可证副本：
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 *  除非适用法律要求或书面同意，否则根据许可证分发的软件是按“原样”分发的，无任何明示或暗示的担保或条件。有关许可证下权限和限制的具体语言，请参阅许可证。
 *
 ******************************************************************************/

/******************************************************************************
 * 这是BTA音频/视频注册模块的专用接口文件。
 *
 ******************************************************************************/
#ifndef BTA_AR_INT_H
#define BTA_AR_INT_H

#include "bta/bta_av_api.h"

#if (BTA_AR_INCLUDED == TRUE)

#ifndef BTA_AR_DEBUG
#define BTA_AR_DEBUG    FALSE
#endif

#define BTA_AR_AV_MASK      0x01
#define BTA_AR_AVK_MASK     0x02

/* 与BTA_AR相关的数据*/
typedef struct {
    tAVDT_CTRL_CBACK *p_av_conn_cback;       /* av连接回调函数*/
    tAVDT_CTRL_CBACK *p_avk_conn_cback;      /* avk连接回调函数*/
    UINT8           avdt_registered;
    UINT8           avct_registered;
    UINT32          sdp_tg_handle;
    UINT32          sdp_ct_handle;
    UINT16          ct_categories[2];
    UINT8           tg_registered;
    tBTA_AV_HNDL    hndl;       /* 与拒绝连接的流关联的句柄。*/
} tBTA_AR_CB;

/*****************************************************************************
**  全局数据
*****************************************************************************/

/* 控制块声明*/
#if BTA_DYNAMIC_MEMORY == FALSE
extern tBTA_AR_CB bta_ar_cb;
#else
extern tBTA_AR_CB *bta_ar_cb_ptr;
#define bta_ar_cb (*bta_ar_cb_ptr)
#endif

#endif  ///BTA_AR_INCLUDED == TRUE

#endif /* BTA_AR_INT_H */

