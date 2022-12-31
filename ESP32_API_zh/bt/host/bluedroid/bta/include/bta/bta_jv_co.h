/******************************************************************************
 * 版权所有（C）2007-2012 Broadcom Corporation
 *
 *  根据Apache许可证2.0版（“许可证”）获得许可；除非符合许可证，否则不得使用此文件。您可以在以下地址获取许可证副本：
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 *  除非适用法律要求或书面同意，否则根据许可证分发的软件是按“原样”分发的，无任何明示或暗示的担保或条件。有关许可证下权限和限制的具体语言，请参阅许可证。
 *
 ******************************************************************************/

/******************************************************************************
 * 这是java接口调用函数的接口文件。
 *
 ******************************************************************************/
#ifndef BTA_JV_CO_H
#define BTA_JV_CO_H

#include "bta/bta_jv_api.h"

#if (defined BTA_JV_INCLUDED && BTA_JV_INCLUDED == TRUE)
/*****************************************************************************
**  函数声明
*****************************************************************************/


/*******************************************************************************
** 函数bta_jv_co_rfc_data
**
** 说明当RX数据路径配置为使用调用时，JV调用此函数以将数据发送到java粘合代码
**
** 返回void
**
*******************************************************************************/

extern int bta_co_rfc_data_incoming(void *user_data, BT_HDR *p_buf);
extern int bta_co_rfc_data_outgoing_size(void *user_data, int *size);
extern int bta_co_rfc_data_outgoing(void *user_data, UINT8 *buf, UINT16 size);

extern int bta_co_l2cap_data_incoming(void *user_data, BT_HDR *p_buf);
extern int bta_co_l2cap_data_outgoing_size(void *user_data, int *size);
extern int bta_co_l2cap_data_outgoing(void *user_data, UINT8 *buf, UINT16 size);

#endif  ///定义的BTA_JV_INCLUDE&BTA_JV_inCLUDE==真
#endif /* BTA_DG_CO_H */

