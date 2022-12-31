/** 版权所有2021 Espressif Systems（Shanghai）PTE LTD
 *
 *  根据Apache许可证2.0版（“许可证”）获得许可；除非符合许可证，否则不得使用此文件。您可以在以下地址获取许可证副本：
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  除非适用法律要求或书面同意，否则根据许可证分发的软件是按“原样”分发的，无任何明示或暗示的担保或条件。有关许可证下权限和限制的具体语言，请参阅许可证。
 */
#pragma once

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**组：配置寄存器*/
/** un_conf0寄存器类型单元n的配置寄存器0
 */
typedef union {
    struct {
        /** 过滤器_阈值_运行：R/W；位位置：[9:0]；默认值：16；这将设置滤波器的最大阈值（APB_CLK周期）。
         *
         *  启用滤波器时，宽度小于此值的任何脉冲都将被忽略。
         */
        uint32_t filter_thres_un: 10;
        /** 过滤器_en_un:R/W；位位置：[10]；默认值：1；这是单元n输入滤波器的启用位。
         */
        uint32_t filter_en_un: 1;
        /** thr_zero_en_un:R/W；位位置：[11]；默认值：1；这是单元n的零比较器的启用位。
         */
        uint32_t thr_zero_en_un: 1;
        /** thr_h_lim_en_un:R/W；位位置：[12]；默认值：1；这是单元n的thr_hl_lim比较器的启用位。
         */
        uint32_t thr_h_lim_en_un: 1;
        /** thr_l_lim_en_un:R/W；位位置：[13]；默认值：1；这是单元n的thr_l_lim比较器的启用位。
         */
        uint32_t thr_l_lim_en_un: 1;
        /** thr_threes0_en_un:R/W；位位置：[14]；默认值：0；这是单元n的thres0比较器的启用位。
         */
        uint32_t thr_thres0_en_un: 1;
        /** thr_threes1_en_un:R/W；位位置：[15]；默认值：0；这是单元n的thres1比较器的启用位。
         */
        uint32_t thr_thres1_en_un: 1;
        /** ch0_neg_mode_un:R/W；比特位置：[17:16]；默认值：0；该寄存器设置通道0的信号输入检测到负边缘时的行为。
         *
         *  1： 增加计数器；2： 减小计数器；0，3:对计数器无影响
         */
        uint32_t ch0_neg_mode_un: 2;
        /** ch0_pos_mode_un:R/W；比特位置：[19:18]；默认值：0；该寄存器设置通道0的信号输入检测到正边缘时的行为。
         *
         *  1： 增加计数器；2： 减小计数器；0，3:对计数器无影响
         */
        uint32_t ch0_pos_mode_un: 2;
        /** ch0_hctrl_mode_un:R/W；比特位置：[21:20]；默认值：0；该寄存器配置当控制信号为高时如何修改CHn_POS_MODE/CHn_NEG_MODE设置。
         *
         *  0：无修改；1： 反转行为（增加->减少，减少->增加）；2、3：禁止计数器修改
         */
        uint32_t ch0_hctrl_mode_un: 2;
        /** ch0_lctrl_mode_un:R/W；比特位置：[23:22]；默认值：0；该寄存器配置控制信号为低时如何修改CHn_POS_MODE/CHn_NEG_MODE设置。
         *
         *  0：无修改；1： 反转行为（增加->减少，减少->增加）；2、3：禁止计数器修改
         */
        uint32_t ch0_lctrl_mode_un: 2;
        /** ch1_neg_mode_un:R/W；位位置：[25:24]；默认值：0；该寄存器设置通道1的信号输入检测到负边缘时的行为。
         *
         *  1： 增加计数器；2： 递减计数器；0，3:对计数器无影响
         */
        uint32_t ch1_neg_mode_un: 2;
        /** ch1_pos_mode_un:R/W；位位置：[27:26]；默认值：0；该寄存器设置通道1的信号输入检测到正边缘时的行为。
         *
         *  1： 增加计数器；2： 递减计数器；0，3:对计数器无影响
         */
        uint32_t ch1_pos_mode_un: 2;
        /** ch1_hctrl_mode_un:R/W；位位置：[29:28]；默认值：0；该寄存器配置当控制信号为高时如何修改CHn_POS_MODE/CHn_NEG_MODE设置。
         *
         *  0：无修改；1： 反转行为（增加->减少，减少->增加）；2、3：禁止计数器修改
         */
        uint32_t ch1_hctrl_mode_un: 2;
        /** ch1_lctrl_mode_un:R/W；比特位置：[31:30]；默认值：0；该寄存器配置控制信号为低时如何修改CHn_POS_MODE/CHn_NEG_MODE设置。
         *
         *  0：无修改；1： 反转行为（增加->减少，减少->增加）；2、3：禁止计数器修改
         */
        uint32_t ch1_lctrl_mode_un: 2;
    };
    uint32_t val;
} pcnt_un_conf0_reg_t;

