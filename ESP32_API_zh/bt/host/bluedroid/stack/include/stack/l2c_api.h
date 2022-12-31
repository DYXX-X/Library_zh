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

/******************************************************************************
 * 此文件包含L2CAP API定义
 *
 ******************************************************************************/
#ifndef L2C_API_H
#define L2C_API_H

#include <stdbool.h>

#include "common/bt_target.h"
#include "stack/l2cdefs.h"
#include "stack/hcidefs.h"
#include "osi/fixed_queue.h"

/*****************************************************************************
**  常量
*****************************************************************************/

/* 定义L2CAP在缓冲区中需要的最小偏移量。它由HCI类型（1）、len（2）、handle（2）和L2CAP len（1）组成，CID（2）=>9
*/
#define L2CAP_MIN_OFFSET    13     /* 加上控制（2），SDU长度（2）*/

/* PSM广播的最小偏移量需要另外两个字节*/
#define L2CAP_BCST_MIN_OFFSET       11

/* ping结果代码*/
#define L2CAP_PING_RESULT_OK        0       /* Ping回复收到正常*/
#define L2CAP_PING_RESULT_NO_LINK   1       /* 无法设置链接*/
#define L2CAP_PING_RESULT_NO_RESP   2       /* 远程L2CAP未回复*/

/* L2CA_DataWrite（）的结果代码*/
#define L2CAP_DW_FAILED        FALSE
#define L2CAP_DW_SUCCESS       TRUE
#define L2CAP_DW_CONGESTED     2

/* L2CA_SetAclPriority的优先级参数值*/
#define L2CAP_PRIORITY_NORMAL       0
#define L2CAP_PRIORITY_HIGH         1

/* L2CA_SetxPriority的优先级参数值*/
#define L2CAP_CHNL_PRIORITY_HIGH    0
#define L2CAP_CHNL_PRIORITY_MEDIUM  1
#define L2CAP_CHNL_PRIORITY_LOW     2

typedef UINT8 tL2CAP_CHNL_PRIORITY;

/* L2CA_SetChnnlDataRate的Tx/Rx数据速率参数值*/
#define L2CAP_CHNL_DATA_RATE_HIGH       3
#define L2CAP_CHNL_DATA_RATE_MEDIUM     2
#define L2CAP_CHNL_DATA_RATE_LOW        1
#define L2CAP_CHNL_DATA_RATE_NO_TRAFFIC 0

typedef UINT8 tL2CAP_CHNL_DATA_RATE;

/* 数据包标志（保留位2-15）*/
/* 层特定14-15位用于FCR SAR*/
#define L2CAP_FLUSHABLE_MASK        0x0003
#define L2CAP_FLUSHABLE_CH_BASED    0x0000
#define L2CAP_FLUSHABLE_PKT         0x0001
#define L2CAP_NON_FLUSHABLE_PKT     0x0002


/* L2CA_FlushChannel num_to_flush定义*/
#define L2CAP_FLUSH_CHANS_ALL       0xffff
#define L2CAP_FLUSH_CHANS_GET       0x0000


/* 用于报告拥塞的多AV专用CID*/
#define L2CAP_MULTI_AV_CID          0

/* HCI标题块的长度*/
/* HCI报头（4）+SNK计数（1）+FCR位（1）+AV数据长度（2）*/
#define L2CAP_MULTI_AV_HCI_HDR_LEN  8

/* 4字节对齐的填充长度*/
#define L2CAP_MULTI_AV_PADDING_LEN  2

/* 带FCR填充的HCI标头块的长度*/
/* HCI报头（4）+SNK计数（1）+FCR位（1）+AV数据长度（2）+填充（2）*/
#define L2CAP_MULTI_AV_HCI_HDR_LEN_WITH_PADDING 10

/* L2CAP标头块的长度*/
/* HCI报头（4）+L2CAP报头（4个）+填充（4个或控制字（2个）+FCS（2个*/
#define L2CAP_MULTI_AV_L2C_HDR_LEN  12

/* 用于L2CA_SetDesireRole的定义*/
#define L2CAP_ROLE_SLAVE            HCI_ROLE_SLAVE
#define L2CAP_ROLE_MASTER           HCI_ROLE_MASTER
#define L2CAP_ROLE_ALLOW_SWITCH     0x80    /* 设置此位以允许在创建连接时切换*/
#define L2CAP_ROLE_DISALLOW_SWITCH  0x40    /* 将此位设置为不允许在创建连接时切换*/
#define L2CAP_ROLE_CHECK_SWITCH     0xC0


/* 结构tL2CAP_ERTM_INFO中传递的“allowed_modes”字段的值
*/
#define L2CAP_FCR_CHAN_OPT_BASIC    (1 << L2CAP_FCR_BASIC_MODE)
#define L2CAP_FCR_CHAN_OPT_ERTM     (1 << L2CAP_FCR_ERTM_MODE)
#define L2CAP_FCR_CHAN_OPT_STREAM   (1 << L2CAP_FCR_STREAM_MODE)

#define L2CAP_FCR_CHAN_OPT_ALL_MASK (L2CAP_FCR_CHAN_OPT_BASIC | L2CAP_FCR_CHAN_OPT_ERTM | L2CAP_FCR_CHAN_OPT_STREAM)

/* PSM有效性检查。PSM值必须为奇数。此外，必须分配所有PSM值，使最有意义的八位字节的最低有效位等于零。
*/
#define L2C_INVALID_PSM(psm)    (((psm) & 0x0101) != 0x0001)
#define L2C_IS_VALID_PSM(psm)   (((psm) & 0x0101) == 0x0001)
#define L2C_IS_VALID_LE_PSM(psm)   (((psm) > 0x0000) && ((psm) < 0x0100))


