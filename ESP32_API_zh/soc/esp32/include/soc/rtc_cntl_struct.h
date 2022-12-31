// 版权所有2015-2016 Espressif Systems（上海）私人有限公司
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
#ifndef _SOC_RTC_CNTL_STRUCT_H_
#define _SOC_RTC_CNTL_STRUCT_H_

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef volatile struct rtc_cntl_dev_s {
    union {
        struct {
            uint32_t sw_stall_appcpu_c0:  2;             /*｛reg_sw_stall_appcpu_c1[5:0]reg_sw_stall_appcp u_c1[1:0]｝==0x86将停止APP CPU*/
            uint32_t sw_stall_procpu_c0:  2;             /*｛reg_sw_stall_procpu_c1[5:0]reg_sw_stall_procpu_c0[1:0]｝==0x86将停止PRO CPU*/
            uint32_t sw_appcpu_rst:       1;             /*APP CPU SW复位*/
            uint32_t sw_procpu_rst:       1;             /*PRO CPU SW复位*/
            uint32_t bb_i2c_force_pd:     1;             /*BB_I2C强制断电*/
            uint32_t bb_i2c_force_pu:     1;             /*BB_I2C强制加电*/
            uint32_t bbpll_i2c_force_pd:  1;             /*BB_PLL _I2C强制断电*/
            uint32_t bbpll_i2c_force_pu:  1;             /*BB_PLL_I2C强制加电*/
            uint32_t bbpll_force_pd:      1;             /*BB_PLL强制断电*/
            uint32_t bbpll_force_pu:      1;             /*BB_PLL强制加电*/
            uint32_t xtl_force_pd:        1;             /*晶体力断电*/
            uint32_t xtl_force_pu:        1;             /*晶体力加电*/
            uint32_t bias_sleep_folw_8m:  1;             /*BIAS_LEEP遵循CK8M*/
            uint32_t bias_force_sleep:    1;             /*BIAS_LEEP强制休眠*/
            uint32_t bias_force_nosleep:  1;             /*BIAS_LEEP强制不休眠*/
            uint32_t bias_i2c_folw_8m:    1;             /*BIAS_I2C遵循CK8M*/
            uint32_t bias_i2c_force_pd:   1;             /*BIAS_I2C强制断电*/
            uint32_t bias_i2c_force_pu:   1;             /*BIAS_I2C强制加电*/
            uint32_t bias_core_folw_8m:   1;             /*BIAS_CORE遵循CK8M*/
            uint32_t bias_core_force_pd:  1;             /*BIAS_CORE强制断电*/
            uint32_t bias_core_force_pu:  1;             /*BIAS_CORE强制加电*/
            uint32_t xtl_force_iso:       1;
            uint32_t pll_force_iso:       1;
            uint32_t analog_force_iso:    1;
            uint32_t xtl_force_noiso:     1;
            uint32_t pll_force_noiso:     1;
            uint32_t analog_force_noiso:  1;
            uint32_t dg_wrap_force_rst:   1;             /*深度睡眠中的数字包裹力重置*/
            uint32_t dg_wrap_force_norst: 1;             /*深度睡眠中的数字核心力无复位*/
            uint32_t sw_sys_rst:          1;             /*SW系统复位*/
        };
        uint32_t val;
    } options0;
    uint32_t slp_timer0;                             /*RTC睡眠定时器低32位*/
    union {
        struct {
            uint32_t slp_val_hi:             16;         /*RTC休眠定时器高16位*/
            uint32_t main_timer_alarm_en: 1;         /*定时器报警启用位*/
            uint32_t reserved17:             15;
        };
        uint32_t val;
    } slp_timer1;
    union {
        struct {
            uint32_t reserved0:      30;
            uint32_t valid:  1;                 /*指示寄存器已更新*/
            uint32_t update: 1;                 /*设置1：用RTC计时器更新寄存器*/
        };
        uint32_t val;
    } time_update;
    uint32_t time0;                                  /*RTC定时器低32位*/
    union {
        struct {
            uint32_t time_hi:16;                     /*RTC计时器高16位*/
            uint32_t reserved16: 16;
        };
        uint32_t val;
    } time1;
    union {
        struct {
            uint32_t reserved0:             20;
            uint32_t touch_wakeup_force_en:  1;          /*触摸控制器强制唤醒*/
            uint32_t ulp_cp_wakeup_force_en: 1;          /*ULP协处理器强制唤醒*/
            uint32_t apb2rtc_bridge_sel:     1;          /*1： APB到RTC使用桥0：APB到RTC使用同步*/
            uint32_t touch_slp_timer_en:     1;          /*触摸计时器启用位*/
            uint32_t ulp_cp_slp_timer_en:    1;          /*ULP协处理器定时器启用位*/
            uint32_t reserved25:             3;
            uint32_t sdio_active_ind:        1;          /*SDIO激活指示*/
            uint32_t slp_wakeup:             1;          /*睡眠唤醒位*/
            uint32_t slp_reject:             1;          /*休眠拒绝位*/
            uint32_t sleep_en:               1;          /*休眠启用位*/
        };
        uint32_t val;
    } state0;
    union {
        struct {
            uint32_t cpu_stall_en:   1;                  /*CPU暂停启用位*/
            uint32_t cpu_stall_wait: 5;                  /*fast_clk_rtc中的CPU暂停等待周期*/
            uint32_t ck8m_wait:      8;                  /*CK8M等待周期（slow_clk_rtc）*/
            uint32_t xtl_buf_wait:  10;                  /*slow_clk_rtc中的XTAL等待周期*/
            uint32_t pll_buf_wait:   8;                  /*以slow_clk_rtc为单位的PLL等待周期*/
        };
        uint32_t val;
    } timer1;
    union {
        struct {
            uint32_t reserved0:             15;
            uint32_t ulpcp_touch_start_wait: 9;          /*ULP协处理器/触摸控制器开始工作之前，在slow_clk_rtc中等待周期*/
            uint32_t min_time_ck8m_off:      8;          /*处于断电状态的CK8M的slow_clk_rtc中的最小周期*/
        };
        uint32_t val;
    } timer2;
    union {
        struct {
            uint32_t wifi_wait_timer:       9;
            uint32_t wifi_powerup_timer:    7;
            uint32_t rom_ram_wait_timer:    9;
            uint32_t rom_ram_powerup_timer: 7;
        };
        uint32_t val;
    } timer3;
    union {
        struct {
            uint32_t rtc_wait_timer:        9;
            uint32_t rtc_powerup_timer:     7;
            uint32_t dg_wrap_wait_timer:    9;
            uint32_t dg_wrap_powerup_timer: 7;
        };
        uint32_t val;
    } timer4;
    union {
        struct {
            uint32_t ulp_cp_subtimer_prediv: 8;
            uint32_t min_slp_val:            8;          /*slowclkrtc中的最小睡眠周期*/
            uint32_t rtcmem_wait_timer:      9;
            uint32_t rtcmem_powerup_timer:   7;
        };
        uint32_t val;
    } timer5;
    union {
        struct {
            uint32_t reserved0:          23;
            uint32_t plla_force_pd:       1;             /*PLLA强制断电*/
            uint32_t plla_force_pu:       1;             /*PLLA强制加电*/
            uint32_t bbpll_cal_slp_start: 1;             /*在休眠期间启动BBPLL校准*/
            uint32_t pvtmon_pu:           1;             /*1： PVTMON通电，否则断电*/
            uint32_t txrf_i2c_pu:         1;             /*1： TXRF_I2C通电，否则断电*/
            uint32_t rfrx_pbus_pu:        1;             /*1： RFRX_PBUS通电，否则断电*/
            uint32_t reserved29:          1;
            uint32_t ckgen_i2c_pu:        1;             /*1： CKGEN_I2C通电，否则断电*/
            uint32_t pll_i2c_pu:          1;             /*1： PLL_I2C通电，否则断电*/
        };
        uint32_t val;
    } ana_conf;
    union {
        struct {
            uint32_t reset_cause_procpu:     6;          /*PRO CPU复位原因*/
            uint32_t reset_cause_appcpu:     6;          /*APP CPU复位原因*/
            uint32_t appcpu_stat_vector_sel: 1;          /*APP CPU状态向量sel*/
            uint32_t procpu_stat_vector_sel: 1;          /*PRO CPU状态向量sel*/
            uint32_t reserved14:            18;
        };
        uint32_t val;
    } reset_state;
    union {
        struct {
            uint32_t wakeup_cause:      11;              /*唤醒原因*/
            uint32_t rtc_wakeup_ena:    11;              /*唤醒启用位图*/
            uint32_t gpio_wakeup_filter: 1;              /*为gpio唤醒事件启用筛选器*/
            uint32_t reserved23:         9;
        };
        uint32_t val;
    } wakeup_state;
    union {
        struct {
            uint32_t slp_wakeup:     1;          /*启用睡眠唤醒中断*/
            uint32_t slp_reject:     1;          /*启用睡眠拒绝中断*/
            uint32_t sdio_idle:      1;          /*启用SDIO空闲中断*/
            uint32_t rtc_wdt:        1;          /*启用RTC WDT中断*/
            uint32_t rtc_time_valid: 1;          /*启用RTC时间有效中断*/
            uint32_t rtc_ulp_cp:     1;          /*启用ULP协处理器中断*/
            uint32_t rtc_touch:      1;          /*启用触摸中断*/
            uint32_t rtc_brown_out:  1;          /*启用断电中断*/
            uint32_t rtc_main_timer: 1;          /*启用RTC主计时器中断*/
            uint32_t reserved9:             23;
        };
        uint32_t val;
    } int_ena;
    union {
        struct {
            uint32_t slp_wakeup:     1;          /*睡眠唤醒中断raw*/
            uint32_t slp_reject:     1;          /*睡眠拒绝中断原始*/
            uint32_t sdio_idle:      1;          /*SDIO空闲中断原始*/
            uint32_t rtc_wdt:        1;          /*RTC WDT中断原始*/
            uint32_t rtc_time_valid: 1;          /*RTC时间有效中断原始*/
            uint32_t rtc_ulp_cp:     1;          /*ULP协处理器中断原始*/
            uint32_t rtc_touch:      1;          /*原始触摸中断*/
            uint32_t rtc_brown_out:  1;          /*棕色中断原始*/
            uint32_t rtc_main_timer: 1;          /*RTC主计时器中断原始*/
            uint32_t reserved9:             23;
        };
        uint32_t val;
    } int_raw;
    union {
        struct {
            uint32_t slp_wakeup:     1;           /*睡眠唤醒中断状态*/
            uint32_t slp_reject:     1;           /*睡眠拒绝中断状态*/
            uint32_t sdio_idle:      1;           /*SDIO空闲中断状态*/
            uint32_t rtc_wdt:        1;           /*RTC WDT中断状态*/
            uint32_t rtc_time_valid: 1;           /*RTC时间有效中断状态*/
            uint32_t rtc_sar:        1;           /*ULP协处理器中断状态*/
            uint32_t rtc_touch:      1;           /*触摸中断状态*/
            uint32_t rtc_brown_out:  1;           /*断电中断状态*/
            uint32_t rtc_main_timer: 1;           /*RTC主计时器中断状态*/
            uint32_t reserved9:            23;
        };
        uint32_t val;
    } int_st;
    union {
        struct {
            uint32_t slp_wakeup:     1;          /*清除睡眠唤醒中断状态*/
            uint32_t slp_reject:     1;          /*清除睡眠拒绝中断状态*/
            uint32_t sdio_idle:      1;          /*清除SDIO空闲中断状态*/
            uint32_t rtc_wdt:        1;          /*清除RTC WDT中断状态*/
            uint32_t rtc_time_valid: 1;          /*清除RTC时间有效中断状态*/
            uint32_t rtc_sar:        1;          /*清除ULP协处理器中断状态*/
            uint32_t rtc_touch:      1;          /*清除触摸中断状态*/
            uint32_t rtc_brown_out:  1;          /*清除棕色中断状态*/
            uint32_t rtc_main_timer: 1;          /*清除RTC主计时器中断状态*/
            uint32_t reserved9:             23;
        };
        uint32_t val;
    } int_clr;
    uint32_t rtc_store0;                                 /*32位通用保留寄存器*/
    uint32_t rtc_store1;                                 /*32位通用保留寄存器*/
    uint32_t rtc_store2;                                 /*32位通用保留寄存器*/
    uint32_t rtc_store3;                                 /*32位通用保留寄存器*/
    union {
        struct {
            uint32_t reserved0:     30;
            uint32_t ctr_lv: 1;                  /*0：关闭高电平XTAL电源1：关闭低电平XTAL*/
            uint32_t ctr_en: 1;                  /*通过外部焊盘启用控制XTAL*/
        };
        uint32_t val;
    } ext_xtl_conf;
    union {
        struct {
            uint32_t reserved0:     30;
            uint32_t wakeup0_lv: 1;                  /*0：低电平外部唤醒1：高电平外部唤醒*/
            uint32_t wakeup1_lv: 1;                  /*0：低电平外部唤醒1：高电平外部唤醒*/
        };
        uint32_t val;
    } ext_wakeup_conf;
    union {
        struct {
            uint32_t reserved0:          24;
            uint32_t gpio_reject_en:      1;             /*启用GPIO拒绝*/
            uint32_t sdio_reject_en:      1;             /*启用SDIO拒绝*/
            uint32_t light_slp_reject_en: 1;             /*启用轻睡眠拒绝*/
            uint32_t deep_slp_reject_en:  1;             /*启用深度睡眠拒绝*/
            uint32_t reject_cause:        4;             /*睡眠拒绝原因*/
        };
        uint32_t val;
    } slp_reject_conf;
    union {
        struct {
            uint32_t reserved0:        29;
            uint32_t cpusel_conf:   1;               /*CPU选择选项*/
            uint32_t cpuperiod_sel: 2;               /*CPU周期选择*/
        };
        uint32_t val;
    } cpu_period_conf;
    union {
        struct {
            uint32_t reserved0:    22;
            uint32_t sdio_act_dnum:10;
        };
        uint32_t val;
    } sdio_act_conf;
    union {
        struct {
            uint32_t reserved0:           4;
            uint32_t ck8m_div:            2;             /*CK8M_D256_OUT除法器。00:div128 01:div256 10:div512 11:div1024。*/
            uint32_t enb_ck8m:            1;             /*禁用CK8M和CK8M_D256_OUT*/
            uint32_t enb_ck8m_div:        1;             /*1： CK8M_D256_OUT实际上是CK8M 0：CK8M_D256 _OUT是CK8MM除以256*/
            uint32_t dig_xtal32k_en:      1;             /*为数字核心启用CK_XTAL_32K（与RTC核心无关系）*/
            uint32_t dig_clk8m_d256_en:   1;             /*为数字核心启用CK8M_D256_OUT（与RTC核心无关系）*/
            uint32_t dig_clk8m_en:        1;             /*为数字核心启用CK8M（与RTC核心无关系）*/
            uint32_t ck8m_dfreq_force:    1;
            uint32_t ck8m_div_sel:        3;             /*除法器=reg_ck8m_div_sel+1*/
            uint32_t xtal_force_nogating: 1;             /*睡眠期间XTAL强制无门控*/
            uint32_t ck8m_force_nogating: 1;             /*CK8M在睡眠期间强制无门控*/
            uint32_t ck8m_dfreq:          8;             /*CK8M_DFREQ*/
            uint32_t ck8m_force_pd:       1;             /*CK8M强制断电*/
            uint32_t ck8m_force_pu:       1;             /*CK8M强制加电*/
            uint32_t soc_clk_sel:         2;             /*SOC时钟选择。0:XTAL 1:PLL 2:CK8M 3:APLL*/
            uint32_t fast_clk_rtc_sel:    1;             /*fast_clk_rtc选择。0:XTAL分区4 1:CK8M*/
            uint32_t ana_clk_rtc_sel:     2;             /*slow_clk_rtc选择。0:SLOW_CK 1:CK_XTAL_32K 2:CK8M_D256_OUT*/
        };
        uint32_t val;
    } clk_conf;
    union {
        struct {
            uint32_t reserved0:   21;
            uint32_t sdio_pd_en:   1;                    /*关闭休眠状态下的SDIO_REG。仅当reg_sdio_force=0时激活*/
            uint32_t sdio_force:   1;                    /*1： 使用SW选项控制SDIO_REG 0：使用状态机*/
            uint32_t sdio_tieh:    1;                    /*SDIO_TIEH的SW选项。仅当reg_sdio_force=1时激活*/
            uint32_t reg1p8_ready: 1;                    /*REG1P8_READY的只读寄存器*/
            uint32_t drefl_sdio:   2;                    /*DREFL_SDIO的SW选项。仅当reg_sdio_force=1时激活*/
            uint32_t drefm_sdio:   2;                    /*DREFM_SDIO的SW选项。仅当reg_sdio_force=1时激活*/
            uint32_t drefh_sdio:   2;                    /*DREFH_SDIO的SW选项。仅当reg_sdio_force=1时激活*/
            uint32_t xpd_sdio:     1;                    /*XPD_SDIO_REG的SW选项。仅当reg_sdio_force=1时激活*/
        };
        uint32_t val;
    } sdio_conf;
    union {
        struct {
            uint32_t reserved0:            24;
            uint32_t dbg_atten:             2;           /*DBG_ATTEN*/
            uint32_t enb_sck_xtal:          1;           /*ENB_SCK_XTAL*/
            uint32_t inc_heartbeat_refresh: 1;           /*INC_HEARTBEAT_REFRESH*/
            uint32_t dec_heartbeat_period:  1;           /*DEC_HEARTBEAT_PERIOD*/
            uint32_t inc_heartbeat_period:  1;           /*INC_HEARTBEAT_PERIOD*/
            uint32_t dec_heartbeat_width:   1;           /*DEC_HEARTBEAT_WIDTH*/
            uint32_t rst_bias_i2c:          1;           /*RST_BIAS_I2C*/
        };
        uint32_t val;
    } bias_conf;
    union {
        struct {
            uint32_t reserved0:           7;
            uint32_t sck_dcap_force:      1;             /*N/A*/
            uint32_t dig_dbias_slp:       3;             /*休眠期间DIG_REG_DBIAS*/
            uint32_t dig_dbias_wak:       3;             /*唤醒期间DIG_REG_DBIAS*/
            uint32_t sck_dcap:            8;             /*SCK_DCAP*/
            uint32_t rtc_dbias_slp:       3;             /*睡眠期间RTC_DBIAS*/
            uint32_t rtc_dbias_wak:       3;             /*唤醒期间RTC_DBIAS*/
            uint32_t rtc_dboost_force_pd: 1;             /*RTC_DBOOST强制断电*/
            uint32_t rtc_dboost_force_pu: 1;             /*RTC_DBOOST强制加电*/
            uint32_t rtc_force_pd:        1;             /*RTC_REG强制断电（对于RTC_REG断电，意味着将电压降至0.8v或更低）*/
            uint32_t rtc_force_pu:        1;             /*RTC_REG强制加电*/
        };
        uint32_t val;
    } rtc;
    union {
        struct {
            uint32_t fastmem_force_noiso: 1;         /*快速RTC内存强制无ISO*/
            uint32_t fastmem_force_iso:   1;         /*快速RTC记忆力ISO*/
            uint32_t slowmem_force_noiso: 1;         /*RTC内存强制无ISO*/
            uint32_t slowmem_force_iso:   1;         /*RTC记忆力ISO*/
            uint32_t rtc_force_iso:           1;         /*rtc_periforce ISO*/
            uint32_t force_noiso:         1;         /*rtc_periforce无ISO*/
            uint32_t fastmem_folw_cpu:    1;         /*1： CPU 0之后的快速RTC内存PD：RTC状态机之后的快速RTC内存PD*/
            uint32_t fastmem_force_lpd:   1;         /*快速RTC记忆力PD*/
            uint32_t fastmem_force_lpu:   1;         /*快速RTC内存强制无PD*/
            uint32_t slowmem_folw_cpu:    1;         /*1： CPU 0之后的RTC内存PD：RTC状态机之后的RTC存储器PD*/
            uint32_t slowmem_force_lpd:   1;         /*RTC记忆力PD*/
            uint32_t slowmem_force_lpu:   1;         /*RTC内存强制无PD*/
            uint32_t fastmem_force_pd:    1;         /*快速RTC内存强制断电*/
            uint32_t fastmem_force_pu:    1;         /*快速RTC内存强制加电*/
            uint32_t fastmem_pd_en:       1;         /*在休眠状态下启用掉电快速RTC内存*/
            uint32_t slowmem_force_pd:    1;         /*RTC内存强制断电*/
            uint32_t slowmem_force_pu:    1;         /*RTC内存强制加电*/
            uint32_t slowmem_pd_en:       1;         /*在休眠状态下启用掉电RTC内存*/
            uint32_t pwc_force_pd:        1;         /*rtc_perioforce断电*/
            uint32_t pwc_force_pu:        1;         /*rtc_perioforce加电*/
            uint32_t pd_en:               1;         /*在睡眠中启用掉电rtc_peri*/
            uint32_t reserved21:             11;
        };
        uint32_t val;
    } rtc_pwc;
    union {
        struct {
            uint32_t reserved0:           3;
            uint32_t lslp_mem_force_pd:   1;             /*睡眠中数字核心力量PD的记忆*/
            uint32_t lslp_mem_force_pu:   1;             /*数字核心中的记忆迫使睡眠中没有PD*/
            uint32_t rom0_force_pd:       1;             /*ROM强制断电*/
            uint32_t rom0_force_pu:       1;             /*ROM强制加电*/
            uint32_t inter_ram0_force_pd: 1;             /*内部SRAM 0强制断电*/
            uint32_t inter_ram0_force_pu: 1;             /*内部SRAM 0强制加电*/
            uint32_t inter_ram1_force_pd: 1;             /*内部SRAM 1强制断电*/
            uint32_t inter_ram1_force_pu: 1;             /*内部SRAM 1强制加电*/
            uint32_t inter_ram2_force_pd: 1;             /*内部SRAM 2强制断电*/
            uint32_t inter_ram2_force_pu: 1;             /*内部SRAM 2强制加电*/
            uint32_t inter_ram3_force_pd: 1;             /*内部SRAM 3强制断电*/
            uint32_t inter_ram3_force_pu: 1;             /*内部SRAM 3强制加电*/
            uint32_t inter_ram4_force_pd: 1;             /*内部SRAM 4强制断电*/
            uint32_t inter_ram4_force_pu: 1;             /*内部SRAM 4强制加电*/
            uint32_t wifi_force_pd:       1;             /*wifi强制关闭电源*/
            uint32_t wifi_force_pu:       1;             /*wifi强制通电*/
            uint32_t dg_wrap_force_pd:    1;             /*数字核心力量断电*/
            uint32_t dg_wrap_force_pu:    1;             /*数字核心力量通电*/
            uint32_t reserved21:          3;
            uint32_t rom0_pd_en:          1;             /*启用休眠状态下的断电ROM*/
            uint32_t inter_ram0_pd_en:    1;             /*使内部SRAM 0处于休眠状态*/
            uint32_t inter_ram1_pd_en:    1;             /*使内部SRAM 1处于休眠状态*/
            uint32_t inter_ram2_pd_en:    1;             /*在休眠状态下关闭内部SRAM 2*/
            uint32_t inter_ram3_pd_en:    1;             /*使内部SRAM 3在休眠状态下断电*/
            uint32_t inter_ram4_pd_en:    1;             /*在休眠状态下关闭内部SRAM 4*/
            uint32_t wifi_pd_en:          1;             /*在睡眠中关闭wifi*/
            uint32_t dg_wrap_pd_en:       1;             /*在休眠状态下关闭数字核心*/
        };
        uint32_t val;
    } dig_pwc;
    union {
        struct {
            uint32_t reserved0:              7;
            uint32_t dig_iso_force_off:      1;
            uint32_t dig_iso_force_on:       1;
            uint32_t dg_pad_autohold:        1;          /*指示数字焊盘自动保持状态的只读寄存器*/
            uint32_t clr_dg_pad_autohold:    1;          /*wtite仅寄存器以清除数字焊盘自动保持*/
            uint32_t dg_pad_autohold_en:     1;          /*数字键盘启用自动保持*/
            uint32_t dg_pad_force_noiso:     1;          /*数字垫力无ISO*/
            uint32_t dg_pad_force_iso:       1;          /*数字垫力ISO*/
            uint32_t dg_pad_force_unhold:    1;          /*数字衬垫力未保持*/
            uint32_t dg_pad_force_hold:      1;          /*数字衬垫力保持*/
            uint32_t rom0_force_iso:         1;          /*ROM力ISO*/
            uint32_t rom0_force_noiso:       1;          /*ROM力无ISO*/
            uint32_t inter_ram0_force_iso:   1;          /*内部SRAM 0强制ISO*/
            uint32_t inter_ram0_force_noiso: 1;          /*内部SRAM 0强制无ISO*/
            uint32_t inter_ram1_force_iso:   1;          /*内部SRAM 1力ISO*/
            uint32_t inter_ram1_force_noiso: 1;          /*内部SRAM 1强制无ISO*/
            uint32_t inter_ram2_force_iso:   1;          /*内部SRAM 2强制ISO*/
            uint32_t inter_ram2_force_noiso: 1;          /*内部SRAM 2强制无ISO*/
            uint32_t inter_ram3_force_iso:   1;          /*内部SRAM 3力ISO*/
            uint32_t inter_ram3_force_noiso: 1;          /*内部SRAM 3强制无ISO*/
            uint32_t inter_ram4_force_iso:   1;          /*内部SRAM 4力ISO*/
            uint32_t inter_ram4_force_noiso: 1;          /*内部SRAM 4强制无ISO*/
            uint32_t wifi_force_iso:         1;          /*wifi强制ISO*/
            uint32_t wifi_force_noiso:       1;          /*wifi强制无ISO*/
            uint32_t dg_wrap_force_iso:      1;          /*数字核心力量ISO*/
            uint32_t dg_wrap_force_noiso:    1;          /*数字核心力量无ISO*/
        };
        uint32_t val;
    } dig_iso;
    union {
        struct {
            uint32_t reserved0:            7;
            uint32_t pause_in_slp:     1;            /*休眠时暂停WDT*/
            uint32_t appcpu_reset_en:  1;            /*启用WDT重置APP CPU*/
            uint32_t procpu_reset_en:  1;            /*启用WDT重置PRO CPU*/
            uint32_t flashboot_mod_en: 1;            /*在闪存引导中启用WDT*/
            uint32_t sys_reset_length: 3;            /*系统复位计数器长度*/
            uint32_t cpu_reset_length: 3;            /*CPU复位计数器长度*/
            uint32_t level_int_en:     1;            /*设置后，启用电平型中断生成*/
            uint32_t edge_int_en:      1;            /*设置后，启用边缘类型中断生成*/
            uint32_t stg3:             3;            /*1： 中断阶段en 2:CPU重置阶段en 3:系统重置阶段en 4:RTC重置阶段en*/
            uint32_t stg2:             3;            /*1： 中断阶段en 2:CPU重置阶段en 3:系统重置阶段en 4:RTC重置阶段en*/
            uint32_t stg1:             3;            /*1： 中断阶段en 2:CPU重置阶段en 3:系统重置阶段en 4:RTC重置阶段en*/
            uint32_t stg0:             3;            /*1： 中断阶段en 2:CPU重置阶段en 3:系统重置阶段en 4:RTC重置阶段en*/
            uint32_t en:               1;            /*启用RTC WDT*/
        };
        uint32_t val;
    } wdt_config0;
    uint32_t wdt_config1;                             /**/
    uint32_t wdt_config2;                             /**/
    uint32_t wdt_config3;                             /**/
    uint32_t wdt_config4;                             /**/
    union {
        struct {
            uint32_t reserved0:   31;
            uint32_t feed: 1;
        };
        uint32_t val;
    } wdt_feed;
    uint32_t wdt_wprotect;                            /**/
    union {
        struct {
            uint32_t reserved0: 29;
            uint32_t ent_rtc:    1;                      /*ENT_RTC*/
            uint32_t dtest_rtc:  2;                      /*DTEST_RTC*/
        };
        uint32_t val;
    } test_mux;
    union {
        struct {
            uint32_t reserved0:         20;
            uint32_t appcpu_c1: 6;              /*｛reg_sw_stall_appcpu_c1[5:0]reg_sw_stall_appcp u_c1[1:0]｝==0x86将停止APP CPU*/
            uint32_t procpu_c1: 6;              /*｛reg_sw_stall_procpu_c1[5:0]reg_sw_stall_procpu_c0[1:0]｝==0x86将停止PRO CPU*/
        };
        uint32_t val;
    } sw_cpu_stall;
    uint32_t store4;                                 /*32位通用保留寄存器*/
    uint32_t store5;                                 /*32位通用保留寄存器*/
    uint32_t store6;                                 /*32位通用保留寄存器*/
    uint32_t store7;                                 /*32位通用保留寄存器*/
    uint32_t diag0;                                  /**/
    uint32_t diag1;                                  /**/
    union {
        struct {
            uint32_t adc1_hold_force:       1;
            uint32_t adc2_hold_force:       1;
            uint32_t pdac1_hold_force:      1;
            uint32_t pdac2_hold_force:      1;
            uint32_t sense1_hold_force:     1;
            uint32_t sense2_hold_force:     1;
            uint32_t sense3_hold_force:     1;
            uint32_t sense4_hold_force:     1;
            uint32_t touch_pad0_hold_force: 1;
            uint32_t touch_pad1_hold_force: 1;
            uint32_t touch_pad2_hold_force: 1;
            uint32_t touch_pad3_hold_force: 1;
            uint32_t touch_pad4_hold_force: 1;
            uint32_t touch_pad5_hold_force: 1;
            uint32_t touch_pad6_hold_force: 1;
            uint32_t touch_pad7_hold_force: 1;
            uint32_t x32p_hold_force:       1;
            uint32_t x32n_hold_force:       1;
            uint32_t reserved18:           14;
        };
        uint32_t val;
    } hold_force;
    union {
        struct {
            uint32_t ext_wakeup1_sel:       18;          /*用于选择下一次唤醒的RTC焊盘的位图1*/
            uint32_t ext_wakeup1_status_clr: 1;          /*清除ext唤醒1状态*/
            uint32_t reserved19:            13;
        };
        uint32_t val;
    } ext_wakeup1;
    union {
        struct {
            uint32_t ext_wakeup1_status:18;              /*ext唤醒1状态*/
            uint32_t reserved18:        14;
        };
        uint32_t val;
    } ext_wakeup1_status;
    union {
        struct {
            uint32_t reserved0:                14;
            uint32_t close_flash_ena: 1;       /*在发生断电时启用关闭闪光灯*/
            uint32_t pd_rf_ena:       1;       /*发生断电时启用断电RF*/
            uint32_t rst_wait:       10;       /*断电复位等待周期*/
            uint32_t rst_ena:         1;       /*启用断电复位*/
            uint32_t thres:          3;       /*褐化阈值*/
            uint32_t ena:             1;       /*启用棕色输出*/
            uint32_t det:         1;       /*褐化检测*/
        };
        uint32_t val;
    } brown_out;
    uint32_t reserved_39;
    uint32_t reserved_3d;
    uint32_t reserved_41;
    uint32_t reserved_45;
    uint32_t reserved_49;
    uint32_t reserved_4d;
    union {
        struct {
            uint32_t date:      28;
            uint32_t reserved28: 4;
        };
        uint32_t val;
    } date;
} rtc_cntl_dev_t;
extern rtc_cntl_dev_t RTCCNTL;

#ifdef __cplusplus
}
#endif

#endif  /* _SOC_RTC_CNTL_STRUCT_H_ */

