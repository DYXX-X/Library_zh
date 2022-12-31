/*
 * SPDX文件版权文本：2019-2021浓缩咖啡系统（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "driver/touch_sensor_common.h"

/**
 * @brief 配置触摸板中断阈值。
 *
 * @note  如果FSM模式设置为TOUCH_FSM_mode_TIMER，则此功能将被阻止一个测量周期，并等待数据有效。
 *
 * @param touch_num 触摸板索引
 * @param threshold 中断阈值，
 *
 * @return
 *     -ESP_OK成功
 *     -如果参数错误，则为ESP_ERR_INVALID_ARG
 *     -如果触摸板未初始化，则为ESP_FAIL
 */
esp_err_t touch_pad_config(touch_pad_t touch_num, uint16_t threshold);

/**
 * @brief 获取触摸传感器计数器值。每个触摸传感器都有一个计数器来计数充电/放电循环的次数。当键盘没有被“触摸”时，我们可以得到计数器的数字。当极板被“触摸”时，由于等效电容较大，计数器中的值将变小。
 *
 * @note 此API请求硬件测量一次。如果启用了IIR过滤器模式，请改用“touch_pad_read_raw_data”接口。
 *
 * @param touch_num 触摸板索引
 * @param touch_value 接受触摸传感器值的指针
 *
 * @return
 *     -ESP_OK成功
 *     -ESP_ERR_INVALID_ARG触摸板参数错误
 *     -ESP_ERR_INVALID_STATE此触摸板硬件连接错误，“touch_value”的值为0。
 *     -ESP_FAIL触摸板未初始化
 */
esp_err_t touch_pad_read(touch_pad_t touch_num, uint16_t *touch_value);

/**
 * @brief 通过IIR滤波器获得滤波后的触摸传感器计数器值。
 *
 * @note 在调用touch_pad_read_filted之前，必须调用touch-pad_filter_start。可以从ISR调用此函数
 *
 * @param touch_num 触摸板索引
 * @param touch_value 接受触摸传感器值的指针
 *
 * @return
 *     -ESP_OK成功
 *     -ESP_ERR_INVALID_ARG触摸板参数错误
 *     -ESP_ERR_INVALID_STATE此触摸板硬件连接错误，“touch_value”的值为0。
 *     -ESP_FAIL触摸板未初始化
 */
esp_err_t touch_pad_read_filtered(touch_pad_t touch_num, uint16_t *touch_value);

/**
 * @brief 从IIR滤波过程中获取原始数据（触摸传感器计数器值）。无需请求硬件测量。
 *
 * @note 在调用touch_pad_read_raw_data之前，必须调用touch-pad_filter_start。可以从ISR调用此函数
 *
 * @param touch_num 触摸板索引
 * @param touch_value 接受触摸传感器值的指针
 *
 * @return
 *     -ESP_OK成功
 *     -ESP_ERR_INVALID_ARG触摸板参数错误
 *     -ESP_ERR_INVALID_STATE此触摸板硬件连接错误，“touch_value”的值为0。
 *     -ESP_FAIL触摸板未初始化
 */
esp_err_t touch_pad_read_raw_data(touch_pad_t touch_num, uint16_t *touch_value);

/**
  * @brief 在每次IIR滤波器计算后调用的回调函数。
  * @note 在每个筛选周期的计时器任务中调用此回调。
  * @note 不应阻止此回调。
  * @param raw_value  指向所有通道的最新原始数据（触摸传感器计数器值）（raw_value[0.touch_PAD_MAX-1]）。
  * @param filtered_value  指向所有通道的最新IIR滤波数据（根据原始数据计算）（filtered_value[0.TOUCH_PAD_MAX-1]）。
  *
  */
typedef void (* filter_cb_t)(uint16_t *raw_value, uint16_t *filtered_value);

/**
 * @brief 注册每次IIR筛选器计算后调用的回调函数。
 * @note 在每个筛选周期的计时器任务中调用“read_cb”回调。
 * @param read_cb  指向已筛选回调函数的指针。如果传入的参数为NULL，则回调将停止。
 * @return
 *      -ESP_OK成功
 *      -ESP_ERR_INVALID_ARG设置错误
 */
esp_err_t touch_pad_set_filter_read_cb(filter_cb_t read_cb);

/**
 * @brief   注册触摸板ISR。处理程序将连接到运行此函数的同一CPU内核。
 * @param fn  指向ISR处理程序的指针
 * @param arg  ISR参数
 * @return
 *     -ESP_OK成功；
 *     -ESP_ERR_INVALID_ARG GPIO错误
 *     -ESP_ERR_NO_MEM无内存
 */
