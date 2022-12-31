/**
  ******************************************************************************
  * @file    dcd_stm32f0_pvt_st.h
  * @brief   来自ST代码的DCD实用程序
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy；版权所有（c）2016 STMicroelectronics</center></h2><h2><center>&copy；零件版权所有（c）N Conrad</center></h2>
  *
  * 在满足以下条件的情况下，允许以源代码和二进制形式重新分发和使用，无论是否进行修改：1.重新分发源代码必须保留上述版权声明、本条件列表和以下免责声明。2.二进制形式的再发行必须在随发行提供的文档和/或其他材料中复制上述版权声明、本条件列表和以下免责声明。3.未经事先书面许可，不得使用STMicroelectronics的名称或其贡献者的名称来支持或推广源自本软件的产品。
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  **********/

// 此文件包含从ST的HAL复制的源代码，因此应具有其版权声明。

// PMA_LENGTH是以字节为单位的PMA缓冲区大小。
// 在512字节设备上，以两个字的步长进行访问（每隔16位地址使用一次）
// 在1024字节设备上，以一个字的步长进行访问（使用每16位地址）

#ifndef PORTABLE_ST_STM32F0_DCD_STM32F0_FSDEV_PVT_ST_H_
#define PORTABLE_ST_STM32F0_DCD_STM32F0_FSDEV_PVT_ST_H_

#if defined(STM32F042x6) || \
    defined(STM32F070x6) || defined(STM32F070xB) || \
    defined(STM32F072xB) || \
    defined(STM32F078xx)
  #include "stm32f0xx.h"
  #define PMA_LENGTH (1024u)
  // F0x2型号无晶体
  // 所有都具有内部D+上拉功能
  // 070RB:2 x 16位/字存储器LPM支持，BCD支持
  // USB专用PMA（不与CAN共享）

#elif defined(STM32F1_FSDEV)
  #include "stm32f1xx.h"
  #define PMA_LENGTH (512u)
  // 无内部引体向上
  //         *B、 和*C:2 x 16位/字

  // F1将此名称与其他名称不同
  #define USB_CNTR_LPMODE   USB_CNTR_LP_MODE

#elif defined(STM32F302xB) || defined(STM32F302xC) || \
      defined(STM32F303xB) || defined(STM32F303xC) || \
      defined(STM32F373xC)
  #include "stm32f3xx.h"
  #define PMA_LENGTH (512u)
  // 无内部引体向上
  //         *B、 和*C:1 x 16位/字
  // PMA专用于USB（不与CAN共享）

#elif defined(STM32F302x6) || defined(STM32F302x8) || \
      defined(STM32F302xD) || defined(STM32F302xE) || \
      defined(STM32F303xD) || defined(STM32F303xE)
  #include "stm32f3xx.h"
  #define PMA_LENGTH (1024u)
  // 无内部引体向上
  // *6、*8、*D和*E:2 x 16位/字LPM支持
  // 当启用CAN时钟时，USB只能使用前768字节。

#elif CFG_TUSB_MCU == OPT_MCU_STM32L0
  #include "stm32l0xx.h"
  #define PMA_LENGTH (1024u)

#else
  #error You are using an untested or unimplemented STM32 variant. Please update the driver.
  // 这包括L1x0、L1x1、L1x2、L4x2和L4x3、G1x1、G1x3和G1x4
#endif

// 为了访问数据包
#if ((PMA_LENGTH) == 512u)
  #define PMA_STRIDE  (2u)
#elif ((PMA_LENGTH) == 1024u)
  #define PMA_STRIDE  (1u)
#endif

// 为了类型安全，为PMAADDR的易失性地址创建一个新的宏
// 如果我们将其转换为非易失性类型，编译器应该警告我们？
// 还需要易失性来防止优化器将访问更改为32位（因为32位访问被禁止）
static __IO uint16_t * const pma = (__IO uint16_t*)USB_PMAADDR;

// 原型
static inline __IO uint16_t* pcd_ep_rx_cnt_ptr(USB_TypeDef * USBx, uint32_t bEpNum);
static inline __IO uint16_t* pcd_ep_tx_cnt_ptr(USB_TypeDef * USBx, uint32_t bEpNum);
static inline void pcd_set_endpoint(USB_TypeDef * USBx, uint32_t bEpNum, uint32_t wRegValue);


