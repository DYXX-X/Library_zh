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
#ifndef GATT_API_H
#define GATT_API_H

#include "common/bt_target.h"
#include "stack/gattdefs.h"
#include "stack/btm_ble_api.h"

/*****************************************************************************
**  常量
*****************************************************************************/
/* 成功代码和错误代码*/
#define  GATT_SUCCESS                        0x00
#define  GATT_INVALID_HANDLE                 0x01
#define  GATT_READ_NOT_PERMIT                0x02
#define  GATT_WRITE_NOT_PERMIT               0x03
#define  GATT_INVALID_PDU                    0x04
#define  GATT_INSUF_AUTHENTICATION           0x05
#define  GATT_REQ_NOT_SUPPORTED              0x06
#define  GATT_INVALID_OFFSET                 0x07
#define  GATT_INSUF_AUTHORIZATION            0x08
#define  GATT_PREPARE_Q_FULL                 0x09
#define  GATT_NOT_FOUND                      0x0a
#define  GATT_NOT_LONG                       0x0b
#define  GATT_INSUF_KEY_SIZE                 0x0c
#define  GATT_INVALID_ATTR_LEN               0x0d
#define  GATT_ERR_UNLIKELY                   0x0e
#define  GATT_INSUF_ENCRYPTION               0x0f
#define  GATT_UNSUPPORT_GRP_TYPE             0x10
#define  GATT_INSUF_RESOURCE                 0x11


#define  GATT_NO_RESOURCES                   0x80
#define  GATT_INTERNAL_ERROR                 0x81
#define  GATT_WRONG_STATE                    0x82
#define  GATT_DB_FULL                        0x83
#define  GATT_BUSY                           0x84
#define  GATT_ERROR                          0x85
#define  GATT_CMD_STARTED                    0x86
#define  GATT_ILLEGAL_PARAMETER              0x87
#define  GATT_PENDING                        0x88
#define  GATT_AUTH_FAIL                      0x89
#define  GATT_MORE                           0x8a
#define  GATT_INVALID_CFG                    0x8b
#define  GATT_SERVICE_STARTED                0x8c
#define  GATT_ENCRYPED_MITM                  GATT_SUCCESS
#define  GATT_ENCRYPED_NO_MITM               0x8d
#define  GATT_NOT_ENCRYPTED                  0x8e
#define  GATT_CONGESTED                      0x8f

#define  GATT_DUP_REG                        0x90
#define  GATT_ALREADY_OPEN                   0x91
#define  GATT_CANCEL                         0x92

/* 0xE0~0xFC保留供将来使用*/
#define  GATT_STACK_RSP                      0xE0
#define  GATT_APP_RSP                        0xE1
//客户应用程序或堆栈错误导致的错误
#define  GATT_UNKNOWN_ERROR                  0XEF

#define  GATT_CCC_CFG_ERR                    0xFD /* 客户端特征配置描述符配置不正确*/
#define  GATT_PRC_IN_PROGRESS                0xFE /* 程序已在进行中*/
#define  GATT_OUT_OF_RANGE                   0xFF /* 属性值超出范围*/

typedef UINT8 tGATT_STATUS;


#define  GATT_RSP_ERROR                      0x01
#define  GATT_REQ_MTU                        0x02
#define  GATT_RSP_MTU                        0x03
#define  GATT_REQ_FIND_INFO                  0x04
#define  GATT_RSP_FIND_INFO                  0x05
#define  GATT_REQ_FIND_TYPE_VALUE            0x06
#define  GATT_RSP_FIND_TYPE_VALUE            0x07
#define  GATT_REQ_READ_BY_TYPE               0x08
#define  GATT_RSP_READ_BY_TYPE               0x09
#define  GATT_REQ_READ                       0x0A
#define  GATT_RSP_READ                       0x0B
#define  GATT_REQ_READ_BLOB                  0x0C
#define  GATT_RSP_READ_BLOB                  0x0D
#define  GATT_REQ_READ_MULTI                 0x0E
#define  GATT_RSP_READ_MULTI                 0x0F
#define  GATT_REQ_READ_BY_GRP_TYPE           0x10
#define  GATT_RSP_READ_BY_GRP_TYPE           0x11
#define  GATT_REQ_WRITE                      0x12 /*                 0001-0010（写入）*/
#define  GATT_RSP_WRITE                      0x13
#define  GATT_CMD_WRITE                      0x52 /* 在V4.0 01001-0010中更改（写入命令）*/
#define  GATT_REQ_PREPARE_WRITE              0x16
#define  GATT_RSP_PREPARE_WRITE              0x17
#define  GATT_REQ_EXEC_WRITE                 0x18
#define  GATT_RSP_EXEC_WRITE                 0x19
#define  GATT_HANDLE_VALUE_NOTIF             0x1B
#define  GATT_HANDLE_VALUE_IND               0x1D
#define  GATT_HANDLE_VALUE_CONF              0x1E
#define  GATT_SIGN_CMD_WRITE                 0xD2 /* 在V4.0 1101-0010中更改（签名写入），请参阅上面的write cmd*/
#define  GATT_OP_CODE_MAX                    GATT_HANDLE_VALUE_CONF + 1 /* 0x1E=30+1=31*/

#define  GATT_COMMAND_FLAG                   0x40 /* 命令标志：设置为一表示命令*/

#define  GATT_HANDLE_IS_VALID(x) ((x) != 0)

