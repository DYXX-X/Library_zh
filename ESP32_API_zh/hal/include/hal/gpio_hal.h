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
 * 注意：hal不是公共api，不要在应用程序代码中使用。请参阅自述文件。在hal/include/hal/readme.md中的md
 ******************************************************************************/

// GPIO的HAL层

#pragma once

#include "soc/gpio_periph.h"
#include "soc/soc_caps.h"
#include "hal/gpio_ll.h"
#include "hal/gpio_types.h"

#ifdef CONFIG_LEGACY_INCLUDE_COMMON_HEADERS
#include "soc/rtc_io_reg.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

// 通过提供GPIO num获取GPIO硬件实例
#define GPIO_HAL_GET_HW(num) GPIO_LL_GET_HW(num)

/**
 * 驾驶员和HAL应维护的上下文
 */

typedef struct {
    gpio_dev_t *dev;
    uint32_t version;
} gpio_hal_context_t;

/**
  * @brief 启用GPIO上拉。
  *
  * @param hal HAL层的上下文
  * @param gpio_num GPIO编号
  */
#define gpio_hal_pullup_en(hal, gpio_num) gpio_ll_pullup_en((hal)->dev, gpio_num)

/**
  * @brief 禁用GPIO上的上拉。
  *
  * @param hal HAL层的上下文
  * @param gpio_num GPIO编号
  */
#define gpio_hal_pullup_dis(hal, gpio_num) gpio_ll_pullup_dis((hal)->dev, gpio_num)

/**
  * @brief 启用GPIO上的下拉。
  *
  * @param hal HAL层的上下文
  * @param gpio_num GPIO编号
  */
#define gpio_hal_pulldown_en(hal, gpio_num) gpio_ll_pulldown_en((hal)->dev, gpio_num)

/**
  * @brief 禁用GPIO上的下拉。
  *
  * @param hal HAL层的上下文
  * @param gpio_num GPIO编号
  */
#define gpio_hal_pulldown_dis(hal, gpio_num) gpio_ll_pulldown_dis((hal)->dev, gpio_num)

/**
 * @brief  GPIO设置中断触发类型
 *
 * @param  hal HAL层的上下文
 * @param  gpio_num GPIO编号。如果要设置触发类型，例如GPIO16，gpio_num应为gpio_num_16（16）；
 * @param  intr_type 中断类型，从gpio_int_type_t中选择
 */
#define gpio_hal_set_intr_type(hal, gpio_num, intr_type) gpio_ll_set_intr_type((hal)->dev, gpio_num, intr_type)

/**
  * @brief 获取GPIO中断状态
  *
  * @param hal HAL层的上下文
  * @param core_id 中断核心id
  * @param status 中断状态
  */
#define gpio_hal_get_intr_status(hal, core_id, status) gpio_ll_get_intr_status((hal)->dev, core_id, status)

/**
  * @brief 获取GPIO中断状态高
  *
  * @param hal HAL层的上下文
  * @param core_id 中断核心id
  * @param status 中断状态高
  */
#define gpio_hal_get_intr_status_high(hal, core_id, status) gpio_ll_get_intr_status_high((hal)->dev, core_id, status)

/**
  * @brief 清除GPIO中断状态
  *
  * @param hal HAL层的上下文
  * @param mask 中断状态清除掩码
  */
#define gpio_hal_clear_intr_status(hal, mask) gpio_ll_clear_intr_status((hal)->dev, mask)

/**
  * @brief 清除GPIO中断状态高
  *
  * @param hal HAL层的上下文
  * @param mask 中断状态高清晰掩码
  */
#define gpio_hal_clear_intr_status_high(hal, mask) gpio_ll_clear_intr_status_high((hal)->dev, mask)

/**
 * @brief  启用GPIO模块中断信号
 *
 * @param  hal HAL层的上下文
 * @param  gpio_num GPIO编号。如果要启用例如GPIO16的中断，gpio_num应为gpio_num_16（16）；
 * @param  core_id 中断启用CPU到相应ID
 */
void gpio_hal_intr_enable_on_core(gpio_hal_context_t *hal, gpio_num_t gpio_num, uint32_t core_id);

/**
 * @brief  禁用GPIO模块中断信号
 *
 * @param  hal HAL层的上下文
 * @param  gpio_num GPIO编号。如果要禁用例如GPIO16的中断，gpio_num应为gpio_num_16（16）；
 */
void gpio_hal_intr_disable(gpio_hal_context_t *hal, gpio_num_t gpio_num);

/**
  * @brief 禁用GPIO上的输入模式。
  *
  * @param hal HAL层的上下文
  * @param gpio_num GPIO编号
  */
#define gpio_hal_input_disable(hal, gpio_num) gpio_ll_input_disable((hal)->dev, gpio_num)

