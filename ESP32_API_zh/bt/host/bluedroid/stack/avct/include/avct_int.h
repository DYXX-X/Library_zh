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
 * 此文件包含AVCTP内部的接口。
 *
 ******************************************************************************/
#ifndef AVCT_INT_H
#define AVCT_INT_H

#include "stack/avct_api.h"
#include "avct_defs.h"
#include "stack/l2c_api.h"
#include "osi/fixed_queue.h"

/*****************************************************************************
** 常量
*****************************************************************************/

/* lcb状态机事件*/
enum {
    AVCT_LCB_UL_BIND_EVT,
    AVCT_LCB_UL_UNBIND_EVT,
    AVCT_LCB_UL_MSG_EVT,
    AVCT_LCB_INT_CLOSE_EVT,
    AVCT_LCB_LL_OPEN_EVT,
    AVCT_LCB_LL_CLOSE_EVT,
    AVCT_LCB_LL_MSG_EVT,
    AVCT_LCB_LL_CONG_EVT
};


/* 用于L2CAP信道的“状态”*/
#define AVCT_CH_IDLE    0       /* 无连接*/
#define AVCT_CH_CONN    1       /* 正在等待连接确认*/
#define AVCT_CH_CFG     2       /* 正在等待配置完成*/
#define AVCT_CH_OPEN    3       /* 通道已打开*/

/* ccb解除锁定使用的“无事件”指示器*/
#define AVCT_NO_EVT     0xFF

/*****************************************************************************
** 数据类型
*****************************************************************************/
/* 子控制块类型—tAVCT_LCB和tAVCT_BCB的公共数据成员*/
typedef struct {
    UINT16              peer_mtu;       /* 对等l2c mtu*/
    UINT16              ch_result;      /* L2CAP连接结果值*/
    UINT16              ch_lcid;        /* L2CAP通道LCID*/
    UINT8               allocated;      /* 0，未分配。否则为索引+1。*/
    UINT8               state;          /* 状态机状态*/
    UINT8               ch_state;       /* L2CAP通道状态*/
    UINT8               ch_flags;       /* L2CAP配置标志*/
} tAVCT_SCB;

/* 链路控制块类型*/
typedef struct {
    UINT16              peer_mtu;       /* 对等l2c mtu*/
    UINT16              ch_result;      /* L2CAP连接结果值*/
    UINT16              ch_lcid;        /* L2CAP通道LCID*/
    UINT8               allocated;      /* 0，未分配。否则为索引+1。*/
    UINT8               state;          /* 状态机状态*/
    UINT8               ch_state;       /* L2CAP通道状态*/
    UINT8               ch_flags;       /* L2CAP配置标志*/
    BT_HDR              *p_rx_msg;      /* 正在重新组装消息*/
    UINT16              conflict_lcid;  /* L2CAP通道LCID*/
    BD_ADDR             peer_addr;      /* 对等方的BD地址*/
    fixed_queue_t       *tx_q;           /* 传输数据缓冲区队列*/
    BOOLEAN             cong;           /* TRUE，如果拥堵*/
} tAVCT_LCB;

/* 浏览控制块类型*/
typedef struct {
    UINT16              peer_mtu;       /* 对等l2c mtu*/
    UINT16              ch_result;      /* L2CAP连接结果值*/
    UINT16              ch_lcid;        /* L2CAP通道LCID*/
    UINT8               allocated;      /* 0，未分配。否则为索引+1。*/
    UINT8               state;          /* 状态机状态*/
    UINT8               ch_state;       /* L2CAP通道状态*/
    UINT8               ch_flags;       /* L2CAP配置标志*/
    BT_HDR              *p_tx_msg;      /* 要发送的消息-如果调用MsgReg时浏览频道未打开*/
    UINT8               ch_close;       /* CCB索引+1，如果CCB启动通道关闭*/
} tAVCT_BCB;

#define AVCT_ALOC_LCB       0x01
#define AVCT_ALOC_BCB       0x02
/* 连接控制块*/
typedef struct {
    tAVCT_CC            cc;                 /* 连接创建中的参数*/
    tAVCT_LCB           *p_lcb;             /* 相关LCB*/
    tAVCT_BCB           *p_bcb;             /* 相关BCB*/
    BOOLEAN             ch_close;           /* CCB是否启动通道关闭*/
    UINT8               allocated;          /* 是否分配LCB/BCB*/
} tAVCT_CCB;

