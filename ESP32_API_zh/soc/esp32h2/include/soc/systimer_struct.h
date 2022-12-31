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

/**配置寄存器*/
/** conf寄存器SYSTIMER_conf的类型。
 */
typedef union {
    struct {
        /** systimer_clk_fo:R/W；位位置：[0]；默认值：0；系统时钟力开启
         */
        uint32_t systimer_clk_fo: 1;
        uint32_t reserved_1: 21;
        /** target2_work_en:R/W；位位置：[22]；默认值：0；target2工作启用
         */
        uint32_t target2_work_en: 1;
        /** target1_work_en:R/W；位位置：[23]；默认值：0；target1工作启用
         */
        uint32_t target1_work_en: 1;
        /** target0_work_en:R/W；位位置：[24]；默认值：0；target0工作启用
         */
        uint32_t target0_work_en: 1;
        /** 计时器单元1_core1_stall_en：R/W；位位置：[25]；默认值：1；如果核心1暂停时计时器第一单元暂停
         */
        uint32_t timer_unit1_core1_stall_en: 1;
        /** 计时器单元1核心0停止：R/W；位位置：[26]；默认值：1；如果核心0停止时计时器第一单元停止
         */
        uint32_t timer_unit1_core0_stall_en: 1;
        /** timer_unit0_core1_stall_en:R/W；位位置：[27]；默认值：0；如果内核1停止时计时器单元0停止
         */
        uint32_t timer_unit0_core1_stall_en: 1;
        /** timer_unit0_core0_install_en:R/W；位位置：[28]；默认值：0；如果内核0停止时计时器单元0停止
         */
        uint32_t timer_unit0_core0_stall_en: 1;
        /** timer_unit1_work_en：读/写；位位置：[29]；默认值：0；定时器第一单元工作启用
         */
        uint32_t timer_unit1_work_en: 1;
        /** timer_unit0_work_en:R/W；位位置：[30]；默认值：1；计时器单元0工作启用
         */
        uint32_t timer_unit0_work_en: 1;
        /** clk_en:R/W；位位置：[31]；默认值：0；寄存器文件clk门控
         */
        uint32_t clk_en: 1;
    };
    uint32_t val;
} systimer_conf_reg_t;

/** unit_op寄存器SYSTIMER_unit_op的类型。
 */
typedef union {
    struct {
        uint32_t reserved_0: 29;
        /** timer_unit_value_valid:R/SS/WTC；位位置：[29]；默认值：0；reg_timer_unit0_value_valid
         */
        uint32_t timer_unit_value_valid: 1;
        /** timer_unit_update:WT；位位置：[30]；默认值：0；更新timer_unit0
         */
        uint32_t timer_unit_update: 1;
        uint32_t reserved31: 1;
    };
    uint32_t val;
} systimer_unit_op_reg_t;

/** 单元加载寄存器类型SYSTIMER_unit_load
 */
typedef struct {
    union {
        struct {
            /** timer_unit_load_hi:R/W；比特位置：[19:0]；默认值：0；计时器单元负载高32位
             */
            uint32_t timer_unit_load_hi: 20;
            uint32_t reserved20: 12;
        };
        uint32_t val;
    } hi;
    union {
        struct {
            /** timer_unit_load_lo:R/W；位位置：[31:0]；默认值：0；计时器单元负载低32位
             */
            uint32_t timer_unit_load_lo: 32;
        };
        uint32_t val;
    } lo;
} systimer_unit_load_val_reg_t;

/** 目标寄存器SYSTIMER_target的类型。
 */
typedef struct {
    union {
        struct {
            /** timer_target_hi:R/W；比特位置：[19:0]；默认值：0；计时器目标高32位
             */
            uint32_t timer_target_hi: 20;
            uint32_t reserved20: 12;
        };
        uint32_t val;
    } hi;
    union {
        struct {
            /** timer_target_lo:R/W；位位置：[31:0]；默认值：0；计时器目标低32位
             */
            uint32_t timer_target_lo: 32;
        };
        uint32_t val;
    } lo;
} systimer_target_val_reg_t;

/** target_conf寄存器SYSTIMER_target_conf的类型。
 */
typedef union {
    struct {
        /** 目标周期：R/W；位位置：[25:0]；默认值：0；目标周期
         */
        uint32_t target_period: 26;
        uint32_t reserved_26: 4;
        /** 目标周期模式：R/W；位位置：[30]；默认值：0；将目标设置为周期模式
         */
        uint32_t target_period_mode: 1;
        /** 目标时间单位：R/W；位位置：[31]；默认值：0；选择要比较的单位
         */
        uint32_t target_timer_unit_sel: 1;
    };
    uint32_t val;
} systimer_target_conf_reg_t;

/** unit_value_hi寄存器SYSTIMER_unit_value_hi的类型。
 */
