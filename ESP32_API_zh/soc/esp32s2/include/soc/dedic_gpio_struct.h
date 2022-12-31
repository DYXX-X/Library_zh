/** 版权所有2020 Espressif Systems（上海）私人有限公司
 *
 *  根据Apache许可证2.0版（“许可证”）获得许可；除非符合许可证，否则不得使用此文件。您可以在以下地址获取许可证副本：
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 *  除非适用法律要求或书面同意，否则根据许可证分发的软件是按“原样”分发的，无任何明示或暗示的担保或条件。有关许可证下权限和限制的具体语言，请参阅许可证。
 */
#pragma once

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**配置寄存器*/
/** gpio_out_drt寄存器类型专用gpio指令输出寄存器
 */
typedef union {
    struct {
        /** gpio_out_drt_vlaue:WO；位位置：[7:0]；默认值：0；该寄存器用于配置8通道专用gpio的指令输出值。
         */
        uint32_t gpio_out_drt_vlaue: 8;
        uint32_t reserved8: 24;
    };
    uint32_t val;
} dedic_gpio_out_drt_reg_t;

/** gpio_out_msk寄存器类型专用gpio掩码输出寄存器
 */
typedef union {
    struct {
        /** gpio_out_value:WO；位位置：[7:0]；默认值：0；该寄存器用于配置8通道专用gpio的屏蔽输出值。
         */
        uint32_t gpio_out_value: 8;
        /** gpio_out_msk:WO；比特位置：[15:8]；默认值：0；此寄存器用于配置将被屏蔽的通道。1： 相应信道的输出将被屏蔽。
         */
        uint32_t gpio_out_msk: 8;
        uint32_t reserved16: 16;
    };
    uint32_t val;
} dedic_gpio_out_msk_reg_t;

/** gpio_out_idv寄存器类型专用gpio单个输出寄存器
 */
typedef union {
    struct {
        /** gpio_out_idv_ch0:WO；位位置：[1:0]；默认值：0；配置通道0输出值。0：保持输出值；1： 设定输出值；2： 明确输出值；3： 反向输出值。
         */
        uint32_t gpio_out_idv_ch0: 2;
        /** gpio_out_idv_ch1:WO；位位置：[3:2]；默认值：0；配置通道1输出值。0：保持输出值；1： 设定输出值；2： 明确输出值；3： 反向输出值。
         */
        uint32_t gpio_out_idv_ch1: 2;
        /** gpio_out_idv_ch2:WO；比特位置：[5:4]；默认值：0；配置通道2输出值。0：保持输出值；1： 设定输出值；2： 明确输出值；3： 反向输出值。
         */
        uint32_t gpio_out_idv_ch2: 2;
        /** gpio_out_idv_ch3:WO；位位置：[7:6]；默认值：0；配置通道3输出值。0：保持输出值；1： 设定输出值；2： 明确输出值；3： 反向输出值。
         */
        uint32_t gpio_out_idv_ch3: 2;
        /** gpio_out_idv_ch4:工单；比特位置：[9:8]；默认值：0；配置通道4输出值。0：保持输出值；1： 设定输出值；2： 明确输出值；3： 反向输出值。
         */
        uint32_t gpio_out_idv_ch4: 2;
        /** gpio_out_idv_ch5:WO；比特位置：[11:10]；默认值：0；配置通道5输出值。0：保持输出值；1： 设定输出值；2： 明确输出值；3： 反向输出值。
         */
        uint32_t gpio_out_idv_ch5: 2;
        /** gpio_out_idv_ch6:WO；比特位置：[13:12]；默认值：0；配置通道6输出值。0：保持输出值；1： 设定输出值；2： 明确输出值；3： 反向输出值。
         */
        uint32_t gpio_out_idv_ch6: 2;
        /** gpio_out_idv_ch7:WO；比特位置：[15:14]；默认值：0；配置通道7输出值。0：保持输出值；1： 设定输出值；2： 明确输出值；3： 反向输出值。
         */
        uint32_t gpio_out_idv_ch7: 2;
        uint32_t reserved16: 16;
    };
    uint32_t val;
} dedic_gpio_out_idv_reg_t;

/** gpio_out_cpu寄存器类型专用gpio输出模式选择寄存器
 */
