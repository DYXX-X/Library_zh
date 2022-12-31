/*
 * SPDX文件版权所有文本：2015-2022 Espressif Systems（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */

/*******************************************************************************
 * 注意：hal不是公共api，不要在应用程序代码中使用。请参阅自述文件。在hal/include/hal/readme.md中的md
 ******************************************************************************/

// ESP32-S2 SPI寄存器操作的LL层

#pragma once

#include <stdlib.h> //用于abs（）
#include <string.h>
#include "esp_types.h"
#include "esp_attr.h"
#include "soc/spi_periph.h"
#include "soc/spi_struct.h"
#include "soc/lldesc.h"
#include "hal/assert.h"
#include "hal/misc.h"
#include "hal/spi_types.h"

#ifdef __cplusplus
extern "C" {
#endif

///初始化期间要重置的寄存器。不要在应用中使用。
#define SPI_LL_DMA_FIFO_RST_MASK (SPI_AHBM_RST | SPI_AHBM_FIFO_RST)
///未使用中断。不要在应用中使用。
#define SPI_LL_UNUSED_INT_MASK  (SPI_INT_TRANS_DONE_EN | SPI_INT_WR_DMA_DONE_EN | SPI_INT_RD_DMA_DONE_EN | SPI_INT_WR_BUF_DONE_EN | SPI_INT_RD_BUF_DONE_EN)
///这两个掩码一起将SPI事务设置为单线模式
#define SPI_LL_ONE_LINE_CTRL_MASK (SPI_FREAD_OCT | SPI_FREAD_QUAD | SPI_FREAD_DUAL | SPI_FCMD_OCT | \
        SPI_FCMD_QUAD | SPI_FCMD_DUAL | SPI_FADDR_OCT | SPI_FADDR_QUAD | SPI_FADDR_DUAL)
#define SPI_LL_ONE_LINE_USER_MASK (SPI_FWRITE_OCT | SPI_FWRITE_QUAD | SPI_FWRITE_DUAL)
///将位顺序交换到正确的发送位置
#define HAL_SPI_SWAP_DATA_TX(data, len) HAL_SWAP32((uint32_t)(data) << (32 - len))
///这是预期的时钟频率
#define SPI_LL_PERIPH_CLK_FREQ (80 * 1000000)
#define SPI_LL_GET_HW(ID) ((ID)==0? ({abort();NULL;}):((ID)==1? &GPSPI2 : &GPSPI3))

/**
 * 保存计算时钟配置的数据结构。由于计算需要很长时间，因此应该在初始化期间计算并存储在某个地方以便快速使用。
 */
typedef uint32_t spi_ll_clock_val_t;

//在ESP32-S2和更早的芯片上，DMA寄存器是SPI寄存器的一部分。因此，设置SPI外设的寄存器以控制DMA。
typedef spi_dev_t spi_dma_dev_t;

///所有支持中断的类型定义
typedef enum {
    SPI_LL_INTR_TRANS_DONE =    BIT(0),     ///<交易已完成
    SPI_LL_INTR_IN_SUC_EOF =    BIT(1),     ///<DMA in_suc_eof已触发
    SPI_LL_INTR_OUT_EOF =       BIT(2),     ///<已触发DMA out_eof
    SPI_LL_INTR_OUT_TOTAL_EOF = BIT(3),     ///<已触发DMA out_total_of
    SPI_LL_INTR_IN_FULL =       BIT(4),     ///发生<DMA in_full错误
    SPI_LL_INTR_OUT_EMPTY =     BIT(5),     ///发生<DMA out_empty错误
    SPI_LL_INTR_RDBUF =         BIT(6),     ///<已收到RDBUF命令。仅在从属HD中可用。
    SPI_LL_INTR_WRBUF =         BIT(7),     ///<已收到WRBUF命令。仅在从属HD中可用。
    SPI_LL_INTR_RDDMA =         BIT(8),     ///<已收到RDDMA命令。仅在从属HD中可用。
    SPI_LL_INTR_WRDMA =         BIT(9),     ///<已收到WRDMA命令。仅在从属HD中可用。
    SPI_LL_INTR_CMD7 =          BIT(10),    ///<已收到CMD7命令。仅在从属HD中可用。
    SPI_LL_INTR_CMD8 =          BIT(11),    ///<已收到CMD8命令。仅在从属HD中可用。
    SPI_LL_INTR_CMD9 =          BIT(12),    ///<已收到CMD9命令。仅在从属HD中可用。
    SPI_LL_INTR_CMDA =          BIT(13),    ///<已收到CMDA命令。仅在从属HD中可用。
    SPI_LL_INTR_SEG_DONE =      BIT(14),
} spi_ll_intr_t;
FLAG_ATTR(spi_ll_intr_t)

