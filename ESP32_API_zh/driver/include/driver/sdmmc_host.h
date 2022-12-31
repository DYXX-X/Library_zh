/*
 * SPDX文件版权文本：2015-2021浓缩咖啡系统（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */

#pragma once

#include "soc/soc_caps.h"
#if SOC_SDMMC_HOST_SUPPORTED

#include <stdint.h>
#include <stddef.h>
#include "esp_err.h"
#include "sdmmc_types.h"
#include "driver/gpio.h"

#ifdef __cplusplus
extern "C" {
#endif

#define SDMMC_HOST_SLOT_0     0     ///<SDMMC插槽0
#define SDMMC_HOST_SLOT_1     1     ///<SDMMC插槽1

/**
 * @brief sdmmc外围设备的默认sdmmc_host_t结构初始值设定项
 *
 * 使用SDMMC外围设备，启用4位模式，最大频率设置为20MHz
 */
#define SDMMC_HOST_DEFAULT() {\
    .flags = SDMMC_HOST_FLAG_8BIT | \
             SDMMC_HOST_FLAG_4BIT | \
             SDMMC_HOST_FLAG_1BIT | \
             SDMMC_HOST_FLAG_DDR, \
    .slot = SDMMC_HOST_SLOT_1, \
    .max_freq_khz = SDMMC_FREQ_DEFAULT, \
    .io_voltage = 3.3f, \
    .init = &sdmmc_host_init, \
    .set_bus_width = &sdmmc_host_set_bus_width, \
    .get_bus_width = &sdmmc_host_get_slot_width, \
    .set_bus_ddr_mode = &sdmmc_host_set_bus_ddr_mode, \
    .set_card_clk = &sdmmc_host_set_card_clk, \
    .do_transaction = &sdmmc_host_do_transaction, \
    .deinit = &sdmmc_host_deinit, \
    .io_int_enable = sdmmc_host_io_int_enable, \
    .io_int_wait = sdmmc_host_io_int_wait, \
    .command_timeout_ms = 0, \
}

/**
 * SDMMC外围插槽的额外配置
 */
typedef struct {
#ifdef SOC_SDMMC_USE_GPIO_MATRIX
    gpio_num_t clk;         ///<CLK信号的GPIO编号。
    gpio_num_t cmd;         ///<CMD信号的GPIO编号。
    gpio_num_t d0;          ///<D0信号的GPIO编号。
    gpio_num_t d1;          ///<D1信号的GPIO数量。
    gpio_num_t d2;          ///<D2信号的GPIO数量。
    gpio_num_t d3;          ///<D3信号的GPIO数量。
    gpio_num_t d4;          ///<D4信号的GPIO数量。在1行或4行模式中忽略。
    gpio_num_t d5;          ///<D5信号的GPIO编号。在1行或4行模式中忽略。
    gpio_num_t d6;          ///<D6信号的GPIO编号。在1行或4行模式中忽略。
    gpio_num_t d7;          ///<D7信号的GPIO编号。在1行或4行模式中忽略。
#endif // SOC_SDMMC_USE_GPIO_MATRIX
    union {
        gpio_num_t gpio_cd;     ///<卡检测信号的GPIO数量
        gpio_num_t cd;          ///<卡检测信号的GPIO数量；简称。
    };
    union {
        gpio_num_t gpio_wp;     ///<写保护信号的GPIO数量
        gpio_num_t wp;          ///<写保护信号的GPIO数量；简称。
    };
    uint8_t width;          ///<插槽使用的总线宽度（可能小于支持的最大宽度）
    uint32_t flags;         ///<此插槽使用的功能
#define SDMMC_SLOT_FLAG_INTERNAL_PULLUP  BIT(0)
        /**< 在启用的引脚上启用内部上拉。但是，内部上拉不足，请确保总线上连接了外部上拉。这仅用于调试/示例目的。
         */
} sdmmc_slot_config_t;

#define SDMMC_SLOT_NO_CD      GPIO_NUM_NC     ///<表示未使用卡检测线
#define SDMMC_SLOT_NO_WP      GPIO_NUM_NC     ///<表示未使用写保护线
#define SDMMC_SLOT_WIDTH_DEFAULT 0 ///<使用插槽的最大可能宽度

