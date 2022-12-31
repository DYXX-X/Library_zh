/*
 * SPDX文件版权文本：2015-2021浓缩咖啡系统（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */


#ifndef _PSRAM_H
#define _PSRAM_H
#include "soc/spi_periph.h"
#include "esp_err.h"
#include "sdkconfig.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    PSRAM_CACHE_F80M_S40M = 0,
    PSRAM_CACHE_F40M_S40M,
    PSRAM_CACHE_F80M_S80M,
    PSRAM_CACHE_MAX,
} psram_cache_mode_t;

typedef enum {
    PSRAM_SIZE_16MBITS = 0,
    PSRAM_SIZE_32MBITS = 1,
    PSRAM_SIZE_64MBITS = 2,
    PSRAM_SIZE_MAX,
} psram_size_t;

/*
有关这些模式的定义，请参阅TRM，PID/MPU/MMU章节，标题“外部RAM”。

重要的是NORMAL在禁用应用程序CPU缓存的情况下工作，但在同时启用应用程序和pro CPU时会产生巨大的缓存一致性问题。LOWHIGH和EVENODD没有这些一致性问题，但在禁用应用程序CPU缓存时无法使用。
*/

typedef enum {
    PSRAM_VADDR_MODE_NORMAL=0, ///<App和pro CPU使用自己的闪存缓存进行外部RAM访问
    PSRAM_VADDR_MODE_LOWHIGH,  ///<App和pro CPU共享外部RAM缓存：pro CPU具有低2M，App CPU具有高2M
    PSRAM_VADDR_MODE_EVENODD,  ///<App和pro CPU共享外部RAM缓存：pro CPU执行偶数32字节范围，App执行奇数32字节范围。
} psram_vaddr_mode_t;

/**
 * @brief 获取psram大小
 * @return
 *     -PSRAM_SIZE_MAX（如果PSRAM未启用或无效）
 *     -PSRAM大小
 */
psram_size_t psram_get_size(void);

/**
 * @brief psram缓存启用功能
 *
 * Esp-idf使用它来初始化psram的缓存，将其映射到主内存地址空间。
 *
 * @param mode       SPI模式访问psram
 * @param vaddrmode  psram缓存的工作模式。
 * @return 成功时为ESP_OK，需要VSPI外设但无法申领时为ESP_ERR_INVALID_STATE。
 */
esp_err_t psram_enable(psram_cache_mode_t mode, psram_vaddr_mode_t vaddrmode);

/**
 * @brief 获取psram CS IO
 *
 * @return psram CS IO
 */
uint8_t psram_get_cs_io(void);

#ifdef __cplusplus
}
#endif

#endif

