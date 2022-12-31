/*
 * 根据一个或多个贡献者许可协议向Apache Software Foundation（ASF）许可。有关版权所有权的更多信息，请参阅随本作品分发的通知文件。ASF根据Apache许可证2.0版（“许可证”）向您许可此文件；除非符合许可证，否则不得使用此文件。您可以在以下地址获取许可证副本：
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 * 除非适用法律要求或书面同意，否则根据许可证分发的软件是按“原样”分发的，无任何明示或暗示的担保或条件。有关许可证下权限和限制的具体语言，请参阅许可证。
 */

 /**
  * @addtogroup OS内核@{
  *   @defgroup OSCPUTime高分辨率定时器@{
  */

#ifndef H_OS_CPUTIME_
#define H_OS_CPUTIME_

#ifdef __cplusplus
extern "C" {
#endif

#include "syscfg/syscfg.h"
#include "hal/hal_timer.h"
#include "os/os.h"

/*
 * 注：这些定义允许覆盖所使用的cputime频率。存在这些定义的原因是，当CPUTIME计数为1MHz时，使代码更有效/更小。
 *
 * 对于那些需要不同cputime频率的用户，可以将OS_cputime_FREQ的配置定义设置为项目、目标或bsp中所需的频率。
 */
#if (MYNEWT_VAL(OS_CPUTIME_FREQ) == 1000000)

#define OS_CPUTIME_FREQ_1MHZ

#elif MYNEWT_VAL(OS_CPUTIME_FREQ) == 256        ||  \
      MYNEWT_VAL(OS_CPUTIME_FREQ) == 512        ||  \
      MYNEWT_VAL(OS_CPUTIME_FREQ) == 1024       ||  \
      MYNEWT_VAL(OS_CPUTIME_FREQ) == 2048       ||  \
      MYNEWT_VAL(OS_CPUTIME_FREQ) == 4096       ||  \
      MYNEWT_VAL(OS_CPUTIME_FREQ) == 8192       ||  \
      MYNEWT_VAL(OS_CPUTIME_FREQ) == 16384      ||  \
      MYNEWT_VAL(OS_CPUTIME_FREQ) == 32768      ||  \
      MYNEWT_VAL(OS_CPUTIME_FREQ) == 65536      ||  \
      MYNEWT_VAL(OS_CPUTIME_FREQ) == 131072     ||  \
      MYNEWT_VAL(OS_CPUTIME_FREQ) == 262144     ||  \
      MYNEWT_VAL(OS_CPUTIME_FREQ) == 524288

#define OS_CPUTIME_FREQ_PWR2

#elif MYNEWT_VAL(OS_CPUTIME_FREQ) > 1000000

#define OS_CPUTIME_FREQ_HIGH

#else

#error "Invalid OS_CPUTIME_FREQ value.  Value must be one of a) a power of 2" \
       ">= 256Hz, or b) any value >= 1MHz"

#endif

#if defined(OS_CPUTIME_FREQ_HIGH)
/* CPUTIME数据。*/
struct os_cputime_data
{
    uint32_t ticks_per_usec;    /* 每次使用的刻度数*/
};
extern struct os_cputime_data g_os_cputime;
#endif

/* 比较cputiles的有用宏*/
/**如果t1在时间上早于t2，则求值为true*/
#define CPUTIME_LT(__t1, __t2) ((int32_t)   ((__t1) - (__t2)) < 0)
/**如果t1在时间t2之后，则求值为true*/
#define CPUTIME_GT(__t1, __t2) ((int32_t)   ((__t1) - (__t2)) > 0)
/**如果t1在时间t2之后，则求值为true*/
#define CPUTIME_GEQ(__t1, __t2) ((int32_t)  ((__t1) - (__t2)) >= 0)
/**如果t1在时间t2上或之后，则求值为true*/
#define CPUTIME_LEQ(__t1, __t2) ((int32_t)  ((__t1) - (__t2)) <= 0)

/**
 * 初始化cputime模块。这必须在调用os_init之后和使用任何其他计时器API之前调用。这应该只调用一次，并且应该在使用硬件计时器之前调用。
 *
 * @param clock_freq 所需的cputime频率，单位为赫兹（Hz）。
 *
 * @return 成功时为int 0-1出现错误。
 */
int os_cputime_init(uint32_t clock_freq);

/**
 * 返回cputime的低32位。
 *
 * @return uint32_t cputime的低32位
 */
uint32_t os_cputime_get32(void);

#if !defined(OS_CPUTIME_FREQ_PWR2)
/**
 * 将给定的纳秒数转换为cputime记号。如果定义了OS_CPUTIME_FREQ_PWR2，则未定义。
 *
 * @param usecs 转换为刻度的纳秒数
 *
 * @return uint32_t与“nsecs”对应的刻度数
 */
uint32_t os_cputime_nsecs_to_ticks(uint32_t nsecs);

/**
 * 将给定的刻度数转换为纳秒。如果定义了OS_CPUTIME_FREQ_PWR2，则未定义。
 *
 * @param ticks 要转换为纳秒的刻度数。
 *
 * @return uint32_t与“滴答声”对应的纳秒数
 */
uint32_t os_cputime_ticks_to_nsecs(uint32_t ticks);

/**
 * 等待“nsecs”纳秒过去。这是一个阻塞延迟。如果定义了OS_CPUTIME_FREQ_PWR2，则未定义。
 *
 *
 * @param nsecs 等待的纳秒数。
 */
void os_cputime_delay_nsecs(uint32_t nsecs);
#endif

#if defined(OS_CPUTIME_FREQ_1MHZ)
#define os_cputime_usecs_to_ticks(x)    (x)
#define os_cputime_ticks_to_usecs(x)    (x)
#else

/**
 * 将给定的微秒数转换为cputime记号。
 *
 * @param usecs 转换为刻度的微秒数
 *
 * @return uint32_t与“usecs”对应的刻度数
 */
uint32_t os_cputime_usecs_to_ticks(uint32_t usecs);

/**
 * 将给定的刻度数转换为微秒。
 *
 * @param ticks 要转换为微秒的刻度数。
 *
 * @return uint32_t与“滴答声”对应的微秒数
 */
uint32_t os_cputime_ticks_to_usecs(uint32_t ticks);
#endif

/**
 * 等待直到滴答数结束。这是一个阻塞延迟。
 *
 * @param ticks 等待的滴答数。
 */
void os_cputime_delay_ticks(uint32_t ticks);

/**
 * 等待“usecs”微秒过去。这是一个阻塞延迟。
 *
 * @param usecs 等待的使用次数。
 */
void os_cputime_delay_usecs(uint32_t usecs);

/**
 * 使用给定的HAL计时器初始化CPU计时器。
 *
 * @param timer 要初始化的计时器。不能为NULL。
 * @param fp    计时器回调函数。不能为NULL。
 * @param arg   指向要传递给计时器的数据对象的指针。
 */
void os_cputime_timer_init(struct hal_timer *timer, hal_timer_cb fp,
        void *arg);

/**
 * 启动将在“cputime”过期的cputimer。如果cputime已经通过，则仍将调用计时器回调（在中断上下文中）。
 *
 * 注意：计时器停止时必须调用此命令。
 *
 * @param timer     指向要启动的计时器的指针。不能为NULL。
 * @param cputime   计时器到期的时间。
 *
 * @return 成功时为int 0；如果计时器已启动或计时器结构无效，则返回EINVAL
 *
 */
int os_cputime_timer_start(struct hal_timer *timer, uint32_t cputime);

/**
 * 设置一个cpu计时器，该计时器将从当前cputime的“usecs”微秒过期。
 *
 * 注意：计时器停止时必须调用此命令。
 *
 * @param timer 指向计时器的指针。不能为NULL。
 * @param usecs 从现在起计时器将到期的使用次数。
 *
 * @return 成功时为int 0；如果计时器已启动或计时器结构无效，则返回EINVAL
 */
int os_cputime_timer_relative(struct hal_timer *timer, uint32_t usecs);

/**
 * 停止cputimer运行。计时器将从计时器队列中删除，如果队列中没有计时器，中断将被禁用。即使计时器未运行，也可以调用。
 *
 * @param timer 指向要停止的cputimer的指针。不能为NULL。
 */
void os_cputime_timer_stop(struct hal_timer *timer);

#ifdef __cplusplus
}
#endif

#endif /* H_OS_CPUTIME_ */

/**
 *   @} OSCPU时间
 * @} 操作系统核心
 */

