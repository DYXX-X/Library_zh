/*
 * SPDX文件版权文本：2015-2021浓缩咖啡系统（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "esp_err.h"
#include "esp_intr_alloc.h"
#include "soc/soc_caps.h"
#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "freertos/ringbuf.h"
#include "hal/uart_types.h"

// 有效的UART端口号
#define UART_NUM_0             (0) /*!< UART端口0*/
#define UART_NUM_1             (1) /*!< UART端口1*/
#if SOC_UART_NUM > 2
#define UART_NUM_2             (2) /*!< UART端口2*/
#endif
#define UART_NUM_MAX           (SOC_UART_NUM) /*!< UART端口最大值*/

/* @brief 当调用“uart_set_pin”时，可以提供“uart_pin_NO_CHANGE”来保持当前分配的引脚，而不是GPIO编号。
 */
#define UART_PIN_NO_CHANGE      (-1)

#define UART_FIFO_LEN           SOC_UART_FIFO_LEN       ///<UART HW FIFO的长度
#define UART_BITRATE_MAX        SOC_UART_BITRATE_MAX    ///<最大可配置比特率

/**
 * @brief UART_intr_config函数的UART中断配置参数
 */
typedef struct {
    uint32_t intr_enable_mask;          /*!< UART中断启用掩码，从UART_INT_ENA_REG（i）下的UART_XXXX_INT_ENA_M中选择，用位或运算符连接*/
    uint8_t  rx_timeout_thresh;         /*!< UART超时中断阈值（单位：发送一个字节的时间）*/
    uint8_t  txfifo_empty_intr_thresh;  /*!< UART TX空中断阈值。*/
    uint8_t  rxfifo_full_thresh;        /*!< UART RX完全中断阈值。*/
} uart_intr_config_t;

/**
 * @brief 环形缓冲区中使用的UART事件类型
 */
typedef enum {
    UART_DATA,              /*!< UART数据事件*/
    UART_BREAK,             /*!< UART中断事件*/
    UART_BUFFER_FULL,       /*!< UART RX缓冲区已满事件*/
    UART_FIFO_OVF,          /*!< UART FIFO溢出事件*/
    UART_FRAME_ERR,         /*!< UART RX帧错误事件*/
    UART_PARITY_ERR,        /*!< UART RX奇偶校验事件*/
    UART_DATA_BREAK,        /*!< UART TX数据和中断事件*/
    UART_PATTERN_DET,       /*!< 检测到UART模式*/
    UART_EVENT_MAX,         /*!< UART事件最大索引*/
} uart_event_type_t;

/**
 * @brief UART事件队列中使用的事件结构
 */
typedef struct {
    uart_event_type_t type; /*!< UART事件类型*/
    size_t size;            /*!< UART_data事件的UART数据大小*/
    bool timeout_flag;      /*!< UART_data事件的UART数据读取超时标志（在配置RX TOUT期间未接收到新数据）*/
                            /*!< 如果事件是由FIFO完全中断引起的，那么在下一个字节到来之前，将不会出现带有超时标志的事件。*/
} uart_event_t;

typedef intr_handle_t uart_isr_handle_t;

/**
 * @brief 安装UART驱动程序并将UART设置为默认配置。
 *
 * UART ISR处理程序将连接到运行此函数的同一CPU内核。
 *
 * @note  Rx_buffer_size应大于UART_FIFO_LEN。Tx_buffer_size应为零或大于UART_FIFO_LEN。
 *
 * @param uart_num UART端口号，最大端口号为（UART_NUM_max-1）。
 * @param rx_buffer_size UART RX环形缓冲区大小。
 * @param tx_buffer_size UART TX环形缓冲区大小。若设置为零，驱动程序将不使用TX缓冲区，TX功能将阻止任务，直到所有数据都发送出去。
 * @param queue_size UART事件队列大小/深度。
 * @param uart_queue UART事件队列句柄（输出参数）。成功后，这里将编写一个新的队列句柄，以提供对UART事件的访问。如果设置为NULL，驱动程序将不使用事件队列。
 * @param intr_alloc_flags 用于分配中断的标志。一个或多个（ORred）ESP_INTR_FLAG_值。请参见esp_intr_alloc。h了解更多信息。不要在此处设置ESP_INTR_FLAG_IRAM（驱动程序的ISR处理程序不在IRAM中）
 *
 * @return
 *     -ESP_OK成功
 *     -ESP_FAIL参数错误
 */
