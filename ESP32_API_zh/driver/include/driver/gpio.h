/*
 * SPDX文件版权文本：2015-2021浓缩咖啡系统（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */

#pragma once

#include "sdkconfig.h"
#include "esp_err.h"
#include <stdbool.h>
#include "esp_intr_alloc.h"
#if !CONFIG_IDF_TARGET_LINUX
#include <esp_types.h>
#include <esp_bit_defs.h>
#include "esp_attr.h"
#include "soc/soc_caps.h"
#include "soc/gpio_periph.h"
#endif // !CONFIG_IDF_TARGET_LINUX
#include "hal/gpio_types.h"

// |================================= WARNING ====================================================== |
// |在PUBLIC API文件中包含ROM头文件将在下一个主要版本（5.x）中删除|
// |如果必须使用这些rom API，用户应该在代码中包含“esp_rom_gpio.h”|
// |================================================================================================ |
#if CONFIG_IDF_TARGET_ESP32
#include "esp32/rom/gpio.h"
#elif CONFIG_IDF_TARGET_ESP32S2
#include "esp32s2/rom/gpio.h"
#elif CONFIG_IDF_TARGET_ESP32S3
#include "esp32s3/rom/gpio.h"
#elif CONFIG_IDF_TARGET_ESP32C3
#include "esp32c3/rom/gpio.h"
#elif CONFIG_IDF_TARGET_ESP32S3
#include "esp32s3/rom/gpio.h"
#elif CONFIG_IDF_TARGET_ESP32H2
#include "esp32h2/rom/gpio.h"
#endif

#ifdef CONFIG_LEGACY_INCLUDE_COMMON_HEADERS
#include "soc/rtc_io_reg.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

#define GPIO_PIN_COUNT                      (SOC_GPIO_PIN_COUNT)
///检查是否为有效的GPIO编号
#define GPIO_IS_VALID_GPIO(gpio_num)        (((1ULL << (gpio_num)) & SOC_GPIO_VALID_GPIO_MASK) != 0)
///检查是否可以是输出模式的有效GPIO编号
#define GPIO_IS_VALID_OUTPUT_GPIO(gpio_num) (((1ULL << (gpio_num)) & SOC_GPIO_VALID_OUTPUT_GPIO_MASK) != 0)


typedef intr_handle_t gpio_isr_handle_t;

/**
 * @brief GPIO通用配置
 *
 *        配置GPIO模式、上拉、下拉和IntrType
 *
 * @param  pGPIOConfig 指向GPIO配置结构的指针
 *
 * @return
 *     -ESP_OK成功
 *     -ESP_ERR_INVALID_ARG参数错误
 *
 */
esp_err_t gpio_config(const gpio_config_t *pGPIOConfig);

/**
 * @brief 将gpio重置为默认状态（选择gpio功能，启用上拉并禁用输入和输出）。
 *
 * @param gpio_num GPIO编号。
 *
 * @note 该功能还将此引脚的IOMUX配置为GPIO功能，并断开通过GPIO矩阵配置的任何其他外围输出。
 *
 * @return 始终返回ESP_OK。
 */
esp_err_t gpio_reset_pin(gpio_num_t gpio_num);

/**
 * @brief  GPIO设置中断触发类型
 *
 * @param  gpio_num GPIO编号。如果要设置触发类型，例如GPIO16，gpio_num应为gpio_num_16（16）；
 * @param  intr_type 中断类型，从gpio_int_type_t中选择
 *
 * @return
 *     -ESP_OK成功
 *     -ESP_ERR_INVALID_ARG参数错误
 *
 */
esp_err_t gpio_set_intr_type(gpio_num_t gpio_num, gpio_int_type_t intr_type);

/**
 * @brief  启用GPIO模块中断信号
 *
 * @note 在启用睡眠模式的情况下使用ADC或Wi-Fi时，请不要使用GPIO36和GPIO39的中断。请参阅“adc1_get_raw”的注释。有关此问题的说明，请参阅“ECO_and_Workarounds_for_Bugs_in_ESP32”的第3.11节。作为解决方法，在应用程序中调用adc_power_acquire（）。这将导致更高的功耗（约1mA），但将消除GPIO36和GPIO39上的故障。
 *
 * @param  gpio_num GPIO编号。如果要在例如GPIO16上启用中断，gpio_num应为gpio_num_16（16）；
 *
 * @return
 *     -ESP_OK成功
 *     -ESP_ERR_INVALID_ARG参数错误
 *
 */
