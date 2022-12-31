// 版权所有2020 Espressif Systems（上海）私人有限公司
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

/*******************************************************************************
 * 注意HAL不是公共api，不要在应用程序代码中使用。请参阅自述文件。soc/README.md中的md
 ******************************************************************************/

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "soc/gdma_struct.h"

typedef struct {
    gdma_dev_t *dev;
} gdma_hal_context_t;

void gdma_hal_init(gdma_hal_context_t *hal, int group_id);

#ifdef __cplusplus
}
#endif

