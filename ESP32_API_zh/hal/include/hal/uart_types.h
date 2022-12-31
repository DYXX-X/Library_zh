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

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>
#include "soc/soc_caps.h"


/**
 * @brief UART端口号，可以是UART_NUM_0~（UART_NUM_MAX-1）。
 */
typedef int uart_port_t;

/**
 * @brief UART模式选择
 */
typedef enum {
    UART_MODE_UART = 0x00,                      /*!< 模式：常规UART模式*/
    UART_MODE_RS485_HALF_DUPLEX = 0x01,         /*!< 模式：由RTS引脚控制的半双工RS485 UART模式*/
    UART_MODE_IRDA = 0x02,                      /*!< 模式：IRDA UART模式*/
    UART_MODE_RS485_COLLISION_DETECT = 0x03,    /*!< 模式：RS485碰撞检测UART模式（用于测试）*/
    UART_MODE_RS485_APP_CTRL = 0x04,            /*!< 模式：应用程序控制RS485 UART模式（用于测试）*/
} uart_mode_t;

/**
 * @brief UART字长常量
 */
typedef enum {
    UART_DATA_5_BITS   = 0x0,    /*!< 字长：5位*/
    UART_DATA_6_BITS   = 0x1,    /*!< 字长：6位*/
    UART_DATA_7_BITS   = 0x2,    /*!< 字长：7位*/
    UART_DATA_8_BITS   = 0x3,    /*!< 字长：8位*/
    UART_DATA_BITS_MAX = 0x4,
} uart_word_length_t;

/**
 * @brief UART停止位数
 */
typedef enum {
    UART_STOP_BITS_1   = 0x1,  /*!< 停止位：1位*/
    UART_STOP_BITS_1_5 = 0x2,  /*!< 停止位：1.5位*/
    UART_STOP_BITS_2   = 0x3,  /*!< 停止位：2位*/
    UART_STOP_BITS_MAX = 0x4,
} uart_stop_bits_t;

/**
 * @brief UART奇偶校验常数
 */
typedef enum {
    UART_PARITY_DISABLE  = 0x0,  /*!< 禁用UART奇偶校验*/
    UART_PARITY_EVEN     = 0x2,  /*!< 启用UART偶校验*/
    UART_PARITY_ODD      = 0x3   /*!< 启用UART奇数奇偶校验*/
} uart_parity_t;

/**
 * @brief UART硬件流量控制模式
 */
typedef enum {
    UART_HW_FLOWCTRL_DISABLE = 0x0,   /*!< 禁用硬件流控制*/
    UART_HW_FLOWCTRL_RTS     = 0x1,   /*!< 启用RX硬件流控制（rts）*/
    UART_HW_FLOWCTRL_CTS     = 0x2,   /*!< 启用TX硬件流量控制（cts）*/
    UART_HW_FLOWCTRL_CTS_RTS = 0x3,   /*!< 启用硬件流控制*/
    UART_HW_FLOWCTRL_MAX     = 0x4,
} uart_hw_flowcontrol_t;

/**
 * @brief UART信号位图
 */
typedef enum {
    UART_SIGNAL_INV_DISABLE  =  0,            /*!< 禁用UART信号反相*/
    UART_SIGNAL_IRDA_TX_INV  = (0x1 << 0),    /*!< 反转UART irda_tx信号*/
    UART_SIGNAL_IRDA_RX_INV  = (0x1 << 1),    /*!< 反转UART irda_rx信号*/
    UART_SIGNAL_RXD_INV      = (0x1 << 2),    /*!< 反转UART rxd信号*/
    UART_SIGNAL_CTS_INV      = (0x1 << 3),    /*!< 反转UART cts信号*/
    UART_SIGNAL_DSR_INV      = (0x1 << 4),    /*!< 反转UART dsr信号*/
    UART_SIGNAL_TXD_INV      = (0x1 << 5),    /*!< 反转UART txd信号*/
    UART_SIGNAL_RTS_INV      = (0x1 << 6),    /*!< 反转UART rts信号*/
    UART_SIGNAL_DTR_INV      = (0x1 << 7),    /*!< 反转UART dtr信号*/
} uart_signal_inv_t;

/**
 * @brief UART源时钟
 */
typedef enum {
    UART_SCLK_APB = 0x0,            /*!< 来自APB的UART源时钟*/
#if SOC_UART_SUPPORT_RTC_CLK
    UART_SCLK_RTC = 0x1,            /*!< 来自RTC的UART源时钟*/
#endif
#if SOC_UART_SUPPORT_XTAL_CLK
    UART_SCLK_XTAL = 0x2,           /*!< 来自XTAL的UART源时钟*/
#endif
#if SOC_UART_SUPPORT_REF_TICK
    UART_SCLK_REF_TICK = 0x3,       /*!< 来自REF_TICK的UART源时钟*/
#endif
} uart_sclk_t;

/**
 * @brief UART AT cmd char配置参数请注意，此功能在不同芯片上可能不同。请在确认时参考TRM。
 */
typedef struct {
    uint8_t  cmd_char;             /*!< UART AT命令字符*/
    uint8_t  char_num;             /*!< AT cmd字符重复编号*/
    uint32_t gap_tout;             /*!< AT cmd字符之间的间隔时间（波特率）*/
    uint32_t pre_idle;             /*!< 非AT字符和第一个AT字符之间的空闲时间（波特率）*/
    uint32_t post_idle;            /*!< 最后一个AT字符和无AT字符之间的空闲时间（波特率）*/
} uart_at_cmd_t;

/**
 * @brief UART软件流控制配置参数
 */
typedef struct {
    uint8_t  xon_char;      /*!< Xon流量控制字符*/
    uint8_t  xoff_char;     /*!< Xoff流量控制字符*/
    uint8_t xon_thrd;      /*!< 如果启用了软件流控制，并且rxfifo中的数据量小于xon_thrd，则将发送一个xon_char*/
    uint8_t xoff_thrd;       /*!< 如果启用了软件流控制，并且rxfifo中的数据量大于xoff_thrd，则将发送xoff_char*/
} uart_sw_flowctrl_t;

/**
 * @brief UART_param_config函数的UART配置参数
 */
typedef struct {
    int baud_rate;                      /*!< UART波特率*/
    uart_word_length_t data_bits;       /*!< UART字节大小*/
    uart_parity_t parity;               /*!< UART奇偶校验模式*/
    uart_stop_bits_t stop_bits;         /*!< UART停止位*/
    uart_hw_flowcontrol_t flow_ctrl;    /*!< UART HW流量控制模式（cts/rts）*/
    uint8_t rx_flow_ctrl_thresh;        /*!< UART HW RTS阈值*/
    union {
        uart_sclk_t source_clk;         /*!< UART源时钟选择*/
        bool use_ref_tick  __attribute__((deprecated)); /*!< 不推荐选择参考时钟源的方法，改为设置source_clk字段*/
    };
} uart_config_t;

#ifdef __cplusplus
}
#endif

