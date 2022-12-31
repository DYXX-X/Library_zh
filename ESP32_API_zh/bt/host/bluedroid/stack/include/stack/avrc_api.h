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
 * AVRCP应用程序编程接口
 *
 ******************************************************************************/
#ifndef AVRC_API_H
#define AVRC_API_H
#include "common/bt_target.h"
#include "common/bt_defs.h"
#include "stack/avct_api.h"
#include "stack/sdp_api.h"
#include "stack/avrc_defs.h"
#if (AVRC_INCLUDED == TRUE)
/*****************************************************************************
**  常量
*****************************************************************************/

/* API函数返回值结果代码。*/
#define AVRC_SUCCESS        AVCT_SUCCESS        /* 0函数成功*/
#define AVRC_NO_RESOURCES   AVCT_NO_RESOURCES   /* 1资源不足*/
#define AVRC_BAD_HANDLE     AVCT_BAD_HANDLE     /* 2坏手柄*/
#define AVRC_PID_IN_USE     AVCT_PID_IN_USE     /* 3 PID已在使用*/
#define AVRC_NOT_OPEN       AVCT_NOT_OPEN       /* 4连接未打开*/
#define AVRC_MSG_TOO_BIG    5                   /* 5消息长度超过浏览频道的MTU*/
#define AVRC_FAIL           0x10                /* 0x10一般故障*/
#define AVRC_BAD_PARAM      0x11                /* 0x11错误参数*/

/* 控制角色-与AVCT_TARGET/AVCT_Control相同*/
#define AVRC_CT_TARGET      1                   /* 目标*/
#define AVRC_CT_CONTROL     2                   /* 控制器*/
#define AVRC_CT_PASSIVE     4                   /* 如果发生冲突，允许对方成功*/

/* 连接角色*/
#define AVRC_CONN_INT       AVCT_INT            /* 引发剂，引发剂*/
#define AVRC_CONN_ACP       AVCT_ACP            /* 接受者*/


/* AVRC CTRL事件*/
/* 成功打开连接时，将发送AVRC_OPEN_IND_EVT事件。此事件是响应AVRC_Open（）而发送的。*/
#define AVRC_OPEN_IND_EVT       0

/* 连接关闭时发送AVRC_CLOSE_IND_EVT事件。此事件可能由调用AVRC_Close（）或对等方关闭连接时产生。当通过AVRC_Open（）尝试连接失败时，也会发送此消息。*/
#define AVRC_CLOSE_IND_EVT      1

/* AVRC_CONG_IND_EVT事件表示AVCTP拥塞，无法发送更多消息。*/
#define AVRC_CONG_IND_EVT       2

/* AVRC_UNCONG_IND_EVT事件表示AVCTP未被占用并准备发送消息。*/
#define AVRC_UNCONG_IND_EVT     3

/* 当浏览频道成功打开时，发送AVRC_BROWSE_OPEN_IND_EVT事件。此事件是响应AVRC_Open（）或AVRC_OopenBrowser（）发送的。*/
#define AVRC_BROWSE_OPEN_IND_EVT       4

/* 当浏览频道关闭时，发送AVRC_BROWSE_CLOSE_IND_EVT事件。此事件可能由调用AVRC_Close（）、AVRC_CluseBrowse（）或对等方关闭连接时产生。当通过AVRC_OpenBrowse（）尝试连接失败时，也会发送此消息。*/
#define AVRC_BROWSE_CLOSE_IND_EVT      5

/* AVRC_BROWSE_CONG_IND_EVT事件表示AVCTP浏览频道拥塞，无法发送更多消息。*/
#define AVRC_BROWSE_CONG_IND_EVT       6

/* AVRC_BROWSE_UNCONG_IND_EVT事件表示AVCTP浏览频道未被占用，准备发送消息。*/
#define AVRC_BROWSE_UNCONG_IND_EVT     7

/* AVRC_CMD_TIMEOUT_EVT事件表示等待对等方AVRC命令响应超时*/
#define AVRC_CMD_TIMEOUT_EVT           8

/* 支持的类别*/
#define AVRC_SUPF_CT_CAT1               0x0001      /* 类别1*/
#define AVRC_SUPF_CT_CAT2               0x0002      /* 类别2*/
#define AVRC_SUPF_CT_CAT3               0x0004      /* 类别3*/
#define AVRC_SUPF_CT_CAT4               0x0008      /* 类别4*/
#define AVRC_SUPF_CT_BROWSE             0x0040      /* 浏览*/

