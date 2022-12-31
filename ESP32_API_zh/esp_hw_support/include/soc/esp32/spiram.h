/*
 * SPDX文件版权文本：2015-2021浓缩咖啡系统（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */


#ifndef __ESP_SPIRAM_H
#define __ESP_SPIRAM_H

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include "esp_err.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    ESP_SPIRAM_SIZE_16MBITS = 0,   /*!< SPI RAM大小为16 MB*/
    ESP_SPIRAM_SIZE_32MBITS = 1,   /*!< SPI RAM大小为32 MB*/
    ESP_SPIRAM_SIZE_64MBITS = 2,   /*!< SPI RAM大小为64 MB*/
    ESP_SPIRAM_SIZE_INVALID,       /*!< SPI RAM大小无效*/
} esp_spiram_size_t;

/**
 * @brief 获取SPI RAM大小
 * @return
 *     -如果SPI RAM未启用或无效，则为ESP_SPIRAM_SIZE_INVALID
 *     -SPI RAM大小
 */
esp_spiram_size_t esp_spiram_get_chip_size(void);

/**
 * @brief 初始化spiram接口/硬件。通常从cpu_start.c调用。
 *
 * @return 成功时ESP_OK
 */
esp_err_t esp_spiram_init(void);

/**
 * @brief 配置缓存/MMU以访问外部SPI RAM。
 *
 * 通常，如果启用了CONFIG_SPIRAM_BOOT_INIT选项，则从cpu_start调用此函数。需要在运行时启用SPI RAM的应用程序可以禁用CONFIG_SPIRAM_BOOT_INIT，稍后调用此函数。
 *
 * @attention 必须在禁用闪存缓存的情况下调用此函数。
 */
void esp_spiram_init_cache(void);


/**
 * @brief SPI RAM的内存测试。应在SPI RAM初始化并且（如果是双核系统）应用程序CPU联机后调用。这个测试用垃圾覆盖内存，所以不要在例如堆分配器将重要内容存储在SPI RAM中之后调用。
 *
 * @return 成功时为true，内存测试失败时为false
 */
bool esp_spiram_test(void);


/**
 * @brief 将初始化的SPI RAM添加到堆分配器。
 */
esp_err_t esp_spiram_add_to_heapalloc(void);


/**
 * @brief 获取在menuconfig中选择的附加SPI RAM芯片的大小
 *
 * @return 大小以字节为单位，如果未编译外部RAM芯片支持，则为0。
 */
size_t esp_spiram_get_size(void);


/**
 * @brief 强制写回SPI RAM缓存中的数据。每当禁用缓存时，都会调用此命令，因为禁用ESP32上的缓存会丢弃SPI RAM缓存中的数据。
 *
 * 这是为了在SPI闪存代码中使用。
 */
void esp_spiram_writeback_cache(void);

/**
 * @brief 获取psram CS IO
 *
 * 应在启用PSRAM后调用此接口，否则将返回无效值-1/0xff。
 *
 * @return psram CS IO或-1/0xff（如果未启用psram）
 */
uint8_t esp_spiram_get_cs_io(void);


/**
 * @brief 为特定DMA/内部分配保留一个内部内存池
 *
 * @param size 保留池的大小（字节）
 *
 * @return
 *          -成功时ESP_OK
 *          -当池没有可用内存时，ESP_ERR_NO_MEM
 */
esp_err_t esp_spiram_reserve_dma_pool(size_t size);


/**
 * @brief 如果SPI RAM（PSRAM）已初始化
 *
 * @return
 *          -真SPI RAM已成功初始化
 *          -假SPI RAM尚未初始化或初始化失败
 */
bool esp_spiram_is_initialized(void);

#ifdef __cplusplus
}
#endif

#endif //  __ESP_SPIRAM_H

