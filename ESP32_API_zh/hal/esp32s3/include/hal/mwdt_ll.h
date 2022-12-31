// 版权所有2015-2019 Espressif Systems（上海）私人有限公司
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

// 定时器组寄存器操作的LL层。
// 注意，该层中的大多数寄存器操作都是非原子操作。

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>
#include "hal/misc.h"
#include "soc/timer_periph.h"
#include "soc/timer_group_struct.h"
#include "hal/wdt_types.h"
#include "esp_attr.h"

/* 需要写入MWDT_LL_WKEY以启用wdt寄存器的值*/
#define MWDT_LL_WKEY_VALUE 0x50D83AA1

/* MWDT_LL_STGx的可能值*/
#define MWDT_LL_STG_SEL_OFF 0
#define MWDT_LL_STG_SEL_INT 1
#define MWDT_LL_STG_SEL_RESET_CPU 2
#define MWDT_LL_STG_SEL_RESET_SYSTEM 3

/* MWDT_LL_CPU_REST_LENGTH和MWDT_LL-SYS_RESET_LENGTH的可能值*/
#define MWDT_LL_RESET_LENGTH_100_NS    0
#define MWDT_LL_RESET_LENGTH_200_NS    1
#define MWDT_LL_RESET_LENGTH_300_NS    2
#define MWDT_LL_RESET_LENGTH_400_NS    3
#define MWDT_LL_RESET_LENGTH_500_NS    4
#define MWDT_LL_RESET_LENGTH_800_NS    5
#define MWDT_LL_RESET_LENGTH_1600_NS   6
#define MWDT_LL_RESET_LENGTH_3200_NS   7

//类型检查wdt_stage_action_t
_Static_assert(WDT_STAGE_ACTION_OFF == MWDT_LL_STG_SEL_OFF, "Add mapping to LL watchdog timeout behavior, since it's no longer naturally compatible with wdt_stage_action_t");
_Static_assert(WDT_STAGE_ACTION_INT == MWDT_LL_STG_SEL_INT, "Add mapping to LL watchdog timeout behavior, since it's no longer naturally compatible with wdt_stage_action_t");
_Static_assert(WDT_STAGE_ACTION_RESET_CPU == MWDT_LL_STG_SEL_RESET_CPU, "Add mapping to LL watchdog timeout behavior, since it's no longer naturally compatible with wdt_stage_action_t");
_Static_assert(WDT_STAGE_ACTION_RESET_SYSTEM == MWDT_LL_STG_SEL_RESET_SYSTEM, "Add mapping to LL watchdog timeout behavior, since it's no longer naturally compatible with wdt_stage_action_t");
//类型检查wdt_reset_sig_length_t
_Static_assert(WDT_RESET_SIG_LENGTH_100ns == MWDT_LL_RESET_LENGTH_100_NS, "Add mapping to LL watchdog timeout behavior, since it's no longer naturally compatible with wdt_reset_sig_length_t");
_Static_assert(WDT_RESET_SIG_LENGTH_200ns == MWDT_LL_RESET_LENGTH_200_NS, "Add mapping to LL watchdog timeout behavior, since it's no longer naturally compatible with wdt_reset_sig_length_t");
_Static_assert(WDT_RESET_SIG_LENGTH_300ns == MWDT_LL_RESET_LENGTH_300_NS, "Add mapping to LL watchdog timeout behavior, since it's no longer naturally compatible with wdt_reset_sig_length_t");
_Static_assert(WDT_RESET_SIG_LENGTH_400ns == MWDT_LL_RESET_LENGTH_400_NS, "Add mapping to LL watchdog timeout behavior, since it's no longer naturally compatible with wdt_reset_sig_length_t");
_Static_assert(WDT_RESET_SIG_LENGTH_500ns == MWDT_LL_RESET_LENGTH_500_NS, "Add mapping to LL watchdog timeout behavior, since it's no longer naturally compatible with wdt_reset_sig_length_t");
_Static_assert(WDT_RESET_SIG_LENGTH_800ns == MWDT_LL_RESET_LENGTH_800_NS, "Add mapping to LL watchdog timeout behavior, since it's no longer naturally compatible with wdt_reset_sig_length_t");
_Static_assert(WDT_RESET_SIG_LENGTH_1_6us == MWDT_LL_RESET_LENGTH_1600_NS, "Add mapping to LL watchdog timeout behavior, since it's no longer naturally compatible with wdt_reset_sig_length_t");
_Static_assert(WDT_RESET_SIG_LENGTH_3_2us == MWDT_LL_RESET_LENGTH_3200_NS, "Add mapping to LL watchdog timeout behavior, since it's no longer naturally compatible with wdt_reset_sig_length_t");