esp_err_t uart_driver_install(uart_port_t uart_num, int rx_buffer_size, int tx_buffer_size, int queue_size, QueueHandle_t* uart_queue, int intr_alloc_flags);

/**
 * @brief 卸载UART驱动程序。
 *
 * @param uart_num UART端口号，最大端口号为（UART_NUM_max-1）。
 *
 * @return
 *     -ESP_OK成功
 *     -ESP_FAIL参数错误
 */
esp_err_t uart_driver_delete(uart_port_t uart_num);

/**
 * @brief 检查驱动程序是否已安装
 *
 * @param uart_num UART端口号，最大端口号为（UART_NUM_max-1）。
 *
 * @return
 *     -已安装true驱动程序
 *     -未安装假驱动程序
 */
bool uart_is_driver_installed(uart_port_t uart_num);

/**
 * @brief 设置UART数据位。
 *
 * @param uart_num UART端口号，最大端口号为（UART_NUM_max-1）。
 * @param data_bit UART数据位
 *
 * @return
 *     -ESP_OK成功
 *     -ESP_FAIL参数错误
 */
esp_err_t uart_set_word_length(uart_port_t uart_num, uart_word_length_t data_bit);

/**
 * @brief 获取UART数据位配置。
 *
 * @param uart_num UART端口号，最大端口号为（UART_NUM_max-1）。
 * @param data_bit 用于接受UART数据位值的指针。
 *
 * @return
 *     -ESP_FAIL参数错误
 *     -ESP_OK成功，结果将放入（*data_bit）
 */
esp_err_t uart_get_word_length(uart_port_t uart_num, uart_word_length_t* data_bit);

/**
 * @brief 设置UART停止位。
 *
 * @param uart_num  UART端口号，最大端口号为（UART_NUM_max-1）。
 * @param stop_bits  UART停止位
 *
 * @return
 *     -ESP_OK成功
 *     -ESP_FAIL失败
 */
esp_err_t uart_set_stop_bits(uart_port_t uart_num, uart_stop_bits_t stop_bits);

/**
 * @brief 获取UART停止位配置。
 *
 * @param uart_num  UART端口号，最大端口号为（UART_NUM_max-1）。
 * @param stop_bits  用于接受UART停止位值的指针。
 *
 * @return
 *     -ESP_FAIL参数错误
 *     -ESP_OK成功，结果将放入（*stop_bit）
 */
esp_err_t uart_get_stop_bits(uart_port_t uart_num, uart_stop_bits_t* stop_bits);

/**
 * @brief 设置UART奇偶校验模式。
 *
 * @param uart_num UART端口号，最大端口号为（UART_NUM_max-1）。
 * @param parity_mode uart奇偶校验配置的枚举
 *
 * @return
 *     -ESP_FAIL参数错误
 *     -ESP_OK成功
 */
esp_err_t uart_set_parity(uart_port_t uart_num, uart_parity_t parity_mode);

/**
 * @brief 获取UART奇偶校验模式配置。
 *
 * @param uart_num  UART端口号，最大端口号为（UART_NUM_max-1）。
 * @param parity_mode 指向UART奇偶校验模式接受值的指针。
 *
 * @return
 *     -ESP_FAIL参数错误
 *     -ESP_OK成功，结果将放入（*parity_mode）
 *
 */
esp_err_t uart_get_parity(uart_port_t uart_num, uart_parity_t* parity_mode);

/**
 * @brief 设置UART波特率。
 *
 * @param uart_num UART端口号，最大端口号为（UART_NUM_max-1）。
 * @param baudrate UART波特率。
 *
 * @return
 *     -ESP_FAIL参数错误
 *     -ESP_OK成功
 */
esp_err_t uart_set_baudrate(uart_port_t uart_num, uint32_t baudrate);

/**
 * @brief 获取UART波特率配置。
 *
 * @param uart_num UART端口号，最大端口号为（UART_NUM_max-1）。
 * @param baudrate 指向UART波特率接受值的指针
 *
 * @return
 *     -ESP_FAIL参数错误
 *     -ESP_OK成功，结果将放入（*baudrate）
 *
 */
esp_err_t uart_get_baudrate(uart_port_t uart_num, uint32_t* baudrate);

/**
 * @brief 设置UART线路反向模式
 *
 * @param uart_num  UART端口号，最大端口号为（UART_NUM_max-1）。
 * @param inverse_mask 选择需要反转的导线。使用“uart_signal_inv_t”的“或”掩码`
 *
 * @return
 *     -ESP_OK成功
 *     -ESP_FAIL参数错误
 */
