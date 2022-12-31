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

// I2C的HAL层

#pragma once
#include "hal/i2c_ll.h"
#include "hal/i2c_types.h"

/**
 * @brief I2C hal上下文定义
 */
typedef struct {
    i2c_dev_t *dev;
    uint32_t version;
} i2c_hal_context_t;

/**
 * @brief  使用给定长度写入I2C rxfifo
 *
 * @param  hal HAL层的上下文
 * @param  wr_data 指向数据缓冲区的指针
 * @param  wr_size 需要写入的数据量
 *
 * @return 没有一个
 */
#define i2c_hal_write_txfifo(hal,wr_data,wr_size)    i2c_ll_write_txfifo((hal)->dev,wr_data,wr_size)

/**
 * @brief  读取给定长度的I2C rxfifo
 *
 * @param  hal HAL层的上下文
 * @param  buf 指向数据缓冲区的指针
 * @param  rd_size 需要读取的数据量
 *
 * @return 没有一个
 */
#define i2c_hal_read_rxfifo(hal,buf,rd_size)    i2c_ll_read_rxfifo((hal)->dev,buf,rd_size)

/**
 * @brief  写入I2C命令寄存器
 *
 * @param  hal HAL层的上下文
 * @param  cmd I2C硬件命令
 * @param  cmd_idx 命令寄存器的索引应小于16
 *
 * @return 没有一个
 */
#define i2c_hal_write_cmd_reg(hal,cmd, cmd_idx)    i2c_ll_write_cmd_reg((hal)->dev,cmd,cmd_idx)

/**
 * @brief  配置I2C以触发事务
 *
 * @param  hal HAL层的上下文
 *
 * @return 没有一个
 */
#define i2c_hal_trans_start(hal)    i2c_ll_trans_start((hal)->dev)

/**
 * @brief  启用I2C主RX中断
 *
 * @param  hal HAL层的上下文
 *
 * @return 没有一个
 */
#define i2c_hal_enable_master_rx_it(hal)    i2c_ll_master_enable_rx_it((hal)->dev)

/**
 * @brief  启用I2C主TX中断
 *
 * @param  hal HAL层的上下文
 *
 * @return 没有一个
 */
#define i2c_hal_enable_master_tx_it(hal)    i2c_ll_master_enable_tx_it((hal)->dev)

/**
 * @brief  清除I2C从属TX中断
 *
 * @param  hal HAL层的上下文
 *
 * @return 没有一个
 */
#define i2c_hal_slave_clr_tx_it(hal)    i2c_ll_slave_clr_tx_it((hal)->dev)

/**
 * @brief  清除I2C从属RX中断
 *
 * @param  hal HAL层的上下文
 *
 * @return 没有一个
 */
#define i2c_hal_slave_clr_rx_it(hal)    i2c_ll_slave_clr_rx_it((hal)->dev)

/**
 * @brief  设置源时钟。此功能用于从属模式，以便选择源时钟abe来处理预期的SCL频率。
 *
 * @param  hal HAL层的上下文
 * @param  src_clk 要使用从“i2c_sclk_t”类型中选择的源时钟
 */
#define i2c_hal_set_source_clk(hal, src_clk) i2c_ll_set_source_clk((hal)->dev, src_clk)

/**
 * @brief  初始化I2C主机。
 *
 * @param  hal HAL层的上下文
 * @param  i2c_num I2C端口号
 *
 * @return 没有一个
 */
void i2c_hal_master_init(i2c_hal_context_t *hal, i2c_port_t i2c_num);

/**
 * @brief  初始化I2C从属设备。
 *
 * @param  hal HAL层的上下文
 * @param  i2c_num I2C端口号
 *
 * @return 没有一个
 */
void i2c_hal_slave_init(i2c_hal_context_t *hal, i2c_port_t i2c_num);

/**
 * @brief  重置I2C硬件txfifo
 *
 * @param  hal HAL层的上下文
 *
 * @return 没有一个
 */
void i2c_hal_txfifo_rst(i2c_hal_context_t *hal);

