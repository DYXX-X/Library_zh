/******************************************************************************
 * 版权所有（C）2014谷歌公司。
 *
 *  根据Apache许可证2.0版（“许可证”）获得许可；除非符合许可证，否则不得使用此文件。您可以在以下地址获取许可证副本：
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 *  除非适用法律要求或书面同意，否则根据许可证分发的软件是按“原样”分发的，无任何明示或暗示的担保或条件。有关许可证下权限和限制的具体语言，请参阅许可证。
 *
 ******************************************************************************/

#ifndef _FIXED_QUEUE_H_
#define _FIXED_QUEUE_H_

#include <stdbool.h>
#include "osi/list.h"
#include "osi/semaphore.h"

#ifndef QUEUE_SIZE_MAX
#define QUEUE_SIZE_MAX                    254
#endif

#define FIXED_QUEUE_MAX_TIMEOUT           OSI_SEM_MAX_TIMEOUT

struct fixed_queue_t;

typedef struct fixed_queue_t fixed_queue_t;
//typedef结构reactor_t反应器_t；

typedef void (*fixed_queue_free_cb)(void *data);
typedef void (*fixed_queue_cb)(fixed_queue_t *queue);

// 创建具有给定|容量|的新固定队列。如果元素多于
// |容量|被添加到队列中，调用者将被阻止，直到空间
// 在队列中可用。失败时返回NULL。呼叫者必须释放
// 返回的队列具有|fixedqueue_free |。
fixed_queue_t *fixed_queue_new(size_t capacity);

// 释放当前正在使用的队列（即有服务员）
// 被阻挡在其上）导致未定义的行为。
void fixed_queue_free(fixed_queue_t *queue, fixed_queue_free_cb free_cb);

// 返回一个值，该值指示给定的|queue|是否为空。如果|队列|
// 为NULL，则返回值为true。
bool fixed_queue_is_empty(fixed_queue_t *queue);

// 返回|queue|的长度。如果|queue|为NULL，则返回值
// 为0。
size_t fixed_queue_length(fixed_queue_t *queue);

// 返回此队列可以容纳的最大元素数|队列|可能
// 不能为NULL。
size_t fixed_queue_capacity(fixed_queue_t *queue);

// 将给定的|数据|排入|队列|。根据参数timeout，调用者将被阻止或立即返回或等待超时。
// 如果入队失败，它将返回false，否则返回true
bool fixed_queue_enqueue(fixed_queue_t *queue, void *data, uint32_t timeout);

// 将下一个元素从|queue|中取消排队。如果队列当前为空，
// 此函数将阻止调用者，直到项目进入队列，或者根据参数timeout立即返回或等待超时。
// 如果出队失败，它将返回NULL，否则返回一个点。
void *fixed_queue_dequeue(fixed_queue_t *queue, uint32_t timeout);

// 返回|queue|中的第一个元素（如果存在），而不将其退出队列。
// 此函数永远不会阻止调用者。如果没有，则返回NULL
// 队列或|queue|中的元素为NULL。
void *fixed_queue_try_peek_first(fixed_queue_t *queue);

// 返回|queue|中的最后一个元素（如果存在），而不将其退出队列。
// 此函数永远不会阻止调用者。如果没有，则返回NULL
// 队列或|queue|中的元素为NULL。
void *fixed_queue_try_peek_last(fixed_queue_t *queue);

// 尝试从|queue|的中间删除|data|元素。这
// 函数永远不会阻止调用者。如果队列为空或NULL
// 函数立即返回NULL|data|不能为NULL。如果|数据|
// 元素，则返回指向已删除数据的指针，
// 否则为NULL。
void *fixed_queue_try_remove_from_queue(fixed_queue_t *queue, void *data);

// 返回包含|queue|中所有条目的可迭代列表。此函数
// 永远不会阻止呼叫者|queue|不能为NULL。
//
// 注意：此函数的返回结果不是线程安全的：列表可能
// 被另一个线程修改，结果将是不可预测的。
// TODO:应重构此函数的用法
// 其本身应被移除。
list_t *fixed_queue_get_list(fixed_queue_t *queue);

// 此函数返回有效的文件描述符。呼叫者可以执行一个
// fd上的操作：select（2）。如果|select|表示文件
// 描述符是可读的，调用者可以在没有
// 舞台调度。调用方不能关闭返回的文件描述符|队列|
// 不能为NULL。
//int fixed_queue_get_enqueue_fd（常量fixed_排队_t*队列）；

// 此函数返回有效的文件描述符。呼叫者可以执行一个
// fd上的操作：select（2）。如果|select|表示文件
// 描述符是可读的，调用者可以调用|fixed_queue_dequeue|
// 舞台调度。调用方不能关闭返回的文件描述符|队列|
// 不能为NULL。
//int fixedqueue_get_dequeue_fd（常量fixedqueue_t*队列）；

// 向|reactor|注册|queue|以进行出列操作。当存在元素时
// 在队列中，将调用readycb。传递|context|参数，
// 返回回调例程。|queue|、|reactor|或|read_cb|都不能为NULL。
// |context|可以为NULL。
void fixed_queue_register_dequeue(fixed_queue_t *queue, fixed_queue_cb ready_cb);

// 从任何反应器中注销|queue|的出列就绪回调
// 如果有，则在注册。此函数是幂等的。
void fixed_queue_unregister_dequeue(fixed_queue_t *queue);

void fixed_queue_process(fixed_queue_t *queue);

list_t *fixed_queue_get_list(fixed_queue_t *queue);

#endif