/*****************************************************************************
**  类型定义
*****************************************************************************/

typedef struct {
#define L2CAP_FCR_BASIC_MODE    0x00
#define L2CAP_FCR_ERTM_MODE     0x03
#define L2CAP_FCR_STREAM_MODE   0x04

    UINT8  mode;

    UINT8  tx_win_sz;
    UINT8  max_transmit;
    UINT16 rtrans_tout;
    UINT16 mon_tout;
    UINT16 mps;
} tL2CAP_FCR_OPTS;

/* 定义用于保存配置参数的结构。由于参数是可选的，因此每个参数都有一个布尔值来表示其存在或不存在。
*/
typedef struct {
    UINT16      result;                 /* 仅用于确认消息*/
    BOOLEAN     mtu_present;
    UINT16      mtu;
    BOOLEAN     qos_present;
    FLOW_SPEC   qos;
    BOOLEAN     flush_to_present;
    UINT16      flush_to;
    BOOLEAN     fcr_present;
    tL2CAP_FCR_OPTS fcr;
    BOOLEAN     fcs_present;            /* 可选地绕过FCS检查*/
    UINT8       fcs;                    /* 如果希望绕过FCS，则为“0”，否则为“1”*/
    BOOLEAN               ext_flow_spec_present;
    tHCI_EXT_FLOW_SPEC    ext_flow_spec;
    UINT16      flags;                  /* 位0:0-无延续，1-延续*/
} tL2CAP_CFG_INFO;

/* 定义一个结构以保存面向LE L2CAP连接的通道的配置参数。
*/
typedef struct
{
    UINT16  mtu;
    UINT16  mps;
    UINT16  credits;
} tL2CAP_LE_CFG_INFO;


/* L2CAP通道配置字段位图*/
#define L2CAP_CH_CFG_MASK_MTU           0x0001
#define L2CAP_CH_CFG_MASK_QOS           0x0002
#define L2CAP_CH_CFG_MASK_FLUSH_TO      0x0004
#define L2CAP_CH_CFG_MASK_FCR           0x0008
#define L2CAP_CH_CFG_MASK_FCS           0x0010
#define L2CAP_CH_CFG_MASK_EXT_FLOW_SPEC 0x0020

typedef UINT16 tL2CAP_CH_CFG_BITS;

/*********************************
**  回调函数原型
**********************************/

/* 连接指示回调原型。参数是分配给远程设备要连接到远程设备发送的标识符的连接PSM的远程本地CID的BD地址
*/
typedef void (tL2CA_CONNECT_IND_CB) (BD_ADDR, UINT16, UINT16, UINT8);


/* 连接确认回调原型。参数为本地CID结果-0=已连接，非零表示故障原因
*/
typedef void (tL2CA_CONNECT_CFM_CB) (UINT16, UINT16);


/* 连接挂起回调原型。参数为本地CID
*/
typedef void (tL2CA_CONNECT_PND_CB) (UINT16);


/* 配置指示回调原型。参数是分配给连接的本地CID指向配置信息的指针
*/
typedef void (tL2CA_CONFIG_IND_CB) (UINT16, tL2CAP_CFG_INFO *);


/* 配置确认回调原型。参数是分配给连接的本地CID指向配置信息的指针
*/
typedef void (tL2CA_CONFIG_CFM_CB) (UINT16, tL2CAP_CFG_INFO *);


/* 断开指示回调原型。参数为本地CID布尔值，上层是否应对此进行确认
*/
typedef void (tL2CA_DISCONNECT_IND_CB) (UINT16, BOOLEAN);


/* 断开确认回调原型。参数为本地CID结果
*/
typedef void (tL2CA_DISCONNECT_CFM_CB) (UINT16, UINT16);


/* QOS违规指示回调原型。参数为违规设备的BD地址
*/
typedef void (tL2CA_QOS_VIOLATION_IND_CB) (BD_ADDR);


/* 数据接收指示回调原型。参数为缓冲区的本地CID地址
*/
typedef void (tL2CA_DATA_IND_CB) (UINT16, BT_HDR *);


/* 回显响应回调原型。请注意，这不包含在注册信息中，而是作为API的一部分传递给L2CAP，以实际发送回显请求。参数为结果
*/
typedef void (tL2CA_ECHO_RSP_CB) (UINT16);


/* 回调函数原型，用于传递特定于broadcom的回波响应*/
/* 至上层*/
typedef void (tL2CA_ECHO_DATA_CB) (BD_ADDR, UINT16, UINT8 *);


/* 拥塞状态回调原型。此回调是可选的。如果应用程序试图在传输队列已满时发送数据，那么数据无论如何都会被丢弃。参数为：本地CID TRUE（如果拥堵），FALSE（如果未拥堵）
*/
typedef void (tL2CA_CONGESTION_STATUS_CB) (UINT16, BOOLEAN);

/* 已完成事件的数据包数的回调原型。当收到“完成的数据包数”事件时，此回调会通知应用程序。此回调最初是为3DG设备设计的。参数为：peer BD_ADDR
*/
typedef void (tL2CA_NOCP_CB) (BD_ADDR);

/* 传输完整的回调原型。此回调是可选的。如果设置，L2CAP将在发送或刷新数据包时调用它。如果计数为0xFFFF，则表示发送了该CID的所有数据包（仅限eRTM模式）。参数为：发送或丢弃的SDU的本地CID数量
*/
typedef void (tL2CA_TX_COMPLETE_CB) (UINT16, UINT16);

