/*
 * SPDX文件版权文本：2015-2021浓缩咖啡系统（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */

#pragma once

/**
 * @file 注册表项
 * @brief 数字PLL（BBPLL）的寄存器定义
 *
 * 此文件列出位于内部配置总线上的BBPLL的寄存器字段。这些定义通过regi2c_ctrl中定义的宏使用。h、 通过rtc_clk.c中的rtc_clk_cpu_freq_set函数。
 */

#define I2C_BBPLL           0x66
#define I2C_BBPLL_HOSTID    4

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

#define I2C_BBPLL_OC_DIV_10_8        2
#define I2C_BBPLL_OC_DIV_10_8_MSB    6
#define I2C_BBPLL_OC_DIV_10_8_LSB    4

#define I2C_BBPLL_OC_LREF        2
#define I2C_BBPLL_OC_LREF_MSB    7
#define I2C_BBPLL_OC_LREF_LSB    7

#define I2C_BBPLL_OC_DIV_7_0        3
#define I2C_BBPLL_OC_DIV_7_0_MSB    7
#define I2C_BBPLL_OC_DIV_7_0_LSB    0

#define I2C_BBPLL_OC_ENB_FCAL        4
#define I2C_BBPLL_OC_ENB_FCAL_MSB    0
#define I2C_BBPLL_OC_ENB_FCAL_LSB    0

#define I2C_BBPLL_OC_DCHGP        4
#define I2C_BBPLL_OC_DCHGP_MSB    3
#define I2C_BBPLL_OC_DCHGP_LSB    1

#define I2C_BBPLL_OC_DHREF_SEL        4
#define I2C_BBPLL_OC_DHREF_SEL_MSB    5
#define I2C_BBPLL_OC_DHREF_SEL_LSB    4

#define I2C_BBPLL_OC_DLREF_SEL        4
#define I2C_BBPLL_OC_DLREF_SEL_MSB    7
#define I2C_BBPLL_OC_DLREF_SEL_LSB    6

#define I2C_BBPLL_OC_DCUR        5
#define I2C_BBPLL_OC_DCUR_MSB    2
#define I2C_BBPLL_OC_DCUR_LSB    0

#define I2C_BBPLL_OC_BST_DIV        5
#define I2C_BBPLL_OC_BST_DIV_MSB    3
#define I2C_BBPLL_OC_BST_DIV_LSB    3

#define I2C_BBPLL_OC_BST_E2C        5
#define I2C_BBPLL_OC_BST_E2C_MSB    4
#define I2C_BBPLL_OC_BST_E2C_LSB    4

#define I2C_BBPLL_OC_TSCHGP        5
#define I2C_BBPLL_OC_TSCHGP_MSB    5
#define I2C_BBPLL_OC_TSCHGP_LSB    5

#define I2C_BBPLL_OC_BW        5
#define I2C_BBPLL_OC_BW_MSB    7
#define I2C_BBPLL_OC_BW_LSB    6

#define I2C_BBPLL_OR_LOCK1        6
#define I2C_BBPLL_OR_LOCK1_MSB    0
#define I2C_BBPLL_OR_LOCK1_LSB    0

#define I2C_BBPLL_OR_LOCK2        6
#define I2C_BBPLL_OR_LOCK2_MSB    1
#define I2C_BBPLL_OR_LOCK2_LSB    1

#define I2C_BBPLL_OR_CAL_CAP        7
#define I2C_BBPLL_OR_CAL_CAP_MSB    3
#define I2C_BBPLL_OR_CAL_CAP_LSB    0

#define I2C_BBPLL_OR_CAL_UDF        7
#define I2C_BBPLL_OR_CAL_UDF_MSB    4
#define I2C_BBPLL_OR_CAL_UDF_LSB    4

#define I2C_BBPLL_OR_CAL_OVF        7
#define I2C_BBPLL_OR_CAL_OVF_MSB    5
#define I2C_BBPLL_OR_CAL_OVF_LSB    5

