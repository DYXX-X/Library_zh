/******************************************************************************
 * 版权所有（C）1999-2012 Broadcom Corporation
 *
 *  根据Apache许可证2.0版（“许可证”）获得许可；除非符合许可证，否则不得使用此文件。您可以在以下地址获取许可证副本：
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 *  除非适用法律要求或书面同意，否则根据许可证分发的软件是按“原样”分发的，无任何明示或暗示的担保或条件。有关许可证下权限和限制的具体语言，请参阅许可证。
 *
 ******************************************************************************/

#ifndef  GATT_INT_H
#define  GATT_INT_H

#include "common/bt_target.h"
#include "common/bt_trace.h"
#include "stack/gatt_api.h"
#include "stack/btm_ble_api.h"
#include "stack/btu.h"
#include "osi/fixed_queue.h"

#include <string.h>


#define GATT_CREATE_CONN_ID(tcb_idx, gatt_if)  ((UINT16) ((((UINT8)(tcb_idx) ) << 8) | ((UINT8) (gatt_if))))
#define GATT_GET_TCB_IDX(conn_id)  ((UINT8) (((UINT16) (conn_id)) >> 8))
#define GATT_GET_GATT_IF(conn_id)  ((tGATT_IF)((UINT8) (conn_id)))

#define GATT_GET_SR_REG_PTR(index) (&gatt_cb.sr_reg[(UINT8) (index)]);
#define GATT_TRANS_ID_MAX          0x0fffffff      /* 保留4 MSB*/
#define GATT_RSP_BY_APP            0x00
#define GATT_RSP_BY_STACK          0x01
#define GATT_RSP_DEFAULT           GATT_RSP_BY_APP          //需要通过应用程序进行rsp。

/* GATT写入和读取请求的安全措施*/
#define GATT_SEC_NONE              0
#define GATT_SEC_OK                1
#define GATT_SEC_SIGN_DATA         2   /* 计算write cmd的签名*/
#define GATT_SEC_ENCRYPT           3    /* 使用当前密钥加密链接*/
#define GATT_SEC_ENCRYPT_NO_MITM   4    /* 未经身份验证的加密或更好的加密*/
#define GATT_SEC_ENCRYPT_MITM      5    /* 经过身份验证的加密*/
#define GATT_SEC_ENC_PENDING       6   /* 等待链接加密挂起*/
typedef UINT8 tGATT_SEC_ACTION;


#define GATT_ATTR_OP_SPT_MTU               (0x00000001 << 0)
#define GATT_ATTR_OP_SPT_FIND_INFO         (0x00000001 << 1)
#define GATT_ATTR_OP_SPT_FIND_BY_TYPE      (0x00000001 << 2)
#define GATT_ATTR_OP_SPT_READ_BY_TYPE      (0x00000001 << 3)
#define GATT_ATTR_OP_SPT_READ              (0x00000001 << 4)
#define GATT_ATTR_OP_SPT_MULT_READ         (0x00000001 << 5)
#define GATT_ATTR_OP_SPT_READ_BLOB         (0x00000001 << 6)
#define GATT_ATTR_OP_SPT_READ_BY_GRP_TYPE  (0x00000001 << 7)
#define GATT_ATTR_OP_SPT_WRITE             (0x00000001 << 8)
#define GATT_ATTR_OP_SPT_WRITE_CMD         (0x00000001 << 9)
#define GATT_ATTR_OP_SPT_PREP_WRITE        (0x00000001 << 10)
#define GATT_ATTR_OP_SPT_EXE_WRITE         (0x00000001 << 11)
#define GATT_ATTR_OP_SPT_HDL_VALUE_CONF    (0x00000001 << 12)
#define GATT_ATTR_OP_SP_SIGN_WRITE         (0x00000001 << 13)

#define GATT_INDEX_INVALID      0xff

#define GATT_PENDING_REQ_NONE   0


#define GATT_WRITE_CMD_MASK     0xc0  /*0x1100-0000美元*/
#define GATT_AUTH_SIGN_MASK     0x80  /*0x1000万*/
#define GATT_AUTH_SIGN_LEN      12

#define GATT_HDR_SIZE           3 /* 1B操作码+2B句柄*/

/* 等待ATT cmd响应超时值*/
#define GATT_WAIT_FOR_RSP_TOUT       30
#define GATT_WAIT_FOR_DISC_RSP_TOUT  5
#define GATT_REQ_RETRY_LIMIT         2
#define GATT_WAIT_FOR_IND_ACK_TOUT   5

/* 特征描述符类型*/
#define GATT_DESCR_EXT_DSCPTOR   1    /* 特征扩展属性*/
#define GATT_DESCR_USER_DSCPTOR  2    /* 特征用户描述*/
#define GATT_DESCR_CLT_CONFIG    3    /* 客户端特征配置*/
#define GATT_DESCR_SVR_CONFIG    4    /* 服务器特征配置*/
#define GATT_DESCR_PRES_FORMAT   5    /* 特色演示格式*/
#define GATT_DESCR_AGGR_FORMAT   6    /* 特征聚合格式*/
#define GATT_DESCR_VALID_RANGE   7    /* 特征有效范围*/
#define GATT_DESCR_UNKNOWN       0xff