/**
  * @brief 启用GPIO上的输入模式。
  *
  * @param hal HAL层的上下文
  * @param gpio_num GPIO编号
  */
#define gpio_hal_input_enable(hal, gpio_num) gpio_ll_input_enable((hal)->dev, gpio_num)

/**
  * @brief 禁用GPIO上的输出模式。
  *
  * @param hal HAL层的上下文
  * @param gpio_num GPIO编号
  */
#define gpio_hal_output_disable(hal, gpio_num) gpio_ll_output_disable((hal)->dev, gpio_num)

/**
  * @brief 启用GPIO上的输出模式。
  *
  * @param hal HAL层的上下文
  * @param gpio_num GPIO编号
  */
#define gpio_hal_output_enable(hal, gpio_num) gpio_ll_output_enable((hal)->dev, gpio_num)

/**
  * @brief 禁用GPIO上的漏极开路模式。
  *
  * @param hal HAL层的上下文
  * @param gpio_num GPIO编号
  */
#define gpio_hal_od_disable(hal, gpio_num) gpio_ll_od_disable((hal)->dev, gpio_num)

/**
  * @brief 启用GPIO上的漏极开路模式。
  *
  * @param hal HAL层的上下文
  * @param gpio_num GPIO编号
  */
#define gpio_hal_od_enable(hal, gpio_num) gpio_ll_od_enable((hal)->dev, gpio_num)

/**
 * @brief  GPIO设置输出电平
 *
 * @param  hal HAL层的上下文
 * @param  gpio_num GPIO编号。如果要设置例如GPIO16的输出电平，gpio_num应为gpio_num_16（16）；
 * @param  level 输出电平。0：低；1： 高
 */
#define gpio_hal_set_level(hal, gpio_num, level) gpio_ll_set_level((hal)->dev, gpio_num, level)

/**
 * @brief  GPIO获取输入电平
 *
 * @warning 如果焊盘未配置为输入（或输入和输出），则返回值始终为0。
 *
 * @param  hal HAL层的上下文
 * @param  gpio_num GPIO编号。如果您想获得例如引脚GPIO16的逻辑电平，gpio_num应为gpio_num_16（16）；
 *
 * @return
 *     -0 GPIO输入电平为0
 *     -1 GPIO输入电平为1
 */
#define gpio_hal_get_level(hal, gpio_num) gpio_ll_get_level((hal)->dev, gpio_num)

/**
 * @brief 启用GPIO唤醒功能。
 *
 * @param hal HAL层的上下文
 * @param gpio_num GPIO编号。
 * @param intr_type GPIO唤醒类型。只能使用GPIO_INTR_LOW_LEVEL或GPIO_INTR_HIGH_LEVEL。
 */
#define gpio_hal_wakeup_enable(hal, gpio_num, intr_type) gpio_ll_wakeup_enable((hal)->dev, gpio_num, intr_type)

/**
 * @brief 禁用GPIO唤醒功能。
 *
 * @param hal HAL层的上下文
 * @param gpio_num GPIO编号
 */
#define gpio_hal_wakeup_disable(hal, gpio_num) gpio_ll_wakeup_disable((hal)->dev, gpio_num)

/**
  * @brief 设置GPIO焊盘驱动能力
  *
  * @param hal HAL层的上下文
  * @param gpio_num GPIO编号，仅支持输出GPIO
  * @param strength 衬垫的驱动能力
  */
#define gpio_hal_set_drive_capability(hal, gpio_num, strength) gpio_ll_set_drive_capability((hal)->dev, gpio_num, strength)

/**
  * @brief 获取GPIO焊盘驱动功能
  *
  * @param hal HAL层的上下文
  * @param gpio_num GPIO编号，仅支持输出GPIO
  * @param strength 接受极板驱动能力的指针
  */
#define gpio_hal_get_drive_capability(hal, gpio_num, strength) gpio_ll_get_drive_capability((hal)->dev, gpio_num, strength)

/**
  * @brief 启用gpio pad hold功能。
  *
  * gpio pad hold功能可以在输入和输出模式下工作，但必须是支持输出的gpios。如果焊盘保持启用：在输出模式下：焊盘的输出电平将被强制锁定，无法更改。在输入模式下：无论输入信号的变化如何，读取的输入值都不会改变。
  *
  * 数字gpio的状态在深度睡眠期间无法保持，当芯片从深度睡眠中醒来时，它将恢复保持功能。如果数字gpio也需要在深度睡眠期间保持，则还应调用“gpio_Deep_sleep_hold_en”。
  *
  * 关闭电源或调用gpio_hold_dis将禁用此功能。
  *
  * @param hal HAL层的上下文
  * @param gpio_num GPIO编号，仅支持输出GPIO
  */
