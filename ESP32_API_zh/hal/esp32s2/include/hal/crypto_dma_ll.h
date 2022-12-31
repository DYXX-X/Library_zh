// 版权所有2020 Espressif Systems（上海）私人有限公司
//
// 根据Apache许可证2.0版（“许可证”）获得许可；
// 除非符合许可证，否则不得使用此文件。
// 您可以在以下地址获取许可证副本：
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// 除非适用法律要求或书面同意，软件
// 根据许可证分发的内容是按“原样”分发的，
// 无任何明示或暗示的保证或条件。
// 有关管理权限和
// 许可证下的限制。

/*******************************************************************************
 * 注意ll不是公共api，不要在应用程序代码中使用。请参阅自述文件。soc/include/hal/readme.md中的md
 ******************************************************************************/
#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "soc/hwcrypto_reg.h"
#include "soc/dport_reg.h"

typedef enum {
    CRYPTO_DMA_AES= 0,
    CRYPTO_DMA_SHA,
} crypto_dma_mode_t;

/**
 * @brief 重置DMA
 *
 */
static inline void crypto_dma_ll_reset(void)
{
    SET_PERI_REG_MASK(CRYPTO_DMA_CONF0_REG, CONF0_REG_AHBM_RST | CONF0_REG_OUT_RST | CONF0_REG_AHBM_FIFO_RST);
    CLEAR_PERI_REG_MASK(CRYPTO_DMA_CONF0_REG, CONF0_REG_AHBM_RST | CONF0_REG_OUT_RST | CONF0_REG_AHBM_FIFO_RST);
}

/**
 * @brief 选择加密DMA模式
 *
 * @param mode 使用模式，AES或SHA
 */
static inline void crypto_dma_ll_set_mode(crypto_dma_mode_t mode)
{
    REG_WRITE(CRYPTO_DMA_AES_SHA_SELECT_REG, mode);
}

/**
 * @brief 设置传输的输出链接
 *
 * @param outlink_addr outlink缓冲区的地址
 */
static inline void crypto_dma_ll_outlink_set(uint32_t outlink_addr)
{
    CLEAR_PERI_REG_MASK(CRYPTO_DMA_OUT_LINK_REG, OUT_LINK_REG_OUTLINK_ADDR);
    SET_PERI_REG_MASK(CRYPTO_DMA_OUT_LINK_REG, outlink_addr & OUT_LINK_REG_OUTLINK_ADDR);
}

/**
 * @brief 设置传输的内联
 *
 * @param inlink_addr 内联缓冲区的地址
 */
static inline void crypto_dma_ll_inlink_set(uint32_t inlink_addr)
{
    CLEAR_PERI_REG_MASK(CRYPTO_DMA_IN_LINK_REG, IN_LINK_REG_INLINK_ADDR);
    SET_PERI_REG_MASK(CRYPTO_DMA_IN_LINK_REG, inlink_addr & IN_LINK_REG_INLINK_ADDR);
}

/**
 * @brief 启动输出链接
 *
 */
static inline void crypto_dma_ll_outlink_start(void)
{
    SET_PERI_REG_MASK(CRYPTO_DMA_OUT_LINK_REG, OUT_LINK_REG_OUTLINK_START);
}

/**
 * @brief 启动内联
 *
 */
static inline void crypto_dma_ll_inlink_start(void)
{
    SET_PERI_REG_MASK(CRYPTO_DMA_IN_LINK_REG, IN_LINK_REG_INLINK_START);
}

static inline bool crypto_dma_ll_inlink_is_eof(void)
{
    return ((REG_READ(CRYPTO_DMA_INT_RAW_REG) & INT_RAW_IN_SUC_EOF) == INT_RAW_IN_SUC_EOF);
}


#ifdef __cplusplus
}
#endif

