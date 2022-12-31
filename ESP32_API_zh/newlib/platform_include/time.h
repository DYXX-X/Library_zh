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


#ifndef _ESP_TIME_H
#define _ESP_TIME_H

#ifdef __cplusplus
extern "C" {
#endif
#include_next <time.h>

#define _POSIX_TIMERS 1
#ifndef CLOCK_MONOTONIC
#define CLOCK_MONOTONIC (clockid_t)4
#endif
#ifndef CLOCK_BOOTTIME
#define CLOCK_BOOTTIME (clockid_t)4
#endif

int clock_settime(clockid_t clock_id, const struct timespec *tp);
int clock_gettime(clockid_t clock_id, struct timespec *tp);
int clock_getres(clockid_t clock_id, struct timespec *res);

#ifdef __cplusplus
}
#endif
#endif /* _ESP_TIME_H */

