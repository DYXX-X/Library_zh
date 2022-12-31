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
#ifndef __ESP_PLATFORM_PTHREAD_H__
#define __ESP_PLATFORM_PTHREAD_H__

#include <sys/types.h>
#include <sys/time.h>
#include <sys/features.h>

#include_next <pthread.h>

#ifdef __cplusplus
extern "C" {
#endif

int pthread_condattr_getclock(const pthread_condattr_t * attr, clockid_t * clock_id);

int pthread_condattr_setclock(pthread_condattr_t *attr, clockid_t clock_id);

#ifdef __cplusplus
}
#endif

#endif // __ESP_PLATFORM_PTHREAD_H__