#define I2C_BBPLL_OR_CAL_END        7
#define I2C_BBPLL_OR_CAL_END_MSB    6
#define I2C_BBPLL_OR_CAL_END_LSB    6

#define I2C_BBPLL_BBADC_DELAY1        8
#define I2C_BBPLL_BBADC_DELAY1_MSB    1
#define I2C_BBPLL_BBADC_DELAY1_LSB    0

#define I2C_BBPLL_BBADC_DELAY2        8
#define I2C_BBPLL_BBADC_DELAY2_MSB    3
#define I2C_BBPLL_BBADC_DELAY2_LSB    2

#define I2C_BBPLL_BBADC_DELAY3        8
#define I2C_BBPLL_BBADC_DELAY3_MSB    5
#define I2C_BBPLL_BBADC_DELAY3_LSB    4

#define I2C_BBPLL_BBADC_DELAY4        8
#define I2C_BBPLL_BBADC_DELAY4_MSB    7
#define I2C_BBPLL_BBADC_DELAY4_LSB    6

#define I2C_BBPLL_BBADC_DELAY5        9
#define I2C_BBPLL_BBADC_DELAY5_MSB    1
#define I2C_BBPLL_BBADC_DELAY5_LSB    0

#define I2C_BBPLL_BBADC_DELAY6        9
#define I2C_BBPLL_BBADC_DELAY6_MSB    3
#define I2C_BBPLL_BBADC_DELAY6_LSB    2

#define I2C_BBPLL_BBADC_DSMP        9
#define I2C_BBPLL_BBADC_DSMP_MSB    7
#define I2C_BBPLL_BBADC_DSMP_LSB    4

#define I2C_BBPLL_DTEST        10
#define I2C_BBPLL_DTEST_MSB    1
#define I2C_BBPLL_DTEST_LSB    0

#define I2C_BBPLL_ENT_ADC        10
#define I2C_BBPLL_ENT_ADC_MSB    3
#define I2C_BBPLL_ENT_ADC_LSB    2

#define I2C_BBPLL_BBADC_DIV        10
#define I2C_BBPLL_BBADC_DIV_MSB    5
#define I2C_BBPLL_BBADC_DIV_LSB    4

#define I2C_BBPLL_ENT_PLL        10
#define I2C_BBPLL_ENT_PLL_MSB    6
#define I2C_BBPLL_ENT_PLL_LSB    6

#define I2C_BBPLL_OC_ENB_VCON        10
#define I2C_BBPLL_OC_ENB_VCON_MSB    7
#define I2C_BBPLL_OC_ENB_VCON_LSB    7

#define I2C_BBPLL_DIV_DAC        11
#define I2C_BBPLL_DIV_DAC_MSB    0
#define I2C_BBPLL_DIV_DAC_LSB    0

#define I2C_BBPLL_DIV_CPU        11
#define I2C_BBPLL_DIV_CPU_MSB    1
#define I2C_BBPLL_DIV_CPU_LSB    1

#define I2C_BBPLL_BBADC_INPUT_SHORT        11
#define I2C_BBPLL_BBADC_INPUT_SHORT_MSB    2
#define I2C_BBPLL_BBADC_INPUT_SHORT_LSB    2

#define I2C_BBPLL_BBADC_CAL_9_8        11
#define I2C_BBPLL_BBADC_CAL_9_8_MSB    4
#define I2C_BBPLL_BBADC_CAL_9_8_LSB    3

#define I2C_BBPLL_BBADC_DCM        11
#define I2C_BBPLL_BBADC_DCM_MSB    6
#define I2C_BBPLL_BBADC_DCM_LSB    5

#define I2C_BBPLL_ENDIV5        11
#define I2C_BBPLL_ENDIV5_MSB    7
#define I2C_BBPLL_ENDIV5_LSB    7

#define I2C_BBPLL_BBADC_CAL_7_0        12
#define I2C_BBPLL_BBADC_CAL_7_0_MSB    7
#define I2C_BBPLL_BBADC_CAL_7_0_LSB    0

