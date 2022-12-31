// 版权所有2015-2019 Espressif Systems（上海）私人有限公司
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
 * 注意：hal不是公共api，不要在应用程序代码中使用。请参阅自述文件。在hal/include/hal/readme.md中的md
 ******************************************************************************/

// SPI主机的HAL层（公共部分）

// SPI HAL用法：
// 1.初始化总线
// 2.如果使用DMA，初始化DMA描述符
// 3.设置时钟速度（因为这需要很长时间）
// 4.调用setup_device更新特定设备的参数
// 5.调用setup_trans更新特定事务的参数
// 6.准备要发送的数据，并准备接收缓冲区
// 7.触发用户定义的SPI事务以启动
// 8.等待用户事务完成
// 9.获取接收到的数据
// 仅在“setup_device”期间更新的参数将在
// 字段注释。

#pragma once
#include "hal/spi_ll.h"
#include <esp_err.h>
#include "soc/lldesc.h"
#include "soc/soc_caps.h"
#include "hal/spi_types.h"

/**
 * 向“spi_hal_cal_clock_conf”输入参数以计算定时配置
 */
typedef struct {
    uint32_t half_duplex;               ///<是否使用半双工模式，设备特定
    uint32_t no_compensate;             ///<无需添加虚拟来补偿定时，设备特定
    uint32_t clock_speed_hz;            ///<所需频率。
    uint32_t duty_cycle;                ///<SPI时钟的期望占空比
    uint32_t input_delay_ns;            /**< SPI启动时钟与有效数据之间的最大延迟。这用于补偿/计算允许的最大频率。如果未知，则保留0。
                                         */
    bool use_gpio;                      ///<如果使用GPIO矩阵，则为True，否则为false
} spi_hal_timing_param_t;

/**
 * 应在初始化和保持时由“spi_hal_cal_clock_conf”计算的定时配置结构。在设置设备之前，填充到HAL上下文的“timing_conf”成员中。
 */
typedef struct {
    spi_ll_clock_val_t clock_reg;       ///<LL层使用的寄存器值
    int timing_dummy;                   ///<需要额外的假人来补偿计时
    int timing_miso_delay;              ///<额外的miso延迟时钟以补偿定时
} spi_hal_timing_conf_t;

/**
 * DMA配置结构应在初始化时由驱动程序设置
 */
typedef struct {
    spi_dma_dev_t *dma_in;              ///<输入DMA（DMA->RAM）外围寄存器地址
    spi_dma_dev_t *dma_out;             ///<输出DMA（RAM->DMA）外围寄存器地址
    bool dma_enabled;                   ///<是否启用DMA，初始化后不更新
    lldesc_t  *dmadesc_tx;              /**< TX DMA使用的DMA描述符数组。金额应大于dmadesc_n。驱动程序应确保要发送的数据比描述符所能容纳的数据短。
                                         */
    lldesc_t *dmadesc_rx;               /**< RX DMA使用的DMA描述符数组。金额应大于dmadesc_n。驱动程序应确保要发送的数据比描述符所能容纳的数据短。
                                         */
    uint32_t tx_dma_chan;               ///<TX DMA信道
    uint32_t rx_dma_chan;               ///<RX DMA信道
    int dmadesc_n;                      ///<HAL可以使用的“dmadesc_tx”和“dmadesc_rx”描述符的数量。
} spi_hal_config_t;

/**
 * 事务配置结构，每次都应由驱动程序分配。所有这些参数将在每次事务中更新到外围设备。
 */