#ifdef SOC_SDMMC_USE_GPIO_MATRIX

/**
 * 宏定义SDMMC主机插槽的默认配置
 */
#define SDMMC_SLOT_CONFIG_DEFAULT() {\
    .clk = GPIO_NUM_14, \
    .cmd = GPIO_NUM_15, \
    .d0 = GPIO_NUM_2, \
    .d1 = GPIO_NUM_4, \
    .d2 = GPIO_NUM_12, \
    .d3 = GPIO_NUM_13, \
    .d4 = GPIO_NUM_33, \
    .d5 = GPIO_NUM_34, \
    .d6 = GPIO_NUM_35, \
    .d7 = GPIO_NUM_36, \
    .cd = SDMMC_SLOT_NO_CD, \
    .wp = SDMMC_SLOT_NO_WP, \
    .width   = SDMMC_SLOT_WIDTH_DEFAULT, \
    .flags = 0, \
}

#else // SOC_SDMMC_USE_GPIO_MATRIX

/**
 * 宏定义SDMMC主机插槽的默认配置
 */
#define SDMMC_SLOT_CONFIG_DEFAULT() {\
    .cd = SDMMC_SLOT_NO_CD, \
    .wp = SDMMC_SLOT_NO_WP, \
    .width   = SDMMC_SLOT_WIDTH_DEFAULT, \
    .flags = 0, \
}

#endif // SOC_SDMMC_USE_GPIO_MATRIX

/**
 * @brief 初始化SDMMC主机外围设备
 *
 * @note 此函数不是线程安全的
 *
 * @return
 *      -成功时ESP_OK
 *      -如果已调用sdmmc_host_init，则为ESP_ERR_INVALID_STATE
 *      -如果无法分配内存，则为ESP_ERR_NO_MEM
 */
esp_err_t sdmmc_host_init(void);

/**
 * @brief 初始化SDMMC外设的给定插槽
 *
 * 在ESP32上，SDMMC外设有两个插槽：
 *  -插槽0:8位宽，映射到PIN MUX中的HS1_*信号
 *  -插槽1:4位宽，映射到PIN MUX中的HS2_*信号
 *
 * 卡检测和写保护信号可以使用GPIO矩阵路由到任意GPIO。
 *
 * @note 此函数不是线程安全的
 *
 * @param slot  插槽编号（SDMMC_HOST_slot_0或SDMMC_HOME_slot_1）
 * @param slot_config  插槽的附加配置
 * @return
 *      -成功时ESP_OK
 *      -如果尚未使用sdmmc_host_init初始化主机，则为ESP_ERR_INVALID_STATE
 */
esp_err_t sdmmc_host_init_slot(int slot, const sdmmc_slot_config_t* slot_config);

/**
 * @brief 选择用于数据传输的总线宽度
 *
 * SD/MMC卡必须在该命令之前初始化，并且必须向卡发送设置总线宽度的命令（例如SD_APP_set_bus_width）
 *
 * @note 此函数不是线程安全的
 *
 * @param slot  插槽编号（SDMMC_HOST_slot_0或SDMMC_HOME_slot_1）
 * @param width  总线宽度（插槽0为1、4或8；插槽1为1或4）
 * @return
 *      -成功时ESP_OK
 *      -如果插槽编号或宽度无效，则为ESP_ERR_INVALID_ARG
 */
esp_err_t sdmmc_host_set_bus_width(int slot, size_t width);

/**
 * @brief 获取在``sdmmc_host_init_slot``中配置的用于数据传输的总线宽度
 *
 * @param slot  插槽编号（SDMMC_HOST_slot_0或SDMMC_HOME_slot_1）
 * @return 指定插槽的配置总线宽度。
 */
size_t sdmmc_host_get_slot_width(int slot);

/**
 * @brief 设置卡时钟频率
 *
 * 目前只能使用40MHz时钟的整数部分。对于高速卡，可以使用40MHz。对于默认速度卡，可以使用20MHz。
 *
 * @note 此函数不是线程安全的
 *
 * @param slot  插槽编号（SDMMC_HOST_slot_0或SDMMC_HOME_slot_1）
 * @param freq_khz  卡时钟频率，kHz
 * @return
 *      -成功时ESP_OK
 *      -将来可能会返回其他错误代码
 */