typedef union {
    struct {
        /** gpio_out_cpu_sel0:R/W；位位置：[0]；默认值：0；为通道0选择寄存器或CPU指令器配置的gpio输出值。1：选择CPU指令器。
         */
        uint32_t gpio_out_cpu_sel0: 1;
        /** gpio_out_cpu_sel1：右侧；位位置：[1]；默认值：0；为通道1选择寄存器或CPU指令器配置的gpio输出值。1：选择CPU指令器。
         */
        uint32_t gpio_out_cpu_sel1: 1;
        /** gpio_out_cpu_sel2:R/W；位位置：[2]；默认值：0；为通道2.1选择寄存器或CPU指令器配置的gpio输出值：选择CPU指令器。
         */
        uint32_t gpio_out_cpu_sel2: 1;
        /** gpio_out_cpu_sel3:R/W；位位置：[3]；默认值：0；为通道3.1选择寄存器或CPU指令器配置的gpio输出值：选择CPU指令器。
         */
        uint32_t gpio_out_cpu_sel3: 1;
        /** gpio_out_cpu_sel4:R/W；位位置：[4]；默认值：0；为通道4.1选择寄存器或CPU指令器配置的gpio输出值：选择CPU指令器。
         */
        uint32_t gpio_out_cpu_sel4: 1;
        /** gpio_out_cpu_sel5:R/W；位位置：[5]；默认值：0；为通道5.1选择寄存器或CPU指令器配置的gpio输出值：选择CPU指令器。
         */
        uint32_t gpio_out_cpu_sel5: 1;
        /** gpio_out_cpu_sel6:R/W；位位置：[6]；默认值：0；为通道6.1选择寄存器或CPU指令器配置的gpio输出值：选择CPU指令器。
         */
        uint32_t gpio_out_cpu_sel6: 1;
        /** gpio_out_cpu_sel7：右侧；位位置：[7]；默认值：0；为通道7.1选择寄存器或CPU指令器配置的gpio输出值：选择CPU指令器。
         */
        uint32_t gpio_out_cpu_sel7: 1;
        uint32_t reserved8: 24;
    };
    uint32_t val;
} dedic_gpio_out_cpu_reg_t;

/** gpio_in_dly寄存器类型专用gpio输入延迟配置寄存器
 */
typedef union {
    struct {
        /** gpio_in_dly_ch0:R/W；位位置：[1:0]；默认值：0；配置gpio 0输入延迟。0：无延迟；1： 一个时钟延迟；2： 双时钟延迟；3： 三时钟延迟。
         */
        uint32_t gpio_in_dly_ch0: 2;
        /** gpio_in_dly_ch1:R/W；位位置：[3:2]；默认值：0；配置gpio 1输入延迟。0：无延迟；1： 一个时钟延迟；2： 双时钟延迟；3： 三时钟延迟。
         */
        uint32_t gpio_in_dly_ch1: 2;
        /** gpio_in_dly_ch2:R/W；比特位置：[5:4]；默认值：0；配置gpio 2输入延迟。0：无延迟；1： 一个时钟延迟；2： 双时钟延迟；3： 三时钟延迟。
         */
        uint32_t gpio_in_dly_ch2: 2;
        /** gpio_in_dly_ch3:R/W；位位置：[7:6]；默认值：0；配置gpio 3输入延迟。0：无延迟；1： 一个时钟延迟；2： 双时钟延迟；3： 三时钟延迟。
         */
        uint32_t gpio_in_dly_ch3: 2;
        /** gpio_in_dly_ch4:R/W；比特位置：[9:8]；默认值：0；配置gpio 4输入延迟。0：无延迟；1： 一个时钟延迟；2： 双时钟延迟；3： 三时钟延迟。
         */
        uint32_t gpio_in_dly_ch4: 2;
        /** gpio_in_dly_ch5:R/W；比特位置：[11:10]；默认值：0；配置gpio 5输入延迟。0：无延迟；1： 一个时钟延迟；2： 双时钟延迟；3： 三时钟延迟。
         */
        uint32_t gpio_in_dly_ch5: 2;
        /** gpio_in_dly_ch6:R/W；比特位置：[13:12]；默认值：0；配置gpio 6输入延迟。0：无延迟；1： 一个时钟延迟；2： 双时钟延迟；3： 三时钟延迟。
         */
        uint32_t gpio_in_dly_ch6: 2;
        /** gpio_in_dly_ch7:R/W；比特位置：[15:14]；默认值：0；配置gpio 7输入延迟。0：无延迟；1： 一个时钟延迟；2： 双时钟延迟；3： 三时钟延迟。
         */
        uint32_t gpio_in_dly_ch7: 2;
        uint32_t reserved16: 16;
    };
    uint32_t val;
} dedic_gpio_in_dly_reg_t;

