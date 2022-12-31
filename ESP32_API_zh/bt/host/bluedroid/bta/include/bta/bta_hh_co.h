/******************************************************************************
 * 版权所有（C）2005-2012 Broadcom Corporation
 *
 *  根据Apache许可证2.0版（“许可证”）获得许可；除非符合许可证，否则不得使用此文件。您可以在以下地址获取许可证副本：
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 *  除非适用法律要求或书面同意，否则根据许可证分发的软件是按“原样”分发的，无任何明示或暗示的担保或条件。有关许可证下权限和限制的具体语言，请参阅许可证。
 *
 ******************************************************************************/

/******************************************************************************
 * 这是hid主机调用函数的接口文件。
 *
 ******************************************************************************/
#ifndef BTA_HH_CO_H
#define BTA_HH_CO_H

#include "bta/bta_hh_api.h"

typedef struct {
    UINT16              rpt_uuid;
    UINT8               rpt_id;
    tBTA_HH_RPT_TYPE    rpt_type;
    UINT8               inst_id;
    UINT8               prop;
} tBTA_HH_RPT_CACHE_ENTRY;

/*******************************************************************************
** 函数bta_hh_co_data
**
** 说明当在中断信道中接收到数据时，HH执行此调出功能。
**
** 返回void。
**
*******************************************************************************/
extern void bta_hh_co_data(UINT8 dev_handle, UINT8 *p_rpt, UINT16 len,
                           tBTA_HH_PROTO_MODE  mode, UINT8 sub_class,
                           UINT8 ctry_code, BD_ADDR peer_addr, UINT8 app_id);

/*******************************************************************************
** 函数bta_hh_co_open
**
** 说明当连接打开时，HH将执行此调出功能，并且应用程序可能会执行某些特定于设备的初始化。
**
** 返回void。
**
*******************************************************************************/
extern void bta_hh_co_open(UINT8 dev_handle, UINT8 sub_class,
                           UINT16 attr_mask, UINT8 app_id);

/*******************************************************************************
** 函数bta_hh_co_close
**
** 说明当连接关闭时，HH执行此callout函数，可能需要特定于设备的终结。
**
** 返回void。
**
*******************************************************************************/
extern void bta_hh_co_close(UINT8 dev_handle, UINT8 app_id);

#if (BLE_INCLUDED == TRUE && BTA_HH_LE_INCLUDED == TRUE)
/*******************************************************************************
** 函数bta_hh_le_corpt_info
**
** 说明此调出功能用于将HOGP设备上的报告信息传递给应用程序。如果设备已绑定，应用程序可以将此信息保存在NV中，并在堆栈重新启动时将其加载回。
**
** 参数remote_bda-远程设备地址p_entry-报告条目指针app_id-应用程序id
**
** 返回void。
**
*******************************************************************************/
extern void bta_hh_le_co_rpt_info(BD_ADDR remote_bda,
                                  tBTA_HH_RPT_CACHE_ENTRY *p_entry,
                                  UINT8 app_id);

/*******************************************************************************
** 函数bta_hh_le_co_cache_load
**
** 说明此callout函数用于请求应用程序加载缓存的HOGP报告（如果有）。缓存读取完成后，应用程序将调用bta_hh_le_ci_cache_load（）。
**
** 参数remote_bda-远程设备地址p_num_rpt：缓存报告app_id的数量-应用程序id
**
** 返回已兑现的报表数组
**
*******************************************************************************/
extern tBTA_HH_RPT_CACHE_ENTRY *bta_hh_le_co_cache_load (BD_ADDR remote_bda,
        UINT8 *p_num_rpt,
        UINT8 app_id);

/*******************************************************************************
** 函数bta_hh_le_coreset_rpt_cache
**
** 说明此调出功能用于重置HOGP设备缓存。
**
** 参数remote_bda-远程设备地址
**
** 不返回任何值
**
*******************************************************************************/
extern void bta_hh_le_co_reset_rpt_cache (BD_ADDR remote_bda, UINT8 app_id);

#endif /* #如果（BLE_INCLUDED==TRUE&&BTA_HH_LE_INCLUDED==TRUE）*/
#endif /* BTA_HH_CO_H */

