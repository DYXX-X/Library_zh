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

/** \inggroup Group_Common Common Files\defgroup Group_TimeoutTimer超时计时器
 *  @{ */

#ifndef _TUSB_TIMEOUT_H_
#define _TUSB_TIMEOUT_H_

#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
  uint32_t start;
  uint32_t interval;
}tu_timeout_t;

#if 0

extern uint32_t tusb_hal_millis(void);

static inline void tu_timeout_set(tu_timeout_t* tt, uint32_t msec)
{
  tt->interval = msec;
  tt->start    = tusb_hal_millis();
}

static inline bool tu_timeout_expired(tu_timeout_t* tt)
{
  return ( tusb_hal_millis() - tt->start ) >= tt->interval;
}

// 用于与周期性事件一起使用，以防止漂移
static inline void tu_timeout_reset(tu_timeout_t* tt)
{
  tt->start += tt->interval;
}

static inline void tu_timeout_restart(tu_timeout_t* tt)
{
  tt->start = tusb_hal_millis();
}

#endif

#ifdef __cplusplus
 }
#endif

#endif /* _TUSB_TIMEOUT_H_ */

/** @} */

