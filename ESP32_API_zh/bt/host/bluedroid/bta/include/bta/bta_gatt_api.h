/******************************************************************************
 * 版权所有（C）2003-2013 Broadcom Corporation
 *
 *  根据Apache许可证2.0版（“许可证”）获得许可；除非符合许可证，否则不得使用此文件。您可以在以下地址获取许可证副本：
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 *  除非适用法律要求或书面同意，否则根据许可证分发的软件是按“原样”分发的，无任何明示或暗示的担保或条件。有关许可证下权限和限制的具体语言，请参阅许可证。
 *
 ******************************************************************************/

/******************************************************************************
 * 这是BTA GATT的公共接口文件。
 *
 ******************************************************************************/

#ifndef BTA_GATT_API_H
#define BTA_GATT_API_H

#include "bta/bta_api.h"
#include "stack/gatt_api.h"
#include "osi/list.h"

#ifndef     BTA_GATT_INCLUDED
#define     BTA_GATT_INCLUDED     FALSE
#endif

#if ((BLE_INCLUDED == FALSE) && (BTA_GATT_INCLUDED == TRUE))
#undef BTA_GATT_INCLUDED
#define BTA_GATT_INCLUDED        FALSE
#endif


#ifndef     BTA_GATT_DEBUG
#define     BTA_GATT_DEBUG       FALSE
#endif

typedef enum {
    BTGATT_DB_PRIMARY_SERVICE,
    BTGATT_DB_SECONDARY_SERVICE,
    BTGATT_DB_CHARACTERISTIC,
    BTGATT_DB_DESCRIPTOR,
    BTGATT_DB_INCLUDED_SERVICE,
}bt_gatt_db_attribute_type_t;

typedef enum {
    GATT_OP_GET_SVC_BY_UUID,
    GATT_OP_GET_ALL_CHAR,
    GATT_OP_GET_ALL_DESCRI,
    GATT_OP_GET_CHAR_BY_UUID,
    GATT_OP_GET_DESCRI_BY_UUID,
    GATT_OP_GET_DESCRI_BY_HANDLE,
    GATT_OP_GET_INCLUDE_SVC,
}bt_gatt_get_db_op_t;

typedef struct {
    bt_gatt_db_attribute_type_t type;
    UINT16                      attribute_handle;
    UINT16                      start_handle;
    UINT16                      end_handle;
    UINT16                      id;
    UINT8                       properties;
    bt_uuid_t                   uuid;
}btgatt_db_element_t;

/*****************************************************************************
**  常量和数据类型
*****************************************************************************/
/**************************
**  通用定义
***************************/
/* GATT ID */
typedef struct {
    tBT_UUID    uuid;           /* 属性的uuid*/
    UINT8       inst_id;        /* 实例ID*/
} __attribute__((packed)) tBTA_GATT_ID;

/* 与ESP_GATT_def中的ESP_GATT_xxx相关。小时*/
/* 成功代码和错误代码*/
#define  BTA_GATT_OK                        GATT_SUCCESS
#define  BTA_GATT_INVALID_HANDLE            GATT_INVALID_HANDLE                /* 0x0001号*/
#define  BTA_GATT_READ_NOT_PERMIT           GATT_READ_NOT_PERMIT               /* 0x0002年*/
#define  BTA_GATT_WRITE_NOT_PERMIT          GATT_WRITE_NOT_PERMIT              /* 2002年03月*/
#define  BTA_GATT_INVALID_PDU               GATT_INVALID_PDU                   /* 0x0004年*/
#define  BTA_GATT_INSUF_AUTHENTICATION      GATT_INSUF_AUTHENTICATION          /* 0x0005年*/
#define  BTA_GATT_REQ_NOT_SUPPORTED         GATT_REQ_NOT_SUPPORTED             /* 2006年9月*/
#define  BTA_GATT_INVALID_OFFSET            GATT_INVALID_OFFSET                /* 2007年9月*/
#define  BTA_GATT_INSUF_AUTHORIZATION       GATT_INSUF_AUTHORIZATION           /* 2008年9月*/
#define  BTA_GATT_PREPARE_Q_FULL            GATT_PREPARE_Q_FULL                /* 2009年9月*/
#define  BTA_GATT_NOT_FOUND                 GATT_NOT_FOUND                     /* 0x000a*/
#define  BTA_GATT_NOT_LONG                  GATT_NOT_LONG                      /* 0x000b*/
#define  BTA_GATT_INSUF_KEY_SIZE            GATT_INSUF_KEY_SIZE                /* 0x000c*/
#define  BTA_GATT_INVALID_ATTR_LEN          GATT_INVALID_ATTR_LEN              /* 0x000d*/
#define  BTA_GATT_ERR_UNLIKELY              GATT_ERR_UNLIKELY                  /* 0x000e*/
#define  BTA_GATT_INSUF_ENCRYPTION          GATT_INSUF_ENCRYPTION              /* 0x000f*/
#define  BTA_GATT_UNSUPPORT_GRP_TYPE        GATT_UNSUPPORT_GRP_TYPE            /* 0x0010位*/
#define  BTA_GATT_INSUF_RESOURCE            GATT_INSUF_RESOURCE                /* 0x0011年*/


#define  BTA_GATT_NO_RESOURCES              GATT_NO_RESOURCES                  /* 0x80像素*/
#define  BTA_GATT_INTERNAL_ERROR            GATT_INTERNAL_ERROR                /* 0秒81*/
#define  BTA_GATT_WRONG_STATE               GATT_WRONG_STATE                   /* 0秒82*/
#define  BTA_GATT_DB_FULL                   GATT_DB_FULL                       /* 0秒83*/
#define  BTA_GATT_BUSY                      GATT_BUSY                          /* 第84页*/
#define  BTA_GATT_ERROR                     GATT_ERROR                         /* 0至85*/
#define  BTA_GATT_CMD_STARTED               GATT_CMD_STARTED                   /* 第86页*/
#define  BTA_GATT_ILLEGAL_PARAMETER         GATT_ILLEGAL_PARAMETER             /* 第87页*/
#define  BTA_GATT_PENDING                   GATT_PENDING                       /* 0x88像素*/
#define  BTA_GATT_AUTH_FAIL                 GATT_AUTH_FAIL                     /* 第89页*/
#define  BTA_GATT_MORE                      GATT_MORE                          /* 0x8a*/
#define  BTA_GATT_INVALID_CFG               GATT_INVALID_CFG                   /* 0x8b*/
#define  BTA_GATT_SERVICE_STARTED           GATT_SERVICE_STARTED               /* 0x8厘米*/
#define  BTA_GATT_ENCRYPED_MITM             GATT_ENCRYPED_MITM                 /* GATT_SUCCESS */
#define  BTA_GATT_ENCRYPED_NO_MITM          GATT_ENCRYPED_NO_MITM              /* 0x8天*/
#define  BTA_GATT_NOT_ENCRYPTED             GATT_NOT_ENCRYPTED                 /* 0x8e*/
#define  BTA_GATT_CONGESTED                 GATT_CONGESTED                     /* 0x8英尺*/

#define  BTA_GATT_DUP_REG                   GATT_DUP_REG                       /* 0x90倍*/
#define  BTA_GATT_ALREADY_OPEN              GATT_ALREADY_OPEN                  /* 0秒91*/
#define  BTA_GATT_CANCEL                    GATT_CANCEL                        /* 0秒92*/

/* 0xE0~0xFC保留供将来使用*/
#define  BTA_GATT_STACK_RSP                 GATT_STACK_RSP                    /* 0xE0*/
#define  BTA_GATT_APP_RSP                   GATT_APP_RSP                      /* 0倍E1*/
//客户应用程序或堆栈错误导致的错误
#define  BTA_GATT_UNKNOWN_ERROR             GATT_UNKNOWN_ERROR                /* 0XEF */
                                             /* 0xE0~0xFC保留供将来使用*/
