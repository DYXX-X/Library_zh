/*
 * 版权所有（c）2017-2018，Nordic Semiconductor ASA保留所有权利。
 *
 * 在满足以下条件的情况下，允许以源代码和二进制形式重新分发和使用，无论是否进行修改：
 *
 * 1.源代码的重新分发必须保留上述版权声明、本条件列表和以下免责声明。
 *
 * 2.二进制形式的再发行必须在随发行提供的文档和/或其他材料中复制上述版权声明、本条件列表和以下免责声明。
 *
 * 3.未经事先书面许可，不得使用版权持有人的姓名或其贡献者的姓名为本软件衍生的产品背书或推广。
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef NRFX_GLUE_H__
#define NRFX_GLUE_H__

// THIS IS A TEMPLATE FILE.
// 应将其复制到主机环境中的适当位置
// 其中nrfx是集成的，并且应提供以下宏
// 适当的实现。
// 应该从自定义文件中删除此注释。

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @defgroup nrfx_值nrfx_。小时@{
 * @ingroup 国家外汇基金
 *
 * @brief 此文件包含宏，这些宏应根据集成了@em nrfx的主机环境的需要来实现。
 */

// 取消注释此行以使用标准MDK方式绑定IRQ处理程序
// 在链接时间。
#include <soc/nrfx_irqs.h>

//------------------------------------------------------------------------------

/**
 * @brief 用于放置运行时断言的宏。
 *
 * @param expression  要计算的表达式。
 */
#define NRFX_ASSERT(expression)

/**
 * @brief 用于放置编译时断言的宏。
 *
 * @param expression  要计算的表达式。
 */
#define NRFX_STATIC_ASSERT(expression)

//------------------------------------------------------------------------------

/**
 * @brief 用于设置特定IRQ优先级的宏。
 *
 * @param irq_number  IRQ编号。
 * @param priority    要设置的优先级。
 */
#define NRFX_IRQ_PRIORITY_SET(irq_number, priority) _NRFX_IRQ_PRIORITY_SET(irq_number, priority)
static inline void _NRFX_IRQ_PRIORITY_SET(IRQn_Type irq_number,
                                          uint8_t   priority)
{
    NRFX_ASSERT(INTERRUPT_PRIORITY_IS_VALID(priority));
    NVIC_SetPriority(irq_number, priority);
}

/**
 * @brief 用于启用特定IRQ的宏。
 *
 * @param irq_number  IRQ编号。
 */
#define NRFX_IRQ_ENABLE(irq_number)  _NRFX_IRQ_ENABLE(irq_number)
static inline void _NRFX_IRQ_ENABLE(IRQn_Type irq_number)
{
    NVIC_ClearPendingIRQ(irq_number);
    NVIC_EnableIRQ(irq_number);
}

/**
 * @brief 用于检查是否启用特定IRQ的宏。
 *
 * @param irq_number  IRQ编号。
 *
 * @retval 如果启用IRQ，则为true。
 * @retval 否则为false。
 */
#define NRFX_IRQ_IS_ENABLED(irq_number)  _NRFX_IRQ_IS_ENABLED(irq_number)
static inline bool _NRFX_IRQ_IS_ENABLED(IRQn_Type irq_number)
{
    return 0 != (NVIC->ISER[irq_number / 32] & (1UL << (irq_number % 32)));
}

/**
 * @brief 用于禁用特定IRQ的宏。
 *
 * @param irq_number  IRQ编号。
 */
#define NRFX_IRQ_DISABLE(irq_number)  _NRFX_IRQ_DISABLE(irq_number)
static inline void _NRFX_IRQ_DISABLE(IRQn_Type irq_number)
{
    NVIC_DisableIRQ(irq_number);
}

/**
 * @brief 用于将特定IRQ设置为挂起的宏。
 *
 * @param irq_number  IRQ编号。
 */
#define NRFX_IRQ_PENDING_SET(irq_number) _NRFX_IRQ_PENDING_SET(irq_number)
static inline void _NRFX_IRQ_PENDING_SET(IRQn_Type irq_number)
{
    NVIC_SetPendingIRQ(irq_number);
}

/**
 * @brief 用于清除特定IRQ的挂起状态的宏。
 *
 * @param irq_number  IRQ编号。
 */
#define NRFX_IRQ_PENDING_CLEAR(irq_number) _NRFX_IRQ_PENDING_CLEAR(irq_number)
static inline void _NRFX_IRQ_PENDING_CLEAR(IRQn_Type irq_number)
{
    NVIC_ClearPendingIRQ(irq_number);
}

/**
 * @brief 用于检查特定IRQ的挂起状态的宏。
 *
 * @retval 如果IRQ待定，则为true。
 * @retval 否则为false。
 */
#define NRFX_IRQ_IS_PENDING(irq_number) _NRFX_IRQ_IS_PENDING(irq_number)
static inline bool _NRFX_IRQ_IS_PENDING(IRQn_Type irq_number)
{
    return (NVIC_GetPendingIRQ(irq_number) == 1);
}

/**
 * @brief 用于进入关键部分的宏。
 */
#define NRFX_CRITICAL_SECTION_ENTER()

/**
 * @brief 用于退出关键部分的宏。
 */
#define NRFX_CRITICAL_SECTION_EXIT()

//------------------------------------------------------------------------------

/**
 * @brief 当设置为非零值时，此宏指定
 *        @ref nrfx_coredep_delay_us使用基于DWT的精确解决方案。如果使用的SoC中不存在DWT单元，则会生成编译错误。
 */
#define NRFX_DELAY_DWT_BASED    0

/**
 * @brief 用于将代码执行延迟至少指定时间的宏。
 *
 * @param us_time 等待的微秒数。
 */
#include <soc/nrfx_coredep.h>
#define NRFX_DELAY_US(us_time) nrfx_coredep_delay_us(us_time)

//------------------------------------------------------------------------------

/**
 * @brief 当设置为非零值时，此宏指定
 *        @ref nrfx_error_codes和@ref nrfx_err_t类型本身是以自定义方式定义的，默认定义来自@c<nrfx_err。h> 不应使用。
 */
#define NRFX_CUSTOM_ERROR_CODES 0

//------------------------------------------------------------------------------

/**
 * @brief 比特掩码定义了保留在nrfx之外使用的PPI信道。
 */
#define NRFX_PPI_CHANNELS_USED  0

/**
 * @brief Bitmask定义了保留在nrfx之外使用的PPI组。
 */
#define NRFX_PPI_GROUPS_USED    0

/**
 * @brief Bitmask定义了保留在nrfx之外使用的SWI实例。
 */
#define NRFX_SWI_USED           0

/**
 * @brief Bitmask定义了保留在nrfx之外使用的TIMER实例。
 */
#define NRFX_TIMERS_USED        0

/** @} */

#ifdef __cplusplus
}
#endif

#endif // NRFX_GLUE_H__

