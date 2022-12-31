// 版权所有2021 Espressif Systems（Shanghai）PTE LTD
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

#include "stdbool.h"
#include "esp_err.h"
#include "esp_event_base.h"
#include "bsd_strings.h"

#define ESP_EVENT_DECLARE_BASE(x)
#define ESP_EVENT_ANY_ID       (-1)

typedef void * esp_event_base_t;
typedef void * system_event_t;

const char* WIFI_EVENT;
const char* IP_EVENT;

esp_err_t esp_event_handler_register(const char * event_base, int32_t event_id, void* event_handler, void* event_handler_arg);

esp_err_t esp_event_handler_unregister(const char * event_base, int32_t event_id, void* event_handler);

