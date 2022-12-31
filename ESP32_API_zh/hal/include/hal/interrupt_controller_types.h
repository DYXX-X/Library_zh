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

#pragma once

#include "soc/soc_caps.h"
#include "soc/soc.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    INTDESC_NORMAL=0,
    INTDESC_RESVD,
    INTDESC_SPECIAL,
} int_desc_flag_t;

typedef enum {
    INTTP_LEVEL=0,
    INTTP_EDGE,
    INTTP_NA,
} int_type_t;

typedef struct {
    int level;
    int_type_t type;
    int_desc_flag_t cpuflags[SOC_CPU_CORES_NUM];
} int_desc_t;

typedef void (*interrupt_handler_t)(void *arg);

#ifdef __cplusplus
}
#endif

