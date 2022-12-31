// 版权所有2015-2019 Espressif Systems（上海）私人有限公司
//
// 根据Apache许可证2.0版（“许可证”）获得许可；
// 除非符合许可证，否则不得使用此文件。
// 您可以在以下地址获取许可证副本：
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// 除非适用法律要求或书面同意，软件
// 根据许可证分发的内容是按“原样”分发的，
// 无任何明示或暗示的保证或条件。
// 有关管理权限和
// 许可证下的限制。

/*******************************************************************************
 * 注意：hal不是公共api，不要在应用程序代码中使用。请参阅自述文件。在hal/include/hal/readme.md中的md
 ******************************************************************************/

// PCNT的HAL层。
// hal层中没有参数检查，因此调用者必须确保参数的正确性。

#pragma once

#include "soc/pcnt_struct.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * 驾驶员和HAL应维护的上下文
 */
typedef struct {
    pcnt_dev_t *dev; /*!< PCNT外围寄存器基址*/
} pcnt_hal_context_t;

/**
 * @brief 初始化PCNT hal并将PCNT设置为默认配置。
 * @note 在调用其他hal层函数之前，应首先调用此函数。
 *
 * @param hal HAL层的上下文
 * @param group_id PCNT组ID
 */
void pcnt_hal_init(pcnt_hal_context_t *hal, int group_id);

#ifdef __cplusplus
}
#endif

