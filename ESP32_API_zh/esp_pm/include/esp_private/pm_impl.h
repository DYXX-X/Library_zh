// 版权所有2016-2017 Espressif Systems（上海）私人有限公司
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

#pragma once

/**
 * @file esp_私有/pm_impl.h
 *
 * 该头文件定义了PM锁定功能（PM_locks.c）和芯片特定电源管理（DFS/轻睡眠）实现之间的接口。
 */

#include "soc/rtc.h"
#include "esp_pm.h"
#include "esp_timer.h"
#include "sdkconfig.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * 这是实现支持的可能电源模式的枚举
 */
typedef enum {
    PM_MODE_LIGHT_SLEEP,//!< 轻度睡眠
    PM_MODE_APB_MIN,    //!< 空闲（无CPU频率或APB频率锁定）
    PM_MODE_APB_MAX,    //!< 最大APB频率模式
    PM_MODE_CPU_MAX,    //!< 最大CPU频率模式
    PM_MODE_COUNT       //!< 项目数量
} pm_mode_t;

/**
 * @brief 获取某个锁对应的模式
 * @param type 锁定类型
 * @param arg 此锁的参数值（传递给esp_pm_lock_create）
 * @return 满足锁约束的最低功耗模式
 */
pm_mode_t esp_pm_impl_get_mode(esp_pm_lock_type_t type, int arg);

/**
 * @brief 通过电源模式获取CPU时钟频率
 * @param mode 功率模式
 * @return CPU时钟频率
 */
int esp_pm_impl_get_cpu_freq(pm_mode_t mode);

/**
 * 如果启用了分析，则此数据类型将用于存储微秒时间戳。
 */
typedef int64_t pm_time_t;

/**
 * 请参见\ref esp_pm_impl_switch_mode
 */
typedef enum {
    MODE_LOCK,
    MODE_UNLOCK
} pm_mode_switch_t;

/**
 * @brief 锁定或释放时在电源模式之间切换
 * @param mode pm_mode_t对应于获取或释放的锁，由\ref esp_pm_impl_get_mode返回
 * @param lock_or_unlock
 *              -MODE_LOCK:已锁定。实现需要确保通过切换到给定的“模式”或任何更高功率的模式来满足锁的约束。
 *              -MODE_UNLOCK：锁定已释放。如果给定模式的所有锁都被释放，并且没有针对高功率模式的锁，则实现可以切换到低功率模式之一。
 * @param now 获取或释放锁的时间戳。作为次要优化传递，因此实现不需要再次调用pm_get_time。
 */
void esp_pm_impl_switch_mode(pm_mode_t mode, pm_mode_switch_t lock_or_unlock, pm_time_t now);

/**
 * @brief 启动时调用一次以初始化pm实现
 */
void esp_pm_impl_init(void);

/**
 * @brief 在进入waiti状态之前，必须从每个CPU上的idle任务调用空闲任务的钩子函数。
 */
void esp_pm_impl_idle_hook(void);

/**
 * @brief 中断调度器的钩子函数必须在进入ISR后立即调用
 */
void esp_pm_impl_isr_hook(void);

/**
 * @brief 转储有关在每种pm模式下花费的时间的信息。
 *
 * 打印三列：模式名称、模式总时间（以微秒为单位）、模式时间百分比
 *
 * @param out 要将信息转储到的流
 */
void esp_pm_impl_dump_stats(FILE* out);

/**
 * @brief 应从空闲任务上下文调用实现“waiti”指令的钩子函数
 */
void esp_pm_impl_waiti(void);

/**
 * @brief 外围设备跳过浅睡眠的回调函数类型。
 *
 */
typedef bool (* skip_light_sleep_cb_t)(void);

/**
  * @brief  注册外设跳过轻睡眠回调
  *
  * 此函数允许您注册一个回调，该回调的结果是如果外围设备应跳过浅睡眠。
  * @param cb 函数以获得结果
  * @return
  *   -成功时ESP_OK
  *   -ESP_ERR_NO_MEM（如果没有更多的回调槽可用）
  */
esp_err_t esp_pm_register_skip_light_sleep_callback(skip_light_sleep_cb_t cb);

/**
  * @brief  注销外设跳过轻睡眠回调
  *
  * 此函数允许您注销以前使用esp_register_skip_light_sleep_callback注册的回调。
  * @param cb 函数以获得结果
  * @return
  *   -成功时ESP_OK
  *   -如果给定回调之前未注册，则返回ESP_ERR_INVALID_STATE
  */
esp_err_t esp_pm_unregister_skip_light_sleep_callback(skip_light_sleep_cb_t cb);

/**
 * @brief 外围设备的回调函数类型，以了解轻睡眠唤醒开销。
 *
 */
typedef void (* inform_out_light_sleep_overhead_cb_t)(uint32_t);

/**
  * @brief  寄存器通知外设轻睡眠唤醒开销时间回调
  *
  * 此函数允许您注册一个回调，通知外围设备轻睡眠的唤醒开销时间。
  * @param cb 通知时间的功能
  * @return
  *   -成功时ESP_OK
  *   -ESP_ERR_NO_MEM（如果没有更多的回调槽可用）
  */
esp_err_t esp_pm_register_inform_out_light_sleep_overhead_callback(inform_out_light_sleep_overhead_cb_t cb);

/**
  * @brief  注销通知外设轻睡眠唤醒开销时间回调
  *
  * 此函数允许您注销一个回调，该回调通知外围设备轻睡眠的唤醒开销时间。
  * @param cb 通知时间的功能
  * @return
  *   -成功时ESP_OK
  *   -如果给定回调之前未注册，则返回ESP_ERR_INVALID_STATE
  */
esp_err_t esp_pm_unregister_inform_out_light_sleep_overhead_callback(inform_out_light_sleep_overhead_cb_t cb);

/**
 * @brief 外围设备的回调函数类型，以了解轻睡眠默认参数
 */
typedef void (* update_light_sleep_default_params_config_cb_t)(int, int);

/**
 * @brief  注册外设轻睡眠默认参数配置回调
 *
 * 此函数允许您注册一个回调，以配置轻睡眠默认参数的外围设备
 * @param cb 更新默认参数的函数
 */
void esp_pm_register_light_sleep_default_params_config_callback(update_light_sleep_default_params_config_cb_t cb);

/**
 * @brief  注销外设轻睡眠默认参数配置回调
 *
 * 此函数允许您注销一个回调，该回调用于配置轻睡眠默认参数的外围设备
 */
void esp_pm_unregister_light_sleep_default_params_config_callback(void);

#ifdef CONFIG_PM_PROFILING
#define WITH_PROFILING
#endif

#ifdef WITH_PROFILING
static inline pm_time_t IRAM_ATTR pm_get_time(void)
{
    return esp_timer_get_time();
}
#endif // WITH_PROFILING

#ifdef __cplusplus
}
#endif