/* 与UL_MSG_EVT关联的数据类型*/
typedef struct {
    BT_HDR                  *p_buf;
    tAVCT_CCB               *p_ccb;
    UINT8                   label;
    UINT8                   cr;
} tAVCT_UL_MSG;

/* 与lcb状态机事件关联的联合*/
typedef union {
    tAVCT_UL_MSG            ul_msg;
    BT_HDR                  *p_buf;
    tAVCT_CCB               *p_ccb;
    UINT16                  result;
    BOOLEAN                 cong;
    UINT8                   err_code;
} tAVCT_LCB_EVT;

/* AVCT控制块*/
typedef struct {
    tAVCT_LCB       lcb[AVCT_NUM_LINKS];    /* 链路控制块*/
    tAVCT_BCB       bcb[AVCT_NUM_LINKS];    /* 浏览控制块*/
    tAVCT_CCB       ccb[AVCT_NUM_CONN];     /* 连接控制块*/
    UINT16          mtu;                    /* 我们的L2CAP MTU*/
    UINT16          mtu_br;                 /* 浏览频道的L2CAP MTU*/
    UINT8           trace_level;            /* 跟踪级别*/
} tAVCT_CB;

/*****************************************************************************
** 函数声明
*****************************************************************************/

/* LCB函数声明*/
extern void avct_lcb_event(tAVCT_LCB *p_lcb, UINT8 event, tAVCT_LCB_EVT *p_data);
#if (AVCT_BROWSE_INCLUDED == TRUE)
extern void avct_bcb_event(tAVCT_BCB *p_bcb, UINT8 event, tAVCT_LCB_EVT *p_data);
extern void avct_close_bcb(tAVCT_LCB *p_lcb, tAVCT_LCB_EVT *p_data);
extern tAVCT_LCB *avct_lcb_by_bcb(tAVCT_BCB *p_bcb);
extern tAVCT_BCB *avct_bcb_by_lcb(tAVCT_LCB *p_lcb);
extern BOOLEAN avct_bcb_last_ccb(tAVCT_BCB *p_bcb, tAVCT_CCB *p_ccb_last);
extern tAVCT_BCB *avct_bcb_by_lcid(UINT16 lcid);
#endif
extern tAVCT_LCB *avct_lcb_by_bd(BD_ADDR bd_addr);
extern tAVCT_LCB *avct_lcb_alloc(BD_ADDR bd_addr);
extern void avct_lcb_dealloc(tAVCT_LCB *p_lcb, tAVCT_LCB_EVT *p_data);
extern tAVCT_LCB *avct_lcb_by_lcid(UINT16 lcid);
extern tAVCT_CCB *avct_lcb_has_pid(tAVCT_LCB *p_lcb, UINT16 pid);
extern BOOLEAN avct_lcb_last_ccb(tAVCT_LCB *p_lcb, tAVCT_CCB *p_ccb_last);

/* LCB动作功能*/
extern void avct_lcb_chnl_open(tAVCT_LCB *p_lcb, tAVCT_LCB_EVT *p_data);
extern void avct_lcb_unbind_disc(tAVCT_LCB *p_lcb, tAVCT_LCB_EVT *p_data);
extern void avct_lcb_open_ind(tAVCT_LCB *p_lcb, tAVCT_LCB_EVT *p_data);
extern void avct_lcb_open_fail(tAVCT_LCB *p_lcb, tAVCT_LCB_EVT *p_data);
extern void avct_lcb_close_ind(tAVCT_LCB *p_lcb, tAVCT_LCB_EVT *p_data);
extern void avct_lcb_close_cfm(tAVCT_LCB *p_lcb, tAVCT_LCB_EVT *p_data);
extern void avct_lcb_bind_conn(tAVCT_LCB *p_lcb, tAVCT_LCB_EVT *p_data);
extern void avct_lcb_chk_disc(tAVCT_LCB *p_lcb, tAVCT_LCB_EVT *p_data);
extern void avct_lcb_chnl_disc(tAVCT_LCB *p_lcb, tAVCT_LCB_EVT *p_data);
extern void avct_lcb_bind_fail(tAVCT_LCB *p_lcb, tAVCT_LCB_EVT *p_data);
extern void avct_lcb_cong_ind(tAVCT_LCB *p_lcb, tAVCT_LCB_EVT *p_data);
extern void avct_lcb_discard_msg(tAVCT_LCB *p_lcb, tAVCT_LCB_EVT *p_data);
extern void avct_lcb_send_msg(tAVCT_LCB *p_lcb, tAVCT_LCB_EVT *p_data);
extern void avct_lcb_msg_ind(tAVCT_LCB *p_lcb, tAVCT_LCB_EVT *p_data);
extern void avct_lcb_free_msg_ind(tAVCT_LCB *p_lcb, tAVCT_LCB_EVT *p_data);

