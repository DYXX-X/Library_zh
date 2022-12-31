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

/* ---------------------------------常规滑块实例默认配置------------------------------*/
#define TOUCH_SLIDER_GLOBAL_DEFAULT_CONFIG()                                  \
{                                                                             \
    .quantify_lower_threshold = 0.3,                                          \
    .threshold_divider = 0.8,                                                 \
    .filter_reset_time = 50,                                                  \
    .benchmark_update_time = 500,                                             \
    .position_filter_size = 10,                                               \
    .position_filter_factor = 2,                                              \
    .calculate_channel_count = 3                                              \
}
/* ------------------------------------------------------------------------------------------------------------------ */

/**
 * @brief   滑块初始化配置传递给touch_Slider_install
 */
typedef struct {
    float quantify_lower_threshold;            //!< 滑块信号量化阈值
    float threshold_divider;                   //!< 滑块通道阈值除法器
    uint16_t filter_reset_time;                //!< 滑块位置过滤器重置时间（单位为esp_timer回调时间）
    uint16_t benchmark_update_time;            //!< 滑块基准更新时间（单位为esp_timer回调时间）
    uint8_t position_filter_size;              //!< 移动窗口筛选器缓冲区大小
    uint8_t position_filter_factor;            //!< 一阶IIR滤波器系数
    uint8_t calculate_channel_count;           //!< 将参与计算的通道数
} touch_slider_global_config_t;

/**
 * @brief   滑块配置（用于新实例）传递给touch_Slider_create（）
 */
typedef struct {
    const touch_pad_t *channel_array;    //!< 滑块通道阵列
    const float *sensitivity_array;      //!< 滑块通道灵敏度阵列
    uint8_t channel_num;                 //!< 滑块通道的数量
    uint8_t position_range;              //!< 触摸滑块位置范围的右侧区域[0，position_range（小于或等于255）]
} touch_slider_config_t;

/**
 * @brief   滑块事件类型
 */
typedef enum {
    TOUCH_SLIDER_EVT_ON_PRESS,                  //!< 按下滑块事件
    TOUCH_SLIDER_EVT_ON_RELEASE,                //!< 释放事件时的滑块
    TOUCH_SLIDER_EVT_ON_CALCULATION,            //!< “计算”事件上的滑块
    TOUCH_SLIDER_EVT_MAX
} touch_slider_event_t;

typedef uint32_t touch_slider_position_t;       //!< 滑块位置数据类型

/**
 * @brief   滑块消息类型
 */
typedef struct {
    touch_slider_event_t event;                 //!< 滑块事件
    touch_slider_position_t position;           //!< 滑块位置
} touch_slider_message_t;

typedef touch_elem_handle_t touch_slider_handle_t;   //!< 滑块实例控制柄
typedef void(*touch_slider_callback_t)(touch_slider_handle_t, touch_slider_message_t *, void *); //!< 滑块回调类型

/**
 * @brief   触摸滑块初始化
 *
 * 此函数初始化触摸滑块对象并作用于所有触摸滑块实例。
 *
 * @param[in] global_config   触摸滑块全局初始化配置
 *
 * @return
 *      -ESP_OK：已成功初始化触摸滑块
 *      -ESP_ERR_INVALID_STATE:触摸元素库未初始化
 *      -ESP_ERR_INVALID_ARG:slider_init为空
 *      -ESP_ERR_NO_MEM:内存不足
 */
esp_err_t touch_slider_install(const touch_slider_global_config_t *global_config);

/**
 * @brief   释放使用touch_slider_install（）分配的资源
 *
 * @return
 *      -ESP_OK：已成功释放资源
 */
void touch_slider_uninstall(void);

