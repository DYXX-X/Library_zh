// 版权所有2020 Espressif Systems（上海）私人有限公司
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

#pragma once

#include <stdint.h>
#include <stdbool.h>

#include "esp_err.h"

#include "soc/soc_caps.h"
#include "hal/cpu_hal.h"
#include "hal/soc_ll.h"

#ifdef __cplusplus
extern "C" {
#endif

#if SOC_CPU_CORES_NUM > 1
// 多核目标的实用函数
#define __SOC_HAL_PERFORM_ON_OTHER_CORES(action)    { \
                                                        for (uint32_t i = 0, cur = cpu_hal_get_core_id(); i < SOC_CPU_CORES_NUM; i++) { \
                                                            if (i != cur) { \
                                                                action(i); \
                                                            } \
                                                        } \
                                                    }

#define SOC_HAL_STALL_OTHER_CORES()                 __SOC_HAL_PERFORM_ON_OTHER_CORES(soc_hal_stall_core);
#define SOC_HAL_UNSTALL_OTHER_CORES()               __SOC_HAL_PERFORM_ON_OTHER_CORES(soc_hal_unstall_core);
#define SOC_HAL_RESET_OTHER_CORES()                 __SOC_HAL_PERFORM_ON_OTHER_CORES(soc_hal_reset_core);

/**
 * 暂停指定的CPU核心。
 *
 * @note 如果内核已停止，则无效-不返回ESP_ERR_INVALID_STATE。
 *
 * @param core 要暂停的内核[0..SOC_CPU_CORES_NUM-1]
 */
void soc_hal_stall_core(int core);

/**
 * 取消停止指定的CPU内核。
 *
 * @note 如果内核已经未调用，则无效-不返回ESP_ERR_INVALID_STATE。
 *
 * @param core 要取消堆叠的堆芯[0..SOC_CPU_CORES_NUM-1]
 */
void soc_hal_unstall_core(int core);

#endif // SOC_CPU_CORES_NUM > 1

/**
 * 重置指定的核心。
 *
 * @param core 要重置的内核[0..SOC_CPU_CORES_NUM-1]
 */
#define soc_hal_reset_core(core)         soc_ll_reset_core((core))

#ifdef __cplusplus
}
#endif

