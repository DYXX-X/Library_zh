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

#ifndef __THREAD_H__
#define __THREAD_H__

#include "freertos/FreeRTOSConfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/queue.h"
#include "freertos/task.h"
#include "osi/semaphore.h"
#include "esp_task.h"
#include "bt_common.h"

#define portBASE_TYPE int

#define OSI_THREAD_MAX_TIMEOUT OSI_SEM_MAX_TIMEOUT

struct osi_thread;

typedef struct osi_thread osi_thread_t;

typedef void (*osi_thread_func_t)(void *context);

typedef enum {
    OSI_THREAD_CORE_0 = 0,
    OSI_THREAD_CORE_1,
    OSI_THREAD_CORE_AFFINITY,
} osi_thread_core_t;

/*
 * brief：创建线程或任务param name：thread name param stack_size：线程堆栈大小param priority：线程优先级param core：此线程运行的CPU内核，OSI_thread_core_AFFINITY表示非特定CPU内核param work_queue_num:指定队列号，队列[0]具有最高优先级，优先级按索引递减return：如果创建成功，返回线程处理程序；否则返回NULL。
 */
osi_thread_t *osi_thread_create(const char *name, size_t stack_size, int priority, osi_thread_core_t core, uint8_t work_queue_num);

/*
 * brief：销毁线程或任务参数thread：线程点处理程序
 */
void osi_thread_free(osi_thread_t *thread);

/*
 * brief：向线程发送消息，并告诉线程调用函数param thread：线程处理程序的点param func：目标线程调用的回调函数param context：回调函数的参数param queue_idx：消息发送给参数的队列timeout：Post timeout，OSI_thread_MAX_timeout表示永远阻塞，0表示永远阻塞，其他值表示块毫秒返回：如果post成功，则返回true，否则返回false
 */
bool osi_thread_post(osi_thread_t *thread, osi_thread_func_t func, void *context, int queue_idx, uint32_t timeout);

/*
 * brief：设置线程的优先级param thread：线程处理程序的点param priority：priority return：如果设置成功，则返回true，否则返回false
 */
bool osi_thread_set_priority(osi_thread_t *thread, int priority);

/* brief：获取线程名称param thread：线程处理程序的返回点：线程名称的常量点
 */
const char *osi_thread_name(osi_thread_t *thread);

/* brief：获取指定队列的大小param thread：线程处理程序的点param wq_idx：线程的队列索引return：队列大小
 */
int osi_thread_queue_wait_size(osi_thread_t *thread, int wq_idx);

#endif /* __THREAD_H__ */