/* 设置终点*/
static inline void pcd_set_endpoint(USB_TypeDef * USBx, uint32_t bEpNum, uint32_t wRegValue)
{
  __O uint16_t *reg = (__O uint16_t *)((&USBx->EP0R) + bEpNum*2u);
  *reg = (uint16_t)wRegValue;
}

/* 获取终点*/
static inline uint16_t pcd_get_endpoint(USB_TypeDef * USBx, uint32_t bEpNum) {
  __I uint16_t *reg = (__I uint16_t *)((&USBx->EP0R) + bEpNum*2u);
  return *reg;
}

static inline void pcd_set_eptype(USB_TypeDef * USBx, uint32_t bEpNum, uint32_t wType)
{
  uint32_t regVal = pcd_get_endpoint(USBx, bEpNum);
  regVal &= (uint32_t)USB_EP_T_MASK;
  regVal |= wType;
  regVal |= USB_EP_CTR_RX | USB_EP_CTR_TX; // 这些在write0时清除，因此必须设置为高
  pcd_set_endpoint(USBx, bEpNum, regVal);
}

static inline uint32_t pcd_get_eptype(USB_TypeDef * USBx, uint32_t bEpNum)
{
  uint32_t regVal = pcd_get_endpoint(USBx, bEpNum);
  regVal &= USB_EP_T_FIELD;
  return regVal;
}
/**
  * @brief  清除端点寄存器中的位CTR_RX/CTR_TX。
  * @param  USBx USB外围设备实例寄存器地址。
  * @param  bEpNum 端点编号。
  * @retval 没有一个
  */
static inline void pcd_clear_rx_ep_ctr(USB_TypeDef * USBx, uint32_t bEpNum)
{
  uint32_t regVal = pcd_get_endpoint(USBx, bEpNum);
  regVal &= USB_EPREG_MASK;
  regVal &= ~USB_EP_CTR_RX;
  regVal |= USB_EP_CTR_TX; // 保留CTR_TX（写入0时清除）
  pcd_set_endpoint(USBx, bEpNum, regVal);
}
static inline void pcd_clear_tx_ep_ctr(USB_TypeDef * USBx, uint32_t bEpNum)
{
  uint32_t regVal = pcd_get_endpoint(USBx, bEpNum);
  regVal &= USB_EPREG_MASK;
  regVal &= ~USB_EP_CTR_TX;
  regVal |= USB_EP_CTR_RX; // 保留CTR_RX（写入0时清除）
  pcd_set_endpoint(USBx, bEpNum,regVal);
}
/**
  * @brief  获取tx缓冲区的计数器。
  * @param  USBx USB外围设备实例寄存器地址。
  * @param  bEpNum 端点编号。
  * @retval 计数器值
  */
static inline uint32_t pcd_get_ep_tx_cnt(USB_TypeDef * USBx, uint32_t bEpNum)
{
  __I uint16_t *regPtr = pcd_ep_tx_cnt_ptr(USBx, bEpNum);
  return *regPtr & 0x3ffU;
}

static inline uint32_t pcd_get_ep_rx_cnt(USB_TypeDef * USBx, uint32_t bEpNum)
{
  __I uint16_t *regPtr = pcd_ep_rx_cnt_ptr(USBx, bEpNum);
  return *regPtr & 0x3ffU;
}

/**
  * @brief  用块数设置rx缓冲区的计数器。
  * @param  dwReg 登记
  * @param  wCount 柜台
  * @param  wNBlocks 砌块数量。
  * @retval 没有一个
  */

static inline void pcd_set_ep_cnt_rx_reg(__O uint16_t * pdwReg, size_t wCount)  {
  uint32_t wNBlocks;
  if(wCount > 62u)
  {
    wNBlocks = wCount >> 5u;
    if((wCount & 0x1fU) == 0u)
    {
      wNBlocks--;
    }
    wNBlocks = wNBlocks << 10u;
    wNBlocks |= 0x8000u; // 将块大小标记为32字节
    *pdwReg = (uint16_t)wNBlocks;
  }
  else
  {
    wNBlocks = wCount >> 1u;
    if((wCount & 0x1U) != 0u)
    {
      wNBlocks++;
    }
    *pdwReg = (uint16_t)((wNBlocks) << 10u);
  }
}


/**
  * @brief  设置端点寄存器中的地址。
  * @param  USBx USB外围设备实例寄存器地址。
  * @param  bEpNum 端点编号。
  * @param  bAddr 住址
  * @retval 没有一个
  */
