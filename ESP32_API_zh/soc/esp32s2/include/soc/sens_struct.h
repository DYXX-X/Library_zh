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
#ifndef _SOC_SENS_STRUCT_H_
#define _SOC_SENS_STRUCT_H_
#ifdef __cplusplus
extern "C" {
#endif

typedef volatile struct sens_dev_s {
    union {
        struct {
            uint32_t sar1_clk_div:    8;                    /*时钟分频器*/
            uint32_t reserved8:      10;
            uint32_t sar1_clk_gated:  1;
            uint32_t sar1_sample_num: 8;
            uint32_t reserved27:      1;
            uint32_t sar1_data_inv:   1;                    /*反转SAR ADC1数据*/
            uint32_t sar1_int_en:     1;                    /*启用saradc1发送中断*/
            uint32_t reserved30:      2;
        };
        uint32_t val;
    } sar_reader1_ctrl;
    uint32_t sar_reader1_status;                            /**/
    union {
        struct {
            uint32_t reserved0:              22;
            uint32_t rtc_saradc_reset:        1;
            uint32_t rtc_saradc_clkgate_en:   1;
            uint32_t force_xpd_amp:           2;
            uint32_t amp_rst_fb_force:        2;
            uint32_t amp_short_ref_force:     2;
            uint32_t amp_short_ref_gnd_force: 2;
        };
        uint32_t val;
    } sar_meas1_ctrl1;
    union {
        struct {
            uint32_t meas1_data_sar:   16;                  /*SAR ADC1数据*/
            uint32_t meas1_done_sar:    1;                  /*SAR ADC1转换完成指示*/
            uint32_t meas1_start_sar:   1;                  /*SAR ADC1控制器（RTC中）开始转换*/
            uint32_t meas1_start_force: 1;                  /*1： SAR ADC1控制器（RTC中）由软件启动*/
            uint32_t sar1_en_pad:      12;                  /*SAR ADC1极板启用位图*/
            uint32_t sar1_en_pad_force: 1;                  /*1： SAR ADC1极板启用位图由软件控制*/
        };
        uint32_t val;
    } sar_meas1_ctrl2;
    union {
        struct {
            uint32_t reserved0:     31;
            uint32_t sar1_dig_force: 1;                     /*1： SAR ADC1由DIG ADC1 CTRL控制*/
        };
        uint32_t val;
    } sar_meas1_mux;
    uint32_t sar_atten1;                                    /*每个焊盘的2位衰减*/
    union {
        struct {
            uint32_t sar_amp_wait1:16;
            uint32_t sar_amp_wait2:16;
        };
        uint32_t val;
    } sar_amp_ctrl1;
    union {
        struct {
            uint32_t sar1_dac_xpd_fsm_idle:      1;
            uint32_t xpd_sar_amp_fsm_idle:       1;
            uint32_t amp_rst_fb_fsm_idle:        1;
            uint32_t amp_short_ref_fsm_idle:     1;
            uint32_t amp_short_ref_gnd_fsm_idle: 1;
            uint32_t xpd_sar_fsm_idle:           1;
            uint32_t sar_rstb_fsm_idle:          1;
            uint32_t reserved7:                  9;
            uint32_t sar_amp_wait3:             16;
        };
        uint32_t val;
    } sar_amp_ctrl2;
    union {
        struct {
            uint32_t sar1_dac_xpd_fsm:      4;
            uint32_t xpd_sar_amp_fsm:       4;
            uint32_t amp_rst_fb_fsm:        4;
            uint32_t amp_short_ref_fsm:     4;
            uint32_t amp_short_ref_gnd_fsm: 4;
            uint32_t xpd_sar_fsm:           4;
            uint32_t sar_rstb_fsm:          4;
            uint32_t reserved28:            4;
        };
        uint32_t val;
    } sar_amp_ctrl3;
    union {
        struct {
            uint32_t sar2_clk_div:        8;                /*时钟分频器*/
            uint32_t reserved8:           8;
            uint32_t sar2_wait_arb_cycle: 2;                /*在sar_done之后等待仲裁稳定*/
            uint32_t sar2_clk_gated:      1;
            uint32_t sar2_sample_num:     8;
            uint32_t reserved27:          2;
            uint32_t sar2_data_inv:       1;                /*反转SAR ADC2数据*/
            uint32_t sar2_int_en:         1;                /*启用saradc2发送中断*/
            uint32_t reserved31:          1;
        };
        uint32_t val;
    } sar_reader2_ctrl;
    uint32_t sar_reader2_status;                            /**/
    union {
        struct {
            uint32_t sar2_cntl_state:   3;                  /*saradc2_cntl_fsm公司*/
            uint32_t sar2_pwdet_cal_en: 1;                  /*rtc控制pwdet启用*/
            uint32_t sar2_pkdet_cal_en: 1;                  /*rtc控制pkdet启用*/
            uint32_t sar2_en_test:      1;                  /*SAR2_EN_TEST*/
            uint32_t sar2_rstb_force:   2;
            uint32_t sar2_standby_wait: 8;
            uint32_t sar2_rstb_wait:    8;
            uint32_t sar2_xpd_wait:     8;
        };
        uint32_t val;
    } sar_meas2_ctrl1;
    union {
        struct {
            uint32_t meas2_data_sar:   16;                  /*SAR ADC2数据*/
            uint32_t meas2_done_sar:    1;                  /*SAR ADC2转换完成指示*/
            uint32_t meas2_start_sar:   1;                  /*SAR ADC2控制器（RTC中）开始转换*/
            uint32_t meas2_start_force: 1;                  /*1： SAR ADC2控制器（RTC中）由软件启动*/
            uint32_t sar2_en_pad:      12;                  /*SAR ADC2极板启用位图*/
            uint32_t sar2_en_pad_force: 1;                  /*1： SAR ADC2极板启用位图由软件控制*/
        };
        uint32_t val;
    } sar_meas2_ctrl2;
    union {
        struct {
            uint32_t reserved0:     28;
            uint32_t sar2_pwdet_cct: 3;                     /*SAR2_PWDET_CCT*/
            uint32_t sar2_rtc_force: 1;                     /*在睡眠中强制使用rtc控制ADC*/
        };
        uint32_t val;
    } sar_meas2_mux;
    uint32_t sar_atten2;                                    /*每个焊盘的2位衰减*/
    union {
        struct {
            uint32_t reserved0:    29;
            uint32_t force_xpd_sar: 2;
            uint32_t sarclk_en:     1;
        };
        uint32_t val;
    } sar_power_xpd_sar;
    union {
        struct {
            uint32_t i2c_slave_addr1:   11;
            uint32_t i2c_slave_addr0:   11;
            uint32_t meas_status:        8;
            uint32_t reserved30:         2;
        };
        uint32_t val;
    } sar_slave_addr1;
    union {
        struct {
            uint32_t i2c_slave_addr3:11;
            uint32_t i2c_slave_addr2:11;
            uint32_t reserved22:     10;
        };
        uint32_t val;
    } sar_slave_addr2;
    union {
        struct {
            uint32_t i2c_slave_addr5:11;
            uint32_t i2c_slave_addr4:11;
            uint32_t reserved22:     10;
        };
        uint32_t val;
    } sar_slave_addr3;
    union {
        struct {
            uint32_t i2c_slave_addr7:11;
            uint32_t i2c_slave_addr6:11;
            uint32_t reserved22:     10;
        };
        uint32_t val;
    } sar_slave_addr4;
    union {
        struct {
            uint32_t tsens_out:            8;               /*温度传感器数据输出*/
            uint32_t tsens_ready:          1;               /*指示温度传感器输出就绪*/
            uint32_t reserved9:            3;
            uint32_t tsens_int_en:         1;               /*使温度传感器发出中断*/
            uint32_t tsens_in_inv:         1;               /*反转温度传感器数据*/
            uint32_t tsens_clk_div:        8;               /*温度传感器时钟分频器*/
            uint32_t tsens_power_up:       1;               /*温度传感器通电*/
            uint32_t tsens_power_up_force: 1;               /*1： 卸载和通电由软件控制*/
            uint32_t tsens_dump_out:       1;               /*温度传感器卸载*/
            uint32_t reserved25:           7;
        };
        uint32_t val;
    } sar_tctrl;
    union {
        struct {
            uint32_t tsens_xpd_wait:  12;
            uint32_t tsens_xpd_force:  2;
            uint32_t tsens_clk_inv:    1;
            uint32_t tsens_clkgate_en: 1;                   /*温度传感器时钟启用*/
            uint32_t tsens_reset:      1;                   /*温度传感器复位*/
            uint32_t reserved17:      15;
        };
        uint32_t val;
    } sar_tctrl2;
    union {
        struct {
            uint32_t sar_i2c_ctrl:       28;                /*I2C控制数据*/
            uint32_t sar_i2c_start:       1;                /*启动I2C*/
            uint32_t sar_i2c_start_force: 1;                /*1： I2C由软件启动*/
            uint32_t reserved30:          2;
        };
        uint32_t val;
    } sar_i2c_ctrl;
    union {
        struct {
            uint32_t touch_outen:        15;                /*触摸控制器输出启用*/
            uint32_t touch_status_clr:    1;                /*清除所有触摸激活状态*/
            uint32_t touch_data_sel:      2;                /*3： 平滑数据2:基准1 0:raw_data*/
            uint32_t touch_denoise_end:   1;                /*触摸_噪声_音调*/
            uint32_t touch_unit_end:      1;                /*触摸单元*/
            uint32_t touch_approach_pad2: 4;                /*指示哪个焊盘是进场焊盘2*/
            uint32_t touch_approach_pad1: 4;                /*指示哪个焊盘是进场焊盘1*/
            uint32_t touch_approach_pad0: 4;                /*指示哪个焊盘是进场焊盘0*/
        };
        uint32_t val;
    } sar_touch_conf;
    union {
        struct {
            uint32_t thresh:       22;                      /*触摸板1的手指阈值*/
            uint32_t reserved22:   10;
        };
        uint32_t val;
    } touch_thresh[14];
    uint32_t reserved_98;
    uint32_t reserved_9c;
    uint32_t reserved_a0;
    uint32_t reserved_a4;
    uint32_t reserved_a8;
    uint32_t reserved_ac;
    uint32_t reserved_b0;
    uint32_t reserved_b4;
    uint32_t reserved_b8;
    uint32_t reserved_bc;
    uint32_t reserved_c0;
    uint32_t reserved_c4;
    uint32_t reserved_c8;
    uint32_t reserved_cc;
    uint32_t reserved_d0;
    union {
        struct {
            uint32_t touch_pad_active: 15;                  /*触摸激活状态*/
            uint32_t touch_channel_clr:15;                  /*清除触摸通道*/
            uint32_t reserved30:        1;
            uint32_t touch_meas_done:   1;
        };
        uint32_t val;
    } sar_touch_chn_st;
    union {
        struct {
            uint32_t touch_denoise_data:22;                 /*触摸板0的计数器*/
            uint32_t touch_scan_curr:    4;
            uint32_t reserved26:         6;
        };
        uint32_t val;
    } sar_touch_status0;
    union {
        struct {
            uint32_t touch_pad_data: 22;
            uint32_t reserved22:          7;
            uint32_t touch_pad_debounce:  3;
        };
        uint32_t val;
    } sar_touch_status[14];
    union {
        struct {
            uint32_t touch_slp_data:    22;
            uint32_t reserved22:         7;
            uint32_t touch_slp_debounce: 3;
        };
        uint32_t val;
    } sar_touch_slp_status;
    union {
        struct {
            uint32_t touch_approach_pad2_cnt: 8;
            uint32_t touch_approach_pad1_cnt: 8;
            uint32_t touch_approach_pad0_cnt: 8;
            uint32_t touch_slp_approach_cnt:  8;
        };
        uint32_t val;
    } sar_touch_appr_status;
    union {
        struct {
            uint32_t sw_fstep:          16;                 /*连续波发生器的频率阶跃*/
            uint32_t sw_tone_en:         1;                 /*1： 启用CW发生器*/
            uint32_t debug_bit_sel:      5;
            uint32_t dac_dig_force:      1;                 /*1： DAC1和DAC2使用DMA*/
            uint32_t dac_clk_force_low:  1;                 /*1： 强制PDAC_CLK为低*/
            uint32_t dac_clk_force_high: 1;                 /*1： 强制PDAC_CLK为高*/
            uint32_t dac_clk_inv:        1;                 /*1： 反转PDAC_CLK*/
            uint32_t dac_reset:          1;
            uint32_t dac_clkgate_en:     1;
            uint32_t reserved28:         4;
        };
        uint32_t val;
    } sar_dac_ctrl1;
    union {
        struct {
            uint32_t dac_dc1:    8;                         /*DAC1 CW发电机的直流偏移*/
            uint32_t dac_dc2:    8;                         /*DAC2 CW发电机的直流偏移*/
            uint32_t dac_scale1: 2;                         /*00：无刻度*/
            uint32_t dac_scale2: 2;                         /*00：无刻度*/
            uint32_t dac_inv1:   2;                         /*00：不反转任何位*/
            uint32_t dac_inv2:   2;                         /*00：不反转任何位*/
            uint32_t dac_cw_en1: 1;                         /*1： 选择CW发生器作为PDAC1_DAC[7:0]的电源*/
            uint32_t dac_cw_en2: 1;                         /*1： 选择CW发生器作为PDAC2_DAC[7:0]的电源*/
            uint32_t reserved26: 6;
        };
        uint32_t val;
    } sar_dac_ctrl2;
    union {
        struct {
            uint32_t reserved0:        25;
            uint32_t dbg_trigger:       1;                  /*触发器cocpu调试寄存器*/
            uint32_t clk_en:            1;                  /*检查cocpu是否打开clk*/
            uint32_t reset_n:           1;                  /*检查cocpu是否处于重置状态*/
            uint32_t eoi:               1;                  /*检查cocpu是否处于中断状态*/
            uint32_t trap:              1;                  /*检查cocpu是否处于陷阱状态*/
            uint32_t ebreak:            1;                  /*检查cocpu是否在ebreak中*/
            uint32_t reserved31:        1;
        };
        uint32_t val;
    } sar_cocpu_state;
    union {
        struct {
            uint32_t touch_done:                   1;       /*完成触摸后的int*/
            uint32_t touch_inactive:               1;       /*来自触摸的int无效*/
            uint32_t touch_active:                 1;       /*int from touch激活*/
            uint32_t saradc1:                      1;       /*来自saradc1的int*/
            uint32_t saradc2:                      1;       /*来自saradc2的int*/
            uint32_t tsens:                        1;       /*来自tsens的int*/
            uint32_t start:                        1;       /*int从开始*/
            uint32_t sw:                           1;       /*来自软件的int*/
            uint32_t swd:                          1;       /*来自超级看门狗的int*/
            uint32_t reserved9:                   23;
        };
        uint32_t val;
    } sar_cocpu_int_raw;
    union {
        struct {
            uint32_t touch_done:                   1;
            uint32_t touch_inactive:               1;
            uint32_t touch_active:                 1;
            uint32_t saradc1:                      1;
            uint32_t saradc2:                      1;
            uint32_t tsens:                        1;
            uint32_t start:                        1;
            uint32_t sw:                           1;       /*cocpu int启用*/
            uint32_t swd:                          1;
            uint32_t reserved9:                   23;
        };
        uint32_t val;
    } sar_cocpu_int_ena;
    union {
        struct {
            uint32_t touch_done:                  1;
            uint32_t touch_inactive:              1;
            uint32_t touch_active:                1;
            uint32_t saradc1:                     1;
            uint32_t saradc2:                     1;
            uint32_t tsens:                       1;
            uint32_t start:                       1;
            uint32_t sw:                          1;        /*cocpu int状态*/
            uint32_t swd:                         1;
            uint32_t reserved9:                  23;
        };
        uint32_t val;
    } sar_cocpu_int_st;
    union {
        struct {
            uint32_t touch_done:                   1;
            uint32_t touch_inactive:               1;
            uint32_t touch_active:                 1;
            uint32_t saradc1:                      1;
            uint32_t saradc2:                      1;
            uint32_t tsens:                        1;
            uint32_t start:                        1;
            uint32_t sw:                           1;       /*cocpuint清除*/
            uint32_t swd:                          1;
            uint32_t reserved9:                   23;
        };
        uint32_t val;
    } sar_cocpu_int_clr;
    union {
        struct {
            uint32_t pc:            13;                     /*cocpu程序计数器*/
            uint32_t mem_vld:        1;                     /*cocpu mem有效输出*/
            uint32_t mem_rdy:        1;                     /*cocpu内存就绪输入*/
            uint32_t mem_wen:        4;                     /*cocpu mem写使能输出*/
            uint32_t mem_addr:      13;                     /*cocpu内存地址输出*/
        };
        uint32_t val;
    } sar_cocpu_debug;
    union {
        struct {
            uint32_t reserved0:       28;
            uint32_t xpd_hall:         1;                   /*接通霍尔传感器电源并连接到VP和VN*/
            uint32_t xpd_hall_force:   1;                   /*1： XPD HALL由SW控制。0:XPD HALL由ULP协处理器中的FSM控制*/
            uint32_t hall_phase:       1;                   /*霍尔传感器反相*/
            uint32_t hall_phase_force: 1;                   /*1： HALL PHASE由SW 0控制：HALL PHASE由ULP协处理器中的FSM控制*/
        };
        uint32_t val;
    } sar_hall_ctrl;
    uint32_t sar_nouse;                                     /**/
    union {
        struct {
            uint32_t reserved0:        30;
            uint32_t iomux_reset:       1;
            uint32_t iomux_clk_gate_en: 1;
        };
        uint32_t val;
    } sar_io_mux_conf;
    union {
        struct {
            uint32_t sar_date:  28;
            uint32_t reserved28: 4;
        };
        uint32_t val;
    } sardate;
} sens_dev_t;
extern sens_dev_t SENS;
#ifdef __cplusplus
}
#endif

#endif  /* _SOC_SENS_STRUCT_H_ */

