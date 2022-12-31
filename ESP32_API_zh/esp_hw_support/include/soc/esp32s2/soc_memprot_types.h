/*
 * SPDX文件版权文本：2021浓缩咖啡系统（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */

//////////////////////////////////////////////////////////
// ESP32-S2 PMS内存保护类型
//

#pragma once

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief PMS识别的内存类型
 */
typedef enum {
    MEMPROT_TYPE_NONE                           = 0x00000000,
    MEMPROT_TYPE_ALL                            = 0x7FFFFFFF,
    MEMPROT_TYPE_INVALID                        = 0x80000000
} esp_mprot_mem_t;

/**
 * @brief 拆分地址（行）类型
 */
typedef enum {
    MEMPROT_SPLIT_ADDR_NONE                     = 0x00000000,
    MEMPROT_SPLIT_ADDR_ALL                      = 0x7FFFFFFF,
    MEMPROT_SPLIT_ADDR_INVALID                  = 0x80000000
} esp_mprot_split_addr_t;

/**
 * @brief PMS区域类型（相邻分割地址之间或主分割地址上方/下方的内存空间）
 */
typedef enum {
    MEMPROT_PMS_AREA_NONE                       = 0x00000000,
    MEMPROT_PMS_AREA_ALL                        = 0x7FFFFFFF,
    MEMPROT_PMS_AREA_INVALID                    = 0x80000000
} esp_mprot_pms_area_t;

/**
* @brief 内存保护配置
*/
typedef struct {
    bool invoke_panic_handler;  /*!< 为紧急处理注册PMS违规中断*/
    bool lock_feature;          /*!< 锁定所有PMS设置*/
    void *split_addr;           /*!< 主I/O拆分地址*/
    uint32_t mem_type_mask;     /*!< 需要保护的内存类型。请参见esp_mprot_mem_t枚举*/
} esp_memp_config_t;

#define ESP_MEMPROT_DEFAULT_CONFIG() { \
    .invoke_panic_handler = true, \
    .lock_feature = true, \
    .split_addr = NULL, \
    .mem_type_mask = MEMPROT_TYPE_ALL \
}

/**
 * @brief 将内存保护类型转换为字符串
 *
 * @param mem_type 内存保护类型
 */
static inline const char *esp_mprot_mem_type_to_str(const esp_mprot_mem_t mem_type)
{
    switch (mem_type) {
    case MEMPROT_TYPE_NONE:
        return "MEMPROT_TYPE_NONE";
    case MEMPROT_TYPE_ALL:
        return "MEMPROT_TYPE_ALL";
    default:
        return "MEMPROT_TYPE_INVALID";
    }
}

/**
 * @brief 将拆分地址类型转换为字符串
 *
 * @param line_type 拆分线型
 */
static inline const char *esp_mprot_split_addr_to_str(const esp_mprot_split_addr_t line_type)
{
    switch (line_type) {
    case MEMPROT_SPLIT_ADDR_NONE:
        return "MEMPROT_SPLIT_ADDR_NONE";
    case MEMPROT_SPLIT_ADDR_ALL:
        return "MEMPROT_SPLIT_ADDR_ALL";
    default:
        return "MEMPROT_SPLIT_ADDR_INVALID";
    }
}

/**
 * @brief 将PMS区域类型转换为字符串
 *
 * @param area_type PMS区域类型
 */
static inline const char *esp_mprot_pms_area_to_str(const esp_mprot_pms_area_t area_type)
{
    switch (area_type) {
    case MEMPROT_PMS_AREA_NONE:
        return "MEMPROT_PMS_AREA_NONE";
    case MEMPROT_PMS_AREA_ALL:
        return "MEMPROT_PMS_AREA_ALL";
    default:
        return "MEMPROT_PMS_AREA_INVALID";
    }
}

#ifdef __cplusplus
}
#endif

