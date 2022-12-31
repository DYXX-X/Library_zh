/*
 * SPDX文件版权文本：2015-2021浓缩咖啡系统（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */

#pragma once

#include "esp_err.h"
#include "esp_intr_alloc.h"
#include "soc/soc.h"
#include "hal/ledc_types.h"
#include "driver/gpio.h"
#include "driver/periph_ctrl.h"

#ifdef __cplusplus
extern "C" {
#endif

#define LEDC_APB_CLK_HZ  (APB_CLK_FREQ)
#define LEDC_REF_CLK_HZ  (REF_CLK_FREQ)
#define LEDC_ERR_DUTY    (0xFFFFFFFF)
#define LEDC_ERR_VAL     (-1)

typedef intr_handle_t ledc_isr_handle_t;

/**
 * @brief LEDC回调事件类型
 */
typedef enum {
    LEDC_FADE_END_EVT                   /**<LEDC淡入结束事件*/
} ledc_cb_event_t;

/**
 * @brief LEDC回调参数
 */
typedef struct {
    ledc_cb_event_t event;              /**<事件名称*/
    uint32_t speed_mode;                /**<LEDC通道组的速度模式*/
    uint32_t channel;                   /**<LEDC通道（0-LEDC_channel_MAX-1）*/
    uint32_t duty;                      /**<信道的LEDC当前占空比，占空比范围为[0，（2**占空比分辨率）-1]*/
} ledc_cb_param_t;

/**
 * @brief LEDC事件回调类型
 * @param param LEDC回调参数
 * @param user_arg 用户注册数据
 */
typedef bool (* ledc_cb_t)(const ledc_cb_param_t *param, void *user_arg);

/**
 * @brief 支持的LEDC回调组
 * @note 回调都在ISR环境下运行
 */
typedef struct {
    ledc_cb_t fade_cb;                  /**<LEDC fade_end回调函数*/
} ledc_cbs_t;

/**
 * @brief LEDC通道配置使用给定的通道/输出gpio_num/中断/源计时器/频率（Hz）/LEDC占空比分辨率配置LEDC通道
 *
 * @param ledc_conf LEDC通道配置结构的指针
 *
 * @return
 *     -ESP_OK成功
 *     -ESP_ERR_INVALID_ARG参数错误
 */
esp_err_t ledc_channel_config(const ledc_channel_config_t* ledc_conf);

/**
 * @brief LEDC计时器配置使用给定的源计时器/频率（Hz）/duty_resolution配置LEDC计时器
 *
 * @param  timer_conf LEDC计时器配置结构的指针
 *
 * @return
 *     -ESP_OK成功
 *     -ESP_ERR_INVALID_ARG参数错误
 *     -ESP_FAIL无法根据给定频率和当前duty_resolution找到正确的预分频器编号。
 */
esp_err_t ledc_timer_config(const ledc_timer_config_t* timer_conf);

/**
 * @brief LEDC更新通道参数
 * @note  调用此函数以激活LEDC更新的参数。在ledc_set_duty之后，我们需要调用此函数来更新设置。新的LEDC参数直到下一个PWM周期才会生效。
 * @note  ledc_set_duty、ledc_set-duty_with_hpoint和ledc_update_duty不是线程安全的，请不要调用这些函数来同时控制不同任务中的一个ledc通道。API的线程安全版本是ledc_set_duty_and_update
 * @param speed_mode 选择具有指定速度模式的LEDC通道组。请注意，并非所有目标都支持高速模式。
 * @param channel LEDC通道（0-LEDC_channel_MAX-1），从LEDC_channel_t中选择
 *
 * @return
 *     -ESP_OK成功
 *     -ESP_ERR_INVALID_ARG参数错误
 *
 */
esp_err_t ledc_update_duty(ledc_mode_t speed_mode, ledc_channel_t channel);

/**
 * @brief 设置LEDC输出gpio。
 * @deprecated 此功能是冗余的，请使用ledc_channel_config设置gpio引脚。
 *
 * @param  gpio_num LEDC输出gpio
 * @param  speed_mode 选择具有指定速度模式的LEDC通道组。请注意，并非所有目标都支持高速模式。
 * @param  ledc_channel LEDC通道（0-LEDC_channel_MAX-1），从LEDC_channel_t中选择
 *
 * @return
 *     -ESP_OK成功
 *     -ESP_ERR_INVALID_ARG参数错误
 */
esp_err_t ledc_set_pin(int gpio_num, ledc_mode_t speed_mode, ledc_channel_t ledc_channel)
    __attribute__((deprecated("use ledc_channel_config instead")));
/**
 * @brief LEDC停止。禁用LEDC输出，并设置空闲电平
 *
 * @param  speed_mode 选择具有指定速度模式的LEDC通道组。请注意，并非所有目标都支持高速模式。
 * @param  channel LEDC通道（0-LEDC_channel_MAX-1），从LEDC_channel_t中选择
 * @param  idle_level 在LEDC停止后设置输出空闲水平。
 *
 * @return
 *     -ESP_OK成功
 *     -ESP_ERR_INVALID_ARG参数错误
 */
esp_err_t ledc_stop(ledc_mode_t speed_mode, ledc_channel_t channel, uint32_t idle_level);

/**
 * @brief LEDC设置通道频率（Hz）
 *
 * @param speed_mode 选择具有指定速度模式的LEDC通道组。请注意，并非所有目标都支持高速模式。
 * @param  timer_num LEDC计时器索引（0-3），从LEDC_timer_t中选择
 * @param  freq_hz 设置LEDC频率
 *
 * @return
 *     -ESP_OK成功
 *     -ESP_ERR_INVALID_ARG参数错误
 *     -ESP_FAIL无法根据给定频率和当前duty_resolution找到正确的预分频器编号。
 */
esp_err_t ledc_set_freq(ledc_mode_t speed_mode, ledc_timer_t timer_num, uint32_t freq_hz);

/**
 * @brief      LEDC获取信道频率（Hz）
 *
 * @param speed_mode 选择具有指定速度模式的LEDC通道组。请注意，并非所有目标都支持高速模式。
 * @param timer_num LEDC计时器索引（0-3），从LEDC_timer_t中选择
 *
 * @return
 *     -0错误
 *     -其他当前LEDC频率
 */
uint32_t ledc_get_freq(ledc_mode_t speed_mode, ledc_timer_t timer_num);

/**
 * @brief LEDC设置占空比和hpoint值只有在调用LEDC_update_duty后，占空比才会更新。
 * @note  ledc_set_duty、ledc_set-duty_with_hpoint和ledc_update_duty不是线程安全的，请不要调用这些函数来同时控制不同任务中的一个ledc通道。API的线程安全版本是ledc_set_duty_and_update
 * @note  如果该频道上正在进行淡入操作，则驱动程序将不允许停止该操作。其他值班操作将不得不等待，直到渐变操作完成。
 * @param speed_mode 选择具有指定速度模式的LEDC通道组。请注意，并非所有目标都支持高速模式。
 * @param channel LEDC通道（0-LEDC_channel_MAX-1），从LEDC_channel_t中选择
 * @param duty 设置LEDC占空比，占空比设置范围为[0，（2**duty_desolution）-1]
 * @param hpoint 设置LEDC hpoint值（最大值：0xfffff）
 *
 * @return
 *     -ESP_OK成功
 *     -ESP_ERR_INVALID_ARG参数错误
 */
esp_err_t ledc_set_duty_with_hpoint(ledc_mode_t speed_mode, ledc_channel_t channel, uint32_t duty, uint32_t hpoint);

/**
 * @brief LEDC获得hpoint值，即输出设置为高电平时的计数器值。
 *
 * @param speed_mode 选择具有指定速度模式的LEDC通道组。请注意，并非所有目标都支持高速模式。
 * @param channel LEDC通道（0-LEDC_channel_MAX-1），从LEDC_channel_t中选择
 * @return
 *     -LEDC_ERR_VAL（如果参数错误）
 *     -其他LEDC通道的当前hpoint值
 */
int ledc_get_hpoint(ledc_mode_t speed_mode, ledc_channel_t channel);

/**
 * @brief LEDC设置占空比此功能不会更改此通道的hpoint值。如果需要，请调用ledc_set_duty_with_hpoint。只有在调用ledc_update_duty之后，负载才会更新。
 * @note  ledc_set_duty、ledc_set-duty_with_hpoint和ledc_update_duty不是线程安全的，请不要调用这些函数来同时控制不同任务中的一个ledc通道。API的线程安全版本是ledc_set_duty_and_update。
 * @note  如果该频道上正在进行淡入操作，则驱动程序将不允许停止该操作。其他值班操作将不得不等待，直到渐变操作完成。
 * @param speed_mode 选择具有指定速度模式的LEDC通道组。请注意，并非所有目标都支持高速模式。
 * @param channel LEDC通道（0-LEDC_channel_MAX-1），从LEDC_channel_t中选择
 * @param duty 设置LEDC占空比，占空比设置范围为[0，（2**duty_desolution）-1]
 *
 * @return
 *     -ESP_OK成功
 *     -ESP_ERR_INVALID_ARG参数错误
 */
esp_err_t ledc_set_duty(ledc_mode_t speed_mode, ledc_channel_t channel, uint32_t duty);

/**
 * @brief LEDC获取占空比此函数返回当前PWM周期的占空比。您不应该期望函数在调用ledc_update_duty的同一周期中返回新的占空比，因为占空比更新直到下一个周期才会生效。
 *
 * @param speed_mode 选择具有指定速度模式的LEDC通道组。请注意，并非所有目标都支持高速模式。
 * @param channel LEDC通道（0-LEDC_channel_MAX-1），从LEDC_channel_t中选择
 *
 * @return
 *     -如果参数错误，则为LEDC_ERR_DUTY
 *     -其他当前LEDC职责
 */
uint32_t ledc_get_duty(ledc_mode_t speed_mode, ledc_channel_t channel);

/**
 * @brief LEDC设置梯度设置LEDC梯度，函数调用LEDC_update_duty函数后，函数即可生效。
 * @note  如果该频道上正在进行淡入操作，则驱动程序将不允许停止该操作。其他值班操作将不得不等待，直到渐变操作完成。
 * @param speed_mode 选择具有指定速度模式的LEDC通道组。请注意，并非所有目标都支持高速模式。
 * @param channel LEDC通道（0-LEDC_channel_MAX-1），从LEDC_channel_t中选择
 * @param duty 设置梯度占空比的开始，占空比设置范围为[0，（2**duty_desolution）-1]
 * @param fade_direction 设置渐变的方向
 * @param step_num 设置渐变的数量
 * @param duty_cycle_num 设置每次渐变持续时LEDC的刻度
 * @param duty_scale 设置梯度变化幅度
 *
 * @return
 *     -ESP_OK成功
 *     -ESP_ERR_INVALID_ARG参数错误
 */
esp_err_t ledc_set_fade(ledc_mode_t speed_mode, ledc_channel_t channel, uint32_t duty, ledc_duty_direction_t fade_direction,
                        uint32_t step_num, uint32_t duty_cycle_num, uint32_t duty_scale);

/**
 * @brief 注册LEDC中断处理程序，该处理程序是ISR。处理程序将连接到运行此函数的同一CPU内核。
 *
 * @param fn 中断处理程序函数。
 * @param arg 用户提供的参数传递给处理程序函数。
 * @param intr_alloc_flags 用于分配中断的标志。一个或多个（ORred）ESP_INTR_FLAG_值。请参见esp_intr_alloc。h了解更多信息。
 * @param handle 指向返回句柄的指针。如果非NULL，将在此处返回中断的句柄。
 *
 * @return
 *     -ESP_OK成功
 *     -ESP_ERR_INVALID_ARG函数指针错误。
 */
esp_err_t ledc_isr_register(void (*fn)(void*), void * arg, int intr_alloc_flags, ledc_isr_handle_t *handle);

/**
 * @brief 配置LEDC设置
 *
 * @param speed_mode 选择具有指定速度模式的LEDC通道组。请注意，并非所有目标都支持高速模式。
 * @param timer_sel  计时器索引（0-3），LEDC模块中有4个计时器
 * @param clock_divider 计时器时钟分频值，计时器时钟从所选时钟源分频
 * @param duty_resolution 占空比设置的分辨率（位数）。占空值范围为[0，（2**duty_desolution）]
 * @param clk_src 选择LEDC源时钟。
 *
 * @return
 *     -（-1）参数错误
 *     -其他当前LEDC负载
 */
esp_err_t ledc_timer_set(ledc_mode_t speed_mode, ledc_timer_t timer_sel, uint32_t clock_divider, uint32_t duty_resolution, ledc_clk_src_t clk_src);

/**
 * @brief 重置LEDC计时器
 *
 * @param  speed_mode 选择具有指定速度模式的LEDC通道组。请注意，并非所有目标都支持高速模式。
 * @param  timer_sel LEDC计时器索引（0-3），从LEDC_timer_t中选择
 *
 * @return
 *     -ESP_ERR_INVALID_ARG参数错误
 *     -ESP_OK成功
 */
esp_err_t ledc_timer_rst(ledc_mode_t speed_mode, ledc_timer_t timer_sel);

/**
 * @brief 暂停LEDC计时器计数器
 *
 * @param  speed_mode  选择具有指定速度模式的LEDC通道组。请注意，并非所有目标都支持高速模式。
 * @param  timer_sel LEDC计时器索引（0-3），从LEDC_timer_t中选择
 *
 * @return
 *     -ESP_ERR_INVALID_ARG参数错误
 *     -ESP_OK成功
 *
 */
esp_err_t ledc_timer_pause(ledc_mode_t speed_mode, ledc_timer_t timer_sel);

/**
 * @brief 恢复LEDC计时器
 *
 * @param speed_mode 选择具有指定速度模式的LEDC通道组。请注意，并非所有目标都支持高速模式。
 * @param timer_sel LEDC计时器索引（0-3），从LEDC_timer_t中选择
 *
 * @return
 *     -ESP_ERR_INVALID_ARG参数错误
 *     -ESP_OK成功
 */
esp_err_t ledc_timer_resume(ledc_mode_t speed_mode, ledc_timer_t timer_sel);

/**
 * @brief 将LEDC通道与所选计时器绑定
 *
 * @param speed_mode 选择具有指定速度模式的LEDC通道组。请注意，并非所有目标都支持高速模式。
 * @param channel LEDC信道索引（0-LEDC_channel_MAX-1），从LEDC_channel_t中选择
 * @param timer_sel LEDC计时器索引（0-3），从LEDC_timer_t中选择
 *
 * @return
 *     -ESP_ERR_INVALID_ARG参数错误
 *     -ESP_OK成功
 */
esp_err_t ledc_bind_channel_timer(ledc_mode_t speed_mode, ledc_channel_t channel, ledc_timer_t timer_sel);

/**
 * @brief 设置LEDC淡入功能。
 * @note  在调用此函数之前，请调用ledc_fade_func_install（）一次。在此之后调用ledc_fade_start（）开始褪色。
 * @note  ledc_set_fade_with_step、ledc_set_fade_with_time和ledc_fade_start不是线程安全的，请不要调用这些函数来同时控制不同任务中的一个ledc通道。API的线程安全版本是ledc_set_fade_step_and_start
 * @note  如果该频道上正在进行淡入操作，则驱动程序将不允许停止该操作。其他值班操作将不得不等待，直到渐变操作完成。
 * @param speed_mode 选择具有指定速度模式的LEDC通道组。注意，并非所有目标都支持高速模式，
 * @param channel LEDC信道索引（0-LEDC_channel_MAX-1），从LEDC_channel_t中选择
 * @param target_duty 衰落的目标占空比[0，（2**占空比_分辨率）-1]
 * @param scale 控制增加或减少步长比例。
 * @param cycle_num 每循环增加或减少占空比_num循环
 *
 * @return
 *     -ESP_ERR_INVALID_ARG参数错误
 *     -ESP_OK成功
 *     -未安装ESP_ERR_INVALID_STATE Fade函数。
 *     -ESP_FAIL Fade函数初始化错误
 */
esp_err_t ledc_set_fade_with_step(ledc_mode_t speed_mode, ledc_channel_t channel, uint32_t target_duty, uint32_t scale, uint32_t cycle_num);

/**
 * @brief 设置LEDC褪色功能，时间有限。
 * @note  在调用此函数之前，请调用ledc_fade_func_install（）一次。在此之后调用ledc_fade_start（）开始褪色。
 * @note  ledc_set_fade_with_step、ledc_set_fade_with_time和ledc_fade_start不是线程安全的，请不要调用这些函数来同时控制不同任务中的一个ledc通道。API的线程安全版本是ledc_set_fade_step_and_start
 * @note  如果该频道上正在进行淡入操作，则驱动程序将不允许停止该操作。其他值班操作将不得不等待，直到渐变操作完成。
 * @param speed_mode 选择具有指定速度模式的LEDC通道组。注意，并非所有目标都支持高速模式，
 * @param channel LEDC信道索引（0-LEDC_channel_MAX-1），从LEDC_channel_t中选择
 * @param target_duty 衰落的目标占空比[0，（2**占空比_分辨率）-1]
 * @param max_fade_time_ms 衰减的最长时间（毫秒）。
 *
 * @return
 *     -ESP_ERR_INVALID_ARG参数错误
 *     -ESP_OK成功
 *     -未安装ESP_ERR_INVALID_STATE Fade函数。
 *     -ESP_FAIL Fade函数初始化错误
 */
esp_err_t ledc_set_fade_with_time(ledc_mode_t speed_mode, ledc_channel_t channel, uint32_t target_duty, int max_fade_time_ms);

/**
 * @brief 安装LEDC褪色功能。此功能将占用LEDC模块的中断。
 * @param intr_alloc_flags 用于分配中断的标志。一个或多个（ORred）ESP_INTR_FLAG_值。请参见esp_intr_alloc。h了解更多信息。
 *
 * @return
 *     -ESP_OK成功
 *     -ESP_ERR_INVALID_STATE Fade函数已安装。
 */
esp_err_t ledc_fade_func_install(int intr_alloc_flags);

/**
 * @brief 卸载LEDC淡入功能。
 *
 */
void ledc_fade_func_uninstall(void);

/**
 * @brief 开始LEDC褪色。
 * @note  在调用此函数之前，请调用ledc_fade_func_install（）一次。在ledc_set_fade_with_time或ledc_set_fade_with_step之后立即调用此API以开始褪色。
 * @note  如果该频道上正在进行淡入操作，则驱动程序将不允许停止该操作。其他值班操作将不得不等待，直到渐变操作完成。
 * @param speed_mode 选择具有指定速度模式的LEDC通道组。请注意，并非所有目标都支持高速模式。
 * @param channel LEDC通道编号
 * @param fade_mode 是否阻止，直到褪色完成。请参见ledc_types。h ledc_fade_mode_t了解更多信息。请注意，如果选择了LEDC_FADE_WAIT_DONE模式，则该功能在衰减到目标占空比之前不会返回。
 *
 * @return
 *     -ESP_OK成功
 *     -未安装ESP_ERR_INVALID_STATE Fade函数。
 *     -ESP_ERR_INVALID_ARG参数错误。
 */
esp_err_t ledc_fade_start(ledc_mode_t speed_mode, ledc_channel_t channel, ledc_fade_mode_t fade_mode);

/**
 * @brief 线程安全API，用于设置LEDC通道的占空比，并在占空比更新时返回。
 * @note  如果该频道上正在进行淡入操作，则驱动程序将不允许停止该操作。其他值班操作将不得不等待，直到渐变操作完成。
 *
 * @param speed_mode 选择具有指定速度模式的LEDC通道组。请注意，并非所有目标都支持高速模式。
 * @param channel LEDC通道（0-LEDC_channel_MAX-1），从LEDC_channel_t中选择
 * @param duty 设置LEDC占空比，占空比设置范围为[0，（2**duty_desolution）-1]
 * @param hpoint 设置LEDC hpoint值（最大值：0xfffff）
 *
 */
esp_err_t ledc_set_duty_and_update(ledc_mode_t speed_mode, ledc_channel_t channel, uint32_t duty, uint32_t hpoint);

/**
 * @brief 一个线程安全API，用于在有限的时间内设置和启动LEDC淡出功能。
 * @note  在调用此函数之前，调用ledc_fade_func_install（）一次。
 * @note  如果该频道上正在进行淡入操作，则驱动程序将不允许停止该操作。其他值班操作将不得不等待，直到渐变操作完成。
 * @param speed_mode 选择具有指定速度模式的LEDC通道组。请注意，并非所有目标都支持高速模式。
 * @param channel LEDC信道索引（0-LEDC_channel_MAX-1），从LEDC_channel_t中选择
 * @param target_duty 衰落的目标占空比[0，（2**占空比_分辨率）-1]
 * @param max_fade_time_ms 衰减的最长时间（毫秒）。
 * @param fade_mode 选择阻塞或非阻塞模式
 * @return
 *     -ESP_ERR_INVALID_ARG参数错误
 *     -ESP_OK成功
 *     -未安装ESP_ERR_INVALID_STATE Fade函数。
 *     -ESP_FAIL Fade函数初始化错误
 */
esp_err_t ledc_set_fade_time_and_start(ledc_mode_t speed_mode, ledc_channel_t channel, uint32_t target_duty, uint32_t max_fade_time_ms, ledc_fade_mode_t fade_mode);

/**
 * @brief 用于设置和启动LEDC淡入功能的线程安全API。
 * @note  在调用此函数之前，请调用ledc_fade_func_install（）一次。
 * @note  如果该频道上正在进行淡入操作，则驱动程序将不允许停止该操作。其他值班操作将不得不等待，直到渐变操作完成。
 * @param speed_mode 选择具有指定速度模式的LEDC通道组。请注意，并非所有目标都支持高速模式。
 * @param channel LEDC信道索引（0-LEDC_channel_MAX-1），从LEDC_channel_t中选择
 * @param target_duty 衰落的目标占空比[0，（2**占空比_分辨率）-1]
 * @param scale 控制增加或减少步长比例。
 * @param cycle_num 每循环增加或减少占空比_num循环
 * @param fade_mode 选择阻塞或非阻塞模式
 * @return
 *     -ESP_ERR_INVALID_ARG参数错误
 *     -ESP_OK成功
 *     -未安装ESP_ERR_INVALID_STATE Fade函数。
 *     -ESP_FAIL Fade函数初始化错误
 */
esp_err_t ledc_set_fade_step_and_start(ledc_mode_t speed_mode, ledc_channel_t channel, uint32_t target_duty, uint32_t scale, uint32_t cycle_num, ledc_fade_mode_t fade_mode);

/**
 * @brief LEDC回调注册功能
 * @note  回调是从ISR调用的，它决不能试图阻止，并且调用的任何FreeRTOS API都必须支持ISR。
 * @param speed_mode 选择具有指定速度模式的LEDC通道组。请注意，并非所有目标都支持高速模式。
 * @param channel LEDC信道索引（0-LEDC_channel_MAX-1），从LEDC_channel_t中选择
 * @param cbs LEDC回调函数组
 * @param user_arg 回调函数的用户注册数据
 * @return
 *     -ESP_ERR_INVALID_ARG参数错误
 *     -ESP_OK成功
 *     -未安装ESP_ERR_INVALID_STATE Fade函数。
 *     -ESP_FAIL Fade函数初始化错误
 */
esp_err_t ledc_cb_register(ledc_mode_t speed_mode, ledc_channel_t channel, ledc_cbs_t *cbs, void *user_arg);
#ifdef __cplusplus
}
#endif

