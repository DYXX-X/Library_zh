/*
 * 根据一个或多个贡献者许可协议向Apache Software Foundation（ASF）许可。有关版权所有权的更多信息，请参阅随本作品分发的通知文件。ASF根据Apache许可证2.0版（“许可证”）向您许可此文件；除非符合许可证，否则不得使用此文件。您可以在以下地址获取许可证副本：
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 * 除非适用法律要求或书面同意，否则根据许可证分发的软件是按“原样”分发的，无任何明示或暗示的担保或条件。有关许可证下权限和限制的具体语言，请参阅许可证。
 */

#ifndef _NIMBLE_NPL_H_
#define _NIMBLE_NPL_H_

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

struct ble_npl_event;
typedef void ble_npl_event_fn(struct ble_npl_event *ev);

enum ble_npl_error {
    BLE_NPL_OK = 0,
    BLE_NPL_ENOMEM = 1,
    BLE_NPL_EINVAL = 2,
    BLE_NPL_INVALID_PARAM = 3,
    BLE_NPL_MEM_NOT_ALIGNED = 4,
    BLE_NPL_BAD_MUTEX = 5,
    BLE_NPL_TIMEOUT = 6,
    BLE_NPL_ERR_IN_ISR = 7,
    BLE_NPL_ERR_PRIV = 8,
    BLE_NPL_OS_NOT_STARTED = 9,
    BLE_NPL_ENOENT = 10,
    BLE_NPL_EBUSY = 11,
    BLE_NPL_ERROR = 12,
};

typedef enum ble_npl_error ble_npl_error_t;

/* 包括特定于操作系统的定义*/
#include "nimble/nimble_npl_os.h"

/*
 * 通用的
 */

bool ble_npl_os_started(void);

void *ble_npl_get_current_task_id(void);

/*
 * 事件队列
 */

void ble_npl_eventq_init(struct ble_npl_eventq *evq);

void ble_npl_eventq_deinit(struct ble_npl_eventq *evq);

struct ble_npl_event *ble_npl_eventq_get(struct ble_npl_eventq *evq,
                                         ble_npl_time_t tmo);

void ble_npl_eventq_put(struct ble_npl_eventq *evq, struct ble_npl_event *ev);

void ble_npl_eventq_remove(struct ble_npl_eventq *evq,
                           struct ble_npl_event *ev);

void ble_npl_event_init(struct ble_npl_event *ev, ble_npl_event_fn *fn,
                        void *arg);

bool ble_npl_event_is_queued(struct ble_npl_event *ev);

void *ble_npl_event_get_arg(struct ble_npl_event *ev);

void ble_npl_event_set_arg(struct ble_npl_event *ev, void *arg);

bool ble_npl_eventq_is_empty(struct ble_npl_eventq *evq);

void ble_npl_event_run(struct ble_npl_event *ev);

/*
 * 互斥量
 */

ble_npl_error_t ble_npl_mutex_init(struct ble_npl_mutex *mu);

ble_npl_error_t ble_npl_mutex_pend(struct ble_npl_mutex *mu,
                                   ble_npl_time_t timeout);

ble_npl_error_t ble_npl_mutex_release(struct ble_npl_mutex *mu);

ble_npl_error_t ble_npl_mutex_deinit(struct ble_npl_mutex *mu);

/*
 * 信号灯
 */

ble_npl_error_t ble_npl_sem_init(struct ble_npl_sem *sem, uint16_t tokens);

ble_npl_error_t ble_npl_sem_pend(struct ble_npl_sem *sem,
                                 ble_npl_time_t timeout);

ble_npl_error_t ble_npl_sem_release(struct ble_npl_sem *sem);

ble_npl_error_t ble_npl_sem_deinit(struct ble_npl_sem *sem);

uint16_t ble_npl_sem_get_count(struct ble_npl_sem *sem);

/*
 * 详图索引
 */

void ble_npl_callout_init(struct ble_npl_callout *co, struct ble_npl_eventq *evq,
                          ble_npl_event_fn *ev_cb, void *ev_arg);

ble_npl_error_t ble_npl_callout_reset(struct ble_npl_callout *co,
                                      ble_npl_time_t ticks);

void ble_npl_callout_stop(struct ble_npl_callout *co);

bool ble_npl_callout_is_active(struct ble_npl_callout *co);

ble_npl_time_t ble_npl_callout_get_ticks(struct ble_npl_callout *co);

ble_npl_time_t ble_npl_callout_remaining_ticks(struct ble_npl_callout *co,
                                               ble_npl_time_t time);

void ble_npl_callout_set_arg(struct ble_npl_callout *co,
                             void *arg);
/*
 * 时间函数
 */

ble_npl_time_t ble_npl_time_get(void);

ble_npl_error_t ble_npl_time_ms_to_ticks(uint32_t ms, ble_npl_time_t *out_ticks);

ble_npl_error_t ble_npl_time_ticks_to_ms(ble_npl_time_t ticks, uint32_t *out_ms);

ble_npl_time_t ble_npl_time_ms_to_ticks32(uint32_t ms);

uint32_t ble_npl_time_ticks_to_ms32(ble_npl_time_t ticks);

void ble_npl_time_delay(ble_npl_time_t ticks);

/*
 * 特定于硬件
 *
 * 这些符号最有可能由应用程序定义，因为它们特定于硬件，而不是操作系统。
 */

#if NIMBLE_CFG_CONTROLLER

void ble_npl_hw_set_isr(int irqn, uint32_t addr);

#endif

uint32_t ble_npl_hw_enter_critical(void);

void ble_npl_hw_exit_critical(uint32_t ctx);

bool ble_npl_hw_is_in_critical(void);

#ifdef __cplusplus
}
#endif

#endif  /* _NIMBLE_NPL_H_ */

