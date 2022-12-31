// 版权所有2018 Espressif Systems（上海）私人有限公司
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

#include "esp_vfs_fat.h"
#include <sys/param.h>
#include <stddef.h>

static inline size_t esp_vfs_fat_get_allocation_unit_size(
        size_t sector_size, size_t requested_size)
{
    size_t alloc_unit_size = requested_size;
    const size_t max_sectors_per_cylinder = 128;
    const size_t max_size = sector_size * max_sectors_per_cylinder;
    alloc_unit_size = MAX(alloc_unit_size, sector_size);
    alloc_unit_size = MIN(alloc_unit_size, max_size);
    return alloc_unit_size;
}