/** gpio_intr_rcgn寄存器类型专用gpio中断生成模式寄存器
 */
typedef union {
    struct {
        /** gpio_intr_mode_ch0:R/W；位位置：[2:0]；默认值：0；配置通道0中断生成模式。0/1：不生成中断；2： 低电平触发；3： 高电平触发；4： 下降沿触发器；5： 上升边缘触发器；6/7：下降和上升边缘触发器。
         */
        uint32_t gpio_intr_mode_ch0: 3;
        /** gpio_intr_mode_ch1:R/W；比特位置：[5:3]；默认值：0；配置通道1中断生成模式。0/1：不生成中断；2： 低电平触发；3： 高电平触发；4： 下降沿触发器；5： 上升边缘触发器；6/7：下降和上升边缘触发器。
         */
        uint32_t gpio_intr_mode_ch1: 3;
        /** gpio_intr_mode_ch2:R/W；位位置：[8:6]；默认值：0；配置通道2中断生成模式。0/1：不生成中断；2： 低电平触发；3： 高电平触发；4： 下降沿触发器；5： 上升边缘触发器；6/7：下降和上升边缘触发器。
         */
        uint32_t gpio_intr_mode_ch2: 3;
        /** gpio_intr_mode_ch3:R/W；比特位置：[11:9]；默认值：0；配置通道3中断生成模式。0/1：不生成中断；2： 低电平触发；3： 高电平触发；4： 下降沿触发器；5： 上升边缘触发器；6/7：下降和上升边缘触发器。
         */
        uint32_t gpio_intr_mode_ch3: 3;
        /** gpio_intr_mode_ch4：读/写；比特位置：[14:12]；默认值：0；配置通道4中断生成模式。0/1：不生成中断；2： 低电平触发；3： 高电平触发；4： 下降沿触发器；5： 上升边缘触发器；6/7：下降和上升边缘触发器。
         */
        uint32_t gpio_intr_mode_ch4: 3;
        /** gpio_intr_mode_ch5:R/W；比特位置：[17:15]；默认值：0；配置通道5中断生成模式。0/1：不生成中断；2： 低电平触发；3： 高电平触发；4： 下降沿触发器；5： 上升边缘触发器；6/7：下降和上升边缘触发器。
         */
        uint32_t gpio_intr_mode_ch5: 3;
        /** gpio_intr_mode_ch6:R/W；比特位置：[20:18]；默认值：0；配置通道6中断生成模式。0/1：不生成中断；2： 低电平触发；3： 高电平触发；4： 下降沿触发器；5： 上升边缘触发器；6/7：下降和上升边缘触发器。
         */
        uint32_t gpio_intr_mode_ch6: 3;
        /** gpio_intr_mode_ch7:R/W；比特位置：[23:21]；默认值：0；配置通道7中断生成模式。0/1：不生成中断；2： 低电平触发；3： 高电平触发；4： 下降沿触发器；5： 上升边缘触发器；6/7：下降和上升边缘触发器。
         */
        uint32_t gpio_intr_mode_ch7: 3;
        uint32_t reserved24: 8;
    };
    uint32_t val;
} dedic_gpio_intr_rcgn_reg_t;


/**状态寄存器*/
/** gpio_out_scan寄存器类型专用gpio输出状态寄存器
 */
typedef union {
    struct {
        /** gpio_out_status:RO；位位置：[7:0]；默认值：0；gpio out值由DEDIC_gpio_out_DRT_REG、DEDIC_GAPIO_out_MSK_REG、DE DIC_gpio_out_IDV_REG配置。
         */
        uint32_t gpio_out_status: 8;
        uint32_t reserved8: 24;
    };
    uint32_t val;
} dedic_gpio_out_scan_reg_t;

/** gpio_in_scan寄存器类型专用gpio输入状态寄存器
 */
typedef union {
    struct {
        /** gpio_in_status:RO；位位置：[7:0]；默认值：0；由DEDIC_gpio_in_DLY_REG配置后的gpio值。
         */
        uint32_t gpio_in_status: 8;
        uint32_t reserved8: 24;
    };
    uint32_t val;
} dedic_gpio_in_scan_reg_t;


/**中断寄存器*/
/** gpio_intr_raw寄存器的类型原始中断状态
 */