#define GATT_SEC_FLAG_LKEY_UNAUTHED     BTM_SEC_FLAG_LKEY_KNOWN
#define GATT_SEC_FLAG_LKEY_AUTHED       BTM_SEC_FLAG_LKEY_AUTHED
#define GATT_SEC_FLAG_ENCRYPTED         BTM_SEC_FLAG_ENCRYPTED
#define GATT_SEC_FLAG_AUTHORIZATION     BTM_SEC_FLAG_AUTHORIZED
typedef UINT8 tGATT_SEC_FLAG;

/* 查找信息响应类型
*/
#define GATT_INFO_TYPE_PAIR_16      0x01
#define GATT_INFO_TYPE_PAIR_128     0x02

#define GATTS_SEND_SERVICE_CHANGE_AUTO   0
#define GATTS_SEND_SERVICE_CHANGE_MANUAL 1

/*  GATT客户端FIND_TYPE_VALUE_Request数据*/
typedef struct {
    tBT_UUID        uuid;           /* 要查找的属性类型*/
    UINT16          s_handle;       /* 起动手柄*/
    UINT16          e_handle;       /* 末端手柄*/
    UINT16          value_len;      /* 属性值的长度*/
    UINT8           value[GATT_MAX_MTU_SIZE];       /* 指向要查找的属性值的指针*/
} tGATT_FIND_TYPE_VALUE;

/* ATT协议的客户端请求消息
*/
typedef union {
    tGATT_READ_BY_TYPE      browse;     /* 按类型读取请求*/
    tGATT_FIND_TYPE_VALUE   find_type_value;/* 按类型值查找*/
    tGATT_READ_MULTI        read_multi;   /* 读取多个请求*/
    tGATT_READ_PARTIAL      read_blob;    /* 读取blob*/
    tGATT_VALUE             attr_value;   /* 写入请求*/
    /* 准备写入*/
    /* 写入blob*/
    UINT16                  handle;        /* 读取，处理值确认*/
    UINT16                  mtu;
    tGATT_EXEC_FLAG         exec_write;    /* 执行写入*/
} tGATT_CL_MSG;

/* 错误响应结构*/
typedef struct {
    UINT16  handle;
    UINT8   cmd_code;
    UINT8   reason;
} tGATT_ERROR;

/* 执行写响应结构*/
typedef struct {
    UINT8   op_code;
}__attribute__((packed)) tGATT_EXEC_WRITE_RSP;

/* 写入请求响应结构*/
typedef struct {
    UINT8   op_code;
}__attribute__((packed)) tGATT_WRITE_REQ_RSP;

/* ATT协议的服务器响应消息
*/
typedef union {
    /* 数据类型成员事件*/
    tGATT_VALUE             attr_value;     /* READ, HANDLE_VALUE_IND, PREPARE_WRITE */
    /* READ_BLOB, READ_BY_TYPE */
    tGATT_ERROR             error;          /* ERROR_RSP */
    UINT16                  handle;         /* WRITE, WRITE_BLOB */
    UINT16                  mtu;            /* 交换MTU请求*/
} tGATT_SR_MSG;

/* 特征声明属性值
*/
typedef struct {
    tGATT_CHAR_PROP             property;
    UINT16                      char_val_handle;
} tGATT_CHAR_DECL;

/* 服务器数据库中维护的属性值
*/
typedef union {
    tBT_UUID                uuid;               /* 服务声明*/
    tGATT_CHAR_DECL         char_decl;          /* 特性声明*/
    tGATT_INCL_SRVC         incl_handle;        /* 包含的服务*/
    tGATT_ATTR_VAL          attr_val;
} tGATT_ATTR_VALUE;

/* 属性UUID类型
*/
#define GATT_ATTR_UUID_TYPE_16      0
#define GATT_ATTR_UUID_TYPE_128     1
#define GATT_ATTR_UUID_TYPE_32      2
typedef UINT8   tGATT_ATTR_UUID_TYPE;

/* 服务器数据库中的16位UUID属性
*/
typedef struct {
    void                    *p_next;  /* 指向下一个属性的指针，tGATT_ATTR16或tGATT_ATTR128*/
    tGATT_ATTR_VALUE        *p_value;
    tGATT_ATTR_UUID_TYPE    uuid_type;
    tGATT_PERM              permission;
    tGATTS_ATTR_CONTROL     control;
    tGATT_ATTR_MASK         mask;
    UINT16                  handle;
    UINT16                  uuid;
} tGATT_ATTR16;

/* 服务器数据库中的32位UUID属性
*/
typedef struct {
    void                    *p_next;  /* 指向下一个属性的指针，tGATT_ATTR16、tGATT_ATTR32或tGATT_ATTR128*/
    tGATT_ATTR_VALUE        *p_value;
    tGATT_ATTR_UUID_TYPE    uuid_type;
    tGATT_PERM              permission;
    tGATTS_ATTR_CONTROL     control;
    tGATT_ATTR_MASK         mask;
    UINT16                  handle;
    UINT32                  uuid;
} tGATT_ATTR32;


/* 服务器数据库中的128位UUID属性
*/
typedef struct {
    void                    *p_next;  /* 指向下一个属性的指针，tGATT_ATTR16或tGATT_ATTR128*/
    tGATT_ATTR_VALUE        *p_value;
    tGATT_ATTR_UUID_TYPE    uuid_type;
    tGATT_PERM              permission;
    tGATTS_ATTR_CONTROL     control;
    tGATT_ATTR_MASK         mask;
    UINT16                  handle;
    UINT8                   uuid[LEN_UUID_128];
} tGATT_ATTR128;