#define  BTA_GATT_CCC_CFG_ERR               GATT_CCC_CFG_ERR     /* 0xFD客户端特征配置描述符配置不正确*/
#define  BTA_GATT_PRC_IN_PROGRESS           GATT_PRC_IN_PROGRESS /* 0xFE过程已在进行中*/
#define  BTA_GATT_OUT_OF_RANGE              GATT_OUT_OF_RANGE    /* 0xFFAttribute值超出范围*/

typedef UINT8 tBTA_GATT_STATUS;

#define BTA_GATT_INVALID_CONN_ID   GATT_INVALID_CONN_ID


/* 客户端回调函数事件*/
#define BTA_GATTC_REG_EVT               0   /* GATT客户已注册。*/
#define BTA_GATTC_DEREG_EVT             1   /* GATT客户注销事件*/
#define BTA_GATTC_OPEN_EVT              2   /* GATTC打开请求状态事件*/
#define BTA_GATTC_READ_CHAR_EVT         3   /* GATT读取特征事件*/
#define BTA_GATTC_WRITE_CHAR_EVT        4   /* GATT写入特性或字符描述符事件*/
#define BTA_GATTC_CLOSE_EVT             5   /* GATTC关闭请求状态事件*/
#define BTA_GATTC_SEARCH_CMPL_EVT       6   /* GATT发现完成事件*/
#define BTA_GATTC_SEARCH_RES_EVT        7   /* GATT发现结果事件*/
#define BTA_GATTC_READ_DESCR_EVT        8   /* GATT读取特征描述符事件*/
#define BTA_GATTC_WRITE_DESCR_EVT       9   /* GATT写入特性描述符事件*/
#define BTA_GATTC_NOTIF_EVT             10  /* GATT属性通知事件*/
#define BTA_GATTC_PREP_WRITE_EVT        11  /* GATT准备写入事件*/
#define BTA_GATTC_EXEC_EVT              12  /* 执行写入完成事件*/
#define BTA_GATTC_ACL_EVT               13  /* ACL向上事件*/
#define BTA_GATTC_CANCEL_OPEN_EVT       14  /* 取消打开事件*/
#define BTA_GATTC_SRVC_CHG_EVT          15  /* 服务更改事件*/
#define BTA_GATTC_LISTEN_EVT            16  /* 侦听事件*/
#define BTA_GATTC_ENC_CMPL_CB_EVT       17  /* 加密完成回调事件*/
#define BTA_GATTC_CFG_MTU_EVT           18  /* 配置MTU完成事件*/
#define BTA_GATTC_ADV_DATA_EVT          19  /* ADV数据事件*/
#define BTA_GATTC_MULT_ADV_ENB_EVT      20  /* 启用多ADV事件*/
#define BTA_GATTC_MULT_ADV_UPD_EVT      21  /* 更新参数事件*/
#define BTA_GATTC_MULT_ADV_DATA_EVT     22  /* 多ADV数据事件*/
#define BTA_GATTC_MULT_ADV_DIS_EVT      23  /* 禁用多ADV事件*/
#define BTA_GATTC_CONGEST_EVT           24  /* 拥堵事件*/
#define BTA_GATTC_BTH_SCAN_ENB_EVT      25 /* 启用批扫描事件*/
#define BTA_GATTC_BTH_SCAN_CFG_EVT      26 /* 配置存储事件*/
#define BTA_GATTC_BTH_SCAN_RD_EVT       27 /* 批扫描报告读取事件*/
#define BTA_GATTC_BTH_SCAN_THR_EVT      28 /* 批量扫描阈值事件*/
#define BTA_GATTC_BTH_SCAN_PARAM_EVT    29 /* 批扫描参数事件*/
#define BTA_GATTC_BTH_SCAN_DIS_EVT      30 /* 禁用批扫描事件*/
#define BTA_GATTC_SCAN_FLT_CFG_EVT      31 /* 扫描筛选器配置事件*/
#define BTA_GATTC_SCAN_FLT_PARAM_EVT    32 /* 参数筛选器事件*/
#define BTA_GATTC_SCAN_FLT_STATUS_EVT   33 /* 筛选器状态事件*/
#define BTA_GATTC_ADV_VSC_EVT           34 /* ADV VSC事件*/
#define BTA_GATTC_CONNECT_EVT           35 /* GATTC CONNECT事件*/
#define BTA_GATTC_DISCONNECT_EVT        36 /* GATTC DISCONNECT事件*/
#define BTA_GATTC_READ_MULTIPLE_EVT     37 /* GATTC读取多个事件*/
#define BTA_GATTC_QUEUE_FULL_EVT        38 /* GATTC队列已满事件*/
#define BTA_GATTC_ASSOC_EVT             39 /* GATTC关联地址事件*/
#define BTA_GATTC_GET_ADDR_LIST_EVT     40 /* GATTC获取缓存事件中的地址列表*/
#define BTA_GATTC_DIS_SRVC_CMPL_EVT     41 /* GATTC发现服务完成*/

typedef UINT8 tBTA_GATTC_EVT;

typedef tGATT_IF tBTA_GATTC_IF;

typedef UINT8 tBTA_ADDR_TYPE;

typedef struct {
    UINT16              unit;       /* 如SIG定义的UUIUD*/
    UINT16              descr;      /* 作为SIG定义的UUID*/
    tGATT_FORMAT        format;
    INT8                exp;
    UINT8               name_spc;   /* 描述的名称空间*/
} tBTA_GATT_CHAR_PRES;

typedef struct {
    UINT16             interval;
    UINT16             latency;
    UINT16             timeout;
} tBTA_GATT_CONN_PARAMS;

#define BTA_GATT_CLT_CONFIG_NONE               GATT_CLT_CONFIG_NONE         /* 00万*/
#define BTA_GATT_CLT_CONFIG_NOTIFICATION       GATT_CLT_CONFIG_NOTIFICATION /* 0x0001号*/
#define BTA_GATT_CLT_CONFIG_INDICATION         GATT_CLT_CONFIG_INDICATION   /* 0x0002年*/
typedef UINT16  tBTA_GATT_CLT_CHAR_CONFIG;

/* 特征描述符：服务器配置值
*/
#define BTA_GATT_SVR_CONFIG_NONE            GATT_SVR_CONFIG_NONE            /* 00万*/
#define BTA_GATT_SVR_CONFIG_BROADCAST       GATT_SVR_CONFIG_BROADCAST       /* 0x0001号*/
typedef UINT16  tBTA_GATT_SVR_CHAR_CONFIG;

/* 特征聚合格式属性值
*/
#define BTA_GATT_AGGR_HANDLE_NUM_MAX        10
typedef struct {
    UINT8                   num_handle;
    UINT16                  handle_list[BTA_GATT_AGGR_HANDLE_NUM_MAX];
} tBTA_GATT_CHAR_AGGRE;
typedef tGATT_VALID_RANGE           tBTA_GATT_VALID_RANGE;

typedef struct {
    UINT16  len;
    UINT8   *p_value;
} tBTA_GATT_UNFMT;

#define BTA_GATT_MAX_ATTR_LEN       GATT_MAX_ATTR_LEN

#define BTA_GATTC_TYPE_WRITE             GATT_WRITE
#define BTA_GATTC_TYPE_WRITE_NO_RSP      GATT_WRITE_NO_RSP
typedef UINT8 tBTA_GATTC_WRITE_TYPE;

