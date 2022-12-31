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
#ifndef _SOC_RTC_IO_STRUCT_H_
#define _SOC_RTC_IO_STRUCT_H_

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef volatile struct rtc_io_dev_s {
    union {
        struct {
            uint32_t reserved0:        14;
            uint32_t data:18;              /*GPIO0~17输出值*/
        };
        uint32_t val;
    } out;
    union {
        struct {
            uint32_t reserved0:             14;
            uint32_t w1ts:18;         /*GPIO0~17输出值写入1设置*/
        };
        uint32_t val;
    } out_w1ts;
    union {
        struct {
            uint32_t reserved0:             14;
            uint32_t w1tc:18;         /*GPIO0~17输出值写入1清除*/
        };
        uint32_t val;
    } out_w1tc;
    union {
        struct {
            uint32_t reserved0:      14;
            uint32_t enable:18;                /*GPIO0~17输出使能*/
        };
        uint32_t val;
    } enable;
    union {
        struct {
            uint32_t reserved0:           14;
            uint32_t w1ts:18;           /*GPIO0~17输出使能写入1设置*/
        };
        uint32_t val;
    } enable_w1ts;
    union {
        struct {
            uint32_t reserved0:           14;
            uint32_t w1tc:18;           /*GPIO0~17输出使写入1清零*/
        };
        uint32_t val;
    } enable_w1tc;
    union {
        struct {
            uint32_t reserved0:          14;
            uint32_t status:18;            /*GPIO0~17中断状态*/
        };
        uint32_t val;
    } status;
    union {
        struct {
            uint32_t reserved0:               14;
            uint32_t w1ts:18;       /*GPIO0~17中断状态写入1设置*/
        };
        uint32_t val;
    } status_w1ts;
    union {
        struct {
            uint32_t reserved0:               14;
            uint32_t w1tc:18;       /*GPIO0~17中断状态写入1清除*/
        };
        uint32_t val;
    } status_w1tc;
    union {
        struct {
            uint32_t reserved0:       14;
            uint32_t in:18;               /*GPIO0~17输入值*/
        };
        uint32_t val;
    } in_val;
    union {
        struct {
            uint32_t reserved0:                   2;
            uint32_t pad_driver:    1;    /*如果设置为0：正常输出如果设置为1：漏极开路*/
            uint32_t reserved3:                   4;
            uint32_t int_type:      3;    /*如果设置为0：GPIO中断禁用如果设置为1：上升沿触发如果设置为2：下降沿触发器如果设置为3：任何边缘触发器如果设置4：低电平触发器如果设置5：高电平触发器*/
            uint32_t wakeup_enable: 1;    /*GPIO唤醒启用仅在轻度睡眠时可用*/
            uint32_t reserved11:                 21;
        };
        uint32_t val;
    } pin[18];
    union {
        struct {
            uint32_t sel0:          5;
            uint32_t sel1:          5;
            uint32_t sel2:          5;
            uint32_t sel3:          5;
            uint32_t sel4:          5;
            uint32_t no_gating_12m: 1;
            uint32_t reserved26:              6;
        };
        uint32_t val;
    } debug_sel;
    uint32_t dig_pad_hold;                              /*选择数字键盘保持值。*/
    union {
        struct {
            uint32_t reserved0: 30;
            uint32_t hall_phase: 1;                     /*霍尔传感器反相*/
            uint32_t xpd_hall:   1;                     /*接通霍尔传感器电源并连接到VP和VN*/
        };
        uint32_t val;
    } hall_sens;
    union {
        struct {
            uint32_t reserved0:      4;
            uint32_t sense4_fun_ie:  1;                 /*键盘的输入使能*/
            uint32_t sense4_slp_ie:  1;                 /*键盘处于睡眠状态时的输入启用*/
            uint32_t sense4_slp_sel: 1;                 /*垫的睡眠状态选择信号*/
            uint32_t sense4_fun_sel: 2;                 /*焊盘的功能选择信号*/
            uint32_t sense3_fun_ie:  1;                 /*键盘的输入使能*/
            uint32_t sense3_slp_ie:  1;                 /*键盘处于睡眠状态时的输入启用*/
            uint32_t sense3_slp_sel: 1;                 /*垫的睡眠状态选择信号*/
            uint32_t sense3_fun_sel: 2;                 /*焊盘的功能选择信号*/
            uint32_t sense2_fun_ie:  1;                 /*键盘的输入使能*/
            uint32_t sense2_slp_ie:  1;                 /*键盘处于睡眠状态时的输入启用*/
            uint32_t sense2_slp_sel: 1;                 /*垫的睡眠状态选择信号*/
            uint32_t sense2_fun_sel: 2;                 /*焊盘的功能选择信号*/
            uint32_t sense1_fun_ie:  1;                 /*键盘的输入使能*/
            uint32_t sense1_slp_ie:  1;                 /*键盘处于睡眠状态时的输入启用*/
            uint32_t sense1_slp_sel: 1;                 /*垫的睡眠状态选择信号*/
            uint32_t sense1_fun_sel: 2;                 /*焊盘的功能选择信号*/
            uint32_t sense4_mux_sel: 1;                 /*�1.� 选择数字功能�0�选择rtc函数*/
            uint32_t sense3_mux_sel: 1;                 /*�1.� 选择数字功能�0�选择rtc函数*/
            uint32_t sense2_mux_sel: 1;                 /*�1.� 选择数字功能�0�选择rtc函数*/
            uint32_t sense1_mux_sel: 1;                 /*�1.� 选择数字功能�0�选择rtc函数*/
            uint32_t sense4_hold:    1;                 /*将保持设置为时保持输出的当前值�1.�*/
            uint32_t sense3_hold:    1;                 /*将保持设置为时保持输出的当前值�1.�*/
            uint32_t sense2_hold:    1;                 /*将保持设置为时保持输出的当前值�1.�*/
            uint32_t sense1_hold:    1;                 /*将保持设置为时保持输出的当前值�1.�*/
        };
        uint32_t val;
    } sensor_pads;
    union {
        struct {
            uint32_t reserved0:   18;
            uint32_t adc2_fun_ie:  1;                   /*键盘的输入使能*/
            uint32_t adc2_slp_ie:  1;                   /*键盘处于睡眠状态时的输入启用*/
            uint32_t adc2_slp_sel: 1;                   /*垫的睡眠状态选择信号*/
            uint32_t adc2_fun_sel: 2;                   /*焊盘的功能选择信号*/
            uint32_t adc1_fun_ie:  1;                   /*键盘的输入使能*/
            uint32_t adc1_slp_ie:  1;                   /*键盘处于睡眠状态时的输入启用*/
            uint32_t adc1_slp_sel: 1;                   /*垫的睡眠状态选择信号*/
            uint32_t adc1_fun_sel: 2;                   /*焊盘的功能选择信号*/
            uint32_t adc2_mux_sel: 1;                   /*�1.� 选择数字功能�0�选择rtc函数*/
            uint32_t adc1_mux_sel: 1;                   /*�1.� 选择数字功能�0�选择rtc函数*/
            uint32_t adc2_hold:    1;                   /*将保持设置为时保持输出的当前值�1.�*/
            uint32_t adc1_hold:    1;                   /*将保持设置为时保持输出的当前值�1.�*/
        };
        uint32_t val;
    } adc_pad;
    union {
        struct {
            uint32_t reserved0:          10;
            uint32_t dac_xpd_force: 1;            /*打开DAC1。通常，如果打开DAC，我们需要将PDAC1设为三态，即IE=0 OE=0 RDE=0 RUE=0*/
            uint32_t fun_ie:        1;            /*键盘的输入使能*/
            uint32_t slp_oe:        1;            /*睡眠状态下极板的输出启用*/
            uint32_t slp_ie:        1;            /*键盘处于睡眠状态时的输入启用*/
            uint32_t slp_sel:       1;            /*垫的睡眠状态选择信号*/
            uint32_t fun_sel:       2;            /*焊盘的功能选择信号*/
            uint32_t mux_sel:       1;            /*�1.� 选择数字功能�0�选择rtc函数*/
            uint32_t xpd_dac:       1;            /*打开DAC1。通常，如果打开DAC，我们需要三态PDAC1，即IE=0 OE=0 RDE=0 RUE=0*/
            uint32_t dac:           8;            /*PAD DAC1控制代码。*/
            uint32_t rue:           1;            /*极板的上拉启用*/
            uint32_t rde:           1;            /*衬垫的下拉启用*/
            uint32_t hold:          1;            /*将保持设置为时保持输出的当前值�1.�*/
            uint32_t drv:           2;            /*衬垫的驱动力*/
        };
        uint32_t val;
    } pad_dac[2];
    union {
        struct {
            uint32_t reserved0:      1;
            uint32_t dbias_xtal_32k: 2;                 /*32K XTAL自偏置参考控制。*/
            uint32_t dres_xtal_32k:  2;                 /*32K XTAL电阻器偏置控制。*/
            uint32_t x32p_fun_ie:    1;                 /*键盘的输入使能*/
            uint32_t x32p_slp_oe:    1;                 /*睡眠状态下极板的输出启用*/
            uint32_t x32p_slp_ie:    1;                 /*键盘处于睡眠状态时的输入启用*/
            uint32_t x32p_slp_sel:   1;                 /*垫的睡眠状态选择信号*/
            uint32_t x32p_fun_sel:   2;                 /*焊盘的功能选择信号*/
            uint32_t x32n_fun_ie:    1;                 /*键盘的输入使能*/
            uint32_t x32n_slp_oe:    1;                 /*睡眠状态下极板的输出启用*/
            uint32_t x32n_slp_ie:    1;                 /*键盘处于睡眠状态时的输入启用*/
            uint32_t x32n_slp_sel:   1;                 /*垫的睡眠状态选择信号*/
            uint32_t x32n_fun_sel:   2;                 /*焊盘的功能选择信号*/
            uint32_t x32p_mux_sel:   1;                 /*�1.� 选择数字功能�0�选择rtc函数*/
            uint32_t x32n_mux_sel:   1;                 /*�1.� 选择数字功能�0�选择rtc函数*/
            uint32_t xpd_xtal_32k:   1;                 /*给32kHz晶体振荡器通电*/
            uint32_t dac_xtal_32k:   2;                 /*32K XTAL偏置电流DAC。*/
            uint32_t x32p_rue:       1;                 /*极板的上拉启用*/
            uint32_t x32p_rde:       1;                 /*衬垫的下拉启用*/
            uint32_t x32p_hold:      1;                 /*将保持设置为时保持输出的当前值�1.�*/
            uint32_t x32p_drv:       2;                 /*衬垫的驱动力*/
            uint32_t x32n_rue:       1;                 /*极板的上拉启用*/
            uint32_t x32n_rde:       1;                 /*衬垫的下拉启用*/
            uint32_t x32n_hold:      1;                 /*将保持设置为时保持输出的当前值�1.�*/
            uint32_t x32n_drv:       2;                 /*衬垫的驱动力*/
        };
        uint32_t val;
    } xtal_32k_pad;
    union {
        struct {
            uint32_t reserved0:     23;
            uint32_t dcur:     2;                 /*触摸传感器偏置电流。应具有与BIAS_LEEP绑定的选项（当BIAS_SEEP时，此设置可用*/
            uint32_t drange:   2;                 /*触摸传感器锯齿波电压范围。*/
            uint32_t drefl:    2;                 /*触摸传感器锯齿波底部电压。*/
            uint32_t drefh:    2;                 /*触摸传感器锯齿波顶部电压。*/
            uint32_t xpd_bias: 1;                 /*触摸传感器偏置电源打开。*/
        };
        uint32_t val;
    } touch_cfg;
    union {
        struct {
            uint32_t reserved0:         12;
            uint32_t to_gpio: 1;             /*将rtc焊盘输入连接到数字焊盘输入�0� 提供GPIO4*/
            uint32_t fun_ie:  1;             /*键盘的输入使能*/
            uint32_t slp_oe:  1;             /*睡眠状态下极板的输出启用*/
            uint32_t slp_ie:  1;             /*键盘处于睡眠状态时的输入启用*/
            uint32_t slp_sel: 1;             /*垫的睡眠状态选择信号*/
            uint32_t fun_sel: 2;             /*焊盘的功能选择信号*/
            uint32_t mux_sel: 1;             /*�1.� 选择数字功能�0�选择rtc函数*/
            uint32_t xpd:     1;             /*触摸传感器电源打开。*/
            uint32_t tie_opt: 1;             /*默认触摸传感器连接选项。0：平局低1：平局高。*/
            uint32_t start:   1;             /*启动触摸传感器。*/
            uint32_t dac:     3;             /*触摸传感器坡度控制。每个触摸面板默认值为100。*/
            uint32_t reserved26:         1;
            uint32_t rue:     1;             /*极板的上拉启用*/
            uint32_t rde:     1;             /*衬垫的下拉启用*/
            uint32_t drv:     2;             /*衬垫的驱动力*/
            uint32_t hold:    1;             /*将保持设置为时保持输出的当前值�1.�*/
        };
        uint32_t val;
    } touch_pad[10];
    union {
        struct {
            uint32_t reserved0:      27;
            uint32_t sel: 5;                /*选择唤醒源�0� 选择GPIO0�1.� 选择GPIO2。。。�17� 选择GPIO17*/
        };
        uint32_t val;
    } ext_wakeup0;
    union {
        struct {
            uint32_t reserved0:      27;
            uint32_t sel: 5;                /*选择外部xtl电源�0� 选择GPIO0�1.� 选择GPIO2。。。�17� 选择GPIO17*/
        };
        uint32_t val;
    } xtl_ext_ctr;
    union {
        struct {
            uint32_t reserved0:        23;
            uint32_t debug_bit_sel: 5;
            uint32_t scl_sel:   2;              /*�0� 使用TOUCH_PARD[0]作为i2c clk�1.� 使用TOUCH_PARD[2]作为i2c clk*/
            uint32_t sda_sel:   2;              /*�0� 使用TOUCH_PAD[1]作为i2c-sda�1.� 使用TOUCH_PAD[3]作为i2c-sda*/
        };
        uint32_t val;
    } sar_i2c_io;
    union {
        struct {
            uint32_t date:      28;                     /*日期*/
            uint32_t reserved28: 4;
        };
        uint32_t val;
    } date;
} rtc_io_dev_t;
extern rtc_io_dev_t RTCIO;

#ifdef __cplusplus
}
#endif

#endif  /* _SOC_RTC_IO_STRUCT_H_ */