esp_err_t uart_set_line_inverse(uart_port_t uart_num, uint32_t inverse_mask);

/**
 * @brief 设置硬件流量控制。
 *
 * @param uart_num   UART端口号，最大端口号为（UART_NUM_max-1）。
 * @param flow_ctrl 硬件流量控制模式
 * @param rx_thresh 硬件RX流量控制阈值（0~UART_FIFO_LEN）。只有当设置了UART_HW_FLOWCTRL_RTS时，才会设置rx_thresh值。
 *
 * @return
 *     -ESP_OK成功
 *     -ESP_FAIL参数错误
 */
esp_err_t uart_set_hw_flow_ctrl(uart_port_t uart_num, uart_hw_flowcontrol_t flow_ctrl, uint8_t rx_thresh);

/**
 * @brief 设置软件流控制。
 *
 * @param uart_num   UART_NUM_0、UART_NUM_1或UART_NUM_2
 * @param enable     打开或关闭
 * @param rx_thresh_xon  低水位线
 * @param rx_thresh_xoff 高水位线
 *
 * @return
 *     -ESP_OK成功
 *     -ESP_FAIL参数错误
 */
 esp_err_t uart_set_sw_flow_ctrl(uart_port_t uart_num, bool enable,  uint8_t rx_thresh_xon,  uint8_t rx_thresh_xoff);

/**
 * @brief 获取UART硬件流控制配置。
 *
 * @param uart_num UART端口号，最大端口号为（UART_NUM_max-1）。
 * @param flow_ctrl 不同流量控制模式的选项。
 *
 * @return
 *     -ESP_FAIL参数错误
 *     -ESP_OK成功，结果将放入（*flow_ctrl）
 */
esp_err_t uart_get_hw_flow_ctrl(uart_port_t uart_num, uart_hw_flowcontrol_t* flow_ctrl);

/**
 * @brief 清除UART中断状态
 *
 * @param uart_num  UART端口号，最大端口号为（UART_NUM_max-1）。
 * @param clr_mask  要清除的中断状态的位掩码。
 *
 * @return
 *     -ESP_OK成功
 *     -ESP_FAIL参数错误
 */
esp_err_t uart_clear_intr_status(uart_port_t uart_num, uint32_t clr_mask);

/**
 * @brief 设置UART中断启用
 *
 * @param uart_num     UART端口号，最大端口号为（UART_NUM_max-1）。
 * @param enable_mask  启用位的位掩码。
 *
 * @return
 *     -ESP_OK成功
 *     -ESP_FAIL参数错误
 */
esp_err_t uart_enable_intr_mask(uart_port_t uart_num, uint32_t enable_mask);

/**
 * @brief 清除UART中断启用位
 *
 * @param uart_num      UART端口号，最大端口号为（UART_NUM_max-1）。
 * @param disable_mask  禁用位的位掩码。
 *
 * @return
 *     -ESP_OK成功
 *     -ESP_FAIL参数错误
 */
esp_err_t uart_disable_intr_mask(uart_port_t uart_num, uint32_t disable_mask);

/**
 * @brief 启用UART RX中断（RX_FULL和RX_TIMEOUT interrupt）
 *
 * @param uart_num  UART端口号，最大端口号为（UART_NUM_max-1）。
 *
 * @return
 *     -ESP_OK成功
 *     -ESP_FAIL参数错误
 */
esp_err_t uart_enable_rx_intr(uart_port_t uart_num);

/**
 * @brief 禁用UART RX中断（RX_FULL和RX_TIMEOUT interrupt）
 *
 * @param uart_num  UART端口号，最大端口号为（UART_NUM_max-1）。
 *
 * @return
 *     -ESP_OK成功
 *     -ESP_FAIL参数错误
 */
esp_err_t uart_disable_rx_intr(uart_port_t uart_num);

/**
 * @brief 禁用UART TX中断（TXFIFO_EMPTY interrupt）
 *
 * @param uart_num  UART端口号
 *
 * @return
 *     -ESP_OK成功
 *     -ESP_FAIL参数错误
 */
esp_err_t uart_disable_tx_intr(uart_port_t uart_num);

/**
 * @brief 启用UART TX中断（TXFIFO_EMPTY interrupt）
 *
 * @param uart_num UART端口号，最大端口号为（UART_NUM_max-1）。
 * @param enable  1： 启用；0：禁用
 * @param thresh  TX中断阈值，0~UART_FIFO_LEN
 *
 * @return
 *     -ESP_OK成功
 *     -ESP_FAIL参数错误
 */
