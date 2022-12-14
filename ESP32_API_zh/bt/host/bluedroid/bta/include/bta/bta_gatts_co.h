/******************************************************************************
 * 版权所有（C）2010-2012 Broadcom Corporation
 *
 *  根据Apache许可证2.0版（“许可证”）获得许可；除非符合许可证，否则不得使用此文件。您可以在以下地址获取许可证副本：
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 *  除非适用法律要求或书面同意，否则根据许可证分发的软件是按“原样”分发的，无任何明示或暗示的担保或条件。有关许可证下权限和限制的具体语言，请参阅许可证。
 *
 ******************************************************************************/

/******************************************************************************
 * 这是BTA GATT服务器调用函数的接口文件。
 *
 ******************************************************************************/
#ifndef BTA_GATTS_CO_H
#define BTA_GATTS_CO_H

#include "bta/bta_gatt_api.h"

/*******************************************************************************
** 函数bta_gats_co_update_handle_range
**
** 说明当GATT服务器处理要添加或删除的范围ios时，GATTS执行此调出功能。
**
** 参数is_add：true是添加句柄范围；否则将删除。p_hndl_range：句柄范围。
**
** 返回void。
**
*******************************************************************************/
extern void bta_gatts_co_update_handle_range(BOOLEAN is_add, tBTA_GATTS_HNDL_RANGE *p_hndl_range);

/*******************************************************************************
** 函数bta_gats_co_srv_chg
**
** 说明此调用用于读取/写入/删除与服务更改相关的信息。请求由cmd和p_req组成，响应在p_rsp中返回
**
** 参数cmd-请求命令p_req-请求参数p_rsp-请求的响应数据
**
** 返回TRUE-如果请求处理成功，并且响应以p_rsp形式返回。FALSE-如果无法处理请求
**
*******************************************************************************/
extern BOOLEAN bta_gatts_co_srv_chg(tBTA_GATTS_SRV_CHG_CMD cmd,
                                    tBTA_GATTS_SRV_CHG_REQ *p_req,
                                    tBTA_GATTS_SRV_CHG_RSP *p_rsp);

/*******************************************************************************
** 函数bta_gats_co_load_handle_range
**
** 说明当请求从NV加载GATT服务器句柄范围时，GATTS执行此调出功能。
**
** 参数
**
** 返回void。
**
*******************************************************************************/
extern  BOOLEAN bta_gatts_co_load_handle_range(UINT8 index,
        tBTA_GATTS_HNDL_RANGE *p_handle);


#endif /* BTA_GATTS_CO_H */