esp_err_t sdmmc_host_set_card_clk(int slot, uint32_t freq_khz);

/**
 * @brief 启用或禁用SD接口的DDR模式
 * @param slot  插槽编号（SDMMC_HOST_slot_0或SDMMC_HOME_slot_1）
 * @param ddr_enabled  启用或禁用DDR模式
 * @return
 *      -成功时ESP_OK
 *      -如果此插槽不支持DDR模式，则为ESP_ERR_NOT_SUPPORTED
 */
esp_err_t sdmmc_host_set_bus_ddr_mode(int slot, bool ddr_enabled);

/**
 * @brief 向卡发送命令并获得响应
 *
 * 当发送命令并收到响应、传输数据或发生超时时，此函数将返回。
 *
 * @note 此函数与r.t.init/deinit函数和总线宽度/时钟速度配置函数不具有线程安全性。只要不调用其他sdmmc_host_函数，多个任务就可以调用sdmmc_host_do_transaction。
 *
 * @attention cmdinfo中传递的数据缓冲区->数据必须在支持DMA的内存中
 *
 * @param slot  插槽编号（SDMMC_HOST_slot_0或SDMMC_HOME_slot_1）
 * @param cmdinfo   指向描述要传输的命令和数据的结构的指针
 * @return
 *      -成功时ESP_OK
 *      -如果响应或数据传输超时，则返回ESP_ERR_TIMEOUT
 *      -如果响应或数据传输CRC检查失败，则为ESP_ERR_INVALID_CRC
 *      -如果卡发送了无效响应，则ESP_ERR_INVALID_RESPONSE
 *      -如果数据传输大小在SD协议中无效，则为ESP_ERR_INVALID_SIZE
 *      -如果数据缓冲区不在支持DMA的内存中，则为ESP_ERR_INVALID_ARG
 */
esp_err_t sdmmc_host_do_transaction(int slot, sdmmc_command_t* cmdinfo);

/**
 * @brief 启用IO中断
 *
 * 此函数配置主机以接受SDIO中断。
 *
 * @param slot  插槽编号（SDMMC_HOST_slot_0或SDMMC_HOME_slot_1）
 * @return 返回ESP_OK，以后可能出现其他错误
 */
esp_err_t sdmmc_host_io_int_enable(int slot);

/**
 * @brief 阻止，直到收到SDIO中断或发生超时
 * @param slot  插槽编号（SDMMC_HOST_slot_0或SDMMC_HOME_slot_1）
 * @param timeout_ticks  等待中断的RTOS节拍数
 * @return
 *  -成功时ESP_OK（收到中断）
 *  -如果中断未在TIMEOUT_ticks内发生，则为ESP_ERR_TIMEOUT
 */
esp_err_t sdmmc_host_io_int_wait(int slot, TickType_t timeout_ticks);

/**
 * @brief 禁用SDMMC主机并释放分配的资源
 *
 * @note 此函数不是线程安全的
 *
 * @return
 *      -成功时ESP_OK
 *      -如果尚未调用sdmmc_host_init函数，则为ESP_ERR_INVALID_STATE
 */
esp_err_t sdmmc_host_deinit(void);

/**
 * @brief 启用sd引脚的上拉。
 *
 * 此函数已弃用。请改为在SDMMC_SLOT_config_t:：flags中设置SDMMC_SLOT_FLAG_INTERNAL_PULLUP标志。
 *
 * @note 您应该始终在线条上放置实际的引体向上，而不是使用此函数。内部上拉阻力高且不充分，可能导致产品不稳定。这仅用于调试或示例。
 *
 * @param slot 要使用的插槽，通常设置为1。
 * @param width 配置的位宽，1或4。
 *
 * @return
 *      -ESP_OK：如果成功
 *      -ESP_ERR_INVALID_ARG：如果配置的宽度大于插槽可以支持的最大值
 */
esp_err_t sdmmc_host_pullup_en(int slot, int width) __attribute__((deprecated));

#ifdef __cplusplus
}
#endif

#endif //SOC_SDMMC_HOST_SUPPORTED