/**
 * @brief  重置I2C hw-rxfifo
 *
 * @param  hal HAL层的上下文
 *
 * @return 没有一个
 */
void i2c_hal_rxfifo_rst(i2c_hal_context_t *hal);

/**
 * @brief  首先配置I2C数据MSB位移位或LSB位移位。
 *
 * @param  hal HAL层的上下文
 * @param  tx_mode TX数据格式
 * @param  rx_mode RX数据格式
 *
 * @return 没有一个
 */
void i2c_hal_set_data_mode(i2c_hal_context_t *hal, i2c_trans_mode_t tx_mode, i2c_trans_mode_t rx_mode);

/**
 * @brief  配置I2C硬件滤波器功能。
 *
 * @param  hal HAL层的上下文
 * @param  filter_num 如果线路上的故障周期小于此值（在APB周期中），则会将其过滤掉。如果“filter_num==0”，则会禁用过滤器
 *
 * @return 没有一个
 */
void i2c_hal_set_filter(i2c_hal_context_t *hal, uint8_t filter_num);

/**
 * @brief 获取I2C硬件过滤器配置
 *
 * @param  hal HAL层的上下文
 * @param  filter_num 用于接受硬件筛选器配置的指针
 *
 * @return 没有一个
 */
void i2c_hal_get_filter(i2c_hal_context_t *hal, uint8_t *filter_num);

/**
 * @brief  配置I2C SCL计时
 *
 * @param  hal HAL层的上下文
 * @param  hight_period SCL高时段
 * @param  low_period SCL低时段
 *
 * @return 没有一个
 */
void i2c_hal_set_scl_timing(i2c_hal_context_t *hal, int hight_period, int low_period);

/**
 * @brief 配置I2C主SCL频率
 *
 * @param  hal HAL层的上下文
 * @param  src_clk I2C源时钟频率
 * @param  scl_freq 要设置的SCL频率
 *
 * @return 没有一个
 */
void i2c_hal_set_scl_freq(i2c_hal_context_t *hal, uint32_t src_clk, uint32_t scl_freq);

/**
 * @brief  使用给定掩码清除I2C中断状态
 *
 * @param  hal HAL层的上下文
 * @param  mask 需要清除中断位图
 *
 * @return 没有一个
 */
void i2c_hal_clr_intsts_mask(i2c_hal_context_t *hal, uint32_t mask);

/**
 * @brief  使用给定掩码启用I2C中断
 *
 * @param  hal HAL层的上下文
 * @param  mask 需要启用中断位图
 *
 * @return 没有一个
 */
void i2c_hal_enable_intr_mask(i2c_hal_context_t *hal, uint32_t mask);

/**
 * @brief  使用给定掩码禁用I2C中断
 *
 * @param  hal HAL层的上下文
 * @param  mask 需要禁用中断位图
 *
 * @return 没有一个
 */
void i2c_hal_disable_intr_mask(i2c_hal_context_t *hal, uint32_t mask);

/**
 * @brief  配置I2C内存访问模式、FIFO模式或无FIFO模式
 *
 * @param  hal HAL层的上下文
 * @param  fifo_mode_en 设置为true以启用FIFO访问模式，否则设置为false
 *
 * @return 没有一个
 */
void i2c_hal_set_fifo_mode(i2c_hal_context_t *hal, bool fifo_mode_en);

/**
 * @brief  配置I2C超时值
 *
 * @param  hal HAL层的上下文
 * @param  tout_val 要设置的超时值
 *
 * @return 没有一个
 */
void i2c_hal_set_tout(i2c_hal_context_t *hal, int tout_val);

/**
 * @brief  获取I2C超时配置
 *
 * @param  tout_val 用于接受超时配置的指针
 *
 * @return 没有一个
 */
void i2c_hal_get_tout(i2c_hal_context_t *hal, int *tout_val);

/**
 * @brief 配置I2C从属地址
 *
 * @param  hal HAL层的上下文
 * @param  slave_addr 从属地址
 * @param  addr_10bit_en 设置为true以启用10位从地址模式，设置为false以启用7位地址模式
 *
 * @return 没有一个
 */
