/*
 * SPDX文件版权文本：2015-2021浓缩咖啡系统（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */

#pragma once

#include <stdint.h>
#include "esp_err.h"

#include "hal/touch_sensor_types.h"
#include "hal/gpio_types.h"

#include "soc/soc_caps.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 用于EXT1唤醒模式的逻辑功能。
 */
typedef enum {
    ESP_EXT1_WAKEUP_ALL_LOW = 0,    //!< 当所有选定GPIO变低时唤醒芯片
    ESP_EXT1_WAKEUP_ANY_HIGH = 1    //!< 当任何选定的GPIO变高时唤醒芯片
} esp_sleep_ext1_wakeup_mode_t;

#if SOC_GPIO_SUPPORT_DEEPSLEEP_WAKEUP
typedef enum {
    ESP_GPIO_WAKEUP_GPIO_LOW = 0,
    ESP_GPIO_WAKEUP_GPIO_HIGH = 1
} esp_deepsleep_gpio_wake_up_mode_t;
#endif

/**
 * @brief 可以在睡眠模式下关闭电源的电源域
 */
typedef enum {
    ESP_PD_DOMAIN_RTC_PERIPH,      //!< RTC IO、传感器和ULP协处理器
    ESP_PD_DOMAIN_RTC_SLOW_MEM,    //!< RTC慢速内存
    ESP_PD_DOMAIN_RTC_FAST_MEM,    //!< RTC快速存储器
    ESP_PD_DOMAIN_XTAL,            //!< XTAL振荡器
#if SOC_PM_SUPPORT_CPU_PD
    ESP_PD_DOMAIN_CPU,             //!< CPU核心
#endif
    ESP_PD_DOMAIN_RTC8M,           //!< 内置8M振荡器
    ESP_PD_DOMAIN_VDDSDIO,         //!< VDD_SDIO
    ESP_PD_DOMAIN_MAX              //!< 域的数量
} esp_sleep_pd_domain_t;

/**
 * @brief 断电选项
 */
typedef enum {
    ESP_PD_OPTION_OFF,      //!< 在睡眠模式下关闭电源域
    ESP_PD_OPTION_ON,       //!< 在睡眠模式下保持电源域启用
    ESP_PD_OPTION_AUTO      //!< 如果某个唤醒选项需要，请在睡眠模式下启用电源域。否则关闭电源。
} esp_sleep_pd_option_t;

/**
 * @brief 睡眠唤醒原因
 */
typedef enum {
    ESP_SLEEP_WAKEUP_UNDEFINED,    //!< 在深度睡眠的情况下，重置不是由退出深度睡眠引起的
    ESP_SLEEP_WAKEUP_ALL,          //!< 不是唤醒原因，用于禁用具有esp_sleep_disable_wakeup_source的所有唤醒源
    ESP_SLEEP_WAKEUP_EXT0,         //!< 使用RTC_IO由外部信号引起的唤醒
    ESP_SLEEP_WAKEUP_EXT1,         //!< 使用RTC_CNTL由外部信号引起的唤醒
    ESP_SLEEP_WAKEUP_TIMER,        //!< 计时器引起的唤醒
    ESP_SLEEP_WAKEUP_TOUCHPAD,     //!< 触摸板引起的唤醒
    ESP_SLEEP_WAKEUP_ULP,          //!< ULP程序导致的唤醒
    ESP_SLEEP_WAKEUP_GPIO,         //!< GPIO引起的唤醒（仅限轻度睡眠）
    ESP_SLEEP_WAKEUP_UART,         //!< UART引起的唤醒（仅限浅睡眠）
    ESP_SLEEP_WAKEUP_WIFI,              //!< WIFI导致的唤醒（仅限轻度睡眠）
    ESP_SLEEP_WAKEUP_COCPU,             //!< COCPU int引起的唤醒
    ESP_SLEEP_WAKEUP_COCPU_TRAP_TRIG,   //!< COCPU崩溃导致的唤醒
    ESP_SLEEP_WAKEUP_BT,           //!< BT引起的唤醒（仅限轻度睡眠）
} esp_sleep_source_t;

/* 保留此类型定义以保持兼容性*/
typedef esp_sleep_source_t esp_sleep_wakeup_cause_t;

