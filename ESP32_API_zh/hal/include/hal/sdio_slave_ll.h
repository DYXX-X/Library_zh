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

// ESP32 SDIO从寄存器操作的LL层
// 奇怪的是，“tx_*”regs用于主机->从属传输，而“rx_*”regs用于从属->主机传输
// 为了减少歧义，我们调用（host->slave，tx）传输接收和（slave->host，rx）传输

#pragma once

#include "hal/sdio_slave_hal.h"
#include "soc/slc_struct.h"
#include "soc/slc_reg.h"
#include "soc/host_struct.h"
#include "soc/host_reg.h"
#include "soc/hinf_struct.h"
#include "soc/lldesc.h"

///获取ESP32的唯一SLC寄存器的地址
#define sdio_slave_ll_get_slc(ID)   (&SLC)
///获取ESP32的唯一主机寄存器的地址
#define sdio_slave_ll_get_host(ID)  (&HOST)
///获取ESP32的唯一HINF寄存器的地址
#define sdio_slave_ll_get_hinf(ID)  (&HINF)


///从主机发送的通用中断掩码。
typedef enum {
    SDIO_SLAVE_LL_SLVINT_0 = BIT(0),    ///<通用中断位0。
    SDIO_SLAVE_LL_SLVINT_1 = BIT(1),
    SDIO_SLAVE_LL_SLVINT_2 = BIT(2),
    SDIO_SLAVE_LL_SLVINT_3 = BIT(3),
    SDIO_SLAVE_LL_SLVINT_4 = BIT(4),
    SDIO_SLAVE_LL_SLVINT_5 = BIT(5),
    SDIO_SLAVE_LL_SLVINT_6 = BIT(6),
    SDIO_SLAVE_LL_SLVINT_7 = BIT(7),
} sdio_slave_ll_slvint_t;

/**
 * 初始化硬件。
 *
 * @param slc SLC寄存器的地址
 */
static inline void sdio_slave_ll_init(slc_dev_t *slc)
{
    slc->slc0_int_ena.val = 0;

    slc->conf0.slc0_rx_auto_wrback = 1;
    slc->conf0.slc0_token_auto_clr = 0;
    slc->conf0.slc0_rx_loop_test = 0;
    slc->conf0.slc0_tx_loop_test = 0;

    slc->conf1.slc0_rx_stitch_en = 0;
    slc->conf1.slc0_tx_stitch_en = 0;
    slc->conf1.slc0_len_auto_clr = 0;

    slc->rx_dscr_conf.slc0_token_no_replace = 1;
}

/**
 * 设置通信时间
 *
 * @param host 主机寄存器的地址
 * @param timing 要设置的定时配置
 */
static inline void sdio_slave_ll_set_timing(host_dev_t *host, sdio_slave_timing_t timing)
{
    switch(timing) {
        case SDIO_SLAVE_TIMING_PSEND_PSAMPLE:
            host->conf.frc_sdio20 = 0x1f;
            host->conf.frc_sdio11 = 0;
            host->conf.frc_pos_samp = 0x1f;
            host->conf.frc_neg_samp = 0;
            break;
        case SDIO_SLAVE_TIMING_PSEND_NSAMPLE:
            host->conf.frc_sdio20 = 0x1f;
            host->conf.frc_sdio11 = 0;
            host->conf.frc_pos_samp = 0;
            host->conf.frc_neg_samp = 0x1f;
            break;
        case SDIO_SLAVE_TIMING_NSEND_PSAMPLE:
            host->conf.frc_sdio20 = 0;
            host->conf.frc_sdio11 = 0x1f;
            host->conf.frc_pos_samp = 0x1f;
            host->conf.frc_neg_samp = 0;
            break;
        case SDIO_SLAVE_TIMING_NSEND_NSAMPLE:
            host->conf.frc_sdio20 = 0;
            host->conf.frc_sdio11 = 0x1f;
            host->conf.frc_pos_samp = 0;
            host->conf.frc_neg_samp = 0x1f;
            break;
    }
}

