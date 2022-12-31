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

#include <stdlib.h>
#include <stdbool.h>
#include "hal/wdt_types.h"
#include "soc/rtc_cntl_periph.h"
#include "soc/rtc_cntl_struct.h"
#include "soc/efuse_reg.h"
#include "esp_attr.h"

/* 需要写入RTC_CNTL_WDT_WKEY以启用WDT寄存器的值*/
#define RWDT_LL_WDT_WKEY_VALUE 0x50D83AA1


/* 阶段动作选择值*/
#define RWDT_LL_STG_SEL_OFF             0
#define RWDT_LL_STG_SEL_INT             1
#define RWDT_LL_STG_SEL_RESET_CPU       2
#define RWDT_LL_STG_SEL_RESET_SYSTEM    3
#define RWDT_LL_STG_SEL_RESET_RTC       4

/* RTC_CNTL_WDT_CPU_REST_LENGTH和RTC_CNTL-WDT_SYS_RESET_LENGTH的可能值*/
#define RWDT_LL_RESET_LENGTH_100_NS    0
#define RWDT_LL_RESET_LENGTH_200_NS    1
#define RWDT_LL_RESET_LENGTH_300_NS    2
#define RWDT_LL_RESET_LENGTH_400_NS    3
#define RWDT_LL_RESET_LENGTH_500_NS    4
#define RWDT_LL_RESET_LENGTH_800_NS    5
#define RWDT_LL_RESET_LENGTH_1600_NS   6
#define RWDT_LL_RESET_LENGTH_3200_NS   7

//类型检查wdt_stage_action_t
_Static_assert(WDT_STAGE_ACTION_OFF == RWDT_LL_STG_SEL_OFF, "Add mapping to LL watchdog timeout behavior, since it's no longer naturally compatible with wdt_stage_action_t");
_Static_assert(WDT_STAGE_ACTION_INT == RWDT_LL_STG_SEL_INT, "Add mapping to LL watchdog timeout behavior, since it's no longer naturally compatible with wdt_stage_action_t");
_Static_assert(WDT_STAGE_ACTION_RESET_CPU == RWDT_LL_STG_SEL_RESET_CPU, "Add mapping to LL watchdog timeout behavior, since it's no longer naturally compatible with wdt_stage_action_t");
_Static_assert(WDT_STAGE_ACTION_RESET_SYSTEM == RWDT_LL_STG_SEL_RESET_SYSTEM, "Add mapping to LL watchdog timeout behavior, since it's no longer naturally compatible with wdt_stage_action_t");
_Static_assert(WDT_STAGE_ACTION_RESET_RTC == RWDT_LL_STG_SEL_RESET_RTC, "Add mapping to LL watchdog timeout behavior, since it's no longer naturally compatible with wdt_stage_action_t");
//类型检查wdt_reset_sig_length_t
_Static_assert(WDT_RESET_SIG_LENGTH_100ns == RWDT_LL_RESET_LENGTH_100_NS, "Add mapping to LL watchdog timeout behavior, since it's no longer naturally compatible with wdt_reset_sig_length_t");
_Static_assert(WDT_RESET_SIG_LENGTH_200ns == RWDT_LL_RESET_LENGTH_200_NS, "Add mapping to LL watchdog timeout behavior, since it's no longer naturally compatible with wdt_reset_sig_length_t");
_Static_assert(WDT_RESET_SIG_LENGTH_300ns == RWDT_LL_RESET_LENGTH_300_NS, "Add mapping to LL watchdog timeout behavior, since it's no longer naturally compatible with wdt_reset_sig_length_t");
_Static_assert(WDT_RESET_SIG_LENGTH_400ns == RWDT_LL_RESET_LENGTH_400_NS, "Add mapping to LL watchdog timeout behavior, since it's no longer naturally compatible with wdt_reset_sig_length_t");
_Static_assert(WDT_RESET_SIG_LENGTH_500ns == RWDT_LL_RESET_LENGTH_500_NS, "Add mapping to LL watchdog timeout behavior, since it's no longer naturally compatible with wdt_reset_sig_length_t");
_Static_assert(WDT_RESET_SIG_LENGTH_800ns == RWDT_LL_RESET_LENGTH_800_NS, "Add mapping to LL watchdog timeout behavior, since it's no longer naturally compatible with wdt_reset_sig_length_t");
_Static_assert(WDT_RESET_SIG_LENGTH_1_6us == RWDT_LL_RESET_LENGTH_1600_NS, "Add mapping to LL watchdog timeout behavior, since it's no longer naturally compatible with wdt_reset_sig_length_t");
_Static_assert(WDT_RESET_SIG_LENGTH_3_2us == RWDT_LL_RESET_LENGTH_3200_NS, "Add mapping to LL watchdog timeout behavior, since it's no longer naturally compatible with wdt_reset_sig_length_t");

