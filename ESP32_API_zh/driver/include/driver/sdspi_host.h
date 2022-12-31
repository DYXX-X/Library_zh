/*
 * SPDX文件版权文本：2015-2021浓缩咖啡系统（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */

#pragma once

#include <stdint.h>
#include <stddef.h>
#include "esp_err.h"
#include "sdmmc_types.h"
#include "driver/gpio.h"
#include "driver/spi_master.h"

#ifdef __cplusplus
extern "C" {
#endif

///表示SD SPI设备的句柄
typedef int sdspi_dev_handle_t;

#if CONFIG_IDF_TARGET_ESP32 || CONFIG_IDF_TARGET_ESP32S2
#define SDSPI_DEFAULT_HOST HSPI_HOST
#else
#define SDSPI_DEFAULT_HOST SPI2_HOST
#endif

/**
 * @brief SD over SPI驱动程序的默认sdmmc_host_t结构初始值设定项
 *
 * 使用SPI模式，最大频率设置为20MHz
 *
 * “slot”应设置为由“sdspi_host_init_device（）”初始化的sdspi设备。
 */
#define SDSPI_HOST_DEFAULT() {\
    .flags = SDMMC_HOST_FLAG_SPI | SDMMC_HOST_FLAG_DEINIT_ARG, \
    .slot = SDSPI_DEFAULT_HOST, \
    .max_freq_khz = SDMMC_FREQ_DEFAULT, \
    .io_voltage = 3.3f, \
    .init = &sdspi_host_init, \
    .set_bus_width = NULL, \
    .get_bus_width = NULL, \
    .set_bus_ddr_mode = NULL, \
    .set_card_clk = &sdspi_host_set_card_clk, \
    .do_transaction = &sdspi_host_do_transaction, \
    .deinit_p = &sdspi_host_remove_device, \
    .io_int_enable = &sdspi_host_io_int_enable, \
    .io_int_wait = &sdspi_host_io_int_wait, \
    .command_timeout_ms = 0, \
}

/**
 * SD SPI设备的额外配置。
 */
typedef struct {
    spi_host_device_t host_id; ///<要使用的SPI主机，SPIx_host（请参见SPI_types.h）。
    gpio_num_t gpio_cs;     ///<CS信号的GPIO编号
    gpio_num_t gpio_cd;     ///<卡检测信号的GPIO数量
    gpio_num_t gpio_wp;     ///<写保护信号的GPIO数量
    gpio_num_t gpio_int;    ///<SDIO卡中断线（输入）的GPIO编号。
} sdspi_device_config_t;

#define SDSPI_SLOT_NO_CD    GPIO_NUM_NC ///<表示未使用卡检测线
#define SDSPI_SLOT_NO_WP    GPIO_NUM_NC ///<表示未使用写保护线
#define SDSPI_SLOT_NO_INT   GPIO_NUM_NC ///<表示未使用中断线

/**
 * 定义SD SPI设备默认配置的宏。
 */
#define SDSPI_DEVICE_CONFIG_DEFAULT() {\
    .host_id   = SDSPI_DEFAULT_HOST, \
    .gpio_cs   = GPIO_NUM_13, \
    .gpio_cd   = SDSPI_SLOT_NO_CD, \
    .gpio_wp   = SDSPI_SLOT_NO_WP, \
    .gpio_int  = GPIO_NUM_NC, \
}

/**
 * @brief 初始化SD SPI驱动程序
 *
 * @note 此函数不是线程安全的
 *
 * @return
 *      -成功时ESP_OK
 *      -在将来的版本中可能会返回其他错误代码
 */
esp_err_t sdspi_host_init(void);

/**
* @brief 在特定SPI总线上连接并初始化SD SPI设备
*
* @note 此函数不是线程安全的
*
* @note 在调用此函数之前，通过“SPI_bus_Initialize（）”初始化SPI总线。
*
* @note sdspi上的SDIO需要一条额外的中断线。在此函数之前调用``gpio_install_isr_service（）``。
*
* @param dev_config 指向设备配置结构的指针
* @param out_handle 将句柄输出到sdspi设备。

* @return
*      -成功时ESP_OK
*      -如果sdspi_host_init_device具有无效参数，则ESP_ERR_INVALID_ARG
*      -如果无法分配内存，则为ESP_ERR_NO_MEM
*      -来自底层spimaster和gpio驱动程序的其他错误
*/
esp_err_t sdspi_host_init_device(const sdspi_device_config_t* dev_config, sdspi_dev_handle_t* out_handle);

/**
 * @brief 卸下SD SPI设备
 *
 * @param handle SD SPI设备的手柄
 * @return 始终ESP_OK
 */
esp_err_t sdspi_host_remove_device(sdspi_dev_handle_t handle);

