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

// 用于LEDC寄存器操作的LL层。
// 注意，该层中的大多数寄存器操作都是非原子操作。

#pragma once

#include "hal/ledc_types.h"
#include "soc/ledc_periph.h"
#include "soc/ledc_struct.h"

#ifdef __cplusplus
extern "C" {
#endif

#define LEDC_LL_GET_HW() &LEDC

/**
 * @brief 设置LEDC低速定时器时钟
 *
 * @param hw 外围寄存器的起始地址
 * @param slow_clk_sel LEDC低速定时器时钟源
 *
 * @return 没有一个
 */
static inline void ledc_ll_set_slow_clk_sel(ledc_dev_t *hw, ledc_slow_clk_sel_t slow_clk_sel){
    uint32_t clk_sel_val = 0;
    if (slow_clk_sel == LEDC_SLOW_CLK_APB) {
        clk_sel_val = 1;
    } else if (slow_clk_sel == LEDC_SLOW_CLK_RTC8M) {
        clk_sel_val = 2;
    } else if (slow_clk_sel == LEDC_SLOW_CLK_XTAL) {
        clk_sel_val = 3;
    }
    hw->conf.apb_clk_sel = clk_sel_val;
}

/**
 * @brief 获取LEDC低速定时器时钟
 *
 * @param hw 外围寄存器的起始地址
 * @param slow_clk_sel LEDC低速定时器时钟源
 *
 * @return 没有一个
 */
static inline void ledc_ll_get_slow_clk_sel(ledc_dev_t *hw, ledc_slow_clk_sel_t *slow_clk_sel){
    uint32_t clk_sel_val = hw->conf.apb_clk_sel;
    if (clk_sel_val == 1) {
        *slow_clk_sel = LEDC_SLOW_CLK_APB;
    } else if (clk_sel_val == 2) {
        *slow_clk_sel = LEDC_SLOW_CLK_RTC8M;
    } else if (clk_sel_val == 3) {
        *slow_clk_sel = LEDC_SLOW_CLK_XTAL;
    }
}

/**
 * @brief 更新LEDC低速计时器
 *
 * @param hw 外围寄存器的起始地址
 * @param speed_mode LEDC speed_mode，高速模式或低速模式
 * @param timer_sel LEDC计时器索引（0-3），从LEDC_timer_t中选择
 *
 * @return 没有一个
 */
static inline void ledc_ll_ls_timer_update(ledc_dev_t *hw, ledc_mode_t speed_mode, ledc_timer_t timer_sel){
    hw->timer_group[speed_mode].timer[timer_sel].conf.low_speed_update = 1;
}

/**
 * @brief 重置LEDC计时器
 *
 * @param hw 外围寄存器的起始地址
 * @param speed_mode LEDC speed_mode，高速模式或低速模式
 * @param timer_sel LEDC计时器索引（0-3），从LEDC_timer_t中选择
 *
 * @return 没有一个
 */
static inline void ledc_ll_timer_rst(ledc_dev_t *hw, ledc_mode_t speed_mode, ledc_timer_t timer_sel){
    hw->timer_group[speed_mode].timer[timer_sel].conf.rst = 1;
    hw->timer_group[speed_mode].timer[timer_sel].conf.rst = 0;
}

/**
 * @brief 暂停LEDC计时器
 *
 * @param hw 外围寄存器的起始地址
 * @param speed_mode LEDC speed_mode，高速模式或低速模式
 * @param timer_sel LEDC计时器索引（0-3），从LEDC_timer_t中选择
 *
 * @return 没有一个
 */
static inline void ledc_ll_timer_pause(ledc_dev_t *hw, ledc_mode_t speed_mode, ledc_timer_t timer_sel){
    hw->timer_group[speed_mode].timer[timer_sel].conf.pause = 1;
}

/**
 * @brief 恢复LEDC计时器
 *
 * @param hw 外围寄存器的起始地址
 * @param speed_mode LEDC speed_mode，高速模式或低速模式
 * @param timer_sel LEDC计时器索引（0-3），从LEDC_timer_t中选择
 *
 * @return 没有一个
 */
static inline void ledc_ll_timer_resume(ledc_dev_t *hw, ledc_mode_t speed_mode, ledc_timer_t timer_sel){
    hw->timer_group[speed_mode].timer[timer_sel].conf.pause = 0;
}

/**
 * @brief 设置LEDC定时器时钟分频器
 *
 * @param hw 外围寄存器的起始地址
 * @param speed_mode LEDC speed_mode，高速模式或低速模式
 * @param timer_sel LEDC计时器索引（0-3），从LEDC_timer_t中选择
 * @param clock_divider 计时器时钟分频值，计时器时钟从所选时钟源分频
 *
 * @return 没有一个
 */
static inline void ledc_ll_set_clock_divider(ledc_dev_t *hw, ledc_mode_t speed_mode, ledc_timer_t timer_sel, uint32_t clock_divider){
    hw->timer_group[speed_mode].timer[timer_sel].conf.clock_divider = clock_divider;
}

/**
 * @brief 获取LEDC定时器时钟分频器
 *
 * @param hw 外围寄存器的起始地址
 * @param speed_mode LEDC speed_mode，高速模式或低速模式
 * @param timer_sel LEDC计时器索引（0-3），从LEDC_timer_t中选择
 * @param clock_divider 计时器时钟分频值，计时器时钟从所选时钟源分频
 *
 * @return 没有一个
 */
static inline void ledc_ll_get_clock_divider(ledc_dev_t *hw, ledc_mode_t speed_mode, ledc_timer_t timer_sel, uint32_t *clock_divider){
    *clock_divider = hw->timer_group[speed_mode].timer[timer_sel].conf.clock_divider;
}

/**
 * @brief 设置LEDC定时器时钟源
 *
 * @param hw 外围寄存器的起始地址
 * @param speed_mode LEDC speed_mode，高速模式或低速模式
 * @param timer_sel LEDC计时器索引（0-3），从LEDC_timer_t中选择
 * @param clk_src 定时器时钟源
 *
 * @return 没有一个
 */
static inline void ledc_ll_set_clock_source(ledc_dev_t *hw, ledc_mode_t speed_mode, ledc_timer_t timer_sel, ledc_clk_src_t clk_src){
    if (clk_src == LEDC_REF_TICK) {
        //REF_TICK只能在选择APB时使用。
        hw->timer_group[speed_mode].timer[timer_sel].conf.tick_sel = 1;
        hw->conf.apb_clk_sel = 1;
    } else {
        hw->timer_group[speed_mode].timer[timer_sel].conf.tick_sel = 0;
    }
}

/**
 * @brief 获取LEDC定时器时钟源
 *
 * @param hw 外围寄存器的起始地址
 * @param speed_mode LEDC speed_mode，高速模式或低速模式
 * @param timer_sel LEDC计时器索引（0-3），从LEDC_timer_t中选择
 * @param clk_src 接受计时器时钟源的指针
 *
 * @return 没有一个
 */
static inline void ledc_ll_get_clock_source(ledc_dev_t *hw, ledc_mode_t speed_mode, ledc_timer_t timer_sel, ledc_clk_src_t *clk_src){
    if (hw->timer_group[speed_mode].timer[timer_sel].conf.tick_sel == 1) {
        *clk_src = LEDC_REF_TICK;
    } else {
        *clk_src = LEDC_APB_CLK;
    }
}

/**
 * @brief 设置LEDC占空比分辨率
 *
 * @param hw 外围寄存器的起始地址
 * @param speed_mode LEDC speed_mode，高速模式或低速模式
 * @param timer_sel LEDC计时器索引（0-3），从LEDC_timer_t中选择
 * @param duty_resolution 占空比设置的分辨率（位数）。占空值范围为[0，（2**duty_desolution）]
 *
 * @return 没有一个
 */
static inline void ledc_ll_set_duty_resolution(ledc_dev_t *hw, ledc_mode_t speed_mode, ledc_timer_t timer_sel, uint32_t duty_resolution){
    hw->timer_group[speed_mode].timer[timer_sel].conf.duty_resolution = duty_resolution;
}

/**
 * @brief 获取LEDC任务解决方案
 *
 * @param hw 外围寄存器的起始地址
 * @param speed_mode LEDC speed_mode，高速模式或低速模式
 * @param timer_sel LEDC计时器索引（0-3），从LEDC_timer_t中选择
 * @param duty_resolution 用于接受占空比设置分辨率（位数）的指针。
 *
 * @return 没有一个
 */
static inline void ledc_ll_get_duty_resolution(ledc_dev_t *hw, ledc_mode_t speed_mode, ledc_timer_t timer_sel, uint32_t *duty_resolution){
    *duty_resolution = hw->timer_group[speed_mode].timer[timer_sel].conf.duty_resolution;
}

/**
 * @brief 选择低速模式时更新信道配置
 *
 * @param hw 外围寄存器的起始地址
 * @param speed_mode LEDC speed_mode，高速模式或低速模式
 * @param channel_num LEDC信道索引（0-7），从LEDC_channel_t中选择
 *
 * @return 没有一个
 */
static inline void ledc_ll_ls_channel_update(ledc_dev_t *hw, ledc_mode_t speed_mode, ledc_channel_t channel_num){
    hw->channel_group[speed_mode].channel[channel_num].conf0.low_speed_update = 1;
}

/**
 * @brief 获取LEDC最大负载
 *
 * @param hw 外围寄存器的起始地址
 * @param speed_mode LEDC speed_mode，高速模式或低速模式
 * @param channel_num LEDC信道索引（0-7），从LEDC_channel_t中选择
 * @param max_duty 接受最大负载的指针
 *
 * @return 没有一个
 */
static inline void ledc_ll_get_max_duty(ledc_dev_t *hw, ledc_mode_t speed_mode, ledc_channel_t channel_num, uint32_t *max_duty){
    uint32_t timer_sel = hw->channel_group[speed_mode].channel[channel_num].conf0.timer_sel;
    *max_duty = (1 << (LEDC.timer_group[speed_mode].timer[timer_sel].conf.duty_resolution));
}

/**
 * @brief 设置LEDC hpoint值
 *
 * @param hw 外围寄存器的起始地址
 * @param speed_mode LEDC speed_mode，高速模式或低速模式
 * @param channel_num LEDC信道索引（0-7），从LEDC_channel_t中选择
 * @param hpoint_val LEDC hpoint值（最大值：0xfffff）
 *
 * @return 没有一个
 */
static inline void ledc_ll_set_hpoint(ledc_dev_t *hw, ledc_mode_t speed_mode, ledc_channel_t channel_num, uint32_t hpoint_val){
    hw->channel_group[speed_mode].channel[channel_num].hpoint.hpoint = hpoint_val;
}

/**
 * @brief 获取LEDC hpoint值
 *
 * @param hw 外围寄存器的起始地址
 * @param speed_mode LEDC speed_mode，高速模式或低速模式
 * @param channel_num LEDC信道索引（0-7），从LEDC_channel_t中选择
 * @param hpoint_val 用于接受LEDC hpoint值的指针（最大值：0xfffff）
 *
 * @return 没有一个
 */
static inline void ledc_ll_get_hpoint(ledc_dev_t *hw, ledc_mode_t speed_mode, ledc_channel_t channel_num, uint32_t *hpoint_val){
    *hpoint_val = hw->channel_group[speed_mode].channel[channel_num].hpoint.hpoint;
}

/**
 * @brief 将LEDC设置为占空值的整数部分
 *
 * @param hw 外围寄存器的起始地址
 * @param speed_mode LEDC speed_mode，高速模式或低速模式
 * @param channel_num LEDC信道索引（0-7），从LEDC_channel_t中选择
 * @param duty_val LEDC占空比值，占空比设置范围为[0，（2**占空比分辨率）]
 *
 * @return 没有一个
 */
static inline void ledc_ll_set_duty_int_part(ledc_dev_t *hw, ledc_mode_t speed_mode, ledc_channel_t channel_num, uint32_t duty_val){
    hw->channel_group[speed_mode].channel[channel_num].duty.duty = duty_val << 4;
}

/**
 * @brief 获取LEDC占空值
 *
 * @param hw 外围寄存器的起始地址
 * @param speed_mode LEDC speed_mode，高速模式或低速模式
 * @param channel_num LEDC信道索引（0-7），从LEDC_channel_t中选择
 * @param duty_val 接受LEDC占空值的指针
 *
 * @return 没有一个
 */
static inline void ledc_ll_get_duty(ledc_dev_t *hw, ledc_mode_t speed_mode, ledc_channel_t channel_num, uint32_t *duty_val){
    *duty_val = (hw->channel_group[speed_mode].channel[channel_num].duty_rd.duty_read >> 4);
}

/**
 * @brief 设置LEDC占空比变化方向
 *
 * @param hw 外围寄存器的起始地址
 * @param speed_mode LEDC speed_mode，高速模式或低速模式
 * @param channel_num LEDC信道索引（0-7），从LEDC_channel_t中选择
 * @param duty_direction LEDC占空比改变方向，增加或减少
 *
 * @return 没有一个
 */
static inline void ledc_ll_set_duty_direction(ledc_dev_t *hw, ledc_mode_t speed_mode, ledc_channel_t channel_num, ledc_duty_direction_t duty_direction){
    hw->channel_group[speed_mode].channel[channel_num].conf1.duty_inc = duty_direction;
}

/**
 * @brief 获取LEDC职责变更方向
 *
 * @param hw 外围寄存器的起始地址
 * @param speed_mode LEDC speed_mode，高速模式或低速模式
 * @param channel_num LEDC信道索引（0-7），从LEDC_channel_t中选择
 * @param duty_direction 用于接受LEDC占空比改变方向、增加或减少的指针
 *
 * @return 没有一个
 */
static inline void ledc_ll_get_duty_direction(ledc_dev_t *hw, ledc_mode_t speed_mode, ledc_channel_t channel_num, ledc_duty_direction_t *duty_direction){
    *duty_direction = hw->channel_group[speed_mode].channel[channel_num].conf1.duty_inc;
}

/**
 * @brief 设置增加或减少的次数
 *
 * @param hw 外围寄存器的起始地址
 * @param speed_mode LEDC speed_mode，高速模式或低速模式
 * @param channel_num LEDC信道索引（0-7），从LEDC_channel_t中选择
 * @param duty_num 增加或减少的次数
 *
 * @return 没有一个
 */
static inline void ledc_ll_set_duty_num(ledc_dev_t *hw, ledc_mode_t speed_mode, ledc_channel_t channel_num, uint32_t duty_num){
    hw->channel_group[speed_mode].channel[channel_num].conf1.duty_num = duty_num;
}

/**
 * @brief 设置增加或减少的占空比
 *
 * @param hw 外围寄存器的起始地址
 * @param speed_mode LEDC speed_mode，高速模式或低速模式
 * @param channel_num LEDC信道索引（0-7），从LEDC_channel_t中选择
 * @param duty_cycle 占空比
 *
 * @return 没有一个
 */
static inline void ledc_ll_set_duty_cycle(ledc_dev_t *hw, ledc_mode_t speed_mode, ledc_channel_t channel_num, uint32_t duty_cycle){
    hw->channel_group[speed_mode].channel[channel_num].conf1.duty_cycle = duty_cycle;
}

/**
 * @brief 设置增加或减少的步长
 *
 * @param hw 外围寄存器的起始地址
 * @param speed_mode LEDC speed_mode，高速模式或低速模式
 * @param channel_num LEDC信道索引（0-7），从LEDC_channel_t中选择
 * @param duty_scale 步长
 *
 * @return 没有一个
 */
static inline void ledc_ll_set_duty_scale(ledc_dev_t *hw, ledc_mode_t speed_mode, ledc_channel_t channel_num, uint32_t duty_scale){
    hw->channel_group[speed_mode].channel[channel_num].conf1.duty_scale = duty_scale;
}

/**
 * @brief 设置输出启用
 *
 * @param hw 外围寄存器的起始地址
 * @param speed_mode LEDC speed_mode，高速模式或低速模式
 * @param channel_num LEDC信道索引（0-7），从LEDC_channel_t中选择
 * @param sig_out_en 输出启用状态
 *
 * @return 没有一个
 */
static inline void ledc_ll_set_sig_out_en(ledc_dev_t *hw, ledc_mode_t speed_mode, ledc_channel_t channel_num, bool sig_out_en){
    hw->channel_group[speed_mode].channel[channel_num].conf0.sig_out_en = sig_out_en;
}

/**
 * @brief 设置负载启动
 *
 * @param hw 外围寄存器的起始地址
 * @param speed_mode LEDC speed_mode，高速模式或低速模式
 * @param channel_num LEDC信道索引（0-7），从LEDC_channel_t中选择
 * @param duty_start 工作开始时间
 *
 * @return 没有一个
 */
static inline void ledc_ll_set_duty_start(ledc_dev_t *hw, ledc_mode_t speed_mode, ledc_channel_t channel_num, bool duty_start){
    hw->channel_group[speed_mode].channel[channel_num].conf1.duty_start = duty_start;
}

/**
 * @brief 设置输出空闲电平
 *
 * @param hw 外围寄存器的起始地址
 * @param speed_mode LEDC speed_mode，高速模式或低速模式
 * @param channel_num LEDC信道索引（0-7），从LEDC_channel_t中选择
 * @param idle_level 输出怠速水平
 *
 * @return 没有一个
 */
static inline void ledc_ll_set_idle_level(ledc_dev_t *hw, ledc_mode_t speed_mode, ledc_channel_t channel_num, uint32_t idle_level){
    hw->channel_group[speed_mode].channel[channel_num].conf0.idle_lv = idle_level & 0x1;
}

/**
 * @brief 设置淡入结束中断启用
 *
 * @param hw 外围寄存器的起始地址
 * @param speed_mode LEDC speed_mode，高速模式或低速模式
 * @param channel_num LEDC信道索引（0-7），从LEDC_channel_t中选择
 * @param fade_end_intr_en 淡入结束中断启用状态
 *
 * @return 没有一个
 */
static inline void ledc_ll_set_fade_end_intr(ledc_dev_t *hw, ledc_mode_t speed_mode, ledc_channel_t channel_num, bool fade_end_intr_en){
    uint32_t value = hw->int_ena.val;
    uint32_t int_en_base = LEDC_DUTY_CHNG_END_LSCH0_INT_ENA_S;
    hw->int_ena.val = fade_end_intr_en ? (value | BIT(int_en_base + channel_num)) : (value & (~(BIT(int_en_base + channel_num))));
}

/**
 * @brief 获取淡入结束中断状态
 *
 * @param hw 外围寄存器的起始地址
 * @param speed_mode LEDC speed_mode，高速模式或低速模式
 * @param channel_num LEDC信道索引（0-7），从LEDC_channel_t中选择
 * @param intr_status 淡入结束中断状态
 *
 * @return 没有一个
 */
static inline void ledc_ll_get_fade_end_intr_status(ledc_dev_t *hw, ledc_mode_t speed_mode, uint32_t *intr_status){
    uint32_t value = hw->int_st.val;
    uint32_t int_en_base = LEDC_DUTY_CHNG_END_LSCH0_INT_ENA_S;
    *intr_status = (value >> int_en_base) & 0xff;
}

/**
 * @brief 清除淡入淡出结束中断状态
 *
 * @param hw 外围寄存器的起始地址
 * @param speed_mode LEDC speed_mode，高速模式或低速模式
 * @param channel_num LEDC信道索引（0-7），从LEDC_channel_t中选择
 *
 * @return 没有一个
 */
static inline void ledc_ll_clear_fade_end_intr_status(ledc_dev_t *hw, ledc_mode_t speed_mode, ledc_channel_t channel_num){
    uint32_t int_en_base = LEDC_DUTY_CHNG_END_LSCH0_INT_ENA_S;
    hw->int_clr.val = BIT(int_en_base + channel_num);
}

/**
 * @brief 设置指定频道的计时器索引
 *
 * @param hw 外围寄存器的起始地址
 * @param speed_mode LEDC speed_mode，高速模式或低速模式
 * @param channel_num LEDC信道索引（0-7），从LEDC_channel_t中选择
 * @param timer_sel LEDC计时器索引（0-3），从LEDC_timer_t中选择
 *
 * @return 没有一个
 */
static inline void ledc_ll_bind_channel_timer(ledc_dev_t *hw, ledc_mode_t speed_mode, ledc_channel_t channel_num, ledc_timer_t timer_sel){
    hw->channel_group[speed_mode].channel[channel_num].conf0.timer_sel = timer_sel;
}

/**
 * @brief 获取指定频道的计时器索引
 *
 * @param hw 外围寄存器的起始地址
 * @param speed_mode LEDC speed_mode，高速模式或低速模式
 * @param channel_num LEDC信道索引（0-7），从LEDC_channel_t中选择
 * @param timer_sel 接受LEDC计时器索引的指针
 *
 * @return 没有一个
 */
static inline void ledc_ll_get_channel_timer(ledc_dev_t *hw, ledc_mode_t speed_mode, ledc_channel_t channel_num, ledc_timer_t *timer_sel){
    *timer_sel = hw->channel_group[speed_mode].channel[channel_num].conf0.timer_sel;
}

#ifdef __cplusplus
}
#endif