esp_err_t gpio_intr_enable(gpio_num_t gpio_num);

/**
 * @brief  禁用GPIO模块中断信号
 *
 * @param  gpio_num GPIO编号。如果要禁用例如GPIO16的中断，gpio_num应为gpio_num_16（16）；
 *
 * @return
 *     -ESP_OK成功
 *     -ESP_ERR_INVALID_ARG参数错误
 *
 */
esp_err_t gpio_intr_disable(gpio_num_t gpio_num);

/**
 * @brief  GPIO设置输出电平
 *
 * @param  gpio_num GPIO编号。如果要设置例如GPIO16的输出电平，gpio_num应为gpio_num_16（16）；
 * @param  level 输出电平。0：低；1： 高
 *
 * @return
 *     -ESP_OK成功
 *     -ESP_ERR_INVALID_ARG GPIO编号错误
 *
 */
esp_err_t gpio_set_level(gpio_num_t gpio_num, uint32_t level);

/**
 * @brief  GPIO获取输入电平
 *
 * @warning 如果焊盘未配置为输入（或输入和输出），则返回值始终为0。
 *
 * @param  gpio_num GPIO编号。如果您想获得例如引脚GPIO16的逻辑电平，gpio_num应为gpio_num_16（16）；
 *
 * @return
 *     -0 GPIO输入电平为0
 *     -1 GPIO输入电平为1
 *
 */
int gpio_get_level(gpio_num_t gpio_num);

/**
 * @brief	 GPIO设置方向
 *
 * 配置GPIO方向，如output_only、input_only和output_and_input
 *
 * @param  gpio_num  配置GPIO引脚编号，应为GPIO编号。如果要设置例如GPIO16的方向，gpio_num应为gpio_num_16（16）；
 * @param  mode GPIO方向
 *
 * @return
 *     -ESP_OK成功
 *     -ESP_ERR_INVALID_ARG GPIO错误
 *
 */
esp_err_t gpio_set_direction(gpio_num_t gpio_num, gpio_mode_t mode);

/**
 * @brief  配置GPIO上拉/下拉电阻器
 *
 * 只有同时支持输入和输出的引脚具有集成的上拉和下拉电阻器。仅输入GPIO 34-39没有。
 *
 * @param  gpio_num GPIO编号。如果要为例如GPIO16设置上拉或下拉模式，gpio_num应为gpio_num_16（16）；
 * @param  pull GPIO上拉/下拉模式。
 *
 * @return
 *     -ESP_OK成功
 *     -ESP_ERR_INVALID_ARG：参数错误
 *
 */
esp_err_t gpio_set_pull_mode(gpio_num_t gpio_num, gpio_pull_mode_t pull);

/**
 * @brief 启用GPIO唤醒功能。
 *
 * @param gpio_num GPIO编号。
 *
 * @param intr_type GPIO唤醒类型。只能使用GPIO_INTR_LOW_LEVEL或GPIO_INTR_HIGH_LEVEL。
 *
 * @return
 *     -ESP_OK成功
 *     -ESP_ERR_INVALID_ARG参数错误
 */
esp_err_t gpio_wakeup_enable(gpio_num_t gpio_num, gpio_int_type_t intr_type);

/**
 * @brief 禁用GPIO唤醒功能。
 *
 * @param gpio_num GPIO编号
 *
 * @return
 *     -ESP_OK成功
 *     -ESP_ERR_INVALID_ARG参数错误
 */
esp_err_t gpio_wakeup_disable(gpio_num_t gpio_num);

/**
 * @brief   注册GPIO中断处理程序，该处理程序是ISR。处理程序将连接到运行此函数的同一CPU内核。
 *
 * 每当发生任何GPIO中断时，都会调用此ISR函数。请参阅gpio_install_isr_service（）和gpio_isr_handler_add（）API，以获得每个gpio isr的驱动程序支持。
 *
 * @param  fn  中断处理程序函数。
 * @param  arg  处理程序函数的参数
 * @param  intr_alloc_flags 用于分配中断的标志。一个或多个（ORred）ESP_INTR_FLAG_值。请参见esp_intr_alloc。h了解更多信息。
 * @param  handle 指向返回句柄的指针。如果非NULL，将在此处返回中断的句柄。
 *
 * \逐字嵌入：rst:leading星号要禁用或删除ISR，请将返回的句柄传递给：doc:`中断分配函数</api-reference/system/intr_alloc>`。\逐字结尾
 *
 * @return
 *     -ESP_OK成功；
 *     -ESP_ERR_INVALID_ARG GPIO错误
 *     -ESP_ERR_NOT_FOUND未找到具有指定标志的空闲中断
 */
