/*
 * MIT许可证（MIT）
 *
 * 版权所有（c）2020 tfx2001(2479727366@qq.com)
 *
 * 特此免费授予获得本软件和相关文档文件（“软件”）副本的任何人无限制地处理软件的权利，包括但不限于使用、复制、修改、合并、发布、分发、再许可和/或销售软件副本的权利，并允许向其提供软件的人这样做，符合以下条件：
 *
 * 上述版权声明和本许可声明应包含在软件的所有副本或主要部分中。
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * 此文件是TinyUSB堆栈的一部分。
 */

#ifndef _TUSB_OSAL_RTTHREAD_H_
#define _TUSB_OSAL_RTTHREAD_H_

// RT线程头
#include "rtthread.h"

#ifdef __cplusplus
extern "C" {
#endif

//--------------------------------------------------------------------+
// TASK API
//--------------------------------------------------------------------+
static inline void osal_task_delay(uint32_t msec) {
  rt_thread_mdelay(msec);
}

//--------------------------------------------------------------------+
// 信号量API
//--------------------------------------------------------------------+
typedef struct rt_semaphore osal_semaphore_def_t;
typedef rt_sem_t osal_semaphore_t;

static inline osal_semaphore_t
osal_semaphore_create(osal_semaphore_def_t *semdef) {
    rt_sem_init(semdef, "tusb", 0, RT_IPC_FLAG_FIFO);
    return semdef;
}

static inline bool osal_semaphore_post(osal_semaphore_t sem_hdl, bool in_isr) {
    (void) in_isr;
    return rt_sem_release(sem_hdl) == RT_EOK;
}

static inline bool osal_semaphore_wait(osal_semaphore_t sem_hdl, uint32_t msec) {
    return rt_sem_take(sem_hdl, rt_tick_from_millisecond(msec)) == RT_EOK;
}

static inline void osal_semaphore_reset(osal_semaphore_t const sem_hdl) {
    // TODO:实现
}

//--------------------------------------------------------------------+
// MUTEX API（优先级继承）
//--------------------------------------------------------------------+
typedef struct rt_mutex osal_mutex_def_t;
typedef rt_mutex_t osal_mutex_t;

static inline osal_mutex_t osal_mutex_create(osal_mutex_def_t *mdef) {
    rt_mutex_init(mdef, "tusb", RT_IPC_FLAG_FIFO);
    return mdef;
}

static inline bool osal_mutex_lock(osal_mutex_t mutex_hdl, uint32_t msec) {
    return rt_mutex_take(mutex_hdl, rt_tick_from_millisecond(msec)) == RT_EOK;
}

static inline bool osal_mutex_unlock(osal_mutex_t mutex_hdl) {
    return rt_mutex_release(mutex_hdl) == RT_EOK;
}

//--------------------------------------------------------------------+
// QUEUE API
//--------------------------------------------------------------------+

// OS NONE仅将角色设备/主机用于互斥锁（禁用usb-isr）
#define OSAL_QUEUE_DEF(_role, _name, _depth, _type) \
    static _type _name##_##buf[_depth]; \
    osal_queue_def_t _name = { .depth = _depth, .item_sz = sizeof(_type), .buf = _name##_##buf };

typedef struct {
    uint16_t depth;
    uint16_t item_sz;
    void *buf;

    struct rt_messagequeue sq;
} osal_queue_def_t;

typedef rt_mq_t osal_queue_t;

static inline osal_queue_t osal_queue_create(osal_queue_def_t *qdef) {
    rt_mq_init(&(qdef->sq), "tusb", qdef->buf, qdef->item_sz,
               qdef->item_sz * qdef->depth, RT_IPC_FLAG_FIFO);
    return &(qdef->sq);
}

static inline bool osal_queue_receive(osal_queue_t qhdl, void *data) {
    return rt_mq_recv(qhdl, data, qhdl->msg_size, RT_WAITING_FOREVER) == RT_EOK;
}

static inline bool osal_queue_send(osal_queue_t qhdl, void const *data, bool in_isr) {
    (void) in_isr;
    return rt_mq_send(qhdl, (void *)data, qhdl->msg_size) == RT_EOK;
}

static inline bool osal_queue_empty(osal_queue_t qhdl) {
    return (qhdl->entry) == 0;
}

#ifdef __cplusplus
}
#endif

#endif /* _TUSB_OSAL_RTTHREAD_H_ */