/**
 * @brief 启用MWDT
 *
 * @param hw 外围寄存器的起始地址。
 */
FORCE_INLINE_ATTR void mwdt_ll_enable(timg_dev_t *hw)
{
    hw->wdtconfig0.wdt_en = 1;
}

/**
 * @brief 禁用MWDT
 *
 * @param hw 外围寄存器的起始地址。
 * @note 此功能不会禁用闪存启动模式。因此，如果使用此功能禁用MWDT，则如果同时启用闪存引导模式，仍可能发生超时。
 */
FORCE_INLINE_ATTR void mwdt_ll_disable(timg_dev_t *hw)
{
    hw->wdtconfig0.wdt_en = 0;
}

/**
 * 检查MWDT是否已启用
 *
 * @param hw 外围寄存器的起始地址。
 * @return 如果MWDT已启用，则为True，否则为false
 */
FORCE_INLINE_ATTR bool mwdt_ll_check_if_enabled(timg_dev_t *hw)
{
    return (hw->wdtconfig0.wdt_en) ? true : false;
}

/**
 * @brief 配置MWDT的特定阶段
 *
 * @param hw 外围寄存器的起始地址。
 * @param stage 要配置的阶段
 * @param timeout 阶段要超时的计时器滴答数
 * @param behavior 舞台超时时要采取什么行动
 */
FORCE_INLINE_ATTR void mwdt_ll_config_stage(timg_dev_t *hw, wdt_stage_t stage, uint32_t timeout, wdt_stage_action_t behavior)
{
    switch (stage) {
    case WDT_STAGE0:
        hw->wdtconfig0.wdt_stg0 = behavior;
        hw->wdtconfig2.wdt_stg0_hold = timeout;
        break;
    case WDT_STAGE1:
        hw->wdtconfig0.wdt_stg1 = behavior;
        hw->wdtconfig3.wdt_stg1_hold = timeout;
        break;
    case WDT_STAGE2:
        hw->wdtconfig0.wdt_stg2 = behavior;
        hw->wdtconfig4.wdt_stg2_hold = timeout;
        break;
    case WDT_STAGE3:
        hw->wdtconfig0.wdt_stg3 = behavior;
        hw->wdtconfig5.wdt_stg3_hold = timeout;
        break;
    default:
        break;
    }
}

/**
 * @brief 禁用MWDT的特定阶段
 *
 * @param hw 外围寄存器的起始地址。
 * @param stage 要禁用的阶段
 */
FORCE_INLINE_ATTR void mwdt_ll_disable_stage(timg_dev_t *hw, uint32_t stage)
{
    switch (stage) {
    case WDT_STAGE0:
        hw->wdtconfig0.wdt_stg0 = WDT_STAGE_ACTION_OFF;
        break;
    case WDT_STAGE1:
        hw->wdtconfig0.wdt_stg1 = WDT_STAGE_ACTION_OFF;
        break;
    case WDT_STAGE2:
        hw->wdtconfig0.wdt_stg2 = WDT_STAGE_ACTION_OFF;
        break;
    case WDT_STAGE3:
        hw->wdtconfig0.wdt_stg3 = WDT_STAGE_ACTION_OFF;
        break;
    default:
        break;
    }
}

/**
 * @brief 启用或禁用MWDT边缘中断
 *
 * @param hw 外围寄存器的起始地址。
 * @param enable 是否启用边缘中断
 */
FORCE_INLINE_ATTR void mwdt_ll_set_edge_intr(timg_dev_t *hw, bool enable)
{
}

