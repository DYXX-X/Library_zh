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
 * 此文件包含内部使用的SDP定义
 *
 ******************************************************************************/

#ifndef  SDP_INT_H
#define  SDP_INT_H

#include "common/bt_target.h"
#include "common/bt_defs.h"
#include "stack/sdp_api.h"
#include "stack/l2c_api.h"
#include "osi/list.h"

#if (SDP_INCLUDED == TRUE)
/* 连续长度-我们使用2字节的偏移量*/
#define SDP_CONTINUATION_LEN        2
#define SDP_MAX_CONTINUATION_LEN    16          /* 根据规范*/

/* 超时定义。*/
#define SDP_INACT_TIMEOUT       30              /* 非活动超时*/


/* 定义“流出”默认值。*/
#define  SDP_OFLOW_QOS_FLAG                 0
#define  SDP_OFLOW_SERV_TYPE                0
#define  SDP_OFLOW_TOKEN_RATE               0
#define  SDP_OFLOW_TOKEN_BUCKET_SIZE        0
#define  SDP_OFLOW_PEAK_BANDWIDTH           0
#define  SDP_OFLOW_LATENCY                  0
#define  SDP_OFLOW_DELAY_VARIATION          0

/* 定义流入默认值。*/
#define  SDP_IFLOW_QOS_FLAG                 0
#define  SDP_IFLOW_SERV_TYPE                0
#define  SDP_IFLOW_TOKEN_RATE               0
#define  SDP_IFLOW_TOKEN_BUCKET_SIZE        0
#define  SDP_IFLOW_PEAK_BANDWIDTH           0
#define  SDP_IFLOW_LATENCY                  0
#define  SDP_IFLOW_DELAY_VARIATION          0

#define  SDP_LINK_TO                        0

/* 定义设备通知的类型。*/
/* （查询扫描和页面扫描）*/
#define  SDP_DEVICE_NOTI_LEN                sizeof (BT_HDR) +           \
                                            HCIC_PREAMBLE_SIZE +        \
                                            HCIC_PARAM_SIZE_WRITE_PARAM1

#define  SDP_DEVICE_NOTI_FLAG               0x03

/* 定义协议数据单元（PDU）类型。
*/
#define  SDP_PDU_ERROR_RESPONSE                 0x01
#define  SDP_PDU_SERVICE_SEARCH_REQ             0x02
#define  SDP_PDU_SERVICE_SEARCH_RSP             0x03
#define  SDP_PDU_SERVICE_ATTR_REQ               0x04
#define  SDP_PDU_SERVICE_ATTR_RSP               0x05
#define  SDP_PDU_SERVICE_SEARCH_ATTR_REQ        0x06
#define  SDP_PDU_SERVICE_SEARCH_ATTR_RSP        0x07

/* 每个序列支持的最大UUID和属性*/
#define     MAX_UUIDS_PER_SEQ       8
#define     MAX_ATTR_PER_SEQ        8

/* 我们支持任何属性的最大长度*/
// btla特定++
#ifdef SDP_MAX_ATTR_LEN
#define MAX_ATTR_LEN SDP_MAX_ATTR_LEN
#else
#define     MAX_ATTR_LEN            256
#endif
// btla特定--

/* 内部UUID序列表示*/
typedef struct {
    UINT16     len;
    UINT8      value[MAX_UUID_SIZE];
} tUID_ENT;

typedef struct {
    UINT16      num_uids;
    tUID_ENT    uuid_entry[MAX_UUIDS_PER_SEQ];
} tSDP_UUID_SEQ;


/* 内部属性序列定义*/
typedef struct {
    UINT16      start;
    UINT16      end;
} tATT_ENT;

typedef struct {
    UINT16      num_attr;
    tATT_ENT    attr_entry[MAX_ATTR_PER_SEQ];
} tSDP_ATTR_SEQ;


/* 定义SDP数据库记录的属性元素*/
typedef struct {
    UINT32  len;           /* 条目中的字节数*/
    UINT8   *value_ptr;    /* 指向attr_pad*/
    UINT16  id;
    UINT8   type;
} tSDP_ATTRIBUTE;

/* SDP记录由一个句柄和一个或多个属性组成*/
typedef struct {
    UINT32              record_handle;
    UINT32              free_pad_ptr;
    UINT16              num_attributes;
    tSDP_ATTRIBUTE      attribute[SDP_MAX_REC_ATTR];
    UINT8               attr_pad[SDP_MAX_PAD_LEN];
} tSDP_RECORD;


/* 定义SDP数据库*/
typedef struct {
    UINT32         di_primary_handle;       /* 设备ID主记录，如果不存在则为NULL*/
    UINT16         num_records;
    list_t         *p_record_list;
} tSDP_DB;

enum {
    SDP_IS_SEARCH,
    SDP_IS_ATTR_SEARCH,
};

