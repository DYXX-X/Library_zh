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

/**组：配置和控制寄存器*/
/** txconfig寄存器类型Timer x配置寄存器
 */
typedef union {
    struct {
        uint32_t reserved_0:9;
        /** tx_use_xtal:R/W；位位置：[9]；默认值：0；1： 使用XTAL_CLK作为定时器组的源时钟。0：使用APB_CLK作为定时器组的源时钟。
         */
        uint32_t tx_use_xtal:1;
        /** tx_alarm_en:R/W；位位置：[10]；默认值：0；设置后，警报启用。一旦
         *
         *  发生报警。
         */
        uint32_t tx_alarm_en:1;
        /** tx_level_int_en:R/W；位位置：[11]；默认值：0；设置后，警报将生成电平类型的中断。
         */
        uint32_t tx_level_int_en:1;
        /** tx_edge_int_en:R/W；位位置：[12]；默认值：0；设置后，警报将生成边缘型中断。
         */
        uint32_t tx_edge_int_en:1;
        /** tx_dider:R/W；比特位置：[28:13]；默认值：1；计时器x时钟（Tx_clk）预分频器值。
         */
        uint32_t tx_divider:16;
        /** tx_autoreload:R/W；位位置：[29]；默认值：1；设置后，启用计时器x报警时自动重新加载。
         */
        uint32_t tx_autoreload:1;
        /** tx_increse:R/W；位位置：[30]；默认值：1；设置后，计时器x时基计数器将在每个时钟周期递增。什么时候
         *
         *  清除，计时器x时基计数器将递减。
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
        /** tx_lo:RO；位位置：[31:0]；默认值：0；写入TIMG_TxUPDATE_REG后，时基计数器的低32位
         *
         *  可以在这里读取计时器x的值。
         */
        uint32_t tx_lo:32;
    };
    uint32_t val;
} timg_txlo_reg_t;

/** txhi寄存器类型定时器x当前值，高32位
 */
typedef union {
    struct {
        /** tx_hi:RO；位位置：[31:0]；默认值：0；写入TIMG_TxUPDATE_REG后，时基计数器的高32位
         *
         *  可以在这里读取计时器x的值。
         */
        uint32_t tx_hi:32;
    };
    uint32_t val;
} timg_txhi_reg_t;

/** txupdate寄存器类型写入以将当前计时器值复制到TIMGn_Tx_（LO/HI）_REG
 */
typedef union {
    struct {
        uint32_t reserved_0:31;
        /** tx_update:R/W；位位置：[31]；默认值：0；向TIMG_TxUPDATE_REG写入0或1后，计数器值被锁存。
         */
        uint32_t tx_update:1;
    };
    uint32_t val;
} timg_txupdate_reg_t;

/** txalarmlo寄存器类型定时器x报警值，低32位
 */
typedef union {
    struct {
        /** tx_alarm_lo:R/W；位位置：[31:0]；默认值：0；计时器x报警触发时基计数器值，低32位。
         */
        uint32_t tx_alarm_lo:32;
    };
    uint32_t val;
} timg_txalarmlo_reg_t;

/** txalarmhi寄存器类型计时器x报警值，高位
 */
typedef union {
    struct {
        /** tx_alarm_hi:R/W；位位置：[31:0]；默认值：0；
         *
         * 计时器x报警触发时基计数器值，高32位。
         */
        uint32_t tx_alarm_hi:32;
    };
    uint32_t val;
} timg_txalarmhi_reg_t;

/** txloadlo寄存器类型计时器x重新加载值，低32位
 */
typedef union {
    struct {
        /** tx_load_lo:R/W；位位置：[31:0]；默认值：0；
         *
         * 重新加载将加载到计时器x时基上的值的低32位
         *
         *  柜台
         */
        uint32_t tx_load_lo:32;
    };
    uint32_t val;
} timg_txloadlo_reg_t;

/** txloadhi寄存器类型Timer x reload值，高32位
 */
typedef union {
    struct {
        /** tx_load_hi:R/W；位位置：[31:0]；默认值：0；
         *
         * 重载将加载到计时器x时基上的值的高32位
         *
         *  柜台
         */
        uint32_t tx_load_hi:32;
    };
    uint32_t val;
} timg_txloadhi_reg_t;

/** txload寄存器类型从TIMG_T0_（LOADLOLOADHI）_REG写入重新加载计时器
 */
typedef union {
    struct {
        /** tx_load:WO；位位置：[31:0]；默认值：0；
         *
         * 写入任何值以触发计时器x时基计数器重新加载。
         */
        uint32_t tx_load:32;
    };
    uint32_t val;
} timg_txload_reg_t;


/**组：WDT的配置和控制寄存器*/
/** wdtconfig0寄存器类型看门狗定时器配置寄存器
 */