/**
 * @brief 禁用唤醒源
 *
 * 此函数用于停用定义为函数参数的源的唤醒触发器。
 *
 * @note 此功能不会修改RTC中的唤醒配置。它将在esp_sleep_start函数中执行。
 *
 * 请参阅文档/睡眠模式。首先了解详情。
 *
 * @param source -esp_sleep_source_t类型的要禁用的源的数量
 * @return
 *      -成功时ESP_OK
 *      -如果触发器未激活，则为ESP_ERR_INVALID_STATE
 */
esp_err_t esp_sleep_disable_wakeup_source(esp_sleep_source_t source);

#if SOC_ULP_SUPPORTED
/**
 * @brief 启用ULP协处理器唤醒
 * @note 在ESP32的第0版和第1版中，当RTC_PERIPH电源域强制通电（ESP_PD_OPTION_on）或使用ext0唤醒源时，无法使用ULP唤醒源。
 * @return
 *      -成功时ESP_OK
 *      -如果启用了额外的触摸电流（CONFIG_ESP32_RTC_EXT_CRYST_ADDIT_current），则为ESP_ERR_NOT_SUPPORTED。
 *      -如果未启用ULP协处理器或唤醒触发冲突，则为ESP_ERR_INVALID_STATE
 */
esp_err_t esp_sleep_enable_ulp_wakeup(void);

#endif // SOC_ULP_SUPPORTED

/**
 * @brief 启用计时器唤醒
 * @param time_in_us  唤醒前的时间，以微秒为单位
 * @return
 *      -成功时ESP_OK
 *      -如果值超出范围（TBD），则为ESP_ERR_INVALID_ARG
 */
esp_err_t esp_sleep_enable_timer_wakeup(uint64_t time_in_us);

#if SOC_TOUCH_SENSOR_NUM > 0

/**
 * @brief 启用触摸传感器唤醒
 *
 * @note 在ESP32的版本0和1中，当RTC_PERIPH电源域被强制通电（ESP_PD_OPTION_on）或使用ext0唤醒源时，不能使用触摸唤醒源。
 *
 * @note 触摸按钮的FSM模式应配置为定时器触发模式。
 *
 * @return
 *      -成功时ESP_OK
 *      -如果启用了额外的触摸电流（CONFIG_ESP32_RTC_EXT_CRYST_ADDIT_current），则为ESP_ERR_NOT_SUPPORTED。
 *      -如果唤醒触发冲突，则ESP_ERR_INVALID_STATE
 */
esp_err_t esp_sleep_enable_touchpad_wakeup(void);

/**
 * @brief 获取导致唤醒的触摸板
 *
 * 如果唤醒是由其他源引起的，则此函数将返回TOUCH_PAD_MAX；
 *
 * @return 导致唤醒的触摸板
 */
touch_pad_t esp_sleep_get_touchpad_wakeup_status(void);

#endif // SOC_TOUCH_SENSOR_NUM > 0

/**
 * @brief 如果GPIO编号有效用作唤醒源，则返回true。
 *
 * @note 对于具有RTC IO功能的SoC，这可以是任何有效的RTC IO输入引脚。
 *
 * @param gpio_num 测试唤醒源能力的GPIO数量
 *
 * @return 如果此GPIO号码将被接受为睡眠唤醒源，则为True。
 */
bool esp_sleep_is_valid_wakeup_gpio(gpio_num_t gpio_num);

#if SOC_PM_SUPPORT_EXT_WAKEUP

/**
 * @brief 使用引脚启用唤醒
 *
 * 此功能使用RTC_IO外围设备的外部唤醒功能。只有当RTC外设在睡眠期间保持打开时，它才会工作。
 *
 * 此功能可监控任何RTC IO引脚。一旦引脚转换到电平参数给定的状态，芯片将被唤醒。
 *
 * @note 此功能不会修改引脚配置。在进入睡眠模式之前，该引脚配置为esp_sleep_start。
 *
 * @note 在ESP32的修订版0和1中，ext0唤醒源不能与触摸或ULP唤醒源一起使用。
 *
 * @param gpio_num  GPIO编号用作唤醒源。只能使用具有RTC功能的GPIO：0,2,4,12-15,25-27,32-39。
 * @param level  将触发唤醒的输入电平（0=低，1=高）
 * @return
 *      -成功时ESP_OK
 *      -如果所选GPIO不是RTC GPIO或模式无效，则为ESP_ERR_INVALID_ARG
 *      -如果唤醒触发冲突，则ESP_ERR_INVALID_STATE
 */
