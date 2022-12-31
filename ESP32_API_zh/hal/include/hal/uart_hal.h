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

// UART的HAL层。
// hal层中没有参数检查，因此调用者必须确保参数的正确性。

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "hal/uart_ll.h"
#include "hal/uart_types.h"

/**
 * 驾驶员和HAL应维护的上下文
 */
typedef struct {
    uart_dev_t *dev;
} uart_hal_context_t;

/**
 * @brief 清除UART中断状态
 *
 * @param  hal HAL层的上下文
 * @param  mask 要清除的中断状态掩码。使用“UART_INTR_XFIFO_FULL…UART_INTR.CMD_CHAR_DET”的OR掩码`
 *
 * @return 没有一个
 */
#define uart_hal_clr_intsts_mask(hal, mask)  uart_ll_clr_intsts_mask((hal)->dev, mask)

/**
 * @brief 禁用UART中断
 *
 * @param  hal HAL层的上下文
 * @param  mask 要禁用的中断掩码。使用“UART_INTR_XFIFO_FULL…UART_INTR.CMD_CHAR_DET”的OR掩码`
 *
 * @return 没有一个
 */
#define uart_hal_disable_intr_mask(hal, mask)  uart_ll_disable_intr_mask((hal)->dev, mask)

/**
 * @brief 启用UART中断
 *
 * @param  hal HAL层的上下文
 * @param  mask 要启用的UART中断掩码。使用“UART_INTR_XFIFO_FULL…UART_INTR.CMD_CHAR_DET”的OR掩码`
 *
 * @return 没有一个
 */
#define uart_hal_ena_intr_mask(hal, mask)  uart_ll_ena_intr_mask((hal)->dev, mask)

/**
 * @brief 获取UART中断状态
 *
 * @param  hal HAL层的上下文
 *
 * @return UART中断状态
 */
#define uart_hal_get_intsts_mask(hal)  uart_ll_get_intsts_mask((hal)->dev)

/**
 * @brief 获取已启用中断的状态
 *
 * @param  hal HAL层的上下文
 *
 * @return UART中断启用值
 */
#define uart_hal_get_intr_ena_status(hal) uart_ll_get_intr_ena_status((hal)->dev)

/**
 * @brief 获取UART模式字符配置
 *
 * @param  hal HAL层的上下文
 * @param  cmd_char 用于接受UART AT cmd字符的指针
 * @param  char_num 用于接受“UART_CHAR_NUM”配置的指针
 *
 * @return 没有一个
 */
#define uart_hal_get_at_cmd_char(hal, cmd_char, char_num)  uart_ll_get_at_cmd_char((hal)->dev, cmd_char, char_num)

/**
 * @brief 设置UART第一信号激活电平
 *
 * @param  hal HAL层的上下文
 * @param  active_level rts活动级别。如果设置为0，则激活电平为低。如果设置为1，则激活级别为高
 *
 * @return 没有一个
 */
#define uart_hal_set_rts(hal, active_level)  uart_ll_set_rts_active_level((hal)->dev, active_level)

/**
 * @brief 获取txfifo可写长度（字节）
 *
 * @param  hal HAL层的上下文
 *
 * @return UART txfifo可写长度
 */
#define uart_hal_get_txfifo_len(hal)  uart_ll_get_txfifo_len((hal)->dev)

/**
 * @brief 检查UART发送状态机是否处于IDLE状态。
 *
 * @param  hal HAL层的上下文
 *
 * @return 如果状态机处于IDLE状态，则为True，否则将返回false。
 */
#define uart_hal_is_tx_idle(hal)  uart_ll_is_tx_idle((hal)->dev)

/**
 * @brief  配置UART核心重置
 *
 * @param  hal HAL层的上下文
 * @param  Set true启用核心重置，否则设置为false
 *
 * @return 没有一个
 */
#define uart_hal_set_reset_core(hal, core_rst_en)  uart_ll_set_reset_core((hal)->dev, core_rst_en)

