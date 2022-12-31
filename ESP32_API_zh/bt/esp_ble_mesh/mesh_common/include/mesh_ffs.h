/*
 * SPDX文件版权文本：2015 Wind River Systems，Inc
 *
 * SPDX许可证标识符：Apache-2.0
 */

#ifndef _BLE_MESH_FFS_H_
#define _BLE_MESH_FFS_H_

#include "mesh_types.h"
#include "mesh_compiler.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 *
 * @brief 查找32位字中的最高有效位集
 *
 * 此例程从传入的参数中的最高有效位开始查找第一个位集，并返回该位的索引。位从最低有效位开始从1开始编号。返回值为零表示传递的值为零。
 *
 * @return 最高有效位集，如果@a op为0，则为0
 */

static ALWAYS_INLINE unsigned int find_msb_set(uint32_t op)
{
    if (op == 0) {
        return 0;
    }

    return 32 - __builtin_clz(op);
}

/**
 *
 * @brief 查找32位字中的最低有效位集
 *
 * 此例程从传入的参数中的最低有效位开始查找第一个位集，并返回该位的索引。位从最低有效位开始从1开始编号。返回值为零表示传递的值为零。
 *
 * @return 最低有效位集，如果@a op为0，则为0
 */

static ALWAYS_INLINE unsigned int find_lsb_set(uint32_t op)
{
    return __builtin_ffs(op);
}

#ifdef __cplusplus
}
#endif

#endif /* _BLE_MESH_FFS_H_ */