typedef struct {
    union {
        struct {
            /** timer_unit_value_hi:RO；比特位置：[19:0]；默认值：0；计时器读取值高20bit
             */
            uint32_t timer_unit_value_hi: 20;
            uint32_t reserved20: 12;
        };
        uint32_t val;
    } hi;
    union {
        struct {
            /** timer_unit_value_lo:RO；位位置：[31:0]；默认值：0；计时器读取值低32位
             */
            uint32_t timer_unit_value_lo: 32;
        };
        uint32_t val;
    } lo;
} systimer_unit_value_reg_t;

/** comp_load寄存器SYSTIMER_comp_load的类型。
 */
typedef union {
    struct {
        /** timer_comp_load:WT；位位置：[0]；默认值：0；计时器补偿负载值
         */
        uint32_t timer_comp_load: 1;
        uint32_t reserved1: 31;
    };
    uint32_t val;
} systimer_comp_load_reg_t;

/** unit_load寄存器SYSTIMER_unit_load的类型。
 */
typedef union {
    struct {
        /** timer_unit_load:WT；位位置：[0]；默认值：0；计时器单元负载值
         */
        uint32_t timer_unit_load: 1;
        uint32_t reserved1: 31;
    };
    uint32_t val;
} systimer_unit_load_reg_t;

/**中断寄存器*/
/** int_ena寄存器SYSTIMER_int_ena的类型。
 */
typedef union {
    struct {
        /** target0_int_ena:R/W；位位置：[0]；默认值：0；interupt0启用
         */
        uint32_t target0_int_ena: 1;
        /** target1_int_ena:R/W；位位置：[1]；默认值：0；interupt1启用
         */
        uint32_t target1_int_ena: 1;
        /** target2_int_ena:R/W；位位置：[2]；默认值：0；interupt2启用
         */
        uint32_t target2_int_ena: 1;
        uint32_t reserved3: 29;
    };
    uint32_t val;
} systimer_int_ena_reg_t;

/** int_raw寄存器SYSTIMER_int_raw的类型。
 */
typedef union {
    struct {
        /** target0_int_raw:R/WTC/SS；位位置：[0]；默认值：0；中断0原始
         */
        uint32_t target0_int_raw: 1;
        /** target1_int_raw:R/WTC/SS；位位置：[1]；默认值：0；中断1原始
         */
        uint32_t target1_int_raw: 1;
        /** target2_int_raw:R/WTC/SS；位位置：[2]；默认值：0；中断2原始
         */
        uint32_t target2_int_raw: 1;
        uint32_t reserved3: 29;
    };
    uint32_t val;
} systimer_int_raw_reg_t;

/** int_clr寄存器SYSTIMER_int_clr的类型。
 */
typedef union {
    struct {
        /** target0_int_clr:WT；位位置：[0]；默认值：0；中断0清除
         */
        uint32_t target0_int_clr: 1;
        /** target1_int_clr:WT；位位置：[1]；默认值：0；中断1清除
         */
        uint32_t target1_int_clr: 1;
        /** target2_int_clr:WT；位位置：[2]；默认值：0；中断2清除
         */
        uint32_t target2_int_clr: 1;
        uint32_t reserved3: 29;
    };
    uint32_t val;
} systimer_int_clr_reg_t;

/** int_st寄存器SYSTIMER_int_st的类型。
 */
typedef union {
    struct {
        /** target0_int_st:RO；位位置：[0]；默认值：0；调整目标时间
         */
        uint32_t target0_int_st: 1;
        /** target1_int_st:RO；位位置：[1]；默认值：0；注册目标1
         */
        uint32_t target1_int_st: 1;
        /** target2_int_st:RO；位位置：[2]；默认值：0；寄存器目标2
         */
        uint32_t target2_int_st: 1;
        uint32_t reserved3: 29;
    };
    uint32_t val;
} systimer_int_st_reg_t;


/**版本寄存器*/
/** 日期寄存器SYSTIMER_date的类型。
 */
typedef union {
    struct {
        /** 日期：R/W；位位置：[31:0]；默认值：33579377；注册日期（_D）
         */
        uint32_t date: 32;
    };
    uint32_t val;
} systimer_date_reg_t;


typedef struct {
    volatile systimer_conf_reg_t conf;
    volatile systimer_unit_op_reg_t unit_op[2];
    volatile systimer_unit_load_val_reg_t unit_load_val[2];
    volatile systimer_target_val_reg_t target_val[3];
    volatile systimer_target_conf_reg_t target_conf[3];
    volatile systimer_unit_value_reg_t unit_val[2];
    volatile systimer_comp_load_reg_t comp_load[3];
    volatile systimer_unit_load_reg_t unit_load[2];
    volatile systimer_int_ena_reg_t int_ena;
    volatile systimer_int_raw_reg_t int_raw;
    volatile systimer_int_clr_reg_t int_clr;
    volatile systimer_int_st_reg_t int_st;
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