/** un_conf1寄存器类型单元n的配置寄存器1
 */
typedef union {
    struct {
        /** cnt_threes0_un:R/W；比特位置：[15:0]；默认值：0；该寄存器用于配置单元n的thres0值。
         */
        uint32_t cnt_thres0_un: 16;
        /** cnt_threes1_un:R/W；比特位置：[31:16]；默认值：0；该寄存器用于配置单元n的thres1值。
         */
        uint32_t cnt_thres1_un: 16;
    };
    uint32_t val;
} pcnt_un_conf1_reg_t;

/** un_conf2寄存器类型单元n的配置寄存器2
 */
typedef union {
    struct {
        /** cnt_h_lim_un:R/W；比特位置：[15:0]；默认值：0；此寄存器用于配置单元n的thr_hl_lim值。
         */
        uint32_t cnt_h_lim_un: 16;
        /** cnt_l_lim_un:R/W；比特位置：[31:16]；默认值：0；该寄存器用于配置单元n的thr_l_lim值。
         */
        uint32_t cnt_l_lim_un: 16;
    };
    uint32_t val;
} pcnt_un_conf2_reg_t;


/** ctrl寄存器类型所有计数器的控制寄存器
 */
typedef union {
    struct {
        /** 脉冲_ cnt_rst_u0：R/W；位位置：[0]；默认值：1；设置此位以清除单元0的计数器。
         */
        uint32_t pulse_cnt_rst_u0: 1;
        /** cnt_use_u0:R/W；位位置：[1]；默认值：0；设置此位以冻结单元0的计数器。
         */
        uint32_t cnt_pause_u0: 1;
        /** 脉冲_ cnt_rst_u1:R/W；位位置：[2]；默认值：1；设置此位以清除第一单元的计数器。
         */
        uint32_t pulse_cnt_rst_u1: 1;
        /** cnt_use_u1:R/W；位位置：[3]；默认值：0；设置此位以冻结第一单元的计数器。
         */
        uint32_t cnt_pause_u1: 1;
        /** 脉冲_ cnt_rst_u2：R/W；位位置：[4]；默认值：1；设置此位以清除第二单元的计数器。
         */
        uint32_t pulse_cnt_rst_u2: 1;
        /** cnt_use_u2:R/W；位位置：[5]；默认值：0；设置此位以冻结第二单元的计数器。
         */
        uint32_t cnt_pause_u2: 1;
        /** 脉冲_ cnt_rst_u3：R/W；位位置：[6]；默认值：1；设置此位以清除第三单元的计数器。
         */
        uint32_t pulse_cnt_rst_u3: 1;
        /** cnt_use_u3:R/W；位位置：[7]；默认值：0；设置此位以冻结第三单元的计数器。
         */
        uint32_t cnt_pause_u3: 1;
        uint32_t reserved_8: 8;
        /** clk_en:R/W；位位置：[16]；默认值：0；PCNT模块的寄存器时钟门启用信号。1： 寄存器可以由应用程序读取和写入。0：应用程序无法读取或写入寄存器
         */
        uint32_t clk_en: 1;
        uint32_t reserved_17: 15;
    };
    uint32_t val;
} pcnt_ctrl_reg_t;


/**组：状态寄存器*/
/** un_cnt寄存器类型单位n的计数器值
 */
typedef union {
    struct {
        /** pulse_cnt_un:RO；比特位置：[15:0]；默认值：0；该寄存器存储单元n的当前脉冲计数值。
         */
        uint32_t pulse_cnt_un: 16;
        uint32_t reserved_16: 16;
    };
    uint32_t val;
} pcnt_un_cnt_reg_t;

