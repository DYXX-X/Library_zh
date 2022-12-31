// 版权所有2018 Espressif Systems（上海）私人有限公司
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

#ifndef ESP_EVENT_PRIVATE_H_
#define ESP_EVENT_PRIVATE_H_

#include <stdbool.h>
#include "esp_event.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 搜索使用事件循环注册的处理程序，以查看它是否已注册。
 *
 * @param[in] event_loop 要搜索的循环
 * @param[in] event_base 要搜索的事件库
 * @param[in] event_id 要搜索的事件id
 * @param[in] event_handler 要查找的事件处理程序
 *
 * @return 已注册true处理程序
 * @return 未注册false处理程序
 *
 * @return
 *  -true:已注册处理程序
 *  -false:未注册处理程序
 */
bool esp_event_is_handler_registered(esp_event_loop_handle_t event_loop, esp_event_base_t event_base, int32_t event_id, esp_event_handler_t event_handler);

/**
 * @brief 取消初始化事件循环库
 *
 * @return
 *  -ESP_OK：成功
 *  -其他：失败
 */
esp_err_t esp_event_loop_deinit(void);

#ifdef __cplusplus
} // 外部“C”
#endif

#endif // #如果是ESP_EVENT_PRIVATE_H_