///<记录交易长度的条件标志
typedef enum {
    SPI_LL_TRANS_LEN_COND_WRBUF =   BIT(0), ///将记录<WRBUF长度
    SPI_LL_TRANS_LEN_COND_RDBUF =   BIT(1), ///<将记录RDBUF长度
    SPI_LL_TRANS_LEN_COND_WRDMA =   BIT(2), ///<将记录WRDMA长度
    SPI_LL_TRANS_LEN_COND_RDDMA =   BIT(3), ///<将记录RDDMA长度
} spi_ll_trans_len_cond_t;
FLAG_ATTR(spi_ll_trans_len_cond_t)

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

    //禁用功能可能会导致事务过长
    hw->user.usr_prep_hold = 0;
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
    hw->user.doutdin = 1; //我们只支持全双工
    hw->user.sio = 0;
    hw->slave.slave_mode = 1;
    hw->slave.soft_reset = 1;
    hw->slave.soft_reset = 0;
    //使用缓冲区的所有64字节
    hw->user.usr_miso_highpart = 0;
    hw->user.usr_mosi_highpart = 0;

    // 将DMA In Link配置为在事务位计数器超过时不终止
    hw->dma_conf.rx_eof_en = 0;

    //禁用不需要的int
    hw->slave.val &= ~SPI_LL_UNUSED_INT_MASK;
}

static inline void spi_ll_slave_hd_init(spi_dev_t *hw)
{
    hw->clock.val = 0;
    hw->user.val = 0;
    hw->ctrl.val = 0;
    hw->user.sio = 0;

    hw->slave.soft_reset = 1;
    hw->slave.soft_reset = 0;

    hw->user.doutdin = 0; //我们只支持半双工
    hw->slave.slave_mode = 1;
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
    //这在esp32s2中未使用
}

/**
 * 重置SPI CPU RX FIFO
 *
 * @param hw 外围寄存器的起始地址。
 */
static inline void spi_ll_cpu_rx_fifo_reset(spi_dev_t *hw)
{
    //这在esp32s2中未使用
}

/**
 * 重置SPI DMA TX FIFO
 *
 * 在ESP32S2上，此功能未分离
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
 * 在ESP32S2上，此功能未分离
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
    hw->dma_conf.infifo_full_clr = 1;
    hw->dma_conf.infifo_full_clr = 0;
}

/**
 * 清除fifo空错误
 *
 * @param hw 外围寄存器的起始地址。
 */
static inline void spi_ll_outfifo_empty_clr(spi_dev_t *hw)
{
    hw->dma_conf.outfifo_empty_clr = 1;
    hw->dma_conf.outfifo_empty_clr = 0;
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
    //这在esp32s2中未使用
}

/**
 * 启用/禁用TX DMA（RAM->DMA->外设）
 *
 * @param hw     外围寄存器的起始地址。
 * @param enable 1： 启用；2： 禁用
 */
static inline void spi_ll_dma_tx_enable(spi_dev_t *hw, bool enable)
{
    //这在esp32s2中未使用
}

/**
 * RX DMA EOF中断生成方式配置
 *
 * @param hw     外围寄存器的起始地址。
 * @param enable 1： 当dma推送数据字节的数量等于spi-dma转换中的spi_slv/mst_dma_rd_bytelen[19:0]的值时，设置spi_dma_inlink_eof。0:spi_dma_inlink_eof由非seg trans中的spi_trans_done或seg trans中的spi_dma_seg_trans_done设置。
 */