#if SDP_SERVER_ENABLED == TRUE
/* SDP服务器响应的继续信息*/
typedef struct {
    UINT16            next_attr_index; /* 下一个连续响应的属性索引*/
    UINT16            next_attr_start_id;  /* 下一个连续响应中属性索引的开始属性id*/
    tSDP_RECORD       *prev_sdp_rec; /* 响应中完全发送的最后一条sdp记录*/
    BOOLEAN           last_attr_seq_desc_sent; /* 之前是否发送了属性序列长度*/
    UINT16            attr_offset; /* 属性内的偏移量，以保持响应中部分属性的trak*/
} tSDP_CONT_INFO;
#endif  /* SDP_SERVER_ENABLED == TRUE */

/* 定义SDP连接控制块*/
typedef struct {
#define SDP_STATE_IDLE              0
#define SDP_STATE_CONN_SETUP        1
#define SDP_STATE_CFG_SETUP         2
#define SDP_STATE_CONNECTED         3
    UINT8             con_state;

#define SDP_FLAGS_IS_ORIG           0x01
#define SDP_FLAGS_HIS_CFG_DONE      0x02
#define SDP_FLAGS_MY_CFG_DONE       0x04
    UINT8             con_flags;

    BD_ADDR           device_address;
    TIMER_LIST_ENT    timer_entry;
    UINT16            rem_mtu_size;
    UINT16            connection_id;
    UINT16            list_len;                 /* GKI缓冲区中的响应长度*/
    UINT8             *rsp_list;                /* 指向GKI缓冲区保持响应的指针*/

#if SDP_CLIENT_ENABLED == TRUE
    tSDP_DISCOVERY_DB *p_db;                    /* 要将信息保存到的数据库*/
    tSDP_DISC_CMPL_CB *p_cb;                    /* 发现的回调已完成*/
    tSDP_DISC_CMPL_CB2 *p_cb2;                   /* 发现回调与用户数据一起完成*/
    void               *user_data;              /* 背负式用户数据*/
    UINT32            handles[SDP_MAX_DISC_SERVER_RECS]; /* 发现的服务器记录句柄*/
    UINT16            num_handles;              /* 服务器句柄数*/
    UINT16            cur_handle;               /* 正在处理的当前句柄*/
    UINT16            transaction_id;
    UINT16            disconnect_reason;        /* 断开连接原因*/
#if (defined(SDP_BROWSE_PLUS) && SDP_BROWSE_PLUS == TRUE)
    UINT16            cur_uuid_idx;
#endif

#define SDP_DISC_WAIT_CONN          0
#define SDP_DISC_WAIT_HANDLES       1
#define SDP_DISC_WAIT_ATTR          2
#define SDP_DISC_WAIT_SEARCH_ATTR   3
#define SDP_DISC_WAIT_CANCEL        5

    UINT8             disc_state;
    UINT8             is_attr_search;
#endif  /* SDP_CLIENT_ENABLED == TRUE */

#if SDP_SERVER_ENABLED == TRUE
    UINT16            cont_offset;              /* 服务器响应中的连续状态数据*/
    tSDP_CONT_INFO    cont_info;                /* 用于保存服务器响应的延续信息的结构*/
#endif  /* SDP_SERVER_ENABLED == TRUE */

} tCONN_CB;


/*  主SDP控制块*/
typedef struct {
    tL2CAP_CFG_INFO   l2cap_my_cfg;             /* 我的L2CAP配置*/
    tCONN_CB          ccb[SDP_MAX_CONNECTIONS];
#if SDP_SERVER_ENABLED == TRUE
    tSDP_DB           server_db;
#endif
    tL2CAP_APPL_INFO  reg_info;                 /* L2CAP注册信息*/
    UINT16            max_attr_list_size;       /* 要使用的最大属性列表大小*/
    UINT16            max_recs_per_search;      /* 每个seaarch需要的最大记录数*/
    UINT8             trace_level;
} tSDP_CB;

#ifdef __cplusplus
extern "C" {
#endif
/* 全球SDP数据*/
#if SDP_DYNAMIC_MEMORY == FALSE
extern tSDP_CB  sdp_cb;
#else
extern tSDP_CB *sdp_cb_ptr;
#define sdp_cb (*sdp_cb_ptr)
#endif

#ifdef __cplusplus
}
#endif

/* sdp_main提供的函数。c*/
extern void     sdp_init (void);
extern void     sdp_deinit (void);
extern void     sdp_disconnect (tCONN_CB *p_ccb, UINT16 reason);

#if (defined(SDP_DEBUG) && SDP_DEBUG == TRUE)
extern UINT16 sdp_set_max_attr_list_size (UINT16 max_size);
#endif

