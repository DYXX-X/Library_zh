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
#ifndef _SOC_PCNT_REG_H_
#define _SOC_PCNT_REG_H_


#include "soc.h"
#define PCNT_U0_CONF0_REG          (DR_REG_PCNT_BASE + 0x0000)
/* PCNT_CH1_LCTRL_MODE_U0:R/W；比特位置：[31:30]；默认值：2'd0；*/
/*描述：此寄存器用于控制单元0的通道1的低控制信号模式。2'd0：控制信号低时增加2'd1：控制信号高时减少其他：禁止*/
#define PCNT_CH1_LCTRL_MODE_U0  0x00000003
#define PCNT_CH1_LCTRL_MODE_U0_M  ((PCNT_CH1_LCTRL_MODE_U0_V)<<(PCNT_CH1_LCTRL_MODE_U0_S))
#define PCNT_CH1_LCTRL_MODE_U0_V  0x3
#define PCNT_CH1_LCTRL_MODE_U0_S  30
/* PCNT_CH1_HCTRL_MODE_U0:R/W；位位置：[29:28]；默认值：2'd0；*/
/*描述：此寄存器用于控制单元0的通道1的高控制信号模式。2'd0：控制信号低时增加2'd1：控制信号高时减少其他：禁止*/
#define PCNT_CH1_HCTRL_MODE_U0  0x00000003
#define PCNT_CH1_HCTRL_MODE_U0_M  ((PCNT_CH1_HCTRL_MODE_U0_V)<<(PCNT_CH1_HCTRL_MODE_U0_S))
#define PCNT_CH1_HCTRL_MODE_U0_V  0x3
#define PCNT_CH1_HCTRL_MODE_U0_S  28
/* PCNT_CH1_POS_MODE_U0:R/W；位位置：[27:26]；默认值：2'd0；*/
/*描述：此寄存器用于控制单元0的通道1输入边缘信号的模式。2'd1：在输入信号边缘增加2'd2：在输入输入信号边缘减少其他：禁止*/
#define PCNT_CH1_POS_MODE_U0  0x00000003
#define PCNT_CH1_POS_MODE_U0_M  ((PCNT_CH1_POS_MODE_U0_V)<<(PCNT_CH1_POS_MODE_U0_S))
#define PCNT_CH1_POS_MODE_U0_V  0x3
#define PCNT_CH1_POS_MODE_U0_S  26
/* PCNT_CH1_NEG_MODE_U0:R/W；位位置：[25:24]；默认值：2'd0；*/
/*描述：此寄存器用于控制单元0的通道1输入负边缘信号的模式。2'd1：在输入信号负边缘增加2'd2：在输入输入信号负边减少其他：禁止*/
#define PCNT_CH1_NEG_MODE_U0  0x00000003
#define PCNT_CH1_NEG_MODE_U0_M  ((PCNT_CH1_NEG_MODE_U0_V)<<(PCNT_CH1_NEG_MODE_U0_S))
#define PCNT_CH1_NEG_MODE_U0_V  0x3
#define PCNT_CH1_NEG_MODE_U0_S  24
/* PCNT_CH0_LCTRL_MODE_U0:R/W；比特位置：[23:22]；默认值：2'd0；*/
/*描述：此寄存器用于控制单元0的通道0的低控制信号模式。2'd0：控制信号低时增加2'd1：控制信号高时减少其他：禁止*/
#define PCNT_CH0_LCTRL_MODE_U0  0x00000003
#define PCNT_CH0_LCTRL_MODE_U0_M  ((PCNT_CH0_LCTRL_MODE_U0_V)<<(PCNT_CH0_LCTRL_MODE_U0_S))
#define PCNT_CH0_LCTRL_MODE_U0_V  0x3
#define PCNT_CH0_LCTRL_MODE_U0_S  22
/* PCNT_CH0_HCTRL_MODE_U0:R/W；比特位置：[21:20]；默认值：2'd0；*/
/*描述：此寄存器用于控制单元0的通道0的高控制信号模式。2'd0：控制信号低时增加2'd1：控制信号高时减少其他：禁止*/
#define PCNT_CH0_HCTRL_MODE_U0  0x00000003
#define PCNT_CH0_HCTRL_MODE_U0_M  ((PCNT_CH0_HCTRL_MODE_U0_V)<<(PCNT_CH0_HCTRL_MODE_U0_S))
#define PCNT_CH0_HCTRL_MODE_U0_V  0x3
#define PCNT_CH0_HCTRL_MODE_U0_S  20
/* PCNT_CH0_POS_MODE_U0:R/W；比特位置：[19:18]；默认值：2'd0；*/
/*描述：此寄存器用于控制单元0的通道0输入边缘信号的模式。2'd1：在输入信号边缘增加2'd2：在输入输入信号边缘减少其他：禁止*/
#define PCNT_CH0_POS_MODE_U0  0x00000003
#define PCNT_CH0_POS_MODE_U0_M  ((PCNT_CH0_POS_MODE_U0_V)<<(PCNT_CH0_POS_MODE_U0_S))
#define PCNT_CH0_POS_MODE_U0_V  0x3
#define PCNT_CH0_POS_MODE_U0_S  18
/* PCNT_CH0_NEG_MODE_U0:R/W；比特位置：[17:16]；默认值：2'd0；*/
/*描述：此寄存器用于控制单元0的通道0输入负边缘信号的模式。2'd1：在输入信号负边缘增加2'd2：在输入输入信号负边减少其他：禁止*/
#define PCNT_CH0_NEG_MODE_U0  0x00000003
#define PCNT_CH0_NEG_MODE_U0_M  ((PCNT_CH0_NEG_MODE_U0_V)<<(PCNT_CH0_NEG_MODE_U0_S))
#define PCNT_CH0_NEG_MODE_U0_V  0x3
#define PCNT_CH0_NEG_MODE_U0_S  16
/* PCNT_THR_threshold1_EN_U0:R/W；位位置：[15]；默认值：1’b0；*/
/*description:这是用于将unit0的计数与thres1值进行比较的启用位。*/
#define PCNT_THR_THRES1_EN_U0  (BIT(15))
#define PCNT_THR_THRES1_EN_U0_M  (BIT(15))
#define PCNT_THR_THRES1_EN_U0_V  0x1
#define PCNT_THR_THRES1_EN_U0_S  15
/* PCNT_THR_THRES0_EN_U0:R/W；位位置：[14]；默认值：1’b0；*/
/*description:这是用于将unit0的计数与thres0值进行比较的启用位。*/
#define PCNT_THR_THRES0_EN_U0  (BIT(14))
#define PCNT_THR_THRES0_EN_U0_M  (BIT(14))
#define PCNT_THR_THRES0_EN_U0_V  0x1
#define PCNT_THR_THRES0_EN_U0_S  14
/* PCNT_THR_L_LIM_EN_U0:R/W；位位置：[13]；默认值：1’b1；*/
/*description:这是用于将unit0的计数与thr_l_lim值进行比较的启用位。*/
#define PCNT_THR_L_LIM_EN_U0  (BIT(13))
#define PCNT_THR_L_LIM_EN_U0_M  (BIT(13))
#define PCNT_THR_L_LIM_EN_U0_V  0x1
#define PCNT_THR_L_LIM_EN_U0_S  13
/* PCNT_THR_H_LIM_EN_U0:R/W；位位置：[12]；默认值：1’b1；*/
/*description:这是用于将unit0的计数与thr_hl_lim值进行比较的启用位。*/
#define PCNT_THR_H_LIM_EN_U0  (BIT(12))
#define PCNT_THR_H_LIM_EN_U0_M  (BIT(12))
#define PCNT_THR_H_LIM_EN_U0_V  0x1
#define PCNT_THR_H_LIM_EN_U0_S  12
/* PCNT_THR_ZERO_EN_U0:R/W；位位置：[11]；默认值：1’b1；*/
/*description:这是用于将unit0的计数与0值进行比较的启用位。*/
#define PCNT_THR_ZERO_EN_U0  (BIT(11))
#define PCNT_THR_ZERO_EN_U0_M  (BIT(11))
#define PCNT_THR_ZERO_EN_U0_V  0x1
#define PCNT_THR_ZERO_EN_U0_S  11
/* PCNT_FILTER_EN_U0:R/W；位位置：[10]；默认值：1’b1；*/
/*description:这是用于过滤unit0的输入信号的启用位。*/
#define PCNT_FILTER_EN_U0  (BIT(10))
#define PCNT_FILTER_EN_U0_M  (BIT(10))
#define PCNT_FILTER_EN_U0_V  0x1
#define PCNT_FILTER_EN_U0_S  10
/* PCNT_FILTER_threes_0:R/W；位位置：[9:0]；默认值：10'h10；*/
/*description:此寄存器用于过滤宽度小于单位0的此值的脉冲。*/
#define PCNT_FILTER_THRES_U0  0x000003FF
#define PCNT_FILTER_THRES_U0_M  ((PCNT_FILTER_THRES_U0_V)<<(PCNT_FILTER_THRES_U0_S))
#define PCNT_FILTER_THRES_U0_V  0x3FF
#define PCNT_FILTER_THRES_U0_S  0

#define PCNT_U0_CONF1_REG          (DR_REG_PCNT_BASE + 0x0004)
/* PCNT_CNT_threshold_U0:R/W；比特位置：[31:16]；默认值：10'0；*/
/*description:此寄存器用于为unit0配置thres1值。*/
#define PCNT_CNT_THRES1_U0  0x0000FFFF
#define PCNT_CNT_THRES1_U0_M  ((PCNT_CNT_THRES1_U0_V)<<(PCNT_CNT_THRES1_U0_S))
#define PCNT_CNT_THRES1_U0_V  0xFFFF
#define PCNT_CNT_THRES1_U0_S  16
/* PCNT_CNT_THRES0_U0:R/W；比特位置：[15:0]；默认值：10'0；*/
/*description:此寄存器用于为unit0配置thres0值。*/
#define PCNT_CNT_THRES0_U0  0x0000FFFF
#define PCNT_CNT_THRES0_U0_M  ((PCNT_CNT_THRES0_U0_V)<<(PCNT_CNT_THRES0_U0_S))
#define PCNT_CNT_THRES0_U0_V  0xFFFF
#define PCNT_CNT_THRES0_U0_S  0

#define PCNT_U0_CONF2_REG          (DR_REG_PCNT_BASE + 0x0008)
/* PCNT_CNT_L_LIM_U0:R/W；比特位置：[31:16]；默认值：10'0；*/
/*description:此寄存器用于配置unit0的thr_l_lim值。*/
#define PCNT_CNT_L_LIM_U0  0x0000FFFF
#define PCNT_CNT_L_LIM_U0_M  ((PCNT_CNT_L_LIM_U0_V)<<(PCNT_CNT_L_LIM_U0_S))
#define PCNT_CNT_L_LIM_U0_V  0xFFFF
#define PCNT_CNT_L_LIM_U0_S  16
/* PCNT_CNT_H_LIM_U0:R/W；比特位置：[15:0]；默认值：10'0；*/
/*description:此寄存器用于为unit0配置thr_hl_lim值。*/
#define PCNT_CNT_H_LIM_U0  0x0000FFFF
#define PCNT_CNT_H_LIM_U0_M  ((PCNT_CNT_H_LIM_U0_V)<<(PCNT_CNT_H_LIM_U0_S))
#define PCNT_CNT_H_LIM_U0_V  0xFFFF
#define PCNT_CNT_H_LIM_U0_S  0

#define PCNT_U1_CONF0_REG          (DR_REG_PCNT_BASE + 0x000c)
/* PCNT_CH1_LCTRL_MODE_U1:R/W；比特位置：[31:30]；默认值：2'd0；*/
/*description:此寄存器用于控制第一单元信道1的低控制信号模式。2'd0：控制信号低时增加2'd1：控制信号高时减少其他：禁止*/
#define PCNT_CH1_LCTRL_MODE_U1  0x00000003
#define PCNT_CH1_LCTRL_MODE_U1_M  ((PCNT_CH1_LCTRL_MODE_U1_V)<<(PCNT_CH1_LCTRL_MODE_U1_S))
#define PCNT_CH1_LCTRL_MODE_U1_V  0x3
#define PCNT_CH1_LCTRL_MODE_U1_S  30
/* PCNT_CH1_HCTRL_MODE_U1:R/W；位位置：[29:28]；默认值：2'd0；*/
/*description:此寄存器用于控制第一单元信道1的高控制信号模式。2'd0：控制信号低时增加2'd1：控制信号高时减少其他：禁止*/
#define PCNT_CH1_HCTRL_MODE_U1  0x00000003
#define PCNT_CH1_HCTRL_MODE_U1_M  ((PCNT_CH1_HCTRL_MODE_U1_V)<<(PCNT_CH1_HCTRL_MODE_U1_S))
#define PCNT_CH1_HCTRL_MODE_U1_V  0x3
#define PCNT_CH1_HCTRL_MODE_U1_S  28
/* PCNT_CH1_POS_MODE_U1:R/W；位位置：[27:26]；默认值：2'd0；*/
/*description:此寄存器用于控制第一单元信道1的输入正边缘信号的模式。2'd1：在输入信号的正边缘增加2'd2：在输入信息的正边缘减少其他：禁止*/
#define PCNT_CH1_POS_MODE_U1  0x00000003
#define PCNT_CH1_POS_MODE_U1_M  ((PCNT_CH1_POS_MODE_U1_V)<<(PCNT_CH1_POS_MODE_U1_S))
#define PCNT_CH1_POS_MODE_U1_V  0x3
#define PCNT_CH1_POS_MODE_U1_S  26
/* PCNT_CH1_NEG_MODE_U1:R/W；位位置：[25:24]；默认值：2'd0；*/
/*description:此寄存器用于控制第一单元信道1的输入负边缘信号的模式。2'd1：在输入信号的负边缘增加2'd2：在输入信息的负边缘减少其他：禁止*/
#define PCNT_CH1_NEG_MODE_U1  0x00000003
#define PCNT_CH1_NEG_MODE_U1_M  ((PCNT_CH1_NEG_MODE_U1_V)<<(PCNT_CH1_NEG_MODE_U1_S))
#define PCNT_CH1_NEG_MODE_U1_V  0x3
#define PCNT_CH1_NEG_MODE_U1_S  24
/* PCNT_CH0_LCTRL_MODE_U1:R/W；比特位置：[23:22]；默认值：2'd0；*/
/*description:此寄存器用于控制第一单元信道0的低控制信号模式。2'd0：控制信号低时增加2'd1：控制信号高时减少其他：禁止*/
#define PCNT_CH0_LCTRL_MODE_U1  0x00000003
#define PCNT_CH0_LCTRL_MODE_U1_M  ((PCNT_CH0_LCTRL_MODE_U1_V)<<(PCNT_CH0_LCTRL_MODE_U1_S))
#define PCNT_CH0_LCTRL_MODE_U1_V  0x3
#define PCNT_CH0_LCTRL_MODE_U1_S  22
/* PCNT_CH0_HCTRL_MODE_U1:R/W；比特位置：[21:20]；默认值：2'd0；*/
/*description:此寄存器用于控制第一单元信道0的高控制信号模式。2'd0：控制信号低时增加2'd1：控制信号高时减少其他：禁止*/
#define PCNT_CH0_HCTRL_MODE_U1  0x00000003
#define PCNT_CH0_HCTRL_MODE_U1_M  ((PCNT_CH0_HCTRL_MODE_U1_V)<<(PCNT_CH0_HCTRL_MODE_U1_S))
#define PCNT_CH0_HCTRL_MODE_U1_V  0x3
#define PCNT_CH0_HCTRL_MODE_U1_S  20
/* PCNT_CH0_POS_MODE_U1:R/W；比特位置：[19:18]；默认值：2'd0；*/
/*description:此寄存器用于控制第一单元信道0的输入正边缘信号的模式。2'd1：在输入信号的正边缘增加2'd2：在输入信息的正边缘减少其他：禁止*/
#define PCNT_CH0_POS_MODE_U1  0x00000003
#define PCNT_CH0_POS_MODE_U1_M  ((PCNT_CH0_POS_MODE_U1_V)<<(PCNT_CH0_POS_MODE_U1_S))
#define PCNT_CH0_POS_MODE_U1_V  0x3
#define PCNT_CH0_POS_MODE_U1_S  18
/* PCNT_CH0_NEG_MODE_U1:R/W；比特位置：[17:16]；默认值：2'd0；*/
/*description:此寄存器用于控制第一单元信道0的输入负边缘信号的模式。2'd1：在输入信号的负边缘增加2'd2：在输入信息的负边缘减少其他：禁止*/
#define PCNT_CH0_NEG_MODE_U1  0x00000003
#define PCNT_CH0_NEG_MODE_U1_M  ((PCNT_CH0_NEG_MODE_U1_V)<<(PCNT_CH0_NEG_MODE_U1_S))
#define PCNT_CH0_NEG_MODE_U1_V  0x3
#define PCNT_CH0_NEG_MODE_U1_S  16
/* PCNT_THR_thresholds_EN_U1:R/W；位位置：[15]；默认值：1’b0；*/
/*description:这是用于比较第一单元的计数与thres1值的启用位。*/
#define PCNT_THR_THRES1_EN_U1  (BIT(15))
#define PCNT_THR_THRES1_EN_U1_M  (BIT(15))
#define PCNT_THR_THRES1_EN_U1_V  0x1
#define PCNT_THR_THRES1_EN_U1_S  15
/* PCNT_THR_THRES0_EN_U1:R/W；位位置：[14]；默认值：1’b0；*/
/*description:这是用于比较第一单元的计数与thres0值的启用位。*/
#define PCNT_THR_THRES0_EN_U1  (BIT(14))
#define PCNT_THR_THRES0_EN_U1_M  (BIT(14))
#define PCNT_THR_THRES0_EN_U1_V  0x1
#define PCNT_THR_THRES0_EN_U1_S  14
/* PCNT_THR_L_LIM_EN_U1:R/W；位位置：[13]；默认值：1’b1；*/
/*description:这是比较第一单元计数与thr_l_lim值的启用位。*/
#define PCNT_THR_L_LIM_EN_U1  (BIT(13))
#define PCNT_THR_L_LIM_EN_U1_M  (BIT(13))
#define PCNT_THR_L_LIM_EN_U1_V  0x1
#define PCNT_THR_L_LIM_EN_U1_S  13
/* PCNT_THR_H_LIM_EN_U1:R/W；位位置：[12]；默认值：1’b1；*/
/*description:这是比较第一单元计数与thr_h_lim值的启用位。*/
#define PCNT_THR_H_LIM_EN_U1  (BIT(12))
#define PCNT_THR_H_LIM_EN_U1_M  (BIT(12))
#define PCNT_THR_H_LIM_EN_U1_V  0x1
#define PCNT_THR_H_LIM_EN_U1_S  12
/* PCNT_THR_ZERO_EN_U1:R/W；位位置：[11]；默认值：1’b1；*/
/*description:这是将第一单元的计数与0值进行比较的启用位。*/
#define PCNT_THR_ZERO_EN_U1  (BIT(11))
#define PCNT_THR_ZERO_EN_U1_M  (BIT(11))
#define PCNT_THR_ZERO_EN_U1_V  0x1
#define PCNT_THR_ZERO_EN_U1_S  11
/* PCNT_FILTER_EN_U1:R/W；位位置：[10]；默认值：1’b1；*/
/*description:这是用于过滤第一单元输入信号的启用位。*/
#define PCNT_FILTER_EN_U1  (BIT(10))
#define PCNT_FILTER_EN_U1_M  (BIT(10))
#define PCNT_FILTER_EN_U1_V  0x1
#define PCNT_FILTER_EN_U1_S  10
/* PCNT_FILTER_threshold_U1:R/W；位位置：[9:0]；默认值：10'h10；*/
/*description:此寄存器用于过滤宽度小于第一单元的该值的加号。*/
#define PCNT_FILTER_THRES_U1  0x000003FF
#define PCNT_FILTER_THRES_U1_M  ((PCNT_FILTER_THRES_U1_V)<<(PCNT_FILTER_THRES_U1_S))
#define PCNT_FILTER_THRES_U1_V  0x3FF
#define PCNT_FILTER_THRES_U1_S  0