static inline void spi_ll_dma_set_rx_eof_generation(spi_dev_t *hw, bool enable)
{
    hw->dma_conf.rx_eof_en = enable;
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

static inline void spi_ll_read_buffer_byte(spi_dev_t *hw, int byte_addr, uint8_t *out_data, int len)
{
    while (len > 0) {
        uint32_t word = hw->data_buf[byte_addr / 4];
        int offset = byte_addr % 4;

        int copy_len = 4 - offset;
        if (copy_len > len) {
            copy_len = len;
        }

        memcpy(out_data, ((uint8_t *)&word) + offset, copy_len);
        byte_addr += copy_len;
        out_data += copy_len;
        len -= copy_len;
    }
}

static inline void spi_ll_write_buffer_byte(spi_dev_t *hw, int byte_addr, uint8_t *data, int len)
{
    HAL_ASSERT(byte_addr + len <= 72);
    HAL_ASSERT(len > 0);
    HAL_ASSERT(byte_addr >= 0);

    while (len > 0) {
        uint32_t word;
        int offset = byte_addr % 4;

        int copy_len = 4 - offset;
        if (copy_len > len) {
            copy_len = len;
        }

        //读修改写
        if (copy_len != 4) {
            word = hw->data_buf[byte_addr / 4];
        }

        memcpy(((uint8_t *)&word) + offset, data, copy_len);
        hw->data_buf[byte_addr / 4] = word;
        data += copy_len;
        byte_addr += copy_len;
        len -= copy_len;
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
        hw->misc.master_cs_pol |= (1 << cs);
    } else {
        hw->misc.master_cs_pol &= ~(1 << cs);
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
        hw->misc.ck_idle_edge = 0;
        hw->user.ck_out_edge = 0;
    } else if (mode == 1) {
        hw->misc.ck_idle_edge = 0;
        hw->user.ck_out_edge = 1;
    } else if (mode == 2) {
        hw->misc.ck_idle_edge = 1;
        hw->user.ck_out_edge = 1;
    } else if (mode == 3) {
        hw->misc.ck_idle_edge = 1;
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
        hw->misc.ck_idle_edge = 0;
        hw->user.rsck_i_edge = 0;
        hw->user.tsck_i_edge = 0;
        hw->ctrl1.clk_mode_13 = 0;
    } else if (mode == 1) {
        hw->misc.ck_idle_edge = 0;
        hw->user.rsck_i_edge = 1;
        hw->user.tsck_i_edge = 1;
        hw->ctrl1.clk_mode_13 = 1;
    } else if (mode == 2) {
        hw->misc.ck_idle_edge = 1;
        hw->user.rsck_i_edge = 1;
        hw->user.tsck_i_edge = 1;
        hw->ctrl1.clk_mode_13 = 0;
    } else if (mode == 3) {
        hw->misc.ck_idle_edge = 1;
        hw->user.rsck_i_edge = 0;
        hw->user.tsck_i_edge = 0;
        hw->ctrl1.clk_mode_13 = 1;
    }
    hw->ctrl1.rsck_data_out = 0;
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
    hw->ctrl.fcmd_dual = (line_mode.cmd_lines == 2);
    hw->ctrl.fcmd_quad = (line_mode.cmd_lines == 4);
    hw->ctrl.fcmd_oct = (line_mode.cmd_lines == 8);
    hw->ctrl.faddr_dual = (line_mode.addr_lines == 2);
    hw->ctrl.faddr_quad = (line_mode.addr_lines == 4);
    hw->ctrl.faddr_oct = (line_mode.addr_lines == 8);
    hw->ctrl.fread_dual = (line_mode.data_lines == 2);
    hw->user.fwrite_dual = (line_mode.data_lines == 2);
    hw->ctrl.fread_quad = (line_mode.data_lines == 4);
    hw->user.fwrite_quad = (line_mode.data_lines == 4);
    hw->ctrl.fread_oct = (line_mode.data_lines == 8);
    hw->user.fwrite_oct = (line_mode.data_lines == 8);
}

static inline void spi_ll_slave_set_seg_mode(spi_dev_t *hw, bool seg_trans)
{
    hw->dma_conf.dma_seg_trans_en = seg_trans;
}

/**
 * 选择要在当前事务中使用的CS之一。
 *
 * @param hw 外围寄存器的起始地址。
 * @param cs_id 要使用的cs为0-2，否则不使用它们。
 */
static inline void spi_ll_master_select_cs(spi_dev_t *hw, int cs_id)
{
    hw->misc.cs0_dis = (cs_id == 0) ? 0 : 1;
    hw->misc.cs1_dis = (cs_id == 1) ? 0 : 1;
    hw->misc.cs2_dis = (cs_id == 2) ? 0 : 1;
    hw->misc.cs3_dis = (cs_id == 3) ? 0 : 1;
    hw->misc.cs4_dis = (cs_id == 4) ? 0 : 1;
    hw->misc.cs5_dis = (cs_id == 5) ? 0 : 1;
}

/**
 * 在当前交易后保持芯片选择激活。
 *
 * @param hw 外围寄存器的起始地址。
 * @param keep_active 如果0不保持CS激活，否则保持CS激活
 */
static inline void spi_ll_master_keep_cs(spi_dev_t *hw, int keep_active)
{
    hw->misc.cs_keep_active = (keep_active != 0) ? 1 : 0;
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
    typeof(GPSPI2.clock) reg;
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
    //TODO:这没有道理
    hw->dout_num.dout0_num = 0;
    hw->dout_num.dout1_num = 0;
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
    //TODO:这没有道理
    hw->din_num.din0_num = 1;
    hw->din_num.din1_num = 1;
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
    hw->ctrl2.cs_hold_time = hold;
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
    hw->ctrl2.cs_setup_time = setup - 1;
    hw->user.cs_setup = setup ? 1 : 0;
}

/**
 * 启用/禁用从设备的段传输功能。
 *
 * @param hw 外围寄存器的起始地址。
 * @param en     true表示启用，false表示禁用。
 */
static inline void spi_ll_slave_set_seg_en(spi_dev_t *hw, bool en)
{
    hw->dma_conf.dma_seg_trans_en = en;
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
    hw->miso_dlen.usr_miso_bit_len = bitlen - 1;
}

/**
 * 设置输出长度（主）。
 *
 * @param hw 外围寄存器的起始地址。
 * @param bitlen 输出长度，以位为单位。
 */
static inline void spi_ll_set_mosi_bitlen(spi_dev_t *hw, size_t bitlen)
{
    hw->mosi_dlen.usr_mosi_bit_len = bitlen - 1;
}

/**
 * 设置最大输入长度（从）。
 *
 * @param hw 外围寄存器的起始地址。
 * @param bitlen 输入长度，以位为单位。
 */
static inline void spi_ll_slave_set_rx_bitlen(spi_dev_t *hw, size_t bitlen)
{
    //这在esp32s2中未使用
}

/**
 * 设置最大输出长度（从）。
 *
 * @param hw 外围寄存器的起始地址。
 * @param bitlen 输出长度，以位为单位。
 */
static inline void spi_ll_slave_set_tx_bitlen(spi_dev_t *hw, size_t bitlen)
{
    //这在esp32s2中未使用
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
        /* 输出地址从最高字节的LSB开始，即addr[24]->addr[31]…addr[0]->addr[7]。因此，交换字节顺序，让LSB先发送。
        */
        addr = HAL_SWAP32(addr);
        //否则只发送addr寄存器
        hw->addr = addr;
    } else {
        // 将地址移位到addr寄存器的MSB。
        // 输出地址将从地址寄存器的MSB发送到LSB
        hw->addr = addr << (32 - addrlen);
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
    hw->slave.soft_reset = 1;
    hw->slave.soft_reset = 0;
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
    return hw->slv_rd_byte.data_bytelen * 8;
}

/*------------------------------------------------------------------------------
 * 中断
 *----------------------------------------------------------------------------*/
//帮助器宏为每个中断生成代码
#define FOR_EACH_ITEM(op, list) do { list(op) } while(0)
#define INTR_LIST(item)    \
    item(SPI_LL_INTR_TRANS_DONE,    slave.int_trans_done_en,        slave.trans_done,               slave.trans_done=0) \
    item(SPI_LL_INTR_RDBUF,         slave.int_rd_buf_done_en,       slv_rdbuf_dlen.rd_buf_done,     slv_rdbuf_dlen.rd_buf_done=0) \
    item(SPI_LL_INTR_WRBUF,         slave.int_wr_buf_done_en,       slv_wrbuf_dlen.wr_buf_done,     slv_wrbuf_dlen.wr_buf_done=0) \
    item(SPI_LL_INTR_RDDMA,         slave.int_rd_dma_done_en,       slv_rd_byte.rd_dma_done,        slv_rd_byte.rd_dma_done=0) \
    item(SPI_LL_INTR_WRDMA,         slave.int_wr_dma_done_en,       slave1.wr_dma_done,             slave1.wr_dma_done=0) \
    item(SPI_LL_INTR_IN_SUC_EOF,    dma_int_ena.in_suc_eof,         dma_int_raw.in_suc_eof,         dma_int_clr.in_suc_eof=1) \
    item(SPI_LL_INTR_OUT_EOF,       dma_int_ena.out_eof,            dma_int_raw.out_eof,            dma_int_clr.out_eof=1) \
    item(SPI_LL_INTR_OUT_TOTAL_EOF, dma_int_ena.out_total_eof,      dma_int_raw.out_total_eof,      dma_int_clr.out_total_eof=1) \
    item(SPI_LL_INTR_SEG_DONE,      slave.int_dma_seg_trans_en,     hold.dma_seg_trans_done,        hold.dma_seg_trans_done=0) \
    item(SPI_LL_INTR_IN_FULL,       dma_int_ena.infifo_full_err,    dma_int_raw.infifo_full_err,    dma_int_clr.infifo_full_err=1) \
    item(SPI_LL_INTR_OUT_EMPTY,     dma_int_ena.outfifo_empty_err,  dma_int_raw.outfifo_empty_err,  dma_int_clr.outfifo_empty_err=1) \
    item(SPI_LL_INTR_CMD7,          dma_int_ena.cmd7,               dma_int_raw.cmd7,               dma_int_clr.cmd7=1) \
    item(SPI_LL_INTR_CMD8,          dma_int_ena.cmd8,               dma_int_raw.cmd8,               dma_int_clr.cmd8=1) \
    item(SPI_LL_INTR_CMD9,          dma_int_ena.cmd9,               dma_int_raw.cmd9,               dma_int_clr.cmd9=1) \
    item(SPI_LL_INTR_CMDA,          dma_int_ena.cmda,               dma_int_raw.cmda,               dma_int_clr.cmda=1)


static inline void spi_ll_enable_intr(spi_dev_t *hw, spi_ll_intr_t intr_mask)
{
#define ENA_INTR(intr_bit, en_reg, ...) if (intr_mask & (intr_bit)) hw->en_reg = 1;
    FOR_EACH_ITEM(ENA_INTR, INTR_LIST);
#undef ENA_INTR
}

static inline void spi_ll_disable_intr(spi_dev_t *hw, spi_ll_intr_t intr_mask)
{
#define DIS_INTR(intr_bit, en_reg, ...) if (intr_mask & (intr_bit)) hw->en_reg = 0;
    FOR_EACH_ITEM(DIS_INTR, INTR_LIST);
#undef DIS_INTR
}

static inline void spi_ll_set_intr(spi_dev_t *hw, spi_ll_intr_t intr_mask)
{
#define SET_INTR(intr_bit, _, st_reg, ...) if (intr_mask & (intr_bit)) hw->st_reg = 1;
    FOR_EACH_ITEM(SET_INTR, INTR_LIST);
#undef SET_INTR
}

static inline void spi_ll_clear_intr(spi_dev_t *hw, spi_ll_intr_t intr_mask)
{
#define CLR_INTR(intr_bit, _, __, clr_reg) if (intr_mask & (intr_bit)) hw->clr_reg;
    FOR_EACH_ITEM(CLR_INTR, INTR_LIST);
#undef CLR_INTR
}

static inline bool spi_ll_get_intr(spi_dev_t *hw, spi_ll_intr_t intr_mask)
{
#define GET_INTR(intr_bit, _, st_reg, ...) if (intr_mask & (intr_bit) && hw->st_reg) return true;
    FOR_EACH_ITEM(GET_INTR, INTR_LIST);
    return false;
#undef GET_INTR
}

#undef FOR_EACH_ITEM
#undef INTR_LIST

/**
 * 禁用trans_done中断。
 *
 * @param hw 外围寄存器的起始地址。
 */
static inline void spi_ll_disable_int(spi_dev_t *hw)
{
    hw->slave.int_trans_done_en = 0;
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
    hw->slave.int_trans_done_en = 1;
}

/*------------------------------------------------------------------------------
 * 从属HD
 *----------------------------------------------------------------------------*/
static inline void spi_ll_slave_hd_set_len_cond(spi_dev_t *hw, spi_ll_trans_len_cond_t cond_mask)
{
    hw->slv_rd_byte.rdbuf_bytelen_en = (cond_mask & SPI_LL_TRANS_LEN_COND_RDBUF) ? 1 : 0;
    hw->slv_rd_byte.wrbuf_bytelen_en = (cond_mask & SPI_LL_TRANS_LEN_COND_WRBUF) ? 1 : 0;
    hw->slv_rd_byte.rddma_bytelen_en = (cond_mask & SPI_LL_TRANS_LEN_COND_RDDMA) ? 1 : 0;
    hw->slv_rd_byte.wrdma_bytelen_en = (cond_mask & SPI_LL_TRANS_LEN_COND_WRDMA) ? 1 : 0;
}

static inline int spi_ll_slave_get_rx_byte_len(spi_dev_t *hw)
{
    return hw->slv_rd_byte.data_bytelen;
}

static inline uint32_t spi_ll_slave_hd_get_last_addr(spi_dev_t *hw)
{
    return HAL_FORCE_READ_U32_REG_FIELD(hw->slave1, last_addr);
}

/*------------------------------------------------------------------------------
 * DMA：RX DMA（外设->DMA->RAM）TX DMA（RAM->DMA->外设）
 *----------------------------------------------------------------------------*/
//---------------------------------------------------RX-------------------------------------------------//
/**
 * 重置RX DMA，将从外设接收的数据存储到RAM中。
 *
 * @param dma_in  DMA外设寄存器的起始地址，将从外设接收的数据存储到RAM中。
 * @param channel DMA通道，用于芯片版本兼容性，未使用。
 */
static inline void spi_dma_ll_rx_reset(spi_dma_dev_t *dma_in, uint32_t channel)
{
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
 * 停止RX DMA。
 *
 * @param dma_in  DMA外设寄存器的起始地址，将从外设接收的数据存储到RAM中。
 * @param channel DMA通道，用于芯片版本兼容性，未使用。
 */
static inline void spi_dma_ll_rx_stop(spi_dma_dev_t *dma_in, uint32_t channel)
{
    dma_in->dma_in_link.stop = 1;
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
    //esp32s2不支持此功能
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
 * 当DMA产生in_suc_eof中断时，获取最后一个内联描述符地址
 *
 * @param dma_in  DMA外设寄存器的起始地址，将从外设接收的数据存储到RAM中。
 * @param channel DMA通道，用于芯片版本兼容性，未使用。
 * @return        地址
 */
static inline uint32_t spi_dma_ll_get_in_suc_eof_desc_addr(spi_dma_dev_t *dma_in, uint32_t channel)
{
    return dma_in->dma_in_suc_eof_des_addr;
}

//---------------------------------------------------TX-------------------------------------------------//
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
 * 停止TX DMA。
 *
 * @param dma_out DMA外设寄存器的起始地址，用于将数据从RAM传输到外设。
 * @param channel DMA通道，用于芯片版本兼容性，未使用。
 */
static inline void spi_dma_ll_tx_stop(spi_dma_dev_t *dma_out, uint32_t channel)
{
    dma_out->dma_out_link.stop = 1;
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
    dma_out->dma_conf.out_auto_wrback = enable;
}

/**
 * 当DMA产生out_eof intrupt时，获取最后一个outlink描述符地址
 *
 * @param dma_out DMA外设寄存器的起始地址，用于将数据从RAM传输到外设。
 * @param channel DMA通道，用于芯片版本兼容性，未使用。
 * @return        地址
 */
static inline uint32_t spi_dma_ll_get_out_eof_desc_addr(spi_dma_dev_t *dma_out, uint32_t channel)
{
    return dma_out->dma_out_eof_des_addr;
}

static inline void spi_dma_ll_rx_restart(spi_dma_dev_t *dma_in, uint32_t channel)
{
    dma_in->dma_in_link.restart = 1;
}

static inline void spi_dma_ll_tx_restart(spi_dma_dev_t *dma_out, uint32_t channel)
{
    dma_out->dma_out_link.restart = 1;
}

static inline void spi_dma_ll_rx_disable(spi_dma_dev_t *dma_in)
{
    dma_in->dma_in_link.dma_rx_ena = 0;
}

static inline void spi_dma_ll_tx_disable(spi_dma_dev_t *dma_out)
{
    dma_out->dma_out_link.dma_tx_ena = 0;
}

static inline bool spi_ll_tx_get_empty_err(spi_dev_t *hw)
{
    return hw->dma_int_raw.outfifo_empty_err;
}

#undef SPI_LL_RST_MASK
#undef SPI_LL_UNUSED_INT_MASK

#ifdef __cplusplus
}
#endif