static inline void pcd_set_ep_address(USB_TypeDef * USBx,  uint32_t bEpNum, uint32_t bAddr)
{
  uint32_t regVal = pcd_get_endpoint(USBx, bEpNum);
  regVal &= USB_EPREG_MASK;
  regVal |= bAddr;
  regVal |= USB_EP_CTR_RX|USB_EP_CTR_TX;
  pcd_set_endpoint(USBx, bEpNum,regVal);
}

static inline __IO uint16_t * pcd_btable_word_ptr(USB_TypeDef * USBx, size_t x)
{
  size_t total_word_offset = (((USBx)->BTABLE)>>1) + x;
  total_word_offset *= PMA_STRIDE;
  return &(pma[total_word_offset]);
}

// 指向PMA表项的指针（使用ARM地址空间）
static inline __IO uint16_t* pcd_ep_tx_address_ptr(USB_TypeDef * USBx, uint32_t bEpNum)
{
  return pcd_btable_word_ptr(USBx,(bEpNum)*4u + 0u);
}
static inline __IO uint16_t* pcd_ep_tx_cnt_ptr(USB_TypeDef * USBx, uint32_t bEpNum)
{
  return pcd_btable_word_ptr(USBx,(bEpNum)*4u + 1u);
}

static inline __IO uint16_t* pcd_ep_rx_address_ptr(USB_TypeDef * USBx, uint32_t bEpNum)
{
  return  pcd_btable_word_ptr(USBx,(bEpNum)*4u + 2u);
}

static inline __IO uint16_t* pcd_ep_rx_cnt_ptr(USB_TypeDef * USBx, uint32_t bEpNum)
{
  return pcd_btable_word_ptr(USBx,(bEpNum)*4u + 3u);
}

static inline void pcd_set_ep_tx_cnt(USB_TypeDef * USBx,  uint32_t bEpNum, uint32_t wCount)
{
  *pcd_ep_tx_cnt_ptr(USBx, bEpNum) = (uint16_t)wCount;
}

static inline void pcd_set_ep_rx_cnt(USB_TypeDef * USBx,  uint32_t bEpNum, uint32_t wCount)
{
  __IO uint16_t *pdwReg = pcd_ep_rx_cnt_ptr((USBx),(bEpNum));
  pcd_set_ep_cnt_rx_reg(pdwReg, wCount);
}

/**
  * @brief  设置tx传输的状态（位STAT_tx[1:0]）。
  * @param  USBx USB外围设备实例寄存器地址。
  * @param  bEpNum 端点编号。
  * @param  wState 新国家
  * @retval 没有一个
  */
static inline void pcd_set_ep_tx_status(USB_TypeDef * USBx,  uint32_t bEpNum, uint32_t wState)
{
  uint32_t regVal = pcd_get_endpoint(USBx, bEpNum);
  regVal &= USB_EPTX_DTOGMASK;

  /* 切换第一位？*/
  if((USB_EPTX_DTOG1 & (wState))!= 0U)
  {
    regVal ^= USB_EPTX_DTOG1;
  }
  /* 切换第二位？*/
  if((USB_EPTX_DTOG2 & ((uint32_t)(wState)))!= 0U)
  {
    regVal ^= USB_EPTX_DTOG2;
  }
  regVal |= USB_EP_CTR_RX|USB_EP_CTR_TX;
  pcd_set_endpoint(USBx, bEpNum, regVal);
} /* pcd_set_ep_tx_状态*/

/**
  * @brief  设置rx传输的状态（位STAT_TX[1:0]）
  * @param  USBx USB外围设备实例寄存器地址。
  * @param  bEpNum 端点编号。
  * @param  wState 新国家
  * @retval 没有一个
  */

static inline void pcd_set_ep_rx_status(USB_TypeDef * USBx,  uint32_t bEpNum, uint32_t wState)
{
  uint32_t regVal = pcd_get_endpoint(USBx, bEpNum);
  regVal &= USB_EPRX_DTOGMASK;

  /* 切换第一位？*/
  if((USB_EPRX_DTOG1 & wState)!= 0U)
  {
    regVal ^= USB_EPRX_DTOG1;
  }
  /* 切换第二位？*/
  if((USB_EPRX_DTOG2 & wState)!= 0U)
  {
    regVal ^= USB_EPRX_DTOG2;
  }
  regVal |= USB_EP_CTR_RX|USB_EP_CTR_TX;
  pcd_set_endpoint(USBx, bEpNum, regVal);
} /* pcd_set_ep_rx状态*/