esp_err_t esp_sleep_enable_ext0_wakeup(gpio_num_t gpio_num, int level);

/**
 * @brief 使用多个引脚启用唤醒
 *
 * 此功能使用RTC控制器的外部唤醒功能。即使RTC外设在睡眠期间关闭，它也能工作。
 *
 * 此功能可以监控RTC IO中的任何数量的引脚。一旦任何选定的引脚进入模式参数给定的状态，芯片将被唤醒。
 *
 * @note 此功能不会修改引脚配置。在进入睡眠模式之前，引脚配置为esp_sleep_start。
 *
 * @note RTC外设关闭时，内部上拉和下拉不起作用。在这种情况下，需要添加外部电阻器。或者，可以使用esp_sleep_pd_config功能启用RTC外围设备（以及上拉/下拉）。
 *
 * @param mask  将导致唤醒的GPIO编号的位掩码。此位图中只能使用具有RTC功能的GPIO：0,2,4,12-15,25-27,32-39。
 * @param mode 选择用于确定唤醒条件的逻辑功能：
 *            -ESP_EXT1_WAKEUP_ALL_LOW：当所有选定的GPIO均为低电平时唤醒
 *            -ESP_EXT1_WAKEUP_ANY_HIGH：当任何选定的GPIO为高时唤醒
 * @return
 *      -成功时ESP_OK
 *      -如果任何选定的GPIO不是RTC GPIO或模式无效，则为ESP_ERR_INVALID_ARG
 */
esp_err_t esp_sleep_enable_ext1_wakeup(uint64_t mask, esp_sleep_ext1_wakeup_mode_t mode);

#endif // SOC_PM_SUPPORT_EXT_WAKEUP

#if SOC_GPIO_SUPPORT_DEEPSLEEP_WAKEUP
/**
 * @brief 使用特定gpio引脚启用唤醒
 *
 * 此功能使IO引脚能够将芯片从深度睡眠中唤醒
 *
 * @note 此功能不会修改引脚配置。在进入睡眠模式之前，引脚配置为esp_sleep_start。
 *
 * @note 在使用此函数之前，您不需要注意上拉或下拉，因为这将在esp_sleep_start中根据您提供的参数掩码完成。顺便说一下，当您使用低电平唤醒芯片时，我们强烈建议您添加外部寄存器（上拉）。
 *
 * @param gpio_pin_mask  将导致唤醒的GPIO编号的位掩码。此位图中只能使用具有RTC功能的GPIO。
 * @param mode 选择用于确定唤醒条件的逻辑功能：
 *            -ESP_GPIO_WAKEUP_GPIO_LOW：当GPIO变低时唤醒。
 *            -ESP_GPIO_WAKEUP_GPIO_HIGH：当GPIO变高时唤醒。
 * @return
 *      -成功时ESP_OK
 *      -如果gpio num大于5或模式无效，
 */
esp_err_t esp_deep_sleep_enable_gpio_wakeup(uint64_t gpio_pin_mask, esp_deepsleep_gpio_wake_up_mode_t mode);
#endif
/**
 * @brief 使用GPIO启用轻睡眠唤醒
 *
 * 每个GPIO支持唤醒功能，可在低电平或高电平触发。与EXT0和EXT1唤醒源不同，此方法可用于所有IO：RTC IO和数字IO。不过，它只能用来从浅睡眠中醒来。
 *
 * 要启用唤醒，首先调用gpio_wakeup_enable，为用于唤醒的每个gpio指定gpio编号和唤醒级别。然后调用此函数以启用唤醒功能。
 *
 * @note 在ESP32的第0版和第1版中，GPIO唤醒源不能与触摸或ULP唤醒源一起使用。
 *
 * @return
 *      -成功时ESP_OK
 *      -如果唤醒触发冲突，则ESP_ERR_INVALID_STATE
 */
esp_err_t esp_sleep_enable_gpio_wakeup(void);