/* 服务数据库定义
*/
typedef struct {
    void            *p_attr_list;       /* 指向第一个属性的指针，tGATT_ATTR16或tGATT_ATTR128*/
    UINT8           *p_free_mem;        /* 指向可用内存的指针*/
    fixed_queue_t   *svc_buffer;         /* 用于服务数据库的缓冲区队列*/
    UINT32          mem_free;           /* 内存仍然可用*/
    UINT16          end_handle;         /* 最后一个句柄编号*/
    UINT16          next_handle;        /* 下一个可用句柄值*/
} tGATT_SVC_DB;

/* GATT服务器使用的数据结构*/
/* GATT注册记录由一个句柄和一个或多个属性组成*/
/* 服务注册信息记录包括开始和结束*/
/* 属性句柄、服务UUID和一组GATT服务器回调。*/
typedef struct {
    tGATT_SVC_DB    *p_db;              /* 指向服务数据库的指针*/
    tBT_UUID        app_uuid;           /* 应用UUID*/
    UINT32          sdp_handle;         /* 主服务SDP句柄*/
    UINT16          service_instance;   /* 服务实例编号*/
    UINT16          type;               /* 服务类型UUID，主要或次要*/
    UINT16          s_hdl;              /* 服务启动手柄*/
    UINT16          e_hdl;              /* 服务结束句柄*/
    tGATT_IF        gatt_if;            /* 此服务属于哪个应用程序*/
    BOOLEAN         in_use;
} tGATT_SR_REG;

#define GATT_LISTEN_TO_ALL  0xff
#define GATT_LISTEN_TO_NONE 0

/* GATT服务器使用的数据结构*/
/* GATT注册记录由一个句柄和一个或多个属性组成*/
/* 服务注册信息记录包括开始和结束*/
/* 属性句柄、服务UUID和一组GATT服务器回调。*/

typedef struct {
    tBT_UUID     app_uuid128;
    tGATT_CBACK  app_cb;
    tGATT_IF     gatt_if; /* 基于一个*/
    BOOLEAN      in_use;
    UINT8        listening; /* 如果已启用adv for all*/
} tGATT_REG;




/* 每个连接的命令队列*/
typedef struct {
    BT_HDR      *p_cmd;
    UINT16      clcb_idx;
    UINT8       op_code;
    BOOLEAN     to_send;
} tGATT_CMD_Q;


#if GATT_MAX_SR_PROFILES <= 8
typedef UINT8 tGATT_APP_MASK;
#elif GATT_MAX_SR_PROFILES <= 16
typedef UINT16 tGATT_APP_MASK;
#elif GATT_MAX_SR_PROFILES <= 32
typedef UINT32 tGATT_APP_MASK;
#endif

/* 每个连接的命令详细信息*/
typedef struct {
    BT_HDR          *p_rsp_msg;
    UINT32           trans_id;
    tGATT_READ_MULTI multi_req;
    fixed_queue_t    *multi_rsp_q;
    UINT16           handle;
    UINT8            op_code;
    UINT8            status;
    UINT8            cback_cnt[GATT_MAX_APPS];
} tGATT_SR_CMD;

#define     GATT_CH_CLOSE               0
#define     GATT_CH_CLOSING             1
#define     GATT_CH_CONN                2
#define     GATT_CH_CFG                 3
#define     GATT_CH_OPEN                4

typedef UINT8 tGATT_CH_STATE;

#define GATT_GATT_START_HANDLE  1
#define GATT_GAP_START_HANDLE   20
#define GATT_APP_START_HANDLE   40

typedef struct hdl_cfg {
    UINT16               gatt_start_hdl;
    UINT16               gap_start_hdl;
    UINT16               app_start_hdl;
} tGATT_HDL_CFG;

typedef struct hdl_list_elem {
    struct              hdl_list_elem *p_next;
    struct              hdl_list_elem *p_prev;
    tGATTS_HNDL_RANGE   asgn_range; /* 指定手柄范围*/
    tGATT_SVC_DB        svc_db;
    BOOLEAN             in_use;
} tGATT_HDL_LIST_ELEM;

typedef struct {
    tGATT_HDL_LIST_ELEM  *p_first;
    tGATT_HDL_LIST_ELEM  *p_last;
    UINT16               count;
} tGATT_HDL_LIST_INFO;


typedef struct srv_list_elem {
    struct              srv_list_elem *p_next;
    struct              srv_list_elem *p_prev;
    UINT16              s_hdl;
    UINT8               i_sreg;
    BOOLEAN             in_use;
    BOOLEAN             is_primary;
} tGATT_SRV_LIST_ELEM;


typedef struct {
    tGATT_SRV_LIST_ELEM  *p_last_primary;
    tGATT_SRV_LIST_ELEM  *p_first;
    tGATT_SRV_LIST_ELEM  *p_last;
    UINT16               count;
} tGATT_SRV_LIST_INFO;

/* 准备写入队列数据*/
typedef struct{
    //len：值的长度
    tGATT_ATTR16  *p_attr;
    UINT16 len;
    UINT8 op_code;
    UINT16 handle;
    UINT16 offset;
    UINT8 value[2];
}__attribute__((packed)) tGATT_PREPARE_WRITE_QUEUE_DATA;