/**
 * @brief 启用RWDT
 *
 * @param hw 外围寄存器的起始地址。
 */
FORCE_INLINE_ATTR void rwdt_ll_enable(rtc_cntl_dev_t *hw)
{
    hw->wdt_config0.en = 1;
}

/**
 * @brief 禁用RWDT
 *
 * @param hw 外围寄存器的起始地址。
 * @note 此功能不会禁用闪存启动模式。因此，如果使用此功能禁用MWDT，则如果同时启用闪存引导模式，仍可能发生超时。
 */
FORCE_INLINE_ATTR void rwdt_ll_disable(rtc_cntl_dev_t *hw)
{
    hw->wdt_config0.en = 0;
}

/**
 * @brief 检查RWDT是否已启用
 *
 * @param hw 外围寄存器的起始地址。
 * @return 如果启用RTC WDT，则为True
 */
FORCE_INLINE_ATTR bool rwdt_ll_check_if_enabled(rtc_cntl_dev_t *hw)
{
    return (hw->wdt_config0.en) ? true : false;
}

/**
 * @brief 配置RWDT的特定阶段
 *
 * @param hw 外围寄存器的起始地址。
 * @param stage 要配置的阶段
 * @param timeout 阶段超时的计时器滴答数（请参阅注释）。
 * @param behavior 舞台超时时要采取什么行动
 *
 * @note RWDT阶段0超时寄存器的值是特殊的，因为隐式乘数应用于该值以产生有效的超时标记值。乘数取决于EFuse值。因此，在配置阶段0时，超时参数的有效值为：
 *       -如果Efuse值为0，[2,2*UINT32_MAX]之间的任何偶数
 *       -如果Efuse值为1，则[4,4*UINT32_MAX]之间的4的任意倍数
 *       -如果Efuse值为2，则[8,8*UINT32_MAX]之间的8的任意倍数
 *       -如果Efuse值为3，则[16,16*UINT32_MAX]之间的16的任意倍数
 */
FORCE_INLINE_ATTR void rwdt_ll_config_stage(rtc_cntl_dev_t *hw, wdt_stage_t stage, uint32_t timeout_ticks, wdt_stage_action_t behavior)
{
    switch (stage) {
    case WDT_STAGE0:
        hw->wdt_config0.stg0 = behavior;
        hw->wdt_config1 = timeout_ticks >> 1;
        break;
    case WDT_STAGE1:
        hw->wdt_config0.stg1 = behavior;
        hw->wdt_config2 = timeout_ticks;
        break;
    case WDT_STAGE2:
        hw->wdt_config0.stg2 = behavior;
        hw->wdt_config3 = timeout_ticks;
        break;
    case WDT_STAGE3:
        hw->wdt_config0.stg3 = behavior;
        hw->wdt_config4 = timeout_ticks;
        break;
    default:
        abort();
    }
}

/**
 * @brief 禁用RWDT的特定阶段
 *
 * @param hw 外围寄存器的起始地址。
 * @param stage 要禁用的阶段
 */
FORCE_INLINE_ATTR void rwdt_ll_disable_stage(rtc_cntl_dev_t *hw, wdt_stage_t stage)
{
    switch (stage) {
    case WDT_STAGE0:
        hw->wdt_config0.stg0 = WDT_STAGE_ACTION_OFF;
        break;
    case WDT_STAGE1:
        hw->wdt_config0.stg1 = WDT_STAGE_ACTION_OFF;
        break;
    case WDT_STAGE2:
        hw->wdt_config0.stg2 = WDT_STAGE_ACTION_OFF;
        break;
    case WDT_STAGE3:
        hw->wdt_config0.stg3 = WDT_STAGE_ACTION_OFF;
        break;
    default:
        abort();
    }
}

/**
 * @brief 设置CPU重置操作的长度
 *
 * @param hw 外围寄存器的起始地址。
 * @param length CPU复位信号长度
 */
FORCE_INLINE_ATTR void rwdt_ll_set_cpu_reset_length(rtc_cntl_dev_t *hw, wdt_reset_sig_length_t length)
{
    hw->wdt_config0.cpu_reset_length = length;
}

/**
 * @brief 设置系统重置操作的长度
 *
 * @param hw 外围寄存器的起始地址。
 * @param length 系统复位信号长度
 */
FORCE_INLINE_ATTR void rwdt_ll_set_sys_reset_length(rtc_cntl_dev_t *hw, wdt_reset_sig_length_t length)
{
    hw->wdt_config0.sys_reset_length = length;
}

/**
 * @brief 启用/禁用RWDT闪存引导模式。
 *
 * @param hw 外围寄存器的起始地址。
 * @param enable True表示启用RWDT闪存启动模式，false表示禁用RWDT闪存引导模式。
 *
 * @note 闪存引导模式是独立的，如果WDT的启用位设置为0，则会触发WDT超时事件。RWDT的闪存引导模式在闪存引导时自动启用，当闪存引导完成时，软件应禁用该模式。
 */