esp_err_t gpio_isr_register(void (*fn)(void *), void *arg, int intr_alloc_flags, gpio_isr_handle_t *handle);

/**
  * @brief 启用GPIO上拉。
  *
  * @param gpio_num GPIO编号
  *
  * @return
  *     -ESP_OK成功
  *     -ESP_ERR_INVALID_ARG参数错误
  */
esp_err_t gpio_pullup_en(gpio_num_t gpio_num);

/**
  * @brief 禁用GPIO上的上拉。
  *
  * @param gpio_num GPIO编号
  *
  * @return
  *     -ESP_OK成功
  *     -ESP_ERR_INVALID_ARG参数错误
  */
esp_err_t gpio_pullup_dis(gpio_num_t gpio_num);

/**
  * @brief 启用GPIO上的下拉。
  *
  * @param gpio_num GPIO编号
  *
  * @return
  *     -ESP_OK成功
  *     -ESP_ERR_INVALID_ARG参数错误
  */
esp_err_t gpio_pulldown_en(gpio_num_t gpio_num);

/**
  * @brief 禁用GPIO上的下拉。
  *
  * @param gpio_num GPIO编号
  *
  * @return
  *     -ESP_OK成功
  *     -ESP_ERR_INVALID_ARG参数错误
  */
esp_err_t gpio_pulldown_dis(gpio_num_t gpio_num);

/**
  * @brief 安装驱动程序的GPIO ISR处理程序服务，该服务允许每引脚GPIO中断处理程序。
  *
  * 此函数与gpio_isr_register（）不兼容-如果使用该函数，则为所有gpio中断注册一个全局isr。如果使用此函数，ISR服务将提供一个全局GPIO ISR，并通过GPIO_ISR_handler_add（）函数注册各个引脚处理程序。
  *
  * @param intr_alloc_flags 用于分配中断的标志。一个或多个（ORred）ESP_INTR_FLAG_值。请参见esp_intr_alloc。h了解更多信息。
  *
  * @return
  *     -ESP_OK成功
  *     -ESP_ERR_NO_MEM没有内存安装此服务
  *     -ESP_ERR_INVALID_STATE ISR服务已安装。
  *     -ESP_ERR_NOT_FOUND未找到具有指定标志的空闲中断
  *     -ESP_ERR_INVALID_ARG GPIO错误
  */
esp_err_t gpio_install_isr_service(int intr_alloc_flags);

/**
  * @brief 卸载驱动程序的GPIO ISR服务，释放相关资源。
  */
void gpio_uninstall_isr_service(void);

/**
  * @brief 为相应的GPIO引脚添加ISR处理器。
  *
  * 使用gpio_install_isr_service（）安装驱动程序的gpio isr处理程序服务后，调用此函数。
  *
  * 引脚ISR处理程序不再需要用IRAM_ATTR声明，除非在gpio_install_ISR_service（）中分配ISR时传递ESP_INTR_FLAG_IRAM标志。
  *
  * 将从ISR调用此ISR处理程序。因此存在堆栈大小限制（在menuconfig中可配置为“ISR堆栈大小”）。由于额外的间接级别，与全局GPIO中断处理程序相比，此限制更小。
  *
  * @param gpio_num GPIO编号
  * @param isr_handler 对应GPIO编号的ISR处理程序函数。
  * @param args ISR处理程序的参数。
  *
  * @return
  *     -ESP_OK成功
  *     -ESP_ERR_INVALID_STATE状态错误，ISR服务尚未初始化。
  *     -ESP_ERR_INVALID_ARG参数错误
  */
esp_err_t gpio_isr_handler_add(gpio_num_t gpio_num, gpio_isr_t isr_handler, void *args);