#define PCNT_U1_CONF1_REG          (DR_REG_PCNT_BASE + 0x0010)
/* PCNT_CNT_threshold_U1:R/W；比特位置：[31:16]；默认值：10'0；*/
/*description:此寄存器用于配置第一单元的thres1值。*/
#define PCNT_CNT_THRES1_U1  0x0000FFFF
#define PCNT_CNT_THRES1_U1_M  ((PCNT_CNT_THRES1_U1_V)<<(PCNT_CNT_THRES1_U1_S))
#define PCNT_CNT_THRES1_U1_V  0xFFFF
#define PCNT_CNT_THRES1_U1_S  16
/* PCNT_CNT_threshold_U1:R/W；比特位置：[15:0]；默认值：10'0；*/
/*description:此寄存器用于配置第一单元的thres0值。*/
#define PCNT_CNT_THRES0_U1  0x0000FFFF
#define PCNT_CNT_THRES0_U1_M  ((PCNT_CNT_THRES0_U1_V)<<(PCNT_CNT_THRES0_U1_S))
#define PCNT_CNT_THRES0_U1_V  0xFFFF
#define PCNT_CNT_THRES0_U1_S  0

#define PCNT_U1_CONF2_REG          (DR_REG_PCNT_BASE + 0x0014)
/* PCNT_CNT_L_LIM_U1:R/W；比特位置：[31:16]；默认值：10'0；*/
/*description:此寄存器用于配置第一单元的thr_l_lim值。*/
#define PCNT_CNT_L_LIM_U1  0x0000FFFF
#define PCNT_CNT_L_LIM_U1_M  ((PCNT_CNT_L_LIM_U1_V)<<(PCNT_CNT_L_LIM_U1_S))
#define PCNT_CNT_L_LIM_U1_V  0xFFFF
#define PCNT_CNT_L_LIM_U1_S  16
/* PCNT_CNT_H_LIM_U1:R/W；比特位置：[15:0]；默认值：10'0；*/
/*description:此寄存器用于配置第一单元的thr_h_lim值。*/
#define PCNT_CNT_H_LIM_U1  0x0000FFFF
#define PCNT_CNT_H_LIM_U1_M  ((PCNT_CNT_H_LIM_U1_V)<<(PCNT_CNT_H_LIM_U1_S))
#define PCNT_CNT_H_LIM_U1_V  0xFFFF
#define PCNT_CNT_H_LIM_U1_S  0

#define PCNT_U2_CONF0_REG          (DR_REG_PCNT_BASE + 0x0018)
/* PCNT_CH1_LCTRL_MODE_U2:R/W；比特位置：[31:30]；默认值：2'd0；*/
/*description:此寄存器用于控制第二单元信道1的低控制信号模式。2'd0：控制信号低时增加2'd1：控制信号高时减少其他：禁止*/
#define PCNT_CH1_LCTRL_MODE_U2  0x00000003
#define PCNT_CH1_LCTRL_MODE_U2_M  ((PCNT_CH1_LCTRL_MODE_U2_V)<<(PCNT_CH1_LCTRL_MODE_U2_S))
#define PCNT_CH1_LCTRL_MODE_U2_V  0x3
#define PCNT_CH1_LCTRL_MODE_U2_S  30
/* PCNT_CH1_HCTRL_MODE_U2:R/W；位位置：[29:28]；默认值：2'd0；*/
/*description:此寄存器用于控制第二单元信道1的高控制信号模式。2'd0：控制信号低时增加2'd1：控制信号高时减少其他：禁止*/
#define PCNT_CH1_HCTRL_MODE_U2  0x00000003
#define PCNT_CH1_HCTRL_MODE_U2_M  ((PCNT_CH1_HCTRL_MODE_U2_V)<<(PCNT_CH1_HCTRL_MODE_U2_S))
#define PCNT_CH1_HCTRL_MODE_U2_V  0x3
#define PCNT_CH1_HCTRL_MODE_U2_S  28
/* PCNT_CH1_POS_MODE_U2:R/W；位位置：[27:26]；默认值：2'd0；*/
/*description:此寄存器用于控制第二单元信道1的输入正边缘信号的模式。2'd1：在输入信号的正边缘增加2'd2：在输入信息的正边缘减少其他：禁止*/
#define PCNT_CH1_POS_MODE_U2  0x00000003
#define PCNT_CH1_POS_MODE_U2_M  ((PCNT_CH1_POS_MODE_U2_V)<<(PCNT_CH1_POS_MODE_U2_S))
#define PCNT_CH1_POS_MODE_U2_V  0x3
#define PCNT_CH1_POS_MODE_U2_S  26
/* PCNT_CH1_NEG_MODE_U2:R/W；位位置：[25:24]；默认值：2'd0；*/
/*description:此寄存器用于控制第二单元信道1的输入负边缘信号的模式。2'd1：在输入信号的负边缘增加2'd2：在输入信息的负边缘减少其他：禁止*/
#define PCNT_CH1_NEG_MODE_U2  0x00000003
#define PCNT_CH1_NEG_MODE_U2_M  ((PCNT_CH1_NEG_MODE_U2_V)<<(PCNT_CH1_NEG_MODE_U2_S))
#define PCNT_CH1_NEG_MODE_U2_V  0x3
#define PCNT_CH1_NEG_MODE_U2_S  24
/* PCNT_CH0_LCTRL_MODE_U2:R/W；比特位置：[23:22]；默认值：2'd0；*/
/*description:此寄存器用于控制第二单元信道0的低控制信号模式。2'd0：控制信号低时增加2'd1：控制信号高时减少其他：禁止*/
#define PCNT_CH0_LCTRL_MODE_U2  0x00000003
#define PCNT_CH0_LCTRL_MODE_U2_M  ((PCNT_CH0_LCTRL_MODE_U2_V)<<(PCNT_CH0_LCTRL_MODE_U2_S))
#define PCNT_CH0_LCTRL_MODE_U2_V  0x3
#define PCNT_CH0_LCTRL_MODE_U2_S  22
/* PCNT_CH0_HCTRL_MODE_U2:R/W；比特位置：[21:20]；默认值：2'd0；*/
/*description:此寄存器用于控制第二单元信道0的高控制信号模式。2'd0：控制信号低时增加2'd1：控制信号高时减少其他：禁止*/
#define PCNT_CH0_HCTRL_MODE_U2  0x00000003
#define PCNT_CH0_HCTRL_MODE_U2_M  ((PCNT_CH0_HCTRL_MODE_U2_V)<<(PCNT_CH0_HCTRL_MODE_U2_S))
#define PCNT_CH0_HCTRL_MODE_U2_V  0x3
#define PCNT_CH0_HCTRL_MODE_U2_S  20
/* PCNT_CH0_POS_MODE_U2:R/W；比特位置：[19:18]；默认值：2'd0；*/
/*description:此寄存器用于控制第二单元信道0的输入正边缘信号的模式。2'd1：在输入信号的正边缘增加2'd2：在输入信息的正边缘减少其他：禁止*/
#define PCNT_CH0_POS_MODE_U2  0x00000003
#define PCNT_CH0_POS_MODE_U2_M  ((PCNT_CH0_POS_MODE_U2_V)<<(PCNT_CH0_POS_MODE_U2_S))
#define PCNT_CH0_POS_MODE_U2_V  0x3
#define PCNT_CH0_POS_MODE_U2_S  18
/* PCNT_CH0_NEG_MODE_U2:R/W；比特位置：[17:16]；默认值：2'd0；*/
/*description:此寄存器用于控制第二单元信道0的输入负边缘信号的模式。2'd1：在输入信号的负边缘增加2'd2：在输入信息的负边缘减少其他：禁止*/
#define PCNT_CH0_NEG_MODE_U2  0x00000003
#define PCNT_CH0_NEG_MODE_U2_M  ((PCNT_CH0_NEG_MODE_U2_V)<<(PCNT_CH0_NEG_MODE_U2_S))
#define PCNT_CH0_NEG_MODE_U2_V  0x3
#define PCNT_CH0_NEG_MODE_U2_S  16
/* PCNT_THR_thresholds_EN_U2:R/W；位位置：[15]；默认值：1’b0；*/
/*description:这是用于比较第二单元的计数与thres1值的启用位。*/
#define PCNT_THR_THRES1_EN_U2  (BIT(15))
#define PCNT_THR_THRES1_EN_U2_M  (BIT(15))
#define PCNT_THR_THRES1_EN_U2_V  0x1
#define PCNT_THR_THRES1_EN_U2_S  15
/* PCNT_THR_THRES0_EN_U2:R/W；位位置：[14]；默认值：1’b0；*/
/*description:这是用于比较第二单元的计数与thres0值的启用位。*/
#define PCNT_THR_THRES0_EN_U2  (BIT(14))
#define PCNT_THR_THRES0_EN_U2_M  (BIT(14))
#define PCNT_THR_THRES0_EN_U2_V  0x1
#define PCNT_THR_THRES0_EN_U2_S  14
/* PCNT_THR_L_LIM_EN_U2:R/W；位位置：[13]；默认值：1’b1；*/
/*description:这是比较第二单元计数与thr_l_lim值的启用位。*/
#define PCNT_THR_L_LIM_EN_U2  (BIT(13))
#define PCNT_THR_L_LIM_EN_U2_M  (BIT(13))
#define PCNT_THR_L_LIM_EN_U2_V  0x1
#define PCNT_THR_L_LIM_EN_U2_S  13
/* PCNT_THR_H_LIM_EN_U2:R/W；位位置：[12]；默认值：1’b1；*/
/*description:这是比较第二单元计数与thr_h_lim值的启用位。*/
#define PCNT_THR_H_LIM_EN_U2  (BIT(12))
#define PCNT_THR_H_LIM_EN_U2_M  (BIT(12))
#define PCNT_THR_H_LIM_EN_U2_V  0x1
#define PCNT_THR_H_LIM_EN_U2_S  12
/* PCNT_THR_ZERO_EN_U2:R/W；位位置：[11]；默认值：1’b1；*/
/*description:这是将第二单元的计数与0值进行比较的启用位。*/
#define PCNT_THR_ZERO_EN_U2  (BIT(11))
#define PCNT_THR_ZERO_EN_U2_M  (BIT(11))
#define PCNT_THR_ZERO_EN_U2_V  0x1
#define PCNT_THR_ZERO_EN_U2_S  11
/* PCNT_FILTER_EN_U2:R/W；位位置：[10]；默认值：1’b1；*/
/*description:这是用于过滤第二单元输入信号的启用位。*/
#define PCNT_FILTER_EN_U2  (BIT(10))
#define PCNT_FILTER_EN_U2_M  (BIT(10))
#define PCNT_FILTER_EN_U2_V  0x1
#define PCNT_FILTER_EN_U2_S  10
/* PCNT_FILTER_threes_2:R/W；位位置：[9:0]；默认值：10'h10；*/
/*description:此寄存器用于过滤宽度小于第二单元的该值的加号。*/
#define PCNT_FILTER_THRES_U2  0x000003FF
#define PCNT_FILTER_THRES_U2_M  ((PCNT_FILTER_THRES_U2_V)<<(PCNT_FILTER_THRES_U2_S))
#define PCNT_FILTER_THRES_U2_V  0x3FF
#define PCNT_FILTER_THRES_U2_S  0

