// 版权所有2015-2017 Espressif Systems（上海）私人有限公司
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
#include <stddef.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "spiffs.h"
#include "esp_vfs.h"
#include "esp_compiler.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief SPIFFS定义结构
 */
typedef struct {
    spiffs *fs;                             /*!< 底层SPIFFS的句柄*/
    SemaphoreHandle_t lock;                 /*!< FS锁*/
    const esp_partition_t* partition;       /*!< SPIFFS所在的分区*/
    char base_path[ESP_VFS_PATH_MAX+1];     /*!< 装载点*/
    bool by_label;                          /*!< 分区已按标签装入*/
    spiffs_config cfg;                      /*!< SPIFFS装载配置*/
    uint8_t *work;                          /*!< 工作缓冲区*/
    uint8_t *fds;                           /*!< 文件描述符缓冲区*/
    uint32_t fds_sz;                        /*!< 文件描述符缓冲区长度*/
    uint8_t *cache;                         /*!< 缓存缓冲区*/
    uint32_t cache_sz;                      /*!< 缓存缓冲区长度*/
} esp_spiffs_t;

s32_t spiffs_api_read(spiffs *fs, uint32_t addr, uint32_t size, uint8_t *dst);

s32_t spiffs_api_write(spiffs *fs, uint32_t addr, uint32_t size, uint8_t *src);

s32_t spiffs_api_erase(spiffs *fs, uint32_t addr, uint32_t size);

void spiffs_api_check(spiffs *fs, spiffs_check_type type,
                            spiffs_check_report report, uint32_t arg1, uint32_t arg2);

#ifdef __cplusplus
}
#endif