#define AVRC_SUPF_TG_CAT1               0x0001      /* 类别1*/
#define AVRC_SUPF_TG_CAT2               0x0002      /* 类别2*/
#define AVRC_SUPF_TG_CAT3               0x0004      /* 类别3*/
#define AVRC_SUPF_TG_CAT4               0x0008      /* 类别4*/
#define AVRC_SUPF_TG_APP_SETTINGS       0x0010      /* 播放机应用程序设置*/
#define AVRC_SUPF_TG_GROUP_NAVI         0x0020      /* 组导航*/
#define AVRC_SUPF_TG_BROWSE             0x0040      /* 浏览*/
#define AVRC_SUPF_TG_MULTI_PLAYER       0x0080      /* 多媒体播放器*/

#define AVRC_META_SUCCESS               AVRC_SUCCESS
#define AVRC_META_FAIL                  AVRC_FAIL
#define AVRC_METADATA_CMD               0x0000
#define AVRC_METADATA_RESP              0x0001



/*****************************************************************************
**  数据类型定义
*****************************************************************************/

/* 此数据类型在AVRC_FindService（）中用于初始化SDP数据库以保存结果服务搜索。*/
typedef struct {
    UINT32              db_len;  /* 发现数据库的长度（字节）*/
    tSDP_DISCOVERY_DB  *p_db;    /* 指向发现数据库的指针*/
    UINT16              num_attr;/* p_attrs中的属性数*/
    UINT16             *p_attrs; /* 属性过滤器。如果为NULL，AVRCP API将属性筛选器设置为ATTR_ID_SERVICE_CLASS_ID_LIST、ATTR_ID_BT_PROFILE_DESC_LIST，ATTR_ID_SUPPORTED_FEATURES、ATTR_ID _SERVICE_NAME和ATTR_ID_PROVIDER_NAME。如果不为NULL，则将输入作为过滤器。*/
} tAVRC_SDP_DB_PARAMS;

/* 调用AVRC_FindService（）API函数后，此回调函数将服务发现信息返回给应用程序。此回调函数的实现必须复制传递给它的p_service_name和p_provider_name参数，因为它们不能保证在回调函数退出后保留。*/
typedef void (tAVRC_FIND_CBACK) (UINT16 status);


/* 这是控件回调函数。此函数将表20中列出的事件传递给应用程序。*/
typedef void (tAVRC_CTRL_CBACK) (UINT8 handle, UINT8 event, UINT16 result,
                                 BD_ADDR peer_addr);


/* 这是消息回调函数。当AVCTP为应用程序准备好消息包时，执行该命令。此回调函数的实现必须复制传递给它的tAVRC_MSG结构，因为它不能保证在回调函数退出后保留。*/
typedef void (tAVRC_MSG_CBACK) (UINT8 handle, UINT8 label, UINT8 opcode,
                                tAVRC_MSG *p_msg);

typedef struct {
    tAVRC_CTRL_CBACK    *p_ctrl_cback;  /* 指向应用程序控件回调的指针*/
    tAVRC_MSG_CBACK     *p_msg_cback;   /* 指向应用程序消息回调的指针*/
    UINT32              company_id;     /* 公司ID*/
    UINT8               conn;           /* 连接角色（发起方/接受方）*/
    UINT8               control;        /* 控制角色（控制/目标）*/
} tAVRC_CONN_CB;