void i2c_hal_set_slave_addr(i2c_hal_context_t *hal, uint16_t slave_addr, bool addr_10bit_en);

/**
 * @brief  配置I2C停止计时
 *
 * @param  hal HAL层的上下文
 * @param  stop_setup 停止条件设置周期（APB周期）
 * @param  stop_hold 停止条件保持期（APB周期）
 *
 * @return 没有一个
 */
void i2c_hal_set_stop_timing(i2c_hal_context_t *hal, int stop_setup, int stop_hold);

/**
 * @brief  配置I2C启动定时
 *
 * @param  hal HAL层的上下文
 * @param  start_setup 启动条件设置周期（APB周期）
 * @param  start_hold 启动条件保持期（APB周期）
 *
 * @return 没有一个
 */
void i2c_hal_set_start_timing(i2c_hal_context_t *hal, int start_setup, int start_hold);

/**
 * @brief  配置I2C sda采样定时
 *
 * @param  hal HAL层的上下文
 * @param  sda_sample SDA采样时间（APB周期）
 * @param  sda_hold SDA保持时间（APB周期）
 *
 * @return 没有一个
 */
void i2c_hal_set_sda_timing(i2c_hal_context_t *hal, int sda_sample, int sda_hold);

/**
 * @brief  配置I2C txfifo空阈值
 *
 * @param  hal HAL层的上下文。
 * @param  empty_thr TxFIFO空阈值
 *
 * @return 没有一个
 */
void i2c_hal_set_txfifo_empty_thr(i2c_hal_context_t *hal, uint8_t empty_thr);

/**
 * @brief  配置I2C rxfifo完整阈值
 *
 * @param  hal HAL层的上下文
 * @param  full_thr RxFIFO满阈值
 *
 * @return 没有一个
 */
void i2c_hal_set_rxfifo_full_thr(i2c_hal_context_t *hal, uint8_t full_thr);

/**
 * @brief  获取I2C中断状态
 *
 * @param  hal HAL层的上下文
 * @param  mask 接受中断状态的指针
 *
 * @return 没有一个
 */
void i2c_hal_get_intsts_mask(i2c_hal_context_t *hal, uint32_t *mask);

/**
 * @brief  检查I2C总线是否繁忙
 *
 * @param  hal HAL层的上下文
 *
 * @return 如果公交车繁忙，则为True，否则将返回fale
 */
bool i2c_hal_is_bus_busy(i2c_hal_context_t *hal);

/**
 * @brief  获取I2C sda采样定时配置
 *
 * @param  hal HAL层的上下文
 * @param  sample_time 用于接受SDA采样时间的指针
 * @param  hold_time 接受SDA保持时间的指针
 *
 * @return 没有一个
 */
void i2c_hal_get_sda_timing(i2c_hal_context_t *hal, int *sample_time, int *hold_time);

/**
 * @brief  获取I2C停止计时配置
 *
 * @param  hal HAL层的上下文
 * @param  setup_time 用于接受停止条件设置周期的指针
 * @param  hold_time 用于接受停止条件保持期的指针
 *
 * @return 没有一个
 */
void i2c_hal_get_stop_timing(i2c_hal_context_t *hal, int *setup_time, int *hold_time);

/**
 * @brief  获取I2C scl定时配置
 *
 * @param  hal HAL层的上下文
 * @param  high_period 用于接受scl高时段的指针
 * @param  low_period 用于接受scl低周期的指针
 *
 * @return 没有一个
 */
void i2c_hal_get_scl_timing(i2c_hal_context_t *hal, int *high_period, int *low_period);

/**
 * @brief  获取I2C启动定时配置
 *
 * @param  hal HAL层的上下文
 * @param  setup_time 用于接受开始条件设置周期的指针
 * @param  hold_time 接受开始条件保持期的指针
 *
 * @return 没有一个
 */
void i2c_hal_get_start_timing(i2c_hal_context_t *hal, int *setup_time, int *hold_time);

/**
 * @brief  检查I2C是否为主模式
 *
 * @param  hal HAL层的上下文
 *
 * @return 如果处于主模式，则为True，否则将返回false
 */
