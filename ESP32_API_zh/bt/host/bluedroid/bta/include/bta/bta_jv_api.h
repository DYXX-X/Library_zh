/******************************************************************************
 * 版权所有（C）2006-2012 Broadcom Corporation
 *
 *  根据Apache许可证2.0版（“许可证”）获得许可；除非符合许可证，否则不得使用此文件。您可以在以下地址获取许可证副本：
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 *  除非适用法律要求或书面同意，否则根据许可证分发的软件是按“原样”分发的，无任何明示或暗示的担保或条件。有关许可证下权限和限制的具体语言，请参阅许可证。
 *
 ******************************************************************************/

/******************************************************************************
 * 这是BTA Java I/F的公共接口文件
 *
 ******************************************************************************/
#ifndef BTA_JV_API_H
#define BTA_JV_API_H

#include "common/bt_target.h"
#include "stack/bt_types.h"
#include "bta/bta_api.h"
#include "stack/btm_api.h"
#include "stack/l2c_api.h"
#include "stack/rfcdefs.h"
#include "stack/sdp_api.h"

#if (defined BTA_JV_INCLUDED && BTA_JV_INCLUDED == TRUE)
/*****************************************************************************
**  常量和数据类型
*****************************************************************************/
/* 状态值*/
#define BTA_JV_SUCCESS             0            /* 操作成功。*/
#define BTA_JV_FAILURE             1            /* 一般故障。*/
#define BTA_JV_BUSY                2            /* 暂时无法处理此请求。*/
#define BTA_JV_NO_DATA             3            /* 没有数据。*/
#define BTA_JV_NO_RESOURCE         4            /* 不再设置pm控制块*/

typedef UINT8 tBTA_JV_STATUS;
#define BTA_JV_INTERNAL_ERR        (-1) /* 内部错误。*/

#define BTA_JV_MAX_UUIDS        SDP_MAX_UUID_FILTERS
#define BTA_JV_MAX_ATTRS        SDP_MAX_ATTR_FILTERS
#define BTA_JV_MAX_SDP_REC      SDP_MAX_RECORDS
#define BTA_JV_MAX_L2C_CONN     GAP_MAX_CONNECTIONS /* GAP句柄用作索引，因此不要更改此值*/
#define BTA_JV_MAX_SCN          PORT_MAX_RFC_PORTS /* 与BTM_MAX_SCN相同（单位为BTM_int.h）*/
#define BTA_JV_MAX_RFC_CONN     MAX_RFC_PORTS

#ifndef BTA_JV_DEF_RFC_MTU
#define BTA_JV_DEF_RFC_MTU      (3*330)
#endif

#ifndef BTA_JV_MAX_RFC_SR_SESSION
#define BTA_JV_MAX_RFC_SR_SESSION   MAX_BD_CONNECTIONS
#endif

/* BTA_JV_MAX_RFC_SR_SESSION不能大于MAX_BD_CONNECTIONS*/
#if (BTA_JV_MAX_RFC_SR_SESSION > MAX_BD_CONNECTIONS)
#undef BTA_JV_MAX_RFC_SR_SESSION
#define BTA_JV_MAX_RFC_SR_SESSION   MAX_BD_CONNECTIONS
#endif

#define BTA_JV_FIRST_SERVICE_ID BTA_FIRST_JV_SERVICE_ID
#define BTA_JV_LAST_SERVICE_ID  BTA_LAST_JV_SERVICE_ID
#define BTA_JV_NUM_SERVICE_ID   (BTA_LAST_JV_SERVICE_ID - BTA_FIRST_JV_SERVICE_ID + 1)

/* 可发现的模式*/
enum {
    BTA_JV_DISC_NONE,
    BTA_JV_DISC_LIMITED,
    BTA_JV_DISC_GENERAL
};
typedef UINT16 tBTA_JV_DISC;

#define BTA_JV_ROLE_SLAVE       BTM_ROLE_SLAVE
#define BTA_JV_ROLE_MASTER      BTM_ROLE_MASTER
typedef UINT32 tBTA_JV_ROLE;

#define BTA_JV_SERVICE_LMTD_DISCOVER    BTM_COD_SERVICE_LMTD_DISCOVER   /* 0x0020位*/
#define BTA_JV_SERVICE_POSITIONING      BTM_COD_SERVICE_POSITIONING     /* 0x0100*/
#define BTA_JV_SERVICE_NETWORKING       BTM_COD_SERVICE_NETWORKING      /* 0x0200*/
#define BTA_JV_SERVICE_RENDERING        BTM_COD_SERVICE_RENDERING       /* 0x0400*/
#define BTA_JV_SERVICE_CAPTURING        BTM_COD_SERVICE_CAPTURING       /* 0x0800*/
#define BTA_JV_SERVICE_OBJ_TRANSFER     BTM_COD_SERVICE_OBJ_TRANSFER    /* 0x1000像素*/
#define BTA_JV_SERVICE_AUDIO            BTM_COD_SERVICE_AUDIO           /* 2000年*/
#define BTA_JV_SERVICE_TELEPHONY        BTM_COD_SERVICE_TELEPHONY       /* 0x4000个*/
#define BTA_JV_SERVICE_INFORMATION      BTM_COD_SERVICE_INFORMATION     /* 0x8000*/

/* 合资企业ID类型*/
#define BTA_JV_PM_ID_1             1    /* PM示例配置文件1*/
#define BTA_JV_PM_ID_2             2    /* PM示例配置文件2*/
#define BTA_JV_PM_ID_CLEAR         0    /* 用于清除PM配置文件的特殊JV ID*/
#define BTA_JV_PM_ALL              0xFF /* 通用匹配所有id，请参见bta_dm_cfg.c*/
typedef UINT8 tBTA_JV_PM_ID;