/*****************************************************************************
**  外部函数声明
*****************************************************************************/
#ifdef __cplusplus
extern "C"
{
#endif

/******************************************************************************
** 函数AVRC_AddRecord
**
** 描述调用此函数以构建AVRCP SDP记录。在调用此函数之前，应用程序必须调用SDP_CreateRecord（）来创建SDP记录。
**
**                  输入参数：service_uuid：表示TG（uuid_SERVCLASS_AV_REM_CTRL_TARGET）或CT（uuid_SERVCLASS_AV-REMOTE_CONTROL）
**
**                      p_service_name：指向包含服务名称的以空结尾的字符串的指针。如果未使用服务名称，请将其设置为NULL。
**
**                      p_provider_name：指向包含提供程序名称的以空结尾的字符串的指针。如果未使用提供程序名称，请将其设置为NULL。
**
**                      categories:支持的类别。
**
**                      sdp_handle:sdp_CreateRecord（）返回的sdp句柄。
**
**                  输出参数：无。
**
** 如果成功，则返回AVRC_SUCCESS。AVRC_NO_RESOURCES，如果没有足够的资源来构建SDP记录。
**
******************************************************************************/
extern UINT16 AVRC_AddRecord(UINT16 service_uuid, char *p_service_name,
                             char *p_provider_name, UINT16 categories, UINT32 sdp_handle);

/******************************************************************************
** 功能AVRC_FindService
**
** 说明应用程序调用此功能以执行服务发现并从对等设备检索AVRCP SDP记录信息。返回在服务器上找到的与服务UUID匹配的第一个服务记录的信息。回调函数将在服务发现完成时执行。一次只能有一个对AVRC_FindService（）的未完成调用；应用程序在再次调用函数之前必须等待回调。应用程序负责为发现数据库分配内存。建议发现数据库的大小至少为300字节。应用程序可以在回调函数执行后释放内存。
**
**                  输入参数：service_uuid：表示TG（uuid_SERVCLASS_AV_REM_CTRL_TARGET）或CT（uuid_SERVCLASS_AV-REMOTE_CONTROL）
**
**                      bd_addr:对等设备的bd地址。
**
**                      p_db:SDP发现数据库参数。
**
**                      p_cback：指向回调函数的指针。
**
**                  输出参数：无。
**
** 如果成功，则返回AVRC_SUCCESS。如果发现数据库参数无效，则返回AVRC_BAD_PARAMS。如果没有足够的资源来执行服务搜索，则返回AVRC_NO_RESOURCES。
**
******************************************************************************/
extern UINT16 AVRC_FindService(UINT16 service_uuid, BD_ADDR bd_addr,
                               tAVRC_SDP_DB_PARAMS *p_db, tAVRC_FIND_CBACK *p_cback);

/******************************************************************************
** 功能AVRC_Open
**
** 说明调用此函数以打开与AVCTP的连接。连接可以是发起方或接受方，这取决于p_ccb->stream参数。根据p_ccb->控制参数的确定，连接可以是目标、控制器，也可以是两种角色。根据定义，目标连接是等待来自对等方的传入AVCTP连接的接收器连接。在应用程序通过调用AVRC_Close（）关闭连接之前，连接对应用程序仍然可用。收到AVRC_CLOSE_IND_EVT后，应用程序不需要重新打开连接。
**
**                  输入参数：p_ccb->company_id：公司标识符。
**
**                      p_ccb->p_ctrl_cback：指向控制回调函数的指针。
**
**                      p_ccb->p_msg_cback：指向消息回调函数的指针。
**
**                      p_ccb->conn：AVCTP连接角色。对于启动器连接，此值设置为AVCTP_INT，对于接收器连接，此设置为AVCT _ACP。
**
**                      p_ccb->control：控制角色。对于目标连接，此值设置为AVRC_CT_TARGET；对于控制连接，此设置为AVRC-CT_CONTROL；对于支持这两个角色的连接，此选项设置为（AVRC_CT.TARGET|AVRC_CT-CONTROL）。
**
**                      peer_addr:对等设备的BD地址。此值仅用于启动器连接；对于接收器连接，它可以设置为NULL。
**
**                  输出参数：p_handle：指向句柄的指针。此参数仅在返回AVRC_SUCCESS时有效。
**
** 如果成功，则返回AVRC_SUCCESS。如果没有足够的资源来打开连接，则返回AVRC_NO_RESOURCES。
**
******************************************************************************/
extern UINT16 AVRC_Open(UINT8 *p_handle, tAVRC_CONN_CB *p_ccb,
                        BD_ADDR_PTR peer_addr);

/******************************************************************************
** 功能AVRC_Close
**
** 说明关闭使用AVRC_Open（）打开的连接。当应用程序不再使用连接时调用此函数。
**
**                  输入参数：handle：此连接的句柄。
**
**                  输出参数：无。
**
** 如果成功，则返回AVRC_SUCCESS。AVRC_BAD_HANDLE（如果句柄无效）。
**
******************************************************************************/
extern UINT16 AVRC_Close(UINT8 handle);

/******************************************************************************
** 函数AVRC_OpenBrowse
**
** 说明调用此函数以打开与AVCTP的浏览连接。连接可以是发起者或接受者，这取决于conn_role。该句柄由先前对AVRC_Open的调用返回。
**
** 如果成功，则返回AVRC_SUCCESS。如果没有足够的资源来打开连接，则返回AVRC_NO_RESOURCES。
**
******************************************************************************/
extern UINT16 AVRC_OpenBrowse(UINT8 handle, UINT8 conn_role);

/******************************************************************************
** 函数AVRC_CloseBrowse
**
** 说明关闭使用AVRC_OpenBrowser（）打开的连接。当应用程序不再使用连接时调用此函数。
**
** 如果成功，则返回AVRC_SUCCESS。AVRC_BAD_HANDLE（如果句柄无效）。
**
******************************************************************************/
extern UINT16 AVRC_CloseBrowse(UINT8 handle);

/******************************************************************************
** 函数AVRC_MsgReq
**
** 说明此函数用于将p_pkt中的AVRCP字节流向下发送到AVCTP。
**
**                  预计p_pkt->偏移量至少为AVCT_MSG_offset p_pkt->layerspecific is AVCT_DATA_CTRL or AVCT_DDATA_BROWSE p_pkt-->event is AVRC_OP_VENDOR，AVRC_OP_PASS_THRU or AVRC_OP-BROWSING上述BT_HDR设置由AVRC_Bld函数设置。
**
** 如果成功，则返回AVRC_SUCCESS。AVRC_BAD_HANDLE（如果句柄无效）。
**
******************************************************************************/
extern UINT16 AVRC_MsgReq (UINT8 handle, UINT8 label, UINT8 ctype, BT_HDR *p_pkt);

/******************************************************************************
** 函数AVRC_UnitCmd
**
** 说明向对等设备发送UNIT INFO命令。只能对控制器角色连接调用此函数。来自对等方的任何响应消息都会通过tAVRC_MSG_CBACK回调函数传回。
**
**                  输入参数：handle：此连接的句柄。
**
**                      label：事务标签。
**
**                  输出参数：无。
**
** 如果成功，则返回AVRC_SUCCESS。AVRC_BAD_HANDLE（如果句柄无效）。
**
******************************************************************************/
extern UINT16 AVRC_UnitCmd(UINT8 handle, UINT8 label);

/******************************************************************************
** 函数AVRC_SubCmd
**
** 说明向对等设备发送SUBUNIT INFO命令。只能对控制器角色连接调用此函数。来自对等方的任何响应消息都会通过tAVRC_MSG_CBACK回调函数传回。
**
**                  输入参数：handle：此连接的句柄。
**
**                      label：事务标签。
**
**                      page：指定请求子单元类型表的哪个部分。对于AVRCP，通常为零。值范围为0-7。
**
**                  输出参数：无。
**
** 如果成功，则返回AVRC_SUCCESS。AVRC_BAD_HANDLE（如果句柄无效）。
**
******************************************************************************/
extern UINT16 AVRC_SubCmd(UINT8 handle, UINT8 label, UINT8 page);


/******************************************************************************
** 函数AVRC_PassCmd
**
** 说明向对等设备发送“通过”命令。只能对控制器角色连接调用此函数。来自对等方的任何响应消息都会通过tAVRC_MSG_CBACK回调函数传回。
**
**                  输入参数：handle：此连接的句柄。
**
**                      label：事务标签。
**
**                      p_msg：指向“通过”消息结构的指针。
**
**                  输出参数：无。
**
** 如果成功，则返回AVRC_SUCCESS。AVRC_BAD_HANDLE（如果句柄无效）。
**
******************************************************************************/
extern UINT16 AVRC_PassCmd(UINT8 handle, UINT8 label, tAVRC_MSG_PASS *p_msg);

/******************************************************************************
** 函数AVRC_PassRsp
**
** 说明向对等设备发送“通过”响应。只能对目标角色连接调用此函数。当通过tAVRC_MSG_CBACK回调函数从对等端接收到PASS THROUGH命令消息时，必须调用此函数。
**
**                  输入参数：handle：此连接的句柄。
**
**                      label：事务标签。必须与回调函数中随命令消息传递的值相同。
**
**                      p_msg：指向“通过”消息结构的指针。
**
**                  输出参数：无。
**
** 如果成功，则返回AVRC_SUCCESS。AVRC_BAD_HANDLE（如果句柄无效）。
**
******************************************************************************/
extern UINT16 AVRC_PassRsp(UINT8 handle, UINT8 label, tAVRC_MSG_PASS *p_msg);


/******************************************************************************
** 函数AVRC_VendorCmd
**
** 说明向对等设备发送厂商依赖命令。只能对控制器角色连接调用此函数。来自对等方的任何响应消息都会通过tAVRC_MSG_CBACK回调函数传回。
**
**                  输入参数：handle：此连接的句柄。
**
**                      label：事务标签。
**
**                      p_msg：指向供应商依赖消息结构的指针。
**
**                  输出参数：无。
**
** 如果成功，则返回AVRC_SUCCESS。AVRC_BAD_HANDLE（如果句柄无效）。
**
******************************************************************************/
extern UINT16 AVRC_VendorCmd(UINT8  handle, UINT8  label, tAVRC_MSG_VENDOR *p_msg);


/******************************************************************************
** 函数AVRC_VendorRsp
**
** 说明向对等设备发送供应商依赖响应。只能对目标角色连接调用此函数。当通过tAVRC_MSG_CBACK回调函数从对等端接收到厂商依赖命令消息时，必须调用此函数。
**
**                  输入参数：handle：此连接的句柄。
**
**                      label：事务标签。必须与回调函数中随命令消息传递的值相同。
**
**                      p_msg：指向供应商依赖消息结构的指针。
**
**                  输出参数：无。
**
** 如果成功，则返回AVRC_SUCCESS。AVRC_BAD_HANDLE（如果句柄无效）。
**
******************************************************************************/
extern UINT16 AVRC_VendorRsp(UINT8  handle, UINT8  label, tAVRC_MSG_VENDOR *p_msg);


/******************************************************************************
** 函数AVRC_SetTraceLevel
**
** 说明设置AVRC的跟踪级别。如果传递了0xff，则返回当前跟踪级别。
**
**                  输入参数：new_level：将AVRC跟踪设置为：0xff的级别返回当前设置。0—关闭跟踪。>=1-错误。>=2-警告。>=3-API。>=4-事件。>=5-调试。
**
** 如果输入参数为0xff，则返回新跟踪级别或当前跟踪级别。
**
******************************************************************************/
extern UINT8 AVRC_SetTraceLevel (UINT8 new_level);

/*******************************************************************************
** 功能AVRC_Init
**
** 说明在堆栈启动时调用此函数以分配控制块（如果使用动态内存），并初始化控制块和跟踪级别。
**
** 退货状态
**
*******************************************************************************/
extern bt_status_t AVRC_Init(void);

/*******************************************************************************
** 函数AVRC_Dinit
**
** 说明在堆栈快照时调用此函数以释放控制块（如果使用动态内存），并取消初始化控制块和跟踪级别。
**
** 返回void
**
*******************************************************************************/
extern void AVRC_Deinit(void);

/*******************************************************************************
** 函数AVRC_ParsCommand
**
** 说明此函数用于解析接收到的命令。
**
** 如果p_data中的消息解析成功，则返回AVRC_STS_NO_ERROR。否则，AVRCP 1.4定义的错误代码
**
*******************************************************************************/
extern tAVRC_STS AVRC_ParsCommand (tAVRC_MSG *p_msg, tAVRC_COMMAND *p_result,
                                   UINT8 *p_buf, UINT16 buf_len);

/*******************************************************************************
** 函数AVRC_ParsResponse
**
** 说明此函数用于解析接收到的响应。
**
** 如果p_data中的消息解析成功，则返回AVRC_STS_NO_ERROR。否则，AVRCP 1.4定义的错误代码
**
*******************************************************************************/
extern tAVRC_STS AVRC_ParsResponse (tAVRC_MSG *p_msg, tAVRC_RESPONSE *p_result);

/*******************************************************************************
** 函数AVRC_BldCommand
**
** 说明此函数将给定的AVRCP命令构建到给定的GKI缓冲区
**
** 如果命令生成成功，则返回AVRC_STS_NO_ERROR。否则返回错误代码。
**
*******************************************************************************/
extern tAVRC_STS AVRC_BldCommand( tAVRC_COMMAND *p_cmd, BT_HDR **pp_pkt);

/*******************************************************************************
** 函数AVRC_BldResponse
**
** 说明此函数将给定的AVRCP响应构建到给定的GKI缓冲区
**
** 如果响应生成成功，则返回AVRC_STS_NO_ERROR。否则返回错误代码。
**
*******************************************************************************/
extern tAVRC_STS AVRC_BldResponse( UINT8 handle, tAVRC_RESPONSE *p_rsp, BT_HDR **pp_pkt);

/**************************************************************************
** 函数AVRC_IsValidAvcType
**
** 说明检查是否指定了正确的AVC类型
**
** 如果有效，则返回TRUE
**
**
*******************************************************************************/
extern BOOLEAN AVRC_IsValidAvcType(UINT8 pdu_id, UINT8 avc_type);

/*******************************************************************************
** 函数AVRC_IsValidPlayerAttr
**
** 说明检查给定的属性值是否有效
**
** 如果有效，则返回TRUE
**
*******************************************************************************/
extern BOOLEAN AVRC_IsValidPlayerAttr(UINT8 attr);

#ifdef __cplusplus
}
#endif

#endif  ///AVRC_INCLUDED == TRUE


#endif /* AVRC_API_H */

