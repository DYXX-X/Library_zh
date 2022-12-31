/******************************************************************************
 * 版权所有（C）2002-2012 Broadcom Corporation
 *
 *  根据Apache许可证2.0版（“许可证”）获得许可；除非符合许可证，否则不得使用此文件。您可以在以下地址获取许可证副本：
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 *  除非适用法律要求或书面同意，否则根据许可证分发的软件是按“原样”分发的，无任何明示或暗示的担保或条件。有关许可证下权限和限制的具体语言，请参阅许可证。
 *
 ******************************************************************************/
#ifndef BTA_HH_API_H
#define BTA_HH_API_H

#include "bta/bta_api.h"
#include "stack/hidh_api.h"
#if defined(BTA_HH_INCLUDED) && (BTA_HH_INCLUDED == TRUE)

#if (defined BTA_HH_LE_INCLUDED && BTA_HH_LE_INCLUDED == TRUE)
#include "stack/gatt_api.h"
#endif

/*****************************************************************************
**  常量和类型定义
*****************************************************************************/
#ifndef BTA_HH_DEBUG
#define BTA_HH_DEBUG    TRUE
#endif

#ifndef BTA_HH_SSR_MAX_LATENCY_DEF
#define BTA_HH_SSR_MAX_LATENCY_DEF  800 /* 500毫秒*/
#endif

#ifndef BTA_HH_SSR_MIN_TOUT_DEF
#define BTA_HH_SSR_MIN_TOUT_DEF     2
#endif

/* BTA HID主机回调事件*/
#define BTA_HH_ENABLE_EVT       0       /* HH已启用*/
#define BTA_HH_DISABLE_EVT      1       /* HH已禁用*/
#define BTA_HH_OPEN_EVT         2       /* 连接已打开*/
#define BTA_HH_CLOSE_EVT        3       /* 连接已关闭*/
#define BTA_HH_GET_RPT_EVT      4       /* BTA_HhGetReport回调*/
#define BTA_HH_SET_RPT_EVT      5       /* BTA_HhSetReport回调*/
#define BTA_HH_GET_PROTO_EVT    6       /* BTA_GetProtoMode回调*/
#define BTA_HH_SET_PROTO_EVT    7       /* BTA_HhSetProtoMode回调*/
#define BTA_HH_GET_IDLE_EVT     8       /* BTA_HhGetIdle返回回调*/
#define BTA_HH_SET_IDLE_EVT     9       /* BTA_HhSetIdle完成回调*/
#define BTA_HH_GET_DSCP_EVT     10      /* 获取报告描述符*/
#define BTA_HH_ADD_DEV_EVT      11      /* 添加设备回调*/
#define BTA_HH_RMV_DEV_EVT      12      /* 删除设备已完成*/
#define BTA_HH_VC_UNPLUG_EVT    13      /* 实际上没有插头*/
#define BTA_HH_DATA_EVT         15
#define BTA_HH_API_ERR_EVT      16      /* 捕捉到API错误*/
#define BTA_HH_UPDATE_SCPP_EVT  17      /* 更新扫描参数完成*/
#define BTA_HH_DATA_IND_EVT     18      /* 中断通道上的数据*/

typedef UINT16 tBTA_HH_EVT;

/* 每种类型设备的应用程序ID（非零）*/
#define BTA_HH_APP_ID_MI            1
#define BTA_HH_APP_ID_KB            2
#define BTA_HH_APP_ID_RMC           3
#define BTA_HH_APP_ID_3DSG          4
#define BTA_HH_APP_ID_JOY           5
#define BTA_HH_APP_ID_GPAD          6
#define BTA_HH_APP_ID_LE            0xff

/* 定义了最小偏移*/
#define BTA_HH_MIN_OFFSET       L2CAP_MIN_OFFSET+1

/* 对于BTA HH的设计，HID_HOST_MAX_DEVICES不能超过15*/
#define BTA_HH_IDX_INVALID      0xff
#define BTA_HH_MAX_KNOWN        HID_HOST_MAX_DEVICES

#if (defined BTA_HH_LE_INCLUDED && BTA_HH_LE_INCLUDED == TRUE)
/* 对于BTA HH的设计，GATT_MAX_PHY_CHANNEL不能超过14*/
#define BTA_HH_LE_MAX_KNOWN     GATT_MAX_PHY_CHANNEL
#define BTA_HH_MAX_DEVICE        (HID_HOST_MAX_DEVICES + GATT_MAX_PHY_CHANNEL)
#else
#define BTA_HH_MAX_DEVICE       HID_HOST_MAX_DEVICES
#endif
/* 无效的设备句柄*/
#define BTA_HH_INVALID_HANDLE   0xff