#define BTA_JV_PM_HANDLE_CLEAR     0xFF /* 用于清除PM配置文件的特殊JV ID*/

/* 定义注册PM实体的最大数量。应该与bta pm同步！*/
#ifndef BTA_JV_PM_MAX_NUM
#define BTA_JV_PM_MAX_NUM 5
#endif

/* JV pm连接状态*/
enum {
    BTA_JV_CONN_OPEN = 0,   /* 连接打开状态*/
    BTA_JV_CONN_CLOSE,      /* 连接关闭状态*/
    BTA_JV_APP_OPEN,        /* 合资企业申请打开状态*/
    BTA_JV_APP_CLOSE,       /* JV应用程序关闭状态*/
    BTA_JV_SCO_OPEN,        /* SCO连接打开状态*/
    BTA_JV_SCO_CLOSE,       /* SCO连接打开状态*/
    BTA_JV_CONN_IDLE,       /* 连接空闲状态*/
    BTA_JV_CONN_BUSY,       /* 连接忙状态*/
    BTA_JV_MAX_CONN_STATE   /* 最大连接状态数*/
};
typedef UINT8 tBTA_JV_CONN_STATE;

/* JV连接类型*/
#define BTA_JV_CONN_TYPE_RFCOMM    0
#define BTA_JV_CONN_TYPE_L2CAP     1
#define BTA_JV_CONN_TYPE_L2CAP_LE  2

/* Java I/F回调事件*/
/* tBTA_JV_DM_CBACK接收的事件*/
#define BTA_JV_ENABLE_EVT           0  /* 合资企业启用*/
#define BTA_JV_DISABLE_EVT          1  /* 合资企业已禁用*/
#define BTA_JV_GET_SCN_EVT          6  /* 保留SCN*/
#define BTA_JV_GET_PSM_EVT          7  /* 保留PSM*/
#define BTA_JV_DISCOVERY_COMP_EVT   8  /* SDP发现完成*/
#define BTA_JV_CREATE_RECORD_EVT    11 /* BTA_JvCreateRecord的结果*/

/* tBTA_JV_L2CAP_CBACK接收的事件*/
#if BTA_JV_L2CAP_INCLUDED
#define BTA_JV_L2CAP_OPEN_EVT       16 /* L2CAP连接的打开状态*/
#define BTA_JV_L2CAP_CLOSE_EVT      17 /* L2CAP连接已关闭*/
#define BTA_JV_L2CAP_START_EVT      18 /* L2CAP服务器已启动*/
#define BTA_JV_L2CAP_CL_INIT_EVT    19 /* L2CAP客户端启动了连接*/
#define BTA_JV_L2CAP_DATA_IND_EVT   20 /* L2CAP连接接收到数据*/
#define BTA_JV_L2CAP_CONG_EVT       21 /* L2CAP连接拥塞状态已更改*/
#define BTA_JV_L2CAP_READ_EVT       22 /* BTA_JvL2capRead的结果*/
#define BTA_JV_L2CAP_RECEIVE_EVT    23 /* BTA_JvL2capReceive的结果*/
#define BTA_JV_L2CAP_WRITE_EVT      24 /* BTA_JvL2capWrite的结果*/
#define BTA_JV_L2CAP_WRITE_FIXED_EVT 25 /* BTA_JvL2capWriteFixed的结果*/
#endif /* BTA_JV_L2CAP_INCLUDED */

/* tBTA_JV_RFCOMM_BACK接收的事件*/
#define BTA_JV_RFCOMM_OPEN_EVT      26 /* RFCOMM客户端连接的打开状态*/
#define BTA_JV_RFCOMM_CLOSE_EVT     27 /* RFCOMM连接已关闭*/
#define BTA_JV_RFCOMM_START_EVT     28 /* RFCOMM服务器已启动*/
#define BTA_JV_RFCOMM_CL_INIT_EVT   29 /* RFCOMM客户端启动了连接*/
#define BTA_JV_RFCOMM_DATA_IND_EVT  30 /* RFCOMM连接接收到数据*/
#define BTA_JV_RFCOMM_CONG_EVT      31 /* RFCOMM连接拥塞状态已更改*/
#define BTA_JV_RFCOMM_READ_EVT      32 /* BTA_JvRfcommRead的结果*/
#define BTA_JV_RFCOMM_WRITE_EVT     33 /* BTA_JvRfcommWrite的结果*/
#define BTA_JV_RFCOMM_SRV_OPEN_EVT  34 /* 服务器RFCOMM连接的打开状态*/
#define BTA_JV_FREE_SCN_EVT         35 /* 释放SCN*/
#define BTA_JV_MAX_EVT              36 /* 合资企业事件的最大数量*/

typedef UINT16 tBTA_JV_EVT;

/* 与BTA_JV_SET_DISCOVER_EVT相关的数据*/
typedef struct {
    tBTA_JV_STATUS  status;     /* 操作成功还是失败。*/
    tBTA_JV_DISC    disc_mode;  /* 当前可发现的模式*/
} tBTA_JV_SET_DISCOVER;

/* 与BTA_JV_DISCOVERY_COMP_EVT_相关的数据*/
typedef struct {
    tBTA_JV_STATUS status;                    /* 操作成功还是失败。*/
    UINT8 scn_num;                            /* 通道数*/
    UINT8 scn[BTA_JV_MAX_SCN];                /* 通道#*/
    const char *service_name[BTA_JV_MAX_SCN]; /* 服务名称*/
} tBTA_JV_DISCOVERY_COMP;

/* 与BTA_JV_CREATE_RECORD_EVT关联的数据*/
typedef struct {
    tBTA_JV_STATUS  status;     /* 操作成功还是失败。*/
    UINT32          handle;     /* SDP句柄*/
} tBTA_JV_CREATE_RECORD;