esp_err_t uart_enable_tx_intr(uart_port_t uart_num, int enable, int thresh);

/**
 * @brief 注册UART中断处理程序（ISR）。
 *
 * @note UART ISR处理程序将连接到运行此函数的同一CPU内核。
 *
 * @param uart_num UART端口号，最大端口号为（UART_NUM_max-1）。
 * @param fn  中断处理程序函数。
 * @param arg 处理程序函数的参数
 * @param intr_alloc_flags 用于分配中断的标志。一个或多个（ORred）ESP_INTR_FLAG_值。请参见esp_intr_alloc。h了解更多信息。
 * @param handle 指向返回句柄的指针。如果非NULL，将在此处返回中断的句柄。
 *
 * @return
 *     -ESP_OK成功
 *     -ESP_FAIL参数错误
 */
esp_err_t uart_isr_register(uart_port_t uart_num, void (*fn)(void*), void * arg, int intr_alloc_flags,  uart_isr_handle_t *handle);

/**
 * @brief UART_isr_register注册的空闲UART中断处理程序。必须在调用uart_isr_register的同一内核上调用。
 *
 * @param uart_num UART端口号，最大端口号为（UART_NUM_max-1）。
 *
 * @return
 *     -ESP_OK成功
 *     -ESP_FAIL参数错误
 */
esp_err_t uart_isr_free(uart_port_t uart_num);

/**
 * @brief 将UART外设的信号分配给GPIO引脚
 *
 * @note 如果为UART信号配置的GPIO编号与该GPIO的一个IOMUX信号匹配，则该信号将直接通过IOMUX连接。否则，GPIO和信号将通过GPIO矩阵连接。例如，如果在ESP32上执行调用“uart_set_pin（0，1，3，-1，-1）”，因为GPIO1是UART0的默认TX引脚，GPIO3是UART00的默认RX引脚，两者都将通过IOMUX分别连接到U0TXD和U0RXD，完全绕过GPIO矩阵。该检查是在每个引脚的基础上进行的。因此，可以通过GPIO矩阵将RX引脚绑定到GPIO，而TX通过IOMUX绑定到其GPIO。
 *
 * @note 内部信号可以输出到多个GPIO焊盘。只有一个GPIO焊盘可以与输入信号连接。
 *
 * @param uart_num   UART端口号，最大端口号为（UART_NUM_max-1）。
 * @param tx_io_num  UART TX引脚GPIO编号。
 * @param rx_io_num  UART RX引脚GPIO编号。
 * @param rts_io_num UART RTS引脚GPIO编号。
 * @param cts_io_num UART CTS引脚GPIO编号。
 *
 * @return
 *     -ESP_OK成功
 *     -ESP_FAIL参数错误
 */
esp_err_t uart_set_pin(uart_port_t uart_num, int tx_io_num, int rx_io_num, int rts_io_num, int cts_io_num);

/**
 * @brief 手动设置UART RTS引脚电平。
 * @note  UART必须配置为禁用硬件流控制。
 *
 * @param uart_num UART端口号，最大端口号为（UART_NUM_max-1）。
 * @param level    1： RTS输出低（激活）；0:RTS输出高（块）
 *
 * @return
 *     -ESP_OK成功
 *     -ESP_FAIL参数错误
 */
esp_err_t uart_set_rts(uart_port_t uart_num, int level);

/**
 * @brief 手动设置UART DTR引脚电平。
 *
 * @param uart_num UART端口号，最大端口号为（UART_NUM_max-1）。
 * @param level    1： DTR输出低；0:DTR输出高
 *
 * @return
 *     -ESP_OK成功
 *     -ESP_FAIL参数错误
 */
esp_err_t uart_set_dtr(uart_port_t uart_num, int level);

/**
 * @brief tx FIFO为空后设置UART空闲间隔
 *
 * @param uart_num UART端口号，最大端口号为（UART_NUM_max-1）。
 * @param idle_num tx FIFO为空后的空闲间隔（单位：在当前波特率下发送一位所需的时间）
 *
 * @return
 *     -ESP_OK成功
 *     -ESP_FAIL参数错误
 */
esp_err_t uart_set_tx_idle_num(uart_port_t uart_num, uint16_t idle_num);

/**
 * @brief 设置UART配置参数。
 *
 * @param uart_num    UART端口号，最大端口号为（UART_NUM_max-1）。
 * @param uart_config UART参数设置
 *
 * @return
 *     -ESP_OK成功
 *     -ESP_FAIL参数错误
 */
