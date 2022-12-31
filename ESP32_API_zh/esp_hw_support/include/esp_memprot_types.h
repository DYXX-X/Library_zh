/*
 * SPDX文件版权文本：2021浓缩咖啡系统（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief PMS World类型（每个PMS区域的属性，类似于x86环方案）
 */
typedef enum {
    MEMPROT_PMS_WORLD_NONE                      = 0x00000000,
    MEMPROT_PMS_WORLD_0                         = 0x00000001,
    MEMPROT_PMS_WORLD_1                         = 0x00000002,
    MEMPROT_PMS_WORLD_2                         = 0x00000004,
    MEMPROT_PMS_WORLD_ALL                       = 0x7FFFFFFF,
    MEMPROT_PMS_WORLD_INVALID                   = 0x80000000
} esp_mprot_pms_world_t;

/**
 * @brief PMS识别的内存操作/权限类型
 */
#define MEMPROT_OP_NONE                         0x00000000
#define MEMPROT_OP_READ                         0x00000001
#define MEMPROT_OP_WRITE                        0x00000002
#define MEMPROT_OP_EXEC                         0x00000004
#define MEMPROT_OP_INVALID                      0x80000000

#ifdef __cplusplus
}
#endif

