/*
 * 根据一个或多个贡献者许可协议向Apache Software Foundation（ASF）许可。有关版权所有权的更多信息，请参阅随本作品分发的通知文件。ASF根据Apache许可证2.0版（“许可证”）向您许可此文件；除非符合许可证，否则不得使用此文件。您可以在以下地址获取许可证副本：
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 * 除非适用法律要求或书面同意，否则根据许可证分发的软件是按“原样”分发的，无任何明示或暗示的担保或条件。有关许可证下权限和限制的具体语言，请参阅许可证。
 */

#ifndef _NIMBLE_NPL_OS_H_
#define _NIMBLE_NPL_OS_H_

#include <assert.h>
#include <stdint.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/queue.h"
#include "freertos/semphr.h"
#include "freertos/task.h"
#include "freertos/timers.h"

#ifdef __cplusplus
extern "C" {
#endif

#define BLE_NPL_OS_ALIGNMENT    4

#define BLE_NPL_TIME_FOREVER    portMAX_DELAY

/* 这应该与TickType_t兼容*/
typedef uint32_t ble_npl_time_t;
typedef int32_t ble_npl_stime_t;

struct ble_npl_event {
    bool queued;
    ble_npl_event_fn *fn;
    void *arg;
};

struct ble_npl_eventq {
    QueueHandle_t q;
};

struct ble_npl_callout {
#if CONFIG_BT_NIMBLE_USE_ESP_TIMER
   esp_timer_handle_t handle;
#else
    TimerHandle_t handle;
#endif
    struct ble_npl_eventq *evq;
    struct ble_npl_event ev;
};

struct ble_npl_mutex {
    SemaphoreHandle_t handle;
};

struct ble_npl_sem {
    SemaphoreHandle_t handle;
};

/*
 * 简单的API只是在下面定义为静态内联，但有些API有点复杂，或者需要一些全局状态变量，因此在.c文件中定义，静态内联包装器只是调用适当的实现。我们需要这些函数的声明，它们在下面的标题中定义。
 */
#include "npl_freertos.h"

static inline bool
ble_npl_os_started(void)
{
    return xTaskGetSchedulerState() != taskSCHEDULER_NOT_STARTED;
}

static inline void *
ble_npl_get_current_task_id(void)
{
    return xTaskGetCurrentTaskHandle();
}

static inline void
ble_npl_eventq_init(struct ble_npl_eventq *evq)
{
    evq->q = xQueueCreate(32, sizeof(struct ble_npl_eventq *));
}

static inline void
ble_npl_eventq_deinit(struct ble_npl_eventq *evq)
{
    vQueueDelete(evq->q);
}

static inline struct ble_npl_event *
ble_npl_eventq_get(struct ble_npl_eventq *evq, ble_npl_time_t tmo)
{
    return npl_freertos_eventq_get(evq, tmo);
}

static inline void
ble_npl_eventq_put(struct ble_npl_eventq *evq, struct ble_npl_event *ev)
{
    npl_freertos_eventq_put(evq, ev);
}

static inline void
ble_npl_eventq_remove(struct ble_npl_eventq *evq, struct ble_npl_event *ev)
{
    npl_freertos_eventq_remove(evq, ev);
}

static inline void
ble_npl_event_run(struct ble_npl_event *ev)
{
    ev->fn(ev);
}

static inline bool
ble_npl_eventq_is_empty(struct ble_npl_eventq *evq)
{
    return xQueueIsQueueEmptyFromISR(evq->q);
}

static inline void
ble_npl_event_init(struct ble_npl_event *ev, ble_npl_event_fn *fn,
                   void *arg)
{
    memset(ev, 0, sizeof(*ev));
    ev->fn = fn;
    ev->arg = arg;
}

static inline bool
ble_npl_event_is_queued(struct ble_npl_event *ev)
{
    return ev->queued;
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
    return npl_freertos_mutex_init(mu);
}

static inline ble_npl_error_t
ble_npl_mutex_deinit(struct ble_npl_mutex *mu)
{
    return npl_freertos_mutex_deinit(mu);
}

static inline ble_npl_error_t
ble_npl_mutex_pend(struct ble_npl_mutex *mu, ble_npl_time_t timeout)
{
    return npl_freertos_mutex_pend(mu, timeout);
}

static inline ble_npl_error_t
ble_npl_mutex_release(struct ble_npl_mutex *mu)
{
    return npl_freertos_mutex_release(mu);
}

static inline ble_npl_error_t
ble_npl_sem_init(struct ble_npl_sem *sem, uint16_t tokens)
{
    return npl_freertos_sem_init(sem, tokens);
}

static inline ble_npl_error_t
ble_npl_sem_deinit(struct ble_npl_sem *sem)
{
    return npl_freertos_sem_deinit(sem);
}

static inline ble_npl_error_t
ble_npl_sem_pend(struct ble_npl_sem *sem, ble_npl_time_t timeout)
{
    return npl_freertos_sem_pend(sem, timeout);
}

static inline ble_npl_error_t
ble_npl_sem_release(struct ble_npl_sem *sem)
{
    return npl_freertos_sem_release(sem);
}

static inline uint16_t
ble_npl_sem_get_count(struct ble_npl_sem *sem)
{
    return uxSemaphoreGetCount(sem->handle);
}

static inline void
ble_npl_callout_init(struct ble_npl_callout *co, struct ble_npl_eventq *evq,
                     ble_npl_event_fn *ev_cb, void *ev_arg)
{
    npl_freertos_callout_init(co, evq, ev_cb, ev_arg);
}

static inline void
ble_npl_callout_deinit(struct ble_npl_callout *co)
{
    npl_freertos_callout_deinit(co);
}

static inline ble_npl_error_t
ble_npl_callout_reset(struct ble_npl_callout *co, ble_npl_time_t ticks)
{
    return npl_freertos_callout_reset(co, ticks);
}

static inline void
ble_npl_callout_stop(struct ble_npl_callout *co)
{
    npl_freertos_callout_stop(co);
}

static inline bool
ble_npl_callout_is_active(struct ble_npl_callout *co)
{
    return npl_freertos_callout_is_active(co);
}

static inline ble_npl_time_t
ble_npl_callout_get_ticks(struct ble_npl_callout *co)
{
    return npl_freertos_callout_get_ticks(co);
}

static inline uint32_t
ble_npl_callout_remaining_ticks(struct ble_npl_callout *co,
                                ble_npl_time_t time)
{
    return npl_freertos_callout_remaining_ticks(co, time);
}

static inline void
ble_npl_callout_set_arg(struct ble_npl_callout *co, void *arg)
{
    co->ev.arg = arg;
}

static inline uint32_t
ble_npl_time_get(void)
{
    return xTaskGetTickCountFromISR();
}

static inline ble_npl_error_t
ble_npl_time_ms_to_ticks(uint32_t ms, ble_npl_time_t *out_ticks)
{
    return npl_freertos_time_ms_to_ticks(ms, out_ticks);
}

static inline ble_npl_error_t
ble_npl_time_ticks_to_ms(ble_npl_time_t ticks, uint32_t *out_ms)
{
    return ble_npl_time_ticks_to_ms(ticks, out_ms);
}

static inline ble_npl_time_t
ble_npl_time_ms_to_ticks32(uint32_t ms)
{
    return ms * configTICK_RATE_HZ / 1000;
}

static inline uint32_t
ble_npl_time_ticks_to_ms32(ble_npl_time_t ticks)
{
    return ticks * 1000 / configTICK_RATE_HZ;
}

static inline void
ble_npl_time_delay(ble_npl_time_t ticks)
{
    vTaskDelay(ticks);
}

#if NIMBLE_CFG_CONTROLLER
static inline void
ble_npl_hw_set_isr(int irqn, uint32_t addr)
{
    npl_freertos_hw_set_isr(irqn, addr);
}
#endif

extern portMUX_TYPE ble_port_mutex; 
//临界截面
static inline uint32_t
ble_npl_hw_enter_critical(void)
{
    portENTER_CRITICAL(&ble_port_mutex);
    return 0;
}

static inline void
ble_npl_hw_exit_critical(uint32_t ctx)
{
    portEXIT_CRITICAL(&ble_port_mutex);

}

#ifdef __cplusplus
}
#endif

#endif  /* _NPL_H_ */