#if BTA_JV_L2CAP_INCLUDED
/* 与BTA_JV_L2CAP_OPEN_EVT相关的数据*/
typedef struct {
    tBTA_JV_STATUS  status;     /* 操作成功还是失败。*/
    UINT32          handle;     /* 连接手柄*/
    BD_ADDR         rem_bda;    /* 对等地址*/
    INT32           tx_mtu;     /* 发送MTU*/
} tBTA_JV_L2CAP_OPEN;

/* 与BTA_JV_L2CAP_CLOSE_EVT相关的数据*/
typedef struct {
    tBTA_JV_STATUS  status;     /* 操作成功还是失败。*/
    UINT32          handle;     /* 连接手柄*/
    BOOLEAN         async;      /* 如果本地启动断开连接，则返回FALSE*/
} tBTA_JV_L2CAP_CLOSE;

/* 与BTA_JV_L2CAP_START_EVT相关的数据*/
typedef struct {
    tBTA_JV_STATUS  status;     /* 操作成功还是失败。*/
    UINT32          handle;     /* 连接手柄*/
    UINT8           sec_id;     /* 此服务器使用的安全ID*/
} tBTA_JV_L2CAP_START;

/* 与BTA_JV_L2CAP_CL_INIT_EVT相关的数据*/
typedef struct {
    tBTA_JV_STATUS  status;     /* 操作成功还是失败。*/
    UINT32          handle;     /* 连接手柄*/
    UINT8           sec_id;     /* 此客户端使用的安全ID*/
} tBTA_JV_L2CAP_CL_INIT;

/* 与BTA_JV_L2CAP_CONG_EVT相关的数据*/
typedef struct {
    tBTA_JV_STATUS  status;     /* 操作成功还是失败。*/
    UINT32          handle;     /* 连接手柄*/
    BOOLEAN         cong;       /* 真的，拥挤。FALSE，未消化*/
} tBTA_JV_L2CAP_CONG;

/* 与BTA_JV_L2CAP_READ_EVT相关的数据*/
typedef struct {
    tBTA_JV_STATUS  status;     /* 操作成功还是失败。*/
    UINT32          handle;     /* 连接手柄*/
    UINT32          req_id;     /* 关联BTA_JvL2capRead（）中的req_id*/
    UINT8           *p_data;    /* 这与BTA_JvL2capRead（）中的p_data参数指向相同的位置*/
    UINT16          len;        /* 读取数据的长度。*/
} tBTA_JV_L2CAP_READ;

/* 与BTA_JV_L2CAP_RECEIVE_EVT关联的数据*/
typedef struct {
    tBTA_JV_STATUS  status;     /* 操作成功还是失败。*/
    UINT32          handle;     /* 连接手柄*/
    UINT32          req_id;     /* 关联BTA_JvL2capReceive（）中的req_id*/
    UINT8           *p_data;    /* 这与BTA_JvL2capReceive（）中的p_data参数指向相同的位置*/
    UINT16          len;        /* 读取数据的长度。*/
} tBTA_JV_L2CAP_RECEIVE;

/* 与BTA_JV_L2CAP_WRITE_EVT关联的数据*/
typedef struct {
    tBTA_JV_STATUS  status;     /* 操作成功还是失败。*/
    UINT32          handle;     /* 连接手柄*/
    UINT32          req_id;     /* 关联BTA_JvL2capWrite（）中的req_id*/
    UINT16          len;        /* 写入数据的长度。*/
    BOOLEAN         cong;       /* 拥挤状态*/
} tBTA_JV_L2CAP_WRITE;

/* 与LE套接字的BTA_JV_L2CAP_OPEN_EVT关联的数据*/
typedef struct {
    tBTA_JV_STATUS  status;     /* 操作成功还是失败。*/
    UINT32          handle;     /* 连接手柄*/
    BD_ADDR         rem_bda;    /* 对等地址*/
    INT32           tx_mtu;     /* 发送MTU*/
    void          **p_p_cback;  /* 为新插座设置它们*/
    void          **p_user_data;/* 为新插座设置它们*/

} tBTA_JV_L2CAP_LE_OPEN;

/*与BTA_JV_L2CAP_data_IND_EVT关联的数据（如果用于LE）*/
typedef struct {
    UINT32          handle;     /* 连接手柄*/
    BT_HDR         *p_buf;      /* 传入数据*/
} tBTA_JV_LE_DATA_IND;

/* 与BTA_JV_L2CAP_WRITE_FIXED_EVT相关的数据*/
typedef struct {
    tBTA_JV_STATUS  status;     /* 操作成功还是失败。*/
    UINT16          channel;    /* 连接通道*/
    BD_ADDR         addr;       /* 对等地址*/
    UINT32          req_id;     /* 关联BTA_JvL2capWrite（）中的req_id*/
    UINT16          len;        /* 写入数据的长度。*/
    BOOLEAN         cong;       /* 拥挤状态*/
} tBTA_JV_L2CAP_WRITE_FIXED;
#endif /* BTA_JV_L2CAP_INCLUDED */

/* 与BTA_JV_RFCOMM_OPEN_VT关联的数据*/
typedef struct {
    tBTA_JV_STATUS  status;     /* 操作成功还是失败。*/
    UINT32          handle;     /* 连接手柄*/
    BD_ADDR         rem_bda;    /* 对等地址*/
} tBTA_JV_RFCOMM_OPEN;

/* 与BTA_JV_RFCOMM_SRV_OPEN_VT关联的数据*/
typedef struct {
    tBTA_JV_STATUS  status;             /* 操作成功还是失败。*/
    UINT32          handle;             /* 连接手柄*/
    UINT32          new_listen_handle;  /* 新的侦听句柄*/
    BD_ADDR         rem_bda;            /* 对等地址*/
} tBTA_JV_RFCOMM_SRV_OPEN;

