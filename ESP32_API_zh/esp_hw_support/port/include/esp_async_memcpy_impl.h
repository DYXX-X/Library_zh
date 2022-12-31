/*
 * SPDX文件版权文本：2020-2021浓缩咖啡系统（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>
#include "esp_err.h"
#include "esp_intr_alloc.h"
#include "soc/soc_caps.h"
#include "hal/dma_types.h"
#include "freertos/FreeRTOS.h"

#if SOC_CP_DMA_SUPPORTED
#include "hal/cp_dma_ll.h"
#include "hal/cp_dma_hal.h"
#elif SOC_GDMA_SUPPORTED
#include "esp_private/gdma.h"
#endif


/**
 * @brief 异步mcp实现层上下文的类型
 *
 */
typedef struct {
#if SOC_CP_DMA_SUPPORTED
    cp_dma_hal_context_t hal; // CP DMA hal
    intr_handle_t intr; // CP DMA中断句柄
    portMUX_TYPE hal_lock; // CP DMA HAL级自旋锁
#elif SOC_GDMA_SUPPORTED
    gdma_channel_handle_t tx_channel;
    gdma_channel_handle_t rx_channel;
#endif
    intptr_t rx_eof_addr;
    size_t sram_trans_align;
    size_t psram_trans_align;
    bool isr_need_yield;      // 如果当前isr需要更高优先级任务的产量
} async_memcpy_impl_t;

/**
 * @brief ISR回调函数，当RX完成事件触发时调用
 *
 * @param impl 异步mcp实现层上下文指针
 */
void async_memcpy_isr_on_rx_done_event(async_memcpy_impl_t *impl);

/**
 * @brief 初始化异步mcp实现层
 *
 * @param impl 异步mcp实现层上下文指针
 * @return 始终返回ESP_OK
 */
esp_err_t async_memcpy_impl_init(async_memcpy_impl_t *impl);

/**
 * @brief 取消初始化异步mcp实现层
 *
 * @param impl 异步mcp实现层上下文指针
 * @return 始终返回ESP_OK
 */
esp_err_t async_memcpy_impl_deinit(async_memcpy_impl_t *impl);

/**
 * @brief 启动异步mcp（在实现层上）
 *
 * @param impl 异步mcp实现层上下文指针
 * @param outlink_base TX DMA信道的基本描述符地址
 * @param inlink_base RX DMA信道的基本描述符地址
 * @return 始终返回ESP_OK
 */
esp_err_t async_memcpy_impl_start(async_memcpy_impl_t *impl, intptr_t outlink_base, intptr_t inlink_base);

/**
 * @brief 停止异步mcp（在实现层上）
 *
 * @param impl 异步mcp实现层上下文指针
 * @return 始终返回ESP_OK
 */
esp_err_t async_memcpy_impl_stop(async_memcpy_impl_t *impl);

/**
 * @brief 重新启动异步mcp DMA引擎
 *
 * @param impl 异步mcp实现层上下文指针
 * @return 始终返回ESP_OK
 */
esp_err_t async_memcpy_impl_restart(async_memcpy_impl_t *impl);

/**
 * @brief 检查缓冲区地址是否有效
 * @note 这与底层目标有关（例如，在esp32-s2上，仅支持位于SRAM中的缓冲区）
 *
 * @param impl 异步mcp实现层上下文指针
 * @param src 源缓冲区地址
 * @param dst 目标缓冲区地址
 * @return 如果两个地址都有效，则为True
 */
bool async_memcpy_impl_is_buffer_address_valid(async_memcpy_impl_t *impl, void *src, void *dst);

#ifdef __cplusplus
}
#endif

