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
 * 注意HAL不是公共api，不要在应用程序代码中使用。请参阅自述文件。soc/README.md中的md
 ******************************************************************************/

// CP DMA HAL用法：
// 1.通过cp_dma_HAL_init初始化HAL层，传入为TX和RX分配的描述符
// 2.通过cp_DMA_hal_start启用DMA和中断
// 3.准备用于TX和RX的描述符
// 4.重新启动DMA引擎，以防它不工作

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>
#include <stdbool.h>
#include "esp_attr.h"
#include "hal/dma_types.h"
#include "soc/cp_dma_struct.h"

/**
 * @brief HAL上下文
 *
 */
typedef struct {
    cp_dma_dev_t *dev;
} cp_dma_hal_context_t;

typedef struct {
} cp_dma_hal_config_t;

/**
 * @brief 初始化HAL层上下文
 *
 * @param hal HAL层上下文，其内存应在驱动层分配
 * @param config HAL层的配置
 */
void cp_dma_hal_init(cp_dma_hal_context_t *hal, const cp_dma_hal_config_t *config);

/**
 * @brief 取消初始化HAL层上下文
 */
void cp_dma_hal_deinit(cp_dma_hal_context_t *hal);

/**
 * @brief 设置描述符基地址
 */
void cp_dma_hal_set_desc_base_addr(cp_dma_hal_context_t *hal, intptr_t outlink_base, intptr_t inlink_base);

/**
 * @brief 启动mem2mem DMA状态机
 */
void cp_dma_hal_start(cp_dma_hal_context_t *hal);

/**
 * @brief 停止mem2mem DMA状态机
 */
void cp_dma_hal_stop(cp_dma_hal_context_t *hal);

/**
 * @brief 获取中断状态字
 *
 * @return uint32_t中断状态
 */
uint32_t cp_dma_hal_get_intr_status(cp_dma_hal_context_t *hal) IRAM_ATTR;

/**
 * @brief 清除中断掩码
 *
 * @param mask 中断掩码
 */
void cp_dma_hal_clear_intr_status(cp_dma_hal_context_t *hal, uint32_t mask) IRAM_ATTR;

/**@{*/
/**
 * @brief 将[start_desc，end_desc]之间描述符的所有者交给DMA，然后重新启动DMA HW引擎
 *
 * @param hal HAL层上下文
 * @param start_desc 携带一个事务的第一个描述符
 * @param end_desc 携带一个事务的最后一个描述符
 */
void cp_dma_hal_restart_tx(cp_dma_hal_context_t *hal);
void cp_dma_hal_restart_rx(cp_dma_hal_context_t *hal);
/**@}*/

#ifdef __cplusplus
}
#endif

