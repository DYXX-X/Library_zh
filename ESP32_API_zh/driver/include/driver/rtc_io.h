/*
 * SPDX文件版权文本：2015-2021浓缩咖啡系统（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */

#ifndef _DRIVER_RTC_GPIO_H_
#define _DRIVER_RTC_GPIO_H_

#include <stdint.h>
#include "esp_err.h"
#include "soc/soc_caps.h"
#include "soc/rtc_io_periph.h"
#include "hal/rtc_io_types.h"
#include "driver/gpio.h"


#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 确定指定的GPIO是否为有效的RTC GPIO。
 *
 * @param gpio_num GPIO编号
 * @return 如果GPIO对RTC GPIO使用有效，则为true。否则为false。
 */
static inline bool rtc_gpio_is_valid_gpio(gpio_num_t gpio_num)
{
#if SOC_RTCIO_INPUT_OUTPUT_SUPPORTED
    return (gpio_num < GPIO_PIN_COUNT && rtc_io_num_map[gpio_num] >= 0);
#else
    return false;
#endif
}

#define RTC_GPIO_IS_VALID_GPIO(gpio_num) rtc_gpio_is_valid_gpio(gpio_num) // 已弃用，请使用rtc_gpio_is_valid_gpio（）

#if SOC_RTCIO_INPUT_OUTPUT_SUPPORTED
/**
 * @brief 通过gpio编号获取RTC IO索引编号。
 *
 * @param gpio_num GPIO编号
 * @return >=0：rtcio索引。
 *        -1：gpio不是rtcio。
 */
static inline int rtc_io_number_get(gpio_num_t gpio_num)
{
    return rtc_io_num_map[gpio_num];
}

/**
 * @brief 将GPIO初始化为RTC GPIO
 *
 * 初始化模拟函数的焊盘时，必须调用此函数。
 *
 * @param  gpio_num GPIO编号（例如GPIO_NUM_12）
 *
 * @return
 *     -ESP_OK成功
 *     -ESP_ERR_INVALID_ARG GPIO不是RTC IO
 */
esp_err_t rtc_gpio_init(gpio_num_t gpio_num);

/**
 * @brief 将GPIO初始化为数字GPIO
 *
 * @param  gpio_num GPIO编号（例如GPIO_NUM_12）
 *
 * @return
 *     -ESP_OK成功
 *     -ESP_ERR_INVALID_ARG GPIO不是RTC IO
 */
esp_err_t rtc_gpio_deinit(gpio_num_t gpio_num);

/**
 * @brief 获取RTC IO输入电平
 *
 * @param  gpio_num GPIO编号（例如GPIO_NUM_12）
 *
 * @return
 *     -1高级
 *     -0低电平
 *     -ESP_ERR_INVALID_ARG GPIO不是RTC IO
 */
uint32_t rtc_gpio_get_level(gpio_num_t gpio_num);

/**
 * @brief 设置RTC IO输出电平
 *
 * @param  gpio_num GPIO编号（例如GPIO_NUM_12）
 * @param  level 输出电平
 *
 * @return
 *     -ESP_OK成功
 *     -ESP_ERR_INVALID_ARG GPIO不是RTC IO
 */
esp_err_t rtc_gpio_set_level(gpio_num_t gpio_num, uint32_t level);

/**
 * @brief    RTC GPIO设置方向
 *
 * 配置RTC GPIO方向，例如仅输出、仅输入、输出和输入。
 *
 * @param  gpio_num GPIO编号（例如GPIO_NUM_12）
 * @param  mode GPIO方向
 *
 * @return
 *     -ESP_OK成功
 *     -ESP_ERR_INVALID_ARG GPIO不是RTC IO
 */
esp_err_t rtc_gpio_set_direction(gpio_num_t gpio_num, rtc_gpio_mode_t mode);

/**
 * @brief RTC GPIO在深度睡眠模式下设置方向或禁用睡眠状态（默认）。在某些应用场景中，IO需要在深度睡眠期间具有其他状态。
 *
 * 注意：ESP32支持INPUT_ONLY模式。ESP32S2支持INPUT_ONLY、OUTPUT_ONLY、INPUT_OUTPUT模式。
 *
 * @param  gpio_num GPIO编号（例如GPIO_NUM_12）
 * @param  mode GPIO方向
 *
 * @return
 *     -ESP_OK成功
 *     -ESP_ERR_INVALID_ARG GPIO不是RTC IO
 */
esp_err_t rtc_gpio_set_direction_in_sleep(gpio_num_t gpio_num, rtc_gpio_mode_t mode);

/**
 * @brief  RTC GPIO上拉启用
 *
 * 此功能仅适用于RTC IO。通常，调用gpio_pullup_en，这将同时适用于普通gpio和RTC IO。
 *
 * @param  gpio_num GPIO编号（例如GPIO_NUM_12）
 *
 * @return
 *     -ESP_OK成功
 *     -ESP_ERR_INVALID_ARG GPIO不是RTC IO
 */
esp_err_t rtc_gpio_pullup_en(gpio_num_t gpio_num);

/**
 * @brief  RTC GPIO下拉启用
 *
 * 此功能仅适用于RTC IO。通常，调用gpio_pulldown_en，这将同时适用于普通gpio和RTC IO。
 *
 * @param  gpio_num GPIO编号（例如GPIO_NUM_12）
 *
 * @return
 *     -ESP_OK成功
 *     -ESP_ERR_INVALID_ARG GPIO不是RTC IO
 */
esp_err_t rtc_gpio_pulldown_en(gpio_num_t gpio_num);

