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
#ifndef _SOC_TIMG_STRUCT_H_
#define _SOC_TIMG_STRUCT_H_

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef volatile struct timg_dev_s {
    struct {
        union {
            struct {
                uint32_t reserved0:   10;
                uint32_t alarm_en:     1;             /*启用设置报警时*/
                uint32_t level_int_en: 1;             /*报警期间将产生设置电平类型的中断*/
                uint32_t edge_int_en:  1;             /*报警期间将产生设置边缘类型中断时*/
                uint32_t divider:     16;             /*计时器时钟（T0/1_clk）预缩放值。*/
                uint32_t autoreload:   1;             /*当设置定时器0/1时，报警时自动重新加载被启用*/
                uint32_t increase:     1;             /*当设置定时器0/1时基计数器增量时。清除计时器0时，时基计数器递减。*/
                uint32_t enable:       1;             /*当设置计时器0/1时基计数器启用时*/
            };
            uint32_t val;
        } config;
        uint32_t cnt_low;                             /*寄存器用于存储计时器0/1时基计数器电流值低32位。*/
        uint32_t cnt_high;                            /*寄存器存储计时器0时基计数器电流值（32位以上）。*/
        uint32_t update;                              /*写入任何值都将触发计时器0时基计数器值更新（计时器0当前值将存储在上述寄存器中）*/
        uint32_t alarm_low;                           /*计时器0时基计数器值低于32位，将触发报警*/
        uint32_t alarm_high;                          /*计时器0时基计数器值高于32位，将触发报警*/
        uint32_t load_low;                            /*将载入计时器0时基计数器的值的低32位*/
        uint32_t load_high;                           /*将加载到计时器0时基计数器中的值的较高32位*/
        uint32_t reload;                              /*写入任何值都将触发计时器0时基计数器重新加载*/
    } hw_timer[2];
    union {
        struct {
            uint32_t reserved0:       14;
            uint32_t flashboot_mod_en: 1;             /*启用设置闪存启动保护时*/
            uint32_t sys_reset_length: 3;             /*系统重置选择的长度。0：100ns 1：200ns 2：300ns 3：400ns 4：500ns 5：800ns 6：1.6us 7：3.2us*/
            uint32_t cpu_reset_length: 3;             /*CPU重置选择的长度。0：100ns 1：200ns 2：300ns 3：400ns 4：500ns 5：800ns 6：1.6us 7：3.2us*/
            uint32_t level_int_en:     1;             /*启用设置级别类型中断生成时*/
            uint32_t edge_int_en:      1;             /*启用设置边缘类型中断生成时*/
            uint32_t stg3:             2;             /*第3阶段配置。0：关闭1：中断2：复位CPU 3：复位系统*/
            uint32_t stg2:             2;             /*第2阶段配置。0：关闭1：中断2：复位CPU 3：复位系统*/
            uint32_t stg1:             2;             /*阶段1配置。0：关闭1：中断2：复位CPU 3：复位系统*/
            uint32_t stg0:             2;             /*阶段0配置。0：关闭1：中断2：复位CPU 3：复位系统*/
            uint32_t en:               1;             /*启用设置SWDT时*/
        };
        uint32_t val;
    } wdt_config0;
    union {
        struct {
            uint32_t reserved0:       16;
            uint32_t clk_prescale:16;             /*SWDT时钟预缩放值。周期=12.5ns*存储在此寄存器中的值*/
        };
        uint32_t val;
    } wdt_config1;
    uint32_t wdt_config2;                             /*SWDT时钟周期中的阶段0超时值*/
    uint32_t wdt_config3;                             /*SWDT时钟周期中的阶段1超时值*/
    uint32_t wdt_config4;                             /*SWDT时钟周期中的第2阶段超时值*/
    uint32_t wdt_config5;                             /*SWDT时钟周期中的第3阶段超时值*/
    uint32_t wdt_feed;                                /*写入任何值都将输入SWDT*/
    uint32_t wdt_wprotect;                            /*如果从默认值更改其值，则启用写保护。*/
    union {
        struct {
            uint32_t reserved0:             12;
            uint32_t start_cycling: 1;
            uint32_t clk_sel:       2;
            uint32_t rdy:           1;
            uint32_t max:          15;
            uint32_t start:         1;
        };
        uint32_t val;
    } rtc_cali_cfg;
    union {
        struct {
            uint32_t reserved0:      7;
            uint32_t value:25;
        };
        uint32_t val;
    } rtc_cali_cfg1;
    union {
        struct {
            uint32_t reserved0:         7;
            uint32_t rtc_only:     1;
            uint32_t cpst_en:      1;
            uint32_t lac_en:       1;
            uint32_t alarm_en:     1;
            uint32_t level_int_en: 1;
            uint32_t edge_int_en:  1;
            uint32_t divider:     16;
            uint32_t autoreload:   1;
            uint32_t increase:     1;
            uint32_t en:           1;
        };
        uint32_t val;
    } lactconfig;
    union {
        struct {
            uint32_t reserved0:         6;
            uint32_t step_len:26;
        };
        uint32_t val;
    } lactrtc;
    uint32_t lactlo;                                  /**/
    uint32_t lacthi;                                  /**/
    uint32_t lactupdate;                              /**/
    uint32_t lactalarmlo;                             /**/
    uint32_t lactalarmhi;                             /**/
    uint32_t lactloadlo;                              /**/
    uint32_t lactloadhi;                              /**/
    uint32_t lactload;                                /**/
    union {
        struct {
            uint32_t t0:         1;                   /*timer0报警时中断*/
            uint32_t t1:         1;                   /*timer1报警时中断*/
            uint32_t wdt:        1;                   /*中断阶段超时时中断*/
            uint32_t lact:       1;
            uint32_t reserved4: 28;
        };
        uint32_t val;
    } int_ena;
    union {
        struct {
            uint32_t t0:        1;                    /*timer0报警时中断*/
            uint32_t t1:        1;                    /*timer1报警时中断*/
            uint32_t wdt:       1;                    /*中断阶段超时时中断*/
            uint32_t lact:      1;
            uint32_t reserved4:28;
        };
        uint32_t val;
    } int_raw;
    union {
        struct {
            uint32_t t0:         1;                   /*timer0报警时中断*/
            uint32_t t1:         1;                   /*timer1报警时中断*/
            uint32_t wdt:        1;                   /*中断阶段超时时中断*/
            uint32_t lact:       1;
            uint32_t reserved4: 28;
        };
        uint32_t val;
    } int_st_timers;
    union {
        struct {
            uint32_t t0:         1;                   /*timer0报警时中断*/
            uint32_t t1:         1;                   /*timer1报警时中断*/
            uint32_t wdt:        1;                   /*中断阶段超时时中断*/
            uint32_t lact:       1;
            uint32_t reserved4: 28;
        };
        uint32_t val;
    } int_clr_timers;
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
    uint32_t reserved_d4;
    uint32_t reserved_d8;
    uint32_t reserved_dc;
    uint32_t reserved_e0;
    uint32_t reserved_e4;
    uint32_t reserved_e8;
    uint32_t reserved_ec;
    uint32_t reserved_f0;
    uint32_t reserved_f4;
    union {
        struct {
            uint32_t date:28;                         /*此regfile的版本*/
            uint32_t reserved28:   4;
        };
        uint32_t val;
    } timg_date;
    union {
        struct {
            uint32_t reserved0: 31;
            uint32_t en:     1;                   /*强制启用此regfile的时钟*/
        };
        uint32_t val;
    } clk;
} timg_dev_t;
extern timg_dev_t TIMERG0;
extern timg_dev_t TIMERG1;

#ifdef __cplusplus
}
#endif

#endif  /* _SOC_TIMG_STRUCT_H_ */

