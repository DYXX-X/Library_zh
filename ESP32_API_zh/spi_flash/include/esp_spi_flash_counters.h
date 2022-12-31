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

#pragma once

#include <stdint.h>
#include <stdbool.h>
#include "esp_err.h"
#include "sdkconfig.h"

#if CONFIG_SPI_FLASH_ENABLE_COUNTERS

#ifdef __cplusplus
extern "C" {
#endif

/**
 * 一种操作类型的结构持有统计信息
 */
typedef struct {
    uint32_t count;     // 执行操作的次数
    uint32_t time;      // 所用总时间（微秒）
    uint32_t bytes;     // 总字节数
} spi_flash_counter_t;

typedef struct {
    spi_flash_counter_t read;
    spi_flash_counter_t write;
    spi_flash_counter_t erase;
} spi_flash_counters_t;

/**
 * @brief  重置SPI闪存操作计数器
 */
void spi_flash_reset_counters(void);

/**
 * @brief  打印SPI闪存操作计数器
 */
void spi_flash_dump_counters(void);

/**
 * @brief  返回电流SPI闪存操作计数器
 *
 * @return  指向保存操作计数器值的spi_flash_recounter_t结构的指针
 */
const spi_flash_counters_t* spi_flash_get_counters(void);

#ifdef __cplusplus
}
#endif

#endif //CONFIG_SPI_FLASH_ENABLE_COUNTERS