/**
 * @brief 启用或禁用MWDT级中断
 *
 * @param hw 外围寄存器的起始地址。
 * @param enable 是否启用电平中断
 */
FORCE_INLINE_ATTR void mwdt_ll_set_level_intr(timg_dev_t *hw, bool enable)
{
    hw->int_ena_timers.wdt_int_ena = enable;
}

/**
 * @brief 设置CPU重置操作的长度
 *
 * @param hw 外围寄存器的起始地址。
 * @param length CPU复位信号长度
 */
FORCE_INLINE_ATTR void mwdt_ll_set_cpu_reset_length(timg_dev_t *hw, wdt_reset_sig_length_t length)
{
    hw->wdtconfig0.wdt_cpu_reset_length = length;
}

/**
 * @brief 设置系统重置操作的长度
 *
 * @param hw 外围寄存器的起始地址。
 * @param length 系统复位信号长度
 */
FORCE_INLINE_ATTR void mwdt_ll_set_sys_reset_length(timg_dev_t *hw, wdt_reset_sig_length_t length)
{
    hw->wdtconfig0.wdt_sys_reset_length = length;
}

/**
 * @brief 启用/禁用MWDT闪存引导模式。
 *
 * @param hw 外围寄存器的起始地址。
 * @param enable True表示启用WDT闪存引导模式，false表示禁用WDT闪存启动模式。
 *
 * @note Flashboot模式是独立的，如果WDT的启用位设置为0，则会触发WDT超时事件。TG0的Flashboot模式会在Flashboot上自动启用，并在flashbooting完成时由软件禁用。
 */
FORCE_INLINE_ATTR void mwdt_ll_set_flashboot_en(timg_dev_t *hw, bool enable)
{
    hw->wdtconfig0.wdt_flashboot_mod_en = (enable) ? 1 : 0;
}

/**
 * @brief 设置MWDT的时钟预分频器
 *
 * @param hw 外围寄存器的起始地址。
 * @param prescaler 预缩放值介于1到65535之间
 */
FORCE_INLINE_ATTR void mwdt_ll_set_prescaler(timg_dev_t *hw, uint32_t prescaler)
{
    HAL_FORCE_MODIFY_U32_REG_FIELD(hw->wdtconfig1, wdt_clk_prescale, prescaler);
}

/**
 * @brief 向MWDT馈电
 *
 * 重置当前计时器计数和当前阶段。
 *
 * @param hw 外围寄存器的起始地址。
 */
FORCE_INLINE_ATTR void mwdt_ll_feed(timg_dev_t *hw)
{
    hw->wdtfeed.wdt_feed = 1;
}

/**
 * @brief 启用MWDT寄存器的写保护
 *
 * 锁定MWDT将防止MWDT的任何寄存器被修改
 *
 * @param hw 外围寄存器的起始地址。
 */
FORCE_INLINE_ATTR void mwdt_ll_write_protect_enable(timg_dev_t *hw)
{
    hw->wdtwprotect.wdt_wkey = 0;
}

/**
 * @brief 禁用MWDT寄存器的写保护
 *
 * @param hw 外围寄存器的起始地址。
 */
FORCE_INLINE_ATTR void mwdt_ll_write_protect_disable(timg_dev_t *hw)
{
    hw->wdtwprotect.wdt_wkey = MWDT_LL_WKEY_VALUE;
}

/**
 * @brief 清除MWDT中断状态。
 *
 * @param hw 外围寄存器的起始地址。
 */
FORCE_INLINE_ATTR void mwdt_ll_clear_intr_status(timg_dev_t *hw)
{
    hw->int_clr_timers.wdt_int_clr = 1;
}

/**
 * @brief 设置MWDT中断的中断启用位。
 *
 * @param hw 外围寄存器的起始地址。
 * @param enable 是否启用MWDT中断
 */
FORCE_INLINE_ATTR void mwdt_ll_set_intr_enable(timg_dev_t *hw, bool enable)
{
    hw->int_ena_timers.wdt_int_ena = (enable) ? 1 : 0;
}

#ifdef __cplusplus
}
#endif

