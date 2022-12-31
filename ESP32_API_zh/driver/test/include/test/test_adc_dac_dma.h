/*
 * SPDX文件版权文本：2015-2021浓缩咖啡系统（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */

#pragma once

/* ESP32-S2 ADC/DAC测试的公共头*/

/**
 * SPI DMA类型。
 */
typedef enum {
    DMA_ONLY_ADC_INLINK = BIT(1),   /*!<选择ADC-DMA配置。*/
    DMA_ONLY_DAC_OUTLINK = BIT(2),  /*!<选择DAC-DMA配置。*/
    DMA_BOTH_ADC_DAC,               /*!<选择DAC-DMA和ADC-DMA配置。*/
#define DMA_BOTH_ADC_DAC (DMA_ONLY_ADC_INLINK | DMA_ONLY_DAC_OUTLINK)
} spi_dma_link_type_t;

/**
 * 注册SPI-DMA中断处理程序。
 *
 * @param handler       处理程序。
 * @param handler_arg   处理程序参数。
 * @param intr_mask     DMA中断类型掩码。
 */
esp_err_t adc_dac_dma_isr_register(intr_handler_t handler, void* handler_arg, uint32_t intr_mask);

/**
 * 取消注册SPI-DMA中断处理程序。
 *
 * @param handler       处理程序。
 * @param handler_arg   处理程序参数。
 */
esp_err_t adc_dac_dma_isr_deregister(intr_handler_t handler, void* handler_arg);

/**
 * 重置DMA链接器指针并启动DMA。
 *
 * @param type     DMA链接器类型。请参见``spi_dma_link_type_t``。
 * @param dma_addr DMA链接器地址。
 * @param int_msk  DMA中断类型掩码。
 */
void adc_dac_dma_linker_start(spi_dma_link_type_t type, void *dma_addr, uint32_t int_msk);

/**
 * 停止DMA。
 *
 * @param type DMA链接器类型。请参见``spi_dma_link_type_t``。
 */
void adc_dac_dma_linker_stop(spi_dma_link_type_t type);

/**
 * Denit SPI3 DMA。禁用中断，停止DMA传输。
 */
void adc_dac_dma_linker_deinit(void);