/**
 * @brief  RTC GPIO上拉禁用
 *
 * 此功能仅适用于RTC IO。通常，调用gpio_pullup_dis，这将同时适用于普通gpio和RTC IO。
 *
 * @param  gpio_num GPIO编号（例如GPIO_NUM_12）
 *
 * @return
 *     -ESP_OK成功
 *     -ESP_ERR_INVALID_ARG GPIO不是RTC IO
 */
esp_err_t rtc_gpio_pullup_dis(gpio_num_t gpio_num);

/**
 * @brief  RTC GPIO下拉禁用
 *
 * 此功能仅适用于RTC IO。通常，调用gpio_pulldown_dis，这将同时适用于普通gpio和RTC IO。
 *
 * @param  gpio_num GPIO编号（例如GPIO_NUM_12）
 *
 * @return
 *     -ESP_OK成功
 *     -ESP_ERR_INVALID_ARG GPIO不是RTC IO
 */
esp_err_t rtc_gpio_pulldown_dis(gpio_num_t gpio_num);

/**
 * @brief 设置RTC GPIO焊盘驱动能力
 *
 * @param gpio_num GPIO编号，仅支持输出GPIO
 * @param strength 衬垫的驱动能力
 *
 * @return
 *     -ESP_OK成功
 *     -ESP_ERR_INVALID_ARG参数错误
 */
esp_err_t rtc_gpio_set_drive_capability(gpio_num_t gpio_num, gpio_drive_cap_t strength);

/**
 * @brief 获取RTC GPIO焊盘驱动功能
 *
 * @param gpio_num GPIO编号，仅支持输出GPIO
 * @param strength 接受极板驱动能力的指针
 *
 * @return
 *     -ESP_OK成功
 *     -ESP_ERR_INVALID_ARG参数错误
 */
esp_err_t rtc_gpio_get_drive_capability(gpio_num_t gpio_num, gpio_drive_cap_t* strength);

#endif // SOC_RTCIO_INPUT_OUTPUT_SUPPORTED

#if SOC_RTCIO_HOLD_SUPPORTED

/**
 * @brief 启用RTC IO板上的保持功能
 *
 * 启用HOLD（保持）功能将使焊盘锁定输入启用、输出启用、输出值、功能、驱动强度值的当前值。当进入浅睡眠或深睡眠模式时，此功能非常有用，以防止引脚配置发生变化。
 *
 * @param gpio_num GPIO编号（例如GPIO_NUM_12）
 * @return
 *     -ESP_OK成功
 *     -ESP_ERR_INVALID_ARG GPIO不是RTC IO
 */
esp_err_t rtc_gpio_hold_en(gpio_num_t gpio_num);

/**
 * @brief 禁用RTC IO板上的保持功能
 *
 * 禁用保持功能将允许焊盘从RTC_IO外围设备接收输入启用、输出启用、输出值、功能和驱动强度的值。
 *
 * @param gpio_num GPIO编号（例如GPIO_NUM_12）
 * @return
 *     -ESP_OK成功
 *     -ESP_ERR_INVALID_ARG GPIO不是RTC IO
 */
esp_err_t rtc_gpio_hold_dis(gpio_num_t gpio_num);

/**
 * @brief 从RTC IO断开内部电路的辅助功能此功能禁用输入、输出、上拉、下拉，并启用RTC IO的保持功能。如果RTC IO需要在深度睡眠状态下从内部电路断开，请使用此功能，以最大限度地减少泄漏电流。
 *
 * 特别是，对于ESP32-WROVER模块，在进入深度睡眠之前调用rtc_gpio_isolate（gpio_NUM_12），以减少深度睡眠电流。
 *
 * @param gpio_num GPIO编号（例如GPIO_NUM_12）。
 * @return
 *      -成功时ESP_OK
 *      -如果GPIO不是RTC IO，则为ESP_ERR_INVALID_ARG
 */
esp_err_t rtc_gpio_isolate(gpio_num_t gpio_num);

/**
 * @brief 启用所有RTC IO的强制保持信号
 *
 * 每个RTC垫都有来自RTC控制器的“强制保持”输入信号。如果设置了该信号，则焊盘锁存输入使能、功能、输出使能和来自RTC多路复用器的其他信号的当前值。对于用于EXT1唤醒的引脚，在进入深度睡眠之前启用强制保持信号。
 */
esp_err_t rtc_gpio_force_hold_all(void);

/**
 * @brief 禁用所有RTC IO的强制保持信号
 */
esp_err_t rtc_gpio_force_hold_dis_all(void);

#endif // SOC_RTCIO_HOLD_SUPPORTED

#if SOC_RTCIO_WAKE_SUPPORTED

/**
 * @brief 使用特定GPIO从睡眠模式唤醒
 * @param gpio_num  GPIO编号
 * @param intr_type  高电平唤醒（GPIO_INTR_high_level）或低电平唤醒（GPIO_INTR_low_LLEVEL）
 * @return
 *      -成功时ESP_OK
 *      -如果gpio_num不是RTC IO，或intr_type不是gpio_intr_HIGH_LEVEL、gpio_intr.LOW_LEVEL之一，则为ESP_ERR_INVALID_ARG。
 */
esp_err_t rtc_gpio_wakeup_enable(gpio_num_t gpio_num, gpio_int_type_t intr_type);

/**
 * @brief 使用特定GPIO禁用从睡眠模式唤醒
 * @param gpio_num  GPIO编号
 * @return
 *      -成功时ESP_OK
 *      -如果gpio_num不是RTC IO，则ESP_ERR_INVALID_ARG
 */
esp_err_t rtc_gpio_wakeup_disable(gpio_num_t gpio_num);

#endif // SOC_RTCIO_WAKE_SUPPORTED

#ifdef __cplusplus
}
#endif

#endif

