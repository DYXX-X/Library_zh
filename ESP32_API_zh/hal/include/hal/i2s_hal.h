/*
 * SPDX文件版权文本：2020-2021浓缩咖啡系统（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */

/*******************************************************************************
 * 注意：hal不是公共api，不要在应用程序代码中使用。请参阅自述文件。在hal/include/hal/readme.md中的md
 ******************************************************************************/

// I2S的HAL层。
// hal层中没有参数检查，因此调用者必须确保参数的正确性。

#pragma once

#include "soc/i2s_periph.h"
#include "soc/soc_caps.h"
#include "hal/i2s_types.h"
#include "hal/i2s_ll.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief I2S时钟配置
 */
typedef struct {
    uint32_t sclk;          /*!< I2S模块时钟*/
    uint32_t mclk;          /*!< I2S主时钟*/
    uint32_t bclk;          /*!< I2S位时钟*/
    uint16_t mclk_div;      /*!< I2S主时钟划分*/
    uint16_t bclk_div;      /*!< I2S位时钟划分*/
} i2s_hal_clock_cfg_t;


/**
 * @brief I2S HAL配置
 */
typedef struct {
    i2s_mode_t              mode;                   /*!< I2S工作模式，使用`I2S_mode_t的着色掩码`*/
    uint32_t                sample_rate;            /*!< I2S采样率*/
    i2s_comm_format_t       comm_fmt;               /*!< I2S通信格式*/
    i2s_channel_fmt_t       chan_fmt;               /*!< I2S信道格式，TDM模式下共有16个信道。*/
    uint32_t                sample_bits;            /*!< 一个通道中的I2S采样位*/
    uint32_t                chan_bits;              /*!< 一个通道中的I2S总比特数。不应小于“sample_bits”，默认值“0”表示等于“sample_bit”*/
    uint32_t                active_chan;            /*!< I2S活动通道编号*/
    uint32_t                total_chan;             /*!< I2S通道总数*/

#if SOC_I2S_SUPPORTS_TDM
    uint32_t                chan_mask;              /*!< 活动通道位掩码，在“i2s_channel_t”中设置值以启用特定通道，活动通道的位图不能超过（0x1<<total_chan_num）。*/
    bool                    left_align;             /*!< 设置为启用左对齐*/
    bool                    big_edin;               /*!< 设置为启用big edin*/
    bool                    bit_order_msb;          /*!< 设置为启用msb顺序*/
    bool                    skip_msk;               /*!< 设置为启用跳过掩码。如果已启用，则仅发送已启用信道的数据，否则将发送DMA TX缓冲区中存储的所有数据*/
#endif
} i2s_hal_config_t;

/**
 * 驾驶员和HAL应维护的上下文
 */
typedef struct {
    i2s_dev_t *dev;
    uint32_t version;
} i2s_hal_context_t;

/**
 * @brief 启用I2S模块时钟
 *
 * @param hal HAL层的上下文
 */
#define i2s_hal_enable_module_clock(hal)        i2s_ll_enable_clock((hal)->dev);

/**
 * @brief 禁用I2S模块时钟
 *
 * @param hal HAL层的上下文
 */
#define i2s_hal_disable_module_clock(hal)       i2s_ll_disable_clock((hal)->dev);

/**
 * @brief 重置I2S TX信道
 *
 * @param hal HAL层的上下文
 */
#define i2s_hal_reset_tx(hal)                   i2s_ll_tx_reset((hal)->dev)

/**
 * @brief 重置I2S TX fifo
 *
 * @param hal HAL层的上下文
 */
#define i2s_hal_reset_tx_fifo(hal)              i2s_ll_tx_reset_fifo((hal)->dev)

/**
 * @brief 重置I2S RX信道
 *
 * @param hal HAL层的上下文
 */
#define i2s_hal_reset_rx(hal)                   i2s_ll_rx_reset((hal)->dev)

/**
 * @brief 重置I2S RX fifo
 *
 * @param hal HAL层的上下文
 */
#define i2s_hal_reset_rx_fifo(hal)              i2s_ll_rx_reset_fifo((hal)->dev)

/**
 * @brief 获取I2S硬件实例并启用I2S模块时钟
 * @note  在调用其他hal层函数之前，应先调用此函数
 *
 * @param hal HAL层的上下文
 * @param i2s_num uart端口号，最大端口号为（I2S_NUM_max-1）
 */
void i2s_hal_init(i2s_hal_context_t *hal, int i2s_num);

/**
 * @brief 配置I2S源时钟
 *
 * @param hal HAL层的上下文
 * @param sel 源时钟索引
 */
void i2s_hal_set_clock_src(i2s_hal_context_t *hal, i2s_clock_src_t sel);