/**
 * 设置主机要读取的HS支持位。
 *
 * @param hinf hinf寄存器的地址
 * @param hs 如果支持，则为true，否则为false。
 */
static inline void sdio_slave_ll_enable_hs(hinf_dev_t *hinf, bool hs)
{
    if (hs) {
        hinf->cfg_data1.sdio_ver = 0x232;
        hinf->cfg_data1.highspeed_enable = 1;
    }
}

/**
 * 设置主机要读取的IO就绪位。
 *
 * @param hinf hinf寄存器的地址
 * @param ready 如果准备就绪，则为true，否则为false。
 */
static inline void sdio_slave_ll_set_ioready(hinf_dev_t *hinf, bool ready)
{
    hinf->cfg_data1.sdio_ioready1 = (ready ? 1 : 0);   //将IO ready设置为1以停止主机使用
}

/*---------------------------------------------------------------------------
 *                  邮寄
 *--------------------------------------------------------------------------*/
/**
 * 重置发送DMA。
 *
 * @param slc SLC寄存器的地址
 */
static inline void sdio_slave_ll_send_reset(slc_dev_t *slc)
{
    //重置以刷新以前的数据包
    slc->conf0.slc0_rx_rst = 1;
    slc->conf0.slc0_rx_rst = 0;
}

/**
 * 使用给定的描述符启动发送DMA。
 *
 * @param slc SLC寄存器的地址
 * @param desc 要发送的描述符
 */
static inline void sdio_slave_ll_send_start(slc_dev_t *slc, const lldesc_t *desc)
{
    slc->slc0_rx_link.addr = (uint32_t)desc;
    slc->slc0_rx_link.start = 1;
}

/**
 * 将主机要写入的PKT_LEN寄存器写入特定值。
 *
 * @param slc SLC寄存器的地址
 * @param len 要写入的长度
 */
static inline void sdio_slave_ll_send_write_len(slc_dev_t *slc, uint32_t len)
{
    slc->slc0_len_conf.val = FIELD_TO_VALUE2(SLC_SLC0_LEN_WDATA, len) | FIELD_TO_VALUE2(SLC_SLC0_LEN_WR, 1);
}

/**
 * 读取PKT_LEN寄存器的值。寄存器可以保持不变，直到被主机读取。
 *
 * @param host 主机寄存器的地址
 * @return PKT_LEN寄存器的值。
 */
static inline uint32_t sdio_slave_ll_send_read_len(host_dev_t *host)
{
    return host->pkt_len.reg_slc0_len;
}

/**
 * 启用rx_done中断。（发送）
 *
 * @param slc SLC寄存器的地址
 * @param ena 如果启用，则为true，否则为false。
 */
static inline void sdio_slave_ll_send_part_done_intr_ena(slc_dev_t *slc, bool ena)
{
    slc->slc0_int_ena.rx_done = (ena ? 1 : 0);
}

/**
 * 清除rx_done中断。（发送）
 *
 * @param slc SLC寄存器的地址
 */
static inline void sdio_slave_ll_send_part_done_clear(slc_dev_t *slc)
{
    slc->slc0_int_clr.rx_done = 1;
}

/**
 * 检查硬件是否准备好让软件使用rx_done调用ISR。
 *
 * @param slc SLC寄存器的地址
 * @return 如果准备就绪，则为true，否则为false。
 */
static inline bool sdio_slave_ll_send_invoker_ready(slc_dev_t *slc)
{
    return slc->slc0_int_raw.rx_done;
}

/**
 * 停止发送DMA。
 *
 * @param slc SLC寄存器的地址
 */
static inline void sdio_slave_ll_send_stop(slc_dev_t *slc)
{
    slc->slc0_rx_link.stop = 1;
}

/**
 * 启用发送中断（rx_of）。
 *
 * @param slc SLC寄存器的地址
 * @param ena true表示启用，false表示禁用
 */
static inline void sdio_slave_ll_send_intr_ena(slc_dev_t *slc, bool ena)
{
    slc->slc0_int_ena.rx_eof = (ena? 1: 0);
}

