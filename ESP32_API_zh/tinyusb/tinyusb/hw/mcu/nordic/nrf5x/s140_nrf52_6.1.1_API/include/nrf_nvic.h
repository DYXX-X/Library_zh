/*
 * 版权所有（c）2016-2018，Nordic Semiconductor ASA保留所有权利。
 *
 * 在满足以下条件的情况下，允许以源代码和二进制形式重新分发和使用，无论是否进行修改：
 *
 * 1.源代码的重新分发必须保留上述版权声明、本条件列表和以下免责声明。
 *
 * 2.二进制形式的再发行，除非嵌入产品中的Nordic Semiconductor ASA集成电路或该产品的软件更新，否则必须在发行提供的文档和/或其他材料中复制上述版权声明、本条件列表和以下免责声明。
 *
 * 3.未经事先书面许可，不得使用Nordic Semiconductor ASA的名称或其贡献者的名称来支持或推广源自本软件的产品。
 *
 * 4.本软件无论是否经过修改，只能与Nordic Semiconductor ASA集成电路一起使用。
 *
 * 5.根据本许可证以二进制形式提供的任何软件不得进行反向工程、反编译、修改和/或反汇编。
 *
 * THIS SOFTWARE IS PROVIDED BY NORDIC SEMICONDUCTOR ASA "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, NONINFRINGEMENT, AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL NORDIC SEMICONDUCTOR ASA OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * @defgroup nrf_nvic_api软设备nvic api@{
 *
 * @note 为了使用此模块，必须将以下代码添加到.c文件中：\code nrf_nvic_state_t nrf_nvac_state={0}；\结束代码
 *
 * @note 此头文件中以__（双下划线）开头的定义和声明不适用于应用程序直接使用。
 *
 * @brief 使用SoftDevice时访问NVIC的API。
 *
 */

#ifndef NRF_NVIC_H__
#define NRF_NVIC_H__

#include <stdint.h>
#include "nrf.h"
#include "nrf_svc.h"
#include "nrf_error.h"
#include "nrf_error_soc.h"

#ifdef __cplusplus
extern "C" {
#endif

/**@addtogroup NRF_NVIC_DEFINES定义
 * @{ */

/**@defgroup NRF_NVIC_ISER_DEFINES SoftDevice NVIC内部定义
 * @{ */

#define __NRF_NVIC_NVMC_IRQn (30) /**<NVMC的外围设备ID。IRQ编号用于识别外围设备，但NVMC在MDK中没有IRQ编号。*/

#define __NRF_NVIC_ISER_COUNT (2) /**<NVIC中使用的ISER/ICER寄存器的数量。*/

/**@brief SoftDevice使用的中断优先级。*/
#define __NRF_NVIC_SD_IRQ_PRIOS ((uint8_t)( \
      (1U << 0)  /**<优先级高。*/   \
    | (1U << 1)  /**<优先级中等。*/ \
    | (1U << 4)  /**<优先级低。*/    \
  ))

/**@brief 应用程序可用的中断优先级。*/
#define __NRF_NVIC_APP_IRQ_PRIOS ((uint8_t)~__NRF_NVIC_SD_IRQ_PRIOS)

/**@brief SoftDevice使用的中断，IRQn在0-31范围内。*/
#define __NRF_NVIC_SD_IRQS_0 ((uint32_t)( \
      (1U << POWER_CLOCK_IRQn) \
    | (1U << RADIO_IRQn) \
    | (1U << RTC0_IRQn) \
    | (1U << TIMER0_IRQn) \
    | (1U << RNG_IRQn) \
    | (1U << ECB_IRQn) \
    | (1U << CCM_AAR_IRQn) \
    | (1U << TEMP_IRQn) \
    | (1U << __NRF_NVIC_NVMC_IRQn) \
    | (1U << (uint32_t)SWI5_IRQn) \
  ))

/**@brief SoftDevice使用的中断，IRQn在32-63范围内。*/
#define __NRF_NVIC_SD_IRQS_1 ((uint32_t)0)

