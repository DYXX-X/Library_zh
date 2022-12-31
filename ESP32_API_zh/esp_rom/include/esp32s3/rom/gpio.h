// 版权所有2010-2020 Espressif Systems（上海）私人有限公司
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

#pragma once

#include <stdint.h>
#include <stdbool.h>
#include "soc/gpio_reg.h"

#ifdef __cplusplus
extern "C" {
#endif

/** \defgroup gpio_apis、uart配置和通信相关api
  * @brief gpio api
  */

/** @addtogroup gpio_apis公司@{
  */

#define GPIO_REG_READ(reg)              READ_PERI_REG(reg)
#define GPIO_REG_WRITE(reg, val)        WRITE_PERI_REG(reg, val)
#define GPIO_ID_PIN0                    0
#define GPIO_ID_PIN(n)                  (GPIO_ID_PIN0+(n))
#define GPIO_PIN_ADDR(i)                (GPIO_PIN0_REG + i*4)

#define GPIO_FUNC_IN_HIGH               0x38
#define GPIO_FUNC_IN_LOW                0x3C

#define GPIO_ID_IS_PIN_REGISTER(reg_id) \
    ((reg_id >= GPIO_ID_PIN0) && (reg_id <= GPIO_ID_PIN(GPIO_PIN_COUNT-1)))

#define GPIO_REGID_TO_PINIDX(reg_id) ((reg_id) - GPIO_ID_PIN0)

typedef enum {
    GPIO_PIN_INTR_DISABLE = 0,
    GPIO_PIN_INTR_POSEDGE = 1,
    GPIO_PIN_INTR_NEGEDGE = 2,
    GPIO_PIN_INTR_ANYEDGE = 3,
    GPIO_PIN_INTR_LOLEVEL = 4,
    GPIO_PIN_INTR_HILEVEL = 5
} GPIO_INT_TYPE;

#define GPIO_OUTPUT_SET(gpio_no, bit_value) \
        ((gpio_no < 32) ? gpio_output_set(bit_value<<gpio_no, (bit_value ? 0 : 1)<<gpio_no, 1<<gpio_no,0) : \
                         gpio_output_set_high(bit_value<<(gpio_no - 32), (bit_value ? 0 : 1)<<(gpio_no - 32), 1<<(gpio_no -32),0))
#define GPIO_DIS_OUTPUT(gpio_no)    ((gpio_no < 32) ? gpio_output_set(0,0,0, 1<<gpio_no) : gpio_output_set_high(0,0,0, 1<<(gpio_no - 32)))
#define GPIO_INPUT_GET(gpio_no)     ((gpio_no < 32) ? ((gpio_input_get()>>gpio_no)&BIT0) : ((gpio_input_get_high()>>(gpio_no - 32))&BIT0))

/* GPIO中断处理程序，通过GPIO_intr_handler_register注册*/
typedef void (* gpio_intr_handler_fn_t)(uint32_t intr_mask, bool high, void *arg);

/**
  * @brief 初始化GPIO。这包括读取GPIO配置数据集以初始化每个GPIO引脚的“输出启用”和引脚配置。请不要在SDK中调用此函数。
  *
  * @param  None
  *
  * @return 没有一个
  */
void gpio_init(void);

/**
  * @brief 通过设置、清除或禁用GPIO0<->BIT（0）引脚来更改GPIO（0-31）引脚输出。没有特定的订购保证；因此，如果写入顺序很重要，调用代码应该将单个调用划分为多个调用。
  *
  * @param  uint32_t setmask：需要高级别的gpios。
  *
  * @param  uint32_t clearmask：需要低级别的gpios。
  *
  * @param  uint32_t enablemask：需要更改的gpios。
  *
  * @param  uint32_t disablemask：需要diable输出的gpios。
  *
  * @return 没有一个
  */
void gpio_output_set(uint32_t set_mask, uint32_t clear_mask, uint32_t enable_mask, uint32_t disable_mask);

/**
  * @brief 通过设置、清除或禁用GPIO32<->BIT（0）引脚来更改GPIO（32-39）引脚输出。没有特定的订购保证；因此，如果写入顺序很重要，调用代码应该将单个调用划分为多个调用。
  *
  * @param  uint32_t setmask：需要高级别的gpios。
  *
  * @param  uint32_t clearmask：需要低级别的gpios。
  *
  * @param  uint32_t enablemask：需要更改的gpios。
  *
  * @param  uint32_t disablemask：需要diable输出的gpios。
  *
  * @return 没有一个
  */
void gpio_output_set_high(uint32_t set_mask, uint32_t clear_mask, uint32_t enable_mask, uint32_t disable_mask);

/**
  * @brief 采样GPIO输入引脚（0-31）的值并返回位掩码。
  *
  * @param None
  *
  * @return uint32_t:GPIO输入引脚的位掩码，GPIO0的位（0）。
  */
uint32_t gpio_input_get(void);

/**
  * @brief 采样GPIO输入引脚（32-39）的值并返回位掩码。
  *
  * @param None
  *
  * @return uint32_t:GPIO输入引脚的位掩码，GPIO32的位（0）。
  */
uint32_t gpio_input_get_high(void);

/**
  * @brief 为GPIO引脚中断注册特定于应用程序的中断处理程序。一旦调用了中断处理程序，在调用gpio_intr_ack之后才会再次调用它。请不要在SDK中调用此函数。
  *
  * @param gpio_intr_handler_fn_t fn:gpio应用程序特定中断处理程序
  *
  * @param void *arg:gpio应用程序特定的中断处理程序参数。
  *
  * @return 没有一个
  */
void gpio_intr_handler_register(gpio_intr_handler_fn_t fn, void *arg);

/**
  * @brief 获取发生但未处理的gpio中断。请不要在SDK中调用此函数。
  *
  * @param None
  *
  * @return uint32_t:GPIO未决中断的位掩码，GPIO0的位（0）。
  */
uint32_t gpio_intr_pending(void);

/**
  * @brief 获取发生但未处理的gpio中断。请不要在SDK中调用此函数。
  *
  * @param None
  *
  * @return uint32_t:GPIO未决中断的位掩码，GPIO32的位（0）。
  */
uint32_t gpio_intr_pending_high(void);

/**
  * @brief 确认gpio中断以处理挂起的中断。请不要在SDK中调用此函数。
  *
  * @param uint32_t ack_mask：GPIO ack中断的位掩码，GPIO0的位掩码（0）。
  *
  * @return 没有一个
  */
void gpio_intr_ack(uint32_t ack_mask);

/**
  * @brief 确认gpio中断以处理挂起的中断。请不要在SDK中调用此函数。
  *
  * @param uint32_t ack_mask：GPIO ack中断的位掩码，GPIO32的位（0）。
  *
  * @return 没有一个
  */
void gpio_intr_ack_high(uint32_t ack_mask);

/**
  * @brief 设置GPIO以唤醒ESP32。请不要在SDK中调用此函数。
  *
  * @param uint32_t i： gpio编号。
  *
  * @param GPIO_INT_TYPE intr_state：只能使用GPIO_PIN_intr_LOLEVEL\GPIO_PIN_intr_HILEVEL
  *
  * @return 没有一个
  */
void gpio_pin_wakeup_enable(uint32_t i, GPIO_INT_TYPE intr_state);

/**
  * @brief 禁用GPIO以唤醒ESP32。请不要在SDK中调用此函数。
  *
  * @param None
  *
  * @return 没有一个
  */
void gpio_pin_wakeup_disable(void);

/**
  * @brief 将gpio输入设置为一个信号，一个gpio可以输入多个信号。
  *
  * @param uint32_t gpio：gpio编号，0~0x2f gpio==0x3C，输入0到信号gpio==0x3A，不输入任何到信号gpio==0x38，输入1到信号
  *
  * @param uint32_t signal_idx：信号索引。
  *
  * @param bool inv：信号是否为inv
  *
  * @return 没有一个
  */
void gpio_matrix_in(uint32_t gpio, uint32_t signal_idx, bool inv);

/**
  * @brief 设置信号输出到gpio，一个信号可以输出到多个gpio。
  *
  * @param uint32_t gpio:gpio编号，0~0x2f
  *
  * @param uint32_t signal_idx：信号索引。signal_idx==0x100，取消输入gpio的输出
  *
  * @param bool out_inv：信号输出是否反相
  *
  * @param bool oen_inv：信号输出使能是否反相
  *
  * @return 没有一个
  */
void gpio_matrix_out(uint32_t gpio, uint32_t signal_idx, bool out_inv, bool oen_inv);

/**
  * @brief 从IOMUX选择pad作为gpio函数。
  *
  * @param uint32_t gpio_num:gpio编号，0~0x2f
  *
  * @return 没有一个
  */
void gpio_pad_select_gpio(uint32_t gpio_num);

/**
  * @brief 设置极板驱动程序功能。
  *
  * @param uint32_t gpio_num:gpio编号，0~0x2f
  *
  * @param uint32_t drv:0-3
  *
  * @return 没有一个
  */
void gpio_pad_set_drv(uint32_t gpio_num, uint32_t drv);

/**
  * @brief 从gpio编号拔出极板。
  *
  * @param uint32_t gpio_num:gpio编号，0~0x2f
  *
  * @return 没有一个
  */
void gpio_pad_pullup(uint32_t gpio_num);

/**
  * @brief 从gpio编号上拉下衬垫。
  *
  * @param uint32_t gpio_num:gpio编号，0~0x2f
  *
  * @return 没有一个
  */
void gpio_pad_pulldown(uint32_t gpio_num);

/**
  * @brief 从gpio编号中取出极板。
  *
  * @param uint32_t gpio_num:gpio编号，0~0x2f
  *
  * @return 没有一个
  */
void gpio_pad_unhold(uint32_t gpio_num);

/**
  * @brief 按住gpio编号的键盘。
  *
  * @param uint32_t gpio_num:gpio编号，0~0x2f
  *
  * @return 没有一个
  */
void gpio_pad_hold(uint32_t gpio_num);

/**
  * @brief 启用gpio pad输入。
  *
  * @param uint32_t gpio_num:gpio编号，0~0x2f
  *
  * @return 没有一个
  */
void gpio_pad_input_enable(uint32_t gpio_num);

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

