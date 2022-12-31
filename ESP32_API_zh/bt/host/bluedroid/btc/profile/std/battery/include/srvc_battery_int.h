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

#ifndef SRVC_BATTERY_INT_H
#define SRVC_BATTERY_INT_H

#include "common/bt_target.h"
#include "srvc_api.h"
#include "stack/gatt_api.h"

#ifndef BA_MAX_INT_NUM
#define BA_MAX_INT_NUM     4
#endif

#define BATTERY_LEVEL_SIZE      1


typedef struct {
    UINT8           app_id;
    UINT16          ba_level_hdl;
    UINT16          clt_cfg_hdl;
    UINT16          rpt_ref_hdl;
    UINT16          pres_fmt_hdl;

    tBA_CBACK       *p_cback;

    UINT16          pending_handle;
    UINT8           pending_clcb_idx;
    UINT8           pending_evt;

} tBA_INST;

typedef struct {
    tBA_INST                battery_inst[BA_MAX_INT_NUM];
    UINT8                   inst_id;
    BOOLEAN                 enabled;

} tBATTERY_CB;

#ifdef __cplusplus
extern "C" {
#endif

/* 全球GATT数据*/
#if GATT_DYNAMIC_MEMORY == FALSE
extern tBATTERY_CB battery_cb;
#else
extern tBATTERY_CB *battery_cb_ptr;
#define battery_cb (*battery_cb_ptr)
#endif


extern BOOLEAN battery_valid_handle_range(UINT16 handle);

extern UINT8 battery_s_write_attr_value(UINT8 clcb_idx, tGATT_WRITE_REQ *p_value,
                                        tGATT_STATUS *p_status);
extern UINT8 battery_s_read_attr_value (UINT8 clcb_idx, UINT16 handle, tGATT_VALUE *p_value, BOOLEAN is_long, tGATT_STATUS *p_status);



#ifdef __cplusplus
}
#endif
#endif

