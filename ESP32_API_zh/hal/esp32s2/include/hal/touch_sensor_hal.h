// 版权所有2019 Espressif Systems（上海）私人有限公司
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

/*******************************************************************************
 * 注意：hal不是公共api，不要在应用程序代码中使用。请参阅自述文件。在hal/include/hal/readme.md中的md
 ******************************************************************************/

// 触摸传感器的HAL层（ESP32-S2特定部分）

#pragma once

#include "hal/touch_sensor_ll.h"
#include "hal/touch_sensor_types.h"

#include_next "hal/touch_sensor_hal.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * 重置整个触摸模块。
 *
 * @note 在“touch_pad_fsm_stop”之后调用此函数，
 */
#define touch_hal_reset() touch_ll_reset()

/**
 * 设置触摸传感器测量时间。
 *
 * @param meas_time 触摸传感器测量的持续时间。t_meas=meas_time/（8MHz），最大测量时间为0xffff/8M=8.19ms。
 */
#define touch_hal_set_meas_times(meas_time) touch_ll_set_meas_times(meas_time)

/**
 * 获取触摸传感器的充电和放电时间。
 *
 * @param meas_times 用于接受充电和放电次数计数的指针。
 */
#define touch_hal_get_measure_times(meas_time) touch_ll_get_measure_times(meas_time)

/**
 * 将触摸通道的连接类型设置为空闲状态。当信道处于测量模式时，其他初始化信道处于空闲模式。触摸通道通常与迹线相邻，因此空闲通道的连接状态影响测试通道的稳定性和灵敏度。“CONN_HIGHZ”（高电阻）设置增加了触摸通道的灵敏度。“CONN_GND”（接地）设置提高了触摸通道的稳定性。
 *
 * @param type  选择空闲通道连接到高电阻状态或接地。
 */
#define touch_hal_set_idle_channel_connect(type) touch_ll_set_idle_channel_connect(type)

/**
 * 将触摸通道的连接类型设置为空闲状态。当信道处于测量模式时，其他初始化信道处于空闲模式。触摸通道通常与迹线相邻，因此空闲通道的连接状态影响测试通道的稳定性和灵敏度。“CONN_HIGHZ”（高电阻）设置增加了触摸通道的灵敏度。“CONN_GND”（接地）设置提高了触摸通道的稳定性。
 *
 * @param type  选择空闲通道连接到高电阻状态或接地。
 */
#define touch_hal_get_idle_channel_connect(type) touch_ll_get_idle_channel_connect(type)

/**
 * 获取当前测量通道。触摸传感器测量为循环扫描模式。
 *
 * @return
 *      -触摸通道编号
 */
#define touch_hal_get_current_meas_channel() touch_ll_get_current_meas_channel()

/**
 * 通过位掩码启用触摸传感器中断。
 *
 * @param type 中断类型
 */
#define touch_hal_intr_enable(int_mask) touch_ll_intr_enable(int_mask)

/**
 * 通过位掩码禁用触摸传感器中断。
 *
 * @param type 中断类型
 */
#define touch_hal_intr_disable(int_mask) touch_ll_intr_disable(int_mask)

/**
 * 通过位掩码清除触摸传感器中断。
 *
 * @param int_mask 清除中断的键盘掩码
 */
#define touch_hal_intr_clear(int_mask) touch_ll_intr_clear(int_mask)

/**
 * 获取触摸传感器中断状态的位掩码。
 *
 * @return 类型中断类型
 */
#define touch_hal_read_intr_status_mask() touch_ll_read_intr_status_mask()

/**
 * 启用所有触摸传感器通道测量的超时检查。当触摸通道的触摸读数超过测量阈值时，如果启用：将产生超时中断，并进入下一个通道测量。如果禁用：FSM始终在信道上，直到该信道的测量结束。
 *
 * @note 在启用超时阈值之前，请正确设置超时阈值。
 */
