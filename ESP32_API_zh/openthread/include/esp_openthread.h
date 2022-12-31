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

#include "esp_err.h"
#include "esp_openthread_types.h"
#include "openthread/error.h"
#include "openthread/instance.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief   初始化整个OpenThread堆栈。
 *
 * @note OpenThread实例也将在此函数中初始化。
 *
 * @param[in]  init_config      初始化配置。
 *
 * @return
 *      -成功时ESP_OK
 *      -如果分配失败，则为ESP_ERR_NO_MEM
 *      -ESP_ERR_INVALID_ARG（如果不支持无线电或主机连接模式）
 *      -ESP_ERR_INVALID_STATE（如果已初始化）
 *
 */
esp_err_t esp_openthread_init(const esp_openthread_platform_config_t *init_config);

/**
 * @brief   启动OpenThread主循环。
 *
 * @note 除非在运行OpenThread堆栈时发生错误，否则该函数不会返回。
 *
 * @return
 *      -成功时ESP_OK
 *      -如果分配失败，则为ESP_ERR_NO_MEM
 *      -其他故障的ESP_FAIL
 *
 */
esp_err_t esp_openthread_launch_mainloop(void);

/**
 * @brief 此函数执行OpenThread堆栈和平台驱动程序去初始化。
 *
 * @return
 *      -成功时ESP_OK
 *      -ESP_ERR_INVALID_STATE（如果未初始化）
 *
 */
esp_err_t esp_openthread_deinit(void);

/**
 * @brief 此函数获取底层OpenThread实例。
 *
 * @note 此函数可以在没有锁定的情况下对其他任务调用。
 *
 * @return OpenThread实例指针
 *
 */
otInstance *esp_openthread_get_instance(void);

#ifdef __cplusplus
} // 外部“C”结尾
#endif