#define PCNT_U2_CONF1_REG          (DR_REG_PCNT_BASE + 0x001c)
/* PCNT_CNT_threshold_U2:R/W；比特位置：[31:16]；默认值：10'0；*/
/*description:此寄存器用于配置第二单元的thres1值。*/
#define PCNT_CNT_THRES1_U2  0x0000FFFF
#define PCNT_CNT_THRES1_U2_M  ((PCNT_CNT_THRES1_U2_V)<<(PCNT_CNT_THRES1_U2_S))
#define PCNT_CNT_THRES1_U2_V  0xFFFF
#define PCNT_CNT_THRES1_U2_S  16
/* PCNT_CNT_THRES0_U2:R/W；比特位置：[15:0]；默认值：10'0；*/
/*description:此寄存器用于配置第二单元的thres0值。*/
#define PCNT_CNT_THRES0_U2  0x0000FFFF
#define PCNT_CNT_THRES0_U2_M  ((PCNT_CNT_THRES0_U2_V)<<(PCNT_CNT_THRES0_U2_S))
#define PCNT_CNT_THRES0_U2_V  0xFFFF
#define PCNT_CNT_THRES0_U2_S  0

#define PCNT_U2_CONF2_REG          (DR_REG_PCNT_BASE + 0x0020)
/* PCNT_CNT_L_LIM_U2:R/W；比特位置：[31:16]；默认值：10'0；*/
/*description:此寄存器用于配置第二单元的thr_l_lim值。*/
#define PCNT_CNT_L_LIM_U2  0x0000FFFF
#define PCNT_CNT_L_LIM_U2_M  ((PCNT_CNT_L_LIM_U2_V)<<(PCNT_CNT_L_LIM_U2_S))
#define PCNT_CNT_L_LIM_U2_V  0xFFFF
#define PCNT_CNT_L_LIM_U2_S  16
/* PCNT_CNT_H_LIM_U2:R/W；比特位置：[15:0]；默认值：10'0；*/
/*description:此寄存器用于配置第二单元的thr_h_lim值。*/
#define PCNT_CNT_H_LIM_U2  0x0000FFFF
#define PCNT_CNT_H_LIM_U2_M  ((PCNT_CNT_H_LIM_U2_V)<<(PCNT_CNT_H_LIM_U2_S))
#define PCNT_CNT_H_LIM_U2_V  0xFFFF
#define PCNT_CNT_H_LIM_U2_S  0

#define PCNT_U3_CONF0_REG          (DR_REG_PCNT_BASE + 0x0024)
/* PCNT_CH1_LCTRL_MODE_U3:R/W；比特位置：[31:30]；默认值：2'd0；*/
/*description:此寄存器用于控制第三单元信道1的低控制信号模式。2'd0：控制信号低时增加2'd1：控制信号高时减少其他：禁止*/
#define PCNT_CH1_LCTRL_MODE_U3  0x00000003
#define PCNT_CH1_LCTRL_MODE_U3_M  ((PCNT_CH1_LCTRL_MODE_U3_V)<<(PCNT_CH1_LCTRL_MODE_U3_S))
#define PCNT_CH1_LCTRL_MODE_U3_V  0x3
#define PCNT_CH1_LCTRL_MODE_U3_S  30
/* PCNT_CH1_HCTRL_MODE_U3:R/W；位位置：[29:28]；默认值：2'd0；*/
/*description:此寄存器用于控制第三单元信道1的高控制信号模式。2'd0：控制信号低时增加2'd1：控制信号高时减少其他：禁止*/
#define PCNT_CH1_HCTRL_MODE_U3  0x00000003
#define PCNT_CH1_HCTRL_MODE_U3_M  ((PCNT_CH1_HCTRL_MODE_U3_V)<<(PCNT_CH1_HCTRL_MODE_U3_S))
#define PCNT_CH1_HCTRL_MODE_U3_V  0x3
#define PCNT_CH1_HCTRL_MODE_U3_S  28
/* PCNT_CH1_POS_MODE_U3:R/W；位位置：[27:26]；默认值：2'd0；*/
/*description:此寄存器用于控制第三单元信道1的输入正边缘信号的模式。2'd1：在输入信号的正边缘增加2'd2：在输入信息的正边缘减少其他：禁止*/
#define PCNT_CH1_POS_MODE_U3  0x00000003
#define PCNT_CH1_POS_MODE_U3_M  ((PCNT_CH1_POS_MODE_U3_V)<<(PCNT_CH1_POS_MODE_U3_S))
#define PCNT_CH1_POS_MODE_U3_V  0x3
#define PCNT_CH1_POS_MODE_U3_S  26
/* PCNT_CH1_NEG_MODE_U3:R/W；位位置：[25:24]；默认值：2'd0；*/
/*description:此寄存器用于控制第三单元信道1的输入负边缘信号的模式。2'd1：在输入信号的负边缘增加2'd2：在输入信息的负边缘减少其他：禁止*/
#define PCNT_CH1_NEG_MODE_U3  0x00000003
#define PCNT_CH1_NEG_MODE_U3_M  ((PCNT_CH1_NEG_MODE_U3_V)<<(PCNT_CH1_NEG_MODE_U3_S))
#define PCNT_CH1_NEG_MODE_U3_V  0x3
#define PCNT_CH1_NEG_MODE_U3_S  24
/* PCNT_CH0_LCTRL_MODE_U3:R/W；比特位置：[23:22]；默认值：2'd0；*/
/*description:此寄存器用于控制第三单元信道0的低控制信号模式。2'd0：控制信号低时增加2'd1：控制信号高时减少其他：禁止*/
#define PCNT_CH0_LCTRL_MODE_U3  0x00000003
#define PCNT_CH0_LCTRL_MODE_U3_M  ((PCNT_CH0_LCTRL_MODE_U3_V)<<(PCNT_CH0_LCTRL_MODE_U3_S))
#define PCNT_CH0_LCTRL_MODE_U3_V  0x3
#define PCNT_CH0_LCTRL_MODE_U3_S  22
/* PCNT_CH0_HCTRL_MODE_U3:R/W；比特位置：[21:20]；默认值：2'd0；*/
/*description:此寄存器用于控制第三单元信道0的高控制信号模式。2'd0：控制信号低时增加2'd1：控制信号高时减少其他：禁止*/
#define PCNT_CH0_HCTRL_MODE_U3  0x00000003
#define PCNT_CH0_HCTRL_MODE_U3_M  ((PCNT_CH0_HCTRL_MODE_U3_V)<<(PCNT_CH0_HCTRL_MODE_U3_S))
#define PCNT_CH0_HCTRL_MODE_U3_V  0x3
#define PCNT_CH0_HCTRL_MODE_U3_S  20
/* PCNT_CH0_POS_MODE_U3:R/W；比特位置：[19:18]；默认值：2'd0；*/
/*description:此寄存器用于控制第三单元信道0的输入正边缘信号的模式。2'd1：在输入信号的正边缘增加2'd2：在输入信息的正边缘减少其他：禁止*/
#define PCNT_CH0_POS_MODE_U3  0x00000003
#define PCNT_CH0_POS_MODE_U3_M  ((PCNT_CH0_POS_MODE_U3_V)<<(PCNT_CH0_POS_MODE_U3_S))
#define PCNT_CH0_POS_MODE_U3_V  0x3
#define PCNT_CH0_POS_MODE_U3_S  18
/* PCNT_CH0_NEG_MODE_U3:R/W；比特位置：[17:16]；默认值：2'd0；*/
/*description:此寄存器用于控制第三单元信道0的输入负边缘信号的模式。2'd1：在输入信号的负边缘增加2'd2：在输入信息的负边缘减少其他：禁止*/
#define PCNT_CH0_NEG_MODE_U3  0x00000003
#define PCNT_CH0_NEG_MODE_U3_M  ((PCNT_CH0_NEG_MODE_U3_V)<<(PCNT_CH0_NEG_MODE_U3_S))
#define PCNT_CH0_NEG_MODE_U3_V  0x3
#define PCNT_CH0_NEG_MODE_U3_S  16
/* PCNT_THR_thresholds_EN_U3:R/W；位位置：[15]；默认值：1’b0；*/
/*description:这是用于比较第三单元的计数与thres1值的启用位。*/
#define PCNT_THR_THRES1_EN_U3  (BIT(15))
#define PCNT_THR_THRES1_EN_U3_M  (BIT(15))
#define PCNT_THR_THRES1_EN_U3_V  0x1
#define PCNT_THR_THRES1_EN_U3_S  15
/* PCNT_THR_THRES0_EN_U3:R/W；位位置：[14]；默认值：1’b0；*/
/*description:这是用于比较第三单元的计数与thres0值的启用位。*/
#define PCNT_THR_THRES0_EN_U3  (BIT(14))
#define PCNT_THR_THRES0_EN_U3_M  (BIT(14))
#define PCNT_THR_THRES0_EN_U3_V  0x1
#define PCNT_THR_THRES0_EN_U3_S  14
/* PCNT_THR_L_LIM_EN_U3:R/W；位位置：[13]；默认值：1’b1；*/
/*description:这是比较第三单元计数与thr_l_lim值的启用位。*/
#define PCNT_THR_L_LIM_EN_U3  (BIT(13))
#define PCNT_THR_L_LIM_EN_U3_M  (BIT(13))
#define PCNT_THR_L_LIM_EN_U3_V  0x1
#define PCNT_THR_L_LIM_EN_U3_S  13
/* PCNT_THR_H_LIM_EN_U3:R/W；位位置：[12]；默认值：1’b1；*/
/*description:这是比较第三单元计数与thr_h_lim值的启用位。*/
#define PCNT_THR_H_LIM_EN_U3  (BIT(12))
#define PCNT_THR_H_LIM_EN_U3_M  (BIT(12))
#define PCNT_THR_H_LIM_EN_U3_V  0x1
#define PCNT_THR_H_LIM_EN_U3_S  12
/* PCNT_THR_ZERO_EN_U3:R/W；位位置：[11]；默认值：1’b1；*/
/*description:这是将第三单元的计数与0值进行比较的启用位。*/
#define PCNT_THR_ZERO_EN_U3  (BIT(11))
#define PCNT_THR_ZERO_EN_U3_M  (BIT(11))
#define PCNT_THR_ZERO_EN_U3_V  0x1
#define PCNT_THR_ZERO_EN_U3_S  11
/* PCNT_FILTER_EN_U3:R/W；位位置：[10]；默认值：1’b1；*/
/*description:这是用于过滤第三单元输入信号的启用位。*/
#define PCNT_FILTER_EN_U3  (BIT(10))
#define PCNT_FILTER_EN_U3_M  (BIT(10))
#define PCNT_FILTER_EN_U3_V  0x1
#define PCNT_FILTER_EN_U3_S  10
/* PCNT_FILTER_threes_3:R/W；位位置：[9:0]；默认值：10'h10；*/
/*description:此寄存器用于过滤宽度小于第三单元的该值的脉冲。*/
#define PCNT_FILTER_THRES_U3  0x000003FF
#define PCNT_FILTER_THRES_U3_M  ((PCNT_FILTER_THRES_U3_V)<<(PCNT_FILTER_THRES_U3_S))
#define PCNT_FILTER_THRES_U3_V  0x3FF
#define PCNT_FILTER_THRES_U3_S  0

#define PCNT_U3_CONF1_REG          (DR_REG_PCNT_BASE + 0x0028)
/* PCNT_CNT_threshold1_U3:R/W；比特位置：[31:16]；默认值：10'0；*/
/*description:此寄存器用于配置第三单元的thres1值。*/
#define PCNT_CNT_THRES1_U3  0x0000FFFF
#define PCNT_CNT_THRES1_U3_M  ((PCNT_CNT_THRES1_U3_V)<<(PCNT_CNT_THRES1_U3_S))
#define PCNT_CNT_THRES1_U3_V  0xFFFF
#define PCNT_CNT_THRES1_U3_S  16
/* PCNT_CNT_THRES0_U3:R/W；比特位置：[15:0]；默认值：10'0；*/
/*description:此寄存器用于配置第三单元的thres0值。*/
#define PCNT_CNT_THRES0_U3  0x0000FFFF
#define PCNT_CNT_THRES0_U3_M  ((PCNT_CNT_THRES0_U3_V)<<(PCNT_CNT_THRES0_U3_S))
#define PCNT_CNT_THRES0_U3_V  0xFFFF
#define PCNT_CNT_THRES0_U3_S  0

#define PCNT_U3_CONF2_REG          (DR_REG_PCNT_BASE + 0x002c)
/* PCNT_CNT_L_LIM_U3:R/W；比特位置：[31:16]；默认值：10'0；*/
/*description:此寄存器用于配置第三单元的thr_l_lim值。*/
#define PCNT_CNT_L_LIM_U3  0x0000FFFF
#define PCNT_CNT_L_LIM_U3_M  ((PCNT_CNT_L_LIM_U3_V)<<(PCNT_CNT_L_LIM_U3_S))
#define PCNT_CNT_L_LIM_U3_V  0xFFFF
#define PCNT_CNT_L_LIM_U3_S  16
/* PCNT_CNT_H_LIM_U3:R/W；比特位置：[15:0]；默认值：10'0；*/
/*description:此寄存器用于配置第三单元的thr_h_lim值。*/
#define PCNT_CNT_H_LIM_U3  0x0000FFFF
#define PCNT_CNT_H_LIM_U3_M  ((PCNT_CNT_H_LIM_U3_V)<<(PCNT_CNT_H_LIM_U3_S))
#define PCNT_CNT_H_LIM_U3_V  0xFFFF
#define PCNT_CNT_H_LIM_U3_S  0