esp_err_t uart_param_config(uart_port_t uart_num, const uart_config_t *uart_config);

/**
 * @brief 配置UART中断。
 *
 * @param uart_num  UART端口号，最大端口号为（UART_NUM_max-1）。
 * @param intr_conf UART中断设置
 *
 * @return
 *     -ESP_OK成功
 *     -ESP_FAIL参数错误
 */
esp_err_t uart_intr_config(uart_port_t uart_num, const uart_intr_config_t *intr_conf);

/**
 * @brief 等待UART TX FIFO为空。
 *
 * @param uart_num      UART端口号，最大端口号为（UART_NUM_max-1）。
 * @param ticks_to_wait 超时，以RTOS为单位的计数
 *
 * @return
 *     -ESP_OK成功
 *     -ESP_FAIL参数错误
 *     -ESP_ERR_TIMEOUT超时
 */
esp_err_t uart_wait_tx_done(uart_port_t uart_num, TickType_t ticks_to_wait);

/**
 * @brief 从给定的缓冲区和长度向UART端口发送数据。
 *
 * 此函数不会等待TX FIFO中的足够空间。它将只填充可用的TX FIFO，并在FIFO满时返回。
 * @note 仅当UART TX缓冲区未启用时，才应使用此功能。
 *
 * @param uart_num UART端口号，最大端口号为（UART_NUM_max-1）。
 * @param buffer 数据缓冲地址
 * @param len    要发送的数据长度
 *
 * @return
 *     -（-1）参数错误
 *     -OTHERS（>=0）推送到TX FIFO的字节数
 */
int uart_tx_chars(uart_port_t uart_num, const char* buffer, uint32_t len);

/**
 * @brief 从给定的缓冲器和长度向UART端口发送数据，
 *
 * 如果UART驱动程序的参数“tx_buffer_size”设置为零：此函数将在所有数据发送出去或至少推入tx FIFO之前不会返回。
 *
 * 否则，如果“tx_buffer_size”>0，则在将所有数据复制到tx环形缓冲区后，此函数将返回，然后UART ISR将逐渐将数据从环形缓冲区移动到tx FIFO。
 *
 * @param uart_num UART端口号，最大端口号为（UART_NUM_max-1）。
 * @param src   数据缓冲地址
 * @param size  要发送的数据长度
 *
 * @return
 *     -（-1）参数错误
 *     -OTHERS（>=0）推送到TX FIFO的字节数
 */
int uart_write_bytes(uart_port_t uart_num, const void* src, size_t size);

/**
 * @brief 从给定的缓冲器和长度向UART端口发送数据，
 *
 * 如果UART驱动程序的参数“tx_buffer_size”设置为零：在发送所有数据和中断信号之前，此函数不会返回。发送所有数据后，发送中断信号。
 *
 * 否则，如果“tx_buffer_size”>0，则在将所有数据复制到tx环形缓冲区后，此函数将返回，然后UART ISR将逐渐将数据从环形缓冲区移动到tx FIFO。所有数据发出后，发送中断信号。
 *
 * @param uart_num UART端口号，最大端口号为（UART_NUM_max-1）。
 * @param src   数据缓冲地址
 * @param size  要发送的数据长度
 * @param brk_len 中断信号持续时间（单位：以当前波特率发送一位所需的时间）
 *
 * @return
 *     -（-1）参数错误
 *     -OTHERS（>=0）推送到TX FIFO的字节数
 */
int uart_write_bytes_with_break(uart_port_t uart_num, const void* src, size_t size, int brk_len);

/**
 * @brief UART从UART缓冲区读取字节
 *
 * @param uart_num UART端口号，最大端口号为（UART_NUM_max-1）。
 * @param buf     指向缓冲区的指针。
 * @param length  数据长度
 * @param ticks_to_wait sTimeout，以RTOS计时为单位计数
 *
 * @return
 *     -（-1）错误
 *     -OTHERS（>=0）从UART FIFO读取的字节数
 */
int uart_read_bytes(uart_port_t uart_num, void* buf, uint32_t length, TickType_t ticks_to_wait);

/**
 * @brief uart_flush_input的别名。UART环形缓冲区刷新。这将丢弃UART RX缓冲区中的所有数据。
 * @note  此函数将清除UART rx缓冲区，而不是等待发送的数据。为了发送tx FIFO中的所有数据，我们可以使用uart_wait_tx-done函数。
 * @param uart_num UART端口号，最大端口号为（UART_NUM_max-1）。
 *
 * @return
 *     -ESP_OK成功
 *     -ESP_FAIL参数错误
 */