/**
 * @brief 使用UART启用从浅睡眠唤醒
 *
 * 使用uart_set_wakeup_threshold函数配置uart唤醒阈值。
 *
 * 从浅睡眠中唤醒需要一些时间，因此应用程序无法接收发送到UART的每个字符。
 *
 * @note ESP32不支持从UART2唤醒。
 *
 * @param uart_num  要从中唤醒的UART端口
 * @return
 *      -成功时ESP_OK
 *      -如果不支持从给定UART唤醒，则为ESP_ERR_INVALID_ARG
 */
esp_err_t esp_sleep_enable_uart_wakeup(int uart_num);

/**
 * @brief 启用WiFi MAC唤醒
 * @return
 *      -成功时ESP_OK
 */
esp_err_t esp_sleep_enable_wifi_wakeup(void);

/**
 * @brief 禁用WiFi MAC唤醒
 * @return
 *      -成功时ESP_OK
 */
esp_err_t esp_sleep_disable_wifi_wakeup(void);

/**
 * @brief 获取导致唤醒的GPIO的位掩码（ext1）
 *
 * 如果唤醒是由其他源引起的，则此函数将返回0。
 *
 * @return 位掩码，如果GPIOn导致唤醒，将设置bit（n）
 */
uint64_t esp_sleep_get_ext1_wakeup_status(void);

#if SOC_GPIO_SUPPORT_DEEPSLEEP_WAKEUP
/**
 * @brief 获取导致唤醒的gpio的位掩码（gpio）
 *
 * 如果唤醒是由其他源引起的，则此函数将返回0。
 *
 * @return 位掩码，如果GPIOn导致唤醒，将设置bit（n）
 */
uint64_t esp_sleep_get_gpio_wakeup_status(void);
#endif //SOC_GPIO_SUPPORT_DEEPSLEEP_WAKEUP

/**
 * @brief 为处于睡眠模式的RTC电源域设置断电模式
 *
 * 如果未使用此API设置，则所有电源域默认为ESP_PD_OPTION_AUTO。
 *
 * @param domain  要配置的电源域
 * @param option  断电选项（ESP_PD_option_OFF、ESP_PD_option_ON或ESP_PD_option_AUTO）
 * @return
 *      -成功时ESP_OK
 *      -如果任一参数超出范围，则返回ESP_ERR_INVALID_ARG
 */
esp_err_t esp_sleep_pd_config(esp_sleep_pd_domain_t domain,
                                   esp_sleep_pd_option_t option);

/**
 * @brief 使用配置的唤醒选项进入深度睡眠
 *
 * 此函数不返回。
 */
void esp_deep_sleep_start(void) __attribute__((noreturn));

/**
 * @brief 使用配置的唤醒选项进入浅睡眠
 *
 * @return
 *  -成功时ESP_OK（唤醒后返回）
 *  -如果WiFi或BT未停止，则为ESP_ERR_INVALID_STATE
 */
esp_err_t esp_light_sleep_start(void);

/**
 * @brief 进入深度睡眠模式
 *
 * 设备将在深度睡眠时间后自动唤醒。在唤醒后，设备调用深度睡眠唤醒存根，然后继续加载应用程序。
 *
 * 对该函数的调用相当于对esp_deep_sleep_enable_timer_wakeup的调用，然后是对esp_deep _sleep_start的调用。
 *
 * esp_deep_sleep不会优雅地关闭WiFi、BT和更高级别的协议连接。确保调用了相关的WiFi和BT堆栈功能，以关闭所有连接并取消初始化外围设备。其中包括：
 *     -esp_bluedroid_disable
 *     -esp_bt_controller_disable（esp_bt_控制器禁用）
 *     -esp_wifi_stop（esp_wifi-stop）
 *
 * 此函数不返回。
 *
 * @note 如果深度睡眠时间设置为0，设备将立即唤醒
 *
 * @param time_in_us  深度睡眠时间，单位：微秒
 */
void esp_deep_sleep(uint64_t time_in_us) __attribute__((noreturn));


/**
 * @brief 获取导致从睡眠中醒来的唤醒源
 *
 * @return 从上次睡眠中醒来的原因（深睡眠或浅睡眠）
 */
