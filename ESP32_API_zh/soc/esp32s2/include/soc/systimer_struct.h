/** 版权所有2021 Espressif Systems（Shanghai）PTE LTD
 *
 *  根据Apache许可证2.0版（“许可证”）获得许可；除非符合许可证，否则不得使用此文件。您可以在以下地址获取许可证副本：
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  除非适用法律要求或书面同意，否则根据许可证分发的软件是按“原样”分发的，无任何明示或暗示的担保或条件。有关许可证下权限和限制的具体语言，请参阅许可证。
 */
#pragma once

#include <stdint.h>
#ifdef __cplusplus
extern "C" {
#endif

/** SYSTEM TIMER REGISTER */
/** conf寄存器类型配置系统计时器时钟
 */
typedef union {
    struct {
        /** clk_fo:R/W；位位置：[0]；默认值：0；系统计时器强制时钟启用
         */
        uint32_t clk_fo: 1;
        uint32_t reserved_1: 30;
        /** clk_en:R/W；位位置：[31]；默认值：0；寄存器时钟启用
         */
        uint32_t clk_en: 1;
    };
    uint32_t val;
} systimer_conf_reg_t;

/** 加载寄存器类型系统计时器的加载值
 */
typedef union {
    struct {
        uint32_t reserved_0: 31;
        /** timer_load：工单；位位置：[31]；默认值：0；系统计时器的负载值
         */
        uint32_t timer_load: 1;
    };
    uint32_t val;
} systimer_load_reg_t;

/** load_hi寄存器类型高32位加载到系统计时器
 */
typedef union {
    struct {
        /** timer_load_hi:R/W；位位置：[31:0]；默认值：0；高32位系统计时器负载
         */
        uint32_t timer_load_hi: 32;
    };
    uint32_t val;
} systimer_load_hi_reg_t;

/** load_lo寄存器类型低32位系统计时器负载
 */
typedef union {
    struct {
        /** timer_load_lo:R/W；位位置：[31:0]；默认值：0；低32位系统计时器负载
         */
        uint32_t timer_load_lo: 32;
    };
    uint32_t val;
} systimer_load_lo_reg_t;

/** 步进寄存器系统定时器累积步进类型
 */
typedef union {
    struct {
        /** timer_xtal_step:R/W；位位置：[9:0]；默认值：80；使用XTAL时的系统计时器累积步骤
         */
        uint32_t timer_xtal_step: 10;
        /** timer_pll_step:R/W；比特位置：[19:10]；默认值：1；使用PLL时的系统计时器累积步骤
         */
        uint32_t timer_pll_step: 10;
        uint32_t reserved20: 12;
    };
    uint32_t val;
} systimer_step_reg_t;

/** target_val寄存器类型系统计时器目标值
 */
typedef struct {
    union {
        struct {
            /** timer_target_hi:R/W；位位置：[31:0]；默认值：0；系统计时器target0高32位
             */
            uint32_t timer_target_hi: 32;
        };
        uint32_t val;
    } hi;
    union {
        struct {
            /** timer_target_lo:R/W；位位置：[31:0]；默认值：0；系统计时器target0低32位
             */
            uint32_t timer_target_lo: 32;
        };
        uint32_t val;
    } lo;
} systimer_target_val_reg_t;

/** target_conf寄存器类型配置系统计时器目标工作模式
 */
typedef union {
    struct {
        /** 目标周期：R/W；位位置：[29:0]；默认值：0；系统计时器目标报警周期
         */
        uint32_t target_period: 30;
        /** 目标周期模式：R/W；位位置：[30]；默认值：0；系统计时器目标是否在周期模式下工作
         */
        uint32_t target_period_mode: 1;
        /** target_work_en:R/W；位位置：[31]；默认值：0；系统计时器目标工作启用
         */
        uint32_t target_work_en: 1;
    };
    uint32_t val;
} systimer_target_conf_reg_t;

/** 更新寄存器类型读取系统计时器值
 */
typedef union {
    struct {
        uint32_t reserved_0: 30;
        /** timer_value_valid:RO；位位置：[30]；默认值：0；如果从寄存器中读取计时器值是有效的
         */
        uint32_t timer_value_valid: 1;
        /** timer_update：工单；位位置：[31]；默认值：0；更新系统计时器值以注册
         */
        uint32_t timer_update: 1;
    };
    uint32_t val;
} systimer_update_reg_t;

/** 值类型_高位寄存器系统计时器32位
 */
typedef union {
    struct {
        /** timer_value_hi:RO；位位置：[31:0]；默认值：0；系统计时器高32位
         */
        uint32_t timer_value_hi: 32;
    };
    uint32_t val;
} systimer_value_hi_reg_t;

/** value类型_寄存器系统计时器低32位
 */
typedef union {
    struct {
        /** timer_value_lo:RO；位位置：[31:0]；默认值：0；系统计时器低32位
         */
        uint32_t timer_value_lo: 32;
    };
    uint32_t val;
} systimer_value_lo_reg_t;

/** int_ena寄存器系统定时器中断启用类型
 */
typedef union {
    struct {
        /** systimer_int0_ena:R/W；位位置：[0]；默认值：0；系统计时器target0中断启用
         */
        uint32_t systimer_int0_ena: 1;
        /** systimer_int1_ena:R/W；位位置：[1]；默认值：0；系统计时器target1中断启用
         */
        uint32_t systimer_int1_ena: 1;
        /** systimer_int2_ena:R/W；位位置：[2]；默认值：0；系统计时器target2中断启用
         */
        uint32_t systimer_int2_ena: 1;
        uint32_t reserved3: 29;
    };
    uint32_t val;
} systimer_int_ena_reg_t;

/** int_raw寄存器系统定时器中断类型原始
 */
typedef union {
    struct {
        /** systimer_int0_raw:RO；位位置：[0]；默认值：0；系统计时器target0中断原始
         */
        uint32_t systimer_int0_raw: 1;
        /** systimer_int1_raw:RO；位位置：[1]；默认值：0；系统计时器target1中断原始
         */
        uint32_t systimer_int1_raw: 1;
        /** systimer_int2_raw:RO；位位置：[2]；默认值：0；系统计时器target2中断原始
         */
        uint32_t systimer_int2_raw: 1;
        uint32_t reserved3: 29;
    };
    uint32_t val;
} systimer_int_raw_reg_t;

/** int_clr寄存器系统计时器中断清除类型
 */
typedef union {
    struct {
        /** systimer_int0_clr:WO；位位置：[0]；默认值：0；系统计时器target0中断清除
         */
        uint32_t systimer_int0_clr: 1;
        /** systimer_int1_clr:WO；位位置：[1]；默认值：0；系统计时器target1中断清除
         */
        uint32_t systimer_int1_clr: 1;
        /** systimer_int2_clr:WO；位位置：[2]；默认值：0；系统计时器target2中断清除
         */
        uint32_t systimer_int2_clr: 1;
        uint32_t reserved3: 29;
    };
    uint32_t val;
} systimer_int_clr_reg_t;


/** DATE */
/** 日期寄存器系统类型计时器寄存器版本
 */
typedef union {
    struct {
        /** 日期：R/W；位位置：[31:0]；默认值：25194848；系统计时器寄存器版本
         */
        uint32_t date: 32;
    };
    uint32_t val;
} systimer_date_reg_t;


typedef struct {
    volatile systimer_conf_reg_t conf;
    volatile systimer_load_reg_t load;
    volatile systimer_load_hi_reg_t load_hi;
    volatile systimer_load_lo_reg_t load_lo;
    volatile systimer_step_reg_t step;
    volatile systimer_target_val_reg_t target_val[3];
    volatile systimer_target_conf_reg_t target_conf[3];
    volatile systimer_update_reg_t update;
    volatile systimer_value_hi_reg_t value_hi;
    volatile systimer_value_lo_reg_t value_lo;
    volatile systimer_int_ena_reg_t int_ena;
    volatile systimer_int_raw_reg_t int_raw;
    volatile systimer_int_clr_reg_t int_clr;
    uint32_t reserved_050;
    uint32_t reserved_054;
    uint32_t reserved_058;
    uint32_t reserved_05c;
    uint32_t reserved_060;
    uint32_t reserved_064;
    uint32_t reserved_068;
    uint32_t reserved_06c;
    uint32_t reserved_070;
    uint32_t reserved_074;
    uint32_t reserved_078;
    uint32_t reserved_07c;
    uint32_t reserved_080;
    uint32_t reserved_084;
    uint32_t reserved_088;
    uint32_t reserved_08c;
    uint32_t reserved_090;
    uint32_t reserved_094;
    uint32_t reserved_098;
    uint32_t reserved_09c;
    uint32_t reserved_0a0;
    uint32_t reserved_0a4;
    uint32_t reserved_0a8;
    uint32_t reserved_0ac;
    uint32_t reserved_0b0;
    uint32_t reserved_0b4;
    uint32_t reserved_0b8;
    uint32_t reserved_0bc;
    uint32_t reserved_0c0;
    uint32_t reserved_0c4;
    uint32_t reserved_0c8;
    uint32_t reserved_0cc;
    uint32_t reserved_0d0;
    uint32_t reserved_0d4;
    uint32_t reserved_0d8;
    uint32_t reserved_0dc;
    uint32_t reserved_0e0;
    uint32_t reserved_0e4;
    uint32_t reserved_0e8;
    uint32_t reserved_0ec;
    uint32_t reserved_0f0;
    uint32_t reserved_0f4;
    uint32_t reserved_0f8;
    volatile systimer_date_reg_t date;
} systimer_dev_t;

extern systimer_dev_t SYSTIMER;

#ifdef __cplusplus
}
#endif

