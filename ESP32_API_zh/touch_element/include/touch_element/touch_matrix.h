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

/* -----------------------------通用矩阵按钮实例默认配置------------------------------*/
#define TOUCH_MATRIX_GLOBAL_DEFAULT_CONFIG()                                  \
{                                                                             \
    .threshold_divider = 0.8,                                                 \
    .default_lp_time = 1000                                                   \
}
/* ------------------------------------------------------------------------------------------------------------------ */
/**
 * @brief   矩阵按钮初始化配置传递给touch_Matrix_install
 */
typedef struct {
    float threshold_divider;        //!< 矩阵按钮通道阈值除法器
    uint32_t default_lp_time;       //!< 矩阵按钮默认LongPress事件时间（毫秒）
} touch_matrix_global_config_t;

/**
 * @brief   矩阵按钮配置（用于新实例）传递给touch_Matrix_create（）
 */
typedef struct {
    const touch_pad_t *x_channel_array;      //!< 矩阵按钮x轴通道阵列
    const touch_pad_t *y_channel_array;      //!< 矩阵按钮y轴通道阵列
    const float *x_sensitivity_array;        //!< 矩阵按钮x轴通道灵敏度阵列
    const float *y_sensitivity_array;        //!< 矩阵按钮y轴通道灵敏度阵列
    uint8_t x_channel_num;                   //!< x轴上的通道数
    uint8_t y_channel_num;                   //!< y轴上的通道数
} touch_matrix_config_t;

/**
 * @brief   矩阵按钮事件类型
 */
typedef enum {
    TOUCH_MATRIX_EVT_ON_PRESS,            //!< 矩阵按钮按下事件
    TOUCH_MATRIX_EVT_ON_RELEASE,          //!< 矩阵按钮按下事件
    TOUCH_MATRIX_EVT_ON_LONGPRESS,        //!< 矩阵按钮LongPress事件
    TOUCH_MATRIX_EVT_MAX
} touch_matrix_event_t;

/**
 * @brief   矩阵按钮位置数据类型
 */
typedef struct {
    uint8_t x_axis;     //!< 矩阵按钮x轴位置
    uint8_t y_axis;     //!< 矩阵按钮y轴位置
    uint8_t index;      //!< 矩阵按钮位置索引
} touch_matrix_position_t;

/**
 * @brief   矩阵消息类型
 */
typedef struct {
    touch_matrix_event_t event;             //!< 矩阵事件
    touch_matrix_position_t position;       //!< 矩阵位置
} touch_matrix_message_t;

typedef touch_elem_handle_t touch_matrix_handle_t;  //!< 矩阵按钮实例句柄
typedef void(*touch_matrix_callback_t)(touch_matrix_handle_t, touch_matrix_message_t *, void *); //!< 矩阵按钮回调类型

/**
 * @brief   触摸矩阵按钮初始化
 *
 * 此函数初始化触摸矩阵按钮对象并作用于所有触摸矩阵按钮实例。
 *
 * @param[in] global_config   触摸矩阵全局初始化配置
 *
 * @return
 *      -ESP_OK：已成功初始化触摸矩阵按钮
 *      -ESP_ERR_INVALID_STATE:触摸元素库未初始化
 *      -ESP_ERR_INVALID_ARG:matrix_init为空
 *      -ESP_ERR_NO_MEM:内存不足
 */
esp_err_t touch_matrix_install(const touch_matrix_global_config_t *global_config);

/**
 * @brief   释放使用touch_matrix_install（）分配的资源
 *
 * @return
 *      -ESP_OK：已成功释放资源
 */
void touch_matrix_uninstall(void);

/**
 * @brief   创建新的触摸矩阵按钮实例
 *
 * @param[in]  matrix_config    矩阵按钮配置
 * @param[out] matrix_handle    矩阵按钮手柄
 *
 * @note    通道阵列和灵敏度阵列必须是这些阵列中的一一对应
 *
 * @note    触摸矩阵按钮现在不支持多点触摸
 *
 * @return
 *      -ESP_OK：成功创建触摸矩阵按钮
 *      -ESP_ERR_INVALID_STATE:触摸矩阵驱动程序未初始化
 *      -ESP_ERR_INVALID_ARG:配置结构无效或参数为NULL
 *      -ESP_ERR_NO_MEM:内存不足
 */
esp_err_t touch_matrix_create(const touch_matrix_config_t *matrix_config, touch_matrix_handle_t *matrix_handle);

