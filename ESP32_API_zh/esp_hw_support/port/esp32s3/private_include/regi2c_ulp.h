/*
 * SPDX文件版权文本：2015-2021浓缩咖啡系统（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */

#pragma once

/**
 * @file 寄存器2c_ulp.h
 * @brief 注册模拟量定义以校准o_code以获得更精确的电压。
 *
 * 此文件列出了位于内部配置总线上的ULP寄存器字段。这些定义通过regi2c_ctrl.h中定义的宏，由rtc_init.c中的rtc_init函数使用。
 */

#define I2C_ULP 0x61
#define I2C_ULP_HOSTID 1

#define I2C_ULP_IR_RESETB 0
#define I2C_ULP_IR_RESETB_MSB 0
#define I2C_ULP_IR_RESETB_LSB 0

#define I2C_ULP_O_DONE_FLAG 3
#define I2C_ULP_O_DONE_FLAG_MSB 0
#define I2C_ULP_O_DONE_FLAG_LSB 0

#define I2C_ULP_BG_O_DONE_FLAG 3
#define I2C_ULP_BG_O_DONE_FLAG_MSB 3
#define I2C_ULP_BG_O_DONE_FLAG_LSB 3