/**
 * 清除发送中断（rx_of）。
 *
 * @param slc SLC寄存器的地址
 */
static inline void sdio_slave_ll_send_intr_clr(slc_dev_t *slc)
{
    slc->slc0_int_clr.rx_eof = 1;
}

/**
 * 检查发送是否完成。
 *
 * @param slc SLC寄存器的地址
 * @return 如果完成，则为true，否则为false
 */
static inline bool sdio_slave_ll_send_done(slc_dev_t *slc)
{
    return slc->slc0_int_st.rx_eof != 0;
}

/**
 * 清除主机中断，指示从机具有要读取的数据包。
 *
 * @param host 主机寄存器的地址
 */
static inline void sdio_slave_ll_send_hostint_clr(host_dev_t *host)
{
    host->slc0_int_clr.rx_new_packet = 1;
}

/*---------------------------------------------------------------------------
 *                  接收
 *--------------------------------------------------------------------------*/
/**
 * 启用接收中断。
 *
 * @param slc SLC寄存器的地址
 * @param ena
 */
static inline void sdio_slave_ll_recv_intr_ena(slc_dev_t *slc, bool ena)
{
    slc->slc0_int_ena.tx_done = (ena ? 1 : 0);
}

/**
 * 开始接收具有给定描述符的DMA。
 *
 * @param slc SLC寄存器的地址
 * @param desc 接收缓冲区的描述符。
 */
static inline void sdio_slave_ll_recv_start(slc_dev_t *slc, lldesc_t *desc)
{
    slc->slc0_tx_link.addr = (uint32_t)desc;
    slc->slc0_tx_link.start = 1;
}

/**
 * 将接收缓冲区计数器增加1。
 *
 * @param slc SLC寄存器的地址
 */
static inline void sdio_slave_ll_recv_size_inc(slc_dev_t *slc)
{
    // 字段wdata和incmore应该由同一条指令写入。
    slc->slc0_token1.val = FIELD_TO_VALUE2(SLC_SLC0_TOKEN1_WDATA, 1) | FIELD_TO_VALUE2(SLC_SLC0_TOKEN1_INC_MORE, 1);
}

/**
 * 重置接收缓冲区。
 *
 * @param slc SLC寄存器的地址
 */
static inline void sdio_slave_ll_recv_size_reset(slc_dev_t *slc)
{
    slc->slc0_token1.val = FIELD_TO_VALUE2(SLC_SLC0_TOKEN1_WDATA, 0) | FIELD_TO_VALUE2(SLC_SLC0_TOKEN1_WR, 1);
}

/**
 * 检查是否存在接收完成事件。
 *
 * @param slc SLC寄存器的地址
 * @return
 */
static inline bool sdio_slave_ll_recv_done(slc_dev_t *slc)
{
    return slc->slc0_int_raw.tx_done != 0;
}

/**
 * 清除接收完成中断。
 *
 * @param slc SLC寄存器的地址
 */
static inline void sdio_slave_ll_recv_done_clear(slc_dev_t *slc)
{
    slc->slc0_int_clr.tx_done = 1;
}

/**
 * 重新启动DMA。在将尾部描述符的下一个指针修改为附加描述符后调用。
 *
 * @param slc SLC寄存器的地址
 */
static inline void sdio_slave_ll_recv_restart(slc_dev_t *slc)
{
    slc->slc0_tx_link.restart = 1;
}

/**
 * 重置接收DMA。
 *
 * @param slc SLC寄存器的地址
 */
static inline void sdio_slave_ll_recv_reset(slc_dev_t *slc)
{
    slc->conf0.slc0_tx_rst = 1;
    slc->conf0.slc0_tx_rst = 0;
}

/**
 * 停止接收DMA。
 *
 * @param slc SLC寄存器的地址
 */
static inline void sdio_slave_ll_recv_stop(slc_dev_t *slc)
{
    slc->slc0_tx_link.stop = 1;
}