esp_err_t uart_flush(uart_port_t uart_num);

/**
 * @brief 清除输入缓冲区，丢弃环形缓冲区中的所有数据。
 * @note  为了发送tx FIFO中的所有数据，我们可以使用uart_wait_tx-done函数。
 * @param uart_num UART端口号，最大端口号为（UART_NUM_max-1）。
 *
 * @return
 *     -ESP_OK成功
 *     -ESP_FAIL参数错误
 */
esp_err_t uart_flush_input(uart_port_t uart_num);

/**
 * @brief   UART获取RX环形缓冲区缓存的数据长度
 *
 * @param   uart_num UART端口号，最大端口号为（UART_NUM_max-1）。
 * @param   size 用于接受缓存数据长度的size_t指针
 *
 * @return
 *     -ESP_OK成功
 *     -ESP_FAIL参数错误
 */
esp_err_t uart_get_buffered_data_len(uart_port_t uart_num, size_t* size);

/**
 * @brief   UART禁用模式检测功能。专为“AT命令”等应用程序设计。当硬件检测到一系列相同的字符时，将触发中断。
 *
 * @param uart_num UART端口号，最大端口号为（UART_NUM_max-1）。
 *
 * @return
 *     -ESP_OK成功
 *     -ESP_FAIL参数错误
 */
esp_err_t uart_disable_pattern_det_intr(uart_port_t uart_num);

#if CONFIG_IDF_TARGET_ESP32
/**
 * @brief UART启用模式检测功能。专为“AT命令”等应用程序设计。当硬件检测到一系列相同的字符时，将触发中断。
 * @note  此函数仅适用于esp32。此函数已弃用，请改用uart_enable_pattern_det_baud_intr。
 *
 * @param uart_num UART端口号。
 * @param pattern_chr 图案的特征。
 * @param chr_num 字符数，8位值。
 * @param chr_tout 每个模式字符之间的间隔超时，24位值，单位为APB（80Mhz）时钟周期。当持续时间小于此值时，它不会将此数据作为at_cmd字符。
 * @param post_idle 最后一个模式字符后的空闲时间，24位值，单位为APB（80Mhz）时钟周期。当持续时间小于此值时，它不会将以前的数据作为最后一个at_cmd字符
 * @param pre_idle 第一个模式字符之前的空闲时间，24位值，单位为APB（80Mhz）时钟周期。当持续时间小于此值时，它不会将此数据作为第一个at_cmd字符。
 *
 * @return
 *     -ESP_OK成功
 *     -ESP_FAIL参数错误
 */
esp_err_t uart_enable_pattern_det_intr(uart_port_t uart_num, char pattern_chr, uint8_t chr_num, int chr_tout, int post_idle, int pre_idle) __attribute__((deprecated));
#endif

/**
 * @brief UART启用模式检测功能。专为“AT命令”等应用程序设计。当硬件检测到一系列相同的字符时，将触发中断。
 *
 * @param uart_num UART端口号。
 * @param pattern_chr 图案的特征。
 * @param chr_num 字符数，8位值。
 * @param chr_tout 每个模式字符之间的间隔超时，16位值，单位是您配置的波特率周期。当持续时间大于此值时，它不会将此数据作为at_cmd字符。
 * @param post_idle 最后一个模式字符后的空闲时间，16位值，单位是您配置的波特率周期。当持续时间小于此值时，它不会将以前的数据作为最后一个at_cmd字符
 * @param pre_idle 第一个模式字符之前的空闲时间，16位值，单位是您配置的波特率周期。当持续时间小于此值时，它不会将此数据作为第一个at_cmd字符。
 *
 * @return
 *     -ESP_OK成功
 *     -ESP_FAIL参数错误
 */
esp_err_t uart_enable_pattern_det_baud_intr(uart_port_t uart_num, char pattern_chr, uint8_t chr_num, int chr_tout, int post_idle, int pre_idle);

/**
 * @brief 返回缓冲区中最近的检测图案位置。检测到的图案的位置保存在队列中，此函数将使第一个图案位置出列，并将指针移动到下一个图案位置。
 * @note  如果RX缓冲区已满且未启用流控制，则可能由于溢出而在RX缓冲区中找不到检测到的模式。
 *
 *        以下API将修改模式位置信息：uart_flush_input、uart_read_bytes、uart_dedriver_delete、uart_pop_pattern_pos使用模式检测功能时，应用程序负责确保对模式队列和rx数据缓冲区的原子访问。
 *
 * @param uart_num UART端口号，最大端口号为（UART_NUM_max-1）。
 * @return
 *     -（-1）未找到当前索引或参数错误的模式
 *     -其他的是rx缓冲区中的模式位置。
 */
