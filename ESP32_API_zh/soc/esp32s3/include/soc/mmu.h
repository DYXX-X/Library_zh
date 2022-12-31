// 版权所有2020 Espressif Systems（上海）私人有限公司
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
#include "soc/cache_memory.h"
#include "soc/soc.h"

#ifdef __cplusplus
extern "C" {
#endif

/* 为flash mmap定义*/
#define SOC_MMU_REGIONS_COUNT                   2
#define SOC_MMU_PAGES_PER_REGION                256
#define SOC_MMU_IROM0_PAGES_START               (CACHE_IROM_MMU_START / sizeof(uint32_t))
#define SOC_MMU_IROM0_PAGES_END                 (CACHE_IROM_MMU_END / sizeof(uint32_t))
#define SOC_MMU_DROM0_PAGES_START               (CACHE_DROM_MMU_START / sizeof(uint32_t))
#define SOC_MMU_DROM0_PAGES_END                 (CACHE_DROM_MMU_END / sizeof(uint32_t))
#define SOC_MMU_INVALID_ENTRY_VAL               MMU_TABLE_INVALID_VAL
#define SOC_MMU_ADDR_MASK                       MMU_ADDRESS_MASK
#define SOC_MMU_PAGE_IN_FLASH(page)             ((page) | MMU_ACCESS_FLASH)
#define SOC_MMU_DPORT_PRO_FLASH_MMU_TABLE       FLASH_MMU_TABLE
#define SOC_MMU_VADDR1_START_ADDR               IRAM0_CACHE_ADDRESS_LOW
#define SOC_MMU_PRO_IRAM0_FIRST_USABLE_PAGE     SOC_MMU_IROM0_PAGES_START
#define SOC_MMU_VADDR0_START_ADDR               (SOC_DROM_LOW + (SOC_MMU_DROM0_PAGES_START * SPI_FLASH_MMU_PAGE_SIZE))
#define SOC_MMU_VADDR1_FIRST_USABLE_ADDR        SOC_IROM_LOW

#ifdef __cplusplus
}
#endif