/* 存储准备写入包信息的结构*/
typedef struct{
    //只存储需要
    //由堆栈（而不是应用程序）响应
    fixed_queue_t *queue;

    //存储准备写入数据包的总数
    //包括应该由堆栈或应用程序响应的
    UINT16 total_num;

    //存储用于准备写入的应用程序错误代码，
    //无效偏移量和无效长度
    UINT8 error_code_app;
}tGATT_PREPARE_WRITE_RECORD;

typedef struct {
    fixed_queue_t    *pending_enc_clcb;   /* 未决加密信道q*/
    tGATT_SEC_ACTION sec_act;
    BD_ADDR         peer_bda;
    tBT_TRANSPORT   transport;
    UINT32          trans_id;

    UINT16          att_lcid;           /* ATT的L2CAP信道ID*/
    UINT16          payload_size;

    tGATT_CH_STATE  ch_state;
    UINT8           ch_flags;

    tGATT_IF        app_hold_link[GATT_MAX_APPS];

    /* 服务器需求*/
    /* 服务器响应数据*/
#if (GATTS_INCLUDED == TRUE)
    tGATT_SR_CMD    sr_cmd;
#endif  ///GATTS_INCLUDED == TRUE
    UINT16          indicate_handle;
    fixed_queue_t   *pending_ind_q;

    TIMER_LIST_ENT  conf_timer_ent;     /* 对等确认指示计时器*/

    UINT8           prep_cnt[GATT_MAX_APPS];
    UINT8           ind_count;

    tGATT_CMD_Q     cl_cmd_q[GATT_CL_MAX_LCB];
    TIMER_LIST_ENT  ind_ack_timer_ent;    /* 本地应用程序确认指示计时器*/
    UINT8           pending_cl_req;
    UINT8           next_slot_inq;    /* 队列中下一个可用插槽的索引*/

    BOOLEAN         in_use;
    UINT8           tcb_idx;
    tGATT_PREPARE_WRITE_RECORD prepare_write_record;    /* 准备写入数据包记录*/
} tGATT_TCB;


/* 逻辑通道*/
typedef struct {
    UINT16                  next_disc_start_hdl;   /* 下一个inc srvv发现的启动句柄*/
    tGATT_DISC_RES          result;
    BOOLEAN                 wait_for_read_rsp;
} tGATT_READ_INC_UUID128;
typedef struct {
    tGATT_TCB               *p_tcb;         /* 该CLCB的相关TCB*/
    tGATT_REG               *p_reg;        /* 该CLCB的所有者*/
    UINT8                   sccb_idx;
    UINT8                   *p_attr_buf;    /* 读取多个属性缓冲区，准备写入*/
    tBT_UUID                uuid;
    UINT16                  conn_id;        /* 连接手柄*/
    UINT16                  clcb_idx;
    UINT16                  s_handle;       /* 活动请求的启动句柄*/
    UINT16                  e_handle;       /* 活动请求的结束句柄*/
    UINT16                  counter;        /* 用作偏移量、属性长度、准备写入数*/
    UINT16                  start_offset;
    tGATT_AUTH_REQ          auth_req;       /* 认证要求*/
    UINT8                   operation;      /* 一个逻辑通道可以激活一个操作*/
    UINT8                   op_subtype;     /* 操作子类型*/
    UINT8                   status;         /* 运行状态*/
    BOOLEAN                 first_read_blob_after_read;
    tGATT_READ_INC_UUID128  read_uuid128;
    BOOLEAN                 in_use;
    TIMER_LIST_ENT          rsp_timer_ent;  /* 对等响应计时器*/
    UINT8                   retry_count;

} tGATT_CLCB;

typedef struct {
    tGATT_CLCB  *p_clcb;
} tGATT_PENDING_ENC_CLCB;


#define GATT_SIGN_WRITE             1
#define GATT_VERIFY_SIGN_DATA       2

typedef struct {
    BT_HDR      hdr;
    tGATT_CLCB  *p_clcb;
} tGATT_SIGN_WRITE_OP;

typedef struct {
    BT_HDR      hdr;
    tGATT_TCB   *p_tcb;
    BT_HDR      *p_data;

} tGATT_VERIFY_SIGN_OP;


typedef struct {
    UINT16                  clcb_idx;
    BOOLEAN                 in_use;
} tGATT_SCCB;

typedef struct {
    UINT16      handle;
    UINT16      uuid;
    UINT32      service_change;
} tGATT_SVC_CHG;

typedef struct {
    tGATT_IF        gatt_if[GATT_MAX_APPS];
    tGATT_IF        listen_gif[GATT_MAX_APPS];
    BD_ADDR         remote_bda;
    BOOLEAN         in_use;
} tGATT_BG_CONN_DEV;

#define GATT_SVC_CHANGED_CONNECTING        1   /* 等待连接*/
#define GATT_SVC_CHANGED_SERVICE           2   /* GATT服务发现*/
#define GATT_SVC_CHANGED_CHARACTERISTIC    3   /* 服务更改字符发现*/
#define GATT_SVC_CHANGED_DESCRIPTOR        4   /* 服务变更CCC折扣店*/
#define GATT_SVC_CHANGED_CONFIGURE_CCCD    5   /* 配置CCC*/

