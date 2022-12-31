/*
 * SPDX文件版权文本：2020-2021浓缩咖啡系统（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */

#pragma once

#include "soc/soc.h"
#include "soc/sensitive_reg.h"
#include "esp32c3/rom/cache.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef union {
    struct {
        uint32_t cat0       : 2;
        uint32_t cat1       : 2;
        uint32_t cat2       : 2;
        uint32_t res0       : 8;
        uint32_t splitaddr  : 8;
        uint32_t res1       : 10;
    };
    uint32_t val;
} constrain_reg_fields_t;

#ifndef I_D_SRAM_SEGMENT_SIZE
#define I_D_SRAM_SEGMENT_SIZE       0x20000
#endif

#define I_D_SPLIT_LINE_SHIFT        0x9
#define I_D_FAULT_ADDR_SHIFT        0x2

#define DRAM_SRAM_START             0x3FC7C000

#ifndef MAP_DRAM_TO_IRAM
#define MAP_DRAM_TO_IRAM(addr)       (addr - DRAM_SRAM_START + SOC_IRAM_LOW)
#endif

#ifndef MAP_IRAM_TO_DRAM
#define MAP_IRAM_TO_DRAM(addr)       (addr - SOC_IRAM_LOW + DRAM_SRAM_START)
#endif

//IRAM0

//16kB（ICACHE）
#define IRAM0_SRAM_LEVEL_0_LOW      SOC_IRAM_LOW //0x40370000
#define IRAM0_SRAM_LEVEL_0_HIGH     (IRAM0_SRAM_LEVEL_0_LOW + CACHE_MEMORY_IBANK_SIZE - 0x1) //0x4037法国法郎

//128kB（1级）
#define IRAM0_SRAM_LEVEL_1_LOW      (IRAM0_SRAM_LEVEL_0_HIGH + 0x1) //0x40380000
#define IRAM0_SRAM_LEVEL_1_HIGH     (IRAM0_SRAM_LEVEL_1_LOW + I_D_SRAM_SEGMENT_SIZE - 0x1) //0x4039法国法郎

//128kB（2级）
#define IRAM0_SRAM_LEVEL_2_LOW      (IRAM0_SRAM_LEVEL_1_HIGH + 0x1) //0x403A0000
#define IRAM0_SRAM_LEVEL_2_HIGH     (IRAM0_SRAM_LEVEL_2_LOW + I_D_SRAM_SEGMENT_SIZE - 0x1) //0x403BFFFF

//128kB（3级）
#define IRAM0_SRAM_LEVEL_3_LOW      (IRAM0_SRAM_LEVEL_2_HIGH + 0x1) //0x403C0000
#define IRAM0_SRAM_LEVEL_3_HIGH     (IRAM0_SRAM_LEVEL_3_LOW + I_D_SRAM_SEGMENT_SIZE - 0x1) //0x403DFFFF

//许可位
#define SENSITIVE_CORE_X_IRAM0_PMS_CONSTRAIN_SRAM_WORLD_X_R  0x1
#define SENSITIVE_CORE_X_IRAM0_PMS_CONSTRAIN_SRAM_WORLD_X_W  0x2
#define SENSITIVE_CORE_X_IRAM0_PMS_CONSTRAIN_SRAM_WORLD_X_F  0x4

//DRAM0

//DRAM0不提供16kB ICACHE

//128kB（1级）
#define DRAM0_SRAM_LEVEL_1_LOW      SOC_DRAM_LOW //0x3FC80000
#define DRAM0_SRAM_LEVEL_1_HIGH     (DRAM0_SRAM_LEVEL_1_LOW + I_D_SRAM_SEGMENT_SIZE - 0x1) //0x3FC9FFFF

//128kB（2级）
#define DRAM0_SRAM_LEVEL_2_LOW      (DRAM0_SRAM_LEVEL_1_HIGH + 0x1) //0x3FCA0000
#define DRAM0_SRAM_LEVEL_2_HIGH     (DRAM0_SRAM_LEVEL_2_LOW + I_D_SRAM_SEGMENT_SIZE - 0x1) //0x3FCFFFF

//128kB（3级）
#define DRAM0_SRAM_LEVEL_3_LOW      (DRAM0_SRAM_LEVEL_2_HIGH + 0x1) //0x3FCC000
#define DRAM0_SRAM_LEVEL_3_HIGH     (DRAM0_SRAM_LEVEL_3_LOW  + I_D_SRAM_SEGMENT_SIZE - 0x1) //0x3FCFDFFFF

#define SENSITIVE_CORE_X_DRAM0_PMS_CONSTRAIN_SRAM_WORLD_X_R  0x1
#define SENSITIVE_CORE_X_DRAM0_PMS_CONSTRAIN_SRAM_WORLD_X_W  0x2

//RTC FAST

//许可位
#define SENSITIVE_CORE_0_PIF_PMS_CONSTRAIN_RTCFAST_WORLD_X_W  0x1
#define SENSITIVE_CORE_0_PIF_PMS_CONSTRAIN_RTCFAST_WORLD_X_R  0x2
#define SENSITIVE_CORE_0_PIF_PMS_CONSTRAIN_RTCFAST_WORLD_X_F  0x4

#define AREA_LOW                                                0
#define AREA_HIGH                                               1

#ifdef __cplusplus
}
#endif