/**@brief 应用程序可用的中断，IRQn在0-31范围内。*/
#define __NRF_NVIC_APP_IRQS_0 (~__NRF_NVIC_SD_IRQS_0)

/**@brief 应用程序可用中断，IRQn在32-63范围内。*/
#define __NRF_NVIC_APP_IRQS_1 (~__NRF_NVIC_SD_IRQS_1)

/**@} */

/**@} */

/**@addtogroup NRF_NVIC_VARIABLES变量
 * @{ */

/**@brief 表示SoftDevice NVIC模块的状态结构的类型。*/
typedef struct
{
  uint32_t volatile __irq_masks[__NRF_NVIC_ISER_COUNT]; /**<NVIC中应用程序启用的IRQ。*/
  uint32_t volatile __cr_flag;                          /**<非零，如果已处于临界区域*/
} nrf_nvic_state_t;

/**@brief 保持SoftDevice NVIC模块状态的变量。这必须在应用程序源文件中声明。*/
extern nrf_nvic_state_t nrf_nvic_state;

/**@} */

/**@addtogroup NRF_NVIC_INTERNAL_FUNCTIONS软设备NVIC内部功能
 * @{ */

/**@brief 全局禁用IRQ中断，包括SoftDevice的中断。
 *
 * @retval  禁用中断前PRIMASK的值。
 */
__STATIC_INLINE int __sd_nvic_irq_disable(void);

/**@brief 全局启用IRQ中断，包括SoftDevice的中断。
 */
__STATIC_INLINE void __sd_nvic_irq_enable(void);

/**@brief 检查IRQn是否可用于应用程序
 * @param[in]  IRQn  IRQ检查
 *
 * @retval  1（true）如果要检查的IRQ对应用程序可用
 */
__STATIC_INLINE uint32_t __sd_nvic_app_accessible_irq(IRQn_Type IRQn);

/**@brief 检查应用程序的优先级是否可用
 * @param[in]  priority  检查优先级
 *
 * @retval  1（true）如果应用程序具有检查优先级
 */
__STATIC_INLINE uint32_t __sd_nvic_is_app_accessible_priority(uint32_t priority);

/**@} */

/**@addtogroup NRF_NVIC_FUNCTIONS软设备NVIC公共功能
 * @{ */

/**@brief 启用外部中断。
 * @note 对应于CMSIS中的NVIC_EnableIRQ。
 *
 * @pre IRQn有效且未被堆栈保留。
 *
 * @param[in] IRQn 请参阅CMSIS中的NVIC_EnableIRQ文档。
 *
 * @retval ：：NRF_SUCCESS中断已启用。
 * @retval ：：NRF_ERROR_SOC_NVIC_INTERRUPT_NOT_AVAILABLE中断不适用于应用程序。
 * @retval ：：NRF_ERROR_SOC_NVIC_INTERRUPT_PRIORITY_NOT_ALLOWED中断的优先级不适用于应用程序。
 */
__STATIC_INLINE uint32_t sd_nvic_EnableIRQ(IRQn_Type IRQn);

/**@brief  禁用外部中断。
 * @note 对应于CMSIS中的NVIC_DisableIRQ。
 *
 * @pre IRQn有效且未被堆栈保留。
 *
 * @param[in] IRQn 请参阅CMSIS中的NVIC_DisableIRQ文档。
 *
 * @retval ：：NRF_SUCCESS中断被禁用。
 * @retval ：：NRF_ERROR_SOC_NVIC_INTERRUPT_NOT_AVAILABLE中断不适用于应用程序。
 */
__STATIC_INLINE uint32_t sd_nvic_DisableIRQ(IRQn_Type IRQn);

/**@brief  获取挂起中断。
 * @note 对应于CMSIS中的NVIC_GetPendingIRQ。
 *
 * @pre IRQn有效且未被堆栈保留。
 *
 * @param[in]   IRQn          请参阅CMSIS中的NVIC_GetPendingIRQ文档。
 * @param[out]  p_pending_irq NVIC_GetPendingIRQ的返回值。
 *
 * @retval ：：NRF_SUCCESS中断可用于应用程序。
 * @retval ：：NRF_ERROR_SOC_NVIC_INTERRUPT_NOT_AVAILABLE IRQn不适用于应用程序。
 */