#define touch_hal_timeout_enable() touch_ll_timeout_enable()

/**
 * 禁用所有触摸传感器通道测量的超时检查。当触摸通道的触摸读数超过测量阈值时，如果启用：将产生超时中断，并进入下一个通道测量。如果禁用：FSM始终在信道上，直到该信道的测量结束。
 *
 * @note 在启用超时阈值之前，请正确设置超时阈值。
 */
#define touch_hal_timeout_disable() touch_ll_timeout_disable()

/**
 * 为所有触摸传感器通道测量设置超时阈值。与触摸读数相比。
 *
 * @param threshold 设置为在一个通道上测量的最大时间。
 */
#define touch_hal_timeout_set_threshold(threshold) touch_ll_timeout_set_threshold(threshold)

/**
 * 获取所有触摸传感器通道测量的超时阈值。与触摸读数相比。
 *
 * @param threshold 指向超时阈值。
 */
#define touch_hal_timeout_get_threshold(threshold) touch_ll_timeout_get_threshold(threshold)

/**
 * 触摸计时器触发测量并始终等待测量完成。触摸计时器的强制完成确保计时器始终可以获得测量完成信号。
 */
#define touch_hal_timer_force_done() touch_ll_timer_force_done()

/************************过滤器寄存器设置************************/

/**
 * 设置触摸传感器滤波器和检测算法的参数。有关检测算法的更多详细信息，请参阅应用程序文档。
 *
 * @param filter_info 检测算法的滤波器类型和阈值选择
 */
void touch_hal_filter_set_config(const touch_filter_config_t *filter_info);

/**
 * 获取触摸传感器滤波器的参数和检测算法。有关检测算法的更多详细信息，请参阅应用程序文档。
 *
 * @param filter_info 检测算法的滤波器类型和阈值选择
 */
void touch_hal_filter_get_config(touch_filter_config_t *filter_info);

/**
 * 获取通过过滤原始数据获得的平滑数据。
 *
 * @param touch_num 触摸板索引
 * @param smooth_data 平滑数据指针
 */
#define touch_hal_filter_read_smooth(touch_num, smooth_data) touch_ll_filter_read_smooth(touch_num, smooth_data)

/**
 * 获取触摸传感器的基准值。
 *
 * @note 初始化后，基准值为第一个测量周期内的最大值。
 * @param touch_num 触摸板索引
 * @param touch_value 接受触摸传感器值的指针
 */
#define touch_hal_read_benchmark(touch_num, benchmark) touch_ll_read_benchmark(touch_num, benchmark)

/**
 * 强制将基准重置为触摸传感器的原始数据。
 *
 * @param touch_num 触摸板索引
 *                  -TOUCH_PAD_MAX重置所有通道的基线。
 */
#define touch_hal_reset_benchmark(touch_num) touch_ll_reset_benchmark(touch_num)

/**
 * 设置过滤器模式。滤波器的输入是触摸读数的原始值，滤波器的输出涉及触摸状态的判断。
 *
 * @param mode 过滤器模式类型。请参阅“touch_filter_mode_t”。
 */
#define touch_hal_filter_set_filter_mode(mode) touch_ll_filter_set_filter_mode(mode)

/**
 * 获取过滤器模式。滤波器的输入是触摸读数的原始值，滤波器的输出涉及触摸状态的判断。
 *
 * @param mode 过滤器模式类型。请参阅“touch_filter_mode_t”。
 */
#define touch_hal_filter_get_filter_mode(mode) touch_ll_filter_get_filter_mode(mode)

/**
 * 设置反跳计数，如“n”。如果测量值持续超过阈值“n”次，则确定触摸传感器状态改变。
 *
 * @param dbc_cnt 取消跳动计数值。
 */
#define touch_hal_filter_set_debounce(dbc_cnt) touch_ll_filter_set_debounce(dbc_cnt)

/**
 * 获取防抖计数。
 *
 * @param dbc_cnt 取消跳动计数值。
 */
