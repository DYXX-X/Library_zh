/*
 * SPDX文件版权文本：2015-2021浓缩咖啡系统（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Memprot LL错误代码
 *
 */
typedef enum {
    MEMP_LL_OK = 0,
    MEMP_LL_FAIL = 1,
    MEMP_LL_ERR_SPLIT_ADDR_OUT_OF_RANGE = 2,
    MEMP_LL_ERR_SPLIT_ADDR_INVALID = 2,         /* S2版本的临时副本*/
    MEMP_LL_ERR_SPLIT_ADDR_UNALIGNED = 3,
    MEMP_LL_ERR_UNI_BLOCK_INVALID = 4,
    MEMP_LL_ERR_AREA_INVALID = 5,
    MEMP_LL_ERR_WORLD_INVALID = 6
} memprot_ll_err_t;

/**
 * @brief Memprot LL PMS世界ID
 *
 */
typedef enum {
    MEMP_LL_WORLD_NONE = 0x00,
    MEMP_LL_WORLD_0 = 0x01,
    MEMP_LL_WORLD_1 = 0x10
} memprot_ll_world_t;

/**
 * @brief Memprot LL PMS区域ID
 *
 */
typedef enum {
    MEMP_LL_AREA_NONE = 0,
    MEMP_LL_AREA_LOW = 1,
    MEMP_LL_AREA_HIGH = 2
} memprot_ll_area_t;

#ifdef __cplusplus
}
#endif

