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


#ifndef __BTC_COMMON_H__
#define __BTC_COMMON_H__

#include <assert.h>
#include "common/bt_trace.h"
#include "stack/bt_types.h"
#include "osi/osi.h"

#define BTC_ASSERTC(cond, msg, val) assert(cond && msg)

#define BTC_HAL_CBACK(P_CB, P_CBACK, ...)\
    if (P_CB && P_CB->P_CBACK) {            \
        LOG_INFO("HAL %s->%s", #P_CB, #P_CBACK); \
        P_CB->P_CBACK(__VA_ARGS__);         \
    }                                       \
    else {                                  \
        BTC_ASSERTC(0, "Callback is NULL", 0);  \
    }

#endif /* __BTC_COMMON_H__ */

