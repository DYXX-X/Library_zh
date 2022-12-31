// 版权所有2015-2016 Espressif Systems（上海）私人有限公司
//
// 根据Apache许可证2.0版（“许可证”）获得许可；
// 除非符合许可证，否则不得使用此文件。
// 您可以在以下地址获取许可证副本：

//     http://www.apache.org/licenses/LICENSE-2.0
//
// 除非适用法律要求或书面同意，软件
// 根据许可证分发的内容是按“原样”分发的，
// 无任何明示或暗示的保证或条件。
// 有关管理权限和
// 许可证下的限制。

#ifndef __ESP_SYSTEM_H__
#define __ESP_SYSTEM_H__

#include <stdint.h>
#include <stdbool.h>
#include "esp_err.h"
#include "esp_attr.h"
#include "esp_bit_defs.h"
#include "esp_idf_version.h"

#include "sdkconfig.h"

// 用于向后兼容。这些标题
// 包含硬件操作功能和定义
// 最初在此标头中声明的。
#include "esp_mac.h"
#include "esp_chip_info.h"
#include "esp_random.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 重置原因
 */
typedef enum {
    ESP_RST_UNKNOWN,    //!< 无法确定重置原因
    ESP_RST_POWERON,    //!< 由于通电事件而重置
    ESP_RST_EXT,        //!< 通过外部引脚复位（不适用于ESP32）
    ESP_RST_SW,         //!< 通过esp_restart重置软件
    ESP_RST_PANIC,      //!< 异常/死机导致软件重置
    ESP_RST_INT_WDT,    //!< 由于中断看门狗而重置（软件或硬件）
    ESP_RST_TASK_WDT,   //!< 由于任务监视器而重置
    ESP_RST_WDT,        //!< 由于其他看门狗而重置
    ESP_RST_DEEPSLEEP,  //!< 退出深度睡眠模式后重置
    ESP_RST_BROWNOUT,   //!< 断电复位（软件或硬件）
    ESP_RST_SDIO,       //!< 通过SDIO复位
} esp_reset_reason_t;

/**
 * 关闭处理程序类型
 */
typedef void (*shutdown_handler_t)(void);

/**
  * @brief  寄存器关闭处理程序
  *
  * 此函数允许您注册在使用esp_restart函数重新启动应用程序之前调用的处理程序。
  * @param handle 重新启动时要执行的函数
  * @return
  *   -成功时ESP_OK
  *   -如果处理程序已注册，则返回ESP_ERR_INVALID_STATE
  *   -ESP_ERR_NO_MEM（如果没有更多关闭处理程序插槽可用）
  */
esp_err_t esp_register_shutdown_handler(shutdown_handler_t handle);

/**
  * @brief  注销关闭处理程序
  *
  * 此函数允许您注销以前使用esp_register_shutdown_handler函数注册的处理程序。
  *   -成功时ESP_OK
  *   -如果给定处理程序之前未注册，则返回ESP_ERR_INVALID_STATE
  */
esp_err_t esp_unregister_shutdown_handler(shutdown_handler_t handle);


/**
  * @brief  重新启动PRO和APP CPU。
  *
  * 该函数可以从PRO和APP CPU调用。成功重启后，CPU重置原因将为SW_CPU_reset。外围设备（WiFi、BT、UART0、SPI1和传统定时器除外）不会重置。此函数不返回。
  */
void esp_restart(void) __attribute__ ((noreturn));

/**
 * @brief  获取上次重置的原因
 * @return 有关每个值的说明，请参见esp_reset_reason_t的说明。
 */
esp_reset_reason_t esp_reset_reason(void);

/**
  * @brief  获取可用堆的大小。
  *
  * 注意，返回的值可能大于可分配的最大连续块。
  *
  * @return 可用堆大小（字节）。
  */
uint32_t esp_get_free_heap_size(void);

/**
  * @brief  获取可用内部堆的大小。
  *
  * 注意，返回的值可能大于可分配的最大连续块。
  *
  * @return 可用的内部堆大小（字节）。
  */
uint32_t esp_get_free_internal_heap_size(void);

/**
  * @brief 获取有史以来可用的最小堆
  *
  * @return 最小可用堆
  */
uint32_t esp_get_minimum_free_heap_size( void );

/**
 * @brief 触发软件中止
 *
 * @param details 在紧急处理过程中显示的详细信息。
 */
void  __attribute__((noreturn)) esp_system_abort(const char* details);

#ifdef __cplusplus
}
#endif

#endif /* __ESP_SYSTEM_H__ */