FORCE_INLINE_ATTR void rwdt_ll_set_flashboot_en(rtc_cntl_dev_t *hw, bool enable)
{
    hw->wdt_config0.flashboot_mod_en = (enable) ? 1 : 0;
}

/**
 * @brief 启用/禁用要在WDT_STAGE_ACTION_reset_CPU上重置的CPU0
 *
 * @param hw 外围寄存器的起始地址。
 * @param enable True表示启用CPU0复位，false表示禁用。
 */
FORCE_INLINE_ATTR void rwdt_ll_set_procpu_reset_en(rtc_cntl_dev_t *hw, bool enable)
{
    hw->wdt_config0.procpu_reset_en = (enable) ? 1 : 0;
}

/**
 * @brief 启用/禁用要在WDT_STAGE_ACTION_reset_CPU上重置的CPU1
 *
 * @param hw 外围寄存器的起始地址。
 * @param enable True表示启用CPU1复位，false表示禁用。
 */
FORCE_INLINE_ATTR void rwdt_ll_set_appcpu_reset_en(rtc_cntl_dev_t *hw, bool enable)
{
    hw->wdt_config0.appcpu_reset_en = (enable) ? 1 : 0;
}

/**
 * @brief 在休眠功能期间启用/禁用RWDT暂停
 *
 * @param hw 外围寄存器的起始地址。
 * @param enable True表示启用，false表示禁用。
 */
FORCE_INLINE_ATTR void rwdt_ll_set_pause_in_sleep_en(rtc_cntl_dev_t *hw, bool enable)
{
    hw->wdt_config0.pause_in_slp = (enable) ? 1 : 0;
}

/**
 * @brief RWDT超时时启用/禁用芯片复位。
 *
 * 芯片重置也重置芯片的模拟部分。它将显示为POWERON重置，而不是RTC重置。
 *
 * @param hw 外围寄存器的起始地址。
 * @param enable True表示启用，false表示禁用。
 */
FORCE_INLINE_ATTR void rwdt_ll_set_chip_reset_en(rtc_cntl_dev_t *hw, bool enable)
{
    hw->wdt_config0.chip_reset_en = (enable) ? 1 : 0;
}

/**
 * @brief 设置芯片复位信号的宽度
 *
 * @param hw 外围寄存器的起始地址。
 * @param width 以RTC_SLOW_CLK周期数表示的芯片复位信号宽度
 */
FORCE_INLINE_ATTR void rwdt_ll_set_chip_reset_width(rtc_cntl_dev_t *hw, uint32_t width)
{
    HAL_FORCE_MODIFY_U32_REG_FIELD(hw->wdt_config0, chip_reset_width, width);
}

/**
 * @brief 给RWDT供电
 *
 * 重置当前计时器计数和当前阶段。
 *
 * @param hw 外围寄存器的起始地址。
 */
FORCE_INLINE_ATTR void rwdt_ll_feed(rtc_cntl_dev_t *hw)
{
    hw->wdt_feed.feed = 1;
}

/**
 * @brief 启用RWDT寄存器的写保护
 *
 * @param hw 外围寄存器的起始地址。
 */
FORCE_INLINE_ATTR void rwdt_ll_write_protect_enable(rtc_cntl_dev_t *hw)
{
    hw->wdt_wprotect = 0;
}

/**
 * @brief 禁用RWDT寄存器的写保护
 *
 * @param hw 外围寄存器的起始地址。
 */
FORCE_INLINE_ATTR void rwdt_ll_write_protect_disable(rtc_cntl_dev_t *hw)
{
    hw->wdt_wprotect = RWDT_LL_WDT_WKEY_VALUE;
}

/**
 * @brief 启用RWDT中断。
 *
 * @param hw 外围寄存器的起始地址。
 * @param enable True表示启用RWDT中断，false表示禁用。
 */
FORCE_INLINE_ATTR void rwdt_ll_set_intr_enable(rtc_cntl_dev_t *hw, bool enable)
{
    hw->int_ena.rtc_wdt = (enable) ? 1 : 0;
}

/**
 * @brief 检查RWDT中断是否已触发
 *
 * @param hw 外围寄存器的起始地址。
 * @return 如果触发了RWDT中断，则为True
 */
FORCE_INLINE_ATTR bool rwdt_ll_check_intr_status(rtc_cntl_dev_t *hw)
{
    return (hw->int_st.rtc_wdt) ? true : false;
}

/**
 * @brief 清除RWDT中断状态。
 *
 * @param hw 外围寄存器的起始地址。
 */
FORCE_INLINE_ATTR void rwdt_ll_clear_intr_status(rtc_cntl_dev_t *hw)
{
    hw->int_clr.rtc_wdt = 1;
}

#ifdef __cplusplus
}
#endif

