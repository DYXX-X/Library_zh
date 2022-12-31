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

#include "esp_err.h"

#include "hal/mpu_types.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * 指定内存区域上允许的访问类型。
 *
 * @param id 区域表索引；在非SOC_MPU_CONFIGURABLE_REGIONS_SUPPORTED的目标上，区域划分在硬件中预定义，这可能反映在LL实现中。
 * @param access 允许的访问类型
 */
void mpu_hal_set_region_access(int id, mpu_access_t access);

#ifdef __cplusplus
}
#endif

