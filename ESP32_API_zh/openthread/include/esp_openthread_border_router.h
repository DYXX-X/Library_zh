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

#include "esp_netif.h"
#include "esp_netif_types.h"
#include "esp_openthread.h"
#include "openthread/instance.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief   初始化OpenThread的边界路由器功能。
 *
 * @note 调用此函数将使设备表现为OpenThread边界路由器。需要Kconfig选项CONFIG_OPENTHREAD_BORDER_ROUTER。
 *
 * @param[in]  backbone_netif   骨干网络接口（WiFi或以太网）
 *
 * @return
 *      -成功时ESP_OK
 *      -ESP_ERR_NOT_SUPPORTED（如果功能不受支持）
 *      -ESP_ERR_INVALID_STATE（如果已初始化）
 *      -其他故障的ESP_FIAL
 *
 */
esp_err_t esp_openthread_border_router_init(esp_netif_t *backbone_netif);

/**
 * @brief   取消初始化OpenThread的边界路由器功能。
 *
 * @return
 *      -成功时ESP_OK
 *      -ESP_ERR_INVALID_STATE（如果未初始化）
 *      -其他故障的ESP_FIAL
 *
 */
esp_err_t esp_openthread_border_router_deinit(void);

/**
 * @brief   获取OpenThread边界路由器的主干接口。
 *
 * @return 骨干接口，如果边界路由器未初始化，则为NULL。
 *
 */
esp_netif_t *esp_openthread_get_backbone_netif(void);

#ifdef __cplusplus
}
#endif

