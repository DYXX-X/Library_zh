/*
 * MIT许可证（MIT）
 *
 * 版权所有（c）2019 Ha Thach（tinyusb.org）版权所有（c）2020 Reinhard Panhuber-修改未屏蔽指针
 *
 * 特此免费授予获得本软件和相关文档文件（“软件”）副本的任何人无限制地处理软件的权利，包括但不限于使用、复制、修改、合并、发布、分发、再许可和/或销售软件副本的权利，并允许向其提供软件的人这样做，符合以下条件：
 *
 * 上述版权声明和本许可声明应包含在软件的所有副本或主要部分中。
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * 此文件是TinyUSB堆栈的一部分。
 */

/** \ingroup Group_Common\defgroup Group_fifo fifo
 *  @{ */

#ifndef _TUSB_FIFO_H_
#define _TUSB_FIFO_H_

// 由于使用了无掩码指针，此FIFO不会丢失
// 一个项目切片。此外，写入和读取操作完全
// 因为写和读函数不修改公共状态，所以去耦。从今以后
// 在ISR中写入或读取FIFO是安全的，只要没有其他
// 进程（线程或ISR）干扰。
// 此外，该FIFO已准备好与DMA结合使用，作为写入和
// 可以从DMA ISR内更新读指针。可检测到溢流
// 在一定数量内（请参见tu_fifo_overflow（））。

// 互斥锁仅用于RTOS
// 对于OS无，我们不会被抢占
#define CFG_FIFO_MUTEX      (CFG_TUSB_OS != OPT_OS_NONE)

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

#if CFG_FIFO_MUTEX
#include "osal/osal.h"
#define tu_fifo_mutex_t  osal_mutex_t
#endif

/** \结构tu_fifo_t\brief简单循环fifo
 */
typedef struct
{
  uint8_t* buffer                        ; ///<缓冲指针
  uint16_t depth                         ; ///<最大项目数
  uint16_t item_size                     ; ///<每个项目的大小
  bool overwritable                      ;

  uint16_t non_used_index_space          ; ///<两个缓冲区长度的非幂所需
  uint16_t max_pointer_idx               ; ///<最大绝对指针索引

  volatile uint16_t wr_idx               ; ///<写入指针
  volatile uint16_t rd_idx               ; ///<读取指针

#if CFG_FIFO_MUTEX
  tu_fifo_mutex_t mutex_wr;
  tu_fifo_mutex_t mutex_rd;
#endif

} tu_fifo_t;

#define TU_FIFO_INIT(_buffer, _depth, _type, _overwritable) \
{                                                           \
  .buffer               = _buffer,                          \
  .depth                = _depth,                           \
  .item_size            = sizeof(_type),                    \
  .overwritable         = _overwritable,                    \
  .max_pointer_idx      = 2*(_depth)-1,                     \
  .non_used_index_space = UINT16_MAX - (2*(_depth)-1),      \
}

#define TU_FIFO_DEF(_name, _depth, _type, _overwritable)                      \
    uint8_t _name##_buf[_depth*sizeof(_type)];                                \
    tu_fifo_t _name = TU_FIFO_INIT(_name##_buf, _depth, _type, _overwritable)


bool tu_fifo_set_overwritable(tu_fifo_t *f, bool overwritable);
bool tu_fifo_clear(tu_fifo_t *f);
bool tu_fifo_config(tu_fifo_t *f, void* buffer, uint16_t depth, uint16_t item_size, bool overwritable);

#if CFG_FIFO_MUTEX
static inline void tu_fifo_config_mutex(tu_fifo_t *f, tu_fifo_mutex_t write_mutex_hdl, tu_fifo_mutex_t read_mutex_hdl)
{
  f->mutex_wr = write_mutex_hdl;
  f->mutex_rd = read_mutex_hdl;
}
#endif

bool     tu_fifo_write                  (tu_fifo_t* f, void const * p_data);
uint16_t tu_fifo_write_n                (tu_fifo_t* f, void const * p_data, uint16_t n);
uint16_t tu_fifo_write_n_const_addr_full_words    (tu_fifo_t* f, const void * data, uint16_t n);

bool     tu_fifo_read                   (tu_fifo_t* f, void * p_buffer);
uint16_t tu_fifo_read_n                 (tu_fifo_t* f, void * p_buffer, uint16_t n);
uint16_t tu_fifo_read_n_const_addr_full_words     (tu_fifo_t* f, void * buffer, uint16_t n);

bool     tu_fifo_peek_at                (tu_fifo_t* f, uint16_t pos, void * p_buffer);
uint16_t tu_fifo_peek_at_n              (tu_fifo_t* f, uint16_t pos, void * p_buffer, uint16_t n);

uint16_t tu_fifo_count                  (tu_fifo_t* f);
bool     tu_fifo_empty                  (tu_fifo_t* f);
bool     tu_fifo_full                   (tu_fifo_t* f);
uint16_t tu_fifo_remaining              (tu_fifo_t* f);
bool     tu_fifo_overflowed             (tu_fifo_t* f);
void     tu_fifo_correct_read_pointer   (tu_fifo_t* f);

// 指针修改旨在与DMA结合使用。
// USE WITH CARE - NO SAFTY CHECKS CONDUCTED HERE! NOT MUTEX PROTECTED!
void     tu_fifo_advance_write_pointer  (tu_fifo_t *f, uint16_t n);
void     tu_fifo_advance_read_pointer   (tu_fifo_t *f, uint16_t n);

// 如果您想使用DMA读取/写入FIFO，您可能需要进行两次复制以处理可能的包装部分
// 此函数提供一个指针，用于开始从/向/读/写，以及一个有效的线性长度，沿着该长度不发生换行。
// 如果在一次读/写中没有所有数据可用，请通过以下方式更新读/写指针
// tu_fifo_advance_read_pointer（）/tu_ifo_advance _write_pointer并执行第二次读/写操作
uint16_t tu_fifo_get_linear_read_info   (tu_fifo_t *f, uint16_t offset, void **ptr, uint16_t n);
uint16_t tu_fifo_get_linear_write_info  (tu_fifo_t *f, uint16_t offset, void **ptr, uint16_t n);

static inline bool tu_fifo_peek(tu_fifo_t* f, void * p_buffer)
{
  return tu_fifo_peek_at(f, 0, p_buffer);
}

static inline uint16_t tu_fifo_depth(tu_fifo_t* f)
{
  return f->depth;
}

#ifdef __cplusplus
}
#endif

#endif /* _TUSB_FIFO_H_ */