static inline uint32_t pcd_get_ep_rx_status(USB_TypeDef * USBx,  uint32_t bEpNum)
{
  uint32_t regVal = pcd_get_endpoint(USBx, bEpNum);
  return (regVal & USB_EPRX_STAT) >> (12u);
} /* pcd_get_ep_rx状态*/


/**
  * @brief  切换端点寄存器中的DTOG_RX/DTOG_TX位。
  * @param  USBx USB外围设备实例寄存器地址。
  * @param  bEpNum 端点编号。
  * @retval 没有一个
  */
static inline void pcd_rx_dtog(USB_TypeDef * USBx,  uint32_t bEpNum)
{
  uint32_t regVal = pcd_get_endpoint(USBx, bEpNum);
  regVal &= USB_EPREG_MASK;
  regVal |= USB_EP_CTR_RX|USB_EP_CTR_TX|USB_EP_DTOG_RX;
  pcd_set_endpoint(USBx, bEpNum, regVal);
}

static inline void pcd_tx_dtog(USB_TypeDef * USBx,  uint32_t bEpNum)
{
  uint32_t regVal = pcd_get_endpoint(USBx, bEpNum);
  regVal &= USB_EPREG_MASK;
  regVal |= USB_EP_CTR_RX|USB_EP_CTR_TX|USB_EP_DTOG_TX;
  pcd_set_endpoint(USBx, bEpNum, regVal);
}

/**
  * @brief  清除端点寄存器中的DTOG_RX/DTOG_TX位。
  * @param  USBx USB外围设备实例寄存器地址。
  * @param  bEpNum 端点编号。
  * @retval 没有一个
  */

static inline void pcd_clear_rx_dtog(USB_TypeDef * USBx,  uint32_t bEpNum)
{
  uint32_t regVal = pcd_get_endpoint(USBx, bEpNum);
  if((regVal & USB_EP_DTOG_RX) != 0)
  {
    pcd_rx_dtog(USBx,bEpNum);
  }
}

static inline void pcd_clear_tx_dtog(USB_TypeDef * USBx,  uint32_t bEpNum)
{
  uint32_t regVal = pcd_get_endpoint(USBx, bEpNum);
  if((regVal & USB_EP_DTOG_TX) != 0)
  {
    pcd_tx_dtog(USBx,bEpNum);
  }
}

/**
  * @brief  设置并清除EP_KIND位。
  * @param  USBx USB外围设备实例寄存器地址。
  * @param  bEpNum 端点编号。
  * @retval 没有一个
  */

static inline void pcd_set_ep_kind(USB_TypeDef * USBx,  uint32_t bEpNum)
{
  uint32_t regVal = pcd_get_endpoint(USBx, bEpNum);
  regVal |= USB_EP_KIND;
  regVal &= USB_EPREG_MASK;
  regVal |= USB_EP_CTR_RX|USB_EP_CTR_TX;
  pcd_set_endpoint(USBx, bEpNum, regVal);
}
static inline void pcd_clear_ep_kind(USB_TypeDef * USBx, uint32_t bEpNum)
{
  uint32_t regVal = pcd_get_endpoint(USBx, bEpNum);
  regVal &= USB_EPKIND_MASK;
  regVal |= USB_EP_CTR_RX|USB_EP_CTR_TX;
  pcd_set_endpoint(USBx, bEpNum, regVal);
}

// 这将检查设备是否具有“LPM”
#if defined(USB_ISTR_L1REQ)
#define USB_ISTR_L1REQ_FORCED (USB_ISTR_L1REQ)
#else
#define USB_ISTR_L1REQ_FORCED ((uint16_t)0x0000U)
#endif

#define USB_ISTR_ALL_EVENTS (USB_ISTR_PMAOVR | USB_ISTR_ERR | USB_ISTR_WKUP | USB_ISTR_SUSP | \
     USB_ISTR_RESET | USB_ISTR_SOF | USB_ISTR_ESOF | USB_ISTR_L1REQ_FORCED )

// 硬件中的端点数
#define STFSDEV_EP_COUNT (8u)

#endif /* PORTABLE_ST_STM32F0_DCD_STM32F0_FSDEV_PVT_ST_H_ */

