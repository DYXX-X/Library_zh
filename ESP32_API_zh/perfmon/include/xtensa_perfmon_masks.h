
// 版权所有2018-2019 Espressif Systems（Shanghai）PTE LTD
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

#ifndef _xtensa_perfmon_masks_H_
#define _xtensa_perfmon_masks_H_
#include <inttypes.h>
#include "xtensa/xt_perf_consts.h"

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * @brief 选择参数的说明
 *
 * 结构定义性能计数器不同选择值的描述
 */
typedef struct xtensa_perfmon_select {
    int select; /*!<  所选计数器*/
    const char *description; /*!<  所选计数器的说明*/
} xtensa_perfmon_select_t;

/**
 * @brief 掩码参数说明
 *
 * 结构定义性能计数器的不同选择和掩码值的描述
 */
typedef struct xtensa_perfmon_masks {
    int select; /*!<  所选计数器*/
    int mask; /*!<  所选计数器掩码*/
    const char *description; /*!<  所选掩码的说明*/
} xtensa_perfmon_masks_t;

// 性能计数器事件的最大数量
#define MAX_PERFMON_EVENTS 119

/**
 * @brief 选择值描述表
 *
 * 表包含性能计数器不同“选择”值的说明
 */
extern const xtensa_perfmon_select_t xtensa_perfmon_select_table[];

/**
 * @brief 掩码值描述表
 *
 * 表包含性能计数器不同“select”和“mask”值的说明
 */
extern const xtensa_perfmon_masks_t xtensa_perfmon_masks_table[];

/**
 * @brief 所有可用计数器
 *
 * 表包含所有可用计数器
 */
extern const uint32_t xtensa_perfmon_select_mask_all[MAX_PERFMON_EVENTS * 2];

#ifdef __cplusplus
}
#endif
#endif // _扩展_性能_任务_ H_