/**
 * @brief  从UART rxfifo读取数据
 *
 * @param[in] hal HAL层的上下文
 * @param[in] buf 指向用于存储读取数据的缓冲区的指针。缓冲区大小应大于128字节
 * @param[inout] inout_rd_len 作为输入，要读取的输出缓冲区的大小（设置为0以读取所有可用数据）。作为输出，返回写入输出缓冲区的实际大小。
 *
 * @return 没有一个
 */
void uart_hal_read_rxfifo(uart_hal_context_t *hal, uint8_t *buf, int *inout_rd_len);

/**
 * @brief  将数据写入UART txfifo
 *
 * @param  hal HAL层的上下文
 * @param  buf 需要将数据缓冲区的指针写入txfifo
 * @param  data_size 需要写入的数据大小（字节）
 * @param  write_size 大小已写入
 *
 * @return 没有一个
 */
void uart_hal_write_txfifo(uart_hal_context_t *hal, const uint8_t *buf, uint32_t data_size, uint32_t *write_size);

/**
 * @brief  重置UART txfifo
 * @note   在ESP32上，此功能保留给UART1和UART2。
 *
 * @param  hal HAL层的上下文
 *
 * @return 没有一个
 */
void uart_hal_txfifo_rst(uart_hal_context_t *hal);

/**
 * @brief  重置UART rxfifo
 *
 * @param  hal HAL层的上下文
 *
 * @return 没有一个
 */
void uart_hal_rxfifo_rst(uart_hal_context_t *hal);

/**
 * @brief 初始化UART hal并将UART设置为默认配置。
 *
 * @param  hal HAL层的上下文
 * @param  uart_num uart端口号，最大端口号为（uart_NUM_max-1）
 *
 * @return 没有一个
 */
void uart_hal_init(uart_hal_context_t *hal, uart_port_t uart_num);

/**
 * @brief 设置UART源时钟类型
 * @param  hal HAL层的上下文
 * @param  sclk UART源时钟类型。
 *
 * @return 没有一个
 */
void uart_hal_set_sclk(uart_hal_context_t *hal, uart_sclk_t sclk);

/**
 * @brief 获取UART源时钟类型
 *
 * @param  hal HAL层的上下文
 * @param  sclk 接受UART源时钟类型的指针
 *
 * @return 没有一个
 */
void uart_hal_get_sclk(uart_hal_context_t *hal, uart_sclk_t *sclk);

/**
 * @brief  配置UART波特率并选择源时钟
 *
 * @param  hal HAL层的上下文
 * @param  baud_rate 要设置的波特率
 *
 * @return 没有一个
 */
void uart_hal_set_baudrate(uart_hal_context_t *hal, uint32_t baud_rate);

/**
 * @brief  配置UART停止位
 *
 * @param  hal HAL层的上下文
 * @param  stop_bit 要设置的停止位
 *
 * @return 没有一个
 */
void uart_hal_set_stop_bits(uart_hal_context_t *hal, uart_stop_bits_t stop_bit);

/**
 * @brief 配置UART数据位
 *
 * @param  hal HAL层的上下文
 * @param  data_bit 要设置的数据位
 *
 * @return 没有一个
 */
void uart_hal_set_data_bit_num(uart_hal_context_t *hal, uart_word_length_t data_bit);

/**
 * @brief 配置UART奇偶校验模式
 *
 * @param  hal HAL层的上下文
 * @param  parity_mode 要设置的UART奇偶校验模式
 *
 * @return 没有一个
 */
void uart_hal_set_parity(uart_hal_context_t *hal, uart_parity_t parity_mode);

/**
 * @brief 配置UART硬件流量控制
 *
 * @param  hal HAL层的上下文
 * @param  flow_ctrl 要设置的流量控制模式
 * @param  rx_thresh 如果rxfifo中的数据长度大于此值，rts流控制信号将激活
 *
 * @return 没有一个
 */
void uart_hal_set_hw_flow_ctrl(uart_hal_context_t *hal, uart_hw_flowcontrol_t flow_ctrl, uint8_t rx_thresh);

