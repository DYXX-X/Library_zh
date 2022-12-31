// 版权所有2018 Espressif Systems（上海）私人有限公司
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


/******************************************************************************
 * 这是hf客户端调用函数的接口文件。
 *
 ******************************************************************************/
#ifndef BTA_HF_CLIENT_CO_H
#define BTA_HF_CLIENT_CO_H

#include "common/bt_target.h"
#include "bta/bta_hf_client_api.h"

#if (BTA_HF_INCLUDED == TRUE)

#if (BTM_SCO_HCI_INCLUDED == TRUE)
/*******************************************************************************
** 函数bta_hf_client_coaudio_state
**
** 说明HF CLIENT在音频连接启动之前、启动之后和关闭之后调用此功能。
**
** 参数句柄-AG实例状态的句柄-音频状态编解码器-如果编译了WBS支持，则提供将要使用的编解码器，并且在SCO_state_SETUP中，必须使用正确的平台参数调用BTM_I2SPCMConfig（）。在其他状态下，不应忽略编解码器类型
**
** 返回void
**
*******************************************************************************/
void bta_hf_client_co_audio_state(UINT16 handle, UINT8 state, tBTA_HFP_PEER_CODEC codec);


/*******************************************************************************
** 函数bta_hf_client_sco_co_init
**
** 说明在SCO连接打开之前，手机可以使用此功能初始化音频编解码器或用于其他初始化目的。
**
** 返回无效。
**
*******************************************************************************/
tBTA_HFP_SCO_ROUTE_TYPE bta_hf_client_sco_co_init(UINT32 rx_bw, UINT32 tx_bw,
        tBTA_HFP_CODEC_INFO *p_codec_info, UINT8 app_id);


/*******************************************************************************
** 函数bta_hf_client_sco_co_open
**
** 说明此功能在SCO连接打开时执行。
**
** 返回void
**
*******************************************************************************/
void bta_hf_client_sco_co_open(UINT16 handle, UINT8 air_mode, UINT8 inout_pkt_size, UINT16 event);

/*******************************************************************************
** 函数bta_hf_client_sco_co_close
**
** 说明当SCO连接关闭时调用此函数
**
** 返回void
**
*******************************************************************************/
void bta_hf_client_sco_co_close(void);

/*******************************************************************************
** 函数bta_hf_client_sco_co_out_data
**
** 描述调用此函数以通过HCI发送SCO数据。
**
** 返回从应用程序获取的字节数
**
*******************************************************************************/
uint32_t bta_hf_client_sco_co_out_data(UINT8 *p_buf);

/*******************************************************************************
** 函数bta_hf_client_sco_co_in_data
**
** 描述调用此函数将传入的SCO数据发送到应用程序。
**
** 返回void
**
*******************************************************************************/
extern void bta_hf_client_sco_co_in_data(BT_HDR  *p_buf, tBTM_SCO_DATA_FLAG status);

#endif /* #如果（BTM_SCO_HCI_INCLUDED==真）*/

#endif /* #如果（BTA_HF_INCLUDE==真）*/
#endif /* BTA_HF_CLIENT_CO_H */