/* 与BTA_JV_RFCOMM_CLOSE_EVT关联的数据*/
typedef struct {
    tBTA_JV_STATUS  status;      /* 操作成功还是失败。*/
    UINT32          port_status; /* PORT状态*/
    UINT32          handle;      /* 连接手柄*/
    BOOLEAN         async;       /* 如果本地启动断开连接，则返回FALSE*/
    void *          user_data;   /* 携带呼叫者的私人数据*/
} tBTA_JV_RFCOMM_CLOSE;

/* 与BTA_JV_RFCOMM_START_VT关联的数据*/
typedef struct {
    tBTA_JV_STATUS  status;     /* 操作成功还是失败。*/
    UINT32          handle;     /* 连接手柄*/
    UINT8           sec_id;     /* 此服务器使用的安全ID*/
    UINT8           scn;        /* 服务器通道编号*/
    BOOLEAN         use_co;     /* TRUE使用corfc_data*/
} tBTA_JV_RFCOMM_START;

/* 与BTA_JV_RFCOMM_CL_INIT_EVT相关的数据*/
typedef struct {
    tBTA_JV_STATUS  status;     /* 操作成功还是失败。*/
    UINT32          handle;     /* 连接手柄*/
    UINT8           sec_id;     /* 此客户端使用的安全ID*/
    BOOLEAN         use_co;     /* TRUE使用corfc_data*/
} tBTA_JV_RFCOMM_CL_INIT;

/*与BTA_JV_L2CAP_data_IND_EVT和BTA_JV_RFCOMM_data_IND_EVT相关的数据*/
typedef struct {
    UINT32          handle;     /* 连接手柄*/
    BT_HDR         *p_buf;      /* 传入数据*/
} tBTA_JV_DATA_IND;

/* 与BTA_JV_RFCOMM_CONG_EVT相关的数据*/
typedef struct {
    tBTA_JV_STATUS  status;     /* 操作成功还是失败。*/
    UINT32          handle;     /* 连接手柄*/
    BOOLEAN         cong;       /* 真的，拥挤。FALSE，未消化*/
} tBTA_JV_RFCOMM_CONG;

/* 与BTA_JV_RFCOMM_READ_EVT相关的数据*/
typedef struct {
    tBTA_JV_STATUS  status;     /* 操作成功还是失败。*/
    UINT32          handle;     /* 连接手柄*/
    UINT32          req_id;     /* 关联BTA_JvRfcommRead（）中的req_id*/
    UINT8           *p_data;    /* 这与BTA_JvRfcommRead（）中的p_data参数指向相同的位置*/
    UINT16          len;        /* 读取数据的长度。*/
} tBTA_JV_RFCOMM_READ;

/* 与BTA_JV_RFCOMM_WRITE_EVT关联的数据*/
typedef struct {
    tBTA_JV_STATUS  status;     /* 操作成功还是失败。*/
    UINT32          handle;     /* 连接手柄*/
    UINT32          req_id;     /* 关联BTA_JvRfcommWrite（）中的req_id*/
    int             len;        /* 写入数据的长度。*/
    BOOLEAN         cong;       /* 拥挤状态*/
    BOOLEAN         old_cong;   /* 拥挤状态*/
} tBTA_JV_RFCOMM_WRITE;

/* 与BTA_JV_API_SET_PM_PROFILE_EVT关联的数据*/
typedef struct {
    tBTA_JV_STATUS  status;     /* 操作状态*/
    UINT32          handle;     /* 连接手柄*/
    tBTA_JV_PM_ID   app_id;      /* 合资企业应用程序ID*/
} tBTA_JV_SET_PM_PROFILE;

/* 与BTA_JV_API_NOTIFY_PM_STATE_CHANGE_EVT关联的数据*/
typedef struct {
    UINT32          handle;     /* 连接手柄*/
    tBTA_JV_CONN_STATE  state;  /* JV连接状态*/
} tBTA_JV_NOTIFY_PM_STATE_CHANGE;

/* 指示服务器的状态*/
typedef enum {
    BTA_JV_SERVER_START_FAILED,
    BTA_JV_SERVER_RUNNING,
    BTA_JV_SERVER_STATUS_MAX,
} tBTA_JV_SERVER_STATUS;

typedef struct {
    tBTA_JV_SERVER_STATUS   server_status;
    UINT32                  slot_id;
}tBTA_JV_FREE_SCN_USER_DATA;

/* 与BTA_JV_FREE_SCN_EVT相关的数据*/
typedef struct {
    tBTA_JV_STATUS          status;         /* 操作状态*/
    tBTA_JV_SERVER_STATUS   server_status;  /* 服务器状态*/
    UINT8                   scn;            /* 服务器通道编号*/
} tBTA_JV_FREE_SCN;


