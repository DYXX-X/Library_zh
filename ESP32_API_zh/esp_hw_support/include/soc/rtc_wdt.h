/*
 * SPDX文件版权文本：2018-2021浓缩咖啡系统（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */

/* 建议使用API RTC_WDT。1） 设置和启用rtc_wdt：
@代码
    rtc_wdt_protect_off（）；
    rtc_wdt_disable（）；
    rtc_wdt_set_length_of_reset_signal（rtc_wdt_SYS_reset_SIG，rtc_wdt_length_3_2us）；
    rtc_wdt_set_stage（rtc_wdt_STAGE0，rtc_wdt_stage_ACTION_RESET_SYSTEM）//RTC_WDT_STAGE_ACTION_RESET_SYSTEM或RTC_WDT-STAGE_ACTION _RESET_RTC
    rtc_wdt_set_time（rtc_wdt_STAGE0，7000）；//超时rtd_wdt 7000ms。
    rtc_wdt_enable（）；
    rtc_wdt_protect_on（）；
 @结束代码

* 如果使用此选项RTC_WDT_STAGE_ACTION_RESET_SYSTEM，则重置后可以看到这些消息。它们可以帮助了解触发WDT时CPU的位置。W（30）引导：PRO CPU已被WDT重置。W（30）引导：WDT重置信息：PRO CPU PC=0x400xxxxx…发生的功能

W（31）引导：WDT重置信息：APP CPU PC=0x400xxxxx…发生的功能

* 如果使用此选项RTC_WDT_STAGE_ACTION_RESET_RTC，则您将看到消息（rst:0x10（RTCWDT_RTC_RESET），boot:0x13（SPI_FAST_FLASH_boot）），而无需描述发生时CPU的位置。

2） 重置rtc_wdt计数器：
@代码
    rtc_wdt_feed（）；
@结束代码

3） 禁用rtc_wdt：
@代码
    rtc_wdt_disable（）；
@结束代码
 */

#pragma once
#include <stdint.h>
#include <stdbool.h>
#include "soc/rtc_periph.h"
#include "esp_err.h"

