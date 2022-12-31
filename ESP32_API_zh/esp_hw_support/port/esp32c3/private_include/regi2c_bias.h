/*
 * SPDX文件版权文本：2015-2021浓缩咖啡系统（上海）有限公司
 *
 * SPDX许可证标识符：Apache-2.0
 */

#pragma once

/**
 * @file 区域2c_bias.h
 * @brief 偏差寄存器定义
 *
 * 此文件列出BIAS的寄存器字段。这些定义通过regi2c_ctrl.h中定义的宏和bootloader_esp32c3.c中的bootloader_hardware_init函数使用。
 */

#define I2C_BIAS            0X6A
#define I2C_BIAS_HOSTID     0

#define I2C_BIAS_DREG_1P1_PVT 1
#define I2C_BIAS_DREG_1P1_PVT_MSB 3
#define I2C_BIAS_DREG_1P1_PVT_LSB 0