/**
  * @brief 移除相应GPIO引脚的ISR处理器。
  *
  * @param gpio_num GPIO编号
  *
  * @return
  *     -ESP_OK成功
  *     -ESP_ERR_INVALID_STATE状态错误，ISR服务尚未初始化。
  *     -ESP_ERR_INVALID_ARG参数错误
  */
esp_err_t gpio_isr_handler_remove(gpio_num_t gpio_num);

/**
  * @brief 设置GPIO焊盘驱动能力
  *
  * @param gpio_num GPIO编号，仅支持输出GPIO
  * @param strength 衬垫的驱动能力
  *
  * @return
  *     -ESP_OK成功
  *     -ESP_ERR_INVALID_ARG参数错误
  */
esp_err_t gpio_set_drive_capability(gpio_num_t gpio_num, gpio_drive_cap_t strength);

/**
  * @brief 获取GPIO焊盘驱动功能
  *
  * @param gpio_num GPIO编号，仅支持输出GPIO
  * @param strength 接受极板驱动能力的指针
  *
  * @return
  *     -ESP_OK成功
  *     -ESP_ERR_INVALID_ARG参数错误
  */
esp_err_t gpio_get_drive_capability(gpio_num_t gpio_num, gpio_drive_cap_t *strength);

/**
  * @brief 启用gpio pad hold功能。
  *
  * gpio pad hold功能可以在输入和输出模式下工作，但必须是支持输出的gpios。如果焊盘保持启用：在输出模式下：焊盘的输出电平将被强制锁定，无法更改。在输入模式下：无论输入信号的变化如何，读取的输入值都不会改变。
  *
  * 数字gpio的状态在深度睡眠期间无法保持，当芯片从深度睡眠中醒来时，它将恢复保持功能。如果数字gpio也需要在深度睡眠期间保持，则还应调用“gpio_Deep_sleep_hold_en”。
  *
  * 关闭电源或调用gpio_hold_dis将禁用此功能。
  *
  * @param gpio_num GPIO编号，仅支持支持输出的GPIO
  *
  * @return
  *     -ESP_OK成功
  *     -ESP_ERR_NOT_SUPPORTED不支持极板保持功能
  */
esp_err_t gpio_hold_en(gpio_num_t gpio_num);

/**
  * @brief 禁用gpio pad hold功能。
  *
  * 当芯片从深度睡眠中唤醒时，gpio将设置为默认模式，因此，如果调用此功能，gpio会输出默认级别。如果不想更改级别，则应在调用此函数之前将gpio配置为已知状态。e、 g.如果在深度睡眠期间将gpio18保持为高电平，则在芯片被唤醒并调用“gpio_hold_dis”后，gpio18将输出低电平（因为gpio18默认为输入模式）。如果不希望出现这种行为，应将gpio18配置为输出模式，并在调用“gpio_hold_dis”之前将其设置为高级别。
  *
  * @param gpio_num GPIO编号，仅支持支持输出的GPIO
  *
  * @return
  *     -ESP_OK成功
  *     -ESP_ERR_NOT_SUPPORTED不支持极板保持功能
  */
esp_err_t gpio_hold_dis(gpio_num_t gpio_num);

/**
  * @brief 在深度睡眠期间启用全数字gpio pad hold功能。
  *
  * 当芯片处于深度睡眠模式时，所有数字gpio将保持睡眠前的状态，而当芯片被唤醒时，数字gpio的状态将不会保持。请注意，pad hold功能仅在芯片处于深度睡眠模式时有效，在不处于睡眠模式时，即使您调用了此功能，也可以更改数字gpio状态。
  *
  * 关闭电源或调用gpio_hold_dis将禁用此功能，否则，只要芯片进入深度睡眠，数字gpio保持功能即可工作。
  */
void gpio_deep_sleep_hold_en(void);

/**
  * @brief 在深度睡眠期间禁用所有数字gpio pad hold功能。
  *
  */
void gpio_deep_sleep_hold_dis(void);

/**
  * @brief 通过IOMUX将焊盘输入设置为外围信号。
  * @param gpio_num 焊盘的GPIO编号。
  * @param signal_idx 要输入的外围信号id。“soc/gpio_sig_map.h”中的“*_IN_IDX”信号之一。
  */
void gpio_iomux_in(uint32_t gpio_num, uint32_t signal_idx);