typedef struct {
    uint16_t cmd;                       ///<要发送的命令值
    int cmd_bits;                       ///<命令阶段的长度（位）
    int addr_bits;                      ///<地址阶段的长度（位）
    int dummy_bits;                     ///<伪相位的基本长度（以位为单位）。注意，当启用补偿时，可能会附加一些额外的虚位。
    int tx_bitlen;                      ///<TX长度，以位为单位
    int rx_bitlen;                      ///<RX长度，以位为单位
    uint64_t addr;                      ///<要发送的地址值
    uint8_t *send_buffer;               ///<要发送的数据
    uint8_t *rcv_buffer;                ///<保存接收数据的缓冲区。
    spi_line_mode_t line_mode;          ///<此事务的SPI线模式
    int cs_keep_active;                 ///<交易后保持CS活动
} spi_hal_trans_config_t;

/**
 * 驱动程序和HAL都应维护的上下文。
 */
typedef struct {
    /* 这两个需要首先由驱动程序分配*/
    lldesc_t  *dmadesc_tx;              /**< TX DMA使用的DMA描述符数组。金额应大于dmadesc_n。驱动程序应确保要发送的数据比描述符所能容纳的数据短。
                                         */
    lldesc_t *dmadesc_rx;               /**< RX DMA使用的DMA描述符数组。金额应大于dmadesc_n。驱动程序应确保要发送的数据比描述符所能容纳的数据短。
                                         */

    /* 初始化时由驱动程序配置，请勿触摸*/
    spi_dev_t     *hw;                  ///<外围寄存器的起始地址。
    spi_dma_dev_t *dma_in;              ///<将从外设接收的数据存储到RAM（DMA->RAM）中的DMA外设寄存器的地址。
    spi_dma_dev_t *dma_out;             ///<将数据从RAM传输到外设（RAM->DMA）的DMA外设寄存器的地址。
    bool  dma_enabled;                  ///<是否启用DMA，初始化后不更新
    uint32_t tx_dma_chan;               ///<TX DMA信道
    uint32_t rx_dma_chan;               ///<RX DMA信道
    int dmadesc_n;                      ///<HAL可以使用的“dmadesc_tx”和“dmadesc_rx”描述符的数量。

    /* 内部参数，请勿触摸*/
    spi_hal_trans_config_t trans_config; ///<事务配置
} spi_hal_context_t;

/**
 * 设备配置结构，应由驱动程序根据不同设备分别初始化。只有当“spi_hal_setup_device”时，所有这些参数才会更新到外围设备。当“spi_hal_setup_trans”时，它们可能不会更新。
 */
typedef struct {
    int mode;                           ///<SPI模式，设备特定
    int cs_setup;                       ///<第一个SPI时钟之前CS活动边缘的设置时间，设备特定
    int cs_hold;                        ///<最后一个SPI时钟后CS非活动边缘的保持时间，设备特定
    int cs_pin_id;                      ///<要使用的CS引脚，0-2，否则不使用所有CS引脚。特定于设备
    spi_hal_timing_conf_t timing_conf;  /**< 此结构保存初始化时设备的预先计算的定时配置，具体取决于设备
                                         */
    struct {
        uint32_t sio : 1;               ///<是否使用SIO模式，设备特定
        uint32_t half_duplex : 1;       ///<是否使用半双工模式，设备特定
        uint32_t tx_lsbfirst : 1;       ///<是否首先发送发送数据的LSB，设备特定
        uint32_t rx_lsbfirst : 1;       ///<是否首先接收接收数据的LSB，设备特定
        uint32_t no_compensate : 1;     ///<无需添加虚拟来补偿定时，设备特定
#if SOC_SPI_SUPPORT_AS_CS
        uint32_t as_cs  : 1;            ///<是否在时钟切换时切换CS，设备特定
#endif
        uint32_t positive_cs : 1;       ///<是否启用正CS功能，设备特定
    };//布尔配置
} spi_hal_dev_config_t;

/**
 * 初始化外围设备和上下文。
 *
 * @param hal        HAL层的上下文。
 * @param host_id    SPI外围设备的索引。SPI1为0，SPI2为1，SPI3为2。
 * @param hal_config 上层定义的hal配置。
 */
void spi_hal_init(spi_hal_context_t *hal, uint32_t host_id, const spi_hal_config_t *hal_config);