typedef struct {
    UINT16  conn_id;
    BOOLEAN in_use;
    BOOLEAN connected;
    BD_ADDR bda;
    tBT_TRANSPORT   transport;

    /* GATT服务变更CCC相关变量*/
    UINT8       ccc_stage;
    UINT8       ccc_result;
    UINT16      s_handle;
    UINT16      e_handle;
} tGATT_PROFILE_CLCB;

typedef struct {
    list_t              *p_tcb_list;
    fixed_queue_t       *sign_op_queue;

    tGATT_SR_REG        sr_reg[GATT_MAX_SR_PROFILES];
    UINT16              next_handle;    /* 下一个可用句柄*/
    tGATT_SVC_CHG       gattp_attr;     /* GATT配置文件属性服务更改*/
    tGATT_IF            gatt_if;
#if (GATTS_INCLUDED == TRUE)
    tGATT_HDL_LIST_INFO hdl_list_info;
    tGATT_HDL_LIST_ELEM hdl_list[GATT_MAX_SR_PROFILES];
    tGATT_SRV_LIST_INFO srv_list_info;
    tGATT_SRV_LIST_ELEM srv_list[GATT_MAX_SR_PROFILES];
#endif  ///GATTS_INCLUDED == TRUE
    fixed_queue_t       *srv_chg_clt_q;   /* 服务更改客户端队列*/
    fixed_queue_t       *pending_new_srv_start_q; /* 挂起的新服务启动队列*/
    tGATT_REG           cl_rcb[GATT_MAX_APPS];
    list_t              *p_clcb_list;           /* 连接链路控制块*/
    tGATT_SCCB          sccb[GATT_MAX_SCCB];    /* 签名完成回调函数GATT_MAX_SCCB<=GATT_CL_MAX_LCB*/
    UINT8               trace_level;
    UINT16              def_mtu_size;

#if GATT_CONFORMANCE_TESTING == TRUE
    BOOLEAN             enable_err_rsp;
    UINT8               req_op_code;
    UINT8               err_status;
    UINT16              handle;
#endif
#if (GATTS_INCLUDED == TRUE)
    tGATT_PROFILE_CLCB  profile_clcb[GATT_MAX_APPS];
#endif  ///GATTS_INCLUDED == TRUE
    UINT16              handle_of_h_r;          /* 手柄的手柄重复使用特征值*/

    tGATT_APPL_INFO       cb_info;



    tGATT_HDL_CFG           hdl_cfg;
    tGATT_BG_CONN_DEV       bgconn_dev[GATT_MAX_BG_CONN_DEV];

} tGATT_CB;

typedef struct{
    UINT16 local_mtu;
} tGATT_DEFAULT;

#define GATT_SIZE_OF_SRV_CHG_HNDL_RANGE 4

#ifdef __cplusplus
extern "C" {
#endif

extern tGATT_DEFAULT gatt_default;

/* 全球GATT数据*/
#if GATT_DYNAMIC_MEMORY == FALSE
extern tGATT_CB  gatt_cb;
#else
extern tGATT_CB *gatt_cb_ptr;
#define gatt_cb (*gatt_cb_ptr)
#endif

#if GATT_CONFORMANCE_TESTING == TRUE
extern void gatt_set_err_rsp(BOOLEAN enable, UINT8 req_op_code, UINT8 err_status);
#endif

#ifdef __cplusplus
}
#endif

/* 内部功能*/
extern void gatt_init (void);
extern void gatt_free(void);

/* 来自gatt_main。c*/
extern BOOLEAN gatt_disconnect (tGATT_TCB *p_tcb);
extern BOOLEAN gatt_act_connect (tGATT_REG *p_reg, BD_ADDR bd_addr, tBLE_ADDR_TYPE bd_addr_type, tBT_TRANSPORT transport, BOOLEAN is_aux);
extern BOOLEAN gatt_connect (BD_ADDR rem_bda, tBLE_ADDR_TYPE bd_addr_type, tGATT_TCB *p_tcb, tBT_TRANSPORT transport, BOOLEAN is_aux);
extern void gatt_data_process (tGATT_TCB *p_tcb, BT_HDR *p_buf);
extern void gatt_update_app_use_link_flag ( tGATT_IF gatt_if, tGATT_TCB *p_tcb, BOOLEAN is_add, BOOLEAN check_acl_link);

extern void gatt_profile_db_init(void);
extern void gatt_set_ch_state(tGATT_TCB *p_tcb, tGATT_CH_STATE ch_state);
extern tGATT_CH_STATE gatt_get_ch_state(tGATT_TCB *p_tcb);
extern void gatt_init_srv_chg(void);
extern void gatt_proc_srv_chg (void);
extern tGATT_STATUS gatt_send_srv_chg_ind (BD_ADDR peer_bda);
extern void gatt_chk_srv_chg(tGATTS_SRV_CHG *p_srv_chg_clt);
extern void gatt_add_a_bonded_dev_for_srv_chg (BD_ADDR bda);

/* 来自gatt_attr。c*/
extern UINT16 gatt_profile_find_conn_id_by_bd_addr(BD_ADDR bda);


/* att_procol提供的功能。c*/
extern tGATT_STATUS attp_send_cl_msg (tGATT_TCB *p_tcb, UINT16 clcb_idx, UINT8 op_code, tGATT_CL_MSG *p_msg);
extern BT_HDR *attp_build_sr_msg(tGATT_TCB *p_tcb, UINT8 op_code, tGATT_SR_MSG *p_msg);
extern tGATT_STATUS attp_send_sr_msg (tGATT_TCB *p_tcb, BT_HDR *p_msg);
extern tGATT_STATUS attp_send_msg_to_l2cap(tGATT_TCB *p_tcb, BT_HDR *p_toL2CAP);