#define touch_hal_filter_get_debounce(dbc_cnt) touch_ll_filter_get_debounce(dbc_cnt)

/**
 * 设置噪声阈值系数。更高=抗噪音能力更强。实际噪声应小于（噪声系数触摸阈值）。范围：0~3。系数为0:4/8；1: 3/8; 2: 2/8; 3: 1;
 *
 * @param hys_thr 噪声阈值系数。
 */
#define touch_hal_filter_set_noise_thres(noise_thr) touch_ll_filter_set_noise_thres(noise_thr)

/**
 * 获取噪声阈值系数。更高=抗噪音能力更强。实际噪声应小于（噪声系数触摸阈值）。范围：0~3。系数为0:4/8；1: 3/8; 2: 2/8; 3: 1;
 *
 * @param noise_thr 噪声阈值系数。
 */
#define touch_hal_filter_get_noise_thres(noise_thr) touch_ll_filter_get_noise_thres(noise_thr)

/**
 * 设置基准重置进程的累积数量。例如“n”。如果测量值持续超过负噪声阈值“n”次，则基准重置为原始数据。范围：0~15
 *
 * @param reset_cnt 基准重置进程的累积数量。
 */
#define touch_hal_filter_set_benchmark_reset(reset_cnt) touch_ll_filter_set_benchmark_reset(reset_cnt)

/**
 * 获取基准重置进程的累积数量。例如“n”。如果测量值持续超过负噪声阈值“n”次，则基准重置为原始数据。范围：0~15
 *
 * @param reset_cnt 基准重置进程的累积数量。
 */
#define touch_hal_filter_get_benchmark_reset(reset_cnt) touch_ll_filter_get_benchmark_reset(reset_cnt)

/**
 * 设置抖动滤波器步长。如果滤波器模式为抖动，应设置抖动的滤波器步长。范围：0~15
 *
 * @param step 数据的步长更改。
 */
#define touch_hal_filter_set_jitter_step(step) touch_ll_filter_set_jitter_step(step)

/**
 * 获取抖动滤波器步长。如果滤波器模式为抖动，应设置抖动的滤波器步长。范围：0~15
 *
 * @param step 数据的步长更改。
 */
#define touch_hal_filter_get_jitter_step(step) touch_ll_filter_get_jitter_step(step)

/**
 * 启用触摸传感器过滤器和检测算法。有关检测算法的更多详细信息，请参阅应用程序文档。
 */
#define touch_hal_filter_enable() touch_ll_filter_enable()

/**
 * 禁用触摸传感器过滤器和检测算法。有关检测算法的更多详细信息，请参阅应用程序文档。
 */
#define touch_hal_filter_disable() touch_ll_filter_disable()

/************************去噪寄存器设置************************/

/**
 * 设置降噪垫的参数（TOUCH_pad_NUM0）。T0是不具有相应外部GPIO的内部通道。T0将与测量的信道Tn同时工作。最后，Tn的实际测量值是减去T0的低位后的值。此去噪功能可滤除所有信道上引入的干扰，例如电源和外部EMI引入的噪声。
 *
 * @param denoise 去噪参数
 */
void touch_hal_denoise_set_config(const touch_pad_denoise_t *denoise);

/**
 * @brief 获取降噪垫的参数（TOUCH_pad_NUM0）。
 *
 * @param denoise 指向降噪参数的指针
 */
void touch_hal_denoise_get_config(touch_pad_denoise_t *denoise);

/**
 * 启用降噪功能。T0是不具有相应外部GPIO的内部通道。T0将与测量的信道Tn同时工作。最后，Tn的实际测量值是减去T0的低位后的值。此去噪功能可滤除所有信道上引入的干扰，例如电源和外部EMI引入的噪声。
 */
void touch_hal_denoise_enable(void);

