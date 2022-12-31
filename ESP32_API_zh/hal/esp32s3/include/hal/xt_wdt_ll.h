/*
 * SPDX文件版权文本：2021浓缩咖啡系统（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */

// xtal32k WDT寄存器操作的LL层。
// 注意，该层中的大多数寄存器操作都是非原子操作。

#pragma once

#include <stdbool.h>
#include "soc/rtc_cntl_periph.h"

#ifdef __cplusplus
extern "C" {
#endif

#define XT_WDT_LL_XTAL32_DEAD_INTR_MASK RTC_CNTL_XTAL32K_DEAD_INT_ST_M

/**
 * @brief 启用XT_WDT
 *
 * @param hw 外围寄存器的起始地址。
 */
inline void xt_wdt_ll_enable(rtc_cntl_dev_t *hw, bool enable)
{
    hw->ext_xtl_conf.xtal32k_wdt_en = enable;
}

/**
 * @brief 检查XT_WDT是否已启用
 *
 * @param hw 外围寄存器的起始地址。
 * @return 如果启用XT WDT，则为True
 */
inline bool xt_wdt_ll_check_if_enabled(rtc_cntl_dev_t *hw)
{
    return (hw->ext_xtl_conf.xtal32k_wdt_en) ? true : false;
}

/**
 * @brief 设置看门狗超时值
 *
 * @param hw 外围寄存器的起始地址。
 * @param timeout RTC_CLK周期中的超时值
 */
inline void xt_wdt_ll_set_timeout(rtc_cntl_dev_t *hw, uint8_t timeout)
{
    hw->xtal32k_conf.xtal32k_wdt_timeout = timeout;
}


/**
 * @brief 重置XT_WDT
 *
 * @param hw 外围寄存器的起始地址。
 */
inline void xt_wdt_ll_reset(rtc_cntl_dev_t *hw)
{
    hw->ext_xtl_conf.xtal32k_wdt_reset = 1;
    hw->ext_xtl_conf.xtal32k_wdt_reset = 0;
}


/**
 * @brief 设置备份时钟值
 *
 * @param hw 外围寄存器的起始地址。
 * @param backup_clk_val 备份时钟值，定义见TRM
 */
inline void xt_wdt_ll_set_backup_clk_factor(rtc_cntl_dev_t *hw, uint32_t backup_clk_val)
{
    hw->xtal32k_clk_factor = backup_clk_val;
}

/**
 * @brief 启用自动备份时钟功能
 *
 * @param hw 外围寄存器的起始地址。
 * @param enable True-启用，False-禁用
 */
inline void xt_wdt_ll_auto_backup_enable(rtc_cntl_dev_t *hw, bool enable)
{
    hw->ext_xtl_conf.xtal32k_auto_backup = enable;
}

/**
 * @brief 启用超时中断
 *
 * @param hw 外围寄存器的起始地址。
 * @param enable True-启用，False-禁用
 */
inline void xt_wdt_ll_intr_enable(rtc_cntl_dev_t *hw, bool enable)
{
    hw->int_ena.rtc_xtal32k_dead = enable;
}

#ifdef __cplusplus
}
#endif

