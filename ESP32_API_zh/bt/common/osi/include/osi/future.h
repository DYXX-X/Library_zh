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

#ifndef __FUTURE_H__
#define __FUTURE_H__

#include "osi/semaphore.h"

struct future {
    bool ready_can_be_called;
    osi_sem_t semaphore; // NULL信号量表示不久的将来
    void *result;
};
typedef struct future future_t;

#define FUTURE_SUCCESS ((void *)1)
#define FUTURE_FAIL ((void *)0)

// 构造一个新的future_t对象。失败时返回NULL。
future_t *future_new(void);

// 使用立即值|值|构造一个新的future_t对象。无需等待
// 在调用|future_await|时发生，因为该值已经存在。
// 失败时返回NULL。
future_t *future_new_immediate(void *value);

// 表示|future|已就绪，将|value|传递回上下文
// 等待结果。每个未来只能调用一次。
// |future |不能为NULL。
void future_ready(future_t *future, void *value);

// 等待|未来|准备就绪。返回|future_ready|中设置的值。
// 在回归之前释放未来|future |不能为NULL。
void *future_await(future_t *async_result);

//如果不使用“未来”，则释放未来
void future_free(future_t *future);
#endif /* __FUTURE_H__ */