/* 效用函数*/
extern UINT8 *gatt_dbg_op_name(UINT8 op_code);
#if (SDP_INCLUDED == TRUE && CLASSIC_BT_GATT_INCLUDED == TRUE)
extern UINT32 gatt_add_sdp_record (tBT_UUID *p_uuid, UINT16 start_hdl, UINT16 end_hdl);
#endif  ///SDP_INCLUDED == TRUE && CLASSIC_BT_GATT_INCLUDED == TRUE
extern BOOLEAN gatt_parse_uuid_from_cmd(tBT_UUID *p_uuid, UINT16 len, UINT8 **p_data);
extern UINT8 gatt_build_uuid_to_stream(UINT8 **p_dst, tBT_UUID uuid);
extern BOOLEAN gatt_uuid_compare(tBT_UUID src, tBT_UUID tar);
extern void gatt_convert_uuid32_to_uuid128(UINT8 uuid_128[LEN_UUID_128], UINT32 uuid_32);
extern void gatt_sr_get_sec_info(BD_ADDR rem_bda, tBT_TRANSPORT transport, UINT8 *p_sec_flag, UINT8 *p_key_size);
extern void gatt_start_rsp_timer(UINT16 clcb_idx);
extern void gatt_start_conf_timer(tGATT_TCB    *p_tcb);
extern void gatt_rsp_timeout(TIMER_LIST_ENT *p_tle);
extern void gatt_ind_ack_timeout(TIMER_LIST_ENT *p_tle);
extern void gatt_start_ind_ack_timer(tGATT_TCB *p_tcb);
extern tGATT_STATUS gatt_send_error_rsp(tGATT_TCB *p_tcb, UINT8 err_code, UINT8 op_code, UINT16 handle, BOOLEAN deq);
extern void gatt_dbg_display_uuid(tBT_UUID bt_uuid);
extern tGATT_PENDING_ENC_CLCB *gatt_add_pending_enc_channel_clcb(tGATT_TCB *p_tcb, tGATT_CLCB *p_clcb );

extern tGATTS_PENDING_NEW_SRV_START *gatt_sr_is_new_srv_chg(tBT_UUID *p_app_uuid128, tBT_UUID *p_svc_uuid, UINT16 svc_inst);

extern BOOLEAN gatt_is_srv_chg_ind_pending (tGATT_TCB *p_tcb);
extern tGATTS_SRV_CHG *gatt_is_bda_in_the_srv_chg_clt_list (BD_ADDR bda);

extern BOOLEAN gatt_find_the_connected_bda(UINT8 start_idx, BD_ADDR bda, UINT8 *p_found_idx, tBT_TRANSPORT *p_transport);
extern void gatt_set_srv_chg(void);
extern void gatt_delete_dev_from_srv_chg_clt_list(BD_ADDR bd_addr);
extern tGATT_VALUE *gatt_add_pending_ind(tGATT_TCB  *p_tcb, tGATT_VALUE *p_ind);
extern tGATTS_PENDING_NEW_SRV_START *gatt_add_pending_new_srv_start( tGATTS_HNDL_RANGE *p_new_srv_start);
extern void gatt_free_srvc_db_buffer_app_id(tBT_UUID *p_app_id);
extern BOOLEAN gatt_update_listen_mode(void);
extern BOOLEAN gatt_cl_send_next_cmd_inq(tGATT_TCB *p_tcb);

/* 保留句柄列表*/
extern tGATT_HDL_LIST_ELEM *gatt_find_hdl_buffer_by_app_id (tBT_UUID *p_app_uuid128, tBT_UUID *p_svc_uuid, UINT16 svc_inst);
extern tGATT_HDL_LIST_ELEM *gatt_find_hdl_buffer_by_handle(UINT16 handle);
extern tGATT_HDL_LIST_ELEM *gatt_find_hdl_buffer_by_attr_handle(UINT16 attr_handle);
extern tGATT_HDL_LIST_ELEM *gatt_alloc_hdl_buffer(void);
extern void gatt_free_hdl_buffer(tGATT_HDL_LIST_ELEM *p);
extern void gatt_free_attr_value_buffer(tGATT_HDL_LIST_ELEM *p);
extern BOOLEAN gatt_is_last_attribute(tGATT_SRV_LIST_INFO *p_list, tGATT_SRV_LIST_ELEM *p_start, tBT_UUID value);
extern void gatt_update_last_pri_srv_info(tGATT_SRV_LIST_INFO *p_list);
extern BOOLEAN gatt_add_a_srv_to_list(tGATT_SRV_LIST_INFO *p_list, tGATT_SRV_LIST_ELEM *p_new);
extern BOOLEAN gatt_remove_a_srv_from_list(tGATT_SRV_LIST_INFO *p_list, tGATT_SRV_LIST_ELEM *p_remove);
extern BOOLEAN gatt_add_an_item_to_list(tGATT_HDL_LIST_INFO *p_list, tGATT_HDL_LIST_ELEM *p_new);
extern BOOLEAN gatt_remove_an_item_from_list(tGATT_HDL_LIST_INFO *p_list, tGATT_HDL_LIST_ELEM *p_remove);
extern tGATTS_SRV_CHG *gatt_add_srv_chg_clt(tGATTS_SRV_CHG *p_srv_chg);