/**
 * 取消外围设备（如果需要，还可以取消上下文）。
 *
 * @param hal HAL层的上下文。
 */
void spi_hal_deinit(spi_hal_context_t *hal);

/**
 * 根据上下文中的设置设置与设备相关的配置。
 *
 * @param hal       HAL层的上下文。
 * @param hal_dev   设备配置
 */
void spi_hal_setup_device(spi_hal_context_t *hal, const spi_hal_dev_config_t *hal_dev);

/**
 * 根据上下文中的设置设置与事务相关的配置。
 *
 * @param hal       HAL层的上下文。
 * @param hal_dev   设备配置
 * @param hal_trans 事务处理配置
 */
void spi_hal_setup_trans(spi_hal_context_t *hal, const spi_hal_dev_config_t *hal_dev, const spi_hal_trans_config_t *hal_trans);

/**
 * 准备当前事务的数据。
 *
 * @param hal            HAL层的上下文。
 * @param hal_dev        设备配置
 * @param hal_trans      事务处理配置
 */
void spi_hal_prepare_data(spi_hal_context_t *hal, const spi_hal_dev_config_t *hal_dev, const spi_hal_trans_config_t *hal_trans);

/**
 * 触发器启动用户定义的事务。
 *
 * @param hal HAL层的上下文。
 */
void spi_hal_user_start(const spi_hal_context_t *hal);

/**
 * 检查事务是否完成（trans_done已设置）。
 *
 * @param hal HAL层的上下文。
 */
bool spi_hal_usr_is_done(const spi_hal_context_t *hal);

/**
 * 事务后操作，主要是从缓冲区获取数据。
 *
 * @param hal       HAL层的上下文。
 */
void spi_hal_fetch_result(const spi_hal_context_t *hal);

/*----------------------------------------------------------
 * Utils公司
 * ---------------------------------------------------------*/
/**
 * 计算时钟和定时的配置。当“spi_hal_setup_device”时将使用该配置。
 *
 * 强烈建议在初始化时执行此操作，因为这需要很长时间。
 *
 * @param timing_param   输入参数以计算定时配置
 * @param out_freq       实际频率的输出，如果不需要，则保留NULL。
 * @param timing_conf    定时配置的输出。
 *
 * @return 如果需要，ESP_OK可用，否则失败。
 */
esp_err_t spi_hal_cal_clock_conf(const spi_hal_timing_param_t *timing_param, int *out_freq, spi_hal_timing_conf_t *timing_conf);

/**
 * 获取实际使用的频率。
 *
 * @param hal            HAL层的上下文。
 * @param fapb           APB时钟频率。
 * @param hz             所需频率c。
 * @param duty_cycle     所需占空比。
 */
int spi_hal_master_cal_clock(int fapb, int hz, int duty_cycle);

/**
 * 获取给定参数的定时配置。
 *
 * @param eff_clk        实际SPI时钟频率
 * @param gpio_is_used   如果使用GPIO矩阵，则为true，否则为false。
 * @param input_delay_ns SPI启动时钟与有效数据之间的最大延迟。这用于补偿/计算允许的最大频率。如果未知，则保留0。
 * @param dummy_n        正确读取数据所需的虚拟循环。
 * @param miso_delay_n   MISO线路上的建议延迟（APB时钟）。
 */
void spi_hal_cal_timing(int eff_clk, bool gpio_is_used, int input_delay_ns, int *dummy_n, int *miso_delay_n);

/**
 * 如果不使用补偿，则获取允许读取的最大频率。
 *
 * @param gpio_is_used   如果使用GPIO矩阵，则为true，否则为false。
 * @param input_delay_ns SPI启动时钟与有效数据之间的最大延迟。这用于补偿/计算允许的最大频率。如果未知，则保留0。
 */
int spi_hal_get_freq_limit(bool gpio_is_used, int input_delay_ns);