/* 与JV回调相关的数据联合*/
typedef union {
    tBTA_JV_STATUS          status;         /* BTA_JV_ENABLE_EVT */
    tBTA_JV_DISCOVERY_COMP  disc_comp;      /* BTA_JV_DISCOVERY_COMP_EVT */
    tBTA_JV_SET_DISCOVER    set_discover;   /* BTA_JV_SET_DISCOVER_EVT */
    UINT8                   scn;            /* BTA_JV_GET_SCN_EVT */
    UINT16                  psm;            /* BTA_JV_GET_PSM_EVT */
    tBTA_JV_CREATE_RECORD   create_rec;     /* BTA_JV_CREATE_RECORD_EVT */
#if BTA_JV_L2CAP_INCLUDED
    tBTA_JV_L2CAP_OPEN      l2c_open;       /* BTA_JV_L2CAP_OPEN_EVT */
    tBTA_JV_L2CAP_CLOSE     l2c_close;      /* BTA_JV_L2CAP_CLOSE_EVT */
    tBTA_JV_L2CAP_START     l2c_start;      /* BTA_JV_L2CAP_START_EVT */
    tBTA_JV_L2CAP_CL_INIT   l2c_cl_init;    /* BTA_JV_L2CAP_CL_INIT_EVT */
    tBTA_JV_L2CAP_CONG      l2c_cong;       /* BTA_JV_L2CAP_CONG_EVT */
    tBTA_JV_L2CAP_READ      l2c_read;       /* BTA_JV_L2CAP_READ_EVT */
    tBTA_JV_L2CAP_WRITE     l2c_write;      /* BTA_JV_L2CAP_WRITE_EVT */
#endif /* BTA_JV_L2CAP_INCLUDED */
    tBTA_JV_RFCOMM_OPEN     rfc_open;       /* BTA_JV_RFCOMM_OPEN_EVT */
    tBTA_JV_RFCOMM_SRV_OPEN rfc_srv_open;   /* BTA_JV_RFCOMM_SRV_OPEN_EVT */
    tBTA_JV_RFCOMM_CLOSE    rfc_close;      /* BTA_JV_RFCOMM_CLOSE_EVT */
    tBTA_JV_RFCOMM_START    rfc_start;      /* BTA_JV_RFCOMM_START_EVT */
    tBTA_JV_RFCOMM_CL_INIT  rfc_cl_init;    /* BTA_JV_RFCOMM_CL_INIT_EVT */
    tBTA_JV_RFCOMM_CONG     rfc_cong;       /* BTA_JV_RFCOMM_CONG_EVT */
    tBTA_JV_RFCOMM_READ     rfc_read;       /* BTA_JV_RFCOMM_READ_EVT */
    tBTA_JV_RFCOMM_WRITE    rfc_write;      /* BTA_JV_RFCOMM_WRITE_EVT */
    tBTA_JV_DATA_IND        data_ind;       /* BTA_JV_L2CAP_DATA_IND_EVT BTA_JV_RFCOMM_DATA_IND_EVT */
    tBTA_JV_FREE_SCN        free_scn;       /* BTA_JV_FREE_SCN_EVT */
#if BTA_JV_L2CAP_INCLUDED
    tBTA_JV_L2CAP_LE_OPEN      l2c_le_open;     /* BTA_JV_L2CAP_OPEN_EVT */
    tBTA_JV_LE_DATA_IND        le_data_ind;     /* BTA_JV_L2CAP_LE_DATA_IND_EVT */
    tBTA_JV_L2CAP_WRITE_FIXED  l2c_write_fixed; /* BTA_JV_L2CAP_WRITE_FIXED_EVT */
#endif /* BTA_JV_L2CAP_INCLUDED */
} tBTA_JV;

/* JAVA DM接口回调*/
typedef void (tBTA_JV_DM_CBACK)(tBTA_JV_EVT event, tBTA_JV *p_data, void *user_data);

/* JAVA RFCOMM接口回调*/
typedef void *(tBTA_JV_RFCOMM_CBACK)(tBTA_JV_EVT event, tBTA_JV *p_data, void *user_data);

#if BTA_JV_L2CAP_INCLUDED
/* JAVA L2CAP接口回调*/
typedef void (tBTA_JV_L2CAP_CBACK)(tBTA_JV_EVT event, tBTA_JV *p_data, void *user_Data);
#endif /* BTA_JV_L2CAP_INCLUDED */

/* 合资企业配置结构*/
typedef struct {
    UINT16  sdp_raw_size;           /* p_sdp_raw_data的大小*/
    UINT16  sdp_db_size;            /* p_sdp_db的大小*/
    UINT8   *p_sdp_raw_data;        /* 保存原始数据的数据缓冲区*/
    tSDP_DISCOVERY_DB   *p_sdp_db;  /* 保存SDP数据库的数据缓冲区*/
} tBTA_JV_CFG;

/*******************************************************************************
** 功能BTA_JvEnable
**
** 说明启用Java I/F服务。启用操作完成后，将使用BTA_JV_enable_EVT调用回调函数。必须在调用JV API中的其他函数之前调用此函数。
**
** 如果成功，则返回BTA_JV_SUCCESS。如果内部故障，则返回BTA_JV_FAIL。
**
*******************************************************************************/
extern tBTA_JV_STATUS BTA_JvEnable(tBTA_JV_DM_CBACK *p_cback);

/*******************************************************************************
** 功能BTA_JvDisable
**
** 说明禁用Java I/F。启用操作完成后，将使用BTA_JV_DISABLE_EVT调用回调函数。
**
** 返回void
**
*******************************************************************************/
extern void BTA_JvDisable(tBTA_JV_RFCOMM_CBACK *p_cback);

/*******************************************************************************
** 功能BTA_JvFree
**
** 说明无合资企业配置
**
** 返回void
**
*******************************************************************************/
extern void BTA_JvFree(void);

/*******************************************************************************
** 功能BTA_JvIsEnable
**
** 说明获取合资企业注册状态。
**
** 如果已注册，则返回TRUE
**
*******************************************************************************/
extern BOOLEAN BTA_JvIsEnable(void);

/*******************************************************************************
** 函数BTA_JvIsEncrypted
**
** 说明此功能检查到对等设备的链接是否已加密
**
** 如果加密，则返回TRUE。否则为FALSE。
**
*******************************************************************************/
extern BOOLEAN BTA_JvIsEncrypted(BD_ADDR bd_addr);

/*******************************************************************************
** 函数BTA_JvGetChannelId
**
** 说明此函数为在RFCOMM或L2CAP上运行的应用程序保留SCN/PSM。它主要由服务器配置文件/应用程序调用，以将其SCN/PSM注册到SDP数据库中。SCN由具有BTA_JV_GET_SCN_EVT的tBTA_JV_DM_CBACK回调报告。如果报告的SCN/PSM为0，则表示所有SCN资源均已耗尽。信道参数可用于请求特定信道。如果特定信道上的请求失败，EVT中返回的SCN/PSM将为0-不会尝试请求新信道。将通道设置为<=0以自动分配通道ID。
**
** 如果正在处理请求，则返回BTA_JV_SUCCESS。否则为BTA_JV_FAILURE。
**
*******************************************************************************/
extern tBTA_JV_STATUS BTA_JvGetChannelId(int conn_type, void *user_data,
        INT32 channel);