int uart_pattern_pop_pos(uart_port_t uart_num);

/**
 * @brief 返回缓冲区中最近的检测图案位置。检测到的图案的位置保存在队列中，此函数对队列不做任何操作。
 * @note  如果RX缓冲区已满且未启用流控制，则可能由于溢出而在RX缓冲区中找不到检测到的模式。
 *
 *        以下API将修改模式位置信息：uart_flush_input、uart_read_bytes、uart_dedriver_delete、uart_pop_pattern_pos使用模式检测功能时，应用程序负责确保对模式队列和rx数据缓冲区的原子访问。
 *
 * @param uart_num UART端口号，最大端口号为（UART_NUM_max-1）。
 * @return
 *     -（-1）未找到当前索引或参数错误的模式
 *     -其他的是rx缓冲区中的模式位置。
 */
int uart_pattern_get_pos(uart_port_t uart_num);

/**
 * @brief 分配一个具有给定长度的新内存，将检测到的图案位置保存到rx缓冲区中。
 *
 * @param uart_num UART端口号，最大端口号为（UART_NUM_max-1）。
 * @param queue_length 检测到的模式的最大队列长度。如果队列长度不够大，可能会丢失一些模式位置。将此值设置为可以同时保存在数据缓冲区中的最大模式数。
 * @return
 *     -ESP_ERR_NO_MEM内存不足
 *     -未安装ESP_ERR_INVALID_STATE驱动程序
 *     -ESP_FAIL参数错误
 *     -ESP_OK成功
 */
esp_err_t uart_pattern_queue_reset(uart_port_t uart_num, int queue_length);

/**
 * @brief UART设置通信模式
 *
 * @note  当驱动程序对象初始化时，必须在uart_driver_install（）之后执行此函数。
 * @param uart_num     U要配置的端口号，最大端口号为（Uart_NUM_max-1）。
 * @param mode 要设置的UART UART模式
 *
 * @return
 *     -ESP_OK成功
 *     -ESP_ERR_INVALID_ARG参数错误
 */
esp_err_t uart_set_mode(uart_port_t uart_num, uart_mode_t mode);

/**
 * @brief 设置RX fifo满的uart阈值
 * @note 如果应用程序使用更高的波特率，并且观察到硬件RX fifo中的字节被覆盖，则可以降低此阈值
 *
 * @param uart_num UART_NUM_0、UART_NUM_1或UART_NUM_2
 * @param threshold 生成RX fifo完全中断的阈值
 *
 * @return
 *     -ESP_OK成功
 *     -ESP_ERR_INVALID_ARG参数错误
 *     -未安装ESP_ERR_INVALID_STATE驱动程序
 */
esp_err_t uart_set_rx_full_threshold(uart_port_t uart_num, int threshold);

/**
 * @brief 为TX fifo空设置uart阈值
 *
 * @param uart_num UART_NUM_0、UART_NUM_1或UART_NUM_2
 * @param threshold 生成TX fifo空中断的阈值
 *
 * @return
 *     -ESP_OK成功
 *     -ESP_ERR_INVALID_ARG参数错误
 *     -未安装ESP_ERR_INVALID_STATE驱动程序
 */
esp_err_t uart_set_tx_empty_threshold(uart_port_t uart_num, int threshold);

/**
 * @brief UART为TOUT功能设置阈值超时
 *
 * @param uart_num     U要配置的端口号，最大端口号为（Uart_NUM_max-1）。
 * @param tout_thresh  此参数定义uart符号周期中的超时阈值。阈值的最大值为126。tout_thresh=1，定义tout中断超时等于当前波特率上一个符号（~11位）的传输时间。如果时间到期，将触发UART_RXFIFO_TOUT_INT中断。如果tout_thresh==0，则禁用tout功能。
 *
 * @return
 *     -ESP_OK成功
 *     -ESP_ERR_INVALID_ARG参数错误
 *     -未安装ESP_ERR_INVALID_STATE驱动程序
 */
esp_err_t uart_set_rx_timeout(uart_port_t uart_num, const uint8_t tout_thresh);

