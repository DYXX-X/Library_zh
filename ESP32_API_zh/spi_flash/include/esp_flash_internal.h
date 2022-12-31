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

#pragma once
#include "esp_err.h"
#include <stdint.h>
#include <stdbool.h>
#include <driver/spi_common_internal.h>
#include "sdkconfig.h"

#include "esp_flash.h"

/**内部API，不在应用程序中使用*/

#ifdef __cplusplus
extern "C" {
#endif


/** @brief 初始化默认SPI闪存芯片
 *
 * 由OS启动代码调用。您不需要在自己的应用程序中调用它。
 */
#ifdef CONFIG_SPI_FLASH_USE_LEGACY_IMPL
#define esp_flash_init_default_chip(...) ({ESP_OK;})
#else
esp_err_t esp_flash_init_default_chip(void);
#endif

/**
 *  在IDF中启用OS级SPI闪存保护
 *
 *  由OS启动代码调用。您不需要在自己的应用程序中调用它。
 *
 * @return 如果成功，则ESP_OK，否则失败。请参见``esp_flash_init_os_functions``的返回值。
 */
#ifdef CONFIG_SPI_FLASH_USE_LEGACY_IMPL
#define esp_flash_app_init(...) ({ESP_OK;})
#else
esp_err_t esp_flash_app_init(void);
#endif

/**
 *  在IDF中禁用（或启用）OS级SPI闪存保护
 *
 *  由IDF内部代码（例如coredump）调用。您不需要在自己的应用程序中调用它。
 *
 * @return 始终为ESP_OK。
 */
#ifdef CONFIG_SPI_FLASH_USE_LEGACY_IMPL
#define esp_flash_app_disable_protect(...) ({ESP_OK;})
#else
esp_err_t esp_flash_app_disable_protect(bool disable);
#endif

/**
 *  初始化特定芯片的OS级函数。
 *
 * @param chip 初始化os功能的芯片。
 * @param host_id 要使用哪个SPI主机，1个用于SPI1，2个用于SPI2（HSPI），3个用于SPI3（VSPI）
 * @param out_dev_id 占用设备插槽的输出
 *
 * @return
 *      -ESP_OK（如果成功）
 *      -如果host_id无效，则为ESP_ERR_INVALID_ARG
 */
esp_err_t esp_flash_init_os_functions(esp_flash_t *chip, int host_id, int *out_dev_id);

/**
 * @brief 取消初始化OS级函数
 *
 * @param chip  去智能操作系统功能的芯片
 * @return 始终为ESP_OK。
 */
esp_err_t esp_flash_deinit_os_functions(esp_flash_t* chip);

/**
 * @brief 初始化SPI1总线上的总线锁。如果驱动程序（包括esp_flash）希望使用SPI1总线，则应调用。
 *
 * @note 当使用传统spi flash API时，SPI1总线上的总线锁将不可用。
 *
 * @return esp_err_t总是esp_OK。
 */
esp_err_t esp_flash_init_main_bus_lock(void);

/**
 *  初始化主闪存芯片的OS级功能。
 *
 * @param chip 初始化os功能的芯片。现在只支持指向默认芯片的指针。
 *
 * @return 始终ESP_OK
 */
esp_err_t esp_flash_app_enable_os_functions(esp_flash_t* chip);

/**
 *  在特殊阶段（例如核心转储）禁用主闪存芯片的OS级功能
 *
 * @param chip 初始化os功能的芯片。现在只支持“esp_flash_default_chip”。
 *
 * @return 始终ESP_OK
 */
esp_err_t esp_flash_app_disable_os_functions(esp_flash_t* chip);



#ifdef __cplusplus
}
#endif

