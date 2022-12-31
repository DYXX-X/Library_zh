/**
 *  SPDX文件版权文本：2021浓缩咖啡系统（上海）有限公司
 *
 *  SPDX许可证标识符：Apache-2.0
 */
#pragma once

#include <stdint.h>
#ifdef __cplusplus
extern "C" {
#endif

/**组：预缩放器配置*/
/** clk_cfg寄存器PWM时钟预分频器寄存器的类型。
 */
typedef union {
    struct {
        /** clk_prescale：R/W；位位置：[7:0]；默认值：0；PWM_clk的周期=6.25ns（PWM_clk_PRESCALE+1）
         */
        uint32_t clk_prescale: 8;
        uint32_t reserved_8: 24;
    };
    uint32_t val;
} mcpwm_clk_cfg_reg_t;


/**组：MCPWM计时器配置和状态*/
/** timer_cfg0寄存器类型PWM定时器周期和更新方法配置寄存器。
 */
typedef union {
    struct {
        /** timer_prescale:R/W；位位置：[7:0]；默认值：0；配置PT0_clk的除数，当PWM计时器停止并启动agsin时生效。PT0_clk的周期=PWM_clk的周期（PWM_TIMER_PRESCALE+1）
         */
        uint32_t timer_prescale: 8;
        /** timer_period:R/W；比特位置：[23:8]；默认值：255；PWM定时器的周期阴影寄存器
         */
        uint32_t timer_period: 16;
        /** timer_period_设备方法：R/W；位位置：[25:24]；默认值：0；PWM定时器周期的激活寄存器的更新方法，0：立即，1:TEZ，2：同步，3:TEZ或同步。此处和下方的TEZ表示计时器等于零事件
         */
        uint32_t timer_period_upmethod: 2;
        uint32_t reserved_26: 6;
    };
    uint32_t val;
} mcpwm_timer_cfg0_reg_t;

/** timer_cfg1寄存器类型PWM定时器工作模式和启动/停止控制配置寄存器。
 */
typedef union {
    struct {
        /** timer_start：R/W/SC；位位置：[2:0]；默认值：0；PWM定时器启动和停止控制。0：如果PWM计时器启动，则在TEZ停止；1：如果计时器启动，那么在TEP停止；2：PWM计时器启动并运行；3：计时器在下一个TEZ启动并停止；4：计时器在上一个TEP启动并停止。这里和下面的TEP表示计时器等于周期时发生的事件
         */
        uint32_t timer_start: 3;
        /** timer_mod:R/W；位位置：[4:3]；默认值：0；PWM定时器工作模式，0：冻结，1：增加模式，2：减少模式，3：上下模式
         */
        uint32_t timer_mod: 2;
        uint32_t reserved_5: 27;
    };
    uint32_t val;
} mcpwm_timer_cfg1_reg_t;

/** timer_sync寄存器类型PWM定时器同步功能配置寄存器。
 */
typedef union {
    struct {
        /** timer_synci_en:R/W；位位置：[0]；默认值：0；设置后，启用同步输入事件时的计时器重新加载。
         */
        uint32_t timer_synci_en: 1;
        /** timer_sync_sw:R/W；位位置：[1]；默认值：0；切换此位将触发软件同步。
         */
        uint32_t timer_sync_sw: 1;
        /** timer_synco_sel:R/W；位位置：[3:2]；默认值：0；PWM定时器sync_out选择，0:sync_in，1:TEZ，2:TEP，在切换reg_timer_sync_sw位时将始终生成sync-out
         */
        uint32_t timer_synco_sel: 2;
        /** timer_phase:R/W；比特位置：[19:4]；默认值：0；同步事件时计时器重新加载阶段
         */
        uint32_t timer_phase: 16;
        /** timer_phase_direction:R/W；位位置：[20]；默认值：0；当定时器模式为上下模式时，在发生时间同步事件时配置PWM定时器的方向：0增加，1减少
         */
        uint32_t timer_phase_direction: 1;
        uint32_t reserved_21: 11;
    };
    uint32_t val;
} mcpwm_timer_sync_reg_t;

/** timer_status寄存器的类型PWM计时器状态寄存器。
 */
typedef union {
    struct {
        /** timer_value:RO；比特位置：[15:0]；默认值：0；当前PWM计时器计数器值
         */
        uint32_t timer_value: 16;
        /** timer_direction:RO；位位置：[16]；默认值：0；当前PWM计时器计数器方向，0：递增1：递减
         */
        uint32_t timer_direction: 1;
        uint32_t reserved_17: 15;
    };
    uint32_t val;
} mcpwm_timer_status_reg_t;


/**组：MCPWM定时器的通用配置*/
/** timer_synci_cfg寄存器类型三个PWM定时器的同步输入选择。
 */
typedef union {
    struct {
        /** timer0_syncisel:R/W；位位置：[2:0]；默认值：0；选择PWM时间r0的同步输入，1:PWM时间r0sync_out，2:PWM时间r1 sync_out；3:PWM时间r2 sync_out、4:GPIO矩阵的SYNC0、5:GPIO矩阵中的SYNC1、6:GPIO矩阵上的SYNC2，其他值：未选择同步输入
         */
        uint32_t timer0_syncisel: 3;
        /** timer1_syncisel:R/W；比特位置：[5:3]；默认值：0；选择PWM计时器1的同步输入，1:PWM计时器0 sync_out，2:PWM计时器1 sync_out；3:PWM计时器2 sync_out、4:GPIO矩阵中的SYNC0、5:GPIO矩阵的SYNC1、6:GPIO矩阵上的SYNC2，其他值：未选择同步输入
         */
        uint32_t timer1_syncisel: 3;
        /** timer2_syncisel:R/W；位位置：[8:6]；默认值：0；选择PWM时间2的同步输入，1:PWM时间0 sync_out，2:PWM时间1 sync_out、3:PWM时间2 sync_out；4:GPIO矩阵的SYNC0，5:GPIO矩阵中的SYNC1，6:GPIO矩阵上的SYNC2，其他值：未选择同步输入
         */
        uint32_t timer2_syncisel: 3;
        /** external_synci0_envert:R/W；位位置：[9]；默认值：0；从GPIO矩阵反转SYNC0
         */
        uint32_t external_synci0_invert: 1;
        /** external_synci_invert:R/W；位位置：[10]；默认值：0；从GPIO矩阵反转SYNC1
         */
        uint32_t external_synci1_invert: 1;
        /** external_synci2_invert:R/W；位位置：[11]；默认值：0；从GPIO矩阵反转SYNC2
         */
        uint32_t external_synci2_invert: 1;
        uint32_t reserved_12: 20;
    };
    uint32_t val;
} mcpwm_timer_synci_cfg_reg_t;

/** 运算符类型_timersel寄存器为PWM运算符选择特定的计时器。
 */
typedef union {
    struct {
        /** operator0_timersel:R/W；位位置：[1:0]；默认值：0；选择哪个PWM计时器是PWM运算符的定时基准0，0:timer0，1:timer1，2:timer2
         */
        uint32_t operator0_timersel: 2;
        /** operator1_timersel:R/W；位位置：[3:2]；默认值：0；选择哪个PWM计时器是PWM运算符的定时基准1，0:timer0，1:timer1，2:timer2
         */
        uint32_t operator1_timersel: 2;
        /** operator2_timersel:R/W；比特位置：[5:4]；默认值：0；选择哪个PWM计时器是PWM运算符的定时基准2，0:timer0，1:timer1，2:timer2
         */
        uint32_t operator2_timersel: 2;
        uint32_t reserved_6: 26;
    };
    uint32_t val;
} mcpwm_operator_timersel_reg_t;


/**组：MCPWM操作员配置和状态*/
/** gen_stmp_cfg寄存器类型时间戳寄存器A和B的传输状态和更新方法
 */
typedef union {
    struct {
        /** gen_a_upmeth:R/W；位位置：[3:0]；默认值：0；PWM发生器时间戳A的激活寄存器的更新方法。当所有位设置为0时：立即，当位0设置为1:TEZ时，当位1设置为1:TECP时，当比特2设置为1:sync时，当位元3设置为1时：禁用更新。
         */
        uint32_t gen_a_upmethod: 4;
        /** gen_b_upmeth:R/W；位位置：[7:4]；默认值：0；PWM发生器时间戳B激活寄存器的更新方法。当所有位设置为0时：立即，当位0设置为1:TEZ时，当位1设置为1:TECP时，当比特2设置为1:sync时，当位元3设置为1时：禁用更新。
         */
        uint32_t gen_b_upmethod: 4;
        /** gen_a_shdw_full:R/W/WTC/SC；位位置：[8]；默认值：0；通过硬件设置和重置。如果设置，PWM发生器时间戳A的影子寄存器将被填充，并等待传输到A的活动寄存器。如果清除，则A的活动注册表已用影子寄存器的最新值更新
         */
        uint32_t gen_a_shdw_full: 1;
        /** gen_b_shdw_full:R/W/WTC/SC；位位置：[9]；默认值：0；通过硬件设置和重置。如果设置，PWM发生器时间戳B的影子寄存器将被填充，并等待传输到B的活动寄存器。如果清除，则B的活动注册表已用影子寄存器的最新值更新
         */
        uint32_t gen_b_shdw_full: 1;
        uint32_t reserved_10: 22;
    };
    uint32_t val;
} mcpwm_gen_stmp_cfg_reg_t;

/** 用于定时器戳的gen_tstmp寄存器类型PWM生成器阴影寄存器
 */
typedef union {
    struct {
        /** 发电机：R/W；比特位置：[15:0]；默认值：0；PWM发生器时间戳的影子寄存器
         */
        uint32_t gen: 16;
        uint32_t reserved_16: 16;
    };
    uint32_t val;
} mcpwm_gen_tstmp_reg_t;

/** gen_cfg0寄存器PWM发生器事件T0和T1处理的类型
 */
typedef union {
    struct {
        /** gen_cfg_upmeth:R/W；位位置：[3:0]；默认值：0；PWM发电机激活寄存器配置的更新方法。当所有位设置为0时：立即，当位0设置为1:TEZ时，当位1设置为1:TECP时，当位数2设置为1:sync时，当bit3设置为1时：禁用更新
         */
        uint32_t gen_cfg_upmethod: 4;
        /** gen_t0_sel:R/W；比特位置：[6:4]；默认值：0；PWM发电机事件_t0的源选择立即生效，0：故障事件0，1：故障事件1，2：故障事件2，3：同步事件，4：无
         */
        uint32_t gen_t0_sel: 3;
        /** gen_t1_sel:R/W；比特位置：[9:7]；默认值：0；PWM发电机事件t1的源选择立即生效，0：故障事件0，1：故障事件1，2：故障事件2，3：同步事件，4：无
         */
        uint32_t gen_t1_sel: 3;
        uint32_t reserved_10: 22;
    };
    uint32_t val;
} mcpwm_gen_cfg0_reg_t;

/** 通过软件强制PWM0A和PWM0B输出的发电机强制寄存器许可类型
 */
typedef union {
    struct {
        /** gen_cnture_upmeth:R/W；比特位置：[5:0]；默认值：32；PWM发生器0的连续软件力更新方法。当所有位设置为0时：立即，当位0设置为1:TEZ时，当位1设置为1:TE P时，当位数2设置为1:TEA时，当3设置为1:T B时，当4设置为1:sync时，位5设置为1时：禁用更新。（这里和下面的TEA/B表示当计时器的值等于寄存器A/B的值时生成的事件。）
         */
        uint32_t gen_cntuforce_upmethod: 6;
        /** gen_a_cnture_mode：R/W；位位置：[7:6]；默认值：0；PWM0A的连续软件强制模式。0：禁用，1：低，2：高，3：禁用
         */
        uint32_t gen_a_cntuforce_mode: 2;
        /** gen_b_cnture_mode：R/W；比特位置：[9:8]；默认值：0；PWM0B的连续软件强制模式。0：禁用，1：低，2：高，3：禁用
         */
        uint32_t gen_b_cntuforce_mode: 2;
        /** gen_a_nciforce:R/W；位位置：[10]；默认值：0；触发PWM0A的非连续立即软件强制事件，触发开关将触发强制事件。
         */
        uint32_t gen_a_nciforce: 1;
        /** gen_a_nciforce_mode：R/W；比特位置：[12:11]；默认值：0；PWM0A的非连续立即软件强制模式，0：禁用，1：低，2：高，3：禁用
         */
        uint32_t gen_a_nciforce_mode: 2;
        /** gen_b_nciforce:R/W；位位置：[13]；默认值：0；触发PWM0B的非连续立即软件强制事件，触发开关将触发强制事件。
         */
        uint32_t gen_b_nciforce: 1;
        /** gen_b_nciforce_mode：R/W；比特位置：[15:14]；默认值：0；PWM0B的非连续立即软件强制模式，0：禁用，1：低，2：高，3：禁用
         */
        uint32_t gen_b_nciforce_mode: 2;
        uint32_t reserved_16: 16;
    };
    uint32_t val;
} mcpwm_gen_force_reg_t;

/** 发电机寄存器类型PWM0A上事件触发的动作
 */
typedef union {
    struct {
        /** gen_utez:R/W；位位置：[1:0]；默认值：0；计时器增加时，事件TEZ触发PWM0A上的动作。0：无变化，1：低，2：高，3：切换
         */
        uint32_t gen_utez: 2;
        /** gen_ustep:R/W；位位置：[3:2]；默认值：0；计时器增加时，事件TEP触发PWM0A上的动作。0：无变化，1：低，2：高，3：切换
         */
        uint32_t gen_utep: 2;
        /** gen_utea:R/W；比特位置：[5:4]；默认值：0；定时器增加时，事件TEA触发PWM0A上的动作。0：无变化，1：低，2：高，3：切换
         */
        uint32_t gen_utea: 2;
        /** gen_uteb:R/W；位位置：[7:6]；默认值：0；计时器增加时，事件TEB触发PWM0A上的动作。0：无变化，1：低，2：高，3：切换
         */
        uint32_t gen_uteb: 2;
        /** gen_ut0:R/W；比特位置：[9:8]；默认值：0；计时器增加时，事件_t0触发PWM0A上的动作。0：无变化，1：低，2：高，3：切换
         */
        uint32_t gen_ut0: 2;
        /** gen_ut1:R/W；比特位置：[11:10]；默认值：0；计时器增加时，事件_t1触发PWM0A上的动作。0：无变化，1：低，2：高，3：切换
         */
        uint32_t gen_ut1: 2;
        /** gen_dtez:R/W；比特位置：[13:12]；默认值：0；计时器减少时，事件TEZ触发PWM0A上的动作。0：无变化，1：低，2：高，3：切换
         */
        uint32_t gen_dtez: 2;
        /** gen_dstep:R/W；比特位置：[15:14]；默认值：0；计时器减少时，事件TEP触发PWM0A上的动作。0：无变化，1：低，2：高，3：切换
         */
        uint32_t gen_dtep: 2;
        /** gen_dtea:R/W；比特位置：[17:16]；默认值：0；计时器减少时，事件TEA触发PWM0A上的动作。0：无变化，1：低，2：高，3：切换
         */
        uint32_t gen_dtea: 2;
        /** gen_dteb:R/W；比特位置：[19:18]；默认值：0；计时器减少时，事件TEB触发PWM0A上的动作。0：无变化，1：低，2：高，3：切换
         */
        uint32_t gen_dteb: 2;
        /** gen_dt0:R/W；比特位置：[21:20]；默认值：0；计时器减少时，事件_t0触发PWM0A上的动作。0：无变化，1：低，2：高，3：切换
         */
        uint32_t gen_dt0: 2;
        /** gen_dt1:R/W；比特位置：[23:22]；默认值：0；计时器减少时，事件_t1触发PWM0A上的动作。0：无变化，1：低，2：高，3：切换
         */
        uint32_t gen_dt1: 2;
        uint32_t reserved_24: 8;
    };
    uint32_t val;
} mcpwm_gen_reg_t;

/** dt_cfg寄存器类型PWM发生器空载时间类型选择和配置
 */
typedef union {
    struct {
        /** dt_fed_up方法：R/W；位位置：[3:0]；默认值：0；FED（上升沿延迟）激活寄存器的更新方法。0：立即，当bit0设置为1:tez，当bit1设置为1:step，当bit2设置为1:sync，当bit 3设置为1时：禁用更新
         */
        uint32_t dt_fed_upmethod: 4;
        /** dt_red_upmethod:R/W；位位置：[7:4]；默认值：0；RED（上升沿延迟）活动寄存器的更新方法。0：立即，当bit0设置为1:tez，当bit1设置为1:step，当bit2设置为1:sync，当bit 3设置为1时：禁用更新
         */
        uint32_t dt_red_upmethod: 4;
        /** dt_deb_mode:R/W；位位置：[8]；默认值：0；表中S8，双边缘B模式，0：馈电/红色分别在不同路径上生效，1：馈电/蓝色在B路径上生效；A输出处于旁路或dulpB模式
         */
        uint32_t dt_deb_mode: 1;
        /** dt_a_outswap:R/W；位位置：[9]；默认值：0；表中的S6
         */
        uint32_t dt_a_outswap: 1;
        /** dt_b_outswap:R/W；位位置：[10]；默认值：0；表中S7
         */
        uint32_t dt_b_outswap: 1;
        /** dt_red_insel:R/W；位位置：[11]；默认值：0；表中的S4
         */
        uint32_t dt_red_insel: 1;
        /** dt_fed_insel:R/W；位位置：[12]；默认值：0；表中S5
         */
        uint32_t dt_fed_insel: 1;
        /** dt_red_outinevert:R/W；位位置：[13]；默认值：0；表中的S2
         */
        uint32_t dt_red_outinvert: 1;
        /** dt_fed_outinevert:R/W；位位置：[14]；默认值：0；表中的S3
         */
        uint32_t dt_fed_outinvert: 1;
        /** dt_a_outbypass:R/W；位位置：[15]；默认值：1；表中的S1
         */
        uint32_t dt_a_outbypass: 1;
        /** dt_b_outbypass:R/W；位位置：[16]；默认值：1；表中S0
         */
        uint32_t dt_b_outbypass: 1;
        /** dt_clk_sel:R/W；位位置：[17]；默认值：0；死区时间时钟选择。0:PWM_clk，1:PT_clk
         */
        uint32_t dt_clk_sel: 1;
        uint32_t reserved_18: 14;
    };
    uint32_t val;
} mcpwm_dt_cfg_reg_t;

/** 用于下降沿延迟（fed）的dt_fed_cfg寄存器PWM生成器阴影寄存器的类型。
 */
typedef union {
    struct {
        /** dt_fed:R/W；比特位置：[15:0]；默认值：0；FED的影子寄存器
         */
        uint32_t dt_fed: 16;
        uint32_t reserved_16: 16;
    };
    uint32_t val;
} mcpwm_dt_fed_cfg_reg_t;

/** 用于上升沿延迟（red）的dt_red_cfg寄存器类型PWM生成器阴影寄存器。
 */
typedef union {
    struct {
        /** dt_red:R/W；比特位置：[15:0]；默认值：0；RED的影子寄存器
         */
        uint32_t dt_red: 16;
        uint32_t reserved_16: 16;
    };
    uint32_t val;
} mcpwm_dt_red_cfg_reg_t;

/** 载波类型.cfg寄存器PWM发电机载波启用和配置
 */
typedef union {
    struct {
        /** carrier_en:R/W；位位置：[0]；默认值：0；设置后，载波功能启用。清除后，绕过载波
         */
        uint32_t carrier_en: 1;
        /** 载波预缩放：R/W；比特位置：[4:1]；默认值：0；PWM载波时钟（PC_clk）预缩放值。PC_clk的周期=PWM_clk的周期（PWM_CARRIR_PRESCALE+1）
         */
        uint32_t carrier_prescale: 4;
        /** 承运人责任：R/W；位位置：[7:5]；默认值：0；承运人职责选择。负载=PWM_CARRIR_Duty/8
         */
        uint32_t carrier_duty: 3;
        /** carrier_oshtwth:R/W；位位置：[11:8]；默认值：0；载波周期数中第一脉冲的宽度
         */
        uint32_t carrier_oshtwth: 4;
        /** 载波输出转换：R/W；位位置：[12]；默认值：0；设置后，反转该子模块的PWM0A和PWM0B的输出
         */
        uint32_t carrier_out_invert: 1;
        /** 载波in_invert:R/W；位位置：[13]；默认值：0；设置后，将该子模块的PWM0A和PWM0B的输入反相
         */
        uint32_t carrier_in_invert: 1;
        uint32_t reserved_14: 18;
    };
    uint32_t val;
} mcpwm_carrier_cfg_reg_t;

/** fh_cfg0寄存器类型PWM0A和PWM0B跳闸事件的动作
 */
typedef union {
    struct {
        /** fh_sw_cbc:R/W；位位置：[0]；默认值：0；启用软件强制循环模式动作的寄存器。0：禁用，1：启用
         */
        uint32_t fh_sw_cbc: 1;
        /** fh_f2_cbc:R/W；位位置：[1]；默认值：0；fault_event2将触发逐周期模式动作。0：禁用，1：启用
         */
        uint32_t fh_f2_cbc: 1;
        /** fh_f1_cbc:R/W；位位置：[2]；默认值：0；fault_event1将触发逐周期模式动作。0：禁用，1：启用
         */
        uint32_t fh_f1_cbc: 1;
        /** fh_f0_cbc:R/W；位位置：[3]；默认值：0；fault_event0将触发逐周期模式动作。0：禁用，1：启用
         */
        uint32_t fh_f0_cbc: 1;
        /** fh_sw_ost:R/W；位位置：[4]；默认值：0；启用软件强制单触发模式动作的寄存器。0：禁用，1：启用
         */
        uint32_t fh_sw_ost: 1;
        /** fh_f2_ost:R/W；位位置：[5]；默认值：0；fault_event2将触发单触发模式动作。0：禁用，1：启用
         */
        uint32_t fh_f2_ost: 1;
        /** fh_f1_ost:R/W；位位置：[6]；默认值：0；fault_event1将触发单触发模式动作。0：禁用，1：启用
         */
        uint32_t fh_f1_ost: 1;
        /** fh_f0_ost:R/W；位位置：[7]；默认值：0；fault_event0将触发单触发模式动作。0：禁用，1：启用
         */
        uint32_t fh_f0_ost: 1;
        /** fh_a_cbc_d:R/W；比特位置：[9:8]；默认值：0；当故障事件发生且计时器正在减少时，PWM0A上的循环模式动作。0：不执行任何操作，1：强制低，2：强制高，3：切换
         */
        uint32_t fh_a_cbc_d: 2;
        /** fh_a_cbc_u:R/W；比特位置：[11:10]；默认值：0；当故障事件发生且计时器增加时，PWM0A上的循环模式动作。0：不执行任何操作，1：强制低，2：强制高，3：切换
         */
        uint32_t fh_a_cbc_u: 2;
        /** fh_a_ost_d:R/W；比特位置：[13:12]；默认值：0；当发生故障事件且计时器正在减少时，PWM0A上的单次模式动作。0：不执行任何操作，1：强制低，2：强制高，3：切换
         */
        uint32_t fh_a_ost_d: 2;
        /** fh_a_ost_u:R/W；比特位置：[15:14]；默认值：0；当故障事件发生且计时器增加时，PWM0A上的单次模式动作。0：不执行任何操作，1：强制低，2：强制高，3：切换
         */
        uint32_t fh_a_ost_u: 2;
        /** fh_b_cbc_d:R/W；比特位置：[17:16]；默认值：0；当故障事件发生且计时器正在减少时，PWM0B上的循环模式动作。0：不执行任何操作，1：强制低，2：强制高，3：切换
         */
        uint32_t fh_b_cbc_d: 2;
        /** fh_b_cbc_u:R/W；比特位置：[19:18]；默认值：0；当故障事件发生且计时器增加时，PWM0B上的循环模式动作。0：不执行任何操作，1：强制低，2：强制高，3：切换
         */
        uint32_t fh_b_cbc_u: 2;
        /** fh_b_ost_d:R/W；比特位置：[21:20]；默认值：0；当发生故障事件且计时器正在减少时，PWM0B上的单次模式动作。0：不执行任何操作，1：强制低，2：强制高，3：切换
         */
        uint32_t fh_b_ost_d: 2;
        /** fh_b_ost_u:R/W；比特位置：[23:22]；默认值：0；当故障事件发生且计时器增加时，PWM0B上的单次模式动作。0：不执行任何操作，1：强制低，2：强制高，3：切换
         */
        uint32_t fh_b_ost_u: 2;
        uint32_t reserved_24: 8;
    };
    uint32_t val;
} mcpwm_fh_cfg0_reg_t;

/** fh_cfg1寄存器的类型故障处理程序操作的软件触发器
 */
typedef union {
    struct {
        /** fh_clr_ost:R/W；位位置：[0]；默认值：0；在进行一次射击模式动作时，上升沿将消失
         */
        uint32_t fh_clr_ost: 1;
        /** fh_cbcpulse:R/W；位位置：[2:1]；默认值：0；逐周期模式动作刷新时刻选择。当bit0设置为1:TEZ时，当bit1设置为1:TECP时，当bit0和bit1都设置为0时：停止刷新，当bit0和bit2都设置为1时：在TEP/TEZ刷新
         */
        uint32_t fh_cbcpulse: 2;
        /** fh_force_cbc:R/W；位位置：[3]；默认值：0；触发一个循环一个循环的模式动作
         */
        uint32_t fh_force_cbc: 1;
        /** fh_force_ost:R/W；位位置：[4]；默认值：0；切换（软件否定其值）触发单次模式动作
         */
        uint32_t fh_force_ost: 1;
        uint32_t reserved_5: 27;
    };
    uint32_t val;
} mcpwm_fh_cfg1_reg_t;

/** fh_status寄存器类型故障事件状态。
 */
typedef union {
    struct {
        /** fh_cbc_on:RO；位位置：[0]；默认值：0；通过硬件设置和重置。如果设置，则循环模式操作正在进行
         */
        uint32_t fh_cbc_on: 1;
        /** fh_ost_on:RO；位位置：[1]；默认值：0；通过硬件设置和重置。如果设置，则一次拍摄模式动作正在进行
         */
        uint32_t fh_ost_on: 1;
        uint32_t reserved_2: 30;
    };
    uint32_t val;
} mcpwm_fh_status_reg_t;

/**组：故障检测配置和状态*/
/** 故障检测寄存器类型故障检测配置和状态
 */
typedef union {
    struct {
        /** f0_en:R/W；位位置：[0]；默认值：0；设置后，将启用fault_event0生成
         */
        uint32_t f0_en: 1;
        /** f1_en:R/W；位位置：[1]；默认值：0；设置后，将启用fault_event1生成
         */
        uint32_t f1_en: 1;
        /** f2_en:R/W；位位置：[2]；默认值：0；设置后，将启用fault_event2生成
         */
        uint32_t f2_en: 1;
        /** f0_极：R/W；位位置：[3]；默认值：0；在GPIO矩阵的FAULT2源上设置fault_event0触发极性。0：级别低，1：级别高
         */
        uint32_t f0_pole: 1;
        /** f1_极：R/W；位位置：[4]；默认值：0；在GPIO矩阵的FAULT2源上设置fault_event1触发极性。0：级别低，1：级别高
         */
        uint32_t f1_pole: 1;
        /** f2_极：R/W；位位置：[5]；默认值：0；在GPIO矩阵的FAULT2源上设置fault_event2触发极性。0：级别低，1：级别高
         */
        uint32_t f2_pole: 1;
        /** event_f0:RO；位位置：[6]；默认值：0；通过硬件设置和重置。如果设置，则fault_event0正在运行
         */
        uint32_t event_f0: 1;
        /** event_f1:RO；位位置：[7]；默认值：0；通过硬件设置和重置。如果设置，则fault_event1正在运行
         */
        uint32_t event_f1: 1;
        /** event_f2:RO；位位置：[8]；默认值：0；通过硬件设置和重置。如果设置，则fault_event2正在运行
         */
        uint32_t event_f2: 1;
        uint32_t reserved_9: 23;
    };
    uint32_t val;
} mcpwm_fault_detect_reg_t;


/**组：捕获配置和状态*/
/** cap_timer_cfg寄存器类型配置捕获计时器
 */
typedef union {
    struct {
        /** cap_timer_en:R/W；位位置：[0]；默认值：0；设置后，启用APB_clk下的捕获计时器递增。
         */
        uint32_t cap_timer_en: 1;
        /** cap_synci_en:R/W；位位置：[1]；默认值：0；设置后，将启用捕获计时器同步。
         */
        uint32_t cap_synci_en: 1;
        /** cap_synci_sel:R/W；位位置：[4:2]；默认值：0；捕获模块同步输入选择。0:无，1:timer0同步输出，2:timer1同步输出，3:timer2同步输出，4:GPIO矩阵的SYNC0，5:GPIO矩阵中的SYNC1，6:GPIO矩阵上的SYNC2
         */
        uint32_t cap_synci_sel: 3;
        /** cap_sync_sw:WT；位位置：[5]；默认值：0；当reg_cap_synci_en为1时，write 1将触发捕获计时器同步，捕获计时器将加载相位寄存器中的值。
         */
        uint32_t cap_sync_sw: 1;
        uint32_t reserved_6: 26;
    };
    uint32_t val;
} mcpwm_cap_timer_cfg_reg_t;

/** 捕获计时器同步的cap_timer_phase寄存器相位类型
 */
typedef union {
    struct {
        /** cap_timer_phase:R/W；位位置：[31:0]；默认值：0；捕获计时器同步操作的相位值。
         */
        uint32_t cap_timer_phase: 32;
    };
    uint32_t val;
} mcpwm_cap_timer_phase_reg_t;

/** cap_chn_cfg寄存器类型捕获通道0配置并启用
 */
typedef union {
    struct {
        /** capn_en:R/W；位位置：[0]；默认值：0；设置后，启用通道0上的捕获
         */
        uint32_t capn_en: 1;
        /** capn_mode：R/W；位位置：[2:1]；默认值：0；预缩放后通道0上的捕获边缘。当bit0设置为1时：在负边缘启用捕获，当bit1设置为1：在正边缘启用捕获。
         */
        uint32_t capn_mode: 2;
        /** capn_prescale:R/W；比特位置：[10:3]；默认值：0；CAPn的可能边上的预定值。预缩放值=PWM_CAPn_Prescale+1
         */
        uint32_t capn_prescale: 8;
        /** capn_in_invert:R/W；位位置：[11]；默认值：0；设置后，CAPn形式的GPIO矩阵在预缩放之前被反转
         */
        uint32_t capn_in_invert: 1;
        /** capn_sw:WT；位位置：[12]；默认值：0；写入1将触发通道0上的软件强制捕获
         */
        uint32_t capn_sw: 1;
        uint32_t reserved_13: 19;
    };
    uint32_t val;
} mcpwm_cap_chn_cfg_reg_t;

/** cap_chn寄存器类型chn捕获值状态寄存器
 */
typedef union {
    struct {
        /** capn_value:RO；位位置：[31:0]；默认值：0；通道n上最后一次捕获的值
         */
        uint32_t capn_value: 32;
    };
    uint32_t val;
} mcpwm_cap_chn_reg_t;

/** cap_status寄存器类型上次捕获触发器的边缘
 */
typedef union {
    struct {
        /** cap0_edge：RO；位位置：[0]；默认值：0；通道0上最后一次捕获触发的边缘，0：边缘，1：负边缘
         */
        uint32_t cap0_edge: 1;
        /** cap1_edge:RO；位位置：[1]；默认值：0；通道1上最后一次捕获触发的边缘，0：边缘，1：负边缘
         */
        uint32_t cap1_edge: 1;
        /** cap2_edge:RO；位位置：[2]；默认值：0；通道2上最后一次捕获触发的边缘，0：边缘，1：负边缘
         */
        uint32_t cap2_edge: 1;
        uint32_t reserved_3: 29;
    };
    uint32_t val;
} mcpwm_cap_status_reg_t;


/**组：启用活动寄存器的更新*/
/** update_cfg寄存器类型启用更新。
 */
typedef union {
    struct {
        /** global_up_en:R/W；位位置：[0]；默认值：1；MCPWM模块中所有活动寄存器的全局启用更新
         */
        uint32_t global_up_en: 1;
        /** global_force_up:R/W；位位置：[1]；默认值：0；触发（软件反转其值）将触发MCPWM模块中所有活动寄存器的强制更新
         */
        uint32_t global_force_up: 1;
        /** op0_up_en:R/W；位位置：[2]；默认值：1；当设置且设置了PWM_GLOBAL_UP_EN时，启用PWM运算符0中的活动寄存器更新
         */
        uint32_t op0_up_en: 1;
        /** op0_force_up:R/W；位位置：[3]；默认值：0；触发（软件反转其值）将触发PWM运算器0中活动寄存器的强制更新
         */
        uint32_t op0_force_up: 1;
        /** op1_up_en:R/W；位位置：[4]；默认值：1；当设置且设置了PWM_GLOBAL_UP_EN时，启用PWM运算符1中的活动寄存器更新
         */
        uint32_t op1_up_en: 1;
        /** op1_force_up:R/W；位位置：[5]；默认值：0；触发（软件反转其值）将触发PWM运算器1中活动寄存器的强制更新
         */
        uint32_t op1_force_up: 1;
        /** op2_up_en:R/W；位位置：[6]；默认值：1；当设置且设置了PWM_GLOBAL_UP_EN时，启用PWM运算符2中的活动寄存器更新
         */
        uint32_t op2_up_en: 1;
        /** op2_force_up:R/W；位位置：[7]；默认值：0；触发（软件反转其值）将触发PWM运算器2中活动寄存器的强制更新
         */
        uint32_t op2_force_up: 1;
        uint32_t reserved_8: 24;
    };
    uint32_t val;
} mcpwm_update_cfg_reg_t;


/**组：管理中断*/
/** int_ena寄存器中断启用位的类型
 */
typedef union {
    struct {
        /** timer0_stop_int_ena:R/W；位位置：[0]；默认值：0；计时器0停止时触发的中断的启用位。
         */
        uint32_t timer0_stop_int_ena: 1;
        /** timer1_stop_int_ena:R/W；位位置：[1]；默认值：0；计时器1停止时触发的中断的启用位。
         */
        uint32_t timer1_stop_int_ena: 1;
        /** timer2_stop_int_ena:R/W；位位置：[2]；默认值：0；计时器2停止时触发的中断的启用位。
         */
        uint32_t timer2_stop_int_ena: 1;
        /** timer0_tez_int_ena:R/W；位位置：[3]；默认值：0；PWM定时器0 TEZ事件触发的中断的启用位。
         */
        uint32_t timer0_tez_int_ena: 1;
        /** timer1_tez_int_ena:R/W；位位置：[4]；默认值：0；PWM定时器1 TEZ事件触发的中断的启用位。
         */
        uint32_t timer1_tez_int_ena: 1;
        /** timer2_tez_int_ena:R/W；位位置：[5]；默认值：0；PWM定时器2 TEZ事件触发的中断的启用位。
         */
        uint32_t timer2_tez_int_ena: 1;
        /** timer0_tep_int_ena:R/W；位位置：[6]；默认值：0；PWM定时器0 TEP事件触发的中断的启用位。
         */
        uint32_t timer0_tep_int_ena: 1;
        /** timer1_tep_int_ena:R/W；位位置：[7]；默认值：0；PWM定时器1 TEP事件触发的中断的启用位。
         */
        uint32_t timer1_tep_int_ena: 1;
        /** timer2_tep_int_ena:R/W；位位置：[8]；默认值：0；PWM定时器2 TEP事件触发的中断的启用位。
         */
        uint32_t timer2_tep_int_ena: 1;
        /** fault0_int_ena:R/W；位位置：[9]；默认值：0；fault_event0启动时触发的中断的启用位。
         */
        uint32_t fault0_int_ena: 1;
        /** fault1_int_ena:R/W；位位置：[10]；默认值：0；fault_event1启动时触发的中断的启用位。
         */
        uint32_t fault1_int_ena: 1;
        /** fault2_int_ena:R/W；位位置：[11]；默认值：0；fault_event2启动时触发的中断的启用位。
         */
        uint32_t fault2_int_ena: 1;
        /** fault0_clr_int_ena:R/W；位位置：[12]；默认值：0；fault_event0结束时触发的中断的启用位。
         */
        uint32_t fault0_clr_int_ena: 1;
        /** fault1_clr_int_ena:R/W；位位置：[13]；默认值：0；fault_event1结束时触发的中断的启用位。
         */
        uint32_t fault1_clr_int_ena: 1;
        /** fault2_clr_int_ena:R/W；位位置：[14]；默认值：0；fault_event2结束时触发的中断的启用位。
         */
        uint32_t fault2_clr_int_ena: 1;
        /** op0_tea_int_ena:R/W；位位置：[15]；默认值：0；PWM运算符0 TEA事件触发的中断的启用位
         */
        uint32_t op0_tea_int_ena: 1;
        /** op1_tea_int_ena:R/W；位位置：[16]；默认值：0；PWM运算符1 TEA事件触发的中断的启用位
         */
        uint32_t op1_tea_int_ena: 1;
        /** op2_tea_int_ena:R/W；位位置：[17]；默认值：0；PWM运算符2 TEA事件触发的中断的启用位
         */
        uint32_t op2_tea_int_ena: 1;
        /** op0_teb_int_ena:R/W；位位置：[18]；默认值：0；PWM运算符0 TEB事件触发的中断的启用位
         */
        uint32_t op0_teb_int_ena: 1;
        /** op1_teb_int_ena:R/W；位位置：[19]；默认值：0；PWM运算符1 TEB事件触发的中断的启用位
         */
        uint32_t op1_teb_int_ena: 1;
        /** op2_teb_int_ena:R/W；位位置：[20]；默认值：0；PWM运算符2 TEB事件触发的中断的启用位
         */
        uint32_t op2_teb_int_ena: 1;
        /** fh0_cbc_int_ena:R/W；位位置：[21]；默认值：0；由PWM0上的逐周期模式动作触发的中断的启用位。
         */
        uint32_t fh0_cbc_int_ena: 1;
        /** fh1_cbc_int_ena:R/W；位位置：[22]；默认值：0；由PWM1上的逐周期模式动作触发的中断的启用位。
         */
        uint32_t fh1_cbc_int_ena: 1;
        /** fh2_cbc_int_ena:R/W；位位置：[23]；默认值：0；由PWM2上的逐周期模式动作触发的中断的启用位。
         */
        uint32_t fh2_cbc_int_ena: 1;
        /** fh0_ost_int_ena:R/W；位位置：[24]；默认值：0；由PWM0上的单触发模式动作触发的中断的启用位。
         */
        uint32_t fh0_ost_int_ena: 1;
        /** fh1_ost_int_ena:R/W；位位置：[25]；默认值：0；由PWM1上的单触发模式动作触发的中断的启用位。
         */
        uint32_t fh1_ost_int_ena: 1;
        /** fh2_ost_int_ena:R/W；位位置：[26]；默认值：0；由PWM2上的单触发模式动作触发的中断的启用位。
         */
        uint32_t fh2_ost_int_ena: 1;
        /** cap0_int_ena:R/W；位位置：[27]；默认值：0；通道0上捕获触发的中断的启用位。
         */
        uint32_t cap0_int_ena: 1;
        /** cap1_int_ena:R/W；位位置：[28]；默认值：0；通道1上捕获触发的中断的启用位。
         */
        uint32_t cap1_int_ena: 1;
        /** cap2_int_ena:R/W；位位置：[29]；默认值：0；通道2上捕获触发的中断的启用位。
         */
        uint32_t cap2_int_ena: 1;
        uint32_t reserved_30: 2;
    };
    uint32_t val;
} mcpwm_int_ena_reg_t;

/** int_raw寄存器的类型原始中断状态
 */
typedef union {
    struct {
        /** timer0_stop_int_raw:R/WTC/SS；位位置：[0]；默认值：0；计时器0停止时触发的中断的原始状态位。
         */
        uint32_t timer0_stop_int_raw: 1;
        /** timer1_stop_int_raw:R/WTC/SS；位位置：[1]；默认值：0；计时器1停止时触发的中断的原始状态位。
         */
        uint32_t timer1_stop_int_raw: 1;
        /** timer2_stop_int_raw:R/WTC/SS；位位置：[2]；默认值：0；计时器2停止时触发的中断的原始状态位。
         */
        uint32_t timer2_stop_int_raw: 1;
        /** timer0_tez_int_raw:R/WTC/SS；位位置：[3]；默认值：0；PWM定时器0 TEZ事件触发的中断的原始状态位。
         */
        uint32_t timer0_tez_int_raw: 1;
        /** timer1_tez_int_raw:R/WTC/SS；位位置：[4]；默认值：0；PWM计时器1 TEZ事件触发的中断的原始状态位。
         */
        uint32_t timer1_tez_int_raw: 1;
        /** timer2_tez_int_raw:R/WTC/SS；位位置：[5]；默认值：0；PWM定时器2 TEZ事件触发的中断的原始状态位。
         */
        uint32_t timer2_tez_int_raw: 1;
        /** timer0_tep_int_raw:R/WTC/SS；位位置：[6]；默认值：0；PWM定时器0 TEP事件触发的中断的原始状态位。
         */
        uint32_t timer0_tep_int_raw: 1;
        /** timer1_tep_int_raw:R/WTC/SS；位位置：[7]；默认值：0；PWM计时器1 TEP事件触发的中断的原始状态位。
         */
        uint32_t timer1_tep_int_raw: 1;
        /** timer2_tep_int_raw:R/WTC/SS；位位置：[8]；默认值：0；PWM定时器2 TEP事件触发的中断的原始状态位。
         */
        uint32_t timer2_tep_int_raw: 1;
        /** fault0_int_raw:R/WTC/SS；位位置：[9]；默认值：0；fault_event0启动时触发的中断的原始状态位。
         */
        uint32_t fault0_int_raw: 1;
        /** fault1_int_raw:R/WTC/SS；位位置：[10]；默认值：0；fault_event1启动时触发的中断的原始状态位。
         */
        uint32_t fault1_int_raw: 1;
        /** fault2_int_raw:R/WTC/SS；位位置：[11]；默认值：0；fault_event2启动时触发的中断的原始状态位。
         */
        uint32_t fault2_int_raw: 1;
        /** fault0_clr_int_raw:R/WTC/SS；位位置：[12]；默认值：0；fault_event0结束时触发的中断的原始状态位。
         */
        uint32_t fault0_clr_int_raw: 1;
        /** fault1_clr_int_raw:R/WTC/SS；位位置：[13]；默认值：0；fault_event1结束时触发的中断的原始状态位。
         */
        uint32_t fault1_clr_int_raw: 1;
        /** fault2_clr_int_raw:R/WTC/SS；位位置：[14]；默认值：0；fault_event2结束时触发的中断的原始状态位。
         */
        uint32_t fault2_clr_int_raw: 1;
        /** op0_tea_int_raw:R/WTC/SS；位位置：[15]；默认值：0；PWM运算符0 TEA事件触发的中断的原始状态位
         */
        uint32_t op0_tea_int_raw: 1;
        /** op1_tea_int_raw:R/WTC/SS；位位置：[16]；默认值：0；PWM运算符1 TEA事件触发的中断的原始状态位
         */
        uint32_t op1_tea_int_raw: 1;
        /** op2_tea_int_raw:R/WTC/SS；位位置：[17]；默认值：0；PWM运算符2 TEA事件触发的中断的原始状态位
         */
        uint32_t op2_tea_int_raw: 1;
        /** op0_teb_int_raw:R/WTC/SS；位位置：[18]；默认值：0；PWM运算符0 TEB事件触发的中断的原始状态位
         */
        uint32_t op0_teb_int_raw: 1;
        /** op1_teb_int_raw:R/WTC/SS；位位置：[19]；默认值：0；PWM运算符1 TEB事件触发的中断的原始状态位
         */
        uint32_t op1_teb_int_raw: 1;
        /** op2_teb_int_raw:R/WTC/SS；位位置：[20]；默认值：0；PWM运算符2 TEB事件触发的中断的原始状态位
         */
        uint32_t op2_teb_int_raw: 1;
        /** fh0_cbc_int_raw:R/WTC/SS；位位置：[21]；默认值：0；由PWM0上的逐周期模式动作触发的中断的原始状态位。
         */
        uint32_t fh0_cbc_int_raw: 1;
        /** fh1_cbc_int_raw:R/WTC/SS；位位置：[22]；默认值：0；由PWM1上的逐周期模式动作触发的中断的原始状态位。
         */
        uint32_t fh1_cbc_int_raw: 1;
        /** fh2_cbc_int_raw:R/WTC/SS；位位置：[23]；默认值：0；由PWM2上的逐周期模式动作触发的中断的原始状态位。
         */
        uint32_t fh2_cbc_int_raw: 1;
        /** fh0_ost_int_raw:R/WTC/SS；位位置：[24]；默认值：0；由PWM0上的单触发模式动作触发的中断的原始状态位。
         */
        uint32_t fh0_ost_int_raw: 1;
        /** fh1_ost_int_raw:R/WTC/SS；位位置：[25]；默认值：0；由PWM1上的单触发模式动作触发的中断的原始状态位。
         */
        uint32_t fh1_ost_int_raw: 1;
        /** fh2_ost_int_raw:R/WTC/SS；位位置：[26]；默认值：0；由PWM2上的单触发模式动作触发的中断的原始状态位。
         */
        uint32_t fh2_ost_int_raw: 1;
        /** cap0_int_raw:R/WTC/SS；位位置：[27]；默认值：0；通道0上捕获触发的中断的原始状态位。
         */
        uint32_t cap0_int_raw: 1;
        /** cap1_int_raw:R/WTC/SS；位位置：[28]；默认值：0；通道1上捕获触发的中断的原始状态位。
         */
        uint32_t cap1_int_raw: 1;
        /** cap2_int_raw:R/WTC/SS；位位置：[29]；默认值：0；通道2上捕获触发的中断的原始状态位。
         */
        uint32_t cap2_int_raw: 1;
        uint32_t reserved_30: 2;
    };
    uint32_t val;
} mcpwm_int_raw_reg_t;

/** int_st寄存器类型屏蔽中断状态
 */
typedef union {
    struct {
        /** timer0_stop_int_st:RO；位位置：[0]；默认值：0；计时器0停止时触发的中断的屏蔽状态位。
         */
        uint32_t timer0_stop_int_st: 1;
        /** timer1_stop_int_st:RO；位位置：[1]；默认值：0；计时器1停止时触发的中断的屏蔽状态位。
         */
        uint32_t timer1_stop_int_st: 1;
        /** timer2_stop_int_st:RO；位位置：[2]；默认值：0；计时器2停止时触发的中断的屏蔽状态位。
         */
        uint32_t timer2_stop_int_st: 1;
        /** timer0_tez_int_st:RO；位位置：[3]；默认值：0；PWM定时器0 TEZ事件触发的中断的屏蔽状态位。
         */
        uint32_t timer0_tez_int_st: 1;
        /** timer1_tez_int_st:RO；位位置：[4]；默认值：0；PWM定时器1 TEZ事件触发的中断的屏蔽状态位。
         */
        uint32_t timer1_tez_int_st: 1;
        /** timer2_tez_int_st:RO；位位置：[5]；默认值：0；PWM定时器2 TEZ事件触发的中断的屏蔽状态位。
         */
        uint32_t timer2_tez_int_st: 1;
        /** timer0_tep_int_st:RO；位位置：[6]；默认值：0；PWM定时器0 TEP事件触发的中断的屏蔽状态位。
         */
        uint32_t timer0_tep_int_st: 1;
        /** 时间r1_tep_int_st:RO；位位置：[7]；默认值：0；PWM定时器1 TEP事件触发的中断的屏蔽状态位。
         */
        uint32_t timer1_tep_int_st: 1;
        /** timer2_tep_int_st:RO；位位置：[8]；默认值：0；PWM定时器2 TEP事件触发的中断的屏蔽状态位。
         */
        uint32_t timer2_tep_int_st: 1;
        /** fault0_int_st:RO；位位置：[9]；默认值：0；fault_event0启动时触发的中断的屏蔽状态位。
         */
        uint32_t fault0_int_st: 1;
        /** fault1_int_st:RO；位位置：[10]；默认值：0；fault_event1启动时触发的中断的屏蔽状态位。
         */
        uint32_t fault1_int_st: 1;
        /** fault2_int_st:RO；位位置：[11]；默认值：0；fault_event2启动时触发的中断的屏蔽状态位。
         */
        uint32_t fault2_int_st: 1;
        /** fault0_clr_int_st:RO；位位置：[12]；默认值：0；fault_event0结束时触发的中断的屏蔽状态位。
         */
        uint32_t fault0_clr_int_st: 1;
        /** fault1_clr_int_st:RO；位位置：[13]；默认值：0；fault_event1结束时触发的中断的屏蔽状态位。
         */
        uint32_t fault1_clr_int_st: 1;
        /** fault2_clr_int_st:RO；位位置：[14]；默认值：0；fault_event2结束时触发的中断的屏蔽状态位。
         */
        uint32_t fault2_clr_int_st: 1;
        /** op0_tea_int_st:RO；位位置：[15]；默认值：0；PWM运算符0 TEA事件触发的中断的屏蔽状态位
         */
        uint32_t op0_tea_int_st: 1;
        /** op1_tea_int_st:RO；位位置：[16]；默认值：0；PWM运算符1 TEA事件触发的中断的屏蔽状态位
         */
        uint32_t op1_tea_int_st: 1;
        /** op2_tea_int_st:RO；位位置：[17]；默认值：0；PWM运算符2 TEA事件触发的中断的屏蔽状态位
         */
        uint32_t op2_tea_int_st: 1;
        /** op0_teb_int_st:RO；位位置：[18]；默认值：0；PWM运算符0 TEB事件触发的中断的屏蔽状态位
         */
        uint32_t op0_teb_int_st: 1;
        /** op1_teb_int_st:RO；位位置：[19]；默认值：0；PWM运算符1 TEB事件触发的中断的屏蔽状态位
         */
        uint32_t op1_teb_int_st: 1;
        /** op2_teb_int_st:RO；位位置：[20]；默认值：0；PWM运算符2 TEB事件触发的中断的屏蔽状态位
         */
        uint32_t op2_teb_int_st: 1;
        /** fh0_cbc_int_st:RO；位位置：[21]；默认值：0；由PWM0上的逐周期模式动作触发的中断的屏蔽状态位。
         */
        uint32_t fh0_cbc_int_st: 1;
        /** fh1_cbc_int_st:RO；位位置：[22]；默认值：0；由PWM1上的逐周期模式动作触发的中断的屏蔽状态位。
         */
        uint32_t fh1_cbc_int_st: 1;
        /** fh2_cbc_int_st:RO；位位置：[23]；默认值：0；由PWM2上的逐周期模式动作触发的中断的屏蔽状态位。
         */
        uint32_t fh2_cbc_int_st: 1;
        /** fh0_ost_int_st:RO；位位置：[24]；默认值：0；由PWM0上的单触发模式动作触发的中断的屏蔽状态位。
         */
        uint32_t fh0_ost_int_st: 1;
        /** fh1_ost_int_st:RO；位位置：[25]；默认值：0；由PWM1上的单触发模式动作触发的中断的屏蔽状态位。
         */
        uint32_t fh1_ost_int_st: 1;
        /** fh2_ost_int_st:RO；位位置：[26]；默认值：0；PWM2上的单触发模式动作触发的中断的屏蔽状态位。
         */
        uint32_t fh2_ost_int_st: 1;
        /** cap0_int_st:RO；位位置：[27]；默认值：0；通道0上捕获触发的中断的屏蔽状态位。
         */
        uint32_t cap0_int_st: 1;
        /** cap1_int_st:RO；位位置：[28]；默认值：0；通道1上捕获触发的中断的屏蔽状态位。
         */
        uint32_t cap1_int_st: 1;
        /** cap2_int_st:RO；位位置：[29]；默认值：0；通道2上捕获触发的中断的屏蔽状态位。
         */
        uint32_t cap2_int_st: 1;
        uint32_t reserved_30: 2;
    };
    uint32_t val;
} mcpwm_int_st_reg_t;

/** int_clr寄存器类型中断清除位
 */
typedef union {
    struct {
        /** timer0_stop_int_clr:WT；位位置：[0]；默认值：0；设置此位以清除计时器0停止时触发的中断。
         */
        uint32_t timer0_stop_int_clr: 1;
        /** timer1_stop_int_clr:WT；位位置：[1]；默认值：0；设置此位以清除计时器1停止时触发的中断。
         */
        uint32_t timer1_stop_int_clr: 1;
        /** timer2_stop_int_clr:WT；位位置：[2]；默认值：0；设置此位以清除计时器2停止时触发的中断。
         */
        uint32_t timer2_stop_int_clr: 1;
        /** timer0_tez_int_clr:WT；位位置：[3]；默认值：0；设置此位以清除PWM定时器0 TEZ事件触发的中断。
         */
        uint32_t timer0_tez_int_clr: 1;
        /** 时间r1_tez_int_clr:WT；位位置：[4]；默认值：0；设置此位以清除PWM定时器1 TEZ事件触发的中断。
         */
        uint32_t timer1_tez_int_clr: 1;
        /** timer2_tez_int_clr:WT；位位置：[5]；默认值：0；设置此位以清除PWM定时器2 TEZ事件触发的中断。
         */
        uint32_t timer2_tez_int_clr: 1;
        /** timer0_tep_int_clr:WT；位位置：[6]；默认值：0；设置此位以清除PWM定时器0 TEP事件触发的中断。
         */
        uint32_t timer0_tep_int_clr: 1;
        /** 时间r1_tep_int_clr:WT；位位置：[7]；默认值：0；设置此位以清除PWM定时器1 TEP事件触发的中断。
         */
        uint32_t timer1_tep_int_clr: 1;
        /** 时间r2_tep_int_clr:WT；位位置：[8]；默认值：0；设置此位以清除PWM定时器2 TEP事件触发的中断。
         */
        uint32_t timer2_tep_int_clr: 1;
        /** fault0_int_clr:WT；位位置：[9]；默认值：0；设置此位以清除fault_event0启动时触发的中断。
         */
        uint32_t fault0_int_clr: 1;
        /** fault1_int_clr:WT；位位置：[10]；默认值：0；设置此位以清除fault_event1启动时触发的中断。
         */
        uint32_t fault1_int_clr: 1;
        /** fault2_int_clr:WT；位位置：[11]；默认值：0；设置此位以清除fault_event2启动时触发的中断。
         */
        uint32_t fault2_int_clr: 1;
        /** fault0_clr_int_clr:WT；位位置：[12]；默认值：0；设置此位以清除fault_event0结束时触发的中断。
         */
        uint32_t fault0_clr_int_clr: 1;
        /** fault1_clr_int_clr:WT；位位置：[13]；默认值：0；设置此位以清除fault_event1结束时触发的中断。
         */
        uint32_t fault1_clr_int_clr: 1;
        /** fault2_clr_int_clr:WT；位位置：[14]；默认值：0；设置此位以清除fault_event2结束时触发的中断。
         */
        uint32_t fault2_clr_int_clr: 1;
        /** op0_tea_int_clr:WT；位位置：[15]；默认值：0；设置此位以清除PWM操作员0 TEA事件触发的中断
         */
        uint32_t op0_tea_int_clr: 1;
        /** op1_tea_int_clr:WT；位位置：[16]；默认值：0；设置此位以清除PWM操作员1 TEA事件触发的中断
         */
        uint32_t op1_tea_int_clr: 1;
        /** op2_tea_int_clr:WT；位位置：[17]；默认值：0；设置此位以清除PWM操作员2 TEA事件触发的中断
         */
        uint32_t op2_tea_int_clr: 1;
        /** op0_teb_int_clr:WT；位位置：[18]；默认值：0；设置此位以清除PWM操作员0 TEB事件触发的中断
         */
        uint32_t op0_teb_int_clr: 1;
        /** op1_teb_int_clr:WT；位位置：[19]；默认值：0；设置此位以清除PWM操作员1 TEB事件触发的中断
         */
        uint32_t op1_teb_int_clr: 1;
        /** op2_teb_int_clr:WT；位位置：[20]；默认值：0；设置此位以清除PWM操作员2 TEB事件触发的中断
         */
        uint32_t op2_teb_int_clr: 1;
        /** fh0_cbc_int_clr:WT；位位置：[21]；默认值：0；设置此位以清除由PWM0上的逐周期模式动作触发的中断。
         */
        uint32_t fh0_cbc_int_clr: 1;
        /** fh1_cbc_int_clr:WT；位位置：[22]；默认值：0；设置该位以清除由PWM1上的逐周期模式动作触发的中断。
         */
        uint32_t fh1_cbc_int_clr: 1;
        /** fh2_cbc_int_clr:WT；位位置：[23]；默认值：0；设置此位以清除由PWM2上的逐周期模式动作触发的中断。
         */
        uint32_t fh2_cbc_int_clr: 1;
        /** fh0_ost_int_clr:WT；位位置：[24]；默认值：0；设置此位以清除由PWM0上的单次模式动作触发的中断。
         */
        uint32_t fh0_ost_int_clr: 1;
        /** fh1_ost_int_clr:WT；位位置：[25]；默认值：0；设置该位以清除由PWM1上的单触发模式动作触发的中断。
         */
        uint32_t fh1_ost_int_clr: 1;
        /** fh2_ost_int_clr:WT；位位置：[26]；默认值：0；设置该位以清除由PWM2上的单触发模式动作触发的中断。
         */
        uint32_t fh2_ost_int_clr: 1;
        /** cap0_int_clr:WT；位位置：[27]；默认值：0；设置此位以清除通道0上捕获触发的中断。
         */
        uint32_t cap0_int_clr: 1;
        /** cap1_int_clr:WT；位位置：[28]；默认值：0；设置此位以清除通道1上捕获触发的中断。
         */
        uint32_t cap1_int_clr: 1;
        /** cap2_int_clr:WT；位位置：[29]；默认值：0；设置此位以清除通道2上捕获触发的中断。
         */
        uint32_t cap2_int_clr: 1;
        uint32_t reserved_30: 2;
    };
    uint32_t val;
} mcpwm_int_clr_reg_t;


/**组：MCMCPWM APB配置寄存器*/
/** clk寄存器类型MCPWM APB配置寄存器
 */
typedef union {
    struct {
        /** clk_en:R/W；位位置：[0]；默认值：0；强制打开此寄存器文件的时钟
         */
        uint32_t clk_en: 1;
        uint32_t reserved_1: 31;
    };
    uint32_t val;
} mcpwm_clk_reg_t;


/**组：版本寄存器*/
/** 版本寄存器类型版本寄存器。
 */
typedef union {
    struct {
        /** 日期：R/W；位位置：[27:0]；默认值：34632240；此注册文件的版本
         */
        uint32_t date: 28;
        uint32_t reserved_28: 4;
    };
    uint32_t val;
} mcpwm_version_reg_t;


typedef struct {
    mcpwm_timer_cfg0_reg_t timer_cfg0;
    mcpwm_timer_cfg1_reg_t timer_cfg1;
    mcpwm_timer_sync_reg_t timer_sync;
    mcpwm_timer_status_reg_t timer_status;
} mcpwm_timer_regs_t;

typedef struct {
    mcpwm_gen_stmp_cfg_reg_t gen_stmp_cfg;
    mcpwm_gen_tstmp_reg_t timestamp[2];
    mcpwm_gen_cfg0_reg_t gen_cfg0;
    mcpwm_gen_force_reg_t gen_force;
    mcpwm_gen_reg_t generator[2];
    mcpwm_dt_cfg_reg_t dt_cfg;
    mcpwm_dt_fed_cfg_reg_t dt_fed_cfg;
    mcpwm_dt_red_cfg_reg_t dt_red_cfg;
    mcpwm_carrier_cfg_reg_t carrier_cfg;
    mcpwm_fh_cfg0_reg_t fh_cfg0;
    mcpwm_fh_cfg1_reg_t fh_cfg1;
    mcpwm_fh_status_reg_t fh_status;
} mcpwm_operator_reg_t;

typedef struct {
    volatile mcpwm_clk_cfg_reg_t clk_cfg;
    volatile mcpwm_timer_regs_t timer[3];
    volatile mcpwm_timer_synci_cfg_reg_t timer_synci_cfg;
    volatile mcpwm_operator_timersel_reg_t operator_timersel;
    volatile mcpwm_operator_reg_t operators[3];
    volatile mcpwm_fault_detect_reg_t fault_detect;
    volatile mcpwm_cap_timer_cfg_reg_t cap_timer_cfg;
    volatile mcpwm_cap_timer_phase_reg_t cap_timer_phase;
    volatile mcpwm_cap_chn_cfg_reg_t cap_chn_cfg[3];
    volatile mcpwm_cap_chn_reg_t cap_chn[3];
    volatile mcpwm_cap_status_reg_t cap_status;
    volatile mcpwm_update_cfg_reg_t update_cfg;
    volatile mcpwm_int_ena_reg_t int_ena;
    volatile mcpwm_int_raw_reg_t int_raw;
    volatile mcpwm_int_st_reg_t int_st;
    volatile mcpwm_int_clr_reg_t int_clr;
    volatile mcpwm_clk_reg_t clk;
    volatile mcpwm_version_reg_t version;
} mcpwm_dev_t;

extern mcpwm_dev_t MCPWM0;
extern mcpwm_dev_t MCPWM1;

#ifndef __cplusplus
_Static_assert(sizeof(mcpwm_dev_t) == 0x128, "Invalid size of mcpwm_dev_t structure");
#endif

#ifdef __cplusplus
}
#endif