esp_err_t touch_pad_isr_register(intr_handler_t fn, void *arg);

/**
 * @brief 设置触摸传感器测量值和睡眠时间。总时间过长会减慢触摸响应。太小的测量时间将无法进行足够的采样，从而导致测量不准确。
 *
 * @note 测量时间的占空比越大，消耗的系统功率越大。
 * @param sleep_cycle  每次测量后，触摸传感器将休眠。sleep_cycle决定每次测量之间的间隔。t_sleep=sleep_cycle/（RTC_SLOW_CLK频率）。RTC_SLOW_CLK的近似频率值可以使用RTC_CLK_SLOW_freq_get_hz函数获得。
 * @param meas_cycle 触摸传感器测量的持续时间。t_meas=meas_cycle/8M，最大测量时间为0xffff/8M=8.19 ms
 * @return
 *      -成功时ESP_OK
 */
esp_err_t touch_pad_set_meas_time(uint16_t sleep_cycle, uint16_t meas_cycle);

/**
 * @brief 获取触摸传感器测量值和睡眠时间
 * @param sleep_cycle  用于接受睡眠周期号的指针
 * @param meas_cycle 接受测量周期计数的指针。
 * @return
 *      -成功时ESP_OK
 */
esp_err_t touch_pad_get_meas_time(uint16_t *sleep_cycle, uint16_t *meas_cycle);

/**
 * @brief 触发触摸传感器测量，仅支持FSM的SW模式
 * @return
 *      -成功时ESP_OK
 */
esp_err_t touch_pad_sw_start(void);

/**
 * @brief 设置触摸传感器中断阈值
 * @param touch_num 触摸板索引
 * @param threshold 触摸板计数阈值，请参阅touch_pad_set_trigger_mode以了解如何设置触发模式。
 * @return
 *      -成功时ESP_OK
 *      -如果参数错误，则返回ESP_ERR_INVALID_ARG
 */
esp_err_t touch_pad_set_thresh(touch_pad_t touch_num, uint16_t threshold);

/**
 * @brief 获取触摸传感器中断阈值
 * @param touch_num 触摸板索引
 * @param threshold 接受阈值的指针
 * @return
 *      -成功时ESP_OK
 *      -如果参数错误，则返回ESP_ERR_INVALID_ARG
 */
esp_err_t touch_pad_get_thresh(touch_pad_t touch_num, uint16_t *threshold);

/**
 * @brief 设置触摸传感器中断触发模式。当计数器结果小于阈值或计数器结果大于阈值时，可以触发中断。
 * @param mode 触摸传感器中断触发模式
 * @return
 *      -成功时ESP_OK
 *      -如果参数错误，则返回ESP_ERR_INVALID_ARG
 */
esp_err_t touch_pad_set_trigger_mode(touch_trigger_mode_t mode);

/**
 * @brief 获取触摸传感器中断触发模式
 * @param mode 接受触摸传感器中断触发模式的指针
 * @return
 *      -成功时ESP_OK
 */
esp_err_t touch_pad_get_trigger_mode(touch_trigger_mode_t *mode);

/**
 * @brief 设置触摸传感器中断触发源。有两组触摸信号。Set1和set2可以被映射到多个触摸信号。如果至少有一个触摸信号被“触摸”，将触发任一组。可以将中断配置为在触发set1时生成，或者仅在触发两个集合时生成。
 * @param src 触摸传感器中断触发源
 * @return
 *      -成功时ESP_OK
 *      -如果参数错误，则返回ESP_ERR_INVALID_ARG
 */
esp_err_t touch_pad_set_trigger_source(touch_trigger_src_t src);

/**
 * @brief 获取触摸传感器中断触发源
 * @param src 接受触摸传感器中断触发源的指针
 * @return
 *      -成功时ESP_OK
 */
esp_err_t touch_pad_get_trigger_source(touch_trigger_src_t *src);

/**
 * @brief 设置触摸传感器组掩码。触摸板模块有两组信号，只有当该组中至少一个触摸板被“触摸”时，才会触发“触摸”信号。此函数将根据给定的位掩码设置寄存器位。
 * @param set1_mask 触摸传感器信号组1的位掩码，为10位值
 * @param set2_mask 触摸传感器信号组2的位掩码，为10位值
 * @param en_mask 触摸传感器工作启用的位掩码，为10位值
 * @return
 *      -成功时ESP_OK
 *      -如果参数错误，则返回ESP_ERR_INVALID_ARG
 */
