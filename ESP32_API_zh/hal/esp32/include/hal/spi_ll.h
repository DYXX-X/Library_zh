// 版权所有2015-2019 Espressif Systems（上海）私人有限公司
//
// 根据Apache许可证2.0版（“许可证”）获得许可；
// 除非符合许可证，否则不得使用此文件。
// 您可以在以下地址获取许可证副本：

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

// ESP32 SPI寄存器操作的LL层

#pragma once

#include <string.h>
#include <stdlib.h> //用于abs（）
#include "esp_types.h"
#include "esp32/rom/lldesc.h"
#include "soc/spi_periph.h"
#include "soc/spi_struct.h"
#include "hal/misc.h"
#include "hal/spi_types.h"
#include "hal/assert.h"

#ifdef __cplusplus
extern "C" {
#endif

///初始化期间要重置的寄存器。不要在应用中使用。
#define SPI_LL_DMA_FIFO_RST_MASK (SPI_AHBM_RST | SPI_AHBM_FIFO_RST)
///未使用中断。不要在应用中使用。
#define SPI_LL_UNUSED_INT_MASK  (SPI_INT_EN | SPI_SLV_WR_STA_DONE | SPI_SLV_RD_STA_DONE | SPI_SLV_WR_BUF_DONE | SPI_SLV_RD_BUF_DONE)
///这两个掩码一起将SPI事务设置为单线模式
#define SPI_LL_ONE_LINE_CTRL_MASK (SPI_FREAD_DUAL | SPI_FREAD_QUAD | SPI_FREAD_DIO | SPI_FREAD_QIO)
#define SPI_LL_ONE_LINE_USER_MASK (SPI_FWRITE_DUAL | SPI_FWRITE_QUAD | SPI_FWRITE_DIO | SPI_FWRITE_QIO)
///将位顺序交换到正确的发送位置
#define HAL_SPI_SWAP_DATA_TX(data, len) HAL_SWAP32((uint32_t)(data) << (32 - len))
///这是预期的时钟频率
#define SPI_LL_PERIPH_CLK_FREQ (80 * 1000000)
#define SPI_LL_GET_HW(ID) ((ID)==0? &SPI1:((ID)==1? &SPI2 : &SPI3))

/**
 * 保存计算时钟配置的数据结构。由于计算需要很长时间，因此应该在初始化期间计算并存储在某个地方以便快速使用。
 */
typedef uint32_t spi_ll_clock_val_t;

//在ESP32-S2和更早的芯片上，DMA寄存器是SPI寄存器的一部分。因此，设置SPI外设的寄存器以控制DMA。
typedef spi_dev_t spi_dma_dev_t;

/*------------------------------------------------------------------------------
 * 控制
 *----------------------------------------------------------------------------*/
/**
 * 初始化SPI外围设备（主设备）。
 *
 * @param hw 外围寄存器的起始地址。
 */
static inline void spi_ll_master_init(spi_dev_t *hw)
{
    //重置计时
    hw->ctrl2.val = 0;

    //使用缓冲区的所有64字节
    hw->user.usr_miso_highpart = 0;
    hw->user.usr_mosi_highpart = 0;

    //禁用不需要的int
    hw->slave.val &= ~SPI_LL_UNUSED_INT_MASK;
}

/**
 * 初始化SPI外围设备（从设备）。
 *
 * @param hw 外围寄存器的起始地址。
 */
static inline void spi_ll_slave_init(spi_dev_t *hw)
{
    //配置从属设备
    hw->clock.val = 0;
    hw->user.val = 0;
    hw->ctrl.val = 0;
    hw->slave.wr_rd_buf_en = 1; //不确定是否需要
    hw->user.doutdin = 1; //我们只支持全双工
    hw->user.sio = 0;
    hw->slave.slave_mode = 1;
    hw->slave.sync_reset = 1;
    hw->slave.sync_reset = 0;
    //使用缓冲区的所有64字节
    hw->user.usr_miso_highpart = 0;
    hw->user.usr_mosi_highpart = 0;

    //禁用不需要的int
    hw->slave.val &= ~SPI_LL_UNUSED_INT_MASK;
}

/**
 * 检查用户定义的事务是否完成。
 *
 * @param hw 外围寄存器的起始地址。
 *
 * @return 如果事务已完成，则为true，否则为false。
 */
static inline bool spi_ll_usr_is_done(spi_dev_t *hw)
{
    return hw->slave.trans_done;
}

/**
 * 触发主用户定义事务的开始。
 *
 * @param hw 外围寄存器的起始地址。
 */
static inline void spi_ll_master_user_start(spi_dev_t *hw)
{
    hw->cmd.usr = 1;
}

/**
 * 为从属设备触发用户定义事务的启动。
 *
 * @param hw 外围寄存器的起始地址。
 */
static inline void spi_ll_slave_user_start(spi_dev_t *hw)
{
    hw->cmd.usr = 1;
}

/**
 * 获取当前运行命令位掩码。（预览）
 *
 * @param hw 外围寄存器的起始地址。
 *
 * @return 运行命令的位掩码，请参见``SPI_CMD_REG``。如果没有飞行中的命令，则为0。
 */
static inline uint32_t spi_ll_get_running_cmd(spi_dev_t *hw)
{
    return hw->cmd.val;
}

/**
 * 重置SPI CPU TX FIFO
 *
 * @param hw 外围寄存器的起始地址。
 */
static inline void spi_ll_cpu_tx_fifo_reset(spi_dev_t *hw)
{
    //这在esp32中未使用
}

/**
 * 重置SPI DMA FIFO
 *
 * @param hw 外围寄存器的起始地址。
 */
static inline void spi_ll_cpu_rx_fifo_reset(spi_dev_t *hw)
{
    //这在esp32中未使用
}

/**
 * 重置SPI DMA TX FIFO
 *
 * 在ESP32上，此功能不分离
 *
 * @param hw 外围寄存器的起始地址。
 */
static inline void spi_ll_dma_tx_fifo_reset(spi_dev_t *hw)
{
    hw->dma_conf.val |= SPI_LL_DMA_FIFO_RST_MASK;
    hw->dma_conf.val &= ~SPI_LL_DMA_FIFO_RST_MASK;
}

/**
 * 重置SPI DMA RX FIFO
 *
 * 在ESP32上，此功能不分离
 *
 * @param hw 外围寄存器的起始地址。
 */
static inline void spi_ll_dma_rx_fifo_reset(spi_dev_t *hw)
{
    hw->dma_conf.val |= SPI_LL_DMA_FIFO_RST_MASK;
    hw->dma_conf.val &= ~SPI_LL_DMA_FIFO_RST_MASK;
}

/**
 * 清除fifo完全错误
 *
 * @param hw 外围寄存器的起始地址。
 */
static inline void spi_ll_infifo_full_clr(spi_dev_t *hw)
{
    //这在esp32中未使用
}

/**
 * 清除fifo空错误
 *
 * @param hw 外围寄存器的起始地址。
 */
static inline void spi_ll_outfifo_empty_clr(spi_dev_t *hw)
{
    //这在esp32中未使用
}

/*------------------------------------------------------------------------------
 * DMA的SPI配置
 *----------------------------------------------------------------------------*/

/**
 * 启用/禁用RX DMA（外设->DMA->RAM）
 *
 * @param hw     外围寄存器的起始地址。
 * @param enable 1： 启用；2： 禁用
 */
static inline void spi_ll_dma_rx_enable(spi_dev_t *hw, bool enable)
{
    //这在esp32中未使用
}

/**
 * 启用/禁用TX DMA（RAM->DMA->外设）
 *
 * @param hw     外围寄存器的起始地址。
 * @param enable 1： 启用；2： 禁用
 */
static inline void spi_ll_dma_tx_enable(spi_dev_t *hw, bool enable)
{
    //这在esp32中未使用
}

/**
 * RX DMA EOF中断生成方式配置
 *
 * @param hw     外围寄存器的起始地址。
 * @param enable 1： 当dma推送数据字节的数量等于spi-dma转换中的spi_slv/mst_dma_rd_bytelen[19:0]的值时，设置spi_dma_inlink_eof。0:spi_dma_inlink_eof由非seg trans中的spi_trans_done或seg trans中的spi_dma_seg_trans_done设置。
 */
static inline void spi_ll_dma_set_rx_eof_generation(spi_dev_t *hw, bool enable)
{
    //这在esp32中未使用
}

/*------------------------------------------------------------------------------
 * 缓冲器
 *----------------------------------------------------------------------------*/
/**
 * 写入SPI缓冲区。
 *
 * @param hw 外围寄存器的起始地址。
 * @param buffer_to_send 要复制到缓冲区的数据地址。
 * @param bitlen 要复制的长度，以位为单位。
 */
static inline void spi_ll_write_buffer(spi_dev_t *hw, const uint8_t *buffer_to_send, size_t bitlen)
{
    for (size_t x = 0; x < bitlen; x += 32) {
        //使用memcpy解决txdata的对齐问题
        uint32_t word;
        memcpy(&word, &buffer_to_send[x / 8], 4);
        hw->data_buf[(x / 32)] = word;
    }
}

/**
 * 从SPI缓冲区读取。
 *
 * @param hw 外围寄存器的起始地址。
 * @param buffer_to_rcv 将缓冲区数据复制到的地址。
 * @param bitlen 要复制的长度，以位为单位。
 */
static inline void spi_ll_read_buffer(spi_dev_t *hw, uint8_t *buffer_to_rcv, size_t bitlen)
{
    for (size_t x = 0; x < bitlen; x += 32) {
        //执行memcpy以避免rx_buffer中可能的对齐问题
        uint32_t word = hw->data_buf[x / 32];
        int len = bitlen - x;
        if (len > 32) {
            len = 32;
        }
        memcpy(&buffer_to_rcv[x / 8], &word, (len + 7) / 8);
    }
}

/*------------------------------------------------------------------------------
 * 配置：模式
 *----------------------------------------------------------------------------*/
/**
 * 启用/禁用正极cs功能。
 *
 * @param hw 外围寄存器的起始地址。
 * @param cs 启用/禁用功能的CS（0-2）之一。
 * @param pos_cs true启用该功能，否则禁用（默认）。
 */
static inline void spi_ll_master_set_pos_cs(spi_dev_t *hw, int cs, uint32_t pos_cs)
{
    if (pos_cs) {
        hw->pin.master_cs_pol |= (1 << cs);
    } else {
        hw->pin.master_cs_pol &= ~(1 << cs);
    }
}

/**
 * 为TX数据启用/禁用LSBFIRST功能。
 *
 * @param hw 外围寄存器的起始地址。
 * @param lsbfirst 如果先发送TX数据的LSB，则为true，否则先发送MSB（默认值）。
 */
static inline void spi_ll_set_tx_lsbfirst(spi_dev_t *hw, bool lsbfirst)
{
    hw->ctrl.wr_bit_order = lsbfirst;
}

/**
 * 启用/禁用RX数据的LSBFIRST功能。
 *
 * @param hw 外围寄存器的起始地址。
 * @param lsbfirst 如果第一位接收为LSB，则为true，否则为MSB（默认值）。
 */
static inline void spi_ll_set_rx_lsbfirst(spi_dev_t *hw, bool lsbfirst)
{
    hw->ctrl.rd_bit_order = lsbfirst;
}

/**
 * 将外围设备的SPI模式设置为主设备。
 *
 * @param hw 外围寄存器的起始地址。
 * @param mode SPI模式工作在0-3。
 */
static inline void spi_ll_master_set_mode(spi_dev_t *hw, uint8_t mode)
{
    //配置极性
    if (mode == 0) {
        hw->pin.ck_idle_edge = 0;
        hw->user.ck_out_edge = 0;
    } else if (mode == 1) {
        hw->pin.ck_idle_edge = 0;
        hw->user.ck_out_edge = 1;
    } else if (mode == 2) {
        hw->pin.ck_idle_edge = 1;
        hw->user.ck_out_edge = 1;
    } else if (mode == 3) {
        hw->pin.ck_idle_edge = 1;
        hw->user.ck_out_edge = 0;
    }
}

/**
 * 将外设的SPI模式设置为从属设备。
 *
 * @param hw 外围寄存器的起始地址。
 * @param mode SPI模式工作在0-3。
 */
static inline void spi_ll_slave_set_mode(spi_dev_t *hw, const int mode, bool dma_used)
{
    if (mode == 0) {
        //定时需要固定以满足DMA的要求
        hw->pin.ck_idle_edge = 1;
        hw->user.ck_i_edge = 0;
        hw->ctrl2.miso_delay_mode = 0;
        hw->ctrl2.miso_delay_num = 0;
        hw->ctrl2.mosi_delay_mode = 2;
        hw->ctrl2.mosi_delay_num = 2;
    } else if (mode == 1) {
        hw->pin.ck_idle_edge = 1;
        hw->user.ck_i_edge = 1;
        hw->ctrl2.miso_delay_mode = 2;
        hw->ctrl2.miso_delay_num = 0;
        hw->ctrl2.mosi_delay_mode = 0;
        hw->ctrl2.mosi_delay_num = 0;
    } else if (mode == 2) {
        //定时需要固定以满足DMA的要求
        hw->pin.ck_idle_edge = 0;
        hw->user.ck_i_edge = 1;
        hw->ctrl2.miso_delay_mode = 0;
        hw->ctrl2.miso_delay_num = 0;
        hw->ctrl2.mosi_delay_mode = 1;
        hw->ctrl2.mosi_delay_num = 2;
    } else if (mode == 3) {
        hw->pin.ck_idle_edge = 0;
        hw->user.ck_i_edge = 0;
        hw->ctrl2.miso_delay_mode = 1;
        hw->ctrl2.miso_delay_num = 0;
        hw->ctrl2.mosi_delay_mode = 0;
        hw->ctrl2.mosi_delay_num = 0;
    }

    /* 使用DMA时，模式0和2存在硅问题，请更改时钟相位以避免DMA问题。这将导致从属输出出现在最多半个spi时钟之前
     */
    if (dma_used) {
        if (mode == 0) {
            hw->pin.ck_idle_edge = 0;
            hw->user.ck_i_edge = 1;
            hw->ctrl2.miso_delay_mode = 0;
            hw->ctrl2.miso_delay_num = 2;
            hw->ctrl2.mosi_delay_mode = 0;
            hw->ctrl2.mosi_delay_num = 3;
        } else if (mode == 2) {
            hw->pin.ck_idle_edge = 1;
            hw->user.ck_i_edge = 0;
            hw->ctrl2.miso_delay_mode = 0;
            hw->ctrl2.miso_delay_num = 2;
            hw->ctrl2.mosi_delay_mode = 0;
            hw->ctrl2.mosi_delay_num = 3;
        }
    }
}

/**
 * 将SPI设置为在全双工或半双工模式下工作。
 *
 * @param hw 外围寄存器的起始地址。
 * @param half_duplex true以半双工模式工作，否则以全双工模式工作。
 */
static inline void spi_ll_set_half_duplex(spi_dev_t *hw, bool half_duplex)
{
    hw->user.doutdin = !half_duplex;
}

/**
 * 将SPI设置为在SIO模式下工作或不工作。
 *
 * SIO是MOSI和MISO共享一条线路的模式。设备必须在半双工模式下工作。
 *
 * @param hw 外围寄存器的起始地址。
 * @param sio_mode true以在SIO模式下工作，否则为false。
 */
static inline void spi_ll_set_sio_mode(spi_dev_t *hw, int sio_mode)
{
    hw->user.sio = sio_mode;
}

/**
 * 配置主机要使用的SPI事务线模式。
 *
 * @param hw        外围寄存器的起始地址。
 * @param line_mode 要使用的SPI事务行模式，请参见``SPI_line_mode_t``。
 */
static inline void spi_ll_master_set_line_mode(spi_dev_t *hw, spi_line_mode_t line_mode)
{
    hw->ctrl.val &= ~SPI_LL_ONE_LINE_CTRL_MASK;
    hw->user.val &= ~SPI_LL_ONE_LINE_USER_MASK;
    if (line_mode.cmd_lines > 1) {
        HAL_ASSERT(false);
    }
    switch (line_mode.data_lines) {
    case 2:
        if (line_mode.addr_lines == 1) {
            // 1行-cmd+1行-addr+2行-data
            hw->ctrl.fread_dual = 1;
            hw->user.fwrite_dual = 1;
        } else if (line_mode.addr_lines == 2) {
            // 1行-cmd+2行-addr+2行数据
            hw->ctrl.fread_dio = 1;
            hw->user.fwrite_dio = 1;
        } else {
            HAL_ASSERT(false);
        }
        hw->ctrl.fastrd_mode = 1;
        break;
    case 4:
        if (line_mode.addr_lines == 1) {
            // 1-line-cmd+1-line-addr+4-line-data
            hw->ctrl.fread_quad = 1;
            hw->user.fwrite_quad = 1;
        } else if (line_mode.addr_lines == 4) {
            // 1行-cmd+4行-addr+4行-data
            hw->ctrl.fread_qio = 1;
            hw->user.fwrite_qio = 1;
        } else {
            HAL_ASSERT(false);
        }
        hw->ctrl.fastrd_mode = 1;
        break;
    default:
        // 1-line-cmd+1-line-addr+1-line-data
        break;
    }
}

/**
 * 选择要在当前事务中使用的CS之一。
 *
 * @param hw 外围寄存器的起始地址。
 * @param cs_id 要使用的cs为0-2，否则不使用它们。
 */
static inline void spi_ll_master_select_cs(spi_dev_t *hw, int cs_id)
{
    hw->pin.cs0_dis = (cs_id == 0) ? 0 : 1;
    hw->pin.cs1_dis = (cs_id == 1) ? 0 : 1;
    hw->pin.cs2_dis = (cs_id == 2) ? 0 : 1;
}

/**
 * 在当前交易后保持芯片选择激活。
 *
 * @param hw 外围寄存器的起始地址。
 * @param keep_active 如果0不保持CS激活，否则保持CS激活
 */
static inline void spi_ll_master_keep_cs(spi_dev_t *hw, int keep_active)
{
    hw->pin.cs_keep_active = (keep_active != 0) ? 1 : 0;
}

/*------------------------------------------------------------------------------
 * 配置：参数
 *----------------------------------------------------------------------------*/
/**
 * 根据存储值设置主时钟。
 *
 * @param hw 外围寄存器的起始地址。
 * @param val 之前计算的存储时钟配置（通过“spi_ll_cal_clock”）。
 */
static inline void spi_ll_master_set_clock_by_reg(spi_dev_t *hw, const spi_ll_clock_val_t *val)
{
    hw->clock.val = *(uint32_t *)val;
}

/**
 * 获取给定分频器的频率。不要在应用中使用。
 *
 * @param fapb 系统的APB时钟。
 * @param pre 预设计。
 * @param n 主分配器。
 *
 * @return 给定分频器的频率。
 */
static inline int spi_ll_freq_for_pre_n(int fapb, int pre, int n)
{
    return (fapb / (pre * n));
}

/**
 * 计算主机可用的最近频率。
 *
 * @param fapb 系统的APB时钟。
 * @param hz 所需频率。
 * @param duty_cycle 所需占空比。
 * @param out_reg 用于存储返回频率的计算时钟配置的输出地址。
 *
 * @return 实际（最近）频率。
 */
static inline int spi_ll_master_cal_clock(int fapb, int hz, int duty_cycle, spi_ll_clock_val_t *out_reg)
{
    typeof(SPI1.clock) reg;
    int eff_clk;

    //在hw中，n、h和l为1-64，pre为1-8K。写入寄存器的值比使用的值低一个。
    if (hz > ((fapb / 4) * 3)) {
        //直接使用Fapb将在这里提供最佳结果。
        reg.clkcnt_l = 0;
        reg.clkcnt_h = 0;
        reg.clkcnt_n = 0;
        reg.clkdiv_pre = 0;
        reg.clk_equ_sysclk = 1;
        eff_clk = fapb;
    } else {
        //为了获得最佳占空比分辨率，我们希望n尽可能接近32，但是
        //我们还需要一个pre/n组合，使我们尽可能接近预期频率。
        //要做到这一点，我们必须严格遵守并计算出最佳的预处理方案。
        //如果在pre/n组合中有一个选择可以得到相同的结果，请使用
        //n越高。
        int pre, n, h, l;
        int bestn = -1;
        int bestpre = -1;
        int besterr = 0;
        int errval;
        for (n = 2; n <= 64; n++) { //从2开始：我们需要能够设置h/l，这样我们至少有一个高脉冲和一个低脉冲。
            //实际上，这是pre=round（（fapb/n）/hz）。
            pre = ((fapb / n) + (hz / 2)) / hz;
            if (pre <= 0) {
                pre = 1;
            }
            if (pre > 8192) {
                pre = 8192;
            }
            errval = abs(spi_ll_freq_for_pre_n(fapb, pre, n) - hz);
            if (bestn == -1 || errval <= besterr) {
                besterr = errval;
                bestn = n;
                bestpre = pre;
            }
        }

        n = bestn;
        pre = bestpre;
        l = n;
        //这有效地进行了舍入（（duty_cycle*n）/256）
        h = (duty_cycle * n + 127) / 256;
        if (h <= 0) {
            h = 1;
        }

        reg.clk_equ_sysclk = 0;
        reg.clkcnt_n = n - 1;
        reg.clkdiv_pre = pre - 1;
        reg.clkcnt_h = h - 1;
        reg.clkcnt_l = l - 1;
        eff_clk = spi_ll_freq_for_pre_n(fapb, pre, n);
    }
    if (out_reg != NULL) {
        *(uint32_t *)out_reg = reg.val;
    }
    return eff_clk;
}

/**
 * 根据所需参数计算并设置SPI主机的时钟。
 *
 * 这需要很长时间，建议在初始化期间通过“spi_ll_master_cal_clock”计算配置并存储结果，然后在“spi_ll_msater_set_clock_by_reg”使用时通过存储值配置时钟。
 *
 * @param hw 外围寄存器的起始地址。
 * @param fapb 系统的APB时钟。
 * @param hz 所需频率。
 * @param duty_cycle 所需占空比。
 *
 * @return 使用的实际频率。
 */
static inline int spi_ll_master_set_clock(spi_dev_t *hw, int fapb, int hz, int duty_cycle)
{
    spi_ll_clock_val_t reg_val;
    int freq = spi_ll_master_cal_clock(fapb, hz, duty_cycle, &reg_val);
    spi_ll_master_set_clock_by_reg(hw, &reg_val);
    return freq;
}

/**
 * 启用/禁用CS引脚的CK sel功能。
 *
 * CK-sel是一个功能，可以随时钟切换CS线。
 *
 * @param hw 外围寄存器的起始地址。
 * @param cs CS引脚用于启用/禁用功能，0-2。
 * @param cksel true启用该功能，否则为false。
 */
static inline void spi_ll_master_set_cksel(spi_dev_t *hw, int cs, uint32_t cksel)
{
    if (cksel) {
        hw->pin.master_ck_sel |= (1 << cs);
    } else {
        hw->pin.master_ck_sel &= ~(1 << cs);
    }
}

/**
 * 设置信号输出边缘后的mosi延迟。（预览）
 *
 * 延迟模式/num是Espressif概念，可能会在新芯片中发生变化。
 *
 * @param hw 外围寄存器的起始地址。
 * @param delay_mode 延迟模式，见TRM。
 * @param delay_num APB时钟延迟。
 */
static inline void spi_ll_set_mosi_delay(spi_dev_t *hw, int delay_mode, int delay_num)
{
    hw->ctrl2.mosi_delay_mode = delay_mode;
    hw->ctrl2.mosi_delay_num = delay_num;
}

/**
 * 在内部外设之前设置应用于输入信号的miso延迟。（预览）
 *
 * 延迟模式/num是Espressif概念，可能会在新芯片中发生变化。
 *
 * @param hw 外围寄存器的起始地址。
 * @param delay_mode 延迟模式，见TRM。
 * @param delay_num APB时钟延迟。
 */
static inline void spi_ll_set_miso_delay(spi_dev_t *hw, int delay_mode, int delay_num)
{
    hw->ctrl2.miso_delay_mode = delay_mode;
    hw->ctrl2.miso_delay_num = delay_num;
}

/**
 * 设置伪时钟以在RX相位之前输出（主），或设置时钟以在数据相位之前和地址相位之后跳过（从）。
 *
 * 注意，该相位还用于补偿半双工模式下的RX定时。
 *
 * @param hw 外围寄存器的起始地址。
 * @param dummy_n 使用的虚拟循环。0以禁用虚拟相位。
 */
static inline void spi_ll_set_dummy(spi_dev_t *hw, int dummy_n)
{
    hw->user.usr_dummy = dummy_n ? 1 : 0;
    HAL_FORCE_MODIFY_U32_REG_FIELD(hw->user1, usr_dummy_cyclelen, dummy_n - 1);
}

/**
 * 在最后一个SPI时钟之后的CS非活动边缘之前设置SPI时钟的延迟。
 *
 * @param hw 外围寄存器的起始地址。
 * @param hold 最后一个时钟后SPI时钟的延迟，0表示禁用保持相位。
 */
static inline void spi_ll_master_set_cs_hold(spi_dev_t *hw, int hold)
{
    hw->ctrl2.hold_time = hold;
    hw->user.cs_hold = hold ? 1 : 0;
}

/**
 * 在CS活动边缘之后的第一个SPI时钟之前设置SPI时钟的延迟。
 *
 * 注意，当在全双工模式下使用命令/地址阶段时，ESP32不支持使用此功能。
 *
 * @param hw 外围寄存器的起始地址。
 * @param setup CS激活边缘后SPI时钟延迟，0表示禁用设置阶段。
 */
static inline void spi_ll_master_set_cs_setup(spi_dev_t *hw, uint8_t setup)
{
    hw->ctrl2.setup_time = setup - 1;
    hw->user.cs_setup = setup ? 1 : 0;
}

/*------------------------------------------------------------------------------
 * 配置：数据
 *----------------------------------------------------------------------------*/
/**
 * 设置输入长度（主）。
 *
 * @param hw 外围寄存器的起始地址。
 * @param bitlen 输入长度，以位为单位。
 */
static inline void spi_ll_set_miso_bitlen(spi_dev_t *hw, size_t bitlen)
{
    hw->miso_dlen.usr_miso_dbitlen = bitlen - 1;
}

/**
 * 设置输出长度（主）。
 *
 * @param hw 外围寄存器的起始地址。
 * @param bitlen 输出长度，以位为单位。
 */
static inline void spi_ll_set_mosi_bitlen(spi_dev_t *hw, size_t bitlen)
{
    hw->mosi_dlen.usr_mosi_dbitlen = bitlen - 1;
}

/**
 * 设置最大输入长度（从）。
 *
 * @param hw 外围寄存器的起始地址。
 * @param bitlen 输入长度，以位为单位。
 */
static inline void spi_ll_slave_set_rx_bitlen(spi_dev_t *hw, size_t bitlen)
{
    hw->slv_rdbuf_dlen.bit_len = bitlen - 1;
}

/**
 * 设置最大输出长度（从）。
 *
 * @param hw 外围寄存器的起始地址。
 * @param bitlen 输出长度，以位为单位。
 */
static inline void spi_ll_slave_set_tx_bitlen(spi_dev_t *hw, size_t bitlen)
{
    hw->slv_wrbuf_dlen.bit_len = bitlen - 1;
}

/**
 * 设置命令阶段的长度。
 *
 * 当处于4位模式时，相位的SPI周期将更短。E、 g.在4位模式下，16位命令相位需要4个周期。
 *
 * @param hw 外围寄存器的起始地址。
 * @param bitlen 命令阶段的长度，以位为单位。0以禁用命令阶段。
 */
static inline void spi_ll_set_command_bitlen(spi_dev_t *hw, int bitlen)
{
    hw->user2.usr_command_bitlen = bitlen - 1;
    hw->user.usr_command = bitlen ? 1 : 0;
}

/**
 * 设置地址阶段的长度。
 *
 * 当处于4位模式时，相位的SPI周期将更短。E、 g.在4位模式下，16位地址相位需要4个周期。
 *
 * @param hw 外围寄存器的起始地址。
 * @param bitlen 地址相位的长度，以位为单位。0以禁用地址阶段。
 */
static inline void spi_ll_set_addr_bitlen(spi_dev_t *hw, int bitlen)
{
    hw->user1.usr_addr_bitlen = bitlen - 1;
    hw->user.usr_addr = bitlen ? 1 : 0;
}

/**
 * 以直观的方式设置地址值。
 *
 * 长度和lsbfirst是将地址移位和交换到正确位置所必需的。
 *
 * @param hw 外围寄存器的起始地址。
 * @param address 要设置的地址
 * @param addrlen 地址阶段的长度
 * @param lsbfirst LSB第一特征是否被启用。
 */
static inline void spi_ll_set_address(spi_dev_t *hw, uint64_t addr, int addrlen, uint32_t lsbfirst)
{
    if (lsbfirst) {
        /* 输出地址从最高字节的LSB开始，即addr[24]->addr[31]…addr[0]->addr[7]slv_wr_status[24]->slv_wr_status[31]…slv_wer_status[0]->slv-wr_status[7]。因此，交换字节顺序，让LSB先发送。
         */
        addr = HAL_SWAP64(addr);
        hw->addr = addr >> 32;
        hw->slv_wr_status = addr;
    } else {
        // 将地址移位到addr（可能还有slv_wr_status）寄存器的MSB。
        // 输出地址将从MSB发送到addr寄存器的LSB，然后将MSB发送至slv_wr_status寄存器的LSA。
        if (addrlen > 32) {
            hw->addr = addr >> (addrlen - 32);
            hw->slv_wr_status = addr << (64 - addrlen);
        } else {
            hw->addr = addr << (32 - addrlen);
        }
    }
}

/**
 * 以直观的方式设置命令值。
 *
 * 长度和lsbfirst是将命令移位和交换到正确位置所必需的。
 *
 * @param hw 外围寄存器的开始命令。
 * @param command 要设置的命令
 * @param addrlen 命令阶段的长度
 * @param lsbfirst LSB第一特征是否被启用。
 */
static inline void spi_ll_set_command(spi_dev_t *hw, uint16_t cmd, int cmdlen, bool lsbfirst)
{
    if (lsbfirst) {
        // 输出命令从第0位开始到第15位，保持原样。
        HAL_FORCE_MODIFY_U32_REG_FIELD(hw->user2, usr_command_value, cmd);
    } else {
        /* 输出命令将从command_value的位7发送到0，然后从同一寄存器字段的位15发送到8。转换和交换以更直接地发送。
         */
        HAL_FORCE_MODIFY_U32_REG_FIELD(hw->user2, usr_command_value, HAL_SPI_SWAP_DATA_TX(cmd, cmdlen));

    }
}

/**
 * 启用/禁用RX数据相位。
 *
 * @param hw 外围寄存器的起始地址。
 * @param enable 如果RX相位存在，则为真，否则为假。
 */
static inline void spi_ll_enable_miso(spi_dev_t *hw, int enable)
{
    hw->user.usr_miso = enable;
}

/**
 * 启用/禁用TX数据阶段。
 *
 * @param hw 外围寄存器的起始地址。
 * @param enable 如果TX相位存在，则为true，否则为false。
 */
static inline void spi_ll_enable_mosi(spi_dev_t *hw, int enable)
{
    hw->user.usr_mosi = enable;
}

/**
 * 在下一个事务之前重置从属外设。
 *
 * @param hw 外围寄存器的起始地址。
 */
static inline void spi_ll_slave_reset(spi_dev_t *hw)
{
    hw->slave.sync_reset = 1;
    hw->slave.sync_reset = 0;
}

/**
 * 获取从设备的接收比特长度。
 *
 * @param hw 外围寄存器的起始地址。
 *
 * @return 从设备的接收位。
 */
static inline uint32_t spi_ll_slave_get_rcv_bitlen(spi_dev_t *hw)
{
    return hw->slv_rd_bit.slv_rdata_bit;
}

/*------------------------------------------------------------------------------
 * 中断
 *----------------------------------------------------------------------------*/
/**
 * 禁用trans_done中断。
 *
 * @param hw 外围寄存器的起始地址。
 */
static inline void spi_ll_disable_int(spi_dev_t *hw)
{
    hw->slave.trans_inten = 0;
}

/**
 * 清除trans_done中断。
 *
 * @param hw 外围寄存器的起始地址。
 */
static inline void spi_ll_clear_int_stat(spi_dev_t *hw)
{
    hw->slave.trans_done = 0;
}

/**
 * 设置trans_done中断。
 *
 * @param hw 外围寄存器的起始地址。
 */
static inline void spi_ll_set_int_stat(spi_dev_t *hw)
{
    hw->slave.trans_done = 1;
}

/**
 * 启用trans_done中断。
 *
 * @param hw 外围寄存器的起始地址。
 */
static inline void spi_ll_enable_int(spi_dev_t *hw)
{
    hw->slave.trans_inten = 1;
}

/*------------------------------------------------------------------------------
 * DMA：RX DMA（外设->DMA->RAM）TX DMA（RAM->DMA->外设）
 *----------------------------------------------------------------------------*/
/**
 * 重置RX DMA，将从外设接收的数据存储到RAM中。
 *
 * @param dma_in  DMA外设寄存器的起始地址，将从外设接收的数据存储到RAM中。
 * @param channel DMA通道，用于芯片版本兼容性，未使用。
 */
static inline void spi_dma_ll_rx_reset(spi_dma_dev_t *dma_in, uint32_t channel)
{
    //重置RX DMA外围设备
    dma_in->dma_conf.in_rst = 1;
    dma_in->dma_conf.in_rst = 0;
}

/**
 * 启动RX DMA。
 *
 * @param dma_in  DMA外设寄存器的起始地址，将从外设接收的数据存储到RAM中。
 * @param channel DMA通道，用于芯片版本兼容性，未使用。
 * @param addr    开始DMA描述符的地址。
 */
static inline void spi_dma_ll_rx_start(spi_dma_dev_t *dma_in, uint32_t channel, lldesc_t *addr)
{
    dma_in->dma_in_link.addr = (int) addr & 0xFFFFF;
    dma_in->dma_in_link.start = 1;
}

/**
 * 为数据启用DMA RX信道突发
 *
 * @param dma_in  DMA外设寄存器的起始地址，将从外设接收的数据存储到RAM中。
 * @param channel DMA通道，用于芯片版本兼容性，未使用。
 * @param enable  True表示启用，false表示禁用
 */
static inline void spi_dma_ll_rx_enable_burst_data(spi_dma_dev_t *dma_in, uint32_t channel, bool enable)
{
    //esp32不支持此功能
}

/**
 * 为描述符启用DMA RX信道突发
 *
 * @param dma_in  DMA外设寄存器的起始地址，将从外设接收的数据存储到RAM中。
 * @param channel DMA通道，用于芯片版本兼容性，未使用。
 * @param enable  True表示启用，false表示禁用
 */
static inline void spi_dma_ll_rx_enable_burst_desc(spi_dma_dev_t *dma_in, uint32_t channel, bool enable)
{
    dma_in->dma_conf.indscr_burst_en = enable;
}

/**
 * 重置TX DMA，将数据从RAM传输到外围设备。
 *
 * @param dma_out DMA外设寄存器的起始地址，用于将数据从RAM传输到外设。
 * @param channel DMA通道，用于芯片版本兼容性，未使用。
 */
static inline void spi_dma_ll_tx_reset(spi_dma_dev_t *dma_out, uint32_t channel)
{
    //重置TX DMA外围设备
    dma_out->dma_conf.out_rst = 1;
    dma_out->dma_conf.out_rst = 0;
}

/**
 * 启动TX DMA。
 *
 * @param dma_out DMA外设寄存器的起始地址，用于将数据从RAM传输到外设。
 * @param channel DMA通道，用于芯片版本兼容性，未使用。
 * @param addr    开始DMA描述符的地址。
 */
static inline void spi_dma_ll_tx_start(spi_dma_dev_t *dma_out, uint32_t channel, lldesc_t *addr)
{
    dma_out->dma_out_link.addr = (int) addr & 0xFFFFF;
    dma_out->dma_out_link.start = 1;
}

/**
 * 为数据启用DMA TX信道突发
 *
 * @param dma_out DMA外设寄存器的起始地址，用于将数据从RAM传输到外设。
 * @param channel DMA通道，用于芯片版本兼容性，未使用。
 * @param enable  True表示启用，false表示禁用
 */
static inline void spi_dma_ll_tx_enable_burst_data(spi_dma_dev_t *dma_out, uint32_t channel, bool enable)
{
    dma_out->dma_conf.out_data_burst_en = enable;
}

/**
 * 为描述符启用DMA TX信道突发
 *
 * @param dma_out DMA外设寄存器的起始地址，用于将数据从RAM传输到外设。
 * @param channel DMA通道，用于芯片版本兼容性，未使用。
 * @param enable  True表示启用，false表示禁用
 */
static inline void spi_dma_ll_tx_enable_burst_desc(spi_dma_dev_t *dma_out, uint32_t channel, bool enable)
{
    dma_out->dma_conf.outdscr_burst_en = enable;
}

/**
 * OUT EOF标志生成方式配置
 *
 * @param dma_out DMA外设寄存器的起始地址，用于将数据从RAM传输到外设。
 * @param channel DMA通道，用于芯片版本兼容性，未使用。
 * @param enable  1： 当dma从fifo 0中弹出所有数据时：当ahb将所有数据推送到fifo时。
 */
static inline void spi_dma_ll_set_out_eof_generation(spi_dma_dev_t *dma_out, uint32_t channel, bool enable)
{
    dma_out->dma_conf.out_eof_mode = enable;
}

/**
 * 启用自动输出链接写回
 *
 * @param dma_out DMA外设寄存器的起始地址，用于将数据从RAM传输到外设。
 * @param channel DMA通道，用于芯片版本兼容性，未使用。
 * @param enable  True表示启用，false表示禁用
 */
static inline void spi_dma_ll_enable_out_auto_wrback(spi_dma_dev_t *dma_out, uint32_t channel, bool enable)
{
    //不在ESP32中配置
}

#undef SPI_LL_RST_MASK
#undef SPI_LL_UNUSED_INT_MASK

#ifdef __cplusplus
}
#endif

