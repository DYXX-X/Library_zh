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

/*******************************************************************************
 * 注意ll不是公共api，不要在应用程序代码中使用。请参阅自述文件。在hal/include/hal/readme.md中的md
 ******************************************************************************/

#pragma once

#include <stdlib.h>
#include "soc/rtc_io_periph.h"
#include "soc/rtc_io_struct.h"
#include "soc/sens_struct.h"
#include "hal/rtc_io_types.h"
#include "hal/gpio_types.h"

#define RTCIO_LL_PIN_FUNC     0

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    RTCIO_FUNC_RTC = 0x0,         /*!< RTC模块控制的引脚。*/
    RTCIO_FUNC_DIGITAL = 0x1,     /*!< 由数字模块控制的引脚。*/
} rtcio_ll_func_t;

typedef enum {
    RTCIO_WAKEUP_DISABLE    = 0,    /*!< 禁用GPIO中断*/
    RTCIO_WAKEUP_LOW_LEVEL  = 0x4,  /*!< GPIO中断类型：输入低电平触发*/
    RTCIO_WAKEUP_HIGH_LEVEL = 0x5,  /*!< GPIO中断类型：输入高电平触发*/
} rtcio_ll_wake_type_t;

typedef enum {
    RTCIO_OUTPUT_NORMAL = 0,    /*!< RTCIO输出模式正常。*/
    RTCIO_OUTPUT_OD = 0x1,      /*!< RTCIO输出模式为漏极开路。*/
} rtcio_ll_out_mode_t;

/**
 * @brief 选择rtcio函数。
 *
 * @note 在启用极板模拟功能之前，必须选择RTC功能。
 * @param rtcio_num rtcio的索引。0~最大值（rtcio）。
 * @param func 选择引脚功能。
 */
static inline void rtcio_ll_function_select(int rtcio_num, rtcio_ll_func_t func)
{
    if (func == RTCIO_FUNC_RTC) {
        SENS.sar_io_mux_conf.iomux_clk_gate_en = 1;
        // 0:GPIO连接到数字GPIO模块。1： GPIO连接到模拟RTC模块。
        SET_PERI_REG_MASK(rtc_io_desc[rtcio_num].reg, (rtc_io_desc[rtcio_num].mux));
        //0:RTC功能1,2,3:保留
        SET_PERI_REG_BITS(rtc_io_desc[rtcio_num].reg, RTC_IO_TOUCH_PAD1_FUN_SEL_V, RTCIO_LL_PIN_FUNC, rtc_io_desc[rtcio_num].func);
    } else if (func == RTCIO_FUNC_DIGITAL) {
        CLEAR_PERI_REG_MASK(rtc_io_desc[rtcio_num].reg, (rtc_io_desc[rtcio_num].mux));
        SENS.sar_io_mux_conf.iomux_clk_gate_en = 0;
    }
}

/**
 * 启用rtcio输出。
 *
 * @param rtcio_num rtcio的索引。0~最大值（rtcio）。
 */
static inline void rtcio_ll_output_enable(int rtcio_num)
{
    RTCIO.enable_w1ts.w1ts = (1U << rtcio_num);
}

/**
 * 禁用rtcio输出。
 *
 * @param rtcio_num rtcio的索引。0~最大值（rtcio）。
 */
static inline void rtcio_ll_output_disable(int rtcio_num)
{
    RTCIO.enable_w1tc.w1tc = (1U << rtcio_num);
}

/**
 * 设置RTCIO输出电平。
 *
 * @param rtcio_num rtcio的索引。0~最大值（rtcio）。
 * @param level 0：输出低~0：输出高。
 */
static inline void rtcio_ll_set_level(int rtcio_num, uint32_t level)
{
    if (level) {
        RTCIO.out_w1ts.w1ts = (1U << rtcio_num);
    } else {
        RTCIO.out_w1tc.w1tc = (1U << rtcio_num);
    }
}

/**
 * 启用rtcio输入。
 *
 * @param rtcio_num rtcio的索引。0~最大值（rtcio）。
 */
static inline void rtcio_ll_input_enable(int rtcio_num)
{
    SET_PERI_REG_MASK(rtc_io_desc[rtcio_num].reg, rtc_io_desc[rtcio_num].ie);
}

/**
 * 禁用rtcio输入。
 *
 * @param rtcio_num rtcio的索引。0~最大值（rtcio）。
 */
static inline void rtcio_ll_input_disable(int rtcio_num)
{
    CLEAR_PERI_REG_MASK(rtc_io_desc[rtcio_num].reg, rtc_io_desc[rtcio_num].ie);
}

/**
 * 获取RTCIO输入电平。
 *
 * @param rtcio_num rtcio的索引。0~最大值（rtcio）。
 * @return 0：输入低~0：输入高。
 */