/** 非状态寄存器类型PNCT UNITn状态寄存器
 */
typedef union {
    struct {
        /** cnt_thr_zero_mode_un:RO；位位置：[1:0]；默认值：0；对应于0.0的PCNT_Un的脉冲计数器状态：脉冲计数器从正变为0.1：脉冲计数器由负变为0.2：脉冲计数器为负。3： 脉冲计数器为正。
         */
        uint32_t cnt_thr_zero_mode_un: 2;
        /** cnt_thr_threes1_lat_un:RO；位位置：[2]；默认值：0；阈值事件中断有效时，PCNT_Un的thres1事件的锁存值。1： 电流脉冲计数器等于thres1，thres1事件有效。0:其他
         */
        uint32_t cnt_thr_thres1_lat_un: 1;
        /** cnt_thr_threes0_lat_un:RO；位位置：[3]；默认值：0；阈值事件中断有效时，PCNT_Un的thres0事件的锁存值。1： 当前脉冲计数器等于thres0，thres0事件有效。0:其他
         */
        uint32_t cnt_thr_thres0_lat_un: 1;
        /** cnt_hr_l_lim_lat_un:RO；位位置：[4]；默认值：0；阈值事件中断有效时，PCNT_Un的下限事件的锁存值。1： 电流脉冲计数器等于thrl_lim，下限事件有效。0:其他
         */
        uint32_t cnt_thr_l_lim_lat_un: 1;
        /** cnt_thr_hl_lim_lat_un:RO；位位置：[5]；默认值：0；阈值事件中断有效时，PCNT_Un的上限事件的锁存值。1： 当前脉冲计数器等于thr_。0:其他
         */
        uint32_t cnt_thr_h_lim_lat_un: 1;
        /** cnt_thr_zero_lat_un:RO；位位置：[6]；默认值：0；阈值事件中断有效时，PCNT_Un的零阈值事件的锁存值。1： 电流脉冲计数器等于0并且零阈值事件是有效的。0:其他
         */
        uint32_t cnt_thr_zero_lat_un: 1;
        uint32_t reserved_7: 25;
    };
    uint32_t val;
} pcnt_un_status_reg_t;


/**组：中断寄存器*/
/** int_raw寄存器类型中断原始状态寄存器
 */
typedef union {
    struct {
        /** cnt_thr_event_u0_int_raw:RO；位位置：[0]；默认值：0；PCNT_CNT_THR_EVENT_U0_INT中断的原始中断状态位。
         */
        uint32_t cnt_thr_event_u0_int_raw: 1;
        /** cnt_thr_event_u1_int_raw:RO；位位置：[1]；默认值：0；PCNT_CNT_THR_EVENT_U1_INT中断的原始中断状态位。
         */
        uint32_t cnt_thr_event_u1_int_raw: 1;
        /** cnt_thr_event_u2_int_raw:RO；位位置：[2]；默认值：0；PCNT_CNT_THR_EVENT_U2_INT中断的原始中断状态位。
         */
        uint32_t cnt_thr_event_u2_int_raw: 1;
        /** cnt_thr_event_u3_int_raw:RO；位位置：[3]；默认值：0；PCNT_CNT_THR_EVENT_U3_INT中断的原始中断状态位。
         */
        uint32_t cnt_thr_event_u3_int_raw: 1;
        uint32_t reserved_4: 28;
    };
    uint32_t val;
} pcnt_int_raw_reg_t;

/** int_st寄存器类型中断状态寄存器
 */
typedef union {
    struct {
        /** cnt_thr_event_u0_int_st:RO；位位置：[0]；默认值：0；PCNT_CNT_THR_EVENT_U0_INT中断的屏蔽中断状态位。
         */
        uint32_t cnt_thr_event_u0_int_st: 1;
        /** cnt_thr_event_u1_int_st:RO；位位置：[1]；默认值：0；PCNT_CNT_THR_EVENT_U1_INT中断的屏蔽中断状态位。
         */
        uint32_t cnt_thr_event_u1_int_st: 1;
        /** cnt_thr_event_u2_int_st:RO；位位置：[2]；默认值：0；PCNT_CNT_THR_EVENT_U2_INT中断的屏蔽中断状态位。
         */
        uint32_t cnt_thr_event_u2_int_st: 1;
        /** cnt_thr_event_u3_int_st:RO；位位置：[3]；默认值：0；PCNT_CNT_THR_EVENT_U3_INT中断的屏蔽中断状态位。
         */
        uint32_t cnt_thr_event_u3_int_st: 1;
        uint32_t reserved_4: 28;
    };
    uint32_t val;
} pcnt_int_st_reg_t;