typedef union {
    struct {
        /** gpio0_int_raw:RO；位位置：[0]；默认值：0；当专用GPIO 0具有由DEDIC_GPIO_INTR_RCGN_REG配置的电平/边缘变化时，该中断原始位变为高电平。
         */
        uint32_t gpio0_int_raw: 1;
        /** gpio1_int_raw:RO；位位置：[1]；默认值：0；当专用GPIO 1具有由DEDIC_GPIO_INTR_RCGN_REG配置的电平/边缘变化时，该中断原始位变为高电平。
         */
        uint32_t gpio1_int_raw: 1;
        /** gpio2_int_raw:RO；位位置：[2]；默认值：0；当专用GPIO 2具有由DEDIC_GPIO_INTR_RCGN_REG配置的电平/边缘变化时，该中断原始位变为高电平。
         */
        uint32_t gpio2_int_raw: 1;
        /** gpio3_int_raw:RO；位位置：[3]；默认值：0；当专用GPIO 3具有由DEDIC_GPIO_INTR_RCGN_REG配置的电平/边缘变化时，该中断原始位变为高电平。
         */
        uint32_t gpio3_int_raw: 1;
        /** gpio4_int_raw:RO；位位置：[4]；默认值：0；当专用GPIO 4具有由DEDIC_GPIO_INTR_RCGN_REG配置的电平/边缘变化时，该中断原始位变为高电平。
         */
        uint32_t gpio4_int_raw: 1;
        /** gpio5_int_raw:RO；位位置：[5]；默认值：0；当专用GPIO 5具有由DEDIC_GPIO_INTR_RCGN_REG配置的电平/边缘变化时，该中断原始位变为高电平。
         */
        uint32_t gpio5_int_raw: 1;
        /** gpio6_int_raw:RO；位位置：[6]；默认值：0；当专用GPIO 6具有由DEDIC_GPIO_INTR_RCGN_REG配置的电平/边缘变化时，该中断原始位变为高电平。
         */
        uint32_t gpio6_int_raw: 1;
        /** gpio7_it_raw:RO；位位置：[7]；默认值：0；当专用GPIO 7具有由DEDIC_GPIO_INTR_RCGN_REG配置的电平/边缘变化时，该中断原始位变为高电平。
         */
        uint32_t gpio7_int_raw: 1;
        uint32_t reserved8: 24;
    };
    uint32_t val;
} dedic_gpio_intr_raw_reg_t;

/** gpio_intr_rls寄存器类型中断启用位
 */
typedef union {
    struct {
        /** gpio0_int_ena:R/W；位位置：[0]；默认值：0；reg_gpio0_int_st寄存器的此启用位。
         */
        uint32_t gpio0_int_ena: 1;
        /** gpio1_int_ena:R/W；位位置：[1]；默认值：0；reg_gpio1_int_st寄存器的此启用位。
         */
        uint32_t gpio1_int_ena: 1;
        /** gpio2_int_ena:R/W；位位置：[2]；默认值：0；reg_gpio2_int_st寄存器的此启用位。
         */
        uint32_t gpio2_int_ena: 1;
        /** gpio3_int_ena:R/W；位位置：[3]；默认值：0；reg_gpio3_int_st寄存器的此启用位。
         */
        uint32_t gpio3_int_ena: 1;
        /** gpio4_int_ena:R/W；位位置：[4]；默认值：0；reg_gpio4_int_st寄存器的此启用位。
         */
        uint32_t gpio4_int_ena: 1;
        /** gpio5_int_ena:R/W；位位置：[5]；默认值：0；reg_gpio5_int_st寄存器的此启用位。
         */
        uint32_t gpio5_int_ena: 1;
        /** gpio6_int_ena:R/W；位位置：[6]；默认值：0；reg_gpio6_int_st寄存器的此启用位。
         */
        uint32_t gpio6_int_ena: 1;
        /** gpio7_it_ena:R/W；位位置：[7]；默认值：0；reg_gpio7_it_st寄存器的此启用位。
         */
        uint32_t gpio7_int_ena: 1;
        uint32_t reserved8: 24;
    };
    uint32_t val;
} dedic_gpio_intr_rls_reg_t;

/** gpio_intr_st寄存器类型屏蔽中断状态
 */