#define PCNT_U4_CONF0_REG          (DR_REG_PCNT_BASE + 0x0030)
/* PCNT_CH1_LCTRL_MODE_U4:R/W；比特位置：[31:30]；默认值：2'd0；*/
/*description:此寄存器用于控制第四单元信道1的低控制信号模式。2'd0：控制信号低时增加2'd1：控制信号高时减少其他：禁止*/
#define PCNT_CH1_LCTRL_MODE_U4  0x00000003
#define PCNT_CH1_LCTRL_MODE_U4_M  ((PCNT_CH1_LCTRL_MODE_U4_V)<<(PCNT_CH1_LCTRL_MODE_U4_S))
#define PCNT_CH1_LCTRL_MODE_U4_V  0x3
#define PCNT_CH1_LCTRL_MODE_U4_S  30
/* PCNT_CH1_HCTRL_MODE_U4:R/W；位位置：[29:28]；默认值：2'd0；*/
/*description:此寄存器用于控制第四单元信道1的高控制信号模式。2'd0：控制信号低时增加2'd1：控制信号高时减少其他：禁止*/
#define PCNT_CH1_HCTRL_MODE_U4  0x00000003
#define PCNT_CH1_HCTRL_MODE_U4_M  ((PCNT_CH1_HCTRL_MODE_U4_V)<<(PCNT_CH1_HCTRL_MODE_U4_S))
#define PCNT_CH1_HCTRL_MODE_U4_V  0x3
#define PCNT_CH1_HCTRL_MODE_U4_S  28
/* PCNT_CH1_POS_MODE_U4:R/W；位位置：[27:26]；默认值：2'd0；*/
/*description:此寄存器用于控制第四单元信道1的输入正边缘信号的模式。2'd1：在输入信号的正边缘增加2'd2：在输入信息的正边缘减少其他：禁止*/
#define PCNT_CH1_POS_MODE_U4  0x00000003
#define PCNT_CH1_POS_MODE_U4_M  ((PCNT_CH1_POS_MODE_U4_V)<<(PCNT_CH1_POS_MODE_U4_S))
#define PCNT_CH1_POS_MODE_U4_V  0x3
#define PCNT_CH1_POS_MODE_U4_S  26
/* PCNT_CH1_NEG_MODE_U4:R/W；位位置：[25:24]；默认值：2'd0；*/
/*description:此寄存器用于控制第四单元信道1的输入负边缘信号的模式。2'd1：在输入信号的负边缘增加2'd2：在输入信息的负边缘减少其他：禁止*/
#define PCNT_CH1_NEG_MODE_U4  0x00000003
#define PCNT_CH1_NEG_MODE_U4_M  ((PCNT_CH1_NEG_MODE_U4_V)<<(PCNT_CH1_NEG_MODE_U4_S))
#define PCNT_CH1_NEG_MODE_U4_V  0x3
#define PCNT_CH1_NEG_MODE_U4_S  24
/* PCNT_CH0_LCTRL_MODE_U4:R/W；比特位置：[23:22]；默认值：2'd0；*/
/*description:此寄存器用于控制第四单元信道0的低控制信号模式。2'd0：控制信号低时增加2'd1：控制信号高时减少其他：禁止*/
#define PCNT_CH0_LCTRL_MODE_U4  0x00000003
#define PCNT_CH0_LCTRL_MODE_U4_M  ((PCNT_CH0_LCTRL_MODE_U4_V)<<(PCNT_CH0_LCTRL_MODE_U4_S))
#define PCNT_CH0_LCTRL_MODE_U4_V  0x3
#define PCNT_CH0_LCTRL_MODE_U4_S  22
/* PCNT_CH0_HCTRL_MODE_U4:R/W；比特位置：[21:20]；默认值：2'd0；*/
/*description:此寄存器用于控制第四单元信道0的高控制信号模式。2'd0：控制信号低时增加2'd1：控制信号高时减少其他：禁止*/
#define PCNT_CH0_HCTRL_MODE_U4  0x00000003
#define PCNT_CH0_HCTRL_MODE_U4_M  ((PCNT_CH0_HCTRL_MODE_U4_V)<<(PCNT_CH0_HCTRL_MODE_U4_S))
#define PCNT_CH0_HCTRL_MODE_U4_V  0x3
#define PCNT_CH0_HCTRL_MODE_U4_S  20
/* PCNT_CH0_POS_MODE_U4:R/W；比特位置：[19:18]；默认值：2'd0；*/
/*description:此寄存器用于控制第四单元信道0的输入正边缘信号的模式。2'd1：在输入信号的正边缘增加2'd2：在输入信息的正边缘减少其他：禁止*/
#define PCNT_CH0_POS_MODE_U4  0x00000003
#define PCNT_CH0_POS_MODE_U4_M  ((PCNT_CH0_POS_MODE_U4_V)<<(PCNT_CH0_POS_MODE_U4_S))
#define PCNT_CH0_POS_MODE_U4_V  0x3
#define PCNT_CH0_POS_MODE_U4_S  18
/* PCNT_CH0_NEG_MODE_U4:R/W；比特位置：[17:16]；默认值：2'd0；*/
/*description:此寄存器用于控制第四单元信道0的输入负边缘信号的模式。2'd1：在输入信号的负边缘增加2'd2：在输入信息的负边缘减少其他：禁止*/
#define PCNT_CH0_NEG_MODE_U4  0x00000003
#define PCNT_CH0_NEG_MODE_U4_M  ((PCNT_CH0_NEG_MODE_U4_V)<<(PCNT_CH0_NEG_MODE_U4_S))
#define PCNT_CH0_NEG_MODE_U4_V  0x3
#define PCNT_CH0_NEG_MODE_U4_S  16
/* PCNT_THR_threshold1_EN_U4:R/W；位位置：[15]；默认值：1’b0；*/
/*description:这是用于比较第四单元的计数与thres1值的启用位。*/
#define PCNT_THR_THRES1_EN_U4  (BIT(15))
#define PCNT_THR_THRES1_EN_U4_M  (BIT(15))
#define PCNT_THR_THRES1_EN_U4_V  0x1
#define PCNT_THR_THRES1_EN_U4_S  15
/* PCNT_THR_threshold_EN_U4:R/W；位位置：[14]；默认值：1’b0；*/
/*description:这是用于比较第四单元计数与thres0值的启用位。*/
#define PCNT_THR_THRES0_EN_U4  (BIT(14))
#define PCNT_THR_THRES0_EN_U4_M  (BIT(14))
#define PCNT_THR_THRES0_EN_U4_V  0x1
#define PCNT_THR_THRES0_EN_U4_S  14
/* PCNT_THR_L_LIM_EN_U4:R/W；位位置：[13]；默认值：1’b1；*/
/*description:这是比较第四单元计数与thr_l_lim值的启用位。*/
#define PCNT_THR_L_LIM_EN_U4  (BIT(13))
#define PCNT_THR_L_LIM_EN_U4_M  (BIT(13))
#define PCNT_THR_L_LIM_EN_U4_V  0x1
#define PCNT_THR_L_LIM_EN_U4_S  13
/* PCNT_THR_H_LIM_EN_U4:R/W；位位置：[12]；默认值：1’b1；*/
/*description:这是比较第四单元计数与thr_h_lim值的启用位。*/
#define PCNT_THR_H_LIM_EN_U4  (BIT(12))
#define PCNT_THR_H_LIM_EN_U4_M  (BIT(12))
#define PCNT_THR_H_LIM_EN_U4_V  0x1
#define PCNT_THR_H_LIM_EN_U4_S  12
/* PCNT_THR_ZERO_EN_U4:R/W；位位置：[11]；默认值：1’b1；*/
/*description:这是将第四单元的计数与0值进行比较的启用位。*/
#define PCNT_THR_ZERO_EN_U4  (BIT(11))
#define PCNT_THR_ZERO_EN_U4_M  (BIT(11))
#define PCNT_THR_ZERO_EN_U4_V  0x1
#define PCNT_THR_ZERO_EN_U4_S  11
/* PCNT_FILTER_EN_U4:R/W；位位置：[10]；默认值：1’b1；*/
/*description:这是用于过滤第四单元输入信号的启用位。*/
#define PCNT_FILTER_EN_U4  (BIT(10))
#define PCNT_FILTER_EN_U4_M  (BIT(10))
#define PCNT_FILTER_EN_U4_V  0x1
#define PCNT_FILTER_EN_U4_S  10
/* PCNT_FILTER_threes_4:R/W；位位置：[9:0]；默认值：10'h10；*/
/*description:此寄存器用于过滤宽度小于第四单元的该值的加号。*/
#define PCNT_FILTER_THRES_U4  0x000003FF
#define PCNT_FILTER_THRES_U4_M  ((PCNT_FILTER_THRES_U4_V)<<(PCNT_FILTER_THRES_U4_S))
#define PCNT_FILTER_THRES_U4_V  0x3FF
#define PCNT_FILTER_THRES_U4_S  0

#define PCNT_U4_CONF1_REG          (DR_REG_PCNT_BASE + 0x0034)
/* PCNT_CNT_threshold_U4:R/W；比特位置：[31:16]；默认值：10'0；*/
/*description:此寄存器用于配置第四单元的thres1值。*/
#define PCNT_CNT_THRES1_U4  0x0000FFFF
#define PCNT_CNT_THRES1_U4_M  ((PCNT_CNT_THRES1_U4_V)<<(PCNT_CNT_THRES1_U4_S))
#define PCNT_CNT_THRES1_U4_V  0xFFFF
#define PCNT_CNT_THRES1_U4_S  16
/* PCNT_CNT_THRES0_U4：R/W；比特位置：[15:0]；默认值：10'0；*/
/*description:此寄存器用于配置第四单元的thres0值。*/
#define PCNT_CNT_THRES0_U4  0x0000FFFF
#define PCNT_CNT_THRES0_U4_M  ((PCNT_CNT_THRES0_U4_V)<<(PCNT_CNT_THRES0_U4_S))
#define PCNT_CNT_THRES0_U4_V  0xFFFF
#define PCNT_CNT_THRES0_U4_S  0

#define PCNT_U4_CONF2_REG          (DR_REG_PCNT_BASE + 0x0038)
/* PCNT_CNT_L_LIM_U4:R/W；比特位置：[31:16]；默认值：10'0；*/
/*description:此寄存器用于配置第四单元的thr_l_lim值。*/
#define PCNT_CNT_L_LIM_U4  0x0000FFFF
#define PCNT_CNT_L_LIM_U4_M  ((PCNT_CNT_L_LIM_U4_V)<<(PCNT_CNT_L_LIM_U4_S))
#define PCNT_CNT_L_LIM_U4_V  0xFFFF
#define PCNT_CNT_L_LIM_U4_S  16
/* PCNT_CNT_H_LIM_U4:R/W；比特位置：[15:0]；默认值：10'0；*/
/*description:此寄存器用于配置第四单元的thr_h_lim值。*/
#define PCNT_CNT_H_LIM_U4  0x0000FFFF
#define PCNT_CNT_H_LIM_U4_M  ((PCNT_CNT_H_LIM_U4_V)<<(PCNT_CNT_H_LIM_U4_S))
#define PCNT_CNT_H_LIM_U4_V  0xFFFF
#define PCNT_CNT_H_LIM_U4_S  0

#define PCNT_U5_CONF0_REG          (DR_REG_PCNT_BASE + 0x003c)
/* PCNT_CH1_LCTRL_MODE_U5:R/W；比特位置：[31:30]；默认值：2'd0；*/
/*description:此寄存器用于控制第五单元信道1的低控制信号模式。2'd0：控制信号低时增加2'd1：控制信号高时减少其他：禁止*/
#define PCNT_CH1_LCTRL_MODE_U5  0x00000003
#define PCNT_CH1_LCTRL_MODE_U5_M  ((PCNT_CH1_LCTRL_MODE_U5_V)<<(PCNT_CH1_LCTRL_MODE_U5_S))
#define PCNT_CH1_LCTRL_MODE_U5_V  0x3
#define PCNT_CH1_LCTRL_MODE_U5_S  30
/* PCNT_CH1_HCTRL_MODE_U5:R/W；位位置：[29:28]；默认值：2'd0；*/
/*description:此寄存器用于控制第五单元信道1的高控制信号模式。2'd0：控制信号低时增加2'd1：控制信号高时减少其他：禁止*/
#define PCNT_CH1_HCTRL_MODE_U5  0x00000003
#define PCNT_CH1_HCTRL_MODE_U5_M  ((PCNT_CH1_HCTRL_MODE_U5_V)<<(PCNT_CH1_HCTRL_MODE_U5_S))
#define PCNT_CH1_HCTRL_MODE_U5_V  0x3
#define PCNT_CH1_HCTRL_MODE_U5_S  28
/* PCNT_CH1_POS_MODE_U5:R/W；位位置：[27:26]；默认值：2'd0；*/
/*description:此寄存器用于控制第五单元信道1的输入正边缘信号的模式。2'd1：在输入信号的正边缘增加2'd2：在输入信息的正边缘减少其他：禁止*/
#define PCNT_CH1_POS_MODE_U5  0x00000003
#define PCNT_CH1_POS_MODE_U5_M  ((PCNT_CH1_POS_MODE_U5_V)<<(PCNT_CH1_POS_MODE_U5_S))
#define PCNT_CH1_POS_MODE_U5_V  0x3
#define PCNT_CH1_POS_MODE_U5_S  26
/* PCNT_CH1_NEG_MODE_U5:R/W；位位置：[25:24]；默认值：2'd0；*/
/*description:此寄存器用于控制第五单元信道1的输入负边缘信号的模式。2'd1：在输入信号的负边缘增加2'd2：在输入信息的负边缘减少其他：禁止*/
#define PCNT_CH1_NEG_MODE_U5  0x00000003
#define PCNT_CH1_NEG_MODE_U5_M  ((PCNT_CH1_NEG_MODE_U5_V)<<(PCNT_CH1_NEG_MODE_U5_S))
#define PCNT_CH1_NEG_MODE_U5_V  0x3
#define PCNT_CH1_NEG_MODE_U5_S  24
/* PCNT_CH0_LCTRL_MODE_U5:R/W；比特位置：[23:22]；默认值：2'd0；*/
/*description:此寄存器用于控制第五单元信道0的低控制信号模式。2'd0：控制信号低时增加2'd1：控制信号高时减少其他：禁止*/
#define PCNT_CH0_LCTRL_MODE_U5  0x00000003
#define PCNT_CH0_LCTRL_MODE_U5_M  ((PCNT_CH0_LCTRL_MODE_U5_V)<<(PCNT_CH0_LCTRL_MODE_U5_S))
#define PCNT_CH0_LCTRL_MODE_U5_V  0x3
#define PCNT_CH0_LCTRL_MODE_U5_S  22
/* PCNT_CH0_HCTRL_MODE_U5:R/W；比特位置：[21:20]；默认值：2'd0；*/
/*description:此寄存器用于控制第五单元信道0的高控制信号模式。2'd0：控制信号低时增加2'd1：控制信号高时减少其他：禁止*/
#define PCNT_CH0_HCTRL_MODE_U5  0x00000003
#define PCNT_CH0_HCTRL_MODE_U5_M  ((PCNT_CH0_HCTRL_MODE_U5_V)<<(PCNT_CH0_HCTRL_MODE_U5_S))
#define PCNT_CH0_HCTRL_MODE_U5_V  0x3
#define PCNT_CH0_HCTRL_MODE_U5_S  20
/* PCNT_CH0_POS_MODE_U5:R/W；比特位置：[19:18]；默认值：2'd0；*/
/*description:此寄存器用于控制第五单元信道0的输入正边缘信号的模式。2'd1：在输入信号的正边缘增加2'd2：在输入信息的正边缘减少其他：禁止*/
#define PCNT_CH0_POS_MODE_U5  0x00000003
#define PCNT_CH0_POS_MODE_U5_M  ((PCNT_CH0_POS_MODE_U5_V)<<(PCNT_CH0_POS_MODE_U5_S))
#define PCNT_CH0_POS_MODE_U5_V  0x3
#define PCNT_CH0_POS_MODE_U5_S  18
/* PCNT_CH0_NEG_MODE_U5:R/W；比特位置：[17:16]；默认值：2'd0；*/
/*description:此寄存器用于控制第五单元信道0的输入负边缘信号的模式。2'd1：在输入信号的负边缘增加2'd2：在输入信息的负边缘减少其他：禁止*/
#define PCNT_CH0_NEG_MODE_U5  0x00000003
#define PCNT_CH0_NEG_MODE_U5_M  ((PCNT_CH0_NEG_MODE_U5_V)<<(PCNT_CH0_NEG_MODE_U5_S))
#define PCNT_CH0_NEG_MODE_U5_V  0x3
#define PCNT_CH0_NEG_MODE_U5_S  16
/* PCNT_THR_thresholds_EN_U5:R/W；位位置：[15]；默认值：1’b0；*/
/*description:这是用于比较第五单元的计数与thres1值的启用位。*/
#define PCNT_THR_THRES1_EN_U5  (BIT(15))
#define PCNT_THR_THRES1_EN_U5_M  (BIT(15))
#define PCNT_THR_THRES1_EN_U5_V  0x1
#define PCNT_THR_THRES1_EN_U5_S  15
/* PCNT_THR_THRES0_EN_U5:R/W；位位置：[14]；默认值：1’b0；*/
/*description:这是用于比较第五单元的计数与thres0值的启用位。*/
#define PCNT_THR_THRES0_EN_U5  (BIT(14))
#define PCNT_THR_THRES0_EN_U5_M  (BIT(14))
#define PCNT_THR_THRES0_EN_U5_V  0x1
#define PCNT_THR_THRES0_EN_U5_S  14
/* PCNT_THR_L_LIM_EN_U5:R/W；位位置：[13]；默认值：1’b1；*/
/*description:这是比较第五单元计数与thr_l_lim值的启用位。*/
#define PCNT_THR_L_LIM_EN_U5  (BIT(13))
#define PCNT_THR_L_LIM_EN_U5_M  (BIT(13))
#define PCNT_THR_L_LIM_EN_U5_V  0x1
#define PCNT_THR_L_LIM_EN_U5_S  13
/* PCNT_THR_H_LIM_EN_U5:R/W；位位置：[12]；默认值：1’b1；*/
/*description:这是比较第五单元计数与thr_h_lim值的启用位。*/
#define PCNT_THR_H_LIM_EN_U5  (BIT(12))
#define PCNT_THR_H_LIM_EN_U5_M  (BIT(12))
#define PCNT_THR_H_LIM_EN_U5_V  0x1
#define PCNT_THR_H_LIM_EN_U5_S  12
/* PCNT_THR_ZERO_EN_U5:R/W；位位置：[11]；默认值：1’b1；*/
/*description:这是将第五单元的计数与0值进行比较的启用位。*/
#define PCNT_THR_ZERO_EN_U5  (BIT(11))
#define PCNT_THR_ZERO_EN_U5_M  (BIT(11))
#define PCNT_THR_ZERO_EN_U5_V  0x1
#define PCNT_THR_ZERO_EN_U5_S  11
/* PCNT_FILTER_EN_U5:R/W；位位置：[10]；默认值：1’b1；*/
/*description:这是用于过滤第五单元输入信号的启用位。*/
#define PCNT_FILTER_EN_U5  (BIT(10))
#define PCNT_FILTER_EN_U5_M  (BIT(10))
#define PCNT_FILTER_EN_U5_V  0x1
#define PCNT_FILTER_EN_U5_S  10
/* PCNT_FILTER_threes_5:R/W；位位置：[9:0]；默认值：10'h10；*/
/*description:此寄存器用于过滤宽度小于第五单元的该值的加号。*/
#define PCNT_FILTER_THRES_U5  0x000003FF
#define PCNT_FILTER_THRES_U5_M  ((PCNT_FILTER_THRES_U5_V)<<(PCNT_FILTER_THRES_U5_S))
#define PCNT_FILTER_THRES_U5_V  0x3FF
#define PCNT_FILTER_THRES_U5_S  0

