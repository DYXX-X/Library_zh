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

// 触摸传感器的HAL层（公共部分）

#pragma once

#include "hal/touch_sensor_ll.h"
#include "hal/touch_sensor_types.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    touch_high_volt_t refh;
    touch_low_volt_t refl;
    touch_volt_atten_t atten;
} touch_hal_volt_t;

typedef struct {
    touch_cnt_slope_t slope;    /*!<为每个极板设置触摸传感器充电/放电速度（电流）。*/
    touch_tie_opt_t tie_opt;    /*!<为每次测量设置触摸通道的初始电压状态。*/
} touch_hal_meas_mode_t;

/**
 * 设置触摸传感器睡眠时间（测量间隔）。
 *
 * @param sleep_time  每次测量后，触摸传感器将休眠。sleep_cycle决定每次测量之间的间隔。t_sleep=sleep_cycle/（RTC_SLOW_CLK频率）。RTC_SLOW_CLK的近似频率值可使用“RTC_CLK_SLOW_freq_get_hz”函数获得。
 */
#define touch_hal_set_sleep_time(sleep_time) touch_ll_set_sleep_time(sleep_time)

/**
 * 获取触摸传感器睡眠时间。
 *
 * @param sleep_time 用于接受睡眠周期计数的指针。
 */
#define touch_hal_get_sleep_time(sleep_time) touch_ll_get_sleep_time(sleep_time)

/**
 * 设置触摸传感器通道的高/低电压阈值。触摸传感器通过对通道进行充电和放电来测量通道电容值。因此，充电阈值应小于电源电压。实际充电阈值是高电压阈值减去衰减值。
 *
 * @param refh 通道的高电压阈值。
 */
void touch_hal_set_voltage(const touch_hal_volt_t *volt);

/**
 * 获取触摸传感器通道的高/低电压阈值。触摸传感器通过对通道进行充电和放电来测量通道电容值。因此，充电阈值应小于电源电压。实际充电阈值是高电压阈值减去衰减值。
 *
 * @param refh 转换/放电的电压阈值。
 */
void touch_hal_get_voltage(touch_hal_volt_t *volt);

/**
 * 为每个极板测量设置触摸传感器充电/放电速度（电流）和初始电压状态。
 *
 * @param touch_num 触摸板索引。
 * @param meas 触摸板测量配置。
 */
void touch_hal_set_meas_mode(touch_pad_t touch_num, const touch_hal_meas_mode_t *meas);

/**
 * 获取每个极板测量的触摸传感器充电/放电速度（电流）和初始电压状态。
 *
 * @param touch_num 触摸板索引。
 * @param meas 触摸板测量配置。
 */
void touch_hal_get_meas_mode(touch_pad_t touch_num, touch_hal_meas_mode_t *meas);

/**
 * 设置触摸传感器FSM模式。测量动作可以由硬件计时器以及软件指令触发。
 *
 * @param mode FSM模式。
 */
#define touch_hal_set_fsm_mode(mode) touch_ll_set_fsm_mode(mode)

/**
 * 获取触摸传感器FSM模式。测量动作可以由硬件计时器以及软件指令触发。
 *
 * @param mode FSM模式。
 */
#define touch_hal_get_fsm_mode(mode) touch_ll_get_fsm_mode(mode)

/**
 * 启动触摸传感器FSM计时器。测量动作可以由硬件计时器以及软件指令触发。
 */
#define touch_hal_start_fsm() touch_ll_start_fsm()

/**
 * 停止触摸传感器FSM计时器。测量动作可以由硬件计时器以及软件指令触发。
 */
#define touch_hal_stop_fsm() touch_ll_stop_fsm()

/**
 * 触发触摸传感器测量，仅支持FSM的SW模式。
 */
#define touch_hal_start_sw_meas() touch_ll_start_sw_meas()

/**
 * 设置触摸传感器中断阈值。
 *
 * @note 请参阅“touch_pad_set_trigger_mode”以了解如何设置触发模式。
 * @param touch_num 触摸板索引。
 * @param threshold 触摸板计数阈值。
 */
#define touch_hal_set_threshold(touch_num, threshold) touch_ll_set_threshold(touch_num, threshold)

/**
 * 获取触摸传感器中断阈值。
 *
 * @param touch_num 触摸板索引。
 * @param threshold 接受阈值的指针。
 */
#define touch_hal_get_threshold(touch_num, threshold) touch_ll_get_threshold(touch_num, threshold)

/**
 * 启用触摸传感器通道。将触摸通道注册到触摸传感器测量组中。触摸传感器的工作模式是同时测量。此函数将根据给定的位掩码设置测量位。
 *
 * @note  如果设置此掩码，则应首先停止FSM计时器。
 * @note  在扫描图中的触摸传感器，应首先取消GPIO功能。
 * @param enable_mask 触摸传感器扫描组的位掩码。e、 g.TOUCH_PAD_NUM1->位（1）
 * @return
 *      -成功时ESP_OK
 */
#define touch_hal_set_channel_mask(enable_mask) touch_ll_set_channel_mask(enable_mask)

/**
 * 获取触摸传感器通道掩码。
 *
 * @param enable_mask 触摸传感器扫描组的位掩码。e、 g.TOUCH_PAD_NUM1->位（1）
 */
#define touch_hal_get_channel_mask(enable_mask) touch_ll_get_channel_mask(enable_mask)

/**
 * 通过位掩码禁用触摸传感器通道。
 *
 * @param enable_mask 触摸传感器扫描组的位掩码。e、 g.TOUCH_PAD_NUM1->位（1）
 */
#define touch_hal_clear_channel_mask(disable_mask) touch_ll_clear_channel_mask(disable_mask)

/**
 * 获取触摸传感器状态，通常用于ISR中，以确定哪些焊盘被“触摸”。
 *
 * @param status_mask 触摸传感器状态。e、 g.触摸1触发状态为“status_mask&（BIT1）”。
 */
#define touch_hal_read_trigger_status_mask(status_mask) touch_ll_read_trigger_status_mask(status_mask)

/**
 * 清除所有触摸传感器状态。
 */
#define touch_hal_clear_trigger_status_mask() touch_ll_clear_trigger_status_mask()

/**
 * 从寄存器中获取触摸传感器原始数据（触摸传感器计数器值）。没有障碍。
 *
 * @param touch_num 触摸板索引。
 * @return 用于接受触摸传感器值的touch_value指针。
 */
#define touch_hal_read_raw_data(touch_num) touch_ll_read_raw_data(touch_num)

/**
 * 获取触摸传感器测量状态。没有障碍。
 *
 * @return
 *      -如果触摸传感器测量完成。
 */
#define touch_hal_meas_is_done() touch_ll_meas_is_done()

/**
 * 初始化触摸模块。
 *
 * @note  如果默认参数与使用场景不匹配，则可以在该函数之后更改。
 */
void touch_hal_init(void);

/**
 * 取消安装触摸板驱动程序。
 *
 * @note  调用此功能后，禁止调用其他触摸功能。
 */
void touch_hal_deinit(void);

/**
 * 为每个通道配置触摸传感器。
 */
void touch_hal_config(touch_pad_t touch_num);

#ifdef __cplusplus
}
#endif