static inline uint32_t rtcio_ll_get_level(int rtcio_num)
{
    return (uint32_t)(RTCIO.in_val.in >> rtcio_num) & 0x1;
}

/**
 * @brief 设置RTC GPIO焊盘驱动能力
 *
 * @param rtcio_num rtcio的索引。0~最大值（rtcio）。
 * @param strength 衬垫的驱动能力。范围：0~3。
 */
static inline void rtcio_ll_set_drive_capability(int rtcio_num, uint32_t strength)
{
    if (rtc_io_desc[rtcio_num].drv_v) {
        SET_PERI_REG_BITS(rtc_io_desc[rtcio_num].reg, rtc_io_desc[rtcio_num].drv_v, strength, rtc_io_desc[rtcio_num].drv_s);
    }
}

/**
 * @brief 获取RTC GPIO焊盘驱动功能。
 *
 * @param rtcio_num rtcio的索引。0~最大值（rtcio）。
 * @return 衬垫的驱动能力。范围：0~3。
 */
static inline uint32_t rtcio_ll_get_drive_capability(int rtcio_num)
{
    return GET_PERI_REG_BITS2(rtc_io_desc[rtcio_num].reg, rtc_io_desc[rtcio_num].drv_v, rtc_io_desc[rtcio_num].drv_s);
}

/**
 * @brief 设置RTC GPIO焊盘输出模式。
 *
 * @param rtcio_num rtcio的索引。0~最大值（rtcio）。
 * @return 模式输出模式。
 */
static inline void rtcio_ll_output_mode_set(int rtcio_num, rtcio_ll_out_mode_t mode)
{
    RTCIO.pin[rtcio_num].pad_driver = mode;
}

/**
 * RTC GPIO上拉启用。
 *
 * @param rtcio_num rtcio的索引。0~最大值（rtcio）。
 */
static inline void rtcio_ll_pullup_enable(int rtcio_num)
{
    if (rtc_io_desc[rtcio_num].pullup) {
        SET_PERI_REG_MASK(rtc_io_desc[rtcio_num].reg, rtc_io_desc[rtcio_num].pullup);
    }
}

/**
 * RTC GPIO上拉禁用。
 *
 * @param rtcio_num rtcio的索引。0~最大值（rtcio）。
 */
static inline void rtcio_ll_pullup_disable(int rtcio_num)
{
    if (rtc_io_desc[rtcio_num].pullup) {
        CLEAR_PERI_REG_MASK(rtc_io_desc[rtcio_num].reg, rtc_io_desc[rtcio_num].pullup);
    }
}

/**
 * RTC GPIO下拉启用。
 *
 * @param rtcio_num rtcio的索引。0~最大值（rtcio）。
 */
static inline void rtcio_ll_pulldown_enable(int rtcio_num)
{
    if (rtc_io_desc[rtcio_num].pulldown) {
        SET_PERI_REG_MASK(rtc_io_desc[rtcio_num].reg, rtc_io_desc[rtcio_num].pulldown);
    }
}

/**
 * RTC GPIO下拉禁用。
 *
 * @param rtcio_num rtcio的索引。0~最大值（rtcio）。
 */
static inline void rtcio_ll_pulldown_disable(int rtcio_num)
{
    if (rtc_io_desc[rtcio_num].pulldown) {
        CLEAR_PERI_REG_MASK(rtc_io_desc[rtcio_num].reg, rtc_io_desc[rtcio_num].pulldown);
    }
}

/**
 * 启用RTC IO垫的强制保持功能。
 *
 * 启用HOLD功能将导致极板锁定当前状态，例如输入/输出启用、输入/输出值、功能、驱动强度值。当进入浅睡眠或深睡眠模式时，此功能非常有用，以防止引脚配置发生变化。
 *
 * @param rtcio_num rtcio的索引。0~最大值（rtcio）。
 */
static inline void rtcio_ll_force_hold_enable(int rtcio_num)
{
    SET_PERI_REG_MASK(RTC_CNTL_PAD_HOLD_REG, rtc_io_desc[rtcio_num].hold_force);
}

/**
 * 禁用RTC IO板上的保持功能
 *
 * @note 如果禁用键盘保持，则键盘的状态可能会在睡眠模式下更改。
 * @param rtcio_num rtcio的索引。0~最大值（rtcio）。
 */
static inline void rtcio_ll_force_hold_disable(int rtcio_num)
{
    CLEAR_PERI_REG_MASK(RTC_CNTL_PAD_HOLD_REG, rtc_io_desc[rtcio_num].hold_force);
}

/**
 * 启用RTC IO垫的强制保持功能。
 *
 * 启用HOLD功能将导致极板锁定当前状态，例如输入/输出启用、输入/输出值、功能、驱动强度值。当进入浅睡眠或深睡眠模式时，此功能非常有用，以防止引脚配置发生变化。
 *
 * @param rtcio_num rtcio的索引。0~最大值（rtcio）。
 */
