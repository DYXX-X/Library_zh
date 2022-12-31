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

#ifndef _ALARM_H_
#define _ALARM_H_

#include <stdint.h>
#include "esp_timer.h"

typedef struct alarm_t osi_alarm_t;
typedef uint64_t period_ms_t;
typedef esp_timer_cb_t osi_alarm_callback_t;

typedef enum {
    OSI_ALARM_ERR_PASS = 0,
    OSI_ALARM_ERR_FAIL = -1,
    OSI_ALARM_ERR_INVALID_ARG = -2,
    OSI_ALARM_ERR_INVALID_STATE = -3,
} osi_alarm_err_t;

#define ALARM_CBS_NUM   50
#define ALARM_ID_BASE   1000

int osi_alarm_create_mux(void);
int osi_alarm_delete_mux(void);
void osi_alarm_init(void);
void osi_alarm_deinit(void);

// 创建新报警对象。必须通过调用
// |alarm_free |。失败时返回NULL。
osi_alarm_t *osi_alarm_new(const char *alarm_name, osi_alarm_callback_t callback, void *data, period_ms_t timer_expire);

// 释放|alarm_new|创建的报警对象|报警|可能为NULL。如果
// 警报正在等待，它将被取消。调用|alarm_free不安全|
// 从|alarm|的回调内部。
void osi_alarm_free(osi_alarm_t *alarm);

// 将报警设置为在给定的|deadline |之后发出|cb|。注意|deadline|是
// 相对于当前时间的毫秒数|data|是上下文变量
// 对于回调，可以为NULL|cb|将在
// 未指定的线程（即它不会在与调用者相同的线程中被调用）。
// |alarm|和|cb|不能为NULL。
osi_alarm_err_t osi_alarm_set(osi_alarm_t *alarm, period_ms_t timeout);

// 将定期报警设置为在每个给定的|period|中发出|cb|。
osi_alarm_err_t osi_alarm_set_periodic(osi_alarm_t *alarm, period_ms_t period);

// 如果以前设置了|报警|，则此函数将取消它。当此呼叫
// 返回，调用者保证回调没有进行，并且
// 如果尚未调用，则不会调用。此函数是幂等的。
// |报警|不能为NULL。
osi_alarm_err_t osi_alarm_cancel(osi_alarm_t *alarm);

// 计算下一次到期的时间。
// 如果未装备，则返回0|报警|不能为NULL。
// 仅适用于一次热报警，不适用于周期性报警
// TODO:一旦PM计时器可以重新分解，请删除此函数
period_ms_t osi_alarm_get_remaining_ms(const osi_alarm_t *alarm);

// 报警相关状态清除
//void alarm_cleanup（void）；

uint32_t osi_time_get_os_boottime_ms(void);

// 此函数返回给定|报警|是否处于活动状态。
// 如果活动，则返回true，否则返回false。
bool osi_alarm_is_active(osi_alarm_t *alarm);

#endif /*_ALARM_H_*/

