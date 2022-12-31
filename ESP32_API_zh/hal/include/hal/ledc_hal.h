// 版权所有2019 Espressif Systems（上海）私人有限公司
//
// 根据Apache许可证2.0版（“许可证”）获得许可；
// 除非符合许可证，否则不得使用此文件。
// 您可以在以下地址获取许可证副本：

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

// LEDC的HAL层。
// hal层中没有参数检查，因此调用者必须确保参数的正确性。

#pragma once

#include "hal/ledc_ll.h"
#include "hal/ledc_types.h"

/**
 * 驾驶员和HAL应维护的上下文
 */
typedef struct {
    ledc_dev_t *dev;
    ledc_mode_t speed_mode;
} ledc_hal_context_t;

/**
 * @brief 设置LEDC低速定时器时钟
 *
 * @param hal HAL层的上下文
 * @param slow_clk_sel LEDC低速定时器时钟源
 *
 * @return 没有一个
 */
#define ledc_hal_set_slow_clk_sel(hal, slow_clk_sel)  ledc_ll_set_slow_clk_sel((hal)->dev, slow_clk_sel)

/**
 * @brief 获取LEDC低速定时器时钟
 *
 * @param hal HAL层的上下文
 * @param slow_clk_sel LEDC低速定时器时钟源
 *
 * @return 没有一个
 */
#define ledc_hal_get_slow_clk_sel(hal, slow_clk_sel)  ledc_ll_get_slow_clk_sel((hal)->dev, slow_clk_sel)

/**
 * @brief 更新LEDC低速计时器
 *
 * @param hal HAL层的上下文
 * @param timer_sel LEDC计时器索引（0-3），从LEDC_timer_t中选择
 *
 * @return 没有一个
 */
#define ledc_hal_ls_timer_update(hal, timer_sel)  ledc_ll_ls_timer_update((hal)->dev, (hal)->speed_mode, timer_sel)

/**
 * @brief 重置LEDC计时器
 *
 * @param hal HAL层的上下文
 * @param timer_sel LEDC计时器索引（0-3），从LEDC_timer_t中选择
 *
 * @return 没有一个
 */
#define ledc_hal_timer_rst(hal, timer_sel)  ledc_ll_timer_rst((hal)->dev, (hal)->speed_mode, timer_sel)

/**
 * @brief 暂停LEDC计时器
 *
 * @param hal HAL层的上下文
 * @param timer_sel LEDC计时器索引（0-3），从LEDC_timer_t中选择
 *
 * @return 没有一个
 */
#define ledc_hal_timer_pause(hal, timer_sel)  ledc_ll_timer_pause((hal)->dev, (hal)->speed_mode, timer_sel)

/**
 * @brief 恢复LEDC计时器
 *
 * @param hal HAL层的上下文
 * @param timer_sel LEDC计时器索引（0-3），从LEDC_timer_t中选择
 *
 * @return 没有一个
 */
#define ledc_hal_timer_resume(hal, timer_sel)  ledc_ll_timer_resume((hal)->dev, (hal)->speed_mode, timer_sel)

/**
 * @brief 设置LEDC定时器时钟分频器
 *
 * @param hal HAL层的上下文
 * @param timer_sel LEDC计时器索引（0-3），从LEDC_timer_t中选择
 * @param clock_divider 计时器时钟分频值，计时器时钟从所选时钟源分频
 *
 * @return 没有一个
 */
#define ledc_hal_set_clock_divider(hal, timer_sel, clock_divider)  ledc_ll_set_clock_divider((hal)->dev, (hal)->speed_mode, timer_sel, clock_divider)

/**
 * @brief 获取LEDC定时器时钟分频器
 *
 * @param hal HAL层的上下文
 * @param timer_sel LEDC计时器索引（0-3），从LEDC_timer_t中选择
 * @param clock_divider 计时器时钟分频值，计时器时钟从所选时钟源分频
 *
 * @return 没有一个
 */
#define ledc_hal_get_clock_divider(hal, timer_sel, clock_divider)  ledc_ll_get_clock_divider((hal)->dev, (hal)->speed_mode, timer_sel, clock_divider)

/**
 * @brief 设置LEDC定时器时钟源
 *
 * @param hal HAL层的上下文
 * @param timer_sel LEDC计时器索引（0-3），从LEDC_timer_t中选择
 * @param clk_src 定时器时钟源
 *
 * @return 没有一个
 */
#define ledc_hal_set_clock_source(hal, timer_sel, clk_src)  ledc_ll_set_clock_source((hal)->dev, (hal)->speed_mode, timer_sel, clk_src)

/**
 * @brief 获取LEDC定时器时钟源
 *
 * @param hal HAL层的上下文
 * @param timer_sel LEDC计时器索引（0-3），从LEDC_timer_t中选择
 * @param clk_src 接受计时器时钟源的指针
 *
 * @return 没有一个
 */
#define ledc_hal_get_clock_source(hal, timer_sel, clk_src)  ledc_ll_get_clock_source((hal)->dev, (hal)->speed_mode, timer_sel, clk_src)

