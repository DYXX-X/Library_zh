/*
 * SPDX文件版权文本：2020-2021浓缩咖啡系统（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */

#pragma once

/**
 * @file i2c应用程序
 * @brief 数字PLL（BBPLL）的寄存器定义
 *
 * 此文件列出位于内部配置总线上的BBPLL的寄存器字段。这些定义通过i2c_rtc_clk中定义的宏使用。h、 通过rtc_clk.c中的rtc_clk_cpu_freq_set函数。
 */

#define I2C_BBPLL           0x66
#define I2C_BBPLL_HOSTID    0


#define I2C_BBPLL_IR_CAL_DELAY        0
#define I2C_BBPLL_IR_CAL_DELAY_MSB    3
#define I2C_BBPLL_IR_CAL_DELAY_LSB    0

#define I2C_BBPLL_IR_CAL_CK_DIV        0
#define I2C_BBPLL_IR_CAL_CK_DIV_MSB    7
#define I2C_BBPLL_IR_CAL_CK_DIV_LSB    4

#define I2C_BBPLL_IR_CAL_EXT_CAP        1
#define I2C_BBPLL_IR_CAL_EXT_CAP_MSB    3
#define I2C_BBPLL_IR_CAL_EXT_CAP_LSB    0

#define I2C_BBPLL_IR_CAL_ENX_CAP        1
#define I2C_BBPLL_IR_CAL_ENX_CAP_MSB    4
#define I2C_BBPLL_IR_CAL_ENX_CAP_LSB    4

#define I2C_BBPLL_IR_CAL_RSTB        1
#define I2C_BBPLL_IR_CAL_RSTB_MSB    5
#define I2C_BBPLL_IR_CAL_RSTB_LSB    5

#define I2C_BBPLL_IR_CAL_START        1
#define I2C_BBPLL_IR_CAL_START_MSB    6
#define I2C_BBPLL_IR_CAL_START_LSB    6

#define I2C_BBPLL_IR_CAL_UNSTOP        1
#define I2C_BBPLL_IR_CAL_UNSTOP_MSB    7
#define I2C_BBPLL_IR_CAL_UNSTOP_LSB    7

#define I2C_BBPLL_OC_REF_DIV        2
#define I2C_BBPLL_OC_REF_DIV_MSB    3
#define I2C_BBPLL_OC_REF_DIV_LSB    0

#define I2C_BBPLL_OC_DIV        3
#define I2C_BBPLL_OC_DIV_MSB    5
#define I2C_BBPLL_OC_DIV_LSB    0

#define I2C_BBPLL_OC_CHGP_DCUR        4
#define I2C_BBPLL_OC_CHGP_DCUR_MSB    2
#define I2C_BBPLL_OC_CHGP_DCUR_LSB    0

#define I2C_BBPLL_OC_BUFF_DCUR        4
#define I2C_BBPLL_OC_BUFF_DCUR_MSB    5
#define I2C_BBPLL_OC_BUFF_DCUR_LSB    3

#define I2C_BBPLL_OC_TSCHGP        4
#define I2C_BBPLL_OC_TSCHGP_MSB    6
#define I2C_BBPLL_OC_TSCHGP_LSB    6

#define I2C_BBPLL_OC_ENB_FCAL        4
#define I2C_BBPLL_OC_ENB_FCAL_MSB    7
#define I2C_BBPLL_OC_ENB_FCAL_LSB    7

#define I2C_BBPLL_OC_LPF_DR        5
#define I2C_BBPLL_OC_LPF_DR_MSB    1
#define I2C_BBPLL_OC_LPF_DR_LSB    0

#define I2C_BBPLL_OC_VCO_DCUR        5
#define I2C_BBPLL_OC_VCO_DCUR_MSB    3
#define I2C_BBPLL_OC_VCO_DCUR_LSB    2

#define I2C_BBPLL_OC_DHREF_SEL        5
#define I2C_BBPLL_OC_DHREF_SEL_MSB    5
#define I2C_BBPLL_OC_DHREF_SEL_LSB    4

#define I2C_BBPLL_OC_DLREF_SEL        5
#define I2C_BBPLL_OC_DLREF_SEL_MSB    7
#define I2C_BBPLL_OC_DLREF_SEL_LSB    6

#define I2C_BBPLL_OR_CAL_CAP        8
#define I2C_BBPLL_OR_CAL_CAP_MSB    3
#define I2C_BBPLL_OR_CAL_CAP_LSB    0

#define I2C_BBPLL_OR_CAL_UDF        8
#define I2C_BBPLL_OR_CAL_UDF_MSB    4
#define I2C_BBPLL_OR_CAL_UDF_LSB    4

#define I2C_BBPLL_OR_CAL_OVF        8
#define I2C_BBPLL_OR_CAL_OVF_MSB    5
#define I2C_BBPLL_OR_CAL_OVF_LSB    5

#define I2C_BBPLL_OR_CAL_END        8
#define I2C_BBPLL_OR_CAL_END_MSB    6
#define I2C_BBPLL_OR_CAL_END_LSB    6

#define I2C_BBPLL_OR_LOCK        8
#define I2C_BBPLL_OR_LOCK_MSB    7
#define I2C_BBPLL_OR_LOCK_LSB    7

#define I2C_BBPLL_DTEST        10
#define I2C_BBPLL_DTEST_MSB    1
#define I2C_BBPLL_DTEST_LSB    0

#define I2C_BBPLL_ENT_PLL        10
#define I2C_BBPLL_ENT_PLL_MSB    2
#define I2C_BBPLL_ENT_PLL_LSB    2

#define I2C_BBPLL_DIV_CPU        10
#define I2C_BBPLL_DIV_CPU_MSB    3
#define I2C_BBPLL_DIV_CPU_LSB    3