/**
 * 启用降噪功能。T0是不具有相应外部GPIO的内部通道。T0将与测量的信道Tn同时工作。最后，Tn的实际测量值是减去T0的低位后的值。此去噪功能可滤除所有信道上引入的干扰，例如电源和外部EMI引入的噪声。
 */
#define touch_hal_denoise_disable() touch_ll_denoise_disable()

/**
 * 设置降噪通道的内部参考电容。选择适当的内部参考电容值，使去噪通道的读数最接近被测通道的读数。
 *
 * @param cap_level 电容水平。
 */
#define touch_hal_denoise_set_cap_level(cap_level) touch_ll_denoise_set_cap_level(cap_level)

/**
 * 获得去噪通道的内部参考电容。选择适当的内部参考电容值，使去噪通道的读数最接近被测通道的读数。
 *
 * @param cap_level 电容水平。
 */
#define touch_hal_denoise_get_cap_level(cap_level) touch_ll_denoise_get_cap_level(cap_level)

/**
 * 设置去噪通道的去噪范围。通过测量去噪信道的噪声幅度来确定。
 *
 * @param grade 去噪通道的去噪范围。
 */
#define touch_hal_denoise_set_grade(grade) touch_ll_denoise_set_grade(grade)

/**
 * 设置去噪通道的去噪范围。通过测量去噪信道的噪声幅度来确定。
 *
 * @param grade 去噪通道的去噪范围。
 */
#define touch_hal_denoise_get_grade(grade) touch_ll_denoise_get_grade(grade)

/**
 * 读取去噪测量值（TOUCH_PAD_NUM0）。
 *
 * @param denoise 去噪值。
 */
#define touch_hal_denoise_read_data(data) touch_ll_denoise_read_data(data)

/************************防水寄存器设置************************/
/**
 * 设置保护板的触摸通道使用。
 *
 * @param pad_num 触摸传感器通道编号。
 */
#define touch_hal_waterproof_set_guard_pad(pad_num) touch_ll_waterproof_set_guard_pad(pad_num)

/**
 * 获得用于保护垫的触摸通道。
 *
 * @param pad_num 触摸传感器通道编号。
 */
#define touch_hal_waterproof_get_guard_pad(pad_num) touch_ll_waterproof_get_guard_pad(pad_num)

/**
 * 设置屏蔽通道的最大等效电容。屏蔽通道的等效电容可以从去噪通道的读数中计算出来。
 *
 * @param pad_num 触摸传感器通道编号。
 */
#define touch_hal_waterproof_set_sheild_driver(driver_level) touch_ll_waterproof_set_sheild_driver(driver_level)

/**
 * 获取屏蔽通道的最大等效电容。屏蔽通道的等效电容可以从去噪通道的读数中计算出来。
 *
 * @param pad_num 触摸传感器通道编号。
 */
#define touch_hal_waterproof_get_sheild_driver(driver_level) touch_ll_waterproof_get_sheild_driver(driver_level)

/**
 * 设置防水功能参数。
 *
 * 防水功能包括屏蔽信道（TOUCH_PAD_NUM14）和保护信道。保护垫用于检测覆盖触摸面板的大面积水。屏蔽垫用于屏蔽覆盖触摸面板的水滴的影响。它通常设计为网格，并放置在触摸按钮周围。
 *
 * @param waterproof 防水参数
 */
void touch_hal_waterproof_set_config(const touch_pad_waterproof_t *waterproof);

/**
 * 获取防水功能参数。
 *
 * @param waterproof 防水参数。
 */
void touch_hal_waterproof_get_config(touch_pad_waterproof_t *waterproof);

/**
 * 启用防水功能参数。应在函数``touch_hal_waterroof_set_config``之后调用。
 */
void touch_hal_waterproof_enable(void);

/**
 * 禁用防水功能参数。
 */
#define touch_hal_waterproof_disable() touch_ll_waterproof_disable()

/************************接近寄存器设置************************/

