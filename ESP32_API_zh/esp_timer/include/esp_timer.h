/*
 * SPDX文件版权文本：2017-2021浓缩咖啡系统（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */

#pragma once

/**
 * @file esp_时间.h
 * @brief 微秒精度64位计时器API，替代ets_timer
 *
 * esp_timer API允许组件在硬件计时器达到特定值时接收回调。计时器提供微秒级的精度和高达64位的范围。注意，虽然计时器本身提供微秒级的精度，但回调是从辅助任务调度的。需要一些时间从计时器ISR通知此任务，然后调用回调。如果在任何特定时间需要调度多个回调，则只有在前一个回调返回时才会调度每个后续回调。因此，回调不应该做很多工作；相反，他们应该使用RTOS通知机制（队列、信号量、事件组等）将信息传递给其他任务。
 *
 * 要实现：应该可以请求直接从ISR调用回调。这减少了延迟，但对需要调度的所有其他回调都有潜在影响。此选项只应用于简单的回调函数，运行时间不超过几微秒。
 *
 * 实现说明：在ESP32上，esp_timer API使用“传统”FRC2计时器。计时器回调是从PRO CPU上运行的任务调用的。
 */

#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include "esp_err.h"
#include "sdkconfig.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 表示单个esp_timer的不透明类型
 */
typedef struct esp_timer* esp_timer_handle_t;

/**
 * @brief 计时器回调函数类型
 * @param arg 指向不透明用户特定数据的指针
 */
typedef void (*esp_timer_cb_t)(void* arg);


/**
 * @brief 调度计时器回调的方法
 */
typedef enum {
    ESP_TIMER_TASK,     //!< 从计时器任务调用回调
#ifdef CONFIG_ESP_TIMER_SUPPORTS_ISR_DISPATCH_METHOD
    ESP_TIMER_ISR,      //!< 从计时器ISR调用回调
#endif
    ESP_TIMER_MAX,      //!< 调度计时器回调的方法计数
} esp_timer_dispatch_t;

/**
 * @brief 计时器配置传递给esp_Timer_create
 */
typedef struct {
    esp_timer_cb_t callback;        //!< 计时器过期时调用的函数
    void* arg;                      //!< 要传递给回调的参数
    esp_timer_dispatch_t dispatch_method;   //!< 从任务或ISR调用回调
    const char* name;               //!< 计时器名称，用于esp_Timer_dump函数
    bool skip_unhandled_events;     //!< 跳过定期计时器的未处理事件
} esp_timer_create_args_t;


/**
 * @brief esp_timer的最小初始化
 *
 * @note 此函数是从启动代码调用的。应用程序在使用其他esp_timer API之前不需要调用此函数。
 *
 * 该函数可以在启动过程的早期调用，调用后只能使用esp_timer_get_time函数。
 *
 * @return
 *      -成功时ESP_OK
 */
esp_err_t esp_timer_early_init(void);

/**
 * @brief 初始化esp_timer库
 *
 * @note 此函数是从启动代码调用的。应用程序在使用其他esp_timer API之前不需要调用此函数。在调用此函数之前，启动代码必须调用esp_timer_early_init。
 *
 * @return
 *      -成功时ESP_OK
 *      -如果分配失败，则为ESP_ERR_NO_MEM
 *      -ESP_ERR_INVALID_STATE（如果已初始化）
 *      -来自中断分配器的其他错误
 */
esp_err_t esp_timer_init(void);

/**
 * @brief 取消初始化esp_timer库
 *
 * @note 通常不应从应用程序调用此函数
 *
 * @return
 *      -成功时ESP_OK
 *      -ESP_ERR_INVALID_STATE（如果尚未初始化）
 */
esp_err_t esp_timer_deinit(void);

/**
 * @brief 创建esp_timer实例
 *
 * @note 使用计时器完成后，使用esp_timer_delete函数将其删除。
 *
 * @param create_args   指向具有计时器创建参数的结构的指针。库未保存，可在堆栈上分配。
 * @param[out] out_handle  输出，指向esp_timer_handle_t变量的指针，该变量将保存创建的计时器句柄。
 *
 * @return
 *      -成功时ESP_OK
 *      -如果某些create_args无效，则返回ESP_ERR_INVALID_ARG
 *      -如果ESP_timer库尚未初始化，则为ESP_ERR_INVALID_STATE
 *      -如果内存分配失败，则为ESP_ERR_NO_MEM
 */
esp_err_t esp_timer_create(const esp_timer_create_args_t* create_args,
                           esp_timer_handle_t* out_handle);