/* 用于后台连接*/
extern BOOLEAN gatt_update_auto_connect_dev (tGATT_IF gatt_if, BOOLEAN add, BD_ADDR bd_addr, BOOLEAN is_initiator);
extern BOOLEAN gatt_is_bg_dev_for_app(tGATT_BG_CONN_DEV *p_dev, tGATT_IF gatt_if);
extern BOOLEAN gatt_remove_bg_dev_for_app(tGATT_IF gatt_if, BD_ADDR bd_addr);
extern UINT8 gatt_get_num_apps_for_bg_dev(BD_ADDR bd_addr);
extern BOOLEAN gatt_find_app_for_bg_dev(BD_ADDR bd_addr, tGATT_IF *p_gatt_if);
extern tGATT_BG_CONN_DEV *gatt_find_bg_dev(BD_ADDR remote_bda);
extern void gatt_deregister_bgdev_list(tGATT_IF gatt_if);
extern void gatt_reset_bgdev_list(void);

/* 服务器功能*/
extern UINT8 gatt_sr_find_i_rcb_by_handle(UINT16 handle);
extern UINT8 gatt_sr_find_i_rcb_by_app_id(tBT_UUID *p_app_uuid128, tBT_UUID *p_svc_uuid, UINT16 svc_inst);
extern UINT8 gatt_sr_alloc_rcb(tGATT_HDL_LIST_ELEM *p_list);
extern tGATT_STATUS gatt_sr_process_app_rsp (tGATT_TCB *p_tcb, tGATT_IF gatt_if, UINT32 trans_id, UINT8 op_code, tGATT_STATUS status, tGATTS_RSP *p_msg);
extern void gatt_server_handle_client_req (tGATT_TCB *p_tcb, UINT8 op_code,
        UINT16 len, UINT8 *p_data);
extern void gatt_sr_send_req_callback(UINT16 conn_id,  UINT32 trans_id,
                                      UINT8 op_code, tGATTS_DATA *p_req_data);
extern UINT32 gatt_sr_enqueue_cmd (tGATT_TCB *p_tcb, UINT8 op_code, UINT16 handle);
extern BOOLEAN gatt_cancel_open(tGATT_IF gatt_if, BD_ADDR bda);

/*   */

extern tGATT_REG *gatt_get_regcb (tGATT_IF gatt_if);
extern BOOLEAN gatt_is_clcb_allocated (UINT16 conn_id);
extern tGATT_CLCB *gatt_clcb_alloc (UINT16 conn_id);
extern void gatt_clcb_dealloc (tGATT_CLCB *p_clcb);
extern tGATT_CLCB *gatt_clcb_find_by_conn_id(UINT16 conn_id);
extern tGATT_CLCB *gatt_clcb_find_by_idx(UINT16 cclcb_idx);

extern void gatt_sr_copy_prep_cnt_to_cback_cnt(tGATT_TCB *p_tcb );
extern BOOLEAN gatt_sr_is_cback_cnt_zero(tGATT_TCB *p_tcb );
extern BOOLEAN gatt_sr_is_prep_cnt_zero(tGATT_TCB *p_tcb );
extern void gatt_sr_reset_cback_cnt(tGATT_TCB *p_tcb );
extern void gatt_sr_reset_prep_cnt(tGATT_TCB *p_tcb );
extern void gatt_sr_update_cback_cnt(tGATT_TCB *p_tcb, tGATT_IF gatt_if, BOOLEAN is_inc, BOOLEAN is_reset_first);
extern void gatt_sr_update_prep_cnt(tGATT_TCB *p_tcb, tGATT_IF gatt_if, BOOLEAN is_inc, BOOLEAN is_reset_first);

extern BOOLEAN gatt_find_app_hold_link(tGATT_TCB *p_tcb, UINT8 start_idx, UINT8 *p_found_idx, tGATT_IF *p_gatt_if);
extern BOOLEAN gatt_find_specific_app_in_hold_link(tGATT_TCB *p_tcb, tGATT_IF p_gatt_if);
extern UINT8 gatt_num_apps_hold_link(tGATT_TCB *p_tcb);
extern UINT8 gatt_num_clcb_by_bd_addr(BD_ADDR bda);
extern tGATT_TCB *gatt_find_tcb_by_cid(UINT16 lcid);
extern tGATT_TCB *gatt_allocate_tcb_by_bdaddr(BD_ADDR bda, tBT_TRANSPORT transport);
extern tGATT_TCB *gatt_get_tcb_by_idx(UINT8 tcb_idx);
extern tGATT_TCB *gatt_find_tcb_by_addr(BD_ADDR bda, tBT_TRANSPORT transport);
extern BOOLEAN gatt_send_ble_burst_data (BD_ADDR remote_bda,  BT_HDR *p_buf);
extern void gatt_tcb_free( tGATT_TCB *p_tcb);

/* GATT客户功能*/
extern void gatt_dequeue_sr_cmd (tGATT_TCB *p_tcb);
extern UINT8 gatt_send_write_msg(tGATT_TCB *p_tcb, UINT16 clcb_idx, UINT8 op_code, UINT16 handle,
                                 UINT16 len, UINT16 offset, UINT8 *p_data);
