/******************************************************************************
 * 版权所有（C）2015谷歌公司。
 *
 *  根据Apache许可证2.0版（“许可证”）获得许可；除非符合许可证，否则不得使用此文件。您可以在以下地址获取许可证副本：
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 *  除非适用法律要求或书面同意，否则根据许可证分发的软件是按“原样”分发的，无任何明示或暗示的担保或条件。有关许可证下权限和限制的具体语言，请参阅许可证。
 *
 ******************************************************************************/

#ifndef __MUTEX_H__
#define __MUTEX_H__

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "freertos/semphr.h"
#include "osi/semaphore.h"

#define OSI_MUTEX_MAX_TIMEOUT OSI_SEM_MAX_TIMEOUT

#define osi_mutex_valid( x ) ( ( ( *x ) == NULL) ? pdFALSE : pdTRUE )
#define osi_mutex_set_invalid( x ) ( ( *x ) = NULL )

typedef xSemaphoreHandle osi_mutex_t;

int osi_mutex_new(osi_mutex_t *mutex);

int osi_mutex_lock(osi_mutex_t *mutex, uint32_t timeout);

void osi_mutex_unlock(osi_mutex_t *mutex);

void osi_mutex_free(osi_mutex_t *mutex);

/* 仅用于全局互斥*/
int osi_mutex_global_init(void);

void osi_mutex_global_deinit(void);

void osi_mutex_global_lock(void);

void osi_mutex_global_unlock(void);

#endif /* __MUTEX_H__ */

