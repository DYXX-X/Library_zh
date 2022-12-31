// 版权所有2020 Espressif Systems（上海）私人有限公司
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

// I2C寄存器操作的LL层

#pragma once

#include "hal/misc.h"
#include "soc/i2c_periph.h"
#include "soc/soc_caps.h"
#include "soc/i2c_struct.h"
#include "hal/i2c_types.h"

#ifdef __cplusplus
extern "C" {
#endif

#define I2C_LL_INTR_MASK          (0x3fff) /*!< I2C全中断位图*/
/**
 * @brief I2C硬件cmd寄存器字段。
 */
typedef union {
    struct {
        uint32_t byte_num:    8,
                 ack_en:      1,
                 ack_exp:     1,
                 ack_val:     1,
                 op_code:     3,
                 reserved14: 17,
                 done:        1;
    };
    uint32_t val;
} i2c_hw_cmd_t;

/**
 * @brief I2C中断事件
 */
typedef enum {
    I2C_INTR_EVENT_ERR,
    I2C_INTR_EVENT_ARBIT_LOST,   /*!< I2C仲裁丢失事件*/
    I2C_INTR_EVENT_NACK,         /*!< I2C NACK事件*/
    I2C_INTR_EVENT_TOUT,         /*!< I2C超时事件*/
    I2C_INTR_EVENT_END_DET,      /*!< I2C结束检测事件*/
    I2C_INTR_EVENT_TRANS_DONE,   /*!< I2C传输完成事件*/
    I2C_INTR_EVENT_RXFIFO_FULL,  /*!< I2C rxfifo完整事件*/
    I2C_INTR_EVENT_TXFIFO_EMPTY, /*!< I2C txfifo空事件*/
} i2c_intr_event_t;

/**
 * @brief 用于计算I2C总线定时的数据结构。
 */
typedef struct {
    uint16_t clkm_div;          /*!< I2C核心时钟分频器*/
    uint16_t scl_low;           /*!< I2C scl低周期*/
    uint16_t scl_high;          /*!< I2C症状高期*/
    uint16_t scl_wait_high;     /*!< I2C scl等待高时段*/
    uint16_t sda_hold;          /*!< I2C scl低周期*/
    uint16_t sda_sample;        /*!< I2C sda采样时间*/
    uint16_t setup;             /*!< I2C启动和停止条件设置周期*/
    uint16_t hold;              /*!< I2C启动和停止条件保持期*/
    uint16_t tout;              /*!< I2C总线超时时间*/
} i2c_clk_cal_t;

// I2C操作模式命令
#define I2C_LL_CMD_RESTART    6    /*!<I2C重启命令*/
#define I2C_LL_CMD_WRITE      1    /*!<I2C写入命令*/
#define I2C_LL_CMD_READ       3    /*!<I2C读取命令*/
#define I2C_LL_CMD_STOP       2    /*!<I2C停止命令*/
#define I2C_LL_CMD_END        4    /*!<I2C结束命令*/

// 获取I2C硬件实例
#define I2C_LL_GET_HW(i2c_num)        (((i2c_num) == 0) ? &I2C0 : &I2C1)
// 获取I2C硬件FIFO地址
#define I2C_LL_GET_FIFO_ADDR(i2c_num) (I2C_DATA_APB_REG(i2c_num))
// I2C主TX中断位图
#define I2C_LL_MASTER_TX_INT          (I2C_NACK_INT_ENA_M|I2C_TIME_OUT_INT_ENA_M|I2C_TRANS_COMPLETE_INT_ENA_M|I2C_ARBITRATION_LOST_INT_ENA_M|I2C_END_DETECT_INT_ENA_M)
// I2C主RX中断位图
#define I2C_LL_MASTER_RX_INT          (I2C_TIME_OUT_INT_ENA_M|I2C_TRANS_COMPLETE_INT_ENA_M|I2C_ARBITRATION_LOST_INT_ENA_M|I2C_END_DETECT_INT_ENA_M)
// I2C从属TX中断位图
#define I2C_LL_SLAVE_TX_INT           (I2C_TXFIFO_WM_INT_ENA_M)
// I2C从属RX中断位图
#define I2C_LL_SLAVE_RX_INT           (I2C_RXFIFO_WM_INT_ENA_M | I2C_TRANS_COMPLETE_INT_ENA_M)
// I2C源时钟
#define I2C_LL_CLK_SRC_FREQ(src_clk)  (((src_clk) == I2C_SCLK_RTC) ? 8*1000*1000 : 40*1000*1000); // 另一个时钟是XTAL时钟
// I2C最大超时值
#define I2C_LL_MAX_TIMEOUT I2C_TIME_OUT_VALUE_V

/**
 * @brief  计算I2C总线频率注意，时钟精度受外部上拉电阻器的影响，这里我们尝试计算接近所需时钟的配置参数。但是在I2C通信中，时钟精度不是很重要。
 *
 * @param  source_clk I2C源时钟
 * @param  bus_freq I2C总线频率
 * @param  clk_cal 接受时钟配置的指针
 *
 * @return 没有一个
 */
static inline void i2c_ll_cal_bus_clk(uint32_t source_clk, uint32_t bus_freq, i2c_clk_cal_t *clk_cal)
{
    uint32_t clkm_div = source_clk / (bus_freq * 1024) +1;
    uint32_t sclk_freq = source_clk / clkm_div;
    uint32_t half_cycle = sclk_freq / bus_freq / 2;
    //SCL
    clk_cal->clkm_div = clkm_div;
    clk_cal->scl_low = half_cycle;
    // 默认值，scl_wait_high<scl_high
    clk_cal->scl_high = (bus_freq <= 50000) ?  half_cycle : (half_cycle / 5 * 4 + 4);
    clk_cal->scl_wait_high = half_cycle - clk_cal->scl_high;
    clk_cal->sda_hold = half_cycle / 2;
    // scl_wait_high<sda_sample<=scl_high
    clk_cal->sda_sample = half_cycle / 2;
    clk_cal->setup = half_cycle;
    clk_cal->hold = half_cycle;
    //默认情况下，我们将超时值设置为大约10个总线周期
    // log（20*半周期）/log（2）=log（半周期）/log（2）+log（20）/log
    clk_cal->tout = (int)(sizeof(half_cycle) * 8 - __builtin_clz(5 * half_cycle)) + 2;
}

/**
 * @brief  更新I2C配置
 *
 * @param  hw 外围寄存器的起始地址
 *
 * @return 没有一个
 */
static inline void i2c_ll_update(i2c_dev_t *hw)
{
    hw->ctr.conf_upgate = 1;
}

/**
 * @brief  配置I2C总线定时相关寄存器。
 *
 * @param  hw 外围寄存器的起始地址
 * @param  bus_cfg 指向保存寄存器配置的数据结构的指针。
 *
 * @return 没有一个
 */
static inline void i2c_ll_set_bus_timing(i2c_dev_t *hw, i2c_clk_cal_t *bus_cfg)
{
    HAL_FORCE_MODIFY_U32_REG_FIELD(hw->clk_conf, sclk_div_num, bus_cfg->clkm_div - 1);
    //scl期
    hw->scl_low_period.scl_low_period = bus_cfg->scl_low - 1;
    hw->scl_high_period.scl_high_period = bus_cfg->scl_high;
    //sda样本
    hw->sda_hold.sda_hold_time = bus_cfg->sda_hold;
    hw->sda_sample.sda_sample_time = bus_cfg->sda_sample;
    //设置
    hw->scl_rstart_setup.scl_rstart_setup_time = bus_cfg->setup;
    hw->scl_stop_setup.scl_stop_setup_time = bus_cfg->setup;
    //持有
    hw->scl_start_hold.scl_start_hold_time = bus_cfg->hold - 1;
    hw->scl_stop_hold.scl_stop_hold_time = bus_cfg->hold;
    hw->to.time_out_value = bus_cfg->tout;
    hw->to.time_out_en = 1;
}

/**
 * @brief  重置I2C txFIFO
 *
 * @param  hw 外围寄存器的起始地址
 *
 * @return 没有一个
 */
static inline void i2c_ll_txfifo_rst(i2c_dev_t *hw)
{
    hw->fifo_conf.tx_fifo_rst = 1;
    hw->fifo_conf.tx_fifo_rst = 0;
}

/**
 * @brief  重置I2C rxFIFO
 *
 * @param  hw 外围寄存器的起始地址
 *
 * @return 没有一个
 */
static inline void i2c_ll_rxfifo_rst(i2c_dev_t *hw)
{
    hw->fifo_conf.rx_fifo_rst = 1;
    hw->fifo_conf.rx_fifo_rst = 0;
}

/**
 * @brief  配置I2C SCL计时
 *
 * @param  hw 外围寄存器的起始地址
 * @param  high_period I2C SCL高周期（在核心时钟周期中，high_period>2）
 * @param  low_period I2C SCL低周期（在核心时钟周期中，low_period>1）
 *
 * @return 没有一个
 */
static inline void i2c_ll_set_scl_timing(i2c_dev_t *hw, int high_period, int low_period)
{
    int high_period_output = high_period - 10; // 漏极开路输出+内部上拉（约50K）的上升沿缓慢
    hw->scl_low_period.scl_low_period = low_period - 1;
    hw->scl_high_period.scl_high_period = high_period_output;
    hw->scl_high_period.scl_wait_high_period = high_period - high_period_output;
}

/**
 * @brief  清除I2C中断状态
 *
 * @param  hw 外围寄存器的起始地址
 * @param  mask 需要清除中断掩码
 *
 * @return 没有一个
 */
static inline void i2c_ll_clr_intsts_mask(i2c_dev_t *hw, uint32_t mask)
{
    hw->int_clr.val = mask;
}

/**
 * @brief  启用I2C中断
 *
 * @param  hw 外围寄存器的起始地址
 * @param  mask 需要启用中断掩码
 *
 * @return 没有一个
 */
static inline void i2c_ll_enable_intr_mask(i2c_dev_t *hw, uint32_t mask)
{
    hw->int_ena.val |= mask;
}

/**
 * @brief  禁用I2C中断
 *
 * @param  hw 外围寄存器的起始地址
 * @param  mask 需要禁用中断掩码
 *
 * @return 没有一个
 */
static inline void i2c_ll_disable_intr_mask(i2c_dev_t *hw, uint32_t mask)
{
    hw->int_ena.val &= (~mask);
}

/**
 * @brief  获取I2C中断状态
 *
 * @param  hw 外围寄存器的起始地址
 *
 * @return I2C中断状态
 */
static inline uint32_t i2c_ll_get_intsts_mask(i2c_dev_t *hw)
{
    return hw->int_status.val;
}

/**
 * @brief  配置I2C内存访问模式、FIFO模式或非FIFO模式
 *
 * @param  hw 外围寄存器的起始地址
 * @param  fifo_mode_en 设置为true以启用FIFO访问模式，否则设置为false
 *
 * @return 没有一个
 */
static inline void i2c_ll_set_fifo_mode(i2c_dev_t *hw, bool fifo_mode_en)
{
    hw->fifo_conf.nonfifo_en = fifo_mode_en ? 0 : 1;
}

/**
 * @brief  配置I2C超时
 *
 * @param  hw 外围寄存器的起始地址
 * @param  tout_num 需要设置I2C超时值（核心时钟周期中的2^tout）
 *
 * @return 没有一个
 */
static inline void i2c_ll_set_tout(i2c_dev_t *hw, int tout)
{
    hw->to.time_out_value = tout;
}

/**
 * @brief  配置I2C从属地址
 *
 * @param  hw 外围寄存器的起始地址
 * @param  slave_addr 需要设置I2C从属地址
 * @param  addr_10bit_en 设置为true以启用10位从地址模式，设置为false以启用7位地址模式
 *
 * @return 没有一个
 */
static inline void i2c_ll_set_slave_addr(i2c_dev_t *hw, uint16_t slave_addr, bool addr_10bit_en)
{
    hw->slave_addr.slave_addr = slave_addr;
    hw->slave_addr.addr_10bit_en = addr_10bit_en;
}

/**
 * @brief 写入I2C硬件命令寄存器
 *
 * @param  hw 外围寄存器的起始地址
 * @param  cmd I2C硬件命令
 * @param  cmd_idx 命令寄存器的索引应小于16
 *
 * @return 没有一个
 */
static inline void i2c_ll_write_cmd_reg(i2c_dev_t *hw, i2c_hw_cmd_t cmd, int cmd_idx)
{
    _Static_assert(sizeof(i2c_comd0_reg_t) == sizeof(i2c_hw_cmd_t),
                   "i2c_comdX_reg_t structure size must be equal to i2c_hw_cmd_t structure size");
    volatile i2c_hw_cmd_t* commands = (volatile i2c_hw_cmd_t*) &hw->comd0;
    commands[cmd_idx].val = cmd.val;
}

/**
 * @brief 配置I2C启动定时
 *
 * @param  hw 外围寄存器的起始地址
 * @param  start_setup 启动条件设置周期（核心时钟周期）
 * @param  start_hold 启动条件保持周期（在核心时钟周期中）
 *
 * @return 没有一个
 */
static inline void i2c_ll_set_start_timing(i2c_dev_t *hw, int start_setup, int start_hold)
{
    hw->scl_rstart_setup.scl_rstart_setup_time = start_setup;
    hw->scl_start_hold.scl_start_hold_time = start_hold - 1;
}

/**
 * @brief 配置I2C停止计时
 *
 * @param  hw 外围寄存器的起始地址
 * @param  stop_setup 停止条件设置周期（核心时钟周期）
 * @param  stop_hold 停止条件保持周期（在核心时钟周期中）
 *
 * @return 没有一个
 */
static inline void i2c_ll_set_stop_timing(i2c_dev_t *hw, int stop_setup, int stop_hold)
{
    hw->scl_stop_setup.scl_stop_setup_time = stop_setup;
    hw->scl_stop_hold.scl_stop_hold_time = stop_hold;
}

/**
 * @brief 配置I2C停止计时
 *
 * @param  hw 外围寄存器的起始地址
 * @param  sda_sample SDA采样时间（核心时钟周期）
 * @param  sda_hold SDA保持时间（核心时钟周期）
 *
 * @return 没有一个
 */
static inline void i2c_ll_set_sda_timing(i2c_dev_t *hw, int sda_sample, int sda_hold)
{
    hw->sda_hold.sda_hold_time = sda_hold;
    hw->sda_sample.sda_sample_time = sda_sample;
}

/**
 * @brief  设置I2C txFIFO空阈值
 *
 * @param  hw 外围寄存器的起始地址
 * @param  empty_thr txFIFO空阈值
 *
 * @return 没有一个
 */
static inline void i2c_ll_set_txfifo_empty_thr(i2c_dev_t *hw, uint8_t empty_thr)
{
    hw->fifo_conf.txfifo_wm_thrhd = empty_thr;
}

/**
 * @brief  设置I2C rxFIFO满阈值
 *
 * @param  hw 外围寄存器的起始地址
 * @param  full_thr rxFIFO满阈值
 *
 * @return 没有一个
 */
static inline void i2c_ll_set_rxfifo_full_thr(i2c_dev_t *hw, uint8_t full_thr)
{
    hw->fifo_conf.rxfifo_wm_thrhd = full_thr;
}

/**
 * @brief  设置I2C数据模式、LSB或MSB
 *
 * @param  hw 外围寄存器的起始地址
 * @param  tx_mode Tx数据位模式
 * @param  rx_mode Rx数据位模式
 *
 * @return 没有一个
 */
static inline void i2c_ll_set_data_mode(i2c_dev_t *hw, i2c_trans_mode_t tx_mode, i2c_trans_mode_t rx_mode)
{
    hw->ctr.tx_lsb_first = tx_mode;
    hw->ctr.rx_lsb_first = rx_mode;
}

/**
 * @brief  获取I2C数据模式
 *
 * @param  hw 外围寄存器的起始地址
 * @param  tx_mode 接受接收字节模式的指针
 * @param  rx_mode 用于接受发送字节模式的指针
 *
 * @return 没有一个
 */
static inline void i2c_ll_get_data_mode(i2c_dev_t *hw, i2c_trans_mode_t *tx_mode, i2c_trans_mode_t *rx_mode)
{
    *tx_mode = hw->ctr.tx_lsb_first;
    *rx_mode = hw->ctr.rx_lsb_first;
}

/**
 * @brief 获取I2C sda定时配置
 *
 * @param  hw 外围寄存器的起始地址
 * @param  sda_sample 用于接受SDA采样定时配置的指针
 * @param  sda_hold 用于接受SDA保持定时配置的指针
 *
 * @return 没有一个
 */
static inline void i2c_ll_get_sda_timing(i2c_dev_t *hw, int *sda_sample, int *sda_hold)
{
    *sda_hold = hw->sda_hold.sda_hold_time;
    *sda_sample = hw->sda_sample.sda_sample_time;
}

/**
 * @brief 获取I2C硬件版本
 *
 * @param  hw 外围寄存器的起始地址
 *
 * @return I2C硬件版本
 */
static inline uint32_t i2c_ll_get_hw_version(i2c_dev_t *hw)
{
    return hw->date.val;
}

/**
 * @brief  检查I2C总线是否繁忙
 *
 * @param  hw 外围寄存器的起始地址
 *
 * @return 如果I2C状态机忙，则为True，否则将返回false
 */
static inline bool i2c_ll_is_bus_busy(i2c_dev_t *hw)
{
    return hw->sr.bus_busy;
}

/**
 * @brief  检查I2C是否为主模式
 *
 * @param  hw 外围寄存器的起始地址
 *
 * @return 如果I2C为主模式，则为True，否则将返回false
 */
static inline bool i2c_ll_is_master_mode(i2c_dev_t *hw)
{
    return hw->ctr.ms_mode;
}

/**
 * @brief 获取rxFIFO可读长度
 *
 * @param  hw 外围寄存器的起始地址
 *
 * @return RxFIFO可读长度
 */
static inline uint32_t i2c_ll_get_rxfifo_cnt(i2c_dev_t *hw)
{
    return hw->sr.rxfifo_cnt;
}

/**
 * @brief  获取I2C txFIFO可写长度
 *
 * @param  hw 外围寄存器的起始地址
 *
 * @return TxFIFO可写长度
 */
static inline uint32_t i2c_ll_get_txfifo_len(i2c_dev_t *hw)
{
    return SOC_I2C_FIFO_LEN - hw->sr.txfifo_cnt;
}

/**
 * @brief 获取I2C超时配置
 *
 * @param  hw 外围寄存器的起始地址
 *
 * @return I2C超时值
 */
static inline uint32_t i2c_ll_get_tout(i2c_dev_t *hw)
{
    return hw->to.time_out_value;
}

/**
 * @brief  启动I2C传输
 *
 * @param  hw 外围寄存器的起始地址
 *
 * @return 没有一个
 */
static inline void i2c_ll_trans_start(i2c_dev_t *hw)
{
    hw->ctr.trans_start = 1;
}

/**
 * @brief 获取I2C启动定时配置
 *
 * @param  hw 外围寄存器的起始地址
 * @param  setup_time 用于接受开始条件设置周期的指针
 * @param  hold_time 接受开始条件保持期的指针
 *
 * @return 没有一个
 */
static inline void i2c_ll_get_start_timing(i2c_dev_t *hw, int *setup_time, int *hold_time)
{
    *setup_time = hw->scl_rstart_setup.scl_rstart_setup_time;
    *hold_time = hw->scl_start_hold.scl_start_hold_time + 1;
}

/**
 * @brief  获取I2C停止计时配置
 *
 * @param  hw 外围寄存器的起始地址
 * @param  setup_time 用于接受停止条件设置周期的指针
 * @param  hold_time 用于接受停止条件保持期的指针
 *
 * @return 没有一个
 */
static inline void i2c_ll_get_stop_timing(i2c_dev_t *hw, int *setup_time, int *hold_time)
{
    *setup_time = hw->scl_stop_setup.scl_stop_setup_time;
    *hold_time = hw->scl_stop_hold.scl_stop_hold_time;
}

/**
 * @brief  获取I2C SCL定时配置
 *
 * @param  hw 外围寄存器的起始地址
 * @param  high_period 用于接受SCL高时段的指针
 * @param  low_period 用于接受SCL低时段的指针
 *
 * @return 没有一个
 */
static inline void i2c_ll_get_scl_timing(i2c_dev_t *hw, int *high_period, int *low_period)
{
    *high_period = hw->scl_high_period.scl_high_period + hw->scl_high_period.scl_wait_high_period;
    *low_period = hw->scl_low_period.scl_low_period + 1;
}

/**
 * @brief  写入I2C硬件txFIFO
 *
 * @param  hw 外围寄存器的起始地址
 * @param  ptr 指向数据缓冲区的指针
 * @param  len 需要写入的数据量
 *
 * @return 没有一个
 */
static inline void i2c_ll_write_txfifo(i2c_dev_t *hw, uint8_t *ptr, uint8_t len)
{
    for (int i = 0; i< len; i++) {
        HAL_FORCE_MODIFY_U32_REG_FIELD(hw->data, fifo_rdata, ptr[i]);
    }
}

/**
 * @brief  读取I2C硬件rxFIFO
 *
 * @param  hw 外围寄存器的起始地址
 * @param  ptr 指向数据缓冲区的指针
 * @param  len 需要读取的数据量
 *
 * @return 没有一个
 */
static inline void i2c_ll_read_rxfifo(i2c_dev_t *hw, uint8_t *ptr, uint8_t len)
{
    for(int i = 0; i < len; i++) {
        ptr[i] = HAL_FORCE_READ_U32_REG_FIELD(hw->data, fifo_rdata);
    }
}

/**
 * @brief  配置I2C硬件过滤器
 *
 * @param  hw 外围寄存器的起始地址
 * @param  filter_num 如果线路上的故障周期小于此值，则可以将其过滤掉。如果“filter_num==0”，则将禁用该过滤器
 *
 * @return 没有一个
 */
static inline void i2c_ll_set_filter(i2c_dev_t *hw, uint8_t filter_num)
{
    if (filter_num > 0) {
        hw->filter_cfg.scl_filter_thres = filter_num;
        hw->filter_cfg.sda_filter_thres = filter_num;
        hw->filter_cfg.scl_filter_en = 1;
        hw->filter_cfg.sda_filter_en = 1;
    } else {
        hw->filter_cfg.scl_filter_en = 0;
        hw->filter_cfg.sda_filter_en = 0;
    }
}

/**
 * @brief  获取I2C硬件过滤器配置
 *
 * @param  hw 外围寄存器的起始地址
 *
 * @return 硬件过滤器配置
 */
static inline uint8_t i2c_ll_get_filter(i2c_dev_t *hw)
{
    return hw->filter_cfg.scl_filter_thres;
}

/**
 * @brief  启用I2C主TX中断
 *
 * @param  hw 外围寄存器的起始地址
 *
 * @return 没有一个
 */
static inline void i2c_ll_master_enable_tx_it(i2c_dev_t *hw)
{
    hw->int_clr.val = ~0;
    hw->int_ena.val =  I2C_LL_MASTER_TX_INT;
}

/**
 * @brief  启用I2C主RX中断
 *
 * @param  hw 外围寄存器的起始地址
 *
 * @return 没有一个
 */
static inline void i2c_ll_master_enable_rx_it(i2c_dev_t *hw)
{
    hw->int_clr.val = ~0;
    hw->int_ena.val = I2C_LL_MASTER_RX_INT;
}

/**
 * @brief  禁用I2C主TX中断
 *
 * @param  hw 外围寄存器的起始地址
 *
 * @return 没有一个
 */
static inline void i2c_ll_master_disable_tx_it(i2c_dev_t *hw)
{
    hw->int_ena.val &= (~I2C_LL_MASTER_TX_INT);
}

/**
 * @brief  禁用I2C主RX中断
 *
 * @param  hw 外围寄存器的起始地址
 *
 * @return 没有一个
 */
static inline void i2c_ll_master_disable_rx_it(i2c_dev_t *hw)
{
    hw->int_ena.val &= (~I2C_LL_MASTER_RX_INT);
}

/**
 * @brief  清除I2C主TX中断状态寄存器
 *
 * @param  hw 外围寄存器的起始地址
 *
 * @return 没有一个
 */
static inline void i2c_ll_master_clr_tx_it(i2c_dev_t *hw)
{
    hw->int_clr.val = I2C_LL_MASTER_TX_INT;
}

/**
 * @brief  清除I2C主RX中断状态寄存器
 *
 * @param  hw 外围寄存器的起始地址
 *
 * @return 没有一个
 */
static inline void i2c_ll_master_clr_rx_it(i2c_dev_t *hw)
{
    hw->int_clr.val = I2C_LL_MASTER_RX_INT;
}

/**
 * @brief
 *
 * @param  hw 外围寄存器的起始地址
 *
 * @return 没有一个
 */
static inline void i2c_ll_slave_enable_tx_it(i2c_dev_t *hw)
{
    hw->int_ena.val |= I2C_LL_SLAVE_TX_INT;
}

/**
 * @brief 启用I2C从属RX中断
 *
 * @param  hw 外围寄存器的起始地址
 *
 * @return 没有一个
 */
static inline void i2c_ll_slave_enable_rx_it(i2c_dev_t *hw)
{
    hw->int_ena.val |= I2C_LL_SLAVE_RX_INT;
}

/**
 * @brief 禁用I2C从属TX中断
 *
 * @param  hw 外围寄存器的起始地址
 *
 * @return 没有一个
 */
static inline void i2c_ll_slave_disable_tx_it(i2c_dev_t *hw)
{
    hw->int_ena.val &= (~I2C_LL_SLAVE_TX_INT);
}

/**
 * @brief  禁用I2C从属RX中断
 *
 * @param  hw 外围寄存器的起始地址
 *
 * @return 没有一个
 */
static inline void i2c_ll_slave_disable_rx_it(i2c_dev_t *hw)
{
    hw->int_ena.val &= (~I2C_LL_SLAVE_RX_INT);
}

/**
 * @brief  清除I2C从TX中断状态寄存器
 *
 * @param  hw 外围寄存器的起始地址
 *
 * @return 没有一个
 */
static inline void i2c_ll_slave_clr_tx_it(i2c_dev_t *hw)
{
    hw->int_clr.val = I2C_LL_SLAVE_TX_INT;
}

/**
 * @brief 清除I2C从属RX中断状态寄存器。
 *
 * @param  hw 外围寄存器的起始地址
 *
 * @return 没有一个
 */
static inline void i2c_ll_slave_clr_rx_it(i2c_dev_t *hw)
{
    hw->int_clr.val = I2C_LL_SLAVE_RX_INT;
}

/**
 * @brief 恢复I2C主FSM。当主FSM卡住时，调用此函数重置FSM
 *
 * @param  hw 外围寄存器的起始地址
 *
 * @return 没有一个
 */
static inline void i2c_ll_master_fsm_rst(i2c_dev_t *hw)
{
    hw->ctr.fsm_rst = 1;
}

/**
 * @brief 清除I2C总线，当从设备陷入死锁并持续拉低总线时，主设备可以控制SCL总线生成9个CLK。
 *
 * 注意：主机无法检测是否发生死锁，但当生成scl_st_to中断时，可能会发生死锁。
 *
 * @param  hw 外围寄存器的起始地址
 *
 * @return 没有一个
 */
static inline void i2c_ll_master_clr_bus(i2c_dev_t *hw)
{
    hw->scl_sp_conf.scl_rst_slv_num = 9;
    hw->scl_sp_conf.scl_rst_slv_en = 0;
    hw->ctr.conf_upgate = 1;
    hw->scl_sp_conf.scl_rst_slv_en = 1;
}

/**
 * @brief 设置I2C源时钟
 *
 * @param  hw 外围寄存器的起始地址
 * @param  src_clk I2C的源时钟
 *
 * @return 没有一个
 */
static inline void i2c_ll_set_source_clk(i2c_dev_t *hw, i2c_sclk_t src_clk)
{
    hw->clk_conf.sclk_sel = (src_clk == I2C_SCLK_RTC) ? 1 : 0;
}

/**
 * @brief  获取I2C主中断事件
 *
 * @param  hw 外围寄存器的起始地址
 * @param  event 接受中断事件的指针
 *
 * @return 没有一个
 */
static inline void i2c_ll_master_get_event(i2c_dev_t *hw, i2c_intr_event_t *event)
{
    typeof(hw->int_status) int_sts = hw->int_status;
    if (int_sts.arbitration_lost_int_st) {
        *event = I2C_INTR_EVENT_ARBIT_LOST;
    } else if (int_sts.nack_int_st) {
        *event = I2C_INTR_EVENT_NACK;
    } else if (int_sts.time_out_int_st) {
        *event = I2C_INTR_EVENT_TOUT;
    } else if (int_sts.end_detect_int_st) {
        *event = I2C_INTR_EVENT_END_DET;
    } else if (int_sts.trans_complete_int_st) {
        *event = I2C_INTR_EVENT_TRANS_DONE;
    } else {
        *event = I2C_INTR_EVENT_ERR;
    }
}

/**
 * @brief  获取I2C从属中断事件
 *
 * @param  hw 外围寄存器的起始地址
 * @param  event 接受中断事件的指针
 *
 * @return 没有一个
 */
static inline void i2c_ll_slave_get_event(i2c_dev_t *hw, i2c_intr_event_t *event)
{
    typeof(hw->int_status) int_sts = hw->int_status;
    if (int_sts.txfifo_wm_int_st) {
        *event = I2C_INTR_EVENT_TXFIFO_EMPTY;
    } else if (int_sts.trans_complete_int_st) {
        *event = I2C_INTR_EVENT_TRANS_DONE;
    } else if (int_sts.rxfifo_wm_int_st) {
        *event = I2C_INTR_EVENT_RXFIFO_FULL;
    } else {
        *event = I2C_INTR_EVENT_ERR;
    }
}

/**
 * @brief  初始化I2C主机
 *
 * @param  hw 外围寄存器的起始地址
 *
 * @return 没有一个
 */
static inline void i2c_ll_master_init(i2c_dev_t *hw)
{
    typeof(hw->ctr) ctrl_reg;
    ctrl_reg.val = 0;
    ctrl_reg.ms_mode = 1;
    ctrl_reg.clk_en = 1;
    ctrl_reg.sda_force_out = 1;
    ctrl_reg.scl_force_out = 1;
    hw->ctr.val = ctrl_reg.val;
}

/**
 * @brief  初始化I2C从属
 *
 * @param  hw 外围寄存器的起始地址
 *
 * @return 没有一个
 */
static inline void i2c_ll_slave_init(i2c_dev_t *hw)
{
    typeof(hw->ctr) ctrl_reg;
    ctrl_reg.val = 0;
    ctrl_reg.sda_force_out = 1;
    ctrl_reg.scl_force_out = 1;
    hw->ctr.val = ctrl_reg.val;
    hw->ctr.slv_tx_auto_start_en = 1;
    hw->fifo_conf.fifo_addr_cfg_en = 0;
}

#ifdef __cplusplus
}
#endif