/*******************************************************************************
** 功能BTA_JvFreeChannel
**
** 说明此函数释放在RFCOMM或L2CAP上运行的应用程序使用的SCN/PSM。参数channel当服务器释放SCN/PSM用户数据时，使用BTA_JV_free_SCN_EVT调用BTA_JV_conn_type_p_cback tBTA_JV_RFCOMM_BACK中释放conn_type的通道
**
** 如果正在处理请求，则返回BTA_JV_SUCCESS。否则为BTA_JV_FAILURE。
**
*******************************************************************************/
extern tBTA_JV_STATUS BTA_JvFreeChannel(UINT16 channel, int conn_type, tBTA_JV_RFCOMM_CBACK *p_cback, void *user_data);

/*******************************************************************************
** 函数BTA_JvStartDiscovery
**
** 描述此功能为给定对等设备提供的服务执行服务发现。操作完成后，将使用BTA_JV_DISCOVERY_COMP_EVT调用tBTA_JV-DM_CBACK回调函数。
**
** 如果正在处理请求，则返回BTA_JV_SUCCESS。否则为BTA_JV_FAILURE。
**
*******************************************************************************/
extern tBTA_JV_STATUS BTA_JvStartDiscovery(BD_ADDR bd_addr, UINT16 num_uuid,
        tSDP_UUID *p_uuid_list, void *user_data);

/*******************************************************************************
** 函数BTA_JvCreateRecordByUser
**
** 说明用户在tBTA_JV_DM_CBACK回调中使用BTA_JV_Create_record_EVT在本地SDP数据库中创建服务记录。
**
** 如果正在处理请求，则返回BTA_JV_SUCCESS。否则为BTA_JV_FAILURE。
**
*******************************************************************************/
extern tBTA_JV_STATUS BTA_JvCreateRecordByUser(const char *name, UINT32 channel, void *user_data);

/*******************************************************************************
** 函数BTA_JvDeleteRecord
**
** 说明删除本地SDP数据库中的服务记录。
**
** 如果正在处理请求，则返回BTA_JV_SUCCESS。否则为BTA_JV_FAILURE。
**
*******************************************************************************/
extern tBTA_JV_STATUS BTA_JvDeleteRecord(UINT32 handle);

#if BTA_JV_L2CAP_INCLUDED
/*******************************************************************************
** 功能BTA_JvL2capConnectLE
**
** 说明作为LE L2CAP客户端启动到给定BD地址的连接。当连接启动或启动失败时，使用BTA_JV_L2CAP_CL_INIT_EVT调用tBTA_JV-L2CAP_CBACK当连接建立或失败时，用BTA_JV.L2CAP_OPEN_EVT调用tBTA-JV_L2CAP _CBACK
**
** 如果正在处理请求，则返回BTA_JV_SUCCESS。否则为BTA_JV_FAILURE。
**
*******************************************************************************/
extern tBTA_JV_STATUS BTA_JvL2capConnectLE(tBTA_SEC sec_mask, tBTA_JV_ROLE role,
        const tL2CAP_ERTM_INFO *ertm_info, UINT16 remote_chan,
        UINT16 rx_mtu, tL2CAP_CFG_INFO *cfg,
        BD_ADDR peer_bd_addr, tBTA_JV_L2CAP_CBACK *p_cback, void *user_data);

/*******************************************************************************
** 功能BTA_JvL2capConnect
**
** 描述作为L2CAP客户端启动到给定BD地址的连接。当连接启动或启动失败时，使用BTA_JV_L2CAP_CL_INIT_EVT调用tBTA_JV-L2CAP_CBACK当连接建立或失败时，用BTA_JV.L2CAP_OPEN_EVT调用tBTA-JV_L2CAP _CBACK
**
** 如果正在处理请求，则返回BTA_JV_SUCCESS。否则为BTA_JV_FAILURE。
**
*******************************************************************************/
extern tBTA_JV_STATUS BTA_JvL2capConnect(tBTA_SEC sec_mask, tBTA_JV_ROLE role,
        const tL2CAP_ERTM_INFO *ertm_info, UINT16 remote_psm,
        UINT16 rx_mtu, tL2CAP_CFG_INFO *cfg,
        BD_ADDR peer_bd_addr, tBTA_JV_L2CAP_CBACK *p_cback, void *user_data);

/*******************************************************************************
** 功能BTA_JvL2capClose
**
** 说明此函数关闭L2CAP客户端连接
**
** 如果正在处理请求，则返回BTA_JV_SUCCESS。否则为BTA_JV_FAILURE。
**
*******************************************************************************/
extern tBTA_JV_STATUS BTA_JvL2capClose(UINT32 handle);

/*******************************************************************************
** 功能BTA_JvL2capCloseLE
**
** 说明此函数关闭固定通道的L2CAP客户端连接。此函数是幂等的，不调用回调！
**
** 如果正在处理请求，则返回BTA_JV_SUCCESS。否则为BTA_JV_FAILURE。
**
*******************************************************************************/
extern tBTA_JV_STATUS BTA_JvL2capCloseLE(UINT32 handle);

