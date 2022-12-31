/*
 * SPDX文件版权文本：2015-2021浓缩咖啡系统（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */

#pragma once

/**
 * @file 区域2c_lp_bias.h
 * @brief 注册模拟量定义以校准o_code以获得更精确的电压。
 *
 * 该文件列出了位于内部配置总线上的低功耗dbais的寄存器字段。这些定义通过regi2c_ctrl中定义的宏使用。h、 由rtc_init.c中的rtc_init函数执行。
 */

#define I2C_ULP 0x61
#define I2C_ULP_HOSTID 0

#define I2C_ULP_IR_RESETB 0
#define I2C_ULP_IR_RESETB_MSB 0
#define I2C_ULP_IR_RESETB_LSB 0

#define I2C_ULP_IR_FORCE_XPD_CK 0
#define I2C_ULP_IR_FORCE_XPD_CK_MSB 2
#define I2C_ULP_IR_FORCE_XPD_CK_LSB 2

#define I2C_ULP_IR_FORCE_XPD_IPH 0
#define I2C_ULP_IR_FORCE_XPD_IPH_MSB 4
#define I2C_ULP_IR_FORCE_XPD_IPH_LSB 4

#define I2C_ULP_IR_DISABLE_WATCHDOG_CK 0
#define I2C_ULP_IR_DISABLE_WATCHDOG_CK_MSB 6
#define I2C_ULP_IR_DISABLE_WATCHDOG_CK_LSB 6

#define I2C_ULP_O_DONE_FLAG 3
#define I2C_ULP_O_DONE_FLAG_MSB 0
#define I2C_ULP_O_DONE_FLAG_LSB 0

#define I2C_ULP_BG_O_DONE_FLAG 3
#define I2C_ULP_BG_O_DONE_FLAG_MSB 3
#define I2C_ULP_BG_O_DONE_FLAG_LSB 3

#define I2C_ULP_OCODE 4
#define I2C_ULP_OCODE_MSB 7
#define I2C_ULP_OCODE_LSB 0

#define I2C_ULP_IR_FORCE_CODE 5
#define I2C_ULP_IR_FORCE_CODE_MSB 6
#define I2C_ULP_IR_FORCE_CODE_LSB 6

#define I2C_ULP_EXT_CODE 6
#define I2C_ULP_EXT_CODE_MSB 7
#define I2C_ULP_EXT_CODE_LSB 0

