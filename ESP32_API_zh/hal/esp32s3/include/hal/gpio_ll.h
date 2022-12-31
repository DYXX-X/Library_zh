/*
 * SPDX文件版权文本：2015-2021浓缩咖啡系统（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */

/*******************************************************************************
 * 注意：hal不是公共api，不要在应用程序代码中使用。请参阅自述文件。在hal/include/hal/readme.md中的md
 ******************************************************************************/

// ESP32-S3 GPIO寄存器操作的LL层

#pragma once

#include "soc/soc.h"
#include "soc/gpio_periph.h"
#include "soc/rtc_cntl_reg.h"
#include "soc/rtc_io_reg.h"
#include "soc/usb_serial_jtag_reg.h"
#include "hal/gpio_types.h"
#include "soc/gpio_struct.h"

#ifdef __cplusplus
extern "C" {
#endif

// 通过提供GPIO num获取GPIO硬件实例
#define GPIO_LL_GET_HW(num) (((num) == 0) ? (&GPIO) : NULL)

// 在ESP32S3上，pro cpu和app cpu共享相同的中断启用位
#define GPIO_LL_INTR_ENA      (BIT(0))
#define GPIO_LL_NMI_INTR_ENA  (BIT(1))

/**
  * @brief 启用GPIO上拉。
  *
  * @param hw 外围GPIO硬件实例地址。
  * @param gpio_num GPIO编号
  */
static inline void gpio_ll_pullup_en(gpio_dev_t *hw, gpio_num_t gpio_num)
{
    REG_SET_BIT(GPIO_PIN_MUX_REG[gpio_num], FUN_PU);
}

/**
  * @brief 禁用GPIO上的上拉。
  *
  * @param hw 外围GPIO硬件实例地址。
  * @param gpio_num GPIO编号
  */
static inline void gpio_ll_pullup_dis(gpio_dev_t *hw, gpio_num_t gpio_num)
{
    REG_CLR_BIT(GPIO_PIN_MUX_REG[gpio_num], FUN_PU);
}

/**
  * @brief 启用GPIO上的下拉。
  *
  * @param hw 外围GPIO硬件实例地址。
  * @param gpio_num GPIO编号
  */
static inline void gpio_ll_pulldown_en(gpio_dev_t *hw, gpio_num_t gpio_num)
{
    REG_SET_BIT(GPIO_PIN_MUX_REG[gpio_num], FUN_PD);
}

/**
  * @brief 禁用GPIO上的下拉。
  *
  * @param hw 外围GPIO硬件实例地址。
  * @param gpio_num GPIO编号
  */
static inline void gpio_ll_pulldown_dis(gpio_dev_t *hw, gpio_num_t gpio_num)
{
    REG_CLR_BIT(GPIO_PIN_MUX_REG[gpio_num], FUN_PD);
}

/**
 * @brief  GPIO设置中断触发类型
 *
 * @param  hw 外围GPIO硬件实例地址。
 * @param  gpio_num GPIO编号。如果要设置触发类型，例如GPIO16，gpio_num应为gpio_num_16（16）；
 * @param  intr_type 中断类型，从gpio_int_type_t中选择
 */
static inline void gpio_ll_set_intr_type(gpio_dev_t *hw, gpio_num_t gpio_num, gpio_int_type_t intr_type)
{
    hw->pin[gpio_num].int_type = intr_type;
}

/**
  * @brief 获取GPIO中断状态
  *
  * @param hw 外围GPIO硬件实例地址。
  * @param core_id 中断核心id
  * @param status 中断状态
  */
static inline void gpio_ll_get_intr_status(gpio_dev_t *hw, uint32_t core_id, uint32_t *status)
{
    // 在ESP32S3上，pcpu_int寄存器表示两个内核上的GPIO0-31中断状态
    (void)core_id;
    *status = hw->pcpu_int;
}

/**
  * @brief 获取GPIO中断状态高
  *
  * @param hw 外围GPIO硬件实例地址。
  * @param core_id 中断核心id
  * @param status 中断状态高
  */
static inline void gpio_ll_get_intr_status_high(gpio_dev_t *hw, uint32_t core_id, uint32_t *status)
{
    // 在ESP32S3上，pcpu_int1寄存器表示两个内核上的GPIO32-48中断状态
    (void)core_id;
    *status = hw->pcpu_int1.intr;
}

/**
  * @brief 清除GPIO中断状态
  *
  * @param hw 外围GPIO硬件实例地址。
  * @param mask 中断状态清除掩码
  */
static inline void gpio_ll_clear_intr_status(gpio_dev_t *hw, uint32_t mask)
{
    hw->status_w1tc = mask;
}

/**
  * @brief 清除GPIO中断状态高
  *
  * @param hw 外围GPIO硬件实例地址。
  * @param mask 中断状态高清晰掩码
  */
static inline void gpio_ll_clear_intr_status_high(gpio_dev_t *hw, uint32_t mask)
{
    hw->status1_w1tc.intr_st = mask;
}

/**
 * @brief  启用GPIO模块中断信号
 *
 * @param  hw 外围GPIO硬件实例地址。
 * @param  core_id 中断启用CPU到相应ID
 * @param  gpio_num GPIO编号。如果要启用例如GPIO16的中断，gpio_num应为gpio_num_16（16）；
 */
static inline void gpio_ll_intr_enable_on_core(gpio_dev_t *hw, uint32_t core_id, gpio_num_t gpio_num)
{
    (void)core_id;
    GPIO.pin[gpio_num].int_ena = GPIO_LL_INTR_ENA;     //启用intr
}

/**
 * @brief  禁用GPIO模块中断信号
 *
 * @param  hw 外围GPIO硬件实例地址。
 * @param  gpio_num GPIO编号。如果要禁用例如GPIO16的中断，gpio_num应为gpio_num_16（16）；
 */
static inline void gpio_ll_intr_disable(gpio_dev_t *hw, gpio_num_t gpio_num)
{
    hw->pin[gpio_num].int_ena = 0;                             //禁用GPIO intr
}

/**
  * @brief 禁用GPIO上的输入模式。
  *
  * @param hw 外围GPIO硬件实例地址。
  * @param gpio_num GPIO编号
  */
static inline void gpio_ll_input_disable(gpio_dev_t *hw, gpio_num_t gpio_num)
{
    PIN_INPUT_DISABLE(GPIO_PIN_MUX_REG[gpio_num]);
}

/**
  * @brief 启用GPIO上的输入模式。
  *
  * @param hw 外围GPIO硬件实例地址。
  * @param gpio_num GPIO编号
  */
static inline void gpio_ll_input_enable(gpio_dev_t *hw, gpio_num_t gpio_num)
{
    PIN_INPUT_ENABLE(GPIO_PIN_MUX_REG[gpio_num]);
}

/**
  * @brief 禁用GPIO上的输出模式。
  *
  * @param hw 外围GPIO硬件实例地址。
  * @param gpio_num GPIO编号
  */
static inline void gpio_ll_output_disable(gpio_dev_t *hw, gpio_num_t gpio_num)
{
    if (gpio_num < 32) {
        hw->enable_w1tc = (0x1 << gpio_num);
    } else {
        hw->enable1_w1tc.data = (0x1 << (gpio_num - 32));
    }

    // 确保没有其他输出信号通过GPIO矩阵路由到此引脚
    REG_WRITE(GPIO_FUNC0_OUT_SEL_CFG_REG + (gpio_num * 4),
              SIG_GPIO_OUT_IDX);
}

/**
  * @brief 启用GPIO上的输出模式。
  *
  * @param hw 外围GPIO硬件实例地址。
  * @param gpio_num GPIO编号
  */
static inline void gpio_ll_output_enable(gpio_dev_t *hw, gpio_num_t gpio_num)
{
    if (gpio_num < 32) {
        hw->enable_w1ts = (0x1 << gpio_num);
    } else {
        hw->enable1_w1ts.data = (0x1 << (gpio_num - 32));
    }
}

/**
  * @brief 禁用GPIO上的漏极开路模式。
  *
  * @param hw 外围GPIO硬件实例地址。
  * @param gpio_num GPIO编号
  */
static inline void gpio_ll_od_disable(gpio_dev_t *hw, gpio_num_t gpio_num)
{
    hw->pin[gpio_num].pad_driver = 0;
}

/**
  * @brief 启用GPIO上的漏极开路模式。
  *
  * @param hw 外围GPIO硬件实例地址。
  * @param gpio_num GPIO编号
  */
static inline void gpio_ll_od_enable(gpio_dev_t *hw, gpio_num_t gpio_num)
{
    hw->pin[gpio_num].pad_driver = 1;
}

/**
 * @brief  GPIO设置输出电平
 *
 * @param  hw 外围GPIO硬件实例地址。
 * @param  gpio_num GPIO编号。如果要设置例如GPIO16的输出电平，gpio_num应为gpio_num_16（16）；
 * @param  level 输出电平。0：低；1： 高
 */
static inline void gpio_ll_set_level(gpio_dev_t *hw, gpio_num_t gpio_num, uint32_t level)
{
    if (level) {
        if (gpio_num < 32) {
            hw->out_w1ts = (1 << gpio_num);
        } else {
            hw->out1_w1ts.data = (1 << (gpio_num - 32));
        }
    } else {
        if (gpio_num < 32) {
            hw->out_w1tc = (1 << gpio_num);
        } else {
            hw->out1_w1tc.data = (1 << (gpio_num - 32));
        }
    }
}

/**
 * @brief  GPIO获取输入电平
 *
 * @warning 如果焊盘未配置为输入（或输入和输出），则返回值始终为0。
 *
 * @param  hw 外围GPIO硬件实例地址。
 * @param  gpio_num GPIO编号。如果您想获得例如引脚GPIO16的逻辑电平，gpio_num应为gpio_num_16（16）；
 *
 * @return
 *     -0 GPIO输入电平为0
 *     -1 GPIO输入电平为1
 */
static inline int gpio_ll_get_level(gpio_dev_t *hw, gpio_num_t gpio_num)
{
    if (gpio_num < 32) {
        return (hw->in >> gpio_num) & 0x1;
    } else {
        return (hw->in1.data >> (gpio_num - 32)) & 0x1;
    }
}

/**
 * @brief 启用GPIO唤醒功能。
 *
 * @param hw 外围GPIO硬件实例地址。
 * @param gpio_num GPIO编号。
 * @param intr_type GPIO唤醒类型。只能使用GPIO_INTR_LOW_LEVEL或GPIO_INTR_HIGH_LEVEL。
 */
static inline void gpio_ll_wakeup_enable(gpio_dev_t *hw, gpio_num_t gpio_num, gpio_int_type_t intr_type)
{
    hw->pin[gpio_num].int_type = intr_type;
    hw->pin[gpio_num].wakeup_enable = 0x1;
}

/**
 * @brief 禁用GPIO唤醒功能。
 *
 * @param hw 外围GPIO硬件实例地址。
 * @param gpio_num GPIO编号
 */
static inline void gpio_ll_wakeup_disable(gpio_dev_t *hw, gpio_num_t gpio_num)
{
    hw->pin[gpio_num].wakeup_enable = 0;
}

/**
  * @brief 设置GPIO焊盘驱动能力
  *
  * @param hw 外围GPIO硬件实例地址。
  * @param gpio_num GPIO编号，仅支持输出GPIO
  * @param strength 衬垫的驱动能力
  */
static inline void gpio_ll_set_drive_capability(gpio_dev_t *hw, gpio_num_t gpio_num, gpio_drive_cap_t strength)
{
    SET_PERI_REG_BITS(GPIO_PIN_MUX_REG[gpio_num], FUN_DRV_V, strength, FUN_DRV_S);
}

/**
  * @brief 获取GPIO焊盘驱动功能
  *
  * @param hw 外围GPIO硬件实例地址。
  * @param gpio_num GPIO编号，仅支持输出GPIO
  * @param strength 接受极板驱动能力的指针
  */
static inline void gpio_ll_get_drive_capability(gpio_dev_t *hw, gpio_num_t gpio_num, gpio_drive_cap_t *strength)
{
    *strength = (gpio_drive_cap_t)GET_PERI_REG_BITS2(GPIO_PIN_MUX_REG[gpio_num], FUN_DRV_V, FUN_DRV_S);
}

/**
  * @brief 在深度睡眠期间启用全数字gpio pad hold功能。
  *
  * @param hw 外围GPIO硬件实例地址。
  */
static inline void gpio_ll_deep_sleep_hold_en(gpio_dev_t *hw)
{
    SET_PERI_REG_MASK(RTC_CNTL_DIG_ISO_REG, RTC_CNTL_DG_PAD_AUTOHOLD_EN_M);
}

/**
  * @brief 在深度睡眠期间禁用所有数字gpio pad hold功能。
  *
  * @param hw 外围GPIO硬件实例地址。
  */
static inline void gpio_ll_deep_sleep_hold_dis(gpio_dev_t *hw)
{
    SET_PERI_REG_MASK(RTC_CNTL_DIG_ISO_REG, RTC_CNTL_CLR_DG_PAD_AUTOHOLD);
}

/**
  * @brief 启用gpio pad hold功能。
  *
  * @param hw 外围GPIO硬件实例地址。
  * @param gpio_num GPIO编号，仅支持输出GPIO
  */
static inline void gpio_ll_hold_en(gpio_dev_t *hw, gpio_num_t gpio_num)
{
    SET_PERI_REG_MASK(RTC_CNTL_DIG_PAD_HOLD_REG, GPIO_HOLD_MASK[gpio_num]);
}

/**
  * @brief 禁用gpio pad hold功能。
  *
  * @param hw 外围GPIO硬件实例地址。
  * @param gpio_num GPIO编号，仅支持输出GPIO
  */
static inline void gpio_ll_hold_dis(gpio_dev_t *hw, gpio_num_t gpio_num)
{
    CLEAR_PERI_REG_MASK(RTC_CNTL_DIG_PAD_HOLD_REG, GPIO_HOLD_MASK[gpio_num]);
}

/**
  * @brief 通过IOMUX将焊盘输入设置为外围信号。
  *
  * @param hw 外围GPIO硬件实例地址。
  * @param gpio_num 焊盘的GPIO编号。
  * @param signal_idx 要输入的外围信号id。“soc/gpio_sig_map.h”中的“*_IN_IDX”信号之一。
  */
static inline void gpio_ll_iomux_in(gpio_dev_t *hw, uint32_t gpio, uint32_t signal_idx)
{
    hw->func_in_sel_cfg[signal_idx].sig_in_sel = 0;
    PIN_INPUT_ENABLE(GPIO_PIN_MUX_REG[gpio]);
}

/**
 * @brief  为IOMUX中的引脚选择功能
 *
 * @param  pin_name 要配置的Pin名称
 * @param  func 分配给引脚的功能
 */
static inline __attribute__((always_inline)) void gpio_ll_iomux_func_sel(uint32_t pin_name, uint32_t func)
{
    if (pin_name == IO_MUX_GPIO19_REG || pin_name == IO_MUX_GPIO20_REG) {
        CLEAR_PERI_REG_MASK(USB_SERIAL_JTAG_CONF0_REG, USB_SERIAL_JTAG_USB_PAD_ENABLE);
    }
    PIN_FUNC_SELECT(pin_name, func);
}

/**
  * @brief 通过IOMUX将外围输出设置为GPIO焊盘。
  *
  * @param hw 外围GPIO硬件实例地址。
  * @param gpio_num gpio_num gpio编号。
  * @param func 外围引脚到输出引脚的功能编号。“soc/io_max_reg.h”中指定引脚（X）的“FUNC_X_”之一。
  * @param oen_inv 如果需要反转输出启用，则为True，否则为False。
  */
static inline void gpio_ll_iomux_out(gpio_dev_t *hw, uint8_t gpio_num, int func, uint32_t oen_inv)
{
    hw->func_out_sel_cfg[gpio_num].oen_sel = 0;
    hw->func_out_sel_cfg[gpio_num].oen_inv_sel = oen_inv;
    gpio_ll_iomux_func_sel(GPIO_PIN_MUX_REG[gpio_num], func);
}

static inline void gpio_ll_force_hold_all(gpio_dev_t *hw)
{
    CLEAR_PERI_REG_MASK(RTC_CNTL_DIG_ISO_REG, RTC_CNTL_DG_PAD_FORCE_UNHOLD);
    SET_PERI_REG_MASK(RTC_CNTL_DIG_ISO_REG, RTC_CNTL_DG_PAD_FORCE_HOLD);
}

static inline void gpio_ll_force_unhold_all(void)
{
    CLEAR_PERI_REG_MASK(RTC_CNTL_DIG_ISO_REG, RTC_CNTL_DG_PAD_FORCE_HOLD);
    SET_PERI_REG_MASK(RTC_CNTL_DIG_ISO_REG, RTC_CNTL_DG_PAD_FORCE_UNHOLD);
    SET_PERI_REG_MASK(RTC_CNTL_DIG_ISO_REG, RTC_CNTL_CLR_DG_PAD_AUTOHOLD);
}

/**
  * @brief 启用用于从睡眠中唤醒的GPIO引脚。
  *
  * @param hw 外围GPIO硬件实例地址。
  * @param gpio_num GPIO编号
  */
static inline void gpio_ll_sleep_sel_en(gpio_dev_t *hw, gpio_num_t gpio_num)
{
    PIN_SLP_SEL_ENABLE(GPIO_PIN_MUX_REG[gpio_num]);
}

/**
  * @brief 禁用用于从睡眠中唤醒的GPIO引脚。
  *
  * @param hw 外围GPIO硬件实例地址。
  * @param gpio_num GPIO编号
  */
static inline void gpio_ll_sleep_sel_dis(gpio_dev_t *hw, gpio_num_t gpio_num)
{
    PIN_SLP_SEL_DISABLE(GPIO_PIN_MUX_REG[gpio_num]);
}

/**
  * @brief 在睡眠模式下禁用GPIO上拉。
  *
  * @param hw 外围GPIO硬件实例地址。
  * @param gpio_num GPIO编号
  */
static inline void gpio_ll_sleep_pullup_dis(gpio_dev_t *hw, gpio_num_t gpio_num)
{
    PIN_SLP_PULLUP_DISABLE(GPIO_PIN_MUX_REG[gpio_num]);
}

/**
  * @brief 在睡眠模式下启用GPIO上拉。
  *
  * @param hw 外围GPIO硬件实例地址。
  * @param gpio_num GPIO编号
  */
static inline void gpio_ll_sleep_pullup_en(gpio_dev_t *hw, gpio_num_t gpio_num)
{
    PIN_SLP_PULLUP_ENABLE(GPIO_PIN_MUX_REG[gpio_num]);
}

/**
  * @brief 在睡眠模式下启用GPIO下拉。
  *
  * @param hw 外围GPIO硬件实例地址。
  * @param gpio_num GPIO编号
  */
static inline void gpio_ll_sleep_pulldown_en(gpio_dev_t *hw, gpio_num_t gpio_num)
{
    PIN_SLP_PULLDOWN_ENABLE(GPIO_PIN_MUX_REG[gpio_num]);
}

/**
  * @brief 在睡眠模式下禁用GPIO下拉。
  *
  * @param hw 外围GPIO硬件实例地址。
  * @param gpio_num GPIO编号
  */
static inline void gpio_ll_sleep_pulldown_dis(gpio_dev_t *hw, gpio_num_t gpio_num)
{
    PIN_SLP_PULLDOWN_DISABLE(GPIO_PIN_MUX_REG[gpio_num]);
}

/**
  * @brief 在睡眠模式下禁用GPIO输入。
  *
  * @param hw 外围GPIO硬件实例地址。
  * @param gpio_num GPIO编号
  */
static inline void gpio_ll_sleep_input_disable(gpio_dev_t *hw, gpio_num_t gpio_num)
{
    PIN_SLP_INPUT_DISABLE(GPIO_PIN_MUX_REG[gpio_num]);
}

/**
  * @brief 在睡眠模式下启用GPIO输入。
  *
  * @param hw 外围GPIO硬件实例地址。
  * @param gpio_num GPIO编号
  */
static inline void gpio_ll_sleep_input_enable(gpio_dev_t *hw, gpio_num_t gpio_num)
{
    PIN_SLP_INPUT_ENABLE(GPIO_PIN_MUX_REG[gpio_num]);
}

/**
  * @brief 在睡眠模式下禁用GPIO输出。
  *
  * @param hw 外围GPIO硬件实例地址。
  * @param gpio_num GPIO编号
  */
static inline void gpio_ll_sleep_output_disable(gpio_dev_t *hw, gpio_num_t gpio_num)
{
    PIN_SLP_OUTPUT_DISABLE(GPIO_PIN_MUX_REG[gpio_num]);
}

/**
  * @brief 在睡眠模式下启用GPIO输出。
  *
  * @param hw 外围GPIO硬件实例地址。
  * @param gpio_num GPIO编号
  */
static inline void gpio_ll_sleep_output_enable(gpio_dev_t *hw, gpio_num_t gpio_num)
{
    PIN_SLP_OUTPUT_ENABLE(GPIO_PIN_MUX_REG[gpio_num]);
}

#ifdef __cplusplus
}
#endif