/* BCB动作功能*/
#if (AVCT_BROWSE_INCLUDED == TRUE)
typedef void (*tAVCT_BCB_ACTION)(tAVCT_BCB *p_bcb, tAVCT_LCB_EVT *p_data);
extern void avct_bcb_chnl_open(tAVCT_BCB *p_bcb, tAVCT_LCB_EVT *p_data);
extern void avct_bcb_unbind_disc(tAVCT_BCB *p_bcb, tAVCT_LCB_EVT *p_data);
extern void avct_bcb_open_ind(tAVCT_BCB *p_bcb, tAVCT_LCB_EVT *p_data);
extern void avct_bcb_open_fail(tAVCT_BCB *p_bcb, tAVCT_LCB_EVT *p_data);
extern void avct_bcb_close_ind(tAVCT_BCB *p_bcb, tAVCT_LCB_EVT *p_data);
extern void avct_bcb_close_cfm(tAVCT_BCB *p_bcb, tAVCT_LCB_EVT *p_data);
extern void avct_bcb_bind_conn(tAVCT_BCB *p_bcb, tAVCT_LCB_EVT *p_data);
extern void avct_bcb_chk_disc(tAVCT_BCB *p_bcb, tAVCT_LCB_EVT *p_data);
extern void avct_bcb_chnl_disc(tAVCT_BCB *p_bcb, tAVCT_LCB_EVT *p_data);
extern void avct_bcb_bind_fail(tAVCT_BCB *p_bcb, tAVCT_LCB_EVT *p_data);
extern void avct_bcb_cong_ind(tAVCT_BCB *p_bcb, tAVCT_LCB_EVT *p_data);
extern void avct_bcb_discard_msg(tAVCT_BCB *p_bcb, tAVCT_LCB_EVT *p_data);
extern void avct_bcb_send_msg(tAVCT_BCB *p_bcb, tAVCT_LCB_EVT *p_data);
extern void avct_bcb_msg_ind(tAVCT_BCB *p_bcb, tAVCT_LCB_EVT *p_data);
extern void avct_bcb_free_msg_ind(tAVCT_BCB *p_bcb, tAVCT_LCB_EVT *p_data);

extern void avct_bcb_dealloc(tAVCT_BCB *p_bcb, tAVCT_LCB_EVT *p_data);

extern const tAVCT_BCB_ACTION avct_bcb_action[];
extern const UINT8 avct_lcb_pkt_type_len[];
extern const tL2CAP_FCR_OPTS avct_l2c_br_fcr_opts_def;
#endif

/* CCB函数声明*/
extern tAVCT_CCB *avct_ccb_alloc(tAVCT_CC *p_cc);
extern void avct_ccb_dealloc(tAVCT_CCB *p_ccb, UINT8 event, UINT16 result, BD_ADDR bd_addr);
extern UINT8 avct_ccb_to_idx(tAVCT_CCB *p_ccb);
extern tAVCT_CCB *avct_ccb_by_idx(UINT8 idx);


/*****************************************************************************
** 全局数据
*****************************************************************************/
#ifdef __cplusplus
extern "C"
{
#endif

/* 主控制块*/
#if AVCT_DYNAMIC_MEMORY == FALSE
extern tAVCT_CB avct_cb;
#else
extern tAVCT_CB *avct_cb_ptr;
#define avct_cb (*avct_cb_ptr)
#endif

/* L2CAP回调注册结构*/
extern const tL2CAP_APPL_INFO avct_l2c_appl;
#if (AVCT_BROWSE_INCLUDED == TRUE)
extern const tL2CAP_APPL_INFO avct_l2c_br_appl;
#endif

#ifdef __cplusplus
}
#endif

#endif /* AVCT_INT_H */

