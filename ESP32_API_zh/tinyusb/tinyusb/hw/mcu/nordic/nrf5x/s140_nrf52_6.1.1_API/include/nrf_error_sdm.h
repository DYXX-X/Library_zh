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
  @添加组nrf_sdm_api@{
  @defgroup nrf_sdm_error SoftDevice Manager错误代码@{

  @SDM API的简要错误定义
*/

/* 收割台护罩*/
#ifndef NRF_ERROR_SDM_H__
#define NRF_ERROR_SDM_H__

#include "nrf_error.h"

#ifdef __cplusplus
extern "C" {
#endif

#define NRF_ERROR_SDM_LFCLK_SOURCE_UNKNOWN              (NRF_ERROR_SDM_BASE_NUM + 0)  ///<未知LFCLK源。
#define NRF_ERROR_SDM_INCORRECT_INTERRUPT_CONFIGURATION (NRF_ERROR_SDM_BASE_NUM + 1)  ///<中断配置不正确（可能是由于使用了非法的优先级或启用了SoftDevice中断）。
#define NRF_ERROR_SDM_INCORRECT_CLENR0                  (NRF_ERROR_SDM_BASE_NUM + 2)  ///<CLENR0不正确（可能由SoftDevice错误闪烁引起）。

#ifdef __cplusplus
}
#endif
#endif // NRF_ERROR_SDM_H__

/**
  @} @}
*/

