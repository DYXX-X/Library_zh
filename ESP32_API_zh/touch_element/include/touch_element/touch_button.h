// 版权所有2016-2020 Espressif Systems（上海）私人有限公司
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

#include "touch_element/touch_element.h"

#ifdef __cplusplus
extern "C" {
#endif
/* ---------------------------------常规按钮实例默认配置------------------------------*/
#define TOUCH_BUTTON_GLOBAL_DEFAULT_CONFIG()                                  \
{                                                                             \
    .threshold_divider = 0.8,                                                 \
    .default_lp_time = 1000                                                   \
}
/* ------------------------------------------------------------------------------------------------------------------ */

/**
 * @brief   按钮初始化配置传递给touch_Button_install
 */
typedef struct {
    float threshold_divider;        //!< 按钮通道阈值除法器
    uint32_t default_lp_time;       //!< 按钮默认LongPress事件时间（毫秒）
} touch_button_global_config_t;

/**
 * @brief   按钮配置（用于新实例）传递给touch_Button_create（）
 */
typedef struct {
    touch_pad_t channel_num;     //!< 按钮通道编号（索引）
    float channel_sens;          //!< 按钮通道灵敏度
} touch_button_config_t;

/**
 * @brief   按钮事件类型
 */
typedef enum {
    TOUCH_BUTTON_EVT_ON_PRESS,         //!< 按钮按下事件
    TOUCH_BUTTON_EVT_ON_RELEASE,       //!< 按钮释放事件
    TOUCH_BUTTON_EVT_ON_LONGPRESS,     //!< Button LongPress事件
    TOUCH_BUTTON_EVT_MAX
} touch_button_event_t;

/**
 * @brief   按钮消息类型
 */
typedef struct {
    touch_button_event_t event;        //!< 按钮事件
} touch_button_message_t;

typedef touch_elem_handle_t touch_button_handle_t;      //!< 按钮手柄
typedef void(*touch_button_callback_t)(touch_button_handle_t, touch_button_message_t *, void *); //!< 按钮回调类型

/**
 * @brief   触摸按钮初始化
 *
 * 此函数初始化触摸按钮全局并作用于所有触摸按钮实例。
 *
 * @param[in] global_config   按钮对象初始化配置
 *
 * @return
 *      -ESP_OK：已成功初始化触摸按钮
 *      -ESP_ERR_INVALID_STATE:触摸元素库未初始化
 *      -ESP_ERR_INVALID_ARG:button_it为空
 *      -ESP_ERR_NO_MEM:内存不足
 */
esp_err_t touch_button_install(const touch_button_global_config_t *global_config);

/**
 * @brief   释放使用touch_button_install（）分配的资源
 */
void touch_button_uninstall(void);

/**
 * @brief   创建新的触摸按钮实例
 *
 * @param[in]  button_config    按钮配置
 * @param[out] button_handle    按钮手柄
 *
 * @note    必须在实验中探索灵敏度，灵敏度=（原始（触摸）-原始（释放））/原始（释放
 *
 * @return
 *      -ESP_OK：成功创建触摸按钮
 *      -ESP_ERR_INVALID_STATE:触摸按钮驱动程序未初始化
 *      -ESP_ERR_NO_MEM:内存不足
 *      -ESP_ERR_INVALID_ARG:配置结构无效或参数为NULL
 */
esp_err_t touch_button_create(const touch_button_config_t *button_config, touch_button_handle_t *button_handle);

/**
 * @brief 释放使用touch_button_create（）分配的资源
 *
 * @param[in] button_handle   按钮手柄
 * @return
 *      -ESP_OK：已成功释放资源
 *      -ESP_ERR_INVALID_STATE:触摸按钮驱动程序未初始化
 *      -ESP_ERR_INVALID_ARG:按钮句柄为空
 *      -ESP_ERR_NOT_FOUND：输入手柄不是按钮手柄
 */
esp_err_t touch_button_delete(touch_button_handle_t button_handle);

/**
 * @brief   触摸按钮订阅事件
 *
 * 此函数使用事件掩码订阅触摸按钮事件，一旦订阅的事件之一发生，可以通过调用touch_element_message_receive（）或输入回调例程来检索事件消息。
 *
 * @param[in] button_handle     按钮手柄
 * @param[in] event_mask        按钮订阅事件掩码
 * @param[in] arg               用户输入参数
 *
 * @note    触摸按钮仅支持三种事件掩码，它们是Touch_ELEM_event_ON_PRESS、Touch_LEM_event-ON_RELEASE、Touch-ELEM_event_ON_LONGPRESS。您可以任意组合使用这些事件掩码来实现所需的效果。
 *
 * @return
 *      -ESP_OK：已成功订阅触摸按钮事件
 *      -ESP_ERR_INVALID_STATE:触摸按钮驱动程序未初始化
 *      -ESP_ERR_INVALID_ARG:button_handle为空或不支持事件
 */
esp_err_t touch_button_subscribe_event(touch_button_handle_t button_handle, uint32_t event_mask, void *arg);

/**
 * @brief   触摸按钮组调度方法
 *
 * 此函数设置一个分派方法，驱动程序核心将使用此方法作为事件通知方法。
 *
 * @param[in] button_handle     按钮手柄
 * @param[in] dispatch_method   调度方法（通过回调/事件）
 *
 * @return
 *      -ESP_OK：已成功设置分派方法
 *      -ESP_ERR_INVALID_STATE:触摸按钮驱动程序未初始化
 *      -ESP_ERR_INVALID_ARG:button_handle为空或dispatch_method无效
 */
esp_err_t touch_button_set_dispatch_method(touch_button_handle_t button_handle, touch_elem_dispatch_t dispatch_method);

/**
 * @brief   触摸按钮设置回拨
 *
 * 此函数将回调例程设置到触摸元素驱动程序核心中，当订阅事件发生时，将调用回调例程。
 *
 * @param[in] button_handle     按钮手柄
 * @param[in] button_callback   用户输入回调
 *
 * @note        按钮消息将从回调函数传递，当回调函数返回时将被销毁。
 *
 * @warning     由于此输入回调例程在驱动程序核心上运行（esp计时器回调例程），因此它不应该执行试图阻止的操作，例如调用vTaskDelay（）。
 *
 * @return
 *      -ESP_OK:已成功设置回调
 *      -ESP_ERR_INVALID_STATE:触摸按钮驱动程序未初始化
 *      -ESP_ERR_INVALID_ARG:button_handle或button_callback为空
 */
esp_err_t touch_button_set_callback(touch_button_handle_t button_handle, touch_button_callback_t button_callback);

/**
 * @brief   触摸按钮设置长按触发时间
 *
 * 此功能设置长按事件的阈值时间（毫秒）。如果按钮被按下并保持超过阈值时间，则会触发长按事件。
 *
 * @param[in] button_handle     按钮手柄
 * @param[in] threshold_time    长按事件发生的阈值时间（ms）
 *
 * @return
 *      -ESP_OK：成功设置长按事件的阈值时间
 *      -ESP_ERR_INVALID_STATE:触摸按钮驱动程序未初始化
 *      -ESP_ERR_INVALID_ARG:按钮句柄为空或时间（毫秒）不大于0
 */
esp_err_t touch_button_set_longpress(touch_button_handle_t button_handle, uint32_t threshold_time);

/**
 * @brief   触摸按钮获取信息
 *
 * 此函数解码touch_element_message_receive（）中的元素消息，并返回按钮消息指针。
 *
 * @param[in] element_message   元素消息
 *
 * @return  触摸按钮信息指针
 */
const touch_button_message_t* touch_button_get_message(const touch_elem_message_t* element_message);

#ifdef __cplusplus
}
#endif