#define GATT_CONN_UNKNOWN                   0
#define GATT_CONN_L2C_FAILURE               1                               /* 一般L2cap故障*/
#define GATT_CONN_TIMEOUT                   HCI_ERR_CONNECTION_TOUT         /* 0x08连接超时*/
#define GATT_CONN_TERMINATE_PEER_USER       HCI_ERR_PEER_USER               /* 0x13连接由对等用户终止*/
#define GATT_CONN_TERMINATE_LOCAL_HOST      HCI_ERR_CONN_CAUSE_LOCAL_HOST   /* 0x16连接被本地主机终止*/
#define GATT_CONN_FAIL_ESTABLISH            HCI_ERR_CONN_FAILED_ESTABLISHMENT/* 0x03E连接无法建立*/
#define GATT_CONN_LMP_TIMEOUT               HCI_ERR_LMP_RESPONSE_TIMEOUT     /* LMP响应tout的0x22连接失败*/
#define GATT_CONN_CANCEL                    L2CAP_CONN_CANCEL                /* 0x0100 L2CAP连接已取消*/
typedef UINT16 tGATT_DISCONN_REASON;

/* 最大GATT MTU尺寸
*/
#ifndef GATT_MAX_MTU_SIZE
#define GATT_MAX_MTU_SIZE                   517
#endif

/* 属性值的最大长度
*/
#ifndef GATT_MAX_ATTR_LEN
#define GATT_MAX_ATTR_LEN                   600
#endif

/* LE链路上的默认GATT MTU大小
*/
#define GATT_DEF_BLE_MTU_SIZE               23

/* 连接ID无效
*/
#define GATT_INVALID_CONN_ID                0xFFFF

#ifndef GATT_CL_MAX_LCB
#define GATT_CL_MAX_LCB                     12 // 22
#endif

#ifndef GATT_MAX_SCCB
#define GATT_MAX_SCCB                       10
#endif


/* GATT通知缓存计时器，默认为3秒
*/
#ifndef GATTC_NOTIF_TIMEOUT
#define GATTC_NOTIF_TIMEOUT                 3
#endif

/*****************************************************************************
** GATT结构定义
*****************************************************************************/

/* 属性权限
*/
#define GATT_PERM_READ                      (1 << 0) /* 位0*/
#define GATT_PERM_READ_ENCRYPTED            (1 << 1) /* 第1位*/
#define GATT_PERM_READ_ENC_MITM             (1 << 2) /* 第2位*/
#define GATT_PERM_WRITE                     (1 << 4) /* 第4位*/
#define GATT_PERM_WRITE_ENCRYPTED           (1 << 5) /* 第5位*/
#define GATT_PERM_WRITE_ENC_MITM            (1 << 6) /* 第6位*/
#define GATT_PERM_WRITE_SIGNED              (1 << 7) /* 第7位*/
#define GATT_PERM_WRITE_SIGNED_MITM         (1 << 8) /* 第8位*/
#define GATT_PERM_READ_AUTHORIZATION        (1 << 9) /* 第9位*/
#define GATT_PERM_WRITE_AUTHORIZATION       (1 << 10)/* 钻头10*/
typedef UINT16 tGATT_PERM;

#define GATT_ENCRYPT_KEY_SIZE_MASK  (0xF000) /* tGATT_PERM的MS半字节；密钥大小7=0；尺寸16=9*/

#define GATT_READ_ALLOWED                   (GATT_PERM_READ | GATT_PERM_READ_ENCRYPTED | GATT_PERM_READ_ENC_MITM | GATT_PERM_READ_AUTHORIZATION)
#define GATT_READ_AUTH_REQUIRED             (GATT_PERM_READ_ENCRYPTED)
#define GATT_READ_MITM_REQUIRED             (GATT_PERM_READ_ENC_MITM)
#define GATT_READ_ENCRYPTED_REQUIRED        (GATT_PERM_READ_ENCRYPTED | GATT_PERM_READ_ENC_MITM)
#define GATT_READ_AUTHORIZATION             (GATT_PERM_READ_AUTHORIZATION)


#define GATT_WRITE_ALLOWED          (GATT_PERM_WRITE | GATT_PERM_WRITE_ENCRYPTED | GATT_PERM_WRITE_ENC_MITM | \
                                     GATT_PERM_WRITE_SIGNED | GATT_PERM_WRITE_SIGNED_MITM | GATT_PERM_WRITE_AUTHORIZATION)

#define GATT_WRITE_AUTH_REQUIRED    (GATT_PERM_WRITE_ENCRYPTED | GATT_PERM_WRITE_SIGNED)

#define GATT_WRITE_MITM_REQUIRED    (GATT_PERM_WRITE_ENC_MITM | GATT_PERM_WRITE_SIGNED_MITM)

#define GATT_WRITE_ENCRYPTED_PERM   (GATT_PERM_WRITE_ENCRYPTED | GATT_PERM_WRITE_ENC_MITM)

#define GATT_WRITE_SIGNED_PERM      (GATT_PERM_WRITE_SIGNED | GATT_PERM_WRITE_SIGNED_MITM)

#define GATT_WRITE_AUTHORIZATION    (GATT_PERM_WRITE_AUTHORIZATION)


/* 特性
*/
#define GATT_CHAR_PROP_BIT_BROADCAST    (1 << 0)
#define GATT_CHAR_PROP_BIT_READ         (1 << 1)
#define GATT_CHAR_PROP_BIT_WRITE_NR     (1 << 2)
#define GATT_CHAR_PROP_BIT_WRITE        (1 << 3)
#define GATT_CHAR_PROP_BIT_NOTIFY       (1 << 4)
#define GATT_CHAR_PROP_BIT_INDICATE     (1 << 5)
#define GATT_CHAR_PROP_BIT_AUTH         (1 << 6)
#define GATT_CHAR_PROP_BIT_EXT_PROP     (1 << 7)
typedef UINT8 tGATT_CHAR_PROP;