esp_sleep_wakeup_cause_t esp_sleep_get_wakeup_cause(void);


/**
 * @brief 从深度睡眠唤醒时运行的默认存根。
 *
 * 允许在软件引导加载程序或ESP-IDF应用程序启动之前，在从睡眠中醒来时立即执行代码。
 *
 * 该函数是弱链接的，因此您可以实现自己的版本，以便在芯片从睡眠中醒来时立即运行代码。
 *
 * 请参阅文档/深度睡眠存根。首先了解详情。
 */
void esp_wake_deep_sleep(void);

/**
 * @brief 存根从睡眠中唤醒时运行的函数类型。
 *
 */
typedef void (*esp_deep_sleep_wake_stub_fn_t)(void);

/**
 * @brief 在运行时安装一个新的存根，以在深度睡眠唤醒时运行
 *
 * 如果实现esp_wake_deep_sleep（），则无需调用此函数。
 *
 * 但是，可以调用此函数来替换不同的深度睡眠存根。任何用作深度睡眠存根的函数都必须标记为RTC_IRAM_ATTR，并且必须遵守为esp_wake_deep_sleep（）提供的相同规则。
 */
void esp_set_deep_sleep_wake_stub(esp_deep_sleep_wake_stub_fn_t new_stub);

/**
 * @brief 从深度睡眠存根获取当前唤醒
 * @return 返回深度睡眠存根的当前唤醒，如果未安装存根，则返回NULL。
 */
esp_deep_sleep_wake_stub_fn_t esp_get_deep_sleep_wake_stub(void);

/**
 *  @brief 默认esp-idf提供了esp_wake_deep_sleep（）存根。
 *
 *  请参阅文档/深度睡眠存根。首先了解详情。
 */
void esp_default_wake_deep_sleep(void);

/**
 * @brief 在深度睡眠后禁用从ROM代码记录。
 *
 * 使用RTC_STORE4。
 */
void esp_deep_sleep_disable_rom_logging(void);

#ifdef SOC_PM_SUPPORT_CPU_PD
/**
 * @brief CPU断电低级初始化
 *
 * @param enable  在轻睡眠期间启用或禁用CPU断电
 * @return
 *      -成功时ESP_OK
 *      -ESP_ERR_NO_MEM没有足够的保留内存
 */
esp_err_t esp_sleep_cpu_pd_low_init(bool enable);
#endif

#if SOC_GPIO_SUPPORT_SLP_SWITCH
/**
 * @brief 配置以隔离处于睡眠状态的所有GPIO引脚
 */
void esp_sleep_config_gpio_isolate(void);

/**
 * @brief 启用或禁用GPIO引脚状态在睡眠状态和唤醒状态之间切换。
 * @param enable 决定是否切换状态
 */
void esp_sleep_enable_gpio_switch(bool enable);
#endif

#if CONFIG_MAC_BB_PD
/**
 * @brief 存根运行mac bb关机的函数类型。
 */
typedef void (* mac_bb_power_down_cb_t)(void);

/**
 * @brief 存根运行mac bb加电的函数类型。
 */
typedef void (* mac_bb_power_up_cb_t)(void);

/**
 * @brief  注册mac bb掉电回调。
 * @param  cb mac bb掉电回调。
 * @return
 *  -成功时ESP_OK
 */
esp_err_t esp_register_mac_bb_pd_callback(mac_bb_power_down_cb_t cb);

/**
 * @brief  取消注册mac bb关机回调。
 * @param  cb mac bb掉电回调。
 * @return
 *  -成功时ESP_OK
 */
esp_err_t esp_unregister_mac_bb_pd_callback(mac_bb_power_down_cb_t cb);

/**
 * @brief  注册mac bb加电回调。
 * @param  cb mac bb加电回调。
 * @return
 *  -成功时ESP_OK
 */
esp_err_t esp_register_mac_bb_pu_callback(mac_bb_power_up_cb_t cb);

/**
 * @brief  取消注册mac bb加电回调。
 * @param  cb mac bb加电回调。
 * @return
 *  -成功时ESP_OK
 */
esp_err_t esp_unregister_mac_bb_pu_callback(mac_bb_power_up_cb_t cb);
#endif

#ifdef __cplusplus
}
#endif