/* 协议模式类型*/
#define BTA_HH_PROTO_RPT_MODE                   (0x00)
#define BTA_HH_PROTO_BOOT_MODE                  (0x01)
#define BTA_HH_PROTO_UNKNOWN                    (0xff)
typedef UINT8   tBTA_HH_PROTO_MODE;

enum {
    BTA_HH_KEYBD_RPT_ID  =               1,
    BTA_HH_MOUSE_RPT_ID
};
typedef UINT8 tBTA_HH_BOOT_RPT_ID;

/* 设备类型，位掩码*/
#define BTA_HH_DEVT_UNKNOWN      0x00
#define BTA_HH_DEVT_JOS          0x01           /* 操纵杆*/
#define BTA_HH_DEVT_GPD          0x02           /* 游戏板*/
#define BTA_HH_DEVT_RMC          0x03           /* 遥控器*/
#define BTA_HH_DEVT_SED          0x04           /* 传感装置*/
#define BTA_HH_DEVT_DGT          0x05           /* 数字化仪平板电脑*/
#define BTA_HH_DEVT_CDR          0x06           /* 读卡器*/
#define BTA_HH_DEVT_KBD          0x10           /* 键盘*/
#define BTA_HH_DEVT_MIC          0x20           /* 指向装置*/
#define BTA_HH_DEVT_COM          0x30           /* 组合键盘/定点*/
#define BTA_HH_DEVT_OTHER        0x80
typedef UINT8  tBTA_HH_DEVT;

enum {
    BTA_HH_OK,
    BTA_HH_HS_HID_NOT_READY,    /* 握手错误：设备未就绪*/
    BTA_HH_HS_INVALID_RPT_ID,   /* 握手错误：报告ID无效*/
    BTA_HH_HS_TRANS_NOT_SPT,    /* 握手错误：事务不是spt*/
    BTA_HH_HS_INVALID_PARAM,    /* 握手错误：参数无效*/
    BTA_HH_HS_ERROR,            /* 握手错误：未指定的HS错误*/
    BTA_HH_ERR,                 /* 一般BTA HH错误*/
    BTA_HH_ERR_SDP,             /* SDP错误*/
    BTA_HH_ERR_PROTO,           /* SET_Protocol错误，仅用于BTA_HH_OPEN_EVT回调*/

    BTA_HH_ERR_DB_FULL,         /* 设备数据库完全错误，用于BTA_HH_OPEN_EVT/BTA_HH_ADD_DEV_EVT*/
    BTA_HH_ERR_TOD_UNSPT,       /* 不支持的设备类型*/
    BTA_HH_ERR_NO_RES,          /* 系统外资源*/
    BTA_HH_ERR_AUTH_FAILED,     /* 身份验证失败*/
    BTA_HH_ERR_HDL,             /* 连接句柄错误*/
    BTA_HH_ERR_SEC,             /* 加密错误*/
};
typedef UINT8 tBTA_HH_STATUS;


#define BTA_HH_VIRTUAL_CABLE           HID_VIRTUAL_CABLE
#define BTA_HH_NORMALLY_CONNECTABLE    HID_NORMALLY_CONNECTABLE
#define BTA_HH_RECONN_INIT             HID_RECONN_INIT
#define BTA_HH_SDP_DISABLE             HID_SDP_DISABLE
#define BTA_HH_BATTERY_POWER           HID_BATTERY_POWER
#define BTA_HH_REMOTE_WAKE             HID_REMOTE_WAKE
#define BTA_HH_SUP_TOUT_AVLBL          HID_SUP_TOUT_AVLBL
#define BTA_HH_SEC_REQUIRED             HID_SEC_REQUIRED
typedef UINT16 tBTA_HH_ATTR_MASK;

/* 支持的设备类型和相应的应用程序ID*/
typedef struct {
    tBTA_HH_DEVT        tod;        /* 设备类型*/
    UINT8               app_id;     /* 对应的应用程序ID*/
} tBTA_HH_SPT_TOD;

/* 配置结构*/
typedef struct {
    UINT8                max_devt_spt; /* 最大设备类型数spt*/
    tBTA_HH_SPT_TOD     *p_devt_list;  /* 支持的设备类型列表*/
    UINT16               sdp_db_size;
} tBTA_HH_CFG;

enum {
    BTA_HH_RPTT_RESRV,      /* 保留*/
    BTA_HH_RPTT_INPUT,      /* 输入报告*/
    BTA_HH_RPTT_OUTPUT,     /* 输出报告*/
    BTA_HH_RPTT_FEATURE     /* 功能报告*/
};
typedef UINT8 tBTA_HH_RPT_TYPE;

