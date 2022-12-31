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
#ifndef _SOC_GPIO_STRUCT_H_
#define _SOC_GPIO_STRUCT_H_

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef volatile struct gpio_dev_s {
    uint32_t bt_select;                             /*NA*/
    uint32_t out;                                   /*GPIO0~31输出值*/
    uint32_t out_w1ts;                              /*GPIO0~31输出值写入1设置*/
    uint32_t out_w1tc;                              /*GPIO0~31输出值写入1清除*/
    union {
        struct {
            uint32_t data:       8;                 /*GPIO32~39输出值*/
            uint32_t reserved8: 24;
        };
        uint32_t val;
    } out1;
    union {
        struct {
            uint32_t data:       8;                 /*GPIO32~39输出值写入1设置*/
            uint32_t reserved8: 24;
        };
        uint32_t val;
    } out1_w1ts;
    union {
        struct {
            uint32_t data:       8;                 /*GPIO32~39输出值写入1清除*/
            uint32_t reserved8: 24;
        };
        uint32_t val;
    } out1_w1tc;
    union {
        struct {
            uint32_t sel:        8;                 /*SDIO PADS从外部打开/关闭控制*/
            uint32_t reserved8: 24;
        };
        uint32_t val;
    } sdio_select;
    uint32_t enable;                                /*GPIO0~31输出使能*/
    uint32_t enable_w1ts;                           /*GPIO0~31输出使能写入1设置*/
    uint32_t enable_w1tc;                           /*GPIO0~31输出使写入1清零*/
    union {
        struct {
            uint32_t data:        8;                /*GPIO32~39输出使能*/
            uint32_t reserved8:  24;
        };
        uint32_t val;
    } enable1;
    union {
        struct {
            uint32_t data:        8;                /*GPIO32~39输出使能写入1设置*/
            uint32_t reserved8:  24;
        };
        uint32_t val;
    } enable1_w1ts;
    union {
        struct {
            uint32_t data:        8;                /*GPIO32~39输出使写入1清零*/
            uint32_t reserved8:  24;
        };
        uint32_t val;
    } enable1_w1tc;
    union {
        struct {
            uint32_t strapping: 16;                 /*GPIO打包结果：｛2'd0 boot_sel_dig[7:1]vsdio_boot_sel boot_sel_chip[5:0]｝。boot_sel_dig[7:1]：｛U0RXD SD_CLK SD_CMD SD_DATA0 SD_DATA1 SD_DATA2 SD_DATA3｝。vsdio_oot_sel:MTDI。boot_sel_chip[5:0]：｛GPIO0 U0TXD GPIO2 GPIO4 MTDO GPIO5｝*/
            uint32_t reserved16:16;
        };
        uint32_t val;
    } strap;
    uint32_t in;                                    /*GPIO0~31输入值*/
    union {
        struct {
            uint32_t data:       8;                 /*GPIO32~39输入值*/
            uint32_t reserved8: 24;
        };
        uint32_t val;
    } in1;
    uint32_t status;                                /*GPIO0~31中断状态*/
    uint32_t status_w1ts;                           /*GPIO0~31中断状态写入1设置*/
    uint32_t status_w1tc;                           /*GPIO0~31中断状态写入1以清除*/
    union {
        struct {
            uint32_t intr_st:    8;                 /*GPIO32~39中断状态*/
            uint32_t reserved8: 24;
        };
        uint32_t val;
    } status1;
    union {
        struct {
            uint32_t intr_st:    8;                 /*GPIO32~39中断状态写入1设置*/
            uint32_t reserved8: 24;
        };
        uint32_t val;
    } status1_w1ts;
    union {
        struct {
            uint32_t intr_st:    8;                 /*GPIO32~39中断状态写1清除*/
            uint32_t reserved8: 24;
        };
        uint32_t val;
    } status1_w1tc;
    uint32_t reserved_5c;
    uint32_t acpu_int;                              /*GPIO0~31 APP CPU中断状态*/
    uint32_t acpu_nmi_int;                          /*GPIO0~31 APP CPU不可屏蔽中断状态*/
    uint32_t pcpu_int;                              /*GPIO0~31 PRO CPU中断状态*/
    uint32_t pcpu_nmi_int;                          /*GPIO0~31 PRO CPU不可屏蔽中断状态*/
    uint32_t cpusdio_int;                           /*SDIO的扩展GPIO0~31中断*/
    union {
        struct {
            uint32_t intr:       8;                 /*GPIO32~39 APP CPU中断状态*/
            uint32_t reserved8: 24;
        };
        uint32_t val;
    } acpu_int1;
    union {
        struct {
            uint32_t intr:       8;                 /*GPIO32~39 APP CPU不可屏蔽中断状态*/
            uint32_t reserved8: 24;
        };
        uint32_t val;
    } acpu_nmi_int1;
    union {
        struct {
            uint32_t intr:       8;                 /*GPIO32~39 PRO CPU中断状态*/
            uint32_t reserved8: 24;
        };
        uint32_t val;
    } pcpu_int1;
    union {
        struct {
            uint32_t intr:       8;                 /*GPIO32~39 PRO CPU不可屏蔽中断状态*/
            uint32_t reserved8: 24;
        };
        uint32_t val;
    } pcpu_nmi_int1;
    union {
        struct {
            uint32_t intr:       8;                 /*SDIO的扩展GPIO32~39中断*/
            uint32_t reserved8: 24;
        };
        uint32_t val;
    } cpusdio_int1;
    union {
        struct {
            uint32_t reserved0:     2;
            uint32_t pad_driver:    1;              /*如果设置为0：正常输出如果设置为1：漏极开路*/
            uint32_t reserved3:     4;
            uint32_t int_type:      3;              /*如果设置为0：GPIO中断禁用如果设置为1：上升沿触发如果设置为2：下降沿触发器如果设置为3：任何边缘触发器如果设置4：低电平触发器如果设置5：高电平触发器*/
            uint32_t wakeup_enable: 1;              /*GPIO唤醒启用仅在轻度睡眠时可用*/
            uint32_t config:        2;              /*NA*/
            uint32_t int_ena:       5;              /*bit0：APP CPU中断启用位1：APP CPU不可屏蔽中断启用位3：PRO CPU中断启用位数4：PRO CPU不可掩码中断启用位5：SDIO的范围中断启用*/
            uint32_t reserved18:   14;
        };
        uint32_t val;
    } pin[40];
    union {
        struct {
            uint32_t rtc_max:     10;
            uint32_t reserved10:  21;
            uint32_t start:        1;
        };
        uint32_t val;
    } cali_conf;
    union {
        struct {
            uint32_t value_sync2: 20;
            uint32_t reserved20:  10;
            uint32_t rdy_real:     1;
            uint32_t rdy_sync2:    1;
        };
        uint32_t val;
    } cali_data;
    union {
        struct {
            uint32_t func_sel:    6;                /*从256个输入中选择一个*/
            uint32_t sig_in_inv:  1;                /*如果要还原，请将输入值设置为1*/
            uint32_t sig_in_sel:  1;                /*如果要将值设置为1，则慢信号是否绕过io矩阵*/
            uint32_t reserved8:  24;                /*如果GPIO_FUNCx_IN_SEL设置为n（0<=n<40），则以下256个寄存器是连接到GPIO矩阵40个GPIO输入的256个输入信号的选择控制：如果GPIO_FONCx_IN_SEL设置为0x38，则表示GPIOn输入用于输入信号x：如果GPIO-FUNCx_IN_SEL设置设置为0x30，则输入信号x设置为1：输入信号x被设置为0*/
        };
        uint32_t val;
    } func_in_sel_cfg[256];
    union {
        struct {
            uint32_t func_sel:     9;               /*从256个输出中选择一个输出到40个GPIO*/
            uint32_t inv_sel:      1;               /*如果要将输出值设置为1，则反转输出值*/
            uint32_t oen_sel:      1;               /*使用逻辑oen信号或不使用寄存器设置的值的天气*/
            uint32_t oen_inv_sel:  1;               /*如果要将输出启用值设置为1，则反转输出启用值*/
            uint32_t reserved12:  20;               /*如果GPIO_FUNCx_OUT_SEL设置为n（0<=n<256），下面的40个寄存器是40个GPIO输出的选择控制：这意味着如果GPIO_FONCx_OUT_INV_SEL设置为1，输出信号x设置为~值，则GPIOn输入用于输出信号x。如果使用GPIO_ENABLE_DATA[x]作为启用值，GPIO_FUNC0_OUT_SEL为256或GPIO_FUNC0_OEN_SEL为1，则使用信号ENABLE*/
        };
        uint32_t val;
    } func_out_sel_cfg[40];
} gpio_dev_t;
extern gpio_dev_t GPIO;

#ifdef __cplusplus
}
#endif

#endif  /* _SOC_GPIO_STRUCT_H_ */