bool i2c_hal_is_master_mode(i2c_hal_context_t *hal);

/**
 * @brief  获取rxFIFO可读长度
 *
 * @param  hal HAL层的上下文
 * @param  len 用于接受rxFIFO可读长度的指针
 *
 * @return 没有一个
 */
void i2c_hal_get_rxfifo_cnt(i2c_hal_context_t *hal, uint32_t *len);

/**
 * @brief  使用给定频率设置I2C总线定时
 *
 * @param  hal HAL层的上下文
 * @param  scl_freq 要设置的scl频率
 * @param  src_clk I2C源时钟
 *
 * @return 没有一个
 */
void i2c_hal_set_bus_timing(i2c_hal_context_t *hal, int scl_freq, i2c_sclk_t src_clk);

/**
 * @brief  获取I2C txFIFO可写长度
 *
 * @param  hal HAL层的上下文
 * @param  len 用于接受txFIFO可写长度的指针
 *
 * @return 没有一个
 */
void i2c_hal_get_txfifo_cnt(i2c_hal_context_t *hal, uint32_t *len);

/**
 * @brief  检查I2C是否为主模式
 *
 * @param  hal HAL层的上下文
 * @param  tx_mode 用于接受TX数据模式的指针
 * @param  rx_mode 接受RX数据模式的指针
 *
 * @return 没有一个
 */
void i2c_hal_get_data_mode(i2c_hal_context_t *hal, i2c_trans_mode_t *tx_mode, i2c_trans_mode_t *rx_mode);

/**
 * @brief  I2C硬件FSM复位
 *
 * @param  hal HAL层的上下文
 *
 * @return 没有一个
 */
void i2c_hal_master_fsm_rst(i2c_hal_context_t *hal);

/**
 * @brief  @简短的清除I2C总线
 *
 * @param  hal HAL层的上下文
 *
 * @return 没有一个
 */
void i2c_hal_master_clr_bus(i2c_hal_context_t *hal);

/**
 * @brief  启用I2C从属TX中断
 *
 * @param  hal HAL层的上下文
 *
 * @return 没有一个
 */
void i2c_hal_enable_slave_tx_it(i2c_hal_context_t *hal);

/**
 * @brief  禁用I2C从属TX中断
 *
 * @param  hal HAL层的上下文
 *
 * @return 没有一个
 */
void i2c_hal_disable_slave_tx_it(i2c_hal_context_t *hal);

/**
 * @brief  启用I2C从属RX中断
 *
 * @param  hal HAL层的上下文
 *
 * @return 没有一个
 */
void i2c_hal_enable_slave_rx_it(i2c_hal_context_t *hal);

/**
 * @brief  禁用I2C从属RX中断
 *
 * @param  hal HAL层的上下文
 *
 * @return 没有一个
 */
void i2c_hal_disable_slave_rx_it(i2c_hal_context_t *hal);

/**
 * @brief  I2C主句柄tx中断事件
 *
 * @param  hal HAL层的上下文
 * @param  event 接受中断事件的指针
 *
 * @return 没有一个
 */
void i2c_hal_master_handle_tx_event(i2c_hal_context_t *hal, i2c_intr_event_t *event);

/**
 * @brief  I2C主句柄rx中断事件
 *
 * @param  hal HAL层的上下文
 * @param  event 接受中断事件的指针
 *
 * @return 没有一个
 */
void i2c_hal_master_handle_rx_event(i2c_hal_context_t *hal, i2c_intr_event_t *event);

/**
 * @brief  I2C从属句柄中断事件
 *
 * @param  hal HAL层的上下文
 * @param  event 接受中断事件的指针
 *
 * @return 没有一个
 */
void i2c_hal_slave_handle_event(i2c_hal_context_t *hal, i2c_intr_event_t *event);

/**
 * @brief 同步I2C状态
 *
 * @param hal HAL层的上下文
 *
 * @return 没有一个
 *
 */
void i2c_hal_update_config(i2c_hal_context_t *hal);

