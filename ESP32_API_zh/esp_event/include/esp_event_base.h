// 版权所有2018 Espressif Systems（上海）私人有限公司
//
// 根据Apache许可证2.0版（“许可证”）获得许可；
// 除非符合许可证，否则不得使用此文件。
// 您可以在以下地址获取许可证副本：
//
//         http://www.apache.org/licenses/LICENSE-2.0
//
// 除非适用法律要求或书面同意，软件
// 根据许可证分发的内容是按“原样”分发的，
// 无任何明示或暗示的保证或条件。
// 有关管理权限和
// 许可证下的限制。

#ifndef ESP_EVENT_BASE_H_
#define ESP_EVENT_BASE_H_

#ifdef __cplusplus
extern "C" {
#endif

// 用于声明和定义事件基的定义
#define ESP_EVENT_DECLARE_BASE(id) extern esp_event_base_t id
#define ESP_EVENT_DEFINE_BASE(id) esp_event_base_t id = #id

// 事件循环库类型
typedef const char*  esp_event_base_t; /**<指向公开事件的子系统的唯一指针*/
typedef void*        esp_event_loop_handle_t; /**<一个数字，用于标识与基础相关的事件*/
typedef void         (*esp_event_handler_t)(void* event_handler_arg,
                                        esp_event_base_t event_base,
                                        int32_t event_id,
                                        void* event_data); /**<当事件发布到队列时调用的函数*/
typedef void*        esp_event_handler_instance_t; /**<context标识已注册事件处理程序的实例*/

// 用于注册/注销事件处理程序的定义
#define ESP_EVENT_ANY_BASE     NULL             /**<为任何事件基注册处理程序*/
#define ESP_EVENT_ANY_ID       -1               /**<为任何事件id注册处理程序*/

#ifdef __cplusplus
}
#endif

#endif // #如果是ESP_EVENT_BASE_H_

