// 版权所有2021浓缩咖啡系统（上海）有限公司
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
// 许可证下的限制

#pragma once

#include <stdbool.h>

#include "esp_err.h"
#include "freertos/FreeRTOS.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 此函数初始化OpenThread API锁。
 *
 * @return
 *      -成功时ESP_OK
 *      -如果分配失败，则为ESP_ERR_NO_MEM
 *      -ESP_ERR_INVALID_STATE（如果已初始化）
 *
 */
esp_err_t esp_openthread_lock_init(void);

/**
 * 此函数用于取消初始化OpenThread API锁。
 *
 */
void esp_openthread_lock_deinit(void);

/**
 * @brief 此函数获取OpenThreadAPI锁。
 *
 * @note 每个使用otInstance参数的OT API都必须使用此API锁进行保护，除非调用站点位于OT回调中。
 *
 * @param[in] block_ticks   等待锁定的最大RTOS滴答数。
 *
 * @return
 *      -获取锁时为True
 *      -在超时后未能获取锁时为False。
 *
 */
bool esp_openthread_lock_acquire(TickType_t block_ticks);

/**
 * @brief 此函数释放OpenThreadAPI锁。
 *
 */
void esp_openthread_lock_release(void);


#ifdef __cplusplus
}
#endif

