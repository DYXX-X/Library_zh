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

/******************************************************************************
 * 此文件包含HID协议定义
 *
 ******************************************************************************/

#ifndef HIDDEFS_H
#define HIDDEFS_H
#include "common/bt_target.h"

#if (HID_HOST_INCLUDED == TRUE || HID_DEV_INCLUDED == TRUE)

#if (SDP_INCLUDED == TRUE)
#include "stack/sdp_api.h"
#endif    ///SDP_INCLUDED == TRUE
/*
** tHID_STATUS：HID结果代码，由HID、设备和主机函数返回。
*/
enum {
    HID_SUCCESS,
    HID_ERR_NOT_REGISTERED,
    HID_ERR_ALREADY_REGISTERED,
    HID_ERR_NO_RESOURCES,
    HID_ERR_NO_CONNECTION,
    HID_ERR_INVALID_PARAM,
    HID_ERR_UNSUPPORTED,
    HID_ERR_UNKNOWN_COMMAND,
    HID_ERR_CONGESTED,
    HID_ERR_CONN_IN_PROCESS,
    HID_ERR_ALREADY_CONN,
    HID_ERR_DISCONNECTING,
    HID_ERR_SET_CONNABLE_FAIL,
    /* 设备特定错误代码*/
    HID_ERR_HOST_UNKNOWN,
    HID_ERR_L2CAP_FAILED,
    HID_ERR_AUTH_FAILED,
    HID_ERR_SDP_BUSY,
    HID_ERR_GATT,

    HID_ERR_INVALID = 0xFF
};

typedef UINT8 tHID_STATUS;

#define    HID_L2CAP_CONN_FAIL (0x0100) /* 已尝试连接但失败*/
#define    HID_L2CAP_REQ_FAIL  (0x0200)  /* L2CAP_ConnectReq API失败*/
#define    HID_L2CAP_CFG_FAIL  (0x0400) /* L2CAP配置被对等方拒绝*/



/* 定义HID事务类型
*/
#define HID_TRANS_HANDSHAKE     (0)
#define HID_TRANS_CONTROL       (1)
#define HID_TRANS_GET_REPORT    (4)
#define HID_TRANS_SET_REPORT    (5)
#define HID_TRANS_GET_PROTOCOL  (6)
#define HID_TRANS_SET_PROTOCOL  (7)
#define HID_TRANS_GET_IDLE      (8)
#define HID_TRANS_SET_IDLE      (9)
#define HID_TRANS_DATA          (10)
#define HID_TRANS_DATAC         (11)

#define HID_GET_TRANS_FROM_HDR(x) ((x >> 4) & 0x0f)
#define HID_GET_PARAM_FROM_HDR(x) (x & 0x0f)
#define HID_BUILD_HDR(t,p)  (UINT8)((t << 4) | (p & 0x0f))


/* 握手的参数
*/
#define HID_PAR_HANDSHAKE_RSP_SUCCESS               (0)
#define HID_PAR_HANDSHAKE_RSP_NOT_READY             (1)
#define HID_PAR_HANDSHAKE_RSP_ERR_INVALID_REP_ID    (2)
#define HID_PAR_HANDSHAKE_RSP_ERR_UNSUPPORTED_REQ   (3)
#define HID_PAR_HANDSHAKE_RSP_ERR_INVALID_PARAM     (4)
#define HID_PAR_HANDSHAKE_RSP_ERR_UNKNOWN           (14)
#define HID_PAR_HANDSHAKE_RSP_ERR_FATAL             (15)


/* 控制参数
*/
#define HID_PAR_CONTROL_NOP                         (0)
#define HID_PAR_CONTROL_HARD_RESET                  (1)
#define HID_PAR_CONTROL_SOFT_RESET                  (2)
#define HID_PAR_CONTROL_SUSPEND                     (3)
#define HID_PAR_CONTROL_EXIT_SUSPEND                (4)
#define HID_PAR_CONTROL_VIRTUAL_CABLE_UNPLUG        (5)


/* get、set、data中的不同报告类型
*/
#define HID_PAR_REP_TYPE_MASK                       (0x03)
#define HID_PAR_REP_TYPE_OTHER                      (0x00)
#define HID_PAR_REP_TYPE_INPUT                      (0x01)
#define HID_PAR_REP_TYPE_OUTPUT                     (0x02)
#define HID_PAR_REP_TYPE_FEATURE                    (0x03)

/* 获取报告的参数
*/

/* 报告ID后的缓冲区大小（以两个字节为单位）*/
#define HID_PAR_GET_REP_BUFSIZE_FOLLOWS             (0x08)


/* 协议类型参数
*/
#define HID_PAR_PROTOCOL_MASK                       (0x01)
#define HID_PAR_PROTOCOL_REPORT                     (0x01)
#define HID_PAR_PROTOCOL_BOOT_MODE                  (0x00)

#define HID_PAR_REP_TYPE_MASK                       (0x03)

/* SDP记录中的描述符类型
*/
#define HID_SDP_DESCRIPTOR_REPORT                   (0x22)
#define HID_SDP_DESCRIPTOR_PHYSICAL                 (0x23)

typedef struct desc_info {
    UINT16 dl_len;
    UINT8 *dsc_list;
} tHID_DEV_DSCP_INFO;

#define HID_SSR_PARAM_INVALID    0xffff

typedef struct sdp_info {
    char svc_name[HID_MAX_SVC_NAME_LEN];   /*服务名称*/
    char svc_descr[HID_MAX_SVC_DESCR_LEN]; /*服务描述*/
    char prov_name[HID_MAX_PROV_NAME_LEN]; /*提供商名称。*/
    UINT16    rel_num;    /*版本号*/
    UINT16    hpars_ver;  /*HID解析器版本。*/
    UINT16    ssr_max_latency; /* 如果未使用HID_SSR_PARAM_INVALID，则为HIDSSRHostMaxLatency值*/
    UINT16    ssr_min_tout; /* 如果未使用HID_SSR_PARAM_INVALID，则HIDSSRHostMinTimeout值**/
    UINT8     sub_class;    /*设备子类。*/
    UINT8     ctry_code;     /*国家代码。*/
    UINT16    sup_timeout;/* 监控超时*/

    tHID_DEV_DSCP_INFO  dscp_info;   /* 要在SDP记录中设置的描述符列表和报告列表。如果HID_DEV_USE_GLB_SDP_REC设置为FALSE，则使用此参数。*/
#if(SDP_INCLUDED == TRUE)
    tSDP_DISC_REC       *p_sdp_layer_rec;
#endif  ///SDP_INCLUDED == TRUE
} tHID_DEV_SDP_INFO;

#endif  ///HID_HOST_INCLUDED == TRUE
#endif

