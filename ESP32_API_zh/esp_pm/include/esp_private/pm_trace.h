// 版权所有2016-2017 Espressif Systems（上海）私人有限公司
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

#include "sdkconfig.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    ESP_PM_TRACE_IDLE,
    ESP_PM_TRACE_TICK,
    ESP_PM_TRACE_FREQ_SWITCH,
    ESP_PM_TRACE_CCOMPARE_UPDATE,
    ESP_PM_TRACE_ISR_HOOK,
    ESP_PM_TRACE_SLEEP,
    ESP_PM_TRACE_TYPE_MAX
} esp_pm_trace_event_t;

void esp_pm_trace_init(void);
void esp_pm_trace_enter(esp_pm_trace_event_t event, int core_id);
void esp_pm_trace_exit(esp_pm_trace_event_t event, int core_id);

#ifdef CONFIG_PM_TRACE

#define ESP_PM_TRACE_ENTER(event, core_id)   \
            esp_pm_trace_enter(ESP_PM_TRACE_ ## event, core_id)
#define ESP_PM_TRACE_EXIT(event, core_id)    \
            esp_pm_trace_exit(ESP_PM_TRACE_ ## event, core_id)

#else // CONFIG_PM_TRACE

#define ESP_PM_TRACE_ENTER(type, core_id) do { (void) core_id; } while(0)
#define ESP_PM_TRACE_EXIT(type, core_id)  do { (void) core_id; } while(0)

#endif // CONFIG_PM_TRACE

#ifdef __cplusplus
}
#endif