/* 特征值的格式。枚举类型
*/
enum {
    GATT_FORMAT_RES,            /* 无线电频率单位*/
    GATT_FORMAT_BOOL,           /* 0x01布尔值*/
    GATT_FORMAT_2BITS,           /* 0x02 2位*/
    GATT_FORMAT_NIBBLE,         /* 0x03半字节*/
    GATT_FORMAT_UINT8,          /* 0x04 uint8*/
    GATT_FORMAT_UINT12,         /* 0x05 uint12*/
    GATT_FORMAT_UINT16,         /* 0x06 uint16*/
    GATT_FORMAT_UINT24,         /* 0x07 uint24*/
    GATT_FORMAT_UINT32,         /* 0x08 uint32*/
    GATT_FORMAT_UINT48,         /* 0x09 uint48*/
    GATT_FORMAT_UINT64,         /* 0x0a uint64*/
    GATT_FORMAT_UINT128,        /* 0x0B uint128*/
    GATT_FORMAT_SINT8,          /* 0x0C有符号8位整数*/
    GATT_FORMAT_SINT12,         /* 0x0D有符号12位整数*/
    GATT_FORMAT_SINT16,         /* 0x0E有符号16位整数*/
    GATT_FORMAT_SINT24,         /* 0x0F有符号24位整数*/
    GATT_FORMAT_SINT32,         /* 0x10有符号32位整数*/
    GATT_FORMAT_SINT48,         /* 0x11有符号48位整数*/
    GATT_FORMAT_SINT64,         /* 0x12有符号64位整数*/
    GATT_FORMAT_SINT128,        /* 0x13有符号128位整数*/
    GATT_FORMAT_FLOAT32,        /* 0x14浮子32*/
    GATT_FORMAT_FLOAT64,        /* 0x15浮动64*/
    GATT_FORMAT_SFLOAT,         /* 0x16 IEEE-11073 16位SFLOAT*/
    GATT_FORMAT_FLOAT,          /* 0x17 IEEE-11073 32位SFLOAT*/
    GATT_FORMAT_DUINT16,        /* 0x18 IEEE-20601格式*/
    GATT_FORMAT_UTF8S,          /* 0x19 UTF-8字符串*/
    GATT_FORMAT_UTF16S,         /* 0x1a UTF-16字符串*/
    GATT_FORMAT_STRUCT,         /* 0x1b不透明结构*/
    GATT_FORMAT_MAX             /* 0x1c或以上预留*/
};
typedef UINT8 tGATT_FORMAT;

/* 特征表示格式描述符值
*/
typedef struct {
    UINT16              unit;        /* 作为SIG定义的UUID*/
    UINT16              descr;       /* 作为SIG定义的UUID*/
    tGATT_FORMAT        format;
    INT8                exp;
    UINT8               name_spc;   /* 描述的名称空间*/
} tGATT_CHAR_PRES;

/* 特征报告参考描述符格式
*/
typedef struct {
    UINT8              rpt_id;       /* 报告ID*/
    UINT8              rpt_type;       /* 报告类型*/
} tGATT_CHAR_RPT_REF;


#define GATT_VALID_RANGE_MAX_SIZE       16
typedef struct {
    UINT8                   format;
    UINT16                  len;
    UINT8                   lower_range[GATT_VALID_RANGE_MAX_SIZE]; /* 小端字节格式*/
    UINT8                   upper_range[GATT_VALID_RANGE_MAX_SIZE];
} tGATT_VALID_RANGE;

/* 特征聚合格式属性值
*/
#define GATT_AGGR_HANDLE_NUM_MAX        10
typedef struct {
    UINT8                   num_handle;
    UINT16                  handle_list[GATT_AGGR_HANDLE_NUM_MAX];
} tGATT_CHAR_AGGRE;

/* 特征描述符：扩展属性值
*/
#define GATT_CHAR_BIT_REL_WRITE    0x0001       /* 允许可靠地写入特征值*/
#define GATT_CHAR_BIT_WRITE_AUX    0x0002       /* 允许写入特征描述符*/


/* 特征描述符：客户端配置值
*/
#define GATT_CLT_CONFIG_NONE               0x0000
#define GATT_CLT_CONFIG_NOTIFICATION       0x0001
#define GATT_CLT_CONFIG_INDICATION         0x0002
typedef UINT16 tGATT_CLT_CHAR_CONFIG;


/* 特征描述符：服务器配置值
*/
#define GATT_SVR_CONFIG_NONE                     0x0000
#define GATT_SVR_CONFIG_BROADCAST                0x0001
typedef UINT16 tGATT_SVR_CHAR_CONFIG;

/* 特征描述符：扩展属性值
*/
#define GATT_CHAR_BIT_REL_WRITE    0x0001       /* 允许可靠地写入特征值*/
#define GATT_CHAR_BIT_WRITE_AUX    0x0002       /* 允许写入特征描述符*/

/* 认证要求
*/
#define GATT_AUTH_REQ_NONE              0
#define GATT_AUTH_REQ_NO_MITM           1   /* 未经身份验证的加密*/
#define GATT_AUTH_REQ_MITM              2   /* 经过身份验证的加密*/
#define GATT_AUTH_REQ_SIGNED_NO_MITM    3
#define GATT_AUTH_REQ_SIGNED_MITM       4
typedef UINT8 tGATT_AUTH_REQ;

/* 属性值结构
*/
typedef struct {
    UINT16          conn_id;
    UINT16          handle;     /* 属性句柄*/
    UINT16          offset;     /* 属性值偏移，如果命令不需要偏移，则忽略它*/
    UINT16          len;        /* 属性值长度*/
    tGATT_AUTH_REQ  auth_req;   /*  身份验证请求*/
    UINT8           value[GATT_MAX_ATTR_LEN];  /* 实际属性值*/
} tGATT_VALUE;

typedef struct{
    UINT16  attr_max_len;
    UINT16  attr_len;
    UINT8   *attr_val;
}tGATT_ATTR_VAL;

typedef struct{
    uint8_t auto_rsp;
}tGATTS_ATTR_CONTROL;

/* gatt服务器属性的掩码*/
#define GATT_ATTR_VALUE_ALLOCATED  0x01
typedef UINT8 tGATT_ATTR_MASK;

/* 服务器响应API中用于携带服务器响应信息的事件数据的联合
*/
typedef union {
    /* 数据类型成员事件*/
    tGATT_VALUE             attr_value;     /* READ, HANDLE_VALUE_IND, PREPARE_WRITE */
    /* READ_BLOB, READ_BY_TYPE */
    UINT16                  handle;         /* WRITE, WRITE_BLOB */

} tGATTS_RSP;