#define PCNT_U5_CONF1_REG          (DR_REG_PCNT_BASE + 0x0040)
/* PCNT_CNT_threshold_U5:R/W；比特位置：[31:16]；默认值：10'0；*/
/*description:此寄存器用于配置第五单元的thres1值。*/
#define PCNT_CNT_THRES1_U5  0x0000FFFF
#define PCNT_CNT_THRES1_U5_M  ((PCNT_CNT_THRES1_U5_V)<<(PCNT_CNT_THRES1_U5_S))
#define PCNT_CNT_THRES1_U5_V  0xFFFF
#define PCNT_CNT_THRES1_U5_S  16
/* PCNT_CNT_THRES0_U5:R/W；比特位置：[15:0]；默认值：10'0；*/
/*description:此寄存器用于配置第五单元的thres0值。*/
#define PCNT_CNT_THRES0_U5  0x0000FFFF
#define PCNT_CNT_THRES0_U5_M  ((PCNT_CNT_THRES0_U5_V)<<(PCNT_CNT_THRES0_U5_S))
#define PCNT_CNT_THRES0_U5_V  0xFFFF
#define PCNT_CNT_THRES0_U5_S  0

#define PCNT_U5_CONF2_REG          (DR_REG_PCNT_BASE + 0x0044)
/* PCNT_CNT_L_LIM_U5:R/W；比特位置：[31:16]；默认值：10'0；*/
/*description:此寄存器用于配置第五单元的thr_l_lim值。*/
#define PCNT_CNT_L_LIM_U5  0x0000FFFF
#define PCNT_CNT_L_LIM_U5_M  ((PCNT_CNT_L_LIM_U5_V)<<(PCNT_CNT_L_LIM_U5_S))
#define PCNT_CNT_L_LIM_U5_V  0xFFFF
#define PCNT_CNT_L_LIM_U5_S  16
/* PCNT_CNT_H_LIM_U5:R/W；比特位置：[15:0]；默认值：10'0；*/
/*description:此寄存器用于配置第五单元的thr_h_lim值。*/
#define PCNT_CNT_H_LIM_U5  0x0000FFFF
#define PCNT_CNT_H_LIM_U5_M  ((PCNT_CNT_H_LIM_U5_V)<<(PCNT_CNT_H_LIM_U5_S))
#define PCNT_CNT_H_LIM_U5_V  0xFFFF
#define PCNT_CNT_H_LIM_U5_S  0

#define PCNT_U6_CONF0_REG          (DR_REG_PCNT_BASE + 0x0048)
/* PCNT_CH1_LCTRL_MODE_U6:R/W；比特位置：[31:30]；默认值：2'd0；*/
/*description:此寄存器用于控制第六单元信道1的低控制信号模式。2'd0：控制信号低时增加2'd1：控制信号高时减少其他：禁止*/
#define PCNT_CH1_LCTRL_MODE_U6  0x00000003
#define PCNT_CH1_LCTRL_MODE_U6_M  ((PCNT_CH1_LCTRL_MODE_U6_V)<<(PCNT_CH1_LCTRL_MODE_U6_S))
#define PCNT_CH1_LCTRL_MODE_U6_V  0x3
#define PCNT_CH1_LCTRL_MODE_U6_S  30
/* PCNT_CH1_HCTRL_MODE_U6:R/W；位位置：[29:28]；默认值：2'd0；*/
/*description:此寄存器用于控制第六单元信道1的高控制信号模式。2'd0：控制信号低时增加2'd1：控制信号高时减少其他：禁止*/
#define PCNT_CH1_HCTRL_MODE_U6  0x00000003
#define PCNT_CH1_HCTRL_MODE_U6_M  ((PCNT_CH1_HCTRL_MODE_U6_V)<<(PCNT_CH1_HCTRL_MODE_U6_S))
#define PCNT_CH1_HCTRL_MODE_U6_V  0x3
#define PCNT_CH1_HCTRL_MODE_U6_S  28
/* PCNT_CH1_POS_MODE_U6:R/W；位位置：[27:26]；默认值：2'd0；*/
/*description:此寄存器用于控制第六单元信道1的输入正边缘信号的模式。2'd1：在输入信号的正边缘增加2'd2：在输入信息的正边缘减少其他：禁止*/
#define PCNT_CH1_POS_MODE_U6  0x00000003
#define PCNT_CH1_POS_MODE_U6_M  ((PCNT_CH1_POS_MODE_U6_V)<<(PCNT_CH1_POS_MODE_U6_S))
#define PCNT_CH1_POS_MODE_U6_V  0x3
#define PCNT_CH1_POS_MODE_U6_S  26
/* PCNT_CH1_NEG_MODE_U6:R/W；位位置：[25:24]；默认值：2'd0；*/
/*description:此寄存器用于控制第六单元信道1的输入负边缘信号的模式。2'd1：在输入信号的负边缘增加2'd2：在输入信息的负边缘减少其他：禁止*/
#define PCNT_CH1_NEG_MODE_U6  0x00000003
#define PCNT_CH1_NEG_MODE_U6_M  ((PCNT_CH1_NEG_MODE_U6_V)<<(PCNT_CH1_NEG_MODE_U6_S))
#define PCNT_CH1_NEG_MODE_U6_V  0x3
#define PCNT_CH1_NEG_MODE_U6_S  24
/* PCNT_CH0_LCTRL_MODE_U6:R/W；比特位置：[23:22]；默认值：2'd0；*/
/*description:此寄存器用于控制第六单元信道0的低控制信号模式。2'd0：控制信号低时增加2'd1：控制信号高时减少其他：禁止*/
#define PCNT_CH0_LCTRL_MODE_U6  0x00000003
#define PCNT_CH0_LCTRL_MODE_U6_M  ((PCNT_CH0_LCTRL_MODE_U6_V)<<(PCNT_CH0_LCTRL_MODE_U6_S))
#define PCNT_CH0_LCTRL_MODE_U6_V  0x3
#define PCNT_CH0_LCTRL_MODE_U6_S  22
/* PCNT_CH0_HCTRL_MODE_U6:R/W；比特位置：[21:20]；默认值：2'd0；*/
/*description:此寄存器用于控制第六单元信道0的高控制信号模式。2'd0：控制信号低时增加2'd1：控制信号高时减少其他：禁止*/
#define PCNT_CH0_HCTRL_MODE_U6  0x00000003
#define PCNT_CH0_HCTRL_MODE_U6_M  ((PCNT_CH0_HCTRL_MODE_U6_V)<<(PCNT_CH0_HCTRL_MODE_U6_S))
#define PCNT_CH0_HCTRL_MODE_U6_V  0x3
#define PCNT_CH0_HCTRL_MODE_U6_S  20
/* PCNT_CH0_POS_MODE_U6:R/W；比特位置：[19:18]；默认值：2'd0；*/
/*description:此寄存器用于控制第六单元信道0的输入正边缘信号的模式。2'd1：在输入信号的正边缘增加2'd2：在输入信息的正边缘减少其他：禁止*/
#define PCNT_CH0_POS_MODE_U6  0x00000003
#define PCNT_CH0_POS_MODE_U6_M  ((PCNT_CH0_POS_MODE_U6_V)<<(PCNT_CH0_POS_MODE_U6_S))
#define PCNT_CH0_POS_MODE_U6_V  0x3
#define PCNT_CH0_POS_MODE_U6_S  18
/* PCNT_CH0_NEG_MODE_U6:R/W；比特位置：[17:16]；默认值：2'd0；*/
/*description:此寄存器用于控制第六单元信道0的输入负边缘信号的模式。2'd1：在输入信号的负边缘增加2'd2：在输入信息的负边缘减少其他：禁止*/
#define PCNT_CH0_NEG_MODE_U6  0x00000003
#define PCNT_CH0_NEG_MODE_U6_M  ((PCNT_CH0_NEG_MODE_U6_V)<<(PCNT_CH0_NEG_MODE_U6_S))
#define PCNT_CH0_NEG_MODE_U6_V  0x3
#define PCNT_CH0_NEG_MODE_U6_S  16
/* PCNT_THR_thresholds_EN_U6:R/W；位位置：[15]；默认值：1’b0；*/
/*description:这是用于比较第六单元的计数与thres1值的启用位。*/
#define PCNT_THR_THRES1_EN_U6  (BIT(15))
#define PCNT_THR_THRES1_EN_U6_M  (BIT(15))
#define PCNT_THR_THRES1_EN_U6_V  0x1
#define PCNT_THR_THRES1_EN_U6_S  15
/* PCNT_THR_THRES0_EN_U6:R/W；位位置：[14]；默认值：1’b0；*/
/*description:这是用于比较第六单元的计数与thres0值的启用位。*/
#define PCNT_THR_THRES0_EN_U6  (BIT(14))
#define PCNT_THR_THRES0_EN_U6_M  (BIT(14))
#define PCNT_THR_THRES0_EN_U6_V  0x1
#define PCNT_THR_THRES0_EN_U6_S  14
/* PCNT_THR_L_LIM_EN_U6:R/W；位位置：[13]；默认值：1’b1；*/
/*description:这是比较第六单元计数与thr_l_lim值的启用位。*/
#define PCNT_THR_L_LIM_EN_U6  (BIT(13))
#define PCNT_THR_L_LIM_EN_U6_M  (BIT(13))
#define PCNT_THR_L_LIM_EN_U6_V  0x1
#define PCNT_THR_L_LIM_EN_U6_S  13
/* PCNT_THR_H_LIM_EN_U6:R/W；位位置：[12]；默认值：1’b1；*/
/*description:这是比较第六单元计数与thr_h_lim值的启用位。*/
#define PCNT_THR_H_LIM_EN_U6  (BIT(12))
#define PCNT_THR_H_LIM_EN_U6_M  (BIT(12))
#define PCNT_THR_H_LIM_EN_U6_V  0x1
#define PCNT_THR_H_LIM_EN_U6_S  12
/* PCNT_THR_ZERO_EN_U6:R/W；位位置：[11]；默认值：1’b1；*/
/*description:这是将第六单元的计数与0值进行比较的启用位。*/
#define PCNT_THR_ZERO_EN_U6  (BIT(11))
#define PCNT_THR_ZERO_EN_U6_M  (BIT(11))
#define PCNT_THR_ZERO_EN_U6_V  0x1
#define PCNT_THR_ZERO_EN_U6_S  11
/* PCNT_FILTER_EN_U6:R/W；位位置：[10]；默认值：1’b1；*/
/*description:这是用于过滤第六单元输入信号的启用位。*/
#define PCNT_FILTER_EN_U6  (BIT(10))
#define PCNT_FILTER_EN_U6_M  (BIT(10))
#define PCNT_FILTER_EN_U6_V  0x1
#define PCNT_FILTER_EN_U6_S  10
/* PCNT_FILTER_threes_6:R/W；位位置：[9:0]；默认值：10'h10；*/
/*description:此寄存器用于过滤宽度小于第六单元的该值的脉冲。*/
#define PCNT_FILTER_THRES_U6  0x000003FF
#define PCNT_FILTER_THRES_U6_M  ((PCNT_FILTER_THRES_U6_V)<<(PCNT_FILTER_THRES_U6_S))
#define PCNT_FILTER_THRES_U6_V  0x3FF
#define PCNT_FILTER_THRES_U6_S  0

#define PCNT_U6_CONF1_REG          (DR_REG_PCNT_BASE + 0x004c)
/* PCNT_CNT_threshold1_U6:R/W；比特位置：[31:16]；默认值：10'0；*/
/*description:此寄存器用于配置第六单元的thres1值。*/
#define PCNT_CNT_THRES1_U6  0x0000FFFF
#define PCNT_CNT_THRES1_U6_M  ((PCNT_CNT_THRES1_U6_V)<<(PCNT_CNT_THRES1_U6_S))
#define PCNT_CNT_THRES1_U6_V  0xFFFF
#define PCNT_CNT_THRES1_U6_S  16
/* PCNT_CNT_THRES0_U6:R/W；比特位置：[15:0]；默认值：10'0；*/
/*description:此寄存器用于配置第六单元的thres0值。*/
#define PCNT_CNT_THRES0_U6  0x0000FFFF
#define PCNT_CNT_THRES0_U6_M  ((PCNT_CNT_THRES0_U6_V)<<(PCNT_CNT_THRES0_U6_S))
#define PCNT_CNT_THRES0_U6_V  0xFFFF
#define PCNT_CNT_THRES0_U6_S  0

#define PCNT_U6_CONF2_REG          (DR_REG_PCNT_BASE + 0x0050)
/* PCNT_CNT_L_LIM_U6:R/W；比特位置：[31:16]；默认值：10'0；*/
/*description:此寄存器用于配置第六单元的thr_l_lim值。*/
#define PCNT_CNT_L_LIM_U6  0x0000FFFF
#define PCNT_CNT_L_LIM_U6_M  ((PCNT_CNT_L_LIM_U6_V)<<(PCNT_CNT_L_LIM_U6_S))
#define PCNT_CNT_L_LIM_U6_V  0xFFFF
#define PCNT_CNT_L_LIM_U6_S  16
/* PCNT_CNT_H_LIM_U6:R/W；比特位置：[15:0]；默认值：10'0；*/
/*description:此寄存器用于配置第六单元的thr_h_lim值。*/
#define PCNT_CNT_H_LIM_U6  0x0000FFFF
#define PCNT_CNT_H_LIM_U6_M  ((PCNT_CNT_H_LIM_U6_V)<<(PCNT_CNT_H_LIM_U6_S))
#define PCNT_CNT_H_LIM_U6_V  0xFFFF
#define PCNT_CNT_H_LIM_U6_S  0