/* sdp_conn.c提供的函数
*/
extern void sdp_conn_rcv_l2e_conn_ind (BT_HDR *p_msg);
extern void sdp_conn_rcv_l2e_conn_cfm (BT_HDR *p_msg);
extern void sdp_conn_rcv_l2e_disc (BT_HDR *p_msg);
extern void sdp_conn_rcv_l2e_config_ind (BT_HDR *p_msg);
extern void sdp_conn_rcv_l2e_config_cfm (BT_HDR *p_msg);
extern void sdp_conn_rcv_l2e_conn_failed (BT_HDR *p_msg);
extern void sdp_conn_rcv_l2e_connected (BT_HDR *p_msg);
extern void sdp_conn_rcv_l2e_conn_failed (BT_HDR *p_msg);
extern void sdp_conn_rcv_l2e_data (BT_HDR *p_msg);
extern void sdp_conn_timeout (tCONN_CB *p_ccb);

extern tCONN_CB *sdp_conn_originate (UINT8 *p_bd_addr);

/* sdp_utils.c提供的函数
*/
extern tCONN_CB *sdpu_find_ccb_by_cid (UINT16 cid);
extern tCONN_CB *sdpu_find_ccb_by_db (tSDP_DISCOVERY_DB *p_db);
extern tCONN_CB *sdpu_allocate_ccb (void);
extern void      sdpu_release_ccb (tCONN_CB *p_ccb);

extern UINT8    *sdpu_build_attrib_seq (UINT8 *p_out, UINT16 *p_attr, UINT16 num_attrs);
extern UINT8    *sdpu_build_attrib_entry (UINT8 *p_out, tSDP_ATTRIBUTE *p_attr);
extern void      sdpu_build_n_send_error (tCONN_CB *p_ccb, UINT16 trans_num, UINT16 error_code, char *p_error_text);

extern UINT8    *sdpu_extract_attr_seq (UINT8 *p, UINT16 param_len, tSDP_ATTR_SEQ *p_seq);
extern UINT8    *sdpu_extract_uid_seq (UINT8 *p, UINT16 param_len, tSDP_UUID_SEQ *p_seq);

extern UINT8    *sdpu_get_len_from_type (UINT8 *p, UINT8 type, UINT32 *p_len);
extern BOOLEAN  sdpu_is_base_uuid (UINT8 *p_uuid);
extern BOOLEAN  sdpu_compare_uuid_arrays (UINT8 *p_uuid1, UINT32 len1, UINT8 *p_uuid2, UINT16 len2);
extern BOOLEAN  sdpu_compare_bt_uuids (tBT_UUID *p_uuid1, tBT_UUID *p_uuid2);
extern BOOLEAN  sdpu_compare_uuid_with_attr (tBT_UUID *p_btuuid, tSDP_DISC_ATTR *p_attr);

extern void     sdpu_sort_attr_list( UINT16 num_attr, tSDP_DISCOVERY_DB *p_db );
extern UINT16 sdpu_get_list_len( tSDP_UUID_SEQ   *uid_seq, tSDP_ATTR_SEQ   *attr_seq );
extern UINT16 sdpu_get_attrib_seq_len(tSDP_RECORD *p_rec, tSDP_ATTR_SEQ *attr_seq);
extern UINT16 sdpu_get_attrib_entry_len(tSDP_ATTRIBUTE *p_attr);
extern UINT8 *sdpu_build_partial_attrib_entry (UINT8 *p_out, tSDP_ATTRIBUTE *p_attr, UINT16 len, UINT16 *offset);
extern void sdpu_uuid16_to_uuid128(UINT16 uuid16, UINT8 *p_uuid128);

/* sdp_db.c提供的函数
*/
extern tSDP_RECORD    *sdp_db_service_search (tSDP_RECORD *p_rec, tSDP_UUID_SEQ *p_seq);
extern tSDP_RECORD    *sdp_db_find_record (UINT32 handle);
extern tSDP_ATTRIBUTE *sdp_db_find_attr_in_rec (tSDP_RECORD *p_rec, UINT16 start_attr, UINT16 end_attr);


/* sdp_server.c提供的函数
*/
#if SDP_SERVER_ENABLED == TRUE
extern void     sdp_server_handle_client_req (tCONN_CB *p_ccb, BT_HDR *p_msg);
#else
#define sdp_server_handle_client_req(p_ccb, p_msg)
#endif

/* sdp_discovery.c提供的函数
*/
#if SDP_CLIENT_ENABLED == TRUE
extern void sdp_disc_connected (tCONN_CB *p_ccb);
extern void sdp_disc_server_rsp (tCONN_CB *p_ccb, BT_HDR *p_msg);
#else
#define sdp_disc_connected(p_ccb)
#define sdp_disc_server_rsp(p_ccb, p_msg)
#endif

#endif  ///SDP_INCLUDED == TRUE

#endif

