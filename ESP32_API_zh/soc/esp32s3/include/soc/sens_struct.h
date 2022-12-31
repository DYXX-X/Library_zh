/*
 * SPDX文件版权文本：2015-2021浓缩咖啡系统（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */

#ifndef _SOC_SENS_STRUCT_H_
#define _SOC_SENS_STRUCT_H_


#include <stdint.h>
#ifdef __cplusplus
extern "C" {
#endif

typedef volatile struct sens_dev_s {
    union {
        struct {
            uint32_t sar1_clk_div                  :    8;  /*时钟分频器*/
            uint32_t reserved8                     :    10;
            uint32_t sar1_clk_gated                :    1;
            uint32_t sar1_sample_num               :    8;
            uint32_t reserved27                    :    1;
            uint32_t sar1_data_inv                 :    1;  /*反转SAR ADC1数据*/
            uint32_t sar1_int_en                   :    1;  /*启用saradc1发送中断*/
            uint32_t reserved30                    :    2;
        };
        uint32_t val;
    } sar_reader1_ctrl;
    uint32_t sar_reader1_status;
    union {
        struct {
            uint32_t reserved0                     :    24;
            uint32_t force_xpd_amp                 :    2;
            uint32_t amp_rst_fb_force              :    2;
            uint32_t amp_short_ref_force           :    2;
            uint32_t amp_short_ref_gnd_force       :    2;
        };
        uint32_t val;
    } sar_meas1_ctrl1;
    union {
        struct {
            uint32_t meas1_data_sar                :    16;  /*SAR ADC1数据*/
            uint32_t meas1_done_sar                :    1;  /*SAR ADC1转换完成指示*/
            uint32_t meas1_start_sar               :    1;  /*SAR ADC1控制器（RTC中）开始转换*/
            uint32_t meas1_start_force             :    1;  /*1： SAR ADC1控制器（RTC中）由软件启动*/
            uint32_t sar1_en_pad                   :    12;  /*SAR ADC1极板启用位图*/
            uint32_t sar1_en_pad_force             :    1;  /*1： SAR ADC1极板启用位图由软件控制*/
        };
        uint32_t val;
    } sar_meas1_ctrl2;
    union {
        struct {
            uint32_t reserved0                     :    31;
            uint32_t sar1_dig_force                :    1;  /*1： SAR ADC1由DIG ADC1 CTRL控制*/
        };
        uint32_t val;
    } sar_meas1_mux;
    uint32_t sar_atten1;
    union {
        struct {
            uint32_t sar_amp_wait1                 :    16;
            uint32_t sar_amp_wait2                 :    16;
        };
        uint32_t val;
    } sar_amp_ctrl1;
    union {
        struct {
            uint32_t sar1_dac_xpd_fsm_idle         :    1;
            uint32_t xpd_sar_amp_fsm_idle          :    1;
            uint32_t amp_rst_fb_fsm_idle           :    1;
            uint32_t amp_short_ref_fsm_idle        :    1;
            uint32_t amp_short_ref_gnd_fsm_idle    :    1;
            uint32_t xpd_sar_fsm_idle              :    1;
            uint32_t sar_rstb_fsm_idle             :    1;
            uint32_t reserved7                     :    9;
            uint32_t sar_amp_wait3                 :    16;
        };
        uint32_t val;
    } sar_amp_ctrl2;
    union {
        struct {
            uint32_t sar1_dac_xpd_fsm              :    4;
            uint32_t xpd_sar_amp_fsm               :    4;
            uint32_t amp_rst_fb_fsm                :    4;
            uint32_t amp_short_ref_fsm             :    4;
            uint32_t amp_short_ref_gnd_fsm         :    4;
            uint32_t xpd_sar_fsm                   :    4;
            uint32_t sar_rstb_fsm                  :    4;
            uint32_t reserved28                    :    4;
        };
        uint32_t val;
    } sar_amp_ctrl3;
    union {
        struct {
            uint32_t sar2_clk_div                  :    8;  /*时钟分频器*/
            uint32_t reserved8                     :    8;
            uint32_t sar2_wait_arb_cycle           :    2;  /*在sar_done之后等待仲裁稳定*/
            uint32_t sar2_clk_gated                :    1;
            uint32_t sar2_sample_num               :    8;
            uint32_t reserved27                    :    2;
            uint32_t sar2_data_inv                 :    1;  /*反转SAR ADC2数据*/
            uint32_t sar2_int_en                   :    1;  /*启用saradc2发送中断*/
            uint32_t reserved31                    :    1;
        };
        uint32_t val;
    } sar_reader2_ctrl;
    uint32_t sar_reader2_status;
    union {
        struct {
            uint32_t sar2_cntl_state               :    3;  /*saradc2_cntl_fsm公司*/
            uint32_t sar2_pwdet_cal_en             :    1;  /*rtc控制pwdet启用*/
            uint32_t sar2_pkdet_cal_en             :    1;  /*rtc控制pkdet启用*/
            uint32_t sar2_en_test                  :    1;  /*SAR2_EN_TEST*/
            uint32_t sar2_rstb_force               :    2;
            uint32_t sar2_standby_wait             :    8;
            uint32_t sar2_rstb_wait                :    8;
            uint32_t sar2_xpd_wait                 :    8;
        };
        uint32_t val;
    } sar_meas2_ctrl1;
    union {
        struct {
            uint32_t meas2_data_sar                :    16;  /*SAR ADC2数据*/
            uint32_t meas2_done_sar                :    1;  /*SAR ADC2转换完成指示*/
            uint32_t meas2_start_sar               :    1;  /*SAR ADC2控制器（RTC中）开始转换*/
            uint32_t meas2_start_force             :    1;  /*1： SAR ADC2控制器（RTC中）由软件启动*/
            uint32_t sar2_en_pad                   :    12;  /*SAR ADC2极板启用位图*/
            uint32_t sar2_en_pad_force             :    1;  /*1： SAR ADC2极板启用位图由软件控制*/
        };
        uint32_t val;
    } sar_meas2_ctrl2;
    union {
        struct {
            uint32_t reserved0                     :    28;
            uint32_t sar2_pwdet_cct                :    3;  /*SAR2_PWDET_CCT*/
            uint32_t sar2_rtc_force                :    1;  /*在休眠状态下，强制使用rtc控制ADC*/
        };
        uint32_t val;
    } sar_meas2_mux;
    uint32_t sar_atten2;
    union {
        struct {
            uint32_t reserved0                     :    29;
            uint32_t force_xpd_sar                 :    2;
            uint32_t sarclk_en                     :    1;
        };
        uint32_t val;
    } sar_power_xpd_sar;
    union {
        struct {
            uint32_t i2c_slave_addr1               :    11;
            uint32_t i2c_slave_addr0               :    11;
            uint32_t meas_status                   :    8;
            uint32_t reserved30                    :    2;
        };
        uint32_t val;
    } sar_slave_addr1;
    union {
        struct {
            uint32_t i2c_slave_addr3               :    11;
            uint32_t i2c_slave_addr2               :    11;
            uint32_t reserved22                    :    10;
        };
        uint32_t val;
    } sar_slave_addr2;
    union {
        struct {
            uint32_t i2c_slave_addr5               :    11;
            uint32_t i2c_slave_addr4               :    11;
            uint32_t reserved22                    :    10;
        };
        uint32_t val;
    } sar_slave_addr3;
    union {
        struct {
            uint32_t i2c_slave_addr7               :    11;
            uint32_t i2c_slave_addr6               :    11;
            uint32_t reserved22                    :    10;
        };
        uint32_t val;
    } sar_slave_addr4;
    union {
        struct {
            uint32_t tsens_out                     :    8;  /*温度传感器数据输出*/
            uint32_t tsens_ready                   :    1;  /*指示温度传感器输出就绪*/
            uint32_t reserved9                     :    3;
            uint32_t tsens_int_en                  :    1;  /*使温度传感器发出中断*/
            uint32_t tsens_in_inv                  :    1;  /*反转温度传感器数据*/
            uint32_t tsens_clk_div                 :    8;  /*温度传感器时钟分频器*/
            uint32_t tsens_power_up                :    1;  /*温度传感器通电*/
            uint32_t tsens_power_up_force          :    1;  /*1： 卸载和通电由软件控制*/
            uint32_t tsens_dump_out                :    1;  /*温度传感器卸载*/
            uint32_t reserved25                    :    7;
        };
        uint32_t val;
    } sar_tctrl;
    union {
        struct {
            uint32_t tsens_xpd_wait                :    12;
            uint32_t tsens_xpd_force               :    2;
            uint32_t tsens_clk_inv                 :    1;
            uint32_t reserved15                    :    17;
        };
        uint32_t val;
    } sar_tctrl2;
    union {
        struct {
            uint32_t sar_i2c_ctrl                  :    28;  /*I2C控制数据*/
            uint32_t sar_i2c_start                 :    1;  /*启动I2C*/
            uint32_t sar_i2c_start_force           :    1;  /*1： I2C由软件启动*/
            uint32_t reserved30                    :    2;
        };
        uint32_t val;
    } sar_i2c_ctrl;
    union {
        struct {
            uint32_t touch_outen                   :    15;  /*触摸控制器输出启用*/
            uint32_t touch_status_clr              :    1;  /*清除所有触摸激活状态*/
            uint32_t touch_data_sel                :    2;  /*3： 平滑数据2：基线1,0:raw_data*/
            uint32_t touch_denoise_end             :    1;  /*触摸_噪声_音调*/
            uint32_t touch_unit_end                :    1;  /*触摸单元*/
            uint32_t touch_approach_pad2           :    4;  /*指示哪个焊盘是进场焊盘2*/
            uint32_t touch_approach_pad1           :    4;  /*指示哪个焊盘是进场焊盘1*/
            uint32_t touch_approach_pad0           :    4;  /*指示哪个焊盘是进场焊盘0*/
        };
        uint32_t val;
    } sar_touch_conf;
    union {
        struct {
            uint32_t touch_denoise_data            :    22;
            uint32_t reserved22                    :    10;
        };
        uint32_t val;
    } sar_touch_denoise;
    union {
        struct {
            uint32_t thresh                        :    22;  /*触摸板1的手指阈值*/
            uint32_t reserved22                    :    10;
        };
        uint32_t val;
    } touch_thresh[14];
    union {
        struct {
            uint32_t touch_pad_active              :    15;  /*触摸激活状态*/
            uint32_t touch_channel_clr             :    15;  /*清除触摸通道*/
            uint32_t reserved30                    :    1;
            uint32_t touch_meas_done               :    1;
        };
        uint32_t val;
    } sar_touch_chn_st;
    union {
        struct {
            uint32_t touch_denoise_data            :    22;  /*触摸板0的计数器*/
            uint32_t touch_scan_curr               :    4;
            uint32_t reserved26                    :    6;
        };
        uint32_t val;
    } sar_touch_status0;
    union {
        struct {
            uint32_t touch_pad_data               :    22;
            uint32_t reserved22                    :    7;
            uint32_t touch_pad_debounce            :    3;
        };
        uint32_t val;
    } sar_touch_status[14];
    union {
        struct {
            uint32_t touch_slp_data                :    22;
            uint32_t reserved22                    :    7;
            uint32_t touch_slp_debounce            :    3;
        };
        uint32_t val;
    } sar_touch_slp_status;
    union {
        struct {
            uint32_t touch_approach_pad2_cnt       :    8;
            uint32_t touch_approach_pad1_cnt       :    8;
            uint32_t touch_approach_pad0_cnt       :    8;
            uint32_t touch_slp_approach_cnt        :    8;
        };
        uint32_t val;
    } sar_touch_appr_status;
    union {
        struct {
            uint32_t reserved0                     :    25;
            uint32_t dbg_trigger                   :    1;  /*触发器cocpu调试寄存器*/
            uint32_t clk_en_st                     :    1;  /*检查cocpu是否打开clk*/
            uint32_t reset_n                       :    1;  /*检查cocpu是否处于重置状态*/
            uint32_t eoi                           :    1;  /*检查cocpu是否处于中断状态*/
            uint32_t trap                          :    1;  /*检查cocpu是否处于陷阱状态*/
            uint32_t ebreak                        :    1;  /*检查cocpu是否在ebreak中*/
            uint32_t reserved31                    :    1;
        };
        uint32_t val;
    } sar_cocpu_state;
    union {
        struct {
            uint32_t touch_done                    :    1;  /*完成触摸后的int*/
            uint32_t touch_inactive                :    1;  /*来自触摸的int无效*/
            uint32_t touch_active                  :    1;  /*int from touch激活*/
            uint32_t saradc1                       :    1;  /*来自saradc1的int*/
            uint32_t saradc2                       :    1;  /*来自saradc2的int*/
            uint32_t tsens                         :    1;  /*来自tsens的int*/
            uint32_t start                         :    1;  /*int从开始*/
            uint32_t sw                            :    1;  /*来自软件的int*/
            uint32_t swd                           :    1;  /*来自超级看门狗的int*/
            uint32_t touch_timeout                 :    1;
            uint32_t touch_approach_loop_done      :    1;
            uint32_t touch_scan_done               :    1;
            uint32_t reserved12                    :    20;
        };
        uint32_t val;
    } sar_cocpu_int_raw;
    union {
        struct {
            uint32_t touch_done                    :    1;
            uint32_t touch_inactive                :    1;
            uint32_t touch_active                  :    1;
            uint32_t saradc1                       :    1;
            uint32_t saradc2                       :    1;
            uint32_t tsens                         :    1;
            uint32_t start                         :    1;
            uint32_t sw                            :    1;  /*cocpu int启用*/
            uint32_t swd                           :    1;
            uint32_t touch_timeout                 :    1;
            uint32_t touch_approach_loop_done      :    1;
            uint32_t touch_scan_done               :    1;
            uint32_t reserved12                    :    20;
        };
        uint32_t val;
    } sar_cocpu_int_ena;
    union {
        struct {
            uint32_t touch_done                    :    1;
            uint32_t touch_inactive                :    1;
            uint32_t touch_active                  :    1;
            uint32_t saradc1                       :    1;
            uint32_t saradc2                       :    1;
            uint32_t tsens                         :    1;
            uint32_t start                         :    1;
            uint32_t sw                            :    1;  /*cocpu int状态*/
            uint32_t swd                           :    1;
            uint32_t touch_timeout                 :    1;
            uint32_t touch_approach_loop_done      :    1;
            uint32_t touch_scan_done               :    1;
            uint32_t reserved12                    :    20;
        };
        uint32_t val;
    } sar_cocpu_int_st;
    union {
        struct {
            uint32_t touch_done                    :    1;
            uint32_t touch_inactive                :    1;
            uint32_t touch_active                  :    1;
            uint32_t saradc1                       :    1;
            uint32_t saradc2                       :    1;
            uint32_t tsens                         :    1;
            uint32_t start                         :    1;
            uint32_t sw                            :    1;  /*cocpuint清除*/
            uint32_t swd                           :    1;
            uint32_t touch_timeout                 :    1;
            uint32_t touch_approach_loop_done      :    1;
            uint32_t touch_scan_done               :    1;
            uint32_t reserved12                    :    20;
        };
        uint32_t val;
    } sar_cocpu_int_clr;
    union {
        struct {
            uint32_t pc                            :    13;  /*cocpu程序计数器*/
            uint32_t mem_vld                       :    1;  /*cocpu mem有效输出*/
            uint32_t mem_rdy                       :    1;  /*cocpu内存就绪输入*/
            uint32_t mem_wen                       :    4;  /*cocpu mem写使能输出*/
            uint32_t mem_addr                      :    13;  /*cocpu内存地址输出*/
        };
        uint32_t val;
    } sar_cocpu_debug;
    union {
        struct {
            uint32_t reserved0                     :    28;
            uint32_t xpd_hall                      :    1;  /*接通霍尔传感器电源并连接到VP和VN*/
            uint32_t xpd_hall_force                :    1;  /*1： XPD HALL由SW控制。0:XPD HALL由ULP协处理器中的FSM控制*/
            uint32_t hall_phase                    :    1;  /*霍尔传感器反相*/
            uint32_t hall_phase_force              :    1;  /*1： HALL PHASE由SW 0控制：HALL PHASE由ULP协处理器中的FSM控制*/
        };
        uint32_t val;
    } sar_hall_ctrl;
    uint32_t sar_nouse;
    union {
        struct {
            uint32_t reserved0                     :    27;
            uint32_t rtc_i2c_clk_en                :    1;
            uint32_t reserved28                    :    1;
            uint32_t tsens_clk_en                  :    1;
            uint32_t saradc_clk_en                 :    1;
            uint32_t iomux_clk_en                  :    1;
        };
        uint32_t val;
    } sar_peri_clk_gate_conf;
    union {
        struct {
            uint32_t reserved0                     :    25;
            uint32_t reset                         :    1;
            uint32_t reserved26                    :    1;
            uint32_t rtc_i2c_reset                 :    1;
            uint32_t reserved28                    :    1;
            uint32_t tsens_reset                   :    1;
            uint32_t saradc_reset                  :    1;
            uint32_t reserved31                    :    1;
        };
        uint32_t val;
    } sar_peri_reset_conf;
    union {
        struct {
            uint32_t touch_done_w1ts               :    1;
            uint32_t touch_inactive_w1ts           :    1;
            uint32_t touch_active_w1ts             :    1;
            uint32_t saradc1_w1ts                  :    1;
            uint32_t saradc2_w1ts                  :    1;
            uint32_t tsens_w1ts                    :    1;
            uint32_t start_w1ts                    :    1;
            uint32_t sw_w1ts                       :    1;
            uint32_t swd_w1ts                      :    1;
            uint32_t touch_timeout_w1ts            :    1;
            uint32_t touch_approach_loop_done_w1ts :    1;
            uint32_t touch_scan_done_w1ts          :    1;
            uint32_t reserved12                    :    20;
        };
        uint32_t val;
    } sar_cocpu_int_ena_w1ts;
    union {
        struct {
            uint32_t touch_done_w1tc               :    1;
            uint32_t touch_inactive_w1tc           :    1;
            uint32_t touch_active_w1tc             :    1;
            uint32_t saradc1_w1tc                  :    1;
            uint32_t saradc2_w1tc                  :    1;
            uint32_t tsens_w1tc                    :    1;
            uint32_t start_w1tc                    :    1;
            uint32_t sw_w1tc                       :    1;
            uint32_t swd_w1tc                      :    1;
            uint32_t touch_timeout_w1tc            :    1;
            uint32_t touch_approach_loop_done_w1tc :    1;
            uint32_t touch_scan_done_w1tc          :    1;
            uint32_t reserved12                    :    20;
        };
        uint32_t val;
    } sar_cocpu_int_ena_w1tc;
    union {
        struct {
            uint32_t debug_bit_sel                 :    5;
            uint32_t reserved5                     :    27;
        };
        uint32_t val;
    } sar_debug_conf;
    uint32_t reserved_118;
    uint32_t reserved_11c;
    uint32_t reserved_120;
    uint32_t reserved_124;
    uint32_t reserved_128;
    uint32_t reserved_12c;
    uint32_t reserved_130;
    uint32_t reserved_134;
    uint32_t reserved_138;
    uint32_t reserved_13c;
    uint32_t reserved_140;
    uint32_t reserved_144;
    uint32_t reserved_148;
    uint32_t reserved_14c;
    uint32_t reserved_150;
    uint32_t reserved_154;
    uint32_t reserved_158;
    uint32_t reserved_15c;
    uint32_t reserved_160;
    uint32_t reserved_164;
    uint32_t reserved_168;
    uint32_t reserved_16c;
    uint32_t reserved_170;
    uint32_t reserved_174;
    uint32_t reserved_178;
    uint32_t reserved_17c;
    uint32_t reserved_180;
    uint32_t reserved_184;
    uint32_t reserved_188;
    uint32_t reserved_18c;
    uint32_t reserved_190;
    uint32_t reserved_194;
    uint32_t reserved_198;
    uint32_t reserved_19c;
    uint32_t reserved_1a0;
    uint32_t reserved_1a4;
    uint32_t reserved_1a8;
    uint32_t reserved_1ac;
    uint32_t reserved_1b0;
    uint32_t reserved_1b4;
    uint32_t reserved_1b8;
    uint32_t reserved_1bc;
    uint32_t reserved_1c0;
    uint32_t reserved_1c4;
    uint32_t reserved_1c8;
    uint32_t reserved_1cc;
    uint32_t reserved_1d0;
    uint32_t reserved_1d4;
    uint32_t reserved_1d8;
    uint32_t reserved_1dc;
    uint32_t reserved_1e0;
    uint32_t reserved_1e4;
    uint32_t reserved_1e8;
    uint32_t reserved_1ec;
    uint32_t reserved_1f0;
    uint32_t reserved_1f4;
    uint32_t reserved_1f8;
    union {
        struct {
            uint32_t sar_date                      :    28;
            uint32_t reserved28                    :    4;
        };
        uint32_t val;
    } sardate;
} sens_dev_t;
extern sens_dev_t SENS;
#ifdef __cplusplus
}
#endif



#endif /*_SOC_SENS_STRUCT_H_ */

