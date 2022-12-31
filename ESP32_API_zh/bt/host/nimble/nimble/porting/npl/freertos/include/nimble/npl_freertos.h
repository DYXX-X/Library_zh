/*
 * 根据一个或多个贡献者许可协议向Apache Software Foundation（ASF）许可。有关版权所有权的更多信息，请参阅随本作品分发的通知文件。ASF根据Apache许可证2.0版（“许可证”）向您许可此文件；除非符合许可证，否则不得使用此文件。您可以在以下地址获取许可证副本：
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 * 除非适用法律要求或书面同意，否则根据许可证分发的软件是按“原样”分发的，无任何明示或暗示的担保或条件。有关许可证下权限和限制的具体语言，请参阅许可证。
 */

#ifndef _NPL_FREERTOS_H_
#define _NPL_FREERTOS_H_

#ifdef __cplusplus
extern "C" {
#endif

struct ble_npl_eventq *npl_freertos_eventq_dflt_get(void);

struct ble_npl_event *npl_freertos_eventq_get(struct ble_npl_eventq *evq,
                                              ble_npl_time_t tmo);

void npl_freertos_eventq_put(struct ble_npl_eventq *evq,
                             struct ble_npl_event *ev);

void npl_freertos_eventq_remove(struct ble_npl_eventq *evq,
                                struct ble_npl_event *ev);

ble_npl_error_t npl_freertos_mutex_init(struct ble_npl_mutex *mu);
ble_npl_error_t npl_freertos_mutex_deinit(struct ble_npl_mutex *mu);

ble_npl_error_t npl_freertos_mutex_pend(struct ble_npl_mutex *mu,
                                        ble_npl_time_t timeout);

ble_npl_error_t npl_freertos_mutex_release(struct ble_npl_mutex *mu);

ble_npl_error_t npl_freertos_sem_init(struct ble_npl_sem *sem, uint16_t tokens);
ble_npl_error_t npl_freertos_sem_deinit(struct ble_npl_sem *sem);

ble_npl_error_t npl_freertos_sem_pend(struct ble_npl_sem *sem,
                                      ble_npl_time_t timeout);

ble_npl_error_t npl_freertos_sem_release(struct ble_npl_sem *sem);

void npl_freertos_callout_init(struct ble_npl_callout *co,
                               struct ble_npl_eventq *evq,
                               ble_npl_event_fn *ev_cb, void *ev_arg);

void npl_freertos_callout_deinit(struct ble_npl_callout *co);

void npl_freertos_callout_stop(struct ble_npl_callout *co);

bool npl_freertos_callout_is_active(struct ble_npl_callout *co);

ble_npl_time_t npl_freertos_callout_get_ticks(struct ble_npl_callout *co);

ble_npl_error_t npl_freertos_callout_reset(struct ble_npl_callout *co,
                                           ble_npl_time_t ticks);

ble_npl_time_t npl_freertos_callout_remaining_ticks(struct ble_npl_callout *co,
						    ble_npl_time_t now);

ble_npl_error_t npl_freertos_time_ms_to_ticks(uint32_t ms,
                                              ble_npl_time_t *out_ticks);

ble_npl_error_t npl_freertos_time_ticks_to_ms(ble_npl_time_t ticks,
                                              uint32_t *out_ms);

void npl_freertos_hw_set_isr(int irqn, uint32_t addr);

uint32_t npl_freertos_hw_enter_critical(void);

void npl_freertos_hw_exit_critical(uint32_t ctx);

#ifdef __cplusplus
}
#endif

#endif  /* _NPL_FREERTOS_H_ */

