/******************************************************************************
 * 版权所有（C）2003-2012 Broadcom Corporation
 *
 *  根据Apache许可证2.0版（“许可证”）获得许可；除非符合许可证，否则不得使用此文件。您可以在以下地址获取许可证副本：
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 *  除非适用法律要求或书面同意，否则根据许可证分发的软件是按“原样”分发的，无任何明示或暗示的担保或条件。有关许可证下权限和限制的具体语言，请参阅许可证。
 *
 ******************************************************************************/

/******************************************************************************
 * 这是BTA GATT服务器的专用文件。
 *
 ******************************************************************************/
#ifndef BTA_GATTS_INT_H
#define BTA_GATTS_INT_H

#include "common/bt_target.h"
#include "bta/bta_sys.h"
#include "bta/bta_gatt_api.h"
#include "stack/gatt_api.h"


/*****************************************************************************
**  常量和数据类型
*****************************************************************************/
enum {
    BTA_GATTS_API_REG_EVT  = BTA_SYS_EVT_START(BTA_ID_GATTS),
    BTA_GATTS_INT_START_IF_EVT,
    BTA_GATTS_API_DEREG_EVT,
    BTA_GATTS_API_CREATE_SRVC_EVT,
    BTA_GATTS_API_INDICATION_EVT,

    BTA_GATTS_API_ADD_INCL_SRVC_EVT,
    BTA_GATTS_API_ADD_CHAR_EVT,
    BTA_GATTS_API_ADD_DESCR_EVT,
    BTA_GATTS_API_DEL_SRVC_EVT,
    BTA_GATTS_API_START_SRVC_EVT,
    BTA_GATTS_API_STOP_SRVC_EVT,
    BTA_GATTS_API_RSP_EVT,
    BTA_GATTS_API_SET_ATTR_VAL_EVT,
    BTA_GATTS_API_OPEN_EVT,
    BTA_GATTS_API_CANCEL_OPEN_EVT,
    BTA_GATTS_API_CLOSE_EVT,
    BTA_GATTS_API_LISTEN_EVT,
    BTA_GATTS_API_DISABLE_EVT,
    BTA_GATTS_API_SEND_SERVICE_CHANGE_EVT
};
typedef UINT16 tBTA_GATTS_INT_EVT;

/* 设备上允许的最大应用程序数*/
#define BTA_GATTS_MAX_APP_NUM   GATT_MAX_SR_PROFILES

/* 设备中允许的最大服务数*/
#define BTA_GATTS_MAX_SRVC_NUM   GATT_MAX_SR_PROFILES

/* GATTC寄存器API的内部结构*/
typedef struct {
    BT_HDR                  hdr;
    tBT_UUID                app_uuid;
    tBTA_GATTS_CBACK        *p_cback;
} tBTA_GATTS_API_REG;

typedef struct {
    BT_HDR                  hdr;
    tBTA_GATTS_IF           server_if;
} tBTA_GATTS_INT_START_IF;

typedef tBTA_GATTS_INT_START_IF tBTA_GATTS_API_DEREG;

typedef struct {
    BT_HDR                  hdr;
    tBTA_GATTS_IF           server_if;
    tBT_UUID                service_uuid;
    UINT16                  num_handle;
    UINT8                   inst;
    BOOLEAN                 is_pri;

} tBTA_GATTS_API_CREATE_SRVC;

typedef struct {
    BT_HDR                  hdr;
    tBT_UUID                char_uuid;
    tBTA_GATT_PERM          perm;
    tBTA_GATT_CHAR_PROP     property;
    tBTA_GATTS_ATTR_CONTROL control;
    tBTA_GATT_ATTR_VAL      attr_val;
} tBTA_GATTS_API_ADD_CHAR;

typedef struct {
    BT_HDR                  hdr;
    UINT16                  included_service_id;
} tBTA_GATTS_API_ADD_INCL_SRVC;

typedef struct {
    BT_HDR                  hdr;
    tBT_UUID                descr_uuid;
    tBTA_GATT_PERM          perm;
    tBTA_GATTS_ATTR_CONTROL control;
    tBTA_GATT_ATTR_VAL      attr_val;
} tBTA_GATTS_API_ADD_DESCR;

