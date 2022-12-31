// 版权所有2017-2018 Espressif Systems（上海）私人有限公司
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
#ifndef _SOC_RTC_CNTL_STRUCT_H_
#define _SOC_RTC_CNTL_STRUCT_H_
#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

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
            uint32_t xtl_en_wait:         4;             /*等待bias_sleep和电流源唤醒*/
            uint32_t reserved18:          5;
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
            uint32_t main_timer_alarm_en:     1;         /*定时器报警启用位*/
            uint32_t reserved17:             15;
        };
        uint32_t val;
    } slp_timer1;
    union {
        struct {
            uint32_t reserved0:      27;
            uint32_t timer_sys_stall: 1;                 /*启用以记录系统暂停时间*/
            uint32_t timer_xtl_off:   1;                 /*启用以记录40M XTAL OFF时间*/
            uint32_t timer_sys_rst:   1;                 /*启用以记录系统重置时间*/
            uint32_t reserved30:      1;
            uint32_t update:          1;                 /*设置1：用RTC计时器更新寄存器*/
        };
        uint32_t val;
    } time_update;
    uint32_t time_low0;                              /*RTC定时器低32位*/
    union {
        struct {
            uint32_t rtc_timer_value0_high:16;           /*RTC计时器高16位*/
            uint32_t reserved16:           16;
        };
        uint32_t val;
    } time_high0;
    union {
        struct {
            uint32_t rtc_sw_cpu_int:           1;        /*主cpu的rtc软件中断*/
            uint32_t rtc_slp_reject_cause_clr: 1;        /*清除rtc睡眠拒绝原因*/
            uint32_t reserved2:               20;
            uint32_t apb2rtc_bridge_sel:       1;        /*1： APB到RTC使用桥0：APB到RTC使用同步*/
            uint32_t reserved23:               5;
            uint32_t sdio_active_ind:          1;        /*SDIO激活指示*/
            uint32_t slp_wakeup:               1;        /*睡眠唤醒位*/
            uint32_t slp_reject:               1;        /*leep拒绝钻头*/
            uint32_t sleep_en:                 1;        /*休眠启用位*/
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
            uint32_t reserved0:            8;
            uint32_t min_slp_val:          8;            /*slowclkrtc中的最小睡眠周期*/
            uint32_t rtcmem_wait_timer:    9;
            uint32_t rtcmem_powerup_timer: 7;
        };
        uint32_t val;
    } timer5;
    union {
        struct {
            uint32_t reserved0:            16;
            uint32_t dg_dcdc_wait_timer:    9;
            uint32_t dg_dcdc_powerup_timer: 7;
        };
        uint32_t val;
    } timer6;
    union {
        struct {
            uint32_t reserved0:             18;
            uint32_t i2c_reset_por_force_pd: 1;
            uint32_t i2c_reset_por_force_pu: 1;
            uint32_t glitch_rst_en:          1;
            uint32_t sar_i2c_force_pd:       1;          /*PLLA强制断电*/
            uint32_t sar_i2c_force_pu:       1;          /*PLLA强制加电*/
            uint32_t plla_force_pd:          1;          /*PLLA强制断电*/
            uint32_t plla_force_pu:          1;          /*PLLA强制加电*/
            uint32_t bbpll_cal_slp_start:    1;          /*在休眠期间启动BBPLL校准*/
            uint32_t pvtmon_pu:              1;          /*1： PVTMON通电，否则断电*/
            uint32_t txrf_i2c_pu:            1;          /*1： TXRF_I2C通电，否则断电*/
            uint32_t rfrx_pbus_pu:           1;          /*1： RFRX_PBUS通电，否则断电*/
            uint32_t reserved29:             1;
            uint32_t ckgen_i2c_pu:           1;          /*1： CKGEN_I2C通电，否则断电*/
            uint32_t pll_i2c_pu:             1;
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
            uint32_t reserved0:     15;
            uint32_t rtc_wakeup_ena:17;                  /*唤醒启用位图*/
        };
        uint32_t val;
    } wakeup_state;
    union {
        struct {
            uint32_t slp_wakeup:                  1;     /*启用睡眠唤醒中断*/
            uint32_t slp_reject:                  1;     /*启用睡眠拒绝中断*/
            uint32_t sdio_idle:                   1;     /*启用SDIO空闲中断*/
            uint32_t rtc_wdt:                     1;     /*启用RTC WDT中断*/
            uint32_t rtc_touch_scan_done:         1;     /*启用触摸扫描完成中断*/
            uint32_t rtc_ulp_cp:                  1;     /*启用ULP协处理器中断*/
            uint32_t rtc_touch_done:              1;     /*启用触摸完成中断*/
            uint32_t rtc_touch_active:            1;     /*启用触摸激活中断*/
            uint32_t rtc_touch_inactive:          1;     /*启用触摸非激活中断*/
            uint32_t rtc_brown_out:               1;     /*启用断电中断*/
            uint32_t rtc_main_timer:              1;     /*启用RTC主计时器中断*/
            uint32_t rtc_saradc1:                 1;     /*启用saradc1中断*/
            uint32_t rtc_tsens:                   1;     /*启用tsens中断*/
            uint32_t rtc_cocpu:                   1;     /*启用riscV cocpu中断*/
            uint32_t rtc_saradc2:                 1;     /*启用saradc2中断*/
            uint32_t rtc_swd:                     1;     /*启用超级看门狗中断*/
            uint32_t rtc_xtal32k_dead:            1;     /*启用xtal32k_day中断*/
            uint32_t rtc_cocpu_trap:              1;     /*启用cocpu陷阱中断*/
            uint32_t rtc_touch_timeout:           1;     /*启用触摸超时中断*/
            uint32_t rtc_glitch_det:              1;     /*enbale gitch det中断*/
            uint32_t reserved20:                 12;
        };
        uint32_t val;
    } int_ena;
    union {
        struct {
            uint32_t slp_wakeup:                  1;     /*睡眠唤醒中断raw*/
            uint32_t slp_reject:                  1;     /*睡眠拒绝中断原始*/
            uint32_t sdio_idle:                   1;     /*SDIO空闲中断原始*/
            uint32_t rtc_wdt:                     1;     /*RTC WDT中断原始*/
            uint32_t rtc_touch_scan_done:         1;
            uint32_t rtc_ulp_cp:                  1;     /*ULP协处理器中断原始*/
            uint32_t rtc_touch_done:              1;     /*原始触摸中断*/
            uint32_t rtc_touch_active:            1;     /*触摸激活中断原始*/
            uint32_t rtc_touch_inactive:          1;     /*触摸非活动中断原始*/
            uint32_t rtc_brown_out:               1;     /*棕色中断原始*/
            uint32_t rtc_main_timer:              1;     /*RTC主计时器中断原始*/
            uint32_t rtc_saradc1:                 1;     /*saradc1中断原始*/
            uint32_t rtc_tsens:                   1;     /*tsens中断原始*/
            uint32_t rtc_cocpu:                   1;     /*riscV cocpu中断原始*/
            uint32_t rtc_saradc2:                 1;     /*saradc2中断原始*/
            uint32_t rtc_swd:                     1;     /*超级看门狗中断raw*/
            uint32_t rtc_xtal32k_dead:            1;     /*xtal32k死检测中断原始*/
            uint32_t rtc_cocpu_trap:              1;     /*cocpu陷阱中断原始*/
            uint32_t rtc_touch_timeout:           1;     /*触摸超时中断原始*/
            uint32_t rtc_glitch_det:              1;     /*故障_det_interrupt_raw*/
            uint32_t reserved20:                 12;
        };
        uint32_t val;
    } int_raw;
    union {
        struct {
            uint32_t slp_wakeup:                 1;      /*睡眠唤醒中断状态*/
            uint32_t slp_reject:                 1;      /*睡眠拒绝中断状态*/
            uint32_t sdio_idle:                  1;      /*SDIO空闲中断状态*/
            uint32_t rtc_wdt:                    1;      /*RTC WDT中断状态*/
            uint32_t rtc_touch_scan_done:        1;
            uint32_t rtc_ulp_cp:                 1;      /*ULP协处理器中断状态*/
            uint32_t rtc_touch_done:             1;      /*触摸完成中断状态*/
            uint32_t rtc_touch_active:           1;      /*触摸激活中断状态*/
            uint32_t rtc_touch_inactive:         1;      /*触摸不活动中断状态*/
            uint32_t rtc_brown_out:              1;      /*断电中断状态*/
            uint32_t rtc_main_timer:             1;      /*RTC主计时器中断状态*/
            uint32_t rtc_saradc1:                1;      /*saradc1中断状态*/
            uint32_t rtc_tsens:                  1;      /*tsens中断状态*/
            uint32_t rtc_cocpu:                  1;      /*riscV cocpu中断状态*/
            uint32_t rtc_saradc2:                1;      /*saradc2中断状态*/
            uint32_t rtc_swd:                    1;      /*超级看门狗中断状态*/
            uint32_t rtc_xtal32k_dead:           1;      /*xtal32k死检测中断状态*/
            uint32_t rtc_cocpu_trap:             1;      /*cocpu陷阱中断状态*/
            uint32_t rtc_touch_timeout:          1;      /*触摸超时中断状态*/
            uint32_t rtc_glitch_det:             1;      /*故障_det_中断状态*/
            uint32_t reserved20:                12;
        };
        uint32_t val;
    } int_st;
    union {
        struct {
            uint32_t slp_wakeup:                  1;     /*清除睡眠唤醒中断状态*/
            uint32_t slp_reject:                  1;     /*清除睡眠拒绝中断状态*/
            uint32_t sdio_idle:                   1;     /*清除SDIO空闲中断状态*/
            uint32_t rtc_wdt:                     1;     /*清除RTC WDT中断状态*/
            uint32_t rtc_touch_scan_done:         1;
            uint32_t rtc_ulp_cp:                  1;     /*清除ULP协处理器中断状态*/
            uint32_t rtc_touch_done:              1;     /*清除触摸完成中断状态*/
            uint32_t rtc_touch_active:            1;     /*清除触摸激活中断状态*/
            uint32_t rtc_touch_inactive:          1;     /*清除触摸非激活中断状态*/
            uint32_t rtc_brown_out:               1;     /*清除棕色中断状态*/
            uint32_t rtc_main_timer:              1;     /*清除RTC主计时器中断状态*/
            uint32_t rtc_saradc1:                 1;     /*清除saradc1中断状态*/
            uint32_t rtc_tsens:                   1;     /*清除tsens中断状态*/
            uint32_t rtc_cocpu:                   1;     /*清除riscV cocpu中断状态*/
            uint32_t rtc_saradc2:                 1;     /*清除saradc2中断状态*/
            uint32_t rtc_swd:                     1;     /*清除超级看门狗中断状态*/
            uint32_t rtc_xtal32k_dead:            1;     /*清除RTC WDT中断状态*/
            uint32_t rtc_cocpu_trap:              1;     /*清除cocpu陷阱中断状态*/
            uint32_t rtc_touch_timeout:           1;     /*清除触摸超时中断状态*/
            uint32_t rtc_glitch_det:              1;     /*清除故障检测中断状态*/
            uint32_t reserved20:                 12;
        };
        uint32_t val;
    } int_clr;
    uint32_t store[4];                                 /**/
    union {
        struct {
            uint32_t xtal32k_wdt_en:       1;            /*xtal 32k看门狗启用*/
            uint32_t xtal32k_wdt_clk_fo:   1;            /*xtal 32k看门狗时钟强制开启*/
            uint32_t xtal32k_wdt_reset:    1;            /*xtal 32k看门狗开关复位*/
            uint32_t xtal32k_ext_clk_fo:   1;            /*xtal 32k外部xtal时钟力开启*/
            uint32_t xtal32k_auto_backup:  1;            /*xtal关闭时，xtal 32k切换到备份时钟*/
            uint32_t xtal32k_auto_restart: 1;            /*xtal死后，xtal 32k重新启动xtal*/
            uint32_t xtal32k_auto_return:  1;            /*xtal重启时，xtal 32k切换回xtal*/
            uint32_t xtal32k_xpd_force:    1;            /*通过sw或fsm控制Xtal 32k xpd*/
            uint32_t enckinit_xtal_32k:    1;            /*应用内部时钟帮助xtal 32k启动*/
            uint32_t dbuf_xtal_32k:        1;            /*0：单端缓冲器1：差分缓冲器*/
            uint32_t dgm_xtal_32k:         3;            /*xtal_32k gm控制*/
            uint32_t dres_xtal_32k:        3;            /*DRES_XTAL_32K*/
            uint32_t xpd_xtal_32k:         1;            /*XPD_XTAL_32K*/
            uint32_t dac_xtal_32k:         3;            /*DAC_XTAL_32K*/
            uint32_t rtc_wdt_state:        3;            /*32k_wdt的状态*/
            uint32_t rtc_xtal32k_gpio_sel: 1;            /*XTAL_32K选择。0：外部XTAL_32K 1：来自RTC焊盘X32P_C的CLK*/
            uint32_t reserved24:           6;
            uint32_t ctr_lv:               1;            /*0：关闭高电平XTAL电源1：关闭低电平XTAL*/
            uint32_t ctr_en:               1;
        };
        uint32_t val;
    } ext_xtl_conf;
    union {
        struct {
            uint32_t reserved0:         29;
            uint32_t gpio_wakeup_filter: 1;              /*为gpio唤醒事件启用筛选器*/
            uint32_t wakeup0_lv:         1;              /*0：低电平外部唤醒1：高电平外部唤醒*/
            uint32_t wakeup1_lv:         1;
        };
        uint32_t val;
    } ext_wakeup_conf;
    union {
        struct {
            uint32_t reserved0:           13;
            uint32_t rtc_sleep_reject_ena:17;            /*睡眠拒绝启用*/
            uint32_t light_slp_reject_en:  1;            /*启用轻睡眠拒绝*/
            uint32_t deep_slp_reject_en:   1;            /*启用深度睡眠拒绝*/
        };
        uint32_t val;
    } slp_reject_conf;
    union {
        struct {
            uint32_t reserved0:        29;
            uint32_t cpusel_conf:       1;               /*CPU选择选项*/
            uint32_t cpuperiod_sel:     2;
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
            uint32_t reserved0:           3;
            uint32_t ck8m_div_sel_vld:    1;             /*用于同步reg_ck8m_div_sel总线。在设置reg_ck8m_div_sel之前清除vld，然后设置vld以实际切换clk*/
            uint32_t ck8m_div:            2;             /*CK8M_D256_OUT除法器。00:div128 01:div256 10:div512 11:div1024。*/
            uint32_t enb_ck8m:            1;             /*禁用CK8M和CK8M_D256_OUT*/
            uint32_t enb_ck8m_div:        1;             /*1： CK8M_D256_OUT实际上是CK8M 0：CK8M_D256 _OUT是CK8MM除以256*/
            uint32_t dig_xtal32k_en:      1;             /*为数字核心启用CK_XTAL_32K（与RTC核心无关系）*/
            uint32_t dig_clk8m_d256_en:   1;             /*为数字核心启用CK8M_D256_OUT（与RTC核心无关系）*/
            uint32_t dig_clk8m_en:        1;             /*为数字核心启用CK8M（与RTC核心无关系）*/
            uint32_t reserved11:          1;
            uint32_t ck8m_div_sel:        3;             /*除法器=reg_ck8m_div_sel+1*/
            uint32_t xtal_force_nogating: 1;             /*睡眠期间XTAL强制无门控*/
            uint32_t ck8m_force_nogating: 1;             /*CK8M在睡眠期间强制无门控*/
            uint32_t ck8m_dfreq:          8;             /*CK8M_DFREQ*/
            uint32_t ck8m_force_pd:       1;             /*CK8M强制断电*/
            uint32_t ck8m_force_pu:       1;             /*CK8M强制加电*/
            uint32_t reserved27:          2;
            uint32_t fast_clk_rtc_sel:    1;             /*fast_clk_rtc选择。0:XTAL分区4 1:CK8M*/
            uint32_t ana_clk_rtc_sel:     2;
        };
        uint32_t val;
    } clk_conf;
    union {
        struct {
            uint32_t reserved0:             22;
            uint32_t rtc_ana_clk_div_vld:    1;          /*用于同步div总线。在设置reg_rtc_ana_clk_div之前清除vld，然后设置vld以实际切换clk*/
            uint32_t rtc_ana_clk_div:        8;
            uint32_t slow_clk_next_edge:     1;
        };
        uint32_t val;
    } slow_clk_conf;
    union {
        struct {
            uint32_t sdio_timer_target: 8;               /*sdio通电后应用reg_sdio_dcap的计时器计数*/
            uint32_t reserved8:         1;
            uint32_t sdio_dthdrv:       2;               /*Tieh=1模式驱动能力。最初设置为0，以限制充电电流设置为3。*/
            uint32_t sdio_dcap:         2;               /*防止LDO过冲的能力*/
            uint32_t sdio_initi:        2;               /*将电阻从ldo输出端接地。0：无分辨率1:6k 2:4k 3:2k*/
            uint32_t sdio_en_initi:     1;               /*0设置init[1:0]=0*/
            uint32_t sdio_dcurlim:      3;               /*当tieh=0时调谐电流限制阈值。约800mA/（8+d）*/
            uint32_t sdio_modecurlim:   1;               /*选择电流限制模式*/
            uint32_t sdio_encurlim:     1;               /*启用电流限制*/
            uint32_t sdio_pd_en:        1;               /*关闭休眠状态下的SDIO_REG。仅当reg_sdio_force=0时激活*/
            uint32_t sdio_force:        1;               /*1： 使用SW选项控制SDIO_REG 0：使用状态机*/
            uint32_t sdio_tieh:         1;               /*SDIO_TIEH的SW选项。仅当reg_sdio_force=1时激活*/
            uint32_t reg1p8_ready:      1;               /*REG1P8_READY的只读寄存器*/
            uint32_t drefl_sdio:        2;               /*DREFL_SDIO的SW选项。仅当reg_sdio_force=1时激活*/
            uint32_t drefm_sdio:        2;               /*DREFM_SDIO的SW选项。仅当reg_sdio_force=1时激活*/
            uint32_t drefh_sdio:        2;               /*DREFH_SDIO的SW选项。仅当reg_sdio_force=1时激活*/
            uint32_t xpd_sdio:          1;
        };
        uint32_t val;
    } sdio_conf;
    union {
        struct {
            uint32_t reserved0:            10;
            uint32_t bias_buf_idle:         1;
            uint32_t bias_buf_wake:         1;
            uint32_t bias_buf_deep_slp:     1;
            uint32_t bias_buf_monitor:      1;
            uint32_t pd_cur_deep_slp:       1;           /*rtc处于sleep_state时的xpd-cur*/
            uint32_t pd_cur_monitor:        1;           /*rtc处于监视器状态时的xpd-cur*/
            uint32_t bias_sleep_deep_slp:   1;           /*当rtc处于sleep_state时，bias_sleep*/
            uint32_t bias_sleep_monitor:    1;           /*当rtc处于监视器状态时bias_sleep*/
            uint32_t dbg_atten_deep_slp:    4;           /*rtc处于睡眠状态时的DBG_ATTEN*/
            uint32_t dbg_atten_monitor:     4;           /*rtc处于监视器状态时的DBG_ATTEN*/
            uint32_t enb_sck_xtal:          1;           /*ENB_SCK_XTAL*/
            uint32_t inc_heartbeat_refresh: 1;           /*INC_HEARTBEAT_REFRESH*/
            uint32_t dec_heartbeat_period:  1;           /*DEC_HEARTBEAT_PERIOD*/
            uint32_t inc_heartbeat_period:  1;           /*INC_HEARTBEAT_PERIOD*/
            uint32_t dec_heartbeat_width:   1;           /*DEC_HEARTBEAT_WIDTH*/
            uint32_t rst_bias_i2c:          1;
        };
        uint32_t val;
    } bias_conf;
    union {
        struct {
            uint32_t reserved0:           8;
            uint32_t dig_dbias_slp:       3;             /*休眠期间DIG_REG_DBIAS*/
            uint32_t dig_dbias_wak:       3;             /*唤醒期间DIG_REG_DBIAS*/
            uint32_t sck_dcap:            8;             /*SCK_DCAP*/
            uint32_t rtc_dbias_slp:       3;             /*睡眠期间RTC_DBIAS*/
            uint32_t rtc_dbias_wak:       3;             /*唤醒期间RTC_DBIAS*/
            uint32_t rtc_dboost_force_pd: 1;             /*RTC_DBOOST强制断电*/
            uint32_t rtc_dboost_force_pu: 1;             /*RTC_DBOOST强制加电*/
            uint32_t rtculator_force_pd:  1;             /*RTC_REG强制断电（对于RTC_REG断电，意味着将电压降至0.8v或更低）*/
            uint32_t rtculator_force_pu:  1;
        };
        uint32_t val;
    } rtc;
    union {
        struct {
            uint32_t fastmem_force_noiso:     1;         /*快速RTC内存强制无ISO*/
            uint32_t fastmem_force_iso:       1;         /*快速RTC记忆力ISO*/
            uint32_t slowmem_force_noiso:     1;         /*RTC内存强制无ISO*/
            uint32_t slowmem_force_iso:       1;         /*RTC记忆力ISO*/
            uint32_t rtc_force_iso:           1;         /*rtc_periforce ISO*/
            uint32_t rtc_force_noiso:         1;         /*rtc_periforce无ISO*/
            uint32_t fastmem_folw_cpu:        1;         /*1： CPU 0之后的快速RTC内存PD：RTC状态机之后的快速RTC内存PD*/
            uint32_t fastmem_force_lpd:       1;         /*快速RTC记忆力PD*/
            uint32_t fastmem_force_lpu:       1;         /*快速RTC内存强制无PD*/
            uint32_t slowmem_folw_cpu:        1;         /*1： CPU 0之后的RTC内存PD：RTC状态机之后的RTC存储器PD*/
            uint32_t slowmem_force_lpd:       1;         /*RTC记忆力PD*/
            uint32_t slowmem_force_lpu:       1;         /*RTC内存强制无PD*/
            uint32_t fastmem_force_pd:        1;         /*快速RTC内存强制断电*/
            uint32_t fastmem_force_pu:        1;         /*快速RTC内存强制加电*/
            uint32_t fastmem_pd_en:           1;         /*在休眠状态下启用掉电快速RTC内存*/
            uint32_t slowmem_force_pd:        1;         /*RTC内存强制断电*/
            uint32_t slowmem_force_pu:        1;         /*RTC内存强制加电*/
            uint32_t slowmem_pd_en:           1;         /*在休眠状态下启用掉电RTC内存*/
            uint32_t rtc_force_pd:            1;         /*rtc_perioforce断电*/
            uint32_t rtc_force_pu:            1;         /*rtc_perioforce加电*/
            uint32_t rtc_pd_en:               1;         /*在睡眠中启用掉电rtc_peri*/
            uint32_t rtc_pad_force_hold:      1;         /*rtc衬垫力保持*/
            uint32_t reserved22:             10;
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
            uint32_t dg_dcdc_force_pd:    1;             /*数字dcdc强制断电*/
            uint32_t dg_dcdc_force_pu:    1;             /*数字dcdc强制加电*/
            uint32_t dg_dcdc_pd_en:       1;             /*在休眠状态下启用断电数字dcdc*/
            uint32_t rom0_pd_en:          1;             /*启用休眠状态下的断电ROM*/
            uint32_t inter_ram0_pd_en:    1;             /*使内部SRAM 0处于休眠状态*/
            uint32_t inter_ram1_pd_en:    1;             /*使内部SRAM 1处于休眠状态*/
            uint32_t inter_ram2_pd_en:    1;             /*在休眠状态下关闭内部SRAM 2*/
            uint32_t inter_ram3_pd_en:    1;             /*使内部SRAM 3在休眠状态下断电*/
            uint32_t inter_ram4_pd_en:    1;             /*在休眠状态下关闭内部SRAM 4*/
            uint32_t wifi_pd_en:          1;             /*在睡眠中关闭wifi*/
            uint32_t dg_wrap_pd_en:       1;
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
            uint32_t dg_wrap_force_noiso:    1;
        };
        uint32_t val;
    } dig_iso;
    union {
        struct {
            uint32_t chip_reset_width:     8;            /*芯片复位信号脉冲宽度*/
            uint32_t chip_reset_en:        1;            /*wdt重置全芯片启用*/
            uint32_t pause_in_slp:         1;            /*休眠时暂停WDT*/
            uint32_t appcpu_reset_en:      1;            /*启用WDT重置APP CPU*/
            uint32_t procpu_reset_en:      1;            /*启用WDT重置PRO CPU*/
            uint32_t flashboot_mod_en:     1;            /*在闪存引导中启用WDT*/
            uint32_t sys_reset_length:     3;            /*系统复位计数器长度*/
            uint32_t cpu_reset_length:     3;            /*CPU复位计数器长度*/
            uint32_t stg3:                 3;            /*1： 中断阶段en 2:CPU重置阶段en 3:系统重置阶段en 4:RTC重置阶段en*/
            uint32_t stg2:                 3;            /*1： 中断阶段en 2:CPU重置阶段en 3:系统重置阶段en 4:RTC重置阶段en*/
            uint32_t stg1:                 3;            /*1： 中断阶段en 2:CPU重置阶段en 3:系统重置阶段en 4:RTC重置阶段en*/
            uint32_t stg0:                 3;            /*1： 中断阶段en 2:CPU重置阶段en 3:系统重置阶段en 4:RTC重置阶段en*/
            uint32_t en:                   1;
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
            uint32_t feed:         1;
        };
        uint32_t val;
    } wdt_feed;
    uint32_t wdt_wprotect;                            /**/
    union {
        struct {
            uint32_t swd_reset_flag:   1;                /*swd复位标志*/
            uint32_t swd_feed_int:     1;                /*swd馈电中断*/
            uint32_t reserved2:       16;
            uint32_t swd_signal_width:10;                /*调整发送到swd的信号宽度*/
            uint32_t swd_rst_flag_clr: 1;                /*重置swd重置标志*/
            uint32_t swd_feed:         1;                /*开关馈电开关*/
            uint32_t swd_disable:      1;                /*禁用SWD*/
            uint32_t swd_auto_feed_en: 1;                /*int出现时自动馈送swd*/
        };
        uint32_t val;
    } swd_conf;
    uint32_t swd_wprotect;                           /*swd写保护*/
    union {
        struct {
            uint32_t reserved0:         20;
            uint32_t appcpu_c1:          6;              /*｛reg_sw_stall_appcpu_c1[5:0]reg_sw_stall_appcp u_c1[1:0]｝==0x86将停止APP CPU*/
            uint32_t procpu_c1:          6;
        };
        uint32_t val;
    } sw_cpu_stall;
    uint32_t store4;                                 /**/
    uint32_t store5;                                 /**/
    uint32_t store6;                                 /**/
    uint32_t store7;                                 /**/
    union {
        struct {
            uint32_t xpd_rom0:                   1;      /*rom0断电*/
            uint32_t reserved1:                  1;
            uint32_t xpd_dig_dcdc:               1;      /*外部DCDC电源关闭*/
            uint32_t rtc_peri_iso:               1;      /*rtc外围iso*/
            uint32_t xpd_rtc_peri:               1;      /*rtc外围设备断电*/
            uint32_t wifi_iso:                   1;      /*wifi iso*/
            uint32_t xpd_wifi:                   1;      /*wifi关闭电源*/
            uint32_t dig_iso:                    1;      /*数字环绕iso*/
            uint32_t xpd_dig:                    1;      /*数字包装断电*/
            uint32_t rtc_touch_state_start:      1;      /*触摸应该开始工作*/
            uint32_t rtc_touch_state_switch:     1;      /*触摸即将生效。开关rtc主状态*/
            uint32_t rtc_touch_state_slp:        1;      /*touch处于睡眠状态*/
            uint32_t rtc_touch_state_done:       1;      /*触摸已完成*/
            uint32_t rtc_cocpu_state_start:      1;      /*ulp/cocpu应该开始工作*/
            uint32_t rtc_cocpu_state_switch:     1;      /*ulp/cocpu即将开始工作。开关rtc主状态*/
            uint32_t rtc_cocpu_state_slp:        1;      /*ulp/cocpu处于睡眠状态*/
            uint32_t rtc_cocpu_state_done:       1;      /*ulp/cocpu完成*/
            uint32_t rtc_main_state_xtal_iso:    1;      /*不再有用了*/
            uint32_t rtc_main_state_pll_on:      1;      /*rtc主状态机处于pll应该运行的状态*/
            uint32_t rtc_rdy_for_wakeup:         1;      /*rtc已准备好从唤醒源接收唤醒触发*/
            uint32_t rtc_main_state_wait_end:    1;      /*rtc主状态机已等待了一些周期*/
            uint32_t rtc_in_wakeup_state:        1;      /*rtc主状态机处于唤醒过程状态*/
            uint32_t rtc_in_low_power_state:     1;      /*rtc主状态机处于低功耗状态*/
            uint32_t rtc_main_state_in_wait_8m:  1;      /*rtc主状态机处于等待8m状态*/
            uint32_t rtc_main_state_in_wait_pll: 1;      /*rtc主状态机处于等待锁相环状态*/
            uint32_t rtc_main_state_in_wait_xtl: 1;      /*rtc主状态机处于等待xtal状态*/
            uint32_t rtc_main_state_in_slp:      1;      /*rtc主状态机处于休眠状态*/
            uint32_t rtc_main_state_in_idle:     1;      /*rtc主状态机处于空闲状态*/
            uint32_t rtc_main_state:             4;      /*rtc主状态机状态*/
        };
        uint32_t val;
    } low_power_st;
    uint32_t diag0;                                  /**/
    union {
        struct {
            uint32_t touch_pad0_hold:  1;
            uint32_t touch_pad1_hold:  1;
            uint32_t touch_pad2_hold:  1;
            uint32_t touch_pad3_hold:  1;
            uint32_t touch_pad4_hold:  1;
            uint32_t touch_pad5_hold:  1;
            uint32_t touch_pad6_hold:  1;
            uint32_t touch_pad7_hold:  1;
            uint32_t touch_pad8_hold:  1;
            uint32_t touch_pad9_hold:  1;
            uint32_t touch_pad10_hold: 1;
            uint32_t touch_pad11_hold: 1;
            uint32_t touch_pad12_hold: 1;
            uint32_t touch_pad13_hold: 1;
            uint32_t touch_pad14_hold: 1;
            uint32_t x32p_hold:        1;
            uint32_t x32n_hold:        1;
            uint32_t pdac1_hold:       1;
            uint32_t pdac2_hold:       1;
            uint32_t rtc_pad19_hold:   1;
            uint32_t rtc_pad20_hold:   1;
            uint32_t rtc_pad21_hold:   1;
            uint32_t reserved22:      10;
        };
        uint32_t val;
    } pad_hold;
    uint32_t dig_pad_hold;                               /**/
    union {
        struct {
            uint32_t sel:                   22;          /*用于选择下一次唤醒的RTC焊盘的位图1*/
            uint32_t status_clr:             1;          /*清除ext唤醒1状态*/
            uint32_t reserved23:             9;
        };
        uint32_t val;
    } ext_wakeup1;
    union {
        struct {
            uint32_t status:            22;              /*ext唤醒1状态*/
            uint32_t reserved22:        10;
        };
        uint32_t val;
    } ext_wakeup1_status;
    union {
        struct {
            uint32_t out2_ena:                  1;       /*启用brown_out2以启动芯片重置*/
            uint32_t reserved1:                 3;
            uint32_t int_wait:                 10;       /*棕色中断等待周期*/
            uint32_t close_flash_ena:           1;       /*在发生断电时启用关闭闪光灯*/
            uint32_t pd_rf_ena:                 1;       /*发生断电时启用断电RF*/
            uint32_t rst_wait:                 10;       /*断电复位等待周期*/
            uint32_t rst_ena:                   1;       /*启用断电复位*/
            uint32_t rst_sel:                   1;       /*1： 4针复位*/
            uint32_t reserved28:                1;
            uint32_t cnt_clr:                   1;       /*清褐计数器*/
            uint32_t ena:                       1;       /*启用棕色输出*/
            uint32_t det:                       1;
        };
        uint32_t val;
    } brown_out;
    uint32_t time_low1;                              /*RTC定时器低32位*/
    union {
        struct {
            uint32_t rtc_timer_value1_high:16;           /*RTC计时器高16位*/
            uint32_t reserved16:           16;
        };
        uint32_t val;
    } time_high1;
    uint32_t xtal32k_clk_factor;                     /*xtal 32k看门狗备份时钟因子*/
    union {
        struct {
            uint32_t xtal32k_return_wait:  4;            /*等待返回noral xtal 32k的周期*/
            uint32_t xtal32k_restart_wait:16;            /*等待在xtal 32k上重新供电的周期*/
            uint32_t xtal32k_wdt_timeout:  8;            /*如果在该时间量32k内没有检测到时钟，则视为无效*/
            uint32_t xtal32k_stable_thres: 4;            /*如果重启的xtal32k周期小于此值，则视为稳定*/
        };
        uint32_t val;
    } xtal32k_conf;
    union {
        struct {
            uint32_t ulp_cp_pc_init:        11;          /*ULP协处理器PC初始地址*/
            uint32_t reserved11:            18;
            uint32_t ulp_cp_gpio_wakeup_ena: 1;          /*通过GPIO启用ULP协处理器唤醒*/
            uint32_t ulp_cp_gpio_wakeup_clr: 1;          /*ULP协处理器通过GPIO状态清除唤醒*/
            uint32_t ulp_cp_slp_timer_en:    1;          /*ULP协处理器定时器启用位*/
        };
        uint32_t val;
    } ulp_cp_timer;
    union {
        struct {
            uint32_t ulp_cp_mem_addr_init:  11;
            uint32_t ulp_cp_mem_addr_size:  11;
            uint32_t ulp_cp_mem_offst_clr:   1;
            uint32_t reserved23:             5;
            uint32_t ulp_cp_clk_fo:          1;          /*ulp协处理器clk强制开启*/
            uint32_t ulp_cp_reset:           1;          /*ulp协处理器clk软件重置*/
            uint32_t ulp_cp_force_start_top: 1;          /*1： ULP协处理器由软件启动*/
            uint32_t ulp_cp_start_top:       1;          /*写入1以启动ULP协处理器*/
        };
        uint32_t val;
    } ulp_cp_ctrl;
    union {
        struct {
            uint32_t cocpu_clk_fo:            1;         /*cocpu clk力*/
            uint32_t cocpu_start_2_reset_dis: 6;         /*从启动cocpu到下拉重置的时间*/
            uint32_t cocpu_start_2_intr_en:   6;         /*从启动cocpu到发出启动中断的时间*/
            uint32_t cocpu_shut:              1;         /*关闭cocpu*/
            uint32_t cocpu_shut_2_clk_dis:    8;         /*从关闭cocpu到禁用clk的时间*/
            uint32_t cocpu_shut_reset_en:     1;         /*重置cocpu*/
            uint32_t cocpu_sel:               1;         /*1： 旧ULP 0：新riscV*/
            uint32_t cocpu_done_force:        1;         /*1： 选择riscv已完成0：选择ulp已完成*/
            uint32_t cocpu_done:              1;         /*riscv用来控制计时器的完成信号。*/
            uint32_t cocpu_sw_int_trigger:    1;         /*触发cocpu寄存器中断*/
            uint32_t reserved27:              5;
        };
        uint32_t val;
    } cocpu_ctrl;
    union {
        struct {
            uint32_t touch_sleep_cycles:16;              /*计时器的睡眠周期*/
            uint32_t touch_meas_num:    16;              /*测量长度（8MHz）*/
        };
        uint32_t val;
    } touch_ctrl1;
    union {
        struct {
            uint32_t reserved0:              2;
            uint32_t touch_drange:           2;          /*TOUCH_DRANGE*/
            uint32_t touch_drefl:            2;          /*TOUCH_DREFL*/
            uint32_t touch_drefh:            2;          /*TOUCH_DREFH*/
            uint32_t touch_xpd_bias:         1;          /*TOUCH_XPD_BIAS*/
            uint32_t touch_refc:             3;          /*TOUCH焊盘0参考帽*/
            uint32_t touch_dbias:            1;          /*1： 使用自偏置0：使用带隙偏置*/
            uint32_t touch_slp_timer_en:     1;          /*触摸计时器启用位*/
            uint32_t touch_start_fsm_en:     1;          /*1： TOUCH_START和TOUCH_XPD由触摸fsm控制*/
            uint32_t touch_start_en:         1;          /*1： 开始触摸fsm*/
            uint32_t touch_start_force:      1;          /*1： 通过软件开始触摸fsm*/
            uint32_t touch_xpd_wait:         8;          /*TOUCH_START和TOUCH_XPD之间的等待周期（8MHz）*/
            uint32_t touch_slp_cyc_div:      2;          /*当触摸板处于活动状态时，睡眠周期可以除以这个数字*/
            uint32_t touch_timer_force_done: 2;          /*强制触摸计时器已完成*/
            uint32_t touch_reset:            1;          /*重置升级触摸*/
            uint32_t touch_clk_fo:           1;          /*触摸时钟强制开启*/
            uint32_t touch_clkgate_en:       1;          /*触摸时钟启用*/
        };
        uint32_t val;
    } touch_ctrl2;
    union {
        struct {
            uint32_t touch_denoise_res:         2;       /*去噪分辨率：12/10/8/4位*/
            uint32_t touch_denoise_en:          1;       /*触摸板0将用于降噪*/
            uint32_t reserved3:                 5;
            uint32_t touch_inactive_connection: 1;       /*非活动触摸板连接到1:gnd 0:HighZ*/
            uint32_t touch_shield_pad_en:       1;       /*触摸板14将用作屏蔽*/
            uint32_t touch_scan_pad_map:       15;       /*触摸扫描模式板启用图*/
            uint32_t touch_bufdrv:              3;       /*touch7缓冲驱动器强度*/
            uint32_t touch_out_ring:            4;       /*选择环垫*/
        };
        uint32_t val;
    } touch_scan_ctrl;
    union {
        struct {
            uint32_t touch_slp_th:         22;           /*睡眠触摸板的阈值*/
            uint32_t reserved22:            4;
            uint32_t touch_slp_approach_en: 1;           /*睡眠垫接近功能启用*/
            uint32_t touch_slp_pad:         5;
        };
        uint32_t val;
    } touch_slp_thres;
    union {
        struct {
            uint32_t reserved0:               23;
            uint32_t touch_slp_channel_clr:    1;        /*清除触摸slp通道*/
            uint32_t touch_approach_meas_time: 8;        /*进场垫总测量时间*/
        };
        uint32_t val;
    } touch_approach;
    union {
        struct {
            uint32_t reserved0:             9;
            uint32_t touch_smooth_lvl:      2;
            uint32_t touch_jitter_step:     4;           /*触摸抖动阶跃*/
            uint32_t config1:               4;
            uint32_t config2:               2;
            uint32_t touch_noise_thres:     2;
            uint32_t config3:               2;
            uint32_t touch_debounce:        3;           /*防抖计数器*/
            uint32_t touch_filter_mode:     3;           /*0:IIR？1： IIR？2： IIR 1/8 3：抖动*/
            uint32_t touch_filter_en:       1;           /*触摸过滤器启用*/
        };
        uint32_t val;
    } touch_filter_ctrl;
    union {
        struct {
            uint32_t usb_vrefh:               2;
            uint32_t usb_vrefl:               2;
            uint32_t usb_vref_override:       1;
            uint32_t usb_pad_pull_override:   1;
            uint32_t usb_dp_pullup:           1;
            uint32_t usb_dp_pulldown:         1;
            uint32_t usb_dm_pullup:           1;
            uint32_t usb_dm_pulldown:         1;
            uint32_t usb_pullup_value:        1;
            uint32_t usb_pad_enable_override: 1;
            uint32_t usb_pad_enable:          1;
            uint32_t usb_txm:                 1;
            uint32_t usb_txp:                 1;
            uint32_t usb_tx_en:               1;
            uint32_t usb_tx_en_override:      1;
            uint32_t usb_reset_disable:       1;
            uint32_t io_mux_reset_disable:    1;
            uint32_t reserved19:             13;
        };
        uint32_t val;
    } usb_conf;
    union {
        struct {
            uint32_t touch_timeout_num:22;
            uint32_t touch_timeout_en:  1;
            uint32_t reserved23:        9;
        };
        uint32_t val;
    } touch_timeout_ctrl;
    union {
        struct {
            uint32_t reject_cause:17;                    /*睡眠拒绝原因*/
            uint32_t reserved17:  15;
        };
        uint32_t val;
    } slp_reject_cause;
    union {
        struct {
            uint32_t force_download_boot: 1;
            uint32_t reserved1:          31;
        };
        uint32_t val;
    } option1;
    union {
        struct {
            uint32_t wakeup_cause:17;                    /*睡眠唤醒原因*/
            uint32_t reserved17:  15;
        };
        uint32_t val;
    } slp_wakeup_cause;
    union {
        struct {
            uint32_t reserved0:              8;
            uint32_t ulp_cp_timer_slp_cycle:24;          /*ULP协处理器计时器的休眠周期*/
        };
        uint32_t val;
    } ulp_cp_timer_1;
    uint32_t reserved_134;
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

