/******************************************************************************
 * 版权所有（C）2015谷歌公司。
 *
 *  根据Apache许可证2.0版（“许可证”）获得许可；除非符合许可证，否则不得使用此文件。您可以在以下地址获取许可证副本：
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 *  除非适用法律要求或书面同意，否则根据许可证分发的软件是按“原样”分发的，无任何明示或暗示的担保或条件。有关许可证下权限和限制的具体语言，请参阅许可证。
 *
 ******************************************************************************/

#ifndef _INTEROP_H_
#define _INTEROP_H_

#include <stdbool.h>
#include "common/bt_defs.h"
#include "common/bt_target.h"

typedef enum {
    // 禁用安全连接
    // 这适用于不处理安全模式的BT 4.1/2之前的设备
    // 很好。
    INTEROP_DISABLE_LE_SECURE_CONNECTIONS,

    // 一些设备在配对过程中被证明存在问题，通常
    // 需要多次重试才能完成配对。为了避免用户降级
    // 这些设备的体验，如果页面
    // 在配对期间接收超时。
    INTEROP_AUTO_RETRY_PAIRING
} interop_feature_t;

// 检查给定的|addr|是否与所标识的已知互操作性解决方案匹配
// 通过|interop_feature_t|枚举。此API用于基于地址的简单查找
// 其中没有更多信息可用。无查找或随机地址解析
// 在|addr|上执行。
bool interop_match(const interop_feature_t feature, const bt_bdaddr_t *addr);

#endif /*_INTEROP_H_*/

