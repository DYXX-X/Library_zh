// 版权所有2019 Espressif Systems（上海）私人有限公司
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

#include "soc/soc_caps.h"
#include "soc/uart_reg.h"
#include "soc/uart_struct.h"
#include "soc/periph_defs.h"
#include "soc/gpio_sig_map.h"
#include "soc/io_mux_reg.h"
#include "soc/uart_pins.h"

#ifdef __cplusplus
extern "C" {
#endif

#define SOC_UART_TX_PIN_IDX  (0)
#define SOC_UART_RX_PIN_IDX  (1)
#define SOC_UART_RTS_PIN_IDX (2)
#define SOC_UART_CTS_PIN_IDX (3)

/**
 * @brief 可用于检索特定UART的特定引脚信号的宏。
 */
#define UART_PERIPH_SIGNAL(IDX, PIN) (uart_periph_signal[(IDX)].pins[(PIN)].signal)

typedef struct {
    /* IOMUX中此UART引脚的默认GPIO编号。如果引脚没有默认GPIO，则该值可以为-1。例如，ESP32-C3没有U0CTS和U0RTS的任何默认GPIO。*/
    int32_t default_gpio    : 15;
    /* 应分配给GPIO用作UART的Func*/
    int32_t iomux_func      : 4;
    /* 标记当前UART引脚是否输入（或未输入）*/
    uint32_t input          : 1;
    /* GPIO信号映射中的信号。*/
    uint32_t signal         : 12;
} uart_periph_sig_t;

typedef struct {
    const uart_periph_sig_t pins[SOC_UART_PINS_COUNT];
    const uint8_t irq;
    const periph_module_t module;
} uart_signal_conn_t;

extern const uart_signal_conn_t uart_periph_signal[SOC_UART_NUM];

#ifdef __cplusplus
}
#endif

