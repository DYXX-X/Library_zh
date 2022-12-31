// 版权所有2020 Espressif Systems（上海）私人有限公司
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

#include <stdint.h>

#include "soc/soc_caps.h"

#ifdef __cplusplus
extern "C" {
#endif

/* 此LL当前未用于ESP32-C3-清理为TODO ESP32-C3 IDF-2375*/

static inline uint32_t mpu_ll_id_to_addr(unsigned id)
{
    abort();
}

static inline void mpu_ll_set_region_rw(uint32_t addr)
{
    abort();
}

static inline void mpu_ll_set_region_rwx(uint32_t addr)
{
    abort();
}

static inline void mpu_ll_set_region_x(uint32_t addr)
{
    abort();
}


static inline void mpu_ll_set_region_illegal(uint32_t addr)
{
    abort();
}

#ifdef __cplusplus
}
#endif