typedef struct {
    BT_HDR  hdr;
    UINT16  attr_id;
    UINT16  len;
    BOOLEAN need_confirm;
    UINT8   value[BTA_GATT_MAX_ATTR_LEN];
} tBTA_GATTS_API_INDICATION;

typedef struct {
    BT_HDR              hdr;
    UINT32              trans_id;
    tBTA_GATT_STATUS    status;
    tBTA_GATTS_RSP      *p_rsp;
} tBTA_GATTS_API_RSP;

typedef struct{
    BT_HDR              hdr;
    UINT16 length;
    UINT8 *value;
}tBTA_GATTS_API_SET_ATTR_VAL;

typedef struct {
    BT_HDR                  hdr;
    tBTA_GATT_TRANSPORT     transport;
} tBTA_GATTS_API_START;


typedef struct {
    BT_HDR                  hdr;
    BD_ADDR                 remote_bda;
    tBTA_GATTS_IF           server_if;
    BOOLEAN                 is_direct;
    tBTA_GATT_TRANSPORT     transport;

} tBTA_GATTS_API_OPEN;

typedef tBTA_GATTS_API_OPEN tBTA_GATTS_API_CANCEL_OPEN;

typedef struct {
    BT_HDR                  hdr;
    BD_ADDR_PTR             remote_bda;
    tBTA_GATTS_IF           server_if;
    BOOLEAN                 start;
} tBTA_GATTS_API_LISTEN;

typedef struct {
    BT_HDR                  hdr;
    tBTA_GATTS_IF           server_if;
    BD_ADDR                 remote_bda;
} tBTA_GATTS_API_SEND_SERVICE_CHANGE;

typedef union {
    BT_HDR                          hdr;
    tBTA_GATTS_API_REG              api_reg;
    tBTA_GATTS_API_DEREG            api_dereg;
    tBTA_GATTS_API_CREATE_SRVC      api_create_svc;
    tBTA_GATTS_API_ADD_INCL_SRVC    api_add_incl_srvc;
    tBTA_GATTS_API_ADD_CHAR         api_add_char;
    tBTA_GATTS_API_ADD_DESCR        api_add_char_descr;
    tBTA_GATTS_API_START            api_start;
    tBTA_GATTS_API_INDICATION       api_indicate;
    tBTA_GATTS_API_RSP              api_rsp;
    tBTA_GATTS_API_SET_ATTR_VAL     api_set_val;
    tBTA_GATTS_API_OPEN             api_open;
    tBTA_GATTS_API_CANCEL_OPEN      api_cancel_open;

    tBTA_GATTS_INT_START_IF         int_start_if;
    /* 如果支持外围角色*/
    tBTA_GATTS_API_LISTEN           api_listen;
    tBTA_GATTS_API_SEND_SERVICE_CHANGE api_send_service_change;
} tBTA_GATTS_DATA;

/* 应用程序注册控制块*/
typedef struct {
    BOOLEAN             in_use;
    tBT_UUID            app_uuid;
    tBTA_GATTS_CBACK    *p_cback;
    tBTA_GATTS_IF       gatt_if;
} tBTA_GATTS_RCB;

/* 服务注册控制块*/
typedef struct {
    tBT_UUID    service_uuid;   /* 服务UUID*/
    UINT16      service_id;     /* 维修手柄*/
    UINT8       inst_num;       /* 实例ID*/
    UINT8       rcb_idx;
    UINT8       idx;            /* 服务CB自指数*/
    BOOLEAN     in_use;

} tBTA_GATTS_SRVC_CB;


/* GATT服务器控制块*/
typedef struct {
    BOOLEAN             enabled;
    tBTA_GATTS_RCB      rcb[BTA_GATTS_MAX_APP_NUM];
    tBTA_GATTS_SRVC_CB  srvc_cb[BTA_GATTS_MAX_SRVC_NUM];
} tBTA_GATTS_CB;



/*****************************************************************************
**  全局数据
*****************************************************************************/

/* GATTC控制块*/
#if BTA_DYNAMIC_MEMORY == FALSE
extern tBTA_GATTS_CB  bta_gatts_cb;
#else
extern tBTA_GATTS_CB *bta_gatts_cb_ptr;
#define bta_gatts_cb (*bta_gatts_cb_ptr)
#endif

