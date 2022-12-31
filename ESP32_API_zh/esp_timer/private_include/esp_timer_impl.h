/*
 * SPDX文件版权文本：2017-2021浓缩咖啡系统（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */

#pragma once

/**
 * @file private_include/esp_timer_impl.h
 *
 * @brief esp_timer的公共部分和平台特定部分之间的接口。
 *
 * 此头文件中的函数是为每个受支持的SoC实现的。esp_timer中定义的高级函数。c调用此处的函数与硬件交互。
 */

#include <stdint.h>
#include "esp_err.h"
#include "esp_intr_alloc.h"

/**
 * @brief esp_timer平台特定层的最小初始化此函数可以在启动过程的早期调用，调用后只能使用esp_timer_get_time函数。必须在该函数之后调用esptimer_impl_init来初始化esptimer实现的其余部分。
 * @return ESP_OK
 */
esp_err_t esp_timer_impl_early_init(void);

/**
 * @brief 初始化esp_timer的平台特定层
 * @param alarm_handler 函数调用计时器中断在调用此函数之前，必须调用esp_timer_impl_early_init。
 * @return ESP_OK、ESP_ERR_NO_MEM或来自中断分配器的错误之一
 */
esp_err_t esp_timer_impl_init(intr_handler_t alarm_handler);

/**
 * @brief 取消初始化esp_timer的平台特定层
 */
void esp_timer_impl_deinit(void);

/**
 * @brief 设置定时器中断以在特定时间启动
 *
 * 如果未来警报时间太近，实施应将警报设置为尽可能早的时间。
 *
 * @param timestamp 中断触发的时间（以微秒为单位）（相对于启动时间，即esp_timer_impl_get_time返回的时间）
 */
void esp_timer_impl_set_alarm(uint64_t timestamp);

/**
 * @brief 为特定报警模块设置定时器中断，以在特定时间启动。
 *
 * 如果未来警报时间太近，实施应将警报设置为尽可能早的时间。
 *
 * @param timestamp 中断触发的时间（以微秒为单位）（相对于启动时间，即esp_timer_impl_get_time返回的时间）
 *
 * @param alarm_id Id报警：0-alarm_0表示ESP_TIMER_TASK调度方法，1-alarm_1表示ESP_TTIMER_ISR调度方法。
 */
void esp_timer_impl_set_alarm_id(uint64_t timestamp, unsigned alarm_id);

/**
 * @brief 通知esp_timer实现APB频率已更改
 *
 * 由频率切换代码调用。
 *
 * @param apb_ticks_per_us 每微秒新的APB时钟周期数
 */
void esp_timer_impl_update_apb_freq(uint32_t apb_ticks_per_us);

/**
 * @brief 将当前esp_timer时间调整一定值
 *
 * 从轻睡眠代码调用以将esp_timer时间与RTC时间同步。
 *
 * @param time_us  要应用于esp_timer时间的调整，以微秒为单位
 */
void esp_timer_impl_advance(int64_t time_us);

/**
 * @brief 获取调用esp_timer_impl_init以来的时间（以微秒为单位）
 * @return 时间戳（微秒）
 */
int64_t esp_timer_impl_get_time(void);

/**
 * @brief 获取最小计时器周期，以微秒为单位。由于中断延迟和上下文切换时间，可能无法实现比返回的计时器周期更短的周期。短周期的周期计时器可能会导致系统花费所有时间来服务中断和计时器回调，从而阻止其他任务运行。
 * @return 周期计时器的最小周期，以微秒为单位
 */
uint64_t esp_timer_impl_get_min_period_us(void);

/**
 * @brief 获取内部关键部分使用的esp_timer实现这可以在必须对esp_timeer进行一系列调用时使用，并且需要在调用之间保持计时器的状态一致。应该以与自旋锁相同的方式处理。调用esp_timer_impl_unlock以释放锁
 */
void esp_timer_impl_lock(void);


/**
 * @brief esp_timer_impl_lock的对应项
 */
void esp_timer_impl_unlock(void);

/**
 * @brief 获取计数寄存器
 *
 * 位深度取决于实现，可以是32位或64位。
 *
 * @return 计数寄存器的值
 */
uint64_t esp_timer_impl_get_counter_reg(void);

/**
 * @brief 获取报警寄存器
 *
 * 位深度取决于实现，可以是32位或64位。
 *
 * @return 报警寄存器的值
 */
uint64_t esp_timer_impl_get_alarm_reg(void);

#if CONFIG_ESP_TIME_FUNCS_USE_ESP_TIMER
/**
 * @brief 将esp_timer初始化为系统时间提供程序。
 */
void esp_timer_impl_init_system_time(void);
#endif