#define gpio_hal_hold_en(hal, gpio_num) gpio_ll_hold_en((hal)->dev, gpio_num)

/**
  * @brief 禁用gpio pad hold功能。
  *
  * 当芯片从深度睡眠中唤醒时，gpio将设置为默认模式，因此，如果调用此功能，gpio会输出默认级别。如果不想更改级别，则应在调用此函数之前将gpio配置为已知状态。e、 g.如果在深度睡眠期间将gpio18保持为高电平，则在芯片被唤醒并调用“gpio_hold_dis”后，gpio18将输出低电平（因为gpio18默认为输入模式）。如果不希望出现这种行为，应将gpio18配置为输出模式，并在调用“gpio_hold_dis”之前将其设置为高级别。
  *
  * @param hal HAL层的上下文
  * @param gpio_num GPIO编号，仅支持输出GPIO
  */
#define gpio_hal_hold_dis(hal, gpio_num) gpio_ll_hold_dis((hal)->dev, gpio_num)

/**
  * @brief 在深度睡眠期间启用全数字gpio pad hold功能。
  *
  * 当芯片处于深度睡眠模式时，所有数字gpio将保持睡眠前的状态，而当芯片被唤醒时，数字gpio的状态将不会保持。请注意，pad hold功能仅在芯片处于深度睡眠模式时有效，在不处于睡眠模式时，即使您调用了此功能，也可以更改数字gpio状态。
  *
  * 关闭电源或调用gpio_hold_dis将禁用此功能，否则，只要芯片进入深度睡眠，数字gpio保持功能即可工作。
  *
  * @param hal HAL层的上下文
  */
#define gpio_hal_deep_sleep_hold_en(hal) gpio_ll_deep_sleep_hold_en((hal)->dev)

/**
  * @brief 在深度睡眠期间禁用所有数字gpio pad hold功能。
  *
  * @param hal HAL层的上下文
  */
#define gpio_hal_deep_sleep_hold_dis(hal) gpio_ll_deep_sleep_hold_dis((hal)->dev)

/**
  * @brief 通过IOMUX将焊盘输入设置为外围信号。
  *
  * @param hal HAL层的上下文
  * @param gpio_num 焊盘的GPIO编号。
  * @param signal_idx 要输入的外围信号id。“soc/gpio_sig_map.h”中的“*_IN_IDX”信号之一。
  */
#define gpio_hal_iomux_in(hal, gpio_num, signal_idx) gpio_ll_iomux_in((hal)->dev, gpio_num, signal_idx)

/**
  * @brief 通过IOMUX将外围输出设置为GPIO焊盘。
  *
  * @param hal HAL层的上下文
  * @param gpio_num gpio_num gpio编号。
  * @param func 外围引脚到输出引脚的功能编号。“soc/io_max_reg.h”中指定引脚（X）的“FUNC_X_”之一。
  * @param oen_inv 如果需要反转输出启用，则为True，否则为False。
  */
#define gpio_hal_iomux_out(hal, gpio_num, func, oen_inv) gpio_ll_iomux_out((hal)->dev, gpio_num, func, oen_inv)

#if SOC_GPIO_SUPPORT_FORCE_HOLD
/**
  * @brief 强制保持数字和rtc gpio垫。
  * @note GPIO强制保持，无论芯片处于睡眠模式还是唤醒模式。
  *
  * @param hal HAL层的上下文
  * */
#define gpio_hal_force_hold_all(hal) gpio_ll_force_hold_all((hal)->dev)

/**
  * @brief 强制解锁数字和rtc gpio pad。
  * @note GPIO强制脱钩，无论芯片处于睡眠模式还是唤醒模式。
  *
  * @param hal HAL层的上下文
  * */
#define gpio_hal_force_unhold_all() gpio_ll_force_unhold_all()
#endif

#if SOC_GPIO_SUPPORT_SLP_SWITCH
/**
  * @brief 在系统休眠时启用GPIO上拉。
  *
  * @param hal HAL层的上下文
  * @param gpio_num GPIO编号
  */
#define gpio_hal_sleep_pullup_en(hal, gpio_num) gpio_ll_sleep_pullup_en((hal)->dev, gpio_num)

/**
  * @brief 系统休眠时禁用GPIO上拉。
  *
  * @param hal HAL层的上下文
  * @param gpio_num GPIO编号
  */
#define gpio_hal_sleep_pullup_dis(hal, gpio_num) gpio_ll_sleep_pullup_dis((hal)->dev, gpio_num)

/**
  * @brief 在系统休眠时启用GPIO下拉。
  *
  * @param hal HAL层的上下文
  * @param gpio_num GPIO编号
  */
#define gpio_hal_sleep_pulldown_en(hal, gpio_num) gpio_ll_sleep_pulldown_en((hal)->dev, gpio_num)