#ifdef __cplusplus
extern "C"
{
#endif

///rtc看门狗阶段列表。WDT有4个阶段。
typedef enum {
    RTC_WDT_STAGE0 = 0,     /*!< 阶段0*/
    RTC_WDT_STAGE1 = 1,     /*!< 第1阶段*/
    RTC_WDT_STAGE2 = 2,     /*!< 第2阶段*/
    RTC_WDT_STAGE3 = 3      /*!< 第3阶段*/
} rtc_wdt_stage_t;

///操作列表。当阶段时间到期时，将触发此操作。
typedef enum {
    RTC_WDT_STAGE_ACTION_OFF            = RTC_WDT_STG_SEL_OFF,          /*!< 残废此阶段对系统没有影响。*/
    RTC_WDT_STAGE_ACTION_INTERRUPT      = RTC_WDT_STG_SEL_INT,          /*!< 触发中断。当阶段到期时，将触发中断。*/
    RTC_WDT_STAGE_ACTION_RESET_CPU      = RTC_WDT_STG_SEL_RESET_CPU,    /*!< 重置CPU核心。*/
    RTC_WDT_STAGE_ACTION_RESET_SYSTEM   = RTC_WDT_STG_SEL_RESET_SYSTEM, /*!< 重置主系统包括CPU和所有外围设备。RTC是一个例外，它不会被重置。*/
    RTC_WDT_STAGE_ACTION_RESET_RTC      = RTC_WDT_STG_SEL_RESET_RTC     /*!< 重置主系统和RTC。*/
} rtc_wdt_stage_action_t;

///复位信号类型
typedef enum {
    RTC_WDT_SYS_RESET_SIG = 0,     /*!< 系统复位信号长度选择*/
    RTC_WDT_CPU_RESET_SIG = 1      /*!< CPU复位信号长度选择*/
} rtc_wdt_reset_sig_t;

///复位信号长度
typedef enum {
    RTC_WDT_LENGTH_100ns = 0,     /*!< 100纳秒*/
    RTC_WDT_LENGTH_200ns = 1,     /*!< 200纳秒*/
    RTC_WDT_LENGTH_300ns = 2,     /*!< 300纳秒*/
    RTC_WDT_LENGTH_400ns = 3,     /*!< 400纳秒*/
    RTC_WDT_LENGTH_500ns = 4,     /*!< 500纳秒*/
    RTC_WDT_LENGTH_800ns = 5,     /*!< 800纳秒*/
    RTC_WDT_LENGTH_1_6us = 6,     /*!< 1.6美元*/
    RTC_WDT_LENGTH_3_2us = 7      /*!< 3.2我们*/
} rtc_wdt_length_sig_t;

/**
 * @brief 获取rtc_wdt的保护状态。
 *
 * @return
 *         -如果设置了RTC_WDT的保护，则为True
 */
bool rtc_wdt_get_protect_status(void);

/**
 * @brief 设置rtc_wdt的保护。
 */
void rtc_wdt_protect_on(void);

/**
 * @brief 重置rtc_wdt的保护。
 */
void rtc_wdt_protect_off(void);

/**
 * @brief 启用rtc_wdt。
 */
void rtc_wdt_enable(void);

/**
 * @brief 启用WDT的闪存启动保护程序。
 *
 * 不建议在应用程序中使用它。添加此函数是为了与旧的引导加载程序兼容。在bootloader中或使用rtc_wdt_disable（）函数禁用此模式。
 */
void rtc_wdt_flashboot_mode_enable(void);

/**
 * @brief 禁用rtc_wdt。
 */
void rtc_wdt_disable(void);

/**
 * @brief 重置计数器rtc_wdt。
 *
 * 它返回到阶段0，其到期计数器从0重新启动。
 */
void rtc_wdt_feed(void);

/**
 * @brief 设置所需阶段的时间。
 *
 * @param[in] stage rtc_wdt阶段。
 * @param[in] timeout_ms 此阶段超时。
 *
 * @return
 *         -成功时ESP_OK
 *         -ESP_ERR_INVALID_ARG如果阶段具有无效值
 */
esp_err_t rtc_wdt_set_time(rtc_wdt_stage_t stage, unsigned int timeout_ms);

/**
 * @brief 获取所需阶段的超时设置。
 *
 * @param[in]  stage rtc_wdt阶段。
 * @param[out] timeout_ms 此阶段的超时设置。（不是经过的时间）。
 *
 * @return
 *         -成功时ESP_OK
 *         -ESP_ERR_INVALID_ARG如果阶段具有无效值
 */
esp_err_t rtc_wdt_get_timeout(rtc_wdt_stage_t stage, unsigned int* timeout_ms);

/**
 * @brief 为所需阶段设置操作。
 *
 * @param[in] stage rtc_wdt阶段。
 * @param[in] stage_sel 此阶段的操作。当阶段时间到期时，将触发此操作。
 *
 * @return
 *         -成功时ESP_OK
 *         -ESP_ERR_INVALID_ARG如果stage或stage_sel具有无效值
 */
esp_err_t rtc_wdt_set_stage(rtc_wdt_stage_t stage, rtc_wdt_stage_action_t stage_sel);

/**
 * @brief 设置重置信号的长度。
 *
 * @param[in] reset_src 复位信号类型。
 * @param[in] reset_signal_length 复位信号的长度。
 *
 * @return
 *         -成功时ESP_OK
 *         -ESP_ERR_INVALID_ARG如果reset_src或reset_signal_length具有无效值
 */
esp_err_t rtc_wdt_set_length_of_reset_signal(rtc_wdt_reset_sig_t reset_src, rtc_wdt_length_sig_t reset_signal_length);

/**
 * @brief 如果启用了rtc_wdt，则返回true。
 *
 * @return
 *         -真rtc_wdt已启用
 */
bool rtc_wdt_is_on(void);

#ifdef __cplusplus
}
#endif

