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
#ifndef _SOC_LEDC_STRUCT_H_
#define _SOC_LEDC_STRUCT_H_
#ifdef __cplusplus
extern "C" {
#endif

typedef volatile struct ledc_dev_s {
    struct {
        struct {
            union {
                struct {
                    uint32_t timer_sel:  2;              /*有四个高速定时器，两个位用于选择其中一个用于高速信道。2’b00：选择hstimer0。2’b01：选择hstimer1。2’b10：选择hs timer2。2’b11：选择hs Timer3。*/
                    uint32_t sig_out_en: 1;              /*这是高速通道的输出启用控制位*/
                    uint32_t idle_lv:    1;              /*该位用于控制高速通道关闭时的输出值。*/
                    uint32_t low_speed_update: 1;        /*此位仅适用于低速计时器通道，保留用于高速计时器*/
                    uint32_t ovf_num:   10;
                    uint32_t ovf_cnt_en: 1;
                    uint32_t ovf_cnt_rst: 1;
                    uint32_t ovf_cnt_rst_st: 1;
                    uint32_t reserved18: 14;
                };
                uint32_t val;
            } conf0;
            union {
                struct {
                    uint32_t hpoint:      14;
                    uint32_t reserved14:  18;
                };
                uint32_t val;
            } hpoint;
            union {
                struct {
                    uint32_t duty:      19;
                    uint32_t reserved19:13;
                };
                uint32_t val;
            } duty;
            union {
                struct {
                    uint32_t duty_scale:      10;
                    uint32_t duty_cycle:      10;
                    uint32_t duty_num:        10;
                    uint32_t duty_inc:         1;
                    uint32_t duty_start:       1;
                };
                uint32_t val;
            } conf1;
            union {
                struct {
                    uint32_t duty_read: 19;
                    uint32_t reserved19:13;
                };
                uint32_t val;
            } duty_rd;
        } channel[8];
    } channel_group[1];  /* 单通道组，仅低速模式*/
    struct {
        struct {
            union {
                struct {
                    uint32_t duty_resolution:   4;
                    uint32_t clock_divider:     18;
                    uint32_t pause:             1;
                    uint32_t rst:               1;
                    uint32_t tick_sel:          1;
                    uint32_t low_speed_update:  1;
                    uint32_t reserved26:        6;
                };
                uint32_t val;
            } conf;
            union {
                struct {
                    uint32_t timer_cnt:   14;
                    uint32_t reserved14:  18;
                };
                uint32_t val;
            } value;
        } timer[4];
    } timer_group[1];  /* 单通道组，仅低速模式*/
    union {
        struct {
            uint32_t lstimer0_ovf:                1;
            uint32_t lstimer1_ovf:                1;
            uint32_t lstimer2_ovf:                1;
            uint32_t lstimer3_ovf:                1;
            uint32_t duty_chng_end_lsch0:         1;
            uint32_t duty_chng_end_lsch1:         1;
            uint32_t duty_chng_end_lsch2:         1;
            uint32_t duty_chng_end_lsch3:         1;
            uint32_t duty_chng_end_lsch4:         1;
            uint32_t duty_chng_end_lsch5:         1;
            uint32_t duty_chng_end_lsch6:         1;
            uint32_t duty_chng_end_lsch7:         1;
            uint32_t ovf_cnt_lsch0:               1;
            uint32_t ovf_cnt_lsch1:               1;
            uint32_t ovf_cnt_lsch2:               1;
            uint32_t ovf_cnt_lsch3:               1;
            uint32_t ovf_cnt_lsch4:               1;
            uint32_t ovf_cnt_lsch5:               1;
            uint32_t ovf_cnt_lsch6:               1;
            uint32_t ovf_cnt_lsch7:               1;
            uint32_t reserved20:                 12;
        };
        uint32_t val;
    } int_raw;
    union {
        struct {
            uint32_t lstimer0_ovf:               1;
            uint32_t lstimer1_ovf:               1;
            uint32_t lstimer2_ovf:               1;
            uint32_t lstimer3_ovf:               1;
            uint32_t duty_chng_end_lsch0:        1;
            uint32_t duty_chng_end_lsch1:        1;
            uint32_t duty_chng_end_lsch2:        1;
            uint32_t duty_chng_end_lsch3:        1;
            uint32_t duty_chng_end_lsch4:        1;
            uint32_t duty_chng_end_lsch5:        1;
            uint32_t duty_chng_end_lsch6:        1;
            uint32_t duty_chng_end_lsch7:        1;
            uint32_t ovf_cnt_lsch0:              1;
            uint32_t ovf_cnt_lsch1:              1;
            uint32_t ovf_cnt_lsch2:              1;
            uint32_t ovf_cnt_lsch3:              1;
            uint32_t ovf_cnt_lsch4:              1;
            uint32_t ovf_cnt_lsch5:              1;
            uint32_t ovf_cnt_lsch6:              1;
            uint32_t ovf_cnt_lsch7:              1;
            uint32_t reserved20:                12;
        };
        uint32_t val;
    } int_st;
    union {
        struct {
            uint32_t lstimer0_ovf:                1;
            uint32_t lstimer1_ovf:                1;
            uint32_t lstimer2_ovf:                1;
            uint32_t lstimer3_ovf:                1;
            uint32_t duty_chng_end_lsch0:         1;
            uint32_t duty_chng_end_lsch1:         1;
            uint32_t duty_chng_end_lsch2:         1;
            uint32_t duty_chng_end_lsch3:         1;
            uint32_t duty_chng_end_lsch4:         1;
            uint32_t duty_chng_end_lsch5:         1;
            uint32_t duty_chng_end_lsch6:         1;
            uint32_t duty_chng_end_lsch7:         1;
            uint32_t ovf_cnt_lsch0:               1;
            uint32_t ovf_cnt_lsch1:               1;
            uint32_t ovf_cnt_lsch2:               1;
            uint32_t ovf_cnt_lsch3:               1;
            uint32_t ovf_cnt_lsch4:               1;
            uint32_t ovf_cnt_lsch5:               1;
            uint32_t ovf_cnt_lsch6:               1;
            uint32_t ovf_cnt_lsch7:               1;
            uint32_t reserved20:                 12;
        };
        uint32_t val;
    } int_ena;
    union {
        struct {
            uint32_t lstimer0_ovf:                1;
            uint32_t lstimer1_ovf:                1;
            uint32_t lstimer2_ovf:                1;
            uint32_t lstimer3_ovf:                1;
            uint32_t duty_chng_end_lsch0:         1;
            uint32_t duty_chng_end_lsch1:         1;
            uint32_t duty_chng_end_lsch2:         1;
            uint32_t duty_chng_end_lsch3:         1;
            uint32_t duty_chng_end_lsch4:         1;
            uint32_t duty_chng_end_lsch5:         1;
            uint32_t duty_chng_end_lsch6:         1;
            uint32_t duty_chng_end_lsch7:         1;
            uint32_t ovf_cnt_lsch0:               1;
            uint32_t ovf_cnt_lsch1:               1;
            uint32_t ovf_cnt_lsch2:               1;
            uint32_t ovf_cnt_lsch3:               1;
            uint32_t ovf_cnt_lsch4:               1;
            uint32_t ovf_cnt_lsch5:               1;
            uint32_t ovf_cnt_lsch6:               1;
            uint32_t ovf_cnt_lsch7:               1;
            uint32_t reserved20:                 12;
        };
        uint32_t val;
    } int_clr;
    union {
        struct {
            uint32_t apb_clk_sel: 2; // 0：无效；1： 80MHz APB时钟；2： 8MHz RTC时钟；3： XTAL时钟
            uint32_t reserved2:  29;
            uint32_t clk_en:      1; /*该位是时钟门控控制信号。当软件配置LED_ PWM内部寄存器时。*/
        };
        uint32_t val;
    } conf;
    uint32_t reserved_d4;
    uint32_t reserved_d8;
    uint32_t reserved_dc;
    uint32_t reserved_e0;
    uint32_t reserved_e4;
    uint32_t reserved_e8;
    uint32_t reserved_ec;
    uint32_t reserved_f0;
    uint32_t reserved_f4;
    uint32_t reserved_f8;
    uint32_t date;                                     /**/
} ledc_dev_t;
extern ledc_dev_t LEDC;
#ifdef __cplusplus
}
#endif

#endif  /* _SOC_LEDC_STRUCT_H_ */

