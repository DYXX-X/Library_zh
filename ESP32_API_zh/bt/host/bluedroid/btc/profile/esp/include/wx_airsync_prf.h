// 版权所有2015-2016 Espressif Systems（上海）私人有限公司
//
// 根据Apache许可证2.0版（“许可证”）获得许可；
// 除非符合许可证，否则不得使用此文件。
// 您可以在以下地址获取许可证副本：

//     http://www.apache.org/licenses/LICENSE-2.0
//
// 除非适用法律要求或书面同意，软件
// 根据许可证分发的内容是按“原样”分发的，
// 无任何明示或暗示的保证或条件。
// 有关管理权限和
// 许可证下的限制。

#include "prf_defs.h"

#if (WX_AIRSYNC_CFG)

#include "common/bt_target.h"
#include "stack/gatt_api.h"
#include "stack/gattdefs.h"
#include "bt_app_api.h"


///最大传输单位
#define ATT_DEFAULT_MTU                                 (23)

#define BLE_WECHAT_MAX_DATA_LEN            (ATT_DEFAULT_MTU - 3)


//定义密钥服务uuid
#define ATT_SVC_AIRSYNC 0xFEE7
//定义空同步字符uuid
#define ATT_CHAR_AIRSYNC_WIT    0xFEC7
#define ATT_CHAR_AIRSYBC_NTF    0xFEC8
#define ATT_CHAR_AIRSYNC_READ   0xFEC9


typedef void (tAIRSYNC_CBACK)(UINT8 app_id, UINT8 event, UINT8 len, UINT8 *data);


///WX AirSync服务属性索引
enum {
    WX_IDX_SVC,
    WX_IDX_AIRSYNC_WIT_CHAR,
    WX_IDX_AIRSYNC_WIT_VAL,
    WX_IDX_AIRSYNC_NTF_CHAR,
    WX_IDX_AIRSYNC_NTF_VAL,
    WX_IDX_AIRSYNC_READ_CHAR,
    WX_IDX_AIRSYNC_READ_VAL,
    WX_IDX_AIRSYNC_NTF_CFG,

    WX_IDX_NB,
};

typedef struct {
    BD_ADDR remote_bda;
    BOOLEAN need_rsp;
    UINT16  clt_cfg;
} tAirSync_WRITE_DATA;

typedef struct {
    BOOLEAN      in_use;
    BOOLEAN      congest;
    UINT16       conn_id;
    BOOLEAN      connected;
    BD_ADDR      remote_bda;
    UINT32       trans_id;
    UINT8            cur_srvc_id;

} tAirSync_CLCB;


typedef struct {
    UINT8            app_id;
    UINT16       airsync_wirt_hdl;
    UINT16       airsync_ntf_hdl;
    UINT16           airsync_read_hdl;
    UINT16       airsync_cfg_hdl;

    tAIRSYNC_CBACK       *p_cback;

} tAirSync_INST;


/* 维修发动机控制块*/
typedef struct {
    tAirSync_CLCB            clcb;           /* 连接链环*/
    tGATT_IF                 gatt_if;
    BOOLEAN              enabled;
    BOOLEAN              is_primery;
    tAirSync_INST            airsync_inst;
    UINT8                    inst_id;
} tAIRSYNC_CB_ENV;

void AirSync_CreateService(void);

tAirSync_CLCB *airsync_env_clcb_alloc (UINT16 conn_id, BD_ADDR remote_bda);

UINT16 AirSync_env_find_conn_id_by_bd_adddr(BD_ADDR bda);

BOOLEAN AirSync_env_clcb_dealloc(UINT16 conn_id);

tGATT_STATUS AirSync_Init(tAIRSYNC_CBACK *call_back);

void AirSync_msg_notify(UINT8 len, UINT8 *button_msg);

extern tAIRSYNC_CB_ENV airsync_cb_env;

#endif  ///WX_AIRSYNC_CFG

