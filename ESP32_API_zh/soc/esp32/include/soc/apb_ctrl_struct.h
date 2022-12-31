// 版权所有2015-2016 Espressif Systems（上海）私人有限公司
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
#ifndef _SOC_APB_CTRL_STRUCT_H_
#define _SOC_APB_CTRL_STRUCT_H_

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct apb_ctrl_dev_s {
    union {
        struct {
            volatile uint32_t pre_div:       10;
            volatile uint32_t clk_320m_en:    1;
            volatile uint32_t clk_en:         1;
            volatile uint32_t rst_tick:       1;
            volatile uint32_t quick_clk_chng: 1;
            volatile uint32_t reserved14:    18;
        };
        volatile uint32_t val;
    }clk_conf;
    union {
        struct {
            volatile uint32_t xtal_tick:     8;
            volatile uint32_t reserved8:    24;
        };
        volatile uint32_t val;
    }xtal_tick_conf;
    union {
        struct {
            volatile uint32_t pll_tick:     8;
            volatile uint32_t reserved8:   24;
        };
        volatile uint32_t val;
    }pll_tick_conf;
    union {
        struct {
            volatile uint32_t ck8m_tick:     8;
            volatile uint32_t reserved8:    24;
        };
        volatile uint32_t val;
    }ck8m_tick_conf;
    union {
        struct {
            volatile uint32_t start_force:       1;
            volatile uint32_t start:             1;
            volatile uint32_t sar2_mux:          1;       /*1： SAR ADC2由DIG ADC2 CTRL 0控制：SAR ADC2受PWDET CTRL控制*/
            volatile uint32_t work_mode:         2;       /*0：单模式1：双模式2：交替模式*/
            volatile uint32_t sar_sel:           1;       /*0:SAR1 1:SAR2仅适用于单SAR模式*/
            volatile uint32_t sar_clk_gated:     1;
            volatile uint32_t sar_clk_div:       8;       /*SAR时钟分频器*/
            volatile uint32_t sar1_patt_len:     4;       /*0~15表示长度1~16*/
            volatile uint32_t sar2_patt_len:     4;       /*0~15表示长度1~16*/
            volatile uint32_t sar1_patt_p_clear: 1;       /*清除DIG ADC1 CTRL的模式表指针*/
            volatile uint32_t sar2_patt_p_clear: 1;       /*清除DIG ADC2 CTRL的模式表指针*/
            volatile uint32_t data_sar_sel:      1;       /*1： 在这种情况下，分辨率不应大于11位。*/
            volatile uint32_t data_to_i2s:       1;       /*1： I2S输入数据来自SAR ADC（用于DMA）0:I2S输入信号来自GPIO矩阵*/
            volatile uint32_t reserved27:        5;
        };
        volatile uint32_t val;
    }saradc_ctrl;
    union {
        struct {
            volatile uint32_t meas_num_limit: 1;
            volatile uint32_t max_meas_num:   8;          /*最大转换数*/
            volatile uint32_t sar1_inv:       1;          /*1： DIG ADC1 CTRL的数据反相，否则不反相*/
            volatile uint32_t sar2_inv:       1;          /*1： DIG ADC2 CTRL的数据被反转，否则不会*/
            volatile uint32_t reserved11:    21;
        };
        volatile uint32_t val;
    }saradc_ctrl2;
    union {
        struct {
            volatile uint32_t rstb_wait:    8;
            volatile uint32_t standby_wait: 8;
            volatile uint32_t start_wait:   8;
            volatile uint32_t sample_cycle: 8;            /*采样周期*/
        };
        volatile uint32_t val;
    }saradc_fsm;
    volatile uint32_t saradc_sar1_patt_tab1;                 /*模式表1的项目0~3（每个项目一个字节）*/
    volatile uint32_t saradc_sar1_patt_tab2;                 /*模式表1的第4~7项（每项一个字节）*/
    volatile uint32_t saradc_sar1_patt_tab3;                 /*模式表1的第8~11项（每项一个字节）*/
    volatile uint32_t saradc_sar1_patt_tab4;                 /*模式表1的第12~15项（每项一个字节）*/
    volatile uint32_t saradc_sar2_patt_tab1;                 /*模式表2的项目0~3（每个项目一个字节）*/
    volatile uint32_t saradc_sar2_patt_tab2;                 /*模式表2的第4~7项（每项一个字节）*/
    volatile uint32_t saradc_sar2_patt_tab3;                 /*模式表2的第8~11项（每项一个字节）*/
    volatile uint32_t saradc_sar2_patt_tab4;                 /*模式表2的项目12~15（每个项目一个字节）*/
    union {
        struct {
            volatile uint32_t apll_tick:     8;
            volatile uint32_t reserved8:    24;
        };
        volatile uint32_t val;
    }apll_tick_conf;
    volatile uint32_t reserved_40;
    volatile uint32_t reserved_44;
    volatile uint32_t reserved_48;
    volatile uint32_t reserved_4c;
    volatile uint32_t reserved_50;
    volatile uint32_t reserved_54;
    volatile uint32_t reserved_58;
    volatile uint32_t reserved_5c;
    volatile uint32_t reserved_60;
    volatile uint32_t reserved_64;
    volatile uint32_t reserved_68;
    volatile uint32_t reserved_6c;
    volatile uint32_t reserved_70;
    volatile uint32_t reserved_74;
    volatile uint32_t reserved_78;
    volatile uint32_t date;                                      /**/
} apb_ctrl_dev_t;


#ifdef __cplusplus
}
#endif

#endif  /* _SOC_APB_CTRL_STRUCT_H_ */

