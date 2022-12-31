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
#include <stdint.h>
#include <stdbool.h>
#include "esp_err.h"
#include "sdkconfig.h"
#if CONFIG_IDF_TARGET_ESP32
#include "esp32/pm.h"
#elif CONFIG_IDF_TARGET_ESP32S2
#include "esp32s2/pm.h"
#elif CONFIG_IDF_TARGET_ESP32S3
#include "esp32s3/pm.h"
#elif CONFIG_IDF_TARGET_ESP32C3
#include "esp32c3/pm.h"
#elif CONFIG_IDF_TARGET_ESP32H2
#include "esp32h2/pm.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 电源管理限制
 */
typedef enum {
    /**
     * 要求CPU频率为通过esp_pm_configure设置的最大值。参数未使用，应设置为0。
     */
    ESP_PM_CPU_FREQ_MAX,
    /**
     * 要求APB频率处于芯片支持的最大值。参数未使用，应设置为0。
     */
    ESP_PM_APB_FREQ_MAX,
    /**
     * 防止系统进入浅睡眠状态。参数未使用，应设置为0。
     */
    ESP_PM_NO_LIGHT_SLEEP,
} esp_pm_lock_type_t;

/**
 * @brief 设置特定于实施的电源管理配置
 * @param config 指向特定于实现的配置结构的指针（例如esp_pm_config_esp32）
 * @return
 *      -成功时ESP_OK
 *      -如果配置值不正确，则返回ESP_ERR_INVALID_ARG
 *      -ESP_ERR_NOT_SUPPORTED（如果不支持某些值组合），或者如果在sdkconfig中未启用CONFIG_PM_ENABLE
 */
esp_err_t esp_pm_configure(const void* config);

/**
 * @brief 获取特定于实施的电源管理配置
 * @param config 指向特定于实现的配置结构的指针（例如esp_pm_config_esp32）
 * @return
 *      -成功时ESP_OK
 *      -如果指针为空，则为ESP_ERR_INVALID_ARG
 */
esp_err_t esp_pm_get_configuration(void* config);

/**
 * @brief 电源管理锁的不透明手柄
 */
typedef struct esp_pm_lock* esp_pm_lock_handle_t;


/**
 * @brief 初始化特定电源管理参数的锁定句柄
 *
 * 创建锁时，最初不会使用它。调用esp_pm_lock_acquire获取锁。
 *
 * 不能从ISR调用此函数。
 *
 * @param lock_type 锁应控制的电源管理约束
 * @param arg 参数，值取决于lock_type，请参见esp_pm_lock_type_t
 * @param name 标识锁的任意字符串（例如“wifi”或“spi”）。esp_pm_dump_locks函数用于列出现有锁。可以设置为NULL。如果未设置为NULL，则必须指向在锁的生存期内有效的字符串。
 * @param[out] out_handle  此函数返回的句柄。调用esp_pm_lock_delete、esp_pm_lock _acquire和esp_pm_lock_release时使用此句柄。不能为NULL。
 * @return
 *      -成功时ESP_OK
 *      -如果无法分配锁结构，则为ESP_ERR_NO_MEM
 *      -如果out_handle为NULL或类型参数无效，则返回ESP_ERR_INVALID_ARG
 *      -如果在sdkconfig中未启用CONFIG_PM_ENABLE，则ESP_ERR_NOT_SUPPORTED
 */
esp_err_t esp_pm_lock_create(esp_pm_lock_type_t lock_type, int arg,
        const char* name, esp_pm_lock_handle_t* out_handle);

/**
 * @brief 使用电源管理锁
 *
 * 一旦锁定，电源管理算法将不会切换到esp_pm_lock_create调用中指定的模式或任何较低功率模式（“mode”的较高数值）。
 *
 * 锁是递归的，因为如果多次调用esp_pm_lock_acquire，则必须多次调用esp_prm_lock_release才能释放锁。
 *
 * 可以从ISR调用此函数。
 *
 * 对于同一句柄，此函数不是线程安全的w.r.t.调用其他esp_pm_lock_*函数。
 *
 * @param handle 从esp_pm_lock_create函数获得的句柄
 * @return
 *      -成功时ESP_OK
 *      -如果句柄无效，则返回ESP_ERR_INVALID_ARG
 *      -如果在sdkconfig中未启用CONFIG_PM_ENABLE，则ESP_ERR_NOT_SUPPORTED
 */
esp_err_t esp_pm_lock_acquire(esp_pm_lock_handle_t handle);

/**
 * @brief 释放使用esp_pm_lock_acquire获取的锁。
 *
 * 调用此函数可消除取锁时设置的电源管理限制。
 *
 * 锁是递归的，因此，如果多次调用esp_pm_lock_acquire，则必须多次调用esp_prm_lock_release才能真正释放锁。
 *
 * 可以从ISR调用此函数。
 *
 * 对于同一句柄，此函数不是线程安全的w.r.t.调用其他esp_pm_lock_*函数。
 *
 * @param handle 从esp_pm_lock_create函数获得的句柄
 * @return
 *      -成功时ESP_OK
 *      -如果句柄无效，则返回ESP_ERR_INVALID_ARG
 *      -如果未获取锁，则为ESP_ERR_INVALID_STATE
 *      -如果在sdkconfig中未启用CONFIG_PM_ENABLE，则ESP_ERR_NOT_SUPPORTED
 */
esp_err_t esp_pm_lock_release(esp_pm_lock_handle_t handle);

/**
 * @brief 删除使用esp_pm_lock创建的锁
 *
 * 在调用此函数之前，必须释放锁。
 *
 * 不能从ISR调用此函数。
 *
 * @param handle 从esp_pm_lock_create函数获得的句柄
 * @return
 *      -成功时ESP_OK
 *      -如果句柄参数为NULL，则为ESP_ERR_INVALID_ARG
 *      -如果仍获取锁，则为ESP_ERR_INVALID_STATE
 *      -如果在sdkconfig中未启用CONFIG_PM_ENABLE，则ESP_ERR_NOT_SUPPORTED
 */
esp_err_t esp_pm_lock_delete(esp_pm_lock_handle_t handle);

/**
 * 将所有锁的列表转储到stderr
 *
 * 此函数将有关使用esp_pm_lock_create创建的锁的调试信息转储到输出流。
 *
 * 不能从ISR调用此函数。如果在运行此函数时调用esp_pm_lock_acquire/release，则可能会报告不一致的结果。
 *
 * @param stream 将信息打印到的流；使用stdout或stderr打印到控制台；使用fmemopen/open_memstream打印到字符串缓冲区。
 * @return
 *      -成功时ESP_OK
 *      -如果在sdkconfig中未启用CONFIG_PM_ENABLE，则ESP_ERR_NOT_SUPPORTED
 */
esp_err_t esp_pm_dump_locks(FILE* stream);

#ifdef __cplusplus
}
#endif