/**
 * @brief 设置Tx信道样式
 *
 * @param hal HAL层的上下文
 * @param hal_cfg I2S hal配置结构，参见`I2S_hal_config_t`
 */
void i2s_hal_tx_set_channel_style(i2s_hal_context_t *hal, const i2s_hal_config_t *hal_cfg);

/**
 * @brief 设置Rx通道样式
 *
 * @param hal HAL层的上下文
 * @param hal_cfg I2S hal配置结构，参见`I2S_hal_config_t`
 */
void i2s_hal_rx_set_channel_style(i2s_hal_context_t *hal, const i2s_hal_config_t *hal_cfg);

/**
 * @brief 初始化I2S硬件
 *
 * @param hal HAL层的上下文
 * @param hal_cfg I2S hal配置结构，参见`I2S_hal_config_t`
 */
void i2s_hal_config_param(i2s_hal_context_t *hal, const i2s_hal_config_t *hal_cfg);

/**
 * @brief 启用I2S主全双工模式
 *
 * @param hal HAL层的上下文
 */
void i2s_hal_enable_master_fd_mode(i2s_hal_context_t *hal);

/**
 * @brief 启用I2S从属全双工模式
 *
 * @param hal HAL层的上下文
 */
void i2s_hal_enable_slave_fd_mode(i2s_hal_context_t *hal);

/**
 * @brief 启动I2S tx
 *
 * @param hal HAL层的上下文
 */
void i2s_hal_start_tx(i2s_hal_context_t *hal);

/**
 * @brief 启动I2S rx
 *
 * @param hal HAL层的上下文
 */
void i2s_hal_start_rx(i2s_hal_context_t *hal);

/**
 * @brief 停止I2S tx
 *
 * @param hal HAL层的上下文
 */
void i2s_hal_stop_tx(i2s_hal_context_t *hal);

/**
 * @brief 停止I2S rx
 *
 * @param hal HAL层的上下文
 */
void i2s_hal_stop_rx(i2s_hal_context_t *hal);

/**
 * @brief 将接收的数据长度设置为触发“in_suc_eof”中断。
 *
 * @param hal HAL层的上下文
 * @param eof_byte 触发in_suc_eof中断的字节长度。
 */
#define i2s_hal_set_rx_eof_num(hal, eof_byte)   i2s_ll_rx_set_eof_num((hal)->dev, eof_byte)

/**
 * @brief 设置I2S TX采样位
 *
 * @param hal HAL层的上下文
 * @param chan_bit I2S TX通道位
 * @param data_bit 样本数据位长度。
 */
#define i2s_hal_set_tx_sample_bit(hal, chan_bit, data_bit)  i2s_ll_tx_set_sample_bit((hal)->dev, chan_bit, data_bit)

/**
 * @brief 设置I2S RX采样位
 *
 * @param hal HAL层的上下文
 * @param chan_bit I2S RX通道位
 * @param data_bit 样本数据位长度。
 */
#define i2s_hal_set_rx_sample_bit(hal, chan_bit, data_bit)  i2s_ll_rx_set_sample_bit((hal)->dev, chan_bit, data_bit)

/**
 * @brief 配置I2S TX模块时钟分配器
 *
 * @param hal HAL层的上下文
 * @param clk_cfg I2S时钟配置
 */
void i2s_hal_tx_clock_config(i2s_hal_context_t *hal, i2s_hal_clock_cfg_t *clk_cfg);

/**
 * @brief 配置I2S RX模块时钟分配器
 *
 * @param hal HAL层的上下文
 * @param clk_cfg I2S时钟配置
 */
void i2s_hal_rx_clock_config(i2s_hal_context_t *hal, i2s_hal_clock_cfg_t *clk_cfg);

/**
 * @brief 设置I2S tx时钟源
 *
 * @param hal HAL层的上下文
 * @param clk_src i2s tx时钟源（参见“i2s_clock_src_t”）
 */
#define i2s_hal_tx_set_clock_source(hal, clk_src)   i2s_ll_tx_clk_set_src((hal)->dev, clk_src)

/**
 * @brief 设置I2S rx时钟源
 *
 * @param hal HAL层的上下文
 * @param clk_src i2s rx时钟源（请参见“i2s_clock_src_t”）
 */
#define i2s_hal_rx_set_clock_source(hal, clk_src)   i2s_ll_rx_clk_set_src((hal)->dev, clk_src)

/**
 * @brief 启用I2S tx从属模式
 *
 * @param hal HAL层的上下文
 * @param enable 设置“true”以启用tx从属模式
 */
#define i2s_hal_tx_enable_slave_mode(hal, enable)   i2s_ll_tx_set_slave_mod((hal)->dev, enable)

/**
 * @brief 启用I2S rx从属模式
 *
 * @param hal HAL层的上下文
 * @param enable 设置“true”以启用rx从属模式
 */