/* 与ESP_GATT_defs中的ESP_GATT_CONN_xxx相关。小时*/
#define BTA_GATT_CONN_UNKNOWN                   0
#define BTA_GATT_CONN_L2C_FAILURE               GATT_CONN_L2C_FAILURE         /* 一般l2cap资源故障*/
#define BTA_GATT_CONN_TIMEOUT                   GATT_CONN_TIMEOUT             /* 0x08连接超时*/
#define BTA_GATT_CONN_TERMINATE_PEER_USER       GATT_CONN_TERMINATE_PEER_USER /* 0x13连接由对等用户终止*/
#define BTA_GATT_CONN_TERMINATE_LOCAL_HOST      GATT_CONN_TERMINATE_LOCAL_HOST/* 0x16连接被本地主机终止*/
#define BTA_GATT_CONN_FAIL_ESTABLISH            GATT_CONN_FAIL_ESTABLISH      /* 0x03E连接无法建立*/
#define BTA_GATT_CONN_LMP_TIMEOUT               GATT_CONN_LMP_TIMEOUT          /* LMP响应tout的0x22连接失败*/
#define BTA_GATT_CONN_CANCEL                    GATT_CONN_CANCEL               /* 0x0100 L2CAP连接已取消*/
#define BTA_GATT_CONN_NONE                      0x0101                          /* 0x0101没有要取消的连接*/
typedef UINT16 tBTA_GATT_REASON;

typedef struct {
    tBTA_GATT_ID        id;
    BOOLEAN             is_primary;
} tBTA_GATT_SRVC_ID;


#define BTA_GATTC_MULTI_MAX    GATT_MAX_READ_MULTI_HANDLES

typedef struct {
    UINT8                       num_attr;
    UINT16                      handles[BTA_GATTC_MULTI_MAX];
}tBTA_GATTC_MULTI;

/* 与ESP_GATT_def中的ESP_GATT_xxx相关。小时*/
#define BTA_GATT_AUTH_REQ_NONE           GATT_AUTH_REQ_NONE
#define BTA_GATT_AUTH_REQ_NO_MITM        GATT_AUTH_REQ_NO_MITM            /* 未经身份验证的加密*/
#define BTA_GATT_AUTH_REQ_MITM           GATT_AUTH_REQ_MITM               /* 经过身份验证的加密*/
#define BTA_GATT_AUTH_REQ_SIGNED_NO_MITM GATT_AUTH_REQ_SIGNED_NO_MITM
#define BTA_GATT_AUTH_REQ_SIGNED_MITM    GATT_AUTH_REQ_SIGNED_MITM

typedef tGATT_AUTH_REQ tBTA_GATT_AUTH_REQ;

enum {
    BTA_GATTC_ATTR_TYPE_INCL_SRVC,
    BTA_GATTC_ATTR_TYPE_CHAR,
    BTA_GATTC_ATTR_TYPE_CHAR_DESCR,
    BTA_GATTC_ATTR_TYPE_SRVC
};
typedef UINT8 tBTA_GATTC_ATTR_TYPE;


typedef struct {
    tBT_UUID    uuid;
    UINT16      s_handle;
    UINT16      e_handle;   /* 仅用于维修*/
    UINT8       attr_type;
    UINT8       id;
    UINT8       prop;       /* 当属性类型为特征时使用*/
    BOOLEAN     is_primary; /* 当属性类型为服务时使用*/
    UINT16      incl_srvc_s_handle; /* 当属性类型包含服务时使用*/
    UINT16      incl_srvc_e_handle; /* 当属性类型包含服务时使用*/
}tBTA_GATTC_NV_ATTR;

/* 回调数据结构*/
typedef struct {
    tBTA_GATT_STATUS    status;
    tBTA_GATTC_IF       client_if;
    tBT_UUID            app_uuid;
}tBTA_GATTC_REG;

typedef struct {
    UINT16              conn_id;
    tBTA_GATT_STATUS    status;
    UINT16              handle;
    tBTA_GATT_UNFMT  *p_value;
}tBTA_GATTC_READ;

typedef struct {
    UINT16              conn_id;
    tBTA_GATT_STATUS    status;
    UINT16              handle;
    UINT16              offset;
}tBTA_GATTC_WRITE;

typedef struct {
    UINT16              conn_id;
    tBTA_GATT_STATUS    status;
} tBTA_GATTC_EXEC_CMPL;

typedef struct {
    UINT16              conn_id;
    tBTA_GATT_STATUS    status;
    UINT8               searched_service_source;
} tBTA_GATTC_SEARCH_CMPL;

typedef struct {
    UINT16              conn_id;
    tBTA_GATT_STATUS    status;
}tBTA_GATTC_DIS_CMPL;

typedef struct {
    UINT16              conn_id;
    UINT16              start_handle;
    UINT16              end_handle;
    tBTA_GATT_ID        service_uuid;
    bool                is_primary;
}tBTA_GATTC_SRVC_RES;

typedef struct {
    UINT16              conn_id;
    tBTA_GATT_STATUS    status;
    UINT16              mtu;
} tBTA_GATTC_CFG_MTU;

typedef struct {
    tBTA_GATT_STATUS    status;
    UINT16              conn_id;
    tBTA_GATTC_IF       client_if;
    BD_ADDR             remote_bda;
    tBTA_TRANSPORT      transport;
    UINT16              mtu;
} tBTA_GATTC_OPEN;

typedef struct {
    tBTA_GATT_STATUS    status;
    UINT16              conn_id;
    tBTA_GATTC_IF       client_if;
    BD_ADDR             remote_bda;
    tBTA_GATT_REASON    reason;         /* 断开原因代码，在报告连接事件时不有用*/
} tBTA_GATTC_CLOSE;

typedef struct {
    UINT16              conn_id;
    BD_ADDR             bda;
    UINT16              handle;
    UINT16              len;
    UINT8               value[BTA_GATT_MAX_ATTR_LEN];
    BOOLEAN             is_notify;
} tBTA_GATTC_NOTIFY;

typedef struct {
    UINT16 conn_id;
    BOOLEAN congested; /* 拥挤指示器*/
} tBTA_GATTC_CONGEST;

typedef struct {
    tBTA_GATT_STATUS status;
    UINT16 conn_id;
    BOOLEAN is_full;
} tBTA_GATTC_QUEUE_FULL;

typedef struct {
    tBTA_GATT_STATUS   status;
    tBTA_GATTC_IF      client_if;
} tBTA_GATTC_SET_ASSOC;

typedef struct {
    tBTA_GATT_STATUS    status;
    tBTA_GATTC_IF       client_if;
    UINT8               num_addr;
    BD_ADDR             *bda_list;
} tBTA_GATTC_GET_ADDR_LIST;

typedef struct {
    tBTA_GATT_STATUS        status;
    tBTA_GATTC_IF           client_if;
    UINT16                  conn_id;
    BD_ADDR                 remote_bda;
} tBTA_GATTC_OPEN_CLOSE;

typedef struct {
    tBTA_GATTC_IF           client_if;
    BD_ADDR                 remote_bda;
} tBTA_GATTC_ENC_CMPL_CB;

typedef struct {
    UINT16              conn_id;
    UINT8               link_role;
    tBTA_GATTC_IF       client_if;
    BD_ADDR             remote_bda;
    tBTA_GATT_CONN_PARAMS conn_params;
} tBTA_GATTC_CONNECT;

typedef struct {
    tGATT_DISCONN_REASON reason;
    UINT16              conn_id;
    tBTA_GATTC_IF       client_if;
    BD_ADDR             remote_bda;
} tBTA_GATTC_DISCONNECT;

typedef struct {
    UINT16              conn_id;
    BD_ADDR             remote_bda;
} tBTA_GATTC_SERVICE_CHANGE;