typedef union {
    struct {
        uint32_t reserved_0:12;
        /** wdt_appcpu_reset_en:R/W；位位置：[12]；默认值：0；保留
         */
        uint32_t wdt_appcpu_reset_en:1;
        /** wdt_procpu_reset_en:R/W；位位置：[13]；默认值：0；WDT重置CPU启用。
         */
        uint32_t wdt_procpu_reset_en:1;
        /** wdt_flashboot_mod_en:R/W；位位置：[14]；默认值：1；设置后，将启用闪存启动保护。
         */
        uint32_t wdt_flashboot_mod_en:1;
        /** wdt_sys_reset_length:R/W；比特位置：[17:15]；默认值：1；系统复位信号长度选择。0：100纳秒、1：200纳秒，
         *
         *  2： 300纳秒，3:400纳秒，4:500纳秒，5:800纳秒，6:1.6微秒，7:3.2微秒。
         */
        uint32_t wdt_sys_reset_length:3;
        /** wdt_cpu_reset_length:R/W；比特位置：[20:18]；默认值：1；CPU复位信号长度选择。0：100纳秒、1：200纳秒，
         *
         *  2： 300纳秒，3:400纳秒，4:500纳秒，5:800纳秒，6:1.6微秒，7:3.2微秒。
         */
        uint32_t wdt_cpu_reset_length:3;
        /** wdt_level_int_en:R/W；位位置：[21]；默认值：0；设置后，在阶段超时时将发生级别类型中断
         *
         *  被配置为生成中断。
         */
        uint32_t wdt_level_int_en:1;
        /** wdt_edge_int_en:R/W；位位置：[22]；默认值：0；设置后，边缘类型中断将在阶段超时时发生
         *
         *  被配置为生成中断。
         */
        uint32_t wdt_edge_int_en:1;
        /** wdt_stg3：右侧；位位置：[24:23]；默认值：0；第3阶段配置。0：关闭，1：中断，2：重置CPU，3：重置系统。
         *
         */
        uint32_t wdt_stg3:2;
        /** wdt_stg2:R/W；比特位置：[26:25]；默认值：0；第2阶段配置。0：关闭，1：中断，2：重置CPU，3：重置系统。
         *
         */
        uint32_t wdt_stg2:2;
        /** wdt_stg1：右侧；位位置：[28:27]；默认值：0；阶段1配置。0：关闭，1：中断，2：重置CPU，3：重置系统。
         *
         */
        uint32_t wdt_stg1:2;
        /** wdt_stg0:R/W；位位置：[30:29]；默认值：0；阶段0配置。0：关闭，1：中断，2：重置CPU，3：重置系统。
         *
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
        uint32_t reserved_0:16;
        /** wdt_clk_prescaler:R/W；比特位置：[31:16]；默认值：1；MWDT时钟预分频器值。MWDT时钟周期=12.5 ns
         *
         *  TIMG_WDT_CLK_PRESCALE.
         */
        uint32_t wdt_clk_prescaler:16;
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
        /** wdt_feed：工单；位位置：[31:0]；默认值：0；写入任何值以馈送MWDT。（WO）
         */
        uint32_t wdt_feed:32;
    };
    uint32_t val;
} timg_wdtfeed_reg_t;

/** wdtwprotect寄存器类型看门狗写保护寄存器
 */
typedef union {
    struct {
        /** wdt_wkey:R/W；位位置：[31:0]；默认值：1356348065；如果寄存器包含与其重置值不同的值，请写入
         *
         *  启用保护。
         */
        uint32_t wdt_wkey:32;
    };
    uint32_t val;
} timg_wdtwprotect_reg_t;


/**组：RTC CALI的配置和控制寄存器*/
/** rtccalicfg寄存器类型RTC校准配置寄存器
 */