#define PCNT_U7_CONF0_REG          (DR_REG_PCNT_BASE + 0x0054)
/* PCNT_CH1_LCTRL_MODE_U7:R/W；比特位置：[31:30]；默认值：2'd0；*/
/*description:此寄存器用于控制第七单元信道1的低控制信号模式。2'd0：控制信号低时增加2'd1：控制信号高时减少其他：禁止*/
#define PCNT_CH1_LCTRL_MODE_U7  0x00000003
#define PCNT_CH1_LCTRL_MODE_U7_M  ((PCNT_CH1_LCTRL_MODE_U7_V)<<(PCNT_CH1_LCTRL_MODE_U7_S))
#define PCNT_CH1_LCTRL_MODE_U7_V  0x3
#define PCNT_CH1_LCTRL_MODE_U7_S  30
/* PCNT_CH1_HCTRL_MODE_U7:R/W；位位置：[29:28]；默认值：2'd0；*/
/*description:此寄存器用于控制第七单元信道1的高控制信号模式。2'd0：控制信号低时增加2'd1：控制信号高时减少其他：禁止*/
#define PCNT_CH1_HCTRL_MODE_U7  0x00000003
#define PCNT_CH1_HCTRL_MODE_U7_M  ((PCNT_CH1_HCTRL_MODE_U7_V)<<(PCNT_CH1_HCTRL_MODE_U7_S))
#define PCNT_CH1_HCTRL_MODE_U7_V  0x3
#define PCNT_CH1_HCTRL_MODE_U7_S  28
/* PCNT_CH1_POS_MODE_U7:R/W；位位置：[27:26]；默认值：2'd0；*/
/*description:此寄存器用于控制第七单元信道1的输入正边缘信号的模式。2'd1：在输入信号的正边缘增加2'd2：在输入信息的正边缘减少其他：禁止*/
#define PCNT_CH1_POS_MODE_U7  0x00000003
#define PCNT_CH1_POS_MODE_U7_M  ((PCNT_CH1_POS_MODE_U7_V)<<(PCNT_CH1_POS_MODE_U7_S))
#define PCNT_CH1_POS_MODE_U7_V  0x3
#define PCNT_CH1_POS_MODE_U7_S  26
/* PCNT_CH1_NEG_MODE_U7:R/W；位位置：[25:24]；默认值：2'd0；*/
/*description:此寄存器用于控制第七单元信道1的输入负边缘信号的模式。2'd1：在输入信号的负边缘增加2'd2：在输入信息的负边缘减少其他：禁止*/
#define PCNT_CH1_NEG_MODE_U7  0x00000003
#define PCNT_CH1_NEG_MODE_U7_M  ((PCNT_CH1_NEG_MODE_U7_V)<<(PCNT_CH1_NEG_MODE_U7_S))
#define PCNT_CH1_NEG_MODE_U7_V  0x3
#define PCNT_CH1_NEG_MODE_U7_S  24
/* PCNT_CH0_LCTRL_MODE_U7:R/W；比特位置：[23:22]；默认值：2'd0；*/
/*description:此寄存器用于控制第七单元信道0的低控制信号模式。2'd0：控制信号低时增加2'd1：控制信号高时减少其他：禁止*/
#define PCNT_CH0_LCTRL_MODE_U7  0x00000003
#define PCNT_CH0_LCTRL_MODE_U7_M  ((PCNT_CH0_LCTRL_MODE_U7_V)<<(PCNT_CH0_LCTRL_MODE_U7_S))
#define PCNT_CH0_LCTRL_MODE_U7_V  0x3
#define PCNT_CH0_LCTRL_MODE_U7_S  22
/* PCNT_CH0_HCTRL_MODE_U7:R/W；比特位置：[21:20]；默认值：2'd0；*/
/*description:此寄存器用于控制第七单元信道0的高控制信号模式。2'd0：控制信号低时增加2'd1：控制信号高时减少其他：禁止*/
#define PCNT_CH0_HCTRL_MODE_U7  0x00000003
#define PCNT_CH0_HCTRL_MODE_U7_M  ((PCNT_CH0_HCTRL_MODE_U7_V)<<(PCNT_CH0_HCTRL_MODE_U7_S))
#define PCNT_CH0_HCTRL_MODE_U7_V  0x3
#define PCNT_CH0_HCTRL_MODE_U7_S  20
/* PCNT_CH0_POS_MODE_U7:R/W；比特位置：[19:18]；默认值：2'd0；*/
/*description:此寄存器用于控制第七单元信道0的输入正边缘信号的模式。2'd1：在输入信号的正边缘增加2'd2：在输入信息的正边缘减少其他：禁止*/
#define PCNT_CH0_POS_MODE_U7  0x00000003
#define PCNT_CH0_POS_MODE_U7_M  ((PCNT_CH0_POS_MODE_U7_V)<<(PCNT_CH0_POS_MODE_U7_S))
#define PCNT_CH0_POS_MODE_U7_V  0x3
#define PCNT_CH0_POS_MODE_U7_S  18
/* PCNT_CH0_NEG_MODE_U7:R/W；比特位置：[17:16]；默认值：2'd0；*/
/*description:此寄存器用于控制第七单元信道0的输入负边缘信号的模式。2'd1：在输入信号的负边缘增加2'd2：在输入信息的负边缘减少其他：禁止*/
#define PCNT_CH0_NEG_MODE_U7  0x00000003
#define PCNT_CH0_NEG_MODE_U7_M  ((PCNT_CH0_NEG_MODE_U7_V)<<(PCNT_CH0_NEG_MODE_U7_S))
#define PCNT_CH0_NEG_MODE_U7_V  0x3
#define PCNT_CH0_NEG_MODE_U7_S  16
/* PCNT_THR_thresholds_EN_U7:R/W；位位置：[15]；默认值：1’b0；*/
/*description:这是用于比较第七单元的计数与thres1值的启用位。*/
#define PCNT_THR_THRES1_EN_U7  (BIT(15))
#define PCNT_THR_THRES1_EN_U7_M  (BIT(15))
#define PCNT_THR_THRES1_EN_U7_V  0x1
#define PCNT_THR_THRES1_EN_U7_S  15
/* PCNT_THR_THRES0_EN_U7:R/W；位位置：[14]；默认值：1’b0；*/
/*description:这是用于比较第七单元的计数与thres0值的启用位。*/
#define PCNT_THR_THRES0_EN_U7  (BIT(14))
#define PCNT_THR_THRES0_EN_U7_M  (BIT(14))
#define PCNT_THR_THRES0_EN_U7_V  0x1
#define PCNT_THR_THRES0_EN_U7_S  14
/* PCNT_THR_L_LIM_EN_U7:R/W；位位置：[13]；默认值：1’b1；*/
/*description:这是用于比较第七单元计数与thr_l_lim值的启用位。*/
#define PCNT_THR_L_LIM_EN_U7  (BIT(13))
#define PCNT_THR_L_LIM_EN_U7_M  (BIT(13))
#define PCNT_THR_L_LIM_EN_U7_V  0x1
#define PCNT_THR_L_LIM_EN_U7_S  13
/* PCNT_THR_H_LIM_EN_U7:R/W；位位置：[12]；默认值：1’b1；*/
/*description:这是比较第七单元计数与thr_h_lim值的启用位。*/
#define PCNT_THR_H_LIM_EN_U7  (BIT(12))
#define PCNT_THR_H_LIM_EN_U7_M  (BIT(12))
#define PCNT_THR_H_LIM_EN_U7_V  0x1
#define PCNT_THR_H_LIM_EN_U7_S  12
/* PCNT_THR_ZERO_EN_U7:R/W；位位置：[11]；默认值：1’b1；*/
/*description:这是将第七单元的计数与0值进行比较的启用位。*/
#define PCNT_THR_ZERO_EN_U7  (BIT(11))
#define PCNT_THR_ZERO_EN_U7_M  (BIT(11))
#define PCNT_THR_ZERO_EN_U7_V  0x1
#define PCNT_THR_ZERO_EN_U7_S  11
/* PCNT_FILTER_EN_U7:R/W；位位置：[10]；默认值：1’b1；*/
/*description:这是用于过滤第七单元输入信号的启用位。*/
#define PCNT_FILTER_EN_U7  (BIT(10))
#define PCNT_FILTER_EN_U7_M  (BIT(10))
#define PCNT_FILTER_EN_U7_V  0x1
#define PCNT_FILTER_EN_U7_S  10
/* PCNT_FILTER_threes_7:R/W；位位置：[9:0]；默认值：10'h10；*/
/*description:此寄存器用于过滤宽度小于第七单元的该值的加号。*/
#define PCNT_FILTER_THRES_U7  0x000003FF
#define PCNT_FILTER_THRES_U7_M  ((PCNT_FILTER_THRES_U7_V)<<(PCNT_FILTER_THRES_U7_S))
#define PCNT_FILTER_THRES_U7_V  0x3FF
#define PCNT_FILTER_THRES_U7_S  0

#define PCNT_U7_CONF1_REG          (DR_REG_PCNT_BASE + 0x0058)
/* PCNT_CNT_threshold_U7:R/W；比特位置：[31:16]；默认值：10'0；*/
/*description:此寄存器用于配置第七单元的thres1值。*/
#define PCNT_CNT_THRES1_U7  0x0000FFFF
#define PCNT_CNT_THRES1_U7_M  ((PCNT_CNT_THRES1_U7_V)<<(PCNT_CNT_THRES1_U7_S))
#define PCNT_CNT_THRES1_U7_V  0xFFFF
#define PCNT_CNT_THRES1_U7_S  16
/* PCNT_CNT_THRES0_U7:R/W；比特位置：[15:0]；默认值：10'0；*/
/*description:此寄存器用于配置第七单元的thres0值。*/
#define PCNT_CNT_THRES0_U7  0x0000FFFF
#define PCNT_CNT_THRES0_U7_M  ((PCNT_CNT_THRES0_U7_V)<<(PCNT_CNT_THRES0_U7_S))
#define PCNT_CNT_THRES0_U7_V  0xFFFF
#define PCNT_CNT_THRES0_U7_S  0

#define PCNT_U7_CONF2_REG          (DR_REG_PCNT_BASE + 0x005c)
/* PCNT_CNT_L_LIM_U7:R/W；比特位置：[31:16]；默认值：10'0；*/
/*description:此寄存器用于配置第七单元的thr_l_lim值。*/
#define PCNT_CNT_L_LIM_U7  0x0000FFFF
#define PCNT_CNT_L_LIM_U7_M  ((PCNT_CNT_L_LIM_U7_V)<<(PCNT_CNT_L_LIM_U7_S))
#define PCNT_CNT_L_LIM_U7_V  0xFFFF
#define PCNT_CNT_L_LIM_U7_S  16
/* PCNT_CNT_H_LIM_U7:R/W；比特位置：[15:0]；默认值：10'0；*/
/*description:此寄存器用于配置第七单元的thr_h_lim值。*/
#define PCNT_CNT_H_LIM_U7  0x0000FFFF
#define PCNT_CNT_H_LIM_U7_M  ((PCNT_CNT_H_LIM_U7_V)<<(PCNT_CNT_H_LIM_U7_S))
#define PCNT_CNT_H_LIM_U7_V  0xFFFF
#define PCNT_CNT_H_LIM_U7_S  0

#define PCNT_U0_CNT_REG          (DR_REG_PCNT_BASE + 0x0060)
/* PCNT_PLUS_CNT_U0:RO；比特位置：[15:0]；默认值：16'0；*/
/*description:此寄存器存储unit0的当前脉冲计数值。*/
#define PCNT_PLUS_CNT_U0  0x0000FFFF
#define PCNT_PLUS_CNT_U0_M  ((PCNT_PLUS_CNT_U0_V)<<(PCNT_PLUS_CNT_U0_S))
#define PCNT_PLUS_CNT_U0_V  0xFFFF
#define PCNT_PLUS_CNT_U0_S  0

#define PCNT_U1_CNT_REG          (DR_REG_PCNT_BASE + 0x0064)
/* PCNT_PLUS_CNT_U1:RO；比特位置：[15:0]；默认值：16'0；*/
/*description:此寄存器存储第一单元的当前脉冲计数值。*/
#define PCNT_PLUS_CNT_U1  0x0000FFFF
#define PCNT_PLUS_CNT_U1_M  ((PCNT_PLUS_CNT_U1_V)<<(PCNT_PLUS_CNT_U1_S))
#define PCNT_PLUS_CNT_U1_V  0xFFFF
#define PCNT_PLUS_CNT_U1_S  0

#define PCNT_U2_CNT_REG          (DR_REG_PCNT_BASE + 0x0068)
/* PCNT_PLUS_CNT_U2:RO；比特位置：[15:0]；默认值：16'0；*/
/*description:此寄存器存储第二单元的当前脉冲计数值。*/
#define PCNT_PLUS_CNT_U2  0x0000FFFF
#define PCNT_PLUS_CNT_U2_M  ((PCNT_PLUS_CNT_U2_V)<<(PCNT_PLUS_CNT_U2_S))
#define PCNT_PLUS_CNT_U2_V  0xFFFF
#define PCNT_PLUS_CNT_U2_S  0

#define PCNT_U3_CNT_REG          (DR_REG_PCNT_BASE + 0x006c)
/* PCNT_PLUS_CNT_U3:RO；比特位置：[15:0]；默认值：16'0；*/
/*description:此寄存器存储第三单元的当前脉冲计数值。*/
#define PCNT_PLUS_CNT_U3  0x0000FFFF
#define PCNT_PLUS_CNT_U3_M  ((PCNT_PLUS_CNT_U3_V)<<(PCNT_PLUS_CNT_U3_S))
#define PCNT_PLUS_CNT_U3_V  0xFFFF
#define PCNT_PLUS_CNT_U3_S  0

#define PCNT_U4_CNT_REG          (DR_REG_PCNT_BASE + 0x0070)
/* PCNT_PLUS_CNT_U4:RO；比特位置：[15:0]；默认值：16'0；*/
/*description:此寄存器存储第四单元的当前脉冲计数值。*/
#define PCNT_PLUS_CNT_U4  0x0000FFFF
#define PCNT_PLUS_CNT_U4_M  ((PCNT_PLUS_CNT_U4_V)<<(PCNT_PLUS_CNT_U4_S))
#define PCNT_PLUS_CNT_U4_V  0xFFFF
#define PCNT_PLUS_CNT_U4_S  0

#define PCNT_U5_CNT_REG          (DR_REG_PCNT_BASE + 0x0074)
/* PCNT_PLUS_CNT_U5:RO；比特位置：[15:0]；默认值：16'0；*/
/*description:此寄存器存储第五单元的当前脉冲计数值。*/
#define PCNT_PLUS_CNT_U5  0x0000FFFF
#define PCNT_PLUS_CNT_U5_M  ((PCNT_PLUS_CNT_U5_V)<<(PCNT_PLUS_CNT_U5_S))
#define PCNT_PLUS_CNT_U5_V  0xFFFF
#define PCNT_PLUS_CNT_U5_S  0

#define PCNT_U6_CNT_REG          (DR_REG_PCNT_BASE + 0x0078)
/* PCNT_PLUS_CNT_U6:RO；比特位置：[15:0]；默认值：16'0；*/
/*description:此寄存器存储第六单元的当前脉冲计数值。*/
#define PCNT_PLUS_CNT_U6  0x0000FFFF
#define PCNT_PLUS_CNT_U6_M  ((PCNT_PLUS_CNT_U6_V)<<(PCNT_PLUS_CNT_U6_S))
#define PCNT_PLUS_CNT_U6_V  0xFFFF
#define PCNT_PLUS_CNT_U6_S  0

#define PCNT_U7_CNT_REG          (DR_REG_PCNT_BASE + 0x007c)
/* PCNT_PLUS_CNT_U7:RO；比特位置：[15:0]；默认值：16'0；*/
/*description:此寄存器存储第七单元的当前脉冲计数值。*/
#define PCNT_PLUS_CNT_U7  0x0000FFFF
#define PCNT_PLUS_CNT_U7_M  ((PCNT_PLUS_CNT_U7_V)<<(PCNT_PLUS_CNT_U7_S))
#define PCNT_PLUS_CNT_U7_V  0xFFFF
#define PCNT_PLUS_CNT_U7_S  0

