/*
 * SPDX文件版权文本：2010-2021浓缩咖啡系统（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */

#pragma once

#include "esp_err.h"
#include "esp_attr.h"
#include "soc/soc.h"
#include "soc/timer_periph.h"
#include "esp_intr_alloc.h"
#include "hal/timer_types.h"

#ifdef __cplusplus
extern "C" {
#endif

#define TIMER_BASE_CLK   (APB_CLK_FREQ)  /*!< 计时器组输入上的时钟频率*/

/**
 * @brief 中断句柄回调函数。用户需要在回调中重新运行布尔值。
 *
 * @return
 *     -ISR结束时的True Do任务产量
 *     -错误ISR结束时任务未完成
 *
 * @note 如果在回调中调用FreeRTOS函数，则需要根据参数“pxHigherPriorityTaskWoken”的retrun值返回true或false。例如，在回调中调用“xQueueSendFromISR”，如果任何FreeRTOS调用的返回值“pxHigherPriorityTaskWoken”为pdTRUE，则返回true；否则返回false。
 */
typedef bool (*timer_isr_t)(void *);

/**
 * @brief 中断句柄，用于在使用后释放isr。现在为int句柄添加别名。
 */
typedef intr_handle_t timer_isr_handle_t;

/**
 * @brief 读取硬件计时器的计数器值。
 *
 * @param group_num 计时器组，0表示TIMERG0，1表示TIMERG1
 * @param timer_num 计时器索引，hw_Timer[0]为0，hw_ttimer[1]为1
 * @param timer_val 接受计时器计数器值的指针。
 *
 * @return
 *     -ESP_OK成功
 *     -ESP_ERR_INVALID_ARG参数错误
 */
esp_err_t timer_get_counter_value(timer_group_t group_num, timer_idx_t timer_num, uint64_t *timer_val);

/**
 * @brief 读取硬件计时器的计数器值，以给定刻度为单位。
 *
 * @param group_num 计时器组，0表示TIMERG0，1表示TIMERG1
 * @param timer_num 计时器索引，hw_Timer[0]为0，hw_ttimer[1]为1
 * @param time 指针，双*类型，用于接受计时器计数器值（以秒为单位）。
 *
 * @return
 *     -ESP_OK成功
 *     -ESP_ERR_INVALID_ARG参数错误
 */
esp_err_t timer_get_counter_time_sec(timer_group_t group_num, timer_idx_t timer_num, double *time);

/**
 * @brief 将计数器值设置为硬件计时器。
 *
 * @param group_num 计时器组，0表示TIMERG0，1表示TIMERG1
 * @param timer_num 计时器索引，hw_Timer[0]为0，hw_ttimer[1]为1
 * @param load_val 写入硬件计时器的计数器值。
 *
 * @return
 *     -ESP_OK成功
 *     -ESP_ERR_INVALID_ARG参数错误
 */
esp_err_t timer_set_counter_value(timer_group_t group_num, timer_idx_t timer_num, uint64_t load_val);

/**
 * @brief 启动硬件计时器的计数器。
 *
 * @param group_num 计时器组编号，0表示TIMERG0，1表示TIMERG1
 * @param timer_num 计时器索引，hw_Timer[0]为0，hw_ttimer[1]为1
 *
 * @return
 *     -ESP_OK成功
 *     -ESP_ERR_INVALID_ARG参数错误
 */
esp_err_t timer_start(timer_group_t group_num, timer_idx_t timer_num);

/**
 * @brief 暂停硬件计时器的计数器。
 *
 * @param group_num 计时器组编号，0表示TIMERG0，1表示TIMERG1
 * @param timer_num 计时器索引，hw_Timer[0]为0，hw_ttimer[1]为1
 *
 * @return
 *     -ESP_OK成功
 *     -ESP_ERR_INVALID_ARG参数错误
 */
esp_err_t timer_pause(timer_group_t group_num, timer_idx_t timer_num);

/**
 * @brief 设置硬件计时器的计数模式。
 *
 * @param group_num 计时器组编号，0表示TIMERG0，1表示TIMERG1
 * @param timer_num 计时器索引，hw_Timer[0]为0，hw_ttimer[1]为1
 * @param counter_dir 计时器的计数方向，向上或向下计数
 *
 * @return
 *     -ESP_OK成功
 *     -ESP_ERR_INVALID_ARG参数错误
 */
esp_err_t timer_set_counter_mode(timer_group_t group_num, timer_idx_t timer_num, timer_count_dir_t counter_dir);

/**
 * @brief 发生报警事件时启用或禁用计数器重新加载功能。
 *
 * @param group_num 计时器组编号，0表示TIMERG0，1表示TIMERG1
 * @param timer_num 计时器索引，hw_Timer[0]为0，hw_ttimer[1]为1
 * @param reload 计数器重新加载模式。
 *
 * @return
 *     -ESP_OK成功
 *     -ESP_ERR_INVALID_ARG参数错误
 */
esp_err_t timer_set_auto_reload(timer_group_t group_num, timer_idx_t timer_num, timer_autoreload_t reload);

/**
 * @brief 将源时钟的硬件分频器设置为计时器组。默认情况下，源时钟是以80MHz运行的APB时钟。有关更多信息，请参阅《芯片技术参考手册》中的重置和时钟章节。
 * @param group_num 计时器组编号，0表示TIMERG0，1表示TIMERG1
 * @param timer_num 计时器索引，hw_Timer[0]为0，hw_ttimer[1]为1
 * @param divider 计时器时钟分频器值。除法器的范围从2到65536。
 *
 * @return
 *     -ESP_OK成功
 *     -ESP_ERR_INVALID_ARG参数错误
 */
esp_err_t timer_set_divider(timer_group_t group_num, timer_idx_t timer_num, uint32_t divider);

/**
 * @brief 设置计时器报警值。
 *
 * @param group_num 计时器组，0表示TIMERG0，1表示TIMERG1
 * @param timer_num 计时器索引，hw_Timer[0]为0，hw_ttimer[1]为1
 * @param alarm_value 设置报警值的64位值。
 *
 * @return
 *     -ESP_OK成功
 *     -ESP_ERR_INVALID_ARG参数错误
 */
esp_err_t timer_set_alarm_value(timer_group_t group_num, timer_idx_t timer_num, uint64_t alarm_value);

/**
 * @brief 获取计时器报警值。
 *
 * @param group_num 计时器组，0表示TIMERG0，1表示TIMERG1
 * @param timer_num 计时器索引，hw_Timer[0]为0，hw_ttimer[1]为1
 * @param alarm_value 用于接受报警值的64位值指针。
 *
 * @return
 *     -ESP_OK成功
 *     -ESP_ERR_INVALID_ARG参数错误
 */
esp_err_t timer_get_alarm_value(timer_group_t group_num, timer_idx_t timer_num, uint64_t *alarm_value);

/**
 * @brief 启用或禁用计时器报警事件的生成。
 *
 * @param group_num 计时器组，0表示TIMERG0，1表示TIMERG1
 * @param timer_num 计时器索引，hw_Timer[0]为0，hw_ttimer[1]为1
 * @param alarm_en 启用或禁用计时器报警功能。
 *
 * @return
 *     -ESP_OK成功
 *     -ESP_ERR_INVALID_ARG参数错误
 */
esp_err_t timer_set_alarm(timer_group_t group_num, timer_idx_t timer_num, timer_alarm_t alarm_en);

/**
 * @brief 为相应的计时器添加ISR句柄回调。
 *
 * @param group_num 计时器组编号
 * @param timer_num 计时器组的计时器索引
 * @param isr_handler 中断处理程序函数，它是一个回调函数。
 * @param arg 处理程序函数的参数
 * @param intr_alloc_flags 用于分配中断的标志。一个或多个（ORred）ESP_INTR_FLAG_值。请参见esp_intr_alloc。h了解更多信息。
 *
 * @note 将从ISR调用此ISR处理程序。这个ISR处理程序不需要处理中断状态，应该保持简短。如果您想实现某些特定的应用程序或编写整个ISR，可以调用timer_ISR_register（…）来注册ISR。
 *
 *       回调应返回布尔值，以确定是否需要在ISR结束时执行YELD。
 *
 *       如果设置了intr_alloc_flags值ESP_intr_FLAG_IRAM，则处理程序函数必须用IRAM_ATTR属性声明，并且只能调用IRAM或ROM中的函数。它不能调用其他计时器API。
 *
 * @return
 *     -ESP_OK成功
 *     -ESP_ERR_INVALID_ARG参数错误
 */
esp_err_t timer_isr_callback_add(timer_group_t group_num, timer_idx_t timer_num, timer_isr_t isr_handler, void *arg, int intr_alloc_flags);

/**
 * @brief 删除相应计时器的ISR句柄回调。
 *
 * @param group_num 计时器组编号
 * @param timer_num 计时器组的计时器索引
 *
 * @return
 *     -ESP_OK成功
 *     -ESP_ERR_INVALID_ARG参数错误
 */
esp_err_t timer_isr_callback_remove(timer_group_t group_num, timer_idx_t timer_num);

/**
 * @brief 寄存器定时器中断处理程序，该处理程序是ISR。处理程序将连接到运行此函数的同一CPU内核。
 *
 * @param group_num 计时器组编号
 * @param timer_num 计时器组的计时器索引
 * @param fn 中断处理程序函数。
 * @param arg 处理程序函数的参数
 * @param intr_alloc_flags 用于分配中断的标志。一个或多个（ORred）ESP_INTR_FLAG_值。请参见esp_intr_alloc。h了解更多信息。
 * @param handle 指向返回句柄的指针。如果非NULL，将在此处返回中断的句柄。
 *
 * @note 如果使用此函数来注册ISR，则需要编写整个ISR。在中断处理程序中，需要在处理之前调用timer_spinlock_take（..），在处理之后调用timer_pinlock_give（…）。
 *
 *       如果设置了intr_alloc_flags值ESP_intr_FLAG_IRAM，则处理程序函数必须用IRAM_ATTR属性声明，并且只能调用IRAM或ROM中的函数。它不能调用其他计时器API。在这种情况下，使用直接寄存器访问从ISR内部配置计时器。
 *
 * @return
 *     -ESP_OK成功
 *     -ESP_ERR_INVALID_ARG参数错误
 */
esp_err_t timer_isr_register(timer_group_t group_num, timer_idx_t timer_num, void (*fn)(void *), void *arg, int intr_alloc_flags, timer_isr_handle_t *handle);

/** @brief 初始化并配置计时器。
 *
 * @param group_num 计时器组编号，0表示TIMERG0，1表示TIMERG1
 * @param timer_num 计时器索引，hw_Timer[0]为0，hw_ttimer[1]为1
 * @param config 指向计时器初始化参数的指针。
 *
 * @return
 *     -ESP_OK成功
 *     -ESP_ERR_INVALID_ARG参数错误
 */
esp_err_t timer_init(timer_group_t group_num, timer_idx_t timer_num, const timer_config_t *config);

/** @brief 取消计时器初始化。
 *
 * @param group_num 计时器组编号，0表示TIMERG0，1表示TIMERG1
 * @param timer_num 计时器索引，hw_Timer[0]为0，hw_ttimer[1]为1
 *
 * @return
 *     -ESP_OK成功
 *     -ESP_ERR_INVALID_ARG参数错误
 */
esp_err_t timer_deinit(timer_group_t group_num, timer_idx_t timer_num);

/** @brief 获取计时器配置值。
 *
 * @param group_num 计时器组编号，0表示TIMERG0，1表示TIMERG1
 * @param timer_num 计时器索引，hw_Timer[0]为0，hw_ttimer[1]为1
 * @param config 用于接受计时器参数的结构的指针。
 *
 * @return
 *     -ESP_OK成功
 *     -ESP_ERR_INVALID_ARG参数错误
 */
esp_err_t timer_get_config(timer_group_t group_num, timer_idx_t timer_num, timer_config_t *config);

/** @brief 通过启用掩码启用定时器组中断
 *
 * @param group_num 计时器组编号，0表示TIMERG0，1表示TIMERG1
 * @param intr_mask 定时器中断启用掩码。
 *          -TIMER_INTR_T0:T0中断
 *          -TIMER_INTR_T1:T1中断
 *          -TIMER_INTR_WDT：看门狗中断
 *
 * @return
 *     -ESP_OK成功
 *     -ESP_ERR_INVALID_ARG参数错误
 */
esp_err_t timer_group_intr_enable(timer_group_t group_num, timer_intr_t intr_mask);

/** @brief 通过禁用掩码禁用计时器组中断
 *
 * @param group_num 计时器组编号，0表示TIMERG0，1表示TIMERG1
 * @param intr_mask 定时器中断禁用掩码。
 *          -TIMER_INTR_T0:T0中断
 *          -TIMER_INTR_T1:T1中断
 *          -TIMER_INTR_WDT：看门狗中断
 *
 * @return
 *     -ESP_OK成功
 *     -ESP_ERR_INVALID_ARG参数错误
 */
esp_err_t timer_group_intr_disable(timer_group_t group_num, timer_intr_t intr_mask);

/** @brief 启用计时器中断
 *
 * @param group_num 计时器组编号，0表示TIMERG0，1表示TIMERG1
 * @param timer_num 计时器索引。
 *
 * @return
 *     -ESP_OK成功
 *     -ESP_ERR_INVALID_ARG参数错误
 */
esp_err_t timer_enable_intr(timer_group_t group_num, timer_idx_t timer_num);

/** @brief 禁用计时器中断
 *
 * @param group_num 计时器组编号，0表示TIMERG0，1表示TIMERG1
 * @param timer_num 计时器索引。
 *
 * @return
 *     -ESP_OK成功
 *     -ESP_ERR_INVALID_ARG参数错误
 */
esp_err_t timer_disable_intr(timer_group_t group_num, timer_idx_t timer_num);

/** @brief 清除计时器中断状态，仅用于ISR
 *
 * @param group_num 计时器组编号，0表示TIMERG0，1表示TIMERG1
 * @param timer_num 计时器索引。
 *
 */
void timer_group_intr_clr_in_isr(timer_group_t group_num, timer_idx_t timer_num) __attribute__((deprecated));

/** @brief 清除计时器中断状态，仅用于ISR
 *
 * @param group_num 计时器组编号，0表示TIMERG0，1表示TIMERG1
 * @param timer_num 计时器索引。
 *
 */
void timer_group_clr_intr_status_in_isr(timer_group_t group_num, timer_idx_t timer_num);

/** @brief 启用报警中断，仅用于ISR
 *
 * @param group_num 计时器组编号，0表示TIMERG0，1表示TIMERG1
 * @param timer_num 计时器索引。
 *
 */
void timer_group_enable_alarm_in_isr(timer_group_t group_num, timer_idx_t timer_num);

/** @brief 获取当前计数器值，仅用于ISR
 *
 * @param group_num 计时器组编号，0表示TIMERG0，1表示TIMERG1
 * @param timer_num 计时器索引。
 *
 * @return
 *     -计数器值
 */
uint64_t timer_group_get_counter_value_in_isr(timer_group_t group_num, timer_idx_t timer_num);

/** @brief 设置计时器的报警阈值，仅用于ISR
 *
 * @param group_num 计时器组编号，0表示TIMERG0，1表示TIMERG1
 * @param timer_num 计时器索引。
 * @param alarm_val 报警阈值。
 *
 */
void timer_group_set_alarm_value_in_isr(timer_group_t group_num, timer_idx_t timer_num, uint64_t alarm_val);

/** @brief 启用/禁用计数器，仅用于ISR
 *
 * @param group_num 计时器组编号，0表示TIMERG0，1表示TIMERG1
 * @param timer_num 计时器索引。
 * @param counter_en 启用/禁用。
 *
 */
void timer_group_set_counter_enable_in_isr(timer_group_t group_num, timer_idx_t timer_num, timer_start_t counter_en);

/** @brief 获取屏蔽中断状态，仅用于ISR
 *
 * @param group_num 计时器组编号，0表示TIMERG0，1表示TIMERG1
 *
 * @return
 *     -中断状态
 */
timer_intr_t timer_group_intr_get_in_isr(timer_group_t group_num) __attribute__((deprecated));

/** @brief 获取中断状态，仅用于ISR
 *
 * @param group_num 计时器组编号，0表示TIMERG0，1表示TIMERG1
 *
 * @return
 *     -中断状态
 */
uint32_t timer_group_get_intr_status_in_isr(timer_group_t group_num);

/** @brief 清除屏蔽中断状态，仅用于ISR
 *
 * @param group_num 计时器组编号，0表示TIMERG0，1表示TIMERG1
 * @param intr_mask 屏蔽中断。
 *
 */
void timer_group_clr_intr_sta_in_isr(timer_group_t group_num, timer_intr_t intr_mask) __attribute__((deprecated));

/** @brief 获取自动重新加载启用状态，仅用于ISR
 *
 * @param group_num 计时器组编号，0表示TIMERG0，1表示TIMERG1
 * @param timer_num 计时器索引
 *
 * @return
 *     -真自动重新加载已启用
 *     -False自动重新加载已禁用
 */
bool timer_group_get_auto_reload_in_isr(timer_group_t group_num, timer_idx_t timer_num);

/** @brief 采用定时器自旋锁进入关键保护
 *
 *  @note 不推荐，建议使用ISR回调，请参见timer_group_example_main
 *
 * @param group_num 计时器组编号，0表示TIMERG0，1表示TIMERG1
 *
 * @return
 *     -ESP_OK成功
 *     -ESP_ERR_INVALID_ARG参数错误
 */
esp_err_t timer_spinlock_take(timer_group_t group_num) __attribute__ ((deprecated));

/** @brief 给予计时器自旋锁以退出关键保护
 *
 *  @note 不推荐，建议使用ISR回调，请参见timer_group_example_main
 *
 * @param group_num 计时器组编号，0表示TIMERG0，1表示TIMERG1
 *
 * @return
 *     -ESP_OK成功
 *     -ESP_ERR_INVALID_ARG参数错误
 */
esp_err_t timer_spinlock_give(timer_group_t group_num) __attribute__ ((deprecated));

#ifdef __cplusplus
}
#endif