/* 主要服务的传输*/
#define GATT_TRANSPORT_LE           BT_TRANSPORT_LE
#define GATT_TRANSPORT_BR_EDR       BT_TRANSPORT_BR_EDR
#define GATT_TRANSPORT_LE_BR_EDR    (BT_TRANSPORT_LE|BT_TRANSPORT_BR_EDR)
typedef UINT8 tGATT_TRANSPORT;

#define GATT_PREP_WRITE_CANCEL   0x00
#define GATT_PREP_WRITE_EXEC     0x01
typedef UINT8   tGATT_EXEC_FLAG;

/* 读取请求始终基于UUID*/
typedef struct {
    UINT16        handle;
    UINT16        offset;
    BOOLEAN       is_long;
    BOOLEAN       need_rsp;
} tGATT_READ_REQ;

/* 写入请求数据*/
typedef struct {
    UINT16          handle;     /* 属性句柄*/
    UINT16          offset;     /* 属性值偏移，如果命令不需要偏移，则忽略它*/
    UINT16          len;        /* 属性值长度*/
    UINT8           value[GATT_MAX_ATTR_LEN];  /* 实际属性值*/
    BOOLEAN         need_rsp;   /* 需要写入响应*/
    BOOLEAN         is_prep;    /* 正在准备写入*/
} tGATT_WRITE_REQ;

/* 客户端服务器访问请求的回调数据*/
typedef union {
    tGATT_READ_REQ         read_req;       /* 读取请求，按类型读取，读取blob*/

    tGATT_WRITE_REQ        write_req;    /* 写*/
    /* 准备写入*/
    /* 写入blob*/
    UINT16                 handle;       /* 处理值确认*/
    UINT16                 mtu;          /* MTU交换请求*/
    tGATT_EXEC_FLAG        exec_write;    /* 执行写入*/
} tGATTS_DATA;

typedef UINT8 tGATT_SERV_IF;               /* GATT服务接口*/

enum {
    GATTS_REQ_TYPE_READ = 1,        /* 属性读取请求*/
    GATTS_REQ_TYPE_WRITE,           /* 属性写入请求*/
    GATTS_REQ_TYPE_WRITE_EXEC,      /* 执行写入*/
    GATTS_REQ_TYPE_MTU,             /* MTU交换信息*/
    GATTS_REQ_TYPE_CONF             /* 处理值确认*/
};
typedef UINT8   tGATTS_REQ_TYPE;



/* 客户端使用的数据结构
*/
/* 不同发现类型的定义*/
enum {
    GATT_DISC_SRVC_ALL = 1,     /* 发现所有服务*/
    GATT_DISC_SRVC_BY_UUID,     /* 发现特殊类型的服务*/
    GATT_DISC_INC_SRVC,         /* 发现服务中包含的服务*/
    GATT_DISC_CHAR,             /* 发现具有/不具有类型要求的服务的特征*/
    GATT_DISC_CHAR_DSCPT,       /* 发现角色的特征描述符*/
    GATT_DISC_MAX               /* maximun发现类型*/
};
typedef UINT8   tGATT_DISC_TYPE;

/* 发现不同发现类型的参数
*/
typedef struct {
    tBT_UUID    service;
    UINT16      s_handle;
    UINT16      e_handle;
} tGATT_DISC_PARAM;

/* GATT读取类型枚举
*/
enum {
    GATT_READ_BY_TYPE =        1,
    GATT_READ_BY_HANDLE,
    GATT_READ_MULTIPLE,
    GATT_READ_CHAR_VALUE,
    GATT_READ_PARTIAL,
    GATT_READ_MAX
};
typedef UINT8 tGATT_READ_TYPE;

/* 按类型读取请求（GATT_Read_By_Type）数据
*/
typedef struct {
    tGATT_AUTH_REQ      auth_req;
    UINT16              s_handle;
    UINT16              e_handle;
    tBT_UUID            uuid;
} tGATT_READ_BY_TYPE;

/*   GATT_READ_MULTIPLE请求数据
*/
#define GATT_MAX_READ_MULTI_HANDLES      10           /* 一个请求中读取的最大属性数*/
typedef struct {
    tGATT_AUTH_REQ          auth_req;
    UINT16                  num_handles;                            /* 要读取的句柄数*/
    UINT16                  handles[GATT_MAX_READ_MULTI_HANDLES];   /* 要读取的句柄列表*/
} tGATT_READ_MULTI;

/*   按句柄读取请求（GATT_Read_By_Handle）数据*/
typedef struct {
    tGATT_AUTH_REQ         auth_req;
    UINT16                 handle;
} tGATT_READ_BY_HANDLE;

/*   READ_BT_HANDLE_Request数据*/
typedef struct {
    tGATT_AUTH_REQ         auth_req;
    UINT16                 handle;
    UINT16                 offset;
} tGATT_READ_PARTIAL;

/* 读取请求数据
*/
typedef union {
    tGATT_READ_BY_TYPE   service;
    tGATT_READ_BY_TYPE   char_type;        /* 特征类型*/
    tGATT_READ_MULTI     read_multiple;
    tGATT_READ_BY_HANDLE by_handle;
    tGATT_READ_PARTIAL   partial;
} tGATT_READ_PARAM;

/* GATT写入类型枚举*/
enum {
    GATT_WRITE_NO_RSP = 1,
    GATT_WRITE ,
    GATT_WRITE_PREPARE
};
typedef UINT8 tGATT_WRITE_TYPE;

/* 客户端操作完成回调数据
*/
typedef union {
    tGATT_VALUE          att_value;
    UINT16               mtu;
    UINT16               handle;
} tGATT_CL_COMPLETE;