typedef union {
    struct {
        uint32_t reserved_0:12;
        /** rtc_cali_start_cycling:R/W；位位置：[12]；默认值：1；保留
         */
        uint32_t rtc_cali_start_cycling:1;
        /** rtc_cali_clk_sel:R/W；比特位置：[14:13]；默认值：1；0:rtslowclock（实时时钟）。1： clk_80m。2： xtal_32k中。
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


/**组：LACT的配置和控制寄存器*/
/** lactconfig寄存器类型LACT配置寄存器
 */
typedef union {
    struct {
        uint32_t reserved_0:6;
        /** 乳糖酶：R/W；位位置：[6]；默认值：0；保留
         */
        uint32_t lact_use_reftick:1;
        /** 仅限乳制品：R/W；位位置：[7]；默认值：0；保留
         */
        uint32_t lact_rtc_only:1;
        /** lact_cpst_en:R/W；位位置：[8]；默认值：1；保留
         */
        uint32_t lact_cpst_en:1;
        /** lact_lac_en:R/W；位位置：[9]；默认值：1；保留
         */
        uint32_t lact_lac_en:1;
        /** 乳_警报_ en：R/W；位位置：[10]；默认值：0；保留
         */
        uint32_t lact_alarm_en:1;
        /** 乳酸盐水平int_en:R/W；位位置：[11]；默认值：0；保留
         */
        uint32_t lact_level_int_en:1;
        /** 乳蛋白_蛋白_蛋白：R/W；位位置：[12]；默认值：0；保留
         */
        uint32_t lact_edge_int_en:1;
        /** 乳酸盐：R/W；比特位置：[28:13]；默认值：1；保留
         */
        uint32_t lact_divider:16;
        /** 乳酸盐：R/W；位位置：[29]；默认值：1；保留
         */
        uint32_t lact_autoreload:1;
        /** 乳酸盐增加：R/W；位位置：[30]；默认值：1；保留
         */
        uint32_t lact_increase:1;
        /** 乳酸盐：R/W；位位置：[31]；默认值：0；保留
         */
        uint32_t lact_en:1;
    };
    uint32_t val;
} timg_lactconfig_reg_t;

/** lactrtc寄存器类型LACT RTC寄存器
 */
typedef union {
    struct {
        uint32_t reserved_0:6;
        /** lact_rtc_stp_len:R/W；位位置：[31:6]；默认值：0；保留
         */
        uint32_t lact_rtc_step_len:26;
    };
    uint32_t val;
} timg_lactrtc_reg_t;

/** 乳寄存器类型LACT低寄存器
 */
typedef union {
    struct {
        /** lact_lo:RO；位位置：[31:0]；默认值：0；保留
         */
        uint32_t lact_lo:32;
    };
    uint32_t val;
} timg_lactlo_reg_t;

/** 乳糖酶寄存器类型LACT高位寄存器
 */
typedef union {
    struct {
        /** lact_hi:RO；位位置：[31:0]；默认值：0；保留
         */
        uint32_t lact_hi:32;
    };
    uint32_t val;
} timg_lacthi_reg_t;

/** 乳更新寄存器类型LACT更新寄存器
 */
typedef union {
    struct {
        /** 乳酸盐更新：WO；位位置：[31:0]；默认值：0；保留
         */
        uint32_t lact_update:32;
    };
    uint32_t val;
} timg_lactupdate_reg_t;

/** 乳警报低寄存器类型LACT警报低寄存器
 */
typedef union {
    struct {
        /** 乳酸盐_警报_ lo：R/W；位位置：[31:0]；默认值：0；保留
         */
        uint32_t lact_alarm_lo:32;
    };
    uint32_t val;
} timg_lactalarmlo_reg_t;

/** lactalarmhi寄存器类型LACT报警高位寄存器
 */
typedef union {
    struct {
        /** 乳_警报_高：R/W；位位置：[31:0]；默认值：0；保留
         */
        uint32_t lact_alarm_hi:32;
    };
    uint32_t val;
} timg_lactalarmhi_reg_t;

/** lactloadlo寄存器类型LACT负载低寄存器
 */
typedef union {
    struct {
        /** 乳酸盐负荷：R/W；位位置：[31:0]；默认值：0；保留
         */
        uint32_t lact_load_lo:32;
    };
    uint32_t val;
} timg_lactloadlo_reg_t;

/** lactloadhi寄存器类型定时器LACT负载高寄存器
 */
typedef union {
    struct {
        /** 乳酸盐负荷：R/W；位位置：[31:0]；默认值：0；保留
         */
        uint32_t lact_load_hi:32;
    };
    uint32_t val;
} timg_lactloadhi_reg_t;

/** 乳负荷寄存器类型定时器LACT负荷寄存器
 */
typedef union {
    struct {
        /** 乳酸盐负荷：WO；位位置：[31:0]；默认值：0；保留
         */
        uint32_t lact_load:32;
    };
    uint32_t val;
} timg_lactload_reg_t;


/**组：中断寄存器*/
/** int_ena_timers寄存器类型中断启用位
 */
typedef union {
    struct {
        /** tx_int_ena:R/W；位位置：[0]；默认值：0；TIMG_T0_INT中断的中断启用位。
         */
        uint32_t tx_int_ena:1;
        /** t1_int_ena:R/W；位位置：[1]；默认值：0；TIMG_T1_INT中断的中断启用位。
         */
        uint32_t t1_int_ena:1;
        /** wdt_int_ena:R/W；位位置：[2]；默认值：0；TIMG_WDT_INT中断的中断启用位。
         */
        uint32_t wdt_int_ena:1;
        /** 乳糖酶_ int_ena:R/W；位位置：[3]；默认值：0；TIMG_LACT_INT中断的中断启用位。
         */
        uint32_t lact_int_ena:1;
        uint32_t reserved_4:28;
    };
    uint32_t val;
} timg_int_ena_timers_reg_t;

/** int_raw_timers寄存器原始中断状态的类型
 */
typedef union {
    struct {
        /** t0_int_raw:RO；位位置：[0]；默认值：0；TIMG_T0_INT中断的原始中断状态位。
         */
        uint32_t t0_int_raw:1;
        /** t1_int_raw:RO；位位置：[1]；默认值：0；TIMG_T1_INT中断的原始中断状态位。
         */
        uint32_t t1_int_raw:1;
        /** wdt_int_raw:RO；位位置：[2]；默认值：0；TIMG_WDT_INT中断的原始中断状态位。
         */
        uint32_t wdt_int_raw:1;
        /** lact_int_raw:RO；位位置：[3]；默认值：0；TIMG_LACT_INT中断的原始中断状态位。
         */
        uint32_t lact_int_raw:1;
        uint32_t reserved_4:28;
    };
    uint32_t val;
} timg_int_raw_timers_reg_t;

/** int_st_timers寄存器类型屏蔽中断状态
 */
typedef union {
    struct {
        /** t0_int_st:RO；位位置：[0]；默认值：0；TIMG_T0_INT中断的屏蔽中断状态位。
         */
        uint32_t t0_int_st:1;
        /** t1_int_st:RO；位位置：[1]；默认值：0；TIMG_T1_INT中断的屏蔽中断状态位。
         */
        uint32_t t1_int_st:1;
        /** wdt_int_st:RO；位位置：[2]；默认值：0；TIMG_WDT_INT中断的屏蔽中断状态位。
         */
        uint32_t wdt_int_st:1;
        /** 乳酸盐指数：RO；位位置：[3]；默认值：0；TIMG_LACT_INT中断的屏蔽中断状态位。
         */
        uint32_t lact_int_st:1;
        uint32_t reserved_4:28;
    };
    uint32_t val;
} timg_int_st_timers_reg_t;

/** int_clr_timers寄存器类型中断清除位
 */
typedef union {
    struct {
        /** t0_int_clr:工单；位位置：[0]；默认值：0；设置该位以清除TIMG_T0_INT中断。
         */
        uint32_t t0_int_clr:1;
        /** t1_int_clr：工单；位位置：[1]；默认值：0；设置该位以清除TIMG_T1_INT中断。
         */
        uint32_t t1_int_clr:1;
        /** wdt_int_clr:WO；位位置：[2]；默认值：0；设置该位以清除TIMG_WDT_INT中断。
         */
        uint32_t wdt_int_clr:1;
        /** lact_int_clr:WO；位位置：[3]；默认值：0；设置该位以清除TIMG_LACT_INT中断。
         */
        uint32_t lact_int_clr:1;
        uint32_t reserved_4:28;
    };
    uint32_t val;
} timg_int_clr_timers_reg_t;


/**组：版本寄存器*/
/** 计时器类型_日期寄存器版本控制寄存器
 */
typedef union {
    struct {
        /** timers_date:R/W；位位置：[27:0]；默认值：26243681；版本控制寄存器。
         */
        uint32_t timers_date:28;
        uint32_t reserved_28:4;
    };
    uint32_t val;
} timg_timers_date_reg_t;


/**组：配置寄存器*/
/** regclk寄存器类型定时器组时钟门寄存器
 */
typedef union {
    struct {
        uint32_t reserved_0:31;
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
    volatile timg_hwtimer_reg_t hw_timer[2];
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
    volatile timg_lactconfig_reg_t lactconfig;
    volatile timg_lactrtc_reg_t lactrtc;
    volatile timg_lactlo_reg_t lactlo;
    volatile timg_lacthi_reg_t lacthi;
    volatile timg_lactupdate_reg_t lactupdate;
    volatile timg_lactalarmlo_reg_t lactalarmlo;
    volatile timg_lactalarmhi_reg_t lactalarmhi;
    volatile timg_lactloadlo_reg_t lactloadlo;
    volatile timg_lactloadhi_reg_t lactloadhi;
    volatile timg_lactload_reg_t lactload;
    volatile timg_int_ena_timers_reg_t int_ena_timers;
    volatile timg_int_raw_timers_reg_t int_raw_timers;
    volatile timg_int_st_timers_reg_t int_st_timers;
    volatile timg_int_clr_timers_reg_t int_clr_timers;
    volatile timg_rtccalicfg2_reg_t rtccalicfg2;
    uint32_t reserved_0ac[19];
    volatile timg_timers_date_reg_t timers_date;
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