/**
 * @brief 配置UART AT cmd字符检测功能。当接收机接收到一个连续的AT cmd字符时，它将产生一个中断
 *
 * @param  hal HAL层的上下文
 * @param  at_cmd AT cmd字符检测配置
 *
 * @return 没有一个
 */
void uart_hal_set_at_cmd_char(uart_hal_context_t *hal, uart_at_cmd_t *at_cmd);

/**
 * @brief 设置UART接收器的超时值
 *
 * @param  hal HAL层的上下文
 * @param  tout 接收器接收数据的超时值
 *
 * @return 没有一个
 */
void uart_hal_set_rx_timeout(uart_hal_context_t *hal, const uint8_t tout);

/**
 * @brief 设置UART dtr信号激活电平
 *
 * @param  hal HAL层的上下文
 * @param  active_level dtr活动级别。如果设置为0，则激活电平为低。如果设置为1，则激活级别为高
 *
 * @return 没有一个
 */
void uart_hal_set_dtr(uart_hal_context_t *hal, int active_level);

/**
 * @brief 设置UART软件流控制
 *
 * @param  hal HAL层的上下文
 * @param  flow_ctrl 软件流控制配置
 * @param  sw_flow_ctrl_en 设置为true以启用软件流控制，否则设置为false
 *
 * @return 没有一个
 */
void uart_hal_set_sw_flow_ctrl(uart_hal_context_t *hal, uart_sw_flowctrl_t *flow_ctrl, bool sw_flow_ctrl_en);

/**
 * @brief 设置UART tx空闲编号
 *
 * @param  hal HAL层的上下文
 * @param  idle_num 两个变速器之间的循环数
 *
 * @return 没有一个
 */
void uart_hal_set_tx_idle_num(uart_hal_context_t *hal, uint16_t idle_num);

/**
 * @brief 设置UART rxfifo满阈值
 *
 * @param  hal HAL层的上下文
 * @param  full_thrhd rxfifo满阈值。如果启用了“UART_RXFIFO_FULL”中断，且RXFIFO中的数据长度大于此值，则将生成“UART_RXFIFO_FULL”中断
 *
 * @return 没有一个
 */
void uart_hal_set_rxfifo_full_thr(uart_hal_context_t *hal, uint32_t full_thrhd);

/**
 * @brief 设置UART txfifo空阈值
 *
 * @param  hal HAL层的上下文
 * @param  empty_thrhd 要设置的txfifo空阈值。如果启用了“UART_TXFIFO_EMPTY”中断，且TXFIFO中的数据长度小于此值，则将生成“UART_TX FIFO_EMPTY”中断
 *
 * @return 没有一个
 */
void uart_hal_set_txfifo_empty_thr(uart_hal_context_t *hal, uint32_t empty_thrhd);

/**
 * @brief 配置UART以发送多个中断（NULL）字符
 *
 * @param  hal HAL层的上下文
 * @param  break_num 需要发送的中断字符数
 *
 * @return 没有一个
 */
void uart_hal_tx_break(uart_hal_context_t *hal, uint32_t break_num);

/**
 * @brief 配置UART唤醒功能。注意，使用此功能时，RXD不能通过GPIO矩阵输入，只能通过IO_MUX输入
 *
 * @param  hal HAL层的上下文
 * @param  wakeup_thrd 要设置的唤醒阈值。当输入RXD边沿变化次数超过“wakeup_thrd+2”时，系统将从浅睡眠中唤醒`
 *
 * @return 没有一个
 */
void uart_hal_set_wakeup_thrd(uart_hal_context_t *hal, uint32_t wakeup_thrd);

/**
 * @brief 配置UART模式
 *
 * @param  hal HAL层的上下文
 * @param  mode 要设置的UART模式
 *
 * @return 没有一个
 */
void uart_hal_set_mode(uart_hal_context_t *hal, uart_mode_t mode);

/**
 * @brief 配置UART硬件以反转信号
 *
 * @param  hal HAL层的上下文
 * @param  inv_mask 信号掩码需要反转。使用“uart_signal_inv_t”类型的“或”掩码`
 *
 * @return 没有一个
 */