/* 定义应用程序用于向L2CAP注册的结构。此结构包括回调函数。必须提供所有功能，“连接挂起”回调和“拥塞状态”回调除外。
*/
typedef struct {
    tL2CA_CONNECT_IND_CB        *pL2CA_ConnectInd_Cb;
    tL2CA_CONNECT_CFM_CB        *pL2CA_ConnectCfm_Cb;
    tL2CA_CONNECT_PND_CB        *pL2CA_ConnectPnd_Cb;
    tL2CA_CONFIG_IND_CB         *pL2CA_ConfigInd_Cb;
    tL2CA_CONFIG_CFM_CB         *pL2CA_ConfigCfm_Cb;
    tL2CA_DISCONNECT_IND_CB     *pL2CA_DisconnectInd_Cb;
    tL2CA_DISCONNECT_CFM_CB     *pL2CA_DisconnectCfm_Cb;
    tL2CA_QOS_VIOLATION_IND_CB  *pL2CA_QoSViolationInd_Cb;
    tL2CA_DATA_IND_CB           *pL2CA_DataInd_Cb;
    tL2CA_CONGESTION_STATUS_CB  *pL2CA_CongestionStatus_Cb;
    tL2CA_TX_COMPLETE_CB        *pL2CA_TxComplete_Cb;

} tL2CAP_APPL_INFO;

/* 定义应用程序用于创建或接受具有增强重传模式的连接的结构。
*/
typedef struct {
    UINT8       preferred_mode;
    UINT8       allowed_modes;
    UINT16      user_rx_buf_size;
    UINT16      user_tx_buf_size;
    UINT16      fcr_rx_buf_size;
    UINT16      fcr_tx_buf_size;

} tL2CAP_ERTM_INFO;

#define L2CA_REGISTER(a,b,c)        L2CA_Register(a,(tL2CAP_APPL_INFO *)b)
#define L2CA_DEREGISTER(a)          L2CA_Deregister(a)
#define L2CA_CONNECT_REQ(a,b,c,d)   L2CA_ErtmConnectReq(a,b,c)
#define L2CA_CONNECT_RSP(a,b,c,d,e,f,g) L2CA_ErtmConnectRsp(a,b,c,d,e,f)
#define L2CA_CONFIG_REQ(a,b)        L2CA_ConfigReq(a,b)
#define L2CA_CONFIG_RSP(a,b)        L2CA_ConfigRsp(a,b)
#define L2CA_DISCONNECT_REQ(a)      L2CA_DisconnectReq(a)
#define L2CA_DISCONNECT_RSP(a)      L2CA_DisconnectRsp(a)
#define L2CA_DATA_WRITE(a, b)       L2CA_DataWrite(a, b)