static inline void rtcio_ll_force_hold_all(void)
{
    SET_PERI_REG_MASK(RTC_CNTL_PWC_REG, RTC_CNTL_PAD_FORCE_HOLD_M);
}

/**
 * 禁用RTC IO板上的保持功能
 *
 * @note 如果禁用键盘保持，则键盘的状态可能会在睡眠模式下更改。
 * @param rtcio_num rtcio的索引。0~最大值（rtcio）。
 */
static inline void rtcio_ll_force_unhold_all(void)
{
    CLEAR_PERI_REG_MASK(RTC_CNTL_PWC_REG, RTC_CNTL_PAD_FORCE_HOLD_M);
}

/**
 * 启用唤醒功能，并为rtcio从浅睡眠状态设置唤醒类型。
 *
 * @param rtcio_num rtcio的索引。0~最大值（rtcio）。
 * @param type  在高电平或低电平唤醒。
 */
static inline void rtcio_ll_wakeup_enable(int rtcio_num, rtcio_ll_wake_type_t type)
{
    SENS.sar_io_mux_conf.iomux_clk_gate_en = 1;
    RTCIO.pin[rtcio_num].wakeup_enable = 0x1;
    RTCIO.pin[rtcio_num].int_type = type;
}

/**
 * 禁用rtcio的轻睡眠状态唤醒功能。
 *
 * @param rtcio_num rtcio的索引。0~最大值（rtcio）。
 */
static inline void rtcio_ll_wakeup_disable(int rtcio_num)
{
    SENS.sar_io_mux_conf.iomux_clk_gate_en = 0;
    RTCIO.pin[rtcio_num].wakeup_enable = 0;
    RTCIO.pin[rtcio_num].int_type = RTCIO_WAKEUP_DISABLE;
}

/**
 * 在深度睡眠中启用rtc io输出。
 *
 * @param rtcio_num rtcio的索引。0~最大值（rtcio）。
 */
static inline void rtcio_ll_enable_output_in_sleep(gpio_num_t gpio_num)
{
    if (rtc_io_desc[gpio_num].slpoe) {
        SET_PERI_REG_MASK(rtc_io_desc[gpio_num].reg, rtc_io_desc[gpio_num].slpoe);
    }
}

/**
 * 在深度睡眠中禁用rtc io输出。
 *
 * @param rtcio_num rtcio的索引。0~最大值（rtcio）。
 */
static inline void rtcio_ll_in_sleep_disable_output(gpio_num_t gpio_num)
{
    if (rtc_io_desc[gpio_num].slpoe) {
        CLEAR_PERI_REG_MASK(rtc_io_desc[gpio_num].reg, rtc_io_desc[gpio_num].slpoe);
    }
}

/**
 * 在深度睡眠中启用rtc io输入。
 *
 * @param rtcio_num rtcio的索引。0~最大值（rtcio）。
 */
static inline void rtcio_ll_in_sleep_enable_input(gpio_num_t gpio_num)
{
    SET_PERI_REG_MASK(rtc_io_desc[gpio_num].reg, rtc_io_desc[gpio_num].slpie);
}

/**
 * 在深度睡眠中禁用rtc io输入。
 *
 * @param rtcio_num rtcio的索引。0~最大值（rtcio）。
 */
static inline void rtcio_ll_in_sleep_disable_input(gpio_num_t gpio_num)
{
    CLEAR_PERI_REG_MASK(rtc_io_desc[gpio_num].reg, rtc_io_desc[gpio_num].slpie);
}

/**
 * 启用rtc io使另一个设置保持深度睡眠。
 *
 * @param rtcio_num rtcio的索引。0~最大值（rtcio）。
 */
static inline void rtcio_ll_enable_sleep_setting(gpio_num_t gpio_num)
{
    SET_PERI_REG_MASK(rtc_io_desc[gpio_num].reg, rtc_io_desc[gpio_num].slpsel);
}

/**
 * 禁用rtc io使另一个设置保持深度睡眠。（默认）
 *
 * @param rtcio_num rtcio的索引。0~最大值（rtcio）。
 */
static inline void rtcio_ll_disable_sleep_setting(gpio_num_t gpio_num)
{
    CLEAR_PERI_REG_MASK(rtc_io_desc[gpio_num].reg, rtc_io_desc[gpio_num].slpsel);
}

static inline void rtcio_ll_ext0_set_wakeup_pin(int rtcio_num, int level)
{
    REG_SET_FIELD(RTC_IO_EXT_WAKEUP0_REG, RTC_IO_EXT_WAKEUP0_SEL, rtcio_num);
    // 设置将触发唤醒的级别
    SET_PERI_REG_BITS(RTC_CNTL_EXT_WAKEUP_CONF_REG, 0x1,
            level , RTC_CNTL_EXT_WAKEUP0_LV_S);
}

#ifdef __cplusplus
}
#endif