typedef union {
    tBTA_GATT_STATUS        status;
    tBTA_GATTC_DIS_CMPL     dis_cmpl;    /* 发现完成*/
    tBTA_GATTC_SEARCH_CMPL  search_cmpl;    /* 搜索完成*/
    tBTA_GATTC_SRVC_RES     srvc_res;       /* 发现结果*/
    tBTA_GATTC_REG          reg_oper;       /* 登记数据*/
    tBTA_GATTC_OPEN         open;
    tBTA_GATTC_CONNECT      connect;
    tBTA_GATTC_CLOSE        close;
    tBTA_GATTC_DISCONNECT   disconnect;
    tBTA_GATTC_READ         read;           /* 读取属性/描述符数据*/
    tBTA_GATTC_WRITE        write;          /* 写入完整数据*/
    tBTA_GATTC_EXEC_CMPL    exec_cmpl;      /*  执行完毕*/
    tBTA_GATTC_NOTIFY       notify;         /* 通知/指示事件数据*/
    tBTA_GATTC_ENC_CMPL_CB  enc_cmpl;
    tBTA_GATTC_CFG_MTU      cfg_mtu;        /* 配置MTU操作*/
    tBTA_GATTC_CONGEST      congest;
    tBTA_GATTC_QUEUE_FULL   queue_full;
    tBTA_GATTC_SERVICE_CHANGE srvc_chg;     /* 服务更改事件*/
    tBTA_GATTC_SET_ASSOC    set_assoc;
    tBTA_GATTC_GET_ADDR_LIST get_addr_list;
} tBTA_GATTC;

/* GATTC启用回调函数*/
typedef void (tBTA_GATTC_ENB_CBACK)(tBTA_GATT_STATUS status);

/* 客户端回调函数*/
typedef void (tBTA_GATTC_CBACK)(tBTA_GATTC_EVT event, tBTA_GATTC *p_data);

/* GATT服务器数据结构*/
/* 服务器回调函数事件*/
#define BTA_GATTS_REG_EVT                               0
#define BTA_GATTS_READ_EVT                              GATTS_REQ_TYPE_READ         /* 1 */
#define BTA_GATTS_WRITE_EVT                             GATTS_REQ_TYPE_WRITE        /* 2 */
#define BTA_GATTS_EXEC_WRITE_EVT                        GATTS_REQ_TYPE_WRITE_EXEC   /* 3 */
#define BTA_GATTS_MTU_EVT                               GATTS_REQ_TYPE_MTU          /* 4 */
#define BTA_GATTS_CONF_EVT                              GATTS_REQ_TYPE_CONF         /* 5 */
#define BTA_GATTS_DEREG_EVT                             6
#define BTA_GATTS_CREATE_EVT                            7
#define BTA_GATTS_ADD_INCL_SRVC_EVT                     8
#define BTA_GATTS_ADD_CHAR_EVT                          9
#define BTA_GATTS_ADD_CHAR_DESCR_EVT                    10
#define BTA_GATTS_DELELTE_EVT                           11
#define BTA_GATTS_START_EVT                             12
#define BTA_GATTS_STOP_EVT                              13
#define BTA_GATTS_CONNECT_EVT                           14
#define BTA_GATTS_DISCONNECT_EVT                        15
#define BTA_GATTS_OPEN_EVT                              16
#define BTA_GATTS_CANCEL_OPEN_EVT                       17
#define BTA_GATTS_CLOSE_EVT                             18
#define BTA_GATTS_LISTEN_EVT                            19
#define BTA_GATTS_CONGEST_EVT                           20
#define BTA_GATTS_SET_ATTR_VAL_EVT                      23
#define BTA_GATTS_SEND_SERVICE_CHANGE_EVT               24

typedef UINT8  tBTA_GATTS_EVT;
typedef tGATT_IF tBTA_GATTS_IF;

/* 属性权限
*/
#define BTA_GATT_PERM_READ              GATT_PERM_READ              /* 位0-0x0001*/
#define BTA_GATT_PERM_READ_ENCRYPTED    GATT_PERM_READ_ENCRYPTED    /* 位1-0x0002*/
#define BTA_GATT_PERM_READ_ENC_MITM     GATT_PERM_READ_ENC_MITM     /* 位2-0x0004*/
#define BTA_GATT_PERM_WRITE             GATT_PERM_WRITE             /* 位4-0x0010*/
#define BTA_GATT_PERM_WRITE_ENCRYPTED   GATT_PERM_WRITE_ENCRYPTED   /* 位5-0x0020*/
#define BTA_GATT_PERM_WRITE_ENC_MITM    GATT_PERM_WRITE_ENC_MITM    /* 位6-0x0040*/
#define BTA_GATT_PERM_WRITE_SIGNED      GATT_PERM_WRITE_SIGNED      /* 位7-0x0080*/
#define BTA_GATT_PERM_WRITE_SIGNED_MITM GATT_PERM_WRITE_SIGNED_MITM /* 位8-0x0100*/
#define BTA_GATT_PERM_READ_AUTHORIZATION GATT_PERM_READ_AUTHORIZATION /* 位9-0x0200*/
#define BTA_GATT_PERM_WRITE_AUTHORIZATION GATT_PERM_WRITE_AUTHORIZATION /* 位10-0x0400*/
typedef UINT16 tBTA_GATT_PERM;
typedef tGATT_ATTR_VAL tBTA_GATT_ATTR_VAL;
typedef tGATTS_ATTR_CONTROL tBTA_GATTS_ATTR_CONTROL;

#define BTA_GATTS_INVALID_APP   0xff

#define BTA_GATTS_INVALID_IF    0

/* 特征特性的定义*/
#define BTA_GATT_CHAR_PROP_BIT_BROADCAST        GATT_CHAR_PROP_BIT_BROADCAST    /* 0x01*/
#define BTA_GATT_CHAR_PROP_BIT_READ             GATT_CHAR_PROP_BIT_READ         /* 0x02*/
#define BTA_GATT_CHAR_PROP_BIT_WRITE_NR         GATT_CHAR_PROP_BIT_WRITE_NR     /* 0x04*/
#define BTA_GATT_CHAR_PROP_BIT_WRITE            GATT_CHAR_PROP_BIT_WRITE        /* 0x08*/
#define BTA_GATT_CHAR_PROP_BIT_NOTIFY           GATT_CHAR_PROP_BIT_NOTIFY       /* 0x10像素*/
#define BTA_GATT_CHAR_PROP_BIT_INDICATE         GATT_CHAR_PROP_BIT_INDICATE     /* 20倍*/
#define BTA_GATT_CHAR_PROP_BIT_AUTH             GATT_CHAR_PROP_BIT_AUTH         /* 0x40倍*/
#define BTA_GATT_CHAR_PROP_BIT_EXT_PROP         GATT_CHAR_PROP_BIT_EXT_PROP     /* 0x80像素*/
typedef UINT8 tBTA_GATT_CHAR_PROP;

#ifndef BTA_GATTC_CHAR_DESCR_MAX
#define BTA_GATTC_CHAR_DESCR_MAX        7
#endif

/***********************  NV回调数据定义**********************
*/
typedef struct {
    tBT_UUID app_uuid128;
    tBT_UUID svc_uuid;
    UINT16   svc_inst;
    UINT16   s_handle;
    UINT16   e_handle;
    BOOLEAN  is_primary;      /* 主要服务或次要服务*/
} tBTA_GATTS_HNDL_RANGE;

#define BTA_GATTS_SRV_CHG_CMD_ADD_CLIENT       GATTS_SRV_CHG_CMD_ADD_CLIENT
#define BTA_GATTS_SRV_CHG_CMD_UPDATE_CLIENT    GATTS_SRV_CHG_CMD_UPDATE_CLIENT
#define BTA_GATTS_SRV_CHG_CMD_REMOVE_CLIENT    GATTS_SRV_CHG_CMD_REMOVE_CLIENT
#define BTA_GATTS_SRV_CHG_CMD_READ_NUM_CLENTS  GATTS_SRV_CHG_CMD_READ_NUM_CLENTS
#define BTA_GATTS_SRV_CHG_CMD_READ_CLENT       GATTS_SRV_CHG_CMD_READ_CLENT
typedef tGATTS_SRV_CHG_CMD tBTA_GATTS_SRV_CHG_CMD;

typedef tGATTS_SRV_CHG     tBTA_GATTS_SRV_CHG;
typedef tGATTS_SRV_CHG_REQ tBTA_GATTS_SRV_CHG_REQ;
typedef tGATTS_SRV_CHG_RSP tBTA_GATTS_SRV_CHG_RSP;