/*****************************************************************************
**  功能原型
*****************************************************************************/
extern BOOLEAN bta_gatts_hdl_event(BT_HDR *p_msg);

extern void bta_gatts_api_disable(tBTA_GATTS_CB *p_cb);
extern void bta_gatts_api_enable(tBTA_GATTS_CB *p_cb, tBTA_GATTS_DATA *p_data);
extern void bta_gatts_register(tBTA_GATTS_CB *p_cb, tBTA_GATTS_DATA *p_msg);
extern void bta_gatts_start_if(tBTA_GATTS_CB *p_cb, tBTA_GATTS_DATA *p_msg);
extern void bta_gatts_deregister(tBTA_GATTS_CB *p_cb, tBTA_GATTS_DATA *p_msg);
extern void bta_gatts_create_srvc(tBTA_GATTS_CB *p_cb, tBTA_GATTS_DATA *p_msg);
extern void bta_gatts_add_include_srvc(tBTA_GATTS_SRVC_CB *p_srvc_cb, tBTA_GATTS_DATA *p_msg);
extern void bta_gatts_add_char(tBTA_GATTS_SRVC_CB *p_srvc_cb, tBTA_GATTS_DATA *p_msg);
extern void bta_gatts_add_char_descr(tBTA_GATTS_SRVC_CB *p_srvc_cb, tBTA_GATTS_DATA *p_msg);
extern void bta_gatts_set_attr_value(tBTA_GATTS_SRVC_CB *p_srvc_cb, tBTA_GATTS_DATA *p_msg);
extern tGATT_STATUS bta_gatts_get_attr_value(UINT16 attr_handle, UINT16 *length, UINT8 **value);
extern void bta_gatts_delete_service(tBTA_GATTS_SRVC_CB *p_srvc_cb, tBTA_GATTS_DATA *p_msg);
extern void bta_gatts_start_service(tBTA_GATTS_SRVC_CB *p_srvc_cb, tBTA_GATTS_DATA *p_msg);
extern void bta_gatts_stop_service(tBTA_GATTS_SRVC_CB *p_srvc_cb, tBTA_GATTS_DATA *p_msg);

extern void bta_gatts_send_rsp(tBTA_GATTS_CB *p_cb, tBTA_GATTS_DATA *p_msg);
extern void bta_gatts_indicate_handle (tBTA_GATTS_CB *p_cb, tBTA_GATTS_DATA *p_msg);


extern void bta_gatts_open (tBTA_GATTS_CB *p_cb, tBTA_GATTS_DATA *p_msg);
extern void bta_gatts_cancel_open (tBTA_GATTS_CB *p_cb, tBTA_GATTS_DATA *p_msg);
extern void bta_gatts_close (tBTA_GATTS_CB *p_cb, tBTA_GATTS_DATA *p_msg);
extern void bta_gatts_listen(tBTA_GATTS_CB *p_cb, tBTA_GATTS_DATA *p_msg);
extern void bta_gatts_send_service_change_indication (tBTA_GATTS_DATA *p_msg);

extern BOOLEAN bta_gatts_uuid_compare(tBT_UUID tar, tBT_UUID src);
extern tBTA_GATTS_RCB *bta_gatts_find_app_rcb_by_app_if(tBTA_GATTS_IF server_if);
extern UINT8 bta_gatts_find_app_rcb_idx_by_app_if(tBTA_GATTS_CB *p_cb, tBTA_GATTS_IF server_if);
extern UINT8 bta_gatts_alloc_srvc_cb(tBTA_GATTS_CB *p_cb, UINT8 rcb_idx);
extern tBTA_GATTS_SRVC_CB *bta_gatts_find_srvc_cb_by_srvc_id(tBTA_GATTS_CB *p_cb, UINT16 service_id);
extern tBTA_GATTS_SRVC_CB *bta_gatts_find_srvc_cb_by_attr_id(tBTA_GATTS_CB *p_cb, UINT16 attr_id);
extern void bta_gatts_deinit(void);

#endif /* BTA_GATTS_INT_H */

