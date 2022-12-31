/*
 * SPDX文件版权文本：2018-2021浓缩咖啡系统（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */

#pragma once

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 检查半开间隔是否重叠
 *
 * @param start1  间隔1开始
 * @param end1    间隔1结束
 * @param start2  间隔2启动
 * @param end2    间隔2结束
 * @return true iff[start1；end1）重叠[start2；end2）
 */
static inline bool bootloader_util_regions_overlap(
        const intptr_t start1, const intptr_t end1,
        const intptr_t start2, const intptr_t end2)
{
    assert(end1>start1);
    assert(end2>start2);
    return (end1 > start2 && end2 > start1);
}

#ifdef __cplusplus
}
#endif