/*******************************************************************************
** 功能BTA_JvL2capStartServer
**
** 说明此功能启动L2CAP服务器并侦听来自远程蓝牙设备的L2CAP连接。成功启动服务器后，使用BTA_JV_L2CAP_START_EVT调用tBTA_JV-L2CAP_CBACK。建立连接后，使用BTA_JV_L2CAP_OPEN_EVT调用tBTA_JV-L2CAP_CBACK。
**
** 如果正在处理请求，则返回BTA_JV_SUCCESS。否则为BTA_JV_FAILURE。
**
*******************************************************************************/
extern tBTA_JV_STATUS BTA_JvL2capStartServer(tBTA_SEC sec_mask, tBTA_JV_ROLE role,
        const tL2CAP_ERTM_INFO *ertm_info,
        UINT16 local_psm, UINT16 rx_mtu, tL2CAP_CFG_INFO *cfg,
        tBTA_JV_L2CAP_CBACK *p_cback, void *user_data);

/*******************************************************************************
** 函数BTA_JvL2capStartServerLE
**
** 说明此功能启动LE L2CAP服务器，并通过LE链路在固定信道上侦听来自远程蓝牙设备的L2CAP连接。成功启动服务器后，使用BTA_JV_L2CAP_START_EVT调用tBTA_JV-L2CAP_CBACK。建立连接后，使用BTA_JV_L2CAP_OPEN_EVT调用tBTA_JV-L2CAP_CBACK。
**
** 如果正在处理请求，则返回BTA_JV_SUCCESS。否则为BTA_JV_FAILURE。
**
*******************************************************************************/
extern tBTA_JV_STATUS BTA_JvL2capStartServerLE(tBTA_SEC sec_mask, tBTA_JV_ROLE role,
        const tL2CAP_ERTM_INFO *ertm_info,
        UINT16 local_chan, UINT16 rx_mtu, tL2CAP_CFG_INFO *cfg,
        tBTA_JV_L2CAP_CBACK *p_cback, void *user_data);

/*******************************************************************************
** 函数BTA_JvL2capStopServerLE
**
** 说明此功能可停止LE L2CAP服务器。如果服务器有一个活动连接，它将被关闭。
**
** 如果正在处理请求，则返回BTA_JV_SUCCESS。否则为BTA_JV_FAILURE。
**
*******************************************************************************/
extern tBTA_JV_STATUS BTA_JvL2capStopServerLE(UINT16 local_chan, void *user_data);

/*******************************************************************************
** 函数BTA_JvL2capStopServerLE
**
** 说明此功能可停止LE L2CAP服务器。如果服务器有一个活动连接，它将被关闭。
**
** 如果正在处理请求，则返回BTA_JV_SUCCESS。否则为BTA_JV_FAILURE。
**
*******************************************************************************/
extern tBTA_JV_STATUS BTA_JvL2capStopServer(UINT16 local_psm, void *user_data);

/*******************************************************************************
** 功能BTA_JvL2capRead
**
** 说明此函数从L2CAP连接读取数据当操作完成时，使用BTA_JV_L2CAP_READ_EVT调用tBTA_JV-L2CAP_CBACK。
**
** 如果正在处理请求，则返回BTA_JV_SUCCESS。否则为BTA_JV_FAILURE。
**
*******************************************************************************/
extern tBTA_JV_STATUS BTA_JvL2capRead(UINT32 handle, UINT32 req_id,
                                      UINT8 *p_data, UINT16 len);

/*******************************************************************************
** 功能BTA_JvL2capReceive
**
** 说明此函数从L2CAP连接读取数据当操作完成时，使用BTA_JV_L2CAP_RECEIVE_EVT调用tBTA_JV-L2CAP_CBACK。如果L2CAP中排队的数据多于len，则将丢弃多余的数据。
**
** 如果正在处理请求，则返回BTA_JV_SUCCESS。否则为BTA_JV_FAILURE。
**
*******************************************************************************/
extern tBTA_JV_STATUS BTA_JvL2capReceive(UINT32 handle, UINT32 req_id,
        UINT8 *p_data, UINT16 len);

/*******************************************************************************
** 功能BTA_JvL2capReady
**
** 说明此功能确定是否有数据要从L2CAP连接读取
**
** 如果数据队列大小为*p_data_size，则返回BTA_JV_SUCCESS。如果错误，则返回BTA_JV_FAILURE。
**
*******************************************************************************/
extern tBTA_JV_STATUS BTA_JvL2capReady(UINT32 handle, UINT32 *p_data_size);

/*******************************************************************************
** 函数BTA_JvL2capWrite
**
** 说明此函数将数据写入L2CAP连接当操作完成时，使用BTA_JV_L2CAP_WRITE_EVT调用tBTA_JV-L2CAP_CBACK。适用于基于PSM的连接
**
** 如果正在处理请求，则返回BTA_JV_SUCCESS。否则为BTA_JV_FAILURE。
**
*******************************************************************************/
extern tBTA_JV_STATUS BTA_JvL2capWrite(UINT32 handle, UINT32 req_id,
                                       UINT8 *p_data, UINT16 len, void *user_data);


/*******************************************************************************
** 函数BTA_JvL2capWriteFixed
**
** 说明此函数将数据写入L2CAP连接当操作完成时，使用BTA_JV_L2CAP_WRITE_FIXED_EVT调用tBTA_JV-L2CAP_CBACK。适用于固定通道连接
**
** 如果正在处理请求，则返回BTA_JV_SUCCESS。否则为BTA_JV_FAILURE。
**
*******************************************************************************/
extern tBTA_JV_STATUS BTA_JvL2capWriteFixed(UINT16 channel, BD_ADDR *addr, UINT32 req_id,
        tBTA_JV_L2CAP_CBACK *p_cback,
        UINT8 *p_data, UINT16 len, void *user_data);
#endif /* BTA_JV_L2CAP_INCLUDED */