/**
  * @brief 通过IOMUX将外围输出设置为GPIO焊盘。
  * @param gpio_num gpio_num gpio编号。
  * @param func 外围引脚到输出引脚的功能编号。“soc/io_max_reg.h”中指定引脚（X）的“FUNC_X_”之一。
  * @param oen_inv 如果需要反转输出启用，则为True，否则为False。
  */
void gpio_iomux_out(uint8_t gpio_num, int func, bool oen_inv);

#if SOC_GPIO_SUPPORT_FORCE_HOLD
/**
  * @brief 强制保持数字和rtc gpio垫。
  * @note GPIO强制保持，无论芯片处于睡眠模式还是唤醒模式。
  * */
esp_err_t gpio_force_hold_all(void);

/**
  * @brief 强制解锁数字和rtc gpio pad。
  * @note GPIO强制脱钩，无论芯片处于睡眠模式还是唤醒模式。
  * */
esp_err_t gpio_force_unhold_all(void);
#endif

#if SOC_GPIO_SUPPORT_SLP_SWITCH
/**
  * @brief 启用SLP_SEL以在睡眠时自动更改GPIO状态。
  * @param gpio_num 焊盘的GPIO编号。
  *
  * @return
  *     -ESP_OK成功
  *
  */
esp_err_t gpio_sleep_sel_en(gpio_num_t gpio_num);

/**
  * @brief 禁用SLP_SEL以在睡眠状态下自动更改GPIO状态。
  * @param gpio_num 焊盘的GPIO编号。
  *
  * @return
  *     -ESP_OK成功
  */
esp_err_t gpio_sleep_sel_dis(gpio_num_t gpio_num);

/**
 * @brief	 睡眠时GPIO设置方向
 *
 * 配置GPIO方向，如output_only、input_only和output_and_input
 *
 * @param  gpio_num  配置GPIO引脚编号，应为GPIO编号。如果要设置例如GPIO16的方向，gpio_num应为gpio_num_16（16）；
 * @param  mode GPIO方向
 *
 * @return
 *     -ESP_OK成功
 *     -ESP_ERR_INVALID_ARG GPIO错误
 */
esp_err_t gpio_sleep_set_direction(gpio_num_t gpio_num, gpio_mode_t mode);

/**
 * @brief  在睡眠状态下配置GPIO上拉/下拉电阻器
 *
 * 只有同时支持输入和输出的引脚具有集成的上拉和下拉电阻器。仅输入GPIO 34-39没有。
 *
 * @param  gpio_num GPIO编号。如果要为例如GPIO16设置上拉或下拉模式，gpio_num应为gpio_num_16（16）；
 * @param  pull GPIO上拉/下拉模式。
 *
 * @return
 *     -ESP_OK成功
 *     -ESP_ERR_INVALID_ARG：参数错误
 */
esp_err_t gpio_sleep_set_pull_mode(gpio_num_t gpio_num, gpio_pull_mode_t pull);
#endif

#if SOC_GPIO_SUPPORT_DEEPSLEEP_WAKEUP

#define GPIO_IS_DEEP_SLEEP_WAKEUP_VALID_GPIO(gpio_num)        ((gpio_num & ~SOC_GPIO_DEEP_SLEEP_WAKEUP_VALID_GPIO_MASK) == 0)

/**
 * @brief 启用GPIO深度睡眠唤醒功能。
 *
 * @param gpio_num GPIO编号。
 *
 * @param intr_type GPIO唤醒类型。只能使用GPIO_INTR_LOW_LEVEL或GPIO_INTR_HIGH_LEVEL。
 *
 * @note 由SDK调用。用户不应在APP中直接调用此功能。
 *
 * @return
 *     -ESP_OK成功
 *     -ESP_ERR_INVALID_ARG参数错误
 */
esp_err_t gpio_deep_sleep_wakeup_enable(gpio_num_t gpio_num, gpio_int_type_t intr_type);

/**
 * @brief 禁用GPIO深度睡眠唤醒功能。
 *
 * @param gpio_num GPIO编号
 *
 * @return
 *     -ESP_OK成功
 *     -ESP_ERR_INVALID_ARG参数错误
 */
esp_err_t gpio_deep_sleep_wakeup_disable(gpio_num_t gpio_num);

#endif

#ifdef __cplusplus
}
#endif