/**
* @brief   创建新的触摸滑块实例
*
* @param[in]  slider_config     滑块配置
* @param[out] slider_handle     滑块控制柄
*
* @note    通道阵列和灵敏度阵列的索引必须一一对应
*
* @return
*      -ESP_OK：成功创建触摸滑块
*      -ESP_ERR_INVALID_STATE:触摸滑块驱动程序未初始化
*      -ESP_ERR_INVALID_ARG:配置结构无效或参数为NULL
*      -ESP_ERR_NO_MEM:内存不足
*/
esp_err_t touch_slider_create(const touch_slider_config_t *slider_config, touch_slider_handle_t *slider_handle);

/**
 * @brief   释放使用touch_slider_create分配的资源
 *
 * @param[in] slider_handle   滑块控制柄
 * @return
 *      -ESP_OK：已成功释放资源
 *      -ESP_ERR_INVALID_STATE:触摸滑块驱动程序未初始化
 *      -ESP_ERR_INVALID_ARG:滑块句柄为空
 *      -ESP_ERR_NOT_FOUND：输入句柄不是滑块句柄
 */
esp_err_t touch_slider_delete(touch_slider_handle_t slider_handle);

/**
 * @brief   触摸滑块订阅事件
 *
 * 此函数使用事件掩码订阅触摸滑块事件，一旦订阅的事件之一发生，可以通过调用touch_element_message_receive（）或输入回调例程来检索事件消息。
 *
 * @param[in] slider_handle     滑块控制柄
 * @param[in] event_mask        滑块订阅事件掩码
 * @param[in] arg               用户输入参数
 *
 * @note    触摸滑块仅支持三种事件掩码，它们是Touch_ELEM_event_ON_PRESS、Touch_LEM_event-ON_RELEASE。您可以任意组合使用这些事件掩码来实现所需的效果。
 *
 * @return
 *      -ESP_OK：已成功订阅触摸滑块事件
 *      -ESP_ERR_INVALID_STATE:触摸滑块驱动程序未初始化
 *      -ESP_ERR_INVALID_ARG:slider_handle为空或不支持事件
 */
esp_err_t touch_slider_subscribe_event(touch_slider_handle_t slider_handle, uint32_t event_mask, void *arg);

/**
 * @brief   触摸滑块集调度方法
 *
 * 此函数设置一个分派方法，驱动程序核心将使用此方法作为事件通知方法。
 *
 * @param[in] slider_handle     滑块控制柄
 * @param[in] dispatch_method   调度方法（通过回调/事件）
 *
 * @return
 *      -ESP_OK：已成功设置分派方法
 *      -ESP_ERR_INVALID_STATE:触摸滑块驱动程序未初始化
 *      -ESP_ERR_INVALID_ARG:slider_handle为空或dispatch_method无效
 */
esp_err_t touch_slider_set_dispatch_method(touch_slider_handle_t slider_handle, touch_elem_dispatch_t dispatch_method);

/**
 * @brief   触摸滑块设置回调
 *
 * 此函数将回调例程设置到触摸元素驱动程序核心中，当订阅事件发生时，将调用回调例程。
 *
 * @param[in] slider_handle     滑块控制柄
 * @param[in] slider_callback   用户输入回调
 *
 * @note        滑块消息将从回调函数传递，当回调函数返回时将被销毁。
 *
 * @warning     由于此输入回调例程在驱动程序核心上运行（esp计时器回调例程），因此它不应该执行试图阻止的操作，例如调用vTaskDelay（）。
 *
 * @return
 *      -ESP_OK:已成功设置回调
 *      -ESP_ERR_INVALID_STATE:触摸滑块驱动程序未初始化
 *      -ESP_ERR_INVALID_ARG:slider_handle或slider_callback为空
 */
esp_err_t touch_slider_set_callback(touch_slider_handle_t slider_handle, touch_slider_callback_t slider_callback);

/**
 * @brief   触摸滑块获取消息
 *
 * 此函数解码touch_element_message_receive（）中的元素消息，并返回滑块消息指针。
 *
 * @param[in] element_message   元素消息
 *
 * @return  触摸滑块消息指针
 */
const touch_slider_message_t* touch_slider_get_message(const touch_elem_message_t* element_message);

#ifdef __cplusplus
}
#endif