esp_err_t touch_pad_set_group_mask(uint16_t set1_mask, uint16_t set2_mask, uint16_t en_mask);

/**
 * @brief 获取触摸传感器组掩码。
 * @param set1_mask 用于接受触摸传感器信号组1的位掩码的指针，它是一个10位值
 * @param set2_mask 用于接受触摸传感器信号组2的位掩码的指针，它是一个10位值
 * @param en_mask 用于接受触摸传感器工作启用位掩码的指针，它是一个10位值
 * @return
 *      -成功时ESP_OK
 */
esp_err_t touch_pad_get_group_mask(uint16_t *set1_mask, uint16_t *set2_mask, uint16_t *en_mask);

/**
 * @brief 清除触摸传感器组掩码。触摸板模块有两组信号，只有当该组中至少一个触摸板被“触摸”时，才会触发中断。此函数将根据给定的位掩码清除寄存器位。
 * @param set1_mask 位掩码触摸传感器信号组1，它是一个10位值
 * @param set2_mask 位掩码触摸传感器信号组2，它是一个10位值
 * @param en_mask 触摸传感器工作启用的位掩码，为10位值
 * @return
 *      -成功时ESP_OK
 *      -如果参数错误，则返回ESP_ERR_INVALID_ARG
 */
esp_err_t touch_pad_clear_group_mask(uint16_t set1_mask, uint16_t set2_mask, uint16_t en_mask);

/**
 * @brief 启用触摸板中断
 * @return
 *      -成功时ESP_OK
 */
esp_err_t touch_pad_intr_enable(void);

/**
 * @brief 禁用触摸板中断
 * @return
 *      -成功时ESP_OK
 */
esp_err_t touch_pad_intr_disable(void);

/**
 * @brief 清除触摸板中断
 * @return
 *      -成功时ESP_OK
 */
esp_err_t touch_pad_intr_clear(void);

/**
 * @brief 设置触摸板过滤器校准周期，以毫秒为单位。需要在所有触摸过滤器API之前调用touch_pad_filter_start
 * @param new_period_ms 过滤周期，单位为毫秒
 * @return
 *      -ESP_OK成功
 *      -ESP_ERR_INVALID_STATE驱动程序状态错误
 *      -ESP_ERR_INVALID_ARG参数错误
 */
esp_err_t touch_pad_set_filter_period(uint32_t new_period_ms);

/**
 * @brief 获取触摸板过滤器校准周期，以毫秒为单位需要在所有触摸过滤器API之前调用touch_pad_filter_start
 * @param p_period_ms 接受周期指针
 * @return
 *      -ESP_OK成功
 *      -ESP_ERR_INVALID_STATE驱动程序状态错误
 *      -ESP_ERR_INVALID_ARG参数错误
 */
esp_err_t touch_pad_get_filter_period(uint32_t *p_period_ms);

/**
 * @brief 启动触摸板滤波器功能此API将启动一个滤波器来处理噪声，以便在检测到电容的轻微变化时防止错误触发。需要在所有触摸过滤器API之前调用touch_pad_filter_start
 *
 * @note 此筛选器使用FreeRTOS计时器，默认情况下，该计时器是从CPU 0上优先级为1的任务调度的。因此，如果某个优先级较高的应用程序任务占用大量CPU0时间，则从该筛选器获得的数据质量将受到影响。您可以在menuconfig中调整FreeRTOS计时器任务优先级。
 * @param filter_period_ms 滤波器校准周期，单位：ms
 * @return
 *      -ESP_OK成功
 *      -ESP_ERR_INVALID_ARG参数错误
 *      -ESP_ERR_NO_MEM无驱动程序内存
 *      -ESP_ERR_INVALID_STATE驱动程序状态错误
 */
esp_err_t touch_pad_filter_start(uint32_t filter_period_ms);

/**
 * @brief 停止触摸板过滤器功能需要在所有触摸过滤器API之前调用touch_pad_filter_start
 * @return
 *      -ESP_OK成功
 *      -ESP_ERR_INVALID_STATE驱动程序状态错误
 */
esp_err_t touch_pad_filter_stop(void);

/**
 * @brief 删除触摸板过滤器驱动程序并释放内存需要在所有触摸过滤器API之前调用touch_pad_filter_start
 * @return
 *      -ESP_OK成功
 *      -ESP_ERR_INVALID_STATE驱动程序状态错误
 */
esp_err_t touch_pad_filter_delete(void);

#ifdef __cplusplus
}
#endif

