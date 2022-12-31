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
#ifndef _SOC_LEDC_STRUCT_H_
#define _SOC_LEDC_STRUCT_H_

#include <stdint.h>

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
                    uint32_t reserved4: 26;
                    uint32_t clk_en:     1;              /*该位是时钟门控控制信号。当软件配置LED_ PWM内部寄存器时。*/
                };
                uint32_t val;
            } conf0;
            union {
                struct {
                    uint32_t hpoint:     20;             /*当高速通道选择的htimerx（x=[03]）达到reg_hpoint_hsch0[19:0]时，输出值变为高*/
                    uint32_t reserved20: 12;
                };
                uint32_t val;
            } hpoint;
            union {
                struct {
                    uint32_t duty:      25;              /*该寄存器用于控制输出占空比。当高速通道选择的hstimerx（x=[03]）达到reg_lpoint_hsch0时，输出信号变为低。reg_lpoint_hsch0=（reg_hpoint_hsch0[19:0]+reg_duty_hsch0[24:4]）（1）reg_lpoint_hsch0=*/
                    uint32_t reserved25: 7;
                };
                uint32_t val;
            } duty;
            union {
                struct {
                    uint32_t duty_scale:10;              /*该寄存器控制高速通道的增加或减少步长。*/
                    uint32_t duty_cycle:10;              /*该寄存器用于在高速通道的每个reg_duty_cycle_hsch0周期增加或减少占空比。*/
                    uint32_t duty_num:  10;              /*该寄存器用于控制高速通道的增加或减少次数。*/
                    uint32_t duty_inc:   1;              /*该寄存器用于增加输出信号的占空比或降低高速通道的输出信号的负载。*/
                    uint32_t duty_start: 1;              /*当已配置reg_duty_num_hsch0 reg_duty-cycle_hsch0和reg_duty_scale_hsch0时。这些寄存器在设置regdutystarthsch0之前不会生效。这个位会被硬件自动清除。*/
                };
                uint32_t val;
            } conf1;
            union {
                struct {
                    uint32_t duty_read: 25;              /*该寄存器表示高速通道输出信号的当前占空比。*/
                    uint32_t reserved25: 7;
                };
                uint32_t val;
            } duty_rd;
        } channel[8];
    } channel_group[2];                                /*两个信道组：0：高速信道；1： 低速通道*/
    struct {
        struct {
            union {
                struct {
                    uint32_t duty_resolution:   5;     /*该寄存器通过定义定时器计数器的比特宽度来控制PWN占空比的分辨率。计数器的最大位宽为20。*/
                    uint32_t clock_divider:    18;     /*该寄存器用于在计时器入口配置时钟分频器。最低有效的八位代表小数部分。*/
                    uint32_t pause:             1;     /*此位用于暂停高速计时器中的计数器*/
                    uint32_t rst:               1;     /*该位用于重置高速计时器，重置后计数器将为0。*/
                    uint32_t tick_sel:          1;     /*该位用于为高速计时器选择apb_clk或ref_tick。1’b1：apb_clk 0：参考标记*/
                    uint32_t low_speed_update:  1;     /*此位仅适用于低速计时器通道，保留用于高速计时器*/
                    uint32_t reserved26:        5;
                };
                uint32_t val;
            } conf;
            union {
                struct {
                    uint32_t timer_cnt:  20;               /*软件可以读取该寄存器以获得高速计时器中的当前计数器值*/
                    uint32_t reserved20: 12;
                };
                uint32_t val;
            } value;
        } timer[4];
    } timer_group[2];                                    /*两个信道组：0：高速信道；1： 低速通道*/
    union {
        struct {
            uint32_t hstimer0_ovf:        1;           /*高速通道0计数器溢出的中断原始位。*/
            uint32_t hstimer1_ovf:        1;           /*高速通道1计数器溢出的中断原始位。*/
            uint32_t hstimer2_ovf:        1;           /*高速通道2计数器溢出的中断原始位。*/
            uint32_t hstimer3_ovf:        1;           /*高速通道3计数器溢出的中断原始位。*/
            uint32_t lstimer0_ovf:        1;           /*低速通道0计数器溢出的中断原始位。*/
            uint32_t lstimer1_ovf:        1;           /*低速通道1计数器溢出的中断原始位。*/
            uint32_t lstimer2_ovf:        1;           /*低速通道2计数器溢出的中断原始位。*/
            uint32_t lstimer3_ovf:        1;           /*低速通道3计数器溢出的中断原始位。*/
            uint32_t duty_chng_end_hsch0: 1;           /*高速通道0占空比变化的中断原始位已完成。*/
            uint32_t duty_chng_end_hsch1: 1;           /*高速通道1占空比变化的中断原始位已完成。*/
            uint32_t duty_chng_end_hsch2: 1;           /*高速通道2占空比更改的中断原始位已完成。*/
            uint32_t duty_chng_end_hsch3: 1;           /*高速通道3占空比变化的中断原始位已完成。*/
            uint32_t duty_chng_end_hsch4: 1;           /*高速通道4占空比更改的中断原始位已完成。*/
            uint32_t duty_chng_end_hsch5: 1;           /*高速通道5占空比变化的中断原始位已完成。*/
            uint32_t duty_chng_end_hsch6: 1;           /*高速通道6的中断原始位占空比改变完成。*/
            uint32_t duty_chng_end_hsch7: 1;           /*高速通道7占空比变化的中断原始位已完成。*/
            uint32_t duty_chng_end_lsch0: 1;           /*低速通道0占空比更改的中断原始位已完成。*/
            uint32_t duty_chng_end_lsch1: 1;           /*低速通道1占空比更改的中断原始位已完成。*/
            uint32_t duty_chng_end_lsch2: 1;           /*低速通道2占空比更改的中断原始位已完成。*/
            uint32_t duty_chng_end_lsch3: 1;           /*低速通道3占空比改变的中断原始位已完成。*/
            uint32_t duty_chng_end_lsch4: 1;           /*低速通道4占空比更改的中断原始位已完成。*/
            uint32_t duty_chng_end_lsch5: 1;           /*低速通道5占空比变化的中断原始位已完成。*/
            uint32_t duty_chng_end_lsch6: 1;           /*低速通道6占空比改变的中断原始位已完成。*/
            uint32_t duty_chng_end_lsch7: 1;           /*低速通道7占空比更改的中断原始位已完成。*/
            uint32_t reserved24:          8;
        };
        uint32_t val;
    } int_raw;
    union {
        struct {
            uint32_t hstimer0_ovf:        1;            /*高速通道0计数器溢出事件的中断状态位。*/
            uint32_t hstimer1_ovf:        1;            /*高速通道1计数器溢出事件的中断状态位。*/
            uint32_t hstimer2_ovf:        1;            /*高速通道2计数器溢出事件的中断状态位。*/
            uint32_t hstimer3_ovf:        1;            /*高速通道3计数器溢出事件的中断状态位。*/
            uint32_t lstimer0_ovf:        1;            /*低速通道0计数器溢出事件的中断状态位。*/
            uint32_t lstimer1_ovf:        1;            /*低速通道1计数器溢出事件的中断状态位。*/
            uint32_t lstimer2_ovf:        1;            /*低速通道2计数器溢出事件的中断状态位。*/
            uint32_t lstimer3_ovf:        1;            /*低速通道3计数器溢出事件的中断状态位。*/
            uint32_t duty_chng_end_hsch0: 1;            /*高速通道0占空比改变完成事件的中断启用位。*/
            uint32_t duty_chng_end_hsch1: 1;            /*高速通道1占空比变化完成事件的中断状态位。*/
            uint32_t duty_chng_end_hsch2: 1;            /*高速通道2占空比变化完成事件的中断状态位。*/
            uint32_t duty_chng_end_hsch3: 1;            /*高速通道3占空比变化完成事件的中断状态位。*/
            uint32_t duty_chng_end_hsch4: 1;            /*高速通道4占空比变化完成事件的中断状态位。*/
            uint32_t duty_chng_end_hsch5: 1;            /*高速通道5占空比变化完成事件的中断状态位。*/
            uint32_t duty_chng_end_hsch6: 1;            /*高速通道6占空比变化完成事件的中断状态位。*/
            uint32_t duty_chng_end_hsch7: 1;            /*高速通道7占空比变化完成事件的中断状态位。*/
            uint32_t duty_chng_end_lsch0: 1;            /*低速通道0占空比变化完成事件的中断状态位。*/
            uint32_t duty_chng_end_lsch1: 1;            /*低速通道1占空比变化完成事件的中断状态位。*/
            uint32_t duty_chng_end_lsch2: 1;            /*低速通道2占空比变化完成事件的中断状态位。*/
            uint32_t duty_chng_end_lsch3: 1;            /*低速通道3占空比变化完成事件的中断状态位。*/
            uint32_t duty_chng_end_lsch4: 1;            /*低速通道4占空比变化完成事件的中断状态位。*/
            uint32_t duty_chng_end_lsch5: 1;            /*低速通道5占空比变化完成事件的中断状态位。*/
            uint32_t duty_chng_end_lsch6: 1;            /*低速通道6占空比变化完成事件的中断状态位。*/
            uint32_t duty_chng_end_lsch7: 1;            /*低速通道7占空比变化完成事件的中断状态位*/
            uint32_t reserved24:          8;
        };
        uint32_t val;
    } int_st;
    union {
        struct {
            uint32_t hstimer0_ovf:        1;           /*高速通道0计数器溢出中断的中断启用位。*/
            uint32_t hstimer1_ovf:        1;           /*高速通道1计数器溢出中断的中断启用位。*/
            uint32_t hstimer2_ovf:        1;           /*高速通道2计数器溢出中断的中断启用位。*/
            uint32_t hstimer3_ovf:        1;           /*高速通道3计数器溢出中断的中断启用位。*/
            uint32_t lstimer0_ovf:        1;           /*低速通道0计数器溢出中断的中断启用位。*/
            uint32_t lstimer1_ovf:        1;           /*低速通道1计数器溢出中断的中断启用位。*/
            uint32_t lstimer2_ovf:        1;           /*低速通道2计数器溢出中断的中断启用位。*/
            uint32_t lstimer3_ovf:        1;           /*低速通道3计数器溢出中断的中断启用位。*/
            uint32_t duty_chng_end_hsch0: 1;           /*高速通道0占空比改变完成中断的中断使能位。*/
            uint32_t duty_chng_end_hsch1: 1;           /*高速通道1占空比改变完成中断的中断使能位。*/
            uint32_t duty_chng_end_hsch2: 1;           /*高速通道2占空比改变完成中断的中断使能位。*/
            uint32_t duty_chng_end_hsch3: 1;           /*高速通道3占空比改变完成中断的中断使能位。*/
            uint32_t duty_chng_end_hsch4: 1;           /*高速通道4占空比改变完成中断的中断使能位。*/
            uint32_t duty_chng_end_hsch5: 1;           /*高速通道5占空比改变完成中断的中断使能位。*/
            uint32_t duty_chng_end_hsch6: 1;           /*高速通道6占空比改变完成中断的中断使能位。*/
            uint32_t duty_chng_end_hsch7: 1;           /*高速通道7占空比改变完成中断的中断使能位。*/
            uint32_t duty_chng_end_lsch0: 1;           /*低速通道0占空比改变完成中断的中断使能位。*/
            uint32_t duty_chng_end_lsch1: 1;           /*低速通道1占空比改变完成中断的中断使能位。*/
            uint32_t duty_chng_end_lsch2: 1;           /*低速通道2占空比改变完成中断的中断使能位。*/
            uint32_t duty_chng_end_lsch3: 1;           /*低速通道3占空比改变完成中断的中断使能位。*/
            uint32_t duty_chng_end_lsch4: 1;           /*低速通道4占空比改变完成中断的中断使能位。*/
            uint32_t duty_chng_end_lsch5: 1;           /*低速通道5占空比改变完成中断的中断使能位。*/
            uint32_t duty_chng_end_lsch6: 1;           /*低速通道6占空比改变完成中断的中断使能位。*/
            uint32_t duty_chng_end_lsch7: 1;           /*低速通道7占空比改变完成中断的中断使能位。*/
            uint32_t reserved24:          8;
        };
        uint32_t val;
    } int_ena;
    union {
        struct {
            uint32_t hstimer0_ovf:        1;           /*设置此位以清除高速通道0计数器溢出中断。*/
            uint32_t hstimer1_ovf:        1;           /*设置此位以清除高速通道1计数器溢出中断。*/
            uint32_t hstimer2_ovf:        1;           /*设置此位以清除高速通道2计数器溢出中断。*/
            uint32_t hstimer3_ovf:        1;           /*设置此位以清除高速通道3计数器溢出中断。*/
            uint32_t lstimer0_ovf:        1;           /*设置此位以清除低速通道0计数器溢出中断。*/
            uint32_t lstimer1_ovf:        1;           /*设置此位以清除低速通道1计数器溢出中断。*/
            uint32_t lstimer2_ovf:        1;           /*设置此位以清除低速通道2计数器溢出中断。*/
            uint32_t lstimer3_ovf:        1;           /*设置此位以清除低速通道3计数器溢出中断。*/
            uint32_t duty_chng_end_hsch0: 1;           /*设置此位以清除高速通道0占空比改变完成中断。*/
            uint32_t duty_chng_end_hsch1: 1;           /*设置此位以清除高速通道1占空比改变完成中断。*/
            uint32_t duty_chng_end_hsch2: 1;           /*设置此位以清除高速通道2占空比改变完成中断。*/
            uint32_t duty_chng_end_hsch3: 1;           /*设置此位以清除高速通道3占空比改变完成中断。*/
            uint32_t duty_chng_end_hsch4: 1;           /*设置此位以清除高速通道4占空比改变完成中断。*/
            uint32_t duty_chng_end_hsch5: 1;           /*设置此位以清除高速通道5占空比改变完成中断。*/
            uint32_t duty_chng_end_hsch6: 1;           /*设置此位以清除高速通道6占空比改变完成中断。*/
            uint32_t duty_chng_end_hsch7: 1;           /*设置此位以清除高速通道7占空比改变完成中断。*/
            uint32_t duty_chng_end_lsch0: 1;           /*设置此位以清除低速通道0占空比改变完成中断。*/
            uint32_t duty_chng_end_lsch1: 1;           /*设置此位以清除低速通道1占空比改变完成中断。*/
            uint32_t duty_chng_end_lsch2: 1;           /*设置此位以清除低速通道2占空比改变完成中断。*/
            uint32_t duty_chng_end_lsch3: 1;           /*设置此位以清除低速通道3占空比改变完成中断。*/
            uint32_t duty_chng_end_lsch4: 1;           /*设置此位以清除低速通道4占空比改变完成中断。*/
            uint32_t duty_chng_end_lsch5: 1;           /*设置此位以清除低速通道5占空比改变完成中断。*/
            uint32_t duty_chng_end_lsch6: 1;           /*设置此位以清除低速通道6占空比改变完成中断。*/
            uint32_t duty_chng_end_lsch7: 1;           /*设置此位以清除低速通道7占空比改变完成中断。*/
            uint32_t reserved24:          8;
        };
        uint32_t val;
    } int_clr;
    union {
        struct {
            uint32_t apb_clk_sel: 1;                   /*该位决定了LEDC低速通道的慢时钟，因此我们想用slow_clk_sel替换字段名*/
            uint32_t reserved1:  31;
        };
        struct {
            uint32_t slow_clk_sel: 1;                  /*该位用于设置slow_clk的频率。1’b1:80mhz 1’b0:8mhz，（仅用于LEDC低速通道/定时器）*/
            uint32_t reserved:  31;
        };
        uint32_t val;
    } conf;
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
    uint32_t date;                                     /*此寄存器表示版本。*/
} ledc_dev_t;
extern ledc_dev_t LEDC;

#ifdef __cplusplus
}
#endif

#endif  /* _SOC_LEDC_STRUCT_H_ */

