/*
 * SPDX文件版权文本：2020-2021浓缩咖啡系统（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */
#pragma once

#include <stdint.h>
#include <stdbool.h>
#include "soc/gdma_struct.h"
#include "soc/gdma_reg.h"

#ifdef __cplusplus
extern "C" {
#endif

#define GDMA_LL_GET_HW(id) (((id) == 0) ? (&GDMA) : NULL)

#define GDMA_LL_RX_EVENT_MASK       (0x06A7)
#define GDMA_LL_TX_EVENT_MASK       (0x1958)

#define GDMA_LL_EVENT_TX_FIFO_UDF   (1<<12)
#define GDMA_LL_EVENT_TX_FIFO_OVF   (1<<11)
#define GDMA_LL_EVENT_RX_FIFO_UDF   (1<<10)
#define GDMA_LL_EVENT_RX_FIFO_OVF   (1<<9)
#define GDMA_LL_EVENT_TX_TOTAL_EOF  (1<<8)
#define GDMA_LL_EVENT_RX_DESC_EMPTY (1<<7)
#define GDMA_LL_EVENT_TX_DESC_ERROR (1<<6)
#define GDMA_LL_EVENT_RX_DESC_ERROR (1<<5)
#define GDMA_LL_EVENT_TX_EOF        (1<<4)
#define GDMA_LL_EVENT_TX_DONE       (1<<3)
#define GDMA_LL_EVENT_RX_ERR_EOF    (1<<2)
#define GDMA_LL_EVENT_RX_SUC_EOF    (1<<1)
#define GDMA_LL_EVENT_RX_DONE       (1<<0)

/////////////////////////////////////通用/////////////////////////////////////////
/**
 * @brief 启用DMA信道M2M模式（TX信道n向RX信道n转发数据），默认禁用
 */
static inline void gdma_ll_enable_m2m_mode(gdma_dev_t *dev, uint32_t channel, bool enable)
{
    dev->channel[channel].in.in_conf0.mem_trans_en = enable;
    if (enable) {
        // 要启用m2m模式，tx-chan必须与rx-chan相同，并设置为有效值
        dev->channel[channel].in.in_peri_sel.sel = 0;
        dev->channel[channel].out.out_peri_sel.sel = 0;
    }
}

/**
 * @brief 启用DMA时钟门控
 */
static inline void gdma_ll_enable_clock(gdma_dev_t *dev, bool enable)
{
    dev->misc_conf.clk_en = enable;
}

///////////////////////////////////// RX /////////////////////////////////////////
/**
 * @brief 获取DMA RX信道中断状态字
 */
__attribute__((always_inline))
static inline uint32_t gdma_ll_rx_get_interrupt_status(gdma_dev_t *dev, uint32_t channel)
{
    return dev->intr[channel].st.val & GDMA_LL_RX_EVENT_MASK;
}

/**
 * @brief 启用DMA RX信道中断
 */
static inline void gdma_ll_rx_enable_interrupt(gdma_dev_t *dev, uint32_t channel, uint32_t mask, bool enable)
{
    if (enable) {
        dev->intr[channel].ena.val |= (mask & GDMA_LL_RX_EVENT_MASK);
    } else {
        dev->intr[channel].ena.val &= ~(mask & GDMA_LL_RX_EVENT_MASK);
    }
}

/**
 * @brief 清除DMA RX信道中断
 */
__attribute__((always_inline))
static inline void gdma_ll_rx_clear_interrupt_status(gdma_dev_t *dev, uint32_t channel, uint32_t mask)
{
    dev->intr[channel].clr.val = (mask & GDMA_LL_RX_EVENT_MASK);
}

/**
 * @brief 获取DMA RX信道中断状态寄存器地址
 */
static inline volatile void *gdma_ll_rx_get_interrupt_status_reg(gdma_dev_t *dev, uint32_t channel)
{
    return (volatile void *)(&dev->intr[channel].st);
}

/**
 * @brief 启用DMA RX通道以检查描述符中的所有者位，默认情况下禁用
 */
static inline void gdma_ll_rx_enable_owner_check(gdma_dev_t *dev, uint32_t channel, bool enable)
{
    dev->channel[channel].in.in_conf1.in_check_owner = enable;
}

/**
 * @brief 启用DMA RX信道突发读取数据，默认禁用
 */
static inline void gdma_ll_rx_enable_data_burst(gdma_dev_t *dev, uint32_t channel, bool enable)
{
    dev->channel[channel].in.in_conf0.in_data_burst_en = enable;
}

/**
 * @brief 启用DMA RX信道突发读取描述符链接，默认禁用
 */
static inline void gdma_ll_rx_enable_descriptor_burst(gdma_dev_t *dev, uint32_t channel, bool enable)
{
    dev->channel[channel].in.in_conf0.indscr_burst_en = enable;
}

/**
 * @brief 重置DMA RX通道FSM和FIFO指针
 */
__attribute__((always_inline))
static inline void gdma_ll_rx_reset_channel(gdma_dev_t *dev, uint32_t channel)
{
    dev->channel[channel].in.in_conf0.in_rst = 1;
    dev->channel[channel].in.in_conf0.in_rst = 0;
}

/**
 * @brief 检查DMA RX FIFO是否已满
 * @param fifo_level 仅支持级别1
 */
static inline bool gdma_ll_rx_is_fifo_full(gdma_dev_t *dev, uint32_t channel, uint32_t fifo_level)
{
    return dev->channel[channel].in.infifo_status.val & 0x01;
}

/**
 * @brief 检查DMA RX FIFO是否为空
 * @param fifo_level 仅支持级别1
 */
static inline bool gdma_ll_rx_is_fifo_empty(gdma_dev_t *dev, uint32_t channel, uint32_t fifo_level)
{
    return dev->channel[channel].in.infifo_status.val & 0x02;
}

/**
 * @brief 获取RX FIFO中的字节数
 * @param fifo_level 仅支持级别1
 */
static inline uint32_t gdma_ll_rx_get_fifo_bytes(gdma_dev_t *dev, uint32_t channel, uint32_t fifo_level)
{
    return dev->channel[channel].in.infifo_status.infifo_cnt;
}

/**
 * @brief 从DMA RX FIFO弹出数据
 */
static inline uint32_t gdma_ll_rx_pop_data(gdma_dev_t *dev, uint32_t channel)
{
    dev->channel[channel].in.in_pop.infifo_pop = 1;
    return dev->channel[channel].in.in_pop.infifo_rdata;
}

/**
 * @brief 设置RX信道的描述符链路基地址
 */
__attribute__((always_inline))
static inline void gdma_ll_rx_set_desc_addr(gdma_dev_t *dev, uint32_t channel, uint32_t addr)
{
    dev->channel[channel].in.in_link.addr = addr;
}

/**
 * @brief 开始处理RX描述符
 */
__attribute__((always_inline))
static inline void gdma_ll_rx_start(gdma_dev_t *dev, uint32_t channel)
{
    dev->channel[channel].in.in_link.start = 1;
}

/**
 * @brief 停止处理RX描述符
 */
__attribute__((always_inline))
static inline void gdma_ll_rx_stop(gdma_dev_t *dev, uint32_t channel)
{
    dev->channel[channel].in.in_link.stop = 1;
}

/**
 * @brief 在最后一个描述符之后重新启动新的内联
 */
__attribute__((always_inline))
static inline void gdma_ll_rx_restart(gdma_dev_t *dev, uint32_t channel)
{
    dev->channel[channel].in.in_link.restart = 1;
}

/**
 * @brief 启用DMA RX以在收到错误时返回当前描述符的地址
 */
static inline void gdma_ll_rx_enable_auto_return(gdma_dev_t *dev, uint32_t channel, bool enable)
{
    dev->channel[channel].in.in_link.auto_ret = enable;
}

/**
 * @brief 检查DMA RX FSM是否处于空闲状态
 */
static inline bool gdma_ll_rx_is_fsm_idle(gdma_dev_t *dev, uint32_t channel)
{
    return dev->channel[channel].in.in_link.park;
}

/**
 * @brief 获取RX成功EOF描述符的地址
 */
__attribute__((always_inline))
static inline uint32_t gdma_ll_rx_get_success_eof_desc_addr(gdma_dev_t *dev, uint32_t channel)
{
    return dev->channel[channel].in.in_suc_eof_des_addr;
}

/**
 * @brief 获取RX错误EOF描述符的地址
 */
__attribute__((always_inline))
static inline uint32_t gdma_ll_rx_get_error_eof_desc_addr(gdma_dev_t *dev, uint32_t channel)
{
    return dev->channel[channel].in.in_err_eof_des_addr;
}

/**
 * @brief 获取当前RX描述符的地址
 */
__attribute__((always_inline))
static inline uint32_t gdma_ll_rx_get_current_desc_addr(gdma_dev_t *dev, uint32_t channel)
{
    return dev->channel[channel].in.in_dscr;
}

/**
 * @brief 设置DMA RX信道的优先级
 */
static inline void gdma_ll_rx_set_priority(gdma_dev_t *dev, uint32_t channel, uint32_t prio)
{
    dev->channel[channel].in.in_pri.rx_pri = prio;
}

/**
 * @brief 将DMA RX信道连接到给定的外围设备
 */
static inline void gdma_ll_rx_connect_to_periph(gdma_dev_t *dev, uint32_t channel, int periph_id)
{
    dev->channel[channel].in.in_peri_sel.sel = periph_id;
}

///////////////////////////////////// TX /////////////////////////////////////////
/**
 * @brief 获取DMA TX信道中断状态字
 */
__attribute__((always_inline))
static inline uint32_t gdma_ll_tx_get_interrupt_status(gdma_dev_t *dev, uint32_t channel)
{
    return dev->intr[channel].st.val & GDMA_LL_TX_EVENT_MASK;
}

/**
 * @brief 启用DMA TX信道中断
 */
static inline void gdma_ll_tx_enable_interrupt(gdma_dev_t *dev, uint32_t channel, uint32_t mask, bool enable)
{
    if (enable) {
        dev->intr[channel].ena.val |= (mask & GDMA_LL_TX_EVENT_MASK);
    } else {
        dev->intr[channel].ena.val &= ~(mask & GDMA_LL_TX_EVENT_MASK);
    }
}

/**
 * @brief 清除DMA TX信道中断
 */
__attribute__((always_inline))
static inline void gdma_ll_tx_clear_interrupt_status(gdma_dev_t *dev, uint32_t channel, uint32_t mask)
{
    dev->intr[channel].clr.val = (mask & GDMA_LL_TX_EVENT_MASK);
}

/**
 * @brief 获取DMA TX信道中断状态寄存器地址
 */
static inline volatile void *gdma_ll_tx_get_interrupt_status_reg(gdma_dev_t *dev, uint32_t channel)
{
    return (volatile void *)(&dev->intr[channel].st);
}

/**
 * @brief 启用DMA TX信道以检查描述符中的所有者位，默认禁用
 */
static inline void gdma_ll_tx_enable_owner_check(gdma_dev_t *dev, uint32_t channel, bool enable)
{
    dev->channel[channel].out.out_conf1.out_check_owner = enable;
}

/**
 * @brief 启用DMA TX信道突发发送数据，默认禁用
 */
static inline void gdma_ll_tx_enable_data_burst(gdma_dev_t *dev, uint32_t channel, bool enable)
{
    dev->channel[channel].out.out_conf0.out_data_burst_en = enable;
}

/**
 * @brief 启用DMA TX信道突发读取描述符链接，默认禁用
 */
static inline void gdma_ll_tx_enable_descriptor_burst(gdma_dev_t *dev, uint32_t channel, bool enable)
{
    dev->channel[channel].out.out_conf0.outdscr_burst_en = enable;
}

/**
 * @brief 设置TX信道EOF模式
 */
static inline void gdma_ll_tx_set_eof_mode(gdma_dev_t *dev, uint32_t channel, uint32_t mode)
{
    dev->channel[channel].out.out_conf0.out_eof_mode = mode;
}

/**
 * @brief 在发送所有数据后，启用DMA TX通道自动将结果写回描述符，默认情况下禁用
 */
static inline void gdma_ll_tx_enable_auto_write_back(gdma_dev_t *dev, uint32_t channel, bool enable)
{
    dev->channel[channel].out.out_conf0.out_auto_wrback = enable;
}

/**
 * @brief 重置DMA TX通道FSM和FIFO指针
 */
__attribute__((always_inline))
static inline void gdma_ll_tx_reset_channel(gdma_dev_t *dev, uint32_t channel)
{
    dev->channel[channel].out.out_conf0.out_rst = 1;
    dev->channel[channel].out.out_conf0.out_rst = 0;
}

/**
 * @brief 检查DMA TX FIFO是否已满
 * @param fifo_level 仅支持级别1
 */
static inline bool gdma_ll_tx_is_fifo_full(gdma_dev_t *dev, uint32_t channel, uint32_t fifo_level)
{
    return dev->channel[channel].out.outfifo_status.val & 0x01;
}

/**
 * @brief 检查DMA TX FIFO是否为空
 * @param fifo_level 仅支持级别1
 */
static inline bool gdma_ll_tx_is_fifo_empty(gdma_dev_t *dev, uint32_t channel, uint32_t fifo_level)
{
    return dev->channel[channel].out.outfifo_status.val & 0x02;
}

/**
 * @brief 获取TX FIFO中的字节数
 * @param fifo_level 仅支持级别1
 */
static inline uint32_t gdma_ll_tx_get_fifo_bytes(gdma_dev_t *dev, uint32_t channel, uint32_t fifo_level)
{
    return dev->channel[channel].out.outfifo_status.outfifo_cnt;
}

/**
 * @brief 将数据推入DMA TX FIFO
 */
static inline void gdma_ll_tx_push_data(gdma_dev_t *dev, uint32_t channel, uint32_t data)
{
    dev->channel[channel].out.out_push.outfifo_wdata = data;
    dev->channel[channel].out.out_push.outfifo_push = 1;
}

/**
 * @brief 设置TX信道的描述符链路基地址
 */
__attribute__((always_inline))
static inline void gdma_ll_tx_set_desc_addr(gdma_dev_t *dev, uint32_t channel, uint32_t addr)
{
    dev->channel[channel].out.out_link.addr = addr;
}

/**
 * @brief 开始处理TX描述符
 */
__attribute__((always_inline))
static inline void gdma_ll_tx_start(gdma_dev_t *dev, uint32_t channel)
{
    dev->channel[channel].out.out_link.start = 1;
}

/**
 * @brief 停止处理TX描述符
 */
__attribute__((always_inline))
static inline void gdma_ll_tx_stop(gdma_dev_t *dev, uint32_t channel)
{
    dev->channel[channel].out.out_link.stop = 1;
}

/**
 * @brief 在最后一个描述符之后重新启动新的outlink
 */
__attribute__((always_inline))
static inline void gdma_ll_tx_restart(gdma_dev_t *dev, uint32_t channel)
{
    dev->channel[channel].out.out_link.restart = 1;
}

/**
 * @brief 检查DMA TX FSM是否处于空闲状态
 */
static inline bool gdma_ll_tx_is_fsm_idle(gdma_dev_t *dev, uint32_t channel)
{
    return dev->channel[channel].out.out_link.park;
}

/**
 * @brief 获取TX EOF描述符的地址
 */
__attribute__((always_inline))
static inline uint32_t gdma_ll_tx_get_eof_desc_addr(gdma_dev_t *dev, uint32_t channel)
{
    return dev->channel[channel].out.out_eof_des_addr;
}

/**
 * @brief 获取当前TX描述符的地址
 */
__attribute__((always_inline))
static inline uint32_t gdma_ll_tx_get_current_desc_addr(gdma_dev_t *dev, uint32_t channel)
{
    return dev->channel[channel].out.out_dscr;
}

/**
 * @brief 设置DMA TX信道的优先级
 */
static inline void gdma_ll_tx_set_priority(gdma_dev_t *dev, uint32_t channel, uint32_t prio)
{
    dev->channel[channel].out.out_pri.tx_pri = prio;
}

/**
 * @brief 将DMA TX信道连接到给定的外围设备
 */
static inline void gdma_ll_tx_connect_to_periph(gdma_dev_t *dev, uint32_t channel, int periph_id)
{
    dev->channel[channel].out.out_peri_sel.sel = periph_id;
}

#ifdef __cplusplus
}
#endif