/* BTA_HhSendCtrl（）中使用的HID_CONTROL操作代码
*/
enum {
    BTA_HH_CTRL_NOP         = 0 + HID_PAR_CONTROL_NOP ,/* 从BTE映射*/
    BTA_HH_CTRL_HARD_RESET,                            /* 硬复位*/
    BTA_HH_CTRL_SOFT_RESET,                            /* 软复位*/
    BTA_HH_CTRL_SUSPEND,                               /* 进入暂停状态*/
    BTA_HH_CTRL_EXIT_SUSPEND,                          /* 退出暂停*/
    BTA_HH_CTRL_VIRTUAL_CABLE_UNPLUG                   /* 虚拟拔出*/
};
typedef UINT8 tBTA_HH_TRANS_CTRL_TYPE;

typedef tHID_DEV_DSCP_INFO tBTA_HH_DEV_DESCR;

#define BTA_HH_SSR_PARAM_INVALID       HID_SSR_PARAM_INVALID

/* 远程设备中不存在id DI，tBTA_HH_DEV_DSCP_INFO中的vendor_id将设置为0xffff*/
#define BTA_HH_VENDOR_ID_INVALID       0xffff


/* 报告描述符信息*/
typedef struct {
    UINT16              vendor_id;      /* 供应商ID*/
    UINT16              product_id;     /* 产品ID*/
    UINT16              version;        /* 版本*/
    UINT16              ssr_max_latency;    /* SSR最大延迟，BTA_HH_SSR_PARAM_INVALID（如果未知）*/
    UINT16              ssr_min_tout;       /* SSR最小超时，BTA_HH_SSR_PARAM_INVALID（如果未知）*/
    UINT8               ctry_code;      /*国家代码。*/
#if (defined BTA_HH_LE_INCLUDED && BTA_HH_LE_INCLUDED == TRUE)
#define BTA_HH_LE_REMOTE_WAKE       0x01
#define BTA_HH_LE_NORMAL_CONN       0x02

    UINT8               flag;
#endif
    tBTA_HH_DEV_DESCR   descriptor;
} tBTA_HH_DEV_DSCP_INFO;

/* BTA_HH_OPEN_EVT的回调事件数据*/
typedef struct {
    BD_ADDR         bda;                /* HID设备bd地址*/
    tBTA_HH_STATUS  status;             /* 运行状态*/
    UINT8           handle;             /* 设备手柄*/
    BOOLEAN         is_orig;            /* 指示主机是否启动连接*/
#if (defined BTA_HH_LE_INCLUDED && BTA_HH_LE_INCLUDED == TRUE)
    BOOLEAN         le_hid;             /* 是LE设备吗？*/
    BOOLEAN         scps_supported;     /* 支持扫描参数服务*/
#endif

} tBTA_HH_CONN;

typedef tBTA_HH_CONN tBTA_HH_DEV_INFO;

/* 回调事件数据*/
typedef struct {
    tBTA_HH_STATUS              status;     /* 运行状态*/
    UINT8                       handle;     /* 设备手柄*/
} tBTA_HH_CBDATA;

enum {
    BTA_HH_MOD_CTRL_KEY,
    BTA_HH_MOD_SHFT_KEY,
    BTA_HH_MOD_ALT_KEY,
    BTA_HH_MOD_GUI_KEY,
    BTA_HH_MOD_MAX_KEY
};

/* 已解析的启动模式键盘报告*/
typedef struct {
    UINT8               this_char[6];       /* 虚拟密钥码*/
    BOOLEAN             mod_key[BTA_HH_MOD_MAX_KEY];
    /* ctrl、shift、Alt、GUI*/
    /* 修改键：按下Shift键*/
    /* 修改键：是否按下Ctrl键*/
    /* 修改键：按下Alt键*/
    /* 修改键：GUI向上/向下*/
    BOOLEAN             caps_lock;          /* 大写字母已锁定*/
    BOOLEAN             num_lock;           /* 是否按下数字键*/
} tBTA_HH_KEYBD_RPT;

/* 解析的启动模式鼠标报告*/
typedef struct {
    UINT8               mouse_button;       /* 单击鼠标按钮*/
    INT8                delta_x;            /* 位移x*/
    INT8                delta_y;            /* 位移y*/
} tBTA_HH_MICE_RPT;

