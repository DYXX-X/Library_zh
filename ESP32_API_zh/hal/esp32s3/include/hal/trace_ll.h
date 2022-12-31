/*
 * SPDX文件版权文本：2020-2021浓缩咖啡系统（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */

#pragma once
#include <stdlib.h>

#include "soc/dport_reg.h"
#include "soc/tracemem_config.h"

static inline void trace_ll_set_mem_block(int cpu, int block)
{
    uint32_t block_bits = 0;

    if (cpu == 0) {
        block_bits = TRACEMEM_CORE0_MUX_BLK_BITS(block);
    } else {
        block_bits = TRACEMEM_CORE1_MUX_BLK_BITS(block);
    }
    DPORT_SET_PERI_REG_MASK(SENSITIVE_INTERNAL_SRAM_USAGE_2_REG, block_bits);
}

