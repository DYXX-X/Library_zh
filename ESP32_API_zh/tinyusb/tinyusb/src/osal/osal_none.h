/* 
 * MIT许可证（MIT）
 *
 * 版权所有（c）2019 Ha Thach（tinyusb.org）
 *
 * 特此免费授予获得本软件和相关文档文件（“软件”）副本的任何人无限制地处理软件的权利，包括但不限于使用、复制、修改、合并、发布、分发、再许可和/或销售软件副本的权利，并允许向其提供软件的人这样做，符合以下条件：
 *
 * 上述版权声明和本许可声明应包含在软件的所有副本或主要部分中。
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * 此文件是TinyUSB堆栈的一部分。
 */

#ifndef _TUSB_OSAL_NONE_H_
#define _TUSB_OSAL_NONE_H_

#ifdef __cplusplus
 extern "C" {
#endif

//--------------------------------------------------------------------+
// TASK API
//--------------------------------------------------------------------+


//--------------------------------------------------------------------+
// 二进制信号量API
//--------------------------------------------------------------------+
typedef struct
{
  volatile uint16_t count;
}osal_semaphore_def_t;

typedef osal_semaphore_def_t* osal_semaphore_t;

static inline osal_semaphore_t osal_semaphore_create(osal_semaphore_def_t* semdef)
{
  semdef->count = 0;
  return semdef;
}

static inline bool osal_semaphore_post(osal_semaphore_t sem_hdl, bool in_isr)
{
  (void) in_isr;
  sem_hdl->count++;
  return true;
}

// TODO暂时阻止
static inline bool osal_semaphore_wait (osal_semaphore_t sem_hdl, uint32_t msec)
{
  (void) msec;

  while (sem_hdl->count == 0) { }
  sem_hdl->count--;

  return true;
}

static inline void osal_semaphore_reset(osal_semaphore_t sem_hdl)
{
  sem_hdl->count = 0;
}

//--------------------------------------------------------------------+
// MUTEX API
// 在tinyusb中，互斥体从未在ISR上下文中使用
//--------------------------------------------------------------------+
typedef osal_semaphore_def_t osal_mutex_def_t;
typedef osal_semaphore_t osal_mutex_t;

static inline osal_mutex_t osal_mutex_create(osal_mutex_def_t* mdef)
{
  mdef->count = 1;
  return mdef;
}

static inline bool osal_mutex_lock (osal_mutex_t mutex_hdl, uint32_t msec)
{
  return osal_semaphore_wait(mutex_hdl, msec);
}

static inline bool osal_mutex_unlock(osal_mutex_t mutex_hdl)
{
  return osal_semaphore_post(mutex_hdl, false);
}

//--------------------------------------------------------------------+
// QUEUE API
//--------------------------------------------------------------------+
#include "common/tusb_fifo.h"

// extern以避免包含dcd。h和hcd.h
#if TUSB_OPT_DEVICE_ENABLED
extern void dcd_int_disable(uint8_t rhport);
extern void dcd_int_enable(uint8_t rhport);
#endif

#if TUSB_OPT_HOST_ENABLED
extern void hcd_int_disable(uint8_t rhport);
extern void hcd_int_enable(uint8_t rhport);
#endif

typedef struct
{
    uint8_t role; // 设备或主机
    tu_fifo_t ff;
}osal_queue_def_t;

typedef osal_queue_def_t* osal_queue_t;

// OS NONE仅将角色设备/主机用于互斥锁（禁用usb-isr）
#define OSAL_QUEUE_DEF(_role, _name, _depth, _type)       \
  uint8_t _name##_buf[_depth*sizeof(_type)];              \
  osal_queue_def_t _name = {                              \
    .role = _role,                                        \
    .ff = TU_FIFO_INIT(_name##_buf, _depth, _type, false) \
  }

// 通过禁用USB中断锁定队列
static inline void _osal_q_lock(osal_queue_t qhdl)
{
  (void) qhdl;

#if TUSB_OPT_DEVICE_ENABLED
  if (qhdl->role == OPT_MODE_DEVICE) dcd_int_disable(TUD_OPT_RHPORT);
#endif

#if TUSB_OPT_HOST_ENABLED
  if (qhdl->role == OPT_MODE_HOST) hcd_int_disable(TUH_OPT_RHPORT);
#endif
}

// 解锁队列
static inline void _osal_q_unlock(osal_queue_t qhdl)
{
  (void) qhdl;

#if TUSB_OPT_DEVICE_ENABLED
  if (qhdl->role == OPT_MODE_DEVICE) dcd_int_enable(TUD_OPT_RHPORT);
#endif

#if TUSB_OPT_HOST_ENABLED
  if (qhdl->role == OPT_MODE_HOST) hcd_int_enable(TUH_OPT_RHPORT);
#endif
}

static inline osal_queue_t osal_queue_create(osal_queue_def_t* qdef)
{
  tu_fifo_clear(&qdef->ff);
  return (osal_queue_t) qdef;
}

static inline bool osal_queue_receive(osal_queue_t qhdl, void* data)
{
  _osal_q_lock(qhdl);
  bool success = tu_fifo_read(&qhdl->ff, data);
  _osal_q_unlock(qhdl);

  return success;
}

static inline bool osal_queue_send(osal_queue_t qhdl, void const * data, bool in_isr)
{
  if (!in_isr) {
    _osal_q_lock(qhdl);
  }

  bool success = tu_fifo_write(&qhdl->ff, data);

  if (!in_isr) {
    _osal_q_unlock(qhdl);
  }

  TU_ASSERT(success);

  return success;
}

static inline bool osal_queue_empty(osal_queue_t qhdl)
{
  // 跳过队列锁定/解锁，因为主要调用此函数
  // 在进入低功率模式之前禁用中断
  return tu_fifo_empty(&qhdl->ff);
}

#ifdef __cplusplus
 }
#endif

#endif /* _TUSB_OSAL_NONE_H_ */