/* 已分析的启动报告*/
typedef struct {
    tBTA_HH_BOOT_RPT_ID dev_type;           /* 设备类型报告*/
    union {
        tBTA_HH_KEYBD_RPT keybd_rpt;        /* 键盘报告*/
        tBTA_HH_MICE_RPT mice_rpt;          /* 鼠标报告*/
    } data_rpt;
} tBTA_HH_BOOT_RPT;

/* 握手数据*/
typedef struct {
    tBTA_HH_STATUS  status;                 /* 握手状态*/
    UINT8           handle;                 /* 设备手柄*/
    union {
        tBTA_HH_PROTO_MODE proto_mode;      /* GET_PROTO_EVT：协议模式*/
        BT_HDR *p_rpt_data;                 /* GET_RPT_EVT：报告数据*/
        UINT8 idle_rate;                    /* GET_IDLE_EVT：空闲率*/
    } rsp_data;

} tBTA_HH_HSDATA;


/* 上层发送数据*/
typedef struct {
    tBTA_HH_STATUS status;         /* 握手状态*/
    UINT8 handle;                  /* 设备手柄*/
    UINT8 reason;                  /* 发送数据失败原因*/
} tBTA_HH_API_SENDDATA;

/* 中断通道数据*/
typedef struct {
    tBTA_HH_STATUS status;         /* 握手状态*/
    UINT8 handle;                  /* 设备手柄*/
    tBTA_HH_PROTO_MODE proto_mode; /* 协议模式*/
    BT_HDR *p_data;                /* DATA_EVT：功能报告数据*/
} tBTA_HH_INTDATA;

/* 与HD回调关联的数据的并集*/
typedef union {
    tBTA_HH_DEV_INFO        dev_info;           /* BTA_HH_ADD_DEV_EVT, BTA_HH_RMV_DEV_EVT   */
    tBTA_HH_CONN            conn;               /* BTA_HH_OPEN_EVT      */
    tBTA_HH_CBDATA          dev_status;         /* BTA_HH_CLOSE_EVT, BTA_HH_SET_PROTO_EVT BTA_HH_SET_RPT_EVT BTA_HH_SET_IDLE_EVT BTA_HH_UPDATE_SCPP_EVT */

    tBTA_HH_STATUS          status;             /* BTA_HH_ENABLE_EVT */
    tBTA_HH_DEV_DSCP_INFO   dscp_info;          /* BTA_HH_GET_DSCP_EVT */
    tBTA_HH_HSDATA          hs_data;            /* GET_事务回调BTA_HH_GET_RPT_EVT BTA_HH-GET_PROTO_EVT BTA-HH_GET_IDLE_VT*/
    tBTA_HH_API_SENDDATA    send_data;          /* BTA_HH_DATA_EVT */
    tBTA_HH_INTDATA         int_data;           /* BTA_HH_DATA_IND_EVT */
} tBTA_HH;

/* BTA HH回调函数*/
typedef void (tBTA_HH_CBACK)(tBTA_HH_EVT event, tBTA_HH *p_data);