#define PCNT_INT_RAW_REG          (DR_REG_PCNT_BASE + 0x0080)
/* PCNT_CNT_THR_EVENT_U7_INT_RAW:RO；位位置：[7]；默认值：1’b0；*/
/*description:这是channel7事件的中断原始位。*/
#define PCNT_CNT_THR_EVENT_U7_INT_RAW  (BIT(7))
#define PCNT_CNT_THR_EVENT_U7_INT_RAW_M  (BIT(7))
#define PCNT_CNT_THR_EVENT_U7_INT_RAW_V  0x1
#define PCNT_CNT_THR_EVENT_U7_INT_RAW_S  7
/* PCNT_CNT_THR_EVENT_U6_INT_RAW:RO；位位置：[6]；默认值：1’b0；*/
/*description:这是channel6事件的中断原始位。*/
#define PCNT_CNT_THR_EVENT_U6_INT_RAW  (BIT(6))
#define PCNT_CNT_THR_EVENT_U6_INT_RAW_M  (BIT(6))
#define PCNT_CNT_THR_EVENT_U6_INT_RAW_V  0x1
#define PCNT_CNT_THR_EVENT_U6_INT_RAW_S  6
/* PCNT_CNT_THR_EVENT_U5_INT_RAW:RO；位位置：[5]；默认值：1’b0；*/
/*description:这是channel5事件的中断原始位。*/
#define PCNT_CNT_THR_EVENT_U5_INT_RAW  (BIT(5))
#define PCNT_CNT_THR_EVENT_U5_INT_RAW_M  (BIT(5))
#define PCNT_CNT_THR_EVENT_U5_INT_RAW_V  0x1
#define PCNT_CNT_THR_EVENT_U5_INT_RAW_S  5
/* PCNT_CNT_THR_EVENT_U4_INT_RAW:RO；位位置：[4]；默认值：1’b0；*/
/*description:这是channel4事件的中断原始位。*/
#define PCNT_CNT_THR_EVENT_U4_INT_RAW  (BIT(4))
#define PCNT_CNT_THR_EVENT_U4_INT_RAW_M  (BIT(4))
#define PCNT_CNT_THR_EVENT_U4_INT_RAW_V  0x1
#define PCNT_CNT_THR_EVENT_U4_INT_RAW_S  4
/* PCNT_CNT_THR_EVENT_U3_INT_RAW:RO；位位置：[3]；默认值：1’b0；*/
/*description:这是channel3事件的中断原始位。*/
#define PCNT_CNT_THR_EVENT_U3_INT_RAW  (BIT(3))
#define PCNT_CNT_THR_EVENT_U3_INT_RAW_M  (BIT(3))
#define PCNT_CNT_THR_EVENT_U3_INT_RAW_V  0x1
#define PCNT_CNT_THR_EVENT_U3_INT_RAW_S  3
/* PCNT_CNT_THR_EVENT_U2_INT_RAW:RO；位位置：[2]；默认值：1’b0；*/
/*description:这是channel2事件的中断原始位。*/
#define PCNT_CNT_THR_EVENT_U2_INT_RAW  (BIT(2))
#define PCNT_CNT_THR_EVENT_U2_INT_RAW_M  (BIT(2))
#define PCNT_CNT_THR_EVENT_U2_INT_RAW_V  0x1
#define PCNT_CNT_THR_EVENT_U2_INT_RAW_S  2
/* PCNT_CNT_THR_EVENT_U1_INT_RAW:RO；位位置：[1]；默认值：1’b0；*/
/*description:这是channel1事件的中断原始位。*/
#define PCNT_CNT_THR_EVENT_U1_INT_RAW  (BIT(1))
#define PCNT_CNT_THR_EVENT_U1_INT_RAW_M  (BIT(1))
#define PCNT_CNT_THR_EVENT_U1_INT_RAW_V  0x1
#define PCNT_CNT_THR_EVENT_U1_INT_RAW_S  1
/* PCNT_CNT_THR_EVENT_U0_INT_RAW:RO；位位置：[0]；默认值：1’b0；*/
/*description:这是channel0事件的中断原始位。*/
#define PCNT_CNT_THR_EVENT_U0_INT_RAW  (BIT(0))
#define PCNT_CNT_THR_EVENT_U0_INT_RAW_M  (BIT(0))
#define PCNT_CNT_THR_EVENT_U0_INT_RAW_V  0x1
#define PCNT_CNT_THR_EVENT_U0_INT_RAW_S  0

#define PCNT_INT_ST_REG          (DR_REG_PCNT_BASE + 0x0084)
/* PCNT_CNT_THR_EVENT_U7_INT_ST:RO；位位置：[7]；默认值：1’b0；*/
/*description:这是channel7事件的中断状态位。*/
#define PCNT_CNT_THR_EVENT_U7_INT_ST  (BIT(7))
#define PCNT_CNT_THR_EVENT_U7_INT_ST_M  (BIT(7))
#define PCNT_CNT_THR_EVENT_U7_INT_ST_V  0x1
#define PCNT_CNT_THR_EVENT_U7_INT_ST_S  7
/* PCNT_CNT_THR_EVENT_U6_INT_ST:RO；位位置：[6]；默认值：1’b0；*/
/*description:这是channel6事件的中断状态位。*/
#define PCNT_CNT_THR_EVENT_U6_INT_ST  (BIT(6))
#define PCNT_CNT_THR_EVENT_U6_INT_ST_M  (BIT(6))
#define PCNT_CNT_THR_EVENT_U6_INT_ST_V  0x1
#define PCNT_CNT_THR_EVENT_U6_INT_ST_S  6
/* PCNT_CNT_THR_EVENT_U5_INT_ST:RO；位位置：[5]；默认值：1’b0；*/
/*description:这是channel5事件的中断状态位。*/
#define PCNT_CNT_THR_EVENT_U5_INT_ST  (BIT(5))
#define PCNT_CNT_THR_EVENT_U5_INT_ST_M  (BIT(5))
#define PCNT_CNT_THR_EVENT_U5_INT_ST_V  0x1
#define PCNT_CNT_THR_EVENT_U5_INT_ST_S  5
/* PCNT_CNT_THR_EVENT_U4_INT_ST:RO；位位置：[4]；默认值：1’b0；*/
/*description:这是channel4事件的中断状态位。*/
#define PCNT_CNT_THR_EVENT_U4_INT_ST  (BIT(4))
#define PCNT_CNT_THR_EVENT_U4_INT_ST_M  (BIT(4))
#define PCNT_CNT_THR_EVENT_U4_INT_ST_V  0x1
#define PCNT_CNT_THR_EVENT_U4_INT_ST_S  4
/* PCNT_CNT_THR_EVENT_U3_INT_ST:RO；位位置：[3]；默认值：1’b0；*/
/*description:这是channel3事件的中断状态位。*/
#define PCNT_CNT_THR_EVENT_U3_INT_ST  (BIT(3))
#define PCNT_CNT_THR_EVENT_U3_INT_ST_M  (BIT(3))
#define PCNT_CNT_THR_EVENT_U3_INT_ST_V  0x1
#define PCNT_CNT_THR_EVENT_U3_INT_ST_S  3
/* PCNT_CNT_THR_EVENT_U2_INT_ST:RO；位位置：[2]；默认值：1’b0；*/
/*description:这是channel2事件的中断状态位。*/
#define PCNT_CNT_THR_EVENT_U2_INT_ST  (BIT(2))
#define PCNT_CNT_THR_EVENT_U2_INT_ST_M  (BIT(2))
#define PCNT_CNT_THR_EVENT_U2_INT_ST_V  0x1
#define PCNT_CNT_THR_EVENT_U2_INT_ST_S  2
/* PCNT_CNT_THR_EVENT_U1_INT_ST:RO；位位置：[1]；默认值：1’b0；*/
/*description:这是channel1事件的中断状态位。*/
#define PCNT_CNT_THR_EVENT_U1_INT_ST  (BIT(1))
#define PCNT_CNT_THR_EVENT_U1_INT_ST_M  (BIT(1))
#define PCNT_CNT_THR_EVENT_U1_INT_ST_V  0x1
#define PCNT_CNT_THR_EVENT_U1_INT_ST_S  1
/* PCNT_CNT_THR_EVENT_U0_INT_ST:RO；位位置：[0]；默认值：1’b0；*/
/*description:这是channel0事件的中断状态位。*/
#define PCNT_CNT_THR_EVENT_U0_INT_ST  (BIT(0))
#define PCNT_CNT_THR_EVENT_U0_INT_ST_M  (BIT(0))
#define PCNT_CNT_THR_EVENT_U0_INT_ST_V  0x1
#define PCNT_CNT_THR_EVENT_U0_INT_ST_S  0

#define PCNT_INT_ENA_REG          (DR_REG_PCNT_BASE + 0x0088)
/* PCNT_CNT_THR_EVENT_U7_INT_ENA:R/W；位位置：[7]；默认值：1’b0；*/
/*description:这是channel7事件的中断启用位。*/
#define PCNT_CNT_THR_EVENT_U7_INT_ENA  (BIT(7))
#define PCNT_CNT_THR_EVENT_U7_INT_ENA_M  (BIT(7))
#define PCNT_CNT_THR_EVENT_U7_INT_ENA_V  0x1
#define PCNT_CNT_THR_EVENT_U7_INT_ENA_S  7
/* PCNT_CNT_THR_EVENT_U6_INT_ENA:R/W；位位置：[6]；默认值：1’b0；*/
/*description:这是channel6事件的中断启用位。*/
#define PCNT_CNT_THR_EVENT_U6_INT_ENA  (BIT(6))
#define PCNT_CNT_THR_EVENT_U6_INT_ENA_M  (BIT(6))
#define PCNT_CNT_THR_EVENT_U6_INT_ENA_V  0x1
#define PCNT_CNT_THR_EVENT_U6_INT_ENA_S  6
/* PCNT_CNT_THR_EVENT_U5_INT_ENA:R/W；位位置：[5]；默认值：1’b0；*/
/*description:这是channel5事件的中断启用位。*/
#define PCNT_CNT_THR_EVENT_U5_INT_ENA  (BIT(5))
#define PCNT_CNT_THR_EVENT_U5_INT_ENA_M  (BIT(5))
#define PCNT_CNT_THR_EVENT_U5_INT_ENA_V  0x1
#define PCNT_CNT_THR_EVENT_U5_INT_ENA_S  5
/* PCNT_CNT_THR_EVENT_U4_INT_ENA:R/W；位位置：[4]；默认值：1’b0；*/
/*description:这是channel4事件的中断启用位。*/
#define PCNT_CNT_THR_EVENT_U4_INT_ENA  (BIT(4))
#define PCNT_CNT_THR_EVENT_U4_INT_ENA_M  (BIT(4))
#define PCNT_CNT_THR_EVENT_U4_INT_ENA_V  0x1
#define PCNT_CNT_THR_EVENT_U4_INT_ENA_S  4
/* PCNT_CNT_THR_EVENT_U3_INT_ENA:R/W；位位置：[3]；默认值：1’b0；*/
/*description:这是channel3事件的中断启用位。*/
#define PCNT_CNT_THR_EVENT_U3_INT_ENA  (BIT(3))
#define PCNT_CNT_THR_EVENT_U3_INT_ENA_M  (BIT(3))
#define PCNT_CNT_THR_EVENT_U3_INT_ENA_V  0x1
#define PCNT_CNT_THR_EVENT_U3_INT_ENA_S  3
/* PCNT_CNT_THR_EVENT_U2_INT_ENA:R/W；位位置：[2]；默认值：1’b0；*/
/*description:这是channel2事件的中断启用位。*/
#define PCNT_CNT_THR_EVENT_U2_INT_ENA  (BIT(2))
#define PCNT_CNT_THR_EVENT_U2_INT_ENA_M  (BIT(2))
#define PCNT_CNT_THR_EVENT_U2_INT_ENA_V  0x1
#define PCNT_CNT_THR_EVENT_U2_INT_ENA_S  2
/* PCNT_CNT_THR_EVENT_U1_INT_ENA:R/W；位位置：[1]；默认值：1’b0；*/
/*description:这是channel1事件的中断启用位。*/
#define PCNT_CNT_THR_EVENT_U1_INT_ENA  (BIT(1))
#define PCNT_CNT_THR_EVENT_U1_INT_ENA_M  (BIT(1))
#define PCNT_CNT_THR_EVENT_U1_INT_ENA_V  0x1
#define PCNT_CNT_THR_EVENT_U1_INT_ENA_S  1
/* PCNT_CNT_THR_EVENT_U0_INT_ENA:R/W；位位置：[0]；默认值：1’b0；*/
/*description:这是channel0事件的中断启用位。*/
#define PCNT_CNT_THR_EVENT_U0_INT_ENA  (BIT(0))
#define PCNT_CNT_THR_EVENT_U0_INT_ENA_M  (BIT(0))
#define PCNT_CNT_THR_EVENT_U0_INT_ENA_V  0x1
#define PCNT_CNT_THR_EVENT_U0_INT_ENA_S  0

#define PCNT_INT_CLR_REG          (DR_REG_PCNT_BASE + 0x008c)
/* PCNT_CNT_THR_EVENT_U7_INT_CLR:WO；位位置：[7]；默认值：1’b0；*/
/*description:设置此位以清除channel7事件中断。*/
#define PCNT_CNT_THR_EVENT_U7_INT_CLR  (BIT(7))
#define PCNT_CNT_THR_EVENT_U7_INT_CLR_M  (BIT(7))
#define PCNT_CNT_THR_EVENT_U7_INT_CLR_V  0x1
#define PCNT_CNT_THR_EVENT_U7_INT_CLR_S  7
/* PCNT_CNT_THR_EVENT_U6_INT_CLR:WO；位位置：[6]；默认值：1’b0；*/
/*description:设置此位以清除channel6事件中断。*/
#define PCNT_CNT_THR_EVENT_U6_INT_CLR  (BIT(6))
#define PCNT_CNT_THR_EVENT_U6_INT_CLR_M  (BIT(6))
#define PCNT_CNT_THR_EVENT_U6_INT_CLR_V  0x1
#define PCNT_CNT_THR_EVENT_U6_INT_CLR_S  6
/* PCNT_CNT_THR_EVENT_U5_INT_CLR:WO；位位置：[5]；默认值：1’b0；*/
/*description:设置此位以清除channel5事件中断。*/
#define PCNT_CNT_THR_EVENT_U5_INT_CLR  (BIT(5))
#define PCNT_CNT_THR_EVENT_U5_INT_CLR_M  (BIT(5))
#define PCNT_CNT_THR_EVENT_U5_INT_CLR_V  0x1
#define PCNT_CNT_THR_EVENT_U5_INT_CLR_S  5
/* PCNT_CNT_THR_EVENT_U4_INT_CLR:WO；位位置：[4]；默认值：1’b0；*/
/*description:设置此位以清除channel4事件中断。*/
#define PCNT_CNT_THR_EVENT_U4_INT_CLR  (BIT(4))
#define PCNT_CNT_THR_EVENT_U4_INT_CLR_M  (BIT(4))
#define PCNT_CNT_THR_EVENT_U4_INT_CLR_V  0x1
#define PCNT_CNT_THR_EVENT_U4_INT_CLR_S  4
/* PCNT_CNT_THR_EVENT_U3_INT_CLR:WO；位位置：[3]；默认值：1’b0；*/
/*description:设置此位以清除channel3事件中断。*/
#define PCNT_CNT_THR_EVENT_U3_INT_CLR  (BIT(3))
#define PCNT_CNT_THR_EVENT_U3_INT_CLR_M  (BIT(3))
#define PCNT_CNT_THR_EVENT_U3_INT_CLR_V  0x1
#define PCNT_CNT_THR_EVENT_U3_INT_CLR_S  3
/* PCNT_CNT_THR_EVENT_U2_INT_CLR:WO；位位置：[2]；默认值：1’b0；*/
/*description:设置此位以清除channel2事件中断。*/
#define PCNT_CNT_THR_EVENT_U2_INT_CLR  (BIT(2))
#define PCNT_CNT_THR_EVENT_U2_INT_CLR_M  (BIT(2))
#define PCNT_CNT_THR_EVENT_U2_INT_CLR_V  0x1
#define PCNT_CNT_THR_EVENT_U2_INT_CLR_S  2
/* PCNT_CNT_THR_EVENT_U1_INT_CLR:WO；位位置：[1]；默认值：1’b0；*/
/*description:设置此位以清除channel1事件中断。*/
#define PCNT_CNT_THR_EVENT_U1_INT_CLR  (BIT(1))
#define PCNT_CNT_THR_EVENT_U1_INT_CLR_M  (BIT(1))
#define PCNT_CNT_THR_EVENT_U1_INT_CLR_V  0x1
#define PCNT_CNT_THR_EVENT_U1_INT_CLR_S  1
/* PCNT_CNT_THR_EVENT_U0_INT_CLR:WO；位位置：[0]；默认值：1’b0；*/
/*description:设置此位以清除channel0事件中断。*/
#define PCNT_CNT_THR_EVENT_U0_INT_CLR  (BIT(0))
#define PCNT_CNT_THR_EVENT_U0_INT_CLR_M  (BIT(0))
#define PCNT_CNT_THR_EVENT_U0_INT_CLR_V  0x1
#define PCNT_CNT_THR_EVENT_U0_INT_CLR_S  0