typedef union {
    struct {
        /** gpio0_int_st:RO；位位置：[0]；默认值：0；这是reg_gpio0_int_ena设置为1时reg_gpio_int_raw的状态位。
         */
        uint32_t gpio0_int_st: 1;
        /** gpio1_int_st:RO；位位置：[1]；默认值：0；这是reg_gpio1_int_ena设置为1时reg_gpiu1_int_raw的状态位。
         */
        uint32_t gpio1_int_st: 1;
        /** gpio2_int_st:RO；位位置：[2]；默认值：0；这是reg_gpio2_int_ena设置为1时reg_gpio2_int_raw的状态位。
         */
        uint32_t gpio2_int_st: 1;
        /** gpio3_int_st:RO；位位置：[3]；默认值：0；这是reg_gpio3_int_ena设置为1时reg_gpio3_int_raw的状态位。
         */
        uint32_t gpio3_int_st: 1;
        /** gpio4_int_st:RO；位位置：[4]；默认值：0；这是reg_gpio_int_ena设置为1时reg_gpiO_int_raw的状态位。
         */
        uint32_t gpio4_int_st: 1;
        /** gpio5_int_st:RO；位位置：[5]；默认值：0；这是reg_gpio5_int_ena设置为1时reg_gpio_int_raw的状态位。
         */
        uint32_t gpio5_int_st: 1;
        /** gpio6_int_st:RO；位位置：[6]；默认值：0；当reg_gpio6_int_ena设置为1时，这是reg_gpio 6_int_raw的状态位。
         */
        uint32_t gpio6_int_st: 1;
        /** gpio7_it_st:RO；位位置：[7]；默认值：0；这是reg_gpio7_int_ena设置为1时reg_gpio 7_int_raw的状态位。
         */
        uint32_t gpio7_int_st: 1;
        uint32_t reserved8: 24;
    };
    uint32_t val;
} dedic_gpio_intr_st_reg_t;

/** gpio_intr_clr寄存器类型中断清除位
 */
typedef union {
    struct {
        /** gpio0_int_clr:WO；位位置：[0]；默认值：0；设置此位以清除reg_gpio0_int_raw中断。
         */
        uint32_t gpio0_int_clr: 1;
        /** gpio1_int_clr:WO；位位置：[1]；默认值：0；设置此位以清除reg_gpio1_int_raw中断。
         */
        uint32_t gpio1_int_clr: 1;
        /** gpio2_int_clr:WO；位位置：[2]；默认值：0；设置此位以清除reg_gpio2_int_raw中断。
         */
        uint32_t gpio2_int_clr: 1;
        /** gpio3_int_clr:WO；位位置：[3]；默认值：0；设置此位以清除reg_gpio3_int_raw中断。
         */
        uint32_t gpio3_int_clr: 1;
        /** gpio4_int_clr:WO；位位置：[4]；默认值：0；设置此位以清除reg_gpio4_int_raw中断。
         */
        uint32_t gpio4_int_clr: 1;
        /** gpio5_int_clr:WO；位位置：[5]；默认值：0；设置此位以清除reg_gpio5_int_raw中断。
         */
        uint32_t gpio5_int_clr: 1;
        /** gpio6_int_clr:WO；位位置：[6]；默认值：0；设置此位以清除reg_gpio6_int_raw中断。
         */
        uint32_t gpio6_int_clr: 1;
        /** gpio7_int_clr:WO；位位置：[7]；默认值：0；设置此位以清除reg_gpio7_it_raw中断。
         */
        uint32_t gpio7_int_clr: 1;
        uint32_t reserved8: 24;
    };
    uint32_t val;
} dedic_gpio_intr_clr_reg_t;

typedef struct {
    volatile dedic_gpio_out_drt_reg_t gpio_out_drt;
    volatile dedic_gpio_out_msk_reg_t gpio_out_msk;
    volatile dedic_gpio_out_idv_reg_t gpio_out_idv;
    volatile dedic_gpio_out_scan_reg_t gpio_out_scan;
    volatile dedic_gpio_out_cpu_reg_t gpio_out_cpu;
    volatile dedic_gpio_in_dly_reg_t gpio_in_dly;
    volatile dedic_gpio_in_scan_reg_t gpio_in_scan;
    volatile dedic_gpio_intr_rcgn_reg_t gpio_intr_rcgn;
    volatile dedic_gpio_intr_raw_reg_t gpio_intr_raw;
    volatile dedic_gpio_intr_rls_reg_t gpio_intr_rls;
    volatile dedic_gpio_intr_st_reg_t gpio_intr_st;
    volatile dedic_gpio_intr_clr_reg_t gpio_intr_clr;
} dedic_dev_t;

_Static_assert(sizeof(dedic_dev_t) == 0x30, "dedic_dev_t should occupy 0x30 bytes in memory");

extern dedic_dev_t DEDIC_GPIO;

#ifdef __cplusplus
}
#endif