#define BTA_GATT_TRANSPORT_LE           GATT_TRANSPORT_LE
#define BTA_GATT_TRANSPORT_BR_EDR       GATT_TRANSPORT_BR_EDR
#define BTA_GATT_TRANSPORT_LE_BR_EDR    GATT_TRANSPORT_LE_BR_EDR
typedef UINT8 tBTA_GATT_TRANSPORT;

/* 属性值*/
typedef tGATT_VALUE tBTA_GATT_VALUE;

/* 属性响应数据*/
typedef tGATTS_RSP tBTA_GATTS_RSP;

/* 与ESP_GATT_defs中的ESP_GATT_PREP_WRITE_xxx相关。小时*/
/* 来自客户端的属性请求数据*/
#define BTA_GATT_PREP_WRITE_CANCEL   0x00
#define BTA_GATT_PREP_WRITE_EXEC     0x01
typedef tGATT_EXEC_FLAG tBTA_GATT_EXEC_FLAG;

/* 读取请求始终基于UUID*/
typedef tGATT_READ_REQ tBTA_GATT_READ_REQ;

/* 写入请求数据*/
typedef tGATT_WRITE_REQ tBTA_GATT_WRITE_REQ;

/* 客户端服务器访问请求的回调数据*/
typedef tGATTS_DATA tBTA_GATTS_REQ_DATA;

typedef struct {
    tBTA_GATT_STATUS    status;
    BD_ADDR             remote_bda;
    UINT32              trans_id;
    UINT16              conn_id;
    UINT16              handle;
    tBTA_GATTS_REQ_DATA *p_data;
    UINT16  data_len;
    UINT8   *value;
} tBTA_GATTS_REQ;

typedef struct {
    tBTA_GATTS_IF       server_if;
    tBTA_GATT_STATUS    status;
    tBT_UUID            uuid;
}tBTA_GATTS_REG_OPER;


typedef struct {
    tBTA_GATTS_IF       server_if;
    UINT16              service_id;
    UINT16              svc_instance;
    BOOLEAN             is_primary;
    tBTA_GATT_STATUS    status;
    tBT_UUID            uuid;
}tBTA_GATTS_CREATE;

typedef struct {
    tBTA_GATTS_IF       server_if;
    UINT16              service_id;
    UINT16              attr_id;
    tBTA_GATT_STATUS    status;
    tBT_UUID            char_uuid;
}tBTA_GATTS_ADD_RESULT;
typedef struct{
    tBTA_GATTS_IF       server_if;
    UINT16              service_id;
    UINT16              attr_id;
    tBTA_GATT_STATUS    status;
}tBAT_GATTS_ATTR_VAL_RESULT;

typedef struct {
    tBTA_GATTS_IF       server_if;
    UINT16              service_id;
    tBTA_GATT_STATUS    status;
} tBTA_GATTS_SRVC_OPER;


typedef struct {
    tBTA_GATTS_IF       server_if;
    BD_ADDR             remote_bda;
    UINT16              conn_id;
    UINT8               link_role;
    tBTA_GATT_REASON    reason; /* 报告断开原因*/
    tBTA_GATT_TRANSPORT transport;
    tBTA_GATT_CONN_PARAMS conn_params;
} tBTA_GATTS_CONN;

typedef struct {
    UINT16 conn_id;
    BOOLEAN congested; /* 报告信道拥塞指示符*/
} tBTA_GATTS_CONGEST;

typedef struct {
    UINT16 conn_id; /* 连接ID*/
    tBTA_GATT_STATUS status; /* 通知/指示状态*/
} tBTA_GATTS_CONF;

typedef struct {
    tBTA_GATT_STATUS    status;
    UINT16              conn_id;    /* 连接ID*/
} tBTA_GATTS_CLOSE;

typedef struct {
    tBTA_GATT_STATUS    status;
    tBTA_GATTS_IF       server_if;
} tBTA_GATTS_SERVICE_CHANGE;

typedef struct {
    tBTA_GATT_STATUS    status;
    tBTA_GATTS_IF       server_if;
} tBTA_GATTS_OPEN;

typedef struct {
    tBTA_GATT_STATUS    status;
    tBTA_GATTS_IF       server_if;
} tBTA_GATTS_CANCEL_OPEN;
/* GATTS回调数据*/
typedef union {
    tBTA_GATTS_REG_OPER         reg_oper;
    tBTA_GATTS_CREATE           create;
    tBTA_GATTS_SRVC_OPER        srvc_oper;
    tBTA_GATT_STATUS            status;         /* BTA_GATTS_LISTEN_EVT */
    tBTA_GATTS_ADD_RESULT       add_result;     /* 添加包含的服务：BTA_GATTS_add_INCL_SRVC_EVT添加字符：BTA_GATTS_add_char_EVT添加字符描述符：BTA_GATTS_add-char_DESCR_EVT*/
    tBAT_GATTS_ATTR_VAL_RESULT  attr_val;
    tBTA_GATTS_REQ              req_data;
    tBTA_GATTS_CONN             conn;           /* BTA_GATTS_CONN_EVT */
    tBTA_GATTS_CONGEST          congest;        /* BTA_GATTS_CONGEST_EVT回调数据*/
    tBTA_GATTS_CONF             confirm;        /* BTA_GATTS_CONF_EVT回调数据*/
    tBTA_GATTS_CLOSE            close;          /* BTA_GATTS_CLOSE_EVT回调数据*/
    tBTA_GATTS_OPEN             open;           /* BTA_GATTS_OPEN_EVT回调数据*/
    tBTA_GATTS_CANCEL_OPEN      cancel_open;    /* tBTA_GATTS_CANCEL_OPEN回调数据*/
    tBTA_GATTS_SERVICE_CHANGE   service_change;

} tBTA_GATTS;

/* GATTC等待服务更改ccc计时器回调数据*/
typedef struct {
    UINT16 conn_id;
    BD_ADDR remote_bda;
    UINT8 count;
    UINT8 last_status;
}tBTA_GATTC_WAIT_CCC_TIMER;

/* GATTS启用回调函数*/
typedef void (tBTA_GATTS_ENB_CBACK)(tBTA_GATT_STATUS status);

/* 服务器回调函数*/
typedef void (tBTA_GATTS_CBACK)(tBTA_GATTS_EVT event,  tBTA_GATTS *p_data);
typedef struct
{
    tBT_UUID                uuid;
    BOOLEAN                 is_primary;
    UINT16                  handle;
    UINT16                  s_handle;
    UINT16                  e_handle;
    list_t                 *characteristics; /* tBTA_GATTC_CHARACTERISTIC列表*/
    list_t                 *included_svc; /* tBTA_GATTC_INCLUDED_SVC列表*/
} __attribute__((packed)) tBTA_GATTC_SERVICE;

typedef struct
{
    tBT_UUID                uuid;
    UINT16                  handle;
    tBTA_GATT_CHAR_PROP     properties;
    tBTA_GATTC_SERVICE     *service; /* 拥有服务*/
    list_t                 *descriptors; /* tBTA_GATTC_DESCRIPTOR列表*/
} __attribute__((packed)) tBTA_GATTC_CHARACTERISTIC;

typedef struct
{
    tBT_UUID                    uuid;
    UINT16                      handle;
    tBTA_GATTC_CHARACTERISTIC  *characteristic; /* 拥有特性*/
} __attribute__((packed)) tBTA_GATTC_DESCRIPTOR;

typedef struct
{
    tBT_UUID                uuid;
    UINT16                  handle;
    UINT16                  incl_srvc_s_handle;
    UINT16                  incl_srvc_e_handle;
    tBTA_GATTC_SERVICE     *owning_service; /* 拥有服务*/
    tBTA_GATTC_SERVICE     *included_service;
} __attribute__((packed)) tBTA_GATTC_INCLUDED_SVC;

/*****************************************************************************
**  外部函数声明
*****************************************************************************/