/**
 * 启用/禁用触摸通道的接近功能。接近传感器测量是触摸通道测量的累积。
 *
 * @note 支持最多三个配置为接近传感器的触摸通道。
 * @param touch_num 触摸板索引
 * @param enabled true：启用接近功能；false：禁用接近功能
 * @return
 *     -true：配置正确。
 *     -false:配置错误。
 */
bool touch_hal_enable_proximity(touch_pad_t touch_num, bool enabled);

/**
 * 设置接近板的触摸通道编号。如果禁用接近焊盘，请将该焊盘指向`TOUCH_pad_NUM0`
 *
 * @param prox_pad 三个接近焊盘的阵列。
 */
#define touch_hal_proximity_set_channel_num(prox_pad) touch_ll_proximity_set_channel_num(prox_pad)

/**
 * 获取接近板的触摸通道编号。如果禁用接近焊盘，请将该焊盘指向`TOUCH_pad_NUM0`
 *
 * @param prox_pad 三个接近焊盘的阵列。
 */
#define touch_hal_proximity_get_channel_num(prox_pad) touch_ll_proximity_get_channel_num(prox_pad)

/**
 * 设置接近板的累计测量时间。
 *
 * @param times 累计测量周期数。
 */
#define touch_hal_proximity_set_meas_times(times) touch_ll_proximity_set_meas_times(times)

/**
 * 获取接近板的累计测量时间。
 *
 * @param times 累计测量周期数。
 */
#define touch_hal_proximity_get_meas_times(times) touch_ll_proximity_get_meas_times(times)

/**
 * 读取接近焊盘的当前累计测量时间。
 *
 * @param times 累计测量周期数。
 */
#define touch_hal_proximity_read_meas_cnt(touch_num, cnt) touch_ll_proximity_read_meas_cnt(touch_num, cnt)

/**
 * 检查触摸传感器通道是否为接近板。
 *
 * @param touch_num 触摸传感器通道编号。
 */
#define touch_hal_proximity_pad_check(touch_num) touch_ll_proximity_pad_check(touch_num)

/**************睡眠垫设置***********************/

/**
 * 获取触摸传感器睡眠通道参数。触摸传感器可以在睡眠模式下工作以唤醒睡眠。配置睡眠频道后，用户应使用特定功能查询频道读数。
 *
 * @param slp_config 指向触摸式睡眠板配置。
 */
void touch_hal_sleep_channel_get_config(touch_pad_sleep_channel_t *slp_config);

/**
 * 设置触摸传感器睡眠通道的参数。触摸传感器可以在睡眠模式下工作以唤醒睡眠。配置睡眠频道后，用户应使用特定功能查询频道读数。
 *
 * @note ESP32S2仅支持一个要设置为睡眠信道的信道。
 *
 * @param pad_num 触摸睡眠板编号。
 * @param enable 启用/禁用睡眠垫功能。
 */
void touch_hal_sleep_channel_enable(touch_pad_t pad_num, bool enable);

/**
 * 设置睡眠板的触摸通道编号。
 *
 * @note 深度睡眠模式下仅支持一个触摸传感器通道。
 * @param touch_num 触摸传感器通道编号。
 */
#define touch_hal_sleep_set_channel_num(touch_num) touch_ll_sleep_set_channel_num(touch_num)

/**
 * 获取睡眠板的触摸通道编号。
 *
 * @note 深度睡眠模式下仅支持一个触摸传感器通道。
 * @param touch_num 触摸传感器通道编号。
 */
#define touch_hal_sleep_get_channel_num(touch_num) touch_ll_sleep_get_channel_num(touch_num)

/**
 * 设置深度睡眠中触摸传感器的触发阈值。阈值确定触摸传感器的灵敏度。阈值是触发状态的原始值减去基准值。
 *
 * @note 睡眠时的阈值与睡眠前的阈值相同。
 */
#define touch_hal_sleep_set_threshold(touch_thres) touch_ll_sleep_set_threshold(touch_thres)

