// 版权所有2015-2016 Espressif Systems（上海）私人有限公司
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

/**
 * common/bt_defs。h为整个Bluedroid定义有用的API
 *
 */
#ifndef _BT_DEFS_H_
#define _BT_DEFS_H_

#include <stdlib.h>
#include <stdint.h>
#include <arpa/inet.h>
#include "bt_common.h"
#include "common/bt_target.h"

#define UNUSED(x)                   (void)(x)

/*计时器相关定义*/

//作者Snake.T
typedef void (TIMER_CBACK)(void *p_tle);
typedef struct _tle {
    struct _tle  *p_next;
    struct _tle  *p_prev;
    TIMER_CBACK  *p_cback;
    INT32         ticks;
    INT32         ticks_initial;
    TIMER_PARAM_TYPE   param;
    TIMER_PARAM_TYPE   data;
    UINT16        event;
    UINT8         in_use;
} TIMER_LIST_ENT;

#define alarm_timer_t               uint32_t
#define alarm_timer_setfn(timer, cb, data)           \
do {                                                 \
} while (0)
#define alarm_timer_arm(timer, to, periodic)         \
do {                                                 \
} while (0)
#define alarm_timer_disarm(timer)                    \
do {                                                 \
} while (0)
#define alarm_timer_now()             (0)


/*蓝牙地址*/
typedef struct {
    uint8_t address[6];
} __attribute__ ((__packed__)) bt_bdaddr_t;

/**蓝牙128位UUID*/
typedef struct {
    uint8_t uu[16];
} bt_uuid_t;

#ifndef CPU_LITTLE_ENDIAN
#define CPU_LITTLE_ENDIAN
#endif

#endif /* _BT_DEFS_H_ */

