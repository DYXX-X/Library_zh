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

#include "xt_instr_macros.h"

#ifdef __cplusplus
extern "C" {
#endif

static inline uint32_t mpu_ll_id_to_addr(unsigned id)
{
    // vpn-id
    // 0x00000000=0
    // 0x20000000=1
    // 0x40000000=2
    // 0x60000000=3
    // 0x80000000=4
    // 0xa0000000=5
    // 0xc0000000=6
    // 0xe000000=7
    return id * SOC_MPU_MIN_REGION_SIZE;
}

static inline void mpu_ll_set_region_rw(uint32_t addr)
{
    WDTLB(0x0, addr); // 缓存，无分配
}

static inline void mpu_ll_set_region_rwx(uint32_t addr)
{
    WDTLB(0x2, addr); // 旁路缓存
}

static inline void mpu_ll_set_region_x(uint32_t addr)
{
    WITLB(0x3, addr); // 高速缓存的
}

static inline void mpu_ll_set_region_illegal(uint32_t addr)
{
    WITLB(0xF, addr);
    WDTLB(0xF, addr);
}

#ifdef __cplusplus
}
#endif