/**
 * @brief 设置LEDC占空比分辨率
 *
 * @param hal HAL层的上下文
 * @param timer_sel LEDC计时器索引（0-3），从LEDC_timer_t中选择
 * @param duty_resolution 占空比设置的分辨率（位数）。占空值范围为[0，（2**duty_desolution）]
 *
 * @return 没有一个
 */
#define ledc_hal_set_duty_resolution(hal, timer_sel, duty_resolution)  ledc_ll_set_duty_resolution((hal)->dev, (hal)->speed_mode, timer_sel, duty_resolution)

/**
 * @brief 获取LEDC任务解决方案
 *
 * @param hal HAL层的上下文
 * @param timer_sel LEDC计时器索引（0-3），从LEDC_timer_t中选择
 * @param duty_resolution 用于接受占空比设置分辨率（位数）的指针。
 *
 * @return 没有一个
 */
#define ledc_hal_get_duty_resolution(hal, timer_sel, duty_resolution)  ledc_ll_get_duty_resolution((hal)->dev, (hal)->speed_mode, timer_sel, duty_resolution)

/**
 * @brief 获取LEDC最大负载
 *
 * @param hal HAL层的上下文
 * @param channel_num LEDC信道索引（0-7），从LEDC_channel_t中选择
 * @param max_duty 接受最大负载的指针
 *
 * @return 没有一个
 */
#define ledc_hal_get_max_duty(hal, channel_num, max_duty)  ledc_ll_get_max_duty((hal)->dev, (hal)->speed_mode, channel_num, max_duty)

/**
 * @brief 获取LEDC hpoint值
 *
 * @param hal HAL层的上下文
 * @param channel_num LEDC信道索引（0-7），从LEDC_channel_t中选择
 * @param hpoint_val 用于接受LEDC hpoint值的指针（最大值：0xfffff）
 *
 * @return 没有一个
 */
#define ledc_hal_get_hpoint(hal, channel_num, hpoint_val)  ledc_ll_get_hpoint((hal)->dev, (hal)->speed_mode, channel_num, hpoint_val)

/**
 * @brief 将LEDC设置为占空值的整数部分
 *
 * @param hal HAL层的上下文
 * @param channel_num LEDC信道索引（0-7），从LEDC_channel_t中选择
 * @param duty_val LEDC占空比值，占空比设置范围为[0，（2**占空比分辨率）]
 *
 * @return 没有一个
 */
#define ledc_hal_set_duty_int_part(hal, channel_num, duty_val)  ledc_ll_set_duty_int_part((hal)->dev, (hal)->speed_mode, channel_num, duty_val)

/**
 * @brief 设置输出启用
 *
 * @param hal HAL层的上下文
 * @param channel_num LEDC信道索引（0-7），从LEDC_channel_t中选择
 * @param sig_out_en 输出启用状态
 *
 * @return 没有一个
 */
#define ledc_hal_set_sig_out_en(hal, channel_num, sig_out_en)  ledc_ll_set_sig_out_en((hal)->dev, (hal)->speed_mode, channel_num, sig_out_en)

/**
 * @brief 设置负载启动
 *
 * @param hal HAL层的上下文
 * @param channel_num LEDC信道索引（0-7），从LEDC_channel_t中选择
 * @param duty_start 工作开始时间
 *
 * @return 没有一个
 */
#define ledc_hal_set_duty_start(hal, channel_num, duty_start)  ledc_ll_set_duty_start((hal)->dev, (hal)->speed_mode, channel_num, duty_start)

/**
 * @brief 设置输出空闲电平
 *
 * @param hal HAL层的上下文
 * @param channel_num LEDC信道索引（0-7），从LEDC_channel_t中选择
 * @param idle_level 输出怠速水平
 *
 * @return 没有一个
 */
#define ledc_hal_set_idle_level(hal, channel_num, idle_level)  ledc_ll_set_idle_level((hal)->dev, (hal)->speed_mode, channel_num, idle_level)

/**
 * @brief 设置淡入结束中断启用
 *
 * @param hal HAL层的上下文
 * @param channel_num LEDC信道索引（0-7），从LEDC_channel_t中选择
 * @param fade_end_intr_en 淡入结束中断启用状态
 *
 * @return 没有一个
 */
#define ledc_hal_set_fade_end_intr(hal, channel_num, fade_end_intr_en)  ledc_ll_set_fade_end_intr((hal)->dev, (hal)->speed_mode, channel_num, fade_end_intr_en)

/**
 * @brief 设置指定频道的计时器索引
 *
 * @param hal HAL层的上下文
 * @param channel_num LEDC信道索引（0-7），从LEDC_channel_t中选择
 * @param timer_sel LEDC计时器索引（0-3），从LEDC_timer_t中选择
 *
 * @return 没有一个
 */
#define ledc_hal_bind_channel_timer(hal, channel_num, timer_sel)  ledc_ll_bind_channel_timer((hal)->dev, (hal)->speed_mode, channel_num, timer_sel)