/**
 * @brief 返回RS485模式的冲突检测标志函数将冲突检测标志返回到collision_flag所指向的变量中。collision_flag=true，如果检测到冲突，则等于false。应在实际传输完成时（uart_write_bytes（）之后）执行此函数。
 *
 * @param uart_num  用于配置最大端口号的部件号为（Uart_NUM_max-1）。
 * @param collision_flag 指向布尔类型变量的指针，以返回冲突标志。
 *
 * @return
 *     -ESP_OK成功
 *     -ESP_ERR_INVALID_ARG参数错误
 */
esp_err_t uart_get_collision_flag(uart_port_t uart_num, bool* collision_flag);

/**
 * @brief 设置浅睡眠唤醒的RX引脚信号边缘数
 *
 * UART可用于将系统从浅睡眠中唤醒。此功能通过计数RX引脚上的正边缘数并将计数与阈值进行比较来工作。当计数超过阈值时，系统将从浅睡眠中唤醒。此功能允许设置阈值。
 *
 * 停止位和奇偶校验位（如果启用）也有助于边缘的数量。例如，带有ASCII代码97的字母“a”在导线上编码为0100001101（具有8n1配置），包括开始和停止位。此序列有3条正边（从0到1的过渡）。因此，要在发送“a”时唤醒系统，请设置wakeup_threshold=3。
 *
 * 触发唤醒的字符未被UART接收（即无法从UART FIFO获取）。根据波特率，在此之后的几个字符也不会被接收。请注意，当芯片进入和退出浅睡眠模式时，APB频率将发生变化。为了确保UART始终具有正确的波特率，通过将UART_config_t中的use_REF_TICK字段设置为true，选择REF_TICK作为UART时钟源。
 *
 * @note 在ESP32中，唤醒信号只能通过IO_MUX输入（即GPIO3应配置为唤醒UART0的功能1，GPIO9应配置为激活UART1的功能5），UART2不支持轻睡眠唤醒功能。
 *
 * @param uart_num  UART号，最大端口号为（UART_NUM_max-1）。
 * @param wakeup_threshold  浅睡眠唤醒的RX边缘数，值为3...0x3ff。
 * @return
 *      -成功时ESP_OK
 *      -如果uart_num不正确或唤醒阈值超出[3，0x3ff]范围，则返回ESP_ERR_INVALID_ARG。
 */
esp_err_t uart_set_wakeup_threshold(uart_port_t uart_num, int wakeup_threshold);

/**
 * @brief 获取浅睡眠唤醒的RX引脚信号边缘数。
 *
 * 有关uart唤醒功能的说明，请参阅uart_set_wakeup_threshold的说明。
 *
 * @param uart_num  UART号，最大端口号为（UART_NUM_max-1）。
 * @param[out] out_wakeup_threshold  输出，设置为给定UART的唤醒阈值的当前值。
 * @return
 *      -成功时ESP_OK
 *      -如果out_wakeup_threshold为空，则ESP_ERR_INVALID_ARG
 */
esp_err_t uart_get_wakeup_threshold(uart_port_t uart_num, int* out_wakeup_threshold);

/**
  * @brief 等待UART tx内存为空，最后一个字符发送ok（轮询模式）。
  *
  * @param uart_num UART编号
  *
  * * @return
  *      -成功时ESP_OK
  *      -ESP_ERR_INVALID_ARG参数错误
  *      -未安装ESP_FAIL驱动程序
  */
esp_err_t uart_wait_tx_idle_polling(uart_port_t uart_num);

/**
  * @brief 将TX信号回路配置回RX模块，仅用于测试用途。
  *
  * @param uart_num UART编号
  * @param loop_back_en 设置ture以启用循环返回功能，否则设置为false。
  *
  * * @return
  *      -成功时ESP_OK
  *      -ESP_ERR_INVALID_ARG参数错误
  *      -未安装ESP_FAIL驱动程序
  */
esp_err_t uart_set_loop_back(uart_port_t uart_num, bool loop_back_en);

/**
  * @brief 配置UART RX超时中断的行为。
  *
  * 当always_rx_timeout为真时，即使FIFO已满，也会触发超时中断。此函数可导致仅为发送超时事件而触发的额外超时中断。仅当您希望确保超时中断总是在字节流之后发生时，才调用此函数。
  *
  * @param uart_num UART编号
  * @param always_rx_timeout_en 设置为false启用超时中断的默认行为，设置为true始终触发超时中断。
  *
  */
void uart_set_always_rx_timeout(uart_port_t uart_num, bool always_rx_timeout_en);

#ifdef __cplusplus
}
#endif

