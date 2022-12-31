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
 * 这是BTA系统管理器的公共接口文件。
 *
 ******************************************************************************/
#ifndef BTA_SYS_H
#define BTA_SYS_H

#include "common/bt_target.h"
#include "common/bt_defs.h"

/*****************************************************************************
**  常量和数据类型
*****************************************************************************/

/* 供应商特定的事件处理程序函数类型*/
typedef BOOLEAN (tBTA_SYS_VS_EVT_HDLR)(UINT16 evt, void *p);

/* 事件处理程序函数类型*/
typedef BOOLEAN (tBTA_SYS_EVT_HDLR)(BT_HDR *p_msg);

/* 禁用函数类型*/
typedef void (tBTA_SYS_DISABLE)(void);


/* 硬件模块*/
enum {
    BTA_SYS_HW_BLUETOOTH,
    BTA_SYS_HW_RT,

    BTA_SYS_MAX_HW_MODULES
};

typedef UINT16 tBTA_SYS_HW_MODULE;

#ifndef BTA_DM_NUM_JV_ID
#define BTA_DM_NUM_JV_ID    2
#endif

/* 软件子系统*/
#define BTA_ID_SYS          0            /* 系统管理员*/
/* 蓝牙部分-从0到BTA_ID_BLUETOOTH_MAX*/
#define BTA_ID_DM           1            /* 设备管理器*/
#define BTA_ID_DM_SEARCH    2            /* 设备管理器搜索*/
#define BTA_ID_DM_SEC       3            /* 设备管理器安全*/
#define BTA_ID_DG           4            /* 数据网关*/
#define BTA_ID_AG           5            /* 音频网关*/
#define BTA_ID_OPC          6            /* 对象推送客户端*/
#define BTA_ID_OPS          7            /* 对象推送服务器*/
#define BTA_ID_FTS          8            /* 文件传输服务器*/
#define BTA_ID_CT           9            /* 无绳电话终端*/
#define BTA_ID_FTC          10           /* 文件传输客户端*/
#define BTA_ID_SS           11           /* 同步服务器*/
#define BTA_ID_PR           12           /* 打印机客户端*/
#define BTA_ID_BIC          13           /* 基本图像客户端*/
#define BTA_ID_PAN          14           /* 个人区域网络*/
#define BTA_ID_BIS          15           /* 基本成像服务器*/
#define BTA_ID_ACC          16           /* 高级照相机客户端*/
#define BTA_ID_SC           17           /* SIM卡访问服务器*/
#define BTA_ID_AV           18           /* 高级音频/视频*/
#define BTA_ID_AVK          19           /* 音频/视频接收器*/
#define BTA_ID_HD           20           /* HID设备*/
#define BTA_ID_CG           21           /* 无绳网关*/
#define BTA_ID_BP           22           /* 基本打印客户端*/
#define BTA_ID_HH           23           /* 人机界面设备主机*/
#define BTA_ID_PBS          24           /* 电话簿访问服务器*/
#define BTA_ID_PBC          25           /* 电话簿访问客户端*/
#define BTA_ID_JV           26           /* Java语言*/
#define BTA_ID_HS           27           /* 头戴式耳机*/
#define BTA_ID_MSE          28           /* 消息服务器设备*/
#define BTA_ID_MCE          29           /* 消息客户端设备*/
#define BTA_ID_HL           30           /* 健康设备配置文件*/
#define BTA_ID_GATTC        31           /* GATT客户*/
#define BTA_ID_GATTS        32           /* GATT客户*/
#define BTA_ID_SDP          33           /* SDP客户端*/
#define BTA_ID_BLUETOOTH_MAX   34        /* 最后一个BT配置文件*/

/* GENERIC */
#define BTA_ID_PRM          38
#define BTA_ID_SYSTEM       39           /* 特定于平台*/
#define BTA_ID_SWRAP        40           /* 洞察脚本包装*/
#define BTA_ID_MIP          41           /* 多阶段个人轮询*/
#define BTA_ID_RT           42           /* 音频路由模块：此模块始终打开。*/


/* JV */
#define BTA_ID_JV1          44           /* JV1 */
#define BTA_ID_JV2          45           /* JV2 */

#define BTA_ID_MAX          (44 + BTA_DM_NUM_JV_ID)

typedef UINT8 tBTA_SYS_ID;