/**
  * @brief 系统休眠时禁用GPIO下拉。
  *
  * @param hal HAL层的上下文
  * @param gpio_num GPIO编号
  */
#define gpio_hal_sleep_pulldown_dis(hal, gpio_num) gpio_ll_sleep_pulldown_dis((hal)->dev, gpio_num)

/**
  * @brief 启用GPIO上的睡眠选择。
  *
  * @param hal HAL层的上下文
  * @param gpio_num GPIO编号
  */
#define gpio_hal_sleep_sel_en(hal, gpio_num) gpio_ll_sleep_sel_en((hal)->dev, gpio_num)

/**
  * @brief 禁用GPIO上的睡眠选择。
  *
  * @param hal HAL层的上下文
  * @param gpio_num GPIO编号
  */
#define gpio_hal_sleep_sel_dis(hal, gpio_num) gpio_ll_sleep_sel_dis((hal)->dev, gpio_num)

/**
  * @brief 系统休眠时禁用GPIO上的输入模式。
  *
  * @param hal HAL层的上下文
  * @param gpio_num GPIO编号
  */
#define gpio_hal_sleep_input_disable(hal, gpio_num) gpio_ll_sleep_input_disable((hal)->dev, gpio_num)

/**
  * @brief 在系统休眠时启用GPIO上的输入模式。
  *
  * @param hal HAL层的上下文
  * @param gpio_num GPIO编号
  */
#define gpio_hal_sleep_input_enable(hal, gpio_num) gpio_ll_sleep_input_enable((hal)->dev, gpio_num)

/**
  * @brief 系统休眠时禁用GPIO上的输出模式。
  *
  * @param hal HAL层的上下文
  * @param gpio_num GPIO编号
  */
#define gpio_hal_sleep_output_disable(hal, gpio_num) gpio_ll_sleep_output_disable((hal)->dev, gpio_num)

/**
  * @brief 在系统休眠时启用GPIO上的输出模式。
  *
  * @param hal HAL层的上下文
  * @param gpio_num GPIO编号
  */
#define gpio_hal_sleep_output_enable(hal, gpio_num) gpio_ll_sleep_output_enable((hal)->dev, gpio_num)

#if CONFIG_GPIO_ESP32_SUPPORT_SWITCH_SLP_PULL
/**
 * @brief  在系统休眠时，将slp_pu/slp_pd配置应用于fun_pu/fun_pd。
 *
 * @param  hal HAL层的上下文
 * @param  gpio_num GPIO编号。
 */
void gpio_hal_sleep_pupd_config_apply(gpio_hal_context_t *hal, gpio_num_t gpio_num);

/**
 * @brief  系统唤醒时恢复fun_pu/fun_pd配置。
 *
 * @param  hal HAL层的上下文
 * @param  gpio_num GPIO编号。
 */
void gpio_hal_sleep_pupd_config_unapply(gpio_hal_context_t *hal, gpio_num_t gpio_num);
#endif // CONFIG_GPIO_ESP32_SUPPORT_SWITCH_SLP_PULL
#endif //SOC_GPIO_SUPPORT_SLP_SWITCH

#if SOC_GPIO_SUPPORT_DEEPSLEEP_WAKEUP

/**
 * @brief 启用GPIO深度睡眠唤醒功能。
 *
 * @param hal HAL层的上下文
 * @param gpio_num GPIO编号。
 * @param intr_type GPIO唤醒类型。只能使用GPIO_INTR_LOW_LEVEL或GPIO_INTR_HIGH_LEVEL。
 */
#define gpio_hal_deepsleep_wakeup_enable(hal, gpio_num, intr_type) gpio_ll_deepsleep_wakeup_enable((hal)->dev, gpio_num, intr_type)

/**
 * @brief 禁用GPIO深度睡眠唤醒功能。
 *
 * @param hal HAL层的上下文
 * @param gpio_num GPIO编号
 */
#define gpio_hal_deepsleep_wakeup_disable(hal, gpio_num) gpio_ll_deepsleep_wakeup_disable((hal)->dev, gpio_num)

/**
 * @brief 判断gpio是否适用于从深度睡眠中唤醒芯片
 *
 * @param gpio_num GPIO编号
 */
#define gpio_hal_is_valid_deepsleep_wakeup_gpio(gpio_num) (gpio_num <= GPIO_NUM_5)

#endif //SOC_GPIO_SUPPORT_DEEPSLEEP_WAKEUP

/**
 * @brief  为IOMUX中的引脚选择功能
 *
 * @param  pin_name 要配置的Pin名称
 * @param  func 分配给引脚的功能
 */
#define gpio_hal_iomux_func_sel(pin_name, func) gpio_ll_iomux_func_sel(pin_name, func)

#ifdef __cplusplus
}
#endif