void uart_hal_inverse_signal(uart_hal_context_t *hal, uint32_t inv_mask);

/**
 * @brief 获取UART唤醒阈值配置
 *
 * @param  hal HAL层的上下文
 * @param  wakeup_thrd 接受UART唤醒阈值配置值的指针
 *
 * @return 没有一个
 */
void uart_hal_get_wakeup_thrd(uart_hal_context_t *hal, uint32_t *wakeup_thrd);

/**
 * @brief 获取UART数据位配置
 *
 * @param  hal HAL层的上下文
 * @param  data_bit 接受UART数据位配置值的指针
 *
 * @return 没有一个
 */
void uart_hal_get_data_bit_num(uart_hal_context_t *hal, uart_word_length_t *data_bit);

/**
 * @brief 获取UART停止位配置
 *
 * @param  hal HAL层的上下文
 * @param  stop_bit 接受UART停止位配置值的指针
 *
 * @return 没有一个
 */
void uart_hal_get_stop_bits(uart_hal_context_t *hal, uart_stop_bits_t *stop_bit);

/**
 * @brief 获取UART奇偶校验模式配置
 *
 * @param  hal HAL层的上下文
 * @param  parity_mode 用于接受UART奇偶校验模式配置的指针
 *
 * @return 没有一个
 */
void uart_hal_get_parity(uart_hal_context_t *hal, uart_parity_t *parity_mode);

/**
 * @brief 获取UART波特率配置
 *
 * @param  hal HAL层的上下文
 * @param  baud_rate 接受当前波特率的指针
 *
 * @return 没有一个
 */
void uart_hal_get_baudrate(uart_hal_context_t *hal, uint32_t *baud_rate);

/**
 * @brief 获取硬件流控制配置
 *
 * @param  hal HAL层的上下文
 * @param  flow_ctrl 用于接受UART流控制配置的指针
 *
 * @return 没有一个
 */
void uart_hal_get_hw_flow_ctrl(uart_hal_context_t *hal, uart_hw_flowcontrol_t *flow_ctrl);

/**
 * @brief 检查UART rts流量控制是否已启用
 *
 * @param  hal HAL层的上下文
 *
 * @return 如果启用rts流控制，则为True，否则将返回false
 */
bool uart_hal_is_hw_rts_en(uart_hal_context_t *hal);

/**
 * @brief 将TX信号回路配置回RX模块，仅用于测试目的
 *
 * @param  hal HAL层的上下文
 * @param  loop_back_en 设置ture以启用循环返回功能，否则设置为false。
 *
 * @return 没有一个
 */
void uart_hal_set_loop_back(uart_hal_context_t *hal, bool loop_back_en);

/**
 * @brief  按照配置中的定义计算uart符号位长度。
 *
 * @param  hw 外围寄存器的起始地址。
 *
 * @return 每个UART符号的位数。
 */
uint8_t uart_hal_get_symb_len(uart_hal_context_t *hal);

/**
 * @brief  获取UART最大超时阈值。
 *
 * @param  hw 外围寄存器的起始地址。
 *
 * @return 目标的最大超时阈值。
 */
uint16_t uart_hal_get_max_rx_timeout_thrd(uart_hal_context_t *hal);

/**
 * @brief  获取为接收器设置的超时阈值。
 *
 * @param  hw 外围寄存器的起始地址。
 *
 * @return tout_thr超时值。如果禁用超时，则返回0。
 */
#define uart_hal_get_rx_tout_thr(hal) uart_ll_get_rx_tout_thr((hal)->dev)

/**
 * @brief  获取UARTRxfifo中可读数据的长度。
 *
 * @param  hw 外围寄存器的起始地址。
 *
 * @return rxifo中的可读数据长度。
 */
#define uart_hal_get_rxfifo_len(hal) uart_ll_get_rxfifo_len((hal)->dev)

#ifdef __cplusplus
}
#endif