#ifdef __cplusplus
extern "C"
{
#endif

/**************************
**  客户端功能
***************************/

/*******************************************************************************
** 功能BTA_GATTC_Disable
**
** 说明调用此函数以禁用GATTC模块
**
** 参数无。
**
** 返回None
**
*******************************************************************************/
extern void BTA_GATTC_Disable(void);

/*******************************************************************************
** 函数BTA_GATTC_AppRegister
**
** 说明调用此函数以向BTA GATTC模块注册应用程序回调。
**
** 参数p_app_uuid-应用程序uuid p_client_cb-指向应用程序回调函数的指针。
**
** 返回None
**
*******************************************************************************/
extern void BTA_GATTC_AppRegister(tBT_UUID *p_app_uuid, tBTA_GATTC_CBACK *p_client_cb);

/*******************************************************************************
** 函数BTA_GATTC_AppDeregister
**
** 说明调用此函数以从BTA GATTC模块注销应用程序。
**
** 参数client_if-客户端接口标识符。
**
** 返回None
**
*******************************************************************************/
extern void BTA_GATTC_AppDeregister (tBTA_GATTC_IF client_if);

/*******************************************************************************
** 功能BTA_GATTC_Open
**
** 说明打开直接连接或添加后台自动连接bd地址
**
** 参数client_if:服务器接口。remote_bda：远程设备BD地址。remote_addr_type：远程设备BD地址类型。is_direct：直接连接或后台自动连接
**
** 返回void
**
*******************************************************************************/
extern void BTA_GATTC_Open(tBTA_GATTC_IF client_if, BD_ADDR remote_bda, tBTA_ADDR_TYPE remote_addr_type,
                    BOOLEAN is_direct, tBTA_GATT_TRANSPORT transport, BOOLEAN is_aux);

/*******************************************************************************
** 功能BTA_GATTC_CancelOpen
**
** 说明打开直接连接或添加后台自动连接bd地址
**
** 参数client_if:服务器接口。remote_bda：远程设备BD地址。is_direct：直接连接或后台自动连接
**
** 返回void
**
*******************************************************************************/
extern void BTA_GATTC_CancelOpen(tBTA_GATTC_IF client_if, BD_ADDR remote_bda, BOOLEAN is_direct);

/*******************************************************************************
** 功能BTA_GATTC_Close
**
** 说明关闭与GATT服务器的连接。
**
** 参数conn_id：要关闭的连接id。
**
** 返回void
**
*******************************************************************************/
extern void BTA_GATTC_Close(UINT16 conn_id);

/*******************************************************************************
** 函数BTA_GATTC_ServiceSearchRequest
**
** 描述调用此函数以请求GATT服务器上的GATT服务发现。此函数通过回调事件和服务搜索完成事件报告服务搜索结果。
**
** 参数conn_id:连接id p_srvc_uuid：服务应用程序感兴趣的uuid。如果为空，则查找所有服务。
**
** 返回None
**
*******************************************************************************/
extern void BTA_GATTC_ServiceSearchRequest(UINT16 conn_id, tBT_UUID *p_srvc_uuid);

/*******************************************************************************
** 函数BTA_GATTC_GetServices
**
** 描述调用此函数以查找给定服务器上的服务。
**
** 参数conn_id：标识服务器的连接id。
**
** 返回返回tBTA_GATTC_SERVICE的list_t或NULL。
**
*******************************************************************************/
extern const list_t* BTA_GATTC_GetServices(UINT16 conn_id);

/*******************************************************************************
** 函数BTA_GATTC_GetCharacteristic
**
** 描述调用此函数以查找给定服务器上的特征。
**
** 参数conn_id：标识服务器的连接id。控制柄：特征控制柄
**
** 返回指向tBTA_GATTC_CHARACTERISTIC或NULL的指针。
**
*******************************************************************************/
extern const tBTA_GATTC_CHARACTERISTIC* BTA_GATTC_GetCharacteristic(UINT16 conn_id, UINT16 handle);

/*******************************************************************************
** 函数BTA_GATTC_GetDescriptor
**
** 描述调用此函数以查找给定服务器上的特征。
**
** 参数conn_id：标识服务器的连接id。句柄：描述符句柄
**
** 返回指向tBTA_GATTC_DESCRIPTOR或NULL的指针。
**
*******************************************************************************/
extern const tBTA_GATTC_DESCRIPTOR* BTA_GATTC_GetDescriptor(UINT16 conn_id, UINT16 handle);

extern void BTA_GATTC_GetServiceWithUUID(UINT16 conn_id, tBT_UUID *svc_uuid,
                                         btgatt_db_element_t **db, UINT16 *count);

extern void BTA_GATTC_GetAllChar(UINT16 conn_id, UINT16 start_handle, UINT16 end_handle,
                                 btgatt_db_element_t **db, UINT16 *count);

extern void BTA_GATTC_GetAllDescriptor(UINT16 conn_id, UINT16 char_handle,
                                       btgatt_db_element_t **db, UINT16 *count);

extern void BTA_GATTC_GetCharByUUID(UINT16 conn_id, UINT16 start_handle, UINT16 end_handle, tBT_UUID char_uuid,
                                    btgatt_db_element_t **db, UINT16 *count);

extern void BTA_GATTC_GetDescrByUUID(UINT16 conn_id, uint16_t start_handle, uint16_t end_handle,
                                     tBT_UUID char_uuid, tBT_UUID descr_uuid,
                                     btgatt_db_element_t **db, UINT16 *count);

extern void BTA_GATTC_GetDescrByCharHandle(UINT16 conn_id, UINT16 char_handle, tBT_UUID descr_uuid,
                                           btgatt_db_element_t **db, UINT16 *count);

extern void BTA_GATTC_GetIncludeService(UINT16 conn_id, UINT16 start_handle, UINT16 end_handle,
                                        tBT_UUID *incl_uuid, btgatt_db_element_t **db, UINT16 *count);

extern void BTA_GATTC_GetDBSize(UINT16 conn_id, UINT16 start_handle, UINT16 end_handle, UINT16 *count);

extern void BTA_GATTC_GetDBSizeByType(UINT16 conn_id, bt_gatt_db_attribute_type_t type,
                                      UINT16 start_handle, UINT16 end_handle, UINT16 char_handle, UINT16 *count);

/*******************************************************************************
** 函数BTA_GATTC_GetGattDb
**
** 说明调用此函数以获取gatt db。
**
** 参数conn_id：标识服务器的连接id。db：将包含gattdb副本的输出参数。调用者负责释放它。count：数据库中的元素数。
**
*******************************************************************************/
extern void BTA_GATTC_GetGattDb(UINT16 conn_id, UINT16 start_handle, UINT16 end_handle,
                                btgatt_db_element_t **db, UINT16 *count);

/*******************************************************************************
** 函数BTA_GATTC_ReadCharacteristic
**
** 说明调用此函数以读取特征值
**
** 参数conn_id-connectino id handle-要读取的字符句柄。
**
** 返回None
**
*******************************************************************************/
void BTA_GATTC_ReadCharacteristic(UINT16 conn_id, UINT16 handle, tBTA_GATT_AUTH_REQ auth_req);

/*******************************************************************************
** 函数BTA_GATTC_Read_by_type
**
** 描述调用此函数以读取uuid的属性值
**
** 参数conn_id-连接id s_handle-启动句柄。e_handle-end hanle uuid-属性uuid。
**
** 返回None
**
*******************************************************************************/
void BTA_GATTC_Read_by_type(UINT16 conn_id, UINT16 s_handle,UINT16 e_handle, tBT_UUID *uuid, tBTA_GATT_AUTH_REQ auth_req);

/*******************************************************************************
** 函数BTA_GATTC_ReadCharDescr
**
** 描述调用此函数以读取描述符值。
**
** 参数conn_id-连接id句柄-要读取的描述符句柄。
**
** 返回None
**
*******************************************************************************/
void BTA_GATTC_ReadCharDescr (UINT16 conn_id, UINT16 handle, tBTA_GATT_AUTH_REQ auth_req);

/*******************************************************************************
** 函数BTA_GATTC_WriteCharValue
**
** 说明调用此函数以写入特征值。
**
** 参数conn_id-连接id句柄-要写入的特征句柄。write_type—写入类型。len：要写入的数据的长度。p_value-要写入的值。
**
** 返回None
**
*******************************************************************************/
void BTA_GATTC_WriteCharValue ( UINT16 conn_id,
                                UINT16 handle,
                                tBTA_GATTC_WRITE_TYPE  write_type,
                                UINT16 len,
                                UINT8 *p_value,
                                tBTA_GATT_AUTH_REQ auth_req);

/*******************************************************************************
** 函数BTA_GATTC_WriteCharDescr
**
** 描述调用此函数以写入描述符值。
**
** 参数conn_id-连接id句柄-要写入的描述符句柄。write_type—写入类型。p_value-要写入的值。
**
** 返回None
**
*******************************************************************************/
void BTA_GATTC_WriteCharDescr (UINT16 conn_id,
                               UINT16 handle,
                               tBTA_GATTC_WRITE_TYPE  write_type,
                               tBTA_GATT_UNFMT      *p_data,
                               tBTA_GATT_AUTH_REQ auth_req);

/*******************************************************************************
** 函数BTA_GATTC_SendIndConfirm
**
** 说明调用此函数以发送句柄值确认。
**
** 参数conn_id-连接id句柄-要确认的特征句柄。
**
** 返回None
**
*******************************************************************************/
extern void BTA_GATTC_SendIndConfirm (UINT16 conn_id, UINT16 handle);

/*******************************************************************************
** 函数BTA_GATTC_RegisterForNotifications
**
** 说明调用此函数以注册服务通知。
**
** 参数client_if-客户端接口。remote_bda—目标GATT服务器。手柄—GATT特性手柄。
**
** 如果注册成功，则返回OK，否则返回失败。
**
*******************************************************************************/
extern tBTA_GATT_STATUS BTA_GATTC_RegisterForNotifications (tBTA_GATTC_IF      client_if,
                                                            BD_ADDR            remote_bda,
                                                            UINT16             handle);

/*******************************************************************************
** 函数BTA_GATTC_DegistorForNotifications
**
** 说明调用此函数以取消注册服务通知。
**
** 参数client_if-客户端接口。remote_bda—目标GATT服务器。手柄—GATT特性手柄。
**
** 如果注销成功，则返回OK，否则返回失败。
**
*******************************************************************************/
extern tBTA_GATT_STATUS BTA_GATTC_DeregisterForNotifications (tBTA_GATTC_IF      client_if,
                                                              BD_ADDR            remote_bda,
                                                              UINT16             handle);

/*******************************************************************************
** 函数BTA_GATTC_PrepareWrite
**
** 说明调用此函数以准备写入特征值。
**
** 参数conn_id-连接id句柄-GATT特征句柄。offset—写入值的偏移量。len—要写入的数据的长度。p_value-要写入的值。
**
** 返回None
**
*******************************************************************************/
extern void BTA_GATTC_PrepareWrite  (UINT16 conn_id,
                                     UINT16 handle,
                                     UINT16 offset,
                                     UINT16 len,
                                     UINT8 *p_value,
                                     tBTA_GATT_AUTH_REQ auth_req);

/*******************************************************************************
** 函数BTA_GATTC_PrepareWriteCharDescr
**
** 描述调用此函数以准备写入特征描述符值。
**
** 参数conn_id-连接id p_char_descr_id-服务的GATT特征描述符id。offset—写入值的偏移量。len：要写入的数据的长度。p_value-要写入的值。
**
** 返回None
**
*******************************************************************************/
extern void BTA_GATTC_PrepareWriteCharDescr  (UINT16 conn_id,
                                              UINT16 handle,
                                              UINT16 offset,
                                              tBTA_GATT_UNFMT   *p_data,
                                              tBTA_GATT_AUTH_REQ auth_req);
/*******************************************************************************
** 函数BTA_GATTC_ExecuteWrite
**
** 说明调用此函数以执行写入准备写入序列。
**
** 参数conn_id-连接id is_execute-执行或取消。
**
** 返回None
**
*******************************************************************************/
extern void BTA_GATTC_ExecuteWrite  (UINT16 conn_id, BOOLEAN is_execute);

/*******************************************************************************
** 函数BTA_GATTC_ReadMultiple
**
** 描述调用此函数以读取多个特征或特征描述符。
**
** 参数conn_id-连接id p_read_multi-读取多个参数。
**
** 返回None
**
*******************************************************************************/
extern void BTA_GATTC_ReadMultiple(UINT16 conn_id, tBTA_GATTC_MULTI *p_read_multi,
                                   tBTA_GATT_AUTH_REQ auth_req);


/*******************************************************************************
** 功能BTA_GATTC_Refresh
**
** 说明刷新远程设备的服务器缓存
**
** 参数remote_bda：远程设备BD地址。erase_flash：从nvs闪存中删除缓存
**
** 返回void
**
*******************************************************************************/
extern void BTA_GATTC_Refresh(BD_ADDR remote_bda, bool erase_flash);

extern void BTA_GATTC_CacheAssoc(tBTA_GATTC_IF client_if, BD_ADDR src_addr, BD_ADDR assoc_addr, BOOLEAN is_assoc);

extern void BTA_GATTC_CacheGetAddrList(tBTA_GATTC_IF client_if);

/*******************************************************************************
** 功能BTA_GATTC_Clean
**
** 说明清理远程设备的服务器缓存
**
** 参数remote_bda：远程设备BD地址。
**
** 返回void
**
*******************************************************************************/
extern void BTA_GATTC_Clean(BD_ADDR remote_bda);

/*******************************************************************************
** 功能BTA_GATTC_Listen
**
** 说明启动播发以侦听连接请求。
**
** 参数client_if:服务器接口。start：开始或停止侦听连接remote_bda：远程设备BD地址，如果侦听所有设备，则使用NULL。
**
** 返回void
**
*******************************************************************************/
extern void BTA_GATTC_Listen(tBTA_GATTC_IF client_if, BOOLEAN start, BD_ADDR_PTR target_bda);

/*******************************************************************************
** 功能BTA_GATTC_Broadcast
**
** 说明开始广播（不可连接的广告）
**
** 参数client_if：客户端接口。start：开始或停止侦听连接
**
** 返回void
**
*******************************************************************************/
extern void BTA_GATTC_Broadcast(tBTA_GATTC_IF client_if, BOOLEAN start);


/*******************************************************************************
** 功能BTA_GATTC_ConfigureMTU
**
** 说明配置GATT通道中的MTU大小。每个连接只能执行一次。
**
** 参数conn_id：连接id。
**
** 返回void
**
*******************************************************************************/
extern void BTA_GATTC_ConfigureMTU (UINT16 conn_id);

/*******************************************************************************
**  BTA GATT服务器API
********************************************************************************/

/*******************************************************************************
** 功能BTA_GATTS_Init
**
** 说明调用此函数以初始化GATTS模块
**
** 参数无
**
** 返回None
**
*******************************************************************************/
extern void BTA_GATTS_Init(void);

/*******************************************************************************
** 功能BTA_GATTS_Disable
**
** 说明调用此函数以禁用GATTS模块
**
** 参数无。
**
** 返回None
**
*******************************************************************************/
extern void BTA_GATTS_Disable(void);

/*******************************************************************************
** 函数BTA_GATTS_AppRegister
**
** 说明调用此函数以向BTA GATTS模块注册应用程序回调。
**
** 参数p_app_uuid-应用程序uuid p_cback-指向应用程序回调函数的指针。
**
** 返回None
**
*******************************************************************************/
extern void BTA_GATTS_AppRegister(const tBT_UUID * p_app_uuid, tBTA_GATTS_CBACK *p_cback);


/*******************************************************************************
** 函数BTA_GATTS_AppDeregister
**
** 说明从BTA GATT服务器注销。
**
** 参数server_if:服务器接口
**
** 返回void
**
*******************************************************************************/
extern void BTA_GATTS_AppDeregister(tBTA_GATTS_IF server_if);

/*******************************************************************************
** 函数BTA_GATTS_CreateService
**
** 描述创建服务。服务创建完成后，将调用回调事件BTA_GATTS_CREATE_EVT，以向配置文件报告状态和服务ID。在将包含的服务和特征/描述符添加到服务中时，需要使用回调函数中获得的服务ID。
**
** 参数server_if:服务器接口。p_service_uuid：服务uuid。inst：此服务的实例ID号。num_handle：此服务所需的句柄数。is_primary：此服务是否为主要服务。
**
** 返回void
**
*******************************************************************************/
extern void BTA_GATTS_CreateService(tBTA_GATTS_IF server_if, const tBT_UUID * p_service_uuid,
                                    UINT8 inst, UINT16 num_handle, BOOLEAN is_primary);

/*******************************************************************************
** 函数BTA_GATTS_AddIncludeService
**
** 说明调用此函数以添加包含的服务。在包含服务之后，将向包含的服务ID报告回调事件BTA_GATTS_ADD_INCL_SRVC_EVT。
**
** 参数service_id：要向其中添加此包含服务的服务id。included_service_id：要包含的服务id。
**
** 返回void
**
*******************************************************************************/
extern void BTA_GATTS_AddIncludeService(UINT16 service_id, UINT16 included_service_id);

/*******************************************************************************
** 函数BTA_GATTS_AddCharacteristic
**
** 描述调用此函数将特性添加到服务中。
**
** 参数service_id：要向其中添加此包含服务的服务id。p_char_uuid：特征uuid。perm：特征值声明属性权限。特性：特性特性
**
** 返回None
**
*******************************************************************************/
extern void BTA_GATTS_AddCharacteristic (UINT16 service_id,  const tBT_UUID  * p_char_uuid,
                                  tBTA_GATT_PERM perm, tBTA_GATT_CHAR_PROP property, tGATT_ATTR_VAL *attr_val,
                                  tBTA_GATTS_ATTR_CONTROL *control);

/*******************************************************************************
** 函数BTA_GATTS_AddCharDescriptor
**
** 描述调用此函数以添加特征描述符。完成后，将调用回调事件BTA_GATTS_ADD_DESCR_EVT来报告此描述符的状态和ID号。
**
** 参数service_id：要向其添加此特征描述符的服务id。perm：描述符访问权限。p_descr_uid：描述符uuid。p_descr_params：如果是只读描述符，则为描述符值。
**
** 返回返回状态。
**
*******************************************************************************/
extern void BTA_GATTS_AddCharDescriptor (UINT16 service_id,
                                  tBTA_GATT_PERM perm,
                                  const tBT_UUID  * p_descr_uuid, tBTA_GATT_ATTR_VAL *attr_val,
                                  tBTA_GATTS_ATTR_CONTROL *control);

/*******************************************************************************
** 功能BTA_GATTS_DeleteService
**
** 说明此函数用于删除服务。完成此操作后，将报告带有状态的回调事件BTA_GATTS_DELETE_EVT。
**
** 参数service_id：要删除的service_id。
**
** 返回无返回。
**
*******************************************************************************/
extern void  BTA_GATTS_DeleteService(UINT16 service_id);

/*******************************************************************************
** 功能BTA_GATTS_StartService
**
** 说明调用此函数以启动服务。
**
** 参数service_id：要启动的服务id。sup_transport：支持的传输。
**
** 返回None。
**
*******************************************************************************/
extern void  BTA_GATTS_StartService(UINT16 service_id, tBTA_GATT_TRANSPORT sup_transport);

/*******************************************************************************
** 功能BTA_GATTS_StopService
**
** 说明调用此函数以停止服务。
**
** 参数service_id-要停止的服务。
**
** 返回None
**
*******************************************************************************/
extern void BTA_GATTS_StopService(UINT16 service_id);

/*******************************************************************************
** 函数BTA_GATTS_HandleValueIndication
**
** 描述调用此函数以读取特征描述符。
**
** 参数conn_id-连接标识符。attr_id-要指示的属性id。data_len-表示数据长度。p_data：要指示的数据。need_confirm-如果该指示是否需要确认。
**
** 返回None
**
*******************************************************************************/
extern void BTA_GATTS_HandleValueIndication (UINT16 conn_id, UINT16 attr_id,
                                             UINT16 data_len,
                                             UINT8 *p_data,
                                             BOOLEAN need_confirm);

/*******************************************************************************
** 函数BTA_GATTS_SendRsp
**
** 描述调用此函数以发送对请求的响应。
**
** 参数conn_id-连接标识符。trans_id-事务id状态-响应状态p_msg-响应数据。
**
** 返回None
**
*******************************************************************************/
extern void BTA_GATTS_SendRsp (UINT16 conn_id, UINT32 trans_id,
                               tBTA_GATT_STATUS status, tBTA_GATTS_RSP *p_msg);



/*******************************************************************************
** 函数BTA_SetAttributeValue
**
** 说明调用此函数以设置gatt数据库中的属性值
**
** 参数attr_handle-属性值句柄。length-已设置为属性的值长度。value-指向值的指针
**
** 返回None
**
*******************************************************************************/
extern void BTA_SetAttributeValue(UINT16 attr_handle, UINT16 length, UINT8 *value);


/*******************************************************************************
** 函数BTA_GetAttributeValue
**
** 描述调用此函数以获取gatt数据库中的属性值
**
** 参数attr_handle-属性值句柄。length-已设置为属性的值长度。value-指向值的指针
**
** 返回tBTA_GATT_STATUS
**
*******************************************************************************/
extern tBTA_GATT_STATUS BTA_GetAttributeValue(UINT16 attr_handle, UINT16 *length, UINT8 **value);

/*******************************************************************************
** 功能BTA_GATTS_Open
**
** 说明打开直接打开的连接或添加后台自动连接bd地址
**
** 参数server_if:服务器接口。remote_bda：远程设备BD地址。is_direct：直接连接或后台自动连接
**
** 返回void
**
*******************************************************************************/
extern void BTA_GATTS_Open(tBTA_GATTS_IF server_if, BD_ADDR remote_bda,
                           BOOLEAN is_direct, tBTA_GATT_TRANSPORT transport);


/*******************************************************************************
** 功能BTA_GATTS_CancelOpen
**
** 说明取消直接打开的连接或删除后台自动连接bd地址
**
** 参数server_if:服务器接口。remote_bda：远程设备BD地址。is_direct：直接连接或后台自动连接
**
** 返回void
**
*******************************************************************************/
extern void BTA_GATTS_CancelOpen(tBTA_GATTS_IF server_if, BD_ADDR remote_bda, BOOLEAN is_direct);


/*******************************************************************************
** 函数BTA_GATTS_Close
**
** 说明关闭远程设备的连接。
**
** 参数conn_id：要关闭的连接id。
**
** 返回void
**
*******************************************************************************/
extern void BTA_GATTS_Close(UINT16 conn_id);

/*******************************************************************************
** 函数BTA_GATTS_SendServiceChangeIndication
**
** 描述发送服务更改指示。
**
** 返回void
**
*******************************************************************************/

void BTA_GATTS_SendServiceChangeIndication(tBTA_GATTS_IF server_if, BD_ADDR remote_bda);

/*******************************************************************************
** 函数BTA_GATTS_Listen
**
** 说明启动播发以侦听GATT服务器的连接请求
**
** 参数server_if:服务器接口。start：开始或停止侦听连接remote_bda：远程设备BD地址，如果侦听所有设备，则使用NULL。
**
** 返回void
**
*******************************************************************************/
extern void BTA_GATTS_Listen(tBTA_GATTS_IF server_if, BOOLEAN start,
                             BD_ADDR_PTR target_bda);


#ifdef __cplusplus

}
#endif


#endif /* BTA_GATT_API_H */

