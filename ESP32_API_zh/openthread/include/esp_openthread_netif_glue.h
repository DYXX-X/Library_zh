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
#include "esp_netif.h"
#include "esp_openthread_types.h"
#include "openthread/instance.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 此函数初始化OpenThread网络接口胶。
 *
 * @param[in] config    平台配置。
 *
 * @return
 *      -成功的胶水指针
 *      -失败时为NULL
 *
 */
void *esp_openthread_netif_glue_init(const esp_openthread_platform_config_t *config);

/**
 * @brief 此函数用于取消初始化OpenThread网络接口胶。
 *
 */
void esp_openthread_netif_glue_deinit(void);

/**
 * @brief 此函数获取OpenThread netif。
 *
 * @return 如果未初始化，OpenThread netif或NULL。
 *
 */
esp_netif_t *esp_openthread_get_netif(void);

#ifdef __cplusplus
}
#endif