/**
 * @brief 获取指定频道的计时器索引
 *
 * @param hal HAL层的上下文
 * @param channel_num LEDC信道索引（0-7），从LEDC_channel_t中选择
 * @param timer_sel 接受LEDC计时器索引的指针
 *
 * @return 没有一个
 */
#define ledc_hal_get_channel_timer(hal, channel_num, timer_sel)  ledc_ll_get_channel_timer((hal)->dev, (hal)->speed_mode, channel_num, timer_sel)

/**
 * @brief 初始化LEDC hal。在调用其他hal层函数之前，应先调用此函数
 *
 * @param hal HAL层的上下文
 * @param speed_mode speed_mode选择LEDC speed_mode、高速模式和低速模式
 *
 * @return 没有一个
 */
void ledc_hal_init(ledc_hal_context_t *hal, ledc_mode_t speed_mode);

/**
 * @brief 选择低速模式时更新信道配置
 *
 * @param hal HAL层的上下文
 * @param channel_num LEDC信道索引（0-7），从LEDC_channel_t中选择
 *
 * @return 没有一个
 */
void ledc_hal_ls_channel_update(ledc_hal_context_t *hal, ledc_channel_t channel_num);

/**
 * @brief 设置LEDC hpoint值
 *
 * @param hal HAL层的上下文
 * @param channel_num LEDC信道索引（0-7），从LEDC_channel_t中选择
 * @param hpoint_val LEDC hpoint值（最大值：0xfffff）
 *
 * @return 没有一个
 */
void ledc_hal_set_hpoint(ledc_hal_context_t *hal, ledc_channel_t channel_num, uint32_t hpoint_val);

/**
 * @brief 获取LEDC占空值
 *
 * @param hal HAL层的上下文
 * @param channel_num LEDC信道索引（0-7），从LEDC_channel_t中选择
 * @param duty_val 接受LEDC占空值的指针
 *
 * @return 没有一个
 */
void ledc_hal_get_duty(ledc_hal_context_t *hal, ledc_channel_t channel_num, uint32_t *duty_val);

/**
 * @brief 设置LEDC占空比变化方向
 *
 * @param hal HAL层的上下文
 * @param channel_num LEDC信道索引（0-7），从LEDC_channel_t中选择
 * @param duty_direction LEDC占空比改变方向，增加或减少
 *
 * @return 没有一个
 */
void ledc_hal_set_duty_direction(ledc_hal_context_t *hal, ledc_channel_t channel_num, ledc_duty_direction_t duty_direction);

/**
 * @brief 设置增加或减少的次数
 *
 * @param hal HAL层的上下文
 * @param channel_num LEDC信道索引（0-7），从LEDC_channel_t中选择
 * @param duty_num 增加或减少的次数
 *
 * @return 没有一个
 */
void ledc_hal_set_duty_num(ledc_hal_context_t *hal, ledc_channel_t channel_num, uint32_t duty_num);

/**
 * @brief 设置增加或减少的占空比
 *
 * @param hal HAL层的上下文
 * @param channel_num LEDC信道索引（0-7），从LEDC_channel_t中选择
 * @param duty_cycle 占空比
 *
 * @return 没有一个
 */
void ledc_hal_set_duty_cycle(ledc_hal_context_t *hal, ledc_channel_t channel_num, uint32_t duty_cycle);

/**
 * @brief 设置增加或减少的步长
 *
 * @param hal HAL层的上下文
 * @param channel_num LEDC信道索引（0-7），从LEDC_channel_t中选择
 * @param duty_scale 步长
 *
 * @return 没有一个
 */
void ledc_hal_set_duty_scale(ledc_hal_context_t *hal, ledc_channel_t channel_num, uint32_t duty_scale);

/**
 * @brief 获取指定通道的中断状态
 *
 * @param hal HAL层的上下文
 * @param channel_num LEDC信道索引（0-7），从LEDC_channel_t中选择
 * @param intr_status 接受中断状态的指针
 *
 * @return 没有一个
 */
void ledc_hal_get_fade_end_intr_status(ledc_hal_context_t *hal, uint32_t *intr_status);

/**
 * @brief 清除指定通道的中断状态
 *
 * @param hal HAL层的上下文
 * @param channel_num LEDC信道索引（0-7），从LEDC_channel_t中选择
 *
 * @return 没有一个
 */
void ledc_hal_clear_fade_end_intr_status(ledc_hal_context_t *hal, ledc_channel_t channel_num);

/**
 * @brief 获取LEDC计时器的时钟配置
 *
 * @param hal HAL层的上下文
 * @param timer_sel LEDC计时器索引（0-3），从LEDC_timer_t中选择
 * @param clk_cfg 用于接受时钟配置的指针
 *
 * @return 没有一个
 */
void ledc_hal_get_clk_cfg(ledc_hal_context_t *hal, ledc_timer_t timer_sel, ledc_clk_cfg_t *clk_cfg);

/**
 * @brief 使用时钟配置配置低速计时器时钟源
 * @param hal HAL层的上下文
 * @param clk_cfg 时钟配置
 *
 * @return 没有一个
 */
void ledc_hal_set_slow_clk(ledc_hal_context_t *hal, ledc_clk_cfg_t clk_cfg);

