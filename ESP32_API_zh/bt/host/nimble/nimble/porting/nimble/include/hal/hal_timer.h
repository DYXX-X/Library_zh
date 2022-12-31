/*
 * 根据一个或多个贡献者许可协议向Apache Software Foundation（ASF）许可。有关版权所有权的更多信息，请参阅随本作品分发的通知文件。ASF根据Apache许可证2.0版（“许可证”）向您许可此文件；除非符合许可证，否则不得使用此文件。您可以在以下地址获取许可证副本：
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 * 除非适用法律要求或书面同意，否则根据许可证分发的软件是按“原样”分发的，无任何明示或暗示的担保或条件。有关许可证下权限和限制的具体语言，请参阅许可证。
 */


/**
 * @addtogroup HAL @{
 *   @defgroup HALTimer HAL计时器@{
 */

#ifndef H_HAL_TIMER_
#define H_HAL_TIMER_

#include <inttypes.h>
#include "os/queue.h"

#ifdef __cplusplus
extern "C" {
#endif

/* HAL计时器回调*/
typedef void (*hal_timer_cb)(void *arg);

/**
 * HAL计时器结构。用户可以根据需要声明任意数量的这些结构。当用户调用：c:func:`hal_timer_start（）`或：c:func:`hal_timer_start_at（）`API时，它们将在特定HW计时器队列中排队。用户必须在启动计时器之前调用了：c:\func:`hal_timer_set_cb（）`。
 *
 * 注：用户不必修改/检查此结构的内容；应使用hal计时器API。
 */
struct hal_timer {
    /**内部平台特定指针*/
    void                *bsp_timer;
    /**回调函数*/
    hal_timer_cb        cb_func;
    /**回调参数*/
    void                *cb_arg;
    /**勾选计时器到期的时间*/
    uint32_t            expiry;
    TAILQ_ENTRY(hal_timer) link;    /* 队列链接列表结构*/
};

/**
 * 初始化硬件计时器。
 *
 * @param timer_num 要初始化的HW计时器的编号
 * @param cfg       硬件特定计时器配置。这将直接从BSP传递到MCU特定的驱动程序。
 */
int hal_timer_init(int timer_num, void *cfg);

/**
 * 取消初始化硬件计时器。
 *
 * @param timer_num 要取消初始化的HW计时器的编号
 */
int hal_timer_deinit(int timer_num);

/**
 * 在给定频率下配置硬件计时器并启动它。如果无法获得准确的频率，则设置最接近的可获得频率。
 *
 * @param timer_num 要配置的HW计时器的编号
 * @param freq_hz   配置计时器的频率（Hz）
 *
 * @return 成功时为0，失败时为非零错误代码
 */
int hal_timer_config(int timer_num, uint32_t freq_hz);

/**
 * 返回硬件计时器的分辨率。注意：可能无法获得频率，因此呼叫者可以使用该频率来确定分辨率。以纳秒为单位返回分辨率。返回值0表示使用的计时器无效。
 *
 * @param timer_num 要获取分辨率的硬件计时器的数量
 *
 * @return 计时器的分辨率
 */
uint32_t hal_timer_get_resolution(int timer_num);

/**
 * 返回HW计时器当前刻度值
 *
 * @param timer_num 读取刻度值的HW计时器
 *
 * @return 当前刻度值
 */
uint32_t hal_timer_read(int timer_num);

/**
 * 对多个刻度执行阻塞延迟。
 *
 * @param timer_num 用于阻塞延迟的计时器编号
 * @param ticks 要延迟的刻度数
 *
 * @return 成功时为0，失败时为非零错误代码
 */
int hal_timer_delay(int timer_num, uint32_t ticks);

/**
 * 使用前设置计时器结构。如果计时器正在运行，则不应调用。必须在使用计时器之前至少调用一次。
 *
 * @param timer_num 用于配置回调的HW计时器的编号
 * @param tmr       用于此计时器的计时器结构
 * @param cb_func   计时器触发时要调用的计时器回调
 * @param arg       提供计时器回调的不透明参数
 *
 * @return 成功时为0，失败时为非零错误代码。
 */
int hal_timer_set_cb(int timer_num, struct hal_timer *tmr, hal_timer_cb cb_func,
                     void *arg);

/**
 * 启动一个将在“滴答”滴答声中过期的计时器。刻度不能为0
 *
 * @param tmr   要启动的计时器
 * @param ticks 计时器到期的刻度数
 *
 * @return 成功时为0，失败时为非零错误代码。
 */
int hal_timer_start(struct hal_timer *tmr, uint32_t ticks);

/**
 * 启动一个计时器，当计时器达到“刻度”时，该计时器将过期。如果滴答声已经过去，则将“立即”调用计时器回调（在中断上下文中）。
 *
 * @param tmr  要启动的计时器
 * @param tick 触发计时器的绝对刻度值
 *
 * @return 成功时为0，失败时为非零错误代码。
 */
int hal_timer_start_at(struct hal_timer *tmr, uint32_t tick);

/**
 * 停止当前正在运行的计时器；不会调用关联的回调
 *
 * @param tmr 要停止的计时器
 */
int hal_timer_stop(struct hal_timer *tmr);

#ifdef __cplusplus
}
#endif

#endif /* H_HAL_TIMER_ */

/**
 *   @} HAL计时器
 * @} HAL
 */