/*******************************************************************************
** 功能BTA_JvRfcommConnect
**
** 说明此函数将RFCOMM连接到远程BD地址。当连接启动或启动失败时，使用BTA_JV_RFCOMM_CL_INIT_EVT调用tBTA_JV-RFCOMM_BACK当连接建立或失败时，用BTA_JV_ReFCOMM_OPEN_EVT调用
**
** 如果正在处理请求，则返回BTA_JV_SUCCESS。否则为BTA_JV_FAILURE。
**
*******************************************************************************/
extern tBTA_JV_STATUS BTA_JvRfcommConnect(tBTA_SEC sec_mask,
        tBTA_JV_ROLE role, UINT8 remote_scn, BD_ADDR peer_bd_addr,
        tBTA_JV_RFCOMM_CBACK *p_cback, void *user_data);

/*******************************************************************************
** 功能BTA_JvRfcommClose
**
** 说明此函数关闭RFCOMM连接
**
** 如果正在处理请求，则返回BTA_JV_SUCCESS。否则为BTA_JV_FAILURE。
**
*******************************************************************************/
extern tBTA_JV_STATUS BTA_JvRfcommClose(UINT32 handle, tBTA_JV_RFCOMM_CBACK *p_cback, void *user_data);

/*******************************************************************************
** 功能BTA_JvRfcommStartServer
**
** 描述此函数开始侦听来自远程蓝牙设备的RFCOMM连接请求。成功启动服务器后，使用BTA_JV_RFCOMM_START_EVT调用tBTA_JV-RFCOMM_BACK。建立连接后，使用BTA_JV_RFCOMM_OPEN_EVT调用tBTA_JV-RFCOMM_BACK。
**
** 如果正在处理请求，则返回BTA_JV_SUCCESS。否则为BTA_JV_FAILURE。
**
*******************************************************************************/
extern tBTA_JV_STATUS BTA_JvRfcommStartServer(tBTA_SEC sec_mask, tBTA_JV_ROLE role,
                                              UINT8 local_scn, UINT8 max_session,
                                              tBTA_JV_RFCOMM_CBACK *p_cback, void *user_data);

/*******************************************************************************
** 功能BTA_JvRfcommStopServer
**
** 说明此函数用于停止RFCOMM服务器。如果服务器有一个活动连接，它将被关闭。
**
** 如果正在处理请求，则返回BTA_JV_SUCCESS。否则为BTA_JV_FAILURE。
**
*******************************************************************************/
extern tBTA_JV_STATUS BTA_JvRfcommStopServer(UINT32 handle, void *user_data);

/*******************************************************************************
** 函数BTA_JvRfcommRead
**
** 说明此函数从RFCOMM连接读取数据当操作完成时，使用BTA_JV_RFCOMM_READ_EVT调用tBTA_JV-RFCOMM_BACK。
**
** 如果正在处理请求，则返回BTA_JV_SUCCESS。否则为BTA_JV_FAILURE。
**
*******************************************************************************/
extern tBTA_JV_STATUS BTA_JvRfcommRead(UINT32 handle, UINT32 req_id, UINT8 *p_data, UINT16 len);

/*******************************************************************************
** 功能BTA_JvRfcommReady
**
** 说明此函数确定是否有数据要从RFCOMM连接读取
**
** 如果数据队列大小为*p_data_size，则返回BTA_JV_SUCCESS。如果错误，则返回BTA_JV_FAILURE。
**
*******************************************************************************/
extern tBTA_JV_STATUS BTA_JvRfcommReady(UINT32 handle, UINT32 *p_data_size);

/*******************************************************************************
** 函数BTA_JvRfcommWrite
**
** 说明此函数将数据写入RFCOMM连接当操作完成时，使用BTA_JV_RFCOMM_WRITE_EVT调用tBTA_JV-RFCOMM_BACK。
**
** 如果正在处理请求，则返回BTA_JV_SUCCESS。否则为BTA_JV_FAILURE。
**
*******************************************************************************/
extern tBTA_JV_STATUS BTA_JvRfcommWrite(UINT32 handle, UINT32 req_id, int len, UINT8 *p_data);

/*******************************************************************************
** 功能BTA_JvRfcommFlowControl
**
** 说明此功能为对等方提供信用
**
** 如果正在处理请求，则返回BTA_JV_SUCCESS。否则为BTA_JV_FAILURE。
**
*******************************************************************************/
extern tBTA_JV_STATUS BTA_JvRfcommFlowControl(UINT32 handle, UINT16 credits_given);

/*******************************************************************************
 ** 函数BTA_JVSetPmProfile
 **
 ** 说明该功能为不同的JV应用设置或自由功率模式配置文件
 **
 ** 参数：handle、RFCOMM或L2CAP app_id中的JV handle：应用程序特定的pm id，可以是BTA_JV_pm_ALL，请参见BTA_dm_cfg。c获取详细信息BTA_JV_PM_ID_CLEAR：删除句柄上的PM管理。init_st被忽略，并且BTA_JV_CONN_CLOSE在调用此API后被隐式调用init_st:state。通常应为BTA_JV_CONN_OPEN
 **
 ** 如果正在处理请求，则返回BTA_JV_SUCCESS。否则为BTA_JV_FAILURE。
 **
 ** 注意：BTA_JV_PM_ID_CLEAR：通常不需要调用，因为JV PM会在连接关闭时自动调用BTA_JV_CONN_CLOSE以删除！
 **
 *******************************************************************************/
extern tBTA_JV_STATUS BTA_JvSetPmProfile(UINT32 handle, tBTA_JV_PM_ID app_id, tBTA_JV_CONN_STATE init_st);

/*******************************************************************************
** 函数BTA_JvRfcommGetPortHdl
**
** 说明此函数获取rfcomm端口句柄
**
** 如果正在处理请求，则返回BTA_JV_SUCCESS。否则为BTA_JV_FAILURE。
**
*******************************************************************************/
UINT16 BTA_JvRfcommGetPortHdl(UINT32 handle);

#endif  ///定义的BTA_JV_INCLUDE&BTA_JV_inCLUDE==真
#endif /* BTA_JV_API_H */

