/*
 * 版权所有（c）2012-2017，Nordic Semiconductor ASA保留所有权利。
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
  @添加组nrf_soc_api@{
  @defgroup nrf_soc_error soc库错误代码@{

  @SoC库的简要错误定义

*/

/* 收割台护罩*/
#ifndef NRF_ERROR_SOC_H__
#define NRF_ERROR_SOC_H__

#include "nrf_error.h"
#ifdef __cplusplus
extern "C" {
#endif

/* Mutex错误*/
#define NRF_ERROR_SOC_MUTEX_ALREADY_TAKEN                 (NRF_ERROR_SOC_BASE_NUM + 0)  ///<Mutex已使用

/* NVIC错误*/
#define NRF_ERROR_SOC_NVIC_INTERRUPT_NOT_AVAILABLE        (NRF_ERROR_SOC_BASE_NUM + 1)  ///<NVIC中断不可用
#define NRF_ERROR_SOC_NVIC_INTERRUPT_PRIORITY_NOT_ALLOWED (NRF_ERROR_SOC_BASE_NUM + 2)  ///<不允许NVIC中断优先级
#define NRF_ERROR_SOC_NVIC_SHOULD_NOT_RETURN              (NRF_ERROR_SOC_BASE_NUM + 3)  ///<NVIC不应返回

/* 电源错误*/
#define NRF_ERROR_SOC_POWER_MODE_UNKNOWN                  (NRF_ERROR_SOC_BASE_NUM + 4)  ///<电源模式未知
#define NRF_ERROR_SOC_POWER_POF_THRESHOLD_UNKNOWN         (NRF_ERROR_SOC_BASE_NUM + 5)  ///<功率POF阈值未知
#define NRF_ERROR_SOC_POWER_OFF_SHOULD_NOT_RETURN         (NRF_ERROR_SOC_BASE_NUM + 6)  ///<断电不应返回

/* 随机错误*/
#define NRF_ERROR_SOC_RAND_NOT_ENOUGH_VALUES              (NRF_ERROR_SOC_BASE_NUM + 7)  ///<RAND值不足

/* PPI错误*/
#define NRF_ERROR_SOC_PPI_INVALID_CHANNEL                 (NRF_ERROR_SOC_BASE_NUM + 8)  ///<无效PPI通道
#define NRF_ERROR_SOC_PPI_INVALID_GROUP                   (NRF_ERROR_SOC_BASE_NUM + 9)  ///<无效PPI组

#ifdef __cplusplus
}
#endif
#endif // NRF_ERROR_SOC_H__
/**
  @} @}
*/