extern void gatt_cleanup_upon_disc(BD_ADDR bda, UINT16 reason, tBT_TRANSPORT transport);
extern void gatt_end_operation(tGATT_CLCB *p_clcb, tGATT_STATUS status, void *p_data);

extern void gatt_act_discovery(tGATT_CLCB *p_clcb);
extern void gatt_act_read(tGATT_CLCB *p_clcb, UINT16 offset);
extern void gatt_act_write(tGATT_CLCB *p_clcb, UINT8 sec_act);
extern UINT8 gatt_act_send_browse(tGATT_TCB *p_tcb, UINT16 index, UINT8 op, UINT16 s_handle, UINT16 e_handle,
                                  tBT_UUID uuid);
extern tGATT_CLCB *gatt_cmd_dequeue(tGATT_TCB *p_tcb, UINT8 *p_opcode);
extern BOOLEAN gatt_cmd_enq(tGATT_TCB *p_tcb, UINT16 clcb_idx, BOOLEAN to_send, UINT8 op_code, BT_HDR *p_buf);
extern void gatt_client_handle_server_rsp (tGATT_TCB *p_tcb, UINT8 op_code,
        UINT16 len, UINT8 *p_data);
extern void gatt_send_queue_write_cancel (tGATT_TCB *p_tcb, tGATT_CLCB *p_clcb, tGATT_EXEC_FLAG flag);

/* gatt_auth。c*/
extern BOOLEAN gatt_security_check_start(tGATT_CLCB *p_clcb);
extern void gatt_verify_signature(tGATT_TCB *p_tcb, BT_HDR *p_buf);
extern tGATT_SEC_ACTION gatt_determine_sec_act(tGATT_CLCB *p_clcb );
extern tGATT_STATUS gatt_get_link_encrypt_status(tGATT_TCB *p_tcb);
extern tGATT_SEC_ACTION gatt_get_sec_act(tGATT_TCB *p_tcb);
extern void gatt_set_sec_act(tGATT_TCB *p_tcb, tGATT_SEC_ACTION sec_act);

/* 集合数据库c*/
extern BOOLEAN gatts_init_service_db (tGATT_SVC_DB *p_db, tBT_UUID *p_service, BOOLEAN is_pri, UINT16 s_hdl, UINT16 num_handle);
extern UINT16 gatts_add_included_service (tGATT_SVC_DB *p_db, UINT16 s_handle, UINT16 e_handle, tBT_UUID service);
extern UINT16 gatts_add_characteristic (tGATT_SVC_DB *p_db, tGATT_PERM perm,
                                                        tGATT_CHAR_PROP property,
                                                        tBT_UUID *p_char_uuid, tGATT_ATTR_VAL *attr_val,
                                                        tGATTS_ATTR_CONTROL *control);
extern UINT16 gatts_add_char_descr (tGATT_SVC_DB *p_db, tGATT_PERM perm,
                                         tBT_UUID *p_dscp_uuid, tGATT_ATTR_VAL *attr_val,
                                         tGATTS_ATTR_CONTROL *control);

extern tGATT_STATUS gatts_set_attribute_value(tGATT_SVC_DB *p_db, UINT16 attr_handle,
                                    UINT16 length, UINT8 *value);

extern tGATT_STATUS gatts_get_attribute_value(tGATT_SVC_DB *p_db, UINT16 attr_handle,
                                    UINT16 *length, UINT8 **value);
extern BOOLEAN gatts_is_auto_response(UINT16 attr_handle);
extern tGATT_STATUS gatts_db_read_attr_value_by_type (tGATT_TCB *p_tcb, tGATT_SVC_DB *p_db, UINT8 op_code, BT_HDR *p_rsp, UINT16 s_handle,
        UINT16 e_handle, tBT_UUID type, UINT16 *p_len, tGATT_SEC_FLAG sec_flag, UINT8 key_size, UINT32 trans_id, UINT16 *p_cur_handle);
extern tGATT_STATUS gatts_read_attr_value_by_handle(tGATT_TCB *p_tcb, tGATT_SVC_DB *p_db, UINT8 op_code, UINT16 handle, UINT16 offset,
        UINT8 *p_value, UINT16 *p_len, UINT16 mtu, tGATT_SEC_FLAG sec_flag, UINT8 key_size, UINT32 trans_id);
extern tGATT_STATUS gatts_write_attr_value_by_handle(tGATT_SVC_DB *p_db,
                                                            UINT16 handle, UINT16 offset,
                                                            UINT8 *p_value, UINT16 len);
extern tGATT_STATUS gatts_write_attr_perm_check (tGATT_SVC_DB *p_db, UINT8 op_code, UINT16 handle, UINT16 offset, UINT8 *p_data,
        UINT16 len, tGATT_SEC_FLAG sec_flag, UINT8 key_size);
extern tGATT_STATUS gatts_read_attr_perm_check(tGATT_SVC_DB *p_db, BOOLEAN is_long, UINT16 handle, tGATT_SEC_FLAG sec_flag, UINT8 key_size);
extern void gatts_update_srv_list_elem(UINT8 i_sreg, UINT16 handle, BOOLEAN is_primary);
extern tBT_UUID *gatts_get_service_uuid (tGATT_SVC_DB *p_db);

extern void gatt_reset_bgdev_list(void);
extern uint16_t gatt_get_local_mtu(void);
extern void gatt_set_local_mtu(uint16_t mtu);
#endif