/**
 * 获取深度睡眠中触摸传感器的触发阈值。阈值确定触摸传感器的灵敏度。阈值是触发状态的原始值减去基准值。
 *
 * @note 睡眠时的阈值与睡眠前的阈值相同。
 */
#define touch_hal_sleep_get_threshold(touch_thres) touch_ll_sleep_get_threshold(touch_thres)

/**
 * 启用睡眠垫的接近功能。
 */
#define touch_hal_sleep_enable_approach() touch_ll_sleep_enable_approach()

/**
 * 禁用睡眠垫的接近功能。
 */
#define touch_hal_sleep_disable_approach() touch_ll_sleep_disable_approach()

/**
 * 读取睡眠垫触摸传感器的基准。
 *
 * @param benchmark 用于接受触摸传感器基准值的指针。
 */
#define touch_hal_sleep_read_benchmark(benchmark) touch_ll_sleep_read_benchmark(benchmark)

/**
 * 读取睡眠垫触摸传感器的平滑数据。
 */
#define touch_hal_sleep_read_smooth(smooth_data) touch_ll_sleep_read_smooth(smooth_data)

/**
 * 读取睡眠垫触摸传感器的原始数据。
 */
#define touch_hal_sleep_read_data(raw_data) touch_ll_sleep_read_data(raw_data)

/**
 * 重置睡眠垫触摸传感器的基准。
 */
#define touch_hal_sleep_reset_benchmark() touch_ll_sleep_reset_benchmark()

/**
 * 读取睡眠垫触摸传感器的防抖。
 *
 * @param debounce 用于接受触摸传感器反跳值的指针。
 */
#define touch_hal_sleep_read_debounce(debounce) touch_ll_sleep_read_debounce(debounce)

/**
 * 读取睡眠垫触摸传感器的接近计数。
 * @param proximity_cnt 用于接受触摸传感器接近计数值的指针。
 */
#define touch_hal_sleep_read_proximity_cnt(approach_cnt) touch_ll_sleep_read_proximity_cnt(approach_cnt)

/**
 * 获取导致从深度睡眠中醒来的触摸板。
 *
 * @param pad_num 导致唤醒的触摸板指针。
 */
#define touch_hal_get_wakeup_status(pad_num) touch_ll_get_wakeup_status(pad_num)

/**
 * 在深度睡眠状态下更改触摸板的工作频率。降低工作频率可以有效地降低功耗。如果未调用此功能，则深度睡眠状态下的触摸工作频率与唤醒状态下的相同。
 *
 * @param sleep_cycle 每次测量后，触摸传感器将休眠。sleep_cycle决定每次测量之间的间隔。t_sleep=sleep_cycle/（RTC_SLOW_CLK频率）。RTC_SLOW_CLK的近似频率值可以使用RTC_CLK_SLOW_freq_get_hz函数获得。
 * @param meas_times 触摸通道的每个测量过程中的充电和放电时间。定时器频率为8Mhz。范围：0~0xffff。建议的典型值：修改此值，使测量时间约为1ms。
 */
void touch_hal_sleep_channel_set_work_time(uint16_t sleep_cycle, uint16_t meas_times);

/**
 * 获取深度睡眠状态下触摸板的工作频率。降低工作频率可以有效地降低功耗。
 *
 * @param sleep_cycle 每次测量后，触摸传感器将休眠。sleep_cycle决定每次测量之间的间隔。t_sleep=sleep_cycle/（RTC_SLOW_CLK频率）。RTC_SLOW_CLK的近似频率值可以使用RTC_CLK_SLOW_freq_get_hz函数获得。
 * @param meas_times 触摸通道的每个测量过程中的充电和放电时间。定时器频率为8Mhz。范围：0~0xffff。建议的典型值：修改此值，使测量时间约为1ms。
 */
void touch_hal_sleep_channel_get_work_time(uint16_t *sleep_cycle, uint16_t *meas_times);

#ifdef __cplusplus
}
#endif