/* GATT客户端操作类型，用于客户端回调函数
*/
#define GATTC_OPTYPE_NONE                 0
#define GATTC_OPTYPE_DISCOVERY            1
#define GATTC_OPTYPE_READ                 2
#define GATTC_OPTYPE_WRITE                3
#define GATTC_OPTYPE_EXE_WRITE            4
#define GATTC_OPTYPE_CONFIG               5
#define GATTC_OPTYPE_NOTIFICATION         6
#define GATTC_OPTYPE_INDICATION           7
typedef UINT8 tGATTC_OPTYPE;

/* 特性声明
*/
typedef struct {
    tGATT_CHAR_PROP       char_prop;   /* 特性*/
    UINT16                val_handle;  /* 特征值属性句柄*/
    tBT_UUID              char_uuid;   /* 特征UUID类型*/
} tGATT_CHAR_DCLR_VAL;

/* 主要服务组数据
*/
typedef struct {
    UINT16          e_handle;       /* 组的结束句柄*/
    tBT_UUID        service_type;   /* 组类型*/
} tGATT_GROUP_VALUE;


/* 包含的服务属性值
*/
typedef struct {
    tBT_UUID    service_type;       /* 包含的服务UUID*/
    UINT16      s_handle;           /* 起动手柄*/
    UINT16      e_handle;           /* 末端手柄*/
} tGATT_INCL_SRVC;

typedef union {
    tGATT_INCL_SRVC     incl_service;  /* 包括服务价值*/
    tGATT_GROUP_VALUE   group_value;   /* 服务UUID类型。此字段与GATT_DISC_SRVC_ALL或GATT_DISC_StRVC_BY_UUID类型的发现结果回调一起使用。*/

    UINT16              handle;        /* 当与GATT_DISC_INC_SRVC类型发现结果一起使用时，它是包含的服务启动句柄。*/

    tGATT_CHAR_DCLR_VAL dclr_value;    /* 特征声明值。此字段用于GATT_DISC_CHAR类型发现。*/
} tGATT_DISC_VALUE;

/* 发现结果记录
*/
typedef struct {
    tBT_UUID            type;
    UINT16              handle;
    tGATT_DISC_VALUE    value;
} tGATT_DISC_RES;


#define GATT_LINK_IDLE_TIMEOUT_WHEN_NO_APP    0 /* 当没有应用程序需要使用链接时，在此期间启动空闲计时器*/

#define GATT_LINK_NO_IDLE_TIMEOUT            0xFFFF

#define GATT_INVALID_ACL_HANDLE              0xFFFF
/* 发现结果回调函数*/
typedef void (tGATT_DISC_RES_CB) (UINT16 conn_id, tGATT_DISC_TYPE disc_type,
                                  tGATT_DISC_RES *p_data);

/* 发现完整的回调函数*/
typedef void (tGATT_DISC_CMPL_CB) (UINT16 conn_id, tGATT_DISC_TYPE disc_type, tGATT_STATUS status);

/* 定义读/写/盘/配置操作完成时的回调函数。*/
typedef void (tGATT_CMPL_CBACK) (UINT16 conn_id, tGATTC_OPTYPE op, tGATT_STATUS status,
                                 tGATT_CL_COMPLETE *p_data);

/* 在建立初始化连接时定义回调函数。*/
typedef void (tGATT_CONN_CBACK) (tGATT_IF gatt_if, BD_ADDR bda, UINT16 conn_id, BOOLEAN connected,
                                 tGATT_DISCONN_REASON reason, tBT_TRANSPORT transport);

/* ATT服务器的属性请求回调*/
typedef void  (tGATT_REQ_CBACK )(UINT16 conn_id, UINT32 trans_id, tGATTS_REQ_TYPE type,
                                 tGATTS_DATA *p_data);

/* 信道拥塞/非拥塞回调*/
typedef void (tGATT_CONGESTION_CBACK )(UINT16 conn_id, BOOLEAN congested);

/* 在建立加密时定义回调函数。*/
typedef void (tGATT_ENC_CMPL_CB)(tGATT_IF gatt_if, BD_ADDR bda);


/* 定义应用程序用于向GATT注册的结构。此结构包括回调函数。必须提供所有功能。
*/
typedef struct {
    tGATT_CONN_CBACK                *p_conn_cb;
    tGATT_CMPL_CBACK                *p_cmpl_cb;
    tGATT_DISC_RES_CB               *p_disc_res_cb;
    tGATT_DISC_CMPL_CB              *p_disc_cmpl_cb;
    tGATT_REQ_CBACK                 *p_req_cb;
    tGATT_ENC_CMPL_CB               *p_enc_cmpl_cb;
    tGATT_CONGESTION_CBACK          *p_congestion_cb;
} tGATT_CBACK;

/***********************  启动句柄管理定义**********************
*/


typedef struct {
    tBT_UUID app_uuid128;
    tBT_UUID svc_uuid;
    UINT16   svc_inst;
    UINT16   s_handle;
    UINT16   e_handle;
    BOOLEAN  is_primary;      /* 主要服务或次要服务*/
} tGATTS_HNDL_RANGE;



#define GATTS_SRV_CHG_CMD_ADD_CLIENT       1
#define GATTS_SRV_CHG_CMD_UPDATE_CLIENT    2
#define GATTS_SRV_CHG_CMD_REMOVE_CLIENT    3
#define GATTS_SRV_CHG_CMD_READ_NUM_CLENTS  4
#define GATTS_SRV_CHG_CMD_READ_CLENT       5
typedef UINT8 tGATTS_SRV_CHG_CMD;

typedef struct {
    BD_ADDR         bda;
    BOOLEAN         srv_changed;
} tGATTS_SRV_CHG;


typedef union {
    tGATTS_SRV_CHG  srv_chg;
    UINT8           client_read_index; /* 仅用于顺序读取客户端srv chg信息*/
} tGATTS_SRV_CHG_REQ;

typedef union {
    tGATTS_SRV_CHG srv_chg;
    UINT8 num_clients;
} tGATTS_SRV_CHG_RSP;