/**
 * @brief 启动一次性计时器
 *
 * 调用此函数时，计时器不应运行。
 *
 * @param timer 使用esp_timer_create创建的计时器句柄
 * @param timeout_us 计时器超时，相对于当前时刻以微秒为单位
 * @return
 *      -成功时ESP_OK
 *      -如果句柄无效，则返回ESP_ERR_INVALID_ARG
 *      -如果计时器已在运行，则为ESP_ERR_INVALID_STATE
 */
esp_err_t esp_timer_start_once(esp_timer_handle_t timer, uint64_t timeout_us);

/**
 * @brief 启动定期计时器
 *
 * 调用此函数时，计时器不应运行。此函数将启动计时器，每“周期”微秒触发一次。
 *
 * @param timer 使用esp_timer_create创建的计时器句柄
 * @param period 计时器周期，以微秒为单位
 * @return
 *      -成功时ESP_OK
 *      -如果句柄无效，则返回ESP_ERR_INVALID_ARG
 *      -如果计时器已在运行，则为ESP_ERR_INVALID_STATE
 */
esp_err_t esp_timer_start_periodic(esp_timer_handle_t timer, uint64_t period);

/**
 * @brief 停止计时器
 *
 * 此函数用于停止之前使用esp_timer_start_once或esp_timeer_start_periodic启动的计时器。
 *
 * @param timer 使用esp_timer_create创建的计时器句柄
 * @return
 *      -成功时ESP_OK
 *      -如果计时器未运行，则为ESP_ERR_INVALID_STATE
 */
esp_err_t esp_timer_stop(esp_timer_handle_t timer);

/**
 * @brief 删除esp_timer实例
 *
 * 删除前必须停止计时器。已过期的一次性计时器不需要停止。
 *
 * @param timer 使用esp_timer_create分配的计时器句柄
 * @return
 *      -成功时ESP_OK
 *      -如果计时器正在运行，则为ESP_ERR_INVALID_STATE
 */
esp_err_t esp_timer_delete(esp_timer_handle_t timer);

/**
 * @brief 获取启动后的时间（微秒）
 * @return 基础计时器启动后的微秒数
 */
int64_t esp_timer_get_time(void);

/**
 * @brief 获取预期下次超时发生的时间戳
 * @return 最近计时器事件的时间戳，以微秒为单位。时基与esp_timer_get_time返回的值相同。
 */
int64_t esp_timer_get_next_alarm(void);

/**
 * @brief 获取预期下一次超时发生时的时间戳，跳过具有skip_unhandled_events标志的超时
 * @return 最近计时器事件的时间戳，以微秒为单位。时基与esp_timer_get_time返回的值相同。
 */
int64_t esp_timer_get_next_alarm_for_wake_up(void);

/**
 * @brief 将计时器列表转储到流
 *
 * 如果启用CONFIG_ESP_TIMER_PROFILING选项，则打印所有现有计时器的列表。否则，仅打印列表活动计时器。
 *
 * 格式为：
 *
 *   name period alarm times_armed times_triggered total_callback_run_time
 *
 * 哪里：
 *
 * name-计时器名称（如果定义了CONFIG_ESP_timer_PROFILING），或计时器指针周期-计时器周期，以微秒为单位，或0表示一次计时器报警-下一次报警的时间，以毫秒为单位，如果计时器未启动，则为0
 *
 * 如果定义了CONFIG_ESP_TIMER_PROFILING，将打印以下字段：
 *
 * times_armed-通过esp_timer_start_X配置计时器的次数times_triggered-调用回调的次数total_callback_run_time-回调在所有调用中执行的总时间
 *
 * @param stream 将信息转储到的流（如stdout）
 * @return
 *      -成功时ESP_OK
 *      -如果无法为输出分配临时缓冲区，则为ESP_ERR_NO_MEM
 */
esp_err_t esp_timer_dump(FILE* stream);

#ifdef CONFIG_ESP_TIMER_SUPPORTS_ISR_DISPATCH_METHOD
/**
 * @brief 从计时器回调函数请求上下文切换。
 *
 * 这只适用于具有ISR分派方法的计时器。处理完所有ISR调度计时器后，将调用上下文开关。
 */
void esp_timer_isr_dispatch_need_yield(void);
#endif // CONFIG_ESP_TIMER_SUPPORTS_ISR_DISPATCH_METHOD

/**
 * @brief 返回计时器的状态，是否处于活动状态
 *
 * 此功能用于确定计时器是否仍处于活动状态。
 *
 * @param timer 使用esp_timer_create创建的计时器句柄
 * @return
 *      -如果计时器仍处于活动状态，则为1
 *      -如果计时器未激活，则为0。
 */
bool esp_timer_is_active(esp_timer_handle_t timer);

#ifdef __cplusplus
}
#endif