__STATIC_INLINE uint32_t sd_nvic_GetPendingIRQ(IRQn_Type IRQn, uint32_t * p_pending_irq);

/**@brief  设置挂起中断。
 * @note 对应于CMSIS中的NVIC_SetPendingIRQ。
 *
 * @pre IRQn有效且未被堆栈保留。
 *
 * @param[in] IRQn 请参阅CMSIS中的NVIC_SetPendingIRQ文档。
 *
 * @retval ：：NRF_SUCCESS中断设置为挂起。
 * @retval ：：NRF_ERROR_SOC_NVIC_INTERRUPT_NOT_AVAILABLE IRQn不适用于应用程序。
 */
__STATIC_INLINE uint32_t sd_nvic_SetPendingIRQ(IRQn_Type IRQn);

/**@brief  清除挂起中断。
 * @note 对应于CMSIS中的NVIC_ClearEndingIRQ。
 *
 * @pre IRQn有效且未被堆栈保留。
 *
 * @param[in] IRQn 请参阅CMSIS中的NVIC_ClearEndingIRQ文档。
 *
 * @retval ：：NRF_SUCCESS中断挂起标志被清除。
 * @retval ：：NRF_ERROR_SOC_NVIC_INTERRUPT_NOT_AVAILABLE IRQn不适用于应用程序。
 */
__STATIC_INLINE uint32_t sd_nvic_ClearPendingIRQ(IRQn_Type IRQn);

/**@brief 设置中断优先级。
 * @note 对应于CMSIS中的NVIC_SetPriority。
 *
 * @pre IRQn有效且未被堆栈保留。
 * @pre 优先级有效，不由堆栈保留。
 *
 * @param[in] IRQn      请参阅CMSIS中的NVIC_SetPriority文档。
 * @param[in] priority  应用程序使用的有效IRQ优先级。
 *
 * @retval ：：NRF_SUCCESS中断和优先级可用于应用程序。
 * @retval ：：NRF_ERROR_SOC_NVIC_INTERRUPT_NOT_AVAILABLE IRQn不适用于应用程序。
 * @retval ：：NRF_ERROR_SOC_NVIC_INTERRUPT_PRIORITY_NOT_ALLOWED中断优先级不适用于应用程序。
 */
__STATIC_INLINE uint32_t sd_nvic_SetPriority(IRQn_Type IRQn, uint32_t priority);

/**@brief 获取中断优先级。
 * @note 对应于CMSIS中的NVIC_GetPriority。
 *
 * @pre IRQn有效且未被堆栈保留。
 *
 * @param[in]  IRQn         请参阅CMSIS中的NVIC_GetPriority文档。
 * @param[out] p_priority   NVIC_GetPriority的返回值。
 *
 * @retval ：：NRF_SUCCESS中断优先级以p_priority返回。
 * @retval ：：NRF_ERROR_SOC_NVIC_INTERRUPT_NOT_AVAILABLE-IRQn不适用于应用程序。
 */
__STATIC_INLINE uint32_t sd_nvic_GetPriority(IRQn_Type IRQn, uint32_t * p_priority);

/**@brief 系统重置。
 * @note 对应于CMSIS中的NVIC_SystemReset。
 *
 * @retval ::NRF_ERROR_SOC_NVIC_SHOULD_NOT_RETURN
 */
__STATIC_INLINE uint32_t sd_nvic_SystemReset(void);

/**@brief 输入关键区域。
 *
 * @post 应用程序中断将被禁用。
 * @note sd_nvic_critical_region_enter（）和：：sd_nvic_Critial_region\uexit（）必须在每个执行上下文中成对调用
 * @sa sd_设备_关键区域_退出
 *
 * @param[out] p_is_nested_critical_region 如果为1，则应用程序现在处于嵌套的关键区域中。
 *
 * @retval ::NRF_SUCCESS
 */