#define PCNT_U0_STATUS_REG          (DR_REG_PCNT_BASE + 0x0090)
/* PCNT_CORE_STATUS_U0:RO；位位置：[31:0]；默认值：32'h0；*/
/*说明：*/
#define PCNT_CORE_STATUS_U0  0xFFFFFFFF
#define PCNT_CORE_STATUS_U0_M  ((PCNT_CORE_STATUS_U0_V)<<(PCNT_CORE_STATUS_U0_S))
#define PCNT_CORE_STATUS_U0_V  0xFFFFFFFF
#define PCNT_CORE_STATUS_U0_S  0
/*0：正值归零；1： 负值为零；2： 计数器值为负值；3： 计数器值正值*/
#define PCNT_STATUS_CNT_MODE    0x3
#define PCNT_STATUS_CNT_MODE_M  ((PCNT_STATUS_CNT_MODE_V)<<(PCNT_STATUS_CNT_MODE_S))
#define PCNT_STATUS_CNT_MODE_V  0x3
#define PCNT_STATUS_CNT_MODE_S  0
/* 计数器值等于threshold1*/
#define PCNT_STATUS_THRES1    BIT(2)
#define PCNT_STATUS_THRES1_M  BIT(2)
#define PCNT_STATUS_THRES1_V  0x1
#define PCNT_STATUS_THRES1_S  2
/* 计数器值等于threshold0*/
#define PCNT_STATUS_THRES0    BIT(3)
#define PCNT_STATUS_THRES0_M  BIT(3)
#define PCNT_STATUS_THRES0_V  0x1
#define PCNT_STATUS_THRES0_S  3
/* 计数器值达到hlim*/
#define PCNT_STATUS_L_LIM    BIT(4)
#define PCNT_STATUS_L_LIM_M  BIT(4)
#define PCNT_STATUS_L_LIM_V  0x1
#define PCNT_STATUS_L_LIM_S  4
/* 计数器值达到l_lim*/
#define PCNT_STATUS_H_LIM    BIT(5)
#define PCNT_STATUS_H_LIM_M  BIT(5)
#define PCNT_STATUS_H_LIM_V  0x1
#define PCNT_STATUS_H_LIM_S  5
/* 计数器值等于零*/
#define PCNT_STATUS_ZERO    BIT(6)
#define PCNT_STATUS_ZERO_M  BIT(6)
#define PCNT_STATUS_ZERO_V  0x1
#define PCNT_STATUS_ZERO_S  6

#define PCNT_U1_STATUS_REG          (DR_REG_PCNT_BASE + 0x0094)
/* PCNT_CORE_STATUS_U1:RO；位位置：[31:0]；默认值：32'h0；*/
/*说明：*/
#define PCNT_CORE_STATUS_U1  0xFFFFFFFF
#define PCNT_CORE_STATUS_U1_M  ((PCNT_CORE_STATUS_U1_V)<<(PCNT_CORE_STATUS_U1_S))
#define PCNT_CORE_STATUS_U1_V  0xFFFFFFFF
#define PCNT_CORE_STATUS_U1_S  0

#define PCNT_U2_STATUS_REG          (DR_REG_PCNT_BASE + 0x0098)
/* PCNT_CORE_STATUS_U2:RO；位位置：[31:0]；默认值：32'h0；*/
/*说明：*/
#define PCNT_CORE_STATUS_U2  0xFFFFFFFF
#define PCNT_CORE_STATUS_U2_M  ((PCNT_CORE_STATUS_U2_V)<<(PCNT_CORE_STATUS_U2_S))
#define PCNT_CORE_STATUS_U2_V  0xFFFFFFFF
#define PCNT_CORE_STATUS_U2_S  0

#define PCNT_U3_STATUS_REG          (DR_REG_PCNT_BASE + 0x009c)
/* PCNT_CORE_STATUS_U3:RO；位位置：[31:0]；默认值：32'h0；*/
/*说明：*/
#define PCNT_CORE_STATUS_U3  0xFFFFFFFF
#define PCNT_CORE_STATUS_U3_M  ((PCNT_CORE_STATUS_U3_V)<<(PCNT_CORE_STATUS_U3_S))
#define PCNT_CORE_STATUS_U3_V  0xFFFFFFFF
#define PCNT_CORE_STATUS_U3_S  0

#define PCNT_U4_STATUS_REG          (DR_REG_PCNT_BASE + 0x00a0)
/* PCNT_CORE_STATUS_U4:RO；位位置：[31:0]；默认值：32'h0；*/
/*说明：*/
#define PCNT_CORE_STATUS_U4  0xFFFFFFFF
#define PCNT_CORE_STATUS_U4_M  ((PCNT_CORE_STATUS_U4_V)<<(PCNT_CORE_STATUS_U4_S))
#define PCNT_CORE_STATUS_U4_V  0xFFFFFFFF
#define PCNT_CORE_STATUS_U4_S  0

#define PCNT_U5_STATUS_REG          (DR_REG_PCNT_BASE + 0x00a4)
/* PCNT_CORE_STATUS_U5:RO；位位置：[31:0]；默认值：32'h0；*/
/*说明：*/
#define PCNT_CORE_STATUS_U5  0xFFFFFFFF
#define PCNT_CORE_STATUS_U5_M  ((PCNT_CORE_STATUS_U5_V)<<(PCNT_CORE_STATUS_U5_S))
#define PCNT_CORE_STATUS_U5_V  0xFFFFFFFF
#define PCNT_CORE_STATUS_U5_S  0

#define PCNT_U6_STATUS_REG          (DR_REG_PCNT_BASE + 0x00a8)
/* PCNT_CORE_STATUS_U6:RO；位位置：[31:0]；默认值：32'h0；*/
/*说明：*/
#define PCNT_CORE_STATUS_U6  0xFFFFFFFF
#define PCNT_CORE_STATUS_U6_M  ((PCNT_CORE_STATUS_U6_V)<<(PCNT_CORE_STATUS_U6_S))
#define PCNT_CORE_STATUS_U6_V  0xFFFFFFFF
#define PCNT_CORE_STATUS_U6_S  0

#define PCNT_U7_STATUS_REG          (DR_REG_PCNT_BASE + 0x00ac)
/* PCNT_CORE_STATUS_U7:RO；位位置：[31:0]；默认值：32'h0；*/
/*说明：*/
#define PCNT_CORE_STATUS_U7  0xFFFFFFFF
#define PCNT_CORE_STATUS_U7_M  ((PCNT_CORE_STATUS_U7_V)<<(PCNT_CORE_STATUS_U7_S))
#define PCNT_CORE_STATUS_U7_V  0xFFFFFFFF
#define PCNT_CORE_STATUS_U7_S  0

#define PCNT_CTRL_REG          (DR_REG_PCNT_BASE + 0x00b0)
/* PCNT_CLK_EN:R/W；位位置：[16]；默认值：1’b0；*/
/*说明：*/
#define PCNT_CLK_EN  (BIT(16))
#define PCNT_CLK_EN_M  (BIT(16))
#define PCNT_CLK_EN_V  0x1
#define PCNT_CLK_EN_S  16
/* PCNT_CNT_PAUSE_U7:R/W；位位置：[15]；默认值：1’b0；*/
/*description:设置此位以暂停第七单元的计数器。*/
#define PCNT_CNT_PAUSE_U7  (BIT(15))
#define PCNT_CNT_PAUSE_U7_M  (BIT(15))
#define PCNT_CNT_PAUSE_U7_V  0x1
#define PCNT_CNT_PAUSE_U7_S  15
/* PCNT_PLUS_CNT_RST_U7:R/W；位位置：[14]；默认值：1’b1；*/
/*description:设置此位以清除第七单元的计数器。*/
#define PCNT_PLUS_CNT_RST_U7  (BIT(14))
#define PCNT_PLUS_CNT_RST_U7_M  (BIT(14))
#define PCNT_PLUS_CNT_RST_U7_V  0x1
#define PCNT_PLUS_CNT_RST_U7_S  14
/* PCNT_CNT_PAUSE_U6:R/W；位位置：[13]；默认值：1’b0；*/
/*description:设置此位以暂停第六单元的计数器。*/
#define PCNT_CNT_PAUSE_U6  (BIT(13))
#define PCNT_CNT_PAUSE_U6_M  (BIT(13))
#define PCNT_CNT_PAUSE_U6_V  0x1
#define PCNT_CNT_PAUSE_U6_S  13
/* PCNT_PLUS_CNT_RST_U6:R/W；位位置：[12]；默认值：1’b1；*/
/*description:设置此位以清除第六单元的计数器。*/
#define PCNT_PLUS_CNT_RST_U6  (BIT(12))
#define PCNT_PLUS_CNT_RST_U6_M  (BIT(12))
#define PCNT_PLUS_CNT_RST_U6_V  0x1
#define PCNT_PLUS_CNT_RST_U6_S  12
/* PCNT_CNT_PAUSE_U5:R/W；位位置：[11]；默认值：1’b0；*/
/*description:设置此位以暂停第五单元的计数器。*/
#define PCNT_CNT_PAUSE_U5  (BIT(11))
#define PCNT_CNT_PAUSE_U5_M  (BIT(11))
#define PCNT_CNT_PAUSE_U5_V  0x1
#define PCNT_CNT_PAUSE_U5_S  11
/* PCNT_PLUS_CNT_RST_U5:R/W；位位置：[10]；默认值：1’b1；*/
/*description:设置此位以清除第五单元的计数器。*/
#define PCNT_PLUS_CNT_RST_U5  (BIT(10))
#define PCNT_PLUS_CNT_RST_U5_M  (BIT(10))
#define PCNT_PLUS_CNT_RST_U5_V  0x1
#define PCNT_PLUS_CNT_RST_U5_S  10
/* PCNT_CNT_PAUSE_U4:R/W；位位置：[9]；默认值：1’b0；*/
/*description:设置此位以暂停第四单元的计数器。*/
#define PCNT_CNT_PAUSE_U4  (BIT(9))
#define PCNT_CNT_PAUSE_U4_M  (BIT(9))
#define PCNT_CNT_PAUSE_U4_V  0x1
#define PCNT_CNT_PAUSE_U4_S  9
/* PCNT_PLUS_CNT_RST_U4:R/W；位位置：[8]；默认值：1’b1；*/
/*description:设置此位以清除第四单元的计数器。*/
#define PCNT_PLUS_CNT_RST_U4  (BIT(8))
#define PCNT_PLUS_CNT_RST_U4_M  (BIT(8))
#define PCNT_PLUS_CNT_RST_U4_V  0x1
#define PCNT_PLUS_CNT_RST_U4_S  8
/* PCNT_CNT_PAUSE_U3:R/W；位位置：[7]；默认值：1’b0；*/
/*description:设置此位以暂停第三单元的计数器。*/
#define PCNT_CNT_PAUSE_U3  (BIT(7))
#define PCNT_CNT_PAUSE_U3_M  (BIT(7))
#define PCNT_CNT_PAUSE_U3_V  0x1
#define PCNT_CNT_PAUSE_U3_S  7
/* PCNT_PLUS_CNT_RST_U3:R/W；位位置：[6]；默认值：1’b1；*/
/*description:设置此位以清除第三单元的计数器。*/
#define PCNT_PLUS_CNT_RST_U3  (BIT(6))
#define PCNT_PLUS_CNT_RST_U3_M  (BIT(6))
#define PCNT_PLUS_CNT_RST_U3_V  0x1
#define PCNT_PLUS_CNT_RST_U3_S  6
/* PCNT_CNT_PAUSE_U2:R/W；位位置：[5]；默认值：1’b0；*/
/*description:设置此位以暂停第二单元的计数器。*/
#define PCNT_CNT_PAUSE_U2  (BIT(5))
#define PCNT_CNT_PAUSE_U2_M  (BIT(5))
#define PCNT_CNT_PAUSE_U2_V  0x1
#define PCNT_CNT_PAUSE_U2_S  5
/* PCNT_PLUS_CNT_RST_U2:R/W；位位置：[4]；默认值：1’b1；*/
/*description:设置此位以清除第二单元的计数器。*/
#define PCNT_PLUS_CNT_RST_U2  (BIT(4))
#define PCNT_PLUS_CNT_RST_U2_M  (BIT(4))
#define PCNT_PLUS_CNT_RST_U2_V  0x1
#define PCNT_PLUS_CNT_RST_U2_S  4
/* PCNT_CNT_PAUSE_U1:R/W；位位置：[3]；默认值：1’b0；*/
/*description:设置此位以暂停第一单元的计数器。*/
#define PCNT_CNT_PAUSE_U1  (BIT(3))
#define PCNT_CNT_PAUSE_U1_M  (BIT(3))
#define PCNT_CNT_PAUSE_U1_V  0x1
#define PCNT_CNT_PAUSE_U1_S  3
/* PCNT_PLUS_CNT_RST_U1:R/W；位位置：[2]；默认值：1’b1；*/
/*description:设置此位以清除第一单元的计数器。*/
#define PCNT_PLUS_CNT_RST_U1  (BIT(2))
#define PCNT_PLUS_CNT_RST_U1_M  (BIT(2))
#define PCNT_PLUS_CNT_RST_U1_V  0x1
#define PCNT_PLUS_CNT_RST_U1_S  2
/* PCNT_CNT_PAUSE_U0:R/W；位位置：[1]；默认值：1’b0；*/
/*description:设置此位以暂停unit0的计数器。*/
#define PCNT_CNT_PAUSE_U0  (BIT(1))
#define PCNT_CNT_PAUSE_U0_M  (BIT(1))
#define PCNT_CNT_PAUSE_U0_V  0x1
#define PCNT_CNT_PAUSE_U0_S  1
/* PCNT_PLUS_CNT_RST_U0:R/W；位位置：[0]；默认值：1’b1；*/
/*description:设置此位以清除unit0的计数器。*/
#define PCNT_PLUS_CNT_RST_U0  (BIT(0))
#define PCNT_PLUS_CNT_RST_U0_M  (BIT(0))
#define PCNT_PLUS_CNT_RST_U0_V  0x1
#define PCNT_PLUS_CNT_RST_U0_S  0

#define PCNT_DATE_REG          (DR_REG_PCNT_BASE + 0x00fc)
/* PCNT_DATE:R/W；位位置：[31:0]；默认值：32'h14122600；*/
/*说明：*/
#define PCNT_DATE  0xFFFFFFFF
#define PCNT_DATE_M  ((PCNT_DATE_V)<<(PCNT_DATE_S))
#define PCNT_DATE_V  0xFFFFFFFF
#define PCNT_DATE_S  0




#endif /*_SOC_PCNT_REG_H_ */

