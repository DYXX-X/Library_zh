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
#ifndef _SOC_PCNT_STRUCT_H_
#define _SOC_PCNT_STRUCT_H_

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef volatile struct pcnt_dev_s {
    struct {
        union {
            struct {
                uint32_t filter_thres:  10;         /*此寄存器用于过滤宽度小于单位0的此值的脉冲。*/
                uint32_t filter_en:      1;         /*这是用于过滤单元0的输入信号的启用位。*/
                uint32_t thr_zero_en:    1;         /*这是用于将unit0的计数与0值进行比较的启用位。*/
                uint32_t thr_h_lim_en:   1;         /*这是将unit0的计数与thr_hl_lim值进行比较的启用位。*/
                uint32_t thr_l_lim_en:   1;         /*这是用于将unit0的计数与thr_l_lim值进行比较的启用位。*/
                uint32_t thr_thres0_en:  1;         /*这是用于将单位0的计数与thres0值进行比较的启用位。*/
                uint32_t thr_thres1_en:  1;         /*这是用于将unit0的计数与thres1值进行比较的启用位。*/
                uint32_t ch0_neg_mode:   2;         /*此寄存器用于控制单元0的通道0输入负边缘信号的模式。2'd1：在输入信号2'd2的负边缘增加：在输入输入信号2'd2的负边缘减少：其他：禁止*/
                uint32_t ch0_pos_mode:   2;         /*此寄存器用于控制单元0的通道0输入位置边缘信号的模式。2'd1：在输入信号2'd2的边缘增加：在输入输入信号2'2的边缘减少：禁止*/
                uint32_t ch0_hctrl_mode: 2;         /*此寄存器用于控制单元0的通道0高控制信号的模式。2'd0：控制信号低时增加2'd1：控制信号高时减少其他：禁止*/
                uint32_t ch0_lctrl_mode: 2;         /*此寄存器用于控制单元0的通道0的低控制信号模式。2'd0：控制信号低时增加2'd1：控制信号高时减少其他：禁止*/
                uint32_t ch1_neg_mode:   2;         /*此寄存器用于控制单元0的通道1输入负边缘信号的模式。2'd1：在输入信号2'd2的负边缘增加：在输入输入信号的负边缘减少其他：禁止*/
                uint32_t ch1_pos_mode:   2;         /*此寄存器用于控制单元0的信道1输入位置边缘信号的模式。2'd1：在输入信号2'd2的边缘增加：在输入输入信号2'2的边缘减少：禁止*/
                uint32_t ch1_hctrl_mode: 2;         /*此寄存器用于控制单元0的通道1高控制信号的模式。2'd0：控制信号低时增加2'd1：控制信号高时减少其他：禁止*/
                uint32_t ch1_lctrl_mode: 2;         /*此寄存器用于控制单元0的信道1的低控制信号模式。2'd0：控制信号低时增加2'd1：控制信号高时减少其他：禁止*/
            };
            uint32_t val;
        } conf0;
        union {
            struct {
                uint32_t cnt_thres0:16;             /*此寄存器用于配置单元0的thres0值。*/
                uint32_t cnt_thres1:16;             /*此寄存器用于为unit0配置thres1值。*/
            };
            uint32_t val;
        } conf1;
        union {
            struct {
                uint32_t cnt_h_lim:16;              /*此寄存器用于为unit0配置thr_hl_lim值。*/
                uint32_t cnt_l_lim:16;              /*此寄存器用于为unit0配置thr_l_lim值。*/
            };
            uint32_t val;
        } conf2;
    } conf_unit[8];
    union {
        struct {
            uint32_t cnt_val   : 16;                /*该寄存器存储单元0的当前脉冲计数值。*/
            uint32_t reserved16: 16;
        };
        uint32_t val;
    } cnt_unit[8];
    union {
        struct {
            uint32_t cnt_thr_event_u0: 1;           /*这是通道0事件的中断原始位。*/
            uint32_t cnt_thr_event_u1: 1;           /*这是通道1事件的中断原始位。*/
            uint32_t cnt_thr_event_u2: 1;           /*这是通道2事件的中断原始位。*/
            uint32_t cnt_thr_event_u3: 1;           /*这是通道3事件的中断原始位。*/
            uint32_t cnt_thr_event_u4: 1;           /*这是通道4事件的中断原始位。*/
            uint32_t cnt_thr_event_u5: 1;           /*这是通道5事件的中断原始位。*/
            uint32_t cnt_thr_event_u6: 1;           /*这是通道6事件的中断原始位。*/
            uint32_t cnt_thr_event_u7: 1;           /*这是通道7事件的中断原始位。*/
            uint32_t reserved8:       24;
        };
        uint32_t val;
    } int_raw;
    union {
        struct {
            uint32_t cnt_thr_event_u0: 1;            /*这是通道0事件的中断状态位。*/
            uint32_t cnt_thr_event_u1: 1;            /*这是通道1事件的中断状态位。*/
            uint32_t cnt_thr_event_u2: 1;            /*这是通道2事件的中断状态位。*/
            uint32_t cnt_thr_event_u3: 1;            /*这是通道3事件的中断状态位。*/
            uint32_t cnt_thr_event_u4: 1;            /*这是通道4事件的中断状态位。*/
            uint32_t cnt_thr_event_u5: 1;            /*这是通道5事件的中断状态位。*/
            uint32_t cnt_thr_event_u6: 1;            /*这是通道6事件的中断状态位。*/
            uint32_t cnt_thr_event_u7: 1;            /*这是通道7事件的中断状态位。*/
            uint32_t reserved8:       24;
        };
        uint32_t val;
    } int_st;
    union {
        struct {
            uint32_t cnt_thr_event_u0: 1;           /*这是通道0事件的中断启用位。*/
            uint32_t cnt_thr_event_u1: 1;           /*这是通道1事件的中断启用位。*/
            uint32_t cnt_thr_event_u2: 1;           /*这是通道2事件的中断启用位。*/
            uint32_t cnt_thr_event_u3: 1;           /*这是通道3事件的中断启用位。*/
            uint32_t cnt_thr_event_u4: 1;           /*这是通道4事件的中断启用位。*/
            uint32_t cnt_thr_event_u5: 1;           /*这是通道5事件的中断启用位。*/
            uint32_t cnt_thr_event_u6: 1;           /*这是通道6事件的中断启用位。*/
            uint32_t cnt_thr_event_u7: 1;           /*这是通道7事件的中断启用位。*/
            uint32_t reserved8:       24;
        };
        uint32_t val;
    } int_ena;
    union {
        struct {
            uint32_t cnt_thr_event_u0: 1;           /*设置此位以清除通道0事件中断。*/
            uint32_t cnt_thr_event_u1: 1;           /*设置此位以清除通道1事件中断。*/
            uint32_t cnt_thr_event_u2: 1;           /*设置此位以清除通道2事件中断。*/
            uint32_t cnt_thr_event_u3: 1;           /*设置此位以清除通道3事件中断。*/
            uint32_t cnt_thr_event_u4: 1;           /*设置此位以清除通道4事件中断。*/
            uint32_t cnt_thr_event_u5: 1;           /*设置此位以清除通道5事件中断。*/
            uint32_t cnt_thr_event_u6: 1;           /*设置此位以清除通道6事件中断。*/
            uint32_t cnt_thr_event_u7: 1;           /*设置此位以清除通道7事件中断。*/
            uint32_t reserved8:       24;
        };
        uint32_t val;
    } int_clr;
    union {
        struct {
            uint32_t cnt_mode:2;                    /*0：正值归零；1： 负值为零；2： 计数器值为负值；3： 计数器值正值*/
            uint32_t thres1_lat:1;                  /* 计数器值等于threshold1*/
            uint32_t thres0_lat:1;                  /* 计数器值等于threshold0*/
            uint32_t l_lim_lat:1;                   /* 计数器值达到hlim*/
            uint32_t h_lim_lat:1;                   /* 计数器值达到l_lim*/
            uint32_t zero_lat:1;                    /* 计数器值等于零*/
            uint32_t reserved7:25;
        };
        uint32_t val;
    } status_unit[8];
    union {
        struct {
            uint32_t cnt_rst_u0:   1;               /*设置此位以清除unit0的计数器。*/
            uint32_t cnt_pause_u0: 1;               /*设置此位以暂停unit0的计数器。*/
            uint32_t cnt_rst_u1:   1;               /*设置此位以清除第一单元的计数器。*/
            uint32_t cnt_pause_u1: 1;               /*设置此位以暂停第一单元的计数器。*/
            uint32_t cnt_rst_u2:   1;               /*设置此位以清除第二单元的计数器。*/
            uint32_t cnt_pause_u2: 1;               /*设置此位以暂停第二单元的计数器。*/
            uint32_t cnt_rst_u3:   1;               /*设置此位以清除第三单元的计数器。*/
            uint32_t cnt_pause_u3: 1;               /*设置此位以暂停第三单元的计数器。*/
            uint32_t cnt_rst_u4:   1;               /*设置此位以清除第四单元的计数器。*/
            uint32_t cnt_pause_u4: 1;               /*设置此位以暂停第四单元的计数器。*/
            uint32_t cnt_rst_u5:   1;               /*设置此位以清除第五单元的计数器。*/
            uint32_t cnt_pause_u5: 1;               /*设置此位以暂停第五单元的计数器。*/
            uint32_t cnt_rst_u6:   1;               /*设置此位以清除第六单元的计数器。*/
            uint32_t cnt_pause_u6: 1;               /*设置此位以暂停第六单元的计数器。*/
            uint32_t cnt_rst_u7:   1;               /*设置此位以清除第七单元的计数器。*/
            uint32_t cnt_pause_u7: 1;               /*设置此位以暂停第七单元的计数器。*/
            uint32_t clk_en:       1;
            uint32_t reserved17:  15;
        };
        uint32_t val;
    } ctrl;
    uint32_t reserved_b4;
    uint32_t reserved_b8;
    uint32_t reserved_bc;
    uint32_t reserved_c0;
    uint32_t reserved_c4;
    uint32_t reserved_c8;
    uint32_t reserved_cc;
    uint32_t reserved_d0;
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
    uint32_t date;                                  /**/
} pcnt_dev_t;
extern pcnt_dev_t PCNT;

#ifdef __cplusplus
}
#endif

#endif  /* _SOC_PCNT_STRUCT_H_ */