__STATIC_INLINE uint32_t sd_nvic_critical_region_enter(uint8_t * p_is_nested_critical_region);

/**@brief 退出关键区域。
 *
 * @pre 应用程序已使用：sd_nvic_critical_region_enter输入关键区域。
 * @post 如果不在嵌套的关键区域中，应用程序中断将恢复到调用：：sd_nvic_critical_region_enter之前的状态。
 *
 * @param[in] is_nested_critical_region 如果设置为1，则不会退出关键区域@sa sd_设备_关键区域_输入。
 *
 * @retval ::NRF_SUCCESS
 */
__STATIC_INLINE uint32_t sd_nvic_critical_region_exit(uint8_t is_nested_critical_region);

/**@} */

#ifndef SUPPRESS_INLINE_IMPLEMENTATION

__STATIC_INLINE int __sd_nvic_irq_disable(void)
{
  int pm = __get_PRIMASK();
  __disable_irq();
  return pm;
}

__STATIC_INLINE void __sd_nvic_irq_enable(void)
{
  __enable_irq();
}

__STATIC_INLINE uint32_t __sd_nvic_app_accessible_irq(IRQn_Type IRQn)
{
  if (IRQn < 32)
  {
    return ((1UL<<IRQn) & __NRF_NVIC_APP_IRQS_0) != 0;
  }
  else if (IRQn < 64)
  {
    return ((1UL<<(IRQn-32)) & __NRF_NVIC_APP_IRQS_1) != 0;
  }
  else
  {
    return 1;
  }
}

__STATIC_INLINE uint32_t __sd_nvic_is_app_accessible_priority(uint32_t priority)
{
  if( (priority >= (1 << __NVIC_PRIO_BITS))
   || (((1 << priority) & __NRF_NVIC_APP_IRQ_PRIOS) == 0)
    )
  {
    return 0;
  }
  return 1;
}


__STATIC_INLINE uint32_t sd_nvic_EnableIRQ(IRQn_Type IRQn)
{
  if (!__sd_nvic_app_accessible_irq(IRQn))
  {
    return NRF_ERROR_SOC_NVIC_INTERRUPT_NOT_AVAILABLE;
  }
  if (!__sd_nvic_is_app_accessible_priority(NVIC_GetPriority(IRQn)))
  {
    return NRF_ERROR_SOC_NVIC_INTERRUPT_PRIORITY_NOT_ALLOWED;
  }

  if (nrf_nvic_state.__cr_flag)
  {
    nrf_nvic_state.__irq_masks[(uint32_t)((int32_t)IRQn) >> 5] |= (uint32_t)(1 << ((uint32_t)((int32_t)IRQn) & (uint32_t)0x1F));
  }
  else
  {
    NVIC_EnableIRQ(IRQn);
  }
  return NRF_SUCCESS;
}

__STATIC_INLINE uint32_t sd_nvic_DisableIRQ(IRQn_Type IRQn)
{
  if (!__sd_nvic_app_accessible_irq(IRQn))
  {
    return NRF_ERROR_SOC_NVIC_INTERRUPT_NOT_AVAILABLE;
  }

  if (nrf_nvic_state.__cr_flag)
  {
    nrf_nvic_state.__irq_masks[(uint32_t)((int32_t)IRQn) >> 5] &= ~(1UL << ((uint32_t)(IRQn) & 0x1F));
  }
  else
  {
    NVIC_DisableIRQ(IRQn);
  }

  return NRF_SUCCESS;
}

__STATIC_INLINE uint32_t sd_nvic_GetPendingIRQ(IRQn_Type IRQn, uint32_t * p_pending_irq)
{
  if (__sd_nvic_app_accessible_irq(IRQn))
  {
    *p_pending_irq = NVIC_GetPendingIRQ(IRQn);
    return NRF_SUCCESS;
  }
  else
  {
    return NRF_ERROR_SOC_NVIC_INTERRUPT_NOT_AVAILABLE;
  }
}

