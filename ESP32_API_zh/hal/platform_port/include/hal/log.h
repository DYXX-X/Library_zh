// 版权所有2021 Espressif Systems（Shanghai）PTE LTD
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

#pragma once

#include "esp_log.h"

#define HAL_LOGE(...)    ESP_LOGE(__VA_ARGS__)
#define HAL_LOGW(...)    ESP_LOGW(__VA_ARGS__)
#define HAL_LOGI(...)    ESP_LOGI(__VA_ARGS__)
#define HAL_LOGD(...)    ESP_LOGD(__VA_ARGS__)
#define HAL_LOGV(...)    ESP_LOGV(__VA_ARGS__)

#define HAL_EARLY_LOGE(...)    ESP_EARLY_LOGE(__VA_ARGS__)
#define HAL_EARLY_LOGW(...)    ESP_EARLY_LOGW(__VA_ARGS__)
#define HAL_EARLY_LOGI(...)    ESP_EARLY_LOGI(__VA_ARGS__)
#define HAL_EARLY_LOGD(...)    ESP_EARLY_LOGD(__VA_ARGS__)
#define HAL_EARLY_LOGV(...)    ESP_EARLY_LOGV(__VA_ARGS__)