#define i2s_hal_rx_enable_slave_mode(hal, enable)   i2s_ll_rx_set_slave_mod((hal)->dev, enable)

/**
 * @brief 启用环回模式
 *
 * @param hal HAL层的上下文
 */
#define i2s_hal_enable_sig_loopback(hal)    i2s_ll_share_bck_ws((hal)->dev, true)

/**
 * @brief 为普通TX模式设置I2S配置
 * @note 通用模式适用于非PDM模式，如philip/MSB/PCM
 *
 * @param hal HAL层的上下文
 * @param hal_cfg hal构型结构
 */
void i2s_hal_tx_set_common_mode(i2s_hal_context_t *hal, const i2s_hal_config_t *hal_cfg);

/**
 * @brief 为普通RX模式设置I2S配置
 * @note 通用模式适用于非PDM模式，如philip/MSB/PCM
 *
 * @param hal HAL层的上下文
 * @param hal_cfg hal构型结构
 */
void i2s_hal_rx_set_common_mode(i2s_hal_context_t *hal, const i2s_hal_config_t *hal_cfg);

#if SOC_I2S_SUPPORTS_PCM
/**
 * @brief 配置I2S TX PCM编码器或解码器。
 *
 * @param hal HAL层的上下文
 * @param cfg PCM配置参数，请参阅`i2s_PCM_compress_t`
 */
#define i2s_hal_tx_pcm_cfg(hal, cfg)        i2s_ll_tx_set_pcm_type((hal)->dev, cfg)

/**
 * @brief 配置I2S RX PCM编码器或解码器。
 *
 * @param hal HAL层的上下文
 * @param cfg PCM配置参数，请参阅`i2s_PCM_compress_t`
 */
#define i2s_hal_rx_pcm_cfg(hal, cfg)        i2s_ll_rx_set_pcm_type((hal)->dev, cfg)
#endif

#if SOC_I2S_SUPPORTS_PDM_TX
/**
 * @brief 配置I2S TX PDM采样率Fpdm=64Fpcmfp/fs
 *
 * @param hal HAL层的上下文
 * @param fp TX PDM fp参数配置
 * @param fs TX PDM fs参数配置
 */
#define i2s_hal_set_tx_pdm_fpfs(hal, fp, fs)    i2s_ll_tx_set_pdm_fpfs((hal)->dev, fp, fs)

/**
 * @brief 获取I2S TX PDM fp
 *
 * @param hal HAL层的上下文
 * @return
 *        -fp配置参数
 */
#define i2s_hal_get_tx_pdm_fp(hal)      i2s_ll_tx_get_pdm_fp((hal)->dev)

/**
 * @brief 获取I2S TX PDM fs
 *
 * @param hal HAL层的上下文
 * @return
 *        -fs配置参数
 */
#define i2s_hal_get_tx_pdm_fs(hal)      i2s_ll_tx_get_pdm_fs((hal)->dev)

/**
 * @brief 为PDM TX模式设置I2S默认配置
 *
 * @param hal HAL层的上下文
 * @param sample_rate PDM采样率
 */
void i2s_hal_tx_set_pdm_mode_default(i2s_hal_context_t *hal, uint32_t sample_rate);
#endif

#if SOC_I2S_SUPPORTS_PDM_RX

/**
 * @brief 配置RX PDM下采样
 *
 * @param hal HAL层的上下文
 * @param dsr PDM下采样配置参数
 */
#define i2s_hal_set_rx_pdm_dsr(hal, dsr)         i2s_ll_rx_set_pdm_dsr((hal)->dev, dsr)

/**
 * @brief 获取RX PDM下采样配置
 *
 * @param hal HAL层的上下文
 * @param dsr 接受PDM下采样配置的指针
 */
#define i2s_hal_get_rx_pdm_dsr(hal, dsr)        i2s_ll_rx_get_pdm_dsr((hal)->dev, dsr)

/**
 * @brief 为PDM R模式设置I2S默认配置
 *
 * @param hal HAL层的上下文
 */
void i2s_hal_rx_set_pdm_mode_default(i2s_hal_context_t *hal);
#endif

#if !SOC_GDMA_SUPPORTED
/**
 * @brief 启用I2S TX DMA
 *
 * @param hal HAL层的上下文
 */
#define i2s_hal_enable_tx_dma(hal) i2s_ll_enable_dma((hal)->dev,true)

/**
 * @brief 启用I2S RX DMA
 *
 * @param hal HAL层的上下文
 */
#define i2s_hal_enable_rx_dma(hal) i2s_ll_enable_dma((hal)->dev,true)

/**
 * @brief 禁用I2S TX DMA
 *
 * @param hal HAL层的上下文
 */
#define i2s_hal_disable_tx_dma(hal) i2s_ll_enable_dma((hal)->dev,false)