#define BTA_SYS_CONN_OPEN           0x00
#define BTA_SYS_CONN_CLOSE          0x01
#define BTA_SYS_APP_OPEN            0x02
#define BTA_SYS_APP_CLOSE           0x03
#define BTA_SYS_SCO_OPEN            0x04
#define BTA_SYS_SCO_CLOSE           0x05
#define BTA_SYS_CONN_IDLE           0x06
#define BTA_SYS_CONN_BUSY           0x07

/* 用于链接策略*/
#define BTA_SYS_PLCY_SET            0x10 /* 将链接策略设置为给定的地址*/
#define BTA_SYS_PLCY_CLR            0x11 /* 清除到给定地址的链接策略*/
#define BTA_SYS_PLCY_DEF_SET        0x12 /* 设置默认链接策略*/
#define BTA_SYS_PLCY_DEF_CLR        0x13 /* 清除默认链接策略*/
#define BTA_SYS_ROLE_CHANGE         0x14 /* 角色变更*/

typedef UINT8 tBTA_SYS_CONN_STATUS;

/* sys功能的Bitmask*/
#define BTA_SYS_FEAT_PCM2           0x0001
#define BTA_SYS_FEAT_PCM2_MASTER    0x0002

/* tBTA_PREF_活塞*/
typedef UINT8 tBTA_SYS_PREF_ROLES;

/* 角色/低功耗管理器的conn回调*/
typedef void (tBTA_SYS_CONN_CBACK)(tBTA_SYS_CONN_STATUS status, UINT8 id, UINT8 app_id, BD_ADDR peer_addr);

/* 角色/低功耗管理器的conn回调*/
typedef void (tBTA_SYS_SSR_CFG_CBACK)(UINT8 id, UINT8 app_id, UINT16 latency, UINT16 tout);

#if (BTA_EIR_CANNED_UUID_LIST != TRUE)
/* eir用于添加/删除UUID的回调*/
typedef void (tBTA_SYS_EIR_CBACK)(UINT16 uuid16, BOOLEAN adding);
#endif

/* 登记结构*/
typedef struct {
    tBTA_SYS_EVT_HDLR   *evt_hdlr;
    tBTA_SYS_DISABLE    *disable;
} tBTA_SYS_REG;

/* 向BTA SYS HW管理器发送事件的数据类型*/
typedef struct {
    BT_HDR                hdr;
    tBTA_SYS_HW_MODULE   hw_module;
} tBTA_SYS_HW_MSG;

/*****************************************************************************
**  全局数据
*****************************************************************************/

/* 跟踪级别*/
extern UINT8 appl_trace_level;

/*****************************************************************************
**  宏
*****************************************************************************/

/* 计算事件枚举的开始；id是事件的前8位*/
#define BTA_SYS_EVT_START(id)       ((id) << 8)

/*****************************************************************************
**  BTA SYS HW管理器事件
*****************************************************************************/

/* 发送到SYS HW管理器的事件-必须与bta_SYS_main中的表保持同步。c*/
enum {
    /* 设备管理器本地设备API事件*/
    BTA_SYS_API_ENABLE_EVT = BTA_SYS_EVT_START(BTA_ID_SYS),
    BTA_SYS_EVT_ENABLED_EVT,
    BTA_SYS_EVT_STACK_ENABLED_EVT,
    BTA_SYS_API_DISABLE_EVT,
    BTA_SYS_EVT_DISABLED_EVT,
    BTA_SYS_ERROR_EVT,

    BTA_SYS_MAX_EVT
};



/* SYS HW状态事件-由SYS硬件管理器返回给其他模块。*/
enum {
    BTA_SYS_HW_OFF_EVT,
    BTA_SYS_HW_ON_EVT,
    BTA_SYS_HW_STARTING_EVT,
    BTA_SYS_HW_STOPPING_EVT,
    BTA_SYS_HW_ERROR_EVT

};
typedef UINT8 tBTA_SYS_HW_EVT;

/* 硬件启用回调类型*/
typedef void (tBTA_SYS_HW_CBACK)(tBTA_SYS_HW_EVT status);