__STATIC_INLINE uint32_t sd_nvic_SetPendingIRQ(IRQn_Type IRQn)
{
  if (__sd_nvic_app_accessible_irq(IRQn))
  {
    NVIC_SetPendingIRQ(IRQn);
    return NRF_SUCCESS;
  }
  else
  {
    return NRF_ERROR_SOC_NVIC_INTERRUPT_NOT_AVAILABLE;
  }
}

__STATIC_INLINE uint32_t sd_nvic_ClearPendingIRQ(IRQn_Type IRQn)
{
  if (__sd_nvic_app_accessible_irq(IRQn))
  {
    NVIC_ClearPendingIRQ(IRQn);
    return NRF_SUCCESS;
  }
  else
  {
    return NRF_ERROR_SOC_NVIC_INTERRUPT_NOT_AVAILABLE;
  }
}

__STATIC_INLINE uint32_t sd_nvic_SetPriority(IRQn_Type IRQn, uint32_t priority)
{
  if (!__sd_nvic_app_accessible_irq(IRQn))
  {
    return NRF_ERROR_SOC_NVIC_INTERRUPT_NOT_AVAILABLE;
  }

  if (!__sd_nvic_is_app_accessible_priority(priority))
  {
    return NRF_ERROR_SOC_NVIC_INTERRUPT_PRIORITY_NOT_ALLOWED;
  }

  NVIC_SetPriority(IRQn, (uint32_t)priority);
  return NRF_SUCCESS;
}

__STATIC_INLINE uint32_t sd_nvic_GetPriority(IRQn_Type IRQn, uint32_t * p_priority)
{
  if (__sd_nvic_app_accessible_irq(IRQn))
  {
    *p_priority = (NVIC_GetPriority(IRQn) & 0xFF);
    return NRF_SUCCESS;
  }
  else
  {
    return NRF_ERROR_SOC_NVIC_INTERRUPT_NOT_AVAILABLE;
  }
}

__STATIC_INLINE uint32_t sd_nvic_SystemReset(void)
{
  NVIC_SystemReset();
  return NRF_ERROR_SOC_NVIC_SHOULD_NOT_RETURN;
}

__STATIC_INLINE uint32_t sd_nvic_critical_region_enter(uint8_t * p_is_nested_critical_region)
{
  int was_masked = __sd_nvic_irq_disable();
  if (!nrf_nvic_state.__cr_flag)
  {
    nrf_nvic_state.__cr_flag = 1;
    nrf_nvic_state.__irq_masks[0] = ( NVIC->ICER[0] & __NRF_NVIC_APP_IRQS_0 );
    NVIC->ICER[0] = __NRF_NVIC_APP_IRQS_0;
    nrf_nvic_state.__irq_masks[1] = ( NVIC->ICER[1] & __NRF_NVIC_APP_IRQS_1 );
    NVIC->ICER[1] = __NRF_NVIC_APP_IRQS_1;
    *p_is_nested_critical_region = 0;
  }
  else
  {
    *p_is_nested_critical_region = 1;
  }
  if (!was_masked)
  {
    __sd_nvic_irq_enable();
  }
  return NRF_SUCCESS;
}

__STATIC_INLINE uint32_t sd_nvic_critical_region_exit(uint8_t is_nested_critical_region)
{
  if (nrf_nvic_state.__cr_flag && (is_nested_critical_region == 0))
  {
    int was_masked = __sd_nvic_irq_disable();
    NVIC->ISER[0] = nrf_nvic_state.__irq_masks[0];
    NVIC->ISER[1] = nrf_nvic_state.__irq_masks[1];
    nrf_nvic_state.__cr_flag = 0;
    if (!was_masked)
    {
      __sd_nvic_irq_enable();
    }
  }

  return NRF_SUCCESS;
}

#endif /* SUPPRESS_INLINE_IMPLEMENTATION */

#ifdef __cplusplus
}
#endif

#endif // NRF_NVIC_H__

/**@} */

