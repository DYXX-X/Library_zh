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

#ifndef _TUSB_OSAL_H_
#define _TUSB_OSAL_H_

#ifdef __cplusplus
 extern "C" {
#endif

/** \添加组group_osal
 *  @{ */

#include "common/tusb_common.h"

// 立即返回
#define OSAL_TIMEOUT_NOTIMEOUT     (0)
// 默认超时
#define OSAL_TIMEOUT_NORMAL        (10)
// 永远等待
#define OSAL_TIMEOUT_WAIT_FOREVER  (UINT32_MAX)

#define OSAL_TIMEOUT_CONTROL_XFER  OSAL_TIMEOUT_WAIT_FOREVER

typedef void (*osal_task_func_t)( void * );

#if CFG_TUSB_OS == OPT_OS_NONE
  #include "osal_none.h"
#elif CFG_TUSB_OS == OPT_OS_FREERTOS
  #include "osal_freertos.h"
#elif CFG_TUSB_OS == OPT_OS_MYNEWT
  #include "osal_mynewt.h"
#elif CFG_TUSB_OS == OPT_OS_PICO
  #include "osal_pico.h"
#elif CFG_TUSB_OS == OPT_OS_RTTHREAD
  #include "osal_rtthread.h"
#elif CFG_TUSB_OS == OPT_OS_CUSTOM
  #include "tusb_os_custom.h" // 由应用程序实现
#else
  #error OS is not supported yet
#endif

//--------------------------------------------------------------------+
// OSAL移植API
//--------------------------------------------------------------------+

//-------------信号量-------------//
static inline osal_semaphore_t osal_semaphore_create(osal_semaphore_def_t* semdef);
static inline bool osal_semaphore_post(osal_semaphore_t sem_hdl, bool in_isr);
static inline bool osal_semaphore_wait(osal_semaphore_t sem_hdl, uint32_t msec);

static inline void osal_semaphore_reset(osal_semaphore_t sem_hdl); // TODO已删除

//-------------Mutex公司-------------//
static inline osal_mutex_t osal_mutex_create(osal_mutex_def_t* mdef);
static inline bool osal_mutex_lock (osal_mutex_t sem_hdl, uint32_t msec);
static inline bool osal_mutex_unlock(osal_mutex_t mutex_hdl);

//-------------队列-------------//
static inline osal_queue_t osal_queue_create(osal_queue_def_t* qdef);
static inline bool osal_queue_receive(osal_queue_t qhdl, void* data);
static inline bool osal_queue_send(osal_queue_t qhdl, void const * data, bool in_isr);
static inline bool osal_queue_empty(osal_queue_t qhdl);

#if 0  // TODO稍后删除与子任务相关的宏
// 子任务
#define OSAL_SUBTASK_BEGIN
#define OSAL_SUBTASK_END                    return TUSB_ERROR_NONE;

#define STASK_RETURN(_error)                return _error;
#define STASK_INVOKE(_subtask, _status)     (_status) = _subtask
#define STASK_ASSERT(_cond)                 TU_VERIFY(_cond, TUSB_ERROR_OSAL_TASK_FAILED)
#endif

#ifdef __cplusplus
 }
#endif

/** @} */

#endif /* _TUSB_OSAL_H_ */

