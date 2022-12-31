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
#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>
#include "hal/misc.h"
#include "soc/dedic_gpio_struct.h"

static inline void dedic_gpio_ll_enable_instruction_access_out(dedic_dev_t *dev, uint32_t channel_mask, bool enable)
{
    if (enable) {
        dev->gpio_out_cpu.val |= channel_mask;
    } else {
        dev->gpio_out_cpu.val &= ~channel_mask;
    }
}

static inline void dedic_gpio_ll_write_all(dedic_dev_t *dev, uint32_t value)
{
    dev->gpio_out_drt.val = value;
}

static inline void dedic_gpio_ll_write_mask(dedic_dev_t *dev, uint32_t channel_mask, uint32_t value)
{
    dedic_gpio_out_msk_reg_t d = {
        .gpio_out_msk = channel_mask,
        .gpio_out_value = value
    };
    dev->gpio_out_msk.val = d.val;
}

static inline void dedic_gpio_ll_set_channel(dedic_dev_t *dev, uint32_t channel)
{
    dev->gpio_out_idv.val = 1 << (2 * channel);
}

static inline void dedic_gpio_ll_clear_channel(dedic_dev_t *dev, uint32_t channel)
{
    dev->gpio_out_idv.val = 2 << (2 * channel);
}

static inline void dedic_gpio_ll_toggle_channel(dedic_dev_t *dev, uint32_t channel)
{
    dev->gpio_out_idv.val = 3 << (2 * channel);
}

static inline uint32_t dedic_gpio_ll_read_out_all(dedic_dev_t *dev)
{
    return HAL_FORCE_READ_U32_REG_FIELD(dev->gpio_out_scan, gpio_out_status);
}

static inline uint32_t dedic_gpio_ll_read_in_all(dedic_dev_t *dev)
{
    return HAL_FORCE_READ_U32_REG_FIELD(dev->gpio_in_scan, gpio_in_status);
}

static inline void dedic_gpio_ll_set_input_delay(dedic_dev_t *dev, uint32_t channel, uint32_t delay_cpu_clks)
{
    dev->gpio_in_dly.val &= ~(3 << (2 * channel));
    dev->gpio_in_dly.val |= (delay_cpu_clks & 0x03) << (2 * channel);
}

static inline uint32_t dedic_gpio_ll_get_input_delay(dedic_dev_t *dev, uint32_t channel)
{
    return (dev->gpio_in_dly.val & (3 << (2 * channel)) >> (2 * channel));
}

static inline void dedic_gpio_ll_set_interrupt_type(dedic_dev_t *dev, uint32_t channel, uint32_t type)
{
    dev->gpio_intr_rcgn.val &= ~(7 << (3 * channel));
    dev->gpio_intr_rcgn.val |= (type & 0x07) << (3 * channel);
}

static inline void dedic_gpio_ll_enable_interrupt(dedic_dev_t *dev, uint32_t channel_mask, bool enable)
{
    if (enable) {
        dev->gpio_intr_rls.val |= channel_mask;
    } else {
        dev->gpio_intr_rls.val &= ~channel_mask;
    }
}

static inline uint32_t __attribute__((always_inline)) dedic_gpio_ll_get_interrupt_status(dedic_dev_t *dev)
{
    return dev->gpio_intr_st.val;
}

static inline void __attribute__((always_inline)) dedic_gpio_ll_clear_interrupt_status(dedic_dev_t *dev, uint32_t channel_mask)
{
    dev->gpio_intr_clr.val = channel_mask;
}

#ifdef __cplusplus
}
#endif