/*****************************************************************************
**  外部函数声明
*****************************************************************************/
#ifdef __cplusplus
extern "C"
{
#endif

#if (CLASSIC_BT_INCLUDED == TRUE)
/*******************************************************************************
** 功能L2CA_Register
**
** 说明其他层调用此函数注册L2CAP服务。
**
** 如果出现错误，则返回使用的PSM或零。通常，返回的PSM与传入的PSM相同，但对于到动态PSM的仅传出连接，将返回一个“虚拟”PSM，并应在调用L2CA_ConnectReq（）和BTM_SetSecurityLevel（）时使用。
**
*******************************************************************************/
extern UINT16 L2CA_Register (UINT16 psm, tL2CAP_APPL_INFO *p_cb_info);

/*******************************************************************************
** 函数L2CA_寄存器
**
** 说明其他层调用此函数以注销L2CAP服务。
**
** 返回void
**
*******************************************************************************/
extern void L2CA_Deregister (UINT16 psm);

/*******************************************************************************
** 函数L2CA_AllocatePSM
**
** 说明其他层调用此函数以查找L2CAP服务的未使用PSM。
**
** 返回要使用的PSM。
**
*******************************************************************************/
extern UINT16 L2CA_AllocatePSM(void);

/*******************************************************************************
** 功能L2CA_ConnectReq
**
** 说明高层调用此函数以创建L2CAP连接。请注意，此时未建立连接，但已开始建立连接。当连接建立或失败时，将调用回调函数。
**
** 返回连接的CID，如果无法启动，则返回0
**
*******************************************************************************/
extern UINT16 L2CA_ConnectReq (UINT16 psm, BD_ADDR p_bd_addr);

/*******************************************************************************
** 函数L2CA_ConnectRsp
**
** 说明更高层调用此函数以接受传入的L2CAP连接，他们已收到连接指示回调。
**
** 成功时返回TRUE，失败时返回FALSE
**
*******************************************************************************/
extern BOOLEAN L2CA_ConnectRsp (BD_ADDR p_bd_addr, UINT8 id, UINT16 lcid,
                                UINT16 result, UINT16 status);

/*******************************************************************************
** 功能L2CA_ErtmConnectReq
**
** 说明更高层调用此函数以创建需要使用增强型重传模式的L2CAP连接。请注意，此时未建立连接，但已开始建立连接。当连接建立或失败时，将调用回调函数。
**
** 返回连接的CID，如果无法启动，则返回0
**
*******************************************************************************/
extern UINT16 L2CA_ErtmConnectReq (UINT16 psm, BD_ADDR p_bd_addr,
                                   tL2CAP_ERTM_INFO *p_ertm_info);

// 此函数设置由引用的L2CAP连接的回调例程
// |local_cid |。只能为传出连接修改回调例程
// 由|L2CA_ConnectReq|建立或接受的传入连接|回调|
// 不能为NULL。如果可以更新回调，则此函数返回true，
// 否则为false（例如，未找到|local_cid|）。
bool L2CA_SetConnectionCallbacks(uint16_t local_cid, const tL2CAP_APPL_INFO *callbacks);

/*******************************************************************************
** 函数L2CA_ErtmConnectRsp
**
** 说明更高层调用此函数以接受传入的L2CAP连接，对于该连接，他们已获得连接指示回调，并且更高层希望使用增强型重传模式。
**
** 成功时返回TRUE，失败时返回FALSE
**
*******************************************************************************/
extern BOOLEAN  L2CA_ErtmConnectRsp (BD_ADDR p_bd_addr, UINT8 id, UINT16 lcid,
                                     UINT16 result, UINT16 status,
                                     tL2CAP_ERTM_INFO *p_ertm_info);

/*******************************************************************************
** 函数L2CA_ConfigReq
**
** 说明高层调用此函数发送配置。
**
** 如果发送了配置，则返回TRUE，否则返回FALSE
**
*******************************************************************************/
extern BOOLEAN L2CA_ConfigReq (UINT16 cid, tL2CAP_CFG_INFO *p_cfg);

/*******************************************************************************
** 函数L2CA_ConfigRsp
**
** 说明高层调用此函数以发送配置响应。
**
** 如果发送了配置响应，则返回TRUE，否则返回FALSE
**
*******************************************************************************/
extern BOOLEAN L2CA_ConfigRsp (UINT16 cid, tL2CAP_CFG_INFO *p_cfg);

/*******************************************************************************
** 功能L2CA_DisconnectReq
**
** 说明高层调用此函数以断开通道。
**
** 如果已发送断开连接，则返回TRUE，否则返回FALSE
**
*******************************************************************************/
extern BOOLEAN L2CA_DisconnectReq (UINT16 cid);

/*******************************************************************************
** 函数L2CA_DisconnectRsp
**
** 说明高层调用此功能以确认信道断开。
**
** 返回void
**
*******************************************************************************/
extern BOOLEAN L2CA_DisconnectRsp (UINT16 cid);
#endif  ///CLASSIC_BT_INCLUDED == TRUE

/*******************************************************************************
** 函数L2CA_RegisterLECoc
**
** 说明其他层调用此函数以注册L2CAP面向连接的信道。
**
** 如果出现错误，则返回使用的PSM或零。通常，返回的PSM与传入的PSM相同，但对于到动态PSM的仅传出连接，将返回一个“虚拟”PSM，并应在调用L2CA_ConnectLECocReq（）和BTM_SetSecurityLevel（）时使用。
**
*******************************************************************************/
extern UINT16 L2CA_RegisterLECoc (UINT16 psm, tL2CAP_APPL_INFO *p_cb_info);

/*******************************************************************************
** 函数L2CA_DegisterLECoc
**
** 说明其他层调用此函数以注销面向L2CAP连接的信道。
**
** 返回void
**
*******************************************************************************/
extern void L2CA_DeregisterLECoc (UINT16 psm);

/*******************************************************************************
** 函数L2CA_ConnectLECocReq
**
** 说明高层调用此函数以创建L2CAP LE COC。请注意，此时未建立连接，但已开始建立连接。当连接建立或失败时，将调用回调函数。
**
** 返回连接的CID，如果无法启动，则返回0
**
*******************************************************************************/
extern UINT16 L2CA_ConnectLECocReq (UINT16 psm, BD_ADDR p_bd_addr, tL2CAP_LE_CFG_INFO *p_cfg);

/*******************************************************************************
** 函数L2CA_ConnectLECocRsp
**
** 描述更高层调用此函数以接受传入的L2CAP LE COC连接，他们已收到连接指示回调。
**
** 成功时返回TRUE，失败时返回FALSE
**
*******************************************************************************/
extern BOOLEAN L2CA_ConnectLECocRsp (BD_ADDR p_bd_addr, UINT8 id, UINT16 lcid, UINT16 result,
                                         UINT16 status, tL2CAP_LE_CFG_INFO *p_cfg);

/*******************************************************************************
** 函数L2CA_GetPeerLECocConfig
**
**  描述获取面向LE连接的通道的对等配置。
**
**  返回值：如果对等体已连接，则返回TRUE
**
*******************************************************************************/
extern BOOLEAN L2CA_GetPeerLECocConfig (UINT16 lcid, tL2CAP_LE_CFG_INFO* peer_cfg);

/*******************************************************************************
** 函数L2CA_DataWrite
**
** 说明高层调用此函数来写入数据。
**
** 如果数据被接受，则返回L2CAP_DW_SUCCESS；如果数据被接收，且信道拥塞，则返回FALSE L2CAP_DW0_CONGESTED；如果错误
**
*******************************************************************************/
extern UINT8 L2CA_DataWrite (UINT16 cid, BT_HDR *p_data);

#if (CLASSIC_BT_INCLUDED == TRUE)

/*******************************************************************************
** 函数L2CA_Ping
**
** 说明高层调用此函数以发送回显请求。
**
** 如果发送回显请求，则返回TRUE，否则返回FALSE。
**
*******************************************************************************/
extern BOOLEAN L2CA_Ping (BD_ADDR p_bd_addr, tL2CA_ECHO_RSP_CB *p_cb);

/*******************************************************************************
** 功能L2CA_Echo
**
** 说明高层调用此函数以发送带有应用程序特定数据的回显请求。
**
** 如果发送回显请求，则返回TRUE，否则返回FALSE。
**
*******************************************************************************/
extern BOOLEAN  L2CA_Echo (BD_ADDR p_bd_addr, BT_HDR *p_data, tL2CA_ECHO_DATA_CB *p_callback);
#endif  ///CLASSIC_BT_INCLUDED == TRUE


// 给定本地通道标识符|lcid|，此函数返回绑定的远程
// 通道标识符|rcid|和ACL链接句柄|handle|。如果|lcid|不是
// 已知或无效，则此函数返回false并且不修改值
// 由|rcid|和|handle|指向|rcid|和|handle|可能为NULL。
bool L2CA_GetIdentifiers(uint16_t lcid, uint16_t *rcid, uint16_t *handle);

/*******************************************************************************
** 函数L2CA_SetIdleTimeout
**
** 说明高层调用此函数以设置连接或所有未来连接的空闲超时。“空闲超时”是指连接在没有L2CAP通道的情况下可以保持连接的时间。超时为零意味着当删除最后一个通道时，连接将立即断开。超时0xFFFF表示没有超时。值以秒为单位。
**
** 如果命令成功，则返回TRUE；如果失败，则返回FALSE
**
*******************************************************************************/
extern BOOLEAN L2CA_SetIdleTimeout (UINT16 cid, UINT16 timeout,
                                    BOOLEAN is_global);


/*******************************************************************************
** 函数L2CA_SetIdleTimeoutByBdAddr
**
** 说明高层调用此函数来设置连接的空闲超时。“空闲超时”是指连接在没有L2CAP通道的情况下可以保持连接的时间。超时为零意味着当删除最后一个通道时，连接将立即断开。超时0xFFFF表示没有超时。值以秒为单位。bd_addr是远程bd地址。如果bd_addr=BT_bd_ANY，则所有活动l2cap链路的空闲超时将被更改。
**
** 如果命令成功，则返回TRUE；如果失败，则返回FALSE
**
** 注意：此超时适用于ACL链路上所有活动的逻辑通道。
*******************************************************************************/
extern BOOLEAN L2CA_SetIdleTimeoutByBdAddr(BD_ADDR bd_addr, UINT16 timeout,
        tBT_TRANSPORT transport);


/*******************************************************************************
** 函数L2CA_SetTraceLevel
**
** 说明此函数设置L2CAP的跟踪级别。如果用0xFF值调用，它只读取当前跟踪级别。
**
** 返回新的（当前）跟踪级别
**
*******************************************************************************/
extern UINT8 L2CA_SetTraceLevel (UINT8 trace_level);


/*******************************************************************************
** 函数L2CA_SetDesireRole
**
** 说明此函数设置L2CAP的期望角色。如果新角色是L2CAP_role_ALLOW_SWITCH，则允许打开HciCreateConnection。如果新角色是L2CAP_role_DISALLOW_SWITCH，则不允许打开HciCreateConnection。
**
**              如果新角色是有效角色（HCI_role_MASTER或HCI_role-SLAVE），则所需角色将设置为新值。否则，不会更改。
**
** 返回新（当前）角色
**
*******************************************************************************/
extern UINT8 L2CA_SetDesireRole (UINT8 new_role);
#if (CLASSIC_BT_INCLUDED == TRUE)
/*******************************************************************************
** 函数L2CA_LocalLoopbackReq
**
** 说明此功能为本地环回设置CID
**
** 如果没有，则返回CID 0。
**
*******************************************************************************/
extern UINT16 L2CA_LocalLoopbackReq (UINT16 psm, UINT16 handle, BD_ADDR p_bd_addr);

/*******************************************************************************
** 函数L2CA_FlushChannel
**
** 说明此函数清除特定CID的无、部分或所有排队等待xmission的缓冲区。如果使用L2CAP_FLUSH_CHANS_GET（0）调用，它只返回排队等待CID L2CAP_FLUSH_CHANS_ALL（0xffff）刷新所有缓冲区的缓冲区数。所有其他值指定要刷新的最大缓冲区。
**
** 返回该CID的剩余队列缓冲区数
**
*******************************************************************************/
extern UINT16   L2CA_FlushChannel (UINT16 lcid, UINT16 num_to_flush);


/*******************************************************************************
** 函数L2CA_SetAclPriority
**
** 说明设置ACL通道的传输优先级。（对于初始实现，只有两个值有效。L2CAP_PRIORITY_NORMAL和L2CAP_PORIORITY_HIGH）。
**
** 如果信道有效，则返回TRUE，否则返回FALSE
**
*******************************************************************************/
extern BOOLEAN L2CA_SetAclPriority (BD_ADDR bd_addr, UINT8 priority);

/*******************************************************************************
** 功能L2CA_FlowControl
**
** 说明更高层调用此函数以流控制通道。
**
**                  data_enabled-TRUE数据流，FALSE数据停止
**
** 如果通道有效，则返回TRUE，否则返回FALSE
**
*******************************************************************************/
extern BOOLEAN L2CA_FlowControl (UINT16 cid, BOOLEAN data_enabled);

/*******************************************************************************
** 函数L2CA_SendTestSFrame
**
** 说明高层调用此函数发送测试S帧。
**
** 如果通道有效，则返回TRUE，否则返回FALSE
**
*******************************************************************************/
extern BOOLEAN L2CA_SendTestSFrame (UINT16 cid, UINT8 sup_type,
                                    UINT8 back_track);

/*******************************************************************************
** 函数L2CA_SetxPriority
**
** 说明设置信道的传输优先级。（FCR模式）
**
** 如果信道有效，则返回TRUE，否则返回FALSE
**
*******************************************************************************/
extern BOOLEAN L2CA_SetTxPriority (UINT16 cid, tL2CAP_CHNL_PRIORITY priority);

/*******************************************************************************
** 函数L2CA_RegForNoCPEvt
**
** 说明注册已完成数据包数事件的回调。
**
** 输入参数p_cb-已完成数据包数的回调事件p_bda-远程设备的BT地址
**
** 退换商品
**
*******************************************************************************/
extern BOOLEAN L2CA_RegForNoCPEvt(tL2CA_NOCP_CB *p_cb, BD_ADDR p_bda);

/*******************************************************************************
** 函数L2CA_SetChnlDataRate
**
** 说明设置频道的tx/rx数据速率。
**
** 如果信道有效，则返回TRUE，否则返回FALSE
**
*******************************************************************************/
extern BOOLEAN L2CA_SetChnlDataRate (UINT16 cid, tL2CAP_CHNL_DATA_RATE tx, tL2CAP_CHNL_DATA_RATE rx);

typedef void (tL2CA_RESERVE_CMPL_CBACK) (void);

/*******************************************************************************
** 函数L2CA_SetFlushTimeout
**
** 说明此函数设置ACL-U数据包的基带自动刷新超时。BdAddr：ACL链接的远程BD地址。如果是BT_DB_ANY，则刷新超时将应用于所有ACL链接。FlushTimeout：刷新超时（毫秒）0x0000：无自动刷新L2CAP_No_RETRANMISSION：无重传0x0002-0xFFFE：刷新超时，如果（flush_tout8）+3/5）<=HCI_MAX_AUTO_flush_TOUT（在625us插槽中）。否则，返回FALSE。L2CAP_NO_AUTOMATIC_FLUSH：无自动冲洗
**
** 如果命令成功，则返回TRUE；如果失败，则返回FALSE
**
** 注：此刷新超时适用于ACL链路上所有活动的逻辑通道。
*******************************************************************************/
extern BOOLEAN L2CA_SetFlushTimeout (BD_ADDR bd_addr, UINT16 flush_tout);
#endif  ///CLASSIC_BT_INCLUDED == TRUE

/*******************************************************************************
** 函数L2CA_DataWriteEx
**
** 说明更高层调用此函数以写入具有扩展标志的数据。标志：L2CAP_FLUSHABLE_CH_BASED L2CAP_FRUSHABLE_PKT L2CAP_NON_FLUSHABLE_PKT
**
** 如果数据被接受，则返回L2CAP_DW_SUCCESS；如果数据被接收，且信道拥塞，则返回FALSE L2CAP_DW0_CONGESTED；如果错误
**
*******************************************************************************/
extern UINT8 L2CA_DataWriteEx (UINT16 cid, BT_HDR *p_data, UINT16 flags);

/*******************************************************************************
** 函数L2CA_SetChnlFlusability
**
** 说明高层调用此函数以设置通道可冲洗性标志
**
** 如果找到CID，则返回TRUE，否则返回FALSE
**
*******************************************************************************/
extern BOOLEAN L2CA_SetChnlFlushability (UINT16 cid, BOOLEAN is_flushable);

/*******************************************************************************
** 函数L2CA_GetPeerFeatures
**
**  描述获取对等功能和固定频道图
**
**  参数：对等点指向特征和通道掩码存储区域的BD地址
**
**  返回值：如果对等体已连接，则返回TRUE
**
*******************************************************************************/
extern BOOLEAN L2CA_GetPeerFeatures (BD_ADDR bd_addr, UINT32 *p_ext_feat, UINT8 *p_chnl_mask);

/*******************************************************************************
** 函数L2CA_GetBDAddrbyHandle
**
**  说明获取给定HCI句柄的BD地址
**
**  参数：HCI处理对等方的BD地址
**
**  返回值：如果找到给定句柄的lcb，则返回TRUE，否则返回FALSE
**
*******************************************************************************/
extern BOOLEAN L2CA_GetBDAddrbyHandle (UINT16 handle, BD_ADDR bd_addr);

#if (CLASSIC_BT_INCLUDED == TRUE)

/*******************************************************************************
** 函数L2CA_GetChnlFcrMode
**
**  说明获取通道FCR模式
**
**  参数：本地CID
**
**  返回值：通道模式
**
*******************************************************************************/
extern UINT8 L2CA_GetChnlFcrMode (UINT16 lcid);
#endif  ///CLASSIC_BT_INCLUDED == TRUE


/*******************************************************************************
** UCD回调原型
**
*******************************************************************************/

/* UCD发现。参数为远程数据类型数据的BD地址
*/
#define L2CAP_UCD_INFO_TYPE_RECEPTION   0x01
#define L2CAP_UCD_INFO_TYPE_MTU         0x02

typedef void (tL2CA_UCD_DISCOVER_CB) (BD_ADDR, UINT8, UINT32);

/* 接收到UCD数据。参数是指向数据缓冲区的远程指针的BD地址
*/
typedef void (tL2CA_UCD_DATA_CB) (BD_ADDR, BT_HDR *);

/* 拥塞状态回调原型。此回调是可选的。如果应用程序试图在传输队列已满时发送数据，那么数据无论如何都会被丢弃。参数为：远程BD_ADDR TRUE（如果拥塞），FALSE（如果未拥塞）
*/
typedef void (tL2CA_UCD_CONGESTION_STATUS_CB) (BD_ADDR, BOOLEAN);

/* UCD注册信息（回调地址和PSM）
*/
typedef struct {
    tL2CA_UCD_DISCOVER_CB           *pL2CA_UCD_Discover_Cb;
    tL2CA_UCD_DATA_CB               *pL2CA_UCD_Data_Cb;
    tL2CA_UCD_CONGESTION_STATUS_CB  *pL2CA_UCD_Congestion_Status_Cb;
} tL2CAP_UCD_CB_INFO;

/*******************************************************************************
** 函数L2CA_UcdRegister
**
**  说明在UCD上注册PSM。
**
**  参数：tL2CAP_UCD_CB_INFO
**
**  返回值：如果成功，则返回TRUE
**
*******************************************************************************/
extern BOOLEAN L2CA_UcdRegister ( UINT16 psm, tL2CAP_UCD_CB_INFO *p_cb_info );

/*******************************************************************************
** 函数L2CA_UcdDeregister
**
**  说明在UCD上注销PSM。
**
**  参数：PSM
**
**  返回值：如果成功，则返回TRUE
**
*******************************************************************************/
extern BOOLEAN L2CA_UcdDeregister ( UINT16 psm );

/*******************************************************************************
** 函数L2CA_UcdDiscover
**
**  说明发现远程设备的UCD。
**
**  参数：远程设备的PSM BD_ADDR info_type:L2CAP_UCD_info_type_RECEPTION L2CAP_UCD-info_type_MTU
**
** 返回值：如果成功，则返回TRUE
**
*******************************************************************************/
extern BOOLEAN L2CA_UcdDiscover ( UINT16 psm, BD_ADDR rem_bda, UINT8 info_type );

/*******************************************************************************
** 函数L2CA_UcdDataWrite
**
**  说明将UCD发送到远程设备
**
**  参数：PSM BD指向BT_HDR类型缓冲区的远程指针的地址标志：L2CAP_FLUSHABLE_CH_BASED L2CAP_FRUSHABLE_PKT L2CAP_NON_FLUSHABLE_PKT
**
** 如果数据接受，返回值L2CAP_DW_SUCCESS；如果错误，返回值为L2CAP_DW0_FAILED
**
*******************************************************************************/
extern UINT16 L2CA_UcdDataWrite (UINT16 psm, BD_ADDR rem_bda, BT_HDR *p_buf, UINT16 flags);

/*******************************************************************************
** 函数L2CA_UcdSetIdleTimeout
**
**  说明设置UCD空闲超时。
**
**  参数：BD Addr超时（秒）
**
**  返回值：如果成功，则返回TRUE
**
*******************************************************************************/
extern BOOLEAN L2CA_UcdSetIdleTimeout ( BD_ADDR rem_bda, UINT16 timeout );

/*******************************************************************************
** 功能L2CA_UCDSetTxPriority
**
** 说明设置无连接信道的传输优先级。
**
** 如果信道有效，则返回TRUE，否则返回FALSE
**
*******************************************************************************/
extern BOOLEAN L2CA_UCDSetTxPriority ( BD_ADDR rem_bda, tL2CAP_CHNL_PRIORITY priority );


/*******************************************************************************
** 固定通道回调原型
**
*******************************************************************************/

/* 固定通道已连接和断开。参数为信道BD远程地址TRUE（如果信道已连接），FALSE（如果已断开）连接失败传输原因：物理传输、BR/EDR或LE
*/
typedef void (tL2CA_FIXED_CHNL_CB) (UINT16, BD_ADDR, BOOLEAN, UINT16, tBT_TRANSPORT);

/* 接收到信号数据。参数是带有数据的远程缓冲区指针的通道BD地址
*/
typedef void (tL2CA_FIXED_DATA_CB) (UINT16, BD_ADDR, BT_HDR *);

/* 拥塞状态回调原型。此回调是可选的。如果应用程序试图在传输队列已满时发送数据，那么数据无论如何都会被丢弃。参数为：远程BD_ADDR TRUE（如果拥塞），FALSE（如果未拥塞）
*/
typedef void (tL2CA_FIXED_CONGESTION_STATUS_CB) (BD_ADDR, BOOLEAN);

/* 固定信道注册信息（回调地址和信道配置）
*/
typedef struct {
    tL2CA_FIXED_CHNL_CB    *pL2CA_FixedConn_Cb;
    tL2CA_FIXED_DATA_CB    *pL2CA_FixedData_Cb;
    tL2CA_FIXED_CONGESTION_STATUS_CB *pL2CA_FixedCong_Cb;
    tL2CAP_FCR_OPTS         fixed_chnl_opts;

    UINT16                  default_idle_tout;
    tL2CA_TX_COMPLETE_CB    *pL2CA_FixedTxComplete_Cb; /* 固定通道tx完成回调*/
} tL2CAP_FIXED_CHNL_REG;


#if (L2CAP_NUM_FIXED_CHNLS > 0)
/*******************************************************************************
** 函数L2CA_RegisterFixedChannel
**
**  说明注册固定通道。
**
**  参数：固定频道#频道回调和配置
**
**  返回值：如果注册正常，则返回TRUE
**
*******************************************************************************/
extern BOOLEAN  L2CA_RegisterFixedChannel (UINT16 fixed_cid, tL2CAP_FIXED_CHNL_REG *p_freg);

/*******************************************************************************
** 函数L2CA_ConnectFixedChnl
**
**  说明将固定信令信道连接到远程设备。
**
**  参数：远程BD地址类型的固定CID BD地址
**
**  返回值：如果连接已启动，则返回TRUE
**
*******************************************************************************/
extern BOOLEAN L2CA_ConnectFixedChnl (UINT16 fixed_cid, BD_ADDR bd_addr, tBLE_ADDR_TYPE bd_addr_type, BOOLEAN is_aux);

/*******************************************************************************
** 函数L2CA_SendFixedChnlData
**
**  说明在固定信令信道上写入数据。
**
**  参数：BT_HDR类型缓冲区的远程指针的固定CID BD地址
**
** 如果数据接受，返回值L2CAP_DW_SUCCESS；如果错误，返回值为L2CAP_DW0_FAILED
**
*******************************************************************************/
extern UINT16 L2CA_SendFixedChnlData (UINT16 fixed_cid, BD_ADDR rem_bda, BT_HDR *p_buf);

/*******************************************************************************
** 函数L2CA_RemoveFixedChnl
**
**  说明删除远程设备的固定通道。
**
**  参数：要使用的远程空闲超时的固定CID BD地址（如果不在意，则为0xFFFF）
**
**  返回值：如果信道已删除，则返回TRUE
**
*******************************************************************************/
extern BOOLEAN L2CA_RemoveFixedChnl (UINT16 fixed_cid, BD_ADDR rem_bda);

/*******************************************************************************
** 函数L2CA_SetFixedChannelTout
**
** 说明更高层调用此函数来设置固定信道的空闲超时。“空闲超时”是指连接在没有L2CAP通道的情况下可以保持连接的时间。超时为零意味着当删除最后一个通道时，连接将立即断开。超时0xFFFF表示没有超时。值以秒为单位。bd_addr是远程bd地址。如果bd_addr=BT_bd_ANY，则所有活动l2cap链路的空闲超时将被更改。
**
** 如果命令成功，则返回TRUE；如果失败，则返回FALSE
**
*******************************************************************************/
extern BOOLEAN L2CA_SetFixedChannelTout (BD_ADDR rem_bda, UINT16 fixed_cid, UINT16 idle_tout);

#endif /* (L2CAP_NUM_FIXED_CHNLS > 0) */

#if (CLASSIC_BT_INCLUDED == TRUE)
/*******************************************************************************
** 函数L2CA_GetCurrentConfig
**
** 描述此函数返回L2CAP通道pp_our_cfg的配置：保存的配置选项的指针p_our_cfg_bits：位图中的有效配置pp_peer_cfg：对等方保存的配置参数的指针p_peer_cfg_bits：有效配置
**
** 如果成功，则返回TRUE
**
*******************************************************************************/
extern BOOLEAN L2CA_GetCurrentConfig (UINT16 lcid,
                                      tL2CAP_CFG_INFO **pp_our_cfg,  tL2CAP_CH_CFG_BITS *p_our_cfg_bits,
                                      tL2CAP_CFG_INFO **pp_peer_cfg, tL2CAP_CH_CFG_BITS *p_peer_cfg_bits);
#endif  ///CLASSIC_BT_INCLUDED == TRUE


#if (BLE_INCLUDED == TRUE)
/*******************************************************************************
** 函数L2CA_取消连接请求
**
**  说明取消与BLE设备的挂起连接尝试。
**
**  参数：BD远程地址
**
**  返回值：如果连接被取消，则返回TRUE
**
*******************************************************************************/
extern BOOLEAN L2CA_CancelBleConnectReq (BD_ADDR rem_bda);

/*******************************************************************************
** 函数L2CA_UpdateLeConnParams
**
**  说明更新BLE连接参数。
**
**  参数：BD远程地址
**
**  返回值：如果更新开始，则返回TRUE
**
*******************************************************************************/
extern BOOLEAN L2CA_UpdateBleConnParams (BD_ADDR rem_bdRa, UINT16 min_int,
        UINT16 max_int, UINT16 latency, UINT16 timeout);

/*******************************************************************************
** 函数L2CA_EnableUpdateBleConnParams
**
**  说明更新BLE连接参数。
**
**  参数：远程启用标志的BD地址
**
**  返回值：如果更新开始，则返回TRUE
**
*******************************************************************************/
extern BOOLEAN L2CA_EnableUpdateBleConnParams (BD_ADDR rem_bda, BOOLEAN enable);

/*******************************************************************************
** 函数L2CA_GetBleConRole
**
** 说明此函数返回连接角色。
**
** 返回链接角色。
**
*******************************************************************************/
extern UINT8 L2CA_GetBleConnRole (BD_ADDR bd_addr);
#endif /* (BLE_INCLUDED == TRUE) */

/*******************************************************************************
** 函数L2CA_GetDisconnectReason
**
** 说明此函数返回断开原因代码。
**
**  参数：L2CAP连接的远程物理传输的BD地址（BR/EDR或LE）
**
** 返回断开原因
**
*******************************************************************************/
extern UINT16 L2CA_GetDisconnectReason (BD_ADDR remote_bda, tBT_TRANSPORT transport);

extern BOOLEAN L2CA_CheckIsCongest(UINT16 fixed_cid, BD_ADDR addr);

#define  L2CA_GET_ATT_NUM      0
#define  L2CA_ADD_BTC_NUM      1
#define  L2CA_DECREASE_BTC_NUM 2
#define  L2CA_ADD_BTU_NUM      3
#define  L2CA_DECREASE_BTU_NUM 4
#define  L2CA_BUFF_INI         5
#define  L2CA_BUFF_DEINIT      6

typedef struct {
    UINT16 conn_id;
    UINT16 * get_num;
} tl2c_buff_param_t;


extern void l2ble_update_att_acl_pkt_num(UINT8 type, tl2c_buff_param_t *param);

#ifdef __cplusplus
}
#endif

#endif  /* L2C_API_H */