/**
 * @brief 禁用I2S RX DMA
 *
 * @param hal HAL层的上下文
 */
#define i2s_hal_disable_rx_dma(hal) i2s_ll_enable_dma((hal)->dev,false)

/**
 * @brief 获取I2S中断状态
 *
 * @param hal HAL层的上下文
 * @return
 *        -模块中断状态
 */
#define i2s_hal_get_intr_status(hal) i2s_ll_get_intr_status((hal)->dev)

/**
 * @brief 获取I2S中断状态
 *
 * @param hal HAL层的上下文
 * @param mask 要清除的中断掩码。
 */
#define i2s_hal_clear_intr_status(hal, mask) i2s_ll_clear_intr_status((hal)->dev, mask)

/**
 * @brief 启用I2S RX中断
 *
 * @param hal HAL层的上下文
 */
#define i2s_hal_enable_rx_intr(hal) i2s_ll_rx_enable_intr((hal)->dev)

/**
 * @brief 禁用I2S RX中断
 *
 * @param hal HAL层的上下文
 */
#define i2s_hal_disable_rx_intr(hal) i2s_ll_rx_disable_intr((hal)->dev)

/**
 * @brief 禁用I2S TX中断
 *
 * @param hal HAL层的上下文
 */
#define i2s_hal_disable_tx_intr(hal) i2s_ll_tx_disable_intr((hal)->dev)

/**
 * @brief 启用I2S TX中断
 *
 * @param hal HAL层的上下文
 */
#define i2s_hal_enable_tx_intr(hal) i2s_ll_tx_enable_intr((hal)->dev)

/**
 * @brief 配置TX DMA描述符地址并启动TX DMA
 *
 * @param hal HAL层的上下文
 * @param link_addr DMA描述符链接地址。
 */
#define i2s_hal_start_tx_link(hal, link_addr) i2s_ll_tx_start_link((hal)->dev, link_addr)

/**
 * @brief 配置RX DMA描述符地址并启动RX DMA
 *
 * @param hal HAL层的上下文
 * @param link_addr DMA描述符链接地址。
 */
#define i2s_hal_start_rx_link(hal, link_addr) i2s_ll_rx_start_link((hal)->dev, link_addr)

/**
 * @brief 停止TX DMA链路
 *
 * @param hal HAL层的上下文
 */
#define i2s_hal_stop_tx_link(hal) i2s_ll_tx_stop_link((hal)->dev)

/**
 * @brief 停止RX DMA链路
 *
 * @param hal HAL层的上下文
 */
#define i2s_hal_stop_rx_link(hal) i2s_ll_rx_stop_link((hal)->dev)

/**
 * @brief 重置RX DMA
 *
 * @param hal HAL层的上下文
 */
#define i2s_hal_reset_rxdma(hal) i2s_ll_rx_reset_dma((hal)->dev)

/**
 * @brief 重置TX DMA
 *
 * @param hal HAL层的上下文
 */
#define i2s_hal_reset_txdma(hal) i2s_ll_tx_reset_dma((hal)->dev)

/**
 * @brief 从描述符地址中获取I2S
 *
 * @param hal HAL层的上下文
 * @param addr 用于接受地址外的指针
 */
#define i2s_hal_get_out_eof_des_addr(hal, addr) i2s_ll_tx_get_eof_des_addr((hal)->dev, addr)

/**
 * @brief 获取描述符地址中的I2S
 *
 * @param hal HAL层的上下文
 * @param addr 要在suc of des地址中接受的指针
 */
#define i2s_hal_get_in_eof_des_addr(hal, addr) i2s_ll_rx_get_eof_des_addr((hal)->dev, addr)
#endif

#if SOC_I2S_SUPPORTS_ADC
/**
 * @brief 启用内置DAC
 *
 * @param hal HAL层的上下文
 */
#define i2s_hal_enable_builtin_dac(hal)      i2s_ll_enable_builtin_dac((hal)->dev, true);

/**
 * @brief 启用内置ADC
 *
 * @param hal HAL层的上下文
 */
#define i2s_hal_enable_builtin_adc(hal)      i2s_ll_enable_builtin_adc((hal)->dev, true);

/**
 * @brief 禁用内置ADC
 *
 * @param hal HAL层的上下文
 */
#define i2s_hal_disable_builtin_adc(hal)     i2s_ll_enable_builtin_adc((hal)->dev, false);
#endif

#if SOC_I2S_SUPPORTS_DAC
/**
 * @brief 禁用内置DAC
 *
 * @param hal HAL层的上下文
 */
#define i2s_hal_disable_builtin_dac(hal)     i2s_ll_enable_builtin_dac((hal)->dev, false);
#endif

#ifdef __cplusplus
}
#endif