/*---------------------------------------------------------------------------
 *                  主办
 *--------------------------------------------------------------------------*/
/**
 * 获取共享通用寄存器的地址。内部的
 *
 * @param host 主机寄存器的地址
 * @param pos 寄存器的位置，0-63，24-27除外。
 * @return 寄存器的地址。
 */
static inline intptr_t sdio_slave_ll_host_get_w_reg(host_dev_t* host, int pos)
{
    return (intptr_t )&(host->conf_w0) + pos + (pos>23?4:0) + (pos>31?12:0);
}

/**
 * 获取共享通用寄存器的值。
 *
 * @param host 主机寄存器的地址
 * @param pos 寄存器的位置，0-63，24-27除外。
 * @return 寄存器的值。
 */
static inline uint8_t sdio_slave_ll_host_get_reg(host_dev_t *host, int pos)
{
    return *(uint8_t*)sdio_slave_ll_host_get_w_reg(host, pos);
}

/**
 * 设置共享通用寄存器的值。
 *
 * @param host 主机寄存器的地址
 * @param pos 寄存器的位置，0-63，24-27除外。
 * @param reg 要设置的值。
 */
static inline void sdio_slave_ll_host_set_reg(host_dev_t* host, int pos, uint8_t reg)
{
    uint32_t* addr = (uint32_t*)(sdio_slave_ll_host_get_w_reg(host, pos) & (~3));
    uint32_t shift = (pos % 4) * 8;
    *addr &= ~(0xff << shift);
    *addr |= ((uint32_t)reg << shift);
}

/**
 * 获取主机的中断启用位。
 *
 * @param host 主机寄存器的地址
 * @return 已启用中断
 */
static inline sdio_slave_hostint_t sdio_slave_ll_host_get_intena(host_dev_t* host)
{
    return host->slc0_func1_int_ena.val;
}

/**
 * 设置主机的中断启用位。
 *
 * @param host 主机寄存器的地址
 * @param mask 要启用的中断掩码
 */
static inline void sdio_slave_ll_host_set_intena(host_dev_t *host, const sdio_slave_hostint_t *mask)
{
    host->slc0_func1_int_ena.val = (*mask);
}

/**
 * 清除主机的中断位。
 * @param host 主机寄存器的地址
 * @param mask 要清除的中断掩码。
 */
static inline void sdio_slave_ll_host_intr_clear(host_dev_t* host, const sdio_slave_hostint_t *mask)
{
    host->slc0_int_clr.val = (*mask);
}

/**
 * 向主机发送通用中断。
 * @param slc SLC寄存器的地址
 * @param mask 要查找到主机的中断掩码
 */
static inline void sdio_slave_ll_host_send_int(slc_dev_t *slc, const sdio_slave_hostint_t *mask)
{
    //使用SLC中的寄存器来触发，而不是直接写入HOST寄存器
    //还不支持除主机中断之外的其他中断
    slc->intvec_tohost.slc0_intvec = (*mask);
}

/**
 * 启用一些从属中断（从主机发送）
 *
 * @param slc SLC寄存器的地址
 * @param mask 要启用的中断掩码，所有设置为0的中断将被禁用。
 */
static inline void sdio_slave_ll_slvint_set_ena(slc_dev_t *slc, const sdio_slave_ll_slvint_t *mask)
{
    //未启用其他中断
    slc->slc0_int_ena.val = (slc->slc0_int_ena.val & (~0xff)) | ((*mask) & 0xff);
}

/**
 * 获取从属中断（从主机发送）并清除它们。
 *
 * @param slc SLC寄存器的地址
 * @param out_slv_int 获取并清除从属中断的输出。
 */
static inline void sdio_slave_ll_slvint_fetch_clear(slc_dev_t *slc, sdio_slave_ll_slvint_t *out_slv_int)
{
    sdio_slave_ll_slvint_t slv_int = slc->slc0_int_st.val & 0xff;
    *out_slv_int = slv_int;
    slc->slc0_int_clr.val = slv_int;
}