/**
 * @brief 向卡发送命令并获得响应
 *
 * 当发送命令并收到响应、传输数据或发生超时时，此函数将返回。
 *
 * @note 此函数与r.t.init/deinit函数和总线宽度/时钟速度配置函数不具有线程安全性。只要不调用其他sdspi_host_函数，多个任务就可以调用sdspi_host _do_transaction。
 *
 * @param handle    sdspi设备的手柄
 * @param cmdinfo   指向描述要传输的命令和数据的结构的指针
 * @return
 *      -成功时ESP_OK
 *      -如果响应或数据传输超时，则返回ESP_ERR_TIMEOUT
 *      -如果响应或数据传输CRC检查失败，则为ESP_ERR_INVALID_CRC
 *      -如果卡发送了无效响应，则ESP_ERR_INVALID_RESPONSE
 */
esp_err_t sdspi_host_do_transaction(sdspi_dev_handle_t handle, sdmmc_command_t *cmdinfo);

/**
 * @brief 设置卡时钟频率
 *
 * 目前只能使用40MHz时钟的整数部分。对于高速卡，可以使用40MHz。对于默认速度卡，可以使用20MHz。
 *
 * @note 此函数不是线程安全的
 *
 * @param host    sdspi设备的手柄
 * @param freq_khz  卡时钟频率，kHz
 * @return
 *      -成功时ESP_OK
 *      -将来可能会返回其他错误代码
 */
esp_err_t sdspi_host_set_card_clk(sdspi_dev_handle_t host, uint32_t freq_khz);

/**
 * @brief 释放使用sdspi_host_init分配的资源
 *
 * @note 此函数不是线程安全的
 *
 * @return
 *      -成功时ESP_OK
 *      -如果尚未调用sdspi_host_init函数，则为ESP_ERR_INVALID_STATE
 */
esp_err_t sdspi_host_deinit(void);

/**
 * @brief 启用SDIO中断。
 *
 * @param handle    sdspi设备的手柄
 *
 * @return
 *      -成功时ESP_OK
 */
esp_err_t sdspi_host_io_int_enable(sdspi_dev_handle_t handle);

/**
 * @brief 等待SDIO中断直到超时。
 *
 * @param handle    sdspi设备的手柄
 * @param timeout_ticks 在超时前等待。
 *
 * @return
 *      -成功时ESP_OK
 */
esp_err_t sdspi_host_io_int_wait(sdspi_dev_handle_t handle, TickType_t timeout_ticks);

/*******************************************************************************
 * 不推荐的API
 ******************************************************************************/

/**
 * SPI主机的额外配置。
 *
 * @deprecated 请改用“sdspi_device_config_t”和相应的“sdspi_host_init_device（）”。
 */
typedef struct {
    gpio_num_t gpio_cs;     ///<CS信号的GPIO编号
    gpio_num_t gpio_cd;     ///<卡检测信号的GPIO数量
    gpio_num_t gpio_wp;     ///<写保护信号的GPIO数量
    gpio_num_t gpio_int;    ///<SDIO卡中断线（输入）的GPIO编号。
    gpio_num_t gpio_miso;   ///<MISO信号的GPIO数量。
    gpio_num_t gpio_mosi;   ///<MOSI信号的GPIO数量。
    gpio_num_t gpio_sck;    ///<SCK信号的GPIO编号。
    int        dma_channel;        ///<SPI驱动程序使用的DMA通道（1或2）。
} sdspi_slot_config_t;

/**
 * 定义SPI主机默认配置的宏
 */
#define SDSPI_SLOT_CONFIG_DEFAULT() {\
    .gpio_cs   = GPIO_NUM_13, \
    .gpio_cd   = SDSPI_SLOT_NO_CD, \
    .gpio_wp   = SDSPI_SLOT_NO_WP, \
    .gpio_int  = GPIO_NUM_NC, \
    .gpio_miso = GPIO_NUM_2, \
    .gpio_mosi = GPIO_NUM_15, \
    .gpio_sck  = GPIO_NUM_14, \
    .dma_channel = 1, \
}

/**
* @brief 初始化特定SPI控制器的SD SPI驱动程序
*
* @note 此函数不是线程安全的
*
* @note sdspi上的SDIO需要一条额外的中断线。在此函数之前调用``gpio_install_isr_service（）``。
*
* @param slot         要使用的SPI控制器（SPI2_HOST或SPI3_HOST）
* @param slot_config  指向插槽配置结构的指针

* @deprecated 请改用“sdspi_host_init_device”。
*
* @return
*      -成功时ESP_OK
*      -如果sdspi_init_slot具有无效参数，则ESP_ERR_INVALID_ARG
*      -如果无法分配内存，则为ESP_ERR_NO_MEM
*      -来自底层spimaster和gpio驱动程序的其他错误
*/
esp_err_t sdspi_host_init_slot(int slot, const sdspi_slot_config_t* slot_config);

#ifdef __cplusplus
}
#endif

