/******************************************************************************
 * 版权所有（C）2009-2013 Broadcom Corporation
 *
 *  根据Apache许可证2.0版（“许可证”）获得许可；除非符合许可证，否则不得使用此文件。您可以在以下地址获取许可证副本：
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 *  除非适用法律要求或书面同意，否则根据许可证分发的软件是按“原样”分发的，无任何明示或暗示的担保或条件。有关许可证下权限和限制的具体语言，请参阅许可证。
 *
 ******************************************************************************/


#ifndef GAP_INT_H
#define GAP_INT_H

#include "common/bt_target.h"
#include "osi/fixed_queue.h"
#include "stack/gap_api.h"
#include "stack/gatt_api.h"
#define GAP_MAX_BLOCKS 2        /* 一次挂起并发GAP命令*/
/* 定义通用访问配置文件控制结构*/
typedef struct {
    void          *p_data;      /* 指向回调中返回的任何数据的指针*/
    tGAP_CALLBACK *gap_cback;   /* 指向用户回调函数的指针*/
    tGAP_CALLBACK *gap_inq_rslt_cback; /* 用于查询结果*/
    UINT16         event;       /* 在回调中传回*/
    UINT8          index;       /* 此控制块和回调的索引*/
    BOOLEAN        in_use;      /* 分配结构时为True*/
} tGAP_INFO;

/* 定义FindAddrByName操作的控制块（一次仅1个活动）*/
typedef struct {
    tGAP_CALLBACK           *p_cback;
    tBTM_INQ_INFO           *p_cur_inq; /* 指向当前查询数据库条目的指针*/
    tGAP_FINDADDR_RESULTS    results;
    BOOLEAN                  in_use;
} tGAP_FINDADDR_CB;

/* 定义GAP连接控制块。
*/
typedef struct {
#define GAP_CCB_STATE_IDLE              0
#define GAP_CCB_STATE_LISTENING         1
#define GAP_CCB_STATE_CONN_SETUP        2
#define GAP_CCB_STATE_CFG_SETUP         3
#define GAP_CCB_STATE_WAIT_SEC          4
#define GAP_CCB_STATE_CONNECTED         5
    UINT8             con_state;

#define GAP_CCB_FLAGS_IS_ORIG           0x01
#define GAP_CCB_FLAGS_HIS_CFG_DONE      0x02
#define GAP_CCB_FLAGS_MY_CFG_DONE       0x04
#define GAP_CCB_FLAGS_SEC_DONE          0x08
#define GAP_CCB_FLAGS_CONN_DONE         0x0E
    UINT8             con_flags;

    UINT8             service_id;           /* BTM使用*/
    UINT16            gap_handle;           /* GAP手柄*/
    UINT16            connection_id;        /* L2CAP CID                            */
    BOOLEAN           rem_addr_specified;
    UINT8             chan_mode_mask;       /* 支持的信道模式（FCR）*/
    BD_ADDR           rem_dev_address;
    UINT16            psm;
    UINT16            rem_mtu_size;

    BOOLEAN           is_congested;
    fixed_queue_t     *tx_queue;             /* 等待发送的缓冲区队列*/
    fixed_queue_t     *rx_queue;             /* 等待读取的缓冲区队列*/

    UINT32            rx_queue_size;        /* rx_queue中的总数据计数*/

    tGAP_CONN_CALLBACK *p_callback;         /* 用户回调函数*/

    tL2CAP_CFG_INFO   cfg;                  /* 配置*/
    tL2CAP_ERTM_INFO  ertm_info;            /* ertm的池和模式*/
} tGAP_CCB;

typedef struct {
#if ((defined AMP_INCLUDED) && (AMP_INCLUDED == TRUE))
    tAMP_APPL_INFO    reg_info;
#else
    tL2CAP_APPL_INFO  reg_info;                     /* L2CAP注册信息*/
#endif
    tGAP_CCB    ccb_pool[GAP_MAX_CONNECTIONS];
} tGAP_CONN;


#if BLE_INCLUDED == TRUE
#define GAP_MAX_CHAR_NUM          4

typedef struct {
    UINT16                  handle;
    UINT16                  uuid;
    tGAP_BLE_ATTR_VALUE     attr_value;
} tGAP_ATTR;
#endif
/**********************************************************************
** M A I N   C O N T R O L   B L O C K
***********************************************************************/

#define GAP_MAX_CL GATT_CL_MAX_LCB

typedef struct {
    UINT16 uuid;
    tGAP_BLE_CMPL_CBACK *p_cback;
} tGAP_BLE_REQ;

typedef struct {
    BD_ADDR                 bda;
    tGAP_BLE_CMPL_CBACK     *p_cback;
    UINT16                  conn_id;
    UINT16                  cl_op_uuid;
    BOOLEAN                 in_use;
    BOOLEAN                 connected;
    fixed_queue_t           *pending_req_q;

} tGAP_CLCB;

typedef struct {
    tGAP_INFO        blk[GAP_MAX_BLOCKS];
    tBTM_CMPL_CB    *btm_cback[GAP_MAX_BLOCKS];
    UINT8            trace_level;
    //tGAP_FINDADDR_CB findaddr_cb;   /* 包含用于查找设备地址的控制块*/
    //tBTM_INQ_INFO*cur_inqptr；

#if GAP_CONN_INCLUDED == TRUE
    tGAP_CONN        conn;
#endif

    /* LE GAP属性数据库*/
#if BLE_INCLUDED == TRUE && GATTS_INCLUDED == TRUE
    tGAP_ATTR               gap_attr[GAP_MAX_CHAR_NUM];
    tGAP_CLCB               clcb[GAP_MAX_CL]; /* 连接链环*/
    tGATT_IF                gatt_if;
#endif
} tGAP_CB;

#if GAP_DYNAMIC_MEMORY == FALSE
extern tGAP_CB  gap_cb;
#else
extern tGAP_CB  *gap_cb_ptr;
#define gap_cb (*gap_cb_ptr)
#endif

#if (GAP_CONN_INCLUDED == TRUE)
extern void gap_conn_init(void);
#endif
#if (BLE_INCLUDED == TRUE && GATTS_INCLUDED == TRUE)
extern void gap_attr_db_init(void);
#endif

#endif

