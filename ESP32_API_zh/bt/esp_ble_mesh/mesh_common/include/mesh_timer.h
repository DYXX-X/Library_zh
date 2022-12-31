/*
 * SPDX文件版权文本：2016 Wind River Systems，Inc.SPDX File贡献者：2018-2021浓缩咖啡系统（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */

#ifndef _BLE_MESH_TIMER_H_
#define _BLE_MESH_TIMER_H_

#include "mesh_types.h"
#include "mesh_slist.h"
#include "mesh_atomic.h"

#ifdef __cplusplus
extern "C" {
#endif

/* 每次使用的nsec数量*/
#define NSEC_PER_USEC   1000

/* 每毫秒微秒数*/
#define USEC_PER_MSEC   1000

/* 每秒毫秒数*/
#define MSEC_PER_SEC    1000

/* 每秒微秒数*/
#define USEC_PER_SEC    ((USEC_PER_MSEC) * (MSEC_PER_SEC))

/* 每秒纳秒数*/
#define NSEC_PER_SEC    ((NSEC_PER_USEC) * (USEC_PER_MSEC) * (MSEC_PER_SEC))

/* 超时未使用*/
#define _INACTIVE       (-1)

struct k_work;

/**
 * @typedef k_work_handler_t
 * @brief 工作项处理程序函数类型。
 *
 * 当工作队列处理工作项时，工作项的处理程序函数由工作队列的线程执行。
 *
 * @param work 工作项的地址。
 *
 * @return N/A
 */
typedef void (*k_work_handler_t)(struct k_work *work);

struct k_work {
    void *_reserved;
    k_work_handler_t handler;
    int index;
};

#define _K_WORK_INITIALIZER(work_handler)   \
{                                           \
    ._reserved = NULL,                      \
    .handler = work_handler,                \
}

/**
 * @brief 生成空超时延迟。
 *
 * 此宏生成超时延迟，指示内核API在无法立即执行请求的操作时不要等待。
 *
 * @return 超时延迟值。
 */
#define K_NO_WAIT       0

/**
 * @brief 从毫秒生成超时延迟。
 *
 * 此宏生成指示内核API的超时延迟
 * to wait up to @a 毫秒以执行请求的操作。
 *
 * @param ms 持续时间（毫秒）。
 *
 * @return 超时延迟值。
 */
#define K_MSEC(ms)      (ms)

/**
 * @brief 从秒开始生成超时延迟。
 *
 * 此宏生成指示内核API的超时延迟
 * to wait up to @a s秒以执行请求的操作。
 *
 * @param s 持续时间（秒）。
 *
 * @return 超时延迟值。
 */
#define K_SECONDS(s)    K_MSEC((s) * MSEC_PER_SEC)

/**
 * @brief 从分钟生成超时延迟。
 *
 * 此宏生成指示内核API的超时延迟
 * to wait up to @a m分钟以执行请求的操作。
 *
 * @param m 持续时间（分钟）。
 *
 * @return 超时延迟值。
 */
#define K_MINUTES(m)    K_SECONDS((m) * 60)

/**
 * @brief 从小时生成超时延迟。
 *
 * 此宏生成指示内核API的超时延迟
 * to wait up to @a h小时以执行请求的操作。
 *
 * @param h 持续时间（小时）。
 *
 * @return 超时延迟值。
 */
#define K_HOURS(h)      K_MINUTES((h) * 60)

/**
 * @brief 生成无限超时延迟。
 *
 * 此宏生成超时延迟，指示内核API等待执行请求的操作所需的时间。
 *
 * @return 超时延迟值。
 */
#define K_FOREVER       (-1)

/**
 * @brief 获取系统正常运行时间（32位版本）。
 *
 * 此例程返回自系统启动以来所用时间的较低32位（以毫秒为单位）。
 *
 * 此例程可以比k_uptime_get（）更高效，因为它减少了中断锁定和64位数学运算的需要。然而，32位结果不能保持系统正常运行时间超过大约50天，因此调用者必须处理可能的回滚。
 *
 * @return 当前正常运行时间。
 */
uint32_t k_uptime_get_32(void);

struct k_delayed_work {
    struct k_work work;
};

/**
 * @brief 将延迟的工作项提交到系统工作队列。
 *
 * This routine schedules work item @a 系统要处理的工作
 * workqueue after a delay of @a 延迟毫秒。例程启动工作项的异步倒计时，然后返回给调用者。只有当倒计时完成时，工作项才实际提交到工作队列并成为挂起状态。
 *
 * 提交之前提交的仍在倒计时的延迟工作项将取消现有提交，并使用新的延迟重新开始倒计时。如果工作项当前在工作队列的队列中挂起，因为已完成倒计时，则重新提交该项太晚了，并且重新提交失败而不会影响工作项。如果工作项已被处理或当前正在处理，则认为其工作已完成，可以重新提交工作项。
 *
 * @warning 提交到系统工作队列的工作项应避免使用阻塞或屈服的处理程序，因为这可能会阻止系统工作队列及时处理其他工作项。
 *
 * @note 可由ISR调用。
 *
 * @param work 延迟工作项的地址。
 * @param delay 提交工作项之前的延迟（毫秒）。
 *
 * @retval 0工作项倒计时已开始。
 * @retval -EINPROGRESS工作项已挂起。
 * @retval -EINVAL工作项正在处理或已完成其工作。
 * @retval -EADDRINUSE工作项在其他工作队列上挂起。
 */
int k_delayed_work_submit(struct k_delayed_work *work, int32_t delay);

int k_delayed_work_submit_periodic(struct k_delayed_work *work, int32_t period);

/**
 * @brief 在安排延迟工作之前获得剩余时间。
 *
 * 此例程计算执行延迟工作之前剩余的（近似）时间。如果延迟的工作未等待调度，则返回零。
 *
 * @param work     延迟的工作项。
 *
 * @return 剩余时间（毫秒）。
 */
int32_t k_delayed_work_remaining_get(struct k_delayed_work *work);

/**
 * @brief 将工作项提交到系统工作队列。
 *
 * This routine submits work item @a 要由系统工作队列处理的工作。如果由于较早的提交，工作项已在工作队列的队列中挂起，则此例程对工作项没有影响。如果工作项已被处理或当前正在处理，则认为其工作已完成，可以重新提交工作项。
 *
 * @warning 提交到系统工作队列的工作项应避免使用阻塞或屈服的处理程序，因为这可能会阻止系统工作队列及时处理其他工作项。
 *
 * @note 可由ISR调用。
 *
 * @param work 工作项的地址。
 *
 * @return N/A
 */
static inline void k_work_submit(struct k_work *work)
{
    if (work && work->handler) {
        work->handler(work);
    }
}

/**
 * @brief 初始化工作项。
 *
 * 此例程在首次使用工作队列工作项之前对其进行初始化。
 *
 * @param work 工作项的地址。
 * @param handler 函数在每次处理工作项时调用。
 *
 * @return N/A
 */
static inline void k_work_init(struct k_work *work, k_work_handler_t handler)
{
    work->handler = handler;
}

int k_delayed_work_cancel(struct k_delayed_work *work);

int k_delayed_work_free(struct k_delayed_work *work);

int k_delayed_work_init(struct k_delayed_work *work, k_work_handler_t handler);

/**
 * @brief 获取系统正常运行时间。
 *
 * 此例程返回自系统启动以来经过的时间（以毫秒为单位）。
 *
 * @return 当前正常运行时间。
 */
int64_t k_uptime_get(void);

void bt_mesh_timer_init(void);
void bt_mesh_timer_deinit(void);

#ifdef __cplusplus
}
#endif

#endif /* _BLE_MESH_TIMER_H_ */