/*****************************************************************************
**  外部函数声明
*****************************************************************************/
#ifdef __cplusplus
extern "C"
{
#endif

/*******************************************************************************
** 函数BTA_HhRegister
**
** 说明此功能启用HID主机并向较低层注册HID主机。
**
** 返回void
**
*******************************************************************************/
extern void BTA_HhEnable(tBTA_SEC sec_mask, tBTA_HH_CBACK *p_cback);

/*******************************************************************************
** 函数BTA_HhDeregister
**
** 说明当主机即将断电时调用此函数。
**
** 返回void
**
*******************************************************************************/
extern void BTA_HhDisable(void);

/*******************************************************************************
** 功能BTA_HhOpen
**
** 说明调用此函数启动查询并读取响应设备的SDP记录；如果仅找到一个活动HID设备，则连接到设备。
**
** 返回void
**
*******************************************************************************/
extern void BTA_HhOpen (BD_ADDR dev_bda, tBTA_HH_PROTO_MODE mode,
                        tBTA_SEC sec_mask);

/*******************************************************************************
** 功能BTA_HhClose
**
** 说明此功能可断开设备。
**
** 返回void
**
*******************************************************************************/
extern void BTA_HhClose(UINT8 dev_handle);

/*******************************************************************************
** 功能BTA_HhSetProtoMode
**
** 说明此函数在指定的HID句柄处设置协议模式
**
** 返回void
**
*******************************************************************************/
extern void BTA_HhSetProtoMode(UINT8 handle, tBTA_HH_PROTO_MODE t_type);

/*******************************************************************************
** 函数BTA_HhGetProtoMode
**
** 描述此函数获取指定HID设备的协议模式。
**
** 返回void
**
*******************************************************************************/
extern void BTA_HhGetProtoMode(UINT8 dev_handle);
/*******************************************************************************
** 函数BTA_HhSetReport
**
** 说明将SET_REPORT发送到设备。
**
** 返回void
**
*******************************************************************************/
extern void BTA_HhSetReport(UINT8 dev_handle, tBTA_HH_RPT_TYPE r_type,
                            BT_HDR *p_data);

/*******************************************************************************
** 函数BTA_HhGetReport
**
** 说明向HID设备发送GET_REPORT。
**
** 返回void
**
*******************************************************************************/
extern void BTA_HhGetReport(UINT8 dev_handle, tBTA_HH_RPT_TYPE r_type,
                            UINT8 rpt_id, UINT16 buf_size);
/*******************************************************************************
** 函数BTA_HhSetIdle
**
** 描述将SET_IDLE发送到设备。
**
** 返回void
**
*******************************************************************************/
extern void BTA_HhSetIdle(UINT8 dev_handle, UINT16 idle_rate);

/*******************************************************************************
** 函数BTA_HhGetIdle
**
** 说明向HID设备发送GET_IDLE。
**
** 返回void
**
*******************************************************************************/
extern void BTA_HhGetIdle(UINT8 dev_handle);

/*******************************************************************************
** 函数BTA_HhSendCtrl
**
** 说明向HID设备发送HID_CONTROL请求。
**
** 返回void
**
*******************************************************************************/
extern void BTA_HhSendCtrl(UINT8 dev_handle,
                           tBTA_HH_TRANS_CTRL_TYPE c_type);

/*******************************************************************************
** 函数BTA_HhSetIdle
**
** 描述将SET_IDLE发送到设备。
**
** 返回void
**
*******************************************************************************/
extern void BTA_HhSetIdle(UINT8 dev_handle, UINT16 idle_rate);


/*******************************************************************************
** 函数BTA_HhGetIdle
**
** 说明从HID设备发送GET_IDLE。
**
** 返回void
**
*******************************************************************************/
extern void BTA_HhGetIdle(UINT8 dev_handle);

/*******************************************************************************
** 函数BTA_HhSendData
**
** 说明将DATA事务发送到HID设备。
**
** 返回void
**
*******************************************************************************/
extern void BTA_HhSendData(UINT8 dev_handle, BD_ADDR dev_bda, BT_HDR  *p_buf);

/*******************************************************************************
** 函数BTA_HhGetDscpInfo
**
** 说明获取设备的报告描述符
**
** 返回void
**
*******************************************************************************/
extern void BTA_HhGetDscpInfo(UINT8 dev_handle);

/*******************************************************************************
** 函数BTA_HhAddDev
**
** 说明将虚拟有线设备添加到HID主机设备列表中，以管理和分配设备句柄以供将来的API调用，主机应用程序在启动时调用此API以初始化其虚拟有线设备。
**
** 返回void
**
*******************************************************************************/
extern void BTA_HhAddDev(BD_ADDR bda, tBTA_HH_ATTR_MASK attr_mask,
                         UINT8 sub_class, UINT8 app_id,
                         tBTA_HH_DEV_DSCP_INFO dscp_info);
/*******************************************************************************
** 函数BTA_HhRemoveDev
**
** 说明从HID主机设备列表中删除设备。
**
** 返回void
**
*******************************************************************************/
extern void BTA_HhRemoveDev(UINT8 dev_handle );

/*******************************************************************************
** 分析实用程序函数
**
*******************************************************************************/
/*******************************************************************************
** 函数BTA_HhParseBootRpt
**
** 说明此实用程序函数解析引导模式报告。
**
** 返回void
**
*******************************************************************************/
extern void BTA_HhParseBootRpt(tBTA_HH_BOOT_RPT *p_data, UINT8 *p_report,
                               UINT16 report_len);

#if BTA_HH_LE_INCLUDED == TRUE
/*******************************************************************************
** 函数BTA_HhUpdateLeScanParam
**
** 说明如果连接到作为报告主机的LE hid设备，则更新扫描参数。
**
** 返回void
**
*******************************************************************************/
extern void BTA_HhUpdateLeScanParam(UINT8 dev_handle, UINT16 scan_int, UINT16 scan_win);
#endif
/* 测试命令*/
extern void bta_hh_le_hid_read_rpt_clt_cfg(BD_ADDR bd_addr, UINT8 rpt_id);



#ifdef __cplusplus
}
#endif

#endif ///已定义（BTA_HH_INCLUDED）&&（BTA_HH_INCLUDED==TRUE）


#endif  /* BTA_HH_API_H */

