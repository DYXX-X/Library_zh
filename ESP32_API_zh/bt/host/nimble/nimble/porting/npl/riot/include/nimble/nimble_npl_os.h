/*
 * 根据一个或多个贡献者许可协议向Apache Software Foundation（ASF）许可。有关版权所有权的更多信息，请参阅随本作品分发的通知文件。ASF根据Apache许可证2.0版（“许可证”）向您许可此文件；除非符合许可证，否则不得使用此文件。您可以在以下地址获取许可证副本：
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 * 除非适用法律要求或书面同意，否则根据许可证分发的软件是按“原样”分发的，无任何明示或暗示的担保或条件。有关许可证下权限和限制的具体语言，请参阅许可证。
 */

#ifndef _NIMBLE_NPL_OS_H_
#define _NIMBLE_NPL_OS_H_

#include <stdint.h>
#include <stdbool.h>
#include "event/callback.h"
#include "mutex.h"
#include "semaphore.h"
#include "xtimer.h"

#ifdef __cplusplus
extern "C" {
#endif

#define BLE_NPL_OS_ALIGNMENT    4

#define BLE_NPL_TIME_FOREVER    UINT32_MAX

typedef uint32_t ble_npl_time_t;
typedef int32_t ble_npl_stime_t;

extern volatile int ble_npl_in_critical;

struct ble_npl_event {
    event_callback_t e;
    void *arg;
};

struct ble_npl_eventq {
    event_queue_t q;
};

struct ble_npl_callout {
    xtimer_t timer;
    uint64_t target_us;
    struct ble_npl_event e;
    event_queue_t *q;
};

struct ble_npl_mutex {
    mutex_t mu;
};

struct ble_npl_sem {
    sem_t sem;
};

static inline bool
ble_npl_os_started(void)
{
    return true;
}

static inline void *
ble_npl_get_current_task_id(void)
{
    return (void *)(uint32_t)thread_getpid();
}

static inline void
ble_npl_eventq_init(struct ble_npl_eventq *evq)
{
    event_queue_init_detached(&evq->q);
}

static inline void
ble_npl_eventq_put(struct ble_npl_eventq *evq, struct ble_npl_event *ev)
{
    event_post(&evq->q, &ev->e.super);
}

static inline struct ble_npl_event *
ble_npl_eventq_get(struct ble_npl_eventq *evq, ble_npl_time_t tmo)
{
    if (evq->q.waiter == NULL) {
        event_queue_claim(&evq->q);
    }

    if (tmo == 0) {
        return (struct ble_npl_event *)event_get(&evq->q);
    } else if (tmo == BLE_NPL_TIME_FOREVER) {
        return (struct ble_npl_event *)event_wait(&evq->q);
    } else {
        return (struct ble_npl_event *)event_wait_timeout64(&evq->q,
                                                            tmo * US_PER_MS);
    }
}

static inline void
ble_npl_eventq_remove(struct ble_npl_eventq *evq, struct ble_npl_event *ev)
{
    event_cancel(&evq->q, &ev->e.super);
}

static inline void
ble_npl_event_run(struct ble_npl_event *ev)
{
    ev->e.super.handler(&ev->e.super);
}

static inline void
ble_npl_event_init(struct ble_npl_event *ev, ble_npl_event_fn *fn, void *arg)
{
    /*
     * 需要手动清除list_node，因为下面的init函数不执行此操作。
     */
    ev->e.super.list_node.next = NULL;
    event_callback_init(&ev->e, (void(*)(void *))fn, ev);
    ev->arg = arg;
}

static inline bool
ble_npl_event_is_queued(struct ble_npl_event *ev)
{
    return (ev->e.super.list_node.next != NULL);
}

static inline void *
ble_npl_event_get_arg(struct ble_npl_event *ev)
{
    return ev->arg;
}

static inline void
ble_npl_event_set_arg(struct ble_npl_event *ev, void *arg)
{
    ev->arg = arg;
}

static inline ble_npl_error_t
ble_npl_mutex_init(struct ble_npl_mutex *mu)
{
    mutex_init(&mu->mu);
    return BLE_NPL_OK;
}

static inline ble_npl_error_t
ble_npl_mutex_pend(struct ble_npl_mutex *mu, ble_npl_time_t timeout)
{
    assert(timeout == BLE_NPL_TIME_FOREVER);
    (void)timeout;

    mutex_lock(&mu->mu);
    return BLE_NPL_OK;
}

static inline ble_npl_error_t
ble_npl_mutex_release(struct ble_npl_mutex *mu)
{
    mutex_unlock(&mu->mu);
    return BLE_NPL_OK;
}

static inline ble_npl_error_t
ble_npl_sem_init(struct ble_npl_sem *sem, uint16_t tokens)
{
    int rc;

    rc = sem_init(&sem->sem, 0, tokens);

    return rc == 0 ? BLE_NPL_OK : BLE_NPL_ERROR;
}

static inline ble_npl_error_t
ble_npl_sem_release(struct ble_npl_sem *sem)
{
    int rc;

    rc = sem_post(&sem->sem);

    return rc == 0 ? BLE_NPL_OK : BLE_NPL_ERROR;
}

static inline uint16_t
ble_npl_sem_get_count(struct ble_npl_sem *sem)
{
    int val = 0;

    sem_getvalue(&sem->sem, &val);

    return (uint16_t)val;
}

static inline void
ble_npl_callout_stop(struct ble_npl_callout *co)
{
    xtimer_remove(&co->timer);
}

static inline bool
ble_npl_callout_is_active(struct ble_npl_callout *c)
{
    return (c->timer.offset || c->timer.long_offset);
}

static inline ble_npl_time_t
ble_npl_callout_get_ticks(struct ble_npl_callout *co)
{
    return (ble_npl_time_t)(co->target_us / US_PER_MS);
}

static inline void
ble_npl_callout_set_arg(struct ble_npl_callout *co, void *arg)
{
    co->e.arg = arg;
}

static inline ble_npl_time_t
ble_npl_time_get(void)
{
    return (ble_npl_time_t)(xtimer_now_usec64() / US_PER_MS);
}

static inline ble_npl_error_t
ble_npl_time_ms_to_ticks(uint32_t ms, ble_npl_time_t *out_ticks)
{
    *out_ticks = ms;
    return BLE_NPL_OK;
}

static inline ble_npl_error_t
ble_npl_time_ticks_to_ms(ble_npl_time_t ticks, uint32_t *out_ms)
{
    *out_ms = ticks;
    return BLE_NPL_OK;
}

static inline ble_npl_time_t
ble_npl_time_ms_to_ticks32(uint32_t ms)
{
    return ms;
}

static inline uint32_t
ble_npl_time_ticks_to_ms32(ble_npl_time_t ticks)
{
    return ticks;
}

static inline void
ble_npl_time_delay(ble_npl_time_t ticks)
{
    xtimer_usleep64(ticks * US_PER_MS);
}

static inline uint32_t
ble_npl_hw_enter_critical(void)
{
    uint32_t ctx = irq_disable();
    ++ble_npl_in_critical;
    return ctx;
}

static inline void
ble_npl_hw_exit_critical(uint32_t ctx)
{
    --ble_npl_in_critical;
    irq_restore((unsigned)ctx);
}

static inline bool
ble_npl_hw_is_in_critical(void)
{
    /*
     * XXX当前RIOT不支持用于查明中断当前是否被禁用的API，因此在本文的关键部分。现在，我们使用这个全局变量来保持这个状态。
    -*/
    return (ble_npl_in_critical > 0);
}

#ifdef __cplusplus
}
#endif

#endif  /* _NPL_H_ */