/**
 * @brief   释放使用touch_matrix_create（）分配的资源
 *
 * @param[in] matrix_handle    矩阵手柄
 * @return
 *      -ESP_OK：已成功释放资源
 *      -ESP_ERR_INVALID_STATE:触摸矩阵驱动程序未初始化
 *      -ESP_ERR_INVALID_ARG:矩阵句柄为空
 *      -ESP_ERR_NOT_FOUND：输入句柄不是矩阵句柄
 */
esp_err_t touch_matrix_delete(touch_matrix_handle_t matrix_handle);

/**
 * @brief   触摸矩阵按钮订阅事件
 *
 * 此函数使用事件掩码订阅触摸矩阵事件，一旦订阅的事件之一发生，可以通过调用touch_element_message_receive（）或输入回调例程来检索事件消息。
 *
 * @param[in] matrix_handle     矩阵手柄
 * @param[in] event_mask        矩阵订阅事件掩码
 * @param[in] arg               用户输入参数
 *
 * @note    触摸矩阵按钮仅支持三种事件掩码，它们是Touch_ELEM_event_ON_PRESS、Touch_LEM_event-ON_RELEASE、Touch-ELEM_event_ON_LONGPRESS。您可以任意组合使用这些事件掩码来实现所需的效果。
 *
 * @return
 *      -ESP_OK：成功订阅触摸矩阵事件
 *      -ESP_ERR_INVALID_STATE:触摸矩阵驱动程序未初始化
 *      -ESP_ERR_INVALID_ARG:matrix_handle为空或不支持事件
 */
esp_err_t touch_matrix_subscribe_event(touch_matrix_handle_t matrix_handle, uint32_t event_mask, void *arg);

/**
 * @brief   触摸矩阵按钮组调度方法
 *
 * 此函数设置一个分派方法，驱动程序核心将使用此方法作为事件通知方法。
 *
 * @param[in] matrix_handle     矩阵按钮手柄
 * @param[in] dispatch_method   调度方法（通过回调/事件）
 *
 * @return
 *      -ESP_OK：已成功设置分派方法
 *      -ESP_ERR_INVALID_STATE:触摸矩阵驱动程序未初始化
 *      -ESP_ERR_INVALID_ARG:matrix_handle为空或dispatch_method无效
 */
esp_err_t touch_matrix_set_dispatch_method(touch_matrix_handle_t matrix_handle, touch_elem_dispatch_t dispatch_method);

/**
 * @brief   触摸矩阵按钮集回调
 *
 * 此函数将回调例程设置到触摸元素驱动程序核心中，当订阅事件发生时，将调用回调例程。
 *
 * @param[in] matrix_handle     矩阵按钮手柄
 * @param[in] matrix_callback   用户输入回调
 *
 * @note        矩阵消息将从回调函数传递，当回调函数返回时将被销毁。
 *
 * @warning     由于此输入回调例程在驱动程序核心上运行（esp计时器回调例程），因此它不应该执行试图阻止的操作，例如调用vTaskDelay（）。
 *
 * @return
 *      -ESP_OK:已成功设置回调
 *      -ESP_ERR_INVALID_STATE:触摸矩阵驱动程序未初始化
 *      -ESP_ERR_INVALID_ARG:矩阵句柄或矩阵回调为空
 */
esp_err_t touch_matrix_set_callback(touch_matrix_handle_t matrix_handle, touch_matrix_callback_t matrix_callback);

/**
 * @brief   触摸矩阵按钮设置长按触发时间
 *
 * 此功能设置长按事件的阈值时间（毫秒）。如果按下并保持矩阵按钮超过阈值时间，则会触发长按事件。
 *
 * @param[in] matrix_handle     矩阵按钮手柄
 * @param[in] threshold_time    长按事件发生的阈值时间（ms）
 *
 * @return
 *      -ESP_OK：成功设置长按事件的时间
 *      -ESP_ERR_INVALID_STATE:触摸矩阵驱动程序未初始化
 *      -ESP_ERR_INVALID_ARG：矩阵句柄为空或时间（ms）为0
 */
esp_err_t touch_matrix_set_longpress(touch_matrix_handle_t matrix_handle, uint32_t threshold_time);

/**
 * @brief   触摸矩阵获取信息
 *
 * 此函数解码touch_element_message_receive（）中的元素消息，并返回矩阵消息指针。
 *
 * @param[in] element_message   元素消息
 *
 * @return  触摸矩阵消息指针
 */
const touch_matrix_message_t* touch_matrix_get_message(const touch_elem_message_t* element_message);

#ifdef __cplusplus
}
#endif

