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

#ifndef __BTA_HFP_DEFS_H__
#define __BTA_HFP_DEFS_H__

#include "stack/btm_api.h"

#define BTA_HFP_CODEC_NONE           BTM_SCO_CODEC_NONE
#define BTA_HFP_CODEC_CVSD           BTM_SCO_CODEC_CVSD      /* CVSD */
#define BTA_HFP_CODEC_MSBC           BTM_SCO_CODEC_MSBC      /* 毫秒BC*/

typedef UINT16 tBTA_HFP_PEER_CODEC;

#ifndef BTA_HFP_SCO_OUT_PKT_SIZE
#define BTA_HFP_SCO_OUT_PKT_SIZE    BTM_SCO_DATA_SIZE_MAX
#endif

#define BTA_HFP_SCO_CODEC_PCM       0       /* 用于常规SCO*/
#define BTA_HFP_SCO_CODEC_SBC       1       /* 用于WBS*/
typedef UINT8   tBTA_HFP_SCO_CODEC_TYPE;

#define BTA_HFP_SCO_SAMP_RATE_8K     8000
#define BTA_HFP_SCO_SAMP_RATE_16K    16000

/* SCO编解码器信息*/
typedef struct {
    tBTA_HFP_SCO_CODEC_TYPE   codec_type;
} tBTA_HFP_CODEC_INFO;

#define BTA_HFP_SCO_ROUTE_PCM    BTM_SCO_ROUTE_PCM
#define BTA_HFP_SCO_ROUTE_HCI    BTM_SCO_ROUTE_HCI

typedef tBTM_SCO_ROUTE_TYPE tBTA_HFP_SCO_ROUTE_TYPE;

#endif /* __BTA_HFP_DEFS_H__ */

