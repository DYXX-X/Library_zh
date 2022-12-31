/**
 *  SPDX文件版权文本：2021浓缩咖啡系统（上海）有限公司
 *
 *  SPDX许可证标识符：Apache-2.0
 */
#pragma once

#include <stdint.h>
#ifdef __cplusplus
extern "C" {
#endif

/**组：T0控制和配置寄存器*/
/** txconfig寄存器类型Timer x配置寄存器
 */
typedef union {
    struct {
        uint32_t reserved_0:9;
        /** tx_use_xtal:R/W；位位置：[9]；默认值：0；1： 使用XTAL_CLK作为定时器组的源时钟。0：使用APB_CLK作为定时器组的源时钟。
         */
        uint32_t tx_use_xtal:1;
        /** tx_alarm_en:R/W/SC；位位置：[10]；默认值：0；设置后，警报启用。一旦发生报警，该位将自动清除。
         */
        uint32_t tx_alarm_en:1;
        uint32_t reserved_11:1;
        /** tx_divcnt_rst:WT；位位置：[12]；默认值：0；设置后，Timer x的时钟分频器计数器将被重置。
         */
        uint32_t tx_divcnt_rst:1;
        /** tx_dider:R/W；比特位置：[28:13]；默认值：1；计时器x时钟（Tx_clk）预分频器值。
         */
        uint32_t tx_divider:16;
        /** tx_autoreload:R/W；位位置：[29]；默认值：1；设置后，启用计时器x报警时自动重新加载。
         */
        uint32_t tx_autoreload:1;
        /** tx_increse:R/W；位位置：[30]；默认值：1；设置后，计时器x时基计数器将在每个时钟周期递增。清除时，计时器x时基计数器将递减。
         */
        uint32_t tx_increase:1;
        /** tx_en:R/W；位位置：[31]；默认值：0；设置后，启用计时器x时基计数器。
         */
        uint32_t tx_en:1;
    };
    uint32_t val;
} timg_txconfig_reg_t;

/** txlo寄存器类型定时器x当前值，低32位
 */
typedef union {
    struct {
        /** tx_lo:RO；位位置：[31:0]；默认值：0；在写入TIMG_TxUPDATE_REG之后，这里可以读取计时器x的时基计数器的低32位。
         */
        uint32_t tx_lo:32;
    };
    uint32_t val;
} timg_txlo_reg_t;

/** txhi寄存器类型计时器$x当前值，高22位
 */
typedef union {
    struct {
        /** tx_hi:RO；比特位置：[21:0]；默认值：0；在写入TIMG_T$xUPDATE_REG之后，可以在这里读取计时器$x的时基计数器的高22位。
         */
        uint32_t tx_hi:22;
        uint32_t reserved_22:10;
    };
    uint32_t val;
} timg_txhi_reg_t;

/** txupdate寄存器类型写入以将当前计时器值复制到TIMGn_T$x_（LO/HI）_REG
 */
typedef union {
    struct {
        uint32_t reserved_0:31;
        /** tx_update:R/W/SC；位位置：[31]；默认值：0；将0或1写入TIMG_T$xUPDATE_REG后，计数器值被锁存。
         */
        uint32_t tx_update:1;
    };
    uint32_t val;
} timg_txupdate_reg_t;

/** txalarmlo寄存器类型计时器$x报警值，低32位
 */
typedef union {
    struct {
        /** tx_alarm_lo:R/W；位位置：[31:0]；默认值：0；计时器$x报警触发时基计数器值，低32位。
         */
        uint32_t tx_alarm_lo:32;
    };
    uint32_t val;
} timg_txalarmlo_reg_t;

/** txalarmhi寄存器类型计时器$x报警值，高位
 */
typedef union {
    struct {
        /** tx_alarm_hi:R/W；比特位置：[21:0]；默认值：0；计时器$x报警触发时基计数器值，高22位。
         */
        uint32_t tx_alarm_hi:22;
        uint32_t reserved_22:10;
    };
    uint32_t val;
} timg_txalarmhi_reg_t;

/** txloadlo寄存器类型计时器$x重新加载值，低32位
 */
typedef union {
    struct {
        /** tx_load_lo:R/W；位位置：[31:0]；默认值：0；重新加载将加载到计时器$x时基计数器上的值的低32位。
         */
        uint32_t tx_load_lo:32;
    };
    uint32_t val;
} timg_txloadlo_reg_t;

/** txloadhi寄存器类型计时器$x重新加载值，高22位
 */
typedef union {
    struct {
        /** tx_load_hi:R/W；比特位置：[21:0]；默认值：0；重载将加载到计时器$x时基计数器上的值的高22位。
         */
        uint32_t tx_load_hi:22;
        uint32_t reserved_22:10;
    };
    uint32_t val;
} timg_txloadhi_reg_t;

/** txload寄存器类型从TIMG_T$x_（LOADLOLOADHI）_REG写入重新加载计时器
 */
typedef union {
    struct {
        /** tx_load:WT；位位置：[31:0]；默认值：0；
         *
         *  写入任何值以触发计时器$x时基计数器重新加载。
         */
        uint32_t tx_load:32;
    };
    uint32_t val;
} timg_txload_reg_t;


/**组：WDT控制和配置寄存器*/
/** wdtconfig0寄存器类型看门狗定时器配置寄存器
 */
typedef union {
    struct {
        uint32_t reserved_0:12;
        /** wdt_appcpu_reset_en:R/W；位位置：[12]；默认值：0；WDT重置CPU启用。
         */
        uint32_t wdt_appcpu_reset_en:1;
        /** wdt_procpu_reset_en:R/W；位位置：[13]；默认值：0；WDT重置CPU启用。
         */
        uint32_t wdt_procpu_reset_en:1;
        /** wdt_flashboot_mod_en:R/W；位位置：[14]；默认值：1；设置后，将启用闪存启动保护。
         */
        uint32_t wdt_flashboot_mod_en:1;
        /** wdt_sys_reset_length:R/W；比特位置：[17:15]；默认值：1；系统复位信号长度选择。0：100纳秒，1：200纳秒，2：300纳秒，3：400纳秒，4：500纳秒，5：800纳秒，6：1.6微秒，7：3.2微秒。
         */
        uint32_t wdt_sys_reset_length:3;
        /** wdt_cpu_reset_length:R/W；比特位置：[20:18]；默认值：1；CPU复位信号长度选择。0：100纳秒，1：200纳秒，2：300纳秒，3：400纳秒，4：500纳秒，5：800纳秒，6：1.6微秒，7：3.2微秒。
         */
        uint32_t wdt_cpu_reset_length:3;
        /** wdt_use_xtal:R/W；位位置：[21]；默认值：0；选择WDT时钟：0-apb_clk；1-xtal_clk。
         */
        uint32_t wdt_use_xtal:1;
        /** wdt_conf_update_en:WT；位位置：[22]；默认值：0；更新WDT配置寄存器
         */
        uint32_t wdt_conf_update_en:1;
        /** wdt_stg3：右侧；位位置：[24:23]；默认值：0；第3阶段配置。0：关闭，1：中断，2：重置CPU，3：重置系统。
         */
        uint32_t wdt_stg3:2;
        /** wdt_stg2:R/W；比特位置：[26:25]；默认值：0；第2阶段配置。0：关闭，1：中断，2：重置CPU，3：重置系统。
         */
        uint32_t wdt_stg2:2;
        /** wdt_stg1：右侧；位位置：[28:27]；默认值：0；阶段1配置。0：关闭，1：中断，2：重置CPU，3：重置系统。
         */
        uint32_t wdt_stg1:2;
        /** wdt_stg0:R/W；位位置：[30:29]；默认值：0；阶段0配置。0：关闭，1：中断，2：重置CPU，3：重置系统。
         */
        uint32_t wdt_stg0:2;
        /** wdt_en:R/W；位位置：[31]；默认值：0；设置后，MWDT启用。
         */
        uint32_t wdt_en:1;
    };
    uint32_t val;
} timg_wdtconfig0_reg_t;

/** wdtconfig1寄存器类型看门狗定时器预分频器寄存器
 */
typedef union {
    struct {
        /** wdt_divcnt_rst:WT；位位置：[0]；默认值：0；设置后，WDT的时钟分频器计数器将复位。
         */
        uint32_t wdt_divcnt_rst:1;
        uint32_t reserved_1:15;
        /** wdt_clk_prescale：R/W；比特位置：[31:16]；默认值：1；MWDT时钟预分频器值。MWDT时钟周期=12.5 ns TIMG_WDT_CLK_PRESCALE。
         */
        uint32_t wdt_clk_prescale:16;
    };
    uint32_t val;
} timg_wdtconfig1_reg_t;

/** wdtconfig2寄存器类型看门狗计时器阶段0超时值
 */
typedef union {
    struct {
        /** wdt_stg0_hold:R/W；位位置：[31:0]；默认值：26000000；阶段0超时值，以MWDT时钟周期为单位。
         */
        uint32_t wdt_stg0_hold:32;
    };
    uint32_t val;
} timg_wdtconfig2_reg_t;

/** wdtconfig3寄存器类型看门狗计时器第1阶段超时值
 */
typedef union {
    struct {
        /** wdt_stg1_hold:R/W；位位置：[31:0]；默认值：134217727；阶段1超时值，以MWDT时钟周期为单位。
         */
        uint32_t wdt_stg1_hold:32;
    };
    uint32_t val;
} timg_wdtconfig3_reg_t;

/** wdtconfig4寄存器类型看门狗定时器第2阶段超时值
 */
typedef union {
    struct {
        /** wdt_stg2_hold:R/W；位位置：[31:0]；默认值：1048575；第2阶段超时值，以MWDT时钟周期为单位。
         */
        uint32_t wdt_stg2_hold:32;
    };
    uint32_t val;
} timg_wdtconfig4_reg_t;

/** wdtconfig5寄存器类型看门狗计时器第3阶段超时值
 */
typedef union {
    struct {
        /** wdt_stg3_hold:R/W；位位置：[31:0]；默认值：1048575；阶段3超时值，以MWDT时钟周期为单位。
         */
        uint32_t wdt_stg3_hold:32;
    };
    uint32_t val;
} timg_wdtconfig5_reg_t;

/** wdtfeed寄存器类型写入以馈送看门狗计时器
 */
typedef union {
    struct {
        /** wdt_feed:WT；位位置：[31:0]；默认值：0；写入任何值以馈送MWDT。（WO）
         */
        uint32_t wdt_feed:32;
    };
    uint32_t val;
} timg_wdtfeed_reg_t;

/** wdtwprotect寄存器类型看门狗写保护寄存器
 */
typedef union {
    struct {
        /** wdt_wkey:R/W；位位置：[31:0]；默认值：1356348065；如果寄存器包含与其重置值不同的值，则启用写保护。
         */
        uint32_t wdt_wkey:32;
    };
    uint32_t val;
} timg_wdtwprotect_reg_t;


/**组：RTC CALI控制和配置寄存器*/
/** rtccalicfg寄存器类型RTC校准配置寄存器
 */
typedef union {
    struct {
        uint32_t reserved_0:12;
        /** rtc_cali_start_cycling:R/W；位位置：[12]；默认值：1；保留
         */
        uint32_t rtc_cali_start_cycling:1;
        /** rtc_cali_clk_sel:R/W；比特位置：[14:13]；默认值：1；0:rtc慢时钟。1： clk_8m，2:xtal_32k。
         */
        uint32_t rtc_cali_clk_sel:2;
        /** rtc_cali_rdy:RO；位位置：[15]；默认值：0；保留
         */
        uint32_t rtc_cali_rdy:1;
        /** rtc_cali_max:R/W；比特位置：[30:16]；默认值：1；保留
         */
        uint32_t rtc_cali_max:15;
        /** rtc_cali_start:R/W；位位置：[31]；默认值：0；保留
         */
        uint32_t rtc_cali_start:1;
    };
    uint32_t val;
} timg_rtccalicfg_reg_t;

/** rtccalicfg1寄存器类型RTC校准配置1寄存器
 */
typedef union {
    struct {
        /** rtc_cali_cycling_data_vld:RO；位位置：[0]；默认值：0；保留
         */
        uint32_t rtc_cali_cycling_data_vld:1;
        uint32_t reserved_1:6;
        /** rtc_cali_value：RO；比特位置：[31:7]；默认值：0；保留
         */
        uint32_t rtc_cali_value:25;
    };
    uint32_t val;
} timg_rtccalicfg1_reg_t;

/** rtccalicfg2寄存器类型定时器组校准寄存器
 */
typedef union {
    struct {
        /** rtc_cali_timeout:RO；位位置：[0]；默认值：0；RTC校准超时指示灯
         */
        uint32_t rtc_cali_timeout:1;
        uint32_t reserved_1:2;
        /** rtc_cali_timeout_rst_cnt:R/W；比特位置：[6:3]；默认值：3；释放校准超时重置的周期
         */
        uint32_t rtc_cali_timeout_rst_cnt:4;
        /** rtc_cali_timeout_thres:R/W；比特位置：[31:7]；默认值：33554431；RTC校准计时器的阈值。如果校准计时器的值超过此阈值，将触发超时。
         */
        uint32_t rtc_cali_timeout_thres:25;
    };
    uint32_t val;
} timg_rtccalicfg2_reg_t;


/**组：中断寄存器*/
/** int_ena_timers寄存器类型中断启用位
 */
typedef union {
    struct {
        /** t0_int_ena:R/W；位位置：[0]；默认值：0；TIMG_T$x_INT中断的中断启用位。
         */
        uint32_t t0_int_ena:1;
        /** wdt_int_ena:R/W；位位置：[1]；默认值：0；TIMG_WDT_INT中断的中断启用位。
         */
        uint32_t wdt_int_ena:1;
        uint32_t reserved_2:30;
    };
    uint32_t val;
} timg_int_ena_timers_reg_t;

/** int_raw_timers寄存器原始中断状态的类型
 */
typedef union {
    struct {
        /** t0_int_raw:R/SS/WTC；位位置：[0]；默认值：0；TIMG_T$x_INT中断的原始中断状态位。
         */
        uint32_t t0_int_raw:1;
        /** wdt_int_raw:R/SS/WTC；位位置：[1]；默认值：0；TIMG_WDT_INT中断的原始中断状态位。
         */
        uint32_t wdt_int_raw:1;
        uint32_t reserved_2:30;
    };
    uint32_t val;
} timg_int_raw_timers_reg_t;

/** int_st_timers寄存器类型屏蔽中断状态
 */
typedef union {
    struct {
        /** t0_int_st:RO；位位置：[0]；默认值：0；TIMG_T$x_INT中断的屏蔽中断状态位。
         */
        uint32_t t0_int_st:1;
        /** wdt_int_st:RO；位位置：[1]；默认值：0；TIMG_WDT_INT中断的屏蔽中断状态位。
         */
        uint32_t wdt_int_st:1;
        uint32_t reserved_2:30;
    };
    uint32_t val;
} timg_int_st_timers_reg_t;

/** int_clr_timers寄存器类型中断清除位
 */
typedef union {
    struct {
        /** t0_int_clr:WT；位位置：[0]；默认值：0；设置该位以清除TIMG_T$x_INT中断。
         */
        uint32_t t0_int_clr:1;
        /** wdt_int_clr:WT；位位置：[1]；默认值：0；设置该位以清除TIMG_WDT_INT中断。
         */
        uint32_t wdt_int_clr:1;
        uint32_t reserved_2:30;
    };
    uint32_t val;
} timg_int_clr_timers_reg_t;


/**组：版本寄存器*/
/** ntimers_date寄存器类型计时器版本控制寄存器
 */
typedef union {
    struct {
        /** ntimgs_date:R/W；位位置：[27:0]；默认值：33579409；定时器版本控制寄存器
         */
        uint32_t ntimgs_date:28;
        uint32_t reserved_28:4;
    };
    uint32_t val;
} timg_ntimers_date_reg_t;


/**组：时钟配置寄存器*/
/** regclk寄存器类型定时器组时钟门寄存器
 */
typedef union {
    struct {
        uint32_t reserved_0:29;
        /** wdt_clk_is_active:R/W；位位置：[29]；默认值：1；启用WDT时钟
         */
        uint32_t wdt_clk_is_active:1;
        /** timer_clk_is_active:R/W；位位置：[30]；默认值：1；启用计时器$x的时钟
         */
        uint32_t timer_clk_is_active:1;
        /** clk_en:R/W；位位置：[31]；默认值：0；寄存器时钟门信号。1： 寄存器可以由软件读取和写入。0：软件无法读取或写入寄存器。
         */
        uint32_t clk_en:1;
    };
    uint32_t val;
} timg_regclk_reg_t;

typedef struct {
    volatile timg_txconfig_reg_t config;
    volatile timg_txlo_reg_t lo;
    volatile timg_txhi_reg_t hi;
    volatile timg_txupdate_reg_t update;
    volatile timg_txalarmlo_reg_t alarmlo;
    volatile timg_txalarmhi_reg_t alarmhi;
    volatile timg_txloadlo_reg_t loadlo;
    volatile timg_txloadhi_reg_t loadhi;
    volatile timg_txload_reg_t load;
} timg_hwtimer_reg_t;

typedef struct {
    volatile timg_hwtimer_reg_t hw_timer[1];
    uint32_t reserved_024[9];
    volatile timg_wdtconfig0_reg_t wdtconfig0;
    volatile timg_wdtconfig1_reg_t wdtconfig1;
    volatile timg_wdtconfig2_reg_t wdtconfig2;
    volatile timg_wdtconfig3_reg_t wdtconfig3;
    volatile timg_wdtconfig4_reg_t wdtconfig4;
    volatile timg_wdtconfig5_reg_t wdtconfig5;
    volatile timg_wdtfeed_reg_t wdtfeed;
    volatile timg_wdtwprotect_reg_t wdtwprotect;
    volatile timg_rtccalicfg_reg_t rtccalicfg;
    volatile timg_rtccalicfg1_reg_t rtccalicfg1;
    volatile timg_int_ena_timers_reg_t int_ena_timers;
    volatile timg_int_raw_timers_reg_t int_raw_timers;
    volatile timg_int_st_timers_reg_t int_st_timers;
    volatile timg_int_clr_timers_reg_t int_clr_timers;
    volatile timg_rtccalicfg2_reg_t rtccalicfg2;
    uint32_t reserved_084[29];
    volatile timg_ntimers_date_reg_t ntimers_date;
    volatile timg_regclk_reg_t regclk;
} timg_dev_t;

extern timg_dev_t TIMERG0;
extern timg_dev_t TIMERG1;

#ifndef __cplusplus
_Static_assert(sizeof(timg_dev_t) == 0x100, "Invalid size of timg_dev_t structure");
#endif

#ifdef __cplusplus
}
#endif

