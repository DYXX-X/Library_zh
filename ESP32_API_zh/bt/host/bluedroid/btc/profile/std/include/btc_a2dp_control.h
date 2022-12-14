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

/*******************************************************************************
 * 文件名：btc_a2dp_control.h
 *
 *******************************************************************************/

#ifndef __BTC_A2DP_CONTROL_H__
#define __BTC_A2DP_CONTROL_H__

#include <stdbool.h>
#include "common/bt_target.h"
#include "bta/bta_api.h"
#include "btc_av_api.h"
#include "esp_a2dp_api.h"

#if BTC_AV_INCLUDED
/*******************************************************************************
 **  公共职能
 *******************************************************************************/

/*******************************************************************************
 ** 函数btc_a2dp_control_media_ctrl
 **
 ** 说明处理media_ctrl命令
 **
 *******************************************************************************/
void btc_a2dp_control_media_ctrl(esp_a2d_media_ctrl_t ctrl);


/*******************************************************************************
 ** 函数btc_a2dp_control_datapath_ctrl
 **
 ** 描述处理媒体数据路径事件，该事件改编自bluedroid的UIPC数据通道
 **
 *******************************************************************************/
void btc_a2dp_control_datapath_ctrl(uint32_t dp_evt);


/*******************************************************************************
 ** 函数btc_a2dp_control_command_ack
 **
 ** 说明确认挂起的media_ctrl命令
 **
 *******************************************************************************/
void btc_a2dp_control_command_ack(int status);


/*******************************************************************************
 ** 函数btc_a2dp_control_get_datachl_stat
 **
 ** 说明检查数据通道状态是否打开
 **
 ** 如果数据通道状态为打开，则返回TRUE
 **
 *******************************************************************************/
BOOLEAN btc_a2dp_control_get_datachnl_stat(void);


/*******************************************************************************
 ** 函数btc_a2dp_control_set_datachl_stat
 **
 ** 说明设置数据通道状态标志
 **
 *******************************************************************************/
void btc_a2dp_control_set_datachnl_stat(BOOLEAN open);


/*******************************************************************************
 ** 函数btc_a2dp_control_init
 **
 ** 说明初始化A2DP控制模块。它应该在A2DP流的启动阶段调用。
 **
 *******************************************************************************/
bool btc_a2dp_control_init(void);


/*******************************************************************************
 ** 函数btc_a2dp_control_cleanup
 **
 ** 说明清理A2DP控制模块
 **
 *******************************************************************************/
void btc_a2dp_control_cleanup(void);

#endif /* #如果BTC_AV_INCLUDED*/

#endif /* __BTC_A2DP_CONTROL_H__ */