/*****************************************************************************
**  函数声明
*****************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

extern void bta_sys_init(void);
extern void bta_sys_free(void);
extern void bta_sys_event(void * param);
extern void bta_sys_set_trace_level(UINT8 level);
extern void bta_sys_register(UINT8 id, const tBTA_SYS_REG *p_reg);
extern void bta_sys_deregister(UINT8 id);
extern BOOLEAN bta_sys_is_register(UINT8 id);
extern UINT16 bta_sys_get_sys_features(void);
extern void bta_sys_sendmsg(void *p_msg);
extern void bta_sys_start_timer(TIMER_LIST_ENT *p_tle, UINT16 type, INT32 timeout_ms);
extern void bta_sys_stop_timer(TIMER_LIST_ENT *p_tle);
extern void bta_sys_free_timer(TIMER_LIST_ENT *p_tle);
extern BOOLEAN bta_sys_timer_is_active(TIMER_LIST_ENT *p_tle);
extern void bta_sys_disable(tBTA_SYS_HW_MODULE module);
extern UINT32 bta_sys_get_remaining_ticks(TIMER_LIST_ENT *p_target_tle);

extern void bta_sys_hw_register( tBTA_SYS_HW_MODULE module, tBTA_SYS_HW_CBACK *cback);
extern void bta_sys_hw_unregister( tBTA_SYS_HW_MODULE module );


extern void bta_sys_rm_register(tBTA_SYS_CONN_CBACK *p_cback);
extern void bta_sys_pm_register(tBTA_SYS_CONN_CBACK *p_cback);

extern void bta_sys_policy_register(tBTA_SYS_CONN_CBACK *p_cback);
extern void bta_sys_sco_register(tBTA_SYS_CONN_CBACK *p_cback);


extern void bta_sys_conn_open(UINT8 id, UINT8 app_id, BD_ADDR peer_addr);
extern void bta_sys_conn_close(UINT8 id, UINT8 app_id, BD_ADDR peer_addr);
extern void bta_sys_app_open(UINT8 id, UINT8 app_id, BD_ADDR peer_addr);
extern void bta_sys_app_close(UINT8 id, UINT8 app_id, BD_ADDR peer_addr);
extern void bta_sys_sco_open(UINT8 id, UINT8 app_id, BD_ADDR peer_addr);
extern void bta_sys_sco_close(UINT8 id, UINT8 app_id, BD_ADDR peer_addr);
extern void bta_sys_sco_use(UINT8 id, UINT8 app_id, BD_ADDR peer_addr);
extern void bta_sys_sco_unuse(UINT8 id, UINT8 app_id, BD_ADDR peer_addr);
extern void bta_sys_idle(UINT8 id, UINT8 app_id, BD_ADDR peer_addr);
extern void bta_sys_busy(UINT8 id, UINT8 app_id, BD_ADDR peer_addr);

#if (BTM_SSR_INCLUDED == TRUE)
extern void bta_sys_ssr_cfg_register(tBTA_SYS_SSR_CFG_CBACK *p_cback);
extern void bta_sys_chg_ssr_config (UINT8 id, UINT8 app_id, UINT16 max_latency, UINT16 min_tout);
#endif

extern void bta_sys_role_chg_register(tBTA_SYS_CONN_CBACK *p_cback);
extern void bta_sys_notify_role_chg(BD_ADDR_PTR p_bda, UINT8 new_role, UINT8 hci_status);
extern void bta_sys_collision_register(UINT8 bta_id, tBTA_SYS_CONN_CBACK *p_cback);
extern void bta_sys_notify_collision (BD_ADDR_PTR p_bda);

#if (BTA_EIR_CANNED_UUID_LIST != TRUE)
extern void bta_sys_eir_register(tBTA_SYS_EIR_CBACK *p_cback);
extern void bta_sys_add_uuid(UINT16 uuid16);
extern void bta_sys_remove_uuid(UINT16 uuid16);
#else
#define bta_sys_eir_register(ut)
#define bta_sys_add_uuid(ut)
#define bta_sys_remove_uuid(ut)
#endif

extern void bta_sys_set_policy (UINT8 id, UINT8 policy, BD_ADDR peer_addr);
extern void bta_sys_clear_policy (UINT8 id, UINT8 policy, BD_ADDR peer_addr);
extern void bta_sys_set_default_policy (UINT8 id, UINT8 policy);
extern void bta_sys_clear_default_policy (UINT8 id, UINT8 policy);
extern BOOLEAN bta_sys_vs_hdl(UINT16 evt, void *p);

#ifdef __cplusplus
}
#endif

#endif /* BTA_SYS_H */