/** int_ena寄存器类型中断启用寄存器
 */
typedef union {
    struct {
        /** cnt_thr_event_u0_int_ena:R/W；位位置：[0]；默认值：0；PCNT_CNT_THR_EVENT_U0_INT中断的中断启用位。
         */
        uint32_t cnt_thr_event_u0_int_ena: 1;
        /** cnt_thr_event_u1_int_ena:R/W；位位置：[1]；默认值：0；PCNT_CNT_THR_EVENT_U1_INT中断的中断启用位。
         */
        uint32_t cnt_thr_event_u1_int_ena: 1;
        /** cnt_thr_event_u2_int_ena:R/W；位位置：[2]；默认值：0；PCNT_CNT_THR_EVENT_U2_INT中断的中断启用位。
         */
        uint32_t cnt_thr_event_u2_int_ena: 1;
        /** cnt_thr_event_u3_int_ena:R/W；位位置：[3]；默认值：0；PCNT_CNT_THR_EVENT_U3_INT中断的中断启用位。
         */
        uint32_t cnt_thr_event_u3_int_ena: 1;
        uint32_t reserved_4: 28;
    };
    uint32_t val;
} pcnt_int_ena_reg_t;

/** int_clr寄存器类型中断清除寄存器
 */
typedef union {
    struct {
        /** cnt_thr_event_u0_int_clr:WO；位位置：[0]；默认值：0；设置此位以清除PCNT_CNT_THR_EVENT_U0_INT中断。
         */
        uint32_t cnt_thr_event_u0_int_clr: 1;
        /** cnt_thr_event_u1_int_clr:WO；位位置：[1]；默认值：0；设置此位以清除PCNT_CNT_THR_EVENT_U1_INT中断。
         */
        uint32_t cnt_thr_event_u1_int_clr: 1;
        /** cnt_thr_event_u2_int_clr:WO；位位置：[2]；默认值：0；设置此位以清除PCNT_CNT_THR_EVENT_U2_INT中断。
         */
        uint32_t cnt_thr_event_u2_int_clr: 1;
        /** cnt_thr_event_u3_int_clr:WO；位位置：[3]；默认值：0；设置此位以清除PCNT_CNT_THR_EVENT_U3_INT中断。
         */
        uint32_t cnt_thr_event_u3_int_clr: 1;
        uint32_t reserved_4: 28;
    };
    uint32_t val;
} pcnt_int_clr_reg_t;


/**组：版本寄存器*/
/** 日期寄存器类型PCNT版本控制寄存器
 */
typedef union {
    struct {
        /** 日期：R/W；位位置：[31:0]；默认值：41989881；这是PCNT版本控制寄存器。
         */
        uint32_t date: 32;
    };
    uint32_t val;
} pcnt_date_reg_t;


typedef struct {
    volatile struct {
        pcnt_un_conf0_reg_t conf0;
        pcnt_un_conf1_reg_t conf1;
        pcnt_un_conf2_reg_t conf2;
    } conf_unit[4];
    volatile pcnt_un_cnt_reg_t cnt_unit[4];
    volatile pcnt_int_raw_reg_t int_raw;
    volatile pcnt_int_st_reg_t int_st;
    volatile pcnt_int_ena_reg_t int_ena;
    volatile pcnt_int_clr_reg_t int_clr;
    volatile pcnt_un_status_reg_t status_unit[4];
    volatile pcnt_ctrl_reg_t ctrl;
    uint32_t reserved_064[38];
    volatile pcnt_date_reg_t date;
} pcnt_dev_t;

#ifndef __cplusplus
_Static_assert(sizeof(pcnt_dev_t) == 0x100, "Invalid size of pcnt_dev_t structure");
#endif

extern pcnt_dev_t PCNT;

#ifdef __cplusplus
}
#endif