typedef struct {
    tGATTS_HNDL_RANGE   *p_new_srv_start;
} tGATTS_PENDING_NEW_SRV_START;

/* 属性服务器句柄范围NV存储回调函数
*/
typedef void  (tGATTS_NV_SAVE_CBACK)(BOOLEAN is_saved, tGATTS_HNDL_RANGE *p_hndl_range);
typedef BOOLEAN  (tGATTS_NV_SRV_CHG_CBACK)(tGATTS_SRV_CHG_CMD cmd, tGATTS_SRV_CHG_REQ *p_req,
        tGATTS_SRV_CHG_RSP *p_rsp);

typedef struct {
    tGATTS_NV_SAVE_CBACK       *p_nv_save_callback;
    tGATTS_NV_SRV_CHG_CBACK    *p_srv_chg_callback;
} tGATT_APPL_INFO;

/***********************末端手柄管理定义**********************/

/*****************************************************************************
**  外部函数声明
*****************************************************************************/
#ifdef __cplusplus
extern "C"
{
#endif

/*******************************************************************************
** 函数GATT_SetTraceLevel
**
** 说明此函数设置跟踪级别。如果使用值0xFF调用，它只返回当前跟踪级别。
**
** 返回新的或当前的跟踪级别
**
*******************************************************************************/
extern UINT8 GATT_SetTraceLevel (UINT8 new_level);


/*******************************************************************************/
/* GATT配置文件API函数*/
/*******************************************************************************/
/* GATT配置文件服务器功能*/
/*******************************************************************************/
/*******************************************************************************
** 函数GATTS_AddHandleRange
**
** 说明此函数为指定的应用程序UUID、服务UUID和服务实例添加分配的句柄范围
**
** 参数p_hndl_range：指向已分配句柄信息的指针
**
** 如果成功添加句柄范围，则返回TRUE；否则为FALSE。
**
*******************************************************************************/

extern BOOLEAN GATTS_AddHandleRange(tGATTS_HNDL_RANGE *p_hndl_range);

/*******************************************************************************
** 函数GATTS_NVRegister
**
** 说明应用程序管理器调用此函数以注册NV保存回调函数。只能有一个NV保存回调函数。
**
** 参数p_cb_info：回调信息
**
** 如果注册为OK，则返回TRUE，否则返回FALSE
**
*******************************************************************************/
extern BOOLEAN  GATTS_NVRegister (const tGATT_APPL_INFO *p_cb_info);


/*******************************************************************************
** 函数GATTS_CreateService
**
** 描述调用此函数为服务保留句柄块。
**
**                  ***每个服务实例只能调用一次***
**
** 参数gatt_if:application-if p_svc_uuid:service uuid svc_inst：应用程序内服务的实例num_handles：服务所需的句柄数。is_pri：是否为主要服务。
**
** 如果成功，则返回服务句柄，否则为0。
**
*******************************************************************************/
extern UINT16 GATTS_CreateService (tGATT_IF gatt_if, tBT_UUID *p_svc_uuid,
                                   UINT16 svc_inst, UINT16 num_handles, BOOLEAN is_pri);


/*******************************************************************************
** 函数GATTS_AddIncludeService
**
** 说明调用此函数以添加包含的服务。
**
** 参数service_handle：将此包含的服务添加到哪个服务。include_svc_handle:包含的服务句柄。
**
** 返回包含的服务属性句柄。如果为0，则添加包含的服务失败。
**
*******************************************************************************/
extern UINT16 GATTS_AddIncludeService (UINT16 service_handle,
                                       UINT16 include_svc_handle);


/*******************************************************************************
** 函数GATTS_AddCharacteristic
**
** 描述调用此函数将特性添加到服务中。它将向由服务句柄标识的服务数据库中添加特征声明和特征值声明。
**
** 参数service_handle：将此包含的服务添加到哪个服务。char_uuid：特征uuid。perm：特征值声明属性权限。特性：特性特性
**
** 返回Characteristic值声明属性句柄。如果添加特征失败，则为0。
**
*******************************************************************************/
extern UINT16 GATTS_AddCharacteristic (UINT16 service_handle, tBT_UUID *p_char_uuid,
                                tGATT_PERM perm, tGATT_CHAR_PROP property,
                                tGATT_ATTR_VAL *attr_val, tGATTS_ATTR_CONTROL *control);

/*******************************************************************************
** 函数GATTS_AddCharDescriptor
**
** 描述调用此函数将特性描述符添加到服务数据库中。添加描述符应该跟在它所属的添加字符之后，下一个添加字符只能在前一个字符的所有添加描述符之后进行。
**
** 参数service_handle：将此特性描述符添加到哪个服务。perm:特性值声明属性权限。p_descr_uid：特征描述符uuid。
**
** 返回Characteristic描述符属性句柄。如果添加特征描述符失败，则为0。
**
*******************************************************************************/
extern UINT16 GATTS_AddCharDescriptor (UINT16 service_handle, tGATT_PERM perm,
                                                                tBT_UUID   *p_descr_uuid, tGATT_ATTR_VAL *attr_val,
                                                                tGATTS_ATTR_CONTROL *control);

/*******************************************************************************
** 函数GATTS_DeleteService
**
** 说明此函数用于删除服务。
**
** 参数gatt_if:application interface p_svc_uuid:service uuid svc_inst：应用程序内服务的实例
**
** 如果操作成功，则返回TRUE；如果未找到句柄块，则返回FALSE。
**
*******************************************************************************/
extern BOOLEAN GATTS_DeleteService (tGATT_IF gatt_if, tBT_UUID *p_svc_uuid,
                                    UINT16 svc_inst);

/*******************************************************************************
** 功能GATTS_StartService
**
** 说明调用此函数以启动GATT服务
**
** 参数gatt_if：服务句柄。p_cback：应用程序服务回调函数。sup_transport:此主要服务支持的传输
**
** 如果成功启动，返回GATT_SUCCESS；否则错误代码。
**
*******************************************************************************/
extern tGATT_STATUS GATTS_StartService (tGATT_IF gatt_if, UINT16 service_handle,
                                        tGATT_TRANSPORT sup_transport);


/*******************************************************************************
** 函数GATTS_StopService
**
** 说明调用此函数以停止服务
**
** 参数service_handle：这是服务的启动句柄
**
** 返回None。
**
*******************************************************************************/
extern void GATTS_StopService (UINT16 service_handle);


/*******************************************************************************
** 函数GATTs_HandleValueIndication
**
** 说明此函数向客户端发送句柄值指示。
**
** 参数conn_id：连接标识符。attr_handle：此句柄值指示的属性句柄。val_len：指定属性值的长度。p_val：指向所指示属性值数据的指针。
**
** 如果成功发送或排队，则返回GATT_SUCCESS；否则错误代码。
**
*******************************************************************************/
extern  tGATT_STATUS GATTS_HandleValueIndication (UINT16 conn_id,
        UINT16 attr_handle,
        UINT16 val_len, UINT8 *p_val);

/*******************************************************************************
** 函数GATTS_HandleValueNotification
**
** 说明此函数向客户端发送句柄值通知。
**
** 参数conn_id：连接标识符。attr_handle：此句柄值指示的属性句柄。val_len：指定属性值的长度。p_val：指向所指示属性值数据的指针。
**
** 如果成功发送，则返回GATT_SUCCESS；否则错误代码。
**
*******************************************************************************/
extern  tGATT_STATUS GATTS_HandleValueNotification (UINT16 conn_id, UINT16 attr_handle,
        UINT16 val_len, UINT8 *p_val);


/*******************************************************************************
** 函数GATTS_SendRsp
**
** 说明此函数将服务器响应发送到客户端。
**
** 参数conn_id：连接标识符。trans_id：事务id状态：响应状态p_msg：指向消息参数结构的指针。
**
** 如果成功发送，则返回GATT_SUCCESS；否则错误代码。
**
*******************************************************************************/
extern  tGATT_STATUS GATTS_SendRsp (UINT16 conn_id,  UINT32 trans_id,
                                    tGATT_STATUS status, tGATTS_RSP *p_msg);


/*******************************************************************************
** 函数GATTS_SetAttributeValue
**
** 说明此函数用于设置属性值。
**
** 参数attr_handle：属性句柄长度：属性长度值：要设置到数据库中属性的值
**
** 如果成功发送，则返回GATT_SUCCESS；否则错误代码。
**
*******************************************************************************/
tGATT_STATUS GATTS_SetAttributeValue(UINT16 attr_handle, UINT16 length, UINT8 *value);


/*******************************************************************************
** 函数GATTS_GetAttributeValue
**
** 说明此函数用于设置属性值。
**
** 参数attr_handle：属性句柄长度：数据库值中的属性值长度：输出的属性值
**
** 如果成功发送，则返回GATT_SUCCESS；否则错误代码。
**
*******************************************************************************/
tGATT_STATUS GATTS_GetAttributeValue(UINT16 attr_handle, UINT16 *length, UINT8 **value);



/*******************************************************************************/
/* GATT配置文件客户端功能*/
/*******************************************************************************/

/*******************************************************************************
** 功能GATTC_ConfigureMTU
**
** 说明调用此函数以配置LE传输上连接的ATT MTU大小。
**
** 参数conn_id：连接标识符。mtu-属性mtu大小。。
**
** 如果命令成功启动，则返回GATT_SUCCESS。
**
*******************************************************************************/
extern tGATT_STATUS GATTC_ConfigureMTU (UINT16 conn_id);

/*******************************************************************************
** 功能GATTC_Discover
**
** 说明调用此函数在ATT服务器上执行查找过程。
**
** 参数conn_id：连接标识符。disc_type：发现类型。p_param：发现需求的参数。
**
** 如果成功接收/发送命令，则返回GATT_SUCCESS。
**
*******************************************************************************/
extern tGATT_STATUS GATTC_Discover (UINT16 conn_id,
                                    tGATT_DISC_TYPE disc_type,
                                    tGATT_DISC_PARAM *p_param );
/*******************************************************************************
** 功能GATTC_Read
**
** 描述调用此函数以从服务器读取属性值。
**
** 参数conn_id：连接标识符。type-属性读取类型。p_read-读取操作参数。
**
** 如果命令成功启动，则返回GATT_SUCCESS。
**
*******************************************************************************/
extern tGATT_STATUS GATTC_Read (UINT16 conn_id, tGATT_READ_TYPE type,
                                tGATT_READ_PARAM *p_read);

/*******************************************************************************
** 函数GATTC_Write
**
** 描述调用此函数以从服务器读取属性值。
**
** 参数conn_id：连接标识符。type-属性写入类型。p_write-写入操作参数。
**
** 如果命令成功启动，则返回GATT_SUCCESS。
**
*******************************************************************************/
extern tGATT_STATUS GATTC_Write (UINT16 conn_id, tGATT_WRITE_TYPE type,
                                 tGATT_VALUE *p_write);


/*******************************************************************************
** 函数GATTC_ExecuteWrite
**
** 描述调用此函数向服务器发送执行写入请求。
**
** 参数conn_id：连接标识符。is_execute-执行或取消准备写入请求
**
** 如果命令成功启动，则返回GATT_SUCCESS。
**
*******************************************************************************/
extern tGATT_STATUS GATTC_ExecuteWrite (UINT16 conn_id, BOOLEAN is_execute);

/*******************************************************************************
** 函数GATTC_SendHandleValueConfirm
**
** 描述调用此函数以发送句柄值确认，作为对来自服务器的句柄值通知的响应。
**
** 参数conn_id：连接标识符。handle：属性确认的句柄。
**
** 如果命令成功启动，则返回GATT_SUCCESS。
**
*******************************************************************************/
extern tGATT_STATUS GATTC_SendHandleValueConfirm (UINT16 conn_id, UINT16 handle);


/*******************************************************************************
** 函数GATT_SetIdleTimeout
**
** 说明此函数（客户端和服务器通用）设置传输连接的空闲超时
**
** 参数bd_addr：目标设备bd地址。idle_tout：超时值（秒）。运输：运输选项。
**
** 返回void
**
*******************************************************************************/
extern void GATT_SetIdleTimeout (BD_ADDR bd_addr, UINT16 idle_tout,
                                 tGATT_TRANSPORT transport);


/*******************************************************************************
** 函数GATT_Register
**
** 说明调用此函数以向GATT注册应用程序
**
** 参数p_app_uuid128：应用程序UUID p_cb_info：回调函数。
**
** 返回0表示错误，否则为向GATT注册的客户端的索引
**
*******************************************************************************/
extern  tGATT_IF GATT_Register (tBT_UUID *p_app_uuid128, const tGATT_CBACK *p_cb_info);

/*******************************************************************************
** 函数GATT_注销
**
** 说明此功能取消了GATT申请的注册。
**
** 参数gatt_if：应用程序接口。
**
** 返回None。
**
*******************************************************************************/
extern void GATT_Deregister (tGATT_IF gatt_if);

/*******************************************************************************
** 函数GATT_StartIf
**
** 说明注册后调用此函数，开始接收注册接口的回调。函数可以调用连接状态和排队通知
**
** 参数gatt_if：应用程序接口。
**
** 返回None
**
*******************************************************************************/
extern  void GATT_StartIf (tGATT_IF gatt_if);

/*******************************************************************************
** 功能GATT_Connect
**
** 说明此功能启动与GATT信道上远程设备的连接。
**
** 参数gatt_if:应用程序接口bd_addr：对等设备地址。bd_addr_type：对等设备地址类型。is_direct：是直接连接还是后台自动连接传输：GATT连接的物理传输（BR/EDR或LE）
**
** 如果连接已启动，则返回TRUE；如果连接启动失败，则返回FALSE。
**
*******************************************************************************/
extern BOOLEAN GATT_Connect (tGATT_IF gatt_if, BD_ADDR bd_addr, tBLE_ADDR_TYPE bd_addr_type,
                             BOOLEAN is_direct, tBT_TRANSPORT transport, BOOLEAN is_aux);


/*******************************************************************************
** 功能GATT_CancelConnect
**
** 说明此函数终止GATT信道上远程设备的连接初始化。
**
** 参数gatt_if：客户端接口。如果0用作无条件断开连接，通常用于直接连接取消。bd_addr：对等设备地址。is_direct：是直接连接还是后台自动连接
**
** 如果连接已启动，则返回TRUE；如果连接启动失败，则返回FALSE。
**
*******************************************************************************/
extern BOOLEAN GATT_CancelConnect (tGATT_IF gatt_if, BD_ADDR bd_addr,
                                   BOOLEAN is_direct);

/*******************************************************************************
** 功能GATT_Disconnect
**
** 说明此功能断开此已注册应用程序的GATT通道。
**
** 参数conn_id：连接标识符。
**
** 如果断开连接，则返回GATT_SUCCESS。
**
*******************************************************************************/
extern tGATT_STATUS GATT_Disconnect (UINT16 conn_id);

/*******************************************************************************
** 函数GATT_SendServiceChangeIndication
**
** 说明此功能用于发送服务更改指示
**
** 参数bd_addr：对等设备地址。
**
** 返回状态。
**
*******************************************************************************/
extern tGATT_STATUS GATT_SendServiceChangeIndication (BD_ADDR bd_addr);

/*******************************************************************************
** 函数GATT_GetConnectionInfor
**
** 说明此函数使用conn_id查找其关联的BD地址和应用程序接口
**
** 参数conn_id：连接id（输入）p_gatt_if：应用程序接口（输出）bd_addr：对等设备地址。（输出）运输：GATT连接的物理运输（BR/EDR或LE）
**
** 如果找到conn_id的逻辑链接信息，则返回TRUE
**
*******************************************************************************/
extern BOOLEAN GATT_GetConnectionInfor(UINT16 conn_id, tGATT_IF *p_gatt_if,
                                       BD_ADDR bd_addr, tBT_TRANSPORT *p_transport);


/*******************************************************************************
** 函数GATT_GetConnIdIfConnected
**
** 说明如果BD地址和应用程序接口的逻辑链接已连接，则此函数查找conn_id
**
** 参数gatt_if:应用程序接口（输入）bd_addr：对等设备地址。（输入）p_conn_id:连接id（输出）传输：GATT连接的物理传输（BR/EDR或LE）
**
** 如果逻辑链接已连接，则返回TRUE
**
*******************************************************************************/
extern BOOLEAN GATT_GetConnIdIfConnected(tGATT_IF gatt_if, BD_ADDR bd_addr,
        UINT16 *p_conn_id, tBT_TRANSPORT transport);


/*******************************************************************************
** 函数GATT_Listen
**
** 说明此功能启动或停止LE广告并侦听连接。
**
** 参数gatt_if:application interface p_bd_addr：侦听特定地址连接，或NULL侦听所有设备连接。start：是直接连接还是后台自动连接
**
** 如果广告已启动，则返回TRUE；如果adv启动失败，则返回FALSE。
**
*******************************************************************************/
extern BOOLEAN GATT_Listen (tGATT_IF gatt_if, BOOLEAN start, BD_ADDR_PTR bd_addr);

/*******************************************************************************
** 函数GATT_ConfigServiceChangeCCC
**
** 说明在远程设备上配置服务更改指示
**
** 返回None。
**
*******************************************************************************/
extern void GATT_ConfigServiceChangeCCC (BD_ADDR remote_bda, BOOLEAN enable,
        tBT_TRANSPORT transport);

#ifdef __cplusplus

}
#endif

#endif  /* GATT_API_H */

