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
 * 这是BTA系统管理器的专用接口文件。
 *
 ******************************************************************************/
#ifndef BTA_SYS_INT_H
#define BTA_SYS_INT_H

/*****************************************************************************
**  常量和数据类型
*****************************************************************************/

/*****************************************************************************
**  状态表
*****************************************************************************/

/* SYS HW状态*/
enum {
    BTA_SYS_HW_OFF,
    BTA_SYS_HW_STARTING,
    BTA_SYS_HW_ON,
    BTA_SYS_HW_STOPPING
};
typedef UINT8 tBTA_SYS_HW_STATE;

/* 碰撞回调*/
#define MAX_COLLISION_REG   5

typedef struct {
    UINT8                   id[MAX_COLLISION_REG];
    tBTA_SYS_CONN_CBACK     *p_coll_cback[MAX_COLLISION_REG];
} tBTA_SYS_COLLISION;

/* 系统管理器控制块*/
typedef struct {
    tBTA_SYS_REG            *reg[BTA_ID_MAX];       /* 登记结构*/
    BOOLEAN                 is_reg[BTA_ID_MAX];     /* 登记结构*/
    tBTA_SYS_HW_STATE state;
    tBTA_SYS_HW_CBACK *sys_hw_cback[BTA_SYS_MAX_HW_MODULES];    /* 为每个硬件模块启用回调*/
    UINT32                  sys_hw_module_active;   /* 所有活动模块的位掩码*/
    UINT16                  sys_features;           /* sys功能的Bitmask*/

    tBTA_SYS_CONN_CBACK     *prm_cb;                 /* DM注册的角色管理回调*/
    tBTA_SYS_CONN_CBACK     *ppm_cb;                 /* DM注册的低功耗管理回调*/
    tBTA_SYS_CONN_CBACK     *p_policy_cb;            /* DM注册的链接策略更改回调*/
    tBTA_SYS_CONN_CBACK     *p_sco_cb;               /* AV注册的SCO连接更改回调*/
    tBTA_SYS_CONN_CBACK     *p_role_cb;              /* AV注册的角色更改回调*/
    tBTA_SYS_COLLISION      colli_reg;               /* 碰撞处理模块*/
#if (BTA_EIR_CANNED_UUID_LIST != TRUE)
    tBTA_SYS_EIR_CBACK      *eir_cb;                /* 向EIR中添加/删除UUID*/
#endif
#if (BTM_SSR_INCLUDED == TRUE)
    tBTA_SYS_SSR_CFG_CBACK      *p_ssr_cb;
#endif
    /* VS事件处理程序*/
    tBTA_SYS_VS_EVT_HDLR   *p_vs_evt_hdlr;

} tBTA_SYS_CB;

/*****************************************************************************
**  全局变量
*****************************************************************************/

/* 系统管理器控制块*/
#if BTA_DYNAMIC_MEMORY == FALSE
extern tBTA_SYS_CB bta_sys_cb;
#else
extern tBTA_SYS_CB *bta_sys_cb_ptr;
#define bta_sys_cb (*bta_sys_cb_ptr)
#endif

/* 用于BTA SYS HW状态机的功能*/
void bta_sys_hw_btm_cback( tBTM_DEV_STATUS status );
void bta_sys_hw_error(tBTA_SYS_HW_MSG *p_sys_hw_msg);
void bta_sys_hw_api_enable( tBTA_SYS_HW_MSG *p_sys_hw_msg );
void bta_sys_hw_api_disable(tBTA_SYS_HW_MSG *p_sys_hw_msg);
void bta_sys_hw_evt_enabled(tBTA_SYS_HW_MSG *p_sys_hw_msg);
void bta_sys_hw_evt_disabled(tBTA_SYS_HW_MSG *p_sys_hw_msg);
void bta_sys_hw_evt_stack_enabled(tBTA_SYS_HW_MSG *p_sys_hw_msg);

BOOLEAN bta_sys_sm_execute(BT_HDR *p_msg);

#endif /* BTA_SYS_INT_H */

