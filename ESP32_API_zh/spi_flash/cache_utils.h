// 版权所有2015-2016 Espressif Systems（上海）私人有限公司
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

#ifndef ESP_SPI_FLASH_CACHE_UTILS_H
#define ESP_SPI_FLASH_CACHE_UTILS_H

#include "sdkconfig.h"
#include <stdbool.h>

/**
 * 这个头文件包含flash_ops中使用的缓存操作函数的声明。c和flash_mmap.c。
 *
 * 这些函数被视为内部函数，不可从应用程序调用。
 */

// 初始化互斥体保护对spi_flash_*API的访问
void spi_flash_init_lock(void);

// 获取对spi_flash_*API的互斥保护访问
void spi_flash_op_lock(void);

// 释放所述互斥锁
void spi_flash_op_unlock(void);

// 在两个CPU上挂起调度程序，禁用缓存。
// 与它的名称相反，它对中断没有任何作用。
// 一旦我们实施，将添加中断禁用功能
// 中断分配API。
void spi_flash_disable_interrupts_caches_and_other_cpu(void);

// 启用缓存，启用中断（将来添加），恢复调度程序
void spi_flash_enable_interrupts_caches_and_other_cpu(void);

// 禁用当前CPU上的非IRAM中断处理程序和两个CPU上的缓存。
// 当其他CPU未运行或正在运行IRAM的代码时，将调用此函数。
void spi_flash_disable_interrupts_caches_and_other_cpu_no_os(void);

// 启用缓存，启用当前CPU上的中断。
// 当其他CPU未运行或正在运行IRAM的代码时，将调用此函数。
void spi_flash_enable_interrupts_caches_no_os(void);

// 将包含闪光区域的页面标记为
// 擦除或写入。这意味着闪存需要
// 在这些页面可以再次被flash_map（）读取之前，
// 因为它们可能包含过时的数据
//
// 仅在按住spi_flash_op_lock（）时调用此函数
// 如果缓存已刷新，则返回true，否则返回false
bool spi_flash_check_and_flush_cache(size_t start_addr, size_t length);

//配置缓存模式
#if !CONFIG_IDF_TARGET_ESP32
//通过menuconfig配置instrcutin缓存大小和缓存块大小
void esp_config_instruction_cache_mode(void);
//通过menuconfig配置数据缓存大小和缓存块大小
void esp_config_data_cache_mode(void);
//为指令缓存和数据缓存启用缓存包装模式
esp_err_t esp_enable_cache_wrap(bool icache_wrap_enable, bool dcache_wrap_enable);
#endif


#endif //ESP_SPI_FLASH_CACHE_UTILS_H

