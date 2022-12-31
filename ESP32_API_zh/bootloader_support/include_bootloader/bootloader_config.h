/*
 * SPDX文件版权文本：2015-2021浓缩咖啡系统（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */
#ifndef __BOOT_CONFIG_H__
#define __BOOT_CONFIG_H__

#include <stdint.h>

#ifdef __cplusplus
extern "C"
{
#endif

#include "esp_flash_partitions.h"
#include "soc/soc.h"

#define SPI_SEC_SIZE 0x1000

#define SPI_ERROR_LOG "spi flash error"

#define MAX_OTA_SLOTS 16

typedef struct {
    esp_partition_pos_t ota_info;
    esp_partition_pos_t factory;
    esp_partition_pos_t test;
    esp_partition_pos_t ota[MAX_OTA_SLOTS];
    uint32_t app_count;
    uint32_t selected_subtype;
} bootloader_state_t;

bool flash_encrypt(bootloader_state_t *bs);

/* index_to_partition使用的索引是OTA索引号或这些特殊常量*/
#define FACTORY_INDEX (-1)
#define TEST_APP_INDEX (-2)
#define INVALID_INDEX (-99)

#ifdef __cplusplus
}
#endif

#endif /* __BOOT_CONFIG_H__ */

